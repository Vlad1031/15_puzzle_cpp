#ifndef BACKEND_H
#define BACKEND_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>
using namespace std;

class Backend : public QAbstractListModel
{
    Q_OBJECT
public:
    Backend(QObject* parent = nullptr);
    ~Backend();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    void Shuffle();
    bool BoardValid() const;
private:
    QList<int> m_board;
};

#endif // BACKEND_H
