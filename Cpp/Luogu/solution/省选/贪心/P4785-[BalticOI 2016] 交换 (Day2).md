# [BalticOI 2016] 交换 (Day2)

## 题目描述

给定一个包含 $n$ 个数的序列 $x_1,x_2,\dots,x_n$。$1,2,\dots,n$ 每个数在序列中刚好出现一次。  
你可以通过交换修改这个序列。你需要进行连续的 $n-1$ 轮操作，编号 $k=2,3,\dots,n$，第 $k$ 轮你可以选择交换 $x_k$ 和 $x_{\lfloor k/2\rfloor}$ 或是什么都不做。  
如果存在一个数 $j(1 \leq j \leq n)$，使得对于所有 $k < j$ 且 $a_j < b_j,$ $a_k = b_k$ 成立，那么序列 $a_1\dots a_n$ 「**字典序小于**」序列 $b_1\dots b_n$。  
你能得到的字典序最小的序列是什么？

## 说明/提示

|子任务|分数|数据范围|
|:-:|:-:|-|
|1|10|$1 \leq n \leq 20$|
|2|11|$1 \leq n \leq 40$|
|3|27|$1 \leq n \leq 1000$|
|4|20|$1 \leq n \leq 5 \cdot 10^4$|
|5|32|$1 \leq n \leq 2 \cdot 10^5$|


## 样例 #1

### 输入

```
5
3 4 2 5 1```

### 输出

```
2 1 3 4 5```

# 题解

## 作者：CPPfive (赞：15)

## 题目分析

看到这道题目，第一反应就是贪心，但是模拟完样例后就发现无脑贪心是不对的。我们只能贪心的选择当前位置的最小值，但是在有些情况下，有多种不同操作都可以把最小值移到当前位置，并且不同操作间是不能贪心选择的。

于是我们观察一下题目。第 $i$ 个位置可以跟第 $2i$ 个位置和第 $2i+1$ 个位置交换。这让我们想到了二叉树。我们可以将题目等价成一棵根节点为 $1$，编号为 $i$ 的结点的左右儿子分别是 $2i$ 和 $2i+1$ 的树。

然后我们考虑维护每一个位置可以取到的数（在不影响前面已经选完的那些的情况下），我们只要贪心地按编号依次在它们能取到的数中选择最小的那一个就可以得到答案。

对于上面这个操作，我们先考虑一个位置可以取到的数在没有任何别的限制的情况下有多少个。我们发现一个结点能取到的数实际上包括这些：
- 这个结点的两个儿子
- 这个结点到根结点的路径上的所有点以及这些点的左儿子（如果这些左儿子原来不在序列里的话）

我们发现，一个结点能取到的所有点的个数是 $\log{N}$ 这个数量级的，因此对于每个结点找出它能取到的最小值，总复杂度是 $\mathcal{O}(n\log{N})$。

因此我们剩下来的任务就是判断对于一个结点来说，哪些点是可以取的，哪些是不能取的。

我们把一个结点分成三类：
- 取值不来自于它的后代
- 取值来自于它的左儿子
- 取值来自于它的右儿子

我们发现，对于第一类结点，它上面的点（包括它自己，下同）是不会换到它的下面的，它的左儿子也不可能到它的右子树上；对于第二类结点，它上面的点只有一个可以换到它的左子树上，并且它的左儿子也不会到右子树上。对于第三类结点，它上面的点只有一个可以到它的左子树或者右子树上（相对应的，它的左儿子可以到另一边去）。

因此，我们只需要在每一个点上维护一些信息，就可以实现前面说的功能。具体来说，我们需要记录每一个点是第几类点（如果这个点还没有选就是 $0$），然后对于第二类点和第三类点记录它们是否被用过，对于第三类点还需要记录它将左儿子放到了左边还是右边。每一次选择完后维护这些信息也是 $\mathcal{O}(\log N)$ 的。

最后贴下代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fa (u>>1)
#define lson (u<<1)
#define rson ((u<<1)|1)
const int MAXN=200050;
int N,x[MAXN];
bool vis[MAXN],use[MAXN];	//vis记录一个数值是否被用过，use记录一个结点是否被使用过 
int type[MAXN],now[MAXN];	//值为0表示两边都可以，值为1表示放到左边，值为2表示放到右边
int ans[MAXN];

