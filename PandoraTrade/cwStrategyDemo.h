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

	///����Ӧ��
	virtual void OnRspError(cwFtdcRspInfoField *pRspInfo);
	///����¼��������Ӧ
	virtual void OnRspOrderInsert(cwOrderPtr pOrder, cwFtdcRspInfoField *pRspInfo);
	///��������������Ӧ
	virtual void OnRspOrderCancel(cwOrderPtr pOrder, cwFtdcRspInfoField *pRspInfo);

	std::string m_strCurrentUpdateTime;
};

