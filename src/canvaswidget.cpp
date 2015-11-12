#include "canvaswidget.h"
#include <QPoint>
#include <QTextStream>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPixmap>
#include <Qt>
#include <QPointF>
#include <QPoint>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene)
    , layout(new QVBoxLayout)
    , frame(0)
    , scale(1)
{
    this->setScene(scene);
    this->setLayout(layout);

    this->setStyleSheet("background: grey;");
}


void CanvasWidget::showFrame(int frame) {
    this->frame = frame;

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(
                         *(this->buffer->fetchSnapshot().at(frame).get())));
}

void CanvasWidget::changeBuffer(std::shared_ptr<Buffer> buffer) {
    this->buffer = buffer;

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(
                         *(this->buffer->fetchSnapshot().front().get())));
}

void CanvasWidget::updateBuffer(std::shared_ptr<Buffer> buffer, int frame) {
    this->buffer = buffer;

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(
                         *(this->buffer->fetchSnapshot().at(frame).get())));
}


void CanvasWidget::mouseMoveEvent(QMouseEvent * event) {
    QPoint point = this->pixelLocation(event);

    if (checkPoint(point))
    {
        emit this->pointSelected(point, event->buttons() == Qt::LeftButton);
    }
}

void CanvasWidget::mousePressEvent(QMouseEvent * event) {
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent* event) {

}

QPoint CanvasWidget::pixelLocation(QMouseEvent * event) {
    QPointF point = this->mapToScene(event->pos());
    return point.toPoint();
}

bool CanvasWidget::checkPoint(QPoint point) {
    int x = point.x();
    int y = point.y();
    int width = this->buffer->fetchFrame(0)->width();
    int height = this->buffer->fetchFrame(0)->height();
    return ((x >= 0) && (y >= 0)) && ((x < width) && (y < height));
}