void cmin(int &a,int b){if(a>b) a=b;}
int find(int u,int from){
	int mn=MAXN;
	for(;u;u=fa){
		if(type[u]==1) break;
		if(from==1&&type[u]==2) break;
		if(from==1){
			if(!vis[x[u]]&&type[u]==3&&!(type[fa]==3&&now[fa]==1)&&now[u]!=1&&!use[u]) cmin(mn,x[u]);
			if(!vis[x[lson]]&&type[u]==3&&now[u]!=2&&lson<=N) cmin(mn,x[lson]);
		}
		else if(from==2){
			if(lson<=N) cmin(mn,x[lson]);if(rson<=N) cmin(mn,x[rson]);if(!vis[x[u]]&&!(type[fa]==3&&now[fa]==1)) cmin(mn,x[u]);
		}
		else{
			if(!vis[x[u]]&&((type[u]==2&&now[u]==0)||(type[u]==3&&now[u]!=2&&!use[u]))&&!(type[fa]==3&&now[fa]==1)) cmin(mn,x[u]);
		}
		if(type[u]==2&&now[u]==1) break;
		if(type[u]==3&&now[u]&&(use[u]||now[u]!=from+1)) break;
		from=u&1;
	}
	return mn;
}
void change(int u){
	if(ans[u]==x[lson]) type[u]=2;
	else if(ans[u]==x[rson]) type[u]=3;
	else type[u]=1;
}
void update(int u){
	int from=u&1,t=ans[u];
	if(type[u]==2||type[u]==3) return;
	if(x[u]==t) return;
	for(u=fa;u;u=fa){
		if(x[u]==t){
			use[u]=1;
			if(type[u]==2) now[u]=1;
			else now[u]=from+1;
			return;
		}
		else if(x[lson]==t){
			now[u]=1;
			return;
		}
		else{
			use[u]=1;
			now[u]=from+1;
		}
        from=u&1;
	}
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;++i) scanf("%d",&x[i]);
	for(int i=1;i<=N;++i){
		ans[i]=find(i,2);
		vis[ans[i]]=1;
		change(i);
		update(i);
	}
	for(int i=1;i<=N;++i) printf("%d%c",ans[i],"\n "[i!=N]);
	
	return 0;
}
```


---

## 作者：pitiless0514 (赞：15)

## Statement

一个长度为 $n$ 的排列，可以通过交换修改这个序列，你可以执行连续 $n-1$ 轮操作，操作编号 $k$ 为 $2 \sim n$，每次你可以交换 $a_k$ 和 $a_{\lfloor \frac{k}{2} \rfloor}$ 或者什么都不干。

要求最小化字典序，$n \leq 2 \times 10^5$。

## Solution

题目的操作很有特性，看到 $x$ 和 $\lfloor \dfrac{x}{2} \rfloor$，联想到线段树的标号，于是先将其给定的序列建成一颗二叉树，在二叉树上考虑问题。

考虑当前在点 $u$，设他的值为 $a$，他左儿子 $u \times 2$ 值为 $b$，右儿子 $u \times 2 + 1$ 值为 $c$。

那么注意到按照操作顺序，$u$ 的值要变化，要么只能是由祖先进行替换，或者是由 $b, c$ 进行替换。

于是大力分类讨论。

当 $a < \min\{b, c\}$ 的时候，$b, c$ 都没 $a$ 小，让他们靠前字典序只会增大，于是 $u$ 节点不交换，递归两个儿子处理儿子就好了。

当 $b < \min\{a, c\}$ 的时候，此时交换 $a, b$ 让 $u$ 节点的值最小，从而可以让字典序最小。

接下来观察子节点 $ls(u), rs(u)$ 的顺序，现在是 $a, c$，但是有没有可能，会为 $c, a$？

一定不可能，因为交换 $(ls(u), u)$ 的时间为 $u \times 2$，交换 $(rs(u), u)$ 的时间为 $u \times 2 + 1$，所以只能先交换左节点，而后面假如交换 $(rs(u), u)$，会让点 $u$ 的值变为 $c$，与最优字典序不符，所以此情况子节点顺序只能为 $a, c$，继续递归两个儿子计算即可。

当 $c < \min\{b, c\}$ 的时候，这个时候交换 $a, c$ 让 $u$ 节点的值最小，才能最小化字典序，但是子节点内的顺序，有可能是 $a, b$ 也有可能是 $b, a$ 这个时候两种情况都有可能，并不确定哪边会更优。

不失一般性假设 $a < b$，假如 $a$ 放到左子树的最后位置为 $p$，那么将 $b$ 放到左子树来，位置 $p$ 的值一定会增大，因为我们会优先让字典序更小，也就是小的在前面，此时更小的 $a$ 都只能到位置 $p$，而更大的 $b$ 自然无法到 $p$ 以前，所以位置 $p$ 的值一定会增大，右子树情况同理。

所以我们可以在写一个爆搜，同样按照我们上面的三条策略，搜出 $a$ 在左子树的位置 $p1$ 和右子树的位置 $p2$，之后看一下 $p1, p2$ 谁更小，就让 $b$ 走小的那边就好了。

然后爆搜写的是 $(u, v, id)$ 表示当前在点 $u$，将 $u$ 的值变成 $v$，然后上一步来自 $id$ 的最优能到达的位置。

记得在爆搜中第三种情况的时候讨论一下 $b$ 和 $v$ 的大小，假如是 $b$ 小一点，就让 $v$ 走 $b$ 左右子树分别走之后最终返回位置大的那一边，因为要最优化整个字典序，而不是单个字典序，$b$ 更小，要先优化它的位置。

复杂度的话，注意到假如访问到一个点 $u$，爆搜中可能出现的 $v$ 一定会是它的祖先或者某个祖先的兄弟，于是合法的 ${u, v}$ 二元组只有 $\log$ 个，记忆化一下，复杂度就对了。

代码用 map 实现的，总复杂度就为 $O(n \log^2 n)$。

```cpp
// 德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱
// 德丽莎的可爱在于德丽莎很可爱，德丽莎为什么很可爱呢，这是因为德丽莎很可爱！
// 没有力量的理想是戏言，没有理想的力量是空虚
#include <bits/stdc++.h>
#define LL long long
using namespace std;
char ibuf[1 << 15], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1 << 15, stdin), p1==p2) ? EOF : *p1++)
inline int read() {
  char ch = getchar();  int x = 0, f = 1;
  while (ch < '0' || ch > '9')  {  if (ch == '-')  f = -1;  ch = getchar();  }
  while (ch >= '0' && ch <= '9')  x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return x * f;
}
void print(LL x) {
  if (x > 9)  print(x / 10);
  putchar(x % 10 + '0');
}
template<class T> bool chkmin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool chkmax(T &a, T b) { return a < b ? (a = b, true) : false; }
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define repd(i, l, r) for (int i = (l); i >= (r); i--)
#define REP(i, l, r)  for (int i = (l); i < (r); i++)
const int N = 2e6;
int n, p[N];
int ls(int p) {  return p << 1;  }
int rs(int p) {  return p << 1 | 1;  }
map < pair<int,int>,int> mp;
int find(int u,int v,int id) {
  if (u > n)  return id;
  if (mp.find({u, v}) != mp.end())  return mp[{u, v}];
  int &b = p[ls(u)], &c = p[rs(u)], &w = mp[{u, v}];
  if (v < min(b, c))  return w = u;
  if (b < c)  return w = find(ls(u), v, u);
  else if (b < v) {
    int lans = find(ls(u), b, u);
    int rans = find(rs(u), b, u);
    if (lans > rans) {
      return w = find(ls(u), v, u);
    } else {
      return w = find(rs(u), v, u);
    }
  } else {
    return w = min(find(u << 1, v, u), find(u << 1 | 1, v, u));
  }
}
void work(int u) { 
  if (u > n)  return;
  int &a = p[u], &b = p[ls(u)], &c = p[rs(u)];
  if (a < min(b, c)) {
    work(ls(u));
    work(rs(u));
    return;
  }
  if (b < c) {
    swap(a, b);
    work(ls(u));
    work(rs(u));
    return;
  }
  swap(a, c);
  if (b > c)  swap(b, c);
  if (find(ls(u), b, ls(u)) > find(rs(u), b, rs(u)))  swap(b, c);
  work(ls(u));
  work(rs(u));
}
void solve() {
  n = read();
  rep (i, 1, n)  p[i] = read();
  rep (i, n + 1, 2 * n + 1)  p[i] = n + 1;
  work(1);
  rep (i, 1, n)  cout << p[i] << " ";
}
signed main () {
#ifdef LOCAL_DEFINE
  freopen("1.in", "r", stdin);
  freopen("1.ans", "w", stdout);
#endif
  int T = 1;  while (T--)  solve();
#ifdef LOCAL_DEFINE
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
  return 0;
}
```

---

## 作者：do_it_tomorrow (赞：4)

[更好的阅读体验](https://www.doittomorrow.xyz/post/balticoi-2016-day2-jiao-huan/)

注意到 $x$ 可以与 $\lfloor\dfrac{x}{2}\rfloor$ 交换，即 $k,2k,2k+1$ 之间可以交换，容易联想到完全二叉树。

假设位置 $k,2k,2k+1$ 的值分别是 $A,B,C$，考虑分类讨论。

对于 $A$ 最小的情况，显然不应该交换。因为字典序可以贪心的选择，如果 $k$ 的位置比 $A$ 大，那么在前面都一样的情况下，显然直接取 $A$ 是最优的。

对于 $B$ 最小的情况，显然应该让 $k,2k$ 交换，原因与上面类似。

对于 $C$ 最小的情况，应该让让 $k,2k+1$ 交换。但是特殊的情况是无论是否交换 $k,2k$ 都可以使 $k$ 这个位置取到最小的 $C$。假设 $A$ 为次小值，需要注意将 $A$ 放到 $2k$ 的位置并不是最优，下图就是一个反例。

对于这样的树形结构

![](https://cdn.luogu.com.cn/upload/image_hosting/emfde9ch.png)

应该进行这样的变换：

![](https://cdn.luogu.com.cn/upload/image_hosting/wmt61me9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/e41e8831.png)

而不是如上述的贪心策略进行这样的变化：

![](https://cdn.luogu.com.cn/upload/image_hosting/v3v95ky0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/g68f4tc6.png)

考虑设 $f(x,v)$ 为 $x$ 这个位置在处理了 $\lfloor \dfrac{x}{2}\rfloor$ 之后为 $v$ 时，$v$ 这个值可以移动到的最小位置。

对于上面的情况，我们就只需要考虑 $f(2k,a),f(2k+1,a)$ 的大小关系，$a$ 就应该换到小的那个子树。

考虑证明这个决策的正确性，不妨设放到 $2k$ 得到的序列为 $x$，反之为 $y$，且 $f(2k,a)\lt f(2k+1,a)$。

要证决策正确性，只需要证明 $\forall i\in[1,\min(f(2k,a),f(2k+1,a)))\cap\mathbb{N}$ 满足 $x_i=y_i$ 且 $x_{f(2k,a)}\lt y_{f(2k,a)}$。

要证明 $\forall i\in[1,\min(f(2k,a),f(2k+1,a)))\cap\mathbb{N}$ 满足 $x_i=y_i$，只需证 $\forall i\in[1,k]\cup(k,\min(f(2k,a),f(2k+1,a))))\cap\mathbb{N}$ 满足 $x_i=y_i$。

因为 $\forall i\in[1,k]\cap\mathbb{N}$ 的选择已经完成，那么显然都有 $x_i=y_i$。

因为 $a$ 这个值可以一直移动到 $f(2k,a)$，说明在在从 $2k$ 向下一直转移到 $f(2k,a)$ 都没有遇到取 $a$ 是最优的情况。那么如果 $2k$ 这个位置放比 $a$ 还要劣的 $b$，在从 $2k$ 向下遍历的时候遇到取 $b$ 是最优的一定不早于 $f(2k,a)$ ，对于在 $2k+1$ 的子树也是一样的。

这就证明了 $\forall i\in[1,\min(f(2k,a),f(2k+1,a)))\cap\mathbb{N}$ 满足 $x_i=y_i$。

根据定义因为 $a$ 会放到 $f(x,a)$，那么 $2\times f(x,a),2\times f(x,a)+1$ 都没有 $a$ 优秀，所以无论这个位置取 $b$ 还是 $2\times f(x,a),2\times f(x,a)+1$ 对应的值都没有 $a$ 优秀，因此策略的正确性得证。

考虑通过深度优先搜索求解 $f(x,v)$。

如果遇到第 $1$ 种情况或者遇到了根节点，那么显然就可以直接回溯求出答案，因为此时位置已经确定。

如果遇到第 $2$ 种情况，那么显然应该继续进入左子树进行递归。

对于第 $3$ 种情况就模仿现在的情况进行递归两个儿子就可以了。

```c++
#include<iostream>
#include<map>
#include<algorithm>
#define ls k*2
#define rs k*2+1
using namespace std;
const int N=4e5+5;
map<int,int> f[N];
int a[N],n;
int solve(int k,int s){
    if(f[k].count(s)){
        return f[k][s];
    }
    int ans=0;
    if(!a[ls]){
        return f[k][s]=k;
    }
    if(!a[rs]){
        if(a[ls]<s){
            return f[k][s]=ls;
        }
        return f[k][s]=k;
    }
    int A=s,B=a[ls],C=a[rs],v=min({A,B,C});
    if(A==v){
        return f[k][s]=k;
    }
    if(B==v){
        return f[k][s]=solve(ls,s);
    }
    int x=solve(ls,min(A,B)),y=solve(rs,min(A,B));
    if(s==min(A,B)){
        return f[k][s]=min(x,y);
    }
    if(x<y){
        return f[k][s]=solve(rs,s);
    }
    return f[k][s]=solve(ls,s);
}

