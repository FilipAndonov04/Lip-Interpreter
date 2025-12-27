#pragma once
#include "Function/Graph/Node/Leaf/LeafNode.h"

class ArgumentNode final : public LeafNode {
public:
	explicit ArgumentNode(size_t argId);

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const override;

	std::unique_ptr<FunctionNode> clone() const override;

	size_t getArgId() const;

public:
	static std::unique_ptr<ArgumentNode> of(size_t argId);

private:
	size_t argId;
};