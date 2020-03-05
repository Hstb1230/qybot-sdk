// 此文件定义API入口
// 请勿随意改动
// 应在QY类中引用
#pragma once
#pragma comment(lib, "dll")

#ifndef QYAPI
#define QYAPI(RETURN_TYPE) extern "C" __declspec(dllimport) RETURN_TYPE __stdcall
#endif


/**
 * 添加日志
 * @param	INT32	 authCode	应用标识
 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
 * @param	INT32	 level		日志等级，请用 LOG_ 开头的对应常量
 * @param	CSTRING	 event		事件名称
 * @param	CSTRING	 contents	事件内容
 * @return	INT32	 unknown	固定返回0
 */
QYAPI(INT) QY_addLog(INT32 authCode, INT64 robotID, INT32 level, CSTRING event, CSTRING contents);

/*
 * 取框架名
 * @param	INT32	 authCode	应用标识
 * @return	CSTRING	 frameName	框架名
 */
QYAPI(CSTRING) QY_getFrameName(INT32 authCode);

/*
 * 置应用自停用
 * @param	INT32	authCode	应用标识
 * @param	INT64	waitTime	等待时间，单位：毫秒
 * @return	INT32	unknown
 */
QYAPI(INT32) QY_setAppSelfDiscontinue(INT32 authCode, INT64 waitTime);

/*
 * 置应用自卸载
 * @param	INT32	authCode	应用标识
 * @param	INT64	waitTime	等待时间，单位：毫秒
 * @return	INT32	unknown
 */
QYAPI(INT32) QY_setAppSelfUninstall(INT32 authCode, INT64 waitTime);

/*
 * 取应用目录
 * @param	INT32	 authCode		应用标识
 * @return	CSTRING	 appDirectory	插件目录
 */
QYAPI(CSTRING) QY_getAppDirectory(INT32 authCode);

/*
 * 取登录QQ列表
 * @param	INT32	 authCode		应用标识
 * @return	CSTRING	 strLoginQQList	登录QQ列表数据，需要解码
 */
QYAPI(CSTRING) QY_getLoginQQList(INT32 authCode);

/*
 * 取框架账号状态
 * @param	INT32	authCode	应用标识
 * @param	INT64	robotID		要查询的账号
 * @return	INT32	账号状态
 */
QYAPI(INT32) QY_getFrameAccountState(INT32 authCode, INT64 robotID);

/*
 * 取登录昵称
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		涉及的机器人QQ
 * @return	CSTRING	 loginNick		昵称
 */
QYAPI(CSTRING) QY_getLoginNick(INT32 authCode, INT64 robotID);

/*
 * 取cookies
 * 此接口需要严格授权
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		涉及的机器人QQ
 * @return	CSTRING	 cookies		cookies
 */
QYAPI(CSTRING) QY_getCookies(INT32 authCode, INT64 robotID);

/*
 * 取csrfToken
 * 此接口需要严格授权
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		涉及的机器人QQ
 * @return	INT32	 csrfToken		csrfToken
 */
QYAPI(INT32) QY_getCsrfToken(INT32 authCode, INT64 robotID);

/*
 * 根据域名取cookie
 * 此接口需要严格授权
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		涉及的机器人QQ
 * @param	CSTRING	 domain			要获取的域名，http://qun.qq.com 或 http://qun.qzone.qq.com 
 * @return	CSTRING	 cookie			登录指定域名在跳转成功后的cookies
 */
QYAPI(CSTRING) QY_getDomainCookie(INT32 authCode, INT64 robotID, CSTRING domain);

/*
 * 取群列表
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		要查询的机器人QQ
 * @return	CSTRING	 strGroupList	群列表数据，需要解码
 */
QYAPI(CSTRING) QY_getGroupList(INT32 authCode, INT64 robotID);

/*
 * 取群信息/资料
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		机器人QQ
 * @param	INT64	 dwGroup		要查询的群号
 * @return	CSTRING	 strGroupInfo	群资料数据，需要解码
 */
QYAPI(CSTRING) QY_getGroupInfo(INT32 authCode, INT64 robotID, INT64 dwGroup);

/*
 * 取群管理组列表
 * 包括群主
 * @param	INT32	 authCode				应用标识
 * @param	INT64	 robotID				机器人QQ
 * @param	INT64	 dwGroup				要查询的群号
 * @return	CSTRING	 strGroupAdminList		群管理组列表数据，需要解码
 */
QYAPI(CSTRING) QY_getGroupAdminList(INT32 authCode, INT64 robotID, INT64 dwGroup);

