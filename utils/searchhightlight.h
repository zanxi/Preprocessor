#ifndef SEARCHHIGHTLIGHT_H
#define SEARCHHIGHTLIGHT_H


#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QList>

class SearchHighLight : public QSyntaxHighlighter
{
    Q_OBJECT
    using BaseClass = QSyntaxHighlighter;
public:
    explicit SearchHighLight(QTextDocument* parent = nullptr);

    void searchText(const QString& text);    

protected:
    virtual void highlightBlock(const QString &text) override;



private:
    QRegularExpression m_pattern; // Regular expression to search for, in our case, this word or text
    QTextCharFormat m_format;     // Text formatting, highlighting

    struct Pos{
        int start;
        int end;
    };

    QList<Pos> positions;
    QRegularExpressionMatchIterator matchIterator;
};


#endif // SEARCHHIGHTLIGHT_H
