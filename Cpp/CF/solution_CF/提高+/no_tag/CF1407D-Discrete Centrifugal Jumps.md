# Discrete Centrifugal Jumps

## 题目描述

There are $ n $ beautiful skyscrapers in New York, the height of the $ i $ -th one is $ h_i $ . Today some villains have set on fire first $ n - 1 $ of them, and now the only safety building is $ n $ -th skyscraper.

Let's call a jump from $ i $ -th skyscraper to $ j $ -th ( $ i < j $ ) discrete, if all skyscrapers between are strictly lower or higher than both of them. Formally, jump is discrete, if $ i < j $ and one of the following conditions satisfied:

- $ i + 1 = j $
- $ \max(h_{i + 1}, \ldots, h_{j - 1}) < \min(h_i, h_j) $
- $ \max(h_i, h_j) < \min(h_{i + 1}, \ldots, h_{j - 1}) $ .

At the moment, Vasya is staying on the first skyscraper and wants to live a little longer, so his goal is to reach $ n $ -th skyscraper with minimal count of discrete jumps. Help him with calcualting this number.

## 说明/提示

In the first testcase, Vasya can jump in the following way: $ 1 \rightarrow 2 \rightarrow 4 \rightarrow 5 $ .

In the second and third testcases, we can reach last skyscraper in one jump.

Sequence of jumps in the fourth testcase: $ 1 \rightarrow 3 \rightarrow 5 $ .

## 样例 #1

### 输入

```
5
1 3 1 4 5```

### 输出

```
3```

## 样例 #2

### 输入

```
4
4 2 2 4```

### 输出

```
1```

## 样例 #3

### 输入

```
2
1 1```

### 输出

```
1```

## 样例 #4

### 输入

```
5
100 1 100 1 100```

### 输出

```
2```

# 题解

## 作者：zhoukangyang (赞：26)

## 蒟蒻语
[到蒟蒻无人问津的博客园里看/kel](https://www.cnblogs.com/zkyJuruo/p/13666216.html)

写了 $100$ 行的 线段树上 ST 表维护二分维护单调栈维护 dp, 结果最后发现只要俩单调栈就好了 = =
## 蒟蒻解
首先 $dp_i$ 表示从 $1$ 楼到 $i$ 楼要跳几次。

题目中有 3 个条件, 对三个条件分别设 $dp$ 方程。

第一个很显然， 就是 : $dp_i = dp_{i - 1} + 1$

第二个怎么弄呢？

考虑看有哪些点是可能来更新这个点的。

假设 $x$ 位置可以来更新 $i$ 位置。那么 $h_x > max(h_{x+1}, h_{x + 2} ... h_{i - 1})$。

考虑使用单调栈。单调栈里面的节点满足严格递增。 这样 $x$ 就一定是单调栈中的节点了

因为要求 $h_i > max(h_{x+1}, h_{x + 2} ... h_{i - 1})$，所以如果单调栈中有一个数比他大，那么单调栈中在他之后的节点就不能更新他了。

可以在单调栈中边弹点边更新答案。

第三个条件和第二个几乎一样，不说了。

## 蒟蒻码

细节看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 7;

int n, m, s[N], dp[N], atot, a[N], btot, b[N];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &s[i]);
	memset(dp, 0x3f, sizeof(dp));
	a[++atot] = 1, b[++btot] = 1, dp[1] = 0;
	for(int i = 2; i <= n; i++) {
		dp[i] = dp[i - 1] + 1;
		while(atot && s[i] >= s[a[atot]]) {
			if(s[i] != s[a[atot]]) dp[i] = min(dp[i], dp[a[atot - 1]] + 1);
			--atot;
		}
		while(btot && s[i] <= s[b[btot]]) {
			if(s[i] != s[b[btot]]) dp[i] = min(dp[i], dp[b[btot - 1]] + 1);
			--btot;
		}
		a[++atot] = i, b[++btot] = i;
	}
	printf("%d\n", dp[n]);
	return 0;
}
```

---

## 作者：封禁用户 (赞：13)

### 前置知识 

[单调栈](https://oi-wiki.org/ds/monotonous-stack/)

### 分析

根据题目的状态转移方程，使用两个单调栈分别维护 $a_i$ 前面的数字中中最后一个大于 $a_i$ 和最后一个小于 $a_i$ 的数字下标，分别记为 $x$ 和 $y$。

则状态转移方程：

- $dp_1 = 0$

- $dp_i = \min(dp_{i-1},dp_x,dp_y) + 1$

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10^48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define N 300010
int n,a[N],dp[N];
stack<int> s1,s2;
int main()
{
	read(n);
	F(i,1,n) read(a[i]);
	s1.push(1);
	s2.push(1);
	F(i,2,n)
	{
		dp[i] = dp[i-1] + 1;
		while(s1.size()&&a[i] <= a[s1.top()])
		{			
			int p = a[s1.top()];
			s1.pop();
			if(s1.size()&&a[i] < p) dp[i] = min(dp[i],dp[s1.top()] + 1);
		}
		s1.push(i);
		while(s2.size()&&a[i] >= a[s2.top()])
		{			
			int p = a[s2.top()];
			s2.pop();
			if(s2.size()&&a[i] > p) dp[i] = min(dp[i],dp[s2.top()] + 1);
		}
		s2.push(i);
	}
	write(dp[n]);
	return 0;
}
```


---

## 作者：胖头鱼学员 (赞：4)


# [CF1407D](https://codeforces.com/contest/1407/problem/D)

## 题意