void dfs(int k){
    if(k>n) return;
    int A=a[k],B=a[ls],C=a[rs],v=min({A,B,C});
    if(!B){
        return;
    }
    if(!C){
        if(B<A){
            swap(a[ls],a[k]);
        }
        return;
    }
    if(A==v){
        dfs(ls),dfs(rs);
        return ;
    }
    if(B==v){
        swap(a[k],a[ls]);
        dfs(ls),dfs(rs);
        return ;
    }
    a[k]=C;
    int x=solve(ls,min(A,B)),y=solve(rs,min(A,B));
    a[ls]=min(A,B),a[rs]=max(A,B);
    if(y<x){
        swap(a[ls],a[rs]);
    }
    dfs(ls),dfs(rs);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        cout<<a[i]<<' ';
    }
    return 0;
}
```

---

## 作者：Creeper_l (赞：4)

看到 $i$ 和 $\lfloor \frac{i}{2} \rfloor$，考虑一颗二叉树。题目的操作相当于按顺序交换当前节点和左右儿子的权值。

假设当前考虑的节点为 $id$，左儿子为 $ls$，右儿子为 $rs$，当前这些点的值分别为 $A,B,C$。

因为 $id$ 的位置最靠前，最终又要字典序最小，所以要尽可能让 $a_{id}$ 最小。

分三种情况讨论：

- $\min(A,B,C)=A$

肯定都不交换，因为要贪心地使 $a_{id}$ 最小，如果交换了任意一个的话 $a_{id}$ 就肯定大于 $A$ 了。

- $\min(A,B,C)=B$

因为要让 $a_{id}$ 最小，所以肯定会交换 $(id,ls)$，并且不会交换 $(id,rs)$。

- $\min(A,B,C)=C$

会发现肯定要交换 $(id,rs)$，但是不确定要不要交换 $(id,ls)$，也就是不确定 $A$ 放左边还是 $B$ 放左边。直接贪心肯定不行，我们假设 $mn = \min(A,B)$。定义函数 $f(id,val)$ 表示将当前节点为 $id$，值为 $val$，最终 $val$ 的位置在哪。看 $mn$ 放哪边的最终位置（即 $f(ls,mn)$ 和 $f(rs,mn)$）更小即可。为啥？因为若 $mn$ 不放最终位置更小的那边，那么这个位置的值肯定会更大，而放这个位置的话影响的位置更靠后，所以放小的这边更优。

那如何求 $f(id,val)$ 呢，会发现对于同一个 $id$，可能的 $val$ 只有 $\log$ 个（$id$ 的祖先以及祖先的兄弟节点），那直接暴力转移再记忆化一下即可。

时间复杂度的瓶颈在求 $f$，复杂度 $O(n \log^2 n)$。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5 + 10;
int n,a[MAXN],ans[MAXN];
#define ls id << 1
#define rs id << 1 | 1
map <int,int> mp[MAXN];
inline int dfs(int id,int val) {
	if(mp[id].count(val)) return mp[id][val];
	int res = id,A = val,B = a[ls],C = a[rs];
	if(B == 0 && C == 0) res = id;
	else if(C == 0) {
		if(B < A) res = ls;
		else res = id;
	} else {
		if(A < B && A < C) res = id;
		else if(B < A && B < C) res = dfs(ls,val);
		else {
			int mx = max(A,B),mn = min(A,B);
			int LS = dfs(ls,mn),RS = dfs(rs,mn);
			if(A < B) res = min(LS,RS);
			else {
				if(LS < RS) res = dfs(rs,val);
				else res = dfs(ls,val);
			}
		}
	} return mp[id][val] = res;
}
inline void solve(int id) {
	int A = a[id],B = a[ls],C = a[rs];
	if(B == 0 && C == 0) return;
	else if(C == 0) {
		if(B < A) swap(a[id],a[ls]);
		return;   
	} else {
		if(A < B && A < C) solve(ls),solve(rs);
		else if(B < A && B < C) {
			swap(a[id],a[ls]);
			solve(ls),solve(rs); 
		} else {
			a[id] = C;
			int mx = max(A,B),mn = min(A,B);
			int LS = dfs(ls,mn),RS = dfs(rs,mn);
			if(LS < RS) a[ls] = mn,a[rs] = mx;
			else a[rs] = mn,a[ls] = mx;
			solve(ls),solve(rs);
		}
	} return;
}
signed main() {
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	solve(1);
	for(int i = 1;i <= n;i++) cout << a[i] << " ";	
	return 0; 
} 
```

