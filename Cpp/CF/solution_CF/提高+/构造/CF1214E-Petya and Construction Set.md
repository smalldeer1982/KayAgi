# Petya and Construction Set

## 题目描述

你需要构造出一个节点数为 $2n$ 的一棵树. 给出 $n$ 个范围在 $[1, n]$ 的正整数 $d_i$ . 你构造出来的树需要满足: 第 $2i - 1$ 个点与第 $2i$ 个点在树上的距离恰为$d_i$.

这里定义两个点 $u$ , $v$ 之间的距离为 $u$ 到 $v$ 路径上的边数.

如果有多种方案, 输出任意一种即可.

## 说明/提示

$1 \leq d_i \leq n \leq 10^5$

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
1 6
2 6
3 5
3 6
4 5
```

## 样例 #2

### 输入

```
4
2 2 2 1
```

### 输出

```
1 6
1 7
2 6
3 5
3 6
4 5
7 8
```

## 样例 #3

### 输入

```
6
2 2 2 2 2 2
```

### 输出

```
1 3
2 3
3 5
4 5
5 7
6 7
7 12
8 12
9 11
9 12
10 11
```

## 样例 #4

### 输入

```
2
1 1
```

### 输出

```
1 2
1 4
3 4
```

# 题解

## 作者：CYJian (赞：8)

打比赛的时候:

md怎么D题数据这么毒硬是过不了...

![](https://cdn.luogu.com.cn/upload/image_hosting/3tldjq3e.png)

D调到 `1:20:××` 后: 算了开E题看看...

1min后: 这不就构造sb题么...

![](https://cdn.luogu.com.cn/upload/image_hosting/w1h23wdd.png)

---

我们注意到题目给出了一个非常~~优美~~的性质: $d_i \leq n$

有啥用呢?

我们考虑把 $2$, $4$, $6$, $\dots$, $2n$ 先拿出来,

然后按照这些点对应的 $d_i$ 从大到小连成一条链.

然后: 考虑$1$, $3$, $5$, $\dots$, $2n-1$ 放在哪里..

然后我们枚举$i$, 然后对于每个 $i \in [1, n]$ 只需要执行下面两步就完了:

- 设链上的第$i$个点是 $a_i$, 那么令 $x=a_{i+d_i-1}$ ,将 $2i-1$ 与 $x$ 连一条边.
- 如果 $x$ 是目前链上的最后一个点, 那么把 $a_i-1$ 放在链尾, 链长度 $+1$ .

正确性? ~~这不是显然的么...~~(如果觉得显然那么下面这段证明就可以忽略了..)

首先, 构造的链上的第 $1$ 个到第 $n$ 个元素的 $d_i$ 都是不升的.

而且第一个元素必定找的到满足距离的点.

考虑后面的第 $i$ 个元素. 如果假定后面的第 $i$ 个元素找不到满足距离条件的点, 且 $1$ 到 $i-1$ 都找到了的话, 那么一定有: $i + d_i - 1 > N_i$ ($N_i$ 为插入第 $i$ 个元素配对的点的时候当前链的长度)

那么对于 $i-1$ , 也一定有: $i-1 + d_{i-1} - 1 \ge i + d_i - 1 > N_i$ , 因为有 $d_{i-1} \ge d_i$

如果$d_{i-1} > d_i$:

那么就有 $i-1 + d_{i-1} - 1 > N_i$

而我们有: $i-1 + d_{i-1} - 1 \leq N_{i-1}$ 和 $N_{i - 1} \leq N_i$

所以就有: $i-1 + d_{i-1} - 1 \leq N_i$

得到矛盾, 所以对于 $d_{i-1} > d_i$ 时不存在这种情况.

如果$d_{i-1} = d_i$:

那么就有: $i + d_{i-1} - 1 > N_i$

并且我们有: $i + d_{i-1} - 1 \leq N_{i-1}+1$ 和 $N_{i - 1} \leq N_i$

所以有: $i + d_{i-1} - 1 \leq N_i+1$

那么结合 $i + d_{i-1} - 1 > N_i$ 我们就得到了: $i - 1 + d_{i-1} - 1 = N_i$

所以就有: $N_i \leq N_{i-1}$ 

结合 $N_{i - 1} \leq N_i$ 就有: $N_{i-1} = N_i$

所以有: $i - 1 + d_{i-1} - 1 = N_{i-1}$

那么我们就知道了, 这种时候第 $i-1$ 个元素的对应的点 $x$ 连上的是链尾. 根据之前设计的算法, 我们在这个时候会将 $x$ 添加至链尾, 同时 $N_i = N_{i-1}+1$, 所以与上面的 $N_i \leq N_{i - 1}$ 矛盾. 于是对于 $d_i=d_{i-1}$不存在这种情况.

所以我们就知道了: 当 $d_i \leq d_{i-1}$ 的时候, 这个算法是正确的.

那么我们做法的正确性就得到了保证.(可能是伪证QwQ)

写起来也很方便:(其实边是可以不用存下来最后输出的...)

```cpp
#include <bits/stdc++.h>
	
