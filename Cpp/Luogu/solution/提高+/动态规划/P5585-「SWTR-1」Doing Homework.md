# 「SWTR-1」Doing Homework

## 题目背景

小 $\mathrm{A}$ 每天都有很多作业要写。

## 题目描述

每天，小 $\mathrm{A}$ 都要写至少 $w$ 吨的作业，如果他达不到目标，就会受到小 $\mathrm{S}$ 制裁并且当场去世。

小 $\mathrm{A}$ 有 $x$ 点精力，每次写作业都会降低小 $\mathrm{A}$ 的精力，且**不可逆**，小 $\mathrm{A}$ 的精力不可以降为负数。

现在，有 $n$ 种作业给小 $\mathrm{A}$ 选。

每种作业有如下的属性：

$x_i:$ 消耗的精力，即写一份这种作业需要 $x_i$ 的精力。

$w_i:$ 重量，即这种作业一份有 $w_i$ 吨。

$t_i:$ 截止日期，即从今天过了 $t_i$ 天之后，这个作业不可以再写。

**每种作业都有无限个。**

因为他的作业实在是多得写不完，所以请你为他安排一种写作业的方案，**最大化**他能存活的天数，当存活天数已最大化时，最大化他剩余的精力。

## 说明/提示

---

### 样例说明

第一天，小 $\mathrm{A}$ 选择写 $2$ 份第二种作业，重量为 $2 * 2=4$，剩余精力为 $30-2 * 3=24$。

第二天，小 $\mathrm{A}$ 选择写 $2$ 份第二种作业，重量为 $2 * 2=4$，剩余精力为 $24-2 * 3=18$。

至此，不可以再写第二种作业 $(t_2=2)$。

第三天，小 $\mathrm{A}$ 选择写 $1$ 份第三种作业，重量为 $4$，剩余精力为 $18-8=10$。

第四天，小 $\mathrm{A}$ 选择写 $1$ 份第三种作业，重量为 $4$，剩余精力为 $10-8=2$。

至此，不可以再写第三种作业 $(t_3=4)$。

小 $\mathrm{A}$ 没有精力再去写别的作业了，所以他最多能活 $4$ 天，剩余精力为 $2$。

可以证明，找不到比该方案更优的方案了。

---

### 数据范围

