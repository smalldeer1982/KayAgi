# Cthulhu

## 题目描述

...Once upon a time a man came to the sea. The sea was stormy and dark. The man started to call for the little mermaid to appear but alas, he only woke up Cthulhu...

Whereas on the other end of the world Pentagon is actively collecting information trying to predict the monster's behavior and preparing the secret super weapon. Due to high seismic activity and poor weather conditions the satellites haven't yet been able to make clear shots of the monster. The analysis of the first shot resulted in an undirected graph with $ n $ vertices and $ m $ edges. Now the world's best minds are about to determine whether this graph can be regarded as Cthulhu or not.

To add simplicity, let's suppose that Cthulhu looks from the space like some spherical body with tentacles attached to it. Formally, we shall regard as Cthulhu such an undirected graph that can be represented as a set of three or more rooted trees, whose roots are connected by a simple cycle.

It is guaranteed that the graph contains no multiple edges and self-loops.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF103B/33dc55a8762ea9a08fee5a98be66bd3670ec0fbb.png)

## 说明/提示

Let us denote as a simple cycle a set of $ v $ vertices that can be numbered so that the edges will only exist between vertices number $ 1 $ and $ 2 $ , $ 2 $ and $ 3 $ , ..., $ v-1 $ and $ v $ , $ v $ and $ 1 $ .

A tree is a connected undirected graph consisting of $ n $ vertices and $ n-1 $ edges ( $ n&gt;0 $ ).

A rooted tree is a tree where one vertex is selected to be the root.

## 样例 #1

### 输入

```
6 6
6 3
6 4
5 1
2 5
1 4
5 4
```

### 输出

```
FHTAGN!```

## 样例 #2

### 输入

```
6 5
5 6
4 6
3 1
5 1
1 2
```

### 输出

```
NO```

# 题解

## 作者：simonG (赞：15)

### 前言
这一题表面说了许多，实则没有用处。
### 详解
>* 本题题意：求给定图中是否有且仅有一个环。
>* 详解：并查集
>* 并查集目的：找到一个点最大的爸爸

```cpp
int get(int x) {
	if(f[x]==x)return x;
	else return  f[x]=get(f[x]);
}
```

>* 原理：
>* 如果一个点的爸爸( $get(f_x)$ )已经知道是他自己（$f_x$）了，那他就是最大的爸爸，就直接返回。
>* 否则不是，就找他的爸爸的爸爸，再把他的爸爸赋值给$f_x$。


>* 回归原题，探究一下条件：
>* 若$m<n$，则不能构成环。

