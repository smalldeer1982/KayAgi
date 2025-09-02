# [AGC057D] Sum Avoidance

## 题目描述

给定正整数 $S, K$。如果正整数序列 $A = (A_1, A_2, \ldots, A_N)$ 满足以下两个条件，则称其为**好数列**。

- $1 \leq A_1 < A_2 < \cdots < A_N \leq S - 1$。
- 对于任意非负整数序列 $(x_1, x_2, \ldots, x_N)$，都有 $\sum_{i=1}^N A_i x_i \neq S$。

在所有项数 $N$ 最大的好数列中，选择字典序最小的那个，记为 $A = (A_1, A_2, \ldots, A_N)$。请输出该数列的第 $K$ 项 $A_K$。如果 $K > N$，则输出 $-1$。

给定 $T$ 组测试数据，请分别输出每组的答案。

## 说明/提示

### 数据范围

- $1 \leq T \leq 1000$
- $3 \leq S \leq 10^{18}$
- $1 \leq K \leq S - 1$

### 样例解释 1

当 $S = 3, 7, 10$ 时，$A$ 分别为：

- $S=3$ 时：$A = (2)$
- $S=7$ 时：$A = (2, 4, 6)$
- $S=10$ 时：$A = (3, 6, 8, 9)$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
13
3 1
3 2
7 1
7 2
7 3
7 4
10 1
10 2
10 3
10 4
10 5
2022 507
1000000000000000000 999999999999999999```

### 输出

```
2
-1
2
4
6
-1
3
6
8
9
-1
1351
-1```

# 题解

## 作者：樱雪喵 (赞：9)

一年前看了一天没看懂的题，现在终于知道题解在说啥了。

## Description

给定一个正整数 $S$ ，称一个正整数集合 $A$ 是好的，当且仅当它满足以下条件：

1. $A$ 中所有元素均在 $[1,S)$ 之间；
2. 不能用 $A$ 中若干元素相加得到 $S$，同一元素可以多次使用。

设集合 $A$ 为满足元素个数最多的条件下，字典序最小的好的集合。多次询问，给定 $S$ 和 $k$，求集合 $A$ 第 $k$ 小的元素，无解输出 `-1`。

$ T \le 10^3,\, S \le 10^{18} $。

## Solution

### Part 1.

> 引理 1. 设 $|A|$ 表示集合 $A$ 的元素个数，则 $|A|=\left\lfloor \frac{S-1}{2}\right\rfloor$。

首先我们证明 $|A|$ 的上界：若 $i\in A$，则必有 $S-i\notin A$。同理，若 $S\bmod 2=0$，则有 $\frac{S}{2}\notin A$。故我们可以把 $[1,S)$ 分为 $\left\lfloor \frac{S-1}{2}\right\rfloor$ 对数，其中每对数至多有一个被选择。

令 $A=\{\left\lfloor \frac{S-1}{2}\right\rfloor+1,\dots,S-1,S\}$，则 $A$ 中任意两个元素之和 $> S$，该构造必然合法。即对于任意的 $S$，我们都能构造出至少一组令 $|A|$ 取到上界的解。

也就是说我们最后的答案集合中，对于 $i\neq \frac{S}{2}$，$i\in A$ 和 $S-i\in A$ 必然恰好满足其一。令 $A$ 中 $\le \left\lfloor \frac{S-1}{2}\right\rfloor$ 的元素构成集合 $B$，则我们可以在只知道 $B$ 的情况下还原出 $A$。

> 引理 2. 若 $a,b\in B,a+b\le \left\lfloor \frac{S-1}{2}\right\rfloor$，则 $a+b\in B$。

考虑反证，若 $a+b\notin B$，则 $S-a-b\in A$。又因为 $a,b\in A$，$A$ 集合能组合出 $S$，不合法。


> 引理 3. 若集合 $B$ 中的元素不能相加得到 $S$，则它对应的集合 $A$ 也合法。

依然反证，若集合 $B$ 合法，但集合 $A$ 不合法，则代表存在一个 $x> \left\lfloor \frac{S-1}{2}\right\rfloor$，能与 $B$ 中的若干个元素组合出 $S$。那么有 $S-x\notin B$，且 $B$ 中元素可以组合出 $S-x$。这与引理 2 矛盾。

由于 $B$ 的元素个数对 $|A|$ 不会产生影响，至此我们考虑最小化 $B$ 的字典序即可。

### Part 2.

最小化 $B$ 的字典序，有显然正确的贪心：从小到大枚举每个数，如果加了不会造成不合法，就把它加进 $B$。我们要做的事是快速维护这个过程。

考虑第一个被加进 $B$ 的数，不难发现它是**第一个不是 $S$ 的约数**的数。那么设这个数为 $d$，则有 $\text{lcm}(1,2,\dots d-1) \mid S$。计算得到当 $S$ 取上界 $10^{18}$ 时，仍有 $d\le 43$。

那么我们可以把贪心过程中加入 $B$ 中的数 $x$ 分为两种情况：

- 这个数已经可以被 $B$ 中原有的数表示，根据引理 2 必须加入；
- 这个数不能被表示，且加入后也不能与其它数表示出 $S$，也应该贪心地加入。

从模 $d$ 的剩余系角度考虑，若 $x$ 以第二种方式加入，则它与所有已经在 $B$ 中的数模 $d$ 不同余。所以至多有 $d$ 个数以第二种方式被加入。

考虑维护一个形如同余最短路的东西，设 $f_i$ 表示当前最小能被 $B$ 集合表示的 $\bmod\ d=i$ 的数。那么只需求出最后的 $f$ 数组即可还原出 $B$ 集合，而数组大小只有 $d$，复杂度可以接受。

第一种情况对 $f$ 数组不会产生任何影响，我们只需考虑第二种情况的贡献。

设下一个以第二种方式加入的数为 $v$，并令 $x=v\bmod d$，那么首先 $v$ 应当满足 $f_x>v$。加入后 $B$ 合法的充要条件是用 $v$ 更新数组后仍满足 $f_{S\bmod d}> S$。用 $v$ 更新的过程有如下式子：

$$\text{for}\  i\in [1,d),\ f_{(x+ix)\bmod d}\gets f_x+ ix$$

枚举 $x$，则 $f_{S\bmod d}$ 更新后的值随着 $v$ 的增大单调不降。可以考虑求出 $v$ 的下界：

$$v_x=\max_{i=1}^{d-1} \left\lfloor\frac{f_{(S-ix)\bmod d}}{i}\right\rfloor +1$$

那么下一个要添加的 $v$ 就是 $\min v_x$，添加以后对 $f$ 数组进行更新即可，重复该过程直到找不到一个合法的 $v$。

### Part 3.

根据最终的 $f$ 数组还原答案。

对于给定的 $x$，则求得集合 $B$ 中 $\le x$ 的元素个数为

$$\sum_{i=0}^d \left\lfloor\frac{x-f_i}{d}\right\rfloor+[i\neq 0]$$

那么对于 $\le \left\lfloor\frac{S-1}{2}\right\rfloor$ 的答案我们可以直接二分出第 $k$ 小的值，另一半也可以类似地反过来二分。

[submission](https://atcoder.jp/contests/agc057/submissions/46217081)

---

## 作者：St_john (赞：3)

# [[AGC057D] Sum Avoidance](https://www.luogu.com.cn/problem/AT_agc057_d)

这个类似反向同余最短路。  
毕竟如果给 $n,A$，是可以求出 $S$ 的最大值的。这就是 [P2662](https://www.luogu.com.cn/problem/P2662) 。  

但是，这给我们 $S$，让我们求最大的 $n$ 和字典序最小的 $A$，似乎很难办。  



------------


先确定答案的范围。  
$n<K$ 输出 `-1`  即可，这引导我们根据 $S$ 判断 $n$ 的范围。  
首先，如果 $i,S-i$ 同时在 $A$ 内，显然是不对的。  
如果 $S$ 为偶数，$\frac{S}{2}$ 也是不能放进去的。  
如果把 $[\lfloor \frac{S}{2} \rfloor +1 ,S-1]$ 放入 $A$，显然这也是 $n$ 最大的，这一定是可以的。  
所以 $n$ 的最大值为 $(S-1)-(\lfloor \frac{S}{2} \rfloor +1)+1=\lfloor \frac{S-1}{2} \rfloor$。  



------------



由于要字典序最小，所以直接将 $[\lfloor \frac{S}{2} \rfloor +1 ,S-1]$ 放入集合 $A$ 不一定是最优的。  

所以，答案必然有一些 $< \lceil \frac{S}{2} \rceil$ 的数在 $A$ 中。  

称 $[\lfloor \frac{S}{2} \rfloor +1 ,S-1]$  为标准集合 $A'$。  
那么答案集合 $A''$ 一定是 $A'$ 中的一些元素 $i$，换成 $S-i$ 得到的。  

令 $A$ 中 $< \lceil \frac{S}{2} \rceil$ 的元素构成的集合为 $B$。  
由上可知，只要合法，就可以根据 $B$ 得出 $A$。  

接下来证明 $B$ 合法， $A$ 即合法。  


------------

* $\forall a,b \in B\land a+b<\lceil \frac{S}{2} \rceil,a+b\in B$ 。   

这是条很显然的性质，如果 $a+b$ 不在 $B$ 中，那么 $S-(a+b)$ 一定在 $A$ 中，就不合法了。  

假设 $A$ 是不合法的，其中组成 $S$ 的数存在一个来自 $A-B$ ，即 $\geqslant \lfloor \frac{S}{2} \rfloor +1$ ，则一定不满足 $B$ 的性质。  

所以说，只要 $B$ 满足条件，$A$ 一定满足条件。  
 

------------
况且 $A$ 的字典序取决于 $B$。   
我们只要构造字典序最小的 $B$ 即可。  



------------


从小到大，贪心地向 $B$ 中加数，判断是否可以。  
第一个加入的数一定是最小的且和 $S$ 互质的数。  
$lcm_{i=1}^{43} > 10^{18}$，可知这个数 $k$ 一定 $\leqslant 43$。  

考虑加入 $B$ 的两种方式。  
1. 可以由 $B$ 中元素构成，直接加入。
1. 不是 $1$ 的情况，加入 $B$ 依然合法，那就加入。  

有第一个数 $k$ 为基石，我们发现，按第二种方式加入的数一定是和 $B$ 中所有的数 $\pmod k$ 不同余，否则是第一种方式加入。    
所以第二种加入方式，最多用 $k$ 次。  

设 $f_i$ 表示 $B$ 中能拼出最小的数 $\equiv i \pmod k$。  
$f$ 不会被第一种加入方式所影响，只会被第二种加入方式影响。  
设 $v$ 能以第二种方式加入，其中 $v\equiv x \pmod k$，当且仅当 $f_x >v\land f_{S \bmod k} >S$。  
加入 $v$ 会对 $f$ 产生如下更新。  
$$f_i \gets \min_{j=1}^{k-1} \big ( f_{(i-j\times v) \bmod k} +v\times k \big )$$

根据加入 $v$ 的条件，可以得出 $v$ 的下界，选出下界的数加入即可。  
接下来就是类似同余最短路的更新。  


------------

构造出 $B$ 来了，我们就可以根据 $f$ ，算出小于某个数的元素有多少个。  
具体方法，也是依据同余最短路，做法和 [P3403](https://www.luogu.com.cn/problem/P3403) 类似。  

通过二分，找到第 $K$ 个元素的位置即可。  

如果不在 $B$ 里，可以用类似的反向二分来算。  


```cpp
#include<cstdio>
#include<queue>
#define _for(i,a,b) for(register int i=(a);i<=(b);++i)
#define __for(i,a,b) for(register int i=(a);i>=(b);--i)
#define Re register int
#define il inline
#define pc putchar
using namespace std;
typedef long long ll;
const int N=5e5+10,M=3e3+10,mod=1e9+7;
il ll re(){
    ll x=0;
    bool f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
        f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return f?-x:x;
}
void pr(ll x){
    if(x<0) x=-x,pc('-');
    if(x>9) pr(x/10);
    pc(x%10|48);
}

