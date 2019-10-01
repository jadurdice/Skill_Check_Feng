#include <Windows.h>
#include "DirectX.h"

#pragma region �O���[�o���ϐ��錾

LPDIRECT3D9 glbD3DInterface;				// DirectX�C���^�[�t�F�[�X
D3DPRESENT_PARAMETERS *glbD3DPresentParam;	//�`��p�����[�^
LPDIRECT3DDEVICE9 glbD3DDevice;				//D3D�f�o�C�X

D3DXVECTOR3 glbCameraPosition;				// �J�����ʒu
D3DXVECTOR3 glbEyePosition; 				// �����_
D3DXVECTOR3 glbUpVector;					// �J�����̌���

VERTEX glbV[6][4];							//�|���S�����_�f�[�^
D3DXVECTOR3 glbPolygonPosition;				//�|���S�����W
D3DXVECTOR3 glbPolygonRotation;				//�|���S����]
D3DXVECTOR3 glbPolygonScale;				//�|���S���g��

float moveFactor;

#pragma endregion

bool InitDirectX(HWND window_handle)
{

	#pragma region �C���^�[�t�F�[�X�쐬


	glbD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (glbD3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}

	glbD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (glbD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(glbD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	glbD3DPresentParam->BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	glbD3DPresentParam->BackBufferFormat = D3DFMT_UNKNOWN;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	glbD3DPresentParam->Windowed = true;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	glbD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

#pragma endregion

	#pragma region DirectDevice�̍쐬
	
	if (FAILED(glbD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		glbD3DPresentParam,
		&glbD3DDevice)))
	{
		return false;
	}

#pragma endregion

	#pragma region �r���[�|�[�g�p�����[�^�ݒ�

	D3DVIEWPORT9 viewPort;

	// �r���[�|�[�g�̍�����W
	viewPort.X = 0;
	viewPort.Y = 0;
	// �r���[�|�[�g�̕�
	viewPort.Width = glbD3DPresentParam->BackBufferWidth;
	// �r���[�|�[�g�̍���
	viewPort.Height = glbD3DPresentParam->BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;

	if (FAILED(glbD3DDevice->SetViewport(&viewPort)))
	{
		return false;
	}

#pragma endregion

	#pragma region �|���S���̃��[�J�����W�̈ʒu�ݒ�

	D3DXCOLOR pointColor[8];

	pointColor[0] = { 0.0f,0.0f,0.0f,1.0f };
	pointColor[1] = { 0.0f,1.0f,1.0f,1.0f };
	pointColor[2] = { 1.0f,0.0f,1.0f,1.0f };
	pointColor[3] = { 1.0f,1.0f,0.0f,1.0f };
	pointColor[4] = { 1.0f,0.0f,0.0f,1.0f };
	pointColor[5] = { 0.0f,1.0f,0.0f,1.0f };
	pointColor[6] = { 0.0f,0.0f,1.0f,1.0f };
	pointColor[7] = { 1.0f,1.0f,1.0f,1.0f };

	//bottom
	glbV[0][0].color = pointColor[0];//1
	glbV[0][1].color = pointColor[1];//2
	glbV[0][2].color = pointColor[2];//3
	glbV[0][3].color = pointColor[3];//4
	glbV[0][0].position = { 1.0f,	-1.0f,	1.0f };
	glbV[0][1].position = { -1.0f,	-1.0f,	1.0f };
	glbV[0][2].position = { 1.0f,	-1.0f,	-1.0f };
	glbV[0][3].position = { -1.0f,	-1.0f,	-1.0f };

	//top
	glbV[1][0].color = pointColor[4];//5
	glbV[1][1].color = pointColor[5];//6
	glbV[1][2].color = pointColor[6];//7
	glbV[1][3].color = pointColor[7];//8
	glbV[1][0].position = { 1.0f,	1.0f,	-1.0f };
	glbV[1][1].position = { -1.0f,	1.0f,	-1.0f };
	glbV[1][2].position = { 1.0f,	1.0f,	1.0f };
	glbV[1][3].position = { -1.0f,	1.0f,	1.0f };

	//left
	glbV[2][0].color = pointColor[7];//8
	glbV[2][1].color = pointColor[5];//6
	glbV[2][2].color = pointColor[1];//2
	glbV[2][3].color = pointColor[3];//4
	glbV[2][0].position = { -1.0f,	1.0f,	1.0f };
	glbV[2][1].position = { -1.0f,	1.0f,	-1.0f };
	glbV[2][2].position = { -1.0f,	-1.0f,	1.0f };
	glbV[2][3].position = { -1.0f,	-1.0f,	-1.0f };

	//right
	glbV[3][0].color = pointColor[4];//5
	glbV[3][1].color = pointColor[6];//7
	glbV[3][2].color = pointColor[2];//3
	glbV[3][3].color = pointColor[0];//1
	glbV[3][0].position = { 1.0f,	1.0f,	-1.0f };
	glbV[3][1].position = { 1.0f,	1.0f,	1.0f };
	glbV[3][2].position = { 1.0f,	-1.0f,	-1.0f };
	glbV[3][3].position = { 1.0f,	-1.0f,	1.0f };

	//front
	glbV[4][0].color = pointColor[6];//7
	glbV[4][1].color = pointColor[7];//8
	glbV[4][2].color = pointColor[0];//1
	glbV[4][3].color = pointColor[1];//2
	glbV[4][0].position = { 1.0f,	1.0f,	1.0f };
	glbV[4][1].position = { -1.0f,	1.0f,	1.0f };
	glbV[4][2].position = { 1.0f,	-1.0f,	1.0f };
	glbV[4][3].position = { -1.0f,	-1.0f,	1.0f };

	//back
	glbV[5][0].color =pointColor[5];//6
	glbV[5][1].color =pointColor[4];//5
	glbV[5][2].color =pointColor[3];//4
	glbV[5][3].color =pointColor[2];//3
	glbV[5][0].position = { -1.0f,	1.0f,	-1.0f };
	glbV[5][1].position = { 1.0f,	1.0f,	-1.0f };
	glbV[5][2].position = { -1.0f,	-1.0f,	-1.0f };
	glbV[5][3].position = { 1.0f,	-1.0f,	-1.0f };



#pragma endregion

	#pragma region �O���[�o���ϐ��̏�����

	glbCameraPosition = { 0.0f, 3.0f, -10.0f };
	glbEyePosition = { 0.0f, 0.0f, 0.0f };
	glbUpVector = { 0.0f, 1.0f, 0.0f };
	glbPolygonPosition = { 0.0f,0.0f,0.0f };
	glbPolygonRotation = { 0.0f,0.0f,0.0f };
	glbPolygonScale = { 1.0f,1.0f,1.0f };

#pragma endregion

	return true;
}

void UpdateDirextX(void)
{

	#pragma region �O���[�o���ϐ��ϓ�

	moveFactor += D3DXToRadian(1);

	glbPolygonRotation += {0.02f, 0.02f, 0.02f};
	glbPolygonPosition = { 3.0f*cosf(moveFactor),1.0f + 3.0f*sinf(moveFactor), 0.0f};
	glbEyePosition = glbPolygonPosition;

	#pragma endregion

	#pragma region �r���[���W�ϊ��p�̍s��Z�o 

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView,
		&glbCameraPosition,				// �J�������W
		&glbEyePosition,					// �����_���W
		&glbUpVector);				// �J�����̏�̌����̃x�N�g��
	glbD3DDevice->SetTransform(D3DTS_VIEW, &matView);

#pragma endregion

	#pragma region �ˉe���W�ϊ��p�̍s��Z�o 
	D3DXMATRIX matProjection;
	D3DVIEWPORT9 vp;
	glbD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&matProjection,
		D3DXToRadian(45),	// ��p
		aspect,				// �A�X�y�N�g��
		0.1f,				// near
		500.0f);			// far
	glbD3DDevice->SetTransform(D3DTS_PROJECTION, &matProjection);

