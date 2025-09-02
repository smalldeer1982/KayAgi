# [USACO3.1] 最短网络 Agri-Net

## 题目背景

Farmer John 被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。


## 题目描述

FJ 已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了用最小的消费，他想铺设最短的光纤去连接所有的农场。

你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤最短的方案。每两个农场间的距离不会超过 $10^5$。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.1


## 样例 #1

### 输入

```
4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0```

### 输出

```
28```

# 题解

## 作者：chengni (赞：94)

这道题所给的数据是矩阵，而矩阵是对称的，我们只需要读入其中一半的数据，就可以转成裸的最小生成树了。

然后使用克鲁斯卡尔算法就可以了。

简单来说 就是把每一条边按权值从小到大排序，然后依次看，如果两个端点不在一个集合里，就把他们合并，计算。如果已经包含所有点了，直接输出数据退出。

```cpp
#include<bits/stdc++.h>

using namespace std;

struct node{
	int x,y,w;
}a[200002];

int f[200002];

bool cmp(node xx,node yy){//结构体排序
	return xx.w<yy.w;
}

int find(int x){
//并查集说白了就是找父结点的过程，同一个父节点即同一个区间
	if(x==f[x]) return x;
	f[x]=find(f[x]);
	return f[x];
}

int main(){
	int n,k,m=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		f[i]=i;
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&k);
			if(j>i){
            //读入时加一个判断就可以了，不需要读那么多
				m++;
				a[m].x=i;a[m].y=j;a[m].w=k;	
			}	
		}
	}
	sort(a+1,a+m+1,cmp);//排序
	int ans=0,p=1;
	for(int i=1;i<=m;i++){
		if(find(a[i].x)!=find(a[i].y)){
        //如果不在一个集合
			ans+=a[i].w;
			f[find(a[i].x)]=a[i].y;
            //合并两个节点
			p++;
			if(p==n) break;	
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：arfa (赞：67)

# Kruskal , K氏算法

相比与Prim,K似乎容易呢......(不妨去试一下P+Heap)。我是来解释一下呢,还是解释一下呢......

AC记录:#10

AC
0ms/5136KB


## 裸-克鲁斯卡尔-最小生成树

步骤:

```psacal
1.将边排序
2.判断是否能插入此边,插入后做:
    1.inc(ans,路径长度)
    2.合并连通分支
```

![](http://www.blogfshare.com/wp-content/uploads/images/--Prim\_9EA9/image\_thumb\_5.png)

意思是:你将边排了序,那么再判断是否能插入,当插入的边的个数为n-1的时候,就是最小生成树[贪心]。



## 如此的解释[对于插入]

背景:假如A是社会上的某个混混,他有很多老大。

### 达到什么条件插入?

A想跟B发生关系,但是他们的兄弟组合有规定,发生什么事情都要告诉老大先...A带着B去访问老大Y。Y叫A去见Z。但是他们没有带见面礼(100万什么的就免了),Z很不削。

```pascal
Z刻薄的说:
1.你们两个不能是同一个血型的...
2.看见B,我很眼熟,我怀疑是我某个亲戚的亲戚的亲戚的女儿,如果是,那千万不能跟你这种小混混发生关系。(查找根是否相同来判断是否是一个联通分支,如果是,那么说明这个点已经合并过了,再合并会增加路径,不是最少的了)
```
1.A大笑:当然不是一个血型的(Z怀疑他在吹牛)。(i<>j,i点不能是j点)


2.A苦笑:那我怎么知道呢?

### 对于[刻薄的问题之2]的破解

A经历[刀山火海],找到了B的大爷爷,他问:“那个面容猥琐的Z是你家的吗?”大爷爷果断的说:“保定不是”。终于，B和A发生了关系...


但是有一个问题,大爷爷的辈份比Z高,也算加入了兄弟组合,他想当老大[另一个规矩]。Z说:“没关系,兄弟们都听我的,你当了只是摆一个架子而已”。


[讲正事]这里很像一个并查集,A要找老大,B要找大爷爷,他们不是一个连通分支的,所以可以合并[没有合并过]。而这2点合并了,应该合成一个连通分支,可是A有老大也有小弟,B有妹妹也有大爷爷,所以直接让根合并不就可以了。让Z做老大,或者大爷爷做老大,他们就是一个连通分支了。

## 关于路径压缩

A每次和别人发生关系都要找Y才能找Z。A很不喜欢Y这个老大,于是他就拿着100kuai去见了Z,“我住在你家旁边好不好?”


每一次找到根都可以直接把父节点指向根,这查找时就能很快。从[A]-[Y]-[Z]变为[A]-[Z],当然有些时候可以节省很多时间。


## 代码详解:

```pascal
var
        fa:array[1..30000] of longint;//老大...
        a,b,c:array[1..30000] of longint;//b(起点)和c(终点)的长度为a
        i,j,n,m,k,l,ans:longint;//ans是答案

procedure sort(l,r:longint); var i,j,s,t:longint; begin i:=l; j:=r; s:=a[(l+r) div 2]; repeat while a[i]<s do i:=i+1; while a[j]>s do j:=j-1; if i<=j then begin t:=a[i]; a[i]:=a[j]; a[j]:=t; t:=b[i]; b[i]:=b[j]; b[j]:=t; t:=c[i]; c[i]:=c[j]; c[j]:=t;
        inc(i); dec(j); end; until i>=j; if i<r then sort(i,r); if j>l then sort(l,j); end;
//pascal手打排序,不必在意。注意,路径用来排序时起点和终点也要换

procedure start;//输入和排序,本人使用一维数组
var
        t,p:longint;
begin
        p:=0;
        read(n);
        for i:=1 to n do
                fa[i]:=i;
        for i:=1 to n do
                for j:=1 to n do
                begin
                        inc(p);
                        b[p]:=i;
                        c[p]:=j;
                        read(a[p]);
                        if i=j then
                                a[p]:=maxlongint;
                end;

        sort(1,n*n);
end;

function get(x:longint):longint;//找根...
begin
        if fa[x]=x then
                exit(x)
        else
        begin
                get:=get(fa[x]);//递归father
                fa[x]:=get;//路径压缩
        end;
end;

procedure min_way(x:longint);
var
        i,j:longint;
begin
        i:=b[x];//b点和c点要连边
        j:=c[x];
        if (i<>j) then//不是同一个点
        begin
                fa[i]:=get(i);//找老大
                fa[j]:=get(j);//找老大
                if (fa[i]<>fa[j]) then//不是同一个组合(不是同一个连通分支)
                begin
                        inc(ans,a[x]);//加上本路径
                        fa[get(j)]:=fa[i];//合并
                end;
        end;
        if x=n*n then//合并完成
                exit;
        min_way(x+1);//下一个需要合并的边
end;

begin
        start;
        min_way(1);
        writeln(ans);
end.






```

---

## 作者：Strong_Jelly (赞：48)

已更新2019.5.2

# 最短网络

**题目背景**

农民约翰被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。

**题目描述**

约翰已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了用最小的消费，他想铺设最短的光纤去连接所有的农场。

你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤**最短**的方案。每两个农场间的距离不会超过100000



------------

这道题是最小生成树的**模板题**。

```cpp
生成树是什么呢？

对于一个拥有n个顶点的无向连通图，它的边数一定多

于n-1条。若从中选择n-1条边，使得无向图仍然连通，

则由n个顶点及这 n-1条边组成的图被称为原无向图的

