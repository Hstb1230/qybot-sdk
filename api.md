# 契约机器人API文档

##### By [S·c]( https://github.com/ScSofts )

<font color="red">Warning:本文档仅供测试！本文档以C++为范例，其它语言类似</font>

## QYAPI == QY

这是核心API，包含[发送]("#send") 、 [设置]("#set") 、[获取]("get")、[转码]("#conv") 

###  发送

<a id="send"> </a>

```c++
	/**
	 * 发送名片赞
	 * @param	INT64	robotID		使用的机器人QQ
	 * @param	INT64	uin			目标对象
	 * @param	INT32	count		点赞次数，默认点赞一次
	 * @return	INT32	固定返回0
	 */
	static INT32 sendLikeFavorite(INT64 robotID, INT64 uin, INT32 count = 1);

	/*
	 * 发送好友消息
	 * @param	INT64	 robotID	使用的机器人QQ
	 * @param	INT64	 uin		目标QQ
	 * @param	string	 msg		消息内容
	 * @return	INT32	 unknown	(推测)状态码
	 */
	static INT32 sendFriendMsg(INT64 robotID, INT64 uin, string msg);

	/*
	 * 发送群消息
	 * @param	INT64	 robotID	使用的机器人QQ
	 * @param	INT64	 dwGroup	目标群
	 * @param	string	 msg		消息内容
	 * @return	INT32	 unknown	(推测)状态码
	 */
	static INT32 sendGroupMsg(INT64 robotID, INT64 dwGroup, string msg);

	/*
	 * 发送群临时消息
	 * @param	INT64	 robotID	使用的机器人QQ
	 * @param	INT64	 dwGroup	所在群
	 * @param	INT64	 uin		目标QQ
	 * @param	string	 msg		消息内容
	 * @return	INT32	 unknown	(推测)状态码
	 */
	static INT32 sendGroupTmpMsg(INT64 robotID, INT64 dwGroup, INT64 uin, string msg);

	/*
	 * 发送讨论组消息
	 * @param	INT64	 robotID	使用的机器人QQ
	 * @param	INT64	 dwDiscuss	目标讨论组
	 * @param	string	 msg		消息内容
	 * @return	INT32	 unknown	(推测)状态码
	 */
	static INT32 sendDiscussMsg(INT64 robotID, INT64 dwDiscuss, string msg);

	/*
	 * 发送讨论组临时消息
	 * @param	INT64	 robotID	使用的机器人QQ
	 * @param	INT64	 dwDiscuss	所在讨论组
	 * @param	INT64	 uin		目标QQ
	 * @param	string	 msg		消息内容
	 * @return	INT32	 unknown	(推测)状态码
	 */
	static INT32 sendDiscussTmpMsg(INT64 robotID, INT64 dwDiscuss, INT64 uin, string msg);

	/*
	 * 发送离线文件
	 * 如需上传群文件到指定目录，请使用「setGroupFileUpload」
	 * @param	INT64		robotID			使用的机器人QQ
	 * @param	INT32		dwMsgType		消息类型，1/好友 2/群 3/讨论组 4/群临时 5/讨论组临时
	 * @param	INT64		dwGroup			所在群组的 群号 / 讨论组ID
	 * @param	INT64		dwUin			QQ号，发送个人消息时使用
	 * @param	string		strLocalPath	文件路径
	 * @return	INT32		unknown			(推测)状态码
	 */
	static INT32 sendOfflineFile(INT64 robotID, INT32 dwMsgType, INT64 dwGroup, INT64 dwUin, string strLocalPath);

	/**
	 * 置消息撤回
	 * @param	INT64		robotID		使用的机器人QQ
	 * @param	string		msgInfo		消息信息
	 * @return	INT32		操作结果
	 */
	static INT32 setMessageSvcMsgWithDraw(INT64 robotID, string msgInfo);

	/*
	 * 删除好友
	 * @param	INT64	 robotID	使用的机器人QQ
	 * @param	INT64	 uin		目标QQ
	 * @return	INT32	 unknown	(推测)状态码
	 */
	static INT32 setFriendDelete(INT64 robotID, INT64 uin);

	/*
	 * 置群文件上传
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	INT64	 dwGroup			目标群
	 * @param	string	 strParentFolder	群文件夹路径，如 「/」为根目录
	 * @param	string	 strLocalPath		本地文件路径，请填完整路径，不可空
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupFileUpload(INT64 robotID, INT64 dwGroup, string strParentFolder = "/", string strLocalPath = "");

	/*
	 * 置群文件删除
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	INT64	 dwGroup			目标群
	 * @param	INT64	 fileBusID			文件总线ID
	 * @param	string	 strParentFolder	父文件夹ID 目标群文件夹路径，如 「/」为根目录
	 * @param	string	 fileID				文件ID，不可空
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupFileDelete(INT64 robotID, INT64 dwGroup, INT64 fileBusID, string strParentFolder = "/", string fileID = "");

	/*
	 * 置群员移除
	 * 需要管理员权限
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	INT64	 dwGroup			所在群
	 * @param	INT64	 uin				目标QQ
	 * @param	bool	 ignoreAddRequest	不再接收此人加群申请，无法撤销，请慎用
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupMembersKick(INT64 robotID, INT64 dwGroup, INT64 uin, bool ignoreAddRequest = false);

	/*
	 * 置全群禁言
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		目标群
	 * @param	bool	 newStatus		要设置的新状态，true/开启禁言 false/关闭禁言
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupWholeBanSpeak(INT64 robotID, INT64 dwGroup, bool newStatus);

	/*
	 * 置群员禁言
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 uin			目标QQ
	 * @param	INT64	 timeStamp		禁言时间，单位为秒，最长为1个月。如果要解禁，这里填写0
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupMemberBanSpeak(INT64 robotID, INT64 dwGroup, INT64 uin, INT64 timeStamp = 0);

	/*
	 * 置群匿名成员禁言
	 * 禁言后无法解除
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 headMark		匿名用户的头像标识
	 * @param	BYTES	 token			匿名用户Token
	 * @param	string	 card			匿名用户名片
	 * @param	INT64	 timeStamp		禁言时间，单位为秒
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupAnonymousBanSpeak(INT64 robotID, INT64 dwGroup, INT64 headMark, BYTES token, string card, INT64 timeStamp);

	/*
	 * 设置群匿名聊天开关
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		目标群
	 * @param	bool	 newStatus		要设置的新状态，true/允许、false/禁止 匿名聊天
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupAnonymousBan(INT64 robotID, INT64 dwGroup, bool newStatus);

	/*
	 * 置群临时会话开关
	 * 需要群主权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		目标群
	 * @param	bool	 newStatus		要设置的新状态，true/允许、false/禁止 通过群发起临时会话
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupPrivateSession(INT64 robotID, INT64 dwGroup, bool newStatus);

	/*
	 * 置群成员发起多人聊天开关
	 * 需要群主权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		目标群
	 * @param	bool	 newStatus		要设置的新状态，true/允许、false/禁止 通过群发起多人聊天
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupManyPeopleChat(INT64 robotID, INT64 dwGroup, bool newStatus);

	/*
	 * 设置群管理员
	 * 需要群主权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 uin			目标QQ
	 * @param	bool	 newStatus		true/设置 false/取消 管理员
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupAdmini(INT64 robotID, INT64 dwGroup, INT64 uin, bool newStatus);

	/*
	 * 设置群成员名片
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 uin			目标QQ
	 * @param	string	 newCard		新名片，如果要删除，请填空文本
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupMemberCard(INT64 robotID, INT64 dwGroup, INT64 uin, string newCard = "");

	/*
	 * 设置群成员专属头衔
	 * 需要群主权限
	 * 目前仅安卓QQ协议支持
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 uin			目标QQ
	 * @param	string	 specialTitle	头衔，如需删除，请填空文本
	 * @param	INT32	 expireTime		有效期，单位为秒。如果永久有效，请填-1
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupSpecialTitle(INT64 robotID, INT64 dwGroup, INT64 uin, string  specialTitle = "", INT32 rxpireTime = -1);

	/*
	 * 置群退出
	 * @param	INT64		robotID		使用的机器人QQ
	 * @param	INT64		dwGroup		目标群
	 * @param	newStatus	disband		是否解散群，true/解散 false/退出
	 * @return	INT32		unknown		(推测)状态码
	 */
	static INT32 setGroupExit(INT64 robotID, INT64 dwGroup, bool disband = false);

	/*
	 * 置讨论组退出
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwDiscuss		目标讨论组
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setDiscussExit(INT64 robotID, INT64 dwDiscuss);

	/*
	 * 置讨论组成员移除
	 * 需要创建者权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwDiscuss		所在讨论组
	 * @param	INT64	 uin			目标QQ
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setDiscussMembersKick(INT64 robotID, INT64 dwDiscuss, INT64 uin);

	/*
	 * 置添加群
	 * 因为各种限制，可能不成功
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	INT64	 dwGroup			目标群
	 * @param	string	 additionalMsg		附加信息
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupAdd(INT64 robotID, INT64 dwGroup, string additionalMsg);

	/*
	 * 置处理群添加请求
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	string	 responseFlag		请求事件收到的「反馈标识」参数
	 * @param	INT32	 requestType		请求类型，邀请/REQUEST_GROUP_INVITE 或 加群/REQUEST_GROUP_INVITE
	 * @param	INT32	 resultFlag			处理结果，通过/REQUEST_ALLOW 或 拒绝/REQUEST_DENY
	 * @param	string	 reason				拒绝理由，仅在 拒绝 时可用
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupAddRequest(INT64 robotID, string responseFlag, INT32 requestType, INT32 resultFlag, string reason = "");

	/*
	 * 置处理好友添加请求
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	string	 responseFlag		请求事件收到的「反馈标识」参数
	 * @param	INT32	 resultFlag			处理结果，通过/REQUEST_ALLOW 或 拒绝/REQUEST_DENY
	 * @param	string	 remarks			通过时为添加后的好友备注，拒绝时为拒绝理由
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setFriendAddRequest(INT64 robotID, string responseFlag, INT32 resultFlag, string remarks = "");
```
### 设置

