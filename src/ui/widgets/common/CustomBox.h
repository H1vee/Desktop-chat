//
// Created by shingesa on 29/07/25.
//
#pragma once

#ifndef CUSTOMBOX_H
#define CUSTOMBOX_H

#include <QWidget>
#include <QVector>

class CustomBox: public QWidget {
    Q_OBJECT
public:
    enum class Direction {
        Horizontal,
        Vertical
    };

    enum class Alignment {
        Start,
        Center,
        End,
        Stretch
    };

    explicit CustomBox(Direction direction = Direction::Vertical, QWidget *parent = nullptr);
    ~CustomBox() override;

    void addItem(QWidget *item, int stretch = 0);
    void insertItem(int index, QWidget *item, int stretch = 0);
    void removeItem(QWidget *item);
    void removeItem(int index);
    void clear();

    QWidget *itemAt(int index) const;
    int indexOf(QWidget *item) const;
    int count() const { return m_items.size(); }

    void setDirection(Direction direction);
    Direction direction()const {return m_direction; }

    void setAlignment(Alignment alignment);
    Alignment alignment()const {return m_alignment; }

    void setSpacing(int spacing);
    int spacing() const {return m_spacing; }

    void setContentsMargins(int left, int top, int right, int bottom);
    void setContentsMargins(const QMargins &margins);
    QMargins contentsMargins() const { return m_margins; }

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

Q_SIGNALS:
  void itemAdded(QWidget *item);
  void itemRemoved(QWidget *item);



protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void childEvent(QChildEvent *event) override;

    virtual void layoutItems();
    virtual QRect calculateItemRect(int index, const QSize &itemSize) const;
    virtual void paintBackground (QPainter &painter);
    virtual void paintBorder (QPainter &painter);

private:
  struct ItemInfo {
    QWidget *widget;
    int stretch;

    ItemInfo(QWidget *w = nullptr, int s = 0)
    : widget(w), stretch(s) {}
    };


    QVector<ItemInfo> m_items;
    Direction m_direction;
    Alignment m_alignment;
    int m_spacing;
    QMargins m_margins;


    void updateLayout();
    QSize calculateTotalSize() const;
    int calculateTotalStretch() const;
    void distributeSpace();

    bool isHorizontal() const {return m_direction == Direction::Horizontal; };
    int getMainSize(const QSize &size) const;
    int getCrossSize(const QSize &size) const;
    QSize makeSize(int main, int cross) const;

};



#endif //CUSTOMBOX_H
