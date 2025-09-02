# 「CMOI R1」mex1

## 题目背景

小 U 对于从一个集合映射到一个数的函数很感兴趣，而 $\text{mex}$ 是一个很好的例子。

$\text{mex}(S)$ 指的是在集合 $S$ 中没有出现过的最小非负整数。

## 题目描述

多组数据。

每组数据，给定 $c$，要求构造序列 $a_1,a_2,...,a_n\in [0,2\times 10^9]$ 满足 

$$\sum\limits_{S\neq \emptyset,S\subseteq \{1,2,...,n\}}\text{mex}(a_{S_1},a_{S_2},...,a_{S_{|S|}})=c$$


其中要求 $1\le n\le40$。可以证明在该题的数据范围内如果存在解，则在 $1\le n\le 40$ 时一定存在解。

## 说明/提示

### 样例解释

我有一个绝妙的解释，可惜这里写不下。

### 数据范围

$id$ 为 $\text{subtask}$ 编号。

|$id$|特殊性质|分数|$id$|特殊性质|分数|
|-:|-:|-:|-:|-:|-:|
|$1$|$c\le10$|$3$|$6$|$c\le1\times 10^6$|$15$|
|$2$|$c\le30$|$6$|$7$|$T\le 10$|$5$|
|$3$|$c\le500$|$6$|$8$|$T\le 5\times 10^4$|$15$|
|$4$|$c\le2\times 10^3$|$5$|$9$|$T\le 8\times 10^4$|$10$|
|$5$|$c\le1\times 10^5$|$20$|$10$||$15$|

对于 $100\%$ 的数据，$T\le 10^5$，$0\le c\le 2\times 10^9$。

### 提示

由于部分 STL 的常数较大，如果认为你的时间复杂度没有问题却 TLE，请不要使用 STL。

请注意输出效率，这里提供一种快写模板（请不要用以下代码输出负数）：

```cpp
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
```

## 样例 #1

### 输入

```
5
120
8128
248
0
5```

### 输出

```
7
1 9 1 9 8 1 0
13
1 1 4 5 1 4 1 9 1 9 8 1 0
8
1 2 3 9 0 7 3 8
7
1 2 3 9 7 3 8
-1```

# 题解

## 作者：Grand_Dawn (赞：8)

## mex1 题解

### checker 

解决该问题，知道如何写 checker 是必要的。

首先，如果 $a_i>n$，则可以直接令 $a_i\leftarrow n$，因为一个子集最多有 $n$ 个元素，$\text{mex}$ 最大为 $n-1$。

又可以发现相同的数字之间没有区别，所以可以设 $\text{calc}(n,cnt_0,cnt_1,\cdots,cnt_n)$ 表示所有子集 $\text{mex}$ 求和。

如果不选取 $0$，该部分答案显然为 $0$。

如果选取了至少一个 $0$，那么共有 $2^{cnt0}-1$ 种选取 $0$ 的方案。

而对于选取非 $0$ 的元素，$ans=\text{calc}(n-cnt_0,cnt_1,\cdots,cnt_n)$ 已经计算出所有这些元素 $-1$ 的子集 $\text{mex}$ 求和。

而且又有这些子集共有 $2^{n-cnt_0}$ 个。因此，答案为 $(ans+2^{n-cnt_0})(2^{cnt_0}-1)$。 

因此可以在 $\Theta(n)$ 的时间复杂度内算出答案。

### 性质

显然以上的过程是唯一确定的，可以认为是一种递推过程。

即可以定义 $f(x,n)$ 表示用 $n$ 个元素凑成答案为 $x$ 是否存在解；如果存在解，则记录 $cnt_0$ 可能的值。直接枚举 $cnt_0$ 是否存在解。

递推式：$f(x,n)\overset{\text{or}}\leftarrow f(\frac{x}{2^i-1}-2^{n-i},n-i)$。

边界条件：

1. $f(0,n)=\textbf{true}$，此时需要填入 $n$ 个 $1$ 符合答案。

2. $x>0$ 时 $f(x,0)=\textbf{false}$。

3. $x<0$ 时 $f(x,n)=\textbf{false}$。

如果采用递推可以获得 $55$ 分。采取枚举 $n$ 后记忆化搜索可以获得 $60$ 分。

### 优化下界

