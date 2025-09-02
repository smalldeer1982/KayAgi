# Penchick and Desert Rabbit

## 题目描述

Dedicated to pushing himself to his limits, Penchick challenged himself to survive the midday sun in the Arabian Desert!

While trekking along a linear oasis, Penchick spots a desert rabbit preparing to jump along a line of palm trees. There are $ n $ trees, each with a height denoted by $ a_i $ .

The rabbit can jump from the $ i $ -th tree to the $ j $ -th tree if exactly one of the following conditions is true:

- $ j < i $ and $ a_j > a_i $ : the rabbit can jump backward to a taller tree.
- $ j > i $ and $ a_j < a_i $ : the rabbit can jump forward to a shorter tree.

For each $ i $ from $ 1 $ to $ n $ , determine the maximum height among all trees that the rabbit can reach if it starts from the $ i $ -th tree.

## 说明/提示

In the first test case, the initial heights of trees are $ a = [2, 3, 1, 4] $ .

- If the rabbit starts from the first tree, it can jump to the third tree as $ 3 > 1 $ and $ 1 < 2 $ . Then, the rabbit can jump to the second tree as $ 2 < 3 $ and $ 3 > 1 $ . It can be proved that the rabbit cannot reach the fourth tree; hence, the maximum height of the tree that the rabbit can reach is $ a_2 = 3 $ .
- If the rabbit starts from the fourth tree, it does not need to jump anywhere as it is already at the highest tree.

In the second test case, the rabbit can jump to the first tree regardless of which tree it starts from.

In the fifth test case, if the rabbit starts from the fifth tree, it can jump to the fourth tree. Then the rabbit can jump to the seventh tree and finally reach the sixth tree. Therefore, the maximum height of the tree that the rabbit can reach is $ 8 $ .

## 样例 #1

### 输入

```
5
4
2 3 1 4
5
5 4 3 2 1
4
2 1 1 3
4
1 1 3 1
8
2 4 1 6 3 8 5 7```

### 输出

```
3 3 3 4 
5 5 5 5 5 
2 2 2 3 
1 1 3 3 
8 8 8 8 8 8 8 8```

# 题解

## 作者：TonviaSzt (赞：4)

**很有意思，总结了三种做法。**

---

