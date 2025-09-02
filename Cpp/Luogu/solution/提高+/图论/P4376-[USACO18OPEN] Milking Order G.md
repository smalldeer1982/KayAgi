# [USACO18OPEN] Milking Order G

## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 10^5$），编号为 $1 \ldots N$，最近闲得发慌。因此，她们发展了一个与 Farmer John 每天早上为她们挤牛奶时的排队顺序相关的复杂社会阶层。

经过若干周的研究，Farmer John 对他的奶牛的社会结构总计进行了 $M$ 次观察（$1 \leq M \leq 50,000$）。每个观察结果都是某些奶牛的一个有序序列，表示这些奶牛应该按照序列中的顺序进行挤奶。例如，如果 Farmer John 的一次观察结果是序列 $2$、$5$、$1$，那么 Farmer John 应该在给奶牛 $5$ 挤奶之前的某个时刻给奶牛 $2$ 挤奶，并在给奶牛 $1$ 挤奶之前的某个时刻给奶牛 $5$ 挤奶。

Farmer John 的观察结果是按优先级排列的，因此他的目标是最大化 $X$ 的值，使得他的挤奶顺序能够符合前 $X$ 个观察结果描述的状态。当多种挤奶顺序都能符合前 $X$ 个状态时，Farmer John 遵循一个长期以来的传统——编号较小的奶牛的地位高于编号较大的奶牛，因此他会最先给编号最小的奶牛挤奶。更正式地说，如果有多个挤奶顺序符合这些状态，Farmer John 会采用字典序最小的那一个。挤奶顺序 $x$ 的字典序比挤奶顺序 $y$ 小，如果对于某个 $j$，$x_i = y_i$ 对所有 $i < j$ 成立，并且 $x_j < y_j$（即这两个挤奶顺序到某个位置之前完全相同，而在该位置上 $x$ 比 $y$ 小）。

请帮助 Farmer John 确定给奶牛挤奶的最佳顺序。

## 说明/提示

在这个例子中，Farmer John 有四头奶牛，他的挤奶顺序应该满足以下规则：奶牛 $1$ 在奶牛 $2$ 之前、奶牛 $2$ 在奶牛 $3$ 之前（第一个观察结果），奶牛 $4$ 在奶牛 $2$ 之前（第二个观察结果），奶牛 $3$ 在奶牛 $4$ 之前、奶牛 $4$ 在奶牛 $1$ 之前（第三个观察结果）。前两个观察结果可以同时被满足，但 Farmer John 不能同时满足所有规则，因为这会要求奶牛 $1$ 在奶牛 $3$ 之前，同时奶牛 $3$ 在奶牛 $1$ 之前。

这意味着总共有两种可能的挤奶顺序：$1\ 4\ 2\ 3$ 和 $4\ 1\ 2\ 3$，第一种是字典序较小的。

题目来源：Jay Leeds

## 样例 #1

### 输入

```
4 3
3 1 2 3
2 4 2
3 3 4 1```

### 输出

```
1 4 2 3
```

# 题解

## 作者：蒟蒻炒扇贝 (赞：22)

## 核心算法&前置知识：拓扑排序+二分
此题解默认大家已经掌握关于以上算法的基础知识。

~~同时也默认大家会链式前向星建图~~点进这题的大佬肯定都会。
### Part1：看题+手玩样例
遇到这种具有多种有关优先级条件的题，我们一般首先考虑按照他们的优先顺序进行建图，然后进行拓扑排序。

以本题样例为例，通过FJ的第一次观察结果可知，为奶牛们挤奶的优先级是 $1$ 号奶牛 $>$ $2$ 号奶牛 $>$ $3$ 号奶牛，那我们就考虑建造这一个有向无环图（DAG）（实际上就是条链）：

![](https://cdn.luogu.com.cn/upload/image_hosting/r1ml66ct.png)

那么结合FJ第二次观察的结果，优先级是 $4$ 号奶牛 $>$ $2$ 号奶牛，那么我们的图就变成了这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/u2tmxvyx.png)

如果你用此图来跑拓扑排序的话，那么拓扑序会有两个，分别是 $4\ 1\ 2\ 3$ 和 $1\ 4\ 2\ 3$。

那我们继续来结合FJ第三次观察的结果，此时我们的图变成了这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/m4761wdf.png)

这时候，我们的图出现了环，意味着有几个条件是互相矛盾的，所以此时这张图并没有拓扑序。

既然有环的时候无解，那我们还得判断这个图是否带环，那我们到底该怎么判断呢？

### Part2：拓扑排序黑科技：判环
我们以下面的这张有向有环图为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/doqvdp76.png)

我们来按照拓扑排序的流程走一遍：此时我们先删掉入度为 $0$ 的点（也就是 $1$ 号点），
现在这张图就成这样了：
![](https://cdn.luogu.com.cn/upload/image_hosting/f4fr0zzq.png)

此时所有的点入度都不为 $0$，也就是说，此时拓扑排序已经进行不下去了（没有任何点可以入队）。

我们知道，当这张图上所有的点都被删去时，拓扑排序才能进行下去，这也侧面说明这张图是一张有向无环图。如果拓扑排序进行不下去时，图上还有点没有被删，那么这张图一定是一张有环的图。

因此，我们只需要在拓扑排序结束之后，判断所有点的入度是否全部为 $0$，如果有不小于 $1$ 个点的入度不为 $0$，则这张图一定有环。

代码：
```cpp
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		for(int i=head[now];i;i=a[i].nxt)
		{
			int to=a[i].v;
			in[to]--;
			if(!in[to])q.push(to);
		}
	}
	int tot=0;
	for(int i=1;i<=n;i++)
		if(!in[i])tot++;
	if(tot<n)return false;
	return true;
```

那这个时候我们就有了一个非常暴力的思路，既然FJ想要使题目中的 $X$ 尽可能大，那我们就可以从 $[1,M]$ 暴力枚举出 $X$ 的最大大小（通过重新建图+判环），求出 $X$ 之后就可以愉快的用拓扑排序+优先队列来跑出这个答案序列了！

但这样做时间复杂度肯定是爆炸的，这是一个时间复杂度为平方级别的做法。

那我们该怎么优化呢？

### Part3：二分

一个显然的结论，如果一张图上有环，那么它无论加上任意数量条边，这张图依然会有环。如果一张图上无环，那么它无论删去任意数量条边，这张图必定没有环。

~~这不是废话吗。~~

所以我们发现，定义 $Y\in [1,X)$，定义 $Z\in (X,M]$，如果 $X$ 符合要求，那么 $Y$ 也必定符合要求。同样，如果$X$不符合要求，那么 $Z$ 也必定不符合要求。

这便说明，求 $X$ 的这个过程可以用二分来实现。

那这样我们就实现了这份暴力代码的优化。

### Part4：完整代码

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=1e5+5;
int n,m,cnt,head[MAXN],in[MAXN];
vector<int>v[MAXN];
struct edge
{
	int v,nxt;
}a[MAXN*2];
void addedge(int u,int v)
{
	a[++cnt].v=v;
	a[cnt].nxt=head[u];
	head[u]=cnt;
}
void build(int x)
{
	cnt=0;
	memset(head,0,sizeof(head));
	memset(in,0,sizeof(in));
	for(int i=1;i<=x;i++)
	for(int j=0;j<v[i].size()-1;j++)
	{
		addedge(v[i][j],v[i][j+1]);
		in[v[i][j+1]]++;
	}
}
int check(int x)
{
	build(x);
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		for(int i=head[now];i;i=a[i].nxt)
		{
			int to=a[i].v;
			in[to]--;
			if(!in[to])q.push(to);
		}
	}
	int tot=0;
	for(int i=1;i<=n;i++)
		if(!in[i])tot++;
	if(tot<n)return false;
	return true;
}
void get_ans(int x)
{
	build(x);
	priority_queue<int,vector<int>,greater<int> >q;//使用优先队列 保证这个拓扑序的字典序最小
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int now=q.top();
		q.pop();
		cout<<now<<" ";
		for(int i=head[now];i;i=a[i].nxt)
		{
			int to=a[i].v;
			in[to]--;
			if(!in[to])q.push(to);
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int si;
		cin>>si;
		for(int j=1;j<=si;j++)
		{
			int x;
			cin>>x;
			v[i].push_back(x);
		}
	}
	int l=1,r=m;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))l=mid+1;
		else r=mid-1;
	}
	int ans;
	for(ans=r;ans<=l;ans++)if(check(ans))break;
	get_ans(ans);
	return 0;
}
```

### Part5：P.S.

快速将图删除的方法：将 $head$ 数组中的数值全部重置为 $0$，并且将 $cnt$ 归 $0$。

二分时不知道 $l$ 是正确答案还是 $r$ 是正确答案？二分结束后用这几行代码：

```cpp
	int ans;
	for(ans=r;ans<=l;ans++)if(check(ans))break;
