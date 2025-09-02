# Half-decay tree

## 题目描述

Recently Petya has become keen on physics. Anna V., his teacher noticed Petya's interest and gave him a fascinating physical puzzle — a half-decay tree.

A half-decay tree is a complete binary tree with the height $ h $ . The height of a tree is the length of the path (in edges) from the root to a leaf in the tree. While studying the tree Petya can add electrons to vertices or induce random decay with synchrophasotron. Random decay is a process during which the edges of some path from the root to the random leaf of the tree are deleted. All the leaves are equiprobable. As the half-decay tree is the school property, Petya will return back the deleted edges into the tree after each decay.

After being desintegrated, the tree decomposes into connected components. Charge of each component is the total quantity of electrons placed in vertices of the component. Potential of desintegerated tree is the maximum from the charges of its connected components. Each time before inducing random decay Petya is curious about the mathematical expectation of potential of the tree after being desintegrated.

## 样例 #1

### 输入

```
1 4
add 1 3
add 2 10
add 3 11
decay
```

### 输出

```
13.50000000
```

# 题解

## 作者：Vocalise (赞：5)

很妙的题。

考虑记录所有出现过的某棵子树的权值和。

每次修改 $h$ 个点，$q$ 次一共只会修改 $nq$ 个点。用 `map` 维护即可，单次复杂度 $\Theta(h^2)$。

对于每次询问，我们尝试枚举所有最大值。计算取最大值的概率。

`dfs` 整棵树，到达一点时，代表了断开它的所有祖先连边的情况。所以维护祖先断边之后的连通块权值最大值为 $m$。

如果该点是叶子，直接再对 $m$ 用它的权值取 $\max$，然后计算概率为 $\frac 1{2^k}$。

如果该点的子树权值小于等于 $m$，那么该子树中断开得到的连通块不可能成为最大值，即，子树内的所有叶子的方案权值都是 $m$，计算后返回。

否则递归。

这个做法单次询问复杂度是 $\Theta(h)$ 的，不太显然。证明如下：

假如一个点递归左儿子和右儿子，它们都没有立即返回。记该点子树权值 $s$，左儿子子树权值 $s_l$，右儿子 $s_r$。

那么有
$$
s - s_l < s_l,s - s_r < s_r
$$
得到
$$
2s_l > s, 2s_r > s
$$
但是 $s_l + s_r\le s$，矛盾。那么一个点最多递归一个儿子，证毕。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

const int H = 30;
const int Q = 100001;

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

char t[5]; int k,q;
std::map <int,double> s;

double Dfs(int v,int l,double mx) {
    if(v >= (1 << k)) mx = std::max(mx,s[v]);
    if(s[v] <= mx) return mx * l / (1 << k);
    return Dfs(v * 2,l / 2,std::max(mx,s[v] - s[2 * v])) + Dfs(v * 2 + 1,l / 2,std::max(mx,s[v] - s[2 * v + 1]));
}

int main() {
    k = read(), q = read();
    while(q--) {
        std::scanf("%s",t);
        if(t[0] == 'a') {
            int v = read(), e = read();
            while(v) s[v] += e, v /= 2;
        } else std::printf("%lf\n",Dfs(1,1 << k,0));
    }
    return 0;
}

```



---

## 作者：ModestCoder_ (赞：3)

这道题目不难
发现总共$q$个询问，每次询问最多涉及到$h$个点，所以总共最多设计到$qh$个点

可以用$map$把以每个点为根的子树权值之和记录下来

修改操作直接把自己到根路径上所有点修改

查询操作不妨反向思考，从根节点开始往下断边，因为是二叉树所以每次只有两种断边可能，对应权值可以求出

由于期望的线性性直接加起来

终止条件是当前的最大值大于等于当前节点的map值

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int h, q;
map <int, int> mp;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

#define ls u << 1
#define rs u << 1 | 1

double dfs(int u, int Max){
	if (Max >= mp[u]) return Max;
	return 0.5 * (dfs(ls, max(Max, mp[u] - mp[ls])) + dfs(rs, max(Max, mp[u] - mp[rs])));
}

int main(){
	h = read(), q = read();
	while (q--){
		char c[10]; scanf("%s", c);
		if (c[0] == 'a'){
			int u = read(), w = read();
			while (u) mp[u] += w, u >>= 1;
		} else printf("%.8f\n", dfs(1, 0));
	}
	return 0;
}
```


---

## 作者：Zxx200611 (赞：2)

给出一棵高度为 $h$ 的完全二叉树 $T$，此树上节点编号遵循线段树的编号方法。初始每个点的权值为 $0$。  
有 $q$ 次操作，每次为下面的两种之一：
+ 选择一个点 $u$，将其权值加 $v$。
+ 询问在 $T$ 中随机断开一条从根到叶的路径后，定义一个连通块的价值为其内点的权值和，求价值最大的连通块的价值期望。


$1 \le h \le 30$，$q \le 10^5$。

---

记 $V_u$​ 为点 $u$​ 的权值，$S_u$​ 为点 $u$​ 的子树的权值和，$L_u$​ 为节点 $u$​ 下方的节点个数。由于节点个数较大，需要用 Map 来存。  
根节点高度为 $0$​。


对于修改操作，暴力往上跳，更新所有 $u$ 上方节点的 $S$ 即可。


