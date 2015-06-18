#pragma once
#include "PHYSICS.h"
#include "btBulletDynamicsCommon.h"

#include "LinearMath/btHashMap.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"

#include "BulletSoftBody/btSoftBodySolvers.h"
#include "BulletSoftBody/btDefaultSoftBodySolver.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"

struct RAY;

class BULLET:public PHYSICS
{
private:
	btCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	btSoftBodySolver* softBodySolver;
	btSoftBodySolverOutput* softBodySolverOutput;

	btVector3 wind;

	static bool grab;
	static RAY grabRay;
public:
	BULLET();
	~BULLET();

	void addWind(const XMFLOAT3& wind);

	void addBox(const XMFLOAT3& sca, const XMFLOAT4& rot, const XMFLOAT3& pos
		, const float& newMass, const float& newFriction, const float& newRestitution, const float& newDamping, bool kinematic);
	void addSphere(const float& rad, const XMFLOAT3& pos
		, const float& newMass, const float& newFriction, const float& newRestitution, const float& newDamping, bool kinematic);
	void addCapsule(const float& rad, const float& hei, const XMFLOAT4& rot, const XMFLOAT3& pos
		, const float& newMass, const float& newFriction, const float& newRestitution, const float& newDamping, bool kinematic);
	void addConvexHull(const vector<SkinnedVertex>& vertices, const XMFLOAT3& sca, const XMFLOAT4& rot, const XMFLOAT3& pos
		, const float& newMass, const float& newFriction, const float& newRestitution, const float& newDamping, bool kinematic);
	void addTriangleMesh(const vector<SkinnedVertex>& vertices, const vector<unsigned int>& indices, const XMFLOAT3& sca, const XMFLOAT4& rot, const XMFLOAT3& pos
		, const float& newMass, const float& newFriction, const float& newRestitution, const float& newDamping, bool kinematic);
	
	void addSoftBodyTriangleMesh(const Mesh* mesh, const XMFLOAT3& sca, const XMFLOAT4& rot, const XMFLOAT3& pos
		, const float& newMass, const float& newFriction, const float& newRestitution, const float& newDamping);

	void addBone(const float& rad, const float& hei);
	
	void connectVerticesToSoftBody(Mesh* const mesh, int objectI);
	void connectSoftBodyToVertices(const Mesh*  const mesh, int objectI);
	void transformBody(const XMFLOAT4& rot, const XMFLOAT3& pos, int objectI);

	Transform* getObject(int index);

	void registerObject(Object* object);

	void Update();
	void MarkForRead();
	void UnMarkForRead();
	void MarkForWrite();
	void UnMarkForWrite();
	void ClearWorld();
	void CleanUp();

	
	void* operator new(size_t);
	void operator delete(void*);

	void setGrab(bool val, const RAY& ray);
	static void pickingPreTickCallback (btDynamicsWorld *world, btScalar timeStep);
	static void soundTickCallback(btDynamicsWorld *world, btScalar timeStep);
};

