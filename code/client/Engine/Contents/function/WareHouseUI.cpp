#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include "WareHouseUI.h"
#include <Engine/Interface/UIPetInfo.h>
#include <Common/Packet/ptype_inventory.h>
#include <Common/Packet/ptype_old_do_stash.h>
#include <Engine/Interface/UISecurity.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>
#include <Engine/Interface/UIHelp.h>
#include <Engine/Interface/UISocketSystem.h>
#include <Engine/Contents/Base/UIMsgBoxNumeric_only.h>
#include <Engine/Info/MyInfo.h>
#include <Engine/Contents/function/WareHouseUI.h>

extern INDEX g_iShowHelp1Icon;

#define WAREHOUSE_WAREHOUSE_SLOT_ROW_TOTAL	60
#define WAREHOUSE_WAREHOUSE_SLOT_COL		5
#define	WAREHOUSE_TRADE_SLOT_TOTAL			10
#define WAREHOUSE_TRADE_SLOT_COL			5

#define WAREHOUSE_DEFUALT_MAX_SLOT			150
#define WAREHOUSE_CASHUSE_MAX_SLOT			300

enum eSelection
{
	WAREHOUSE_IN,
	WAREHOUSE_OUT,
	WAREHOUSE_CHANGEPW,
	WAREHOUSE_TALK,
};

enum ErrCode 
{
	eERR_KEEP_FAIL_EMPTY,
	eERR_TAKE_FAIL_EMPTY
};

class CmdWareHouseAddItem : public Command
{
public:
	CmdWareHouseAddItem() : m_pWnd(NULL)	{}
	void setData(CWareHouseUI* pWnd)	{ m_pWnd = pWnd;	}
	void execute() 
	{
		if (m_pWnd != NULL)
			m_pWnd->AddItemCallback();
	}
private:
	CWareHouseUI* m_pWnd;
};

class CmdWareHouseDelItem : public Command
{
public:
	CmdWareHouseDelItem() : m_pWnd(NULL)	{}
	void setData(CWareHouseUI* pWnd)	{ m_pWnd = pWnd;	}
	void execute() 
	{
		if (m_pWnd != NULL)
			m_pWnd->DelItemCallback();
	}
private:
	CWareHouseUI* m_pWnd;
};

// Ware House Icon LButton Down Event
class CmdWareHouseIconDown : public Command
{
public:
	CmdWareHouseIconDown() : m_pWnd(NULL), nIndex_(-1)	{}
	void setData(CWareHouseUI* pWnd, int nIndex)	{ m_pWnd = pWnd; nIndex_ = nIndex; }
	void execute() 
	{
		if (m_pWnd != NULL)
			m_pWnd->WareIconMouseLDownEvent(nIndex_);
	}
private:
	CWareHouseUI* m_pWnd;
	int nIndex_;
};

// Trade Icon LButton Down Event
class CmdTradeIconDown : public Command
{
public:
	CmdTradeIconDown() : m_pWnd(NULL), nIndex_(-1)	{}
	void setData(CWareHouseUI* pWnd, int nIndex)	{ m_pWnd = pWnd; nIndex_ = nIndex; }
	void execute() 
	{
		if (m_pWnd != NULL)
			m_pWnd->TradeIconMouseLDownEvent(nIndex_);
	}
private:
	CWareHouseUI* m_pWnd;
	int nIndex_;
};

// Ware House Icon Double LButton Click Event
class CmdWareHouseIconDBLCLK : public Command
{
public:
	CmdWareHouseIconDBLCLK() : m_pWnd(NULL), nIndex_(-1)	{}
	void setData(CWareHouseUI* pWnd, int nIndex)	{ m_pWnd = pWnd; nIndex_ = nIndex; }
	void execute() 
	{
		if (m_pWnd != NULL)
			m_pWnd->WareIconMouseDBLCLKEvent(nIndex_);
	}
private:
	CWareHouseUI* m_pWnd;
	int nIndex_;
};

// Trade Icon Double LButton Click Event
class CmdTradeIconDBLCLK : public Command
{
public:
	CmdTradeIconDBLCLK() : m_pWnd(NULL), nIndex_(-1)	{}
	void setData(CWareHouseUI* pWnd, int nIndex)	{ m_pWnd = pWnd; nIndex_ = nIndex; }
	void execute() 
	{
		if (m_pWnd != NULL)
			m_pWnd->TradeIconMouseDBLCLKEvent(nIndex_);
	}
private:
	CWareHouseUI* m_pWnd;
	int nIndex_;
};


CWareHouseUI::CWareHouseUI()
	: m_pMoveArea(NULL)
	, m_pItemsTemp(NULL)
	, m_bDrag(false)
	, m_nOriX(0), m_nOriY(0)
	, m_nMouseX(0)
	, m_nMouseY(0)
	
{
	m_fNpcPosX = 0.0f;
	m_fNpcPosZ = 0.0f;
	m_nNpcIndex = -1;
	m_nNPCVIdx	= -1;
	m_bStorageWareHouse	= FALSE;
	m_bHasPassword	= false;
	m_strPW			= CTString( "0" );
	m_useTime		= 0; 
	m_nTempTradeIdx	= -1;
	m_nTempStorageIdx = -1;

	int i;
	for (i = 0; i < eBTN_MAX; ++i)
		m_pBtn[i] = NULL;
	
	for (i = 0; i < eTEXT_MAX; ++i)
		m_pText[i] = NULL;

	for (i = 0; i < eARRAY_MAX; ++i)
		m_pArray[i] = NULL;

	ResetUI();
	setInherit(false);
}

CWareHouseUI::~CWareHouseUI()
{
	Destroy();

	if( m_vectorStorageItems.empty() == FALSE )
		ClearItems();
}

void CWareHouseUI::AddItemCallback()
{
	if (UIMGR()->GetMsgBoxNumOnly()->GetData() > 0)
	{
		SQUAD llCount = UIMGR()->GetMsgBoxNumOnly()->GetData();
		WareHouseToTrade(llCount);
	}
}

void CWareHouseUI::DelItemCallback()
{
	SQUAD llCount = UIMGR()->GetMsgBoxNumOnly()->GetData();

	if (llCount > 0 && llCount <= m_pItemsTemp->Item_Sum)
	{
		TradeToWareHouse(llCount);
	}
}

void CWareHouseUI::AddWareHouseItem( int nIndex )
{
	if (nIndex < 0 || nIndex >= m_vectorStorageItems.size())
		return;

	m_nTempStorageIdx = nIndex;

	CUIManager* pUIManager = CUIManager::getSingleton();
	m_pItemsTemp = m_vectorStorageItems[nIndex];
	CItemData*	pItemData = m_vectorStorageItems[nIndex]->ItemData;
	int		nItemIndex = m_vectorStorageItems[nIndex]->Item_Index;
	SQUAD	nCount = m_vectorStorageItems[nIndex]->Item_Sum;
	int		nItemPlus = m_vectorStorageItems[nIndex]->Item_Plus;
	m_nTempMax = -1;

	// Ask quantity
	if ((m_bStorageWareHouse && (pItemData->GetFlag() & ITEM_FLAG_COUNT)) ||
		(!m_bStorageWareHouse && (pItemData->GetFlag() & ITEM_FLAG_COUNT) && nCount > 1))
	{
		CTString	strMessage;
		const char	*szItemName = _pNetwork->GetItemName(nItemIndex);

		if( pItemData->GetType() == CItemData::ITEM_ETC &&
			pItemData->GetSubType() == CItemData::ITEM_ETC_MONEY )
		{
			strMessage.PrintF( _S( 1323, "몇 나스를 옮기시겠습니까?" ) );

			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo( _S( 823, "창고" ), UMBS_OKCANCEL | UMBS_INPUTBOX,	
				UI_WARE_HOUSE, MSGCMD_WAREHOUSE_ADD_ITEM );

			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
			pUIManager->GetMsgBoxNumOnly()->CloseBox();
		}
		else
		{
			strMessage.PrintF( _S2( 150, szItemName, "몇 개의 %s<를> 옮기시겠습니까?" ), szItemName );

			CmdWareHouseAddItem* pCmd = new CmdWareHouseAddItem;
			pCmd->setData(this);
			UIMGR()->GetMsgBoxNumOnly()->SetInfo(pCmd, _S( 823, "창고" ), strMessage, 1, nCount);
		}
	}
	else if (nItemPlus > 0 && !(pUIManager->IsPet(pItemData) || pUIManager->IsWildPet(pItemData) ||
		(pItemData->GetType() == CItemData::ITEM_ETC && 
		(pItemData->GetSubType() == CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD || nItemIndex == 6941))))
	{
		CTString	strMessage;
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo( _S( 823, "창고" ), UMBS_YESNO,		
			UI_WARE_HOUSE, MSGCMD_WAREHOUSE_ADD_PLUSITEM );
		const char*	szItemName = _pNetwork->GetItemName(nItemIndex);
		strMessage.PrintF(_S2(264, szItemName, "[%s +%d]<를> 옮기시겠습니까?"), szItemName, nItemPlus);
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
	}
	else
	{
		WareHouseToTrade();
	}
}

