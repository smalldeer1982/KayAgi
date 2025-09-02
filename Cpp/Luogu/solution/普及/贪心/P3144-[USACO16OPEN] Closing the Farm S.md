# [USACO16OPEN] Closing the Farm S

## 题目背景

*本题和 [金组同名题目](/problem/P6121) 在题意上一致，唯一的不同是数据范围。*

## 题目描述

FJ 和他的奶牛们正在计划离开小镇做一次长的旅行，同时 FJ 想临时地关掉他的农场以节省一些金钱。

这个农场一共有被用 $M$ 条双向道路连接的 $N$ 个谷仓（$1 \leq N,M \leq 3000$）。为了关闭整个农场，FJ 计划每一次关闭掉一个谷仓。当一个谷仓被关闭了，所有的连接到这个谷仓的道路都会被关闭，而且再也不能够被使用。

FJ 现在正感兴趣于知道在每一个时间（这里的“时间”指在每一次关闭谷仓之前的时间）时他的农场是否是“全连通的”——也就是说从任意的一个开着的谷仓开始，能够到达另外的一个谷仓。注意自从某一个时间之后，可能整个农场都开始不会是“全连通的”。

## 样例 #1

### 输入

```
4 3
1 2
2 3
3 4
3
4
1
2```

### 输出

```
YES
NO
YES
YES```

# 题解

## 作者：sdxjzsq (赞：35)

感觉楼上用并查集的题解注释太少，看起来好吃力，趁自己明白给大家讲讲自己的并查集做法...

首先读入相连的点，但这里不能直接合并建立并查集，因为并查集没有Ctrl+Z操作(就是无法分离两个已经合并的集合)，所以我们要先存起来，等所有的询问都读入之后，倒着进行操作。

我们考虑怎样倒着操作：

首先，读入数据，把所有的数据都存起来，其中x[i],y[i]表示第i次读入的关系，order[i]表示第i次读入的数是多少，ss[i]表示i是否在并查集里面，如果存在，则为0，不存在则为1。

之后，把所有没有去掉的点之间的关系都加到并查集里面，但是在这个题看来，应该tan90，因为读入节点个数N之后，就进行了N次关闭操作，但是为了代码的普适性，我保留了这部分代码。（其实是开始没注意，一些题解才发现这里可以删掉...）

接着，倒着处理读入的询问。从第i=n次开始，把与点order[i]有关的边读入，合并并查集，之后在把和该点有关的所有的可加入的边都加入并查集以后，判断并查集中集合的个数，并记录在ans[i]中，然后i--，重复以上步骤。

最后，从1开始到n-1，判断ans是否为1，如果为1，说明所有的点都是联通的，输出YES，否则输出NO，第n次询问的时候，所有的点都已经从并查集删除，因此一定是联通的，输出YES。


代码如下：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,g[3001],x[3001],y[3001],order[3001],ss[3001],ans[3001],w;
//x[i],y[i]表示第i次读入的关系，order[i]表示第i次读入的数是多少，ss[i]表示i是否在并查集里面，如果存在，则为0，不存在则为1
//g[i]存储并查集，ans[i]存储第i次询问时并查集中有多少个集合。
int find(int u)
{
    if(g[u]!=u)g[u]=find(g[u]);
    return g[u];
}
void merg(int u,int v)
{
    u=find(u);
    v=find(v);
    if(u==v)return;
    g[u]=v;
}
int main()
{
    memset(ss,0,sizeof(ss));
    scanf("%d%d",&n,&m);
    for(int j=1;j<=n;j++)g[j]=j;
    for(int i=1;i<=m;i++)
        scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&w);
        order[i]=w;
        ss[w]=1;
    }
```
/\*
//如果题目中关闭农场的个数小于N的时候要加上这段代码

    for(int i=1;i<=m;i++)

        if(ss[x[i]]==0&&ss[y[i]]==0)

            merg(x[i],y[i]);

\*/
```cpp
    for(int i=n;i>0;i--)
    {
        ss[order[i]]=0;
        for(int j=1;j<=m;j++)
            if(ss[x[j]]==0&&ss[y[j]]==0)
                merg(x[j],y[j]);
        ans[n]=0;
        for(int j=1;j<=n;j++)
            if(find(j)==j&&ss[j]==0)
                ans[i]++;
    }
    for(int i=1;i<=n-1;i++)
        if(ans[i]==1)printf("YES\n");
        else printf("NO\n");
    printf("YES");
    return 0;
}
```

---

## 作者：fls233666 (赞：23)

题面中说，**FJ感兴趣于关闭每个谷仓后，农场的联通状况**。显然，如果每次关闭谷仓后就去遍历整个图，会比较耗时。那么，我们用**并查集**试一试。

我们知道，**如果两个谷仓之间有双向道路连接，那么我们就可以认为这两个谷仓是连通的。** 于是，我们可以**把每条双向道路连接的两个谷仓所在集合合并，表示这两个谷仓连通的。** 这样操作后，**如果所有开启的谷仓在同一个集合中（即有着相同的代表元素），那么这个农场就是“全连通的”。**

但是，我们发现一个问题：**如果在开始时根据谷仓之间的双向道路合并完成后，关闭谷仓的操作实现将十分困难**。

这个时候，正着想不行，就倒过来试试——**让谷仓一间一间地“开启”，判断连通情况，把判断结果逆序输出。**

显然，倒过来做这题会容易实现很多。那么，我们归纳一下程序的实现步骤。

1. 读入数据并初始化
2. 按照谷仓关闭的顺序逆序操作
3. **把当前要“开启”的谷仓的所有道路“开启”——合并道路连接的两个谷仓所在集合**
4. **判断所有已经开启的谷仓是否在同一个集合中**，存储判断结果
5. 输出判断结果

下面是AC代码：

```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
  
