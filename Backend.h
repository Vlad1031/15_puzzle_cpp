#ifndef BACKEND_H
#define BACKEND_H

#include <QAbstractListModel>
#include <QList>
using namespace std;

class Backend : public QAbstractListModel
{
    Q_OBJECT
public:
    Backend(QObject* parent = nullptr);
    ~Backend();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void shaffle();
    Q_INVOKABLE bool BoardValid() const;
    int FindZero() const;
    Q_INVOKABLE bool neighboring(int index, int idx);
    Q_INVOKABLE bool move(int index);
    Q_INVOKABLE bool popup();

    bool PositionValid(const size_t position) const;
private:
    QList<int> m_board;
};

#endif // BACKEND_H
