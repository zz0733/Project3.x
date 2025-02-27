#include "BRNNGameLogic.h"
#include "BRNNDefine.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
BRNNGameLogic::BRNNGameLogic()
{
}

//析构函数
BRNNGameLogic::~BRNNGameLogic()
{
}

E_BRNN_CardType BRNNGameLogic::RetType(int itype)
{
	itype = itype%10;
	switch(itype)
	{
	case 0:
		return E_BRNN_CardType_NiuNiu;
	case 1:
		return E_BRNN_CardType_Niu1;
		break;
	case 2:
		return E_BRNN_CardType_Niu2;
		break;
	case 3:
		return E_BRNN_CardType_Niu3;
		break;
	case 4:
		return E_BRNN_CardType_Niu4;
		break;
	case 5:
		return E_BRNN_CardType_Niu5;
		break;
	case 6:
		return E_BRNN_CardType_Niu6;
		break;
	case 7:
		return E_BRNN_CardType_Niu7;
		break;
	case 8:
		return E_BRNN_CardType_Niu8;
		break;
	case 9:
		return E_BRNN_CardType_Niu9;
		break;
	default :
		return E_BRNN_CardType_Point;
		break;
	}

}
//获取牌型
E_BRNN_CardType BRNNGameLogic::GetCardType(const BYTE cbCardData[], BYTE cbCardCount,BYTE bcOutCadData[] )
{
	//合法判断
	if (5!=cbCardCount) return E_BRNN_CardType_Error;

	//排序扑克
	BYTE cbCardDataSort[CARD_COUNT];
	memcpy(cbCardDataSort,cbCardData,sizeof(BYTE)*cbCardCount);
	SortCardList(cbCardDataSort,cbCardCount,ST_NEW);

	if(bcOutCadData != NULL)
	{
		memcpy(bcOutCadData,cbCardDataSort,cbCardCount);
	}

	int igetW= 0;


	if(GetCardNewValue(cbCardDataSort[0])==GetCardNewValue(cbCardDataSort[cbCardCount-2]))
	{
		if(bcOutCadData != NULL)
		{
			memcpy(bcOutCadData,cbCardDataSort,cbCardCount);
		}
		return E_BRNN_CardType_Bomb;
	}else
	{
		if(GetCardNewValue(cbCardDataSort[1])==GetCardNewValue(cbCardDataSort[cbCardCount-1]))
		{
			if(bcOutCadData != NULL)
			{
				memcpy(bcOutCadData,cbCardDataSort,cbCardCount);
			}
			return E_BRNN_CardType_Bomb;
		}

	}
	if(GetCardColor(cbCardDataSort[0])==0x04&&GetCardColor(cbCardDataSort[1])==0x04)
	{
		if(GetCardNewValue(cbCardDataSort[2])==GetCardNewValue(cbCardDataSort[3]))
		{
			if(bcOutCadData != NULL)
			{
				bcOutCadData[0] = cbCardDataSort[2];
				bcOutCadData[1] = cbCardDataSort[3];
				bcOutCadData[2] = cbCardDataSort[0];
				bcOutCadData[3] = cbCardDataSort[1];
				bcOutCadData[4] = cbCardDataSort[4];

			}
			return E_BRNN_CardType_Bomb;
		}else
		{
			if(GetCardNewValue(cbCardDataSort[3])==GetCardNewValue(cbCardDataSort[4]))
			{
				if(bcOutCadData != NULL)
				{
					bcOutCadData[0] = cbCardDataSort[0];
					bcOutCadData[1] = cbCardDataSort[1];
					bcOutCadData[2] = cbCardDataSort[3];
					bcOutCadData[3] = cbCardDataSort[4];
					bcOutCadData[4] = cbCardDataSort[2];

				}
				return E_BRNN_CardType_Bomb;
			}

		}	

	}
	if(GetCardColor(cbCardDataSort[0])==0x04)
	{
		if(GetCardNewValue(cbCardDataSort[1])==GetCardNewValue(cbCardDataSort[3]))
		{
			if(bcOutCadData != NULL)
			{
				bcOutCadData[0] = cbCardDataSort[1];
				bcOutCadData[1] = cbCardDataSort[2];
				bcOutCadData[2] = cbCardDataSort[3];
				bcOutCadData[3] = cbCardDataSort[0];
				bcOutCadData[4] = cbCardDataSort[4];

			}
			return E_BRNN_CardType_Bomb;
		}else
		{
			if(GetCardNewValue(cbCardDataSort[2])==GetCardNewValue(cbCardDataSort[4]))
			{
				if(bcOutCadData != NULL)
				{
					bcOutCadData[0] = cbCardDataSort[2];
					bcOutCadData[1] = cbCardDataSort[3];
					bcOutCadData[2] = cbCardDataSort[4];
					bcOutCadData[3] = cbCardDataSort[0];
					bcOutCadData[4] = cbCardDataSort[1];

				}
				return E_BRNN_CardType_Bomb;
			}

		}	

	}
	bool blBig = true;
	int iCount = 0;
	int iLogicValue = 0;
	int iValueTen = 0;
	for (int i = 0;i<cbCardCount;i++)
	{
		BYTE bcGetValue = GetCardLogicValue(cbCardDataSort[i]);
		if(bcGetValue!=10&&bcGetValue!=11)
		{

			blBig = false;
			break;

		}else
		{
			if(GetCardNewValue(cbCardDataSort[i])==10)
			{
				iValueTen++;
			}
		}
		iCount++;
	}
	if(blBig)
	{
		if(bcOutCadData != NULL)
		{
			memcpy(bcOutCadData,cbCardDataSort,cbCardCount);
		}
		if(iValueTen==0)
			return E_BRNN_CardType_GoldNiu;
		else
		{
			if(iValueTen==1)
			{
				return E_BRNN_CardType_SilverNiu;
			}
		}
	}

	int n = 0;

	BYTE bcMakeMax[5];
	memset(bcMakeMax, 0, sizeof(bcMakeMax));
	int iBigValue = 0;
	BYTE iSingleA[2];
	int iIndex = 0;
	bcMakeMax[0]= cbCardDataSort[n];

	int iGetTenCount = 0;

	for (int iten = 0;iten<cbCardCount;iten++)
	{
		if(GetCardLogicValue(cbCardDataSort[iten])==10||GetCardLogicValue(cbCardDataSort[iten])==11)
		{
			iGetTenCount++;

		}
	}
	if( iGetTenCount>=3)
	{
		if(GetCardColor(cbCardDataSort[0])==0x04&&GetCardColor(cbCardDataSort[1])==0x04)
		{
			if(bcOutCadData != NULL)
			{
				bcOutCadData[0] = cbCardDataSort[0];
				bcOutCadData[1] = cbCardDataSort[3];
				bcOutCadData[2] = cbCardDataSort[4];
				bcOutCadData[3] = cbCardDataSort[1];
				bcOutCadData[4] = cbCardDataSort[2];

			}
			return E_BRNN_CardType_BigNiu;

		}
		if(GetCardColor(cbCardDataSort[0])==0x04)
		{
			//大小王与最小的组合成牛 
			if(bcOutCadData != NULL)
			{
				bcOutCadData[0] = cbCardDataSort[0];
				bcOutCadData[1] = cbCardDataSort[3];
				bcOutCadData[2] = cbCardDataSort[4];
				bcOutCadData[3] = cbCardDataSort[1];
				bcOutCadData[4] = cbCardDataSort[2];
			}
			if(cbCardDataSort[0]==0x42)
				return E_BRNN_CardType_BigNiu;
			else
				return E_BRNN_CardType_SmallNiu;
		}else
		{
			return RetType(GetCardLogicValue(cbCardDataSort[3])+GetCardLogicValue(cbCardDataSort[4]));
		}

	}
	if(iGetTenCount==2||(iGetTenCount==1&&GetCardColor(cbCardDataSort[0])==0x04))
	{

		if(GetCardColor(cbCardDataSort[0])==0x04&&GetCardColor(cbCardDataSort[1])==0x04)
		{
			if(bcOutCadData != NULL)
			{
				bcOutCadData[0] = cbCardDataSort[0];
				bcOutCadData[1] = cbCardDataSort[3];
				bcOutCadData[2] = cbCardDataSort[4];
				bcOutCadData[3] = cbCardDataSort[1];
				bcOutCadData[4] = cbCardDataSort[2];
			}
			return E_BRNN_CardType_BigNiu;
		}else
		{
			//如果有一张王 其他任意三张组合为10则是牛牛
			if(GetCardColor(cbCardDataSort[0])==0x04)
			{

				for ( n=1;n<cbCardCount;n++)
				{
					for (int j = 1;j<cbCardCount;j++)
					{
						if(j != n)
						{
							for (int w = 1;w<cbCardCount;w++)
							{
								if(w != n&&w!=j)
								{
									//如果剩余的四张中任意三张能组合位10的整数倍

									if((GetCardLogicValue(cbCardDataSort[n])+GetCardLogicValue(cbCardDataSort[j])+GetCardLogicValue(cbCardDataSort[w]))%10==0)
									{

										int add = 0;
										for (int y = 1;y<cbCardCount;y++)
										{
											if(y != n&&y!=j&&y!=w)
											{
												iSingleA[add] =cbCardDataSort[y]; 
												add++;

											}

										}
										if(bcOutCadData != NULL)
										{
											bcOutCadData[0] = cbCardDataSort[n];
											bcOutCadData[1] = cbCardDataSort[j];
											bcOutCadData[2] = cbCardDataSort[w];
											bcOutCadData[3] = cbCardDataSort[0];
											bcOutCadData[4] = iSingleA[0];
										}
										if(cbCardDataSort[0]==0x42)
											return E_BRNN_CardType_BigNiu;
										else
											return E_BRNN_CardType_SmallNiu;


									}
								}
							}
						}
					}
				}
				//如果有一张王 其他任意三张组合不为10则 取两张点数最大的组合
				BYTE bcTmp[4];
				int iBig = 0;
				int in = 0;
				for ( in = 1;in<cbCardCount;in++)
				{
					for (int j = 1;j<cbCardCount;j++)
					{
						if(in != j)
						{
							BYTE bclogic = (GetCardLogicValue(cbCardDataSort[in])+GetCardLogicValue(cbCardDataSort[j]))%10;
							if(bclogic>iBig)
							{
								iBig = bclogic;
								int add = 0;
								bcTmp[0]=cbCardDataSort[in];
								bcTmp[1]=cbCardDataSort[j];
								for (int y = 1;y<cbCardCount;y++)
								{
									if(y != in&&y!=j)
									{
										iSingleA[add] =cbCardDataSort[y]; 
										add++;
									}

								}
								bcTmp[2]=iSingleA[0];
								bcTmp[3]=iSingleA[1];

							}

						}
					}   
				}

				if(bcOutCadData != NULL)
				{
					bcOutCadData[0] = cbCardDataSort[0];
					bcOutCadData[1] = bcTmp[2];
					bcOutCadData[2] = bcTmp[3];
					bcOutCadData[3] = bcTmp[0];
					bcOutCadData[4] = bcTmp[1];
				}
				if(iGetTenCount==1&&GetCardColor(cbCardDataSort[0])==0x04)
				{
					//下面还能组合 有两张为 10 也可以组合成牛牛

				}else
				{
					//如果没有则比较 完与最小组合最大点数和组合
					return RetType(GetCardLogicValue(bcTmp[0])+GetCardLogicValue(bcTmp[1]));
				}

			
			}else
			{
				if((GetCardLogicValue(cbCardDataSort[2])+GetCardLogicValue(cbCardDataSort[3])+GetCardLogicValue(cbCardDataSort[4]))%10==0)
				{
					if(bcOutCadData != NULL)
					{
						bcOutCadData[0] = cbCardDataSort[2];
						bcOutCadData[1] = cbCardDataSort[3];
						bcOutCadData[2] = cbCardDataSort[4];
						bcOutCadData[3] = cbCardDataSort[0];
						bcOutCadData[4] = cbCardDataSort[1];
					}
					return E_BRNN_CardType_NiuNiu;
				}else
				{
					for ( n= 2;n<cbCardCount;n++)
					{
						for (int j = 2;j<cbCardCount;j++)
						{
							if(j != n)
							{
								if((GetCardLogicValue(cbCardDataSort[n])+GetCardLogicValue(cbCardDataSort[j]))%10==0)
								{
									int add = 0;
									for (int y = 2;y<cbCardCount;y++)
									{
										if(y != n&&y!=j)
										{
											iSingleA[add] =cbCardDataSort[y]; 
											add++;

										}
									}
									if(iBigValue<=iSingleA[0]%10)
									{
										iBigValue = GetCardLogicValue(iSingleA[0])%10;
										if(bcOutCadData != NULL)
										{
											bcOutCadData[0]= cbCardDataSort[0];
											bcOutCadData[1]= cbCardDataSort[n]; 
											bcOutCadData[2]= cbCardDataSort[j]; 
											bcOutCadData[3]= cbCardDataSort[1];
											bcOutCadData[4]= iSingleA[0]; 

										}

										if(iBigValue==0)
										{

											return E_BRNN_CardType_NiuNiu;
										}
									}

								}
							}
						}
					}
					if(iBigValue != 0)
					{
						return RetType(iBigValue);
					}
				}
			}

		}

		iGetTenCount = 1;

	}
	//4个组合
	if(iGetTenCount==1)
	{
		if(GetCardColor(cbCardDataSort[0])==0x04)
		{
			for ( n= 1;n<cbCardCount;n++)
			{
				for (int j = 1;j<cbCardCount;j++)
				{
					if(j != n)
					{
						//任意两张组合成牛
						if((GetCardLogicValue(cbCardDataSort[n])+GetCardLogicValue(cbCardDataSort[j]))%10==0)
						{
							int add = 0;
							for (int y = 1;y<cbCardCount;y++)
							{
								if(y != n&&y!=j)
								{
									iSingleA[add] =cbCardDataSort[y]; 
									add++;

								}

							}

							if(bcOutCadData != NULL)
							{
								bcOutCadData[0] = cbCardDataSort[0];
								bcOutCadData[1] = iSingleA[0];
								bcOutCadData[2] = iSingleA[1];
								bcOutCadData[3] = cbCardDataSort[n];
								bcOutCadData[4] = cbCardDataSort[j];
							}
							if(cbCardDataSort[0]==0x42)
								return E_BRNN_CardType_BigNiu;
							else
								return E_BRNN_CardType_SmallNiu;

						}
					}

				}
			}

			//取4张中组合最大的点数

			BYTE bcTmp[4];
			int iBig = 0;
			int in = 0;
			for ( in = 1;in<cbCardCount;in++)
			{
				for (int j = 1;j<cbCardCount;j++)
				{
					if(in != j)
					{
						BYTE bclogic = (GetCardLogicValue(cbCardDataSort[in])+GetCardLogicValue(cbCardDataSort[j]))%10;
						if(bclogic>iBig)
						{
							iBig = bclogic;
							int add = 0;
							bcTmp[0]=cbCardDataSort[in];
							bcTmp[1]=cbCardDataSort[j];
							for (int y = 1;y<cbCardCount;y++)
							{
								if(y != in&&y!=j)
								{
									iSingleA[add] =cbCardDataSort[y]; 
									add++;
								}

							}
							bcTmp[2]=iSingleA[0];
							bcTmp[3]=iSingleA[1];

						}

					}
				}   
			}

			if(bcOutCadData != NULL)
			{
				bcOutCadData[0] = cbCardDataSort[0];
				bcOutCadData[1] = bcTmp[2];
				bcOutCadData[2] = bcTmp[3];
				bcOutCadData[3] = bcTmp[0];
				bcOutCadData[4] = bcTmp[1];
			}
			return RetType(GetCardLogicValue(bcTmp[0])+GetCardLogicValue(bcTmp[1]));

		}
		//取4张中任两张组合为10 然后求另外两张的组合看是否是组合中最大
		for ( n= 1;n<cbCardCount;n++)
		{
			for (int j = 1;j<cbCardCount;j++)
			{
				if(j != n)
				{
					if((GetCardLogicValue(cbCardDataSort[n])+GetCardLogicValue(cbCardDataSort[j]))%10==0)
					{
						int add = 0;
						for (int y = 1;y<cbCardCount;y++)
						{
							if(y != n&&y!=j)
							{
								iSingleA[add] =cbCardDataSort[y]; 
								add++;

							}

						}
						if(iBigValue<=(GetCardLogicValue(iSingleA[0])+GetCardLogicValue(iSingleA[1]))%10)
						{
							iBigValue = GetCardLogicValue(iSingleA[0])+GetCardLogicValue(iSingleA[1])%10;
							bcMakeMax[0]= cbCardDataSort[0];
							bcMakeMax[1]= cbCardDataSort[j];
							bcMakeMax[2]= cbCardDataSort[n]; 
							bcMakeMax[3]= iSingleA[0]; 
							bcMakeMax[4]= iSingleA[1]; 

							if(bcOutCadData != NULL)
							{
								memcpy(bcOutCadData,bcMakeMax,cbCardCount);
							}
							if(iBigValue==0)
							{

								return E_BRNN_CardType_NiuNiu;
							}
						}

					}
				}
			}
		}
		if(iBigValue!= 0)
		{
			return RetType(iBigValue);
		}else
		{
			//如果组合不成功
			iGetTenCount = 0;
		}

	}
	if(iGetTenCount==0)
	{
		//5个组合
		for ( n= 0;n<cbCardCount;n++)
		{
			for (int j = 0;j<cbCardCount;j++)
			{
				if(j != n)
				{
					for (int w = 0;w<cbCardCount;w++)
					{
						if(w != n&&w!=j)
						{
							int valueAdd = GetCardLogicValue(cbCardDataSort[n]);
							valueAdd += GetCardLogicValue(cbCardDataSort[j]);
							valueAdd += GetCardLogicValue(cbCardDataSort[w]);

							if(valueAdd%10==0)
							{
								int add = 0;
								for (int y = 0;y<cbCardCount;y++)
								{
									if(y != n&&y!=j&&y!=w)
									{
										iSingleA[add] =cbCardDataSort[y]; 
										add++;

									}

								}
								if(iBigValue<=(GetCardLogicValue(iSingleA[0])+GetCardLogicValue(iSingleA[1]))%10)
								{
									iBigValue = GetCardLogicValue(iSingleA[0])+GetCardLogicValue(iSingleA[1])%10;
									bcMakeMax[0]= cbCardDataSort[n];
									bcMakeMax[1]= cbCardDataSort[j];
									bcMakeMax[2]= cbCardDataSort[w]; 
									bcMakeMax[3]= iSingleA[0]; 
									bcMakeMax[4]= iSingleA[1]; 

									if(bcOutCadData != NULL)
									{
										memcpy(bcOutCadData,bcMakeMax,cbCardCount);
									}
									if(iBigValue==0)
									{

										return E_BRNN_CardType_NiuNiu;
									}
								}

							}

						}
					}
				}
			}		
		}
		if(iBigValue!=0)
		{
			return RetType(iBigValue);
		}	
		else
		{
			return E_BRNN_CardType_Point;
		}

	}

	return E_BRNN_CardType_Point;
}

