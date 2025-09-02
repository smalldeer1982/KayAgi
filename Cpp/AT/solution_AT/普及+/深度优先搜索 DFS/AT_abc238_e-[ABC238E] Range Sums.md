# [ABC238E] Range Sums

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc238/tasks/abc238_e

高橋くんは秘密の整数列 $ a $ を持っており、現時点で、$ a $ の長さが $ N $ であることは分かっています。

$ a $ の中身を当てたいあなたに対し、高橋くんは以下の $ Q $ 個の情報を追加で与えてくれることを約束しました。

- $ i\ (1\ \leq\ i\ \leq\ Q) $ 個目の情報: $ a_{l_i}+a_{l_i+1}+\cdots+a_{r_i} $ の値

高橋くんが約束を守り、$ Q $ 個の情報すべてが与えられた場合、$ a $ に含まれる全要素の総和 $ a_1+a_2+\cdots+a_N $ を特定することは可能ですか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ \min(2\ \times\ 10^5,\frac{N(N+1)}{2}) $
- $ 1\ \leq\ l_i\ \leq\ r_i\ \leq\ N $
- $ (l_i,r_i)\ \neq\ (l_j,r_j)\ (i\ \neq\ j) $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 個目の情報と $ 2 $ 個目の情報から、$ a_1+a_2+a_2+a_3 $ の値が分かります。そこから $ 3 $ 個目の情報によって得られる $ a_2 $ の値を引くと、$ a_1+a_2+a_3 $ の値を特定可能です。

### Sample Explanation 2

$ a $ の先頭 $ 3 $ 項の総和を特定することは可能ですが、全要素の総和を特定することは不可能です。

### Sample Explanation 3

$ 4 $ 個目の情報によって全要素の総和が直接与えられています。

## 样例 #1

### 输入

```
3 3
1 2
2 3
2 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4 3
1 3
1 2
2 3```

### 输出

```
No```

## 样例 #3

### 输入

```
4 4
1 1
2 2
3 3
1 4```

### 输出

```
Yes```

# 题解

## 作者：BLuemoon_ (赞：11)

$l$ 到 $r$ 的区间和，很容易让人想到前缀和。

而正向求区间和的公式是：$ans=s_r-s_{l-1}$，其中 $s$ 为前缀和数组。

在往反方向想，$s_{l-1}=s_r-ans$，所以对于题目给定的 $ans$，用 $s_r$ 可以求出 $s_{l-1}$。

这个特点就很熟悉了，连一条边，然后判断 $0$ 和 $n$ 是否在同一个联通块中，如果在，那么就求的出 $s_n-s_0$，也就是所有数的和。联通块直接用并查集即可。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,l,r,fa[2000005];
int find(int x)
{
  return fa[x]==x?x:fa[x]=find(fa[x]); //并查集压缩路径
}
int main()
{
  cin>>n>>q;
  for(int i=0;i<=n+3;i++)
    fa[i]=i;
  for(int i=1;i<=q;i++)
  {
    cin>>l>>r;
    fa[find(r)]=find(l-1); //连边
  }
  cout<<(find(0)==find(n)?"Yes":"No")<<'\n'; //判断
  return 0;
}
```

---

## 作者：54188_you_Dad (赞：8)

看了 $3$ 篇题解都是并查集。

 ~~为什么不用图论。~~
 
 ~~为什么不用 BFS。~~
 
 先建立一个无向图,再使用 BFS 遍历即可。
 
最后看一下能否到达 $n$ 即可。

 上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,q;
	cin>>n>>q;
	vector<vector<int> > a(n+5);//建立无向图 
	for(int i=1;i<=q;i++)
	{
		int l,r;
		cin>>l>>r;
		//存储无向图
		l--;
		a[l].push_back(r);
		a[r].push_back(l);
	}
	int tf[n+5] = {};//有没有访问过 
	queue<int> que;
	que.push(0);
	tf[0] = 1;//访问过
	while(!que.empty())//使用BFS遍历无向图
	{
		int u = que.front();
		que.pop();
		for(int i:a[u])
		{
			if(!tf[i])
			{
				que.push(i);
				tf[i] = 1;
			}
		}
	}
	cout<<(tf[n] ? "YES":"NO)")<<"\n";
	return 0;
}
```
 你这么认真的看完这篇题解,就点个赞再走吧。