生成树。
```
那最小生成树，顾名思义是指**一个图中所有边的权值之和最小的生成树**（权值是指一个图中某一条边的长度）。

让我们先来介绍两种求最小生成树的算法吧~

## 1.Prim算法（普里姆算法）


**Prim算法是通过每次添加一个新节点加入集合，直到所有点加入停止的 最小生成树的算法。**

**时间复杂度：O（n²）**

模板（本题代码）code：

```cpp
#include <bits/stdc++.h>//万能头 
#define INF 0x3f3f3f3f//巨大无比的一个数 
using namespace std;
int n, q[1001][1001], minn[100001], ans;//minn表示不在最小生成树中的点与在最小生成树中的点相连的最小边权 
bool f[100001];//不在最小生成树中的点f等于false，在就等于true 
int main()
{
	memset(minn, INF, sizeof(minn));//初始化 
	minn[1] = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &q[i][j]);//输入邻接矩阵 
		}
	}
	for(int i = 1; i <= n; i++)
	{
		int k = 0;
		for(int j = 1; j <= n; j++)
		{
			if(!f[j] && minn[j] < minn[k])//寻找权值最短的边（且不能是已经在最小生成树中的点） 
			{
				k = j;
			}
		}
		f[k] = true;//把它加入最小生成树 
		for(int j = 1; j <= n; j++)
		{
			if(!f[j] && q[k][j] < minn[j])//利用新点改变其他不在最小生成树中的点的边的权值 
			{
				minn[j] = q[k][j];
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		ans += minn[i];//把所有在最小生成树中的点的权值加起来 
	}
	printf("%d", ans);
	return 0;
} 
```



------------


## 2.Kruskal算法（克鲁斯卡尔算法）

**Kruskal算法是通过并查集，按照边的权重顺序（从小到大）将边加入生成树中，但是若加入该边会与生成树形成环则不加入该边,选其次。直到树中含有n - 1条边为止。**

**时间复杂度：O（E log E）（E为边数）**

这里就不多说并查集了，不懂的可以先看一下[【模板】并查集](https://www.luogu.org/problemnew/show/P3367)

这是并查集的题解----->[并查集的题解](https://www.luogu.org/blog/qqq1112/solution-p3367)

模板（本题代码）code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, v, k, ans, fa[10000001];
struct node//定义结构体存图 
{
	int x, y, z;//z表示x连y的权值 
}stu[100001];
int find(int x)//并查集 
{
	if(x != fa[x])
	{
		fa[x] = find(fa[x]);
	}
	return fa[x];
}//查找 
void unity(int x, int y)
{
	int r1 = find(x);
	int r2 = find(y);
	fa[r1] = r2;
}//合并 
bool cmp(node a, node b)//从小到大结构体排序 
{
	return a.z < b.z;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		fa[i] = i;//并查集初始化 
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &v);
			if(j > i)//邻接矩阵上下对称，存一半就行了 
			{
				m++;
				stu[m].x = i;
				stu[m].y = j;
				stu[m].z = v;
			}
		}
	}
	sort(stu + 1, stu + m + 1, cmp);//排序 
	for(int i = 1; i <= m; i++)
	{
		if(find(stu[i].x) != find(stu[i].y))
		{
			ans += stu[i].z;//加上最小生成树中边的权值 
			unity(stu[i].x, stu[i].y);//连接起来 
			k++;//记录边数 
			if(k == n - 1)//n - 1条边就行了 
			{
				printf("%d", ans);
				return 0;
			}
		}
	}
	return 0;
}
```

# finish(～￣▽￣)～

---

## 作者：yyy2015c01 (赞：22)

发现题解里较少堆优化的Prim解法，来提交一发（使用了STL的优先队列）。  

鉴于该题中，图为稠密图，边数大于点数，因此理论时间复杂度方面堆优化Prim优于Kruskal。  
Prim的简要步骤说明：  
1. 初始所有节点为白色。
2. 选择1号节点，加入最小生成树（染为蓝色）；
3. 重复以下步骤直至建完（重复N-1次，因为有N-1条边）：  
	1. 在连接白-蓝点的边中找到边权最小的**（此处堆优化降低复杂度）**；
    2. 将该边连接的白点（未加入最小生成树的点）染为蓝色（加入），更新当前边权和。  

想要更具体的百度即可。  
程序注释应该足够多了吧……？

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 105
struct Node{
    int a, b;//a->b
    int w;//距离 
    bool operator <(const struct Node &n)const{
        return w> n.w;
    }
};
priority_queue <Node> edge;//待选边集 
vector <Node> G[maxn];//G[i]:以i为起点的边集 
bool visted[maxn];//是否已在最小生成树里 
int main()
{
    int N;
    scanf("%d", &N);
    for (int i=0;i<N;i++)
    	for (int j=0;j<N;j++) {
    		int tmp;
    		scanf("%d",&tmp);
    		if (tmp==0) continue;
    		else {
    			G[i].push_back(Node{i, j, tmp});
        		G[j].push_back(Node{j, i, tmp});
				//C++11才能这么用参数列表，虽然非C++11也能通过，但不建议这么做 
        		//双向边 
            }
        }
    visted[1] = true;
    for(int i=0; i< G[1].size(); i++)//预先将以1号点为起点的所有边加入待选边集 
        edge.push(G[1][i]);
    int all =0;//目前的最小生成树边权和 
    int cnt = 0;//已经在最小生成树里的边数 
    while(cnt < N-1){
        int w = edge.top().w;
        int n = edge.top().b;
        edge.pop();

        if (visted[n])//若该边所到达节点已经处于最小生成树中则跳过 
            continue;
        visted[n] = true;//标记其已加入最小生成树 
        all += w;
        cnt ++;
        for (int i=0; i< G[n].size(); i++)
        {
            if (!visted[G[n][i].b])//将以新点为起点的边加入待选边集 
                edge.push(G[n][i]);
        }
    }
    printf("%d\n", all);
    return 0;

}
```

---

## 作者：Outro5201 (赞：13)

朴素的的Prim算法（没有任何优化）

用时: 32ms / 内存: 820KB

直接上代码

```c
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAX = 105;
int g[MAX][MAX];//邻接矩阵
int minn[MAX];
bool vis[MAX];//标记是否访问
int n;

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> g[i][j];
		}
	}
	memset(minn, 0x7f, sizeof(minn));//初始化
	memset(vis, false, sizeof(vis));
	minn[1] = 0;//将起点初始化
	for(int i = 1; i <= n; i++) {
		int k = 0;
		for(int j = 1; j <= n; j++) {
			if(!vis[j] && (minn[j] < minn[k])) {
				k = j;//从起点出发
			}
		}
		vis[k] = true;//将这个顶点标记为访问过
		for(int j = 1; j <= n; j++) {
			if(!vis[j] && (g[k][j] < minn[j])) {
				minn[j] = g[k][j];//记录这条边的权值
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += minn[i];//将走过的边的权值加起来
	}
	cout << ans << endl;//输出结果
	return 0;
}
```
# 管理员辛苦了

听说NOIP前发题解 rp++

**祝大家AK NOIP！**


---

## 作者：ღ﹏ﻬ北❦栀 (赞：9)

## 唉，看各位大佬用各种算法，我这个蒟蒻只能用克鲁斯卡尔了。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//为什么要用这个头文件呢，因为克鲁斯卡尔要先快排sort函数， 不了解可以去题解最下面看一下克鲁斯卡尔的算法套路。 
using namespace std;
struct point
{
	int x;
	int y;
	int v;
};//定义结构体来存各条边 
point a[9901];//存边 
int fat[101];
int n,i,j,x,m,tot,k;//tot用来存这个最小生成树的长度 
int father(int x)
{
	if(fat[x]!=x)fat[x]=father(fat[x]);
	return fat[x];
}
void unionn(int x,int y)
{
	int fa=father(x);
	int fb=father(y);
	if(fa!=fb)fat[fa]=fb;
}
int cmp(const point&a,const point &b) //sort函数中的自定义的比较函数 
{
	if(a.v<b.v)return 1;
	else return 0;
}
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	{
		cin>>x;
		if(x!=0)
		{
			m++;
			a[m].x=i;
			a[m].y=j;
			a[m].v=x;
		}
	}
	for(i=1;i<=n;i++)fat[i]=i;
	sort(a+1,a+m+1,cmp);//C++标准库中自带的快排
	                    //cmp为自定义的比较函数，这个表示a数组中的1-m按顺序来cmp比较排序 
	for(i=1;i<=m;i++)
	{
		if(father(a[i].x)!=father(a[i].y))
		{
			unionn(a[i].x,a[i].y);
			tot+=a[i].v;
			k++;
		}
		if(k==n-1)break;
	}
	cout<<tot;
	return 0;
}
```


------------
下面为克鲁斯算法的套路，大家可以学习一下。（~~虽然我也不太会~~）

1.首先初始化并查集：father[x]=x；

2.tot=0赋初值为0给tot

3.将所有边用快排从小到大排序。

4.计数器 k=0;

5.
```cpp
for (i=1; i<=M; i++)      //循环所有已从小到大排序的边
  if  这是一条u,v不属于同一集合的边(u,v)(因为已经排序，所以必为最小)，
    begin
    　①合并u,v所在的集合，相当于把边(u,v)加入最小生成树。
　    ②tot=tot+W(u,v)
      ③k++
      ④如果k=n-1,说明最小生成树已经生成，则break; 
    end;

```
6. 结束，tot即为最小生成树的总权值之和。


------------
这就是整道题的全部过程了，还有包括克鲁斯卡尔的套路，希望大家能喜欢，如果有错误或者问题的话可以告诉蒟蒻，蒟蒻尽量去纠正。蟹蟹٩('ω')و

祝大家能早日ac这道题

![](https://www.luogu.org/images/congratulation.png)و


---

## 作者：Celebrate (赞：8)

这一道题我用了并查集来做，这样是最优解

其实这一题也可以用最短路来做，但是做起来很麻烦，还需要判断是否走过所有的点，时间复杂度和思维复杂度都会比较高，也很容易出现错误

因为要跑所有的点，所以先把每一条边的长度排一次序，然后逐个找，如果两个点不属于同一个集合，就把它们合并成一个集合，原理就不说了

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y,d;
}a[21000];int len;//记录边 
int n,t;
int fa[21000];//fa[x]表示点x的父亲是谁 
int find_zuxian(int x)//找祖先 
{
	if(fa[x]==x) return x;//如果找到了祖先节点，就直接返回 
	else		 return find_zuxian(fa[x]);//不然就继续往下找 
}
inline int cmp(const void *xx,const void *yy)//排序 
{
	node x=*(node*)xx;
	node y=*(node*)yy;
	if(x.d<y.d) return -1;
	if(x.d>y.d) return 1;
	return 0;
}
int main()
{
	int i,j,t;
	scanf("%d",&n);//输入 
	for(i=1;i<=n;i++)
	{
		fa[i]=i;//一开始自己就是自己的祖先 
		for(j=1;j<=n;j++)
		{
			scanf("%d",&t);//输入 
			if(j>i)//如果之前没有出现过，就建立一条新的边 
			{
				len++;//因为这个不是最短路，建双向边是多余的，而且会出错 
				a[len].x=i;a[len].y=j;a[len].d=t;
			}
		}
	}
	qsort(a+1,len,sizeof(node),cmp);//长度从小到大排序 
	int s=1,ans=0;//s表示当前找到的点，ans表示边的长度 
	for(i=1;i<=len;i++)//逐个搜索 
	{
		int tx=find_zuxian(a[i].x);
		int ty=find_zuxian(a[i].y);
		if(tx!=ty)//如果两个点的祖先不同的话 
		{
			ans=ans+a[i].d;//就用这一条边 
			fa[ty]=tx;//并且合并两个点 
			s++;if(s==n) break;//如果找到了n个点，就直接退出搜索 
		}
	}
	printf("%d\n",ans);//输出 
	return 0;
}
```

---

## 作者：The_Dark_Knight (赞：5)

此题为典型的求最小生成树问题，Prim算法最佳，但是Kruskal算法同样适用，在这里提供Kruskal算法求最小生成树的pascal代码，运用并查集判断是否形成回路

```delphi

type node=record//边的记录
     v1,v2,s:longint;//v1，v2为边所连接的两点，s为农场间的距离，即光纤长度
     end;
var i,j,n,ans,p,k:longint;a:array[1..10000] of node;//把边以数组形式存储在a数组中
    f:array[1..10000] of longint;//父结点数组
function gf(x:longint):longint;//求根节点的过程
begin
    if f[x]=x then exit(x);
    f[x]:=gf(f[x]);
    exit(f[x]);
end;
procedure union(a,b:longint);//合并两集合的过程
begin
    if gf(a)<>gf(b) then f[gf(a)]:=gf(b);
end;
procedure sort(l,r: longint);//快排过程
      var
         i,j,x: longint;y:node;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2].s;
         repeat
           while a[i].s<x do
            inc(i);
           while x<a[j].s do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
