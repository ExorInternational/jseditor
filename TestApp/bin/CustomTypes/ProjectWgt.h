// ProjectWgt.h: interface for the CProjectMgrWgt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTWGT_H__4C956A93_1BFD_4861_9613_A67D0B0079A4__INCLUDED_)
#define AFX_PROJECTWGT_H__4C956A93_1BFD_4861_9613_A67D0B0079A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<QMainWindow>
#include "PageWgt.h"
#include "JSObjects.h"
#include "Widget.h"

class CPageMgrWgt;
class CStateObj;
class CGroupObj;
class CZoneTagUsageDetails;
class CActionWgtMoveIPCamera;

class CProjectWgt : public CPageWgt 
{
	Q_OBJECT
public:
	CProjectWgt();
	virtual ~CProjectWgt();

public:
	


protected:
	//	vector<CWidget*> m_vPages;
	//	map<_tstring, _tstring> m_mPageNames;
	//vector<pair<QString, QString> > m_vPageNames;
	//   QString m_strProjectPath;
	QString m_strStartPage;	
	QString m_strDebugIP;
	QString m_strServerSynchEnable;
	int m_nContextMenu;
	bool m_bDevTools;
	unsigned long m_availablePlugins;
	bool m_bEnableTouchBuzzer;
	unsigned long m_nTouchBuzzerTime;
	int m_nPrevClientSynchValue;
	bool m_bPrevQuality;
	bool m_bStarted;
	bool m_bUserMgmt;
	int m_nProjectMode;
	static bool m_bImageDBDefault;
	unsigned int m_wScreenSaverPage;
	unsigned int m_wScreenSaverTimeout;
	unsigned int m_wScreenSaverDisplayTime;
	bool m_bActiveJSDebugger;
	bool m_bAllowRemoteJsDebug;
	int m_nAutoRepeatPeriod;
	int m_nHoldTime;
	unsigned int m_nWebInactivityTimeout;
	// ------------ JavaScript interface -----------------------
public:	// these functions can be accessed from javascript
	Q_INVOKABLE QObject* getTagObj(const QString& tagName){return NULL;};
	Q_INVOKABLE void setTagObj(QObject* tagObj){return ;};

	Q_INVOKABLE QVariant getTag(const QString& tagName, const int index=0){QVariant var;return var;};
	Q_INVOKABLE QVariant getTag(const QString& tagName, CStateObj* state, const int index, const QString& strFnCallBack = "", bool bForceRead = false){QVariant var;return var;};
	Q_INVOKABLE QVariant setTag(const QString& tagName, const QVariant& tagValue, const int index=0, bool bForceWrite = false){QVariant var;return var;};

	//group interface
	Q_INVOKABLE int getGroup(const QString& groupName, CGroupObj* group, const QString& strFnCallBack = ""){return 1;};
	//recipe js interface
	Q_INVOKABLE QVariant getRecipeItem(const QString& recipeName, const QString& recipeSet, const QString& recipeItem){QVariant var;return var;};
	Q_INVOKABLE int setRecipeItem(const QString& recipeName, const QString& recipeSet, const QString& recipeItem, const QVariant& itemValue){return 1;};
	Q_INVOKABLE void downloadRecipe(const QString& recipeName, const QString& recipeSet){return ;};
	Q_INVOKABLE void uploadRecipe(const QString& recipeName, const QString& recipeSet){return ;};
	// macro commands
	Q_INVOKABLE void loadPage(const QString& pageName){return ;};
	Q_INVOKABLE void nextPage(){return ;};
	Q_INVOKABLE void prevPage(){return ;};
	Q_INVOKABLE void homePage(){return ;};
	Q_INVOKABLE void lastVisitedPage(){return ;};
	Q_INVOKABLE void showDialog(const QString& fileName){return ;};
	Q_INVOKABLE void closeDialog(const QString& closeParam = "Selected"){return ;};
	Q_INVOKABLE void showAlarmDialog(){return ;};
	Q_INVOKABLE void showAlarmsList(const QString& strAlarmsBuffer){return ;};
	Q_INVOKABLE void showMessage(const QString& strMessage){return ;};
	Q_INVOKABLE void clearAllTimeouts(){return ;};
	Q_INVOKABLE void launchApp(const QString& appName, const QString& appPath, const QString& arguments, bool singleInstance){return ;};
	Q_INVOKABLE void replaceMedia(const QString& strFolderName = "images", bool bSilent = false, const QString& sourcePath = "",  int nMediaType = 1, bool bResize = false){return ;};
	Q_INVOKABLE bool uploadToHMI(const QString& path, const QString& filter){return true;};
	Q_INVOKABLE bool downloadFromHMI(const QString& path, const QString& filter){return true;};
	Q_INVOKABLE void launchUpdater(const QString& path){return ;};
	// macro commans for Alarms
	Q_INVOKABLE void enableAlarms(){return ;};
	Q_INVOKABLE void ackAlarms(){return ;};
	Q_INVOKABLE void resetAlarms(){return ;};

