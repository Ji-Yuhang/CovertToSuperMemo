#!/usr/bin/env ruby

class Bgl
  @@bgl_json_path = 'webster_mini.json'

  @@bgl = JSON.parse(File.read(@@bgl_json_path))

  def self.bgl(word)
    #puts word
    #puts @@thesaurus.size
    #puts @@thesaurus.include? word
    return @@bgl[word]
  end

  def self.all_bgl
    @@bgl
  end
end

#puts Thesaurus.thesaurus(ARGV[0])

