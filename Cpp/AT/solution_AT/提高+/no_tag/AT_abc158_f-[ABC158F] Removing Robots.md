# [ABC158F] Removing Robots

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc158/tasks/abc158_f

数直線上に、$ 1 $ から $ N $ の番号のついた $ N $ 個のロボットが置かれています。ロボット $ i $ は座標 $ X_i $ に存在し、起動すると $ D_i $ だけ正の方向に移動し、移動を終えると同時に数直線上から取り除かれます。全てのロボットの移動速度は同じで、大きさは無視できます。

イタズラ好きの高橋君は、数直線上にロボットが残っている限り、好きなだけ以下の操作を行うことができます。($ 1 $ 回も行わないことも可能です)

- ロボットを $ 1 $ つ選び起動する。移動中のロボットが存在するときは行えない。

ロボット $ i $ が移動する過程で、数直線上の座標 $ X_i $ 以上 $ X_i\ +\ D_i $ 未満の範囲に残っている別のロボット $ j $ と接触したら、ロボット $ j $ も起動されて移動を開始します。この処理は再帰的に繰り返されます。

高橋君が操作を繰り返した後、数直線上に残っているロボットの組み合わせとして考えられるものは何通り存在するでしょうか。答えは非常に大きくなる場合があるので、$ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ -10^9\ \leq\ X_i\ \leq\ 10^9 $
- $ 1\ \leq\ D_i\ \leq\ 10^9 $
- $ X_i\ \neq\ X_j\ (i\ \neq\ j) $
- 入力は全て整数である

### Sample Explanation 1

数直線上に残っているロボットの組み合わせとしては、$ \{1,\ 2\},\ \{1\},\ \{\} $ の $ 3 $ 通りが考えられます。 これらは次のように操作すると実現されます。 - 高橋君はロボットを起動しない。このとき、ロボット $ \{1,\ 2\} $ が残ります。 - 高橋君がロボット $ 1 $ を起動する。このとき、ロボット $ 1 $ が移動する過程でロボット $ 2 $ を起動します。最終的にロボットは $ 1 $ つも残っていません。もしくは、高橋君がロボット $ 2 $ を起動した後ロボット $ 1 $ を起動しても、ロボットが残っていない状態にすることができます。 - 高橋君がロボット $ 2 $ を起動し、操作を終了する。このとき、ロボット $ \{1\} $ が残ります。

### Sample Explanation 2

数直線上に残っているロボットの組み合わせとしては、$ \{1,\ 2,\ 3\},\ \{1,\ 2\},\ \{2\},\ \{2,\ 3\},\ \{\} $ の $ 5 $ 通りが考えられます。

### Sample Explanation 3

どのロボットも他のロボットに影響しません。

### Sample Explanation 4

