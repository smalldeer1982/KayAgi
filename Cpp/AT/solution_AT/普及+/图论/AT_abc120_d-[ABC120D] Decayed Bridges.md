# [ABC120D] Decayed Bridges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc120/tasks/abc120_d

$ N $ 個の島と $ M $ 本の橋があります。

$ i $ 番目の橋は $ A_i $ 番目の島と $ B_i $ 番目の島を繋いでおり、双方向に行き来可能です。

はじめ、どの $ 2 $ つの島についてもいくつかの橋を渡って互いに行き来できます。

調査の結果、老朽化のためこれら $ M $ 本の橋は $ 1 $ 番目の橋から順に全て崩落することがわかりました。

「いくつかの橋を渡って互いに行き来できなくなった $ 2 $ つの島の組 $ (a,\ b) $ ($ a\ <\ b $) の数」を**不便さ**と呼ぶことにします。

各 $ i $ $ (1\ \leq\ i\ \leq\ M) $ について、$ i $ 番目の橋が崩落した直後の不便さを求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,\ B_i) $ の組は全て異なる。
- 初期状態における不便さは $ 0 $ である。

### Sample Explanation 1

例えば、$ 1 $ から $ 3 $ 番目の橋が崩落したとき、$ (1,\ 2),\ (1,\ 3),\ (2,\ 4),\ (3,\ 4) $ の島の組について行き来できなくなるので不便さは $ 4 $ です。

## 样例 #1

### 输入

```
4 5
1 2
3 4
1 3
2 3
1 4```

### 输出

```
0
0
4
5
6```

## 样例 #2

### 输入

```
6 5
2 3
1 2
5 6
3 4
4 5```

### 输出

```
8
9
12
14
15```

## 样例 #3

### 输入

```
2 1
1 2```

### 输出

```
1```

# 题解

## 作者：ElmPoplar (赞：10)

> 春风起意，落叶静水

