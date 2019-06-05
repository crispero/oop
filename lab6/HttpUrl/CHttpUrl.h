#pragma once
#include "Protocol.h"
#include <string>

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	~CHttpUrl();

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	std::string ParseDomain(std::string const& url);
	std::string ParseDocument(std::string const& url);
	std::string ParseProtocol(std::string const& url);
	std::string ParsePort(std::string const& url);

	bool IsValidDomain(std::string const& domain);
	bool IsValidDocument(std::string const& document);
	bool IsValidProtocol(std::string const& protocol);
	bool IsValidPort(unsigned const port);

	Protocol ConvertStringToProtocol(std::string const& protocol) const;
	std::string ConvertProtocolToString() const;

	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
