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
    if words.is_a? Array
      @word_list += words
    else
      @word_list << words
    end
  end

  def make_collection
    collection = Collection.new
    @word_list.each do |word|
      units = @strategy.covert_to_memo_unit(word)
      collection.add_memo_unit_list units if units
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
