#include "../stdafx.h"
#include "dll.h"
#include "log.h"

/**
 * 添加日志
 * 不建议直接使用本方法
 * @param	INT32	 level		日志等级，请用 LOG_ 开头的对应常量
 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
 * @param	string	 event		事件名称
 * @param	string	 contents	事件内容
 * @return	INT32	 unknown	固定返回0
 */
INT32 QYLOG::addLog(
	INT32	level,		//日志等级，请用 LOG_ 开头的对应常量
	INT64	robotID,	//机器人QQ，用于区分多号登录
	string	event,		//事件名称
	string	contents	//事件内容
)
{
	return QY_addLog(QY::getAuthCode(), robotID, level, event.c_str(), contents.c_str());
}

/**
 * 添加调试日志
 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
 * @param	string	 event		事件名称
 * @param	string	 contents	事件内容
 * @return	INT32	 unknown	固定返回0
 */
INT32 QYLOG::Debug(
	INT64	robotID,	//机器人QQ，用于区分多号登录
	string	event,		//事件名称
	string	contents	//事件内容
)
{
	return QYLOG::addLog(LOG_DEBUG, robotID, event, contents);
}


/**
 * 添加信息日志
 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
 * @param	string	 event		事件名称
 * @param	string	 contents	事件内容
 * @return	INT32	 unknown	固定返回0
 */
INT32 QYLOG::Info(
	INT64	robotID,	//机器人QQ，用于区分多号登录
	string	event,		//事件名称
	string	contents	//事件内容
)
{
	return QYLOG::addLog(LOG_INFO, robotID, event, contents);
}

/**
 * 添加警告日志
 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
 * @param	string	 event		事件名称
 * @param	string	 contents	事件内容
 * @return	INT32	 unknown	固定返回0
 */
INT32 QYLOG::Warning(
	INT64	robotID,	//机器人QQ，用于区分多号登录
	string	event,		//事件名称
	string	contents	//事件内容
)
{
	return QYLOG::addLog(LOG_WARNING, robotID, event, contents);
}

/**
 * 添加错误日志
 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
 * @param	string	 event		事件名称
 * @param	string	 contents	事件内容
 * @return	INT32	 unknown	固定返回0
 */
INT32 QYLOG::Error(
	INT64	robotID,	//机器人QQ，用于区分多号登录
	string	event,		//事件名称
	string	contents	//事件内容
)
{
	return QYLOG::addLog(LOG_ERROR, robotID, event, contents);
}

/**
 * 添加致命错误日志
 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
 * @param	string	 event		事件名称
 * @param	string	 contents	事件内容
 * @return	INT32	 unknown	固定返回0
 */
INT32 QYLOG::Fatal(
	INT64	robotID,	//机器人QQ，用于区分多号登录
	string	event,		//事件名称
	string	contents	//事件内容
)
{
	return QYLOG::addLog(LOG_FATAL, robotID, event, contents);
}