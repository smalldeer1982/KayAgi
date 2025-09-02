# [USACO05MAR] Space Elevator 太空电梯

## 题目描述

奶牛们要去太空了！它们打算用方块建造一座太空电梯。现在它们有 $N$ 种方块，第 $i$ 种方块有一个特定的高度 $h_i$，一定的数量 $c_i$。为了防止宇宙射线破坏方块，第 $i$ 种方块的任何部分不能超过高度 $a_i$。\
请用这些方块堆出最高的太空电梯。

## 说明/提示

对于 $100\%$ 的数据：$1\le N\le 400$，$1\le h_i \le 100$，$1\le c_i\le 10$，$1\le a_i\le 4\times 10^4$。

## 样例 #1

### 输入

```
3
7 40 3
5 23 8
2 52 6
```

### 输出

```
48
```

# 题解

## 作者：AgrumeStly (赞：37)

> [P6771](https://www.luogu.com.cn/problem/P6771)

这是一道很明显的 dp 问题。

首先 dp 最重要的三要素是：动态表示、动态转移、初始状态。  
只要这三个要素搞明白了，基本就能把这题做出来了。

### solution

让我们来看看这题的动态表示、动态转移和初始状态。

**状态表示**：  
$dp_{i,j}$ 表示用前 $i$ 种方块是否可以拼成高度 $j$  

**状态转移**：  
$
dp_{i,j}=
\begin{cases}\\\\\\\\\\\end{cases}
\begin{matrix}
dp_{i-1,j} && \text{用}0\text{块第}i\text{种方块}\\
dp_{i-1,j-h_{i}} && \text{用}1\text{块第}i\text{种方块}\\
&\ldots&\\
dp_{i-1,j-k\times h_{i}} && \text{用}k\text{块第i种方块}\\
&\ldots&\\
dp_{i-1,j-c_{i}\times h_{i}} && \text{用}c_{i}\text{块第}i\text{种方块}\\
\end{matrix}$  
$
dp_{i,j}|=dp{i,j-k\times h_{i}};(h_{i}\le j\le a_{i}, 1\le k\le c_i)
$  

**初始状态**：  
$dp_{i,j}=\mathrm{false};dp_{0,0}=\mathrm{true}$


最后物品维可以直接省掉，即：  
$dp_{j}|=dp_{j-k\times h_{i}};(h_{i}\le j\le a_{i}, 1\le k\le c_i)$

那么写出这三要素就很容易写出代码了

### code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#define line cout << endl
using namespace std;

const int NR = 405;
struct node {
	int h, a, c;
};
node e[NR];
int n;
bool dp[40005];

bool cmp (node x, node y) {
	return x.a < y.a; 
}

int main () {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> e[i].h >> e[i].a >> e[i].c;
	dp[0] = true;
	sort (e + 1, e + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= e[i].c; j++) {
			for (int k = e[i].a; k >= e[i].h; k--) {
				dp[k] |= dp[k - e[i].h];//动态转移方程
			}
		}
	}
	for (int i = e[n].a; i >= 0; i--) {
		if (dp[i]) {
			cout << i << endl;
			break;
		}
	}
	return 0;
}
```

---

## 作者：SzTC (赞：20)

## 题目大意
共有 $N$  种方块，每种方块的高度为 $h[i]$ ，且有 $c[i]$ 件，同时任何一件物品的高度不超过 $a[i]$ $($注：此处的“高度”指的是方块叠在一起后的总高度，包括垫在下方的方块，而不是该种方块单独的高度$)$，求堆叠成的最高高度。  
## 思路分析
由题意明显得这是一道多重背包的DP  
如果对背包问题还不太了解的，推荐先去做一下这些基础背包题：
- [P2871 [USACO07DEC]Charm Bracelet S](https://www.luogu.com.cn/problem/P2871)
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)    
- [P1049 [NOIP2001 普及组] 装箱问题](https://www.luogu.com.cn/problem/P1049)
- [P2347 [NOIP1996 提高组] 砝码称重](https://www.luogu.com.cn/problem/P1049)


对背包问题有了一点基础的了解之后，再来看这题就会容易很多。背包的“重量”和“价值”都是方块的高度，而问题就在于如何解决高度限制的问题。  
这个问题的解决也并不复杂，只需要每个物品进行dp时都从头开始到最高高度就可以了。原因：在dp时限制高度保证了高度不会超过限制；每次从头开始保证了不会发生像贪心一样的错误。  
还有两个注意点：  
1. 根据分析我们可以知道高度高的答案转移自高度低的答案，因此在dp开始前要先将方块高度从低到高排序，$($以最高高度 $a[i]$ 排$)$，先算低的。
2. 最后的答案不一定在最后一个方块的最高处，从1到最高都有可能出现答案。  

最后得出代码：
```cpp
      
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{	//使用结构体，方便排序
	int h,a,c;
} a[11111111];
bool cmp(node x,node y)
{
	return x.a<y.a;
}
int f[11111111];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a[i].h,&a[i].a,&a[i].c);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		for(int k=1;k<=a[i].c;k++)//多重背包
		{
			for(int j=a[i].a;j>=a[i].h;j--)
			{
				f[j]=max(f[j],f[j-a[i].h]+a[i].h);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=a[n].a;i++)//寻找答案
	{
		ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Froranzen (赞：9)

[题目传送门~](https://www.luogu.com.cn/problem/P6771)


------------

# 思路


------------
有 N 种方块，第 i 种方块的高度为 $h_i$ ,数量数量为 $c_i$ 。第 i 种方块的任何部分不能超过高度 $a_i$ ，求能搭建的最大高度。


显然，这是一道**多重背包**的动态规划题目。

我们定义一个数组 $vis$ 代表**当前高度是否到达过**。同时再定义一个 $qwq$ 的二维数组，**$qwq[i][j]$表示，搭建到 $j$ 的高度需要多少个 $i$ 类型的方块**，这样利用我们进行多重背包的数量统计。 易得转移方程：
$$ vis[0] = 1$$
$$ vis[j] = vis[j - e[i].h] $$
$$ qwq[i][j] = qwq[i][j - e[i].h] + 1$$

这道题目还有一个坑点，就是**循环的顺序**。
```cpp
比如，我们有一个高度为 100，限制为 110 的方块，同时还有一个高度为 5，限制为 99 的方块。
如果先放高度为 100 的方块，那么高度为 5 的方块就无法放下，答案为 100。
但是，最优解是先放高度为 5 的方块，再放高度为 100 的方块，最终答案为 105。
```

所以，为了避免出现上述第一种情况的出现，我们dp前要**先已高度限制为关键字从小到大排序**。


------------

# 代码


------------

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

inline char nc (){  //fread 快读
	static char buf[100000],*p1 = buf,*p2 = buf;  //static：声明一个全局变量
	return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 100000,stdin), p1 == p2) ? EOF: *p1++; 
}

inline int read () {
	register int x(0), f(1);
	char ch = nc ();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			f = ~f +1;
		ch = nc ();
	}
	while (ch <= '9' && ch >= '0') {
		x = (x<<3) + (x<<1) + (ch ^ 48);
		ch = nc ();
	}
	return x * f;
}

