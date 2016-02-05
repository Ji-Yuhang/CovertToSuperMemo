#ifndef MEMOUNIT_H
#define MEMOUNIT_H
#include <QString>
#include <QUrl>
class HtmlHelper {
public:
    HtmlHelper();
};

class Question : public HtmlHelper {
public:
    Question();
    Question(const QString& plainText);
    Question(const Question& other);
    QString toHtmlString();
private:
    QString html_;
};

class Answer : public HtmlHelper {
public:
    Answer();
    Answer(const QString& plainText);
    Answer(const Answer& other);

    QString toHtmlString();
private:
    QString html_;
};

class Sound {
public:
    Sound();
    Sound(const QString& name, const QString& url, const QString& text);
    Sound(const Sound& other);

    void setText(const QString& text) {text_ = text;}
    void setUrl(const QString& url) {url_ = url;}
    void setName(const QString& name) {name_ = name;}
    void setSource(const QUrl& source) {source_ = source;}

    QString text() const {return text_;}
    QString url() const {return url_;}
    QString name() const {return name_;}
    QUrl source() const {return source_;}

    bool isNull() const {return url_.isEmpty();}

private:
    QString text_;
    QString url_;
    QString name_;
    QUrl source_;

};

class MemoUnit
{
public:
    MemoUnit();
    MemoUnit(const Question& question, const Answer& answer, const Sound& sound);
    MemoUnit(const MemoUnit& other);
    void setQuestion(const Question& question);
    void setAnswer(const Answer& answer);
    void setSound(const Sound& sound);
    Question question() const {return question_;}
    Answer answer() const {return answer_;}
    Sound sound() const {return sound_;}
    bool haveSound() const {return !sound_.isNull();}
private:
    Question question_;
    Answer answer_;
    Sound sound_;
};

#endif // MEMOUNIT_H
