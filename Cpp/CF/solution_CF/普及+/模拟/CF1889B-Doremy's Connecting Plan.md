# Doremy's Connecting Plan

## 题目描述

Doremy lives in a country consisting of $ n $ cities numbered from $ 1 $ to $ n $ , with $ a_i $ people living in the $ i $ -th city. It can be modeled as an undirected graph with $ n $ nodes.

Initially, there are no edges in the graph. Now Doremy wants to make the graph connected.

To do this, she can add an edge between $ i $ and $ j $ if

 $ $$$ \sum_{k \in S} a_k \ge i\cdot j \cdot c,  $ $ </p><p>where  $ S $  is the set of all the nodes that are currently in the same connected component of either  $ i $  or  $ j $ , and  $ c $  is a given constant.</p><p>Can Doremy make the graph connected?</p><p>Two nodes  $ (i, j) $  are in the same connected component if there exists a path from  $ i $  to  $ j$$$. A graph is connected if all its nodes are in the same connected component.

## 说明/提示

In the first test case, Doremy can add edges in the following order:

1. Add $ (1,2) $ . This operation is valid because $ a_1 + a_2 = 20 \ge i\cdot j \cdot c = 20 $ .
2. Add $ (1,3) $ . This operation is valid because $ a_1 + a_2 + a_3 = 35 \ge i \cdot j \cdot c = 30 $ .
3. Add $ (1,4) $ . This operation is valid because $ a_1 + a_2 + a_3 + a_4 = 45 \ge i \cdot j \cdot c = 40 $ .

In the second test case, Doremy can add edge $ (1,2) $ because $ a_1 + a_2 =2 \ge 1 \cdot 2 \cdot 1 $ . After that, the graph is connected.

In the third test case, Doremy can add edges in the order $ (5,4) $ , $ (5,3) $ , $ (5,2) $ and $ (5,1) $ .

In the fourth test case, Doremy cannot add any edge at all.

## 样例 #1

### 输入

```
7
4 10
0 20 15 10
2 1
1 1
5 1
0 1 0 4 199
5 2
1 1 3 1 1
5 5
5 6 1 10 2
5 1000000
1000000000000 1000000000000 1000000000000 1000000000000 1000000000000
3 1
0 0 2```

### 输出

```
Yes
Yes
Yes
No
No
Yes
No```

# 题解

## 作者：Cocoly1990 (赞：9)

出题人题解。

~~这似乎是一道个人差比较大的题目，栗子哥好像寄在这题了~~。

首先不难发现 $c$ 是毫无用处的（事实上也只是为了造数据更有强度）。

**结论**：若有解，则一定可以构造一种策略，使得最终形态是以 $1$ 为根的菊花。

**证明**：考虑一对 $(i,j)$ 满足 $i>j>1$，若 $i,j$ 可以连边，那么则有 $S_i+S_j\geq i\times j$，又因为 $i\times j\geq i+j$，因此有 $S_i+S_j\geq i+j$，那么至少有 $S_i\geq i$ 或者 $S_j\geq j$，因此必然可以以此连 $(1,i)$，$(1,j)$。

考虑接下来怎么维护，一种做法是按 $i-a_i$ 排序，从小到大贪心的连边。其中 $i-a_i$ 的含义是我想要和 $1$ 连上，$1$ 所在连通块的权值和最小是 $i-a_i$，注意到 $a_i\geq 0$，因此我们只要能和 $1$ 连就尽可能地连上，所以贪心是正确的。

综合时间复杂度 $\mathcal{O}(n\log n)$。

事实上，本题还存在线性做法，注意到如果 $(1,i)$ 能连上，那么此时对于任意的 $j<i$，$(1,j)$ 都能被连上，直接扫描即可线性。


---

## 作者：bmatrix (赞：5)

