#include <rw.h>
#include <skeleton.h>
#include <assert.h>

#include <rwgta.h>
#define PS2

using namespace std;
using rw::int8;
using rw::uint8;
using rw::int16;
using rw::uint16;
using rw::int32;
using rw::uint32;
using rw::float32;
using rw::bool32;

struct ObjectInst;

#include "Pad.h"
#include "camera.h"
#include "collision.h"

void panic(const char *fmt, ...);
void debug(const char *fmt, ...);
void log(const char *fmt, ...);

char *getPath(const char *path);
FILE *fopen_ci(const char *path, const char *mode);

void plCapturePad(int arg);
void plUpdatePad(CControllerState *state);

void ConvertTxd(rw::TexDictionary *txd);

extern float timeStep;


// These don't necessarily match the game's values, roughly double of SA PC
enum {
	MODELNAMELEN = 30,
	NUMOBJECTDEFS = 40000,
	NUMTEXDICTS = 10000,
	NUMCOLS = 510,
	NUMSCENES = 80,
	NUMIPLS = 512,
	NUMCDIMAGES = 100,
};

#include "Rect.h"
#include "PtrNode.h"
#include "PtrList.h"

// Game

enum eGame
{
	GAME_NA,
	GAME_III,
	GAME_VC,
	GAME_SA,
};
extern int gameversion;
inline bool isIII(void) { return gameversion == GAME_III; }
inline bool isVC(void) { return gameversion == GAME_VC; }
inline bool isSA(void) { return gameversion == GAME_SA; }

extern int gameTxdSlot;

extern int currentHour;
extern int currentWeather;
extern int currentArea;

bool IsHourInRange(int h1, int h2);
void FindVersion(void);
void LoadGame(void);
void Idle(void);
void DefinedState(void);

// Game Data structures

void AddCdImage(const char *path);
void InitCdImages(void);
uint8 *ReadFileFromImage(int i, int *size);
void RequestObject(int id);
void LoadAllRequestedObjects(void);


struct TxdDef
{
	char name[MODELNAMELEN];
	rw::TexDictionary *txd;
	int parentId;
	int imageIndex;
};
extern rw::TexDictionary *defaultTxd;
void RegisterTexStorePlugin(void);
TxdDef *GetTxdDef(int i);
int AddTxdSlot(const char *name);
bool IsTxdLoaded(int i);
void CreateTxd(int i);
void LoadTxd(int i);
void TxdMakeCurrent(int i);
void TxdSetParent(const char *child, const char *parent);


struct ColFileHeader
{
	uint32 fourcc;
	uint32 modelsize;
	char name[24];
};

struct ColDef
{
	char name[MODELNAMELEN];
	int imageIndex;
};
ColDef *GetColDef(int i);
int AddColSlot(const char *name);
void LoadCol(int slot);
void LoadAllCollisions(void);

// One class for all map objects
struct ObjectDef
{
	enum Type {
		ATOMIC,
		CLUMP
	};

	int m_id;	// our own id
	char m_name[MODELNAMELEN];
	int m_txdSlot;
	int m_type;
	CColModel *m_colModel;

	// flags
	bool m_normalCull;	// only III
	bool m_noFade;
	bool m_drawLast;
	bool m_additive;
	bool m_isSubway;	// only III?
	bool m_ignoreLight;
	bool m_noZwrite;
	// VC
	bool m_wetRoadReflection;
	bool m_noShadows;
	bool m_ignoreDrawDist;	// needs a better name perhaps
	bool m_isCodeGlass;
	bool m_isArtistGlass;
	// SA Base
	bool m_noBackfaceCulling;
	// SA Atomic
	bool m_dontCollideWithFlyer;
	bool m_isGarageDoor;
	bool m_isDamageable;
	bool m_isTree;
	bool m_isPalmTree;
	bool m_isTag;
	bool m_noCover;
	bool m_wetOnly;
	// SA Clump
	bool m_isDoor;

	// atomic info
	int m_numAtomics;
	float m_drawDist[3];
	rw::Atomic *m_atomics[3];
	// time objects
	bool m_isTimed;
	int m_timeOn, m_timeOff;

	// clump info
	rw::Clump *m_clump;
	char m_animname[MODELNAMELEN];

	bool m_cantLoad;
	int m_imageIndex;
	float m_minDrawDist;
	bool m_isBigBuilding;
	bool m_isHidden;
	ObjectDef *m_relatedModel;
	ObjectDef *m_relatedTimeModel;

	float GetLargestDrawDist(void);
	rw::Atomic *GetAtomicForDist(float dist);
	bool IsLoaded(void);
	void LoadAtomic(void);
	void LoadClump(void);
	void Load(void);
	void SetAtomic(int n, rw::Atomic *atomic);
	void SetClump(rw::Clump *clump);
	void CantLoad(void);
	void SetupBigBuilding(void);
	void SetFlags(int flags);
};
ObjectDef *AddObjectDef(int id);
ObjectDef *GetObjectDef(int id);
ObjectDef *GetObjectDef(const char *name, int *id);


struct FileObjectInstance
{
	rw::V3d position;
	rw::Quat rotation;
	int objectId;
	int area;
	int lod;
};

struct ObjectInst
{
	rw::V3d m_translation;
	rw::Quat m_rotation;
	// cached form of the above
	rw::Matrix m_matrix;
	int m_objectId;
	int m_area;

	void *m_rwObject;
	bool m_isBigBuilding;
	uint16 m_scanCode;

	// SA only
	int m_lodId;
	int m_iplSlot;
	ObjectInst *m_lod;
	int m_numChildren;	// hq versions
	int m_numChildrenRendered;
	// SA flags
	bool m_isUnimportant;
	bool m_isUnderWater;
	bool m_isTunnel;
	bool m_isTunnelTransition;

	void UpdateMatrix(void);
	void *CreateRwObject(void);
	void Init(FileObjectInstance *fi);
	void SetupBigBuilding(void);
	CRect GetBoundRect(void);
	bool IsOnScreen(void);
};
extern CPtrList instances;
ObjectInst *AddInstance(void);

// World/sectors

struct Sector
{
	CPtrList buildings;
	CPtrList buildings_overlap;
	CPtrList bigbuildings;
	CPtrList bigbuildings_overlap;
};
extern int numSectorsX, numSectorsY;
extern CRect worldBounds;
extern Sector *sectors;
extern Sector outOfBoundsSector;
void InitSectors(void);
Sector *GetSector(int ix, int iy);
//Sector *GetSector(float x, float y);
int GetSectorIndexX(float x);
int GetSectorIndexY(float x);
bool IsInstInBounds(ObjectInst *inst);
void InsertInstIntoSectors(ObjectInst *inst);


struct IplDef
{
	char name[MODELNAMELEN];
	int instArraySlot;

	int imageIndex;
};
int AddInstArraySlot(int n);
ObjectInst **GetInstArray(int i);
IplDef *GetIplDef(int i);
int AddIplSlot(const char *name);
void LoadIpl(int i);

// File Loader

namespace FileLoader {

struct DatDesc
{
	char name[5];
	void (*handler)(char *line);

	static void *get(DatDesc *desc, const char *name);
};

void LoadLevel(const char *filename);
}

// Rendering

struct SceneGlobals {
	rw::World *world;
	rw::Camera *camera;
};
extern rw::Light *pAmbient, *pDirect;
extern SceneGlobals Scene;
extern CCamera TheCamera;

void BuildRenderList(void);
void RenderEverything(void);

void RenderColModelWire(CColModel *col, rw::Matrix *xform, bool onlyBounds);
void RenderEverythingCollisions(void);
void RenderDebugLines(void);
