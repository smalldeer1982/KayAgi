# [USACO24OPEN] Identity Theft P

## 题目背景

**注意：本题的时间限制和内存限制为 3 秒 和 512MB，分别为通常限制的 1.5 倍和 2 倍。**

## 题目描述

Farmer John 的 $N$（$1\le N\le 10^5$）头奶牛每头都有一个二进制字符串（由字符 `0` 和 `1` 组成的字符串）形式的农场证号。Bessie，最年长的奶牛，记住了所有奶牛的农场证号，还喜欢到处询问奶牛她们的农场证号。

当一头奶牛被询问她的农场证号时，她们会开始报正确的二进制字符串，但有可能会感到困惑并在报完之前停下来。当 Bessie 听到该二进制字符串时，如果它不等于农场上任何一头奶牛的农场证号，她就会耸耸肩走开。然而，如果它等于不同于她所询问的奶牛的另一头奶牛的农场证号，那么她就会认为发生了身份盗用并封锁整个农场。注意，这种情况即使当奶牛报出完整的农场证号时也可能发生。

Farmer John 希望防止这种情况发生，并愿意以添加更多二进制位的方式改变奶牛的农场证号。他可以在一秒钟内在任意一头牛的农场证号末尾添加一个二进制位。求出他所需要的最小时间以防止封锁发生。 

## 说明/提示

### 样例解释 1

这一样例满足第一个子任务的性质。

我们可以花费 5 秒使得封锁不可能发生，通过对第一个农场证号添加 `0`，对第二个农场证号添加 `10`，对第三个农场证号添加 `11`，使农场证号变为 `10`，`110` 和 `111`。

你可以证明这不可能在 4 秒或更少的时间内完成。例如，如果你保持所有农场证号不变，则所有 3 头奶牛都具有相同的农场证号 `1`，因此当 Bessie 听到它时，它将始终等于另一头奶牛的农场证号。

作为另一个例子，如果你仅花费 2 秒对第二个农场证号添加 `0`，对第三个农场证号添加 `1`，则农场证号变为 `1`，`10` 和 `11`，因此第二头和第三头奶牛在报她们的农场证号时，可能会停在中间只报出 `1`，而这将等于第一头奶牛的农场证号。

### 样例解释 2

我们可以在 2 秒内使得封锁不可能发生，通过对前两个农场证号添加 `0`，像之前一样使农场证号变为 `10`，`110` 和 `111`。你可以证明这不可能在 1 秒内完成。

### 样例解释 3

我们可以在 4 秒内使得封锁不可能发生，通过对第一个农场证号添加 `00`，对第二个农场证号添加 `01`。你可以证明这不可能在 3 秒或更少的时间内完成。

### 样例解释 5

这一样例满足第一个子任务的性质。

### 测试点性质

- 测试点 $6-7$：所有农场证号的长度均恰好为 $1$。
- 测试点 $8-15$：$N\le 10^2$，且所有农场证号的总长度不超过 $10^3$。
- 测试点 $16-25$：没有额外限制。

## 样例 #1

### 输入

```
3
1
1
1```

### 输出

```
5```

## 样例 #2

### 输入

```
3
1
11
111```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1
1
11```

### 输出

```
4```

## 样例 #4

### 输入

```
5
0
01
0011
010
01```

### 输出

```
6```

## 样例 #5

### 输入

```
14
0
1
1
0
1
0
1
1
1
1
1
0
0
1```

### 输出

```
41```

# 题解

## 作者：NATO (赞：11)

还以为自己铂金组的号被 ban 到铜组了捏。

### 思路浅析：

考虑建 trie。在建树的过程中去操作。

考虑什么情况是合法的。

首先我们知道，任意从根到叶子的路径都代表一个串。其次，如果一个串 $S_a$ 是另一个串 $S_b$ 的前缀，必有 $S_a$ 的终止节点是 $S_b$ 的终止节点的祖先（包括 $S_b$ 的终止节点本身）。

那么容易想到，所有字符串的终止节点都是叶子节点时，操作是合法的。

那么可以想到，当出现冲突的时候我们就是要继续往下走（往这个字符串后面加字符，每走一层就是插入一个字符），将一个儿子不满的节点加上一个儿子，或者是将某个叶子节点置上两个儿子（代表之前在这个叶子节点结束的字符串末尾加一个字符，当前的字符串走到这里时加另一个字符），即可。

每一次我们都可以取局部最优，但我们怎么确保全局最优？简单来说，我们插入的时候可能出现这样的问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/14yywmsi.png)

已经插入 `00`，`01`，`1`。

现在我们再插入一个 `0`，那么由于存在两种最优决策（给 `00` 或 `01` 建两个儿子）它就有可能任选一种决策。而如果我们的决策是给 `00` 建两个儿子，那么我们如果还需要插入一个 `00`，我们会发现之前我们做出的决策就让当前决策变劣。我们并不知道我们当前的决策是否会影响后面的决策，就会错误决策。

因为插入字符串的顺序不影响答案，我们考虑将字符串**按长度从大到小**排序后插入，也可以理解成按原串建树后**自底向上**的递归去做，此时不会出现后效性。就用递归这个等价做法分析一下正确性：

令 $f_u$ 为使 $u$ 子树合法的最小操作数。考虑一个节点 $u$。

1. 如果节点 $u$ 为叶子或空节点，$f_u=0$。

2. 如果节点 $u$ 不是任意一个字符串的终止节点，那么显然不操作（也无法操作）最优：$f_u=f_{lson}+f_{rson}$。

3. 如果节点 $u$ 是某一个字符串的终止节点（暂时不考虑多个相同的串，~~虽然是一样的~~），按前面的思路，我们先将左右子树分别操作到所用操作数最小的合法状态，然后再走到深度最小的空位。如果存在更优的方案，那么就必然是这一步存在着可以走到深度严格不大于当前方案的某个位置的方案。然而深度小的部分都必然是满二叉树，否则我们当前就会到深度小的部分去。如果通过反悔之前的操作让开位置，让开的那个字符串仍然要走下去，不会更优。令 $cost_u$ 为走到深度最小的空位的代价，则 $f_u=f_{lson}+f_{rson}+cost_u$。

分析一下复杂度：

只有当插入字符串结尾子树内的某一层满了的时候，我们的最优决策才需要走到下一层，否则显然在该层结束是严格不劣于在下面的某一层结束的，要卡满层数显然是让 trie 变成满二叉树，而这样显然是 $\log n$ 层的（一个叶子节点对应一个字符串嘛），所以最坏情况下只会往下走 $\log n$ 层，故时间复杂度是 $O(n\log n+\sum\limits_{i=1}^n |s_i|)$ 的，空间复杂度同时间复杂度。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
string s[100005];
ll res;
int cnt,tr[10000005][2],mad[10000005];
bool cmp(string a,string b)
{
	return a.size()>b.size();
}
void add_more(ll now)
{
	++res;
	if(!tr[now][0]&&!tr[now][1])
	{
		res+=2;tr[now][0]=++cnt;mad[cnt]=2;tr[now][1]=++cnt;mad[cnt]=2;
		mad[now]=3;
		return;
	}
	else if(!tr[now][0])
	{
		++res;tr[now][0]=++cnt;mad[cnt]=2;
		mad[now]=min((tr[now][0]?mad[tr[now][0]]:0),(tr[now][1]?mad[tr[now][1]]:0))+1;
		return;
	}
	else if(!tr[now][1])
	{
		++res;tr[now][1]=++cnt;mad[cnt]=2;
		mad[now]=min((tr[now][0]?mad[tr[now][0]]:0),(tr[now][1]?mad[tr[now][1]]:0))+1;
		return;
	}
	else
	{
		if(mad[tr[now][0]]<=mad[tr[now][1]])add_more(tr[now][0]);
		else add_more(tr[now][1]);
		mad[now]=min((tr[now][0]?mad[tr[now][0]]:0),(tr[now][1]?mad[tr[now][1]]:0))+1;
	}
}
void insert(ll now,ll sid,ll nv,bool use)
{
	if(s[sid].size()==nv)
	{
		if(!use)
		add_more(now),--res;
		else mad[now]=2;
		return;
	}
	if(!tr[now][s[sid][nv]-'0'])tr[now][s[sid][nv]-'0']=++cnt,use=1;
	insert(tr[now][s[sid][nv]-'0'],sid,nv+1,use);
	mad[now]=min((tr[now][0]?mad[tr[now][0]]:0),(tr[now][1]?mad[tr[now][1]]:0))+1;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;++i)cin>>s[i];
	sort(s+1,s+1+n,cmp);
	for(ll i=1;i<=n;++i)
	insert(0,i,0,0);
	cout<<res;
}

```

