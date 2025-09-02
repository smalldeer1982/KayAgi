# [USACO13FEB] Milk Scheduling S

## 题目描述

Farmer John's N cows (1 <= N <= 10,000) are conveniently numbered 1..N. Each cow i takes T(i) units of time to milk.  Unfortunately, some cows must be milked before others, owing to the layout of FJ's barn.  If cow A must be milked before cow B, then FJ needs to completely finish milking A before he can start milking B.

In order to milk his cows as quickly as possible, FJ has hired a large number of farmhands to help with the task -- enough to milk any number of cows at the same time.  However, even though cows can be milked at the same time, there is a limit to how quickly the entire process can proceed due to the constraints requiring certain cows to be milked before others.  Please help FJ compute the minimum total time the milking process must take.

农民约翰有N头奶牛(1<=N<=10,000)，编号为1...N。每一头奶牛需要T(i)单位的时间来挤奶。不幸的是，由于FJ的仓库布局，一些奶牛要在别的牛之前挤奶。比如说，如果奶牛A必须在奶牛B前挤奶，FJ就需要在给奶牛B挤奶前结束给奶牛A的挤奶。


为了尽量完成挤奶任务，FJ聘请了一大批雇工协助任务——同一时刻足够去给任意数量的奶牛挤奶。然而，尽管奶牛可以同时挤奶，但仍需要满足以上的挤奶先后顺序。请帮助FJ计算挤奶过程中的最小总时间。


## 说明/提示

There are 3 cows.  The time required to milk each cow is 10, 5, and 6, respectively.  Cow 3 must be fully milked before we can start milking cow 2.


Cows 1 and 3 can initially be milked at the same time.  When cow 3 is finished with milking, cow 2 can then begin.  All cows are finished milking after 11 units of time have elapsed.


## 样例 #1

### 输入

```
3 1 
10 
5 
6 
3 2 
```

### 输出

```
11 
```

# 题解

## 作者：Datura_ (赞：19)

拓扑排序模板题。

这里我用了广搜的删边法，记录每个点的入度，从入度为0的点开始搜索，每删一条边入度减1。

AC代码：

```cpp
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
 
const int MAXN=10001;
int n,m,ans,t[MAXN],tot[MAXN],d[MAXN];
vector<int> g[MAXN];
queue<int> q;
 
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>t[i];
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        d[y]++;//记录入度
    }
    for(int i=1;i<=n;i++)
    {
        if(d[i]==0)//入度为0的点入队
        {
            tot[i]=t[i];
            q.push(i);
        }
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i];
            d[v]--;//删边
            tot[v]=max(tot[v],tot[u]+t[v]);
            if(d[v]==0)q.push(v);//入度为0的点入队
        }
    }
    for(int i=1;i<=n;i++)
        ans=max(tot[i],ans);
    cout<<ans;
    return 0;
}
```

---

## 作者：Ginger_he (赞：8)

# 题解
提到先后顺序，就不难想到**拓扑排序**。值得注意的是，虽然这道题问的是总时间的最小值，但我们要求的是这张图的**最长路**。下面我们来证明一下：  
首先要明确的是，题目给定的图不一定连通（样例就具有这个性质）,因此我们就要把它分成多个部分。  
接着可以得出两个结论：每个部分之间是**相互独立**的，用题目的话说就是可以同时挤奶；每个部分内部是**相互约束**的，必须要等前面的奶牛挤完后再挤下一只。  
最后，我们设每个部分的用时为 $t_1,t_2,...,t_k$，不难得出总用时为 $\max\left\{t_1,t_2,...,t_k\right\}$，即为原图最长路。
## 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10005;
int n,m,t[maxn],r[maxn],f[maxn],ans;
vector<int> g[maxn];
queue<int> q;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&t[i]);
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        g[a].push_back(b);
        r[b]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(!r[i])
        {
        	f[i]=t[i];
        	q.push(i);
		}
    }
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        for(int i=0;i<g[tmp].size();i++)
        {
            f[g[tmp][i]]=max(f[g[tmp][i]],f[tmp]+t[g[tmp][i]]);
            if(--r[g[tmp][i]]==0)
                q.push(g[tmp][i]);
        }
    }
    for(int i=1;i<=n;i++)
    	ans=max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：y2823774827y (赞：7)

