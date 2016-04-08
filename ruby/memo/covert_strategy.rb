require_relative 'unit'

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
  def covert_to_memo_unit(collins)
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
