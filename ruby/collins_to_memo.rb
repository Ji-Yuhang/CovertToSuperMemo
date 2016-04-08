require_relative 'memo/collection'
require_relative 'memo/covert_strategy'

class CollinsWordToMemo
  attr_writer :strategy
  def initialize(detach_strategy)
    @strategy = detach_strategy
    @word_list = []
  end

  def add_word(word)
    @word_list << word
  end
  
  def add_word_list(words)
    @word_list << words
  end

  def make_collection
    collection = Collection.new
    @word_list.each do |word|
=begin
      infos = Collins.zhCollins word
      infos.each do |info|
        unit = @strategy.covert_to_memo_unit info
        collection << unit
      end
=end
    end
    collection
  end

end