```
这样即可求出本次二分的正确答案。~~感觉有点暴力~~实际上跑的还是很快的，因为二分过后 $l-r$ 的值非常小。

---

## 作者：GrayCatH (赞：15)

p4376      （超详细！）
#### 题面：     
N头奶牛（1≤N≤10^5）编号为1…N;M次观察（1≤M≤50,000）表示这些奶牛应该以与她们在序列中出现的顺序相同的顺序进行挤奶。比如序列2、5、1，表示应该在给奶牛5挤奶之前的某个时刻给奶牛2挤奶，在给奶牛1挤奶之前的某个时刻给奶牛5挤奶。     
观察结果是按优先级排列的，所以他的目标是**最大化X**的值，使得他的挤奶顺序能够符合**前X个**观察结果描述的状态。当多种挤奶顺序都能符合前X个状态时采用字典序最小的那一个。例如两串答案（1 4 2 3|4 1 2 3）按位置从左到右比较，当发现有第一个（第一位1|4）不一样时，选择小者的那串答案（1 4 2 3,1<4）         
#### 输入：

第一行包含N和M。  
接下来的M行，每行描述了一个观察结果。    
第i+1行描述了观察结果i：   
第一个数是观察结果中的**奶牛数量mi**   
后面是一列**mi个整数**，给出这次观察中奶牛的顺序。所有mi的和至多为200,000。      
#### 输出：
输出N个空格分隔的整数，给出一个1…N的排列
## 1.拓扑排序
#### 定义：有向无环图（DAG）所有顶点的线性序列
#### 满足：
1.每个顶点出现且仅出现一次   
2.若存在一条从顶点A到顶点B的路径，那么在序列中顶点A出现在顶点B的前面。   
例如：   
（表示两个数表示的顶点间有一条有向边）   
1 2     
1 4       
2 4    
2 3     
4 3      
4 5        
3 5          
它的拓扑排序即
1,2,4,3,5          
**一个图可以有多个拓扑排序（本题）**
#### 实现：
1.选择一个入度为0的顶点并输出     
2.将该顶点从图中删除，同时删除以该点为起点的有向边（将它连接的点入度减1）     
3.重复1,2操作直到图为空或不存在入度为0的点（有环，此处可判环）    
#### 一句话，不断选择入度为0的节点，把其连向的点入度减1
##### 具体框架：
1.建立空的拓扑序列A,并开队列queue   
2.预处理出所有点的入度deg[i],起初把所有入度为0的点入队         
3.取队头top，加入序列A末尾        
4.对于从top为起点的每条边（top，to），把deg[to]减1。若减为0则把to入队push、——，     
5.重复3,4直至队列为空
6.若A长度小于图中点的数量说明存在环
    
具体呔码：
```
void build(int x,int y){//领接表建有向边
	to[++tot]=y,next[tot]=head[x],head[x]=tot;
    deg[y]++;
    }
void topsort(){//拓排
		queue<int> q;
        for(int i=1;i<=n;i++)
        	if(deg[i]==0)q.push(i);
        while(q.size()){
        int x=q.front();q.pop();
        a[++cnt]=x;
        for(int i=head[x];i;i=next[i]){
        int y=to[i];
        if(--deg[y]==0)q.push(y);
        }
       }
      }
int main(){
	cin>>n>>m;//点数，边数
    for(int i=1;i<=m;i++){
    int x,y;
    scanf("%d%d",&x,&y);
    build(x,y);
    }
    topsort();
    for(int i=1;i<=cnt;i++)
    printf("%d ",a[i]);
    cout<<endl;
    }
```
#### 应用：
有依赖的问题，如有A要先有B、具有确定的先后关系，没有关系，绝对不存在互相矛盾的关系（即无环路）
## 2.优先队列(stl)
优先队列：
priority_queue      
priority_queue可理解为一个**大根堆**    
操作:**q.push(x)**   x入堆，复杂度O（log n）   
	 **q.pop()**     删堆顶O（logn）  
     **q.top()**     查堆顶（最大）O（1）  
对于小根堆（简单写法，常见于dijkstra(wu)）

```
priority_queue<int, vector<int>, greater<int> > q;   
```
关于堆涉及一个重要知识点：
#### 重载运算符
以下为堆中常见重载“<”运算符：      
优先队列中储存元素类型**需定义“小于号”**，较大的元素会被放在堆顶。但**int、string**类型有默认的大小比较。当使用自定义的结构体时则需重载运算符。      
举例：（引用《算法竞赛进阶指南》）    
定义结构体poi保存二维平面的点编号和坐标，并比较大小时先比横坐标再比纵坐标（考虑精度误差）
```
struct poi{
		int id;
        double x,y;
        };
const double eps=1e-8;
bool operator < (const poi &a, const poi &b){
	return a.x + eps < b.x || a.x < b.x + eps && a.y < b.y;
    }
```
其中某些特殊名词直接记住就行，想了解具体含义可以直接百度            
知道了重载运算符，我们就有了另一种实现小根堆的方法：       
建立自定义结构体，重载小于号当做大于号编写函数：        
```
struct rec{
		int id;
        double value;
        };
bool operator  < (const rec &a, const rec &b){
		return a.value>b.value;
        }
