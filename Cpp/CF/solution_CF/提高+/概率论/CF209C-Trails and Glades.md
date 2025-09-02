# Trails and Glades

## 题目描述

Vasya went for a walk in the park. The park has $ n $ glades, numbered from 1 to $ n $ . There are $ m $ trails between the glades. The trails are numbered from 1 to $ m $ , where the $ i $ -th trail connects glades $ x_{i} $ and $ y_{i} $ . The numbers of the connected glades may be the same $ (x_{i}=y_{i}) $ , which means that a trail connects a glade to itself. Also, two glades may have several non-intersecting trails between them.

Vasya is on glade 1, he wants to walk on all trails of the park exactly once, so that he can eventually return to glade 1. Unfortunately, Vasya does not know whether this walk is possible or not. Help Vasya, determine whether the walk is possible or not. If such walk is impossible, find the minimum number of trails the authorities need to add to the park in order to make the described walk possible.

Vasya can shift from one trail to another one only on glades. He can move on the trails in both directions. If Vasya started going on the trail that connects glades $ a $ and $ b $ , from glade $ a $ , then he must finish this trail on glade $ b $ .

## 说明/提示

In the first test case the described walk is possible without building extra trails. For example, let's first go on the first trail, then on the second one, and finally on the third one.

In the second test case the described walk is impossible without adding extra trails. To make the walk possible, it is enough to add one trail, for example, between glades number one and two.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 5
1 1
1 2
1 2
2 2
1 2
```

### 输出

```
1
```

# 题解

## 作者：wucstdio (赞：11)

本来只是想发布一篇题解，结果写到一半把我之前的AC代码叉掉了……23333……

题目大意：无向图最少加多少条边，使得图中存在一条从$1$号点出发的欧拉回路。

首先，让我们回顾一下连通图中存在欧拉回路的充要条件：**所有节点的度数均为偶数**。

所以，一个显然的想法就是：我们找出来所有度数为奇数的点，然后将这些点两两相连，得到的图的度数就全部是偶数了！

但是这样并不对。原因很简单：存在欧拉回路需要先保证原图是一个**连通图**！

所以，我们在连边的过程中还需要保证新图连通。

考虑每一个连通块。

如果这个连通块所有节点的度数均为偶数，那么我们需要从这个连通块向别的连通块额外连两条边（为什么是两条边？因为一条边的话就出现奇数点了）。这样会导致总答案在原来的基础上+1（因为一条边被算了两次）

如果这个连通块存在奇数点，那么我们只需要保留两个奇数点，从这两个奇数点出发向外连接两条边。这样并不会对答案产生影响。

最后还有一个坑：这道题要求的是从$1$号点出发的欧拉回路。所以如果一个连通块内部（注意不能是$1$号点所在的连通块！）没有边，我们可以不管这个连通块，因为没必要到达这个点。

总结一下算法流程：

1、统计所有节点的度数，并且求出内部有边的或者包含$1$的连通块数量。

2、如果图中仅有一个这样的连通块，那么直接输出奇数点个数$/2$。

3、否则，依次查看每一个有边的或包含$1$的连通块。先让$ans+=num/2$，$num$表示奇数点个数。再查看这个连通块内部是否存在奇数点，如果不存在，则$ans++$。

4、输出。

奉上改后的代码（如还有BUG，欢迎Hack）：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,pa[1000005],num[1000005],size[1000005];
bool d[1000005],flag[1000005];
int find(int x)
{
	return x==pa[x]?x:pa[x]=find(pa[x]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	  pa[i]=i,size[i]=1;
	flag[1]=1;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		int x=find(u),y=find(v);
		d[u]^=1;
		d[v]^=1;
		if(x!=y)
		{
			if(size[x]>size[y])swap(x,y);
			pa[x]=y;
		}
		flag[y]=1;
	}
	int rest=0;
	for(int i=1;i<=n;i++)
	  if(i==find(i)&&flag[find(i)])
	    rest++;
	if(!flag[find(1)])rest++;
	for(int i=1;i<=n;i++)
	  if(d[i])num[find(i)]++;
	if(rest==1)
	{
		printf("%d\n",num[find(1)]/2);
		return 0;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(find(i)==i&&flag[i])
		{
			ans+=num[i]>>1;
			if(num[i]==0)ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：GalwayGirl (赞：4)

刚开始看着道题，以为是道水紫题，然后被机房大佬一眼识破：图不联通。但其实做好分类讨论，问题也能迎刃而解。

前置芝士：[欧拉路径](https://www.luogu.com.cn/blog/20080316xzh/ou-la-lu-jing)

因为图不联通，所以在保证每个节点度数为偶数的情况下，还要考虑将各个连通块串起来操作最小，让我们分以下情况。

## Solution
我们首先记 $odd$ 为奇点数，$even$ 为偶数联通块数。 

1.  仅有奇数连通块。

这个是最好讨论的，因为奇数节点是成对出现的，所以只需两两配对，答案为 $odd/2$。

2. 仅有偶数联通块。

这个比较难想，多画图还是可以搞出来的，看下面的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/fnlzt3cs.png)

有三个连通块，且都为偶数连通块，由于每个偶点要多连两条边，所以就会想到将每个连通块的欧点抠出来并且连成环，这就是最优方案，答案为 $even$。

3. 两种连通块都有。

继续画图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zgzfgg4f.png)

会发现这一情况的处理方式与操作 2 差不多，都是将偶数连通块连成环，只不过因为有奇点，所以会优先选择其中两个奇点共同串成环，所以贡献为 $even+1$，但别忘记剩下的 $odd-2$ 个奇点，他们还可以进行操作 1 ，
贡献为 $even+1+(odd-2)/2=even+odd/2$。这时候我们发现操作 1 时 $even$ 为 0，操作 2 时 $odd$ 为 0，贡献都为 $even+odd/2$，所以也不需要分类讨论了，成功把这个题转化成了结论题。看别的题解没有这么写的，希望大家能多多点赞。

## Detail
当整个图为一个偶数连通块时，答案为 $0$，而按照上面写会输出 $1$，需特判一下。

最后贴上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+100;
int n,m,f[N],in[N],odd,even;
vector<int>G[N];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
        in[u]++;in[v]++;
    }
    for(int i=1;i<=n;i++){
        if(f[i]||(i!=1&&G[i].empty()))continue;
        queue<int>q;
        bool flag=false;
        f[i]=i;
        q.push(i);
        while(!q.empty()){
            int now=q.front();
            q.pop();            
            if(in[now]%2){
                odd++;flag=true;
            }
            for(int j=0;j<G[now].size();j++){
                int v=G[now][j];
                if(f[v])continue;
                f[v]=i;
                q.push(v);
            }
        }
        if(!flag)even++;
    }
    int ans=even+odd/2;
    if(even==1&&!odd)ans--;
    printf("%d",ans);
    return 0;
}
```