ll f[50];
queue<int> q;
bool in[50];
int k;
const ll inf=1e18;
void spfa(ll add){
	for(Re i=0;i<k;++i)
			q.push(i),in[i]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		in[x]=0;
		int y=(x+add)%k;
		if(f[y]>f[x]+add){
			f[y]=f[x]+add;
			if(!in[y]){
				q.push(y);
				in[y]=1;
			}
		}
	}
}
il ll max(ll a,ll b){
	return a>b?a:b;
}
il ll calc(ll h){//f[0]=0 包含0了，而原题没有
	ll ans=0;
	for(Re i=0;i<k;++i)
		if(h>=f[i])
			ans+=(h-f[i])/k+1;
	return ans-1;
}

signed main(){
	__for(_,re(),1){
		ll S=re(),K=re();
		if(K>(S-1)/2){
			pr(-1),pc('\n');
			continue;
		}
		k=1;
		while(S%k==0) ++k;
		for(Re i=1;i<k;++i)
			f[i]=inf;
		while(1){
			ll v=inf;
			for(Re x=1;x<k;++x){
				ll xj=0;
				for(Re j=1;j<k;++j){
					int last=((S-j*x)%k+k)%k;
					xj=max(xj,(S-f[last])/j+1);
				}
				if((xj+k-x)%k)
					xj+=(k-(xj+k-x)%k);
				//使下界符合条件
				if(f[x]>xj&&xj<v)
					v=xj;
			}
			if(v>=S/2) break;
			spfa(v);
		}
		ll l=1,r=S/2,ans=-1;
		while(l<=r){
			ll mid=(l+r)/2;
			if(calc(mid)>=K)
				ans=mid,r=mid-1;
			else l=mid+1;
		}
		if(ans!=-1){
			pr(ans),pc('\n');
			continue;
		}
		l=1,r=S/2;
		K=(S-1)/2-K+1;
		//K之后（包含K），有多少个元素
		while(l<=r){//反向二分
			ll mid=(l+r)/2;
			if(mid-calc(mid)>=K)
				ans=mid,r=mid-1;
			else l=mid+1;
		}
		pr(S-ans),pc('\n');
	}
    return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc057_d)

