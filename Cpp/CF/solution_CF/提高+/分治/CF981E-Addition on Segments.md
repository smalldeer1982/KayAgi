# Addition on Segments

## 题目描述

Grisha come to a contest and faced the following problem.

You are given an array of size $ n $ , initially consisting of zeros. The elements of the array are enumerated from $ 1 $ to $ n $ . You perform $ q $ operations on the array. The $ i $ -th operation is described with three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ) and means that you should add $ x_i $ to each of the elements with indices $ l_i, l_i + 1, \ldots, r_i $ . After all operations you should find the maximum in the array.

Grisha is clever, so he solved the problem quickly.

However something went wrong inside his head and now he thinks of the following question: "consider we applied some subset of the operations to the array. What are the possible values of the maximum in the array?"

Help Grisha, find all integers $ y $ between $ 1 $ and $ n $ such that if you apply some subset (possibly empty) of the operations, then the maximum in the array becomes equal to $ y $ .

## 说明/提示

Consider the first example. If you consider the subset only of the first query, the maximum is equal to $ 1 $ . If you take only the second query, the maximum equals to $ 2 $ . If you take the first two queries, the maximum becomes $ 3 $ . If you take only the fourth query, the maximum becomes $ 4 $ . If you take the fourth query and something more, the maximum becomes greater that $ n $ , so you shouldn't print it.

In the second example you can take the first query to obtain $ 1 $ . You can take only the second query to obtain $ 2 $ . You can take all queries to obtain $ 3 $ .

In the third example you can obtain the following maximums:

- You can achieve the maximim of $ 2 $ by using queries: $ (1) $ .
- You can achieve the maximim of $ 3 $ by using queries: $ (2) $ .
- You can achieve the maximim of $ 5 $ by using queries: $ (1, 2) $ .
- You can achieve the maximim of $ 6 $ by using queries: $ (3) $ .
- You can achieve the maximim of $ 8 $ by using queries: $ (1, 3) $ .
- You can achieve the maximim of $ 9 $ by using queries: $ (2, 3) $ .

## 样例 #1

### 输入

```
4 3
1 3 1
2 4 2
3 4 4
```

### 输出

```
4
1 2 3 4 
```

## 样例 #2

### 输入

```
7 2
1 5 1
3 7 2
```

### 输出

```
3
1 2 3 
```

## 样例 #3

### 输入

```
10 3
1 1 2
1 1 3
1 1 6
```

### 输出

```
6
2 3 5 6 8 9 
```

# 题解

## 作者：zhaoyp (赞：17)

# Solution

首先如果没有区间的限制，那么这题就是一个裸的 $01$ 背包，可以在 $O(n^2)$ 的时间内 $\text{DP}$ 出来。考虑如何将其推广到一段段区间上。

首先转化一下定义，设 $f_{i,j}$ 表示选到区间 $i$，序列的最大值为 $j$ 时，最左边一个值可以为 $j$ 的位置。

先将所有的区间按照右端点升序排序，从后往前扫，做一个类似 $01$ 背包的转移。

假设当前枚举到区间 $i$，最大值为 $j$，初始时 $f_{i,j} = f_{i + 1,j}$，当且仅当 $f_{i+1,j - x_{i}} \le r_{i}$ 时，$f_{i,j}$ 可以由 $f_{i+1,j - x_{i}}$ 转移来：$f_{i,j} = \min\{f_{i,j},\max\{f_{i+1,j - x_{i}},l_{i}\}\}$。

解释下上式的含义：
- 如果 $r_{i}$ 以左的所有位置都无法被原先的最大值 $j - x_{i}$ 取到，显然无法转移，这也解释了为什么状态要设计成是最左边一个位置。
- 如果 $f_{i+1,j - x_{i}} \geq l_{i}$，则 $f_{i,j}$ 的值显然为 $f_{i+1,j - x_{i}}$。
- 如果 $f_{i+1,j - x_{i}} < l_{i}$，由于我们已经按右端点升序排序，从后往前扫，所以区间 $i$ 是被之前取到 $j - x_{i}$ 的区间包含，则整个 $[l_i,r_i]$ 范围内都可以取到 $j$，最左边的位置为 $l_i$。

