#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
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

	SECTION("Invalid protocol")
	{
		std::string url("https:/www.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);

		std::string url1("htt://www.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url1), CUrlParsingError);

		std::string url2("httpwww.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url2), CUrlParsingError);

		std::string url3("test://www.youtube.com/");
		CHECK_THROWS_AS(CHttpUrl(url3), CUrlParsingError);
	}

	SECTION("Invalid domain")
	{
		std::string url = "https://www.googl^e.com/doc";
		CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);

		std::string url1 = "https://www google.com/doc";
		CHECK_THROWS_AS(CHttpUrl(url1), CUrlParsingError);

		std::string url2 = "https://www,google.com/doc";
		CHECK_THROWS_AS(CHttpUrl(url2), CUrlParsingError);

		std::string url3 = "http:///docs/document1.html";
		CHECK_THROWS_AS(CHttpUrl(url3), CUrlParsingError);
	}

	SECTION("Min and max port")
	{
		CHttpUrl url("https://www.hello.com:1/dsad");
		CHECK(url.GetPort() == MIN_PORT);
		CHttpUrl url1("https://www.hello.com:49151/dasda");
		CHECK(url1.GetPort() == MAX_PORT);
	}

	SECTION("Invalid port")
	{
		std::string url = "https://www.google.com:-1/doc";
		CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);

		std::string url1 = "https://www.google.com:dsa/doc";
		CHECK_THROWS_AS(CHttpUrl(url1), std::invalid_argument);

		std::string url2 = "https://www.google.com:49152/doc";
		CHECK_THROWS_AS(CHttpUrl(url2), CUrlParsingError);
	}

	SECTION("Invalid document")
	{
		std::string url = "https://drive.google.com////";
		CHECK_THROWS_AS(CHttpUrl(url), CUrlParsingError);

		std::string url1 = "https://drive.google.com/ument1.html?page=3450&lang=//////en#zero";
		CHECK_THROWS_AS(CHttpUrl(url1), CUrlParsingError);

		std::string url2 = "https://drive.google.com/ument1.html?page=3450&lang=)en#zero";
		CHECK_THROWS_AS(CHttpUrl(url2), CUrlParsingError);

		std::string url3 = "https://drive.google.com/ument1.html?page=3450&lang=**en#zero";
		CHECK_THROWS_AS(CHttpUrl(url3), CUrlParsingError);

		std::string url4 = "https://drive.google.com/";
		CHECK_THROWS_AS(CHttpUrl(url4), CUrlParsingError);

		std::string url5 = "https://drive.google.com";
		CHECK_THROWS_AS(CHttpUrl(url5), CUrlParsingError);
	}
}
