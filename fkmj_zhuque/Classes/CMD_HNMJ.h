#ifndef CMD_SPARROW_HEAD_FILE
#define CMD_SPARROW_HEAD_FILE

#include "GameDefine.h"
#pragma pack(8)

//组件属性
#define GAME_PLAYER					4								//游戏人数

#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_GOLD)	//游戏类型

//游戏状态
#define GS_MJ_FREE					GAME_STATUS_FREE					//空闲状态
#define GS_MJ_PLAY					(GAME_STATUS_PLAY+1)				//游戏状态
#define GS_MJ_XIAOHU				(GAME_STATUS_PLAY+2)							//小胡状态

#define TIME_START_GAME				30									//开始定时器
#define TIME_OPERATE_CARD			15									//操作定时器


#define GAME_TYPE_ZZ				0
#define GAME_TYPE_CS				1

#define GAME_TYPE_ZZ_ZIMOHU			1		//只能自模胡
#define GAME_TYPE_ZZ_QIDUI			2		//可胡七对
#define GAME_TYPE_ZZ_QIANGGANGHU	3		//可抢杠胡
#define GAME_TYPE_ZZ_ZHANIAO2		4		//扎鸟2个
#define GAME_TYPE_ZZ_ZHANIAO4		5		//扎鸟4个
#define GAME_TYPE_ZZ_ZHANIAO6		6		//扎鸟6个
#define GAME_TYPE_ZZ_HONGZHONG		7		//红中玩法
#define GAME_TYPE_CS_ZHUANGXIANFEN	8		//庄闲分
#define GAME_TYPE_ZZ_ZHANIAO3		9		//扎鸟3个
#define GAME_TYPE_ZZ_ZHANIAO5		10		//扎鸟5个
#define GAME_TYPE_ZZ_258			11		//258做将 长沙麻将
#define GAME_TYPE_ZZ_HONGZHONG_GZ	12		//红中癞子算红中2分

#define GAME_TYPE_ZZ_LIUJU_4CARD	13		//剩余4张黄庄
#define GAME_TYPE_ZZ_ZHANIAO1		14		//扎鸟1个
#define GAME_TYPE_ZZ_ZHANIAO_DOUBLE	15		//扎鸟翻倍
#define GAME_TYPE_ZZ_ZHANIAO_DIFF	16		//扎鸟分开算
#define GAME_TYPE_ZZ_ZHANIAO_2FEN	17		//扎鸟+2分
#define GAME_TYPE_ZZ_PIAO			18		//飘
#define GAME_TYPE_BU_NIAO			19		//牌不够补鸟

#define MAX_GAME_RULE				8		//最多规则

//////////////////////////////////////////////////////////////////////////

//组合子项
struct CMD_WeaveItem
{
	DWORD							cbWeaveKind;						//组合类型
	BYTE							cbCenterCard;						//中心扑克
	BYTE							cbPublicCard;						//公开标志
	WORD							wProvideUser;						//供应用户
};

//////////////////////////////////////////////////////////////////////////
//服务器命令结构

#define SUB_S_GAME_START			100									//游戏开始
#define SUB_S_OUT_CARD				101									//出牌命令
#define SUB_S_SEND_CARD				102									//发送扑克
#define SUB_S_SEND_CARD_CSGANG		103									//发送扑克
#define SUB_S_OPERATE_NOTIFY		104									//操作提示
#define SUB_S_OPERATE_RESULT		105									//操作命令
#define SUB_S_GAME_END				106									//游戏结束
#define SUB_S_TRUSTEE				107									//用户托管
#define SUB_S_CHI_HU				108									//
#define SUB_S_GANG_SCORE			110									//
#define SUB_S_OUT_CARD_CSGANG		111									//
#define SUB_S_XIAO_HU				112									//小胡
#define SUB_S_GAME_END_LAST_CARD	113									//剩下牌
#define SUB_S_USE_HAIDI_CARD		114									//是否用海底
#define SUB_S_PIAO_NOTICE			115									//是否飘


