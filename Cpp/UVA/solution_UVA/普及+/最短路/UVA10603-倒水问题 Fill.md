# 倒水问题 Fill

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1544

[PDF](https://uva.onlinejudge.org/external/106/p10603.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/2d3a044bd29738a849110d68bb92f13a9aef7016.png)

## 样例 #1

### 输入

```
2
2 3 4 2
96 97 199 62```

### 输出

```
2 2
9859 62```

# 题解

## 作者：昤昽 (赞：10)

[UVa 10603 Fill](https://www.luogu.org/problemnew/show/UVA10603)

---
此题是一道经典的搜索题，但其实又是一道经典的“**隐式图最短路**”问题。

将当前三个杯子中的水量 $(x,y,z)$ 视作“**结点**”，结点之间的**路径长度**即为倒水量。题目中要求求解倒水量最少，即求 $(0,0,c)$ 与某一结点 $u$ 之间的最短路，其中 $u$ 的某一杯子中的水量为 $d$ 或 $d'$

很明显这个图的边权都为正数，因此可以用 Dijkstra 算法。

需要注意：
1. 状态的存储：由前两个杯子中的水量即可确定第三只杯子中的水量
2. 答案的更新：有可能有多个结点的水量中都包含$d$，因此利用每一个已经得到最短路的结点的$dist$对答案进行更新

```cpp
//Copyright(C)Corona.
//2018-09-28
//Dijkstra
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN=200+1;
int vis[MAXN][MAXN],dis[MAXN][MAXN];
int jug[3],ans[MAXN];

struct Node
{
    int v[3],dist;
    Node(int a,int b,int c,int d)
    {
        v[0]=a;v[1]=b;v[2]=c;
        dist=d;
    }
    
    bool operator < (const Node& rhs)
    const{
        return dist > rhs.dist;
    }
};

void update_ans(Node u)
{
    for(int i=0;i<3;i++)
    {
        int amount=u.v[i];
        if(ans[amount] < 0 || ans[amount] > u.dist)
            ans[amount] = u.dist;
    }
}

void Dijkstra(int a,int b,int c,int d)
{
    jug[0]=a;jug[1]=b;jug[2]=c;
    
    memset(ans,-1,sizeof(ans));
    memset(vis,0,sizeof(vis));
    memset(dis,0x7f,sizeof(dis));	
    
    priority_queue<Node>Q;
    
    Q.push(Node(0,0,c,0));
    dis[0][0]=0;
    
    while(!Q.empty())
    {
        Node u=Q.top();Q.pop();
        if(vis[u.v[0]][u.v[1]])continue;
        
        vis[u.v[0]][u.v[1]] = 1;
        update_ans(u);
        
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(i != j)
                {
                    int amount=min(u.v[i],jug[j]-u.v[j]);//将 i 中的水倒入 j 中;
                    Node x=u;
                    x.v[i] -= amount;x.v[j] += amount;
                    x.dist = u.dist + amount;
                    if(!vis[x.v[0]][x.v[1]] && dis[x.v[0]][x.v[1]] > x.dist)
                    {
                        dis[x.v[0]][x.v[1]] = x.dist;
                        Q.push(x);
                    }
                }
    } 
}

void print_ans(int aim)
{
    for(int d=aim;d>=0;d--)
        if(ans[d] >=0 )
        {
            cout << ans[d] <<" "<< d <<endl;
            break;
        }
}
int main()
{	
    int T;
    cin >> T;
    while(T--)
    {
        int a,b,c,d;
        cin >>a>>b>>c>>d;
        Dijkstra(a,b,c,d);
        print_ans(d);
    }
    return 0;
}
```

当然,$Dijkstra$算法可以,$Bellman-Ford$算法自然也可以.
```cpp
//Copyright(C)Corona.
//2018-09-28
//Bellman_Ford 
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
const int MAXN = 200+1;
int dis[MAXN][MAXN],ans[MAXN],cap[3];
int inq[MAXN][MAXN];

struct Node
{
    int v[3],dist;
    Node(int a=0,int b=0,int c=0,int d=0)
    {
        v[0]=a;v[1]=b;v[2]=c;
        dist=d;
    }
};

void update_ans(Node u)
{
    for(int i=0;i<3;i++)
    {
        int amount=u.v[i];
        if(ans[amount] < 0 || ans[amount] > u.dist)
        {
            ans[amount] = u.dist;
        }
    }
    
}
void print_ans(int aim)
{
    for(int d=aim;d>=0;d--)
        if(ans[d] >=0 )
        {
            cout << ans[d] <<" "<< d <<endl;
            break;
        }
}

queue<Node>Q;

void Bellman_Ford(int a,int b,int c,int d)
{
    cap[0]=a;cap[1]=b;cap[2]=c;
    
    memset(ans,-1,sizeof(ans));
    memset(dis,0x7f,sizeof(dis));   
    memset(inq,0,sizeof(inq));
    
    Q.push(Node(0,0,c,0));
    dis[0][0]=0;
    inq[0][0]=true;
    
    while(!Q.empty())
    {
        Node u=Q.front();Q.pop();
        u.dist=dis[u.v[0]][u.v[1]];
        inq[u.v[0]][u.v[1]]=0;
        
        update_ans(u);
        
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(i != j)
                {
                    int amount=min(u.v[i],cap[j]-u.v[j]);//将 i 中的水倒入 j 中;
                    
                    Node x=u;
                    
                    x.v[i] -= amount;
                    x.v[j] += amount;
                    x.dist = u.dist + amount;
                    
                    if(dis[x.v[0]][x.v[1]] > x.dist)
                    {
                        dis[x.v[0]][x.v[1]] = x.dist;
                        if(!inq[x.v[0]][x.v[1]])
                        {
                            Q.push(x);
                            inq[x.v[0]][x.v[1]]=1;
                        }
                    }
                }
    }
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int a,b,c,d;
        cin >>a>>b>>c>>d;
        Bellman_Ford(a,b,c,d);
        print_ans(d);
    }
    return 0;
}
```

---

## 作者：d3NtMDAw (赞：4)

# 1.先说判重   
由于第二次搜到的答案一定比第一次劣，所以一定要有判重。   
假设在某一时刻，第一杯杯子里有v0升水，第二个杯子里有v1升，第三个里有v2升，称当时的系统状态为 **(v0,v1,v2)**.(以后有时间再附上个手绘的节点图和更详细的说明)   
由于无论怎么到，杯子中的水量总是整数。所以3号杯的数量只有**0,1,2,...c**共c+1种可能，同理2号杯一共只有b+1种可能，1号杯一共只有a+1种可能。以此理论上状态最多有**201^3=8120601**，看起来很大，实际上水量不变，前两个杯子的水量相同，第三个杯子也相同。换句话说，最多的可能状态数不会超过**201^2=40401**.
```cpp
int vis[maxn][maxn];
```
```cpp
if(!vis[u2.v[0]][u2.v[1]]){
   vis[u2.v[0]][u2.v[1]]=1;
   q.push(u2);	
}
```

------------

# 2. 算法 
本题最大的坑点就是他要求的是倒的水量最少~~(步数最少)~~，所以我们要用优先队列替换掉队列.下面的代码把状态和dist合起来定义为一个Node类型。
```cpp
struct Node
{
	int v[3],dist;
	bool operator <(const Node& rhs) const {
	 return dist > rhs.dist;	
	}
};
```
```cpp
priority_queue<Node> q;
```

接下来就是进行一次搜索，核心代码如下
```cpp
    Node start;
	start.dist=0;
	start.v[0]=0;start.v[1]=0;start.v[2]=c;
	q.push(start);
	vis[0][0]=1;
	while(!q.empty())
	{
	 Node u=q.top();q.pop();
	 update_ans(u);
	 if(ans[d]>=0)
	   break;
	 for(int i=0;i<3;i++)
	  for(int j=0;j<3;j++)
	  if(i!=j)
	  {
	  	if(u.v[i]==0||u.v[j]==cap[j])continue;
	  	int amount=min(cap[j],u.v[i]+u.v[j])-u.v[j];
	  	Node u2;
	  	memcpy(&u2,&u,sizeof(u));
	  	u2.dist=u.dist+amount;
	  	u2.v[i]-=amount;
	  	u2.v[j]+=amount;
	  	if(!vis[u2.v[0]][u2.v[1]])
	  	{
	  	  vis[u2.v[0]][u2.v[1]]=1;
		  q.push(u2);	
	  	}
	  }	
	}
	while(d>=0)
	{
		if(ans[d]>=0)
		{
		  printf("%d %d\n",ans[d],d);
		  return ;	
		}
		d--;
	}
```


---

## 作者：珈乐唯毒 (赞：2)

本题很明显是广搜 ~~毕竟算法标签里都写了呢~~

首先，我们思考一下本题中的状态如何描述。

不难想到对于一个状态首先需要知道3个杯子中的水量，状态总数为 201^3。这个数据有一点危险。

但是进一步思考发现，由于总水量确定，我们实际上知道两个杯子中的水量就已经足够了，状态总数应该为 201^2。 

对于每一个状态，有6种转移方式，即 a往b中倒，a往c中倒.....

但是普通的广搜是不行的。每个状态并不一定在第一次被访问到时取到最优值。因为我们第一次访问到一个状态时，只能保证倒水次数最少，而不是倒水量最少。

因此要使用优先队列来储存，每一次取水量最少的状态（有点像最短路）

上AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,ma,mb,mc,d,ans[1005];
int ta,tb,tc,sa,sb,sc,ss,t,cost;
struct lyf{
	int x,y,s;
	lyf(int a,int b,int c){
		x=a;
		y=b;
		s=c;
	}
	bool operator < (const lyf& l) const{
		return s>l.s;
	} 
};
priority_queue<lyf> q; 
bool vis[201][201];
void c_a(){
	tb=sb;
	ta=sc+sa;
	tc=0;
	if(ta>ma){
		tc=ta-ma;
		ta=ma;
	}
	return;
}
void c_b(){
	ta=sa;
	tb=sc+sb;
	tc=0;
	if(tb>mb){
		tc=tb-mb;
		tb=mb;
	}
	return;
}
void a_b(){
	tc=sc;
	tb=sa+sb;
	ta=0;
	if(tb>mb){
		ta=tb-mb;
		tb=mb;
	}
	return;
}
void b_a(){
	tc=sc;
	ta=sb+sa;
	tb=0;
	if(ta>ma){
		tb=ta-ma;
		ta=ma;
	}
	return;
}
void a_c(){
	tb=sb;
	tc=sa+sc;
	ta=0;
	if(tc>mc){
		ta=tc-mc;
		tc=mc;
	}
	return;
}
void b_c(){
	ta=sa;
	tc=sb+sc;
	tb=0;
	if(tc>mc){
		tb=tc-mc;
		tc=mc;
	}
	return;
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>ma>>mb>>mc>>d;
		a=0;
		b=0;
		memset(vis,0,sizeof(vis));
		for(int i=0;i<=d;i++)ans[i]=300000;
		vis[0][0]=1;
		q.push(lyf(0,0,0));
		while(!q.empty()){
			sa=q.top().x;
			sb=q.top().y;
			ss=q.top().s;
			q.pop();
			sc=mc-sa-sb;
			ans[sa]=min(ans[sa],ss);
			ans[sb]=min(ans[sb],ss);
			ans[sc]=min(ans[sc],ss);
			a_c();
			if(vis[ta][tb]==0){
				q.push(lyf(ta,tb,ss+tc-sc));
				vis[ta][tb]=1;                    
			}
			b_c();
			if(vis[ta][tb]==0){
				q.push(lyf(ta,tb,ss+tc-sc));
				vis[ta][tb]=1;                    
			}
			a_b();
			if(vis[ta][tb]==0){
				q.push(lyf(ta,tb,ss+tb-sb));
				vis[ta][tb]=1;                    
			}
			c_a();  
			if(vis[ta][tb]==0){
				q.push(lyf(ta,tb,ss+ta-sa));
				vis[ta][tb]=1;
			}
			c_b();  
			if(vis[ta][tb]==0){
				q.push(lyf(ta,tb,ss+tb-sb));
				vis[ta][tb]=1;
			}
			b_a();     
			if(vis[ta][tb]==0){        
				q.push(lyf(ta,tb,ss+ta-sa));
				vis[ta][tb]=1;
			}
		}
		for(int i=d;i>=0;i--){
			if(ans[i]!=300000){
				cout<<ans[i]<<' '<<i<<endl;
				break;
			}
		}	
	}
	return 0;
} 
```


---

## 作者：EPSILONCXL (赞：2)

### 题目简述

有三个有刻度的水壶，容量分别为$a,b,c$，其中$a,b,c\leq 200$。初始时前两个水壶是空的，只有第三个装满了水。每次可以从一个水壶往另一个水壶注水，直到一个水壶倒空或者另一个水壶倒满。为了使某个水壶恰好有$d$升水，求至少要倒多少升水。如果无解，则找出一个最接近$d$的$d'$。



### 输入数据

第一行输入一个数$n$。表示测试数据的组数。

接下来$n$行，每一行输入三个整数$a,b,c$，如题面所示。



### 输出数据

输出数据一共$n$行。

每一行两个数据$x,y$，分别表示为了使某个水壶恰好有$y$升水，至少要倒$x$升水。$y\in\{d,d'\}$。



### 题解

用$BFS$搜索。

考虑如何设计$BFS$的状态。对每一个状态，首先我们需要知道当前状态每一个水壶的水量，也许要知道当前状态已经倒了多少升水了。所以我们用一个结构体保存上述四个信息，用这个结构体作为状态。为了方便起见，我们把每一个水壶的水量保存在一个数组内。

考虑如何设计$BFS$的转移。对当前状态，选择任意两个合法的杯子倒水，记录下倒水的量。这里，合法是指需要满足一下两个条件：

1）倒水的杯子水量不能为0

2）被倒水的杯子水量不能满

题目要求的是求至少要倒多少升水，而不是至少需要倒几次水。所以我们为了方便及时找到答案所在的状态，我们在$BFS$时，优先搜索倒水量少的，所以我们需要用到优先队列。

特别值得注意的是，对当前的状态，如果之前搜索的时候已经搜索过了，那么我们就不需要继续搜索了。（因为我们是按照倒水量从小到大搜索的，所以当前的状态的倒水量必定≥之前搜索的时候的倒水量。

考虑如何设计$ans$的处理。我们将每一个$y,y\in\{d,d'\}$保存下来即可。

至此，算法框架已经形成。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=205;
template<typename t>void read(t &x)
{
	x=0;int f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x=x*f;
}
struct node
{
	int w[5];
	int num;
	node(int a=0,int b=0,int c=0,int d=0){w[1]=a;w[2]=b;w[3]=c;num=d;}
	bool operator <(const node &x)const 
	{
		return x.num<num;
	}
};

int used[maxn][maxn],a[maxn],ans[maxn];
int n,d;

void mark(node u)//记录当前的答案
{
	for(int i=1;i<=3;i++)
	{
		int tmp=u.w[i];
		if(ans[tmp]==-1 || ans[tmp]>u.num)ans[tmp]=u.num;
	}
}

void BFS()
{
	memset(used,0,sizeof(used));
	priority_queue<node>q;
	q.push(node(0,0,a[3],0));
	while(!q.empty())
	{
		node u=q.top();q.pop();
		used[u.w[1]][u.w[2]]=1;
		mark(u);
		if(ans[d]>=0)break;
		for(int i=1;i<=3;i++)
		{
			for(int j=1;j<=3;j++)
			{
                //将i杯子里面的水倒入j杯子
				if(j==i)continue;
				if(!u.w[i])continue;
				if(u.w[j]==a[j])continue;
				int water=0;
				if(u.w[i]>a[j]-u.w[j])water=a[j]-u.w[j];//i杯子的水有剩
				else water=u.w[i];
	
				node v=u;
				v.w[i]-=water;
				v.w[j]+=water;
				v.num+=water;
				if(!used[v.w[1]][v.w[2]])//剪枝
				{
					q.push(v);	
				}
			}
		}
	}
	while(d>=0)//输出答案
	{
		if(ans[d]>=0)
		{
			printf("%d %d\n",ans[d],d);
			return;
		}
		d--;
	}
}

int main() 
{
	read(n);
	while(n--)
	{
		memset(ans,-1,sizeof(ans));
		for(int i=1;i<=3;i++)
		{
			read(a[i]);
		}
		read(d);
		BFS();
	}
    return 0;
}
```







---

## 作者：_Aghost (赞：1)

## 题目大意
三个容量分别为$a$,$b$,$c$的容器，初始状态只有$c$装满，$a$,$b$都为空，需要计算出如何最少需要倒多少升水才能让其中某一个杯子中的水有$d$升。如果能够找到这样的$d$，你还是需要计算出其中某一个杯子达到$d$升时，最少需要倒多少升水。
## 状态设置
怎么标记一个状态有没有出现过呢？ 如果用一个三维数组表示，我们发现总数是一定的，最后一维一定是确定的，那么它就没有作用了，因此可以用一个二维数组表示状态，$v[i][j]$表示$a$有$i$升水，$b$有$j$升水是否出现过，状态总数 $ 201 \times $ $201$。

对于一个状态，可以用结构体来存储，还要存储到这个状态需要的倒水数，那么怎么让倒水数最少呢？考虑用优先队列来维护这个状态，以倒水数为关键字排序。
### 模拟过程
模拟从三个水桶里面的倒水过程，注意每个水桶有最大的容量，而且水桶容量不能为$0$。
### 答案统计
如果目标水量已经出现过直接终止操作。否则就找最接近的。
## Code
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
int a,b,c,d,T,cap[3];
bool v[210][210];
int ans[210];
struct Node{
	int v[3];
	int d;
	bool operator < (const Node& j) const{
		return d>j.d;
	}
};
void update(const Node& x)
{
	for(int i=0;i<3;i++)
	{
		int t=x.v[i];
		if(ans[t]<0||x.d<ans[t]) ans[t]=x.d;
	}
}
void solve(int a,int b,int c,int d)
{
	cap[0]=a;cap[1]=b;cap[2]=c;
	priority_queue<Node> q;
	memset(v,0,sizeof(v));
	memset(ans,-1,sizeof(ans));
	Node x; 
	x.v[0]=0;x.v[1]=0;x.v[2]=c;x.d=0;
	q.push(x);
	v[0][0]=1;
	while(!q.empty())
	{
		Node now=q.top();
		update(now);
		q.pop();
		if(ans[d]>=0) break;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Node t;
				if(now.v[i]==0||now.v[j]==cap[j]) continue;
				int p=min(cap[j],now.v[i]+now.v[j])-now.v[j];
				t=now;
				t.v[i]-=p;
				t.v[j]+=p;
				t.d+=p;
				if(!v[t.v[0]][t.v[1]])
				{
					v[t.v[0]][t.v[1]]=1;
					q.push(t);
				}
			}
		}
	}
	while(d>=0)
	{
		if(ans[d]>=0)
		{
			printf("%d %d\n",ans[d],d);
			return;
		}
		d--;
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		solve(a,b,c,d);
	}
}
```



---

## 作者：ccg12345 (赞：0)

本题为紫书例题，引用下主要思路。


### 题目大意

设 $3$ 个杯子的容量分别为 $a$,$b$,$c$，起初只有第三个杯子装了 $c$ 升水，其他两个杯子为空，最少需要多少升水才能使某个杯子的水有 $d$ 升呢？如果无法做到刚好 $d$ 升，就让某一个杯子里的水是 $d'$ 升，其中 $d' < d$ 且尽量接近 $d$。要求输出最少的倒水量和目标水量。

### 分析

假设在某一时刻，第一个杯子有 $t_0$ 升水，第二个杯子有 $t_1$ 升水，第三个杯子有 $t_2$ 升水，则称此时的状态为 ($t_0$,$t_1$,$t_2$)。

由于无论如何倒，杯子中的水量均为整数，因此第三个杯子的水量有 $c+1$ 种情况（一与二同理）。

因此，理论上的状态最多有 $(a + 1)(b + 1)(c + 1)$ 即  $8120601$ 种情况，但这个估计不准确，由于总数 $c$ 固定，如果状态中两个相同，则另一个也相同，所以最多有 $201^2$ 为 $40401$ 种情况。

所以，我们的算法应该是取出水量最少的节点进行拓展。只需把队列 `queue` 换成优先队列 `priority_queue`。如果要打印路径，需要把访问过的节点放在一个 `node` 数组中。然后在 `node` 数组中加一个变量 $fa$，表示父节点在 `node` 数组中的下标，而在队列中只存节点在 `node` 数组中的下标而非节点本身。
```
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int v[3], dist;
    bool operator < (const Node& rhs) const
    {
        return dist > rhs.dist; 
    }
};
int vis[205][205], cap[8], ans[205];
void update_ans(const Node& u)
{
    for(int i = 0; i < 3; i++)
    {
        int d = u.v[i];
        if(ans[d] < 0 || u.dist < ans[d])
            ans[d] = u.dist;
    }
}

