#include "../stdafx.h"
#include "../utils/utils.h"
#include "../resource.h"
#include "api.h"
//#include "dll.h"
#include <qy\dll.h>

#ifndef QYAPI_TOLOG
#define QYAPI_TOLOG true // 调用API时输出调试日志，用来判断是否触发API
#endif // !QYAPI_TOLOG


bool QYAPI::appEnable = false;
INT32 QYAPI::authCode = 0;
INT32 QYAPI::protocolType = 0;
string QYAPI::appDirectory = "";



/**
 * 取插件的Json信息
 * @return	CSTRING		json文本
 */
CSTRING QYAPI::getJsonInfo()
{
	static char * info = nullptr;
	if(info) return info;
	//ofstream out("test.log");

	string source = GetResourceFile("JSON", IDR_JSON1);
	//out << source;

	string json = "";
	string lineText = "";

	uint32_t index = 0;
	uint32_t indexLine = 0;
	uint32_t indexNote = 0;

	while(true) {
		/* 获取每行文本，因为行尾可能是\n\r、\n，所以反复查找 */
		indexLine = source.find("\n\r", index);
		if(indexLine == (uint32_t)string::npos)
			indexLine = source.find("\n", index);
		lineText = (indexLine == (uint32_t)string::npos)
			? source.substr(index) : source.substr(index, (indexLine - index));
		//out << lineText << " " << lineText.length() << endl;

		/* 简单过滤单行注释 */
		indexNote = 0;
		while(true) {
			indexNote = lineText.find("//", indexNote);
			if(indexNote == (uint32_t)string::npos) break;
			/* 取出前面文本，根据引号数量判断是否为注释 */
			int qm = 0; //引号数量
			const char * head = lineText.substr(0, indexNote).c_str();
			for(int i = 0; head[i] != '\0'; i++) {
				if(head[i] == '"' && (i > 0 && head[i - 1] != '\\')) ++qm;
			}
			//out << "qm = " << qm << " ";
			if(qm % 2 == 0) {
				//是注释
				lineText = lineText.substr(0, indexNote);
				break;
			}
			indexNote += 2;
		}
		/* 判断是否为空文本行(纯空格) */
		int nSpace = 0;
		const char * s = lineText.c_str();
		for(int i = 0; s[i] == ' '; i++) nSpace++;
		/* 是空文本行就不返回 */
		if(nSpace != lineText.length()) {
			json += lineText; // +"\n\r";
			//out << lineText << " [E]" << endl;
		}
		if(indexLine == (uint32_t)string::npos) break;
		index = indexLine + strlen("\n");
	}


	//out << endl << endl;
	//不知道为什么文末乱码，总之再截取一次就over
	json = json.substr(0, json.find_last_of('}') + 1);
	//out << json;
	//MessageBoxA(NULL, json.c_str(), "信息框", 0);
	info = new char[json.length() + 1];
	strcpy_s(info, json.length() + 1, json.c_str());
	return info;
}

/**
 * 置AuthCode
 * @param	INT32	authCode	应用标识
 */
void QYAPI::setAuthCode(
	INT32	authCode	// 应用标识
)
{
	QYAPI::authCode = authCode;
}

/**
 * 取AuthCode
 * @return	INT32	authCode	应用标识
 */
INT32 QYAPI::getAuthCode()
{
	return QYAPI::authCode;
}

/**
 * 置ProtocolType
 * @param	INT32	ProtocolType	协议类型 1/安卓QQ协议 2/PCQQ协议
 */
void QYAPI::setProtocolType(
	INT32	protocolType	// 协议类型 1/安卓QQ协议 2/PCQQ协议
)
{
	QYAPI::protocolType = protocolType;
}

/**
 * 取ProtocolType
 * @return	INT32	ProtocolType	协议类型 1/安卓QQ协议 2/PCQQ协议
 */
INT32 QYAPI::getProtocolType()
{
	return QYAPI::protocolType;
}

/**
 * 置插件启用状态
 * @param	bool	state	启用状态
 */
void QYAPI::setAppEnable(
	bool state
)
{
	QYAPI::appEnable = state;
}

/**
 * 取插件启用状态
 * @return	bool	AppEnable	启用状态
 */
bool QYAPI::getAppEnable()
{
	return QYAPI::appEnable;
}

/**
 * 取框架名
 * @return	string		框架名
 */
string QYAPI::getFrameName()
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(true), __func__, "");
	return QY_getFrameName(QYAPI::authCode);
}

/*
 * 置应用自停用
 * @param	INT64	waitTime		等待时间，单位：毫秒
 * @return	INT32	unknown
 */
INT32 QYAPI::setAppSelfDiscontinue(
	INT64 waitTime	// 等待时间
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(true), __func__, "等待时间：" + to_string(waitTime));
	return QY_setAppSelfDiscontinue(QYAPI::authCode, waitTime);
}

/*
 * 置应用自卸载
 * @param	INT64	waitTime	等待时间，单位：毫秒
 * @return	INT32	unknown
 */
INT32 QYAPI::setAppSelfUninstall(
	INT64 waitTime		//等待时间
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(true), __func__, "等待时间：" + to_string(waitTime));
	return QY_setAppSelfUninstall(QYAPI::authCode, waitTime);
}

/**
 * 取应用目录
 * 返回的路径末尾带「\」
 * @return	string		应用目录
 */
string QYAPI::getAppDirectory()
{
	if(QYAPI::appDirectory == "") {
		if(QYAPI_TOLOG)
			QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(true), __func__, "");
		QYAPI::appDirectory = QY_getAppDirectory(QYAPI::authCode);
	}
	return QYAPI::appDirectory;
}

/**
 * 解析_到登录QQ列表
 * @param	string		strLoginQQList
 * @param	INT64List	bindLoginQQList
 * @return	bool		解析是否成功
 */
bool decodeLoginQQList(
	string		strLoginQQList,		// 从接口获取的编码文本
	INT64List &	bindLoginQQList		// 登录QQ数组
)
{
	if(!strLoginQQList.length()) return false;
	string data = base64_decode(strLoginQQList);
	if(data.length() < 12) return false;
	UnPack u(data);
	INT32 count = u.GetInt();
	bindLoginQQList.resize(count);
	for(int i = 0; i < count; i++) 
		bindLoginQQList[i] = u.GetLong();
	return true;
}
/**
 * 取登录QQ列表
 * @param	INT64List	bindLoginQQList
 * @return	bool		执行结果
 */
bool QYAPI::getLoginQQList(
	INT64List & bindLoginQQList	// 登录QQ数组
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(true), __func__, "");
	string strLoginQQList = QY_getLoginQQList(QYAPI::authCode);
	if(!strLoginQQList.length()) return false;
	return decodeLoginQQList(strLoginQQList, bindLoginQQList);
}

/**
 * 取登录QQ列表(含在线状态)
 * @param	bool		getState			取在线状态
 * @param	LoginQQList	bindLoginQQList		登录QQ列表，执行成功后将存放数据于此
 * @return	bool		执行结果
 */