void CWareHouseUI::DelWareHouseItem()
{
	if (m_pItemsTemp == NULL)
		return;

	CItemData	*pItemData = m_pItemsTemp->ItemData;

	if (pItemData == NULL)
		return;

	// Ask quantity
	if (m_pItemsTemp->Item_Sum > 1)
	{
		CTString	strMessage;
		const char	*szItemName = _pNetwork->GetItemName(m_pItemsTemp->Item_Index);

		if (pItemData->GetType() != CItemData::ITEM_ETC ||
			pItemData->GetSubType() != CItemData::ITEM_ETC_MONEY)
		{
			strMessage.PrintF( _S2( 150, szItemName, "몇 개의 %s<를> 옮기시겠습니까?" ), szItemName );

			CmdWareHouseDelItem* pCmd = new CmdWareHouseDelItem;
			pCmd->setData(this);
			UIMGR()->GetMsgBoxNumOnly()->SetInfo(pCmd, _S( 823, "창고" ), strMessage, 1, m_pItemsTemp->Item_Sum);
		}
	}
	else
	{
		TradeToWareHouse();
	}
}

void CWareHouseUI::PressFirstBtn()
{
	if (m_bStorageWareHouse == TRUE)
		InNas();
	else
		OutNas();
}

void CWareHouseUI::PressSecondBtn()
{
	if (m_bStorageWareHouse == TRUE)
		KeepItems();
	else
		TakeItems();
}

void CWareHouseUI::WareIconMouseLDownEvent( int nSelIdx )
{
	if (m_bStorageWareHouse == FALSE)
	{
		m_nSelTradeItemID = -1;
		m_nSelWareHouseItemID = nSelIdx;	// 선택된 슬롯의 아이템 ID
	}	
}

void CWareHouseUI::TradeIconMouseLDownEvent( int nSelIdx )
{
	m_nSelTradeItemID = nSelIdx;
	m_nSelWareHouseItemID = -1;
}

void CWareHouseUI::WareIconMouseDBLCLKEvent(int nSelIdx)
{
	m_nSelWareHouseItemID = -1;

	if (!m_bStorageWareHouse)
	{
		WareHouseCloseMessageBox();
		AddWareHouseItem(nSelIdx);
	}
}

void CWareHouseUI::TradeIconMouseDBLCLKEvent(int nSelIdx)
{
	int	nTradeItemID = m_nSelTradeItemID;
	m_nSelTradeItemID = -1;
	WareHouseCloseMessageBox();

	if (nSelIdx >= m_vecTradeItems.size())
		return;

	m_pItemsTemp = m_vecTradeItems[nSelIdx];
	m_nTempTradeIdx = nTradeItemID;

	int nCnt = m_vectorStorageItems.size();

	for (int i = 0; i < nCnt; ++i)
	{
		if (m_vectorStorageItems[i]->Item_UniIndex == m_pItemsTemp->Item_UniIndex)
		{
			m_nTempStorageIdx = i;
			break;
		}
	}
	DelWareHouseItem();
}

void CWareHouseUI::WareSlotMouseLUPEvent()
{
	CUIManager* pUIMgr = UIMGR();
	CUIIcon* pDrag = pUIMgr->GetDragIcon();

	if (pDrag == NULL)
		return;

	if (m_bStorageWareHouse == FALSE)
	{
		// If holding button is item and is from warehouse
		if (pDrag->getBtnType() == UBET_ITEM &&
			pDrag->GetWhichUI() == UI_WARE_HOUSE )
		{
			CUIIcon* pIcon = GetWareHouseItemIcon(m_nSelWareHouseItemID);

			// If this item is moved from trade slot
			if (m_nSelWareHouseItemID < 0 ||
				(pIcon && pIcon->getIndex() != pDrag->getIndex()) )
			{
				m_nTempTradeIdx = m_nSelTradeItemID;
				m_pItemsTemp = m_vecTradeItems[m_nTempTradeIdx];

				int nCnt = m_vectorStorageItems.size();

				for (int i = 0; i < nCnt; ++i)
				{
					if (m_vectorStorageItems[i]->Item_UniIndex == m_pItemsTemp->Item_UniIndex)
					{
						m_nTempStorageIdx = i;
						break;
					}
				}

				DelWareHouseItem();
			}
		}
	}	
}

void CWareHouseUI::TradeSlotMouseLUPEvent()
{
	CUIManager* pUIMgr = UIMGR();
	CUIIcon* pDrag = pUIMgr->GetDragIcon();

	if (pDrag == NULL)
		return;

	if (m_bStorageWareHouse == TRUE)
	{
		// If holding button is item and is from warehouse
		if (pDrag->getBtnType() == UBET_ITEM &&
			pDrag->GetWhichUI() == UI_INVENTORY )
		{
			AddWareHouseItemFromInventory();
		}
	}
	else
	{
		if (pDrag->getBtnType() == UBET_ITEM &&
			pDrag->GetWhichUI() == UI_WARE_HOUSE )
		{
			CUIIcon* pIcon = GetTradeItemIcon(m_nSelTradeItemID);

			// If this item is moved from warehouse slot
			if (m_nSelTradeItemID < 0 ||
				(pIcon && pIcon->getIndex() != pDrag->getIndex()) )
			{
				AddWareHouseItem(m_nSelWareHouseItemID);
			}
		}
	}
}

void CWareHouseUI::KeepItems()
{
	int		i;
	// Buy nothing
	if( m_nTotalPrice < 0 && m_nInNas <= 0 )
	{
		ErrMessage(eERR_KEEP_FAIL_EMPTY);
		return;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();
	CUIIcon* pIcon = NULL;
	// Can't stash items

	for (i = 0; i < WAREHOUSE_TRADE_SLOT_TOTAL; i++)
	{
		// Add system message
		CTString tv_str;
		pIcon = GetTradeItemIcon(i);

		if (pIcon == NULL)
			continue;

		CItems*		pItems = pIcon->getItems();

		if (pItems == NULL)
			continue;

		CItemData*	pItemData = pItems->ItemData;

		if (pItemData == NULL)
			continue;

#ifdef ADD_SUBJOB

		if (pItemData->IsFlag(ITEM_FLAG_SELLER) ?
			!pUIManager->CheckSellerItem(UI_WARE_HOUSE, pItemData->GetFlag()) :
		(pItemData->GetFlag() & ITEM_FLAG_NO_STASH) ||
			(pItemData->GetFlag() & ITEM_FLAG_ORIGIN && pItems->Item_Flag & FLAG_ITEM_BELONG) || 
			pItemData->GetFlag() & ITEM_FLAG_ABS)
#else
		if ((pItemData->GetFlag() & ITEM_FLAG_NO_STASH) ||
			(pItemData->GetFlag() & ITEM_FLAG_ORIGIN && pItems->Item_Flag & FLAG_ITEM_BELONG) || 
			pItemData->GetFlag() & ITEM_FLAG_ABS)
#endif
		{
			tv_str.PrintF(_S(2578, "저장할 수 없는 아이템[%s] 입니다."), pItemData->GetName());
			pUIManager->GetChattingUI()->AddSysMessage(tv_str, SYSMSG_ERROR);
			return;
		}

	}

	// Not enough money
	if(_pNetwork->MyCharacterInfo.money < m_nTotalPrice )
	{
		// Add system message
		pUIManager->GetChattingUI()->AddSysMessage( _S( 827, "나스가 부족하여 물품을 보관할 수 없습니다." ), SYSMSG_ERROR );	
		return;
	}

	// Check inventory space
	int	ctEmptySlot = 0;
	int	ctTradeItems = 0;

	for( i = 0; i < ITEM_COUNT_IN_INVENTORY_STASH; i++ )
	{
		pIcon = GetWareHouseItemIcon(i);

		if (pIcon == NULL || pIcon->IsEmpty())
		{
			ctEmptySlot++;
			continue;
		}

		int	nIndex = pIcon->getIndex();
		CItemData*	pItemData = CItemData::getData(nIndex);

		if (pItemData->GetFlag() & ITEM_FLAG_COUNT)
		{
			for( int iItem = 0; iItem < WAREHOUSE_TRADE_SLOT_TOTAL; iItem++ )
			{
				CUIIcon* pIcon = GetTradeItemIcon(iItem);

				if (pIcon == NULL)
					continue;

				if (nIndex == pIcon->getIndex())
					ctTradeItems--;
			}
		}
	}

	// Not enough space
	if( ctEmptySlot < ctTradeItems )
	{
		// Add system message
		pUIManager->GetChattingUI()->AddSysMessage( _S( 265, "인벤토리 공간이 부족합니다." ), SYSMSG_ERROR );
		return;
	}

	//_pNetwork->BuyItem( m_nSelectedWareHouseID, m_nNumOfItem, m_nTotalPrice );
	SendWareHouseKeepReq();
}

void CWareHouseUI::TakeItems()
{
	// Sell nothing
	if( m_nTotalPrice < 0 && m_nOutNas <= 0 )
	{
		ErrMessage(eERR_TAKE_FAIL_EMPTY);
		return;
	}

	//_pNetwork->SellItem( m_nSelectedWareHouseID, m_nNumOfItem, m_nTotalPrice );
	SendWareHouseTakeReq();
}

void CWareHouseUI::InNas()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	if(pUIManager->DoesMessageBoxExist(MSGCMD_WAREHOUSE_ADD_MONEY))
		return;
	MsgBoxInfo.SetMsgBoxInfo( _S( 5906, "입금" ), UMBS_OKCANCEL | UMBS_INPUTBOX,	
		UI_WARE_HOUSE, MSGCMD_WAREHOUSE_ADD_MONEY );
	strMessage.PrintF( _S( 5904, "몇 개의 나스를 입금 하시겠습니까?" ) );		
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );

	return;
}