---

## 作者：SIXIANG32 (赞：4)

超级好的一道题，吹爆！

这个报告希望可以更加详细明确的探讨一下这道题的思维过程，欢迎各位来探讨交流 qwq

---
首先我们战术观察一下这道题目。Democy 子曰，字典序最小就是贪心，所以我们这道题的大框架就是贪心。我们看到这个交换很有意思，$a_n$ 和 $a_{\lfloor\frac{n}{2}\rfloor}$ 换。。如果你二叉树学的很扎实或者做过相似的题目（举个例子[这题](https://www.luogu.com.cn/problem/P2606)）那么我们就会想到把它放到一个完全二叉树上去。那么每次交换操作就是交换一个儿子和父亲了。

现在我们已经确定了大框架：在完全二叉树上跑贪心。

---
然后我们继续深入思考。

这道题让我们字典序最小，其实是什么？是我从上到下从左到右把每个点的值串下来的最小字典序。

每次交换儿子和父亲，而且是从 $i = 2\sim n$ 这样依次交换，放到完全二叉树上，就是从上到下，从左到右的交换。

拿样例举例子，像这样：
[![pCvOFRx.png](https://s1.ax1x.com/2023/07/27/pCvOFRx.png)](https://imgse.com/i/pCvOFRx)

这道题的操作是交换，从上到下从左到右交换自己的父亲，这有什么性质？我们可以把一个点通过它的儿子们不断的交换交换交换到下面去，但是不可能把它通过儿子交换上来，这就颇有几分“不同层之间互不干扰”的意味（当然还是有一定干扰的）。在不同子树之间又是基本上互不影响的，我们可以根据不同的子树划分子问题。这就启发我们每次考虑一个父亲和它的两个儿子，然后递归下去。像这样
[![pCvO0Wq.png](https://s1.ax1x.com/2023/07/27/pCvO0Wq.png)](https://imgse.com/i/pCvO0Wq)

由于我们不可能把 A 点换上去，所以一个子树是基本独立的。然后呢？我们肯定会考虑 B，C 怎么换。这一共有四种换发
1. 不换
2. B 换 C 不换
3. B 不换 C 换
4. B，C 都换。

通过手玩不难找到这四种情况对应的序列
1. A-B-C
2. B-A-C
3. C-B-A
4. C-A-B

为了字典序最小，首先根肯定要最小，这很容易理解。也就是说，如果 $a(A)$ 或 $a(B)$ 是 $a(A), a(B), a(C)$ 三者中的最小者，那么我们可以直接确定。但是 $C$ 呢？A，B 可以在子树中继续交换，这就不简单了。因为我们并不知道 A 和 B 放在哪。我们来幻想一下 A 在左子树 B 在右子树和 A 在右 B 在左的情况。画一下图

[![pCvXi7Q.png](https://s1.ax1x.com/2023/07/27/pCvXi7Q.png)](https://imgse.com/i/pCvXi7Q)

我们会发现这样一点，我们只需要知道 A，B 在左右子树中最优能在哪个位置就好了。这个位置是在整个二叉树中的编号。我们肯定希望这里面小的的编号小。不妨设 $a(A) < a(B)$。令 $a(A)$ 在左子树的最优位置是 $pos1$，在右边的是 $pos2$。如果 $pos1 < pos2$ 就让 A 去左边，反之去右边。$a(A) > a(B)$ 同理。

那么我们怎么求这个 $pos1$ 和 $pos2$ 呢？这个子问题让我们很想 dp 一下（雾，我们可以定义 $f(u, val)$ 代表以编号 $u$ 为根的子树根节点的值变成了 $val$ 后，$val$ 所处的最优位置。这个问题可以通过上面的策略解决。这样一个 $val$ 只可能出现在 $u$ 的祖先上，所以一共只有 $O(n\log_2 n)$ 种状态，记忆化一下时间复杂度 $O(n\log2_n)$。这样说很笼统，但是重新叙述一遍又太累赘，所以具体看代码吧 awa

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e5;
int a[MAXN + 10], n;
unordered_map <int, unordered_map <int, int> > f;
int getpos(int now, int val) {
	if(!a[2 * now]) return now;
	if(!a[2 * now + 1]) {
		if(a[2 * now] < val) return 2 * now;
		else return now;
	}
	if(f[now][val]) return f[now][val];

	int A = val, B = a[2 * now], C = a[2 * now + 1];
	if(A < B && A < C) return f[now][val] = now;
	else if(B < A && B < C) return f[now][val] = getpos(2 * now, val);
	else {
		if(A < B) return f[now][val] = min(getpos(2 * now, val), getpos(2 * now + 1, val));
		else {
			if(getpos(2 * now, B) > getpos(2 * now + 1, B))
				return f[now][val] = getpos(2 * now, val);
			else return f[now][val] = getpos(2 * now + 1, val);
		}
	}
	return f[now][val];
}
void dfs(int now) {
	if(!a[2 * now]) return ;
	if(!a[2 * now + 1]) {
		if(a[now] > a[2 * now]) swap(a[now], a[2 * now]);
		return ;
	}
	int &A = a[now], &B = a[2 * now], &C = a[2 * now + 1];
	if(A < B && A < C) dfs(2 * now), dfs(2 * now + 1);
	else if(B < A && B < C) {
		swap(A, B);
		dfs(2 * now), dfs(2 * now + 1);
	}
	else {
		int aa = A, bb = B, cc = C;
		if(getpos(2 * now, min(A, B)) < getpos(2 * now + 1, min(A, B))) B = min(aa, bb), C = max(aa, bb);
		else B = max(aa, bb), C = min(aa, bb);
		a[now] = cc;
		dfs(2 * now), dfs(2 * now + 1);
	}
	return ;
}
void init() {
    scanf("%d", &n);
	for(int p = 1; p <= n; p++)
		scanf("%d", &a[p]);

	dfs(1);
	for(int p = 1; p <= n; p++)
        printf("%d ", a[p]);
}
int main() {
	init();
}
```

---

## 作者：qijianci (赞：4)

#### 不同于记忆化搜索的一种解法，轻松跑到最优解。

今天模拟赛考了这题，但因为细节写挂了没调出来，写篇题解来总结一下。

题意大致为给定一个序列 $a$，从 $1$ 到 $n-1$ 顺序操作，每次可以交换 $a_{i+1}$ 和  $a_{\lfloor \frac {(i+1)} {2} \rfloor}$ 的值，要求最后序列的字典序最小。

首先我们可以观察到交换只能是 $a_i$ 与 $a_{2i}$ 交换， $a_{i}$ 与 $a_{2i+1}$ 交换，所以我们可以依据这一点建立一棵类似于线段树的二叉树。然后继续可观察得到父亲 $A$ 与儿子节点 $B$、$C$ 之间只可能有这几种关系。

>  $A$ 比 $B$，$C$ 都要小。
>
> 那么 $A$ 不与 $B$，$C$ 交换。

>  $B$ 比 $A$，$C$ 都要小。
>
> 那么 $A$，仅与 $B$，交换。

> $C$ 比 $A$，$B$ 都要小。
>
> 那么，$B$ 在父节点，子结点 $A$，$C$，可以互换位置。

前两种都是唯一的，麻烦的只有第三种。

~~当然可以记忆化搜索，状态数是 $n\log n$ 的。~~

但是我选择了更聪（tang）明（shi），的做法，观察到树高是 $\log_n$ 的，所以我们对于第三种我们可以先随便放，要求值的时候暴力跳父亲去找最小值即可。

应该有很多种实现方式，我的实现方式是记一个数组 $a$ 表示这个节点是由哪个节点走过来的，数组 $v$ 的值 $2$ 表示当前节点的儿子不能交换且不能从上面走下来，$1$ 表示当前节点可以从上面走下来但儿子不能交换，$0$ 表示当前节点儿子能交换且能从上面走下来，然后两个节点交换时他们子树内能从他们走到的点的 $a$ 值暴力改即可，可以想象这样的点应该是一条链，所以总时间复杂度也是 $n\log^2 n$ 的，能过，而且事实上跑得很快。

要注意儿子交换时哪个是可以上面走下来的，哪个是不行的，我在这卡了好久。

~~代码不好写，细节很多，慢慢调吧。~~

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],ans[N],now[N],v[N];
bool ck(int x){return now[a[x]]==a[x];}
inline int read(){
	char a=getchar_unlocked();
	int x=0,y=1;
	while(a<'0'||a>'9'){if(a=='-')y=-1;a=getchar_unlocked();}
	while(a>='0'&&a<='9'){
		x=(x<<3)+(x<<1)+a-'0';
		a=getchar_unlocked();
	} return x*y;
}
int sol(int x,int res=2e9){
    int fa=x>>1;
    while(fa){
        if(v[fa]==2)break;
        if(v[fa]&&a[x]!=a[fa])break;
        if(!v[fa]&&a[x]!=a[fa]&&!ck(x^1))break;
        if(!v[fa]&&ck(x^1))res=min(res,a[x^1]);
        fa>>=1,x>>=1;
    } return res;
}
void dfs(int x,int val){
    if(x*2<=n&&a[x<<1]==a[x])dfs(x<<1,val);
    if(x*2+1<=n&&a[x<<1|1]==a[x])dfs(x<<1|1,val);
    a[x]=val;
}
void re(int x,int mn){
    int fa=x>>1,t;
    if(mn==now[a[x]])return;
    while(fa){
        if(!v[fa]&&now[a[x^1]]==mn){
            v[fa]=1+(a[fa]!=a[x]);
            t=a[x],dfs(x,a[x^1]),dfs(x^1,t);break;
        } if(!v[fa]&&a[x]!=a[fa])t=a[x],dfs(x,a[x^1]),dfs(x^1,t),v[fa]=2;
        fa>>=1,x>>=1;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    int i,j,k,l,r,x,y,z;
    // cin>>n;
    n=read();
    for(i=1;i<=n;++i)a[i]=read(),now[i]=i;
    for(i=1;i<=n;++i){
        x=i<<1,y=x+1,l=sol(i),r=now[a[i]],z=min(l,r);
        if(x<=n&&y<=n){    
            if(z<min(a[x],a[y]))
                ans[i]=z,re(i,z),now[a[i]]=2e9,v[i]=2;
            else {
                ans[i]=min(a[x],a[y]);
                if(a[x]>a[y])a[y]=a[x];
                else v[i]=1; a[x]=a[i];
            }
        } else if(x<=n){
            if(z<a[x])
                ans[i]=z,re(i,z),now[a[i]]=2e9,v[i]=2;
            else ans[i]=a[x],a[x]=a[i],v[i]=1;
        } else ans[i]=z,re(i,z),now[a[i]]=2e9,v[i]=2;
    } for(i=1;i<=n;++i)printf("%d ",ans[i]);puts("");
    return 0;
}
```

---

## 作者：pref_ctrl27 (赞：3)

首先考虑 $x\to \lfloor\frac{x}{2}\rfloor$ 连出一棵完全二叉树，然后考虑从根开始确定权值。

分别记录当前点，左儿子和右儿子的权值为 $a,b,c$。

+ 如果 $a$ 最小，显然不会发生交换。
+ 如果 $b$ 最小，显然会让根和左子树换一下。
+ 如果 $c$ 最小，此时无法确定 $a,b$ 位于哪个子树。

我们需要比较两种情况下哪种更优。

对一棵树考虑根分别为 $a,b (a<b)$ 的情况下的最优解 $S_a,S_b$。设 $S_a$ 中 $a$ 出现在 $pos_a$，$S_b$ 中 $b$ 出现在 $pos_b$，可以发现 $pos_a\leq pos_b$ 且 $S_a$ 和 $S_b$ 在 $pos_a$ 之前的位置相同，用调整法易证。因此我们断定两个序列第一个不同的位置就是 $pos_a$。

对于两个子树合并考虑，我们相当于要找到整个序列第一个不同的位置比较，这其实恰好为两个 $pos_a$ 取 $\min$。我们可以简单比较这个位置属于哪个子树即可确定哪个更优。

因此我们考虑设 $f(u,v)$ 表示根节点 $u$ 为 $v$ 的情况下最终序列 $v$ 所处的位置，这是一个和原问题类似的问题，不再赘述。

考虑对 $f(u,v)$ 记忆化，注意到对于一个 $u$，可能的 $v$ 只有所有祖先以及祖先的另一个儿子，因此为 $\mathcal O(\log n)$ 的级别。

使用哈希即可做到 $\mathcal O(n\log n)$。

下面给出未加记忆化的暴力代码（实际上开了 O2 就能过）：


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N], ls[N], rs[N];
int check(int u, int val){
    if(!ls[u]) return u;
    if(!rs[u]){
        if(val<a[ls[u]]) return u;
        return check(ls[u], val);
    }
    int x=val, y=a[ls[u]], z=a[rs[u]];
    if(x==min({x, y, z})) return u;
    if(y==min({x, y, z})) return check(ls[u], val);
    if(x<y) return min(check(ls[u], val), check(rs[u], val));
    if(check(ls[u], y)>check(rs[u], y)) return check(ls[u], val);
    return check(rs[u], val);
}
void solve(int u){
    if(!ls[u]) return ;
    if(!rs[u]){
        if(a[u]>a[ls[u]]) swap(a[u], a[ls[u]]);
        solve(ls[u]);
        return ;
    }
    int x=a[u], y=a[ls[u]], z=a[rs[u]];
    if(x==min({x, y, z})){
        solve(ls[u]); solve(rs[u]);
        return ;
    }
    if(y==min({x, y, z})){
        swap(a[u], a[ls[u]]);
        solve(ls[u]), solve(rs[u]);
        return ;
    }
    a[u]=z;
    if(check(ls[u], min(x, y))<check(rs[u], min(x, y))) a[ls[u]]=min(x, y), a[rs[u]]=max(x, y);
    else a[ls[u]]=max(x, y), a[rs[u]]=min(x, y);
    solve(ls[u]); solve(rs[u]);
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<=n;++i){
        if(i*2<=n) ls[i]=i<<1;
        if(i*2+1<=n) rs[i]=i<<1|1;
    }
    solve(1);
    for(int i=1;i<=n;++i)
        printf("%d%c", a[i], " \n"[i==n]);
    return 0;
}

```

---

## 作者：云浅知处 (赞：2)

考虑从前往后推，考虑 $p_i,p_{2i},p_{2i+1}$，我们发现在这里进行完交换之后左右子树就独立了；而我们的首要目标是最小化 $p_i$。设这三个数是 $a,b,c$，讨论一下两边是否交换，发现交换完之后有四种情况：

```
    a    |    b    |    c    |    c
  b   c  |  a   c  |  b   a  |  a   b
```

可以发现，如果 $a,b$ 之一是最小值，那么交换方案唯一；否则我们需要把 $c$ 换上来，然后决策把 $a,b$ 中的哪个分配到左边，哪个分配到右边。

不难发现这只需要知道 $a,b$ 如果放在左边或右边，它们最终会被排到什么位置；然后我们尽量把小的那个排的靠前即可。可以设 $f(u,j)$ 表示如果在 $u$ 的子树内，先令 $p_u=j$，最终这个 $j$ 会被放到什么位置，但时间复杂度至少为 $O(n^2)$。

注意到所有点的子树大小之和为 $O(n\log n)$，而如果 $u$ 的子树内有 $x$ 个点，所有的 $f(u,\cdot)$ 至多只会有本质不同的 $x+1$ 种。因此直接记录就行了，复杂度不超过 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>

#define ll long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int N=2e5+5;
vector<int>vals[N],f[N];
int n,a[N];

#define ls(u) (u<<1)
#define rs(u) (u<<1|1)

int getpos(int u,int j){
	int p=lower_bound(vals[u].begin(),vals[u].end(),j)-vals[u].begin();
	if(f[u][p]!=-1)return f[u][p];
	int ans=u;
	if(rs(u)<=n){
		int x=j,y=a[ls(u)],z=a[rs(u)];
		if(x<y&&x<z)ans=u;
		else if(y<x&&y<z)ans=getpos(ls(u),x);
		else{
			if(x<y){
				int Lp=getpos(ls(u),x),Rp=getpos(rs(u),x);
				ans=min(Lp,Rp);
			}
			else{
				int Lp=getpos(ls(u),y),Rp=getpos(rs(u),y);
				if(Lp<Rp)ans=getpos(rs(u),x);
				else ans=getpos(ls(u),x);
			}
		}
	}
	else if(ls(u)<=n){
		if(j<a[ls(u)])ans=u;
		else ans=ls(u);
	}
	else ans=u;
	return f[u][p]=ans;
}

void solve(int u){
	if(rs(u)<=n){
		int x=a[u],y=a[ls(u)],z=a[rs(u)];
		if(x<y&&x<z)solve(ls(u)),solve(rs(u));
		else if(y<x&&y<z)swap(a[u],a[ls(u)]),solve(ls(u)),solve(rs(u));
		else{
			a[u]=z;if(x>y)swap(x,y);
			int Lp=getpos(ls(u),x),Rp=getpos(rs(u),x);
			if(Lp<Rp)a[ls(u)]=x,a[rs(u)]=y,solve(ls(u)),solve(rs(u));
			else a[ls(u)]=y,a[rs(u)]=x,solve(ls(u)),solve(rs(u));
		}
	}
	else if(ls(u)<=n){
		if(a[u]>a[ls(u)])swap(a[u],a[ls(u)]);
	}
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read();
	for(int i=1;i<=n;i++)a[i]=read();

	for(int i=1;i<=n;i++){
		int x=i;
		while(x)vals[x].emplace_back(a[i]),x>>=1;
	}
	for(int i=1;i<=n;i++)sort(vals[i].begin(),vals[i].end()),f[i].resize(vals[i].size()+1,-1);
	
	solve(1);
	for(int i=1;i<=n;i++)cout<<a[i]<<" \n"[i==n];

	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

直接考虑 $k$ 和 $\lfloor\dfrac{k}{2}\rfloor$ 是否交换比较烦。

注意到 $\forall k'>k,\lfloor\dfrac{k'}{2}\rfloor\ge\lfloor\dfrac{k}{2}\rfloor$，因此此时 $[1,\lfloor\dfrac{k}{2}\rfloor-1]$ 都已经被确定了，这启发我们往每个是否确定想，考虑 dp。

发现 $k$ 这个位置能对它造成影响的就只有 $2k$ 和 $2k+1$，得到了一个完全二叉树的结构。

注意到 $a_{2k},a_{2k+1}$ 因为没有被 $k$ 交换过，后面的没遍历到，所以这两个位置就是原位置上的值。

但是 $a_k$ 就不一定了，因为 $k$ 可能和 $\lfloor\dfrac{k}{2}\rfloor$ 交换过，但是 $\lfloor\dfrac{k}{2}\rfloor$ 是否交换过不确定，所以 $a_k$ 应该放到状态里面。

因此 dp 的状态为 $dp_{k,x}$ 表示 $a_k=x$ 时子树内生成的最小字典序方案。

令 $x=a_k,y=a_{2k},z=a_{2k+1}$，对它们的最小值分类讨论：

- $x=\min\{x,y,z\}$

显然 $k$ 和 $2k,2k+1$ 交换都不优。

- $y=\min\{x,y,z\}$

显然 $k$ 必须和 $2k$ 交换，不能和 $2k+1$ 交换。

- $z=\min\{x,y,z\}$

$k$ 必须和 $2k+1$ 交换，但是此时和 $2k$ 可以交换，也可以不交换，两种方案取字典序较小的那个即可。

合并左右儿子是简单的，第一次两边各取一个，第二次两边各取两个，第 $i$ 次两边各取 $2^{i-1}$ 个。

时间复杂度分析：$x$ 这一维只会是祖先或者它的兄弟的 $a$ 值，然后 `vector` 的总大小是 $\sum siz$ 的，时间复杂度是 $O(n\log^2n)$。

直接记忆化会被卡，实际上可以考虑底层分块，在子树大小不超过 $16$ 的时候每次都跑一遍，不记忆化就行了。

---

## 作者：MusicBox (赞：0)

一道非常小清新的思维题。

不难发现，我们每次可以选择交换 $x_i$ 和 $x_{i \times 2}$，以及 $x_i$ 和 $x_{i \times 2 + 1}$ ，请记住，这两个交换是有序的，即我们只能选择前操作后再选择后操作。

那么这个问题就转化到一个二叉树上，我们每次可以选择按照 bfs 序选择是否与左儿子交换，是否与右儿子交换。

我们接下来分析这个过程，我们设父亲，左儿子，右儿子分别为 $a, b, c$。

若 $a = \min(a, b, c)$，我们显然不会和左儿子和右儿子交换，所以显然是不变的。

若 $b = \min(a, b, c)$，我们显然会和左儿子交换，然后不会和右儿子交换。

若 $c = \min(a, b, c)$，我们显然会和右儿子交换，但是是否第一次与左儿子交换，我们并不知道。

我们设 $w = \min(a, b)$，我们假设将 $w$ 放入左子树，它最终会落到 $p1$ 位置，放入右子树，它最终会落到 $p2$ 位置，若 $p1 < p2$，我们会将 $w$ 放入左子树，否则放入右子树。

考虑正确性，若我们将较大数放入那一边，则 $\min(p1, p2)$ 的字符显然会变大，且我们从当前子树位置到 $\min(p1, p2) - 1$ 的字符是不受影响的。

我们设 $f_{i,j}$ 表示，将 $j$ 放置在 $i$ 位置最后会落到哪里。不难发现，我们对于每个 $i$ 查询的一定是它的祖先的节点，或者它祖先的左或右儿子，我们可以预处理出来，由于在一颗特殊二叉树上，层高是 $\log n$ 级别的，预处理复杂度 $\mathcal O(n\log n)$，贪心复杂度 $\mathcal O(n)$。

当然，我们也可以不预处理，使用 map 进行记忆化，复杂度 $\mathcal O(n\log^2 n)$。

code:

```cpp
#define mi(a, b, c) min(a, min(b, c))

int n, a[L];
vector<int> nums;
bool ban[L];

map<pii, int> tmp;

int check(int x, int f) {
    if(tmp[{x, f}]) return tmp[{x, f}];
    int l = (x << 1), r = (x << 1 | 1);
    if(l <= n && r <= n) {
        if(f == mi(a[l], a[r], f)) return tmp[{x, f}] = x;
        else if(a[l] == mi(a[l], a[r], f)) return tmp[{x, f}] = check(l, f);
        else { 
            int _x = a[l], _y = f; if(_x > _y) swap(_x, _y);
            int p1 = check(l, _x), p2 = check(r, _x);
            if(p1 < p2) 
                return tmp[{x, f}] = ((_x == f) ? p1 : check(r, f));
            else 
                return tmp[{x, f}] = ((_x == f) ? p2 : check(l, f));
        }
    } else if(l <= n) {
        if(f == min(a[l], f)) return tmp[{x, f}] = x;
        else return tmp[{x, f}] = check(l, f);
    } else {
        return tmp[{x, f}] = x;
    }
}

signed main() {
    rd(n); rep(i, 1, n) rd(a[i]);
    rep(i, 1, n) {
        int l = (i << 1), r = (i << 1 | 1);
        if(l <= n && r <= n) {
            if(a[i] == mi(a[i], a[l], a[r])) continue;
            else if(a[l] == mi(a[i], a[l], a[r])) swap(a[l], a[i]);
            else {
                int x = a[l], y = a[i]; if(x > y) swap(x, y); 
                int p1 = check(l, x), p2 = check(r, x);
                if(p1 < p2) a[i] = a[r], a[l] = x, a[r] = y;
                else a[i] = a[r], a[r] = x, a[l] = y;
            }
        } else if(l <= n) {
            if(a[i] == min(a[i], a[l])) continue;
            else if(a[l] == min(a[i], a[l])) swap(a[l], a[i]);
        }
    }
    rep(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ');
    return 0;
}
```

---

