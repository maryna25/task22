#pragma once
#include "visitor.h"
#include <sstream>

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