//大小比较
/*
cbNextCardData>cbFirstCardData  返回1
cbNextCardData<cbFirstCardData  返回-1
cbNextCardData==cbFirstCardData 返回0
*/
//Multiple 比较出来的倍数
int BRNNGameLogic::CompareCard(const BYTE cbFirstCardData[], BYTE cbFirstCardCount,const BYTE cbNextCardData[], BYTE cbNextCardCount,BYTE &Multiple)
{
	//合法判断
	if (!(5==cbFirstCardCount && 5==cbNextCardCount)) return 0;

	//获取牌型
	BYTE cbFirstCardType=GetCardType(cbFirstCardData, cbFirstCardCount);
	BYTE cbNextCardType=GetCardType(cbNextCardData, cbNextCardCount);

	//牌型比较
	if (cbFirstCardType != cbNextCardType) 
	{
		if (cbNextCardType > cbFirstCardType)
		{
			switch(cbNextCardType)
			{
			case E_BRNN_CardType_Point:
			case E_BRNN_CardType_Niu1:
			case E_BRNN_CardType_Niu2:
			case E_BRNN_CardType_Niu3:
			case E_BRNN_CardType_Niu4:
			case E_BRNN_CardType_Niu5:
			case E_BRNN_CardType_Niu6:
				{
					Multiple=1;
					break;

				}
			case E_BRNN_CardType_Niu7:
				{
					Multiple=2;
					break;
				}
			case E_BRNN_CardType_Niu8:
				{
					Multiple=3;
					break;
				}
			case E_BRNN_CardType_Niu9:
				{
					Multiple=4;
					break;
				}
			case E_BRNN_CardType_SmallNiu:
			case E_BRNN_CardType_BigNiu:
			case E_BRNN_CardType_NiuNiu:
			case E_BRNN_CardType_SilverNiu:
			case E_BRNN_CardType_GoldNiu:
			case E_BRNN_CardType_Bomb:
				{
					Multiple = 5;
					break;
				}
			default:
				{
					Multiple = 1;
					break;
				}
			}
// 			if(cbNextCardType>=12)
// 			{
// 				Multiple = 10;
// 
// 			}else
// 			{
// 				Multiple = cbNextCardType-2;
// 
// 			}
			return 1;

		}
		else
		{
			switch(cbFirstCardType)
			{
			case E_BRNN_CardType_Point:
			case E_BRNN_CardType_Niu1:
			case E_BRNN_CardType_Niu2:
			case E_BRNN_CardType_Niu3:
			case E_BRNN_CardType_Niu4:
			case E_BRNN_CardType_Niu5:
			case E_BRNN_CardType_Niu6:
				{
					Multiple=1;
					break;

				}
			case E_BRNN_CardType_Niu7:
				{
					Multiple=2;
					break;
				}
			case E_BRNN_CardType_Niu8:
				{
					Multiple=3;
					break;
				}
			case E_BRNN_CardType_Niu9:
				{
					Multiple=4;
					break;
				}
			case E_BRNN_CardType_SmallNiu:
			case E_BRNN_CardType_BigNiu:
			case E_BRNN_CardType_NiuNiu:
			case E_BRNN_CardType_SilverNiu:
			case E_BRNN_CardType_GoldNiu:
			case E_BRNN_CardType_Bomb:
				{
					Multiple = 5;
					break;
				}
			default:
				{
					Multiple = 1;
					break;
				}
			}			return -1;
		}
	}

	//特殊牌型判断
	if (E_BRNN_CardType_Point!=cbFirstCardType && cbFirstCardType==cbNextCardType)
	{
		//排序扑克
		BYTE cbFirstCardDataTmp[CARD_COUNT], cbNextCardDataTmp[CARD_COUNT];

		memcpy(cbFirstCardDataTmp,cbFirstCardData,sizeof(BYTE)*cbFirstCardCount);
		memcpy(cbNextCardDataTmp,cbNextCardData,sizeof(BYTE)*cbNextCardCount);
		SortCardList(cbFirstCardDataTmp,cbFirstCardCount,ST_NEW);
		SortCardList(cbNextCardDataTmp,cbNextCardCount,ST_NEW);

		switch(cbFirstCardType)
		{
		case E_BRNN_CardType_Point:
		case E_BRNN_CardType_Niu1:
		case E_BRNN_CardType_Niu2:
		case E_BRNN_CardType_Niu3:
		case E_BRNN_CardType_Niu4:
		case E_BRNN_CardType_Niu5:
		case E_BRNN_CardType_Niu6:
			{
				Multiple=1;
				break;

			}
		case E_BRNN_CardType_Niu7:
			{
				Multiple=2;
				break;
			}
		case E_BRNN_CardType_Niu8:
			{
				Multiple=3;
				break;
			}
		case E_BRNN_CardType_Niu9:
			{
				Multiple=4;
				break;
			}
		case E_BRNN_CardType_SmallNiu:
		case E_BRNN_CardType_BigNiu:
		case E_BRNN_CardType_NiuNiu:
		case E_BRNN_CardType_SilverNiu:
		case E_BRNN_CardType_GoldNiu:
		case E_BRNN_CardType_Bomb:
			{
				Multiple = 5;
				break;
			}
		default:
			{
				Multiple = 1;
				break;
			}
		}
		BYTE firstValue = GetCardNewValue(cbFirstCardDataTmp[0]);
		BYTE NextValue = GetCardNewValue(cbNextCardDataTmp[0]);

		BYTE firstColor = GetCardColor(cbFirstCardDataTmp[0]);

		BYTE NextColor = GetCardColor(cbNextCardDataTmp[0]);


		if(firstValue<NextValue)
		{
			return 1;
		}else
		{
			if(firstValue==NextValue)
			{
				if(firstColor<NextColor)
				{
					return 1;

				}else
				{
					return -1;
				}
			}
			return -1;
		}

	}

	//排序扑克
	BYTE cbFirstCardDataTmp[CARD_COUNT], cbNextCardDataTmp[CARD_COUNT];
	memcpy(cbFirstCardDataTmp,cbFirstCardData,sizeof(BYTE)*cbFirstCardCount);
	memcpy(cbNextCardDataTmp,cbNextCardData,sizeof(BYTE)*cbNextCardCount);
	SortCardList(cbFirstCardDataTmp,cbFirstCardCount,ST_NEW);
	SortCardList(cbNextCardDataTmp,cbNextCardCount,ST_NEW);

	BYTE firstValue = GetCardNewValue(cbFirstCardDataTmp[0]);
	BYTE NextValue = GetCardNewValue(cbNextCardDataTmp[0]);
	BYTE firstColor = GetCardColor(cbFirstCardDataTmp[0]);
	BYTE NextColor = GetCardColor(cbNextCardDataTmp[0]);

	if(firstValue<NextValue)
	{
		return 1;
	}else
	{
		if(firstValue==NextValue)
		{
			if(firstColor<NextColor)
			{
				return 1;

			}else
			{
				return -1;
			}
		}
		return -1;
	}

}