組み合わせとして考えられるものの個数を $ 998244353 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
2
1 5
3 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3
6 5
-1 10
3 3```

### 输出

```
5```

## 样例 #3

### 输入

```
4
7 10
-10 3
4 3
-4 3```

### 输出

```
16```

## 样例 #4

### 输入

```
20
-8 1
26 4
0 5
9 1
19 4
22 20
28 27
11 8
-3 20
-25 17
10 4
-18 27
24 28
-11 19
2 27
-2 18
-1 12
-24 29
31 29
29 7```

### 输出

```
110```

# 题解

## 作者：Acfboy (赞：8)

觉得 dp 还是比较显然的，肯定得排一个序，然后倒着。因为我们能唯一能确定的状态就是 $n+1$ 这个编号，根本没有机器人，方案只有 $1$。

$f_i$ 表示后 $i$ 个的方案数。显然可以 $f_i = f_{i+1} + f_{next}$, 其中 $next$ 是后面不受影响的。

问题在于后面那个怎么求。 `next` 即后面第一个大于 $x + d - 1$ 的，那不就是单调栈的最基本应用吗？

代码

```cpp
#include <cstdio>
#include <stack>
#include <algorithm>
const int N = 200005, p = 998244353;
int n, f[N];
std::pair<int, int> a[N];
std::stack<std::pair<int, int> > st;
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].first, &a[i].second);
	std::sort(a+1, a+1+n);
	f[n+1] = 1;
	for(int i = n; i >= 1; i--) {
		int t = a[i].first + a[i].second, next = i+1;
		while(!st.empty() && t > a[st.top().first].first) {
			next = st.top().second;
			st.pop();
		}
		st.push({i, next});
		f[i] = (f[i+1] + f[next]) % p;
	}
	printf("%d", f[1]);
}
```	

---

## 作者：_maojun_ (赞：4)

一种奇怪的建模方法。

---

建一个 DAG，$u\rightarrow v$ 表示如果 $u$ 被激活则 $v$ 会激活，然后 DP 求解。然而显然边数是 $n^2$ 级别的。

那么定义 $fa_i$ 表示所有能激活它的点中起始坐标最大的元素，那么这就变成一个森林，然后跑 DP 就行了。

正确性？显然 DAG 的做法是正确的，而如果 $u_1,u_2$ 都能激活 $v$，且 $u_1$ 的起始坐标小于 $u_2$，则因为 $u_2$ 的起始坐标小于 $v$，所以 $u_1$ 必然能激活 $u_2$，继而可以间接地激活 $v$，所以这样正确性是没有问题的。

假设我们建好了森林，那么设 $dp[u]$ 表示以 $u$ 为根的子树激活后结果的方案数。首先激活它则它的子树就全部被激活，共 $1$ 种情况；接下来考虑不激活它的做法，因为所有子树之间是相互独立，所有方案数就是它的所有子树的方案树之积。

即 $dp[u]=1+\prod dp[v]$，其中 $v$ 为 $u$ 的子节点。而答案就是所有森林的根的方案数之积。

那么考虑怎么建图。

```cpp
for(int i=1;i<=n;i++){
	int fa=getfa(i);
	if(fa)Add(fa,i);	// 如果有父亲就建边
	else root[++cnt]=i;	// 没有就说明是某棵树的根
}
```

`fi` 表示开始坐标，`se` 表示可以移动的距离。先按开始坐标排序。

首先能用脑子想到一个 $n^2$ 的建图：

```cpp
int getfa(int x){
	for(int i=x-1;i>=1;i--)		// 从 x-1 开始是因为需要 a[i].fi<=a[x].fi
		if(a[x].fi<=a[i].fi+a[i].se-1)return i;
	return 0;
}
```

然后发现因为 $x$ 从 $1$ 到 $n$ 枚举，所有 `a[x].fi` 是递增的。也就是只要有第一个 $x$ 使得 `a[x].fi>=a[i].fi+a[i].se` 那么后面就一定不会再有可能被作为答案了，直接去掉它。

用链表加速建图，可以优化到 $O(n)$。

```cpp
int getfa(int x){
	for(int i=x-1;i>=1;i=nxt[i])
		if(a[x].fi>=a[i].fi+a[i].se)nxt[pre[i]]=nxt[i],pre[nxt[i]]=pre[i];	// 链表模拟删除
		else return i;
	return 0;
}
```

这里直接从 $x-1$ 开始而不是从 $nxt[x]$ 是因为在此之前不可能删除 $x-1$，所以一定有 $nxt[x]=x-1$。

然后就做完了，瓶颈在排序，复杂度 $O(n\log n)$。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define pi pair<int,int>
#define fi first
#define se second
using namespace std;

typedef long long ll;
const int MAXN=2e5+5,MOD=998244353;
int n,r[MAXN],nxt[MAXN],pre[MAXN];pi a[MAXN];
int tot=0,head[MAXN];
int cnt=0,root[MAXN];
struct Edge{
	int to,nxt;Edge():to(to),nxt(nxt){}
	Edge(int to,int nxt):to(to),nxt(nxt){}
}edge[MAXN<<1];
void Add(int u,int v){edge[++tot]=Edge(v,head[u]);head[u]=tot;}
inline bool cmp(pi x,pi y){return x.fi<y.fi;}
int getfa(int x){
	for(int i=x-1;i>=1;i=nxt[i])
		if(a[x].fi>=a[i].fi+a[i].se)nxt[pre[i]]=nxt[i],pre[nxt[i]]=pre[i];
		else return i;
	return 0;
}

ll dp[MAXN];
void dfs(int u){			// 树形 DP
	dp[u]=1;
	for(int i=head[u],v;i!=0;i=edge[i].nxt){
		v=edge[i].to;if(dp[v])continue;
		dfs(v);
		dp[u]=dp[u]*dp[v]%MOD;
	}dp[u]++;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].fi,&a[i].se);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)nxt[i]=i-1,pre[i]=i+1;
	for(int i=1;i<=n;i++){	// 建图
		int fa=getfa(i);
		if(fa)Add(fa,i);
		else root[++cnt]=i;
	}
	ll mul=1;
	for(int i=1;i<=cnt;i++)dfs(root[i]),mul=mul*dp[root[i]]%MOD;
	printf("%lld\n",mul);
	return 0;
}
```

