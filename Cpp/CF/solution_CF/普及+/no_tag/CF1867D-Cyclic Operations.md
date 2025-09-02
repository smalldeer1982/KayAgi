# Cyclic Operations

## 题目描述

Egor has an array $ a $ of length $ n $ , initially consisting of zeros. However, he wanted to turn it into another array $ b $ of length $ n $ .

Since Egor doesn't take easy paths, only the following operation can be used (possibly zero or several times):

- choose an array $ l $ of length $ k $ ( $ 1 \leq l_i \leq n $ , all $ l_i $ are distinct) and change each element $ a_{l_i} $ to $ l_{(i\%k)+1} $ ( $ 1 \leq i \leq k $ ).

He became interested in whether it is possible to get the array $ b $ using only these operations. Since Egor is still a beginner programmer, he asked you to help him solve this problem.

The operation $ \% $ means taking the remainder, that is, $ a\%b $ is equal to the remainder of dividing the number $ a $ by the number $ b $ .

## 说明/提示

Let's consider the first example:

- Apply the operation with $ l $ = $ [1,2,3] $ . Now $ a $ = $ [2,3,1,0,0] $ .
- Apply the operation with $ l $ = $ [3,5,4] $ . Now $ a $ = $ [2,3,5,3,4] $ = $ b $ .

 We see that it is possible to get the array $ b $ . Therefore, the answer is YES.In the second example, it can be proven that the array $ b $ cannot be obtained, therefore the answer is NO.

## 样例 #1

### 输入

```
6
5 3
2 3 5 3 4
4 2
2 4 3 1
1 1
1
3 1
1 2 3
5 3
5 4 3 2 1
6 1
1 2 3 1 5 6```

### 输出

```
YES
NO
YES
YES
NO
NO```

# 题解

## 作者：intconstlee (赞：10)

## Cyclic Operations 题解

拓扑找环。

### 题意简述

给定一个长为 $n$ 的数组 $a$，初始全为 $0$，可进行如下操作：

构建长为 $k$ 的数组 $l$，将 $a_{l_i}$ 变为 $l_{(i\bmod k)+1}(1\le i\le k)$。

若干操作后可得到数组 $b$，给定 $n,k,b$，求 $b$ 能否由 $a$ 经过上述操作得到。

### 思路分析

从数组 $a$ 的变化过程入手，发现给出 $l$ 以后的变化过程事实上就是使 $a$ 中 $k$ 个位置构成一个环，但操作区间之间可以覆盖，意味着某个环可能被断开，其一部分参与构成另一个环，且原环保留着向该部分的连边，也就是原环剩余部分向新环有连边。