**题目大意**

> 给定 $n$，定义一个 $[1,n)$ 的子集 $S$ 是好的当且仅当不能从 $S$ 中选出若干元素求和得到 $n$（可以重复选元素）。
>
> 取所有好的集合中最大的一个，有多个取从小到大排序后字典序最小的集合 $S$，求出其中的第 $k$ 个元素。
>
> 数据范围：$n\le 10^{18}$。

**思路分析**

显然集合最大大小就是 $\left\lfloor\dfrac{n-1}2\right\rfloor$，因为所有 $(1,n-1),(2,n-2),\dots$ 的匹配只能每对选一个，即 $i\in S$ 和 $n-i\in S$ 恰有一个成立。

不妨设 $S$ 在 $1\sim \left\lfloor\dfrac{n-1}2\right\rfloor$ 范围内的集合是 $A$，那么我们知道 $A$ 就能还原 $S$，并且只要最小化 $A$ 的字典序即可。

我们发现如果 $x,y\in  A$ 且 $x+y\le \left\lfloor\dfrac{n-1}2\right\rfloor$，那么必须有 $x+y\in A$，否则 $n-x-y\in S\setminus A$，则 $x,y,n-x-y$ 加起来得到 $n$。

其次，如果 $A$ 中元素加起来得不到 $n$，那么 $S$ 中元素加起来也得不到 $n$。