典型的拓扑排序，注意点的修改就好了，程序有写了注解应该容易看懂
```cpp
# include<cstdio>
# include<queue>
# include<iostream>
using namespace std;
int n,m,num=0,ans=0,u,v;
int t[10005],to[50005],bian[50005],v_u[10005],ru[10005],before[10005],pay[10005];
queue<int> q;
inline void read(){//节省空间 ,inline的用法：https://www.cnblogs.com/fnlingnzb-learner/p/6423917.html 
	scanf("%d%d",&u,&v);
	++ru[v];
	to[++num]=v;//存第num条边的v 
	bian[num]=v_u[u];//存第num条边前一条边（属于u） 
	v_u[u]=num;//存属于u的最后一条边 
}
void qiu(){
	for(int i=1;i<=n;++i) if(!ru[i]) q.push(i);
	while(!q.empty()){
		u=q.front(); q.pop();
		pay[u]=before[u]+t[u];//做完u的时间可以确定下来=在做u之前的时间+做u的时间 
		ans=max(ans,pay[u]);//最终解为所有顶点中最晚结束时间 
		for(int i=v_u[u];i;i=bian[i]){//参考read()函数可以更好理解,其实就是遍历u的所有边 
			v=to[i];//此边的v
			--ru[v]; 
			before[v]=max(before[v],pay[u]);//v所有前提的边所需时间,得把u全部做完才能做v
			if(!ru[v]) q.push(v);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&t[i]);
	for(int i=1;i<=m;++i) read();
	qiu();
	printf("%d",ans);
	return 0;
}
```




有没有dalao帮忙解释一下这样写为什么Compile Error
```cpp
# include<cstdio>
# include<queue>
# include<iostream>
using namespace std;
int n,m,num=0,ans=0,u,v;
int t[10005],to[50005],bian[50005],v_u[10005],ru[10005],before[10005],pay[10005];
queue<int> q;
inline void read(){//节省空间 ,inline的用法：https://www.cnblogs.com/fnlingnzb-learner/p/6423917.html 
	scanf("%d%d",&u,&v);
	++ru[v];
	to[++num]=v;//存第num条边的v 
	bian[num]=v_u[u];//存第num条边前一条边（属于u） 
	v_u[u]=num;//存属于u的最后一条边 
}
void qiu(){
	for(int i=1;i<=n;++i) if(!ru[i]) q.push(i);
	while(!q.empty()){
		u=q.front(); q.pop();
		pay[u]=before[u]+t[u];//做完u的时间可以确定下来=在做u之前的时间+做u的时间 
		ans=max(ans,pay[u]);//最终解为所有顶点中最晚结束时间 
		for(int i=v_u[u];i;i=bian[i]){//参考read()函数可以更好理解,其实就是遍历u的所有边 
			v=to[i];//此边的v
			--ru[v]; 
			before[v]=max(before[v],pay[u]);//v所有前提的边所需时间,得把u全部做完才能做v
			if(!ru[v]) q.push(v);
		}
	}
	printf("%d",ans);
	exit(0);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&t[i]);
	for(int i=1;i<=m;++i) read();
	qiu();
}
```

---

## 作者：dingcx (赞：5)

2019.7.20

**好多大佬都用拓扑，由于我太弱了，只好用暴力。**

思路：把每头牛看作一个点，若需要满足先后顺序，则用rule数组记录。

rule[i][j]表示从i发出的第j条线指向的点。这样写的好处是最大化利用数组。

本题及其容易TLE，于是我开了一个f数组，f[i]表示从i点开始往后取至少要用的时间，这样可以防止做过多的冗余运算。

其余的数组中rout[i]表示从i发出线的个数，t[i]表示奶牛i挤奶需要的时间

代码在此~~~

```cpp
#include<cstdio>
#include<algorithm>//算法库
using namespace std;
const int MAXN=10010,MAXM=50010;
int rule[MAXN][MAXM],rout[MAXM],t[MAXN],f[MAXN],ans=0;//如上所述，自动初始化为0
int find(int x){
	if(f[x]) return f[x];//如果以前算过，直接返回
	int maxt=0;//从点x往后取至少要用的时间
	for(int i=1;i<=rout[x];i++){
		maxt=max(maxt,find(rule[x][i]));
	}
	return f[x]=maxt+t[x];//别忘了加上原用时间
}
int main(){
	int n,m,a,b;
	scanf("%d%d",&n,&m);//读入
	for(int i=1;i<=n;i++) scanf("%d",&t[i]);
	while(m--){
		scanf("%d%d",&a,&b);
		rule[a][++rout[a]]=b;
	}
	for(int i=1;i<=n;i++){//求出至少要用的时间ans
		find(i);
		ans=max(ans,f[i]);
	}
	printf("%d",ans);//输出
	return 0;//华丽结束
}
```
~~抄题解不是好习惯~~

