# Cycles

## 题目描述

构造一个无向图（没有自环），使这个无向图恰好有 $m$ 个三元环，输出这个无向图的 $01$ 矩阵。

$($无向图的顶点数不超过 $100,1 \leq m \leq 10^5)$

## 样例 #1

### 输入

```
1
```

### 输出

```
3
011
101
110
```

## 样例 #2

### 输入

```
10
```

### 输出

```
5
01111
10111
11011
11101
11110
```

# 题解

## 作者：Heartlessly (赞：5)

## Description

构造一个无向图（没有自环），使这个无向图恰好有 $m$ 个三元环，输出这个无向图的 $01$ 矩阵。

$($无向图的顶点数不超过 $100,1 \leq m \leq 10^5)$

## Solution

从 $n$ 个点的完全图中任意选出 $3$ 个点都能组成三元环，所以一共有 $C_n^3$ 个三元环。

我们可以先构造出一个尽可能大的完全图，满足 $C_n^3 \leq m$ 。

我们只需要再使这个无向图增加 $m - C_n^3$ 个三元环即可。

考虑新加一个点，这个点与完全图中 $x$ 个点连边。从这 $x$ 个点中任意选出 $2$ 个点都能与这个新加的点构成三元环，所以就会增加 $C_x^2$ 个三元环。

我们可以把 $m - C_n^3$ 拆分成多个 $C_x^2$ 的和。

举个例子，当 $m = 15$ 时，我们可以先构造一个 $5$ 个点的完全图，共有 $C_5^3 = 10$ 个三元环（如图）。