void CWareHouseUI::OutNas()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	if(pUIManager->DoesMessageBoxExist(MSGCMD_WAREHOUSE_TAKE_MONEY))
		return;
	MsgBoxInfo.SetMsgBoxInfo( _S( 5907, "출금" ), UMBS_OKCANCEL | UMBS_INPUTBOX,	
		UI_WARE_HOUSE, MSGCMD_WAREHOUSE_TAKE_MONEY );
	strMessage.PrintF( _S( 5905, "몇개의 나스를 출금 하시겠습니까?" ) );		
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );

	return;
}

void CWareHouseUI::AddWareHouseItemFromInventory()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	CUIIcon* pDrag = pUIManager->GetDragIcon();

	if (pDrag == NULL)
		return;

	CItems* pItems = pDrag->getItems();

	if (pItems == NULL)
		return;

	if (pItems->Item_Wearing >= 0) // 착용중인 장비일 경우 등록 되면 안된다.
		return;

	m_pItemsTemp = pItems;

	CItemData*	pItemData	= m_pItemsTemp->ItemData;
	const char* szItemName	= pItemData->GetName();

	int		nItemIndex = m_pItemsTemp->Item_Index;
	int		nItemPlus = m_pItemsTemp->Item_Plus;
	ULONG	ulItemFlag = m_pItemsTemp->Item_Flag;
	m_nTempMax = m_pItemsTemp->Item_Sum;

	// Ask quantity
	if( ( m_bStorageWareHouse && ( pItemData->GetFlag() & ITEM_FLAG_COUNT ) && m_nTempMax > 1) ||
		( !m_bStorageWareHouse && ( pItemData->GetFlag() & ITEM_FLAG_COUNT ) && m_nTempMax > 1 ) )
	{
		CTString	strMessage;
		CUIMsgBox_Info	MsgBoxInfo;

		// 나스의 경우.
		if( pItemData->GetType() == CItemData::ITEM_ETC &&
			pItemData->GetSubType() == CItemData::ITEM_ETC_MONEY )
		{
			MsgBoxInfo.SetMsgBoxInfo( _S( 823, "창고" ), UMBS_OKCANCEL | UMBS_INPUTBOX,	
				UI_WARE_HOUSE, MSGCMD_WAREHOUSE_ADD_MONEY );
			strMessage.PrintF(  _S( 960, "보관하실 나스를 입력해 주십시오." )  );		
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		else
		{
			strMessage.PrintF( _S2( 150, szItemName, "몇 개의 %s<를> 옮기시겠습니까?" ), szItemName );

			CmdWareHouseAddItem* pCmd = new CmdWareHouseAddItem;
			pCmd->setData(this);
			UIMGR()->GetMsgBoxNumOnly()->SetInfo(pCmd, _S( 823, "창고" ), strMessage, 1, m_nTempMax);
		}		
	}
	else if ((pItemData->GetFlag() & ITEM_FLAG_ORIGIN) && (ulItemFlag& FLAG_ITEM_BELONG))
	{
		CTString tv_str;
		tv_str.PrintF(_S(2578, "저장할 수 없는 아이템[%s] 입니다." ),pItemData->GetName() );
		pUIManager->GetChattingUI()->AddSysMessage( tv_str, SYSMSG_ERROR );
		return;
	}
	else if (nItemPlus > 0 && !(pUIManager->IsPet(pItemData) || pUIManager->IsWildPet(pItemData) ||
		pItemData->GetType() == CItemData::ITEM_ETC && (pItemData->GetSubType() == CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD || nItemIndex == 6941)))
	{
		CTString	strMessage;
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo( _S( 823, "창고" ), UMBS_YESNO,		
			UI_WARE_HOUSE, MSGCMD_WAREHOUSE_ADD_PLUSITEM );
		//const char	*szItemName = pItemData->GetName();
		strMessage.PrintF( _S2( 264, szItemName, "[%s +%d]<를> 옮기시겠습니까?" ), szItemName, nItemPlus );
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
	}
	else
	{
		WareHouseToTrade();
	}
}

void CWareHouseUI::DelWareHouseItemToInventory()
{
	// 보관 모드에서만 동작
	if (m_bStorageWareHouse == FALSE)
		return;

	if(m_nSelTradeItemID < 0)
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();

	CUIIcon* pDrag = pUIManager->GetDragIcon();

	if (pDrag == NULL)
		return;

	CItems* pItems = pDrag->getItems();

	if (pItems == NULL)
		return;

	int i, nCnt = m_vecTradeItems.size();

	for (i = 0; i < nCnt; ++i)
	{
		if (m_vecTradeItems[i]->Item_UniIndex == pItems->Item_UniIndex)
		{
			m_nTempTradeIdx = i;
			break;
		}
	}

	if (i == nCnt)
		return;

	m_pItemsTemp = pItems;

	DelWareHouseItem();
}

void CWareHouseUI::OpenWareHouse( SBYTE sbSetPW, bool bCashRemoteOpen /*= false */ )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if(pUIManager->DoesMessageBoxLExist( MSGLCMD_WAREHOUSE_REQ ) || IsVisible())
		return;

	if(pUIManager->GetSecurity()->IsVisible() )
	{
		return;
	}

	// If inventory is already locked
	if (pUIManager->GetInventory()->IsLocked() == TRUE ||
		pUIManager->GetInventory()->IsLockedArrange() == TRUE)
	{
		// 이미 Lock 인 창이 있을 경우 열지 못한다.
		pUIManager->GetInventory()->ShowLockErrorMessage();
		return;
	}

	pUIManager->CloseMessageBox( MSGCMD_SECURITY_PASSWORD);
	pUIManager->CloseMessageBox( MSGCMD_CONFIRM_PASSWORD);
	pUIManager->CloseMessageBox( MSGCMD_OLD_PASSWORD);	

	// 패스워드 기능 삭제 -> Quest has 로 사용중
	BOOL bHasQuest = sbSetPW ? TRUE : FALSE;
	closeUI();

	// Set position of target npc
	//m_fNpcX = fX;
	//m_fNpcZ = fZ;

	// Character state flags
	pUIManager->SetCSFlagOn( CSF_WAREHOUSE );

	pUIManager->CloseMessageBoxL( MSGLCMD_WAREHOUSE_REQ );

	// Create refine message box
	pUIManager->CreateMessageBoxL( _S( 814, "보관소" ) , UI_WARE_HOUSE, MSGLCMD_WAREHOUSE_REQ );	

	if( m_nNpcIndex != -1 )
	{
		CTString	strNpcName = CMobData::getData(m_nNpcIndex)->GetName();
		pUIManager->AddMessageBoxLString( MSGLCMD_WAREHOUSE_REQ, TRUE, strNpcName, -1, 0xE18600FF );
	}

	pUIManager->AddMessageBoxLString( MSGLCMD_WAREHOUSE_REQ, TRUE, _S( 815, "물품 보관을 원하십니까?" ) , -1, 0xA3A1A3FF );		
	pUIManager->AddMessageBoxLString( MSGLCMD_WAREHOUSE_REQ, TRUE, _S( 816, "저희 물품 보관소에서는 여행자님의 물품을 안전하게 보관하고 언제 어디서든지 저희 물품 보관소가 있는 곳이라면 물품을 찾으실 수 있습니다." ) , -1, 0xA3A1A3FF );		

	CTString strMessage;	
	strMessage.PrintF( _S( 817, "물품을 맡긴다." ) );			
	pUIManager->AddMessageBoxLString( MSGLCMD_WAREHOUSE_REQ, FALSE, strMessage, WAREHOUSE_IN );

	strMessage.PrintF( _S( 818, "물품을 찾는다." ) );			
	pUIManager->AddMessageBoxLString( MSGLCMD_WAREHOUSE_REQ, FALSE, strMessage, WAREHOUSE_OUT );

#ifdef	STASH_PASSWORD
	pUIManager->AddMessageBoxLString( MSGLCMD_WAREHOUSE_REQ, FALSE, _S( 819, "암호를 변경한다." ), WAREHOUSE_CHANGEPW );
#endif	// STASH_PASSWORD

	if( bHasQuest )
	{
		// 2009. 05. 27 김정래
		// 이야기한다 변경 처리
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_WAREHOUSE_REQ);				
	}

	strMessage.PrintF( _S( 1220, "취소한다." ) );		
	pUIManager->AddMessageBoxLString( MSGLCMD_WAREHOUSE_REQ, FALSE, strMessage );

	m_bCashRemote = bCashRemoteOpen;

	if (bCashRemoteOpen == true)
		m_nNPCVIdx = -1;
}

void CWareHouseUI::openUI()
{
	if (GetHide() == FALSE)
		return;
	Hide(FALSE);
	SetVisible(TRUE);

	SetUI();

	CUIManager* pUIMgr = UIMGR();
	pUIMgr->RearrangeOrder( UI_WARE_HOUSE, TRUE );
}

