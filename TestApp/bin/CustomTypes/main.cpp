
#include <QApplication>

//#include "QDataTransferWnd.h"
#include "QEmailsInfoDlg.h"
#include "QGroupsSel.h"

#include "ProjectWgt.h"
#include "ProjectWgt.h"
#include "PageWgt.h"
#include "JSObjects.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(dataTransferWnd);
    QApplication app(argc, argv);
    QGroupsSel window;

	CProjectWgt* pProjectWgt = new CProjectWgt();
	CPageWgt* pPage = new CPageWgt();
	CStateObj* pState = new CStateObj();
	CWidget* pWgt = new CWidget();
	CGroupObj* pGroup = new CGroupObj();
	CJSTagObj* pTag = new CJSTagObj();

	

    window.show();
    return app.exec();
}
