﻿#ifndef __GuangDong11Xuan5CartCart__
#define __GuangDong11Xuan5CartCart__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
#include "GuangDong11Xuan5WuFen.h"
#include "Define.h"
#include "ChaseNumBerLayer.h"
#include "LotteryGlobal.h"
USING_NS_CC;
using namespace std;
using namespace extension;

#define DELETE_SPRITE_TAG			50
class GuangDong11Xuan5Cart : public Layer, public TableViewDelegate,
	public TableViewDataSource
{
public:
    GuangDong11Xuan5Cart();
    ~GuangDong11Xuan5Cart();
    CREATE_FUNC(GuangDong11Xuan5Cart);
    virtual bool init();
    static Scene* scene();
    virtual void onEnter();
    virtual void onExit();
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);		

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual cocos2d::Size cellSizeForTable(TableView *table);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);

	void bottomMenuEnabled(bool GuangDong11Xuan5BoolSuccen);

private:
	void initData();
	void initView();		
	//top menu
	void back(Object *obj);
	//bottom menu
	void confirm(Object *obj);

	Vec2 startPoint;
	Vec2 endPoint;

	void pressChaseNumShow(Object *obj);
	void deleRandom(Object* obj);
	//beilv

	void pressDeleteButton(int index);
	void updateBetInfo();
	void ZhuiHaoItemMinusobj(Object *obj);
	void SetusedBonusRet(Object *obj);
	void RemoveCurrentLayer(Object *obj);
	void RefreshData(Object *obj);	

	void ZhuiHaoback(Object *obj);
	void ShowIsChaseNum();
	void dissisChaseNum();	

	int	selectedItemTag;	
	cocos2d::Size winSize;	
	TableView *gameResultTable;
	LabelTTF *KindTTfle;
	float cellHeight;	
	LabelTTF* lotteryIdLabel; //注数
	LabelTTF* MoenyIdLabel; //合计	
	ChaseNumBerLayer* ZhuiHao11Xuan5Cart;
	MenuItemSprite *confirmItem;
	Menu *pCloseButton;
	//底部
	Menu *bottomMenu;
	//清空
	Menu *transactionMenu;
};

#endif // __HELLOWORLD_SCENE_H__