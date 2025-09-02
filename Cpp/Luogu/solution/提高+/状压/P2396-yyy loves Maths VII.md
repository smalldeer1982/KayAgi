# yyy loves Maths VII

## 题目背景

yyy 对某些数字有着情有独钟的喜爱，他叫他们为“幸运数字”；然而他作死太多，所以把自己讨厌的数字称为“厄运数字”。

## 题目描述

一群同学在和 yyy 玩一个游戏。

每次,他们会给 yyy $n$ 张卡片，卡片上有数字，所有的数字都是“幸运数字”，我们认为第 $i$ 张卡片上数字是 $a_{i}$。

每次 yyy 可以选择向前走 $a_{i}$ 步并且丢掉第 $i$ 张卡片。当他手上没有卡片的时候他就赢了。

但是呢，大家对“厄运数字”的位置布置下了陷阱，如果 yyy 停在这个格子上，那么他就输了。注意：**即使到了终点，但是这个位置是厄运数字，那么也输了。**

现在，有些同学开始问：yyy 有多大的概率会赢呢？

大家觉得这是个好问题，有人立即让 yyy 写个程序：“电脑运行速度很快！$24$ 的阶乘也不过就 $620\,448\,401\,733\,239\,439\,360\,000$，yyy 你快写个程序来算一算。”

yyy 表示很无语，他表示他不想算概率，最多算算赢的方案数，而且是对 $10^9+7$ 取模后的值。

大家都不会写程序，只好妥协。

但是这时候 yyy 为难了，$24!$ 太大了，要跑好长时间。

他时间严重不够！需要你的帮助！

某个数字可能既属于幸运数字又属于厄运数字。

## 说明/提示

- $10\%$ 的数据 $n \leq 10$；
- $50\%$ 的数据 $n \leq 23$；
- $100\%$ 的数据 $n \leq 24$，$0\le m\le 2$，$1\le a_i,b_i\le 10^9$。

## 样例 #1

### 输入

```
8
1 3 1 5 2 2 2 3
0```

### 输出

```
40320```

## 样例 #2

### 输入

```
24
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
2
10 15
```

### 输出

```
0```

# 题解

## 作者：Siyuan (赞：31)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Luogu 2396](https://www.luogu.org/problemnew/show/P2396)

yyy 有 $n$ 张卡片，每张卡片上都有一个数字 $a_i$，每次 yyy 可以选择向前走 $a_i$ 步并丢弃第 $i$ 张卡片。当他手上没有卡片的时候他就赢了；但是有 $m$ 个“厄运数字”，在“厄运数字”的位置有陷阱，只要 yyy 停在这个格子上他就输了（即使终点是陷阱，那么也输了）。你需要算出 yyy 能赢的方案数，答案对 $1000000007$ 取模。

数据范围：$1\le n\le 24$，$0\le m\le 2$

------

## Solution

我们首先可以确定这是一道 $\texttt{DP}$ 题目。由于并没有给出 $a_i$ 的具体范围，因此无法把距离设计进状态；又发现每张牌只能用一次并且没有顺序限制，观察到 $n$ 的范围也很小，我们可以考虑状压 $\texttt{DP}$。

我们定义 $f[i]$ 表示使用了集合 $i$ 内的卡片有多少种赢的方案。转移时，我们记 $dis[i]$ 表示使用了集合 $i$ 内的卡片到达的位置，显然当 $dis[i]$ 为“厄运数字”时不能转移。否则我们枚举这次使用的卡片 $j$（$j\in i$），那么有转移方程：$f[i]=\sum_{j=1}^n[j\in i]\cdot f[i\ \texttt{XOR}\ j]$（其中 $i\ \texttt{XOR}\ j$ 本质是从集合 $i$ 中删去元素 $j$）。

**时间复杂度**：$O(2^n\log n)$

------

## Code

```cpp
#include <cstdio>

const int N=24;
const int mod=1e9+7;
int n,m,b1,b2,dis[1<<N],f[1<<N];

void upd(int &x,int y) {(x+=y)>=mod&&(x-=mod);}
void solve(int x) {
    for(int i=x,j;i;i^=j) j=i&-i,upd(f[x],f[x^j]);
}
int main() {
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d",&dis[1<<i]);
    scanf("%d",&m);
    if(m>0) scanf("%d",&b1);
    if(m>1) scanf("%d",&b2);
    f[0]=1;
    int msk=(1<<n)-1;
    for(int i=1;i<=msk;++i) {
        int j=i&-i;
        dis[i]=dis[i^j]+dis[j];
        if(dis[i]==b1||dis[i]==b2) continue;
        solve(i);
    }
    printf("%d\n",f[msk]);
    return 0;
}
```



