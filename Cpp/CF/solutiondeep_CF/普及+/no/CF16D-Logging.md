# 题目信息

# Logging

## 题目描述

The main server of Gomble company received a log of one top-secret process, the name of which can't be revealed. The log was written in the following format: «\[date:time\]: message», where for each «\[date:time\]» value existed not more than 10 lines. All the files were encoded in a very complicated manner, and only one programmer — Alex — managed to decode them. The code was so complicated that Alex needed four weeks to decode it. Right after the decoding process was finished, all the files were deleted. But after the files deletion, Alex noticed that he saved the recordings in format «\[time\]: message». So, information about the dates was lost. However, as the lines were added into the log in chronological order, it's not difficult to say if the recordings could appear during one day or not. It is possible also to find the minimum amount of days during which the log was written.

So, to make up for his mistake Alex has to find the minimum amount of days covered by the log. Note that Alex doesn't have to find the minimum amount of days between the beginning and the end of the logging, he has to find the minimum amount of dates in which records could be done. (See Sample test 2 for further clarifications).

We should remind you that the process made not more than 10 recordings in a minute. Consider that a midnight belongs to coming day.

## 说明/提示

Formally the 12-hour time format is described at:

- http://en.wikipedia.org/wiki/12-hour\_clock.

 The problem authors recommend you to look through these descriptions before you start with the problem.

## 样例 #1

### 输入

```
5
[05:00 a.m.]: Server is started
[05:00 a.m.]: Rescan initialized
[01:13 p.m.]: Request processed
[01:10 p.m.]: Request processed
[11:40 p.m.]: Rescan completed
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
[09:00 a.m.]: User logged in
[08:00 a.m.]: User logged in
[07:00 a.m.]: User logged in
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 日志记录

## 题目描述
Gomble公司的主服务器收到了一个绝密进程的日志，该进程的名称暂不能透露。日志采用以下格式书写：「[日期:时间]: 消息」，对于每个「[日期:时间]」值，对应的行数不超过10行。所有文件都以一种非常复杂的方式进行了编码，只有一位程序员——Alex——成功解码。编码非常复杂，Alex花了四周时间才完成解码。解码过程一结束，所有文件就被删除了。但在文件删除后，Alex注意到他将记录保存为「[时间]: 消息」的格式。因此，日期信息丢失了。然而，由于日志中的行是按时间顺序添加的，所以判断这些记录是否可能在一天内出现并不困难。也有可能找出记录日志所花费的最少天数。

所以，为了弥补他的错误，Alex必须找出日志所涵盖的最少天数。请注意，Alex不必找出日志开始和结束之间的最少天数，他必须找出可能进行记录的最少日期数。（有关更多说明，请参阅示例测试2）。

我们提醒你，该进程每分钟的记录不超过10条。请考虑午夜属于新的一天。

## 说明/提示
正式的12小时时间格式描述如下：
- http://en.wikipedia.org/wiki/12-hour_clock 。
问题作者建议你在开始解决问题之前查看这些描述。

## 样例 #1
### 输入
```
5
[05:00 a.m.]: Server is started
[05:00 a.m.]: Rescan initialized
[01:13 p.m.]: Request processed
[01:10 p.m.]: Request processed
[11:40 p.m.]: Rescan completed
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3
[09:00 a.m.]: User logged in
[08:00 a.m.]: User logged in
[07:00 a.m.]: User logged in
```
### 输出
```
3
```

### 算法分类
模拟

### 题解综合分析与结论
所有题解思路核心均为模拟，需将12小时制时间转换为24小时制，对比相邻时间判断是否跨天，同时利用计数器处理一分钟内记录不超10条的限制。各题解在实现细节上存在差异，如读入方式、时间转换方法、计数器处理等。部分题解代码可读性欠佳，部分题解在处理细节上存在遗漏或不够简洁。整体题解质量不高，无4星及以上题解。

### 通用建议与扩展思路
- **读入优化**：可利用`scanf`的特性，精准读入时间相关信息，减少字符串处理工作量。
- **逻辑简化**：在判断跨天和计数器处理逻辑上，应尽量简洁明了，增强代码可读性。
- **细节处理**：对时间转换边界情况，如12:00 p.m.等，要谨慎处理。

同类型题通常围绕时间处理、条件判断和模拟实际场景展开。可关注时间格式转换、事件按时间顺序模拟等方面的题目。

### 相似知识点洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及枚举和简单的数学计算，与本题在逻辑判断和计数方面有相似思路。
- [P1046 陶陶摘苹果（升级版）](https://www.luogu.com.cn/problem/P1046)：通过模拟实际场景，根据给定条件进行判断和计算，与本题模拟思路类似。
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：通过模拟开关灯的过程，依据特定规则进行状态改变和统计，锻炼模拟能力。 

---
处理用时：36.62秒