<a id="set"> </a>

```c++
/**
	 * 置消息撤回
	 * @param	INT64		robotID		使用的机器人QQ
	 * @param	string		msgInfo		消息信息
	 * @return	INT32		操作结果
	 */
	static INT32 setMessageSvcMsgWithDraw(INT64 robotID, string msgInfo);

	/*
	 * 删除好友
	 * @param	INT64	 robotID	使用的机器人QQ
	 * @param	INT64	 uin		目标QQ
	 * @return	INT32	 unknown	(推测)状态码
	 */
	static INT32 setFriendDelete(INT64 robotID, INT64 uin);

	/*
	 * 置群文件上传
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	INT64	 dwGroup			目标群
	 * @param	string	 strParentFolder	群文件夹路径，如 「/」为根目录
	 * @param	string	 strLocalPath		本地文件路径，请填完整路径，不可空
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupFileUpload(INT64 robotID, INT64 dwGroup, string strParentFolder = "/", string strLocalPath = "");

	/*
	 * 置群文件删除
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	INT64	 dwGroup			目标群
	 * @param	INT64	 fileBusID			文件总线ID
	 * @param	string	 strParentFolder	父文件夹ID 目标群文件夹路径，如 「/」为根目录
	 * @param	string	 fileID				文件ID，不可空
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupFileDelete(INT64 robotID, INT64 dwGroup, INT64 fileBusID, string strParentFolder = "/", string fileID = "");

	/*
	 * 置群员移除
	 * 需要管理员权限
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	INT64	 dwGroup			所在群
	 * @param	INT64	 uin				目标QQ
	 * @param	bool	 ignoreAddRequest	不再接收此人加群申请，无法撤销，请慎用
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupMembersKick(INT64 robotID, INT64 dwGroup, INT64 uin, bool ignoreAddRequest = false);

	/*
	 * 置全群禁言
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		目标群
	 * @param	bool	 newStatus		要设置的新状态，true/开启禁言 false/关闭禁言
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupWholeBanSpeak(INT64 robotID, INT64 dwGroup, bool newStatus);

	/*
	 * 置群员禁言
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 uin			目标QQ
	 * @param	INT64	 timeStamp		禁言时间，单位为秒，最长为1个月。如果要解禁，这里填写0
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupMemberBanSpeak(INT64 robotID, INT64 dwGroup, INT64 uin, INT64 timeStamp = 0);

	/*
	 * 置群匿名成员禁言
	 * 禁言后无法解除
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 headMark		匿名用户的头像标识
	 * @param	BYTES	 token			匿名用户Token
	 * @param	string	 card			匿名用户名片
	 * @param	INT64	 timeStamp		禁言时间，单位为秒
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupAnonymousBanSpeak(INT64 robotID, INT64 dwGroup, INT64 headMark, BYTES token, string card, INT64 timeStamp);

	/*
	 * 设置群匿名聊天开关
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		目标群
	 * @param	bool	 newStatus		要设置的新状态，true/允许、false/禁止 匿名聊天
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupAnonymousBan(INT64 robotID, INT64 dwGroup, bool newStatus);

	/*
	 * 置群临时会话开关
	 * 需要群主权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		目标群
	 * @param	bool	 newStatus		要设置的新状态，true/允许、false/禁止 通过群发起临时会话
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupPrivateSession(INT64 robotID, INT64 dwGroup, bool newStatus);

	/*
	 * 置群成员发起多人聊天开关
	 * 需要群主权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		目标群
	 * @param	bool	 newStatus		要设置的新状态，true/允许、false/禁止 通过群发起多人聊天
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupManyPeopleChat(INT64 robotID, INT64 dwGroup, bool newStatus);

	/*
	 * 设置群管理员
	 * 需要群主权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 uin			目标QQ
	 * @param	bool	 newStatus		true/设置 false/取消 管理员
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupAdmini(INT64 robotID, INT64 dwGroup, INT64 uin, bool newStatus);

	/*
	 * 设置群成员名片
	 * 需要管理员权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 uin			目标QQ
	 * @param	string	 newCard		新名片，如果要删除，请填空文本
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupMemberCard(INT64 robotID, INT64 dwGroup, INT64 uin, string newCard = "");

	/*
	 * 设置群成员专属头衔
	 * 需要群主权限
	 * 目前仅安卓QQ协议支持
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwGroup		所在群
	 * @param	INT64	 uin			目标QQ
	 * @param	string	 specialTitle	头衔，如需删除，请填空文本
	 * @param	INT32	 expireTime		有效期，单位为秒。如果永久有效，请填-1
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setGroupSpecialTitle(INT64 robotID, INT64 dwGroup, INT64 uin, string  specialTitle = "", INT32 rxpireTime = -1);

	/*
	 * 置群退出
	 * @param	INT64		robotID		使用的机器人QQ
	 * @param	INT64		dwGroup		目标群
	 * @param	newStatus	disband		是否解散群，true/解散 false/退出
	 * @return	INT32		unknown		(推测)状态码
	 */
	static INT32 setGroupExit(INT64 robotID, INT64 dwGroup, bool disband = false);

	/*
	 * 置讨论组退出
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwDiscuss		目标讨论组
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setDiscussExit(INT64 robotID, INT64 dwDiscuss);

	/*
	 * 置讨论组成员移除
	 * 需要创建者权限
	 * @param	INT64	 robotID		使用的机器人QQ
	 * @param	INT64	 dwDiscuss		所在讨论组
	 * @param	INT64	 uin			目标QQ
	 * @return	INT32	 unknown		(推测)状态码
	 */
	static INT32 setDiscussMembersKick(INT64 robotID, INT64 dwDiscuss, INT64 uin);

	/*
	 * 置添加群
	 * 因为各种限制，可能不成功
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	INT64	 dwGroup			目标群
	 * @param	string	 additionalMsg		附加信息
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupAdd(INT64 robotID, INT64 dwGroup, string additionalMsg);

	/*
	 * 置处理群添加请求
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	string	 responseFlag		请求事件收到的「反馈标识」参数
	 * @param	INT32	 requestType		请求类型，邀请/REQUEST_GROUP_INVITE 或 加群/REQUEST_GROUP_INVITE
	 * @param	INT32	 resultFlag			处理结果，通过/REQUEST_ALLOW 或 拒绝/REQUEST_DENY
	 * @param	string	 reason				拒绝理由，仅在 拒绝 时可用
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setGroupAddRequest(INT64 robotID, string responseFlag, INT32 requestType, INT32 resultFlag, string reason = "");

	/*
	 * 置处理好友添加请求
	 * @param	INT64	 robotID			使用的机器人QQ
	 * @param	string	 responseFlag		请求事件收到的「反馈标识」参数
	 * @param	INT32	 resultFlag			处理结果，通过/REQUEST_ALLOW 或 拒绝/REQUEST_DENY
	 * @param	string	 remarks			通过时为添加后的好友备注，拒绝时为拒绝理由
	 * @return	INT32	 unknown			(推测)状态码
	 */
	static INT32 setFriendAddRequest(INT64 robotID, string responseFlag, INT32 resultFlag, string remarks = "");
```
### 获取
<a id="get"> </a>

