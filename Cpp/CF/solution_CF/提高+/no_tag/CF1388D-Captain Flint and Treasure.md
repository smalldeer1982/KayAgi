# Captain Flint and Treasure

## 题目描述

这里有长度为 $n$ 的两个数组 $a$ 和 $b$ 。一开始，答案 $ans$ 等于 $0$ 。现在我们定义如下操作：

- 选择一个位置 $i$ $(1\leq i \leq n)$
- 让 $ans$ 增大 $a_i$
- 如果 $b_i \neq -1 $ 就将 $a_{b_i}$ 增大 $a_i$

如果每一个 $i$ $(1\leq i \leq n)$ 只能选一次，请问 $ans$ 最大是多少？ 并给出 $ans$ 最大时选择 $i$ 的顺序。

## 样例 #1

### 输入

```
3
1 2 3
2 3 -1```

### 输出

```
10
1 2 3```

## 样例 #2

### 输入

```
2
-1 100
2 -1```

### 输出

```
99
2 1```

## 样例 #3

### 输入

```
10
-10 -1 2 2 5 -2 -3 -4 2 -6
-1 -1 2 2 -1 5 5 7 7 9```

### 输出

```
-9
3 5 6 1 9 4 10 7 8 2```

# 题解

## 作者：zhangyaiwei (赞：5)

## 题目简述
给你两个数组 $a$ 和 $b$ ，你要按顺序对每个 $i$ 作如下操作：
1. $ans\rightarrow ans+a_i$
2. $a_{b_i}\rightarrow a_{b_i}+a_i(b_i\not=-1)$
   
求出一种操作顺序使得最终的 $ans$ 最大
## 解法
看到这道题应该就能马上发现，这个 $b_i$ 实际上就可以看成 $i$ 的父节点，于是这道题就变成在一个森林中操作。

注意到，如果 $a_i$ 是非负的，那让 $b_i$ 加上 $a_i$ 后再操作一定不劣，所以我们可以对每棵树 dfs，先操作子节点，再操作父节点。

但是注意到这道题的 $a_i$ 是可能小于 $0$ 的，如果这个点的 $a_i$ 加上子节点给的贡献后，仍然小于 $0$。为了防止操作后使父节点 $a_i$ 减少影响答案，就不能让它现在操作，应该放到最后。

但是放到最后操作也不能随意排序，在 $a_i$ 非负的情况下，我们希望 $a_i$ 对父节点造成贡献，所以从深往浅处理。而对于 $a_i$ 为负的，我们不希望 $a_i$ 对父节点造成影响，所以应该从浅往深操作。

## 代码
最后，放代码

