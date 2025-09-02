# 题目信息

# Something Comforting

## 题目背景

![Something Comforting](https://mivik.gitee.io/image/nurture/something_comforting.png)

> Cause getting made you want more
>
> And hoping made you hurt more
>
> Someone tell me
>
> Something comforting

## 题目描述

Porter Robinson 花了五年的时间制作了 Something Comforting 这首歌，Mivik 花了五天时间造出了一道和括号序列相关的题。但 Mivik 并不开心，因为他发现他不会造数据了！

Mivik 需要随机生成一个 **合法** 的括号序列，于是 Mivik 想了一会，写出了下面的算法：

```cpp
#include <algorithm>
#include <string>

std::string generate(int n) { // 生成一个长度为 n * 2 的括号序列
	const int len = n * 2;
	bool arr[len]; // 0 代表左括号，1 代表右括号
	for (int i = 0; i < n; ++i) arr[i] = 0;
	for (int i = n; i < len; ++i) arr[i] = 1;
	std::random_shuffle(arr, arr + len); // 随机打乱这个数组
	for (int i = 0, j, sum = 0; i < len; ) {
		sum += arr[i]? -1: 1;
		if (sum < 0) { // 出现了不合法的位置
			for (j = i + 1; j < len; ++j) {
				sum += arr[j]? -1: 1;
				if (sum == 0) break;
			}
			// 现在 i 是第一个不合法的位置，j 是 i 后面第一个合法的位置
			// ( ( ) ) ) ) ( ( ( ) ( )
			//         i     j
			for (int k = i; k <= j; ++k)
				arr[k] ^= 1; // 把这段区间全部反转
			i = j + 1;
		} else ++i;
	}
	std::string ret;
	for (int i = 0; i < len; ++i)
		ret += arr[i]? ')': '(';
	return ret;
}
```

P.S. 为了给其它语言用户带来做题体验，[这里](https://www.luogu.com.cn/paste/wof8zjn8) 提供了多种语言对该算法的描述。

Mivik 十分开心，因为这个算法总能生成合法的括号序列。但不一会儿他就发现这个算法生成的括号序列并不均匀，也就是说，当 $n$ 固定时，所有合法的括号序列出现的概率并不均等。例如，Mivik 发现当 $n=3$ 时，`()()()` 被生成的概率要远大于 `((()))`。

现在 Mivik 给了你一个 $n$ 和一个长度为 $2n$ 的 **合法** 括号序列，假设 `std::random_shuffle` （对于其它语言来说，`shuffle`）能够均匀随机地打乱一个数组，他想问问你这个括号序列通过上文的算法被生成的概率是多少。由于 Mivik 不喜欢小数，你需要输出这个概率对 $998244353$ 取模的结果。如果你不知道如何将一个有理数对质数取模，可以参考 [有理数取模](https://www.luogu.com.cn/problem/P2613)。

## 说明/提示


### 样例解释

样例一：$n$ 为 1 时，无论怎样都只可能会生成 `()` 这一种合法的括号序列，因此概率为 1。

### 数据范围

对于全部数据，有 $1\le n\le 5\cdot 10^5$，且输入的括号序列合法。

Subtask 1（20 pts）：保证 $1\le n\le 5$。

Subtask 2（30 pts）：保证 $1\le n\le 1000$。

Subtask 3（50 pts）：无特殊限制。


## 样例 #1

### 输入

```
1
()```

### 输出

```
1```

## 样例 #2

### 输入

```
3
()(())```

### 输出

```
598946612```

# AI分析结果



### 综合分析与结论

本题核心在于分析生成算法对合法括号序列的分段影响，关键在于统计遍历过程中括号序列的`sum`归零次数。正确公式为概率等于 $2^{k} / C(2n, n)$，其中 $k$ 是遍历过程中`sum`归零的次数（不包括初始点）。各题解的核心思路一致，实现简洁，主要区别在于数学模型的描述方式。

---

### 精选题解

#### 1. 作者：Lonely_NewYear （4星）
**关键亮点**：分步骤讲解清晰，代码可读性强，直接统计`sum`归零次数，组合数计算高效。
**代码核心**：
```cpp
// 统计sum归零次数
for(int i=1;i<=2*n;i++){
    if(s[i]=='(') sum++;
    else sum--;
    if(sum==0) ans=ans*2%mod;
}
// 计算组合数逆元
for(int i=n+1;i<=2*n;i++) num=num*i%mod;
for(int i=1;i<=n;i++) num=num*ksm(i,mod-2)%mod;
printf("%lld",ans*ksm(num,mod-2)%mod);
```

#### 2. 作者：vectorwyx （4星）
**关键亮点**：代码简洁高效，直接遍历字符串并维护`sum`，快速幂优化逆元计算。
**核心代码**：
```cpp
int sum=0,cnt=0;
for(int i=0;i<2*n;i++){	
    sum += (s[i]=='('?1:-1);
    if(sum==0) cnt++;
}
// 组合数计算
int numerator=1, denominator=1;
for(int i=1;i<=n;i++) denominator=denominator*i%mod;
for(int i=n+1;i<=2*n;i++) numerator=numerator*i%mod;
int comb = numerator * pow(denominator, MOD-2) % MOD;
cout << pow(2, cnt) * pow(comb, MOD-2) % MOD;
```

#### 3. 作者：Mivik （4星）
**关键亮点**：数学模型严谨，结合行走轨迹解释分段原理，深化理解。
**核心思路**：合法序列的轨迹与X轴相交次数 $m$，对应 $2^{m-1}$ 种初始序列，最终概率为 $2^{m-1}/C(2n,n)$。

---

### 最优思路总结
1. **分段统计**：遍历合法括号序列，统计`sum`归零次数 $k$，每个归零点对应一个独立段。
2. **组合数计算**：总方案数为 $C(2n, n)$，需预处理阶乘并求逆元。
3. **快速幂优化**：利用费马小定理计算逆元，提升效率。

---

### 拓展与举一反三
- **同类问题**：类似分段计数问题可转化为独立事件组合（如路径翻转、区间覆盖）。
- **推荐题目**：
  1. [P2613 【模板】有理数取模](https://www.luogu.com.cn/problem/P2613)
  2. [P1641 [SCOI2010]生成字符串](https://www.luogu.com.cn/problem/P1641)
  3. [P1754 球迷购票问题](https://www.luogu.com.cn/problem/P1754)

---

### 心得摘录
- **调试经验**：需注意`sum`归零次数是否包含初始点，否则会导致公式错误。
- **关键顿悟**：合法括号序列的每个独立段对应两种初始状态，翻转不影响总括号数。

---
处理用时：117.75秒