require_relative 'collins_to_memo'
def main
    #app = Qt::Application.new ARGV

    wordlist = "a b c d e f g"
    collins2Memo = CollinsWordToMemo.new EnExampleToEnExplaionCN.new
    collins2Memo.add_word_list wordlist
    now = Time.now.strftime "%Y%m%d-%H%M%S"
    puts now
    collection = collins2Memo.make_collection
    collection.shuffle
    collection.to_xml_file "supermemo-#{now}.xml"
    
    #app.exec
end
if __FILE__ == $0
    main
end
