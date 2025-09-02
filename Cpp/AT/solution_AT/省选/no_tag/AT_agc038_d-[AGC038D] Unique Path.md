# [AGC038D] Unique Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc038/tasks/agc038_d

すぬけ君は、$ 0 $ から $ N-1 $ までの番号のついた $ N $ 個の頂点と、$ M $ 本の辺からなる無向グラフをお母さんにもらいました。 このグラフは連結で、また、多重辺や自己ループは存在しませんでした。

ある日、すぬけ君はこのグラフを壊してしまいました。 しかし、すぬけ君はこのグラフについて、$ Q $ 個の情報を覚えています。 $ i $ ($ 0\ \leq\ i\ \leq\ Q-1 $) 番目の情報は整数 $ A_i,B_i,C_i $ で表され、次のことを意味します。

- $ C_i=0 $ の時: 頂点 $ A_i $ から $ B_i $ に向かう単純パス（同じ頂点を $ 2 $ 度通らないパス）が、$ 1 $ つしか存在しない。
- $ C_i=1 $ の時: 頂点 $ A_i $ から $ B_i $ に向かう単純パスが $ 2 $ つ以上存在する。

すぬけ君は自分の記憶に自信がないので、これら $ Q $ 個の情報に合致するグラフが存在するのかどうか心配になりました。 すぬけくんの記憶に合致するグラフが存在するかどうか判定してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ N\ \times\ (N-1)/2 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 0\ \leq\ A_i,B_i\ \leq\ N-1 $
- $ A_i\ \neq\ B_i $
- $ 0\ \leq\ C_i\ \leq\ 1 $
- 入力される値はすべて整数である。

### Sample Explanation 1

例えば、辺集合が $ (0,1),(1,2),(1,4),(2,3),(2,4) $ であるグラフを考えると、これは条件を満たします。

## 样例 #1

### 输入

```
5 5 3
0 1 0
1 2 1
2 3 0```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4 4 3
0 1 0
1 2 1
2 3 0```

### 输出

```
No```

## 样例 #3

### 输入

```
10 9 9
7 6 0
4 5 1
9 7 0
2 9 0
2 3 0
4 1 0
8 0 0
9 1 0
3 0 0```

### 输出

```
No```

# 题解

## 作者：_quasar_ (赞：8)

首先如果 $a,b$ 只有一条路径，且 $b,c$ 只有一条路径，那么 $a,c$ 一定只有一条路径。显而易见的，$a,c$ 之间的合法路径只能为 $a\rightarrow b\rightarrow c$ 。因此将所有的由 $0$ 类边连起来的点放在一起，形成一个联通块（显然只能是一棵树）。

假设有 $k$ 个联通块，因为每个联通块都是一棵树，因此还剩下 $m-n+k$ 条边。

如果这个时候没有 $1$ 类边的话：

- 边数的最小取值：将 $k$ 棵树连起来的边数花费为 $k-1$ 。
- 边数的最大取值：比较显然的是因为同一联通块中的点不能属于一个环内，所以钦定每个联通块有一个"外交官"专门负责向外面连边，其他点都不能向外面连边。这样的话 $k$ 个"外交官"可以随便连边，因此边数为 $\frac{k(k-1)}{2}$ 。

如果有 $1$ 类边：

- 如果只有两个联通块：想不出怎么构造了，无解。
- 如果有一条 $1$ 类边的两个端点属于同一联通块：两个同一联通块的点不能放在一个环里面，无解。
- 边数的最小取值：将 $k$ 个"外交官"连成一个环即可，边数为 $k$ 。
- 边数的最大取值：同样是 $\frac{k(k-1)}{2}$ 。

维护一下联通块，然后判断 $m$ 是否在合法区间内即可（注意判断 `m<n-1`）。

```cpp
const int N=1e5+5;
int n,k,q,a[N],b[N],c[N],fa[N];
ll m;

int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}

