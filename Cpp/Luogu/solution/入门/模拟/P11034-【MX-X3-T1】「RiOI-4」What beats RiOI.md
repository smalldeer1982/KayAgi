# 【MX-X3-T1】「RiOI-4」What beats RiOI

## 题目背景

原题链接：<https://oier.team/problems/X3B>。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/tb8chlhk.png)

但是众所周知 RiOI 是从 KDOI 里面裂出来的，所以这个只是整活……（小声）  
KDOI 对不起喵！

## 题目描述

定义一个字符串是**好闪**的，当且仅当这个字符串包含子串 `RiOI`（大小写均可，例如含有 `rioi`，`RIOI`，`rIoI` 均算作含有）。

给定两个只包含大小写英文字母的非空字符串 $s,t$：

- 如果两个字符串都是好闪的，那么输出 `Either is ok!`。
- 否则，如果 $s$ 是好闪的，输出 $s$ `for sure!`。
- 否则，如果 $t$ 是好闪的，输出 $t$ `for sure!`。
- 如果两个字符串都不是好闪的，请输出 `Try again!`。

## 说明/提示

**【样例解释 #1】**

`RiOI` 含有 `RiOI` 子串，而 `KDOI` 不含，所以输出 `RiOI for sure!`。

**【样例解释 #2】**

`RiOIroundfour` 和 `RiOIroundnegtiveone` 都含有 `RiOI` 子串，所以输出 `Either is ok!`。

**【样例解释 #4】**

`GoInForIOI` 含有 `rIOI` 子串，而 `GoInForNOI` 不含有，所以输出 `GoInForIOI for sure!`。

**【数据范围】**

对于 $50\%$ 的数据，保证 $s,t$ 只包含小写英文字母。  
对于 $100\%$ 的数据，保证 $s,t$ 的长度都不超过 $1\ 000$，且均为仅由大小写英文字母组成的非空字符串。

## 样例 #1

### 输入

```
RiOI
KDOI```

### 输出

```
RiOI for sure!```

## 样例 #2

### 输入

```
RiOIroundfour
RiOIroundnegtiveone```

### 输出

```
Either is ok!```

## 样例 #3

### 输入

```
majsoul
digdigio```

### 输出

```
Try again!```

## 样例 #4

### 输入

```
GoInForNOI
GoInForIOI```

### 输出

```
GoInForIOI for sure!```