update:2019.10.7

时隔两个月，新学了拓扑排序，发现我的方法和拓扑排序还是挺像的。。。

上面的代码虽然不会TLE但是很可能MLE，需要用vector优化。
```cpp
#include<cstdio>
#include<algorithm>
#include<vector>//头文件
using namespace std;
const int MAXN=10010;
vector<int> rule[MAXN];
int t[MAXN],f[MAXN],ans=0;
int find(int x){
	if(f[x]) return f[x];
	int maxt=0;
	for(int i=0;i<rule[x].size();i++){//这里改
		maxt=max(maxt,find(rule[x][i]));
	}
	return f[x]=maxt+t[x];
}
int main(){
	int n,m,a,b;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&t[i]);
	while(m--){
		scanf("%d%d",&a,&b);
		rule[a].push_back(b);//还有这里
	}
	for(int i=1;i<=n;i++){
		find(i);
		ans=max(ans,f[i]);
	}
	printf("%d",ans);
	return 0;
}
```
这样就不会超空间啦~

---

## 作者：编程客 (赞：3)

## 拓扑模板

### 拓扑思路：
- 刚开始建图，我用的是 vector 存图。 存图时要不每个点的入度顺便记录下来。
- 用一个 queue 存当前的点，队列刚开时进了所有入度为零的点。
- 每次取出队头结点，并删除所有以这个点出发的边，同时那个点的入度-1。如果那个点的入度变为零，就入队。
- 最后拓扑排序结果就是各个结点依次入队的顺序。
### 涉及本题
- 本题结果求的是最小时间，即最后一只奶牛挤完牛奶的时间。我们就可以定义一个数组 s[] ,存储当前奶牛挤完奶所需要的时间。
- 最后定义 ans 为 挤奶时间最久的奶牛所需的时间。
### 关于其他
（随便说说，与本题无关。）
- 本人的题解在当时是最优解排行榜中第三，这里分享一下如何成为最优解。
- 洛谷的最优解主要在于时间复杂度和空间复杂的，而时间复杂度又是重中之重。如果大家希望自己的代码成为最优解，最好学习一下快读快写。毕竟也无害处。
- 然后就是你的算法的优虐性了。掌握一门算法，必须要多做题。
## Code
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int n,m,t[10005],s[10005],d[10005],ans;
//        挤奶所需时间     入度    答案 
vector<int> g[10005];// 存边 
queue<int> q;
int read()        //快读 
{
	char c;
	int ans=0;
	int flag=1;
	c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-') flag=-1;
		c=getchar();
	}
	while(c<='9'&&'0'<=c)
	{
		ans=(ans<<3)+(ans<<1)+(c-'0');
		c=getchar();
	}
	return ans*flag;
}
void put_(int t)   //快写 
{
	if(t<0)
	{
		putchar('-');
		t=-t;
	}
	char c[25],i;
	for(i=0;t!=0;i++)
	{
		c[i]=(t%10+'0');
		t/=10;
	}
	for(int j=i-1;j>=0;j--)
	{
		putchar(c[j]);
	}
}
int main()
{
/////////读入///////// 
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		t[i]=read();
	}
	for(int i=1;i<=m;i++)
	{
		int u,v;
		u=read();
		v=read();
		g[u].push_back(v);
		d[v]++;
	}
/////////拓扑排序///////// 
	for(int i=1;i<=n;i++)
	{
		if(d[i]==0)
		{
			s[i]=t[i];
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i];
			s[v]=max(s[v],s[u]+t[v]);   //记录当前奶牛挤牛奶所需要的时间
			d[v]--;
			if(d[v]==0)
			{
				q.push(v);				//入队 
			}
		}
	}
