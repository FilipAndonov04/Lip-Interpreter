#pragma once
#include "Function/Function.h"
#include "Value/Value.h"

template <typename Func>
class WrapperFunction final : public Function {
public:
	explicit WrapperFunction(size_t argCount);
	WrapperFunction(size_t argCount, Func func);

	std::unique_ptr<Function> clone() const override;

protected:
	std::unique_ptr<Expression> callImpl(const std::vector<const Expression*>& args) const override;

private:
	Func func{};
};

template<typename Func>
inline WrapperFunction<Func>::WrapperFunction(size_t argCount) 
	: Function(argCount) {}

template<typename Func>
inline WrapperFunction<Func>::WrapperFunction(size_t argCount, Func func) 
	: Function(argCount), func(std::move(func)) {}

template<typename Func>
inline std::unique_ptr<Function> WrapperFunction<Func>::clone() const {
	return std::make_unique<WrapperFunction>(getArgCount(), func);
}

template<typename Func>
inline std::unique_ptr<Expression> WrapperFunction<Func>::callImpl(const std::vector<const Expression*>& args) const {
	return func(args);
}