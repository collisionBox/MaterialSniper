#pragma once

enum GraphicFx
{
	GraFxBlink,//点滅
	GraFxFadeIn,//透明→不透明
	GraFxFadeOut,//不透明→透明
	GraFxFadeInOut,//不透明←→透明
	GraFxNone//通常描画
};

class Effect
{
public:
	void Init();
	void GraphicfxStart(GraphicFx* fx, int millTime, int millInterval, float deltaTime);

private:
	bool isFxStartFlag;//描画エフェクトフラグ
	GraphicFx fx;//描画エフェクトの種類
	int fxMillTime;//エフェクト時間カウント
	int fxMillTimeMax;//エフェクト時間カウントMAX 

	int fxInterMillTime;//エフェクト間隔カウント
	int fxInterMillTimeMax;//エフェクト間隔ウントMAX
	float alpha;
	const int GraFxInfinity = -99999;
};