int f[3003];  //存储每个元素所在集合代表元素
int fd(int x){  //并查集的查找函数
    return x==f[x]?x:f[x]=fd(f[x]);
}
//并查集
  
vector<int>ck;  
//存储已经开放的谷仓，方便检查农场是否为全连通
  
int main(){
    int n,m;
    cin>>n>>m;  //读入n和m
    vector<int>road[n+1];
  //road[i]存储连接了谷仓i的所有路径
    for(int u,v,i=0;i<m;i++){
        cin>>u>>v;
        road[u].push_back(v);
        road[v].push_back(u);
    }  //读入每条双向道路并存储
    bool p[n+1],open[n+1];
  //p[i]代表关闭第i个谷仓前农场是否全连通
  //open[i]代表第i个谷仓是否开放，便于合并操作
    int close[n+1];
  //close[i]代表第i次操作时关掉的谷仓编号
    for(int i=1;i<=n;i++)
        cin>>close[i];  //读入每次关掉的谷仓编号
    memset(open,false,sizeof(open));
  //初始化open[]，逆推，所有谷仓都是关闭的
    memset(p,true,sizeof(p));
  //初始化p[]，假设每次操作后农场都是全连通的
  
  //以上为初始化和数据读入
  
    for(int u,i=n;i;i--){
        u=f[close[i]]=close[i];  //初始化对应集合
        open[close[i]]=true;  //标记谷仓开放
        ck.push_back(close[i]);  //加入检查对象
        if(i==n) continue;
  //第n次操作前只有一个谷仓开放，所以农场一定是全连通的
        for(int v,j=0;j<road[close[i]].size();j++){
            //合并该谷仓有连接的所有道路上的谷仓
            if(open[road[close[i]][j]]){
           //判断在道路上的谷仓是否有开放
                v=fd(road[close[i]][j]);
            //有开放则判断是否连通
                if(v!=u) //如果没有连通则合并所在集合
                    f[v]=u;
            }
        }
        //开放谷仓并合并开放的道路所连接的谷仓
                                                    
        u=fd(ck[0]);
        for(int j=1;j<ck.size();j++){
            if(u!=fd(ck[j])){
                p[i]=false;
                break;
            }
        }
  		//检查已开放的谷仓是否全连通
  		//即检查它们是否是一个相同的代表元素
  
    }
  
  //以上是开放谷仓判断操作，以下就是输出
  
    for(int i=1;i<=n;i++)
        if(p[i]) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    return 0; 
} 
```


---

## 作者：Parabola (赞：13)

### Part0.题外话

事实上这题的Gold是$N <= 300000 , M <= 300000$的。

然后你们那种$n^2$乱水事实上是过不了的

这里讲下$O(N \log N + M)$

### Part1.思路

只要奶牛题你日的够多，这题就是个套路题。

先上一句话

> 智商不够，数据结构来凑

对于每一个点，我们要关闭它，然后断开所有与它相连的边，并且把它标记为已删除，接着按照题目判断就好了。

断边，lct？

当然可以，但是没必要。

事实上，这种没有强制在线的断边似乎都可以并查集搞。

你离线，然后倒着加边，最后倒着回答询问就好了。

主要是对于这个题目，你需要$O(1)$判断一张图是否联通。

这在并查集如果你枚举每个点算联通块个数的话会超时

不如直接维护个size，然后判断下是否为图中点数就好了。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<unordered_set>
using namespace std;

const int N = 300000 + 5;
vector <int> G[N];
unordered_set <int> s;

int n , m , q[N] , f[N] , sz[N];
bool ans[N];
int find(int u) {return u != f[u] ? f[u] = find(f[u]) : u;}
void link(int u , int v) {
	int t1 = find(u) , t2 = find(v);
	if(t1 == t2) return ;
	if(sz[t2] < sz[t1]) swap(t1 , t2);
	f[t1] = t2; sz[t2] += sz[t1];
}

int main() {
	freopen("closing.in" , "r" , stdin); freopen("closing.out" , "w" , stdout);
	scanf("%d %d" , &n , &m);
	for(int i = 1 ; i <= n ; ++i) sz[f[i] = i] = 1;
	for(int i = 1 , u , v ; i <= m ; ++i) {
		scanf("%d %d" , &u , &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	for(int i = 1 ; i <= n ; ++i) scanf("%d" , q + i);
	for(int i = n ; i >= 1 ; --i) {
		int u = q[i]; s.insert(u);
		for(int k = 0 ; k < G[u].size() ; ++k)
			if(s.count(G[u][k])) link(G[u][k] , u);
		int rt = find(*s.begin());
		ans[i] = sz[rt] == s.size();
	}
	for(int i = 1 ; i <= n ; ++i) printf("%s\n" , ans[i] ? "YES" : "NO");
}
```


