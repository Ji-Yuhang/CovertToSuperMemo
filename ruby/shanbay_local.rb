#!/usr/bin/env ruby
#gem 'bigdecimal', '1.2.4'
require 'active_record'
require 'sqlite3'
#require 'awesome_print'
require 'socket'
require 'json'
require_relative "thesaurus"

module ShanbayDB
    ActiveRecord::Base.establish_connection :adapter => "sqlite3",
        :database =>  File.join(ENV["HOME"],"vimrc/shanbay.db")

    class Words < ActiveRecord::Base
    end

    def local_data(word)
        list = ShanbayDB::Words.where :word => word
        if list.size > 0
            jsonstr = list.first.json
            data = JSON.parse(jsonstr)
            data["thesaurus"] = Thesaurus.thesaurus(data["content"])
            return data
        else
            return nil
        end
    end

    module_function :local_data
end