using namespace std;
	
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	inline void pc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template <class I>
	inline void gi (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	template <class I>
	inline void print (I x) {
		if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) pc (qu[qr --]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: print;
using io :: pc;
	
#define Space pc(' ')
#define Enter pc('\n')
	
typedef long long ll;
typedef double db;
typedef unsigned int uit;
	
template<typename T> inline void chkmax(T&a, T b) { a = a > b ? a : b; }
template<typename T> inline void chkmin(T&a, T b) { a = a < b ? a : b; }
template<typename T> inline int gcd(T&a, T b) { return !b ? a : gcd(a, b); }
	
const db pi = acos(-1);
const int mod = 19260817;
const int Mod1 = 19491001;
const int Mod2 = 998244353;
const int Mod3 = 1000000007;
const int Mod4 = 1004535809;
const int Mod5 = 104857601;
// 看题目模数, 记得改啊!!!!!!
const int MAXN = 200000;

inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline void Add(int&x, int y) { x = Mod(x + y); }
inline int Mul(int x, int y) { return 1LL * x * y % mod; }

struct Node {
	int x, d;

	friend bool operator < (Node a, Node b) {
		return a.d > b.d;
	}
}a[MAXN + 1];

int id[MAXN + 1];
int num[MAXN + 1];
int nex[MAXN + 1];
vector<int>to[MAXN + 1];

int main() {
	int n; gi(n);
	for(int i = 1; i <= n; i++)
		gi(a[i].d), a[i].x = i;
	sort(a + 1, a + 1 + n);
	for(int i = 1; i < n; i++)
		nex[num[i] = a[i].x << 1] = a[i + 1].x << 1;
	num[n] = a[n].x << 1;
	int N = n, mx = n;
	for(int i = 1; i <= n; i++) {
		if(a[i].d == mx)
			nex[num[N++]] = (a[i].x << 1) - 1, num[N] = (a[i].x << 1) - 1;
		else {
			mx--;
			to[num[i + a[i].d - 1]].push_back((a[i].x << 1) - 1);
		}
	}
	for(int i = 1; i < N; i++)
		print(num[i]), Space, print(nex[num[i]]), Enter;
	for(int i = 1; i <= N; i++) {
		int s = to[num[i]].size();
		for(int j = 0; j < s; j++)
			print(num[i]), Space, print(to[num[i]][j]), Enter;
	}
	return 0;
}
```

---

## 作者：123zbk (赞：2)

构造题。

要使第 $2i-1$ 个点和第 $2i$ 个点的距离为 $d_i$，于是先将每一个奇数按 $d_i$ 从大到小排成一条链，再去配偶数的点。（注意到 $d_i\le n$）

枚举每一个点 $i$，如果 $i+d-1$ 当前有点，那直接和它连一条边。否则，就将链加长一次。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,ans[maxn],cnt;
struct node
{
	int id,d;
	bool operator <(const node &x) const
	{
		return d>x.d;
	}
}a[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].d);
		a[i].id=i;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		ans[++cnt]=a[i].id*2-1;
	}
	for(int i=1;i<n;i++)
	{
		printf("%d %d\n",ans[i],ans[i+1]);
	}
	for(int i=1;i<=n;i++)
	{
		int j=i+a[i].d-1;
		printf("%d %d\n",ans[j],a[i].id*2);
		if(j==cnt)
		{
			ans[++cnt]=a[i].id*2;
		}
	}
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：1)

首先这道题有一个优美的性质，保证 $d_i\le n$，因此把所有奇数号的点排成一条链，用去 $n-1$ 条边，然后把偶数点分别用 $n$ 条边连接在这条链上。

问题就变成了如何排列这 $n$ 个奇数点。

前面说了有一个性质，因此我们考虑把 $d_i$ 最大的先放到一端，考虑数据：
```
3
3 3 2
```
的情况，建好的链如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/yrn43xzn.png)

因为 $1$ 和 $2$ 之间要连接 $3$ 条边，可行的办法就是在 $5$ 后面接入点 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jxchgdve.png)

像这样排列，把最大的排在边上肯定可以满足该点的需求。

继续考虑较小的点，$3$ 和 $4$ 之间也要有 $3$ 条边，在添加 $2$ 号点之后，我们发现 $3$ 到 $2$ 的距离也只有 $2$ 了，因此在 $2$ 后面添加一条边肯定可以满足。

![](https://cdn.luogu.com.cn/upload/image_hosting/jwroani3.png)

再来考虑 $5$ 号点，因为只用经过 $2$ 条边，在 $2$ 号点连接一个 $6$ 号点即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/284kf0ds.png)

如果有剩下的点的话，因为其 $d_i$ 不大于前面的点，因此总是可以转换为上述的两种情况，即在链的尾部添加一个节点，或者在链中某一个节点连出一条边添加这个节点。

由上所述，我们可以得出构造过程：

- 将点对按照其 $d_i$ 从大到小排序；

- 将排序后的点对中奇数的点依次添加到链中，后续需要维护这条链；

- 从前往后枚举点，对于在链上 $p$ 位置的点 $2\times i-1$：

  - 如果链上第 $p+d_i$ 个位置没有点，则将 $2\times i$ 号点放在这个位置，往链上前一个位置连接一条边；
  
  - 如果有点，则直接往前一个位置（即链上 $p+d_i-1$）的点连接一条边。

然后就没有了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int line[1000010];
struct Node
{
    int id, dis;
} a[1000010];
bool cmp1(Node x, Node y)
{
    return x.dis > y.dis;
}
signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].dis;
        a[i].id = i;
    };
    sort(a + 1, a + n + 1, cmp1);
    for (int i = 1; i <= n; i++)
    {
        line[i] = a[i].id * 2 - 1;
        if (i > 1)
            cout << line[i] << ' ' << line[i - 1] << '\n';
    }
    for(int i=1;i<=n;i++)
    {
        if(!line[i+a[i].dis])
        {
            line[i+a[i].dis]=a[i].id*2;
        }
        cout<<a[i].id*2<<' '<<line[i+a[i].dis-1]<<'\n';
    }
}
```

---

## 作者：Hoks (赞：0)

## 前言
sgl duel 到的题，我旁观看了下，感觉还挺有意思的。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
构造题，肯定优先考虑乱搞。

我们肯定要优先考虑去构造 $d_i$ 最大的点对，因为他们之间至少要插入 $d_i-1$ 个点，如果先不构造他们那么后面就没有足够的点可以填充这个空隙。

接着考虑把其他的点对扔进去构造。

但是我们发现这样很容易就出现两个点要在链的同一个位置上，或是链填充不满，更或是填满了链后再开一条新链无法处理。

所以我们考虑正难则反，刚刚我们是考虑先找到一对 $d_i$，然后去填充。

现在我们先构造出一条链，然后去满足 $d_i$。

那么这条链上的点要互不影响，所以我们把 $2$ 的倍数的点全部都扔进去就行了。

但是这时我们会发现有一个问题，如果一个点，他要求的距离是 $n$，但是却被排在了中间，就很难构造了。

所以还是为了方便考虑，我们按从大到小的顺序把每个点连起来组成一条链。

接着对于每个奇数，我们考虑满足 $d_i$。

那么即是找到链上向下的第 $d_i-1$ 个点即可。

注意此处，如果他在接在链底后，要把链扩长一格，避免被一堆 $d_i=n$ 的情况卡掉。
## 代码
实现非常简洁。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,V=1e5,M=310,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,tot,a[N],c[N];pair<int,int>b[N];vector<pair<int,int>>e;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read();for(int i=1;i<=n;i++) b[i]={a[i]=read(),i<<1};sort(b+1,b+1+n);
    for(int i=n;i>=1;i--) c[++tot]=b[i].second;
    for(int i=1;i<n;i++) e.emplace_back(c[i],c[i+1]);
    for(int i=1;i<=n;i++)
    {
        int j=c[i]/2;e.emplace_back(c[i]-1,c[i+a[j]-1]);
        if(i+a[j]-1==tot) c[++tot]=c[i]-1;
    }for(auto [x,y]:e) print(x),put(' '),print(y),put('\n');
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

$\color{orange}\texttt{Difficulty: *2000}$

考虑构造一只毛毛虫树。

维护一条构造的树的直径，初始没有元素。

然后将所有下标为奇数的点按照 $d$ 的值从大到小排序，按照顺序插入树的直径的点集。

然后插入偶数号点。直接找到第 $i\times 2-1$ 个点沿着直径走后面的第 $d_i-1$ 个点然后插一条支边。如果直径变长了，那么就把这条支边扔到直径里。

时间复杂度 $O(n\log n)$。

---

## 作者：operator_ (赞：0)

# Petya and Construction Set

[题目传送门](https://www.luogu.com.cn/problem/CF1214E)

## 题解

一个构造题，结论挺容易猜的。观察到关键信息：$d_i\le n$。所以我们先把所有奇数编号的点按对应的 $d$ 从大到小组成一条链，然后依次考虑偶数号点应该接在链上的哪个点后，容易知道这个点为链上的第 $i+d-1$ 个。特殊的，如果接在了最后一个点后面，我们就更新链的长度。

我可以告诉你，这是对的，证明如下（感觉比另一篇的证明简单些）：

我们用归纳法。

+ 第一个点一定能找到对应的位置，这是因为 $d_i\le n$。

+ 假设第 $i-1$ 个点找到了对应位置，那么第 $i$ 个点也可以找到对应位置，这是因为第 $i-1$ 个点找到了对应位置就意味着从第 $i-1$ 个点往后，至少存在 $d_{i-1}$ 个点，而 $d_i\le d_{i-1}$，所以我们要找 $i$ 后第 $d_i-1$ 个点一定存在。

+ 可推广至 $n$。

代码已经短到一种境界了：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
	int s=0,m=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
	while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return m?-s:s;
}
int n,l[200005],cnt;
struct QWQ {int id,d;} a[200005];
bool cmp(QWQ a1,QWQ a2) {return a1.d>a2.d;}
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++)
		a[i]={i,rd()};
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		l[++cnt]=a[i].id*2-1;
	for(int i=1;i<n;i++)
		printf("%lld %lld\n",l[i],l[i+1]);
	for(int i=1;i<=n;i++) {
		int j=i+a[i].d-1;
		printf("%lld %lld\n",l[j],a[i].id*2);
		if(j==cnt) 
			l[++cnt]=a[i].id*2;
	}
	return 0;
}

```

---