bool QYAPI::getLoginQQList(
	bool getState,							// 取在线状态
	QYTYPE::LoginQQList & bindLoginQQList	// 登录QQ列表
)
{
	INT64List intLoginQQList;
	if(!QYAPI::getLoginQQList(intLoginQQList)) return false;
	bindLoginQQList.resize(intLoginQQList.size());
	for(size_t i = 0; i < intLoginQQList.size(); ++i)
	{
		bindLoginQQList[i].id = intLoginQQList[i];
		if(getState)
			bindLoginQQList[i].state = QYAPI::getFrameAccountState(bindLoginQQList[i].id);
	}
	return true;
}

#include <random>
/**
 * 随机取一个登录QQ
 * @param	useCache	使用缓存
 * @return	INT64		登录QQ
 */
INT64 QYAPI::getRandomLoginQQ(bool useCache)
{
	static INT64 loginQQ = 0;
	if(useCache && loginQQ) return loginQQ;
	INT64List loginQQList;
	if(!QYAPI::getLoginQQList(loginQQList)) return false;
	std::random_device seed;
	std::mt19937 mt(seed());
	std::uniform_int_distribution<int> dist(1, loginQQList.size());
	loginQQ = loginQQList[dist(mt) - 1];
	return loginQQ;
}

/*
 * 取框架账号状态
 * @param	INT64	robotID		要查询的账号
 * @return	INT32	账号状态		0/离线 1/在线
 */
INT32 QYAPI::getFrameAccountState(
	INT64 robotID
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__, "机器人QQ：" + to_string(robotID));
	return QY_getFrameAccountState(QYAPI::authCode, robotID);
}

/**
 * 取指定机器人的昵称
 * @param	INT64		robotID		要查询昵称的机器人QQ
 * @return	string		nick		该机器人的昵称
 */
string QYAPI::getLoginQQName(
	INT64 robotID // 要查询昵称的已登录QQ
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__, "机器人QQ：" + to_string(robotID));
	return QY_getLoginNick(QYAPI::authCode, robotID);
}

/**
 * 取指定机器人的Cookies
 * @param	INT64		robotID		要查询的机器人QQ
 * @return	string		cookies		该机器人的Cookies
 */
string QYAPI::getCookies(
	INT64 robotID	// 要查询昵称的机器人QQ
) 
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__, "机器人QQ：" + to_string(robotID));
	return QY_getCookies(QYAPI::authCode, robotID);
}

/**
 * 取指定机器人的csrfToken
 * @param	INT64	robotID		要查询的机器人QQ
 * @return	INT32	csrfToken	该机器人的csrfToken
 */
INT32 QYAPI::getCsrfToken(
	INT64 robotID	// 要查询的机器人QQ
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__, "机器人QQ：" + to_string(robotID));
	return QY_getCsrfToken(QYAPI::authCode, robotID);
}

/**
 * 取指定域名的cookie
 * @param	INT64		robotID		要查询的机器人QQ
 * @param	string		domain		要获取cookies的域名，http://qun.qq.com 或 http://qun.qzone.qq.com
 * @return	string		cookies		登录指定域名在跳转成功后的cookies
 */
string QYAPI::getDomainCookies(
	INT64	robotID,	// 要查询的机器人QQ
	string	domain		// 要获取cookies的域名，http://qun.qq.com 或 http://qun.qzone.qq.com
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__, 
			"机器人QQ：" + to_string(robotID) \
			+ "，要获取cookies的域名：" + domain
		);
	if(domain == "") domain = "http://qun.qq.com";
	return QY_getDomainCookie(QYAPI::authCode, robotID, domain.c_str());
}

/**
 * 解析_到好友列表
 * @param	string		strFriendList
 * @param	FriendList	bindFriendList
 * @return	bool		解析是否成功
 */
bool decodeFriendList(
	string strFriendList,					// 从接口获取的编码数据
	QYTYPE::FriendList & bindFriendList		// 好友列表的引用
)
{
	if(!strFriendList.length()) return false;
	string data = base64_decode(strFriendList);
	if(data.length() < 10) return false;
	UnPack u(data);
	INT32 count = u.GetInt();
	bindFriendList.resize(count);
	for(int i = 0; i < count; i++) {
		bindFriendList[i].uin = u.GetLong();
		bindFriendList[i].nick = u.GetLenStr();
	}
	return true;
}
/**
 * 取好友列表
 * @param	INT64		robotID			要查询的机器人QQ
 * @param	FriendList	bindFriendList	好友列表的引用，执行成功后将存放数据于此
 * @return	bool		执行结果
 */
bool QYAPI::getFriendList(
	INT64 robotID,							// 要查询的机器人QQ
	Type::FriendList & bindFriendList		// 好友列表的引用
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__, "机器人QQ：" + to_string(robotID));
	string strFriendList = QY_getFriendList(QYAPI::authCode, robotID);
	if(!strFriendList.length()) return false;
	return decodeFriendList(strFriendList, bindFriendList);
}

#include <ctime>
/**
 * 解析_到QQ概要信息
 * @param	string			strSummaryInfo
 * @param	QQSummaryInfo	bindQSummaryInfo
 * @return	bool			解析是否成功
 */
bool decodeQQSummaryInfo(
	string strSummaryInfo,						// 从接口获取的编码数据
	QYTYPE::QQSummaryInfo &	bindQSummaryInfo	// QQ概要信息的引用
)
{
	if(!strSummaryInfo.length()) return false;
	string data = base64_decode(strSummaryInfo);
	if(data.length() < 9) return false;
	UnPack u(data);
	bindQSummaryInfo.uin = u.GetLong();
	bindQSummaryInfo.sex = u.GetInt();
	bindQSummaryInfo.nick = u.GetLenStr();
	u.GetToken();
	bindQSummaryInfo.signature = u.GetLenStr();
	u.GetToken();
	bindQSummaryInfo.birthday = u.GetLenStr();
	if(bindQSummaryInfo.birthday == "0/0/0" || bindQSummaryInfo.birthday == "")
		bindQSummaryInfo.age = -1;
	else {
		// 获取实际时间
		int AgeYear = static_cast<int>(strtoll(bindQSummaryInfo.birthday.c_str(), nullptr, 10));
		int AgeMonth = static_cast<int>(
			strtoll(
				bindQSummaryInfo.birthday.substr(
					bindQSummaryInfo.birthday.find_first_of('/') + 1, 
					bindQSummaryInfo.birthday.find_last_of('/') - bindQSummaryInfo.birthday.find_first_of('/')
				).c_str(),
				nullptr, 
				10
			));
		int AgeDay = static_cast<int>(strtoll(bindQSummaryInfo.birthday.substr(bindQSummaryInfo.birthday.find_last_of('/') + 1).c_str(), nullptr, 10));
		/*
		QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(), "TransformBirthday", 
			to_string(AgeYear) + "/" + to_string(AgeMonth) + "/" + to_string(AgeDay));
		*/
		// 获取当前时间
		time_t timeStamp = time(NULL);
		struct tm NowTime;
		localtime_s(&NowTime, &timeStamp);
		NowTime.tm_year += 1900;
		++NowTime.tm_mon;
		NowTime.tm_wday;

		bindQSummaryInfo.age = NowTime.tm_year - AgeYear;
		//判断是否需要减1(是否满岁)
		if(AgeMonth > NowTime.tm_mon || (AgeMonth == NowTime.tm_mon && AgeDay > NowTime.tm_wday))
			--bindQSummaryInfo.age;
	}
	bindQSummaryInfo.level = u.GetInt();
	bindQSummaryInfo.qAge = u.GetInt();
	bindQSummaryInfo.likeCount = u.GetInt();
	bindQSummaryInfo.isLike = u.GetInt();
	return true;
}
/**
 * 取QQ概要信息
 * @param	INT64			robotID				使用的机器人QQ
 * @param	INT64			uin					查询QQ
 * @param	QQSummaryInfo	bindQSummaryInfo	QQ概要信息的引用，执行成功后将存放数据于此
 * @return	bool			执行结果
 */
