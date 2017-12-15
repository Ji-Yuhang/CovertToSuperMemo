require_relative 'unit'
require 'erb'
require 'open-uri'
require 'active_support'
require_relative '../thesaurus'
require_relative '../shanbay_local'
require_relative '../shanbay'
require_relative '../bgl'

class CovertHelper
  def highlight_word(sentence, word)
  end
  def cloze_word(sentence, word)
  end
  def multi_space(count)
  end

  def cn_word(word)
    word.gsub!(/\s\(.*$/, '')
    data = ShanbayDB::local_data word
    puts word
    data = ShanbayHttp::http_data word if data.nil?
    if data
      cndef = data["cn_definition"]["defn"] if data["cn_definition"]
      word = data["content"]
      return cndef
    else
      return ''
    end
  end

  def download_file(file_name,url)
    open(file_name, 'wb') do |file|
      file << open(url).read
    end
  end

  def pron_to_html(pron)
    pron.unpack("U*").map{|c| "&##{c.to_s};"}.join
  end
end

# Import:
# covert Word to Memo Unit
class CovertStrategy < CovertHelper
  include ::ActiveSupport::Inflector
end

# by Collins dictionary
class CollinsCovertStrategy < CovertStrategy
  def covert_to_memo_unit(collins)
  end
end

# by Shanbay API
class ShanbayCovertStrategy < CovertStrategy
  def covert_to_memo_unit(shanbay)
  end
end

# 

class EnWordToShanbayCN < ShanbayCovertStrategy
  def covert_to_memo_unit(shanbay)
  end
end

class EnExampleToEnExplaionCN < CollinsCovertStrategy
  def covert_to_memo_unit(word)
    # render erb
    
    question =  Question.new
    answer =  Answer.new
    sound = Sound.new

    @word = word
    #@thesaurus = Thesaurus.thesaurus word

    @data = ShanbayDB::local_data word
    #@data = ShanbayHttp::http_data word if @data.nil?
    return nil unless @data
    return nil unless @data["cn_definition"]
    @cndef = @data["cn_definition"]["defn"]
    @endef = @data["en_definition"]
    @word = @data["content"]
    @pron = pron_to_html(@data["pron"])
    @thesaurus = @data["thesaurus"]
    @audio = @data["us_audio"]

    @bgl = Bgl.bgl(@word)
    a, @yinjie, c = @bgl


    question.html= "<b>#{word}</b>"
    answer.html= "<b>#{word}</b>"

    audio_name = @audio.match(/([\w%-]+).mp3$/)[0]
    sound.name = ""
    sound.text = @pron
    sound.url = "[SecondaryStorage]\\" + audio_name
    sound.source = @audio

    #download_file(audio_name, @audio)
    
    
    question_erb = ERB.new(File.read("#{underscore(self.class.to_s)}_question.html.erb"))
    question.html = question_erb.result binding

    answer_erb = ERB.new(File.read("#{underscore(self.class.to_s)}_answer.html.erb"))
    answer.html = answer_erb.result binding



    unit = Unit.new
    unit.question = question
    unit.answer = answer
    unit.sound = sound
    return unit
  end
end

########################################################
# I need modify strategy at runtime
# strategy/en_sentence_to_cn_sentence.rb
# or en_sentence_to_cn_sentence.yaml
# name : en_sentence_to_cn_sentence
# template :
#   Q : 
#     en sentence of collins
#     Sound:
#       word
#     Movie:
#       Sometime we must endure a little pain, in order to achieve satisfaction
#       
#   A :
#     zh sentence of collins
#     explicit word en explain
#     explicit word cn explicit
#     thesaurus
#     pronunciation
#     morphology
#     
#   
#