begin
    readln(n);//读入农场数
    for i:=1 to n do//因为读入数据以邻接矩阵的形式读入，所以在使用Kruskal算法时要注意转换成边集数组形式
      for j:=1 to n do
      begin
          inc(k);//k为边的数组下标
          a[k].v1:=i;//i，j分别为边连通的两点，记入到记录里
          a[k].v2:=j;
          read(p);
          a[k].s:=p;//存储此边的长度
      end;
      for i:=1 to n do
        f[i]:=i;//初始化各结点的集合，形成不同的集合
      sort(1,k);//把边按照长度排序
      i:=1;//i为要求的第i条边
      j:=1;//j为边的数组下标
      while i<=n-1 do
      begin
          if (gf(a[j].v1)<>gf(a[j].v2))and(a[j].s<>0) then//因为读入数据中，当两结点相同时会出现长度为0的情况，所以判断是否保留边时要排除，如果此边连接的两结点不在同一集合内则保留此边
          begin
              inc(i);//i后移
              ans:=ans+a[j].s;//更新光纤总长度
              union(a[j].v1,a[j].v2);//合并连接的两结点
          end;
          inc(j);//探究下一条边
      end;
      writeln(ans);//输出结果
end.

```

---

## 作者：ACgod (赞：4)

蒟蒻的题解，望通过，谢谢

------------


这题其实就是一题裸的最小生成树，我用的是克鲁斯卡尔算法（Kruskal），
其实也可以用普里姆算法（Prim），~~但我貌似更喜欢K...~~

（~~以上是废话~~）

克鲁斯卡尔算法需要先把边排个序，然后到并查集来判断每两个结点是否在同一个集合中，如果不是，就用最短的边把他们连接起来，由于有n个结点，所以会有n-1条边，我们只要找到n-1条边就OK了。

下面讲如何实现：

首先我使用了一个结构体Edge来存储每条边的信息，详情见注释
```cpp
struct Edge
{
    int u,v,w;//u,v代表这个边的两端的结点，w代表权值
}e[10001];
```

并查集，在这里就不多废话了，不会的童鞋自己上网找度娘，直接看代码：
```cpp
int getf(int v)
{
    if(f[v]==v)
    {
      return v;//当自己的祖先就是自己时（感觉很搞笑），就结束了
    }
    else{
        f[v]=getf(f[v]);//路径压缩，减短找父亲的时间
        return f[v];
    }
}
```
下面这个函数是用来判断二者是否在同一个集合中的（就是是否有共同的祖先）
```cpp
int merge(int v,int u)
{
    int t1,t2;
    t1=getf(v);
    t2=getf(u);
    if(t1!=t2)//如果不在一个集合，他们就可以连起来
    {
      f[t2]=t1;//t2的父亲是t1;
      return 1;//可以执行
    }
    return 0;//反之不能
}
```
核心的函数在上面都解释过了，下面上代码（为了您的名字颜色不变，请不要Ctrl+c+Ctrl+v哦）
```cpp
#include <iostream>
#include <algorithm>//使用sort快排需要用到哦（表示不喜欢用万能头文件）
using namespace std;
struct Edge
{
    int u,v,w;
}e[10001];//已解释
int n,m;
int f[10001];
int getf(int v)
{
    if(f[v]==v)
    {
      return v;
    }
    else{
        f[v]=getf(f[v]);
        return f[v];
    }
}//已解释
int merge(int v,int u)
{
    int t1,t2;
    t1=getf(v);
    t2=getf(u);
    if(t1!=t2)
    {
      f[t2]=t1;
      return 1;
    }
    return 0;
}
int cmp(Edge xx,Edge yy)//排序时需要
{
    return xx.w<yy.w;//从小到大排
}
int main()
{
    cin>>n;
    int p=0;
    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=n;j++)
      {
        p++;
        e[p].u=i;
        e[p].v=j;
        cin>>e[p].w;//输入
        if(i==j)
        {
          e[p].w=2147483647;//本身不能到达本身，所以当两个结点相同时，把它设为正无穷
        }
      }
    }
    sort(e+1,e+p+1,cmp);//从小到大排序
    for(int i=1;i<=n;i++)
    {
      f[i]=i;//并查集初始化，一开始每个人的祖先都是自己
    }
    int cnt=0,sum=0;//sum统计答案，cnt统计已经选的边的条数
    for(int i=1;;i++)
    {
      if(merge(e[i].u,e[i].v))//判断是否在同一个集合中
      {
        cnt++;//边数+1
        sum+=e[i].w;//答案
      }
      if(cnt==n-1)//当已经有n-1条边时，退出循环
      {
       break;	
      }
    }
    while(true);//防抄袭
    cout<<sum<<endl;
}
```
谢谢大家！

---

## 作者：dl__hh6 (赞：3)

~~pascal来一发~~

以我的大蒟蒻来看，这题目是一题很经典的图论中的最小生成树！！

我的做法是prim的算法；

题意是：包含连接到每个农场的光纤的最小长度。

所以很符合我们的**prim**算法；

**详见代码注释**：

```pascal
var 
    a:array[1..100,1..100]of longint;//两个村庄之间路程多远
    dis:array[1..100]of longint;//每次更新的到目前所有点的最短距离
    used:array[1..100]of boolean;//有没有连上
    i,j,n,ans,k,sum:longint;
begin
  read(n);
  for i:=1 to n do dis[i]:=maxlongint;//初始成无穷大
  for i:=1 to n do
   for j:=1 to n do
    read(a[i,j]);//输入任意两个村庄之间的距离
  for i:=2 to n do dis[i]:=a[1,i];//从第一个村庄开始连，初始每个村庄和第一村庄之间的距离
  used[1]:=true;//第一个已联通
  for i:=2 to n do
   begin
    ans:=maxlongint;//初始成最大
    for j:=1 to n do
     if not(used[j])and(dis[j]<ans) then//判断没有在已联通村庄中
      begin  ans:=dis[j];k:=j;end;//求和已联通的村庄中任何一个联通最短的村庄
    sum:=sum+dis[k];//计算目前的总电缆长度
    used[k]:=true;//标记已联通
    for j:=1 to n do
     if not(used[j])and(dis[j]>a[k,j]) then//判断没有联通
      dis[j]:=a[k,j];//更新和目前联通村庄中任何一个的最短距离
   end;
   writeln(sum);
end.
```
~~偶自己认为我的代码还算短~~

---

## 作者：soy_un_perro (赞：2)

看到大家用的都是Kruskal，我发一篇Prim的吧。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[101][101];
int dist[101],u[101],v[101],p,sum=0;
//u表示已进入最小生成树的节点，v表示未进入最小生成树的节点。u[i]=1:i节点已进入最小生成树。
int main()
{
	cin>>n;
	memset(dist,0x7f,sizeof(dist));
	for(int i=1;i<=n;i++)//读入
	{
		v[i]=1;//初始所有节点都未进入最小生成树
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	}
	p=1;
	for(int j=1;j<=n-1;j++)
	{
		v[p]=0;
		u[p]=1;//把p放入最小生成树
        //Prim算法，不解释了
		for(int i=1;i<=n;i++)
			dist[i]=min(a[p][i],dist[i]);
		int minn=10000000,minp;
		for(int i=1;i<=n;i++)
		{
			if (!u[i] && dist[i]<minn)
			{
				minn=dist[i];
				minp=i;
			}
		}
		sum+=minn;
		p=minp;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：tangjerry (赞：1)

# 克鲁斯卡尔
##  题目背景
农民约翰被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。

## 题目描述
约翰已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了用最小的消费，他想铺设最短的光纤去连接所有的农场。

你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤最短的方案。每两个农场间的距离不会超过100000

## 输入格式
第一行： 农场的个数，N（3<=N<=100）。

第二行..结尾: 后来的行包含了一个N*N的矩阵,表示每个农场之间的距离。理论上，他们是N行，每行由N个用空格分隔的数组成，实际上，他们限制在80个字符，因此，某些行会紧接着另一些行。当然，对角线将会是0，因为不会有线路从第i个农场到它本身。

输出格式
只有一个输出，其中包含连接到每个农场的光纤的最小长度。
### 样例
输入 

4

0 4 9 21

4 0 8 17

9 8 0 16

21 17 16 0

输出
28
# 讲解
## 第一步：存图
  从样例可以看出输入是一个二维数组，所以关键是把二位数组转换为已边的形式存储的结构体。
  先上存图的代码：
  ```cpp
   for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>a;
            if(a!=0&&i<j)//存图策略。
            {
                q[m].u=i;
                q[m].v=j;
                q[m].w=a;
                m++;
            }
        }
```

	m类似与一个指针，给结构体存储用的。
    存图的代码关键句为if(a!=0&&i<j)，这样就可以很好的存储边的关系与权值了
## 第二步：排序
  由于是用结构体存储边，所以我们用sort排序的时候要专门写一个cmp的bool函数比较，代码如下：
  ```cpp
bool cm_p(que a,que b)
{
    return a.w<b.w;
}
                    
sort(q,q+m,cm_p);//一定要加上头文件algorithm
```
  最小生成树当然是将边从小到大排序啦。
  这里有一点需要注意，c++用到sort排序时须要加上头文件：
  ```cpp
#include <algorithm>
```
## 第三步，从小到大枚举每一条边，通过并查集判断
首先并查集代码如下：
```cpp
int getf(int x)
{
    if(f[x]==x) return x;//如果他的父亲就是他自己，直接返回x 
    else
    {
        f[x]=getf(f[x]);//路径压缩，把他的祖宗也带上 
        return f[x];
    }
}
bool hebing(int a,int b)
{
    int t1,t2;
    t1=getf(a);//分别寻找两个节点的父亲 
    t2=getf(b);
    if(t1!=t2)//如果两个节点父亲不同，表明需要合并 
    {
        f[t2]=t1;//靠右原则 
        return true;
    }
    return false;
}
```
关于并查集的具体讲解见我的另一个博客文章：
[并查集](https://www.luogu.org/blog/tangjerryprogram/solution-p3366)
# 完整代码：
```cpp

#include <iostream>
#include <algorithm>//用到了sort一定要加上的 

