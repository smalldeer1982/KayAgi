# [ABC304Ex] Constrained Topological Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc304/tasks/abc304_h

$ N $ 頂点 $ M $ 辺の有向グラフが与えられます。 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ s_i $ から頂点 $ t_i $ への有向辺です。

$ (1,\ 2,\ \ldots,\ N) $ の順列 $ P\ =\ (P_1,\ P_2,\ \ldots,\ P_N) $ であって下記の $ 2 $ つの条件をともに満たすものが存在するかを判定し、存在する場合はその一例を示してください。

- すべての $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ P_{s_i}\ \lt\ P_{t_i} $
- すべての $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ L_i\ \leq\ P_i\ \leq\ R_i $

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min\lbrace\ 4\ \times\ 10^5,\ N(N-1)\ \rbrace $
- $ 1\ \leq\ s_i,\ t_i\ \leq\ N $
- $ s_i\ \neq\ t_i $
- $ i\ \neq\ j\ \implies\ (s_i,\ t_i)\ \neq\ (s_j,\ t_j) $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- 入力はすべて整数
 
### Sample Explanation 1

$ P\ =\ (3,\ 1,\ 4,\ 2,\ 5) $ が条件を満たします。実際、 - $ 1 $ 番目の辺 $ (s_1,\ t_1)\ =\ (1,\ 5) $ について、$ P_1\ =\ 3\ \lt\ 5\ =\ P_5 $ - $ 2 $ 番目の辺 $ (s_2,\ t_2)\ =\ (2,\ 1) $ について、$ P_2\ =\ 1\ \lt\ 3\ =\ P_1 $ - $ 3 $ 番目の辺 $ (s_3,\ t_3)\ =\ (2,\ 5) $ について、$ P_2\ =\ 1\ \lt\ 5\ =\ P_5 $ - $ 4 $ 番目の辺 $ (s_4,\ t_4)\ =\ (4,\ 3) $ について、$ P_4\ =\ 2\ \lt\ 4\ =\ P_3 $ が成り立ちます。また、 - $ L_1\ =\ 1\ \leq\ P_1\ =\ 3\ \leq\ R_1\ =\ 5 $ - $ L_2\ =\ 1\ \leq\ P_2\ =\ 1\ \leq\ R_2\ =\ 3 $ - $ L_3\ =\ 3\ \leq\ P_3\ =\ 4\ \leq\ R_3\ =\ 4 $ - $ L_4\ =\ 1\ \leq\ P_4\ =\ 2\ \leq\ R_4\ =\ 3 $ - $ L_5\ =\ 4\ \leq\ P_5\ =\ 5\ \leq\ R_5\ =\ 5 $ も成り立ちます。

### Sample Explanation 2

条件を満たす $ P $ が存在しないので、`No` を出力します。

## 样例 #1

### 输入

```
5 4
1 5
2 1
2 5
4 3
1 5
1 3
3 4
1 3
4 5```

### 输出

```
Yes
3 1 4 2 5```

## 样例 #2

### 输入

```
2 2
1 2
2 1
1 2
1 2```

### 输出

```
No```

# 题解

## 作者：Hasinon (赞：10)

简要题意：求拓补序，但是对每个点的编号有范围限制。只需输出一种方案即可。

很 naive 的思路第 $i$ 次选择是在出度为 $0$ 的且 $l_x \geq i$ 的点里面选，优先选 $r_x$ 最小的。但是被 hack 了，比如一个图形如 $1[1-3]\rightarrow 2[2-2]$，然后 $3[1-2]$ 单出来（中括号表示点的拓补序范围限制）。合法方案是 $1,2,3$，但是贪心会先选 $3$，再选 $1$，非法了。

显然的优化思路是把 $r_1$ 与 $r_2-1$  取 min，也就是反着拓补一遍，把 $r_u$ 向其后继节点 $\min r_v-1$ 取 min。