---

## 作者：Graphcity (赞：8)

我们把问题放在 01Trie 上进行讨论。我们在每个串的终止位置放置一个棋子，容易发现每次操作相当于让一个棋子往下走一步。限制成立当且仅当所有棋子都分居在不同的叶子结点。

决策有两种：结点 $x$ 不是叶子时，新开一个分叉，让它的祖先 $y$ 上的一个棋子移到分叉处，代价为 $dep_x-dep_y+1$；结点 $x$ 为叶子结点，此时新开两个分叉，一个存放结点 $x$ 上的棋子，一个让它的祖先 $y$ 上的一个棋子移到那儿，代价为 $dep_x-dep_y+2$。

使用小根堆来存储每种决策对应的代价，并用启发式合并来合并两个堆，就可以做到 $O(\sum_{i=1}^n |s_i|\log n)$ 的时间复杂度。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef pair<int,int> Pair;
const int Maxn=1e6;

int n,ans,tot,t[Maxn+5][2],cnt[Maxn+5],dep[Maxn+5];
priority_queue<Pair,vector<Pair>,greater<Pair>> q[Maxn+5];

inline void Insert()
{
    string s; cin>>s; int p=0; for(auto i:s)
    {
        if(!t[p][i-'0']) t[p][i-'0']=++tot,dep[tot]=dep[p]+1;
        p=t[p][i-'0'];
    } cnt[p]++;
}
inline void dfs(int x)
{
    int a=t[x][0],b=t[x][1];
    if(a) dfs(a); if(b) dfs(b);
    if(!a && !b) q[x].emplace(dep[x]+2,1),cnt[x]--;
    else if(!a || !b) swap(q[x],q[a+b]),q[x].emplace(dep[x]+1,2);
    else
    {
        if(q[a].size()<q[b].size()) swap(a,b);
        swap(q[x],q[a]); while(!q[b].empty())
            q[x].push(q[b].top()),q[b].pop();
    }
    while(cnt[x]--)
    {
        auto [k,id]=q[x].top(); q[x].pop(),ans+=(k-dep[x]);
        if(id==1) q[x].emplace(k+1,1),q[x].emplace(k+1,1);
        else q[x].emplace(k+2,1);
    }
}

int main()
{
    cin>>n; For(i,1,n) Insert();
    dfs(0); cout<<ans<<endl;
    return 0;
}
```

---

## 作者：_Cheems (赞：8)

看到 $01$ 串无脑建 $\rm trie$，尝试放在树上讨论下。

如果在每个串结尾的对应位置上放个点，那么问题等价于：一次操作可以让一个点向下走一步，求使得每个点的子树内不存在其它点的最小操作数。

（后半句又等价于让每个点呆在不同叶子上。）

显然有个贪心：从底向上调整每个点，并把用花费最小的方案将其移到目标位置。

于是维护 $f_u$ 表示当前在 $u$ 上放一个点，需要调整多少次。

边界条件：如果 $u$ 是叶子节点，那么 $f_u=2$；如果 $u$ 上没有点且恰好有一个儿子为空，则 $f_u=1$；

对于一般情况：$f_u=\min(f_{lson},f_{rson})+1$。

然后每次将 $f_u$ 算入答案，并更新 $f$ 的值。更新的话沿着转移路径，找到目标位置，然后向上更新即可。

最后，它为什么是对的？注意到一个点的次优方案始终劣于最优方案，因为向上走一步会使代价都 $+1$。换句话说，如果现在不选最优方案也不会产生更好的贡献，那不如每次选最优。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define lt t[u][0]
#define rt t[u][1]
const int N = 2e6 + 5, inf = 1e9;
int n, len, tot = 1, res, t[N][2], f[N], ed[N];
char ch[N];

inline void upd(int u){
	f[u] = min(f[lt], f[rt]) + 1;
	if((!lt && rt) || (!rt && lt)) f[u] = min(f[u], 1);
	if(!lt && !rt) f[u] = min(f[u], 2);
}
inline void ins(int u){
	if(!lt && !rt) {lt = ++tot, rt = ++tot, f[lt] = f[rt] = 2, upd(u); return ;} 
	if(!lt) {lt = ++tot, f[lt] = 2, upd(u); return ;}
	if(!rt) {rt = ++tot, f[rt] = 2, upd(u); return ;}
	if(f[lt] <= f[rt]) ins(lt);
	else ins(rt);
	upd(u);
}
inline void dfs(int u){
	if(lt) dfs(lt); if(rt) dfs(rt);
	if(ed[u] && !lt && !rt) --ed[u], f[u] = 2;
	else upd(u);
	while(ed[u]--) res += f[u], ins(u);
}
int main(){
	f[0] = inf;
	cin >> n;
	for(int i = 1; i <= n; ++i){
		scanf("%s", ch + 1), len = strlen(ch + 1);
		int u = 1;
		for(int j = 1; j <= len; ++j){
			if(!t[u][ch[j] - '0']) t[u][ch[j] - '0'] = ++tot;
			u = t[u][ch[j] - '0'];
		}
		++ed[u];
	}
	dfs(1);
	cout << res;
	return 0;
}

```

---

## 作者：WorldMachine (赞：4)

怎么只有我是大力做法？

首先在 01-Trie 上考虑，操作就是让一个人往子树里走，需要使得任意两个人不存在祖先后代的关系。

对于点 $u$ 上的人，先保证 $u$ 子树内的其它点都已经合法，那么其余所有人都在叶子上，那么 $u$ 有两种移动方案：

1. 找到子树内一个度数为 $1$ 的点 $v$ 并成为它的儿子，花费 $\text{dep}_v-\text{dep}_u+1$；
2. 找到子树内一个叶节点 $v$，此时上面一定有人，把这个人和 $u$ 上的那个人移到 $v$ 的左右儿子上面去，花费 $\text{dep}_v-\text{dep}_u+2$。

容易发现直接贪心地选择花费较少的 $v$ 是正确的，因为留给祖先用并不会使得答案变优，现在问题就在于如何动态维护如上两种点的信息。

把树拍成 dfs 序，使用线段树维护子树内深度最小的一度点和叶节点及其编号，寻找 $v$ 的时候直接在线段树上面区间查即可。

当发生修改时，会插入一些新的节点，直接维护编号是不可行的，但发现新插入的节点形成的子树内一定只有二度点和叶节点，因此对于每个点 $u$，使用小根堆 $Q_u$ 来维护 $u$ 的新插入的儿子子树中每个可用的叶节点的深度。对于每个叶节点，初始时 $Q_u$ 中仅包含 $\text{dep}_u$ 一个元素；对于非叶节点，初始时 $Q_u$ 为空。

当使用一度点 $v$ 时，将 $v$ 从一度点中移除，并往 $Q_v$ 中插入 $\text{dep}_v+1$；当使用二度点 $v$ 时，实际上使用的是 $Q_v$ 中深度最小的点，设其深度为 $d$，则将 $d$ 弹出，再插入两个 $d+1$。在对 $Q$ 做修改时，同时修改线段树上对应节点的信息。时间复杂度为 $\mathcal O(m\log n)$。