void CWareHouseUI::closeUI()
{
	Hide(TRUE);
	SetVisible(FALSE);

	ResetUI();
	ClearItems();

	m_fNpcPosX = 0.0f;
	m_fNpcPosZ = 0.0f;

	CUIManager* pUIMgr = UIMGR();
	pUIMgr->RearrangeOrder( UI_WARE_HOUSE, FALSE );
	pUIMgr->GetInventory()->Lock( FALSE, FALSE, LOCK_WAREHOUSE );
	
	WareHouseCloseMessageBox();
	// Character state flags
	pUIMgr->SetCSFlagOff( CSF_WAREHOUSE );
}

void CWareHouseUI::ResetUI()
{
	m_nSelWareHouseItemID	= -1;
	m_nSelTradeItemID		= -1;
	m_nTotalPrice	= 0;
	m_nInNas		= 0;
	m_nOutNas		= 0;
	m_nTotalNas		= 0;

	CTString strTemp = CTString("0");
	SetUIString(eTEXT_NAS1, strTemp);
	SetUIString(eTEXT_NAS2, strTemp);
}

void CWareHouseUI::initialize()
{
#ifndef		WORLD_EDITOR
	int i;
	// Btn
	std::string strBtnID[eBTN_MAX] = { "btn_first", "btn_second", "btn_cancel", "btn_close" };

	for (i = 0; i < eBTN_MAX; ++ i)
		m_pBtn[i] = (CUIButton*)findUI(strBtnID[i].c_str());

	if (m_pBtn[eBTN_CLOSE] != NULL)
		m_pBtn[eBTN_CLOSE]->SetCommandFUp(boost::bind(&CWareHouseUI::closeUI, this));

	if (m_pBtn[eBTN_CANCEL] != NULL)
		m_pBtn[eBTN_CANCEL]->SetCommandFUp(boost::bind(&CWareHouseUI::closeUI, this));

	if (m_pBtn[eBTN_FIRST] != NULL)
		m_pBtn[eBTN_FIRST]->SetCommandFUp(boost::bind(&CWareHouseUI::PressFirstBtn, this));

	if (m_pBtn[eBTN_SECOND] != NULL)
		m_pBtn[eBTN_SECOND]->SetCommandFUp(boost::bind(&CWareHouseUI::PressSecondBtn, this));

	// drag
	m_pMoveArea = (CUIImage*)findUI("move_area");

	// Array
	std::string strArrayID[eARRAY_MAX] = { "array_inItem", "array_userItem" };

	for (i = 0; i < eARRAY_MAX; ++i)
		m_pArray[i] = (CUIArray*)findUI(strArrayID[i].c_str());

	CUIArrayItem* pItem = NULL;
	CUIIcon* pIcon = NULL;

	for( i = 0; i < WAREHOUSE_TRADE_SLOT_TOTAL; ++i )
	{
		pIcon = GetTradeItemIcon(i);

		if (pIcon != NULL)
		{
			CmdTradeIconDBLCLK* pCmdDbk = new CmdTradeIconDBLCLK;
			pCmdDbk->setData(this, i);
			pIcon->SetCommandDBL(pCmdDbk);

			CmdTradeIconDown* pCmd = new CmdTradeIconDown;
			pCmd->setData(this, i);
			pIcon->SetCommand(pCmd);
		}			
	}
	
	// Text
	std::string strTextID[eTEXT_MAX] = { "text_usetime", "text_slotinfo", "text_nasTitle1", 
		"text_nasTitle2", "text_inputnas1", "text_inputnas2"};

	for (i = 0; i < eTEXT_MAX; ++i)
		m_pText[i] = (CUIText*)findUI(strTextID[i].c_str());

#endif		// WORLD_EDITOR
}

void CWareHouseUI::OnUpdate( float fDeltaTime, ULONG ElapsedTime )
{
	if (GetHide() == TRUE)
		return;
	
	if (m_bCashRemote == true)
		return;

	FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - m_fNpcPosX;
	FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - m_fNpcPosZ;

	if( fDiffX * fDiffX + fDiffZ * fDiffZ > UI_VALID_SQRDIST )
		closeUI();
}

static SQUAD	llTempNas = 0;

void CWareHouseUI::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	if( !bOK )
		return;

	CUIManager* pUIMgr = UIMGR();

	switch( nCommandCode )
	{
	case MSGCMD_WAREHOUSE_ADD_ITEM:
		{
			char	*pcInput	= strInput.str_String;
			int		nLength		= strInput.Length();
			int		iChar;
			for( iChar = 0; iChar < nLength; iChar++ )
			{
				if( pcInput[iChar] < '0' || pcInput[iChar] > '9' )
					break;
			}

			if( iChar == nLength )
			{
				SQUAD	llCount = _atoi64( pcInput );

				if (llCount > 0)
				{
					if (llCount > m_pItemsTemp->Item_Sum)
						llCount = m_pItemsTemp->Item_Sum;

					CItemData* pItemData = m_pItemsTemp->ItemData;

					if (llCount > pItemData->GetStack())
						llCount = pItemData->GetStack();

					WareHouseToTrade(llCount);
				} 				
			}
		}
		break;

	case MSGCMD_WAREHOUSE_ADD_PLUSITEM:
		{
			WareHouseToTrade();
		}
		break;

	case MSGCMD_WAREHOUSE_ADD_MONEY:	//2013/04/04 jeil 나스 아이템 제거 
		{
			char	*pcInput	= strInput.str_String;
			int		nLength		= strInput.Length();
			int		iChar;
			for( iChar = 0; iChar < nLength; iChar++ )
			{
				if( pcInput[iChar] < '0' || pcInput[iChar] > '9' )
					break;
			}

			if( iChar == nLength )
			{
				SQUAD	llCount = _atoi64( pcInput );
				CTString strInNas;
				//if( llCount > 0 && llCount <= llTempCount )
				if( (llCount+m_nInNas) > 0 && (llCount+m_nInNas) <= _pNetwork->MyCharacterInfo.money)
				{
					llTempNas		= llCount;
					//SendWareHouseKeepReqNas( llCount);
					m_nInNas		+= llCount;
					strInNas.PrintF( "%I64d", m_nInNas );
					pUIMgr->InsertCommaToString( strInNas );
					
					SetUIString(eTEXT_NAS1, strInNas, pUIMgr->GetNasColor(strInNas));
				}
				else
				{
					CTString strInNasError;
					strInNasError.PrintF( _S( 5911, "현재 가지고 있는 나스 보다 많은 나스를 입금 할 수 없습니다." ));		
					_pNetwork->ClientSystemMessage( strInNasError );
				}
			}
		}
		break;

	case MSGCMD_WAREHOUSE_ADD_REQ:
		{
			WareHouseToTrade();
		}
		break;

	case MSGCMD_WAREHOUSE_ERROR:
		{
		}
		break;

	case MSGCMD_WAREHOUSE_DEL_ITEM:
		{
			char	*pcInput	= strInput.str_String;
			int		nLength		= strInput.Length();
			int		iChar;
			for( iChar = 0; iChar < nLength; iChar++ )
			{
				if( pcInput[iChar] < '0' || pcInput[iChar] > '9' )
					break;
			}

			if (iChar == nLength)
			{
				SQUAD	llCount = _atoi64( pcInput );

				if (llCount > 0 && llCount <= m_pItemsTemp->Item_Sum)
					TradeToWareHouse();
			}
		}
		break;
	case MSGCMD_WAREHOUSE_TAKE_MONEY:	//2013/04/04 jeil 나스 아이템 제거 
		{
			char	*pcInput	= strInput.str_String;
			int		nLength		= strInput.Length();
			int		iChar;
			for( iChar = 0; iChar < nLength; iChar++ )
			{
				if( pcInput[iChar] < '0' || pcInput[iChar] > '9' )
					break;
			}

			if( iChar == nLength )
			{
				SQUAD	llCount = _atoi64( pcInput );
				CTString strOutNas;
				if( (llCount+m_nOutNas) > 0 && (llCount+m_nOutNas) <= m_nTotalNas )
				{
					llTempNas		= llCount;
					//SendWareHouseTakeReqNas( llCount);
					m_nOutNas		+= llCount;
					strOutNas.PrintF( "%I64d", m_nOutNas );
					pUIMgr->InsertCommaToString( strOutNas );

					SetUIString(eTEXT_NAS2, strOutNas, pUIMgr->GetNasColor(strOutNas));
				}
				else
				{
					CTString strOutNasError;
					strOutNasError.PrintF( _S( 5912, "현재 입금 되어 있는 나스 보다 많은 나스를 출금 할 수 없습니다." ));		
					_pNetwork->ClientSystemMessage( strOutNasError );
				}
			}
		}

		break;
	}
}

