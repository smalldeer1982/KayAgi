# Wildflower

## 题目描述

Yousef 有一棵包含 $n$ 个结点，以结点 $1$ 为根的树 $^*$。你打算给 Yousef 一个长度为 $n$ 的数组 $a$，其中每个元素 $a_i$（$1 \le i \le n$）可以是 $1$ 或者 $2$。

我们记结点 $u$ 的子树中所有结点 $v$ 对应的 $a_v$ 之和为 $s_u$。如果这些 $s_u$ 两两不同，即所有的子树权值之和不同，那么 Yousef 会认为这棵树是特别的。

你的任务是帮助 Yousef 统计数组 $a$ 的数目，要求它能使得树是特别的。若存在一个下标 $i$ 使得两个数组 $b$ 和 $c$ 满足 $b_i \neq c_i$，则称 $b$ 和 $c$ 是不同的。

由于答案可能非常大，你需要输出答案模 $10^9+7$ 的结果。

$^*$ 一棵树是一个包含 $n-1$ 条边的无向连通图。

$^\dagger$ 结点 $v$ 的子树是指所有在通往根结点的简单路径上必须经过结点 $v$ 的结点构成的集合。

## 说明/提示

如图是第五个测试用例所对应的树。

## 样例 #1

### 输入

```
7
2
1 2
8
1 2
2 3
3 8
2 4
4 5
5 6
6 7
10
1 2
2 3
3 4
4 5
5 6
4 7
7 8
4 9
9 10
7
1 4
4 2
3 2
3 5
2 6
6 7
7
1 2
2 3
3 4
3 5
4 6
6 7
7
5 7
4 6
1 6
1 3
2 6
6 7
5
3 4
1 2
1 3
2 5```

### 输出

```
4
24
0
16
48
0
4```

# 题解

## 作者：yzjznbQWQ (赞：3)

# CF2117F 题解