一条线上按顺序有$n$个大楼，第$i$个高$h_i$，你从第$1$号楼要跳到$n$号楼，求最少步数。
你可以从$i$跳跃到$j$，要求$i < j$，并且要么$i + 1$ ~ $j - 1$之间的高度均比$h_i$和$h_j$小，要么均比$h_i$和$h_j$大。

## 做法

你可以一个$dp$解决它，只需要枚举之前最高的，和当前跳到哪个，还有之前跳了几步这三个量即可。但是很明显，$O(n^3)$的算法直接$TLE$了。所以本蒟蒻提供一个方法：单调栈。

首先不难发现一个点可以由题目中描述的几点转移过来（$i$是当前点，$j$是可以转移到$i$的任意点，$j < i$）。

ps（敲重点）：
要么对于任意一个$i$、$j$、$k$（$j < k < i$，$k \in i、j$）。
1. 都是严格按照$min(h[i],h[j]) > h[k]$（$k$满足$h_k$最大），即单调递增；
2. 都是严格按照$max(h[i],h[j]) < h[k]$（$k$满足$h_k$最小），即单调递减。

所以我们可以维护两个单调栈，每次加入一个点是就$T$掉一些数，使得这两个栈还是单调递增或递减的。

## 代码如下$QAQ$

蒟蒻的我曾曰：“$STL$它不香吗。”

~~仅仅只是因为我不会写而已~~

```cpp
#include <iostream>
#include <stack>

using namespace std;

const int kMaxN = 300001;
const int Max = ~(1 << 31);

int n;
int h[kMaxN];

int f[kMaxN];

stack<int> s[2];

bool Check(int i, int x, bool l) {
  return l ? h[x] > h[i] : h[x] < h[i];
}

void Work(int i, bool l, bool res) {
  while (!s[l].empty()) {
    int x = s[l].top();
    if (Check(i, x, l)) {
      break;
    }
    res = h[x] != h[i];
    f[i] = min(f[i], f[x] + 1);
    s[l].pop();
  }
  if (res && !s[l].empty()) {
    f[i] = min(f[i], f[s[l].top()] + 1);
  }
  s[l].push(i);
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
  }
  fill_n(f, n + 1, Max);
  f[1] = 0, s[0].push(1), s[1].push(1);
  for (int i = 2; i <= n; i++) {
    Work(i, 0, 1);
    Work(i, 1, 1);
  }
  cout << f[n];
  return 0;
}
```

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18543542)

# 思路

注意到第二个条件和第三个条件本质相似，可以用相同的维护方式处理，因此这个只讨论第二个条件的维护方式。

定义 $dp_i$ 表示走到 $i$ 的最少步数。第一个条件的转移显然为 $dp_i \leftarrow dp_{i - 1}$。

对于第二个条件，$i$ 能向 $j$ 转移，当且仅当 $h_{i + 1 \sim j - 1}$ 都比 $h_i,h_j$ 高。不妨将 $i,j$ 的限制分开，对于 $j$ 而言，一个合法的 $i$ 必须满足 $\max_{p = i + 1}^{j - 1}\{h_p\} < h_j$。不难发现合法的 $i$ 一定是对于 $j$ 的一个后缀，可以二分 + ST 表 $\Theta(\log n)$ 求出这个后缀。

对于 $i$ 同样得满足这个条件，用一个 set 维护所有可能合法的位置。每一次插入一个 $j$，需要将所有 $\geq h_j$ 的位置全部删掉，因为对于 $j + 1$ 合法的 $i$ 必须满足 $h_i < h_j$。

现在问题变成查询一个后缀中在 set 中的元素的 $dp$ 值的 $\min$。可以在线段树上维护，将所有不在 set 中的位置赋为 inf 即可。因为每一个元素都只会进出 set 一次，时间复杂度 $\Theta(n \log n)$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define chmin(a,b) (a = min(a,b))

using namespace std;

typedef pair<int,int> pii;
const int N = 3e5 + 10,M = 24;
const int inf = 1e9 + 10;
int n;
int arr[N],dp[N];
set<pii> st1,st2;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct{
    #define pot(x) (1 << x)

    int lg[N],dp1[N][M],dp2[N][M];

    inline void build(){
        for (re int i = 2;i <= n;i++) lg[i] = lg[i >> 1] + 1;
        for (re int i = 1;i <= n;i++) dp1[i][0] = dp2[i][0] = arr[i];
        for (re int j = 1;j <= lg[n];j++){
            for (re int i = 1;i + pot(j) - 1 <= n;i++){
                dp1[i][j] = min(dp1[i][j - 1],dp1[i + pot(j - 1)][j - 1]);
                dp2[i][j] = max(dp2[i][j - 1],dp2[i + pot(j - 1)][j - 1]);
            }
        }
    }

    inline int querymin(int l,int r){
        int x = lg[r - l + 1];
        return min(dp1[l][x],dp1[r - pot(x) + 1][x]);
    }

    inline int querymax(int l,int r){
        int x = lg[r - l + 1];
        return max(dp2[l][x],dp2[r - pot(x) + 1][x]);
    }

    #undef pot
}st;

struct{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int Min;
    }tr[N << 2];

    inline void pushup(int u){
        tr[u].Min = min(tr[ls(u)].Min,tr[rs(u)].Min);
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r,inf};
        if (l == r) return;
        int mid = l + r >> 1;
        build(ls(u),l,mid); build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int x,int k){
        if (tr[u].l == tr[u].r) return (tr[u].Min = k),void();
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(ls(u),x,k);
        else modify(rs(u),x,k);
        pushup(u);
    }

    inline int query(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].Min;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid && r > mid) return min(query(ls(u),l,r),query(rs(u),l,r));
        else if (l <= mid) return query(ls(u),l,r);
        else return query(rs(u),l,r);
    }

    #undef ls
    #undef rs
}T1,T2;