void solve(int a, int b, int c, int d)
{
    cap[0] = a; 
    cap[1] = b;
    cap[2] = c;
    memset(vis, 0, sizeof(vis));
    memset(ans, -1, sizeof(ans));
    priority_queue<Node> q;

    Node start;
    start.dist = 0;
    start.v[0] = 0;
    start.v[1] = 0;
    start.v[2] = c;
    q.push(start);

    vis[0][0] = 1;
    while(!q.empty())
    {
        Node u = q.top(); q.pop();
        update_ans(u);
        if(ans[d] >= 0)
            break;

        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(i != j)
                {
                    if(u.v[i] == 0 || u.v[j] == cap[j])
                    	continue;
                    int amount = min(cap[j], u.v[i] + u.v[j]) - u.v[j];
                    Node u2;
                    memcpy(&u2, &u, sizeof(u));
                    u2.dist = u.dist + amount;
                    u2.v[i] -= amount;
                    u2.v[j] += amount;
                    if(!vis[u2.v[0]][u2.v[1]])
                    {
                    	vis[u2.v[0]][u2.v[1]] = 1;
                    	q.push(u2);
					}
				}
	}
	while(d >= 0)
	{
		if(ans[d] >= 0)
		{
			printf("%d %d", ans[d], d);
			return;
		}
		d--;
	}
}
int main()
{
	int n, a, b, c, d;
	cin >> n;
	while(n--)
	{
		cin >> a >> b >> c >> d;
		solve(a, b, c, d);
	}
	return 0;
}
```


---

