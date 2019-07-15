//////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************
//---
//---	author: Wu Chang Sheng
//---
//---	CreateTime:	2018/12/12
//---
//---	VerifyTime:	2018/12/12
//---
//*******************************************************************************
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include <map>

#include "cwTradeCommonDefine.h"

class cwBasicSimulator
{
public:
	cwBasicSimulator();
	~cwBasicSimulator();

	virtual void InitialStrategy(const char * pConfigFilePath);
	std::string			m_strConfigFileFullPath;


	virtual int ReqUserMdLogin() { return 0; }
	virtual int ReqQryInstrument() { return 0; }

	virtual int ReqOrderInsert(cwOrderPtr pOrder) { return 0; }
	virtual int CancelOrder(cwOrderPtr pOrder) { return 0; }

	/// MD
	//���ĺ�Լ
	void		SubScribePrice(std::vector<std::string>& SubscribeInstrument);
	//ȡ�����ĺ�Լ
	void		UnSubScribePrice(std::vector<std::string>& UnSubscribeInstrument);

	bool		GetIsSubscribedInstrument(char * Ins);
	///Trade

	///ϵͳ���ýӿ���Ϣ����
	void			   SetMdSpi(void * pSpi);
	void			   SetTradeSpi(void *pSpi);

protected:
	void *		m_pMdSpi;
	void *		m_pTradeSpi;

	std::map<std::string, bool>	m_SubscribeInstrumentMap;
};