```
顺便把另一种思路也补上：      
对于int等内置数组类型，把插入元素的相反数放入堆中，取出时再变回来……
#### 特别的——懒惰（延迟）删除法
stl实现的优先队列方便但与手工二叉堆相比还是有些区别的——不支持删除堆中任意元素。     
~~这里呼应线段树的懒惰标记~~     
当我们遇到删除操作时，在优先队列之外做一些特殊的记录（如记录元素的最新值），用于辨别那些堆中尚未清除的“过时”元素。当从堆顶取出最值时，再检查“最值元素”是不是“过时”的，若是，则重新取出下一个最值。换言之，原素的删除被延迟到堆顶进行。（又是dij常见了……）   
||
## 3.题解
一开始看到这题两眼一蒙：插入排序？队列？并查集？怎么打暴力？？？？          
分析思路：   
我们得到的信息：序列中的前后位置关系    
要求：找一个合适的排序             
对于相对位置的排序？        
这不是很像拓扑排序满足的**“若存在一条从顶点A到顶点B的路径，那么在序列中顶点A出现在顶点B的前面”**吗？           
于是我们想到用**拓扑排序建图**去处理题目。  
回到题目，我们要**选择前x个观察，并且x要尽可能大**。        
因为本蒟蒻实在是太垃圾了，想不出这道题哪有最大值哪有最小值，所以只好换种说法。   
因为我们希望**前**x个，所以这是一个**从头开始的连续的区间，并且是一个可行性的判断，而x就是就是我们要找的可行位置**。  
这符合二分解决问题的特征。（安利自己的p1083二分博客：https://www.luogu.org/blog/deemoender-XFZaifish/noip-ti-gao-2012-jie-jiao-shi-guan-yu-qian-zhui-hu-ci-fen-er-fen-ji）)         
具体来说就是假如你发现在所有观察中，如果取中点mid是可行的，那么mid前面应该都是可行的；反之mid不行后面肯定也不行。      
那么如何判断是否可行？这时候拓扑排序处理图就有用了。
### 总体叙述：
（先说好本题解描述了比较直观的写法，本蒟蒻代码500ms+慢的一匹，100ms+的巨佬一抓一大把，后期可能会更新100ms+的写法）   
先开一个vector G描述每个观测   
再开一个vector mp每次描述到第x个观测记录
对于第x个观测记录，将其与之前的观测记录建图拓扑排序并判环，若无环则可行，有环则不可行，二分直到找到最大x，再拓扑排序一遍将序列输出，其中取字典序环节开一个简洁的小根堆。       
代码中采用傻瓜相机注释法超详细        
### code：
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#define fu(i,q,w) for(register int i=q;i<=w;i++)
#define fd(i,q,w) for(register int i=q;i>=w;i--)
using namespace std;
typedef int  ll;
inline ll read(){
	ll ret=0,f=1;char c;
	while((c=getchar())<'0'||c>'9')if(c=='-')f=-1;
	while(c>='0'&&c<='9')ret=ret*10+(c-'0'),c=getchar();
	return ret*f;
} 
const int maxn=111111;
vector<int> mp[maxn];// 对于取用观测时建立临时图 
vector<int> G[maxn];//记录每次观测 方便取用 
int ind[maxn],n,m,mi;//入度，牛数，观测数，观测点数 
void build(int x){//建图（到第x观测） 
	int u,v;
	fu(i,1,n){mp[i].clear();ind[i]=0;}//初始化 
	 fu(i,1,x)
		 fu(j,0,G[i].size()-2)
		 {//从G里取每个观测所看到的点序，建DAG 
	 		u=G[i][j];
	 		v=G[i][j+1];//u在v前面出现 
	 		mp[u].push_back(v);//由u到v建一条有向边 
	 		ind[v]++;//统计节点入度 
		 } 
}
inline int topsort(){
	int cnt=0;//计数器 
	priority_queue< int, vector<int>, greater<int> > q;
	//方便快捷的建立小根堆 
	//以每次取字典序最小 
	fu(i,1,n){//遍历所有节点 
		if(ind[i]==0) q.push(i);//将入度为0的节点入堆 
	}
	while(!q.empty()){//如果堆不空 
		int x=q.top();//取堆顶 
		q.pop();//删除堆顶 
		cnt++;//记录拓扑排序取出的点的数目
		for(int i=0;i<mp[x].size();i++) 
		{//遍历x连接的节点 
			int v=mp[x][i];//提出 
			ind[v]--;//将x连接的节点入度减1 
			if(ind[v]==0){//如果x连接的节点v也入度为0了
			q.push(v);//入堆 
			} 
		}
	}	
	if(cnt==n) return 1;//计数器发现拓扑排序找到节点和总节点数一样多 
 	//证明无环，即观测合法
	else return 0;//表示有环观测不合法 
}

inline void solve(int x){	//printf("!%d\n",x);
	int ans[maxn];
	build(x);//建图；
	int cnt=0;
	priority_queue<int ,vector<int> ,greater<int> > q;
	fu(i,1,n){//	for(int i=1;i<=n;i++){
		//	printf("@@@%d\n",ind[i]);
	//	}
		if(ind[i]==0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int x=q.top();
		q.pop();
		ans[cnt++]=x;
		for(int i=0;i<mp[x].size();i++){
			int v=mp[x][i];
			ind[v]--;
			if(ind[v]==0){
				q.push(v);
			}
		}
		printf("%d ",x);
	} 
} 
int l,r; 
inline void check(){
	int mid;
	while(l<=r){
		mid=(l+r)>>1;//二分枚举答案 
		build(mid);//由这个观测点建临时图
	//printf("mid:%d\n",mid);
		if(topsort()){//如果这个观测点符合要求
		l=mid+1;
	//	printf("1");
		 
		}
		else
		r=mid-1; 
	//	printf("~%d\n",r);
	} 	
//	printf("%d\n",r);//可以看看具体运行过程 
}
int main(){
	n=read(),m=read();
	fu(i,1,m){
		mi=read();
		while(mi--){
			
			int t;
			t=read();
			G[i].push_back(t);//记录一次观测 
		}
	}
	l=0,r=m; 
	check();//二分 
//	printf("%d\n",l);
	
	solve(r);//找出来合适的x个再跑一遍好把答案找出来 
	return 0;
}
```
    




---

## 作者：空の軌跡 (赞：14)

# 题目大意：

给定你 $n$ 个排序，

要求找出一个序列，使得这个序列满足前 $x$ 个排序前后关系，且 $x$ 尽可能大，

在满足 $x$ 最大的情况下使得 **字典序** 最小 。

# 算法：
1. dfs
2. 拓扑排序
# 思路：

1. 我们首先需要保证 $x$ 最大，那么我们对于每个序列可以逐个判断。具体做法就是把每个序列的前一个数字向后一个数字建边，然后跑一遍 dfs 找环，如果无环就可以接着向下判断，不然到这里就停止。

2. 我们做完第一步后要建出图来，然后进行 **拓扑排序**，开个堆把 **入度为 $0$** 的点塞进去，每次取出最小的即可。

3. 这样我们把可以确定顺序的牛都保证了字典序最小，那么剩余的无法确定顺序的奶牛则可以随意放置，那么我们就把这些奶牛随意插入，保证字典序最小即可。

# 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
vector<int>side[100010];
int ru[100010],read[200005];
bool vis[100010],used[100010];
priority_queue< int , vector <int> , greater<int> > cnm;
vector<int>ha;
bool dfs(int x)
{
	int size=side[x].size();
	for(int i=0;i<size;++i)
	{
		if(vis[side[x][i]])return 0;
		vis[side[x][i]]=1;
		if(!dfs(side[x][i]))
		{
			vis[x]=0;return 0;
		}
	}
	vis[x]=0;
	return 1;
}
int main()
{
	int n,m,c;scanf("%d%d",&n,&m);
    
   //判断可以满足的前 x 个
	while(m--)
	{
		scanf("%d%d",&c,&read[1]);
		for(int i=2;i<=c;++i) 	//建边
		{
			scanf("%d",&read[i]);++ru[read[i]];
			side[read[i-1]].push_back(read[i]);
		}
		vis[read[1]]=1;
		if(!dfs(read[1]))		//dfs判断，如果不行，撤销建边
		{
			for(int i=1;i<c;++i)
			side[read[i]].pop_back();
			for(int i=2;i<=c;++i)
			--ru[read[i]];
			break;
		}
		for(int i=1;i<=c;++i)
		used[read[i]]=1;
		vis[read[1]]=0;
	}
	for(int i=1;i<=n;++i)		//拓扑排序，开堆存编号
	if(used[i]&&ru[i]==0)cnm.push(i);
	while(!cnm.empty())			//拓扑
	{
		int mm=cnm.top();
		cnm.pop();
		ha.push_back(mm);
		int size=side[mm].size();
		for(int i=0;i<size;i++)
		{
			--ru[side[mm][i]];
			if(ru[side[mm][i]]==0)
			cnm.push(side[mm][i]);
		}
	}
	int cnt=1,size=ha.size();
	for(int i=0;i<size;++i)		//处理没有先后顺序的奶牛
	{
		while(cnt<ha[i])
		{
			if(cnt<ha[i]&&!used[cnt])
			{
				used[cnt]=1;cout<<cnt<<" ";
			}
			++cnt;
		}
		cout<<ha[i]<<" ";
	}
	for(int i=cnt;i<=n;++i)
	if(!used[i])cout<<i<<" ";
}
```

至于其他题解提到的二分，我不晓得为什么会比我的逐个判断速度慢，可能数据太水，也可能因为他们每次重构图都要建边导致跑得慢，总之我是没有用二分。

---

## 作者：Seg_Tree (赞：8)

相信不少人看到这道题的第一想法应该就是一条一条add_edg,每加一条边判一次环.

嗯,对,这种**非正解**的方法已经有人尝试过(并且ac了~~还比正解快很多~~)

是的,就是那个榜一的题解.或许他是在那个dfs里加了点玄学优化吧,反正我交了[1](https://www.luogu.org/record/25086093)
[2](https://www.luogu.org/record/25086040)
[3](https://www.luogu.org/record/25084621)
[4](https://www.luogu.org/record/25084310)
[5](https://www.luogu.org/record/25083987)
次,用了各种方法,都T飞了...

------------

# 接下来讨论正解

**0.有关二分**

以后大家在做题时都要对特定的数据敏感一点.像这样50000的数据,好像让我们如数数一般数一遍,看看是哪个数符合要求,首先就应该 ~~乖乖一个个数~~ 想到二分答案.

再看复杂度,若是二分,那么每次判断都得重新建图.这看似很累,实则不然,因为我们可以在题面的一角看见一个重要的数据:**所有m[i]的和至多为200,000。** 因此,我们每一次建图都最多仅为200000.再加上O(n)的拓扑排序判环,每次判断的复杂度还是O(n) ~~故1加1等于1~~ 总复杂度为O(mlog(M)+Nlog(M)),炸不了.**不建议因为懒得建图而去跑dfs,那样理论最高复杂度会达到O(MN),理论上会炸,不是正解!**

**1.有关该题的拓扑排序**

对于FJ的每一次观察,我们都从第一个点开始,一条一条连边,连到最后一个点.连完之后,我们再找一个入度为0的点,那个点肯定是要先挤奶的(毕竟没有哪头牛要求要在它前面挤),挤完他的奶,就把剩下的奶牛中被他要求先于之挤奶的牛的入度减一,再找入度为0的奶牛.若有多个,**在判环的时候**随便找一个就行了;但在最后挤奶的时候,要以奶牛的编号为关键字,开个小根堆,保证多个入度为0点的情况下,编号小的会先被挤.

**2.有关用了二分还T五个点**

在拓扑判环的时候是不用加堆优化的,这样会T.**你只要判环就行了,没必要去管他的字典序**

附代码:
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int n,ans[100001],ansx;
int in_degree[100001];
vector<int>tot_relatn[50001];
vector<int>edg[100001];
void read(int &in){
	char c=getchar();in=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')in=in*10+c-'0',c=getchar();
}
void build(int x){
	int i,j,frm,to;
	for(i=1; i<=n; i++)edg[i].clear(),in_degree[i]=0;
	for(i=1; i<=x; i++){
		to=tot_relatn[i][0];
		for(j=0; j<tot_relatn[i].size()-1; j++){
			frm=to,to=tot_relatn[i][j+1];
			edg[frm].push_back(to);
			in_degree[to]++;
		}
	}
}
int check(){
	int i,cnt=0,to;
	queue<int>q;
	for(i=1; i<=n; i++)if(in_degree[i]==0)q.push(i),in_degree[i]=-1;
	while(!q.empty()){
		int b=q.front();
		q.pop();
		cnt++;
		for(i=0; i<edg[b].size(); i++){
			to=edg[b][i];
			in_degree[to]--;
			if(in_degree[to]==0){
				in_degree[to]=-1;
				q.push(to);
			}
		}
	}
	return cnt==n?1:0;
}
int main(){
	int i,m,mi,ci,l,r,mid;
	read(n),read(m);
	for(i=1; i<=m; i++){
		read(mi);
		while(mi--){
			read(ci);
			tot_relatn[i].push_back(ci);
		}
	}
	l=1,r=m;
	while(l<=r){
		mid=l+r>>1;
		build(mid);
		if(check())l=mid+1,ansx=mid;
		else r=mid-1;
	}
	build(ansx);
	int cnt=0;
	priority_queue<int,vector<int>,greater<int> >q;
	for(i=1; i<=n; i++)if(in_degree[i]==0)q.push(i);
	while(!q.empty()){
		int b=q.top();
		q.pop();
		ans[++cnt]=b;
		for(i=0; i<edg[b].size(); i++){
			in_degree[edg[b][i]]--;
			if(in_degree[edg[b][i]]==0){
				in_degree[edg[b][i]]=-1;
				q.push(edg[b][i]);
			}
		}
	}
	for(i=1; i<=n; i++)printf("%d ",ans[i]);
	return 0;
}
```
~~夸我,码风好看,快点~~

