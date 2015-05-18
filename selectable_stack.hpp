/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	selectable_stack.hpp
 * @brief	最優先値を最悪計算量Θ(1)で出力できるスタックの実装
 * @author	Yasutaka SHINDOH / 新堂 安孝
 */

#ifndef	__SELECTABLE_STACK_HPP__
#define	__SELECTABLE_STACK_HPP__	"selectable_stack.hpp"

#include <cstddef>
#include <cassert>
#include <vector>

namespace ys
{
	/**
	 * @class	最優先値を最悪計算量Θ(1)で出力できるスタック
	 * @note	テンプレートの型 @a TYPE はスタックのキーの型。
	 */
	template<typename TYPE>
	class SelectableStack
	{
	private:

		std::vector<TYPE> data_;	///< 本来のスタック
		std::vector<size_t> index_;	///< 最優先値のインデックスのスタック
		size_t length_;				///< スタックの要素数

		/**
		 * 最優先を定義する関数
		 * @note	第一引数を優先すべき時は @a true を、そうでないときは @a false を返す。
		 */
		bool (* select_)(const TYPE&, const TYPE&);

	public:

		/**
		 * コンストラクタ
		 * @param[in]	select	最優先を定義する関数 (see @a select_ )
		 */
		SelectableStack(bool (* select)(const TYPE&, const TYPE&))
			: length_(0),
			  select_(select)
			{
				;
			}

		/**
		 * デストラクタ
		 */
		virtual
		~SelectableStack()
			{
				;
			}

		/**
		 * スタックが空か確認
		 * @return	true: 空, false: 空でない
		 * @note	最悪計算量はO(1)。
		 */
		bool
		empty() const
			{
				return length_ == 0;
			}

		/**
		 * スタックの要素数を取得
		 * @return	スタックの要素数
		 * @note	最悪計算量はO(1)。
		 */
		size_t
		size() const
			{
				return length_;
			}

		/**
		 * スタックの値を取得
		 * @param[in]	prior	返却値のフラグ
		 * @return	最後にスタックに追加した値 (@a prior が @a false の時)
		 もしくは最優先値 (@a prior が @a true の時) を取得
		 * @note	事前にスタックが空でないことを確認しておくこと。
		 * @note	最悪計算量はO(1)。
		 */
		TYPE
		top(bool prior = false) const
			{
				assert(0 < length_);

				if (prior) {
					size_t i = index_.back();
					return data_[i];
				}
				else {
					return data_.back();
				}
			}

		/**
		 * スタックに要素を追加
		 * @param[in]	data	追加するデータ
		 * @note	通常の std::vector であれば、ならし解析の計算量はO(1)となる。
					最悪計算量はO(n)で、nはスタックの長さ。
		*/
		void
		push(const TYPE& data)
			{
				assert(select_);

				++length_;
				data_.push_back(data);
				if (1 < length_) {
					size_t i = index_.back();
					if (select_(data_[i], data)) {
						index_.push_back(i);
						return;
					}
				}
				index_.push_back(length_ - 1);
			}

		/**
		 * スタックから要素を削除
		 * @note	事前にスタックが空でないことを確認しておくこと。
		 * @note	最悪計算量はO(1)。
		 */
		void
		pop()
			{
				assert(0 < length_);

				--length_;
				data_.pop_back();
				index_.pop_back();
			}
	};
};

#endif	// __SELECTABLE_STACK_HPP__