---

## 作者：Elaina_ (赞：3)

欧拉回路。

思路：

首先我们要学习一下欧拉回路的判断条件——“一个无向图存在欧拉回路，当且仅当该图所有顶点度数都为偶数,且该图是连通图。”

注意上面那句话的两个要点：

 1. 所有顶点度数都为偶数。
 
 2. 图是连通图。
 
然后我们对不是连通图的情况分类讨论：（下面的联通块代表无欧拉回路的联通块，欧拉联通块代表有欧拉回路的联通块）

 1. 只有一个联通块：这一种情况只需要记录度数为奇数的点然后除以二就是连边的数量（每两个奇数点连一条边）。
 
 2. 有多个欧拉联通块联通块（联通块可以转化为欧拉联通块，所以这里只考虑欧拉联通块）：块内的连边方式和 1 相同，考虑怎么把块组合到一起：
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/xcv025ld.png)
 
 
 不难发现，上面的连边方式应该是最小的连边数（其中序号代表第几个欧拉联通块），因为 Vasya 还要回到第一个点。因此连的边数为 $n-1$（$n$ 为欧拉联通块的个数）。
 
接下来我们考虑怎么把一个初始的联通块，变成一个目标的联通块：（下面开始只考虑 2 的情况）

我们不难发现，每个联通块必然连了两个出边，所以我们可以先分类讨论一下两种不同的联通块：

 1. 联通块：我们把度为奇数的点连边连到只剩 $2$ 个用来和两个欧拉联通块连接，所以此时块内所需要的边数就是 $(n-2)\div 2$（$n$ 是度为奇数的点的个数）。
 
 2. 欧拉联通块：因为我们不能空出两个点来和其他欧拉联通块连接，所以我们一定要连一条边。
 
