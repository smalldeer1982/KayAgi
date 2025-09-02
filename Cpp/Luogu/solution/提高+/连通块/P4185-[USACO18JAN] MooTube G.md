# [USACO18JAN] MooTube G

## 题目背景

*本题与 [银组同名题目](/problem/P6111) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

在业余时间，Farmer John 创建了一个新的视频共享服务，他将其命名为 MooTube。在 MooTube 上，Farmer John 的奶牛可以录制，分享和发现许多有趣的视频。他的奶牛已经发布了 $N$ 个视频（$1 \leq N \leq 10^5$），为了方便将其编号为  $1 \ldots N$ 。然而，FJ 无法弄清楚如何帮助他的奶牛找到他们可能喜欢的新视频。

FJ 希望为每个 MooTube 视频创建一个“推荐视频”列表。这样，奶牛将被推荐与他们已经观看过的视频最相关的视频。

FJ 设计了一个“相关性”度量标准，顾名思义，它确定了两个视频相互之间的相关性。他选择 $N-1$ 对视频并手动计算其之间的相关性。然后，FJ 将他的视频建成一棵树，其中每个视频是节点，并且他手动将 $N-1$ 对视频连接。为了方便，FJ 选择了 $N-1$ 对，这样任意视频都可以通过一条连通路径到达任意其他视频。 FJ 决定将任意一对视频的相关性定义为沿此路径的任何连接的最小相关性。

Farmer John 想要选择一个 $K$ 值，以便在任何给定的 MooTube 视频旁边，推荐所有其他与该视频至少有 $K$ 相关的视频。然而，FJ 担心会向他的奶牛推荐太多的视频，这可能会分散他们对产奶的注意力！因此，他想设定适当的 $K$ 值。 Farmer John希望得到您的帮助，回答有关 $K$ 值的推荐视频的一些问题。

## 样例 #1

### 输入

```
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1```

### 输出

```
3
0
2
```

# 题解

## 作者：StudyingFather (赞：47)

题目并不要求强制在线，我们可以将询问按 $k$ 的值降序排序后离线解决本题。

