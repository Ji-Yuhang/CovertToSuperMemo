#!/usr/bin/env ruby
require "open-uri"
require "json"
require 'uri'
#require "iconv"
require_relative "shanbay_local"

module ShanbayHttp
  def http_data(word)
    puts "ShanbayHttp::http_data #{word}"
    begin
      getwordui = URI.escape("https://api.shanbay.com/bdc/search/?word=#{word}")
      open( getwordui) do |io|
        jsonstr =  io.read
        json = JSON.parse(jsonstr)
        data = json["data"]
        return data
      end
    rescue
      return nil
    end
    return nil
  end
  def local_http_data(word)
    getwordui = "http://localhost/shanbayword/?word=#{word}"
    open( getwordui) do |io|
      jsonstr =  io.read
      #Iconv.conv('gbk','utf-8',result)
      json = JSON.parse(jsonstr)
      #data = json["data"]
      return json
    end
    return nil
  end
  module_function :http_data, :local_http_data
end

def parse_shanbay_data(data)
    cndef = data["cn_definition"]
    endef = data["en_definition"]
    word = data["content"]
    pron = data["pron"]
    thesaurus = data["thesaurus"]
    if ARGV[1] == "only_english"
      print  " [ " + pron + " ]"
      puts endef["defn"]
    else
      printf word
      if !pron.empty?
        print  "\t [ " + pron + " ]"
        print "\n"
      end


      puts cndef["defn"]
      puts endef["defn"]

      puts_thesaurus thesaurus
    end

    audio = data["us_audio"]
    #system "mplayer " + audio + " >/dev/null 2>&1"
    exec("mplayer " + audio + " >/dev/null 2>1") if fork.nil?

    #localmdeid = "/Users/jiyuhang/Documents/Anki/用户1/collection.media/#{word}.mp3"
    #    pid = fork { exec 'wget',audio,'-o',localmdeid }
    #    pid = fork{ exec 'afplay', localmdeid }

end

def puts_thesaurus(thesaurus)
  return if thesaurus.nil?
  thesaurus.each do | noun, list_list |
    puts noun + ":"
    list_list.each_with_index do |list,index|
      puts "    #{index}. #{list.join(' -> ')}"
      
    end
    
  end
end

def main
    argu = ARGV[0]
    if argu && argu.chomp
      word = argu.chomp
      data = ShanbayDB::local_data word
      #data = nil
      data = ShanbayHttp::http_data word if data.nil?
      parse_shanbay_data data
    end
end

#main
