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
$map = {} # word => [zhs]
def find_collins_word(word)
    zhs = Zhmultiword.where :word=>word
    #ap word
    #ap zhs.class
    zhs.each do |zh|
        #ap zh
    end
    $map[word] = zhs
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
lines = []
$map.each do |key, zhs|
    zhs.each do |zh|
        content = zh.sentence
        next if content.nil?
        content += "    "if !zh.cn.nil?
        content += zh.cn if !zh.cn.nil?
        content += "  "
        content += zh.word
        
        lines.push content
        #io.puts content
    end
end
lines.shuffle!
io = File.open('./star3-wordlist/1-sentence-cn.txt', 'w')
lines.each do |line|
    io.puts line
end
io.close

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