bool QYAPI::getQQSummaryInfo(
	INT64 robotID,								// 使用的机器人QQ
	INT64 uin,									// 查询QQ
	QYTYPE::QQSummaryInfo & bindQSummaryInfo	// QQ概要信息的引用
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__, 
			"机器人QQ：" + to_string(robotID) \
			+ "，查询的QQ：" + to_string(uin)
		);
	string strSummaryInfo = QY_getSummaryInfo(QYAPI::authCode, robotID, uin);
	if(!strSummaryInfo.length()) return false;
	return decodeQQSummaryInfo(strSummaryInfo, bindQSummaryInfo);
}

/**
 * 解析_到群列表
 * @param	string		strGroupList
 * @param	GroupList	bindGroupList
 * @return	bool		解析是否成功
 */
bool decodeGroupList(
	string strGroupList,				// 从接口获取的编码数据
	QYTYPE::GroupList &	bindGroupList	// 群列表数组的引用
)
{
	if(!strGroupList.length()) return false;
	string data = base64_decode(strGroupList);
	if(data.length() < 10) return false;
	UnPack u(data);
	INT32 count = u.GetInt();
	bindGroupList.resize(count);
	for(int i = 0; i < count; i++) {
		bindGroupList[i].tempID = u.GetLong();
		bindGroupList[i].id = u.GetLong();
		bindGroupList[i].name = u.GetLenStr();
	}
	return true;
}
/**
 * 取群列表
 * @param	INT64		robotID			要查询的机器人QQ
 * @param	GroupList	bindGroupList	群列表的引用，执行成功后将存放数据于此
 * @return	bool		执行结果
 */
bool QYAPI::getGroupList(
	INT64 robotID,						// 要查询的机器人QQ
	QYTYPE::GroupList & bindGroupList	// 群列表的引用，执行成功后将存放数据于此
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID)
		);
	string strGroupList = QY_getGroupList(QYAPI::authCode, robotID);
	if(!strGroupList.length()) return false;
	return decodeGroupList(strGroupList, bindGroupList);
}

/**
 * 解析_到群资料
 * @param	string		strGroupInfo
 * @param	GroupInfo	bindGroupInfo
 * @return	bool		解析是否成功
 */
bool decodeGroupInfo(
	string strGroupInfo,				// 从接口获取的编码数据
	QYTYPE::GroupInfo &	bindGroupInfo	// 群信息的引用
)
{
	if(!strGroupInfo.length()) return false;
	string data = base64_decode(strGroupInfo);
	if(data.length() < 9) return false;
	UnPack u(data);
	bindGroupInfo.id = u.GetLong();
	bindGroupInfo.ownerUin = u.GetLong();
	bindGroupInfo.createTimeStamp = u.GetInt();
	bindGroupInfo.maxMemberNum = u.GetInt();
	bindGroupInfo.memberNum = u.GetInt();
	bindGroupInfo.name = u.GetLenStr();
	bindGroupInfo.nameBuffer = u.GetToken();
	bindGroupInfo.level = u.GetInt();
	bindGroupInfo.introduction = u.GetLenStr();
	bindGroupInfo.introductionBuffer = u.GetToken();
	return true;
}
/**
 * 取群资料
 * @param	INT64		robotID			使用的机器人QQ
 * @param	INT64		dwGroup			要查询的群号
 * @param	GroupInfo	bindGroupInfo	群资料的引用，执行成功后将存放数据于此
 * @return	bool		执行结果
 */
bool QYAPI::getGroupInfo(
	INT64 robotID,						// 要查询的机器人QQ
	INT64 dwGroup,						// 要查询的群号
	QYTYPE::GroupInfo & bindGroupInfo	// 群资料的引用
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，查询的群：" + to_string(dwGroup)
		);
	string strGroupInfo = QY_getGroupInfo(QYAPI::authCode, robotID, dwGroup);
	if(!strGroupInfo.length()) return false;
	return decodeGroupInfo(strGroupInfo, bindGroupInfo);
}

/**
 * 解析_到群管理员列表
 * @param	string			strGroupAdminList
 * @param	GroupAdminList	bindGroupAdminList
 * @return	bool			解析是否成功
 */
bool decodeGroupAdminList(
	string strGroupAdminList,					// 从接口获取的编码数据
	QYTYPE::GroupAdminList & bindGroupAdminList	// 群管理员数组的引用
)
{
	if(!strGroupAdminList.length()) return false;
	string data = base64_decode(strGroupAdminList);
	if(data.length() < 12) return false;
	UnPack u(data);
	INT32 count = u.GetInt();
	bindGroupAdminList.resize(count);
	for(int i = 0; i < count; i++) {
		bindGroupAdminList[i].uin = u.GetLong();
		bindGroupAdminList[i].permission = u.GetInt();
	}
	return true;
}

/**
 * 取群管理员列表
 * 包括群主
 * @param	INT64			robotID					使用的机器人QQ
 * @param	INT64			dwGroup					要查询的群号
 * @param	GroupAdminList	bindGroupAdminList		群管理数组的引用，执行成功后将存放数据于此
 * @return	bool			执行结果
 */
bool QYAPI::getGroupAdminList(
	INT64 robotID,									// 使用的机器人QQ
	INT64 dwGroup,									// 要查询的群号
	QYTYPE::GroupAdminList & bindGroupAdminList		// 群管理数组的引用
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，查询的群：" + to_string(dwGroup)
		);
	string strAdminList = QY_getGroupAdminList(QYAPI::authCode, robotID, dwGroup);
	if(strAdminList == "") return false;
	return decodeGroupAdminList(strAdminList, bindGroupAdminList);
}

