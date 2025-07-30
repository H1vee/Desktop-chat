//
// Created by shingesa on 30/07/25.
//

#include "CustomButton.h"
#include <QPainter>
#include <QMouseEvent>
CustomButton::CustomButton(const QString &text, QWidget *parent)
    : QWidget(parent),
      m_text(text),
      m_font("Arial", 12),
      m_backgroundColor(Qt::lightGray),
      m_textColor(Qt::black),
      m_hoverColor(Qt::gray),
      m_pressedColor(Qt::darkGray),
      m_currentState(NORMAL),
      m_enabled(true),
      m_mousePressed(false)
{
    initializeDefaults();
    setMouseTracking(true);
}

CustomButton::CustomButton(const QString &text, const QColor &color, QWidget *parent)
: CustomButton(text, parent) {
    m_backgroundColor = color;
}

void CustomButton::initializeDefaults() {
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void CustomButton::setText(const QString &text) {
    if (m_text != text) {
        m_text = text;
        update();
    }
}

void CustomButton::setBackgroundColor(const QColor &color) {
    m_backgroundColor = color;
    update();
}

void CustomButton::setTextColor(const QColor &color) {
    m_textColor = color;
    update();
}

void CustomButton::setHoverColor(const QColor &color) {
    m_hoverColor = color;
    update();
}

void CustomButton::setPressedColor(const QColor &color) {
    m_pressedColor = color;
    update();
}

void CustomButton::setFont(const QFont &font) {
    m_font = font;
    update();
}

void CustomButton::setEnabled(bool enabled) {
    if (m_enabled != enabled) {
        m_enabled = enabled;
        m_currentState = enabled ? NORMAL : DISABLED;
        update();
    }
}

QSize CustomButton::sizeHint() const {
    QFontMetrics fm(m_font);
    QSize size = fm.size(Qt::TextSingleLine, m_text);
    return size+QSize(20, 10);
}

QSize CustomButton::minimumSizeHint() const {
    return sizeHint();
}
void CustomButton::mousePressEvent(QMouseEvent *event) {
    if (m_enabled && event->button() == Qt::LeftButton) {
        m_mousePressed = true;
        m_currentState = PRESSED;
        update();
        Q_EMIT pressed();
    }
}

void CustomButton::mouseReleaseEvent(QMouseEvent *event) {
    if (m_enabled && event->button() == Qt::LeftButton) {
        if (rect().contains(event->pos())) {
            Q_EMIT clicked();
        }
        m_mousePressed = false;
        m_currentState = rect().contains(event->pos()) ? HOVERED : NORMAL;
        update();
        Q_EMIT released();
    }
}

void CustomButton::enterEvent(QEnterEvent *event) {
    Q_UNUSED(event);
    if (m_enabled && m_mousePressed) {
        m_currentState = HOVERED;
        update();
    }
}

void CustomButton::leaveEvent(QEvent *event) {
    Q_UNUSED(event);
    if (m_enabled && m_mousePressed) {
        m_currentState = NORMAL;
        update();
    }
}

QColor CustomButton::getCurrentBackgroundColor() const {
    switch (m_currentState) {
        case NORMAL: return m_backgroundColor;
        case HOVERED: return m_hoverColor;
        case PRESSED: return m_pressedColor;
        case DISABLED: return QColor(200, 200, 200);
    }
    return m_backgroundColor;
}

void CustomButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(getCurrentBackgroundColor());
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    painter.setFont(m_font);
    painter.setPen(m_textColor);
    painter.drawText(rect(), Qt::AlignCenter, m_text);
}