```c++
/**
		 * 取插件的Json信息
		 * 用于APPInfo函数
		 * @return	CSTRING		Json文本
		 */
		static CSTRING getJsonInfo();
	/**
	 * 置AuthCode
	 * @param	INT32	authCode	应用标识
	 */
	static void setAuthCode(INT32 authCode);

	/**
	 * 取AuthCode
	 * @return	INT32	authCode	应用标识
	 */
	static INT32 getAuthCode();

	/**
	 * 置ProtocolType
	 * @param	INT32	protocolType	协议类型 1/安卓QQ协议 2/PCQQ协议
	 */
	static void setProtocolType(INT32 protocolType);

	/**
	 * 取ProtocolType
	 * @return	INT32	protocolType	协议类型 1/安卓QQ协议 2/PCQQ协议
	 */
	static INT32 getProtocolType();

	/**
	 * 置插件启用状态
	 * @param	bool	state	启用状态
	 */
	static void setAppEnable(bool state);

	/**
	 * 取插件启用状态
	 * @return	bool	state	启用状态
	 */
	static bool getAppEnable();

	/**
	 * 取框架名
	 * @return	string		框架名
	 */
	static string getFrameName();

	/*
	 * 置应用自停用
	 * @param	INT64	waitTime	等待时间(单位：毫秒)，留出一定时间使函数调用完成，避免直接操作出现冲突造成框架崩溃
	 * @return	INT32	unknown
	 */
	static INT32 setAppSelfDiscontinue(INT64 waitTime = 1000);

	/*
	 * 置应用自卸载
	 * @param	INT64	waitTime	等待时间，单位：毫秒
	 * @return	INT32	unknown
	 */
	static INT32 setAppSelfUninstall(INT64 waitTime = 1000);

	/**
	 * 取应用目录
	 * 返回的路径末尾带「\」
	 * @return	string		应用目录
	 */
	static string getAppDirectory();

	/**
	 * 取登录QQ列表
	 * @param	INT64List	bindLoginQQList		登录QQ列表的引用，执行成功后将存放数据于此
	 * @return	bool		执行结果
	 */
	static bool getLoginQQList(INT64List & bindLoginQQList);

	/**
	 * 取登录QQ列表(含在线状态)
	 * @param	bool		getState			取在线状态
	 * @param	LoginQQList	bindLoginQQList		登录QQ列表的引用，执行成功后将存放数据于此
	 * @return	bool		执行结果
	 */
	static bool getLoginQQList(bool getState, Type::LoginQQList & bindLoginQQList);

	/**
	 * 随机取一个登录QQ
	 * @param	useCache	使用缓存
	 * @return	INT64		登录QQ
	 */
	static INT64 getRandomLoginQQ(bool useCache = false);

	/*
	 * 取框架账号状态
	 * @param	INT64	robotID		要查询的账号
	 * @return	INT32	账号状态		0/离线 1/在线
	 */
	static INT32 getFrameAccountState(INT64 robotID);

	/**
	 * 取指定机器人的昵称
	 * @param	INT64	robotID		要查询昵称的机器人QQ
	 * @return	string	nick		该机器人的昵称
	 */
	static string getLoginQQName(INT64 robotID);

	/**
	 * 取指定机器人的cookies
	 * @param	INT64		robotID		要查询的机器人QQ
	 * @return	string		cookies		该机器人的cookies
	 */
	static string getCookies(INT64 robotID);

	/**
	 * 取指定机器人的csrfToken
	 * @param	INT64	robotID		要查询的机器人QQ
	 * @return	INT32	csrfToken	该机器人的csrfToken
	 */
	static INT32 getCsrfToken(INT64 robotID);

	/**
	 * 取域名cookie
	 * @param	INT64		robotID		要查询的机器人QQ
	 * @param	string		domain		要获取cookies的域名，http://qun.qq.com 或 http://qun.qzone.qq.com
	 * @return	string		cookies		登录指定域名在跳转成功后的cookies
	 */
	static string getDomainCookies(INT64 robotID, string domain = "http://qun.qq.com");

	/**
	 * 取好友列表
	 * @param	INT64		robotID			要查询的机器人QQ
	 * @param	FriendList	bindFriendList	好友列表的引用，执行成功后将存放数据于此
	 * @return	bool		执行结果
	 */
	static bool getFriendList(INT64 robotID, Type::FriendList & bindFriendList);

	/**
	 * 取QQ概要信息
	 * @param	INT64			robotID				使用的机器人QQ
	 * @param	INT64			uin					查询QQ
	 * @param	QQSummaryInfo	bindQSummaryInfo	QQ概要信息的引用，执行成功后将存放数据于此
	 * @return	bool			执行结果
	 */
	static bool getQQSummaryInfo(INT64 robotID, INT64 uin, Type::QQSummaryInfo & bindQSummaryInfo);

	/**
	 * 取群列表
	 * @param	INT64		robotID			要查询的机器人QQ
	 * @param	GroupList	bindGroupList	群列表的引用，执行成功后将存放数据于此
	 * @return	bool		执行结果
	 */
	static bool getGroupList(INT64 robotID, Type::GroupList & bindGroupList);

	/**
	 * 取群资料
	 * @param	INT64		robotID			使用的机器人QQ
	 * @param	INT64		dwGroup			要查询的群号
	 * @param	GroupInfo	bindGroupInfo	群资料的引用，执行成功后将存放数据于此
	 * @return	bool		执行结果
	 */
	static bool getGroupInfo(INT64 robotID, INT64 dwGroup, Type::GroupInfo & bindGroupInfo);

	/**
	 * 取群管理员列表
	 * 包括群主
	 * @param	INT64			robotID				使用的机器人QQ
	 * @param	INT64			dwGroup				要查询的群号
	 * @param	GroupAdminList	bindGroupAdminList	群管理列表的引用，执行成功后将存放数据于此
	 * @return	bool			执行结果
	 */
	static bool getGroupAdminList(INT64 robotID, INT64 dwGroup, Type::GroupAdminList & bindGroupAdminList);

	/**
	 * 取群成员列表
	 * PC协议只能获取QQ和管理权限
	 * @param	INT64			robotID					使用的机器人QQ
	 * @param	INT64			dwGroup					要查询的群号
	 * @param	GroupMemberList	bindGroupMemberList		群成员列表的引用，执行成功后将存放数据于此
	 * @return	bool			执行结果
	 */
	static bool getGroupMemberList(INT64 robotID, INT64 dwGroup, Type::GroupMemberList & bindGroupMemberList);

	/**
	 * 取群成员名片
	 * @param	INT64		robotID			使用的机器人QQ
	 * @param	INT64		dwGroup			所在群
	 * @param	INT64		uin				要查询的QQ号
	 * @param	bool		useNick			使用昵称，默认不使用。若名片为空，使用时返回昵称，不使用则返回空
	 * @param	bool		useCache		使用缓存，默认使用
	 * @return	string		该群成员的名片
	 */
	static string getGroupMemberCard(INT64 robotID, INT64 dwGroup, INT64 uin, bool useNick = false, bool useCache = true);

	/**
	 * 取讨论组列表
	 * @param	INT64			robotID				要查询的机器人QQ
	 * @param	DiscussList		bindDiscussList		讨论组列表的引用，执行成功后将存放数据于此
	 * @return	bool			执行结果
	 */
	static bool getDiscussList(INT64 robotID, Type::DiscussList & bindDiscussList);
```
### 转化
<a id="conv"> </a>

