# [ABC177D] Friends

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc177/tasks/abc177_d

人 $ 1 $ から 人 $ N $ までの $ N $ 人の人がいます。

「人 $ A_i $ と人 $ B_i $ は友達である」という情報が $ M $ 個与えられます。同じ情報が複数回与えられることもあります。

$ X $ と $ Y $ が友達、かつ、$ Y $ と $ Z $ が友達ならば、$ X $ と $ Z $ も友達です。また、$ M $ 個の情報から導くことができない友達関係は存在しません。

悪の高橋君は、この $ N $ 人をいくつかのグループに分け、全ての人について「同じグループの中に友達がいない」という状況を作ろうとしています。

最小でいくつのグループに分ければ良いでしょうか？

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\leq\ N $
- $ A_i\ \neq\ B_i $

### Sample Explanation 1

例えば $ \{1,3\},\{2,4\},\{5\} $ という $ 3 $ つのグループに分けることで目的を達成できます。

## 样例 #1

### 输入

```
5 3
1 2
3 4
5 1```

### 输出

```
3```

## 样例 #2

### 输入

```
4 10
1 2
2 1
1 2
2 1
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
4```

## 样例 #3

### 输入

```
10 4
3 1
4 1
5 9
2 6```

### 输出

```
3```

# 题解

## 作者：Neilchenyinuo (赞：2)

## 题目大意

有一个 $N$ 个点 $M$ 条边的**不连通图**，现将这些点分成 $k$ 个组，使第 $i(1\le i\le k)$ 个组里面的所有点都**不连通**，求 $k$ 的最小值。

- 前置知识：[并查集](https://oi.wiki/ds/dsu/)。

## Solution

1. 看到“连通块”三个字，脑海里就不禁想到并查集，没错，本题正是用并查集写。

2. 做法就是把每一个连通图中的每一个数合起来化成一组，这样使得答案为最大连通块的大小。

3. 具体怎么做呢？

- 循环输入时，调用 `find()` 函数找到 $x$ 和 $y$ 的祖先。

- 如果不同，就用考虑使用 $sum_i$ 来统计存储联通块的节点数，然后将其并在一个连通块下就好了。

4. 那么组的个数就是最大的联通块的节点数。

5. 那么求出最小值就可以了。

## 坑点

- 并查集记得初始化。

- $sum_i$ 初始化为一。（因为最少有 $1$ 组）

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int fa[N],n,m,x,y,sum[N],ans; 
int find(int x)
{
    if(fa[x]==x)
    	return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    for(int i=1;i<N;i++)
    {
    	fa[i]=i;
		sum[i]=1;
	}
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y;
        x=find(x),y=find(y);
        if(x!=y)
            sum[y]+=sum[x];
        fa[x]=y;
    }
    for(int i=1;i<=n;i++)
		ans=max(ans,sum[i]); 
    cout<<ans;
    return 0;
}
```


---

## 作者：PineappleSummer (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc177_d)

RMJ 寄了，一直 UKE......好在 atcoder 上 AC 了。

并查集好题。

题目要求使每个组里的所有点都不连通，也就是说**一个组里的所有点都不在一个连通块里面**，所以让**一个连通块里面的所有点都在不同的组里**。设连通块 $i$ 中点的个数为 $cnt_i$，答案即为 $\max\{cnt_i\}$。

拿样例 $1$ 讲一下：连通块 $1$ 中的点为 $\{1,2,5\}$，连通块 $3$ 中的点为 $\{3,4\}$，所以 $cnt_1=3$，$cnt_3=2$，答案为 $\max(cnt_1,cnt_3)=3$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,ans,f[N],cnt[N];
int find(int k)//并查集查找
{
	if(f[k]==k) return k;
	return f[k]=find(f[k]);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;//设集i的“代表”为i
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		int fx=find(x),fy=find(y);
		if(fx!=fy) f[fx]=fy;//并查集合并操作
	}
	for(int i=1;i<=n;i++) cnt[find(i)]++;//计算每个连通块中点的个数
	for(int i=1;i<=n;i++)
		ans=max(ans,cnt[i]);//取最大的连通块
	cout<<ans;
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：1)

## Desciption

[Link](https://www.luogu.com.cn/problem/AT_abc177_d)

有一个 $n$ 个点 $m$ 条边的不连通图，现将这些点分成 $k$ 个组，使第 $i(i\in[1,k])$ 个组里面的所有点都不连通，求 $k$ 的最小值。

## Solution

要求维护连通块找答案，什么可以管理节点元素集合（连通块）呢？

**并查集**。

题目要求让 $k$ 最小，令 $S$ 为图的集合，包括了所有不互相联通的连通块，尽量让其中几个连通块大，那么 $k$ 就会更小。

则 $k$ 为：

$$k=\max^{|S|}_{i=1}\{S_i,k\}$$

## Code

```cpp
// 2023/6/27 Accept__

#include <iostream>

using namespace std;

typedef long long ll;

const int kMaxN = 2e5 + 7;

int n, m, fa[kMaxN], rnk[kMaxN], ans = -1;

bool swap(int& a, int& b) {
    a ^= b ^= a ^= b;
    return a;
}

int find(int x) {
    return (x == fa[x]) ? x : (fa[x] = find(fa[x]));
}

void uni(int u, int v) {
    int fx = find(u), fy = find(v);
    (rnk[fx] > rnk[fy]) && (swap(u, v));
    (fx != fy) && (rnk[fy] += rnk[fx]), fa[fx] = fy;
}

