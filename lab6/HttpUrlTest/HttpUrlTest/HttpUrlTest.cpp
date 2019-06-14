#define CATCH_CONFIG_MAIN
#include "lab6/HttpUrl/CHttpUrl.h"
#include "lab6/HttpUrl/CUrlParsingError.h"
#include "lab6/HttpUrl/Const.h"
#include <catch2/catch.hpp>

TEST_CASE("tests")
{
	SECTION("Check standard constructor")
	{
		CHttpUrl url("https://www.twitch.tv/alohadancetv");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetDomain() == "www.twitch.tv");
		CHECK(url.GetPort() == STANDARD_PORT_FOR_HTTPS);
		CHECK(url.GetDocument() == "alohadancetv");
		CHECK(url.GetURL() == "https://www.twitch.tv/alohadancetv");

		CHttpUrl url1("http://www.youtube.com:3141/feed/trending");
		CHECK(url1.GetProtocol() == Protocol::HTTP);
		CHECK(url1.GetDomain() == "www.youtube.com");
		CHECK(url1.GetPort() == 3141);
		CHECK(url1.GetDocument() == "feed/trending");
		CHECK(url1.GetURL() == "http://www.youtube.com:3141/feed/trending");

		CHttpUrl url2("www.youtube.com:3141/feed/trending");
		CHECK(url2.GetProtocol() == Protocol::HTTPS);
		CHECK(url2.GetDomain() == "www.youtube.com");
		CHECK(url2.GetPort() == 3141);
		CHECK(url2.GetDocument() == "feed/trending");
		CHECK(url2.GetURL() == "https://www.youtube.com:3141/feed/trending");

		CHttpUrl url3("https://www.twitch.tv/");
		CHECK(url3.GetProtocol() == Protocol::HTTPS);
		CHECK(url3.GetDomain() == "www.twitch.tv");
		CHECK(url3.GetPort() == STANDARD_PORT_FOR_HTTPS);
		CHECK(url3.GetDocument() == "");
		CHECK(url3.GetURL() == "https://www.twitch.tv/");

		CHttpUrl url4("https://www.twitch.tv");
		CHECK(url4.GetProtocol() == Protocol::HTTPS);
		CHECK(url4.GetDomain() == "www.twitch.tv");
		CHECK(url4.GetPort() == STANDARD_PORT_FOR_HTTPS);
		CHECK(url4.GetDocument() == "");
		CHECK(url4.GetURL() == "https://www.twitch.tv/");

		CHttpUrl url5("www.twitch.tv");
		CHECK(url5.GetProtocol() == Protocol::HTTPS);
		CHECK(url5.GetDomain() == "www.twitch.tv");
		CHECK(url5.GetPort() == STANDARD_PORT_FOR_HTTPS);
		CHECK(url5.GetDocument() == "");
		CHECK(url5.GetURL() == "https://www.twitch.tv/");
	}

	SECTION("Check constructor with port")
	{
		std::string domain = "www.youtube.com";
		std::string document = "watch?v=7VAUMP7s-p0";
		Protocol protocol = Protocol::HTTPS;
		int port = 443;
		CHttpUrl url(domain, document, protocol, port);

		CHECK(url.GetProtocol() == protocol);
		CHECK(url.GetDomain() == domain);
		CHECK(url.GetPort() == port);
		CHECK(url.GetDocument() == document);
		CHECK(url.GetURL() == "https://www.youtube.com/watch?v=7VAUMP7s-p0");
	}

	SECTION("Check constructor without port")
	{
		std::string domain = "www.youtube.com";
		std::string document = "watch?v=7VAUMP7s-p0";
		Protocol protocol = Protocol::HTTPS;
		CHttpUrl url(domain, document, protocol);

		CHECK(url.GetProtocol() == protocol);
		CHECK(url.GetDomain() == domain);
		CHECK(url.GetPort() == STANDARD_PORT_FOR_HTTPS);
		CHECK(url.GetDocument() == document);
		CHECK(url.GetURL() == "https://www.youtube.com/watch?v=7VAUMP7s-p0");
	}

	SECTION("Testing protocol")
	{
		std::string url("https:/www.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);

		std::string url1("htt://www.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url1), CUrlParsingError);

		std::string url2("httpwww.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url2), CUrlParsingError);

		std::string url3("test://www.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url3), CUrlParsingError);

		std::string url4("http::/www.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url4), CUrlParsingError);

		CHttpUrl url5("HTTPS://www.youtube.com/");
		CHECK(url5.GetProtocolString() == CONST_HTTPS);

		CHttpUrl url6("HTTP://www.youtube.com/");
		CHECK(url6.GetProtocolString() == CONST_HTTP);

		CHttpUrl url7("HtTpS://www.youtube.com/");
		CHECK(url7.GetProtocolString() == CONST_HTTPS);

		CHttpUrl url8("HttP://www.youtube.com/");
		CHECK(url8.GetProtocolString() == CONST_HTTP);

		CHttpUrl url9("www.youtube.com");
		CHECK(url9.GetProtocolString() == CONST_HTTPS);
	}

	SECTION("Testing domain")
	{
		std::string url = "https://www.googl^e.com/doc";
		CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);

		std::string url1 = "https://www google.com/doc";
		CHECK_THROWS_AS(CHttpUrl(url1), CUrlParsingError);

		std::string url2 = "https://www,google.com/doc";
		CHECK_THROWS_AS(CHttpUrl(url2), CUrlParsingError);

		std::string url3 = "http:///docs/document1.html";
		CHECK_THROWS_AS(CHttpUrl(url3), CUrlParsingError);

		CHttpUrl url4("www.youtube.com");
		CHECK(url4.GetDomain() == "www.youtube.com");

		std::string url5 = "http://";
		CHECK_THROWS_AS(CHttpUrl(url5), CUrlParsingError);
	}

	SECTION("Min and max port")
	{
		CHttpUrl url("https://www.hello.com:1/dsad");
		CHECK(url.GetPort() == MIN_PORT);
		CHttpUrl url1("https://www.hello.com:49151/dasda");
		CHECK(url1.GetPort() == MAX_PORT);
	}

	SECTION("Testing port")
	{
		std::string url = "https://hello.com:dsafasa/da";
		CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);

		std::string url1 = "https://hello.com:0/da";
		CHECK_THROWS_AS(CHttpUrl(url1), CUrlParsingError);

		std::string url2 = "https://hello.com:49152/da";
		CHECK_THROWS_AS(CHttpUrl(url2), CUrlParsingError);

		std::string url3 = "https://hello.com:-1/da";
		CHECK_THROWS_AS(CHttpUrl(url3), CUrlParsingError);

		std::string url4 = "hello.com:ada/da";
		CHECK_THROWS_AS(CHttpUrl(url4), CUrlParsingError);

		CHttpUrl url5("hello.com:312/da");
		CHECK(url5.GetPort() == 312);

		CHttpUrl url6("hello.com");
		CHECK(url6.GetPort() == 443);

		CHttpUrl url7("http://hello.com");
		CHECK(url7.GetPort() == 80);

		CHttpUrl url8("https://hello.com");
		CHECK(url8.GetPort() == 443);
	}

	SECTION("Testing document")
	{
		std::string url = "https://drive.google.com////";
		CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);

		std::string url1 = "https://drive.google.com/ument1.html?page=3450&lang=//////en#zero";
		CHECK_THROWS_AS(CHttpUrl(url1), CUrlParsingError);

		std::string url2 = "https://drive.google.com/ument1.html?page=3450&lang=)en#zero";
		CHECK_THROWS_AS(CHttpUrl(url2), CUrlParsingError);

		std::string url3 = "https://drive.google.com/ument1.html?page=3450&lang=**en#zero";
		CHECK_THROWS_AS(CHttpUrl(url3), CUrlParsingError);

		CHttpUrl url4("https://drive.google.com/");
		CHECK(url4.GetDocument() == "");

		CHttpUrl url5("https://drive.google.com");
		CHECK(url5.GetDocument() == "");
	}
}
