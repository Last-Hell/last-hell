/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#ifndef _Counter_INCLUDED
#define _Counter_INCLUDED 1
#include <EntitiesMP/ModelHolder2.h>
extern "C" DECL_DLL CDLLEntityClass CCounter_DLLClass;
class CCounter : public CRationalEntity {
public:
virtual const CTString &GetName(void) const { return m_strName; };
virtual BOOL IsTargetable(void) const { return TRUE; };
virtual BOOL IsImportant(void) const { return TRUE; };
	DECL_DLL virtual void SetDefaultProperties(void);
	FLOAT m_fCountdownSpeed;
	CEntityPointer m_penTarget;
	FLOAT m_fNumber;
	FLOAT m_tmStart;
	CTString m_strName;
	CSoundObject m_soSound;
	INDEX m_iCountFrom;
	CEntityPointer m_pen0;
	CEntityPointer m_pen1;
	CEntityPointer m_pen2;
	CEntityPointer m_pen3;
	CEntityPointer m_pen4;
	CEntityPointer m_pen5;
	CEntityPointer m_pen6;
	CEntityPointer m_pen7;
	CEntityPointer m_pen8;
	CEntityPointer m_pen9;
   
#line 38 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/Counter.es"
void Precache(void);
   
#line 44 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/Counter.es"
void DisplayNumber(void);
#define  STATE_CCounter_Main 1
	BOOL 
#line 72 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/Counter.es"
Main(const CEntityEvent &__eeInput);
	BOOL H0x00e80000_Main_01(const CEntityEvent &__eeInput);
	BOOL H0x00e80001_Main_02(const CEntityEvent &__eeInput);
	BOOL H0x00e80002_Main_03(const CEntityEvent &__eeInput);
	BOOL H0x00e80003_Main_04(const CEntityEvent &__eeInput);
#define  STATE_CCounter_CountDown 0x00e80004
	BOOL 
#line 108 "C:/Users/djcyb/Desktop/BAckups/Reco_Csrc/EntitiesMP/Counter.es"
CountDown(const CEntityEvent &__eeInput);
	BOOL H0x00e80005_CountDown_01(const CEntityEvent &__eeInput);
	BOOL H0x00e80006_CountDown_02(const CEntityEvent &__eeInput);
	BOOL H0x00e80007_CountDown_03(const CEntityEvent &__eeInput);
	BOOL H0x00e80008_CountDown_04(const CEntityEvent &__eeInput);
};
#endif // _Counter_INCLUDED
