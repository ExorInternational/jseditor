#include "JSObjects.h"

CStateObj::CStateObj(QObject* obj)
{
	m_nQualityBits = 0;
	m_timeStamp = 0;
	m_bQuality = false;
}
QVariant CGroupObj::getTag(const QString& strTag)
{ 
	QVariant val;
	return val;
}

QVariant CGroupObj::getTags()
{ 
	QVariant tagList ;
	return tagList;
}