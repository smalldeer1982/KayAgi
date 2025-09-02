# Monster Invaders

## 题目描述

这是一个 RPG 枪战游戏。

有 $n$ 个关卡，每一个关卡都有 $a_i$ 个生命值为 $1$ 的小怪，$1$ 个生命值为 $2$ 的 boss。

有三种武器：
+ 手枪，可以对一个怪物造成 $1$ 点伤害，每次使用前需要 $r_{1}$ 秒装弹。
+    激光枪，可以对目前关卡所有怪物造成 $1$ 点伤害，每次使用前需要 $r_{2}$ 秒装弹。
+    AWP（一种狙击枪），可以直接杀死任意怪物，每次使用前需要 $r_{3}$ 秒装弹。

由于游戏 $feature$，用手枪或 AWP 攻击 boss 前必须先杀死 boss 所在关卡的所有小怪。如果攻击 boss 但此次攻击并没有杀死 boss，必须移动到该关卡的相邻关卡。

除此之外，可以在任意时间移动到所在关卡的相邻关卡，每一次移动需要 $d$ 秒，此时什么都不能做。

从第一关开始游戏，游戏目标是击杀所有 boss，求完成游戏的最短时间。
第二行 $n$ 个正整数 $a_1,a_2,\dots,a_n$，表示每一关的小怪数量。

## 说明/提示

- 对于 $100\%$ 的数据，$2\leq n\leq 10^6,1\leq r1\leq r2\leq r3\leq 10^9,1\leq d\leq 10^9,1\leq a_i\leq 10^6$
- 不要求在第 $n$ 个关卡结束游戏。
- 如果移动前该关卡里有没有杀死的敌人，回到这个关卡时敌人的状态不会发生变化。

## 样例 #1

### 输入

```
4 1 3 4 3
3 2 5 1```

### 输出

```
34```

## 样例 #2

### 输入

```
4 2 4 4 1
4 5 1 2```

### 输出

```
31```

# 题解

## 作者：45dinо (赞：10)

肯定是一个 dp 或搜索，先考虑 dp。

显而易见，转移的可能钛多了……

仔细阅读题目，可以利用最优性获得三条结论：
1. 因为 AWP 只能击杀一个敌人，冷却时间不短于其他武器，故 AWP 只能用于 boss。
1. 每次最多连续往前一个关卡走 $1$ 次。
1. 只能在第 $n$ 个关卡或第 $n-1$ 个关卡结束游戏。

此时就已经比较接近真理了。

对于第 $i$ 关，有两种处理方法：
- 用手枪一个一个地打死小怪，用 AWP 打死 boss（结论1）。
- 用激光枪（或手枪）对所有敌人造成 1 点伤害，被迫移动到第 $i+1$ 关。

对于上述第 $2$ 种方法，对于第 $i+1$ 关，又有两种处理方法（由于结论2，必须要在第 $i+1$ 关就折返）
- 直接折返，用手枪打死第 $i$ 关的 boss，折返回第 $i+1$ 关。
- 用激光枪（或手枪）对所有敌人造成 1 点伤害，被迫移动到第 $i+1-1$ 关（第 $i$ 关），用手枪打死第 $i$ 关的 boss，回到第 $i+1$ 关，用手枪打死第 $i+1$ 的 boss（此时打肯定比到第 $i+2$ 关再折返更优），最后移动到第 $i+2$ 关。

设 $dp_i$ 为杀死前 $i-1$ 关的boss的最少用时。可以用 $dp_i$ 推出上述三条转移方程：
$$dp_{i+1}=\min(dp_{i+1},dp_i+a_i\times r_1+r_3+d)$$
$$dp_{i+1}=\min(dp_{i+1},dp_i+\min((a_i+1)\times r_1,r_2)+d+d+r_1+d)$$
$$dp_{i+2}=\min(dp_{i+2},dp_i+\min((a_i+1)\times r_1,r_2)+d+\min((a_{i+1}+1)\times r1,r2)+d+r_1+d+r_1+d)$$
根据结论3，最后的答案应该是：
$$\min(dp_{n+1}-d,dp_{n-1}+d+a_n\times r_1+r_2+d+r_1)$$

其实搜索的思路也类似，请读者自行yy。