---

## 作者：bztMinamoto (赞：13)

说来惭愧，这道题我懵了好几天，最后还是在老师的提示下才有所思路，所以蒟蒻还是想发上来帮一下大家

首先，这是一道并查集，不过必须倒着做。我们可以把所有边先读进来，倒着做，将拆边过程变为合并过程，最后倒着输出答案

第一步，我们先用结构体把每一条边存着，按优先度升序排列（优先度即为第几个拆除），设置变量num，为连接的两边较早拆除的优先度（越早拆除的，越晚才能合并）。之后倒着遍历数组，即为边的合并顺序

第二步，我们可以用k表示当前有多少个集合（包括没有被连边的），每连一条边，k--（即为少了一个集合），如果合并第i条边后k=i（注意，i是倒着循环的），说明农场连通，否则不连通。记录答案

第三步，倒着输出合并过程的答案，即为拆除时的连通情况

我语文不太好，不过还是希望大家能看懂上面的话，如果有什么细节不明白，可以看注解

上代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#define a(i,a,b) for(int i=a;i<=b;i++)
#define b(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
struct ab{
    int from,to,num;
    //边的两个点和优先度
};
const int N=200050;
ab a[N];
int f[N],h[N],t[N],s[N];
bool ans[N];
int p=0,q;
int n,m;
int k;
int ff(int x)
{
    if(f[x]==x) return x;
    return f[x]=ff(f[x]);
}
void unite(int x,int y)
{
    x=ff(x),y=ff(y);
    if(x==y) return;
    k--;
    //每连接一条边，集合数量减少1
    if(h[x]<h[y])
    f[x]=y;
    else if(h[x]>h[y])
    f[y]=x;
    else
    f[y]=x,h[x]++;
    return;
    //h用于按秩合并，可以忽略
}
bool same(int x,int y)
{
    if(ff(x)==ff(y)) return true;
    return false;
}
bool cmp(ab x,ab y)
{
    return x.num<y.num;
}
int main()
{
    scanf("%d%d",&n,&m);
    k=n;
    a(i,0,m-1)
    scanf("%d%d",&a[i].from,&a[i].to);
    a(i,1,n)
    {
        int x;
        scanf("%d",&x);
        t[x]=i;
        s[i]=x;
    }
    //t为每个点的优先度
    a(i,1,n)
    f[i]=i,h[i]=1;
    a(i,0,m-1)
    a[i].num=min(t[a[i].from],t[a[i].to]);
    //将每一条边的优先度设为两点较小的优先度
    sort(a,a+m,cmp);
    q=m-1;
    //因为拆分优先度从小到大，合并时需要倒叙
    b(i,n,1)
    {
        while(a[q].num>=i)
        {
            unite(a[q].from,a[q].to);
            q--;
            //倒叙枚举优先度，依次合并每一条边
        }
        if(k==i) ans[p]=1;
        else ans[p]=0;
        p++;
        //记录答案
    }
    b(i,p-1,0)
    if(ans[i])
    printf("YES\n");
    else
    printf("NO\n");
    //倒序输出
    return 0;
}
```

---

## 作者：Orion_Rigel (赞：8)

看到楼上有了灌水判联通，我就写一个并查集好了。

可以倒着加入边，然后每次暴力的去找根的个数，如果大于1就是NO

储存起来倒序输出。

------完结，撒花-----

···
```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int can[3001],n;
int fa[3001];
int ans[3001],a[3001];
int h[3001],ne[6001],to[6001],fr[6001],en=0;
inline void add(int a,int b)
{ne[en]=h[a];to[en]=b;fr[en]=a;h[a]=en++;}
inline int gf(int k)
{
    if (fa[k]==k) return k;
    else return fa[k]=gf(fa[k]);
}
int main()
{
    memset(h,-1,sizeof h);
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    for (int i=1;i<=n;++i) scanf("%d",&a[i]),fa[i]=i;
    for (int i=n;i>=1;--i)
    {
        can[a[i]]=1;
        for (int j=h[a[i]];j>=0;j=ne[j])
        {
            if (can[fr[j]]&&can[to[j]])
            {
                int l=fr[j],r=to[j];
                int fl=gf(l),fr=gf(r);
                if (fl!=fr) fa[fl]=fr;
            }
        }
        int cnt=0;
        for (int j=1;j<=n;++j)
            if (can[j]&&fa[j]==j) cnt++;
        if (cnt==1) ans[i]=1;
    }
    printf("YES\n");
    for (int i=2;i<=n;++i) if (ans[i]) printf("YES\n");
    else printf("NO\n");
}
···
```

---

## 作者：Arghariza (赞：7)

这是一道并查集裸题啊。~~不过我竟然改了半个小时。~~

1. 我们来想一下为什么是并查集。

并查集是用来干嘛的？无非是合并&查询啊。

这题要求的就是求他是不是联通的，也就是求他们是否拥有公共的祖先

所以我们用并查集实现

2. code

-  定义变量：我们定义```pre[i]```为```i```的祖先，一开始因为并没有联通，所以我们认为每个人的祖先是他自己；```f[i]```表示第```i```个时间关闭的农场；定义一个结构体数组```a[i]```，```a[i].x```和```a[i].y```代表输入时第```i```组时把两个农场连在一起

```
int n, m, pre[100001], f[100001], s[100001], t[100001];