/*
 * 取群成员列表
 * @param	INT32	 authCode				应用标识
 * @param	INT64	 robotID				机器人QQ
 * @param	INT64	 dwGroup				要查询的群号
 * @return	CSTRING	 strGroupMemberList		群成员列表数据，需要解码
 */
QYAPI(CSTRING) QY_getGroupMemberList(INT32 authCode, INT64 robotID, INT64 dwGroup);

/*
 * 取群成员名片
 * @param	INT32	 authCode				应用标识
 * @param	INT64	 robotID				机器人QQ
 * @param	INT64	 dwGroup				所在群
 * @param	INT64	 uin					要查询的QQ
 * @param	BOOLEAN  ignoreCache			不使用缓存，true/不使用缓存 false/使用缓存
 * @return	CSTRING	 strGroupMemberCard		该群成员名片
 */
QYAPI(CSTRING) QY_getGroupMemberCard(INT32 authCode, INT64 robotID, INT64 dwGroup, INT64 uin, BOOLEAN ignoreCache);

/*
 * 取QQ信息/资料
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			机器人QQ
 * @param	INT64	 uin				要查询的QQ
 * @return	CSTRING	 strSummaryInfo		QQ信息数据，需要解码
 */
QYAPI(CSTRING) QY_getSummaryInfo(INT32 authCode, INT64 robotID, INT64 uin);

/*
 * 取好友列表
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			要查询的机器人QQ
 * @return	CSTRING	 strFriendList		好友列表数据，需要解码
 */
QYAPI(CSTRING) QY_getFriendList(INT32 authCode, INT64 robotID);

/*
 * 取讨论组列表
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			要查询的机器人QQ
 * @return	CSTRING	 strDiscussList		讨论组列表数据，需要解码
 */
QYAPI(CSTRING) QY_getDiscussList(INT32 authCode, INT64 robotID);

/*
 * 发送名片点赞
 * @param	INT32	 authCode	应用标识
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 uin		目标QQ
 * @return	INT32	 unknown	(推测)状态码
 */
QYAPI(INT32) QY_sendLikeFavorite(INT32 authCode, INT64 robotID, INT64 uin);

/*
 * 发送好友消息
 * @param	INT32	 authCode	应用标识
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 uin		目标QQ
 * @param	CSTRING	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
QYAPI(INT32) QY_sendFriendMsg(INT32 authCode, INT64 robotID, INT64 uin, CSTRING msg);

/*
 * 发送群消息
 * @param	INT32	 authCode	应用标识
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 dwGroup	目标群
 * @param	CSTRING	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
QYAPI(INT32) QY_sendGroupMsg(INT32 authCode, INT64 robotID, INT64 dwGroup, CSTRING msg);

/*
 * 发送群临时消息
 * @param	INT32	 authCode	应用标识
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 dwGroup	所在群
 * @param	INT64	 uin		目标QQ
 * @param	CSTRING	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
QYAPI(INT32) QY_sendGroupTmpMsg(INT32 authCode, INT64 robotID, INT64 dwGroup, INT64 uin, CSTRING msg);

/*
 * 发送讨论组消息
 * @param	INT32		authCode	应用标识
 * @param	INT64		robotID		使用的机器人QQ
 * @param	INT64		dwDiscuss	目标讨论组
 * @param	CSTRING		msg			消息内容
 * @return	INT32		unknown		(推测)状态码
 */
QYAPI(INT32) QY_sendDiscussMsg(INT32 authCode, INT64 robotID, INT64 dwDiscuss, CSTRING msg);

/*
 * 发送讨论组临时消息
 * @param	INT32	 authCode	应用标识
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 dwDiscuss	所在讨论组
 * @param	INT64	 uin		目标QQ
 * @param	CSTRING	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
QYAPI(INT32) QY_sendDiscussTmpMsg(INT32 authCode, INT64 robotID, INT64 dwDiscuss, INT64 uin, CSTRING msg);

/*
 * 发送离线文件
 * @param	INT32		authCode		应用标识
 * @param	INT64		robotID			使用的机器人QQ
 * @param	INT64		dwUin			目标对象，群号 / 讨论组ID / 好友QQ
 * @param	INT64		dwToUin			QQ号，发送临时消息时使用
 * @param	INT32		dwMsgType		消息类型，83/讨论组消息 141/临时消息 166/好友消息
 * @param	INT32		dwSubMsgType	临时消息类型，0/群临时 1/讨论组临时
 * @param	CSTRING		strLocalPath	文件路径
 * @return	INT32		unknown			(推测)状态码
 */
