#include "../stdafx.h"
#include "../utils/utils.h"
#include "infoAnalyze.h"

/* 清空 */
void QYInfoAnalyze::clear()
{
	this->infoList.clear();
}

/**
 * 写入
 * @param	string	msg		消息串
 * @return	bool	写入结果
 */
bool QYInfoAnalyze::write(
	string msg	// 消息串
)
{
	string source = base64_decode(msg);
	if(source.length() < 4) return false;
	UnPack u(source);
	size_t count = u.GetInt();
	if(count < 0) return false;
	this->infoList.resize(count);
	BYTES tmp;
	UnPack u2;
	for(size_t i = 0; i < count; i++) {
		tmp = u.GetToken();
		if(tmp.size() < 4) {
			this->infoList.clear();
			return false;
		}
		u2.SetData(tmp);
		this->infoList[i].key = u2.GetLenStr();
		this->infoList[i].value = u2.GetLenStr();
	}
	return true;
}

/**
 * 添加单个
 * @param	string	key
 * @param	string	value
 */
void QYInfoAnalyze::addSingle(
	string key, 
	string value
)
{
	for(size_t i = 0; i < this->infoList.size(); ++i) {
		if(this->infoList[i].key == key) {
			this->infoList[i].value = value;
			return;
		}
	}
	info tmp;
	tmp.key = key;
	tmp.value = value;
	this->infoList.push_back(tmp);
}

/**
 * 读取
 * @param	string	key
 * @return	string	value
 */
string QYInfoAnalyze::read(
	string key
)
{
	for(size_t i = 0; i < this->infoList.size(); ++i) {
		if(this->infoList[i].key == key) {
			return this->infoList[i].value;
		}
	}
	return "";
}

/**
 * 输出
 * @return	string	信息内容
 */
string QYInfoAnalyze::print()
{
	Pack p, p2;
	p.SetInt(this->infoList.size());
	for(size_t i = 0; i < this->infoList.size(); ++i) {
		p2.SetLenStr(this->infoList[i].key);
		p2.SetLenStr(this->infoList[i].value);
		p.SetToken(p2.GetAll());
		p2.Empty();
	}
	BYTES Contents = p.GetAll();
	BYTE * bin = new BYTE[Contents.size()];
	for(size_t i = 0; i < Contents.size(); i++)
		bin[i] = Contents[i];
	string str = base64_encode(bin, Contents.size());
	delete[] bin;
	return str;
}

/**
 * 删除单个
 * @param	string	key
 * @return	bool	删除结果
 */
bool QYInfoAnalyze::delSingle(
	string key
)
{
	for(size_t i = 0; i < this->infoList.size(); ++i) {
		if(this->infoList[i].key == key) {
			this->infoList.erase(this->infoList.cbegin() + i, this->infoList.cbegin() + i);
			return true;
		}
	}
	return false;
}