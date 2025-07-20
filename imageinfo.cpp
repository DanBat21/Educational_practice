#include "imageinfo.h"
#include "codingtext.h"
#include "decodingtext.h"



ImageInfo::ImageInfo(QObject *parent)
    : QObject{parent}
{}

int ImageInfo::getCodingSymbols()
{
    return _availableSymbols;
}

QString ImageInfo::getCodingText() { return _codingText; }
int ImageInfo::getBits() { return _bits; }
QString ImageInfo::getImagePath() { return _imagePath; }

void ImageInfo::setCodingText(const QString &text) {

        _codingText = text;
        emit codingTextChanged();
}

void ImageInfo::setBits(int bits) {

        _bits = bits;
        emit bitsChanged();

}

bool ImageInfo::codingAndSave(const QString &savePath) {
    if(_codingText.isEmpty() || _image.isNull()) {
         qDebug() << "Empty text or null image";
        return false;
    }
    QImage encoded = _coder.coding(_codingText, _image, _bits);
    if(encoded.isNull()) {
        qDebug() << "Encoding failed";
        return false;
    }

    QString localPath = QUrl(savePath).toLocalFile();

    bool finish = encoded.save(QUrl(savePath).toLocalFile());
    emit codingFinished(finish);
    return finish;
}

bool ImageInfo::decodingAndDisplay() {
    setCodingText("");

    if (_image.isNull()) {
        qDebug() << "No image loaded for decoding";
        return false;
    }

    DecodingText decoder;

    QString decodedText = decoder.decoding(_image);

    setCodingText(decodedText);
    //_codingText = decodedText;
    //emit codingTextChanged();

    qDebug() << "Decoded Text: " << decodedText;

    return true;
}

Q_INVOKABLE void ImageInfo::setImage(QString filepath)
{
    _image.load(QUrl(filepath).toLocalFile());
    int width = _image.width();
    int height = _image.height();
    int total = width * height * 4;
    int available = total * 2;
    _availableSymbols = available / 8;
    emit imageChanged();
}
