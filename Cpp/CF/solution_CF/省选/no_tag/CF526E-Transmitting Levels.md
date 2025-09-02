# Transmitting Levels

## 题目描述

Optimizing the amount of data transmitted via a network is an important and interesting part of developing any network application.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526E/a78fce818bfb1b716eb4c13dcdfd873c3aac4f4e.png)In one secret game developed deep in the ZeptoLab company, the game universe consists of $ n $ levels, located in a circle. You can get from level $ i $ to levels $ i-1 $ and $ i+1 $ , also you can get from level $ 1 $ to level $ n $ and vice versa. The map of the $ i $ -th level description size is $ a_{i} $ bytes.

In order to reduce the transmitted traffic, the game gets levels as follows. All the levels on the server are divided into $ m $ groups and each time a player finds himself on one of the levels of a certain group for the first time, the server sends all levels of the group to the game client as a single packet. Thus, when a player travels inside the levels of a single group, the application doesn't need any new information. Due to the technical limitations the packet can contain an arbitrary number of levels but their total size mustn't exceed $ b $ bytes, where $ b $ is some positive integer constant.

Usual situation is that players finish levels one by one, that's why a decision was made to split $ n $ levels into $ m $ groups so that each group was a continuous segment containing multiple neighboring levels (also, the group can have two adjacent levels, $ n $ and $ 1 $ ). Specifically, if the descriptions of all levels have the total weight of at most $ b $ bytes, then they can all be united into one group to be sent in a single packet.

Determine, what minimum number of groups do you need to make in order to organize the levels of the game observing the conditions above?

As developing a game is a long process and technology never stagnates, it is yet impossible to predict exactly what value will take constant value $ b $ limiting the packet size when the game is out. That's why the developers ask you to find the answer for multiple values of $ b $ .

## 说明/提示

In the test from the statement you can do in the following manner.

- at $ b=7 $ you can divide into two segments: $ 2|421|32 $ (note that one of the segments contains the fifth, sixth and first levels);
- at $ b=4 $ you can divide into four segments: $ 2|4|21|3|2 $ ;
- at $ b=6 $ you can divide into three segments: $ 24|21|32| $ .

## 样例 #1

### 输入

```
6 3
2 4 2 1 3 2
7
4
6
```

### 输出

```
2
4
3
```

# 题解

## 作者：Sparkle_ZH (赞：5)

提供一种不一样的做法。

注意到 $q$ 很小，如果能在 $O(n)$ 的时间内回答单次询问，复杂度是可以接受的。为方便起见，下文中的时间复杂度均为 **单次询问** 的复杂度。

---

假如已经固定了起点位置，那么一个很显然的贪心策略就是：每次在保证和不超过 $k$ 尽可能地向后走，走到不能走为止，就划分为新的一段。

可以预处理出每个点 $i$ 能到的最远位置 $p_i$，这里可以将环扩展成长为 $2n + 1$ 的序列后双指针求解。即便如此，记 $f(i) = p_i + 1$，如果我们暴力枚举起点 $i$ 然后每次按 $[i, f(i) - 1] \rightarrow [f(i), f(f(i)) - 1]$ 跳的话，复杂度还是 $O(n^2)$。是不是还遗漏了什么性质？

记 $ans_i$ 表示以 $i$ 为起点开始跳，最后划分出的段数，答案即为 $\min_{i=1}^n ans_i$。可以得到：

> **结论：** $ans_i \geq ans_{f(i)}$，即以 $f(i)$ 为起点必不劣于以 $i$ 为起点。

> 证明：定义 $g^1(i) = f(i), g^k(i) = f(g^{k-1}(i))$，也就是从 $i$ 开始跳 $k$ 次后的位置。

> 思考以 $i$ 为起点暴力跳的过程，最后的分段形如 $[i, g^1(i) - 1], [g^1(i), g^2(i) - 1], ..., [g^{k1}(i), i - 1]$。

> 同理，以 $f(i)$，也就是 $g^0(i)$ 为起点的分段形如 $[g^1(i), g^2(i) - 1], ..., [g^{k2}(i), g^0(i) - 1]$。