总结一下上面的内容，我们就可以容易的得到一个式子：$(n_3-n_1\times 2){\div} 2+n_1+n_2$（$n_1$ 为联通块的个数，$n_2$ 为欧拉联通块的个数，$n_3$ 为度为奇数的个数）。

PS：上面的式子没办法解决只有一个欧拉联通块的情况，需要特判一下。

- 不理解的可以这样想：$(n_3-n_1\times 2){\div} 2$ 是联通块内连的边数 $n_1+n_2$ 是联通块之间连的边数。

于是我们容易得到代码：（提醒一下，因为 Vasya 是从 1 号点开始走的，其必须经过 1 号点，所以如果 1 号和其他点没有连边，可以把这个点看成一个有自环的点，也就是一个欧拉联通块）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int F=1000100;

int n,m,cnt,flag,tot,n1,n2,n3;
int d[F],v[F],head[F],ver[3*F],nxt[3*F],fq[F];

void add(int x,int y){
    ver[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}

void dfs(int x){
    if(d[x]&1){
        n3++;
        flag=1;
    }
    v[x]=1; cnt++;
    for(int i=head[x];i;i=nxt[i]){
        int y=ver[i];
        if(!v[y]) dfs(y);
    }
}

void fst(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}

signed main(){
    freopen("try.in","r",stdin);
    fst();
    cin>>n>>m;
    while(m--){
        int x,y;
        cin>>x>>y;
        if(x!=y){
            d[x]++; d[y]++;
            add(x,y);
            add(y,x);
        }
        else fq[x]=1;
    }
    for(int i=1;i<=n;i++){
        if(!v[i]){
            flag=cnt=0;
            dfs(i);
            if(cnt>1||fq[i]||i==1){
                if(flag) n1++;
                else n2++;
            }
        }
    }
    if(n1+n2==1) cout<<n3/2<<endl;
    else cout<<(n3-n1*2)/2+n1+n2<<endl;
    return 0;
}
```


---

## 作者：i207M (赞：3)

## 题意

最少添加多少条边，使无向图有欧拉回路

## 方法

这个题看着简单，其实很坑；

~~4分钟代码，20分钟调~~

求出每个点的度数

奇度数点需要连一条新边

仅有偶度数点的连通块需要连两条新边

答案为上面统计的新边数 / 2 （一条边可以满足两个需求）

## 易错！！！

1.这个题强制从1出发；

2.记得统计联通块个数；

3.重边也必须走！！！

## 代码

```
//#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define gc getchar
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
// ST 21:38
#define N 1000010
#define M N<<1
int v[M], u[M], nx[M];
int cnt, head[N];
int n, m;
il void add(int uu, int vv) {
    u[++cnt] = uu, v[cnt] = vv, nx[cnt] = head[uu];
    head[uu] = cnt;
}
int du[N];
int ans;
bool vis[N];
int hvj;
void dfs(int x) {
    vis[x] = 1;
    hvj|=(du[x]&1);
    for (ri i = head[x]; i; i = nx[i]) {
        if (vis[v[i]]) continue;
        dfs(v[i]);
    }
}
bool exi[N];
signed main() {
    in(n), in(m);
    for (ri i = 1, a, b; i <= m; ++i) {
        in(a), in(b);
        exi[a]=1,exi[b]=1;
        if (a == b) continue;
        add(a, b);
        add(b, a);
        du[a]++, du[b]++;
    }
    exi[1]=1;
    bool has=0;
    int cnt=0;
    for (ri i = 1; i <= n; ++i) {
        if (du[i] & 1) {
            ans++;
            has=1;
            //printf("A %d\n", i);
        }
        if(!vis[i]&&exi[i]){
        	cnt++;
        	hvj=0;
        	dfs(i);
        	if(!hvj) ans+=2;
		}
    }
    if(cnt==1&&has==0) ans-=2;
    printf("%d\n", ans / 2);
    return 0;
}
//EN 21:
```


---

## 作者：ycy1124 (赞：2)

### 题意
题意很清楚，这里不讲。
### 思路
首先发现，题目其实就是让我们加入一些边之后能使这个图中除了度数为 $0$ 的点，其它点与 $1$ 联通并且全部点的度数为偶数。对于图中很多的连通块，我们将他们分为两类，一种是包含度数为奇数的点的，另一种是所有点均为偶数度数的。

对于这两种连通块，我们可以对他们进行分别考虑。对于所有第二种连通块，我们可以在每个连通块当中每个取出一个点连成一条链。此时我们发现，这些联通块就被连成了一个包含两个奇数度数的点的连通块。此时在将新得到的连通块的一个奇数度数的点连接到其它连通块的一个奇数度数的点上。我们发现此时奇数度数的点的个数不变而所有第二种连通块都被连完了并且连的边数等于第二种连通块的个数，这种方案一定是最优的。

证明：由于这些连通块需要联通，所以你将这些第二种连通块与 $1$ 联通的最少边数为它的个数，而这种方案差不多等于将这些第二种连通块直接去掉，使用的边数也等于第二种连通块的个数。所以这种方案是最优的。

然后考虑第一种连通块。发现此时图中所有连通块中奇数度数的点的个数一定是偶数且**大于等于二**。我们考虑每次取两个奇数度数的点来相连，一定有一种方案能使得所有连通块全部联通并且加的边数等于奇数度数的点的个数除以二。这种方案显然最优。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,js,d[100005],color[100005],Color,sum;
bool bj[100005];
vector<int>a[100005];
inline void dfs(int p){
    bj[p]=1;
    if(d[p]%2){
        color[Color]++;
        js++;
    }
    for(auto it:a[p]){
        if(!bj[it]){
            dfs(it);
        }
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        d[u]++;
        d[v]++;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!bj[i]&&(i==1||d[i]!=0)){//除了1以外度数为0的点无需考虑
            ++Color;
            dfs(i);
        }
    }
    if(Color==1){
        cout<<js/2;
        return 0;
    }
    for(int i=1;i<=Color;i++){
        if(!color[i]){
            sum++;
        }
    }
    ans=js/2+sum;
    cout<<ans;
    return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/z214aiqc.png)

---

## 作者：ThisIsLu (赞：2)

我们知道，一个无向联通图是欧拉图当且仅当不存在度数为奇数的点。

所以，我们只要找到所有度数为奇数的点，两两配对即可。

至于会不会有奇数个度数为奇数的点，因为所有点度数之和是偶数，而如果有奇数个度数为奇数的点，则度数之和为奇数，矛盾。

让我们把这个代码交上去：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int n,m;
int dep[N+5];
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        dep[u]++;
        dep[v]++;
    }
    int res=0;
    for(int i=1;i<=n;i++){
        res+=(dep[i]&1);
    }
    cout<<res/2;
    return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/h1ivexfs.png)

什么情况！让我们看下 #7 是什么数据。

```
10 10
3 10
7 3
7 10
2 5
3 4
7 6
5 5
7 6
7 2
2 5
```

让我们看下这个图长什么样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/9gr1h3zw.png)

啊，原来是因为不连通，因此我们还得想办法把图变成联通的。

把图分为若干个连通块，可以把图串成一条链，对于每个连通块，分为几种情况：

- 1.块内没有边：忽略即可，如果包含点 $1$ 则仍需考虑

- 2.块内没有度数为奇数的点：要向外部连 $2$ 条边，由于会重复计数，实际上贡献为 $1$。

- 3.块内有度数为奇数的点：用两个度数为奇数的点连向外部，剩下的两两连接，由于每个度数为奇数的点都连一条边，贡献为奇点数的一半。

注意：如果原图为欧拉图，直接输出 $0$。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int n,m;
pair<int,int> e[N+5];
int dep[N+5];
int fa[N+5],sz[N+5],num[N+5];
int getfa(int x){
    return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
bool join(int x,int y){
    x=getfa(x),y=getfa(y);
    if(sz[x]>sz[y]){
        swap(x,y);
    }
    num[y]++;
    if(x==y){
        return false;
    }
    sz[y]+=sz[x];
    dep[y]+=dep[x];
    fa[x]=y;
    return true;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
        dep[i]=0;
        num[i]=0;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>e[i].first>>e[i].second;
        dep[e[i].first]^=1;
        dep[e[i].second]^=1;
    }
    for(int i=1;i<=m;i++){
        join(e[i].first,e[i].second);
    }
    if(dep[getfa(1)]==0&&num[getfa(1)]==m){
        cout<<"0";
        return 0;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            if(num[i]==0&&i!=getfa(1)){
                continue;
            }
            if(dep[i]==0){
                ans++;
            }
            else{
                ans+=(dep[i]>>1);
            }
        }
    }
    cout<<ans;
    return 0;
}
```
update:

把“3.块内没有度数为奇数的点”更改为“3.块内有度数为奇数的点”。

---

## 作者：Deamer (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF209C)

## 题意

给出一个无向图，问至少加多少条边能使图中存在有一条从 1 开始的欧拉回路。

##### 我们考虑，因为是一个欧拉回路，所以每个点都是偶点


那么我们是不是把奇点两两相连就可以了？

但这样并不对，因为我们判断一个图是否存在欧拉路径或欧拉回路时，首先这个图必须是一个连通图。

对于每一个连通块，我们分两种情况考虑：

第一种：这个连通块每个节点都是偶点，那么只要额外向其他连通块连两条边，
因为如果只连一条就会出现奇点了。

第二种：这个连通块存在奇点，每个奇数点需要向外连一条边，记得除以二
因为两个连通块之间只需要连一条边。

你以为这就完了吗，这还有个坑：（我就被坑了……

这道题强制从结点 1 出发。

总结一下吧

1. 建图。

2. 扫图统计答案，中间分两种情况考虑。


再来谈几个题目的坑（我就中了，别学我

首先，题目说的是边的欧拉回路，如果 1 所在的连通块之外还存在一个孤立点，那我们是不用额外再连一条边的，因为那个孤立点没有连边，错第 7 个点的同学注意了。

还有一点，如果那个孤立点存在自环我们要格外连边，因为它有边啊，错第 12 个点 的同学注意了。

 _~~**reader：Talk is cheap,show me the code!!!**~~_ 
 
 详细注释放代码里了……
 
 
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m;
int s,cnt;
int flag;
int p[N];		
int degree[N];
int vis[N];
vector<int>G[N];
int ans;

void DFS(int x){
	vis[x]=1;
	if(degree[x]&1) flag=1;					//这个连通块里有奇点
	for(int i=0;i<G[x].size();i++){
		if(!vis[G[x][i]]) DFS(G[x][i]);	
	}
}

int main(){
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		//注意无向图，要双向存储
		p[u]=1; p[v]=1;	
		if(u==v) continue;
		G[u].push_back(v);
		G[v].push_back(u);
		degree[u]++; degree[v]++;
	}
	p[1]=1;							//1必须访问，所以设为1
	for(int i=1;i<=n;i++){
		if(degree[i]&1){			//如果是奇点，ans++，s记录图里有没有奇点
			ans++; s=1;				
		}
		else if(!vis[i] && p[i]){	//如果是偶点，未曾访问过，还有边与它相连，就是遇到了新的连通块
			cnt++;
			flag=0;					//判断这个连通块是不是都是偶点
			DFS(i);
			if(!flag) ans+=2;		//如果都是偶点，ans+=2，因为后面要除以2，所以加2
		}
	}
	if(!s && cnt==1) ans=0;			//如果这个图里没有奇点（都是偶点），而且只有一个连通块，说明这个图本身就是一个欧拉回路
	printf("%d",ans/2);
	return 0;
}
```

 
[完结撒花！！！](https://www.luogu.com.cn/record/73206264)

 

---

## 作者：wyl_AC (赞：1)

这道题表面很简单，背地里人心险恶。

首先欧拉回路看见性质都会搞了。

最开始以为是只有一个联通块：

奇度点向另一个奇度点连线，答案为奇度点数/2

然后是惨痛爆炸。
发现有多个连通图：

奇度点向外连边，和原来一样

但是没有奇度点的联通块只要有一个块连出去两个就行了，其他的连一个就好。，答案为奇度点数/2+没有奇度点的联通块数。

可还是不够：

你会发现，有些图没有1点，所以你得特判，有些图没有边，特判，有些图点不全，特判，只做出现的以及1。
code
```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
#define LL long long
#define M 1000005
#define N 2005
#define Mod 1000000007
void read(LL &x) {
    x = 0;
    LL f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -f;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    x *= f;
    return;
}
vector<LL>G[M];
LL n,m,d[M];
bool f=0,vis[M],p[M];
void dfs(LL u){
	vis[u]=1;
	if(d[u]&1)
		f=1;
	for(int i=0;i<G[u].size();i++){
		LL v=G[u][i];
		if(!vis[v]){
			dfs(v);
		}
	}
	return ;
}
int main(){
	read(n),read(m);
	if(!m){
		puts("0");
		return 0;
	}
	for(int i=1;i<=m;i++){
		LL u,v;
		read(u),read(v);
		G[u].push_back(v);
		G[v].push_back(u);
		p[u]=1,p[v]=1;
		d[u]++;
		d[v]++;
	}
	p[1]=1;
	LL t=0;
	LL s=0,ans=0;
	for(int i=1;i<=n;i++)
	if(p[i]){
		if(!vis[i]){
			f=0;
			dfs(i);
			t++;
			if(!f)
				s++;
		}
		if(d[i]&1)
			ans++;
	}
	if(t>=2)
		printf("%I64d\n",ans/2+s);
	else
		printf("%I64d\n",ans/2);
}