/**
 * 取群成员信息
 * PC协议只能获取QQ和管理权限
 * @param	INT64			robotID					使用的机器人QQ
 * @param	INT64			dwGroup					要查询的群号
 * @param	INT64			uin						要查询的成员信息
 * @param	GroupMember		bindGroupMember			群成员信息的引用，执行成功后将存放数据于此
 * @return	bool			执行结果
 */
bool QYAPI::getGroupMemberInfo(
	INT64 robotID,
	INT64 dwGroup,
	INT64 uin,
	QYTYPE::GroupMember & bindGroupMember
)
{
	/*
		框架未提供查询单用户的API, 因此先获取全部成员信息, 再进行筛选.
	*/
	QYTYPE::GroupMemberList gMemberList;
	if(!QYAPI::getGroupMemberList(robotID, dwGroup, gMemberList)) return false;
	for(auto i : gMemberList) {
		if(i.uin == uin) {
			bindGroupMember = i;
			return true;
		}
	}
	return false;
}

/**
 * 解析_到群成员信息
 * @param	string			bytesGroupMember
 * @param	GroupMember		gMember
 * @return	bool			解析是否成功
 */
bool decodeGroupMember(
	BYTES bytesGroupMember,			// 从接口获取的编码数据
	QYTYPE::GroupMember & gMember	// 群成员数据
)
{
	if(bytesGroupMember.size() < 40) return false;
	UnPack u(bytesGroupMember);
	gMember.uin = u.GetLong();
	gMember.nick = u.GetLenStr();
	gMember.card = u.GetLenStr();
	gMember.sex = u.GetInt();
	gMember.age = u.GetInt();
	gMember.area = u.GetLenStr();
	gMember.joinTimeStamp = u.GetInt();
	gMember.lastSpeakTimeStamp = u.GetInt();
	gMember.gLevelName = u.GetLenStr();
	gMember.permission = u.GetInt();
	gMember.isBadMember = u.GetInt();
	gMember.sTitle = u.GetLenStr();
	gMember.sTitleValidPeriod = u.GetInt();
	gMember.allowChangeCard = u.GetInt();
	return true;
}
/**
 * 解析_到群成员列表
 * @param	string			strGroupMemberList
 * @param	GroupMemberList	gMemberList
 * @return	bool			解析是否成功
 */
bool decodeGroupMemberList(
	string strGroupMemberList,				// 从接口获取的编码数据
	QYTYPE::GroupMemberList & gMemberList	// 群成员数组
)
{
	if(!strGroupMemberList.length()) return false;
	string data = base64_decode(strGroupMemberList);
	if(data.length() < 10) return false;
	UnPack u(data);
	INT32 count = u.GetInt();
	gMemberList.resize(count);
	for(int i = 0; i < count; i++) {
		if(u.Len() <= 0) return false;
		if(!decodeGroupMember(u.GetToken(), gMemberList[i])) return false;
	}
	return true;
}
/**
 * 取群成员列表
 * PC协议获取只有QQ和管理权限
 * @param	INT64			robotID					使用的机器人QQ
 * @param	INT64			dwGroup					要查询的群号
 * @param	GroupMemberList	bindGroupMemberList		群成员数组的引用，执行成功后将存放数据于此
 * @return	bool			执行结果
 */
bool QYAPI::getGroupMemberList(
	INT64 robotID,									// 使用的机器人QQ
	INT64 dwGroup,									// 要查询的群号
	QYTYPE::GroupMemberList & bindGroupMemberList	// 群成员数组的引用
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，查询的群：" + to_string(dwGroup)
		);
	string strGroupMemberList = QY_getGroupMemberList(QYAPI::authCode, robotID, dwGroup);
	if(strGroupMemberList == "") return false;
	return decodeGroupMemberList(strGroupMemberList, bindGroupMemberList);
}

/**
 * 解析_到群名片
 * @param	string	strGroupMemberCard
 * @param	string	card
 * @param	bool	useNick
 * @return	bool	解析是否成功
 */
bool decodeGroupAdminList(
	string strGroupMemberCard,		// 从接口获取的编码数据
	string & card,					// 群名片
	bool useNick					// 使用昵称
)
{
	if(!strGroupMemberCard.length()) return false;
	string data = base64_decode(strGroupMemberCard);
	if(data.length() < 8) return false;
	UnPack u(data);
	card = u.GetLenStr();
	if(card == "" && useNick)
		card = u.GetLenStr();
	return true;
}
/**
 * 取群成员名片
 * @param	INT64		robotID			使用的机器人QQ
 * @param	INT64		dwGroup			所在群
 * @param	INT64		QQUin			要查询的QQ号
 * @param	bool		useNick			使用昵称，默认不使用。使用时，若名片为空则返回昵称；不使用则返回名片
 * @param	bool		useCache		使用缓存，默认使用
 * @return	string		该群成员的名片
 */
string QYAPI::getGroupMemberCard(
	INT64	robotID,	// 使用的机器人QQ
	INT64	dwGroup,	// 所在群
	INT64	uin,		// 要查询的QQ号
	bool	useNick,	// 使用昵称
	bool	useCache	// 使用缓存
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，查询的QQ：" + to_string(uin) \
			+ "，所在群：" + to_string(dwGroup) \
			+ "，" + (useNick ? "" : "不") + "使用昵称" \
			+ "，" + (useCache ? "" : "不") + "使用缓存"
		);
	string strGroupMemberCard = QY_getGroupMemberCard(QYAPI::authCode, robotID, dwGroup, uin, !useCache);
	if(strGroupMemberCard == "") return false;
	string card;
	decodeGroupAdminList(strGroupMemberCard, card, useNick);
	return card;
}

/**
 * 解析_到讨论组列表
 * @param	string			strDiscussList
 * @param	DiscussList		DiscussList
 * @return	bool			解析是否成功
 */
bool decodeDiscussList(
	string	strDiscussList,					// 从接口获取的编码数据
	QYTYPE::DiscussList & bindDiscussList	// 讨论组列表数组
)
{
	if(!strDiscussList.length()) return false;
	string data = base64_decode(strDiscussList);
	if(data.length() < 10) return false;
	UnPack u(data);
	INT32 count = u.GetInt();
	bindDiscussList.resize(count);
	for(int i = 0; i < count; i++) {
		bindDiscussList[i].id = u.GetLong();
		bindDiscussList[i].nameBuffer = u.GetToken();
		bindDiscussList[i].name = u.GetLenStr();
		u.GetInt();  // 错误代码
		bindDiscussList[i].createTimeStamp = u.GetInt();
		bindDiscussList[i].createUin = u.GetLong();
		bindDiscussList[i].infoSeq = u.GetInt();
		bindDiscussList[i].lastInfoTimeStamp = u.GetInt();
		bindDiscussList[i].msgSeq = u.GetInt();
		bindDiscussList[i].lastMsgTimeStamp = u.GetInt();
		bindDiscussList[i].memberNum = u.GetInt();
		bindDiscussList[i].flag = u.GetInt();
		bindDiscussList[i].inheritOwnerUin = u.GetLong();
		bindDiscussList[i].groupID = u.GetLong();
		bindDiscussList[i].groupTempID = u.GetLong();
		bindDiscussList[i].confMeetingOrigin = u.GetInt();
		bindDiscussList[i].qidianConfType = u.GetInt();
		bindDiscussList[i].confMeetingOption = u.GetInt();
	}
	return true;
}
/**
 * 取讨论组列表
 * @param	INT64			robotID				要查询的机器人QQ
 * @param	DiscussList		bindDiscussList		讨论组列表，执行成功后将存放数据于此
 * @return	bool			执行结果
 */