> 注意到大部分的分段都是一样的，显然 $k1 \leq k2$。注意到由 $[g^{k1}(i), i - 1]$ 的分段可知 $g^{k1 + 1}(i) \geq i$，从而 $g^{k1 + 2}(i) \geq g^0(i) - 1$，因此 $k2 \leq k1 + 1$。

> 从而：$ans_i = k1 + 1$，$ans_{f(i)} = k_2$，从而 $ans_i \geq ans_{f(i)}$。

到这里问题已经几乎做完了，任意选择一些 $i$ 然后不断地让 $i \leftarrow f(i)$，直觉告诉我们经过了若干次迭代后 $ans_i$ 必定能取到最小值，此时我们从 $i$ 开始暴力求一遍答案即可。但这是对的吗？迭代多少次呢？可以用图论建模帮我们想清楚问题。

按 $i \rightarrow f(i)$ 连边，注意到每个点的出度恰为 1，所以这是一个内向基环树森林。由前面的结论，可以知道环上每个点的答案一样且均为该连通块内的最优解。所以，直接在每个连通块的环上任取一点，然后暴力跑一遍答案就做完了。时间复杂度 $O(n)$。

---

## 作者：MyukiyoMekya (赞：5)

很妙的一道题。

发现 $q\le 50$ ，所以出题人大概就是想让我们写线性做法。

考虑如果已经知道了起点，断环成链，那么就是一个很经典的贪心问题，能取就取。

我们可以搞个指针线性预处理每个 $i$ 能到达的最远位置 $to_i$ 使得 $[i,to_i]$ 的和 $\le k$。

那么，假设已知起点，单次查询我们可以通过不断跳 $to$ 来达到 $O(ans)$ 的复杂度，$ans$ 为跳的次数。

我们随意选一个 $i$ ，显然有 $to_{i-1} \le to _i$ 。

考虑答案构成情况，我们称从 $i$ 点跳到 $j$ 中 $[i,j-1]$ 为一个块，那么必定有一个块的结尾在 $[i,to_i ]$ 中。

因为考虑某个块的起始位置一定是其前一个块的结尾位置 $+1$，

然后不存在某个块起始位置 $\le i$ 并且其终止位置 $>to_i$，所以没问题。

那么也就是说，我们可以考虑找一个 $i$ ，枚举 $[i+1,to_i+1]$ 为起点，单次查询复杂度为 $O(k\times ans)$

但这可以被卡掉，考虑 $\{1,1,1,1,\cdots ,10^9,10^9,10^9\},k=10^9$。

那么我们考虑在一次跳完整个序列的跳跃过程中，会经过 $ans$ 个点 $x_1,x_2,\cdots , x_{ans}$。

因为 $n\le \sum to_{x_i}-x_i  $ ，根据鸽巢原理，必然存在一个 $to_{x_i}-x_i \le \lfloor \frac {n}{ans} \rfloor$。

