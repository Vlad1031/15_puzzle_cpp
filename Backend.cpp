#include "Backend.h"
#include <algorithm>
#include <random>

Backend::Backend(QObject *parent) : QAbstractListModel (parent)
{
    for(int i = 0; i < 16; i++){
        m_board.push_back(i + 1);
    }
    Shuffle();
}

Backend::~Backend() { }

void Backend::Shuffle()
{
    auto seet = chrono::system_clock::now().time_since_epoch().count();
    static mt19937 generator(seet);

    do{
        shuffle(m_board.begin(), m_board.end(), generator);
    } while(!BoardValid());
}

bool Backend::BoardValid() const
{
    size_t count = 0;
    for(size_t i = 0; i < 16; i++){
        for(size_t j = 0; j < i; j++){
            if(m_board[j] > m_board[i]){
                count++;
            }
        }
    }
    return count % 2 == 0;
}


int Backend::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_board.count();
}

QVariant Backend::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_board.count()){
        return QVariant();
    }

    switch (role) {
        case Qt::DisplayRole:
        return m_board.value(index.row());
    }
    return QVariant();
}