[Problem Link](https://codeforces.com/contest/2031/problem/D)

**简要题意**

> 有 $q$ 次询问，每次给出长度为 $n\le 5\cdot10^5$ 的序列，称 $i$ 与 $j$ 是互相可达的当且仅当 $i<j\ |\ a_i>a_j$。问从每个位置 $i$ 出发能到达的最大高度。

**思路分析**

赛时给出一种做法，赛后学到两种。不过 CF 的 Editorial 是最巧妙的，三种方法的方向几乎完全不同。

### 赛时做法

连通性问题首先考虑建边跑并查集。朴素想法是考虑一个位置向左一步能跳到的位置，但是这样建边复杂度是 $O(N^2)$ 的。

发现很多边实际是冗余的，当一个位置 $i$ 与其左边满足条件的位置并到一起后，之后的位置只需要连 $i$ 左边最大的 $h_x$ 位置就可以把他们全部并入一个块里。于是可以拿个 $set$ 维护 $i$ 左边 $fa_i=i$ 的位置，每次 $i$ 连边时只需要连 $h>h_i$ 的位置，再把这些已经在一个块内的位置删到只剩一个即可。总复杂度 $O(Tn\log n)$。

赛时并查集不用 dsu 超时了一发，难绷。

[Submission](https://codeforces.com/contest/2031/submission/291635653)

### ？分段法

从同伴那学到的，感觉也很妙。

![](https://cdn.luogu.com.cn/upload/image_hosting/2ljlxqnv.png)

可以发现所有的跳跃都是若干次上图的折线跳跃或者折线的一部分。我们将上述折线分成“向右跳”和“向左跳”两部分。

考虑第二个绿色条 $j$ 怎么更新到第一个绿色条 $i$。倒序扫描，将 $j$ 的贡献记录在 $[j+1,n]$ 中最低的点，再在 $i$ 取出该贡献，可以用树状数组维护最大值实现该功能。具体地，维护后缀最小值 $h_{\min}$，在 $j$ 处时修改树状数组上 $[h_{\min}+1,n]$ 的最大值，在 $i$ 处时取出 $[1,h_i)$ 的最大值，就能实现如图折线跳跃的情况。

这时候再考虑如何求图中红色条的最值，正序扫描，类似上面的情况处理即可。

### Editorial

考虑 $i$ 能否到达 $i+1$，若能跳到必然要么是 $h_i>h_{i+1}$，要么是先从 $i$ 向前跳到某个高于 $h_i$ 的位置 $j$，再从 $j$ 向后跳到 $i$ 后的某个位置 $k$，最后从 $k$ 跳到 $i+1$。

因此维护前缀最大值和后缀最小值，再扫描转移即可，复杂度是可喜的 $O(Tn)$。

[Submission](https://codeforces.com/contest/2031/submission/291677082)

---

真是妙妙妙极了。

---

## 作者：ran_qwq (赞：3)

怎么赛时这么多人写优化建图呢。这不是我们模拟赛题的结论吗。

首先边可以看成双向边。

结论：若 $x,y$ 连通，则 $\forall i\in(x,y)$，$i$ 在 $x,y$ 的连通块中。

证明：

> 第一种情况：$a_x>a_y$。若 $a_x>a_i$，$x$ 和 $i$ 相连；若 $a_i>a_y$，$i$ 和 $y$ 相连。不可能两个条件都不满足。
> 
> 第二种情况：$a_x\le a_y$。此时要满足 $x,y$ 连通，必须存在 $j\in[1,x)$，$a_j>a_x$，或者存在 $j\in(y,n]$，$a_y>a_j$。如果 $a_i\not\in[x,y]$，与第一种情况类似，能连到 $x$ 或 $y$。如果 $a_i\in[x,y]$，可以和 $j$ 连通，而 $j$ 又与 $x,y$ 连通。

故连通块是一个区间，即一个点要么与前一个连通块相连，要么新开一个连通块。

我们只关心 $i$ 与 $i-1$ 的连通情况，即新开连通块的条件是不存在 $j\in[1,i-1)$，$a_j>a_{i-1}$，也不存在 $j\in(i,n]$，$a_i>a_j$。

简化一下，就是 $\max\limits_{j=1}^{i-1}a_j\le\min\limits_{j=i}^na_j$，求个前缀 max 和后缀 min 即可。

时间复杂度 $O(\sum n)$。

---

## 作者：_segmenttree (赞：2)

题意：$i$ 可以跳到 $j$ 当且仅当 $j<i$ 且 $a_j>a_i$ 或 $j>i$ 且 $a_j<a_i$ ，求每个 $i$ 能跳到的最大 $a_j$。

做法：我们发现从一个点开始可能先往后再往前，顺序处理比较麻烦。我们考虑最开始可以较为简单求出答案的点，容易发现 $a_i$ 最大的点往后的点肯定跳到这个点上。

我们的做法就出来了。每次求出答案未确定的点中 $a_i$ 最大的点。如果它能跳到 $j$ 且 $j$ 的答案已求出，答案 $ans_i=ans_j$ (我们是从大往小枚举，先求出的答案肯定大)。 再让它后面所有没求出答案的 $j$ 答案为 $ans_i$ 。


```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N=5e5+10;
    int n,a[N],c[N],ans[N],mn[N];
    bool cmp(int aa,int b) {
        return a[aa]>a[b];
    }
    void solve() {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
           scanf("%d",&a[i]);
        mn[n+1]=1e9;
        for(int i=n;i>=1;i--) 
            c[i]=i,mn[i]=min(mn[i+1],a[i]);
        sort(c+1,c+n+1,cmp);
        int id=c[1];
        for(int i=c[1];i<=n;i++) ans[i]=a[id];
        for(int i=2;i<=n;i++) {
            if(c[i]>id) continue ;
            if(a[c[i]]>mn[id]) ans[c[i]]=ans[id];
            else ans[c[i]]=a[c[i]];
            for(int j=c[i];j<id;j++) ans[j]=ans[c[i]];
            id=c[i];
        }
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    signed main() {
        int t;
        cin>>t;
        while(t--) solve();
        return 0;
    }
```

---

## 作者：Lyw_and_Segment_Tree (赞：2)

## 题意简述

有 $n$ 棵树，第 $i$ 棵树的高度为 $a_i$，有一只兔子，并且有如下条件：

- 若 $j \lt i$ 且 $a_j \gt a_i$，则兔子可以从第 $i$ 棵树跳到第 $j$ 棵树

- 若 $j \gt i$ 且 $a_j \lt a_i$，则兔子可以从第 $i$ 棵树跳到第 $j$ 棵树

现在求对于所有的 $1 \le i \le n$，求兔子从第 $i$ 棵树出发所能达到的最大高度。

## 开始解题！

这个题的思路其实是比较显然的，可以维护前缀最大值和后缀最小值来计算答案。具体实现如下：

定义 $pre_i$ 表示前 $i$ 个数的最大值，即 $pre_i = \max(pre_{i - 1}, a_i)$，注意需要把 $pre_0$ 设为一个极小的数（比如 `LLONG_MIN`）。

定义 $suf_i$ 表示从 $i$ 到 $n$ 的最小值，**注意需要倒序遍历**，则 $suf_i = \min(suf_{i + 1}, a_i)$，注意需要把 $suf_{n + 1}$ 设为一个极大的数（比如 `LLONG_MAX`）

那么这样维护有什么好处呢？那么显然，通过维护这些值，不需要担心时序问题，即 $j \lt i$ 或 $j \gt i$ 的条件已经自然满足。然后对于第 $i$ 棵树，在理想状态下，其最小可以跳到 $suf_{i + 1}$，最大可以跳到 $pre_i$，那么接下来考虑的就是应该如何跳？

所以应该如何跳呢？定义 $ans_i$ 表示树 $i$ 能跳到的最大高度，为了计算 $ans_i$，会有两种情况：

- 若 $pre_i \gt suf_{i + 1}$，此时我们假设 $a_x = pre_i, a_y = suf_{i + 1}$，那么对于第 $i + 1$ 棵树，一定可以通过 $i + 1 \rightarrow y \rightarrow x \rightarrow i$ 到达第 $i + 1$ 棵树，第 $i$ 棵树也可以通过 $i \rightarrow x \rightarrow y \rightarrow i + 1$ 的顺序到达第 $i + 1$ 棵树，那么我们可以得出任何可以从树 $i$ 到达的树都可以从树 $i + 1$ 到达，反之亦然；因此对于这种情况，$ans_i = ans_{i + 1}$。

- 反之，即 $pre_i \le suf_{i + 1}$，那么第 $i$ 棵树无法到达第 $i + 1$ 到第 $n$ 棵树中的任何一棵树，则对于这种情况，$ans_i = pre_i$。

最后，为了使答案最优，我们从右往左遍历，防止答案错误。

时间复杂度 $O(Tn)$，代码易得。

code : 

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double

using namespace std;

ll a[1000005], pre[1000005], suf[1000005], ans[1000005];  

char buf[1 << 21], *p1 = buf, *p2 = buf;
 
const ll getc() {
    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
}
 
const ll read() {
	ll x = 0, f = 1;
	
	char ch = getc();
	
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1; ch = getc();
	}
	
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
	}
	
	return x * f;
}
 
const void write(ll x) {
    ll sta[35], top = 0;
    
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    
    while (top) putchar(sta[--top] + 48);
}

int main() {
    ll T = read();

    while (T--) {
        ll n = read();

        for (ll i = 1; i <= n; i++) {  
            a[i] = read();
        }

		pre[0] = LLONG_MIN;

        for (ll i = 1; i <= n; i++) {
			pre[i] = max(a[i], pre[i - 1]);
		}

		suf[n + 1] = LLONG_MAX;

		for (ll i = n; i; i--) {
			suf[i] = min(a[i], suf[i + 1]);
 		}

        for (ll i = n; i; i--) {  
            if (pre[i] > suf[i + 1]) {
                ans[i] = ans[i + 1];
            } else {
                ans[i] = pre[i];
            }
        }
  
        for (ll i = 1; i <= n; i++) {
            write(ans[i]), putchar(' ');
        }

        puts("");
    } 

    return 0;  
}
```

[AC record](https://codeforces.com/contest/2031/submission/291877285)

---

## 作者：w9095 (赞：2)

[CF2031D Penchick and Desert Rabbit](https://www.luogu.com.cn/problem/CF2031D)

赛时 A,B,C 共计吃了 $5$ 发罚时，这就是我的真实实力！来补篇题解。

考虑分析每一个位置的性质，不难发现最后一个位置一定能跳到最大值的位置。

接下来，我们考虑第 $n-1$ 个位置。类比最后一个位置，我们发现，这个位置一定能跳到 $1\sim n-1$ 内含有的最大值。此时，$1\sim n-1$ 内的其他树均没有意义。因为一方面它们不会成为答案，一定不会被跳到，另一方面由于往后跳只能跳到更小的位置，所以若要跳到 $n$，则选取 $1\sim n-1$ 内的最大值就够了。如果可以跳到，我们发现可以直接跳到最后一个位置能跳到最大值，可以直接继承。

我们不妨推广一下。如果已知 $i+1$ 能跳到最大值，如何求出 $i$ 能跳到最大值？显然还是一定能跳到 $1\sim i$ 内含有的最大值，且必然还是从最大值往回后跳。考虑往后跳能跳到的最大位置一定是 $i+1$ 能跳到最大值，如果不是 $i+1$ 能跳到最大值，那么 $i+1$ 一定也能跳到这个位置，矛盾。因此，我们只需要看能不能跳到 $i+1\sim n$ 的最小值，再直接跳到 $i+1$ 继承能跳到最大值即可。

这样一想，动态规划的思路就清晰了。预处理前缀最大值与后缀最小值，即可做到 $O(n)$ 递推。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,a[600000],mx[600000],mi[600000],f[600000];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld",&n);
	   	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	   	mx[0]=0,mi[n+1]=1e18;
	   	for(int i=1;i<=n;i++)mx[i]=max(mx[i-1],a[i]);
	   	for(int i=n;i>=1;i--)mi[i]=min(mi[i+1],a[i]);
	   	f[n]=mx[n];
	   	for(int i=n-1;i>=1;i--)
	   	    if(mx[i]>mi[i+1])f[i]=f[i+1];
	   	    else f[i]=mx[i];
	   	for(int i=1;i<=n;i++)printf("%lld ",f[i]);
	   	printf("\n");
	   }
	return 0;
}
```

---

## 作者：tai_chi (赞：1)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18549167) 中阅读。

#### 题意

给一个序列，兔子向更大的下标跳只能跳到更矮的位置，向更小的下标跳只能跳到更高的位置，问从每个 $i \in [1,n]$，从 $i$ 出发能跳到的最高的位置。

#### 分析

首先答案的下界是前缀最大值。

考虑一个跳的策略：先向大下标跳到一个很矮的位置，再向小下标跳到一个很高的位置。这个过程可以重复以到达较靠后的位置。注意到这实际表明了前面的高的位置可以继承后面的矮的位置的答案，这启发我们倒着扫。

我们先把答案置为前缀最大值，然后从后往前扫，每个位置继承后面比自己矮的位置的答案，用单点修前缀 max 的 BIT 可以维护。

```cpp
template <class T>
struct BIT
{
	// 查询前缀 单点修改
	// BIT<T> b(len);
	const int n;
	vector<T> a;
	BIT(int _n) : n(_n), a(_n+5) {}
	int lowbit(int x) { return x&(-x); }
	T query(int pl)
	{
		if(pl<=0) return 0;
		T res=0;
		for(int i=pl;i;i-=lowbit(i)) res=max(res,a[i]);
		return res;
	}
	void add(int pl,T x)
	{
		if(pl<=0) return;
		for(int i=pl;i<=n;i+=lowbit(i)) a[i]=max(a[i],x);
	}
};

void solve()
{
	int n; cin>>n;
	vector<int> a(n+5),mx(n+5),ans(n+5);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) mx[i]=max(a[i],mx[i-1]);
	BIT<int> A(n);
	for(int i=n;i>=1;i--)
	{
		ans[i]=max(mx[i],A.query(mx[i]-1));
		A.add(a[i],ans[i]);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<"\n";
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

题目要求每个位置能跳到的最高高度，而由跳跃操作的条件可知往前跳是一定会变高的，往后跳是一定会变矮的。所以思考为啥会往后跳？肯定是当前位置到后一个比它矮的位置中间有比它高的才会往后跳去取到那个更高的位置。

设 $dp_i$ 为 $i$ 能跳到的最大高度，$v_i=\displaystyle\max_{j=1}^i a_j$（即前缀最大值）。因为可以一直往前跳，初始化 $dp_i=v_i$。从后往前扫，有转移：$dp_i\gets\displaystyle\max_{i<j,a_j<v_i}dp_j$，就是说可以从前缀最大值那个地方往后跳到一个比它低的位置。很明显的二维偏序关系，以 $a$ 为下标放在树状数组上，可以优化至 $O(n\log n)$。

# Code

```cpp
#include<bits/stdc++.h>
inline int lowbit(int x){
	return x&-x;
}
int t[500005];
int n;
inline void add(int x,int y){
	for(;x<=n;x+=lowbit(x))t[x]=std::max(t[x],y);
}
inline int ask(int x){
	static int s;s=0;
	for(;x;x^=lowbit(x))s=std::max(s,t[x]);
	return s;
}
int dp[500005];
int a[500005];
int T;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]),dp[i]=std::max(dp[i-1],a[i]),t[i]=0;
		for(int i=n;i;--i)
			add(a[i],dp[i]=std::max(dp[i],ask(dp[i]-1)));
		for(int i=1;i<=n;++i)
			printf("%d%c",dp[i]," \n"[i==n]);
	}
	return 0;
}
```

---

## 作者：Xuan_qwq (赞：1)

### 题目大意
给定一个长为 $N$ 的数列 $A$，在所有逆序对间建边，求每个点所在的连通块大小。

### 思路
这看起来就很像 [CF1638C](https://www.luogu.com.cn/problem/CF1638C) 啊，只不过数列是可重的。

我们考虑怎么把这题转换过去。我们知道相同的数之间是不建边的，所以我们把相同的数转换成单增连续数列，不同的数转换之后相对大小关系不变，这样边的关系还是一样的。

然后我们就知道独立联通快形成的条件：$h_1$ 到 $h_i$ 构成长为 $i$ 的排列，则一个联通块一定以 $h_i$ 结尾，且联通块内最大值为 $i$。

所以只需要计算 $h_1$ 至 $h_i$ 的前缀和，如果当前前缀和等于 $\frac{i\times (i+1)}{2}$，则出现了一个新的联通块，记录该联通快内的答案即可。

另外我们还要记录转换后的数对应的原数，千万不要直接输出转换后的答案！

### ACcode
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T,n,a[500005],cnt[500005],pre[500005],ans[500005],id[500005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cnt[i]=0;//多测要清空！！！
		for(int i=1;i<=n;i++)cin>>a[i],cnt[a[i]]++;//开桶记录每个数出现多少次
		for(int i=1;i<=n;i++)pre[i]=pre[i-1]+cnt[i];//前缀和
		for(int i=1;i<=n;i++){
			cnt[a[i]]--;//这个数又取了一个
			id[pre[a[i]]-cnt[a[i]]]=a[i];//记录转换前后对应的数
			a[i]=pre[a[i]]-cnt[a[i]];
			//这两句顺序不能换
		}
		int sum=0,lst=1;
		for(int i=1;i<=n;i++){
			sum+=a[i];
			if(sum==(i+1)*i/2){
				for(int j=lst;j<=i;j++)ans[j]=id[i];//记录答案
				lst=i+1;//更新分割点
			}
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：lilong (赞：0)

一眼 dp。

设 $f_i$ 表示从第 $i$ 个位置出发能跳到的最大值。考虑**从后往前**枚举，对于当前位置 $i$，其往前跳到的最大值即为 **$a$ 的前缀最大值**。而如果先往后跳，那么就可以跳到比 $a_i$ 小的位置。而这些位置能跳到的最大值已经计算好了，因此可以直接使用。转移的位置只与 $a_i$ 有关，因此只需要维护 **$f$ 的前缀最大值**并支持单点修改即可。树状数组就是一种简单的方法。

单组数据时间复杂度 $O(n \log n)$。


```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

