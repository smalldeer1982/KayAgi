# Turtle and Multiplication

## 题目描述

Turtle 刚刚在数学课上学会了如何将两个整数相乘，他感到非常兴奋。

然后 Piggy 给了他一个整数 $n$，并要求他构造一个由整数组成的序列 $a_1, a_2, \ldots, a_n$，使其满足以下条件：

- 对于所有 $1 \le i \le n$，都有 $1 \le a_i \le 3 \cdot 10^5$。
- 对于所有 $1 \le i < j \le n - 1$，都有 $a_i \cdot a_{i + 1} \ne a_j \cdot a_{j + 1}$。

在所有满足条件的序列中，Piggy 要求 Turtle 找出不同元素数量最少的那一个。

Turtle 显然无法解决这个问题，所以请你帮帮他吧！

## 说明/提示

在第三个测试用例中，$a = [3, 4, 2, 6]$ 不满足第二个条件，因为 $a_1 \cdot a_2 = a_3 \cdot a_4$。$a = [2, 3, 4, 4]$ 虽然满足条件，但其不同元素的数量不是最少的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2
3
4```

### 输出

```
114514 114514
1 2 2
3 3 4 4```

# 题解

## 作者：EuphoricStar (赞：10)

$a_i \cdot  a_{i + 1} = a_j \cdot  a_{j + 1}$ 的必要条件是无序对 $(a_i, a_{i + 1})$ 和无序对 $(a_j, a_{j + 1})$ 相同。事实上，若 $a_i$ 都取质数，那么这个必要条件就会变成充要条件。

如果我们把 $(a_i, a_{i + 1})$ 看成一条边，那么问题变成找到点数最少的无向完全图（每个点还有一个自环），使得这个完全图存在一条经过 $n - 1$ 条边且不经过重复边的路径。

考虑若完全图点数确定，我们如何计算这个完全图的最长不经过重复边的路径长度。

设完全图点数为 $m$，若 $m$ 是奇数那么每个点的度数都是偶数，所以这个图存在欧拉路径，路径长度即为边数，其等于 $\frac{m(m + 1)}{2}$。

若 $m$ 是偶数那么每个点的度数都是奇数，我们需要删除一些边使得这个图存在欧拉路径。容易发现一条边最多使奇度数点的数量减少 $2$，所以我们至少需要删除 $\frac{m}{2} - 1$ 条边，删除 $(2, 3), (4, 5), \ldots, (m - 2, m - 1)$ 这些边即可，路径长度为 $\frac{m(m - 1)}{2} - \frac{m}{2} + 1 + m = \frac{m^2}{2} + 1$。

当 $n = 10^6$ 时最小的 $m$ 是 $1415$，第 $1415$ 小的质数是 $11807$，符合 $a_i \le 3 \cdot  10^5$。

我们可以二分求出最小的 $m$，使用 Hierholzer 算法求出一个无向图的欧拉路径。

时间复杂度：每个测试用例 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 4000100;
const int N = 1000000;

int n, a[maxn], pr[maxn], tot, stk[maxn], top;
bool vis[maxn];

inline void init() {
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) {
			pr[++tot] = i;
		}
		for (int j = 1; j <= tot && i * pr[j] <= N; ++j) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				break;
			}
		}
	}
	mems(vis, 0);
}

inline bool check(int x) {
	if (x & 1) {
		return x + 1 + x * (x - 1) / 2 >= n;
	} else {
		return x * (x - 1) / 2 - x / 2 + 2 + x >= n;
	}
}

vector<pii> G[10000];

void dfs(int u) {
	while (G[u].size()) {
		pii p = G[u].back();
		G[u].pop_back();
		if (vis[p.scd]) {
			continue;
		}
		vis[p.scd] = 1;
		dfs(p.fst);
	}
	stk[++top] = pr[u];
}

void solve() {
	scanf("%d", &n);
	int l = 1, r = 10000, ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	for (int i = 1; i <= ans; ++i) {
		vector<pii>().swap(G[i]);
	}
	int tot = 0;
	for (int i = 1; i <= ans; ++i) {
		for (int j = i; j <= ans; ++j) {
			if (ans % 2 == 0 && i % 2 == 0 && i + 1 == j) {
				continue;
			}
			G[i].pb(j, ++tot);
			G[j].pb(i, tot);
		}
	}
	for (int i = 1; i <= tot; ++i) {
		vis[i] = 0;
	}
	top = 0;
	dfs(1);
	reverse(stk + 1, stk + top + 1);
	for (int i = 1; i <= n; ++i) {
		printf("%d%c", stk[i], " \n"[i == n]);
	}
}

int main() {
	init();
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Oracynx (赞：4)

## [CF1981D] Turtle and Multiplication 题解

### 思路分析

注：本题解非正解。

我们考虑一个最多使用 $n$ 个不同元素构造最优序列的方式。

首先我们对于 $n$ 个队列 $q_i$，将 $1 \sim n$ 加入队列。

然后记录 $now$，每次从重复取出队首的元素 $k$ 直到 $now \times k$ 没有出现，在序列尾部增加 $k$，$now \gets k$​。

代码如下：

```cpp
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= n; j++)
    {
        q[i].push(j);
    }
}
int now = 1;
printf("%d", lk[now]);
int cnt = 1;
for (; cnt < limit;)
{
    int next = -1;
    for (; !q[now].empty();)
    {
        int k = q[now].front();
        q[now].pop();
        if (!vis[now * k])
        {
            next = k;
            break;
        }
    }
    if (next == -1)
    {
        break;
    }
    vis[now * next] = true;
    vis[next * now] = true;
    printf(" %d", lk[next]);
    now = next;
    cnt++;
}
printf("\n");
```

显然不是最优的，考虑更改序列顺序。

显然的对于一个合法的序列 $\dots, x, y, z, \dots$，其肯定可以更改为 $\dots, x, y, y, z, \dots$。

我们自然地想到把 $i$ 的队首放置为 $i$。

代码如下：

```cpp
for (int i = 1; i <= n; i++)
{
    q[i].push(i);
    for (int j = 1; j <= i - 1; j++)
    {
        q[i].push(j);
    }
    for (int j = i + 1; j <= n; j++)
    {
        q[i].push(j);
    }
}
```

然后我们就很自然地发现后面两个循环的相对顺序和枚举方向一共有 $2 \times 2^2 = 8$ 种方式。

每种都试一下。

尽管如此，我们发现此时的序列依旧不尽人意，使用 $6$ 个元素最多构造长度为 $18$，最优的是 $20$。

我们发现，$4 = 1 \times 4 = 2 \times 2$，占用了 $2$ 对数，而更大的数甚至更多。

同时 $1 \le a_i \le 3 \times 10^5$，而我们使用的远远不足。

想到寻找一些乘积互不相同的数。

对于每一个数，如果他们的因数互不相同，显然他们也不可能相同。

选用质数，先筛到 $2000$ 个备用。

由于质数过大，我们无法使用数组，选用 `unordered_map`。

这时，我们的代码便稀里糊涂地构造出了最优序列。

但我们代码的巨大常数加上哈希表简直是雪上加霜……

由于乘积互不相同，所以我们只需要标记是哪两个质数相乘即可，同时还需要标记互换位置的情况。

```cpp
void solve(int n, int limit)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            vis[i][j] = false;
        }
        for (; !q[i].empty();)
        {
            q[i].pop();
        }
        q[i].push(i);
        for (int j = i - 1; j >= 1; j--)
        {
            q[i].push(j);
        }
        for (int j = n; j >= i + 1; j--)
        {
            q[i].push(j);
        }
    }
    int now = 1;
    printf("%d", lk[now]);
    int cnt = 1;
    for (; cnt < limit;)
    {
        int next = -1;
        for (; !q[now].empty();)
        {
            int k = q[now].front();
            q[now].pop();
            if (!vis[now][k])
            {
                next = k;
                break;
            }
        }
        if (next == -1)
        {
            break;
        }
        vis[now][next] = true;
        vis[next][now] = true;
        printf(" %d", lk[next]);
        now = next;
        cnt++;
    }
    printf("\n");
}
```

但我们需要从所需序列的长度获取所需的元素个数。

而现在我们的代码已经接近了时限极限。

同时由于只需要 $1415$ 个元素即可达到 $10^6$ 的长度，所以我们选择打表。

```shell
clang++ CF1981D.cpp -o judge.exe -O3
./judge.exe > list.txt
```

得到了以下每个元素数量对应的最大的序列长度。

[Link](https://www.luogu.com.cn/paste/7hvj6632)

然后二分所需的元素数量，总体复杂度忽略二分为 $O(\sum n)$。

### 代码实现

出于观赏性，[完整代码](https://www.luogu.com.cn/paste/xj6zipdk)并没有放置于此。

```cpp
int size[] = {};
#include <cstdio>
#include <cstring>
#include <queue>
constexpr int MaxN = 2e3 + 5;
constexpr int MaxM = 3e5 + 5;
int n;
int top;
int lk[MaxN];
bool v[MaxM];
bool vis[MaxN][MaxN];
std::queue<int> q[MaxN];
void init()
{
    for (int i = 2; i <= 300000 && top <= 2000; i++)
    {
        if (v[i])
        {
            continue;
        }
        top++;
        lk[top] = i;
        for (int j = 2; i * j <= 300000; j++)
        {
            v[i * j] = true;
        }
    }
}
void solve(int n, int limit)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            vis[i][j] = false;
        }
        for (; !q[i].empty();)
        {
            q[i].pop();
        }
        q[i].push(i);
        for (int j = i - 1; j >= 1; j--)
        {
            q[i].push(j);
        }
        for (int j = n; j >= i + 1; j--)
        {
            q[i].push(j);
        }
    }
    int now = 1;
    printf("%d", lk[now]);
    int cnt = 1;
    for (; cnt < limit;)
    {
        int next = -1;
        for (; !q[now].empty();)
        {
            int k = q[now].front();
            q[now].pop();
            if (!vis[now][k])
            {
                next = k;
                break;
            }
        }
        if (next == -1)
        {
            break;
        }
        vis[now][next] = true;
        vis[next][now] = true;
        printf(" %d", lk[next]);
        now = next;
        cnt++;
    }
    printf("\n");
}
int main()
{
    init();
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        int need;
        scanf("%d", &need);
        int l, r;
        l = 1;
        r = 1415;
        int res = -1;
        for (; l <= r;)
        {
            int mid = (l + r) / 2;
            if (size[mid] >= need)
            {
                res = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        solve(res, need);
    }
    return 0;
}
```

---

## 作者：_determination_ (赞：3)

发现只需要让所有的数都是质数并且相邻的数对不同即可。

数据范围内的质数有至少 10000 个，而按照这样的构造方式是完全可以的。

怎么构造呢？我们建出一个带自环的完全图跑欧拉回路即可。

发现当点数是偶数的时候，是没有欧拉回路的。所以我们删去全部形如 $2x$，$2x+1$ 的边跑欧拉回路，最后路径就是答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define debug cout << "114514" << endl
const int mod=1e9+7;
const int inf=0x3f3f3f3f3f3f3f3f; 
int vis[300010],pm[300010],tot;
void init()
{
	for ( int i = 2 ; i <= 3e5 ; i++ )
	{
		if(!vis[i])pm[++tot]=i;
		for ( int j = 1 ; j <= tot ; j++ )
		{
			if(pm[j]*i>3e5)break;
			vis[pm[j]*i]=1;
			if(i%pm[j]==0)break;
		}
	}
}
vector<pair<int,int> >e[10010];
stack<int>st;
int vise[5000010];
void dfs(int x)
{
	while(e[x].size())
	{
		int v=e[x].back().first,id=e[x].back().second;
		e[x].pop_back();
		if(vise[id])continue;
		vise[id]=1;
		dfs(v);
	}
	st.push(x);
}
void solve()
{
	int n;
	cin >> n;
	int len=0;
	for ( int i = 1 ; i <= 1415 ; i++ )
	{
		if(i&1)
		{
			if(i*(i-1)/2+i>=n-1)
			{
				len=i;
				break;
			}
		}else{
			if(i*(i-1)/2-i/2+1+i>=n-1)
			{
				len=i;
				break;
			}
		}
	}
	if(len==1)
	{
		if(n==1)
		{
			cout << 1 << endl;
			return;
		}else{
			cout << "1 1" << endl;
			return;
		}
	}
	if(len==2)
	{
		if(n==3)
		{
			cout << "1 1 2" << endl;
			return;
		}else{
			cout << "1 1 2 2" << endl;
			return;
		}
	}
	int tot=0;
	for ( int i = 1 ; i <= len ; i++ )
	{
		e[i].clear();
	}
	for ( int i = 1 ; i <= len ; i++ )
	{
		for ( int j = i ; j <= len ; j++ )
		{
			if(len%2==0&&i%2==0&&i+1==j)continue;
			e[i].push_back({j,++tot});
			e[j].push_back({i,tot});
		}
	}
	for ( int i = 1 ; i <= tot ; i++ )
	{
		vise[i]=0;
	}
	dfs(1);
	while(!st.empty()&&n--)
	{
		cout << pm[st.top()] << " ";
		st.pop();
	}
	cout << endl;
	
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    init();
    int T;
    cin >>T;
    while(T--)solve();
    return 0;
} 
```

---

## 作者：Luzhuoyuan (赞：3)

Links: [[Codeforces]](http://codeforces.com/problemset/problem/1981/D) [[Luogu]](https://www.luogu.com.cn/problem/CF1981D)

一种不需要跑欧拉路的做法。

### 题意

给定一个正整数 $n$ 要求构造一个正整数序列 $a$，满足 $a$ 中数字种数最少，且：

- $\forall 1\le i\le n,1\le a_i\le 3\cdot 10^5$；
- $\forall 1\le i\le j\le n-1,a_i\cdot a_{i+1}\ne a_j\cdot a_{j+1}$。

每个测试点 $t$ 组测试用例。

- $1\le t\le 10^4$；
- $2\le n\le 10^6$；
- $\sum n\le 10^6$。

### 思路

首先，我们将原问题转化为一个图论问题，将每种数看作一个点，原问题即转化为找出一条长为 $n-1$ 的（非简单）路径，其中经过的每条边的权值即两端之积都不同，并要求经过点数最少。

我们要让有限的点数创造更长的路径，就要尽量使不同的边权值不同。我们可以令每个点的权值为最小的一些质数，并且将每个点与所有点（包括自己）连边，这样每条边权值不同。

根据欧拉路的判定定理，对于 $m$ 个点，若 $n$ 为奇数，则路径最长为 $\frac{m(m+1)}{2}$（这是一个欧拉图），否则为 $\frac{m^2}{2}+1$（即只经过一条对称轴，非对称轴的边全都经过）。这样边数大约为 $\frac{m^2}{2}$ 条，而 $3\times 10^5$ 以内显然有足够的质数来构造这条路径。

根据这个构造方法直接建图跑欧拉路就能解决了。一种更简单的做法是：考虑到达一个点时，先走它上面的自环，然后一直走从当前点开始顺时针跨过（跳过）$1$ 个点的边（如果没有走过的话），直到回到该点；然后再走跨过 $2$ 个、$3$ 个等点的边，走完后再走到顺时针下一个点。在走跨过 $(k-1)$ 个点的边时，会经过每一个与当前节点同余于 $\gcd(k,m)$ 的点。因此我们先处理出每个 $k$ 的 $\gcd(k,m)$，并按照 $\gcd$ 降序排序，然后对于每个点 $i$ 走 $\gcd(k,m)\ge i$ 的边即可。最后要记得回到开始点。若 $m$ 为偶数则可以在最开始先从点 $\frac m 2+1$ 走到点 $1$（先把加上去的对称轴走了）。复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=1e6+5,V=1e6;
int _,n,m,k,p[N],pn,c[N];
bool fl[N];
vector<int> ve;
struct node{int x,g;}a[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	for(int i=2;i<=V&&pn<=2000;i++){
		if(!fl[i])p[++pn]=i;
		for(int j=1;j<=pn&&i*p[j]<=V;j++){
			fl[i*p[j]]=true;
			if(i%p[j]==0)break;
		}
	}
	for(int i=1;i<=pn;i++)c[i]=(i&1?i*(i+1)/2:i*i/2+1);
	cin>>_;
	while(_--){
		cin>>n;
		if(n==3){cout<<"1 1 2\n";continue;}
		if(n==4){cout<<"1 1 2 2\n";continue;}
		m=lower_bound(c+1,c+pn+1,n-1)-c;ve.clear();k=0;
		//上面这个 m 可以直接计算，偷懒（这会使复杂度加上一个 O(t log n)）
		if(!(m&1))ve.pb(p[m/2+1]);
		for(int i=2;(i<<1)<m;i++)a[++k]={i,__gcd(m,i)};
		sort(a+1,a+k+1,[](node x,node y){return x.g>y.g;});
		for(int i=1;i<=m;i++){
			ve.pb(p[i]),ve.pb(p[i]);
			for(int j=1;j<=k&&a[j].g>=i;j++){
				int x=i;
				do x=(x+a[j].x-1)%m+1,ve.pb(p[x]);while(x!=i);
			}
		}ve.pb(p[1]);
		for(int i=0;i<n;i++)cout<<ve[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

（逃

---

## 作者：Disjoint_cat (赞：3)

# [CF1981D](https://www.luogu.com.cn/problem/CF1981D)

众所周知一篇题解需要一张头图。

![](https://cdn.luogu.com.cn/upload/image_hosting/5sfso9km.png)

## 题意

给定 $n$，构造长为 $n$ 的序列 $a$，使得相邻两项的乘积两两不等，且 $a$ 中不同的数的个数最少。

Data range：$n\le10^6$。

## 题解

首先乘积这个东西很辣手，所以考虑一个必要条件：每相邻两项组成的无序对两两不同。

然后会发现只要每一种数都取质数，就能保证乘积也一定两两不同。

所以只需要考虑上述条件就可以了。

二分答案，不妨假设需要判定 $x$ 种不同的数是否可行。

把每一种数看成一个点，相邻两个数看成一条边。显然序列长度是边数 $+1$。

那么就转化成了：$x$ 个点的无向完全图（加上自环），一条边只能走一次，求最长路。也就是保留尽量多的边，使其存在欧拉路径。

如果 $x$ 是奇数，由于所有点度数都是 $x+1$，所有边都可以保留；

如果 $x$ 是偶数，那么所有点度数都是奇数，所以我们至少要删掉 $\dfrac{x-2}2$ 条边，才能使奇点个数不超过 $2$。例如，可以删去形如 $(2i,2i+1),i\in[1,\frac x2-1]$ 的所有边，此时只有 $1$ 和 $x$ 是奇点。

然后直接跑欧拉回路并构造即可。时间复杂度 $\Theta(n)$。

可以证明最小可行的 $x=\Theta(\sqrt n)$，而在 $n=10^6$ 时第 $x$ 个质数只有大概 $10000$，所以数的大小远远不会爆炸。另外如果你把二分上界设为 $\Theta(\sqrt{\max n})$ 并且你二分的 check 是不优秀的 $\Theta(x^2)$，你会被多测干成 [TLE on test 5](https://codeforces.com/contest/1981/submission/263483522)。

[赛时 submission](https://codeforces.com/contest/1981/submission/263484289)。

---

## 作者：封禁用户 (赞：1)

### 题面
让你构造一个长为 $n$ 的序列 ${a}$，使得

- $1 \le a_i \le 3 \times 10^5$
- $\forall 1 \le i<j\le n-1$，有 $a_ia_{i+1} \ne a_ja_{j+1}$，即：相邻两项之积两两互不相等。

最小化元素种数。

### 思路
很容易想到质数两两乘积不同。
于是先试试可以全填质数，因为不同，所以 $a_i$ 不等于 $a_{i+1}$ 的几何意义可以理解为：当 $a_i$ 与 $a_{i+1}$ 连边时，满足可以从 $1$ 走到 $n$ 且任意一条路走且只走一遍，而这样，我们要求的就是 $n$ 个点的完全图中的长 $k$ 的子图满足上述条件。然后发现这玩意就是欧拉路径。

在分析一下欧拉序列的特质，可以简单发现 $x$ 个点的最大欧拉路径：

- $x$ 为奇数：$(x+1)\times x/2+1$。因为 $n-2$ 个点此时度数为 $x$ 是奇数，要减一，而起点和终点不用。
- $x$ 为偶数：$(x+1)\times x/2-x/2+2$。原因跟上面的差不太多，就不赘述了。

啊于是再看我们要选 $n$ 的值，发现这玩意对结果单调递增，于是二分来了。

最后就一个二分找最小值、一个线性筛再加一个欧拉路径就没了。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 10000005 
using namespace std;
struct Prim {
    int prim[Maxn],vis[Maxn],tot;
    void into(int n) {
        for(int i=2;i<=n;i++) {
            if(!vis[i])prim[++tot]=i;
            for(int j=1;j<=tot&&i*prim[j]<=n;j++) {
                vis[i*prim[j]]=1;
                if(i%prim[j]==0)break;
            }
        }
    }
} ;
Prim line;
struct Road {int to,id;};
vector<Road> q[Maxn];
int vis[Maxn];
stack<int> st;
void dfs(int x) {
    for(Road u:q[x]) {
        if(!vis[u.id])
            vis[u.id]=1,
            dfs(u.to);
    } st.push(x);
}
int main()
{
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    int t,n;
    cin>>t;
    line.into(3e5);
    while(t--) {
        for(int i=1;i<=n;i++)
            q[i].clear();
        cin>>n;
        int l=1,r=3e5,mid,ans;
        while(l<=r) {
            mid=(l+r)>>1;
            if(((mid%2==1)&&(n<=mid*(mid+1)/2+1))||((mid%2==0)&&(n<=mid*(mid+1)/2-mid/2+2)))
                r=mid-1,ans=mid;
            else l=mid+1;
        } int cnt=0;
        for(int i=1;i<=ans;i++) {
            for(int j=i;j<=ans;j++) {
                if((ans%2==0)&&(i==j-1)&&i%2==0)
                    continue;
                q[i].push_back({j,++cnt}),
                q[j].push_back({i,cnt});
                // cout<<i<<" "<<j<<" )\n";
            }
        }
        int ans0=1;
        for(int i=1;i<=n;i++)
            if(((int)q[i].size())%2)
                ans0=i;
        dfs(ans0); ans0=0;
        for(int i=1;i<=cnt;i++)
            vis[i]=0;
        while(!st.empty()&&++ans0<=n)
            cout<<line.prim[st.top()]<<" ",st.pop();
        while(!st.empty())st.pop();
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：Fesdrer (赞：1)

首先容易想到填入质数。因为 $a_i\le 3\times 10^5$，其中的质数足以组成超过 $n$ 个不同的乘积。那么接下来将问题转化为图论问题。

假设我们要填入 $d$ 个不同的质数，在任意两个质数之间连边（两个质数可以相同，即可以出现自环），这样子问题就转化为了选择一个质数开始并不断沿着边走 $n$ 步，同时不能走重复的边（否则就出现重复的乘积了）。

容易发现这是一个欧拉路问题。如果 $d$ 为奇数，则每个点的度数为 $d+1$ 为偶数，必然存在一个欧拉回路，最多能形成长度为 $\frac{d(d+1)}2$ 的序列。而如果 $d$ 为偶数，我们删去其中的 $\frac d2-1$ 条边且删去的边没有两条边有公共的端点，例如 $d=6$ 时，我们删去边 $(1,2),(3,4)$，剩下的点中只有 $2$ 个点度数为 $d+1$，其他的点度数都是 $d$，因此存在一个欧拉路径，最多能够形成长度为 $\frac{d^2}2+1$ 的路径。

找到最小的能形成长度超过 $n$ 的路径的 $d$，然后建图跑欧拉路即可。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T,n,m,a[N];
int vis[N],pr[N],prn;
unordered_set<int> e[2000];
void init(){
	for(int i=2;i<N;i++){
		if(!vis[i])		pr[++prn]=i;
		for(int j=1;j<=prn&&i*pr[j]<N;j++){
			vis[i*pr[j]]=1;
			if(i%pr[j]==0)	break;
		}
	}
}
int getnum(){
	int l=1,r=5005;
	while(l<r){
		int mid=(l+r)/2;
		if((mid&1?(mid*(mid+1)/2):(mid*mid/2+1))+1>=n)	r=mid;
		else	l=mid+1;
	}
	return l;
}
void build(){
	for(int i=1;i<=m;i++)	e[i].clear();
	if(m&1)	for(int i=1;i<=m;i++)	for(int j=i;j<=m;j++)	e[i].insert(j),e[j].insert(i);
	else	for(int i=1;i<=m;i++)	for(int j=i;j<=m;j++)
		if(!((i&1)&&j==i+1&&i!=1))	e[i].insert(j),e[j].insert(i);
}
void dfs(int x,vector<int> &ans){
	while(e[x].size()){
		int y=*e[x].begin();
		e[x].erase(y),e[y].erase(x);
		dfs(y,ans);
	}
	ans.push_back(x);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	init();
	while(T--){
		cin>>n;
		m=getnum();
		build();
		vector<int> ans(0);
		dfs(1,ans);
		while(n--)	cout<<pr[ans.back()]<<" ",ans.pop_back();
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：1)

在校考试时作为 $\texttt{T5}$ 出现的。

首先我们考虑只取质数，为啥这样呢？

因为我们两个质数的乘积的分解只有这一种方式，设 $P_i$ 为第 $i$ 个质数。

当 $a_ia_{i+1}=a_ja_{j+1}$，当且仅当 $a_i=a_j,a_{i+1}=a_{j+1}$ 或者 $a_i=a_{j+1},a_{i+1}=a_j$。

这么完美的性质，现在假设有 $n$ 个质数，那么我们知道，这些质数可以产生最多 $\frac{(n+1)n}2$ 对关系，那我们如何把这些关系全用上呢？

考虑质数看成点，那么我们相当于在完全图上做一笔画，经典的欧拉路问题。

在 $n$ 为奇数下欧拉回路的条件满足。

在 $n$ 为偶数下删掉 $(2,3)(4,5)$ 等边即可成为一条欧拉路径。

~~考试这堆东西我想出来了，不会打欧拉路（大雾~~

```cpp
#include <bits/stdc++.h>
using namespace std;
bool vis[15000][15000];
stack<int>st;
vector<int>vec[150000];
int t,cnt,prime[600005],h[150000];
bool book[300005];
void init(){
	book[1]=1;
	for(int i=2;i<=300000;i++){
		if(!book[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&prime[j]*i<=300000;j++){
			book[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int check(int n){
	if(n%2==0)return n*(n+1)/2-n/2+2;
	return n*(n+1)/2+1;
	//n*(n+1)/2 n/2-1
}
//int cnt1;
void dfs(int u){
//	cnt1++;
//	cout<<cnt1<<"\n";
//	cout<<u<<"\n";
//	h[u]++;
//	cout<<"iakioi\n";
	for(int i=h[u];i<vec[u].size();i=h[u]){
//		cout<<h[u]<<endl;
		if(vis[u][vec[u][i]]){
			h[u]=i+1;
			continue;
		}
		
		h[u]=i+1;
		
		vis[u][vec[u][i]]=1;
	
		vis[vec[u][i]][u]=1;
//		cout<<i<<" "<<u<<" "<<vec[u][i]<<"\n";
		dfs(vec[u][i]);
		
	}
	st.push(u);
}
void work(){
	int n;
	cin>>n;
//	cout<<n<<endl;
	while(!st.empty())st.pop(); 
	int ans=1;
	while(check(ans)<n)ans++;
//	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)h[i]=0,vec[i].clear();
	for(int i=1;i<=ans;i++)for(int j=1;j<=ans;j++)vis[i][j]=0;
	for(int i=1;i<=ans;i++){
		for(int j=i;j<=ans;j++){
			if(ans%2==0&&i==j-1&&i%2==0)continue;
			vec[i].push_back(j);
			vec[j].push_back(i);
		}
	}
//	cout<<"iakioi"<<endl;
	dfs(1);
	for(int i=1;i<=n;i++)cout<<prime[st.top()]<<" ",st.pop();
	cout<<"\n";
}
int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
    
    init();
    cin>>t;
	while(t--)work();
    return 0; 
}
```

---

## 作者：_Chronostatis_ (赞：0)

## 题意
给定一个整数 $n$，构造一个长度为 $n$ 的整数序列 $a$，使得其满足以下条件且为合法答案中不同元素个数最小的一个：
- 对于 $1 \le i \lt j \lt n$，有 $a_i \times a_{i + 1} \ne a_j \times a_{j + 1}$。

## 思路
前置芝士：数论基础、欧拉路径。

看到题目，会发现似乎不太好构造这种序列。但是如果我们观察性质，那么就会发现，如果只使用质数，那么麻烦将大大减小。设 $p, q$ 为质数，那么能与 $p \times q$ 相等的只有 $q \times p$，因为只能使用质数，而 $p \times q$ 显然不是质数。

所以我们尝试使用质数来构造序列。如果我们将一个个质数视作一个个节点，将节点间的连边视作乘积，那么就会发现，此时每条边最多经过一次。设总用的质数个数为 $x$，此时总边数为 $\frac{x(x - 1)}2 + x = \frac{x(x + 1)}2$，因为自环也可以算进去，如果我们将双向边视作两条单向边，那么每个点的度数就是 $x + 1$。若 $x$ 为奇数，那么可以构造出一条欧拉回路。

但是 $x$ 并不总是奇数。如果 $x$ 为偶数，那么 $x + 1$ 为奇数，此时图没有任何特殊性质。我们考虑删一些边，如果我们删除形式为 $(1, 2), (3, 4), \dots, (x - 1, x)$ 的边，并留下其中一条，设留下边的端点分别为 $u, v$，那么除留下的边的两个端点外，每个点的度数都会减少 1。此时可以构造出一条起点为 $u$，终点为 $v$ 的欧拉路径。此时留下的边数为 $\frac{x(x + 1)}2 - \frac x 2 + 1 = \frac{x^2}2 + 1$。

所以我们可以对输入的 $n$ 进行处理，使得边数不超过 $n - 1$，因为输入的 $n$ 实际上是点数。定义如下函数：

$$
f(x) = \begin{cases} 
\frac{x(x + 1)}2 && x \equiv 1 \pmod 2 \\
\frac{x ^ 2}2 + 1 && x \equiv 0 \pmod 2
\end{cases}
$$

那么就是找到最小的 $x$，使得 $f(x) \ge n$。容易发现该函数在 $[0, +\infty)$ 上单增。因为对于任意 $x \in [0, + \infty)$，都满足 $\frac{x(x + 1)}2 \lt \frac{(x + 1)^2}2 + 1 \lt \frac{(x + 2)(x + 3)}2$。

所以我们可以预处理 $10^6$ 内的质数，然后将 $f(x)$ 预处理成为一个数组，二分求解 $x$ 即可。每次按照上述做法删边，最后跑一边 dfs 求解欧拉路径即可。

关于欧拉路径，详见 [OI Wiki](https://oi-wiki.org/graph/euler/)，这里不再赘述。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e6 + 10;

int n, p[MAXN], tot, to[MAXN], ec;
ll f[MAXN];
bool vis[MAXN << 1];
vector<pii> g[MAXN];
vector<int> res;

void dfs(int u) {
  for (int i = to[u]; i < g[u].size(); i = to[u]) {
    to[u] = i + 1;
    pii e = g[u][i];
    if (vis[e.second]) continue;
    vis[e.second] = vis[e.second ^ 1] = 1;
    dfs(e.first);
  }
  res.push_back(u);
}

void add_edge(int u, int v) {
  g[u].push_back({v, ec++});
  g[v].push_back({u, ec++});
}

void Solve() {
  cin >> n;
  int x;
  for (x = 1; f[x] < n; x++);
  for (int i = 1; i <= x; i++) {
    for (int j = i; j <= x; j++) {
      if (x % 2 == 0 && i % 2 == 1 && j == i + 1 && i != 1) continue;
      add_edge(i, j);
    }
  }
  res.clear();
  dfs(1);
  fill(vis + 0, vis + ec + 1, 0);
  ec = 0;
  for (int i = 1; i <= x; i++) {
    g[i].clear();
    to[i] = 0;
  }
  reverse(res.begin(), res.end());
  for (int i = 0; i < n; i++) {
    cout << p[res[i]] << ' ';
  }
  cout << '\n';
}

void Sieve(int n) {
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      p[++tot] = i;
    }
    for (int j = 1; j <= tot && i * p[j] <= n; j++) {
      vis[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
  memset(vis, 0, sizeof(vis));
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  Sieve(MAXN - 1);
  for (int i = 1; i <= tot; i++) {
    f[i] = i % 2 == 1 ? 1ll * i * (i + 1) / 2 + 1 : 1ll * i * (i + 1) / 2 - i / 2 + 2;
  }
  int T;
  for (cin >> T; T--; Solve());
  return 0;
}
```

---

## 作者：yuhong056 (赞：0)

# 题解：CF1981D Turtle and Multiplication
## 题意
给定数 $n$，构造出一个长 $n$ 的数组 $A$，满足：
- 不存在数对 $(i, j)$ 使得 $A_i \times A_{i + 1} \ne A_j \times A_{j + 1}$ 并且 $i \ne j$。
## 思路
首先，我们可以发现：如果存在数对 $(i, j)$ 满足 $\{A_i,A_{i + 1}\} = \{A_j, A_{j + 1}\}$ 并且 $i \ne j$，那么此数组绝对不满足题意。

但是，如果不出现这样的数对，也可能不满足题意，如：$[1, 4, 2, 2]$ 中的数对 $(1, 3)$ 不满足题意。

出现这种原因是因为其中有一个数是合数，导致其可以拆分一个因子给 $A_{i + 1}$。

那么，我们就将所有数都换成质数，那么就可以转换题意：
> 求出只包含质数的且长度为 $n$ 的数组，满足不存在数对 $(i, j)$ 满足 $\{A_i,A_{i + 1}\} = \{A_j, A_{j + 1}\}$ 并且 $i \ne j$。

但是，这题看起来还是没法做，因此，我们考虑给定 $s$ 个质数可以拼出长度为几的数组。

假设我们将 $s$ 个质数抽象成图上的 $s$ 个点，那么他就是一张包含自环的完全图。

假设我们知道了这张图，我们将题意转换成了：
> 给定一张无向图，求出一条路径经过 $n - 1$ 条边，且不经过重复的边。

现在，我们就可以看出：这就是一个一笔画问题。

欧拉告诉过我们：能一笔画的图形要么没有奇点，要么有两个奇点。

可见 [oiwiki](https://oi-wiki.org/graph/euler/#%E5%AE%9A%E4%B9%89)。

因此，可以得出：
- 如果 $x$ 为奇数，那么此图可以一笔走完，有 $\frac{n \times (n + 1)}{2}$ 条边。
- 否则，由于最多有 $2$ 个奇点，整张图的度数和为 $2 \times (n + 1) + (n - 2) \times n$，有 $\frac{2 \times (n + 1) + (n - 2) \times n}{2} = \frac{n^2+2}{2} = \frac{n^2}{2} + 1$ 条边。

因此，我们可以枚举找到第一个有 $n - 1$ 条边的完全图，在在这个完全图上跑一遍欧拉路径即可。
## 细节
如果 $x$ 为奇数，还要删去多余的边，不然会喜提 WA on test 2。
## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 2e6 + 16, MAXM = 4e6 + 26;

int etot;
vector<int>e[MAXN];
int edge[MAXM];
bool vis[MAXM];
int st[MAXN];
vector<int>ans;

vector<int>prime;

void add(int u, int v) {
  e[u].push_back(etot);
  edge[etot] = v;
  etot++;
}

void dfs(int u) {
  for(int i = st[u]; i < e[u].size(); i = st[u]) {
    st[u]++;
    int eid = e[u][i];
    if(vis[eid])continue;
    vis[eid] = vis[eid ^ 1] = 1;
    int v = edge[eid];
    dfs(v);
  }
  ans.push_back(u);
}

void solve() {
  int n;
  cin >> n;
  int s = 1;
  for(; ; s++){ //枚举找到第一个有 n - 1 条边的完全图
    if(s & 1){
      if((s + 1) * s / 2 >= n - 1)break;
    }else{
      if(s * (s + 1) / 2 - s / 2 + 1 >= n - 1)break;
    }
  }
  ans.clear();
  for(int i = 1; i <= s; i++) {
    for(int j = i; j <= s; j++) {
    if(s % 2 == 0 && i > 2 && i % 2 == 1 && j == i + 1)continue; // 删去多余的边
      add(i, j);
      add(j, i);
    }
  }
  dfs(1);
  for(int i = 1; i <= s; i++) {
    e[i].clear();
    st[i] = 0;
  }
  for(int i = 0; i <= etot + 1; i++) {
    vis[i] = 0;
    edge[i] = 0;
  }
  etot = 0;
  reverse(ans.begin(), ans.end());
  for(int i = 0; i < n; i++){
    cout << prime[ans[i]] << ' ';
  }
  cout << '\n';
}

bool is_prime[MAXN];

void init(int n = 1e6) { // 筛质数
  memset(is_prime, 1, sizeof is_prime);
  for(int i = 2; i <= n; i++) {
    if(is_prime[i]){
      for(int j = i * 2; j <= n; j += i)is_prime[j] = 0;
    }
  }
  for(int i = 1; i <= n; i++){
    if(is_prime[i]){
      prime.push_back(i);
    }
  }
}

int main(){
  init();
  int T;
  for(cin >> T; T--; solve());
  return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

~~来水一篇题解~~

十分简单的 $2400$。考虑到质数的因子数量相对较少，而且两个数 $a_1,a_2$ 若能表示为 $a_1=p_1p_2,a_2=p_3p_4$ 的形式（$\forall i\in[1,4],p_i\in\text{prime}$），则 $a_1=a_2$ 当且仅当 $\lbrace p_1,p_2\rbrace=\lbrace p_3,p_4\rbrace$。因此考虑二分选前 $m$ 个质数建图，对于任意两个质数都连一条边。然后就是问图上是否存在一个子边集使得这个子边集和点集合起来形成的新图存在欧拉路径，可以使用 Hierholzer Algorithm 求解，时间复杂度为 $O(n\log n)$。

太慢了，能不能优化？考虑更快速的解决合法性问题，即询问 $n$ 个点的完全无向图选取子边集得到的新图的欧拉路径最长的长度，设这个答案为 $F(n)$，那么可以分奇偶讨论，有：

+ 若 $2\nmid n$，则此时每一个点的度数都为 $n-1$，有 $2\mid n-1$，每一个点的度数都为偶数，此时原图就存在欧拉路径。
+ 若 $2\mid n$，则此时每一个点的度数都为奇数。考虑删掉 $n$ 号点和除了 $1$ 号点以外所有点的连边，此时 $1,n$ 两个点的度数为奇数，其余点度数全部为偶数。该新图存在欧拉路径。

计算上述两张图的边数就是 $F(n)$ 的值。

$F(n)$ 显然满足单调性，因此可以二分出最小需要选取前 $m$ 个质数，然后根据上面的方法来构造一张合法的图，跑欧拉路径即可。时间复杂度为 $O(n)$，可以通过。

---

## 作者：AKPC (赞：0)

注意到：

- 当 $a=a',b=b'$ 或 $a=b',b=a'$ 时，$ab=a'b'$，这个显然。
- 当 $a,a',b,b'$ 均为质数时，当且仅当 $a=a',b=b'$ 或 $a=b',b=a'$ 时，$ab=a'b'$。

对于第二点，考虑设 $ab=a'b'=t$，根据唯一分解定理，把 $t$ 拆解后只能是 $a,b$，故 $t$ 的因子为 $1,a,b,t$，而显然 $1,t$ 都不是质数，故 $a=a',b=b'$ 或 $a=b',b=a'$ 成立。

因此考虑把 $a_i$ 全部设为质数，这样肯定是最优的。用一些合数与这些质数做映射可以证明使用合数一定不会更优。

显然，如果使用 $k\in[1,n)$ 种质数作为合法的答案，那么 $k+1$ 也同样可以，故使用数的种类具有单调性，可以考虑二分这个 $k$。

假设现在使用 $k$ 作为答案的数字种类数，那么可以考虑建立 $k$ 个节点，对每两个点都连一条双向边（两个点可以相同，即存在自环）。发现可以考虑找一条路径，使得经过的边不重复（方向相反也不行），顺次经过的点标号即为答案。这其实就是跑一个欧拉路径。

但实际上，在 $k$ 是偶数的时候，建图后每个节点出度为 $k+1$，是奇数，这不满足欧拉路径的性质，故需要删掉一些边。可以考虑删掉 $3\to4,5\to6,\dots,k-1\to k$，这样奇数出度的点只有 $1,2$（保留 $1\to2$ 是保证留下边的数量最多，满足二分条件），从 $1$ 开搜即可。这样无论 $k$ 奇偶都存在欧拉路径。

显然，欧拉路径的长度就是图中边的数量。对于 $k$ 为奇数，边的数量显然是 $\frac{k(k+1)}{2}$；对于偶数，原本边数也是 $\frac{k(k+1)}{2}$，但是由于删掉了 $\frac{k-2}{2}$ 条边，故最终留下的只有 $\frac{k^2+2}{2}$ 条。实际上，通过边的数量即可模拟二分过程，容易证明 $k_1>k_2$ 时 $k_1$ 个节点的边数大于 $k_2$ 的边数，故同样存在单调性。

$\frac{k(k+1)}{2}$ 与 $\frac{k^2+2}{2}$ 均为 $k^2$ 级别，故二分上界不会太大，$10^3$ 左右就行。

[code](/paste/cpptd29h)。

---

## 作者：Yc_cY (赞：0)

要满足 $a_i \times a_j$ 均不相等，显然 $a$ 数组全取质数是最优的，这样不会有 $ 1 \times 6 = 2 \times 3 $ 这样的情况，下证明全取质数可以构造出来。

反过来想，先钦定若干个质数，假设有 $m$ 个，考虑这么多质数最多可以构造出多长的序列，因为是质数，所以各个数对乘积均不相同，考虑对所有 $(i,j)$ 建边，并在图中找一条最长路，最长路的边数加一即为序列的最长长度。

当 $m$ 为奇数，则每个点连了 $m-1$ 条边，为偶数，满足欧拉回路的条件，只要找到一条欧拉路径即可。

当 $m$ 为偶数，则每个点连了奇数条边，显然不能一笔画，考虑删边构造能形成欧拉回路的图，当删除 $(3,4)$ , $(5,6)$ 到 $( m - 1 , m )$ （这里的数字指我们所取的质数在 $m$ 个质数中的排名，如 $(a,b)$ 即指第 $a$ 小的质数与第 $b$ 小的质数之间的边，下同 ）之间的边时，仅 $1$ , $2$ 为奇点，其他均为偶点，满足欧拉路径条件，且显然这样的删边方法删除的边是最少的。

由此可见边数是 $O(m^2)$ 级别的，而 $[1,3 \times 10 ^ 5 ]$ 中有 $10^4$ 级别个质数，显然可以满足 $ 1 \leq n \leq 10^6 $ 的条件，实际上， $1415$ 个质数就够了，于是就做完了。

code:
```cpp
#include<bits/stdc++.h>
#define For( i , a , b ) for( register int i = ( a ) ; i <= ( b ) ; ++i )
#define Rep( i , a , b ) for( register int i = ( a ) ; i >= ( b ) ; --i )
using namespace std ;
const int N = 3e5 + 5 , P = 3e5 , K = 2e4 + 5 , L = 1e6 + 1e5 ;
int T , n , p[ N ] , t[ K ] ;
bool isp[ N ] ;
void pre() {
    For( i , 2 , P ) {
        if( !isp[ i ] ) p[ ++p[ 0 ] ] = i ;
        for( int j = 1 ; j <= p[ 0 ] && p[ j ] * i <= P ; ++j ) {
            isp[ p[ j ] * i ] = 1 ; if( ! i % p[ j ] ) break ;
        }
    }
    For( i , 1 , p[ 0 ] ) {
        if( i % 2 == 1 ) t[ i ] = ( i + i * ( i - 1 ) / 2 ) + 1 ;
        else t[ i ] = i + i * ( i - 1 ) / 2 - ( i / 2 ) + 2 ;
        if( t[ i ] > 1e6 ) { t[ 0 ] = i ; break ; }
    }
}
int ans[ L * 2 ] , top ;
struct edge{
    int to , nxt ;
    bool flag ;
} e[ L * 2 ] ;
int head[ K ] , tot = 1 ;
void add( int u , int v ) {
    e[ ++tot ].to = v ;
    e[ tot ].nxt = head[ u ] ;
    e[ tot ].flag = 0 ;
    head[ u ] = tot ;
}
void dfs( int x ) {
    for( int i = head[ x ] ; i ; i = min( e[ i ].nxt , head[ x ] ) ) {
        if( e[ i ].flag ) continue ;
        e[ i ].flag = 1 ; e[ i ^ 1 ].flag = 1 ; head[ x ] = e[ i ].nxt ;
        dfs( e[ i ].to ) ;
    }
    ans[ ++top ] = x ;
}
void solve() {
    int tmp = lower_bound( t + 1 , t + 1 + t[ 0 ] , n ) - t ;
    For( i , 1 , tmp ) add( i , i ) , add( i , i )  ;
    if( tmp % 2 ) For( i , 1 , tmp ) For( j , i + 1 , tmp ) add( i , j ) , add( j , i ) ;
    else {
        For( i , 1 , tmp ) {
            if( i % 2 ) For( j , i + 1 , tmp ) add( i , j ) , add( j , i ) ;
            else For( j , i + 2 , tmp ) add( i , j ) , add( j , i ) ;
        }
    }
    top = 0 ; dfs( 1 ) ;
    while( n-- ) printf("%d " , p[ ans[ top -- ] ] ) ; puts("") ;
    For( i , 1 , tmp ) head[ i ] = 0 ; tot = 1 ;
}
int main() {
    pre() ;
    scanf("%d" , &T ) ;
    while( T-- ) {
        scanf("%d" , &n ) ;
        solve() ;
    }
    return 0 ;
}
```

---

## 作者：gan1234 (赞：0)

比较好想的一题。

### 分析

首先考虑两个数相乘不同，我们发现两对不同质数相乘一定不同。

所以我们不妨只使用质数来构造数列，这一定比使用其它数更优。

考虑 $m$ 个质数最多能构造出多长的数列。我们将每个质数看成一个点，将两个质数的乘积看作这两个质数的边，题目中构造数列就变成了找到图上一条通路，要求相邻乘积不同的约束变成了一条边只能经过一次。注意每个点都有自环。

我们发现这是欧拉通路，考虑欧拉通路的判定条件。

- 当 $m$ 是奇数时：所有点度数为偶数，因此存在欧拉回路，路径长度就是： $\frac{m(m-1)}{2}+i+1$。加的 $i$ 是自环边。

- 当 $m$ 是偶数时：所有点度数为奇数，但是无所谓，我们可以隔一条边删一条边，删掉 $1-2,3-4,5-6...$ 这 $\frac{m-2}{2}$ 条边，使得只剩下两个点度数为奇数。路径长度：$\frac{m(m-1)}{2}+i+1-\frac{m-2}{2}$。

在求出最少需要的点数后，我们直接在图上跑欧拉通路即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;
int n,cnt;
vector<int>v;
map<int,int>ma;
stack<int>S;
int now[100005];
void dfs(int x){
	for(int &i=now[x];i<cnt;i++)
		if(!ma[v[i]*v[x]]){
			ma[v[i]*v[x]]=1;
			dfs(i);
		}
	S.push(x);
}
void work(){
	cin>>n;
	ma.clear();
	while(!S.empty())S.pop();
	if(n==1){
		cout<<1<<endl;
		return ;
	} 
	for(int i=1;n>=i;i++){
		int t;
		if(i&1)t=(i)*(i-1)/2+1+i;
		else t=i*(i-1)/2-(i-2)/2+1+i;
		if(t>=n){
			cnt=i;
			break;
		}
	}
	for(int i=0;cnt>i;i++)now[i]=0;
	if(cnt%2==0){
		for(int i=2;cnt>i;i+=2)
			ma[v[i]*v[i+1]]=1;
	}
	dfs(0);
	while(!S.empty()&&n){
		n--;
		cout<<v[S.top()]<<" ";
		S.pop();
	}
	cout<<endl;
}
int main(){
	v.push_back(2);
	for(int i=3;3e5>=i;i++){
		int flg=0;
		for(auto y:v){
			if(i%y==0){flg=1;break;}
			if(y*y>i)break;
		}
		if(!flg)v.push_back(i);
	}
	v.push_back(1);
	int _T;
	cin>>_T;
	while(_T--)work();
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

我们发现 $a\times b=b\times a$。

对于 $x\times y=c\times d$ 的情况，发现如果都是质数，除非满足上一个式子，否则一定不成立。

我们可以让答案的数都是质数，这样只需要考虑第一个式子的情况了。

考虑把每种数抽象成节点，节点之间连边，形成完全图。当前在这个节点表示此时序列中最后一个数为这个数，每一次需要跑向其它节点，自环另外特判，跑完后不能同样的情况回去，否则满足一式而导致答案不合法，所以删边，最后要跑 $n-1-m$ 条边，$m$ 表示节点数量，因为有自环，$n-1$ 是因为 $n$ 个数总共有 $n-1$ 对乘积。

这是欧拉路径板子。

于是发现有 $m$ 个节点的完全图最多可以跑 $O(m^2)$ 个边，所以 $m$ 是 $O(\sqrt n)$ 量级的。

枚举 $m$，每次考虑这个 $m$ 加上自环最多可以跑几条边，因为当 $m$ 为偶数时每个点度数均为奇数，所以要删除 $\frac{m}{2}-1$ 条边，所以列方程代码细节会很多。

然后暴力建图即可，边数是 $O(m^2)$ 即 $O(n)$ 级别的。

然后就跑欧拉路径。

最后输出时注意第一次碰到的节点要考虑自环。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
bool v[1000009];
int q[1000009];
int inn;
map<pii,bool> mp;
int h[5009];
struct st{
	int v,ne;
	bool c;
}sd[10000009];
void add(int u,int v){
	sd[++inn].v=v;
	sd[inn].ne=h[u];
	h[u]=inn;
	sd[inn].c=0;
}
int s[10000009];
int t;
void dfs(int u){
	for(int i=h[u]; i; i=h[u]){//小优化，否则超时
		h[u]=sd[i].ne;
		if(!sd[i].c&&!mp[{u,sd[i].v}]&&!mp[{sd[i].v,u}]){
			sd[i].c=1;
			mp[{u,sd[i].v}]=1;mp[{sd[i].v,u}]=1;
			dfs(sd[i].v);
		}
	}
	s[++t]=u;
}
map<int,bool> zzz;
int ans[10000009];
int znn;
map<int,bool> zs;
void _main(){
	znn=0;
	mp.clear();
	inn+=3;
	while(inn--){
		sd[inn]={0,0,0};
	}
	memset(h,0,sizeof(h));
	t+=3;
	while(t--){
		s[t]=0;
	}
	t=0,inn=0;
	int n,nn;
	cin>>n;
	if(n==3){
		cout<<"2 2 3"<<endl;
		return;
	}
	nn=n;
	int m;
	m=1;
	for(int i=1;i<=5005;i++){
		if(i&1){
			if((i*i+i)/2>=n-1){
				m=i;
				break;
			}
		}else{
			if(i*i/2+1>=n-1){
				m=i;
				break;
			}
		}
	}
	
	mp.clear();
	for(int i=1;i<m;i++){
		for(int j=i+1;j<=m;j++){
			if(i!=j&&(m%2||j!=i+1||i%2==0||i==m-1)){
				add(i,j);
				add(j,i);
			}
		}
	}
	dfs(m);
	int p;
	p=0;
	while(n>0){
		cout<<q[s[++p]]<<" ";
		ans[++znn]=q[s[p]];
		n--;
		if(!zzz[q[s[p]]]&&n){
			cout<<q[s[p]]<<" ";
			ans[++znn]=q[s[p]];
			n--;
		}
		zzz[q[s[p]]]=1;
	}
	zzz.clear();
	cout<<endl;
}
signed main(){
	v[1]=1;
	for(int i=2;i<=1000000;i++){
		if(!v[i]){
			q[++inn]=i;
		}
		for(int j=1;j<=inn&&q[j]*i<=1000000;j++){
			v[q[j]*i]=1;
			if(i%q[j]==0){
				break;
			}
		}
	}
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

细节不少，思考只花了 $1$ 小时，我调了 $3.5$ 小时~~掉大分~~，联合 ECR 的差 $7$ 分钟交 D，我已经掉回蓝了~~打回原形~~。

---

## 作者：sunzz3183 (赞：0)

# CF1981D Turtle and Multiplication题解

## 前言

标签：**筛法，欧拉回路**。

~~赛后过的~~，构造一眼秒，欧拉图写错了，多少有点抽象。

## 题意

构造一个长度为 $n$ 的序列 $a$，需要满足：

- $\forall 1 \le i \le n,1 \le a_i \le 3\times10^5$。

- $\forall 1 \le i<j<n,a_i\times a_{i+1}\ne a_j\times a_{j+1}$。

## 分析

发现任意两个质数的乘积是唯一的，而 $\max_{1\le i\le 3\times 10^5}\{d(i)^2\} \le 10^6$。

所以显然只需要选 $m$ 个质数。

而现在就是要构造一个长度为 $n$ 的序列使得每一对无序数对 $\{a_i,a_{i+1}\}$ 都不同。

因为构造方式是从一个数开始，走到另一个数，和**路径**是一样的，所以考虑构造一个无向完全图（带自环），然后找最长路径。

当 $m$ 是奇数时，每个点的度一定是偶数，所以直接跑欧拉回路，序列长度为 $\frac{m\times (m+1)}{2}+1$。

当 $m$ 是偶数，每个点的度一定是奇数，我们可以删除所有形如 $\{3,4\},\{5,6\},\dots,\{n-1,n\}$ 的边，这样就剩下了两个奇点，直接跑欧拉回路，序列长度为 $\frac{m\times (m+1)}{2}-\frac{m-2}{2}+1$。

直接枚举求 $m$ 即可。

## 代码

建图用了 `bitset`。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=3e5+2;
int cnt,prime[N];
bool is_p[N];
void init(int n){
    for(int i=2;i<=n;i++){
        if(!is_p[i])prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            is_p[i*prime[j]]=1;
            if(!(i%prime[j]))break;
        }
    }
}
const int M=1500;
int n,m;
bitset<M>vis[M];
stack<int>st;
void dfs(int u){
    if(vis[u][u])vis[u][u]=0,dfs(u);
    for(int i=vis[u]._Find_first();i<=m;i=vis[u]._Find_first())
        if(vis[u][i])
            vis[u][i]=vis[i][u]=0,dfs(i);
    st.push(prime[u]);//注意要最后加点，不然跑出来的不是欧拉回路，笔者栽在这里了
}
void Main(){
    n=read();
    if(n==1)return puts("1"),void();
    for(m=1;(m*(m+1)/2)-((m&1)?0ll:((m>>1)-1))<n-1;m++);
    for(int i=1;i<=m;i++)
        vis[i].set();
    if(!(m&1))
        for(int i=3;i<=m;i+=2)vis[i][i+1]=vis[i+1][i]=0;
    dfs(1);
    while(!st.empty()&&n)printf("%d ",st.top()),st.pop(),n--;
    while(!st.empty())st.pop();
    puts("");
    return;
}
signed main(){
    init(13000);
    int T=read();
    while(T--)Main();
    return 0;
}
```

---

