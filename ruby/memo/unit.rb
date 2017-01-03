class HtmlHelper
  attr_accessor :html
end

class Question < HtmlHelper
end

class Answer < HtmlHelper
end

class Sound
  attr_accessor :text
  attr_accessor :url
  attr_accessor :name
  attr_accessor :source

  def is_null?
    #TODO: url.isEmpty?
  end
end

class Unit
  attr_accessor :question
  attr_accessor :answer
  attr_accessor :sound

  def have_sound?
    #TODO: sound.isNull?
  end
end
