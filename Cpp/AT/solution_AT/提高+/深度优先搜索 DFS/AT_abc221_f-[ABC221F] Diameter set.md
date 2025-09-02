# [ABC221F] Diameter set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc221/tasks/abc221_f

$ N $ 頂点からなる木が与えられます。 頂点は $ 1 $ , $ 2 $ , $ \ldots $ , $ N $ と番号付けられており、 $ 1\leq\ i\leq\ N-1 $ について、$ i $ 本目の辺は頂点 $ U_i $ と頂点 $ V_i $ を結んでいます。 木の直径を $ D $ とするとき、木の頂点のうち $ 2 $ 点以上を選んで赤く塗る方法であって、 赤く塗られたどの頂点の間の距離も $ D $ であるようなものの数を $ 998244353 $ で割った余りを求めてください。

ただし、木の $ 2 $ 頂点の間の距離は一方から他方へ移動するときに用いる辺の本数の最小値であり、 木の直径は任意の $ 2 $ 頂点の間の距離の最大値として定められます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ U_i,V_i\ \leq\ N $
- $ U_i\ \neq\ V_i $
- 入力は全て整数である。
- 与えられるグラフは木である。

### Sample Explanation 1

与えられた木は $ 5 $ 頂点からなり、直径は $ 3 $ です。 $ 2 $ 頂点の組であって、その間の距離が $ 3 $ であるようなものは $ (2,5) $ , $ (3,5) $ しか存在しないため、 条件をみたす塗り方は $ \lbrace\ 2,5\rbrace $ と $ \lbrace\ 3,5\rbrace $ の $ 2 $ 通りとなります。 $ \lbrace\ 2,3,5\rbrace $ は頂点 $ 2 $ と頂点 $ 3 $ の間の距離が $ 2 $ であるため条件をみたさないことに注意してください。

### Sample Explanation 2

直径は $ 2 $ であり、条件をみたす塗り方は $ \lbrace\ 2,3\rbrace $ , $ \lbrace\ 2,4\rbrace $ , $ \lbrace\ 3,4\rbrace $ , $ \lbrace\ 2,3,4\rbrace $ の $ 4 $ 通りとなります。

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
4 5```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4```

### 输出

```
4```

# 题解

## 作者：mojoege (赞：9)

## 分析

前置知识：树的直径。

按照题意，可以先找到这条直径和中心，这里的直径长度指的是经过点数量（包括开头结尾）记为 $d$，而这个中心可能是在一条边上或者点上，所以要按直径分奇偶讨论。对于中心节点唯一并且奇偶性位置的证明可以分类讨论一下，或者模拟一下。

- 偶数，中心在边上：只用计算这条边连着的两个节点符合要求的数量然后乘相乘，这里符合要求指的是到中心（左边或右边的节点）距离为 $\frac{d}{2}-1$ 的点。

