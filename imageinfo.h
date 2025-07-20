#ifndef IMAGEINFO_H
#define IMAGEINFO_H
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Qstring>
#include <QImage>
#include "codingtext.h"

using namespace std;


class ImageInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int codingSymbols READ getCodingSymbols NOTIFY imageChanged)
    Q_PROPERTY(QString codingText READ getCodingText WRITE setCodingText NOTIFY codingTextChanged)
    Q_PROPERTY(int bits READ getBits WRITE setBits NOTIFY bitsChanged)
    Q_PROPERTY(QString imagePath READ getImagePath NOTIFY imageChanged)

signals:
    void imageChanged();
    void codingTextChanged();
    void bitsChanged();
    void codingFinished(bool finish);

public:
    explicit ImageInfo(QObject *parent = nullptr);

    int getCodingSymbols();
    QString getCodingText();
    int getBits();
    QString getImagePath();

    void setCodingText(const QString &text);
    void setBits(int bits);

    Q_INVOKABLE void setImage(QString filepath);

    Q_INVOKABLE bool codingAndSave(const QString& savePath);
    Q_INVOKABLE bool decodingAndDisplay();



private:
    QImage _image;
    int _availableSymbols = 0;
    CodingText _coder;
    QString _codingText;
    int _bits = 2;
    QString _imagePath;
};

#endif // IMAGEINFO_H