可以发现很多记忆化数组中很多的答案都是 $\textbf{false}$，因此可以对于固定的 $n$ 可以找到 $x$ 的上下界使得 $f(x,n)\neq \textbf{false}$。

可以发现，当 $x<2^n$ 时，$f(x,n)\neq\textbf{false}$ 当且仅当 $x=2^n-2^k$（$k$ 为整数且 $0\le k\le n$），以下进行证明：

初始时先令 $a_i=n$，考虑从小到大填入真正的 $a_k$ 的过程，加入 $a_k$ 后，$\text{mex}=c(c\in \mathbb{Z})$ 的数量均为 $2^{n-k}$ 的倍数，在于剩下的 $n-k$ 个 $n$ 可以任意选择选与不选。

若加入 $a_k$ 时 $x$ 发生变化，则由以上性质得至少增加 $2^{n-k}$。

若加入 $a_k$ 时 $x$ 不变化，则 $a_k$ 数组中不存在 $a_k-1$，因此等价于之后均不会增加 $x$。

因此若加入 $a_k$ 之前每个元素均发生变化，则 $x$ 至少为 $\sum\limits_{i=1}^{k}2^{n-i}=2^n-2^k$。又由于是 $2^{n-k}$ 得倍数，且 $x<2^n$，故 $x=2^n-2^k$。

因此证明完毕，构造仅需采用 $k$ 个 $0$ 和 $n-k$ 个 $n$ 即可。

实际上，下界仅需要设定为 $2^{n-1}$ 就可以通过此题。

### 优化上界

可以发现有以下性质：如果 $x$ 取到上界，那么 $cnt_0\ge cnt_1\ge cnt_2\ge\cdots\ge cnt_n$。

证明：如果 $cnt_k<cnt_{k+1}$，那么对比交换 $cnt_k$ 和 $cnt_{k+1}$ 的结果：

那么对于 $c>k+1$ 的 $\text{mex}=c$ 的子集数量为 $\prod\limits_{i=1}^{c-1}(2^i-1)$，数量不变。

对于 $c\le k$ 的  $\text{mex}=c$ 的子集数量为 $\prod\limits_{i=1}^{c-1}(2^i-1)$，数量不变。

而 $\text{mex}=k+1$ 的子集数量 $\prod\limits_{i=1}^{k}(2^i-1)$，数量变多。

因此答案会变大。使用冒泡排序可证明以上性质。

因此使用拆分数暴力枚举可以确定上确界。

实际上，上界仅需要设定为 $n\cdot 2^{n-1}$（所有子集长度之和）就可以通过此题。上界设定为 $n\cdot 2^n$ 应该不能通过。

