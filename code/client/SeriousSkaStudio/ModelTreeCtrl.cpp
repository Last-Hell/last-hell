// ModelTreeCtrl.cpp: implementation of the CModelTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "SeriousSkaStudio.h"
#include "ModelTreeCtrl.h"
#include "DlgBarTreeView.h"

#ifdef _DEBUG
#undef new
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModelTreeCtrl::CModelTreeCtrl()
{
  hLastSelected = NULL;
}

CModelTreeCtrl::~CModelTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CModelTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CModelTreeCtrl)
  ON_NOTIFY_REFLECT (TVN_SELCHANGED, OnSelChanged)
	ON_WM_CHAR()
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(NM_CLICK, OnItemClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnItemDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CModelTreeCtrl::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
  HTREEITEM hSelected = GetSelectedItem();
  // if selected item is diferent from last selected item
  if(hLastSelected != hSelected) {
    theApp.m_dlgBarTreeView.SelItemChanged(hSelected);
    hLastSelected = hSelected;
  }
  *pResult = 0;
}

void CModelTreeCtrl::OnItemClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
  POINT pt;
  UINT uiFlags=0;
  GetCursorPos(&pt);
  ScreenToClient(&pt);
  HTREEITEM hClicked = HitTest(pt,&uiFlags);
  if(hClicked!=NULL) {
    RECT rcItem;
    // get item rect
    GetItemRect(hClicked,&rcItem,TRUE);
    NodeInfo &niClicked = theApp.m_dlgBarTreeView.GetNodeInfo(hClicked);
    // check if clicked only inside in rect of icon
    RECT rcIcon = {rcItem.left-18,rcItem.top,rcItem.left,rcItem.bottom};
    RECT rcItemAndIcon = {rcItem.left-18,rcItem.top,rcItem.right,rcItem.bottom};
    if(PtInRect(&rcItem/*AndIcon*/,pt)) {
      // notify that item icon was clicked
      theApp.m_dlgBarTreeView.OnItemClick(hClicked,hLastSelected);
      
      // if clicked item is animation
      if(niClicked.ni_iType == NT_ANIMATION) {
        theApp.m_dlgBarTreeView.SelItemChanged(hClicked);
        hLastSelected = hClicked;
      }
    }
    else if(PtInRect(&rcIcon,pt)) {
      theApp.m_dlgBarTreeView.OnItemIconClick(hClicked);
    }
  }
	*pResult = 0;
}

void CModelTreeCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
  POINT pt;
  UINT uiFlags=0;
  GetCursorPos(&pt);
  ScreenToClient(&pt);
  HTREEITEM hClicked = HitTest(pt,&uiFlags);
  if(hClicked!=NULL)
  {
    NodeInfo &ni = theApp.m_dlgBarTreeView.GetNodeInfo(hClicked);
    RECT rcItem;
    // get item rect
    GetItemRect(hClicked,&rcItem,TRUE);
    // check if clicked only inside in rect of icon
    RECT rcIcon = {rcItem.left-18,rcItem.top,rcItem.left,rcItem.bottom};
    // if clicked in icon rect
    if(PtInRect(&rcIcon,pt)) {
      // if clicked item is mesh surface
      if(ni.ni_iType == NT_MESHSURFACE) {
        // notify that item icon was clicked
        Select(hClicked,TVGN_CARET);
        theApp.m_dlgBarTreeView.SelectAllSurfaces(hClicked);
      }
    }
    CMenu menu;
    INDEX iMenuIndex=-1;
    
    if(menu.LoadMenu(IDR_POPUP_MENU)) {
      switch(ni.ni_iType) {
        case NT_MODELINSTANCE  : iMenuIndex = 0; break;
        case NT_MESHLODLIST    : iMenuIndex = 1; break;
        case NT_MESHLOD        : iMenuIndex = 7; break;
        case NT_TEXINSTANCE    : iMenuIndex = 4; break;
        case NT_SKELETONLODLIST: iMenuIndex = 2; break;
        case NT_SKELETONLOD    : iMenuIndex = 9; break;
        case NT_BONE           : iMenuIndex =-1; break;
        case NT_ANIMSET        : iMenuIndex = 3; break;
        case NT_ANIMATION      : iMenuIndex = 8; break;
        case NT_ANIM_BONEENV   : iMenuIndex =-1; break;
        case NT_COLISIONBOX    : iMenuIndex = 5; break;
        case NT_ALLFRAMESBBOX  : iMenuIndex = 6; break;
        case NT_MESHSURFACE    : iMenuIndex =-1; break;
//안태훈 수정 시작	//(Add & Modify SSSE Effect)(0.1)
        case NT_SKATAG         : iMenuIndex =10; break;
//안태훈 수정 끝	//(Add & Modify SSSE Effect)(0.1)
//안태훈 수정 시작	//(Effect Add & Modify for Close Beta)(0.1)
        case NT_ANIMEFFECT_REG : iMenuIndex =11; break;
//안태훈 수정 끝	//(Effect Add & Modify for Close Beta)(0.1)
		case NT_RIDINGPOSITION : iMenuIndex = 9; break;
      }
      if(iMenuIndex>=0) {
        Select(hClicked,TVGN_CARET);
        CMenu *pPopup = menu.GetSubMenu(iMenuIndex);
		
		// 
		if (iMenuIndex == 0) // NT_MODELINSTANCE일때
		{
			CModelInstance *pmi = (CModelInstance*)ni.ni_pPtr;
			CModelInstance *pmiParent = pmi->GetParent(theApp.GetDocument()->m_ModelInstance);

			if (pmiParent == NULL) // Parent Model일 경우
			{ // menu에서 Ride setting을 제외한다.
				pPopup->DeleteMenu(ID_RIDESETTING, MF_BYCOMMAND);
			}
		}

        CSeriousSkaStudioView *pSKAView = theApp.GetActiveView();
        if(pPopup!=NULL && pSKAView!=NULL) {
          CRect rc;
          GetWindowRect(&rc);
          pPopup->TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_LEFTALIGN,
								       rc.left+pt.x, rc.top+pt.y, pSKAView);
        }
      }
    }
  }
	*pResult = 1;
}

void CModelTreeCtrl::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnRclick(pNMHDR,pResult);
	*pResult = 1;
}

void CModelTreeCtrl::OnItemDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnItemClick(pNMHDR,pResult);
	*pResult = 0;
}

void CModelTreeCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CTreeCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CModelTreeCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR; 
  BOOL bControl = (GetKeyState( VK_CONTROL)&0x8000) != 0;

  switch(pTVKeyDown->wVKey)
  {
    case VK_F5:
    {
      theApp.ReloadRootModelInstance();
      theApp.NotificationMessage("Document reloaded");
    }
    break;
    case 0x52://VK_R
    {
      if(bControl)
      {
        theApp.ReloadRootModelInstance();
        theApp.NotificationMessage("Document reloaded");
      }
    }
    break;
    case VK_DELETE:
    {
      // delete selected item
      ((CSeriousSkaStudioView*)theApp.GetActiveView())->SendMessage(WM_COMMAND,ID_DELETESELECTED);
    }
    break;
  }
	
	*pResult = 0;
}