QYAPI(INT32) QY_sendOfflineFile(INT32 authCode, INT64 robotID, INT64 dwUin, INT64 dwToUin, INT32 dwMsgType, INT32 dwSubMsgType, CSTRING strLocalPath);

/*
 * 置消息撤回
 * 部分情况需要管理员权限
 * @param	INT32	 authCode	应用标识
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	CSTRING	 msgInfo	消息数据，为聊天事件的参数
 * @return	INT32	 unknown	(推测)状态码
 */
QYAPI(INT32) QY_setMessageSvcMsgWithDraw(INT32 authCode, INT64 robotID, CSTRING msgInfo);

/*
 * 删除好友
 * @param	INT32	 authCode	应用标识
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 QQUin		目标QQ
 * @return	INT32	 unknown	(推测)状态码
 */
QYAPI(INT32) QY_setDelFriend(INT32 authCode, INT64 robotID, INT64 uin);

/*
 * 置群文件上传
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	INT64	 dwGroup			目标群
 * @param	CSTRING	 strParentFolder	群文件夹路径，如 「/」为根目录
 * @param	CSTRING	 strLocalPath		本地文件路径
 * @return	INT32	 unknown			(推测)状态码
 */
QYAPI(INT32) QY_setGroupFileUpload(INT32 authCode, INT64 robotID, INT64 dwGroup, CSTRING strParentFolder, CSTRING strLocalPath);

/*
 * 置群文件删除
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	INT64	 dwGroup			目标群
 * @param	INT64	 fileBusID			文件总线ID
 * @param	CSTRING	 strParentFolder	父文件夹ID 目标 群文件夹路径，如 「/」为根目录
 * @param	CSTRING	 fileID				文件ID
 * @return	INT32	 unknown			(推测)状态码
 */
QYAPI(INT32) QY_setDelGroupFile(INT32 authCode, INT64 robotID, INT64 dwGroup, INT64 fileBusID, CSTRING strParentFolder, CSTRING fileID);


/*
 * 置群员移除
 * 需要管理员权限
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	INT64	 dwGroup			所在群
 * @param	INT64	 uin				目标QQ
 * @param	INT32	 ignoreAddRequest	不再接收此人加群申请，请慎用
 * @return	INT32	 unknown			(推测)状态码
 */
QYAPI(INT32) QY_setGroupMembersKick(INT32 authCode, INT64 robotID, INT64 dwGroup, INT64 uin, INT32 ignoreAddRequest);

/*
 * 置全群禁言
 * 需要管理员权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	INT32	 newStatus		开关
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setGroupWholeBanSpeak(INT32 authCode, INT64 robotID, INT64 dwGroup, INT32 newStatus);

/*
 * 置群员禁言
 * 需要管理员权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT64	 uin			目标QQ
 * @param	INT64	 timeStamp		禁言时间，单位为秒。如果要解禁，这里填写0
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setGroupMembersBanSpeak(INT32 authCode, INT64 robotID, INT64 dwGroup, INT64 uin, INT64 timeStamp);

/*
 * 置群匿名成员禁言
 * 禁言后无法解除
 * 需要管理员权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT32	 anonHead		匿名用户的头像标识
 * @param	CSTRING	 anonToken		匿名用户Token
 * @param	CSTRING	 anonCard		匿名用户名片
 * @param	INT64	 timeStamp		禁言时间，单位为秒
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setGroupAnonymousBanSpeak(INT32 authCode, INT64 robotID, INT64 dwGroup, INT32 anonHead, CSTRING token, CSTRING anonCard, INT64 timeStamp);

/*
 * 设置群匿名聊天开关
 * 需要管理员权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	INT32	 newStatus		新状态，0/禁止 1/允许
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setGroupAnonymousBan(INT32 authCode, INT64 robotID, INT64 dwGroup, INT32 newStatus);

/*
 * 置群临时会话开关
 * 需要群主权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	INT32	 newStatus		新状态，0/禁止 1/允许
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setGroupPrivateSession(INT32 authCode, INT64 robotID, INT64 dwGroup, INT32 newStatus);

/*
 * 置群成员发起多人聊天开关
 * 需要群主权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	INT32	 newStatus		新状态，0/禁止 1/允许
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setGroupManyPeopleChat(INT32 authCode, INT64 robotID, INT64 dwGroup, INT32 newStatus);

/*
 * 设置群管理员
 * 需要群主权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT64	 uin			目标QQ
 * @param	INT32	 newStatus		新状态，0/取消管理员 1/设置为管理员
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setGroupAdmini(INT32 authCode, INT64 robotID, INT64 dwGroup, INT64 uin, INT32 newStatus);

/*
 * 设置群成员名片
 * 需要管理员权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT64	 uin			目标QQ
 * @param	CSTRING	 newCard		新名片
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setModifyGroupMemberCard(INT32 authCode, INT64 robotID, INT64 dwGroup, INT64 uin, CSTRING newCard);

/*
 * 设置群成员专属头衔
 * 需要群主权限
 * 目前仅安卓QQ协议支持
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT64	 uin			目标QQ
 * @param	CSTRING	 specialTitle	头衔，如需删除，请填空文本
 * @param	INT32	 expireTime		有效期，单位为秒。如果永久有效，请填-1
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setGroupSpecialTitle(INT32 authCode, INT64 robotID, INT64 dwGroup, INT64 uin, CSTRING specialTitle, INT32 expireTime);

/*
 * 置群退出
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT32	 disband		是否解散群，1/解散 0/退出
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setExitGroupChat(INT32 authCode, INT64 robotID, INT64 dwGroup, INT32 disband);

/*
 * 置讨论组退出
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwDiscuss		目标讨论组
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setExitDiscussChat(INT32 authCode, INT64 robotID, INT64 dwDiscuss);

/*
 * 置讨论组成员移除
 * 需要创建者权限
 * @param	INT32	 authCode		应用标识
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwDiscuss		所在讨论组
 * @param	INT64	 uin			目标QQ
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setDiscussMembersKick(INT32 authCode, INT64 robotID, INT64 dwDiscuss, INT64 uin);

/*
 * 置添加群
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	INT64	 dwGroup			目标群
 * @param	CSTRING	 additionalMsg		附加信息
 * @return	INT32	 unknown			(推测)状态码
 */