不过这种写法好像已经有人写了，但貌似我们的建模方式是不一样的。

---

## 作者：Clouder (赞：4)

考虑正难则反，计算出有多少个激活集合。

每一个激活集合会对应一个未激活集合。

然后可以发现，当激活某一个机器人时，会激活它后方的一系列机器人，因此可以考虑把它们缩在一起。

可以简单地用一个动态规划来实现：

定义 $f(i,0)$ 为考虑 $i$ 以后的所有机器人，不激活 $i$ 时的方案数，$f(i,1)$ 为激活 $i$ 时的方案数。

有：

$$f(i,0) = f(i + 1,0) + f(i + 1,1)$$

而激活的话，假定激活 $i$ 后区间 $[i,to(i))$ 都会激活，那么从 $to(i)$ 转移即可。

$$f(i,1) = f(to(i),0) + f(to(i),1)$$

只需要求出 $to(i)$ 就解决了，可以用二分求出 $i$ 点可以直接激活的边界，然后查询区间最值即可。

随便打了个线段树。

```cpp
#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
const int mod = 998244353;
int n, to[maxn], f[maxn][2];
struct node
{
    int pos, d;
} A[maxn];
bool cmp(const node& a, const node& b) { return a.pos < b.pos; }
int maxx[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p) { maxx[p] = std::max(maxx[ls], maxx[rs]); }
void modify(int l, int r, int p, int pos, int k)
{
    if(l == r) return (void)(maxx[p] = k);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos, k);
    else modify(mid + 1, r, rs, pos, k);
    pushup(p);
}
int ask(int l, int r, int p, int ll, int rr)
{
    if (ll > rr) return 0;
    if (l >= ll && r <= rr) return maxx[p];
    int mid = l + r >> 1, res = 0;
    if (ll <= mid) res = ask(l, mid, ls, ll, rr);
    if (rr > mid) res = std::max(res, ask(mid + 1, r, rs, ll, rr));
    return res;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(A[i].pos), read(A[i].d);
    std::sort(A + 1, A + 1 + n, cmp);
    for (int i = n; i; --i)
    {
        int l = i, r = n, mid, ans = 0;
        while (l <= r)
        {
            mid = l + r >> 1;
            if (A[mid].pos < A[i].pos + A[i].d) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        to[i] = std::max(r + 1, ask(1, n, 1, i + 1, ans));
        modify(1, n, 1, i, to[i]);
    }
    f[n + 1][0] = 1;
    for (int i = n; i; --i)
    {
        f[i][0] = (f[i + 1][0] + f[i + 1][1]) % mod;
        f[i][1] = (f[to[i]][0] + f[to[i]][1]) % mod;
    }
    printf("%d\n", (f[1][0] + f[1][1]) % mod);
    return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：3)

可以把这些机器人想成一个 DAG 性结构：如果机器人 $i$ 给启动了，肯定会导致机器人 $j$ 启动，那就连一个 $i$ 往 $j$ 的边。但是这样不仅显然存储不了，但是也很难来从这个结构计算答案。

所以，第一个想法是让 DAG 退化成一棵树。意思就是，如果有三个点 $(a,b,c)$ 满足 $a$ 往 $b$ 有边，$b$ 往 $c$ 有边，和 $a$ 往 $c$ 有边，那可以删除 $a$ 往 $c$ 的边。

怎么保证最终的图是一个有向森林呢？第一个发现，如果 $a$ 往 $b$ 有边，并且 $b$ 往 $c$ 有边，那肯定 $a$ 往 $c$ 或者 $c$ 往 $a$ 有边，应为如果把机器人按位置排序，那 $b$ 在 $a$ 和 $c$ 中间，肯定可以忽略至少一个边在这种情况。

但是如果用上方的方法缩 DAG，太慢了，$O(n^3)$。但是如果需要先构造 DAG 的话，肯定至少 $O(n^2)$，所以必须跳过建立完全 DAG 的步骤。

来直接构造森林，需要先定义一个节点的父亲应该是什么。如果用 DAG 删边完的森林，那一个节点的父亲就是它左方最右边的机器人使得这个机器人启动它本身肯定会启动。应为要求”最左边“这个性质，这样肯定是直接启动，而不是一个机器人碰了另一个机器人才启动它本身。

这样明显可以使用二分查找做，但是比赛时关心最好些的方法。从最右边的机器人往左遍历，并且维护一个小根堆，这个小根堆里元素就是还没有配对一个父亲的机器人。小根堆堆顶应该是最靠左的没配对机器人。遍历到机器人 $i$，把所有堆里它可以直接跑到的机器人 $j$ 父亲设为 $i$ 并且弹出堆，最后在把 $i$ 本身放进堆。

最终遍历完堆里的元素就是这个森林的根。现在问题退化成一个树形 DP：有多少个染色方案，使得每个节点染黑白，并且如果一个节点父亲染黑色，它必须染黑色？

设 $DP[u]$ 为染 $u$ 子树的总共方案。如果节点 $u$ 染黑色，那只有一个方案（所有子树里节点也染黑色），但是如果染白色，那孩子可以随便染。应为孩子的染色是独立选择，染白色的方案数是孩子的 $DP$ 乘积。

$$DP[u]=1+\prod^v_{(u,v)\in E}DP[v]$$

最后答案是所有根 $DP$ 值乘积。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 998244353;

vector<int> elist[200005];
int ans[200005]; bool pin[200005];
vector<pii> rob;
priority_queue<pair<pii, int>, vector<pair<pii, int>>, greater<pair<pii, int>>> pq;

int dfs(int node) {
    ans[node] = 1;
    ll prod = 1;
    for(int& i:elist[node]) prod = prod * dfs(i) % MOD;
    ans[node] += prod;
    if(ans[node] == MOD) ans[node]--;
    return ans[node];
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    rep(i, n) {
        int a, b; cin >> a >> b;
        rob.pb({a, b});
    }
    sort(all(rob));
    for(int i=n-1; i>=0; i--) {
        while(pq.size() && rob[i].fi+rob[i].se > pq.top().fi.fi) {
            elist[i].pb(pq.top().se);
            pin[pq.top().se] = 1;
            pq.pop();
        }
        pq.push({rob[i], i});
    }
    ll res = 1;
    rep(i, n) if(!pin[i]) res = res * dfs(i) % MOD;
    cout << res << endl;
}

```