感觉还是放一下代码为好。（尽管写起来非常容易）

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,r1,r2,r3,d,a[1000001],dp[1000003];
signed main()
{
	scanf("%lld %lld %lld %lld %lld",&n,&r1,&r2,&r3,&d);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		dp[i]=114514114514114514;
	}
	dp[n+1]=dp[n+2]=112414114514114514;
	dp[1]=0;
	for(int i=1;i<=n;i++)
	{
		dp[i+1]=min(dp[i+1],dp[i]+a[i]*r1+r3+d);
		dp[i+1]=min(dp[i+1],dp[i]+min((a[i]+1)*r1,r2)+r1+d*3);
		dp[i+2]=min(dp[i+2],dp[i]+min((a[i]+1)*r1,r2)+min((a[i+1]+1)*r1,r2)+2*r1+d*4); 
	}
	cout<<min(dp[n+1]-d,dp[n-1]+min((a[n-1]+1)*r1,r2)+r1*a[n]+r3+2*d+r1);
	return 0;
}
```

**Update 2020.9.1 经过神 $\color{black}\text Frogg$$\color{red}\text y$ 的友情提醒，修改了第一个状态转移方程**

---

## 作者：George1123 (赞：4)


更棒棒的体验 $\to$ [$\it\color{#142857}{George1123}$](https://www.cnblogs.com/George1123/p/13591631.html)

---
## 题面

> [CF1396C Monster Invaders](https://www.luogu.com.cn/problem/CF1396C)

> 有 $n$ 层关卡，每层有 $a_i$ 个小怪（$1$ 血）和 $1$ 个老怪（$2$ 血）。有三种武器：$1$ 武器每次攻击耗时 $r_1$，可以攻击一个怪 $1$ 血；$2$ 武器每次攻击耗时 $r_2$，可以攻击一层每个怪 $1$ 血；$3$ 武器每次攻击耗时 $r_3$，可以杀死一个怪。当一次攻击伤害了老怪但是没有杀死他时，玩家会被迫移动至相邻的层；也可以主动移至相邻的层。刚开始时在 $1$ 层，每次移动耗时 $d$，求最后杀死所有怪的最少耗时（不一定要在 $n$ 层结束）。

> 数据范围：$2\le n\le 10^6$，$1\le r_1\le r_2\le r_3\le 10^9$，$1\le d\le 10^9$，$1\le a_i\le 10^6$。

---
## 蒟蒻语

开学前最后一场比赛因为这题卡住了掉回了 CM，真是悲伤。当时少看了 $r_1\le r_2\le r_3$ 这个条件，AC 后才看到（所以即使没有这个条件蒟蒻的代码可能也可以 AC）。于是彻底失败的蒟蒻决定卧薪尝胆，做了这题写题解。

---
## 蒟蒻解

首先很明显，打每一层都有两种打法：

- 分次打，先用 $2$ 或 $1$ 把 boss 打残，把小兵都打死，然后到时候回来补一刀（用 $1$）。

$$st_i=\min(r_2,r_1(a_i+1))+r_1$$

- 一次打掉，用 $1$ 把 $a_i$ 个依次打掉，然后用 $3$ 把 boss 干掉。

$$pa_i=r_1a_i+r_3$$

除了 $st_i$ 和 $pa_i$，剩下可以对答案产生贡献的就是如何走位（$d$ 的贡献）。

假设每个每层如何打已经决定好，且下文中的分界点一定，可以证明如下走位最优：

> 对于某个分界点后一段选 $st$ 的，可以到达终点后回来打完（详见样例 $\#1$ 解释）。
>
> 对于分界点前一段的，从 $1$ 出发：
> 
> 对于每两个相邻的选 $st$ 的层对 $a,b$，走 $a\to b\to a\to b$ 的途中将两层打完；
> 
> 对于多余的选 $st$ 的层 $i$，走 $i\to i\pm 1\to i$。
> 
> 对于选 $pa$ 的，直接走过就可以。

放个抽象一点的图：

![1145141919810.jpg](https://i.loli.net/2020/08/31/Q7J6u5gsCFD1ETq.jpg)

比如样例 $\#2$：

打法选择：$[pa,pa,st,st]=6+6+6+8$。

走位选择：$1\to 2\to 1\to 2\to 3\to 4=5$。

所以答案是 $6+6+6+8+5=31$。

所以可以先 dp 出以第 $n$ 层为终点的前 $i$ 层的最少打法 $+$ 走位耗时，然后枚举分界点，两边答案加起来取最小值。


---
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define be(a) (a).begin()
#define en(a) (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),I=(b);i<I;i++)
#define L(i,a,b) for(int i=(a),I=(b);i>I;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    ll n,r1,r2,r3,d,ans=linf;
    cin>>n>>r1>>r2>>r3>>d;
    vector<ll> a(n),pa(n),st(n);
    R(i,0,n) cin>>a[i],pa[i]=r1*a[i]+r3,st[i]=min(r2,r1*(a[i]+1))+min(min(r1,r2),r3);
    vector<ll> f(n+1,linf),g(n+1); f[0]=d*(n-1);
    R(i,0,n){
        f[i+1]=min(f[i+1],f[i]+pa[i]);
        f[i+1]=min(f[i+1],f[i]+st[i]+d*2);
        if(i+1<n) f[i+2]=min(f[i+2],f[i]+st[i]+st[i+1]+d*2);  
    }
    ans=min(ans,f[n]);
    L(i,n-2,-1) g[i]=g[i+1]+min(pa[i],st[i]);
    R(i,0,n-1){
        ans=min(ans,f[i]+g[i]+d*(n-1-i)+pa[n-1]);
        ans=min(ans,f[i]+g[i]+d*(n-1-i)+d*2+st[n-1]);
    }
    cout<<ans<<'\n';
    return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：Soulist (赞：4)

挺无聊一个题...

大概先画一下你的行动路线，发现大概是一条链上挂了一点环，然后最后一个环可以不走回来的这样的一个东西。

所以就可以考虑 dp 了，设 $f_i$ 表示当前到位置 $i$，将 $[1,i]$ 中所有怪都消灭的方案。

那么转移有两种：

1. 从 $i-1$ 处转移过来，这个时候我们要直接消灭 $i$ 处的怪物才能保证留在 $i$ 处。
2. 枚举环的起点 $l+1$，那么每个位置的怪物可以直接以最小花费解决（注意我们会路过每个怪物至少两次）预处理最小花费，其前缀和，转移为 $f_i=f_l+S_n-S_{l}+(i-l-1)\times 3d+d$

然后边界情况会需要一点特判比较麻烦，所以可以直接认为 $f_0=-d$（相当于增加了一段起点）

然后对于 $f_n$ 单独转移一下即可，第二种转移显然可以拆开记录前缀 $\min$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int inf = 1e18 ; 
const int N = 1e6 + 5 ; 
int n, r1, r2, r3, d, a[N], f[N], mi[N], S[N], g[N] ; 
signed main()
{
	n = gi(), r1 = gi(), r2 = gi(), r3 = gi(), d = gi() ; 
	rep( i, 1, n ) a[i] = gi(), mi[i] = min( a[i] * r1 + min( r1 * 2, r3 ), r2 + r1 ) ; 
	rep( i, 1, n ) S[i] = S[i - 1] + mi[i] ; 
	memset( g, 63, sizeof(g) ) ; 
	memset( f, 63, sizeof(f) ) ;  
	g[0] = -d, f[0] = -d ; 
	for(re int i = 1; i <= n; ++ i ) {
		if( i > 1 ) f[i] = g[i - 2] + (i - 1) * 3 * d + S[i] ;
		f[i] = min( f[i], f[i - 1] + a[i] * r1 + r3 ), f[i] += d ; 
		g[i] = min( g[i - 1], f[i] - S[i] - i * 3 * d ) ; 
	}
	int tk = a[n] * r1 + r3 ; 
	for(re int i = 0; i < n; ++ i ) {
		if( i < n - 1 ) 
		f[n] = min( f[n], f[i] + d + S[n - 1] - S[i] + (n - i - 1) * 2 * d + tk ) ;
	}
	cout << f[n] << endl ; 
	return 0 ;
}
```

---

## 作者：SSerxhs (赞：3)

显然上 $x$ 层再下 $x$ 层不劣于上一层下一层，且如果非被迫不需要提前离开某一层

可以考虑设 $f_{i,0/1}$ 表示到第 $i$ 层清空与否的最短时间，则 $dp$ 方程只需要考虑直接清空、打一下上去下来清空再上去的情况，具体方程可见代码

注意最后不一定在第 $n$ 层结束，意味着最后可能并不需要上下上而只需要上下，注意对 $f_n$ 要特殊处理

```
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=1e6+2;
ll f[N][2];
int a[N];
int r,rr,rrr,d,n,i,c;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
int main()
{
	memset(f,0x3f,sizeof(f));
	read(n);read(r);read(rr);read(rrr);read(d);
	for (i=1;i<=n;i++) read(a[i]);
	f[0][1]=-d;
	for (i=1;i<=n;i++)
	{
		f[i][0]=f[i-1][1]+d+min((ll)rr,(ll)r*(a[i]+1));
		f[i][1]=min(f[i-1][1]+d+(ll)r*a[i]+rrr,f[i-1][0]+d*3ll+r+min((ll)rr+r,(ll)r*a[i]+min(rrr,r<<1)));
	}i=n;
	f[n][1]=min(f[i-1][1]+d+(ll)r*a[i]+rrr,f[i-1][0]+d*2ll+r+min((ll)rr+r+d,(ll)r*a[i]+min((ll)rrr,(ll)d+(r<<1))));
	printf("%lld",min(f[n][1],f[n][0]+d*2ll+r));
}
```

