// event.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#ifndef QYEVENT
#define QYEVENT(TYPE) extern "C" __declspec(dllexport) TYPE __stdcall 
#endif

void test();

/*
 * 返回插件基础信息
 * 本函数【禁止】处理其他任何代码
 */
QYEVENT(CSTRING) AppInfo()
{
	return QY::getJsonInfo();
}


/*
 * 接收应用AuthCode
 * 本函数【禁止】处理其他任何代码，请不要改动本函数
 */
QYEVENT(INT32) Initialize(
	INT32	AuthCode,		// 应用标识
	INT32	ProtocolType	// 协议类型 1 / 安卓QQ协议 2 / PCQQ协议
)
{
	QY::setAuthCode(AuthCode);
	QY::setProtocolType(ProtocolType);
	return 0;
}

/*
 * [1001]主程序启动
 * 本子程序会在【主线程】中被调用。
 * 无论本应用是否被启用，本函数都会在主程序启动后执行一次，请在这里执行插件初始化代码。
 * 请务必尽快返回本子程序，否则会卡住其他插件以及主程序的加载。
 * 这里禁止直接载入窗口
 */
QYEVENT(INT32) QY_Event_Startup()
{
	return 0; //请固定返回0。
}

/*
 * [1002]主程序退出
 * 本子程序会在【主线程】中被调用。
 * 无论本应用是否被启用或卸载，本函数都会在退出前执行一次，请在这里执行插件关闭代码。
 */
QYEVENT(INT32) QY_Event_Exit()
{
	return 0; //请固定返回0。
}

/*
 * [1003]应用被启用
 * 本子程序会在【主线程】中被调用。
 * 当应用被启用后，将收到此事件。
 * 如果载入时应用已被启用，则在_eventStartup(Type=1001,启动)被调用后，本函数也将被调用一次。
 * 如非必要，不建议在这里加载窗口。（可以添加菜单，让用户手动打开窗口）
 */
QYEVENT(INT32) QY_Event_Enable()
{
	QY::setAppEnable(true);
	return 0; //请固定返回0。
}

/*
 * [1004]应用被停用
 * 当应用被停用前，将收到此事件。
 * 如果载入时应用已被停用或卸载，则本函数【不会】被调用。
 * 无论本应用是否被启用，主程序关闭前本函数都【不会】被调用。
 */
QYEVENT(INT32) QY_Event_Disable()
{
	QY::setAppEnable(false);
	return 0; //请固定返回0。
}