void init() {
    for (int i = 0; i < kMaxN; i++) {
        fa[i] = i, rnk[i] = 1;
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), init();
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        uni(u, v);
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, rnk[i]);
    }
    cout << ans << '\n';

    return 0;
}
```


---

## 作者：_GW_ (赞：1)

## 思路
前置知识：并查集。

不连通，即全部不再一个联通块。题目要让 $k$ 最小，考虑从图中的联通块下手。

判联通，以及联通块，第一个想到的就是并查集，并且并查集也能过。

如何让 $k$ 最小呢？那么就贪心，每次在每个联通块中选一个节点，构成一个每个节点都不连通的组。

那么组的个数就是最大的联通块的节点数。

如何存储联通块的节点数呢？用一个数组 $s$，我们用 $s_i$ 表示在节点 $i$ 所处联通块的节点数，在建图的同时计算即可。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=114514*2;
int fa[N],num,n,m,x,y,data,s[N],ans;
//fa[i]表示节点i的祖先，size[i]表示节点i所在联通块的节点数。 
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);//并查集模板 
}
int main()
{
    for(int i=1;i<N;i++)
    {
        fa[i]=i;
        s[i]=1;//并查集初始化。
    }
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y;
        if(find(x)!=find(y))
        {
            s[find(y)]+=s[find(x)];//建图的同时计算联通块大小。 
        }
        fa[find(x)]=find(y);
    }
    for(int i=1;i<=n;i++) ans=max(ans,s[i]);//寻找答案。 
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：_shine_ (赞：1)

## 题目大意
现在有 $n$ 个点，$m$ 条边的不连通图，现在需要你把这个不连通图分成 $k$ 个组，使得每组中的元素互相不连通，并且使得 $k$ 的值最小。
## 思路
不难发现，在本题中，最优解法就是把每一个连通图中的每一个数合起来化成一组，这样使得答案为最大连通块的大小，这样也是最优的。考虑使用并查集把连通块存储起来，每次在输入时合并存储连通块大小即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m;
int f[maxn],ans[maxn];
int res;
int find(int x){
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
signed main(){
	cin >> n >> m;
	for(int i=1;i<=n;++i){
		f[i]=i;
		ans[i]=1;
	}
	while(m--){
		int a,b;
		cin >> a >> b;
		int finda=find(a),findb=find(b);
		f[finda]=findb;
		if(finda!=findb){
			ans[findb]+=ans[finda];
		}
	}
	for(int i=1;i<=n;++i){
		res=max(res,ans[i]);
	}
	cout << res << endl;
	return 0;
}
```


---

## 作者：xiaomuyun (赞：1)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc177_d)
- [AtCoder 题目传送门](https://atcoder.jp/contests/abc177/tasks/abc177_d)

## 思路分析

很容易想到，如果把朋友关系看成图的边的话，答案就是最大的连通块的节点数量。

维护连通块，最简单的方法是并查集。

## 代码实现

注意重边（不过好像并不需要像代码中那样开一个 `map`，实际上 `find_root` 之后如果根相等不合并就行了）。

```cpp
#include<algorithm>
#include<iostream>
#include<utility>
#include<cstdio>
#include<map>
#define mkp(a,b) make_pair(a,b)
using namespace std;
const int maxn=2e5+2;
int n,m,fa[maxn],cnt[maxn],mx=0;
map<pair<int,int>,int> mp;
int find_root(int a){
	if(fa[a]==a) return a;
	return fa[a]=find_root(fa[a]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1,a,b;i<=m;++i){
		scanf("%d%d",&a,&b);
		if(a>b) swap(a,b);
		if(mp[mkp(a,b)]==1) continue;//去重边
		mp[mkp(a,b)]=1,fa[find_root(a)]=find_root(b);//合并
	}
	for(int i=1;i<=n;++i) ++cnt[find_root(i)],mx=max(cnt[find_root(i)],mx);//统计答案
	printf("%d\n",mx);
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

显然答案应该为最大连通块的大小。

证明：显然至少需要最大连通块的大小才能使得这个连通块被划分，否则根据抽屉原理不可能使得这个连通块全部被分入不同的组。而这个答案为上限也是显然的，一种构造方案是将第 $ i $ 个元素丢入第 $ i $ 个组，显然这么做两两就不存在连边。

所以只需要维护一个并查集实现查询最大连通块大小，不加按秩合并优化的单次并查集操作是 $ \mathcal{O}(\log{n}) $ 的，所以总时间复杂度 $ \mathcal{O}(m\log{n}) $，可以通过。当然注意下面的代码为了省事没写正常的并查集。

实现上可以每次合并的时候维护子树大小，用带权并查集合并，也可以全部合并完之后将相同父亲的点塞进桶里，然后统计桶里答案的最大值，这里采用的是第二种方法。

代码：

```cpp
#include <bits/stdc++.h>
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
}
void clean(int n)
{
for(int i=1;i<=n;i++)
st.clear(i),st.maintain(i),st.splay(i);
}//main
unordered_map<int,int>p;
signed main()
{
int n,m;
cin>>n>>m;
clean(n);
while(m--)
{
int u,v;
cin>>u>>v;
merge(u,v);
}
for(int i=1;i<=n;i++)
p[find(i)]++;
int maxn=-1;
for(auto x:p)
maxn=max(maxn,x.second);
cout<<maxn;
}
```


---

## 作者：happy_zero (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc177_d)

很好想到，维护两个点是否联通可以用并查集维护。对于每一个连通块里有 $x$ 个点，则这 $x$ 个点至少要在 $x$ 组里，由此可见，$k$ 的最小值为最大连通块的大小，同样可以用并查集维护：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int fa[N], siz[N];
int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int main(){
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fa[i] = i, siz[i] = 1;
	while (m--)
	{
		int x, y;
		cin >> x >> y;
		int tx = find(x), ty = find(y);
		fa[tx] = ty;
		if (tx != ty) siz[ty] += siz[tx];
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, siz[i]);
	cout << ans;
	return 0;
}

```


---

