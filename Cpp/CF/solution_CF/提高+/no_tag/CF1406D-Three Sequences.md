# Three Sequences

## 题目描述

You are given a sequence of $ n $ integers $ a_1, a_2, \ldots, a_n $ .

You have to construct two sequences of integers $ b $ and $ c $ with length $ n $ that satisfy:

- for every $ i $ ( $ 1\leq i\leq n $ ) $ b_i+c_i=a_i $
- $ b $ is non-decreasing, which means that for every $ 1<i\leq n $ , $ b_i\geq b_{i-1} $ must hold
- $ c $ is non-increasing, which means that for every $ 1<i\leq n $ , $ c_i\leq c_{i-1} $ must hold

You have to minimize $ \max(b_i,c_i) $ . In other words, you have to minimize the maximum number in sequences $ b $ and $ c $ .

Also there will be $ q $ changes, the $ i $ -th change is described by three integers $ l,r,x $ . You should add $ x $ to $ a_l,a_{l+1}, \ldots, a_r $ .

You have to find the minimum possible value of $ \max(b_i,c_i) $ for the initial sequence and for sequence after each change.

## 说明/提示

In the first test:

- The initial sequence $ a = (2, -1, 7, 3) $ . Two sequences $ b=(-3,-3,5,5),c=(5,2,2,-2) $ is a possible choice.
- After the first change $ a = (2, -4, 4, 0) $ . Two sequences $ b=(-3,-3,5,5),c=(5,-1,-1,-5) $ is a possible choice.
- After the second change $ a = (2, -4, 6, 2) $ . Two sequences $ b=(-4,-4,6,6),c=(6,0,0,-4) $ is a possible choice.

## 样例 #1

### 输入

```
4
2 -1 7 3
2
2 4 -3
3 4 2```

### 输出

```
5
5
6```

## 样例 #2

### 输入

```
6
-9 -10 -9 -6 -5 4
3
2 6 -9
1 2 -10
4 6 -3```

### 输出

```
3
3
3
1```

## 样例 #3

### 输入

```
1
0
2
1 1 -1
1 1 -1```

### 输出

```
0
0
-1```

# 题解

## 作者：SatsukiQAQ (赞：14)

upd again on 2020.9.22:又修了一处锅，感谢@tommy0103
upd on 2020.9.14:修了一些锅

题意:给定序列 $a$ ，要求构造序列 $b$ 和 $c$ 满足所有的 $b_i + c_i = a_i$ ，其中 $b$ 不减，$c$ 不增。求 $max(b_i,c_i)$ 的最小值（两个序列中的最大值取max）。
然后有 $q$ 个操作，每个操作是把 $a$ 的 $l$ 到 $r$ 这一段 $+x$ ，求每次操作后的 $max(b_i,c_i)$ 的最小值。

题解:首先我们考虑若 $a$ 序列中的值都相等，此时 $b, c$序列显然也是保持序列中元素都相等最优。然后我们考虑若 $a$ 序列有上升的部分，如果这个上升由 $c$ 序列贡献，则 $c$ 序列必须整体抬高（因为 $c$ 单调递减），而 $b$ 就没有这个问题，下降同理。因此我们可以得知：上升全部由 $b$ 序列贡献，下降全部由 $c$ 序列贡献时是最优的。

因为 $b_n$ 是 $b$ 中的最大值， $c_1$ 是 $c$ 中的最大值，且满足 $a_1 = b_1 + c_1 = b_n - \sum\limits_{i = 2} ^ {n} (b_i - b_{i - 1})  + c_1$, 由此可见令 $b_n, c_1$ 尽量接近是最优的，因此答案就是 $\lceil \frac{\sum\limits_{i = 2} ^ {n} (b_i - b_{i - 1})}{2} \rceil$

考虑修改，因为这是差分数组，因此只需单点修改，并考虑修改对 $\sum\limits_{i = 2} ^ {n} (b_i - b_{i - 1})$ 的影响，重新计算答案即可。

总复杂度 $O(n + q)$ ，别忘了开long long

$Code:$


``` cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
using namespace std;
const int MAXN = 1e5 + 10;
int n, a[MAXN], b[MAXN], c[MAXN];
signed main() 
{
	int res(0);
	scanf("%lld", &n);
	rep(i, 1, n)
	{
		scanf("%lld", &a[i]);
		b[i] = a[i] - a[i - 1];
		if(i != 1 && b[i] > 0) res += b[i];
	}
	printf("%lld\n", (int)ceil((res + a[1]) * 0.5)); 
	int q;
	scanf("%lld", &q);
	while(q --)
	{
		int l, r, x;
		scanf("%lld%lld%lld", &l, &r, &x);
		++r;
		int tmp1 = b[l], tmp2 = b[r];
		b[l] += x, b[r] -= x;
		if(l != 1) res -= max(0ll, tmp1) - max(0ll, b[l]);
		if(r != n + 1 && r != 1) res -= max(0ll, tmp2) - max(0ll, b[r]);
		printf("%lld\n", (long long)ceil((res + b[1]) * 0.5)); 
	}
    return 0;
}
```

---

## 作者：dead_X (赞：7)

## 前言
好题，我喜欢。
## 题意
求序列 $a$ 中每个数拆成两半，组成一个非严格递增序列 $b$ 和非严格递减序列 $c$ ，序列 $b,c$ 中所有元素的最大值是多少。

你还需要回答 $m$ 次形如将 $l$ 到 $r$ 的数增加 $k$ 后的答案。
## 思路
乍眼一看，似乎是线段树维护区间最大值然后乱搞一下，然后就没有然后了。

然后我们开始手玩样例。

- $a=(2,-1,7,3)$ 被我们拆成了 $b=(-3-3,5,5)$ 和 $c=(5,2,2,-2)$ 。
- $a=(2,-4,4,3)$ 被我们拆成了 $b=(-3-3,5,5)$ 和 $c=(5,-1,-1,-5)$ 。
- $a=(2,-4,6,2)$ 被我们拆成了 $b=(-4,-4,6,6)$ 和 $c=(6,0,0,-4)$ 。

