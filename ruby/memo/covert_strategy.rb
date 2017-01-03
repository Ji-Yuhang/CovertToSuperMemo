require_relative 'unit'
require 'erb'
require 'active_support'

class CovertHelper
  def highlight_word(sentence, word)
  end
  def cloze_word(sentence, word)
  end
  def pron_to_html(pron)
  end
  def multi_space(count)
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

    question.html= "<b>#{word}</b>"
    answer.html= "<b>#{word}</b>"
    sound.name= "<b>#{word}</b>"

    
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
