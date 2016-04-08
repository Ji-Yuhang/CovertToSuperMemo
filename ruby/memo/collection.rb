require_relative 'unit'

class Collection
  def initialize
    @units = [] # vector<Unit>
  end

  def add_memo_unit(unit)
    @units << unit
  end

  def add_memo_unit_list(units)
    @units << units
  end

  def shuffle
    @units.shuffle!

  end

  def to_xml_file(file)
    #TODO: stream_out to xml file

  end

  def pron_to_html(pron)
    #TODO: utf8 char to &#3215;
  end


end