第一眼看上去，我们总觉得出题人在忽悠我们。样例中 $b$ 和 $c$ 出现了大量**重复的相邻数字**，而且上面相邻下面不相邻，总觉得很奇怪。

但是只要过了一点时间，再结合另外的几个样例，我们就可以发现一件重要的事情：对于 $a_i$ 和 $a_{i+1}$ ，在最优解中，若 $a_{i+1}>a_i$ ，$b_{i+1}$ 会比 $b_i$ 大，否则 $c_{i+1}$ 会比 $c_i$ 小，而且增大的量恰好是差值。

证明：如果要使一个非严格递增（递减）数列最大值最小，显然任意一位上的数如果能取一个更小值是必定**更优**的，而除了最优解的其余决策必然会导致**某一位上的值变得更大**，从而影响最终答案。

差值，区间修改……会不会是**差分**？

恭喜你，如果发现了这条性质，你离成功已经不远了。我强烈建议你关掉题解，继续想下去，你马上就会体会到柳暗花明又一村的乐趣。

--------------------

好的，相信你已经口胡出解法了，我们继续。

首先，$a_1$ 可以分成 $b_1$ 和 $c_1$ 。然后我们按照上方最优解的形式，可以将 $b_n$ 和 $c_n$ 写成 $b_1+k_1$ 和 $c_1-k_2$ ，其中 $k_1$ 和 $k_2$ 都是非负整数。

代回原题，答案就是 $max(b_n,c_1)=max(b_1+k_1,c_1)$ ，不难发现答案就是 $\Large\lceil \frac{a_1+k_1}{2}\rceil$ 。

接下来我们只需要实现 $k_1$ 怎么计算和修改即可，这个公式是显然的，即 $\sum max(a_i-a_{i-1},0)$ 。单点修改的时候直接减掉贡献再加回去就行了。

**坑点：C++的除法是向 $0$ 取整，即 ``-5/2=-(5/2)`` 。**

## 代码
```
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
#define int long long
using namespace std;
inline int read(){
   int s=0ll,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int s[1000003],a[1000003];
long long half(long long x)
{
	if(x>=0) return x/2;
	else if(x%2==0) return x/2;
	else return x/2-1;
}
signed main()
{
	int T=1;
	while(T--)
	{
		int n=read();
		for(int i=1; i<=n; i++) s[i]=read();
		for(int i=1; i<=n; i++) a[i]=s[i]-s[i-1];
		long long sum=a[1];
		for(int i=2; i<=n; i++) sum+=max(0ll,a[i]);
		printf("%lld\n",half(sum+1));
		int m=read();
		while(m--)
		{
			int l=read(),r=read(),k=read();
			if(l!=1) sum-=max(a[l],0ll),a[l]+=k,sum+=max(a[l],0ll);
			else sum-=a[l],a[l]+=k,sum+=a[l];
			if(r!=n) sum-=max(a[r+1],0ll),a[r+1]-=k,sum+=max(a[r+1],0ll);
			
			//for(int i=1; i<=n; i++) cout<<a[i]<<' ';
			printf("%lld\n",half(sum+1));
		}
	}
	return 0ll;
}

```

---

## 作者：tommymio (赞：4)

非常好的一道性质题。

手玩+稍加证明就可以发现，$a_i$ 增时，只会影响 $b_i$，$a_i$ 降时只会影响 $c_i$。

由于 $b_i$ 不降，$c_i$ 不增，所以 $b,c$ 两序列的最大值分别为 $b_n,c_1$，而又有 $b_n=b_1+\sum_{i=2}^nb_i-b_{i-1}$，和 $\max \{b_n,c_1\}=\left\lceil\frac{b_n+c_1}{2}\right\rceil$，于是有 $\left\lceil\frac{b_n+c_1}{2}\right\rceil=\left\lceil\frac{(b_1+c_1)+\sum_{i=2}^nb_i-b_{i-1}}{2}\right\rceil$。

发现 $b_1+c_1$ 就是 $a_1$，那么我们必须要求出 $\sum_{i=2}^n b_i-b_{i-1}$，不妨记 $b_i-b_{i-1}$ 为 $\Delta_i$，则该式可以记作 $\sum_{i=2}^n \Delta_i$ 那么根据上述性质，$\Delta_i$ 与 $a_i$ 的关系式是 $\Delta_i=(a_i-a_{i-1})\times[a_i\geq a_{i-1}]$，这个东西可以预处理出来。

加上修改操作又该怎么做呢？我们发现一次修改事实上只会影响 $d_l,d_{r+1}$ 的值，直接修改 $d_l,d_{r+1}$，并且用 $\text{BIT}$ 维护 $a_i$ 的区间增量即可。

```cpp
#include<cstdio>
#include<cmath>
typedef long long ll;
int n,a[100005];;
ll sum[100005],d[100005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int val) {for(;x<=n;x+=x&(-x)) sum[x]+=val;}
inline ll ask(int x) {ll res=0; for(;x;x-=x&(-x)) res+=sum[x]; return res;}
int main() {
	n=read(); ll cur=0;
	for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=2;i<=n;++i) d[i]=(a[i]-a[i-1])*(a[i]>=a[i-1]);
	for(register int i=2;i<=n;++i) cur+=d[i];
	printf("%lld\n",(ll)ceil((a[1]+cur)*1.00/2));
	int T=read();
	while(T--) {
		int l=read(),r=read(),x=read();
		add(l,x);if(r<n) add(r+1,-x);
		ll a1=a[l-1]+ask(l-1),a2=a[l]+ask(l);
		if(l>1) {cur-=d[l];d[l]=(a2-a1)*(a2>=a1);cur+=d[l];}
		a1=a[r]+ask(r),a2=a[r+1]+ask(r+1);
		if(r<n) {cur-=d[r+1];d[r+1]=(a2-a1)*(a2>=a1);cur+=d[r+1];}
		printf("%lld\n",(ll)ceil((a[1]+ask(1)+cur)*1.00/2));	
	}
	return 0;
}
```

