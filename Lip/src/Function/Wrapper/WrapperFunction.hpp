#pragma once
#include "Function/Function.h"
#include "Value/Value.h"

template <typename Func>
class WrapperFunction final : public Function {
public:
	WrapperFunction() = default;
	explicit WrapperFunction(Func func);

	std::unique_ptr<Function> clone() const override;

protected:
	std::unique_ptr<Value> callImpl(const std::vector<const Expression*>& args) const override;

private:
	Func func{};
};

template<typename Func>
inline WrapperFunction<Func>::WrapperFunction(Func func) 
	: func(std::move(func)) {}

template<typename Func>
inline std::unique_ptr<Function> WrapperFunction<Func>::clone() const {
	return std::make_unique<WrapperFunction>(func);
}

template<typename Func>
inline std::unique_ptr<Value> WrapperFunction<Func>::callImpl(const std::vector<const Expression*>& args) const {
	return func(args);
}