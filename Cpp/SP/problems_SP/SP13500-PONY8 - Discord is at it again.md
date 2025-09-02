---
title: "PONY8 - Discord is at it again"
layout: "post"
diff: 难度0
pid: SP13500
tag: []
---

# PONY8 - Discord is at it again

## 题目描述

Celestia 公主决定释放 Discord 并尝试改造他。然而，Discord 并不愿意被改造。当他逃出来时，悄悄毁掉了 Twilight Sparkle 所有关于改造魔法的书籍。不过，信息依然存在，只是被他的混沌魔法封印了起来。

Discord 的混沌魔法生成了一种被称为「Mega String」的字符串。要创建这个字符串，就从依次写下自然数 1, 2, 3, ... 开始，而且各数字之间不加任何空格。

结果看起来就像这样：12345678910111213141516...

然而，在生成过程中，他对数字 5 感到厌恶。

因此，任何包含数字 5 的数都会被排除在 Mega String 之外。

所以真正的 Mega String 如下所示：

1234678910111213141617...

再往后是：

...47, 48, 49, ...

...474849606162...

Twilight Sparkle 想知道，在 Mega String 中第 $K$ 个��置上的数字是什么？请迅速找到答案，否则隐藏在 Mega String 中的信息将永远消失。

Mega String 采用零索引计数。

## 输入格式

输入一个整数 $K$，表示要查询的位置。

## 输出格式

输出一个字符，表示 Mega String 中第 $K$ 个位置上的数字。

## 说明/提示

保证 $0 \le K < 10^{18}$。

 **本翻译由 AI 自动生成**

