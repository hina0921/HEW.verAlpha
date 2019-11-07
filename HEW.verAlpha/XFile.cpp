/*==============================================

	[XFile.cpp]
	Author : �o���đ�

===============================================*/

#include "main.h"
#include "XFile.h"

//	�O���[�o���ϐ�
DWORD				XFile::MeshNum = 0;								//	���b�V����
LPD3DXMESH			XFile::Mesh = NULL;								//	���b�V��
D3DMATERIAL9		*XFile::pMeshMaterialList = NULL;				//	���b�V���}�e���A��
LPDIRECT3DTEXTURE9	*XFile::pTextureList = NULL;					//	�e�N�X�`�����X�g
LPDIRECT3DDEVICE9	XFile::g_pD3Device;								//	�f�o�C�X�̎擾
std::map<std::string, XFile*>g_pXFileList;	// �ǂݍ���XFile�̃��X�g
extern std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;


bool XFile::Load(std::string fliename)
{
	//# ���f���f�[�^�̃��[�h
	// XFile�f�[�^���i�[���鉼�o�b�t�@
	LPD3DXBUFFER p_material_buffer = NULL;

	//	XFile�̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(fliename.c_str(), D3DXMESH_SYSTEMMEM, g_pD3Device, NULL, &p_material_buffer, NULL, &MeshNum, &Mesh)))
	{
		return false;
	}

	// �}�e���A�����̃R�s�[
	// �ǂݍ��܂ꂽXFile�̃}�e���A������D3DMATERIAL9��p�ӂ���
	pMeshMaterialList = new D3DMATERIAL9[MeshNum];

	// ���b�V���Ɏg�p����Ă���e�N�X�`���p�̔z���p�ӂ���
	pTextureList = new LPDIRECT3DTEXTURE9[MeshNum];

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL *pmat_list = (D3DXMATERIAL*)p_material_buffer->GetBufferPointer();

	// �e���b�V���̃}�e���A�������擾����
	for (DWORD i = 0; i < MeshNum; i++)
	{
		// �}�e���A���擾
		pMeshMaterialList[i] = pmat_list[i].MatD3D;
		pTextureList[i] = NULL;

		// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
		if (pmat_list[i].pTextureFilename != NULL)
		{
			std::string filename = pmat_list[i].pTextureFilename;
			LPDIRECT3DTEXTURE9 texture = NULL;
		}
	}

	// �}�e���A���̃R�s�[���I������̂Ńo�b�t�@���������
	p_material_buffer->Release();

	return true;
}

void XFile::Unload()
{
	//# ���f���f�[�^�̃A�����[�h
	// �}�e���A�����X�g�̉��
	if (pMeshMaterialList != NULL)
	{
		delete[](pMeshMaterialList);
		pMeshMaterialList = NULL;
	}

	// �e�N�X�`�����X�g�̉��
	delete[](pTextureList);

	//	�f�o�C�X�̉��
	DEVICE_RELEASE(g_pD3Device);

	// �e�N�X�`���t�@�C�������X�g�̏�����
}

void XFile::Draw()
{
	for (DWORD i = 0; i < MeshNum; i++)
	{
		// �}�e���A���̐ݒ�
		g_pD3Device->SetMaterial(&pMeshMaterialList[i]);
		// �e�N�X�`���̐ݒ�
		g_pD3Device->SetTexture(0, pTextureList[i]);
		// ���b�V����`��
		Mesh->DrawSubset(i);
	}
}