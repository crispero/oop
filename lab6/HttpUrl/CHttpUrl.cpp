#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include "Const.h"
#include <algorithm>
#include <clocale>
#include <exception>
#include <iostream>
#include <regex>

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::string protocol = ParseProtocol(url);
	if (!IsValidProtocol(protocol))
	{
		throw CUrlParsingError(INVALID_PROTOCOL);
	}
	m_protocol = ConvertStringToProtocol(protocol);

	std::string domain = ParseDomain(url);
	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError(INVALID_DOMAIN);
	}
	m_domain = domain;

	unsigned short port = std::stoi(ParsePort(url));
	if (!IsValidPort(port))
	{
		throw CUrlParsingError(INVALID_PORT);
	}
	m_port = port;

	std::string document = ParseDocument(url);
	if (!IsValidDocument(document))
	{
		throw CUrlParsingError(INVALID_DOCUMENT);
	}
	m_document = document;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	if (!IsValidProtocol(ConvertProtocolToString(protocol)))
	{
		throw CUrlParsingError(INVALID_PROTOCOL);
	}
	m_protocol = protocol;

	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError(INVALID_DOMAIN);
	}
	m_domain = domain;

	if (!IsValidDocument(document))
	{
		throw CUrlParsingError(INVALID_DOCUMENT);
	}
	m_document = document;

	if (m_protocol == Protocol::HTTP)
	{
		m_port = STANDARD_PORT_FOR_HTTP;
	}
	else if (m_protocol == Protocol::HTTPS)
	{
		m_port = STANDARD_PORT_FOR_HTTPS;
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	if (!IsValidProtocol(ConvertProtocolToString(protocol)))
	{
		throw CUrlParsingError(INVALID_PROTOCOL);
	}
	m_protocol = protocol;

	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError(INVALID_DOMAIN);
	}
	m_domain = domain;

	if (!IsValidDocument(document))
	{
		throw CUrlParsingError(INVALID_DOCUMENT);
	}
	m_document = document;

	if (!IsValidPort(port))
	{
		throw CUrlParsingError(INVALID_PORT);
	}
	m_port = port;
}

CHttpUrl::~CHttpUrl()
{
}

std::string CHttpUrl::GetURL() const
{
	std::string port = ":" + std::to_string(m_port);
	if ((m_port == 80 && m_protocol == Protocol::HTTP) || (m_port == 443 && m_protocol == Protocol::HTTPS))
	{
		port = "";
	}
	return ConvertProtocolToString(m_protocol) + "://"
		+ m_domain
		+ port + "/"
		+ m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ParseProtocol(std::string const& url)
{
	auto protocol = url;
	if (protocol.substr(0, 4) == CONST_HTTP)
	{
		auto protocolEnd = url.find('://');
		if (url[5] == 's' && protocolEnd == 6)
		{
			return CONST_HTTPS;
		}
		else if (protocol.substr(5, 7) == "://")
		{
			return CONST_HTTP;
		}
	}
	
	throw CUrlParsingError(INVALID_PROTOCOL);
}

bool CHttpUrl::IsValidProtocol(std::string const& protocol)
{
	if (protocol != CONST_HTTP && protocol != CONST_HTTPS)
	{
		return false;
	}
	return true;
}

std::string CHttpUrl::ParseDomain(std::string const& url)
{
	auto domain = url;
	auto domainStart = domain.find("://");
	if (domainStart == std::string::npos)
	{
		throw CUrlParsingError(INVALID_DOMAIN);
	}
	domain = domain.substr(domainStart + 3, url.length());
	auto domainEnd = domain.find(":");
	if (domainEnd == std::string::npos)
	{
		domainEnd = domain.find("/");
		if (domainEnd == std::string::npos)
		{
			domainEnd = domain.length();
		}
	}
	return domain.substr(0, domainEnd);
}

bool CHttpUrl::IsValidDomain(std::string const& domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError(EMPTY_DOMAIN);
	}

	std::regex regex(DOMAIN_REGEX);
	std::smatch match;
	if (!regex_match(domain, match, regex))
	{
		throw CUrlParsingError(INVALID_DOMAIN);
	}

	return true;
}

std::string CHttpUrl::ParsePort(std::string const& url)
{
	auto port = url;
	port = port.substr(ConvertProtocolToString(m_protocol).length() + 3 + m_domain.length(), url.length());
	auto portStart = port.find(':');
	if (portStart == std::string::npos)
	{
		return (m_protocol == Protocol::HTTP) ? std::to_string(STANDARD_PORT_FOR_HTTP) : std::to_string(STANDARD_PORT_FOR_HTTPS);
	}
	auto portEnd = port.find('/');
	if (portEnd == std::string::npos)
	{
		portEnd = port.length();
	}

	return port.substr(portStart + 1, portEnd);
}

bool CHttpUrl::IsValidPort(unsigned const port)
{
	if (port >= MIN_PORT && port <= MAX_PORT)
	{
		return true;
	}
	return false;
}

std::string CHttpUrl::ParseDocument(std::string const& url)
{
	auto document = url;
	document = document.substr(ConvertProtocolToString(m_protocol).length() + 3 + m_domain.length(), url.length());
	auto documentStart = document.find("/");
	if (documentStart == std::string::npos)
	{
		throw CUrlParsingError(INVALID_DOCUMENT);
	}
	auto documentEnd = document.length();
	if (documentEnd == std::string::npos)
	{
		throw CUrlParsingError(INVALID_DOCUMENT);
	}
	return document.substr(documentStart + 1, documentEnd);
}

bool CHttpUrl::IsValidDocument(std::string const& document)
{
	for (auto ch : document)
	{
		if (ch == '~' || ch == '\'' || ch == '"' || ch == '�'
			|| ch == ';' || ch == '^' || ch == '*' || ch == '(' || ch == ')'
			|| ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '|'
			|| ch == '<' || ch == '>')
		{
			throw CUrlParsingError(INVALID_DOCUMENT);
		}
	}
	for (int i = 0; i < document.length() - 1; i++)
	{
		if (document[i] == '/' && document[i + 1] == '/')
		{
			throw CUrlParsingError(INVALID_DOCUMENT);
		}
	}
	return true;
}

std::string CHttpUrl::ConvertProtocolToString(Protocol const& protocol) const
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return CONST_HTTP;
	case Protocol::HTTPS:
		return CONST_HTTPS;
	default:
		return "";
	}
}

Protocol CHttpUrl::ConvertStringToProtocol(std::string const& protocol) const
{
	if (protocol == CONST_HTTP)
	{
		return Protocol::HTTP;
	}
	else if (protocol == CONST_HTTPS)
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError(INVALID_PROTOCOL);
}