inline void upd(pii x){
    while (!st1.empty() && (*st1.rbegin()).fst >= x.fst){
        T1.modify(1,(*st1.rbegin()).snd,inf);
        st1.erase(prev(st1.end()));
    }
    while (!st2.empty() && (*st2.begin()).fst <= x.fst){
        T2.modify(1,(*st2.begin()).snd,inf);
        st2.erase(st2.begin());
    }
    st1.insert(x); st2.insert(x);
    T1.modify(1,x.snd,dp[x.snd]); T2.modify(1,x.snd,dp[x.snd]);
}

int main(){
    n = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    st.build();
    T1.build(1,1,n); T2.build(1,1,n);
    upd({arr[1],1});
    for (re int i = 2;i <= n;i++){
        dp[i] = dp[i - 1] + 1;
        int l = 1,r = i - 1;
        while (l < r){
            int mid = l + r >> 1;
            if (st.querymin(mid,i - 1) > arr[i]) r = mid;
            else l = mid + 1;
        }
        if (st.querymin(l,i - 1) > arr[i]) chmin(dp[i],T1.query(1,max(1,l - 1),i - 1) + 1);
        l = 1,r = i - 1;
        while (l < r){
            int mid = l + r >> 1;
            if (st.querymax(mid,i - 1) < arr[i]) r = mid;
            else l = mid + 1;
        }
        if (st.querymax(l,i - 1) < arr[i]) chmin(dp[i],T2.query(1,max(1,l - 1),i - 1) + 1);
        upd({arr[i],i});
    }
    printf("%d",dp[n]);
    return 0;
}
```

---

## 作者：lfxxx (赞：3)

看到这个形式就往单调栈上想了。

条件 $1$ 是简单的。

条件 $2$ 与条件 $3$ 对称，这里只考虑条件 $2$。

其等价于区间 $[i+1,j-1]$ 中的数全部小于 $h_i$ 也小于 $h_j$。

于是考虑从前往后扫描时建立单调栈，我们发现可能成为决策的点就是单调栈中的点（单调栈遇到等于的情况时需要弹掉前面的），进一步地，可能成为点 $j$ 的决策点 $i$ 一定是在加入点 $j$ 时单调栈中被弹掉的值。于是记一下最短路值就是 $O(n)$ 的。

需要注意一个细节，当弹掉的最后一个点不等于 $h_j$ 时，这个点在单调栈上的前一个点也能作为决策点 $i$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+114;
int stk_mx[maxn],dp_mx[maxn],tpmx;
int stk_mi[maxn],dp_mi[maxn],tpmi;
int a[maxn],n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    stk_mx[++tpmx]=1,dp_mx[tpmx]=0;
    stk_mi[++tpmi]=1,dp_mi[tpmi]=0;
    for(int i=2;i<=n;i++){
        int dp=maxn;
        int lstmx=-1,lstmi=-1;
        while(tpmx>0&&a[stk_mx[tpmx]]<=a[i]) dp=min(dp,dp_mx[tpmx]+1),lstmx=a[stk_mx[tpmx]],tpmx--;
        while(tpmi>0&&a[stk_mi[tpmi]]>=a[i]) dp=min(dp,dp_mi[tpmi]+1),lstmi=a[stk_mi[tpmi]],tpmi--;
        if(lstmx!=a[i]&&tpmx>0) dp=min(dp,dp_mx[tpmx]+1);
        if(lstmi!=a[i]&&tpmi>0) dp=min(dp,dp_mi[tpmi]+1);
        if(i==n){
            cout<<dp<<'\n';
        }
        stk_mx[++tpmx]=i;
        dp_mx[tpmx]=dp;
        stk_mi[++tpmi]=i;
        dp_mi[tpmi]=dp;
    }
    return 0;
}

```

---

## 作者：SunnyYuan (赞：2)

## 思路

首先，不难想到，是这两种情况才可以转移：