struct node {
	int h, a, v;
}e[44444];

bool cmp (node a, node b) {  //高度限制为关键字排序
	return a.a < b.a;
}

int n;
int i(1);
int qwq[2333][2333];
bool vis[233333];
int ans;

int main () {
	n = read ();
	for (; i <= n - 8; i += 8) {  
		e[i].h = read (), e[i].a = read (), e[i].v = read ();
		e[i +1].h = read (), e[i +1].a = read (), e[i +1].v = read ();
		e[i +2].h = read (), e[i +2].a = read (), e[i +2].v = read ();
		e[i +3].h = read (), e[i +3].a = read (), e[i +3].v = read ();
		e[i +4].h = read (), e[i +4].a = read (), e[i +4].v = read ();
		e[i +5].h = read (), e[i +5].a = read (), e[i +5].v = read ();
		e[i +6].h = read (), e[i +6].a = read (), e[i +6].v = read ();
		e[i +7].h = read (), e[i +7].a = read (), e[i +7].v = read ();
	}
	for (; i <= n; ++i) {
		e[i].h = read (), e[i].a = read (), e[i].v = read ();
	}
  //循环展开，等价于：
  //for (register int i(1); i <= n; ++i) e[i].h = read (), e[i].a = read (), e[i].v = read ();
	sort (e +1, e +n +1, cmp);
   vis[0] = 1;  //初始化
	for (register int i(1); i <= n; ++i) {
		for (register int j(e[i].h); j <= e[i].a; ++j) {
			if (vis[j - e[i].h] && qwq[i][j - e[i].h] < e[i].v && !vis[j]) {  //能从上一个状态转移，且方块数量足够
				vis[j] = 1;  //标记
				qwq[i][j] = qwq[i][j - e[i].h] +1;  //转移
				if (j > ans) ans = j;  //更新答案
			}
		}
	}
	printf ("%d", ans);
}
```


------------

（[悄悄要个关注](https://www.luogu.com.cn/user/361432)，不过分吧）


---

## 作者：Viktley (赞：8)

**题意：**

有 $n$ 种方块，第 $i$ 种方块有 $c[i]$ 个，每个高度为 $h[i]$, 问每一种方块高度不超过 $a[i]$ 的最高高度

------------

**思路：**

本题是一个多重背包问题模型。
“方块” 为物品， “方块高度” 为面积，$a[i]$ 为背包的总容量。
这道题目没有 “物品价值” 属性，不是一个最优化问题，而是一个可行性问题。
按照我们学过的DP算法，可以依次考虑第 $i$ 种方块是否放入背包，以 “已近考虑过的物品种数” $i$ 作为DP的 “阶段” ，在 “阶段” $i$ 时， $f[j]$ 表示前 $i$ 种方块的最高高度。

是不是以为已近结束了，没有，这是我一开始的想法，当然也能对。但是我们最近在学位运算，我想了个更简单的方法：我们先用两重循环来模拟第 $i$ 种方块放背包（~~先不管容量~~）,然后我们再用一个神奇的符号 “$<<$” 来表示背包容量的限制就欧了

__code：__

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<bitset>
#include<iostream>
using namespace std;

int n;
#define maxn 411
struct Obj{int h,m,c;}a[maxn];
bool cmp(const Obj &a,const Obj &b) {return a.m<b.m;}
bitset<40011> f,tmp,t;
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d%d%d",&a[i].h,&a[i].m,&a[i].c);
    f.reset();f[0]=1;
    tmp.set();
    sort(a+1,a+1+n,cmp);
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=a[i].c;j++)
            f|=(f<<a[i].h);
        t=tmp<<(a[i].m+1);t.flip();
        f&=t;
    }
    int ans;
    for (ans=40000;ans;ans--) if (f[ans]) break;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：勘探员·引魂人 (赞：6)

**前言：由于  ~~不想写~~   学页繁忙的原因，几乎一年没发题解了，最近在学这方面的知识，所以发篇题解康康  ~~希望能过（doge）~~**

**思路：低批（dp）（根据砖块的高度来建立动态转移方程）**

------------

# **上代码！**

```
#include<algorithm>
#include<cstdio>
#include<iostream>//文件头不讲
using namespace std;
struct data
{
    int h,a,c;
}dp[400+5];//用struct定义
bool cmp(data x,data y)
{
    return x.a<y.a;//struct的专用排序法，越小的高度限制排在越前
}
bool f[400+5][40000+5];//bool数组是来判断最后结果的
int n,k;//定义变量（应该没人不会吧）
int main()
{
    /*scanf ("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&dp[i].h,&dp[i].a,&dp[i].c); 
    }*/输入不讲
    sort(dp+1,dp+1+n,cmp);//动规都是要先排序der
    f[0][0]=true;//划重点，初始的0,0位置必须是true，否则再见
    for(int i=1;i<=n;i++)
    {
        for(int j=dp[i].a;j>=0;j--)//从第dp[i]的最大高度限制到小枚举
        {
            for(int k=0;k<=dp[i].c;k++)//从0枚举到最大块数
            {
                if(f[i-1][j-dp[i].h*k]==true&&j-dp[i].h*k>=0) f[i][j]=true;//动态转移方程，如果f[i-1][j-当前高度*k]==true&&j-当前高度*k>=0，那么这个格子就是true的
            }
        }
    }
    for(int j=dp[n].a;j>=0;j--)//寻找最优值并输出
    {
        if(f[n][j]==true)
        {
            printf("%d",j);
            return 0;
        }
    }
     
    return 0;//完结
}
```
# 最后说一句：我回坑啦！

---

## 作者：Inlay1158 (赞：6)

这道题目是一道显然的背包问题，但不是直接做的的背包问题，由于每样物品都有堆放的最大高度限制，所以最大高度限制越低的就要放越底下，这样答案才可能最大，因为这样在较低的高度的时候，达到的高度尽可能的大，所以先按限制高度排序，然后同时以该物品的高度为体积和价值，由于 $k \times h \times c$ 不大，所以直接做多重背包即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 400 + 7;
const int M = 4e4 + 10;
struct node {
	int h, a, c;
	node(int h = 0, int a = 0, int c = 0): h(h), a(a), c(c){}
	friend bool operator <(node x, node y) {
		return x.a < y.a;
	}
};
node b[N];
int n, h, a, c, ans, maxa, dp[M];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &h, &a, &c);
		maxa = max(maxa, a), b[i] = node(h, a, c);
	}
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; ++i) {
		h = b[i].h, a = b[i].a, c = b[i].c;
		for (int j = 1; j <= c; ++j)
			for (int k = a; k >= h; --k)
				dp[k] = max(dp[k], dp[k - h] + h);
	}
	for (int i = 1; i <= maxa; ++i) ans = max(ans, dp[i]);//这个地方我不确定dp[maxa]是否最大，保险起见取个max
	return 0 & printf("%d", ans);
}
```