void CWareHouseUI::MsgBoxLCommand( int nCommandCode, int nResult )
{
	if( nCommandCode != MSGLCMD_WAREHOUSE_REQ )
		return;

	// [090527: selo] 확장팩 퀘스트 이야기 한다 처리 수정을 위한 루틴
	int iQuestIndex = -1;
	if( ciQuestClassifier < nResult )	
	{
		iQuestIndex = nResult;
		nResult = ciQuestClassifier;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch ( nResult ) 
	{
	case WAREHOUSE_IN: // 물품을 맡긴다
		{
			if (pUIManager->GetInventory()->IsLocked() == TRUE ||
				pUIManager->GetInventory()->IsLockedArrange() == TRUE)
			{
				// 이미 Lock 인 창이 있을 경우 열지 못한다.
				pUIManager->GetInventory()->ShowLockErrorMessage();
				return;
			}

			m_bStorageWareHouse			= TRUE;

			if (m_bHasPassword)
			{
				pUIManager->GetSecurity()->OpenSecurity(TRUE);
			}
			else
			{
				SendListReq(CTString(""));
			}

			// [KH_07043] 3차 도움말 관련 추가
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3313, "캐릭터의 인벤토리 창에서 창고에 보관 하고자 하는 물품을 클릭 후 창고의 하단 빈칸에 드래그 하여 올려 놓습니다."));
				pUIManager->GetHelp3()->AddHelpString(_S(3314, "보관버튼을 누르면 보관료만큼 자신의 인벤토리에서 나스가 빠져나가고 물품은 창고에 보관 됩니다."));
				pUIManager->GetHelp3()->AddHelpString(_S(3315, "※ 보관료는 맡기려는 물품 1개당 100나스 입니다."));
				pUIManager->GetHelp3()->AddHelpString(_S(3316, "※ 흰색 테두리가 둘러진 아이템은 창고에 보관이 불가능합니다."));
				pUIManager->GetHelp3()->AddHelpString(_S(3317, "※ 창고에 보관 가능한 공간은 기본 50칸이며, 창고확장카드를 사용하면 150칸으로 확장할 수 있습니다."));
				pUIManager->GetHelp3()->OpenHelp(this);
			}		
		}
		break;

	case WAREHOUSE_OUT: // 물품을 찾는다
		{
			if (pUIManager->GetInventory()->IsLocked() == TRUE ||
				pUIManager->GetInventory()->IsLockedArrange() == TRUE)
			{
				// 이미 Lock 인 창이 있을 경우 열지 못한다.
				pUIManager->GetInventory()->ShowLockErrorMessage();
				return;
			}

			m_bStorageWareHouse			= FALSE;

			if (m_bHasPassword)
			{
				pUIManager->GetSecurity()->OpenSecurity(TRUE);
			}
			else
			{
				SendListReq(CTString(""));
			}

			// [KH_07043] 3차 도움말 관련 추가
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3318, "창고에 보관된 물품 중 찾으려는 물품을 창고 창 아래의 빈칸으로 옮기고 찾기 버튼을 클릭 합니다."));
				pUIManager->GetHelp3()->AddHelpString(_S(3319, "찾은 물품은 자신의 인벤토리에 옮겨지게 됩니다."));
				pUIManager->GetHelp3()->AddHelpString(_S(3320, "※ 최대 10개의 아이템을 한번에 찾을 수 있습니다."));
				pUIManager->GetHelp3()->OpenHelp(this);
			}
		}
		break;

	case WAREHOUSE_TALK:
		{
			// 퀘스트 창 띄우기
			//pUIManager->GetQuest()->OpenQuest( pUIManager->GetCharacterInfo()->GetMobIndex(), m_fNpcX, m_fNpcZ );
			CUIQuestBook::TalkWithNPC();
		}
		break;

	case WAREHOUSE_CHANGEPW : // 암호를 변경한다.
		{
			pUIManager->CloseMessageBoxL( MSGLCMD_SECURITY_REQ );

			pUIManager->CreateMessageBoxL( _S( 1743, "창고 보안설정" ) , UI_SECURITY, MSGLCMD_SECURITY_REQ );		

			pUIManager->AddMessageBoxLString( MSGLCMD_SECURITY_REQ, TRUE, _S( 1778, "창고 보안을 위하여 암호를 설정 하실 수 있습니다." ), -1, 0xA3A1A3FF );	
			pUIManager->AddMessageBoxLString( MSGLCMD_SECURITY_REQ, TRUE, CTString("  "), -1, 0xA3A1A3FF );
			pUIManager->AddMessageBoxLString( MSGLCMD_SECURITY_REQ, TRUE, _S( 1779, "암호를 설정하면 창고를 이용할 때 설정하신 암호를 입력하여야만 창고를 이용할 수 있습니다." ), -1, 0xA3A1A3FF );	

			pUIManager->AddMessageBoxLString( MSGLCMD_SECURITY_REQ, FALSE, _S( 1780, "암호 설정" ), CUISecurity::SET_PASSWORD );
			if( m_bHasPassword )
			{
				pUIManager->AddMessageBoxLString( MSGLCMD_SECURITY_REQ, FALSE, _S( 1781, "암호 분실" ), CUISecurity::UNSET_PASSWORD );
			}
			pUIManager->AddMessageBoxLString( MSGLCMD_SECURITY_REQ, FALSE, _S( 1220, "취소한다." ) );
		}
		break;	

		// [090527: selo] 확장팩 퀘스트 수정
	case ciQuestClassifier:
		{
			// 선택한 퀘스트에 대해 수락 또는 보상 창을 연다.
			CUIQuestBook::SelectQuestFromMessageBox( iQuestIndex );					
		}
		break;

	default:
		{
			// Character state flags
			pUIManager->SetCSFlagOff( CSF_WAREHOUSE );
		}
		break;
	}
}

WMSG_RESULT CWareHouseUI::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_nMouseX = x;
	m_nMouseY = y;

	if( m_bDrag && ( pMsg->wParam & MK_LBUTTON ) )
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move( ndX, ndY );
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();
	return WMSG_FAIL;
}

WMSG_RESULT CWareHouseUI::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pMoveArea && m_pMoveArea->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	CUIManager::getSingleton()->RearrangeOrder( UI_WARE_HOUSE, TRUE );

	return WMSG_FAIL;
}

WMSG_RESULT CWareHouseUI::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if (m_pArray[eARRAY_TRADE_ITEM] && m_pArray[eARRAY_TRADE_ITEM]->IsInside(x, y))
		TradeSlotMouseLUPEvent();
	else if (m_pArray[eARRAY_WAREHOUSE_ITEM] && m_pArray[eARRAY_WAREHOUSE_ITEM]->IsInside(x, y))
		WareSlotMouseLUPEvent();

	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->ResetHoldBtn();
	return WMSG_FAIL;
}

void CWareHouseUI::SetNPCPos( int nNPCIdx, FLOAT fX, FLOAT fZ )
{
	m_fNpcPosX			= fX;
	m_fNpcPosZ			= fZ;
	m_nNpcIndex		= nNPCIdx;

	if (CEntity* pEntity = INFO()->GetTargetEntity(eTARGET))
		m_nNPCVIdx = pEntity->GetNetworkID();
}

int CWareHouseUI::GetWareHouseItemIndex( int nInvenIdx )
{
	if ( nInvenIdx > ITEM_COUNT_IN_INVENTORY_STASH || nInvenIdx < 0)
		return -1;

	CUIIcon* pIcon = GetWareHouseItemIcon(nInvenIdx);

	if (pIcon == NULL)
		return -1;
	
	return pIcon->getIndex();
}

LONGLONG CWareHouseUI::GetWareHouseItemCount( int nInvenIdx )
{
	if (nInvenIdx < 0 || nInvenIdx >= m_vectorStorageItems.size())
		return -1;

	return m_vectorStorageItems[nInvenIdx]->Item_Sum;
}

void CWareHouseUI::SendListReq( CTString& strPW )
{
	CNetworkMessage nmMessage;
	RequestClient::doStashList* packet = reinterpret_cast<RequestClient::doStashList*>(nmMessage.nm_pubMessage);
	packet->type = MSG_STASH;
	packet->subType = MSG_STASH_LIST;

#ifdef	STASH_PASSWORD
	m_strPW = strPW;
	memset(packet->password, 0, MAX_STASH_PASSWORD_LENGTH+1);
	int nSize = strPW.Length();
	if (nSize > MAX_STASH_PASSWORD_LENGTH)
		nSize = MAX_STASH_PASSWORD_LENGTH;
	memcpy(packet->password, strPW.str_String, nSize);
#endif	// STASH_PASSWORD

	nmMessage.setSize( sizeof(*packet) );

	_pNetwork->SendToServerNew( nmMessage );
}

void CWareHouseUI::ReceiveNas( CNetworkMessage *istr )
{
	UpdateClient::money* pPack = reinterpret_cast<UpdateClient::money*>(istr->GetBuffer());
	CUIManager* pUIMgr = UIMGR();
	CTString strTotalNas;

	if (pPack->subType == MSG_SUB_UPDATE_MONENY)
	{
		__int64 delta_nas = pPack->nas - m_nTotalNas;

		if (delta_nas > 0)
		{
			CTString strOutNas;
			strTotalNas.PrintF("%I64d", delta_nas);
			pUIMgr->InsertCommaToString(strTotalNas);

			strOutNas.PrintF( _S( 1346, "나스를 %s개 보관하였습니다." ), strTotalNas);		

			_pNetwork->ClientSystemMessage( strOutNas );
		}

		closeUI();
	}

	m_nTotalNas = pPack->nas;	

	strTotalNas.PrintF( "%I64d", m_nTotalNas );
	pUIMgr->InsertCommaToString( strTotalNas );

	if (m_bStorageWareHouse == FALSE)
		SetUIString(eTEXT_NAS1, strTotalNas, pUIMgr->GetNasColor(strTotalNas));
}