[题面](https://www.luogu.com.cn/problem/CF1889B)

> 给一个 $n$ 个点的图，每个点 $i$ 有点权 $a_i$，初始图上没有边，你可以进行如下操作若干次：
>
> - 若 $S_i+S_j\ge i\times j\times c$，添加一条边 $(i, j)$。其中 $S_i$ 表示 $i$ 所在连通块的点权和，$c$ 是一个给定的常数。
>
> 问最终能否使图联通。

首先我们有一个简单的 $O(n^3)$ 做法：暴力 $O(n^2)$ 寻找能连的边，如果能连 $n-1$ 次就 `yes`，否则 `no`。

考虑优化连边过程。我们发现，合并两个连通块时，我们一定要选连通块中编号最小的点连边，因为这样在 $S_i+S_j$ 不改变时使 $i\times j\times c$ 最小，能连边的可能性最大。因此下文提到 $i,j$ 都默认它们是连通块中编号最小的点。

这时注意到一个特殊的连通块：$1$ 号点所在的连通块。这个连通块的最小编号是不变的。在手玩半天样例并猜错结论 WA 了一发后，我猜想了这样一个结论：如果 $i$ 和 $j$ 能连边，那么 $1$ 和 $i$，$1$ 和 $j$ 至少有一组能连边。

更加形式化地：若 $S_i+S_j\ge i\times j\times c$，则 $S_1+S_i\ge i\times c$ 和 $S_1+S_j\ge j\times c$ 至少有一个成立。

于是按 $i\times c-a_i$ 由小到大排序再逐个连边就过了。

结论证明（参考了官方题解）：
$$
\begin{aligned}
&S_i+S_j\ge i\times j\times c\\
\iff&\frac{S_i+S_j}c\ge i\times j=(i-1)(j-1)+i+j-1\\
\implies&\frac{S_i+S_j}c\ge i+j-1\quad(*)
\end{aligned}
$$
不妨令 $S_1=0$，于是我们要证明 $\frac{S_i}c\ge i$ 或 $\frac{S_j}c\ge j$。根据 $(*)$ 式使用反证法易证。

代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
#define int ll
#define gmin(x, y) (x = min(x, y))
#define gmax(x, y) (x = max(x, y))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double f128;
typedef pair<int, int> pii;
void solve() {
    int n, c; 
    cin >> n >> c;
    vector<pii> a(n + 5);
    rep(i, 1, n) cin >> a[i].F, a[i].S = i;
    sort(a.begin() + 2, a.begin() + n + 1, [&](pii a, pii b) {
        return a.F - a.S * c > b.F - b.S * c;
    });
    int s = a[1].F;
    rep(i, 2, n) {
        // cerr << a[i].F << ' ' << a[i].S << endl;
        if(a[i].S * c <= s + a[i].F) s += a[i].F;
        else { cout << "No\n"; return; }
    }
    cout << "Yes\n";
}
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    int t; cin >> t;
    while(t--) solve();
    return 0;
}
```



---

## 作者：henrytb (赞：5)

容易发现，假如两个点 $i$ 和 $j$ 能连边，那么它们一定存在一个点能和 $1$ 连边。

证明：假设它们都不能和 $1$ 连边，那么

$$
\begin{aligned}
a_i + a_j &\ge i \cdot j\cdot c \\
a_i + a_1 & < i \cdot c \\
a_j + a_1 & < j \cdot c
\end{aligned}
$$

后两行相加与第一行比较，又由于 $a_1 \ge 0$，得出

$$
(i + j) \cdot c > i\cdot j \cdot c
$$

即

$$
i + j > ij
$$

而这显然对于 $> 1$ 的 $i, j$ 是错误的。因此一定存在一个点能和 $1$ 连边。

那么只需要考虑和 $1$ 连边的情况了，我们用堆维护每个点的 $a_i - i \cdot c$ 值即可。

---

## 作者：Dregen_Yor (赞：3)

# 题意

有一张有 $n$ 个点的图，初始时图中任意两个点直接都没有边相连。

给定正整数 $c$，你可以进行若干次如下操作：

每次选取两个点 $i,j$ 若 $\sum\limits_{k\in S}a_k\ge i\times j\times c$，则可以在点 $i$ 与点 $j$ 之间连一条边。其中 $S$ 表示与 $i$ 和 $j$ 联通的点的集合。

最后能不能通过若干次该操作使图联通。

# 思路

根据贪心的思想，我们考虑每次连接两个不连通的快时，在每个块中编号最小的点之间连边。直到最后所有点都联通为止。

我们考虑从 $1$ 号点出发，将所有的点都连向 $1$ 号边，对于每个点 $i$(除了 $1$ 号点），根据  $i\times c-a_i$ 的大小从小到大进行排序，然后根据排序的结果一次和 $1$ 号点连边即可。

# 证明

有没有可能从 $1$ 号点开始向其他点连边无解但从其他点中选取两个点连边有解呢？

我们设一种极端情况，设 $a_1=1$，存在另外两个点 $k$ 和 $k+1$，其中 $a_k= k\times c-2$，$a_{k+1}=(k+1)\times c -2$。（选取两个相邻的点是为了让他们的乘积尽可能的小）。显然 $a_1$ 无法与 $a_k$ 和 $a_{k+1}$ 直接连边。

但此时，$k\times(k+1)\times c$ 与 $a_k+a_{k+1}$ 相减，可得 $ k^2-k+4$。根据初中二次函数的知识可以知道这个方程在 $k\ge1$ 的时候是恒大于 $0$ 的。由此可得，若某两个点不能与 $1$ 号点相连，那么这两个点之间也无法相互连接。

正确性得证。

# 代码

```cpp
#include<bits/stdc++.h>
#define N 200010
#define int long long
//#define P pair<int,int>
using namespace std;
int T=1,n,c,a[N],siz[N],f[N];
struct node{
    int id,val;
}p[N];
bool cmp(node a,node b){
    return a.id*c-a.val<b.id*c-b.val;
}
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&c);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            f[i]=i;
            siz[i]=1;
            p[i-1]=node{i,a[i]};
        }
        sort(p+1,p+n,cmp);
        bool f=1;
        int sum=a[1];
        for(int i=1;i<n;i++){
            sum+=p[i].val;
            if(sum<p[i].id*c){
                f=0;
                break;
            }
        }
        if(f){
            puts("Yes");
        }
        else{
            puts("No");
        }
    }
    return 0;
}
```


---

## 作者：DerrickLo (赞：2)

很容易想到，每个点都连 $1$ 是最优的。

设目前与 $1$ 联通的所有点点权总和为 $sum$，那么如果要要连 $j$ 则需要满足

$$sum+a_j\ge j\times c$$

移项得到

$$sum\ge j\times c-a_j$$

那么我们将每个非 $1$ 的点 $i$ 按照 $i\times c-a_i$ 从小到大排序，然后按顺序添加点，就能判断可不可行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,c,a[200005];
struct nd{
	int id,x;
	friend bool operator<(const nd&a,const nd&b){
		return a.x<b.x;
	} 
}b[200005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>c;
		for(int i=1;i<=n;i++)cin>>a[i],b[i].x=i*c-a[i],b[i].id=i;
		sort(b+2,b+n+1);
		int flag=1,sum=a[1];
		for(int i=2;i<=n;i++){
			if(sum>=b[i].x){
				sum+=a[b[i].id];
			}
			else{
				flag=0;
				break;
			}
		}
		if(flag)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：_Ink (赞：1)

## 题意

给你一个有 $n$ 个点的图，每个点带有点权，第 $i$ 个点的点权为 $a_i$。

最开始图中没有边，若有两个点 $(i, j)$ 满足：

$$
\sum_{k \in S} a_k \ge i\cdot j \cdot c,
$$

你就可以将两个点连接起来。其中 $S$ 是与 $i$ 和 $j$ 相连通的点的集合，$c$ 是一个给定的常数。

请问你能否使整张图连通。

## 题解

个人觉得这题很有趣，所以浅写一篇题解。

图中最开始没有边。显然，我们加边要从零条边慢慢开始加，于是我们就会试图去寻找加边的最优解，这就符合了贪心的思想。

也许你在贪心的思想发现了，这题有一个很精妙的结论：**图中无边时，如果 $(i,j)$ 可以连接，那么 $(1,i)$ 与 $(1,j)$ 必能连接其一（其中 $i,j \ne1$）。**

我们可以用反证法来证明：

如果对于任何的 $2\le k\le n$， $(1,k)$ 都不能连接，那么便有：  

$a_k < k \cdot c.$  
$a_i + a_j < (i + j) \cdot c < i \cdot j \cdot c$
，其中，$2 \le i, j \le n, ~i \ne j$。

即，在这种情况下，不存在 $(i,j)$ 可以互相连接。

所以，如果 $(i,j)$ 能够互相连接，那么 $(1,i)$ 与 $(1,j)$ 便必能连接其一。命题得证。

显然的是，因为连接所需的限制与点的编号大小有关，所以我们用 $1$ 号点去连接其他点一定是更优的。结合上面我们得到的结论，我们只需要用 $1$ 号点去连接其他的点就可以了。

于是我们就可以把除了 $1$ 以外的点进行排序，把“更加可能与 $1$ 连接得上的点”排在前面，然后按照次序判断是否能与 $1$ 连接。

如何具体地描述“更加可能与 $1$ 连接得上的点”呢？我们可以记与 $1$ 连通的点的点权和为 $sum$，由于点 $i$ 与点 $1$ 连接得上的限制是：$sum + a_i \ge i \cdot c$，所以只有当 $sum \ge i \times c - a_i$ 时才能连接上。

故我们可以预处理出每个点的 $i \times c - a_i$ 值，然后对这个值进行由小到大的排序。这样就把最可能连接的点放在了前面。

按顺序依次判断是否能连接即可。如果所有的都能连接，答案显然是 `Yes`。否则就是 `No`。

## $\text{Code:}$

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define maxn 200050
#define maxm 500050 
#define endl '\n'
#define ll long long
using namespace std;

long long a[maxn];
struct City
{
	ll a, w;
	int rk;
	bool operator < (const City &A) const
	{
		return w > A.w;
	} 
} ct[maxn];

void run()
{
	int n, c; cin >> n >> c;
	for(int i = 1; i <= n; i ++)
	{
		cin >> ct[i].a;
		ct[i].w = ct[i].a - 1ll * i * c;
		ct[i].rk = i;
	}
	sort(ct + 2, ct + 1 + n);
	long long sum = ct[1].a;
	for(int i = 2; i <= n; i ++)
	{
		if(sum + ct[i].a >= 1ll * ct[i].rk * c) sum += ct[i].a;
		else
		{
			cout << "No\n";
			return;
		}
	}
	cout << "Yes\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int t = 1;
	cin >> t; 
	while(t --) run();
	
	return 0;
}

```

