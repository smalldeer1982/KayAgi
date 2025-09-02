# Not Quick Transformation

## 题目描述

给定一个包含 $n$ 个数的数组 $a$。数组元素编号从 $1$ 到 $n$。$even$ 是由 $a$ 中编号为偶数的元素组成的数组（$even_{i}=a_{2i}$，$1 \leq 2i \leq n$），$odd$ 是由 $a$ 中编号为奇数的元素组成的数组（$odd_{i}=a_{2i-1}$，$1 \leq 2i-1 \leq n$）。我们定义数组的变换 $F(a)$ 如下：

- 如果 $n > 1$，则 $F(a) = F(odd) + F(even)$，其中“$+$”表示数组的连接（拼接）操作。
- 如果 $n = 1$，则 $F(a) = a$。

设 $a$ 是一个包含 $n$ 个数 $1,2,3,\ldots,n$ 的数组。$b$ 是对数组 $a$ 应用上述变换后的结果（即 $b = F(a)$）。你会得到 $m$ 个询问，每个询问为 $(l, r, u, v)$。你的任务是，对于每个询问，求出所有满足 $l \leq i \leq r$ 且 $u \leq b_i \leq v$ 的 $b_i$ 之和。请将每个询问的结果对 $mod$ 取余后输出。

## 说明/提示

我们来看第一个样例。首先构造数组 $b = F(a) = F([1,2,3,4])$。

- 第一步，$F([1,2,3,4]) = F([1,3]) + F([2,4])$。
- 第二步，$F([1,3]) = F([1]) + F([3]) = [1] + [3] = [1,3]$。
- 第三步，$F([2,4]) = F([2]) + F([4]) = [2] + [4] = [2,4]$。
- 第四步，$b = F([1,2,3,4]) = F([1,3]) + F([2,4]) = [1,3] + [2,4] = [1,3,2,4]$。

