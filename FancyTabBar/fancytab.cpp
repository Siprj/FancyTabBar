#include "fancytab.h"

#include <QDebug>

FancyTab::FancyTab(QIcon &icon, QString text)
{
    m_icon = icon;
    m_text = text;
}
