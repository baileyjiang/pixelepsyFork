#include "buffer.h"

#include <algorithm>
#include <memory>
#include <vector>

#include <QColor>
#include <QImage>

Buffer::Buffer(int width, int height, QColor background)
{
    frames.push_back(std::make_shared<QImage>(width, height, QImage::Format_ARGB32));
    frames.back()->fill(background);

    frames.push_back(std::make_shared<QImage>(width, height, QImage::Format_ARGB32));
    frames.back()->fill(Qt::red);

    frames.push_back(std::make_shared<QImage>(width, height, QImage::Format_ARGB32));
    frames.back()->fill(Qt::blue);
}

Buffer::Buffer(std::vector<std::shared_ptr<QImage> > images) {
    this->frames = images;
}

std::vector<std::shared_ptr<QImage>> Buffer::fetchSnapshot()
{
    std::vector<std::shared_ptr<QImage>> snapshot;
    foreach (auto frame, frames) {
        snapshot.push_back(std::make_shared<QImage>(frame->copy()));
    }

    return snapshot;
}

std::shared_ptr<QImage> Buffer::fetchFrame(int index)
{
    // Guard against high numbers
    index = std::min(index, (int) frames.size() - 1);

    return frames.at(index);
}

void Buffer::insertFrame(int index)
{
    frames.insert(frames.begin() + index + 1,
                  std::make_shared<QImage>(*fetchFrame(index)));
}
void Buffer::insertFrame(QImage image) {
    frames.insert(frames.end() + 1,
                  std::make_shared<QImage>(image));
}

QString Buffer::toString() {
    std::stringstream stream;
    stream << this->fetchFrame(0)->height() << SPACE
           << this->fetchFrame(0)->width() << SPACE
           << NEWLINE;


    stream << this->getFrames().size() << NEWLINE;

    for (std::shared_ptr<QImage> frame : this->getFrames()) {
        QImage* image = frame.get();
        for (int i = 0; i < image->height(); i++) {
                for (int j = 0; j < image->width(); j++) {
                    QColor color = image->pixel(j, i);
                    stream << color.red() << SPACE
                           << color.green() << SPACE
                           << color.blue() << SPACE
                           << color.alpha() << SPACE;
                }
                stream << NEWLINE;
            }
    }


    return QString::fromStdString(stream.str());





}
void Buffer::deleteFrame(int index)
{
    if (frames.size() >= 2) {
        frames.erase(frames.begin() + index);
    }
}
std::vector<std::shared_ptr<QImage>> Buffer::getFrames() {
    return frames;
}