---

## 作者：曹老师 (赞：7)

**拓扑+二分+优先队列**

最小值最大（x）考虑二分

首先先把条件记录下来 方便以后建图用

然后以[1,M]为区间二分 mid

把前 mid 个条件建出图来

**具体建图方法：**从前一个点指向另一个点 有向图

再根据题目描述 **判断是一个有向无环图 于是考虑拓扑**

拓扑的目的很简单 就是判断有没有环

然后配合二分找到 临界的mid值

在拓扑一遍输出就可以了

因为是字典序 所以要用优先队列维护

定义小根堆~~忘了默认的排列顺序~~

Ps：代码中拓扑函数没传参数 于是写了两个拓扑程序

其实可以一个程序 传一个参数 特判一下输出就好了

（效果一样 就是代码长短的问题罢了
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define INF 2147483640
#define MOD 100000007
#define free(s) freopen("s.txt","r",stdin);
using namespace std;
struct node{
	int x;
    node(int b):x(b){}
    bool operator < (const node &a) const
	{
        return a.x < x;
    }
};
const int L=50005;
int n,m,l,r,ind[L*2],ans;
vector<int>p[L*2],map[L*2];
priority_queue<node>g;
void build(int x)
{
	memset(ind,0,sizeof(ind));
	memset(map,0,sizeof(map));
	for(int i=1;i<=x;i++)
		for(int j=0;j<p[i].size()-1;j++)
		{
			map[p[i][j]].push_back(p[i][j+1]);
			ind[p[i][j+1]]++;
		}
}
int topo()
{
	int num=0;
	for(int i=1;i<=n;i++)
		if(!ind[i])
		{
			g.push(i);
			num++;
		}
	int temp;
	while(!g.empty())
	{
		temp=g.top().x;
		g.pop();
		for(int i=0;i<map[temp].size();i++)
		{
			ind[map[temp][i]]--;
			if(!ind[map[temp][i]])
			{
				g.push(map[temp][i]);
				num++;
			}
		}
	}
	if(num==n)
		return 1;
	return 0;
}
int find_ans(int x)
{
	build(x);
	for(int i=1;i<=n;i++)
		if(!ind[i])
			g.push(i);
	int temp;
	while(!g.empty())
	{
		temp=g.top().x;
		printf("%d ",temp);
		g.pop();
		for(int i=0;i<map[temp].size();i++)
		{
			ind[map[temp][i]]--;
			if(!ind[map[temp][i]])
			{
				g.push(map[temp][i]);
			}
		}
	}
}
int check(int x)
{
	build(x);
	return topo();
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int t;
		scanf("%d",&t);
		for(int j=1;j<=t;j++)
		{
			int q;
			scanf("%d",&q);
			p[i].push_back(q);
		}
	}
	l=0,r=m+1;
	while(r>=l)
	{
		int mid=(l+r)>>1;
		if(check(mid)==1)
		{
			l=mid+1;
			ans=mid;
		}
		else
			r=mid-1;
	}
	find_ans(ans);
	return 0;
}
```

---

## 作者：fly20040720 (赞：3)

（本题解默认读者已对本层次算法有充分了解，故不再提及过于微观部分）
# 基本思路
## 大框架
先读一遍题，然后就发现了一些非常明显的二分答案的特征：最小值（前X个）最大（最大化X）。但是，众所周知，二分答案的复杂度基本全在于check函数
## check函数
其实可以建一个图，若a在b前则连一条由a到b的有向边（没有什么难度）。关键是见完图之后进行的操作。再分析第二、三部分，可以得出以下信息：

1、这种操作针对有向图

2、这种操作的结果不唯一

在排除掉一堆奇怪的东西之后，我们发现，拓扑排序是个好东西。我们只需要对整个图求一边拓扑序，并且以字典序为辅助关键字，就可以了

# 稍微整理过的东西（可能是伪代码）
输入

建图

二分（check是拓扑排序（存拓扑序））

输出

# 上代码（码风不喜勿喷）
```cpp
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

vector<pair<int,int>> edges[1000000];//存图（存的是边）
vector<int> succ[1000000];//也是存图（临时）（临接向量）
int pred[1000000],result[1000000],n,m,d,e,last;//一开始就全部定义（据说可以减小常数）

bool check(int n,int k)//先写check
{
	for(int i=0;i<n;i++)
	{
		succ[i].clear();
		pred[i]=0;
	}//初始化
	for(int i=0;i<k;i++)
	{
		for(auto p:edges[i])//auto是c++11新特性,自动判断偏亮类型（c++11和c++98没什么特别的的区别。至于P党，还是快转c++吧）
		{
			succ[p.first].push_back(p.second);
			pred[p.second]++;
		}
	}
	priority_queue<int> q;//别问我为什么不重载，待会儿就知道了
//O(2)是个好东西，把我的代码从TLE降到了200+ms
//不想开O(2)可以手写堆或者在其他地方常数优化，反正理论复杂度没有问题
	for(int i=0;i<n;i++)
		if(pred[i]==0)
			q.push(-i);//把负的压进去，就不用重载了
	for(int i=0;i<n;i++)
	{
		if(q.empty())
		{
			return false;
		}//如果啥都没有了，返回假
		int v=-q.top();//再变成正的
		q.pop();//弹出

		result[i]=v;//记录答案
		for(int next:succ[v])//类似于python的for i in range succ
		{
			pred[next]--;
			if(pred[next]==0)
			{
				q.push(-next);
			}
		}
	}
	return true;//最后当然要返回成功
}