[题目传送门](https://codeforces.com/problemset/problem/2117/F)

## 题目大意

给你一颗树，每个节点的权值可以为 $1$ 或 $2$，求对于任意节点其子树权值和均不同的树的个数。

## 思路

不难发现，有解（即答案不为 $0$）的充要条件是叶子节点的个数小于等于 $2$ 个。

那么有解的情况仅有 “|” 形和 “人” 形两种。

- 对于 “|” 形，每个节点的权值没有要求，则答案为 $2^n$。

- 对于 “人” 形，上面的公共部分可以看作 “|” 形，重点在下面的两部分，不妨设两叶子节点的 lca 的深度为 $dep_{lca}$，两叶子节点到 lca 的深度分别为 $dep_{left}$ 和 $dep_{right}$，令 $dep_{left} > dep_{right}$，不妨从叶子节点向上考虑，对于两个叶子其权值仅有两种情况 $1, 2$ 或 $2, 1$，从两个叶子向上的 $dep_{right}$ 个节点，对于叶子为 $1$ 的那条链，仅能填 $2$，对于另一条链亦是如此。则重点在于左侧比右侧多出的那部分，我们再分两种情况考虑：

  - 若该链的叶子为 $1$，则从下往上的第 $dep_{right} + 1$ 个节点仅能填 $2$。那么这部分对答案的贡献为 $2^{dep_{left} - dep_{right} - 1}$。

  - 若该链的叶子为 $2$，则从下往上的第 $dep_{right} + 1$ 个节点并没有限制，那么这部分对答案的贡献为 $2^{dep_{left} - dep_{right}}$。
  
  因此对于这种情况的答案为 $2^{dep_{lca}} \cdot (2^{dep_{left} - dep_{right} - 1} + 2^{dep_{left} - dep_{right}})$。

## 关键代码

```cpp
inline void solve() {
    int n = read(), lca_length = 0;
    vector <int> edge[n + 1], lengths;
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        edge[x].push_back(y); edge[y].push_back(x);
    } edge[1].push_back(0);
    function<void(int, int, int)> dfs = [&](int u, int fa, int length) {
        if (edge[u].size() > 2) lca_length = length;
        bool leaf = true;
        for (int v : edge[u]) {
            if (v != fa) {
                dfs(v, u, length + 1);
                leaf = false;
            }
        }
        if (leaf) lengths.push_back(length); return;
    };
    dfs(1, 0, 1);
    if (lengths.size() > 2) {cout << "0" << '\n'; return;}
    else if (lengths.size() == 1) {cout << qpow(2, n) << '\n'; return;}
    else {
        int tmp = abs(lengths[0] - lengths[1]);
        if (tmp == 0) {cout << qpow(2, lca_length + 1) % MOD << '\n'; return;}
        else cout << (qpow(2, lca_length + tmp - 1) % MOD + qpow(2, lca_length + tmp) % MOD) % MOD << '\n';
    } return;
}
```

---

## 作者：P2441M (赞：2)

下文中用 $sub_u$ 表示以 $u$ 点为根的子树，$dep_u$ 表示 $u$ 到 $1$ 的路径上的节点个数，$sz_u$ 表示 $sub_u$ 的大小。

## 题意

给定一个 $n$ 个点的、以 $1$ 为根的树。求有多少个长度为 $n$ 的序列 $a$，满足：

- 对于 $1\leq i\leq n$，$a_i\in\{1,2\}$。
- 定义 $s_u=\sum_{v\in sub_u}a_v$，则 $s$ 两两不同。

答案对 $10^9+7$ 取模。多测，$1\leq T\leq 10^4$，$2\leq n\leq\sum{n}\leq 2\times 10^5$。

## 题解

首先一个显然的观察是，若这个树有 $>2$ 个叶子节点，则答案必然为 $0$。因为 $s$ 必然包含所有叶子节点的 $a$ 值，如果有 $>2$ 个叶子节点，这些叶子节点的 $a$ 值必然会有重复。

于是我们只需考虑叶子节点个数 $\leq 2$ 的情况。

先来考虑一条链，也就是叶子节点个数 $=1$。因为 $1\leq a_i\leq 2$，所以此时任意的 $a$ 都能满足 $s$ 两两不同的要求，方案数为 $2^n$。

再来考虑有恰好 $2$ 个叶子节点的情况，设它们分别为 $u,v$，令 $d=\operatorname{lca}(u,v)$。不难发现，我们可以拆成两部分：一部分是 $d$ 到 $1$ 的路径，另一部分是 $sub_d$ 除去 $d$ 的部分。显然这两部分之间的计数互不影响，因为只要第二部分是合法的，我们接上第一部分的链也一定是合法的。

第一部分的方案数显然是 $2^{dep_d}$。

对于第二部分，不妨从叶子节点开始考虑，显然必须有 $\{a_u,a_v\}=\{1,2\}$，我们钦定 $a_u=1,a_v=2$。从下往上推：

- 首先 $a_{fa_u}$ 必须填 $2$，否则会有 $s_{fa_u}=s_v=2$，于是 $s_{fa_u}$ 也必须填 $2$。
- 那么 $a_{fa_{fa_u}}$ 也，必须填 $2$，否则会有 $s_{fa_{fa_u}}=s_{fa_v}=4$，于是 $s_{fa_{fa_v}}$ 也必须填 $2$。
- ……

设 $d$ 在 $u$ 方向上的儿子为 $p$，在 $v$ 方向上的儿子为 $q$。

于是如果 $sz_p=sz_q$，那么当叶子确定了之后，只能一路向上填 $2$，方案数就是填叶子的方案数，即为 $2$。

如果 $sz_p\neq sz_q$，钦定 $sz_p<sz_q$。若令 $a_u=1,a_v=2$，则一路向上填了 $sz_p-1$ 个 $2$ 后，$v$ 的部分就没有限制了，方案数为 $2^{sz_q-sz_p}$。若令 $a_u=2,a_v=1$，一路向上填了 $sz_p-1$ 个 $2$ 后，此时 $v$ 部分向上的一个位置不能填 $1$，然后就没有限制了，方案数为 $2^{sz_q-sz_p-1}$。

所以第二部分的总方案数为 $2^{sz_q-sz_p-1}+2^{sz_q-sz_p}$。那么答案就是 $2^{dep_d}(2^{sz_q-sz_p-1}+2^{sz_q-sz_p})$。

时间复杂度 $\mathcal{O}(\sum{n})$。

## 代码

实现时，找到度数最大的点就是 $d$ 了。

```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 5, MOD = 1e9 + 7;

inline int add(int x, int y) { return x += y, x >= MOD ? x - MOD : x; }
inline int sub(int x, int y) { return x -= y, x < 0 ? x + MOD : x; }
inline void cadd(int &x, int y) { x += y, x < MOD || (x -= MOD); }
inline void csub(int &x, int y) { x -= y, x < 0 && (x += MOD); }

int T, n, mx, ans, deg[N], sz[N], dep[N];

struct AdjList {
	int tot, head[N], nxt[N << 1], to[N << 1];
	inline void init() {
		tot = 0;
		for (int i = 1; i <= n; ++i) head[i] = -1;
	}
	inline void ins(int x, int y) { ++deg[y], to[++tot] = y, nxt[tot] = head[x], head[x] = tot; }
} t;

inline int qpow(int a, int b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = (ll)res * a % MOD;
		a = (ll)a * a % MOD;
	}
	return res;
}
inline void dfs(int x, int fx) {
	sz[x] = 1;
	for (int i = t.head[x]; i != -1; i = t.nxt[i]) {
		int y = t.to[i];
		if (y == fx) continue;
		dep[y] = dep[x] + 1;
		dfs(y, x), sz[x] += sz[y];
	}
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> T;
    while (T--) {
    	cin >> n, t.init();
    	for (int i = 1; i <= n; ++i) deg[i] = 0;
    	for (int i = 1, u, v; i < n; ++i) cin >> u >> v, t.ins(u, v), t.ins(v, u);
    	int cnt = 0;
    	for (int i = 2; i <= n; ++i) if (deg[i] == 1) ++cnt;
    	if (cnt > 2) { cout << "0\n"; continue; }
    	if (cnt == 1) cout << qpow(2, n) << '\n';
    	else {
    		dep[1] = 1, dfs(1, 0);
    		int p = 1;
    		for (int i = 2; i <= n; ++i) if (deg[i] == 3) { p = i; break; }
    		ans = qpow(2, dep[p]);
    		int a = n + 1, b = 0;
    		for (int i = t.head[p]; i != -1; i = t.nxt[i]) {
    			int y = t.to[i];
    			if (dep[y] < dep[p]) continue;
    			chk_min(a, sz[y]), chk_max(b, sz[y]);
    		}
    		if (a == b) ans = (ll)ans * 2 % MOD;
    		else ans = (ll)ans * add(qpow(2, b - a - 1), qpow(2, b - a)) % MOD;
    		cout << ans << '\n';
    	}
    }
    return 0;
}
```

---

## 作者：rechess (赞：1)

### 思路
由于要求每个节点的值都不一样且对于叶节点只存在 $1$  $2$ ，两种可能的值，所以最多只能有两个叶节点，所以这棵树要么是一条单链，要么存在唯一一个拥有 $2$ 个子节点的节点;\
如果能满足上述条件，则对于前者，每个节点都有两种选择，所以最后答案是  $2^n$ ;\
对于后者，分裂之前的节点的选法与前者一样，对于分裂后得到的两条链，从两者的最后一个节点开始考虑，我们发现如果其中一者填 $2$ ，那么之后就一直只能填 $2$ 
，同时对于最后一个节点填 $1$ 的链只能一直填 $2$ 
，直到这两条链中的至少一条链填完为止，如果还剩下节点没填，再单独把每个节点的填法相乘即可；

### 代码


```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
#define int long long
const int mod=1e9+7;
int T;

int n;
int pos,idx;

vector<int> q[1000010];

int mi,mx; //mi,mx分别对应两条分裂链中较短的一条与较长的一条

bool flag=true;
int num=0;

void dfs(int u,int dt,int p)
{
    int ct=0;
    bool fg=false;
    
    for(int i=0;i<q[u].size();i++)
    {
        if(q[u][i]==p)continue;
        ct++;
        if(ct>2)flag=false;
        if(ct==2){num++;pos=dt;}
        dfs(q[u][i],dt+1,u);
        fg=true;
    }
    
    if(!fg)
    {
        mi=min(mi,dt);
        mx=max(mx,dt);
    }
}

signed main()
{
    cin>>T;
    while(T--)
    {
        flag=true;
        num=0;
        mi=0x3f3f3f3f,mx=-0x3f3f3f3f;
        int cnt=0;
        bool fg=true;
        cin>>n;
        for(int i=0;i<n+2;i++)q[i].clear();
        for(int i=0;i<n-1;i++)
        {
            int a,b;
            cin>>a>>b;
            q[a].push_back(b);
            q[b].push_back(a);
        }
        
        dfs(1,1,-1);
        
        //flag与num用来排除没有方案的情况，flag用来说明是否有节点拥有大于2个子节点，num用来记录有几个有两个子节点的点
        if(!flag||num>1)
        {
            cout<<0<<endl;
        }
        else if(num==0)
        {
            int res=1;
            for(int i=1;i<=n;i++)
            {
                res=res*2%mod;
            }
            cout<<res<<endl;
        }
        else
        {
            int res=0;
            mi=mi-pos;
            mx=mx-pos;
            int cha=mx-mi;
            if(cha==0)
            {
                res+=2;
            }
            else if(cha==1)
            {
                res+=3;
            }
            else
            {
                int r1=1,r2=1;
                for(int i=1;i<=cha;i++)
                {
                    r1=r1*2%mod;
                }
                for(int i=2;i<=cha;i++)
                {
                    r2=r2*2%mod;
                }
                res=((res+r1)%mod+r2)%mod;
            }
            for(int i=1;i<=pos;i++)
            {
                res=res*2%mod;
            }
            cout<<res<<endl;
        }
    }
    
    return 0;
}
```

---

## 作者：Air2011 (赞：1)

## 题意

给定一棵有根树，你可以在树的节点上写 $1$ 或 $2$。使得任意子树，在子树内节点之和，两两不同，求方案数。

## 分析

显然这棵树最多有两个子节点，否则一定没有方案，因为一共就两种颜色，要给大于两个点染色，无法做到颜色不同。

如果只有一个叶节点，可以任填，答案就是 $2^n$。

如果有两个叶节点，我们画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tsb4lobw.png)

