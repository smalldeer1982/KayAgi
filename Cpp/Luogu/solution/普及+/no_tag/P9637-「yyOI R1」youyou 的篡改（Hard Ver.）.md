# 「yyOI R1」youyou 的篡改（Hard Ver.）

## 题目背景

**Easy Version 与 Hard Version 仅最后所求内容不同，其他描述均一致。**

## 题目描述

youyou 准备举办一场比赛，这场比赛有 $n$ 道题，每一道题都有一个难度值 $v_i$。

youyou 给出一个计数分量 $k(k\le n)$，他认为，第 $x(x \geq k)$ 道题的可做性 $a_x$ 应当是第 $1\sim x$ 题所有题目中将难度值从小到大排序后难度较大的 $k$ 道题目难度值之和。

由于第 $1 \sim k-1$ 题难度过于简单，youyou 不想考虑这些题目的可做性。

那么这场比赛的总可做性即为第 $k$ 道题至第 $n$ 道题可做性之和，即 $\sum^{n}_{i=k}a_i$
 的值。

他可以篡改题目 $m$ 的难度为任意正整数。

问：总可做性必须满足在区间 $[l,r]$ 的范围内，那么总可做性有几种取值？

## 说明/提示

### 样例解释#1

你可以改动 $v_1$，$k=1$。

当第一个数改动为 $1$ 时，总难度 $1+2+2+2+2=9$。

当第一个数改动为 $2$ 时，总难度 $2+2+2+2+2=10$。

仅有以上两种取值符合题意，即总难度值等于 $9$ 或 $10$。因此答案为 $2$。

## 数据范围

本题启用 **Subtask**，对于每一个 **Subtask**，你需要通过全部测试点才能得到该部分的分数。

| 子任务编号 | $n$ | 分数 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $\le10$ | $15$ |
| $2$ | $\le10^3$ | $15$ |
| $3$ | $\le10^5$ | $70$ |


对于 $100\%$ 的数据，$1\le k,t \le n \le 10^5$，$1 \le l \le r \le 10^{9}$，$1\le v_i\le10^9$。

## 样例 #1

### 输入

```
5 1 1 5 10
1 2 2 2 2```

### 输出

```
2```

# 题解

## 作者：what_else (赞：2)

# Solution
## Hard Version

感谢 @syksykCCC 对 Easy Ver 的看法与见解，于是有了这道 Hard Ver。

%%% %%%

接下来考虑，在只能篡改一道题难度的情况下，怎样求方案数。

如果用 $t$ 表示篡改后的难度值，用 $f(t)$ 表示篡改难度值为 $t$ 的总可做性，那么 $f(t)$ 单调递增。

但 $f(t)$ 是不是严格单调递增的呢？其实，对于当 $t$ 小于前 $1 \sim m-1$ 个数中 $k$ 个较大者的最小值，$f(t)$ 均相等，即篡改没有影响。

但是大于时，这就严格单调递增了。

那么解法好想：提前处理以上的非单调情况，然后二分 $a_m$ 的上下界，$a_m$ 的单调取值显然就是 $[l,r]$ 的取值。

总时间复杂度为 $O(n \log n \log V)$。

