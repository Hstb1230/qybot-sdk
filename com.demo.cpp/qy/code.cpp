#include "../stdafx.h"
#include "code.h"

/**
 * 替换子文本
 * @param	string	str			需要操作的文本
 * @param	string	find		需要替换的文本
 * @param	string	replace		用来替换的文本
 * @param	size_t	count		替换次数，0/无限替换直到无法找到可替换文本
 */
void replaceStr(
	string & str,			// 需要操作的文本
	string find,			// 需要替换的文本
	string replace = "",	// 用来替换的文本
	size_t count = 0		// 替换次数
)
{
	if(find == "") return;
	size_t t = 0; // 用于统计替换次数
	size_t pos = 0;
	while(str.length() > 0) {
		pos = str.find(find, pos);
		if(pos == string::npos) break;
		str = str.replace(pos, find.length(), replace);
		pos += replace.length();
		if(count || ++t == count) break;
	}
}

/**
 * 转义
 * @param	string	text			原文本
 * @param	bool	escapeComma		转义逗号，默认不转义
 * @return	string	转义结果
 */
string QYCODE::Escape(
	string text,		// 原文本
	bool escapeComma	// 转义逗号
)
{
	string result = text;
	replaceStr(result, "&", "&amp;");
	replaceStr(result, "[", "&#91;");
	replaceStr(result, "]", "&#93;");
	if(escapeComma)
		replaceStr(result, ",", "&#44;");
	return result;
}

/**
 * 反转义
 * @param	string	text		需要反转义的文本
 * @return	string	反转义结果
 */
string QYCODE::AntiEscape(
	string text		// 需要反转义的文本
)
{
	string result = text;
	replaceStr(result, "&amp;", "&");
	replaceStr(result, "&#91;", "[");
	replaceStr(result, "&#93;", "]");
	replaceStr(result, "&#44;", ",");
	return result;
}

/**
 * 发送表情(face)
 * @param	INT32	faceID		表情ID
 * @return	string	LQ码_表情
 */
string QYCODE::Face(
	INT32 faceID	// 表情ID
)
{
	return "[LQ:face,id=" + to_string(faceID) + "]";
}

/**
 * @某人(at) - 仅支持群
 * @param	INT64	uin			需要@的对象，-1为全体成员
 * @param	bool	needSpace	At后加空格，默认为True，可使At更规范美观
 * @return	string	LQ码_AT
 */
string QYCODE::At(
	INT64 uin,		// 需要@的对象
	bool needSpace	// At后加空格
)
{
	return "[@" + (uin == -1 ? "all" : to_string(uin)) + "]" + (needSpace ? " " : "");
}

/**
 * 发送本地图片
 * @param	string	localPath	图片路径，请填写全路径。例 E:\robot\image\1.jpg
 * @return	string	LQ码_图片
 */
string QYCODE::LocalImage(
	string localPath	// 图片路径
)
{
	return "[LQ:image,path=" + QYCODE::Escape(localPath, true) + "]";
}

/**
 * 发送网络图片
 * @param	string	url		网络图片路径，请填写网络图片的网址。 例 http://dwz.cn/2ZJkzQ
 * @return	string	LQ码_图片
 */
string QYCODE::OnlineImage(
	string url	// 网络图片路径
)
{
	return "[LQ:image,urls=" + QYCODE::Escape(url, true) + "]";
}

/**
 * 发送闪照
 * @param	string	localPath	图片路径，请填写全路径。例 E:\robot\image\1.jpg
 * @return	string	LQ码_闪照
 */
string QYCODE::FlashPic(
	string localPath	// 图片路径
)
{
	return "[LQ:flashpic,path=" + QYCODE::Escape(localPath, true) + "]";
}

/**
 * 发送本地语音
 * @param	string	localPath	语音路径，请填写全路径。例 E:\robot\record\1.amr
 * @return	string	LQ码_语音
 */
string QYCODE::Record(
	string localPath	// 语音路径
)
{
	return "[LQ:record,path=" + QYCODE::Escape(localPath, true) + "]";
}