一个点上可能有很多个人，逐个处理即可。注意叶节点要特判，设有 $k$ 个人，那么只有 $k-1$ 个人需要进行如上步骤。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, INF = 1e9;
int n, m, ch[N][2], deg[N], cnt[N], tot = -1, dfn[N], nfd[N], dep[N], mxd[N], ans;
char s[N]; priority_queue<int, vector<int>, greater<int> > Q[N];
void ins() {
	int p = 0;
	for (int i = 0; s[i]; i++) {
		int c = s[i] - '0';
		if (!ch[p][c]) ch[p][c] = ++m, deg[p]++;
		p = ch[p][c];
	}
	cnt[p]++;
}
void dfs(int u, int d) {
	nfd[dfn[u] = ++tot] = u, dep[u] = d;
	for (int i : {0, 1}) if (ch[u][i]) dfs(ch[u][i], d + 1);
	mxd[u] = tot;
	if (!deg[u]) Q[u].push(dep[u]);
}
struct node { int p0, d0, p1, d1; } t[N << 2];
node operator+(node a, node b) {
	if (b.d0 < a.d0) a.p0 = b.p0, a.d0 = b.d0;
	if (b.d1 < a.d1) a.p1 = b.p1, a.d1 = b.d1;
	return a;
}
void build(int p, int l, int r) {
	if (l == r) {
		if (!deg[nfd[l]]) t[p].p0 = l, t[p].d0 = dep[nfd[l]];
		else t[p].p0 = -1, t[p].d0 = INF;
		if (deg[nfd[l]] == 1) t[p].p1 = l, t[p].d1 = dep[nfd[l]];
		else t[p].p1 = -1, t[p].d1 = INF;
		return;
	}
	int mid = l + r >> 1;
	build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
	t[p] = t[p << 1] + t[p << 1 | 1];
}
node qry(int p, int l, int r, int L, int R) {
	if (L <= l && r <= R) return t[p];
	int mid = l + r >> 1;
	if (R <= mid) return qry(p << 1, l, mid, L, R);
	if (L > mid) return qry(p << 1 | 1, mid + 1, r, L, R);
	return qry(p << 1, l, mid, L, R) + qry(p << 1 | 1, mid + 1, r, L, R);
}
void upd1(int p, int l, int r, int x) {
	if (l == r) {
		t[p].p0 = l, t[p].d0 = dep[nfd[l]] + 1;
		t[p].p1 = -1, t[p].d1 = INF;
		Q[nfd[l]].push(dep[nfd[l]] + 1);
		return;
	}
	int mid = l + r >> 1;
	x <= mid ? upd1(p << 1, l, mid, x) : upd1(p << 1 | 1, mid + 1, r, x);
	t[p] = t[p << 1] + t[p << 1 | 1];
}
void upd0(int p, int l, int r, int x) {
	if (l == r) {
		int i = nfd[l], d = Q[i].top(); Q[i].pop();
		Q[i].push(d + 1), Q[i].push(d + 1);
		return t[p].d0 = Q[i].top(), void();
	}
	int mid = l + r >> 1;
	x <= mid ? upd0(p << 1, l, mid, x) : upd0(p << 1 | 1, mid + 1, r, x);
	t[p] = t[p << 1] + t[p << 1 | 1];
}
void Dfs(int u) {
	if (!deg[u]) {
		for (int i = 2; i <= cnt[u]; i++) ans += Q[u].top() - dep[u] + 2, upd0(1, 0, m, dfn[u]);
		return;
	}
	for (int i : {0, 1}) if (ch[u][i]) Dfs(ch[u][i]);
	while (cnt[u]--) {
		node p = qry(1, 0, m, dfn[u], mxd[u]);
		if (p.d1 <= p.d0) ans += p.d1 - dep[u] + 1, upd1(1, 0, m, p.p1);
		else ans += p.d0 - dep[u] + 2, upd0(1, 0, m, p.p0);
	}
}
int main() {
	// freopen("id.in", "r", stdin), freopen("id.out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s, ins();
	dfs(0, 1), build(1, 0, m), Dfs(0);
	cout << ans;
//	while (1);
}
```

---

## 作者：AC_Lover (赞：4)

**简要题意：**

给一些 $01$ 字符串，要在每个字符串末尾添加字符，使得每个字符串都不是其他串的子串，求最少添加的字符数量。

**分析：**

对于多个字符串，考虑先放到Trie上做，那么原题意就是要求每个字符串的对应路径结尾都是一个叶子节点。于是考虑从下到上做，进行调整。

定义 $f_u$ 表示当前情况下，在点 $u$ 处插入一个字符串所需要添加的字符总数。

当 $u$ 为叶子节点时，根据之前的转化，这个叶子节点上已经有一个字符串了，那么现在要添加一个，我们将原来的字符串末尾添加$0$，当前这个字符串末尾添加$1$，将其分配到不同叶子中即可，于是 $f_u=2$。

当 $u$ 一端为空时，我们可以将这个字符串末尾添加空的那个字符，这样就满足了，于是 $f_u=1$。

当 $u$ 两端都非空时，可以选择在一端添加，我们选择代价更小的一端即可，于是 $f_u=\min\set{f_{lc},f_{rc}}+1$。

那么我们从下到上做，对于一个点 $u$，如果其上有字符串且未被分配到叶子节点，那么就将其向下递归插入，插入时按照上述方法更新 $f$，那么每次代价就是 $f_u$，累加就是总共需要添加的字符总数。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
int n;

namespace Trie
{
	const int N=3000010;
	int son[N][2],idx=1;
	int ed[N];
	
	void Insert(string str)
	{
		int p=1;
		for (int i=0;i<str.length();i++)
		{
			int v=str[i]-'0';
			if (!son[p][v]) son[p][v]=++idx;
			p=son[p][v];
		}
		ed[p]++;
	}
	
	int f[N]; //点u处下放一个字符串需要增加的长度
	ll ans=0;
	
	void upd(int u)
	{
		int &lc=son[u][0],&rc=son[u][1];
		if (!lc && !rc) f[u]=2;
		else if (!lc || !rc) { f[u]=1; }
		else { f[u]=min(f[lc],f[rc])+1; }
	}
	
	void put(int &u) { u=++idx,f[u]=2; }
	
	void ins(int u)
	{
		int &lc=son[u][0],&rc=son[u][1];
		if (!lc && !rc)
		{
			put(lc),put(rc);
			upd(u);
			return;
		}
		if (lc && !rc) 
		{
			put(rc);
			upd(u);
			return;
		}
		if (!lc && rc)
		{
			put(lc);
			upd(u);
			return;
		}
		if (f[lc]<=f[rc]) ins(lc);
		else ins(rc);
		upd(u);
	}
	void work(int u)
	{
		int &lc=son[u][0],&rc=son[u][1];
		if (lc) work(lc);
		if (rc) work(rc);
		
		if (!lc && !rc && ed[u]) 
		{
			f[u]=2;
			ed[u]--;
		}
		else upd(u);
		
		while (ed[u]--) 
		{
			ans+=f[u];
			ins(u);
		}
	}
}

int main()
{
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		string s;
		cin >> s;
		Trie::Insert(s);
	}
	Trie::work(1);
	cout << Trie::ans << "\n";
	
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：4)

如果你通关铂金组了，那么你就没有**贝提拔**的机会了。

我觉得这题和金组 T1 一个难度，为什么那题是黄，这题是紫啊？

考虑建 Trie，每一个节点上，如果有多个串或者有儿子，它就必须向下延伸。

考虑两种延伸方法：

1. 分裂叶子节点，代价是深度减去当前节点深度再加 $2$；
2. 插入空节点，代价是深度减去当前深度，然后新增一个叶子节点。

所以在深搜时先往下走，如果没有儿子就创建自己为空节点，否则将儿子创建的节点并进来，如果另一边有空儿子就新建空节点。

如果自己是 $k$ 个字符串的结束位置，就不断找到代价最小的方法，将其使用再修改权值。

将儿子并进来和取出最小值使用可并堆即可，时间 $O(n\log n)$，空间 $O(n)$：
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=(1<<20)+100,_g=3,M=1e9+7,M1=1e9+7,M2=1e9+9;
int T,rt,ct,t[N][2],d[N],v[N];
string s;
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
using ppr=pair<int,int>;
__gnu_pbds::priority_queue<ppr,greater<ppr>,pairing_heap_tag>q1[N];
long long ans;
void dfs(int x){
    int i,y;
    if(t[x][0]||t[x][1]){
        for(i=0;i<2;++i)
            if(y=t[x][i]){
                d[y]=d[x]+1,dfs(y);
                q1[x].join(q1[y]);
            }else q1[x].push({d[x]+1,0});
    }else q1[x].push({d[x],0});
    for(i=1;i<=v[x];++i){
        auto k=q1[x].top();q1[x].pop();
        ans+=(k.first++)-d[x];
        if(k.second)q1[x].push(k);
        else ++k.first,++k.second;
        q1[x].push(k);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z;
    rt=ct=1;
    for(cin>>T;T--;){
        cin>>s,x=1;
        for(char &c:s){
            k=48^c;
            if(!t[x][k])t[x][k]=++ct;
            x=t[x][k];
        }++v[x];
    }dfs(1),printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Genius_Star (赞：3)

智慧题。

### 思路：

看到 01 串和前缀相关，果断建 01Trie。

我们需要使得最终 Trie 树上每个叶子节点到根节点的路径上只有一个 end 标记。

考虑我们一次操作本质是在干什么：即将一个原来在 $u$ 点的 end 标记移动到 $lu$ 或者 $ru$（如果不存在则新建）。

于是容易想到动态规划，即设 $dp_u$ 表示若在 $u$ 处新放一个 end 标记，至少要多少次操作才可以移到叶子上且满足要求；考虑分类讨论：

- 若 $u$ 本身即为叶子，那么 $u$ 处必然原先就有一个 end 标记，于是可以新建 $lu, ru$，将原先的移到 $lu$，新放的移到 $ru$；于是 $dp_u = 2$。

- 若 $u$ 有一个儿子为空，那么可以将其新建出来，然后将 end 标记移到它上面；于是 $dp_u = 1$。

- 否则 end 标记可以推到左边或者右边，于是 $dp_u = min(dp_{lu}, dp_{ru}) + 1$。

然后我们自底向上考虑每个 end 标记，将它使用 $dp_u$ 的代价移下去，然后用它新建的点 $new$ 动态更新 $new$ 到 $u$ 路径上的 $dp$。

这样暴力去更新为什么是对的？你考虑最优策略必然是填满一个满二叉树而不是去再去开下一层，所以树高是 $\log n$ 的。

时间复杂度为 $O(n \log n + \sum |s_i|)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) ch[0][k]
#define rs(k) ch[1][k]
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e6 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll ans;
int n, cnt = 1;
int dp[N], siz[N], ch[2][N];
string s;
inline void insert(){
	int p = 1;
	int len = s.size();
	for(int i = 0; i < len; ++i){
		int c = s[i] - '0';
		if(!ch[c][p])
		  ch[c][p] = ++cnt;
		p = ch[c][p];
	}
	++siz[p];
}
inline void pushup(int k){
	if(!ls(k) && !rs(k))
	  dp[k] = 2;
	else if((!ls(k) && rs(k)) || (ls(k) && !rs(k)))
	  dp[k] = 1;
	else
	  dp[k] = min(dp[ls(k)], dp[rs(k)]) + 1;
}
inline void insert(int u){
	if(!ls(u) && !rs(u)){
		ls(u) = ++cnt;
		rs(u) = ++cnt;
		dp[ls(u)] = dp[rs(u)] = 2;
		pushup(u);
		return ;
	}
	if(!ls(u)){
		ls(u) = ++cnt;
		dp[ls(u)] = 2;
		pushup(u);
		return ;
	}
	if(!rs(u)){
		rs(u) = ++cnt;
		dp[rs(u)] = 2;
		pushup(u);
		return ;
	}
	if(dp[ls(u)] <= dp[rs(u)])
	  insert(ls(u));
	else
	  insert(rs(u));
	pushup(u);
}
inline void work(int u){
	if(ls(u))
	  work(ls(u));
	if(rs(u))
	  work(rs(u));
	if(!ls(u) && !rs(u)){
		--siz[u];
		dp[u] = 2;
	}
	else
	  pushup(u);
	while(siz[u]--){
		ans += dp[u];
		insert(u);
	}
}
bool End;
int main(){
//	freopen("id.in", "r", stdin);
//	freopen("id.out", "w", stdout);
	dp[0] = 1e9;
	n = read();
	for(int i = 1; i <= n; ++i){
		cin >> s;
		insert();
	}
	work(1);
	write(ans);
	//cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：_l_l_ (赞：3)

发现一个超级复杂写法，时间复杂度和空间复杂度均为 $O(n\log_2n)$。

首先把所有人编号放到 01trie 上面，然后变成了花费 $1$ 的代价将一个人所在的节点走到他的任意儿子节点，最小化花费使得任意两人不是祖先关系。

考虑一个人的最优决策一定是找到深度最小的不被其他人覆盖的位置，然后如果走到这个节点经过了其他人，那么这个人就会被挤到另外一个儿子节点。

考虑定义（无限）有序数列 $w_{u}$ 代表，在 $u$ 到根上有若干人要到达这个子树，那么为了使得合法，每增加一人对答案的贡献是多少。由于 01trie 留的空间是非常多的，我们发现这个数列的增长的非常慢，实际上第一个数和第 $10^5$ 个数之间相差不超过 $18$，因此我们可以直接记录数列的第一个数 $w_1$ 以及 $w_1,w_1+1,w_1+2,\cdots,w_1+18$ 分别出现的次数，合并的时候直接对位相加然后保留前 $19$ 个值即可。

遇到了需要移动的点可以直接找到数列的最小值（不必要更新你存储的 $w_1$），具体实现可以看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005, K = 19;
int trie[MAXN][2], cnt[MAXN], tot = 1;
int bas[MAXN]; long long wi[MAXN][K];
long long ans;
void insert(char *str) {
	int n = strlen(str + 1); for (int i = 1, rt = 1; i <= n; i++) {
		int x = str[i] - '0'; if (trie[rt][x] == 0) trie[rt][x] = ++tot;
		rt = trie[rt][x]; if (i == n) cnt[rt]++;
	} ans -= n;
}
void merge(int &bas1, long long *w1, int bas2, const long long *w2) {
	if (bas1 <= bas2) for (int i = bas2 - bas1; i < K; i++) w1[i] += w2[i - bas2 + bas1];
	else for (int i = K - 1; ~i; i--) w1[i] = (i >= bas1 - bas2 ? w1[i - bas1 + bas2] : 0) + w2[i];
	bas1 = min(bas1, bas2);
}
void build(long long *w) {w[0] = 1; for (int i = 2; i < K; i++) w[i] = 1 << (i - 2);}
void merge(int rt, int dep) {
	if (trie[rt][0] == 0 && trie[rt][1] == 0) {
		bas[rt] = dep; build(wi[rt]);
	}
	else if (trie[rt][0] == 0 || trie[rt][1] == 0) {
		int v = trie[rt][0] | trie[rt][1]; merge(v, dep + 1);
		bas[rt] = dep + 1; build(wi[rt]); merge(bas[rt], wi[rt], bas[v], wi[v]);
	}
	else {
		merge(trie[rt][0], dep + 1); merge(trie[rt][1], dep + 1);
		memcpy(wi[rt], wi[trie[rt][0]], sizeof wi[0]); bas[rt] = bas[trie[rt][0]];
		merge(bas[rt], wi[rt], bas[trie[rt][1]], wi[trie[rt][1]]);
	}
	while (cnt[rt]--) for (int i = 0; ; i++) if (wi[rt][i]) {wi[rt][i]--; ans += bas[rt] + i; break;}
}
char str[MAXN];
int main() {
	int n; scanf("%d", &n);
	while (n--) scanf("%s", str + 1), insert(str);
	merge(1, 0); printf("%lld\n", ans);
}
```

