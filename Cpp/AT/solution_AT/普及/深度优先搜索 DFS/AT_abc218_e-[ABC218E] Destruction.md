# [ABC218E] Destruction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc218/tasks/abc218_e

$ N $ 頂点 $ M $ 辺の連結無向グラフがあります。  
 頂点には $ 1 $ から $ N $ の番号が、辺には $ 1 $ から $ M $ の番号がついており、辺 $ i $ は頂点 $ A_i $ と $ B_i $ を結んでいます。

高橋君は、このグラフから $ 0 $ 個以上の辺を取り除こうとしています。

辺 $ i $ を取り除くと、$ C_i\ \geq\ 0 $ のとき $ C_i $ の報酬を得、$ C_i\ <\ 0 $ のとき $ |C_i| $ の罰金を払います。

辺を取り除いたあともグラフが連結でなければならないとき、高橋君が得られる報酬の最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ -10^9\ \leq\ C_i\ \leq\ 10^9 $
- 与えられるグラフは連結である
- 入力に含まれる値は全て整数である

### Sample Explanation 1

辺 $ 4,5 $ を取り除くことで合計 $ 4 $ の報酬を得られます。これより多くの報酬を得ることはできないため、答えは $ 4 $ となります。

### Sample Explanation 2

報酬が負であるような辺が存在することもあります。

### Sample Explanation 3

多重辺や自己ループが存在することもあります。

## 样例 #1

### 输入

```
4 5
1 2 1
1 3 1
1 4 1
3 2 2
4 2 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 0
3 1 -1```

### 输出

```
1```

## 样例 #3

### 输入

```
2 3
1 2 -1
1 2 2
1 1 3```

### 输出

```
5```

# 题解

## 作者：JoyLosingK (赞：3)

注意：剩下的图必须是****连通****图，所以我们考虑造一棵原图的生成树。

题目让我们选出的边权最大，那么剩下的一定是最小的，然而是一棵生成树，那么必定是一棵最小生成树。

我们考虑 Kruskal 算法，首先将所有边按照边权排序，利用贪心的思想选择边权最小的边，然后把它接上。如果图中出现了环，那么就不用它。反之则把它添加到我们的最小生成树里。

