QYBot SDK For C++
---
[![License](https://img.shields.io/github/license/Hstb1230/qybot-sdk.svg)](LICENSE)
[![Q群](https://img.shields.io/badge/Q%20%E7%BE%A4-529483966-orange.svg)](https://jq.qq.com/?_wv=1027&k=5McnWRW)
[![社区](https://img.shields.io/badge/%E7%A4%BE%E5%8C%BA-qyue.cc-blue.svg)](https://qyue.cc)

使用办法
---
1.  Microsoft Visual Studio 2019

    (目前之前使用2017开发, 最近升级到2019, 2017应该也可以成功编译, 因为2019下的类型检查更严格, 

    甚至IDE能根据语句推导出那些是永远不会执行的无效语句, 以至于出现一些莫名奇妙又毫无头绪的警告(最后当然是解决了))
    
2.  打开「项目属性」窗口, 在最上方切换「配置」为「所有配置」, 切换「平台」为「所有平台」,

    将「常规」属性的「输出目录」修改为 **`机器人软件目录下的plugin文件夹的绝对路径`** , 以更快调试插件.
    
3.  使用「生成解决方案」编译插件, 

    请不要使用`x64`平台的解决方案编译, 一方面会出现很多类型检查警告, 
    
    另一方面, 即使不存在警告, 也会因目标机非x64而被当做是错误阻止编译, 并且, QY并不支持x64.

    请注意, **编译前请先卸载插件或关闭QY**, 否则会因为文件被占用导致编译失败.

文本编码
---
本项目默认使用「多字节字符集」, 可改为「未设置」, 也可调成「Unicode字符集」. 

但请不要安装`ForceUTF8(NO BOM)`之类的插件, 或者是在编译命令中添加`/utf-8`选项, 否则会因为QY不支持UTF-8编码, 在回复消息等相关操作时出现乱码情况. 同时, 如果这两步操作只做其中一步, 编译时也会出现很多错误. 

---

经过精心调教, SDK已经很好的支持了ANSI(GB2312), UTF-8与Unicode等常用编码, 您可以在ANSI与Unicode之间自由转换, 

但因为UTF-8与ANSI编码都为`const char *`类型, 无法做到直接识别和自动转换, 所以请使用SDK提供的`nstring`类进行手动转换, 具体使用方法请查阅`event.cpp`下的`test`函数.

如您需要转换ANSI与UTF-8编码, 可自行转换, 也可使用`nstring`类, 但更建议使用QY提供的API`convertAnsiToUtf8`与`convertUtf8ToAnsi`, 一些其他语言的开发者称, 部分文本似乎只能使用该API进行转换.

致歉
---
因学业繁忙, 加上本身比较咸鱼, 暂抽不出时间编写更多详细说明与使用文档, 但demo中已写了绝大部分API的使用样例, 请先自行参考使用. 

如您遇到一些无法解决的问题, 可发在issue, 或加群沟通, 看到后会回复。