///////////求得答案并输出///////// 
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,s[i]);
	}
	put_(ans);
	return 0;
}
```
希望此篇题解对大家有所帮助。

---

## 作者：Sunlight9 (赞：3)

## 本人思路：拓扑思想+简单模拟  ##
```
这道题其实并不难，只是用到了拓扑的思想，A奶牛必须在B奶牛挤奶前挤奶，这就形成了一个有向图，点A指向点B。
```
#### 我们只需要记一下总量（实际上是每只奶牛挤奶时间的总和），每一次循环将入度为0的奶牛加入要挤奶的数组，并且取挤奶数组的最小值，让在挤奶数组里的奶牛减去最小值，如果一个奶牛挤完奶了，那就删除与它相连的边，并且相连的点入度减一，总时间加上最小值，总量减去最小值*挤奶牛数，直到总量为0结束,如果到这里还不懂可以看代码，代码有更详细的解释。####

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 10007
using namespace std;
int n,m,minn,ans,tot,len;  //n奶牛数目 m有先后要求的量 minn挤奶数组的最小值 ans最后答案  tot总量 len挤奶数组长度 
int a[maxn],ru[maxn],q[maxn];  //a[]每只奶牛挤奶时间 ru[]每只奶牛的入度 q[]挤奶数组 
bool edg[20000][20000];  //二维数组建图（模拟大法好） 
int main()  //程序开始 
{
	scanf("%d%d",&n,&m);   
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),tot+=a[i];  //输入，并且计算总量 
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		ru[y]++;  //x指向y  y入度+1 
		edg[x][y]=1;  //建图 
	}
	while(tot)  //直到总量为0结束 
	{
		minn=0x7fffffff;  //先赋一个最大值 
		len=0; 
		memset(q,0,sizeof(q));  //挤奶数组长度、内容清零 
		for(int i=1;i<=n;i++)
		{
			if(!ru[i]&&a[i]>0)  q[++len]=i,minn=min(minn,a[i]);  //找还有奶并且入度为0的奶牛加入挤奶数组 && 计算挤奶最小值 
		}
		for(int i=1;i<=len;i++)
		{
			a[q[i]]-=minn;  //每只挤奶奶牛减去最小值 
			if(a[q[i]]<=0)  //处理没奶的奶牛 
			{
				for(int j=1;j<=n;j++)
				{
					if(edg[q[i]][j]==1)  ru[j]--,edg[q[i]][j]=0;  //删除和它相连的所有边以及和它相连点的入度 
				}
			}
		}
		tot-=(minn*len);  //总量减去（最小值*挤奶奶牛数） 
		ans+=minn;   //需要时间（答案）加上最小值 
	}
	printf("%d",ans);  //输出 
	return 0;  //程序结束 
}
```
##### 另外嘱咐大家一句：数组一定要够大，否则[RE](https://www.luogu.org/record/show?rid=12080872) #####
## 最后祝大家
# RP++；
###### 拒绝代码抄袭，共建美好洛谷。

---

## 作者：Vimpire_D (赞：3)









```cpp
//~~一个最经典的拓扑排序~~ 
//看到这种存在先后关系的题目，我们应该立刻想到拓扑
//先打一个拓扑的模板，然后在排序的时候求最大值就可以了
//不多说了，放代码
#include <bits/stdc++.h>
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
#define f(i,a,b) for(int i=a;i<=b;i++)
#define LL long long 
using namespace std;
const int Ma=50000+10;
int n,m,cnt,cen,ans,mx;
int chu[Ma],head[Ma],num[Ma],tim[Ma],t[Ma];
struct node {
    int u,v,next;
}e[Ma];
void add(int x,int y) {
    e[++cnt].u=x;e[cnt].v=y;e[cnt].next=head[x];
    head[x]=cnt;
}
queue <int> q;
void BFS() {
    while (!q.empty())
    {
        int root=q.front();q.pop();
        tim[root]=num[root]+t[root];
        mx=Max(mx,tim[root]);
        for (int i=head[root],to;i,to=e[i].v;i=e[i].next)
        {  
                chu[to]--;
                num[to]=max(num[to],tim[root]);
                if (!chu[to]) 
                {
                    q.push(to);
                 }         
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    f(i,1,n) scanf("%d",&t[i]);
    f(i,1,m) {
        int a,b;
        scanf("%d%d",&a,&b);
        add(b,a);
        chu[a]++;
    }
    f(i,1,n) 
        if (!chu[i]) q.push(i);
    BFS(); 
    printf("%d",mx);
    return 0;
}
```