这题代码还是比较好写的

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,Top,a[211111],b[211111];
vector<int> v[211111],anv;
bool t[211111];
int dfs(int rt){
	for(int i=0;i<v[rt].size();i++){
		int sn=v[rt][i];
		a[rt]+=dfs(sn);
	}
	ans+=a[rt];
	if(a[rt]>=0) anv.push_back(rt),t[rt]=1;//只有非负才操作
	return max(a[rt],0ll);
}
void dfs2(int rt){
	if(!t[rt]){
		anv.push_back(rt);
	}
	for(int i=0;i<v[rt].size();i++){
		int sn=v[rt][i];
		dfs2(sn);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(b[i]>0) v[b[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		if(b[i]==-1) dfs(i);
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(b[i]==-1) dfs2(i);
	}
	for(int i=0;i<anv.size();i++){
		cout<<anv[i]<<" ";
	}
}
```

---

## 作者：MyukiyoMekya (赞：3)

第一问求最大 $ans$ ，这个没什么问题直接跑记搜就行了。

麻烦的是第二问，他要求达到这个最优解的操作顺序。

```plain
        -1 -> 100 -> -1 -> 100
edgeid     1      2     3
```

通过反向建边跑记搜可以得出操作后每个点最大的 $a_i$ 为 $-1,99,99,199$

在操作中，我们发现 1 号边会让后面的 100 的值变低，这种边肯定要最后操作

然后 2 号边和 3 号边都是可以让值变大的，所以要按照先 2 号边再 3 号边这样来操作，让增加的值叠加

把能让值变大的操作全部按照顺序输出，这个顺序可以参考拓扑排序

接下来处理那些会让值变小的边

```plain
        -1 -> -1 -> 100
edgeid     1     2  
```

在这里，我们 1 号边和 2 号边都是会让指向的点的值变小的边，我们肯定不能想之前把减少的值叠加了，所以我们跟之前一样，但是用反向拓扑序（或者建反图然后的拓扑序）输出这些操作点

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
using namespace std;
const int MaxN=200050;
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int a[MaxN];
int f[MaxN],n;
vector<int> nxt[MaxN],pre[MaxN];
int deg[MaxN];
bool bad[MaxN];
inline int dfs(int u)
{
	if(~f[u])
		return f[u];
	f[u]=a[u];
	for(int i=0;i<(int)nxt[u].size();++i)
	{
		reg int v=nxt[u][i];
		reg int t=dfs(v);
		if(t>0)
			f[u]+=t,pre[v].push_back(u),++deg[u];//,printf("degup %d\n",u);
		else
			bad[v]=true,pre[u].push_back(v),++deg[v];
	}
	return f[u];
}
signed main(void)
{
	memset(f,-1,sizeof f);
	cin>>n;
	for(int i=1;i<=n;++i)
		read(a[i]);
	for(int i=1;i<=n;++i)
	{
		reg int x;read(x);
		if(x!=-1)
			nxt[x].push_back(i);
	}
	reg int ans=0;
	for(int i=1;i<=n;++i)
		ans+=dfs(i);
	cout<<ans<<endl;
	queue<int> Q;
	for(int i=1;i<=n;++i)
		if(!deg[i]&&!bad[i])
			Q.push(i);
	while(!Q.empty())
	{
		reg int u=Q.front();Q.pop();
		if(bad[u])
			continue;
		printf("%lld ",u);
		for(int i=0;i<(int)pre[u].size();++i)
		{
			reg int v=pre[u][i];
			--deg[v];
			if(!deg[v])
				Q.push(v);
		}
	}
	for(int i=1;i<=n;++i)
		if(!deg[i]&&bad[i])
			Q.push(i);
	while(!Q.empty())
	{
		reg int u=Q.front();Q.pop();
		if(!bad[u])
			continue;
		printf("%lld ",u);
		for(int i=0;i<(int)pre[u].size();++i)
		{
			reg int v=pre[u][i];
			if(!bad[v])
				continue;
			--deg[v];
			if(!deg[v])
				Q.push(v);
		}
	}
	puts("");
	return 0;
}
```

---

## 作者：PanH (赞：2)

## 题意
给出数组 $a$ 和数组 $b$，每次可以指定一个 $i$ ，使：

- $ans$ 加上 $a_i$ ；
- $a_{b_i}$ 加上 $a_i$ ，如果 $b_i=-1$ ，则不执行。

每个 $i$ 只能并必须被指定一次。

求最大的 $ans$ ，并输出取 $i$ 的顺序。

数据保证 $b_{b_{...b_i}}$ 一定以 $-1$ 结尾，即不存在环。

## 题解

按照 $b$ 所给的关系连边，显然形成了一个森林的结构。那么我们可以每棵树分开算。

考虑一个贪心的思路，让每个节点能取到的值尽量大，这个能取到值的记为 $f_i$ 。

因为儿子可以向父亲增加它的 $f_i$。那么只要这个 $f_i$ 是个正数，我们就一定要取。

至于输出方案，可以递归输出。$f_i$ 为正的儿子先遍历，输出当前节点，再遍历$f_i$ 为负的儿子。

code：
```
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
const int N=2e5+5;
struct edge{
	int next,to;
}e[N<<1];
int n,head[N],a[N],cnt,deg[N],rt[N],tot;
long long ans,f[N];
vector<int> fro[N],bac[N];
void add(int u,int v)
{
	e[++cnt]={head[u],v};
	head[u]=cnt;
}
void dfs(int x)
{
	f[x]=a[x];
	for(int i=head[x];i;i=e[i].next)
	{
		int y=e[i].to;
		dfs(y);
		if(f[y]>0)	fro[x].push_back(y),f[x]+=f[y];
		else		bac[x].push_back(y);
	}
	ans+=f[x];
}
void outit(int x)
{
	for(auto y:fro[x])	outit(y);
	printf("%d ",x);
	for(auto y:bac[x])	outit(y);
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)	read(a[i]);
	for(int i=1,to;i<=n;i++)
	{
		read(to);
		if(~to)	add(to,i);
		else	rt[++tot]=i;
	}
	for(int i=1;i<=tot;i++)	dfs(rt[i]);
	printf("%lld\n",ans);
	for(int i=1;i<=tot;i++)	outit(rt[i]);
	return 0;
}
```


---

## 作者：SGColin (赞：2)

每个点最多只有一个指向，无环，这是个森林

假设 `i` 号点在最终累计答案时的取值为 `mx[i]`

对于当前点 `x`, 枚举所有子节点 `son`

最终 `mx[son] > 0` 就将其值加到当前点上 `mx[x] += mx[son]`，反之不加

第一遍 `dfs` 求最优解

第二遍 `dfs2` 输出方案，对于当前点 `x`，先搜 `mx[son] > 0` 的子节点，递归输出他们的编号后，输出 `x` 的编号，再搜其他子节点即可。



```cpp
#include<bits/stdc++.h>
#define N 200007
using namespace std;
typedef long long ll;

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  while (!isdigit(c)) {
    if (c == '-') f = 1;
    c = getchar();
  }
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = getchar();
  }
  return f ? -x : x;
}

int tot, ver[N], hd[N], nxt[N];

inline void add(int fa, int x) {
  ver[++tot] = x;
  nxt[tot] = hd[fa];
  hd[fa] = tot;
}

int a[N], rot[N], totr;

ll ans, mx[N];

void dfs(int x) {
  ll nw = a[x];
  for (int i = hd[x]; i; i = nxt[i]) {
    dfs(ver[i]);
    nw += max(mx[ver[i]], 0ll);
  }
  ans += (mx[x] = nw);
}

void dfs2(int x) {
  for (int i = hd[x]; i; i = nxt[i])
    if (mx[ver[i]] > 0) dfs2(ver[i]);
  printf("%d ", x);
  for (int i = hd[x]; i; i = nxt[i])
    if (mx[ver[i]] <= 0) dfs2(ver[i]);
}

int main() {
  int n = rd(), tmp;
  for (int i = 1; i <= n; ++i) a[i] = rd();
  for (int i = 1; i <= n; ++i) {
    tmp = rd();
    if (tmp > 0) add(tmp, i);
    else rot[++totr] = i;
  }
  for (int i = 1; i <= totr; ++i) dfs(rot[i]);
  printf("%lld\n", ans);
  for (int i = 1; i <= totr; ++i) dfs2(rot[i]);
  return 0;
}
```



---

## 作者：Register_int (赞：1)

将 $(i,b_i)$ 间连边。可以发现每个点出度均为 $1$ 且不存在环，显然是一个森林。

之后可以从下往上贪心，每次遍历一个节点的儿子，并加上所有正贡献，即可算出答案。题目要求输出方案，可以按照 dfs 顺序，正贡献节点从前插入，负贡献从后插入，即可满足要求。复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct node {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], deg[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot, deg[v]++;
}

int n, p[MAXN], x, y; ll ans, a[MAXN];

void dfs(int u) {
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v, dfs(v);
		if (a[v] > 0) a[u] += a[v];
	}
	ans += a[u], (a[u] > 0 ? p[++x] : p[y--]) = u;
}

int main() {
	scanf("%d", &n), y = n;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1, u; i <= n; i++) scanf("%d", &u), ~u && (add(u, i), 0);
	for (int i = 1; i <= n; i++) if (!deg[i]) dfs(i);
	printf("%lld\n", ans);
	for (int i = 1; i <= n; i++) printf("%d ", p[i]);
}
```

---

## 作者：F_Mu (赞：1)

**题意**

给长度为$n$的序列$a[n]$和$b[n]$，初始时$ans=0$,有以下操作：

+ $ans=ans+a[i]$
+ 如果$b[i]\neq-1$，则$a[b[i]]=a[b[i]]+a[i]$

问每个元素操作一次后，$ans$最大为多少，并输出操作序列

**分析**

对于一个数，如果他有前驱的话，可以考虑对于其某些前驱进行操作后再操作该数，那么画一个前驱图可以发现，这是一个拓扑排序的题，操作到某个节点时

+ 如果该节点的值大于$0$，说明将其操作到后续节点一定是更优的
+ 否则，这个节点一定要晚于其后续节点操作，否则会将该节点的值再贡献一次

那么拓扑排序的时候维护一个队列和一个栈，对于值大于$0$的节点，将其放入队列中，然后将其值加入后续节点，否则将其放入栈中（因为若连续两个节点值都小于$0$，那么应先操作后续节点），最后输出即可

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
 
#include <bits/stdc++.h>
 
#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define repd(z, x, y) for(int z=x;z>=y;--z)
#define com bool operator<(const node &b)const
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int maxn = (ll) 3e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
int T = 1;
int a[maxn], b[maxn];
vector<int> v[maxn];
int in[maxn];
 
void solve() {
    int n;
    cin >> n;
    rep(i, 1, n)cin >> a[i];
    rep(i, 1, n) {
        cin >> b[i];
        if (b[i] != -1) {
            v[i].push_back(b[i]);
            ++in[b[i]];
        }
    }
    int ans = 0;
    queue<int> q;
    rep(i, 1, n) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    vector<int> tmp;
    stack<int> last;
    while (!q.empty()) {
        int now = q.front();
        if (a[now] > 0)
            tmp.push_back(now);
        else
            last.push(now);
        ans += a[now];
        q.pop();
        for (auto &to:v[now]) {
            if (a[now] > 0)
                a[to] += a[now];
            --in[to];
            if (in[to] == 0) {
                q.push(to);
            }
        }
    }
    cout << ans << '\n';
    for (auto &to:tmp)cout << to << ' ';
    while (!last.empty()) {
        cout << last.top() << ' ';
        last.pop();
    }
}
 
signed main() {
    start;
    while (T--)
        solve();
    return 0;
}
```



