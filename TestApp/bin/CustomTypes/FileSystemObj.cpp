
#include "FileSystemObj.h"

CFileSystemObj::CFileSystemObj(QObject *parent)
	: QObject(parent)
{

}

CFileSystemObj::~CFileSystemObj()
{

}

/*Removes directory at strPath if exists and empty*/
bool CFileSystemObj::rmdir(const QString& strPath)
{
	bool bRet = false;	
	return bRet;
}

/*Makes directory at strPath, all sub directories will also be made*/
bool CFileSystemObj::mkdir(const QString& strPath)
{
	bool bRet = false;
	return bRet;
}

QVariant CFileSystemObj::readdir(const QString& strPath)
{
	QStringList list;//empty list
	return list;
}

/*Removes the file at strPath if exists*/
bool CFileSystemObj::unlink(const QString& strFile)
{
	bool bRet = false;	
	return bRet;
}

/*Opens file in read mode and returns all data*/
QVariant CFileSystemObj::readFile(const QString& strFile, const QString& strFlag)
{
	QVariant retVal;
	return retVal;
}

/*Opens/Creates file in write mode and appends/replace the data wrt strFlag*/
int CFileSystemObj::writeFile(const QString& strFile, const QVariant& fileData, const QString& strFlag)
{
	int retVal = -1;	
	return retVal;
}

/*Returns true if a file or folder exists in file system at strPath*/
bool CFileSystemObj::exists(const QString& strPath)
{
	bool bRet = false;	
	return bRet;
}

/*if path is relative and not start with /, then prepend local path*/
QString CFileSystemObj::ResolvePath(const QString& strFilePath,bool isDir)
{
	QString strPath = strFilePath;	
	return strPath.replace("\\","/");//return UNIX style
}
