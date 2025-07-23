#include "decodingtext.h"
#include <qbitarray.h>

DecodingText::DecodingText(QObject *parent)
    : QObject{parent}
{}

QBitArray DecodingText::getImageBits(int index, QImage& image, int bitsPerChannel)
{

    int pixelIndex = index / 3;

    int x = pixelIndex % image.width();
    int y = pixelIndex / image.width();

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

    auto t1 = getImageBits(1, img, 2);
    auto t2 = getImageBits(0, img, 2);
    t1.resize(4);
    t1.setBit(2, t2.at(1));
    t1.setBit(3, t2.at(0));

    int param = t1.toUInt32(QSysInfo::LittleEndian);
    qDebug() << "Decoded param: " << param;

    qDebug() << "Text length";

    QBitArray lengthBits(24);
    for (int i = 0; i < 24/2; ++i) {
        QBitArray ar = getImageBits(2 + i, img, 2);
        lengthBits.setBit(2*i + 1, ar.at(0));
        lengthBits.setBit(2*i, ar.at(1));
    }

    QString lengthBitsStr;
    for (int i = 0; i < lengthBits.size(); ++i) {
        lengthBitsStr.append(lengthBits.testBit(i) ? '1' : '0');
    }
    qDebug() << "Extracted message length bits: " << lengthBitsStr;

    int messageBitLength = 0;
    for (int i = 0; i < 24; ++i) {
        messageBitLength |= (lengthBits.testBit(i) ? 1 : 0) << (23 - i);
    }

    qDebug() << "Decoded message bit length: " << messageBitLength;
    int maxTextLength = messageBitLength;

    QBitArray textBits(maxTextLength);
    int startIndex = 14;
    int groupCount = (maxTextLength + param - 1) / param;

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
            if (bitIndex >= maxTextLength) break;

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

    /*int nullCharIndex = decodedText.indexOf('\0');
    if (nullCharIndex != -1) {
        decodedText = decodedText.left(nullCharIndex);
    }*/

    qDebug() << "Decoded Text: " << decodedText;

    return decodedText;
}
