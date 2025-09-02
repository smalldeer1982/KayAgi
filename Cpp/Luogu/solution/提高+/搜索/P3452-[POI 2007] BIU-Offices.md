# [POI 2007] BIU-Offices

## 题目描述

Bytel 是一家移动通信公司。该公司的每位员工都收到了一部公司生产的电话，电话的通讯录中存储着一些同事的电话号码（每部手机中也都有该手机本身的电话号码）。

由于业务扩张，公司总部需要迁移至新的办公区。为了提高工作效率，董事会决定在不同栋楼工作的每一对员工需要**相互**知道对方的电话号码。即如果 $u$ 和 $v$ 在不同的楼工作，则 $u$ 的通讯录里需要存储 $v$ 的电话号，$v$ 的通讯录里也要存储 $u$ 的电话号码。

同时，董事会决定租用尽可能多的楼，以确保良好的工作条件。现在你需要帮助 Bytel 公司计算出他们需要租用多少栋楼。

## 说明/提示

$2 \leq n \leq 10^5$，$1 \leq m \leq 2 \times 10^6$，$1 \leq a_i \lt b_i \leq n$。

## 样例 #1

### 输入

```
7 16
1 3
1 4
1 5
2 3
3 4
4 5
4 7
4 6
5 6
6 7
2 4
2 7
2 5
3 5
3 7
1 7```

### 输出

```
3
1 2 4```

# 题解

## 作者：孑思 (赞：24)

# 这是一个求原图的补图联通块个数的题

### 我们可以知道如果一个点在原图中不能到达另一个点

### 那么这个点一定可以在补图中到达那个点