---

## 作者：听取MLE声一片 (赞：2)

简单题。

令 $A=r1$,$B=r2$,$C=r3$。

容易发现到达一个关卡之后都应该先把小怪给突突了，因为反正都要打，早打肯定不劣于晚打。

考虑 dp，设 $f_{i,0/1}$ 表示前 $i$ 关都处理完成，第 $i$ 关的 boss 死了或者残血的最短时间。

初值全部设为无穷大，因为进入下一关要有一定的距离，所以令 $f_{0,0}=-d$。

因为装弹时间的大小比较，手枪比狙击枪冷却要快，所以狙击枪只能打 boss。

有两种过关方式，第一种是用手枪把小怪全杀了然后用狙击枪把 boss 杀了；第二种是用手枪把所有怪都打一遍或者直接用激光枪，然后跑路，最后在回来把 boss 杀了。

转移就是分两类，一种是前面 boss 都打完了，直接转移就行；还有一种情况是前面的 boss 还有一个没死，转移的时候是要把这个 boss 杀了。

暴力模拟一下，转移用代码写就是这个样子：

```
int x=a[i]*A+C,y=min(a[i]*A+A,B);
f[i][0]=min(f[i][0],f[i-1][0]+d+x);
f[i][1]=min(f[i][1],f[i-1][0]+d+y);
f[i][0]=min(f[i][0],f[i-1][1]+d+min(x,y+A)+d+A+d);
```

第 $n$ 关要特殊转移。第一点是如果先把第 $n$ 关 boss 打完回到第 $n-1$ 关之后就不需要再去第 $n$ 关了；其次因为不能往后走了，是在前面 boss 都打完的情况下打一下 boss 后走到第 $n-1$ 关再走到第 $n$ 关。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e6+10;
const int inf=1e18;
int n,A,B,C,d,a[N],f[N][2]; 
signed main()
{
	n=read(),A=read(),B=read(),C=read(),d=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=0;i<N;i++)
		f[i][0]=f[i][1]=inf;
	f[0][0]=-d;
	for(int i=1;i<n;i++){
		int x=a[i]*A+C,y=min(a[i]*A+A,B);
		f[i][0]=min(f[i][0],f[i-1][0]+d+x);
		f[i][1]=min(f[i][1],f[i-1][0]+d+y);
		f[i][0]=min(f[i][0],f[i-1][1]+d+min(x,y+A)+d+A+d);
	}	
	int x=a[n]*A+C,y=min(a[n]*A+A,B);
	f[n][0]=min(f[n][0],f[n-1][0]+d+x);
	f[n][0]=min(f[n][0],f[n-1][1]+d+min(x,y+A+d)+d+A);
	f[n][0]=min(f[n][0],f[n-1][0]+d+y+d+d+A);
	cout<<f[n][0];
	return 0;
}

```







---

## 作者：wind_whisper (赞：2)

## 前言
本篇题解是笔者按照笔者自己的思路撰写的，做完后发现和官方题解以及洛谷大部分都题解的状态设计都略有不同，因此发了这篇题解希望能够通过.  
## 解析
本题的关键是通过题意抽象出简洁、易转移的打怪策略.  
首先可以发现，如非被迫，在打完怪之前离开是不优的.  
打怪的策略选择可以简化为如下三种：  
>1.手枪点死所有小怪， AWP 干掉 boss .  
>2.手枪点死所有小怪，再点一下 boss ，逃跑，回来再点一下 boss .  
>3.激光枪扫死所有小怪，逃跑，回来用手枪点死 boss .  

其中 2、3 都需要去而复返，对全局而言是等价的.   
设打 1 次通关第 $i$ 关的代价是 $f_{i,1}$ , 打两次通关第 $i$ 关的代价是 $f_{i,2}$ .  （均不考虑移动的代价）  
那么就有：  
$$f_{i,1}=a[i]\times r1+r3$$  
$$f_{i,2}=\min((a_i+2)*r1,r1+r2)$$

注意到， $f_{i,2}$ 不大于 $f_{i,1}$ .  
我们需要打两次第 $i$ 关的时候，只需要先打一次 $i$ ，去 $i+1$ 关顺便打一次，回到第 $i$ 关打完，去第 $i+1$ 关打完，这样在相邻的两关之间横跳，只需要两次额外的移动就可以使相邻的两关都打两次，这样在需要移动的时候是不劣的.  
设计 $dp_i$ 表示打完 $[1,i]$ 关并**站在第 $i$ 关**的最小代价.  
对于 $dp_i$ 的转移，按照打一次或者打两次，分别从 $dp_{i-1}$ 或者$dp_{i-2}$ 模拟过程进行转移，再取最小值即可.  
在第 $1$ 关和第 $n$ 关边界处需要特殊处理一下，具体的细节可见代码.  
## 代码
$dp$ 式子看着复杂，其实都是模拟.在必要处加了注释便于理解.
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+100;
const int mod=1e9+7;
#define ll long long
ll read(){
	ll x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();};
	while(isdigit(c)){x=x*10+c-'0';c=getchar();};
	return x*f;
}
int n,m,k;
ll r1,r2,r3,a[N],dp[N],d;
int main(){
	#ifndef ONLINE_JUDGE
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	#endif
	n=read();r1=read();r2=read();r3=read();d=read();
	for(int i=1;i<=n;i++) a[i]=read();
	dp[0]=-d;//边界的dp[0]设为-d，与从第0关走到第1关需要的d时间恰好抵消 
	dp[1]=min(a[1]*r1+r3,r2+2*d+r1);
	for(int i=2;i<=n;i++){
		//min的前面一项是在第i关一次打完，后面一项是模拟在i-1和i之间横跳 
		dp[i]=min(dp[i-1]+d+min(a[i]*r1+r3,2*d+min(r2+r1,(a[i]+2)*r1)),dp[i-2]+d+min(r2+r1,(a[i-1]+2)*r1)+3*d+min(r2+r1,(a[i]+2)*r1));
	}
	ll ans=min(dp[n],dp[n-2]+d+r2+r1+2*d+a[n]*r1+r3);//特判最后可以停在第n-1关不再回来 
	printf("%lld\n",ans);
	//printf("%lld\n",dp[2]);
	return 0;
}
/*
4 2 4 4 1
4 5 1 2
*/


```



