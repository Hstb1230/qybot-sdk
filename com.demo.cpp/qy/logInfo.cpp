#include "../stdafx.h"
#include "logInfo.h"

/**
 * 添加成功信息日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG_INFO::Success(
    INT64       robotID,	//机器人QQ，用于区分多号登录
    nstring     eventName,	//事件名称
    nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_INFO_SUCCESS, robotID, eventName, contents);
}

/**
 * 添加失败信息日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG_INFO::Fail(
    INT64       robotID,	//机器人QQ，用于区分多号登录
    nstring     eventName,	//事件名称
    nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_INFO_FAIL, robotID, eventName, contents);
}

/**
 * 添加接收信息日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG_INFO::Receive(
    INT64       robotID,	//机器人QQ，用于区分多号登录
    nstring     eventName,	//事件名称
    nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_INFO_RECEIVE, robotID, eventName, contents);
}

/**
 * 添加发送信息日志
 * @param	INT64				robotID		机器人QQ，用于区分多号登录
 * @param	string | wstring	eventName	事件名称
 * @param	string | wstring	contents	事件内容
 * @return	INT32				unknown		固定返回0
 */
INT32 QYLOG_INFO::Send(
    INT64       robotID,	//机器人QQ，用于区分多号登录
    nstring     eventName,	//事件名称
    nstring     contents	//事件内容
)
{
	return QYLOG::addLog(LOG_INFO_SEND, robotID, eventName, contents);
}
