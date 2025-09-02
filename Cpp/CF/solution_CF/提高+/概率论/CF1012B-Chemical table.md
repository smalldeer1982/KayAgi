# Chemical table

## 题目描述

Innopolis University scientists continue to investigate the periodic table. There are $ n·m $ known elements and they form a periodic table: a rectangle with $ n $ rows and $ m $ columns. Each element can be described by its coordinates $ (r,c) $ ( $ 1<=r<=n $ , $ 1<=c<=m $ ) in the table.

Recently scientists discovered that for every four different elements in this table that form a rectangle with sides parallel to the sides of the table, if they have samples of three of the four elements, they can produce a sample of the fourth element using nuclear fusion. So if we have elements in positions $ (r_{1},c_{1}) $ , $ (r_{1},c_{2}) $ , $ (r_{2},c_{1}) $ , where $ r_{1}≠r_{2} $ and $ c_{1}≠c_{2} $ , then we can produce element $ (r_{2},c_{2}) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/a1ec2b34980f17dea8ef9d5c32f5d591ae712bba.png)Samples used in fusion are not wasted and can be used again in future fusions. Newly crafted elements also can be used in future fusions.

Innopolis University scientists already have samples of $ q $ elements. They want to obtain samples of all $ n·m $ elements. To achieve that, they will purchase some samples from other laboratories and then produce all remaining elements using an arbitrary number of nuclear fusions in some order. Help them to find the minimal number of elements they need to purchase.

## 说明/提示

For each example you have a picture which illustrates it.

The first picture for each example describes the initial set of element samples available. Black crosses represent elements available in the lab initially.

The second picture describes how remaining samples can be obtained. Red dashed circles denote elements that should be purchased from other labs (the optimal solution should minimize the number of red circles). Blue dashed circles are elements that can be produced with nuclear fusion. They are numbered in order in which they can be produced.

Test 1

We can use nuclear fusion and get the element from three other samples, so we don't need to purchase anything.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/d0188b7b484eed4ec50dd63bc64a04ce06b65611.png)Test 2

We cannot use any nuclear fusion at all as there is only one row, so we have to purchase all missing elements.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/ba8b5c94cc17a4604dd0e58fb6a66f6e2487526e.png)Test 3

There are several possible solutions. One of them is illustrated below.

Note that after purchasing one element marked as red it's still not possible to immidiately produce the middle element in the bottom row (marked as 4). So we produce the element in the left-top corner first (marked as 1), and then use it in future fusions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/5273513fe4bf0485a76591391c8b08a7edf8e9af.png)

## 样例 #1

### 输入

```
2 2 3
1 2
2 2
2 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1 5 3
1 3
1 1
1 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 3 6
1 2
1 3
2 2
2 3
3 1
3 3
```

### 输出

```
1
```

# 题解

## 作者：小粉兔 (赞：12)

这题也就是 P5089 EJOI 的 D 题，所以说是双倍经验啦！

比赛时这题我想了很久，猜了一个奇怪的结论交上去就对了。

这里贴一下官方题解的证明方法：

建立一张二分图，左边的点代表 $n$ 个周期，右边的点代表 $m$ 个主族。

把每一个元素 $(x,y)$ 看作一条边，连接第 $x$ 周期和第 $y$ 主族。

那么我们的目标是是这个二分图变成完全二分图，也就是有 $n \times m$ 条边。

考虑核聚变的条件：  
$(r_1, c_1) + (r_1, c_2) + (r_2, c_1) \to (r_2, c_2)$。

可以发现这个过程是不改变二分图中的连通分量的个数的。

而反过来，对于二分图中的某一个连通分量，也可以通过核聚变的方式，把这个连通分量变成“完全”的，也就是连接左右两部分的所有边都存在。

那么答案就是将这个二分图添加尽量少的边使得它联通的边数。

也就是：$\text{连通分量的个数}-1$。

思路很巧妙，代码并不难写：

```cpp
#include<bits/stdc++.h>
int n,m,q,x,y,S;
int v[400001];
int h[400001],nxt[400001],to[400001],tot;
inline void ins(int x,int y){nxt[++tot]=h[x];to[tot]=y;h[x]=tot;}
void D(int u){
	for(int i=h[u];i;i=nxt[i])if(!v[to[i]])
		v[to[i]]=1, D(to[i]);
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	while(q--) scanf("%d%d",&x,&y), ins(x,n+y), ins(n+y,x);
	for(int i=1;i<=n+m;++i) if(!v[i]) ++S, v[i]=1, D(i);
	printf("%d",S-1);
	return 0;
}
```

