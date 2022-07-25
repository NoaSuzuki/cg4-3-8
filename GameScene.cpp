#include "GameScene.h"
#include "FbxLoader.h"
#include "Object3d.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"Input.h"
#include"sprite.h"
#include"PostEffect.h"
using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(object1);
	safe_delete(model1);
	safe_delete(spriteBG);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText = DebugText::GetInstance();
	debugText->Initialize(debugTextTexNumber);

	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });


	// �e�N�X�`��2�Ԃɓǂݍ���
	Sprite::LoadTexture(2, L"Resources/tex1.png");


	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 3, 0 });
	camera->SetDistance(8.0f);


	// ���f�������w�肵�ăt�@�C���ǂݍ���
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	// �f�o�C�X���Z�b�g
	Object3d::SetDevice(dxCommon->GetDevice());
	// �J�������Z�b�g
	Object3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	Object3d::CreateGraphicsPipeline();

	object1 = new Object3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->PlayAnimation();
}

void GameScene::Update()
{

	camera->Update();

	object1->Update();

}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	//Sprite::PreDraw(cmdList);
	//// �w�i�X�v���C�g�`��
	//spriteBG->Draw();

	///// <summary>
	///// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	///// </summary>
	///// 
	///// 

	//// �X�v���C�g�`��㏈��
	//Sprite::PostDraw();
	//// �[�x�o�b�t�@�N���A
	//dxCommon->ClearDepthBuffer();

#pragma endregion

#pragma region 3D�`��
	object1->Draw(cmdList);

#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>



	// �f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(cmdList);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}