那么直接选择这个 $x_i$ ，然后暴力枚举 $[x_i,to_{x_{i+1}}]$ 为起点就好了，单次查询复杂度 $O(\lfloor \frac n{ans}\rfloor \times ans)= O(n)$。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ln putchar('\n')
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
template <class t>inline bool ckmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
const int MaxN=2e6+50;
int a[MaxN],s[MaxN],to[MaxN],n;
inline int go(int st,int ed,int K)
{
	reg int ans=0;
	while(st<=ed)++ans,st=to[st]+1;
	return ans;
}
inline int solve(int K)
{
	if(s[n]<=K)return 1;
	reg int pos=1;
	for(int i=1;i<=n;++i)
	{
		while(s[pos+1]-s[i-1]<=K)++pos;
		to[i]=pos;
	}
	for(int i=1;i<=n;++i)to[i+n]=to[i]+n;
	pos=1;
	for(int i=2;i<=n;++i)if(to[i]-i<to[pos]-pos)pos=i;
	reg int ans=1e9;
	for(int i=pos+1;i<=to[pos]+1;++i)
	{
		reg int st=i>n?i-n:i;
		ckmin(ans,go(st,st+n-1,K));
	}
	return ans;
}
signed main(void)
{
	int q;read(n,q);
	for(int i=1;i<=n;++i)read(a[i]),a[i+n]=a[i];
	for(int i=1;i<=(n<<1);++i)s[i]=s[i-1]+a[i];
	reg int K;
	while(q--)read(K),write(solve(K)),ln;
	return 0;
}
```





---

## 作者：奇米 (赞：5)

# 题解 - $\mathrm{CF526E}$

## 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF526E)

## $\mathrm{Sol}$

* 真没想到 $O(n\log(n)\times Q)$ 卡卡常竟然过了，虽然有更优秀的解法。

考虑枚举第一段的起点 $s$ 以及用 $f_i$ 表示以其作为起点的最小分组。以及假设 $rem$ 为序列的最后部分与开始部分接起来的值，那么答案就考虑如果 $rem\leq b_i$ 即为$f_i$ 否则为 $f_i+1$（相当于把最后一段再分一次）

对于每次更新 $f_i$ 时候记录 $g_i$ 为当前最小分组时候最远能达到的点，$f_i,g_i$ 具体求法可以看代码。

## $\mathrm{Sol}$

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
#define For(i,a,b) for ( register int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
using namespace std;

struct IO
{
	#define MAXSIZE (1 << 20)
	#define isdigit(x) (x >= '0' && x <= '9')
  	char buf[MAXSIZE],*p1,*p2;
  	char pbuf[MAXSIZE],*pp;
  	IO():p1(buf),p2(buf),pp(pbuf){}
  	inline char gc() {
//    	return getchar();
    	if (p1==p2) p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin);
    	return p1==p2?' ':*p1++;
  	}
	inline bool blank(char ch) {return ch==' '||ch =='\n'||ch == '\r'||ch == '\t';}
  	template <class T>
  	inline void read(T &x)
	{
	    register double tmp=1;register bool sign=0; x=0;
	    register char ch=gc();
	    for (;!isdigit(ch);ch=gc()) if(ch=='-') sign=1;
	    for (;isdigit(ch);ch=gc()) x=x*10+(ch-'0');
	    if (ch=='.') for (ch=gc();isdigit(ch);ch=gc()) tmp/=10.0,x+=tmp*(ch-'0');
	    if (sign) x=-x;
  	}
  	inline void read(char *s)
	{
    	register char ch=gc();
		for (;blank(ch);ch=gc());
		for (;!blank(ch);ch=gc()) *s++=ch;
    	*s=0;
  	}
  	inline void read(char &c) {for(c=gc();blank(c);c=gc());}
  	template<class t> inline void write(t x){
		if(x<0) putchar('-'),write(-x);
		else{if(x>9) write(x/10);putchar('0'+x%10);}
	}
} io;

const int mod=1e9+7;
const int mo=998244353;
const int N=1e6+5;

int n,m,a[N],f[N],g[N];
long long b[N];

inline int min(int x,int y) { return (x>y)?y:x;}

signed main()
{
	io.read(n),io.read(m);
	For(i,1,n)
	{
		io.read(a[i]);
		b[i]=b[i-1]+a[i];
	}
	for (;m--;)
	{
		long long x;
		io.read(x);
		if(b[n]<=x) 
		{
			puts("1");
			continue;
		}
		f[n+1]=0;
		Dow(i,n,1)
		{
			g[i]=i;
			int l=i,r=n;
			f[i]=f[i+1]+1;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(b[mid]-b[i-1]<=x) g[i]=mid,l=mid+1;
				else r=mid-1;
			}
			f[i]=f[g[i]+1]+1;
			if(g[i]==n) g[i]=i;
			else if(g[i]+1<=n) g[i]=g[g[i]+1];
		}
		int ans=1e9;
		For(i,1,n) if(b[i-1]<=x)
		{
			long long half=b[n]-b[g[i]-1];
			if(half+b[i-1]<=x) ans=min(ans,f[i]);
			else ans=min(ans,f[i]+1);
		}
		else break;
		io.write(ans),putchar('\n');
	}
	return 0;
}
		
		


```


---

## 作者：灵茶山艾府 (赞：4)

提供一个简单的思路。

题目要我们把数组切成若干段，每一段的元素和都 $\le b$。如果首尾两段的元素和 $\le b$，那么首尾两段可以合并成一段。

**枚举**最后一刀切在 $i$，我们需要知道两个信息：

1. 一共切了多少刀，或者说前 $i$ 个数分成了多少段。
2. 第一刀切在哪。如果首尾两段的元素和 $\le b$，那么分的段数可以减少一。