int main() {
    IN(n,m,q),k=n;
    lep(i,1,q) IN(a[i],b[i],c[i]);
    lep(i,1,n) fa[i]=i;

    bool flag=false;
    lep(i,1,q) if(!c[i]) {if(find(a[i])!=find(b[i])) fa[find(a[i])]=find(b[i]),--k;}
    lep(i,1,q) if(c[i]) {
        flag=true;
        if(find(a[i])==find(b[i])) return puts("No"),0;
    }

    if(m<n-1) return puts("NO"),0;
    if(!flag) puts((k-1<=m-n+k&&m-n+k<=1ll*k*(k-1)/2)?"Yes":"No");
    else puts((k>2&&k<=m-n+k&&m-n+k<=1ll*k*(k-1)/2)?"Yes":"No");
    return 0;
}
```

---

## 作者：Autumn_Rain (赞：2)

> 温馨提示：不开 long long 见祖宗。

- 引理：若 $A,B$ 间仅一条简单路径，$B,C$ 间也仅一条简单路径，那么 $A,C$ 间也仅一条简单路径 $A\to B\to C$。

- 证明：![](https://cdn.luogu.com.cn/upload/image_hosting/yo6u1kb3.png)



---

分析过程。

由引理知，把 $c_i$ 等于 $0$ 的点分成几个连通块建树可以满足限制。若 $c_i=1$ 的两个点在同一个连通块内则无解。

两连通块间若连了超过一条边，连通块内部的点就不只一条路径了。易证此情况下两连通块内所有点连通。设第一个连通块有 $a$ 个点，第二个有 $b$ 个点，那么连两条边时就有总边数为 $a-1+b-1+2=a+b$，和节点数一致，故有环。环上两点间不满足只有一条路径的限制，就会出现同一连通块多条路径的情况。综上两连通块间最多连一条边。

而且我们易得，建立的这 $cnt$ 棵树花费了我们 $n-1-(cnt-1)=n-cnt$ 条边。（这是因为 $n$ 个点的树要 $n-1$ 条边，我们每从这棵大树分出一个子树，就减少一条边，共减少了 $cnt-1$ 条边）。

---



整理一下就是：

- 把 $c_i$ 等于 $0$ 的点分成 $cnt$ 个连通块。
- 若 $c_i=1$ 的两点在同一连通块就判无解。
- 两两连通块间最多连一条边。
- 目前已耗费 $n-cnt$ 条边。


随后大力分讨。

- 所有 $c_i=0$ 时。可用的边的数量必须大于等于 $n-cnt$。把每个连通块缩成一个点，两两间最多一条边。其实就是 $cnt$ 个点连成完全图时是上限（$cnt$ 个点连完全图需要 $\frac{cnt \times (cnt-1)}{2}$ 条边）。合法边数范围是：$\left [ n-cnt, n-cnt+ \frac{cnt \times (cnt-1)}{2}\right ] $ 即 $\left [ n-1, n+ \frac{cnt \times (cnt-3)}{2}\right ] $。(此时 $cnt=1$，是一棵包含所有输入点的大树。未输入的不用管它，没有限制）。
  
- 否则：把每个连通块缩成一点，连出一个环。可以发现满足条件。（有人可能认为连通块内点相互之间会有 $2$ 条路径可以到达是错的，但仔细看会发现那不是简单路径），又因为两两间最多一条边，所以合法边数范围是：$\left [ n-cnt+cnt, n-cnt+ \frac{cnt \times (cnt-1)}{2}\right ] $ 即 $\left [ n, n+ \frac{cnt \times (cnt-3)}{2}\right ] $。


---



```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+10;
int n,q;
ll l,r,m;
int a[N],b[N];
bool c[N],ans;
int fa[N],cnt;
ll find(ll x){
	if(x==fa[x]){
		return x;
	}
	return fa[x]=find(fa[x]);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	l=n-1;
	for(int i=1;i<=q;i++){
		cin>>a[i]>>b[i]>>c[i];
		a[i]++;
		b[i]++;
		if(!c[i]){
			fa[find(a[i])]=find(b[i]);
		}
		else l=n;
	}
	for(int i=1;i<=n;i++){
		if(fa[i]==i){
			cnt++;
		}
	}
	r=n+cnt*(cnt-3)/2;
	if(l<=m&&m<=r){
		ans=1;
	}
	for(int i=1;i<=q;i++){
		if(!c[i])continue;
		if(find(a[i])==find(b[i])){
			ans=0;
		}
	}
	if(ans)cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

分类讨论。

首先用并查集将所有 $c_i=0$ 的缩在一起。设一个连通块大小为 $V$，那么他们之间最多（同时也是最少）只能有 $V-1$ 条边。

如果所有 $c_i$ 有 $c_i=0$，那么我们可以在每一个连通块中取出一个特殊点，在他们之间一点一点连出完全图。故边数可以取到 $n-1\sim n-cnt+\frac{cnt(cnt-1)}{2}$，其中 $cnt$ 为连通块数量。

否则，如果存在 $c_i=1$ 使得 $a_i,b_i$ 在同一个连通块，那么他们之间只有一条路径，先判掉。

剩余的情况，由于至少要有 $2$ 条路径，我们可以每一个连通块中取出一个特殊点，先连出一个环，这样所有要求就可以都被满足了，然后再一点一点加到完全图，故边数可以取到 $n\sim n-cnt+\frac{cnt(cnt-1)}{2}$。

总复杂度 $O(n\log n+q)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int a[100005],b[100005],c[100005];
int f[100005];
int find(int i){
	return f[i]==i?f[i]:f[i]=find(f[i]);
}
signed main(){
	int n,m,q; cin>>n>>m>>q;
	for(int i=1;i<=n;i++) f[i]=i;
	bool ok=1;
	for(int i=1;i<=q;i++){
		cin>>a[i]>>b[i]>>c[i],ok&=(c[i]==0);
		a[i]++,b[i]++;
		if(c[i]==0) f[find(a[i])]=find(b[i]);
	}
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=(find(i)==i);
	if(ok){
		int low=n-1,high=n-cnt+cnt*(cnt-1)/2;
		if(low<=m&&m<=high) cout<<"Yes";
		else cout<<"No";
		return 0;
	}
	for(int i=1;i<=q;i++){
		if(c[i]==1){
			if(find(a[i])==find(b[i])){
				cout<<"No";
				return 0;
			}
		}
	}
	int low=n,high=n-cnt+cnt*(cnt-1)/2;
	if(low<=m&&m<=high) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