### 但是原图可以到达的点补图不一定不能到达

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
bool vis[100010],cov[100010];
int cnt,head[100010],nxt[4000100],var[4000100];
int nex[100010],last[100010];
int st[100010],ans;
int n,m;
queue<int> q;
void add(int x,int y) {
	cnt++;
	var[cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}//链式向前星，蒟蒻不会vector QWQ
void del(int x) {
	nex[last[x]]=nex[x];
	last[nex[x]]=last[x];
}//删除链表中的某个元素
int main() {
	scanf("%d%d",&n,&m);
	int x,y;
	for(int i=1; i<=m; i++) {
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);//建图
	}
	nex[0]=1;
	for(int i=1; i<n; i++) {
		last[i+1]=i;
		nex[i]=i+1;
	}
	//可以理解为链表，访问的时候可以快一点
	for(int i=1; i<=n; i++) {
		if(!vis[i]) { 
		//如果没被访问过
			st[++ans]=1;//新开一个联通块
			vis[i]=true;//标记
			q.push(i);//入队
			del(i);//删除这个点
			while(!q.empty()) {
				int x=q.front();
				q.pop();
				for(int j=head[x]; j; j=nxt[j]) {
					if(!vis[var[j]]) { 
					//如果原图可以到达的点没有访问过
						cov[var[j]]=true;
						//标记，原图可以访问
					}
				}
				for(int j=nex[0]; j; j=nex[j]) {
					if(!cov[j]) { 
					//访问不到的全都入队，因为在补图里可以访问到
						vis[j]=true;
						//这个点在补图里访问过了
						st[ans]++;
						//联通块里的点的个数++；
						del(j);
						//删除这个点
						q.push(j);
						//入队
					} else cov[j]=false; 
					//如果在原图中可以访问到，那就没他什么事了，恢复原样吧
				}
			}
		}
	}
	sort(st+1,st+ans+1);//排序一下
	printf("%d\n",ans);
	for(int i=1; i<=ans; i++) {
		printf("%d ",st[i]);
	}
	return 0;
	//return 0不知道有没有必要，这几天Claris上课标程永远没有return 0，但是蒟蒻又不敢不打，瑟瑟发抖
}
```
感谢 奔波儿霸 指出错误

---

## 作者：ButterflyDew (赞：8)

## 题意

给定$n(\le 100000)$个点$m(\le 2000000)$条边的无向图$G$，求这个图$G$补图的连通块个数。

------

一开始想了半天各种啥啥啥优化补图连边。

但复杂度没算好，最开始$\tt{set}$的想法是可以通过此题的。

使用链表+队列可以做到$O(n+m)$的复杂度

具体流程如下：

1. 将所有的点加入链表
2. 从链表中随便拿出一个点加入队列，如果链表为空，结束
3. 遍历队列
   - 对于当前点，把$\tt{Ta}$的连接的边打标记。
   - 遍历链表，取出没有打标记的点从链表中删去并加入队列。
   - 取消标记。
4. 在$3$中进入队列的点统计为一个连通块

考虑这样的复杂度为什么是$O(n+m)$的

每条边两边的点会被打一次标记并取消一次标记，并最多一次作为遍历链表时没有被删去的点，这里是$O(m)$的。

每个点最多会从链表中删去一次，这里是$O(n)$的。

------

**Code:**

```cpp
#include <cstdio>
#include <algorithm>
const int N=1e5+10;
const int M=2e6+10;
int head[N],to[M<<1],Next[M<<1],cnt;
void add(int u,int v)
{
    to[++cnt]=v,Next[cnt]=head[u],head[u]=cnt;
}
int n,m,pre[N],suc[N],q[N],l,r,ans[N],col[N],tot;
int main()
{
    scanf("%d%d",&n,&m);
    for(int u,v,i=1;i<=m;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    for(int i=1;i<=n;i++)
        pre[i]=i-1,suc[i]=i+1;
    suc[0]=1,suc[n]=0;
    while(suc[0])
    {
        l=1,r=0;
        q[++r]=suc[0];
        suc[0]=suc[suc[0]];
        pre[suc[q[r]]]=0;
        while(l<=r)
        {
            int now=q[l++];
            for(int i=head[now];i;i=Next[i])
                col[to[i]]=1;
            int cur=suc[0];
            while(cur)
            {
                if(!col[cur])
                {
                    q[++r]=cur;
                    pre[suc[cur]]=pre[cur];
                    suc[pre[cur]]=suc[cur];
                }
                cur=suc[cur];
            }
            for(int i=head[now];i;i=Next[i])
                col[to[i]]=0;
        }
        ans[++tot]=l-1;
    }
    std::sort(ans+1,ans+1+tot);
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：PCCP (赞：4)

题解里已经有一篇并查集的题解了，但是并不是我这种做法，所以特来写一篇题解，~~这样才对得起我调了一个下午的成果~~。当然了，那位dalao的解法比我的优很多（

## 思考过程

看到这道题，我们一眼顶真，发现和我们熟悉的[P3295 萌萌哒](https://www.luogu.com.cn/problem/P3295)以及[P1840 Color the Axis](https://www.luogu.com.cn/problem/P1840)很像啊。

为什么这么说呢，题目给定了我们一些关系，两个人之间有连系就可以把这两个人分开来，但是这两个一定会分开了吗？不一定！考虑下图这么一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/cbdw7aeg.png)

其中点 2 和点 4 有联系，那么可以把他们分开来吗？不可以，因为 3 与 2 和 4 均没有联系。

在此前的诸多题目里，我们应该养成了正反向同时思考的习惯，事物存在对立的这一面，就一定存在对立的另一面。我们考虑建立补图，发现没有联系的两人是必须在同一栋楼里的，不理解的同学请去回顾题意。

我们得到这么一种暴力的做法：建立补图后求连通块数量，图论做法的时间复杂度为 $ O(n^2-m) $ ，而并查集做法还要带个反阿克曼函数。以本题的数据范围，这是不可接受的。

我们不免去思考如何优化建图，但是这是和连通块相关的题，放着并查集不想，何必煞费苦心去想优化建图呢！~~有50块钱的好兄弟填线，要什么T-90（~~

发现给定关系的数量比较少，考虑把给定关系排序（注意：要求同一点对内第一关键字比第二关键字小，就像普通建图一样）。这样对于同一第一关键字来说，连续的少量的第二关键字把 $ 1 - n $ 的范围划分成了几个少量的大区间。我们只要维护区间和点之间的连通关系即可。

这样一来就和我们前面说到的两道题有些相似之处了：维护一段区间和一个点的连通关系。

## 蒟蒻的做法

看到区间问题，想到线段树，一个点即可代表一个区间，符合我们对并查集维护点与点之间的关系的幻想。按以下过程即可通过本题：

- 预处理区间节点，每一个节点的父亲就是他之间的编号；

- 将给定关系排序，划分区间；

- 像修改线段树一样将代表范围区间内的节点与代表原本的一个人的叶子节点合并；

- 结束后，自上而下遍历，对于每一个非叶子节点，如果当前节点被划分到一个不同于本身的集合，那么将两个儿子节点同当前节点合并；

- 最后对于每一个叶子节点，找到其祖宗节点，统计答案即可。

时间复杂度：预期为 $ O(m\log_2{n}\alpha(n)) $ ，不是很优，但是仍可以一半左右的时间和四分之一左右的空间通过本题。

## 正确性

- 在这里，我们建的线段树并不是普通的线段树，我们不需要线段树维护什么，只需要它划分区间，因此并不是一种从属的父子节点的关系，只有包含与被包含的关系，在并查集中一个节点的父亲节点是它本身，而不是线段树里的父亲节点吗，因此不会所有节点一开始就都被连通到一起去。

- 存在一种情况，某区间内存在独立点，而剩下的则有划分：自上而下遍历时，如果一个非叶子结点对应的区间是不完全的，不合并两个子节点即可。

## tips:

 同时有路径压缩和按秩合并的并查集的时间复杂度才是 $ O(m\alpha(n)) $ ，只有路径压缩的并查集， Tarjan 证明其最劣时间复杂度是 $ O(m\log_2{n}) $ ，姚期智证明了其平均复杂度是 $ O(m\alpha(m,n)) $ ，按秩合并比较难写，可以使用启发式合并代替，时间复杂度和按秩合并是一样，这里不证明了。

实测有启发式合并比没有快了 0.05s :(

------------

具体见代码：
 
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
const int N=3e5+10;
const int M=3e6+10;
int n,m,fa[M],siz[M],seq[N],maxn,cnt[N];
struct node{
	int x,y;
}p[M];
vector<int> ple[N];
set<int> q;
multiset<int> res;
inline bool cmp(node a,node b){
	if(a.x==b.x){
		return a.y<b.y;
	}
	return a.x<b.x;
}
inline int find(int x){
	//查找root 
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
inline void hb(int fx,int fy){
	//启发式合并 
	if(siz[fx]<siz[fy]){
		swap(fx,fy);
	}
	siz[fx]+=siz[fy];
	fa[fy]=fx;
}
inline void build(int x,int l,int r){
	//建树 
	maxn=max(maxn,x);
	if(l==r){
		seq[l]=x;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
inline void ycl(){
	//预处理 
	build(1,1,n);
	for(int i=1;i<=maxn;i++){
		fa[i]=i;
		siz[i]=1;
	}
}
inline void unify(int x,int l,int r,int ql,int qr,int k){
	//普通线段树修改式遍历 
	if(ql<=l&&r<=qr){
		int fy=find(x),fx=find(seq[k]);
		//不同才合并，节省时间 
		if(fx!=fy){
			hb(fx,fy);
		}
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid){
		unify(x<<1,l,mid,ql,qr,k);
	}
	if(qr>mid){
		unify(x<<1|1,mid+1,r,ql,qr,k);
	}
}
inline void prepare(int x,int l,int r){
	int fx=find(x),fy;
	if(fx!=x&&l!=r){
		fy=find(x<<1);
		if(fy!=fx){
			hb(fx,fy);
		}
		fy=find(x<<1|1);
		if(fy!=fx){
			hb(fx,fy);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	ycl();
	int x,y;
	//输入 
	for(int i=1;i<=m;i++){
		scanf("%d%d",&p[i].x,&p[i].y);
		if(p[i].x>p[i].y){
			swap(p[i].x,p[i].y);
			//保证第一关键字比第二关键字小 
		}
	}
	//排序 
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;i++){
		ple[p[i].x].push_back(p[i].y);
	}
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		int len=ple[i].size();
		l=0;
		if(!len){
			if(i+1<=n){
				unify(1,1,n,i+1,n,i);
			}
			continue;
		}
		for(int j=0;j<len;j++){
			if(j!=0){
				l=ple[i][j-1]+1;
			}
			r=ple[i][j]-1;
			if(r<=i||l>r){
				//不能和比自己小的区间合并，因为第一关键字比第二关键字小，无法确定关系 
				continue;
			}
			if(l<=i){
				//同上 
				l=i+1;
			}
			unify(1,1,n,l,r,i);
		}
		if(ple[i][len-1]+1<=n){
			//小学奥数的植树问题的原理 
			unify(1,1,n,ple[i][len-1]+1,n,i);
		}
	}
	//全树合并 
	prepare(1,1,n);
	for(int i=1;i<=n;i++){
		//一个一个找root 
		x=find(seq[i]);
		q.insert(x);
		cnt[x]++;
	}
	//输出答案 
	y=q.size();
	printf("%d\n",y);
	set<int>::iterator it;
	for(it=q.begin();it!=q.end();it++){
		res.insert(cnt[*it]);
	}
	multiset<int>::iterator item;
	for(item=res.begin();item!=res.end();item++){
		printf("%d ",*item);
	}
}
```
这么良心的题解，不点个赞再走吗？

---

## 作者：zhwzzhhww (赞：4)

首先对这个题目的一句话翻译...已经把问题说的很明显了......

**给出一个图（N个点，M条边），让你把此图分成尽可能多的集合，满足任意不在同一集合的点之间都有边相连。**


考虑 若一个点与其她某一个点没有连边，那么她们一定会在一个集合里。如果建立补图（原图中存在的边变成不存在，不存在的边变成存在）， 那么需要被分在一个集合里，即原图中没有连边的两个点，现在在补图中都有了连边。

为了保证最优性，只需在补图中找联通块个数就好了。理由是如当前联通块没有连边的点，若只保证正确则可以与当前联通块归为一个集合，但为了保证最优，每个联通块自成一个集合就好了。

这个思路是正确的，然而瓶颈在于补图的建立上，如果硬建图的话会有原题中$N * N - M$ 条边，$m$不管怎么取都是存不下的。

再看思路，只需求得联通块中点的数目以及联通块个数，所以如果把在补图中一定会相连的点缩成一个点，把点的数目降低，那么就可以通过建反图再dfs什么的一顿乱搞就好。

边数很多，不能遍历很多遍，缩点又需要看边，所以考虑只缩一个点。补图中相连即原图中不相连，又只缩一个点，那么缩的这个点在原图中需要度数最小。
考虑最坏情况：如果点少边少，明显不会有影响。如果点多边少，不存在的边就会变多，也不会有影响。只有让最小度最大才会影响的最终点数。所以当点少边多的时候，平均每个点的度数都很大，边最多$2 000 000$， 点最少少到1500左右($\sqrt{2}$大约$1.4$)，再没有意义，再大边数限制在了$M$，所以缩完点后可以直接邻接矩阵存，再补图联通什么的胡搞就行

具体看代码，如下：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
const int N = 100010, M = 2000010;

struct node
{
	int v, next;
}e[ M ];

pair < int, int > links[ M ];
//超级点编号为1
int head[ N ], vis[ N ], cnt = 1, tot, father[ N ], ind[ N ], ans, named[ N ], print[ N ], printcnt;//cnt与named记录新点编号以及与旧点的对应关系
int g[ 1500 ][ 1500 ], G[ 1500 ][ 1500 ];//g缩点后原图，G补图

inline void add_edge( int u, int v )
{
	tot ++;
	e[ tot ].v = v;
	e[ tot ].next = head[ u ];
	head[ u ] = tot;
}

void dfs( int cur )
{
	if( vis[ cur ] )
		return ;
	vis[ cur ] = 1;
	
	ans ++;
	
	for( int i = 1 ; i <= cnt ; i ++ )
		if( G[ cur ][ i ] )
			dfs( i );
}

int main()
{
	int n, m;
	scanf( "%d%d", &n, &m );
	for( int i = 1 ; i <= m ; i ++ )
	{
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
		links[ i ].first = u;//存边
		links[ i ].second = v;
		ind[ u ] ++;//记录度数
		ind[ v ] ++;
	}
	
	int mind = INF, id = 0;
	
	for( int i = 1 ; i <= n ; i ++ )
		if( ind[ i ] < mind )
			mind = ind[ i ],
			id = i;//超级点get~
	
	for( int i = 1 ; i <= n ; i ++ )
		father[ i ] = i;//并不用于并查集！！
	
	for( int i = head[ id ] ; i ; i = e[ i ].next )
	{
		int v = e[ i ] .v;
		vis[ v ] = 1;
	}
	
	int weight = 1;
	for( int i = 1 ; i <= n ; i ++ )//找到补图中必定会与超级点相连的点
		if( ! vis[ i ] && i != id )//即与超级点没有直接相连的点
			father[ i ] = id,
			weight ++;//超级点包含的点，包括自己
	
	memset( vis, 0,sizeof( vis ) );
	
    //注意：若一个点要与超级点有连边，即要与超级点中所有点都有连边，这样才能保证补图中该点与超级点一定不在一个联通块中
    //这里处理方法为：若一个点与超级点的包含节点（即father[ cur ] = id）相连，那么就记录改点个数++，若个数为weight，则改点与包含点全部相连，就将原图超级点与该点相连。顺便处理了编号问题
	for( int i = 1 ; i <= m ; i ++ )
	{
		if( father[ links[ i ].first ] == id && father[ links[ i ].second ] == id )
			continue;
		if( father[ links[ i ].first ] == id )
			vis[ links[ i ].second ] ++;
		else if( father[ links[ i ].second ] == id )
			vis[ links[ i ].first ] ++;
		else 
		{
			if( ! named[ links[ i ].first ] )
			{
				cnt ++;
				named[ links[ i ].first ] = cnt;
			}
			if( ! named[ links[ i ].second ] )
			{
				cnt ++;
				named[ links[ i ].second ] = cnt;
			}
			
			g[ named[ links[ i ].first ] ][ named[ links[ i ].second ] ] = 1;
			g[ named[ links[ i ].second ] ][ named[ links[ i ].first ] ] = 1;
		}
	}
	
	for( int i = 1 ; i <= n ; i ++ )
		if( vis[ i ] >=weight )
		{
			if( ! named[ i ] )
			{
				cnt ++;
				named[ i ] = cnt;
			}
			g[ 1 ][ named[ i ] ] = 1;
			g[ named[ i ] ][ 1 ] = 1;
		}
	
    //补图
	for( int i = 1 ; i <= cnt ; i ++ )
		for( int j = 1 ; j <= cnt ; j ++ )
		{
			if( i == j ) continue;
			
			if( g[ i ][ j ] )
				G[ i ][ j ] = 0;
			else 
				G[ i ][ j ] = 1;
		}
	
	memset( vis, 0, sizeof( vis ) );
	
    //联通块
	for( int i = 1 ; i <= cnt ; i ++ )
		if( ! vis[ i ] )
		{
			ans = 0;
			dfs( i );
			
			printcnt ++;
			if( i == 1 )
				ans = ans + weight - 1;
			print[ printcnt ] = ans;
		}
	
	sort( print, print + printcnt + 1 );
	
	printf( "%d\n", printcnt );
	for( int i = 1 ; i <= printcnt ; i ++ )
		printf( "%d ", print[ i ] );
	
	return 0;
}
```

---

## 作者：xcrr (赞：3)

从直接搜索的角度优化。

#### 题意

给 $n$ 个点的完全图，给定 $m$ 条边不能走，问连通块个数。

#### 朴素

从朴素做法来想，直接广搜。

想其更新新点的流程（以下简称“流程”），是对于出队的点 $u$，找到它所有连边，如果连边对应的点没有被访问过，即没被 $vis$ 数组标记，那么就将它进队。

复杂度 $O(n+e)$ ，$n$ 是点数，$e$ 是边数。

过不了，只因这个题 $e$ 与 $n^2$ 同阶的特点。

#### 优化

上面提到的流程是我们复杂度的瓶颈，想想在这个题下我们如何优化。

输入的边，代表在图中删掉了这条边。

因为大部分边都能走，就相当于 $u$ 除了删掉的边对应的点外，其余 $v=1 \to n$ 都可直达。

由于不能直达的点相对很少，
流程就变成了对于 $u$，扫一遍（除了被删的点，剩余的）整个 $vis$ 数组，找到 $vis$ 没有被标记的点，进入队列。

似乎很好优化了？用链表或并查集跳过 $vis$ 标记过的点，不扫它们不就行了，均摊下来就 $O(n)$ 了。

细节在于，如何处理扫 $vis$ 数组时跳过被删的点？我们可以将每个点 $u$ 预处理出可达区间，区间之间不包含的部分就是相对 $u$ 而言删掉的点，也就是 $u$ 出队时扫 $vis$ 跳过的点。处理好这个，流程中，我们对每个区间分别做即可。

举个例子

若 $n=100$：

$1$ 号节点举例，原可达区间 $[2,100]$。

若加入 $u=1,v=5$，对 $1$ 号来说就是删掉了 $5$ 号，$1$ 号的可达区间变为 $[2,4],[6,100]$。

若再加入 $u=1,v=20$，$1$ 号的可达区间变为 $[2,4],[6,19],[21,100]$。

以此类推。注意上面只是拿 $1$ 号点举例。处理时要对每个点处理，比如对 $3$ 而言第一个读入就是删掉了 $1$。

这部分不是重点，但是可能有点抽象，可以直接读代码帮助理解。

```cpp
#define pr make_pair
int fa[N],c[N];
int getfa(int x){if(x>n)return x;return fa[x]==x?x:fa[x]=getfa(fa[x]);}
vector<int>G[N];//暂时存储删掉的边
vector<pair<int,int> >v[N];
int bfs(int x)
{
	int ret=0;
	queue<int>q;
	q.push(x);
	fa[x]=x+1;
	while(q.size())
	{
		int nq=q.front(); q.pop();
		ret++;
		for(auto rg:v[nq])//对每个可达区间分别做
		{
			int l=rg.first,r=rg.second;
			for(int i=getfa(l);i<=r;i=getfa(i))
			q.push(i),fa[i]=i+1;
		}
	}
	return ret;//返回连通块大小
}
inline void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i,G[i].push_back(i);
	for(int i=1,u,v;i<=m;i++)
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<=n;i++)//处理删边
	{
		sort(G[i].begin(),G[i].end());
		int l=1;
		for(auto cc:G[i])
		{
			if(l<=cc-1) v[i].push_back(pr(l,cc-1));
			l=cc+1;
		}
		if(l<=n) v[i].push_back(pr(l,n));
	}
	vector<int>ans;
	for(int i=1;i<=n;i=getfa(i))
	ans.push_back(bfs(i));
	cout<<ans.size()<<endl;
	sort(ans.begin(),ans.end());
	for(auto p:ans) cout<<p<<' '; 
}
```

---

## 作者：Tsukimaru (赞：3)

**前言**：前面的各位已经提出了 $O(n + m)$ 的优秀解法。此处，我提供一个 $O(n \cdot \alpha(n) + m)$ 的较为 Trival 的并查集解法。

**题目转换**：给出一个 $n$ 个点的无向完全图，删掉其中的 $m$ 条边，求连通块个数。

**解法**：对于某个点 $u$，我们可以知道与 $u$ 不相连的点 $v$ 的集合 $S$。不难发现，我们可以把它变为：**将点 $u$ 与某个区间 $[l, r]$ 内的点合并**。

合并的过程就是非常 Trival 的并查集了。此处可参见 51Nod 1525 重组公司。

**实现**：对于每条删去的边，都有 $u_i < v_i$。我们使用基数排序 $O(m)$ 对每条边按照 $u_i$ 从小到大排序，对于同样的 $u_i$ 则按 $v_i$ 从小到大排序，即可得到与 $u$ 不相连的点 $v$ 的集合 $S$。合并过程使用带按秩合并和路径压缩的并查集，可做到 $O(n \cdot \alpha(n) + m)$。

**时间复杂度**：$O(n \cdot \alpha(n) + m)$。

**附注**：如果你程序常数够小的话，排序部分使用 `std::sort` 可能可以通过；但这样时间复杂度就会变为 $O(n \cdot \alpha(n) + m \log m)$，不够优秀。

---

## 作者：Freeyer (赞：2)

给出一个图（N个点，M条边），让你把此图分成尽可能多的集合，满足任意不在同一集合的点之间都有边相连。

题意已经十分明确了，一开始可以想到建出图的补图，然后求出图的联通块个数。直接建补图可能会炸掉（0<m<=2000000）,于是就有了下面的bfs做法。

首先，根据题意有一个~~显然~~的推论：若两个点之间没有边相连，则一定属于同一集合。根据这个推论，我们可以愉快地进行bfs

g：存图

h：不需要加入当前集合的点

s：还未被分配到其他集合的点

b：判断是否被访问过（bfs判重）

每次选取一个未被访问的点，若其他点与他没有边相连则与他同属一个集合，并加入该点集合。直到所有点都被加入集合。
复杂度大约O（n+m）

统计完答案后，记得排序后再输出


```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=100006,maxm=200004;
int x,y,n,m,head[maxn],to[maxm*2],nxt[maxm*2],cnt,b[maxn],v[maxn],h[maxn];
vector<int> s;
vector<int> res;
vector<int> g[maxn];
int bfs(int x)
{
    int tot=0;
    queue<int> q;
    q.push(x);
    h[x]=1;
    while(!q.empty())
    {
        int k=q.front();
        b[k]=1;tot++;q.pop();
        for(int i=0;i<g[k].size();++i)
        	h[g[k][i]]=1;//与当前点有边的点不需要被拓展，进行标记
        vector<int> tmp=s;s.clear();
        for(int i=0;i<tmp.size();++i)
        {
            if(h[tmp[i]]) s.push_back(tmp[i]);//重新加入待拓展节点
            else q.push(tmp[i]);
        }   
        for(int i=0;i<g[k].size();++i)
        	h[g[k][i]]=0;  
    }
    return tot;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i=1;i<=n;++i)
        s.push_back(i);
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0)
			res.push_back(bfs(i));//统计答案
    }
    cout<<res.size()<<endl;
    sort(res.begin(),res.end());
    for(int i=0;i<res.size();++i)
        printf("%d ",res[i]);
    return 0;
}
```


---

## 作者：Resurgammm (赞：1)

> 给定一张 $n$ 个点 $m$ 条边的图，求补图的连通块个数以及各个连通块的大小

有个 $\text{naive}$ 的想法就是直接暴力建出补图然后去跑，但是这样边数是 $n^2$ 级别的，显然会 $\text{T}$。

发现只需要知道每个连通块的信息，所以可以考虑建出生成树。

考虑 $\text{BFS}$ 树，枚举一个没有被标记过的点 $u$ 标记它并把它加入到队列，先把它在 **原图** 直接相邻的点标记，然后将它在 **补图** 上相邻且没有被标记过的点 $v$ 标记并放入队列。

可以直接用链表直接维护出来这个 $v$。

这样每个点在链表中只会被遍历一遍，且这么做枚举仅涉及到树边，而对 $u$ 枚举在原图上相邻的点也只等于枚举原图上的边的复杂度，所以总复杂度是 $O(n+m)$ 的。

[双倍经验](https://www.luogu.com.cn/problem/P4833)

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long 
#define ull unsigned long long
#define fir first
#define sec second
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	#define fill(a,b,c,d) memset(a,b,sizeof(c)*(d+1))
	#define copy(a,b,c,d) memcpy(a,b,sizeof(c)*(d+1))
	#define fillall(x,y) memset(x,y,sizeof(x))
	#define copyall(x,y) memcpy(x,y,sizeof(x))
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<1)+(w<<3)+(ch^48); ch=getchar();}
		return w*f;
	}
}
using namespace IO;
namespace CL{

	const int maxn=1e5+5,maxm=2e6+5;

	int n,m,top;
	int stk[maxn];
	bool vis[maxn],org[maxn];
	queue<int> q;
	namespace Graph{
		int head[maxn],id;
		struct e{int v,next;}edge[maxm<<1];
		inline void add(int u,int v){
			edge[++id]=(e){v,head[u]};
			head[u]=id;
		}
	}using namespace Graph;
	namespace list{
		int pre[maxn],nxt[maxn];
		inline void init(){
			nxt[0]=1;
			for(int i=1;i<n;i++) pre[i+1]=i,nxt[i]=i+1;
		}
		inline void del(int x){pre[nxt[x]]=pre[x],nxt[pre[x]]=nxt[x];}
	}using namespace list;

	inline int main(){
		n=read(),m=read();
		for(int i=1;i<=m;i++){
			int x=read(),y=read();
			add(x,y),add(y,x);
		}
		init();
		for(int i=1;i<=n;i++) if(!vis[i]){
			vis[i]=1,stk[++top]=1;
			del(i),q.push(i);
			while(!q.empty()){
				int u=q.front(); q.pop();
				for(int j=head[u];j;j=edge[j].next){
					int v=edge[j].v;
					if(!vis[v]) org[v]=1;
				}
				for(int j=nxt[0];j;j=nxt[j]){
					if(!org[j]){
						vis[j]=1,stk[top]++;
						del(j),q.push(j);
					}
					else org[j]=0;
				}
			}
		}
		sort(stk+1,stk+1+top);
		printf("%d\n",top);
		for(int i=1;i<=top;i++) printf("%d ",stk[i]); puts("");
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：orangejuice (赞：1)

5098: [BZOJ1098][POI2007]办公楼biu
-----------------------------------
没有数据结构就很棒

一个看上去非常玄学的代码
```cpp
const int N=1e5+10,M=2e6+10;
  
int n,m;
int fa[N];
int Find(int x){ return fa[x]==x?x:fa[x]=Find(fa[x]); }
  
vector <int> G[N];
typedef vector <int> ::iterator iter;
  
  
void merge(int x,int y){
    x=Find(x),y=Find(y);
    if(x==y) return;
    vector <int> tmp;tmp.clear();
    if(G[x].size()>G[y].size()) swap(x,y);
    int p=0;
    for(reg int i=0;i<(int)G[x].size();i++){
        while(p<(int)G[y].size()&&G[y][p]<G[x][i]) p++;
        if(p>=(int)G[y].size()||G[y][p]!=G[x][i]) {
            tmp.push_back(G[x][i]);
            G[x].erase(G[x].begin()+i);
            i--;
        } 
    }
    fa[y]=x;
    rep(i,0,tmp.size()-1) merge(x,tmp[i]);
}
  
int cnt[N];
int ans[N],ac;
bool go[N];
  
  
  
void Sort(vector <int> &V){
    if(V.size()<20000) return sort(V.begin(),V.end());
    memset(go,0,sizeof go);
    rep(i,0,V.size()) go[V[i]]=true;
    V.clear();
    rep(i,1,n) if(go[i]) V.push_back(i);
}
 
int num[N]; 
 
bool cmp(int x,int y){
    return G[x].size()<G[y].size();
}
  
int main(){
    n=rd(),m=rd();
    rep(i,1,n) fa[i]=num[i]=i;
    rep(i,1,m) {
        int u=rd(),v=rd();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    rep(i,1,n) Sort(G[i]);
    sort(num+1,num+n+1,cmp);
    rep(i,1,n) if(Find(num[i])==num[i]) {
        memset(go,0,sizeof go);
        rep(j,0,G[num[i]].size()-1) go[G[num[i]][j]]=1;
        rep(j,1,n) if(num[i]!=j&&!go[j]) merge(num[i],j);
    }
    rep(i,1,n) cnt[Find(i)]++;
    rep(i,1,n) if(cnt[i]) ans[++ac]=cnt[i];
    sort(ans+1,ans+ac+1);
    printf("%d\n",ac);
    rep(i,1,ac) printf("%d",ans[i]),putchar(i==ac?'\n':' ');
}
  
```
我这个代码大概是在讲这样的:

按照出度排序,没有连边的点必须合并,最后找集合个数

但是合并的时候要注意用y的答案更新x,这样y就不用再跑一次了~~(这里的总复杂度较为诡异)~~

更新过程:遍历x的边,如果y的边中没有x的这条边,那么就将其删去,并且将这个点合并

-----------

首先根据鸽巢原理,出度最小的点最大出度必然是$\frac{m}{n}$

它的边数也是$\frac{m}{n}$

每次和其他的点合并,这个复杂度是 $\frac{m}{n} \cdot m$ (事实上是远远跑不到的!因为每次都会删去大量的边!)

所以哪,是不会T的

然后由于合并完之后也就剩下不到$\frac{m}{n}$个点了,所以这里就算你暴力$O(n)$合并也没关系

最后是你们担心的$\frac{m}{n} \cdot m$会TLE

瞪眼一看当$m=2e6,n$较小时就T了

哪你n较小时直接跑$O(n^2)$不就是了 ~~吐舌头~~

注意时限是20s的这个代码还根本跑不满,所以自然不用担心!

tips: vector可以用链表优化更棒



---

## 作者：帅到报警 (赞：1)

	【问题描述】
神牛 LXX 昨天刚刚满 18 岁，他现在是个成熟的有为男青年。他有 N 个 MM，分别从 1 到 N 标号。
这些 MM 有些是互相认识的。现在，LXX 为了处理和 MM 们复杂的关系，想把他们划分成尽量多的集合，
要求任意两个属于不同集合的 MM 都必须互相认识。这样方便交流。现在 LXX 想知道最多可以分成多
少个集合，每个集合的人数是多少。

	【输入】
输入第一行是两个数 N 和 M。
接下来 M 行，每行两个数，表示这两个 MM 是互相认识的。


	【输出】
第一行一个数 S，表示最多有多少个集合。
第二行 S 个数，从小到大，表示每个集合的人数。

	【分析】
本来以为可以用vector通过存反边，再排序边的数量后从大到小删边，直到所有边都从集合删除后便可得到答案。但发现WA了一个点……内存会炸！！

然后发现用过BFS更加省时省空间，大致就是用BFS和队列，把一组无边的点放入，删边，再找边。。。

**完整代码如下：**
```cpp
#include <stdio.h>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100010;
int n, m;
vector <int> edge[N];
int top, nt, cnt, ans;
int q[N], st[N], num[N], mark[N];
int main()
{
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int tmp1, tmp2;
		scanf("%d %d", &tmp1, &tmp2);
		edge[tmp1].push_back(tmp2);
		edge[tmp2].push_back(tmp1);
	}
	top = n;
	for(int i = 1; i <= n; i++)
		q[i] = i;
	while(top)
	{
		ans++;
		cnt++;
		st[nt = 1] = q[top--];
		while(nt)
		{
			num[ans]++;
			int x = st[nt--];
			cnt++;
			for(vector<int>::iterator i = edge[x].begin(); i != edge[x].end(); ++i)
				mark[*i] = cnt;
			int top0 = top;
			top = 0;
			for(int i = 1; i <= top0; i++)
			{
				int x = q[i];
				if(mark[x] != cnt)
					st[++nt] = x;
				else
					q[++top] = x;
			}###### 
		}
	}
	
	printf("%d\n", ans);
	sort(num + 1, num + ans + 1);
	for(int i = 1; i <= ans; i++)
		printf("%d ", num[i]);

	return 0;
}
```
总的来说，这种题目不用并查集就用广搜试…………

---

## 作者：Fzrcy (赞：0)

> 简要题意：给你一个无向图 $(V,E)$，将点集划分为若干个子集，使得对于任意的两个点 $x,y$，且 $x$ 和 $y$ 不在同一个集合中，满足 $x$ 和 $y$ 有连边，求点集最多可以划分为多少个子集，及其方案。

先对无向图的边集 $E$ 取反得到 $E'$，显然在 $E'$ 中有连边的两个点必须在同一个集合中，所以答案为反图的连通块数和所有连通块的大小。

我们用一个链表维护未删去的点的集合，初始为 $\{1,2,\dots,n\}$，进行以下操作直到链表为空。

- 从链表中选出任意一个点 $s$ 加入拓展队列，并从链表中删去，并进行以下操作：
- 1. 从拓展队列中选出一个点 $x$，并删去。
- 2. 将所有与 $x$ 相连的点标记。
- 3. 暴力遍历链表将未标记的点加入拓展队列并从链表中删去，然后将有标记的点的标记删去。
- 则反图中 $s$ 所在的连通块的大小为点加入拓展队列的次数。

因为操作 2 的时间复杂度为 $O(m)$、操作 3 的时间复杂度为 $O(n+m)$（最多只有 $m$ 次是只枚举且不从链表中删去）。

所有总时间复杂度为 $O(n+m)$。

```cpp
// qwq
#include <bits/stdc++.h>
using namespace std;
constexpr int N=2e5+6;
int Vis[N],ans,A[N],ban[N];
int n,m,pr[N],nxt[N];
vector<int>e[N];
queue<int> q;
void D(int x){
    nxt[pr[x]]=nxt[x];
    pr[nxt[x]]=pr[x];
}
int main(){
    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++)
        cin>>x>>y,e[x].push_back(y),
        e[y].push_back(x);
    for(int i=1;i<n;i++)
        pr[i+1]=i,nxt[i]=i+1;
    nxt[0]=1;
    for(int i=1;i<=n;i++)if(!Vis[i]){
        A[++ans]=1,q.push(i),Vis[i]=1,D(i);
        while(!q.empty()){
            int u=q.front();q.pop();Vis[u]=1;
            for(int v:e[u])ban[v]=1;
            for(int j=nxt[0];j;j=nxt[j])
                if(!ban[j])D(j),Vis[j]=1,++A[ans],q.push(j);
                else ban[j]=0;
        }
    }
    sort(A+1,A+ans+1);
    cout<<ans<<'\n';
    for(int i=1;i<=ans;i++)
        cout<<A[i]<<' ';
    return 0;
}
```

---

## 作者：Ameiyo (赞：0)

# 对 orangejuice9 的思想所提供的另一种方法

RT

他的做法在 [这里](https://www.luogu.org/blog/1to2to3to4/bzoj1098poi2007-ban-gong-lou-biu)

这里就只提供另一种做法，并且对复杂度进行优化。

没错这是一道神题，原图中连了的边是“__可分可不分__”，到了补图里（那些原图中没连的边）就变成了“__必须有__”。这是最关键的一点。（然而根本想不到）

__但是这样的话每个点要连的边还是很多啊？__

于是乎抽屉原理引出的“超级点”就出现了。

然后每次把必须在一起的点合并到一起，用广搜扩展，每次只找还没被搜过的点，所以链表就很棒了。

感觉复杂度怪怪的，如果放大了讲的话就是 $ O(\frac {m} {n} \times m) $ ，但是其实并没有这么大，因为每个点找了之后会删掉很多点，而且数据也挺水的。。。

事实上，因为每次删点的时候要把联通块里的点都删掉，而和超级点连着的点非常多，直接搜碰到超级点的概率非常大，所以就算一开始没找它也不会TLE。

代码没什么细节，因为有第二问的存在，所以要用并查集统计，不然每次合并时答案减一就行了。

```cpp

#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ll long long
#define reg register
#define rep(i, a, b) for (reg int i = (a), i##end = (b); i <= i##end; ++i)
#define dep(i, a, b) for (reg int i = (a), i##end = (b); i >= i##end; --i)

template <typename _typer> inline _typer read() {
	_typer init = 0;
	char ch = getchar(), k = 0;
	for ( ; !isdigit(ch); ch = getchar()) k = (ch == '-');
	for ( ; isdigit(ch); ch = getchar())
		init = (init << 3) + (init << 1) + (ch ^ 48);
	return k ? -init : init;
}
const ll N = 100005, INF = 1e9;
const ll M = 2000005;

/*******************************************************************************
 *
 * v73: E
 * 根据抽屉原理，度数最小的点度数最大是 m / n，那么第一次去掉后
 * 剩下的点只有 m / n ，对于这些点，每次暴力找补图，这里是 O(n) 的，
 * 那么总的复杂度就是 O(m / n * n) = O(m)
 * 用上链表之后就是 O(m / n * (n - m / n)) = O(m - (m / n) ^ 2)
 *
 ******************************************************************************/

int n, m;
int mark[N];

struct EDGE {
	int to, nex;
} edge[M << 1];
int head[N], cntedge, In[N];
void Addedge(int u, int v) {
	edge[++cntedge] = (EDGE) { v, head[u] };
	head[u] = cntedge, ++In[v];
}

int pre[N], nxt[N], isDel[N];
void Del(int x) {
	nxt[pre[x]] = nxt[x];
	pre[nxt[x]] = pre[x];
	isDel[x] = true;
}

int Fa[N], Siz[N];
int Find(int x) {
	return x == Fa[x] ? x : Fa[x] = Find(Fa[x]);
}
void Uni(int x, int y) {
	x = Find(x), y = Find(y);
	if (x != y) {
		Fa[x] = y;
		Siz[y] += Siz[x];
	}
}

int li[N], Q[N], l, r;
void Work(int u) {
	Del(u);
	l = r = 0;
	Q[++r] = u;
	while (l < r) {
		u = Q[++l];
		for (reg int i = head[u]; i; i = edge[i].nex)
			mark[edge[i].to] = true;
		for (reg int i = nxt[0]; i; i = nxt[i]) if (!mark[i])
			Del(i), Uni(i, u), Q[++r] = i;
		for (reg int i = head[u]; i; i = edge[i].nex)
			mark[edge[i].to] = false;
	}
}

int main() {
	n = read<int>(), m = read<int>();
	rep (i, 1, m) {
		int x = read<int>(), y = read<int>();
		Addedge(x, y); Addedge(y, x);
	}

	int id = 0; In[0] = INF;
	rep (i, 1, n) {
		if (In[id] > In[i])
			id = i;
		pre[i] = i - 1;
		nxt[i] = i + 1;
		Fa[i] = i, Siz[i] = 1;
	}
	nxt[0] = 1, nxt[n] = 0;

	Work(id);
	rep (i, 1, n) if (!isDel[i]) {
		Work(i);
	}

	rep (i, 1, n) if (Fa[i] == i) {
		li[++li[0]] = Siz[i];
	}
	sort(li + 1, li + li[0] + 1);

	printf("%d\n", li[0]);
	rep (i, 1, li[0]) {
		printf("%d%c", li[i], " \n"[i == li[0]]);
	}
	return 0;
}

```

于是这题就神仙的结束了。

最后膜拜 %%% [机房 巨佬](https://www.luogu.org/space/show?uid=130740) 的抽屉原理 orz orz orz








---

## 作者：荣一鸣 (赞：0)

这一道题，一开始想用并查集，一开始一切都挺好，结果第五个点TLE，然后就只能尽全力优化，后来又想到用bfs可以在很快的时间内过，然后就用bfs，还是T

最后只能用数组模拟链表来减少枚举已经过的点的时间。事实证明是成功的。

还有关于边的处理，求反图时由于边数太多，可以先用数组存下现在边的信息，反一下就行了。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
int vi[100010];
int pre[100010];
int next[100010];
vector<int> to[100010];
vector<int> tt;
vector<int> ti;
queue<int> q;
int n,m;
int head=0;

void ll(int i,int j){
	next[i]=j;
	pre[j]=i;
}//将中间某点删去

void bfs(int i){
	vi[i]=1;
	q.push(i);
	ll(pre[i],next[i]);
	int sum=1;
	while(!q.empty()){
		int u=q.front();
		int ff[100010];//ff用来标记已出现过的边
		memset(ff,0,sizeof(ff));
		q.pop();
		int a,b;
		for(int j=0;j<to[u].size();j++){
			ff[to[u][j]]=1;
		}
		for(int j=next[head];j<=n;j=next[j]){
			if(ff[j]==1) continue;
			q.push(j);
			ll(pre[j],next[j]);
			vi[j]=1;
			sum++;
		}
	}
	ti.push_back(sum);
}

int main(){
	freopen("biu.in","r",stdin);
	freopen("biu.out","w",stdout);
    scanf("%d%d",&n,&m);
    if(m<n-1){
        cout<<1<<endl<<n;
        return 0;
    }
	for(int i=1;i<=n;i++){
		pre[i]=i-1;
		next[i]=i+1;
	}
    for(int i=1;i<=m;i++){
        int f,t;
        scanf("%d%d",&f,&t);
        to[f].push_back(t);
        to[t].push_back(f);//临接表储存
    }
    for(int i=1;i<=n;i=next[i]){
        if(vi[i]==0) bfs(i);
    }
    printf("%d\n",ti.size());
    sort(ti.begin(),ti.end());
    for(int i=0;i<ti.size();i++){
        cout<<ti[i]<<" ";
    }
    return 0;
}	
```

---

## 作者：kczno1 (赞：0)

先随便选个点

那么所有和他没边的点必须分到同一个集合

重复这个操作

就能得到他所在集合至少的大小

显然剩下来的点越多集合才能越多

所以这个集合就是答案所要求的集合


具体实现

用一个队列q把所有存在的点存下来

然后选一个点加入队列now

将它所连接的所有点标记

然后枚举所有已存在的点

如果没有标记就加入now，并在q中删除

不断拿now的队首重复操作

时间O(n+m)


注意:将答案排序后输出

```cpp
#include<bits/stdc++.h>
using namespace std;

#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
#define pb push_back
#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=1e5+5;
vector<int>link[N];
int q[N],top;
int st[N],nt;
int mark[N],cnt;
int num[N];

int main()
{
    freopen("1.in","r",stdin);
    int n=read(),m=read();
    while(m--)
    {
        int x=read(),y=read();
        link[x].pb(y);link[y].pb(x);
    }
    
    top=n;
    rep(i,1,n)q[i]=i;
    
    int ans=0;
    while(top)
    {
        ++ans;
        st[nt=1]=q[top--];
        while(nt)
        {
            ++num[ans];
          int x=st[nt--];    
          ++cnt;
          for(vector<int>::iterator i=link[x].begin();i!=link[x].end();++i)
            mark[*i]=cnt;
          int top0=top;top=0;
          rep(i,1,top0)
          {
               int x=q[i];
               if(mark[x]!=cnt) st[++nt]=x;
               else q[++top]=x;
          }
        }
    }
    
    printf("%d\n",ans);
    sort(num+1,num+ans+1);
    rep(i,1,ans) printf("%d ",num[i]);
}
```

---