int main()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		cin>>d;
		for(int j=0;j<d;j++)
		{
			cin>>e;
			e--;//这里减1，因为取负数的方法有些奇怪
			if(j>0)
				edges[i].push_back(make_pair(last,e));
			last=e;
		}
	}//建图，没什么好说的
	int L=0,R=m+1;
	while(R>L+1)
	{
		int mid=(L+R)/2;
		if(check(n,mid))
			L=mid;
		else
			R=mid;
	}//标准二分
	int ans=L;
	check(n,ans);//填装答案
	for(int i=0;i<n;i++)
		cout<<result[i]+1<<' ';//输出，这里加1
}
```

[博客](https://www.luogu.org/blog/27950)

---

## 作者：tcswuzb (赞：2)

# [题目链接](https://www.luogu.com.cn/problem/P4376)

# 题意分析

首先我们发现 **这个可以满足序列的数目是单调的**

所以我们可以直接二分答案来确实满足了几个序列

然后的话我们发现 如果把先后顺序加成有向图的表示方式

**我们就需要判断一下这个图中是否存在环**

可以使用Tarjan算法判断

如果是一个DAG的话就是合理的

最后的话 我们根据满足的序列数再建一个DAG

使用拓扑排序确定答案序列 

如何保证字典序最小呢 我们**只需要把拓扑排序中的队列换成优先队列就可以了**

# CODE:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#define M 100080
#define N 500080
using namespace std;
int n,m,tot,cnt,ans,top;
int num[M],ansq[M];
int to[N],nex[N],head[N];
int dfn[M],low[M],sta[M],in[M];
bool vis[M];
vector<int> G[M];
priority_queue<int,vector<int>,greater<int> > que;
void add(int x,int y)
{to[++tot]=y;nex[tot]=head[x];head[x]=tot;}
void Tarjan(int now)
{
	dfn[now]=low[now]=++cnt;sta[++top]=now;vis[now]=1;
	for(int i=head[now];i;i=nex[i])
	{
		int v=to[i];
		if(!dfn[v]) Tarjan(v),low[now]=min(low[now],low[v]);
		else if(vis[v]) low[now]=min(low[now],dfn[v]);
	}
	if(dfn[now]==low[now])
	{
		++tot;
		while(sta[top+1]!=now)
		vis[sta[top--]]=0;
	}
}
bool check(int x)
{//二分答案判断函数
	tot=0;	
	for(int i=1;i<=n;++i) head[i]=0;
	for(int i=1;i<=x;++i)
	 for(int j=0;j<(int)G[i].size()-1;++j)
	  add(G[i][j],G[i][j+1]); 
	tot=0;cnt=0;  
	for(int i=1;i<=n;++i) vis[i]=0;
	for(int i=1;i<=n;++i) dfn[i]=low[i]=0;
	top=0;
	for(int i=n;i;--i) if(!dfn[i]) Tarjan(i);  
	if(tot==n) return 1;
	else return 0;
}
void Top_sort(int now)
{//拓扑排序求解答案
	tot=0;	
	for(int i=1;i<=n;++i) head[i]=0;
	for(int i=1;i<=now;++i)
	 for(int j=0;j<(int)G[i].size()-1;++j)
	  {
	  	add(G[i][j],G[i][j+1]),in[G[i][j+1]]++; 
	  }
	cnt=0;
	for(int i=1;i<=n;++i) if(!in[i]) que.push(i);
	while(!que.empty())
	{
		int u=que.top();que.pop();
		ansq[++cnt]=u;
		for(int i=head[u];i;i=nex[i])
		{
			int v=to[i];
			in[v]--;
			if(!in[v]) que.push(v);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d",&num[i]);
		for(int j=1,x;j<=num[i];++j)
		scanf("%d",&x),G[i].push_back(x);
	}
	int le=1,ri=n,ans=0;
	while(le<=ri)
	{
		int mid=(le+ri)>>1;
		if(check(mid)) ans=mid,le=mid+1;
		else ri=mid-1;
	}
	Top_sort(ans);
	for(int i=1;i<=n;++i) printf("%d%c",ansq[i],(i==n ? '\n':' '));
	return 0;
}
```


---

## 作者：LlLlCc (赞：2)

很经典的拓扑+二分啊，为什么题解不多呢？（题外话）

------------
这题还是有比较**比较强的层次关系（前后关系）** 的，所以肯定会想到拓扑来排序的。

