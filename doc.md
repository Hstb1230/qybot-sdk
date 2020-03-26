# 契约开发者文档

##### By [S·c]( https://github.com/ScSofts )

<font color="red">Warning:本文档仅供测试！本文档以C++为范例，其它语言类似</font>

### 目录

<a href="#setup">安装框架和SDK</a>

<a href="#example">第一个程序Hello World</a>

### 正文

- ###  <a id="setup">安装框架和SDK</a>

  ####  准备工具
  1. Microsoft Visual Studio 2017 或 2019 (必须安装C++桌面开发功能)
  
  2. 契约机器人框架  到[官网]( https://qybot.net/ )下载
  
  3. C++ SDK（同2）
  
  #### 编译Demo
  
  1. 解压SDK
  
  2. 进入目录C++_SDK(20190325)
  
  3. 双击QYDemo.sln
  
  4. 工程配置改Release x86
  
  5. 生成解决方案，如果出现错误，请按照流程重试，没问题则继续
  
     <font color="red">Warning:Demo请妥善保管！</font>

- ### <a id="example">第一个程序 Hello World</a>

  #### 建立工程

 1. 复制Demo到其它位置

 2. 修改工程名称

 3. 修改`info.json` 参考如下 
```javascript
     {
       "ret": 1, // 返回码，固定为1
       "apiver": 2018, // Api版本，本SDK为2018
       "appid": "com.test.helloworld", // 其中 appid 需与文件名(不含后缀)一致, 如appid=com.demo.cpp, 则文件名为com.demo.cpp.qyk(或.qyk.dll)
       "name": "第一个插件Hello World", // 应用名称
       "version": "1.0.0", // 应用版本
       "version_id": 1, // 应用顺序版本（每次发布时至少+1）
       "author": "S·c", // 应用作者
       "description": "我的第一个插件", // 应用说明，需要换行请使用\r\n
       "event": [ 
         // 事件列表（发布前请删除无用事件）
     {
       "id": 1,
       "type": 166,
       "name": "私聊消息处理",
       "function": "QY_Event_PrivateMsg",//这个函数和C++里面的函数对应！
       "priority": 30000//优先级
     }
       ],
       "menu": [
         // 设置菜单（发布前请删除无用菜单，如果无需设置菜单请全部删除）
       ],
       "auth": [
         // 应用权限（发布前请删除无用权限）
         // 注意逗号
         101, // 发送好友消息          sendFriendMsg
        ]
     }
```

  4. 修改`event.cpp`

```c++
  #include "stdafx.h"
  #ifndef QYEVENT
  #define QYEVENT(TYPE) extern "C" __declspec(dllexport) TYPE __stdcall 
  #endif
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
 * [166]私聊消息
 * 本子程序会在【线程】中被调用，请注意使用对象等需要初始化(CoInitialize,CoUninitialize)。
 */
QYEVENT(INT32) QY_Event_PrivateMsg(
	INT64		robotID,		// 机器人QQ，用于区分多号登录
	INT32		subType,		// 子类型，11/来自好友 1/来自在线状态 2/来自群 3/来自讨论组 4/来自公众号
	INT64		sendTime,		// 发送时间(13位时间戳)
	INT64		fromQQ,			// 来源对象
	INT64		fromGroup,		// 来源群组(仅子类型为2/3时使用)
	CSTRING		fromInfo,		// 来源者信息
	CSTRING		msg,			// 消息内容
	CSTRING		info,			// 信息
	INT32		intTest			// 用于测试(我也不知道机器人作者想干嘛
)
{
	string Message(msg);//转化消息
    /*
    为啥要转化？
    msg的类型是cosnt char *，如果直接判断 msg == "xxx"，实际上是在比较msg和"xxx"在内存中的位置，所以恒为false。转化成了string类型，就能正常比较啦！
    */
    if(Message=="test"){
       QY::sendFriendMsg(robotID, fromQQ, string("Test OK!"));//调用API
    }
	
	// 如果要回复消息，请调用API发送，并且这里 return QY::EVENT_BLOCK - 截断本条消息，不再继续处理
	// 注意：应用优先级设置为"最高"(10000)时，不得使用本返回值
	// 如果不回复消息，交由之后的应用/过滤器处理，这里 return QY::EVENT_IGNORE - 忽略本条消息
	return QY::EVENT_IGNORE;
}
#undef QYEVENT
```

5. 编译工程
6. 将生成的DLL放置到契约的Plugin目录
7. 登录契约，并在任务栏托盘找到契约机器人图标，右击，选择应用
8. 载入插件并启用
9. 用另一个QQ号给机器人私聊发送`test` 若自动回复了`Test OK!` 即为正常，否则按照步骤重试或提交issue



### 更多用法，参考[API文档](api.md)