```


---

## 作者：Cold_Eyes_bystander (赞：0)

模拟赛没判连通，挂了。

我们的题目是问一个人要加几条边才能不重不漏地走完每一条边，自然联想道一个点如果有一条边能到达它，就要有另一条边让那个人出去，也就是说一个点的度要是偶数。

而对于两个奇数点，我们给它们连一条边就可以解决。同时我们还可以连接两个不同连通块的的奇数点，既能让其连通，又可以消掉奇数点。

所以当连通块内有奇数点时，便让他去连其他的连通块，剩下的就进行内耗。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+1;
int a[N];
int f[N];
int find(int x)
{
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}
bool f1[N];
int qwq[N];
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		a[x]++;
		a[y]++;
		if(find(x)!=find(y))
		f[find(x)]=find(y);
	}
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]%2==1) 
		{
			qwq[find(i)]++;
		}
	}
	int cnt=0;
	bool f111=0;
	for(int i=1;i<=n;i++)
	{
		if(qwq[find(i)]&&f[i]==i)
		{
			sum+=qwq[find(i)]/2;
			cnt++;
			f111=1;
		}
		else if(f[i]==i&&(a[i]!=0||i==1))
		{
//			cout<<i<<endl;
			sum++;
			cnt++;
		}
	}
    if(cnt==1) 
    {
        if(f111==1) cout<<sum;
        else cout<<0;
    }
    else cout<<sum;
	return 0;
}
```