> 考虑反证法，如果存在一种选元素的方法选了 $S\setminus A$ 中元素，显然至多选一个，因为选两个的和就 $>n$ 了。
>
> 那么设选出了 $x\in S\setminus A$，则 $A$ 中能选出若干元素和为 $n-x$，但 $n-x\le \left\lfloor\dfrac{n-1}2\right\rfloor$ 且能被 $A$ 中元素表示，则根据刚才的结论，一定有 $n-x\in A$，从而导出矛盾。

那么求 $A$ 的过程就可以贪心，从小到大考虑每个元素，如果加入后依然不能表示出 $n$ 就加入，并且把 $\le \left\lfloor\dfrac{n-1}2\right\rfloor$ 的子集和加入 $A$。

考虑 $A$ 中最小的元素，即第一个 $p$ 满足 $p\nmid n$，此时 $\mathrm{lcm}(1,2,\dots,p-1)\mid n$，因此 $p\le 43$。

那么加入 $p$ 后会加入所有 $\le \left\lfloor\dfrac{n-1}2\right\rfloor$ 的倍数。

加入某个 $x$ 后又会加入所有 $x+p,x+2p,\dots$，因此可以考虑同余最短路。

设 $f_i$ 表示当前 $A$ 中元素能组合出的最小的 $\bmod p=i$ 的数。

加入一个 $x$ 就会让 $f_i\gets f_{(i-kx)\bmod n}+kx$，可以转两圈更新。

一个元素加入后合法当且仅当加入后 $f_{n\bmod p}>n$，因此对于所有 $i$，都有 $x\ge \left\lfloor\dfrac{n-f_{(n-ix)\bmod p}}{i}\right\rfloor+1$。

枚举每个 $x\bmod p$ 算出最小的 $x$，取出所有可能的 $x$ 中最小的一个加入。