最后如果 $f_{1,j} \le n$，则 $j$ 是一个可行的解。

发现 $f_i$ 仅由 $f_{i+1}$ 转移来，可以用滚动数组优化空间。

初值 $f_j = \inf$，$f_0 = 1$。

时间复杂度 $O(n^2)$，空间复杂度 $O(n)$，$n \le 10^4$ 跑的很稳，~~还可以冲最优解~~。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
int n,m,ans[maxn],tot,f[maxn];
struct node
{
	int l,r,x;
}a[maxn];
bool cmp(node a,node b){return a.l < b.l;}
void input()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++)
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].x);
}
void DP()
{
	memset(f,0x3f,sizeof(f));
	f[0] = 1;
	for(int i = m;i;i--)
		for(int j = n;j >= a[i].x;j--)
			if(f[j - a[i].x] <= a[i].r)
				f[j] = min(f[j],max(f[j - a[i].x],a[i].l));
}
void output()
{
	for(int i = 1;i <= n;i++)
		if(f[i] <= n)
			ans[++tot] = i;
	printf("%d\n",tot);
	for(int i = 1;i <= tot;i++)
		printf("%d ",ans[i]);
}
int main()
{
	input();
	sort(a + 1,a + 1 + m,cmp);
	DP();
	output();
	return 0 ;
}
```

---

## 作者：一扶苏一 (赞：9)

## 【线段树分治】【CF981E】Addition on Segments

### Description

- 给定一个长度为 $n$ 的序列，和 $q$ 条操作。
- 序列初始为全 $0$。$q$ 条操作都形如 $l, r, x$，意为给序列 $[l, r]$ 区间内的每个数加上 $x$。
- 对于 $1 \leq k \leq n$，求有多少个 $k$ 满足从 $q$ 条操作中选出若干条操作后序列的最大值为 $k$。（对于一个 $k$，一条操作最多进行一次）。
- $1 \leq n,  q \leq 10^4$。

### Solution

这个问法和这个数据范围看起来就很 bitset，仔细想想果然是 bitset（（

对序列的每个位置依次考虑，对于一个位置，只要保证选出的操作对应的区间都包含这个位置，那么这个位置一定可以作为操作后的序列最大值。

考虑对于一个位置，我们可以用 bitset 轻松维护出进行一系列包含该位置的操作后所有可能得到的值。具体的，设 $f$ 为一个保存了该位置可能得到的值的 bitset，若一次操作为区间加 $x$，则

$$f |= f << x$$

初值为 $f_0 = \text{true}$。

但是注意到由于是取或，在从一个位置进行到下一个位置时，对于只包含原位置而不包含新位置的修改造成的影响无法撤销。

考虑进行线段树分治，将每个修改操作打到线段树的对应节点上，最后遍历这颗线段树，在每个节点维护进行该节点到根路径上的所有操作后可以得到的值，在叶节点统计答案即可。

时间复杂度：打修改操作的复杂度是 $O(q \log n)$，遍历线段树是 $O(n)$ 的，遍历过程中会有 $O(q \log n)$ 次对长度为 $O(n)$ 的 bitset 取或的操作，因此总复杂度 $O(\frac{nq\log n}{w})$。

### Code

```cpp
const int maxn = 10001;

int n, q, bcnt, acnt;
std::bitset<maxn> bt[maxn << 1], ans;
int pans[maxn];


struct OP {
  int l, r, x;

  inline void init() {
    qr(l); qr(r); qr(x);
  }
};
OP op[maxn];

struct Node {
  int l, r, ld, rd, id;
  std::vector<int> opid;
};
Node tree[maxn << 1];

void build(int &o, const int l, const int r);
void insert(const int o, const int id);
void calc(const int o);