由于数组元素非负，段的右端点越大，左端点也越大，所以固定右端点时，左端点的最小值可以用滑动窗口计算。

一共切了多少刀，可以用 DP 算：

- 定义 $f_i$ 表示前 $i$ 个数至少要分成多少段。
- 设前 $i$ 个数的最后一段的左端点为 $\ell$，那么问题变成前 $\ell$ 个数至少要分成多少段，即 $f_i = f_{\ell} + 1$。初始值 $f_0=0$。

第一刀切在哪，也可以用 DP 算：

- 定义 $\textit{begin}_i$ 表示前 $i$ 个数的第二段的左端点。
- 如果 $f_i=2$，那么 $\textit{begin}_i=\ell$；否则，$\textit{begin}_i=\textit{begin}_\ell$。

设前缀和数组为 $s$。由于 $i$ 越大 $f_i$ 也越大，所以当我们发现 $s_n - (s_i - s_{\textit{begin}_{\ell}})\le b$ 时，说明首尾两段可以拼成一段，直接输出 $\max(f_i,2)$ 即可。这里和 $2$ 取最大值是因为存在找到第一段后剩余元素就 $\le b$ 的情况，此时 $f_i=1$ 但答案为 $2$。

AC 代码（Golang）：

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, q, b int
	Fscan(in, &n, &q)
	sum := make([]int, n+1)
	for i := 1; i <= n; i++ {
		Fscan(in, &sum[i])
		sum[i] += sum[i-1] // 前缀和
	}
	total := sum[n]

	f := make([]int, n+1)
	begin := make([]int, n+1)
	for range q {
		Fscan(in, &b)
		if total <= b { // 只有一段
			Println(1)
			continue
		}
		l := 0
		for i := 1; ; i++ {
			for sum[i]-sum[l] > b { // 滑动窗口
				l++
			}
			f[i] = f[l] + 1 // 前 i 个数至少要分 f[i] 段
			if f[i] == 2 {
				begin[i] = l // 记录第二段的开始位置
			} else {
				begin[i] = begin[l]
			}
			// 剩余部分 <= b，说明首尾两段可以拼成一段，或者相当于把剩余的后缀拼到了第一段，所以答案就是 f[i]
			if total-(sum[i]-sum[begin[i]]) <= b {
				Println(max(f[i], 2)) // 可能找到第一段就触发 if 了，此时答案是 2
				break
			}
		}
	}
}
```

时间复杂度：$\mathcal{O}(nq)$。

相似题目：[3464. 正方形上的点之间的最大距离](https://leetcode.cn/problems/maximize-the-distance-between-points-on-a-square/)

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：tongzhenxuan (赞：3)

发现 $q\le 50$ 我们可以寻找 $O(n)$ 单次做法。

先考虑对一个怎么做。

1. 对于环上问题，我们可以枚举第一个分割点，当分割点往后移的时候，将上一个加到结尾的元素中。

2. 对于一个点，我们可以尺取的找到它在和为 $k$ 之内最多可以走到哪里，记为 $to_i$。然后我们就可以知道第一个位置走到 $n$ 至少要多少步记为 $f_i$，这个是可以 $O(n)$ 的。



结合上面两条，发现我们每次后移分割点，将最后一个值变大，需要对 $to_i$ 为 $n+1$ 的一些值进行修改，当然是 $i$ 小的更早进行前移一位，最后一个数多一段。当我们把  $i$ 和 $to_i$ 连起来的时候，我们会发现其实是一颗树，实际上是对树中一些子树进行整体的 $-1$ 操作。然后我们可以 dfs 这颗树，我们发现只要前移的时间小于以这个点为分割点的时间，那就还是原来的值，具体实现可以不用 dfs 记一个根下面的最早的祖先即可。

[Submission](https://codeforces.com/contest/526/submission/239018062)

---

## 作者：Fracture_Dream (赞：1)

# 简述题意
给定一个 $n$ 个元素的环形数组 $a$，$q$ 次查询，每次给定一个 $k$，将数组划分为若干个连续段，使得每一段的和都不超过 $k$，最小化连续段个数。

- $2 \le n \le 10^6, 1 \le q \le 50$
- $1 \le a_i \le 10^9,\max\{a_i\} \le k \le 10^{15}$

# 思路
先破环成链，然后求前缀和 $pre$。
对于每一个 $i$，不妨先双指针求出 $nxt_i$，表示最大的满足 $pre_{nxt_i} - pre_{i-1} \le k$ 的点。
显然，如果我们已经知道了某个连续段的起点，那么贪心的往后跳到 $nxt_i+1$，答案是固定的。
然而，如果直接枚举 $n$ 个起点，时间复杂度接受不了，考虑优化。
我们可以发现，无论怎么划分，连续段长度都存在一个下限，那就是 $\min\{nxt_i-i+1\}$，那么每次贪心的时间复杂度即为 $O(\dfrac{n}{\min\{nxt_i-i+1\}})$。不妨令 $nxt_i-i+1$ 最小的这个点为 $x$。

考虑进一步优化：减少枚举起点的数量。

观察上面那个式子的分母，可以想到，无论怎么划分，一定有一个连续段的起点在 $[x,nxt_x+1]$，否则一定划分出来有一个连续段的和大于 $k$，这是显然的。所以枚举起点的复杂度为 $O(nxt_x-x+1)$。

单次查询的时间复杂度为 $O(n)$。

# 代码
很简单的一道 $2400$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 2e6 + 5;
int n , q , a[MAXN] , nxt[MAXN];
ll pre[MAXN] , k;
int Path(int now) {
    if (now > n) now -= n;
    int l = 0 , sum = 0;
    while(l < n) {
        l += nxt[now] - now + 1;
        sum ++;
        now = nxt[now] + 1;
    }
    return sum;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr); 
    cin >> n >> q;
    for (int i = 1 ; i <= n ; i ++) cin >> a[i] , a[i + n] = a[i];
    for (int i = 1 ; i <= 2 * n ; i ++) pre[i] = pre[i - 1] + a[i];
    while(q --) {
        cin >> k;
        int len = 1e9 , st;
        for (int i = 1 , j = 1 ; i <= 2 * n ; i ++) {
            while(j < 2 * n && pre[j + 1] - pre[i - 1] <= k) j ++;
            nxt[i] = j;
            if (nxt[i] - i + 1 < len && i <= n) st = i , len = nxt[i] - i + 1;
        }
        int ans = 1e9;
        for (int i = st ; i <= nxt[st] + 1 ; i ++) ans = min(ans , Path(i));
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF526E 题解

[Problem Link](https://www.luogu.com.cn/problem/CF526E)

**题目大意**

> 给一个大小为 $n$ 的环，$q$ 次询问，每次给定 $k$，要求把环划分成若干段，每段元素和 $\le k$，求最小段数。
>
> 数据访问：$n\le 10^6,k\le 50$。

**思路分析**

显然起点确定后是一个简单贪心，因此处理出以每个位置 $i$ 为开头，贪心取得的下一个开头 $nxt_i$ 在哪里，然后倍增优化跳跃即可做到 $\mathcal O(nq\log n)$。

考虑进一步优化，考虑某个 $i\to nxt_i$，显然不存在任何一个跳跃不经过 $[i,nxt_i]$ 中的元素，因此一定有一个最优解起点在 $i\to nxt_i$ 里，找到最小的一段 $i\to nxt_i$，记长度为 $k$，那么每一次跳跃显然至少经过 $k$ 个点，因此对于同一起点的跳跃次数是 $\mathcal O\left(\dfrac nk\right)$，对于 $k$ 个起点就是 $\mathcal O(n)$ 的。

需要特殊处理经过 $n\to 1$ 的情况。

时间复杂度 $\mathcal O(nq)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e6+5,inf=1e9;
ll sum[MAXN];
int fa[MAXN];
signed main() {
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) scanf("%lld",&sum[i]),sum[i+n]=sum[i];
	for(int i=1;i<=2*n;++i) sum[i]+=sum[i-1];
	for(ll k;q--;) {
		scanf("%lld",&k);
		for(int i=1,j=0;i<=2*n;++i) {
			while(j<=2*n&&sum[j]-sum[i-1]<=k) ++j;
			fa[i]=j;
		}
		int u=1;
		for(int i=1;i<=n;++i) if(fa[i]-i<fa[u]-u) u=i;
		fa[2*n+1]=2*n+1;
		int ans=inf;
		for(int i=u;i<=fa[u];++i) {
			int res=0,s=(i>n?i-n:i);
			for(int p=s;fa[p]<s+n;) p=fa[p],++res;
			ans=min(ans,++res);
		}
		printf("%d\n",ans);
	}
	return 0;
	
}
```

