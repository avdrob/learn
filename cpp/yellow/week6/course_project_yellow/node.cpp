#include <stdexcept>

#include "node.h"

using namespace std;

Node::Node(const NodeType &type)
	: type_(type)
{
}

EmptyNode::EmptyNode()
	: Node()
{
}

bool EmptyNode::Evaluate(const Date &date, const string &event) const
{
	return true;
}

DateComparisonNode::DateComparisonNode(const Comparison &cmp, const Date &date)
	: Node(NodeType::DateComparison), cmp_(cmp), date_(date)
{
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const
{
	switch (cmp_) {
	case Comparison::Less:
		return date < date_;
	case Comparison::LessOrEqual:
		return date <= date_;
	case Comparison::Greater:
		return date > date_;
	case Comparison::GreaterOrEqual:
		return date >= date_;
	case Comparison::Equal:
		return date == date_;
	case Comparison::NotEqual:
		return date != date_;
	}

	throw logic_error("Wrong date comparison op in node");
}

EventComparisonNode::EventComparisonNode(const Comparison &cmp,
						const string &event)
	: Node(NodeType::EventComparison), cmp_(cmp), event_(event)
{
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const
{
	switch (cmp_) {
	case Comparison::Less:
		return event < event_;
	case Comparison::LessOrEqual:
		return event <= event_;
	case Comparison::Greater:
		return event > event_;
	case Comparison::GreaterOrEqual:
		return event >= event_;
	case Comparison::Equal:
		return event == event_;
	case Comparison::NotEqual:
		return event != event_;
	}

	throw logic_error("Wrong event comparison op in node");
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation op,
					const shared_ptr<Node> &left,
					const shared_ptr<Node> &right)
	: Node(NodeType::LogicalOperation), op_(op), left_(left), right_(right)
{
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const
{
	switch (op_) {
	case LogicalOperation::Or:
		return left_->Evaluate(date, event) ||
			right_->Evaluate(date, event);
	case LogicalOperation::And:
		return left_->Evaluate(date, event) &&
			right_->Evaluate(date, event);
	}

	throw logic_error("Wrong logical op in node");
}
