#ifndef _COLLISION_H_
#define _COLLISION_H_

struct CColSphere
{
	CVector center;
	float radius;
	uint8 surface;
	uint8 piece;

	void Set(float radius, const CVector &center, uint8 surf, uint8 piece);
	void Set(float radius, const CVector &center);
};

struct CColBox
{
	CVector min;
	CVector max;
	uint8 surface;
	uint8 piece;

	void Set(const CVector &min, const CVector &max, uint8 surf, uint8 piece);
};

struct CColLine
{
	CVector p0;
	int pad0;
	CVector p1;
	int pad1;

	void Set(const CVector &p0, const CVector &p1);
};

struct CColTriangle
{
	uint16 a;
	uint16 b;
	uint16 c;
	uint8 surface;

	void Set(int a, int b, int c, uint8 surf);
};

struct CColTrianglePlane
{
	CVector normal;
	float dist;
	uint8 dir;

	void Set(const CVector *v, CColTriangle &tri);
	void GetNormal(CVector &n) const { n = normal; }
	float CalcPoint(const CVector &v) const { return DotProduct(normal, v) - dist; };
};

struct CColPoint
{
	CVector point;
	int pad1;
	// the surface normal on the surface of point
	CVector normal;
	int pad2;
	uint8 surfaceA;
	uint8 pieceA;
	uint8 surfaceB;
	uint8 pieceB;
	float depth;
};

struct CStoredCollPoly
{
	CVector verts[3];
	bool valid;
};

struct CColModel
{
	CColSphere boundingSphere;
	CColBox boundingBox;
	short numSpheres;
	short numLines;
	short numBoxes;
	short numTriangles;
	int level;
	bool ownsCollisionVolumes;
	CColSphere *spheres;
	CColLine *lines;
	CColBox *boxes;
	CVector *vertices;
	CColTriangle *triangles;
	CColTrianglePlane *trianglePlanes;

	CColModel(void);
	~CColModel(void);
	void RemoveCollisionVolumes(void);
	void CalculateTrianglePlanes(void);
	void RemoveTrianglePlanes(void);
	CLink<CColModel*> *GetLinkPtr(void);
	void SetLinkPtr(CLink<CColModel*>*);
};

class CCollision
{
public:
	static eLevelName ms_collisionInMemory;
	static CLinkList<CColModel*> ms_colModelCache;

	static void Init(void);
	static void Update(void);
	static void LoadCollisionWhenINeedIt(bool changeLevel);
	static void DrawColModel(const CMatrix &mat, const CColModel &colModel);

	static void CalculateTrianglePlanes(CColModel *model);

	// all these return true if there's a collision
	static bool TestSphereSphere(const CColSphere &s1, const CColSphere &s2);
	static bool TestSphereBox(const CColSphere &sph, const CColBox &box);
	static bool TestLineBox(const CColLine &line, const CColBox &box);
	static bool TestVerticalLineBox(const CColLine &line, const CColBox &box);
	static bool TestLineTriangle(const CColLine &line, const CVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane);
	static bool TestLineSphere(const CColLine &line, const CColSphere &sph);
	static bool TestSphereTriangle(const CColSphere &sphere, const CVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane);
	static bool TestLineOfSight(CColLine &line, const CMatrix &matrix, CColModel &model, bool ignoreSurf78);

	static bool ProcessSphereSphere(const CColSphere &s1, const CColSphere &s2, CColPoint &point, float &mindistsq);
	static bool ProcessSphereBox(const CColSphere &sph, const CColBox &box, CColPoint &point, float &mindistsq);
	static bool ProcessLineBox(const CColLine &line, const CColBox &box, CColPoint &point, float &mindist);
	static bool ProcessVerticalLineTriangle(const CColLine &line, const CVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane, CColPoint &point, float &mindist, CStoredCollPoly *poly);
	static bool ProcessLineTriangle(const CColLine &line , const CVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane, CColPoint &point, float &mindist);
	static bool ProcessLineSphere(const CColLine &line, const CColSphere &sphere, CColPoint &point, float &mindist);
	static bool ProcessSphereTriangle(const CColSphere &sph, const CVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane, CColPoint &point, float &mindistsq);
	static bool ProcessLineOfSight(const CColLine &line, const CMatrix &matrix, CColModel &model, CColPoint &point, float &mindist, bool ignoreSurf78);
	static bool ProcessVerticalLine(const CColLine &line, const CMatrix &matrix, CColModel &model, CColPoint &point, float &mindist, bool ignoreSurf78, CStoredCollPoly *poly);
	static int32 ProcessColModels(const CMatrix &matrix1, CColModel &model1, const CMatrix &matrix2, CColModel &model2, CColPoint *point1, CColPoint *point2, float *linedists);

	static float DistToLine(const CVector *l0, const CVector *l1, const CVector *point);
	static float DistToLine(const CVector *l0, const CVector *l1, const CVector *point, CVector &closest);
};

#endif