```cpp
#include<bits/stdc++.h>
#define N 35
#define INF 2000000009
using namespace std;
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int pw[N],mx[N];
template<class first,class second,int C>
struct Unordered_map{
	struct node{
		first t;
		second w;
		int nxt;
	}e[C+9];
	int tot,hd[C+9];
	int hash(first x){
		return x%C;
	}
	second& operator [](first a){
		int x=hash(a);
		for(int i=hd[x];i;i=e[i].nxt){
			if(e[i].t==a)return e[i].w;
		}
		e[++tot].t=a;
		e[tot].nxt=hd[x];
		hd[x]=tot;
		return e[tot].w;
	}
	second find(first a){
		int x=hash(a);
		for(int i=hd[x];i;i=e[i].nxt){
			if(e[i].t==a)return e[i].w;
		}
		return -1;
	}
};
Unordered_map<int,char,300009>mp[N];
int check(int x,int n){
	if(x==0)return 1;
	if(x>mx[n])return 0;
	if(mp[n].find(x)!=-1)return mp[n][x];
	if(x<pw[n])return 0;
	for(int i=1;i<=n;i++){
		if(x%(pw[i]-1))continue;
		if(check(x/(pw[i]-1)-pw[n-i],n-i))return mp[n][x]=i;
	}
	return mp[n][x]=0;
}
void solve(){
	int x;cin>>x;
	for(int n=1;pw[n-1]<=x+1;n++)
		if(check(x,n)){
			int id=0;
			write(n);putchar('\n');
			while(x){
				int pos=mp[n][x];
				for(int i=pos;i>=1;i--)write(id),putchar(' ');
				x=x/(pw[pos]-1)-pw[n-pos];
				n-=pos;id++;
			}
			for(int i=n;i>=1;i--)write(id+1),putchar(' ');
			putchar('\n');
			return;
		}
	puts("-1");
}
int b[39];
int calc(){
	int c=0;while(b[c])c++;
	int ans=0,cnt=0;
	while(c>0){
		ans=(ans+pw[cnt])*(pw[b[--c]]-1);
		cnt+=b[c];
	}
	return ans;
}
int dfs(int x,int lft,int lst=1000000000){
	if(lft==0)return calc();
	int ans=0;
	for(int i=min(lft,lst);i>=1;i--){
		b[x]=i;
		ans=max(ans,dfs(x+1,lft-i,i));
		b[x]=0;
	}
	return ans;
}
int main(){
	//freopen("10-1.in","r",stdin);
	//freopen("a.out","w",stdout);
	pw[0]=1;for(int i=1;i<=31;i++)pw[i]=pw[i-1]*2;pw[32]=INF;
	for(int i=1;i<=31;i++){
		if(i<=28)mx[i]=dfs(0,i);
		else mx[i]=INF;
	}
	for(int i=1;i<=32;i++)
		for(int j=i-1,tmp=0;j>=0&&tmp<=INF;j--){
			tmp+=pw[j];
			mp[i][tmp]=i-j;
		}
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：VainSylphid (赞：0)

好牛好神秘的爆搜题。

大部分内容官方题解已经讲得很清楚了，想学做法先去看官方题解。

但是官方题解优化上界这一部分，这个枚举拆分数也太搞笑了吧，直接用那个 dp 算一下就行了。

具体地，设 $g(i)$ 表示序列长度为 $i$ 时能构造出的最大数，枚举 $0$ 的个数 $j$，显然有：

$$\max((g(i-j)+2^{i-j})\times(2^j-1))\rightarrow g(i)$$

边界条件为 $g(0)=0$。预处理这个东西作为记忆化搜索中的上界，直接拿 $2^{n-1}$ 作为下界卡卡就过了。感觉这样过没啥含金量，官方题解对上下界的分析还是挺牛的。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct hash_map{
    struct Data{
    	ll u;int v,nxt;
    }e[500005];
    const int tmod = 300009;
    int h[300011],cnt;
    int& operator[](ll u)
	{
   	    int hu = u % tmod;
    	for(int i = h[hu];i;i = e[i].nxt)
        	if(e[i].u == u)
				return e[i].v;
    	return e[++cnt] = {u,0,h[hu]},h[hu] = cnt,e[cnt].v;
    }
    hash_map(){cnt = 0,memset(h,0,sizeof(h));}
}mp[33];
ll T,x,c,lim[33];
int solve(ll n,ll s)
{
	if(!s)
		return 1;
	if(!n)
		return 0;
	if(s < (1LL << (n - 1)) || s > lim[n])
		return 0;
	int& t = mp[n][s];
	if(t)
		return (t != -1);
	for(int i = 1;i <= n;i++)
		if(s % ((1LL << i) - 1) == 0 && solve(n - i,s / ((1LL << i) - 1) - (1LL << (n - i))))
			t = i;
	return t ? 1 : 0;	
}
ll ans[43],pos;
void calc(ll n,ll s)
{
	if(!s)
	{
		for(ll i = 1;i <= n;i++)
			ans[++pos] = 1;
		return;
	}
	int t = mp[n][s];
	calc(n - t,s / ((1LL << t) - 1) - (1LL << (n - t)));
	for(ll i = 1;i <= pos;i++)
		ans[i]++;
	pos += t;
}
int main()
{
	scanf("%lld",&T);
	for(ll i = 1;i <= 31;i++)
		for(ll j = 1;j <= i;j++)
			lim[i] = max(lim[i],(lim[i - j] + (1LL << (i - j))) * ((1LL << j) - 1));
	while(T--)
	{
		scanf("%lld",&x);
		bool f = 0;
		for(ll i = 1;i <= 31;i++)
			if(solve(i,x))
			{
				memset(ans,0,sizeof ans),pos = 0,calc(i,x),f = 1;
				break;
			}
		if(!f)
			printf("-1\n");
		else
		{
			printf("%lld\n",pos);
			for(ll i = 1;i <= pos;i++)
				printf("%lld%c",ans[i]," \n"[i == pos]);
		}
	}
    return 0;
}
```

---

