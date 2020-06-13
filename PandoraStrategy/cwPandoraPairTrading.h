//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	author: Wu Chang Sheng
//---
//---	CreateTime:	2020/05/20
//---
//---	VerifyTime:	2020/05/30
//---
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

//PairTrading may use for arbitrage

#pragma once
#include "cwBasicKindleStrategy.h"
#include "cwStrategyLog.h"
#include "cwBasicCout.h"


class cwPandoraPairTrading :
	public cwBasicKindleStrategy
{
public:
	cwPandoraPairTrading();
	~cwPandoraPairTrading();


	///MarketData SPI
//�������
	virtual void PriceUpdate(cwMarketDataPtr pPriceData);

	///Trade SPI
	//�ɽ��ر�
	virtual void OnRtnTrade(cwTradePtr pTrade) {};
	//�����ر�, pOrderΪ���±�����pOriginOrderΪ��һ�θ��±����ṹ�壬�п���ΪNULL
	virtual void OnRtnOrder(cwOrderPtr pOrder, cwOrderPtr pOriginOrder = cwOrderPtr()) {};
	//�����ɹ�
	virtual void OnOrderCanceled(cwOrderPtr pOrder) {};
	//����¼��������Ӧ
	virtual void OnRspOrderInsert(cwOrderPtr pOrder, cwFtdcRspInfoField * pRspInfo) {};
	//��������������Ӧ
	virtual void OnRspOrderCancel(cwOrderPtr pOrder, cwFtdcRspInfoField * pRspInfo) {};
	//�����Խ��׳�ʼ�����ʱ�����OnReady, �����ڴ˺��������Եĳ�ʼ������
	virtual void OnReady();
	
	//���Խ��״�������Լ
	void		 DoManualSpread();
	//���Ը��ݴ�������Լ�ֲ֣��µ�������Լ�Գ塣
	//void		 LockPosition();
protected:
	std::string					m_MainInstrumentID;				//������Լ
	std::string					m_SubMainInstrumentID;			//��������Լ

	//�۲��Ϊ����-������
	double						m_dBuyThreadHold;				//�۲�����ֵ
	double						m_dSellThreadHold;				//�۲�����ֵ
	
	double						m_dVolumeCoefficient;			//�Գ����

	cwMarketDataPtr				m_cwMainMarketData;				//������Լ����
	cwMarketDataPtr				m_cwSubMainMarketData;			//��������Լ����

	cwOpenCloseMode				m_cwMainOpenCloseMode;			//������ƽģʽ
	cwOpenCloseMode				m_cwSubMainOpenCloseMode;		//��������ƽģʽ

	int							m_iPositionLimit;				//�ֲ�����
	int							m_iOrderVolume;					//��������

	cwStrategyLog				m_StrategyLog;					//������־
	cwBasicCout					m_cwShow;						//cout

	std::string					m_strCurrentUpdateTime;			//��������ʱ��
};