求答案可以二分，求出 $A$ 中 $\le k$ 的元素个数，即 $\sum\limits_{i=0}^{p-1} \left\lfloor\dfrac{k-f_i}{p}\right\rfloor+[i>0]$。

时间复杂度 $\mathcal O(p^3+p\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=1e18;
ll n,m,p,f[45];
ll cnt(ll x) {
	ll s=0;
	for(int i=0;i<p;++i) if(f[i]<=x) s+=(x-f[i])/p+(i>0);
	return s;
}
void solve() {
	scanf("%lld%lld",&n,&m);
	if(m>(n-1)/2) return puts("-1"),void();
	for(p=1;n%p==0;++p);
	f[0]=0,fill(f+1,f+p,inf);
	while(true) {
		ll v=inf;
		for(int x=1;x<p;++x) {
			ll c=0;
			for(int i=1;i<p;++i) c=max(c,(n-f[(n+(p-x)*i)%p])/i+1);
			while(c%p!=x) ++c;
			if(c<f[x]) v=min(v,c);
		}
		if(v>(n-1)/2) break;
		f[v%p]=v;
		for(int r=0;r<__gcd(v,p);++r) {
			for(int i=r,c=0;c<2;i=(i+v)%p,c+=(i==r)) {
				f[(i+v)%p]=min(f[(i+v)%p],f[i]+v);
			}
		}
	}
	if(m<=cnt((n-1)/2)) {
		ll l=1,r=(n-1)/2,z=(n-1)/2;
		while(l<=r) {
			ll mid=(l+r)>>1;
			if(cnt(mid)>=m) z=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",z);
	} else {
		ll l=(n-1)/2+1,r=n-1,z=n-1;
		while(l<=r) {
			ll mid=(l+r)>>1;
			if((n-1)/2-(n-mid-1-cnt(n-mid-1))>=m) z=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",z);
	}
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：2)

update on 01/30/2023：之前题解太抽象了不是给人看的，在 @hyzhutao 的帮助下修改了大部分表述。

## 一、题意

给定一个正整数 $S$ ，称一个正整数集合 $A$ 是好的，当且仅当它满足以下条件：

1. $A$  中元素在 $[0,S)$ 之间

2. 不能用 $A$ 中元素多次相加得到 $S$

考虑所有好的集合中元素数量最大且字典序最小的集合 $A$ ，多次询问，求集合 $A$ 从小到大排序后的第 $k$ 项，或集合大小小于 $k$

$ T \le 1000 , S \le 10^{18} $

其实这个题意写的不太清楚，到底是需要先保证字典序最小还是先保证元素数量最多？所以先澄清一下，题目要求的应当是先保证字典序最小再保证元素个数最多，也就是我们需要做一个简单的的贪心：从 $1$ 扫描到 $S$ ，每次能新加一个元素就加进去，有矛盾加不进去的话就不加。

## 二、一个直观感受

$A_1$ 是**最小的不是** $S$ 的约数的正整数，这一点在我们的前面提到的贪心成立的前提下是显然成立的。

比如 $S = 120$ 则 $A_1 = 7$ 。

所以我们又可以有一个直观感受：这个 $A_1$ 大概不会太大，因为 $S$ 是 $lcm(1, 2, ...A_1 - 1)$ 的倍数。

于是我们可以计算得到： $A_1 \leq 43$ 。

## 三、解决问题

既然 $A_1$ 很小，可以利用 $A_1$ 来解决问题。

下文中设 $A_1=m\leq 43$ ，最终所选数字的集合为 $B$。（和题面有所不同）

- 引理 1. 若 $a,b\in B$ 且 $a+b<S$，则 $a+b\in B$。

$a+b$ 是 $a,b$ 的一个线性组合，若 $a,b$ 在集合 $B$ 中，且此时 $B$ 中元素不能用线性组合表示出 $S$，那么加入 $a+b$ 后也不可能就能表示出 $S$ 了。秉持着能加则加的原则，可以把 $a+b$ 加进 $B$。

更进一步地，若当前 $B$ 中元素为 $A_1,A_2,A_3,...A_r$ 且 $\sum_{i=1}^{r}k_iA_i < S$，则 $\sum_{i=1}^{r}k_iA_i\in B$。

据此可以得出 $m,2m,3m,4m...$ 必定在集合 $B$ 中，但我们不满足于此。把所有 $[1, S - 1]$ 中的正整数按照模 $m$ 的余数分成 $m$ 个剩余类，并将第 $i$ 类中的元素按照升序排序为 $Q_i$。

- 引理 2. $B$ 中含有的第 $i$ 类元素，只要该类非空，则其应该是 $Q_i$ 的一段后缀。

这个引理可以根据引理 1 来说明。

分成 $m$ 类有什么用处呢？只要我们求出了所有第 $i$ 类元素的开头元素 $st_i$，就能知道集合 $B$ 中的所有元素，于是可以用二分查找法找到第 $K$ 个元素。具体实现的方法：二分一个数 $o$，找出每一类中不大于它的元素的个数，即可求出 $o$ 在 $B$ 中的位置。

我们现在只知道 $A_1=m$，$st_0=m$，剩下的问题是如何快速求出其他 $st_i$。

考虑这件事情：假设我们有一个集合 $C$，$C$ 中元素为 $D_1,D_2,D_3...D_t$，它满足 $D_1=m$，但不符合题目要求，即它能够线性表示出 $S$，我们把表示 $S$ 的表达式列出来：

$k_1m+\sum_{i=2}^{t}k_iD_i=S,k_i\in N$。

事实上，右边并不一定需要是 $S$，如果右边是 $S-Km$ 的话，也能说明 $C$ 并不符合要求。

更进一步地，若存在 $k_i$ 序列使得 $\sum_{i=2}^{t}k_iD_i = S \mod m$ 且 $\sum_{i=2}^{t}k_iD_i \leq S$，即可说明 $C$ 不符合要求。

所以，记 $P_i$ 表示以当前 $B$ 中元素所能表示出的模 $m$ 余 $i$ 的数中的最小值。初始时，我们先加入一个元素 $A_1=m$，令 $P_0=0,P_i= \text{inf}(i>0)$。

每当我们加入一个 $st_i$ 时，每个 $P_j$ 都有可能被更新。

具体一点，新加入一个数字 $x$ 进入集合中时，对于每个 $i$ ，枚举 $x$ 的出现次数 $w$ ，用 $P_{i-xw \mod m} + xw$ 尝试更新 $P_i$ 。$w$ 最多只需要枚举到 $m-1$ ，因为 $m$ 个 $x$ 可以用 $x$ 个 $m$ 来代替。

最后的问题是：如何决定每次新加入哪个剩余类的数字？

显然我们需要加入能加入的数字中最小的一个。枚举 $st_i$ 仍然为空的所有剩余类 $i$，我们若想保证加入的数字 $qm+i$ 不会使得集合 $B$ 不合法，只需要保证这个数字在线性表示中前面的系数为 $1,2,...m-1$ 时仍然不能与其他 $P_w$ 凑出 $S$ 即可，原理同上，$m$ 个 $qm+i$ 可以替换成 $qm+i$ 个 $m$。用数学语言来说的话，就是 $\forall j\in[1,m-1]$，有 $j(qm+i)+P_{S-ij\mod m}>S$，由此可求出对于每个 $j$ ，$qm+i$ 的最小值，然后在所有 $j$ 中取最大的最小值 $z_i$。最后再找到这一轮更新中 $z_i$ 的最小值并把它加入就行。

这样的话，每次决定新加入的数字消耗 $O(m^2)$ 的复杂度，用其更新 $P$ 消耗 $O(m)$ 的复杂度，总共最多加入 $O(m)$ 次，所以单个测试点复杂度为 $O(m^3)$。

总时间复杂度：$O(T\cdot m^3)$，可以通过。

四、代码

```cpp
#include <bits/stdc++.h>
#define ll long long
const ll inf = 2ll * 1e18;
int T, m;
ll S, K, st[51], p[51];
void add(ll x){
	for(int i = 1; i <= m - 1; ++i){
		if(1ll * i * x > S) break;
		for(int j = 1; j <= m - 1; ++j){
			int tmp = j - i * (int)(x % (1ll * m));
			tmp = (tmp % m + m) % m;
			p[j] = std::min(p[j], p[tmp] + 1ll * i * x);
		}		
	}
	return ;
}
ll fd(ll x){
	ll res = 0ll;
	for(int i = 0; i <= m - 1; ++i)
		if(st[i] <= x)
			res += (x - st[i]) / m + 1ll;
	return res;	
}
signed main(){
	scanf("%d", &T);
	while(T--){
		scanf("%lld%lld", &S, &K);
		for(int i = 2;; ++i) if(S % i) {m = i; break;}
		p[0] = 0ll;
		st[0] = 1ll * m;
		for(ll i = 1; i <= m - 1; ++i) p[i] = st[i] = inf;
		while(true){
			int y = 0; ll z = inf;
			for(int i = 1; i <= m - 1; ++i){
				if(st[i] != inf) continue;
				ll w = 1ll * i;
				for(int j = 1; j <= m - 1; ++j){
					int tmp =(int)(S % (1ll * m)) - j * i;
					tmp = (tmp % m + m) % m;
					if(p[tmp] != inf) 
						w = std::max(w, 
						(S - p[tmp] + 1ll * j) / (1ll * j));
				}
				if(w % (1ll * m) < i) w += 1ll * i - (w % (1ll * m));
				else if(w % (1ll * m) > i) 
					w += 1ll * m + 1ll * i - (w % (1ll * m));
				if(w < z) z = w, y = i;
			}
			if(z == inf) break;
			//printf("y = %d z = %lld\n", y, z);
			st[y] = z;
			add(z);
		}
		ll o = 0ll;
		for(int i = 0; i <= m - 1; ++i) 
			if(st[i] < S)
				o += (S - st[i] - 1ll) / m + 1ll;
		if(K > o) printf("-1\n");
		else {
			ll L = m, R = S - 1ll;
			while(L < R){
				ll mid = L + R >> 1ll;
				if(fd(mid) >= K) R = mid;
				else L = mid + 1ll;
			}
			printf("%lld\n", L);
		}
	}
	return 0;
}
```


---

## 作者：R_shuffle (赞：0)

同样还是考虑最简单的方式。显然把不小于 $\lceil\frac n2\rceil$ 的所有数都取一遍是比较好的，这样就能比较暴力的完成题目的要求。

然后观察样例，发现在 $S$ 为奇数的时候竟然还有更好的方法，我们直接全取偶数。容易证明这样是最优的。

不难发现在 $S=10$ 的时候还是只能取 $4$ 个，所以基本可以肯定最多只能取 $\lfloor\frac {S-1}2\rfloor$ 个。这个是可以证明的，由于和为 $S$ 的一对数中只能取 $1$ 个，但是总共只有 $\lfloor\frac {S-1}2\rfloor$ 对，同时也给出了一组构造是满足的。

不难发现现在就只有 $S$ 是偶数的时候有问题了。不妨还是以 $10$ 为例，然后可以随便口一个做法出来。由于字典序最小，所以需要从小往大考虑每对数。显然 $1$ 是不能取的，$2$ 也是不能取的，$3$ 如果取了，后面每逢$3$的倍数就要取小的。不难举一个例子。比如 $17$。
$$
17:(1,16),(2,15),(3,14),(4,13),(5,12),(6,11),(7,10),(8,9)
$$
如果取了 $3$，那么 $14,11$ 不能取，所以就要取 $6$，然后发现 $8$ 不能取，其余可能凑出 $8,11,14$ 的也不能取。比如 $4,5,7$ 不能取，然后就搞完了。

那么问题在于，取 $3$ 在 $S$ 不是 $3$ 的倍数的情况下是恒定的吗？同时可以猜测，对于任意一个 $S$，取得最小的数就是满足 $p\nmid S$ 的最小的数。

然后考虑证明这个猜测。显然如果取了 $p$，那么所有 $p$ 的倍数就都会被取，而还没有选择的对就无脑选比较大的，于是显然成立。

由于字典序最小这个条件，导致需要考虑剩下的若干对数怎么选。不妨考虑暴力，从小到大考虑每一个不确定的数，如果这个数可以被已经确定的表示，那么就必须加入；如果这个数不能被已经确定的表示，且不会直接不合法，贪心的加入。不难发现以后一种形式加入的数不会超过 $p$。所以考虑类似同余最短路的东西，然后求出之后就可以以此表示答案。之后就可以直接二分了

---

## 作者：OrezTsim (赞：0)

考虑 $n,k$ 的数量关系，也就是对序列 $a$ 的最长长度进行探究。

由于 $i$ 和 $n-i$ 不能同时放在一个集合里，$n \equiv 0 \space (\bmod\space 2)$ 时 $\dfrac{n}{2}$ 也不可放入。

那么 $[\left \lfloor \dfrac{n}{2} \right \rfloor+1,n)$ 可以放入这个集合里。

即最多有 $\left \lfloor \dfrac{n-1}{2} \right \rfloor$ 个数。

考虑到字典序最小，那么有某些数一定被替换成 $n-i$。

即设标准集合为 $A$，$[\left \lfloor \dfrac{n}{2} \right \rfloor+1,n)$。

则答案集合 $A'$ 一定是 $A$ 替换一些元素 $i$ 换成 $n-i$ 得到的。

简单来说，对于若干组 $(i,n-i)$，两者选其一。

令 $A'$ 中 $< \left \lceil \dfrac{n}{2} \right \rceil$ 的元素构成集合 $B$。

猜想合法的 $B$ 可以推断出合法的 $A'$。

- $\forall a,b \in B$ 且 $a+b < \left \lceil \dfrac{n}{2} \right \rceil$，有 $a+b \in B$。

若 $a+b$ 不在 $B$ 中，$n-(a+b)$ 就一定在 $A'$ 中，则不合法。

此时 $a+b+(n-(a+b))=n$，这种情况非法。

---

$A'$ 的字典序由 $B$ 决定，那么只要构造字典序最小的 $B$ 即可。

考虑 $B$ 的第一个元素一定是最小的非 $n$ 的因数的正整数 $d$。

接下来有两种加入元素的方式：

- 由 $B$ 中的元素可以确定。
- 新加入一个合法元素。

第一种情况平凡，使用同余最短路或者暴力更新即可。

第二种情况有 $v \equiv x\space (\bmod\space d)$ 的 $x$ 互不相同，若相同则可将另一个 $v' \equiv x\space (\bmod\space d)$ 与 $d$ 进行组合，从而得到 $v$。这种情况就可以化作第一种情况，故第二种情况至多有 $d$ 次。

那么可以在每一次处理完第二次情况后集中处理第一种情况。

设 $g_i$ 表示 $B$ 中当前元素能拼出最小的数 $\equiv i \space (\bmod d)$。

$g_i$ 显然和第一种情况无关（自我组合对最小值没有影响），仅和第二种情况有关。

考虑引入一个新的值，$f_i$ 表示 $\equiv i \space (\bmod \space d)$ 情况下放入的最小数。

那么只要处理 $f_i$ 就可以轻松转移求出 $g_i$ 了。

$g_i$ 的处理方法也很暴力，对于每一个可能的 $0 \le i < d$ 作为余数，我们可以枚举选的 $i$ 的个数 $t$，考虑这样一种方式，就是选定 $i \times t$、若干 $t$ 和某个数 $v$，使得它们的和 $\equiv n \space (\bmod \space d)$，那么这是一种不合法的情况；那么，为了规避这种不合法的方案，对于 $i$ 来说最小的取值一定是，最小的使得 $u \times t > n-g_{v \bmod d}$ 且 $u \equiv i \space (\bmod \space d)$ 的 $u$。这样，最小的 $g_{v \bmod d}$ 就无法使得当前 $u$ 不合法。

枚举所有未选过的 $u$，那么最小的合法 $u$ 就是当前加入 $B$ 的值。

如果当前最小的合法 $u > \left \lfloor \dfrac{n}{2} \right \rfloor$，$B$ 集合就取完了。

那么 $A'$ 集合也随之确定。

---

回到问题，如何计算排名 $k$ 的数？

感觉根据排名算数很困难，所以可以根据数算排名进行二分。

很简单，既然已经求出了 $f$，也就是放入集合中每个余数放入的最小数。

那么根据性质有，对于任意 $f_i$ 有 $f_i+p \times d$ 也一定在集合 $B$ 中。

则容易统计某个 $s < \left \lceil \dfrac{n}{2} \right \rceil$ 的值的排名。

若对于某个 $s > \left \lfloor \dfrac{n}{2} \right \rfloor$，我们可以这样计算。

根据定义，从 $\left \lfloor \dfrac{n}{2} \right \rfloor + 1$ 到 $s$，这一段关于中心对称的部分也在答案贡献范围内。

又因为 $(i,n-i)$ 其中之一在 $A'$ 内，那么对称部分以及超出 $\left \lfloor \dfrac{n}{2} \right \rfloor$ 的部分的贡献即为 $s - \left \lfloor \dfrac{n}{2} \right \rfloor$。

把 $s$ 设为 $n - 1 - \left \lfloor \dfrac{n}{2} \right \rfloor$，按照原来的方法求即可。

这里的 $d$ 根据 $\text{lcm}$，显然是 $\log$ 级别的。

令值域为 $v$，复杂度即为 $\mathcal{O}(t(\log v)^3)$。

---