using namespace std;
struct que
{
    int u;
    int v;
    int w;
}q[10005];//通过结构体来存边 
int f[305];//父亲数组，f[i]表示i的父亲为f[i] 
int ans,countt;
int a,n,m;
bool cm_p(que a,que b)
{
    return a.w<b.w;
}
int getf(int x)
{
    if(f[x]==x) return x;//如果他的父亲就是他自己，直接返回x 
    else
    {
        f[x]=getf(f[x]);//路径压缩，把他的祖宗也带上 
        return f[x];
    }
}
bool hebing(int a,int b)
{
    int t1,t2;
    t1=getf(a);//分别寻找两个节点的父亲 
    t2=getf(b);
    if(t1!=t2)//如果两个节点父亲不同，表明需要合并 
    {
        f[t2]=t1;//靠右原则 
        return true;
    }
    return false;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>a;
            if(a!=0&&i<j)//存边规则 
            {
                q[m].u=i;
                q[m].v=j;
                q[m].w=a;
                m++;
            }
        }
    sort(q,q+m,cm_p);//排序，需要自己写cmp 
    for(int i=0;i<m;i++)
    {
        if(hebing(q[i].u,q[i].v))
        {
            ans+=q[i].w;//计算最后最小生成树的权值和 
            countt++;//计数 
        }
        if(countt==n-1) break;//树的节点个数是他边的n+1 
    }
    cout<<ans;
    return 0;
}
```

## 总结
  之前也写过几篇题解，但是通过的很少，所以诚心希望管理员大大能通过。
  我在代码里加入了详细的注释，希望可以帮到大家，欢迎来我的博客逛：
  https://www.luogu.org/blog/tangjerryprogram/
  如果有问题也可以加我的qq：2332596092
##   完美结束



---

## 作者：王鹏PRO (赞：1)

没有Java的题解，来一发希望可以过审
---

“最短网络”求-->**连接到每个农场的光纤的最小长度**

首先分析一下题目：
1. 把题目中的描述，想象成图-->无向图-->有权无向图
2. 图中连接各个节点所需最短路径长度和-->MST,最小生成树
3. MST的经典算法 _**Kruskal算法**_ 和 _**Prim算法**_ 
4. 本人喜欢Kruskal算法，该算法关键点是取N-1条边，可以连通图中的N个点
5. 考察图的连通性就要使用并查集Union-Find
6. 图模型，Kruskal算法进行MST，只考虑边和边的权值，所以只是用int[][]就够了

---
然后 解释一下代码中关键点：
1. IO部分, 通常情况下使用StreamTokenizer 性能更高一些

```java
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
```

2. 图的表示，使用int[N][3] 存储测试数据中邻接矩阵中的边，由于是无向图
所以邻接矩阵的数据是轴对称的，我们只需处理上三角或者下三角
int[i][0]\int[i][1] 存储边的两个端点
int[i][2] 存储边的权值

```java
	int[][] edges = new int[cnt][3];
	int index = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                in.nextToken();
                if (i == j) continue;//对角线不处理
                if (i > j) continue;//放弃下三角数据
                edges[index][0] = i;
                edges[index][1] = j;
                edges[index][2] = (int) in.nval;
                index++;
            }
        }
```
3. Kruskal算法要求将边按照从小到大进行排序，MergerSort稳定的排序算法
使用Comparator进行排序，在JDK8的环境下比使用lambda效率要高。

```java
        //强制使用MergerSort 进行排序
        System.setProperty("java.util.Arrays.useLegacyMergeSort", "true");
        Arrays.sort(edges, 0, index, new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                return o1[2] - o2[2];
            }
        });
```

4. 并查集算法，这里使用简单并查集，所谓“简单”是指Union时，使用了简单的合并原则,不考察路径压缩的成本问题

```java
    private static int find(int c, int[] p) {
        if (p[c] == c) return c;
        return p[c] = find(p[c], p);
    }

    static boolean union(int c1, int c2, int[] p) {
        int p1 = find(c1, p);
        int p2 = find(c2, p);
        if (p1 == p2) return false;
        //简单的合并原则
        if (p1 < p2) p[p2] = p1;
        else p[p1] = p2;
        return true;
    }
```
5.  Kruskal算法的核心代码， cnt记录已经选择边的个数，sum选择边的权值和，union成功（true）意味选择了当前边。


```java
	for (int i = 0; i < index && cnt < N - 1; i++) {
            if (union(edges[i][1], edges[i][0], p)) {
                cnt++;
                sum += edges[i][2];
            }
        }
```


---
完整代码
```java

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Arrays;
import java.util.Comparator;

public class Main {
    public static void main(String[] args) throws Exception {
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        in.nextToken();
        int N = (int) in.nval;
        int cnt = (N * N) >> 1;
        int[][] edges = new int[cnt][3];
        int index = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                in.nextToken();
                if (i == j) continue;
                if (i > j) continue;
                edges[index][0] = i;
                edges[index][1] = j;
                edges[index][2] = (int) in.nval;
                index++;
            }
        }
        System.setProperty("java.util.Arrays.useLegacyMergeSort", "true");
        Arrays.sort(edges, 0, index, new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                return o1[2] - o2[2];
            }
        });

        int[] p = new int[N + 1];
        for (int i = 1; i <= N; i++) p[i] = i;
        int sum = 0;
        cnt = 0;
        for (int i = 0; i < index && cnt < N - 1; i++) {
            if (union(edges[i][1], edges[i][0], p)) {
                cnt++;
                sum += edges[i][2];
            }
        }
        System.out.println(sum);

    }

    private static int find(int c, int[] p) {
        if (p[c] == c) return c;
        return p[c] = find(p[c], p);
    }

    static boolean union(int c1, int c2, int[] p) {
        int p1 = find(c1, p);
        int p2 = find(c2, p);
        if (p1 == p2) return false;
        if (p1 < p2) p[p2] = p1;
        else p[p1] = p2;
        return true;
    }
}

```


---

## 作者：QQ3111822945 (赞：1)

非常典型的kruskal算法！！！（相信大佬们都会做———O(∩\_∩)O~）

其实这道题很简单，最小生成树！

首先应先输入数据--按照题意输入就可。。（不相信你不会。。）

其次，father数组初始化（相信你会初始化。。）

接着，进行比较长度的大小，当然，我用的结构体（结构体什么东西？），大佬们也可以用很复杂的数组，当然弱弱的我认为开结构体更方便。

然后，就进入主程序了，集合外的进行连接，集合内的舍去，设一计数变量，达到点的 次数-1（即边数）退出循环

最后输出结果就可！！！

相信大佬们一定会做会优化！！！

    
        
    
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
namespace std;
int n,fa[100001],tot,m,x,k;
struct po                                    //¶¨ÒåµÄ½á¹¹Ìå 
{
    int s; int w; int j;
}a[100001];
int cmp(const po &aa,const po &bb)              //Ê®·ÖÖØÒªµÄ½á¹¹Ìå±È½ÏÄ£°å£¡£¡£¡ 
{
    if(aa.j<bb.j) return 1;
    else return 0;
}
int fat(int x)                              //ÅÐ¶ÏÄ£°å 
{
    if(fa[x]!=x) fa[x]=fat(fa[x]);
    return fa[x];
}
int main()
{
    freopen("7.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      {
          cin>>x;
          if(x!=0)
          {
              m++;
              a[m].s=i; a[m].w=j; a[m].j=x;
          }
      }
    for(int i=1;i<=n;i++)
     fa[i]=i;                                  // ³õÊ¼»¯fatherÊý×é 
    sort(a+1,a+m+1,cmp);                       //³¤¶È½øÐÐ±È½Ï 
    for(int i=1;i<=m;i++)                      //µÚ¼¸¸öÊý 
    {
        int faa=fat(a[i].s);                     
        int fab=fat(a[i].w);
        if(faa!=fab)                            //ÊÇ·ñÒÑ¾­½øÈë¼¯ºÏ 
        {
        fa[faa]=fab;                            //¼ÆÈë¼¯ºÏ£¨½øÈëÒ»±é¼´¿É£© 
        tot+=a[i].j;                           //×î¶Ì³¤¶È½øÐÐÏà¼Ó 
        k++;                                    //¼ÆÊýº¯Êý½øÐÐÏà¼Ó 
        }
        if(k==n-1) break;    
    }
    cout<<tot<<endl;
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：1)

prim
```cpp

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

int g[310][310];
bool pd[310]={false};//0 is false;
int Min[310];
int Mst=0;
int main()
{
    int n,m;
    cin>>n;
    for(int i=0;i<=300;i++)//将邻接矩阵赋初值 
      for(int j=1;j<=300;j++)
        g[i][j]=2000000000;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        scanf("%d",&g[i][j]);
    for(int i=1;i<=309;i++)//最小权值数组赋初值 
      Min[i]=g[1][i];
    pd[1]=1;
    for(int i=1;i<n;i++)
      {
        int j;
        int zuixiao=2000000000;
        int zui;//zui存最小值的 
        for(j=1;j<=n;j++)//擂台比较找最小的
          {
            if(pd[j]==0)
              if(zuixiao>Min[j])
                {zuixiao=Min[j];zui=j;}
          }
        pd[zui]=1;//标记
        Mst+=zuixiao;
        for(int k=1;k<=n;k++)//更新
          {
            if(g[zui][k]<Min[k]&&pd[k]==0)
              Min[k]=g[zui][k];
          }

      }
      cout<<Mst; 
} 

```

---

## 作者：SiTer (赞：1)

```cpp

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int N,vset[1000],tcnt,cnt,sum;
struct Node{int x,y,cost;}edge[100100];
bool cmp(Node x,Node y){return x.cost<y.cost;}
int find(int x){return x==vset[x] ? x : vset[x]=find(vset[x]);} 
int judge(int x,int y){if(find(x)!=find(y)){vset[find(y)]=find(x);return 1;}return 0;}
void init()//将矩阵数据转换为边集（虽然会有重复边比如1-2和2-1但是这俩并查集祖先一样所以没事，而且并查集有路径压缩所以就算判断也不会耗费多少时间）
{
    cin>>N;
    int temp;
    for(int i=1;i<=N;i++)
        for(int k=1;k<=N;k++)
        {
            cin>>temp;
            if(temp)
            {edge[++tcnt].cost=temp; edge[tcnt].x=i;   edge[tcnt].y=k;}
        }
    sort(edge+1,edge+tcnt+1,cmp);
    for(int i=1;i<=N;i++)
        vset[i]=i;
}
int main()
{
    init();
    for(int i=1;i<=tcnt;i++)//kruskal模板直接套用
    {
        if(judge(edge[i].x,edge[i].y))
        {
            cnt++;sum+=edge[i].cost;
        }
        if(cnt==N-1)
            break;
    }
    cout<<sum;
    return 0;
}