---

## 作者：luogubot (赞：1)

给定环形数组 $a_{1\cdots n}$，$q$ 次询问给定 $k$，要求把数组划分成若干和 $\leq k$ 的段，求最小段数。

$n\leq 10^6$，$q\leq 50$，保证有解。

首先是 $O(qn\log n)$ 的暴力：双指针预处理每个点最远选到哪里，然后倍增。

然后为啥大家都写奇怪需要分析复杂度的做法啊，不如来点更直接的 $O(qn)$。

令上面预处理出来的是 $[i,to_i)$ 是最长合法区间，考虑假设我们钦定 $(n,1)$ 不被跨过会发生什么。只需要从 $x=1$ 开始不断执行 $x\gets to_x$ 直到跨过 $(n,1)$。可是当初始 $x=2$ 时，其最后一段的和不一定满足 $\leq k$，不妨检验最后一段的值加上 $a_1$ 是否仍然 $\leq$，如果可以，前面跳的次数 +1 就可以被贡献到答案；再令 $x=i$ 时不断跳，检验最后一段的和加上 $a_{1\sim i-1}$ 是否 $\leq k$，是的话就能用次数 +1 贡献到答案。可以证明这样能够覆盖到所有情况：

- 如果检验成功，那么等价于从 $i$ 出发一直跳 $to_i$，即正确模拟了以 $i$ 为起点的情况。
- 如果检验失败，考虑最后一段不能跳的到 $n$ 为止都 $\leq k$，加上 $a_{1\sim i-1}$ 之后 $>k$ 了，说明这里产生的最后一段至少需要被切为两段，那么从 $n$ 开始往后加到不能加为止，从那个位置的后一个执行贪心能得到不劣的结果。

