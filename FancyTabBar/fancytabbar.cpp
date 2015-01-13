#include "fancytabbar.h"

#include <QPainter>
#include <QDebug>
#include <QLinearGradient>
#include <QMouseEvent>

/*!
 * \brief FancyTabBar::FancyTabBar is basic constructor if you want to
 *   create stand alone window with menu.
 */
FancyTabBar::FancyTabBar() : QWidget(NULL)
{
    init();
}

/*!
 * \brief FancyTabBar::FancyTabBar is used for creating embedded fancyTabBar
 *   into some window.
 * \param widget
 * \see QWidget documentation.
 */
FancyTabBar::FancyTabBar(QWidget *widget) :
    QWidget(widget)
{
    init();
}

/*!
 * \brief FancyTabBar::~FancyTabBar delete allocated memory (free tabVector).
 */
FancyTabBar::~FancyTabBar()
{
    for(int i = 0; i < tabVector.size(); i++)
    {
        delete tabVector.at(i);
    }
    tabVector.clear();
}

/*!
 * \brief FancyTabBar::addFancyTab add fancy tab to tab bar. New tab will
 *    contain passed icon and taxst as capption.
 * \param icon will be showed as tab icon. It is similar to tool bar icon.
 * \param text will be showed as captoin.
 * \return return id (index) of tab. This value is returned by signal. Indexes
 *    are starting at 0 and they are incremented with each new tab.
 * \see FancyTabBar::activeIndexChanged()
 */
qint32 FancyTabBar::addFancyTab(QIcon icon, QString text)
{
    FancyTab *fancyTab = new FancyTab(icon, text);
    tabVector.append(fancyTab);
    setMinimumHeight((tabHeight * tabVector.size()) + 2);
    return tabVector.size() - 1;
}

/*!
 * \brief FancyTabBar::getActiveIndex return index of active tab.
 * \return index of active tab.
 */
qint32 FancyTabBar::getActiveIndex() const
{
    return activeIndex;
}

/*!
 * \brief FancyTabBar::setActiveIndex set active tab. This function is mostly
 *    used on start up to set which tab is active.
 * \param index tab index
 * \return FancyTabBar::SUCESS if sucesfuly set.
 * \return FancyTabBar::INDEX_OUT_OF_RANGE if index is out of possible range.
 */
FancyTabBar::Error FancyTabBar::setActiveIndex(qint32 index)
{
    if(index >= tabVector.size() || index < 0)
        return INDEX_OUT_OF_RANGE;

    activeIndex = index;
    emit activeIndexChanged(activeIndex);

    return SUCESS;
}

/*!
 * \brief FancyTabBar::paintEvent
 * \param event
 */
void FancyTabBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // Reduced size is size reduced by one becouse we need to draw from 0
    // so size - 1. That how all arrays works ;)
    QSize reducedSize = this->size() - QSize(1, 1);

    // Draw separation rect
    // Rest of parameters are zeros becouse we want to do only vertical
    // gradient.
    QLinearGradient linearGradient(0, 0, reducedSize.width(), 0);
    linearGradient.setColorAt(0, QColor(64, 64, 64));
    linearGradient.setColorAt(1, QColor(130, 130, 130));

    painter.setBrush(linearGradient);
    painter.setPen(QColor(49, 49, 49));
    painter.drawRect(0, 0, reducedSize.width(), reducedSize.height());

    // Draw additional separation line to right side of bar
    // This makes it more fancy ;)
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(171, 171, 171));
    painter.drawLine(reducedSize.width() - 1, 1, reducedSize.width() - 1,
        reducedSize.height() - 1);


    if(hower >= 0 && hower != activeIndex)
    {
        QLinearGradient lineaGradientHover = QLinearGradient(0, 0, reducedSize.width(), 0);
        lineaGradientHover.setColorAt(0, QColor(200,200,200, 20));
        lineaGradientHover.setColorAt(0.5, QColor(200,200,200, 100));
        lineaGradientHover.setColorAt(1, QColor(200,200,200, 20));
        painter.setPen(Qt::NoPen);
        painter.setBrush(lineaGradientHover);
        painter.drawRect(getTabRect(hower));
    }

    for(int i = 0, y = 0; i < tabVector.size(); i++, y += 50)
    {
        // Active tab must be drawen last because it will draw into neighbours
        // tabs... This is most easy way how to draw specific frames
        if(activeIndex != i)
        {
            drawTabContent(&painter, i);
        }
    }

    // Draw activ tab if any
    // Will draw into neighbors tab!!!
    if(activeIndex >= 0)
    {
        // Make gradient more lighter. This indicate active tab
        QColor color1(170,170,170);
        QColor color2(233,233,233);
        linearGradient.setColorAt(0, color1);
        linearGradient.setColorAt(1, color2);

        painter.setBrush(linearGradient);
        painter.setPen(Qt::NoPen);
        painter.drawRect(getTabRect(activeIndex));

        drawTabContent(&painter, activeIndex, true);

        painter.setPen(QColor(49, 49, 49));

        QRect r = getTabRect(activeIndex).adjusted(-1, -1, 1, 1);
        // Draw top line
        painter.drawLine(r.topLeft(), r.topRight());
        // Draw bottom line
        painter.drawLine(r.bottomLeft(), r.bottomRight());

        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush());
        color1.setRgb(100, 100, 100);
        color2.setRgb(150, 150, 150);
        linearGradient.setColorAt(0, color1);
        linearGradient.setColorAt(1, color2);
        painter.setBrush(linearGradient);
        r.adjust(1, -1, 0, 1);
        // Draw top line
        painter.drawRect(r.left(), r.top(), r.right()-1, 1);
        // Draw bottom line
        painter.drawRect(r.left(), r.bottom(), r.right()-1, 1);
    }
}