![](https://cdn.luogu.com.cn/upload/image_hosting/i3tjmoeq.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

>* 若$m=n$，刚好能够构成环。
![](https://cdn.luogu.com.cn/upload/image_hosting/csnn9t5s.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

>* 若$m>n$，则构成环过多。
![](https://cdn.luogu.com.cn/upload/image_hosting/hszd06vq.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

>* 即先判断$m=n$，然后再用并查集求解是否大家都有一个爸爸。


### 代码

```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
#define ll long long
#define maxn 1001
#define INF 79871282
#define fre {freopen("group.in","r",stdin);freopen("group.out","w",stdout);}
using namespace std;
int n,m,p,q,f[maxn];
il int get(int x) {
	if(f[x]==x) return x;
	else return f[x]=get(f[x]);
}
int main() {
	scanf("%d%d",&n,&m);
	for(re int i=1; i<=n; i++) f[i]=i;
	if(n!=m) {
		puts("NO");
		return 0;
	}
	for(re int i=1; i<=n; i++) {
		scanf("%d%d",&p,&q);
		f[get(p)]=get(get(q));
	}
	for(re int i=2; i<=n; i++)
		if(get(i)!=get(i-1)) {
			puts("NO");
			return 0;
		}
	puts("FHTAGN!");
	return 0;
}
```

### 后记
行己有耻，请勿copy

---

## 作者：yimuhua (赞：7)

**题意：**

判断一个图是否**有且只有**一个环。

**算法：**

本题采用并查集。

**解题思路：**

1.如果 $n > m$ 时，不管怎么连，无法成为一个环。

2.如果 $n < m$ 时，不管怎么连，都会形成不止一个环。

总之， $n != m$ 时，环都无法形成。

3.当 $n = m$ 时运用并查集维护一个连通块，如果所有的点都在一个连通块里，那么就能形成有且只有一个环。

**注意：**

并查集寻找根节点时记得使用**路径压缩**，否则很容易超时。

使用并查集时一定要记得**初始化**，因为自己就是一个集合。

**AC代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, x, y, fa[100005];
int find(int x) {
    if(x == fa[x])//根节点
        return x;
    return fa[x] = find(fa[x]);//路径压缩
}
void unionn(int x, int y) {//合并
    int fx = find(x), fy = find(y);//各自所在的集合
    if(fx != fy)
        fa[fx] = fy;//不在同一集合就合并
    return;
}
int main() {
    cin >> n >> m;
    if(n != m) {
        cout << "NO";
        return 0;
    }
    //无法形成环
    for(int i = 1; i <= n; i++)
        fa[i] = i;
    //初始化
    for(int i = 1; i <= m; i++)
        cin >> x >> y, unionn(x, y);//合并图中的点
    for(int i = 2; i <= n; i++)
        if(find(i) != find(i - 1)) {//不在同一集合就一定不对
            cout << "NO";
            return 0;
    }
    cout << "FHTAGN!";//只有一个环
    return 0;
}
```


---

## 作者：GeChang (赞：6)

# 题解【CF103B Cthulhu】
## 0.题意
题目说了一大堆废话，最后就是在问你，**给出的图中是否只存在一个环**。

~~只找到了章鱼怪珂海星~~
## 1.分析

先分析亿下，如图，一个有 $n$ 个点， $n-1$ 条边的图中，必定可以构造出不存在环路的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/w54k3cxj.png)

这时，无论在图上连出任意两条边，都一定会形成环路；

![](https://cdn.luogu.com.cn/upload/image_hosting/xh451lmq.png)

再如图，一个有 $n$ 个点， $n$ 条边的图中，依旧考虑环路的情况，在最坏的情况下依然满足条件；

![](https://cdn.luogu.com.cn/upload/image_hosting/7i9mb9md.png)

最后在一个同上的图中考虑出现多于一个环路的情况，在最好情况下不可能出现只存在一个连通图的情况。
## 2.代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,x,y,p[100010]; //p[]为并查集数组
ll getroot(ll z) //并查集find+union的合体
{
	if(p[z]==z) return z;
	p[z]=getroot(p[z]); //路径压缩
	return p[z]; //返回
}
int main()
{
	cin>>n>>m;
	if(n!=m)
	{
		//假如n!=m，则一定不可能只出现一个环路且只有一个连通图
		cout<<"NO"<<endl;
		return 0;
	}
	for(ll i=1;i<=n;i++) p[i]=i; //初始化大小为n的并查集
	for(ll i=1;i<=m;i++) //循环输入+并查集
	{
		cin>>x>>y;
		ll root_x=getroot(x),root_y=getroot(y); //找祖先
		if(root_x!=root_y) p[root_x]=root_y; //假如不相等则合并
	}
	for(ll i=1;i<m;i++) //循环遍历m遍
	{
		if(getroot(p[i])==getroot(p[i+1])) continue; //满足条件
		else //不只存在一个连通图
		{
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"FHTAGN!"<<endl; //满足要求
	return 0; //结束qwq
}
```
# 莫抄袭，没了AC记录，空悲切！

---

## 作者：StevenJin (赞：2)

#### 这题有个简洁的算法：
##### 首先，这个图必须联通；其次，这个图的点数必须与边数相等，那么，这题就很水了。
#### 下面是代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool vis[100005];
vector<int>vec[100005];
void dfs(int i)
{
	vis[i]=1;
	for(int j=0;j<vec[i].size();j++)
		if(!vis[vec[i][j]])dfs(vec[i][j]);
}
int main()
{
	cin>>n>>m;
	if(n!=m)
	{
		cout<<"NO";
		return 0;
	}
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		vec[x].push_back(y);
		vec[y].push_back(x);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			cout<<"NO";
			return 0;
		}
	cout<<"FHTAGN!";
	return 0;
}

```


---

## 作者：Error_Eric (赞：1)

这题可真是够~~水~~的。

首先，及其显然，想要满足题目要求，必须是一个连通图。

### 一 判断连通图

判断连通图有很多办法，这里给出三种思路：

####  1.dfs

最常用，最实用，最好用，你甚至**不用回溯**。

```cpp
void dfs(int x){
    vis[x]=1;//标记自己来过
    for(int i=1;i<=n;i++) //循环决定自己下一个去的节点
        if(e[i][x] and (not vis[i])) dfs(i); 
}
```

然后只需要在主函数里面加上

```cpp
dfs(1);
for(int i=1;i<=n;i++) if(!vis[i]) return 0*puts("NO");
return 0*puts("FHTAGN!");
```

就万事大吉了。

时间复杂度$\Theta(n)$ , $n$为节点数。

#### 2.bfs

bfs其实是枚举边。

用``g[x][y]``保存一条边，表示从 $x$ 号节点连出的第 $y$ 条边,当然，最后还是要判断是否所有节点都已经遍历过。

当然，用vector 存``g``更香。

代码大概这样:

广搜：

```cpp
void bfs(int x){            //用队列广搜
    int q[100*2],head=0,tail=0;
    q[tail++]=x;
    while(tail>head){
        int x=q[tail++];
        vis[x]=1;
        for(int i=0;i<g[x].size();++i){ //枚举边
            if(vis[g[x][i]]) g[x].erase(g[x].begin()+i);
            else q[tail++]=g[x][i];
        }
    }
}
```
判断：
```cpp
bool judge(){                   //判断是否所有点已被遍历过
    for(int i=1;i<=n;++i)
        if(!vis[i]) return false;
    return true;
}
```
输入：
```cpp
int main(){
    ···
    for(int i=1;i<=m;i++）{
        scanf("%d %d",&p,&q);
        a[q].push_back(p);
        a[p].push_back(q);
    }
    ···
}
```
时间复杂度（仅在这道题中）  $\Theta(n)$ 。

然而有时~~好像~~是 $\Theta(n+m)$ 。

#### 3.并查集

可以判断有几个连通块。

并查集，顾名思义就是用来"并"和"查"的"集合"。

主要思路就是给所有集合一个"father",最初始每一个节点都是一个集合，最初始的“father”是他自己。

合并就是让两个集合拥有共同的"father"。

查询就是查询两个元素是否拥有共同的"father"。

当然你叫"father""pre"我也拿你没办法对不对。

这里就不详细讲了，详情看代码。

```cpp
#include<stdio.h>
using namespace std;
int n,m,p,q,fa[1000+50];
struct e{//边
	int a,b;
}d[1000+50];
int find(int x) {//找最father的father。
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);//路径压缩。
}
int main(){
...
	for(int i=1;i<=n;i++){
		scanf("%d %d",&p,&q);//输入边
		if(p>q) m=p,p=q,q=m;//并没有什么意义。
		fa[find(p)]=find(find(q));//合并集合
	}
	for(int i=2;i<=n;i++)
		if(find(i)!=find(i-1)) return 0*puts("NO");//判断是不是所有元素都在同一个集合。
	return 0*puts("FHTAGN!");
} 
```

### 二 判断合法

这道题的合法结构是若干棵根节点在一个环上的树。

如果我们在环上任意拆开一条边，那么所有的根节点就构成了一颗“一叉树”。

由于树是递归定义的，所以在环上任意拆开一条边之后，形成的数据结构就是一颗树。

换言之，这个图形的节点数和边数必须相等。

那么反过来思考，我们一旦有一棵无根树--“无环连通图”，将其中两个原本不相连的节点相连，这个图形就是合法的。

又因为一旦一个连通图只有$n-1$条边( $n$ 为节点数）那么这个连通图一定是树，所以只要一个连通图的边和节点数目相等，这个图在这道题中就是符合条件的。

### 三 代码

搜索：
```cpp
#include<stdio.h>
using namespace std;
int n,m,p,q;
bool e[1000+50][1000+50],vis[1000+50];
void dfs(int x){
	vis[x]=1;
	for(int i=1;i<=n;i++) if(e[i][x] and (not vis[i])) dfs(i); 
}
int main(){
	scanf("%d%d",&n,&m);
	if(n!=m) return 0*puts("NO");
	for(int i=1;i<=m;i++) scanf("%d%d",&p,&q),e[q][p]=e[p][q]=1;
	dfs(1);
	for(int i=1;i<=n;i++) if(!vis[i]) return 0*puts("NO");
	return 0*puts("FHTAGN!");
} 
```
并查集：
```cpp
#include<stdio.h>
using namespace std;
int n,m,p,q,fa[1000+50];
struct e{
	int a,b;
}d[1000+50];
int find(int x) {
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	if(n!=m) return 0*puts("NO");
	for(int i=1;i<=n;i++){
		scanf("%d %d",&p,&q);
		if(p>q) m=p,p=q,q=m;
		fa[find(p)]=find(find(q));
	}
	for(int i=2;i<=n;i++)
		if(find(i)!=find(i-1)) return 0*puts("NO");
	return 0*puts("FHTAGN!");
} 
```

---

## 作者：yzx72424 (赞：1)

题目要求和楼下说的基本差不多，我的思路和ta也一样，不过我用的是并查集找环。~~因为..并查集写起来比较简单，代码量较少QAQ~~

```
#include <bits/stdc++.h>
int pre[1005],n, m, a, b, flag, fail, road; 
inline int find(int x) {
    if(x != pre[x]) pre[x] = find(pre[x]);
    return pre[x];
} 
int main(){ 
        for(int i=1;i<=1000;i++)pre[i]=i;
        scanf("%d%d",&n,&m); 
        while(m--){
            scanf("%d%d",&a,&b);
            if(fail)continue;
            int px=find(a),py=find(b);
            if(px != py)++road,pre[px] = py;
            else{
                if(!flag)++road,flag=1; 
                else fail=1;
            }
        }
        if(fail||!flag||n!=road)puts("NO");
        else puts("FHTAGN!"); 
        return 0;
}

```
 

---

## 作者：StarryWander (赞：0)

## 本题解采用并查集。

### 题目概述：

判断一个图是否存在**有且只有**一个环。

### 解题思路：
1.如果 $n > m$ 时，不管怎么连，**无法成为一个环**。

2.如果 $n < m$ 时，不管怎么连，都会形成**不止一个环**。

总之，$n \ne m$ 时,环都**无法形成**。

3.当 $n = m$ 时运用**并查集**维护一个连通块，如果所有的点**都在一个连通块里**，那么就能形成有且只有一个环。


### 提示：

有关并查集的问题，寻找祖先时最好使用**路径压缩**，否则很可能超时。

在使用并查集时，一定要记得**初始化**，将自己设置为自己祖先。

### code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int pre[1000005];
int find(int x){//并查集路径压缩。
	if(pre[x]!=x) return pre[x]=find(pre[x]);
	else return x;
}
int main(){
	int n=read(),m=read();
	if(n!=m){//一定不可能的情况。
		printf("NO");
		return 0;
	} 
	for(int i=1;i<=n;i++) pre[i]=i;//初始化一定要注意。
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		pre[find(x)]=find(y);//将图中的点合并。
	} 
	for(int i=1;i<n;i++){
		if(find(i)!=find(i+1)){//如果两个点不在一个连通块就一定不是。
			printf("NO");
			return 0;
		} 
	}
	printf("FHTAGN!");
	return 0;
}

```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

题目大意：给一个无向图，如果它是连通无向图，而且有且仅有1个环，就是章鱼怪，否则不是。

设点数为 $n$，边数为 $m$：

依据图的性质，当它是一棵树时，$m=n-1$；

当它有大于等于2个环时，$m>n$；

所以，我们可以得出，当 $m!=n$ 时，就不是章鱼怪。

接下来说说 $m=n$ 的情况。

这个时候就要用到并查集了，先连边，因为 $m=n$，所以如果它是一个连通无向图，那么必定有一个环，它就是章鱼怪。

怎么判断它连通与否呢？很简单，用大约 $O(n)$ 的时间复杂度搜索一下，如果有两个点之间不是亲戚关系，说明该图不连通。注意，这里没有必要用 $O(n^2)$ 的时间复杂度。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
const int max_n=100;//最大点数
int n;//点数
int m;//边数
int fa[max_n+2];//并查集
int find(int a){
	if(a==fa[a]){
		return a;
	}
	fa[a]=find(fa[a]);
	return fa[a];
}
int main(){
	scanf("%d%d",&n,&m);
	if(n!=m){//点数和边数不相等，可能有大于等于两个环，也可能没有环
		printf("NO\n");
		return 0;
	}
	for(int i=1;i<=n;++i){
		fa[i]=i;
	}
	for(int i=1,x,y,xf,yf;i<=m;++i){
		scanf("%d%d",&x,&y);
		xf=find(x);
		yf=find(y);
		if(xf!=yf);
			fa[xf]=yf;
		}
	}
	for(int i=1;i<n;++i){
		if(find(i)!=find(i+1)){//如果没有亲戚关系，说明整张图有大于等于两个连通块
			printf("NO\n");
			return 0;
		}
	}
	printf("FHTAGN!\n");
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51328529)

By **dengziyue**

---

## 作者：FutureThx (赞：0)

……从前有个人来到海边。海上风雨交加，漆黑一片。这个人开始叫小美人鱼出现，但是他只叫醒了克图鲁……
$ $

~~题面笑死~~
$ $

## 题意
给定一个节点数 $N$ ，边数 $M$ 的无向图，若此图拥有一个环并且所有节点都联通，输出 $FHTAGN!$ ,否则输出 $NO$ .

## 思路

1. 首先我们可以着手判断图是否有一个环，我们画个图来看一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/2vd60fc6.png)
**发现当 $N = M$ 的时候图必定会出现环状.**
$ $

