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

void Buffer::deleteFrame(int index)
{
    if (frames.size() >= 2) {
        frames.erase(frames.begin() + index);
    }
}
