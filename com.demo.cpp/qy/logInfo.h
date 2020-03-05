#pragma once
#include "log.h"

class QYLOG_INFO
{
	private:
		/* 日志常量 */
		//	信息(成功)	深紫罗兰的蓝色(BlueViolet)	14822282  #8A2BE2  RGB(138,43,226)
		static const auto LOG_INFO_SUCCESS	=	11;
		//	信息(失败)	棕色(Brown)					2763429   #A52A2A  RGB(165,42,42)
		static const auto LOG_INFO_FAIL		=	12;
		//	信息(接收)	纯蓝(Blue)					16711680  #0000FF  RGB(0,0,255)
		static const auto LOG_INFO_RECEIVE	=	13;
		//	信息(发送)	纯绿(Green)					32768     #008000  RGB(0,128,0)
		static const auto LOG_INFO_SEND		=	14;

	public:

		/**
		 * 添加成功信息日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Success(INT64 robotID, nstring eventName, nstring contents);


		/**
		 * 添加失败信息日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Fail(INT64 robotID, nstring eventName, nstring contents);


		/**
		 * 添加接收信息日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Receive(INT64 robotID, nstring eventName, nstring contents);


		/**
		 * 添加发送信息日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Send(INT64 robotID, nstring eventName, nstring contents);
};