---

## 作者：RabbitHu (赞：20)

# 洛谷P2396 | 状压DP卡常题


洛谷题解里面唯一的一篇题解……我太弱了，没看懂……


在一个已经404的页面（的百度快照里）找到了一种看起来靠谱的解法（卡常法？）


正常DP的瓶颈在于对于每个状态$i$都要枚举$n$个位，实际上我们需要的只是在$i$中为"1"的那些位，而"1"的位置通过lowbit可以得到，从$i$中去掉这个"1"，再取lowbit，就能得到剩余的"1"。


代码亲测……开O2能过。


    
    
```cpp
    #include <cstdio>
    #include <cmath>
    #include <cstring>
    #include <algorithm>
    #include <ctime>
    #include <cstdlib>
    using namespace std;
    typedef long long ll;
    #define enter putchar('\n')
    #define space putchar(' ')
    template <class T>
    void read(T &x){
        char c;
        bool op = 0;
        while(c = getchar(), c > '9' || c < '0')
        if(c == '-') op = 1;
        x = c - '0';
        while(c = getchar(), c >= '0' && c <= '9')
        x = x * 10 + c - '0';
        if(op) x = -x;
    }
    template <class T>
    void write(T x){
        if(x < 0) putchar('-'), x = -x;
        if(x >= 10) write(x / 10);
        putchar('0' + x % 10);
    }
    const int N = 24, P = 1e9 + 7;
    int n, m, b[2], f[1 << N], dis[1 << N];
    // b: 厄运数字；f: dp数组；dis：某状态时yyy已走过的距离
    int main(){
        read(n);
        for(int i = 0; i < n; i++)
            read(dis[1 << i]);
        read(m);
        if(m > 0) read(b[0]);
        if(m > 1) read(b[1]);
        f[0] = 1;
        for(int i = 1; i < (1 << n); i++){
            int j = i & -i, k = i;
            // k是一个辅助变量，用来不停地lowbit以找出i中的所有"1"
            dis[i] = dis[i ^ j] + dis[j]; //用i去掉一个"1"得到的状态可求dis[i]
            if(dis[i] == b[0] || dis[i] == b[1]) continue; //如果是厄运数字
            while(k){ 
                j = k & -k; //j是当前找到的lowbit
                f[i] += f[i ^ j];
                if(f[i] >= P) f[i] -= P; //卡常嘛
                k ^= j; //k中去掉这个"1"，这样下次lowbit会找到另一个"1"
            }
        }
        write(f[(1 << n) - 1]), enter;
        return 0;
    }

```

---

## 作者：Alex_Wei (赞：17)

