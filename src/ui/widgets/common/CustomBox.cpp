//
// Created by shingesa on 29/07/25.
//

#include "CustomBox.h"

#include <qcoreevent.h>
#include <QPainter>

CustomBox::CustomBox(Direction direction, QWidget *parent)
    :QWidget(parent)
      ,m_direction(direction)
      ,m_alignment(Alignment::Start)
      ,m_spacing(0)
      ,m_margins(0,0,0,0)
  {
  setAttribute(Qt::WA_StyledBackground, true);
  setMinimumSize(0, 0);
  }

CustomBox::~CustomBox() {
     clear();
}

void CustomBox::addItem(QWidget *item, int stretch) {
    if (!item) return;

    insertItem(m_items.size(), item,stretch);
}

void CustomBox::insertItem(int index, QWidget *item, int stretch) {
    if (!item || index < 0 || index > m_items.size())
        return;

    for (const auto &info :m_items) {
        if (info.widget == item) return;
    }

    item->setParent(this);
    item->show();

    m_items.insert(index,ItemInfo(item,qMax(0,stretch)));

    updateLayout();

    Q_EMIT itemAdded(item);
}

void CustomBox::removeItem(QWidget *item) {
    if (!item) return;
    if (const int index = indexOf(item); index!=-1) {
        removeItem(index);
    }
}

void CustomBox::removeItem(int index) {
    if (index < 0 || index > m_items.size()) return;

    QWidget *item = m_items[index].widget;
    m_items.removeAt(index);

    if (item) {
        item->setParent(nullptr);
        item->hide();
    }
    updateLayout();

    Q_EMIT itemRemoved(item);
}

void CustomBox::clear() {
    while (!m_items.isEmpty()) {
        removeItem(0);
    }
}

QWidget *CustomBox::itemAt(int index) const {
    if (index < 0 ||index > m_items.size()) return nullptr;

    return m_items[index].widget;
}

int CustomBox::indexOf(QWidget *item) const {
    for (int i = 0; i<m_items.size(); ++i) {
        if (m_items[i].widget == item) return i;
    }
    return -1;
}

void CustomBox::setDirection(Direction direction) {
    if (m_direction != direction) {
        m_direction = direction;
        updateLayout();
    }
}

void CustomBox::setSpacing(int spacing) {
    if (m_spacing !=spacing) {
        m_spacing = qMax(0,spacing);
        updateLayout();
    }
}

void CustomBox::setContentsMargins(int left, int top, int right, int bottom) {
        setContentsMargins(QMargins(left, top, right, bottom));
}

void CustomBox::setContentsMargins(const QMargins &margins) {
    if (m_margins !=margins) {
        m_margins = margins;
        updateLayout();
    }
}

QSize CustomBox::sizeHint() const {
    return calculateTotalSize();
}

QSize CustomBox::minimumSizeHint() const {
    QSize total (0, 0);

    for (const auto &info : m_items) {
        if (!info.widget || !info.widget->isVisible())continue;

        QSize itemMin = info.widget->minimumSizeHint();

        if (isHorizontal()) {
            total.rwidth()+= itemMin.width();
            total.rheight()+= qMax(total.height(), itemMin.height());
        }else {
            total.rwidth()+= qMax(total.width(),itemMin.width());
            total.rheight()+=itemMin.height();
        }
    }

    if (m_items.size() > 1) {
        int spacingTotal = m_spacing * (m_items.size()-1);
        if (isHorizontal()) {
            total.rwidth()+=spacingTotal;
        }else {
            total.rheight()+=spacingTotal;
        }
    }

    total+=QSize(m_margins.left()+m_margins.right(), m_margins.top()+m_margins.bottom());

    return total;
}


void CustomBox::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updateLayout();
}

void CustomBox::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    paintBackground(painter);
    paintBorder(painter);
}

void CustomBox::childEvent(QChildEvent *event) {
    QWidget::childEvent(event);

    if (event->type() == QEvent::ChildAdded) {
        if (auto *widget = qobject_cast<QWidget*>(event->child())) {
            if (indexOf(widget) == -1) addItem(widget);
        }
    }
}

void CustomBox::layoutItems() {
    if (m_items.isEmpty()) return;

    distributeSpace();
}

QRect CustomBox::calculateItemRect(int index, const QSize &itemSize) const {
    Q_UNUSED(index)
    Q_UNUSED(itemSize)

    return QRect();
}

void CustomBox::paintBackground(QPainter &painter) {
    Q_UNUSED(painter);
}

void CustomBox::paintBorder(QPainter &painter) {
    Q_UNUSED(painter);
}

void CustomBox::updateLayout() {
    if (!isVisible()) return;

    layoutItems();
    update();
    updateGeometry();
}

int CustomBox::getMainSize(const QSize &size) const {
    return isHorizontal() ? size.width() : size.height();
}
int CustomBox::getCrossSize(const QSize &size) const {
    return isHorizontal() ? size.height() : size.width();
}
QSize CustomBox::makeSize(int main, int cross) const {
    return isHorizontal()? QSize(main,cross) : QSize(cross,main);
}