---

## 作者：Genius_Star (赞：1)

### 思路：

简单题，首先需要按照 $X$ 排序。

然后考虑动态规划，定义 $dp_i$ 表示后 $i$ 个的方案数，$nxt_i$ 表示若激活第 $i$ 个机器人，右边最近的不会被影响激活的机器人编号。

则状态转移方程为：

$$dp_i = dp_{i+1} + dp_{nxt_i}$$

其中 $dp_{i+1}$ 表示不激活的方案数，$dp_{nxt_i}$ 表示激活的方案数。

现在主要是求 $nxt_i$ 的问题。

容易发现这个式子：

$$nxt_i = \max\limits_{j=i+1}^n [X_j \le X_i+D_i] nxt_i$$

可以权值线段树维护区间最大值或者使用单调栈。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
const ll N=2e5+10,mod=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll x,y;
	bool operator<(const Node&rhs)const{
		if(x!=rhs.x)
		  return x<rhs.x;
		return y<rhs.y;
	}
}a[N];
ll n;
ll dp[N];
stack<pair<ll,ll>> S;
int main(){
	n=read();
	for(int i=1;i<=n;i++)
	  a[i]={read(),read()};
	sort(a+1,a+n+1);
	dp[n+1]=1;
	for(int i=n;i>=1;i--){
		ll nxt=i+1;
		while(!S.empty()&&a[S.top().first].x<a[i].x+a[i].y){
			nxt=S.top().second;
			S.pop();
		}
		dp[i]=(dp[i+1]+dp[nxt])%mod;
		S.push({i,nxt});
	}
	write(dp[1]);
	return 0;
}
```

---

## 作者：chenxia25 (赞：1)

大前提：这是一道简单题，难度只有 2000（

> ### [AtC 题目页面传送门]( https://atcoder.jp/contests/abc158/tasks/abc158_f )
>
> 有 $i$ 个机器人，第 $i$ 个坐标为 $x_i$，激活后移动距离为 $d_i$。一开始全未激活，你可以激活若干个，第 $i$ 个激活后，所有坐标在 $[x_i,x_i+d_i)$ 内的机器人都会被激活。问有多少种可能的被激活的机器人集合。答案对 $998244353$ 取模。
>
> $n\in\left[1,2\times10^5\right]$。

首先第一反应是建图，将每个机器人连向它可以激活的所有机器人。但是这样光建图暴力就平方了。然而我们可以用线段树优化。但是建出来图之后要求传递闭包，不可能行。所以必须避开建图这一想法。

那显然，建图不能做那它肯定有特殊性质可以用更简单的方法做。注意到一个显然且有用的性质：将机器人按坐标排序后，每个机器人的传递闭包都是个区间。那我们就可以用类似 DP 的方法求了。

设 $rit_i$ 表示机器人 $i$ 的传递闭包的右端点（左端点显然是 $i$），那么就与 $i$ 和所有的 $rit_j$（$j$ 能被 $i$ 到达）取个 $\max$。又显然，$j$ 组成的也是区间，于是我们可以动态 RMQ。比较傻的方法是线段树，然而 hb 让我们不要养成线段树依赖症。注意到这里是每次相当于在序列开头加一个数，然后查询一次，不难想到 ST 表是可以在开头结尾 push 的，于是写个动态 ST 表可以有效减少码量。

然而还有更 nb 的方法。注意到从右往左递推的过程中，若一个机器人被它左边的机器人算进去了，那么此机器人就再也发挥不了用处了，因为算它进去的机器人已经覆盖它的所有影响效果了。根据这个性质我们可以及时删除无用决策，使用单调栈。具体就是每次算的时候弹出所有栈顶可以转移到的机器人转移，然后 pop 掉，然后再把本机器人 push。这样每个机器人进出一次，线性。

然后就是求出来 $rit$ 之后怎么求答案了。这个就异常简单了，随便 DP 就行了。注意到最终的一种情况一定可以分解成若干个选的区间和不选的区间错落排列，于是 $dp_{i,0/1}$ 表示前 $i$ 个中，第 $i$ 个是选 / 不选的方案数。转移就随便前缀和即可，左端点随便单调栈一下。

总复杂度肯定是线性对数的，无论怎么优化排序还是要排的。

~~由于我比较无聊~~为了稍微练一下不常用的 DS，我把求 $rit$ 的三种方法都写了一遍，代码太长了就只放链接了。

- 线段树： https://atcoder.jp/contests/abc158/submissions/17098557
- ST 表： https://atcoder.jp/contests/abc158/submissions/17098727 
- 单调栈： https://atcoder.jp/contests/abc158/submissions/17099115 

---

## 作者：StayAlone (赞：1)

计算 $to_i$ 表示若激活机器人 $i$，会影响到第几个机器人。

这个事情可以单调栈，或者线段树维护单点修改 + 区间最大值计算。

算完后考虑 dp。设 $f_i$ 表示必须激活某个 $to_j=i$ 的机器人 $j$ 时，激活的不同方案数。转移方程为 $f_{to_{i + 1}}\gets s_i + 1$，其中 $s_i=\sum_{j=1}^i f_j$。加一的原因是可以在 $[1,i]$ 选空集。 

树状数组优化 dp 即可，最后答案就是 $f$ 的前缀和加上空集。时间复杂度 $\mathcal O(n\log n)$。

[AC record](https://www.luogu.com.cn/record/131191526)

```cpp
int n, to[MAXN]; pii a[MAXN];
const int mod = 998244353;
int ans, f[MAXN];