//获取牌点
BYTE BRNNGameLogic::GetCardListPip(const BYTE cbCardData[], BYTE cbCardCount)
{
	//变量定义
	BYTE cbPipCount=0;

	//获取牌点
	BYTE cbCardValue=0;
	for (BYTE i=0;i<cbCardCount;i++)
	{
		cbCardValue=GetCardValue(cbCardData[i]);
		if(cbCardValue>10)
		{
			cbCardValue = 10;

		}
		cbPipCount+=cbCardValue;
	}
	return (cbPipCount%10);
}
BYTE BRNNGameLogic::GetCardNewValue(BYTE cbCardData)
{
	//扑克属性
	BYTE cbCardColor=GetCardColor(cbCardData);
	BYTE cbCardValue=GetCardValue(cbCardData);

	//转换数值
	if (cbCardColor==0x04) return cbCardValue+13+2;
	return cbCardValue;

}
//逻辑大小
BYTE BRNNGameLogic::GetCardLogicValue(BYTE cbCardData)
{
	BYTE cbValue=GetCardValue(cbCardData);

	//获取花色
	BYTE cbColor=GetCardColor(cbCardData);

	if(cbValue>10)
	{
		cbValue = 10;

	}
	if(cbColor==0x4)
	{
		return 11;
	}
	return cbValue;
}

