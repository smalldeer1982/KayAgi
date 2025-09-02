# [GXOI/GZOI2019] 宝牌一大堆

## 题目描述

麻将是一种传统的博弈游戏，由 $4$ 名玩家参与，轮流摸牌、打牌。在竞技比赛中主要有国标麻将（中国）和立直麻将（日本）两大规则。本题采用一种特别的规则——「宝牌一大堆」规则。

#### 牌型
一副麻将由 $136$ 张牌组成，其中包含 $34$ 种不同的牌，每种各有 $4$ 张。这 $34$ 种牌分别是：  
一万到九万、一索到九索、一筒到九筒、东、南、西、北、中、白、发。

![doraippai1.png](https://cdn.luogu.com.cn/upload/pic/56677.png)

它们可以组合成不同的牌型：
- 顺子：$3$ 张数字连续的万，或 $3$ 张数字连续的索，或 $3$ 张数字连续的筒。
- 刻子：$3$ 张完全一样的牌。
- 杠子：$4$ 张完全一样的牌。
- 雀头：$2$ 张完全一样的牌。

其中顺子和刻子统称为面子。

#### 和牌
手牌（一名玩家持有的牌）宣告胜利的状况称为「和牌」。
- 当玩家持有 $14$ 张牌，并且满足以下三个条件之一时，判定为「和牌」：
  1. 存在一种方案，使得这 $14$ 张牌可以分成 $4$ 组面子、$1$ 组雀头，简记为「$3 \times 4 + 2$」。
  2. 存在一种方案，使得这 $14$ 张牌可以分成 $7$ 组**不同的**雀头，称为「七对子」。
  3. 这 $14$ 张牌**仅由**一万、九万、一索、九索、一筒、九筒、东、南、西、北、中、白、发这 $13$ 种牌组成，并且这 $13$ 种牌**每种至少有 $1$ 张**，称为「国士无双」。
- 当玩家持有 $15$ 张牌，并且存在一种方案，使得这 $15$ 张牌可以分成 $1$ 组杠子、$3$ 组面子、$1$ 组雀头，判定为和牌。
- 当玩家持有 $16$ 张牌，并且存在一种方案，使得这 $16$ 张牌可以分成 $2$ 组杠子、$2$ 组面子、$1$ 组雀头，判定为和牌。
- 当玩家持有 $17$ 张牌，并且存在一种方案，使得这 $17$ 张牌可以分成 $3$ 组杠子、$1$ 组面子、$1$ 组雀头，判定为和牌。
- 当玩家持有 $18$ 张牌，并且存在一种方案，使得这 $18$ 张牌可以分成 $4$ 组杠子、$1$ 组雀头，判定为和牌。

#### 宝牌
每局游戏还会指定若干张「宝牌」，和牌时，手牌中的每张宝牌会使收益翻一番（会在接下来详细介绍）。

#### 达成分数
由于可以「和牌」的手牌很多，可以给每种判定为「和牌」的手牌定义一个「达成分数」，这个分数等于从所有尚未打出的牌中选出若干张，能够组成该手牌的方法数，再乘上手牌中 $2$ 的「宝牌数」次方。  
该分数综合考虑了和牌几率与和牌收益，理论上以分数较高的手牌为目标较好。

例如下图手牌显然是可以「和牌」的，如果目前场上还剩 $3$ 张一万、$4$ 张九万，以及二到八万各 $2$ 张没有打出，宝牌为九万，那么下图手牌的「达成分数」就是 $C_3^3 C_4^3 C_2^2 (C_2^1)^6 2^3 = 2048$，其中 $C$ 表示组合数。

![doraippai2.png](https://cdn.luogu.com.cn/upload/pic/56678.png)

特别地，「七对子」和牌的手牌，达成分数额外乘 $7$。「国士无双」和牌的手牌，达成分数额外乘 $13$。

有一天，小 L，小 Y，小 I 和小 W 正在打麻将，路过的雪野和看到了所有已经打出的牌，但不知道任何一名玩家的手牌。也许你已经猜到了下面的剧情—
—雪野和想知道在所有尚未打出的牌中，「达成分数」最高的可以「和牌」的手牌有多少分，但是她还要观看麻将比赛，所以这个问题就交给你了。

## 说明/提示

### 样例解释

在第一组数据中，没有打出过任何牌，没有宝牌，和「国士无双」分数最高，为 $13 \times 6 \times 4^{12}$。  
和「$3 \times 4 + 2$」和「七对子」的分数为 $100663296$ 和 $1959552$。

在第二组数据中，和「$3 \times 4 + 2$」分数最高，为 $127401984$，可以得到该分数的手牌之一为「$\texttt{1m2m3m 7m8m9m 1p2p3p 3p4p5p SS}$」。  
和「七对子」的分数为 $125411328$，不存在和「国士无双」的可能。

### 数据范围

保证已经打出的牌必定是合法的牌，且每种不超过 $4$ 张。宝牌不会重复给出。

|测试点编号|$T$ 的规模|已经打出的牌|宝牌数|
|:-:|:-:|:-:|:-:|
|$1$|$T = 10$|无特殊限制|$\le 20$ 张|
|$2$|$T = 100$|至少包括所有数字为三到七的牌|$\le 20$ 张|
|$3$|$T = 500$|每种至少 $2$ 张|$\le 20$ 张|
|$4$|$T = 500$|每种至少 $3$ 张|$\le 20$ 张|
|$5$|$T = 500$|无特殊限制|$0$ 张|
|$6$|$T = 1,000$|无特殊限制|$0$ 张|
|$7$|$T = 1,000$|无特殊限制|$\le 20$ 张|
|$8$|$T = 1,500$|无特殊限制|$\le 20$ 张|
|$9$|$T = 2,000$|无特殊限制|$\le 20$ 张|
|$10$|$T = 2,500$|无特殊限制|$\le 20$ 张|

## 样例 #1

### 输入

```
2
0
0
7m 4p 2s 7s 6p 8s 7p 5s 9s 9s 1p 5m 9m 5s 4p 5s E 1p 6s 5p B 4m 6m W 6p 6s E 9s 5p 2s 8s 8p 4m 3s 9m 5p 3s 2s 6s 8s 8p 6p 5m 4s 3m 4s 5s 4s 6m 9s 6p N 5m 7s 4m 2m 2s 6s 3m 7p B B N 1m 3m B 8p F 7p 0
W 4p N 3m 2m B 9m 3p 1p 6p S 4s 5p 8s 4m 5s 2s 3s 0```

### 输出

```
1308622848
127401984```

# 题解

## 作者：do_while_true (赞：21)

[获得~~可能~~更优的阅读体验](https://www.cnblogs.com/do-while-true/p/14993015.html)

**快跑。**

本篇文章重点在于整理如何~~优美地~~写完这道题。

先手写张攻略理解下规则。

发现 $>15$ 张的「和牌」方式不需考虑，没有 「$[3\times 4+2]$」 的更优。若是宝牌： $\binom{4}{4}\times 2<\binom{4}{3}\times2$；若不是宝牌：$\binom{4}{4}<\binom{4}{3}$，所以 $>15$ 张的「和牌」方式中的杠子可以换成刻子，答案更优。

「宝牌」数对「达成分数」的贡献可以拆开分给每个数。

现在「和牌」方式仅剩 「$[3\times 4+2]$」、「七对子」、「国士无双」 三种方案。前两种分别 dp 一下，后者暴力算答案。

- 预处理

为了方便做，先给每种牌一个标号。因人而异，建议万索筒这三个序数牌放在一起编号，因为他们**各自**可以组成顺子。

```cpp
bool baopai[35];
int cnt[35]; 

//为了方便，我把和计算答案有关的，和输入有关的分别放到namespace中。
 
namespace Calc {
	int fac[15], pow2[50];
	void Cpre() { fac[0] = 1; for(int i = 1; i <= 10; ++i) fac[i] = fac[i-1] * i; pow2[0] = 1; for(int i = 1; i <= 30; ++i) pow2[i] = pow2[i-1]*2; }
	inline ll C(int x, int y) { return fac[x] / fac[y] / fac[x-y]; }
	inline ll cbp(int x, int y) { return baopai[x] ? pow2[y] : 1; }
}
using namespace Calc;
namespace How_to_get {
	//1  -> 9   1m,2m,3m...
	//10 -> 18  1p,2p,3p...
	//19 -> 27  1s,2s,3s...
	//28:E  29:S  30:W  31:N  32:Z  33:B  34:F
	inline char getcha() { char ch; std::cin >> ch; return ch; }          
	inline int getpai() {
		char ch = getcha(); if(ch == '0') return 0;
		if(ch >= '1' && ch <= '9') {
			char ch2 = getcha();
			if(ch2 == 'm') return ch-'0';
			if(ch2 == 'p') return 9+(ch-'0');
			if(ch2 == 's') return 18+(ch-'0');
		}
		switch(ch) {
			case 'E': return 28;
			case 'S': return 29;
			case 'W': return 30; 
			case 'N': return 31; 
			case 'Z': return 32; 
			case 'B': return 33; 
			case 'F': return 34; 
		}
		return 0;
	}
	void read1() {
		int x = getpai();
		while(x) {
			cnt[x]--;
			x = getpai();
		}
	}
	void read2() {
		int x = getpai();
		while(x) {
			baopai[x] = 1;
			x = getpai();
		}
	}
}
using namespace How_to_get;
```

- 「国士无双」

直接暴力做。列出可以「国士无双」的牌的编号，先假装全只选一个算出答案，然后枚举哪张牌选了两遍，算一下答案即可。

```cpp
int gsws[15] = {0, 1, 9, 10, 18, 19, 27, 28, 29, 30, 31, 32, 33, 34};
ll Gsws() {
	Cpre();
	ll sumq = 0, mul = 1, bps = 0;
	for(int i = 1; i <= 13; ++i) if(cnt[gsws[i]] == 0) return 0;
	for(int i = 1; i <= 13; ++i) mul *= cnt[gsws[i]], bps += baopai[gsws[i]];
	for(int i = 1; i <= 13; ++i) {
		if(cnt[gsws[i]] <= 1) continue ;
		sumq = Max(sumq, mul / cnt[gsws[i]] * C(cnt[gsws[i]], 2) * pow2[bps+baopai[gsws[i]]]);
	}
	return sumq * 13;
}
```

- 「$[3\times 4+2]$」

算是最难写的一部分。

设 $f_{i,j,k,c1,c2}$ 为考虑前 $i$ 种牌，$j$ 个面子，有 $k$ 个雀头，第 $i$ 种牌选了 $c_1$ 个，第 $(i-1)$ 种牌选了 $c_2$ 个的最高分数。

填表法是前面状态转移到当前状态，涉及减法有点绕。考虑刷表法，从当前状态转移到后面状态。值得注意的是选取 $c_1,c_2$ 意义为选了几个而不是剩下几个也是避免 dp 的时候关于状态的下标涉及减法，不太好绕得过来。

有两种 dp 方式，一种是 $(i+1)$ 能作为结尾顺顺子的，一种是不能的。（因为选择刷表法，所以枚举 $i$ 之后看的牌是 $(i+1)$ 号牌。）

**注意到不仅有八筒不能往下顺下去，八万和八索也不能往下顺下去，不能出现八万九万一索顺子的情况**。

对于前一种，有以下几种转移方法：

- 一组刻子；

- 一组或两组顺子；

- 一组刻子，一组顺子；

- 一组雀头；

- 一组雀头，一组顺子；

- 一组雀头，两组顺子；

- 什么也不选。

因为三个顺子可以转化成三个刻子，所以不需要三个顺子的转移，四个顺子也类似。

对于后一种，有以下几种转移方法：

- 一组刻子；

- 一组雀头；

- 什么也不选。

然后就是考验代码能力的环节了：

```cpp
void dp1(int l, int r) {
    for(int i = l; i <= r; ++i)
        for(int j = 0; j <= 4; ++j)
            for(int k = 0; k <= 1; ++k)
                    for(int c1 = 0; c1 <= 4; ++c1)
                        for(int c2 = 0; c2 <= 4; ++c2) {
                                if(!f[i][j][k][c1][c2]) continue ;
                                if(j == 4 && k) chkmax(ans, f[i][j][k][c1][c2]);
                                //刻子*1
                                if(j+1<=4 && cnt[i+1] >= 3)
                                    chkmax(f[i+1][j+1][k][3][c1], f[i][j][k][c1][c2] * C(cnt[i+1], 3) * cbp(i+1, 3));
                                //顺子
                                for(int p = 1; p <= 2; ++p) 
                                    if(j+p<=4 && i>=2 && cnt[i+1]>=p && c1<=cnt[i]-p && c2<=cnt[i-1]-p)
                                        chkmax(f[i+1][j+p][k][p][c1+p], f[i][j][k][c1][c2] / C(cnt[i], c1) / C(cnt[i-1], c2) * C(cnt[i+1], p) * C(cnt[i], c1+p) * C(cnt[i-1], c2+p) * cbp(i+1, p) * cbp(i, p) * cbp(i-1, p));
                                //刻子*1+顺子*1
                                if(j+2<=4 && i>=2 && cnt[i+1] >= 4 && c1 < cnt[i] && c2 < cnt[i-1])
                                    chkmax(f[i+1][j+2][k][4][c1+1], f[i][j][k][c1][c2] / C(cnt[i], c1) / C(cnt[i-1], c2) * C(cnt[i+1], 4) * C(cnt[i], c1+1) * C(cnt[i-1], c2+1) * cbp(i+1, 4) * cbp(i, 1) * cbp(i-1, 1));
                                //雀头*1
                                if(cnt[i+1] >= 2 && !k)
                                    chkmax(f[i+1][j][1][2][c1], f[i][j][k][c1][c2] * C(cnt[i+1], 2) * cbp(i+1, 2));
                                //雀头*1 + 顺子*1
                                if(j+1<=4 && i>=2 && cnt[i+1] >= 3 && !k && c1 < cnt[i] && c2 < cnt[i-1])
                                    chkmax(f[i+1][j+1][1][3][c1+1], f[i][j][k][c1][c2] / C(cnt[i], c1) / C(cnt[i-1], c2) * C(cnt[i+1], 3) * C(cnt[i], c1+1) * C(cnt[i-1], c2+1) * cbp(i+1, 3) * cbp(i, 1) * cbp(i-1, 1));
                                chkmax(f[i+1][j][k][0][c1], f[i][j][k][c1][c2]);
                                //雀头*1 + 顺子*2
                                if(j+2<=4 && i>=2 && cnt[i+1] >= 4 && !k && c1 < cnt[i]-1 && c2 < cnt[i-1]-1)
                                    chkmax(f[i+1][j+2][1][4][c1+2], f[i][j][k][c1][c2] / C(cnt[i], c1) / C(cnt[i-1], c2) * C(cnt[i+1], 4) * C(cnt[i], c1+2) * C(cnt[i-1], c2+2) * cbp(i+1, 4) * cbp(i, 2) * cbp(i-1, 2));
                                chkmax(f[i+1][j][k][0][c1], f[i][j][k][c1][c2]);
                            }
}
void dp2(int l, int r) {
	for(int i = l; i <= r; ++i)
		for(int j = 0; j <= 4; ++j)
			for(int k = 0; k <= 1; ++k)
					for(int c1 = 0; c1 <= 4; ++c1)
						for(int c2 = 0; c2 <= 4; ++c2) {
								if(!f[i][j][k][c1][c2]) continue ;
								if(j == 4 && k) chkmax(ans, f[i][j][k][c1][c2]), chkmax(sumq1, f[i][j][k][c1][c2]);
								//刻子           
								if(j+1 <= 4 && cnt[i+1] >= 3)
									chkmax(f[i+1][j+1][k][3][c1], f[i][j][k][c1][c2] * C(cnt[i+1], 3) * cbp(i+1, 3));
								//雀头 
								if(cnt[i+1] >= 2 && !k)
									chkmax(f[i+1][j][1][2][c1], f[i][j][k][c1][c2] * C(cnt[i+1], 2) * cbp(i+1, 2));
								chkmax(f[i+1][j][k][0][c1], f[i][j][k][c1][c2]);
						}
}
```

处理当前询问的部分有关「$[3\times 4+2]$」的：

```cpp
	f[0][0][0][0][0] = 1;
	dp1(0, 8);
	dp2(9, 10);
	dp1(11, 17);
	dp2(18, 19);
	dp1(20, 26);
	dp2(27, 33);
	for(int c1 = 0; c1 <= 4; ++c1)
		for(int c2 = 0; c2 <= 4; ++c2)
			chkmax(ans, f[34][4][1][c1][c2]);
```

- 「七对子」

和上面的类似，不过更为简单。

设 $g_{i,j}$ 为前 $i$ 种牌，$j$ 个雀头，的最高分数。

由于需要**不同的雀头**，对于一种牌，只能选出一组雀头。

这样转移就很好转移了。

```cpp
	g[0][0] = 7;
	for(int i = 0; i <= 33; ++i)
		for(int j = 0; j <= 7; ++j) {
			if(!g[i][j]) continue ;
			if(j == 7) chkmax(ans, g[i][j]);
			if(cnt[i+1] >= 2 && j+1 <= 7)
				chkmax(g[i+1][j+1], g[i][j] * C(cnt[i+1], 2) * cbp(i+1, 2));
			chkmax(g[i+1][j], g[i][j]);
		}
	chkmax(ans, g[34][7]);
```

总得来讲，我写这道题大体分为这三步：

1. 整理题目规则，写一份"攻略"，标出重点，坑点，例如该题中顺子的条件，「七对子」要求雀头都不相等。

2. 分析题目哪些是不必要写的，剩下几部分分别应该怎么解决。

3. 编写代码，尽量封装来减少代码量，使代码可读性更高，更好调试。

希望能对你有所帮助。

完整版代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define pb push_back
#define fir first
#define sec second
#define mp std::make_pair
typedef std::pair<int, int> pii;
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Abs(T x) { return x < 0 ? -x : x; }
template <typename T> T chkmax(T &x, T y) { return x = x > y ? x : y; }
template <typename T>
T &read(T &r) {
    r = 0; bool w = 0; char ch = getchar();
    while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
    while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
    return r = w ? -r : r;
}

bool baopai[35];
int cnt[35];

namespace Calc {
    int fac[15], pow2[50];
    void Cpre() { fac[0] = 1; for(int i = 1; i <= 10; ++i) fac[i] = fac[i-1] * i; pow2[0] = 1; for(int i = 1; i <= 30; ++i) pow2[i] = pow2[i-1]*2; }
    inline ll C(int x, int y) { return fac[x] / fac[y] / fac[x-y]; }
    inline ll cbp(int x, int y) { return baopai[x] ? pow2[y] : 1; }
}
using namespace Calc;
namespace How_to_get {
    inline char getcha() { char ch; std::cin >> ch; return ch; }          
    inline int getpai() {
        char ch = getcha(); if(ch == '0') return 0;
        if(ch >= '1' && ch <= '9') {
            char ch2 = getcha();
            if(ch2 == 'm') return ch-'0';
            if(ch2 == 'p') return 9+(ch-'0');
            if(ch2 == 's') return 18+(ch-'0');
        }
        switch(ch) {
            case 'E': return 28;
            case 'S': return 29;
            case 'W': return 30; 
            case 'N': return 31; 
            case 'Z': return 32; 
            case 'B': return 33; 
            case 'F': return 34; 
        }
        return 0;
    }
}
using namespace How_to_get;

int gsws[15] = {0, 1, 9, 10, 18, 19, 27, 28, 29, 30, 31, 32, 33, 34};

void read1() {
    int x = getpai();
    while(x) {
        cnt[x]--;
        x = getpai();
    }
}
void read2() {
    int x = getpai();
    while(x) {
        baopai[x] = 1;
        x = getpai();
    }
}
ll Gsws() {
    Cpre();
    ll sumq = 0, mul = 1, bps = 0;
    for(int i = 1; i <= 13; ++i) if(cnt[gsws[i]] == 0) return 0;
    for(int i = 1; i <= 13; ++i) mul *= cnt[gsws[i]], bps += baopai[gsws[i]];
    for(int i = 1; i <= 13; ++i) {
        if(cnt[gsws[i]] <= 1) continue ;
        sumq = Max(sumq, mul / cnt[gsws[i]] * C(cnt[gsws[i]], 2) * pow2[bps+baopai[gsws[i]]]);
    }
    return sumq * 13;
}

ll f[40][10][5][6][6], g[40][10];
ll ans = 0;

    //1  -> 9   1m,2m,3m...
    //10 -> 18  1p,2p,3p...
    //19 -> 27  1s,2s,3s...
    //28:E  29:S  30:W  31:N  32:Z  33:B  34:F 
void dp1(int l, int r) {
    for(int i = l; i <= r; ++i)
        for(int j = 0; j <= 4; ++j)
            for(int k = 0; k <= 1; ++k)
                    for(int c1 = 0; c1 <= 4; ++c1)
                        for(int c2 = 0; c2 <= 4; ++c2) {
                                if(!f[i][j][k][c1][c2]) continue ;
                                if(j == 4 && k) chkmax(ans, f[i][j][k][c1][c2]);
                                //刻子*1
                                if(j+1<=4 && cnt[i+1] >= 3)
                                    chkmax(f[i+1][j+1][k][3][c1], f[i][j][k][c1][c2] * C(cnt[i+1], 3) * cbp(i+1, 3));
                                //顺子
                                for(int p = 1; p <= 2; ++p) 
                                    if(j+p<=4 && i>=2 && cnt[i+1]>=p && c1<=cnt[i]-p && c2<=cnt[i-1]-p)
                                        chkmax(f[i+1][j+p][k][p][c1+p], f[i][j][k][c1][c2] / C(cnt[i], c1) / C(cnt[i-1], c2) * C(cnt[i+1], p) * C(cnt[i], c1+p) * C(cnt[i-1], c2+p) * cbp(i+1, p) * cbp(i, p) * cbp(i-1, p));
                                //刻子*1+顺子*1
                                if(j+2<=4 && i>=2 && cnt[i+1] >= 4 && c1 < cnt[i] && c2 < cnt[i-1])
                                    chkmax(f[i+1][j+2][k][4][c1+1], f[i][j][k][c1][c2] / C(cnt[i], c1) / C(cnt[i-1], c2) * C(cnt[i+1], 4) * C(cnt[i], c1+1) * C(cnt[i-1], c2+1) * cbp(i+1, 4) * cbp(i, 1) * cbp(i-1, 1));
                                //雀头*1
                                if(cnt[i+1] >= 2 && !k)
                                    chkmax(f[i+1][j][1][2][c1], f[i][j][k][c1][c2] * C(cnt[i+1], 2) * cbp(i+1, 2));
                                //雀头*1 + 顺子*1
                                if(j+1<=4 && i>=2 && cnt[i+1] >= 3 && !k && c1 < cnt[i] && c2 < cnt[i-1])
                                    chkmax(f[i+1][j+1][1][3][c1+1], f[i][j][k][c1][c2] / C(cnt[i], c1) / C(cnt[i-1], c2) * C(cnt[i+1], 3) * C(cnt[i], c1+1) * C(cnt[i-1], c2+1) * cbp(i+1, 3) * cbp(i, 1) * cbp(i-1, 1));
                                chkmax(f[i+1][j][k][0][c1], f[i][j][k][c1][c2]);
                                //雀头*1 + 顺子*2
                                if(j+2<=4 && i>=2 && cnt[i+1] >= 4 && !k && c1 < cnt[i]-1 && c2 < cnt[i-1]-1)
                                    chkmax(f[i+1][j+2][1][4][c1+2], f[i][j][k][c1][c2] / C(cnt[i], c1) / C(cnt[i-1], c2) * C(cnt[i+1], 4) * C(cnt[i], c1+2) * C(cnt[i-1], c2+2) * cbp(i+1, 4) * cbp(i, 2) * cbp(i-1, 2));
                                chkmax(f[i+1][j][k][0][c1], f[i][j][k][c1][c2]);
                            }
}
void dp2(int l, int r) {
    for(int i = l; i <= r; ++i)
        for(int j = 0; j <= 4; ++j)
            for(int k = 0; k <= 1; ++k)
                    for(int c1 = 0; c1 <= 4; ++c1)
                        for(int c2 = 0; c2 <= 4; ++c2) {
                                if(!f[i][j][k][c1][c2]) continue ;
                                if(j == 4 && k) chkmax(ans, f[i][j][k][c1][c2]);
                                //刻子           
                                if(j+1 <= 4 && cnt[i+1] >= 3)
                                    chkmax(f[i+1][j+1][k][3][c1], f[i][j][k][c1][c2] * C(cnt[i+1], 3) * cbp(i+1, 3));
                                //雀头 
                                if(cnt[i+1] >= 2 && !k)
                                    chkmax(f[i+1][j][1][2][c1], f[i][j][k][c1][c2] * C(cnt[i+1], 2) * cbp(i+1, 2));
                                chkmax(f[i+1][j][k][0][c1], f[i][j][k][c1][c2]);
                        }
}
void solve() {
    for(int i = 1; i <= 34; ++i) cnt[i] = 4, baopai[i] = 0;
    read1(); read2();
    ans = 0;
    ans = Max(ans, Gsws());
    for(int i = 1; i <= 34; ++i)
        for(int j = 0; j <= 4; ++j)
            for(int k = 0; k <= 1; ++k)
                    for(int c1 = 0; c1 <= 4; ++c1)
                        for(int c2 = 0; c2 <= 4; ++c2)
                                f[i][j][k][c1][c2] = 0;
    for(int i = 1; i <= 34; ++i)
        for(int j = 0; j <= 7; ++j)
                    g[i][j] = 0;
    f[0][0][0][0][0] = 1;
    dp1(0, 8);
    dp2(9, 10);
    dp1(11, 17);
    dp2(18, 19);
    dp1(20, 26);
    dp2(27, 33);
    for(int c1 = 0; c1 <= 4; ++c1)
        for(int c2 = 0; c2 <= 4; ++c2)
            chkmax(ans, f[34][4][1][c1][c2]);
    g[0][0] = 7;
    for(int i = 0; i <= 33; ++i)
        for(int j = 0; j <= 7; ++j) {
            if(!g[i][j]) continue ;
            if(j == 7) chkmax(ans, g[i][j]);
            if(cnt[i+1] >= 2 && j+1 <= 7)
                chkmax(g[i+1][j+1], g[i][j] * C(cnt[i+1], 2) * cbp(i+1, 2));
            chkmax(g[i+1][j], g[i][j]);
        }
    chkmax(ans, g[34][7]);
    printf("%lld\n", ans);
}

signed main() { //freopen("in.txt", "r", stdin);
    int T; read(T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：Refined_heart (赞：11)

[[GXOI/GZOI2019]宝牌一大堆](https://www.luogu.com.cn/problem/P5301)

$\text{Solution:}$

从 $8kb$ 代码改到 $11kb$ 最后封装到 $5kb$ ……封装 yyds dwt yyds

学到最大的除了 $dp$ 应该是调试技巧和封装的重要性了……

方程可能写的有点奇怪）看看能不能帮到和我一样设计状态的同学）

后面附带了一些注意事项。欢迎补充。

* 「国士无双」

考虑枚举哪一张牌选两张即可，复杂度 $O(13^2).$

* 「七对子」

由于七对子不能重复，所以考虑把每一张牌做对子的价值倍率都记录下来，选取最大的七个即可。

* $「3 \times 4 + 2」$

这部分就需要 $dp$ 了，暴力的复杂度显然不能接受。

考虑：设 $dp[i][j][k][l][m]$ 表示当前是第 $i$ 张牌，已经凑出 $j$ 个面子， $k$ 代表有没有雀头， 当前牌还剩 $l$ 张，上一张牌还剩 $m$ 张的最大得分。

注意这里是还剩下几张，所以转移的时候是用 $i+1$ 牌的数量减去当前转移用掉的牌数。

以下令函数 $\text{Getv(pos,num)}$ 表示第 $pos$ 张牌有 $num$ 张造成的宝牌收益。

凑一组刻子：

条件： $Num_{i+1}>2$

转移： 

$$dp[i+1][j+1][k][Num_{i+1}-3][l]=\max\left\{ dp[i][j][k][l][m]\cdot Getv(i+1,3)\cdot {Num_{i+1}\choose 3}\right\}$$

凑一组顺子：

条件： $l>0,m>0,Num_{i+1}>0$

转移： 

$$dp[i+1][j+1][k][Num_{i+1}-1][l-1]=\max\left\{ dp[i][j][k][l][m]\cdot Getv(i-1,1)\cdot Getv(i,1)\cdot Getv(i+1,1)\cdot\frac{ {Num_{i-1}\choose Num_{i-1}-m+1}\cdot {Num_i\choose Num_i-l+1}\cdot{Num_{i+1}\choose 1}}{{Num_i\choose l}\cdot {Num_{i-1}\choose m}}\right\}$$

凑两组顺子：

条件： $l>1,m>1,Num_{i+1}>1$

转移：

$$dp[i+1][j+2][k][Num_{i+1}-2][l-2]=\max\left\{ dp[i][j][k][l][m]\cdot Getv(i-1,2)\cdot Getv(i,2)\cdot Getv(i+1,2)\cdot\frac{ {Num_{i-1}\choose Num_{i-1}-m+2}\cdot {Num_i\choose Num_i-l+2}\cdot{Num_{i+1}\choose 2}}{{Num_i\choose l}\cdot {Num_{i-1}\choose m}}\right\}$$

凑一组雀头：

条件： $k=0,Num_{i+1}>1$

转移：

$$dp[i+1][j][k+1][Num_{i+1}-2][l]=\max\left\{dp[i][j][k][l][m]\cdot{Num_{i+1}\choose 2}\cdot Getv(i+1,2)\right\}$$

凑一组雀头带顺子一对：

条件： $k=0,Num_{i+1}>2,l>0,m>0$

转移：

$$dp[i+1][j+1][k+1][Num_{i+1}-3][l-1]=\max\left\{dp[i][j][k][l][m]\cdot Getv(i-1,1)\cdot Getv(i,1)\cdot Getv(i,3)\cdot\frac{{Num_{i+1}\choose 3}\cdot{Num_i\choose Num_i-l+1}\cdot {Num_{i-1}\choose Num_{i-1}-m+1}}{{Num_i\choose l}\cdot {Num_{i-1}\choose m}}\right\}$$

凑一组雀头带顺子两对：

条件： $k=0,l>1,m>1,Num_{i+1}=4$

转移：

$$dp[i+1][j+2][k+1][Num_{i+1}-4][l-2]=\max\left\{dp[i][j][k][l][m]\cdot Getv(i-1,2)\cdot Getv(i,2)\cdot Getv(i,4)\cdot\frac{{Num_{i+1}\choose 4}\cdot{Num_i\choose Num_i-l+2}\cdot {Num_{i-1}\choose Num_{i-1}-m+2}}{{Num_i\choose l}\cdot {Num_{i-1}\choose m}}\right\}$$

凑顺子带刻子：

条件： $Num_{i+1}=4,l>0,m>0$

转移：

$$dp[i+1][j+2][k][Num_{i+1}-4][l-1]=\max\left\{dp[i][j][k][l][m]\cdot Getv(i+1,4)\cdot Getv(i,1)\cdot Getv(i-1,1)\cdot\frac{{Num_i\choose Num_i-l+1}\cdot {Num_{i-1}\choose Num_{i-1}-m+1}\cdot{Num_i\choose 4}}{{Num_i\choose l}\cdot{Num_{i-1}\choose m}}\right\}$$

不选当前牌：

转移：

$$dp[i+1][j][k][Num_{i+1}][l]=\max\left\{dp[i][j][k][l][m]\right\}$$

注意事项：

* 除法一定放在乘法最后，要不然先除可能会变成 $0$ 。

* 注意顺子能不能连起来，比如九筒和一索就不能连。

* 注意转移的时候 $j$ 代表的面子数量到底改不改动以及改多少。

* 宝牌的数量不要想错，应该是 $2^{num}.$

* 判断顺子的时候还要注意它是不是能连顺子的牌，即排除掉 “东西南北中白发” 七张牌。

* 走国士无双的时候要判断一下能不能走。

* 代码注意封装以减轻调试难度。

* 读入的时候转数字编码要记录一下来方便写完后的代码调试以及细节处理。

* $dp$ 值为 $0$ 的状态是不需要进入转移的。

* 别忘了 「国士无双」 牌型的胡牌倍率 $13$ 以及 「七对子」 胡牌牌型的倍率 $7$ .

* 开 $\text{long long}.$

代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
int T,fac[20],card,num[50],vis[50];
vector<int>v;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
void pre(){
	fac[0]=1;card=0;
	for(int i=1;i<=12;++i)fac[i]=fac[i-1]*i;
	for(int i=1;i<=34;++i)num[i]=4;
	for(int i=1;i<=34;++i)vis[i]=0;
}
int C(int x,int y){if(x<y)return 1;return fac[x]/fac[y]/fac[x-y];}
// num是牌的数量 vis是标记是不是宝牌 fac[]是阶乘 card是总牌数 
/*--------国士无双-----------*/
inline bool check_Tbp(int p){
	if(vis[p]&&num[p]>1)return true;
	return false;
}
int equal(){
	int ct=0;
	for(auto j:v){
		if(num[j]<1)return 0;
		ct+=num[j];
	}
	int ans=-1;
	for(auto j:v){
		if(num[j]<2)continue;
		// cout<<j<<" "<<num[j]<<" "<<vis[j]<<endl;
		int res=C(num[j],2);
		if(vis[j])res<<=2ll;
		for(auto k:v){
			if(k==j)continue;
			res*=num[k];
			if(vis[k])res<<=1ll;
		}
		ans=Max(ans,res);
//		if(res==ans)cout<<j<<" "<<num[j]<<endl;
	}
	return ans*13ll;
}
/*-------------七对子-------------*/
int val[50];
inline bool cmp(int A,int B){return A>B;}
int solve_seven(){
	for(int i=1;i<=34;++i){
		if(num[i]<2)continue;
		val[i]=C(num[i],2);
		if(vis[i])val[i]<<=2;
	}
	sort(val+1,val+34+1,cmp);
	int ans=1;
	for(int i=1;i<=7;++i)ans=ans*val[i];
	for(int i=1;i<=34;++i)val[i]=0;
	return ans*7;
}
/*--------------胡牌-------------*/
int dp[40][7][7][7][7]; 
//前i张牌，有j个面子，有没有雀头 i还剩几张，i-1还剩几张，
//dp[i][j][k][l][m]
bool ck(int x){
	if(x==28||x==29||x==30||x==31||x==32||x==33||x==34)return false;
	return true;
}
inline int Getv(int pos,int num){
	return vis[pos]?1LL<<num:1;
}
inline bool Ck(int x,int y,int z){
	return ck(y)&&ck(x)&&ck(z)&&(((z<=9)&&((x)>=1))||((z>9)&&(z)<=18&&x>9)||(z>18&&z<=27&&x>18));
}
int general(){
	dp[0][0][0][0][0]=1;
	for(int i=0;i<=33;++i)
		for(int j=0;j<=4;++j)
			for(int k=0;k<=1;++k)
				for(int l=0;l<=num[i];++l)//当前 
					for(int mm=0;mm<=num[i-1];++mm){//上一个 
						int cd=i+1;
						int numc=num[cd];
						int Len1=num[i];
						int Len2=num[i-1];
						if(!dp[i][j][k][l][mm])continue;
						if(numc>=3){//刻子 
							dp[i+1][j+1][k][numc-3][l]=Max(dp[i+1][j+1][k][numc-3][l],dp[i][j][k][l][mm]*Getv(i+1,3)*C(numc,3));
						}
						
						//顺子1 	
						if(l>0&&mm>0&&numc>0&&Ck(i-1,i,i+1)){
							dp[i+1][j+1][k][numc-1][l-1]=Max(dp[i+1][j+1][k][numc-1][l-1],dp[i][j][k][l][mm]*Getv(i-1,1)*Getv(i,1)*Getv(i+1,1)*numc*C(num[i-1],num[i-1]-mm+1)*C(num[i],num[i]-l+1)/C(Len2,Len2-mm)/C(Len1,Len1-l));
						}
						
						//顺子2 
						if(l>1&&mm>1&&numc>1&&Ck(i-1,i,i+1)){
							dp[i+1][j+2][k][numc-2][l-2]=Max(dp[i+1][j+2][k][numc-2][l-2],dp[i][j][k][l][mm]*Getv(i-1,2)*Getv(i,2)*Getv(i+1,2)*C(numc,2)*C(Len2,Len2-mm+2)*C(Len1,Len1-l+2)/C(Len2,Len2-mm)/C(Len1,Len1-l));
						}
						
						//单雀头 
						if(numc>=2&&!k)dp[i+1][j][k^1][numc-2][l]=Max(dp[i+1][j][k^1][numc-2][l],dp[i][j][k][l][mm]*Getv(i+1,2)*C(numc,2));
						
						
						//雀头带单顺子 
						if(!k&&numc>=3&&l>0&&mm>0&&Ck(i-1,i,i+1))
							dp[i+1][j+1][k^1][numc-3][l-1]=Max(dp[i+1][j+1][k^1][numc-3][l-1],dp[i][j][k][l][mm]*Getv(i+1,3)*Getv(i,1)*Getv(i-1,1)*C(Len2,Len2-mm+1)*C(Len1,Len1-l+1)/C(Len2,Len2-mm)/C(Len1,l)*C(numc,3));
						
						
						//雀头带双顺子 
						if(!k&&numc>=4&&l>1&&mm>1&&Ck(i-1,i,i+1))
							dp[i+1][j+2][k^1][numc-4][l-2]=Max(dp[i+1][j+2][k^1][numc-4][l-2],dp[i][j][k][l][mm]*Getv(i+1,4)*Getv(i,2)*Getv(i-1,2)*C(Len2,Len2-mm+2)*C(Len1,Len1-l+2)/C(Len2,Len2-mm)/C(Len1,Len1-l));
						//顺子带刻子
						if(numc>=4&&l>0&&mm>0&&Ck(i-1,i,i+1)){
							dp[i+1][j+2][k][numc-4][l-1]=Max(dp[i+1][j+2][k][numc-4][l-1],dp[i][j][k][l][mm]*Getv(i+1,4)*Getv(i,1)*Getv(i-1,1)*C(Len1,Len1-l+1)*C(Len2,Len2-mm+1)/C(Len1,Len1-l)/C(Len2,Len2-mm));
						} 
						
						
						//不选 
						dp[i+1][j][k][numc][l]=Max(dp[i+1][j][k][numc][l],dp[i][j][k][l][mm]);
					}
//	//----------------------------------------------------------------------------------------------------------------------------------
	int ans=-1;
	for(int i=0;i<=34;++i)
		for(int j=0;j<=4;++j)
			for(int k=0;k<=4;++k)
				ans=Max(ans,dp[i][4][1][j][k]);
	return ans;
	
}
void clear(){
	for(int i=0;i<=35;++i)
		for(int j=0;j<=5;++j)
			for(int k=0;k<=1;++k)
				for(int l=0;l<=5;++l)
					for(int mm=0;mm<=5;++mm)
						dp[i][j][k][l][mm]=0;
}
char getcha(){char x;cin>>x;return x;}
int Readchar(){
	char ch=getcha();
	if(ch=='0')return 0;
	if(isdigit(ch)){
		char c=getcha();
		if(c=='m')return (int)ch-'0';
		if(c=='p')return (int)ch-'0'+9;
		if(c=='s')return (int)ch-'0'+18;
	}
	else{
		switch(ch){
			case 'E':return 28;
			case 'W':return 29;
			case 'S':return 30;
			case 'N':return 31;
			case 'Z':return 32;
			case 'B':return 33;
			case 'F':return 34;
		}
	}
	return 0;
}
void Init(){
	int TT;
	scanf("%lld",&TT);
	while(TT--){
		pre();
		do{
			int x=Readchar();
			if(x==0)break;
			num[x]--;
			if(x>27||x==1||x==9||x==10||x==18||x==19||x==27)card++;
		}while(1);
		do{
			int x=Readchar();
			if(x==0)break;
			vis[x]=1;
		}while(1);
		card=13*4-card;
		int Ans=Max(equal(),Max(solve_seven(),general()));
//		printf("%lld %lld %lld\n",equal(),solve_seven(),general());
		printf("%lld\n",Ans);
		clear();
	}
}
signed main(){
//	freopen("111.txt","r",stdin);
	v.push_back(1);
	v.push_back(9);
	v.push_back(10);
	v.push_back(18);
	v.push_back(19);
	v.push_back(27);
	v.push_back(28);
	v.push_back(29);
	v.push_back(30);
	v.push_back(31);
	v.push_back(32);
	v.push_back(33);
	v.push_back(34);
	Init();
	return 0;
}
```

---

## 作者：liuzhangfeiabc (赞：10)

怎么大家都这么喜欢麻将啊......~~(话说我们机房已经全体中毒雀魂了的说)~~

如果大家之前做过zjoi的麻将的话应该对这题印象还可以吧...毕竟相比那题的dp套dp来说，这题相当于直接把内层dp拿出来出成题。

设f[i][j][k][l][0/1]表示：处理了前i种牌，目前有j个面子(或杠子)，以i-1开始的顺子打算选k个，以i开始的面子打算选l个，现在是否有雀头的答案。

转移时直接枚举下一种牌选几张，讨论一下它用来凑什么牌即可。

新的一种牌必须拿出k+l张来满足前面的顺子，其余的可以用来凑对子/刻子/杠子/新开几个面子。

注意杠子和刻子的唯一区别就是差一张牌，因此无需单独记录杠子的状态，而是把它也当成一种刻子，只不过凑的时候额外需要一张牌。

大家可能注意到了我们并没有记录选了多少张牌。实际上，记录这个是不需要的，因为我们可以通过后几维的信息算出它来。

另外，注意到东南西北中发白和点数为8,9的牌是不能作为顺子的开头的，这里在枚举时要注意一下。

再另外，j的范围显然是0~4，然而k和l的范围呢？仔细想想就会知道它们应该是0~2范围，因为一组形如(i,i+1,i+2),(i,i+1,i+2),(i,i+1,i+2)的顺子，我们其实可以将其看做(i,i,i),(i+1,i+1,i+1),(i+2,i+2,i+2）的一组刻子，因此从一个位置开始的顺子数量不会超过2。

最后f[34][4][0][0][1]即为所求。

最后判一下七小对和国士无双两种特殊牌型。前者直接贪心地选7个价值最大的对子，后者枚举哪一种牌选2张即可。

复杂度O(T×34×5×3×3×2×5),实际上因为不合法状态比较多还会更小一些。

~~代码蛮好写的也就4个k：~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define li long long
#define gc getchar()
#define pc putchar
inline li read(){
    li x = 0,y = 0,c = gc;
    while(!isdigit(c)) y = c,c = gc;
    while(isdigit(c)) x = x * 10 + c - '0',c = gc;
    return y == '-' ? -x : x;
}
inline void print(li q){
    if(q < 0) pc('-'),q = -q;
    if(q >= 10) print(q / 10);
    pc(q % 10 + '0');
}
int t,cnt;
int a[40],c[5][5];
bool b[40];
li f[40][5][3][3][2];
int gs[14] = {0,1,9,10,18,19,27,28,29,30,31,32,33,34};//国士无双的13张牌
li tp[40];
int main(){
    register int i,j,k,l,u,v;
    c[0][0] = 1;
    for(i = 1;i <= 4;++i){
        c[i][0] = 1;
        for(j = 1;j <= i;++j) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
    t = read();
    while(t--){
        memset(a,0,sizeof(a));memset(b,0,sizeof(b));memset(f,0,sizeof(f));
        while(1){//读入打出的牌
            string c;cin>>c;
            if(c[0] == '0') break;
            else if(c[0] == 'E') ++a[28];
            else if(c[0] == 'S') ++a[29];
            else if(c[0] == 'W') ++a[30];
            else if(c[0] == 'N') ++a[31];
            else if(c[0] == 'Z') ++a[32];
            else if(c[0] == 'F') ++a[33];
            else if(c[0] == 'B') ++a[34];
            else if(c[1] == 'm') ++a[c[0] - '0'];
            else if(c[1] == 'p') ++a[c[0] + 9 - '0'];
            else if(c[1] == 's') ++a[c[0] + 18 - '0'];
        }
        while(1){//读入宝牌
            string c;cin>>c;
            if(c[0] == '0') break;
            else if(c[0] == 'E') b[28] = 1;
            else if(c[0] == 'S') b[29] = 1;
            else if(c[0] == 'W') b[30] = 1;
            else if(c[0] == 'N') b[31] = 1;
            else if(c[0] == 'Z') b[32] = 1;
            else if(c[0] == 'F') b[33] = 1;
            else if(c[0] == 'B') b[34] = 1;
            else if(c[1] == 'm') b[c[0] - '0'] = 1;
            else if(c[1] == 'p') b[c[0] + 9 - '0'] = 1;
            else if(c[1] == 's') b[c[0] + 18 - '0'] = 1;
        }
        for(i = 1;i <= 34;++i) a[i] = 4 - a[i];
        li as = 0;
        //处理国士无双
        for(i = 1;i <= 13;++i){
            li tmp = 1;
            for(j = 1;j <= 13;++j){
                if(i == j){
                    if(a[gs[j]] < 2) tmp = 0;
                    else tmp *= c[a[gs[j]]][2] * (b[gs[j]] ? 4 : 1);
                }
                else{
                    if(a[gs[j]] < 1) tmp = 0;
                    else tmp *= c[a[gs[j]]][1] * (b[gs[j]] ? 2 : 1);
                }
            }
            as = max(as,tmp * 13);
        }
        //处理七对子
        cnt = 0;
        for(i = 1;i <= 34;++i) if(a[i] >= 2) tp[++cnt] = c[a[i]][2] * (b[i] ? 4 : 1);
        if(cnt >= 7){
            sort(tp + 1,tp + cnt + 1);
            li tmp = 1;
            for(i = cnt;i > cnt - 7;--i) tmp *= tp[i];
            as = max(as,tmp * 7);
        }
        //尽显编程之美的dp
        f[0][0][0][0][0] = 1;
        for(i = 0;i < 34;++i){
            for(j = 0;j <= 4;++j){
                for(k = 0;k < 3 && j + k <= 4;++k){
                    if(k >= 1 && (i == 9 || i == 18 || i >= 27)) break;
                    for(l = 0;l < 3 && j + k + l <= 4;++l){
                        if(l >= 1 && (i == 9 || i == 18 || i >= 27)) break;
                        if(!f[i][j][k][l][0] && !f[i][j][k][l][1]) continue;
                        for(u = k + l;u <= a[i + 1];++u){
                            li tmp = c[a[i + 1]][u] * (b[i + 1] ? (1 << u) : 1);
                            if(j + u <= 4 && u - k - l < 3){
                                f[i + 1][j + k][l][u - k - l][0] = max(f[i + 1][j + k][l][u - k - l][0],f[i][j][k][l][0] * tmp);
                                f[i + 1][j + k][l][u - k - l][1] = max(f[i + 1][j + k][l][u - k - l][1],f[i][j][k][l][1] * tmp);
                            } 
                            if(u - k - l - 2 >= 0 && j + u - 2 <= 4){
                                f[i + 1][j + k][l][u - k - l - 2][1] = max(f[i + 1][j + k][l][u - k - l - 2][1],f[i][j][k][l][0] * tmp);
                            }
                            if(u - k - l - 3 >= 0 && j + u - 2 <= 4){
                                f[i + 1][j + k + 1][l][u - k - l - 3][0] = max(f[i + 1][j + k + 1][l][u - k - l - 3][0],f[i][j][k][l][0] * tmp);
                                f[i + 1][j + k + 1][l][u - k - l - 3][1] = max(f[i + 1][j + k + 1][l][u - k - l - 3][1],f[i][j][k][l][1] * tmp);
                            }
                            if(u == 4 && !k && !l && j <= 3){
                                f[i + 1][j + 1][0][0][0] = max(f[i + 1][j + 1][0][0][0],f[i][j][k][l][0] * tmp);
                                f[i + 1][j + 1][0][0][1] = max(f[i + 1][j + 1][0][0][1],f[i][j][k][l][1] * tmp);
                            }
                        }
                    }
                }
            }
        }
        as = max(as,f[34][4][0][0][1]);
        print(as);pc('\n');
    }
    return 0;
}
```

---

## 作者：墨笙_Mooos (赞：8)

题解区都是推转移方程，提供一种记忆化搜索的写法，不需要推式子，更适合我这种摆烂选手(x

---

首先是对牌进行编号，预处理一些需要用到的数。

编号方式因人而异，在此我给出我的编号方式。

我还预处理了二的幂次和组合数，方便调用。

```cpp
map<string, ll> Trans = { { "E", 1 }, { "S", 2 }, { "W", 3 }, { "N", 4 }, { "B", 5 }, { "F", 6 }, { "Z", 7 }, { "1m", 8 }, { "2m", 9 }, { "3m", 10 }, { "4m", 11 }, { "5m", 12 }, { "6m", 13 }, { "7m", 14 }, { "8m", 15 }, { "9m", 16 }, { "1p", 17 }, { "2p", 18 }, { "3p", 19 }, { "4p", 20 }, { "5p", 21 }, { "6p", 22 }, { "7p", 23 }, { "8p", 24 }, { "9p", 25 }, { "1s", 26 }, { "2s", 27 }, { "3s", 28 }, { "4s", 29 }, { "5s", 30 }, { "6s", 31 }, { "7s", 32 }, { "8s", 33 }, { "9s", 34 } };
const ll Pow2[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
const ll C[5][5] = { { 1, 0, 0, 0, 0 }, { 1, 1, 0, 0, 0 }, { 1, 2, 1, 0, 0 }, { 1, 3, 3, 1, 0 }, { 1, 4, 6, 4, 1 } };
```

考虑国士和七对，这部分做法不再赘述，只需要对每一种牌进行枚举即可。

```cpp
// inline void CkMax (ll& x, ll y) { x = max (x, y); }
// const vector<ll> Goshi = { 1, 2, 3, 4, 5, 6, 7, 8, 16, 17, 25, 26, 34 };
// Last[i] 表示第 i 种牌剩余枚数
// Dora[i] 表示第 i 种牌是否为宝牌
// Goshi 是储存所有字牌和幺九牌编号的 vector

// Sub 1 国士无双。
for (ll i : Goshi)
{
	if (Last[i] == 1) continue;
	Res = C[Last[i]][2] * (Dora[i] ? 4 : 1);
	for (ll Now : Goshi) if (Now != i)
		Res *= Last[Now] * (Dora[Now] ? 2 : 1);
	CkMax (Ans, Res * 13);
}

// 我使用的是背包的做法，f七对[i] 表示组成 i 个对子的最大价值。
// Sub 2 七对子。
f七对[0] = 1; For (i, 1, 7) f七对[i] = 0;
For (i, 1, 34) if (Last[i] >= 2) uFor (j, 7, 1)
	CkMax (f七对[j], f七对[j - 1] * C[Last[i]][2] * (Dora[i] ? 4 : 1));
CkMax (Ans, f七对[7] * 7);
```

再考虑一般型。

令 ```Calc(Now, x)``` 表示 ```x``` 张第 ```Now``` 种牌对答案的价值，即 ```Calc(Now, x) = C[Last[Now]][x] * (Dora[Now] ? Pow2[x] : 1)```。


令每个顺子都由最小的一张牌搜索到，下文中组成顺子代表从这张牌开始往后组成一个顺子。```Kind[x]``` 表示第 ```x``` 种牌是否可以往后组成一个顺子，可以预处理。（即 ```Kind[x] = 1``` 当且仅当 ```x``` 代表 ```1~7 m/p/s```）

那么考虑搜索到第 ```Now``` 种牌，已经组成了 ```Pre``` 个面子，在之前用了 ```CntNow``` 个第 ```Now``` 种牌和 ```CntNxt``` 个第 ```Now + 1``` 种牌（因为在 ```Now``` 之前的顺子最多能用到 ```Now + 1```），是否已经组成了雀头。容易得到搜索的状态 ```DFS (Now, Pre, CntNow, CntNxt, Couple)```，它等于下列情况中的最大值：

* 第 ```Now``` 种牌不再组成任何新的面子或者雀头。
  * 所有情况下均成立。
  * 价值为 ```DFS (Now + 1, Pre, CntNxt, 0, Couple) * Calc (Now, CntNow)```。
* 第 ```Now``` 种牌组成一个刻子。
  * ```Last[Now] >= CntNow + 3``` 时可取。
  * 价值为 ```DFS (Now + 1, Pre + 1, CntNxt, 0, Couple) * Calc (Now, CntNow + 3)```。
* 第 ```Now``` 种牌组成 ```i``` 个顺子。
  * ```Kind[Now] && Last[Now] >= CntNow + i``` 时可取。
  * 价值为 ```DFS (Now + 1, Pre + i, CntNxt + i, i, Couple) * Calc (Now, CntNow + i)```。
* 第 ```Now``` 种牌**组成一个刻子和组成一个顺子**。
  * ```Kind[Now] && Last[Now] >= CntNow + 4``` 时可取。
  * 价值为 ```DFS (Now + 1, Pre + 2, CntNxt + 1, 1, Couple) * Calc (Now, CntNow + 4)```。
* 第 ```Now``` 种牌组成一个雀头。
  * ```Couple == 0 && Last[Now] >= CntNow + 2``` 时可取。
  * 价值为 ```DFS (Now + 1, Pre, CntNxt, 0, true) * Calc (Now, CntNow + 2)```。
* 第 ```Now``` 种牌组成一个雀头和组成 ```i``` 个顺子。
  * ```Couple == 0 && Kind[Now] && Last[Now] >= CntNow + 2 + i``` 时可取。
  * 价值为 ```DFS (Now + 1, Pre + i, CntNxt + i, i, true) * Calc (Now, CntNow + 2 + i)```。

对每个变量考虑边界状态。

* 当前种类或下一种类的牌使用过多，或者**面子过多**。
  * ```CntNow > Last[Now] || CntNxt > Last[Now + 1] || Pre > 4```
  * 返回 ```0```
* 当前的牌已经组成了四个面子和一个雀头，那么再往后搜索也不会增加任何新的价值。
  * ```Pre == 4 && Couple```
  * 返回 ```Calc (Now, CntNow) * Calc (Now + 1, CntNxt)```
* 搜索完了所有牌。
  * ```Now == 35```
  * 此时如果正好能够组成一个和牌，且使用的牌不越界，则返回 ```1```。
  * 即返回 ```Couple && Pre == 4 && !CntNow && !CntNxt```
  * 事实上，前一种情况已经涵盖了有解的可能，所以可以直接返回 ```0```

按上述方法模拟，再给这个搜索的状态加上记忆化。

```cpp
// 预处理可以组成顺子的位置
const bool Kind[35] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 };

ll f[35][5][5][5][2];
// f[i][j][k][l][0 / 1]
// 考虑前 i 种牌，组成 j 个面子，用了 k 个第 i 种牌，l 个第 i + 1 种牌，[是 / 否] 组成了雀头的情况下最大的分数。

inline void CkMax (ll& x, ll y) { x = max (x, y); }

// 计算第 Now 种牌使用了 UsedCnt 个的价值
inline ll Calc (ll Now, ll UsedCnt) { return C[Last[Now]][UsedCnt] * (Dora[Now] ? Pow2[UsedCnt] : 1); }

inline ll DFS (ll Now = 1, ll Pre = 0, ll CntNow = 0, ll CntNxt = 0, bool Couple = false)
{
	// 当前种类或下一种类的牌使用过多，或者面子过多
	if (CntNow > Last[Now] || CntNxt > Last[Now + 1] || Pre > 4) return 0;
	// 当前的牌已经组成了四个面子和一个雀头
	if (Pre == 4 && Couple) return Calc (Now, CntNow) * Calc (Now + 1, CntNxt);
	// 搜索完所有牌
	if (Now == 35) return 0;
	// 记忆化
	if (f[Now][Pre][CntNow][CntNxt][Couple]) return f[Now][Pre][CntNow][CntNxt][Couple];
	ll Ans = 0;
	// 什么都不组成
	CkMax (Ans, DFS (Now + 1, Pre, CntNxt, 0, Couple) * Calc (Now, CntNow));
	// 组成一个刻子
	if (Last[Now] >= CntNow + 3)
		CkMax (Ans, DFS (Now + 1, Pre + 1, CntNxt, 0, Couple) * Calc (Now, CntNow + 3));
	// 前提：能够组成顺子
	if (Kind[Now])
	{
		For (i, 1, 4 - Pre)
			// 组成 i 个顺子
			if (CntNow + i <= Last[Now])
				CkMax (Ans, DFS (Now + 1, Pre + i, CntNxt + i, i, Couple) * Calc (Now, CntNow + i));
			else break; // 如果 i 个不行那么 (i + 1) 个更不行
		// 组成一个刻子和一个顺子
		if (Last[Now] >= CntNow + 4)
			CkMax (Ans, DFS (Now + 1, Pre + 2, CntNxt + 1, 1, Couple) * Calc (Now, CntNow + 4));
	}
	// 前提：没有雀头
	if (!Couple)
	{
		// 组成一个雀头
		if (Last[Now] >= CntNow + 2)
			CkMax (Ans, DFS (Now + 1, Pre, CntNxt, 0, true) * Calc (Now, CntNow + 2));
		// 前提：能够组成顺子
		if (Kind[Now]) For (i, 1, min (2ll, Pre - 4))
		{
			// 组成一个雀头的前提下组成 i 个顺子
			if (CntNow + i + 2 <= Last[Now])
				CkMax (Ans, DFS (Now + 1, Pre + i, CntNxt + i, i, true) * Calc (Now, CntNow + i + 2));
			else break; // 如果 i 个不行那么 (i + 1) 个更不行
		}
	}
	return f[Now][Pre][CntNow][CntNxt][Couple] = Ans;
}
```

你还可以将每次更新封装，这样可以使你的代码更加简洁。

令 ``Update (A, B, C)`` 表示增加 ```A``` 个刻子，```B``` 个顺子，是否增加雀头。

那么更新的答案就是 ```DFS (Now + 1, Pre + A + B, CntNxt + B, B, (!C ? CP : C)) * Calc (Now, CntNow + A * 3 + B + C * 2)```。

```cpp
auto Update = [&](ll A, ll B, bool C = false)
{
	CkMax (Ans, DFS (Now + 1, Pre + A + B, CntNxt + B, B, (!C ? CP : C)) * Calc (Now, CntNow + A * 3 + B + C * 2));
};
```

---

## 作者：黄哟哟哟 (赞：4)

写了3h，查错4h，~~现在跑还来得及~~，
**本题分为四部分**
#### 1. 预处理
没啥好说的，别忘清零且别把不该清零的清零就行。
注意：你可以假设剩下的牌全是一个人的。
#### 2. 七对子
这也不难，就是34种牌枚举一遍，我是排序了一下，选了前七个。
注意由于对子有两张，所以宝牌要乘四。
#### 3. 国士无双
警醒后人：不要以为你过了样例就以为你的国士无双对了。
    先判断一下能不能进去（即十三张牌是否都有）。
    还要判断一下所枚举的牌是否有两张。
#### 4. 3*4+2
最恶心的一部分，得想清楚。简化后就是两个决策：选或不选\
我用的是六维DP
### $f_{i,j,k,l,m,n}$
i 是进行到第几种牌,j 是已经凑出j个面子,k 代表有没有雀头（这一维我放到循环里了）,l 表示当下牌的使用数量,m 和 n 表示后一种、后两种牌的使用数量

------------
三个优化

1.枚举到 dp 值为0的跳过，dp 值为零没有意义。

2.不需要考虑杠。杠换成刻子，四选四与四选三，组合数上优四倍，即使是宝牌乘二也没法弥补组合数上的劣势

3.n 和 m 只枚举到 2。三个顺子完全可以用三个刻子代替。

------------

```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long bpd[2]={1,2};
long long gs[20]={1,9,10,18,19,27,28,29,30,31,32,33,34};
long long jc[20]={0,1,2,6,24,120,720},qt[150],ansqdz=1,gsws[150],ansgsws,true_ansgsws,gswspd,anst;
long long f[36][5][2][5][5][5],dp[36];
long long t,a[150];
bool bao[150];
char k[2];
bool cmp(long long a,long long b){
	return a>b;
}
void pd(char u,char o){
	if(u=='1'&&o=='m')a[1]--;
	if(u=='2'&&o=='m')a[2]--;
	if(u=='3'&&o=='m')a[3]--;
	if(u=='4'&&o=='m')a[4]--;
	if(u=='5'&&o=='m')a[5]--;
	if(u=='6'&&o=='m')a[6]--;
	if(u=='7'&&o=='m')a[7]--;
	if(u=='8'&&o=='m')a[8]--;
	if(u=='9'&&o=='m')a[9]--;
	if(u=='1'&&o=='p')a[10]--;
	if(u=='2'&&o=='p')a[11]--;
	if(u=='3'&&o=='p')a[12]--;
	if(u=='4'&&o=='p')a[13]--;
	if(u=='5'&&o=='p')a[14]--;
	if(u=='6'&&o=='p')a[15]--;
	if(u=='7'&&o=='p')a[16]--;
	if(u=='8'&&o=='p')a[17]--;
	if(u=='9'&&o=='p')a[18]--;
	if(u=='1'&&o=='s')a[19]--;
	if(u=='2'&&o=='s')a[20]--;
	if(u=='3'&&o=='s')a[21]--;
	if(u=='4'&&o=='s')a[22]--;
	if(u=='5'&&o=='s')a[23]--;
	if(u=='6'&&o=='s')a[24]--;
	if(u=='7'&&o=='s')a[25]--;
	if(u=='8'&&o=='s')a[26]--;
	if(u=='9'&&o=='s')a[27]--;
	if(u=='E')a[28]--;
	if(u=='S')a[29]--;
	if(u=='W')a[30]--;
	if(u=='N')a[31]--;
	if(u=='Z')a[32]--;
	if(u=='B')a[33]--;
	if(u=='F')a[34]--;
}
void pb(char u,char o){
	if(u=='1'&&o=='m')bao[1]=1;
	if(u=='2'&&o=='m')bao[2]=1;
	if(u=='3'&&o=='m')bao[3]=1;
	if(u=='4'&&o=='m')bao[4]=1;
	if(u=='5'&&o=='m')bao[5]=1;
	if(u=='6'&&o=='m')bao[6]=1;
	if(u=='7'&&o=='m')bao[7]=1;
	if(u=='8'&&o=='m')bao[8]=1;
	if(u=='9'&&o=='m')bao[9]=1;
	if(u=='1'&&o=='p')bao[10]=1;
	if(u=='2'&&o=='p')bao[11]=1;
	if(u=='3'&&o=='p')bao[12]=1;
	if(u=='4'&&o=='p')bao[13]=1;
	if(u=='5'&&o=='p')bao[14]=1;
	if(u=='6'&&o=='p')bao[15]=1;
	if(u=='7'&&o=='p')bao[16]=1;
	if(u=='8'&&o=='p')bao[17]=1;
	if(u=='9'&&o=='p')bao[18]=1;
	if(u=='1'&&o=='s')bao[19]=1;
	if(u=='2'&&o=='s')bao[20]=1;
	if(u=='3'&&o=='s')bao[21]=1;
	if(u=='4'&&o=='s')bao[22]=1;
	if(u=='5'&&o=='s')bao[23]=1;
	if(u=='6'&&o=='s')bao[24]=1;
	if(u=='7'&&o=='s')bao[25]=1;
	if(u=='8'&&o=='s')bao[26]=1;
	if(u=='9'&&o=='s')bao[27]=1;
	if(u=='E')bao[28]=1;
	if(u=='S')bao[29]=1;
	if(u=='W')bao[30]=1;
	if(u=='N')bao[31]=1;
	if(u=='Z')bao[32]=1;
	if(u=='B')bao[33]=1;
	if(u=='F')bao[34]=1;
}
long long C[5][5]{
	1,1,1,1,1,
	0,1,2,3,4,
	0,0,1,3,6,
	0,0,0,1,4,
	0,0,0,0,1
};
void work(){
	
	//七对子 
	for(int i=1;i<=34;i++){
		if(a[i]>=2){
			qt[i]=C[2][a[i]];
			if(bao[i])qt[i]*=4;
		}
	}
	sort(qt+1,qt+34+1,cmp);
	for(int i=1;i<=7;i++){
		ansqdz*=qt[i];
	}
	ansqdz*=7;
	
	//国士无双
	gswspd=1;
	for(int i=0;i<13;i++){
		if(!a[gs[i]])gswspd=0;
	}
	if(gswspd){
		for(int i=0;i<13;i++){
			if(a[gs[i]]<2)continue;
			ansgsws=1;
			for(int j=0;j<13;j++){
				if(i==j){
					gsws[j]=C[2][a[gs[j]]]*bpd[bao[gs[j]]]*bpd[bao[gs[j]]];
				}
				else{
					gsws[j]=C[1][a[gs[j]]]*bpd[bao[gs[j]]];
				}
			}
			for(int i=0;i<13;i++){
				ansgsws*=gsws[i];
			}
			true_ansgsws=max(true_ansgsws,ansgsws);
		}
		true_ansgsws*=13;
	} 
	
	//3*4+2
	f[1][0][0][0][0][0]=1;
	for(int i=1;i<=34;i++){
		for(int j=0;j<=4;j++){
			for(int l=0;l<=4;l++){
				for(int m=0;m<=2;m++){
					for(int n=0;n<=2;n++){
						if(!f[i][j][0][l][m][n]&&!f[i][j][1][l][m][n])continue;
						if(a[i]-l>=2){
							f[i][j][1][l+2][m][n]=max(f[i][j][1][l+2][m][n],f[i][j][0][l][m][n]*C[l+2][a[i]]/C[l][a[i]]*bpd[bao[i]]*bpd[bao[i]]);
						}
						if(j<4){
							if((m!=2&&n!=2)&&(a[i]-l>0)&&(a[i+1]-m>0)&&(a[i+2]-n>0)&&((1<=i&&i<=7)||(10<=i&&i<=16)||(19<=i&&i<=25))){
								f[i][j+1][0][l+1][m+1][n+1]=max(f[i][j+1][0][l+1][m+1][n+1],f[i][j][0][l][m][n]*C[l+1][a[i]]*C[m+1][a[i+1]]*C[n+1][a[i+2]]*bpd[bao[i]]*bpd[bao[i+1]]*bpd[bao[i+2]])/C[l][a[i]]/C[m][a[i+1]]/C[n][a[i+2]];
								f[i][j+1][1][l+1][m+1][n+1]=max(f[i][j+1][1][l+1][m+1][n+1],f[i][j][1][l][m][n]*C[l+1][a[i]]*C[m+1][a[i+1]]*C[n+1][a[i+2]]*bpd[bao[i]]*bpd[bao[i+1]]*bpd[bao[i+2]])/C[l][a[i]]/C[m][a[i+1]]/C[n][a[i+2]];
							}
							if(a[i]-l>=3){
								f[i][j+1][0][l+3][m][n]=max(f[i][j+1][0][l+3][m][n],f[i][j][0][l][m][n]/C[l][a[i]]*C[l+3][a[i]]*bpd[bao[i]]*bpd[bao[i]]*bpd[bao[i]]);
								f[i][j+1][1][l+3][m][n]=max(f[i][j+1][1][l+3][m][n],f[i][j][1][l][m][n]/C[l][a[i]]*C[l+3][a[i]]*bpd[bao[i]]*bpd[bao[i]]*bpd[bao[i]]);
							
							}
						}
						f[i+1][j][0][m][n][0]=max(f[i+1][j][0][m][n][0],f[i][j][0][l][m][n]); 
						f[i+1][j][1][m][n][0]=max(f[i+1][j][1][m][n][0],f[i][j][1][l][m][n]);
						if(j==4){
							dp[i]=max(dp[i],f[i][j][1][l][m][n]);
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=34;i++){
		anst=max(anst,dp[i]);
	}	
}
void init(){
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));//清零，重点检查 
		memset(bao,0,sizeof(bao));
		true_ansgsws=0;ansqdz=1;anst=0; 
		memset(gsws,0,sizeof(gsws));
		memset(qt,0,sizeof(qt));
		memset(dp,0,sizeof(dp));
		memset(f,0,sizeof(f));
		for(int i=1;i<=34;i++){
			a[i]=4;
		}
		cin>>k;
		while(k[0]!='0'){
			pd(k[0],k[1]);
			cin>>k;
		}
		cin>>k;
		while(k[0]!='0'){
			pb(k[0],k[1]);
			cin>>k;
		}
		work();
		cout<<max(max(true_ansgsws,ansqdz),anst)<<endl;
	}
}
int main(){
	init();
	return 0;
}
```





---

## 作者：cirnovsky (赞：4)

## Description

[Link](https://www.luogu.com.cn/problem/P5301).

Summarizing the fking statement is the last thing in the world I ever want to do.

## Solution

FFT 学不懂来写麻将 DP。

我们来重新描述一些概念：

- 数字牌：筒条万。
- 顺子：$3$ 张连续的数字牌。（面子）
- 雀头：$2$ 张完全一样的牌。
- 刻子：$3$ 张完全一样的牌。（面子）
- 杠子：$4$ 张完全一样的牌。

看起来好看了一点。

观察发现：杠子在除了 $14$ 张牌胡牌情况以外的胡牌情况都出现了，于是又发现：$\binom{4}{3}>\binom{4}{4}$；

于是：

- 对于胡牌的形式，我们只需要考虑「$3\times4+2$」「七对子」和「国士无双」。

于是我们只需要三种情况取最大即可。

1. 「七对子」只需要把所有牌型的贡献拉出来，取前 $7$ 个最大的乘起来即可。

2. 「国士无双」枚举谁来做 $2$ 个的那个，然后取最大。

3. 「$3\times4+2$」

$\qquad$ 考虑这样一个 DP，设：$f(i,j,k,a,b,c)$ 为前 $i$ 个数，$j$ 个面子，$k$ 个雀头，第 $i$ / $i+1$ / $i+2$ 张牌用了 $a$ / $b$ / $c$ 张的最优答案（$k\in\{0,1\}$）。

$\qquad$ $\qquad$ 1. 对于雀头：

$$
f(i,j,1,a+2,b,c)=\max\{\frac{f(i,j,0,a,b,c)\times\text{calc}(i,a+2)}{\text{calc}(i,a)}\}
$$

$\qquad$ $\qquad$ $\qquad$ 其中 $\text{calc}(x,y)$ 为第 $x$ 张牌，在手牌中需要出现 $y$ 次，此时对答案的贡献。

$\qquad$ $\qquad$ $\qquad$ 方程的意义即：去掉把第 $i$ 种牌之前的贡献，再算上现在算作雀头的贡献。

$\qquad$ $\qquad$ 2. 对于刻子：

$$
f(i,j+1,0\text{ or }1,a+3,b,c)=\max\{\frac{f(i,j,0\text{ or }1,a,b,c)\times\text{calc}(i,a+3)}{\text{calc}(i,a)}\}
$$

$\qquad$ $\qquad$ $\qquad$ 基本同上。

$\qquad$ $\qquad$ 3. 对于顺子：

$$
f(i,j+1,0\text{ or }1,a+1,b+1,c+1)=\max\{\frac{f(i,j,0\text{ or }1,a,b,c)\times\text{calc}(i,a+1)\times\text{calc}(i+1,b+1)\times\text{calc}(i+2,c+1)}{\text{calc}(i,a)\times\text{calc}(i+1,b)\times\text{calc}(i+2,c)}\}
$$

$\qquad$ $\qquad$ $\qquad$ 完全同理。

然后就完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL koshi[15]={0,1,9,10,18,19,27,28,29,30,31,32,33,34}; // the cards that Kokushimusou needs
const bool chunko[36]={0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1}; // the cards which are able to be jyunko
LL getCard()
{
	static char s[10];
	scanf("%s",s+1);
	if(s[1]=='0')	return -1;
	else if(!isdigit(s[1]))
	{
		if(s[1]=='E')	return 28;
		else if(s[1]=='S')	return 29;
		else if(s[1]=='W')	return 30;
		else if(s[1]=='N')	return 31;
		else if(s[1]=='Z')	return 32;
		else if(s[1]=='B')	return 33;
		else	return 34;
	}
	else
	{
		if(s[2]=='m')	return s[1]-'0';
		else if(s[2]=='p')	return s[1]-'0'+9;
		else	return s[1]-'0'+18;
	}
}
LL t,comb[10][10],cnt[40],trs[40],f[40][5][5][5][5][5];
#define calc(x,f) (((cnt[x])<(f)?0:comb[cnt[x]][f])*(trs[x]?(1<<(f)):1))
LL onesolve() // Seven Pairs
{
	vector<LL> pri;
	for(LL i=1;i<=34;++i)	if(cnt[i]>=2)	pri.push_back(calc(i,2));
	sort(pri.begin(),pri.end(),greater<LL>());
	if(pri.size()<size_t(7))	return 0;
	else
	{
		LL res=7;
		for(LL i=0;i<7;++i)	res*=pri[i];
		return res;
	}
}
LL anosolve() // Kokushimusou
{
	LL flag=0;
	for(LL i=1;i<=13;++i)
	{
		if(cnt[koshi[i]]>=2)	flag=1;
		if(cnt[koshi[i]]==0)	return 0;
	}
	if(flag)
	{
		LL res=0;
		for(LL i=1;i<=13;++i)
		{
			LL tmp=13;
			if(cnt[koshi[i]]>=2)
			{
				for(LL j=1;j<=13;++j)	tmp*=calc(koshi[j],(i==j)+1);
			}
			res=max(res,tmp);
		}
		return res;
	}
	else	return 0;
}
void getmax(LL &one,LL ano){one=max(one,ano);}
LL exsolve() // 3x4+2
{
	#define f(i,j,k,a,b,c) (f[i][j][k][a][b][c])
	f(1,0,0,0,0,0)=1;
	for(LL i=1;i<=34;++i)
	{
		for(LL j=0;j<=4;++j)
		{
			for(LL a=0;a<=4;++a)
			{
				for(LL b=0;b<=2;++b)
				{
					for(LL c=0;c<=2;++c)
					{
						if(cnt[i]-a>=2)	getmax(f(i,j,1,a+2,b,c),f(i,j,0,a,b,c)/calc(i,a)*calc(i,a+2));
						if(j^4)
						{
							if(cnt[i]-a>=3)
							{
								getmax(f(i,j+1,0,a+3,b,c),f(i,j,0,a,b,c)/calc(i,a)*calc(i,a+3));
								getmax(f(i,j+1,1,a+3,b,c),f(i,j,1,a,b,c)/calc(i,a)*calc(i,a+3));
							}
							if(chunko[i]&&cnt[i]-a>=1&&cnt[i+1]-b>=1&&cnt[i+2]-c>=1&&(b^2)&&(c^2))
							{
								getmax(f(i,j+1,0,a+1,b+1,c+1),f(i,j,0,a,b,c)/calc(i,a)/calc(i+1,b)/calc(i+2,c)*calc(i,a+1)*calc(i+1,b+1)*calc(i+2,c+1));
								getmax(f(i,j+1,1,a+1,b+1,c+1),f(i,j,1,a,b,c)/calc(i,a)/calc(i+1,b)/calc(i+2,c)*calc(i,a+1)*calc(i+1,b+1)*calc(i+2,c+1));
							}
						}
						getmax(f(i+1,j,0,b,c,0),f(i,j,0,a,b,c));
						getmax(f(i+1,j,1,b,c,0),f(i,j,1,a,b,c));
					}
				}
			}
		}
	}
	LL res=0;
	for(LL i=1;i<=34;++i)
	{
		for(LL a=0;a<=4;++a)
		{
			for(LL b=0;b<=2;++b)
			{
				for(LL c=0;c<=2;++c)	getmax(res,f(i,4,1,a,b,c));
			}
		}
	}
	#undef f
	return res;
}
int main()
{
	for(LL i=0;i<=4;++i)	comb[i][0]=comb[i][i]=1;
	for(LL i=1;i<=4;++i)	for(LL j=1;j<i;++j)	comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
	scanf("%lld",&t);
	while(t--)
	{
		memset(f,0,sizeof(f));
		for(LL i=1;i<=34;++i)	cnt[i]=4,trs[i]=0;
		LL tmp=getCard();
		while(~tmp)	--cnt[tmp],tmp=getCard();
		tmp=getCard();
		while(~tmp)	trs[tmp]=1,tmp=getCard();
		printf("%lld\n",max(max(onesolve(),anosolve()),exsolve()));
	}
	return 0;
}
```

---

## 作者：FjswYuzu (赞：2)

$\ \ \ \ \ \ \ $[luogu](https://www.luogu.com.cn/problem/P5301)，同步于[动态规划100题17题](https://www.luogu.com.cn/blog/blog10086001/dong-tai-gui-hua-100-ti)，随缘更新。

$\ \ \ \ \ \ \ $作为一个颓雀魂的想做一下麻将题，发现 ZJOI 的麻将题过于毒瘤，这个反而比较简单。

$\ \ \ \ \ \ \ $考虑到只有刻子/顺子/杠子/雀头，面子与雀头只跟当前牌，下一张牌，下下张牌有关系，其他需要注意的有组成了多少个面子，有没有雀头。考虑到将这五个东西联合当前牌是什么塞进 dp 中。但是我们很快发现在这个模式下杠了牌就是[杠精](https://zh.moegirl.org/%E6%97%A5%E6%9C%AC%E9%BA%BB%E5%B0%86:%E6%9D%A0%E7%B2%BE)，原因是 $C_4^3=4C_4^4$。即使这张牌是 dora 也无济于事，没有用。~~（杠杠杠，杠出新天地，杠出宝牌一大堆）~~

$\ \ \ \ \ \ \ $现在考虑到这六维的信息。定义 $dp_{i,,j1 \ or \ 0,k,l,o}$ 为在第 $i$ 张牌（共有 34 张牌），组成的牌中有没有雀头，组成了 $j$ 个面子，$i$ 张牌用了 $k$ 张，第 $i+1$ 张牌用了 $l$ 张，$i+2$ 用了 $o$ 张，分有无雀头两边 dp，分情况讨论新组成顺子，新组成刻子，新组成雀头就OK了。

$\ \ \ \ \ \ \ $定义 $dp_{i,j,0 \ or \ 1 ,k,l,o}$ 为选到 $i$ 张牌，组成 $j$ 刻子，有无雀头，$i$ 张牌用了 $k$ 张，$i+1$ 用了 $l$ 张，$i+2$ 用了 $o$ 张。对有无雀头分别 dp，考虑新增雀头/刻子/顺子讨论即可。

$\ \ \ \ \ \ \ $超时了，考虑优化：

- $l \leq 2,o \leq 2$。这是因为当 $l>2$ 时，它是一个刻子，更别说 $l>2,o>2$ 了，这直接是一个三连刻好吗？（你听说过三连刻没有.jpg，古役，两番？）；（优化 1）

- 组合数打表计算，不要直接计算；（优化 2）

- 如果当前 dp 值为 0，直接 `continue`，这是因为你之前组成的牌胡不了。。（优化 3）

$\ \ \ \ \ \ \ $七对子贪心选择贡献最大的七个对子，国士无双（三大民工役满之一，剩下为大三元和四暗刻）枚举哪一张用两次，$O(169)$ 枚举就 OK。

$\ \ \ \ \ \ \ $看不懂就领略一下精神就好了。。。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
#define mahjongMaxn 35
using namespace std;
const int initC[7][7]=
{
	{1,0,0,0,0},
	{1,1,0,0,0},
	{1,2,1,0,0},
	{1,3,3,1,0},
	{1,4,6,4,1}
};//一定要做的事
void write(long long t)
{
	if(t<0)	putchar('-'),t=-t;
	if(t>9)	write(t/10);
	putchar('0'+t%10);
}
const int Kin[]={0,1,9,10,18,19,27,28,29,30,31,32,33,34};//国士无双需要的牌，Kokushimusou in need
const bool shien[]={0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};//能做顺子开头的牌
int rest[mahjongMaxn+5],isDora[mahjongMaxn+5];//剩下多少张以及是否是 dora
long long dp[mahjongMaxn+5][6][4][6][4][4];
int C(int x,int y){return initC[x][y];}//可以换成正常计算（优化 2）
int mahjong(char x)
{
	switch (x)
	{
		case 'E':	return 28;
		case 'S':	return 29;
		case 'W':	return 30;
		case 'N':	return 31;
		case 'Z':	return 32;
		case 'B':	return 33;
		case 'F':	return 34;
	}
	return 10086001;
}
int mahjong(char x,char y)
{
	switch (y)
	{
		case 'm':	return x-'0';
		case 'p':	return 9+x-'0';
		case 's':	return 18+x-'0';
	}
	return 10086001;
}//输入，返回麻将标号
long long Kokushimusou()
{
	for(int i=1;i<=13;++i)	if(!rest[Kin[i]])	return 0;
	long long ans=0;
	for(int i=1;i<=13;++i)
	{
		long long tmp=C(rest[Kin[i]],2)*isDora[Kin[i]]*isDora[Kin[i]]*13;
		for(int j=1;j<=13;++j)	if(i!=j)	tmp*=isDora[Kin[j]]*rest[Kin[j]];
		ans=max(ans,tmp);
	}
	return ans;
}//国士无双
long long Chitoicu()
{
	long long ans=7;
	priority_queue<long long> PQ;
	for(int i=1;i<=mahjongMaxn-1;++i)	PQ.push(isDora[i]*isDora[i]*C(rest[i],2));
	if(PQ.size()<7)	return 0;
	for(int i=1;i<=7;++i)	ans*=PQ.top(),PQ.pop();
	return ans;
}//七对子
long long OthersDP(){
	long long ans=0;
	dp[1][0][0][0][0][0]=1;
	for(int i=1;i<=mahjongMaxn-1;++i)
	{
		for(int j=0;j<=4;++j)
		{
			for(int k=0;k<=4;++k)
			{
				for(int l=0;l<=2;++l)
				{
					for(int o=0;o<=2;++o)//（优化 1）
					{
						long long kc1=dp[i][j][0][k][l][o],kc2=dp[i][j][1][k][l][o];
						if(!kc1 && !kc2)	continue;//（优化 3）
						if(rest[i]-k>=2)	dp[i][j][1][k+2][l][o]=max(dp[i][j][1][k+2][l][o],kc1/C(rest[i],k)*C(rest[i],k+2)*isDora[i]*isDora[i]);//新雀头
						if(j<4)
						{
							if(rest[i]-k>=3)
								dp[i][j+1][0][k+3][l][o]=
								max(dp[i][j+1][0][k+3][l][o],
								kc1/C(rest[i],k)*C(rest[i],k+3)*isDora[i]*isDora[i]*isDora[i]),
								dp[i][j+1][1][k+3][l][o]=
								max(dp[i][j+1][1][k+3][l][o],
								kc2/C(rest[i],k)*C(rest[i],k+3)*isDora[i]*isDora[i]*isDora[i]);//新刻子
							if(shien[i] && rest[i]>k && rest[i+1]>l && rest[i+2]>o && l!=2 && o!=2)
								dp[i][j+1][0][k+1][l+1][o+1]=max(dp[i][j+1][0][k+1][l+1][o+1],
								kc1
								/C(rest[i],k)*C(rest[i],k+1)*isDora[i]
								/C(rest[i+1],l)*C(rest[i+1],l+1)*isDora[i+1]
								/C(rest[i+2],o)*C(rest[i+2],o+1)*isDora[i+2]),
								dp[i][j+1][1][k+1][l+1][o+1]=max(dp[i][j+1][1][k+1][l+1][o+1],
								kc2
								/C(rest[i],k)*C(rest[i],k+1)*isDora[i]
								/C(rest[i+1],l)*C(rest[i+1],l+1)*isDora[i+1]
								/C(rest[i+2],o)*C(rest[i+2],o+1)*isDora[i+2]);//新顺子
						}
						dp[i+1][j][0][l][o][0]=max(dp[i+1][j][0][l][o][0],kc1);
						dp[i+1][j][1][l][o][0]=max(dp[i+1][j][1][l][o][0],kc2);//自身状态继承下一状态
						if(j==4) ans=max(ans,kc2);//四个刻子和一个雀头就以经胡牌，保存答案
					}
				}
			}
		}
	}
	return ans;
}
void Prepare()
{
	fill(rest,rest+mahjongMaxn,4);
	fill(isDora,isDora+mahjongMaxn,1);
	memset(dp,0,sizeof dp);
}
void ReadMahjongRiver()
{
	char s[2];
	while(scanf("%s",s))
	{
		if(s[0]=='0')	return ;
		if(s[1]=='\0')	--rest[mahjong(s[0])];
		else	--rest[mahjong(s[0],s[1])];
	}
}
void ReadDora()
{
	char s[2];
	while(scanf("%s",s))
	{
		if(s[0]=='0')	return ;
		if(s[1]=='\0')	isDora[mahjong(s[0])]=2;
		else	isDora[mahjong(s[0],s[1])]=2;
	}
}//Input
int main(){
	long long T;
	scanf("%lld",&T);
	while(T-->0)
	{
		Prepare();
		ReadMahjongRiver();
		ReadDora();
		write(max({Chitoicu(),Kokushimusou(),OthersDP()}));//C++11标准
		puts("");
	}
	return 0;
}
```

---

## 作者：crashed (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/P5301)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本题思路——~~语文阅读+~~ $DP$+贪心  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先，你要把题目读懂。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后考虑「七对子」和「国士无双」。「七对子」显然是每次选择贡献最大的一种牌加入到手牌中；「国士无双」就直接暴力枚举哪一种牌会选$2$次。   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果我们把杠子看作是面子的话，正常的胡牌就是「$3\times 4+2$」的结构。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑$DP$: 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i,j,k,a,b,c)$：前$i$种牌，组成了$j$副面子，$k$副雀头，$i-2$种牌使用了$a$张，$i-1$种牌使用了$b$张，$i$种牌使用了$c$张，此时**前$i-1$种牌的最大贡献**。   

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;转移分情况：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$1.$雀头：  
$$f(i,j,k+1,a,b,c+2)=f(i,j,k,a,b,c)$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$2.$刻子：  
$$f(i,j+1,k,a,b,c+3)=f(i,j,k,a,b,c)$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$3.$杠子：  
$$f(i,j+1,k,a,b,c+4)=f(i,j,k,a,b,c)$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~前三种都很像~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$4.$顺子：  
$$f(i,j+1,k,a+1,b+1,c+1)=f(i,j,k,a,b,c)\times \frac{C_{cnt_{i-2}}^{a+1}}{C_{cnt_{i-2}}^a}\times\frac{C_{cnt_{i-1}}^{b+1}}{C_{cnt_{i-1}}^b}\times combo_a\times combo_b$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$5.$隔空转移（雾）：  
$$f(i+1,j,k,b,c,0)=f(i,j,k,a,b,c)\times C_{cnt_{i}}^c\times combo_{i}^c$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;以上的特殊定义的解释：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$C$：组合数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$cnt_i$：第$i$种牌的未打出数量。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$combo_i$：第$i$种牌的额外贡献。可以理解为如果$i$是宝牌就为$2$，否则为$1$。    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;答案统计：  
$$\max_{j=4,k=1} \{f(i,j,k,a,b,c)\times C_{cnt_i}^c\times combo_{i}^c\}$$

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然而，交上去一发之后你会发现自己$T$了，于是考虑优化：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$1.$遇到$f$为$0$的状态直接放弃转移，反正都是不合法的牌型。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$2.$三个刻子和三个顺子实际上可以通过打乱顺序互相换（$(3,4,5)\times3 \Leftrightarrow (3,3,3)+(4,4,4)+(5,5,5)$），所以有一些状态是不必要的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$3.$~~没啥用的优化~~  杠子没有刻子好。因为杠子的数量最多为$1$，刻子的数量则不然。假如这种牌是宝牌，组合数会给刻子带来$4$的“额外贡献”，然而杠子只会因为宝牌得到$2$的额外贡献。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;总时间上界是$O(T\times34\times5^4\times 2)$，但是不会$T$。很多不合法的状态都被弃掉了。  
# 代码
```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
   	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

priority_queue<int> q;

LL f[50][5][2][5][5][5];
LL ans = 0;
int cnt[50] = {}, combo[50] = {};
int GSWSCard[14] = { 0, 1, 9, 10, 18, 19, 27, 28, 29, 30, 31, 32, 33, 34 };
int C[5][5] = {};
bool sz[50] = { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 };

void upt( LL &x, const LL y ) { x = MAX( x, y ); }

void init()
{
	C[0][0] = 1; 
	for( int i = 1 ; i <= 5 ; i ++ )
	{
		C[i][0] = C[i][i] = 1;
		for( int j = 1 ; j < i ; j ++ ) C[i][j] = ( C[i - 1][j] + C[i - 1][j - 1] );
	}
}

void GSWS()
{
	LL score;
	for( int i = 1 ; i <= 13 ; i ++ )
	{
		score = 13 * C[cnt[GSWSCard[i]]][2] * combo[GSWSCard[i]] * combo[GSWSCard[i]];
		for( int j = 1 ; j <= 13 ; j ++ ) if( i ^ j ) score *= C[cnt[GSWSCard[j]]][1] * combo[GSWSCard[j]];
		ans = MAX( ans, score );
	}
}

void QDZ()
{
	LL res = 7;
	int tot = 0;
	while( ! q.empty() ) q.pop();
	for( int i = 1 ; i <= 34 ; i ++ ) q.push( C[cnt[i]][2] * combo[i] * combo[i] );
	while( ! q.empty() && tot < 7 ) tot ++, res *= q.top(), q.pop();
	if( tot == 7 ) ans = MAX( ans, res );
}

int label( char *s ) 
{
	if( s[0] == 'E' ) return 28;
	if( s[0] == 'S' ) return 29;
	if( s[0] == 'W' ) return 30;
	if( s[0] == 'N' ) return 31;
	if( s[0] == 'Z' ) return 32;
	if( s[0] == 'B' ) return 33;
	if( s[0] == 'F' ) return 34;
	if( s[1] == 'm' ) return s[0] - '0';
	if( s[1] == 'p' ) return s[0] - '0' + 9;
	if( s[1] == 's' ) return s[0] - '0' + 18;
}

void clear() 
{
	ans = 0;
	for( int i = 1 ; i <= 34 ; i ++ ) cnt[i] = 4, combo[i] = 1;
	for( int i = 1 ; i <= 34 ; i ++ )
		for( int j = 0 ; j < 5 ; j ++ )
			for( int k = 0 ; k < 2 ; k ++ )
				for( int a = 0 ; a < 5 ; a ++ )
					for( int b = 0 ; b < 5 ; b ++ )
						for( int c = 0 ; c < 5 ; c ++ )
							f[i][j][k][a][b][c] = 0;
}

int comb( const int indx, const int x ) { return pow( combo[indx], x ); }

int main()
{
	LL cur;
	int T;
	char s[5];
	init();
	read( T );
	while( T -- )
	{
		clear();
		while( true )
		{
			scanf( "%s", s ); 
			if( s[0] == '0' ) break; 
			cnt[label( s )] --;
		}
		while( true )
		{
			scanf( "%s", s );
			if( s[0] == '0' ) break;
			combo[label( s )] = 2;
		}
		GSWS();
		QDZ();
		f[1][0][0][0][0][0] = 1;
		for( int i = 1 ; i <= 34 ; i ++ )
			for( int j = 0 ; j < 5 ; j ++ )
				for( int k = 0 ; k < 2 ; k ++ )
					for( int a = 0 ; a < 5 ; a ++ )
						for( int b = 0 ; b < 5 ; b ++ )
							for( int c = 0 ; c < 5 ; c ++ )
							{
								if( ! f[i][j][k][a][b][c] ) continue;
								cur = f[i][j][k][a][b][c];
								if( ! k && cnt[i] - c >= 2 ) 
									upt( f[i][j][1][a][b][c + 2], cur );
								if( j < 4 && cnt[i] - c >= 3 )
									upt( f[i][j + 1][k][a][b][c + 3], cur );
								if( j < 4 && cnt[i] - c >= 4 )
									upt( f[i][j + 1][k][a][b][c + 4], cur );
								if( sz[i] && j < 4 && cnt[i - 2] - a >= 1 && cnt[i - 1] - b >= 1 && cnt[i] - c >= 1 )
									upt( f[i][j + 1][k][a + 1][b + 1][c + 1], 
										 cur / C[cnt[i - 2]][a] * C[cnt[i - 2]][a + 1] / C[cnt[i - 1]][b] * C[cnt[i - 1]][b + 1] * 
										 combo[i - 2] * combo[i - 1] );
								if( i < 34 ) upt( f[i + 1][j][k][b][c][0], cur * C[cnt[i]][c] * comb( i, c ) );
								if( j == 4 && k == 1 ) upt( ans, cur * C[cnt[i]][c] * comb( i, c ) );
							}
		write( ans ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：xht (赞：2)

题目地址：[P5301 [GXOI/GZOI2019]宝牌一大堆](https://www.luogu.org/problemnew/show/P5301)

这里是官方题解（by lydrainbowcat）

### 部分分

直接搜索可以得到暴力分，因为所有和牌方案一共只有一千万左右，稍微优化一下数据少的测试点可以跑过

$3$ ~ $7$ 已经打出的，不需要考虑顺子，可以跟七对子类似直接算

### 正解

预处理组合数

**DP** 计算 $3*4+2$ ：

前 $i$ 种牌，选了 $j$ 组面子， $k$ 组雀头，其中第 $i - 2$ ~ $i$ 种牌分别选了 $l,m,n$ 张时，前 $i - 3$ 种牌可以获得的最大价值

转移：刻子、顺子、杠子、雀头四个转移，详见 **std** 中 **calc_normal** 函数的注释

直接计算七对子、国士无双

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
// 1m 2m ... 9m 1p 2p ... 9p 1s 2s ... 9s E S W N Z B F
const bool shuntsu[35] = { 0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0 };
const int yao[13] = { 1,9,10,18,19,27,28,29,30,31,32,33,34 };
int a[35], b[35], c[5][5], d[35];
long long f[35][5][2][5][5][5], chitoi[35][8], ans;

int label(char str[3]) {
	if (str[0] == 'E') return 28;
	if (str[0] == 'S') return 29;
	if (str[0] == 'W') return 30;
	if (str[0] == 'N') return 31;
	if (str[0] == 'Z') return 32;
	if (str[0] == 'B') return 33;
	if (str[0] == 'F') return 34;
	if (str[1] == 'm') return str[0] - '0';
	if (str[1] == 'p') return 9 + str[0] - '0';
	if (str[1] == 's') return 18 + str[0] - '0';
	return 0;
}

inline void update(long long &dst, long long src) {
	dst = max(dst, src);
}

inline int dora(int idx, int cnt) {
	return d[idx] ? 1 << cnt : 1;
}

long long calc_normal() {
	long long ret = 0;
	memset(f, 0, sizeof(f));
	f[1][0][0][0][0][0] = 1;
	// 前i种牌，选了j组面子，k组雀头，其中第i-2~i种牌分别选了l,m,n张时，前i-3种牌可以获得的最大价值
	for (int i = 1; i <= 34; i++)
		for (int j = 0; j <= 4; j++)
			for (int k = 0; k <= 1; k++)
				for (int l = 0; l <= 4; l++)
					for (int m = 0; m <= 4; m++)
						for (int n = 0; n <= 4; n++) {
							long long now;
							if ((now = f[i][j][k][l][m][n]) == 0) continue;
							// 去选下一种牌
							if (i < 34)
								update(f[i + 1][j][k][m][n][0], now * (i > 2 ? c[a[i - 2]][l] : 1) * dora(i - 2, l));
							// 组成刻子
							if (j < 4 && a[i] - n >= 3)
								update(f[i][j + 1][k][l][m][n + 3], now);
							// 组成杠子，杠子也可以算作面子来统计
							if (j < 4 && a[i] - n >= 4)
								update(f[i][j + 1][k][l][m][n + 4], now);
							// 组成顺子
							if (j < 4 && shuntsu[i] && a[i] - n && a[i - 1] - m && a[i - 2] - l)
								update(f[i][j + 1][k][l + 1][m + 1][n + 1], now);
							// 组成雀头
							if (k < 1 && a[i] - n >= 2)
								update(f[i][j][k + 1][l][m][n + 2], now);
							if (i == 34 && j == 4 && k == 1)
								update(ret, now * c[a[i]][n] * c[a[i - 1]][m] * c[a[i - 2]][l] * dora(i, n) * dora(i - 1, m) * dora(i - 2, l));
						}
	return ret;
}

long long calc_chitoi() {
	memset(chitoi, 0, sizeof(chitoi));
	chitoi[0][0] = 1;
	for (int i = 1; i <= 34; i++)
		for (int j = 0; j <= 7; j++) {
			if (chitoi[i - 1][j] == 0) continue;
			update(chitoi[i][j], chitoi[i - 1][j]);
			if (j < 7) update(chitoi[i][j + 1], chitoi[i - 1][j] * c[a[i]][2] * dora(i, 2));
		}
	return chitoi[34][7] * 7;
}

long long calc_kokushi() {
	long long ret = 0;
	for (int i = 0; i < 13; i++) {
		if (a[yao[i]] == 0) return 0;
		if (a[yao[i]] == 1) continue;
		long long temp = c[a[yao[i]]][2] * dora(yao[i], 2);
		for (int j = 0; j < 13; j++) {
			if (i == j) continue;
			temp = temp * a[yao[j]] * dora(yao[j], 1);
		}
		update(ret, temp * 13);
	}
	return ret;
}

/*void dfs(int x, int m, int n) {
	if (m == 4 && n == 1 || m == 0 && n == 7) {
		long long temp = n;
		for (int i = 1; i <= 34; i++)
			if (a[i] < b[i]) temp = temp * c[b[i]][b[i] - a[i]] * dora(i, b[i] - a[i]);
		update(ans, temp);
		return;
	}
	if (x > 34) return;
	if (n > 1 && m) return;
	dfs(x + 1, m, n);
	if (m < 4 && a[x] >= 4) { // 杠
		a[x] -= 4;
		dfs(x, m + 1, n);
		a[x] += 4;
	}
	if (m < 4 && a[x] >= 3) { // 刻
		a[x] -= 3;
		dfs(x, m + 1, n);
		a[x] += 3;
	}
	if (n < 1 && a[x] >= 2) { // 雀头
		a[x] -= 2;
		dfs(x, m, n + 1);
		a[x] += 2;
	}
	if (m<= 4 && shuntsu[x] && a[x] && a[x - 1] && a[x - 2]) { // 顺子
		a[x] -= 1, a[x - 1] -= 1, a[x - 2] -= 1;
		dfs(x, m + 1, n);
		a[x] += 1, a[x - 1] += 1, a[x - 2] += 1;
	}
	if (m == 0 && a[x] >= 2 && n > 0 && n < 7) {
		a[x] -= 2;
		dfs(x + 1, m, n + 1);
		a[x] += 2;
	}
}*/

int main() {
	for (int i = 0; i <= 5; i++) c[i][0] = 1;
	for (int i = 1; i <= 5; i++)
		for (int j = 1; j <= 5; j++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	char str[3];
	int T;
	cin >> T;
	while (T--) {
		for (int i = 1; i <= 34; i++) a[i] = 4;
		while (scanf("%s", str) != EOF && str[0] != '0') a[label(str)]--;
		memset(d, 0, sizeof(d));
		while (scanf("%s", str) != EOF && str[0] != '0') d[label(str)] = 1;
		// ans = 0;
		// for (int i = 1; i <= 34; i++) b[i] = a[i];
		// dfs(1, 0, 0);
		// if (ans != calc_normal() && ans != calc_chitoi()) while (1);
		ans = 0;
		update(ans, calc_normal());
		update(ans, calc_chitoi());
		update(ans, calc_kokushi());
		cout << ans << endl;
	}
}
```

---

## 作者：yzhang (赞：1)

[原题传送门](https://www.luogu.org/problem/P5301)

[更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/11306732.html)

首先先要学会麻将，然后会发现就是一个暴力dp，分三种情况考虑：

1.非七对子国士无双，设$dp_{i,j,k,a,b}$表示看到了第$i$种牌，一共有$j$个$i-1$开头的顺子，有$k$个$i$开头的顺子，有$a$个面子/杠子，有$b$个雀头时最大分数，暴力转移即可

2.七对子，设$dp_{i,j}$表示看到了第$i$种牌，一共有$j$个雀头时最大分数，暴力转移即可

3.国士无双，设$dp_{i,j}$表示看到了国士无双限定的第$i$张牌，已经选了$j$张牌时最大分数，暴力转移即可

最后比个最大就星了

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline void write(register ll x)
{
    if(!x)putchar('0');if(x<0)x=-x,putchar('-');
    static int sta[20];register int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
int T,v,cnt[35],mrk[35];
ll C[5][5]={
    {1,0,0,0,0},{1,1,0,0,0},{1,2,1,0,0},{1,3,3,1,0},{1,4,6,4,1}
};
ll bin[5]={1,2,4,8,16};
inline void upd(register ll &x,register ll y)
{
    x=x>y?x:y;
}
inline ll chose(register int x,register int y)
{
    return C[cnt[x]][y]*(mrk[x]?bin[y]:1);
}
inline ll work1()
{
    static ll dp[35][3][3][5][2];
    memset(dp,0,sizeof(dp));
    dp[0][0][0][0][0]=1;
    for(register int i=0;i<34;++i)
        for(register int j=0;j<3;++j)
            if(!j||i>7&&(i-7)%9!=0&&(i-7)%9!=1)
                for(register int k=0;k<3;++k)
                    if(!k||i>7&&(i-7)%9!=8&&(i-7)%9!=0)
                        if(cnt[i+1]>=j+k)
                            for(register int a=j+k;a<=4;++a)
                                for(register int b=0;b<=1;++b)
                                    if(dp[i][j][k][a][b])
                                    {
                                        for(register int c=0;c<=2&&j+k+c<=cnt[i+1]&&a+c<=4;++c)
                                            for(register int d=0;j+k+c+d*3<=cnt[i+1]&&a+c+d<=4;++d)
                                            {
                                                int t=j+k+c+d*3;
                                                upd(dp[i+1][k][c][a+c+d][b],dp[i][j][k][a][b]*chose(i+1,t));
                                                if(!b&&t+2<=cnt[i+1])
                                                    upd(dp[i+1][k][c][a+c+d][1],dp[i][j][k][a][b]*chose(i+1,t+2));
                                            }
                                        if(cnt[i+1]-j-k==4&&a<4)
                                            upd(dp[i+1][k][0][a+1][b],dp[i][j][k][a][b]*chose(i+1,4));
                                    }
    return dp[34][0][0][4][1];
}
inline ll work2()
{
    static ll dp[35][8];
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(register int i=0;i<34;++i)
        for(register int j=0;j<=7;++j)
        {
            upd(dp[i+1][j],dp[i][j]);
            if(j<7)
                upd(dp[i+1][j+1],dp[i][j]*chose(i+1,2));
        }
    return dp[34][7]*7;
}
int id[]={0,1,2,3,4,5,6,7,8,16,17,25,26,34};
inline ll work3()
{
    static ll dp[14][15];
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(register int i=0;i<13;++i)
        for(register int j=0;j<=14;++j)
            for(register int k=1;k<=cnt[id[i+1]]&&k<=2;++k)
                upd(dp[i+1][j+k],dp[i][j]*chose(id[i+1],k));
    return dp[13][14]*13;
}
inline int read()
{
    int v;
    char str[5];
    scanf("%s",str);
    if(str[0]=='0')
        return 0;
    if(strlen(str)==1)
    {
        if(str[0]=='E')
            v=1;
        else if(str[0]=='S')
            v=2;
        else if(str[0]=='W')
            v=3;
        else if(str[0]=='N')
            v=4;
        else if(str[0]=='Z')
            v=5;
        else if(str[0]=='B')
            v=6;
        else
            v=7;
    }
    else
    {
        if(str[1]=='m')
            v=7;
        else if(str[1]=='p')
            v=16;
        else
            v=25;
        v+=str[0]-'0';
    }
    return v;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        for(register int i=1;i<=34;++i)
            cnt[i]=4,mrk[i]=0;
        while(v=read())
            --cnt[v];
        while(v=read())
            mrk[v]=1;
        write(max(work1(),max(work2(),work3()))),puts("");
    }
	return 0;
}
```

---

## 作者：genshy (赞：0)

动态规划（传说中的麻将类dp）。

简化题意：给你一些已经使用过的牌，让你从没使用过的牌中选出一组能够胡牌的组合，问这个组合的最大达成分数为多少。

首先考虑一个问题就是杠子是没有刻子要优的。因为 ${4\choose 1} < {4\choose 3}$， 也就是说当你选了杠子的时候，舍弃一张牌让其变成刻子是要更优的。

然后我们的胡牌方式就变成了三种：七对子，国土无双，$3\times 4+2$ 。

分三种情况讨论一下：

**第一种情况：七对子胡牌**

这种情况很好处理，只需要开个堆，维护每种牌组成雀头的最大价值。取堆中前 $7$ 大的即可。

**第二种情况：国土无双胡牌**

枚举那一种牌出现了两次，算一下每种情况的答案，最后在取个 $\min$ 即可。

复杂度：$O(13^2)$ 。

**第三种情况：$3\times 4+2$**

这种情况就比较难处理了，考虑用 $dp$ 来解决这个问题。

设 $f(i,j,k,u,v,w) (k\in \{0,1\})$ 表示前 $i$ 种牌，组成 $j$ 对面子，$k$ 对雀头，其中第 $i,i+1,i+2$ 分别选了 $u,v,w$ 张的最大价值。

分 刻子/顺子/雀头/直接转移四种情况考虑。

- 直接转移：

  $ f(i+1,j,k,0,v,w) = f(i,j,k,u,v,w)$ 

- 雀头：

  $ f(i,j,k+1,u+2,v,w) = f(i,j,k,u,v,w)\times  {{num[i]\choose u+2}\over {num[i]\choose u}}\times (good[i])^2$

  中间拿两个组合数相除的意思为先把 $i$ 在 $f(i,j,k,u,v,w)$ 中的贡献 $num[i]\choose u$ 除去，在算上其在 $f(i,j,k,u+2,v,w)$ 的贡献 $num[i]\choose u+2$ 。$(good[i])^2$ 则算的是新加入的两张 $i$ 类型的牌的宝牌分数。

- 刻子：

  $ f(i,j+1,k,u+3,v,w) = f(i,j,k,u,v,w)\times {{num[i]\choose u+3}\over {num[i]\choose u}}\times (good[i])^3$

  这个其实和上面雀头的转移是类似的。

- 顺子：
	$ f(i,j+1,k,u+1,v+1,w+1) = f(i,j,k,u,v,w)\times {{num[i]\choose u+1}\over {num[i]\choose u}}\times {{num[i+1]\choose v+1}\over {num[i+1]\choose v}}\times {{num[i+2]\choose w+1}\over {num[i+2]\choose w}} \times good[i]\times good[i+1]\times good[i+2]$

  和上面的刻子的转移时类似的，就是考虑先把 $i,i+1,i+2$ 在 $f(i,j,k,u,v,w)$ 乘上的组合数除去，在乘上其在 $f(i,j+1,k,u+1,v+1,w+1)$ 的组合数，同时在算上选 $i,i+1,i+2$ 的宝牌分数即可

然后这样我们就可以直接暴力 $dp$ 了，复杂度：$O(T\times 34\times 2\times 4^4)$ 。

这样只能得到 $60pts$ 的分数。

考虑优化一下，其实当 $f(i,j,k,u,v,w) = 0$ 的时候，我们是没必要用它来进行转移的.

用这个优化就可以省去不少无用状态,然后这道题就可以过了。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define int long long
int T,ans,c[50][50],num[50],good[50],f[36][5][2][5][5][5];
int a[50] = {0,1,9,10,18,19,27,28,29,30,31,32,33,34};
bool can[50] = {0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
char s[5];
void YYCH()
{
	c[0][0] = 1;
	for(int i = 1; i <= 4; i++)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j++)
		{
			c[i][j] = c[i-1][j] + c[i-1][j-1];
		}
	}
}
int bianhao(char s[3])
{
    if(s[1] >= '0' && s[1] <= '9')
    {
        if(s[2] == 'm') return s[1] - '0';
        if(s[2] == 'p') return 9 + s[1] - '0';
        if(s[2] == 's') return 18 + s[1] - '0';
    }   
    if(s[1] == 'E') return 28;
    if(s[1] == 'S') return 29;
    if(s[1] == 'W') return 30;
    if(s[1] == 'N') return 31;
    if(s[1] == 'Z') return 32; 
    if(s[1] == 'B') return 33;
    if(s[1] == 'F') return 34;
}
int C(int x,int y){return c[x][y];}
int Qiduizi()
{
    priority_queue<int> q;
    for(int i = 1; i <= 34; i++)
    {
        if(num[i] >= 2) q.push(C(num[i],2)*good[i]*good[i]);
    }
    if(q.size() < 7) return 0;
    int res = 1, cnt = 0;
    while(cnt < 7) cnt++, res *= q.top(), q.pop();
    return res*7;
}
int Guotuwushuang()
{
    for(int i = 1; i <= 13; i++) if(!num[a[i]]) return 0;
    int ans = 0;
    for(int i = 1; i <= 13; i++)
    {
        int res = 13 * C(num[a[i]],2) * good[a[i]] * good[a[i]];
        for(int j = 1; j <= 13; j++) if(j != i) res = res * C(num[a[j]],1) * good[a[j]];
        ans = max(ans,res);
    }
    return ans;
}
int dp()
{
    memset(f,0,sizeof(f));//前i张牌，j对面子，k对雀头，第i,i+1,i+2 的牌的数量的最大价值。
    f[1][0][0][0][0][0] = 1;
    for(int i = 1; i <= 34; i++)
    {
        for(int j = 0; j <= 4; j++)
        {
            for(int k = 0; k <= 1; k++)
            {
                for(int u = 0; u <= 4; u++)
                {
                    for(int v = 0; v <= 4; v++)
                    {
                        for(int w = 0; w <= 4; w++)
                        {
                        	if(!f[i][j][k][u][v][w]) continue;
                            if(k == 0 && u+2 <= num[i]) f[i][j][1][u+2][v][w] = max(f[i][j][1][u+2][v][w],f[i][j][k][u][v][w]/C(num[i],u)*C(num[i],u+2)*good[i]*good[i]);
                            if(j+1 <= 4 && u+3 <= num[i]) f[i][j+1][k][u+3][v][w] = max(f[i][j+1][k][u+3][v][w],f[i][j][k][u][v][w]/C(num[i],u)*C(num[i],u+3)*good[i]*good[i]*good[i]);
                            if(j+1 <= 4 && can[i] && u+1 <= num[i] && v+1 <= num[i+1] && w+1 <= num[i+2]) f[i][j+1][k][u+1][v+1][w+1] = max(f[i][j+1][k][u+1][v+1][w+1],f[i][j][k][u][v][w]/C(num[i],u)*C(num[i],u+1)/C(num[i+1],v)*C(num[i+1],v+1)/C(num[i+2],w)*C(num[i+2],w+1)*good[i]*good[i+1]*good[i+2]); 
                            if(i <= 34) f[i+1][j][k][v][w][0] = max(f[i+1][j][k][v][w][0],f[i][j][k][u][v][w]);
                        }
                    }
                }
            }
        }
	}
    int ans = 0;
    for(int i = 1; i <= 34; i++)
    {
    	for(int j = 0; j <= 4; j++)
    	{
        	for(int k = 0; k <= 4; k++)
        	{
            	for(int u = 0; u <= 4; u++)
            	{
                	ans = max(ans,f[i][4][0][j][k][u]);
                	ans = max(ans,f[i][4][1][j][k][u]);
            	}
        	}
    	}
    }
    return ans;
}
signed main()
{
    scanf("%d",&T); YYCH();
    while(T--)
    {
        ans = 0;
        for(int i = 1; i <= 34; i++) num[i] = 4, good[i] = 1;
        while(scanf("%s",s+1) != EOF && s[1] != '0') num[bianhao(s)]--;
        while(scanf("%s",s+1) != EOF && s[1] != '0') good[bianhao(s)] = 2;
        ans = max(ans,Guotuwushuang());
        ans = max(ans,Qiduizi());
        ans = max(ans,dp());
        printf("%lld\n",ans);
    } 
    return 0;
}
```


---

## 作者：Rainybunny (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.com.cn/problem/P5301).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~有没有顺其自然地想到斗地主然后肝暴搜的qwq.~~  
## 题意理解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这道题其实是一个高维的$DP$, 不过包装得十分晦涩难懂. 接下来我们一起梳理一下题意:  

- 输入的是"打出的牌", 所以 **场上的牌是4-"打出的牌"**. 相当于作为旁观者的雪野小朋友只看到桌子中央的牌, 其余牌可能在你手中.  

- 对于"胡牌"的分值计算, 是**场上的牌组成你手牌的方案数**. ( 其实也比较贴近生活, 方案数越多, 胡牌概率自然越大, 那么手牌就更优秀. ) 此外, 再乘上$2^\text{宝牌张数}$.  

- 胡牌从本质上分为三种. 分别是「国士无双」, 「七对子」, 和「$3\times4+2$」. 前两种情况只有在$14$张手牌时合法, 第三种情况是因为单看任意一个「杠子」都是比「刻子」少至少一半 ( ${4\choose3}=4{4\choose4}$ ), 自然就不会出现在最优解中.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以, 在求答案时分别求出「国士无双」, 「七对子」, 和「$3\times4+2$」的最优解, 取$\max$即可. 前两种比较显然 ( 否则就直接看代码去吧$qwq$. ), 我们着重讲一讲「$3\times4+2$」的$DP$求解过程.
## 「$3\times4+2$」
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;令状态$f(i,j,0/1,k,a,b)$, 表示 **决定了前$i$张牌, 有$j$个「面子」, 是否有「雀头」, 第$i$, $i+1$, $i+2$张牌分别取了$k$, $a$, $b$张牌的最大价值**, 同时令$Cnt_i$表示场子里$i$的数量, $Dora(x,y)$表示第$x$张牌取$y$张的价值, 按三种牌型进行转移 ( 这里采用刷表法 ):  

1. 雀头转移:
$$
f(i,j,1,k+2,a,b)=\frac{f(i,j,0,k,a,b)\times{Cnt_i\choose k+2}\times Dora(i,2)}{Cnt_i\choose k}
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;即除掉第$i$张牌提供的方案数重新计算, 在补上多选的两张牌的价值. $n\choose m$表示从$n$个物品里选$m$个的方案, 即$C_n^m$.  

2. 刻子转移:
$$
f(i,j+1,0/1,k+3,a,b)=\frac{f(i,j,0/1,k,a,b)\times{Cnt_i\choose k+3}\times Dora(i,3)}{Cnt_i\choose k}
$$

3. 顺子转移:
$$
f(i,j+1,0/1,k+1,a+1,b+1)=\frac{f(i,j,0/1,k,a,b)\times({\dots\choose\dots}Dora())\times\dots}{{\dots\choose\dots}{\dots\choose\dots}{\dots\choose\dots}}
$$

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~读者自证不难.~~

## 代码
```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <assert.h>

#define Int register int
#define C( n, m ) ( assert ( n >= m ), C[n][m] )
#define F( i, j, k, a, b, c ) F[i][j][k][a][b][c]

using namespace std;

typedef long long int LL;

const int P = 34, G[15] = { 0, 1, 9, 10, 18, 19, 27, 28, 29, 30, 31, 32, 33, 34 };
const bool BEG[36] = { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 };
int C[6][6];
int Cnt[36]; // 1~9: wan. 10~18: tong. 19~27: tiao. 28~34: E, S, W, N, Z, B, F. 
bool Val[36];

inline LL Max ( const LL a, const LL b ) { return a > b ? a : b; }

inline void Chkmax ( LL& a, const LL b ) { a = Max ( a, b ); }

inline void InitC () {
	C[0][0] = 1;
	for ( Int i = 1; i <= 4; ++ i ) {
		for ( Int j = 0; j <= i; ++ j ) {
			C[i][j] = j ? C[i - 1][j] + C[i - 1][j - 1] : 1;
		}
	}
}

inline int GetCard () {
	static char s[10];
	scanf ( "%s", s );
	if ( strlen ( s ) == 1 ) {
		if ( s[0] == '0' ) return 0;
		switch ( s[0] ) {
			case 'E': return 28;
			case 'S': return 29;
			case 'W': return 30;
			case 'N': return 31;
			case 'Z': return 32;
			case 'B': return 33;
			default: return 34;
		}
	} else {
		int p = s[0] - '0', q = s[1] == 'm' ? 0 : 1 + ( s[1] == 'p' );
		return q * 9 + p;
	}
}

inline void Input () {
	for ( int v; ( v = GetCard () ); -- Cnt[v] );
	for ( int v; ( v = GetCard () ); Val[v] = true );
}

inline LL Dora ( const int Indx, const int Num ) { return Val[Indx] ? 1LL << Num : 1; }

inline LL SevenPairs () {
	static priority_queue<LL> Q; for ( ; ! Q.empty (); Q.pop () );
	for ( Int i = 1; i <= P; ++ i ) {
		if ( Cnt[i] >= 2 ) {
			Q.push ( C ( Cnt[i], 2 ) * Dora ( i, 2 ) );
		}
	}
	if ( Q.size () < 7 ) return 0;
	LL ret = 7;
	for ( Int i = 1; i <= 7; ++ i ) ret *= Q.top (), Q.pop ();
	return ret;
}

inline LL GSWS () {
	LL ret = 0;
	bool ext = false;
	for ( Int i = 1; i <= 13; ++ i ) {
		ext |= Cnt[G[i]] > 1;
		if ( ! Cnt[G[i]] ) return 0;
	}
	if ( ! ext ) return 0;
	for ( Int i = 1; i <= 13; ++ i ) {
		LL now = 1;
		if ( Cnt[G[i]] > 1 ) {
			now *= C ( Cnt[G[i]], 2 ) * Dora ( G[i], 2 );
			for ( Int j = 1; j <= 13; ++ j ) if ( i ^ j ) now *= C ( Cnt[G[j]], 1 ) * Dora ( G[j], 1 );
		}
		Chkmax ( ret, now );
	}
	return ret * 13;
}

inline LL Normal () {
	static LL F[36][5][5][5][5][5]; memset ( F, 0, sizeof F );
	LL ret = 0;
	F ( 1, 0, 0, 0, 0, 0 ) = 1;
	for ( Int i = 1; i <= P; ++ i ) {
		for ( Int j = 0; j <= 4; ++ j ) {
			for ( Int k = 0; k <= 4; ++ k ) {
				for ( Int a = 0; a <= 2; ++ a ) {
					for ( Int b = 0; b <= 2; ++ b ) {
						LL &now0 = F ( i, j, 0, k, a, b ), &now1 = F ( i, j, 1, k, a, b );
						if ( ! now0 && ! now1 ) continue;
						if ( Cnt[i] - k >= 2 ) Chkmax ( F ( i, j, 1, k + 2, a, b ), now0 / C ( Cnt[i], k ) * C ( Cnt[i], k + 2 ) * Dora ( i, 2 ) );
						if ( j < 4 ) {
							if ( Cnt[i] - k >= 3 ) {
								Chkmax ( F ( i, j + 1, 0, k + 3, a, b ), now0 / C ( Cnt[i], k ) * C ( Cnt[i], k + 3 ) * Dora ( i, 3 ) );
								Chkmax ( F ( i, j + 1, 1, k + 3, a, b ), now1 / C ( Cnt[i], k ) * C ( Cnt[i], k + 3 ) * Dora ( i, 3 ) );
							}
							if ( BEG[i] && Cnt[i] - k > 0 && Cnt[i + 1] - a > 0 && Cnt[i + 2] - b > 0 && a ^ 2 && b ^ 2 ) {
								Chkmax ( F ( i, j + 1, 0, k + 1, a + 1, b + 1 ), now0
										/ C ( Cnt[i], k ) * C ( Cnt[i], k + 1 ) * Dora ( i, 1 )
										/ C ( Cnt[i + 1], a ) * C ( Cnt[i + 1], a + 1 ) * Dora ( i + 1, 1 )
										/ C ( Cnt[i + 2], b ) * C ( Cnt[i + 2], b + 1 ) * Dora ( i + 2, 1 ) );
								Chkmax ( F ( i, j + 1, 1, k + 1, a + 1, b + 1 ), now1
										/ C ( Cnt[i], k ) * C ( Cnt[i], k + 1 ) * Dora ( i, 1 )
										/ C ( Cnt[i + 1], a ) * C ( Cnt[i + 1], a + 1 ) * Dora ( i + 1, 1 )
										/ C ( Cnt[i + 2], b ) * C ( Cnt[i + 2], b + 1 ) * Dora ( i + 2, 1 ) );
							}
						}
						Chkmax ( F ( i + 1, j, 0, a, b, 0 ), now0 );
						Chkmax ( F ( i + 1, j, 1, a, b, 0 ), now1 );
						if ( j == 4 ) Chkmax ( ret, now1 );
					}
				}
			}
		}
	}
	return ret;
}

inline void Work () {
	InitC ();
	int T; scanf ( "%d", &T );
	for ( ; T --; ) {
		for ( Int i = 1; i <= P; ++ i ) Cnt[i] = 4, Val[i] = false;
		Input ();
		LL Ans1 = SevenPairs ();
		LL Ans2 = GSWS ();
		LL Ans3 = Normal ();
//		printf ( "%lld %lld %lld\n", Ans1, Ans2, Ans3 );
		printf ( "%lld\n", Max ( Ans1, Max ( Ans2, Ans3 ) ) );
	}
}

int main () {
//	freopen ( "doraippai.in", "r", stdin );
//	freopen ( "doraippai.out", "w", stdout );
	Work ();
	return 0;
}
```

---

## 作者：Jμdge (赞：0)

这道题除了非常恶心以外也没有什么非常让人恶心的地方

当然一定要说有的话还是有的，就是这题和咱 ZJOI 的 mahjong 真的是好像的说~

~~于是就想说这道题出题人应该被 锕 掉~~

# noteskey


整体的思路就是特判国士无双和七对子，然后 dp 搞普通的胡牌

dp 状态设计和楼上大佬说的一样，就是用一个五维的 $f[i][j][k][l][p]$ 表示当前处理了前 i 种类型的牌，存在 j 个 面子/杠子 ，以 i-1 开头的顺子要选 k 个，以 i 开头的面子要选 l 个，以及当前是否有 雀头 (用 p 表示)

然后转移就非常的暴力了，反正这里的数据范围也比较小，枚举下状态转移就好了


总的来说就是道 语文 + 码农 + dp 题，虽说没什么思维难度但我不见得能想出来

# watch out

这题的字符串读入还是比较毒瘤的...要稍微注意一下不然可能会出事

# code

这压行是同样的味道呢~

```cpp
//by Judge
#include<bits/stdc++.h>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define ll long long
using namespace std;
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline bool cmax(ll& a,ll b){return a<b?a=b,1:0;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} inline void reads(string& s){ char c=getchar();
	for(;!isalpha(c)&&!isdigit(c);c=getchar()); s="";
	for(;isalpha(c)||isdigit(c);c=getchar()) s+=c;
} char sr[1<<21],z[20];int CCF=-1,Z;
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(ll x,char chr='\n'){
	if(CCF>1<<20)Ot();if(x<0)sr[++CCF]=45,x=-x;
	while(z[++Z]=x%10+48,x/=10);
	while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
} int t,cnt,a[41],b[41],C[5][5]; ll f[41][5][3][3][2],tp[41];
int gs[14]={0,1,9,10,18,19,27,28,29,30,31,32,33,34}; string c;
inline int id(){ if(c[0]=='B') return 34;
	if(c[0]=='E') return 28; if(c[0]=='S') return 29; if(c[0]=='W') return 30;
	if(c[0]=='N') return 31; if(c[0]=='Z') return 32; if(c[0]=='F') return 33;
	if(c[1]=='m') return c[0]-48; if(c[1]=='p') return c[0]-39; return c[0]-30;
}
int main(){ C[0][0]=1;
	fp(i,1,4){ C[i][0]=1;
		fp(j,1,i) C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	fp(T,1,read()){
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		memset(f,0,sizeof f);
		while(1){ reads(c);
			if(c[0]=='0') break;
			else ++a[id()];
		}
		while(1){ reads(c);
			if(c[0]=='0') break;
			else b[id()]=1;
		}
		fp(i,1,34) a[i]=4-a[i];
		ll ans=0;
		fp(i,1,13){ ll tmp=1; //枚举出现两次的牌 
			fp(j,1,13) //枚举 13 种牌 
				if(i==j)
					if(a[gs[j]]<2) tmp=0; //如果数量不够就让 tmp=0 
					else tmp*=C[a[gs[j]]][2]*(b[gs[j]]?4:1); //否则加贡献 
				else
					if(a[gs[j]]<1) tmp=0;
					else tmp*=C[a[gs[j]]][1]*(b[gs[j]]?2:1);
			cmax(ans,tmp*13);
		}
		cnt=0;
		fp(i,1,34) if(a[i]>=2) tp[++cnt]=C[a[i]][2]*(b[i]?4:1);
		if(cnt>=7){ //如果牌数大于等于 2 的不止 7 张就可以构成七对子 
			sort(tp+1,tp+1+cnt); ll tmp=1; //选出权最大的 7 种牌 
			fp(i,cnt-6,cnt) tmp*=tp[i]; //累乘贡献 
			cmax(ans,tmp*7);
		}
		f[0][0][0][0][0]=1; //初始化边界 
		fp(i,0,33) fp(j,0,4) for(Rg int k=0;k<3&&j+k<=4;++k){
			if(k>=1&&(i==9||i==18||i>=27)) break; //不合法开头无法构成顺子 
			for(Rg int l=0;l<3&&j+k+l<=4;++l){
				if(l>=1&&(i==9||i==18||i==27)) break;
				if(f[i][j][k][l][0]||f[i][j][k][l][1]) fp(u,k+l,a[i+1]){
					ll tmp=C[a[i+1]][u]*(b[i+1]?(1<<u):1); //计算贡献 
					// 四种转移 
					if(j+u<=4&&u-k-l<3) 
						cmax(f[i+1][j+k][l][u-k-l][0],f[i][j][k][l][0]*tmp),
						cmax(f[i+1][j+k][l][u-k-l][1],f[i][j][k][l][1]*tmp);
					if(u-k-l-2>=0&&j+u-2<=4)
						cmax(f[i+1][j+k][l][u-k-l-2][1],f[i][j][k][l][0]*tmp);
					if(u-k-l-3>=0&&j+u-2<=4)
						cmax(f[i+1][j+k+1][l][u-k-l-3][0],f[i][j][k][l][0]*tmp),
						cmax(f[i+1][j+k+1][l][u-k-l-3][1],f[i][j][k][l][1]*tmp);
					if(u==4&&!k&&!l&&j<=3)
						cmax(f[i+1][j+1][0][0][0],f[i][j][k][l][0]*tmp),
						cmax(f[i+1][j+1][0][0][1],f[i][j][k][l][1]*tmp);
				}
			}
		}
		cmax(ans,f[34][4][0][0][1]),print(ans);
	} return Ot(),0;
}
```


---

