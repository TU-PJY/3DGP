#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"



CScene::CScene(CPlayer* pPlayer) {
	m_pPlayer = pPlayer;
}



CScene::~CScene() {}



void CScene::BuildObjects() {
	//CExplosiveObject::PrepareExplosion();
	
	// 벽을 만드는 코드
	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 200.0f;

	// 벽이 가지는 매쉬
	CWallMesh* pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 30);

	// 벽 객체
	m_pWallsObject = new CWallsObject();

	m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pWallsObject->SetMesh(pWallCubeMesh);
	m_pWallsObject->SetColor(RGB(0, 0, 0));

	m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
	m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);

	m_pWallsObject->m_xmOOBBPlayerMoveCheck = 
		BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), 
							XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.05f), 
							XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));


	// 적 기체
	CAirplaneMesh* airplaneMesh = new CAirplaneMesh(6.0, 6.0, 1.0);

	for (int i = 0; i < 5; ++i) {
		m_airplane_object[i] = new CAirplaneObject();

		m_airplane_object[i]->SetPosition(-30.0f + i * 15, 0.0f, 20.0f);
		m_airplane_object[i]->SetMesh(airplaneMesh);
		m_airplane_object[i]->Rotate(-90.0, 0.0, 0.0);
		m_airplane_object[i]->SetColor(RGB(255, 0, 0));
	}

	// 과제를 위해 큐브를 제거함
	//// 
	//// 공중에 떠다니는 큐브가 가지는 메쉬
	//CCubeMesh* pCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f); // -> setMesh를 통해 공중을 떠다니는 큐브들에 메쉬 삽입

	//// 공중에 떠다니는 큐브 10개
	//// 아래의 코드들은 모두 공중에 떠다니는 큐브를 생성하고 세팅하는 코드인듯?
	//m_nObjects = 10;
	//m_ppObjects = new CGameObject * [m_nObjects];

	//
	//CExplosiveObject* pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(255, 0, 0));
	//pExplosiveObject->SetPosition(-13.5f, 0.0f, -14.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	//pExplosiveObject->SetRotationSpeed(90.0f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	//pExplosiveObject->SetMovingSpeed(10.5f);
	//m_ppObjects[0] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(0, 0, 255));
	//pExplosiveObject->SetPosition(+13.5f, 0.0f, -14.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	//pExplosiveObject->SetRotationSpeed(180.0f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	//pExplosiveObject->SetMovingSpeed(8.8f);
	//m_ppObjects[1] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(0, 255, 0));
	//pExplosiveObject->SetPosition(0.0f, +5.0f, 20.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	//pExplosiveObject->SetRotationSpeed(30.15f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
	//pExplosiveObject->SetMovingSpeed(5.2f);
	//m_ppObjects[2] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(0, 255, 255));
	//pExplosiveObject->SetPosition(0.0f, 0.0f, 0.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	//pExplosiveObject->SetRotationSpeed(40.6f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	//pExplosiveObject->SetMovingSpeed(20.4f);
	//m_ppObjects[3] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(128, 0, 255));
	//pExplosiveObject->SetPosition(10.0f, 0.0f, 0.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pExplosiveObject->SetRotationSpeed(50.06f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(0.0f, 1.0f, 1.0f));
	//pExplosiveObject->SetMovingSpeed(6.4f);
	//m_ppObjects[4] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(255, 0, 255));
	//pExplosiveObject->SetPosition(-10.0f, 0.0f, -10.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pExplosiveObject->SetRotationSpeed(60.06f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	//pExplosiveObject->SetMovingSpeed(8.9f);
	//m_ppObjects[5] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(255, 0, 255));
	//pExplosiveObject->SetPosition(-10.0f, 10.0f, -10.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pExplosiveObject->SetRotationSpeed(60.06f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 1.0f));
	//pExplosiveObject->SetMovingSpeed(9.7f);
	//m_ppObjects[6] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(255, 0, 128));
	//pExplosiveObject->SetPosition(-10.0f, 10.0f, -20.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	//pExplosiveObject->SetRotationSpeed(70.06f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 1.0f));
	//pExplosiveObject->SetMovingSpeed(15.6f);
	//m_ppObjects[7] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(128, 0, 255));
	//pExplosiveObject->SetPosition(-15.0f, 10.0f, -30.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	//pExplosiveObject->SetRotationSpeed(90.06f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
	//pExplosiveObject->SetMovingSpeed(15.0f);
	//m_ppObjects[8] = pExplosiveObject;

	//pExplosiveObject = new CExplosiveObject();
	//pExplosiveObject->SetMesh(pCubeMesh);
	//pExplosiveObject->SetColor(RGB(255, 64, 64));
	//pExplosiveObject->SetPosition(+15.0f, 10.0f, 0.0f);
	//pExplosiveObject->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	//pExplosiveObject->SetRotationSpeed(90.06f);
	//pExplosiveObject->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, -1.0f));
	//pExplosiveObject->SetMovingSpeed(15.0f);
	//m_ppObjects[9] = pExplosiveObject;


#ifdef _WITH_DRAW_AXIS
	m_pWorldAxis = new CGameObject();
	CAxisMesh* pAxisMesh = new CAxisMesh(0.5f, 0.5f, 0.5f);
	m_pWorldAxis->SetMesh(pAxisMesh);
