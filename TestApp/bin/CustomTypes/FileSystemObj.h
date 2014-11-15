#ifndef FILESYSTEMOBJ_H
#define FILESYSTEMOBJ_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QStringList>

class CFileSystemObj : public QObject
{
	Q_OBJECT

public:
	CFileSystemObj(QObject *parent=NULL);
	~CFileSystemObj();

protected:
	QString ResolvePath(const QString& strFilePath,bool isDir=false);

public:
	//opertaions on dir
	Q_INVOKABLE bool rmdir(const QString& strPath);
	Q_INVOKABLE bool mkdir(const QString& strPath);
	Q_INVOKABLE QVariant readdir(const QString& strPath);

	//operations on file
	Q_INVOKABLE bool unlink(const QString& strFile);
	Q_INVOKABLE QVariant readFile(const QString& strFile, const QString& strFlag="");
	Q_INVOKABLE int writeFile(const QString& strFile, const QVariant& fileData, const QString& strFlag="a");

	//opertaions on both
	Q_INVOKABLE bool exists(const QString& strPath); 
	
};

#endif // FILESYSTEMOBJ_H
