#pragma once

class QYTYPE
{
	public:

	typedef struct {
		INT64	uin;	// QQ号
		string	nick;	// 昵称
	} Friend; // 好友信息
	typedef std::vector<Friend> FriendList; // 好友列表

	typedef struct {
		INT64	tempID;		// 临时群号
		INT64	id;			// 群号
		string	name;		// 群名
	} Group; // 群信息
	typedef std::vector<Group> GroupList; // 群列表

	typedef struct {
		INT64	id;					// 讨论组ID
		string	name;				// 讨论组名称(GB2312编码)
		BYTES	nameBuffer;			// 讨论组名称(Utf-8编码)
		INT32	createTimeStamp;	// 创建时间戳
		INT64	createUin;			// 创建者
		INT32	infoSeq;			// 信息序列
		INT32	lastInfoTimeStamp;	// 最后信息时间戳
		INT32	msgSeq;				// 消息序列
		INT32	lastMsgTimeStamp;	// 最后消息时间戳
		INT32	memberNum;			// 成员数量
		INT32	flag;				// 未知
		INT64	inheritOwnerUin;	// 继承创建者
		INT64	groupID;			// 群号
		INT64	groupTempID;		// 临时群号
		INT32	confMeetingOrigin;	// 未知
		INT32	qidianConfType;		// 未知
		INT32	confMeetingOption;	// 未知
	} Discuss; // 讨论组信息
	typedef std::vector<Discuss> DiscussList; // 讨论组列表

	typedef struct {
		INT64	uin;					// QQ号
		string	nick;					// 昵称
		string	card;					// 名片
		INT32	sex;					// 性别，0/男 1/女 255/未知
		INT32	age;					// 年龄
		string	area;					// 地区
		INT32	joinTimeStamp;			// 加群时间(时间戳)
		INT32	lastSpeakTimeStamp;		// 最后发言时间(时间戳)
		string	gLevelName;				// 所处群等级名称
		INT32	permission;				// 管理权限，1/成员 2/管理员 3/群主
		string	sTitle;					// 专属头衔
		INT32	sTitleValidPeriod;		// 专属头衔有效期
		bool	isBadMember;			// 是否为不良成员
		bool	allowChangeCard;		// 允许修改名片
	} GroupMember; // 群成员信息
	typedef std::vector<GroupMember> GroupMemberList; // 群成员列表

	typedef struct {
		INT64	id;						// 群号
		INT64	ownerUin;				// 群主QQ
		INT32	createTimeStamp;		// 创建时间(时间戳)
		INT32	memberNum;				// 群目前人数
		INT32	maxMemberNum;			// 群人数上限
		string	name;					// 群名称(GB2312编码)
		BYTES	nameBuffer;				// 群名称(UTF-8编码)
		INT32	level;					// 群等级，所有群都可以获取到，但是有条件是否显示，有些群不满足条件有等级也不显示
		string	introduction;			// 群介绍(GB2312编码)
		BYTES	introductionBuffer;		// 群介绍(UTF-8编码)
	} GroupInfo; // 群资料

	typedef struct {
		INT64	uin;				// QQ号
		INT32	permission;		// 权限，0/群主 1/管理员
	} GroupAdmin; // 群管理
	typedef std::vector<GroupAdmin> GroupAdminList; // 群管理列表

	typedef struct {
		INT64	uin;			// QQ号
		INT32	sex;			// 性别，0/男 1/女 2/未知
		string	nick;			// 昵称
		string	signature;		// 签名
		string	birthday;		// 生日，格式例：1990/12/12
		INT32	age;			// 年龄，-1为未知
		INT32	level;			// QQ等级
		INT32	qAge;			// Q龄，仅PCQQ协议支持 -1/255 表示查询失败
		INT32	likeCount;		// 赞数量
		INT32	isLike;			// 是否可赞，0/已赞 1/未赞，仅安卓QQ协议支持
	} QQSummaryInfo; // QQ简要资料

	typedef struct {
		BYTES	token;				// 匿名用户Token
		string	card;				// 匿名用户名片 如“大力鬼王”
		INT64	headMark;			// 匿名用户的头像标识
		INT64	expireTimeStamp;	// 匿名用户到期时间戳
	} Anonymous; // 匿名信息

	typedef struct {
		string	nick;		// 昵称		有昵称表示没有群昵称	Nick和GCard不能共存
		string	gCard;		// 群昵称	有群昵称表示没有昵称	Nick和GCard不能共存
		INT32	level;		// 群个人等级
		INT32	flags;		// 未知
		INT32	gLevel;		// 群等级
		string	sTitle;		// 群头衔
		INT32	MTID;		// 未知
	} GroupAdditionalInfo; // 附加信息

	typedef struct {
		string	name;			// 名称
		INT32	size;			// 字号
		INT32	color;			// 颜色
		INT32	effect;			// 样式 1/粗体 2/斜体 4/下划线
		INT32	colorTextID;	// 气泡ID
	} Font; // 字体信息

	typedef struct {
		string	name;		// 文件名
		string	id;			// 文件ID
		string	size;		// 文件大小
		INT64	busID;		// 反正就这名字
		INT64	byteSize;	// 文件大小，单位：字节
	} File; // 文件信息

	typedef struct {
		INT64 id;			// QQ号
		INT32 state = 0;	// 在线状态，0/离线 1/在线
	} LoginQQ;
	typedef std::vector<LoginQQ> LoginQQList; // 登录QQ列表

};