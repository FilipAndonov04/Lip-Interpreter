#pragma once
#include "Interpreter/Environment/Environment.h"

class EnvironmentStack {
public:
	EnvironmentStack() = default;
	EnvironmentStack(const EnvironmentStack& other);
	EnvironmentStack(EnvironmentStack&& other) noexcept = default;
	EnvironmentStack& operator=(const EnvironmentStack& other);
	EnvironmentStack& operator=(EnvironmentStack&& other) noexcept = default;
	~EnvironmentStack() = default;

	const Environment& getCurrentEnvironment() const;
	Environment& getCurrentEnvironment();
	bool isEmpty() const;

	void pushEnvironment(const Environment& environment);
	void pushEnvironment(Environment&& environment);
	Environment popEnvironment();

private:
	void assertNotEmpty() const;

private:
	struct EnvironmentNode {
		Environment environment;
		std::unique_ptr<EnvironmentNode> prev;

		EnvironmentNode(const Environment& environment);
		EnvironmentNode(Environment&& environment);
	};
	std::unique_ptr<EnvironmentNode> top;
};