[题目传送门](https://www.luogu.com.cn/problem/AT4319)

## 题目大意

给定一张 $n$ 个点， $m$ 条边的无向图，现按输入顺序依次删除每一条边，求出每删除一条边是，有多少对 $(x,y)$ 不能联通，注意 $(x,y)$ 与 $(y,x)$ 为一种。

## 解题思路

看到这道题，是不是有种似曾相识的感觉，还记得[JSOI2008 星球大战](https://www.luogu.com.cn/problem/P1197)吗，其实跟这道题如出一辙，这不过这次是删边~~甚至更简单~~。

我们可以使用并查集维护联通块，但是好像并查集可以合并但不能分开~~我不知道有没有这样的并查集~~，那正着不好想，那我们就反着想嘛，思路一下就就打开了。

反着想的话，那就把边连接起来，然后我们就可以用并查集维护了。

我们不是要求有多少对吗，我们可以用 $size$ 数组维护联通块的点的个数，连边的时候就减去这两个联通块如果分开所产生的对数。

## 实现细节

> 注意答案可能不在 int 范围内。

一场 OI 一场空，不开 long long 见祖宗。

~~这道题是真的良心~~。

具体细节请看代码。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, u[N], v[N], fa[N], Size[N];
long long ans[N];

int find(int x) {// 标准并查集
	if (x != fa[x]) fa[x] = find(fa[x]);
	return fa[x];
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i ++)
		scanf("%d%d", &u[i], &v[i]);

    // 初始化
	for (int i = 1; i <= n; i ++)
		Size[i] = 1;
	for (int i = 1; i <= n; i ++)
		fa[i] = i;

	ans[m] = (long long)n * (n - 1) / 2;// 每个点各自为一个联通块
	for (int i = m; i > 1; i --) {// 倒序
		int x = find(u[i]), y = find(v[i]);
		if (x == y)// 如果删除这条边还在这个联通块的话，那么就不会增加对数
			ans[i - 1] = ans[i];
		else {
			ans[i - 1] = ans[i] - (long long)Size[x] * Size[y];// 减去删除这条边所产生的对数
			fa[y] = x;// 令y的父亲为x
			Size[x] += Size[y], Size[y] = 0;// 加上联通块y的点的数量
		}
	}

	for (int i = 1; i <= m; i ++)
		printf("%lld\n", ans[i]);

	return 0;
}
```

码风不行，不喜勿喷。

---

## 作者：μηδσ (赞：3)

## Description

给你$n$个小鸟,$m$条边,问你从第一条边开始删的时候,每次删除一条边存在多少对不连通的小鸟

## Solution

题目要求我们删边，正着的思路并不是很好想(也可能是我太弱了想不出来

于是我们决定倒着思考，从第一条边开始加边，直到加到第$m$条边，然后统计一下每个连通块的数量。

每增加一条边，都会导致一些新的小鸟联通，统计这些新的对数，就是删掉这条边的时候回砍掉对少对。

这里顺便介绍一下scanf的返回值

其实scanf这个东西是有返回值的（~~想不到吧~~

scanf的返回值类型是正确输入的个数，比如我要输入多组数据的时候可以使用，非常的方便

~~~cpp
while(scanf("%d%d", &n, &m) == 2) //表示检查输入的数据中时候有两个是合法输入
~~~

这里其实也可以用一下这两个


~~~cpp
while(scanf("%d%d", &n, &m) != EOF)

while(cin >> n >> m)

~~~

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;

const int MAXN = 100005;

int u[MAXN], v[MAXN];
int pre[MAXN], sum[MAXN];
ll ans[MAXN]; 

int find(int x){	
	if(x == pre[x])
		return x;
	return pre[x] = find(pre[x]);
}

void join(int a, int b){ 
	a = find(a), b = find(b);
	if(a != b){
		sum[a] += sum[b];
		sum[b] = 0;
		pre[b] = a;
	}
}

int main(){
	int n, m;
	while(scanf("%d%d", &n, &m) == 2){ 
		for(int i = 0;i <= MAXN;i++){
			sum[i] = 1; 
			pre[i] = i;
		}
		memset(ans, 0, sizeof(ans));
		for(int i = 1;i <= m;i++)
			cin >> u[i] >> v[i];
		ll cnt = n;
		ans[m + 1] = cnt * (cnt - 1) / 2;
		for(int i = m;i >= 2;i--){
			int tmpu = find(u[i]);
			int tmpv = find(v[i]);
			if(tmpu != tmpv){
				ans[i] = ans[i + 1] - sum[tmpu] * sum[tmpv];
				join(u[i], v[i]);
			}
			else
				ans[i] = ans[i + 1];
		}
		for(int i = 2;i <= m +1;i++)
			cout << ans[i] << endl;
	}
	return 0; 
}
~~~

---

## 作者：Morax_ (赞：2)

# [AT4319 [ABC120D] Decayed Bridges](https://www.luogu.com.cn/problem/AT4319) 题解

### 题意

~~题意显然，目标明确，~~ 我们要求出在依次删去一个无向图的边之后有多少对点不联通。

### 正文

~~思路显然，~~ 我们将删边操作反过来，变成建边，并查集维护即可。

**注意：以下一段的答案一词含义为删去第 $i$ 条边后有多少对点联通而非不联通**

最开始的时候，所有点都不联通，此时答案为 $0$。

然后，每加一条边，就判断两点 $a_i,b_i$ 是否属于同一个集合，

如果是，那么这一步的答案为： $size_{a_i}\times size_{b_i}+ans_{i-1}$。

其中 $size_a,size_b$ 为 $a,b$ 所属集合的元素个数， $ans_{i-1}$ 为上一步的答案，初始为 $0$。

然后合并两点所属集合。

如果不是，说明不会产生新的答案，此时答案为 $ans_{i-1}$。

最后，逆序输出 $\frac{N\times (N-1)}{2}$ 减去每一步的答案即可。

$\frac{N\times (N-1)}{2}$ 是所有点都不联通时的不联通点对个数（任意选出两点都不联通，即 $C^2_N=\frac{N\times (N-1)}{2}$）。

**注意：本题要开 long long。**

### 代码（码风怪异，勿喷）

```c++
#include <stdio.h>
#include <utility>

long long fa [100005];//并查集中的每个点的父亲
long long si [100005], ans [100005];//集合大小和答案
std :: pair <long long, long long> bri [100005];

long long find (long long x) {
    if (x != fa [x])
        fa [x] = find (fa [x]);
    return fa [x];
}//并查集找根

void merge (long long x, long long y) {
    long long rx = find (x), ry = find (y);
    fa [ry] = rx;
    si [rx] += si [ry];
}//并查集合并

int main () {
    long long n, m;
    scanf ("%lld%lld", &n, &m);
    for (long long i = m; i >= 1; -- i) {
        long long a, b;
        scanf ("%lld%lld", &a, &b);
        bri [i] = {a, b};
    }//保存删边的顺序，方便反着来
    
    for (long long i = 1; i <= n; ++ i) {
        fa [i] = i;
        si [i] = 1;
    }//初始化
    
    long long end = n * (n - 1) >> 1;//所有点都不联通时的不联通点对个数
    for (long long i = 1; i <= m; ++ i) {
        long long a = bri [i].first, b = bri [i].second, ra = find (a), rb = find (b);
        if (ra != rb) {
            ans [i] = si [ra] * si [rb] + ans [i - 1];
            merge (a, b);//当a,b不为同一集合
        } else
            ans [i] = ans [i - 1];//当a,b为同一集合
    }
    
    for (long long i = m - 1; i >= 1; -- i)
        printf ("%lld\n", end - ans [i]);//输出答案
    printf ("%lld", end);//输出最终情况答案
}
```

---

完！

推荐几道相似的题：[P1197](https://www.luogu.com.cn/problem/P1197)，[P8359](https://www.luogu.com.cn/problem/P8359)，[P6121](https://www.luogu.com.cn/problem/P6121)。

---

## 作者：紊莫 (赞：1)

## 题意

给定一个 $n$ 个点，$m$ 条边的无向图，每次删除一条仍未被删除的边，共删除 $m$ 次。  

求每一次删除后有多少对 $(x,y)$ 不能联通。  

## 分析

容易想到用并查集来维护各个点之间的连通性，可惜并查集并不能方便的进行“删除”操作，因此可以转化一下，从最后一次删除开始向上倒推，不断建立被删除的边。  

容易想到在所有节点都被摧毁时的答案即 $\frac{n(n-1)}{2}$。  

之后每一次建立新的边，都在上一个答案的基础上减去两者连接数目的乘积。  

例如当前的 $u$ 连接了节点 $2$ 和 $4$，$v$ 连接了 $1$ 和 $3$。  

![](https://cdn.luogu.com.cn/upload/image_hosting/hi0cay4n.png)  

就会有如图四种排列方式。  

初始的，每个节点的连接数目就是 $1$，即自己。  

## 代码

基础的并查集操作，按倒序处理即可。  

主要分析下 ``merge`` 函数中的操作（~~因为自己被坑了~~）。  

```cpp
void merge(int x,int y)
{
	if(x!=y)
	{
		link[x]+=link[y];
		f[find(y)]=find(x);
	}
}
```  
其中第六行的意思是将 ``y`` 所在的集合并到 ``x`` 的集合里，所以才有上一行的相加顺序。  

完整的代码就不放了，需者可自取。  
[$Code$](https://www.luogu.com.cn/paste/arhpuggl)


---

## 作者：HMZHMZHMZ (赞：1)

## 题意

给定一个联通的无向图，每次操作删去一条边，求每次删去后 $\sum_{1 \leq x ,y \leq n}D(x,y) $ 的值。

定义 $ D(x,y) $ 表示 $ x ,y $ 不连通。

## 思路

考虑倒序操作。每一次连接边两边的点，如果他们本身就联通，那么不会产生新的连通块。如果不连通，那么增加的联通点个数就为两个连通块大小之积。

将当前答案记为 $ ans $，然后输出的数就是 $ \frac{n \times (n-1)}{2} - ans $。

用并查集实现。

时间复杂度 $ O(n\alpha(n)) $。

## 代码

```cpp

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
struct node{
	ll from,to;
}a[N];
struct bcj{
	ll siz,fa;
}f[N];
ll n,m,cnt;
ll ans[N],now;
inline ll find(ll x){
	if(f[x].fa==x) return x;
	return f[x].fa=find(f[x].fa);
}
inline void add(ll x,ll y){
	now+=1ll*f[find(x)].siz*f[find(y)].siz;
	f[find(y)].siz+=f[find(x)].siz;
	f[find(x)].fa=find(y);
}
inline ll read(){
	ll s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
int main(){
	n=read(),m=read();
	for(register ll i=1;i<=n;++i) f[i]=(bcj){1,i};
	for(register ll i=m;i>=1;--i) a[i].from=read(),a[i].to=read();
	for(register ll i=1;i<=m;++i){
		ans[i]=now;
		if(find(a[i].from)!=find(a[i].to)) add(a[i].from,a[i].to);
	}
	ll tot=n*(n-1)>>1;
	for(register ll i=m;i>=1;--i) printf("%lld\n",tot-ans[i]);
	return 0;
}

```

---

## 作者：hxhhxh (赞：1)

## 大意

$ n $ 个点， $ m $ 条边，边依次断开，定义 $ con(i,j) $ 为两个点 $ i $ 和 $ j $ 是否不连通。求每一次断开一条边后

$$ \sum_{i=1}^n \sum_{j=i+1}^n con(i,j) $$

## 思路

反向操作，问题转化为每一次连一条边，求答案

用带权并查集，每一次连接会减少 $ size(a) \times size(b) $ 对联通点。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[100005],siz[100005],n,m,ea[100005],eb[100005],ans[100005];
int dfs(int x){
	if(f[x]==x) return x;
	return f[x]=dfs(f[x]);
}
signed main(){
	cin>>n>>m;
	int an=0;
	for(int i=1;i<=n;i++) f[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++) scanf("%lld %lld",&ea[i],&eb[i]);
	for(int i=m;i>=1;i--){
		ans[i]=an;
		if(dfs(ea[i])!=dfs(eb[i])){
			int sa=siz[dfs(ea[i])],sb=siz[dfs(eb[i])];
			an+=sa*sb;
			siz[dfs(eb[i])]+=sa;
			f[dfs(ea[i])]=dfs(eb[i]);
		}
	}
	for(int i=1;i<=m;i++) printf("%lld\n",n*(n-1)/2-ans[i]);
	return 0;
}
```

---

## 作者：徐晨轩✅ (赞：1)

# $ \mathtt{Description} $

> 有 $ m $ 座桥，这些桥会相继断开。
>
> 每断开一次，求有多少对顶点不能连通。

# $ \mathtt{Solution} $

标签：并查集

难度：普及/提高-

分析：这题说是一个一个断开，不如想成一个一个连起来。我们用一个并查集，倒序遍历每一条边，如果这一条边的两个顶点属于一个连通块，那么这条边加了等于没加，即`ans[i-1]=ans[i]`，而如果这两个点不属于一个连通块，那么这一条边加上后，这两个连通块就合并为一个连通块了，即`ans[i-1]=ans[i]-size[ff]*size[ft]`，还要进行 $ \mathtt{merge} $ 操作，也就是`merge(ff,ft)`。最后输出 $ \mathtt{ans} $ 数组就行了。

# $ \mathtt{Code} $

```cpp
#include <stdio.h>
int n,m,ff,ft,f[100001];
long long ans[100001],size[100001];
struct node
{
	int from;
	int to;
}ge[100001];
int find(int x)
{
	if(f[x]!=x)f[x]=find(f[x]);
	return f[x];
}
void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	f[fx]=fy;
	size[fy]+=size[fx];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		f[i]=i,size[i]=1;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&ge[i].from,&ge[i].to);
	ans[m]=1LL*n*(n-1)/2;
	for(int i=m;i>=1;i--)
	{
		ff=find(ge[i].from),ft=find(ge[i].to);
		if(ff==ft)ans[i-1]=ans[i];
		else ans[i-1]=ans[i]-size[ff]*size[ft],merge(ff,ft);
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：Nightingale_OI (赞：0)

### 大意

有 $ n $ 个点， $ m $ 条无向边，每条边按顺序消失。

问你每条边消失后不能互相到达的点对的数量（不记方向）。

### 思路

用权值并查集倒着记录能到的点对，用总点对数减去即可。

时间复杂度 $ O(n) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define c(x) 1ll*(x)*(x-1)/2
int fa[101010];
int le[101010];
int ri[101010];
int siz[101010];
long long ans[101010];
int fifa(int x){return x==fa[x]?x:fa[x]=fifa(fa[x]);}
int main(){
    cin>>n>>m;
    f(i,1,n)fa[i]=i;
    f(i,1,n)siz[i]=1;
    f(i,1,m)scanf("%d %d",&le[i],&ri[i]);
    ans[m]=c(n);
    g(i,m,1){
        ans[i-1]=ans[i];
        s=fifa(le[i]);
        l=fifa(ri[i]);
        if(s!=l){
            ans[i-1]-=c(siz[s]+siz[l])-c(siz[s])-c(siz[l]);
            fa[s]=l;
            siz[l]+=siz[s];
        }
    }
    f(i,1,m)printf("%lld\n",ans[i]);
    return 0;
}
```

---