---

## 作者：feecle6418 (赞：2)

显然是一个 dp。

在每一层有三种抉择：

- 用第一种枪 $a_i$ 次，再用 AWP；
- 用第一种枪 $a_i+1$ 次，逃走，等会再来；
- 用第二种枪，逃走，等会再来。

**本题的难点在于设一个好的状态。** 设 $f_{i,0}$ 为打了前 $i$ 层，第 $i$ 层的 boss 打完了，现在在 $i$ 的最优解；$f_{i,1}$ 为打了前 $i$ 层，第 $i$ 层的 boss 还有一滴血，**现在在 $i$，需要逃走等会回来**的最优解。直接转移即可，转移不是重点，略去。

最后的答案两种情况：可以是 $f_{n,0}$，亦可以是从没打完的 $n-1$ 层到 $n$，打完 $n$ 再回到 $n-1$ 清除 boss。相信这一点也不难想到。

这里重复一遍：本题的关键在于状态的定义，特别是 $f_{i,1}$，若没有明确定义就会出现“到底能不能直接攻击 boss？”之类的问题，需要推敲一下才能得到以上的定义。

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
ll f[1000005][2],c1,c2,c3,d,a[1000005];
int n;
int main(){
	ios::sync_with_stdio(0),cin>>n>>c1>>c2>>c3>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	f[1][0]=c1*a[1]+c3,f[1][1]=min(c2,c1*(a[1]+1));
	for(int i=1;i<n;i++){
		f[i+1][1]=f[i][0]+min(c2,c1*(a[i+1]+1))+d;
		f[i+1][1]=min(f[i+1][1],f[i][1]+d+min(c2,c1*(a[i+1]+1))+c1+2*d);
		f[i+1][0]=f[i][0]+c1*a[i+1]+c3+d;
		f[i+1][0]=min(f[i+1][0],f[i][1]+d+c1*a[i+1]+c3+d+c1+d);
		f[i+1][0]=min(f[i+1][0],f[i][1]+d+min(c2,c1*(a[i+1]+1))+2*d+2*c1);
	}
	cout<<min(f[n][0],f[n-1][1]+d+c1*a[n]+c3+d+c1);
    return 0;
}
```

---

## 作者：chenxia25 (赞：2)

首先扯一句题外话：B 出题人 \*\*\*\*。nmd 老子开学前一天打你午夜的比赛，还出个结论题糟蹋我比赛体验？还好把这个 C 做出来了，要不然玩完了。

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/CF1396C ) & [CF 题目页面传送门]( https://codeforces.com/contest/1396/problem/C )
>
> 题意见洛谷。

注意到一个 boss 的血量为 $2$，于是每一级最多会被强制离开 $1$ 次。

于是考虑对于每一级决定是否被强制离开。设若不离开，那么第 $i$ 级最少需要 $x_i$ 的时间打怪；若离开，那么第 $i$ 级最少需要 $y_i$ 的时间打怪（这个 $x_i,y_i$ 太好算了，显然可以 $\mathrm O(1)$，就不再赘述了）。显然，对于一种决定，总时间就是它们的打怪时间相加（虽然被强制离开的级别的打怪过程不是连续的，但也可以相加）加上走路的最小总时间。不妨来研究对于任意一个决定，走路的最优路线长什么样子。

若没有被强制离开的级别的话，最优路线显然是从 $1$ 笔直走到 $n$。如果有的话，那么那些被强制离开的点要经过 $2$ 次（这是显然的吧）。按原笔直路线经过它们的时候，它们只被经过了 $1$ 次；要想来个第 $2$ 次，肯定要回头；然后还要继续往前走啊，于是回头走到某处的时候还要再回头按原笔直路线走。于是很容易得出结论：最优路线一定是在笔直路线的基础上，有若干个不相交的区间多走了 $2$ 遍，其中这些区间要覆盖所有的被强制离开的点。

细节：

1. 每个区间的大小要 $>1$，因为 $=1$ 的话就是原地打转，是不算经过多遍的；
2. **若 $n$ 处不被强制离开的话**，那么右端点为 $n$ 的区间是只需要再多走 $1$ 遍的，因为到达了左端点之后就没必要再回头了，游戏已经 win 了。

接下来就很容易设计出无后效性的 DP 了（在得出结论之前，瓶颈在于可以往两边跑，后效性消除不了）。$dp_i$ 表示考虑到第 $i$ 级，停在第 $i$ 级且前 $i$ 级都打掉了时的最小打怪、额外走路总时间。边界：$dp_0=0,dp_1=x_1$；目标：$dp_n+(n-1)d$。转移的话，考虑第 $i$ 级是离开还是不离开两种选择：不离开简单要死；离开的话，显然 $i$ 是最后一个重复走区间的右端点，于是枚举左端点。所以状态转移方程：

$$dp_i=\min\!\left(dp_{i-1}+x_i,\min\limits_{j=0}^{i-2}\!\left\{dp_j+\sum\limits_{k=j+1}^i\min(x_k,y_k)+2(i-j-1)d\right\}\right)$$

直接算是 $\mathrm O\!\left(n^3\right)$ 的。里层 $\sum$ 可以前缀和优化掉，剩下来也可以 two-pointers 简单优化成 $\mathrm O(n)$。注意，$i=n$ 要特殊算，随便跑一下即可，不影响复杂度。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=1000000;
int n;
int r1,r2,r3,d;
int a[N+1];
int dp[N+1];
int x[N+1],y[N+1];
int Sum[N+1];
signed main(){
	cin>>n>>r1>>r2>>r3>>d;
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	for(int i=1;i<=n;i++){
		x[i]=a[i]*min(r1,r3)+r3;
		y[i]=min(r2+min(min(r1,r2),r3),a[i]*min(r1,r3)+min(r1,r2)+min(min(r1,r2),r3));
		Sum[i]=Sum[i-1]+min(x[i],y[i]);
//		cout<<x[i]<<" "<<y[i]<<"\n";
	}
	int mn=inf;
	dp[1]=x[1];
	for(int i=2;i<n;i++){
		mn=min(mn,dp[i-2]-Sum[i-2]-2*(i-1)*d);
		dp[i]=min(dp[i-1]+x[i],mn+Sum[i]+2*i*d);
//		cout<<dp[i]<<"\n";
	}
	dp[n]=dp[n-1]+x[n];
	for(int i=0;i<=n-2;i++)
		dp[n]=min(dp[n],dp[i]+Sum[n]-Sum[i]+2*n*d-2*(i+1)*d),
		dp[n]=min(dp[n],dp[i]+Sum[n-1]-Sum[i]+x[n]+n*d-(i+1)*d);
	cout<<dp[n]+(n-1)*d;
	return 0;
}
```