#define SUB_S_MASTER_HANDCARD		120									//
#define SUB_S_MASTER_LEFTCARD		121									//剩余牌堆

#define ZI_PAI_COUNT	7												//堆立全牌

#define MASK_CHI_HU_RIGHT			0x0fffffff							//最大权位DWORD个数			

//常量定义
#define MAX_WEAVE					4									//最大组合
#define MAX_INDEX					34									//最大索引
#define MAX_COUNT					14									//最大数目
#define MAX_REPERTORY				108									//最大库存

#define MAX_NIAO_CARD				10									//最大中鸟数
//游戏状态
struct CMD_S_StatusFree
{
	LONGLONG						lCellScore;							//基础金币
	WORD							wBankerUser;						//庄家用户
	bool							bTrustee[GAME_PLAYER];				//是否托管
};

//游戏状态
struct CMD_S_StatusPlay
{
	//游戏变量
	LONGLONG						lCellScore;									//单元积分
	WORD							wBankerUser;								//庄家用户
	WORD							wCurrentUser;								//当前用户

	//状态变量
	BYTE							cbActionCard;								//动作扑克
	DWORD							cbActionMask;								//动作掩码
	BYTE							cbLeftCardCount;							//剩余数目
	bool							bTrustee[GAME_PLAYER];						//是否托管
	WORD							wWinOrder[GAME_PLAYER];						//

	//出牌信息
	WORD							wOutCardUser;								//出牌用户
	BYTE							cbOutCardData;								//出牌扑克
	BYTE							cbDiscardCount[GAME_PLAYER];				//丢弃数目
	BYTE							cbDiscardCard[GAME_PLAYER][60];				//丢弃记录

	//扑克数据
	BYTE							cbCardCount;								//扑克数目
	BYTE							cbCardData[MAX_COUNT];						//扑克列表
	BYTE							cbSendCardData;								//发送扑克

	//组合扑克
	BYTE							cbWeaveCount[GAME_PLAYER];					//组合数目
	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//组合扑克

	bool                           bHasCSGang[GAME_PLAYER];
};

//游戏开始
struct CMD_S_GameStart
{
	QYLONG						lSiceCount;									//骰子点数
	WORD							wBankerUser;								//庄家用户
	WORD							wCurrentUser;								//当前用户
	DWORD							cbUserAction;								//用户动作
	BYTE							cbCardData[MAX_COUNT*GAME_PLAYER];			//扑克列表
	BYTE							cbLeftCardCount;							//
	BYTE                         cbXiaoHuTag;                             //小胡标记 0 没小胡 1 有小胡；
};

//出牌命令
struct CMD_S_OutCard
{
	WORD							wOutCardUser;						//出牌用户
	BYTE							cbOutCardData;						//出牌扑克
};

//出牌命令
struct CMD_S_OutCard_CSGang
{
	WORD							wOutCardUser;						//出牌用户
	BYTE							cbOutCardData1;						//出牌扑克
	BYTE							cbOutCardData2;						//出牌扑克
};
//发送扑克
struct CMD_S_SendCard
{
	bool							bGangStatus_CS;						//长沙杠的状态
	BYTE							cbCardData;							//扑克数据
	DWORD							cbActionMask;						//动作掩码
	WORD							wCurrentUser;						//当前用户
	bool							bTail;								//末尾发牌
};
//发送扑克
struct CMD_S_SendCard_CSGang
{
	BYTE							cbCardData1;						//扑克数据
	BYTE							cbCardData2;						//扑克数据
	DWORD							cbActionMask;						//动作掩码
	WORD							wCurrentUser;						//当前用户
};

//操作提示
struct CMD_S_OperateNotify
{
	bool							bGangStatus_CS;						//长沙杠的状态
	WORD							wProviderUser;						//提供用户
	BYTE							cbActionCard1;						//动作扑克
	DWORD							cbActionMask1;						//动作掩码
	BYTE							cbActionCard2;						//动作扑克
	DWORD							cbActionMask2;						//动作掩码
	BYTE							cbGangCardCount;					//杠牌数目
	BYTE							cbGangCardData[4];					//杠牌数据
};