/*
 * [166]私聊消息
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_PrivateMsg(
	INT64		robotID,		// 机器人QQ，用于区分多号登录
	INT32		subType,		// 消息渠道，11/来自好友 1/来自在线状态 2/来自群 3/来自讨论组 4/来自公众号
	INT64		sendTime,		// 发送时间(13位时间戳)
	INT64		fromQQ,			// 来源对象
	INT64		fromGroup,		// 来源群组(仅子类型为2/3时使用)
	CSTRING		fromInfo,		// 来源者信息
	CSTRING		msg,			// 消息内容
	CSTRING		info,			// 信息
	INT32		intTest			// 用于测试(我也不知道机器人作者想干嘛
)
{
	// 发送私聊消息
	QY::sendFriendMsg(robotID, fromQQ, string("你发送了这样的消息：") + msg);
 	if(string(msg) == "1") {
		// 点赞1次
		QY::sendLikeFavorite(robotID, fromQQ, 1);
		// 删除好友
		//QY::setFriendDelete(robotID, fromQQ);
		// 发送离线文件
		switch(subType) {
			case 11: // 好友消息
			{
				//QY::sendOfflineFile(robotID, 1, 0, fromQQ, R"(D:\QYBot\QY.robot.Update.exe)");
				nstring ns(L"你好");
				QY::sendFriendMsg(robotID, fromQQ, ns);
				ns = "我是小娜";
				QY::sendFriendMsg(robotID, fromQQ, ns);
				ns = "请问你是我的闺蜜Sir吗";
				ns += "?";
				QY::sendFriendMsg(robotID, fromQQ, ns);
				break;
			}
			case 2: // 群临时消息
			case 3: // 讨论组临时消息
			{
				QY::sendOfflineFile(robotID, (2 + subType), fromGroup, fromQQ, R"(D:\test\123.cpp)");
				break;
			}
			// 其他临时消息就不用管了，因为发不了
		}
		return QY::EVENT_BLOCK;
	}

	// 如果要回复消息，请调用API发送，并且这里 return QY::EVENT_BLOCK - 截断本条消息，不再继续处理
	// 注意：应用优先级设置为"最高"(10000)时，不得使用本返回值
	// 如果不回复消息，交由之后的应用/过滤器处理，这里 return QY::EVENT_IGNORE - 忽略本条消息
	return QY::EVENT_IGNORE;
}

/*
 * [82]群消息
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_GroupMsg(
	INT64		robotID,		// 机器人QQ，用于区分多号登录
	INT32		subType,		// 子类型，目前固定为1
	INT64		sendTime,		// 发送时间(13位时间戳)
	INT64		fromGroup,		// 来源群号
	INT64		fromQQ,			// 来源QQ号
	CSTRING		fromInfo,		// 来源者信息
	CSTRING		msg,			// 消息内容
	CSTRING		info,			// 事件总信息
	INT32		intTest			// 用于测试
)
{
	QY::infoAnalyze u;
	if(fromInfo != "") {
		u.write(fromInfo);
		if(fromQQ == 80000000) {
			// 收到匿名消息
			QY::Type::Anonymous anonInfo;
			QY::decodeAnonymousInfo(u.read("Anon"), anonInfo);
			string strTips = "";
			strTips += "Token长度：" + to_string(anonInfo.token.size());
			strTips += "，Card：" + anonInfo.card;
			strTips += "，Head：" + to_string(anonInfo.headMark);
			strTips += "，Time：" + to_string(anonInfo.expireTimeStamp);
			//QY::addLog::Debug(robotID, "AnonymousInfo", strTips);
			QY::setGroupAnonymousBanSpeak(robotID, fromGroup, anonInfo.headMark, anonInfo.token, anonInfo.card, 1);
			QY::setGroupAnonymousBan(robotID, fromGroup, false);
		}

		// 群附加信息
		QY::Type::GroupAdditionalInfo gAdditionalInfo;
		if(QY::decodeGroupAdditionalInfo(u.read("GExtraInfo"), gAdditionalInfo)) {
			string strTips = "";
			strTips += "Nick：";
			strTips += gAdditionalInfo.nick;
			strTips += "，gCard：" + gAdditionalInfo.gCard;
			strTips += "，Level：" + to_string(gAdditionalInfo.level);
			strTips += "，Flags：" + to_string(gAdditionalInfo.flags);
			strTips += "，gLevel：" + to_string(gAdditionalInfo.gLevel);
			strTips += "，sTitle：" + gAdditionalInfo.sTitle;
			strTips += "，MTID：" + to_string(gAdditionalInfo.MTID);
			//QY::addLog::Debug(robotID, "GroupAdditionalInfo", strTips);
		}

		// 字体信息
		QY::Type::Font fontInfo;
		if(QY::decodeFontInfo(u.read("FontInfo"), fontInfo)) {
			string strTips = "";
			strTips += "Name：" + fontInfo.name;
			strTips += "，Size：" + to_string(fontInfo.size);
			strTips += "，Color：" + to_string(fontInfo.color);
			strTips += "，Effect：" + to_string(fontInfo.effect);
			strTips += "，ColorTextID：" + to_string(fontInfo.colorTextID);
			//QY::addLog::Debug(robotID, "FontInfo", strTips);
		}
		QY::addLog::Debug(robotID, "msg", msg);

		string msgInfo = u.read("MsgInfo");
		// QY::addLog::Debug(robotID, "msgInfo", msgInfo);
		string srcMsg = u.read("srcmsg");
		QY::addLog::Debug(robotID, "srcMsg", srcMsg);
		if(string(msg) == "&#91;群签到&#93;请使用手机QQ进行查看。")
			// 撤回消息 (可恶的签到鸡)
			QY::setMessageSvcMsgWithDraw(robotID, msgInfo);
	}
	if(string(msg) == "求踢") {
		QY::setGroupMembersKick(robotID, fromGroup, fromQQ);
	}
	if(string(msg) == "test") {
		if(fromQQ == 10001) {
			//QY::setGroupAdmini(robotID, fromGroup, fromQQ, false);
			//QY::setGroupAdmini(robotID, fromGroup, fromQQ, true);

			//QY::setGroupAnonymousBan(robotID, fromGroup, false);
			//QY::setGroupAnonymousBan(robotID, fromGroup, true);
			//QY::setGroupWholeBanSpeak(robotID, fromGroup, true);
			//QY::setGroupFileUpload(robotID, fromGroup, "/", "D:\\QYBot\\QY.PC\\SDKv.2018\\[面向对象]Json.ec");
			QY::sendOfflineFile(robotID, 2, fromGroup, 0, "D:\\QYBot\\QY.PC\\SDKv.2018\\[面向对象]Json.ec");
			//QY::setGroupWholeBanSpeak(robotID, fromGroup, false);
		} else {
			//QY::setGroupMemberBanSpeak(robotID, fromGroup, fromQQ, 10);
			//QY::setGroupMemberBanSpeak(robotID, fromGroup, fromQQ, 0);
			QY::sendOfflineFile(robotID, 4, fromGroup, fromQQ, "D:\\QYBot\\QY.PC\\SDKv.2018\\[面向对象]Json.ec");
			/*
			QY::addLog::Debug(robotID, "getGroupMemberCard", QY::getGroupMemberCard(robotID, fromGroup, fromQQ, false, false));
			if(QY::getGroupMemberCard(robotID, fromGroup, fromQQ, false, false) == "")
				QY::setGroupMemberCard(robotID, fromGroup, fromQQ, "test");
			else
				QY::setGroupMemberCard(robotID, fromGroup, fromQQ);
			*/
		}
	}
	return QYAPI::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * [83]讨论组消息
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_DiscussMsg(
	INT64		robotID,		// 机器人QQ，用于区分多号登录
	INT32		subType,		// 子类型，目前固定为1
	INT64		sendTime,		// 发送时间(13位时间戳)
	INT64		fromDiscuss,	// 来源讨论组
	INT64		fromQQ,			// 来源QQ号
	CSTRING		fromInfo,		// 来源者信息
	CSTRING		msg,			// 消息内容
	CSTRING		info,			// 事件总信息
	INT32		intTest			// 用于测试
)
{
	return QY::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * [101]推送消息
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_PushMsgEvent(
	INT64		robotID,		// 机器人QQ，用于区分多号登录
	INT32		subType,		// 子类型，目前固定为1
	INT64		sendTime,		// 发送时间(13位时间戳)
	INT64		fromGroup,		// 来源群号
	INT64		fromQQ,			// 操作对象
	INT64		param,			// 操作参数，部分情况下会是QQ号
	CSTRING		msg,			// 事件信息
	CSTRING		info,			// 事件总信息
	INT32		intTest			// 用于测试
)
{
	string strTips;
	switch(subType)
	{
		case 1:		// 群成员名片变更
		{
			strTips = "群：" + to_string(fromGroup) + " QQ：" + to_string(fromQQ) + " 群名片变更为：" + msg;
			break;
		}

		case 2:		// 群公告变更 要新发布才有 修改是没有的
		{
			strTips = "群：" + to_string(fromGroup) + " QQ：" + to_string(fromQQ) + " 发布了新公告：" + msg;
			break;
		}

		case 3:		// 全员禁言开关
		{
			strTips = "群：" + to_string(fromGroup) + " QQ：" + to_string(fromQQ) + " ";
			strTips += (param == 0) ? "关闭" : "开启";
			strTips += "了全员禁言";
			break;
		}

		case 4:		// 群成员被禁言
		{
			strTips = "群：" + to_string(fromGroup) + " QQ：" + to_string(fromQQ) + " 被管理QQ：" + to_string(param);
			if(string(msg) == "0")
				strTips += "解除禁言";
			else
				strTips += string("禁言") + msg + "秒";
			break;
		}

		case 5:		// 群匿名开关
		{
			strTips = "群：" + to_string(fromGroup) + " QQ：" + to_string(fromQQ) + " ";
			strTips += (param == 4294967295) ? "已禁止群内匿名聊天" : "已允许群内匿名聊天";
			break;
		}

		case 6:		// 群匿名成员被禁言
		{
			strTips = "群：" + to_string(fromGroup) + " QQ：" + to_string(fromQQ) + " 已禁言匿名用户[" + msg + "] ";
			strTips += to_string(param) + "秒";
			break;
		}

		case 7:		// 群消息撤回
		{
			strTips = "群：" + to_string(fromGroup) + " QQ：" + to_string(fromQQ) + " " + msg;
			break;
		}

		case 8:		// 群系统提示
		{
			strTips = "群：" + to_string(fromGroup) + " Tips：" + msg;
			break;
		}

		case 9:		// 群文件上传
		{
			strTips = "fromGroup：" + to_string(fromGroup) + "\n" \
				+ "fromQQ：" + to_string(fromQQ) + "\n" \
				+ "msg：" + msg + "\n";
			if(info == "") break;
			string str;
			QY::infoAnalyze u(info);
			QY::Type::File fileInfo;
			if(QY::decodeFileInfo(u.read("MsgFile"), fileInfo)) {
				str += "name：" + fileInfo.name + "\n" \
					+ "，id：" + fileInfo.id + "\n" \
					+ "，size：" + fileInfo.size + "\n" \
					+ "，busID：" + to_string(fileInfo.busID) + "\n" \
					+ "，byteSize：" + to_string(fileInfo.byteSize) + "\n";
				str += "，setGroupFileDelete：" + to_string(QY::setGroupFileDelete(robotID, fromGroup, fileInfo.busID, "/", fileInfo.id));
			}
			QY::addLog::Debug(robotID, "群文件", str);

			break;
		}

		default:
			break;
	}
	QY::addLog::Debug(robotID, to_string(subType), strTips);
	return QY::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * [102]群事件-管理员变动
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_System_GroupAdmin(
	INT64	robotID,		// 机器人QQ，用于区分多号登录
	INT32	subType,		// 子类型，1/被取消管理员 2/被设置管理员
	INT64	sendTime,		// 发送时间(13位时间戳)
	INT64	fromGroup,		// 来源群组
	INT64	beingOperateQQ	// 被操作对象
)
{
	return QY::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * [103]群事件-群成员减少
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_System_GroupMemberDecrease(
	INT64	robotID,		// 机器人QQ，用于区分多号
	INT32	subType,		// 子类型，1/群解散 2/群员离开 3/群员被踢。
	INT64	sendTime,		// 发送时间(13位时间戳)
	INT64	fromGroup,		// 来源群组
	INT64	fromQQ,			// 操作对象(仅子类型为2、3时存在)
	INT64	beingOperateQQ	// 被操作对象
)
{
	return QY::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * [104]群事件-群成员增加
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_System_GroupMemberIncrease(
	INT64	robotID,		// 机器人QQ，用于区分多号
	INT32	subType,		// 子类型，1/管理员已同意 2/管理员邀请。
	INT64	sendTime,		// 发送时间(13位时间戳)
	INT64	fromGroup,		// 来源群组
	INT64	fromQQ,			// 操作对象(仅子类型为2、3时存在)
	INT64	beingOperateQQ	// 被操作对象
)
{
	return QY::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * [201]添加他人为好友结果事件
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_FriendEvent(
	INT64		robotID,		// 机器人QQ，用于区分多号
	INT32		subType,		// 子类型，1/对方同意添加 2/对方拒绝添加
	INT64		sendTime,		// 发送时间(13位时间戳)
	INT64		fromQQ,			// 来源对象
	CSTRING		info			// 信息
)
{
	return QY::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * [301]请求-他人添加好友
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_Request_AddFriend(
	INT64		robotID,		// 机器人QQ，用于区分多号
	INT32		subType,		// 子类型，目前固定为1
	INT64		sendTime,		// 请求时间(13位时间戳)
	INT64		fromQQ,			// 来源对象
	CSTRING		source,			// 来源信息
	CSTRING		msg,			// 附言
	CSTRING		responseFlag	// 反馈标识(处理请求用)
)
{
	string res = "robotID：" + to_string(robotID);
	res += "，subType：" + to_string(subType);
	res += "，sendTime：" + to_string(sendTime);
	res += "，fromQQ：" + to_string(fromQQ);
	res += "，source：" + string(source);
	res += "，msg：" + string(msg);
	//QY::addLog::Debug(robotID, "Request_AddFriend", res);

	//QY::setFriendAddRequest(robotID, responseFlag, QY::REQUEST_DENY, "这是拒绝理由");
	QY::setFriendAddRequest(robotID, responseFlag, QY::REQUEST_ALLOW, "备注");
	return QY::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * [302]请求-群添加
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_Request_AddGroup(
	INT64		robotID,		// 机器人QQ，用于区分多号
	INT32		responseType,	// 请求类型，1/他人申请入群 2/群成员邀请他人入群 3/自己(即登录号)受邀入群
	INT64		sendTime,		// 请求时间(13位时间戳)
	INT64		fromGroup,		// 来源群组
	INT64		fromQQ,			// 来源对象
	CSTRING		source,			// 来源信息，请求类型为1时是来源渠道、为2或3时是邀请人QQ
	CSTRING		msg,			// 附言
	CSTRING		responseFlag	// 反馈标识(处理请求用)
)
{
	string res = "robotID：" + to_string(robotID);
	res += "，subType：" + to_string(responseType);
	res += "，sendTime：" + to_string(sendTime);
	res += "，fromGroup：" + to_string(fromGroup);
	res += "，fromQQ：" + to_string(fromQQ);
	res += "，source：" + string(source);
	res += "，msg：" + string(msg);
	//QY::addLog::Debug(robotID, "Request_AddGroup", res);

	switch(responseType)
	{
		case 1: // 他人申请入群
		{
			//QY::setGroupAddRequest(robotID, responseFlag, responseType, QY::REQUEST_ALLOW);
			//QY::setGroupAddRequest(robotID, responseFlag, responseType, QY::REQUEST_DENY, "拒绝申请加群");
			//return QY::EVENT_BLOCK;
			break;
		}

		case 2: // 群成员邀请他人入群
		{
			//QY::setGroupAddRequest(robotID, responseFlag, responseType, QY::REQUEST_DENY, "拒绝邀请");
			//return QY::EVENT_BLOCK;
			break;
		}

		case 3: // 自己(即登录号)受邀入群
		{
			//QY::setGroupAddRequest(robotID, responseFlag, responseType, QY::REQUEST_ALLOW);
			//QY::setGroupAddRequest(robotID, responseFlag, responseType, QY::REQUEST_DENY, "拒绝受邀");
			//return QY::EVENT_BLOCK;
			break;
		}

	}

	return QY::EVENT_IGNORE; //关于返回值说明, 见「QY_Event_PrivateMsg」函数
}

/*
 * 菜单函数，可在 info.json 资源文件中设置菜单数目、函数名
 * 如果不使用菜单，请在「 info.json、events.def 以及 此处 」删除无用函数
 */
QYEVENT(INT32) _menuA()
{
	/*
		写成这样, 
		一方面是为了兼容乱改字符集的操作,
		一方面是为了提醒你注意编码.
	*/
#ifdef UNICODE
	//MessageBox(NULL, L"这是menuA，在这里载入窗口，或者进行其他工作。", L"信息框", 0);
	MessageBoxA(NULL, "这是menuA，在这里载入窗口，或者进行其他工作。", "信息框", 0);
#else
	MessageBoxA(NULL, "这是menuA，在这里载入窗口，或者进行其他工作。", "信息框", 0);
#endif // !UNICODE
	return 0; //请固定返回0
}

QYEVENT(INT32) _menuB()
{
	test();
	return 0; //请固定返回0
}

//#include <fstream>
void test()
{
	nstring ns(QY::convertAnsiToUtf8("你好"));
	QY::addLog::Debug(QY::getRandomLoginQQ(), "convertAnsiToUtf8", to_string(strlen(ns.u8Str())));
	QY::addLog::Debug(QY::getRandomLoginQQ(), "convertAnsiToUtf8", ns);
	ns = QY::convertUtf8ToAnsi(ns);
	QY::addLog::Debug(QY::getRandomLoginQQ(), "convertUtf8ToAnsi", ns);
	//return;
	/* 部分测试代码使用「 if(i == 0) break; 」代替代码注释，如需使用，请自行删除 */

	// 停用插件自身
	//QY::setAppSelfDiscontinue();
	// 卸载插件自身
	//QY::setAppSelfUninstall();

	// 测试部分LQ码
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::Escape", QY::Code::Escape("&[,]"));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::Escape", QY::Code::Escape("&[,]", true));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::AntiEscape", QY::Code::AntiEscape("&amp;&#91;&#93;&#44;"));

	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::Face", QY::Code::Face(1));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::At", QY::Code::At(10001));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::At", QY::Code::At(10001, false));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::At", QY::Code::At(-1));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::LocalImage", QY::Code::LocalImage("E:\\robot\\image\\1.jpg"));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::OnlineImage", QY::Code::OnlineImage("http://dwz.cn/2ZJkzQ"));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::FlashPic", QY::Code::FlashPic("E:\\robot\\image,\\1.jpg"));
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "Code::Record", QY::Code::Record("E:\\robot\\record\\1.amr"));

	/*
	// 测试日志函数
	QY::addLog::Debug(QY::getRandomLoginQQ(), "AuthCode", std::to_string(QY::getAuthCode()).c_str());
	QY::addLog::Infos::Success(QY::getRandomLoginQQ(), "AuthCode", std::to_string(QY::getAuthCode()).c_str());
	QY::addLog::Infos::Fail(QY::getRandomLoginQQ(), "AuthCode", std::to_string(QY::getAuthCode()).c_str());
	QY::addLog::Infos::Receive(QY::getRandomLoginQQ(), "AuthCode", std::to_string(QY::getAuthCode()).c_str());
	QY::addLog::Infos::Send(QY::getRandomLoginQQ(), "AuthCode", std::to_string(QY::getAuthCode()).c_str());
	QY::addLog::Warning(QY::getRandomLoginQQ(), "AuthCode", std::to_string(QY::getAuthCode()).c_str());
	QY::addLog::Error(QY::getRandomLoginQQ(), "AuthCode", std::to_string(QY::getAuthCode()).c_str());
	QY::addLog::Fatal(QY::getRandomLoginQQ(), "AuthCode", std::to_string(QY::getAuthCode()).c_str());
	*/

	// 获取应用目录
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "getAppDirectory", QY::getAppDirectory());
	// 获取框架名
	//QY::addLog::Debug(QY::getRandomLoginQQ(), "getFrameName", QY::getFrameName());

	// 机器人QQ列表(含在线状态)
	//QY::Type::LoginQQList rList; 
	//QY::getLoginQQList(true, rList);

	INT64List rList; // 机器人QQ列表
	QY::getLoginQQList(rList);
	for(size_t i = 0; i < rList.size(); i++) {
		// 获取在线状态
		//QY::addLog::Debug(rList[i], to_string(rList[i]), to_string(QY::getFrameAccountState(rList[i])));

		// 获取机器人昵称
		//QY::addLog::Debug(rList[i], to_string(rList[i]), QY::getLoginQQName(rList[i]));

		// 获取Cookies、CsrfToken、指定域名Cookies
		//QY::addLog::Debug(rList[i], "getCookies", QY::getCookies(rList[i]));
		//QY::addLog::Debug(rList[i], "getCsrfToken", to_string(QY::getCsrfToken(rList[i])));
		//QY::addLog::Debug(rList[i], "getDomainCookies", QY::getDomainCookies(rList[i]));


		// 输出讨论组列表
		QY::Type::DiscussList disList;
		if(QY::getDiscussList(rList[i], disList)) {
			for(size_t j = 0; j < disList.size(); j++) {
				// 只是为了在不警告的情况下跳过执行
				if(j == 0) break;
				QY::addLog::Debug(rList[i], "createUin", to_string(disList[j].createUin));
				if(disList[j].createUin != rList[i]) {
					// 退出讨论组
					//QY::setDiscussExit(rList[i], disList[j].id);
				}
				else {
					// 移除讨论组成员
					//QY::setDiscussMembersKick(rList[i], disList[j].id, 10001);
				}

				// 测试发送消息
				//QY::sendDiscussMsg(rList[i], disList[j].id, "123");
				//QY::sendDiscussTmpMsg(rList[i], disList[j].id, 12345, "123");

				// 输出讨论组资料
				QY::addLog::Debug(rList[i], "id", to_string(disList[j].id));
				QY::addLog::Debug(rList[i], "name", disList[j].name);
				QY::addLog::Debug(rList[i], "nameBuffer", QY::convertUtf8ToAnsi(disList[i].nameBuffer));
				QY::addLog::Debug(rList[i], "createTimeStamp", to_string(disList[j].createTimeStamp));
				QY::addLog::Debug(rList[i], "createUin", to_string(disList[j].createUin));
				QY::addLog::Debug(rList[i], "infoSeq", to_string(disList[j].infoSeq));
				QY::addLog::Debug(rList[i], "lastInfoTimeStamp", to_string(disList[j].lastInfoTimeStamp));
				QY::addLog::Debug(rList[i], "msgSeq", to_string(disList[j].msgSeq));
				QY::addLog::Debug(rList[i], "lastMsgTimeStamp", to_string(disList[j].lastMsgTimeStamp));
				QY::addLog::Debug(rList[i], "memberNum", to_string(disList[j].memberNum));
				QY::addLog::Debug(rList[i], "flag", to_string(disList[j].flag));
				QY::addLog::Debug(rList[i], "inheritOwnerUin", to_string(disList[j].inheritOwnerUin));
				QY::addLog::Debug(rList[i], "groupID", to_string(disList[j].groupID));
				QY::addLog::Debug(rList[i], "groupTempID", to_string(disList[j].groupTempID));
				QY::addLog::Debug(rList[i], "confMeetingOrigin", to_string(disList[j].confMeetingOrigin));
				QY::addLog::Debug(rList[i], "qidianConfType", to_string(disList[j].qidianConfType));
				QY::addLog::Debug(rList[i], "confMeetingOption", to_string(disList[j].confMeetingOption));
			}
		}

		//QY::setGroupAdd(rList[i], 10001, "测试加群");

		// 输出群列表
		QY::Type::GroupList gList;
		if(QY::getGroupList(rList[i], gList)) {
			for(size_t j = 0; j < gList.size(); j++) {
				//QY::sendGroupMsg(rList[i], gList[j].id, "123");
				//QY::sendGroupTmpMsg(rList[i], gList[j].id, 12345, "123");
				//continue;

				//QY::addLog::Debug(rList[i], "GroupID", to_string(gList[j].id));
				//QY::addLog::Debug(rList[i], "Name", gList[j].name);
				//QY::addLog::Debug(rList[i], "TempGroupID", to_string(gList[j].tempID));
				//QY::addLog::Debug(rList[i], to_string(gList[j].id), gList[j].name);


				// 输出群资料
				QY::Type::GroupInfo gInfo;
				QY::getGroupInfo(rList[i], gList[j].id, gInfo);

				QY::addLog::Debug(rList[i], to_string(gInfo.id), to_string(gInfo.ownerUin));
				QY::addLog::Debug(rList[i], to_string(gInfo.id), to_string(gInfo.createTimeStamp));
				QY::addLog::Debug(rList[i], to_string(gInfo.id), to_string(gInfo.memberNum));
				QY::addLog::Debug(rList[i], to_string(gInfo.id), to_string(gInfo.maxMemberNum));
				QY::addLog::Debug(rList[i], to_string(gInfo.id), to_string(gInfo.level));
				QY::addLog::Debug(rList[i], to_string(gInfo.id), gInfo.name);
				QY::addLog::Debug(rList[i], to_string(gInfo.id), QY::convertUtf8ToAnsi(gInfo.nameBuffer));
				QY::addLog::Debug(rList[i], to_string(gInfo.id), gInfo.introduction);
				QY::addLog::Debug(rList[i], to_string(gInfo.id), QY::convertUtf8ToAnsi(gInfo.introductionBuffer));

				break;

				// 如果机器人是群主
				if(gInfo.ownerUin == rList[i]) {
					/*
					// 设置群临时会话开关
					QY::setGroupPrivateSession(rList[i], gInfo.id, false);
					QY::setGroupPrivateSession(rList[i], gInfo.id, true);
					QY::setGroupPrivateSession(rList[i], gInfo.id, false);

					// 设置群多人聊天开关
					QY::setGroupManyPeopleChat(rList[i], gInfo.id, false);
					QY::setGroupManyPeopleChat(rList[i], gInfo.id, true);
					QY::setGroupManyPeopleChat(rList[i], gInfo.id, false);
					*/

					// 退群(一定失败，因为是群主)
					//QY::setGroupExit(rList[i], gInfo.id, false);
					// 解散群(PC端似乎不允许使用)
					//QY::setGroupExit(rList[i], gInfo.id, true);
				}


				// 输出群管理员列表
				QY::Type::GroupAdminList gAdminList;
				if(QY::getGroupAdminList(rList[i], gList[j].id, gAdminList)) {
					string card;
					for(size_t k = 0; k < gAdminList.size(); k++) {
						QY::getGroupMemberCard(rList[i], gList[j].id, gAdminList[k].uin, card, true);
						QY::addLog::Debug(
							rList[i],
							to_string(gList[j].id),
							to_string(gAdminList[k].uin) + " " \
							+ to_string(gAdminList[k].permission) + " " \
							// + QY::getGroupMemberCard(rList[i], gList[j].id, gAdminList[k].uin)
							+ card
						);
					}
				}


				/*
				// 输出群成员列表
				QY::Type::GroupMemberList gMemberList;
				if(QY::getGroupMemberList(rList[i], gList[j].id, gMemberList)) {
					// 使用ofstream时，记得把函数上面的「 #include <fstream> 」解除注释
					std::ofstream o(std::to_string(gList[j].id) + ".log");
					for(size_t k = 0; k < gMemberList.size(); k++) {
						o << gMemberList[k].uin << " ";
						o << gMemberList[k].nick << " ";
						o << gMemberList[k].card << " ";
						o << gMemberList[k].sex << " ";
						o << gMemberList[k].age << " ";
						o << gMemberList[k].age << " ";
						o << gMemberList[k].joinTimeStamp << " ";
						o << gMemberList[k].lastSpeakTimeStamp << " ";
						o << gMemberList[k].gLevelName << " ";
						o << gMemberList[k].permission << " ";
						o << gMemberList[k].sTitle << " ";
						o << gMemberList[k].sTitleValidPeriod << " ";
						o << (int)gMemberList[k].isBadMember << " ";
						o << (int)gMemberList[k].allowChangeCard << " ";
						o << std::endl;
					}
					o.close();

				}
				*/

			}
		}

		continue;

		// 取机器人自己的概要资料
		QY::Type::QQSummaryInfo QQSummaryInfo;
		if(QY::getQQSummaryInfo(rList[i], rList[i], QQSummaryInfo)) {
			QY::addLog::Debug(rList[i], "QQID", to_string(QQSummaryInfo.uin));
			QY::addLog::Debug(rList[i], "Sex", to_string(QQSummaryInfo.sex));
			QY::addLog::Debug(rList[i], "Nick", QQSummaryInfo.nick);
			QY::addLog::Debug(rList[i], "Signature", QQSummaryInfo.signature);
			QY::addLog::Debug(rList[i], "Birthday", QQSummaryInfo.birthday);
			QY::addLog::Debug(rList[i], "Age", to_string(QQSummaryInfo.age));
			QY::addLog::Debug(rList[i], "Level", to_string(QQSummaryInfo.level));
			QY::addLog::Debug(rList[i], "qAge", to_string(QQSummaryInfo.qAge));
			QY::addLog::Debug(rList[i], "LikeCount", to_string(QQSummaryInfo.likeCount));
			QY::addLog::Debug(rList[i], "IsLike", to_string(QQSummaryInfo.isLike));
		}

		// 输出好友列表
		QY::Type::FriendList friendList;
		if(QY::getFriendList(rList[i], friendList)) {
			for(size_t i = 0; i < friendList.size(); i++) {
				QY::addLog::Debug(rList[i], "Uin", std::to_string(friendList[i].uin).c_str());
				QY::addLog::Debug(rList[i], "Nick", friendList[i].nick);
			}
		}
	}
}

#undef QYEVENT