![](https://cdn.luogu.com.cn/upload/image_hosting/k9ftv0mh.png)

故经过若干操作后，得到的结构应该是一个内向基环树森林（由 $b_i\ge 1$ 可知 $a$ 中全部位置均经过操作，不存在无连边的孤点），且基环大小为 $k$，当 $k\ne 1$ 时对基环树的非基环部分没有要求。

### 实现过程

首先拓扑排序，找出每棵基环树的环，之后对于每个环判断环的大小。特别地，当 $k=1$ 时需要特判，因为这时若存在非环上点会直接无解。


给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=100005;
int t,n,k,ans,to[N],dg[N],vis[N];
void topu()
{
    queue<int> q;
    for(int i=1;i<=n;i++) if(dg[i]==0) q.push(i);
    while(!q.empty())
    {
        int u=q.front(); vis[u]=1,q.pop();
        if(!--dg[to[u]]) q.push(to[u]);
    }
}
void findcir(int u)
{
    int siz=0;
    while(!vis[u]) vis[u]=1,u=to[u],siz++;
    if(siz!=k) ans=0;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)
    {
        cin>>n>>k,ans=1;
        memset(dg,0,sizeof(dg)),memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++) cin>>to[i],dg[to[i]]++;
        if(k==1) for(int i=1;i<=n;i++) if(to[i]!=i) ans=0;
        if(ans) topu();
        for(int i=1;i<=n;i++) if(!vis[i]&&ans) findcir(i);
        cout<<(ans?"YES":"NO")<<endl;
    }
    return 0;
}
```

---

## 作者：Creeper_l (赞：6)

## 前言

看这道题有好多巨佬都是用 Tarjan 来做的，在这里讲一个自认为比较简单的做法，~~(不到 $30$ 行)~~。

## 题意

题意比较难讲，建议自己去看一下翻译，在这里不多赘述。

## 思路

首先看到题目中间给的一个每一次操作的式子：$a_{l_{i}}=l_{(i\mod k)+1}$。仔细观察这个式子后会发现，其实每一次操作的目的其实就是将 $a_{i}$ 变为 $(i+1)\mod k$。再看样例的数组从 $1,2,3$ 变成了 $2,3,1$，于是我们就联想到了环。所以我们可以从 $i$ 向 $a_{i}$ 连一条边，这样就构成了一张图，且图中有若干个环。而每一个环其实就对应着每一次操作，不在环上的点不用考虑，因为随便选一些不在环上的点和一些在环上的点一共凑齐 $k$ 个点之后按要求进行操作就可以达到目标了。

接下来只需要考虑每一个环是否符合要求就行了。因为题目上说了每一次操作选的数的数量必须刚好是 $k$ 个，而每一个环上的点又必须一起选，所以我们只需要判断每一个环上的点数是否刚刚好等于 $k$ 就行了。

注意当 $k=1$ 的情况时需要特判一下。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair <int,int> pii;
const int MAXN = 2e5 + 10;
int T,n,k,a[MAXN],num[MAXN],vis[MAXN];
bool flag;
signed main()
{
	cin >> T;
	while(T--)
	{
		flag = true;
		cin >> n >> k;
		for(int i = 1;i <= n;i++) cin >> a[i],flag &= (!(k == 1 && a[i] != i));
		for(int i = 1;i <= n;i++)
		{
			if(vis[i] == true) continue;
			int u = i,cnt = 0;
			while(vis[u] == false) vis[u] = i,num[u] = ++cnt,u = a[u];
			if(vis[u] != i) continue;
			if(cnt - num[u] + 1 != k) flag = false;
		}
		if(flag == false) puts("No");
		else puts("Yes");
		for(int i = 1;i <= n;i++) num[i] = vis[i] = 0;
	}
	return 0;
}

```


---

## 作者：fast_photon (赞：3)

Upd 2023/10/2 20:53：题目传送门链接挂了。

**0. 前言**  
魔怔伪图论[题](/problem/CF1867D)，赛时[写了个倍增](https://codeforces.com/contest/1867/submission/222953100)水过去了。  
但是赛后回来真的一步一步推结论，还是挺巧妙的。  

**0.5 题意**  
一个无边图，每次操作选择 $k$ 个点，将它们原有出边删去后顺次连接成环。现给出每个点的出边终点编号，问这张图是否可以通过有限次操作得到。  

**1. 分析**  
> 每条边在不超过一个环上。  

证明：  
若一个点不停走向后继能回到自身，它在环上。这样走到后继构成的路径就是这个环。  
而对于后继唯一的节点构成的图，这样的走法不超过一个。因此每个节点至多在一个环上。而一条边必然与它的起点在相同的环上，则**每条边所在环唯一**。  

每次操作形成一个长度为 $k$ 的环。我们来研究一下能否通过若干操作形成一个其他长度的环。  
考虑一条环上边 $B\to C$ 及其环上前驱 $A\to B$，当 $A\to B$ 形成时，$B$ 必然在成环序列里。那么 $B$ 的出边就会被刷新。所以任一条边的成边时间不早于其环上前驱。  
可这是个环啊。我们对环用一圈这个不等式，就变成了一个等式：环上所有边成边时间相同！可是我们又注意到，一次操作只能形成长度为 $k$ 的环。所以**任意环长度必须为 $k$**。  

从一个点开始跳后继，由于每个点的出边不但是唯一而且是存在的，所以可以无限地跳下去。而图中的点有 $n$ 个，跳 $n+1$ 次一定跳到过某个节点多次，即**每个点都能跳到一个环上**。  

考虑环外的边 $A\to B$ 是如何建立的。若形如 $X\to A$ 的边已经全部建立完成，那么选择最终状态某个环上任意 $k-2$ 个**异于**$A,B$ 的点，建立一个环即可。因为 $B$ 的出边会在后续操作中被更正，而这次操作也不会影响 $A$ 的入边。  
而操作中 $A$ 的前驱因为在环上，最后一次操作时会被直接更正，无需操心。因此，**在环信息正确的情况下，任意环外边都是可以被建立的**。  

**2. 坑**  
如果您还没有发现问题，那恕我直言您的数学感觉不够敏锐。  
$k-2$ 个节点。$1\le k$。  
所以要特判 $1$。推一下发现每个点必须自环。没别的坑了。

**3. 代码**  
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<queue>
#include<vector>

using namespace std;

int n, k, f[200005], don[200005], ctn[200005];

bool work() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) don[i] = 0;
	for(int i = 1; i <= n; i++) cin >> f[i];
	if(k == 1) {
		for(int i = 1; i <= n; i++) if(i != f[i]) return false;
		return true;
	}
	for(int i = 1; i <= n; i++) {
		if(don[i] == 0) {
			int cnt = 0, r;
			for(r = i; !don[r]; r = f[r]) {
				ctn[r] = cnt;
				cnt++;
				don[r] = i;
			}
			if(don[r] != i) continue;
			if(cnt - ctn[r] != k) return false;
		}
	}
	return true;
}