![VqLaS1.png](https://s2.ax1x.com/2019/06/18/VqLaS1.png)

这时我们还需要增加 $15 - 10 = 5$ 个三元环。

而 $4 = 3 + 1 + 1 = C_3^2 + 2C_2^2$，我们可以新加一个点 $6$，与 $1,2,3$ 连边，增加了 $3$ 个三元环。

![VqLNWR.png](https://s2.ax1x.com/2019/06/18/VqLNWR.png)

再加一个点 $7$，与 $1,2$ 连边，增加了 $1$ 个三元环。

![VqLdQx.png](https://s2.ax1x.com/2019/06/18/VqLdQx.png)

最后加一个点 $8$，与 $1,2$ 连边，增加了 $1$ 个三元环。

![VqLtY9.png](https://s2.ax1x.com/2019/06/18/VqLtY9.png)

这样一共就有 $15$ 个三元环了。

注意拆分时要从大到小枚举 $x$，且 $x$ 的最大值为 $n - 1$，最小值为 $2$ 。用这种构造方法，最后的点数不会超过 $100$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 100;
int n = 1, m, e[MAXN + 5][MAXN + 5];

inline int C(int n, int m) {//组合数，这道题只用到 m = 2 和 m = 3
    if (m == 2) return n * (n - 1) / 2;
    if (m == 3) return n * (n - 1) * (n - 2) / 6;
    return -1;
}

int main() {
    read(m);
    for (; C(n, 3) <= m; ++n);//构造一个尽可能大的完全图 
    --n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            e[i][j] = e[j][i] = 1;//完全图中点与点之间连无向边 
    m -= C(n, 3);//需要增加的三元环个数 
    for (int i = n - 1; i > 1; --i)//从大到小枚举 x 
        for (; m >= C(i, 2); m -= C(i, 2)) {//如果足够分解 
            ++n;//新建一个节点 
            for (int j = 1; j <= i; ++j) e[j][n] = e[n][j] = 1;
            //新节点连向 1 ~ i，共 i 个点，增加了 C(i,2) 个三元环 
        }
    write(n);
    putchar('\n');
    for (int i = 1; i <= n; ++i, putchar('\n'))
        for (int j = 1; j <= n; ++j)
            write(e[i][j]);
    return 0;
}
```



---

## 作者：hgoicjl (赞：3)

### 题意：
给定一个数$m[1,1e5]$，要求构造 $n[0,1e2]$个顶点，其中有$m$个三元环的图

### 算法：
**组合数  思维 构造**
### 解法：
假设有一个完全图，显然其中任意的三个点都可以构造一个三元环

所以对于一个$n$个顶点的完全图，有$C^3_n$个三元环

![完全图样例](https://cdn.luogu.com.cn/upload/pic/61880.png)

先构造一个完全图，满足$C^3_n≤m<C^3_{n+1}$

此时还需要添加$m-C^3_n$个三元环

以下图举例

![样例图](https://cdn.luogu.com.cn/upload/pic/61881.png)

三角形的顶点是新添加的顶点

底边上的五个点是已有的五个点，并且他们完全等价

因为底边上的点是完全图上的点，任意三点已构成了三元环

所以新添加的点对答案的贡献，就是图中含有顶点的个数，即$C^2_k$

所以新加顶点后的三元环个数即$C^3_n+C^2_{k_1}+C^2_{k_2}+......$

若满足$C^3_n+C^2_{k_1}+C^2_{k_2}+......=m$即是我们所求的答案

***

### code A
```
#include<bits/stdc++.h>
using namespace std;
bool map1[105][105];
int c1[105]/*C(3,n)*/,c2[105]/*C(2,n)*/,pnum=0,m;
int mian()
{
	c1[101]=0x3f3f3f3f,cin>>m;
	for(int i=2;i<=100;i++)
		c1[i]=i*(i-1)*(i-2)/6,c2[i]=i*(i-1)/2;
	for(int i=1;i<=100;i++)
		if(m<c1[i+1]&&c1[i]<=m)
			pnum=i,m-=c1[pnum];
	for(int i=1;i<=pnum;i++)
		for(int j=1;j<=pnum;j++)
			map1[i][j]=(i!=j)?1:0;
	for(int k=100;m!=0;)
		if(m>=c2[k]){
			m-=c2[k],pnum++;
			for(int i=1;i<=k;i++)
				map1[i][pnum]++,map1[pnum][i]++;}
		else k--;
	cout<<pnum<<endl;
	for(int i=1;i<=pnum;i++)
		for(int j=1;j<=pnum;j++)
			(j==pnum)?cout<<map1[i][j]<<endl:cout<<map1[i][j];
	return 0;
//压行狂魔 具体解释见code B
}
```
### code B
```
#include<bits/stdc++.h>
using namespace std;
bool map1[105][105];//储存边的信息
int c1[105]/*C(3,n)*/,c2[105]/*C(2,n)*/,pnum=0/*点的数量*/;
int mian()
{
	memset(map1,0,sizeof(map1));//初始化，可写可不写
	memset(map1,0,sizeof(c2));
	memset(map1,0,sizeof(c1));
	c1[101]=0x3f3f3f3f;
	int m;
	cin>>m;
	for(int i=3;i<=100;i++)//预处理C(3,n)
		c1[i]=i*(i-1)*(i-2)/6;
	for(int i=2;i<=100;i++)预处理C(2,n)
		c2[i]=i*(i-1)/2;
	for(int i=1;i<=100;i++)
		if(m<c1[i+1]&&c1[i]<=m)
			pnum=i;//寻找满足条件的最大完全图
	m-=c1[pnum];//求得还需添加的三元环数量
	for(int i=1;i<=pnum;i++)
		for(int j=1;j<=pnum;j++)
			if(i!=j)
				map1[i][j]++;//对完全图赋值
	for(int k=100;m!=0;)//与添加的点相连的点的数量由多到少递减
	{
		if(m>=c2[k])//如果需要添加的三元环多余添加三元环的数量即可添加
		{
			m-=c2[k];//还需添加的三元环
			pnum++;//多增加一个与k个点相连的点
			for(int i=1;i<=k;i++)
			{
				map1[i][pnum]++;
				map1[pnum][i]++;//对边赋值
			}
		}
		else
			k--;
	}
	cout<<pnum<<endl;//按格式输出
	for(int i=1;i<=pnum;i++)
	{
		for(int j=1;j<=pnum;j++)
			cout<<map1[i][j];
		cout<<endl;
	}
	return 0;
}
```
***
### 你说抄题解的人会不会WA掉呢（滑稽）

---

## 作者：lukelin (赞：3)

### 题解
刚看到这道题的时候，我的第一反应是构造一些互相独立的完全图，一个大小为k的完全图对答案的贡献是$C_k^3$，然后交了一遍直接WA。  
仔细一想，其实还有另外一种构造方法，先构造一个所有点连到$1$，然后从点$3$开始加边，如果当前节点已经连接了$cnt$条边(由于是菊花图，所以刚开始边数一定为$1$)，那么显然连这条边对答案的贡献就是$cnt$，然后能连就连即可。
### 代码
```cpp
#include <cstdio>
#include <algorithm>

int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int map[105][105];

int main(){
    int k = read();
    map[1][2] = map[2][1] = 1; int cnt = 0;
    for (int i = 3; i <= 100; ++i){
        map[1][i] = map[i][1] = 1;
        cnt = 1;
        for (int j = 2; j < i; ++j)
            if (k >= cnt)
                map[i][j] = map[j][i] = 1, k -= cnt, ++cnt;
    }
    puts("100");
    for (int i = 1; i <= 100; ++i){
        for (int j = 1; j <= 100; ++j)
            putchar('0' + map[i][j]);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：BFSDFS123 (赞：2)

兔群的跳题 Bot 跳到了这道题。

题目要求构造一个无向图使图中有 $m$ 个三元环。

不难发现，对于一个 $n$ 个点的完全图，任意三个点都在一个三元环上，故有 $\operatorname C_{n}^3$ 个三元环。

对于一个完全图，每次加入一个节点。因为原完全图上任意两点是相连的，设其与完全图内连边的数量为 $k$，则会多出 $\operatorname C_{k}^2$ 个三元环。

我们只需要求出最大的 $n$ 使 $\operatorname C_{n}^3 \le m$，并枚举 $k$，使 $\operatorname C_{n}^3+\sum\operatorname C_{k}^2=m$ 即可。

实现十分简单。

现在有一个问题，为什么我们能保证这样能构造出一个正确的矩阵呢？

对于 $k=1\to n$，我们有序列 $A=\operatorname C_{k}^2=0,1,3,6,\dots, \dfrac{n\times (n-1)}{2}$。此时不难注意到，对于任意一个需要补充的三元环的数量，我们至少都可以通过若干个 $k=2$ 补上，显然我们可以用更少的 $k=3$ 来替换某些 $k=2$，用某些 $k=4$ 来替换 $k=3$ 和 $k=2$，这样，在范围内总能被我们找出正确的答案。

同时，我们有 $1\le m \le 10^5$，而 $\operatorname C_{100}^3=161700 > 10^5$，所以肯定有解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eps 1e-8
const int inf=0x3f3f3f3f;
const int Maxn=110;
int Lian[Maxn][Maxn];
int C(int x,int y)
{
	if(y==3)
	{
		return x*(x-1)*(x-2)/6;
	}
	if(y==2)
	{
		return x*(x-1)/2;
	}
}
int main()
{
	int m;
	scanf("%d",&m);
	int now=0;
	for(int i=1;i<=100;i++)
	{
		int Nodes=C(i,3);
		if(Nodes<=m)
		{
			now=i;
		}else{
			break;
		}
	}
	for(int i=1;i<=now;i++)
	{
		for(int j=1;j<=now;j++)
		{
			if(i==j) continue;
			Lian[i][j]=Lian[j][i]=1;
		}
	}
	m-=C(now,3);
	int Nd=now;
	for(int i=now;i>=2;i--)
	{
		while(C(i,2)<=m)
		{
			m-=C(i,2);
			Nd++;
			for(int j=1;j<=i;j++)
			{
				Lian[j][Nd]=Lian[Nd][j]=1;
			}
		}
	}
	printf("%d\n",Nd);
	for(int i=1;i<=Nd;i++)
	{
		for(int j=1;j<=Nd;j++)
		{
			printf("%d",Lian[i][j]);
		}
		putchar('\n');
	}

	return 0;
}
```

---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF232A)

## 思路
绘制一张恰好包含 $k$ 个三元环，总顶点数不超过 $100$ 的无向图。定义三元环是一个由三个不同顶点 $a,b$ 和 $c$，每对顶点之间都通过一条无向边相连。

看了一眼是图论，我们都知道一个完全图会有 $\operatorname C_{n}^3$ 个三元环，因为他是一个图上的三个点构成的环。我们还要尽可能多的环，可以想象成还要 $\operatorname C_{a}^2$ 个环，所以我们只需要枚举一下 $a$ 就可以了。
## code
```cpp
while(b<=k)
	{
		n++;
		b=n*(n-1)*(n-2)/6;
	}
	n--;
	for(i=1;i<=n;i++)for(j=1;j<=i;j++)a[i][j]=a[j][i]=1;
	k-=n*(n-1)*(n-2)/6;
	for(i=n-1;i>1;i--)
	{
		while(k>=i*(i-1)/2)
		{
			n++;
			for(j=1;j<=i;j++)a[j][n]=a[n][j]=1;
			k-=i*(i-1)/2;
		}
	}
```

---

## 作者：lkjzyd20 (赞：0)

构造菊花图。

先构造所有点连向 $1$，如果当前点已经连接了 $x$ 条边，那么对答案的贡献就是 $x$，再将这两个点链接。
```cpp
#include<bits/stdc++.h>
#define R(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
int n,k,p[99][99];
main(){
    cin>>k;
    for(;k;++n)
        R(i,0,min(k,n-1))
            p[n][i]=p[i][n]=1,k-=i;
    cout<<n<<'\n';
    R(i,0,n-1){
        R(j,0,n-1)cout<<p[i][j];
        cout<<'\n';
    }
}
```

---

## 作者：Elma_ (赞：0)

突然意识到好像并不是所有题解的构造方法都是一样的，这里先给出我的构造方法：

一个朴素的想法是让每个点对答案的贡献都尽量多，我们直接找到最大的 $p$ 使得 $C_p^3 \leq k$，造一个 $p$ 个点的完全图，这样还剩下 $k - C_p^3$ 个三元环没造。考虑新建一个点 $u$，让它和完全图中的 $q(q \leq p)$ 个点连边，这样对答案的贡献是 $C_q^2$。那我们要干的事就是把 $k-C_p^3$ 拆成较少的一些 $C_q^2$ 之和，从大到小枚举 $q$，能拆就拆就行了。

不知道为啥其他题解要么不写证明要么就是在谜语，这里简单证一下这样构造的正确性。


回顾构造的过程，我们找到了最大的 $p$ 使得 $C_p^3 \leq k < C_{p+1}^3$（显然有 $p \leq 85$），这意味着 $k - C_p^3 < C_{p+1}^3 - C_p^3 = C_p^2$，接下来要做的事情是将 $k - C_p^3$ 拆分成较少的一些 $C_q^2$ 之和（其中 $q \leq p$）。

令 $d = k - C_p^3$，对于最大的 $q$ 使得 $C_q^2 \leq d < C_{q+1}^2$，有 $d - C_q^2 < q$。由此我们可以看出，在这种拆分方法下 $d$ 减少的速度其实是很快的，手模一下会发现这个过程最多只会进行 $5$ 次。因此总点数不会超过 $85 + 5= 90$，即正确性得证。

---

## 作者：cz666 (赞：0)

## 题目简述

给你一个整数 $M$ ，让你用不多于 $100$ 个点来建立无向边图使这个图的三元环个数等于 $M$ 。

## 具体思路

我们先对样例输出的邻接矩阵从下往上分析，发现每往上一行，那一行都选满能的到对答案的贡献如下表：

$0,1,3,6,10,15,21,28,36...$

显然这个数列就是 $1$ ~ $N-1$ 的和，正确性很显然。

然后对每一行从左往右填满 $1$ 对本行答案的贡献发现也和上面的表的贡献是一样的，那么我们 $1$ ~ $99$ 只要做一次前缀和，把每一个格子加边的能对该行答案贡献的答案记录在另一个对应的邻接矩阵 $P$ 中，再对前缀和数组做一次前缀和来得出最多能填满几行，最后对多余的那些没有构造的三元环在填满的矩阵上面从左往右占一格减去哪一个对答案的贡献就可以了。

注意的是这是一个无向图的构造题，所以一次要在邻接矩阵中添两个方向的边。

答案就是邻接矩阵 $G$ 。

## AC代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define dd c=getchar()
inline int read(){int s=0,w=1;char c;while (dd,c>'9' || c<'0') if (c=='-') w=-1;while (c>='0' && c<='9') s=s*10+c-'0',dd;return s*w;}
inline void write(int x){if (x<0) putchar('-'),x=-x;if (x>=10) write(x/10);putchar(x%10|'0');}
inline void wln(int x){write(x);puts("");}
inline void wlk(int x){write(x);printf(" ");}
#undef dd
int g[103][103],p[103][103],sum[103];
signed main(){
	freopen("cycles.in","r",stdin);freopen("cycles.out","w",stdout);
	int m=read(),pos;puts("100");
	for (int i=1;i<=99;i++) sum[i]=sum[i-1]+i;//第一次的前缀和
	for (int i=1;i<=100;i++)
	 for (int j=i+1;j<=100;j++) p[i][j]=j-i-1;//放到储存答案贡献的矩阵中
	for (int i=1;i<=99;i++) sum[i]+=sum[i-1];//第二次做前缀和的前缀和
	for (int i=1;i<=99;i++) if (sum[i]<=m) pos=i;
	m-=sum[pos];//找到最多摆满几行，并算出还有几个三元环没有构造
	for (int i=99-pos;i<=99;i++)
	 for (int j=i+1;j<=100;j++) g[i][j]=g[j][i]=1;//能填满的矩阵直接填满
	int x=98-pos,y=x+1;
	while(m){
		if (p[x][y]<=m) g[x][y]=g[y][x]=1,m-=p[x][y];
		else x--,y=x;
		y++;
	}//从能填满的矩阵开始向上一行一行找过去，这一行最多能填多少就填多少，不能填就转上一行，以此类推，直到全部三元环全部被构造
	for (int i=1;i<=100;i++,cout<<endl)
	 for (int j=1;j<=100;j++) cout<<g[i][j];//输出答案
	return 0;
}
```

### 完结撒花QwQ

---

## 作者：两年打铁 (赞：0)

## 题意

给定一个数M，让你输出一个以邻接矩阵形式的图 ，使得图里的三元环的个数等于M.

# 分析

首先我们知道，完全图任意两个点都能互相到达，那么图里的三元环的个数就是
$C^{3}_{N} $
那么我们先预处理出组合数，然后先找到最大的$C^{3}_{N} $减去个数。

接下来我们就开始一个个加点，对于任意一个加的点，如果这个点与j个完全图里的点相连，那么这个加的点就会产生$C^{2}_{j}$的贡献，那么我们就可以不断最大的符合条件的j，并减去。

## 复杂度
由于第二列的组合数在100左右时上下差值还是100,也就是说我们找的次数不会超过10次，复杂度是常数级别。

```
#include<bits/stdc++.h>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
#define int long long 
using namespace std;
const int L=1e6+233;
char *p1,*p2,ppp[L];
inline char gc()
{
	if(p1==p2)
	{
		p2=(p1=ppp)+fread(ppp,1,L,stdin);
	}
	return *p1++;
}
inline void read(int &x)
{
    x=0;int pd=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    int s=0;int tmp=x;if(tmp==0){putchar('0');return;}
    if(tmp<0)tmp=-tmp,putchar('-');
    char ggg[20];while(tmp>0){ggg[s++]=tmp%10+'0',tmp/=10;}
    while(s>0)putchar(ggg[--s]);
}

int c[1010][1010];
int now,n;

int cnt,mp[110][110];

signed main()
{
	for(register int i=0;i<=100;++i)
	{
		c[i][0]=1;
		for(register int j=1;j<=3;++j)
		{
			c[i][j]=c[i-1][j]+c[i-1][j-1];
		}
	}
	read(n);
	for(register int i=1;i<=100;++i)
	{
		if(c[i][3]>n)
		{
			now=i-1;
			break;
		}
	}
	n-=c[now][3];
	cnt=now+1;
	for(register int i=1;i<=now;++i)
	{
		for(register int j=1;j<=now;++j)
		{
			if(i!=j)
			{
				mp[i][j]=1;
			}
		}
	}
	if(!n)
	{
		cout<<now<<endl;
		for(register int i=1;i<=now;++i)
		{
			for(register int j=1;j<=now;++j)
			{
				write(mp[i][j]);
			}
			puts("");
		}
		return 0; 
	}
	while(1)
	{
		for(register int i=1;i<=100;++i)
		{
			if(c[i][2]>n)
			{
				now=i-1;
				break;
			}
		}
		n-=c[now][2];
		for(register int i=1;i<=now;++i)
		{
			mp[cnt][i]=mp[i][cnt]=1;
		}
		if(!n)
		{
			break;
		}
		else 
		{
			++cnt;
		}
	}
	cout<<cnt<<endl;
	for(register int i=1;i<=cnt;++i)
	{
		for(register int j=1;j<=cnt;++j)
		{
			write(mp[i][j]);
		}
		puts("");
	}
	return 0;
}
```


---