---

## 作者：MessiYT (赞：3)

#看到题目，就看到了先后关系：X必须在Y之前挤奶。那会让我们想到什么？

#拓扑！

##没错，拓扑就是可以用来解决带有这种先后关系的题目。（写第一篇题解的大佬用了并查集，我不知道拓扑是不是正解）

###那该怎么处理呢？假设我们有一个父节点X，我们可从X众多的儿子节点中找出一个最大的值，然后用该时间加上挤X 的时间与已求好的挤到X的时间。

###可能类似于DP（或求最长路径，有这种意思）

上代码（有不懂可以私信，代码有注释）：



```cpp
var
  n,m,i,tot,x,y,ans:longint;
  link,f,q,dis:array[0..10005] of longint;
  next,w,son:array[0..50005] of longint;
  function max(a,b:longint):longint;  //求出a,b两者的较大值
  begin
    if a>b then exit(a)
           else exit(b);
  end;
  procedure BFS;
  var
    h,t,i,j:longint;
  begin
    h:=0;
    t:=0;
    for i:=1 to n do
    if f[i]=0 then
    begin
      inc(t);
      q[t]:=i;
      dis[i]:=w[i];  //寻找到入度为0的点（即叶子节点）将其入队
    end;
    while h<>t do
    begin
      inc(h);  //要省空间可以滚起数组来
      j:=link[q[h]];  //取q[h]的最后一条边的编号
      while j<>0 do
      begin
        dec(f[son[j]]);  //这个点已经被遍历过，因此将它的儿子节点的入度减一
        dis[son[j]]:=max(dis[son[j]],dis[q[h]]+w[son[j]]);  //刷最大值“最长路径”
        if f[son[j]]=0 then
        begin
          inc(t);
          q[t]:=son[j];  //如果它的儿子节点全部被遍历过，那么就入队
        end;
        j:=next[j];  //取第j条边的上一条边的编号
      end;
    end;
    ans:=0;
    for i:=1 to n do ans:=max(ans,dis[i]);  //刷一趟答案
  end;
begin
  readln(n,m);  
  for i:=1 to n do readln(w[i]);  //帅气的读入
  for i:=1 to m do
  begin
    readln(x,y);
    inc(f[y]);  //统计一个点的入度
    inc(tot);
    son[tot]:=y;
    next[tot]:=link[x];
    link[x]:=tot;  //高端的邻接表建图
  end;
  BFS;  //使用无敌的BFS版拓扑
  writeln(ans);  //绝对正确的输出
end.
```

---

## 作者：OI_AKed_me (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/P3074)

