#ifndef __LINKED_PARTICLE_H__
#define __LINKED_PARTICLE_H__

#include <vector>
#include "Map.h"
#include "camera.h"

class LinkedParticle;

typedef struct LinkedParticleConnectionInfo
{

	LinkedParticle* m_particle;
	float           m_springLen;
	float           m_springConstant;

}LinkedParticleConnectionInfo;

typedef enum LP_STATE_ENUM
{

	LP_STATE_ENUM_CONSTRAINT,  // 拘束されている
	LP_STATE_ENUM_SLEEP,       // スリープ
	LP_STATE_ENUM_ACTIVE,      // 活動中（衝突してない）
	LP_STATE_ENUM_ON_GROUND,   // 接地している
	LP_STATE_ENUM_HIT,         // 壁にヒットしている
	LP_STATE_ENUM_RESERVED,    // 将来の拡張の予約

}LP_STATE_ENUM;

class LinkedParticle
{
public:
	LinkedParticle();
	~LinkedParticle();

	void           linkCalc(Map* pMap)										; // 接続されている質点同士の計算
	void           move( Map* pMap )										; // 移動処理
	void           debugDraw(Camera* pCam)									; // デバッグ描画
	void           addForce(float addFx, float addFy)                       ; // 外力を加える
	bool           isConstraint() { return mbConstraint; }                   // コンストレイント（拘束）状態か？
	float          getPosY() { return my; }								  // Ｙ座標取得
	float          getPosX() { return mx; }								  // Ｘ座標取得
	void           link( LinkedParticle *p , float springStrength = 1.0)    ; // 質点リンク接続
	void           setMassPoint(float posx, float posy, float weight = 1.0f); // 質点初期化
	void           setConstraint();                  // コンストレイント（拘束）を行う 
	void           CutConstraint();              // コンストレイント（拘束）の解除
	void           reset()													; // 質点リセット

	static void    setMaxSpeed(float speed)									; // 最高速のセット
	static void    setGravity(float gravity)								; // 重力のセット
	static void    setEpsiron(float epsiron)								; // 微小値切り捨てしきい値

private:
	float          mx                                                      ; // 現在 x座標
	float          my                                                      ; // 現在 y座標
	float          mPrevX                                                 ; // １フレーム前 x座標
	float          mPrevY                                                 ; // １フレーム前 y座標
	float          mFx                                                     ; // x方向にかかる力の総和
	float          mFy                                                     ; // y方向にかかる力の総和
	float          mWeight                                                 ; // この質点の重さ
	bool           mbActive                                                ; // 実行対象か？
	bool           mbConstraint                                            ; // コンストレイント（拘束）パーティクルか？
	bool           mbHitWall                                               ; // 現在壁に衝突しているか？
	LP_STATE_ENUM  mState                                                  ; // パーティクル状態 
	std::vector<LinkedParticleConnectionInfo> mParticleArray               ; // パーティクル接続情報

	static float   mMaxSpeed                                               ; // 最高速度
	static float   mGravity                                                ; // 重力
	static float   mFrictionRatio                                          ; // 摩擦係数
	static float   mEpsiron                                                ; // 微小値切り捨てしきい値

	void           mapHit(Map* pMap)										; // マップとのあたり判定
};


#endif