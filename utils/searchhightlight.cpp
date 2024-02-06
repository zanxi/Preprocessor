#include "searchhightlight.h"

#include <QTextCharFormat>
#include "Debug/logger.h"

SearchHighLight::SearchHighLight(QTextDocument* parent) : BaseClass(parent)
{
    // Set the backlight color
    m_format.setBackground(Qt::red);
}

void SearchHighLight::highlightBlock(const QString& text)
{
    // Using a regular expression, we find all matches.
    QRegularExpressionMatchIterator matchIterator = m_pattern.globalMatch(text);
    while (matchIterator.hasNext())
    {
        // Highlight all matches
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), m_format);        
        Pos pos;
        pos.start = match.capturedStart();
        pos.end = match.capturedEnd();
        positions.append(pos);
        //logger::WriteLog("Find text: ["+text+"]: start: "+ QString::number(pos.start) + "; end: " + QString::number(pos.end) );
    }
}

void SearchHighLight::searchText(const QString& text)
{
    positions.clear();
    // Set the text as a regular expression.
    m_pattern = QRegularExpression(text);
    rehighlight(); // Restart the backlight
}