#endif
}



void CScene::ReleaseObjects() {
	if (CExplosiveObject::m_pExplosionMesh) 
		CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++) 
		if (m_ppObjects[i]) 
			delete m_ppObjects[i];

	if (m_ppObjects) 
		delete[] m_ppObjects;

	if (m_pWallsObject) 
		delete m_pWallsObject;

	// 적 기체
	for(int i = 0; i < 5; ++i)
		delete m_airplane_object[i];


#ifdef _WITH_DRAW_AXIS
	if (m_pWorldAxis) delete m_pWorldAxis;
#endif
}



void CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {}



void CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	switch (nMessageID){
	case WM_KEYDOWN:
		switch (wParam){
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':


		/*case 'C':{
			CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[int(wParam - '1')];
			pExplosiveObject->m_bBlowingUp = true;
			break;
		}

		case 'V':
			for (int i = 0; i < m_nObjects; i++){
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
			}
			break;*/


		default:
			break;
		}


		break;


	default:
		break;
	}
}



CGameObject* CScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera) {
	XMFLOAT3 xmf3PickPosition;

	xmf3PickPosition.x = (((2.0f * xClient) / (float)pCamera->m_Viewport.m_nWidth) - 1) / pCamera->m_xmf4x4PerspectiveProject._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / (float)pCamera->m_Viewport.m_nHeight) - 1) / pCamera->m_xmf4x4PerspectiveProject._22;
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);
	XMMATRIX xmmtxView = XMLoadFloat4x4(&pCamera->m_xmf4x4View);

	int nIntersected = 0;
	float fNearestHitDistance = FLT_MAX;

	CGameObject* pNearestObject = NULL;

	for (int i = 0; i < m_nObjects; i++){
		float fHitDistance = FLT_MAX;

		nIntersected = m_ppObjects[i]->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance);

		if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance)){
			fNearestHitDistance = fHitDistance;
			pNearestObject = m_ppObjects[i];
		}
	}

	return(pNearestObject);
}



void CScene::CheckObjectByObjectCollisions() {
	for (int i = 0; i < m_nObjects; i++) 
		m_ppObjects[i]->m_pObjectCollided = NULL;


	for (int i = 0; i < m_nObjects; i++){
		for (int j = (i + 1); j < m_nObjects; j++){
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB)){
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
			}
		}
	}


	for (int i = 0; i < m_nObjects; i++){
		if (m_ppObjects[i]->m_pObjectCollided){
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;

			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;

			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;

			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;

			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}



void CScene::CheckObjectByWallCollisions() {
	for (int i = 0; i < m_nObjects; i++) {
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);

		switch (containType){
		case DISJOINT:{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++){
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));

				if (intersectType == BACK){
					nPlaneIndex = j;
					break;
				}
			}

			if (nPlaneIndex != -1){
				XMVECTOR xmvNormal = 
					XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, 
								m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, 
								m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);

				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);

				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}

			break;
		}


		case INTERSECTS:{
			int nPlaneIndex = -1;

			for (int j = 0; j < 6; j++) {
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));

				if (intersectType == INTERSECTING) {
					nPlaneIndex = j;
					break;
				}
			}

			if (nPlaneIndex != -1){
				XMVECTOR xmvNormal = 
					XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, 
								m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, 
								m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);

				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);

				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}

			break;
		}


		case CONTAINS:
			break;
		}
	}
}



void CScene::CheckPlayerByWallCollision() {
	BoundingOrientedBox xmOOBBPlayerMoveCheck;

	m_pWallsObject->m_xmOOBBPlayerMoveCheck.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&m_pWallsObject->m_xmf4x4World));

	XMStoreFloat4(&xmOOBBPlayerMoveCheck.Orientation, XMQuaternionNormalize(XMLoadFloat4(&xmOOBBPlayerMoveCheck.Orientation)));

	if (!xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB)) 
		m_pWallsObject->SetPosition(m_pPlayer->m_xmf3Position);
}



void CScene::CheckObjectByBulletCollisions() {
	CBulletObject** ppBullets = ((CAirplanePlayer*)m_pPlayer)->m_ppBullets;

	for (int i = 0; i < m_nObjects; i++){
		for (int j = 0; j < BULLETS; j++){
			if (ppBullets[j]->m_bActive && m_ppObjects[i]->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB)){
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];

				pExplosiveObject->m_bBlowingUp = true;
				ppBullets[j]->Reset();
			}
		}
	}
}



void CScene::Animate(float fElapsedTime) {
	m_pWallsObject->Animate(fElapsedTime);

	for (int i = 0; i < m_nObjects; i++) 
		m_ppObjects[i]->Animate(fElapsedTime);

	CheckPlayerByWallCollision();

	CheckObjectByWallCollisions();

	CheckObjectByObjectCollisions();

	CheckObjectByBulletCollisions();
}



void CScene::Render(HDC hDCFrameBuffer, CCamera* pCamera) {
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	m_pWallsObject->Render(hDCFrameBuffer, pCamera);


	for (int i = 0; i < m_nObjects; i++) 
		m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

	if (m_pPlayer) 
		m_pPlayer->Render(hDCFrameBuffer, pCamera);


	for (int i = 0; i < 5; ++i) 
		m_airplane_object[i]->Render(hDCFrameBuffer, pCamera);


//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}