实际上，钦定的“断边”是任意边都是正确的。

---

## 作者：SnowTrace (赞：0)

提供若干做法。

首先，如何求出一条链的答案？

考虑设 $nxt_i$ 是以 $i$ 为起点可以到达的最远的位置。

然后可以暴力跳 $nxt_i$。

我们的思路是考虑断环为链的去做。

---------------------

结论：设 强制钦定以 $i$ 为分界点的得到的答案是 $g_i$，则有：$\operatorname{Max}g_i\leq\operatorname{Min}g_i+1$。

考虑 $g$ 中最小的元素，设为 $g_k$。

再考虑一个异于 $g_k$ 的元素，设为 $g_j$。

则 $g_j$ 可以在 $g_k$ 方案上通过一步调整达到值为 $g_k+1$。具体来说，如果 $j$ 是 $g_k$ 中方案的一个起始点，则有 $g_k = g_j$，否则我们把 $j$ 所在的区间分为在 $j$ 前面的和在 $j$ 后面的两段，从而 $j$ 成为分界点，此时操作数是 $g_k+1$。




# Solution 1

这是一个经典做法。我们考虑先对钦定 $1$ 为起点跑一遍，设跑出来答案为 $k$。

设此时划分出的线段的起点序列为 $S_i$。

考察使 $S_i-S_{i-1}$ 最小的 $i$，不妨枚举 $[S_{i-1},S_i)$ 区间内的数，强制钦定其作为端点，然后运行一次上面的算法。

注意到，这里不包括 $S_1-S_k$ 这一项，因为我们认为它不是完整的一段。

样例 $a = \{2,4,2,1,3,2\}$，以 $1$ 为起点的划分中会划分出一个区间 $[6,6]$，但是第 6 个元素在最优解中确实不是一个端点。

这样做时间复杂度是正确的，首先有 $\operatorname {Min}(S_i-S_{i-1})\leq \dfrac{n}{k-1}$，根据抽屉原理易得。

而根据一开始所说的可以知道从任何起点出发都只需要跳 $O(k)$ 次就可以得到答案，或者说，答案的量级是 $O(k)$ 的，你一步一步的跳是可以接受的。

正确性考虑，选出来的这一段实际上是一个极长的合法段，也就是你无法完全越过这个段，否则它就不是一个极长的合法段。

