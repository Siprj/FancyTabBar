#ifndef FANCYTAB_H
#define FANCYTAB_H

#include <QString>
#include <QIcon>

class FancyTab
{
public:
    FancyTab(QIcon &icon, QString text);

    QString m_text;
    QIcon m_icon;
};

#endif // FANCYTAB_H