struct setr {
	#define STZ MAXN << 2
	int maa[STZ];
	
	il void pushup(int x) {
		maa[x] = max(maa[ls(x)], maa[rs(x)]);
	}
	
	il void upd(int x, int l, int r, int k, int p) {
		if (l == r) return maa[x] = p, void();
		int mid = l + r >> 1;
		if (k <= mid) upd(ls(x), l, mid, k, p);
		else upd(rs(x), mid + 1, r, k, p);
		pushup(x);
	}
	
	il int query(int x, int l, int r, int ql, int qr) {
		if (l > qr || r < ql) return -inf;
		if (l >= ql && r <= qr) return maa[x];
		int mid = l + r >> 1;
		return max(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
	}
} T;

struct BIT {
	int sum[MAXN];
	
	il void add(int x, int k) {
		while (x <= n) (sum[x] += k) %= mod, x += lowbit(x);
	}
	
	il int query(int x) {
		int s = 1;
		while (x) (s += sum[x]) %= mod, x -= lowbit(x);
		return s;
	}
} T2;

int main() {
	read(n); rer(i, 1, n, a);
	sort(a + 1, a + 1 + n); to[n] = n;
	rep2(i, n - 1, 1) {
		int r = lower_bound(a + 1, a + 1 + n, mp(a[i].fst + a[i].snd, -1)) - a - 1;
		to[i] = max(r, T.query(1, 1, n, i + 1, r)); T.upd(1, 1, n, i, to[i]);
	} f[0] = 1;
	rep1(i, 0, n - 1) {
		int q = T2.query(i);
		(f[to[i + 1]] += q) %= mod, T2.add(to[i + 1], q);
	} printf("%d", T2.query(n));
	rout;
}
```

---

## 作者：AbsMatt (赞：1)

### [题目传送器](https://www.luogu.com.cn/problem/AT_abc158_f)

### [更爽的阅读体验](https://www.luogu.com.cn/blog/yaohaoyou/solution-at-abc158-f)

## 题意
翻译写的很清楚了，这里不做过多的解释。但注意空集也是集合，也就是说最后包含不激活任何一个的情况。

## 做法
考虑 dp。

#### 状态定义
后面的机器人会被前面的所影响，但前面的不会被后面的影响，所以理所应当地选择倒叙遍历。定义 $dp_{i,0}$	 为不选第 $i$ 个机器人时后 $i$ 个机器人的答案，$dp_{i,1}$ 为选择第 $i$ 个机器人时后 $i$ 个机器人的答案。

#### 状态转移
定义 $nxt_i$ 为激活 $i$ 号点后能经过不断激活到达的最远的机器人的编号。特殊的，若激活后不能再激活任意一个机器人时，$nxt_i=i$。所以转移方程为
$$
dp_{i,0}=dp_{i+1,0}+dp_{i+1,1} \\
dp_{i,1}=\begin{cases} dp_{nxt_i,1} & nxt_i \ne i \\ dp_{i,0} & nxt_i = i \end{cases}
$$

#### 初始化
$dp_{n,0}=1$，$dp_{n,1}=1$。用一个 stack 维护 $nxt_i$，细节见代码。

### 总结
时间复杂度为 $O(n)$。记得取模和开 long long，开始要先排序。第一篇题解用的也是 dp，但可以貌似我们的转移和找 nxt 的方法不太一样。
### AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 10, mod = 998244353;
int n, dp[maxn][2];
pair<int, int> a[maxn];
stack<pair<int, int> > s;
signed main()
{
    scanf("%lld", &n);  // 开始了
    for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].first, &a[i].second);
    sort(a + 1, a + n + 1);  // 排序
	// 初始化
    dp[n][0] = 1;
    dp[n][1] = 1;
    s.push({n, n});
    for (int i = n - 1; i; i--)
    {
        int nxt = i, t = a[i].second + a[i].first;  // stack 维护 nxt
        while (!s.empty() && t > a[s.top().first].first)
        {
            nxt = s.top().second;
            s.pop();
        }
        s.push({i, nxt});
		// 转移
        dp[i][0] = (dp[i + 1][0] + dp[i + 1][1]) % mod;
        if (i != nxt)
            dp[i][1] = dp[nxt][1];
        else
            dp[i][1] = dp[i][0];
    }
    printf("%lld", (dp[1][0] + dp[1][1]) % mod);  // 输出
	return 0;
}
```


---

## 作者：__Cby___ (赞：0)

## 思路
一眼动态规划。由于坐标是乱序的，不好处理，肯定得先排序。  
排序后，由于机器人只会干扰到右方的机器人，所以我们要倒着转移。我们设 $dp_i$ 为后 $i$ 个的方案数，$nxt$ 为激活第 $i$ 个机器人最靠左不被激活的。如果激活第 $i$ 个机器人，有 $dp_{nxt}$ 种方案。否则有 $dp_{i+1}$ 种。所以得到转移方程：$dp_i = dp_{i+1} + dp_{nxt}$。  
$nxt$ 可以用单调栈来求解。  
## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
long long int dp[200025];
struct node {
	int a, b;
};
bool operator <(node a, node b) {
	return a.a < b.a;
}
node g[200025];
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> g[i].a >> g[i].b;
	}
	sort(g + 1, g + 1 + n);
	dp[n + 1] = 1;
	stack<node> s;
	for (int i = n; i >= 1; i--) {
		int t = g[i].a + g[i].b, nxt = i + 1;
		while (!s.empty() && g[s.top().a].a < t) {
			nxt = s.top().b;
			s.pop();
		}
		s.push({ i, nxt });
		dp[i] = (dp[i + 1] + dp[nxt]) % 998244353;
	}
	cout << dp[1] << endl;
	return 0;
}
```

---

## 作者：Mirasycle (赞：0)

先找计数基准点，显然为左边第一个激活的机器人。设 $f_i$ 为必须激活左边的第 $i$ 个机器人的方案数，则有
$$ f_i=\sum\limits_{j=k(i)}^{n+1} f_j$$

记 $g_i=\sum\limits_{j=i}^{n+1}f_j$，则有 $f_i=g_j$。答案即为 $g_1$。

现在来解决 $k(i)$ 如何求，$k(i)$ 表示 $i$ 右边第一个不受影响的机器人。大概是这么一个过程：在机器人 $i$ 的覆盖范围内找到一个覆盖范围最广的点 $z$。由于该点的覆盖范围此前已经求出，于是 $k(z) \to k(i)$。
 
这个过程可以通过线段树完成，但是我们也可以发现本质是维护一系列随着位置单调递增，覆盖范围也单调递增的点。于是单调栈就可以了。

---

