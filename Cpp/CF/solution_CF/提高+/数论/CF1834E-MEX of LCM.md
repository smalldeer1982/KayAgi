# MEX of LCM

## 题目描述

You are given an array $ a $ of length $ n $ . A positive integer $ x $ is called good if it is impossible to find a subsegment $ ^{\dagger} $ of the array such that the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of all its elements is equal to $ x $ .

You need to find the smallest good integer.

A subsegment $ ^{\dagger} $ of the array $ a $ is a set of elements $ a_l, a_{l + 1}, \ldots, a_r $ for some $ 1 \le l \le r \le n $ . We will denote such subsegment as $ [l, r] $ .

## 说明/提示

In the first test case, $ 4 $ is a good integer, and it is the smallest one, since the integers $ 1,2,3 $ appear in the array, which means that there are subsegments of the array of length $ 1 $ with least common multiples of $ 1,2,3 $ . However, it is impossible to find a subsegment of the array with a least common multiple equal to $ 4 $ .

In the second test case, $ 7 $ is a good integer. The integers $ 1,2,3,4,5 $ appear explicitly in the array, and the integer $ 6 $ is the least common multiple of the subsegments $ [2, 3] $ and $ [1, 3] $ .

In the third test case, $ 1 $ is a good integer, since the least common multiples for the integer in the subsegments $ [1, 1], [1, 2], [2, 2] $ are $ 2,6,3 $ , respectively.

## 样例 #1

### 输入

```
6
3
1 2 3
5
1 2 3 4 5
2
2 3
1
1000000000
12
1 8 4 2 3 5 7 2 9 10 11 13
12
7 2 5 4 2 1 1 2 3 11 8 9```

### 输出

```
4
7
1
1
16
13```

# 题解

## 作者：樱雪喵 (赞：16)

不会做 \*2300。鉴定为没救了。

## Description

给定长度为 $n$ 的序列 $a$，求最小正整数 $x$，使得 $x$ 不是 $a$ 任何一个子段的 $\operatorname{lcm}$。

$T\le 5\times 10^4,\sum n\le 3\times 10^5$。

## Solution

考虑答案的上界，因为长度为 $n$ 的序列只有 $n^2$ 个子段，那么答案必然是不超过 $n^2$ 的。但实际答案的上界是 $n\log n$，我们将在随后给出证明。

固定当前区间的左端点 $l$，则在 $r$ 右移过程中，区间 $\operatorname{lcm}$ 显然不会变小，因此只有 **不变/变大** 两种情况。  
对于 $\operatorname{lcm}$ 变大的情况，不难发现新的 $\operatorname{lcm}$ 一定是旧 $\operatorname{lcm}$ 的倍数。也就是说，每次变大，$\operatorname{lcm}$ 的值是至少翻倍的。又根据上文所述，当 $\operatorname{lcm}$ 增大到超过 $n^2$ 就已经不可能成为答案了，无需继续枚举。那么对于每个 $l$，有效的 $\operatorname{lcm}$ 只有 $\log n$ 个，证得答案的上界为 $n\log n$。

那么问题的瓶颈变成了：如何只枚举变大的位置的 $\operatorname{lcm}$ 值？   
~~于是这只菜喵就不会了。~~

考虑倒序枚举 $l$，并维护上一轮所有出现过的 $\operatorname{lcm}$ 值。那么这一轮就只让 $a_l$ 对上一轮出现的所有值求 $\operatorname{lcm}$ 就好了。这个东西用 set 是容易维护的。

```cpp
#define int long long
const int N=3e5+5;
int n,a[N];
set<int> ans,s;
il int lcm(int x,int y) {return x/__gcd(x,y)*y;}
signed main()
{
	int T=read();
	while(T--)
	{
		n=read(); ans.clear(),s.clear();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=n;i;i--)
		{
			set<int> now;
			for(auto x:s) if(lcm(x,a[i])<1e9) now.insert(lcm(x,a[i]));
			now.insert(a[i]),swap(now,s);
			for(auto x:s) ans.insert(x);
		}
		int lst=0,res=0;
		for(auto x:ans)
			if(x>lst+1) {res=lst+1;break;}
			else lst=x;
		printf("%lld\n",res?res:lst+1);
	}
	return 0;
}
```

---

## 作者：stntn (赞：8)

涉及到求区间 $\text{lcm}$ 考虑暴力，但暴力是 $O(n^2\log n)$ 的。

尝试粗略估计一个答案上界。如果我们取出前 $n+1$ 个质数，可以发现其中至少有一个不会出现，所以答案不会超过 $p_{n+1}$，这个数大概在 $4 \times 10^6$ 左右。