//操作命令
struct CMD_S_OperateResult
{
	WORD							wOperateUser;						//操作用户
	WORD							wProvideUser;						//供应用户
	DWORD							cbOperateCode;						//操作代码
	BYTE							cbOperateCard;						//操作扑克
};

//游戏结束
struct CMD_S_GameEnd
{
	BYTE							cbCardCount[GAME_PLAYER];			//
	BYTE							cbCardData[GAME_PLAYER][MAX_COUNT];	//
	BYTE							cbChiHuCardData[GAME_PLAYER][2];	//
	//结束信息
	WORD							wProvideUser[GAME_PLAYER];			//供应用户
	DWORD							dwChiHuRight1[GAME_PLAYER];			//胡牌类型
	DWORD							dwChiHuRight2[GAME_PLAYER];			//胡牌类型
	dword							dwStartHuRight[GAME_PLAYER];			//起手胡牌类型
	LONGLONG						lStartHuScore[GAME_PLAYER];			//起手胡牌分数

	//积分信息
	LONGLONG						lGameScore[GAME_PLAYER];			//游戏积分
	int								lGameTax[GAME_PLAYER];				//

	WORD							wWinOrder[GAME_PLAYER];				//胡牌排名

	LONGLONG						lGangScore[GAME_PLAYER];			//详细得分
	BYTE							cbGenCount[GAME_PLAYER];			//
	WORD							wLostFanShu[GAME_PLAYER][GAME_PLAYER];
	WORD							wLeftUser;							//

	//组合扑克
	BYTE							cbWeaveCount[GAME_PLAYER];					//组合数目
	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//组合扑克

	BYTE							cbCardDataNiao[MAX_NIAO_CARD];	// 鸟牌
	BYTE							cbChairIDNiaoCout[GAME_PLAYER];	// 鸟牌
	BYTE							cbNiaoCount;	//鸟牌个数
	BYTE							cbNiaoPick;	//中鸟个数

	BYTE                         cbPiaoBei[GAME_PLAYER];
};

struct CMD_S_GameEnd_LastCard
{
	BYTE							cbCardCout;//剩余个数
	BYTE							cbCardData[108];	//剩余牌
};

//用户托管
struct CMD_S_Trustee
{
	bool							bTrustee;							//是否托管
	WORD							wChairID;							//托管用户
};

//
struct CMD_S_ChiHu
{
	WORD							wChiHuUser;							//
	WORD							wProviderUser;						//
	BYTE							cbChiHuCard;						//
	BYTE							cbCardCount;						//
	LONGLONG						lGameScore;							//
	BYTE							cbWinOrder;							//
};
struct CMD_S_XiaoHu
{
	WORD							wXiaoHuUser;							//
	DWORD                        dwXiaoCode;

	BYTE							cbCardCount;
	BYTE							cbCardData[MAX_COUNT];
};

//
struct CMD_S_GangScore
{
	WORD							wChairId;							//
	BYTE							cbXiaYu;							//
	LONGLONG						lGangScore[GAME_PLAYER];			//
};

//发送扑克
struct CMD_S_UseHaiDi
{
	WORD							wCurrentUser;						//当前用户
};
//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define SUB_C_OUT_CARD				1									//出牌命令
#define SUB_C_OPERATE_CARD			3									//操作扑克
#define SUB_C_TRUSTEE				4									//用户托管
#define SUB_C_XIAOHU				5									//小胡
#define SUB_C_MASTER_LEFTCARD		6									//剩余牌堆
#define SUB_C_MASTER_CHEAKCARD		7									//选择的牌
#define SUB_C_MASTER_ZHANIAO		8									//扎鸟
#define SUB_C_OUT_CARD_CSGANG		9									//长沙杠打出
#define SUB_C_USE_HAIDI			10									//用海底牌
#define SUB_C_PIAO_BEI				11									//票倍数

