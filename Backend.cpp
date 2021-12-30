#include "Backend.h"
#include <random>
#include <QDebug>

const int MAX_SIZE = 16;
Backend::Backend(QObject *parent) : QAbstractListModel (parent)
{
    for(int i = 1; i <= MAX_SIZE; i++){
        m_board.push_back(i);
    }
    shaffle();
}

Backend::~Backend() { }

void Backend::shaffle()
{
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937 generator(seed);

    do{
        shuffle(m_board.begin(), m_board.end(), generator);
        emit dataChanged(createIndex(0, 0), createIndex(15, 0));
    } while(!BoardValid());
    qDebug() << "shaffle:" << m_board;
}

bool Backend::BoardValid() const
{
    int k = 0;
    for(int i = 0; i < MAX_SIZE; i++){
        if(m_board[i] != MAX_SIZE){
            for(int j = i + 1; j < MAX_SIZE; j++){
                if(m_board[j] != MAX_SIZE){
                    if(m_board[i] > m_board[j]){
                        k++;
                    }
                }
            }
        }
    }

    int number_zero = (FindZero() / 4) + 1;
    int N = k + number_zero;
    return N % 2 == 0;
}

int Backend::FindZero() const{
    for(int i = 0; i < MAX_SIZE; i++){
        if(m_board[i] == MAX_SIZE){
            return i;
        }
    }
}

bool Backend::neighboring(int from, int to){
    if(from % 4 < 3 && from + 1 == to)
        return true;
    if(from % 4 > 0 && from - 1 == to)
        return true;
    if(from < 12 && from + 4 == to)
        return true;
    if(from >= 4 && from - 4 == to)
        return true;
    return false;
}

bool Backend::move(int from){
    int to = 0;
    while (m_board[to] != MAX_SIZE){
        to++;
    }

    if(neighboring(from, to)){
        m_board.move(from, to);
        if(from > to){
            beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);
            endMoveRows();
            if(to < from && to < from - 1){
                beginMoveRows(QModelIndex(), to + 1, to + 1, QModelIndex(), from + 1);
                endMoveRows();
            }
            m_board.move(to + 1, from);
        }

        else{
            beginMoveRows(QModelIndex(), from, from, QModelIndex(), to + 1);
            endMoveRows();
            if(to > from && to > from + 1){
                beginMoveRows(QModelIndex(), to - 1, to - 1, QModelIndex(), from);
                endMoveRows();
            }
            m_board.move(to - 1, from);
        }
        return true;
    }
    else {
        return false;
    }
}

bool Backend::win(){
    for(int i = 0; i < MAX_SIZE - 1; i++){
        if(m_board[i] != i + 1){
            return false;
        }
    }
    return true;
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
