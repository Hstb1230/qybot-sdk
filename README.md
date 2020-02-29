QYBot SDK For C++
---
[![License](https://img.shields.io/github/license/Hstb1230/qybot-sdk.svg)](LICENSE)
[![Q群](https://img.shields.io/badge/Q%20%E7%BE%A4-529483966-orange.svg)](https://jq.qq.com/?_wv=1027&k=5McnWRW)
[![社区](https://img.shields.io/badge/%E7%A4%BE%E5%8C%BA-qyue.cc-blue.svg)](https://qyue.cc)

使用办法
---
1.  Microsoft Visual Studio 2017

    (不清楚2019对旧项目的兼容性如何, 据部分开发者反馈存在编译问题, 待测试)
    
2.  打开「项目属性」窗口, 在最上方切换「配置」为「所有配置」, 切换「平台」为「所有平台」,

    将「常规」属性的「输出目录」修改为 **`机器人软件目录下的plugin文件夹的绝对路径`** , 以更快调试插件.
    
3.  使用「生成解决方案」编译插件.

    请注意, **编译前请卸载插件或退出机器人软件**, 否则会因为文件被占用而编译失败.

说明
---
本项目默认使用「多字节字符集」, 可改为「未设置」, 也可调成「Unicode字符集」, 不过目前还没在函数上做好兼容, 仍以GB2312编码为主, 所以不要强行传入wstring相关类型的参数(传了编译也不会让你过的.jpg). 

但请不要安装`ForceUTF8(NO BOM)`之类的插件, 或者是在编译命令中添加`/utf-8`选项, 否则会因为机器人软件不支持UTF-8编码, 而在回复消息等操作时会出现乱码情况.

致歉
---
因学业繁忙, 加上本身比较咸鱼, 暂抽不出时间编写详细说明, 如有疑问可发在issue, 或加群沟通, 看到后会回复。
