#ifndef CAPTIONHOLDER_H
#define CAPTIONHOLDER_H

#include <QObject>

class CaptionHolder {
public:
    explicit CaptionHolder(QString caption)
    {
        this->_caption = caption;
    }

    const QString caption() const
    {
        return _caption;
    }

    bool operator== (const CaptionHolder &source) const
    {
        return _caption == source.caption();
    }

    bool operator!= (const CaptionHolder &source) const
    {
        return !(_caption == source.caption());
    }

    bool operator<(const CaptionHolder &other) const {
        return std::tie(caption()) < std::tie(other.caption());
    }

//    inline uint qHash(const CaptionHolder &key)
//    {
//        return key.caption().toUInt();
//    }

protected:
    void setCaption(const QString caption)
    {
        _caption = caption;
    }

private:
    QString _caption;
};

#endif // CAPTIONHOLDER_H