int main() {
  freopen("1.in", "r", stdin);
  qr(n); qr(q);
  bt[0].set(0);
  build(bcnt, 1, n);
  for (int i = 1; i <= q; ++i) {
    op[i].init();
    insert(0, i);
  }
  calc(0);
  for (int i = 1; i <= n; ++i) if (ans.test(i)) {
    pans[++acnt] = i;
  }
  qw(acnt, '\n');
  qwa(pans, acnt, ' ', '\n');
  return 0;
}

void build(int &o, const int l, const int r) {
  auto u = tree + o;
  u->l = l; u->r = r; u->id = o;
  if (l != r) {
    int m = (l + r) >> 1;
    u->ld = ++o;
    build(o, l, m);
    u->rd = ++o;
    build(o, m + 1, r);
  }
}

void insert(const int o, const int id) {
  auto u = tree + o;
  if ((u->l >= op[id].l) && (u->r <= op[id].r)) {
    u->opid.push_back(id);
  } else if (!((u->l > op[id].r) || (u->r < op[id].l))) {
    insert(u->ld, id);
    insert(u->rd, id);
  }
}

void calc(const int o) {
  auto u = tree + o;
  for (auto p : u->opid) {
    bt[o] |= bt[o] << op[p].x;
  }
  if (u->ld) {
    bt[u->rd] = bt[u->ld] = bt[o];
    calc(u->ld); calc(u->rd);
  } else {
    ans |= bt[o];
  }
}
```

---

## 作者：万弘 (赞：8)

为了避免格式出问题，请去[My blog](https://oierwanhong.cc/2020/04/06/%E6%B5%85%E8%B0%88%E7%BA%BF%E6%AE%B5%E6%A0%91%E5%88%86%E6%B2%BB/)查看
## CF 981E

题意:

给一个长度为$n$ 的序列(初始全为0)和$q$条操作(以$(l,r,x)$表示将$[l,r]$中的每个数都加上$x$.  
对于$1\le k\le n$,求哪些$k$满足选出若干条操作后序列最大值为$k$.(对于一个$k$,每条操作至多用一次)

$1\le n,q\le 10^4$

<!--more> 

解:首先,可行的$k$集合等于每个位置可达的值的集合 的并集.故求出每个位置可达的值集合即可.  
对于每个位置$i$维护一个`bitset`,记为`s`,设现在考虑的$(l,r,x)$满足$l\le i\le r$,那么$(l,r,x)$对`s`的贡献就是:`s|=(s<<x)`

于是暴力做法就显然了:对于$[l,r]$中的每个元素,都做一次`s|=(s<<x)`即可.时间复杂度上界$\mathcal O(nq\times \frac{n}{w})$,显然不行.  

接下来就是套路:用线段树分治,把$(l,r,x)$的影响打到线段树的$\mathcal O(\log n)$个节点上.(注意节点上用`vector`维护增加的值即可,不用维护`bitset`徒增时间复杂度)最后从根dfs一下,把信息下推至叶子节点即可.叶子节点的`bitset or`起来的结果就是答案.  

时间复杂度$\mathcal O(q\log n+\frac{n^2}{w})$

```cpp
/**********/
#define MAXN 10011
ll n,q;
std::bitset<MAXN>ans;
struct Segment_Tree
{
    std::vector<ll>t[MAXN<<2|1];
    #define rt t[num]
    #define tl t[num<<1]
    #define tr t[num<<1|1]
    void modify(un ql,un qr,ll k,un l=1,un r=n,un num=1)
    {
        if(ql<=l&&r<=qr)
        {
            rt.push_back(k);return;
        }
        un mid=(l+r)>>1;
        if(ql<=mid)modify(ql,qr,k,l,mid,num<<1);
        if(qr>mid)modify(ql,qr,k,mid+1,r,num<<1|1);
    }
    void dfs(std::bitset<MAXN>pre,un l=1,un r=n,un num=1)
    {
        std::bitset<MAXN>cur=pre;
        for(auto x:rt)cur|=(cur<<x);
        un mid=(l+r)>>1;
        if(l==r){ans|=cur;return;}
        dfs(cur,l,mid,num<<1),dfs(cur,mid+1,r,num<<1|1);
    }
}sgt;
std::bitset<MAXN>s;
int main()
{
    n=read(),q=read();
    while(q--)
    {
        ll l=read(),r=read(),k=read();
        sgt.modify(l,r,k);
    }
    s[0]=1;
    sgt.dfs(s);
    ll cnt=0;
    for(ll i=1;i<=n;++i)
        if(ans[i])++cnt;
    printf("%lld\n",cnt);
    for(ll i=1;i<=n;++i)
        if(ans[i])printf("%lld ",i);
    return 0;
}
```





---

## 作者：_edge_ (赞：4)

updata：感谢评论区内的 hack，CF 数据较水所以没发现。

已经通过的题解，麻烦管理员再审核一下，感谢。

注：在 CF 上 $n^2$ 过 $10^4$ 是可行的。

我们发现如果没有区间限制就是一个朴素的背包。

考虑直接进行暴力 DP，$f_i$ 表示当前拼出 $i$ 这个数所能到达最小的左端点。

贪心的想一想，我们需要就是最小的左端点，这可以使得更多的区间和他拼一块。

当然我们要按左端点排序，以及倒着扫，否则就要记录最大的右端点。

判断两个区间是否有交，就是 $l_i \le r_j$ 并且 $l_j \le l_i$，第二个条件完全可以用排序来做到。

然后就是非常普通的 DP，不用任何数据结构！！

当然需要滚动数组进行优化。

更具体的来说。

先对于左端点排序，然后 DP 的时候从后往前枚举，做一个背包，注意这边判一下区间是否有交。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int INF=1e4+5;
int n,q,f[INF],ans,ans1[INF];
struct _node_data{
	int l,r,x;
}a[INF];
bool cmp(_node_data xx,_node_data yy) {
	return xx.l<yy.l;
}
signed main()
{
	memset(f,63,sizeof f);
	scanf("%d %d",&n,&q);
	for (int i=1;i<=q;i++) {
		scanf("%d %d %d",&a[i].l,&a[i].r,&a[i].x);
	}
	f[0]=1;
	sort(a+1,a+1+q,cmp);
	for (int i=q;i>=1;i--) {
		for (int j=n;j>=a[i].x;j--) {
			if (f[j-a[i].x]<=a[i].r) {
				f[j]=min(f[j],max(f[j-a[i].x],a[i].l));
			}
		}
	}
	for (int i=1;i<=n;i++)
		if (f[i]<=n) ans1[++ans]=i;
	cout<<ans<<"\n";
	for (int i=1;i<=ans;i++)
		cout<<ans1[i]<<" ";
	return 0;
}
```

