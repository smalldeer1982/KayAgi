# [OOI 2025] Dreaming is not harmful

## 题目背景

[试题来源](https://inf-open.ru/2024-25/final-materials/)。

## 题目描述

在婚礼策划公司 M.，计划进行大规模裁员。所有员工都在忙着计算天数，期待着在有利的情况下，他们能够取代现有的领导，执掌公司。

公司的结构表示为一个以顶点 $1$ 为根的悬挂树。员工编号 $v$ 的直接主管是编号为 $p_v$ 的员工。员工 $v$ 的能力水平由参数 $s_v$ 定义。这个参数是所有员工的独立值，且能力水平越高，员工对公司越有用。注意，由于不透明的招聘过程，可能会出现能力较低的员工是能力较高员工的主管的情况。

由于公司进行大规模人员调整，每天位于工作层级结构根部的 CEO 会被解雇。如果公司中还有员工，则能力最强的直接下属会接替 CEO 的位置。之后，前任主管的其他下属将成为新任主管的下属。为了更好地理解这个条件，可以参考样例中的说明。

每个员工都轻松地计算出自己成为 CEO 需要多少天。许多人不愿意等那么久，因为他们只能当一天的主管！为了加速这个过程，他们准备“拉黑”（cancel）一位同事。被“拉黑”的员工的能力水平会降至 $0$，因为没有人再愿意与他们互动。

您需要回答 $q$ 个询问。在第 $k$ 个询问中，编号为 $v_k$ 的员工想知道，如果他们愿意“拉黑”**恰好**一名员工，他们能够领导公司的最少等待天数是多少。所有询问都是假想且独立的，员工的实际能力水平在所有询问中保持不变。

## 说明/提示

**样例解释**

在测试样例中，第五名员工可以在 1 天后领导公司。为此，只需“拉黑”第二名员工即可。公司结构将如下改变：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ihwvwsj.png)

第三名员工可以在 3 天后领导公司。为此，只需“拉黑”第五名或第四名员工即可。如果拉黑第五名员工，公司结构将如下改变：