不会拓扑的看这里：[拓扑基础](https://blog.csdn.net/qq_41713256/article/details/80805338)

------------
知道了要用拓扑后，接下来就只剩下些小问题了。

- #### 要如何求出最大的X呢？

首先我们要知道X的定义是什么。X表示前X个观察结果成立（不矛盾），也就是根据前X个观察结果建的有向图是一个无环图。

其实X的取值是满足**单调性**的，为什么呢？仔细想想，如果前X个关系不矛盾，那么前X-1，X-2，...,都是不矛盾的，而单调性的话就可以借助**二分**来确定X的**最大**值。

不会二分的看这里（~~肯定没有~~）：[二分的基础思想](https://www.cnblogs.com/idreamo/p/9000762.html)

------------


- #### 如何满足字典序最小？

正常情况下，拓扑是将**入度为1**的节点塞进队列里，然后根据入队列的时间戳来遍历其他节点，我们要满足字典序**最小**，只要改变入队列的顺序就好了，每次在**入度为1的所有节点中，挑最小的**就可以做到字典序最小了，而每次都挑最小的，自然就会想到借助**堆**或者**集合**来实现加速，问题就解决了。

------------
总的来说，这道题是一道拿来联系不错的模板题，**最好自己写一写**

AC代码：（借助堆来实现）
```
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
int now,n,m,len,k[maxn],Q[maxn],hep[maxn],hed,til,tot,lnk[maxn],nxt[maxn],T_in[maxn],son[maxn],ans,L,R,mid;
vector <int> a[maxn];
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
    while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}
inline void put(int x){
	hep[now=++len]=x;
	while (now>1&&hep[now]<hep[now>>1]) swap(hep[now],hep[now>>1]),now>>=1;
}
inline int get(){pop_heap(hep+1,hep+len+1,greater<int>());return hep[len--];}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline bool check(int x){
	memset(lnk,0,sizeof lnk);
	memset(T_in,0,sizeof T_in);
	hed=0,til=0,tot=0;
	for (int i=1;i<=x;i++)
	for (int j=1;j<a[i].size();j++) add(a[i][j],a[i][j-1]),T_in[a[i][j-1]]++;
	tot=0;
	for (int i=1;i<=n;i++) if (!T_in[i]) Q[++til]=i;
	while (hed<til){
		hed++,tot++;
		for (int i=lnk[Q[hed]];i;i=nxt[i]){
			T_in[son[i]]--;
	    	if (!T_in[son[i]]) Q[++til]=son[i];
    	}
    }
	if (tot==n) return 1;
	return 0;
}
inline void To(int x){
	memset(lnk,0,sizeof lnk);
	memset(T_in,0,sizeof T_in);
	hed=0,til=0,tot=0;
	for (int i=1;i<=x;i++)
	for (int j=0;j<a[i].size()-1;j++) add(a[i][j],a[i][j+1]),T_in[a[i][j+1]]++;  //倒着建边，方便输出答案
	for (int i=1;i<=n;i++) if (!T_in[i]) put(i);
	while (len){
	    now=get();printf("%d ",now);
	    for (int i=lnk[now];i;i=nxt[i]) if (!(--T_in[son[i]])) put(son[i]);
	}
}
int main(){
    n=read(),m=read();
    for (int i=1;i<=m;i++){
    	k[i]=read();
    	for (int j=1;j<=k[i];j++) a[i].push_back(read());
	}
	L=1,R=m;
	while (L<=R){    //二分确定X的最大值
		mid=L+R>>1;
		if (check(mid)) ans=mid,L=mid+1;
	    else R=mid-1;
	}
	To(ans);
   return 0;
}
```


---

## 作者：嚯呀嚯呀 (赞：2)

只有这么几篇？(而且还没有Pascal的)

**二分答案+tarjan判环+堆**

**不急，我们一步一步来**

首先，要求满足最多的前x个观察结果要相同，如果我们一步一步看一下能不能满足，就太慢了，这里就是用二分答案来写

接下来，对于每一个二分出来的答案mid，怎么判断是否合法呢，如果一头奶牛要在另一头奶牛前面，又要在一头奶牛后面，那么这种情况就是满足不了的，**更广泛的来说，我们对于每一组谁在谁前面的条件，从前面的奶牛建一条有向边指向后面那头奶牛，如果成环，那么就是不合法的**

**那么一个新的问题：我们怎么判环呢？**

**第一种方法：spfa**

我们建边的时候把边的权值改为-1，然后判有没有负环就可以了，具体可以参照洛谷P3385模板

这里dfs版的spfa并不可取，在没有负环的情况下dfs就很慢（我的一个同学亲测，tle了6个点），但是写bfs用一个点有没有进入队列超过n次的话也很慢，[这里可以参照我之前写的题解](https://www.luogu.org/blog/user39488/solution-p3385)

**第2种办法:tarjan判环**

对于任意一个强连通分量，如果其中有超过1个点组成，那么就是不合法的

**这时候我们已经求好了最大的x是多少了，接下来怎么输出呢？**

**题目可是要求字典序最小啊(乱七八糟的事情真多（逃）)**

我们记录一下每个点的入度是多少，很显然要先输出入度为0的点

这时候写一个小根堆来维护输出序列，对于输出的每一个点，我们删掉他连出去的所有边，这时候可能会重新出现入度为0的点，就加到堆里去

**看，这样一个一个分开不都是很简单的吗**

by the way，这里二分的时候有一个小细节，我们每得到一个新的mid，图也会因此而变化，你可以选择重新建图（可以过的），或者用一个比较巧妙的方法，**记录一下每一个观察结果所产生的图的最大的那条边是什么**，就是我代码里的last数组，如果你进行什么操作的时候要用的边大于last[mid]的时候，就不用这条边，因为它不在前mid信息里面

**说了好多好累啊.....看代码吧**

**勉强挤入最优解第一页（我好蒟蒻啊）**
```
var
  bi:boolean;
  ans,look,t,l,r,mid,tot,top,a1,a2,len:longint;
  i,j,m,n,k,p:longint;
  ru,next,other,a,last,dfn,low,stack,num,check,f:array[0..200005]of longint;
function min(x,y:longint):longint;
begin
  if x<y then exit(x)
  else exit(y);
end;
procedure tarjan(u:longint);
var
  j,v,k:longint;
begin
  if bi=false then exit;
  inc(t); dfn[u]:=t; low[u]:=t;
  check[u]:=1; inc(top); stack[top]:=u;
  k:=a[u];
  while k<>0 do
    begin
      v:=other[k];
      if k>last[mid] then
        begin
          k:=next[k]; continue;
        end;
      if check[v]=0 then
        begin
          tarjan(v);
          low[u]:=min(low[u],low[v]);
        end
      else
        if check[v]=1 then
          low[u]:=min(low[u],dfn[v]);
      k:=next[k];
    end;
  if dfn[u]=low[u] then
    begin
      inc(tot);
      repeat
        j:=stack[top]; dec(top);
        check[j]:=-1;
        inc(num[tot]);
        if num[tot]=2 then
          begin
            bi:=false; exit;
          end;
      until j=u;
    end;
end;
procedure put(x:longint);
var
  now,father,a1:longint;
begin
  inc(look); f[look]:=x;
  now:=look;
  while now<>1 do
    begin
      father:=now div 2;
      if f[father]<f[now] then break
      else
        begin
          a1:=f[father]; f[father]:=f[now]; f[now]:=a1;
          now:=father;
        end;
    end;
end;
procedure get;
var
  now,a1,son:longint;
begin
  f[1]:=f[look]; dec(look);
  now:=1;
  while now*2<=look do
    begin
      son:=now*2;
      if (son+1<=look)and(f[son+1]<f[son]) then inc(son);
      if f[son]>=f[now] then break
      else
        begin
          a1:=f[son]; f[son]:=f[now]; f[now]:=a1;
          now:=son;
        end;
    end;
end;
begin
  {assign(input,'11.in');
  assign(output,'11.out');
  reset(input); rewrite(output);}
  readln(n,m);
  for i:=1 to m do
    begin
      read(k);
      if k<>0 then
        begin
          read(a1);
          for j:=2 to k do
            begin
              read(a2);
              inc(len);
              next[len]:=a[a1]; a[a1]:=len; other[len]:=a2;
              a1:=a2;
            end;
        end;
      readln;
      last[i]:=len;
    end;
  {for i:=1 to m do
    writeln(last[i],' ');}
  l:=0; r:=m;
  while l<r do
    begin
      mid:=(l+r+1) div 2;
      t:=0; tot:=0; top:=0;
      fillchar(check,sizeof(check),0); {fillchar(dfn,sizeof(dfn),0);
      fillchar(low,sizeof(low),0);} fillchar(num,sizeof(num),0);
      bi:=true;
      for i:=1 to n do
        if (check[i]=0)and(bi=true) then
          tarjan(i);
      if bi=true then l:=mid
      else r:=mid-1;
    end;
  //writeln(l);
  for i:=1 to n do
    begin
      k:=a[i];
      while k<>0 do
        begin
          p:=other[k];
          if k>last[l] then
            begin
              k:=next[k]; continue;
            end;
          inc(ru[p]);
          k:=next[k];
        end;
    end;
  {for i:=1 to n do
    writeln(ru[i]);}
  look:=0;
  for i:=1 to n do
    if ru[i]=0 then
      put(i);
  ans:=n;
  while ans>0 do
    begin
      a1:=f[1]; write(a1,' '); get;
      dec(ans);
      k:=a[a1];
      while k<>0 do
        begin
          p:=other[k];
          if k>last[l] then
            begin
              k:=next[k]; continue;
            end;
          dec(ru[p]);
          if ru[p]=0 then
            put(p);
          k:=next[k];
        end;
    end;
  //close(input); close(output);
end.
```
祝大家2018 RP++

---

## 作者：Terac (赞：1)

[$\texttt{Link}$](https://www.luogu.com.cn/problem/P4376)  

把每只奶牛都看成一个点，题目中有规定点的先后顺序，容易想到拓补排序，把这样的先后顺序看作一条边，点 $u$ 在点 $v$ 前即为连一条 $u\to v$ 的边，并使点 $v$ 的入度 $in_v\gets in_v+1$。  

其中还有一些规定是无法满足的，即出现环时没有拓补排序，题目要求满足前 $x$ 个规定并使 $x$ 最大。  

这个东西显然是满足单调性的。因为加了前 $x$ 组边若有环，那对于 $y\in\left(x,m\right]$，加了前 $y$ 组边，必定会有前 $x$ 组边中的环。  

于是想到可以二分可加入边的组数 $x$。每次二分重新加边，跑拓补排序，找到 $x_{\max}$ 后再跑一遍记录答案即可。  

因为题目要求字典序最小的拓补排序，所以用小根堆维护入队的点，注意在二分 `check` 的时候不需要用小根堆，否则复杂度会多乘堆的一个 $\log$，变为 $O(n\log^2n)$，~~虽然本题没什么区别~~。  

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
int ld[N], rd[N], c[N << 1], awa;
//ld[i]和rd[i]是存第i组边在所有点中对应的区间
struct edge {
	int to, nxt;
} e[N << 1];
int head[N], cnt;
void add(int u, int v) {
	e[++cnt] = (edge){v, head[u]};
	head[u] = cnt;
}
int in[N];
queue<int> q;
priority_queue<int, vector<int>, greater<int> > p;
int ans[N], tot;
bool check(int x){
	memset(head, 0, sizeof(head));
	memset(in, 0, sizeof(in));
	cnt = tot = 0;
	for(int i = 1; i <= x; i++)
		for(int j = ld[i] + 1; j <= rd[i]; j++)
			add(c[j - 1], c[j]), in[c[j]]++;
	for(int i = 1; i <= n; i++) if(!in[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		++tot;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(!(--in[v])) q.push(v); 
		}
	}
	return (tot == n);
}
void topu(int x){
	memset(head, 0, sizeof(head));
	memset(in, 0, sizeof(in));
	cnt = tot = 0;
	for(int i = 1; i <= x; i++)
		for(int j = ld[i] + 1; j <= rd[i]; j++)
			add(c[j - 1], c[j]), in[c[j]]++;
	for(int i = 1; i <= n; i++) if(!in[i]) p.push(i);
	while(!p.empty()) {
		int u = p.top();
		p.pop();
		ans[++tot] = u;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			--in[v];
			if(!in[v]) p.push(v); 
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int t; scanf("%d", &t);
		if(!t) continue;
		ld[i] = awa + 1;
		for(int j = 1; j <= t; j++)
			scanf("%d", &c[++awa]);
		rd[i] = awa;
	}
	int l = 1, r = m, x, mid;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(check(mid)) x = mid, l = mid + 1;
		else r = mid - 1;
	}
	topu(x);
	for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}
```


---

## 作者：柠檬草苏打水 (赞：1)

### 思路：

不难发现，如果我们对一些可以满足的观察结果建有向图的话，会得到一个DAG，得到DAG之后我们就可以用拓扑+堆来选出字典序最小的点。因此本题问题就在于如果找出那个DAG
我们知道观察结果是要前缀满足的，因此我们可以用O(nm)的时间找出那个断点，不过这样不一定能过。所以我们改一下方法，二分枚举断点，将1~mid的观察结果全部加进去，然后判环，这样就可以在O(mlogn)的时间内求出DAG了

### Code：
```cpp
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar())	if (ch=='-')    f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())	x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}
inline void print(int x){
	if (x>=10)	print(x/10);
	putchar(x%10+'0');
}
const int N=1e5,M=5e4;
int pre[(N<<1)+10],now[N+10],child[(N<<1)+10],d[N+10];
int dfn[N+10],low[N+10],stack[N+10],num[N+10],milk[N+10];
bool instack[N+10];
int tot,Time,top,cnt,n,m;
vector<int>vec[M+10];
struct S1{
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define fa (p>>1)
	int Q[N+10],len;
	void insert(int x){
		Q[++len]=x;
		int p=len;
		while (p!=1&&Q[p]<Q[fa])	swap(Q[p],Q[fa]),p=fa;
	}
	int Get(){
		int Ans=Q[1],p=1,son; Q[1]=Q[len--];
		while (ls<=len){
			if (rs>len||Q[ls]<Q[rs])	son=ls;
			else	son=rs;
			if (Q[p]>Q[son])	swap(Q[p],Q[son]),p=son;
			else	break;
		}
		return Ans;
	}
}Heap;
void join(int x,int y){pre[++tot]=now[x],now[x]=tot,child[tot]=y,d[y]++;}
void tarjan(int x){
	dfn[x]=low[x]=++Time;
	instack[stack[++top]=x]=1;
	for (int p=now[x],son=child[p];p;p=pre[p],son=child[p]){
		if (!dfn[son])	tarjan(son),low[x]=min(low[x],low[son]);
		else	if (instack[son])	low[x]=min(low[x],dfn[son]);
	}
	if (dfn[x]==low[x]){
		instack[x]=0,num[x]=++cnt;
		while (stack[top]!=x)	instack[stack[top]]=0,num[stack[top--]]=cnt;
		top--;
	}
}
void init(){
	tot=Time=cnt=0;
	memset(d,0,sizeof(d));
	memset(now,0,sizeof(now));
	memset(dfn,0,sizeof(dfn));
}
bool check(int x){
	init();
	for (int i=1;i<=x;i++)	for (int j=1;j<(int)vec[i].size();j++)	join(vec[i][j-1],vec[i][j]);
	for (int i=1;i<=n;i++)	if (!dfn[i])	tarjan(i);
	return cnt==n;
}
void topo(){
	int T=0;
	for (int i=1;i<=n;i++)	if (!d[i])	Heap.insert(i);
	while (Heap.len){
		int x=(milk[++T]=Heap.Get());
		for (int p=now[x],son=child[p];p;p=pre[p],son=child[p])
			if (!--d[son])	Heap.insert(son);
	}
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++)	for (int j=read();j;j--)	vec[i].push_back(read());
	int l=1,r=m,res=0;
	while (l<=r){
		int mid=(l+r)>>1;
		if (check(mid))	res=mid,l=mid+1;
		else	r=mid-1;
	}
	init();
	for (int i=1;i<=res;i++)	for (int j=1;j<(int)vec[i].size();j++)	join(vec[i][j-1],vec[i][j]);
	topo();
	for (int i=1;i<=n;i++)	printf("%d",milk[i]),i==n?putchar('\n'):putchar(' ');
	return 0;
}

