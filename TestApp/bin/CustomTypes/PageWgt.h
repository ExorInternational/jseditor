
// PageWgt.h: interface for the CPageWgt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAGEWGT_H__8CB2C6E0_7707_4295_A15C_6E49EE9ED2E4__INCLUDED_)
#define AFX_PAGEWGT_H__8CB2C6E0_7707_4295_A15C_6E49EE9ED2E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Widget.h"
#include <QScriptValue>
#include <QScriptEngine>
#include <QElapsedTimer>
#include <QMutex>


class IPageListener;
class CData;
class CPageMgrWgt;
class CScript;
class CProjectWgt;
class CHMICmd;
class CWEventData;
class CTemplatePageWgt;
class CQPageWgt;
class QGraphicsItem;
class CMLTextMgrWgt;
class QScriptEngine;

#ifdef _DXWIDGET
class CHMIViewerWnd;
#endif

#define PAGE_STARTING_ZORDER	10000

enum {
	kPlayMode,
	kEditMode,
	kLadderMode,
	kPrintMode
};

enum {
	kNormalPage         = 0x00000001,
	kDialogPage         = 0x00000002,
	kProjectPage        = 0x00000004,
	kGalleryPage        = 0x00000008,
	kGalleryDataPage    = 0x00000010,
	kSystemPage         = 0x00000020,
	kServerPage         = 0x00000040,
	kTemplatePage       = 0x00000080,
	kKeypadPage         = 0x00000100,
	// @M31
	kReportPage         = 0x00000200,
	kReportTemplatePage = 0x00000400,
	// ---
	kMobilePage         = 0x00000800,
	kMobileTemplatePage = 0x00001000,
	kMobileDialogPage   = 0x00002000,
	kWidgetPage         = 0x00004000,

	kHMIPages           = kNormalPage | kDialogPage | kTemplatePage | kMobilePage | kMobileDialogPage | kMobileTemplatePage,

	kAnyPage            = 0xffffffff
};

enum {
	kPageExportNone,
	kPageExportWeb             = 0x0001,
	kPageExportMobile          = 0x0002,
	kPageExportTablet          = 0x0004,
	kPageExportCloud           = 0x0008,
	kPageExportWebStartPage   = 0x0100,
	kPageExportMobileStartPage = 0x0200,
	kPageExportTabletStartPage = 0x0400,
	kPageExportCloudStartPage  = 0x0800,

	kPageExportAll			= kPageExportWeb | kPageExportMobile | kPageExportTablet | kPageExportCloud,
	kPageExportStartPageAll	= kPageExportWebStartPage | kPageExportMobileStartPage | kPageExportTabletStartPage | kPageExportCloudStartPage
};

enum {
	kPageDataJMX,
	kPageDataSVG
};
class CPageModel;
class CPageWgt;

class CPageWgt : public CWidget 
{
	Q_OBJECT		// needed to support javascript

public:


public:
	CPageWgt();
	virtual ~CPageWgt();
	void SetScriptData(QString &strData)
	{ m_strScriptData = strData;}
	QString GetScriptData()
	{ return m_strScriptData;}
	bool HasScriptData()
	{ return !m_strScriptData.isEmpty();}

	QString m_strFileName;
	int m_mode;
	bool m_bDirty; 
	QString m_strTempColor;
	int m_nPageType;
	QString m_strPageName;
	QString m_strSVGFileName;
	CWidget* m_pEditWgt;
	QString m_strScriptFileName;
	QString m_strScriptData;
	QString m_strTemplateFile;
	QString m_strImagesPath;		// defines dir of images if not the standard "images/"
	QString m_strStaticFileType;

	bool m_bActivated;
	float m_fZoomScale;
	bool m_bPrecacheEnabled;  
	QMutex m_lock;  
	bool m_bJSDebugEnable;
	bool m_bKeyMacrosEnable;
	QHash<int, CWidget*> m_pageKeys;

	bool m_bFirst; // is true when page is activated first time.
	bool m_bShowToolbar;
	bool m_bDownloadDone;
	bool m_bBlinkState;
	CTemplatePageWgt *m_pTemplatePage;
	//#1785
	CMLTextMgrWgt* m_pPageMLMgr;
	long m_exportFlags;

	//speed up initial updates
	QVector<CDataLink*> m_vWidgetLinks;
	QVector<CLink*> m_vMultiLangLinks;
	QVector<CWidget*> m_vInitList;

#ifdef _DXWIDGET
	CHMIViewerWnd* m_pWnd;
#endif
	// ------------ JavaScript interface -----------------------

public:	// these functions can be accessed from ascript
	Q_INVOKABLE QObject* getWidget(const QString& wgtName){return NULL;};
	Q_INVOKABLE QObject* getProject(){return NULL;};
	//Q_INVOKABLE int setTimeout(QScriptValue function, int delay);
	Q_INVOKABLE void clearTimeout(int timerID){return ;};
	//Q_INVOKABLE int setInterval(QScriptValue function, int interval);
	Q_INVOKABLE void clearInterval(int intervalID){return ;};
	Q_INVOKABLE void clearAllTimeouts(){return ;};
	Q_INVOKABLE void beginDataEntry(const QString& widgetName){return ;};

	Q_PROPERTY(QVariant backgroundColor READ getBackgroundColor WRITE setBackgroundColor);

	// Returns a map "x", "y", "pressed"
	Q_PROPERTY(QVariantMap primaryTouch READ primaryTouch);


protected:
	QVariant getBackgroundColor(){QVariant var;return var;};
	void setBackgroundColor(const QVariant& color){return ;};

	QVariantMap primaryTouch(){QVariantMap var;return var;};


};

#endif 