#define CARD_COLOR_NULL			0
#define CARD_COLOR_TONG			1
#define CARD_COLOR_WAN			2
#define CARD_COLOR_TIAO			3
//出牌命令
struct CMD_C_OutCard
{
	BYTE							cbCardData;							//扑克数据
};
//出牌命令
struct CMD_C_OutCard_CSGang
{
	BYTE							cbCardData1;							//扑克数据
	BYTE							cbCardData2;							//扑克数据
};
//操作命令
struct CMD_C_OperateCard
{
	BYTE							cbCSGangIdex;						//长沙杠操作索引
	DWORD							cbOperateCode;						//操作代码
	BYTE							cbOperateCard;						//操作扑克
};

//用户托管
struct CMD_C_Trustee
{
	bool							bTrustee;							//是否托管	
};

//起手小胡
struct CMD_C_XiaoHu
{
	DWORD						cbOperateCode;						//操作代码
	BYTE							cbOperateCard;						//操作扑克
};

//操作命令
struct CMD_C_Use_HaiDi
{
	DWORD							cbUseHaiDi;							//是否要海底
};

struct CMD_C_PiaoBei
{
	BYTE cbPiaoBei;
};

//////////////////////////////////////////////////////////////////////////

struct  HNMJGameRecordPlayer
{
	DWORD dwUserID;
	std::string kHead;
	std::string kNickName;
	std::vector<BYTE> cbCardData;
	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(dwUserID);
		Stream_VALUE(kHead);
		Stream_VALUE(kNickName);
		Stream_VECTOR(cbCardData);
	}
};

struct  HNMJGameRecordOperateResult
{
	enum Type
	{
		TYPE_NULL,
		TYPE_OperateResult,
		TYPE_SendCard,
		TYPE_OutCard,
		TYPE_ChiHu,
	};
	HNMJGameRecordOperateResult()
	{
		cbActionType = 0;
		wOperateUser = 0;
		wProvideUser = 0;
		cbOperateCode = 0;
		cbOperateCard = 0;
	}
	BYTE							cbActionType;
	WORD							wOperateUser;						//操作用户
	WORD							wProvideUser;						//供应用户
	DWORD							cbOperateCode;						//操作代码
	BYTE							cbOperateCard;						//操作扑克
	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(cbActionType);
		Stream_VALUE(wOperateUser);
		Stream_VALUE(wProvideUser);
		Stream_VALUE(cbOperateCode);
		Stream_VALUE(cbOperateCard);
	}
};
struct  HNMJGameRecord
{
	DWORD dwKindID;
	DWORD dwVersion;
	std::vector<HNMJGameRecordPlayer> kPlayers;
	std::vector<HNMJGameRecordOperateResult> kAction;
	void StreamValue(datastream& kData,bool bSend)
	{
		StructVecotrMember(HNMJGameRecordPlayer,kPlayers);
		StructVecotrMember(HNMJGameRecordOperateResult,kAction);
		Stream_VALUE(dwKindID);
		Stream_VALUE(dwVersion);
	}

};

struct MasterHandCardInfo
{
	int nChairId;
	std::vector<BYTE>    kMasterHandCard;

	void StreamValue(datastream& kData,bool bSend)
	{
		Stream_VALUE(nChairId);
		Stream_VECTOR(kMasterHandCard);
	}
};

struct MasterHandCard
{
	std::vector<MasterHandCardInfo>    kMasterHandCardList;
	void StreamValue(datastream& kData,bool bSend)
	{
		StructVecotrMember(MasterHandCardInfo,kMasterHandCardList);
	}
};
struct MaterCheckCard
{
	BYTE							cbCheakCard;						//操作代码
};

struct MaterNiaoCout
{
	BYTE							cbNiaoCout;							//操作代码
};

struct MasterLeftCard
{
	BYTE      kMasterLeftIndex[MAX_INDEX];
	BYTE      kMasterCheakCard;
};

#pragma pack()
//////////////////////////////////////////////////////////////////////////

#endif
