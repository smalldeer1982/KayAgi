# Li Hua and Tree

## 题目描述

Li Hua has a tree of $ n $ vertices and $ n-1 $ edges. The root of the tree is vertex $ 1 $ . Each vertex $ i $ has importance $ a_i $ . Denote the size of a subtree as the number of vertices in it, and the importance as the sum of the importance of vertices in it. Denote the heavy son of a non-leaf vertex as the son with the largest subtree size. If multiple of them exist, the heavy son is the one with the minimum index.

Li Hua wants to perform $ m $ operations:

- "1 $ x $ " ( $ 1\leq x \leq n $ ) — calculate the importance of the subtree whose root is $ x $ .
- "2 $ x $ " ( $ 2\leq x \leq n $ ) — rotate the heavy son of $ x $ up. Formally, denote $ son_x $ as the heavy son of $ x $ , $ fa_x $ as the father of $ x $ . He wants to remove the edge between $ x $ and $ fa_x $ and connect an edge between $ son_x $ and $ fa_x $ . It is guaranteed that $ x $ is not root, but not guaranteed that $ x $ is not a leaf. If $ x $ is a leaf, please ignore the operation.

Suppose you were Li Hua, please solve this problem.

## 说明/提示

In the first example:

The initial tree is shown in the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797D/9987ad8dcf3fa22fea3d32776e957eb49f799b18.png)The importance of the subtree of $ 6 $ is $ a_6+a_7=2 $ .

After rotating the heavy son of $ 3 $ (which is $ 6 $ ) up, the tree is shown in the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797D/d9aa4837f3bc9a3bc8a0cab55eb204e43f3ef9ba.png)The importance of the subtree of $ 6 $ is $ a_6+a_3+a_7=3 $ .

The importance of the subtree of $ 2 $ is $ a_2+a_4+a_5=3 $ .

## 样例 #1

### 输入

```
7 4
1 1 1 1 1 1 1
1 2
1 3
2 4
2 5
3 6
6 7
1 6
2 3
1 6
1 2```

### 输出

```
2
3
3```

## 样例 #2

### 输入

```
10 14
-160016413 -90133231 -671446275 -314847579 -910548234 121155052 -359359950 83112406 -704889624 145489303
1 6
1 10
10 8
1 4
3 4
2 7
2 5
3 2
9 8
1 4
2 2
2 4
1 4
1 10
2 10
1 9
1 6
2 8
2 10
1 5
1 8
1 1
2 5```

### 输出

```
-2346335269
-314847579
-476287915
-704889624
121155052
-1360041415
228601709
-2861484545```

# 题解

## 作者：FFTotoro (赞：7)

## 前言

难得一好水 $*1900$……

警示后人：翻译中说的“点数”指的是**子树大小**，我开始时把这玩意读错了，WA 了 $2$ 发……

## 解法

本题需要使用 STL `std::set` 维护树上操作。

符号规定：记一个结点 $x$ 的父亲为 $f_x$，子树大小为 $e_x$，子树和为 $s_x$。

先跑一遍预处理 dfs，把还未进行任何操作时所有结点的父亲、子树大小、子树和算出来，便于后续维护。

接着对于每个结点开一个 `set`，`set` 中每个元素代表它的一个儿子 $x$，里面存一个二元组 `pair`，第一关键字存的是该儿子的子树大小 $e_x$（但是因为 `set` 默认比较方式是 `less<>`，所以较小的元素会排在前，插入时对 $e_x$ 取一个相反数即可），第二关键字即为该儿子的结点编号 $x$。

对于每一次操作，如果是操作 $1$，直接输出 $s_x$，否则执行以下的算法流程：

1. 找出 $x$ 的重儿子（即 `set` 中存储的第一个元素），记为 $h$；

2. 从 $x$ 的 `set` 中删除 $h$；

3. 从 $f_x$ 的 `set` 中删除 $x$；

