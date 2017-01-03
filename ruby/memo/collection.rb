require_relative 'unit'
#require "nokogiri"
class Collection
  def initialize
    @units = [] # vector<Unit>
  end

  def download_file(file_name,url)
    puts "download_file #{file_name}"
    open(file_name, 'wb') do |file|
      file << open(url).read
    end
  end

  def add_memo_unit(unit)
    @units << unit
  end

  def add_memo_unit_list(units)
    if units.is_a? Array
      @units += units
    else
      @units << units
    end
    
  end

  def shuffle
    @units.shuffle!

  end

  def to_xml_file(file)
    #TODO: stream_out to xml file
    dirname = file.match(/([\w%-]+).xml/)[1]
    dirpath = "#{dirname}_files/Elements" 


    Dir.mkdir "#{dirname}_files"
    Dir.mkdir dirpath

    iid = 2
    builder = Nokogiri::XML::Builder.new :encoding => 'UTF-8' do |xml|
      xml.SuperMemoCollection {
        xml.count @units.count
        xml.SuperMemoElement {
          xml.ID 1
          xml.Title Time.now
          xml.Type "Topic"

          @units.each do |unit|
            iid += 2
            xml.SuperMemoElement {
              xml.ID  iid
              xml.Type "Item"
              xml.Oridinal "100"
              xml.Content {
                xml.Question unit.question.html
                xml.Answer unit.answer.html
                xml.Sound {
                  audio_name = unit.sound.url.match(/([\w%]+).mp3$/)[0]
                  download_file(dirpath + "/" + audio_name,unit.sound.source )
                  xml.Text unit.sound.text
                  xml.URL unit.sound.url
                  xml.Name unit.sound.name
                  # copy source
                }
              }
              
            } # unit element
          end
        } # topic element
      } # root collection
    end
    File.open file, 'w' do |io|
      io.puts builder.to_xml
    end
  end

  def pron_to_html(pron)
    #TODO: utf8 char to &#3215;
  end


end
