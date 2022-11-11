#include "questions.h"
#include "math2D.h"

Quest22_23Seq::Quest22_23Seq()
{
	mImgHandle = LoadGraph("image/block1.bmp");

	//開始点と終了点初期化
	for (int i = 0; i < 4; i++)
	{
		m_Pos[i] = m_startPos[i] = Point2D(100.0f, i * 100.0f + 100.0f);
		m_endPos[i] = Point2D(700.0f, i * 100.0f + 60.0f);
	}

	//アニメーション
	m_anim = 0.0f;
	m_animInc = 0.005f;

	m_easingType = EASETYPE_NORMAL;

	// イージング名初期化
	sprintf(m_easeInOutNames[0], "EASE-IN");
	sprintf(m_easeInOutNames[1], "EASE-OUT");
	sprintf(m_easeInOutNames[2], "EASE-INOUT");

	sprintf(m_easingTypeNames[EASETYPE_NORMAL],"NORMAL");
	sprintf(m_easingTypeNames[EASETYPE_CUBIC], "CUBIC");
	sprintf(m_easingTypeNames[EASETYPE_CIRCULAR], "CIRCULAR");
	sprintf(m_easingTypeNames[EASETYPE_EXPONENTIAL], "EXPONENTIAL");

}

Quest22_23Seq::~Quest22_23Seq()
{
	if (mImgHandle != -1)
	{
		DeleteGraph(mImgHandle);
	}
}
Sequence* Quest22_23Seq::move()
{
	// animを0～1.0の間を行ったり来たりアニメーション

	if (m_anim > 1.5 && m_animInc > 0.0f)
	{
		m_animInc *= -1.0f;
	}
	if (m_anim < 0.0 && m_animInc < 0.0f)
	{
		m_animInc *= -1.0f;
	}
	m_anim += m_animInc;

	// 線形補間計算 開始点から終了点までの補間をそれぞれの方式で計算
	m_Pos[0] = linearInterporation(m_startPos[0], m_endPos[0], m_anim);

	if (m_easingType == EASETYPE_NORMAL)
	{
		m_Pos[1] = easeIn(m_startPos[1], m_endPos[1], m_anim);
		m_Pos[2] = easeOut(m_startPos[2], m_endPos[2], m_anim);
		m_Pos[3] = easeInOut(m_startPos[3], m_endPos[3], m_anim);
	}
	if (m_easingType == EASETYPE_CUBIC)
	{
		m_Pos[1] = easeInCubic(m_startPos[1], m_endPos[1], m_anim);
		m_Pos[2] = easeOutCubic(m_startPos[2], m_endPos[2], m_anim);
		m_Pos[3] = easeInOutCubic(m_startPos[3], m_endPos[3], m_anim);
	}
	if (m_easingType == EASETYPE_CIRCULAR)
	{
		m_Pos[1] = easeInCircular(m_startPos[1], m_endPos[1], m_anim);
		m_Pos[2] = easeOutCircular(m_startPos[2], m_endPos[2], m_anim);
		m_Pos[3] = easeInOutCircular(m_startPos[3], m_endPos[3], m_anim);
	}

	if (m_easingType == EASETYPE_EXPONENTIAL)
	{
		m_Pos[1] = easeInExponential(m_startPos[1], m_endPos[1], m_anim);
		m_Pos[2] = easeOutExponential(m_startPos[2], m_endPos[2], m_anim);
		m_Pos[3] = easeInOutExponential(m_startPos[3], m_endPos[3], m_anim);
	}

	// イージングタイプ変更
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN)
	{
		m_easingType++;
		m_easingType %= 4;
	}

	// スペースキーが押されたら次のクエストのシーケンスを作成してシーケンスチェンジ
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN)
	{
		return new Quest24Seq;
	}

	// 現行シーケンス続行
	return this;
}


void Quest22_23Seq::draw()
{
	char buf[64];
	ClearDrawScreen();

	// 移動ライン表示
	for (int i = 0; i < 4; i++)
	{
		DrawLine((int)m_startPos[i].x, (int)m_startPos[i].y,
			     (int)m_endPos[i].x, (int)m_endPos[i].y,
			     0xff005522, 2);
	}

	// ブロック表示
	for (int i = 0; i < 4; i++)
	{
		DrawGraph((int)m_Pos[i].x, (int)m_Pos[i].y, mImgHandle, true);
	}

	GAMEINSTANCE.systemText.textDraw(10, 80, "LINEAR");

	//イージング方式を表示
	for (int i = 0; i < 3; i++)
	{
		sprintf(buf, "%s/%s", m_easeInOutNames[i], m_easingTypeNames[m_easingType]);
		GAMEINSTANCE.systemText.textDraw(10, 180 + i * 100, buf);
	}

	sprintf(buf, "ANIM [0.0f - 1.0f] %0.3f", m_anim);
	GAMEINSTANCE.systemText.textDraw(10, 30, buf);

	GAMEINSTANCE.systemText.textDraw(10, 10, "QUESTION #22-23.");
	blinkingString(10, GAMEINSTANCE.getScreenHeight() - 32, "Push Space Key To Next Question.");

}