void CWareHouseUI::ReceiveList( CNetworkMessage *istr )
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	UpdateClient::invenList* pPack = reinterpret_cast<UpdateClient::invenList*>(istr->GetBuffer());

	for (int nList = 0; nList < pPack->count; ++nList)
	{
		UpdateClient::itemInfo* pInfo = &pPack->info_list[nList];


		CItems* pItems = new CItems(pInfo->dbIndex);
		pItems->InitOptionData();

		SBYTE opt_cnt = pInfo->option_count;

		CItemData* pItemData = CItemData::getData(pInfo->dbIndex);

		//레어 아이템이면...
		if( pItemData->GetFlag() & ITEM_FLAG_RARE )
		{
			//옵션 개수가 0이면 미감정 레어아이템
			if (opt_cnt == 0)
				pItems->SetRareIndex(0);
			//감정된 레어 아이템
			else
				pUIManager->SetRareOption(&pPack->info_list[nList], *pItems);
		}		
		else
		{
			//레어 아이템이 아니면...
			if (pItemData->GetFlag() & ITEM_FLAG_ORIGIN)
			{
				pItems->SetItemBelong( pItemData->GetItemBelong() );

				int		OpCount;

				for (OpCount = 0; OpCount < MAX_ORIGIN_OPTION; OpCount++)
				{
					pItems->SetOptionData( OpCount, pItemData->GetOptionOriginType(OpCount), 
						pItemData->GetOptionOriginLevel(OpCount), pInfo->origin_var[OpCount] );
				}

				// 아이템 스킬 세팅
				for (OpCount = 0; OpCount < MAX_ITEM_SKILL; OpCount++)
				{
					pItems->SetItemSkill(OpCount, pItemData->GetOptionSkillType(OpCount), pItemData->GetOptionSkillLevel(OpCount));
				}
			}
			else
			{
				for (int OpCount = 0; OpCount < opt_cnt; OpCount++)
				{
					pItems->SetOptionData( OpCount, pInfo->option_type[OpCount], 
						pInfo->option_level[OpCount], ORIGIN_VAR_DEFAULT );
				}
			}
		}

		//(*istr) >> useTime;
		//pUIManager->GetWareHouseUI()->SetUseTime(useTime);	//wooss 050817

		pItems->SetItemPlus2(pInfo->plus_2);
		pItems->SetData( pInfo->dbIndex, pInfo->virtualIndex, -1, -1, pInfo->plus, pInfo->flag, -1, 
			pInfo->used, pInfo->used_2, -1, pInfo->itemCount );

		pItems->SetServerIndex(pInfo->invenIndex);

		// socket system. [6/23/2010 rumist]
		pItems->InitSocketInfo();
		if( pItemData->GetFlag() & ITEM_FLAG_SOCKET )
		{
			SBYTE	sbSocketCreateCount = 0;
			int		sc;

			for (sc = 0; sc < JEWEL_MAX_COUNT; ++sc)
			{
				if (pInfo->socket[sc] >= 0)
				{
					sbSocketCreateCount++;
					pItems->SetSocketOption( sc, pInfo->socket[sc] );
				}
			}

			pItems->SetSocketCount( sbSocketCreateCount );
		}

#ifdef DURABILITY
		pItems->SetDurability(pInfo->now_durability, pInfo->max_durability);
#endif	//	DURABILITY

		m_vectorStorageItems.push_back(pItems);
	}

	if (IsVisible() == FALSE)
	{		
		pUIManager->GetInventory()->Lock( TRUE, TRUE, LOCK_WAREHOUSE );
		pUIManager->RearrangeOrder( UI_INVENTORY, TRUE );		
	}

	PrepareWareHouse();
}

void CWareHouseUI::PrepareWareHouse()
{
		CUIManager* pUIManager = CUIManager::getSingleton();

	// Already exchange
	if( pUIManager->IsCSFlagOn( CSF_EXCHANGE ) )
	{
		pUIManager->SetCSFlagOff( CSF_WAREHOUSE );
		pUIManager->GetChattingUI()->AddSysMessage( _S( 821, "교환중에는 창고를 사용할 수 없습니다." ), SYSMSG_ERROR );		
		return;
	}

	// Already personal shop
	if( pUIManager->IsCSFlagOn( CSF_PERSONALSHOP ) )
	{
		pUIManager->SetCSFlagOff( CSF_WAREHOUSE );
		pUIManager->GetChattingUI()->AddSysMessage( _S( 822, "개인 상점 사용중에는 창고를 사용할 수 없습니다." ), SYSMSG_ERROR );		
		return;
	}

	// Already shop
	if( pUIManager->IsCSFlagOn( CSF_SHOP ) )
	{
		pUIManager->SetCSFlagOff( CSF_WAREHOUSE );
		pUIManager->GetChattingUI()->AddSysMessage( _S( 807, "상점 거래중에는 창고를 사용할 수 없습니다." ), SYSMSG_ERROR );		
		return;
	}

	RefreshWareHouse();
	openUI();
}

void CWareHouseUI::RefreshWareHouse()
{
	if (m_pArray[eARRAY_WAREHOUSE_ITEM] == NULL)
		return;

	m_pArray[eARRAY_WAREHOUSE_ITEM]->ResetArray();

	CUIArrayItem* pTempItem = m_pArray[eARRAY_WAREHOUSE_ITEM]->GetArrayItemTemplate();

	if (pTempItem == NULL)
		return;

	CUIArrayItem* pItem = NULL;
	CUIIcon* pIcon = NULL;
	int t = 0;
	vec_Items_iter pos = m_vectorStorageItems.begin();
	vec_Items_iter end = m_vectorStorageItems.end();

	for (; pos != end; ++pos)
	{
		if ((*pos)->Item_Sum > 0)
		{
			m_pArray[eARRAY_WAREHOUSE_ITEM]->AddArrayItem((CUIArrayItem*)pTempItem->Clone());

			pIcon = GetWareHouseItemIcon(t);

			if (pIcon != NULL)
			{
				pIcon->setData((*pos));
				pIcon->SetWhichUI(UI_WARE_HOUSE);
				pIcon->Hide(FALSE);

				if (m_bStorageWareHouse == FALSE)
				{
					CmdDragIcon* pCmdDrag = new CmdDragIcon;
					pCmdDrag->setData(pIcon);
					pIcon->SetCommandDrag(pCmdDrag);
				}

				CmdWareHouseIconDBLCLK* pCmdDbk = new CmdWareHouseIconDBLCLK;
				pCmdDbk->setData(this, t);
				pIcon->SetCommandDBL(pCmdDbk);

				CmdWareHouseIconDown* pCmd = new CmdWareHouseIconDown;
				pCmd->setData(this, t);
				pIcon->SetCommand(pCmd);
				t++;
			}			
		}
	}

	m_pArray[eARRAY_WAREHOUSE_ITEM]->UpdateItem();
	updateUseTime();
}

void CWareHouseUI::TradeToWareHouse( SQUAD llCount /*= 1*/ )
{
	if (m_pItemsTemp == NULL)
		return;

	// Update count of trade item
	SQUAD llTrade = m_vecTradeItems[m_nTempTradeIdx]->Item_Sum - llCount;

	CUIIcon* pIcon = GetTradeItemIcon(m_nTempTradeIdx);
	CUIIcon* pIconWareHouse = GetWareHouseItemIcon(m_nTempStorageIdx);

	if (pIcon == NULL)
		return;

	if (m_bStorageWareHouse == FALSE)
	{
		if (pIconWareHouse == NULL)
			return;
	}

	pIcon->setCount(llTrade);

	if (m_vecTradeItems[m_nTempTradeIdx]->Item_Sum <= 0)
	{
		// Rearrange buttons
		for( int iArrItem = m_nTempTradeIdx; iArrItem < WAREHOUSE_TRADE_SLOT_TOTAL; iArrItem++ )
		{
			pIcon = GetTradeItemIcon(iArrItem);
			
			if (pIcon == NULL)
				continue;

			if ((iArrItem + 1) == WAREHOUSE_TRADE_SLOT_TOTAL)
			{
				pIcon->clearIconData();				
				break;
			}

			CUIIcon* pIconNext = GetTradeItemIcon(iArrItem + 1);

			if (pIconNext == NULL || pIconNext->IsEmpty())
			{
				pIcon->clearIconData();
				break;
			}

			pIcon->setData(pIconNext->getItems());
			pIcon->SetWhichUI(UI_WARE_HOUSE);

			CmdTradeIconDBLCLK* pCmdDbk = new CmdTradeIconDBLCLK;
			pCmdDbk->setData(this, iArrItem);
			pIcon->SetCommandDBL(pCmdDbk);

			CmdTradeIconDown* pCmd = new CmdTradeIconDown;
			pCmd->setData(this, iArrItem);
			pIcon->SetCommand(pCmd);

			CmdDragIcon* pCmdDrag = new CmdDragIcon;
			pCmdDrag->setData(pIcon);
			pIcon->SetCommandDrag(pCmdDrag);
		}

		if (m_bStorageWareHouse == FALSE)
		{
			// Update count of warehouse item
			if (m_nTempStorageIdx >= m_vectorStorageItems.size())
			{
				m_vectorStorageItems.push_back(m_vecTradeItems[m_nTempTradeIdx]);
			}
			else
			{
				if (m_vectorStorageItems[m_nTempStorageIdx] == NULL)
					m_vectorStorageItems[m_nTempStorageIdx] = m_vecTradeItems[m_nTempTradeIdx];
				else
					m_vectorStorageItems[m_nTempStorageIdx]->Item_Sum += m_pItemsTemp->Item_Sum;
			}

			pIconWareHouse->setData(m_vectorStorageItems[m_nTempStorageIdx]);
			pIconWareHouse->SetWhichUI(UI_WARE_HOUSE);
		}
		else
		{
			SAFE_DELETE(m_vecTradeItems[m_nTempTradeIdx]);
		}

		m_vecTradeItems.erase(m_vecTradeItems.begin() + m_nTempTradeIdx);

		// Unselect item
		if (m_nTempTradeIdx == m_nSelTradeItemID)
			m_nSelTradeItemID = -1;
	}

	if (m_bStorageWareHouse == FALSE)
	{
		SQUAD llNewCount = m_vectorStorageItems[m_nTempStorageIdx]->Item_Sum + llCount;
		pIconWareHouse->setCount(llNewCount);

		if (m_vectorStorageItems[m_nTempStorageIdx]->Item_Sum > 0)
			pIconWareHouse->Hide(FALSE);
	}

	if (m_bStorageWareHouse == TRUE)
	{
		m_nTotalPrice = CalculateStoragePrice();
		CUIManager* pUIMgr = UIMGR();
		CTString strTotalPrice;
		strTotalPrice.PrintF( "%I64d", m_nTotalPrice );
		pUIMgr->InsertCommaToString( strTotalPrice );

		SetUIString(eTEXT_NAS2, strTotalPrice, pUIMgr->GetNasColor(strTotalPrice));
	}

	m_pItemsTemp = NULL;
}

