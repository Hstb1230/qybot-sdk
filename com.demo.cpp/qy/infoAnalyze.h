#pragma once

class QYInfoAnalyze
{
	private:
		typedef struct {
			string key;
			string value;
		} info;
		std::vector<info> infoList;
		//infoList infoList;

	public:
		QYInfoAnalyze() {}
		QYInfoAnalyze(string msg) {
			write(msg);
		}
		~QYInfoAnalyze()
		{
			this->clear();
		}

		/* 清空 */
		void clear();

		/**
		 * 写入
		 * @param	string	msg		消息串
		 * @return	bool	写入结果
		 */
		bool write(string msg);

		/**
		 * 添加单个
		 * @param	string	key
		 * @param	string	value
		 */
		void addSingle(string key, string value);

		/**
		 * 读取
		 * @param	string	key
		 * @return	string	value
		 */
		string read(string key);

		/**
		 * 输出
		 * @return	string	信息内容
		 */
		string print();

		/**
		 * 删除单个
		 * @param	string	key
		 * @return	bool	删除结果
		 */
		bool delSingle(string key);
};