# Solution 2

我们考虑这样的结构，划分出若干个区间，实际上每一个区间的端点都可以当作起点。

这启发我们去钦定一些东西。

我们不妨钦定，包含 $1$ 的区间是在最优划分中最后一个选的。

正确性在于 $1$ 肯定会被选到。

这样做的好处是，这个问题就有了单调性。

我们可以算出以任意 $i$ 为起点，走到**恰好还没包含 1 的位置**（意思是如果再往下走一步就会把 $1$ 包含进去）时具体在哪个位置上，以及走到这个位置需要多少步。

关键在于把原本不能递推的问题通过类似破环成链的方式又变成了链上的 dp。

然后根据钦定，剩下没算的位置（是一个前缀和一个后缀拼起来）会构成一整段，然后还需要判一下这最后一段是不是合法。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define lowbit(x) (x&(-x))
int n,q;int a[1000005],f[1000005],pos[1000005],nxt[1000005],pre[1000005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> q;for(int i =1;i<=n;i++)cin >> a[i];
	for(int i = 1;i<=n;i++)pre[i] = pre[i-1]+a[i];
	while(q--){
		int k;cin >> k;
		int l = 1,s =0;
		for(int i = 1;i<=n;i++){
			l = max(l,i);
			while(l<n+1 and s+a[l]<=k)s+=a[l],++l;
			nxt[i] = l;s-=a[i];
		}
		for(int i = n;i>=1;i--){
			if(nxt[i] == n+1){
				pos[i] = i,f[i] = 1;
			}else{
				pos[i] = pos[nxt[i]];
				f[i] = f[nxt[i]]+1;
			}
		}
		int ans = f[1],sum = 0;
		for(int i = 2;i<=n;i++){
			sum+=a[i-1];
			if(sum+pre[n]-pre[pos[i]-1]<=k)ans = min(ans,f[i]);
		}
		cout << ans << endl;
	}
	return 0;
}
```

# Solution 3

萌萌做法。

我们还是先对钦定 $1$ 为起点跑一遍，设跑出来答案为 $k$。

这个时候我们根据一开始的定理，如果答案比 $k$ 小则答案就一定是 $k-1$。

我们让 $i$ 向 $ nxt_i$ 连边，构成一颗基环树。

然后你需要算每个点往前走 $k-1$ 步能不能恰好走完全程，这个可以递推。

---

## 作者：E1_de5truct0r (赞：0)

## 闲话

我真的服了，第一篇题解 $O(qn\log n)$ 过了，我一个跑不满的 $O(n)$ 被卡了/dk

大常数选手的悲哀。

## 思路

$q \leq 50,n \leq 10^6$，应该是考虑 $O(qn)$ 做法了。

显然考虑断环为链，然后预处理每个点 $i$ 向后最远走的距离 $d_i$。由 $a_i>0$ 得 $d_{i-1}<d_i$，所以直接记录前缀和以及一个右端点的 $r$ 指针扫一遍就行了。

然后考虑怎么统计答案。

最暴力的想法是枚举 $1 \leq i \leq n$，对每个 $i$ 假设它是起点，暴力做一下统计答案。复杂度是 $O(n^2)$ 不能接受。考虑进行优化。

不妨令对于每个 $i$，它的块是 $[i,d_i]$。我们发现，每次变更起点，只对包含这个起点的那些块内有影响。那么我们可以选长度最小的那个块进行枚举，复杂度就是 $O(n)$ 的了。

证明：

假设最后我们从起点 $i$ 跳 $k$ 次就能跳到终点。显然我们可以分成 $k$ 段。而由抽屉原理可得，长度为 $n$ 的线段分成 $k$ 段，最小值最大为 $\left\lfloor\dfrac{n}{k}\right\rfloor$。所以我们每次枚举复杂度是 $O\left(\left\lfloor\dfrac{n}{k}\right\rfloor\right)$，暴力统计是 $O(k)$，总复杂度就是 $O(n)$。

有 $q$ 次询问，每次我们都这样处理，总复杂度为 $O(qn)$。

## 代码

由于我卡常之后的代码太丑了，就不放出来了。

需要的可以来这里：[Link](https://www.luogu.com.cn/paste/sa8ndv4c)

卡完之后跑的还是挺快的qwq

---

