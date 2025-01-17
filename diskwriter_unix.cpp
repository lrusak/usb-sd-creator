////////////////////////////////////////////////////////////////////////////////
//      This file is part of LibreELEC - http://www.libreelec.tv
//      Copyright (C) 2013-2015 RasPlex project
//      Copyright (C) 2016 Team LibreELEC
//
//  LibreELEC is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 2 of the License, or
//  (at your option) any later version.
//
//  LibreELEC is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with LibreELEC.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////

#include "diskwriter_unix.h"

#include <QDebug>
#include <unistd.h>

#ifdef Q_OS_MAC
#include <QProcess>
#endif


DiskWriter_unix::DiskWriter_unix(QObject *parent) :
    DiskWriter(parent)
{
    isCancelled = false;
}

DiskWriter_unix::~DiskWriter_unix()
{
    if (isOpen())
        close();
}

bool DiskWriter_unix::open(const QString& device)
{
    dev.setFileName(device);
#ifdef Q_OS_MAC
    // write to RAW device, this is MUCH faster
    QString rawdev(device);
    rawdev.replace(QString("/dev/"),QString("/dev/r"));

    // unmount the device
    QProcess unmount;
    unmount.start("diskutil", {"unmountDisk", rawdev}, QIODevice::ReadOnly);
    unmount.waitForStarted();
    unmount.waitForFinished();
    dev.setFileName(rawdev);
#endif

    return dev.open(QFile::WriteOnly);
}

void DiskWriter_unix::close()
{
    dev.close();
}

void DiskWriter_unix::sync()
{
    if (this->isOpen())
        fsync(dev.handle());
}

bool DiskWriter_unix::isOpen()
{
    return dev.isOpen();
}

bool DiskWriter_unix::write(const QByteArray &data)
{
    return dev.write(data);
}

