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
    } while(!BoardValid());
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

bool Backend::neighboring(int index, int idx){
    if(index % 4 < 3 && index + 1 == idx)
        return true;
    if(index % 4 > 0 && index - 1 == idx)
        return true;
    if(index < 12 && index + 4 == idx)
        return true;
    if(index >= 4 && index - 4 == idx)
        return true;
    return false;
}

bool Backend::move(int index){
    int idx = 0;
    while (m_board[idx] != MAX_SIZE) {
        idx++;
    }

    if(neighboring(index, idx)){
        m_board.move(idx, index);
        m_board.move(index, idx);
        return true;
    }
    else{
        return false;
    }
}

bool Backend::popup(){
    for(int i = 0; i < 15; i++){
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
