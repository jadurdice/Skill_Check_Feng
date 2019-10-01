#include <Windows.h>
#include "DirectX.h"

// �O���[�o���ϐ�
LPDIRECT3D9 glbD3DInterface;	// DirectX�C���^�[�t�F�[�X
D3DPRESENT_PARAMETERS *glbD3DPresentParam;
LPDIRECT3DDEVICE9 glbD3DDevice;

bool InitDirectX(HWND window_handle)
{
	// �C���^�[�t�F�[�X�쐬
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

	// DirectDevice�̍쐬
	if (FAILED(glbD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		glbD3DPresentParam,
		&glbD3DDevice)))
	{
		return false;
	}

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = glbD3DPresentParam->BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = glbD3DPresentParam->BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
	if (FAILED(glbD3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void Draw()
{
	glbD3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,			// ����������o�b�t�@�̎��
		D3DCOLOR_ARGB(255, 0, 0, 0),// �t���[���o�b�t�@�̏������F
		1.0f,						// Z�o�b�t�@�̏����l
		0);							// �X�e���V���o�b�t�@�̏����l

	glbD3DDevice->BeginScene();

	// �O�p�`��`�� start
	VERTEX v[3];

	v[0].pos.x = 200.0f; v[0].pos.y = 120.0f; v[0].pos.z = 0.0f;
	v[1].pos.x = 240.0f; v[1].pos.y = 200.0f; v[1].pos.z = 0.0f;
	v[2].pos.x = 160.0f; v[2].pos.y = 200.0f; v[2].pos.z = 0.0f;

	v[0].w = v[1].w = v[2].w = 1.0f;

	v[0].color = D3DCOLOR_ARGB(255, 255, 0, 0);
	v[1].color = D3DCOLOR_ARGB(255, 255, 0, 0);
	v[2].color = D3DCOLOR_ARGB(255, 255, 0, 0);

	// ���_�\���̎w��
	glbD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	glbD3DDevice->SetTexture(0, NULL);

	glbD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, v, sizeof(VERTEX));

	// �O�p�`��`�� end

	glbD3DDevice->EndScene();

	glbD3DDevice->Present(NULL, NULL, NULL, NULL);

}