感谢 @[syksykCCC](https://www.luogu.com.cn/user/51971) 对此题的帮助与支持！ %%%

---

## 作者：Spouter_27 (赞：1)

设第 $ m $ 个题的难度为 $ t $，不难发现总可做性 $ f(t) $ 满足关于 $ t $ 单调不减，而且如果第 $ m $ 个题至少贡献了一次答案的话 $ f(t) $ 关于 $ t $ 单调递增。

二分 $ t $ 最大最小分别是多少满足最终的总可做性在区间之内，设二分出的 $ t $ 最大最小值分别是 $ maxt,mint $，那么对于大多数情况， $ maxt-mint+1 $ 就是最终答案。

下面是特殊情况：

如果不存在 $ maxt $ 和 $ mint $，即在 easy var 中答案是  $ -1 $，那么输出 $ 0 $。

如果 $ t $ 等于 $ maxt $ 和 $ mint $ 时第 $ m $ 个题都没有贡献答案，那么总可做性只有一种取值。

否则在此基础上找出第 $ m $ 个题至少贡献一次的 $ t $ 值，这个可以在二分的过程中实现。

总复杂度 $ O(n\log n\log V) $，细节挺多。

这是赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define deb(x) cerr<<"Line: "<<__LINE__<<", val= "<<x<<"; \n"
typedef long long ll;
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=2e5+10;
inline ll read(){
	ll a=0,x=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	x=-x;
		c=getchar();
	}
	while(isdigit(c)){
		a=a*10+c-'0';
		c=getchar();
	}
	return a*x;
}
ll flag;
ll n,v[N],m,k,l,r;
ll ldl=1,rr=1e9,ansm=0,anso=0;
ll sum=0,ans=0;
priority_queue<ll> q;
ll count(ll mid){
	v[m]=mid;
	sum=ans=0;
	while(!q.empty()){
		q.pop();
	}
	for(int i=1;i<k;i++){
		sum+=v[i];
		q.push(-v[i]);
	}	
	sum+=v[k];
	ans+=sum;
	q.push(-v[k]);
	flag=1;
	for(int i=k+1;i<=n;i++){
		if(v[i]>-q.top()){
			sum+=v[i]+q.top();
			q.push(-v[i]);
			q.pop();
		}
		else if(i==m){
			flag=0;
		}
		ans+=sum;
	}
	return ans;
}
signed main(){
	n=read(),m=read(),k=read(),l=read(),r=read();
	for(int i=1;i<=n;i++){
		v[i]=read();
	}
	while(ldl<=rr){
		ll mid=(ldl+rr)/2;
		ll ans=count(mid);
		if(ans>r){
			rr=mid-1;
		}
		else if(ans<l){
			ldl=mid+1;
		}
		else{
			ansm=mid;
			ldl=mid+1;
		}
	}
	ldl=1,rr=1e9,anso=0;
	while(ldl<=rr){
		ll mid=(ldl+rr)/2;
		ll ans=count(mid);
		if(flag==0){
			ldl=mid+1;
		}
		else if(ans>r){
			rr=mid-1;
		}
		else if(ans<l){
			ldl=mid+1;
		}
		else{
			anso=mid;
			rr=mid-1;
		}
	}
	if(anso==0&&ansm!=0){
		puts("1");
		return 0;
	}
	if(anso==0&&ansm==0){
		puts("0");
		return 0;
	}
	ll ans=count(anso-1);
	if(ans>=l&&ans<=r&&flag==0){
		assert(count(anso)!=ans);
		assert(count(anso-2)==ans);
		anso--;
	}
	printf("%lld\n",ansm-anso+1);
	return 0;
}
/*
6 1 2 20 90
1 9 1 9 8 1
*/
```


---

## 作者：DFM_O (赞：0)

## [P9637题目](https://www.luogu.com.cn/problem/P9637)

### 解题思路
我们很容易就能发现，$v_m$ 越大，可做性之和就越大。

但是当 $v_m$ 小于 $v_1∼v_{m-1}$ 中第 $k$ 难的题目的难度值时，可做性之和相等，即篡改 $v_m$ 的值无意义。

当然，当 $m\le k$ 时，在任何情况下，篡改 $v_m$ 的值都是有意义的。

此时我们只需要用二分分别求出在满足条件的情况下 $v_m$ 的最大值和最小值，并去除篡改 $v_m$ 无意义的情况即可。

至于怎么求可做性之和的方法我就不说了，不会的可以去看 [Easy Ver. 的题解](https://www.luogu.com.cn/blog/wangyuningqyx/solution-p9636)（~~不会有人连 Easy Ver. 都没做就来做 Hard Ver. 吧~~）。

### Code
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
#define int long long//记得开long long
priority_queue<int,vector<int>,greater<int>>c;//优先队列
int v[100001];
int n,k,m,l,r,maxm=-1,minm=1000000001,ans;
int kz()//计算可做性之和
{
	int zs=0,s=0;
	for(int i=1;i<=c.size();)//清空队列
		c.pop();
	for(int i=1;i<=k;++i)
		c.push(v[i]),s+=v[i];
	zs+=s;
	for(int i=k+1;i<=n;++i)
	{
		if(v[i]>c.top())
		{
			s=s+v[i]-c.top(),zs+=s;
			c.pop(),c.push(v[i]);
		}
		else
			zs+=s;
	}
	return zs;
}
void efmax()//用二分求出m的最大值
{
	int ll=1,rr=1000000000,mid,maxx=-1;//maxx用来可做性之和的记录最大值
	while(ll<=rr)
	{
		mid=rr-(rr-ll)/2,v[m]=mid;
		int zzs=kz();
		if(zzs>=l&&zzs<=r)
		{
			maxx=max(maxx,zzs),maxm=max(maxm,mid);
			ll=mid+1;
		}
		else
		{
			if(zzs<l)
				ll=mid+1;
			if(zzs>r)
				rr=mid-1;	
		}
	}
	return;
}
void efmin()//用二分求出m的最小值
{
	int ll=1,rr=1000000000,mid,minn=1e18;//minn用来可做性之和的记录最大值
	while(ll<=rr)
	{
		mid=rr-(rr-ll)/2,v[m]=mid;
		int zzs=kz();
		if(zzs>=l&&zzs<=r)
		{
			minn=min(minn,zzs),minm=min(minm,mid);
			rr=mid-1;//注意这里和求最大值时不一样
		}
		else
		{
			if(zzs<l)
				ll=mid+1;
			if(zzs>r)
				rr=mid-1;	
		}
	}
	return;
}
signed main()//这里要用signed
{
	scanf("%lld%lld%lld%lld%lld",&n,&m,&k,&l,&r);
	for(int i=1;i<=n;++i)
		scanf("%lld",&v[i]);
	efmin(),efmax();
	if(m>k)//m小于等于k时无需进行操作
	{
		for(int i=1;i<=c.size();)
			c.pop();
		for(int i=1;i<=m-1;i++)
			c.push(v[i]);
		for(int i=1;i<=m-1-k;i++)
			c.pop();
		minm=max(minm,c.top());//去掉篡改v[m]但对可做性之和无影响的可能
	}
	if(minm>maxm)//若此时minm大于maxm,输出0,不进行此特判可能会输出负数
		ans=0;
	else	
		ans=maxm-minm+1;
	printf("%lld\n",ans);
    return 0;
}
```

---

