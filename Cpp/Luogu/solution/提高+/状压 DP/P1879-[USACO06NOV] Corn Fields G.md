# [USACO06NOV] Corn Fields G

## 题目描述

Farmer John has purchased a lush new rectangular pasture composed of M by N (1 ≤ M ≤ 12, 1 ≤ N ≤ 12) square parcels. He wants to grow some yummy corn for the cows on a number of squares. Regrettably, some of the squares are infertile and can't be planted. Canny FJ knows that the cows dislike eating close to each other, so when choosing which squares to plant, he avoids choosing squares that are adjacent; no two chosen squares share an edge. He has not yet made the final choice as to which squares to plant.

Being a very open-minded man, Farmer John wants to consider all possible options for how to choose the squares for planting. He is so open-minded that he considers choosing no squares as a valid option! Please help Farmer John determine the number of ways he can choose the squares to plant.

农场主 $\rm John$ 新买了一块长方形的新牧场，这块牧场被划分成 $M$ 行 $N$ 列 $(1 \le M \le 12, 1 \le  N \le 12)$，每一格都是一块正方形的土地。 $\rm John$ 打算在牧场上的某几格里种上美味的草，供他的奶牛们享用。

遗憾的是，有些土地相当贫瘠，不能用来种草。并且，奶牛们喜欢独占一块草地的感觉，于是 $\rm John$ 不会选择两块相邻的土地，也就是说，没有哪两块草地有公共边。

$\rm John$ 想知道，如果不考虑草地的总块数，那么，一共有多少种种植方案可供他选择？（当然，把新牧场完全荒废也是一种方案）


## 样例 #1

### 输入

```
2 3
1 1 1
0 1 0```

### 输出

```
9
```

# 题解

## 作者：Owen_codeisking (赞：140)

## 前排警告
### 这是写给刚学的我看的，大佬请自动忽略

人生第一道状压$dp$ ~~互不侵犯是学术交流过的~~

本蒟蒻今天在机房听到状压$dp$，感觉很高大上……其实就是位运算高大上一点

#### 解释一下位运算：

& 给个例子

$0110101+1010011=0010001$，返回值为$17$

$n<<k$ 将$n$左移$k$位，相当于给$n$乘上$2^k$

$n>>k$ 将$n$右移$k$位，相当于给$n$除以$2^k$后向下取整

#### 解释一下状压$dp$：

它的基本思想就是用二进制来优美地暴力枚举出现的方案，

若二进制下第$i$位有赋值$1$，则一行的第$i$列有放牛

那么$f[i][j]$表示在前$i$行中（包括$i$）在$j$个状态下的最大方案数

易得$f[i][j]=(f[i][j]+f[i-1][k])\ mod\ p$（$p=10^9$，$j$是第$i$行的状态，$k$是第$i-1$行的状态）

所以我们还要再预处理一下，$g[i]$表示第$i$个状态是否存在，判断条件是

$g[i]=$ $!(i$&$(i>>1))!(i$&$(i<<1))$

目标状态：$f[n][i]$全部相加