struct node {//结构体
    int x;
    int y;
} a[100001];

```

- 并查集初始化函数init()：刚刚讲过，一开始每一个人都是自己的祖先

```
void init() {
    for (int i = 1; i <= n; i++) {//枚举从i ~ n
        pre[i] = i;//初始化，每个人都是自己的祖先
    }
}
```
- 并查集找祖先函数getf()：我们可以把祖先理解为树的根节点，他的子节点就是他的下属，图片大概是这样的：

![屏幕快照 2020-02-17 16.59.26.png](https://i.loli.net/2020/02/17/WZn4bANrgM9xpzB.png)

其中，1为2、3的祖先，所以```pre[2] = 1```、```pre[2] = 1```，接下来以此类推......

所以我们得出来了我们搜最大祖先的方法：假设我们要搜7的祖先，我们先可以看到```pre[7] = 4```，于是我们改成找4的祖先，又看到```pre[4] = 2```，所以我们去找2的祖先，2的祖先是1，1的祖先是1，所以我们就找到了

推理成代码大概这样：

```
int getf(int root) {
    if (pre[root] == root) return root;//如果找到
    else return getf(pre[root]);//否则找祖先的祖先
}
```

但是！可能有一些~~毒瘤~~数据他长这样：

![屏幕快照 2020-02-17 17.05.36.png](https://i.loli.net/2020/02/17/PH15fDEsCu2oOYv.png)

也就是一个线形的树，这样查找起来时间会成为一个问题，于是我们可以这样：每次搜祖先的时候把他变成和他祖先在同一深度的层面上，这就是路径压缩，上面的图路径压缩之后大概长这样：
![屏幕快照 2020-02-17 17.07.58.png](https://i.loli.net/2020/02/17/9HgKpwnsjIG5MVP.png)

路径压缩版本的代码：

```
int getf(int root) {
    if (pre[root] == root) return root;
    else return pre[root] = getf(pre[root]);//路径压缩
}
```

可以看到，这里路径压缩只加了一点

- merge(x, y)合并函数：我们可以查找```x```和```y```的祖先，如果是一个人，说明两个农场已经合并，否则说明没有合并，需要合并

```
void merge(int root1, int root2) {
    root1 = getf(root1);
    root2 = getf(root2);
    //找到两个人的祖先
    if (root1 != root2) {//如果祖先不是一个人
        pre[root2] = root1;//另一个人的祖先要变成这个人的子节点
    }
}
```

- merged(x, y)判断是否合并函数：我们同样查找```x```和```y```的祖先，如果是一个人返回true，不是返回false

```
bool merged(int root1, int root2) {
    if (getf(root1) != getf(root2)) {
        return false;
    } else {
        return true;
    }
}
```

- 所以我们的大体代码就出来了：

```
#include <iostream>
using namespace std;

int n, m, pre[100001], f[100001], s[100001], t[100001];

struct node {
    int x;
    int y;
} a[100001];

void init() {
    for (int i = 1; i <= n; i++) {
        pre[i] = i;
    }
}

int getf(int root) {
    if (pre[root] == root) return root;
    else return pre[root] = getf(pre[root]);
}

void merge(int root1, int root2) {
    root1 = getf(root1);
    root2 = getf(root2);
    if (root1 != root2) {
        pre[root2] = root1;
    }
}

