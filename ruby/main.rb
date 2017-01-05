require_relative 'collins_to_memo'
require 'bundler'
Bundler.require
def main
    #app = Qt::Application.new ARGV

    collins1 = "/home/jiyuhang/Documents/collins1_list/collins_1_list_1.txt"
    wordlist = File.read(collins1).split("\n")#[0,10]
    #wordlist = "a b c d e f g"
    collins2Memo = CollinsWordToMemo.new EnExampleToEnExplaionCN.new
    collins2Memo.add_word_list wordlist
    now = Time.now.strftime "%Y%m%d-%H%M%S"
    puts now
    collection = collins2Memo.make_collection
    #collection.shuffle
    collection.to_xml_file "supermemo-#{now}.xml"
    
    #app.exec
end
if __FILE__ == $0
    main
end