![](https://cdn.luogu.com.cn/upload/image_hosting/grptp827.png)

第一名员工已经是公司的领导者，因此对应查询的答案是 $0$。

第四名员工可以在两天后成为公司领导。与前一个例子类似，只需“拉黑”第五名员工即可。

**评分**

本题的测试点包含九个分组。每个分组的分数只有在该分组的所有测试点以及所有依赖分组的测试点都通过时才能获得。请注意，通过样例测试点对于某些分组不是必需的。$\textbf{Offline-evaluation}$ 表示该分组的测试结果将在比赛结束后才可查看。

| Subtask | 分数 | 额外限制：$n$ | 额外限制：$q$ | 依赖组别 | 说明                                                                  |
| :--- | :--- | :---------- | :---------- | :------- | :-------------------------------------------------------------------- |
| 0    | 0    | --          | --          | --       | 样例。                                                                |
| 1    | 10   | --          | --          | --       | $p_i = 1$ 或 $p_i = i - 1$，其中 $p_i = 1$ 的 $i$ 不超过两个。       |
| 2    | 6    | --          | --          | 1        | $p_i = 1$ 或 $p_i = i - 1$。                                          |
| 3    | 8    | $n \le 50$  | $q \le 50$  | 0        |                                                                      |
| 4    | 13   | $n \le 1000$ | $q \le 1000$ | 0, 3     |                                                                      |
| 5    | 11   | --          | $q \le 100$ | 0, 3     |                                                                      |
| 6    | 9    | --          | --          | --       | $p_i = \lfloor \frac{i}{2} \rfloor$。                                 |
| 7    | 11   | --          | --          | 0, 3, 6  | 任何员工的主管\*数量不超过 $100$。                                    |
| 8    | 14   | --          | --          | --       | $s_i > s_{p_i}$ 对于任何 $i > 1$。                                    |
| 9    | 18   | --          | --          | 0 -- 8   | **Offline-evaluation.**                                               |

主管\*：直接或者间接的主管。

## 样例 #1

### 输入

```
5 4
1 2 2 1
3 5 1 2 4
5 3 1 4```

### 输出

```
1 3 0 2```

# 题解

## 作者：_lmh_ (赞：5)

首先跑一个完整的替换序列出来，假设 $u$ 在 $t_u$ 时刻被删除。

“拉黑”一个人等价于将其子树中所有人从序列中删除，所以一个点 $u$ 的最优策略是找到一个 $v$ 点使得 $v$ 不是 $u$ 的祖先并且 $v$ 子树中的点在 $1\sim t_u$ 中出现次数尽可能多。

按照 $t_u$ 从小到大的顺序做。维护出现次数可以用树链剖分，而树剖没有修改的点自然就是可以被选择的 $v$，用线段树维护即可。

时间复杂度 $O(n\log^2 n)$，使用 `LCT` 可以优化到 $O(n\log n)$ 但没必要。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lson (u<<1)
#define rson (u<<1|1)
const ll N=300007;
ll n,m,p[N],son[N],sz[N],dfn[N],timer,top[N],ans[N],val[N<<2],tag[N<<2],w[N],id[N];
vector<ll> to[N];
priority_queue<pair<ll,ll> > pq;
void add(int u,int v){val[u]+=v;tag[u]+=v;}
void pushdown(int u){
	if (tag[u]){
		add(lson,tag[u]);add(rson,tag[u]);tag[u]=0;
	}
}
void modify(int u,int l,int r,int L,int R,int v){
	if (L<=l&&r<=R){
		add(u,v);return;
	}
	int mid=l+r>>1;pushdown(u);
	if (L<=mid) modify(lson,l,mid,L,R,v);
	if (R>mid) modify(rson,mid+1,r,L,R,v);
	val[u]=max(val[lson],val[rson]);
}
ll query(int u,int l,int r,int L,int R){
	if (L<=l&&r<=R) return val[u];
	int mid=l+r>>1;pushdown(u);
	if (R<=mid) return query(lson,l,mid,L,R);
	if (L>mid) return query(rson,mid+1,r,L,R);
	return max(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
}
void dfs(int u,int t){
	top[u]=t;dfn[u]=++timer;
	if (son[u]){
		dfs(son[u],t);
		for (auto v:to[u]) if (v!=son[u]) dfs(v,v);
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for (int i=2;i<=n;++i){cin>>p[i];to[p[i]].emplace_back(i);}
	for (int i=1;i<=n;++i){sz[i]=1;cin>>w[i];}
	pq.push(make_pair(w[1],1));
	while(!pq.empty()){
		int u=pq.top().second;pq.pop();
		id[++timer]=u;
		for (auto v:to[u]) pq.push(make_pair(w[v],v));
	}
	timer=0;
	for (int i=n;i>1;--i){
		sz[p[i]]+=sz[i];
		if (sz[i]>sz[son[p[i]]]) son[p[i]]=i;
	}
	dfs(1,1);
	for (int i=1;i<=n;++i){
		int u=id[i],v=u,lst=n;
		while(u){
			int t=top[u];
			modify(1,1,n,dfn[t],dfn[u],1);
			if (dfn[u]<lst) ans[v]=max(ans[v],query(1,1,n,dfn[u]+1,lst));
			lst=dfn[t]-1;
			u=p[t];
		}
		ans[v]=i-1-ans[v];
	}
	while(m--){
		int x;cin>>x;cout<<ans[x]<<' ';
	}
	cout<<'\n';
	return 0;
}
```

---

## 作者：FFTotoro (赞：4)

*Dreaming is not harmful.*

有一个很重要的点：如果不考虑降低员工能力值，那么所有员工被开除的顺序是固定的。先处理出这个序列（可以使用优先队列维护这个过程），记 $\mathrm{ord}(i)$ 为第 $i$ 天当上 CEO 的员工编号。

接着观察到将一个员工的能力值降为 $0$，等价于删掉这个员工和他 / 她的所有下属（即忽略一棵子树）。假设员工 $u$ 满足 $\mathrm{ord}(p)=u$，那么只有员工 $\mathrm{ord}(1),\mathrm{ord}(2),\ldots,\mathrm{ord}(p-1)$ 可能影响到他 / 她。只需要选择一棵子树（当然这棵子树不能包含 $u$），使得其中包含尽可能多的上述员工，进行删除后的答案就是最优的。

维护一棵带权树 $T$：顺次求解 $\mathrm{ord}(1),\mathrm{ord}(2),\ldots,\mathrm{ord}(n)$ 的答案，设当前考虑到的员工编号为 $u$，那么每次求解结束后就将 $T$ 中 $u$ 到根的路径上所有点权值 $+1$；于是查询最大子树和变为单点权值，就可以用树链剖分 + 线段树维护。

注意特别处理“子树不能包含 $u$”的限制：考虑一个极大值 $I$（可以取 $I=10^{18}$），只需要在求解前将 $u$ 到根的链上点的权值都减去 $I$，求解后再加上 $I$ 即可。

时间复杂度 $O(n\log^2n)$。

代码中为了方便实现，直接将员工编号替换为其能力值。放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int I=1e9;
class segtree{
  private:
    vector<pii> B;
    vector<ll> S,T;
    inline void pushup(int u){
      S[u]=max(S[u<<1],S[u<<1|1]);
    }
    inline void pushdown(int u){
      if(T[u]){
        S[u<<1]+=T[u],S[u<<1|1]+=T[u];
        T[u<<1]+=T[u],T[u<<1|1]+=T[u],T[u]=0;
      }
    }
  public:
    segtree(int n):B(n<<2),S(n<<2),T(n<<2){
      function<void(int,int,int)> build=[&](int u,int l,int r){
        if(B[u]=make_pair(l,r);l==r)return;
        int m=l+r>>1;
        build(u<<1,l,m),build(u<<1|1,m+1,r);
      };
      build(1,0,n-1);
    }
    void update(int u,int l,int r,int d){
      if(B[u].first>r||B[u].second<l)return;
      if(l<=B[u].first&&B[u].second<=r){
        S[u]+=d,T[u]+=d; return;
      }
      pushdown(u);
      update(u<<1,l,r,d),update(u<<1|1,l,r,d);
      pushup(u);
    }
    inline int all_prod(){return S[1];}
}; // 线段树
class hld{
  private:
    int n;
    vector<int> f,e,h,t,l;
    segtree T;
  public:
    hld(int rt,vector<vector<int> > g):n(g.size()),T(n){
      f.resize(n),e.resize(n,1);
      h.resize(n,-1),t.resize(n),l.resize(n);
      function<void(int)> dfs=[&](int u){
        int mx=0;
        for(int i:g[u]){
          f[i]=u,dfs(i),e[u]+=e[i];
          if(e[i]>mx)mx=e[i],h[u]=i;
        }
      };
      int o=0;
      function<void(int,bool)> decomp=[&](int u,bool b){
        t[u]=b?t[f[u]]:u,l[u]=o++;
        if(~h[u])decomp(h[u],true);
        for(int i:g[u])
          if(i!=h[u])decomp(i,false);
      };
      f[rt]=-1,dfs(rt),decomp(rt,false);
    }
    inline void update(int u,int d){
      while(~u)T.update(1,l[t[u]],l[u],d),u=f[t[u]];
    } // 链加
    inline int query(){return T.all_prod();} // 全局 max
}; // 树链剖分
int main(){
  ios::sync_with_stdio(false);
  int n,m; cin>>n>>m;
  vector<pii> e;
  for(int i=1;i<n;i++){
    int f; cin>>f;
    e.emplace_back(f-1,i);
  }
  vector<int> s(n),o,r(n);
  for(auto &i:s)cin>>i,i--;
  vector<vector<int> > g(n);
  for(auto [u,v]:e)
    g[s[u]].emplace_back(s[v]);
  priority_queue<int> q;
  q.emplace(s[0]);
  while(!q.empty()){
    int u=q.top(); q.pop();
    o.emplace_back(u);
    for(int i:g[u])q.emplace(i);
  } // 求解原顺序
  hld h(s[0],g);
  for(int i=0;i<n;i++){
    int u=o[i];
    h.update(u,-I);
    r[u]=i-max(0,h.query());
    h.update(u,I+1);
  } // 依次求解
  while(m--){
    int x; cin>>x;
    cout<<r[s[x-1]]<<' ';
  }
  cout<<endl;
  return 0;
}
```

---