bool QYAPI::getDiscussList(
	INT64 robotID,							// 要查询的机器人QQ
	QYTYPE::DiscussList & bindDiscussList	// 讨论组列表
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) 
		);
	string strDiscussList = QY_getDiscussList(QYAPI::authCode, robotID);
	if(strDiscussList == "") return false;
	return decodeDiscussList(strDiscussList, bindDiscussList);
}

/**
 * 编码_UTF8转Ansi
 * @param	BYTES		contents		UTF-8编码文本
 * @return	CSTRING		GB2312编码文本
 */
CSTRING QYAPI::convertUtf8ToAnsi(
	BYTES contents	// UTF-8编码文本
)
{
	BYTE * bin = new BYTE[contents.size()];
	for(size_t i = 0; i < contents.size(); i++)
		bin[i] = contents[i];
	string str = base64_encode(bin, contents.size());
	delete[] bin;
	return QY_setEncodeUtf8ToAnsi(QYAPI::authCode, str.c_str());
}
/**
 * 编码_UTF8转Ansi
 * @param	string		contents		UTF-8编码文本
 * @return	CSTRING		GB2312编码文本
 */
CSTRING QYAPI::convertUtf8ToAnsi(
	string contents	// UTF-8编码文本
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(true), __func__,
			"待解码的utf-8文本：" + contents
		);
	BYTES bin(contents.cbegin(), contents.cend());
	return QYAPI::convertUtf8ToAnsi(bin);
}

/**
 * 编码_GB2312转UTF8
 * @param	string		contents	GB2312编码文本
 * @return	BYTES		UTF-8编码文本
 */
BYTES QYAPI::convertAnsiToUtf8(
	string contents	// GB2312编码文本
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(true), __func__,
			"待解码的gb2312文本：" + contents
		);
	string utf8 = QY_setEncodeAnsiToUtf8(QYAPI::authCode, contents.c_str());
	if(utf8 == "") return BYTES();
	utf8 = base64_decode(utf8);
	BYTES bin(utf8.cbegin(), utf8.cend());
	return bin;
}

/**
 * 解析到匿名信息
 * @param	string		strAnonymousInfo	匿名数据
 * @param	Anonymous	bindAnonymousInfo	匿名信息的引用
 * @return	bool		解析结果
 */
bool QYAPI::decodeAnonymousInfo(
	string strAnonymousInfo,
	QYTYPE::Anonymous & bindAnonymousInfo
)
{
	if(strAnonymousInfo == "") return false;
	string data = base64_decode(strAnonymousInfo);
	if(data.length() < 9) return false;
	UnPack u(data);
	bindAnonymousInfo.token = u.GetToken();
	bindAnonymousInfo.card = u.GetLenStr();
	bindAnonymousInfo.headMark = u.GetLong();
	bindAnonymousInfo.expireTimeStamp = u.GetLong();
	return true;
}

/**
 * 解析到群附加信息
 * @param	string					strGroupAdditionalInfo		群附加信息数据
 * @param	GroupAdditionalInfo		bindGroupAdditionalInfo		群附加信息的引用，解析成功后将存放数据于此
 * @return	bool					解析结果
 */
bool QYAPI::decodeGroupAdditionalInfo(
	string strGroupAdditionalInfo,							// 群附加信息数据
	QYTYPE::GroupAdditionalInfo & bindGroupAdditionalInfo	// 群附加信息的引用
)
{
	if(strGroupAdditionalInfo == "") return false;
	string data = base64_decode(strGroupAdditionalInfo);
	if(data.length() < 9) return false;
	UnPack u(data);
	bindGroupAdditionalInfo.nick = u.GetLenStr();
	bindGroupAdditionalInfo.gCard = u.GetLenStr();
	bindGroupAdditionalInfo.level = u.GetInt();
	bindGroupAdditionalInfo.flags = u.GetInt();
	bindGroupAdditionalInfo.gLevel = u.GetInt();
	bindGroupAdditionalInfo.sTitle = u.GetLenStr();
	bindGroupAdditionalInfo.MTID = u.GetInt();
	return true;
}

/**
 * 解析到字体信息
 * @param	string		strFontInfo		字体数据
 * @param	Font		bindFontInfo	字体信息的引用，解析成功后将存放数据于此
 * @return	bool		解析结果
 */
bool QYAPI::decodeFontInfo(
	string strFontInfo,				// 字体数据
	QYTYPE::Font & bindFontInfo		// 字体信息的引用
)
{
	if(strFontInfo == "") return false;
	string data = base64_decode(strFontInfo);
	if(data.length() < 9) return false;
	UnPack u(data);
	bindFontInfo.name = u.GetLenStr();
	bindFontInfo.size = u.GetInt();
	bindFontInfo.color = u.GetInt();
	bindFontInfo.effect = u.GetInt();
	bindFontInfo.colorTextID = u.GetInt();
	return true;
}

/**
 * 解析到群文件信息
 * @param	string		strFileInfo		文件数据
 * @param	File		bindFileInfo	文件信息的引用，解析成功后将存放数据于此
 * @return	bool		解析结果
 */
bool QYAPI::decodeFileInfo(
	string strFileInfo,				// 文件数据
	QYTYPE::File & bindFileInfo		// 文件信息的引用
)
{
	if(strFileInfo == "") return false;
	string data = base64_decode(strFileInfo);
	if(data.length() < 12) return false;
	UnPack u(data);
	bindFileInfo.name = u.GetLenStr();
	bindFileInfo.id = u.GetLenStr();
	bindFileInfo.size = u.GetLenStr();
	bindFileInfo.busID = u.GetLong();
	bindFileInfo.byteSize = u.GetLong();
	return true;
}

/**
 * 置致命错误提示
 * @param	string		errMsg		错误信息
 * @return	INT32		unknown
 */
INT32 QYAPI::setFatal(
	string errMsg	// 错误信息
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(QYAPI::getRandomLoginQQ(true), __func__,
			"错误信息：" + errMsg
		);
	return QY_setFatal(QYAPI::authCode, errMsg.c_str());
}

/**
 * 发送名片赞
 * @param	INT64	robotID		使用的机器人QQ
 * @param	INT64	uin			目标对象
 * @param	INT32	count		点赞次数
 * @return	INT32	固定返回0
 */