我们用并查集维护连通块，对于每个询问，我们将边权大于等于给定的边权 $k$ 的边加入图中，对于一个点 $v$，满足条件的点数为其所在连通块大小 $-1$（不包括这个点本身）。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct edge
{
 int u,v,w;
}e[100005];
struct query
{
 int k,v,id;
}a[100005];
int fa[100005],siz[100005],ans[100005];
bool cmp1(const edge&a,const edge&b)
{
 return a.w>b.w;
}
bool cmp2(const query&a,const query&b)
{
 return a.k>b.k;
}
void unionn(int x,int y)
{
 if(x==y)return;
 fa[y]=x;
 siz[x]+=siz[y];
}
int find(int x)
{
 return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
 int n,q;
 scanf("%d%d",&n,&q);
 for(int i=1;i<=n;i++)
  fa[i]=i,siz[i]=1;
 for(int i=1;i<n;i++)
  scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
 for(int i=1;i<=q;i++)
 {
  scanf("%d%d",&a[i].k,&a[i].v);
  a[i].id=i;
 }
 sort(e+1,e+n,cmp1);
 sort(a+1,a+q+1,cmp2);
 int cur=1;
 for(int i=1;i<=q;i++)
 {
  while(cur<=n&&a[i].k<=e[cur].w)
  {
   unionn(find(e[cur].u),find(e[cur].v));
   cur++;
  }
  ans[a[i].id]=siz[find(a[i].v)]-1;
 }
 for(int i=1;i<=q;i++)
  printf("%d\n",ans[i]);
 return 0;
}
```


---

## 作者：蔡俊黠 (赞：31)

哇没想到我也能做提高+的题好开心

一开始很简单粗暴地想到了邻接矩阵，做到10分才发觉这么高大上的题目你用这个方法来做是不是大傻X

看了大牛 elijahqi 的题解就想明白了原来是并查集啊~~哈哈哈~~

蒟蒻的第一篇题解就你了哈哈

思路：
1. 在并查集的基础上加一点料，并查集原来是有边就把它连的两个点合并嘛，在这里我们吧、加一个条件，要>=k即符合条件的边才给它合并，这样的话这个连通块中所有的点都符合条件啦
2. 但是如果每次询问都重新合并一次的话会超时啊孩纸，所以我们用到两个快排，把每条边从大到小排 ，再把 询问的k从大到小排，先做最大的k，把符合条件的点合并后（不要忘记统计结点数，这个才是我们想要的嘛），那么下一个k肯定比这个小啦（排序了嘛），那么符合大k的点肯定符合小k的点啦，那么就不用再重复合并啦，做到第i个k，这个连通块中的结点就符合条件啦  ~~阿拉拉拉~~

emmm好像就这些把，我能理解的想必大神们都能理解嘻嘻

如果我说得有什么不对或遗漏的欢迎评论哦

不BB了上题解
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int j=1,n,q,number[110000],father[110000],ans[110000];
struct kind{
	int start;
	int end;
	int w;
}bian[110000];
struct kind2  
{
	int k;
	int v;
	int id;
}ask[110000];
int cmp(kind x,kind y){ return x.w>y.w; }
int cmp2(kind2 x,kind2 y){ return x.k>y.k; }
int getfather(int x) //寻找x的父节点 
{
	if (father[x]!=x) father[x]=getfather(father[x]);
	return father[x];
}
void onion(int x,int y)
{
	x=getfather(x);
	y=getfather(y);
	if (x!=y)
	{
      father[x]=y;  //合并父节点就把它们合并啦啦啦 
	  number[y]+=number[x];  //父亲又多了几个儿子哈哈 
    }
}
int main()
{
	cin>>n>>q;
	for (int i=1;i<=n;i++) 
	{ 
	  father[i]=i;  
	  number[i]=1;  //number[]统计连通块中的结点数量 
    }
	for (int i=1;i<n;i++) 
	  cin>>bian[i].start>>bian[i].end>>bian[i].w; //读入起始点，到达点，边（连自己都觉得幼稚的数组bian[]） 
	for (int i=1;i<=q;i++) 
	{
	    cin>>ask[i].k>>ask[i].v;  
	    ask[i].id=i;
	}                    //“离线”操作 ，因为后面还要对询问中的k进行排序（“离线”是指读入完后再操作，“在线”是指边读入边操作） 
    sort(bian+1,bian+n+1,cmp);  //对bian[]数组进行快排，把每条边的长度从大到小排，方便后面将>=k的边连接的点进行合并 
    sort(ask+1,ask+1+q,cmp2);  //对ask[]询问数组进行快排，把询问的k从大到小排， 
    for (int i=1;i<=q;i++)   //对每个个询问进行操作 
    {
    	while (j<n&&bian[j].w>=ask[i].k)  //也可以用for语句代替，不过要把bian[j].w>=ask[i].k写在 for()括号里，避免多余的操作，不然会TLE的啊
		//把每条>=k的边连接的点进行合并，即将符合条件的点都拉进这个连通块，那么这个连通块中所有的点都符合条件 
    	//注意：变量j的声明一定要放在外面啊，不然会TLE，为什么呢，因为我们是把k从大做到小，k=4这个连通块里的结点肯定也符合k=3的这个条件，所以就不必要做重复的结合啦  
		{
		    onion(bian[j].start,bian[j].end);
		    j++;
		}
    	ans[ask[i].id]=number[getfather(ask[i].v)];  //ans[]就是要输出的东西啦，要保证原来的输入对应输出，就需要ans[ask.id]这个东西，找到v点的父节点，那么符合条件的节点数就在number[]里面啦啦啦 
    }
    for (int i=1;i<=q;i++) cout<<ans[i]-1<<endl;  //去掉自己一个结点后输出  
    return 0;  //Yeah~~ 
}
```

---

## 作者：Patrickpwq (赞：10)