2. 接着我们有多种方法来判断图的连通性，这里我使用了**并查集** ，怎么写呢，让我们来看一下:
$ $

2.1. 首先进行**在线的建立父子关系**:
```cpp
void read(){
    cin >> n >> m;
    for(int i = 1;i <= m;i++){
        int x,y;
        cin >> x >> y;
        if(find_father(x) != find_father(y))
           node[find_father(x)].father = find_father(y);
    }
}
```

$ $

2.2 接着 $O(N)$ 扫一遍就完事了：
```cpp
int standard = find_father(1);
for(int i = 2;i <= n;i++){
   if(find_father(i) != standard){
     cout << "NO" << endl;
     return;
   }
}
cout << "FHTAGN!" << endl;
```

其中的变量 $standard$ 作用是**采用节点 $1$ 的祖先作为标准，若发现不同直接输出 $NO$ ,否则输出 $FHTAGN!$ .**

## 代码
$100pts \ $ 代码:
```cpp
#include <iostream>
using namespace std;
#define MAX_N 101
struct tree{
    int father = -1;
}node[MAX_N];
int n,m;
void read();
void deal_with();
int find_father(int x);
int main()
{
    read();
    deal_with();
    return 0;
}
void read(){
    cin >> n >> m;
    for(int i = 1;i <= m;i++){
        int x,y;
        cin >> x >> y;
        if(find_father(x) != find_father(y))
           node[find_father(x)].father = find_father(y);
    }
}
void deal_with(){
    if(m != n)
       cout << "NO" << endl;
    else{
        int standard = find_father(1);
        for(int i = 2;i <= n;i++){
            if(find_father(i) != standard){
               cout << "NO" << endl;
               return;
            }
        }
        cout << "FHTAGN!" << endl;
    }
}
int find_father(int x){
    if(node[x].father == -1)
       return x;
    return node[x].father = find_father(node[x].father);
}
```
总体来讲这题用并查集来做比较容易，希望各位可以借鉴思路但别借鉴代码。

## 后记

$Updata \ \ 2020.8.28 \ :$ 完成题解，求管理员给一个通过

---