---

## 作者：钓鱼王子 (赞：2)

一道简单 DP。

首先，分析一下路径的样子：
![](https://cdn.luogu.com.cn/upload/image_hosting/e0pu5x3v.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

是一段连续的上中间穿插一些单个的下加上一段连续的上最后一段连续的下。

拆成两半，DP 求解。

后一半直接计算，前一半设 $dp_{i,0/1}$ 表示当前第 $i$ 层，前一层是否有 boss。

为什么这样是正确的？

如果当前必须移动，且之前还有 boss，那么往前一定会优。

具体转移可以看代码，有一些边界。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t; 
}
int n,a[1000005],r1,r2,r3,d,dp[1000005][2],ans,f[1000005];
signed main(){
	n=read(),r1=read(),r2=read(),r3=read(),d=read();
	dp[1][1]=dp[1][0]=0;
	for(re int i=1;i<=n;++i)a[i]=read();
	for(re int i=2;i<=n+1;++i){
		dp[i][0]=dp[i-1][1]+min(r1*(a[i-1]+1),r2)+(i==n+1?0:d);
		dp[i][0]=min(dp[i][0],dp[i-1][0]+min(min(r1*(a[i-1]+1),r2)+r1+d+d,r1*a[i-1]+r3+d+(i==n+1?0:d))+(i==n+1?0:d));
		dp[i][1]=min(dp[i-1][1]+r1*a[i-1]+r3+(i==n+1?0:d),dp[i-1][0]+min(min(r1*(a[i-1]+1),r2)+r1+d+r1+d,r1*a[i-1]+r3+d+r1+(i==n+1?0:d))+(i==n+1?0:d));
	}
	ans=dp[n+1][1];
	for(re int i=n;i;--i){
		f[i]=f[i+1]+min((a[i]+1)*r1,r2)+r1+d+(i==n?d:0)+(i==n?0:d);
		ans=min(ans,dp[i][1]+f[i]);
	}
	printf("%lld",ans);
}
```


---

## 作者：BIG_CUTE_BUG (赞：1)

[题传](https://www.luogu.com.cn/problem/CF1396C) [cf](https://codeforces.com/problemset/problem/1396/C)

## 思路

这题就没什么后效性，联想到 dp。瓶颈在于强制转移到相邻房间该怎么处理。

于是进行讨论，对于每一个房间：
1. 用手枪打死所有小兵后，用大狙秒掉 boss。
2. 用手枪打死所有但折返一次。
3. 用激光枪打死所有小兵后，用手枪打死 boss，但折返一次。

发现对于某个房间的击杀策略，分为折返和不折返。所以想到单独设一个状态来处理折返。

$f_{i,1/0}$ 表示第 $i$ 个房间击杀 boss 是（否）折返时，清空前 $i$ 个房间的最少时间。

转移就很纯度了：
1. 如果 $i-1$ 不折返，就直接花费 $d$ 转移，然后清空 $i$ 房间就行了。
2. 如果 $i-1$ 需要折返，就需要从 $i-1$ 到 $i$，再从 $i$ 回到 $i-1$，最后再到 $i$ 清空怪物，花费 $3d$。
3. 如果 $i-1$ 需要折返，$i-2$ 也需要折返，那 $i-1$ 和 $i-2$ 相互折返就行了，不用向 $i$ 折返了。具体来讲，就是从 $i-2$ 至 $i-1$，再从 $i-1$ 回到 $i-2$，再从 $i-2$ 到 $i-1$，最后再到 $i$，花费 $4d$。

其中，有一个处理技巧，就是所记录清空前 $i$ 个房间的最少时间，并没有包括 $i$ 的折返时间。这个折返时间会被加入到 $i+1$ 中。

具体见下面的转移方程（代码，~~懒得打 KateX~~）：
```cpp
f[i][0] = min({f[i - 1][0] + d, f[i - 1][1] + d * 3, f[i - 2][1] + d * 4 + min(a * (p[i - 1] + 2), a + b)}) + a * p[i] + c;
f[i][1] = min({f[i - 1][0] + d, f[i - 1][1] + d * 3, f[i - 2][1] + d * 4 + min(a * (p[i - 1] + 2), a + b)}) + min(a * (p[i] + 2), a + b);
```

不难发现，第 $n$ 间房间得单独讨论。

由于我并没有加入每个房间的折返时间，故第 $n$ 间得将其加入考虑：
1. 第 $n$ 间不折返，直接从 $n-1$ 正常转移。
2. 第 $n$ 间不折返，$n-1$ 折返，从 $n-1$ 到 $n$ 再到 $n-1$ 结束，只花费 $2d$。
3. 第 $n$ 间折返，不论 $n-1,n-2$ 如何，最终都是 $n-1$ 到 $n$ 再到 $n-1$，花费 $3d$。

（事实上从转移方程看来，是不用设两维的，~~所以我太菜了~~）
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, p[N];
long long f[N][2], a, b, c, d;
signed main()
{
	ios :: sync_with_stdio(0); cin.tie(0);
	cin >> n >> a >> b >> c >> d;
	for(int i = 1; i <= n; i++) cin >> p[i];
	f[0][0] = f[0][1] = 1e18; f[1][0] = a * p[1] + c; f[1][1] = min(a * (p[1] + 2), a + b);
	for(int i = 2; i <= n; i++)
	{
		f[i][0] = min({f[i - 1][0] + d, f[i - 1][1] + d * 3, f[i - 2][1] + d * 4 + min(a * (p[i - 1] + 2), a + b)}) + a * p[i] + c;
		f[i][1] = min({f[i - 1][0] + d, f[i - 1][1] + d * 3, f[i - 2][1] + d * 4 + min(a * (p[i - 1] + 2), a + b)}) + min(a * (p[i] + 2), a + b);
	}
	cout << min({f[n][0], min(f[n - 1][0], f[n - 1][1]) + d * 3 + min(a * (p[n] + 2), a + b), f[n - 1][1] + d * 2 + a * p[n] + c});
	return 0;
}
```

---

## 作者：Fairicle (赞：1)

一道 DP 题。

我们发现这题的特点是可以反复横跳（bushi

于是不能简单地设置一维的状态

可行的一种方案是设计状态 $f_{i,{0/1}}$ 表示现在在级别 $i$，是否消灭了 boss（0 代表消灭）

则初始化 

$f_{1,0}=a[1] \times r_1 + r_3$

$f_{1,1}=min(a[1] \times r_1+r_1,r_2)$

有转移方程

$$f_{i,0}=min(f_{i-1,0}+d+a[i] \times r_1+r_3,f_{i-1,1}+d+min(a[i] \times r_1+r_1,r_2)+d+r_1+d+r_1)$$