INT32 QYAPI::sendLikeFavorite(
	INT64 robotID,	// 机器人QQ
	INT64 uin,		// 目标QQ
	INT32 count		// 次数
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，对象：" + to_string(uin) \
			+ "，次数：" + to_string(count)
		);
	for(INT32 i = 0; i < count; i++) {
		QY_sendLikeFavorite(QYAPI::authCode, robotID, uin);
	}
	return 0;
}

/*
 * 发送好友消息
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 uin		目标QQ
 * @param	CSTRING	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
INT32 QYAPI::sendFriendMsg(
	INT64 robotID,	// 使用机器人QQ
	INT64 uin,		// 目标QQ
	string msg		// 消息内容
)
{
	if(msg == "") return -1;
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，发送到好友：" + to_string(uin) \
			+ "，消息内容：" + msg
		);
	return QY_sendFriendMsg(QYAPI::authCode, robotID, uin, msg.c_str());
}

/*
 * 发送群消息
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 dwGroup	目标群
 * @param	CSTRING	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
INT32 QYAPI::sendGroupMsg(
	INT64 robotID,	// 使用的机器人QQ
	INT64 dwGroup,	// 目标群
	string msg		// 消息内容
)
{
	if(msg == "") return -1;
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，发送到群：" + to_string(dwGroup) \
			+ "，消息内容：" + msg
		);
	return QY_sendGroupMsg(QYAPI::authCode, robotID, dwGroup, msg.c_str());
}

/*
 * 发送群临时消息
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 dwGroup	所在群
 * @param	INT64	 uin		目标QQ
 * @param	string	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
INT32 QYAPI::sendGroupTmpMsg(
	INT64 robotID,	// 使用的机器人QQ
	INT64 dwGroup,	// 所在群
	INT64 uin,		// 目标QQ
	string msg		// 消息内容
)
{
	if(msg == "") return -1;
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，发送到临时对象：" + to_string(uin) \
			+ "，所在群：" + to_string(dwGroup) \
			+ "，消息内容：" + msg
		);
	return QY_sendGroupTmpMsg(QYAPI::authCode, robotID, dwGroup, uin, msg.c_str());
}

/*
 * 发送讨论组消息
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 dwDiscuss	目标讨论组
 * @param	string	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
INT32 QYAPI::sendDiscussMsg(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwDiscuss,	// 目标讨论组
	string msg			// 消息内容
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，发送到讨论组：" + to_string(dwDiscuss) \
			+ "，消息内容：" + msg
		);
	return QY_sendDiscussMsg(QYAPI::authCode, robotID, dwDiscuss, msg.c_str());
}

/*
 * 发送讨论组临时消息
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 dwDiscuss	所在讨论组
 * @param	INT64	 uin		目标QQ
 * @param	string	 msg		消息内容
 * @return	INT32	 unknown	(推测)状态码
 */
INT32 QYAPI::sendDiscussTmpMsg(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwDiscuss,	// 所在讨论组
	INT64 uin,			// 目标QQ
	string msg			// 消息内容
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，发送到临时对象：" + to_string(uin) \
			+ "，所在讨论组：" + to_string(dwDiscuss) \
			+ "，消息内容：" + msg
		);
	return QY_sendDiscussTmpMsg(QYAPI::authCode, robotID, dwDiscuss, uin, msg.c_str());
}

/*
 * 发送离线文件
 * 如需上传群文件到指定目录，请使用「setGroupFileUpload」
 * @param	INT64		robotID			使用的机器人QQ
 * @param	INT32		dwMsgType		消息类型，1/好友 2/群 3/讨论组 4/群临时 5/讨论组临时
 * @param	INT64		dwGroup			所在群组的 群号 / 讨论组ID
 * @param	INT64		dwUin			QQ号，发送个人消息时使用(包括临时消息)
 * @param	CSTRING		strLocalPath	文件路径
 * @return	INT32		unknown			(推测)状态码
 */
INT32 QYAPI::sendOfflineFile(
	INT64 robotID,			// 使用的机器人QQ
	INT32 dwMsgType,		// 消息类型
	INT64 dwGroup,			// 群组号
	INT64 dwUin,			// QQ号
	string strLocalPath		// 文件路径
)
{
	switch(dwMsgType)
	{
		case 1: // 好友消息
		{
			if(QYAPI_TOLOG)
				QYAPI::addLog::Debug(robotID, __func__,
					"机器人QQ：" + to_string(robotID) \
					+ "，发送到好友：" + to_string(dwUin) \
					+ "，文件路径：" + strLocalPath
				);
			return QY_sendOfflineFile(QYAPI::authCode, robotID, dwUin, dwUin, 166, 0, strLocalPath.c_str());
		}

		case 2: // 群消息
		{
			return QYAPI::setGroupFileUpload(robotID, dwGroup, "/", strLocalPath);
		}

		case 3: // 讨论组
		{
			if(QYAPI_TOLOG)
				QYAPI::addLog::Debug(robotID, __func__,
					"机器人QQ：" + to_string(robotID) \
					+ "，发送到讨论组：" + to_string(dwGroup) \
					+ "，文件路径：" + strLocalPath
				);
			return QY_sendOfflineFile(QYAPI::authCode, robotID, dwGroup, 0, 83, 0, strLocalPath.c_str());
		}

		case 4: // 群临时
		{
			if(QYAPI_TOLOG)
				QYAPI::addLog::Debug(robotID, __func__,
					"机器人QQ：" + to_string(robotID) \
					+ "，发送到临时对象：" + to_string(dwUin) \
					+ "，所在群：" + to_string(dwGroup) \
					+ "，文件路径：" + strLocalPath
				);
			return QY_sendOfflineFile(QYAPI::authCode, robotID, dwGroup, dwUin, 141, 0, strLocalPath.c_str());
		}

		case 5: // 讨论组临时
		{
			if(QYAPI_TOLOG)
				QYAPI::addLog::Debug(robotID, __func__,
					"机器人QQ：" + to_string(robotID) \
					+ "，发送到临时对象：" + to_string(dwUin) \
					+ "，所在讨论组：" + to_string(dwGroup) \
					+ "，文件路径：" + strLocalPath
				);
			return QY_sendOfflineFile(QYAPI::authCode, robotID, dwGroup, dwUin, 141, 1, strLocalPath.c_str());
		}
	}
	return -1;
}

/**
 * 置消息撤回
 * @param	INT64		robotID		使用的机器人QQ
 * @param	string		msgInfo		消息信息
 * @return	INT32		操作结果
 */
INT32 QYAPI::setMessageSvcMsgWithDraw(
	INT64 robotID,		// 使用的机器人
	string msgInfo		// 消息信息
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，msgInfo：" + msgInfo
		);
	return QY_setMessageSvcMsgWithDraw(QYAPI::authCode, robotID, msgInfo.c_str());
}

/*
 * 删除好友
 * @param	INT64	 robotID	使用的机器人QQ
 * @param	INT64	 QQUin		目标QQ
 * @return	INT32	 unknown	(推测)状态码
 */