![](https://cdn.luogu.com.cn/upload/image_hosting/az3z28bm.png)

然后我们可以维护两个单调栈：

![](https://cdn.luogu.com.cn/upload/image_hosting/0gemtvpc.png)

对于这两种情况，我们要仔细想一想怎么从之前的一个 $i$ 转移到 $j$ 了，注意是**从 $i$ 转移到 $j$**。

首先，我们想一想，现在我们来到了 $j$。

看下图：是不是栈中任何一个满足 $h_k < h_j$，都可以将 $k$ 到栈顶的所有元素作为下凸的那一个部分，然后 $k$ 前面的一个作为 $i = k - 1$ 可以转移到 $j$：

![](https://cdn.luogu.com.cn/upload/image_hosting/qz86ec2w.png)

$$f_{j} = \min(f_{j}, f_{i} + 1)$$

实际上，我们想让 $j$ 离得越远越好，所以可以边弹出边转移，直到 $a_k > a_i$ 的时候停止。

第二种上凸的情况就不说了，就把上面的东西全部反过来就可以了。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Discrete Centrifugal Jumps
| Contest1: Luogu
| URL:     https://www.luogu.com.cn/problem/CF1407D
| When:    2023-10-05 19:39:46
| 
| Memory:  250 MB
| Time:    2000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 300010;

int n, h[N], f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    stack<int> s1, s2;
    f[0] = -1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] + 1;// 跳一步
        while (s1.size() && h[s1.top()] <= h[i]) {	// 第一种情况
            int x = s1.top();
            s1.pop();
            if (s1.size() && min(h[s1.top()], h[i]) > h[x]) f[i] = min(f[i], f[s1.top()] + 1);
        }
        while (s2.size() && h[s2.top()] >= h[i]) {	// 第二种情况
            int x = s2.top();
            s2.pop();
            if (s2.size() && max(h[s2.top()], h[i]) < h[x]) f[i] = min(f[i], f[s2.top()] + 1);
        }
        s1.push(i);
        s2.push(i);
    }
    cout << f[n] << '\n';
    return 0;
}
```

---

## 作者：Kevin_Mamba (赞：2)

题面上的题意挺好，不用多解释。

## 原题解析

考虑 $dp$。设 $dp_i$ 表示跳到楼 $i$ 最少跳的次数。初始化 $dp_1=0$。

条件一很简单，不多解释。

$$dp_i=\min(dp_i,dp_{i-1})$$

条件二和条件三虽然看上去很难，但有异曲同工之妙。

先感性理解（简称图文结合）一下两个条件（仅供参考）。

![](https://cdn.luogu.com.cn/upload/image_hosting/mb05ui0a.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

### 深入分析条件二

以样例一为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/bxsrzx08.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

注记：下面数字为位置编号，上面为高度。

如图，红、蓝两线表示 $2$ 号位置通过条件二的蹦跳。

设跳跃的 $i=2,j_1=4,j_2=3$。

集中注意力，观察，发现:
1. $j_1$ 是 $i$ **右边最近且不低于于** $i$ 的位置。

2. $i$ 是 $j_2$ **左边最近且不低于于** $i$ 的位置。

转移详见代码。

条件三同理。

可能会有人问，这样会不会漏掉？并不会，因为是相互的。自己理解一下吧。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
using namespace std;

const int N=3e5+10;

int n,a[N];

int pos[N],top,dp[N],lmin[N],rmin[N],lmax[N],rmax[N];

int main()
{
    scanf("%d",&n);
    for(re int i=1;i<=n;i++) scanf("%d",&a[i]);

    pos[0]=0;
    // 左边最近小 
    for(re int i=1,top=0;i<=n;i++)
    {
        while(top&&a[i]<a[pos[top]]) top--;
        lmin[i]=pos[top];
        pos[++top]=i; 
    }
    // 左边最近大 
    for(re int i=1,top=0;i<=n;i++)
    {
        while(top&&a[i]>a[pos[top]]) top--;
        lmax[i]=pos[top];
        pos[++top]=i; 
    }

    pos[0]=n+1;
    // 右边最近小 
    for(re int i=n,top=0;i;i--)
    {
        while(top&&a[i]<a[pos[top]]) top--;
        rmin[i]=pos[top];
        pos[++top]=i; 
    }
    // 右边最近大 
    for(re int i=n,top=0;i;i--)
    {
        while(top&&a[i]>a[pos[top]]) top--;
        rmax[i]=pos[top];
        pos[++top]=i; 
    }   

    memset(dp,0x7e7e7e7e,sizeof dp);
    dp[1]=0;
    for(re int i=1;i<=n;i++)
    // 必须从 1 开始，因为要向后转移。
    {
        dp[i]=min(dp[i],dp[i-1]+1);
        dp[i]=min(dp[i],dp[lmin[i]]+1);
        dp[i]=min(dp[i],dp[lmax[i]]+1);
        dp[rmin[i]]=min(dp[rmin[i]],dp[i]+1);
        dp[rmax[i]]=min(dp[rmax[i]],dp[i]+1);       
    }
    printf("%d\n",dp[n]);
    return 0;
}
```



---

## 作者：引领天下 (赞：2)

算法：单调栈+DP。

由于规则 $2,3$ 在本质上是一样的，所以我们对规则 $2$ 进行说明。

设 $f_i$ 为从起点跳到第 $i$ 个大厦需要的最少跳跃次数，维护一个单调递增的单调栈（注意！一定是单调递增而不能是非减！我这个屑就因为这个细节吃了不少罚时），其中存放一个二元组 $(h,i)$，分别表示高度和是第几个大厦。设我们正在处理第 $j$ 个大厦，则对于弹栈过程中的每个元素 $t$，都有 $\max\{a_{t_i+1}\dots a_{j-1}\}=t_h$。于是可以用 $t_i$ 来更新 $f_j$。