```

---

## 作者：sqc1999 (赞：1)

不用解释什么了吧，最小生成树的模板题。

给出Kruskal的代码

```cpp

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
int n;
struct Edge
{
    int U, V, W;
    Edge(int u, int v, int w) :U(u), V(v), W(w){}
};
vector<Edge> Edges;
bool cmp(const int& a, const int& b)
{
    return Edges[a].W < Edges[b].W;
}
int p[10000], r[10000];
int find(int x)
{
    return p[x] == x ? x : p[x] = find(p[x]);
}
int Kruskal()
{
    int ans = 0, m = Edges.size();
    for (int i = 0; i < n; i++) p[i] = i;
    for (int i = 0; i < m; i++) r[i] = i;
    sort(r, r + m, cmp);
    for (int i = 0; i < m; i++)
    {
        int e = r[i], x = find(Edges[e].U), y = find(Edges[e].V);
        if (x != y)
        {
            ans += Edges[e].W;
            p[x] = y;
        }
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            if (j < i)
            {
                Edges.push_back(Edge(i, j, x));
            }
        }
    }
    cout << Kruskal();
}

```

---

## 作者：USER113968 (赞：0)

首先，我们看看题目。想一想其实很简单。这不就是**图的最小生成树**吗？
然后以邻接矩阵的形式读入每一条边。
那图的最小生成树是个啥？其实就是一个只留下最短的n-1条边的图。为什么只有n-1条边呢？你想，一棵树有n个顶点，肯定只有n-1条边啊！


------------

# 算法分析
那怎么求图的最小生成树呢？我这里用大名鼎鼎的Kruskal算法。
**算法步骤如下**
step1:读入所有边，存到一个结构体数组中。

step2:把他们按照边长排序

step3:看一看这条边连接的两点（无向图）是否已经联通，如果不是，那么选用这条边，tot++，将这两个点设为已联通。

step4:重复执行step3，直到选择了n-1条边，或无边可选。

这个算法中，比较难的一点是**如何判断两点已经联通**，这个我们可以用并查集来实现。每次判断两个点的祖先是否相同，如果不相同，那么就选用这条边并且合并两个点。没有学过并查集的童鞋，自己去百度一下吧！

接下来，上代码！
```cpp
#include<iostream>//适用于无向图 
#include<algorithm>
#include<stdio.h>
using namespace std;
class UFS//我把并查集，写成了一个class
{
    public:
	int f[1001];
    UFS()
    {
        init(1000);
    }
    void init(int n)
    {
        for (int i = 0;i <=n;++i)
        {
            f[i] = i;
        }
    }
    int find(int x)
    {
        if(f[x]==x)
        	return x;
		f[x]=find(f[x]);
		return f[x];
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) return;
        f[x]=y;
    }
    bool same(int x, int y)
    {
        return (find(x)==find(y));
    }
};
struct Edge
{
	int from,to,len;	
};
bool cmp(Edge a,Edge b)
{
	return a.len<b.len;
}
Edge edge[100*100+1];//用于存储边的结构体数组
int num=0;
int n;
int ans=0;
int tot=0;
UFS ufs;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			int l;
			cin>>l;
			if(i==j)//自己接到自己的边就不算了
				continue;
			num++;
			edge[num].from=i;
			edge[num].to=j;
			edge[num].len=l;
		}
	sort(edge+1,edge+num,cmp);//按照边长排序
	for(int i=1;i<=num;i++);//Kruskal算法的step3部分
	{
		if(tot==n-1)
			break;
		if(ufs.same(edge[i].from,edge[i].to))//已联通的边不选
			continue;
		ans+=edge[i].len;
		ufs.merge(edge[i].from,edge[i].to);//合并两个点
		tot++;
	}
	cout<<ans;//输出解答
	return 0;
}
```

**亲测能AC，不过，请不要抄袭。如果你们执意要copy我的代码，我给你们留了个惊喜哟！**

题解到此为止，拜拜！


---

## 作者：zhaowangji (赞：0)

最小生成树，用kruskal法（要用并查集）

实在没力气再把两个算法很详细的说一遍了，如果第一次涉及，可以先看下一本通或者[我之前写的题解](https://zhaoqi.blog.luogu.org/solution-p2820)

基本是裸的最小生成树

读入每条边然后排序，依次枚举

如果两点没有在同一个集合里，就合并，答案加上这条边的边权，边数加一，当边数等于n-1（如果更小不可能把每个点都连接）时退出循环

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n;
struct node{
	int a,b;
	int jl;
}dis[10007];//保存边
int fa[107];//并查集，保存祖先
int ans;//答案
int bs;//边数
int fi(int x){
	if(fa[x]!=x)fa[x]=fi(fa[x]);
	return fa[x];//找祖先
}
void hb(int x,int y){
	fa[x]=y;
	return;//合并
}
bool cmp(node x,node y){
	return x.jl<y.jl;//按边权排序
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
    		//这里读入要注意下，第x条边可以表示为第（i-1）*n+j条边
		dis[(i-1)*n+j].a=i;
		dis[(i-1)*n+j].b=j;
		cin>>dis[(i-1)*n+j].jl;
		if(dis[(i-1)*n+j].jl==0)dis[i].jl=0x3f3f3f3f;//不然就会排在前面，到时候判断也行
	}
	for(int i=1;i<=n;i++)
	fa[i]=i;//先把祖先改成每个人自己
	sort(dis+1,dis+n*n-n+1,cmp);//排序
	for(int i=1;i<=n*n-n;i++){
		int x=dis[i].a;
		int y=dis[i].b;//为写代码方便
		if(fi(x)!=fi(y)){//不在同一集合
			hb(fi(x),fi(y));//合并
			bs++;//边数加一
			ans+=dis[i].jl;//加上边权
		}
		if(bs==n-1)break;//已全部连接
	}
	cout<<ans<<endl;//输出
	return 0;
}
```


---

## 作者：Hexarhy (赞：0)

### 最近蒟蒻学了最小生成树算法， 写篇题解巩固一下。

老规矩，简单分析一下题目。


------------

首先，判断是最短路还是最小生成树。由于要使**每个点相互连通**，因此是最小生成树。这道题大家一看便知道是比较裸的了。

因为是稠密图，且$n$很小，用什么方法都可以过。这里我推荐$Prim$加堆优化，时间复杂度$O(nlogn)$。

当然$Kruskal$+路径压缩也可以，哪种简单就选哪种（个人感觉$Prim$更简单）。


------------

那么怎么用$Prim$怎么找呢？

$1)$ 有点像$SPFA$，从起点开始，把每一个点都遍历一遍，使图连通，同时利用堆选出最佳方案。

$2)$ $visit$数组标记这个点遍历过没有，我们只需要一次就能找到最优。

$3)$重载堆的方法就不说了，大家自行百度吧。

$4)$因为数据小，建图方法随便，这里我用$vector$实现邻接链表。

------------
参考程序如下，请见注释：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int MAXN=105;
int n,ans;
struct node
{
	int to,v;
};
vector <node> edge[MAXN];
bool visit[MAXN];

struct cmp//重载为小根堆，注意语法
{
	bool operator()(const node& x,const node& y)const
	{//注意重载的是()运算符；而在结构体内重载是<运算符
		return x.v>y.v;
	}
};

void input(void)
{
	cin>>n;
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=n;j++)
	{
		int x;
		cin>>x;
		if(x)//按题目要求建无向图
		{
			edge[i].push_back((node){j,x});	
			edge[j].push_back((node){i,x});	
		}
	}
}

void prim(void)
{
	priority_queue <node,vector<node>,cmp> q;
	visit[1]=true;//从第一个点开始，为起点
	for(vector<node>::iterator it=edge[1].begin();it!=edge[1].end();it++)
	 q.push(*it);//把第一个点相关的点进堆，之后好拿出来用
	while(!q.empty())//开始遍历
	{
		const node tmp=q.top();
		q.pop();
		if(visit[tmp.to])//访问过就跳过
		 continue;
		visit[tmp.to]=true;
		ans+=tmp.v;//别忘了存储答案
		for(vector<node>::iterator it=edge[tmp.to].begin();it!=edge[tmp.to].end();it++)
		 if(!visit[it->to])
		  q.push(*it);//再次进堆
	}
}

int main()
{
	input();
	prim();
	cout<<ans;
	return 0;
}
```

---

## 作者：MambaHJ (赞：0)

最小生成树的模板题，概念部分可以参考这篇[博客](https://www.jianshu.com/p/efcd21494dff)，~~讲的很清楚详细~~，很多图例，入门很友好。

本文主要采用kruskal算法（前置知识：并查集），根据紫书实现模板。

## 变量定义
该结构体存图u，v是节点，w是权值 

```
struct Edge{
	int u, v, w;
}edge[maxn];
```

并查集模板

```
struct union_find{
	int fa[maxn];

	void init(int n){
		for (int i = 0; i < n; ++i)
			fa[i] = i;
	} 

	int find(int u){
		return u == fa[u] ? fa[u] : fa[u] = find(fa[u]);
	}

}solve;

```

## 算法实现

**kruskal算法的伪代码：**

```
1. 将图的所有边从小到大排序，记第 i 小的边为edge[i]
2. 初始化MST（Minimum spanning tree）为空
3. 初始化连通分量，让每个点自成一个独立的连通分量
4. for(int i = 0; i < m; ++i)
		if(edge[i].v 和 edge[i].u 不在一个连通分量中)
        	把边加入MST;
            合并edge[i].v 和 edge[i].u所在的连通分量
```

实现：
```
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 10010;

int n, tot;

struct Edge{
	int u, v, w;
}edge[maxn];

void add_edge(int u, int v, int w){
	edge[tot].u = u;
	edge[tot].v = v;
	edge[tot++].w = w;
}

bool cmp(Edge &a, Edge &b){
	return a.w < b.w;
}

struct union_find{
	int fa[maxn];

	void init(int n){
		for (int i = 0; i < n; ++i)
			fa[i] = i;
	} 

	int find(int u){
		return u == fa[u] ? fa[u] : fa[u] = find(fa[u]);
	}

}solve;

int kruskal(){
	int ans = 0;
	solve.init(maxn);
	sort(edge, edge + tot, cmp);
	for (int i = 0; i < tot; ++i){
		int x = solve.find(edge[i].u);
		int y = solve.find(edge[i].v);
		if (x != y){
			solve.fa[x] = y;
			ans += edge[i].w;
		}
	}
	return ans;
}

