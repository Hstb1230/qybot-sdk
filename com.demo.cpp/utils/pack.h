#pragma once

class Pack
{
	private:
		BYTES m_bin;

	public:
		/* 清除 */
		void Empty();
		/* 取全部数据 */
		BYTES GetAll();
		/* 取长度 */
		size_t Len();
		/* 置字节集 */
		void SetBin(BYTES);
		/* 置字节 */
		void SetByte(BYTE);
		/* 置类数据 */
		void SetData(BYTES);
		/* 置整数 */
		void SetInt(INT32);
		/* 置短整数 */
		void SetShort(INT16);
		/* 置长整数 */
		void SetLong(INT64);
		/* 置文本 */
		void SetStr(string);
		/* 置? */
		void SetLenStr(string);
		/* 置令牌 */
		void SetToken(BYTES);
};