规则3同理，只不过换成了维护一个单调递减的单调栈。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[300005],a[300005];
stack<pair<int,int> >mx,mn;
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    memset(f,0x3f,sizeof(f));
    f[1]=0;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    mx.push(make_pair(a[1],1)),mn.push(make_pair(a[1],1));
    for(int i=2;i<=n;i++){
        int last=INT_MAX;
        while(mx.size()&&mx.top().first>=a[i]){//弹栈，更新
            f[i]=min(f[i],f[mx.top().second]+1);
            last=mx.top().first,mx.pop();
        }
        if(mx.size()&&last!=a[i])f[i]=min(f[i],f[mx.top().second]+1);//特别注意！如果弹栈过程中弹出了一个正好=ai的元素，是不可以用他来更新fi的（想一想：为什么？*）
        mx.push(make_pair(a[i],i));//入栈
        last=INT_MAX;
        while(mn.size()&&mn.top().first<=a[i]){
            f[i]=min(f[i],f[mn.top().second]+1);
            last=mn.top().first,mn.pop();
        }
        if(mn.size()&&last!=a[i])f[i]=min(f[i],f[mn.top().second]+1);
        mn.push(make_pair(a[i],i));//同理
    }
    cout<<f[n];
    return 0;
}
```

\*：这里是个坑点，我在这里也吃了罚时。因为当弹出的这个元素正好 $=a_i$ 的时候，规则2的小于号就无法成立。规则3同理。

---

## 作者：onglu (赞：1)

## D. Discrete Centrifugal Jumps
### 题目大意  
一开始站在第$1$栋大楼楼顶，想要到第$n$栋大楼楼顶。  

每次可以向相邻的大楼跳跃，或者说如果中间一整段都比起点和终点都要低或高，就可以直接跳过去。  

形式化的，$i$可以跳到$j$当且仅当满足下面三个条件之一。  
> $i = j - 1$  
> $max(h[i], h[j]) < max(h[k]),(i < k < j)$  
> $min(h[i], h[j]) > min(h[k]),(i < k < j)$  


求$1$到$n$的最小跳跃次数。  
$2 \le n \le 3 \cdot 10^5$  
$1 \le h_i \le 10^9$  

### 思路  
~~考场中降智，连单调栈都写不来了。~~  
考虑直接$dp$，显然$f[i] = min(f[k]\ +\  1)$$(if\ k\ can\ jump\ to\ i)$。  
那么我们考虑优化这个枚举过程。  
用单调栈就可以维护最近的第一个大于或者小于当前的值。  

下面就单调递增的栈来讲解。  
考虑最后一个值和当前值的比较。  
如果小于等于当前值：那么只有最后一个值可以转移，因为再之前的值都会被最后一个值卡住。  
如果大于当前值，那么直到之前第一个小于等于当前值的位置之前都可以作为状态转移。  

维护单调递增单调递减两个栈就可以了。  

时间复杂度是均摊的$O(n)$。  

### 代码  
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 1009;

int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}
int n, a[N], l[N], r[N], t1, t2, f[N];
int main()
{
	n = read(); t1 = t2 = 1; f[1] = 0;
	for(int i = 1; i <= n; i++)a[i] = read();
	l[1] = r[1] = 1;
	for(int i = 2; i <= n; i++){
		f[i] = f[i - 1] + 1;
		if(a[i - 1] < a[i]){
			for(int j = t1; j; j--){
				f[i] = min(f[i], f[l[j]] + 1);
				if(a[l[j]] >= a[i])break;
			}
		}else {
			for(int j = t2; j; j--){
				f[i] = min(f[i], f[r[j]] + 1);
				if(a[r[j]] <= a[i])break;
			}
		}
		while(t1 && a[l[t1]] <= a[i])t1--;l[++t1] = i;
		while(t2 && a[r[t2]] >= a[i])t2--;r[++t2] = i;
	}
	printf("%d\n",f[n]);
	return 0;
}
```

---

## 作者：lory1608 (赞：1)

观察一下原题限制，就发现对于位置 $i$ 我们可以在以下位置转移

- 第一个比他小的位置

- 第一个比他大的位置

- 对左边的一个位置 $x$ ,$i$ 是第一个比他大的位置

- 对左边的一个位置 $x$ ,$i$ 是第一个比他小的位置

然后用**单调队列维护**就行了。

复杂度 $\Theta(n)$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#include<set>
#define IN inline
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
using namespace std;
inline int getint()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=3e5+5;
int n,h[maxn],dp[maxn];
vector<int>v;
vector<int>jump[maxn];
int main()
{
	n=getint();
	FOR(i,1,n)h[i]=getint();
	memset(dp,0x3f,sizeof(dp));
	dp[1]=0;
	FOR(i,1,n)///左边第一个比他大的 
	{
		while(!v.empty()&&h[v.back()]<h[i])v.pop_back();
		if(!v.empty())jump[i].push_back(v.back());
		v.push_back(i);
	}
	v.clear();
	FOR(i,1,n)///左边第一个比他小的 
	{
		while(!v.empty()&&h[v.back()]>h[i])v.pop_back();
		if(!v.empty())jump[i].push_back(v.back());
		v.push_back(i);
	}
	v.clear();
	for(int i=n;i>=1;--i)///右边第一个比他大的 
	{
		while(!v.empty()&&h[v.back()]<h[i])v.pop_back();
		if(!v.empty())jump[v.back()].push_back(i);
		v.push_back(i);
	}
	v.clear();
	for(int i=n;i>=1;--i)///右边第一个比他小的 
	{
		while(!v.empty()&&h[v.back()]>h[i])v.pop_back();
		if(!v.empty())jump[v.back()].push_back(i);
		v.push_back(i);
	}
	FOR(i,2,n)
	{
		FOR(j,0,(int)jump[i].size()-1)
		dp[i]=min(dp[i],dp[jump[i][j]]+1);
	}
	printf("%d\n",dp[n]);
	return 0;
}

```

---

## 作者：big_news (赞：1)

[菜鸡的Div2题解](https://big-news.cn/2020/09/09/%E3%80%8C%E8%A7%A3%E9%A2%98%E6%8A%A5%E5%91%8A%E3%80%8DCodeforces%20Round%20669%20(Div.%202)/)

理性分析一下，边数看上去不是 $O(n^2)$ 的而是 $O(n)$ 的，那么可以线性地把图建出来，单调栈维护一下即可。

但是这个题并不需要最短路算法，注意到这是一个 DAG，因此直接 DP 计算即可，时间复杂度 $O(n)$。
```cpp
n = read(); for(int i = 1; i <= n; i++) a[i] = read();
    
