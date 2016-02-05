require 'active_record'
require 'sqlite3'
require 'awesome_print'
ActiveRecord::Base.establish_connection :adapter => "sqlite3",
    :database => "collins.db"

class Zhwords < ActiveRecord::Base

end
words = []
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

