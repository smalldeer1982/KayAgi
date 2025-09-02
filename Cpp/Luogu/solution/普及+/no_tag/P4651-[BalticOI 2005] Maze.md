# [BalticOI 2005] Maze

## 题目描述

给出一个平行四边形的长与高. 给出入口与出口,对于四边形的每条边都有一种Color,非黑即白. 你要找出一条路径,走过的边黑白交替,且长度最短

## 说明/提示

对于第一个数据:

(0, 0) -> (1, 0) -> (0, 1) -> (1, 1) -> (1, 0) ->(2, 0) -> (2, 1)

![](https://cdn.luogu.com.cn/upload/image_hosting/a7qxcn67.png)  

对于第二个数据:

(0, 2) -> (1, 2) -> (1, 1) -> (2, 1) -> (2, 0) ->

(3, 0) -> (3, 1) -> (3, 2) -> (4, 1) -> (3, 1) ->

(3, 0) -> (2, 0) -> (2, 1) -> (1, 1) -> (1, 2) ->

(1, 3) -> (2, 3) -> (2, 4) -> (3, 4) -> (3, 3) ->

(4, 3) -> (4, 2) -> (5, 2)

![](https://cdn.luogu.com.cn/upload/image_hosting/8d0gue8n.png)

## 样例 #1

### 输入

```
2 1
0 0 2 1
bb
nwwnw
bn```

### 输出

```
6```

## 样例 #2

### 输入

```
5 4
0 2 5 2
nnbnn
nnnwwbwnnnn
nbbbn
nnwbwwbwwnn
bwwww
nnbwbbwwbnn
nwwwn
nnnnbwbbnnn
nnwnn```

### 输出

```
22```

# 题解

## 作者：施玮宸SECSA (赞：3)

第一次在做这道题时：\
whaaaat?什么题目？\
但是，这题真有那么难吗?????????\
经过一定思考后，发现该题其实就是一个BFS。此题并没有边权的一定限制，却有一个边的颜色（黑，白，也有可能没有颜色）\
那么这题是不是一个奇偶最短路（用广度优先搜索来求解）呢？？？？？？
经过分析，发现的确如此。\
需要记录走过的边的号码。\
复杂度：$O(ts)$~~~~~~~

前方贴出代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1000001,max_m=2000001;
const int max_e=5000001;
struct node{
	int t;
	int w;
	int n;
};//用于链表的结构体
node e[max_e];
bool bl[2][max_n];
int now[max_m],ret[max_m],h[max_m],m;
void a(int x,int y,int z){
	e[++m].w=z;
	e[m].t=y;
	e[m].n=h[x];
	h[x]=m;//链表增边
}
int x,y,xx,yy;
int s,t,u,v;
int le,ri;//左，右
int tmp,rem,res;
char c;//读入的字符
int main(){
	ri=tmp=2;
	cin>>t>>s>>x>>y>>xx>>yy;
	for(int i=1;i<=((s*2)|1);i++){
		c=getchar();//读入
		for(int j=1;j<=((i&1)?t:((t*2)|1));j++){
			c=getchar();//读入
			if('n'==c) continue;
			if((i&1)!=0){
				u=(t+1)*(i/2)+j;
				v=u+1;
			}
			else{
				u=(t+1)*(i/2)+(j/2)+(1&j);
				v=u-(1&j)-t;
			}
			a(v,u,!(c=='w'));
			a(u,v,!(c=='w'));
		}
	}
   	//上边是所有的输入&预处理~~~
	now[2]=now[1]=x+1+(t+1)*y;
	ret[1]=0;
	res=0;
	rem=xx+1+(t+1)*yy;
	ret[2]=le=1;
	bl[1][now[1]]=1;
	bl[0][now[1]]=1;
	while(ri>=le){
		if(rem==now[le]){
			break;
		}
		for(int i=h[now[le]];i;i=e[i].n){
			if(e[i].w!=ret[le]){
				v=e[i].t;
				if(bl[e[i].w][v]==0){
					now[++ri]=v;
					bl[e[i].w][v]=1;
					ret[ri]=e[i].w;
				}
			}
		}
		le++;
		if(tmp<le){
			res++;
			tmp=ri;
		}
	}
    	//????上面是整个bfs~
	cout<<res<<endl;//最后输出
	return 0;
}
```
感谢观看。

---

## 作者：ls623820778 (赞：1)

随机跳题跳到的题目，不是很难，就做了。

首先，题目应该不是很严谨，题目里面说的是“对于四边形的每条边都有一种Color,非黑即白”，但是通过观察样例，我们发现，其实除了黑边和白边，还有一种边是没有颜色不能走的，不过看样例就能明白，问题不大。

既然是找最短路径，很容易就会想到广搜。但是题目有一个限制，走过的边的颜色必须是黑白交替，所以我们必须对广搜进行一些修改。在广搜时，我们不仅要记录从起点到该点的距离，还要记录到这个点时的那条边的颜色是黑色还是白色，然后就能过了。

其他小细节自己考虑就行了，下面是代码。
```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
//除了bfs，应该没有什么重要的部分吧。 
const int V=501*501+10;
const int E=V*6+10;
int head[V],next[E][3],tot=1;//前向星 

char s[501*2+10];

int dis[V][2];

int w,h;
int S,T;

int zhuan(int,int);
void connect(int,int,int);
void print();
int ans();
void bfs();
int main()
{
	memset(head,0,sizeof(head));
	memset(next,0,sizeof(next));
	memset(s,0,sizeof(s));
	memset(dis,-1,sizeof(dis));
	
	int x1,x2,y1,y2;
	scanf("%d%d",&w,&h);
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	S=zhuan(x1,y1);//函数zhuan用于给每一个点编号，从1开始 
	T=zhuan(x2,y2);
	
	for(int i=0;i<=h;i++)//输入边，没有颜色的边不用管 
	{
		scanf("%s",s);
		for(int j=0;j<w;j++)
		{
			if(s[j]=='w')
				connect(zhuan(j,i),zhuan(j+1,i),1);
			else if(s[j]=='b')
				connect(zhuan(j,i),zhuan(j+1,i),0);
		}
		if(i==h) continue;
		scanf("%s",s);
		for(int j=0;j<=w;j++)
		{
			if(s[j*2]=='w')
				connect(zhuan(j,i),zhuan(j,i+1),1);
			else if(s[j*2]=='b')
				connect(zhuan(j,i),zhuan(j,i+1),0);
			if(!j) continue;
			if(s[j*2-1]=='w')
				connect(zhuan(j,i),zhuan(j-1,i+1),1);
			else if(s[j*2-1]=='b')
				connect(zhuan(j,i),zhuan(j-1,i+1),0);
		}
	}
	
	bfs(); 
	printf("%d\n",ans());
	//print(); 
	return 0;
}
void bfs()
{
	dis[S][0]=0;
	dis[S][1]=0;
	queue <int> q;
	q.push(S);
	q.push(-S);//用正数和负数来表示这个点是从黑边过来的还是白边过来的。 
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		int color;
		if(x>0)
			color=1;
		else
		{
			color=0;
			x=-x;
		}
		if(x==T) return;
		for(int p=head[x];p;p=next[p][0])
		{
			int v=next[p][1];
			if(next[p][2]==color) continue;
			if(dis[v][color^1]==-1||dis[v][color^1]>dis[x][color]+1)
			{
				dis[v][color^1]=dis[x][color]+1;
				if(color)
					q.push(-v);
				else
					q.push(v);
			}
		}
	}
}
int ans()
{
	if(dis[T][0]==-1) return dis[T][1];
	if(dis[T][1]==-1) return dis[T][0];
	return dis[T][0]<dis[T][1]?dis[T][0]:dis[T][1];
}
void print()//调试用代码，不用管 
{
	for(int i=0;i<=h;i++)
	{
		for(int j=0;j<=w;j++)
		{
			int u=zhuan(j,i);
			printf("u:%d\n",u);
			for(int p=head[u];p;p=next[p][0])
			{
				printf("    v:%2d  w:%s\n",next[p][1],next[p][2]?"white":"black");
			}
		}
	}
	for(int i=0;i<=h;i++)
	{
		for(int j=0;j<=w;j++)
		{
			int u=zhuan(j,i);
			printf("u:%2d dis[0]:%2d dis[1]:%2d\n",u,dis[u][0],dis[u][1]);
		}
	}
}
void connect(int u,int v,int w)
{
	next[++tot][0]=head[u],head[u]=tot,next[tot][1]=v,next[tot][2]=w;
	next[++tot][0]=head[v],head[v]=tot,next[tot][1]=u,next[tot][2]=w;
}
int zhuan(int x,int y)
{
	return x+1+y*(w+1);
}
```


---

## 作者：FJ_OIer (赞：0)

正解：BFS，主要难点在**建图**。

这个图完全可以用矩阵存储，~~但是我非常非常脑瘫的选择把坐标转换为连续的点（（？？？~~。好吧虽然也能做，注意到坐标从 $0$ 开始，我们先将所有坐标加 $1$。那么 $(x,y)$ 对应的点就是 $m(x-1)+y$（坐标从 $1$ 开始）。

接下来考虑边与点的关系。我们将平行四边形拉成一个长方形：

![](https://cdn.luogu.com.cn/upload/image_hosting/r8umcc5u.png)

那么在输入的时候就会有两种：一是输入横向边，二是输入纵向边和斜边，总共输入 $2n-1$ 条字符串。设当前边是第 $i$ 个字符串第 $j$ 位（还是强制从 $1$ 开始）。

1. 横向边：连接两个横向相邻的点。那么它左边的点就是 $\frac{i-1}{2}\times m+j$，它右边的点就是 $\frac{i-2}{2}\times m+j+1$。
2. 纵向边：连接两个纵向相邻的点。那么它上边的点就是 $m(\frac{i}{2}-1)+\frac{j+1}{2}$，它下边的点就是 $\frac{i}{2}\times m+\frac{j+1}{2}$
3. 斜边：连接两个右上-左下相邻的点。那么它右上的点就是 $m(\frac{i}{2}-1)+\frac{j+2}{2}$，它左下的点就是 $\frac{i}{2}\times m+\frac{j+2}{2}-1$

据此建图。~~证明略，画个图就行~~

接下来就可以~~愉快的~~ BFS 了。注意一下标记的问题：一个点最多只会经过两次，并且每次经过时边的颜色不同（比如第一次从白边进第二次从黑边进）。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Edge{
	int v,c;//编号、颜色
};
struct BFS{
	int v,c,d;
};
int n,m,sx,sy,ex,ey;
int vis[255001];//开大点，因为坐标加1
string s;
vector<Edge> e[255001];
queue<BFS> q;
int color(char c){//返回每个字母对应的颜色（1 黑 2 白）
	if (c=='b'){
		return 1;
	}
	return 2;
}
void bfs(){
	q.push({(sx-1)*m+sy,-1,0});
	vis[(sx-1)*m+sy]=-1;
  	//起点只能进一次且没有颜色
  	//标记：1 从黑边进 2 从白边进 0 无标记 -1 永久封杀
	while (!q.empty()){
		auto u=q.front();
		q.pop();
		for (auto i:e[u.v]){
			int v=i.v;
			if (vis[v]==-1||vis[v]==i.c||u.c!=-1&&i.c+u.c!=3){
				//永久封杀 或 从同色边进 或 不符合规则
				continue;
			}
			if (v==(ex-1)*m+ey){
				cout<<u.d+1;
				exit(0);
			}
			q.push({v,i.c,u.d+1});
			vis[v]=(!vis[v]?i.c:-1);//如果两次路过就封杀，否则正常标记
		}
	}
	cout<<0;
}
int main(){
	cin>>n>>m>>sx>>sy>>ex>>ey;
	n++,m++,sx++,ex++,sy++,ey++;//各坐标加1
	swap(n,m);
	swap(sx,sy);
	swap(ex,ey);
  	//交换坐标
	for (int i=1;i<=2*n-1;i++){
		cin>>s;
		s=' '+s;//从1开始
		for (int j=1;j<s.size();j++){
			if (s[j]=='n'){//忽略无色边（这边建议修改题面）
				continue;
			}
			if (i&1){//恶心的让人发指的建图。。。
				e[(i-1)/2*m+j].push_back({(i-1)/2*m+j+1,color(s[j])});
				e[(i-1)/2*m+j+1].push_back({(i-1)/2*m+j,color(s[j])});
			}else if (j&1){
				e[(i/2-1)*m+(j+1)/2].push_back({i/2*m+(j+1)/2,color(s[j])});
				e[i/2*m+(j+1)/2].push_back({(i/2-1)*m+(j+1)/2,color(s[j])});
			}else{
				e[(i/2-1)*m+(j+2)/2].push_back({i/2*m+(j+2)/2-1,color(s[j])});
				e[i/2*m+(j+2)/2-1].push_back({(i/2-1)*m+(j+2)/2,color(s[j])});
			}
		}
	}
	bfs();
	return 0;
}
```

---

## 作者：WaterSky (赞：0)

# [P4651 [BalticOI 2005] Maze](https://www.luogu.com.cn/problem/P4651)

呃，怎么说呢，这题我单单看题，根本不知道讲的是什么，但是如果联系图片就比较好理解了。

![](https://cdn.luogu.com.cn/upload/image_hosting/a7qxcn67.png)

联系题目，可以知道，题目给出一个由若干个三角形组成的平行四边形，以及入口与出口，求**一条最短的黑白交替的由入口到出口的路径的长度**（绕口），而路径沿着边，一个小三角形的边长度为 $1$。

题意有一点不明白，就是路径不一定非黑即白，还有一种没有颜色的，因为要求的是黑白交替的，所以这种边没有用。

再分析题目的本质，易得题目其实就是需要广搜解决奇偶最短路，然后这题就做完了。

最后就是需要解释一些代码里的细节：
```
#include<bits/stdc++.h>
using namespace std;
struct wbx{
	int t,w,n;
}e[5000001];//存图 
bool bl[2][1000001];
int now[2000001],ret[2000001],h[2000001],m;
int x,y,xx,yy,s,t,u,v,l,r;
int tmp,rem,res;
char c;
int main(){
	r=tmp=2;
	
	//第一部分：输入与预处理。
	scanf("%d%d%d%d%d%d",&t,&s,&x,&y,&xx,&yy);
	for(int i=1;i<=((s*2)|1);i++)
	{
		for(int j=1;j<= ((i&1)?t:((t*2)|1)) ;j++)//一个三目运算符，快速判断边的类型（横或斜） 
		{
			cin>>c;
			if('n'==c) continue;
			if(i&1) u=(t+1)*(i/2)+j,v=u+1;
			else u=(t+1)*(i/2)+(j/2)+(1&j),v=u-(1&j)-t;
			e[++m].w=!(c=='w'),e[m].t=u,e[m].n=h[v],h[v]=m; //增边操作。 
			e[++m].w=!(c=='w'),e[m].t=v,e[m].n=h[u],h[u]=m; //增边操作。 
		}
	}
	
	//第二部分：BFS。 
	now[2]=now[1]=x+1+(t+1)*y;
	ret[1]=0,res=0,rem=xx+1+(t+1)*yy,ret[2]=l=1;
	bl[1][now[1]]=1,bl[0][now[1]]=1;
	while(r>=l)
	{
		if(rem==now[l]) break;
		for(int i=h[now[l]];i;i=e[i].n)
			if(e[i].w!=ret[l])
			{
				v=e[i].t;
				if(bl[e[i].w][v]==0) now[++r]=v,bl[e[i].w][v]=1,ret[r]=e[i].w;
			}
		l++;
		if(tmp<l) res++,tmp=r;
	}
	
	
	printf("%d",res);
	return 0;
}
```
怎么说，难度似乎不是很大，稍微思考就能够得出答案，所以解释的也就比较粗糙，还请自行思考！

感谢管理员审核！

---