---

## 作者：SingularPoint (赞：4)

### 题目大意
给出方块种类（<=400），求用现有的的方块在 **使用数目不超过方块个数 ci ，方块所处高度不超过其最大限制高度 ai** 时可以达到的最大高度
### 分析
“种类”、“个数”、“最大高度”等字眼再加上<=400的数据范围，相信大家很快就能够看出来这是一道DP，将“方块”作为“物品”，“高度”作为“体积”，显而易见——**多重背包**。

1. 定义状态：注意到题目中“高度”一量既是所求答案又是运算的判断条件（即同时作为多重背包的“重量”和“价值”），所以我们可以考虑**将$f(i)$定义为高度 i 是否可行**，得出状态转移方程$f(i)=f(i-h_{i})$，特殊的：$f(0)=1$。

1. 考虑边界：本题中边界有两个：ci和ai。在DP的循环条件中我们可以将ai作为循环终止的条件进行判断，现在考虑对方块使用个数ci的判断： 对于循环中的每种方块 i 达到的高度 j ，我们可以设定一个计数数组来记录这个状态下使用的方块 i 的个数，**到达高度 j 时的使用个数就等于$cnt(i,j-h_{i})+1$**。

1. 特殊情况：在循环的途中我们发现，如果在前面的循环中计算了 ai 较大的方块，后面 ai 较小的方块将不会被计算，所以我们可以在DP前使用一个**贪心策略**：将方块按照 ai 从小到大排序。

