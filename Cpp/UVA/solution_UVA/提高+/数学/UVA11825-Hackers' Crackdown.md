# Hackers' Crackdown

## 题目描述

假如你是一个黑客，侵入了一个有着 $n$ 台计算机（编号为$0,1,2,3....n-1$）的网络。一共有 $n$ 种服务，每台计算机都运行着所有服务。对于每台计算机，你都可以选择一项服务，终止这台计算机和所有与它相邻计算机的该项服务（如果其中一些服务已经停止，那他们继续保持停止状态）。你的目标是让尽量多的服务完全瘫痪(即：没有任何计算及运行着该服务)

## 样例 #1

### 输入

```
3
2 1 2
2 0 2
2 0 1
4
1 1
1 0
1 3
1 2
0```

### 输出

```
Case 1: 3
Case 2: 2```

# 题解

## 作者：Mathic (赞：7)

【先来一波~~精致的~~分析】

本题的数学模型是：把$\color{red}\mathcal{n}$个集合$\color{red}\mathcal{P1,P2,...,Pn}$分成尽量多组，使得每组中所以集合的并集等于全集。这里集合$\color{red}\mathcal{Pi}$就是计算机$\color{red}\mathcal{i}$及其相邻计算机的集合，每组对应于题目中的一项服务。

注意到$\color{red}\mathcal{n}$很小，可以套用《算法竞赛》里面提到的二进制法表示这些集合，即在代码中，

每个集合$\color{red}\mathcal{Pi}$实际上是一个非负整数。输入部分代码如下：

```
for(int i=0;i<n;i++)
{
	int m,x;
    scanf("%d",&m);
    P[i]=1<<i;
    while(m--)
    {
    	scanf("%d",&x);
        P[i]|=(1<<x);
    }
}
```
为了方便，窝萌用$\color{red}\mathcal{cover(S)}$表示若干$\color{red}\mathcal{Pi}$的并集（二进制表示），即这些$\color{red}\mathcal{Pi}$在数值上的“按位或”。
```
for{int S=0;S<(1<<n);S++)
{
	cover[S]=0;
    for(int i=0;i<n;i++)
    if(S & (1<<i)) cover[S]=P[i];
}
```
不难想到这样的动态规划：用$\color{red}\mathcal{f(S)}$表示子集S最多可以分成多少组，则

$\color{darkblue}\mathcal{f(S)=max(f(S-S0)|S0}$
$\color{darkblue}\text{是S的子集，}$
$\color{darkblue}\mathcal{cover[So]}$
$\color{darkblue}\text{等于全集)}$
$\color{darkblue}\text{+1}$



------------
$\color{darkred}\text{（划重点！！）}$
$\color{darkred}\text{这里有一个重要的技巧：枚举}$
$\color{red}\mathcal{S}$
$\color{darkred}\text{的子集}$
$\color{red}\mathcal{S0}$。



------------



详见下面代码：
```
f[0]=0;
int All=(1<<n)-1;
for(int S=1;S<(1<<n);S++
{
	f[S]=0;
    for(int S0=S;S0;S0=(S0-1)&S)
    if(cover[S0]==All f[S]=max(f[S],f[S^S0]+1);
}
printf("Case %d: %d\n",++kase,f[ALl]);
```

如何分析上述算法的时间复杂度呢$qwq$？它等于全集$\color{red}\mathcal{(1,2,3,...,n)}$的所有子集的子集个数之和，也可以令
$\color{red}\mathcal{c(S)}$表示集S的子集的个数（它等于
$\color{red}\text{2}$
$\color{red}\mathcal{^|}$
$\color{red}\mathcal{^s}$
$\color{red}\mathcal{^|}$)，则本题的时间复杂度为


$\color{red}\mathcal{sum(c(S)|S0}$
$\color{red}\text{是(1,2,3,...,n)的子集）}$。

注意到元素个数相同的集合，其子集个数也相同，窝萌可以按照元素个数“合并同类元素项”。元素个数为$k$的集合有
$\color{red}\mathcal{C(n,k)}$个，其中每个集合有
$\color{red}\text{2}$
$\color{red}\mathcal{^k}$个子集（高一
$\color{red}\mathcal{New}$ 
$\color{red}\mathcal{knowledge}$),