---

## 作者：Zechariah (赞：0)

# 题意
大小为n的数组a和b，1~n按某种排列依次选择，每次将a[i]加到ans中，若b[i]不为-1，则a[b[i]]+=a[i]，问ans最大值以及对应的一种排列。

# 解法
对每一个b[i]直接建有向边i->b[i]，进行拓扑排序。因为没有入度的点值将不再改变。对于值为负数的点，就放在后面，避免减小其他点的值，其余的点就可以直接顺着做。

# AC代码
```cpp
#include <bits/stdc++.h>
#define jh(x, y) x ^= y ^= y ^= x
#define lowbit(x) (x & -x)
#define loc(x, y) (x = 1) * m + y
#define rg register
#define inl inline
typedef long long ll;
const int N = 5e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
ll A[N], B[N], du[N], nt[N], ans[N], lt[N], q[N], head, tail = 1;
void add(int x, int y) {
	nt[x] = y;
	++du[y];
}

int main() {
	ll n = fast_IO::read(), ANS = 0;
	for (rg int i = 1; i <= n; ++i)A[i] = fast_IO::read();
	for (rg int i = 1; i <= n; ++i) {
		B[i] = fast_IO::read();
		if (~B[i])add(i, B[i]);
	}
	for (rg int i = 1; i <= n; ++i)if (du[i] == 0)q[++head] = i;
	while (head >= tail) {
		rg int k = q[tail++];
		if (A[k] < 0)lt[++*lt] = k;
		else {
			ans[++*ans] = k;
			ANS += A[k];
			A[nt[k]] += A[k];
		}
		--du[nt[k]];
		if (du[nt[k]] == 0)q[++head] = nt[k];
	}
	while (*lt)ans[++*ans] = lt[*lt], ANS += A[lt[*lt]], (*lt)--;
	printf("%I64d\n", ANS);
	for (rg int i = 1; i <= n; ++i)printf("%I64d ", ans[i]);
	return 0;
}
```