![](https://cdn.luogu.com.cn/upload/image_hosting/meko5h7g.png)

---

对于 $n \leq 5000$ 中 $25\%$ 的数据，有时间限制 $1s$，空间限制 $256MB$。

其余测试点时间限制 $400ms$，空间限制 $8MB$。

## 样例 #1

### 输入

```
30 4
3
5 3 8
3 2 2
8 4 4```

### 输出

```
4 2```

## 样例 #2

### 输入

```
100 3
2
3 2 8
2 1 5```

### 输出

```
8 57```

# 题解

## 作者：Alex_Wei (赞：11)

$\color{#9400d3}T4.\ Doing\ Homework$

[$\color{#9400d3}\text{题面}$](https://www.luogu.org/problem/P5585)

官方题解

~~我也不知道这个部分分给的有什么用~~

---

$Sol\ 1\ :\ 5-15\ pts$

爆搜，期望得分 $5-15\%$ （要看你怎么搜）

~~反正我也没写过爆搜~~

---

$Sol\ 2\ :\ 75-100\ pts$

（大多数应该能拿到 $100\%$，除非被卡空间）

一看题就应该知道 时间 $O(nk)$，空间 $O(k)$

如果没有时间的限制，那么这道题目就是**完全背包**

但有了时间怎么办 $qwq?$

不慌，将所有种类的作业按时间**从大到小**排

每次一种作业去更新 $dp$ 数组

再 **对于每一个更新** 求出最小（精力）花费

最后求出天数不就行了嘛 $awa$

记得用 $long\ long$ 啊！

---

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize(3)
#define ll long long
ll read()//快读
{
	ll x=0,sign=1;char s=getchar();
	while(!isdigit(s))s=getchar();
	while(isdigit(s))x=(x<<1)+(x<<3)+(s^48),s=getchar();
	return x;
}
const ll N=5e3+2;
const ll INF=1e18;

struct homew{
	ll x,w,t,cos; 
}k[N];
bool cmp(homew a,homew b){return a.t>b.t;}//将作业按时间大小排序

ll min(ll a,ll b){return a<b?a:b;}//手写 min 函数
ll x,w,n,dp[N<<1];

void init()
{
	x=read(),w=read(),n=read();
	for(int i=1;i<=n;i++)
		k[i].x=read(),k[i].w=read(),k[i].t=read();//读入
	sort(k+1,k+n+1,cmp);//sort 
	memset(dp,0x3f,sizeof(dp));//dp 赋初值
	dp[0]=0;
}

void DP()
{
	for(int i=1;i<=n;i++){
		if(k[i].w>=w)//特判一下 w[i]>=w 的情况
			dp[w]=min(dp[w],k[i].x);
		else
			for(int j=k[i].w;j<=w+k[i].w;j++)//完全背包
				dp[j]=min(dp[j],dp[j-k[i].w]+k[i].x);
		k[i].cos=INF;//赋初值
		for(int j=w;j<=(w<<1);j++)
			k[i].cos=min(k[i].cos,dp[j]);//找出最小值
	}
}

void answer()
{
	for(int i=n;i>0;i--){//时间从小到大遍历
		ll cos=k[i].cos*(k[i].t-k[i+1].t);//总花费
		if(cos<=x)x-=cos;//有足够的精力
		else cout<<k[i+1].t+x/k[i].cos<<" "<<x%k[i].cos<<endl,exit(0);//否则输出并退出
	}
	cout<<k[1].t<<" "<<x;//特判天天能写完作业
}

int main()
{
	init();
	DP();
	answer();
	return 0;
}
```

---

## 作者：在想Peach (赞：1)

见数据考虑dp，先预处理每个时间满足最小W的最小代价，dp转移就是一个完全背包，只不过要倒着推（时间点后面的可以用，前面的不行）：

f[i][j]=f[i+1][j];
			
 if(j>=t[i].w)f[i][j]=min(f[i][j],f[i][j-t[i].w]+t[i].val);
 
 发现空间是2mb，开那么大会gg，自然想到滚动数组，并且再开一个数组只记录每个时间点的最优解即可。
 
 if(j>=w)fl[i]=min(fl[i],f[zz][j]);（zz是滚动数组的变量）
 
 然后每个时间点枚举即可（一开始完全背包被卡t了瞎改了一个容量上限就~~由于数据水~~过了）
 
 ```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int val,w,t;
	friend bool operator <(node a,node b)
	{	
		return a.t<b.t;
	}
}t[5005];
int val,w,n,mx,ans;
int f[2][10005],fl[10005];
inline int read()
{
	char z=getchar();int x=0,y=1;
	while(z<'0'||z>'9'){if(z=='-')y=-1;z=getchar();}
	while(z<='9'&&z>='0'){x=x*10+z-'0';z=getchar();}
	return x*y;
}
int main()
{
	val=read();w=read();
	n=read();
	mx=w+1000;
	for(int i=1;i<=n;i++)
	{
		t[i].val=read();
		t[i].w=read();
		t[i].t=read();
		mx=max(mx,t[i].w+1000);
	}
	sort(t+1,t+n+1);
	memset(f,0x3f,sizeof(f));
	int zz=0;
	f[zz][0]=0;
	for(int i=n;i>=1;i--)
	{
		fl[i]=999999999;
		zz^=1;
		f[zz][0]=0;
		for(int j=1;j<=mx;j++)
		{
			f[zz][j]=f[zz^1][j];
			if(j>=t[i].w)f[zz][j]=min(f[zz][j],f[zz][j-t[i].w]+t[i].val);
			if(j>=w)fl[i]=min(fl[i],f[zz][j]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(t[i].t!=t[i-1].t)
		{
			int cheap=fl[i];
			int u=val/cheap;
			if(u>=t[i].t-t[i-1].t)ans+=t[i].t-t[i-1].t;
			else 
			{
				ans+=u;
				val-=cheap*u;
				break;
			}
			val-=cheap*(t[i].t-t[i-1].t);
		}
	}
	printf("%d %d\n",ans,val);
	return 0;
}
```


---