4. 更改 $e_x,e_h,s_x,s_h$，具体地：

   - $e_x\leftarrow e_x-e_h$（从 $x$ 中减掉 $h$ 对子树大小的贡献）；
   
   - $e_h\leftarrow e_h+e_x$（$x$ 成为 $h$ 的儿子，$h$ 的子树大小加上上一次操作完后的 $e_x$）；
   
   - $s_x\leftarrow s_x-s_h$（从 $x$ 中减掉 $h$ 对子树和的贡献）；
   
   - $s_h\leftarrow s_h+s_x$（$x$ 成为 $h$ 的儿子，$h$ 的子树和加上上一次操作完后的 $s_x$）。

5. 在 $h$ 的 `set` 中加入 $x$；

6. 在 $f_x$ 的 `set` 中加入 $h$；

7. 更改 $f_x$ 和 $f_h$。

注意，以上的流程顺序不可以更改，把有些操作安排在前更便于引用未更改的信息。

时间复杂度 $O(n+m\log n)$，可以通过本题。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> g[100001];
set<pair<int,int> > k[100001];
int a[100001],s[100001],e[100001],f[100001];
void dfs(int u,int r){
  s[u]=a[u],e[u]=1,f[u]=r;
  for(int i:g[u])
    if(i!=r){
      dfs(i,u),s[u]+=s[i],e[u]+=e[i];
      k[u].emplace(-e[i],i);
    }
} // dfs 预处理所有信息
main(){
  ios::sync_with_stdio(false);
  int n,m; cin>>n>>m;
  for(int i=1;i<=n;i++)cin>>a[i];
  for(int i=1;i<n;i++){
    int u,v; cin>>u>>v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  dfs(1,0);
  while(m--){
    int op,x; cin>>op>>x;
    if(op==1)cout<<s[x]<<endl;
    else if(!k[x].empty()){
      int h=k[x].begin()->second;
      k[f[x]].erase(make_pair(-e[x],x));
      k[x].erase(make_pair(-e[h],h));
      e[x]-=e[h],e[h]+=e[x],s[x]-=s[h],s[h]+=s[x];
      k[h].emplace(-e[x],x);
      k[f[h]=f[x]].emplace(-e[h],h);
      f[x]=h;
    } // 按上面的流程模拟
  }
  return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：3)

我们发现，题目其实只需要我们维护这些值。

+ $fa_x$：$x$ 的父亲。
+ $p_x$：以 $x$ 为根的点权和。
+ $son_x$：$x$ 的重儿子。

对于 $1$ 操作，输出 $p_x$。

对于 $2$ 操作，我们依次考虑。

设 $x$ 的重儿子是 $y$，父亲是 $z$。

首先，$fa_y\gets z$，$fa_x\gets y$，这是极其显然的。

然后，如何修改受到影响的 $p_x,p_y,p_z$？

我们随便画一个图：

[![p91hfTs.png](https://s1.ax1x.com/2023/04/29/p91hfTs.png)](https://imgse.com/i/p91hfTs)

对 $3$ 进行 $2$ 操作之后的结果：

[![p91hWwj.png](https://s1.ax1x.com/2023/04/29/p91hWwj.png)](https://imgse.com/i/p91hWwj)

我们发现，阴影部分的节点的 $p$ 值均不变。

$p_3$ 现在没有 $p_6$ 的贡献，$p_6$ 现在有了 $p_3$ 的贡献。

则 $p_3\gets p_3-p_6$，然后 $p_6\gets p_6+p_3$。

[![p91h4kn.png](https://s1.ax1x.com/2023/04/29/p91h4kn.png)](https://imgse.com/i/p91h4kn)

最后是重头戏 $son_x$ 的维护，我们发现每次 $2$ 操作下，$x,y,z$ 的重儿子都可能发生改变，虽然我们可以像维护 $p$ 一样维护以 $i$ 为根的子树大小 $q_i$，但不可能每次都重新求一遍 $son_x$。

那我们把每个点的儿子极其 $q_i$ 存到一个 `std::set` 中，这样，每次 $2$ 操作时，如果删去的是重儿子，新的重儿子也能通过 `.begin()` 再次取到。

那么，定义一个类存储 $\{i,q_i\}$，$q_i$ 为第一关键词从大到小，$i$ 为第二关键字从小到大。

预处理要将点丢进父亲的 `std::set`，所以复杂度是 $O(n)\times O(\log n)=O(n\log n)$。

然后每次询问时，我们只需要在几个 `std::set` 中删去或添加某些节点（画图辅助理解），所以操作的复杂度是 $O(m)\times O(\log n)=O(m\log n)$。

总复杂度 $O((n+m)\log n)$，$n,m$ 同阶，视作 $O(n\log n)$。

最后一点，$2$ 操作一定要判叶子结点！！！
```cpp
#include <set>
#define rep(i,l,r) for(i=l;i<=r;++i)
#include <vector>
#include <stdio.h>
using ll=long long;
class stype
{
public:
	int id,tot;
	stype(int x=0,int y=0):id(x),tot(y)
	{}
	inline const bool operator<(const stype &other)const
	{
		return tot!=other.tot ? tot>other.tot : id<other.id;
	}
};
const int N=200005;
std::vector<int> e[N];
ll p[N],cnt[N],fa[N],v[N];
std::set<stype> q[N];
inline void pre(int id,int fat)
{
	p[id]=v[id];
	fa[id]=fat;
	cnt[id]=1;
	for(auto nxt:e[id])
	{
		if(nxt==fat)
			continue;
		pre(nxt,id);
//		printf("%d %d -> %d %d\n",id,fat,nxt,id);
		p[id]+=p[nxt];
		cnt[id]+=cnt[nxt];
		q[id].insert(stype(nxt,cnt[nxt]));
	}
	return ;
}
inline void solve(int op,int v)
{
	static int w;
	if(op==1)
		printf("%lld\n",p[v]);
	else
	{
/*
首先找出 v 的重儿子 w
然后将 q[v] q[fa[v]] 内改变的点删去。
其次处理 cnt[v] cnt[w] p[v] p[w] 的变化
最后将新的儿子 insert，改变 fa[w] fa[v]。
*/
        if(q[v].empty())
            return ;
		w=(*q[v].begin()).id;
		q[v].erase(stype(w,cnt[w]));
		q[fa[v]].erase(stype(v,cnt[v]));
		cnt[v]-=cnt[w];
		cnt[w]+=cnt[v];
		p[v]-=p[w];
		p[w]+=p[v];
		q[w].insert(stype(v,cnt[v]));
		fa[w]=fa[v];
		q[fa[w]].insert(stype(w,cnt[w]));
		fa[v]=w;
	}
}
int main()
{int n,m,i,opt,x,u,v,rt=1;;
	scanf("%d %d",&n,&m);
	rep(i,1,n)
		scanf("%lld",::v+i);
	rep(i,2,n)
	{
		scanf("%d %d",&u,&v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	pre(rt,0);//puts("ok");
	while(m--)
	{
		scanf("%d %d",&opt,&x);
		solve(opt,x);
	}
	return 0;
}
```

---

## 作者：Y_QWQ_Y (赞：1)

一道很好的 set 练手题，但是没有蓝。

### 浅谈思路
看一下操作，我们可以把操作理解为：将 $x$ 的子树去掉重子节点及其子树之后，将 $x$ 的重子节点及其子树连接 $x$ 的父节点，然后，把去掉 $x$ 的重子节点的子树连接 $x$ 的重子节点。

当然，这样讲的还是有点抽象，我们来画图。

以样例 1 为例。

这是原树：

![](https://cdn.luogu.com.cn/upload/image_hosting/2w5u3yao.png)

这是修改后的树：

![](https://cdn.luogu.com.cn/upload/image_hosting/b9fhe6jr.png)

可见，操作就是先将 3 和他的父亲，3 的重子节点的子树分开，形成一块，将 3 的重子节点及其子树与它的父亲连接，再将原先割出的以 3 为根的子树与 3 的重子节点连接。

更形象的，我们可以认为是他原点权和减去它的重子节点的点权和，它的重子节点的点权和加上它减去重子节点点权和之后的点权和。

即
$$sum_x\to sum_x-sum_y$$

$$sum_y\to sum_y+sum_x$$

$sum_x$ 表示以 $x$ 为根的点权和。

但是，我们还需要维护每个节点的重子节点，可以用 set，按照子树大小排序。所以，对于每一个节点，都要统计它的子树大小，在操作时变化同 $sum$ 数组。同时，需要统计节点的父亲，用于插入和删除。

只要想到用 set 维护重子节点，并且推出贡献的变化，这题也就迎刃而解了。

### 部分代码
给出操作部分的伪代码，请自行计算点权和以及子树大小，在计算时把 $x$ 的子节点加入 $x$ 的集合中。
```
定义 y 为重子节点(s[x].begin ()->id)
在 x 的父亲的集合里删除 x，在 x 的集合里删除 y
更改点权和以及子树大小的贡献
在 x 的父亲里插入 y，在 y 里插入 x
修改 y 的父亲为 x 的父亲，修改 x 的父亲为 y
```

因为用了 set，所以时间复杂度为：预处理 $\Theta(n\log n)+$ 操作 $\Theta(m\log n)\approx\Theta(n\log n)$。

温馨提示：set 的优先级是按从小到大，重载运算符请重载 $<$，在里面可以写从大到小的排序，并千万记得，要特判子树大小相等的情况。

[$\color{white}{我很良心的好吧，不要骂我。}$](https://www.luogu.com/paste/uon2kz86)

---

## 作者：Anamnesis (赞：1)

操作的维护思路其他题解已经讲的很清楚了，按照题意模拟有关节点的信息更新即可。这里有一个略微不同的实现。

题解区为了维护删除儿子的操作都使用了 `std::set`，但实际上我们不删除儿子也可以。这是因为，一个节点应当被从其父节点的儿子集合中删除这一事件的数量是 $\mathcal{O}(m)$ 级别的，也就是节点会在儿子集合中重复出现的总次数是 $\mathcal{O}(m)$ 级别的。

那么我们只要在每次取出 $hson$ 时暴力检查当前 $hson$ 是否没被旋转走即可：如果旋转走了，就换下一个试试。这个复杂度是正确的。


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
  int n = read(), m = read();
  vector<i64> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  vector<vector<int>> e(n);
  for (int i = 0; i + 1 < n; ++i) {
    int u = read() - 1, v = read() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (auto& vec : e) {
    sort(all(vec));
  }

  vector<int> sz(n, 1), p(n);
  vector<i64> f(a);
  vector<priority_queue<array<int, 2>>> ch(n);
  function<void(int)> dfs = [&](int u) {
    for (int v : e[u]) {
      if (v == p[u]) {
        continue;
      }
      p[v] = u;
      dfs(v);
      sz[u] += sz[v];
      f[u] += f[v];
      ch[u].push({sz[v], -v});
    }
  };
  dfs(0);
  while (m--) {
    int opt = read(), x = read() - 1;
    if (opt == 1) {
      cout << f[x] << '\n';
    } else {
      if (sz[x] == 1) {
        continue;
      }

      int hson = -ch[x].top()[1];
      ch[x].pop();

      while (!ch[x].empty() && p[hson] != x) {
        hson = -ch[x].top()[1];
        ch[x].pop();
      }
      if (p[hson] != x) {
        continue;
      }

      sz[x] -= sz[hson];
      sz[hson] += sz[x];
      f[x] -= f[hson];
      f[hson] += f[x];
      ch[p[x]].push({sz[hson], -hson});
      ch[hson].push({sz[x], -x});
      p[hson] = p[x];
      p[x] = hson;
    }
  }
  return 0;
}
```

---

## 作者：spider_oyster (赞：1)

考虑对 $u$ 节点进行操作 2 会有哪些变化。

设 $v=son[u]$，即 $u$ 的重儿子。

设 $u$ 的子树为 $T_u$，$v$ 的子树为 $T_v$。

则操作 2 本质是 $T_u-=T_v$，$T_v+=T_u$（加法可理解为合并）。

据此，更新子树大小，权值和。

然后每个节点的重儿子用 $set$ 维护一下。

设 $p$ 为 $u$ 的父亲，则 $set_p$ 也需要维护。

注意 $T_p$ 子树大小和权值和不会改变，只是把 $p$ 的一个儿子从 $u$ 变为了 $v$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N=1e5+5;
int n,m,a[N],sz[N],fa[N],son[N];
ll w[N];
struct node{
    int sz,id;
    bool operator<(const node &x)const{
        if(sz==x.sz) return id<x.id;
        return sz>x.sz;
    }
};
set<node> s[N];
vector<int> G[N];
 
void dfs(int u,int f)
{
    w[u]=a[u],sz[u]=1,fa[u]=f;
    for(int v:G[u])
    {
        if(v==f) continue;
        dfs(v,u);
        w[u]+=w[v],sz[u]+=sz[v];
        s[u].insert({sz[v],v});
        if(sz[v]>sz[son[u]]||(sz[v]==sz[son[u]]&&v<son[u])) son[u]=v;
    } 
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++) cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
    dfs(1,0);
    while(m--)
    {
        int op,u;
        cin>>op>>u;
        if(op==1) cout<<w[u]<<'\n';
        else
        {
            int v=son[u],p=fa[u];
            if(!v) continue;
            fa[u]=v,fa[v]=p;
            s[p].erase({sz[u],u});
            sz[u]-=sz[v],w[u]-=w[v];
            s[u].erase({sz[v],v});
            son[u]=s[u].empty()?0:s[u].begin()->id;
            sz[v]+=sz[u],w[v]+=w[u];
            s[v].insert({sz[u],u});
            son[v]=s[v].begin()->id;
            s[p].insert({sz[v],v});
            son[p]=s[p].begin()->id;
        }
    }
}
```


---

## 作者：Gao_yc (赞：1)

# Solution：

首先发现我们要维护每个点 $x$ 的 $sum_x$（子树点权和），$son_x$（重儿子），$sz_x$（子树大小），$fa_x$。

仔细模拟，发现每次对点 $x$ 的操作二，设操作前的 $fa_x,son_x$ 分别为 $f,sn$，那么会影响到的只有 $son_f,sz_x,fa_x,son_x,sum_x,fa_{sn}$ 的信息。

唯一难点是 $son_x$ 如何维护：只要对每个点，开一个 `set`，维护每个儿子的子树大小就好了。

具体实现可以看代码。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,m,sz[N],a[N],fa[N];
ll sum[N];
struct node{
    int id,val;
	bool operator <(const node &A)const{return val>A.val||(val==A.val&&id<A.id);}
};
set<node> s[N];
vector<int> G[N];
void dfs(int x){
    sum[x]=a[x];sz[x]=1;
    for(int y:G[x]){
        if(y==fa[x]) continue;
        fa[y]=x;
        dfs(y);
        sum[x]+=sum[y];sz[x]+=sz[y];
        s[x].insert((node){y,sz[y]});
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",a+i);
    for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
    dfs(1);
    // for(int i=1;i<=n;++i) printf("%lld ",sum[i]);puts("");
    // for(int i=1;i<=n;++i) printf("%d ",sz[i]);puts("");
    int op,x,sn,f,ss;ll ssu;
    set<node>::iterator it;
    while(m--){
        scanf("%d%d",&op,&x);
        if(op==1) printf("%lld\n",sum[x]);
        else{
            if(s[x].empty()) continue;
            it=s[x].begin();
            f=fa[x];sn=(*it).id;
            it=s[f].find((node){x,sz[x]});
            s[f].erase(*it);
            s[f].insert((node){sn,sz[x]});
            ss=sz[sn];ssu=sum[sn];sz[sn]=sz[x];sum[sn]=sum[x];
            sz[x]-=ss;sum[x]-=ssu;
            it=s[x].begin();
            s[x].erase(*it);
            s[sn].insert((node){x,sz[x]});
            fa[sn]=f;fa[x]=sn;
        }
    }
    return 0;
}
```


---