博主考试的时候失智了 明明只差一句话就可以AC了的 然后抽风了交了暴力上去

标算是离线并查集 这里提供一种Kruskal重构树的简单做法

将重构树建出来后 此时是一个小根堆

我们倍增的往上跳 直到找到一个祖先的权值刚好大于K 显然 此时这个祖先的所有子节点到V的距离都是大于等于K的。因为此时u到v的距离是LCA(u,v)，而显然，LCA(u,v)一定属于这个祖先的子树。

```cpp
#include<bits/stdc++.h>
const int N=100005;
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	static char ch=getchar();
	while(!isdigit(ch))	ch=getchar();
	while(isdigit(ch))	x=x*10+ch-'0',ch=getchar();
}
int n,Q,cnt,first[2*N],tot,size[2*N];
struct Edge
{
	int from,to,next,val;
	bool operator <(const Edge &p) const
	{
		return this->val>p.val;
	}
}e[N],edge[8*N];
inline void addedge(int x,int y)
{
	tot++;
	edge[tot].to=y; edge[tot].next=first[x]; first[x]=tot;
}
int father[2*N],up[2*N][22],val[2*N],depth[2*N];
inline int getfather(int x)
{
	if(father[x]==x)	return x;
	return father[x]=getfather(father[x]);
}
void Kruskal_Rebuild()
{
	sort(e+1,e+cnt+1);
	for(register int i=1;i<=2*n;i++)	father[i]=i;
	int sign=n;
	for(register int i=1;i<=cnt;i++)
	{
		int fx=getfather(e[i].from);		int fy=getfather(e[i].to);
		if(fx==fy)	continue;
		father[fx]=father[fy]=++sign;
		addedge(fx,sign); addedge(sign,fx);
		addedge(fy,sign); addedge(sign,fy);
		val[sign]=e[i].val;
	}
}
void dfs(int now,int fa)
{
	if(now<=n)	size[now]=1;
	depth[now]=depth[fa]+1;
	up[now][0]=fa;
	for(int i=1;i<=19;i++)	up[now][i]=up[up[now][i-1]][i-1];
	for(int u=first[now];u;u=edge[u].next)
	{
		int vis=edge[u].to;
		if(vis==fa)	continue;
		dfs(vis,now);
		size[now]+=size[vis];
	}
}
int main()
{
	cin>>n>>Q;
	for(register int i=1;i<=n-1;i++)
	{
		int x,y,z;
		read(x); read(y); read(z);
		e[++cnt].from=x; e[cnt].to=y; e[cnt].val=z; 
	}
	Kruskal_Rebuild();
	dfs(2*n-1,0);
	while(Q--)
	{
		int v,k;
		read(k); read(v);
		for(int i=19;i>=0;i--)
			if(val[up[v][i]]>=k)	v=up[v][i];
		cout<<size[v]-1<<'\n';
	}
	return 0;
}
```

---

## 作者：xh39 (赞：9)

前置算法:并查集。(为保证您的阅读质量,阅读此篇题解前请先学习并查集。)。
## 思路
我们把询问按k从大到小排序,把边按边权从大到排序。

我们就可以对于每个询问$i$,依次合并所有**不小于**$k[i]$的边连接的2个**节点**(注意宾语是**结点**)。

合并用并查集合并。

## 演示

下面来演示此算法。就拿样例来演示吧。
```cpp
4 3     排序后:
1 2 3   2 4 4
2 3 2   1 2 3
2 4 4   2 3 2
1 2     4 1
4 1     3 1
3 1     1 2
```
初始集合{1},{2},{3},{4}。

询问$k=4,v=1$:合并所有$>=4$。$2$合并到$4$,集合为{$1$},{$3$},{$2,4$};此时$v(1)$所在的集合元素个数为$1$。

询问$k=3,v=1$:合并所有$>=3$。$1$合并到$2$,集合为{$3$},{$1,2,4$};此时$v(1)$所在的集合元素个数为$3$。

询问$k=4,v=1$:合并所有$>=1$。$2$合并到$3$,集合为{$1,2,3,4$};此时$v(2)$所在的集合元素个数为$4$。