这道题大部分人都是写拓补排序的，我补充一下巨佬 [dingcx](https://www.luogu.com.cn/user/130981) 的做法，可能也算是拓补排序的一种吧。

其实这种做法可以理解成一开始我们有许多棵树，我们要做的就是找到一条从根走到叶，走过的点的和最大。以下面这组样例为例：
```
10 5
1 2 3 4 5 6 7 8 9 10
1 3
2 3
3 5
4 5
5 7
```

![](https://cdn.luogu.com.cn/upload/image_hosting/9e6fcz1u.png)

我们可以把点 $1$、$2$、$4$、$6$、$8$、$9$、$10$ 当作树根，要走到其对应的叶子节点。

对于这个问题，我们可以使用深搜解决，把每个点当作根进行搜索，时间复杂度最坏为 $O(n^2)$，妥妥的 TLE，考虑剪枝。

我们发现，我们在做的时候会有很多重复的情况，以上图为例，$5$ 会被走到 $3$ 次，这就导致了许多重复的查询，我们可以采用记忆化，即记录每个点的结果，当再次访问时就不必再重做一遍，这样就可以把复杂度优化到 $O(n)$。

以下是代码的核心部分，记忆化搜索：
```cpp
int sum(int k){
	int cnt=0;
	if(b[k]) return t[k];
	for(int i=0;i<v[k].size();i++){
		cnt=max(sum(v[k][i]),cnt);
	}
	b[k]=1;
	t[k]=cnt+t[k];
	return t[k];
}
```
其中 ```b``` 数组用于记录每个点的结果是否算过，``` t ``` 数组即输入进来的数，```v``` 数组记录子节点，应开成 ```vector```，否则会 MLE。在主函数中就直接便利每个点即可，最后取最大值。

---

## 作者：arrow_king (赞：1)

# 算法：拓扑排序+邻接表
我们一看题目中这句话：
>如果奶牛A必须在奶牛B前挤奶，FJ就需要在给奶牛B挤奶前结束给奶牛A的挤奶。

就知道这道题一定是拓扑排序题。
但是这道题虽然是图论题，但是权值却不能存在边上，而要存储在节点上。我们定义一个数组 $w$，令 $w_i$ 标识第 $i$ 头奶牛挤奶所需的时间。    
至于计算时间，只需要在拓扑排序中计算就行了。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define maxm 50010
#define maxn 10005
struct Edge {    //邻接表
    int next,to;
};
Edge edge[maxm];
int head[maxn],num_edge;
void add_edge(int from,int to) {    //建边
    edge[++num_edge].next=head[from];
    edge[num_edge].to=to;
    head[from]=num_edge;
}
int n,m;
int w[maxn],rd[maxn];    //rd[i]表示第i个节点的入度
int st[1000005],top=0;
int f[maxn];    //记录最大值
int Max(int a,int b) {
    return a>b?a:b;
}
void topsort() {    //拓扑排序
    for(int i=1;i<=n;i++)
        if(rd[i]==0) {
            st[++top]=i;
            f[i]=w[i];
        }
    while(top>0) {
        int u=st[top];
        top--;
        for(int i=head[u];i;i=edge[i].next) {
            int v=edge[i].to;
            f[v]=Max(f[v],f[u]+w[v]);    //三角不等式计算最大值
            rd[v]--;
            if(rd[v]==0) st[++top]=v;
        }
    }
    int ans=-100000000;
    for(int i=1;i<=n;i++) ans=max(ans,f[i]);
    printf("%d\n",ans);
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    for(int i=1;i<=m;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);    //建立一条从u到v的边，表示必须先给u挤奶再给v挤奶
        rd[v]++;    //计算入度
    }
    topsort();
    return 0;
}
```

---

## 作者：梦离 (赞：1)

**这题其实是真的简单，但是有些细节要注意**

**大概就是每一头牛都开个数组存它之前必须要挤奶的牛，再定义一个更新数组，然后走一遍O(n)的循环，每次去找前面的牛是否更新，没有更新就更新再将更新数组标1，已经全部更新了就找其中所需时间最长的加上自己的时间，然后再将自己标为已更新，最后再走一遍循环找最大的时间就可以了(ps:如果一头牛更新两次的话，超时不说，而且每次数值也会变掉，必定WA)**

**AC代码：**

’‘’

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int chu[10005][10005]/*存前牛*/,t[10005],cen=0,gg[10005],n,m,gen[10005];
int milk(int u)//更新
{
    int ans=0;
    if(!chu[u])
    return t[u];
    else
    for(int i=1;i<=chu[u][0];i++)
    {
        if(!gen[chu[u][i]])//如果没有更新就更新
        {
            gen[chu[u][i]]=1;
            t[chu[u][i]]=milk(chu[u][i]);
        }
        ans=max(ans,t[chu[u][i]]);
    }
    t[u]+=ans;
    gen[u]=1;//标为已更新
    return t[u];
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
      cin>>t[i];
    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin>>b>>a;
        chu[a][0]++;
        chu[a][chu[a][0]]=b;//存之前的牛
    }
    for(int i=1;i<=n;i++)
    {
        if(!gen[i])//如果已经更新就不需要更新了，不然会WA
        milk(i);
    }
    for(int i=1;i<=n;i++)
    {
        cen=max(cen,t[i]);
    }
    cout<<cen<<endl;
    return 0;
}
‘’‘
```

---

## 作者：Bruce__Lee (赞：0)

其实吧，这题也还是个dfs啦，哈哈哈，
好了不开玩笑了，其实本题确实是个topo最长路嘛，一旦是个topo最长路，就可以运用我们熟悉的dfs啦，实际上就是记忆化搜索。

每个点x设置一个dp值，该值意味着在x点做完后，所需要的最短时间，也就是以x结尾的最长路距离
用题目的例子来说的话， 3 在 2前面必须做完， 我们就可以建一个反向边，让2 连着 3，在dfs过程中，寻找与自己相连的边的dp值最大，然后加上该点的初始值就行啦。

如果有不明白的朋友可以画画图哦，~~其实是我太菜了不知道在题解区怎么画图~~

下面是代码：

~~~
//#pragma GCC optimize(2)

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<vector>
#define ls (k << 1)
#define rs (ls | 1)
using namespace std;
typedef long long ll; 
typedef unsigned long long ull;
typedef pair<int, int> P; 
typedef pair<ll, ll> pll; 
const int mod = 1e9 + 7;
const int N = 1e5 + 5;
struct ed{
	int to, nxt;
}e[N << 1];
int head[N], tot = 1;
void add(int u, int v){
	e[tot].to = v, e[tot].nxt = head[u], head[u] = tot++;
}
int dp[N], st[N], n, m, ans;
int dfs(int x)
{
	if (dp[x])	return dp[x];
	int mx = 0;
	for (int i = head[x]; i; i = e[i].nxt)
	{
		mx = max(mx, dfs(e[i].to));
	}
	return dp[x] = st[x] + mx;
}
int  main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &st[i]);	
	}	
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(b, a);
	}
	for (int i = 1; i <= n; i++)
	{
		ans = max(ans, dfs(i));
	}
	printf("%d\n", ans);
}
~~~