$$f_{i,1}=min(f_{i-1,0}+d+min(r_2,a[i]*r_1+r_1),f_{i-1,1}+d+min(a[i]*r_1+r_1,r_2)+d+r_1+d)$$

虽然它看上去很长但是还是很直观的。

最后答案为 $min(f_{n,0},f_{n-1,1}+d+a[n] \times r_1+r_3+d+r_1)$

第二项为什么那么长呢？首先显然是不能取 $f_{n,1}$ 的，因为 boss 没死。答案中的情况就是最后在 $n-1$ 处杀死了所有的 boss。

那能不能用 $f_{n,1}+d+d+r_1$ 更新答案？

不能，显然是不优的，$f_{n-1,1}+a[n] \times r_1+r_3<f_{n,1}$

code：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ul unsigned long long
#define ui unsigned int
#define ri register int
#define pb push_back
#define mp make_pair
char p[30]={'0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
inline ll rd(){
	ll x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
#define N 1000010
ll n,r1,r2,r3,d,a[N],f[N][2];
inline int lowbit(int x){return x & ( - x ) ;}
int main()
{
	std::ios::sync_with_stdio(false);
    n=rd(),r1=rd(),r2=rd(),r3=rd(),d=rd();
    for(ri i=1;i<=n;++i) a[i]=rd();
    f[1][0]=a[1]*r1+r3,f[1][1]=min(r2,a[1]*r1+r1);
    for(ri i=2;i<=n;++i){
    	f[i][0]=min(f[i-1][0]+d+a[i]*r1+r3,f[i-1][1]+d+r1+d+min(a[i]*r1+r1,r2)+r1+d);
    	f[i][1]=min(f[i-1][0]+d+min(r2,a[i]*r1+r1),f[i-1][1]+d+min(a[i]*r1+r1,r2)+d+r1+d);
	}
	cout<<min(f[n][0],f[n-1][1]+d+a[n]*r1+r3+d+r1);
	return 0;
}
```


---

## 作者：Zi_Gao (赞：0)

首先需要正确理解题面：

1. 手枪、激光枪、AWP 分别有 $r1,r2,r3$ 的冷却时间，但是这个冷却实际上是**蓄力前摇**，**不能**同时冷却。

2. 这些枪都不**不能**打其他关卡的怪。

首先分析下三个武器：

1. 手枪：相当于每次杀死一个小怪。打 boss 时会先打一枪，然后被送走，后来后再打一枪。

2. 激光枪：相当于杀死关卡中所有小怪，打掉 boss 一滴血，然后被送走。显然一关最多在开头使用一次激光枪。

3. AWP：直接杀死一个怪。

分析一下打过某一关的方式：

1. 开头使用一次激光枪，然后被送走，回来用一次手枪打死 boss。

2. 使用手枪打完小怪，打 boss 一枪，然后被送走，后来后再打一次手枪。

3. 使用手枪打完小怪，然后使用 AWP 杀死 boss。

考虑前两个方式，我们称为打法一，第三个方式称为打法二，对于打法一的连续段：

1. 连续段在中间，那么连续段中相邻两关的路程会贡献 3 次。

2. 连续段在最后：那么最后一关使用打法二，然后回依次向前被送走，打完每个 boss。

于是设计一个 dp 状态：

1. $dp_{i,0}$ 表示前 $i$ 关 boss 打完了的最小时间花费。

2. $dp_{i,1}$ 表示前 $i-1$ 关 boss 打完了，并且第 $i-1$ 关需要回去打一次的最小时间花费，注意回去打一次手枪的时间已经 $dp_{i,1}$ 计算了。

3. $dp_{i,2}$ 表示，接下来是方式二的连续段，并且直到最后一关。

分类讨论一下转移即可，特别的当 $dp_{n,2}$ 的代价是直接击杀 boss 的代价。看代码就能看懂这个分类讨论了。

```cpp
#include<bits/stdc++.h>

int read(){
	int x;
	scanf("%d",&x);
	return x;
}

void print(long long x){
	printf("%lld",x);
	return;
}

long long arr[1000010],dp[1000010][3];

int main(){
	register int i;
	long long r1,r2,r3,d,val1,val2;
	int n=read();
	r1=read();
	r2=read();
	r3=read();
	d=read();

	dp[0][0]=-d;
	
	for(i=1;i<=n;++i){
		arr[i]=read();
		val1=r1*arr[i]+r3;
		val2=std::min(r1*arr[i]+r1,r2)+r1;
		
		dp[i][0]=std::min({
			dp[i-1][0]+val1+d,
			dp[i-1][1]+val1+d+d*2,
			dp[i-1][0]+val2+d+d*2,
			dp[i-1][1]+val2+d+d*2,
		});
		dp[i][1]=std::min({
			dp[i-1][0]+val1+d,
			dp[i-1][1]+val1+d+d*2,
			dp[i-1][0]+val2+d,
			dp[i-1][1]+val2+d+d*2,
		});
		if(i==n) val2=std::min(val2+d*2,val1);
		dp[i][2]=std::min({
			dp[i-1][2]+val2+d+d,
			dp[i-1][0]+val2+d,
			dp[i-1][1]+val2+d+d*2,
		}); 
		
	}
	
	print(std::min(dp[n][0],dp[n][2])); 
	
	return 0;
}


```

---

## 作者：Unnamed114514 (赞：0)

每个位置转移到其它位置时，只有如下 $3$ 种情况：

- $a+1$ 发手枪

- 一发激光枪

- $a$ 发手枪，一发 AWP

前两种情况都需要跳到旁边再跳回来。

你从 $i$ 一直选 $1/2$ 到 $j$，再从 $j$ 回到 $i$，还要从 $i$ 再去 $j$ 然后再到 $j+1$。

注意到这个方案等价于 $i\to i+1\to i\to i+1\to\cdots\to j$，那么这种情况我们直接单独考虑每一位即可。

特殊情况是，当 $j=n$ 时，$j$ 到 $i$ 之后结束，这样的话就不用回到 $j$ 了。

这种情况直接预处理一下后缀就行了，记 $i$ 开头后缀的答案是 $s_i$。

然后还有 $i$ 和 $i-1$ 互相反复横跳的情况，不是很好处理，于是我们可以给它放到状态里。

定义 $f_{i,0/1}$ 表示前 $i$ 个 $i$ 是否跳到 $i+1$ 的答案，初始化 $f_{1,0}\gets a_1\times d_1+d_3,f_{1,1}\gets\min\{(a_1+1)d_1,d_2\}$。

考虑转移。

$f_{i,0}$ 的情况，$i-1$ 可以和 $i$ 互相独立，即 $f_{i-1,0}+d+a_i\times d_1+d_3$，可以 $i$ 跳到 $i-1$，此时 $i-1$ 是否依赖 $i$ 并不重要：$\min\{f_{i-1,1}+d\times 3+d_1+\min\{a_i\times d_1+d_3,d_1+d_2,(a_i+2)\times d_1\},f_{i-1,0}+d\times 3+\min\{d_1+d_2,(a_i+2)\times d_1\}\}$。

$f_{i,1}$ 的情况相对简单，如果 $i-1$ 依赖 $i$，那么 $i$ 依赖 $i+1$ 显然不优，所以只需要从 $f_{i,0}$ 转移即可：$f_{i-1,0}+d+\min\{(a_i+1)\times d_1,d_2\}$。

考虑求答案：不在后面接 $s$ 的情况，$n$ 显然不能依赖 $n+1$，答案是 $f_{n,0}$；如果 $i$ 后面接 $s$，那 $i$ 就不能依赖 $i+1$，否则就会少算贡献，就是 $\min\{s_1,\min\limits_{i=1}^{n-1} f_{i,0}+d+s_{i+1}\}$。

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,ans,d1,d2,d3,d,a[N],s[N],f[N][2];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>d1>>d2>>d3>>d;
    for(int i=1;i<=n;++i) cin>>a[i];
    s[n+1]=1e18,s[n]=a[n]*d1+d3;
    for(int i=n-1;i;--i) s[i]=s[i+1]+min((a[i]+2)*d1,d1+d2)+d*2;
    memset(f,0x3f,sizeof(f));
    ans=s[1];
    f[1][0]=a[1]*d1+d3;
    f[1][1]=min((a[1]+1)*d1,d2);
    for(int i=2;i<=n;++i){
        f[i][0]=min({f[i-1][0]+d+a[i]*d1+d3,f[i-1][1]+d1+d*3+min({a[i]*d1+d3,d1+d2,(a[i]+2)*d1}),f[i-1][0]+d*3+min(d1+d2,(a[i]+2)*d1)});
        f[i][1]=f[i-1][0]+d+min((a[i]+1)*d1,d2);
        ans=min(ans,f[i][0]+d+s[i+1]);
    }
    cout<<min(ans,f[n][0])<<endl;
    return 0;
}
```

---

## 作者：jasonliujiahua (赞：0)

# CF1396C

## Solution：

首先这个翻译非常的差劲，题目所说的时间其实就是代价，不影响后面的决策，即不会持续有影响。然后就比较无脑地 dp 即可：设 $dp_{i,0/1}$ 表示前 $i-1$ 位的 boss 都死了，第 $i$ 个 boss 死/残后走到 $i$ 的最小代价。可以设 $x=a_i\times r1+r3$，$y=min((a_i+1)\times r1,r2)$，表示只考虑 $i$ 内部是打死/残的最小代价。$dp_{i,1}=dp_{i-1,0}+d+y$ 非常显然，接下来只需考虑 $dp_{i,0}$ 即可。有以下情况：
- 不与 $i-1$ 合作
	- 直接打死：$dp_{i-1,0}+d+x$
	- 打残再逃跑再打死：$dp_{i-1,0}+d+y+d+d+r1$
- 与 $i-1$ 合作
	- 直接打死：$dp_{i-1,1}+d+x+d+r1+d$
	- 打残再逃跑再打死：$dp_{i-1,1}+d+y+d+r1+d+r1$
      
四种情况取最小值即可。然后发现第 $n$ 个人不一定要回到 $n$，需特殊处理。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
int n,r1,r2,r3,d,a[maxn],dp[maxn][2];//0：boss 死，1：boss 残 
void init()
{
	cin>>n>>r1>>r2>>r3>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
}
void DP()
{
    dp[1][0]=a[1]*r1+r3;
    dp[1][1]=min((a[1]+1)*r1,r2);
	for(int i=2;i<n;i++)
	{
		int x=a[i]*r1+r3,y=min((a[i]+1)*r1,r2);
		dp[i][1]=dp[i-1][0]+d+y; 
		dp[i][0]=dp[i-1][0]+d+x;
	    dp[i][0]=min(dp[i][0],dp[i-1][0]+d+y+d+d+r1);
		dp[i][0]=min(dp[i][0],dp[i-1][1]+d+min(y+r1,x)+d+r1+d); 
	}
	int i=n;
	int x=a[i]*r1+r3,y=min((a[i]+1)*r1,r2);
	dp[i][0]=dp[i-1][0]+d+x; 
	dp[i][0]=min(dp[i][0],dp[i-1][0]+d+y+d+d+r1);
	dp[i][0]=min(dp[i][0],dp[i-1][1]+d+min(y+d+r1,x)+d+r1);
	cout<<dp[n][0]; 
} 
signed main()
{
	init();
	DP();
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [CF1396C Monster Invaders](https://www.luogu.com.cn/problem/CF1396C)

首先大怪的血量只有 $2$，因此最多强制离开一次。如果不被强制离开，我们需要 $a_{i} \times r_{1}+r_{3}$ 的时间通关，即先用手枪把所有小怪点掉，然后再把大怪狙掉。如果被强制离开，我们需要 $\min(r_{1}+r_{2},r_{1} \times (a_{i}+2))$，即用激光枪扫一遍之后再用手枪点掉或者全用手枪点掉。

如果不被强制离开所需的通关时间更少，那么我们肯定选择一遍通关。不然的话，我们就要考虑是否折回来，并且折回来了还要继续向前走，所以，最优策略一定是在走一遍路程的基础上加上一些不相交的区间走了两次，而且所有被强制离开的点一定要被这些区间覆盖。

考虑转移。首先，区间的长度肯定要大于 $1$，不然就原地转圈了。其次，如果最后一关不被强制离开的话，那么以最后一关为右端点的区间只要走一次，因为可以在任何地方结束，所以走到左端点就可以直接结束了。令 $dp_{i}$ 表示当前在 $i$，前 $i$ 关都通关了的最小时间（不包括必须走一遍的时间）。转移首先考虑 $i$ 离不离开，如果不离开，直接加上不离开的通关时间。不然，枚举 $i$ 为右端点的区间的左端点。转移方程为：

$$dp_{i}=\min(dp_{i-1}+x_{i},\min_{j=0}^{i-2}(dp_{j}+\sum_{k=j}^{i}\min(x_{k},y_{k})+2 \times (i-j) \times d))$$

求和可以前缀和优化，然后把后面那个式子拆开，边转移边维护一个关于 $j$ 的最小值，这样复杂度就是 $O(n)$ 的了。

code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10,INF=1e18;
int n,r1,r2,r3,d;
int a[N],x[N],y[N],sum[N];
int dp[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>r1>>r2>>r3>>d;
	for (int i=1;i<=n;++i)
    {
        cin>>a[i];
		x[i]=a[i]*r1+r3;
		y[i]=min(r1+r2,r1*(a[i]+2));
		sum[i]=sum[i-1]+min(x[i],y[i]);
	}
	int minx=INF;
	dp[1]=x[1];
	for (int i=2;i<n;++i)
    {
		minx=min(minx,dp[i-2]-sum[i-2]-2*(i-1)*d);
		dp[i]=min(dp[i-1]+x[i],minx+sum[i]+2*i*d);
	}
	dp[n]=dp[n-1]+x[n];
	for (int i=0;i<n-1;++i)
    {
        dp[n]=min(dp[n],dp[i]+sum[n]-sum[i]+2*n*d-2*(i+1)*d),
		dp[n]=min(dp[n],dp[i]+sum[n-1]-sum[i]+x[n]+n*d-(i+1)*d);
    }
	cout<<dp[n]+(n-1)*d<<endl;
	return 0;
}
```


---

## 作者：DiDi123 (赞：0)

首先可以发现 AWP 使用在小怪身上很不值，所以就应该直接使用在大怪身上，而且此时的大怪的血量应该为 $2$。这样的话就可以分两种情况：

1. 使用 AWP。这时需要先杀掉该关卡的所有小怪，并且不能对大怪造成伤害，所以只能先使用手枪击杀小怪，需要花费的总时间为 $a_i\times r_1+r_3$。

2. 不适用 AWP。这样的话不能一下子把大怪杀死，所以需要分两次闯关，只考虑闯关时花费的时间的话，需要花费的最小时间就是 $\min (r_2+r_1,r_1\times (a_i+2))$。

很明显地，情况 2 会需要之后我们再折回来，这样也会多花费路费，所以当情况 1 和情况 2 在关内花费相同或情况 1 更优的时候，我们会选择情况 1。

如果情况 2 在关内更优，我们可以采用一种方式表示是否选情况 2。我们可以先默认全选情况 1，然后把情况 2 需要花费的时间定为**负数**，设这个数为 $at_i$。题目就变为**选择一条路径，经过两次 $i$ 之后可以少花费 $|at_i|$ 的时间，且经过每条路需要花费 $d$ 的时间。** 

考虑用 dp 去做。我们会发现因为要求通过所有的关卡，所以必须要向右走到 $n$，也就是说走到 $i(i<n)$ 这个点的时候，如果选择往左走，还需要再折回到 $i$，为了能继续向右走。所以我们令 $f_i$ 表示走到 $i$ 这个点，进行向左的折回（也可以不向左走）之后能花费的最小时间。

那么我们就可以枚举向左进行折回的位置（设为 $j$），则 $f_i=\min(f_{i-1}+d,\min \limits _{j=1}^{i-1} \{3d(i-j)+\sum \limits _{k=j}^i at_k+f_{j-1} +d \})$

可以参考图片理解：

![tp](https://cdn.luogu.com.cn/upload/image_hosting/48ad0p49.png)

我们对 $at$ 取一下前缀和，令 $sum_i=\sum \limits _{j=1}^iat_j$，则

$$
\begin{aligned}
f_i &=\min \limits _{j=1}^{i-1} \{3d(i-j)+sum_i-sum_{j-1}+f_{j-1}+d \} \\
&= 3di+sum_i-\max \limits _{j=1}^{i-1}\{3dj+sum_j-f_{j-1}-d\}

\end {aligned}
$$

然后从前往后处理过程中对 $3dj+sum_j-f_{j-1}-d$ 取一个前缀最大值就行了。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000010
typedef long long ll;
ll n,d,r1,r2,r3,a[MAXN];
__int128 sum[MAXN],f[MAXN],mx; //可能会比较大，需要用 int128
int main()
{
	__int128 ans; 
	cin>>n>>r1>>r2>>r3>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ll tx=a[i]*r1+r3,ty=min(r2+r1,r1*(a[i]+2));
		ans+=tx;
		if(ty<tx) sum[i]=ty-tx;
	}
	for(int i=1;i<=n;i++) sum[i]+=sum[i-1];
	mx=3*d;
	for(int i=2;i<n;i++)
	{
		f[i]=min(f[i-1]+d,sum[i]+3*d*i-mx);
		mx=max(mx,sum[i-1]+3*d*i-f[i-1]-d);
	}
	__int128 tp=f[n-1]+d;
	for(int i=1;i<=n;i++) //最后可能在各个点结束
		tp=min(tp,f[i-1]+sum[n-1]-sum[i-1]+2*d*(n-i)+d);
	tp=min(tp,sum[n]+3*d*n-mx);	//经过两次n才能获得
	cout<<(ll)(ans+tp);
}
```


---

## 作者：TTpandaS (赞：0)

一个关卡有三种方式打完。第一种是先用 $r2$ 再走到另一个关卡再走回来用 $r1$ 补掉 boss。第二种是先给所有怪用 $r1$ 打再走到另一个关卡再走回来用 $r1$ 补掉 boss。第三种是给所有小怪用 $r1$，在用 $r3$ 解决 boss。

前两种情况都涉及走到其他关卡，所以再各分两种情况：走到上一个关卡或者下一个关卡。

那么当一个关卡在第一种情况或第二种情况时选择走到上一个关卡，如果上一个关卡也在第一种情况或第二种情况选择走到下一个关卡，就可以节约一个来回的时间。

然后其他的都按照各个情况 dp 即可。

```cpp
  		dp[i][0][0]=min(min(dp[i-1][0][1],dp[i-1][1][1])+r[2]+r[1]+d,min(dp[i-1][0][0],min(dp[i-1][1][0],dp[i-1][2][0]))+r[2]+d+d+r[1]+d);
  		dp[i][1][0]=min(min(dp[i-1][0][1],dp[i-1][1][1])+a[i]*r[1]+r[1]+r[1]+d,min(dp[i-1][0][0],min(dp[i-1][1][0],dp[i-1][2][0]))+a[i]*r[1]+r[1]+d+d+r[1]+d);
  		dp[i][0][1]=min(min(min(dp[i-1][0][0],dp[i-1][0][1]),min(dp[i-1][1][0],dp[i-1][1][1])),dp[i-1][2][0])+r[2]+d+d+r[1]+d;
  		dp[i][1][1]=min(min(min(dp[i-1][0][0],dp[i-1][0][1]),min(dp[i-1][1][0],dp[i-1][1][1])),dp[i-1][2][0])+a[i]*r[1]+r[1]+d+d+r[1]+d;
  		dp[i][2][0]=min(min(min(dp[i-1][0][0],dp[i-1][0][1]),min(dp[i-1][1][0],dp[i-1][1][1])),dp[i-1][2][0])+a[i]*r[1]+r[3]+d;
```

---