#pragma endregion

}

void DrawDirectX()
{

	#pragma region �O�̃o�b�N�o�b�t�@�����ƕ`��J�n

	glbD3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 100, 100, 100),
		1.0f,	// Z�o�b�t�@�̏����l
		0);		// �X�e���V���o�b�t�@�̏����l

	glbD3DDevice->BeginScene();

	//���C�e�B���O�𖳌��ɂ���B
	glbD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	#pragma endregion

	#pragma region ���[���h���W�ϊ��p�̍s��̎Z�o 

	D3DXMATRIX matWorld, matTrans, matRot, matRotx, matRoty, matRotz, matScale;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	// �ړ�
	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 10.0f);

	// ��]

	D3DXMatrixRotationX(&matRotx, glbPolygonRotation.x);
	D3DXMatrixRotationY(&matRoty, glbPolygonRotation.y);
	D3DXMatrixRotationZ(&matRotz, glbPolygonRotation.z);

	D3DXMatrixMultiply(&matRot, &matRot, &matRoty);
	D3DXMatrixMultiply(&matRot, &matRot, &matRotx);
	D3DXMatrixMultiply(&matRot, &matRot, &matRotz);

	// �g��
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);

	// �|�����킹(�g�k * ��] * �ړ�)
	matWorld *= matScale * matRot * matTrans;

	glbD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);


#pragma endregion

	#pragma region FVF�ƃe�N�X�`���̐ݒ�

	glbD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	glbD3DDevice->SetTexture(0, NULL);

	#pragma endregion
	
	#pragma region �|���S����DrawPrimitiveUP

	for (int i = 0; i < 6; i++)
	{
		glbD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, glbV[i], sizeof(VERTEX));
	}

#pragma endregion

	#pragma region �`��I��

	glbD3DDevice->EndScene();
	glbD3DDevice->Present(NULL, NULL, NULL, NULL);

#pragma endregion


}