	Q_INVOKABLE void moveIPCamera(const QString& strUser, const QString& strPassword, const QString& strIPAddr, const QString& strCommand){return ;};

	//@M31
	// printing macro command
	Q_INVOKABLE void printGfxReport(const QString& report, bool silent){return ;};
	Q_INVOKABLE void printText(const QString& text, bool silent){return ;};
	Q_INVOKABLE void printBytes(const QVariant& data, bool silent){return ;};
	Q_INVOKABLE void emptyPrintQueue(){return ;};
	Q_INVOKABLE void pausePrinting(){return ;};
	Q_INVOKABLE void resumePrinting(){return ;};
	Q_INVOKABLE void abortPrinting(){return ;};

	Q_PROPERTY(QVariant printStatus READ getPrintStatus)
	Q_PROPERTY(QString  printLastErrorString READ getPrintErrorString)
	Q_PROPERTY(QVariant printGfxJobQueueSize READ getPrintGfxJobQueueSize)
	Q_PROPERTY(QVariant printTextJobQueueSize READ getPrintTextJobQueueSize)
	Q_PROPERTY(QVariant printCurrentJob READ getPrintCurrentJob)
	Q_PROPERTY(QVariant printActualRAMUsage READ getPrintActualRamUsage)
	Q_PROPERTY(QVariant printRAMQuota READ getPrintRAMQuota)
	Q_PROPERTY(QVariant printActualDiskUsage READ getPrintActualDiskUsage)
	Q_PROPERTY(QVariant printDiskQuota READ getPrintDiskQuota)
	Q_PROPERTY(QVariant printSpoolFolder READ getPrintSpoolFolder)
	Q_PROPERTY(QVariant printPercentage READ getPrintPercentage)
		//---

	//database macros
	Q_INVOKABLE void dbInit(const QString& linkName, const QString& customSQL){return ;};
	Q_INVOKABLE void dbWriteTags(const QString& linkName,  const QString& customSQL, const QString& tags){return ;};
	Q_INVOKABLE void dbReadTags(const QString& linkName, const QString& customSQL, const QString& tags){return ;};
	Q_INVOKABLE void dbWriteGroups(const QString& linkName, const QString& customSQL, const QString& groups){return ;};
	Q_INVOKABLE void dbReadGroups(const QString& linkName, const QString& customSQL, const QString& groups){return ;};

	Q_INVOKABLE void dbWriteTrends(const  QString& dbLinkName,const  QString& sqlCustomQuery, const QString& trendName, const int durationIndex){return ;};
	Q_INVOKABLE void dbWriteEvents(const  QString& dbLinkName, const QString& sqlCustomQuery, const QString& archiveName,const int durationIndex){return ;};

	Q_INVOKABLE void dbWriteRecipes(const QString& dbLinkName, const QString& sqlCustomQuery, const QString& recipeNames){return ;};
	Q_INVOKABLE void dbReadRecipes(const QString& dbLinkName, const QString& sqlCustomQuery, const QString& recipeNames){return ;};

	// user management functions
	Q_INVOKABLE void logout(){return ;};

	/*! Begin data entry on the widget in given page, or current visual active page */
	Q_INVOKABLE void beginDataEntry(const QString& widgetName, const QString& pageName = ""){return ;};



	Q_PROPERTY(QVariant startPage READ getStartPage WRITE setStartPage)
	Q_PROPERTY(QVariant projectVersion READ getProjectVersion WRITE setProjectVersion)
	Q_PROPERTY(QVariant numTags READ getNumTags WRITE setNumTags)
	Q_PROPERTY(QVariant numTrends READ getNumTrends WRITE setNumTrends)
	Q_PROPERTY(QVariant numRecipes READ getNumRecipes WRITE setNumRecipes)
	Q_PROPERTY(QVariant numAlarms READ getNumAlarms WRITE setNumAlarms)
	Q_PROPERTY(QVariant numSchedules READ getNumSchedules WRITE setNumSchedules)
	Q_PROPERTY(QVariant numLanguages READ getNumLanguages WRITE setNumLanguages)
	//Q_PROPERTY(QVariant languageIndex READ getLanguageIndex WRITE setLanguageIndex)