因此 $b = [1,3,2,4]$。来看第一个询问 $l=2, r=3, u=4, v=5$。数组 $b$ 的第 2 和第 3 个位置都没有在区间 $[4,5]$ 的数，因此和显然为 0。再看第二个询问 $l=2, r=4, u=1, v=3$。第 2 和第 3 个位置有两个数属于区间 $[1,3]$，它们的和为 5。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 5 10000
2 3 4 5
2 4 1 3
1 2 2 4
2 3 3 5
1 3 3 4
```

### 输出

```
0
5
3
3
3
```

## 样例 #2

### 输入

```
2 5 10000
1 2 2 2
1 1 4 5
1 1 2 5
1 1 1 3
1 2 5 5
```

### 输出

```
2
0
0
1
0
```

# 题解

## 作者：jun头吉吉 (赞：2)

# 洛谷难度最玄学的灰题
首先这道题的$n$很大，有$10^{18}$,那么暴力什么的都不可能了

考虑一下能过$10^{18}$的复杂度：$O(log_2n)$或者$O(1)$,但作为一个**Not Quick Transformation**，$O(1)$还是很难推的，因此我们考虑$O(log_2n)$的算法：分治

我们用$ans(lim,first,num,d,len)$表示项为first，公差为d，项数为len的等差数列。要计算这个序列变换完以后区间[1,num]中所有不超过lim的数的和

当一个数变换前在$[u,v]$并且变换后在$[L,R]$内，才会对答案有贡献，我们不妨只考虑在变换后$[1,R]$内以及变换前$[1,v]$内，用容斥原理减一减就可以得到答案

显然，$[1,R]$到$[1,v]$的答案数为$ans(v,1,1,R,n)$

现在我们只需考虑$ans$的求法

设$mid=\lceil \frac {len} 2\rceil$

当前等差数列经过一次变换会变成一个首项为$first$，公差为$d*2$，项数为$mid$的等差数列（原等差数列的第奇数项）加上一个首项为$first+d$,公差为$d*2$，项数为$len-mid$的等差数列（原等差数列的第偶数项）

如果$mid\leq num$，那么左边的等差数列无论怎么变换，它都是要全部算进去的，那么直接计算其中不超过$lim$的数的和即可，然后递归右边$ans(lim,first+d,num−mid,d∗2,len−mid)$

否则，递归左边$ans(lim,first,num,d∗2,mid)$

复杂度:$O(mlog_2n)$

```cpp
#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
typedef long long ll;
ll n,m,mod;
#define mul(x,y) ((x)%mod)*((y)%mod)%mod
#define add(x,y) ((x)+(y))%mod
ll get(ll fs,ll num,ll lim,ll d){
	if(lim<fs)return 0;
	lim=(lim-fs)/d*d+fs;
	ll ls=min(lim,fs+d*(num-1));
	ll v1=(ls-fs)/d+1,v2=(fs+ls);
	if(v1%2==0)v1/=2;
	else v2/=2;
	return mul(v1,v2);
}
ll solve(ll lim,ll fs,ll d,ll num,ll len){
	if(num==0)return 0;
	if(len==1)return fs<=lim?fs:0;
	ll mid=(len+1)/2;
	if(num>=mid)return add(get(fs,mid,lim,d*2),solve(lim,fs+d,d*2,num-mid,len-mid));
	else return solve(lim,fs,d*2,num,mid);
}
signed main(){
	read(n,m,mod);
	while(m--){
		ll l,r,x,y;
		read(l,r,x,y);
		write((((solve(y,1,1,r,n)-solve(x-1,1,1,r,n)+mod)%mod-(solve(y,1,1,l-1,n)-solve(x-1,1,1,l-1,n)+mod)%mod)+mod)%mod);
		putchar('\n');
	}
}
```

---

## 作者：Mr_Dolphin (赞：1)

# 分治神题

[题目传送门](https://www.luogu.com.cn/problem/CF117D)

## 题目大意

定义一个数列 $s$ 的变换 $F(s)$：

$$
F(s)=\begin{cases}
F(odd_s)+F(even_s)&|s|>1\\
s&|s|=1
\end{cases}
$$

将 $1$ 到 $n$ 的排列进行一次变换得到数组 $b$，$m$ 次询问，每次给定 $l$，$r$，$x$，$y$，求在区间 $[l,r]$ 中所有在 $[x,y]$ 的数的和。

## 思路

注意到 $n \le 10^{18}$，这告诉我们两件事情。

1. 大部分的数据结构肯定都用不了了，会爆内存。
2. $O(n)$ 的算法肯定过不去，需要寻求 $\log$ 算法或根号算法解决。

基于以上的角度进行分析，本蒟蒻能够想到的算法只有分治了。

考虑状态 $(k,l,r,x,y)$ 表示 $1$ \~ $k$ 在区间 $[l,r]$ 中所有在 $[x,y]$ 的数的和，思考如何进行分治。一个很直接的思路就是按照题目给出的操作进行分治，但你会发现两边分别变成了 $(1,3,5,...,2\times|odd|-1)$ 和 $(2,4,6,...2\times|even|)$。其中：

$$\begin{cases}
|odd|= \lceil\frac{|s|}{2}\rceil \\
|even|=|s|-|odd|
\end{cases}$$

显然分治后与我们定义的状态不同。考虑进行转化，发现只需将只需将两边变为 $ (1,2,3,...,|odd|) $ 和 $(1,2,3,...|even|)$ 便能符合要求。

同时，我们要改变区间 $[x,y]$ 使得转换后区间包含的数的位置与转换前相同。这里需要手搓几个数据算一下，建议先算第二种情况，好推一点。最后我们可以得到两边分别为 $[\lfloor\frac{x}{2}\rfloor+1,\lceil\frac{y}{2}\rceil]$ 和 $[\lceil\frac{x}{2}\rceil,\lfloor\frac{y}{2}\rfloor]$。

然而这样我们得到的值显然是错的，我们要将答案转化回去，记转化后答案为 $ret$，转化前答案为 $ans$ 则有：
$$

ans=\begin{cases}
ret\times2-|odd|&F(odd_s) \\
ret\times2&F(even_s)
\end{cases}

$$
因而我们的分治函数要返回两个值，一个是答案，一个是有效区间长度。可以通过返回pair类型来解决。

最后解决向哪里分治的问题。令 $mid=\lceil \frac{k}{2}\rceil$，则：

$$
(k,l,r,x,y)=\begin{cases}
(k-mid,l-mid,r-mid,\lfloor\frac{x}{2}\rfloor+1,\lceil\frac{y}{2}&mid < l \\
(mid,l,r,\lceil\frac{x}{2}\rceil,\lfloor\frac{y}{2}\rfloor)&mid\ge r \\
(k-mid,1,r-mid,\lfloor\frac{x}{2}\rfloor+1,\lceil\frac{y}{2}\rceil)+(mid,l,mid,\lceil\frac{x}{2}\rceil,\lfloor\frac{y}{2}\rfloor)&l\le mid<r
\end{cases}$$

复杂度分析：每一次操作都要对这个序列进行一次分治，时间复杂度为 $O(m \log n)$，可以通过本题。
## code
需要注意取模的问题。因为有减法，因此需要取模后加上模数再取一遍模。
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mpii make_pair
using namespace std;
int n,m,mod;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<3)+(x<<1)+(ch^'0');
		ch=getchar();
	}
	return x*f;
}
pii query(int k,int l,int r,int x,int y)//记得多多取模
{
	if(x>k||l>r)
	{
		return mpii(0,0);
	}
	if(k==r&&l==1)//整个序列为[1,k]，则答案为[x,y]的和，用等差数列求和公式即可
	{
		x=max(1ll,x);
		y=min(k,y);
		int tmp=x+y;
		if(tmp&1)
		{
			tmp=(((y-x+1)>>1)%mod)*(tmp%mod)%mod;
		}
		else
		{
			tmp=((tmp>>1)%mod)*((y-x+1)%mod)%mod;
		}
		return mpii(tmp,y-x+1);
	}
	int mid=(k+1)>>1;
	pii ret;
	if(mid>=r)
	{
		pii p=query(mid,l,r,(x>>1)+1,(y+1)>>1);
		ret=mpii((((p.fi<<1)%mod)-(p.se%mod)+mod)%mod,p.se%mod);
	}
	else
	{
		if(mid<l)
		{
			pii p=query(k-mid,l-mid,r-mid,(x+1)>>1,y>>1);
			ret=mpii((p.fi<<1)%mod,p.se%mod);
		}
		else
		{
			pii p1=query(mid,l,mid,(x>>1)+1,(y+1)>>1),p2=query(k-mid,1,r-mid,(x+1)>>1,y>>1);
			ret=mpii((((p1.fi<<1)%mod)-(p1.se%mod)+(p2.fi<<1)%mod+mod)%mod,(p1.se+p2.se)%mod);
		}
	}
	return ret;
}
signed main()
{
	n=read(),m=read(),mod=read();
	while(m--)
	{
		int l=read(),r=read(),x=read(),y=read();
		printf("%lld\n",query(n,l,r,x,y).fi%mod);
	}
	return 0;
}
```
[AClink](https://codeforces.com/contest/117/submission/291387282)

码风轻喷

有问题请私信

---

