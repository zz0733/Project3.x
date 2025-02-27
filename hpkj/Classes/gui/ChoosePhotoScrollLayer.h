#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChoosePhotoScrollLayer : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	bool intPhotoScrollLayerWith(int type,int num);
	static ChoosePhotoScrollLayer* PhotoScrollLayerWith(int type,int num);

	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {}
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual cocos2d::Size cellSizeForTable(TableView *table);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	ChoosePhotoScrollLayer(void);
	~ChoosePhotoScrollLayer(void);
private:
	int m_nType;
	int m_nMessageNum;
	
};