因此本题的时间复杂度为
$\color{red}\mathcal{sum(C(n,k)}$
$\color{red}\text{2}$
$\color{red}\mathcal{^k}$
$\color{red}\mathcal{=}$
$\color{red}\text{(2+1)}$
$\color{red}\mathcal{^n}$
$\color{red}\mathcal{=}$
$\color{red}\text{3}$
$\color{red}\mathcal{^n}$其中第一个等号得到的用到了二项式定理（不过是反着用的$QwQ$）

本题比较抽象，大家花点时间仔细想明白哦~~

---

## 作者：封禁用户 (赞：4)

一道不错的状压DP，但是评分太高了。看过《入门经典》的同学肯定都会书上讲的枚举子集的$O(3^{n})$算法，但我太弱了，写这题时把枚举子集的复杂度算错了，以为会超时，~~而且我也不会枚举子集的算法~~，于是瞎搞出了一个理论最坏复杂度为$O(2^{n}C_{n}^{n/2})$~~其实是O(玄学)~~的算法~

使用的数组大致和书上的一样，$group[i]$(以下称为"组")表示$i,i \in [0,n)$号电脑和它的相邻电脑组成的集合,$dp[S]$表示当前选择的所有$group$组成的集合$S$能使多少种服务瘫痪。我的方法不用cover数组，临时算就好了。

首先，我想到，为了避免冗余，$dp$值应该只由上一个阶段转移过来，即枚举的其中一个子集的$dp$值应为$1$。其实就是书上的状态转移方程：$dp[S]=max\{dp[S-S_{0}]+1,S_{0} \subset S,cover[S_{0}]==true\}$,其中$cover[S_{0}]$表示$S_{0}$包含的组是否能覆盖所有电脑。如果能覆盖，显然可以让$S_{0}$中的组停止同一种服务，$dp$值就等于把$S_{0}$中元素拿掉后的$dp$值$+1$。

不过，我们其实可以有一种贪心的想法：我们取出所有满足以下条件的组的集合(以下称为"单元集")：它们的$dp$值为$1$($cover$值为$true$)，且它们的真子集的$dp$值均为$0$。我们可以只用单元集作为dp方程中的$S_{0}$来转移，因为这样我们可以留更多的元素给$S-S_{0}$，答案肯定不劣。于是，状态转移时我们可以枚举单元集，判断它们是不是$S$的子集。

那么，单元集的个数(以下记为$U$)最多是多少？由于单元集互不为子集，只有当所有单元集元素个数相同时$U$才可能最大。因为，假设一开始所有单元集元素个数相同(均为$k$)，并且所有元素个数都是$k$的集合都是单元集，增加1个元素更多的单元集，就会有至少1个原来的单元集成为它的子集，于是又要去掉一个，个数不会更多。所以，$U_{max}=max\{C_{n}^{k},k \in [1,n]\}$，显然当$k=n/2$时取最大。枚举每个$S$时都要枚举**整数意义下小于$S$的**每个单元集(这样才有可能是$S$的子集)，于是最坏复杂度~~好像~~就是$O(2^{n}C_{n}^{n/2})$。

虽然复杂度偏大，但跑起来只要110ms，比枚举子集快很多，直接rank1了！~~可能我复杂度又算错了~~

## 代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <class T>
inline void read(T &x)//读入优化(没啥用)
{
    static char c;
    x=0;
    for(c=getchar();isspace(c);c=getchar());
    static bool sign;
    sign=0;
    if (c=='-') sign=!sign,c=getchar();
    for(;isdigit(c);x=x*10+c-'0',c=getchar());
    if (sign) x=-x;
    return;
}

const int MAXN=17;
int group[MAXN+5];//每台电脑和它的相邻电脑组成的集合
int dp[(1<<MAXN)+5];//不同group组成集合对应的答案
int unit[12875];//单元集
//C(16,8)+5=12875

int main()
{
    int CaseCnt=0;
    int n;
    while (cin>>n&&n)
    {
        for (int i=0;i<n;i++)
        {
            group[i]=1<<i;
            int m,nb;
            read(m);
            for (int j=1;j<=m;j++)
            {
                read(nb);
                group[i]|=1<<nb;
            }
        }
        memset(dp,0,sizeof(dp));
        int num=0;//单位集合的数量
        for (int S=1;S<1<<n;S++)//枚举groups
        {
            for (int i=1;i<=num;i++)
            {
                if ((S&unit[i])==unit[i])//unit[i]是S的子集
                {
                	dp[S]=max(dp[S],1+dp[S^unit[i]]);
                    //S^unit[i]==S-unit[i]
                }
            }
            if (!dp[S])//
            {
                int c=0;//这些groups覆盖到的电脑
                for (int i=0;i<n;i++)
                {
                    if ((S>>i)&1) c|=group[i];
                }
                if (c==(1<<n)-1)//是单元集
                {
                	dp[S]=1;
                	unit[++num]=S;
                }
            }
        }
        cout<<"Case "<<++CaseCnt<<": "<<dp[(1<<n)-1]<<endl;
    }
    return 0;
}
```

---

## 作者：RPChe_ (赞：3)

# 模拟退火
没错，我可以很负责的告诉你，模拟退火是目前本题的最优解。
[我的提交记录](https://www.luogu.com.cn/record/36045150)

题面已经很清晰了，我们的目标是将$n$个集合分成尽量多组，使得每一组里面所有集合的并集等于全集。

首先我们可以用二进制方法来表示每个集合，方便存储也方便判断。然后，我们可以把这$n$个集合抽象成一个序列，并且按序列的顺序对这个集合进行分组，使得分组以后的结果满足上面的条件。这样此题就转化为了求一个分组结果最大的序列，我们用模拟退火求这个序列就可以了。[不会模拟退火？](https://www.luogu.com.cn/blog/Darth-Che/mu-ni-tui-huo-xue-xi-bi-ji)

时间复杂度$O(玄学)$，如果想看更清晰的过程，代码如下——

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<stdlib.h>
#include<ctime>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
#define maxn 17
#define delta 0.996//退火系数
using namespace std;

inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}

int n,put[maxn],ans,p[maxn];

int calculate(int x[]) {
	int res=0,t=0;
	rep(i,0,n-1) {
		t|=put[x[i]];
		if(t==(1<<n)-1) res++,t=0;
	}
	return res;
}//计算序列x的分组结果

void pretreat() {
	rep(i,0,n-1) p[i]=i;
	ans=calculate(p);
}//预处理出初值

void simulate_anneal() {
	int a[maxn];
	rep(i,0,n-1) a[i]=p[i];
	double t=3000;
	while(t>1e-15) {
		int X=rand()%n;
		int Y=rand()%n;
		swap(a[X],a[Y]);
		int now=calculate(a);
		double Delta=ans-now;
		if(Delta<0) {
			ans=now;
			rep(i,0,n-1) p[i]=a[i];
		} else if(exp(-Delta/t)*RAND_MAX<rand()) swap(a[X],a[Y]);
		t*=delta;
	}
}//模拟退火

void work() {
	pretreat();
	rep(i,1,3) simulate_anneal();
}//跑三次模拟退火

int main() {
	srand(time(0));//随机数种子
	int T=0;
	while(n=read()) {
		if(!n) return 0;
		rep(i,0,n-1) {
			int t=read();
			put[i]=1<<i;
			rep(j,1,t) {
				int a=read();
				put[i]+=1<<a;
			}
		}//边读入边用二进制表示集合
		work();
		cout<<"Case "<<++T<<": "<<ans<<'\n';
	}
	return 0;
}
```

~~然而窝写的状压dpTLE了QAQ~~

---

## 作者：Future_Fate (赞：3)

**自己通过的第一道紫题%%%**

首先考虑本题的数学模型：

设集合pi为计算机i以及其相邻计算机的集合，设全集为n(即所有服务器的全集)

**我们把n台电脑分组，并且每一组电脑及和它们直接相邻的电脑都包含所有的电脑，这样的组数就是可以导致多少种服务瘫痪。所以我们找尽可能多的组数。**

把n个集合s1,s2……sn分成尽量多组，使得每组中的所有集合的并集等于全集，每组对应题目中的一项服务

那么我们就用二进制来进行状态压缩

用cover[]数组存储每一种分组包含的电脑的个数

用dp[s]表示子集s最多可以分成多少组，我们可以得到：

dp[s]=max(,dp[s],f[All-a]+1) 其中All全集

**代码并不长**

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 16;
int s[maxn],cover[1<<maxn],dp[1<<maxn],n,m,a,ca=1;
int main(){	
  while(cin>>n&&n){
    for(int i=0;i<n;i++){
	 cin>>m,s[i]=1<<i;
      for(int j=0;j<m;j++)
       cin>>a,s[i] |=(1<<a);}      
    memset(cover,0,sizeof(cover));
     for(int i=0;i<(1<<n);i++) 
	  for(int j=0;j<n;j++) 
	   if(i&(1<<j)) cover[i] |=s[j];         
    memset(dp,0,sizeof(dp));
     for(int i=0;i<(1<<n);i++)
      for(int s0=i;s0;s0=(s0-1)&i)
       if(cover[s0]==(1<<n)-1) dp[i]=max(dp[i],dp[s0^i]+1);      
    cout<<"Case "<<ca++<<": "<<dp[(1<<n)-1]<<endl;
    }
    return 0;
}

```

---

## 作者：一个简单名字 (赞：2)


## soution

令 $f[s]$ 表示 $s$ 状态(用二进制数来表示)能完全瘫痪服务的数量，状态转移方程如下，即若当前枚举的 $s$ 状态是全集，此时 $s$ 就是一种方案，则 $f[S]$ 就可以从 $f[S-s]+1$ 转移过来。 

## AC Code：

```c++
#include <bits/stdc++.h>
#define maxn 1<<16
using namespace std;
int n,m,max_i;
int f[maxn],p[20],c[maxn];
void cinn(int i,int x)//处理p[i],p[i]为i能连接到的点的并集，内部存一个二进制数
{
	p[i]|=(1<<x);
}
void clear()  //每次清空所用的数组
{
	memset(p,0,sizeof(p));
	memset(c,0,sizeof(c));
	memset(f,0,sizeof(f));
}
int main()
{
std::ios::sync_with_stdio(0);
cin.tie(0);
cin>>n;
while(n)
{
	clear();
	int MAX=(1<<n)-1;
	for(int i=0;i<n;i++)
	{
		p[i]=(1<<i);//初始化
		cin>>m;
		for(int j=1;j<=m;j++)
		{
			int x;
			cin>>x;
			cinn(i,x);//处理p[i]
		}
	}
	for(int i=0;i<=MAX;i++)
		for(int j=0;j<n;j++)
			if(i&(1<<j))c[i]|=p[j];//i状态中所包含的所有p的并集，这里i是一个二进制数
	for(int S=0;S<=MAX;S++)	
		for(int s=S;s;s=S&(s-1))
			if(c[s]==MAX)f[S]=max(f[S],f[S-s]+1);
	cout<<"Case "<<++max_i<<": "<<f[MAX]<<endl;
	cin>>n;
}
return 0;
}
```



---

## 作者：RoRoyyy (赞：1)

# 状压dp

我们并不关心关闭的服务的顺序， 所以这题首先需要把题目抽象一下， 即有$n$个集合， 每个集合代表了一个点联通的所有点， 而我们就是要求把这些集合划分成尽可能多的组， 使每一组能包含所有的点。每有一个组就代表能形成一个服务暂停。

所以我们首先考虑与预处理对于所有集合，我们先枚举集合编号的子集， 也就是选那些集合来组成一个组，和构成这个组都包含了那些点。

然后我们考虑$dp$，因为要构成一个组， 必定这个组内所有点都出现过， 所以考虑从上一个没有该组的状态转移，不妨设当前要考虑的状态为$S$， 要加入的组是$s$, 那么上一个状态是{$S-s$}, 而且必须满足$s$包含了全部的点。

这里我们发现利用二进制数储存一个组很方便， 所以我们的$S$和$s$都用二进制数表示就行了。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 20;
int bit[N], cover[1<<N], dp[1<<N];
int main() {
    int n, Kase = 0;
    while(scanf("%d", &n) != EOF && n) {
        Kase++;
        memset(bit, 0, sizeof(bit));
        memset(cover, 0, sizeof(cover));
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n; i++) {
            int m, x;
            scanf("%d", &m);
            bit[i] = 1 << i;//选自己
            while(m--) scanf("%d", &x), bit[i] = bit[i] | (1 << x);//计算所有的集合
        }
        for(int i = 0; i < (1 << n); i++) {//枚举选那些集合
            cover[i] = 0;
            for(int j = 0; j < n; j++) {//计算选i表示的所有集合的并集
                if(i & (1 << j)) cover[i] |= bit[j];
            }
        }
        int ALL = (1 << n) - 1;
        //dp[i] = dp[i - {x}] + 1 if(x == ALL)
        for(int i = 1; i < (1 << n); i++) {//枚举cover
            dp[i] = 0;
            for(int j = i; j; j = (j - 1) & i) {//枚举cover的子集 就是从哪个状态转移而来
                if(cover[j] == ALL) dp[i] = max(dp[i], dp[i ^ j] + 1);
                //如果是j这个二进制数表示的所有集合并起来为全集， 那么就有可能单独成为一组（即hack一项服务）
            }
        }
        printf("Case %d: %d\n", Kase, dp[ALL]);
    }
    return 0;
}
```


---

## 作者：Leianha (赞：1)

## 状压DP

首先感谢lrj的透彻讲解.

我们要使一项服务瘫痪，就必须选择一些计算机，使它们与他们所相连的计算机是所有的计算机，即：我们将每一个计算机本身及其相连的计算机看成一个集合$P_i$，我们要分成尽量多的集合，使每一个集合里$Pi∪...∪Pj$为全集。

我们又发现n的值比较小，因此我们可以考虑一下状压，$P_i$的每一位表示$i$号计算机的联通情况，$C_i$(这是数组，不是组合数)表示我们选择该二进制位下所选择的计算机的并集，$f(C_i)$表示在二进制下$C_i$可以分成的最大答案。

那么我们就要枚举全集子集的子集，对于子集，我们循环就行了，对于子集的子集，我们这样写就行了（~~虽然我也不知道为什么~~）学长说记住就行了
```cpp
for(int S=0;S<=maxn;++S)//全集的子集 
for(int s0=S;s0;s0=(s0-1)&S)//全集的子集的子集
```
关于这样的时间复杂度，我们知道一个大小为$n$ 的集合的子集的个数是$2^n=\sum_{k=0}^{n}C_{n}^{k}$（这里是组合数）,那么一个集合的子集的子集的个数就是$\sum_{k=0}^{n} C_{n}^{k}2^k$,根据二项式定理$(a+b)^k=\sum_{k=0}^{n}C_n^k a^kb^{n-k}$,我们逆用后就能得到原式为$(2+1)^n=3^n$,所以时间复杂度为$O(3^n)$~~O(能过)~~

剩下的就是一个简单的DP啦

另外用位运算也可以优化一下常数。

最后献上我~~丑陋~~的代码。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m,x,maxn,my_case;
int p[21],c[1<<18],f[1<<18];
int main()
{
	while(scanf("%d",&n)&&n)
	{
		maxn=(1<<n)-1;
		memset(c,0,sizeof(c));memset(f,0,sizeof(f));
		for(int i=0;i<n;++i)
		{
			p[i]=(1<<i);scanf("%d",&m);
			while(m--){scanf("%d",&x);p[i]|=(1<<x);}
		}
		
		for(int S=0;S<=maxn;++S)
			for(int i=0;i<n;++i) if(S&(1<<i))c[S]|=p[i];
		
		for(int S=0;S<=maxn;++S)//全集的子集 
			for(int s0=S;s0;s0=(s0-1)&S)//全集的子集的子集 
			if(c[s0]==maxn)f[S]=max(f[S],f[S-s0]+1);
		
		printf("Case %d: %d\n",++my_case,f[maxn]);
	}
	return 0;
}
```


---

## 作者：Plus_Ultra (赞：0)

一. $题目大意$:

把$n$个集合 $P1，P2, ... , Pn$ 分成尽量多组，使得每组的并集等于全集 $ {1,...,n} $.

二. 做法:

令$cover(S)$表示若干Pi的集合S中所有Pi的并集。

$f(S)$表示 $S$最多能分成多少组.




$f(S)$ = $max$ (${ f(S-S0) }) + 1$.$S0$是$S$的子集，$cover[S0]$ $=$ $全集$

枚举$S$的子集$S0$？

   $for$( $int$ $S0 = S;$ $S0;$ $S0 =$ $(S0 - 1)$ & $S$).

三. 代码:

```
#include<iostream>

using namespace std;

int n,m,F[1<<16],cover[1<<16],p[17],K;

int main()
{
	while(cin>>n)
	{
		if(n==0) return 0;
		for(int i=0,x;i<n;i++)
		{
			cin>>m;
			p[i]=1<<i;
			for(int j=1;j<=m;j++)
			{
				cin>>x;
				p[i]|=(1<<x);
			}	
		}	
		int All=(1<<n)-1;
		for(int S=0;S<=All;S++)
		{
			cover[S]=0;
			for(int i=0;i<n;i++)
			 	if(S&(1<<i)) cover[S]|=p[i]; 
		}
		for(int S=0;S<=All;S++)
		{
			F[S]=0;
			for(int s=S;s;s=(s-1)&S)
				if(cover[s]==All) F[S]=max(F[S],F[S^s]+1);
		}
		cout<<"Case "<<++K<<": "<<F[All]<<endl;
	} 
}
```



---

