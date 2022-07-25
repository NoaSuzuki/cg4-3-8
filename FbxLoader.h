#pragma once

#include "fbxsdk.h"
#include "Model.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FbxLoader
{
private: // �G�C���A�X
	// std::���ȗ�
	using string = std::string;

public: // �萔
	// ���f���i�[���[�g�p�X
	static const string baseDirectory;
	// �e�N�X�`�����Ȃ��ꍇ�̕W���e�N�X�`���t�@�C����
	static const string defaultTextureFileName;
public:
	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static FbxLoader* GetInstance();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="device">D3D12�f�o�C�X</param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �t�@�C������FBX���f���Ǎ�
	/// </summary>
	/// <param name="modelName">���f����</param>
	Model* LoadModelFromFile(const string& modelName);

	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxMatrix& src);

private:
	// D3D12�f�o�C�X
	ID3D12Device* device = nullptr;
	// FBX�}�l�[�W��
	FbxManager* fbxManager = nullptr;
	// FBX�C���|�[�^
	FbxImporter* fbxImporter = nullptr;

private:
	// private�ȃR���X�g���N�^�i�V���O���g���p�^�[���j
	FbxLoader() = default;
	// private�ȃf�X�g���N�^�i�V���O���g���p�^�[���j
	~FbxLoader() = default;
	// �R�s�[�R���X�g���N�^���֎~�i�V���O���g���p�^�[���j
	FbxLoader(const FbxLoader& obj) = delete;
	// �R�s�[������Z�q���֎~�i�V���O���g���p�^�[���j
	void operator=(const FbxLoader& obj) = delete;

	/// <summary>
	/// �ċA�I�Ƀm�[�h�\�������
	/// </summary>
	/// <param name="model">�ǂݍ��ݐ惂�f���I�u�W�F�N�g</param>
	/// <param name="fbxNode">��͑Ώۂ̃m�[�h</param>
	/// <param name="parent">�e�m�[�h</param>
	void ParseNodeRecursive(Model* model, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// ���b�V���ǂݎ��
	/// </summary>
	/// <param name="model">�ǂݍ��ݐ惂�f���I�u�W�F�N�g</param>
	/// <param name="fbxNode">��͑Ώۂ̃m�[�h</param>
	void ParseMesh(Model* model, FbxNode* fbxNode);
	// ���_���W�ǂݎ��
	void ParseMeshVertices(Model* model, FbxMesh* fbxMesh);
	// �ʏ��ǂݎ��
	void ParseMeshFaces(Model* model, FbxMesh* fbxMesh);
	// �}�e���A���ǂݎ��
	void ParseMaterial(Model* model, FbxNode* fbxNode);
	// �e�N�X�`���ǂݍ���
	void LoadTexture(Model* model, const std::string& fullpath);
	// �f�B���N�g�����܂񂾃t�@�C���p�X����t�@�C�����𒊏o����
	std::string ExtractFileName(const std::string& path);
	//�X�L�j���O���̓ǂݎ��
	void ParseSkin(Model* model, FbxMesh* fbxMesh);
};