#include "encodertext.h"
#include <QDebug>

EncoderText::EncoderText(QObject *parent)
    : QObject{parent}
{}

void EncoderText::writeChanel(int index, QBitArray bitsToWrite, QImage& image)
{
    int pixelIndex = index / 3;
    int channel = index % 3;

    int width = image.width();
    int x = pixelIndex % width;
    int y = pixelIndex / width;

    if (x >= width || y >= image.height())
        return;

    QColor color = image.pixelColor(x, y);

    qDebug() << "Before encoding: Pixel(" << x << "," << y << ")"
             << "Channel:" << channel
             << "R:" << color.red() << "G:" << color.green() << "B:" << color.blue();

    int channelValue;
    if (channel == 0)
        channelValue = color.red();
    else if (channel == 1)
        channelValue = color.green();
    else
        channelValue = color.blue();

    qDebug() << "Channel Value to write: " << channelValue;

    int newBits = 0;
    int weight = 1;
    for (int i = 0; i < bitsToWrite.size(); i++) {
        if (bitsToWrite.testBit(i)) {
            newBits = newBits + weight;
        }
        weight = weight * 2;
    }

    int clearValue = (channelValue / weight) * weight;
    int result = clearValue + newBits;

    if (channel == 0)
        color.setRed(result);
    else if (channel == 1)
        color.setGreen(result);
    else if (channel == 2)
        color.setBlue(result);

    qDebug() << "After encoding: Pixel(" << x << "," << y << ")"
             << "New Color - R:" << color.red() << "G:" << color.green() << "B:" << color.blue();

    image.setPixelColor(x, y, color);
}


QImage EncoderText::coding(QString text, QImage image, int param)
{
    QImage encodedImage = image.convertToFormat(QImage::Format_RGB32);

    QByteArray byteArr = text.toUtf8();
    //byteArr.append('\0');

    QBitArray bits(byteArr.size() * 8);
    for (int i = 0; i < byteArr.size(); i++) {
        for (int b = 0; b < 8; b++) {
            bits.setBit(i * 8 + b, byteArr[i] & (1 << (7 - b)));
        }
    }

    QBitArray headerBits(28);

    for (int i = 0; i < 4; i++) {
        bool bit = (param >> (3 - i)) & 1;
        headerBits.setBit(i, bit);
    }

    int messageBitLength = bits.size();
    for (int i = 0; i < 24; i++) {
        bool bit = (messageBitLength >> (23 - i)) & 1;
        headerBits.setBit(4 + i, bit);
    }

    qDebug() << "Message Length: " << messageBitLength;


    int headerParam = 2;
    int headerGroups = headerBits.size() / headerParam;
    for (int i = 0; i < headerGroups; i++) {
        QBitArray slice(headerParam);
        for (int j = 0; j < headerParam; j++) {
            int indx = i * headerParam + j;
            slice.setBit(j, headerBits.testBit(indx));
        }

        QString bitStr;
        for (int b = 0; b < slice.size(); b++) {
            bitStr.append(slice.testBit(b) ? '1' : '0');
        }
        qDebug() << "Header Group" << i << ":" << bitStr;

        writeChanel(i, slice, encodedImage);
    }


    QString fullBitStr;
    for (int i = 0; i < bits.size(); i++) {
        fullBitStr.append(bits.testBit(i) ? '1' : '0');
    }
    qDebug() << "Full bit array (" << bits.size() << " bits):" << fullBitStr;

    int bitGroups = bits.size() / param;
    if (bits.size() % param != 0)
        ++bitGroups;

    for (int i = 0; i < bitGroups; i++) {
        QBitArray slice(param);
        for (int j = 0; j < param; j++) {
            int ind = i * param + j;
            if (ind < bits.size())
                slice.setBit(j, bits.testBit(ind));
            else
                slice.setBit(j, false);
        }

        QString bitStr;
        for (int b = 0; b < slice.size(); b++) {
            bitStr.append(slice.testBit(b) ? '1' : '0');
        }
        qDebug() << "Data Group" << i << ":" << bitStr;

        writeChanel(14 + i, slice, encodedImage);
    }

    return encodedImage;
}

