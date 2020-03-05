#pragma once
// LQ码
class QYCODE
{
	public:
		/**
		 * 转义
		 * @param	string	text			原文本
		 * @param	bool	escapeComma		转义逗号，默认不转义
		 * @return	string	转义结果
		 */
		static string Escape(string text, bool escapeComma = false);

		/**
		 * 反转义
		 * @param	string	text		需要反转义的文本
		 * @return	string	反转义结果
		 */
		static string AntiEscape(string text);

		/**
		 * 发送表情(face)
		 * @param	INT32	faceID		表情ID
		 * @return	string	LQ码_表情
		 */
		static string Face(INT32 faceID);

		/**
		 * @某人(at) - 仅支持群
		 * @param	INT64	uin			需要@的对象，-1为全体成员
		 * @param	bool	needSpace	At后加空格，默认为True，可使At更规范美观
		 * @return	string	LQ码_AT
		 */
		static string At(INT64 uin, bool needSpace = true);

		/**
		 * 发送本地图片
		 * @param	string	localPath	图片路径，请填写全路径。例 E:\robot\image\1.jpg 
		 * @return	string	LQ码_图片
		 */
		static string LocalImage(string localPath);

		/**
		 * 发送网络图片
		 * @param	string	url		网络图片路径，请填写网络图片的网址。 例 http://dwz.cn/2ZJkzQ
		 * @return	string	LQ码_图片
		 */
		static string OnlineImage(string url);

		/**
		 * 发送闪照
		 * @param	string	localPath	图片路径，请填写全路径。例 E:\robot\image\1.jpg
		 * @return	string	LQ码_闪照
		 */
		static string FlashPic(string localPath);

		/**
		 * 发送本地语音
		 * @param	string	localPath	语音路径，请填写全路径。例 E:\robot\record\1.amr
		 * @return	string	LQ码_语音
		 */
		static string Record(string localPath);

};