---

## 作者：chenxia25 (赞：3)

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/CF1406D ) & [CF 题目页面传送门]( https://codeforces.com/contest/1406/problem/D )
>
> 给定一个长度为 $n$ 的数列 $a$。你需要构造出长度为 $n$ 的数列 $b,c$，满足 $a_i=b_i+c_i$，且 $b$ 不降，$c$ 不升。最小化 $\max(b_i,c_i)$。然后还有 $q$ 次区间增加，每次输出最小化的结果。
>
> $n,q\in\left[1,10^5\right]$。

二话不说先找结论啊。通过观察样例发现，一开始 $b_1,c_1$ 随便取只要满足 $a_1=b_1+c_1$ 即可，然后以后的话，若 $a$ 的增量 $\geq 0$ 就在 $b$ 上加，否则就在 $c$ 上减。证明的话随便想想很简单，显然 $\max(b_i,c_i)=\max(b_n,c_1)$，那么在 $b_1,c_1$ 固定的时候，$b$ 的总增量显然越小越好，于是就只有在必要的时候才在 $b$ 上加咯。

然后现在解决 $b_1,c_1$ 不固定的事情。我们想要令 $\max(b_n,c_1)$ 这个柿子最小，那么首先需要将 $b_n$ 用 $b_1$ 表示一下。令增量 $\Delta_i=a_{i+1}-a_i$，则 $b_n=b_1+\sum\limits_{i=1}^{n-1}[\Delta_i\geq 0]\Delta_i$。令那个 $\sum$ 为 $\Sigma$，那么柿子为 $\max(b_1+\Sigma,c_1)$。又 $a_1=b_1+c_1$，则柿子又可以写为 $\max(b_1+\Sigma,a_1-b_1)$。那么注意到 $\max$ 两个参数是和为常量的，那么最理想的情况是令它们相等，则 $\max$ 最小。解个方程可以得到 $b_1=\dfrac{a_1-\Sigma}2$。但是不允许出现小数，所以还要取个整然后左右两边 round 一下。

然后还有区间加呢。注意到区间加只会令两个增量变化，于是随便 $\mathrm O(1)$ 维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=100000;
int n;
int a[N+1];
int qu;
int d[N+1];
int calc(int now,int x){
	int res=inf;
	for(int i=now-3;i<=now+3;i++)res=min(res,max(i+x,a[1]-i));
	return res;
}
void mian(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	for(int i=1;i<n;i++)d[i]=a[i+1]-a[i];
	int x=0;
	for(int i=1;i<n;i++)if(d[i]>0)x+=d[i];
	cout<<calc(a[1]-x>>1,x)<<"\n";
	cin>>qu;
	while(qu--){
		int l,r,v;
		scanf("%lld%lld%lld",&l,&r,&v);
		if(l==1)a[1]+=v;
		if(l-1&&d[l-1]>0)x-=d[l-1];
		if(r<n&&d[r]>0)x-=d[r];
		d[l-1]+=v,d[r]-=v;
		if(l-1&&d[l-1]>0)x+=d[l-1];
		if(r<n&&d[r]>0)x+=d[r];
		printf("%lld\n",calc(a[1]-x>>1,x));
	}
}
signed main(){
	int testnum=1;
//	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

## 作者：奇米 (赞：3)

# $\mathrm{CF1406D}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF1406D)

给你一个长度为 $n$ 的序列 $a_i$，让你构造 $b_i,c_i$ 使得 $b_i+c_i=a_i$ 并且 $b_i$ 不降，$c_i$ 不升，使得 $\min(\max\limits_{i=1}^{n}(a_i,b_i))$，并且有 $q$ 次修改。$n,q\leq 10^5$

## $\mathrm{Sol}$

一道不错的思维题

我们考虑若 $a_{i-1}<a_i$ 那么 $c_i=c_{i-1},b_i=b_{i-1}+(a_i-a_{i-1})$

若 $a_i<a_{i-1}$ 那么 $b_i=b_{i-1},c_i=c_{i-1}+(a_i-a_{i-1})$

这个还是比较显然的（利用 $b_i,c_i$ 不升不降的特殊性质）。

我们设 $mx=c_1$，那么 $b_1=a_1-mx$，$b_n=b_1+(S=\sum\limits_{i=2}^{n}\max(0,a_i-a_{i-1}))$

那么$mx=a_1-mx+S$ 所以 $mx=\frac{a1+S}{2}$。

对于对于带修改我们考虑差分即可，具体地对于一次修改 $(l,r,s)$

若 $a_l>a_{l-1}$ 那么我们先减去原先的贡献再加上修改后的即 $(a_l+s)$ 若大于 $a_{l-1}$ 那么加上 $a_l+s-a_{l-1}$ 否则只减不加。

时间复杂度 $O(n+q)$

## $\mathrm{Code}$

```cpp
const int mod=1e9+7;
const int mo=998244353;
const int N=2e5+5;

int n,m,a[N],cf[N],Q;

signed main()
{
	io.read(n);
	int mx=0;
	For(i,1,n) io.read(a[i]),mx+=(i>1)?max(a[i]-a[i-1],0ll):0;
	io.write((a[1]+mx+1)>>1ll),puts("");
	Dow(i,n,1) a[i]=a[i]-a[i-1];
	io.read(m);
	for (;m--;)
	{
		int l,r,s;
		io.read(l),io.read(r),io.read(s);
		if(l==1) a[1]+=s;
		else
		{
			if(a[l]>0) mx-=a[l];
			a[l]+=s;
			if(a[l]>0) mx+=a[l];
		}
		if(r<n) 
		{
			r++;
			if(a[r]>0) mx-=a[r];
			a[r]-=s;
			if(a[r]>0) mx+=a[r];
		}
		io.write((a[1]+mx+1)>>1ll),puts("");
	}
	return 0;
}

```


---

## 作者：QwQcOrZ (赞：2)

因为 $b$ 是不降的，$c$ 是不升的，那么考虑将 $a$ 数组上升的影响用 $b$ 消除，$a$ 下降的影响用 $c$ 消除

然后最优解就可以用 $b$ 和 $c$ 的整体上升或下降得到

也就是说我们先令 $b_1=0,c_1=a_1$

然后对于每个 $i$，若 $a_{i-1}<a_i$，则 $b_i=b_{i-1}+a_i-a_{i-1},c_i=c_{i-1}$

否则 $b_i=b_{i-1},c_i=c_{i-1}+a_i-a_{i-1}$

此时可以发现我们构造了一组在 $b_1=0,c_1=a_1$ 时，$b_n$ 和 $c_1$ 尽量小的解

为什么要这样构造？因为只有 $b$ 的最大值（$b_1$）和 $c$ 的最大值（$c_n$）对答案有影响，我们只要保证这两个数最小即可

然后构造了这样一组解时，我们发现这样不一定是最优的，因为我们可以用 $b$ 和 $c$ 的整体上升或下降来使答案更优

也就是说当 $b_1<c_n$ 时，我们可以令 $b_i=b_i+1,c_i=c_i-1$，此时可以发现在 $c_n\geq b_1+2$ 时答案会变优，否则答案不变。 $b_1\geq c_n$ 时同理

然后答案就变成最小解了，因为我们保证了每步都是最优的

接下来就是修改操作

因为可以发现显然答案只和 $a$ 数组的差分数组有关，那么我们令 $a_i=a_i-a_{i-1}$

此时发现加 $x$ 的操作就变成了 $a_l=a_l+x,a_{r+1}=a_{r+1}-x$

然后将对应的答案增减即可，具体可以看代码

注意 `C++` 中的取整是向 $0$ 取整的，所以要特判一下

$Code\ Below$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
void Print(int x)
{
	if (x&1) x++;
	print(x/2);
}
int n,Max1=0,Max2=0,a[N];
void add(int l,int x)
{
	l--;
	if (l==0) Max1+=x;
	if (l<1||n<=l) return;
	if (a[l]>0) Max2-=a[l];
	a[l]+=x;
	if (a[l]>0) Max2+=a[l];
}

signed main()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	Max1=a[1];
	for (int i=1;i<=n;i++) a[i]=a[i+1]-a[i];
	for (int i=1;i<n;i++) if (a[i]>0) Max2+=a[i];
	Print(Max1+Max2);
	int m=read();
	for (int i=1;i<=m;i++)
	{
		int l=read(),r=read(),x=read();
		add(l,x);
		add(r+1,-x);
		Print(Max1+Max2);
	}

	return 0;
}
```

---

## 作者：formkiller (赞：2)

### Problem ：

给出序列 a，其长度为 n

求构造非下降序列 b 和非上升序列 c，使其满足 $a_i=b_i+c_i$

更具体地说： $b_{i} \ge b_{i-1}$ ， $c_{i} \le c_{i-1}$

求 $\max(b_i,c_i)$ 的最小值，也就是求序列 $b$ 和 $c$ 的最大元素的最小值

然后给出 $q$ 和 $q$ 次操作

每次操作 $l,r,x$ 代表将 $a_l,a_{l+1},...,a_r$ 加上 $x$

求每次操作后 $\max(b_i,c_i)$ 的最小值

------------


### Solution :
一道很好的思维题

首先先观察 $b$ 和 $c$ 的性质，不难发现 $b_n$ 是 $\max(b_i)$， $c_1$ 是 $\max(c_i)$

于是问题转化成求 $\max(b_n,c_1)$

不妨设 $b_n=c_1=k$ 

那么 $b_1=a_1-c_1=a_1-k$

$c_n=a_n-b_n=a_n-k$

确定了第 $1$ 项和第 $n$ 项后就可以考虑构造中间的数了

根据题意可以得到：

$c_{i} \le c_{i-1}$

$a_{i} - b_{i} \le a_{i-1} - b_{i-1}$

$b_{i-1} + a_{i} - a_{i-1} \le  b_{i}$

$\because  b_{i-1} \le  b_{i}$

$\therefore b_{i} \ge \max(b_{i-1} + a_{i} - a_{i-1} ,b_{i-1})$

$\therefore b_{i} \ge b_{i-1} + \max(a_{i} - a_{i-1} ,0)$

由大于的传递性可得：

$b_{n} \ge b_{n-1} + \max(a_{n} - a_{n-1} ,0) \ge b_{n-2} + \max(a_{n} - a_{n-1} ,0) + \max(a_{n-1} - a_{n-2} ,0)$

$b_{n} \ge b_{1} + \sum\limits^{n}_{i=2}\max(a_{i} - a_{i-1} ,0)$

将 $b_n = k$ 和 $b_1 = a_1 - k$ 代入：

$k \ge a_1 - k + \sum\limits^{n}_{i=2}\max(a_{i} - a_{i-1} ,0)$

$k \ge (a_1 + \sum\limits^{n}_{i=2}\max(a_{i} - a_{i-1} ,0))/2$

同理，对 $c$ 进行分析可得：

$k \ge (a_n - \sum\limits^{n}_{i=2}\min(a_{i} - a_{i-1} ,0))/2$

不等式取等号时可令 $k$ 取最小值，两个不等式中较大的一个即为答案

然后考虑维护 $a_{i} - a_{i-1}$ 这个东西

注意到每次操作都是区间加减，而对于 $i \in [l+1,r]$ ， $a_{i} - a_{i-1}$ 不会改变

因此我们只需要维护 $i = l$ 和 $i = r + 1$ 两处的差值

预处理时做差分，更新时更新差分数组即可

处理好判断边界和求 $k$ 时是否要 $+1/-1$ 的细节之后就没有问题了

时间复杂度：$O(n+q)$




------------


赛时代码有点乱，将就着看吧（


### Code :

```cpp

//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstdlib>
# include <algorithm>

#define LL long long
#define maxn int(1e5+5)
#define is(a) (a>='0'&&a<='9')
#define imax(a,b) ((a)>(b)?(a):(b))
#define imin(a,b) ((a)<(b)?(a):(b))

using namespace std;

LL N,M;
LL all,bll,ans,a[maxn],d[maxn];

inline void read(LL &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

LL count(LL x)
{
	return (x>=0)?x:0;
}

int main()
{
//	freopen("a.in","r",stdin);
	read(N);
	for (int i = 1; i <= N; ++i)
	{
		read(a[i]);
		d[i] = a[i] - a[i-1];
		all+=count(d[i]);
		bll+=count(-d[i]);
	}
	all-=count(d[1]);
	bll-=count(-d[1]);
	ans=imax((a[1]+all+(a[1]+all>=0))/2,(a[N]+bll+(a[N]+bll>=0))/2);
	printf("%lld\n",ans);
	read(M);
	for (int i = 1; i <= M; ++i)
	{
		LL x,y,v;
		read(x); read(y); read(v);
		if (N==1)
		{
			a[1]+=v;
			ans=a[1]/2;
			printf("%lld\n",ans);
			continue;
		}
		if (x==1)
		{
			if (y!=N)
			{
				all-=count(d[y+1]); bll-=count(-d[y+1]);
				d[y+1]-=v;
				all+=count(d[y+1]); bll+=count(-d[y+1]);
				a[1]+=v;
			}
			else
			{
				a[1]+=v;
				a[N]+=v;
			}
		}
		else 
		{
			if (y!=N)
			{
				all-=count(d[x]); all-=count(d[y+1]); bll-=count(-d[x]); bll-=count(-d[y+1]);
				d[x]+=v; d[y+1]-=v;
				all+=count(d[x]); all+=count(d[y+1]); bll+=count(-d[x]); bll+=count(-d[y+1]);
			}
			else
			{
				all-=count(d[x]); bll-=count(-d[x]);
				d[x]+=v;
				all+=count(d[x]); bll+=count(-d[x]);
				a[N]+=v;
			}
		}
		
		ans=imax((a[1]+all+(a[1]+all>=0))/2,(a[N]+bll+(a[N]+bll>=0))/2);
		printf("%lld\n",ans);
	}
    return 0;
}
```














---

## 作者：Chinese_zjc_ (赞：2)

显然,由于 $ B $ 和 $ C $ 均有序,因此 $ B $ 和 $ C $ 中最大的一个元素必然是 $ \max(b_1,c_n) $ .

考虑贪心,尽可能让 $ B $ 和 $ C $ 的值不要轻易变化,因为一旦变化就变不回去了.

对于 $ i(1<i\leq n) $ ,我们知道有下面式子:
$$
\begin{cases}
a_i=b_i+c_i\\
a_{i-1}=b_{i-1}+c_{i-1}\\
a_i-a_{i-1}=(b_i-b_{i-1})+(c_i-c_{i-1})\\
b_i-b_{i-1}\leq0\\
c_i-c_{i-1}\geq0\\
\end{cases}
$$
由于之前的贪心策略,我们要尽量满足
$$
\begin{cases}
b_i-b_{i-1}=0\\
c_i-c_{i-1}=0\\
\end{cases}
$$
显然两者只有当 $ a_i-a_{i-1}=0 $ 时才能同时满足.

那我们别的时候就满足其中一个式子.

- 当 $ a_i-a_{i-1}>0 $ 时,我们让 $ b_i-b_{i-1}=0 $ , $ c_i-c_{i-1}=a_i-a_{i-1} $ .
- 当 $ a_i-a_{i-1}>0 $ 时,我们让 $ c_i-c_{i-1}=0 $ , $ b_i-b_{i-1}=a_i-a_{i-1} $ .

到这里,贪心策略已经非常明显了.

那么我们就可以得到:
$$
c_n=c_1+\sum_{i=2}^n\max(0,a_i-a_{i-1})
\\
\ \ \ \ =a_1-b_1+\sum_{i=2}^n\max(0,a_i-a_{i-1})\\
$$
 到这里,我们已经可以 $ O(n) $ 计算出 $ c_n $ 与 $ b_1 $ 的数量关系.

因此就可以用各种算法乱搞出答案的值了(如二分答案).

再看修改部分,我们上面实际用到的是数据之间的差分,而差分恰好又能很好地做到 $ O(1) $ 区间修改.

直接暴力修改,然后再重新求一次答案即可.

**注意特判边界.**

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
#define int long long
#define PI 3.14159265358979323
#define INF 0x3fffffffffffffff
using namespace std;
int n,a[100005],ans,q,l,r,x;
int getans()
{
    return max((a[1]+ans)/2,a[1]+ans-(a[1]+ans)/2);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
    }
    for(int i=n;i>1;--i)
    {
        a[i]=a[i]-a[i-1];
        ans+=max(0ll,a[i]);
    }
    cout<<getans()<<endl;
    cin>>q;
    for(int i=1;i<=q;++i)
    {
        cin>>l>>r>>x;
        if(l>1)
        {
            ans-=max(0ll,a[l]);
            a[l]+=x;
            ans+=max(0ll,a[l]);
        }
        else
        {
            a[1]+=x;
        }
        ++r;
        if(r<=n)
        {
            ans-=max(0ll,a[r]);
            a[r]-=x;
            ans+=max(0ll,a[r]);
        }
        cout<<getans()<<endl;
    }
    return 0;
}
```



---

## 作者：gyh20 (赞：2)

贪心。

这里令 $b$ 为不下降， $c$ 为不上升。

如果 $a_i>a_{i-1}$，则令 $b_i=b_{i-1}+a_i-a_{i-1},c_i=c_{i-1}$

否则令 $c_i=c_{i-1}+a_i-a_{i-1},b_i=b_{i-1}$

假设 $b_1=x,c_1=a_1-x,b_n=x+\sum\limits_{i=2}^n\max(a_i-a_{i-1},0)$，则 $\max(c_1,b_n)=ceil(\dfrac{c_1+b_n}{2})$。

由于是区间修改，可以快速维护 $a_1,\sum\limits_{i=2}^n\max(a_i-a_{i-1},0)$。

代码：

```cpp
#include<cstdio>
#include<cmath>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
int n,a[100002],sumg,suml,a1,A,B,C,q;
inline int check(){
	return ceil((double)(a1+sumg)/2.0);
}
inline void cg(re int x,re int y){
	if(x>n)return;
	a[x]>0?sumg-=a[x]:suml+=a[x];
	a[x]+=y;
	a[x]>0?sumg+=a[x]:suml-=a[x];
}
signed main(){
	n=read();
	for(re int i=1;i<=n;++i)a[i]=read();
	for(re int i=2;i<=n;++i){
		if(a[i]>a[i-1])sumg+=a[i]-a[i-1];else suml+=a[i-1]-a[i];
	}
	for(re int i=n;i;--i)a[i]=a[i]-a[i-1];
	a1=a[1];
	printf("%lld\n",check());
	q=read();
	while(q--){
		re int l=read(),r=read(),x=read();
		if(l==1)a1+=x;
		else cg(l,x);
		cg(r+1,-x);
		printf("%lld\n",check());
	}
}
```




---

## 作者：jun头吉吉 (赞：1)

# CF1406D 【Three Sequences】

## 题意
给定一个序列$a_1,a_2,\ldots ,a_n$，长度为$n$的序列$b,c$符合以下条件

1. $a_i=b_i+c_i$
2. $b$为不下降序列，$c$为不上升序列，即$b_i\geq b_{i-1}, c_i\leq c_{i-1}$

有$q$个操作，每次操作可以把$[l,r]$的数增加$x$。求每次操作后最小的$\max(b_i,c_i)$

## 题解
首先，假如我们已经求出了$c_1,c_2,\ldots,c_n$，那么就求出了$a_1-c_1,a_2-c_2,\ldots,a_n-c_n$

由于要满足两个序列的限制，因此：

$$\begin{cases}c_i&\leq c_{i-1}\\ a_i-c_i&\geq a_{i-1}-c_{i-1}\end{cases}$$

简单整理得到$c_i\leq c_{i-1}+\min(0,a_i-a_{i-1})$

那么我们记$\sum_{i=2}^n\min(0,a_i-a_{i-1})=sum$，则$c_n\leq c_1+sum $,**我们这里可以直接取$c_n=c_1+sum$**

然后又有一个显然的性质：$\max(b_i,c_i)=\max(\max(b_1,b_2,\ldots,b_n),\max(c_1,c_2,\ldots,c_n))$。

根据不下降不上升序列的性质，上面那坨就等于$max(b_n,c_1)$

我们假设$c_1=x$，那么$c_n=sum+x$，$b_n=a_n-sum-x$。

要使得$\max(b_n,c_1)$最小，且$b_n+c_1$是定值，我们希望他们尽可能相等。因此若$a_n-sum$是$2$的的倍数，就直接平分了罢。若不是，那么就分别向上向下去试一下，具体操作可以看代码。

于是现在的问题变成了如何维护$sum$，我们发现，若将$[l,r]$同时加上一个$x$，$i\in [l+1,r]$的$\min(0,a_i-a_{i-1})$是不会有变化的，变的只有$\min(0,a_l-a_{l-1})$与$\min(0,a_{r+1}-a_r)$，因此每次操作时把$\min(0,a_l-a_{l-1})$与$\min(0,a_{r+1}-a_r)$的贡献减去，更改后再加上就可以了。

最后一个问题：如何维护加操作。其实办法很多，树状数组和线段树都可以。我这里选择线段树。

## 代码
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
#define int long long
int a[1000000],n,sum=0;
#define lson rt<<1
#define rson rt<<1|1
#define maxn 100010
using namespace std;
struct node{
	int l,r;
	long long ans;
	long long tag;
}t[maxn<<2];
void build(int rt,int l,int r){
	t[rt].l=l,t[rt].r=r;
	t[rt].tag=0;
	if(l==r){
		t[rt].ans=a[l];
		return;
	}
	int mid=l+r>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	t[rt].ans=t[lson].ans+t[rson].ans;
}
void pushdown(int rt){
	t[lson].ans+=t[rt].tag*(t[lson].r-t[lson].l+1);
	t[lson].tag+=t[rt].tag;
	t[rson].ans+=t[rt].tag*(t[rson].r-t[rson].l+1);
	t[rson].tag+=t[rt].tag;
	t[rt].tag=0;
}
void add(int rt,int l,int r,long long x){
	if(t[rt].l>r||t[rt].r<l)return;
	if(t[rt].l>=l&&t[rt].r<=r){
		t[rt].ans+=x*(t[rt].r-t[rt].l+1);
		t[rt].tag+=x;
		return;
	}
	pushdown(rt);
	add(lson,l,r,x);
	add(rson,l,r,x);
	t[rt].ans=t[lson].ans+t[rson].ans;
}
long long query(int rt,int l,int r){
	if(t[rt].l>r||t[rt].r<l)return 0;
	if(t[rt].l>=l&&t[rt].r<=r)return t[rt].ans;
	pushdown(rt);
	return query(lson,l,r)+query(rson,l,r);
}
int get(){
	int tmp=query(1,n,n)-sum;
	if(tmp%2==0){return tmp/2;}
	else{
		double x=1.0*(query(1,n,n)-sum)/2;
		return min(max((int)ceil(x+1),query(1,n,n)-sum-(int)ceil(x+1)),max((int)ceil(x-1),query(1,n,n)-sum-(int)ceil(x-1)));
	}
}
signed main(){
	in::read(n);
	for(int i=1;i<=n;i++){
		in::read(a[i]);
		if(i!=1)sum+=min(0ll,a[i]-a[i-1]);
	}
	build(1,1,n);
	out::write(get());out::putc('\n');
	int q;in::read(q);
	while(q--){
		int l,r,x;
		in::read(l,r,x);
		//for(int i=1;i<=n;i++)
		//	printf("%d ",query(1,i,i));
		//printf("\n");
		if(l!=1)sum-=min(0ll,query(1,l,l)-query(1,l-1,l-1));
		if(r!=n)sum-=min(0ll,query(1,r+1,r+1)-query(1,r,r));
		add(1,l,r,x);
		if(l!=1)sum+=min(0ll,query(1,l,l)-query(1,l-1,l-1));
		if(r!=n)sum+=min(0ll,query(1,r+1,r+1)-query(1,r,r));
		out::write(get());out::putc('\n');
	}
	out::flush();
	return 0;
}
```

---

## 作者：Scintilla (赞：1)

### 题意

给定长度为 $n$ 的序列 $\{a_n\}$，你需要构造不降序列 $\{b_n\}$，不升序列 $\{c_n\}$ 使得对 $\forall i \in [1, n], b_i + c_i = a_i$ 且 $max\{b_i, c_j\}$ 最小，其中 $i, j \in [1, n]$。输出该最小值即可。

### 题解

显然只需 $max\{b_n, c_1\}$ 最小。不妨设 $c_1 = x$，则 $b_1 = a_1 - x$。现在依次填充这两个序列。我们需要尽量使 $b_n$ 最小。若 $a_i \leq a_{i - 1}$，则可令
$$c_i = c_{i - 1} + a_i - a_{i - 1}, b_i = b_{i - 1}$$

否则因为 $c$ 不升，只能令

$$c_i = c_{i - 1}, b_i = b_{i - 1} + a_i - a_{i - 1}$$

这样得到的序列肯定是在 $c_1 = x$ 的情况下最优的，所以

$$b_n = b_1 + \sum\limits_{a_i > a_{i - 1}} a_i - a_{i - 1}$$

令后面的和式为 $d$，则最后的结果 $ans = min\{max\{x, a_1 + d - x\}\}$。注意到 $(x) + (a_1 + d - x)$ 为定值（指两次修改之间），所以当两者相等或差为 $1$ 时最优。注意这里的负数比较恶心，具体细节见代码。

那么怎么进行修改操作呢？我们可以将 $d$ 变成一个长度为 $n - 1$ 的序列，$d_i = a_{i + 1} - a_i$。每次操作相当于将 $d_{l - 1}$ 加上 $x$，将 $d_r$ 减去 $x$，而原来的和式就相当于将 $d$ 中正数的和。那用一个变量（我代码中的 $tot$），统计当前和式的值，每次操作就分情况讨论，对 $tot$ 进行加减即可，正负数比较恶心，具体细节见代码。

### $Code:$

```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)
#define Dep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = false; c = getchar();}
    while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

typedef long long ll;

const int N = 100010;

ll n, a[N], q, d[N], ans, now, tot;

il void s1(ll pos, ll x) {
	if (d[pos] > 0) tot += x;
    else if (d[pos] + x > 0) tot += d[pos] + x;
    d[pos] += x;
}

il void s2(ll pos, ll x) {
	if (d[pos] > x) tot -= x;
    else if (d[pos] > 0) tot -= d[pos];
    d[pos] -= x;
}

int main() {
    n = read();
    Rep(i, 1, n) a[i] = read();
    Rep(i, 1, n - 1) d[i] = a[i + 1] - a[i];
    now = a[1], tot = 0;
    Rep(i, 1, n - 1) if (d[i] > 0) tot += d[i];
    ll ans = now + tot;
    if (ans > 0) ++ans; //若是正数则要加 1
    ans /= 2;
    printf("%lld\n", ans);
    q = read();
    while (q--) {
        ll l = read(), r = read(), x = read();
        if (l == 1) now += x;
        else {
            if (x > 0) s1(l - 1, x); //这里我分正负数讨论了，应该有更简单高效的写法，但我不会 qwq
            else s2(l - 1, -x);
        }
        if (r != n) {
        	if (x > 0) s2(r, x);
	        else s1(r, -x);
			}
        ll ans = now + tot;
        if (ans > 0) ++ans;
        ans /= 2;
    	printf("%lld\n", ans);
    }
    return 0;
}
```


---

## 作者：RockyYue (赞：0)

### 1406D

给定一个序列 $a_1,a_2,\ldots ,a_n$，长度为 $n$ 的序列 $b,c$ 符合以下条件

1. $a_i=b_i+c_i$
2. $b$ 为不下降序列，$ c$为不上升序列，即 $b_i\geq b_{i-1}, c_i\leq c_{i-1}$

有 $q$ 个操作，每次操作可以把 $[l,r]$ 的数增加 $x$。求每次操作后最小的 $\max\{\max_i\{b_i\},max_i\{c_i\}\}$，要求 $O(n)$。

### Sol

- 先不结合操作，对固定的序列 $a$ 分析最优策略。

- 考虑构造，要求 $b$ 不降 $c$ 不增，则 $b_i$ 和 $c_i$ 分别在 $b_{i-1}$ 和 $c_{i-1}$ 基础上操作，要求 $b_i$ 加的值 $c_i$ 减的值均为非负数，且作差为 $a_i-a_{i-1}$。
- 先尝试固定 $b_1$ 和 $c_1$，因为 $b$ 全体 $-\Delta$，$c$ 全体 $+\Delta$ 后依然合法，先令 $b_1=a_1,c_1=0$，最终操作 $\Delta=\lfloor \frac{a_1}{2}\rfloor$。
  - 发现所求即为操作后 $b_n$，则使操作前 $b_n$ 尽量小，则每步 $b_i$ 相对 $b_{i-1}$ 的增量都要尽可能小，若更大则 $c_i$ 更小，同样不利于为后续 $b$ 分担。
- 于是得到策略，对于 $i\ge 2$：
  - 若 $a_i\le a_{i-1}$，$b_i=b_{i-1}$，$c_i=c_{i-1}-(a_{i-1}-a_i)$。
  - $a_i>a_{i-1}$，则 $b_i=b_{i-1}+(a_i-a_{i-1})$，$c_i=c_{i-1}$。
  - 最终 $b_n$ 可以表示为 $a_1+\sum_{i=2}^{n}\{\max\{a_i-a_{i-1},0\}\}$。
- 即对于 $a$ 的差分数组 $d$，答案为 $d_1+\sum_{2\le i\le n\land d_i>0}d_i$，可以维护。

---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF1406D)

[CF's link](http://codeforces.com/problemset/problem/1406/D)

#### 题意：

给定一个序列 $a_1,a_2,\dots,a_n$，长度为 $n$ 的序列 $b,c$ 符合以下条件

1. $a_i=b_i+c_i$
2. $b$ 为不下降序列，$c$ 为不上升序列，即 $b_i ≥ b_{i-1},c_i ≤ c_{i-1}$

有 $q$ 个操作，每次操作可以把 $[l,r]$ 的数增加 $x$，求每次操作最小的 $\max{(b_i,c_i)}$。

#### Solution：

由于 $b$ 为不下降序列，$c$ 为不上升序列

1. 当 $a_i>a_{i-1}$ 时，$c_i=c_{i-1},b_i=b_{i-1}+(a_i-a_{i-1})$。
2. 当 $a_i<a_{i-1}$ 时，$b_i=b_{i-1},c_i=c_{i-1}+(a_i-a_{i-1})$。

定义 $x=c_1$，则 $b_1=a_1-x,b_n=b_1+\sum\limits_{i=2}^{n}{\max(0,a_i-a_{i-1})}$，推出 $x=\frac{a_1+\sum\limits_{i=2}^{n}{\max(0,a_i-a_{i-1})}}{2}$。

修改时用差分维护即可。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-27 15:26:13 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-27 15:59:19
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=1e5+5;
int n,a[N],q,szh;//szh 即为上文的 x
signed main(){
    n=read();
    FOR(i,1,n) a[i]=read();
    FOR(i,2,n) szh+=max(0ll,a[i]-a[i-1]);
    if(a[1]+szh>0) write((a[1]+szh+1)/2),puts("");
    else write((a[1]+szh)/2),puts("");
    REP(i,n,1) a[i]=a[i]-a[i-1];
    q=read();
    while(q--){
        int l=read(),r=read(),x=read();
        if(l==1) a[1]+=x;
        else{
            if(a[l]>0) szh-=a[l];
            a[l]+=x;
            if(a[l]>0) szh+=a[l];
        }
        if(r<n){
            r++;
            if(a[r]>0) szh-=a[r];
            a[r]-=x;
            if(a[r]>0) szh+=a[r];
        }
        if(a[1]+szh>0) write((a[1]+szh+1)/2),puts("");
        else write((a[1]+szh)/2),puts("");
    }
    return 0;
}
```



---

## 作者：Demoe (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1406D)

## 题意

- 给定一个数列 $a$，求两个数列 $b$，$c$，使得 $b_i+c_i=a_i$ 且 $b_i \ge b_{i-1}$ $c_i \le c_{i-1}$。

- 每次修改能将 $a$ 的 $[l,r]$ 中所有元素增加 $x$。

- 每次输出 $max(b_n,c_1)$ 的最小值。

## Sol

~~显然 这题思维简单 代码好写 细节少~~

考虑已经化简到输出一定为 $max(b_n,c_1)$。

我们考虑让它们尽量小。

首先，对于每个 $a_i \ge a_{i-1}$ 我们可以发现 $b_i=b_{i-1}+a_i-a_{i-1}+k(k\ge 0)$，$c_i=c_{i-1}-k$。

对于每个 $a_i \le a_{i-1}$ 可得 $b_i=b_{i-1}+k(k\ge 0)$，$c_i=c_{i-1}+a_i-a_{i-1}-k$。

因为 $c_1$ 在过程中没有影响，所以即可直接考虑 $b_n$ 最小。

那么在 $a_i \ge a_{i-1}$ 时 让 $b_i=b_{i-1}+a_i-a_{i-1}$。

在 $a_i \le a_{i-1}$ 时 让 $b_i=b_{i-1}$。

那么可得 $b_n=b_1+\sum\limits_{i=2}^nmax(a_i-a_{i-1},0)$。

这个第一次可以暴力 $O(n)$ 记录差分跑得。

我们考虑 $max(b_1+\sum\limits_{i=2}^nmax(a_i-a_{i-1},0),a_1-b_1)$ 最小，其中仅有 $b_1$ 为变量。

那么即为 $b_1=\dfrac{a_1-\sum\limits_{i=2}^nmax(a_i-a_{i-1},0)}{2}$ 时取得。

需要向上取整。

我们考虑修改操作。

发现仅有 $a_1$，$a_l-a_{l-1}$，$a_{r+1}-a_r$ 需要修改。

那么直接修改即可达成 $O(1)$ 修改。

即可解决问题。

时间复杂度 $O(n+q)$。

```cpp
// wish to get better qwq
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
ll n,m,a[N],b[N],qaq;
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);
	for(ll i=1;i<=n;i++) rd(a[i]);
	for(ll i=1;i<n;i++) b[i]=a[i+1]-a[i],qaq+=max(b[i],0ll);
//	cout<<qaq<<endl;
	wr(max((a[1]-qaq)/2ll+qaq,a[1]-(a[1]-qaq)/2ll));puts("");
	rd(m);
	for(ll i=0,l,r,x;i<m;i++){
		rd(l);rd(r);rd(x);
		if(l<=1&&r>=1) a[1]+=x;
		if(l-1>=1)qaq-=max(b[l-1],0ll),b[l-1]+=x,qaq+=max(b[l-1],0ll);
	//	cout<<"qaq"<<qaq<<endl;
		if(r<n)qaq-=max(b[r],0ll),b[r]-=x,qaq+=max(b[r],0ll);
	//	cout<<"qaqaq"<<qaq<<endl;
		wr(max((a[1]-qaq)/2ll+qaq,a[1]-(a[1]-qaq)/2ll));puts("");
	}
	return 0;
}

```

---