> [P2396 yyy loves Maths VII](https://www.luogu.com.cn/problem/P2396)

[双倍经验](https://www.luogu.com.cn/problem/CF327E)。

设 $f_S$ 表示集合 $S$ 的答案，若 $g_S = \sum_{i\in S} a_i$ 不合法，则 $f_S = 0$，否则 $f_S = \sum_{i\in S} f_{S\backslash i}$。

直接做的时间复杂度为 $\mathcal{O}(2 ^ n n)$，开 O2 可以通过。我们枚举 $i$ 的时候通过 $\mathrm{lowbit}(S)$ 做到不枚举无用转移，有 $\frac 1 2$ 的常数。

优化：

- 若 $k = 0$，则答案为 $n!$。
- 若 $k = 1$，则答案为 $n! - \sum_{g(S) = x} |S|! (n - |S|)!$。

- 当 $g_S < \min(x, y)$ 时，$f_S = |S|!$。可以将 $x, y$ 同时变成 $\sum a_i - x, \sum a_i - y$ 使 $\min(x, y)$ 变大。
- 当使得 $g(S) = x$ 和 $g(T) = \sum a_i - y$ 的 $S$ 和 $T$ 的数量之积不大时，可以枚举 $S, T$ 算出同时经过 $x, y$ 的路径数，再套入 $k = 1$ 的容斥。

[代码](https://codeforces.com/contest/327/submission/176821874)，不开 O2 获得了最优解（749ms），开 O2 又获得了最优解（476ms）。

**怎么没有人写 $\boldsymbol {3 ^ {n / 2}}$ 的做法啊？**

设 $A(S)$ 表示集合 $S$ 的 $a_i$ 之和。

考虑 $k = 1$，我们发现相当于求 $n! - \sum\limits_{A(S) = x} |S|! (n - |S|)!$。子集和等于某个值，考虑 MITM，将 $a$ 分成两部分 $L, R$，求出 $f_{i, j}$ 表示 $R$ 的子集 $R_1$ 的数量，使得 $|R_1| = i$ 且 $A(R_1) = j$。枚举 $L$ 子集 $L_1$ 和 $i = |R_1|$，则答案减去 $f_{i, x - A(L_1)} (i + |L_1|)!(n - i - |L_1|)!$。

$k = 2$ 同理，运用容斥原理将答案转化为 $n!$ 减去经过 $x$ 的方案数，减去经过 $y$ 的方案数，再加上同时经过 $x$ 和 $y$ 的方案数。对于后者 $\sum\limits_{A(S_1) = x} \sum\limits_{A(S_2) = y - x\land S_1 \cap S_2 = \varnothing} |S_1|! |S_2|! (n - |S_1| - |S_2|)!$。类似地，枚举 $R$ 的子集 $R_1$ 和 $R\backslash R_1$ 的子集 $R_2$，求出 $f_{i, j, l, m}$ 表示 $|R_1| = i$，$|R_2| = j$，$A(R_1) = l$ 且 $A(R_2) = m$ 的方案数。枚举 $L$ 子集 $L_1$ 和 $L\backslash L_1$ 的子集 $L_2$，则答案加上 $f_{i, j, x - A(L_1), y - x - A(L_2)} (|L_1| + i)! (|L_2| + j)! (n - i - j - |L_1| - |L_2|)!$。

使用哈希表维护 $k = 1$ 的 $j$ 一维和 $k = 2$ 的 $l, m$ 两维，时间复杂度 $\mathcal{O}(3 ^ {n / 2} n ^ 2)$。[代码](https://codeforces.com/contest/327/submission/176961722)。不开 O2 会 TLE，开 O2 获得了最优解（383ms）。注意 CF 双倍经验 `unodered_map` 会 TLE，用 `gp_hash_table`。

---

## 作者：lyx613 (赞：14)

@qleonardo

没天理的暴力踩大常数正解~~~

不优化的状压动归空间是O(2^n)，时间是O(2^n\*n)，加上递归的大常数，妥妥爆炸TLE30

此题开创了连状压动归都要剪枝优化的新时代QAQ：

优化1：对于位置没有到第一个厄运数字的状态，方案数等于选的数的个数的阶乘

优化2：对所有的幸运数字从小到大排序

优化3：如果两个厄运数字都很小，把（sum幸运数字-厄运数字1）作为-厄运数字1；把（sum幸运数字-厄运数字2）作为-厄运数字2

优化4：人工栈大法好

优化5：c++可以手动开O2 /\*说笑\*/

练习常数优化的好题~~~~~


---

## 作者：花里心爱 (赞：10)

一道神仙~~卡常~~题

首先，看到$n \leq 24$的数据范围，我们想到了状压dp。

状态设为一个2进制数表示每张卡片是否用过，设$f[i]$表示状态$i$时的方案数，$d[i]$表示状态为$i$的距离。

然后dp，对于每一个$i$，找到其中的每一个$1$（设为$k$），则$f[i] += f[i-k]$。初始化$f[0]=1$。注意当$d[i]$为"厄运数字"的时候要设为0。

最后答案即为$f[(1<<n)-1]$。

然后我们就会发现这样过不掉qwq

考虑优化，首先枚举$i$其中的$1$的时候可以记录一个$j$初始值为$i$，每次$k=lowbit(j),j-=k$，这样$k$就为取出的$1$。

然后算出$d[i]$后如果是"厄运数字"可以直接跳掉。

然而样例2还是过不掉……

~~于是大力卡常~~，循环变量加`register`，一些运算用位运算代替，模运算用减代替。（就这样卡到了1s内）

代码如下 :
```
#include <cstdio>
#include <cctype>
#define M 1000000007
#define lowbit(x) ((x)&(-x))
inline int read() {
    int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
    while(isdigit(ch)){d=d*10+ch-48;ch=getchar();}return d;
}

int n, m, mx;
int dis[1<<24], a[2];
int f[1<<24];

int main() {
    n = read();
    for(register int i = 0; i < n; ++i)
        dis[1<<i] = read();
    m = read();
    for(register int i = 0; i < m; ++i)
        a[i] = read();
    f[0] = 1, mx = (1<<n)-1;
    for(register int i = 1; i <= mx; ++i) {
        dis[i] = dis[i^lowbit(i)] + dis[lowbit(i)];
        if(dis[i] == a[0] || dis[i] == a[1]) continue;
        for(register int j = i, k = lowbit(j); j; j ^= k, k = lowbit(j)) {
            f[i] += f[i^k];
            if(f[i] > M) f[i] -= M;
        }
    }
    printf("%d", f[mx]);
    return 0;
}
```

---

## 作者：quarmer (赞：5)

[题目](https://www.luogu.com.cn/problem/P2396)

比较板子的状压 dp。

读完题容易设出状态 $f_{i}$ 表示此时已选卡片的状态，$i$ 的二进制位 $0/1$ 分别对应这一张卡片不选或选。

因为已选卡片数字总和不得等于给定数，我们新开一个数组记录每个选择卡片的状态的卡片总和。

对于每一个 $i$，找到 $i$ 中所有二进制位为 $1$ 的位，设此位为第 $j$ 位，则易得 $f_{i}=f_{i} + f_{i \otimes 2^j}$。其中 $\otimes$ 表示异或运算。

但是怎么说这也是一道紫，不可能这么简单，果然，交上去 TLE（60pts）。


在上述 dp 过程中，如果对于每一个状态都要枚举一下每一位是否为 $1$，常数过大，会 T 掉。

**为了突破此瓶颈，用到 lowbit 运算，快速找到此二进制数的每一个 $1$。**

交上去改进后的代码，依然 TLE（60pts），~~此时只要开启 O2，即可 AC。~~

要知道，很多比赛是没有 O2 的，所以我们要卡进 1s 之内。

开始乱搞，循环变量在外面定义，并加上 regiter，还有取模不要用取模，用减法，加上这些就够了，不开 O2 可 AC。

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <ctime>
//#define int long long
//#define int __int128
//#define int long long
//#define int long double
//#define Int int
#define mr make_pair
#define ff first
#define ss second
#define lb(x) (x & (-x))
using namespace std ;
int a[26] ;
int b[3] ;
int f[1 << 24 | 1] ;  
int sum[1 << 24 | 1] ;
const int mod = 1e9 + 7 ;
int n, m ; 
bool check(int x) {
	return (x != b[1] && x != b[2]) ;
}
int read(){
	char ch ;int s = 0 ;int w = 1;
	while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
	while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
	return s * w ;
}
signed main() {
    cin >> n ;
    register int i ;
    for(i = 1 ; i <= n ; i++) a[i] = read() ;
    cin >> m ;
    memset(b, -1, sizeof(b)) ;
    for(i = 1 ; i <= m ; i++) b[i] = read() ;
    f[0] = 1 ;
    for(i = 0 ; i < n ; i++) sum[1 << i] = a[i + 1] ;
    int maxn = 1 << n ;
    for(i = 1 ; i < maxn ; i++) sum[i] = sum[lb(i)] + sum[i - lb(i)] ;
    for(i = 0 ; i < maxn ; i++) {
    	if(!check(sum[i])) continue ;
		int k = i ;
    	while(k) { 
    		f[i] += f[i ^ lb(k)] ;
    		if(f[i] >= mod) f[i] -= mod ;
    		k -= lb(k) ; //用lowbit快速找出每一位的1 
		}
	}	
    cout << f[(1 << n) - 1]  ;
	return 0 ;
}
```

---

## 作者：Exschawasion (赞：3)

状态压缩 dp。

一个比较显然的思路是设 $S$ 为状态。记十进制数 $S$ 二进制表示下的第 $i$ 位为 $S_i$，则 $S_i=0$ 表示第 $i$ 个数选过，$S_i=1$ 表示第 $i$ 个数未被选过。

状态转移方式为：每次枚举 $x \in [1, n]$；如果 $S_i=0$，则检查加入第 $x$ 个数之后总和是否为禁止选中的数，如果不是则将 $S_i$ 设为 $1$ 并转移。很容易看出这个算法的时间复杂度是 $\mathcal{O}(n2^n) $，会超时。一个优化是把每次直接枚举 $x \in [1, n]$ 换成枚举所有 $S_x=0$ 的 $x$，这确实能优化，但是效果有限：平均情况下 $S$ 有一半的位是 $0$，这个优化仅仅是把常数缩减到原来的 $\frac{1}{2}$，仍然无法通过 $n \leq 24$ 的数据。

由此，需要想办法将时间复杂度中的 $n$ 因子去除。可以发现，状态 $S(\texttt{111100})$ 会被 $S(\texttt{111000})$、$S(\texttt{110100})$ 等多个状态转移到。虽然状态计算可以达到 $\mathcal{O}(1) $，**但是状态转移也会耗费时间**。这就是症结所在。

![](https://i.bmp.ovh/imgs/2022/06/27/53eecacbde5c28b7.png)

状态之间的转移可以看成一张有向无环图，既然正着遍历耗费时间，那就反着遍历。对于每一个状态，寻找**所有能够转移到该状态的状态**，将它们的可能数相加即为该状态的总可能数，即**加法原理**。

![](https://i.bmp.ovh/imgs/2022/06/27/5f274d14b04451ce.png)

能转移到该状态的状态，很明显就是将 $S$ 中所有为 $1$ 的位依次设为 $0$ 并相加。寻找所有为 $1$ 的位就是 `lowbit` 操作。另外需要计算一下当前状态 $a_x$ 的总和，如果发现总和为被禁止的数则不进行转移。相对容易，见代码即可。时间复杂度是 $\mathcal{O}(2^n \log n) $。

```
#include <bits/stdc++.h>

using namespace std;

const int maxn = 24;
const int mod = 1e9 + 7;

int a[maxn + 2];
int sum[1 << maxn];
int f[1 << maxn];
int bad[maxn + 2];
int badcnt;

#define lowbit(x) ((x) & -(x))

int main() {
	int n, target;
	scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", &sum[1 << i]); target = (1 << n) - 1;
	scanf("%d", &badcnt); for (int i = 1; i <= badcnt; i++) scanf("%d", &bad[i]);
	f[0] = 1; // 初始化 
	for (int i = 1; i <= target; i++) {
		sum[i] = sum[i xor lowbit(i)] + sum[lowbit(i)]; // 计算当前状态下 a[x] 的总和 
		if (sum[i] != bad[1] && sum[i] != bad[2]) { // 不是被禁止的数 
			for (int j = i; j; j -= lowbit(j)) f[i] += f[i xor lowbit(j)], f[i] %= mod; // 枚举所有为 1 的位，即找出去掉该位后的状态 
		}
	}
	printf("%d\n", f[target]);
	return 0;
}
```


---

## 作者：fanypcd (赞：3)

妙妙题。

不开 -O2 过不了还是有点离谱的。

数据范围启示我们这是状压 dp。

考虑将当前用过的卡片的状态压成一个二进制数 $S$，设 $f_{S}$ 表示当前的使用状态为 $S$ 时达成的方案数。（1 表示已经使用，0 表示未使用）

容易发现转移方程是 $f_{S}= \sum f_{S'}\ (s.t.\ S' \ \texttt{是}\ S\ \texttt{中去除一个使用过的卡片得到的集合})$

然后写出来就是：

```
for(int state = 0; state < (1 << n) - 1; state++)
{
	int tmp = 0;
	for(int i = 0; i < n; i++)
	{
		if(state & (1 << i))
		{
			tmp += a[i + 1];
		}
	}
	for(int i = 0; i < n; i++)
	{
		if(!(state & (1 << i)))
		{
			if(tmp + a[i + 1] != b1 && tmp + a[i + 1] != b2)
			{
				f[state | (1 << i)] = (f[state | (1 << i)] + f[state]) % mod;
			}
		}
	}
}
```

复杂度 $O(n\times 2^n)$，过不了啊。

---
考虑妙妙的优化。

首先发现不用每次都去求当前集合 $S$ 所对应的位置（$\sum \limits_{i \in S}a_i$），可以预处理出来。

令 $g_{S}$ 表示当前集合为 $S$ 时的 $\sum \limits_{i \in S}a_i$，那么可以这么转移 g：

```cpp
for(int state = 1; state < (1 << n); state++)
{
	g[state] = g[state ^ lowbit(state)] + a[lg2[lowbit(state)] + 1];
}
```

即考虑 g 从最低位的取了的卡牌所代表的值转移过来，即 $\log_2 {\text{lowbit}(S)}$。（每个 2 的整数次幂对应的指数可以预处理出来）

然后同样的，我们发现在转移 f 的过程中 S 可能有不少位置本来就是 1，但是我们只需要枚举 0 的位置。

同样考虑用 lowbit 实现 0 的位置的枚举（先要将 S 取反，再从低到高减去 lowbit 来取到每一位）。

注意这里不能使用 ```~``` 运算，因为更高位的 0 我们不希望改成 1。

优化过后，发现均摊下来会少一半的次数（即 $[0,2^n]$ 的二进制表示下 0 的个数是 $2^{n - 1}$）。

复杂度为 $O(n \times 2^{n - 1})$。

```cpp
for(int i = state ^ ((1 << n) - 1); i; i -= lowbit(i))
{
	if(g[state] + a[lg2[lowbit(i)] + 1] != b1 && g[state] + a[lg2[lowbit(i)] + 1] != b2)
	{
		f[state | lowbit(i)] = (f[state | lowbit(i)] + f[state]) % mod;
	}
}
```

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
const int mod = 1e9 + 7;
#define N 25
int n, a[N];
int m, b1 = 0x3f3f3f3f, b2 = 0x3f3f3f3f;
int f[1 << N], g[1 << N], lg2[1 << N];
inline int lowbit(int x)
{
	return x & (-x);
}
signed main()
{
	read(n);
	for(int i = 1; i <= n; i++)
	{
		read(a[i]);
	}
	read(m);
	if(m >= 1)
	{
		read(b1);
	}
	if(m >= 2)
	{
		read(b2);
	}
	f[0] = (b1 && b2);
	for(int i = 0, now = 1; i <= n; i++, now <<= 1)
	{
		lg2[now] = i;
	}
	for(int state = 1; state < (1 << n); state++)
	{
		g[state] = g[state ^ lowbit(state)] + a[lg2[lowbit(state)] + 1];
	}
	for(int state = 0; state < (1 << n) - 1; state++)
	{
		for(int i = state ^ ((1 << n) - 1); i; i -= lowbit(i))
		{
			if(g[state] + a[lg2[lowbit(i)] + 1] != b1 && g[state] + a[lg2[lowbit(i)] + 1] != b2)
			{
				f[state | lowbit(i)] = (f[state | lowbit(i)] + f[state]) % mod;
			}
		}
	}
	printf("%d", f[(1 << n) - 1]);
	return 0;
}
```

---

## 作者：eastcloud (赞：2)

## P2396 yyy loves Maths VII 题解

### 题意简述

给出 $ n $ 张卡片和最多两个厄运格子，每次可以使用一张卡片并使 yyy 前进 $ a_i $ 格，求使 yyy 全部用完卡片且不踩到厄运格子的方案数。

### 做法简析

看到方案数，每张卡片只有一张，又看到这么小的数据范围，我们就可以直接想到采取状压 dp 的方式。

将每张卡片使用过记为 1，未使用过记为 0，使用一个二进制数记录状态。

对于转移，我们则可以考虑在计算此状态时，任意扣掉使用过的一张卡片的状态肯定被计算过，我们便可以枚举最后一张使用的卡片，从上个阶段转移。

但是注意数据范围，这个算法会被卡常，需要优化，注意到我们每次枚举时都是去找一个当前二进制数对应为 1 的位，我们便可以使用 lowbit 运算优化查找的步骤，便可 AC。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#define mod 1000000007
#define ll long long
using namespace std;
int num[30];
int dp[(1<<24)];
int val[(1<<24)];
int main(){
	int n,a=0,b=0,m;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>val[(1<<(i-1))];
	cin>>m;
	if(m==1) cin>>a;
	else if(m==2) cin>>a>>b;
	dp[0]=1;
	for(int i=0;i<(1<<n);i++){
		if(i==0) continue;
		int tmp=i,x,flag=0;
		while(tmp){
			x=(tmp&(-tmp));
			if(!flag){
				val[i]=val[i-x]+val[x];
				if(val[i]==a || val[i]==b) break;
				flag^=1;
			}
			dp[i]=(dp[i]+dp[i-x])%mod;
			tmp-=x;
		}
	}
	cout<<dp[(1<<n)-1];
}
```


---

## 作者：Mobius127 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P2396)

---
>>题目大意

> 给出一堆数，让你对其进行排序，求有多少种方案满足任意前缀和不会出现给定的数字。
---

看到这么小的数据范围果断状压。

令 $f_S$ 为选择状态为 $S$ 的方案数，易知最终答案为 $f_{2^n-1}$ 。

考虑 $f_S$ 珂以由哪些前继状态 $f_T$ 转移而来，因为每次只能选一个，所以 $S$ 与 $T$ 应该满足：$S \oplus  T = 2^p | S>T$，异或相当与把除了选择的数之外的的去掉，然后只剩一个数就必然是 $2^p$ 了。

直接一个个枚举 $T$ 肯定是会爆的，我们可以拿一个东西记录最后一个位是什么，然后将一个原值等于 $S$ 的寄存器异或掉她，然后拿这个寄存器的最后一位去异或 $S$ 即可枚举到所有可能的 $T$。

上面的一个过程都离不开一个操作：取最后一位，想必学过树状数组的同学都能回忆起来它是 $\text{lowbit(x)}$。

我们再把状态转移方程列出：

$$f_S=\sum_{T \oplus S = 2^p}^{(0,S)} f_T$$

这是没有限制的情况。

那如果有限制呢？

很简单，只要 $S$ 所表示的选择状态和被限制赋值为 0 即可。

这个和珂以直接每次 $O(\log n)$ 暴力求，也可以类似于 $f$ 一样求。

### Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define N 100005
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const int mo=1e9+7;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int n, k, notin[3], R;
int a[1<<24], f[1<<24];
signed main(){
	n=read(), R=1<<n;
	for(int i=1; i<R; i<<=1) a[i]=read();
	k=read();for(int i=1; i<=k; i++) notin[i]=read();
	f[0]=1;
	for(int S=1; S<R; S++){
		a[S]=a[S^lowbit(S)]+a[lowbit(S)];
		if(a[S]==notin[1]||a[S]==notin[2]) continue;
		for(int T=S; T; T^=lowbit(T)) f[S]=(f[S]+f[S^lowbit(T)])%mo;
	}
	printf("%d", f[R-1]);
	return 0;
}

```


---

## 作者：404Not_Found (赞：1)

考虑状压 dp。

设 $f(S)$ 为将集合 $S$ 内的卡片全部选的方案数，$d(S)$ 表示将集合 $S$ 内的卡片全部选之后的位置。转移容易想到：

$$f(S)=\sum_{i \in S} f(S-\{i\})$$

时间复杂度： $\mathcal{O}(n2^n)$。过不去。

考虑转移的过程，实质上就是取出每一位上的 $1$。这个操作可以用 $\mathrm{lowbit}$ 优化。

时间复杂度：$\mathcal{O}(2^n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 24;
const int P = 1e9+7;
#define lowbit(x) (x&-x)
int n,m,a[1<<N],f[1<<N],b[2];
int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		a[1<<(i-1)]=x;
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++) scanf("%d",&b[i]);
	f[0]=1;
	for(int i=1;i<(1<<n);i++)
	{
		a[i]=a[lowbit(i)]+a[i^lowbit(i)];
		if(a[i]==b[0]||a[i]==b[1]) continue;
		for(int j=i;j;j-=lowbit(j)) f[i]=(f[i]+f[i^lowbit(j)])%P;
	}
	printf("%d\n",f[(1<<n)-1]);
}
```

---

## 作者：AIskeleton (赞：0)

状压好题。

### 题意

> 给你一个长度为 $n$ 的正整数序列 $a$，再有 $k$ 个正整数。
求有多少种 $a$ 的排列方式使得其前缀和不会成为那 $k$ 个数里的任意一个。

### 题解

因为 $n \le 24$，明显是状压。

假设 $f_i$ 表示在状态为 $i$ 的情况下的组合方法数，则答案为 $f_{2^n-1}$。

考虑如何转移。

对于 $f_i$ 可以由 $f_j$ 转移而来，其中 $j$ 是 $i$ 去掉一个元素得来的。

那么状态转移方程就是 $f_i = \sum f_j$，在循环内枚举每一位的情况即可。

因为要用到取最后一位的操作，所以要用到 lowbit 进行优化。

定义一个数组 a，其中 $a_i$ 存储在情况 $i$ 下的元素之和，很容易理解。

对于一个新的 $a_i$，$a_i = a_{lowbit(i)} + a_{i \, \operatorname{xor}  \, lowbit(i)}$。

### 代码

亲测不开 O2 能过。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lb(x) (x&(-x))
using namespace std;const ll N=24,mod=1e9+7;
int a[1<<N],f[1<<N],n,k,b[N],lim;
int main(){
    cin>>n;lim=(1<<n)-1;for(int i=1;i<=lim;i<<=1)cin>>a[i];
    cin>>k;for(int i=1;i<=k;i++)cin>>b[i];f[0]=1;
    for(int i=0;i<=lim;i++){
	a[i]=a[i^lb(i)]+a[lb(i)];
	if(a[i]!=b[1]&&a[i]!=b[2])
	    for(int j=i;j;j^=lb(j))
            	f[i]=(f[i^lb(j)]+f[i])%mod;
    }cout<<f[lim];return 0;
}
```

还似乎有[双倍经验](https://www.luogu.com.cn/problem/CF327E)。

---

## 作者：peterwuyihong (赞：0)

我尝试写一个 $\purple{\text{状压}}$

题意：给定长度为 $1\le n\le 24$ 的序列 $a$，求有多少种长度为 $n$ 的排列 $\pi$，使得$\{x|x=\sum_{i=1}^ga_{\pi_i}(1\le g\le n)\}$ 中不包含给定的至多两个数。

你状压，用 $f_S$ 表示选择了 $S$ 集合的方案数，那么如果集合 $nxt$ 之和不为你给定的数。

$$f_{nxt}\leftarrow f_{nxt}+f_{pre}$$

```cpp
#include<stdio.h>
int n,a[24],m;
const int p=1e9+7;
#define add(a,b) ((a+=b)>=p&&(a-=p))
#define mul(a,b) a=1ll*a*b%p;
int f[1<<24],g[1<<24];
int A,B;
int G(int x){
	int ans=0;
	for(int i=0;i<n;i++)
	if(x>>i&1)ans+=a[i];
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",a+i);
	scanf("%d",&m);
	if(m==0){
		int ans=1;
		for(int i=1;i<=n;i++)mul(ans,i);
		printf("%d",ans);
	}else
		for(int i=0;i<1<<n;i++)g[i]=G(i);
	if(m==1){
		scanf("%d",&A);
		f[0]=1;
		for(int S=0;S<1<<n;S++)
		for(int i=0;i<n;i++)if(!(S>>i&1)){
			int T=S|(1<<i);
			if(g[T]!=A)add(f[T],f[S]);
		}
		printf("%d",f[(1<<n)-1]);
	}
	if(m==2){
		scanf("%d%d",&A,&B);
		f[0]=1;
		for(int S=0;S<1<<n;S++)
		for(int i=0;i<n;i++)if(!(S>>i&1)){
			int T=S|(1<<i);
			if(g[T]!=A&&g[T]!=B)add(f[T],f[S]);
		}
		printf("%d",f[(1<<n)-1]);
	}
}
```

然后你被卡常了。

我们注意到有很多冗余操作白白跑了很多个 $\text{skip}$ 的 $\text{if}$，于是你换为枚举 $T$，然后用 `__builtin_ctz` 把 $1$ 取出来就行了。

```cpp
#include<stdio.h>
int n,a[24],m;
const int p=1e9+7;
#define add(a,b) ((a+=b)>=p&&(a-=p))
#define mul(a,b) a=1ll*a*b%p;
int f[1<<24],g[1<<24];
int A,B,S,T;
int G(int x){
	int ans=0;
	for(int i=x;i;i-=i&-i)ans+=a[__builtin_ctz(i)];
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",a+i);
	scanf("%d",&m);
	if(m==0){
		int ans=1;
		for(int i=1;i<=n;i++)mul(ans,i);
		printf("%d",ans);
	}else
		for(int i=0;i<1<<n;i++)g[i]=G(i);
	if(m==1){
		scanf("%d",&A);
		f[0]=1;
		for(T=1;T<1<<n;T++)
		for(int i=T;i;i-=i&-i){
			S=T^(1<<__builtin_ctz(i));
			if(g[T]!=A)add(f[T],f[S]);
		}
		printf("%d",f[(1<<n)-1]);
	}
	if(m==2){
		scanf("%d%d",&A,&B);
		f[0]=1;
		for(T=1;T<1<<n;T++)
		for(int i=T;i;i-=i&-i){
			S=T^(1<<__builtin_ctz(i));
			if(g[T]!=A&&g[T]!=B)add(f[T],f[S]);
		}
		printf("%d",f[(1<<n)-1]);
	}
}
```

---