int main(int argc, char const *argv[]){
	cin>>n;
	int weight;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			cin>>weight;
			if (weight)
				add_edge(i, j, weight);
		}
	}
	cout<<kruskal()<<endl;
	return 0;
}
```

---

## 作者：LostSummer (赞：0)

看大佬们都用的Kruskal，就试着拿prim算法写了一下，发现两个过了并且我的prim还快一点点(可能是我Kruskal没优化之类的吧)
不多说直接上代码吧
```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f
using namespace std;
int n,a[110][110],d[110],minn,ans,t;
bool b[110];//集合内部有哪些点 
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			scanf("%d",&a[i][j]);
	for(int i=1; i<=n; i++)d[i]=inf;//初始化 
	d[1]=0;
	for(int i=1; i<=n; i++) {
		minn=inf;
		for(int j=1; j<=n; j++)if(!b[j]&&d[j]<minn) {//找到距离集合最近的点 
				minn=d[j];
				t=j;
			}
		b[t]=1;
		ans+=minn;//将这个点放入集合内 
		for(int j=1; j<=n; j++)// 用这个点来更新 其他未在集合里的点 距离 集合的最短距离 
			if(a[t][j]<d[j])
				d[j]=a[t][j];
	}
	printf("%d",ans);
	return 0;
}
```
prim对于Kruskal的优点就是不怕边多具体请看
[P1265 公路修建](https://www.luogu.org/problemnew/show/P1265)
最短网络道题写完了可以再去看看公路维修，增强下对于prim的理解。



下面是我的Kruskal代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct QWE{
    int f,t,w;
}e[200010];
bool cmp(QWE x,QWE y){
    return x.w<y.w;
}
int n,m,f[5050],S,T,ans=0,sum;
int get_fa(int x){
    if(f[x]==x)return x;
    return f[x]=get_fa(f[x]);
}
void merge(int x,int y){
    x=get_fa(x);
    y=get_fa(y);
    if(x!=y)f[x]=y;
    }
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        e[++sum].f=i;
        e[sum].t=j;
        scanf("%d",&e[sum].w);
    }
    sort(e+1,e+sum+1,cmp);
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1;i<=sum;i++){
        S=get_fa(e[i].f);
        T=get_fa(e[i].t);
        if(S==T)continue;
        ans+=e[i].w;
        merge(e[i].f,e[i].t);	
    }
    printf("%d",ans);
    return 0;
}
```



---

## 作者：Rbrq (赞：0)

