#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <algorithm>
#include <clocale>
#include <iostream>
#include <regex>

CHttpUrl::CHttpUrl(std::string const& url)
{
	auto protocol = ParseProtocol(url);
	if (IsValidProtocol(protocol))
	{
		m_protocol = ConvertStringToProtocol(protocol);
	}

	std::string domain = ParseDomain(url);
	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError("Invalid domain");
	}
	m_domain = domain;

	unsigned short port = std::stoi(ParsePort(url));
	if (!IsValidPort(port))
	{
		throw CUrlParsingError("Invalid port");
	}
	m_port = port;

	std::string document = ParseDocument(url);
	if (!IsValidDocument(document))
	{
		throw CUrlParsingError("Invalid document");
	}
	m_document = document;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError("Invalid domain");
	}
	if (!IsValidDocument(document))
	{
		throw CUrlParsingError("Invalid document");
	}
	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError("Invalid domain");
	}
	if (!IsValidDocument(document))
	{
		throw CUrlParsingError("Invalid document");
	}
	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
	if (IsValidPort(port))
	{
		m_port = port;
	}
	else
	{
		throw CUrlParsingError("Invalid port");
	}
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
	return ConvertProtocolToString() + "://"
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
	auto protocolEnd = protocol.find('://');
	if (protocolEnd == std::string::npos)
	{
		throw CUrlParsingError("Parse protocol error");
	}

	return protocol.substr(0, protocolEnd - 1);
}

bool CHttpUrl::IsValidProtocol(std::string const& protocol)
{
	if (protocol != "http" && protocol != "https")
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
		throw CUrlParsingError("Parse domain domainStart error");
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
		throw CUrlParsingError("IsValidDomain empty");
	}

	std::regex regex(R"(^([[:alnum:]-\\.]+)$)");
	std::smatch match;
	if (!regex_match(domain, match, regex))
	{
		throw CUrlParsingError("IsValidDomain error");
	}

	return true;
}

std::string CHttpUrl::ParsePort(std::string const& url)
{
	auto port = url;
	port = port.substr(ConvertProtocolToString().length() + 3 + m_domain.length(), url.length());
	auto portStart = port.find(':');
	if (portStart == std::string::npos)
	{
		throw CUrlParsingError("ParsePort portStart");
	}
	auto portEnd = port.find('/');
	if (portEnd == std::string::npos)
	{
		throw CUrlParsingError("ParsePort portEnd");
	}

	return port.substr(portStart + 1, portEnd);
}

bool CHttpUrl::IsValidPort(unsigned const port)
{
	if (port > 0 && port < 49151)
	{
		return true;
	}
	return false;
}

std::string CHttpUrl::ParseDocument(std::string const& url)
{
	auto document = url;
	document = document.substr(ConvertProtocolToString().length() + 3 + m_domain.length() + std::to_string(m_port).length() + 1, url.length());
	auto documentStart = document.find("/");
	if (documentStart == std::string::npos)
	{
		throw CUrlParsingError("ParseDocument documentStart");
	}
	auto documentEnd = document.length();
	if (documentEnd == std::string::npos)
	{
		throw CUrlParsingError("ParseDocument documentEnd");
	}
	return document.substr(documentStart + 1, documentEnd);
}

bool CHttpUrl::IsValidDocument(std::string const& document)
{
	if (document.empty())
	{
		throw CUrlParsingError("IsValidDocument empty");
	}
	for (auto ch : document)
	{
		if (ch == '~' || ch == '\'' || ch == '"' || ch == '¹'
			|| ch == ';' || ch == '^' || ch == '*' || ch == '(' || ch == ')'
			|| ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '|'
			|| ch == '<' || ch == '>')
		{
			throw CUrlParsingError("IsValidDocument error");
		}
	}
	return true;
}

std::string CHttpUrl::ConvertProtocolToString() const
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		return "";
	}
}

Protocol CHttpUrl::ConvertStringToProtocol(std::string const& protocol) const
{
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError("Invalid protocol");
}