自己不能推荐自己。所以把所有的答案-1,然后输出。
## ac.code
已经讲得很具体了,代码里的注释就不会很多了。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct ${ //存询问。
	int k,v,id; //id表示询问编号。好将答案存起来。最后一起输出。
}_[1000005];
struct xyq{
	int u,v,w;
}e[1000005];
struct rule{ //存图。
	bool operator()(const xyq &s1,const xyq &s2){
		return s1.w>s2.w;
	}
};
struct rule${ //自定义排序。
	bool operator()(const $ &s1,const $ &s2){
		return s1.k>s2.k;
	}
};
int f[1000005],ans[1000005],size[1000005]; //f存并查集的父亲。ans存答案,size存大小。
int getfather(int iakioi){ //并查集找父亲。
	if(f[iakioi]==iakioi){
		return iakioi;
	}
	f[iakioi]=getfather(f[iakioi]); //路径压缩。
	return f[iakioi];
}
int main(){
	int n,m,i,a,b,c,tot=0,sum=0;
	cin>>n>>m;
	for(i=0;i<n-1;++i){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	for(i=0;i<m;++i){
		cin>>_[i].k>>_[i].v;
		_[i].id=i; //初始化编号别漏掉。
	}
	for(i=0;i<=n;++i){
		f[i]=i; //一开始自己的父亲都是自己。
		size[i]=1; //一开始元素的大小都是1。
	}
	sort(e,e+n,rule());
	sort(_,_+m,rule$());
	for(i=0;i<m;++i){
		while(_[i].k<=e[tot].w){
			size[getfather(e[tot].v)]+=size[getfather(e[tot].u)];
			f[getfather(e[tot].u)]=getfather(e[tot].v);
			++tot;
		}
		ans[_[i].id]=size[getfather(_[i].v)];
	}
	for(i=0;i<m;++i){
		cout<<ans[i]-1<<endl; //减1是因为自己不推荐自己。
	}
	return 0;
}
```

---

## 作者：さょなち (赞：6)

~~这是蒟蒻的第一篇题解，想不到竟然这么高大上哈哈哈，dalao请指点~~
这是老师叫做的题，一开始就想到简单模拟，先把边权最小的值按大小排序，在边输入边处理，但是看了看数据，很显然空间会达到O（n*n）（n*log2n），会RE。
后来想了想，既然如果满足大的K必然会满足小的K，所以只需要把询问也排一次序就可以省掉很多时间，既然路径是连通的，那就用并查集合并起来，但是合并是有技巧的，只需要把大于K的数合并就可以了。其实这道题用到离线解决的方法。
所以，这题可以转化为求连通块。
如图~~画的丑请见谅~~
![](我的文档)
代码如下
```
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int N,Q;
int ft[100005],size[100005],ans[100005];
struct edge{
    int p,q,r;
}a[100005];
struct ask{
    int k,v,id;
}b[100005];
int cmp(edge x,edge y){return x.r>y.r;}
int cmp1(ask x,ask y){return x.k>y.k;}
int gf(int n){
    if(ft[n]!=n)ft[n]=gf(ft[n]);
    return ft[n];
}
int main(){
    /*freopen("mootube.in","r",stdin);
    freopen("mootube.out","w",stdout); */
    cin>>N>>Q;
    for(int i=1;i<N;i++)
        cin>>a[i].p>>a[i].q>>a[i].r;
    for(int i=1;i<=Q;i++){
        cin>>b[i].k>>b[i].v;b[i].id=i;
    }
    sort(a+1,a+N+1,cmp);sort(b+1,b+Q+1,cmp1);//离线解决 
    for(int i=1;i<=N;i++){ft[i]=i;size[i]=1;}
    int j=1;
    for(int i=1;i<=Q;i++){
        while(a[j].r>=b[i].k&&j<N){
            int x=gf(a[j].p),y=gf(a[j].q);
            j++;
            if(x==y)continue;
            ft[x]=y;
            size[y]+=size[x];
        }
        ans[b[i].id]=size[gf(b[i].v)]-1;
        //在同集里且满足条件，大的满足，小的也满足 
    }
    for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;//按顺序输出 
    return 0;
}
```

---

## 作者：elijahqi (赞：5)

http://www.elijahqi.win/2018/02/02/luogu4185-usaco18janmootube-gold/ 
http://blog.csdn.net/elijahqi/article/details/79243095

题目描述

In his spare time, Farmer John has created a new video-sharing service, which he names MooTube. On MooTube, Farmer John's cows can record, share, and discover many amusing videos. His cows already have posted
NN

N videos (
1≤N≤100,0001 \leq N \leq 100,000

1≤N≤100,000 ), conveniently numbered
1…N1 \ldots N

1…N . However, FJ can't quite figure out how to help his cows find new videos they might like.

FJ wants to create a list of "suggested videos" for every MooTube video. This way, cows will be recommended the videos most relevant to the ones they already watch.

FJ devises a metric of "relevance," which determines, as the name suggests, how relevant two videos are to each other. He picks
N−1N-1

N−1 pairs of videos and manually computes their pairwise relevance. Then, FJ visualizes his videos as a network, where each video is a node and the
N−1N-1

N−1 pairs of videos he manually considered are connected. Conveniently, FJ has picked his
N−1N-1

N−1 pairs so that any video can be reached from any other video along a path of connections in exactly one way. FJ decides that the relevance of any pair of videos should be defined as the minimum relevance of any connection along this path.

Farmer John wants to pick a value
KK

K so that next to any given MooTube video, all other videos with relevance at least
KK

K to that video will be suggested. However, FJ is worried that too many videos will be suggested to his cows, which could distract them from milk production! Therefore, he wants to carefully set an appropriate value of
KK

K . Farmer John would like your help answering a number of questions about the suggested videos for certain values of
KK

K .
输入输出格式

输入格式：
The first line of input contains
NN

N and
QQ

Q (
1≤Q≤100,0001 \leq Q \leq 100,000

1≤Q≤100,000 ).

The next
N−1N-1

N−1 lines each describe a pair of videos FJ manually compares. Each line includes three integers
pip_i

pi​ ,
qiq_i

qi​ , and
rir_i

ri​ (
1≤pi,qi≤N,1≤ri≤1,000,000,0001 \leq p_i, q_i \leq N, 1 \leq r_i \leq 1,000,000,000

1≤pi​,qi​≤N,1≤ri​≤1,000,000,000 ), indicating that videos
pip_i

pi​ and
qiq_i

qi​ are connected with relevance
rir_i

ri​ .

The next
QQ

Q lines describe Farmer John's
QQ

Q questions. Each line contains two integers,
kik_i

ki​ and
viv_i

vi​ (
1≤ki≤1,000,000,000,1≤vi≤N1 \leq k_i \leq 1,000,000,000, 1 \leq v_i \leq N

1≤ki​≤1,000,000,000,1≤vi​≤N ), indicating that FJ's
ii

i th question asks how many videos will be suggested to viewers of video
viv_i

vi​ if
K=kiK = k_i

K=ki​ .

输出格式：
Output
QQ

Q lines. On line
ii

i , output the answer to FJ's
ii

i th question.
输入输出样例

输入样例#1： 复制

4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1

输出样例#1： 复制

3
0
2
Farmer John finds that videos one and two have relevance three, that videos two and three have relevance two, and that videos two and four have relevance four. Based on this, videos one and three have relevance min(3, 2) = 2, videos one and four have relevance min(3, 4) = 3, and videos three and four have relevance min(2, 4) = 2.

Farmer John wants to know how many videos will be suggested from video two if $K=1$, from video one if $K=3$, and from video one if $K=4$. We see that with $K=1$, videos 1, 3, and 4 will be suggested on video two. With $K=4$, no videos will be suggested from video one. With $K=3$, however, videos 2 and 4 will be suggested from video one.

题意：每次给一个起点 然后询问和他相连的点的边权比k大的点有几个 路径边权是两点连接的所有路径上最小值

所以我针对询问离线然后 从大到小进行询问 每次把他加入并查集方便统计答案 一开始犹豫 这个大小怎么记因为我没有递归后来认真考虑了下 其实无所谓我只需要直到一个完整块的大小即可

```
#include<cstdio>
#include<algorithm>
#define N 110000
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=gc();}
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
    return x*f;
}
struct node{
    int x,y,z;
}data[N];
struct node1{
    int k,v,id;
}qr[N];
inline bool cmp(const node1 &a,const node1 &b){return a.k>b.k;}
inline bool cmp1(const node &a,const node &b){return a.z>b.z;}
int fa[N],size[N],ans[N],n,q;
inline int find(int x){while(x!=fa[x]) x=fa[x]=fa[fa[x]];return x;}
int main(){
//	freopen("mootube.in","r",stdin);
//	freopen("mootube.out","w",stdout);
    n=read();q=read();
    for (int i=1;i<n;++i) data[i].x=read(),data[i].y=read(),data[i].z=read();
    for (int i=1;i<=q;++i) qr[i].k=read(),qr[i].v=read(),qr[i].id=i;
    sort(qr+1,qr+q+1,cmp);sort(data+1,data+n+1,cmp1);
    for (int i=1;i<=n;++i) fa[i]=i,size[i]=1;int now=1;
    for (int i=1;i<=q;++i){
        while(now<=n&&data[now].z>=qr[i].k){
            int x=find(data[now].x),y=find(data[now].y);++now;
            if (x==y) continue;fa[x]=y;size[y]+=size[x];
        }ans[qr[i].id]=size[find(qr[i].v)]-1;
    }
    for (int i=1;i<=q;++i) printf("%d\n",ans[i]);
    return 0;
}

