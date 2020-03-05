#include "../stdafx.h"
#include "dll.h"
#include "log.h"

/**
 * 添加日志
 * 不建议直接使用本方法
 * @param	INT32				level		日志等级，请用 LOG_ 开头的对应常量
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown	固定返回0
 */
INT32 QYLOG::addLog(
	INT32       level,		//日志等级，请用 LOG_ 开头的对应常量
	INT64       robotID,	//机器人QQ，用于区分多号登录
	nstring     eventName,	//事件名称
	nstring     contents	//事件内容
)
{
 //   string cEventName(eventName), cContents(contents);
    //return QY_addLog(QY::getAuthCode(), robotID, level, cEventName.c_str(), cContents.c_str());
    return QY_addLog(QY::getAuthCode(), robotID, level, eventName, contents);
}

/**
 * 添加调试日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG::Debug(
    INT64      robotID,	//机器人QQ，用于区分多号登录
    nstring     eventName,	//事件名称
    nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_DEBUG, robotID, eventName, contents);
}

/**
 * 添加信息日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG::Info(
    INT64       robotID,	//机器人QQ，用于区分多号登录
    nstring     eventName,	//事件名称
    nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_INFO, robotID, eventName, contents);
}

/**
 * 添加警告日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG::Warning(
    INT64       robotID,	//机器人QQ，用于区分多号登录
    nstring     eventName,	//事件名称
    nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_WARNING, robotID, eventName, contents);
}

/**
 * 添加错误日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG::Error(
    INT64       robotID,	//机器人QQ，用于区分多号登录
    nstring     eventName,	//事件名称
    nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_ERROR, robotID, eventName, contents);
}

/**
 * 添加致命错误日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG::Fatal(
	INT64       robotID,	//机器人QQ，用于区分多号登录
	nstring     eventName,	//事件名称
	nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_FATAL, robotID, eventName, contents);
}
