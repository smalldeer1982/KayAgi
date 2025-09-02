# Hellish Constraints

## 题目描述

Katya recently started to invent programming tasks and prepare her own contests. What she does not like is boring and simple constraints. Katya is fed up with all those " $ N $ does not exceed a thousand" and "the sum of $ a_{i} $ does not exceed a million" and she decided to come up with something a little more complicated.

The last problem written by Katya deals with strings. The input is a string of small Latin letters. To make the statement longer and strike terror into the people who will solve the contest, Katya came up with the following set of $ k $ restrictions of the same type (characters in restrictions can be repeated and some restrictions may contradict each other):

- The number of characters $ c_{1} $ in a string is not less than $ l_{1} $ and not more than $ r_{1} $ .
- ...
- The number of characters $ c_{i} $ in a string is not less than $ l_{i} $ and not more than $ r_{i} $ .
- ...
- The number of characters $ c_{k} $ in a string is not less than $ l_{k} $ and not more than $ r_{k} $ .

However, having decided that it is too simple and obvious, Katya added the following condition: a string meets no less than $ L $ and not more than $ R $ constraints from the above given list.

Katya does not like to compose difficult and mean tests, so she just took a big string $ s $ and wants to add to the tests all its substrings that meet the constraints. However, Katya got lost in her conditions and asked you to count the number of substrings of the string $ s $ that meet the conditions (each occurrence of the substring is counted separately).

## 说明/提示

In the first test we should count the number of strings that do not contain characters "e" and "o". All such strings are as follows (in the order of occurrence in the initial string from the left to the right): "c", "d"', "f", "r", "rc", "c", "s".

In the second test we cannot achieve fulfilling exactly one of the two identical constrictions, so the answer is 0.

## 样例 #1

### 输入

```
codeforces
2 0 0
o 1 2
e 1 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
codeforces
2 1 1
o 1 2
o 1 2
```

### 输出

```
0
```

# 题解

## 作者：_Diu_ (赞：2)

[luogu 传送门](https://www.luogu.com.cn/problem/CF138E)

[CF 传送门](https://codeforces.com/contest/138/problem/E)

## 题目大意

对于一个字符串，我们有 $k$ 条限制，第 $i$ 条是要求字符 $c_i$ 出现次数在 $[l_i,r_i]$ 中间。假设这个字符串满足了 $t$ 条限制，那么如果满足 $L\le t\le R$，那么称这个字符串为“好的”。给定一个长度为 $n$ 的字符串，求这个字符串有多少个子串是“好的”。

$1\le n\le 10^5,1\le L\le R\le k\le500$。

## 双指针

乍一看数据范围感觉很恐怖，但是看到了时限，明显知道这一题时间复杂度是需要 $O(nk)$ 的。

原本想的对每个字母单独处理，但是需要乘上常数 $26$，明显不行。

我们应该从每一个限制入手，首先我们把一个限制拆成两个：假设 $s$ 是字符 $c_i$ 的出现次数，如果 $s\ge l_i$，则贡献 $1$，如果 $s\ge r_i+1$，则贡献 $-1$。

这样子对于每个限制就描述成如果某个字符出现次数大于 $x_i$，则贡献 $w_i$。（$w_i\in\{1,-1\}$）

这样子就可以双指针了，对每个限制开一个左指针。我们对每个位置记录一下这个位置被贡献了多少次，每次更改贡献时先把这个位置对答案的贡献减掉，更改完之后再加回去。

大概就是这样：

```cpp
for(int r=1;r<=n;r++){
	f[r]=0;
	if(check(f[r]))++now;//这里后面可能会减掉，所以要先加回去
	for(int j=0;j<k;j++){
		if(c[j]==s[r])++cnt[j];//cnt表示当前这个限制覆盖区间内的字符个数
		while(l[j]<=r&&cnt[j]>=x[j]){//l 表示左端点，x 表示限制
			if(check(f[l[j]]))--now;
			f[l[j]]+=w[j];
			if(c[j]==s[l[j]])--cnt[j];
			if(check(f[l[j]]))++now;
			++l[j];
		}
	}
	ans+=now;
}
```

时间复杂度就是每个限制都扫了一遍 $O(n)$ 的序列，中间的若干操作都是 $O(1)$ 的，所以总时间复杂度是 $O(nk)$，稳过。

难度建议评绿或蓝，CF 上评分 `2900` 感觉有点过了，~~不过是远古 CF 当我没说~~，算是一道比较基础的题吧。

---