---

## 作者：tribool4_in (赞：0)

首先看到题目，看到 “为奶牛挤奶的顺序”，自然想到拓扑排序。接下来就有几点问题：

1. 建图，只需对于每个观察结果，每两个相邻的数之间建一条边即可；
2. 求 X 值，易知答案（是否存在拓扑序，即是否有环）满足单调性，可以二分；
3. 判断环，有多种方法，我是判断最终输出的拓扑序列是否长度为 $n$，如果不为 $n$ 则表示有环；
4. 每次拓扑前只保留前 $x$ 条边，可以在拓扑开始时将 $i> x$ 的边对应的入度减一，且找入度为 0 的点时不走 $i>x$ 的边。
5. 字典序最小，使用优先队列即可（话说我在考试时脑抽没想到这种方法，直接把边排序，结果 100->10 ）

吸氧可过，代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
inline int read() {
	int x = 0; char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	return x;
}
struct node {
	int v, i;
	bool operator <(node rhs) const {
		return v < rhs.v;
	}
};
int n, m;
vector<node> G[N];
int qqq[N], ccc = 0;
int in[N], in2[N];
bool topo(int x) {
	ccc = 0;
	memcpy(in, in2, sizeof in);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < G[i].size(); j++) {
			if (G[i][j].i > x) {
				in[G[i][j].v]--; // 对应边入度 -1
			}
		}
	}
	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 1; i <= n; i++) {
		if (in[i] == 0) q.push(i);
	}
	int cnt = 0;
	while (!q.empty()) {
		int now = q.top(); q.pop();
		qqq[++ccc] = now;
		cnt++;
		for (int i = 0; i < G[now].size(); i++) {
			if (G[now][i].i > x) continue; // 不走 i > x 的边
			in[G[now][i].v]--;
			if (in[G[now][i].v] == 0) q.push(G[now][i].v);
		}
	}
	if (cnt < n) return false; // 有环
	return true;
}
int as[N];
int erfen() {
	int l = 1, r = m, ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (topo(mid)) {
			ans = mid;
			memcpy(as, qqq, sizeof as);
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return ans;
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), a = 0, b = 0;
		for (int j = 1; j <= x; j++) {
			b = read();
			if (a) G[a].push_back((node){b, i}), in[b]++, in2[b]++; // 每两个相邻的数之间建一条边
			a = b;
		}
	}
	erfen();
	for (int i = 1; i < n; i++) printf("%d ", as[i]);
	printf("%d\n", as[n]);
	return 0;
}
```

---

## 作者：江yyyz1911 (赞：0)

## 题目
Farmer John 的 N 头奶牛（1≤N≤10^5），仍然编号为 1…N，正好闲得发慌。因此，她们发展了一个与 Farmer John 每天早上为她们挤牛奶的时候的排队顺序相关的复杂的社会阶层。

经过若干周的研究，Farmer John 对他的奶牛的社会结构总计进行了 M 次观察
（1≤M≤50,000）。每个观察结果都是他的某些奶牛的一个有序序列，表示这些奶牛应该以与她们在序列中出现的顺序相同的顺序进行挤奶。

比方说，如果 Farmer John 的一次观察结果是序列 2、5、1，Farmer John 应该在给奶牛 5 挤奶之前的某个时刻给奶牛 2 挤奶，在给奶牛 1 挤奶之前的某个时刻给奶牛 5 挤奶。

Farmer John 的观察结果是按优先级排列的，所以他的目标是最大化 X 的值，使得他的挤奶顺序能够符合前 X 个观察结果描述的状态。当多种挤奶顺序都能符合前 X 个状态时，Farmer John 相信一个长期以来的传统——编号较小的奶牛的地位高于编号较大的奶牛，所以他会最先给编号最小的奶牛挤奶。

更加正式地说，如果有多个挤奶顺序符合这些状态，Farmer John 会采用字典序最小的那一个。挤奶顺序 x 的字典序比挤奶顺序 y 要小，如果对于某个 j，xi=yi 对所有 i<j 成立，并且 xj<yj（也就是说，这两个挤奶顺序到某个位置之
前都是完全相同的，在这个位置上 x 比 y 要小）。

请帮助 Farmer John 求出为奶牛挤奶的最佳顺序。
## 分析

做这道题的前几天正好做的初赛题目里有个和这个类似的，就是有几个点对关系求最小的顺序，而他的解法就是用拓扑序求，所以考场上，我很自然地想到了拓扑序解这道题

首先，对于每一个关系，都可以抽象成一条边；

其次，要判断输入的关系我们还要不要，不要这一组关系（假设为 A 到 B ）的必要条件是：

	在我已建的图里已经有 B 到 A 这条边了，那么我再加上这条边就会形成环，
 
很明显就没有了拓扑序且关系混乱，所以这时这个及之后的关系都可以不要了

然后，用拓扑序找点加入堆里，用小根堆维护，每次取出栈顶最小编号的点，就可以保证字典序最小

【不用特判过了我们机房所有毒瘤数据哦~】

## 代码
```
#include<bits/stdc++.h>
using namespace std;
const int M=50004,N=1e5+10;
int n,m,flag=0,len,num;
int b[M],rd[N],q[N<<4],ans[N];
int d[N<<4]; 
bool book[N];
struct ege{
	int v,next;
}e[N<<1];
int h[N<<1];
int cnt=0;
void add(int x,int y)
{
	cnt++;
	e[cnt].v=y;
	e[cnt].next=h[x];
	h[x]=cnt;
}
int read()
{
	int s=0,f=1; char ch; ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-f; ch=getchar(); }
	while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar(); }
	return s*f;
}
bool dfs(int x,int y)
{
	if(flag) return 1;
	if(x==y){flag=1; return 1;}
	for(int i=h[x];i;i=e[i].next)
	{
		int v=e[i].v;
		if(book[v]==0)
		{
			book[v]=1;
			bool un=dfs(v,y);
			book[v]=0;
			if(un) return 1;
		}
	}
	return 0;
}
void up(int xbw)
{
	while(xbw>1)//只要没有到达根 
	{
		if(d[xbw]<d[xbw/2])//如果插入的数比我的父节点小 
		{//维护规则 
			swap(d[xbw],d[xbw/2]);
			xbw/=2;
		}
		else break;
	}
}
void down(int xbv)//从根开始 
{//向下调整 
	int r=xbv*2;//左 
	while(r<=num)
	{
		if(r<num&&d[r]>d[r+1]) r++;//左比右大 
		if(d[xbv]>d[r]) 
		{
			swap(d[xbv],d[r]);
			xbv=r;
			r=xbv*2;
		} 
		else break;
	} 
}
void topo()
{
	int hh=0,tt=0;
	for(int i=1;i<=n;i++) if(rd[i]==0) d[++num]=i,up(num);
	if(d[1]) q[++tt]=d[1], d[1]=d[num--], down(1);
	while(hh<tt)
	{
		hh++;
		int x=q[hh];
		cout<<x<<" ";
		for(int i=h[x];i;i=e[i].next)
		{
			int v=e[i].v;
			rd[v]--;
			if(rd[v]==0) d[++num]=v,up(num);
		}
		while(d[1]==0) d[1]=d[num--],down(1);
		if(num>0) q[++tt]=d[1],d[1]=d[num--],down(1);
	}
}
int main()
{
	n=read(); m=read();
	bool un=1;
	for(int u=1;u<=m;u++)
	{
		int sum; sum=read();
		for(int i=1;i<=sum;i++) b[i]=read();
		for(int i=1;i<=sum;i++)
		{
			if(un==0) break;
			for(int j=i+1;j<=sum;j++)
			if(un&&dfs(b[j],b[i])) { un=0; break; }
			else flag=0;
		}
		if(un) 
		for(int i=2;i<=sum;i++) add(b[i-1],b[i]),rd[b[i]]++;
	}
	topo();
	return 0;
}
```


---

## 作者：羽儇 (赞：0)

$Solution$

1、$\text{先二分找最大的 X}$

  
  //清空下
  
  //左边的优先级大，以TA为左端点
  
  //toposort板子，用来计数num，以判断是否有缺少，或矛盾的情况
  
  ```
  bool AC(int cnt)
{
	memset(G,0,sizeof G);
	memset(ru,0,sizeof ru);
	queue<int>q;
	int num = 0;
	for(int i = 1 ;i <= cnt ; i++)
	for(int j = 1 ; j < V[i].size() ; j ++)
	{
		int u = V[i][j-1],v = V[i][j] ;
		G[u].push_back(v);
		ru[v] ++;
	}
    for(int i = 1 ;i <= N ; i++)
    if(!ru[i])q.push(i),num++;
	while(!q.empty())
	{
		int u = q.front();q.pop();
		for(int i = 0 ; i < G[u].size(); i ++)
		{
			int v = G[u][i];
			ru[v]--;
			if(!ru[v])q.push(v),num++;
		} 
	}
	if(num != N)return false;
	else return true;
}

  ```

2、
```
	memset(G,0,sizeof G);
	memset(ru,0,sizeof ru);
	for(int i = 1 ;i <= ans ; i++)
	for(int j = 1 ; j < V[i].size() ; j ++)
	{
		int u = V[i][j-1],v = V[i][j] ;
		G[u].push_back(v);
		ru[v] ++;
	}
    priority_queue<int,vector<int>,greater<int> >q;int cnt = 0 ;//因为按照字典序，所以小的尽量在前面，可用小根堆
	for(int i = 1 ;i <= N; i ++)
	if(!ru[i])q.push(i);
	while(!q.empty())
	{
		int u = q.top();q.pop();
		printf("%d ",u);//直接输出即可
		for(int i = 0 ;i < G[u].size() ;i ++)
		{
			int v = G[u][i];
			ru[v] --;
			if(!ru[v])q.push(v);
		}
	}