int n,f[1000001],a[1000001],mx[1000001],mi[1000001],t[2000001],k,tot;

int lowbit( int x )
{
	return x & ( -x );
}

void xg( int x , int y )
{
	for( int i = x ; i <= n ; i += lowbit( i ) )
		t[i] = max( t[i] , y );
	return;
}

int cx( int x )
{
	int s = 0;
	for( int i = x ; i >= 1 ; i -= lowbit( i ) )
		s = max( s , t[i] );
	return s;
}

void solve( void )
{
	cin >> n;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i];
	for( int i = 1 ; i <= n * 2 ; i ++ )
		t[i] = 0;
	mx[1] = a[1];
	for( int i = 2 ; i <= n ; i ++ )
		mx[i] = max( mx[i - 1] , a[i] );
	for( int i = n ; i >= 1 ; i -- )
	{
		f[i] = mx[i];
		f[i] = max( f[i] , cx( mx[i] - 1 ) );
		xg( a[i] , f[i] );
	}
	for( int i = 1 ; i <= n ; i ++ )
		cout << f[i] << ' ';
	cout << '\n';
	return;
}

signed main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 );
	int T;
	cin >> T;
	while( T -- )
		solve();
	return 0;
}
```

---

## 作者：fanminghao000 (赞：0)

## 题目大意

一个兔子在一个数列上跳动，从每个位置可以跳到任意一个满足以下条件的位置：

- 往左边跳，终点的值必须大于当前位置的值
- 往右边跳，终点的值必须小于当前位置的值

求出以每个位置作为起点时能跳到的最大的值

## 做法

显然在最大值右边的数都可以跳到最大值上，所以这一部分的答案一定就是序列最大值，也是整个答案序列能达到的最大答案。

那么剩余的数呢？贪心地想，对于离最大值不远的数，它们肯定也想跳到最大值右边的某一个数，让自己变成最大的答案。为此，它会先跳到它左边一个最大的数，再从这个数跳到右边能跳到的最远的位置。那这个策略能否运用到所有数上呢？

是可以的，因为答案序列实际上是单调不降的。这也很好理解。假设一个位置 $i$，在 $i$ 右边且值小于 $a_i$ 的实际上都要先跳到 $i$ 再向右跳，因此答案和 $i$ 位置的答案是一样的；如果值大于 $a_i$，那它一定能跳到 $i$ 位置能跳到的位置以及之后的位置上，答案肯定不小于 $i$ 位置的答案。也就是说答案序列单调不降，一直跳到右边能跳到的最远位置的贪心是正确的。

于是，这个题目就很好做了，有很多种方法可以维护。

这里我维护了一个前缀最大值 $pre$，也就是每个位置向前跳能跳到的最大的值；以及一个后缀最小值 $bac$，也就是向后跳能跳到的最小的值。对于每个位置 $i$，其答案就是 $bac$ 中第一个大于 $pre_i$ 的位置的答案，可以用二分求得这个位置。当然也有可能根本就跳不到后面，这时候答案就是 $pre_i$。具体实现看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

int pre[500010],bac[500010],a[500010],t[500010],ans[500010],n; 
int main(){
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=0;i<=n+1;i++) t[i]=ans[i]=pre[i]=0,bac[i]=1e9; 
		int w=0,maxa=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]>maxa) w=i,maxa=a[i],ans[i]=a[i];
		}
		for(int i=1;i<=n;i++) pre[i]=max(pre[i-1],a[i]);
		for(int i=n;i>=1;i--) bac[i]=min(bac[i+1],a[i]);
		for(int i=w;i<=n;i++) ans[i]=maxa;
		for(int i=w-1;i>=1;i--){
			int p=lower_bound(bac+1,bac+n+1,pre[i])-bac-1;
			ans[i]=max(ans[p],pre[i]);
		}
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<' ';
		}
		cout<<endl;
	}
	return 0;
} 
```