/*!
 * \brief FancyTabBar::mouseReleaseEvent
 * \param event
 */
void FancyTabBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        activeIndex = getTabIndexByPoint(event->x(), event->y());
        update();

        emit activeIndexChanged(activeIndex);
    }
    QWidget::mouseReleaseEvent(event);
}

/*!
 * \brief FancyTabBar::mouseMoveEvent
 * \param event
 */
void FancyTabBar::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    hower = getTabIndexByPoint(event->x(), event->y());
    update();
}

/*!
 * \brief FancyTabBar::enterEvent
 * \param event
 */
void FancyTabBar::enterEvent(QEvent *event)
{
    QEnterEvent *enterEvent = static_cast<QEnterEvent*>(event);
    hower = getTabIndexByPoint(enterEvent->x(), enterEvent->y());
    update();
}

/*!
 * \brief FancyTabBar::leaveEvent
 * \param event
 */
void FancyTabBar::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    hower = -1;
    update();
}

/*!
 * \brief FancyTabBar::getTabRect
 * \param index
 * \return
 */
QRect FancyTabBar::getTabRect(qint32 index)
{
    qint32 tabPos = getTabYPos(index);
    return QRect(1, tabPos, tabWidth, tabHeight);
}

/*!
 * \brief FancyTabBar::getIconRect
 * \param index
 * \return
 */
QRect FancyTabBar::getIconRect(qint32 index)
{
    qint32 iconPos = getTabYPos(index) + tabTopSpaceing;
    return QRect((tabWidth - iconSize) / 2, iconPos, iconSize, iconSize);
}

/*!
 * \brief FancyTabBar::getTextRect
 * \param index
 * \return
 */
QRect FancyTabBar::getTextRect(qint32 index)
{
    qint32 textPos = getTabYPos(index) + tabTopSpaceing + iconSize;
    return QRect(1, textPos, tabWidth, textHeight);
}

/*!
 * \brief FancyTabBar::getTabYPos
 * \param index
 * \return
 */
qint32 FancyTabBar::getTabYPos(qint32 index)
{
    return (tabHeight * index) + 1;
}

/*!
 * \brief FancyTabBar::getTabIndexByPoint
 * \param x
 * \param y
 * \return
 */
qint32 FancyTabBar::getTabIndexByPoint(qint32 x, qint32 y)
{
    if(x < 1 || x > tabWidth)
        return -1;
    if(y > ((tabVector.size() * tabHeight) - 2))
        return -1;

    return (y-1)/tabHeight;
}

/*!
 * \brief FancyTabBar::drawTabContent
 * \param painter
 * \param index
 * \param invertTextColor
 */
void FancyTabBar::drawTabContent(QPainter *painter, qint32 index,
                                 bool invertTextColor)
{
    if(invertTextColor)
        painter->setPen(QColor(65, 65, 65));
    else
        painter->setPen(QColor(255, 255, 255));

    QFont font = painter->font();
    font.setBold(true);
    font.setPixelSize(10);
    painter->setFont(font);

    QPixmap pixmap = tabVector[index]->m_icon.pixmap(iconSize, iconSize);

    QRect iconRect = getIconRect(index);
    QRect textRect = getTextRect(index);

    painter->drawPixmap(iconRect.topLeft(), pixmap);
    painter->drawText(textRect, Qt::AlignBottom | Qt::AlignHCenter,
                      tabVector[index]->m_text);
}

/*!
 * \brief FancyTabBar::init
 */
void FancyTabBar::init()
{
    activeIndex = -1;

    barWidth = 80;

    setMaximumWidth(barWidth);
    setMinimumWidth(barWidth);

    iconSize = 36;
    textHeight = 10;
    tabWidth  = barWidth - 2;   // Two are substraceted because there are two
                                // pixels of frame.
    textWidth  = tabWidth;
    tabHeight = 50;
                     // on the left side
    tabTopSpaceing = 1;

    setMouseTracking(true);
    hower = -1;


    // TODO: Reasonable min/max width/height setup
}
