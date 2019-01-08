#pragma once
#include "cwBasicStrategy.h"

class cwStrategyDemo :
	public cwBasicStrategy
{
public:
	cwStrategyDemo();
	~cwStrategyDemo();

	//MarketData SPI
	///�������
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);

	//Trade SPI
	///�ɽ��ر�
	virtual void OnRtnTrade(cwTradePtr pTrade);
	//�����ر�
	virtual void OnRtnOrder(cwOrderPtr pOrder);
	//�����ɹ�
	virtual void OnOrderCanceled(cwOrderPtr pOrder);

	std::string m_strCurrentUpdateTime;
};

