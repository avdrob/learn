#pragma once

#include <string>
#include <memory>
#include <functional>

#include "date.h"

enum class NodeType {
	Empty,
	DateComparison,
	EventComparison,
	LogicalOperation
};

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

class Node {
public:
	Node(const NodeType &type = NodeType::Empty);
	virtual bool Evaluate(const Date &date,
					const std::string &event) const = 0;
	virtual ~Node() {}

protected:
	const NodeType type_;
};

class EmptyNode : public Node {
public:
	EmptyNode();
	virtual bool Evaluate(const Date &date,
					const std::string &event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison &cmp, const Date &date);
	virtual bool Evaluate(const Date &date,
					const std::string &event) const override;

private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison &cmp, const std::string &event);
	virtual bool Evaluate(const Date &date,
					const std::string &event) const override;

private:
	const Comparison cmp_;
	const std::string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation op,
				const std::shared_ptr<Node> &left,
				const std::shared_ptr<Node> &right);
	virtual bool Evaluate(const Date &date,
					const std::string &event) const override;

private:
	LogicalOperation op_;
	std::shared_ptr<Node> left_, right_;
};