```


---

## 作者：zengxr (赞：4)

# 算法步骤：
1.按边权从大小到排序

2.然后按照询问所要求的边权，将大于它的加
入进去看集合中有多少个点，答案即为ans-1

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int ans[100010];
struct tree{
  int x,y,dis;
}a[100010];
struct node{
  int dis,v,pos;
}b[100010],c[100010];
int father[100010];
int size[100010];
bool cmp(tree xx,tree yy)
{
  return xx.dis>yy.dis;
}
bool cmp1(node xx,node yy)
{
  return xx.dis>yy.dis;
}
int find(int x)
{
  if(x!=father[x])
    father[x]=find(father[x]);
  return father[x];
}
void unionn(int x,int y)
{
  x=find(x);
  y=find(y);
  if(x!=y)
  {
    father[x]=y;
    size[y]+=size[x];
  }
}
int main()
{
  scanf("%d%d",&n,&m);
  for(int i=1;i<n;i++)
    scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].dis);
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&b[i].dis,&b[i].v);
    b[i].pos=i;
  }
  sort(a+1,a+n+1-1,cmp);
  sort(b+1,b+1+m,cmp1);
  for(int i=1;i<=n;i++)
  {
    father[i]=i;
    size[i]=1;
  }
  int t=1;
  for(int i=1;i<=m;i++)
  {
    int dis=b[i].dis;
    int v=b[i].v;
    while(t<n&&a[t].dis>=dis)
    {
      unionn(a[t].x,a[t].y);
      t++;
    }
    ans[b[i].pos]=size[find(v)]-1;
    //printf("%d\n",size[find(v)]-1);
  }
  for(int i=1;i<=m;i++)
    printf("%d\n",ans[i]);
 
 
 
}
```