---

## 作者：zhaotiensn (赞：7)

~~这题的思路楼下的dalao已经讲的很清楚了，所以我只是来水一发c++的而已。~~

当一个元素（x，y）可以被合成时，说明有元素（x，y1），（x1，y），（x1，y1）。然后当你把n个横坐标和m个纵坐标抽象成点时，上面的东西就相当于当x和y在同一个集合里时，元素（x，y）可以被合成。每一个点就相当于将x所在的集合和y所在的集合合并起来。

当我们把一个点（x，y）看成将x所在集合和y所在集合合并时，可以发现，假设一个集合中有x和y，那么要么本来就有（x，y）这种元素，要么就是x先和y1合并，y先和x1合并，然后x1和y1合并，相当于有点（x，y1）（x1，y）（x1，y1），所以元素（x，y）也可以被合成。（~~我自认为这一段讲的很清楚了，十分好想，但是比赛是脑抽了。。~~）

然后直接用裸的并查集维护一下n+m个点的关系就好了，当有s个集合时显然添加s-1个点就可以合并为一个。所以统计集合数量，然后输出减一。


AC代码：
```
#include <iostream>
#include <cstdio>

#define Max 200005

using namespace std;

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read(){
    int x=0;char ch=gc();bool positive=1;
    for(;!isdigit(ch);ch=gc())if(ch=='-')positive=0;
    for(;isdigit(ch);ch=gc())x=x*10+ch-'0';
    return positive?x:-x;
}

inline void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}

inline void writeln(int x){
    write(x);puts("");
}//以上均不重要

int n,m,s,x,y,ans,fa[Max*2];//记得开n+m大小的数组

inline int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}//只有路径压缩的并查集

int main(){
    n=read();m=read();s=read();
    for(int i=1;i<=n+m;i++)fa[i]=i;//初始化
    for(int i=1;i<=s;i++){
        x=read();y=read()+n;//将y视为n+y然后就直接合并
        fa[find(y)]=find(x);
    }
    for(int i=1;i<=n+m;i++){
        if(fa[i]==i){//统计集合数量
            ans++;
        }
    }
    writeln(ans-1);//输出集合数减一
    return 0;
}

```

---

## 作者：derta (赞：3)

棋盘格套路：将点转化为边。具体地，我们可以将 $(x,y)$ 转化为 $x$ 到 $y'$ 的双向边，如下图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/ipb8nvea.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

此时，我们将题目中的条件转化：如果有 $x_1$ 到 $y_1'$，$x_2$ 到 $y_1'$，$x_2$ 到 $y_2'$ 的双向边，那么必然有 $x_1$ 到 $y_2'$ 的双向边。

即，