signed main() {
	int _;
	cin >> _;
	while(_--) {
		cout << (work() ? "Yes\n" : "No\n");
	}
}  
```  

---

## 作者：luan341502 (赞：2)

从基环树的角度考虑。

根据题目中数组的下标和数值很容易想到形成一个环，可以想到构建一个图。因此我们连有向边 $(i,b_i)$，构成内向基环树森林。

考虑如果是合法的数组，最后一步肯定在数组上形成一个 $k$ 元环。因此考虑构造方案。对于在环上的点，如果正好为 $k$ 个，则可以通过一次操作覆盖环上所有点。而如果不为 $k$ 个，则无法覆盖。对于不在环上的点，我们可以将还没有赋值为 $b_i$ 按照离环的距离由远到近每 $k$ 个为一组赋值（可以选环上的点），因为后来的赋值会将前面的赋值覆盖，因此这么做是正确的。所以不需要考虑不在环上的点，总是可以赋成正确的值。

所以本题只需要判断图中的环是否都为 $k$ 元环。不需要建图，因为每个点出度都是 $1$，直接 dfs 即可。注意特判 $k=1$ 和 dfs 剪枝。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,ans=1;
int n,k,a[200005];
int d[200005],vis[200005];
void dfs(int x,int s){ //x->a[x]
	if(!a[x]) return;
	if(vis[x]){
		if(s-d[x]!=k) ans=0;
		return;
	}
	vis[x]=1;
	d[x]=s;
	dfs(a[x],s+1);
	vis[x]=0;
	a[x]=0;
}
void print(int x){
	if(x) puts("YES");
	else puts("NO");
}
void solve(){
	for(int i=1;i<=n;i++){
		vis[i]=d[i]=0;
	}
	ans=1;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	if(k==1){
		for(int i=1;i<=n;i++){
			if(a[i]!=i){
				print(0);
				return;
			}
		}
		print(1);
		return;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==i){
			print(0);
			return;
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]) dfs(i,0);
	}
	print(ans);
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：2020kanade (赞：1)

考虑每次操作的变换：依次选出若干个下标，将 $a$ 数组中这些选出的下标变成选出的“下一个”下标，注意此处的“下一个”是在环意义上的，最后一个位置的“下一个”位置是第一个位置。容易发现，一次操作后，如果将 $a$ 数组上所有被影响到的位置挑出来，让它们的值指向对应的下标，之后读取下标对应位置上的值接着走，走一圈会发现成了一个环，并且大小等于被影响到的元素个数，对应到原题也就是 $k$。

有了这样的关系，考虑连有向边：$i \rightarrow b_i$，这样构成的图一定是一个森林，每个联通块要么是一颗内向树要么是一颗内向基环树。如果要判断操作合法的情况，我们根据上面的推理可知，一次操作会成一个大小为 $k$ 的环，考虑再来一次操作进行覆盖，那么结果是，在不影响原有环的情况下，会形成一个新的独立的大小为 $k$ 的环；否则，考虑到原有的环上的点受到的影响，不难发现其出边一定会更换一条，而入边可能是更换一条或者是加一条，这样的话，原有的环会被破坏，形成一个新的大小为 $k$ 的环。

那么，我们得到结论：$b$ 数组能够通过若干次题中所给变换操作得到，当且仅当 $\forall i \in [1,n]$，连接有向边 $i\rightarrow b_i$，此时构成的图是一个内向基环森林，且所有环的大小为 $k$。注意，$k=1$ 时情况较特殊，所有环都是自环，即 $b_i=i$。

对于其他情况，我们直接存下有向边，从 $1$ 号结点开始暴力爬有向边，并对访问过的结点打上标记，如果出点也没有被访问就在并查集上将自己合并到边的出点。一旦发现出点已经被访问，停止跳边，此时可能有两种情况：出点之前被访问且当前点是出点的儿子，或者是加入该条边后成环。

用并查集查询判断：设当前边为 $u\rightarrow v$，如果并查集操作发现 $find(u)=find(v)$，则加入此边后会成环（原因留给读者思考，并不难），此时直接在环上跑一圈查出大小，将环的并查集上代表元与环的大小一起扔进一个集合中去。否则，正常在并查集上进行合并。注意，此时无论是哪一种情况，此时都应该转到下一个点而不是继续跳边。

同时，跳过被打标记的点的访问，可以保证时间复杂度。

执行完毕后，对每个点用并查集查询其所在环的代表元，然后在集合里看看这个环的大小是不是 $k$。如果每个点都符合条件，则数组合法。

时间复杂度 $\Theta(n\alpha(n))$，$\alpha(n)$ 为并查集操作均摊到单次的复杂度。

```cpp
//codeforces Round 897 Div2 D
//written by Codeforces:Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int ufs[N];
int sgs(int u)//sagasu
{
	return u==ufs[u]?u:ufs[u]=sgs(ufs[u]);
}
int to[N],vis[N],cyc[N],t,n,k;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;++i) ufs[i]=i,vis[i]=cyc[i]=0,cin>>to[i];
		if(k==1)
		{
			bool y=1;
			for(int i=1;i<=n;++i) if(to[i]!=i)
			{
				y=0;break;
			}
			if(!y) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
			continue;
		}
		bool y=1;
		for(int i=1;i<=n;++i) if(to[i]==i)
		{
			y=0;break;
		}
		if(!y)
		{
			cout<<"NO"<<endl;continue;
		}
		for(int i=1;i<=n;++i)
		{
			if(vis[i]) continue;
			int u=i;
			while(to[u]&&!vis[to[u]]) vis[u]=1,ufs[u]=to[u],u=to[u];vis[u]=1;
			if(!to[u])
			{
				y=0;break;
			}
			else if(vis[to[u]])
			if(sgs(u)==sgs(to[u]))
			{
				int x=to[u],cnt=0;
				for(;x!=u;x=to[x]) ++cnt;
				cyc[sgs(u)]=cnt+1;
				continue;
			}
			else ufs[u]=to[u];
		}
		if(!y)
		{
			cout<<"NO"<<endl;continue;
		}
		for(int i=1;i<=n;++i) if(cyc[sgs(i)]!=k)
		{
			y=0;break;
		}
		if(!y) cout<<"NO"<<'\n';
		else cout<<"YES"<<'\n';
	}
	return 0;
}
```


---

## 作者：Anamnesis (赞：1)

考虑什么样的 $b$ 是合法的。

可以发现每次操作会生成一个基于 $i \leftrightarrow b_i$ 的大小为 $k$ 的简单环。不同的环可能互相重叠，被覆盖的部分可以视为有一些边被删除，它就断开了，与覆盖了它的环形成一个连通块。对于每个这样的连通块，一定存在至少一个完整的大小为 $k$ 的环，来自最后一次未被其他操作覆盖的操作。可以参考下图理解一个合法的操作过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/4wwbpk4b.png)

检查 $b$ 是否由上述过程生成即可，也就是建图后判断每个连通块内是否存在至少一个点数为 $k$ 的简单环。有许多简单的方法，但无聊地复制一个边双连通分量缩点模板也可以通过。

除非 $k=1$，合法的 $b$ 一定满足 $b_i\neq i$，因此构造的图不存在自环（可以直接判 `NO`）。然而可能存在重边，这主要会影响我们在 $k=2$ 时的判断。

在 tarjan 的过程中，如果遇到超过 1 次父边，就说明这是重边。只需要增加一小段特判即可处理这问题。

```cpp
#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++);
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline long long read() { 
  long long x = 0, f = 1; char ch = getchar();
  while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
  while (ch >= '0' && ch <= '9') { x = x * 10 + ch - 48; ch = getchar(); }
  return x * f;
}
template <typename T>  //    !! debug only
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  int n = v.size();
  for (int i = 0; i < n; ++i)
    os << v[i] << ' ';
  return os;
}
using namespace std;
using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = read();
  while (T--) {
    int n = read(), k = read();
    vector<int> b(n), a(n);
    for (int i = 0; i < n; ++i)
      b[i] = read() - 1;
    iota(all(a), 0);
    if (k == 1) {
      if (a != b) {
        cout << "NO\n";
      } else {
        cout << "YES\n";
      }
      continue;
    }

    bool bad = 0;
    vector<vector<int>> e(n);
    for (int i = 0; i < n; ++i) {
      if (i == b[i]) {
        bad = 1;
        break;
      }
      e[i].push_back(b[i]);
      e[b[i]].push_back(i);
    }
    if (bad) {
      cout << "NO\n";
      continue;
    }

    struct Node {
      int fa, dfn, low, scc, vis;
    };
    vector<Node> g(n);
    vector<int> stk, sz;
    int sc = 0, dfscnt = 0;
    function<void(int, int)> tarjan = [&](int u, int fa) {
      g[u].dfn = g[u].low = ++dfscnt;
      g[u].vis = 1;
      stk.push_back(u);
      bool multiedge = 0;
      for (int v : e[u]) {
        if (v == fa && !multiedge) {
          multiedge = 1;
          continue;
        }
        if (!g[v].dfn) {
          tarjan(v, u);
          g[u].low = min(g[u].low, g[v].low);
        } else if (g[v].vis) {
          g[u].low = min(g[u].low, g[v].dfn);
        }
      }
      if (g[u].dfn == g[u].low) {
        sz.push_back(0);
        int top;
        do {
          top = stk.back();
          stk.pop_back();
          g[top].scc = sc;
          g[top].vis = 0;
          ++sz.back();
        } while (top != u);
        ++sc;
      }
    };
    
    for (int i = 0, lst = 0; i < n; ++i) {
      if (!g[i].dfn) {
        tarjan(i, -1);
        bool ok = 0;
        for (; lst < sc; ++lst) {
          if (sz[lst] == k) {
            ok = 1;
          } else if (sz[lst] > k) {
            ok = 0;
          }
        }
        if (!ok) {
          bad = 1;
          break;
        }
      }
    }

    cout << (bad ? "NO" : "YES") << '\n';
  }
  return 0;
}
```

---

## 作者：LCat90 (赞：1)

把题干转化为 $a[\ l[i]\ ]=l[i+1]$，似乎要清晰地多了。很容易看出这是一个环状结构。于是可以发现当这个环的长度为 $k$ 的时候对于环内明显是可以构造的。

建边就是朴素地将 $i$ 和 $b_i$ 相连，即 $(i,b_i)$。

对于不在环上的点，我们先考虑填充它们。选上 $k$ 个数（可以选环上的）使不在换上的点一定满足条件，后面我们最后再覆盖环上的即可。因为顺序后面的优先级更大。

等于的情况满足了，接下来要判断大于或小于的情况。

如果环长小于 $k$，那么在环上的操作中，至少有一个顶点不是来自环上，这意味着环上至少有一个顶点将被一个不在环上下一个顶点的数字所替换。但是因为环上的每个顶点都应该被它后面的下一个顶点所替换，故不行。大于的情况同理不行。故问题即为**判断环长是否等于 $k$**。

注意特判 $1$ 的情况。

---

## 作者：One_JuRuo (赞：1)

## 前言

赛时没调出来，赛后调了一个上午，最后发现是有个地方没清零。

## 思路

首先对于位置 $i$，我们必须要保证进行的操作中，最后一次出现 $i$，$i$ 的后面一定是 $a_i$。

那么我们考虑统计所有位置上的要求，用有向边链接，那么就会出现一个有环有向图（一定有环，因为点数等于边数）。

那么，自然想到缩点。

首先，如果有某个环的长度不为 $k$（不讨论长度为 $1$ 的情况），那么一定无解，因为总会剩几个点没办法改，或者为了改最后几个点而导致把最开始的点改了，自己手玩一下应该很好理解。

那么还有不构成环的，也可以理解成长度为 $1$ 的情况，我们可以先满足这些边的要求，这样可能会使得环内得答案不正确，但是我们可以最后再处理环，把之前错误的答案改正确。

所以做法就出来了，先建图，然后 tarjan 缩点，统计每个环的长度，长度要么为 $k$，要么为 $1$，如果存在不是 $k$ 也不是 $1$ 肯定无解，然后再统计长度为 $k$ 的个数，如果没有也肯定无解，否则就是有解。

另外，还有 $k=1$ 的特殊情况，这种情况，必须满足 $a_i=i$，也就是它只能每次选一个值 $l$，那必定是把 $a_l$ 改成 $l$，所以必须满足上述条件。

$k\neq1$ 则必须满足 $a_i\neq i$，因为 $l$ 互不相同。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,a[100005],e[100005],ne[100005],h[100005],num,idx=1,dcnt,siz[100005],dfn[100005],low[100005],z[100005],top,in_z[100005],ff,flag;
inline void add(int a,int b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
void dfs(int u)
{
	dfn[u]=low[u]=++dcnt,in_z[u]=1,z[++top]=u;
	for(int i=h[u];i;i=ne[i])
	{
		if(!dfn[e[i]]) dfs(e[i]),low[u]=min(low[u],low[e[i]]);
		else if(in_z[e[i]]) low[u]=min(low[u],dfn[e[i]]);
	}
	if(dfn[u]==low[u])
	{
		++num;
		while(z[top+1]!=u) in_z[z[top--]]=0,++siz[num];//因为这个写法，可能和上一次的进栈的元素相同，导致错误，所以要初始化z数组。
	}
}
inline bool sol()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n+1;++i) z[i]=siz[i]=h[i]=dfn[i]=0;//因为判断是z[top+1]，所以要多预处理一位
   //奇怪的是，我在洛谷这么写都没错，难道是洛谷没卡这种情况？
	idx=1,num=flag=dcnt=top=0;
	if(k==1)
	{
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1;i<=n;++i) if(i!=a[i]) return 0;
		return 1;
	}
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) if(i==a[i]) return 0;else add(i,a[i]);
	for(int i=1;i<=n;++i) if(!dfn[i]) dfs(i);
	for(int i=1;i<=num;++i)
	{
		if(siz[i]!=1&&siz[i]!=k) return 0;
		if(siz[i]==k) flag=1;
	}
	return flag;
}
int main()
{
	scanf("%d",&T);
	while(T--)
		if(sol()) puts("YES");
		else puts("NO");
	return 0;
}
 
```

