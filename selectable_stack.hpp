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

		/**
		 * 最優先を定義する関数
		 * @note	第一引数を優先すべき時は @a true を、そうでないときは @a false を返す。
		 * @note	優先度が同等の場合は @a false を返すこと。
		 */
		bool (* select_)(const TYPE&, const TYPE&);

	public:

		/**
		 * コンストラクタ
		 * @param[in]	select	最優先を定義する関数 (see @a select_ )
		 */
		SelectableStack(bool (* select)(const TYPE&, const TYPE&))
			: select_(select)
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
				return data_.empty();
			}

		/**
		 * スタックの要素数を取得
		 * @return	スタックの要素数
		 * @note	最悪計算量はO(1)。
		 */
		size_t
		size() const
			{
				return data_.size();
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
				assert(!data_.empty());
				assert(!index_.empty());

				if (!prior) return data_.back();

				size_t i = index_.back();
				return data_[i];
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

				if (index_.empty()) {
					index_.push_back(0);
				}
				else {
					size_t i = index_.back();
					if (select_(data, data_[i])) {
						i = data_.size();
						index_.push_back(i);
					}
				}

				data_.push_back(data);
			}

		/**
		 * スタックから要素を削除
		 * @note	事前にスタックが空でないことを確認しておくこと。
		 * @note	最悪計算量はO(1)。
		 */
		void
		pop()
			{
				assert(!data_.empty());
				assert(!index_.empty());

				data_.pop_back();
				if (data_.size() <= index_.back()) index_.pop_back();
			}
	};
};

#endif	// __SELECTABLE_STACK_HPP__