![](https://cdn.luogu.com.cn/upload/image_hosting/ig00w579.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

时，有

![](https://cdn.luogu.com.cn/upload/image_hosting/wzuynpca.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

但如果情况更复杂呢？考虑

![](https://cdn.luogu.com.cn/upload/image_hosting/55h6xvd3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

的情况。根据题目条件，有

![](https://cdn.luogu.com.cn/upload/image_hosting/35j696q7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

观察到 $x_1,y_2'$，$x_3,y_2'$，$x_3,y_3'$ 之间均有边，故有

![](https://cdn.luogu.com.cn/upload/image_hosting/bl5cfy0h.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

同理，$x_2,y_1'$，$x_2,y_3'$，$x_3,y_3'$ 之间均有边，故有

![](https://cdn.luogu.com.cn/upload/image_hosting/yk2xdy7z.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

此时我们做出猜测：若 $x_1,y_1',x_2,y_2',\cdots,x_n,y_n'$ 联通，则对于任意 $i,j \in \{1,2,\cdots,n\}$，$x_i$ 与 $y_j$ 之间均有边

证明比较简单，留作习题（

说了这么多，我们回到正题。把标记的点转化为边，那么原题所求即为加多少条边能使整张图联通，故答案即为 $\text{连通块的个数}-1$。用并查集维护即可。

```cpp
#include <cstdio>
const int MAXN = 200005;
int f[MAXN << 1], n, m, q, x, y, cnt;

int Find(int x) {
	int res = x, k = x, t;
	while(res != f[res])
		res = f[res];
	while(k != res) {
		t = f[k];
		f[k] = res;
		k = t;
	}
	return res;
}

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n + m; ++i)
		f[i] = i;
	while(q--) {
		scanf("%d%d", &x, &y);
		if(Find(x) != Find(y + n))
			f[Find(x)] = Find(y + n);
	}
	for(int i = 1; i <= n + m; ++i)
		if(f[i] == i)
			++cnt;
	printf("%d", cnt - 1);
	return 0;
} 
```

---

## 作者：CQ_Bab (赞：1)

# 思路
因为我们对于一个 $2\times2$ 的矩阵中若有 $3$ 个点可以就能将第 $4$ 个点给标记，那么我们现在就要想如何处理这种特点。我们首先可以将二维的点 $x,y$ 转换为 $x,y+n$ 这样就是一维了。那么我们可以发现一种神奇的东西例如我们的矩阵中的 $4$ 个数为 $(x,y),(x+1,y+n),(x,y+n+1),(x+1,y+n+1)$ 那么如果我们有三个数被加入了，例如将前三个合并了不就可以将第 $4$ 个给合并了吗。我们可以用并查集，将左右 $x$ 和 $y+n$ 合并即可。最后我们就只需要统计出联通块的数量再减去 $1$ 既可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y) 
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
const int N=1e6+10;
int f[N];
int find(int x) {
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
int n ,m,q;
fire main() {
	in(n),in(m),in(q);
	rep(i,1,n+m) f[i]=i;
	rep(i,1,q) {
		int x,y;
		in(x),in(y);
		f[find(y+n)]=find(x);
	}
	int res=0;
	rep(i,1,n+m) if(f[i]==i) res++;
	print(res-1);
	return false;
}
```

---

## 作者：KevinYu (赞：1)

Codeforces #500 Div1 Problem B:Chemical table        
同时也是eJOI2018 Problem D          
更优美的翻译可以参考[Luogu P5089 [eJOI2018]元素周期表](https://www.luogu.org/problemnew/show/P5089)           
我们可以将周期数理解成矩阵的行数，将族数理解为矩阵的列数，于是我们就可以用两个属性唯一确定一个元素了。        
聚变的规则如图所示:             
![](https://i.loli.net/2018/12/20/5c1b674365af9.jpg)         
最终有两道红线交汇处的点就是聚变产生的元素的编号。             
但是用矩阵表示元素太为低效(直接爆炸)，我们就考虑用边来表示点。
![](https://i.loli.net/2018/12/20/5c1b68255eb5e.jpg)            
就像这样，我们将左边设为行数，右边设为列数，就可以快乐地表示出边了。         
光光是表示了边肯定是不够的，我们要想办法表示聚变，以及求出怎么连上所有边。       
于是我们使劲观察起图像与实际的操作之间的联系。       
我们发现:在同一个强连通分量的所有点均可连边:       
![](https://i.loli.net/2018/12/20/5c1b81fb05658.jpg)          
所以我们需要将所有的点使用tarjan进行染色。     
染色过后呢？         
我们为了将所有的点都染上同样的颜色，以保证左右点两两间都可以连边，将所有的强连通分量都用一条边连起来即可。       
如图所示:           
![](https://i.loli.net/2018/12/20/5c1b8d5963237.jpg)
共需要连接(k-1)条边(如图中第三组所示),即可合成所有元素(k为连边前强连通分量的数量)。               
核心算法:tarjan(事实上，由于所有边都是双向的，dfs一边就行了)。           
(不会Tarjan的看看这里吧)tarjan详解:        
tarjan算法基于时间戳与dfs实现，我们将一个点被发现的时间存入dfn数组中，然后将一个点够追溯到的最早的栈中节点的次序计入low数组中。        
我们来过一遍算法流程：
1.初始化:
```cpp
void tarjan(int u)
{
    low[u]=dfn[u]=++now;
    hep[++top]=u;vis[u]=1;
```
我们可以发现，tarjan的初始化中要完成2个工作:     
①.更新时间戳与low数组      
②.将节点压栈并打上标记       
2.tarjan主过程:
```cpp
    for(int i=head[u];i!=-1;i=a[i].next)
    {
		int v=a[i].to;
		if(!dfn[v]){tarjan(v);low[u]=min(low[u],low[v]);}
        	else if(vis[v])low[u]=min(low[u],dfn[v]);
    }
```
我们来慢慢分析它：    
我们首先遍历每一条边，然后对能到达的点进行访问:     
```cpp
    for(int i=head[u];i!=-1;i=a[i].next)
    {
		int v=a[i].to;
```
我们需要分出三种v点：     
1.从没访问过的     
对于这个点，我们将它作为下一个点，递归地进行tarjan过程。    
在tarjan结束后，更新它的low数组。      
你可以把更新的过程理解成从tarjan过程里回传来了它的low值，我们将它的low值与现在这个节点的low值比较，并取较小值。
```cpp
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
```
2.访问过，并在栈里的       
这种节点是可以到达当前节点的，我们发现了这样一个点，就是发现了一个强连通分量，于是我们对当前点的low值进行更新
```cpp
        else if(vis[v])low[u]=min(low[u],dfn[v]);
```
3.访问过，但不在栈里的          
都不能到达你，跟你有什么关系吗，直接忽视掉就行了。      
3.退栈:
```cpp
    if(dfn[u]==low[u])
    {
        ++tot;
        vis[u]=0;
        while(hep[top+1]!=u)
        {
            fa[hep[top]]=tot;
            vis[hep[top--]]=0;
        }
    }
}
```
整个退栈过程就是记录强连通分量的过程，下面我就来详细解释一下。         
退栈的条件是```dfn[u]==low[u]```，代表着我们的遍历过程已经触底，并且回溯回来了。      
在我们当前点上方的都是什么点呢？都是在同一个强连通分量中的点。所以我们将其全部取出，并记录进一个强连通分量中(一般管这个叫“染色”)。       
tarjan缩点过程完整代码:
```cpp
void tarjan(int u)
{
    low[u]=dfn[u]=++now;
    hep[++top]=u;vis[u]=1;
    for(int i=head[u];i!=-1;i=a[i].next)
    {
		int v=a[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
        else if(vis[v])low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        ++tot;
        vis[u]=0;
        while(hep[top+1]!=u)
        {
            fa[hep[top]]=tot;
            vis[hep[top--]]=0;
        }
    }
}
```
本题完整代码:
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<climits>
#include<ctime>
#include<algorithm>
#include<complex>
#include<iostream>
#include<map>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
#define ll long long
using namespace std;
struct edge
{
    int to,next;
}a[400040];
int head[400040];
int w[400040];
int val[400040];
int fa[400040];
int low[400040];
int dfn[400040];
int now(0);
int hep[400040];
int top(0);
int vis[400040];
int usd[400040];
int cnt(0);
int cal(0);
int tot(0);
int n,m,q;
void addedge(int xi,int yi)
{
    a[cnt].to=yi;
    a[cnt].next=head[xi];
    head[xi]=cnt++;
}
void tarjan(int u)
{
    low[u]=dfn[u]=++now;
    hep[++top]=u;vis[u]=1;
    for(int i=head[u];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v])low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        ++tot;
        vis[u]=0;
        while(hep[top+1]!=u)
        {
            fa[hep[top]]=tot;
            vis[hep[top--]]=0;
        }
    }
}
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&q);
	while(q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		addedge(x,y+n);
		addedge(y+n,x);
	}
	for(int i=1;i<=n+m;i++)if(!dfn[i])tarjan(i);
	printf("%d",tot-1);
    return 0;
}
```



---

## 作者：AC_love (赞：1)

我们不妨把这个网格抽象成一个 $m + n$ 个点的图，其中每个点都对应了一横行或一竖列。

此时我们发现：每个点 $(x, \ y)$ 都可以抽象成一条连接了 $x$ 行和 $y$ 列的一条边。

那么我们要求覆盖全部元素其实就是要任何一个 $x$ 行和 $y$ 列，都有一条边相连。

然后我们再看我们的合成元素的规则。

如果 $x$ 行 $y$ 列，$x + a$ 行 $y$ 列和 $x$ 行 $y + b$ 列都有元素的话，我们就可以合成一个 $x + a$ 行，$y + b$ 列的元素。

这东西可以抽象成：

$x$ 和 $x + a$ 到 $y$ 有边，$x$ 和 $y + b$ 有边，那么 $x + a$ 和 $y + b$ 就有一条新边。

发现规律其实就是：互相连通的点之间可以自己搭一条边。

那么我们考虑：如何标记最少的格点来使整个图都被标记呢？

显然我们只需要至多 $m + n - 1$ 个点让整个图上的所有点都互相连通即可。

那么我们只需要计算让所有点都连通的最小代价即可。

这玩意怎么算呢？

我们发现我们每次可以通过添加一条边的方式来合并两个连通块。我们希望所有点最后合成一个大连通块，那么所需要的代价就是连通块数量减一。

维护连通块数量，显然用并查集。

并查集每次有效的合并操作都会使连通块数量减一，因此我们只需要统计一共进行了几次有效的合并操作即可。

注意一个坑点：此题的点数是 $n + m$，也就是说数组要开 $4 \times 10^5$ 以上而不是 $2 \times 10^5$ 以上！开小了会 RE！

代码实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 414514;
int r[N];

int Find(int x)
{
	if(r[x] == x)
		return x;
	r[x] = Find(r[x]);
	return r[x];
}

int n, m, q;

int main()
{
	cin >> n >> m >> q;
	for(int i = 1; i <= n + m; i = i + 1)
		r[i] = i;
	int ans = n + m - 1;
	for(int i = 1; i <= q; i = i + 1)
	{
		int x, y;
		cin >> x >> y;
		int fx = Find(x);
		int fy = Find(y + n);
		if(fx == fy)
			continue;
		r[fy] = fx;
		ans --;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Mickey_snow (赞：1)

　这道题目难度并不大，但是需要使用到特殊构造的算法。

　首先，我们假设这个表规格是 $nm$ 的，如果上面一个点也没有，那么我们只需要放置 $n+m-1$ 的点，就可以产生出其它所有的点。一种可行的方案是放满最上面一行和最左边一列。换句话说，最终计算出来的总代价(额外放置的点的数量)不可能超过 $n+m-1.$

　我们假设这是一个并查集，那么当这个并查集中只有一个联通块时，就覆盖了所有的点，满足题意。
 
　那么如何将一个使用二元组描述的点抽象成一个并查集中的元素呢？我们假设这个点坐标为 $(x_1, y_1)$ 如果有另外三个点 $(x_1, y_0), (x_0,y_1), (x_0, y_0)$ 那么这个点就与他们在同一个集合中。对于一个存在的点 $(x_1, y_1)$ ，将集合 $x_1$ 与集合 $y_1 + n$ 合并，这样原图中所有的点都可以被分到 $n+m$ 个集合中，而合并两个集合的代价就是添加一个额外的点。也就是1.
 
　并查集可以在线维护，最后求一下它的联通数量减去1即为答案。
 
伪代码如下:

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CF1012B
{
    class Program
    {
        public class Global 
        {
            public static int[] up;
        }

        public static int FindTop(int nowAt) {
            return (Global.up[nowAt] == nowAt ? nowAt : (Global.up[nowAt] = FindTop(Global.up[nowAt])));
        }

        static void Main(string[] args)
        {
            string inp;string[] div;
            int totLine, totList, totPoints, x, y;

            inp = Console.ReadLine();div = inp.Split(' ');
            totLine = Convert.ToInt32(div[0]);
            totList = Convert.ToInt32(div[1]);
            totPoints = Convert.ToInt32(div[2]);

            Global.up = new int[totLine + totList];
            for (int i = 0; i < totLine + totList; i++)
                Global.up[i] = i;

            for (int i = 0; i < totPoints; i++) {
                inp = Console.ReadLine();div = inp.Split(' ');
                y = Convert.ToInt32(div[0]) - 1;x = Convert.ToInt32(div[1]) - 1;
                Global.up[FindTop(y)] = FindTop(x + totLine);
            }

            int _count = -1;
            for (int i = 0; i < totLine + totList; i++)
                if (Global.up[i] == i)
                    _count++;
            Console.WriteLine(_count.ToString());
        }
    }
}
```

---

## 作者：Mars_Dingdang (赞：0)

神奇的二分图连通块题。

## 题目大意
给定一张 $n$ 行 $m$ 列的矩阵，有 $q$ 个元素 $(x_i,y_i)$ 为 $1$，其余均为 $0$。如果 $(x,y), (x,y'), (x',y)$ 上的元素均为 $1$，那么你可以将 $(x',y')$ 上的元素也扩展为 $1$。

求最少需要在初始矩阵中将几个 $0$ 变成 $1$，才能使得整张矩阵能够通过上述规则的扩展使得所有元素均变为 $1$。$m,n,q\le 2\times 10^5$。

## 大体思路
这一类矩阵题目有一个套路的二分图建模方式：将 $n$ 行作为 $n$ 个左部点，编号 $1\sim n$；$m$ 列作为 $m$ 个右部点，编号 $n+1\sim n+m$。我们令所有 $(x,y)$ 上值为 $1$ 的元素，在 $(x,y+n)$ 直接连边。题目要求的最终状态是每个位置的元素均为 $1$，即二分图构成完全二分图。

考虑题目中的扩展规则。$(x,y), (x,y'), (x',y)$ 上的元素均为 $1$，等价于 $(x,y), (x,y'), (x',y)$ 之间有连边，那么 $x,y,x',y'$ 构成一个连通块。显然，添加了 $(x',y')$ 这条边后，连通块数量不会改变。假设原二分图有 $C$ 个连通块，那么，无论每个连通块如何连边都不会使得 $C$ 减少。为了使得 $C$ 变为 $1$，需要额外连至少 $C-1$ 条边（这是因为连通块变成完全二分图可能需要额外连边）。因此 $ans\ge C-1$。

接下来证明 $ans =C-1$ 可行。考虑某一连通块中两个点 $u,v$。最终的目标是保证 $u,v$ 之间连边。

- 如果 $(u,v)\in E$ 那么直接成立。
- 如果 $(u,v)\notin E$，必然存在另外一个左部点 $x$ 和右部点 $y$，使得 $(u,y),(x,v)\in E$，并且存在 $y\to x$ 的路径，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/ffsseb6l.png)

由于 `Z` 字形和 `又` 字行都是满足扩展条件的，可以在 $y\to x$ 路径上将 `Z` 字形反复连边，最后会形成一个大的 `又` 字形，然后 $u,v$ 便可连边。这证明了同一个连通块内任意两点之间都可以通过扩展自动连边，因此只需要额外连接 $C-1$ 条边即可。

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 4e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int hd[maxn], ver[maxn], nxt[maxn], tot, n, m, q, ans;
inline void add(int u, int v) {
	ver[++tot] = v; nxt[tot] = hd[u]; hd[u] = tot;
	ver[++tot] = u; nxt[tot] = hd[v]; hd[v] = tot;
}
bool vis[maxn];
inline void dfs(int u) {
	for(int i = hd[u]; i; i = nxt[i]) {
		int v = ver[i];
		if(vis[v]) continue;
		vis[v] = 1;
		dfs(v);
	}
}
int main () {
	read(n); read(m); read(q);
	rep(i, 1, q) {
		int x, y;
		read(x); read(y);
		add(x, y + n);
	}
	rep(u, 1, n + m) if(!vis[u]) {
		vis[u] = 1;
		ans ++;
		dfs(u);
	}
	writeln(ans - 1);
	return 0;
}
```

---

## 作者：芦苇林 (赞：0)

虽然兔队已经发过一样方法的题解了，还是发一份对结论简单证明与进一步阐释叭qwq

[原题链接](https://codeforces.com/problemset/problem/1012/B)     
[宣传博客](https://www.cnblogs.com/violetholmes/p/14341627.html)

## 题解

可以发现，能够使另一个方格填色的三个方格的坐标可以写为$(a,b),(a,c),(c,d)$，由$(a,b)$以$a$为检索可以找到$(a,c)$，而$(a,c)$以$c$为检索找到$(c,d)$。由此想到，将行、列数构造为点，而每一个方格则是一条无向边。如题目样例3可构造为如下的图：
![图](https://images.cnblogs.com/cnblogs_com/violetholmes/1913672/o_2101281002592021-01-28.png)

其中深蓝色的边是题目中已给出的格子。例如$(C_5,C_2,C_1,C_6)$四个联通的点即可推断出一条新边$C_5C_6$，图中用黄色笔画出，代表格子$(1,1)$可以被填充，其余黄边同理。而这时，点$C_7$仍未与其他点联通，也就是格子$(4,1),(4,2),(4,3)$未被填充。因此必须消耗一次填涂次数，添加一条边$C_7C_2$（$C_7C_4,C_7C_6$亦可），也就是图中浅蓝色边。而通过这条边可以推断出另2条绿边，最终该图变为完全二分图，全部填充完毕。

但是无法直接枚举点递归，因为这样时间为$O(nq)$。可以发现，每一个连通图一定可以通过上述推导化为完全二分图，证明：当连通图中节点数$\ge 3$时，一定可以划分为若干个由$3$个节点组成的连通子图，由其可连接新边使之称为环。而与该环连接的其他点一定可以通过推导与环中全部节点连接（过程略），因为此图为连通图，所有节点均可通过相邻节点与该子图（环）连接。所以只需使构造出的图成为连通图，即将所有连通子图连接，需建新边数$=$连通子图数$-1$。

## AC代码

```c
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int fst[N],nxt[2*N],v[2*N],cnt;
bool vis[N];//vis[i]:是否(1/0)已经过编号为i的节点
void add(int x,int y)
{
	v[++cnt]=y;
	nxt[cnt]=fst[x]; fst[x]=cnt;
}
void dfs(int x)
{
	vis[x]=1;
	for(int i=fst[x];i;i=nxt[i])
	{
		int y=v[i];
		if(!vis[y]) dfs(y);
	}
}
int main()
{
	int n,m,q,ans=0;
	scanf("%d%d%d",&n,&m,&q);
	int x,y;
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,n+y); add(n+y,x);
	}
	for(int i=1;i<=n+m;i++)//统计联通子图个数
		if(!vis[i]) {dfs(i); ans++;}
	printf("%d",ans-1);
	return 0;
}
```


---

## 作者：LiftingTheElephant (赞：0)

将问题转化成n行m列的图       
一个点$(x,y)$的作用是将$x$行和$y$列连通  
这个题目要求的是求最小代价使图全部连通，按照上述方式维护并查集并最终统计有多少个并查即可。      
最后上代码：
```
#include<iostream>
#define maxn 200005
using namespace std;
int n,m,q,ans,fa[maxn<<1];//fa数组维护每个点的父亲
int getf(int u)//路径压缩+求一个点的父亲。
{
	if(fa[u]==u)
		return u;
	return fa[u]=getf(fa[u]);
}
int main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=n+m;i++)
		fa[i]=i;
	for(int i=1,u,v;i<=q;i++)
	{
		cin>>u>>v;
		v=v+n;
		int fu=getf(u),fv=getf(v);
		if(fu==fv)
			continue;
		fa[fu]=fv;//构建并查集。
	}
	for(int i=1;i<=n+m;i++)
		if(fa[i]==i)
			ans++;//找到并查集中一个根就ans++
	cout<<ans-1<<endl;
    cout<<"ans"<<endl;
	return 1;
}

```

---

## 作者：大菜鸡fks (赞：0)

可以把加点操作抽象为 集合合并操作。因为 当x1,y1,x2,y2在同一个集合时（有其中任意三个点时），这四个点就都能被生成。那么我们要做的工作就是把所以点都加入这个集合中。

```cpp
#include<cstdio>
using namespace std;
const int N=600005;
int n,m,q,fa[N];
int getpa(int x){return (fa[x]==x)?x:fa[x]=getpa(fa[x]);}
inline int Union(int x,int y){
	int u=getpa(x),v=getpa(y);
	if (u!=v){
		fa[u]=v;
		return 1;
	}
	return 0;
}
inline void init(){
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=n+m;i++) fa[i]=i;
	for (int i=1;i<=q;i++) {
		int x,y; scanf("%d%d",&x,&y);
		Union(x,y+n); 
	}
}
int ans;
inline void solve(){
	int rt=getpa(1);
	for (int i=1;i<=n+m;i++) ans+=Union(i,rt);
	printf("%d\n",ans);
}
int main(){
	init();
	solve();
	return 0;
}
```



---

