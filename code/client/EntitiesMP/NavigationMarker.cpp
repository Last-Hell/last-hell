/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#line 2 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"

#include "StdH.h"
#include "EntitiesMP/Common/PathFinding.h"

#define MAX_TARGETS 6

#include <NavigationMarker.h>
#include <NavigationMarker_tables.h>
#line 11 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"

// info structure
static EntityInfo eiMarker = {
  EIBT_ROCK, 10.0f,
  0.0f, 1.0f, 0.0f,     // source (eyes)
  0.0f, 1.0f, 0.0f,     // target (body)
};


void CNavigationMarker::SetDefaultProperties(void) {
	m_strName = "Marker";
	m_fMarkerRange = 1.0f;
	m_penTarget0 = NULL;
	m_penTarget1 = NULL;
	m_penTarget2 = NULL;
	m_penTarget3 = NULL;
	m_penTarget4 = NULL;
	m_penTarget5 = NULL;
	CEntity::SetDefaultProperties();
}
 CNavigationMarker::CNavigationMarker(void) 
#line 47 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
{
#line 48 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
m_ppnNode  = NULL ;
#line 49 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
 CNavigationMarker:: ~ CNavigationMarker(void) 
#line 51 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
{
#line 52 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
ASSERT  (m_ppnNode  == NULL );
#line 53 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 56 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
void CNavigationMarker::Read_t(CTStream * istr,BOOL bNetwork) 
#line 57 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
{
#line 58 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CEntity  :: Read_t  (istr  , bNetwork );
#line 59 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
m_ppnNode  = NULL ;
#line 60 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 62 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CEntity * CNavigationMarker::GetTarget(void)const {return m_penTarget0 ;}

#line 65 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
void * CNavigationMarker::GetEntityInfo(void) {
#line 66 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return & eiMarker ;
#line 67 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 70 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CPathNode * CNavigationMarker::GetPathNode(void) 
#line 71 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
{
#line 72 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
if(m_ppnNode  == NULL ){
#line 73 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
m_ppnNode  = new  CPathNode  (this );
#line 74 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 76 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return m_ppnNode ;
#line 77 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 79 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CEntityPointer & CNavigationMarker::TargetPointer(INDEX i) 
#line 80 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
{
#line 81 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
ASSERT  (i  >= 0 && i  < MAX_TARGETS );
#line 82 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return (& m_penTarget0 ) [ i  ];
#line 83 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 84 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CNavigationMarker & CNavigationMarker::Target(INDEX i) 
#line 85 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
{
#line 86 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return (CNavigationMarker  &) * TargetPointer  (i );
#line 87 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 90 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CNavigationMarker * CNavigationMarker::GetLink(INDEX i) 
#line 91 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
{
#line 92 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
for(INDEX iTarget  = 0;iTarget  < MAX_TARGETS ;iTarget  ++){
#line 93 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CNavigationMarker  * penLink  = & Target  (iTarget );
#line 94 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
if(penLink  == NULL ){
#line 95 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
continue ;
#line 96 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 97 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
if(iTarget  == i ){
#line 98 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return penLink ;
#line 99 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 100 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 101 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return NULL ;
#line 102 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 104 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
const CTString & CNavigationMarker::GetDescription(void)const {
#line 105 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return m_strName ;
#line 106 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 109 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
BOOL CNavigationMarker::MovesByTargetedRoute(CTString & strTargetProperty)const {
#line 110 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
strTargetProperty  = "Target 0";
#line 111 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return TRUE ;
#line 112 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}

#line 114 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
BOOL CNavigationMarker::DropsMarker(CTFileName & fnmMarkerClass,CTString & strTargetProperty)const {
#line 115 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
fnmMarkerClass  = CTFILENAME  ("Classes\\NavigationMarker.ecl");
#line 116 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
strTargetProperty  = "Target 0";
#line 117 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return TRUE ;
#line 118 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
BOOL CNavigationMarker::IsMarker(void)const {
#line 121 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return TRUE ;
#line 122 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
BOOL CNavigationMarker::
#line 125 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
Main(const CEntityEvent &__eeInput) {
#undef STATE_CURRENT
#define STATE_CURRENT STATE_CNavigationMarker_Main
	ASSERTMSG(__eeInput.ee_slEvent==EVENTCODE_EVoid, "CNavigationMarker::Main expects 'EVoid' as input!");	const EVoid &e = (const EVoid &)__eeInput;
#line 126 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
InitAsEditorModel  ();
#line 127 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
SetPhysicsFlags  (EPF_MODEL_IMMATERIAL );
#line 128 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
SetCollisionFlags  (ECF_IMMATERIAL );
#line 131 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
const FLOAT fSize  = 0.25f;
#line 132 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
GetModelObject  () -> StretchModel  (FLOAT3D (fSize  , fSize  , fSize ));
#line 133 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
SetModel  (MODEL_MARKER );
#line 134 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
ModelChangeNotify  ();
#line 135 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
SetModelMainTexture  (TEXTURE_MARKER );
#line 138 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
for(INDEX iTarget  = 0;iTarget  < MAX_TARGETS ;iTarget  ++){
#line 139 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CEntityPointer & penTarget  = TargetPointer  (iTarget );
#line 140 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
if(penTarget  == NULL ){
#line 141 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
continue ;
#line 142 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 145 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
if(! IsOfClass  (penTarget  , & CNavigationMarker_DLLClass )){
#line 147 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
penTarget  = NULL ;
#line 148 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
continue ;
#line 149 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 151 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CNavigationMarker  & nmOther  = (CNavigationMarker  &) * penTarget ;
#line 154 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
BOOL bFound  = FALSE ;
#line 155 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
for(INDEX iTarget2  = 0;iTarget2  < MAX_TARGETS ;iTarget2  ++){
#line 156 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CEntityPointer & penTarget2  = nmOther  . TargetPointer  (iTarget2 );
#line 157 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
if(penTarget2  == this ){
#line 158 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
bFound  = TRUE ;
#line 159 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
break ;
#line 160 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 161 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 163 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
if(! bFound ){
#line 165 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
for(INDEX iTarget2  = 0;iTarget2  < MAX_TARGETS ;iTarget2  ++){
#line 166 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
CEntityPointer & penTarget2  = nmOther  . TargetPointer  (iTarget2 );
#line 167 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
if(penTarget2  == NULL ){
#line 168 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
penTarget2  = this ;
#line 169 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
break ;
#line 170 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 171 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 172 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 173 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
}
#line 175 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
Return(STATE_CURRENT,EVoid());
#line 175 "F:/SD-Source/mandra/Reco_Csrc/EntitiesMP/NavigationMarker.es"
return TRUE; ASSERT(FALSE); return TRUE;};