$Code \ Below:$
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int p=100000000;
ll f[13][1<<12],n,m;
ll g[1<<12],h[1<<12],a[13][13];
ll F[13];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			F[i]=(F[i]<<1)+a[i][j];
	for(int i=0;i<(1<<m);i++){
		if(!(i&(i>>1))&&!(i&(i<<1))){
			g[i]=1;
			if((i&F[1])==i) f[1][i]=1;
		}
	}
	for(int x=2;x<=n;x++)
		for(int j=0;j<(1<<m);j++)
			if(((j&F[x-1])==j)&&g[j])
				for(int k=0;k<(1<<m);k++)
					if(((k&F[x])==k)&&!(j&k)&&g[k]){
						f[x][k]=(f[x][k]+f[x-1][j])%p;
					}
	int ans=0;
	for(int i=0;i<(1<<m);i++)
		ans=(ans+f[n][i])%p;
	printf("%d\n",ans);
    return 0;
}
```



---

## 作者：梅川丘库 (赞：87)

此题是我第二次打...这次感觉非常良好,,,原因是找到了一个做此类的一个套路

首先：我们可以先把一行中不能相邻的状态预处理，可以节省枚举的大量花费...

然后：对它输入状态进行处理

最后：因为是相邻，所以每排会受到上一排的影响！所以定义状态F[i][k]+=F[i-1][j],表示第i行状态为k时的方案总数等于第i-1行状态为j时的方案总数之和,其中状态k对于状态j而言是可行状态









```cpp
#include<stdio.h>
using namespace std;
const int MOD=1e8;
int f[13][2100];//表示方案数 
int can[13];//最开始可以的（输入限制） 
int donot[201];//预处理行，表示合法的状态，大概不超过101个 
bool judge(int x)
{
    return (x & (x>>1));
}
int main()
{
    int m,n; 
    scanf("%d%d",&m,&n);
    int x;
    int full=(1<<n)-1;//满状态 
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&x);
            if(!x) can[i]=can[i] | (1<<(n-j));
        }
    }
    int cnt=0;
    for(int i=0;i<=full;i++)
    {
      if(judge(i)) continue;
      donot[++cnt]=i;
    }
    int last,now;
    for(int i=1;i<=cnt;i++)
    {
        now=donot[i];
        if(donot[i] & can[1]) continue;
        f[1][i]=1;
    }
    for(int i=2;i<=m;i++)
    {
        for(int j=1;j<=cnt;j++)
        {
            last=donot[j];//上个状态 
            if(last & can[i-1]) continue;
            for(int k=1;k<=cnt;k++)
            {
                now=donot[k];
                if(now & can[i]) continue;
                if(now & last) continue;
                f[i][k]+=f[i-1][j];
                f[i][k]%=MOD;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=cnt;i++) ans=(ans+f[m][i])%MOD;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Diogenes (赞：36)

### 轮廓线dp
记录当前的轮廓线，根据当前轮廓线进行状态转移，理论时间复杂度比普通状压dp快。


------------

| |  |  |  |
| -----------: | -----------: | -----------: | -----------: |
|  |  |k3  |k4  |
|k1  |k2  | * |

* 如图，假设当前转移到*位置，轮廓线状态为二进制数k1k2k3k4，1表示第i列已选，0表示第i列未选，转移时用位运算解压出k3与k2,作出决策，并维护每一列的轮廓线即可 *



------------

代码如下

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define max(x,y) ((x)>(y) ? (x) : (y))
#define min(x,y) ((x)<(y) ? (x) : (y))
#define Mod 100000000
#define N 18
using namespace std;
//运用滚动数组优化
int d[2][65546],n,m,a[N][N],cur;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++)
			scanf("%d",&a[i][j]);
	}
	memset(d,0,sizeof d);
	cur=0;
	d[0][0]=1;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			cur^=1;
			memset(d[cur],0,sizeof d[cur]);
			for(int k=0;k<(1<<m);k++) {
				int up=(1<<j)&k;
				int left=0;//解压出左边和上面
				if(j>0) left=(1<<(j-1))&k;
				if(!i && up) continue;
				if(!j && left) continue;
				if(up && left) {//上面选了，左边选了，这个只能不选
					d[cur][k^(1<<j)]=(d[cur][k^(1<<j)]+d[cur^1][k])%Mod;
					continue;
				}
				if(up) {//上面选了，这个只能不选
					d[cur][k^(1<<j)]=(d[cur][k^(1<<j)]+d[cur^1][k])%Mod;
					continue;
				}
				if(left) {//左边选了，这个只能不选
					d[cur][k]=(d[cur][k]+d[cur^1][k])%Mod;
					continue;
				}
                //障碍不能选
				if(!a[i][j]) {
					d[cur][k]=(d[cur][k]+d[cur^1][k])%Mod;
					continue;
				}
                //除去以上状态，考虑选和不选两种情况
				d[cur][k]=(d[cur][k]+d[cur^1][k])%Mod;
				d[cur][k^(1<<j)]=(d[cur][k^(1<<j)]+d[cur^1][k])%Mod;
			}
		}
	}
	int ans=0;
	for(int i=0;i<(1<<m);i++) {
		ans=(ans+d[cur][i])%Mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Jayun (赞：30)

# 玉米田

## UPD：

2021.7.20：修改了版面、添加了两种优化方法。

## 链接：

[洛谷](https://www.luogu.org/problem/P1879)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/12037232.html)

## 题目大意：

在一个有障碍的矩阵中放置物品，要求不能相邻，求方案数。

## 思路：

很容易想到是状压 DP。

### 朴素：

设 $f_{i,j}$ 表示第 $i$ 行的方案是 $j$（是一个二进制数，用十进制来存储，第 $k$ 位是 $1/0$（二进制）表示**选或不选**）时的方案数。

声明：下面的 $j,k$ 都是一个合法的方案。

若已经进行到 $i$ 行，此时的方案是 $j$，上一行的方案是 $k$。

有一个特殊条件（边界）：$i = 1$。

既然是第一行，那么它的所以合法方案都是正确的，所以边界是：

$$f_{1,j} = 1$$

也可以很容易地想到本行的合法方案的方案数是上一行的**所有**合法方案数，也就是：

$$f_{i,j} = f_{i,j}+f_{i - 1,k}$$

### 朴素代码：

时间复杂度 $\mathcal{O}(n{F_m}^2)$，其中 $F_m$ 表示宽为 $m$ 的无障碍行的合法方案数。

```cpp
const int N = 15;
int n, m;
int f[N][(1 << N)];
int st[1 << N];
int a[N];
int tot;

void _init()     //缩小状态集合优化，判断此方案  在这一行  是不是合法的
{
	for (int i = 0; i < (1 << m); i++)
	{
		if (i & (i << 1)) continue;
		st[++tot] = i;
	}
}

int main()
{
	scanf ("%d%d", &n, &m);
	for (int j = 1; j <= n; j++)
		for (int i = m - 1; i >= 0; i--)
		{
			int x;
			scanf ("%d",&x);
			a[j] += (x << i);
		}
	_init();
	for (int i = 1; i <= tot; i++)         //边界条件
	{
		if (!((st[i] | a[1]) == a[1]))continue;  //是否合法
		f[1][st[i]] = 1;
	}
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= tot; j++)
		{
			if (!((st[j] | a[i]) == a[i]))continue;   //判断合法
			for (int k = 1; k <= tot; k++)
			{
				if (!((st[k] | a[i - 1]) == a[i - 1]))continue;  //同上条注释
				if (st[j] & st[k]) continue;
				f[i][st[j]] += f[i - 1][st[k]];      //转移
				f[i][st[j]] %= 100000000;
			}
		}
	}
	int ans = 0;
	for (int j = 1; j <= tot; j++)
		ans += f[n][st[j]], ans %= 100000000;
	printf ("%d", ans);
	return 0;
}

```

### 轮廓线 DP：

优化是无止境的。若 $n,m\leq19$，要怎么解决本题呢？

可采用轮廓线 DP。设 $f_{i,j,k}$ 表示当前点在 $(i,j)$，轮廓线的状态是 $k$ 的方案数：

|   ?   |   ?   |   ?   |   ?   |
| ---- | ---- | ---- | ---- |
|   ?   |   ?   |   $\mathrm{st}_{1}$   |   $\mathrm{st}_{2}$   |
| $\mathrm{st}_{3}$   |   $\mathrm{st}_{4}$   |   $x$   |   ?   |   

如表格，轮廓线的状态为 $\mathrm{st}_{3}\mathrm{st}_{4}\mathrm{st}_{1}\mathrm{st}_{2}$，其中 $\mathrm{st}_{n}$ 是一位二进制数，表示是否选择所在格子。

那么转移的话，考虑到 $x$ 的上面和左面是否是 $1$，分类讨论即可。关于转移方程，位运算使得公式很难看，所以还是在代码看好了。

### 轮廓线 DP 代码：

时间复杂度 $\mathcal{O}(nm2^m)$。

```cpp
const int N = 30, M = 524298;
const int mod = 100000000;

inline ll Read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int n, m, Now = 0;
int f[2][M];
int a[N][N];

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = Read();
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			Now ^= 1;
			for (int k = 0; k < (1 << m); k++)
			{
				int lf = (j == 1? 0: (k >> (j - 2)) & 1), up = (k >> (j - 1)) & 1;
				if ((i == 1 && up) || (j == 1 && lf)) continue;
				if (up) f[Now][k ^ (1 << j - 1)] += f[Now ^ 1][k];         //即上面选了，这里不能选 
				else if (lf || !a[i][j]) f[Now][k] += f[Now ^ 1][k];       //即左边选了或有障碍，这里不能选 
				else              // 都可以选 
				{
					f[Now][k] += f[Now ^ 1][k];
					f[Now][k ^ (1 << j - 1)] += f[Now ^ 1][k];
				}
			}
			for (int k = 0; k < (1 << m); k++) // 卡常数，减法的常数比取模小；
			{				//顺便实现memset(f[Now ^ 1], 0, sizeof f[Now ^ 1]) 也是卡常 
				for (; f[Now][k] > mod; f[Now][k] -= mod);
				f[Now ^ 1][k] = 0;
			}
		}
	int ans = 0;
	for (int k = 0; k < (1 << m); k++)
		ans = (ans + f[Now][k]) % mod;
	printf ("%d", ans);
	return 0;
}
```

### 轮廓线且缩小状态集合：

优化是无止境的。若 $n\leq120,m\leq21$ 呢？

在朴素中，我们用了缩小状态集合优化，使得时间复杂度从原本的 $\mathcal{O}(n4^m)$ 降到 $\mathcal{O}(n{F_m}^2)$。

为了让时间复杂度更小，我们也考虑让轮廓线 DP 也缩小状态集合。但似乎遇到一个瓶颈：朴素的状态是一整行，所以可以直接判断相邻确定合法；而轮廓线的状态可能分布在两行，就是说出现一组相邻都选的情况是合法的。难道不能确定合法吗？

跳出思维，越过瓶颈。它存在相邻的地方就是行的分割处，把它记录下来，在 DP 时根据当前点的位置就单纯枚举“当前是分割点”的状态即可。

### 轮廓线且缩小状态集合代码：

时间复杂度不会算。但实测比神仙 [cmd](https://www.luogu.com.cn/blog/command-block/zhuang-ya-dp-za-tan) 的代码快。

```cpp
const int N = 121, N2 = 22, M = 1747628, M2 = 5e4;
const int mod = 100000000;

inline ll Read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int n, m, Now = 0;
int f[2][M2];
int a[N], st[N2][M2];
short id[2][M];  // 用 short 压空间

int main()
{
	n = Read(), m = Read();
	
	for (int i = 0; i < (1 << m); i++)
	{
		int u = i & (i >> 1);
		if(u != (u & -u)) continue;
		int p = u? log2(u) + 1: 0; 
		st[p][++st[p][0]] = i;
		id[0][i] = p, id[1][i] = st[p][0];
	}
	
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < m; ++j)
			a[i] = a[i] << 1 | Read();
	
	for (int i = 1; i <= st[0][0]; i++)
		if ((st[0][i] & a[1]) == st[0][i])
			f[Now][i] = 1;
	
	for (int i = 2; i <= n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Now ^= 1;
			for (int k = 1; k <= st[0][0]; k++)  // 枚举没有分割点的状态 
			{
				if (!f[Now ^ 1][k]) continue; 
				int u = st[0][k] & (st[0][k] ^ (1 << j)), tmp = f[Now ^ 1][k];
				f[Now ^ 1][k] = 0;
				f[Now][id[1][u]] += tmp;
				f[Now][id[1][u]] -= f[Now][id[1][u]] > mod? mod: 0;
				
				if (!(a[i] & (1 << j)) || (st[0][k] & (1 << j)) || (j && (st[0][k] & (1 << j - 1)))) continue;
				
				int x = id[1][st[0][k] | (1 << j)];
				if (id[0][st[0][k] | (1 << j)]) x += st[0][0];
				f[Now][x] += tmp;
				f[Now][x] -= f[Now][x] > mod? mod: 0;
			}
			if (!j) continue;
			for (int k = 1; k <= st[j][0]; k++)  //有分割点 
			{
				if (!f[Now ^ 1][k + st[0][0]]) continue; 
				int u = st[j][k] & (st[j][k] ^ (1 << j)), tmp = f[Now ^ 1][k + st[0][0]];
				f[Now ^ 1][k + st[0][0]] = 0;
				f[Now][id[1][u]] += tmp;
				f[Now][id[1][u]] -= f[Now][id[1][u]] > mod? mod: 0;
				
				if (!(a[i] & (1 << j)) || (st[j][k] & (1 << j)) || (j && (st[j][k] & (1 << j - 1)))) continue;
				
				int x = id[1][st[j][k] | (1 << j)];
				if (id[0][st[j][k] | (1 << j)]) x += st[0][0];
				f[Now][x] += tmp;
				f[Now][x] -= f[Now][x] > mod? mod: 0;
			}
		}
	}
	int ans = 0;
	for (int k = 1; k <= st[0][0]; k++)
	{
		ans = ans + f[Now][k];
		ans -= ans > mod ? mod: 0;
	}
	printf ("%d", ans);
	return 0;
}
```

---

## 作者：superMB (赞：22)

我感觉前面的题解有些讲的不是很清楚qwq，所以我发一篇。

很明显，这是一个状压dp，下面我说下思路

1、先预处理第i行的草地状态init[i]，压缩为一个整数。

2、再预处理第i行不相邻的状态legal[i]，每行共有(1<<m)-1种状态，但是很多是存在相邻的情况，所以提前处理不合法的状态可以在状态转移中降低很多时间复杂度。

那么怎么判断某一状态是否相邻呢？只需要(i&(i<<1)==0)&&(i&(i>>1)==0)就可以判断,如果存在相邻情况则将legal[i]置为false，不存在相邻则为true。

3、怎么处理只能放到肥沃的草地呢？对于第i行的地形init[i]和某一状态j，如果枚举到的init[i]&j==j即说明了两个状态完全相同，没有放到贫瘠草地的情况。

4、对于第i行不和i-1行有连通草地，枚举上一行方案k，该行方案j&k==0即可满足条件。

```cpp
#include<cstdio>
#include<bitset>
#define ri register int
using namespace std;
const int mod=100000000; 
template<typename TP>inline void read(TP&x)
{
    x=0;int f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    x*=f;
}
template<typename TP>inline void print(TP x)
{
    if(x<0)x=-x,putchar('-');
    if(x>=10)print(x/10);
    putchar(x%10+'0');
}
int dp[13][1<<12];//该dp的状态 dp[i][j]为在前i行,此行是方案j时的方案总数 
bitset<1<<12>legal;//初始化一行每种可能放牛方案的合法性(数组下标的二进制代表状态,其中存储的true或者false表示该方案是否可行)
int init[13];//每行的初始草坪状态(数组内存储的整数的二进制代表状态)
int n,m,temp,maxn,sum;
int main()
{
	read(n),read(m);
	for(ri i=1;i<=n;++i)
		for(ri j=1;j<=m;++j)
			read(temp),init[i]=(init[i]<<1)+temp;//将每行有无草坪的初始状态压缩成一个整数 
	maxn=(1<<m)-1;//最大状态,即全部草坪都放牛时的状态 
	for(ri i=0;i<=maxn;++i)
		if(!(i&i<<1)&&!(i&i>>1))//如果枚举到的此种方案任意相邻两格之间没有同时放牛,则这种方案是合法的 
			legal[i]=1;
	dp[0][0]=1;//初始化dp数组
	for(ri i=1;i<=n;++i)//循环每一行
		for(ri j=0;j<=maxn;++j)//枚举该行的方案
			if(legal[j]&&(j&init[i])==j)//该种方案合法并且每头牛所在位置与此行草坪上有草的位置相同则该方案可行 
				for(ri k=0;k<=maxn;++k)//枚举上一行方案
					if(!(k&j))//如果该种方案与上一行方案k不存在公共边,则可以在该方案累加上一行方案k的方案总数，此时不需要考虑上一行方案的合法性,因为上一种方案不合法则本身方案数就为0 
						dp[i][j]=(dp[i][j]+dp[i-1][k])%mod;
	for(ri i=0;i<=maxn;++i)
		sum=(sum+dp[n][i])%mod;//将前n行的方案总数累加
	print(sum);
}
```

---

## 作者：Lacer (赞：10)

（非新手向，只是看到似乎没人用记搜，代码也比较长才发的这个）

像这样的状压dp题能用公式填表当然也能用记搜啦~本蒟蒻~~不会递推所以~~比较喜欢记搜

直接上代码吧，很短的，注释打上去了，有疑问欢迎骚扰~~

```cpp
//以下的状态i（或者类似表达）的意思是，将i转化为二进制数后，在1的位置种东西，0的位置不种东西。eg.状态为5（二进制表示为101）表示只有倒数第1,3个位置种草的状态，
#include<cstdio>
#include<cstring>
#define N 12
#define MOD 100000000
int a[N+1];//把每一行肥沃程度压缩成二进制数存储
long long ans[N+2][1<<N];//f[i][j]表示第i行状态为j时其下面几行的总方案数
int n,m;
int dfs(int cur,int p)//正在处理第cur行，上一行状态为p 
{
	if(ans[cur][p])return ans[cur][p];//记忆化搜索核心，搜过的就不搜了，掉了这句会严重超时
	if(cur==n+1)return 1;//已经搜完了一遍，找到了一种方案
	bool book[1<<N];//标记本次搜索中哪些状态已经搜过，由于后期枚举第cur行的合法状态的时候要把不肥沃的地方置零，因此我们在枚举1~1<<n的时候很有可能枚举到一个已经算过的状态，结果会因为重复计算而偏大。具体解释见下方注释。
	memset(book,0,sizeof(book));//初始化
	for(int i=0;i<1<<m;i++)
	{
		if(i&(i<<1)||i&p)continue;//i&(i<<1)==true则表示当前枚举到的状态中有相邻的草，不合法。i&p表示与上面一行的某一块草地相邻，也不合法。两种情况都跳过。
		int t=i&a[cur];//这就是上文提到的把能种草的地方过滤出来，细细一想book的作用就体现出来了。比如当i=2或7时，表示状态分别为10和111，倒数第二位都种上了，当这一行的肥沃程度为010时，i=2与i=7两次都搜到了010，重复计算结果偏大。
		if(book[t])continue;//已经搜过的就跳过
        //此时搜到的状态t就是合法的
		ans[cur][p]+=dfs(cur+1,t);ans[cur][p]%=MOD;//累加方案数并取模，因此函数返回值不必用long long 
		book[t]=true;//标记已经搜过
	}
	return ans[cur][p];
}
int main()
{
	int i,j,t;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			{scanf("%d",&t);a[i]<<=1;a[i]|=t;}//二进制存图
	printf("%d",dfs(1,0));//上一层状态为0，第一层的搜索不受影响，dfs(1,0)计算出来的自然就是总方案数了
    return 0;
}
```
30ms，还行QWQ

---

## 作者：huihao (赞：10)

没人来个搜索，我来插个空。(这个对初学者理解起来要容易)


其实就是两种选择,放和不放.


```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<cstdio>
using namespace std;
const int maxn=(1<<16);
int m,n;
int ans=0;
int mod=100000000;
int f[30][maxn],a[30];
void dfs(int i,int j,int state,int nex)//state表示当前行状态，
{//nex表示下一行状态
    if(j>=n)
    {
        f[i+1][nex]+=f[i][state];
        f[i+1][nex]%=mod;//这个要取余,防止中间过程溢出.
        return;
    }
    dfs(i,j+1,state,nex);//这一个点不放
    if(!((1<<j)&state)) dfs(i,j+2,state,nex|(1<<j));//这一个点如果能放就放
    return;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
    for(int j=0;j<n;j++)
    {
        int x;
        scanf("%d",&x);
        if(x==0)
        a[i]=a[i]|(1<<j);
    }
    f[1][a[1]]=1;//当第一行什么也不放时只有一种方法
    for(int i=1;i<=m;i++)
    for(int j=a[i];j<(1<<n);j++)//这儿从a[i]开始就行了
```
{//因为放0个就是a[i],没有比它更少了.
```cpp
        if(f[i][j])
        dfs(i,0,j,a[i+1]);
    }
    for(int i=0;i<(1<<n);i++)
    {if(f[m+1][i]){ans+=f[m+1][i];ans%=mod;}}//注意最后加的是m+1行.
    printf("%d",ans);
    return 0;
}
```

---

## 作者：George1123 (赞：9)

[${\color{orange}\text{欢迎拜访我这个蒟蒻的博客}}$](https://www.luogu.org/blog/wzc-wwwwd/)

[P1879 【\[USACO06NOV\]玉米田Corn Fields】传送门](https://www.luogu.org/problem/P1879)

### 此题算法:状压dp

是水题，当被整了一天的我真的不能这么说

大致做法:

>1.$dp[i][j]$中$j$是一个二进制数，$i$表示算到前$i$行，$j$表示第$i$行的状态($0$表示空，$1$表示玉米)$dp[i][j]$的值为当前状态下的种法种数。

>2.$full$表示满玉米状态，$sp[i]$的值是一个二进制数，表示肥沃土地的状态。由于题目有玉米不相邻的要求，所以构建$C$布尔数组，$C[i]=ture$表示$i$这种情况符合无玉米相邻。别忘了位运算的优先级低于比较符，计算机会先算$i==0$再算$(i<<1)\& 1$。

>3.$ $枚举每行$i$，每个状态$j$。如果当前状态土地可以种植，即$(sp[i]\& j)==j$(意思就是$j$中的$1$被$sp[i]$中的$1$所包含)，并且$C[i]$就再枚举上一行的每个状态~~对这就是不会超时~~并加上其中与$j$互不覆盖的状态的值。

>4.$ $统计最后一行所有状态的值的和$ans$，这就是答案。别忘了种类值相加时$\%$一$\% 10^8$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=13,M=1e8;
int n,m,sp[N],full;
int dp[N][1<<N],ans;
bool a,C[1<<N];
int main(){
	scanf("%d%d",&n,&m);
	sp[0]=full=(1<<m)-1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a);
			if(a) sp[i]|=(1<<(j-1));			
		}
	} for(int i=0;i<=full;i++)
		C[i]=(((i<<1)&i)==0);
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=full;j++)
			if((sp[i]&j)==j&&C[j])
				for(int k=0;k<=full;k++)
					if((k&j)==0)
						dp[i][j]=(dp[i][
						j]+dp[i-1][k])%M;
	for(int i=0;i<=full;i++)
		ans=(ans+dp[n][i])%M;
	printf("%d\n",ans);
	return 0;
}
```
不懂运算优先级真会害死人！

谢谢大家! !


---

## 作者：laeva (赞：8)

推广一下**轮廓线DP**

考虑现在正在决定下图中$x(2,2)$点的取舍，假设现在所有格子全部无障碍

|- |   0   |   1   |   2   |   3   |
|:-| :---: | :---: | :---: | :---: |
|1 |   ?   |   ?   | $k_3$ | $k_4$ |
|2 | $k_1$ | $k_2$ |  $x$  |   0   |

我们假设让$x$后面全不放东西（为0）

也就是说$x$取不取只受到$k2$ $k3$的限制

那么我们可以考虑用二进制数$k=k_1k_2k_3k_4$
来表示当前轮廓线为$k$，
其中二进制数$k$中在$x$点及其后面的位置表示上一层的状态，$x$位置前面的数表示当前层的状态

这样的话，我们可以通过位运算获得$x$点上面和左面的状态然后对结果进行转移

转移方程为：


	f[i][k] += f[i - 1][k];//不取点(i,j)
	f[i][k ^ (1<<j)] += f[i - 1][k];//取点(i,j)
    
这样就OK了

**等等，好像有什么不对**

在上个图中，当我们选择取点$x$的时候，转移到的状态为
$k_1k_21k_4$，
但我们想转移到的状态是
$k_1k_210$

**那怎么办呢？**

事实上这并不影响我们统计答案，即$f[i][k_1k_2k_3k_4]$表示的是状态：$k_1k_2k_3k_4$，$k_1k_2k_30$中的一部分，$k_1000$中的一部分，$0000$中的一部分加在一起的总和

这样我们再处理一下有障碍的情况即一些小细节就可以A掉这题了

时间复杂度$O(nm2^m)$最慢的点用了$0s$

~~（借鉴了楼下的楼下的做法，但是他太强啦以至于解释好少，我只好就在这里把做题时我的思考写下来，写一篇让和我一样的蒟蒻也能看懂的题解咯）~~

##  code
```cpp
//#include <iostream>
#include <cstdio>
#include <cstring>

#define MAXN 15
#define mod 100000000
#define INF 0x7fffffff
#define ll long long
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define foi(i, a, b) for (int i = a; i >= b; i--)

int abs(int x) { return x > 0 ? x : -x; }
int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

int read() {
	int ans = 0; char ch = getchar(), t = ch;
	while (ch < '0' || ch > '9') { t = ch; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { ans = ans * 10 + ch - '0'; ch = getchar(); }
	if (t == '-') ans = -ans; return ans;
}

using namespace std;

int a[MAXN][MAXN], f[2][(1 << MAXN)];
//因为dp时当前这层只与上一层有关，可以使用滚动数组优化

int main() {
/*	freopen(".in", "w", stdin);
	freopen(".out", "r", stdout);*/
	int n = read(), m = read(), nown = 0;
	rep(i, 1, n) rep(j, 0, m - 1) a[i][j] = read();
	f[0][0] = 1;
	rep(i, 1, n) rep(j, 0, m - 1) {//枚举(i,j)点放不放
		nown ^= 1; memset(f[nown], 0, sizeof(f[nown]));
		rep(k, 0, (1 << m) - 1) {//枚举轮廓线
			int up = (1 << j) & k, left = (j > 0 ? (1 << (j - 1)) & k : 0);
			//找到左面、上面有没有东西
			if ((i == 1 && up) || (!j && left)) continue;
			//不可能出现的情况
			if (up) {//当前位置不能选
				f[nown][k ^ (1<<j)] = (1ll * f[nown][k ^ (1<<j)] + f[nown^1][k]) % mod;
				continue;
			}//注意这里因为轮廓线k在j这个位置为1，要改成0
			if (left || !a[i][j]) {//当前位置不能选
				f[nown][k] = (1ll *  f[nown][k] + f[nown ^ 1][k]) % mod;
				continue;
			}
			//以下为可选可不选
			f[nown][k] = (1ll * f[nown][k] + f[nown ^ 1][k]) % mod;//不选
			f[nown][k ^ (1<<j)] = (1ll * f[nown][k ^ (1<<j)] + f[nown^1][k]) % mod;//选
		}
	}
	int ans = 0;
	rep(i, 0, (1 << m) - 1) ans = (1ll * ans + f[nown][i]) % mod;
	printf("%d", ans);
	return 0;
}
```

顺便吐槽下luogu数据太弱了：
```cpp
f[nown][k ^ (1<<j)] = (1ll * f[nown][k ^ (1<<j)] + f[nown^1][k]) % mod;//选
```
写成
```cpp
f[nown][k ^ (1<<j)] += (1ll * f[nown][k ^ (1<<j)] + f[nown^1][k]) % mod;//选
```
居然AC了？？

---

## 作者：ywy_c_asm (赞：6)

这题虽然是一道状压入门好题，但是居然没人用$FWT$做真是可惜……

首先状态转移方程为$dp[i][S]=\sum_{T\&S=0}dp[i-1][T]$，其中$S$为合法状态，这个就是细节了。

然后我们发现这个东西跟$FWT$的形式非常相似，都是下标进行位运算然后累加，然后我们把这个式子变一下形：

$\sum_{T\&S=0}dp[i-1][T]=\sum_{T|(\sim S)=\sim S}dp[i-1][T]$

解释一下，因为$S$与$T$没有交集，也就是说$T$是$S$的补集的子集，即$T|(\sim S)=\sim S$，那么就转化为了$\sum_{j|i=i}A_j$的形式，这不裸的$FWT$？直接用$or$卷积的$FWT$在$O(m2^m)$的时间内处理$dp[i-1]$数组，然后就能$O(1)$转移了。

然后时间复杂度$O(nm2^m)$比大部分人的暴力$dp$优越~~

上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define p 100000000
using namespace std;
namespace ywy{
	inline void fwt(int n,ll *f){//FWT板子 
		for(register int bit=2;bit<=n;bit<<=1){
			for(register int i=0;i<n;i+=bit){
				for(register int j=i;j<i+(bit>>1);j++){
					f[j+(bit>>1)]=(f[j]+f[j+(bit>>1)])%p;
				}
			}
		}
	}
	ll dp[13][4097];//dp
	int s[13];//这行不能放的位置集合（判断状态合法性） 
	unsigned char bv[4097];//这个状态里是否有相邻的1 （判断状态合法性） 
	void ywymain(){
		int n,m;cin>>n>>m;for(register int i=0;i<(1<<m);i++){
			int lst=-1234;int tmp=i;while(tmp){//判断状态是否有相邻的1，不断取lowbit判断 
				int lb=tmp&(-tmp);if(lb==(lst<<1)){
					bv[i]=1;break;
				}tmp-=lb;lst=lb;
			}
		}
		for(register int i=1;i<=n;i++){
			for(register int j=0;j<m;j++){
				int a;cin>>a;if(!a)s[i]|=(1<<j);//读入每行状态 
			}
		}
		for(register int i=0;i<(1<<m);i++){
			if(bv[i])continue;if(i&s[1])continue;dp[1][i]=1;//预处理第一行 
		}
		for(register int i=2;i<=n;i++){
			fwt(1<<m,dp[i-1]);//对上一行的dp数组做一个fwt 
			for(register int j=0;j<(1<<m);j++){
				if(j&s[i])continue;if(bv[j])continue;
				dp[i][j]=dp[i-1][((1<<m)-1)^j];//注意取补集 
			}
		}
		ll ans=0;for(register int i=0;i<(1<<m);i++)ans=(ans+dp[n][i])%p;cout<<ans<<endl;//统计答案 
	}
}
int main(){
	ywy::ywymain();return(0);
}
```

---

## 作者：jins3599 (赞：3)

其实是`P1896 [SCOI2005]互不侵犯`的弱化版。

我们设计方程`f[i][j]`代表，选择前$i$行，状态为$j$时的方案总数。

这种求方案数的题目都是这样的套路，设计方程的时候也要向这种方程形式靠拢。

我们考虑这个方程如何转移。

我们设两个状态$h,g$，并且保障$h,g$不冲突且合法。

于是`f[i][h] += {f[i - 1][g]}.`

那么最后的问题就是如何判断$h,g$是否冲突。

显然的结论，当$h\&j=0$时，一定不会冲突，因为他们按位之间没有相同的$1.$

这样的话我们只需要预处理出来每一行摆放的所有情况，然后再根据每一行的草坪情况进行决策，最后留下合法的情况进行转移即可。

时间复杂度$O(n*m*4^{n})$看样子好像跑不过，其实这个$4^n$根本跑不到一半，我们在预处理状态的时候会舍去很多的不合法的状态，因此速度还是蛮快的。

$Code$:

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 15;
int g[N][N];
int n , m , ans;
const int mod = 100000000;

int cow[(1 << N)] , cnt;

void dfs(int now ,int tot) {
	if(tot >= m) {
		cow[++ cnt] = now; return;
	}
	dfs(now , tot + 1);
	dfs(now | (1 << tot) , tot + 2);
}

int f[N][(1 << N)];

int main () {
	scanf("%d %d" , &n , &m);
	for(int i = 1 ; i <= n; ++ i)
		for(int j = 1 ; j <= m ; ++ j) scanf("%d" , &g[i][j]);
	dfs(0 , 0);
	for(int i = 1 ; i <= cnt ; ++ i) {
		f[1][cow[i]] = 1;
		for(int p = 1 ; p <= m ; ++ p) 
			if(g[1][p] == 0 && (cow[i] & (1 << (p - 1)))) f[1][cow[i]] = 0;
	}
	for(int i = 2 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= cnt ; ++ j){
			for(int k = 1 ; k <= cnt ; ++ k) {
				if((cow[j] & cow[k])) continue;
				bool flag = 0;
				for(int p = 1 ; p <= m ; ++ p) 
					if(g[i][p] == 0 && (cow[j] & (1 << (p - 1)))) {flag = 1; break;}
				if(flag) continue;
				//printf("%d from %d\n" , cow[j] , cow[k]);
				f[i][cow[j]] += f[i - 1][cow[k]];
				f[i][cow[j]] %= mod;
			}
		}		
	}
	//for(int i = 1 ; i <= cnt ; ++ i) printf("%d %d\n" , cow[i],f[n][cow[i]]);
	for(int i = 1 ; i <= cnt ; ++ i) ans = (ans + f[n][cow[i]]) % mod;
	printf("%d\n" , ans % mod);
	return 0;
}
```

---

## 作者：shadowice1984 (赞：3)

来一波0s做法。

显然这是状态压缩dp

定义也是非常的好想，

定义d[i][j]表示决策到了第i行，j记录上一个行的表示情况

那么显然有d[i][j]=sigma(d[i-1][j ban p])(p属于j)

当然实际上采用存在性dp的形式转移。

那么有一个很有趣的问题，如何确定一个横行是合法的？

打表啊~~~~

下面是数据生成器代码

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int res[100000];int cnt;
void dfs(int x,int step)//简单的dfs没啥好说
{
    if(step==13)
    {
        res[cnt++]=(x>>1);
        return;
    }
    if(((1<<step)&x)==0)
    {
        dfs((x|1<<(step+1)),step+1);
        dfs(x,step+1);
    }
    else 
    {
        dfs(x,step+1);
    }
    return;
}
int main()
{
    dfs(0,0);
    printf("cnt=%d",cnt);
    sort(res,res+cnt);
    for(int i=0;i<cnt;i++)
    {
        if(i%16==0)printf("\n");
        printf("%-5d,",res[i]);
    }
    return 0;
}
```
然后我们就可以愉快的dp了~
这个剪枝剪得非常狠，所以超级快~

上代码~

```cpp
#include<stdio.h>
#include<math.h>
using namespace std;
int dp[20][30000];
int n;int m;int c[20];
int res;bool map[20][20];
int up;
int s[600]={
```
0    ,1    ,2    ,4    ,5    ,8    ,9    ,10   ,16   ,17   ,18   ,20   ,21   ,32   ,33   ,34   ,
36   ,37   ,40   ,41   ,42   ,64   ,65   ,66   ,68   ,69   ,72   ,73   ,74   ,80   ,81   ,82   ,

84   ,85   ,128  ,129  ,130  ,132  ,133  ,136  ,137  ,138  ,144  ,145  ,146  ,148  ,149  ,160  ,

161  ,162  ,164  ,165  ,168  ,169  ,170  ,256  ,257  ,258  ,260  ,261  ,264  ,265  ,266  ,272  ,

273  ,274  ,276  ,277  ,288  ,289  ,290  ,292  ,293  ,296  ,297  ,298  ,320  ,321  ,322  ,324  ,

325  ,328  ,329  ,330  ,336  ,337  ,338  ,340  ,341  ,512  ,513  ,514  ,516  ,517  ,520  ,521  ,

522  ,528  ,529  ,530  ,532  ,533  ,544  ,545  ,546  ,548  ,549  ,552  ,553  ,554  ,576  ,577  ,

578  ,580  ,581  ,584  ,585  ,586  ,592  ,593  ,594  ,596  ,597  ,640  ,641  ,642  ,644  ,645  ,

648  ,649  ,650  ,656  ,657  ,658  ,660  ,661  ,672  ,673  ,674  ,676  ,677  ,680  ,681  ,682  ,

1024 ,1025 ,1026 ,1028 ,1029 ,1032 ,1033 ,1034 ,1040 ,1041 ,1042 ,1044 ,1045 ,1056 ,1057 ,1058 ,

1060 ,1061 ,1064 ,1065 ,1066 ,1088 ,1089 ,1090 ,1092 ,1093 ,1096 ,1097 ,1098 ,1104 ,1105 ,1106 ,

1108 ,1109 ,1152 ,1153 ,1154 ,1156 ,1157 ,1160 ,1161 ,1162 ,1168 ,1169 ,1170 ,1172 ,1173 ,1184 ,

1185 ,1186 ,1188 ,1189 ,1192 ,1193 ,1194 ,1280 ,1281 ,1282 ,1284 ,1285 ,1288 ,1289 ,1290 ,1296 ,

1297 ,1298 ,1300 ,1301 ,1312 ,1313 ,1314 ,1316 ,1317 ,1320 ,1321 ,1322 ,1344 ,1345 ,1346 ,1348 ,

1349 ,1352 ,1353 ,1354 ,1360 ,1361 ,1362 ,1364 ,1365 ,2048 ,2049 ,2050 ,2052 ,2053 ,2056 ,2057 ,

2058 ,2064 ,2065 ,2066 ,2068 ,2069 ,2080 ,2081 ,2082 ,2084 ,2085 ,2088 ,2089 ,2090 ,2112 ,2113 ,

2114 ,2116 ,2117 ,2120 ,2121 ,2122 ,2128 ,2129 ,2130 ,2132 ,2133 ,2176 ,2177 ,2178 ,2180 ,2181 ,

2184 ,2185 ,2186 ,2192 ,2193 ,2194 ,2196 ,2197 ,2208 ,2209 ,2210 ,2212 ,2213 ,2216 ,2217 ,2218 ,

2304 ,2305 ,2306 ,2308 ,2309 ,2312 ,2313 ,2314 ,2320 ,2321 ,2322 ,2324 ,2325 ,2336 ,2337 ,2338 ,

2340 ,2341 ,2344 ,2345 ,2346 ,2368 ,2369 ,2370 ,2372 ,2373 ,2376 ,2377 ,2378 ,2384 ,2385 ,2386 ,

2388 ,2389 ,2560 ,2561 ,2562 ,2564 ,2565 ,2568 ,2569 ,2570 ,2576 ,2577 ,2578 ,2580 ,2581 ,2592 ,

2593 ,2594 ,2596 ,2597 ,2600 ,2601 ,2602 ,2624 ,2625 ,2626 ,2628 ,2629 ,2632 ,2633 ,2634 ,2640 ,

2641 ,2642 ,2644 ,2645 ,2688 ,2689 ,2690 ,2692 ,2693 ,2696 ,2697 ,2698 ,2704 ,2705 ,2706 ,2708 ,

2709 ,2720 ,2721 ,2722 ,2724 ,2725 ,2728 ,2729 ,2730 ,4100 ,4101 ,4104 ,4105 ,4106 ,4112 ,

4113 ,4114 ,4116 ,4117 ,4128 ,4129 ,4130 ,4132 ,4133 ,4136 ,4137 ,4138 ,4160 ,4161 ,

4162 ,4164 ,4165 ,4168 ,4169 ,4170 ,4176 ,4177 ,4178 ,4180 ,4181 ,4224 ,4225 ,4226 ,4228 ,4229 ,

4232 ,4233 ,4234 ,4240 ,4241 ,4242 ,4244 ,4245 ,4256 ,4257 ,4258 ,4260 ,4261 ,4264 ,4265 ,4266 ,

4352 ,4353 ,4354 ,4356 ,4357 ,4360 ,4361 ,4362 ,4368 ,4369 ,4370 ,4372 ,4373 ,4384 ,4385 ,4386 ,

4388 ,4389 ,4392 ,4393 ,4394 ,4416 ,4417 ,4418 ,4420 ,4421 ,4424 ,4425 ,4426 ,4432 ,4433 ,4434 ,

4436 ,4437 ,4608 ,4609 ,4610 ,4612 ,4613 ,4616 ,4617 ,4618 ,4624 ,4625 ,4626 ,4628 ,4629 ,4640 ,

4641 ,4642 ,4644 ,4645 ,4648 ,4649 ,4650 ,4672 ,4673 ,4674 ,4676 ,4677 ,4680 ,4681 ,4682 ,4688 ,

4689 ,4690 ,4692 ,4693 ,4736 ,4737 ,4738 ,4740 ,4741 ,4744 ,4745 ,4746 ,4752 ,4753 ,4754 ,4756 ,

4757 ,4768 ,4769 ,4770 ,4772 ,4773 ,4776 ,4777 ,4778 ,4096 };//丧心病狂的数据表

            
```cpp
int main()
{
        //状压dp都是一样的，这个是模板
    scanf("%d%d",&n,&m);
    up=pow(2,m+1)-1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&map[i][j]);
            if(map[i][j])
            {
                c[i]+=1<<j;
                //printf("c[%d]=%d\n",i,c[i]);
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=up;j++)
        {
            dp[i][j]=-1;
        }
    }
    dp[0][0]=1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;s[j]<=up;j++)
        {
            if(dp[i][s[j]]!=-1)
            {
                //printf("dp[%d][%d]=%d\n",i,s[j],dp[i][s[j]]);
                for(int k=0;s[k]<=up;k++)
                {
                    if((s[k]&s[j])==0&&(s[k]|c[i+1])==c[i+1])
                    {
                        if(dp[i+1][s[k]]==-1)dp[i+1][s[k]]=0;
                        dp[i+1][s[k]]+=dp[i][s[j]];dp[i+1][s[k]]%=1000000000;
                        //printf("->dp[%d][%d]=%d\n",i+1,s[k],dp[i+1][s[k]]);
                    }
                }
            }
        }
    }
    for(int j=0;s[j]<=up;j++)
    {
        if(dp[n][s[j]]!=-1)
        {
            res+=dp[n][s[j]];
            res%=1000000000;
        }
    }
    printf("%d",res);
    return 0;
}
```

---

## 作者：scallop (赞：3)

其实这道题可以套用插头DP的模板。（虽然有点大材小用）

我们考虑定义状态 $f(i,j,k)$ 表示当前正在安排第i行第j列，其中k是一个二进制数，它表示

$(i,1)\to(i,j-1)$ $(i-1)(j)\to(i-1,m)$

这几个格子有没有被种上草。

如果$(i-1,j) or(i,j-1)$ 有草，我们就只能转移到不种草，否则可种可不种。

这样的话时间复杂度是 $O(n^22^n)$ 的。

我的代码写复杂了。


```cpp
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

const int MOD = 100000000;
int n, m;
long long ans;
int ch[20], c[20][20];
long long f[15][15][1 << 14];

void inc(long long &a, long long b)
{
    a = (a % MOD + b % MOD) % MOD;
}

long long encode()
{
    long long ret = 0;
    for (int i = m; i > -1; --i)
    {
        ret <<= 1;
        ret |= ch[i];
    }
    return ret;
}

void decode(long long v)
{
    for (int i = 0; i < m + 1; ++i)
    {
        ch[i] = v & 1;
        v >>= 1;
    }
}

void dpblank(int x, int y)
{
    int op = 0;
    for (int i = 0; i < (1 << (m + 1)); ++i)
    {
        if (f[x][y][i] > 0)
        {
            decode(i);    
            int u = ch[y - 1], v = ch[m];
            ch[m] = 0;
            ch[y - 1] = 0;
            if (y != m)
                inc(f[x][y + 1][encode()], f[x][y][i]);
            else
                inc(f[x + 1][1][encode()], f[x][y][i]);
            if (u == 0 && v == 0)
            {
                ch[m] = 1;
                ch[y - 1] = 1;
                if (y != m)
                    inc(f[x][y + 1][encode()], f[x][y][i]);
                else
                {
                    ch[m] = 0;
                    inc(f[x + 1][1][encode()], f[x][y][i]);
                }
            }
        }
    }
}

void dpblock(int x, int y)
{
    for (int i = 0; i < (1 << (m + 1)); ++i)
    {
        if (f[x][y][i] > 0)
        {
            decode(i);
            ch[y - 1] = 0;
            ch[m] = 0;
            if (y != m)
                inc(f[x][y + 1][encode()], f[x][y][i]);
            else
                inc(f[x + 1][1][encode()], f[x][y][i]);
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < m + 1; ++j)
            cin >> c[i][j];
    }
    f[1][1][0] = 1;
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < m + 1; ++j)
        {
            if (c[i][j] == 1)
                dpblank(i, j);
            else
                dpblock(i, j);
        }
    }
    for (int i = 0; i < (1 << m); ++i)
        inc(ans, f[n + 1][1][i]);
    printf("%lld\n", ans);
}
```

---

## 作者：WSJwsj (赞：2)

这是个裸状压题，真的很水。。。
 
题目大致意思是说有一块地，每一格都是一块正方形的土 地（什么鬼），有许多奶牛（我也不知道有多少 QAQ ,反正 有很多很多奶牛，一定比地多）。
 
有些地不能用，相当于不能放牛。并且，奶牛们喜欢独占一 块地的感觉（地主），所以两头奶牛不能相邻。
 
在不相邻的情况下，有许多可行方案，当然也可以选择不 放奶牛。问有多少种可行方案。


**从问题与结果出发**

可以很轻松地知道，我们要求的是在第M行、最后一个状 态时，前M行所有可行方案之和。
 
分解成每一个阶段，我们要求的就是第 i 行、第 j 个状态 时，前 i 行所有可行方案之和。
 
于是我们定义一个 f 数组，由于 f[i][j]肯定是从第i-1行转移过来的，所以我们必须在第0行,第1个状态时就要赋好初始值。
 
f[0][0]= 1; / / 第一个状态从下标0开始

**如何找到可行状态？**

我们第一眼看到这题的思路应该是暴力搜索，去以实际 的空间去一步一步搜索回溯。这个思路也是对的。 其实动规与暴搜的思路差不多。只需要判断与左右和上 一行是否冲突。 我们在判断这个状态是否成立的时候，状态被二进制压 缩了，所以位置本身是否可行，就也要用二进制表示。于 是定义一个 map 数组用二进制存储。 用来判断的时候只需要取反即可。 

```cpp
for(int i=1;i<=m;i++)
	for(int j=1;j<=n;j++){
    x=read();
    map[i]=(map[i]<<1)+x; 
 }
```

上代????:

```cpp
//luogu 1879
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,x,mod=1e8;
int mapp[20],f[20][4100];
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
signed main(){
    m=read();n=read();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            x=read();mapp[i]=(mapp[i]<<1)+x;
        }
    }
    f[0][0]=1;
    for(int i=1;i<=m;i++) {
        for(int j=0;j<=(1<<n)-1;j++){
            if(!(j&(j<<1))&&!(j&(j>>1))&&!(j&(~mapp[i]))){
                for(int k=0;k<=(1<<n)-1;k++){
                   if(!(k&(k<<1))&&!(k&(k>>1))&&!(k&(~mapp[i-1]))&&!(j&k)) f[i][j]+=f[i-1][k];
                }
            }
        }
    }
    for(int i=0;i<=(1<<n)-1;i++) ans+=f[m][i];
    printf("%d",ans%mod);
    return 0;
}

```



---

## 作者：冒泡ioa (赞：2)

[欢迎来我博客玩~](https://bubbleioa.github.io/2018/09/20/[%E6%B4%9B%E8%B0%B7P1879][USACO06NOV]%E7%8E%89%E7%B1%B3%E7%94%B0Corn%20Fields/#more)
## 题解
一道状态压缩入门题，也是第一道我在不看任何题解的情况下写出来的状压dp题  
状压dp一般会有明显的数据范围特征，即n,m一般都在20以内  

状压dp的状态设计和转移是有套路的，就拿这道题来说，$f[i][j]$表示第$i$行在状态$j$的时候的方案数，其中$j$我们用一个二进制数来表示。  
转移的时候只要判断与当前行和上一行是否冲突即可，如果不冲突，$f[i][j]=\sum f[i-1][z]$其中z为不冲突的状态


$\sum_{1\le i\le cnt} f[n][i]$ 就是最后的答案（$cnt$为状态总数）

至于为什么在下面的代码里先枚举本层，在枚举上一层：  
因为我们动态规划是靠状态转移来实现的，上一行相当于处在i-1阶段，我们需要不断用上一个阶段来更新下一个阶段（逆推），因此本层循环在外侧。

## 代码
```c++
#include<iostream>
#include<cstdio>
using namespace std;
const int mod=100000000;
int f[13][5000];
int ok[13];//纪录每一行输入的数据，也是用二进制保存
int n,m;
int can[5000],cnt;//预处理出所有合法状态

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int a;
            cin>>a;
            ok[i]<<=1;//这里的顺序一定要注意
            ok[i]|=a;
        }
    }
    int MAXN=(1<<m)-1;//假设m为5最大的状态显然为1 1 1 1 1
    for(int i=0;i<=MAXN;i++)if((i&(i<<1))==0)can[++cnt]=i;//自己如果和自己左移重叠了，说明有相邻的，不合法，只有不重叠才合法，注意从0开始
    for(int i=1;i<=cnt;i++){
        if(can[i]&(~ok[1]))continue;//第一行单独处理，~按位取反
        f[1][i]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=cnt;j++){//枚举当前行
            int x=can[j];
            for(int z=1;z<=cnt;z++){//枚举上一行
                int y=can[z];
                if(x&y||x&(~ok[i])||y&(~ok[i-1]))continue;
                f[i][j]=(f[i][j]+f[i-1][z])%mod;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=cnt;i++)ans=(ans+f[n][i])%mod;
    cout<<ans;
    return 0;
}
```

---

## 作者：littleseven (赞：1)


## 题解：

**状压DP**

>  还是那句话，为什么是状压DP？？？
>
> ​					——  因为数据范围很状压

那么对于这道题的DP过程，DP属性如下：

- 状态：$f[i][j]$表示前$i$行的压缩状态为$j$时候的方案数，$F[i]$表示第$i$行的状态。
- 初值：$f[0][0] = 1$，第0行没有草坪，方案数为$1$。
- 转移方程：`f[i][j] = (f[i][j] + f[i - 1][k]) % mod;`

状态怎么初始化？？？

- 这道题中的合法条件要求不能有两头牛的草地相邻，那么对于当前位置$i$我们进行以下判断
  1. `i & (i >> 1) == 0`表示它不与右边的草地相邻。
  2. `i & (i << 1) == 0`表示它不与左边的草地相邻。
- 如果符合上述两个条件，证明该位置是合法的，对标记数组标记$g[i]= 1$。

最终我们只需要循环统计答案输出即可。

## AC代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 15;

const int M = (1 << 12) + 10;

const int mod = 1e8;

bool g[M];

int n, m, F[N], mp[N][N], f[N][M];

int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i ++ )
	{
		for (int j = 1; j <= n; j ++ )
		{
			scanf("%d", &mp[i][j]);
			F[i] = (F[i] << 1) + mp[i][j];
		}
	}
	for (int i = 0; i < (1 << n); i ++ )
	{
		if ((!(i & (i << 1))) && (!(i & (i >> 1))))
		{
			g[i] = 1;
		}
	}
	f[0][0] = 1;
	for (int i = 1; i <= m; i ++ )
	{
		for (int j = 0; j < (1 << n); j ++ )
		{
			if (g[j] && (j & F[i]) == j)
			{
				for (int k = 0; k < (1 << n); k ++ )
				{
					if ((k & j) == 0)
					{
						f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < (1 << n); i ++ )
	{
		ans = (ans + f[m][i]) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：kikuss (赞：1)

解题思路:按照刚才我说的,题目中的m,n最大都只有12,我们要很快想到状压dp,那么如何状压呢?其实状压dp就是一种枚举,是最暴力的一种dp.

在题目中,有1的地方就可以种植,否则不行,在不考虑时间复杂度的情况下,我们是不是会想到打暴搜,枚举每一种情况,如果一块地上已经种了草,那么上下左右就都不能种了.我们经这种思路转化成二进制,1代表在这块地上种植,0代表不种,例如:010就代表在第二块地种植,其他地都不种.

我们枚举每一行的状态,在左右不相邻的情况下,再判断下一行不和本行状态冲突的状态(如:第一行是0 1 0,第二行是0 1 0就冲突了,即上下行同一位置不能同时种植),这样我们只需要预处理出第一行的状态就可以递推出其他行的所有满足条件的状态个数了

下面来分析一下题目样例

1 1 1

0 1 0

第一行满足条件的状态有

1	000

2	100 　

3	010

4	001

5	101

第二行满足条件的状态有

1	000

2	010

根据乘法原理有5*2=10种方法,但其中一种第一行0 1 0和第二行0 1 0是冲突的,所以结果为10-1=9种方案

设计dp数组的状态,状压dp状态应该还是比较好设计的,本题为dp[i][state[j]]表示到第i行到第j种状态满足条件的方案数

满足无后效性原则,下一行的状态只能由前一行转移过来

dp[i+1][state[j]]+=dp[i][state[k]] state[k]表示第i行满足条件的状态

总结一下思路：先枚举第一行，把所有可能的状态和第一行的题目所给环境对比，如果成功，则在循环里继续枚举第二行，把所有可能的状态和第二行的环境对比，如果成功，再和第一行填入的状态对比，如果又匹配成功，则dp[2][000] = dp[2][000] + dp[1][100];方法数加到第二行。这就是一次循环结束了，重新枚举第二行...

欢迎大家来踩博客[real_l](https://www.cnblogs.com/real-l/p/8562834.html)
 

---

## 作者：Julytree (赞：1)

首先，需要了解**位运算**：

1.“&”与——两个都是1，结果为1，其他为0；

2.“|”或——只要一个是1，结果为1；（两个都是0为0，其他为1）；

3.“^”异或——不同为1，相同为0（常用于取反）；

4。“~”取反；-


**状态转移方程**：dp[某一行] [当前状态]=sum dp[上一行][与其不冲突的状态]；

最后答案就是sum dp[最后一行][所有可能状态]；

**关于状态存储**：开13维数组是不现实****的，而且每个位置只有两种状态，所以我们可以将每一行的状态转化为一个数字，二进制下 的0101…即不同选择方案；

详细解释见代码。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
const int Mod=100000000; 
int n,m,num,ans;
int dp[15][1<<15];//dp[第i行] [状态为j (二进制下)] =方案数 
int map[15],stat[1<<15];//map存图，stat保留左右不相邻的选择方案 
using namespace std;

void init()
{
  memset(dp,0,sizeof(dp));
  memset(map,0,sizeof(map));
  
  scanf("%d%d",&m,&n);
  for(int i=1;i<=m;i++)//m行n列
  {
      int t;
    for(int j=1;j<=n;j++)
    {
      scanf("%d",&t);
      map[i]=(map[i]<<1)+(t^1);/*将每一行存为一个数。全部取反，方便后面运算*/
    }
  }    
}

void begin()
{
  num=0;
  for(int i=0;i<(1<<n);i++)//枚举所有可能状态，判断是否相邻
    if(! (i&(i<<1)) ) stat[++num]=i;//最后存储的都是左右不冲突的状态

  for(int i=1;i<=num;i++)
    if(! (map[1]&stat[i]) )//第一行中，能放
      dp[1][stat[i]]=1;
}

void DP()
{
  for(int i=2;i<=m;i++)    //所有行
    for(int j=1;j<=num;j++)//所有可能状态
    {
      if(map[i]&stat[j]) continue;//能放
      
      for(int k=1;k<=num;k++)//上一行可能状态
      { 
        if(map[i-1]&stat[k]) continue;//也能放
         
        if(! (stat[k]&stat[j]) )//上下不相邻
          dp[i][stat[j]]=( dp[i-1][stat[k]] +dp[i][stat[j]] )%Mod;    
          
      }     
    } 
 
 ans=0;
 for(int i=1;i<=num;i++)
  ans=( ans+ dp[m][stat[i]])%Mod;
}
int main()
{
  init();
  begin();
  DP(); 
  
  printf("%d",ans);
return 0;
}
```

---

## 作者：檀黎斗·神 (赞：1)

如果用坐标性Dp，那么按照习惯我们就要定义一个

f[行数][该行第一个位置的状态][该行第二个位置的状态]……[该行第12个位置的状态]

总计13个下标的大数组，显然我们处理起来会很麻烦，这时候我们就应该要优化一下

我们可以看到m的范围其实很小，而如果有一个范围是在20以内，并且是一个Dp问题的话

我们不难想到状压Dp，状压Dp的实质就是通过二进制数对其进行优化

最好先去学一下位运算不然很难看懂后面的代码

例如样例中的1 1 1 / 0 1 0 我们就可以用二进制数 111/010 (即7与2) 来表示

为了方便后面的计算我对其进行了取反的处理，就变成了 000/101 （即0与5）

这样用二进制数把图一行一行的存储就能将原 f 数组后面12维压缩成一维

当然还想优化空间也可以使用滚动数组（可我这种懒人不想写）

其实方程本来也就不难想主要是看怎么去把数组优化

所以我就不说状态转移方程怎么推了自己推一下吧

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int Mod=100000000;
int n,m,k,ans,x;
int map[15],st[5000],f[15][5000];
void init()
{
    k=0,ans=0;
    memset(map,0,sizeof(map));
    memset(f,0,sizeof f);
    memset(st,0,sizeof st);
 } 
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF) //有多组数据 
    {
        init();//记得初始化数组与变量 
        for(int i=1;i<=n;i++)
         for(int j=1;j<=m;j++)
         {
             scanf("%d",&x);
            if(x==0) map[i]+=1<<(j-1); //读入处理 
            //用来存地图(一行一行地存)并取反 
         }
            
        for(int i=0;i<(1<<m);i++)
          if(!(i&(i<<1))) st[++k]=i;    //判断是否相邻，找到可行的情况 
          
         for(int i=1;i<=k;i++)
          if(!(map[1]&st[i])) f[1][st[i]]=1; //初始化第一行 
          
         for(int i=2;i<=n;i++)
          for(int j=1;j<=k;j++)
          {
              if(st[j]&map[i]) continue;
              for(int l=1;l<=k;l++)
               {
                   if(st[l]&map[i-1]) continue;
                  if(!(st[l]&st[j])) f[i][st[j]]+=f[i-1][st[l]];
             }
         }
         
         for(int i=1;i<=k;i++)
          ans=(ans+f[n][st[i]])%Mod;
         printf("%d",ans);
    }    
    return 0;
}
```

---

## 作者：Sober_Clever (赞：1)

```cpp
#include<cstdio>
#include<vector>
using namespace std;
const int mod=100000000;
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}
	return x*w;
}

vector<int> s[15];
int n,m,f[15][1<<13]={0},cnt=0,sta[15]={0},len[15];//n行m列 
//上下左右不能种，f[i][j]表示符合题设条件且第i行状态为j的方案数
//s[i][j]表示状态i对第j行是否成立 

inline void init()
{
	int tot=(1<<n)-1;
	for(int i=0;i<=tot;i++)
	{
		if((i>>1)&i) continue;
		for(int j=1;j<=m;j++)
			if((sta[j]|i)==sta[j])//成立 
				s[j].push_back(i);
	}
}
int main()
{
	m=read(),n=read();
	for(register int i=1;i<=m;i++)
		for(register int j=1;j<=n;j++)
		{
			int x=read();
			if(x)
				sta[i]|=(1<<(n-j));
		}
	init();
	for(register int i=1;i<=m;i++)
		len[i]=s[i].size();
	for(register int i=0;i<len[1];i++)
		f[1][s[1][i]]=1;
	for(register int i=2;i<=m;i++)
	{
		for(register int j=0;j<len[i];j++)
		{
			int s1=s[i][j];
			for(register int k=0;k<len[i-1];k++)
			{
				int s2=s[i-1][k];
				if(s1&s2) continue;//判断上下是否有一样的 
				f[i][s1]=(f[i][s1]+f[i-1][s2])%mod;
			}
		}
	}
	int ans=0;
	for(register int j=0;j<len[m];j++)
	{
		int s1=s[m][j];
		ans=(ans+f[m][s1])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：redegg (赞：1)

状压的话是压缩每一行，然后每行每行地做类似背包的操作。

其状态定义为做到$i$行，第$i$行的状态是$j$（$j$是一个二进制$01$串，为了存储转换成十进制），算出来的总可能性数。

那么这个转移很明显，我们可以选择前面所有的可能，只要合法都可以加上去，而且前面一行也已经帮我们统计了它之前的答案，那么我们只需要从前一行合法的转移。这个状态$j$是可以为$0$的，毕竟这一行不选也是可以的。

主要问题在，如何判断是否不相邻。

对于相邻两行的比较，很简单，设两个01串是$S_1$，$S_2$，那么$S_1 $ & $S_2==0$就可以了。

但是同一行来比较每列呢？比较好写的是预处理出每个状态$j$是否相邻，比较好想，直接的是直接枚举进行比较。

至于复杂度，我也觉得有点大，毕竟数据水，过了并且跑得挺快的。


```
#include <bits/stdc++.h>
using namespace std;

int mod=100000000;

int n,m;
int a[100];
long long dp[105][6005];
long long ans;

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int now=1;
        for(int j=1;j<=m;j++)
        {
            int x;
            scanf("%d",&x);
            a[i]+=now*x;
            now*=2;
        }
    }

    dp[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=(1<<m)-1;j++)
        {
            bool ok=0;
            for(int k=2;k<=m;k++)
                if(((1<<(k-1))&j)&&((1<<(k-2))&j))
                {
                    ok=1;
                    break;
                }
            if(ok)continue;
            if((j&a[i])!=j)continue;
            for(int k=0;k<=(1<<m)-1;k++)
            {
                if((j&k)==0){
                    dp[i][j]+=dp[i-1][k];
                    dp[i][j]%=mod;
                }
            }
            dp[i][j]%=mod;
            if(i==n)ans=(ans+dp[i][j])%mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：wuzhaoxin (赞：1)

# 典型的状态压缩
#### 使用了各种玄学操作后，复杂度不超过1705548，空间也很小
###### （↓↓↓~~感觉数据有点水，不像蓝题的数据~~↓↓↓）

```
12 12
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
```

------------
首先预处理出所有的状态（不超过377种）
```cpp
for(int i=pw[n]*2-1;i>=0;i--)//pw[n]=pow(2,n+1)
    if(!(i&(i<<1)))
    {
    	zts++;
    	zt[zts]=i;
    }
```

------------
然后压缩每一行是否能种植
```cpp
int fd[13]={0};
for(int i=1;i<=m;i++)
    for(int j=1;j<=n;j++)
    {
    	cin>>fd[0];
    	if(!fd[0])
    		fd[i]+=pw[j];
    }
//若第i行当前状态&fd[i]!=0 则这种方式是非法的
```

------------
### 实现：
枚举状态（两个循环），若**zt[j]&zt[k]==0**则**dp[i][j]+=dp[i-1][k]**

------------

再加上滚动数组就能减少空间复杂度了
```cpp
#include<bits/stdc++.h>
using namespace std;
int zt[378]={0};
int main()
{
    ios::sync_with_stdio(0);
    int m,n,zts=0;
    int pw[13]={0};
    pw[1]=1;
    cin>>m>>n;
    for(int i=2;i<=n;i++)
    	pw[i]=pw[i-1]*2;
    for(int i=pw[n]*2-1;i>=0;i--)
    	if(!(i&(i<<1)))
    	{
    		zts++;
    		zt[zts]=i;
    	}
    int fd[13]={0};
    for(int i=1;i<=m;i++)
    	for(int j=1;j<=n;j++)
    	{
    		cin>>fd[0];
    		if(!fd[0])
    			fd[i]+=pw[j];
    	}
    int dp[2][378]={0};
    dp[0][zts]=1;
    for(int i=1;i<=m;i++)
    	for(int j=1;j<=zts;j++)
    	{
    		dp[i&1][j]=0;
    		if(zt[j]&fd[i])continue;
    		for(int k=1;k<=zts;k++)
    		{
    			if(zt[j]&zt[k])continue;
    			dp[i&1][j]+=dp[!(i&1)][k];
    			dp[i&1][j]%=100000000;
    		}
    	}
    int ans=0;
    for(int i=1;i<=zts;i++)
    	ans+=dp[m&1][i],ans%=100000000;
    cout<<ans;
    return 0;
}
```
还有一种不那么好的解决方式
```cpp
int dp[2][4096]={0};
    dp[0][0]=1;
    for(int i=1;i<=m;i++)
    	for(int j=1;j<=zts;j++)
    	{
    		dp[i&1][zt[j]]=0;
    		if(zt[j]&fd[i])continue;
    		for(int k=1;k<=zts;k++)
    		{
    			if(zt[j]&zt[k])continue;
    			dp[i&1][zt[j]]+=dp[!(i&1)][zt[k]];
    			dp[i&1][zt[j]]%=100000000;
    		}
    	}
    int ans=0;
    for(int i=1;i<=zts;i++)
    	ans+=dp[m&1][zt[i]],ans%=100000000;
```

---

## 作者：XG_Zepto (赞：1)

## 思路

根据数据范围和题意，这是一道非常裸的状压DP题。
对于每一行，我们枚举状态S和下一行的状态j，转移合法有以下条件：
- 这两行的种植方案中不包括不可用的土地
- 不存在相邻的草地

对于第一个判断，我们预处理出av数组，av[i]储存第i行不可用土地的状态，和上面提到的S，j一样，用01串表示。所以在判断的时候，只需要&一下即可。

对于第二个判断，只需要&一下(S,j),(S,(S>>1))和j,(j>>1))即可。

## 代码

（记得取模。

```
/*变量解释
mmp:防止和map重名，储存土地是否可用
av:指available，以01串储存第i行的可用状态
dp:储存方案数
n，m:含义与题意刚好相反
*/
#include <bits/stdc++.h>
#define maxn 15
#define sum (1<<15)
#define p 100000000
#define ll long long
using namespace std;
ll n,m,ans,mmp[maxn][maxn];
ll av[maxn],dp[sum][maxn];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m; int temp;
    for (ll i=0;i<n;i++)
    for (ll j=0;j<m;j++){
    	cin>>temp;
    	if (!temp) mmp[i][j]=1;
    }
    ll up=(1<<m);
    for (ll i=0;i<n;i++)
    for (ll j=m-1;j>=0;j--)
    av[i]+=mmp[i][j]*pow(2,m-j-1);//预处理av数组，0表示可用，1表示不可用
    for (ll S=0;S<up;S++)
    if (！S&av[0])&&(！&(S>>1))) dp[S][0]=1;//边界条件，第一行的合法状态方案数为1
    for (ll i=0;i<n-1;i++){
        for (ll S=0;S<up;S++)
        if (dp[S][i])
        for (ll j=0;j<up;j++)
        if (!(j&av[i+1])&&!(j&(j>>1))&&!(S&j))
        dp[j][i+1]+=(dp[S][i])%p;
    }
    for (ll i=0;i<up;i++)
    ans+=dp[i][n-1];
    cout<<ans%p;
}
```

---

## 作者：xxxxxxx__ (赞：1)

#### 看了一下前面的题解，感觉说的都不太清楚，所以决定自己写一篇！

#### 仍然是个状压dp的入门题 直接用模版做法套上去即可

#### 具体来说的话就是：先枚举出可能的摆放方式（不考虑土地的问题，只考虑一行的玉米田是否冲突），再遍历每一行推出方案数即可

#### 转移方程是：f[i][j]+=f[i-1][k] i表示第几行，j表示这一行的方案数，显然这一行摆成j能产生的方案数是上一行摆所有不冲突状态产生的方案数之和。

#### 之后遍历一遍输出方案即可

#### 注意读题！！ 开始我以为是周围八个都不能种玉米，但其实是上下左右四个。（大概只有我这么傻吧）


---

## 作者：我欲LU天 (赞：1)

题意:自己看，看不到没必要做吧-\_-||
做法：由于n,m只有12；结合要求方案数所以是装压dp+二进制；

限制条件：①作业周围不能有作业，②不能再“0”处放作业；

解决方法：①用与运算逐位比较②与运算区别“1”“0”方格；

转移：求方案数；f[i][j]=f[i][j]+f[i-1][k];

k从0枚举到1<<n-1;其中f[i][j]表示第i列状态为j的方案数；

细节:①作业：左右需要比较相邻两列的状态是否合法

②f[0][0]=1，别小看这个了;

答案统计：只要求和最后一列的所有状态即可；

~~最后怼一波上个题解（滑稽）：思路差不多，但是写法的问题比较多，详细见下（不是真的怼，吐槽一下罢了不会打我吧？？）；~~

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int g[15],s,m,n,f[15][1<<13],ans,mod=100000000;
bool check(int x)
{
    for(int i=0;i<=n-1;i++)
    if((x&(1<<i))&&(x&(1<<(i-1))))//上下是否合法
    return 0;return 1;
}
int main()
{
    f[0][0]=1;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        cin>>s;
        g[j]|=s<<i-1;
    }
    f[0][0]=1;
    for(int i=1;i<=m;i++)
    for(int j=0;j<=(1<<n)-1;j++)
    {
        if((j&g[i-1])!=j)continue;//左右合法，注意g[i-1]
        if(!check(j))continue;
        for(int k=0;k<=(1<<n)-1;k++)
        {
            if(k&j)continue;
            if((k&g[i])!=k)continue;//左右合法注意和g[i]
            if(!check(k))continue;
            f[i][k]=(f[i][k]+f[i-1][j])%mod;
        }
    }
    for(int i=0;i<=(1<<n)-1;i++)
    ans=(ans+f[m][i])%mod;
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：chenzijie (赞：1)

状态表示，对于每行土地，可用每个2进制位表示该行中每块土地的状态（1表示种草，0表示不种草），这样对于每行土地状态state可用以下形式表示（每行土地最有n块）：

n    n-1    …    3    2    1    十进制

min    0    0    0    0    0    0    0

1/0    1/0    1/0    1/0    1/0    1/0    …

max    1    1    1    1    1    1    2n-1

故，对于每一行，state范围为：[0, 2n-1]

然后，对该行的每一种状态进行可行性判断，如果有某格土地贫瘠，或存在连续两格有种草，均为不符合要求的状态


对于每行土地中，每格土地是否能种草（土地是否贫瘠），可以用数组yes[1-M]（压缩状态）表示，对于行i，yes[i]中存放一个状态值，该状态值每一位对应一块土地的贫瘠情况，以样例1为例：

样例1，2行3列，

1    2    3

1    1（可种草）    1（可种草）    1（可种草）

2    0（不可种草）    1（可种草）    0（不可种草）

相应的数据存储如下：

二进制    十进制

yes[1]    111    7

yes[2]    010    2


若已知m,n，并获取土地贫瘠状态数组map[m][n](非压缩的，map[i][j]=0/1表示第i行第j列土地贫瘠/不贫瘠)

计算yes的具体代码如下：


```cpp
doyes()
{
  int i,j;
for (i=1;i<=m;i++)//对每一行进行处理
for(j=n;j>=1;j--)//从高位到低位，类似多位数字字符串转数值
  yes[i]=yes[i]<<1 | map[i][j];  
}
```
按行进行动态规划，计算符合要求的方案数量,dp[i][state]表示动态规划到第i行状态state时，符合要求的方案数
初始值：dp[0][0-2n-1]=1

i从1-n逐行动态规划：

  
首先，看该行的state是否符合要求：

if ((state | yes[i])!=yes[i]) continue;//若state中含贫瘠土地，则为不可能方案

if ((state & (state<<1))!=0) continue;//若state中有连续两块土地种草，则为不可能方案


再与dp[i-1][各种state]进行对比，进行动态规划


        
    
    
            
        
                    
        
        
```cpp
for(k=0;k<=2n-1;k++)//表示第i-1的各种状态
  { if((state & k) !=0)continue;//表示该行与上一行有同一列上都种了草，为不可能方案
   dp[i][state]+=dp[i-1][k];}//符合条件方案，叠加方案数
    #include<cstdio>
    using namespace std;
    int main()
    {
        int n,m,map[15][15],dp[15][1<<13]={0},ans=0;
        scanf("%d %d",&m,&n);
        for (int i=1;i<=m;i++)
            for (int j=1;j<=n;j++)
                scanf("%d",&map[i][j]);
        int rich[15]={0};
        for (int i=1;i<=m;i++)
            for (int j=1;j<=n;j++)
                  rich[i]=(rich[i]<<1)|map[i][j];
        for (int j=0;j<=(1<<n)-1;j++)
            if (((j|rich[1])==rich[1])&&((j&(j<<1))==0))
                dp[1][j]=1;
        for (int i=2;i<=m;i++)
            for (int j=0;j<=(1<<n)-1;j++)
                if (((j|rich[i])==rich[i])&&((j&(j<<1))==0))
                    for (int k=0;k<=(1<<n)-1;k++)
                        if((k&j)==0)
                            dp[i][j]+=dp[i-1][k];
        for (int i=0;i<=(1<<n)-1;i++)
            ans+=dp[m][i];
        printf("%d",ans%100000000);
        return 0;
}
```

---

## 作者：何卓然 (赞：1)

经典的状压DP例题


我们在审题时发现，题目中要求的合法的方案，没有公共边即可。

对于一种方案，每一行的选取，只对当前行，和上下两行有影响，我们考虑动态规划，

不妨设 dp[i][j] 表示取到第 i 行，第 i 行的选取状态为 j 的方案数，本题的要求刚好满足动态规划解决问题的一大要件：无后效性。

就是说，我们在第 i 行枚举选取状态时，所受到的限制仅仅来自于当前行和上一行，于是，我们得到了状态转移方程：


dp[i][j] = Σ(dp[i-1][k])    （j 在第 i 行没有冲突，没有选取不能选的点 && j 与 k 没有相邻选取）


最终的答案是：Σ(dp[n-1][i])   ( i ∈ [0,1<<m) )



**Code**









        



    


```cpp
#include<bits/stdc++.h>
#define MOD int(1E8)
using namespace std;
int dp[20][1<<15];
bool ok_state[20][1<<15];
int a[20][20];
int n,m,ans = 0;
bool check(int line,int sta)
{
    for (int i=0;i<m;i++)
        if ( ( sta & (1 << i) ) && a[line][i] == false) /// 不能取的点取了
            return false;
    for (int i=1;i<m;i++)
        if ( ( sta & (1 << i) ) && ( sta & (1 << (i - 1))) ) /// 连选两个
            return false;
    return true;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            scanf("%d",&a[i][j]);
    memset(dp,0,sizeof dp);
    for (int i=0;i<n;i++)
        for (int j=0;j<(1<<m);j++)
            ok_state[i][j] = check(i,j);
    for (int i=0;i<(1<<m);i++) dp[0][i] = ok_state[0][i];
    for (int i=1;i<n;i++)
    {
        for (int j=0;j<(1<<m);j++) /// 枚举第 i 行的选取状态
        {
            if (ok_state[i][j] == false) continue;
            for (int k=0;k<(1<<m);k++) /// 枚举 i - 1 的选取状态
            {
                if (ok_state[i-1][k] == false) continue;
                bool flag = true;
                for (int t=0;t<m;t++)
                    if (j & (1 << t) && k & (1 << t))
                    {
                        flag = false;
                        break;
                    }
                if (flag) dp[i][j] = (dp[i][j] + dp[i-1][k]) % MOD;
            }
        }
    }
    for (int i=0;i<(1<<m);i++) ans = (ans + dp[n-1][i]) % MOD;
    printf("%d",ans);
    return 0;
}

```

---

## 作者：ChrisK (赞：0)

蓝书上看到的状压DP练习题。数据范围也就是状压。

状压最关键就是预处理出合法的状态。

这个题合法的状态就是当前状态左移和右移分别与当前状态按位与，结果都为0。

预处理出正确的状态就可以快乐DP了。

不要忘了判断上下两行的是不是合法。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=100000000;
int tu[20][20],m,n,f[20][5000];
int h[20];
bool pd[1<<13];
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&tu[i][j]);
			h[i]=(h[i]<<1)+tu[i][j];
		}
	 for(int i=0;i<(1<<n);i++)
	 	if( !((i>>1) & i) && !((i<<1) & i) )
			pd[i]=1;
		else pd[i]=0;
	f[0][0]=1;
	for(int i=1;i<=m;i++)
		for(int j=0;j<(1<<n);j++)
			if(pd[j] && (j&h[i])==j)
				for(int k=0;k<(1<<n);k++)
					if(!(k&j))
						f[i][j]=(f[i][j]+f[i-1][k])%mod;
	long long ans=0;
	for(int i=0;i<(1<<n);i++)
		ans=(ans+f[m][i])%mod;
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：ljc20020730 (赞：0)

介绍一个子集枚举的通用算法：

设$Sub$是状态$mask$的子集，那么对于$Sub$中状态所有可能的取值为(含空集)：

```cpp
 for (int Sub =  mask; ; Sub=(Sub-1) & mask ){
 	// do sth. 
 	if (!mask) break;
 }
```

所以这道题就是一个很明显的状态压缩dp了。

设$f[i][j]$表示前$i$行合法且最后一行的状态是$j$的方案数。

对于这一行状态只和这一行和上一行状态有关系。

枚举这一行状态为$mask1$,上一行状态为$mask2$

- 若本行状态不合理产生的限制为 mask1存在两个连续的1

- 若上一行状态不合理产生的限制为 mask2存在两个连续的1

- 若上一行状态+这一行状态不和里就是mask1和mask2相同位上都有1

对于$1,2$两个限制，我们只需要：
```cpp
if (mask >> 1) return false;
else return true;
```
对于$3$限制，我们只需要
```cpp
if (mask1 & mask2) return false;
else return true;
```

代码就比较简单了：

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N=13,mo=100000000;
int f[N][1<<N],n,m,state[N];
signed  main()
{
	scanf("%lld%lld",&n,&m); int all=(1<<m)-1;
	for (int i=1;i<=n;i++) {
		int ret=0;
		for (int j=1;j<=m;j++) {
			int t; scanf("%lld",&t);
			ret=(ret<<1)+t;
		}
		state[i]=ret;
	}
	
	for (int mask=state[1] ; ; mask=(mask-1)&state[1] )  {
		if (!(mask & (mask>>1))) { f[1][mask]=1; }
		if (!mask) break;
	}
	 
	for (int i=2;i<=n;i++) {
		for (int mask1 = state[i]; ;mask1=(mask1-1)&state[i]) {
			if (mask1 & (mask1>>1)) continue;
			for (int mask2=state[i-1]; ;mask2=(mask2-1)&state[i-1]) {
				if (mask2 & (mask2>>1)) continue;
				if (mask1 & mask2) continue;
				(f[i][mask1]+=f[i-1][mask2])%=mo;
				if (!mask2) break;
			}
			if (!mask1) break;
		}
	}
	
	int ans=0;
	for (int i=0;i<=all;i++) (ans+=f[n][i])%=mo; 
	printf("%lld\n",ans);
	 
	return 0;
}
```

---

## 作者：鹭天 (赞：0)

#### [博客传送门](https://blog.csdn.net/huang_ke_hai/article/details/86669145)
#### 题目描述：
农场主John新买了一块长方形的新牧场，这块牧场被划分成M行N列(1 ≤ M ≤ 12; 1 ≤ N ≤ 12)，每一格都是一块正方形的土地。John打算在牧场上的某几格里种上美味的草，供他的奶牛们享用。
遗憾的是，有些土地相当贫瘠，不能用来种草。并且，奶牛们喜欢独占一块草地的感觉，于是John不会选择两块相邻的土地，也就是说，没有哪两块草地有公共边。
John想知道，如果不考虑草地的总块数，那么，一共有多少种种植方案可供他选择？（当然，把新牧场完全荒废也是一种方案）
***
输入输出格式

输入格式：
第一行：两个整数M和N，用空格隔开。
第2到第M+1行：每行包含N个用空格隔开的整数，描述了每块土地的状态。第i+1行描述了第i行的土地，所有整数均为0或1，是1的话，表示这块土地足够肥沃，0则表示这块土地不适合种草。
***
输出格式：
一个整数，即牧场分配总方案数除以100,000,000的余数。
***
分析：状压dp，设dp[i][j]为第i行状态为j的方案数。开始用一个数组$f[i]$预处理出每一行的二进制所对应得十进制数。转移时，枚举上下两行，不难发现，如果当前种的田是合理的，那么就肯定满足 $(i\&(i>>1)==0)\&\&(i\&(i<<1)==0)$，以及是放在农田不贫瘠的土上的$(j|f[k]==j)$。转移时就从上层转移累加即可.

不难处理出预处理部分：

```cpp
    for (int i=1,x;i<=n;i++){
	    int sum=0;
	    for (int j=1;j<=m;j++) scanf("%d",&x),sum=sum*2+x;
	    f[i]=sum;
	}
```

dp部分如下：

```cpp
	for (int i=1;i<=n;i++)
	  for (int j=0;j<=sum;j++)
	    if (vis[j]&&((j&f[i])==j))
	      for (int k=0;k<=sum;k++)
	        if (!(k&j))
	          dp[i][j]=(dp[i][j]+dp[i-1][k])%P;
```
这两部分是核心，需要注意，不过值得一提的是这道题的初值也比较特殊。

那么具体代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define P 100000000
int f[100001];
int dp[13][16777217];
bool vis[16777217];
int n,m;

int main(){
    scanf("%d %d",&n,&m);
    for (int i=1,x;i<=n;i++){
	    int sum=0;
	    for (int j=1;j<=m;j++) scanf("%d",&x),sum=sum*2+x;
	    f[i]=sum;
	}
//	for (int i=1;i<=n;i++) cout<<f[i]<<endl;
	int sum=(1<<m)-1;
	for (int i=0;i<=sum;i++)
	  if (!(i&(i<<1))&&(i|f[1])==f[1]) dp[1][i]=1;
	for (int i=0;i<=sum;i++)
	  vis[i]=(!(i&(i>>1)))&&(!(i&(i<<1)));
	for (int i=1;i<=n;i++)
	  for (int j=0;j<=sum;j++)
	    if (vis[j]&&((j&f[i])==j))
	      for (int k=0;k<=sum;k++)
	        if (!(k&j))
	          dp[i][j]=(dp[i][j]+dp[i-1][k])%P;
	int ans=0;
	for (int i=0;i<=sum;i++) ans=(ans+dp[n][i])%P;
	printf("%d",ans);
}
```



---

## 作者：Baihua (赞：0)

## P1879 [USACO06NOV]玉米田Corn Fields

看到 N 较小 ， 应该能想到 **状态压缩**

* #### 状态设计

```
F[I][J]
```

表示第Ｉ行处于状态Ｊ，总的方案数　；

那么容易得出Ｆ［Ｉ］［Ｊ］　＝　$F[i][j]=sum(F[i-1][0],F[i-1][1],F[i-1][2])$

* #### 判断状态是否合法

  ```
  (i<<1)&i
  ```

  这可以判断I中是否有相邻的两个1；



* #### 调试的小技巧

  显示数字代表的状态

  ```c
  string Dbg(int X) {
      string Ans = "" ;
      for (R int i = 0 ; i < M ; ++ i) {
          Ans = (char)('0' + (((1<<i)&X)?1:0)) + Ans ;
      }
      return Ans ;
  }
  ```



* Code

  ```C
  #include <string.h>
  #include <stdio.h>
  #define re register
  #define gc getchar()
  int Qread () {
      int x = 0,f = 1;
      char ch = gc ;
      while (ch >'9' || ch < '0') {
          if (ch =='-')f = -1;
          ch = gc ;
      }
      while (ch >='0' && ch <='9') {
          x = x * 10 + ch -'0' ;
          ch = gc ;
      }
      return x *f ;
  }
  const int Wzx = 100000000 ;
  int N , M ,F[14][4098];
  unsigned short int A[14] , Pw;
  int main () {
      //freopen ("P1879.in" , "r" , stdin) ;
      N = Qread () , M = Qread () ;
      Pw = 1 << M ;
      memset (A , 0 ,sizeof (A)) ;
      re unsigned int i , j , k;
      for (i = 0; i < N; ++ i) {
          for (j = 0 ; j < M ; ++ j) {
              A[i]= A[i] | (Qread() << j) ;
          }
          A[i] = ~A[i] ;
      }
      memset (F , 0 , sizeof (F)) ;
      for (i = 0 ; i < Pw ; ++ i) {
          if ((i >> 1) & i) continue ;
          if (i&A[0]) continue ;
          F[0][i] = 1 ;
      }
      for (i = 1; i < N ; ++ i) {
          for (j = 0 ; j < Pw; ++ j) {
              if ((j>>1) & j) continue ;
              if (j&A[i]) continue ;
              for (k = 0 ; k < Pw ; ++ k) {
                  if (k&A[i-1]) continue ;
                  if (k&j)continue ;
                  F[i][j] += F[i-1][k] ;
                  F[i][j] %= Wzx; 
              }
          }
      }
      int Ans = 0 ;
      for (i = 0 ; i < Pw ; ++ i) {
          Ans += F[N-1][i] ;
          Ans %= Wzx; 
      }
      printf ("%d\n" , Ans) ;
      fclose (stdin) ;
      fclose (stdout);
      return 0;
  }
  ```



Thanks!

---

## 作者：狸狸养的敏敏 (赞：0)

位运算+DP经典好题。  
具体思路：输入的地图由于只有0和1，很容易想到用2进制来保存。  
例如：$1 0 1$用$5$来保存，即$2^2+2^0$  

输入完地图之后，就可以来生成初始状态，先生成当前行中可能的状态

我们使用位运算来进行初始化，例如$110$不是一种可行的方案，因为 6&(6<<1) != 0 ，为什么！=0就不成立呢？

比如$1 1 0_2$，他左移1位变成了$1100_2$,110$_2$&1100$_2$=$100_2 \neq 0$，

而$101_2$就是一种可行的方案，因为他与他左移一位后做与运算等于0。

解决了初始化，我们再来看看塞入地图的问题，这个简单，将可能性与地图进行或运算，如果结果仍然是地图，那么这就是一种可行的方案。

最后，我们来看看DP的思路，dp[i][j]表示前i行的第j种状态最多的种数，因此答案就是$\sum dp[n]$。

```cpp
int n,m,maps[22],cnt,ans;//cnt表示成立的方案种数
int ok[5555],dp[22][5555];//dp[i][j]表示前i行的第j种状态的最大值（答案就是把最后一行都加起来） ，ok表示成立的状态
int main() {
	ios::sync_with_stdio(0);
	n=read();
	m=read();
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			if(read())maps[i]+=(1<<j);//读入地图（我这里实际上是反着存的，但是并不影响结果）
	for(int i=0; i<(1<<m); i++)
		if(!(i&(i<<1)))
			ok[cnt++]=i;//检查可能的情况种数
	for(int i=0; i<cnt; i++)
		if((maps[0]|ok[i])==maps[0])dp[0][i]=1;//优先处理第1行（我存图从0开始）
	for(int i=1; i<n; i++) {
		for(int j=0; j<cnt; j++)
			if((maps[i]|ok[j])==maps[i])//如果这种状态可以放进当前地图
				for(int k=0; k<cnt; k++)
					if(!(ok[j]&ok[k]))dp[i][j]+=dp[i-1][k];//如果第j种状态和第k种状态没有冲突，则继承上一状态的答案
	}
	for(int i=0; i<cnt; i++)
		ans+=dp[n-1][i];//把最后一行加起来
	write(ans%100000000);//输出结果
	return 0;
}


```

---

## 作者：天下第一剑客 (赞：0)

首先这个数据范围……刚开始脑子一抽以为2^12会MLE，看了题解再一算——还绰绰有余hhhh

首先说一下状态定义，和楼下大佬都是一样的，f[i][j]表示第i行状态为j的方案数，j是用十进制表示的一个二进制数，二进制数的每一位代表该为选还是没选，选了就是1，不选就是0

（其实第一维是可以用滚动数组优化掉的，但懒得写）

我个人比较喜欢刷表法，感觉推起来比较方便，所以……

另外这个题是我第一次用递归来更新状态hhhh

下面是代码，具体细节在代码里讲

```cpp
#include<bits/stdc++.h>
#define REP(x,a,b) for (int (x)=(a); (x)<=(b); (x)++) //个人习惯hhhh
using namespace std;
const int N=13,toad=100000000;//至于为什么模数起这个名字，想想它的英语（手动滑稽）
int n,m,ans,a[N][N],f[N][1<<N];//动规数组起名为f
int read(){
    char c=getchar(); bool negative=false; int ret=0;
    while ((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-') negative=true,c=getchar();
    while (c>='0' && c<='9') ret=ret*10+c-'0',c=getchar();
    return negative?-ret:ret;
```
}//读入优化（江胡习气）
void Update(int line, int step, int stats, int value, int cur){//递归更新状态，line代表那一行，step代表现在在填第几位，stats是上一行用于转移的状态，value就是上一行该状态的方案数，cur是当前状态

if (step==m+1){f[line][cur]=(f[line][cur]+value)%toad; return;}//如果step==m+1代表填完了，更新答案

    if (cur&1 || (stats>>m-step)&1) Update(line,step+1,stats,value,cur<<1);//如果这一位的左边或上面是1这一位只能是0
```cpp
    else {//否则
        Update(line,step+1,stats,value,cur<<1);//可以不放
        if (a[line][step]) Update(line,step+1,stats,value,cur<<1|1);//放的话必须满足这位置的土地是肥沃的
    }
}
int main(){
    n=read(), m=read();
    REP(i,1,n) REP(j,1,m) a[i][j]=read();//读入
    f[0][0]=1;//初始化，因为第0行不能填，可以看做这一行土地全部贫瘠，这样这一行只能一个不放
    REP(i,0,n-1) REP(j,0,(1<<m)-1) if (f[i][j])//挨个刷表，注意刷表的时候行数只能到n-1
        Update(i+1,1,j,f[i][j]%toad,0);
    REP(i,0,1<<m) ans=(ans+f[n][i])%toad;//统计答案，同时不忘膜*
    printf("%d",ans%toad);//输出
    return 0;
}
```

---

## 作者：cheeseYang (赞：0)

状压DP，本题主要在于存2进制数，还有题目的意思是输入为0的草地不能种草，也就是说在题目里我们还要判断当前的状态是否满足这一要求，存图可以反过来存，因为这样1就是不能放，方便我们的位运算&直接筛掉这些不能放的情况，其它就没有什么特别注意的地方了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int hang=13;
const int zong=1<<hang;
int n,m,st[zong],dp[hang][zong],mapp[hang],k,ans;
void read(int &x){
    char c=getchar();x=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
}
int pd(int x){
    return x&(x<<1);
}
int bj(int x,int y){
    return (mapp[x]&st[y]);
}
int main(){
    read(m),read(n);
    for(register int i=1;i<=m;++i)
        for(register int j=1;j<=n;++j){    
            int x;
            read(x);
            if(x==0){
                mapp[i]+=1<<(j-1);
            }
        }
    for(register int i=0;i<(1<<n);++i){
        if(!pd(i))
            st[k++]=i;
    }
    for(register int i=0;i<k;++i)
        if(!bj(1,i))
            dp[1][st[i]]=1;
    for(register int i=2;i<=m;++i){
        for(int j=0;j<k;++j){
            if(bj(i,j))continue;
            for(int f=0;f<k;++f){
                if(bj(i-1,f))continue;
                if((st[j]&st[f])==0)
                    dp[i][st[j]]+=dp[i-1][st[f]];
            }
        }
    }
    for(int i=0;i<(1<<n);++i){
        ans+=dp[m][i];
        ans%=100000000;    
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：zhaoyifan (赞：0)

看取膜的数就知道暴搜死定，那么用状压，f[i][j]表示可以转移到i行j状态的方案数，和互不侵犯类似，但由于提前有赋值，所以把1和0换一下可以更方便的判断推导。

```cpp
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int m,n;
bool a[14][14];int b[14],f[14][9000];
int dfs(int x,int y,int zhuang,int net,int l,int old)
{
    if(y>=n)
    {
        f[x+1][(net|b[x+1])]=(f[x+1][(net|b[x+1])]+old)%100000000;
        return 0;
    }
    if(y-l>1&&((1<<y)&zhuang)==0)
    {
        int k=net;
        k=k|(1<<y);
        dfs(x,y+2,zhuang,k,y,old);
    }
    dfs(x,y+1,zhuang,net,l,old);
}
int main()
{
    cin>>m>>n;
    for(int i=1;i<=m;++i)
     for(int j=1;j<=n;++j)
     cin>>a[i][j];
    for(int i=1;i<=m;++i)
    {
        b[i]=0;
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]==1)
            a[i][j]=0;
            else a[i][j]=1;
            b[i]<<=1;
            b[i]+=a[i][j];
        }
    }
    f[1][b[1]]=1;  //从f【0】【0】推也可以
    for(int i=1;i<=m;++i)
     for(int j=0;j<(1<<n);++j)
      if(f[i][j])
      {
          dfs(i,0,j,0,-2,f[i][j]);
      }
    int ans=0;
    for(int i=0;i<(1<<n);++i)
    ans=(ans+f[m+1][i])%100000000;
    cout<<ans;
    return 0;
}
```

---

## 作者：顾z (赞：0)

# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

题目描述-->[p1879 [USACO06NOV]玉米田Corn Fields](https://www.luogu.org/problemnew/show/P1879)

### 分析

**下面的$n,m$为$n$行$m$列,与题目描述不符.**

难得做起了状压DP的题 

$f[i]$代表第$i$行的状态.就是输入的状态,这个东西的话就直接算就好了.

$$(f[i]<<=1)|=x$$

初始化：$dp[0][0]=1$

那么我们需要枚举每一行,再枚举状态$j$判断当前行的状态$f[i]$是否会包含状态$j$,即合法与否.

判断不能有相临的话,直接写一个函数即可

![](https://i.loli.net/2018/10/12/5bc09deb93c6b.png)

这里就不多解释了.

然后在枚举上一行状态$k$是否与当前状态$j$不相邻.即上下＆起来为0。

(这就涉及到了＆的性质,两边为$True$才为$True$)

$$ans=\sum_{i=0}^{(1<<m)-1}f[n][i]$$

时间复杂度$O(n \times 2^{m+1})$

``代码``

```c++
#include<cstdio>
#include<cctype>
#define mod 100000000
#define R register
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int res[15][15],f[18],n,m,dp[18][1<<15],ans;
inline bool ok(int state)
{
	return ((state&(state>>1))==0 and (state&(state<<1))==0);
}
int main()
{
	in(n),in(m);
	for(R int i=1;i<=n;i++)
		for(R int j=1,x;j<=m;j++)
		{
			in(x);
			(f[i]<<=1)|=x;
		}
	int state=(1<<m)-1;
	dp[0][0]=1;
	for(R int i=1;i<=n;i++)
		for(R int j=0;j<=state;j++)
			if(ok(j) and (f[i]&j)==j)
				for(R int k=0;k<=state;k++)
					if((k&j)==0)
						(dp[i][j]+=dp[i-1][k])%=mod;
	for(R int i=0;i<=state;i++)
		(ans+=dp[n][i])%=mod;
	printf("%d",ans%mod);
}
```



---

## 作者：C201914 (赞：0)

**高能警告 高能警告**

~~其实一点也不高能QWQ~~

做完以后看了众位大佬的题解，似乎只有我这个蒟蒻输入时用了[异或](https://blog.csdn.net/xiezhongyuan07/article/details/79248516)？

好了不管了，重点是我的思路实际上与前人并无两样：dfs暴力预处理出对于任一行所有可能的状态（暂不考虑贫瘠的土地），就是这样滴：
```
void dfs(int depth,int x)
{
	if(depth>=m)
	{
		sum[++cnt]=x;
		return;
	}
	dfs(depth+1,x);
	dfs(depth+2,x+(1<<depth));
}
```

其中sum记录的就是用二进制表示的每行的状态，如：
```
1 0 1 0 0 1
```
我们就可以把它看做一个6位二进制数。注意，在本蒟蒻的代码中该二进制数是倒着存的（= =）例子中的01串就表示为1+2^2+2^5=37。易得每行种地方案数总数（_cnt_）不超过$2^{12}$

预处理完毕，就该考虑状态转移方程了。我们用_prog[i][j]_表示第_i_行第_j_种种地方式的方案总数，那么在合法的情况下，就有prog[i][j]=$\sum_{k=1,j=1}^{cnt}{prog[i-1][k]}$

这里_k_是枚举上一排（即第_i-1_排）的种地方式，_j_是枚举当前排（即第_i_排）的种地方式。

最后代码如下
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 100000000
typedef unsigned long long ULL;
using namespace std;
ULL n,m,prog[13][4097],sum[4097],cnt=0,field[13];
long long read()
{
	long long res=0,bj=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')bj=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=res*10+c-48;c=getchar();}
	return res*bj;
}
void dfs(int depth,int x)
{
	if(depth>=m)
	{
		sum[++cnt]=x;
		return;
	}
	dfs(depth+1,x);
	dfs(depth+2,x+(1<<depth));
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)field[i]+=((read()^1)<<(j-1));
	dfs(0,0);
	for(int i=1;i<=cnt;i++)
		if(!(field[1]&sum[i]))prog[1][i]=1;//预处理部分（千万记得判断合法，蒟蒻就是因为没在这里判断WA了一个点）
	for(int i=2;i<=n;i++)
		for(int j=1;j<=cnt;j++)
			for(int k=1;k<=cnt;k++)
			{
				if(sum[j]&field[i])continue;//如果该情况不合法舍去
				if(sum[k]&field[i-1])continue;//如果上一行不合法舍去
				if(sum[j]&sum[k])continue;//如果上下相邻也舍去
				prog[i][j]+=prog[i-1][k];//总感觉之前的求和符号写错了，不过看代码也能看懂
				prog[i][j]%=MAXN;记得取模
			}
	ULL ans=0;
	for(int i=1;i<=cnt;i++)ans+=prog[n][i];
	printf("%lld\n",ans%MAXN);
//	for(int i=1;i<=cnt;i++)printf("%lld\n",prog[n][i]);
	return 0;
}

```
后记：本蒟蒻$\sum$没学过，~~（估计用错了）~~；LATEX又不会，只能临场问个大佬才能勉强维持的了生活这样子。

---

## 作者：DarkEyeR (赞：0)

这道题和棋盘那道题很相似 就是poj上那个，我们唯一需要多考虑的一点就是如何解决行内某个位置不能放置的问题。

我是利用记录行内不能放置的位置，然后枚举每个位置通过位运算来进行判断，具体可看check函数


    
    
    
```cpp
    #include <iostream>
    #define MAX 100
    using namespace std;
    int pic[14][14];
    int dp[14][1<<13];
    int n,m,k;
    int check(int x,int y){
        if(((y >> 1) & y)) return 0;
        for(int i = 1;i <= pic[x][0];i++){
            if((y >> (m-pic[x][i])) & 1)
                return 0;
        }
        return 1;
    }
    int main(){
        cin >> n >> m;
        for(int i = 1;i<=n;i++)
            for(int j = 1;j <= m;j++){
                int a;
                cin >> a;
                if(a == 0){
                    pic[i][++pic[i][0]] = j;
                }
            }
        dp[0][0] = 1;
        for(int i = 1;i <= n;i++){
            for(int j = 0;j < (1<<m);j++){
                if(!check(i,j)) continue;
                for(int k = 0;k < (1<<m);k++){
                    if(!check(i-1,k) || (j & k)) continue;
                    dp[i][j] += dp[i-1][k];
                }
            }
        }
        unsigned long long int ans = 0;
        for(int i = 0;i < (1<<m);i++){
            ans += dp[n][i];
        }
        cout << ans%100000000 ;
        return 0;
}
```

---

## 作者：ysner (赞：0)

数据范围小的可怜（m,n<=12），但结果似乎又很大（mod1000000000），爆搜会T。这道题数据摆明要我们用状压DP乱搞。

二进制01串存信息应该很经典吧（位与|=）；

然后每次枚举两行状态防止上下相邻，同时check防止左右相邻。

不妨设 dp[i][j] 表示取到第 i 行的选取状态为 j 的方案数，

然后把方案数累加起来，dp[i][j] = Σ(dp[i-1][k]) （j 在第 i 行没有冲突，没有选取不能选的点 && j 与 k 没有相邻选取（上下+左右））

最终的答案是：Σ(dp[n-1][i]) ( i ∈ [0,1<<m) )

另外，位运算符优先级比加减乘除之类的都低，使用时别忘了打括号。。。


```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define ll long long
#define re register
#define il inline
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
const int mod=100000000;
int n,m,g[15]={},f[15][1<<13]={},ans=0;
il int gi()
{
    re int x=0;
    re int t=1;
    re char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') t=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*t;
}
il bool check(int x)
{
    fp(i,1,m-1)
        if((x&(1<<i))&&(x&(1<<(i-1)))) return 0;//防止作业放在左右相邻格子的情况
    return 1;
}
int main()
{
    m=gi();n=gi();
    fp(i,1,m)
      fp(j,1,n)
        g[j]|=(gi()<<i-1);//g[i]用于存第i行所有状态
    f[0][0]=1;
    fp(i,1,n)
        fp(j,0,(1<<m)-1)//枚举第i行的选取状态
    {
        if((j&g[i-1])!=j) continue;//防止在不能放作业的地方放作业
        if(!check(j)) continue;
        fp(k,0,(1<<m)-1)//枚举i-1行的选取状态
        {
            if(k&j) continue;//防止上下相邻选取
            if((k&g[i])!=k) continue;//注意&的优先级低于!=,要打括号 
            if(!check(k)) continue;
            f[i][k]=(f[i][k]+f[i-1][j])%mod;//从上一行转移状态
        }
    }
    fp(i,0,(1<<m)-1)
      ans=(ans+f[n][i])%mod;
      printf("%d\n",ans);
    return 0;
}

```

---

## 作者：chestX_ray (赞：0)

看到数据范围毫无疑问的状压动归

还是一如既往的没有代码里加注释的习惯

先预处理一波 得到每一行的所有状态一共 s种 s=2的n次方-1

然后枚举每种状态 看是否符合左右没有相邻的 g[i]=(!(i<<1 & i) && !(i>>1 & i))

在输入的时候考虑哪些地不能种

用t[i]记录 判断的时候 (j&t[i])==j 看是否符合要求

一次枚举上一行的状态 for(int j=0;j<s;j++)

和下一行的状态 for(int k=0;k<s;k++)

判断上下没有相邻的 !(j&k)

然后相加就ok了

顺便说一句

位运算由于太底层了 运算的优先级贼低（所以我被坑了很久），比赋值的优先级还低

所以多加括号（敲黑板）！！！

```cpp
#include<cstdio>
#define N 14
#define S (1<<13)+5 
int m,n,s,x,ans,f[N][S],t[N],g[S];
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++){
            scanf("%d",&x);
            t[i] = (t[i]<<1) + x;
        }
    s=1<<n;
    for(int i=0;i<s;i++)
        g[i]=(!(i<<1 & i) && !(i>>1 & i));
    f[0][0]=1;
    for(int i=1;i<=m;i++)
        for(int j=0;j<s;j++)if(g[j]&&(j&t[i])==j)for(int k=0;k<s;k++)if(!(j&k))f[i][j]+=f[i-1][k];
    for(int i=0;i<s;i++)
        ans=(ans+f[m][i])%100000000;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Right (赞：0)

>>转移方程 dp[i][j]=sum（dp[i-1][k]）。

根据题意发现行的一种放法是最多由12个 0 或者 1 组成的，那么我们很容易想到用二进制，用二进制的一个数来表示一种放法。定义状态dp[i][j]，第 i 行状态为 j 的时候放牛的种数。j 的话我们转化成二进制，从低位到高位依次 1 表示放牛0表示没有放牛，就可以表示一行所有的情况。


状压dp

代码如下：

            
```cpp
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
int n,m;
const int mx=1<<13; 
int dp[20][mx];
int map[mx];
int s[mx];
int mod=100000000;
int ans;
bool pd(int x)
{
    return (x&(x<<1)); //left and right all can put cows
}
bool judge(int x, int y)
{
    return (map[x]&s[y]);  //Di Tu Fu He 
}
int main()
{
    int i,j,v,k;
    cin>>n>>m;
    int x;
    for (i=1; i<=n; ++i)
    {
        for (j=1; j<=m; ++j)
        {
            scanf("%d",&x);
            if (x==0)
            {
                map[i]+=(1<<(j-1));  
            }
        }
    }  //记录0的位置
    //-----------------------------------------------//
    k=0;
    for (i=0; i<(1<<m); ++i)
    {
        if (!pd(i))
        {
            s[++k]=i;
            //k++
        }
    }  //初始化所有可行状态
    //-------------------------------------------------//
    for (i=1; i<=k; ++i)
    {
        if (!judge(1,i))
        {
            dp[1][i]=1;  //表示在第1行状态为i时候可以放牛的种数  
        }
    }
    //-------------------------------------------------//
    for (i=2; i<=n; ++i) //从第2行开始dp
    {
        for (j=1; j<=k; ++j)     //枚举k种状态  k kinds of 可行状态
        {
            if (judge(i,j))
                continue;
            //判断第i行 假如按状态j放牛的话行不行。   cut!
            for (v=1; v<=k; ++v)   //枚举上一行可行状态
            {
                if (judge(i-1,v)) //i-1 is last line
                    continue;
                //剪枝 判断上一行与其状态是否满足  
                if (!(s[j]&s[v]))  //i-1 line and i line 不冲突
                    dp[i][j]+=dp[i-1][v];  
                    dp[i][j]%=mod; 
            }
            if (i==n)
            {
                ans+=dp[n][j];
                ans%=mod;
            }
        }        
    }
    if (n==1)
    {
        for (i=1; i<=k; ++i)
        {        
            ans+=dp[1][i];
        }
    }
    cout<<ans<<endl;  
}
>>分割线就是分块哦
```

---

## 作者：Memorize (赞：0)

根据题目分析n，m很小并且状态只有0 1 所以很容易看出是一道状态压缩dp

题目要求两个草地不相邻 所以就很容易联想到左右& 和前后& 最后f[i][j]表示第i行是j这个状态的方案数

则转移方程为f[i][j]=sigma(f[i-1][k])(当j 和 k不冲突)

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define mod 100000000
using namespace std;
int n,m;
int map[20][20],sta[20][200],sum[200];
long long f[20][200],ans=0;//表示第i行是j这个状态的总方案数 
void dfs(int line,int num,int put)
{
    if(put>m) return;
    sta[line][++sum[line]]=num;
    for(int i=put+2;i<=m;i++)
     if(map[line][m-i+1])
      dfs(line,num+(1<<(i-1)),i);//预处理每一行的可行状态
}
void pre_treat()
{
    memset(f,0,sizeof(f));
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;i++)
     dfs(i,0,-1);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++) scanf("%d",&map[i][j]);
    pre_treat(); 
    for(int i=1;i<=sum[1];i++) f[1][i]=1;
    for(int i=2;i<=n;i++)
     for(int j=1;j<=sum[i];j++)
      for(int k=1;k<=sum[i-1];k++)
       if(!(sta[i][j]&sta[i-1][k]))
        f[i][j]=(f[i][j]+f[i-1][k])%mod;
    for(int i=1;i<=sum[n];i++) ans=(ans+f[n][i])%mod;
    printf("%lld",ans%mod);     
    return 0;
}
```

---