有了上面的分析过程，相信代码也很快可以完成辣~

### 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int M=200000;
int n,ans=0;
struct node{
	int h,c,a;
}p[405];
int cnt[405][M];
bool f[M];
bool cmp(node x,node y)
{return x.a<y.a;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&p[i].h,&p[i].a,&p[i].c);
	sort(p+1,p+n+1,cmp);//将方块按照ai排序以避免出错 
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=p[i].h;j<=p[i].a;j++)
			if(f[j-p[i].h]&&!f[j]&&cnt[i][j-p[i].h]<p[i].c){//在这里必需要有“!f[j]”的判断，以防cnt被重复计算 
				cnt[i][j]=cnt[i][j-p[i].h]+1;
				f[j]=1;
				ans=max(ans,j);//ans记录答案（可行的最大高度） 
			}
	printf("%d",ans);
	return 0;
 } 
```
完结撒fa~

---

## 作者：syf2008 (赞：3)

这是一道dp(~~这不废话~~)中的多重背包题，就是多了一个限制

这题我们可以不用二进制优化来做，因为数据比较小

上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct ss{int h,a,c;}s[405];
inline bool cmp(ss x,ss y){return x.a<y.a;}//根据限制高度排序
int n,f[40005]={1},dp[405][40005],maxn=0;//f存状态，dp存结果
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>s[i].h>>s[i].a>>s[i].c;
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++)
	for(int j=s[i].h;j<=s[i].a;j++)//枚举
	if(f[j-s[i].h]==1&&dp[i][j-s[i].h]<s[i].c&&!f[j])
	{
	f[j]=f[j-s[i].h];
	dp[i][j]=dp[i][j-s[i].h]+1;
	maxn=max(maxn,j);//取最大值
	}
	cout<<maxn;
}
```

