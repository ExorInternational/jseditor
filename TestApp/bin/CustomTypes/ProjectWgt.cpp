// ProjectWgt.cpp: implementation of the CProjectMgrWgt class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectWgt.h"
#include "JSObjects.h"


const float kTargetMinZoom = (float)0.2;
const float kTargetMaxZoom = (float)3;

//////////////////////////////////////////////////////////////////////
// CProjectWgt
//////////////////////////////////////////////////////////////////////
bool CProjectWgt::m_bImageDBDefault=true;

CProjectWgt::CProjectWgt()
{
}

CProjectWgt::~CProjectWgt()
{
}
