#pragma once

class UnPack
{
	private:
		BYTES  m_bin;
		INT32  location = 0;

	public:
		UnPack() {}
		UnPack(BYTES bin) : m_bin(bin) {}
		UnPack(string bin)
		{
			m_bin.assign(bin.begin(), bin.end());
		}
		/* 清除 */
		void Empty();
		/* 取所有数据 */
		BYTES GetAll();
		/* 取字节集 */
		BYTES GetBin(INT32);
		/* 取字节 */
		BYTE GetByte();
		/* 取整数 */
		INT32 GetInt();
		/* 取长整数 */
		INT64 GetLong();
		/* 取短整数 */
		INT16 GetShort();
		/* 取文本 */
		string GetLenStr();
		/* 取? */
		BYTES GetLenBin();
		/* 取令牌 */
		BYTES GetToken();
		/* 取长度 */
		INT32 Len();
		/* 置数据 */
		void SetData(BYTES);
};