---

## 作者：丧黑福造 (赞：2)

$\text{CSP2020 RP++}$

本题并不是传统意义上的$DP$，加上了贪心和枚举的思路

大致题意：$N$种木块，每种高度为$h_i$，数量$c_i$，求不能超过$a_i$的**最大**高度

贪心：如果在前面的计算中计算了较大的方块$a_j$，则后面小于$a_j$的方块将不会被计算。故在$DP$前将方块按照从小到大排序。

对于每个木块而言，$j$从$a_i$枚举到$h_i$，如果$j$可行，则$ans=max(ans,j)$

* 如何记录高度是否可行$?$

设$f_j$表示$j$的高度是否可行，初始状态$f_0=1$

* 怎样保证$c_i$的合法呢$?$

设$t_{ij}$表示第$i$块木块高度为$j$的数量，如果合法，每次累加1

$code$:

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
inline int read(int &x) {//快读
	x = 0;
	int f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
struct ac {
	int h, a, c;
}a[405];//结构体
bool f[40005];//因为f[i]的状态只会为0或1，所以可以用bool数组
int t[405][40005];
int ans;
inline bool cmp(ac x, ac y) {
	return x.a < y.a;
}
main() {
	int n;
	read(n);
	f[0] = 1;//初始化
	for (register int i = 1; i <= n; i ++) {//读入
		read(a[i].h);
		read(a[i].a);
		read(a[i].c);
	}
	sort (a+1, a+n+1, cmp);//贪心
	for (register int i = 1; i <= n; i ++) {
		for (register int j = a[i].h; j <= a[i].a; j ++) {//枚举最高的可行高度
			if (f[j-a[i].h] == 1 && t[i][j-a[i].h] < a[i].c && !f[j]) {//这里只能是<，如果是<=，当等号成立且其他条件都满足时，t[i][j]在加1，已经超过c[i]了
				f[j] = 1;
				t[i][j] = t[i][j-a[i].h] + 1;//累加
				ans = ans > j ? ans : j;//三目运算符，求ans最大值，等同于ans=max(ans,j);
			}
		}
	}
	printf ("%d\n", ans);
	return 0;
}
```

---

## 作者：JK_LOVER (赞：2)

## 题意
$n$ 种物品，每一种物品有各自的高度，数量，最高限制。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-p6771)
## 分析
用 $dp[i][j]$ 表示，考虑前 $i$ 种物品时，能否搭出高度为 $j$ 的。那么可以发现高度限制越小的必须优先考虑。那么直接 $O(w\times n\times c)$ 是可以接受的。

- 细节， $dp[i][j]$ 只有 $0/1$ 两种状态，可以用 $bitset$ 优化。方程可以滚动，优化空间。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 505;
int K;
struct Node{int h,c,a;}s[N];
bool cmp(Node a,Node b){return a.a<b.a;}
int dp[505][50100];
int main()
{
	cin>>K;
	for(int i = 1;i <= K;i++)
	cin>>s[i].h>>s[i].a>>s[i].c;
	sort(s+1,s+1+K,cmp);
	dp[0][0] = 1;
	for(int i = 1;i <= K;i++)
	{
		for(int k = 0;k <= s[i].c;k++)
		{
			for(int j = 0;j <= 4e4;j++)
			{
				if(j-k*s[i].h < 0) continue;
				if(dp[i-1][j-k*s[i].h] && j <= s[i].a)
				{
					dp[i][j] = 1;
				}
			}
		}
	}
	for(int i = 4e4;i>=0;i--){
		if(dp[K][i]){
			cout<<i<<endl;
			return 0;
		}
	}
}
```


---