---

## 作者：_299817_ (赞：0)

## Part 0: 前言
为什么最近 CF 总喜欢考一些第一眼看不出来的图论题啊。

~~不是为什么你觉得能一眼看出来~~

## Part 1：主要思路
首先，我们拿到这道题的第一反应是先暴力。

但是，我们发现，即使暴力是正确的，但是时间复杂度也是 $O(n^2)$ 的，过不了这道题。

这时候，我们开始考虑构造 $l$ 数组，但是这个想法也被否决了，因为复杂度是 $O(nk)$ 的。

于是，我们将目光放到数据上面。

我们再看一眼题目给的公式：$a_{l_i} = l_{(i\%k)+1}$

这时候，我们可以想到：$a_i$ 与 $i$ 之间有着很大的联系。

于是，我们考虑以 $a_i$ 建图，接着所有边满足这个条件：$i \to a_i$。

也就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/epb7iias.png)

所有样例都在里面，包括 $k$ 和答案都和答案都标注了。

不难发现，这个图是一个有 $n$ 个点 $n$ 条边图，于是这张图内必然出现环。

我们观察环与 $k$ 的关系，可以发现：当 $k \geq 2$ 时，如果环的大小与 $k$ 不同，那么 $a$ 就是合法的，否则 $a$ 就是不合法的。