---

## 作者：yz0414 (赞：0)

### 一看到题目就想到这题得用拓扑

首先计算每个点的入度，为零就加入队列。接着宽搜spfa框架，做一条边删一条边，如果当前点入度为零，就加入队列，直到搜完。最后输出最大值

代码：
```pascal
var a,b,c,d,e,v,u:array[0..50001]of longint;
    n,m,i,x,y,t,w,max:longint;
begin
   readln(n,m);
   for i:=1 to n do read(v[i]);
   for i:=1 to m do
     begin
        readln(x,y);inc(u[y]);
        a[i]:=y;b[i]:=c[x];c[x]:=i;
     end;
   for i:=1 to n do
     if u[i]=0 then
      begin inc(w);d[w]:=i;e[i]:=v[i]; end;
   t:=1;
   while t<=w do
     begin
        i:=c[d[t]];
        while i<>0 do
          begin
             dec(u[a[i]]);
             if e[d[t]]+v[a[i]]>e[a[i]] then
              e[a[i]]:=e[d[t]]+v[a[i]];
             if u[a[i]]=0 then
              begin inc(w);d[w]:=a[i]; end;
             i:=b[i];
          end;
        t:=t+1;
     end;
   for i:=1 to n do
     if e[i]>max then max:=e[i];
   writeln(max);
end.

```


---

## 作者：psk011102 (赞：0)

这道题开始我还以为是个并查集，后面发现原来有多个前提，于是用结构体来存控制关系就行了。

代码如下

```cpp
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 10005
#define ll long long
#define F(a,b,c) for(int a=b;a<=c;++a)
#define f(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
struct node{
    int fa,son;
};//结构体来定义从属关系 
vector<node>con;//控制关系存起来 
vector<int>k[maxn]; 
int n,m,t[maxn],control[maxn],d[maxn]; 
int read(){
    int x=0;
    char c=getchar();
    while(!isdigit(c)){
        c=getchar();
    }
    while(isdigit(c)){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
    return x;
```
}//快读
```cpp
int main(){
n=read();
m=read();
F(i,1,n){
    t[i]=read();
}
F(i,1,m){
    int u=read(),v=read();
    con.push_back((node){u,v});
    control[v]++;//表示这头牛挤奶的要求又多一条 
    k[u].push_back(con.size()-1);//表示u这头牛是多少牛挤奶的前提 
}
queue<int>milk;//表示挤过奶的牛。 
F(i,1,n){
    if(!control[i])milk.push(i);//把前提为0的入队。 
}
int minmax=0;
while(!milk.empty()){
    int fr=milk.front(); 
    milk.pop();//从队首开始消除前提条件。 
    d[fr]+=t[fr]; //他等待的时间等于他的前提加上他自己的时间 
    minmax=max(minmax,d[fr]);
    int r=k[fr].size();//需要消除的牛的数量 
    F(i,0,r-1){
        d[con[k[fr][i]].son]=max(d[con[k[fr][i]].son],d[fr]);
        if(--control[con[k[fr][i]].son]==0)milk.push(con[k[fr][i]].son);//如果前提变为0了就挤奶。 
    }
}
cout<<minmax<<endl;
return 0;
}
```

---

