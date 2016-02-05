#include "memounit.h"
HtmlHelper::HtmlHelper()
{

}

Question::Question()
{

}


Question::Question(const QString& plainText) : html_(plainText)
{

}

Question::Question(const Question &other)
{
    this->html_ = other.html_;
}

QString Question::toHtmlString()
{
    return html_;
}

Answer::Answer()
{

}

Answer::Answer(const QString& plainText) : html_(plainText)
{

}

Answer::Answer(const Answer &other)
{
    this->html_ = other.html_;

}

QString Answer::toHtmlString()
{
    return html_;

}



MemoUnit::MemoUnit()
{

}

MemoUnit::MemoUnit(const Question &question, const Answer &answer, const Sound &sound)
{

}

MemoUnit::MemoUnit(const MemoUnit &other)
{
    this->question_ = other.question_;
    this->answer_ = other.answer_;
    this->sound_ = other.sound_;
}

void MemoUnit::setQuestion(const Question &question)
{
    question_ = question;
}

void MemoUnit::setAnswer(const Answer &answer)
{
    answer_ = answer;
}

void MemoUnit::setSound(const Sound &sound)
{
    sound_ = sound;
}

Sound::Sound()
{

}

Sound::Sound(const QString &name, const QString &url, const QString &text)
    :name_(name)
    ,url_(url)
    ,text_(text)
{

}

Sound::Sound(const Sound &other)
{
    this->name_ = other.name_;
    this->url_ = other.url_;
    this->text_ = other.text_;
    this->source_ = other.source_;
}