```c++
	/**
	 * 编码_UTF8转Ansi
	 * @param	BYTES		contents		UTF-8编码文本
	 * @return	CSTRING		GB2312编码文本
	 */
	static CSTRING convertUtf8ToAnsi(BYTES contents);
	/**
	 * 编码_UTF8转Ansi
	 * @param	string		contents		UTF-8编码文本
	 * @return	CSTRING		GB2312编码文本
	 */
	static CSTRING convertUtf8ToAnsi(string contents);

	/**
	 * 编码_GB2312转UTF8
	 * @param	string		contents	GB2312编码文本
	 * @return	BYTES		UTF-8编码文本
	 */
	static BYTES convertAnsiToUtf8(string contents);

	/**
	 * 解析到匿名信息
	 * @param	string		strAnonymousInfo	匿名数据
	 * @param	Anonymous	bindAnonymousInfo	匿名信息的引用，解析成功后将存放数据于此
	 * @return	bool		解析结果
	 */
	static bool decodeAnonymousInfo(string strAnonymousInfo, Type::Anonymous & bindAnonymousInfo);

	/**
	 * 解析到群附加信息
	 * @param	string					strGroupAdditionalInfo		群附加信息数据
	 * @param	GroupAdditionalInfo		bindGroupAdditionalInfo		群附加信息的引用，解析成功后将存放数据于此
	 * @return	bool					解析结果
	 */
	static bool decodeGroupAdditionalInfo(string strGroupAdditionalInfo, Type::GroupAdditionalInfo & bindGroupAdditionalInfo);

	/**
	 * 解析到字体信息
	 * @param	string		strFontInfo		字体数据
	 * @param	Font		bindFontInfo	字体信息的引用，解析成功后将存放数据于此
	 * @return	bool		解析结果
	 */
	static bool decodeFontInfo(string strFontInfo, Type::Font & bindFontInfo);

	/**
	 * 解析到群文件信息
	 * @param	string		strFileInfo		文件数据
	 * @param	File		bindFileInfo	文件信息的引用，解析成功后将存放数据于此
	 * @return	bool		解析结果
	 */
	static bool decodeFileInfo(string strFileInfo, Type::File & bindFileInfo);
```
## QYCODE