---

## 作者：白鲟 (赞：0)

## 前言
安利自己首场 CF 的[游记](https://www.luogu.com.cn/blog/PsephurusGladius-zdx/codeforces-round-660-div-2-post)（其实啥也没写）。

## 题目分析
容易发现所有 $b_i$ 表示出的关系会构成一个 DAG。由于我们需要让最后的答案最大，有一个显然的贪心策略：若当前结点权值不为负，则将它的权值累计到它的出边对应的结点上，即让它比它的出边对应的结点均先选择；否则让它后选择。求答案的这一步用拓扑排序就可以解决了。

但是这道题还需要我们输出方案，也就是我们需要知道选择结点的顺序。如上所述，我们可以知道每一条边上两个点选择的先后顺序：若起点为负则先选终点，否则先选起点。考场上我想到的是当某个点为负数时就将它的出边全部逆向。显然，这样做并不会改变它是 DAG 的性质。之后在新图上跑一遍拓扑排序，并使得对于每一条边，满足 $priority_{from}<priority_{to}$。按照 $priority_i$ 从小到大的顺序输出结点即可。

## 代码
```cpp
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
long long n,ans,tot[2],a[200001],b[200001],head[2][200001],go[2][200001],suc[2][200001],degree[2][200001];
queue<long long>que;
struct node
{
	long long no,priority;
}p[200001];
inline bool cmp(const node &t1,const node &t2)
{
	return t1.priority<t2.priority;
}
inline void add_edge(long long opt,long long u,long long v)
{
	go[opt][++tot[opt]]=v;
	suc[opt][tot[opt]]=head[opt][u];
	head[opt][u]=tot[opt];
	++degree[opt][v];
	return;
}
signed main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	for(long long i=1;i<=n;++i)
	{
		scanf("%lld",&b[i]);
		if(b[i]!=-1)
			add_edge(0,i,b[i]);
		p[i].no=i;
	}
	for(long long i=1;i<=n;++i)
		if(!degree[0][i])
			que.push(i);
	while(!que.empty())
	{
		long long front=que.front();
		que.pop();
		ans+=a[front];
		for(long long i=head[0][front];i;i=suc[0][i])
		{
			--degree[0][go[0][i]];
			if(!degree[0][go[0][i]])
				que.push(go[0][i]);
			if(a[front]>=0)
			{
				a[go[0][i]]+=a[front];
				add_edge(1,front,go[0][i]);
			}
			else add_edge(1,go[0][i],front);
		}
	}
	for(long long i=1;i<=n;++i)
		if(!degree[1][i])
			que.push(i);
	while(!que.empty())
	{
		long long front=que.front();
		que.pop();
		for(long long i=head[1][front];i;i=suc[1][i])
		{
			--degree[1][go[1][i]];
			if(!degree[1][go[1][i]])
				que.push(go[1][i]);
			p[go[1][i]].priority=max(p[go[1][i]].priority,p[front].priority+1);
		}
	}
	sort(p+1,p+n+1,cmp);
	printf("%lld\n",ans);
	for(long long i=1;i<=n;++i)
		printf("%lld ",p[i].no);
	return 0;
}
```

---

## 作者：Isshiki_Hugh (赞：0)

是我太菜了，写完比赛刚好结束 ( 1551

这道题的思路不难，我们不难发现选择正数总是比选择负数好，因为负数可能会让别的数更小，而正数可能会让别的数更大，所以我们先把所有的正数点光。那么问题来了，怎么选正数。

我们思考怎样才能让一个正数的贡献最大，那当然是先点最深的。我们这里定义一下深度最大这件事

已知$a_i$可以为$a_{b_i}$做贡献，如果以这个方向建无向图会形成一片森林，但是实际上这些边是有方向的，如果我们按照题目所给的方向建，$a_i$->$a_{b_i}$，那这样根就是没有出度的那个点，然而这样不好处理，因为我们是从根开始遍历整棵树来记忆化深度的，所以我们反向建边，也就是 父节点->子节点 的有向边，表示父节点可以被子节点贡献。

然后我们dfs一遍处理森林里每一个节点在树里的深度就行了。

那为什么要处理这个深度呢，我们思考一下这个树的含义。如果我们从叶子开始选择这些节点，那么这些节点的权值就会向父亲传递，但是按照反方向来，父节点的权值无法向儿子传递。所以对于正权值节点，先处理更深的节点总能让它的贡献最大化。

但是我们需要知道，选择一个正节点以后，父节点可能被子节点更新为正节点，而此时这个正节点的优先级会比某些正节点高。也就是说我们需要按照深度动态维护正节点。不难想到用优先队列维护pair或者结构体实现。

而对于负节点，处理是相反的，我们需要它的贡献尽可能少（减去的越少），也就是负的父节点的优先级高于负的子节点的优先级，同样可以用优先队列维护，不过方向不同

### AC代码
```cpp
#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,a,b) for(register ll i = (a);i <= (b);++i)
#define per(i,a,b) for(register ll i = (a);i >= (b);--i)  
using std::string;using std::cin;using std::cout;
using std::priority_queue;

//pair<dep,num>
priority_queue<std::pair<ll,ll> > a_zheng;
priority_queue<std::pair<ll,ll> > a_fu;

const ll N = 2e5+5;
ll a[N],b[N],ans,p[N],cnt;
ll head[N],next[N],ver[N],tot,dep[N];
inline void link(ll x,ll y){ver[++tot] = y , next[tot] = head[x] , head[x] = tot;}
ll n;
inline void dfs(ll now,ll father){
	dep[now] = dep[father] + 1;
	for(ll i = head[now];i;i = next[i]){
		if(ver[i] == father) continue;
		dfs(ver[i],now);
	}
}

int main(){
	dep[0] = -1 , cnt = 0;
	std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	//freopen("in.in", "r", stdin);
	cin >> n;
	while(a_zheng.size()) a_zheng.pop();
	while(a_fu.size()) a_fu.pop();
	rep(i,1,n) cin >> a[i];
	rep(i,1,n) cin >> b[i];
	rep(i,1,n) dep[i] = 0;
	rep(i,1,n){
		if(b[i] < 0) continue;
		link(b[i],i);
		dep[i] = -1;
	}
	rep(i,1,n){
		if(dep[i] == 0) dfs(i,0);
		else continue;
	}
	rep(i,1,n) if(a[i] >= 0) a_zheng.push(std::make_pair(dep[i],i));
	while(a_zheng.size()){
		std::pair<ll,ll> now = a_zheng.top();a_zheng.pop();
		ans += a[now.second] , a[ b[now.second] ] += a[now.second];
		p[++cnt] = now.second;
		if(a[ b[now.second] ] - a[now.second] < 0 && a[ b[now.second] ] >= 0) a_zheng.push(std::make_pair(dep[ b[now.second] ],b[now.second]));
	}
	rep(i,1,n) if(a[i] < 0) a_fu.push(std::make_pair(-dep[i],i));
	while(a_fu.size()){
		std::pair<ll,ll> now = a_fu.top();a_fu.pop();
		ans += a[now.second] , a[ b[now.second] ] += a[now.second];
		p[++cnt] = now.second;
	}
	cout << ans << "\n";
	rep(i,1,cnt) cout << p[i] << " ";
	cout << "\n";
	return 0;
}
```

---

## 作者：Yuby (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1388D)

#### 翻译有误的问题：

[看这里](https://www.luogu.com.cn/discuss/408280)

#### 题目分析：

注意到 $n \leq 2\times10^5$ 显然需要 $O(n\log n)$ 及以内的算法。

题目中有一点提示：保证不存在环。

这告诉我们这题可以用图论解决。把 $i$ 和 $b_i$ 之间建边，单向边，小于 $n$ 个，有结束点，你想到了什么？这是一片森林。每一次操作相当于把整条链上的点全部加上一个数。不难发现从下往上累加最优，所以直接 dfs 一下即可。

对于 $u$ 如果 $u$ 的子树的值已经都累加到了 $u$ 这个节点，但是 $u$ 的点权还是负数，那么就不去累加这个节点，把它放到最后。这样能保证最优。

答案为最后把所有节点的点权加在一起。

总复杂度：$O(n)$。

代码如下：

[提交记录](https://www.luogu.com.cn/record/69053943)

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define pc putchar
#define fast_iostream ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef double db;
const ld EPS=1e-8;
const ll INF=ll(1e9+7);
const ll LLINF=ll(1e18+7);
const ld LDEPS=1e-18;
const ll MAXN=2e5+7;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline ld dmax(ld x,ld y){return x>y?x:y;}
inline ld dmin(ld x,ld y){return x<y?x:y;}
inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll lcm(ll a,ll b){return a*b/gcd(a,b);}
inline ll lowbit(ll x){return x&(-x);}
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline ld dread(){ld x=0,d=0.1;char f=0,ch=getchar();while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch)) x=x*10+ch-48,ch=getchar();if(ch=='.'){ch=getchar();while(isdigit(ch))x+=d*(ch^48),d*=0.1,ch=getchar();}return f?-x:x;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
ll n,a[MAXN],b[MAXN],ans[MAXN],dfncnt,dfn[MAXN],res=0,ans1[MAXN];
vector<ll>tree[MAXN];
void dfs(ll u,ll fa)
{
	if(u>0)ans[u]=a[u];
	for(ll i=0;i<tree[u].size();i++)
	{
		ll son=tree[u][i];
		if(son==fa)continue;
		dfs(son,u);
		if(ans[son]>0)ans[u]+=ans[son];
	}
	if(ans[u]>0&&u>0)dfn[u]=++dfncnt;
	if(u>0)res+=ans[u];
}
void dfs1(ll u,ll fa)
{
	if(u>0&&!dfn[u])dfn[u]=++dfncnt; 
	for(ll i=0;i<tree[u].size();i++)
	{
		ll son=tree[u][i];
		if(son==fa)continue;
		dfs1(son,u);
	}
}
int main()
{
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++)
	{
		b[i]=read();
		if(b[i]!=-1)tree[b[i]].push_back(i);
		else tree[0].push_back(i);
	}
	dfs(0,-1),dfs1(0,-1);
	write(res),pc(10);
	for(ll i=1;i<=n;i++)ans1[dfn[i]]=i;
	for(ll i=1;i<=n;i++)
	{
		write(ans1[i]);
		pc(32);
	}
	return 0;
}
```



---

