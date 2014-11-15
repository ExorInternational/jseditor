
#include <QApplication>

//#include "QDataTransferWnd.h"
#include "QEmailsInfoDlg.h"
#include "QGroupsSel.h"

#include "ProjectWgt.h"
#include "ProjectWgt.h"
#include "PageWgt.h"
#include "JSObjects.h"
#include "FileSystemObj.h"

int main(int argc, char *argv[])
{
	/*Q_INIT_RESOURCE(dataTransferWnd);
    QApplication app(argc, argv);
    QGroupsSel window;*/

	CProjectWgt* pProjectWgt = new CProjectWgt();// js object name = "project"
	CPageWgt* pPage = new CPageWgt();// js object name = "page"
	CStateObj* pState = new CStateObj();// js object name = "State"
	CWidget* pWgt = new CWidget();// doesn't seem to have any global js object
	CGroupObj* pGroup = new CGroupObj();// js object name = "Group"
	CJSTagObj* pTag = new CJSTagObj();// doesn't seem to have any global js object
	CFileSystemObj* fs = new CFileSystemObj();// js object name = "js"
	

    //window.show();
    //return app.exec();
}
