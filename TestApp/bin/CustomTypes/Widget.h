// Widget.h: interface for the CWidget class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIDGET_H__EBA9EF85_3799_47F8_A3C8_C0B5BFD2E196__INCLUDED_)
#define AFX_WIDGET_H__EBA9EF85_3799_47F8_A3C8_C0B5BFD2E196__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SINGLE_INITSTART
#include <QScriptable>
#include <QObject>
#include <QVariant>
#include <QString>
#include <QSet>
#include <QMap>
#include <QVector>

class IDataListener;
class IMouseListener;
class IClickListener;
class IUpdateListener;
	
class CDataLink;
class CWEventData;
class CLink;
class CAction;
class CActionLink;
class CAttrLink;
class CWgtEditEditor;
class ICUEvent;
class CQHMIWidget;
class CWgtModel;
class IQHMIWidget;

struct sMessageEvent;

enum {
	E_CONSUMPTIONMETER  = 0x0001,
	E_MEDIAPLAYER = 0x0002, // StudioAbout and HMIAbout
	E_WEATHERWGT = 0x0004,
	E_WEBBROWSER = 0x0008,
	E_HYPERLINK = 0x0010,
	E_SCREENSAVER = 0x0020,
	E_ATTACHTOALARMTRIGGER = 0x0040,
	E_TRENDBACKGROUNDCOLOR  = 0x0080,
	E_REPLACEMEDIA = 0x0100,
	E_HMILICENSEING = 0x0200,
	E_JM4W =  0x0400, // StudioAbout
	E_OLD_TAGIMPORT =  0x0800,
	E_EXT_KEY_BOARD_MACROS = 0x00002000,
	E_EXPAND_ONLY_1_ROW_N_KEYEDIT = 0x00004000,
	E_LMX = 0x00008000,
	E_LMX_CLIENT = 0x00010000,
	E_PDF = 0x00020000,
	E_VNC = 0x00040000,
	E_BACNET_ACTIONS = 0x00100000,
	E_MOVECAMERA_ACTION = 0x00200000,
	E_VPN = 0x00400000,
	E_CMD_LINE = 0x00800000,
	E_DT_ONINIT_GLOBAL_FLAG = 0x01000000, // show data transfer on init golbal switch

	E_TREND_OUT_OF_RANGE_DOTS = 0x02000000,
	E_WARNING_ON_COPY_TO_ANOTHER_PAGE = 0x04000000,
	E_HIDE_REMOTE_JS_DEBUGGER = 0x08000000,//Hide Remote JS Debugger in studio
	E_HIDE_DEV_TOOLS = 0x10000000, //Developer Tools - HIDE on Studio
	E_HIDE_FREE_TYPE_FONT = 0x20000000,//Free Type Font Engine - HIDE on Studio
	E_HIDE_SCATTER_DGRM = 0x40000000,//Scatter Diagram wgt - REMOVE widget and related
	E_HIDE_PLC_ENCODE_COL = 0x80000000,//Custom Encoding From String From PLC		
};
const unsigned long long E_HIDE_BACKUP_RESTORE = 0x100000000;//Backup\Restore on context menu - HIDE on Runtime..	
const unsigned long long E_HIDE_BUZZER = 0x200000000;//HIDE buzzer.

	// widget styles