图片是官方英语题解证明的中文翻译（~~虽然是 chatgpt 写的但是我自己看懂了~~），证明里的 $R$ 是取 min 处理之后得到的。你发现根据证明，取 min 过程不减一也是对的。

![](https://cdn.luogu.com.cn/upload/image_hosting/3bk434h9.png)

---

## 作者：wxzzzz (赞：8)

### 思路

- 感谢 @[Rain_chr](https://www.luogu.com.cn/user/684254) 的精彩讲解。

首先，$l,r$ 的限制很宽，无法在任意时刻直接确定某个点一定需要满足的 $l,r$，考虑缩小范围。

因为对于任意点 $x,y$，若存在边 $(x,y)$，则必然有 $l_y\ge l_x+1$，且 $r_x\le r_y-1$。根据这个性质，可以在任意拓扑序和它的倒序上分别更新 $l,r$。

然后，有一个显然的贪心思路：根据 $r$ 从小到大考虑每个点，使每个点的拓扑序在满足要求的前提下尽可能小。

注意：在没有更新 $l,r$ 之前直接按照 $r$ 从小到大考虑是错误的，因为此时的 $r$ 不是“真实值”。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, idx, v[1000005], h[1000005], ne[1000005], deg[1000005], ord[1000005], ans[1000005];
queue<int> q;
bitset<1000005> vis;
set<int> s;
set<int>::iterator it;
struct point {
    int l, r, id;
} t[1000005];
inline bool cmp(point x, point y) {
    return x.r < y.r;
}
inline void add(int x, int y) {
    v[++idx] = y, ne[idx] = h[x], h[x] = idx, deg[y]++;
}
inline bool topsort() {
    int cnt = 0;

    for (int i = 1; i <= n; i++)
        if (!deg[i])
            q.push(i);

    while (!q.empty()) {
        int x = q.front();
        q.pop(), ord[++cnt] = x;

        for (int i = h[x]; ~i; i = ne[i]) {
            int y = v[i];
            deg[y]--;
            t[y].l = max(t[y].l, t[x].l + 1);

            if (!deg[y])
                q.push(y);
        }
    }

    if (cnt != n)
        return 0;

    for (int i = cnt; i >= 1; i--) {
        int x = ord[i];

        for (int j = h[x]; ~j; j = ne[j]) {
            int y = v[j];
            t[x].r = min(t[x].r, t[y].r - 1);
        }
    }

    return 1;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;

    while (m--) {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }

    for (int i = 1; i <= n; i++) {
        cin >> t[i].l >> t[i].r;
        t[i].id = i;
    }

    if (!topsort()) {
        cout << "No";
        return 0;
    }

    sort(t + 1, t + n + 1, cmp);

    for (int i = 1, x; i <= n; i++) {
        x = t[i].id;

        for (int j = t[i - 1].r + 1; j <= t[i].r; j++)
            s.insert(j);

        it = s.lower_bound(t[i].l);

        if (it == s.end()) {
            cout << "No";
            return 0;
        }

        ans[x] = *it, s.erase(it);
    }

    cout << "Yes\n";

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';

    return 0;
}
```

---

## 作者：Creeper_l (赞：4)

## 题意

给定一张有向图 $G$，有 $n$ 个点和 $m$ 条边，问是否存在一种拓扑序的排列 $P$ 使得 $l_{i} \le p_{i} \le r_{i}$。

## 思路

首先对于一条边 $u \to v$，如果限制满足 $r_{v}\le r_{u}$ 或者 $l_{v} \ge l_{u}$ 的话，那么这个限制其实是不完全正确的。因为最终的序列一定是一个拓扑序，所以一定有 $p_{u} \le p_{v}$，而题目给定的限制是不一定满足这个条件的。所以应该将限制更改为：

$l_{v}=\max(l_{v},l_{u} + 1),r_{u}=\min(l_{u},l_{v} + 1)$。

对于 $l$ 限制的更改应该在拓扑序上正序更改，而对于 $r$ 的限制应该在拓扑序上倒序更改，因为前者是从 $u$ 更新到 $v$，而后者是从 $v$ 更新到 $u$。

将限制修改后，考虑贪心。应该按照 $r$ 从小到大的顺序来选择这些点，对于每一个点 $u$，最终 $u$ 点的位置应该满足 $p_{u}\ge l_{u}$ 并且 $p_{u}$ 应该尽量去接近 $l_{u}$，因为这样选择位置后可以使后面 $r$ 的值更大的点有更多的选择空间。这个操作可以用一个 $set$ 来实现，每一次选择就相当于在 $set$ 中间做一次二分查找第一个大于 $l_{u}$ 的数，总时间复杂度 $O(n \log n)$。

注意还需要判断这个图是不是一个有向无环图，如果不是的话直接判断为不可能即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define re register
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 3e5 + 10;
int n,m,x,y,l[MAXN],r[MAXN],head[MAXN],cnt,din[MAXN],a[MAXN],tot,ans[MAXN];
struct Node{int u,v,nxt;}e[MAXN];
set <int> s;
vector <int> v[MAXN];
queue <int> q;
inline void Add(int u,int v){e[++cnt] = {u,v,head[u]};head[u] = cnt;}
signed main()
{
	memset(head,-1,sizeof head);
	cin >> n >> m;
	for(int i = 1;i <= m;i++) cin >> x >> y,Add(x,y),din[y]++;
	for(int i = 1;i <= n;i++) cin >> l[i] >> r[i];
	for(int i = 1;i <= n;i++) if(din[i] == 0) q.push(i);
	while(!q.empty())
	{
		int u = a[++tot] = q.front();q.pop();
		for(int i = head[u]; ~ i;i = e[i].nxt)
		{
			int now = e[i].v;
			l[now] = max(l[now],l[u] + 1);
			if(--din[now] == 0) q.push(now);
		}
	}
	if(tot < n){puts("No");return 0;}
	for(int i = tot;i >= 1;i--)
	{
		int u = a[i];
		for(int j = head[u]; ~ j;j = e[j].nxt)
		{
			int now = e[j].v;
			r[u] = min(r[u],r[now] - 1);
		}
		v[r[u]].emplace_back(u);
	}
	for(int i = 1;i <= n;i++)
	{
		s.insert(i);
		for(int j = 0;j < v[i].size();j++)
		{
			int u = v[i][j];
			auto k = s.lower_bound(l[u]);
			if(k == s.end()){puts("No");return 0;}
			ans[u] = *k,s.erase(k);
		}
	}
	puts("Yes");
	for(int i = 1;i <= n;i++) cout << ans[i] << " ";
	return 0; 
}
```


---

## 作者：lfxxx (赞：2)

考虑假若不是拓扑序，只是要求每个点的值在某个区间内，我们考虑按限制从紧到松依次满足，具体地将所有限制按照 $L$ 降序为第一关键字，$R$ 升序为第二关键字排序，从后往前扫，用一个 set 维护当前可以使用的编号，每次找一个最大能满足当前限制的填进去，因为显然把小的编号留到后面更优，更容易满足 $R$ 的限制。

但是考虑有了边对拓扑序的限制怎么办，考虑先正着反着各做一遍拓扑排序，对于一条边 $u,v$ 使得 $L_{v} = \max(L_v,L_u+1),R_u = \min(R_u,R_v-1)$，更新后新的拓扑序可以满足在满足区间限制的同时满足了边对拓扑序的限制，跑上面那个贪心即可。

时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int L[maxn],R[maxn];
vector<int> E[maxn],e[maxn];
int In[maxn],Out[maxn];
queue<int> q;
int n,m;
bool cmp(int x,int y){
    return R[x]<R[y];
}
vector<int> vec[maxn];
int ans[maxn];
int vis[maxn];
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        In[v]++;
        e[v].push_back(u);
        Out[u]++;
    }
    for(int i=1;i<=n;i++) cin>>L[i]>>R[i];
    for(int i=1;i<=n;i++){
        if(In[i]==0) q.push(i);
    }
    while(q.size()>0){
        int u=q.front();
        vis[u]=true;
        q.pop();
        for(int v:E[u]){
            In[v]--;
            L[v]=max(L[v],L[u]+1);
            if(In[v]==0) q.push(v);
        }
    }
    for(int i=1;i<=n;i++)
        if(vis[i]==false){
            cout<<"No\n";
            return 0;
        }
    for(int i=1;i<=n;i++){
        if(Out[i]==0) q.push(i);
    }
    while(q.size()>0){
        int u=q.front();
        q.pop();
        for(int v:e[u]){
            Out[v]--;
            R[v]=min(R[v],R[u]-1);
            if(Out[v]==0) q.push(v);
        }
    }
    for(int i=1;i<=n;i++)
        if(L[i]>R[i]){
            cout<<"No\n";
            return 0;
        }
    for(int i=1;i<=n;i++) vec[L[i]].push_back(i);
    for(int i=1;i<=n;i++) sort(vec[i].begin(),vec[i].end(),cmp);
    set<int> S;
    for(int i=n;i>=1;i--){
        S.insert(-i);
        for(int id:vec[i]){
            if(S.lower_bound(-R[id])!=S.end()){
                ans[id]=-(*S.lower_bound(-R[id]));
                S.erase(-ans[id]);
            }else{
                cout<<"No\n";
                return 0;
            }
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    return 0;
}
```

---

## 作者：BINYU (赞：2)

## 题意

给定一张有 $n$ 个点 $m$ 条边的有向图，需要求出一个满足一下条件的拓扑序：第 $i$ 个点的拓扑序在 $l_i$ 至 $r_i$ 之间。如果有，则输出 `Yes` 和每个点的拓扑序，否则输出 `No`。

## 思路

首先有环的情况肯定是不合法的，我们只考虑 DAG。

有一个非常显然但是错误的贪心：每次从当前可以加的点中选一个满足条件且 $r_u$ 最小的点 $u$ 来遍历，但这样是错误的，因为可能在一个 $r$ 非常大节点后面有一个 $r$ 非常小的节点，在考虑第一个节点是我们跳过了它，以至于之后再来考虑是发现不满足限制。

具体地，这里有一组数据：

Input

```
4 1
1 2
1 4
2 2
1 3
1 4
```

Output

```
Yes
1 2 3 4
```

发现这里贪心错误的原因是因为 $r_1$ 过于“宽松”，考虑通过一些手段更新 $r$ 让贪心成立。

我们发现有一部分点的 $r$ 限制是“无效的”，如：点 $u$ 是 $v$ 的前驱，$r_u \ge r_v$ 时，$u$ 的限制就是“无效的”，实际上此时 $r_u$ 的最大值为 $r_v - 1$，我们可以尝试用这个值去更新 $r_u$，得到一个更加“紧”的限制，
这可以通过一次 DFS 实现。

由于现在每个点的 $r$ 都比它的前驱要大，所以上述情况不会出现，贪心就正确率（具体的证明我不会，就口胡一下吧）。

回到之前的贪心上，我们考虑去实现它。我们可以建两个堆，一个装**仅满足拓扑排序本身条件**的点，另一个装满足拓扑排序本身条件且 **$l$ 合法**的点，每次从第二个堆中选点。

对于第一个堆，我们让它的排序关键字为 $l$，因为 $l$ 小的节点一定能被更先装入第二个堆中，第二个堆的排序关键字自然就是 $r$，符合我们贪心的需求。在拓扑排序时，只需要在每次从第二个堆中选点之前把第一个堆中能加入第二个堆的点全部加进去即可。

需要判断无解的情况有：有环，第二个堆为空，第二个堆堆顶元素的 $r$ 不合法。均可在拓扑排序中实现。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$，可过。

---

## 作者：rzh01014 (赞：0)

# [abc304_Ex](https://www.luogu.com.cn/problem/AT_abc304_h)
### 题目描述
给定一张 $n$ 个点 $m$ 条边的有向图，判断是否存在一个拓扑序 $P$ 满足 $P_i \in [L_i,R_i]$。
### 做法
根据题意，易判断如果图中存在一个环，则必没有解，因此先判断图中是否有环。   
由于最终的答案序列是一个拓扑序，给定的一条边 $u,v$ 决定了必有 $P_u \leq P_v$。  
此时 $P_u$，$P_v$ 也同时受到约束。

- $L_u \leq P_u \leq R_u$
- $L_v \leq P_v \leq R_v$
   
因此该约束条件可以转为：

- $L_u \leq P_u \leq \min(R_u,R_v-1)$
- $\max(L_u+1,L_v) \leq P_u \leq R_v$

在约束考虑完后，照 $R$ 的大小考虑每个点的拓扑序，贪心使每个点的权值尽可能小。   
### code
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,cnt,b[N],l[N],r[N],inv[N],ans[N];
vector<int>ve[N],g[N];
queue<int>q;
set<int>se;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		ve[u].emplace_back(v);
		inv[v]++;
	}
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
	for(int i=1;i<=n;i++) if(!inv[i]) q.push(i);
	while(!q.empty()){
		b[++cnt]=q.front();
		int u=b[cnt];
		q.pop();
		for(auto v:ve[u]){
			l[v]=max(l[v],l[u]+1);
			if(--inv[v]==0) q.push(v);
		}
	}
	if(cnt<n) return (cout<<"No"),0;
	for(int i=n;i>=1;i--){
		int u=b[i];
		for(auto v:ve[u]) r[u]=min(r[u],r[v]-1);
		g[r[u]].emplace_back(u);
	}
	for(int i=1;i<=n;i++){
		se.insert(i);
		for(int u:g[i]){
			auto it=se.lower_bound(l[u]);
			if(it==se.end()) return (cout<<"No"),0;
			ans[u]=*it;
			se.erase(it);
		}
	}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}

```

---

## 作者：elbissoPtImaerD (赞：0)

自然是考虑将每个点 $u$ 的真实 $l_u,r_u$ 值算出来，然后 Hall 定理贪心构造即可。

考虑边 $(u,v)$：  
有：$l_v\ge l_u +1$，$r_v\ge r_u+1$。

按拓扑序算一下即可得到 $[l_u,r_u]$。

然后按 $r$ 递增贪心即可构造。

```cpp
il void Solve()
{
  int n,m;
  rd(n),rd(m);
  ve<ve<int>>G(n);
  ve<int>d(n),l(n),r(n);
  for(int u,v;m--;rd(u),rd(v),--u,--v,G[u].pb(v),++d[v]);
  for(int i=0;i<n;++i) rd(l[i]),rd(r[i]);
  auto Topo=[&]
  {
    sd queue<int>q;
    ve<int>a;
    for(int i=0;i<n;++i) if(!d[i]) q.ep(i);
    for(;q.size();)
    {
      int u=q.front();
      q.pop(),a.pb(u);
      for(int v:G[u]) if(cx(l[v],l[u]+1),!--d[v]) q.ep(v);
    }
    if(a.size()!=n) return true;
    sd reverse(all(a));
    for(int u:a) for(int v:G[u]) cn(r[u],r[v]-1);
    return false;
  }();
  if(Topo) return wrt("No"),void();
  ve<int>p(n),ans(n);
  sd iota(all(p),0),sd stable_sort(all(p),[&](int x,int y){return r[x]<r[y];});
  sd set<int>S;
  for(int i=0;i<n;++i)
  {
    for(int j=i?r[p[i-1]]+1:0;j<=r[p[i]];++j) S.ep(j);
    auto it=S.lower_bound(l[p[i]]);
    if(it==end(S)) return wrt("No"),void();
    ans[p[i]]=*it,S.erase(it);
  }
  wrt("Yes\n");
  for(int x:ans) wrt(x,' ');
  return;
}
```

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc304/submissions/48878162)

---