```
------------

$ ACcode $
```cpp
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#define maxn 100005
using namespace std;
int N,M,x,ru[maxn],t;
vector<int>V[maxn],G[maxn];
bool AC(int cnt)
{
	memset(G,0,sizeof G);
	memset(ru,0,sizeof ru);
	queue<int>q;
	int num = 0;
	for(int i = 1 ;i <= cnt ; i++)
	for(int j = 1 ; j < V[i].size() ; j ++)
	{
		int u = V[i][j-1],v = V[i][j] ;
		G[u].push_back(v);
		ru[v] ++;
	}
    for(int i = 1 ;i <= N ; i++)
    if(!ru[i])q.push(i),num++;
	while(!q.empty())
	{
		int u = q.front();q.pop();
		for(int i = 0 ; i < G[u].size(); i ++)
		{
			int v = G[u][i];
			ru[v]--;
			if(!ru[v])q.push(v),num++;
		} 
	}
	if(num != N)return false;
	else return true;
}
int main()
{
	scanf("%d%d",&N,&M);
	for(int i = 1 ;i <= M; i ++)
	{
	    scanf("%d",&t);
	    for(int j = 1; j <= t; j ++)
	    scanf("%d",&x),V[i].push_back(x);
	}
	int l = 1 , r = N , mid ,ans;
	while(l <= r)
	{
		mid = l + r >> 1;
		if(AC(mid))l = mid + 1,ans = mid;
		else r = mid - 1 ;
	}
	memset(G,0,sizeof G);
	memset(ru,0,sizeof ru);
	for(int i = 1 ;i <= ans ; i++)
	for(int j = 1 ; j < V[i].size() ; j ++)
	{
		int u = V[i][j-1],v = V[i][j] ;
		G[u].push_back(v);
		ru[v] ++;
	}
    priority_queue<int,vector<int>,greater<int> >q;int cnt = 0 ;
	for(int i = 1 ;i <= N; i ++)
	if(!ru[i])q.push(i);
	while(!q.empty())
	{
		int u = q.top();q.pop();
		printf("%d ",u);
		for(int i = 0 ;i < G[u].size() ;i ++)
		{
			int v = G[u][i];
			ru[v] --;
			if(!ru[v])q.push(v);
		}
	}
	return 0;
}
```
挺水的一道topo+二分题

---

