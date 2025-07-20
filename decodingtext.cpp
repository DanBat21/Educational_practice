#include "decodingtext.h"
#include <qbitarray.h>

DecodingText::DecodingText(QObject *parent)
    : QObject{parent}
{}

QBitArray DecodingText::getImageBits(int index, QImage& image, int bitsPerChannel)
{

    int x = index % image.width();
    int y = index / image.width();

    QColor color = image.pixelColor(x, y);
    qDebug() << "Извлечение битов из пикселя (" << x << "," << y << ")";
    qDebug() << "Цвет: " << color;

    QBitArray bits(bitsPerChannel);

    int value = 0;
    if (index % 3 == 0) {
        value = color.red();
        qDebug() << "R channel value: " << value;
    } else if (index % 3 == 1) {
        value = color.green();
        qDebug() << "G channel value: " << value;
    } else {
        value = color.blue();
        qDebug() << "B channel value: " << value;
    }

    for (int i = 0; i < bitsPerChannel; ++i) {
        bool bit = (value >> (bitsPerChannel - i - 1)) & 1;
        qDebug() << "Bit " << i << ": " << bit;
        bits.setBit(i, bit);
    }

    return bits;
}


QString DecodingText::decoding(QImage img)
{
    qDebug() << "Image: " << img.width() << ", " << img.height();
    qDebug() << "Param:";

    //Беру 4 бита для param R и G
    auto t1 = getImageBits(0, img, 2);  // 2 бита из R
    auto t2 = getImageBits(1, img, 2);  // 2 бита G
    t1.resize(4);
    t1.setBit(2, t2.at(0));
    t1.setBit(3, t2.at(1));

    int param = t1.toUInt32(QSysInfo::LittleEndian);
    qDebug() << "Decoded param: " << param;

    qDebug() << "Text length";

    // Беру 24 бита для length
    auto b1 = getImageBits(2, img, 2);
    auto b2 = getImageBits(3, img, 2);
    b1.resize(4);
    b1.setBit(2, b2.at(0));
    b1.setBit(3, b2.at(1));

    int messageBitLength = b1.toUInt32(QSysInfo::LittleEndian);
    qDebug() << "Decoded message length: " << messageBitLength;

    QBitArray textBits(messageBitLength);
    int startIndex = 14;
    int groupCount = (messageBitLength + param - 1) / param;

    for (int i = 0; i < groupCount; i++) {
        int channelIndex = startIndex + i;
        int pixelIndex = channelIndex / 3;
        int channel = channelIndex % 3;
        int x = pixelIndex % img.width();
        int y = pixelIndex / img.width();

        QColor color = img.pixelColor(x, y);
        int value = (channel == 0) ? color.red()
                    : (channel == 1) ? color.green()
                                     : color.blue();

        for (int b = 0; b < param; b++) {
            int bitIndex = i * param + b;
            if (bitIndex >= messageBitLength) break;

            bool bit = (value >> b) & 1;
            textBits.setBit(bitIndex, bit);
        }
    }

    QByteArray byteArray((textBits.size() + 7) / 8, 0);
    for (int i = 0; i < textBits.size(); i++) {
        if (textBits.testBit(i))
            byteArray[i / 8] |= (1 << (7 - (i % 8)));
    }

    QString decodedText = QString::fromUtf8(byteArray);
    return decodedText;
}



