//
// Created by shingesa on 30/07/25.
//
#pragma once

#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QString>
#include <QColor>
#include <QFont>

class CustomButton : public QWidget{
    Q_OBJECT

public:

    enum State {
        NORMAL,
        HOVERED,
        PRESSED,
        DISABLED
    };

    explicit CustomButton(const QString &text ="",QWidget *parent = nullptr);
    explicit CustomButton(const QString &text ="",const QColor &color,QWidget *parent = nullptr);

    void setText(const QString &text);
    [[nodiscard]] QString text()const { return m_text; }
    void setBackgroundColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setHoverColor(const QColor &color);
    void setPressedColor(const QColor &color);

    void setFont(const QFont &font);
    [[nodiscard]] QFont font() const {return m_font; };

    void setEnabled(bool enabled);
    [[nodiscard]]  bool isEnabled() const {return m_enabled; };

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

Q_SIGNALS:
void clicked();
void pressed();
void released();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
private:
    QString m_text;
    QFont m_font;


    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_hoverColor;
    QColor m_pressedColor;


    State m_currentState;
    bool m_enabled;
    bool m_mousePressed;

    void initializeDefaults();
    QColor getCurrentBackgroundColor() const;
    void updateState();
};



#endif //CUSTOMBUTTON_H