我们再考虑 $k=1$ 的情况，不难发现，这个时候只有当所有的 $i$ 满足 $a_i=i$ 时 $a$ 才合法。

具体怎么判环，我这里的方法是用 Tarjan 算法，但是其他算法（比如拓扑排序）也可以。

这里说明一下在这里我们怎么用 Tarjan 判环。

因为我们知道，这张图里面，每一个点只有可能有一条出边。

而环的要求就是 $n$ 个点 $n$ 条边，而且每个点都联通。

既然一个强连通分量里面的所有点都联通，且没有出边，不难发现，这个强连通分量就满足上述的两个条件。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

struct edge{
    int from, to;
    int nxt;
}; // 边

int T;
int n, k;
edge e[100010];
int head[100010]; // 图
int low[100010];
int dfn[100010];
int ins[100010]; // Tarjan 所需的数组
int pos[100010]; // 每个点属于哪个强连通分量
int sz[100010]; // 强连通分量的大小，用于记录环的大小
int out[100010]; // 每个强连通分量发出边数
int sccs; // 强连通分量的数量
int num; // Tarjan 记录遍历顺序
int cnt; // 图
stack<int> st; // Tarjan 所需的栈

void add(int x, int y){ // 加边
    e[cnt].from = x;
    e[cnt].to = y;
    e[cnt].nxt = head[x];
    head[x] = cnt;
    cnt++;
}