那么该如何判断环呢？如果每次都用深搜或着广搜的话时间一定会炸的。我们可以使用[并查集](https://oi-wiki.org/ds/dsu/)来判断是否出现环。

还有一个很重要的细节，图中的边可能是****负权边****，所以我们遍历到的时候直接将它加入最小生成树即可。

时间复杂度大概为 $O(m\log m)$。


```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<stdio.h>
#include<string>
#define int long long //开longlong
using namespace std;
const int N=1e5+5; //数组要开大
int n,m,fa[N],k,c,ans,st,lt;
struct Edge{int u,v,w;} d[N]; //邻接表存边
bool cmp(Edge a,Edge b){return a.w<b.w;} //按照边权从小到大排序
int find(int x){ //并查集的路径压缩
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];}
main(){ cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>d[i].u>>d[i].v>>d[i].w,st+=d[i].w; //输入
	for(int i=1;i<=n;i++) fa[i]=i; //并查集初始化
	sort(d+1,d+m+1,cmp);
	while(m--){ c++; //考虑每一条边
		int us=find(d[c].u);
		int vs=find(d[c].v); //判环
		if(us!=vs) k++,fa[us]=vs,ans+=d[c].w;
		else if(d[c].w<0) ans+=d[c].w; //特判负权边
	} cout<<st-ans; //注意不是输出剩下的而是输出取走的
	return 0; //好习惯！！！！
}
```

[AC链接](https://www.luogu.com.cn/record/179661223)

谢谢审核的管理员，你们辛苦了！！！

---

## 作者：PineappleSummer (赞：1)

[[ABC218E] Destruction](https://www.luogu.com.cn/problem/AT_abc218_e)

最小生成树板子题。

要求选出的边权总和最大，就要使剩下的边权总和最小，而剩下的又是连通图，所以剩下最小生成树一定是最优的。

但是这题又有负权边，所以对于不是最小生成树中的边，我们只选边权为正的边，舍弃边权为负的边。

[参考代码](https://atcoder.jp/contests/abc218/submissions/58283004)，时间复杂度 $O(m\log m)$，瓶颈为排序。

---

## 作者：Redamancy_Lydic (赞：0)

题意很一眼，如果单纯跑最大生成树的话无法保证剩下的图联通，但是注意到边权和相等，所以问题转化为求总和减去最小生成树的差。

正常做的话会错，因为题目中存在负权边。但是负权边最后一定都在选出的最小生成树中，所以直接放进去最后一块减即可。

[提交记录](https://atcoder.jp/contests/abc218/submissions/58283044)

---

## 作者：Happy_mouse (赞：0)

# [Destruction](https://www.luogu.com.cn/problem/AT_abc218_e) 题解
[AC证明](https://www.luogu.com.cn/record/173706994)

## 分析与解答
删边仍为连通图？

剩的最大？

这不由得让我们联想到了最小生成树。对啊，剩的最大，不就是取得最小吗？

考虑用 [Kruskal](https://blog.csdn.net/qq_41754350/article/details/81460643?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522172411546416800186575729%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=172411546416800186575729&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-81460643-null-null.142^v100^pc_search_result_base2&utm_term=kruskal&spm=1018.2226.3001.4187)（不会的赶快加餐） 求最小生成树，统计剩下的边。

注意一个小坑：

数据范围 $-10^9\le C_i\le 10^9$，即**边权可能为负**。

想都别想，直接往树里塞，如果不加，会导致剩余边权和更小，与题意不符。

反正树加了边还是连通图，生成树需要这条边，还是得加。

## 代码
话不多说，看代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
struct nd{
	int u,v,w;
	bool operator <(const nd&x)const{//重载运算符，对边权排序
		return w<x.w;
	}
} a[N];
int fa[N];
int belong(int u){//并查集搜索
	if(u!=fa[u]) return fa[u]=belong(fa[u]);
	return u;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//输入
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i].u>>a[i].v>>a[i].w;
	//初始化
	for(int i=1;i<=n;i++) fa[i]=i;
	//排序
	sort(a+1,a+m+1);//因为已重载过运算符，不必写排序函数
	//kruskal重构树
	int cnt=0;
	for(int i=1;i<=m;i++){
		int u=a[i].u,v=a[i].v,w=a[i].w;
		bool f=0;//标记是否用到该边
		if(w<0) f=1;//如果边权为负，直接标记
		if(belong(u)!=belong(v)){//如果两节点不在同一个连通块
			fa[belong(u)]=belong(v);//合并
			f=1;//标记
		}
		if(!f) cnt+=w;//如果没有标记（没用到），加上边权
	}
	//输出
	cout<<cnt;
	return 0;//华丽结束
}
```

---

## 作者：shitingjia (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc218_e)

### 题目思路
选出几个边边权总和最大，并且剩下的图要是一个连通图。

转化一下，就是在图中找**最小生成树**，输出总边权减去生成树的边权和。可以用 Kruskal 解决。

看看数据范围：

$-10^9 \le C_i \le 10^9$

边权可能为负数。所以遇到负边权时，直接加入生成树，可以这么理解：

- 如果这条边权为负的边连接了两个**原本不相通的**连通分量，那么遵循 Kruskal 算法的原则，加入生成树。

- 如果这条边权为负的边已经**在一个连通分量中**，那么加入生成树还可以减小答案，必须加啊。

### AC Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=2e5+5;
int n,m,fat[N];
LL sum,ans;//防止溢出！
struct node{
	int u,v,w;
}e[N];
bool cmp(node s1,node s2){
	return s1.w<s2.w;
}
int find(int x){
	if(fat[x]!=x)	fat[x]=find(fat[x]);
	return fat[x];
}
bool un(int x,int y){//检查合并是否成功 
	int fx=find(x),fy=find(y);
	if(fx!=fy){
		fat[fx]=fy;
		return 1;
	}
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
		sum+=e[i].w;	
	}
	for(int i=1;i<=n;i++)	fat[i]=i;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		bool fl=0;
		fl=un(e[i].u,e[i].v);
		if(e[i].w<0||fl)	ans+=e[i].w;//小于0直接加入 或 合并成功 
	}
	printf("%lld",sum-ans);
	return 0;
}
```

---

## 作者：chl090410 (赞：0)

## The Solution to [ABC218E] Destruction

### 题目大意

给一个无向图，让你从中选出几个边，要求选出的边权总和最大并且剩下的图要是一个连通图，输出最大的边权。

### 分析

因为选出的边权总和要最大，而无向图中所有边的边权总和又不变，所以剩下的边的边权总和要最小。

又因为剩下的图要是一个连通图，所以自然想到[最小生成树](https://oi-wiki.org/graph/mst/)，而 $2\le N\le2\times10^5$，所以 $O(N^2)$ 的 Prim 算法肯定不行。因为 $M\le2\times10^5$，所以考虑使用时间复杂度为 $O(M\times logM)$ 的 Kruskal 算法。

因为图中还有负权边，而选择了负权边一定会让选出的边权总和变小，所以，若图中有负权边，直接放入生成树即可。

### 下面附上完整代码：

```
#include<bits/stdc++.h>
#define int long long
#define maxn 10000000
using namespace std;
int n,m,fa[maxn],k=0,c=0,ans=0,kkk,lt;
struct node{
	int u,v,w;
}e[maxn];
bool cmp(node a11,node a22){
	return a11.w<a22.w;
}
int find(int x){
	if(x!=fa[x]){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
		kkk+=e[i].w;
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	sort(e+1,e+m+1,cmp);
	while(m--){
		c++;
		int u1=find(e[c].u);
		int v1=find(e[c].v);
		if(u1!=v1){
			k++;
			fa[u1]=v1;
			ans+=e[c].w;
		}else if(e[c].w<0){
			ans+=e[c].w;
		} 
	}
	cout<<kkk-ans;
	return 0;
}

---

## 作者：CodingOIer (赞：0)

## [ABC218E] Destruction 题解

### 思路分析

这道题的题意是去掉一些边，使得去掉的边权值和最大，且剩下的图连通。

转换一下就是选出一些边，使得这些边的权值最小，且图连通。

这不是最小生成树模板吗？

但是要注意一个细节：这道题中存在负权边，此时不管是否连通，都因该留下这条边，因为这条边的贡献为负。

### 代码实现

下面是使用 [Kruskal](https://oi-wiki.org/graph/mst/#kruskal-%E7%AE%97%E6%B3%95) 算法实现的本题代码：

```cpp
#include <algorithm>
#include <cstdio>
void add(int, int);
int find(int);
class edge
{
  public:
    int len;
    int u, v;
    friend bool operator<(const edge &x, const edge &y)
    {
        return x.len < y.len;
    }
};
const int MaxN = 2e5 + 5;
int n, m;
int f[MaxN];
long long min;
long long sum;
edge link[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        f[i] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &link[i].u, &link[i].v, &link[i].len);
        sum += link[i].len;
    }
    std::sort(link + 1, link + 1 + m);
    for (int i = 1; i <= m; i++)
    {
        if (find(link[i].u) != find(link[i].v) || link[i].len < 0)
        {
            add(link[i].u, link[i].v);
            min += link[i].len;
        }
    }
    printf("%lld\n", sum - min);
    return 0;
}
void add(int x, int y)
{
    f[find(y)] = find(x);
}
int find(int x)
{
    if (f[x] != x)
    {
        f[x] = find(f[x]);
    }
    return f[x];
}
```

附：[P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)

---

## 作者：asas111 (赞：0)

## 前置知识
[最小生成树](https://www.luogu.com.cn/problem/solution/P3366)。

## 思路
要让选出的边权总和最大，就得让剩下的边权总和最小。这题就转化成一个最小生成树问题，答案用边权总和减去最小生成树就行。

根据数据范围，$2\le N\le2\times10^5$，$N-1\le M\le2\times10^5$，可以用 Kruskal 算法（实际上是不会写 Prim 的堆优化），时间复杂度 $O(n\log n)$，可以通过此题。

代码和模板并没有太大的变化，但需要判断负边权。负边权在答案中反而会使答案变小，所以遇到负边权就把它放进最小生成树里，就可以通过了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1e9
using namespace std;
const int N=200009;
int n,m,fa[N],s=0;
struct edge{int u,v,w;}e[2*N];
bool cmp(edge a,edge b){return a.w<b.w;}
int root(int x){return fa[x]==x?x:fa[x]=root(fa[x]);}//找祖先
void unite(int x,int y){fa[root(x)]=root(y);} //合并
int kruskal(){
	int sum=0;
	for(int i=1;i<=n;i++)fa[i]=i;//并查集初始化
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=m;i++)
		if(root(e[i].u)!=root(e[i].v)){//判断连通性
			sum+=e[i].w;
			unite(e[i].u,e[i].v);
		}
		else if(e[i].w<0)sum+=e[i].w;//处理负边权
	return sum;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
		s+=e[i].w;
	}
	cout<<s-kruskal();
	return 0;
}
```


---

## 作者：Hog_Dawa_IOI (赞：0)

### 题意简述
给一个无向图，让你从中选出几个边，要求选出的边权总和最大并且剩下的图要是一个连通图，输出最大的边权。
### 思路分析
第一眼：这不就总边权减去最小生成树吗？     
几秒后：开打 Kruskal！      
交上去：唉，怎么答案错误八十五分啊！！！      
参考别人代码：哦，忘了判负边。      
再交上去：哇，通过啦！！！     

通过我的经历，大家也看出来我们的思路了。     
的确，答案就是总边权减去最小生成树。但是对于负边权的边，我们不能删去（因为会多罚金，减少利润），所以我们需要特别判断。     
肉眼可见的，使用 Kruskal 求解（prim 在这里太慢了，复杂度为 $O(n^2)$，无法通过）。        
不过这个算法和平常的 Kruskal 有所不同，下面提供算法流程。    
1. 读入数据，对每一条边按照边权从小到大进行排序。   
1. 按顺序遍历每一条边，如果这条边的边权为负数，那么无条件选择这条边，统计答案（不管这条边两个端点是否在同一集合），并把这条边两个端点所在的集合合并（即并查集合并操作，若这两个端点不在同一集合亦可不做操作）。
1. 否则，如果这条边两个端点在同一集合，则统计答案，把这条边两个端点所在的集合合并，否则不做操作。
1. 最后把总边权减去统计好的答案，就是最后想要的结果。  

### 参考代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct sss{long long a,b,c;}bian[400005];
bool cmp(sss a,sss b) {return a.c<b.c;}
long long n,m,num,father[200005],ans,sum;
long long fa(long long where)
{
    if(father[where]==where) return where;
    return father[where]=fa(father[where]);
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) father[i]=i;
    for(int i=1;i<=m;i++) scanf("%lld%lld%lld",&bian[i].a,&bian[i].b,&bian[i].c),sum+=bian[i].c;
    sort(bian+1,bian+m+1,cmp);
    for(int i=1;i<=m;i++)
    {
        if(bian[i].c<0)
        {
            if(fa(bian[i].a)!=fa(bian[i].b)) father[fa(bian[i].a)]=fa(bian[i].b);
            ans+=bian[i].c;
        }
        else if(fa(bian[i].a)!=fa(bian[i].b)) father[fa(bian[i].a)]=fa(bian[i].b),ans+=bian[i].c;
    }
    printf("%lld",sum-ans);
}
```

---

## 作者：zyxabcd (赞：0)

## 题意

给一个无向图，让你从中选出几个边，要求选出的边权总和最大并且剩下的图要是一个连通图，输出最大的边权。

## 分析

我们反向思考一下，要使得选出的边权总和最大，那就是让剩下的图边权总和最小，还要保证它是连通图。所以首先想到 [最小生成树](https://baike.so.com/doc/6806060-7023006.html) 。用生成树跑出来最小的边权和，然后计算图上所有边的边权总和，最后相减就能得出答案。

我们开始考虑细节。直接跑最小生成树肯定是不行的，因为题目上有负权边。但是负权边我们最终答案里面肯定不能选择的。所以我们只需要特判一下，只要我们在跑最小生成树只要碰到负边权我们就给把它放进图里，这样就能保证最终答案里没有负权边。

然后就可以上代码了

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;
#define ll long long
const int N = 200010, M = 200010, INF = 0x3f3f3f3f;

int n, m;
int p[N];

struct Edge {
    int a, b, w;

    bool operator<(const Edge &W) const //重载运算符以便于能直接sort
    {
        return w < W.w;
    }
} edges[M];

int find(int x) //并查集
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

ll kruskal() {
    sort(edges, edges + m);

    for (int i = 1; i <= n; i++) p[i] = i;    // 初始化并查集

    ll res = 0, cnt = 0;
    for (int i = 0; i < m; i++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;

        a = find(a), b = find(b);
        if (a != b)//找到的祖宗不相等说明不连通
        {
            p[a] = b;
            res += w;
            cnt++;
        }
        else {
            if (w < 0)res += w;
        }
    }

    return res;
}

int main() {
//freopen("des.in","r",stdin);
//freopen("des.out","w",stdout);
    ll sum = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
        sum += w;
    }

    cout << sum - kruskal();


    return 0;
}

```


---

## 作者：I_Like_Play_Genshin (赞：0)

第一次看到裸题还能写题解！

## Solution

一眼题，要求选出来的权值最大，跑个 Kruskal 就行了，另外，如果剩余的边里面有负权边，就直接跳过。

## Code

懒得写，一个模板套一下不就行了。

---