void CWareHouseUI::WareHouseToTrade( SQUAD llCount /*= 1*/ )
{
	// Find same item in trade slot
	int		iItem;
	CUIIcon* pIcon = NULL;
	CTString strTotalPrice;
	CUIManager* pUIMgr = UIMGR();

	for (iItem = 0; iItem < WAREHOUSE_TRADE_SLOT_TOTAL; iItem++)
	{
		pIcon = GetTradeItemIcon(iItem);

		if (pIcon == NULL)
			continue;

		if (pIcon->getItems() != NULL &&
			m_pItemsTemp != NULL &&
			pIcon->getItems()->Item_UniIndex == m_pItemsTemp->Item_UniIndex)
			break;
	}

	// Check if item is countable
	CItemData*	pItemData = m_pItemsTemp->ItemData;

	// If there is same item
	if (iItem < WAREHOUSE_TRADE_SLOT_TOTAL)
	{
		CItems* pItems = pIcon->getItems();

		if (pItems == NULL)
			return;

		if (pItemData->GetFlag() & ITEM_FLAG_COUNT)
		{
			// Update count of trade item
			SQUAD	llNewCount	= pItems->Item_Sum;
			llNewCount			+= llCount;

			// 인벤에 가고 있는 갯수보다 많은 갯수의 아이템을 보관하려 할때...
			if (m_bStorageWareHouse && m_nTempMax > 0)
			{
				if( llNewCount > m_nTempMax )
					llNewCount = m_nTempMax;
			}

			pIcon->setCount(llNewCount);

			if (m_bStorageWareHouse == FALSE)
			{
				// Update count of warehouse item
				llNewCount = m_vectorStorageItems[m_nTempStorageIdx]->Item_Sum;
				llNewCount -= llCount;

				CUIIcon* pIconWare = GetWareHouseItemIcon(m_nTempStorageIdx);

				if (pIconWare != NULL)
					pIconWare->setCount(llNewCount);

				if( llNewCount <= 0 )
				{
					if (pIconWare != NULL)
						pIconWare->Hide(TRUE);

					// Unselect item
					if (m_nSelWareHouseItemID == m_nTempStorageIdx)
						m_nSelWareHouseItemID = -1;
				}
			}
			else
			{
				m_nTotalPrice = CalculateStoragePrice();
				strTotalPrice.PrintF( "%I64d", m_nTotalPrice );
				pUIMgr->InsertCommaToString( strTotalPrice );

				SetUIString(eTEXT_NAS2, strTotalPrice, pUIMgr->GetNasColor(strTotalPrice));
			}

			m_pItemsTemp = NULL;
			return;
		}
		else
		{
			if(m_bStorageWareHouse)
			{
				m_nSelWareHouseItemID = -1;
				m_pItemsTemp = NULL;
				return;
			}
		}
	}
	else
	{
		// Find empty slot
		for( iItem = 0; iItem < WAREHOUSE_TRADE_SLOT_TOTAL; iItem++ )
		{
			pIcon = GetTradeItemIcon(iItem);

			if (pIcon == NULL || pIcon->IsEmpty())
				break;
		}

		// If there is not empty slot
		if( iItem == WAREHOUSE_TRADE_SLOT_TOTAL )
		{
			CTString	strMessage;

			// Add system message
			if( m_bStorageWareHouse )
				strMessage.PrintF( _S( 831, "한번에 최대 %d개의 아이템을 보관하실 수 있습니다." ), WAREHOUSE_TRADE_SLOT_TOTAL );	
			else
				strMessage.PrintF( _S( 832, "한번에 최대 %d개의 아이템을 찾으실 수 있습니다." ), WAREHOUSE_TRADE_SLOT_TOTAL );		

			pUIMgr->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_ERROR );
			return;
		}

		if (iItem <= m_vecTradeItems.size())
		{
			CItems* pNewItems = new CItems(m_pItemsTemp->Item_Index);
			m_vecTradeItems.push_back(pNewItems);
		}

		CItems* pItems = m_vecTradeItems[iItem];
		memcpy(pItems, m_pItemsTemp, sizeof(CItems));
		pIcon->setData(pItems);
		pIcon->setCount(llCount);
		pIcon->SetWhichUI(UI_WARE_HOUSE);

		CmdTradeIconDBLCLK* pCmdDbk = new CmdTradeIconDBLCLK;
		pCmdDbk->setData(this, iItem);
		pIcon->SetCommandDBL(pCmdDbk);

		CmdTradeIconDown* pCmd = new CmdTradeIconDown;
		pCmd->setData(this, iItem);
		pIcon->SetCommand(pCmd);

		CmdDragIcon* pCmdDrag = new CmdDragIcon;
		pCmdDrag->setData(pIcon);
		pIcon->SetCommandDrag(pCmdDrag);

		if (m_bStorageWareHouse == FALSE)
		{												
			// Update count of warehouse item
			SQUAD	llNewCount = m_vectorStorageItems[m_nTempStorageIdx]->Item_Sum;
			llNewCount -= llCount;

			CUIIcon* pIconWare = GetWareHouseItemIcon(m_nTempStorageIdx);

			if (pIconWare != NULL)
				pIconWare->setCount(llNewCount);

			if (llNewCount <= 0)
			{
				if (pIconWare != NULL)
					pIconWare->Hide(TRUE);

				// Unselect item
				if (m_nSelWareHouseItemID == m_nTempStorageIdx)
					m_nSelWareHouseItemID = -1;
			}
		}

		if (m_bStorageWareHouse == TRUE)
		{
			m_nTotalPrice = CalculateStoragePrice();
			strTotalPrice.PrintF( "%I64d", m_nTotalPrice );
			pUIMgr->InsertCommaToString( strTotalPrice );

			SetUIString(eTEXT_NAS2, strTotalPrice, pUIMgr->GetNasColor(strTotalPrice));
		}

		m_pItemsTemp = NULL;
	}
}

