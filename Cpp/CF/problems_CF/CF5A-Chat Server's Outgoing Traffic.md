---
title: "Chat Server's Outgoing Traffic"
layout: "post"
diff: 入门
pid: CF5A
tag: ['模拟', '字符串']
---

# Chat Server's Outgoing Traffic

## 题目描述

Polycarp正在开发一个名为“Polychat”的新项目。按照IT的现代倾向，他决定，这个项目也应该包含聊天。为了实现这一目标，Polycarp在笔记本电脑前花费了几个小时，实现了一个可以处理三种命令的聊天服务器：

将一个人加入聊天（“添加”命令）。

从聊天中删除一个人（“删除”命令）。

向所有正在聊天的人发送消息，包括发送消息的人（“发送”命令）。

现在，Polycarp希望了解处理特定命令集时服务器将产生的传出流量。

Polycarp知道聊天服务器不会为“添加”和“删除”命令发送流量。当处理“发送”命令时，服务器向聊天的每个参与者(当前在线的人)发送l个字节，其中l是消息的长度。

由于Polycarp没有时间，他在寻求帮助来解决这个问题。

## 输入格式

输入文件将包含不超过100个命令，每个命令都在自己的行中。每行不超过100个字符。命令的格式如下：

+<名称>为“添加”命令。
-<名称>为“删除”命令。
<SENDER_NAME>：<MESSAGE_TEXT>为'发送'命令。

<name>(名字)和<sender_name>是拉丁字母和数字的非空序列。<message_text>可以包含字母，数字和空格，但不能以空格开始或结束<message_text>是一个空行。

保证输入数据是正确的，即不会有“添加”命令，如果人用这样的名字已经在聊天，不会有“删除”命令，如果没有人跟在这样的名字聊天等

所有的名字都是区分大小写的。

## 输出格式

输出流量

Translated by @liyifeng

## 样例 #1

### 输入

```
+Mike
Mike:hello
+Kate
+Dmitry
-Dmitry
Kate:hi
-Kate

```

### 输出

```
9

```

## 样例 #2

### 输入

```
+Mike
-Mike
+Mike
Mike:Hi   I am here
-Mike
+Kate
-Kate

```

### 输出

```
14

```

