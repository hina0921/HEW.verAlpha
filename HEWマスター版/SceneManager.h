/*======================================================

	[SceneManager.h]
	概要 : ゲームループを管理する
	Author : 出合翔太

======================================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"

//#	SceneManagerクラス
class SceneManager
{
private:
	static SceneBase			*m_scene[4];	//	シーン管理ポインタ変数
	static SCENE_STATE			m_sceneState;	//	シーンステートの管理変数
	static LPDIRECT3DDEVICE9	p3DDevice;		//	デバイスの取得変数
public:
	static void Init();					//	初期化処理
	static void Uninit();				//	終了処理
	static void Update();				//	更新処理
	static void Draw();					//	描画処理
	static void ChangeSceneState();		//	シーン遷移処理
	static SceneBase*	SetSceneGame();	
};

