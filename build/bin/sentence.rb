gem 'bigdecimal', '~> 1.1'
require 'active_record'
require 'sqlite3'
require 'awesome_print'
ActiveRecord::Base.establish_connection :adapter => "sqlite3",
    :database => "collins.db"

class Zhwords < ActiveRecord::Base
end
class Zhmultiword < ActiveRecord::Base
    self.inheritance_column = :_type_disabled
end
$map = Hash.new # word => [zhs]
def find_collins_word(word)
    ap Zhmultiword.find 182
    zhs = Zhmultiword.where :word=>word
    #ap word
    #ap zhs.class
    ap word if word.nil?
    ap word.class
    zhs.each do |zh|
        ap zh
    end
    ap zhs.size if zhs.nil?
    $maps[word] = zhs
end

wordlist = []
words = File.read './star3-wordlist/1.txt'
words.each_line do |word|
    word.chomp!
    wordlist.push word
    ap word
    find_collins_word word
end
ap wordlist
ap $map

=begin
zhs = Zhwords.where :frequency=>3
zhs.each do |zh|
    words.push  zh.word
end
words.pop
copy = words.shuffle 
ap copy.size
index =1
while copy.size>0
    list = copy.slice!(1,30)
    ap list
    ap list.size
    copy.shuffle!
    filename = "./star3-wordlist/#{index}.txt"
    index += 1
    io = File.open(filename,"w")
    list.each do |word|
        io.puts word
    end
    io.close
    
end
=end