memset(f, 0x3f, sizeof(f)), f[1] = 0;
stk1[++top1] = 1, stk2[++top2] = 1;
for(int i = 2; i <= n; i++){
    while(top1 && a[ stk1[top1] ] < a[i]){
        f[i] = min(f[i], f[ stk1[top1] ]);
        while(top1 && a[ stk1[top1] ] == a[ stk1[top1 - 1] ]) top1--;
        if(top1) top1--;
    }
    if(top1) f[i] = min(f[i], f[ stk1[top1] ]);
    stk1[++top1] = i;

    while(top2 && a[ stk2[top2] ] > a[i]){
        f[i] = min(f[i], f[ stk2[top2] ]);
        while(top2 && a[ stk2[top2] ] == a[ stk2[top2 - 1] ]) top2--;
        if(top2) top2--;
    }
    if(top2) f[i] = min(f[i], f[ stk2[top2] ]);
    stk2[++top2] = i;

    f[i]++;
}

printf("%lld", f[n]);
```

---

## 作者：lyt_awa (赞：1)

## 题意
[**传送门**](https://www.luogu.com.cn/problem/CF1407D)
## 思路
可以看出本题可以用 **dp** 来做。
### 状态
$f_i$ 表示跳到第 $i$ 栋楼所需的最少步数。
### 转移
需要考虑 $i$ 能从那些楼转移过来，题目中有：

>可以从楼 $i$ 跳到 楼 $j$，当 $i$, $j$ ( $i < j$ )满足以下三个条件之一：

>* $i+1=j$

>* $\max(h_{i+1},h_{i+2},\cdots,h_{j-1})<\min(h_i,h_j)$

>* $\min(h_{i+1},h_{i+2},\cdots,h_{j-1})>\max(h_i,h_j)$

可以看出 $i$ 可以从左边第一个大于等于和小于等于它高度的楼 $j1,j2$ 转移过来（因为 $j1$ 是 $i$ 左边第一个高于等于 $i$ 的楼，所以 $i$ 和 $j1$ 之间的楼一定都比它们矮，同理 $i$ 和 $j1$ 之间的楼一定都比它们高）。

$i$ 右边第一个大于等于和小于等于它高度的楼 $j3,j4$ 可以从 $i$ 转移过来（因为 $j3$ 是 $i$ 右边第一个高于等于 $i$ 的楼，所以 $i$ 和 $j3$ 之间的楼一定都比它们矮，同理 $i$ 和 $j4$ 之间的楼一定都比它们高）。

所以可以用**刷表 + 填表**的方法来转移：
```cpp
f[i] = min(min(f[i], f[i - 1]), min(f[L[i][0]], f[L[i][1]]));
++f[i];//跳到i需要一步
f[R[i][0]] = min(f[R[i][0]], f[i]);
f[R[i][1]] = min(f[R[i][1]], f[i]);
```
$L_{i,0}$ 表示左边第一个矮于等于 $i$ 的楼。  
$L_{i,1}$ 表示左边第一个高于等于 $i$ 的楼。  
$R_{i,0}$ 表示右边第一个矮于等于 $i$ 的楼。  
$R_{i,1}$ 表示右边第一个高于等于 $i$ 的楼。  
这些可以用**单调栈** $O(n)$ 预处理出来。

## $code$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int n, h[N], f[N], R[N][2], L[N][2];
int sk[N][2], top0, top1;

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		h[i] = read();
		R[i][0] = R[i][1] = n + 1;
		L[i][0] = L[i][1] = 0;
		while (top0 && h[sk[top0][0]] > h[i]) --top0;
		if (top0) L[i][0] = sk[top0][0];
		sk[++top0][0] = i;
		while (top1 && h[sk[top1][1]] < h[i]) --top1;
		if (top1) L[i][1] = sk[top1][1];
		sk[++top1][1] = i;
	}
	top0 = top1 = 0;
	for (int i = n; i; --i) {
		while (top0 && h[sk[top0][0]] > h[i]) --top0;
		if (top0) R[i][0] = sk[top0][0];
		sk[++top0][0] = i;
		while (top1 && h[sk[top1][1]] < h[i]) --top1;
		if (top1) R[i][1] = sk[top1][1];
		sk[++top1][1] = i;
	}
	memset(f, 0x3f, sizeof(f));
	f[1] = -1;
	for (int i = 1; i <= n; ++i) {
		f[i] = min(min(f[i], f[i - 1]), min(f[L[i][0]], f[L[i][1]]));
		++f[i];
		f[R[i][0]] = min(f[R[i][0]], f[i]);
		f[R[i][1]] = min(f[R[i][1]], f[i]);
	}
	printf("%d\n", f[n]);
	return 0;
}
```
时间复杂度 $O(n)$。

---

## 作者：Y2y7m (赞：0)

可以看出这是一道 dp 题。

容易想出 $n^2$ 的 $dp$ 怎么做，现在想想如何优化转移

考虑第一个条件

* $\max(h_{i+1},h_{i+2},\cdots,h_{j-1})<\min(h_i,h_j)$

发现如果到了最近的一个位置 $p$，$h_i\leq h_p$，那次是位置 $p$ 以前的所有的楼都对 $i$ 没有用了。

再考虑第二个

* $\min(h_{i+1},h_{i+2},\cdots,h_{j-1})>\max(h_i,h_j)$