于是考虑这样一个暴力：假设我们枚举左端点，暴力向右拓展求 $\text{lcm}$，当值大于上界时退出。显然复杂度没有保证，比如一排 $2$。但是如果每次求 $\text{lcm}$ 都保证其值增加，那么复杂度就是对的，因为这样做每个左端点不会超过 $\log V$ 次（$V$ 为 $p_{n+1}$）。

至于怎么保证每次都增加就比较简单了，比如随便写个倍增找到最后一个点使得 $\text{lcm}$ 不变，然后跳过去。

总复杂度 $O(n \log n \log V)$ ~~简单易懂，跑得飞快~~。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 6000010
#define M 300010
#define int long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int T,n,ans,pri[N],cc,a[M],nxt[M][21],pre[M][21];
bool inp[N];
map<int,bool> vis;
inline void Pre(int lim=6000000)
{
	rep(i,2,lim)
	{
		if(!inp[i]) pri[++cc]=i;
		for(int j=1;j<=cc&&i*pri[j]<=lim;j++)
		{
			inp[i*pri[j]]=1;
			if(i%pri[j]==0) break;
		}
	}
}
inline int lcm(int x,int y)
{
	if(x==-1||y==-1) return -1;
	return x/__gcd(x,y)*y;
}
signed main()
{
	Pre();read(T);
	while(T--)
	{
		read(n);vis.clear();ans=1;int lim=pri[n+1];
		printf("%d\n",lim);
		rep(i,1,n)
		{
			read(a[i]),nxt[i][0]=i+1;
			if(pre[i][0]>lim) pre[i][0]=-1;
		}
		rep(i,1,n) pre[i][0]=(i<n?lcm(a[i],a[i+1]):-1);
		rep(i,0,20) nxt[n+1][i]=n+1,pre[n+1][i]=-1;
		per(i,n,1) rep(j,1,20)
		{
			nxt[i][j]=nxt[nxt[i][j-1]][j-1];
			if(nxt[i][j]<=n)
			{
				pre[i][j]=lcm(pre[i][j-1],pre[nxt[i][j-1]][j-1]);
				if(pre[i][j]>lim) pre[i][j]=-1;
			}
			else pre[i][j]=-1;
		}
		rep(i,1,n)
		{
			int pos=i,cur=a[i];vis[cur]=1;
			while(1)
			{
				per(j,20,0) if(nxt[pos][j]<=n&&lcm(pre[pos][j],cur)==cur) pos=nxt[pos][j];
				if(pos>=n) break;
				cur=lcm(cur,a[++pos]);
				if(cur>lim) break;
				vis[cur]=1;
			}
		}
		for(;vis[ans];ans++);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：童年的小翼龙 (赞：5)

感谢 @llingy 和 @LRC0511 大佬！

## 题意简述

你有 $n$ 个正整数 $a_i(1\leq a_i \leq 10^9)$，你需要找到最小的一个正整数 $x$，使得**不存在**任一区间 $[l,r]$ 满足 $\operatorname{lcm}_{l\leq i \leq r}\{a_i\} = x$。

## 题解

容易发现，在左端点固定的时候，若右端点向右移动，则区间的 $\operatorname{lcm}$ 值要么不变，要么至少乘 $2$。而对于一个质数，它不可能成为任意两个与它不等的数的 $\operatorname{lcm}$，而第 $3\times 10^5+1$ 个是 $4256233$，所以在所有区间的 $\operatorname{lcm}$ 中，那些大于 $4256233$ 的是没有用的。因此，记 $V=4256233$，则当左端点固定的时候，不同的有用 $\operatorname{lcm}$ 只有 $\log V$ 个。

考虑从右向左移动移动左端点，并且维护以当前点为左端点的不同 $\operatorname{lcm}$。具体地，可以用两个 ```set``` $A,B$ 分别维护当前存在的不同 $\operatorname{lcm}$ 和所有可能有用的 $\operatorname{lcm}$，左端点左移到 $i$ 的时候，需要将 $a_i$ 放入  $A$，并遍历 $A$ 中本来就存在的区间，对 $a_i$ 取 $\operatorname{lcm}$ 后重新放入 $A$。每次更新完之后，就把当前 $A$ 中的元素放入 $B$ 中。最后对 $B$ 中的元素求 $\operatorname{mex}$ 即可。

时间复杂度 $O(n\log^2V)$

评测记录：[CF](https://codeforces.com/contest/1834/submission/210191043) & [洛谷](https://www.luogu.com.cn/record/112974401)

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Kycida{
using ll = long long;
const int N = 114.5e4;
set <ll> myset , tmp , tmptmp;
int n , a[N];
ll lcm(ll x , ll j){return x * j / __gcd(x , j);}
int main()
{
    int T; cin >> T;
    while(T--) {
        cin >> n; myset.clear(); tmp.clear();
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = n; i > 0; i--) {
            tmptmp.clear(); tmptmp.insert(a[i]);
            for (auto j : tmp) {
                ll tt = lcm(j , a[i]);
                if (tt < 5e6) {
                    tmptmp.insert(tt);
                }
            }
            tmp.clear();
            for (auto j : tmptmp) {
                tmp.insert(j);
                myset.insert(j);
            }
        }
        int ans = 1;
        for (; myset.count(ans); ans++);
        cout << ans << '\n';
    }
    return 0;
}
}int main()
{
    ios :: sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    return Kycida :: main();
}
```

---

## 作者：CYZZ (赞：2)

# [MEX of LCM](https://www.luogu.com.cn/problem/CF1834E)
## 思路
考虑一个比较暴力的做法：枚举 $n$ 轮，把每轮求出的 $\operatorname{lcm}$ 扔进一个 `set` 里。每次把 $a_i$ 和上一轮 `set` 里的值继续求 $\operatorname{lcm}$，把计算出来的值扔进 $ans$ 集合里。最后遍历 $ans$ 求答案。

但是，这样做的复杂度和直接枚举子段的复杂度差不了多少。考虑优化，把一定不会改变答案的 $\operatorname{lcm}$ 剔除，不让它更新后面的值。

一个简单的性质：加入一个新的值求 $\operatorname{lcm}$ 不会使 $\operatorname{lcm}$ 变小。

可以缩小答案的上界。一个质数只能是它自己（和 $1$）的 $\operatorname{lcm}$，所以 $n+1$ 个质数中肯定有一个取不到。于是我们可以把大于第 $n_{\max}+1$ 个质数（也就是 $4256233$）的 $\operatorname{lcm}$ 直接排除。

实现挺简单的，可以直接康注释。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,val[300005];
set<int>a,b,c;//a为答案集合,b为这一轮的lcm,c为上一轮的lcm
long long lcm(int x,int y)
{
    return 1ll*x*y/__gcd(x,y);
}
void solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&val[i]);
    }
    a.clear();
    c.clear();
    for(int i=1;i<=n;i++)
    {
        b.clear();
        c.insert(1);//val[i]也会成为lcm
        for(auto j:c)
        {
            if(lcm(val[i],j)<=4780478)//答案上界
                b.insert(lcm(val[i],j));
        }
        c.clear();
        for(auto j:b)
        {
            a.insert(j);
            c.insert(j);
        }
    }
    int mex=1;
    while(a.find(mex)!=a.end())//暴力找答案
        mex++;
    printf("%d\n",mex);
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
}
```
希望本篇题解能帮到大家！！！

---

## 作者：Xy_top (赞：1)

学校里口胡的时候什么性质都发现了，但是懒得往下想了，就想了 $3$ 个 $\log$ 的。（枚举左端点，二分 $\operatorname{lcm}$ 的变化位置，求区间 $\operatorname{lcm}$）

考虑答案的上界，可以先考虑一个素数什么时候被计入答案，显然是这个数组中出现了这个素数，那么答案的上界就显然是第 $300001$ 个素数。

这个数并不大，也就是 $3000000$ 左右的样子，然后来看 $\operatorname{lcm}$，每次 $\operatorname{lcm}$ 变化至少乘以 $2$，$\log 3000000$ 次就超出了答案上界，统计它就没意义了。

于是可以先枚举左端点，然后二分每次 $\operatorname{lcm}$ 的变化位置，再用猫树（目前想不到 $O(1)$ 求区间 $\operatorname{lcm}$ 的办法），这样就是 $3$ 个 $\log$，无法通过。

考虑由 $i+1$ 为起点所有能凑出的 $\operatorname{lcm}$（根据刚刚的分析，只有 $\log$ 级别） 再加上 $a_i$ 就能得到以 $i$ 为起点能凑出的所有 $\operatorname{lcm}$，最后将这些答案都放到 ``set`` 里去重，能够做到 $O(n\log^2 n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, mex;
int a[300005];
set <int> s, ans, tmp;
int gcd (int x, int y) {
	if (y == 0) return x;
	return gcd (y, x % y);
}
int lcm (int x, int y) {return x * y / gcd (x, y);}
void solve () {
	s.clear ();
	ans.clear ();
	cin >> n;
	For (i, 1, n) cin >> a[i];
	foR (i, n, 1) {
		tmp.clear ();
		for (int j : s) {
			if (lcm (j, a[i]) <= 4256249) tmp.insert (lcm (j, a[i]) );
			ans.insert (j);
		}
		tmp.insert (a[i]);
		swap (s, tmp);
	}
	for (int i : s) ans.insert (i);
	int mex = 1;
	for (int i : ans)
		if (i == mex) ++ mex;
	cout << mex;
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}

```


---

## 作者：Lithium_Chestnut (赞：1)

原文链接在自己博客杂题里面，就不挂了。

---

yx 神发题解的题，有必要做做，CF *2300，无言以对。

很暴力的一道题，对于 lcm 这个概念还是比较抽象的一个小 trick，对于一个序列求所有元素的 lcm，若我们向序列中继续插入一个元素，整个序列的 lcm 一定不会减小，只能不变或变大。

不难发现答案一定不会超过 $n^2$，再加上去重之后答案值域缩小到 $\text{log } n$ 以内，故有一种比较暴力的思路，又不难发现 $\text{lcm(a,b,c)=lcm(lcm(a,b),lcm(b,c))}$，因此我们考虑枚举 $a_i$ 中的每一位，并开一个 `set` 来维护上一次询问中所有的 lcm 值，再求 lcm 即可，不断把每次求得的 lcm 进行更新，存储到一个答案集合中，最后查询时找到与其下标不相同的第一个元素即可。

警钟长鸣：不开 ll 见祖宗。

```
#include<bits/stdc++.h>
#define Std_Maker lhm
#define ll long long
using namespace std;
const int N=3e5+1;
ll n,q,x;
bool ok;
array<ll,N> a;
set<ll> ans,lst,now,ins;
ll gcd(ll a,ll b)
{
    if(!b) return a;
    else return gcd(b,a%b);
}
ll lcm(ll a,ll b)
{
    return a/gcd(a,b)*b;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>q;
    while(q--)
    {
        cin>>n;
        ok=0;
        ins.clear(),ans.clear(),lst.clear(),now.clear();
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            ans.insert(a[i]);
        }
        for(int i=n;i>=1;i--)
        {
            now.insert(a[i]);
            for(auto j:lst)
            {
                if(lcm(j,a[i])<9e10)
                {
                    now.insert(lcm(j,a[i]));
                    ans.insert(lcm(j,a[i]));
                }
            }
            swap(now,lst);
            now.clear();
        }
        for(int i=1;i<=ans.size();i++) ins.insert(i);
        for(auto i:ins)
        {
            if(ans.find(i)==ans.end())
            {
                cout<<i<<endl;
                ok=1;
                break;
            }
        }
        if(ok==0) cout<<ans.size()+1<<endl;
    }
    return 0;
}
```

---

## 作者：masonpop (赞：1)

数学神题。提供一个较为好写的做法。

首先考虑估计答案范围。容易发现，设前 $n+1$ 个素数是 $p_1,p_2,\cdots p_{n+1}$，则这 $n+1$ 个素数中必有至少一个不出现。把第 $300001$ 个素数塞进线性筛板子跑一下发现是 $4256233$。这样答案的值域就被确定了，设为 $T$。

我们先考虑固定左端点。发现一个关键性质：每次加入一个数求 $\text{lcm}$ 时，如果答案变化，则最小公倍数至少乘 $2$。那么，固定左端点时本质不同的最小公倍数其实只有 $\log T$ 级别。


知道了这个就好办了。可以从右往左枚举左端点，具体做法是：用一个容器 $S$ 维护上一轮的 $\text{lcm}$ 集合。那么枚举 $S$ 中的值，由于我们可以把当前左端点的元素 $a_i$ 与上一轮的区间拼接，故把 $a_i$ 和 $S$ 中的数取 $\text{lcm}$ 后放回去就得到了新的值，加入答案集合，同时更新集合 $S$。

但是这个去重工作不好处理。考虑什么容器可以高效维护集合并随时去重？显然是 $\text{set}$。这样就完成了这道题，总时间复杂度 $O(n\log^2 T)$。[代码](https://codeforces.com/contest/1834/submission/210316985)。

---

## 作者：az__eg (赞：0)

首先看到这道题，感觉可以枚举答案。

我们发现 $a_i \leq 10 ^ 9$，那么也就是说对序列每个数分解质因数，大于 $\sqrt{10^9}$ 的质数至多 $n$ 个。那么从大于 $\sqrt{10^9}$ 的第一个质数开始，到大于 $\sqrt{10 ^ 9}$ 的第 $3 \times 10 ^5$ 个质数，肯定有一个质数不能被 $\operatorname{lcm}$ 取到，根据上述式子发现答案小于 $3 \times 10 ^ 6$。

我们可以枚举每次 $\operatorname{lcm}$ 区间的起点，然后当 $\operatorname{lcm}$ 超过 $3 \times 10 ^ 6$ 就肯定可以直接退出了。但我们发现一个一个跳右端点太慢了，发现每次 $\operatorname{lcm}$ 的值必定增加 $1$ 倍，那么我们考虑用这个性质求，我们从后往前扫，维护一个数组表示一这个端点为左端点的区间的不同的 $\operatorname{lcm}$。然后每次后退一次就扫一遍更新 $\operatorname{lcm}$，并去重和删掉大于 $\operatorname{lcm}$ 的数，最后再判断当前这个数独立加进去是否重复或者大于 $3 \times 10 ^ 6$ 即可。

时间复杂度 $(n \log^2 V)$。

---

## 作者：honglan0301 (赞：0)

## 题目分析

大体做法题解已经讲得很详细了（答案上界 $O(n\log n)$，从每个位置开始的 $<B$ 的前缀 $\text{lcm}$ 至多 $\log B$ 种），我下面提供一个时间复杂度优化到 $O(n\log n)$ 的技巧。

首先尝试递推求出从每个位置开始的前缀 $\text{lcm}$。不妨记从 $i$ 开始的前缀 $\text{lcm}$ 为集合 $\{b_i\}$，设 $m_{l,r}$ 表示 $\text{lcm}(a_l,a_{l+1},\dots,a_r)$。那么由其性质可知 $m_{l,r}=\text{lcm}(a_l,m_{l+1,r})$，于是发现若 $m_{l+1,r_1}=m_{l+1,r_2}$ 则一定有 $m_{l,r_1}=m_{l,r_2}$，故有 $\{b_i\}=\{a_i\}\bigcup \{\text{lcm}(a_i,c)\}\ (c\in \{b_{i+1}\})$，即从 $i$ 开始的前缀 $\text{lcm}$ 可以由从 $i+1$ 开始的递推过来。

此时直接暴力递推的话时间复杂度是 $O(n\log^2 n)$ 的，原因是要求 $O(n\log n)$ 次两个数的 $\text{lcm}$，而单次求 $\text{lcm}(a,b)=\frac{ab}{\gcd(a,b)}$ 是 $O(\log n)$ 的。前者不太好优化，但我们可以把后者的时间复杂度均摊掉：

注意到 $m_{l,r}\mid m_{l,r+1}$，所以有 $\gcd(a_i,m_{l,r})=\gcd(\gcd(a_i,m_{l,r+1}),m_{l,r})$，于是转移时可以从后向前算 $\gcd$ 以最大化利用信息，一次转移的效果等价于只进行一次辗转相除（可以势能分析），故总时间复杂度降到了优秀的 $O(n(\log n+\log n))=O(n\log n)$。

## 代码

非常好写，并且加快读后容易跑到最优解。

```cpp
const int B=4600000;
int t,n,a[300005],zt[4600005],us[8000005],nm[2][65],tp[2],tpu,na,nb;
int gcd(int x,int y) {return !y?x:gcd(y,x%y);}

signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n; for(int i=1;i<=n;i++) cin>>a[i]; tp[0]=tp[1]=tpu=na=0,nb=1;
		for(int i=n;i>=1;i--,na^=1,nb^=1)
		{
			int ng=a[i]; ll nl=tp[nb]=0;
			for(int j=1;j<=tp[na];j++) {nl=(ll)a[i]*nm[na][j]/(ng=gcd(ng,nm[na][j])); if(nl<=B&&nl!=nm[nb][tp[nb]]) us[++tpu]=nm[nb][++tp[nb]]=nl;}
			if(a[i]<=B&&a[i]!=nm[nb][tp[nb]]) us[++tpu]=nm[nb][++tp[nb]]=a[i];
		}
		for(int i=1;i<=tpu;i++) zt[us[i]]=1; 
		for(int i=1;i<=B;i++) if(!zt[i]) {cout<<i<<endl; break;} 
		for(int i=1;i<=tpu;i++) zt[us[i]]=0; 
	}
}
```


---