---

## 作者：loser_seele (赞：5)

观察到原数组的具体取值并不重要，我们需要的信息只是区间 $ [l,r] $ 的和为 $ sum_r-sum_{l-1} $，其中 $ sum $ 代表前缀和。

于是不难想到一个思路：对于给定的一个区间 $ [l,r] $，建无向边 $ (l-1,r) $，代表由 $ sum_r $ 的信息能推出 $ sum_{l-1} $ 的信息，反之亦然。

于是我们已知 $ sum_0=0 $，问题转化为能否知道 $ sum_n $，也就是从图上的 $ 0 $ 节点能否到达 $ n $。

这个可以直接用并查集维护，时间复杂度 $ \mathcal{O}(q\log{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
const int mod=1e18;
int n,q,u,v,c;
char op;
struct Splay
{
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn];
    void clear(int x)
    {
        ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=0;
        mul[x]=1;
    }
    int getch(int x)
    {
        return (ch[fa[x]][1]==x);
    }
    int isroot(int x)
    {
        clear(0);
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void maintain(int x)
    {
        clear(0);
        siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]])%mod;
        sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]])%mod;
    }
    void pushdown(int x)
    {
        clear(0);
        if(mul[x]!=1)
        {
            if(ch[x][0])
            mul[ch[x][0]]=(mul[x]*mul[ch[x][0]])%mod,val[ch[x][0]]=(val[ch[x][0]]*mul[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]*mul[x])%mod,add[ch[x][0]]=(add[ch[x][0]]*mul[x])%mod;
            if(ch[x][1])
            mul[ch[x][1]]=(mul[x]*mul[ch[x][1]])%mod,val[ch[x][1]]=(val[ch[x][1]]*mul[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]*mul[x])%mod,add[ch[x][1]]=(add[ch[x][1]]*mul[x])%mod;
            mul[x]=1;
        }
        if(add[x])
        {
            if(ch[x][0])
            add[ch[x][0]]=(add[ch[x][0]]+add[x])%mod,val[ch[x][0]]=(val[ch[x][0]]+add[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]+add[x]*siz[ch[x][0]])%mod;
            if(ch[x][1])
            add[ch[x][1]]=(add[ch[x][1]]+add[x])%mod,val[ch[x][1]]=(val[ch[x][1]]+add[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]+add[x]*siz[ch[x][1]])%mod;
            add[x]=0;
        }
        if(rev[x])
        {
            if(ch[x][0])
            rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
            if(ch[x][1])
            rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
            rev[x]=0;
        }
    }
    void update(int x)
    {
        if(!isroot(x))
        update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;
        if(!isroot(y))
        ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];
        fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;
        fa[y]=x;
        maintain(y);
        maintain(x);
        maintain(z);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))
        rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])
        splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    int find(int x)
    {
        access(x);
        splay(x);
        while(ch[x][0])
        x=ch[x][0];
        splay(x);
        return x;
    }
    void final_mul(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = val[v] * c % mod;
      sum[v] = sum[v] * c % mod;
      mul[v] = mul[v] * c % mod;
    }
    void final_add(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = (val[v] + c) % mod;
      sum[v] = (sum[v] + siz[v] * c % mod) % mod;
      add[v] = (add[v] + c) % mod;
    }
    int query1(int u,int v)
    {
    makeroot(u), access(v), splay(v);
    return sum[v];
    }
    void link(int u,int v)
    {
    if (find(u) != find(v)) 
    makeroot(u), fa[u] = v;
    }
    void cut(int u,int v)
    {
    makeroot(u);
      access(v);
      splay(v);
      if (ch[v][0] == u && !ch[u][1]) 
      ch[v][0] = fa[u] = 0;
    }
    bool query2(int u,int v)
    {
    return find(u) == find(v);
    }
}st;
int find(int x)
{
return st.find(x);
}
void merge(int u,int v)
{
st.link(u,v);
}//LCT-并查集
signed main()
{
	ios::sync_with_stdio(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n+1;i++)
		st.clear(i),st.maintain(i),st.splay(i);
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		st.link(r+1,l);//因为LCT不支持对0节点操作（否则会超时）所以坐标集体平移1
	}
	if(st.find(1)==st.find(n+1))
		cout<<"Yes";
	else
		cout<<"No";
}
```


---

## 作者：fengenrong (赞：2)

这其实是一道并查集的题目，我们可以设 $f$ 为 $a$ 的前缀和，那么从 $l$ 到 $r$ 的和即为 $f_r-f_{l-1}$。

因为题目要求求出数组的前缀和，那么其实就是在求 $f_n-f_0$ 的值。所以，我们可以直接利用并查集，每次合并将 $r$ 和 $l-1$ 合并。最后，查找一下 $0$ 是否可以连接到 $n$ 就行了。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,father[100000005];
void ycl()//预处理
{
	for(register int i=1;i<=100000004;i++)
   {
    	father[i]=i;//先将自己的祖先点设为自己
	}
}
int find(int x)
{
	return father[x]==x?x:father[x]=find(father[x]);//路径压缩
}
signed main()
{
	cin>>n>>q;
	ycl();
	for(register int i=1;i<=q;i++)
	{
		int l,r;
		cin>>l>>r;
		father[find(l-1)]=find(r);//合并
	}
	cout<<((find(0)==find(n))?"Yes":"No");//判断是否能到
	return 0;
} 
```

