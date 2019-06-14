#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include "Const.h"
#include <algorithm>
#include <cctype>
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

	try
	{
		unsigned short port = std::stoi(ParsePort(url));
		if (!IsValidPort(port))
		{
			throw CUrlParsingError(INVALID_PORT);
		}
		m_port = port;
	}
	catch (...)
	{
		throw CUrlParsingError(INVALID_PORT);
	}

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

std::string CHttpUrl::GetProtocolString() const
{
	switch (m_protocol)
	{
	case HTTP:
		return CONST_HTTP;
	case HTTPS:
		return CONST_HTTPS;
	default:
		throw CUrlParsingError(INVALID_DOMAIN);
	}
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
	protocol = protocol.substr(0, 5);
	std::transform(protocol.begin(), protocol.end(), protocol.begin(), tolower);
	auto protocolEnd = url.find("://");

	if (protocolEnd == std::string::npos)
	{
		if (protocol.substr(0, 4) == CONST_HTTP || protocol.substr(0, 5) == CONST_HTTPS)
		{
			throw CUrlParsingError(INVALID_PROTOCOL);
		}
		else
		{
			return CONST_HTTPS;
		}
	}
	else if (protocol.substr(0, 4) == CONST_HTTP)
	{
		if (protocolEnd == 4)
		{
			return CONST_HTTP;
		}
		else if (protocol[4] == 's')
		{
			if (protocolEnd == 5)
			{
				return CONST_HTTPS;
			}
			else
			{
				throw CUrlParsingError(INVALID_PROTOCOL);
			}
		}
		else
		{
			throw CUrlParsingError(INVALID_PROTOCOL);
		}
	}
	else
	{
		throw CUrlParsingError(INVALID_PROTOCOL);
	}
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
		domain = domain.substr(0, url.length());
	}
	else
	{
		domain = domain.substr(domainStart + 3, url.length());
	}
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
	auto domainStart = port.find("://");
	if (domainStart == std::string::npos)
	{
		port = port.substr(m_domain.length(), url.length());
	}
	else
	{
		port = port.substr(ConvertProtocolToString(m_protocol).length() + 3 + m_domain.length(), url.length());
	}
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
	auto domainStart = document.find("://");
	if (domainStart == std::string::npos)
	{
		document = document.substr(m_domain.length(), url.length());
	}
	else
	{
		document = document.substr(ConvertProtocolToString(m_protocol).length() + 3 + m_domain.length(), url.length());
	}

	auto documentStart = document.find("/");
	if (documentStart == std::string::npos)
	{
		return "";
	}

	return document.substr(documentStart + 1, url.length());
}

bool CHttpUrl::IsValidDocument(std::string const& document)
{
	if (document.length() == 0)
	{
		return true;
	}

	for (auto ch : document)
	{
		if (ch == '~' || ch == '\'' || ch == '"' || ch == '¹'
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