bool merged(int root1, int root2) {
    if (getf(root1) != getf(root2)) {
        return false;
    } else {
        return true;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i].x >> a[i].y;
    init();
    for (int i = 1; i <= n; i++) {
        cin >> f[i];
        s[f[i]] = 1;
    }
    for (int i = n; i >= 1; i--) {
        s[f[i]] = 0;
        for (int j = 1; j <= m; j++) {
            if (!s[a[j].x] && !s[a[j].y]) {
                merge(a[j].x, a[j].y);
            }
        }
        t[i] = 0;
        for (int j = 1; j <= n; j++) {
            if (getf(j) == j && !s[j]) {
                t[i]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (t[i] == 1) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：LevenKoko (赞：3)

总体思路类似于楼上的楼上，用并查集倒着做，但是。。。dalao存储图的方法没看太懂，于是用vector来做，可能会简单一点。
（比较适合先看楼上的楼上的dalao的题解，解释比较详细）
```
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm> 
using namespace std;

const int maxn=200005;
int mm[maxn]; 
bool open[maxn]; 
bool ans[maxn]; 
vector<int> g[maxn];//用来存储两个村庄之间的关系
int p=1;
int s[maxn]; 
int fa[maxn];


int find(int x){//找爸爸
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
} 

void Union(int a,int b){//合并
    int af=find(a),bf=find(b);
    if(af==bf) return;
    fa[af]=bf;
    s[bf]+=s[af];
    return;
}

int u,v;
int n,m;
int main(){

    cin>>n>>m;

    for(int i=0;i<m;i++)
        cin>>u>>v,g[v].push_back(u),g[u].push_back(v);//存入节点关系
    for(int i=1;i<=n;i++)
        cin>>mm[i], s[i]=1,fa[i]=i; 
        
    for(int i=n;i>=1;i--){ 
        int x=mm[i];
        open[x]=1;
        for(int j=0;j<=g[x].size()-1;j++)
            if(open[g[x][j]]) Union(g[x][j],x); 
            
        if(s[x]==n-i+1) ans[i]=1; 
        else ans[i]=0;
    }
    for(int i=1;i<=n;i++)
        cout<<(ans[i]?"YES":"NO")<<endl; 
    return 0;
}
```

---

## 作者：Scarlet_Lightning (赞：2)

大佬们都是用一些很高级的方法啊……

本蒟蒻脑回路太短，不会像其他大佬一样用倒推的方法，就上一个比较暴力的方法吧……

## 思路：
大家应该都看出来了，如何判断整个农场联通呢？  
正解就是并查集。  
把整个图遍历一遍，有边相连的点合并到一个集合里，最后看剩下的集合数，如果只有1个集合那么就是联通的，输出YES。如果多于1个集合那么就是不连通的，输出NO。  
接下来问题来了：  
题目中将点删掉之后再判断是否联通，应该将此点所在的集合分割成2个，然后再做并查集判断是否联通。  
然而，并查集并没有我们想象的那么高级，他并不支持分割集合的操作，那么怎么解决题目中的删点问题呢？  
这时候，某些大佬可能想到的很好的方法：倒推。意思大概是把并查集倒着做一遍，从一开始没有点，一直添加节点，直到所有点都被加入图中，这样可以省去题目中最为棘手的删点问题。  
**然鹅我是个蒟蒻，一开始并没有想出来倒推这种方法，于是脑回路是直的的本蒟蒻写了个正着推的方法**  
如何操作呢？  
既然题目中的删点操作要求我们分割并查集，那么我们每删掉一个点干脆重新做一遍并查集，并在做并查集的时候无视已经删掉的点，最后照样也能得出正确答案。~~尽管时间复杂度比大佬的倒推方法大好多，然鹅一看这题数据只有3000，果断用暴力水~~

### 下面上代码，里面有详细注释（~~暴力他不香吗~~）
```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int n,m;
int father[100001];//并查集
int f,t;
int sum,nn;//sum表示当前还剩多少个集合，nn表示当前最多还有多少个集合
int close[100001];//close[i]表示i这个点是否已被删掉，1为是，0为否
int cnt=0;
struct node{
	int from;
	int to;
}edge[50001];//存边
int kingeight(int x)//其实是查找祖先，因为我们班有个人外号kingeight,所以我把find改成了kingeight（意思请自行理解）
{
	if(father[x]!=x){father[x]=kingeight(father[x]);return father[x];}
	else return x;
}
int main()
{
	scanf("%d%d",&n,&m);//读入不解释
	sum=n;
	for(int i=1;i<=n;i++)
	{
		father[i]=i;
	}//并查集初始化
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&f,&t);
		edge[++cnt].from=f;
		edge[cnt].to=t;
		edge[++cnt].from=t;
		edge[cnt].to=f;//存边不解释
		int r1=kingeight(father[f]);//并查集
		int r2=kingeight(father[t]);
		if(r1!=r2){//如果有边相连且集合不同，那么合并他们的集合
			sum--;
			father[r2]=father[r1];
		}
	}
	if(sum==1)printf("YES\n");//如果只剩1个集合，那么整个图是联通的
	else printf("NO\n");
	nn=n-1;//有一个点已经被删掉了，所以最大集合数--
	scanf("%d",&f);
	close[f]=1;
	for(int j=1;j<=n;j++){
		father[j]=j;
	}
	for(int i=2;i<=n;i++)
	{	
		sum=nn--;
		for(int j=1;j<=cnt;j++) //暴力扫边，重新做一遍并查集
		{
			if(close[edge[j].from]||close[edge[j].to])continue;//跳过已经被删掉的点
			int r1=kingeight(edge[j].from);//并查集
			int r2=kingeight(edge[j].to);
			if(r1!=r2){如果有边相连且集合不同，那么合并
				father[r2]=father[r1];
				sum--;
			}
		}
		if(sum==1)printf("YES\n");//同上
		else printf("NO\n");
		scanf("%d",&f);
		close[f]=1;
		for(int j=1;j<=n;j++){
			father[j]=j;
		}//清空并查集，准备下一次暴力
	}
	return 0;
}
```
**The end.**

---

## 作者：Sakura_Peng (赞：2)

一遇到这种连通性的问题，首先想到的是并查集来解决
这里要注意一句话：

> （这里的“时间”指在每一次关闭谷仓之前的时间）

我用的也是最简单的方法，按照关闭的结点，每一次都进行合并子树并查集的操作，只把已经关闭的相连的路不要连在一起就行了。

然后再按照树个数的性质

即**根节点只有一个的话就只有一棵树，有两个以上就说明没有全部连通还是有两个即两个以上的点没有连通**

输入YES或者NO即可


代码：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int a[10001][3],fa[10001],n,m,ans,b[10001],w[10001];
int find(int x)
{
	if (x==fa[x])
	return x;
	fa[x]=find(fa[x]);
	return fa[x];
} //并查集路径压缩
void he(int x,int y)
{
	int x1=find(x),x2=find(y);
	if (x1!=x2)
	{
		fa[x2]=x1;
	}
}//并查集合并操作
void sc() 
{
	for (int i=1;i<=n;i++)
	fa[i]=i;
	return ;
}
int pd()
{
	int k=0;
	for (int i=1;i<=n;i++)
	{
		if (b[i]==1)  //因为已经关闭的结点不算在最后判断剩下结点的联通问题上，所以要把他们给忽略
		continue;
		if (fa[i]==i)
		k++;
	}
	if (k>=2)
	return 0;
	else
	return 1;
}  //判断是否为每个节点都连通
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
	   int x,y;
	   scanf("%d%d",&a[i][0],&a[i][1]);
	   	he(a[i][0],a[i][0]);
}
int k=0;
	for (int i=1;i<=n;i++)
	{
		if (fa[i]==i)
		k++;
	}
	if (k>=2)
	ans=1; //每一次输出的是在关闭当前这个点之前的连通情况，所以要先判断一开始有没有全部连通
	for (int i=1;i<=n;i++)
	{
		if (ans==1 && i==1)
		{	
		printf("NO\n");
		continue;
	}
		scanf("%d",&w[i]);
		b[w[i-1]]=1;  //标记点已经关闭
		sc();
		for (int j=1;j<=m;j++)
		{
			if (b[a[j][0]]==0 && b[a[j][1]]==0)  //标记关闭的点与其有任何关系的路都已经失效了，不能再合并他们
			he(a[j][0],a[j][1]);
		}
		if (pd())
		printf("YES\n");
		else
		printf("NO\n"); 
	}
	return 0;
}
```


---

## 作者：fy0123 (赞：2)

我用的是灌水判联通（也可以用并查集 反向考虑 从最后一个加点和边）

灌水的话直接删就可以了 3000的规模 边我用的是邻接表存 然后一个个删点删边 每次判断一下图是否联通 （一开始还要判一次整个图的联通情况） 然后我用的是宽搜灌水 应该快一些吧

```cpp
var n,m,i,j,x,y,k:longint;
    f:array[0..3000]of boolean;
    a:array[0..3000,0..3000]of longint;
function check(v:longint):boolean;
var i,j,s,x,y,l,r,sum:longint;
    vis:array[0..3000]of boolean;
    q:array[0..3000]of longint;
begin
fillchar(vis,sizeof(vis),0);
for i:=1 to n do if not f[i] then begin s:=i; break; end;
fillchar(q,sizeof(q),0);
l:=1;r:=1;q[1]:=s;vis[s]:=true;sum:=1;
while l<=r do
      begin
      x:=q[l];
      for i:=1 to a[x][0] do
            begin
            y:=a[x][i];
            if (not vis[y])and(not f[y]) then
               begin
               vis[y]:=true;inc(sum);
               inc(r);q[r]:=y;
               end;
            end;
      if sum=v then break;
      inc(l);
      end;
if sum=v then exit(true)
   else exit(false);
end;
begin
read(n,m);
for i:=1 to m do
    begin
    read(x,y);
    inc(a[x][0]);a[x][a[x][0]]:=y;
    inc(a[y][0]);a[y][a[y][0]]:=x;
    end;
if check(n) then writeln('YES')
   else writeln('NO');
for i:=1 to n-1 do
    begin
    read(k);
    f[k]:=true;
    if check(n-i) then writeln('YES')
       else writeln('NO');
    end;
read(k);
end.
```

---

## 作者：NightStriker (赞：1)

看到别的题解都是写并查集，我表示看不懂......

$n,m\le 3000$ 完全可以用 $\mathcal{O}(n^2)$ 的 dfs。

题意很简单，每删去一个节点就判断一下整个图是否联通。

那我们每删一次，就从任意节点 dfs 统计是否所有的节点都能到达，如果访问到的节点数是现在存在的所有节点数，那就说明该图是联通的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,k,ans,flag[3001],vis[3001];
vector<int>a[3001];//vector 存图
void dfs(int u){
	vis[u] = 1;
	ans++;
	for(int v = 0;v<a[u].size();v++){
		if(vis[a[u][v]]==0&&flag[a[u][v]]==0) dfs(a[u][v]);//这里要注意判断节点是否合法：被删去/访问过 都要考虑到。
	}
}
int main(){
	cin>>n>>m;
	for(int i = 1;i<=m;i++){
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	k = 1;
	for(int i = 1;i<=n;i++){
		for(;k<=n;k++){//小小的优化
			if(flag[k]==0){
				ans = 0;
				memset(vis,0,sizeof vis);//注意 vis 和 ans 都要清空
				dfs(k);
				if(ans==n-i+1) cout<<"YES"<<endl;//是否把当前存在的所有节点都访问过了
				else cout<<"NO"<<endl;
				break;
			}
		}
		cin>>u;
		flag[u] = 1;
	}
    return 0; 
}

```

---

## 作者：风潇潇兮 (赞：1)

#### 题目大意
给你n个点和m条边，依次删去一个点，求每种状态下是否连通。
#### 题目解析
本题刚开始还以为是~~用暴力做法~~，但一看数据范围就不淡定了。不过各位也可以看一看[弱化版](https://begin.lydsy.com/JudgeOnline/problem.php?id=5972)
那么此题的正解应该是**并查集**：
但怎么用呢？这里要用一个小技巧：先把依次删去的点全部读进来，然后倒过来做。
定义一个**sum**，用来判断当前连通快的个数，若个数为1，则全部连通。
每读入一个点**i**，就先把sum++，然后搜索所有与**i**相连的点，若该点已经出现，且没有与**i**点连通，则可以做一次连通，并把sum-1。
#### 程序实现
```javascript
#include<bits/stdc++.h>
using namespace std;
bool flag[200010],ans[200010];
int n,m,tot,pre[400010],now[200010],ch[400010],f[200010],x,y,sum,kk[200010],k;
inline void sb(int x,int y){pre[++tot]=now[x];now[x]=tot;ch[tot]=y;}
int fa(int num)
{
    int nu=num,nm;
    while(num!=f[num])
        num=f[num];
    while(nu!=f[nu])
        nm=nu,nu=f[nu],f[nm]=num;//将树压得扁平，节省时间。
    return num;
}//合并
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        f[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        sb(x,y),sb(y,x);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&kk[i]);
    for(int i=n;i>=1;i--)
    {
        sum++;
        k=kk[i];
        flag[k]=true; 
        for(int j=now[k];j;j=pre[j])
            if(flag[ch[j]]&&fa(ch[j])!=fa(k))
                f[fa(ch[j])]=f[fa(k)],sum--;
        if(sum==1)
            ans[i]=1;
    }
    for(int i=1; i<=n; i++)
        if(ans[i]==1)printf("YES\n");
        else printf("NO\n");
    return 0;
}
```

---

## 作者：Sino_E (赞：1)

去掉某个点连的边再判断连通性，太麻烦。考虑将操作序列反过来，变成加入某个点和点所连的边，再来判断连通性。

因为无论正着或是反过来操作，同一个时刻按照这种操作方法，得到的图是相同的，因此连通性也是相同的。离线处理，到时候将答案序列反过来输出即可。

如何方便的判断目前开启的点是否全连通？基本操作使用并查集。

假设目前已经有一些点开启了。然后加入一个开启的点。我们会枚举与该点相连的边。若边的另一端的点也已经开启，我们应该将两点所属的集合合并在一起，否则忽略该边。显然如果目前为止图是全连通的，这个合并的集合的大小应该等于目前已经开启的点的个数，否则就不是全连通。

于是每次加入新开启的点，我们都将其它相邻的集合合并到新加入的点上，维护一下每个集合的大小即可。

细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

/* 链式前向星存图 */
const int N=3010,M=6010;
int h[N],to[M],nexp[M],p=1;
inline void ins(int a,int b){
    nexp[p]=h[a],h[a]=p,to[p]=b,p++;
}

/* 并查集 */
int fa[N];
inline int Find(int x){
    if(!fa[x]) return x;
    return fa[x]=Find(fa[x]);
} 
int siz[N]; // 并查集大小
inline bool Union(int a,int b){
    int af=Find(a),bf=Find(b);
    if(af==bf) return false;
    fa[af]=bf;
    siz[bf]+=siz[af];
    return true;
}

int con[N]; // 操作序列
bool opend[N]; // 标记点是否已经开启
bool ans[N]; // 答案序列

int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    int u,v;
    for(int i=0;i<m;i++)
        cin>>u>>v,ins(u,v),ins(v,u);
    for(int i=1;i<=n;i++)
        cin>>con[i], siz[i]=1; // 输入操作序列，初始化并查集大小
    for(int i=n;i>=1;i--){ // 倒序处理操作序列
        int &x=con[i];
        opend[x]=1;
        for(int u=h[x];u;u=nexp[u])
            if(opend[to[u]]) Union(to[u],x); // 枚举相邻的边，如果另一个点开启则合并
        if(siz[x]==n-i+1) ans[i]=1; // 如果并查集的大小是现在已经开启了的点的个数则全连通
        else ans[i]=0;
    }
    for(int i=1;i<=n;i++)
        cout<<(ans[i]?"YES":"NO")<<endl; // 正序输出答案序列
    return 0;
}
```

---

## 作者：revenger (赞：1)

楼上并查集暴力找连通块个数 其实可以更快地计算

加入一个计数器 开始的时候计数为0 每次加入一个节点后 计数器加一 然后开始枚举边 合并

每次成功合并后计数器减一（连通块减少）

如果当前的计数器为1的话就是联通的 不用每次暴力搜

其他的就是并查集的基本操作 注意最后倒序输出（然而只有我才会sb地正着输出……）

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,next[6010],head[6010],point[6010],sum,open[6010],a[6010],step[6010],k,p,c,d;
int ans[6010];
int up(int x)
{
    if(a[x]!=x)
    a[x]=up(a[x]);
    return a[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&c,&d);
        sum++;
        next[sum]=head[c];
        head[c]=sum;
        point[sum]=d;
        sum++;
        next[sum]=head[d];
        head[d]=sum;
        point[sum]=c;
    }
    k=0;
    for(int i=n;i>=1;i--)
    {
        a[i]=i;
        scanf("%d",&step[i]);
    }
    for(int i=1;i<=n;i++)
    {
        k++;
        open[step[i]]=1;
        p=head[step[i]];
        while(p)
        {
            if(open[point[p]])
            {
                int ax=up(point[p]);
                int ay=up(step[i]);
                if(ax!=ay)
                {
                    a[ax]=ay;
                    k--;
                }
            }
            p=next[p];
        }
        ans[i]=k;
    }
    for(int i=n;i>=1;i--)
    {
        if(ans[i]==1)
        printf("YES\n");
        else
        printf("NO\n");
    }
}
```

---

## 作者：Victorique (赞：1)

这个题楼上的思路确实崩溃，spfa对于这个题完全没有任何用处，只是提供一种思路罢了，这个题没给你边权

###没给你边权###

所以压根就不需要跑最短路，如果点数足够多，图足够稠密，那么这么多遍spfa等着T就可以了，实际上这个题直接bfs暴力遍历整张图就可以了，当然是对于这个题的数据而言。我们测试的时候的数据，貌似200000，导致bfs也会T飞6个点，所以这个题最好的解法貌似是并查集。然而这个题一会关闭这个点一会关闭那个点看着好难受。。那么就先读入所有点，然后反向循环，一个一个往里加，记录下来，最后再顺序输出就可以了，楼下貌似也已经有过并查集了，只是可能不是特别严谨（毕竟这个题完全用不着这么做，直接暴力打起来更舒服）。我就挂上200000版本的吧。。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,p[200010],a[400010],nxt[400010],father[400010],now,q[200010],tot;
bool ans[200010],ext[200010];
void add(int x,int y){
    tot++;a[tot]=y;nxt[tot]=p[x];p[x]=tot;
}
int find(int x){
    if (father[x]==x) return x;
    father[x]=find(father[x]);
    return father[x];
}
int main()
{
//    freopen("closing.in","r",stdin);
//    freopen("closing.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        add(x,y);add(y,x);
    }
    for (int i=1;i<=n;i++){
        scanf("%d",&q[i]);father[i]=i;
    }
    now=0;
    for (int i=n;i>=1;i--){
        ++now;ext[q[i]]=true;
        for (int j=p[q[i]];j!=0;j=nxt[j])
          if (ext[a[j]]==true){
                int r1,r2;
                r1=find(q[i]);r2=find(a[j]);
                if (r1!=r2){
                     --now;father[r1]=r2;
              }
          }
        if (now==1) ans[i]=true;
    }
    for (int i=1;i<=n;i++)
      if (ans[i]==true) printf("YES\n");
      else printf("NO\n");
    return 0;
}
```

---

## 作者：皮卡丘最萌 (赞：0)

这题一开始想到直接暴力，先建一个并查集，再进行操作，但是万万没有想到题目居然让我们拆边，而并查集又不支持拆边操作。。

所以我们需要换一个思路。

考虑这一个图中一开始没有小镇，我们再将要删除的小镇一个个倒着加进来，再判断图是否联通。

比如题目中关闭顺序为：3 4 1 2

那么我们加小镇的顺序就是：2 1 4 3 

这样就很好的解决了并查集不能支持拆边操作的缺点。

接下来就只要考虑在加点时如何判断与其他点是否联通，这点可以用一个二维数组存关系（这题数据小，只有3000），或者用邻接表存。

最后就是判断整个图是否联通，这点我们需要找到第一个已经加进去的小镇，再与其他加进来的小镇做一次判断，就可以了。

在加上优化了的并查集，总的时间复杂度为O(n^2×k),这里的k是一个小小的并查集操作的时间复杂度。(当然用邻接表可能有O(n))

放代码：
```pascal
var n,m,i,x,y,x1,y1,j,t:longint; flag:boolean;
a,c,f:array[0..100001] of longint;
e,d:array[0..100001] of boolean;
b:array[0..3001,0..3001] of longint;
function find(x:longint):longint;
begin
if f[x]=x then exit(x);
f[x]:=find(f[x]);
exit(f[x]);
end;                      //优化了的并查集，不解释

begin
readln(n,m);
for i:=1 to n do f[i]:=i;      //默认祖先是他自己
for i:=1 to m do
  begin
  readln(x,y);
  inc(a[x]); b[x,a[x]]:=y;
  inc(a[y]); b[y,a[y]]:=x;       //二维数组保存关系
  end;
for i:=1 to n do readln(c[i]);
for i:=n downto 1 do                  //倒着加入
  begin
  d[c[i]]:=true;                 //加入这一个小镇
  flag:=true;                    //默认联通
  for j:=1 to a[c[i]] do         
    if d[b[c[i],j]] then         
                 //如果有关系并且已经加入，那么就连边
      begin
      x1:=find(b[c[i],j]); y1:=find(c[i]);   //找祖先
      if x1<>y1 then f[x1]:=y1;         //连边
      end; 
  t:=1; while not d[t] do inc(t);     //找第一个加入的小镇
  for j:=t+1 to n do
    if (find(j)<>find(t))and(d[j]) then 
      flag:=false;         //如果有一个不连通，就变为false
  e[i]:=flag; 
  end;
for i:=1 to n do            //上面倒着，下边就顺着
  if e[i] then writeln('YES') else writeln('NO');
end.
```




---