void CWareHouseUI::ClearItems()
{
	vec_Items_iter iter = m_vectorStorageItems.begin();
	vec_Items_iter eiter = m_vectorStorageItems.end();

	for (; iter != eiter; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_vectorStorageItems.clear();

	iter = m_vecTradeItems.begin();
	eiter = m_vecTradeItems.end();

	for (; iter != eiter; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_vecTradeItems.clear();

	int		i;
	CUIIcon* pIcon = NULL;
	for (i = 0; i < WAREHOUSE_TRADE_SLOT_TOTAL; ++i)
	{
		pIcon = GetTradeItemIcon(i);

		if (pIcon == NULL)
			continue;

		pIcon->clearIconData();
	}

	for (i = 0; i < ITEM_COUNT_IN_INVENTORY_STASH; ++i)
	{
		pIcon = GetWareHouseItemIcon(i);

		if (pIcon == NULL)
			continue;

		pIcon->clearIconData();
	}
}

SQUAD CWareHouseUI::CalculateStoragePrice()
{
	SQUAD llTotalPrice		= 0;
	SQUAD llItemCnt			= 0;
	const int nTax			= 100;	// 아이템 한개의 세금 100원.
	CUIIcon* pIcon			= NULL;

	for (int iItem = 0; iItem < WAREHOUSE_TRADE_SLOT_TOTAL; iItem++)
	{	
		pIcon = GetTradeItemIcon(iItem);

		if (pIcon == NULL)
			continue;

		if (pIcon->IsEmpty())
			continue;

		llItemCnt		   += m_vecTradeItems[iItem]->Item_Sum;
	}

	llTotalPrice += llItemCnt * nTax;

	return llTotalPrice;
}

void CWareHouseUI::ErrMessage( int nErr )
{
	if( CUIManager::getSingleton()->DoesMessageBoxExist( MSGCMD_NULL ) )
		return;

	CUIMsgBox_Info MsgInfo;
	MsgInfo.SetMsgBoxInfo( _S( 191, "확인" ), UMBS_OK, UI_NONE, MSGCMD_NULL );

	switch( nErr )
	{
	case eERR_KEEP_FAIL_EMPTY:
		MsgInfo.AddString( _S( 5554, "맡길 아이템이 없습니다. 확인후 다시 하시기 바랍니다.") );		
		break;
	case eERR_TAKE_FAIL_EMPTY:
		MsgInfo.AddString( _S( 5555, "찾을 아이템이 없습니다. 확인후 다시 하시기 바랍니다.") );		
		break;
	}
	CUIManager::getSingleton()->CreateMessageBox( MsgInfo );
}

void CWareHouseUI::SendWareHouseKeepReq()
{
	LONG lKeepCount = 0;
	int		i;

	CUIIcon* pIcon = NULL;

	for( i = 0; i < WAREHOUSE_TRADE_SLOT_TOTAL; ++i )
	{
		pIcon = GetTradeItemIcon(i);
		
		if (pIcon == NULL || pIcon->IsEmpty())
			continue;
		lKeepCount++;
	}

	if(m_nInNas == 0 && lKeepCount <= 0)
	{
		return;
	}

	CNetworkMessage nmMessage;
	RequestClient::doStashKeep* packet = reinterpret_cast<RequestClient::doStashKeep*>(nmMessage.nm_pubMessage);
	packet->type = MSG_STASH;
	packet->subType = MSG_STASH_KEEP;
#ifdef	STASH_PASSWORD
	memset(packet->password, 0, MAX_STASH_PASSWORD_LENGTH+1);
	int nSize = m_strPW.Length();
	if (nSize > MAX_STASH_PASSWORD_LENGTH)
		nSize = MAX_STASH_PASSWORD_LENGTH;
	memcpy(packet->password, m_strPW.str_String, nSize);
#endif	// STASH_PASSWORD
	packet->npcKind = m_nNPCVIdx;
	packet->keepMoney = m_nInNas;
	packet->keepCount = lKeepCount;

	for (i = 0; i < lKeepCount; ++i)
	{
		SWORD nTab		= m_vecTradeItems[i]->Item_Tab;
		SWORD nIdx		= m_vecTradeItems[i]->InvenIndex;
		LONG lIndex		= m_vecTradeItems[i]->Item_UniIndex;
		int  nCnt		= (int)m_vecTradeItems[i]->Item_Sum;

		packet->list[i].tab = nTab;
		packet->list[i].invenIndex = nIdx;
		packet->list[i].virtualIndex = lIndex;
		packet->list[i].count = nCnt;
	}

	nmMessage.setSize( sizeof(*packet) + (sizeof(packet->list[0]) * lKeepCount) );

	_pNetwork->SendToServerNew( nmMessage );
}

void CWareHouseUI::SendWareHouseTakeReq()
{
	LONG lTakeCount = 0;
	int		i;
	CUIIcon* pIcon = NULL;

	for( i = 0; i < WAREHOUSE_TRADE_SLOT_TOTAL; ++i )
	{
		pIcon = GetTradeItemIcon(i);

		if (pIcon == NULL || pIcon->IsEmpty())
			continue;
		lTakeCount++;
	}

	if(m_nOutNas == 0 && lTakeCount <= 0)
	{
		return;
	}

	// 찾기 요청				: password(str) takecount(n) [item_idx(n) count(ll)]:takecount
	CNetworkMessage nmMessage;
	RequestClient::doStashTake* packet = reinterpret_cast<RequestClient::doStashTake*>(nmMessage.nm_pubMessage);
	packet->type = MSG_STASH;
	packet->subType = MSG_STASH_TAKE;
#ifdef	STASH_PASSWORD
	memset(packet->password, 0, MAX_STASH_PASSWORD_LENGTH+1);
	int nSize = m_strPW.Length();
	if (nSize > MAX_STASH_PASSWORD_LENGTH)
		nSize = MAX_STASH_PASSWORD_LENGTH;
	memcpy(packet->password, m_strPW.str_String, nSize);
#endif	// STASH_PASSWORD
	packet->npcKind = m_nNPCVIdx;
	packet->takeMoney = m_nOutNas;
	packet->takeCount = lTakeCount;

	for (i = 0; i < lTakeCount; ++i)
	{		
		SWORD nIdx		= m_vecTradeItems[i]->GetServerIndex();
		LONG lIndex		= m_vecTradeItems[i]->Item_UniIndex;
		int  nCnt		= (int)m_vecTradeItems[i]->Item_Sum;

		packet->list[i].invenIndex = nIdx;
		packet->list[i].virtualIndex = lIndex;
		packet->list[i].count = nCnt;
	}

	nmMessage.setSize( sizeof(*packet) + (sizeof(packet->list[0]) * lTakeCount) );

	_pNetwork->SendToServerNew( nmMessage );
}

CUIIcon* CWareHouseUI::GetTradeItemIcon( int nIdx )
{
	if (nIdx < 0 || nIdx >= WAREHOUSE_TRADE_SLOT_TOTAL)
		return NULL;

	if (m_pArray[eARRAY_TRADE_ITEM] == NULL)
		return NULL;

	CUIArrayItem* pItem = m_pArray[eARRAY_TRADE_ITEM]->GetArrayItem(nIdx);

	if (pItem == NULL)
		return NULL;

	return (CUIIcon*)pItem->findUI("icon_item");
}

CUIIcon* CWareHouseUI::GetWareHouseItemIcon( int nIdx )
{
	if (nIdx < 0 || nIdx >= (WAREHOUSE_WAREHOUSE_SLOT_COL * WAREHOUSE_WAREHOUSE_SLOT_ROW_TOTAL))
		return NULL;

	if (m_pArray[eARRAY_WAREHOUSE_ITEM] == NULL)
		return NULL;

	CUIArrayItem* pItem = m_pArray[eARRAY_WAREHOUSE_ITEM]->GetArrayItem(nIdx);

	if (pItem == NULL)
		return NULL;

	return (CUIIcon*)pItem->findUI("icon_item");
}

void CWareHouseUI::SetUIString( int nStringType, CTString strContents, COLOR col /*= 0xF2F2F2FF*/ )
{
	if (nStringType < 0 || nStringType >= eTEXT_MAX)
		return;

	if (m_pText[nStringType] == NULL)
		return;

	m_pText[nStringType]->SetText(strContents);
	m_pText[nStringType]->setFontColor(col);
}

void CWareHouseUI::updateUseTime()
{
	if (m_pText[eTEXT_USETIME] == NULL)
		return;
	
	CTString tv_str = CTString("");
	int nMaxSlot = WAREHOUSE_DEFUALT_MAX_SLOT;

	if (m_useTime > 0)
	{
		tm* pTime = NULL;
		pTime = localtime((time_t*)&m_useTime);

		tv_str.PrintF(  _S( 6070,"만료 : %d년%d월%d일%d시%d분"),pTime->tm_year + 1900
			,pTime->tm_mon + 1,pTime->tm_mday,pTime->tm_hour, pTime->tm_min);

		nMaxSlot = WAREHOUSE_CASHUSE_MAX_SLOT;
	}
	
	SetUIString(eTEXT_USETIME, tv_str);
	
	tv_str.PrintF("(%d / %d)", m_vectorStorageItems.size(), nMaxSlot);
	SetUIString(eTEXT_SLOTINFO, tv_str);
}

void CWareHouseUI::SetUI()
{
	CTString strNasTitle1;
	CTString strNasTitle2;
	CTString strBtn1;
	CTString strBtn2;

	if (m_bStorageWareHouse == TRUE)
	{
		strNasTitle1.PrintF(_S( 5908, "입금 금액" ));
		strNasTitle2.PrintF(_S( 824, "보관료" ));
		strBtn1.PrintF(_S( 5906, "입금" ));
		strBtn2.PrintF(_S( 812, "보관" ));		
	}
	else
	{
		strNasTitle1.PrintF(_S( 5909, "보관 금액" ));
		strNasTitle2.PrintF(_S( 5910, "출금 금액" ));
		strBtn1.PrintF(_S( 5907, "출금" ));
		strBtn2.PrintF(_S( 813, "찾기" ));	
	}
	// Nas Title
	SetUIString(eTEXT_NASTITLE1, strNasTitle1);
	SetUIString(eTEXT_NASTITLE2, strNasTitle2);

	// Btn
	if (m_pBtn[eBTN_FIRST] != NULL)
		m_pBtn[eBTN_FIRST]->SetText(strBtn1);

	if (m_pBtn[eBTN_SECOND] != NULL)
		m_pBtn[eBTN_SECOND]->SetText(strBtn2);
}

void CWareHouseUI::WareHouseCloseMessageBox()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close message box of warehouse
	pUIManager->CloseMessageBox(MSGCMD_WAREHOUSE_ADD_ITEM);
	pUIManager->CloseMessageBox(MSGCMD_WAREHOUSE_DEL_ITEM);
	pUIManager->CloseMessageBox(MSGCMD_WAREHOUSE_ADD_PLUSITEM);
	pUIManager->CloseMessageBox(MSGCMD_WAREHOUSE_ADD_MONEY);
	pUIManager->CloseMessageBox(MSGCMD_WAREHOUSE_TAKE_MONEY);
	pUIManager->GetMsgBoxNumOnly()->CloseBox();
}