enum {
	WS_ISMGRWGT = 0x0001,
	WS_ISSVGWGT = 0x0002, //depricated
	WS_ISDATAWGT = 0x0004,
	WS_ISPAGEWGT = 0x0008,
	WS_ISPROJECTWGT = 0x0010,
	WS_HASVIEWER = 0x0020, //depricated
	WS_USEREDITABLE = 0x0040, // This widget can be edited by user except when kWgtAuthReadOnly security mode is used)
	WS_CLICKEDIT = 0x0080,
	WS_DBLCLICKEDIT=0x0100, //not used
	WS_ISDATASOURCE = 0x0200,
	WS_HASGROUPTAGS = 0x0400,
	WS_ISCONTAINER = 0x0800,
	WS_ISGROUP = 0x00001000,
	WS_ISWRITABLE  = 0x00002000, // This widget can be attached to a tag
	WS_HMIWEBSUPPORT  = 0x00004000,
//	WS_XYPARAMS = 0x00008000,
	WS_SIZETOFIT = 0x00010000,
	WS_ISSERVERWGT = 0x00020000, //depricated
	WS_ISNOTDELETABLEWGT=0x00040000,
	WS_SHOWCHILDDATAWGT = 0x00080000,
	WS_HASCUSTOMPROPS = 0x00100000,
	WS_ISCUSTOM = 0x00200000,
	WS_ISSECURITYWGT = 0x00400000,
	WS_ISTEXTWGT = 0x00800000,
	WS_MLSUPPORT = 0x01000000,
	WS_ISAUDITWGT = 0x02000000,
	WS_MLTEXTWGT = 0x04000000,
	WS_MLCOMBOWGT = 0x08000000,
	WS_MLMSGTXTWGT = 0x10000000,
	// @M31
	WS_ISREPORTPAGEWGT = 0x20000000,
	WS_ISREPORTTEMPLATEPAGEWGT = 0x40000000,
	// ---
	WS_ISHIDDEN = 0x80000000 //to hide widget in object view and data view (project page)
};

enum {						// defined security style for widgets
	kSecurityTypeNone=0,
	kSecurityTypeShow=0x0001,
	kSecurityTypeEnable=0x0002,
	kSecurityTypePrompt=0x0004
};

enum {
	kChildChangeWrite = 1,		// child widget wrote to a tag
	kChildChangeReload,			// reload the child widgets
	kChildChanged,				// child widgets have changed
	kChildGeometryChange		// the child widget has changed its geometry
};

enum {
	kUpdateMultiLangChangeCurrLang,
	kUpdateMultiLangMgrLoaded,
	kUpdateMultiLangChangeLink,
	kUpdateMultiLangChangelang,
	kUpdateMultiLangAddlang,
	kUpdateMultiLangDeletelang,
	kUpdateMultiLangMLTxtChanged,
	kMLUpdateAddLinks,
	kMLUpdateRemoveLinks,
	kUpdateMultiLangUpdateFont
};

class CWidget : public QObject//, protected QScriptable
{
	Q_OBJECT		// needed to support javascript

public:
	CWidget();
	virtual ~CWidget();
	
protected:	
	// ------------ JavaScript interface -----------------------
public:	// these functions can be accessed from ascript
	Q_INVOKABLE QObject* getWidget(const QString& aName){return NULL;};
	Q_INVOKABLE QVariant getProperty(const QString& strTag, int index=0){QVariant var;return var;};
	Q_INVOKABLE bool setProperty(const QString& pszTag, const QVariant& value, int index=0){return true;};;
	Q_INVOKABLE void moveTo(int x, int y){return;};
	Q_INVOKABLE void resize(int width, int height){return;};
	Q_INVOKABLE void refresh(){return;};

	Q_PROPERTY(int x READ getX WRITE setX)
	Q_PROPERTY(int y READ getY WRITE setY)
	Q_PROPERTY(int width READ getWidth WRITE setWidth)
	Q_PROPERTY(int height READ getHeight WRITE setHeight)
	Q_PROPERTY(bool visible READ getVisible WRITE setVisible)
	Q_PROPERTY(float opacity READ getOpacity WRITE setOpacity)
	Q_PROPERTY(float rotation READ getRotation WRITE setRotation)
	Q_PROPERTY(QVariant value READ getValue WRITE setValue)
	Q_PROPERTY(QVariant userValue READ getUserValue WRITE setUserValue)

	Q_PROPERTY(bool blink READ getBlink WRITE setBlink)
protected:
	int getX(){return 0;};
	void setX(int x){return;};
	int getY(){return 0;};
	void setY(int y){return;};
	int getWidth(){return 0;};
	void setWidth(int width){};
	int getHeight(){return 0;};
	void setHeight(int height){return;};
	bool getVisible(){return true;};
	void setVisible(bool bVisible){return;};
	float getOpacity(){return 0;};
	void setOpacity(float opacity){return;};
	float getRotation(){return 0.0;};
	void setRotation(float opacity){return;};
	QVariant getValue(){QVariant var;return var;};
	void setValue(const QVariant& value){return;};
	QVariant getUserValue(){QVariant var;return var;};
	void setUserValue(const QVariant& userValue){return;};
	bool getBlink(){return true;};
	void setBlink(bool bBlink){return;};
};

#endif