---

## 作者：BugGod (赞：1)

我们将每一个已知的 $(l-1,r)$ 连边，显然，如果 $l,r$ 是一个连通块的，那么一定可以通过将 $l-1,r$ 路径上的边相加的形式，求出 $s_r-s_{l-1}$（自己列一下就出来了，会相消的），所以这个问题就转化为了求 $l-1,r$ 是否在一个连通块里的问题，直接用并查集解决。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,l,r,fa[200010];
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    cin>>n>>q;
    for(int i=0;i<=n;i++)fa[i]=i;
    while(q--)
    {
        cin>>l>>r;
        fa[find(l-1)]=fa[r];
    }
    if(find(0)==find(n))cout<<"Yes";
    else cout<<"No";
    return 0;
}
```

---

## 作者：Rosent (赞：1)

[题目Link](https://www.luogu.com.cn/problem/AT_abc238_e)

~~并查集模板题~~

题目要求输入一个 $l$ 和 $r$，表示 $l$ 和 $r$ 之间的区间和，不难想到前缀和。

设前缀和数组 $s$，每个区间 $l,r$ 的区间和即为 $s_{r}-s_{l-1}$。

题目求数组的和，即为求区间 $s_{n}-s_{0}$ 的值，易想到使用并查集，将每个 $s_{r}$ 和 $s_{l-1}$ 之间连接一条边，表示可以知道区间 $s_{r}$ 和 $s_{l-1}$ 的值。最后若 $s_{n}$ 和 $s_{0}$ 之间有连边（即可以知道区间 $s_{n}-s_{0}$ 的值），则说明满足题目要求，输出 `Yes`，否则输出 `No`。

代码：
```cpp
#include <bits/stdc++.h>
#define maxn 200010
using namespace std;
struct n
{
	int l,r;
}a[maxn];
int fa[maxn];
int find(int x)
{
	if(x==fa[x]) return x;
	else return x=fa[x]=find(fa[x]);
}
int main()
{
	int n,q;
	cin>>n>>q;
	for(int i=0;i<=n;i++)
	{
		fa[i]=i;
	}
	for(int i=1;i<=q;i++)
	{
		cin>>a[i].l>>a[i].r;
		fa[find(a[i].l-1)]=find(a[i].r);
	}
	if(find(0)==find(n))
	{
		cout<<"Yes";
		return 0;
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：cosf (赞：0)

## [ABC238E](https://atcoder.jp/contests/abc238/tasks/abc238_e) [区间和](https://www.luogu.com.cn/problem/AT_abc238_e)

## 并查集模版

可以发现，如果令 $S_{l, r}=\sum_{i=l}^ra_i$，那么知道 $S_{l_i, r_i}$ 相当于知道 $S_{1, l_{i}-1}$ 和 $S_{1, r_i}$。那么整个问题就可以转换为一个非常典型的问题：

现在有 $n+1$ 个点，编号为 $0, 1, \dots, n$，有 $q$ 条边，每条边用 $(l_i, r_i)$ 描述，表示 $l_i - 1$ 和 $r_i$ 之间有连边。问：$0$ 号节点与 $n$ 号节点是否相连。

这不就并查集板子吗？

```cpp
#include <iostream>
using namespace std;

#define MAXN 200005

int fa[MAXN];

int find(int x)
{
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 0; i <= n; i++)
    {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        fa[find(u - 1)] = find(v);
    }
    if (find(0) == find(n))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}

```

## 拓展

[P8779](https://www.luogu.com.cn/problem/P8779)，这道题几乎和这道一模一样。可以认为，本题和 P8779 是铺垫关系。


---

## 作者：1234567890sjx (赞：0)

为啥是绿啊。

首先求一个前缀和。

很容易得到 $l\sim r$ 的和其实就是知道 $s_r-s_{l-1}$ 的值，也就是 $l-1\sim r$ 连一条边。

求 $1\sim n$ 的和就是 $s_n-s_0$ 的值。

所以答案就是判断 $n$ 和 $0$ 的连通性。

动态维护点的连通性（加边，查询）显然可以用并查集来维护。

每一次并查集合并 $l-1$ 和 $r$ 的祖先，最后判断 $0$ 和 $n$ 的祖先是否相同即可。

时间复杂度 $O(\alpha n)$。

---

## 作者：wangyishan (赞：0)

# ABC138E Range Sums 题解

题目传送门：[Link](https://www.luogu.com.cn/problem/AT_abc238_e)

题意简述：给你一个长度为 $n$ 的序列 $a$ , 你知道其中 $q$ 组子区间的和，求你能否还原出整个数组之和。

处理区间和的问题有一种很常见的技巧就是**前缀和**。在这道题中也会用到。

我们令某段子区间之和为 $\text{ans}$，前缀和数组为 $s_{1...n}$，则区间 $[l,r]$ 之和可以表示为 
$$\text{ans}=s_r-s_{l-1}$$
移项可得
$$s_{l-1}=s_r-\text{ans}$$
所以，我们发现一旦知道了 $s_r$ 和 $\text{ans}$，$s_{l-1}$ 也就可以求得了。题目中要求的整个区间和就是 $s_n-s_0$。

由于在这道题中 $\text{ans}$ 的值并不重要，所以可以考虑并查集（[并查集板子](https://www.luogu.com.cn/problem/P3367)）：在 $s_r$ 和 $s_{l-1}$ 之间连一条边，在最后如果 $s_n$ 和 $s_0$ 在一个连通块内，就是 `Yes`。

代码如下：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int f[200010];
int find(int x){//路径压缩
    if(x!=f[x])f[x]=find(f[x]);
    return f[x];
}
int n,q;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i=0;i<=n;i++)f[i]=i;
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        f[find(l-1)]=find(r);
    }
    if(find(n)==find(0))cout<<"Yes";
    else cout<<"No";
    return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/abc238e.html)

## 简要题意

有一个长度为 $N$ 的序列 $a$，你知道 $Q$ 个区间的和。求是否可以知道 $[1,n]$ 的和。

$1 \leq N,Q \leq 2 \times 10^5$

## 思路

这是一道并查集题。

首先考虑，我们是如何快速求区间和的：前缀和！

首先考虑以下前缀和，令 $P$ 为 $a$ 的前缀和，那么我们只需要知道 $P_r$ 和 $P_{l-1}$ 就可以了。

所以我们自然想到对于知道的区间 $[l,r]$，连边 $(l-1,r)$。最后查 $0$ 和 $N$ 是否连通即可。

使用并查集实现，时间复杂度 $O(Q\log N)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

int n,q;
int fa[2000005];

int find(int x){
	if(fa[x]==x)return x;
	else {
		int parent=find(fa[x]);
		fa[x]=parent;
		return parent;
	}
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	else{
		fa[fy]=fx;
	}
}
bool same(int x,int y){
	return find(x)==find(y);
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		merge(l-1,r);
	}
	cout<<(same(0,n)?"Yes":"No")<<'\n';
	return 0;
}
```

[AC Record](https://atcoder.jp/contests/abc238/submissions/36770950)

---