	QVariant getProjectVersion(){QVariant var;return var;};
	void setProjectVersion(const QVariant& version){return ;};

protected:
	//@M31
	QString  getPrintErrorString(){QString var;return var;};
	QVariant getPrintStatus(){QVariant var;return var;};
	QVariant getPrintGfxJobQueueSize(){QVariant var;return var;};
	QVariant getPrintTextJobQueueSize(){QVariant var;return var;};
	QVariant getPrintCurrentJob(){QVariant var;return var;};
	QVariant getPrintActualRamUsage(){QVariant var;return var;};
	QVariant getPrintRAMQuota(){QVariant var;return var;};
	QVariant getPrintActualDiskUsage(){QVariant var;return var;};
	QVariant getPrintDiskQuota(){QVariant var;return var;};
	QVariant getPrintSpoolFolder(){QVariant var;return var;};
	QVariant getPrintPercentage(){QVariant var;return var;};
	//---

	QVariant getStartPage(){QVariant var;return var;};
	void setStartPage(const QVariant& page){return ;};
	QVariant getNumTags(){QVariant var;return var;};
	void setNumTags(const QVariant& numTags){return ;};
	QVariant getNumTrends(){QVariant var;return var;};
	void setNumTrends(const QVariant& numTags){return ;};
	QVariant getNumRecipes(){QVariant var;return var;};
	void setNumRecipes(const QVariant& numTags){return ;};
	QVariant getNumAlarms(){QVariant var;return var;};
	void setNumAlarms(const QVariant& numTags){return ;};
	QVariant getNumSchedules(){QVariant var;return var;};
	void setNumSchedules(const QVariant& numTags){return ;};
	QVariant getNumLanguages(){QVariant var;return var;};
	void setNumLanguages(const QVariant& numTags){return ;};
	//	QVariant getLanguageIndex();
	//	void setLanguageIndex(QVariant numTags);

	
protected:
	
	QString m_strTarget;
	QString m_strTargetName;
	QString m_projectVersion;

#ifdef _CUST_TMPL
	QString m_strKeyPadTmplType;
	QString m_strUserMgmtTmplType;
	QString m_strKeyPadTmplType_Portrait;
	QString m_strUserMgmtTmplType_Portrait;
#endif
	QStringList m_keyboards;
	unsigned int m_nMaxWidgets;
	unsigned int m_nMaxPages;
	unsigned int m_nMaxPageWidth;
	unsigned int m_nMaxPageHeight;
	unsigned int m_nMaxTemplatePages;
	unsigned int m_nMaxTags;
	unsigned int m_nMaxSchedulers;
	unsigned int m_nMaxAlarms;
	unsigned int m_nMaxDialogs;
	unsigned int m_nMaxTrends;
	unsigned int m_nMaxLanguages;
	unsigned int m_nMaxRecipes;
	unsigned int  m_nMaxRecipeElements;
	unsigned int  m_nMaxRecipeSets;
	unsigned int  m_nMaxRecipeTags;
	unsigned int  m_nMaxUsers;
	unsigned int  m_nMaxUserGroups;
	unsigned int  m_nMaxClients;
	unsigned int  m_nMaxTrendBufferSize;
	unsigned int m_nMaxTrendBufferSamples;
	unsigned int m_nMaxMacroActions ;
	unsigned int m_nMaxJavaScriptFileSize ;
	unsigned int m_nMaxProjectSize ;
	unsigned int m_nMaxMessages;
	unsigned int m_nMaxEvents;
	unsigned int m_nMaxEventsBufferSize;
	unsigned int m_nMaxUpdatePackageUserFolderSize;

	// @M31
	int m_nMaxReports;
	int m_nMaxReportPages;
	int m_nMaxPrintRAMQuota;
	int m_nMaxPrintDiskQuota;
	int m_nMaxPrintPixmapSize;
	// ---
	int m_nMaxDBLinks;
	int m_nMaxDBColumns;
	int m_nMaxDBStrLen;
	int 	m_nMaxDBRows;

	int m_nMaxDataTransfers;
	int m_nMaxOpenDialogs;
	int m_nMaxVariables;
	int m_nMaxFtpAdditionalFolders;

	// Enable freetype font engine
	bool m_bEnableQtFT;
	float m_fTargetZoomFac;
	bool m_bTargetZoomFacSup;

};

#endif 
