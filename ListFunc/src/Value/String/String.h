#include "Value/Value.h"

#include <string>

class String final : public Value {
public:
	explicit String(std::string string);

	ValueType type() const override;

	std::unique_ptr<Value> cloneValue() const override;

	std::string toString() const override;

	const std::string& getString() const;
	void setString(std::string string);

public:
	static std::unique_ptr<String> of(std::string string);

private:
	std::string string;
};