特殊代码相关。包括表情、文件、图片等等。

```c++
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
```
## QYLOG

日志相关，调试用的API

```c++
	/**
	 * 添加调试日志
	 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
	 * @param	string	 event		事件名称
	 * @param	string	 contents	事件内容
	 * @return	INT32	 unknown	固定返回0
	 */
	static INT32 Debug(INT64 robotID, string event, string contents);
```


```c++
	/**
	 * 添加信息日志
	 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
	 * @param	string	 event		事件名称
	 * @param	string	 contents	事件内容
	 * @return	INT32	 unknown	固定返回0
	 */
	static INT32 Info(INT64 robotID, string event, string contents);
```


```c++
	/**
	 * 添加警告日志
	 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
	 * @param	string	 event		事件名称
	 * @param	string	 contents	事件内容
	 * @return	INT32	 unknown	固定返回0
	 */
	static INT32 Warning(INT64 robotID, string event, string contents);
```


```c++
	/**
	 * 添加错误日志
	 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
	 * @param	string	 event		事件名称
	 * @param	string	 contents	事件内容
	 * @return	INT32	 unknown	固定返回0
	 */
	static INT32 Error(INT64 robotID, string event, string contents);
```


```C++
	/**
	 * 添加致命错误日志
	 * @param	INT64	 robotID	机器人QQ，用于区分多号登录
	 * @param	string	 event		事件名称
	 * @param	string	 contents	事件内容
	 * @return	INT32	 unknown	固定返回0
	 */
	static INT32 Fatal(INT64 robotID, string event, string contents);
```