---

## 作者：LiJoQiao (赞：0)

[原题链接](https://codeforces.com/contest/1889/problem/B) [洛谷题面](https://www.luogu.com.cn/problem/CF1889B)  
### 题目简述  
有共 $n$ 个节点的无向图，起初这个图没有边，每个点都有点权 $a_i$，你可以对两个节点连边等且仅当满足此式。  
$$\sum_{k \in S}a_k \ge i \cdot j\cdot c$$  
其中 $S$ 为连接后形成的连通块，$i$，$j$，为连边的节点编号，$c$ 是一个给定的常数。  
求是否能通过连边使图连通。  
### 题目分析  
先给出一个结论：  
如果图可连通，则存在一种方案使得每条边都与节点 $1$ 相连。  

证明：假设该结论不成立，存在节点 $i$ 与节点 $j$ 连边。  
设节点 $x$ 所在的连通块为 $S_x$。  
所以 $\sum\limits_{k \in S_i}a\left[k\right]+\sum\limits_{k \in S_j}a\left[k\right] \ge i\cdot j \cdot c$。  
又因为 $i,j \ge 2$，  
所以 $\sum\limits_{k \in S_i}a\left[k\right] \ge i \cdot c$ 或 $\sum\limits_{k \in S_j}a\left[k\right]\ge j \cdot c$。  
即有一点可以与 $1$ 相连。  
连接后 $\sum\limits_{k \in S_1}a\left[k\right]$ 大于等于未连接时的两个连通块，所以可以与另一个点相连。  
推出的情况与上述假设矛盾，所以该结论正确。  

推出这个结论后，我们只需要判断每点与 $1$ 能否连接即可。  
节点 $i$ 能与 $1$ 连接当且仅当 $\sum\limits_{k \in S_1}+\sum\limits_{k \in S_i}\ge 1\cdot i\cdot c$。  
由于未连 $1$ 点时 $i$ 没有边，所以可以把 $\sum\limits_{k \in S_i}$ 看做 $a_i$。  
移项得 $\sum\limits_{k \in S_1}\ge i\cdot c -a_i$。  
我们把 $i \cdot c -a_i$ 记做 $g_i$。  
将 $g_i$ 排序，每次查找最大的 $g_i \le \sum\limits_{k \in S_1}$，然后更新 $\sum\limits_{k \in S_1}$，更新不动的时候判断是否连通即为本题答案。  

显然时间复杂度 $O(n \log n)$。

代码如下。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2e5+10;
int n;
ll c,a[MAXN],sum[MAXN];
struct node{
    ll g;int id;
}g[MAXN];
bool cmp(node a,node b){
    return a.g<b.g;
}
ll read(){
    ll f=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return f*x;
}
int main(){
    int t=read();
    while(t){
        --t;
        n=read();c=read();
        for(int i=1;i<=n;++i){
            a[i]=read();
            g[i].id=i;
            g[i].g=c*i-a[i];
        }
        sort(g+1,g+1+n,cmp);
        sum[0]=a[1];
        for(int i=1;i<=n;++i){
            if(g[i].id==1)sum[i]=sum[i-1];
            else sum[i]=sum[i-1]+a[g[i].id];
        }
        int lp=0;
        while(1){
            int l=1,r=n;
            while(l<r){
                int mid=(l+r+1)>>1;
                if(g[mid].g<=sum[lp]){
                    l=mid;
                }
                else r=mid-1;
            }
            if(g[l].g>sum[lp])break;
            if(r<=lp)break;
            lp=r;
        }
        if(lp==n)puts("Yes");
        else puts("No");
    }
    return 0;
}
```

---

