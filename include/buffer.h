#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <vector>

#include <QColor>
#include <QImage>

class Buffer
{
        std::vector<std::shared_ptr<QImage>> frames;

    public:
        Buffer(int width, int height, QColor background);

        std::vector<std::shared_ptr<QImage>> fetchSnapshot();

        std::shared_ptr<QImage> fetchFrame(int index);

        void insertFrame(int index);
        void deleteFrame(int index);
};

#endif // BUFFER_H
