#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <vector>

#include <QColor>
#include <QImage>
#include <sstream>
#define SPACE " "
#define NEWLINE '\n'

class Buffer
{
        std::vector<std::shared_ptr<QImage>> frames;

    public:
        Buffer(int width, int height, QColor background);

        std::vector<std::shared_ptr<QImage>> fetchSnapshot();

        std::shared_ptr<QImage> fetchFrame(int index);

        QString toString();

        void insertFrame(int index);
        void insertFrame(QImage);
        void deleteFrame(int index);
        std::vector<std::shared_ptr<QImage>> getFrames();
};

#endif // BUFFER_H