---

## 作者：Hanghang (赞：3)

铂金组零的突破！

虽然感觉这场难度不大，但是我分数依旧难崩。

简要题意：$n$ 个 $01$ 串，你可以花费 $1$ 的代价再任意一个串的末尾加上 $0$ 或者 $1$，最小化代价使得任意一个串都不是另一个串的前缀。

这种 $01$ 串最优话问题无脑建字典树，在树上分析往往可以让问题变得简单。

如何让一个串不成为其他串的前缀呢？观察到每个点最终一定会走到某个红色节点的子树上。

![](https://cdn.luogu.com.cn/upload/image_hosting/p3b2zpfe.png)

红色节点分成两类，一类是字典树上的叶子，另一类是一个节点如果只有一个子树，往另一个方向去的新建节点。

我们把贡献拆成两部分，第一部分是一个节点走到某个红色节点需要的代价，第二部分是红色节点内部需要处理的代价。

第一部分是好求的，答案是 $dep_x-dep_p$，$p$ 是一开始的节点，$x$ 是走到红色节点。

第二部分，设 $cnt$ 表示有多少个节点走到了红色节点，因为需要保证一个节点不能是另一个节点的前缀，所以我们还需要在子树内加点。 

![](https://cdn.luogu.com.cn/upload/image_hosting/zog23yu1.png)

大概就是需要构造 $cnt$ 个叶子，代价为每个叶子到根的路径和。

将 $val$ 差分一下即可得到新加一个点所需的代价。
$$
val_i=\begin{cases}
0 & i=1
\\
2 & i=2
\\
val_{\lceil\frac{i}{2}\rceil}+1 & i>2
\end{cases}
$$
注意到随着节点的增加，每增加一个新的点的代价单调不降，因此考虑贪心处理。

对每个红色节点开个小根堆，再记录一个 $now_x$ 表示当前节点已经有了 $x$ 个点。

往小根堆里面插入 $dep_x+val_{now_x+1}$ 表示新增一个点所需的代价。($dep$ 那里使用了差分，在真正的值还需减去个 $dep_p$)。

一个点只能去子树内的红点。所以需要支持子树合并以及删除插入元素的操作。

使用 pb_ds 即可做到 $O(\sum \log \sum)$，常数较小。(不会 pb_ds 的右转可以看[这里](https://www.cnblogs.com/Hanghang007/p/17789124.html))

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/priority_queue.hpp>
#define heap __gnu_pbds::priority_queue

typedef long long ll;
const int N=2e6+3;
int n,tot,ans,cnt[N],now[N],dep[N],val[N],tr[N][2];
bool vis[N];
struct Nod
{
	int x,id;
	friend bool operator <(Nod a,Nod b){return a.x>b.x;}
};
heap<Nod>q[N];
void Ins()
{
	string str;cin>>str;int p=1;
	for(int i=0;i<(int)str.size();i++)
	{
		int c=str[i]-'0';
		if(!tr[p][c])tr[p][c]=++tot;
	    dep[tr[p][c]]=dep[p]+1;p=tr[p][c];
	}
	cnt[p]++;
}
#define ls tr[p][0]
#define rs tr[p][1] 
void Dfs(int p)
{
	if(vis[p]){q[p].push({dep[p]+val[1],p});return;}
	if(!ls&&!rs)
	{
		for(int i=2;i<=cnt[p];i++)ans+=val[i];
		now[p]=cnt[p];q[p].push({dep[p]+val[now[p]+1],p});return;
	}
	Dfs(ls);Dfs(rs);q[p].join(q[ls]);q[p].join(q[rs]);
	while(cnt[p]--)
	{
		Nod t=q[p].top();q[p].pop();ans+=t.x-dep[p];now[t.id]++;
		q[p].push({t.x-val[now[t.id]]+val[now[t.id]+1],t.id}); 
	}
}
int main()
{
	cin>>n;tot=1;val[2]=2;
	for(int i=3;i<N;i++)val[i]=val[(i+1)/2]+1;
	for(int i=1;i<=n;i++)Ins();
	for(int p=1;p<=tot;p++)if((!ls&&rs)||(ls&&!rs))
		!ls?ls=++tot:rs=++tot,dep[tot]=dep[p]+1,vis[tot]=1;
	Dfs(1);cout<<ans;
}
```

---

## 作者：rainygame (赞：2)

模拟赛半小时会了紫，但是挂成 24 了。/kk

看到这个又有前缀又有 `01` 串，肯定先上 01-Trie 考虑！假设要加入第 $i$ 个串，前 $i-1$ 个串（拓展完的）已经加入了 01-Trie，那么就先往下走完原本的 `01` 串，如果这个时候到了一个没有串到过的结点，那么就说明它不是任何一个串的前缀，可以不用管了，否则需要继续往下直到“开辟”了一个新的结点。

那怎么往下走呢？目标肯定是找到一个“有一个儿子为空”的结点，然后“开辟”它的一个新儿子。如果已经求出了左右子树分别需要走多少步才能走到这种结点，那么直接往少的那边走就行了。实际也确实如此，需要对每个结点记录一个 $f_u$ 表示 $u$ 子树的叶子到 $u$ 的距离最小值，等走完了再重新更新所有祖先的 $f$（$f_u=\min\{f_{ls},f_{rs}\}+1$），复杂度不变。

但是要考虑一种情况，如果走到了本来就有串结束的位置，该怎么办？首先这个位置一定是叶子，其次此时两个串都不能呆在这个结点了，所以解法是直接给这个叶子加上左右儿子，分别让两个串终止在两个位置上。因为这时它的代价的 $2$（将两个串的长度都加一），所以这种叶子 $f_u=2$。

最后还有一种情况，就是可能一个串走完没有扩展的部分就已经开辟了新的结点，但这时前面还有一些结点是它的前缀。我懒得处理这个，所以在插入之前直接按照长度排序就可以不处理这个了。

最后关于复杂度，注意到一个串继续往下走当且仅当它前面都满儿子了且其兄弟的最小深度比它大，画一下图就会发现此时令一颗子树一定比它大，所以按照启发式合并的思路，容易证明复杂度是 $O(\sum\lvert S\rvert \log \sum\lvert S\rvert)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 20000005

int n, ans;
string s[100005];

namespace Trie{
    set<int> st; int ct; struct Node{int t[2], dmn, fa;}tr[MAXN];
    void ins(string s){
        int p(0), las(ct);
        for (auto i: s){
            if (!tr[p].t[i-'0']) tr[tr[p].t[i-'0']=++ct].fa = p, tr[ct].dmn = 1; p = tr[p].t[i-'0'];
        }
        while (las == ct){
            int lst(tr[tr[p].t[0]].dmn < tr[tr[p].t[1]].dmn ? tr[p].t[0] : tr[p].t[1]);
            if (!lst) tr[lst=++ct].fa = p, tr[lst].dmn = 1; tr[p].t[tr[tr[p].t[0]].dmn>=tr[tr[p].t[1]].dmn] = lst; p = lst; ++ans;
        }
        st.insert(p); tr[p].dmn = 2;
        if (st.count(tr[p].fa)){
            ++ans; st.erase(tr[p].fa); st.insert(tr[tr[p].fa].t[p==tr[tr[p].fa].t[0]]=++ct); tr[ct].dmn = 2;
            tr[ct].fa = tr[p].fa;
        }
        for (p=tr[p].fa; p; p=tr[p].fa){
            tr[p].dmn = min(tr[tr[p].t[0]].dmn, tr[tr[p].t[1]].dmn)+1;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n; for (int i(1); i<=n; ++i) cin >> s[i];
    sort(s+1, s+n+1, [](string s, string t){return s.size() > t.size();});
    for (int i(1); i<=n; ++i) Trie::ins(s[i]); cout << ans;

    return 0;
}

```

---

## 作者：wYYSZLwSSY (赞：2)

好题，妙题。

因为我很菜，所以题解可能有点啰嗦。
## 题解
给定字符串是最终字符串的前缀，而且判定条件与前缀有关，所以考虑放到 trie 树上。

考虑怎样的 trie 树是符合条件的，显然，需要 trie 树没有不再叶子上的串的结尾，而且一个叶子上只能有一个串的结尾。

加字符的操作其实就是就是把串的结尾向下“推”，“推”到一个空的叶子结点（也就是说之前没有串在这里），需要的步数是深度之差。

关键在于新建空的叶子节点，具体有两种方法：

- 将一个叶子分成两个（把它的两个儿子建出来），一个存放这个叶子上的串结尾，另一个形成空的叶子。
- 将一个仅有一个儿子的节点的“空位”变成一个空的叶子。

这两个方法构建出叶子后填数的操作数为：叶子深度+$1$-结尾节点深度+$1$ 和 叶子深度+$1$-结尾深度。

具体应该怎么做呢？考虑先解决层数深的。因为串的结尾不能被“推”上去。

最先解决的是叶子节点，叶子节点首先会用第一种方法创造一个深度为叶子深度+$1$ 的空叶子（假设这个叶子已经填上东西）。这个位置被填之后会形成两个叶子（一个是新添入的，一个是原来叶子节点被“推”下去的），这两个叶子也成为候选。可以把它们扔到优先队列里面。不断这样填，然后填完原来在这个叶子上的所有东西。

之后处理它的父亲，它的父亲会继承它候选位置组成的优先队列，假设父亲有一个空位，就可以放进优先队列里面。当这个空位拿出来的时候，它会产生一个空叶子，把这个空叶子用上面的方法放进优先队列里面。如果取出的是叶子，就按之前说过的方法。

具体地看代码吧：

## 代码
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long 
using namespace std;
int n,a[1000006];
int pos[1000006][2],rt,cnt;
int ans,deep[1000006];
string s;
void add(string s){
	int len=s.size(),tp=rt;
	for(int i=0;i<len;++i){
		if(pos[tp][s[i]-'0'])tp=pos[tp][s[i]-'0'];
		else{
			pos[tp][s[i]-'0']=++cnt;
			tp=cnt;
		}
	}
	++a[tp];
	return ;
}
__gnu_pbds::priority_queue<pair<int,bool>,greater<pair<int,bool> > >dl[1000006];//pair 中的 int 表示空位的深度，bool 表示产生空位的是一个叶子还是一个只有一个儿子的节点，1 表示是叶子。
void dfs(int x,int fa){
	deep[x]=deep[fa]+1;
	if(pos[x][1] or pos[x][0])for(int i:{0,1}){
		if(pos[x][i]){
			dfs(pos[x][i],x);
			dl[x].join(dl[pos[x][i]]);
		}else dl[x].push({deep[x]+1,0});//deep[x] 有空位
	}else {
		--a[x];
		dl[x].push({deep[x]+2,1});//空位的深度是 deep[x]+1，但是还要动用一步来把原来在叶子上的结尾“推”下去，方便排序写成 deep[x]+2
	}
	for(int i=1;i<=a[x];++i){
		auto tp=dl[x].top();dl[x].pop();
		ans+=tp.first-deep[x];
		++tp.first;
		if(!tp.second)++tp.first,tp.second=1;//空位从单儿子变成叶子
		else dl[x].push(tp);//叶子要产生两个空位，所以要再写一个
		dl[x].push(tp);
	}
	return ;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
// 	freopen("1.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>s;
		add(s);
	}
	dfs(rt,0);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Filberte (赞：1)

看到二进制，再看到前缀，不难想到 0-1 trie，在树上解决此题。题意转化为给定一棵二叉树，有一些点上有标记，每次可以把一个标记把一个标记下移到其儿子节点，要使得任意一个标记所在子树内只存在它自己这个标记的最小次数。

这类问题无非就是贪心或者动态规划，贪心比较好想（也比较好写），先考虑贪心。手玩一下发现自底向上把每个标记放到合法的位置，这个策略肯定是最优的。

维护一个数组 $f_u$ 表示目前已有的标记都放好了，若再往 $u$ 放一个标记，最少需要多少操作可以把它变成合法状态。这棵树中，所有叶节点必然都是已经有标记的，否则创建这个无标记的叶节点没有任何意义。所以若 $u$ 为叶节点，则 $f_u = 2$，把本来有的标记和新的标记分别移到左儿子和右儿子即可。若 $u$ 只有左儿子或右儿子，那么直接把当前比较移动到空的那一侧即可，$f_u = 1$。剩下的情况，说明这个点左子树和右子树都有标记了，那么往哪一侧下移就取决于哪一侧操作数少， $f_u = \min(f_{lc},f_{rc}) + 1$。

先把字典树建出来，在树上处理标记。到达一个节点，应该先处理其儿子的标记。若当前点 $u$ 有标记，先用 $f_u$ 更新答案，再维护 $f_u$ 即可。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 100; 
const int inf = 1e9;
int n, cnod = 1, res, ch[N][2];
int f[N], ed[N];
void upd(int u){
    f[u] = min(f[ch[u][0]], f[ch[u][1]]) + 1;
	if((!ch[u][0] && ch[u][1]) || (!ch[u][1] && ch[u][0])) f[u] = min(f[u], 1);
	if(!ch[u][0] && !ch[u][1]) f[u] = min(f[u], 2);
}
inline void add(int u){
	if(!ch[u][0] && !ch[u][1]){
        ch[u][0] = ++cnod, ch[u][1] = ++cnod;
        f[ch[u][0]] = f[ch[u][1]] = 2;
        upd(u);
        return ;
    } 
	if(!ch[u][0]){
        ch[u][0] = ++cnod;
        f[ch[u][0]] = 2;
        upd(u);
        return ;
    }
    if(!ch[u][1]){
        ch[u][1] = ++cnod;
        f[ch[u][1]] = 2;
        upd(u);
        return ;
    }
	if(f[ch[u][0]] <= f[ch[u][1]]) add(ch[u][0]);
	else add(ch[u][1]);
	upd(u);
}
inline void dfs(int u){
	if(ch[u][0]) dfs(ch[u][0]);
    if(ch[u][1]) dfs(ch[u][1]);
	if(ed[u] && !ch[u][0] && !ch[u][1]) ed[u]--;
	upd(u);
	for(int _t = 1;_t <= ed[u];_t++) res += f[u], add(u);
}
char s[N];
void ins(){
    int len = strlen(s + 1);
    int u = 1;
    for(int j = 1; j <= len; ++j){
        int v = s[j] - '0';
        if(!ch[u][v]) ch[u][v] = ++cnod;
        u = ch[u][v];
    }
    ++ed[u];
}
int main(){
    scanf("%d",&n);
	for(int i = 1; i <= n; ++i){
		scanf("%s", s + 1);
        ins();
	}
    f[0] = inf;
	dfs(1);
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：huhaoming2011 (赞：1)

## 题目大意
给你 $n$ 个字符串，然后让你在每个字符串后增加字符，使得任意字符串的前缀不与其他字符串相同，每增加一个字符代价为 $1$。

问最小的代价是多少。

## 分析

其实这道题目并没有想象中的那么难。

第一眼看到题目，根据感觉，先建一棵字典树。

然后，我们手玩一下样例，就会发现，这是很明显的贪心。因为想要让其前缀不同，就要保证从根到叶子结点的路径上只有一个结尾的标记，假设在这个路径上有多余的叶子结点，它的必会选择往下延伸成一个叶子结点。

有以下几种情况：
1. 当前多余的结尾标记处为叶子结点，则它需要左右分叉以保证不同，其贡献为二。
2. 当前多余的结尾标记处只有一个儿子，则可以向没有儿子处延伸，其贡献为一。
3. 当前多余的结尾标记处有两个儿子，则其贡献为左右儿子处的最小贡献加一。

发现如上贪心，发现可以进行转移，转移显而易见，直接按贪心来即可。从叶子结点往根处理，每遇到一个标记就处理一次，同时延伸字典树。

最后的时间复杂度为 $O(nV)$，其中 $v$ 为字符串长度。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 100;
const int M = 1e6 + 100;

int n, f[N], ans;
char s[M];

//f[i]表示Trie上节点i处如果要延伸的最小代价

struct Trie
{
	int tr[N][2], end[N], len;
	
	void insert(int l)
	{
		int op = 0;
		for(int i = 1; i <= l; ++i)
		{
			int c = s[i] - '0';
			if(!tr[op][c])
				tr[op][c] = ++len;
			op = tr[op][c];
		}
		++end[op];
		return ;
	}

	void get(int x)
	{
		if(!tr[x][0] and !tr[x][1])
			f[x] = 2;
		else if((!tr[x][0] and tr[x][1]) or (!tr[x][1] and tr[x][0]))
			f[x] = 1;
		else
			f[x] = min(f[tr[x][0]], f[tr[x][1]]) + 1;
		return ;
	}

	void update(int x)
	{
		if(!tr[x][0] and !tr[x][1])
		{
			tr[x][0] = ++len;
			tr[x][1] = ++len;
			f[tr[x][0]] = f[tr[x][1]] = 2;
		}
		else if(!tr[x][0])
		{
			tr[x][0] = ++len;
			f[tr[x][0]] = 2;
		}
		else if(!tr[x][1])
		{
			tr[x][1] = ++len;
			f[tr[x][1]] = 2;
		}
		else
		{
			if(f[tr[x][0]] > f[tr[x][1]])
				update(tr[x][1]);
			else 
				update(tr[x][0]);
		}
		get(x);
//每次更新一次f[x]
		return ;
	}

	void dfs(int x)
	{
		if(tr[x][0])
			dfs(tr[x][0]);
		if(tr[x][1])
			dfs(tr[x][1]);
		if(end[x] and !tr[x][0] and !tr[x][1])
		{
//对原来的叶子结点特殊处理，不然会统计上其贡献
			f[x] = 2;
			--end[x];
		}
		else
			get(x);
		while(end[x])
		{
			ans += f[x];
			update(x);
			--end[x];
		}
		return ;
	}
}t;

int main()
{
	
	scanf("%d", &n);

	char ch = getchar();

	for(int i = 1; i <= n; ++i)
	{
		int l = 0;
		while(ch < '0' or ch > '1') ch = getchar();
		while(ch == '0' or ch == '1')
		{
			s[++l] = ch;
			ch = getchar();
		}
		t.insert(l);
	}
	t.dfs(0);
	printf("%d", ans);
	return 0;
}
```
谢谢观看

---

## 作者：Red_river (赞：1)

### 题目大意
给你一个 $N$ 及 $N$ 个字符串。~~在一开始时我甚至差点没明白题意~~。但其实题意很简单，这头奶牛呢，就是去问别人号码，别人有可能断开也有可能说完。但只要断开或说完的话要是与这头奶牛已经询问过了的奶牛相同，即有相同的前缀的话，就会把农场给引爆。自然农场主不想发生这种事。于是我们可以通过加上字符改变，使其前缀不等。

一句话题意：有 $N$ 个字符串，你可以在其后面填上字符，使任意两个字符串不等。这头奶牛问完后如果没奶牛符合的话，就会**更新这个人的信息**。即为：即使它断开，奶牛在问完后也会知道他的**完整消息**。
### 题意分析
具体的思想就是一道在 `Trie` 树上的贪心。于是题目简化为：求给定字符串集合中的一个字符串，使得它不是任何其他字符串的前缀的最短长度。

解题思路：

构建一个 `Trie` 树，将所有的字符串插入到 `Trie` 树中。遍历每个字符串，从根节点开始向下查找，直到遇到一个叶子节点，表示该节点是唯一的前缀，停止遍历。记录最短长度，即为所有唯一前缀的节点的深度之和。复杂度分析：

1. 构建 `Trie` 树的时间复杂度为 $O(NK)$ 其中 $N$ 为字符串数量而 $K$ 为字符串的平均长度。
1. 遍历每个字符串的时间复杂度为 $O(N)$ 而其中 $N$ 为字符串数量。
1. 总时间复杂度为 $O(NK)$ 的。

具体实现可以参考代码和注释。
### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define N 2000005
#define ru(x) gpt[x][1]
#define lu(x) gpt[x][0]
#define ll long long
#define ri register int
#define INF 1e9
using namespace std;
int n,m,u,jk,ans,sum,num,cnt,tot;
int dis[N],f[N],gpt[N][3];
char a[N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

void update(int x){//下发标记。
	f[x]=min(f[lu(x)],f[ru(x)])+1;
	if((!lu(x)&&ru(x))||(!ru(x)&&lu(x))) f[x]=min(f[x],1);
	if(!lu(x)&&!ru(x)) f[x]=min(f[x],2);
}

void got(int x){//枚举
	if(!lu(x)&&!ru(x)){
		lu(x)=++tot,ru(x)=++tot;
		f[lu(x)]=f[ru(x)]=2,update(x);
		return;
	} 
	if(!lu(x)){
		lu(x)=++tot,f[lu(x)]=2;
		update(x);return;
	}
	if(!ru(x)){
		ru(x)=++tot,f[ru(x)]=2;
		update(x);return;
	}
	if(f[lu(x)]<=f[ru(x)]) got(lu(x));
	else got(ru(x));update(x);
}

void dfs(int x){//枚举字符。
	if(lu(x)) dfs(lu(x));if(ru(x)) dfs(ru(x));
	if(dis[x]&&(!lu(x)&&!ru(x))) --dis[x],f[x]=2;//都为空，则代价就是二，否则为一或儿子值加一。
	else update(x);while(dis[x]--) ans+=f[x],got(x);return;
}

signed main()
{
//	freopen("theft.in","r",stdin);
//	freopen("theft.out","w",stdout);
	read(n);f[0]=INF;tot=1;
	for(int i=1;i<=n;i++){
		scanf("%s",a+1);
		u=1;m=strlen(a+1);
		for(int j=1;j<=m;j++){//建立字典树。
			if(!gpt[u][a[j]-'0']) gpt[u][a[j]-'0']=++tot;
			u=gpt[u][a[j]-'0'];
		}
		dis[u]++;//节点的字符串个数（即相同的个数）。
	}
	dfs(1);wh(ans);
	return 0;
}
```

---

## 作者：山田リョウ (赞：1)

## [「USACO 2024 US Open Platinum」Identity Theft](https://www.luogu.com.cn/problem/P10283)

### 题意：

给定 $n$ 个 $01$ 串 $s_1,s_2,\cdots,s_n$，求最少添加几个 $0/1$ 字符能使其任意两个 $01$ 串不存在前缀关系。

$1\leq n\leq 10^5, 1\leq m=\sum\limits_i|s_i|\leq 10^6$。

### 题解：

显然要建 trie 树，然后考虑一个简单贪心，自下向上考虑，对于每个字符串贪心选取增加字符数最少的一种方案，容易证明贪心是正确的。

直接做复杂度是平方级的，不可接受。考虑优化，对于每个子树维护下增加串且不造成前缀关系的最小代价，然后可以用可并堆胡乱做。

但是太过复杂。不难观察到最短增加数  $\operatorname{cost}_u$ 是类似于左偏树中 $\operatorname{dist}_u$ 的，于是也容易证明 $O(\operatorname{cost}_u)=O(\log |\operatorname{subtree}(u)|)$ 的，且对于每个串贪心增加时也最多在 trie 树上增加两个结点，因此在此基础上暴力向子树中查找并维护的复杂度是正确的 $O((n+m)\log (n+m))$。

[code.](https://paste.ubuntu.com/p/bfp9HqQxgS/)

---

## 作者：Caiest_Oier (赞：1)

# [P10283](https://www.luogu.com.cn/problem/P10283)    

不使用可并堆的做法。首先建出 01-trie，从下往上考虑，当前点如果存在一个不合法的身份证号，则找到当前节点内最近的可以放入的位置，将其放进去即可。       

具体的，令 $dp_i$ 表示 $i$ 子树内距离 $i$ 节点最近的可以添加的合法位置与 $i$ 的距离。当 $i$ 为叶子，则需要挪动两步，分别将 $i$ 本身的身份证号与外来的身份证号挪到下一层，$dp_i=2$。当 $i$ 只有一个儿子，则 $dp_i=1$。当 $i$ 有两个儿子，取两个儿子的 $dp$ 值中较小的 $+1$ 作为当前点的 $dp$ 值。        

每次根据 $dp$ 值找到一个最近的可放入的位置，并将身份证号放入。容易发现，两者的距离不超过 $O(\log n)$ 级别，于是对于链上 $O(\log n)$ 个点重新计算 $dp$ 值即可。可能有一点需要分类讨论的细节。     

代码写的很丑，没有什么参考价值，就不放了（）。

---

## 作者：cike_bilibili (赞：0)

wc 了我怎么连上 01-trie 都没想到，鉴定为题做少了。

上 01-trie，考虑合法状态，就是任何一个终止点的祖先链上没有终止节点，考虑将原 trie 树调整至合法状态。

考虑从下往上调整，记录 $f_i$ 表示假设在 $i$ 节点插入了一个字符串，调整至合法的最少步数，如果是叶子节点，$f_i=2$，因为叶子上本身就有一个终止节点，只能将其分至两侧；如果只有一边是空的，则 $f_i=1$，即调整至空儿子中；否则 $f_i=\min \{f_{ls},f_{rs}\} +1$，即选一边传下去。

从下往上调整时，我们如果遇到了终止点，就挑一边 $f$ 值小的位置递归下去，然后重构路径上的 $f$ 值即可，容易证明这样做一定永远处于最优状态。

复杂度 $O(n \log n + \sum |s_i|)$。

由于我太菜了所以贴个代码。

```cpp
#include <bits/stdc++.h>
#define ls tree[i].ch[0]
#define rs tree[i].ch[1]
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int ans=0,w=1;
    char ch=getchar();
    while(ch<48||ch>57){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>=48&&ch<=57){
        ans=(ans<<1)+(ans<<3)+ch-48;
        ch=getchar();
    }
    return w*ans;
}
int n;
struct tree{
    int ch[2];
    int cnt;
    int val;
}tree[3000005];
int tim=1;
void pushup(int i){
    if(!ls&&!rs)tree[i].val=2;
    else if(!ls||!rs)tree[i].val=1;
    else tree[i].val=min(tree[ls].val,tree[rs].val)+1;
}
void insert(string s){
    int len=s.size();
    int u=1;
    for(int i=0;i<len;i++){
        if(!tree[u].ch[s[i]-'0'])tree[u].ch[s[i]-'0']=++tim;
        u=tree[u].ch[s[i]-'0'];
    }
    // cerr<<u<<'\n';
    tree[u].cnt++;
}
void dp(int x){
    for(int i:{0,1})if(tree[x].ch[i])dp(tree[x].ch[i]);
    pushup(x);
}
void put(int i){
    if(!ls&&!rs){
        ls=++tim,rs=++tim;
        tree[ls].val=tree[rs].val=2;
        pushup(i);
        return;
    }
    if(!ls){
        ls=++tim;
        tree[ls].val=2;
        pushup(i);
        return;
    }
    if(!rs){
        rs=++tim;
        tree[rs].val=2;
        pushup(i);
        return;
    }
    if(tree[ls].val<=tree[rs].val){
        put(ls);
        pushup(i);
    }else{
        put(rs);
        pushup(i);
    }
}
ll ans=0;
void work(int x){
    // cerr<<x<<' '<<tree[x].ch[0]<<' '<<tree[x].ch[1]<<' '<<tree[x].cnt<<"\n";
    for(int i:{0,1})if(tree[x].ch[i])work(tree[x].ch[i]);
    if(!tree[x].ch[0]&&!tree[x].ch[1])--tree[x].cnt;
    else pushup(x);
    while(tree[x].cnt--){
        ans+=tree[x].val;
        put(x);
    }
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        insert(s);
    }
    dp(1);
    work(1);
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：Larunatrecy (赞：0)

考虑一个无限大的字典树，那么这 $n$ 个串各代表了一个终止节点，我们每次可以花费一个代价把一个终止节点移动到某个儿子，使得最终任意两个终止节点不构成祖先关系。

考虑自底向上贪心，我们每次可以选择以下两种决策：

- 注意到每个时刻当前字典树的叶子恰好有一个终止节点，我们可以选择一个子树内的叶子，给这个叶子建两个儿子，并且把当前终止节点和叶子上的终止节点移动上去，代价是 $d+2$，其中 $d$ 为到叶子的距离。
- 选择一个子树内的，恰好有一个儿子的节点，给这点新建一个儿子，然后把当前终止节点移上去，代价是 $d+1$。

维护所有可能的决策，每次用最小代价的决策更新即可，决策的合并可以用可并堆，复杂度 $O(N\log N)$，其中 $N$ 为所有串的总长度和。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
template <typename T>inline void read(T &x)
{
    x=0;char c=getchar();bool f=0;
    for(;c<'0'||c>'9';c=getchar())f|=(c=='-');
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
    x=(f?-x:x);
}
const int N = 5e6+7;
int tot=1;
char s[N];
int tr[N][2],cnt[N],d[N];
int ans=0;
#define PII pair<int,int>
#define mk(x,y) make_pair(x,y)
int rot[N],lson[N],rson[N],idx=0,dis[N];
PII val[N];
int Merge(int x,int y)
{
	if(!x||!y)return x+y;
	if(val[x]>val[y])swap(x,y);
	if(dis[lson[x]]<dis[rson[x]]) swap(lson[x],rson[x]);
	dis[x]=dis[rson[x]]+1;
	rson[x]=Merge(rson[x],y);
	return x;
}
void dfs(int x)
{
    if(!tr[x][0]&&!tr[x][1])
    {
        int u=++idx;
        val[u]=mk(d[x]+2,x);
        rot[x]=u;
    }
    else if(!tr[x][0]||!tr[x][1])
    {
        int u=++idx;
        val[u]=mk(d[x]+1,x);
        rot[x]=u;
    }
    for(int c=0;c<=1;c++)
    if(tr[x][c])
    {
        d[tr[x][c]]=d[x]+1;
        dfs(tr[x][c]);
        rot[x]=Merge(rot[x],rot[tr[x][c]]);
    }
    if(!tr[x][0]&&!tr[x][1])cnt[x]--;
    while(cnt[x])
    {
        cnt[x]--;
        int u=rot[x],p=val[u].second;
        ans+=val[u].first-d[x];
        rot[x]=Merge(lson[u],rson[u]);
        if(!tr[p][0]&&!tr[p][1])
        {
            tr[p][0]=++tot;d[tot]=d[p]+1;
            int v=++idx;
            val[v]=mk(d[tot]+2,tot);
            rot[x]=Merge(rot[x],v);
            tr[p][1]=++tot;d[tot]=d[p]+1;
            v=++idx;
            val[v]=mk(d[tot]+2,tot);
            rot[x]=Merge(rot[x],v);
        }
        else
        {
            if(!tr[p][0])tr[p][0]=++tot,d[tot]=d[p]+1;
            if(!tr[p][1])tr[p][1]=++tot,d[tot]=d[p]+1;
            int v=++idx;
            val[v]=mk(d[tot]+2,tot);
            rot[x]=Merge(rot[x],v);
        }
    }
}
int main()
{
    //freopen("a.in","r",stdin);
    int n;
    read(n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        int p=1,m=strlen(s+1);
        for(int j=1;j<=m;j++)
        {
            int c=s[j]-'0';
            if(!tr[p][c])tr[p][c]=++tot;
            p=tr[p][c];
        }
        cnt[p]++;
    }
    dfs(1);
    cout<<ans;
    return 0;
}
```

---

