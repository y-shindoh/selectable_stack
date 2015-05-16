/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	main.cpp
 * @brief	selectable_stack.hppの動作確認用コマンド
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include "selectable_stack.hpp"

bool
select(const int& left,
	   const int& right)
{
	return left <= right;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	ys::SelectableStack<int>* stack = new ys::SelectableStack<int>(select);

	stack->push(2);
	stack->push(3);
	stack->push(1);
	stack->push(5);
	stack->push(4);	// pop対象
	stack->push(0);	// pop対象
	stack->push(6);	// pop対象

	stack->pop();
	stack->pop();
	stack->pop();

	std::printf("last: %d\n", stack->top());
	std::printf("min:  %d\n", stack->top(true));
	std::printf("size: %lu\n", stack->size());

	delete stack;

	return 0;
}