发现如果到了最近的一个位置 $p$，$h_p\leq h_i$，那次是位置 $p$ 以前的所有的楼都对 $i$ 没有用了。

发现都可以用单调栈维护，每次弹出都进行一次更新，但是需要注意，如果弹栈时出现了和 $h_i$ 相同时就无法更新下一个了，所以要特判。

[submisson](https://codeforces.com/contest/1407/submission/213063113)

---

## 作者：XXXxm (赞：0)


#### [听说博客观赏更加](https://www.luogu.com.cn/blog/shencowbiantai/solution-cf1407d)


**前言**：本题机房里老师拿来比赛，本蒟蒻没时间，浅浅敲了一个低配版**递归搜索**骗部分分(~~过于丑陋~~)，就不展示了。后来同机房一大佬讲解后，豁然开朗。文末会给出他的题解。

下面讲讲该怎么写出正解。

## 思路

首先看到题干，如此明显的暗示，一眼 **DP**，题目都把状态摆到你脸上了：

- $i+1=j$

- $\max(h_{i+1},h_{i+2},\cdots,h_{j-1})<\min(h_i,h_j)$

- $\min(h_{i+1},h_{i+2},\cdots,h_{j-1})>\max(h_i,h_j)$


那我们可以直接敲一个**动态规划**先试试水。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5;
int h[N], f[N], n;
void Min(int &a, int b) {
    if (a > b)
        a = b;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
    memset(f, 0x3f, sizeof(f));
    f[1] = 0;
    for (int i = 1; i < n; ++i) {
        Min(f[i + 1], f[i] + 1);
        int mx = 0, mi = 1e9 + 7;
        for (int j = i + 2; j <= n; ++j) {
            mx = max(mx, h[j - 1]);
            Min(mi, h[j - 1]);
            if (mi > h[i] && mi > h[j] || mx < h[i] && mx < h[j])
                Min(f[j], f[i] + 1);
        }
    }
    printf("%d", f[n]);
    return 0;
}
```

不用想的，肯定会 **TLE** ，只能拿到 _60%_ 的分数 
(当然如果对于没有太多想法的同学用来切分已经 OK 了)。

然后就是怎么维护优化 **dp** 得到正解的事了。

再仔细看看题干

- $i+1=j$

- $\max(h_{i+1},h_{i+2},\cdots,h_{j-1})<\min(h_i,h_j)$

- $\min(h_{i+1},h_{i+2},\cdots,h_{j-1})>\max(h_i,h_j)$

形象点的话就是这样的

![](https://cdn.luogu.com.cn/upload/image_hosting/st0yyka9.png)

也就是说，对于任意的一栋楼 $h_i$ 都可以从它的左边

**第一个** $h_j$($h_j \ge h_i$)

或者

**第一个** $h_j$($h_j \le h_i$)跳过来。

（~~不然就是往前跳到最近的楼上~~）。

~~同理~~对于 $h_i$ 右边的任意一个 $h_k$ ( $h_k \ge h_i \vee h_k \le h_i$ )也可以由左边的 $h_i$ 跳过来。

那么这就是我们的状态转移方程。

对于 **dp** ，选择开两个**单调栈** $st1$ 和 $st2$ 来维护。

```cpp
void init(int i) {
	while(top1 && a[st1[top1]] > a[i]) --top1;
	if(top1) l[i][0] = st1[top1];
	st1[++top1] = i;
	while(top2 && a[st2[top2]] < a[i]) --top2;
	if(top2) l[i][1] = st2[top2];
	st2[++top2] = i;
}
void init1(int i) {
	while (top1 && a[st1[top1]] > a[i]) --top1;
	if (top1) r[i][0] = st1[top1];
	st1[++top1] = i;
	while (top2 && a[st2[top2]] < a[i]) --top2;
	if (top2) r[i][1] = st2[top2];
	st2[++top2] = i;
}
```


------------

以下附上完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int a[N],st[N][2];//用于记录左右第一个大于等于和小于等于它高度的楼的下标
int dp[N];//dp[i] 表示跳到第 i 栋楼所需的最少步数
int st1[N],st2[N];
int l[N][2],r[N][2];//开2维分别记录最高的楼和最低的楼 
int n,top1 = 0,top2 = 0;
void init(int i) {
	while(top1 && a[st1[top1]] > a[i]) --top1;
	if(top1) l[i][0] = st1[top1];
	st1[++top1] = i;
	while(top2 && a[st2[top2]] < a[i]) --top2;
	if(top2) l[i][1] = st2[top2];
	st2[++top2] = i;
}
void init1(int i) {
	while (top1 && a[st1[top1]] > a[i]) --top1;
	if (top1) r[i][0] = st1[top1];
	st1[++top1] = i;
	while (top2 && a[st2[top2]] < a[i]) --top2;
	if (top2) r[i][1] = st2[top2];
	st2[++top2] = i;
}
int main() {
	scanf("%d",&n);

	for(int i = 1; i<=n; i++) {
		scanf("%d",&a[i]);
		r[i][0] = r[i][1] = n + 1;
		l[i][0] = l[i][1] = 0;
	}
	for(int i = 1; i<=n; i++)
		init(i);

	top1 = top2 = 0;//千万不要忘记栈顶为空 

	for(int i = n; i>=1; i--)
		init1(i);

	memset(dp,0x3f,sizeof(dp));//初始化数组好习惯 
	dp[1] = -1;
	for(int i = 1; i<=n; i++) {
		dp[i] = min(min(dp[i],dp[i-1]) , min(dp[l[i][0]] , dp[l[i][1]])),++dp[i];//这里++dp[i]是 表示到i需要一步 
		dp[r[i][0]] = min(dp[r[i][0]] , dp[i]);//从右边第一个大于等于它高度的楼转移过来
		dp[r[i][1]] = min(dp[r[i][1]] , dp[i]);//从右边第一个大小于等于它高度的楼转移过来
	}
	printf("%d",dp[n]);
	return 0;
}

```

#### [大佬](https://www.luogu.com.cn/blog/lx13506678/solution-cf1407d)

祝大家都可以 A 掉这道$\color{blue}{\text{ 蓝题 }}$。

---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF-shua-ti-ji-lu.html)
#### 分析

