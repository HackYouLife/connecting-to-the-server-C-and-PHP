#include <Windows.h>
#include <iostream>
#include <winhttp.h>
#include <urlmon.h>

#pragma comment( lib, "urlmon.lib")
#pragma comment( lib, "Winhttp.lib" )

class CHTTPSession
{
private:
	HINTERNET hSession,
		      hConnect, 
		      hRequest;

	LPCWSTR wcUserAgent;
	LPCWSTR wcHTTPVerb;

	int iHTTPMethod;
	std::wstring wsDomain,
		         wsDocument;
	std::string  sPOSTData, 
		         sPOSTFile;

	int iSESSION_PROTOCOL, 
		iSESSION_PORT;
private:
	bool         SetHTTPSecuirty(int iProtocolID);
	bool         CreateSession();
	bool         SetServer(LPCWSTR wcServerDomain, INTERNET_PORT wdPort);
	bool         SetRequest(LPCWSTR wcData);
	bool         SendRequest(std::string sParameters);
	bool         SetResponseHandle();
	bool         HTTPPhraseData(std::string sTarget, std::string sParameters);
	void         CloseHandles();

public:
	std::wstring GetResponseHeader();
	int          GetHTTPStatusCode();
	bool         ReciveData(std::string& sData);
	bool         SetHTTPMethod(int iVERBID);

	bool         Send(LPCWSTR wcDomain, LPCWSTR wcDirectory, std::string wParameters);
	bool         Recv(int& iStatusCode, std::string& sHeader, std::string& sData);
	int          Request(int iHTTP_Method, int iHTTP_Protocol, std::string sTarget, std::string& sRecvData, std::string sParameters, int iEncyption);
	void         AddPOSTFile(std::string sData)
	{
		sPOSTFile = sData;
	}
	
	
	CHTTPSession()
	{
		wcUserAgent = L"UE CLIENT";
	}
	CHTTPSession(LPCWSTR lwcUserAgent)
	{
		wcUserAgent = lwcUserAgent;
	}
	~CHTTPSession()
	{
		CloseHandles();
	}	
};

enum CHTTP_PROTOCOLID
{
	HTTP_CLEAR = 10,
	HTTP_SSL
};

enum CHTTP_METHODID
{
	HTTP_GET = 10,
	HTTP_POST
};