INT32 QYAPI::setFriendDelete(
	INT64 robotID,	// 使用的机器人QQ
	INT64 uin		// 目标QQ
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，目标QQ：" + to_string(uin)
		);
	return QY_setDelFriend(QYAPI::authCode, robotID, uin);
}

/*
 * 置群文件上传
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	INT64	 dwGroup			目标群
 * @param	string	 strParentFolder	群文件夹路径，如 「/」为根目录
 * @param	string	 strLocalPath		本地文件路径
 * @return	INT32	 unknown			(推测)状态码
 */
INT32 QYAPI::setGroupFileUpload(
	INT64 robotID,				// 使用的机器人QQ
	INT64 dwGroup,				// 目标群
	string strParentFolder,		// 群文件夹路径
	string strLocalPath			// 本地文件路径
)
{
	if(strLocalPath == "") return -1;
	if(strParentFolder == "") strParentFolder = "/";
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，目标群：" + to_string(dwGroup) \
			+ "，群文件夹目录：" + strParentFolder \
			+ "，本地文件路径：" + strLocalPath
		);
	return QY_setGroupFileUpload(QYAPI::authCode, robotID, dwGroup, strParentFolder.c_str(), strLocalPath.c_str());
}

/*
 * 置群文件删除
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	INT64	 dwGroup			目标群
 * @param	INT64	 fileBusID			文件总线ID
 * @param	string	 strParentFolder	父文件夹ID 目标 群文件夹路径，如 「/」为根目录
 * @param	string	 fileID				文件ID，不可空
 * @return	INT32	 unknown			(推测)状态码
 */
INT32 QYAPI::setGroupFileDelete(
	INT64 robotID,				// 使用的机器人QQ
	INT64 dwGroup,				// 目标群
	INT64 fileBusID,			// 文件总线ID
	string strParentFolder,		// 父文件夹ID
	string fileID				// 文件ID
)
{
	if(fileID == "") return -1;
	if(strParentFolder == "") strParentFolder = "/";
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，目标群：" + to_string(dwGroup) \
			+ "，文件总线ID：" + to_string(fileBusID) \
			+ "，父文件夹ID：" + strParentFolder \
			+ "，文件ID：" + fileID
		);
	return QY_setDelGroupFile(QYAPI::authCode, robotID, dwGroup, fileBusID, strParentFolder.c_str(), fileID.c_str());
}

/*
 * 置群员移除
 * 需要管理员权限
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	INT64	 dwGroup			所在群
 * @param	INT64	 uin				目标QQ
 * @param	bool	 rejectAddRequest	不再接收此人加群申请，请慎用
 * @return	INT32	 unknown			(推测)状态码
 */
INT32 QYAPI::setGroupMembersKick(
	INT64 robotID,				// 使用的机器人QQ
	INT64 dwGroup,				// 所在群
	INT64 uin,					// 目标QQ
	bool rejectAddRequest		// 不再接收此人加群申请
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，所在群：" + to_string(dwGroup) \
			+ "，目标QQ：" + to_string(uin) \
			+ "，" + (rejectAddRequest ? "不再接收此人加群申请" : "允许下次加群")
		);
	return QY_setGroupMembersKick(QYAPI::authCode, robotID, dwGroup, uin, int(rejectAddRequest));
}

/*
 * 置全群禁言
 * 需要管理员权限
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	bool	 newStatus		要设置的新状态，true/开启禁言 false/关闭禁言
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupWholeBanSpeak(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwGroup,		// 所在群
	bool newStatus		// 要设置的新状态
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，群：" + to_string(dwGroup) \
			+ "，" + (newStatus ? "开启" : "关闭") + "全群禁言"
		);
	return QY_setGroupWholeBanSpeak(QYAPI::authCode, robotID, dwGroup, int(newStatus));
}

/*
 * 置群员禁言
 * 需要管理员权限
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT64	 uin			目标QQ
 * @param	INT64	 timeStamp		禁言时间，单位为秒。如果要解禁，这里填写0
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupMemberBanSpeak(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwGroup,		// 所在群
	INT64 uin,			// 目标QQ
	INT64 timeStamp		// 禁言时间
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，所在群：" + to_string(dwGroup) \
			+ "，目标QQ：" + to_string(uin) \
			+ "，" + (timeStamp ? ("禁言" + to_string(timeStamp) + "秒") : "解除禁言")
		);
	return QY_setGroupMembersBanSpeak(QYAPI::authCode, robotID, dwGroup, uin, timeStamp);
}

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
INT32 QYAPI::setGroupAnonymousBanSpeak(
	INT64 robotID,
	INT64 dwGroup,
	INT64 headMark,
	BYTES token,
	string card,
	INT64 timeStamp
)
{
	BYTE * bin = new BYTE[token.size()];
	for(size_t i = 0; i < token.size(); i++)
		bin[i] = token[i];
	string strToken = base64_encode(bin, token.size());
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，所在群：" + to_string(dwGroup) \
			+ "，头像标识：" + to_string(headMark) \
			+ "，Token：" + strToken \
			+ "，名片：" + card \
			+ "，禁言：" + to_string(timeStamp) + "秒"
		);
	return QY_setGroupAnonymousBanSpeak(QYAPI::authCode, robotID, dwGroup, (INT32)headMark, strToken.c_str(), card.c_str(), timeStamp);
}

/*
 * 设置群匿名聊天开关
 * 需要管理员权限
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	bool	 newStatus		要设置的新状态
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupAnonymousBan(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwGroup,		// 目标群
	bool newStatus		// 要设置的新状态
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，群：" + to_string(dwGroup) \
			+ "，" + (newStatus ? "允许" : "禁止") + "匿名聊天"
		);
	return QY_setGroupAnonymousBan(QYAPI::authCode, robotID, dwGroup, int(newStatus));
}

/*
 * 置群临时会话开关
 * 需要群主权限
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	bool	 newStatus		要设置的新状态
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupPrivateSession(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwGroup,		// 目标群
	bool newStatus		// 要设置的新状态
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，群：" + to_string(dwGroup) \
			+ "，" + (newStatus ? "允许" : "禁止") + "通过群发起临时会话"
		);
	return QY_setGroupPrivateSession(QYAPI::authCode, robotID, dwGroup, int(newStatus));
}

/*
 * 置群成员发起多人聊天开关
 * 需要群主权限
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	INT32	 Switch			开关
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupManyPeopleChat(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwGroup,		// 目标群
	bool newStatus		// 要设置的新状态
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，群：" + to_string(dwGroup) \
			+ "，" + (newStatus ? "允许" : "禁止") + "通过群发起多人聊天"
		);
	return QY_setGroupManyPeopleChat(QYAPI::authCode, robotID, dwGroup, int(newStatus));
}

/*
 * 设置群管理员
 * 需要群主权限
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT64	 uin			目标QQ
 * @param	bool	 newStatus		true/设置 false/取消
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupAdmini(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwGroup,		// 所在群
	INT64 uin,			// 目标QQ
	bool newStatus		// 要设置的新状态
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，群：" + to_string(dwGroup) \
			+ "，" + (newStatus ? "设置" : "取消") + "管理员：" + to_string(uin)
		);
	return QY_setGroupAdmini(QYAPI::authCode, robotID, dwGroup, uin, int(newStatus));
}

/*
 * 设置群成员名片
 * 需要管理员权限
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT64	 QQUin			目标QQ
 * @param	string	 newCard		新名片
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupMemberCard(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwGroup,		// 所在群
	INT64 uin,			// 目标QQ
	string newCard		// 新名片
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，所在群：" + to_string(dwGroup) \
			+ "，目标QQ：" + to_string(uin) \
			+ "，" + (newCard.length() ? ("新名片：" + newCard) : "删除名片")
		);
	return QY_setModifyGroupMemberCard(QYAPI::authCode, robotID, dwGroup, uin, newCard.c_str());
}

/*
 * 设置群成员专属头衔
 * 需要群主权限
 * 目前仅安卓QQ协议支持
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		所在群
 * @param	INT64	 uin			目标QQ
 * @param	CSTRING	 specialTitle	头衔，如需删除，请填空文本
 * @param	INT32	 ExpireTime		有效期，单位为秒。如果永久有效，请填-1
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupSpecialTitle(
	INT64 robotID,			// 使用的机器人QQ
	INT64 dwGroup,			// 所在群
	INT64 uin,				// 目标QQ
	string specialTitle,	// 头衔
	INT32 expireTime		// 有效期
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，所在群：" + to_string(dwGroup) \
			+ "，目标QQ：" + to_string(uin) \
			+ "，" + (specialTitle.length() ? ("设置新头衔：" + specialTitle + "，有效时间：" + (expireTime == -1 ? "永久" : (to_string(expireTime) + "秒"))) : "删除头衔")
		);
	return QY_setGroupSpecialTitle(QYAPI::authCode, robotID, dwGroup, uin, specialTitle.c_str(), expireTime);
}

/*
 * 置群退出
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwGroup		目标群
 * @param	bool	 Disband		是否解散群，true/解散 false/退出
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setGroupExit(
	INT64 robotID,	// 使用的机器人QQ
	INT64 dwGroup,	// 目标群
	bool disband	// 是否解散群
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，" + (disband ? "解散" : "退出") + "群：" + to_string(dwGroup)
		);
	return QY_setExitGroupChat(QYAPI::authCode, robotID, dwGroup, int(disband));
}

/*
 * 置讨论组退出
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwDiscuss		目标讨论组
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setDiscussExit(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwDiscuss		// 目标讨论组
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，退出讨论组：" + to_string(dwDiscuss)
		);
	return QY_setExitDiscussChat(QYAPI::authCode, robotID, dwDiscuss);
}

/*
 * 置讨论组成员移除
 * 需要创建者权限
 * @param	INT64	 robotID		使用的机器人QQ
 * @param	INT64	 dwDiscuss		所在讨论组
 * @param	INT64	 uin			目标QQ
 * @return	INT32	 unknown		(推测)状态码
 */
