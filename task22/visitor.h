#pragma once
#include <string>
#include "model.h"
using namespace std;

struct List;
struct ListItem;
struct Paragraph;

struct Visitor
{
	virtual ~Visitor() = default;

	virtual void visit(const Paragraph& p) = 0;
	virtual void visit(const ListItem& p) = 0;
	virtual void visit(const List& p) = 0;

	virtual std::string str() const = 0;
};