发现第二个条件就相当于中间的全大于两边的，第三个条件相当于中间的全小于两边的。于是可以维护一个单调递增的单调栈和一个单调递减的单调栈。对于单调递增的单调栈，发现如果栈顶需要弹，那么栈顶到新加入的这位中间的高度一定都大于这位的高度，也一定大于栈顶之下的元素的高度。设 $dp_i$ 表示从 $1$ 跳到 $i$ 的最少次数，那么此时符合条件二， $dp_i$ 就能从栈顶之下的 dp 值转移,即 $dp_i=\min\{dp_{s_top-1}+1\}$。条件三同理。

#### 核心代码

```cpp
qread(n);int i,j;for(i=1;i<=n;i++) qread(a[i]);mem(dp,0x7f);
dp[1]=0;t1=t2=1;s1[1]=s2[1]=1;
for(i=2;i<=n;i++){
    dp[i]=dp[i-1]+1;
    while(t1&&a[i]>=a[s1[t1]]){
        if(a[s1[t1]]!=a[i]) dp[i]=qmin(dp[i],dp[s1[t1-1]]+1);t1--;
    }while(t2&&a[i]<=a[s2[t2]]){
        if(a[s2[t2]]!=a[i]) dp[i]=qmin(dp[i],dp[s2[t2-1]]+1);t2--;
    }s1[++t1]=s2[++t2]=i;
}printf("%d\n",dp[n]);
```

---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Solution]}}$

很容易想到 dp，记 $f_{i}$ 表示从 $1$ 到 $i$ 最少需要几步，显然 $f_{1}=0$。

第一个条件等价于下面一个方程：

$$f_{i}=f_{i-1}+1$$

考虑第 $2$ 个条件怎么办。

因为 $\min(h_{i},h_{j}) \leq h_{i}$，所以当 $\max \{ h_{i+1 \cdots j-1} \}>h_{i}$ 时，第二个条件一定不被满足（注意，为了叙述的方便，在下面的讨论中，我们认为 $j<i$，即从 $j$ 转移到 $i$）。

从 $i$ 往前找，遍历每一个 $h_{j}<h_{i}$ 的点，当出现一个点 $j$ 满足 $\max \{ h_{i+1 \cdots j-1} \}<h_{j}$ 则一定可以从点 $j$ 跳到点 $i$。

如何找出这样的点 $j$ 呢？很简单，我们可以用一个单调栈维护即可。

第 $3$ 个条件同理即可。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=3e5+100;
int h[N],n,ans,f[N];
int s1[N],top1,s2[N],top2;
int main(){
	n=read();ans=n-1;
	for(int i=1;i<=n;i++)
		h[i]=read();
	f[0]=0x3f3f3f3f;f[1]=0;
	s1[top1=1]=s2[top2=1]=1;
	for(int i=2;i<=n;i++){
		f[i]=f[i-1]+1;//init
		while (top1&&h[i]<=h[s1[top1]]){
			if (h[i]!=h[s1[top1]])
				f[i]=min(f[i],f[s1[top1-1]]+1);
			--top1;
		}
		while (top2&&h[i]>=h[s2[top2]]){
			if (h[i]!=h[s2[top2]])
				f[i]=min(f[i],f[s2[top2-1]]+1);
			--top2;
		}
		s1[++top1]=s2[++top2]=i;
	}
	printf("%d",f[n]);
	return 0;
}
```

---

## 作者：极寒神冰 (赞：0)

直接根据题意模拟。

$1$.直接从上一个位置+$1$

$2$从左边第一个比现在这个数大的数位置+$1$

$3$从左边第一个比现在这个数小的位置+$1$

所以直接建两个单调栈，一个维护上升，一个维护下降，当出栈时更新答案即可。

```
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;
#define test puts("QAQ");
//define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int inf=0x7f7f7f7f;
const int N=3e5+10;
int n;
stack<int>upp,dwn;

int a[N];
int dp[N];
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	fill(dp,dp+n+1,inf);
	dp[1]=0;
	upp.push(1);
	dwn.push(1);
	for(int i=2;i<=n;i++)
	{
		dp[i]=min(dp[i],dp[i-1]+1);
		while((!upp.empty())&&a[i]<=a[upp.top()])
		{			
			int x=a[upp.top()];
			upp.pop();
			if(a[i]<x&&!upp.empty()) dp[i]=min(dp[i],dp[upp.top()]+1);
		}
		upp.push(i);
		while((!dwn.empty())&&a[i]>=a[dwn.top()])
		{
			int x=a[dwn.top()];
			dwn.pop();
			if(a[i]>x&&!dwn.empty()) dp[i]=min(dp[i],dp[dwn.top()]+1);
		}
		dwn.push(i);
	}
	cout<<dp[n]<<endl;

}
```



---

