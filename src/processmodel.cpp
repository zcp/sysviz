#include <QDebug>

#include "processmodel.h"
#include "slice.h"

ProcessModel::ProcessModel(QObject *parent, qlonglong pid)
    : QAbstractListModel(parent)
    , m_pid(pid)
{
}

int ProcessModel::rowCount(const QModelIndex &parent) const
{
    return m_threads.count();
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(index.row() >= 0 && index.row() < m_threads.count());
    switch (role)
    {
        case ProcessModel::ThreadModelRole:
            return QVariant::fromValue(m_threads.at(index.row()));
    }

    Q_UNREACHABLE();
    return QVariant();
}

QHash<int, QByteArray> ProcessModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ProcessModel::ThreadModelRole] = "threadModel";
    return roles;
}

void ProcessModel::ensureThread(const QString &threadName)
{
    for (int i = 0; i < m_threads.count(); ++i) {
        if (m_threads.at(i)->threadName() == threadName)
            return;
    }

    qDebug() << "Creating thread model for " << threadName << " on pid " << m_pid;
    m_threads.append(new ThreadModel(this, threadName));
}