INT32 QYAPI::setDiscussMembersKick(
	INT64 robotID,		// 使用的机器人QQ
	INT64 dwDiscuss,	// 目标讨论组
	INT64 uin			// 目标QQ
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，从讨论组：" + to_string(dwDiscuss) \
			+ "中踢出成员：" + to_string(uin)
		);
	return QY_setDiscussMembersKick(QYAPI::authCode, robotID, dwDiscuss, uin);
}

/*
 * 置添加群
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	INT64	 dwGroup			目标群
 * @param	string	 additionalMsg		附加信息
 * @return	INT32	 unknown			(推测)状态码
 */
INT32 QYAPI::setGroupAdd(
	INT64 robotID,			// 使用的机器人QQ
	INT64 dwGroup,			// 目标群
	string additionalMsg	// 附加信息
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，向群：" + to_string(dwGroup)  + "发出加群申请"\
			+ "，附加信息：" + additionalMsg
		);
	return QY_setAddGroup(QYAPI::authCode, robotID, dwGroup, additionalMsg.c_str());
}

/*
 * 置处理群添加请求
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	string	 responseFlag		请求事件收到的「反馈标识」参数
 * @param	INT32	 requestType		请求类型，邀请/REQUEST_GROUP_INVITE 或 加群/REQUEST_GROUP_INVITE
 * @param	INT32	 resultFlag			处理结果，通过/REQUEST_ALLOW 或 拒绝/REQUEST_DENY
 * @param	string	 reason				拒绝理由，仅在 拒绝 时可用
 * @return	INT32	 unknown			(推测)状态码
 */
INT32 QYAPI::setGroupAddRequest(
	INT64 robotID,			// 使用的机器人QQ
	string responseFlag,	// 反馈标识
	INT32 requestType,		// 请求类型
	INT32 resultFlag,		// 处理结果
	string reason			// 拒绝理由
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，反馈标识：" + responseFlag \
			+ "，请求类型：" + to_string(requestType) \
			+ "，处理结果：" + ((resultFlag == REQUEST_ALLOW) ? "通过" : "拒绝") \
			+ ((resultFlag == REQUEST_DENY) ? ("，拒绝理由：" + reason) : "")
		);
	return QY_setGroupAddRequest(QYAPI::authCode, robotID, responseFlag.c_str(), requestType, resultFlag, reason.c_str());
}

/*
 * 置处理好友添加请求
 * @param	INT64	 robotID			使用的机器人QQ
 * @param	string	 responseFlag		请求事件收到的「反馈标识」参数
 * @param	INT32	 resultFlag			处理结果，通过/REQUEST_ALLOW 或 拒绝/REQUEST_DENY
 * @param	string	 remarks			通过时为添加后的好友备注，拒绝时为拒绝理由
 * @return	INT32	 unknown			(推测)状态码
 */
INT32 QYAPI::setFriendAddRequest(
	INT64 robotID,			// 使用的机器人QQ
	string responseFlag,	// 反馈标识
	INT32 resultFlag,		// 处理结果
	string remarks			// 通过时为添加后的好友备注，拒绝时为拒绝理由
)
{
	if(QYAPI_TOLOG)
		QYAPI::addLog::Debug(robotID, __func__,
			"机器人QQ：" + to_string(robotID) \
			+ "，反馈标识：" + responseFlag \
			+ "，处理结果：" + ((resultFlag == REQUEST_ALLOW) ? "通过" : "拒绝") \
			+ "，" + ((resultFlag == REQUEST_ALLOW) ? "备注：" : "拒绝理由：") + remarks
		);
	return QY_setFriendAddRequest(QYAPI::authCode, robotID, responseFlag.c_str(), resultFlag, remarks.c_str());
}

#undef QYAPI_TOLOG