如有问题还请指出。

---

## 作者：小闸蟹 (赞：3)

```cpp
// dp题，详解看代码及我的注释，希望能对大家有所帮助
#include <iostream>
#include <array>
#include <tuple>
#include <algorithm>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::tuple<int, int, int>> Q;   // 端点对<l, r, x>的集合
    for (int i = 0; i < q; ++i)
    {
        int l, r, x;
        std::cin >> l >> r >> x;
        Q.push_back({ l, r, x });
    }
    std::sort(Q.begin(), Q.end(), [](const auto &l, const auto &r) // 按右端点从小到大进行排序
    {
        return std::get<1>(l) < std::get<1>(r);
    });

    constexpr int MaxN = 10000 + 5;
    std::array<int, MaxN> dp{ 0 };

    // dp[i]表示数字i能够达到的最右边的端点位置，如果数字i无法取得则为0
    // 起始状态是dp[0] = n，因为一开始全是0，0本身就能达到最右的端点n
    dp[0] = n;
    for (int i = 0; i < q; ++i) // 排序之后遍历每一个区间
    {
        const auto &[l, r, x] = Q[i];

        for (int j = n; j >= x; --j)    // 由于不能超过n，所以从n往下循环，但到底的时候j - x不能小于零，因此下界是x
        {
            if (dp[j - x] >= l) // 如果左端点小于j - x能在的最右位置，说明j - x有可能被这个加上的x更新。然后我们有两种更新方式：
            {
                if (dp[j - x] <= r) // 如果当前区间能够包含j - x所在的最右端点，说明j - x可以被更新为j，那么就看一下更新之后是否能延申j的最右端
                {
                    dp[j] = std::max(dp[j], dp[j - x]);
                }
                else // 如果当前区间不能包含j - x，那就看看能不能更新x的位置，由于r以按从小到大排序，所以直接赋值r就行了，它是递增的
                {
                    dp[x] = r;
                }
            }
        }
    }

    int Ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (dp[i])  // 统计能达到的数字有多少个，因为按照原先的约定，无法取得的数字右端点被设为了0
        {
            ++Ans;
        }
    }

    // 按题意输出
    std::cout << Ans << std::endl;
    for (int i = 1; i <= n; ++i)
    {
        if (dp[i])
        {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

$f_i$ 表示当序列最大值为 $i$，值为 $i$ 的数中最左边的下标。这是方向在 dp 中取到的极大作用。

区间背包产生的贡献与下标相关，那么对于最大值的贡献要在可继承的情况下转移，继承意味着新区间要覆盖旧的最大值，在它的基础上转移。

那么有方程 $f_i = \min\{f_i,\max\{f_{i-x_j},l_j\}\}$。这个方程涵盖了新旧区间的左端的扩展。所以是正确的。

那么这个 dp 的核心思想在于，把条件作为 dp 的主体，把优越的解当作状态。

那么对于所有的 $k$，都看看是否能将 dp 结果压至整个序列中即可。

---

## 作者：sanaka87 (赞：2)

大家好，因为我是一个新手，所以我用了一个傻逼方法秒了这题。

显然我们只需要考虑有交的线段集合，否则统计出来的答案可以被有交的线段集合包含。

那么枚举交点位置，跑所有包含这个点的线段的 01 背包，更新每一个点的取值即可。

扫描线+退背包即可。01 背包做方案数，选择 998244353 作为模数，这道题就艹过去了。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define ljc 998244353
#define gc getchar
using namespace std;
inline int read(){
	int x=0,f=1;char ch=gc();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=gc();}
	while (isdigit(ch)){x=x*10ll+ch-'0';ch=gc();}
	return x*f;
}
int n,m,f[10001],g[10001];
vector<int> add[10001],del[10001];
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++){
		int l=read(),r=read(),w=read();
		add[l].push_back(w);
		del[r].push_back(w);
	}
	f[0]=1;
	for (int i=1;i<=n;i++){
		for (auto j:add[i]){
			for (int k=n;k>=j;k--) f[k]=(f[k]+f[k-j])%ljc;
		}
		for (int j=1;j<=n;j++) g[j]|=(f[j]>0);
		for (auto j:del[i]){
			for (int k=j;k<=n;k++) f[k]=(f[k]-f[k-j]+ljc)%ljc;
		}
	}
	int _=0;
	for (int i=1;i<=n;i++) _+=g[i]>0;
	printf("%d\n",_);
	for (int i=1;i<=n;i++) if (g[i]>0) printf("%d ",i);
	return 0;
}

```