//排列扑克
void BRNNGameLogic::SortCardList(BYTE cbCardData[], BYTE cbCardCount, BYTE cbSortType)
{
	//数目过虑
	if (cbCardCount==0) return;

	//转换数值
	BYTE cbSortValue[CARD_COUNT];
	if (ST_VALUE==cbSortType)
	{
		for (BYTE i=0;i<cbCardCount;i++) cbSortValue[i]=GetCardValue(cbCardData[i]);	
	}
	else 
	{
		if(cbSortType==ST_NEW)
		{
			for (BYTE i=0;i<cbCardCount;i++) cbSortValue[i]=GetCardNewValue(cbCardData[i]);	

		}else
		{
			for (BYTE i=0;i<cbCardCount;i++) cbSortValue[i]=GetCardLogicValue(cbCardData[i]);	

		}

	}


	//排序操作
	bool bSorted=true;
	BYTE cbThreeCount,cbLast=cbCardCount-1;
	do
	{
		bSorted=true;
		for (BYTE i=0;i<cbLast;i++)
		{
			if ((cbSortValue[i]<cbSortValue[i+1])||
				((cbSortValue[i]==cbSortValue[i+1])&&(cbCardData[i]<cbCardData[i+1])))
			{
				//交换位置
				cbThreeCount=cbCardData[i];
				cbCardData[i]=cbCardData[i+1];
				cbCardData[i+1]=cbThreeCount;
				cbThreeCount=cbSortValue[i];
				cbSortValue[i]=cbSortValue[i+1];
				cbSortValue[i+1]=cbThreeCount;
				bSorted=false;
			}	
		}
		cbLast--;
	} while(bSorted==false);

	return;
}

//////////////////////////////////////////////////////////////////////////