---

## 作者：AK_400 (赞：0)

观察样例，发现答案是不减的，因为
> - $ j < i $ and $ a_j > a_i $ : the rabbit can jump backward to a taller tree.

也就是说要跳到更高的树只能从下标大的跳到下标小的。于是我们考虑已知 $i+1$，的答案后怎么得到 $i$ 的答案。

声明：下文中 $mx_i,mn_i，ans_i$ 分别表示 $[1,i]$ 的最大值,$[i,n]$ 的最小值和以 $i$ 为起点能跳到最高的高度。

如果 $mx_i>mn_{i+1}$,那么 $ans_i=ans_{i+1}$。

因为
> - $ j < i $ and $ a_j > a_i $ : the rabbit can jump backward to a taller tree.

于是如果兔子在 $i$，那么它一定能跳到 $mx_i$ 所在的位置。

因为
> - $ j > i $ and $ a_j < a_i $ : the rabbit can jump forward to a shorter tree.

于是如果 $mx_i>mn_{i+1}$ 那么如果兔子在 $i$，那么它一定能跳到 $mn_{i+1}$ 所在的位置。

同理，它能跳到 $i+1$，所以 $ans_i=ans_{i+1}$。

如果 $mx_i\le mn_{i+1}$，那么 $ans_i=mx_i$。原因同上。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500005],mx[500005],mn[500005],ans[500005];
void slv(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        mx[i]=mx[i-1];
        if(mx[i]<a[i])mx[i]=a[i];
    }
    mn[n]=a[n];
    for(int i=n-1;i>=1;i--){
        mn[i]=mn[i+1];
        if(mn[i]>a[i])mn[i]=a[i];
    }
    ans[n]=mx[n];
    for(int i=n-1;i>=1;i--){
        if(mx[i]>mn[i+1])ans[i]=ans[i+1];
        else ans[i]=mx[i];
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    cout<<endl;
    for(int i=1;i<=n;i++)a[i]=mx[i]=mn[i]=ans[i]=0;
}
int main(){
    int T;cin>>T;while(T--)
    slv();
    return 0;
}
```

---

## 作者：zhouruoheng (赞：0)

## D

赛时的清奇想法。

首先发现能跳跃的两个位置是逆序对，因此考虑用并查集维护，并记录集合内最大值与最小值。

再考虑这样一种做法，先遍历一遍数组，目前遇到的最大值为 $x$，下标为 $id$，加入一个数 $a_i$。

* 若 $a_i>=x$ 更新 $x$ 和 $id$。
* 若 $a_i<x$ 那么就合并 $i$ 和 $id$。

以最后一组样例为例：  
![](https://cdn.luogu.com.cn/upload/image_hosting/c4v91nfl.png)

用 $mx_i$ 表示集合 $i$ 中最大的 $a_i$，$mi_i$ 表示最小值。

然后考虑合并不同集合，从后往前，如果出现两个不同集合 $i,j$ 且 $i<j$。由前面的过程易知 $mx_i \le mx_j$，如果 $mx_i>mi_j$，就说明这两个集合可以合并。  
那有没有可能出现不是相邻的集合合并呢？答案是否定的，考虑 $k,i,j$ 三个集合，$mx_k \le mx_i \le mx_j$，如果 $i$ 与 $j$ 不能合并，则 $mx_i \le mi_j$，就会有 $mx_k \le mx_i \le mi_j$，显然 $k$ 与 $j$ 不能合并。因此每个集合都只能和相邻的集合合并。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=5e5+5;
int n;
int a[N],ans[N];
int fa[N],mi[N],mx[N];
int find(int x)
{
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    x=fa[x],y=fa[y];
    fa[y]=x;
    mi[x]=min(mi[x],mi[y]);
    mx[x]=max(mx[x],mx[y]);
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        fa[i]=i;
        mi[i]=mx[i]=a[i];
    }
    int x=a[1],id=1;
    for(int i=2;i<=n;i++) 
    {
        if(a[i]<x) merge(id,i);
        else x=a[i],id=i;
    }
    
    for(int i=n-1;i>=1;i--)
        if(find(i)!=find(i+1)&&mi[find(i+1)]<mx[find(i)])
            merge(i,i+1);
    for(int i=1;i<=n;i++) cout<<mx[find(i)]<<' ';
    cout<<'\n';
}
int main ()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}

```