一看题解发现可以线段树分治+bitset 优化，但是我是一个新手，所以我没想到，自闭了。但是复杂度差不多，因为多了一个 log。

一看题解发现我又被学弟吊打了。不过这好像很正常。

---

## 作者：大菜鸡fks (赞：2)

emmmmmm 怀疑自己傻掉了

由于选的是集合，你可以先选好必选的，再选其他的。

能使第i个元素改变大小的只能是包含这个元素的区间。我们可以用类似背包的方法得到这个元素的取值种类和大小

这些取值是均能达到的。因为你可以只取这一些操作，并且操作的值都是>0的，这可以保证你是最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10005;
int n,q;
vector<int > tag[N<<2];
bitset<N> ans,C;
void update(int k,int l,int r,int x,int y,int w){
	if (l==x&&r==y) {tag[k].push_back(w); return;}
	int mid=(l+r)>>1;
	if (mid>=y) update(k<<1,l,mid,x,y,w);
		else if (mid<x) update(k<<1|1,mid+1,r,x,y,w);
			else update(k<<1,l,mid,x,mid,w),update(k<<1|1,mid+1,r,mid+1,y,w);
}
void dfs(int k,int l,int r,bitset<N> A){
	bitset<N> B=A;
	for (int i=0;i<tag[k].size();i++) B|=(B<<tag[k][i]);
	if (l==r) {ans|=B; return;}
	int mid=(l+r)>>1; dfs(k<<1,l,mid,B); dfs(k<<1|1,mid+1,r,B);
}
int main(){
	scanf("%d%d",&n,&q);
	for (int i=1;i<=q;i++){
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		update(1,1,n,l,r,x); 
	}
	C[0]=1;
	dfs(1,1,n,C); int tot=0;
	for (int i=1;i<=n;i++) if (ans[i]) tot++;
	printf("%d\n",tot);
	for (int i=1;i<=n;i++) if (ans[i]) printf("%d ",i);
	puts("");
	return 0;
} 
```

---

## 作者：Hasinon (赞：0)

### 前言
本题暴力 DP 可过，而且能优雅的拿到最优解 [here](https://www.luogu.com.cn/record/69596894)，鉴于有神犇写过该题 DP 题解
[here](https://www.luogu.com.cn/blog/dfg/solution-cf981e)，我在他的基础上简化一下代码实现。  

### 解析
如何搞出序列最大值 $k$？如果存在一些相交的区间（或者只选一个）他们的加值和等于 $k$，说明可行。  

所以设 $dp_i$ 为使序列最大值为 $i$ 的一些区间的左边界最大值。  
我们把所有区间按左边界大小排序，从大到小遍历区间。两个区间相交，即 $ l_i≤ l_j $ 且 $ l_j≤r_i$。  
因为我们已经排了序，所以我们只需要管第二个条件。  
当枚到第 $i$ 个区间时，如果存在序列最大值 $k$ 且 $dp_k≤r_i$,说明 $k+x_i$ 也存在。

### ~~摸鱼结束~~ 开始原创

- 因为按左边界从大到小枚区间，所以 $ dp_{k+x_i}=dp_k $。

- 特判一下单选一个区间，即枚完一个区间后用此区间的 $k$ 和 $l$ 进行初始化 $dp_{k}=l$。

### code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(int i=(a); i>=(b); --i)
using namespace std;
//
const ll N=1e4;
//
struct node{
	ll l,r,z;
};
node que[N+10];
ll dp[N+10];
//
bool cmp(node a,node b){
	return a.l<b.l; 
}
int main() {
	memset(dp,0x3f,sizeof(dp));
	ll n=gt(),q=gt();
	FOR(i,1,q){
		que[i].l=gt(),que[i].r=gt(),que[i].z=gt();
	} 
	sort(que+1,que+q+1,cmp);
	ROF(i,q,1){
		node aba=que[i];
		ROF(j,n-aba.z,1){
			aba.r>=dp[j]?dp[j+aba.z]=dp[j]:n; 
		} 
		dp[aba.z]=aba.l;
	}
	ll ans=0;
	FOR(i,1,n) ans+=dp[i]<=n?1:0;
	printf("%lld\n",ans);
	FOR(i,1,n) dp[i]<=n?printf("%lld ",i):n;
}


```

~~为代码美观删了快读 XD~~


---

