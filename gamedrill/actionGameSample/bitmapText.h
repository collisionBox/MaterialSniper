#include "DxLib.h"
////////////////////////////////////////////////////////////////
// Bitmap Text class
// 
// 数字〜アルファベットが並んだビットマップ画像をフォントとして登録
// 文字列を画面表示するクラス
////////////////////////////////////////////////////////////////

#ifndef __BITMAPTEXT_H__
#define __BITMAPTEXT_H__

class BitmapText
{
public:
	BitmapText();
	~BitmapText();

	void          setBackGroundAlpha(bool bg_alpha_on) { mBgalpha = bg_alpha_on; }                 // フォント背景を透過するか？
	void          setFontImage(int Xnum, int Ynum, char* fontImgfilename);                          // フォント画像よりフォントをセットする
	void          setFontColor(int r, int g, int b);                                                // フォントカラーセット
	void          setFontColorShadow(int r, int g, int b);                                          // 影カラーをセット
	void          textDrawRandom(int x, int y, char* string, int maxRand, int countDown);           // ランダム文字表示
	
	void          setFontShadowOffset(int ofsX, int ofsY);                                          // 影フォント位置オフセット
	void          textDraw(int x, int y, char* string);                                             // テキストを描画
	void          textDrawWithShadow(int x, int y, char* string);                                   // 影付きでテキスト描画

	void          textDrawMessage(int x, int y, char* string, unsigned int display_lengh);          // メッセージ風表示（文字数制限あり）
	void          textDrawMessageWithShadow(int x, int y, char*string, unsigned int display_lengh); // メッセージ風表示（文字数制限あり）
	void          reMapText(char* remapText); // ビットマップに並んでいる文字列を入れて、テキストから文字列を作れるようにする。（初期化で必要）

private:
	int           mFontImg[256] ; // フォントイメージ配列
	int           mFontMap[256] ; // 文字マップ char型文字→フォントイメージ配列添え字番号のマッピング

	unsigned int  mSizeX        ; // フォント1文字分横サイズ
	unsigned int  mSizeY        ; // フォント1文字分縦サイズ	
	int           mShadowOffsetX; // 影フォント位置オフセットX
	int           mShadowOffsetY; // 影フォント位置オフセットY
	bool          mUseflag      ; // フォント使用可能フラグ
	bool          mBgalpha      ; // 文字背景を透過させるか

	int           isString(char c)          ; // 文字をイメージ配列の添え字に変換
	unsigned char R, G, B;         // 文字色 
	unsigned char mShadowR;
	unsigned char mShadowG;
	unsigned char mShadowB;
};

#endif