---

## 作者：Milmon (赞：0)

[in Blog](//milk-lemon.blog.luogu.org/notes-EulerPath) & [Problem](//www.luogu.com.cn/problem/CF209C)

## 题目大意

- 给定 $n$ 个点，$m$ 条边的无向图，添加若干条无向边，使得图存在从 $1$ 号点出发又回到 $1$ 号点，且覆盖图中每一条边仅一次的路径，求添加边的数量的最小值。

- $1\leq n,\ m\leq 10^6$

## 解题思路

图中存在若干奇点，容易想到奇点之间两两配对连边。

题目要求存在整个图的欧拉回路，而图可能分为若干个连通块。

设一个连通块中有 $t$ 个奇点。

若 $t>0$，则只需与其它连通块的奇点连线，也就是 $t$ 个奇点参与两两配对连边。

若 $t=0$，为了使图连通，则必须从该连通块连出去一条边，此时产生一个奇点，为了存在欧拉回路，必定又要连一条边。此时相当于增加两个点进行配对。

故答案为

$$\frac{\sum\max(2,\ t)}2=\sum\max(1,\ \frac t2).$$

注意到当只有 $1$ 个连通块且没有奇点时，不需要连出去边，所以上述公式会得出错误的答案，只需在输出时特判即可。

**说明** 由于题目要求从 $1$ 开始存在欧拉回路，故我们可以在 $1$ 号点没有边的情况下，把 $1$ 号点也视为一个独立的连通块以避免 $1$ 号点没有连边的情况的错误。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int n,m,deg[1000001];
int oddcnt[1000001],f[1000001];
bool p[1000001];

int get(int id){
	return f[id]==id?id:f[id]=get(f[id]);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u,v; scanf("%d%d",&u,&v);
		deg[u]++,deg[v]++;
		f[get(u)]=get(v); // 合并连通块
	}
	int total=0,block=0;
    // 统计奇点
	for(int i=1;i<=n;i++)
		if(deg[i]&1)oddcnt[get(i)]++,total++;
	int answer=0;
	for(int i=1;i<=n;i++){
		int tmp=get(i);
		if(!p[tmp]&&(i==1||deg[i])){
            // 遇到一个新的连通块，计算对答案的贡献
			p[tmp]=true,block++;
			if(oddcnt[tmp]==0)answer++;
			else answer+=oddcnt[tmp]>>1;
		}
	}
	if(block==1&&total==0)answer=0; // 特判
	printf("%d\n",answer);
	return 0;
} 
```

---

## 作者：UperFicial (赞：0)

> [**CF209C Trails and Glades**](https://www.luogu.com.cn/problem/CF209C)

> 解题报告

> [**不一定更好的阅读体验**](https://www.cnblogs.com/UperFicial/p/16730678.html)。

图论基础题。

考虑一张无向联通图存在欧拉回路的条件是什么：

> 每一个点的度数均为偶数。

但这个条件的前提是连通图，那么我们可以考虑每一个连通块。

若这个连通块所有点度数均为偶数，那么我们可以从这个连通块往外连两条边，与其它连通块合并，贡献为 $1$。

若有 $k$ 个点的度数是奇数，那么我们只保留两个这样奇数点来往外连边即可，其余点相互连，贡献是 $\frac{k}{2}+1$。

注意贡献为 $1$ 的意思是，原本是要连两条边的，但由于两个连通块的相互连的话，每一条边会被算两次，所以连两条边只算一条边的贡献。

注意坑点：

若一个连通块只有一个点这个连通块是不用考虑的，但如果有自环是需要考虑的。

代码：

```cpp
const int MAXN(1e6+10);