对于这道题，稍有常识的人都知道(逃是一道裸的最小生成树版题，那么就是运用到某K算法，下面简述一下。

首先定义一下生成树的概念，指的是对于一个有n个点的图，删去若干条边，使得整张图为一个只有n-1条边的联通块，而最小生成树则取生成树中的极小，既边权和为最小。

对于kruscal算法步骤如下

1.对于边的长度按照单调递增的要求排序

```cpp
const int Maxn = 10010;

struct st {
   int u, v, w;
} edge[Maxn]

inline int comp (const st & a, const st & b){
     return a.w < b.w ;
}

inline void kruscal () {
   sort(edge+1, edge+1+m, comp);
   .......
}
   
```

2.贪心地从小到大选取边。对于每一个边如果连接前该边两个端点已经联通，就不选择，否则将他们联通并将该边边权计入总和,一直到加入n-1条边。

```cpp
const int MAxn = 110;

int ans,fa[MAxn];

int find (int x) {

   return fa[x] == x?x:fa[x] = find(x);
   
   //路径压缩
   
}

inline void clear () {
    for (int i = 1; i < = n; ++i ) fa[i] = i;
    //初始化fa数组
    
}

inline void kruscal () {
     ......
     int cnt = 0;
     for(int i=1; i < = m; ++i){
         int uu = find (edge[i].u);
         int vv = find (edge[i].v);
         if(uu == vv) continue;
         ans += edge[i].w;
         fa[uu] = vv;
         if( ++cnt == n-1 ) break;
     }
}
```

最后输出这个总和就好了，以上就是k算法的简介。



------------


但是这道题如果就是完全的版题，那就没有存在的意义了，首先我们注意到存边时我们对于无向图只存边一次，如果将整个矩阵存图，那么无疑会导致错误，通过观察易得，对于右上角的矩阵来说，y都大于x，易得存图代码。

```cpp

int m = 0, val;

inline void add_edge ( int u, int v, int w ) {
      edge[++m].u = u;
      edge[m].v = v;
      edge[m].w = w;
}

int main(){
  scanf ( "%d", &n );
  for ( int i = 1; i <= n; ++i )
    for ( int j = 1; j <= n; ++j ) {
         scanf ( "%d", &val ) ;
         if ( j < i ) add_edge ( i, j, val ) ;
        }
```

最后附上本题完整ac代码以及ac用时

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=110;
const int MAxn=10010;
int n,val,cnt=0;
int tot=0,ans=0,fa[Maxn];
struct st{
	int u,v,w;
}edge[MAxn];
inline void add_edge(int u,int v,int w){
	edge[++cnt].u=u;
	edge[cnt].v=v;
	edge[cnt].w=w;
}
int comp(const st &a,const st &b){
	return a.w<b.w;
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
inline void kruscal(){
	sort(edge+1,edge+1+cnt,comp);
	for(int i=1;i<=cnt;++i){
	    int uu=find(edge[i].u);
	    int vv=find(edge[i].v);
	    if(uu==vv) continue;
	    ans+=edge[i].w;
	    fa[uu]=vv;
	    if(++tot==n-1) break;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1;i<=n;++i)
	  for(int j=1;j<=n;++j){
	  	scanf("%d",&val);
	  	if(j>i) add_edge(i,j,val);
	}
	kruscal();
	printf("%d",ans);
	return 0;
} 
```
![](http://wx4.sinaimg.cn/mw690/0060lm7Tly1fvm5i344mrj30kl07574f.jpg)

不要介意码分的转化，博主现在在变码分，见谅

最后，希望大家指出我博客错误，OI就是一个共同学习的过程



---

## 作者：jrqsjdpqlwnwhyn (赞：0)

这是一道基本的图论题，本蒟蒻不别的算法，就来一发用Prim吧。
以下是p党的福利。为现在还在写pascal的人加油！
不多说了，直接上代码！
```pascal
{题目概述：在N个农场之间建wifi，求光纤的最短长度｝
{方法：prim｝
var
u:array[1..100000]of boolean;
k:array[1..100000]of longint;
i,j,n,m,min,s,sum:longint;
a:array[1..1000,1..1000]of longint;
begin
readln(n);
for i:=1 to n do｛读入｝
 for j:=1 to n do
  read(a[i,j]);
  fillchar(u,sizeof(u),false);｛初值｝
 for i:=1 to n do
  k[i]:=a[1,i];
  u[1]:=true;
 for i:=1 to n-1 do｛找最短路｝
  begin
  min:=maxlongint;
   for j:=1to n do
    if not(u[j])and(k[j]<min) then begin s:=j;min:=k[j];end;｛判断｝
   u[s]:=true;sum:=sum+min;
   for j:=1 to n do
   if not(U[j])and(a[s,j]<k[j]) then k[j]:=a[s,j];｛更新｝
  end;
  writeln(sum);｛输出｝
  end.
```
本蒟蒻的第一篇题解，不喜欢勿喷，希望管理员通过。

---

## 作者：Туполев (赞：0)

# [原题](https://www.luogu.org/problemnew/show/P1546)
## 题目描述

农民约翰被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。

约翰已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了用最小的消费，他想铺设最短的光纤去连接所有的农场。

你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤最短的方案。每两个农场间的距离不会超过100000

## 输入输出格式
### 输入格式：
第一行： 农场的个数，N（3<=N<=100）。

第二行..结尾: 后来的行包含了一个N*N的矩阵,表示每个农场之间的距离。理论上，他们是N行，每行由N个用空格分隔的数组成，实际上，他们限制在80个字符，因此，某些行会紧接着另一些行。当然，对角线将会是0，因为不会有线路从第i个农场到它本身。

### 输出格式：
只有一个输出，其中包含连接到每个农场的光纤的最小长度。

------------

# 题解
首先~~点开算法标签~~审清题目，知道一个大概题意。可以看出是图论中的生成树（最小生成树），这道题的数据是比较适合使用Kruskal算法来解（其实Prim也可以）
 

### 思路：
直接用Kruskal。每次选择一条最小的且能合并两个不同的集合的边，总共选取N-1次边。因为我们每次选的都是最小的，所以最后必得一个最小生成树。又我们每次选的边都可以合并两个集合，所以最后N个点一定会合并成一个集合。其实原理与贪心还是很像的。

### 注意事项：
1. 看清样例，分析好题目和样例
1. 避开**TLE**，不要乱优化！！！
1. 注意Kruskal的实现过程
1. 其他详见标程注释 
## 标程
```cpp
#include<bits/stdc++.h>
using namespace std;
struct point{
	int x,y,v;
}a[9901];//定义结构类型，表示边 
int fat[101],n,i,j,x,m,tot,k;
int father(int x){
	if(fat[x]!=x) fat[x]=father(fat[x]);
	return fat[x];
}
void unionn(int x,int y){
	int fa=father(x),fb=father(y);
	if(fa!=fb) fat[fa]=fb;
}
bool cmp(const point &a,const point &b){//自定义比较函数 
	if(a.v<b.v) return 1;
	else return 0;
}
int main(){
	cin>>n;
	for(i=1;i<=n;i++) for(j=1;j<=n;j++){
		cin>>x;
		if(x!=0){
			m++;
			a[m].x=i;
			a[m].y=j;
			a[m].v=x;
		}
	}
	for(i=1;i<=n;i++) fat[i]=i;
	sort(a+1,a+m+1,cmp);//标准库中的快排
	//用cmp再定义后进行排序 
	for(i=1;i<=m;i++){
		if(father(a[i].x)!=father(a[i].y)){
			unionn(a[i].x,a[i].y);
			tot+=a[i].v;
			k++;
		}
		if(k==n-1) break;
	}
	cout<<tot;
	return 0;
}
```

---

## 作者：s66104444 (赞：0)

第一条题解

标准的库鲁斯考算法

就因为比较裸，所以才有勇气发。

值得提醒的是边开大点 我开30000才过，第一次开300-.-，始终不明白为何才60分。

就是边从小排序，然后一个个往里面加就ok。

并查集来维护的思想。<http://paste.ubuntu.com/25678622/>


---

## 作者：司徒stuart (赞：0)

裸的Kruskal板子 输入的时候记得要处理一下i=j的情况

还有就是要细心啊！！！

我之前居然一直弱智的以为在合并的时候 只要开一个vis数组记录一下 如果两个点都被vis过了就不用合并了

然后我弱智的交了 弱智的30 qaq

大家一定不要这么写啊 把代码和板子对比的时候一下反应过来 **就算两个点被vis过 也不能说明他们都被连接到同一个图里了！！**

总之大家没事写写板子还是有用的嗯。。。 不然比赛的时候弱智的错掉了就划不来了

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define MAXN 10010
using namespace std;
int n,father[MAXN],vis[MAXN];
struct Edge{//结构体 
    int from;
    int to;
    int w;
};Edge edge[MAXN];
bool cmp(Edge x,Edge y)
{
    return x.w<y.w;//一直看不懂大神写的重载运算符。。乖乖的自己写个cmp吧 
}
int find(int x)
{
    if(father[x]!=x) 
    {
        father[x]=find(father[x]);//路径压缩 
    }
    return father[x];
}
int onion(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx!=fy) father[fx]=fy;
}
int main()
{
    memset(vis,1,sizeof(vis));
    int a,cnt,ans=0,dd=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        father[i]=i;
        for(int j=1;j<=n;j++)
        {
            cin>>a;
            if(i==j)continue;//特判一下 
            edge[++cnt].w=a;
            edge[cnt].from=i;
            edge[cnt].to=j;
        }
    }
    sort(edge+1,edge+1+cnt,cmp);
    for(int i=1;i<=cnt;i++)
    {
        if(find(edge[i].from)!=find(edge[i].to))//万恶之源 
        {
            onion(edge[i].from,edge[i].to);
            ans+=edge[i].w;
        }
    }
    cout<<ans;
/*    for(int i=1;i<=cnt;i++)
    {
        cout<<edge[i].from<<" "<<edge[i].to<<" "<<edge[i].w<<endl;
    }*/
    return 0;
}
```

---

## 作者：陈新月 (赞：0)

思路：

其实没啥思路的，只是Kruskal算法的裸题，那就在这说一下kruskal算法

kruskal算法是基于这样一个推论：在一张图的最小生成树中，边长最小的边一定为生成树的一部分（有兴趣的Oier们可以自己去证明）

所以基于这样一个推论，我们就可以将所有边按边长进行排序，每次选择边长最小的并且是没有被选择过的边，因为在这我们要记录某条边是否被选择过，所以要用到并查集，每次选择一条未被选择的边后就将其边长加进答案，最后的答案就是最小生成树的长度


以下为代码，重要地方已经进行注释，如果有那个地方不是很理解可以给我留言








    
 

```cpp
#include<cstdio>
#include<algorithm>
#define N 200
#define M 100009
using namespace std;
int en,n,fa[N];                          //fa为并查集所需原件，en为边的条数 
struct edge{
    int s,e,d;
}ed[M];
void add_edge(int s,int e,int d){          //直接存边就行，不需要别的 
    en++;
    ed[en].s = s;
    ed[en].e = e;
    ed[en].d = d;
}
bool operator < (const edge &a,const edge &b){   //给边长排序要用到STL的sort函数，重载一下运算符，因为是结构体排序 
    return a.d < b.d;
}
int getf(int now){                              //带路径压缩的并查集 
    if(fa[now] == now)return now;
    else return fa[now] = getf(fa[now]);
}
int kruskal(){
    sort(ed+1,ed+en+1);                            //对边进行排序 
    for(int a = 1; a <= n; a++)fa[a] = a;        //并查集初始化 
    int ans = 0;             
    for(int a = 1;a <= en;a++){
        int f1 = getf(ed[a].s);                    //获取边两边的集合编号，s为起点，e为终点 
        int f2 = getf(ed[a].e);                 //同上 
        if(f1 != f2){                           //如果起点与终点不在同一集合，则说明这条边未被选择，则对其进行选择并合并两集合 
            fa[f2] = f1;                        //合并过程 
            ans += ed[a].d;                        //加边长 
        }
    }
    return ans;
}
int main(){
    scanf("%d",&n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int x;
            scanf("%d",&x);
            if(i == j)continue;                //对角线不需要存，则直接跳过 
            add_edge(i,j,x);                //存边 
        }
    }
    int ans = kruskal();                   //Kruskal（）跑一遍 
    printf("%d\n",ans);                      //输出答案 
    return 0;
}

```

---

## 作者：龘龘龘龘龘龘 (赞：0)

#克鲁斯卡尔算法解释

本人是小蒟蒻，代码写的不好不要介意哦，嘿嘿，详解如下，仅供参考，不要抄袭，自己多想想哦，

本人代码，

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<iostream>//把很多常用的都写出来了，虽然只用到来的两三个，但巩固一下记忆嘛 
const int maxlongint=0xfffffff;
using namespace std; 
int a[10000][3],fa[101];
int x,tot,p=0,n;
int myfind(int poi);
void mysort(int l,int r);
int main()
{
    int i,j,m=0,ta,tb;
    cin>>n;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            cin>>x;
            if(x!=0)
            {
                m++;
                a[m][1]=i;
                a[m][2]=j;
                a[m][0]=x;
```
}//初始化存边
```cpp
        }
    for(i=1;i<=n;i++)fa[i]=i;//初始化 
    mysort(1,m);//快排 
    k=0;//计数器 
    for(i=1;k!=n-1;i++)//kruskal算法 
```
{//循环所有已从小到大排序的边
```cpp
        ta=myfind(a[i][1]);
        tb=myfind(a[i][2]);
        if(ta!=tb)//合并序列 
        {
            fa[tb]=ta;
            k++;
            tot+=a[i][0];//生成树的权值和
        }
    }
    cout<<tot<<endl;
    return 0;
}
int myfind(int poi)//并查集，合并 
{
    if (fa[poi]!=poi)fa[poi]=myfind(fa[poi]);//路径压缩，优化 
    return fa[poi];
}
void mysort(int l,int r)//手写快排，时间复杂度小，但是如果懒得话可以有sort；头文件是algorithm； 
{
    int i,j,t,m;
    i=l;j=r;
    m=a[(l+r)/2][0];//将当前序列在中间位置的数定义为分隔数 
    do
    {
        while (a[i][0]<m) i++;//在左半部分寻找比中间大的数 
        while (a[j][0]>m) j--;//在右边寻找比中间小的数 
        if (i<=j)//若找到一组与排序目标不一致的数对，则交换他们 
        {
            t=a[i][1];a[i][1]=a[j][1];a[j][1]=t;
            t=a[i][2];a[i][2]=a[j][2];a[j][2]=t;
            t=a[i][0];a[i][0]=a[j][0];a[j][0]=t;
            i++;j--;//继续寻找 
        }
    }
    while(i<=j);//不能少了等号哦 
    if(i<r) mysort(i,r);//若没到到两个数的边界则递归搜素左右区间 
    if(l<j) mysort(l,j);
    return;
}
```

---

## 作者：SEELE (赞：0)


这道题是一道最小生成树的模板题.


直接用并查集优化的kruskal就可以过了.

原理:用邻接表读入图,然后把边从小到大按边权排序.依次把边加入最小生成树中.

如果两个点已经联通,则把该边去掉(否则就有环了).

代码如下:


```cpp
#include<iostream>
#include<algorithm>
using namespace std;
//为了排序方便,使用邻接表存储图
struct edge//边的邻接表存储
{
    int u, v, w;
}edges[1000001];
//tot是总边数
int cnt,n,tot,ans;
int uset[1000001];
//快速排序比较函数:按照边的权值从小到大排序 
bool cmp(edge a, edge b)
{
    return a.w < b.w;
}
//加一条边
void addedge(int u, int v,int w)
{
    edges[++cnt].u = u;
    edges[cnt].v = v;
    edges[cnt].w = w;
}
//并查集查找根节点
int find(int s)
{
    if (uset[s] != s) return uset[s] = find(uset[s]);//路径压缩
    return s;
}
//并查集合并
void merge(int a, int b)
{
    int x = find(a), y = find(b);
    if (x == y)
        return;
    uset[x] = y;
}
void init()
{
    cin >> n;
    tot = n*n - n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int tmp;
            cin >> tmp;
            if (i != j)
            {
                addedge(i, j, tmp);
            }
        }
    }
    //将边排序
    sort(edges + 1, edges + tot + 1, cmp);
    //并查集初始化
    for (int i = 1; i <= tot; i++)
    {
        uset[i] = i;
    }
}
//最小生成树算法核心
void kruskal()
{
    for (int i = 1; i <= tot; i++)
    {
        int u = edges[i].u,v=edges[i].v;
        //如果两个点不在一个并查集内,则连接.
        if (find(u) != find(v))
        {
            ans += edges[i].w;
            merge(u, v);
        }
    }
}
int main()
{
    init();
    kruskal();
    cout << ans;
}
```

---

## 作者：maruijie (赞：0)

prim的写法，类似于最短路径中的dijkstra，解析在代码中有解释，再此不多讲

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,c[105];//点到当前生成树的最短距离 
int b[105];//标记点是否加入生成树
int s; 
int a[105][105];
int main()
{
    int i,j;
    memset(c,0x7f,sizeof(c));//赋初值，到生成树最短距离为无限大 
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        scanf("%d",&a[i][j]);
    }
    for(i=1;i<=n;i++)
    {
        c[i]=a[1][i];//以点1为起点，把与点1相连的点最短距离改变 
    }
    b[1]=1;//点1标记为已经在生成树中 
    for(i=1;i<=n;i++)
    {
        int k=0;
        for(j=1;j<=n;j++)//找到到生成树最短距离的点 
        {
            if(b[j]==0&&c[j]<c[k])
            {
                k=j;
            }
        }
        b[k]=1;
        for(j=1;j<=n;j++)//对与刚才找到的点周围点进行松弛 
        {
            if(b[j]==0&&a[j][k]<c[j])
            c[j]=a[j][k];    
        }
    }
    for(i=1;i<=n;i++)//求和 
    s=s+c[i];
    printf("%d",s);
    return 0;
}
```

---

## 作者：云雾繁星 (赞：0)

看见DL们都用克鲁斯卡尔，萌新默默掏出了prim...

算法思想是，先从1开始找最小生成树，（因为是最小生成树，所以一共循环N-1次，这里我就不证明了），**逐个比较每个点所连接的权值，找出最小的那一个之后继续从这一个找**，用VISIT进行判重，最后将每次的权值进行相加即可。代码如下，比较容易理解


```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int map[110][110];
int vis[110];//判重 
int low[110];//每个顶点的最短路 
int main()
{
    int minn,pos;
    int ans=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>map[i][j];
        }
    }
    vis[1]=1;
    low[1]=0;//先从1点开始搜，初始化1点 
    for(int i=2;i<=n;i++)
    {
        low[i]=map[1][i];//给low赋值 
    }
    for(int j=1;j<=n-1;j++) //最小生成树的n-1次循环 
    {
        minn=101000;//由于村庄之间最大路程为100000，所以每次将权值定义为101000即为最大 
        for(int i=1;i<=n;i++)
        {
            if(vis[i]!=1&&low[i]<minn)//找第j个点与第几个点为最短路，找到最短路再从那个点开始循环 
            {
                minn=low[i];
                pos=i;
            }
        }
        ans=ans+minn;//记录答案 
        vis[pos]=1;
        for(int i=1;i<=n;i++)
        {
            if(vis[i]!=1&&low[i]>map[pos][i])//更新权值 
            {
                low[i]=map[pos][i];
            }
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：duzhenbang (赞：0)

非常裸的Prim算法，个人认为自己写的适合新手。


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int map[101][101],n,sum=0;
int mina[1000];
bool visit[1000];
int main() {
    cin>>n;
    for(int i=1; i<=n; ++i)
        for(int k=1; k<=n; ++k)
            cin>>map[i][k];//因为数据水，用邻接矩阵存储完全可以。
    memset(mina,0x7f,sizeof(mina));//mina[i]表示I电与他的父亲连接的最小权值
    memset(visit,true,sizeof(visit));//visit用来判断该点是否在生成树内
    mina[1]=0;
    for(int i=1; i<=n; ++i) {
        int k=0;
        for(int j=1; j<=n; ++j)
            if(visit[j]==true&&(mina[j]<mina[k]))//转换父亲节点
                    k=j;
                    visit[k]=false;
                    for(int j=1; j<=n; ++j)
                        if(visit[j]==true&&map[k][j]<mina[j])//判断是否为最小边
                            mina[j]=map[k][j];
                }
int total=0;
for(int i=1;i<=n;++i)
total+=mina[i];
cout<<total;
}
```

---

## 作者：Ouaoan (赞：0)

这题是最小生成树，我用prim和kruskal都做了。


prim代码：

/\*
ID: veilman1

PROG: agrinet

LANG: C++

\*/

```cpp
#include<stdio.h>
#include<iostream>
#include<fstream>
using namespace std;
int n;    //农场数量
int a[101][101]= {0};    //领接矩阵
int p[101]= {0},q[101]= {0};
int b[101][101]= {0};
int main() {
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");
    fin>>n;    //输入
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            fin>>a[i][j];
        }
    }
    p[1]=1;
    for(int i=2; i<=n; i++) {
        q[i]=1;
    }
    for(int i=1; i<=n; i++) {
        int s=999999999;
        int x=0,y=0;
        for(int j=1; j<=n; j++) {
            if(p[j]==1) {
                for(int k=1; k<=n; k++) {
                    if(a[j][k]!=0&&s>a[j][k]&&q[k]) {
                        s=a[j][k];
                        x=k;
                        y=j;
                    }
                }
            }
        }
        p[x]=1;
        q[x]=0;
        b[x][y]=1;
        b[y][x]=1;
        int h=0;
        for(int j=1; j<=n; j++) {
            if(p[j]==0) {
                h=1;
                break;
            }
        }
        if(h==0) {
            break;
        }
    }
    int ans=0;
    for(int i=1; i<=n; i++) {
        for(int j=n; j>=i; j--) {
            if(b[i][j]) {
                ans+=a[i][j];
            }
        }
    }
    fout<<ans<<endl;
    return 0;
}
```
kruskal代码:
/\*
ID: veilman1

PROG: agrinet

LANG: C++

\*/
```cpp
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
int n;    //农场数量
int a[101][101]= {0};    //接矩阵
struct A {
    int x,y,z;    //两个可连的点及权值
    bool zt=false;    //是否连接
} b[10001];
int p[101]= {0};
int zgjd(int x) {    //找根节点
    while(p[x]>0) {
        x=p[x];
    }
    return x;
}
int m=0;    //边数
int total=0;
int cmp(A const x,A const y) {
    if(x.z<y.z) {
        return 1;
    }
    return 0;
}
int main() {
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");
    fin>>n;    //输入
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            fin>>a[i][j];
            if(i!=j) {
                m++;
                b[m].x=i;
                b[m].y=j;
                b[m].z=a[i][j];
            }
        }
    }
    sort(b+1,b+m+1,cmp);
    for(int i=1; i<=n; i++) {
        p[i]=-1;
    }
    for(int i=1; i<=m; i++) {
        int genx=zgjd(b[i].x);
        int geny=zgjd(b[i].y);
        if(genx!=geny) {
            p[genx]+=p[geny];
            p[geny]=genx;
            total+=a[b[i].x][b[i].y];
            b[i].zt=true;    //状态为连接
        }
    }
    fout<<total<<endl;
    return 0;
}
```

---

## 作者：flipped (赞：0)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int g[101][101];              //邻接矩阵
int minn[101];                //minn[i]存放蓝点i与白点相连的最小边权
bool u[101];                  //u[i]=True，表示顶点i还未加入到生成树中
                              //u[i]=False，表示顶点i已加入到生成树中 
int n,i,j;
int main()
{
    freopen("wire.in","r",stdin);
    freopen("wire.out","w",stdout);
    cin >> n;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            cin >> g[i][j];           
    memset(minn,0x7f,sizeof(minn));   //初始化为maxint
    minn[1] = 0;
    memset(u,1,sizeof(u));            //初始化为True，表示所有顶点为蓝点
for (i = 1; i <= n; i++)
    {
        int k = 0;
        for (j = 1; j <= n; j++)     //找一个与白点相连的权值最小的蓝点k
            if (u[j] && (minn[j] < minn[k]))
                k = j;
        u[k] = false;                    //蓝点k加入生成树，标记为白点
        for (j = 1; j <= n; j++)         //修改与k相连的所有蓝点
            if (u[j] && (g[k][j] < minn[j]))
                 minn[j] = g[k][j]; 
    }       
    int total = 0;
    for (i = 1; i <= n; i++)             //累加权值 
        total += minn[i];
    cout << total << endl;
    return 0;
}
===========================================================================================================
Prim
```

---

## 作者：她说123 (赞：0)

prim算法一遍过

  
  
  
  
   
   
 
 
 
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int n,a[10002][10002],i,j,k,dis[10002],minn=0x7fffffff,ans;
bool f[10002];
int main()
{
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  memset(f,false,sizeof(f));
  memset(dis,127/3,sizeof(dis));
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  for(j=1;j<=n;j++) scanf("%d",&a[i][j]);
  for(i=1;i<=n;i++) if(a[1][i]!=0) dis[i]=a[1][i];
  f[1]=true;
  for(i=1;i<=n;i++)
 {
     minn=dis[0]+10; k=0;
   for(j=1;j<=n;j++)
   if(!f[j]&&minn>dis[j]) { minn=dis[j]; k=j; }
   if(k==0) break;
    f[k]=true;
   ans=ans+dis[k];
   for(j=1;j<=n;j++)
   if(dis[j]>a[k][j]&&a[k][j]>0&&!f[j]) 
   dis[j]=a[k][j];
 }
 cout<<ans;
 fclose(stdin);
 fclose(stdout);
 return 0;
}

```

---

## 作者：Stolf (赞：0)

这道题默认用矩阵存储

所以直接套用Prim

```cpp

#include <iostream>  
using namespace std;  
bool flag[100];  
int n, dist[100], w[100][100], ans = 0;  
void Prim(int vi)  
{  
    int k = vi;  
    for (int i = 0; i < n; i++)  
        dist[i] = w[vi][i];  
    flag[vi] = true;  
    for (int i = 0; i < n - 1; i++)  
    {  
        int min = 99999999;  
        for(int j = 0; j < n; j++)  
            if (dist[j] < min && !flag[j])  
                k = j, min = dist[j];  
        flag[k] = true;  
        for (int j = 0; j < n; j++)  
            if (dist[j] > w[k][j] && !flag[j])  
                dist[j] = w[k][j];  
    }  
}  
int main(int argc, char *argv[])  
{  
    cin >> n;  
    for (int i = 0; i < n; i++)  
        for (int j = 0; j < n; j++)  
            cin >> w[i][j];  
    Prim(0);  
    for (int i = 0; i < n; i++)  
        ans += dist[i];  
    cout << ans;  
    return 0;  
}  

```

---

## 作者：lych (赞：0)

这道题目一般有两种解法，介绍一种（prim算法）；

算法时间复杂度是O(N^2);空间O(N^2);

```cpp
//首先B数组负true
fillchar(b,sizeof(b),true);
//首先将第一个节点加入，B数组负false
 b[1]:=false;
//用min[i]表示当前连接到i节点最少的路径
for i:=1 to n do min[i]:=a[1,i];
//然后每次贪心取最少的
for i:=2 to n do
    begin
      w:=0;
      for j:=2 to n do
        if b[j] then
          if min[j]<min[w] then w:=j;
//取好后，B数组负false
b[w]:=false;
```
累加总和  inc(ans,min[w]);
并且更新min数组的值

```cpp
for j:=2 to n do
        if b[j] then
          if a[w,j]<min[j] then
            min[j]:=a[w,j];
```
具体程序如下：
```cpp
var
  n,i,j,w,ans:longint;
  a:array[0..101,0..101] of longint;
  b:array[0..1000] of boolean;
  min:array[0..1000] of longint;
begin
  read(n);
  for i:=1 to n do
    for j:=1 to n do
      read(a[i,j]);//读入
  for i:=1 to n do min[i]:=a[1,i];//设置min数组的初值
  fillchar(b,sizeof(b),true);//B数组负true
  b[1]:=false;
  min[0]:=maxlongint;//为了简化代码，其实用一个数记录最小也可以
  for i:=2 to n do  // 把所有的节点全都连接，共需要n-1次（不包括第一次）
    begin
      w:=0;
      for j:=2 to n do
        if b[j] then //判重与回路
          if min[j]<min[w] then w:=j;
      inc(ans,min[w]);
      b[w]:=false;//非常关键，否则出错
      for j:=2 to n do
        if b[j] then //同上
          if a[w,j]<min[j] then
            min[j]:=a[w,j];//每次更新min的值，以便下次使用
    end;
  writeln(ans);
end.{prim算法}
```

---