对于询问操作，考虑一次在树上从根开始，随机向下走并断边的过程。记录一个上面已经被断出来的连通块的价值最大值 $Mxv$​。  
假设现在节点 $u$，左儿子为 $l$，右儿子为 $r$​：  
+ 若 $S_u \le Mxv$​​，则以 $u$​​ 子树中叶子为结束的根叶路对应的价值最大连通块价值即为 $Mxv$​​​。由于所有叶子对应的根叶路有 $\frac{L_u}{2^h}$ 的概率会来到这里，对答案的贡献为 $Mxv \times \frac{L_u}{2^h}$​​​。不需要再继续往下递归算了。
+ 若 $S_u \ge Mxv$​​，则此子树对答案可能还有贡献：
  + 若此节点为叶子，则对答案的贡献为 $\frac{\max(u,Mxv)}{2^h}$​。​
  + 若此节点不为叶子，往左右儿子递归即可。



为了不掉精度，在计算时所有答案乘以 $2^h$，最后除掉即可。

至此，得到了一个 $O(qh \log n) = O(qh^2)$​ 的做法，足以通过此题。

---

```cpp
#include<bits/stdc++.h>
using namespace std;

int h;
unordered_map<int,int> V,S;

inline
int L(int u)
{
	return (1<<h)/(1<<(int)log2(u));
}
inline
bool isLeaf(int u)
{
	return ((int)log2(u))==h;
}
inline
void update(int p,int v)
{
	V[p]+=v;
	for(int u=p;u;u>>=1)
	{
		S[u]+=v;
	}
}
unsigned long long query(int u,int Mxv)
{
	int l=(u<<1),r=(u<<1)|1;

	if(S[u]<=Mxv)
	{
		return 1ull*L(u)*Mxv;
	}
	if(isLeaf(u))
	{
		return max(V[u],Mxv);
	}

	unsigned long long ans=0;
	ans+=query(l,max(Mxv,V[u]+S[r]));
	ans+=query(r,max(Mxv,V[u]+S[l]));
	return ans;
}

int main()
{
	int q;
	scanf("%d%d",&h,&q);

	char *s=new char[110];
	int p,v;
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='a')
		{
			scanf("%d%d",&p,&v);
			update(p,v);
		}
		if(s[0]=='d')
		{
			printf("%.6lf\n",(double)query(1,0)/(1<<h));
		}
	}
}
```



---

## 作者：YLWang (赞：1)

优美的题。

考虑最后一定是分成了一条链上的点和一些子树上的点的拼合。

很套路地计算每棵子树的贡献。

容易发现，我们以根节点剖分的时候，当当前子树 $u$ 的子树和比任何一个其他子树的子树和小的时候，他的所有子树都没用了。

那么直接暴力 dfs 的时候维护一个 max 就行了。

为什么复杂度是对的？

考虑线段树的证明过程。读者自证不难。

代码链接：https://www.luogu.com.cn/paste/vylqy0o8

---

## 作者：q1uple (赞：0)

好题。

我们注意到树的结构非常特殊，是完全二叉树，并且我们发现操作二显然强于操作一，我们从操作二入手。

我们先考虑最暴力的方式，直接爆搜出所有的情况，但是显然过不去，我们注意到实际上每个点修改的值是很少的，我们如果当前找到了一个最大值 $mx$，这个子树的最大值已经 $\le mx$ 的时候，我们直接不找了，否则直接递归，因为我们能找的个数是很少的，并且如果我们一边已经递归过了，另一边很快就能停止。而对于求子树最大值，直接用 map 往上跳就行。

[submission](https://codeforces.com/contest/68/submission/325027397)

---

## 作者：Drind (赞：0)

### 题目解析

完全二叉树上单点修改，查询每次随机选中一个叶子，把叶子到根的所有路径断掉后形成的森林权值和最大值的期望。

首先我们发现可以在 $\log n$ 的复杂度内实现修改每个节点的子树权值，但是数组存不下，而只会有 $q\log n$ 个点被修改，所以用 map 存。

查询呢？我们用 dfs 解决，我们记这个点以上最大连通块权值为 $mx$，如果这个点的子树权值小于 $mx$ 那不用走了，直接把答案更新即可。如果这个点是叶子节点那么也可以更新答案，否则继续递归。

复杂度 O( 能过 )，精度注意一下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;

map<int,int>siz;
int pw[40];
int n,m,ans; 

void dfs(int u,int mx,int dep){
	if(siz[u]<=mx){
		ans+=mx*pw[n]/pw[dep];
		return;
	}else{
		if(dep==n){
			ans+=siz[u];
		}
		else{
			dfs(u*2,max(mx,siz[u]-siz[u*2]),dep+1);
			dfs(u*2+1,max(mx,siz[u]-siz[u*2+1]),dep+1);
		}
	}
	
}

inline void fake_main(){
	cin>>n>>m; n++;
	pw[0]=1;
	for(int i=1;i<=31;i++) pw[i]=pw[i-1]*2;
	for(int i=1;i<=m;i++){
		string op; cin>>op;
		if(op[0]=='a'){
			int v,e; cin>>v>>e;
			siz[v]+=e;
			while(v!=1){
				v/=2;
				siz[v]+=e;
			}
		}else{
			ans=0;
			dfs(1,0,1);
			cout<<fixed<<setprecision(8)<<ans*1.0/pw[n-1]<<"\n";
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

