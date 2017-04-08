#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#define CATCH_CONFIG_RUNNER 
#include "catch.hpp"
#include "model.h"
#include "visitor.h"
using namespace std;

struct HTMLVisitor : Visitor
{
	void visit(const Paragraph& p) override
	{
		oss << "<p>" << p.text << "</p>" << endl;
	}
	void visit(const ListItem& p) override
	{
		oss << "<li>" << p.text << "</li>" << endl;
	}
	void visit(const List& p) override
	{
		oss << "<ul>" << endl;
		for (auto x : p)
		{
			x.accept(*this);
		}
		oss << "</ul>" << endl;
	}
	std::string str() const override
	{
		return oss.str();
	}
private:
	ostringstream oss;
};

TEST_CASE("Paragraph visitor")
{
	Paragraph p{ "Hi, I'm paragraph" };
	HTMLVisitor v;
	p.accept(v);
	REQUIRE(v.str() == "<p>Hi, I'm paragraph</p>\n");

	Paragraph p1{ "And who are you?" };
	Paragraph p2{ "Nice to meet you" };

	vector<Element*> text{ &p1, &p2 };
	for (auto x : text)
	{
		x->accept(v);
	}
	REQUIRE(v.str() == "<p>Hi, I'm paragraph</p>\n<p>And who are you?</p>\n<p>Nice to meet you</p>\n");
}

TEST_CASE("ListItem visitor")
{
	ListItem l{ "dog" };
	HTMLVisitor v;
	l.accept(v);
	REQUIRE(v.str() == "<li>dog</li>\n");

	ListItem l1{ "cat" };
	ListItem l2{ "cow" };

	vector<Element*> text{ &l1, &l2 };
	for (auto x : text)
	{
		x->accept(v);
	}
	REQUIRE(v.str() == "<li>dog</li>\n<li>cat</li>\n<li>cow</li>\n");
}

TEST_CASE("List visitor")
{
	ListItem l{ "dog" };
	ListItem l1{ "cat" };
	ListItem l2{ "cow" };

	List list{ l, l1, l2 };
	vector<Element*> text{ &list };
	HTMLVisitor v;
	for (auto x : text)
	{
		x->accept(v);
	}
	REQUIRE(v.str() == "<ul>\n<li>dog</li>\n<li>cat</li>\n<li>cow</li>\n</ul>\n");
}

TEST_CASE("all visitor")
{
	Paragraph p{ "hello" };
	ListItem item1{ "Vitalik" };
	ListItem item2{ "Galya" };
	List l{ item1, item2 };

	vector<Element*> text{ &p, &l };
	HTMLVisitor v;

	for (auto x : text)
	{
		x->accept(v);
	}

	REQUIRE(v.str() == "<p>hello</p>\n<ul>\n<li>Vitalik</li>\n<li>Galya</li>\n</ul>\n");
}

int main(int argc, char* argv[])
{
	int result = Catch::Session().run(argc, argv);
	getchar();
	return result;
}

