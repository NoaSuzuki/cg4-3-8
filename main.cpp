#include "WinApp.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "GameScene.h"
#include "FbxLoader.h"
#include"PostEffect.h"
#include"Object3d.h"
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 汎用機能
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	GameScene* gameScene = nullptr;
	PostEffect* postEffect = nullptr;

	// ゲームウィンドウの作成
	win = new WinApp();
	win->CreateGameWindow();

	//DirectX初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);


#pragma region 汎用機能初期化
	// Audioの初期化
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}
	// Input初期化
	input = Input::GetInstance();
	if (!input->Initialize(win->GetInstance(), win->GetHwnd())) {
		assert(0);
		return 1;
	}

	// Sprite静的初期化
	if (!Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	/*Sprite::LoadTexture(100, L"Resources/white1x1.png");*/

	//ポストエフェクト初期化
	postEffect = new PostEffect();
	postEffect->Initialize();

	// FBX関連静的初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
#pragma endregion

	// GameSceneの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input, audio);



	// メインループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage()) { break; }

		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();

		//レンダーテクスチャ
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		gameScene->Draw();
		postEffect->PostDrawScene(dxCommon->GetCommandList());
		// 描画開始
		dxCommon->PreDraw();
		//ポスエフェ描画
		postEffect->Draw(dxCommon->GetCommandList());
		// ゲームシーンの描画
	/*	gameScene->Draw();*/
		// 描画終了
		dxCommon->PostDraw();

	}
	// 各種解放
	safe_delete(gameScene);
	FbxLoader::GetInstance()->Finalize();
	safe_delete(audio);
	safe_delete(dxCommon);

	delete postEffect;

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	safe_delete(win);

	return 0;
}