![image-20240321184538644](https://cdn.luogu.com.cn/upload/image_hosting/v2ad297x.png)

- 奇数，中心在点上：符合要求的点到中心的距离为 $\lfloor\frac{d}{2}\rfloor$，那么只需要找每棵子树上到根节点为 $\lfloor \frac{d}{2}\rfloor$ 的数量，然后组合一下。具体的，设一棵子树符合要求的节点数量为 $cnt$，那么贡献就是乘上 $cnt+1$，也就是取 $0$ 个到取 $cnt$ 个。统计答案把它们乘起来后还要特判一下，减去全部子树都取 $0$ 个，和只有一个节点的情况。也就是减去 $\sum cnt+1$。

    ![image-20240321184556801](https://cdn.luogu.com.cn/upload/image_hosting/b3logkvx.png)

不开 `long long` 见祖宗。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int n, maxd, l, r, tmp, cnt, ans = 1;
int fa[200005];
vector<int> g[200005];

void dfs(int x, int f, int st){//找直径
    fa[x] = f;
    if (st > maxd) maxd = st, tmp = x;
    for (int i = 0; i < g[x].size(); i++){
        int v = g[x][i];
        if (v == f) continue;
        dfs(v, x, st + 1);
    }
}

void dfs1(int x, int f, int st){//计算 cnt
    if (st == tmp) cnt++;
    for (int i = 0; i < g[x].size(); i++){
        int v = g[x][i];
        if (v == f) continue;
        dfs1(v, x, st + 1);
    }
}

int main(){
    cin >> n;
    for (int i = 1, u, v; i < n; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0, 1);//跑两边 dfs 找树的直径
    l = tmp, tmp = maxd = 0;
    dfs(l, 0, 1);//跑完这次 dfs maxd 就已经是直径长度了
    r = tmp;
    if (maxd % 2){//分奇偶讨论
        int x = r;
        for (int i = 1; i <= maxd / 2; i++) x = fa[x];//还原中心
        tmp = maxd / 2;//这里可以模拟一下理解
        for (int i = 0; i < g[x].size(); i++, cnt = 0){
            dfs1(g[x][i], x, 1);//求这一个子树下有多少个节点满足要求
            ans = ans * (cnt + 1) % mod;//乘法原理
        }
        dfs1(x, 0, 0);//处理 cnt 的和
        ans -= cnt + 1;//特判掉不可能的情况
    }
    else{
        int x = r;
        for (int i = 1; i <= maxd / 2 - 1; i++) x = fa[x];//还原中心（左边或右边的节点）
        tmp = maxd / 2 - 1, cnt = 0;
        dfs1(x, fa[x], 0);//这里 fa[x] 就是这条边上的另一个点
        ans = ans * cnt % mod, cnt = 0;//计算贡献
        dfs1(fa[x], x, 0);
        ans = ans * cnt % mod;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：EuphoricStar (赞：6)

显然，选出的每两个点都要组成一条直径。

进一步发现，设直径点数为 $x$，如果 $x \nmid 2$，所有直径都会在中点重合，否则会在连接两个中点的边重合。简单证一下，如果有两条直径不在中点或中边重合，那么：

- 它们不可能不重合，要不然就不会成为直径了；
- 它们在除了中点和中边的地方重合，此时长的两端构成了一条新的直径。

然后考虑计数。

- 如果重合部分是点 $u$，答案为 $\prod\limits_{v, (u,v) \in E} (f_v + 1) - a - 1$，其中 $f_v$ 为 $u$ 为根时 $v$ 的子树中有多少个点与 $u$ 的距离为 $\frac{x-1}{2}$，$a$ 为整棵树中有多少个点与 $u$ 的距离为 $\frac{x-1}{2}$。大概意思就是每个点可选可不选，最后减去 $|S| \le 1$ 的 $S$。

- 如果重合部分是边 $(u,v)$，答案为 $f_u \times g_v$，其中 $f_u$ 为以 $v$ 为根时 $u$ 的子树中有多少个点到 $u$ 距离为 $\frac{x}{2} - 1$，$g_v$ 为以 $u$ 为根时 $v$ 的子树中有多少个点到 $v$ 距离为 $\frac{x}{2} - 1$。

时间复杂度 $O(n)$。

[code](https://atcoder.jp/contests/abc221/submissions/41291249)

---

## 作者：TSY48 (赞：1)

**解题思路**

按照题意得，任选出的两个点均为一条直径。不难发现，所有直径的中点均为相同。

则考虑中点的每个子树，按照上面的结论，不难发现每个子树中只能取一个点且此点到中点的距离为直径长度的一半（如果长度为偶数，则考虑其两端点的子树。这里直径的长度为直径上的每个点）。

贡献为：

令子树内每个满足条件的点的数为 $cnt_i$。

答案为：
$$
Ans = \begin{cases}
  \prod_{i=1}^k(cnt_i+1)-\sum_{i=1}^kcnt_i-1 & dis为奇数 \\
  \prod_{i=1}^kcnt_i & dis为偶数 \\
\end{cases}
$$
注：$k$ 为中点子树个数，直径为偶数的时候，$k=2$。$dis$ 为直径长度。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define pf push_front
#define m_p make_pair
#define str string
#define lowbit(x) (x&(-x))
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define siz(x) (int)x.size()
#define int long long
typedef pair<int,int> pi;
//typedef __int128 it;
const int Maxn=2e5+10;
const int inf=0x3f;
const int mod=998244353;
int f[Maxn];
vector<int> e[Maxn];
int st,ed;
int cnt;
int mx=1,mxd=1,d;
inline void dfs1(int u,int fa,int step){
    f[u]=fa;
    if(step>mx){
        mx=step;st=u;
    }
    for(auto v:e[u]){
        if(v==fa) continue;
        dfs1(v,u,step+1);
    }
}
inline void dfs2(int u,int fa,int step){
    f[u]=fa;
    if(step>mxd){
        mxd=step;ed=u;
    }
    for(auto v:e[u]){
        if(v==fa) continue;
        dfs2(v,u,step+1);
    }
}
inline void dfs3(int u,int fa,int step){
    if(step==d){
        cnt++;
        return ;
    }
    for(auto v:e[u]){
        if(v==fa) continue;
        dfs3(v,u,step+1);
    }
}
signed main()
{
    int n;
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        e[u].pb(v);e[v].pb(u);
    }
    dfs1(1,0,1);
    dfs2(st,0,1);
    // printf("%lld %lld\n",st,ed);
    // printf("%lld\n",mxd);
    if(mxd&1){
        int ans=1;
        int mid=ed;
        for(int i=1;i<=mxd/2;i++) mid=f[mid];
        d=mxd/2;
        int sum=0;
        for(auto v:e[mid]){
            dfs3(v,mid,1);
            ans=(ans*(cnt+1))%mod;
            sum=(cnt+sum)%mod;
            cnt=0;
        }
        ans=(ans-(sum+1)+mod)%mod;
        printf("%lld",ans);
    }
    else{
        int ans=1;
        int mid=ed;
        for(int i=1;i<mxd/2;i++) mid=f[mid];
        d=(mxd-1)/2;
        // printf("%lld\n",f[mid]);
        dfs3(mid,f[mid],0);
        ans=(ans*cnt)%mod;cnt=0;
        dfs3(f[mid],mid,0);
        ans=(ans*cnt)%mod;
        printf("%lld",ans);
    }
}
```

---

## 作者：红黑树 (赞：1)

[可能更好的阅读体验](https://rbtr.ee/abc-221-f)

## [题意](https://atcoder.jp/contests/abc221/tasks/abc221_f)
给定一颗 $n$ 个点的树，求使得顶点集合 $S$ 中任意两个顶点的距离恰好为树的直径的长度的集合个数，对 $998244353$ 取模，且 $\lvert S\rvert \geq 2$。

$2 \leq n \leq 2\times 10^5$

## 题解
首先需要知道一个性质：树的所有直径的中点重合。

但是有个小问题，如果有两个点都是中点咋办？其实可以分讨一下解决。另一种方法是在每两条边中间都加一个点，听不懂可以类比一下字符串回文，我们为了避免偶回文，会在每两个字符之间插一个其它字符。

我们可以求出这个中点，把它作为根。这样，所有直径都必然经过根。现在我们考虑计算答案。我们需要找到两个能凑成直径的点，算匹配个数。

能凑成直径的点，到根的深度是树直径的一半。因此我们可以快速计算。

于是计算每个根的直接子树里，满足要求的叶子的个数，记为 $t_i$，答案即为：

$$\left(\prod\left(t_i + 1\right)\right) - \left(\sum t_i\right) - 1$$

## 代码
```cpp
/* Please submit with C++17! It's best to use C++20 or higher version.
 * No header file and no RBLIB (https://git.rbtr.ee/root/Template).
 * By Koicy (https://koicy.ly)
 * Email n@rbtr.ee
 * I've reached the end of my fantasy.

         __    __                             __         _
   _____/ /_  / /_________  ___              / /______  (_)______  __
  / ___/ __ \/ __/ ___/ _ \/ _ \   ______   / //_/ __ \/ / ___/ / / /
 / /  / /_/ / /_/ /  /  __/  __/  /_____/  / ,< / /_/ / / /__/ /_/ /
/_/  /_.___/\__/_/   \___/\___/           /_/|_|\____/_/\___/\__, /
                               SIGN                         /___*/
#ifndef XCODE
constexpr bool _CONSOLE = false;
#else
constexpr bool _CONSOLE = true;
#endif
#define __NO_MAIN__ false
#define __ENABLE_RBLIB__ true
constexpr bool _MTS = false, SPC_MTS = false;
constexpr char EFILE[] = "";
#define FULL(arg) arg.begin(), arg.end()

// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  constexpr tp mod = 998244353;
  tp n = bin;
  vector<vetp> e(n * 2 + 1);
  for (tp i = 2; i <= n; ++i) {
    tp u, v; bin >> u >> v;
    e[u].push_back(n + i);
    e[n + i].push_back(v);
    e[v].push_back(n + i);
    e[n + i].push_back(u);
  }
  auto dfs = [&](auto $, tp x, tp f, tp cnt) -> pair<tp, tp> {
    tp mav = cnt, tar = x;
    for (auto& i : e[x]) {
      if (i == f) continue;
      auto ret = $($, i, x, cnt + 1);
      if (ret.first >= mav) {
        mav = ret.first;
        tar = ret.second;
      }
    }
    return make_pair(mav, tar);
  };
  tp t1 = dfs(dfs, 1, 1, 0).second;
  tp t2 = dfs(dfs, t1, t1, 0).second;
  vetp lst;
  auto foo = [&](auto $, tp x, tp f, tp tar) -> bool {
    if (x == tar) {
      lst.push_back(x);
      return true;
    }
    for (auto& i : e[x]) {
      if (i == f) continue;
      if ($($, i, x, tar)) {
        lst.push_back(x);
        return true;
      }
    }
    return false;
  };
  foo(foo, t2, t2, t1);
  tp rt = lst[lst.size() / 2];
  tp tar = 0;
  auto bar = [&](auto $, tp x, tp f, tp dep) -> pair<tp, tp> {
    tp mav = dep, cnt = 1;
    tp tgt = 1;
    for (auto& i : e[x]) {
      if (i == f) continue;
      auto ret = $($, i, x, dep + 1);
      if (ret.first > mav) {
        mav = ret.first;
        cnt = ret.second;
        tgt = ret.second + 1;
      } else if (ret.first == mav) {
        cnt += ret.second;
        tgt = tgt * (ret.second + 1) % mod;
      }
    }
    bg(x, mav, cnt);
    if (x == rt) tar += tgt - cnt - 1;
    return make_pair(mav, cnt);
  };
  bar(bar, rt, rt, 0);
  bin << tar % mod << '\n';
  return 0;
}

void MIST() {
}

// :\ */
```

---

## 作者：majoego (赞：1)

本题要引入一个知识点，就是树的中心。

因为我们每一次选的集合，每两个点都构成一条直径。我们发现，如果直径上有 $k$ 个点，那么如果 $k$ 是奇数，那么所有直径都穿过这个中心，如果它为偶数，那么会有两个中心，那么这个直径会穿过两个中心之间的边。

所以，奇偶处理的方式就不同，得要进行分讨。

先放一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yj0x1q9b.png)

奇数情况（如图二）：

- 红色的点为单个的树的中心，所有蓝色节点就是直接它的儿子。我们选两个端点作为直径的两端点，显然不能在都在同一个蓝色节点的子树内，如果两个点在同一个蓝色节点的子树内，那么，显然会有更短的方案（他们连的蓝色的点然后就连回去了）。所以，我们选的两两个点，都不能出现在同一个子树内。于是，我们可以统计每一个蓝色节点的子树内有多少个是有直径长度的一半，这样，将所有数量乘法原理在一起就好了。为什么是直径的一半呢？因为两个一半就可以拼成一个完整的直径。

偶数情况（如图一）：

- 两个蓝色的节点都是中心，他们之间有一条连边，所有的直径都会经过这条边。所以说，我们只需要统计左边（也就是中心 $1$ 的子树）和右边（中心 $2$ 的子树）。这两边里面的直径一半的个数直接相乘那就是答案，原理与奇数情况是类似的。

我们先要处理出中心，然后从中心再往外 DFS 即可。

[link](https://atcoder.jp/contests/abc221/submissions/51475690)。

---

## 作者：ATION001 (赞：0)

分类讨论。

首先求出树的中心。

如果树的中心数量为 $1$，那么求出以树的中心直接连接的点为根的子树中**有多少个叶子节点在树的直径上**。

设 $siz_i$ 表示以 $i$ 为根的子树有多少个叶子节点在树的直径上（从树的中心开始遍历）。

假设集合 $S$ 记录的是所有与树的中心有直接边连接的点。

那么答案为（$a$ 表示树的中心，$ans$ 表示答案）：

$$
ans=(\prod_{i=1}^{|S|} siz_{S_i})-siz_a-1 \bmod 998244353
$$

即答案等于，每个子树满足要求的叶子节点的个数的乘积（$\prod_{i=1}^{|S|} siz_{S_i}$）减去，所有满足要求的叶子节点的个数（$siz_a$）减去 $1$。

对于树的中心的数量等于 $2$ 的情况（设第 $1$ 个树的中心为 $a$，第 $2$ 个树的中心为 $b$）：

显而易见，答案等于以 $a$ 为根的子树的叶子节点的个数（下文中用 $sum$ 表示）乘以以 $b$ 为根的子树的叶子节点的个数（下文中用 $tmp$）。

用公式表示为：

$$
ans=(sum\times tmp)\bmod 998244353
$$

最后需要注意的是，**需要开 `long long`**。
### 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int n,ans=1,minn=1e18,dp[200005],dp1[200005],A[200005],up[200005],dep[200005],max_dep,siz[200005];
vector<int>v[200005],st;
void dfs(int x,int fa){
	for(auto z:v[x]){
		if(z!=fa){
			dfs(z,x);
			if(dp[x]<=dp[z]+1){
				dp1[x]=dp[x];
				dp[x]=dp[z]+1;
			}else if(dp1[x]<=dp[z]+1){
				dp1[x]=dp[z]+1;
			}
		}
	}
}
void dfs_up(int x,int fa){
	for(auto z:v[x]){
		if(z!=fa){
			up[z]=up[x]+1;
			if(dp[x]==dp[z]+1){
				up[z]=max(up[z],dp1[x]+1);
			}else{
				up[z]=max(up[z],dp[x]+1);
			}
			dfs_up(z,x);
		}
	}
}
void dfs1(int x,int fa,int len){
	dep[x]=len;
	max_dep=max(max_dep,dep[x]);
	for(auto z:v[x]){
		if(z!=fa){
			dfs1(z,x,len+1);
		}
	}
}
void dfs2(int x,int fa,int dep){
	if(v[x].size()==1&&fa!=-1&&dep==max_dep){
		siz[x]=1;
		return;
	}
	for(auto z:v[x]){
		if(z!=fa){
			dfs2(z,x,dep+1);
			siz[x]+=siz[z];
		}
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	A[0]=1;
	for(int i=1;i<=n;i++){
		A[i]=(A[i-1]*i)%mod,dep[i]=-1;
	}
	for(int i=1,x,y;i<n;i++){
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,-1);
	dfs_up(1,-1);
	for(int i=1;i<=n;i++){
		if(max(dp[i],up[i])<minn){
			minn=max(dp[i],up[i]);
			st.clear();
			st.push_back(i);
		}else if(max(dp[i],up[i])==minn){
			st.push_back(i);
		}
	}
	if(st.size()==1){
		fill(dep,dep+n+1,-1);
		dfs1(st[0],-1,0);
		dfs2(st[0],-1,0);
		for(auto z:v[st[0]]){
			ans=(ans*(siz[z]+1))%mod;
		}
		ans=(ans-siz[st[0]]-1)%mod;
	}else{
		fill(dep,dep+n+1,-1);
		dfs1(st[0],st[1],0);
		int txt=0,tot=0;
		for(int i=1;i<=n;i++){
			txt+=(dep[i]==max_dep);
		}
		fill(dep,dep+n+1,-1);
		max_dep=0;
		dfs1(st[1],st[0],0);
		for(int i=1;i<=n;i++){
			tot+=(dep[i]==max_dep);
		}
		ans=(txt*tot)%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：yr409892525 (赞：0)

## [AT_abc221_f [ABC221F] Diameter set](https://www.luogu.com.cn/problem/AT_abc221_f)
发现选出来的数**任意**两个的距离都为 $d$，即每两个节点都组成一条直径，又知道所有直径都经过树的中心，所以选出来的集合任意一点到树的中心的距离为 $\frac{d}{2}$。           
由于 $d$ 有可能为奇数，所以我们可以在每一条边的中间加入一个节点使 $d$ 一定为偶数。             
然后就可以从树的中心开始搜索，令 $dp_i$ 代表以树的中心为根节点 $i$ 的子树有多少个距离树的中心长度为 $\frac{d}{2}$。            
则答案为 $\prod\limits_{v\in son_u} (dp_v+1)- \sum\limits_{v\in son_u} dp_v-1$，其中 $son_u$ 代表 $u$ 的所有直接连边的儿子。              
也就是 $u$ 的每个儿子都有 $dp_v+1$ 种选法，减去直选一个的和不选的就是答案。             

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,inf=1e18,mod=998244353;
int n;
vector<int> op[N];
int down[N][2],up[N],son[N];
void dfs1(int u,int fa){
    for(int v:op[u]){
        if(v!=fa){
            dfs1(v,u);
            int x=down[v][0]+1;
            if(x>down[u][0]){
                down[u][1]=down[u][0];
                down[u][0]=x;
                son[u]=v;
            }else if(x>down[u][1]){
                down[u][1]=x;
            }
        }
    }
}
void dfs2(int u,int fa){
    for(int v:op[u]){
        if(v!=fa){
            if(son[u]==v){
                up[v]=max(up[u],down[u][1])+1;
            }else{
                up[v]=max(up[u],down[u][0])+1;
            }
            dfs2(v,u);
        }
    }
}
int ans=inf;
int dp[N];
int dfs3(int u,int fa,int dis){
    if(dis==ans){
        return dp[u]=1;
    }
    int ans=0;
    for(int v:op[u]){
        if(v!=fa){
            ans+=dfs3(v,u,dis+1);
        }
    }
    return dp[u]=ans;
}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        op[u].push_back(i+n);
        op[i+n].push_back(u);
        op[v].push_back(i+n);
        op[i+n].push_back(v);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n+n-1;i++){
        ans=min(ans,max(down[i][0],up[i]));
    }
    for(int i=1;i<=n+n-1;i++){
        if(max(down[i][0],up[i])==ans){
            dfs3(i,0,0);
            int sum=1,k=0;
            for(int j:op[i]){
                sum*=(dp[j]+1);
                sum%=mod;
                k+=dp[j];
            }
            cout<<((sum-k-1)%mod+mod)%mod;
            return 0;
        }
    }
	return 0;
}
```

---