QYAPI(INT32) QY_setAddGroup(INT32 authCode, INT64 robotID, INT64 dwGroup, CSTRING additionalMsg);

/*
 * 置处理群添加请求
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	CSTRING	 responseFlag		请求事件收到的「反馈标识」参数
 * @param	INT32	 requestType		请求类型，邀请/REQUEST_GROUP_INVITE 或 加群/REQUEST_GROUP_INVITE
 * @param	INT32	 resultFlag			处理结果，通过/REQUEST_ALLOW 或 拒绝/REQUEST_DENY
 * @param	CSTRING	 reason				拒绝理由，仅在 加群 且 拒绝 时可用
 * @return	INT32	 unknown			(推测)状态码
 */
QYAPI(INT32) QY_setGroupAddRequest(INT32 authCode, INT64 robotID, CSTRING responseFlag, INT32 requestType, INT32 resultFlag, CSTRING reason);

/*
 * 置处理好友添加请求
 * @param	INT32	 authCode			应用标识
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	CSTRING	 responseFlag		请求事件收到的「反馈标识」参数
 * @param	INT32	 resultFlag			处理结果，通过/REQUEST_ALLOW 或 拒绝/REQUEST_DENY
 * @param	CSTRING	 remarks			通过时为添加后的好友备注，拒绝时为拒绝理由
 * @return	INT32	 unknown			(推测)状态码
 */
QYAPI(INT32) QY_setFriendAddRequest(INT32 authCode, INT64 robotID, CSTRING responseFlag, INT32 resultFlag, CSTRING remarks);

/*
 * 置致命错误提示
 * @param	INT32	 authCode		应用标识
 * @param	CSTRING	 errorInfo		错误信息
 * @return	INT32	 unknown		(推测)状态码
 */
QYAPI(INT32) QY_setFatal(INT32 authCode, CSTRING errorInfo);

/*
 * 编码Utf8到Ansi
 * @param	INT32	 authCode		应用标识
 * @param	CSTRING	 utf8Content	需要转换的UTF-8编码文本
 * @return	CSTRING	 ansiContent	转换后的ANSI编码文本
 */
QYAPI(CSTRING) QY_setEncodeUtf8ToAnsi(INT32 authCode, CSTRING utf8Content);

/*
 * 编码Ansi到Utf8
 * @param	INT32	 authCode		应用标识
 * @param	CSTRING	 ansiContent	需要转换的ANSI编码文本
 * @return	CSTRING	 utf8Content	转换后的UTF-8编码文本
 */
QYAPI(CSTRING) QY_setEncodeAnsiToUtf8(INT32 authCode, CSTRING ansiContent);

#undef QYAPI