---

## 作者：何俞均 (赞：2)

广告：食用[$blog$](https://www.cnblogs.com/heyujun/p/10333375.html)体验更佳

## 题解：

先将所有操作和询问离线

然后按照边权从大到小将操作和询问排序

利用$two\;pointers$，每次扫到一个询问，将边权大于等于它的边的两点全部都并起来

因为边权大的满足，那么边权小的一定也能满足

对于每个询问，直接查它联通块的$size$即可

代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring> 
#include <cmath> 
#include <algorithm>
using namespace std; 
inline int gi() {
	register int data = 0, w = 1;
	register char ch = 0;
	while (!isdigit(ch) && ch != '-') ch = getchar(); 
	if (ch == '-') w = -1, ch = getchar();
	while (isdigit(ch)) data = 10 * data + ch - '0', ch = getchar();
	return w * data; 
}
const int MAX_N = 1e5 + 5; 
struct Query { int k, v, id; } q[MAX_N]; 
struct Edge { int u, v, w; } e[MAX_N]; 
bool operator < (const Query &l, const Query &r) { return l.k > r.k; } 
bool operator < (const Edge &l, const Edge &r) { return l.w > r.w; } 
int N, Q, fa[MAX_N], size[MAX_N], ans[MAX_N]; 
int getf(int x) { return (x == fa[x]) ? x : (fa[x] = getf(fa[x])); }
void unite(int x, int y) { x = getf(x), y = getf(y); if (x != y) fa[x] = y, size[y] += size[x]; } 
int main () { 
	N = gi(), Q = gi(); 
	for (int i = 1; i < N; i++) e[i].v = gi(), e[i].u = gi(), e[i].w = gi(); 
	for (int i = 1; i <= Q; i++) q[i].k = gi(), q[i].v = gi(), q[i].id = i; 
	sort(&e[1], &e[N]); sort(&q[1], &q[Q + 1]);
	for (int i = 1; i <= N; i++) fa[i] = i, size[i] = 1; 
	for (int i = 1, j = 1; i <= Q; i++) { 
		while (e[j].w >= q[i].k && j < N) unite(e[j].u, e[j].v), ++j; 
		ans[q[i].id] = size[getf(q[i].v)] - 1; 
	}
	for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]); 
	return 0; 
} 
```

---

## 作者：SUNCHAOYI (赞：1)

**并查集思想，一开始排序后（从大到小方便处理）。然后循环，如果符合条件（关联度不小于k），那么进行合并。最后记录连通块的数量，但答案记得要减去自己（当时把自己这个点给算进去了）。**

**详见代码：**
```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 100001;
struct tree
{
	int x,y,dis;
}a[MAX];
struct node
{
	int k,v,num;
}b[MAX];
int n,m,fa[MAX],size[MAX],ans[MAX] = {0};
bool cmp(tree xx,tree yy);
bool _cmp(node xx,node yy);
void work(int xx,int yy);
int getfather(int xx);
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i < n;i++)scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].dis);
	for(int i = 1;i <= m;i++)
	{
		scanf("%d%d",&b[i].k,&b[i].v);
		b[i].num = i;
	}
	sort(a + 1,a + n + 1,cmp);
	sort(b + 1,b + m + 1,_cmp);
	for(int i = 1;i <= n;i++)
	{
		fa[i] = i;//父亲 
		size[i] = 1;//关联块数量 
	}
	int j = 1;
	for(int i = 1;i <= m;i++)
	{
		while(j < n && a[j].dis >= b[i].k)//关联度大于k 
		{
			work(a[j].x,a[j].y);
			j++;
		}
		ans[b[i].num] = size[getfather(b[i].v)];//size即为关联的视频数量，num记录是第几个(因为排序过，但需按原序输出) 
	}
	for(int i = 1;i <= m;i++)printf("%d\n",ans[i] - 1);//减去自己 
	return 0;
}
bool cmp(tree xx,tree yy){return xx.dis > yy.dis;}
bool _cmp(node xx,node yy){return xx.k > yy.k;}
void work(int xx,int yy)//合并操作 
{
	xx = getfather(xx);yy = getfather(yy);
	if(xx != yy)
	{
		fa[xx] = yy;
		size[yy] += size[xx];
	}
}
int getfather(int xx)
{
	if(fa[xx] != xx)fa[xx] = getfather(fa[xx]);
	return fa[xx];
}
```


---