假设叶节点为 $x,y$，其到 LCA 的距离为 $dis_x,dis_y$，$dep_{lca}$ 表示 LCA 节点的深度。

不妨设 $dis_x \ge dis_y$。

当我们给 $x$ 染上 $1$，$y$ 染上 $2$ 时：

我们注意到 $x,y$ 往上至少染 $dis_y$ 个 $2$。

证明：我们当第一个不符的是在 $x$ 处，则显然对应到 $y$ 上，对应节点的儿子的子树和一定等于原节点子树和，当第二个不符的在 $y$ 处，对应的 $x$ 处子树和同样等于原节点子树和，大家可以画个图来理解。

当我们给 $x$ 染上 $2$，$y$ 染上 $1$ 时：

我们只需要一起染色至 LCA（LCA 不染色），同样是染色为颜色 $2$。

那么这样做有一个缺陷，当 $dis_x=dis_y$ 时，$x$ 往上染色就会染色到 LCA 上，这样是不需要的，所以这一类答案就是 $2 \cdot 2^{dep_{lca}}$，式子开头是因为 $x,y$ 可以互换。

当 $dis_x>dis_y$ 时，我们总结一下式子：

![](https://cdn.luogu.com.cn/upload/image_hosting/jsh64jat.png)

两者式子不同是因为两者有一个需要往上多染色一层。

之后在 LCA 以上的节点任意染色，乘起来就做完了。

## 代码

[submission-323720152](https://codeforces.com/contest/2117/submission/323720152)

---