void tarjan(int u){ // Tarjan 求强连通分量
    num++;
    low[u] = num, dfn[u] = num;
    ins[u] = 1;
    st.push(u);
    for(int i = head[u]; i != -1; i = e[i].nxt){
        int v = e[i].to;
        if(dfn[v] == 0){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if(ins[v] != 0){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        sccs++; 
        int now, ccnt = 0;
        do{
            now = st.top();
            ins[now] = 0;
            pos[now] = sccs;
            ccnt++;
            st.pop();
        }while(now != u);
        sz[sccs] = ccnt;
    }
}

void init(){ // 注意清空数据
    cnt = 0;
    num = 0;
    for(int i = 1; i <= n; i++){
        head[i] = -1;
        low[i] = 0;
        dfn[i] = 0;
        ins[i] = 0;
        pos[i] = 0;
        out[i] = 0;
        sz[i] = 0;
    }
    sccs = 0;
    while(st.empty() == 0){
        st.pop();
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(head, -1, sizeof(head));
    cin >> T;
    while(T--){
        init();
        cin >> n >> k;
        bool flag0 = 1;
        for(int i = 1; i <= n; i++){
            int u;
            cin >> u;
            if(k == 1 && u != i){
                flag0 = 0;
            }
            add(i, u);
        }
        if(flag0 == 0){ // 特判 k = 1 的情况
            cout << "No" << endl;
            continue;
        }
        for(int i = 1; i <= n; i++){ // Tarjan
            if(dfn[i] == 0){
                tarjan(i);
            }
        }
        for(int i = 0; i < cnt; i++){ // 计算每个强连通分量的出边数量
            if(pos[e[i].from] != pos[e[i].to]){
                out[pos[e[i].from]]++;
            }
        }
        bool flag = 1;
        for(int i = 1; i <= sccs; i++){ // 判断环的大小是不是等于 k
            if(out[i] < 1){
                if(sz[i] != k){
                    flag = 0;
                    break;
                }
            }
        }
        if(flag == 1){ // 输出
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }
    return 0;
}
```


---

