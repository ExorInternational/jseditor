#pragma once

#include <QObject>
#include <QVariant>
#include <QString>
#include <QList>
#include <QMap>
#include <QVector>

class CStateObj : public QObject
{
	Q_OBJECT
public:
	CStateObj(QObject* obj=NULL);
	virtual ~CStateObj(){}
public:
	Q_INVOKABLE unsigned int getQualityBits()
	{ return m_nQualityBits; }
	Q_INVOKABLE qlonglong getTimestamp()
	{ return m_timeStamp; }
	Q_INVOKABLE bool isQualityGood()
	{ return m_bQuality; }
	Q_INVOKABLE QVariant getValue()
	{ return m_value; }

	void setQualityBits(unsigned int bits)
	{ m_nQualityBits = bits; }
	void setTimestamp(qlonglong timestamp)
	{ m_timeStamp = timestamp; }
	void setQuality(bool bQual)
	{ m_bQuality = bQual; }
	void setValue(const QVariant& value)
	{ m_value = value; }

protected:
	int m_nQualityBits;
	qlonglong m_timeStamp;
	bool m_bQuality;
	QVariant m_value;
};

class CGroupObj : public QObject
{
	Q_OBJECT
public:
	CGroupObj(QObject* obj=NULL){}
	virtual ~CGroupObj(){}
public:
	Q_INVOKABLE QVariant getTag(const QString& strTag);
	//{ return *m_tagMap.value(strTag); }
	Q_INVOKABLE QVariant getTags();
	Q_INVOKABLE QVariant getCount()
	{ return 32; }
protected:
	//CTagMapData m_tagMap;
};
class CJSTagObj : public QObject
{
public:
	Q_OBJECT

				// ------------ JavaScript interface -----------------------
public:	
	Q_PROPERTY(QVariant name READ getName WRITE setName)
	Q_PROPERTY(QVariant value READ getValue WRITE setValue)

public:
			// todo:  change to return a QVariant
	QVariant getValue()
		{ return m_strValue; }
	void setValue(const QVariant&  value)
		{ m_strValue = value.toString(); }
	void setName(const QVariant&  value)
		{ m_strName = value.toString(); }
	QVariant getName()
		{ return m_strName; }

protected:
	QString m_strValue;
	QString m_strName;
	QString m_strComent;
};

class CJSRecipeObj : public QObject
{
public:
	Q_OBJECT

				// ------------ JavaScript interface -----------------------
public:	
	Q_PROPERTY(QVariant name READ getName WRITE setName)
	Q_PROPERTY(int index READ getIndex WRITE setIndex)

public:

	void setName(const QVariant&  value)
		{ m_strName = value.toString(); }
	QVariant getName()
		{ return m_strName; }
	void setIndex(int index)
	{ m_nIndex = index; }
	int getIndex()
	{ return m_nIndex; }

protected:
	QString m_strName;
	int m_nIndex;
};
