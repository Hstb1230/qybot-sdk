#pragma once
#include "logInfo.h"

class QYLOG
{	
	private:
		/* 日志常量 */
		//	调试			暗淡的灰色(DimGray)		6908265   #696969	RGB(105,105,105)
		static const auto LOG_DEBUG		=	0;
		//	信息			纯黑(Black)				0         #000000	RGB(0,0,0)
		static const auto LOG_INFO		=	10;
		//	警告			深橙色(DarkOrange)		36095     #FF8C00	RGB(255,140,0)
		static const auto LOG_WARNING	=	20;
		//	错误			深粉色(DeepPink)			9639167   #FF1493	RGB(255,20,147)
		static const auto LOG_ERROR		=	30;
		//	致命错误		纯红(Red)				255       #FF0000	RGB(255,0,0)
		static const auto LOG_FATAL		=	40;

		/** 
		 * 添加日志
		 * 不建议直接使用本方法
		 * @param	INT32				level		日志等级，请用 LOG_ 开头的对应常量
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 addLog(INT32 level, INT64 robotID, nstring eventName, nstring contents);

	public:
		/**
		 * 添加调试日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Debug(INT64 robotID, nstring eventName, nstring contents);


		/**
		 * 添加信息日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Info(INT64 robotID, nstring eventName, nstring contents);


		friend class QYLOG_INFO;
		typedef QYLOG_INFO Infos; // 信息类日志子类


		/**
		 * 添加警告日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Warning(INT64 robotID, nstring eventName, nstring contents);


		/**
		 * 添加错误日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Error(INT64 robotID, nstring eventName, nstring contents);


		/**
		 * 添加致命错误日志
		 * @param	INT64				robotID		机器人QQ，用于区分多号登录
		 * @param	string | wstring	eventName	事件名称
		 * @param	string | wstring	contents	事件内容
		 * @return	INT32				unknown		固定返回0
		 */
		static INT32 Fatal(INT64 robotID, nstring eventName, nstring contents);


};