---

## 作者：StrSeeker (赞：0)

写一下赛时做法。

容易发现每一个点先向左跳到前缀最大值处一定是不劣的，因为高度可能增加，同时位置更靠前，能跳到后面的机会显然就越多。

定义 $dp_i$ 表示从第 $i$ 个点开始跳能跳到的最大高度。根据向左边跳的结论，我们可以设置 $dp_i$ 的初始值为 $premax_i$。我们只用更新向右跳的 $dp$ 值，因为向左跳一定可以取到最大的那个。

考虑如何更新答案。当 $i<j$ 且 $dp_i>h_j$ 时，点 $i$ 可以跳到点 $j$。需要注意的是点 $i$ 最初始能够到达的最大高度是前缀最大值（$dp_i$ 的初始值）而不是 $h_i$。

问题转化为求点 $i$ 后面所有高度小于 $dp_i$ 的位置的最大 $dp$ 值。显然可以使用树状数组维护。在高度一维开树状数组并维护前缀最大值，每一次更新 $dp$ 值时区间修改即可。

单组询问时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
int a[maxn],dp[maxn],c[maxn],n;
int lowbit(int x){return x&(-x);}
void add(int p,int x)
{
	for(int i=p;i<=n;i+=lowbit(i)) c[i]=max(c[i],x);
}
int query(int p)
{
	int res=0;
	for(int i=p;i;i-=lowbit(i)) res=max(res,c[i]);
	return res;
}
void solve()
{
	cin>>n;
	int mx=-1;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		c[i]=0;
		mx=max(mx,a[i]);
		dp[i]=mx;
	}
	for(int i=n;i;i--)
	{
		dp[i]=max(dp[i],query(dp[i]-1));
		add(a[i],dp[i]);
	}
	for(int i=1;i<=n;i++) cout<<dp[i]<<' ';
	cout<<'\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
}
```

---

## 作者：Binah_cyc (赞：0)

一道脑电波好题。

看见 $1 \le a_i \le n$ 的数据范围，就知道需要枚举高度，不然它为什么要给这样的数据范围。加上 $n \le 5 \times 10^5$ 的数据范围，就知道时间复杂度大概率为 $O(n \log n)$ 或者 $O(n)$。

我们先考虑哪些树能够跳到高度为 $n$ 的树上。显然，在 $n$ 后面的树都能跳到它上面。因为贪心，它们必定会跳到 $n$ 上，我们在后面将不会考虑它们。

一棵树只要能够跳到任意一棵在 $n$ 后面的树，它就能借助这棵树跳到 $n$ 上面。而能够跳到 $n$ 后面的树等价于能够跳到 $n$ 后面高度最低的树上。我们设它的高度为 $x$，我们就成功的将问题从一棵树能否跳到高度为 $n$ 的树上转化为了一棵树的高度是否大于 $x$。

我们将这个结论继续推广，从高到低考虑每一个高度，如果这个高度的树能够跳到前面某一棵树上面，那就跳。使用单调栈维护每一个树的高度与跳到它的阈值，查询的时候二分即可。

示例代码：
```c
// Problem: D. Penchick and Desert Rabbit
// Contest: Codeforces - Codeforces Round 987 (Div. 2)
// URL: https://codeforces.com/contest/2031/problem/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define push_back emplace_back
const int N=5e5+5;
int _,n;
vector<int> a;
vector<pair<int,int> > s;
int ans[N];
int cnt[N];

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>_;
	while(_--)
	{
		cin>>n;
		a.reserve(n);
		for(int i=1,x;i<=n;i++) cin>>x,a.push_back(x),cnt[x]++;
		for(int i=n;i;i--)//按高度从高到低考虑每一棵树
		{
			if(cnt[i])
			{
				int l=0,r=s.size()-1,num=-1;
				while(l<=r)
				{
					int mid=(l+r)>>1;
					if(i<=s[mid].first) l=mid+1;
					else r=mid-1,num=mid;
				}
				if(num!=-1) num=s[num].second;
				else num=i;//二分出这棵树能够跳到的最高的树
				int minn=i;
				//考虑这棵树后面的树，更新答案
				while(cnt[i])
					ans[a.size()]=num,cnt[a.back()]--,minn=min(minn,a.back()),a.pop_back();
				if(!s.size()||minn<s.back().first) s.emplace_back(minn,num);//将这棵树的高度与阈值入栈
			}
		}
		for(int i=1;i<=n;i++) cout<<ans[i]<<' ',ans[i]=0;
		cout<<endl;
		while(s.size()) s.pop_back();
	}
	return 0;
}
```

---