int n,m;
struct E{int to,nxt;};
E edge[MAXN<<1];

int head[MAXN],tot;

inline void add_edge(int u,int v)
{
	edge[++tot].nxt=head[u];
	head[u]=tot;
	edge[tot].to=v;
	return;
}

int cnt,deg[MAXN];
bool vis[MAXN];
vector<int>G[MAXN];

inline void dfs(int u)
{
	vis[u]=true;
	G[cnt].push_back(u);
	gra(i,u)
	{
		int v=edge[i].to;
		if(!vis[v]) dfs(v);
	}
	return;
}

int ans;

inline int Count(int i)
{
	int num=0;
	rep(j,0,(int)G[i].size()-1) if(deg[G[i][j]]&1) ++num;
	return num;
}

int main()
{
    n=read(),m=read();
    while(m--)
    {
    	int u=read(),v=read();
    	add_edge(u,v),add_edge(v,u);
    	++deg[u],++deg[v];
    }
    rep(i,1,n) if(!vis[i])
    {
    	++cnt;
    	dfs(i);
    	if(G[cnt].size()==1&&G[cnt][0]!=1&&deg[i]==0) G[cnt--].pop_back();
    }
    if(cnt==1)
    {
    	printf("%d\n",Count(1)>>1);
    	return 0;
    }
    rep(i,1,cnt)
    {
    	int num=Count(i);
    	if(!num) ++ans;
    	else ans=ans+(num>>1);
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Fan_Tuan (赞：0)

# 题意
$n$个点$m$条无向边，问加几条无向边可以使图存在从$1$号点开始到$1$号点结束有欧拉回路；
# 思路 
$1.$记录每个点的度数.

$2.$度数为奇数的点需要加一条边.

$3.$度数全为偶数的连通块需要加两条边.

$4.$特判度数全为偶数，连通块只有一个的情况，不需要加边.

$5.$最终答案为 $ans/2$.

###### 【代码中有比较详细的解释】

# 注意
$1.$没有边的点不访问,但是$1$必须访问.

$2.$自环要访问.

# 代码
```
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int maxn = 1000500;
int n, m, vis[maxn], flag, du[maxn], point[maxn], cnt, ans;   //n, m为点和边，vis用来记录与这个点相连的边是否走完，du记录点的度数，point记录这个点是否有边相连，cnt记录连通块的个数，ans为答案； 
vector<int> e[maxn];

void dfs(int u) {   //dfs求连通块 
	vis[u] = 1;
	if (du[u] & 1) flag = 1;
	for (int i = 0; i < e[u].size(); i++) {
		if (vis[e[u][i]] == 0) dfs(e[u][i]);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf ("%d%d", &u, &v);
		point[u] = point[v] = 1;     //u, v两个点有边相连 
		if (u == v) continue;
		e[u].push_back(v);     //vector存边 
		e[v].push_back(u);
		du[u]++, du[v]++;      //记录度数 
	}
	point[1] = 1;          //因为1必须访问，所以设为1 
	int jidian = 0;      
	for (int i = 1; i <= n; i++) {
		if (du[i] & 1) {     //如果度数为奇数，ans++ ，jidian记录所有点中度数有没有奇数 
			ans++;
			jidian = 1;
		}
		else if (vis[i] == 0 && point[i] == 1) {  //如果度数为偶数 && 还未被标记 && 有边与它相连 
			cnt++;
			flag = 0;
			dfs(i);
			if (flag == 0) ans += 2;   //如果与i号点相连的点中没有度数为奇数的点 ans+=2； 
		}
	}
	if (jidian == 0 && cnt == 1) ans = 0;   //特判如果连通块为1个且点的度数全为偶数，那么不需要加边 ans = 0； 
	printf("%d", ans/2);
	return 0;
}
```



---

