#pragma once
#include <vector>
#include <set>
#include "cwProductTradeTime.h"
#include "cwTradeCommonDefine.h"
#include "cwStrategyLog.h"

enum cwOpenCloseMode:int
{
	CloseTodayThenYd = 0,//��ƽ����ƽ��,�ɿ�������ƽ�����Ʒ��
	OpenOnly = 1,//ֻ��
	CloseOnly = 2,//ֻƽ
	CloseYdThenOpen = 3,//��ƽ�򣬺󿪲֣���ƽ������ƽ��ܹ��Ʒ�֣��ײ���Ҫ��ȫ��ƽ���ٿ���
	CloseYdOrOpen = 4,//����ƽ�򣬿ɿ��֣����ֺ���ƽ�֣�����ƽ��ܹ��Ʒ�֣��ֲ����󿪲֣��ײ�����һ����ֿ���ûƽ
	CloseYdThenToday = 5//��ƽ����ƽ��,�ɿ�������ƽ����ˣ�ƽ��Ϳ��ֲ���Ʒ��
};

enum cwInsertOrderType:int
{
	cwInsertLimitOrder = 0,			//�޼۵�
	cwInsertFAKOrder = 1,			//FAK 
	cwInsertFOKOrder = 2,			//FOK
	cwInsertMarketOrder				//�м۵����ݲ�֧�֣�
};

class cwBasicStrategy
{
public:
	cwBasicStrategy();
	~cwBasicStrategy();

	//��ʾϵͳ�Ƿ��ʼ����ɣ������������б���������
	bool	m_bStrategyReady;

	//��ʾ��������
	virtual std::string  GetStrategyName() { return "BasicStrategy"; }

	///MarketData SPI
	//�������
	virtual void PriceUpdate(cwMarketDataPtr pPriceData) = 0;
	
	///Trade SPI
	//�ɽ��ر�
	virtual void OnRtnTrade(cwTradePtr pTrade) = 0;
	//�����ر�
	virtual void OnRtnOrder(cwOrderPtr pOrder) = 0;
	//�����ɹ�
	virtual void OnOrderCanceled(cwOrderPtr pOrder) = 0;


	virtual void InitialStrategy(const char * pConfigFilePath);
	std::string			m_strConfigFileFullPath;

	///Action  Function
	//��ȡ���µ�����
	cwMarketDataPtr	GetLastestMarketData(std::string InstrumentID);
	//��ȡ�˻���Ϣ
	cwAccountPtr GetAccount();
	//��ȡ�ҵ��б�����map���ڷ�����Ϣ�����ر������ΪKey
	bool GetActiveOrders(std::map<std::string, cwOrderPtr>& ActiveOrders);		///key OrderRef
	//��ȡ�ҵ��б�����map���ڷ�����Ϣ�����ر������ΪKey
	bool GetActiveOrders(std::string InstrumentID, std::map<std::string, cwOrderPtr>& ActiveOrders);		///key OrderRef
	//��ȡ�ҵ��б�����map���ڷ�����Ϣ�����ر������ΪKey
	int GetActiveOrdersLong(std::string InstrumentID);		///key OrderRef
	//��ȡ�ҵ��б�����map���ڷ�����Ϣ�����ر������ΪKey
	int GetActiveOrdersShort(std::string InstrumentID);		///key OrderRef
	//��ȡ���б����б�����map���ڷ�����Ϣ���������������ΪKey
	bool GetAllOrders(std::map<std::string, cwOrderPtr>& Orders);				///Key OrderSysID
	//��ȡ�ֲ��б�����map���ڷ�����Ϣ����ԼIDΪKey
	bool GetPositions(std::map<std::string, cwPositionPtr>& PositionMap);		///Key InstrumentID
	//��ȡ�ֲֺ͹ҵ��б�
	bool GetPositionsAndActiveOrders(std::map<std::string, cwPositionPtr>& PositionMap,
		std::map<std::string, cwOrderPtr>& ActiveOrders);
	bool GetPositionsAndActiveOrders(std::string InstrumentID, cwPositionPtr& pPosition, std::map<std::string, cwOrderPtr>& ActiveOrders);
	//��ȡ��Լ��Ϣ
	cwInstrumentDataPtr GetInstrumentData(std::string InstrumentID);
	//��������
	cwOrderPtr InputLimitOrder(const char * szInstrumentID, cwFtdcDirectionType direction, cwOpenClose openclose, int volume, double price);
	//�򻯱��������� volume����ʾ�򣬸���ʾ�����Զ���ƽ���гֲ־�ƽ�֣�û�оͿ���
	cwOrderPtr EasyInputOrder(const char * szInstrumentID, int volume, double price,
		cwOpenCloseMode openclosemode = cwOpenCloseMode::CloseTodayThenYd,
		cwInsertOrderType insertordertype = cwInsertOrderType::cwInsertLimitOrder);
	//��������
	bool CancelOrder(cwOrderPtr pOrder);

	//���ĺ�Լ
	void	   SubScribePrice(std::vector<std::string>& SubscribeInstrument);
	//ȡ�����ĺ�Լ
	void	   UnSubScribePrice(std::vector<std::string>& UnSubscribeInstrument);

	//��Լ��Ϣ�б���Ҫ��С�䶯����Լ��������Ϣ����ͨ�����map��ȡ����ԼIDΪKey
	std::map<std::string, cwInstrumentDataPtr> m_InstrumentMap;
	//��ȡ��Լ��С�䶯�������ȡʧ�ܷ���-1
	double    GetTickSize(const char * szInstrumentID);
	//��ȡ��Լ�����������ȡʧ�ܷ���-1
	double	  GetMultiplier(const char * szInstrumentID);
	//��ȡ��ƷID 
	char *    GetProductID(const char * szInstrumentID);
	//��ȡ����ʱ��Σ��࿪�̶�����;����̶�����
	//��������Լ��������ʱ�䣨102835->10:28:35),���׽׶Σ� ��ý���ʱ�ο��̶����룬�����̶�����
	bool	  GetTradeTimeSpace(const char * szInstrumentID, const char * updatetime,
		cwProductTradeTime::cwTradeTimeSpace& iTradeIndex, int& iOpen, int& iClose);
	
	int		  GetInstrumentCancelCount(std::string InstrumentID);
	///������ظú�������ȷ��������ĺ����ܹ������õ���
	virtual void	   SetStrategyReady();
	///ϵͳ���ýӿ���Ϣ����
	void			   SetMdSpi(cwMDAPIType apiType, void * pSpi);
	void			   SetTradeSpi(cwTradeAPIType apiType, void *pSpi);
private:
	///ϵͳ���ýӿ���Ϣ����
	friend class		cwFtdTradeSpi;
	void *				m_pTradeSpi;
	cwTradeAPIType		m_TradeApiType;

	void *				m_pMdSpi;
	cwMDAPIType			m_MdApiType;


	std::set<std::string>	m_SubscribeInstrumentSet;
	cwProductTradeTime		m_ProductTradeTime;

	cwStrategyLog			m_BasicStrategyLog;
};
