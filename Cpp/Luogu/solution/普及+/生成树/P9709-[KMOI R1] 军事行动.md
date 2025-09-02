# [KMOI R1] 军事行动

## 题目背景

$$\blue{他们来了。}$$

$$\purple{集结军队，干掉他们，一个不留。}$$

$$\blue{是！}$$

## 题目描述

喵星边境局势愈发紧张，导致发生边境冲突。喵星军队总司令小袁立即对 $Y$ 星采取军事行动。

整个宇宙可以看作一个平面直角坐标系，城市 $1,2,\dots,n$ 的坐标分别为 $(x_1,y_1),(x_2,y_2),\dots(x_n,y_n)$。

现在小袁率领的**若干支**舰队（可以理解为小袁的军事力量是无限的）驻扎在边境要塞，城市 $1$ 处。他的舰队会进行以下移动：

- 如果舰队的坐标为 $(x,y)$，那么一天之后它可以移动到 $(x-1,y+2)$ 或 $(x+1,y+2)$ 或 $(x+2,y+1)$ 或 $(x-2,y+1)$ 或 $(x-1,y-2)$ 或 $(x+1,y-2)$ 或 $(x+2,y-1)$ 或 $(x-2,y-1)$ 处。

其中环绕在外的还有一条小行星带，当舰队的坐标  $(x,y)$ 且 $x\le 0$ 或 $y\le 0$ 或 $m < x$ 或 $m < y$ 时，舰队就会撞到小行星带。这是小袁所不想看到的。

现在小袁要攻打城市 $2,3,\dots,n$，每一次他都会从一个**已经占领**的城市（城市 $1$ 也算），派出舰队前往城市 $i$ 并攻打它，舰队**到达之后的第二天**城市 $i$ 就被攻占了。

特别的，小袁在一个舰队**前往攻打或攻打一个城市**的时候不会派出另外一支舰队，在**攻占一座城市后当天**可以立即派出另外一支舰队。

小袁想问，最少要花多少时间才能攻占所有的城市。

**攻打顺序可以不按照 $2,3\dots n$ 的顺序。**

## 说明/提示

## 样例一解释：

舰队在第一天来到了 $(3,2)$ 的位置，第二天到达了城市 $2$ 的位置，第三天占领了城市 $2$。总共花了 $3$ 天。

## 样例二解释：

舰队在第一天到达了城市 $2$ 的位置，第二天占领了城市 $2$。第三天到达了城市 $3$ 的位置，第四天占领了城市 $3$。总共花了 $4$ 天。

## 数据范围

**本题采用 Subtask 捆绑测试。**

|子任务编号|  测试点编号| $n$ | $m$ |特殊性质|分值|
|:-----:| :----------: | :----------: | :----------: | :----------: |:---:|
|$1$| $1\sim2$ | $1\le n\le 7$ |$4\le m\le 7$|无|$10$|
|$2$| $3\sim7$ | $1\le n\le 200$ |$4\le m\le 70$|无|$25$|
|$3$| $8\sim9$ | $1\le n\le 150$ |$4\le m\le 150$|有|$15$|
|$4$| $10\sim20$ | $1\le n\le 2000$ |$4\le m\le 150$|无|$50$|

特殊性质：对于每一个 $1\le i\le n-1$，都有 $x_i = x_{i+1}$。

**数据严格保证不会有不同的城市拥有相同的坐标。**

## 样例 #1

### 输入

```
2 20
1 1
1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3 150
1 2
2 4
4 3```

### 输出

```
4```

## 样例 #3

### 输入

```
10 10
1 4
2 3
2 6
3 6
10 3
1 5
4 2
5 3
2 8
9 2```

### 输出

```
23```

## 样例 #4

### 输入

```
查看附件的 example4.in```

### 输出

```
查看附件的 example4.out```

# 题解

## 作者：Fire_flame (赞：7)

# $\mathtt{Solution}$

其实题目描述是来迷惑你的（

因为每一次可以从任意已攻占的城市出发，所以相当于是求最小生成树。

我们可以用 `bfs` 马走日求出每两个点之间的边权。然后再跑一遍最小生成树即可。

但是 `bfs` 的时候，每一个点入队的时候就要标记为走过，如果等到遍历到这个点的时候再标记就晚了。

时间复杂度 $O(nm^2+m\log n)$（kruskal），$O(nm^2+n\log n)$（prim）。

标程一（`bfs` + `kruskal`）：

```cpp
#include<bits/stdc++.h>//By Fire_flame
using namespace std;
const int MAXN = 3e3 + 5, MR = 9e6 + 5, MN = 2e2 + 5;
int n, m, cnt, ans, mp[MN][MN], f[MN][MN], fa[MAXN];
struct edge{
    int x, y, len;
    bool operator < (const edge &ll)const{
        return len < ll.len;
    }
}e[MR];
struct node{
    int x, y;
    bool operator < (const node &rr)const{
        if(x != rr.x)return x < rr.x;
        return y < rr.y;
    }
}a[MAXN];
struct step{
    int x, y, len;
};
int dx[] = {-1, 1, 2, -2, -1, 1, 2, -2};
int dy[] = {2, 2, 1, 1, -2, -2, -1, -1};
void bfs(int sx, int sy){
    queue<step>q;
    q.push({sx, sy, 0});
    memset(f, 0, sizeof(f));
    f[sx][sy] = 1;
    while(!q.empty()){
        int tx = q.front().x, ty = q.front().y, tl = q.front().len;
        q.pop();
        for(int i = 0;i < 8;i ++){
            int px = tx + dx[i], py = ty + dy[i];
            if(f[px][py] || px <= 0 || py <= 0 || px > m || py > m)continue;
            if(mp[px][py])e[++ cnt] = {mp[sx][sy], mp[px][py], tl + 1};
            f[px][py] = 1;
            q.push({px, py, tl + 1});
        }
//        printf("%d %d %d\n", tx, ty, tl);
    }
}
int find(int u){
    if(fa[u] == u)return u;
    return fa[u] = find(fa[u]);
}
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= n;i ++)scanf("%d%d", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1);
    for(int i = 1;i <= n;i ++)mp[a[i].x][a[i].y] = fa[i] = i;
    for(int i = 1;i <= n;i ++)bfs(a[i].x, a[i].y);
    sort(e + 1, e + cnt + 1);
    for(int i = 1;i <= cnt;i ++){
        int tx = e[i].x, ty = e[i].y, tl = e[i].len;
        if(find(tx) != find(ty)){
            fa[find(tx)] = find(ty);
            ans += tl;
        }
    }
    printf("%d", ans + n - 1);
    return 0;
}
```

标程二（`bfs` + `prim`）：

```cpp
#include <bits/stdc++.h>//代码提供者：康立扬
using namespace std;
int n;
int x,y,diss[310][310],u,v,vis[310][310],dis[4010],ans,N,a[310][310];
pair<int,int> q1[202500];int hd,tl;
struct node{
	int u,dis;
	bool operator<(const node &a) const{
		return dis>a.dis;
	}
};

int fx[8]={-1,1,2,-2,-1,1,2,-2};
int fy[8]={2,2,1,1,-2,-2,-1,-1};
struct point{
	int x,y;
}c[4010];
void bfs(int x,int y){
	hd=0,tl=0;
	q1[tl++]={x,y};
	for(int i=1;i<=N;i++) for(int j=1;j<=N;j++) vis[i][j]=0;
	diss[x][y]=1;
    vis[x][y]=1;
    int cnt=1;
	while(hd<tl){
		pair<int,int>u=q1[hd++];
        //cout<<"~~"<<u.first<<" "<<u.second<<" "<<diss[u.first][u.second]<<"\n";
		if(cnt==n) break;
		for(int i=0;i<8;i++){
			pair<int,int>v={u.first+fx[i],u.second+fy[i]};
            //cout<<"to"<<v.first<<" "<<v.second<<"\n";
			if(vis[v.first][v.second]||v.first<1||v.second<1||v.first>N||v.second>N) continue;
			diss[v.first][v.second]=diss[u.first][u.second]+1;
		    vis[v.first][v.second]=1;
		    if(a[v.first][v.second]) cnt++;
			q1[tl++]=v;
		}
	} 
}
priority_queue<node>q;
void prim(){
    dis[0]=0;
	q.push({0,0});
	while(!q.empty()){
		int u=q.top().u,d=q.top().dis;
		q.pop();
		if(d!=dis[u]) continue;
		ans+=d;
		//cout<<u<<" "<<d<<"\n";
		dis[u]=0;
		bfs(c[u].x,c[u].y);
		for(int i=0;i<n;i++){
			if(diss[c[i].x][c[i].y]<dis[i]){
				dis[i]=diss[c[i].x][c[i].y];
				q.push({i,dis[i]});
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	memset(dis,0x3f,sizeof dis);
	scanf("%d",&N);
	for(int i=0;i<n;i++){
		scanf("%d%d",&u,&v);
		c[i].x=u,c[i].y=v;
		a[u][v]=1;
	}
	prim();
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：_Flame_ (赞：3)

### $\text{solution}$

观察题目要求的东西，每次从一个点去往另外一个点，要求连接所有点所要的时间的最小值，你会发现这个东西很像一个最小生成树。

于是想到将点两两之间连边，求出整个图的最小生成树，边数有 $n^2$ 条，可以过。

考虑怎么 $O(1)$ 求出两点之间按照题目给出的方法要走多少步，即连接两点的边的边权，这里推一下数学式子，分类讨论一下。

将两点中间的某一点 $a$ 当作坐标轴原点，另外一点 $b$ 的横坐标为 $x$ 纵坐标为 $y$，有以下几种情况。

- $x$ 和 $y$ 一个为 $1$，一个为 $0$ 时，此时从 $a$ 到 $b$ 要走 $3$ 步。

- $x$ 和 $y$ 一个为 $2$，一个为 $2$ 时，此时从 $a$ 到 $b$ 要走 $4$ 步。

- 其他情况下令 $y$ 大于 $x$，（反之交换即可），若 $x\leq y-x$，步数为 $y-x-2\times \lfloor \frac {y-2\times x}{3} \rfloor$ 否则则为 $y-x-2\times \lfloor \frac {y-2\times x}{4} \rfloor$。

然后直接建图，跑一次 Kruskal 或者 Prim，求出最小生成树大小，最后由于到每一个城市后第二天才会占领，在最小生成树的大小上加上 $n-1$ 几位答案。

### $\text{code}$

```cpp

int n,m;

struct node{
	int x,y;
}a[maxn];

int head[maxn],tot;
struct edge{
	int to,nxt,w;
}e[maxn<<1];

void add(int u,int v,int w){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	e[tot].w=w;
	head[u]=tot;
}

bool vis[maxn];
int dis[maxn],ans;

struct Dis{
	int dis,id;
	bool operator <(const Dis&tmp)const{return dis>tmp.dis;}
};
priority_queue<Dis> q;

void prim(){
	int cnt=1;
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	q.push({0,1});
	while(cnt<=n){
		if(!q.empty()){
			int u=q.top().id;
			q.pop();
			if(!vis[u]){
				vis[u]=1;
				ans+=dis[u];
				++cnt;
				for(int i=head[u];i;i=e[i].nxt){
					int v=e[i].to;
					if(dis[v]>e[i].w){
						dis[v]=e[i].w;
					}
					q.push({dis[v],v});
				}
			}
		}
		
	}
	write(ans+n-1);
	puts("");
}//prim求最小生成树

int get(int x,int y){
	x=abs(x),y=abs(y);
	if(x>y){
		swap(x,y);
	}
	if(y==1&&x==0){
		return 3;
	}
	if(y==2&&x==2){
		return 4;
	}
	int res=y-x;
	if(x>res){
		return res-2*floor(1.0*(res-x)/3.0);
	}
	else{
		return res-2*floor(1.0*(res-x)/4.0);
	}
}//计算两点间距离

void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j){
				continue ;
			}
			else{
				int xx=a[i].x-a[j].x,yy=a[i].y-a[j].y;
				add(i,j,get(xx,yy));
				add(j,i,get(xx,yy));
			}
		}
	}
	prim();
	return ;
}


```

---

## 作者：DerrickLo (赞：2)

显然攻占城市的最小时间可以认为是一棵最小生成树。

然后我们对于每个城市进行 `bfs`，如果找到了一个城市那么就将这两个城市连边，边权为找到的时间。最后求出这个图的最小生成树边权之和即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x[2005],y[2005],fa[2005],cnt,dx[]={-1,1,2,-2,-1,1,2,-2},dy[]={2,2,1,1,-2,-2,-1,-1},vis[205][205],hs[40005],hv[2005][2005],cntt,ans;
struct edge{
	int u,v,w;
	friend bool operator<(const edge&a,const edge&b){
		return a.w<b.w;
	}
}ee[8000005];
int find(int x){
	return(fa[x]==x?x:fa[x]=find(fa[x]));
}
struct lll{int x,y,tm;};
void bfs(int sx,int sy,int num){
	queue<lll> q;
	q.push({sx,sy,1});
	vis[sx][sy]=1;
	while(!q.empty()){
		auto ft=q.front();q.pop();
		for(int i=0;i<8;i++){
			int tx=ft.x+dx[i],ty=ft.y+dy[i];
			if(tx>=1&&tx<=m&&ty>=1&&ty<=m&&!vis[tx][ty]){
				vis[tx][ty]=1;
				q.push({tx,ty,ft.tm+1});
				int hss=tx*200+ty;
				if(hs[hss]){
					if(!hv[num][hs[hss]]){
						hv[num][hs[hss]]=1;
						ee[++cnt]={num,hs[hss],ft.tm+1};
					}
				}
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i],hs[x[i]*200+y[i]]=i,fa[i]=i;
	for(int i=1;i<=n;i++)memset(vis,0,sizeof vis),bfs(x[i],y[i],i);
	sort(ee+1,ee+cnt+1);
	for(int i=1;i<=cnt;i++){
		if(cntt==n-1)break;
		int fx=find(ee[i].u),fy=find(ee[i].v);
		if(fx==fy)continue;
		cntt++;
		fa[fx]=fy;
		ans+=ee[i].w;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：1)

### 题目分析

不知道最小生成树的可以走了。

可以把题面转化一下。

对于所有点，要用 $n-1$ 条边去让 $n$ 个点联通。

求最小代价。

长得跟最小生成树差不多。

只不过处理边上不太一样。

可以用 bfs 像中国象棋里面马一样跑一遍，建边，然后跑最小生成树。

所以评绿是不是高了（汗

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[8]={-1,-2,-2,-1,1,2,2,1};
const int dy[8]={2,1,-1,-2,2,1,-1,-2};
struct node
{
	int x,y;
	int z;
}a[9000010];
struct qnum
{
	int x,y,step;
};
queue<qnum> q;
int vis[151][151];
int n,m;
int cnt;
int mp[2010][2010];
int fa[2010];
int find(int x)
{
	if(fa[x]!=x)
	{
		return fa[x]=find(fa[x]);
	}
	return x;
}
bool cmp(node a,node b)
{
	return a.z<b.z;
}
int wtf()
{
	int dis=0,num=0;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt&&num<n;i++)
	{
		int fx=find(a[i].x);
		int fy=find(a[i].y);
		if(fx!=fy)
		{
			fa[fx]=fy;
			dis+=a[i].z;
			num++;	
		}
	}
	return dis;
}
void bfs(int sx,int sy)
{
	memset(vis,false,sizeof(vis));
// 	for(int i=1;i<=m;i++)
// 	    for(int j=1;j<=m;j++)
	        
	vis[sx][sy]=true;
	qnum s={sx,sy,1};
	q.push(s);
    while(!q.empty())
    {
        qnum u=q.front();
        int ux=u.x,uy=u.y,ustep=u.step;
		q.pop();
        for(int i=0;i<8;i++)
        {
            int vx=ux+dx[i],vy=uy+dy[i];
            if(vx<1||vx>m||vy<1||vy>m||vis[vx][vy])
				continue;
            vis[vx][vy]=true;
            if(mp[vx][vy]!=0)
            	a[++cnt]={mp[sx][sy],mp[vx][vy],ustep};
            qnum v={vx,vy,ustep+1};
			q.push(v);
        }
    }
}
int x[2010],y[2010];
inline void write(int x)
{
    if(x<0)
	{
    	putchar('-');
		x=-x;
	}
    if(x>9)
    {
    	write(x/10);
	}
    putchar(x%10+'0');
}
inline int read() 
{
     bool f=false; 
	 int x=0;
     char ch=getchar();
     while(ch<'0'||ch>'9') 
	 {
         if(ch=='-') 
		 {
		 	f=true;
		 }
         ch=getchar();
     }
     while(ch>='0'&&ch<='9') 
	 {
         x=(x<<1)+(x<<3)+ch-'0';
         ch=getchar();
     }
     return f?-x:x;
 }
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
    	x[i]=read(),y[i]=read();
    	mp[x[i]][y[i]]=i;
	}
	for(int i=1;i<=n;i++)
		bfs(x[i],y[i]);
	printf("%d",wtf()+n-1);
    return 0;
}
```


---

## 作者：Night_sea_64 (赞：1)

前置知识：bfs，最小生成树（都非常简单）。

**简要题意：** 在 $m\times m$ 的棋盘中，有 $n$ 个关键格子。每两个格子之间的距离定义为按国际象棋中“马”的走法的最小步数 $+1$。求这 $n$ 个点的最小生成树。

这题没什么好想的，就是直接对每个城市跑一遍 bfs，求出它到其他城市的最短距离，时间复杂度 $O(nm^2)$。

然后求一遍最小生成树。因为每两个城市之间都有连边，所以该图是个**完全图**，用 Prim 算法更快，时间复杂度 $O(n^2)$。最后答案加上 $n-1$ 即可。

```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
int n,m,xx[2010],yy[2010];
int g[2010][2010],dis[160][160];
bool flag[160][160];
int dx[]={0,-2,-2,-1,-1,1,1,2,2};
int dy[]={0,-1,1,-2,2,-2,2,-1,1};
struct node{int x,y,step;};
void bfs(int s)
{
    queue<node>q;
    q.push({xx[s],yy[s],0});
    memset(dis,999999,sizeof(dis));
    memset(flag,0,sizeof(flag));
    dis[xx[s]][yy[s]]=0,flag[xx[s]][yy[s]]=1;
    while(!q.empty())
    {
        int x=q.front().x,y=q.front().y,step=q.front().step;
        q.pop();
        for(int i=1;i<=8;i++)
        {
            int nx=x+dx[i],ny=y+dy[i];
            if(nx<1||nx>m||ny<1||ny>m)continue;
            if(flag[nx][ny])continue;
            flag[nx][ny]=1,dis[nx][ny]=step+1;
            q.push({nx,ny,step+1});
        }
    }
}
int d[2010],sum;
bool f[2010];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>xx[i]>>yy[i];
    for(int i=1;i<=n;i++)
    {
        bfs(i);
        for(int j=1;j<=n;j++)
            g[i][j]=dis[xx[j]][yy[j]];
    }
    memset(d,999999,sizeof(d));
    d[1]=0;
    for(int i=1;i<=n;i++)
    {
        int minn=1e9,minid;
        for(int j=1;j<=n;j++)
            if(d[j]<minn&&!f[j])minn=d[j],minid=j;
        f[minid]=1,sum+=d[minid];
        for(int j=1;j<=n;j++)d[j]=min(d[j],g[minid][j]);
    }
    cout<<sum+n-1<<endl;
    return 0;
}
```

---

## 作者：sbno333 (赞：1)

这道题其实像最小生成树，但比赛时由于最小生成树担心爆时间，因此写了纯搜索。

结果搜索比最小生成树快了 $10$ 倍，因此有了下面的题解。

广度优先搜索思路可以是这样的：

从第一个城市开始搜索，将每一个搜到的坐标记录步数，如果搜到城市，则以搜到的城市开始向外搜索，步数为从搜到的城市出发的步数，如果搜到了搜过的城市，则减掉这个分支。

如果搜到了搜过的地点，仿照`SPFA`，进行一次松弛操作，如果比原来的步数少，则以这个坐标继续搜索，否则剪枝。

按照广度优先搜索，每一次在队列中取步数最少的坐标向外搜索，但由于有新的城市，不能保证第一个就是步数最少，因此用一个优先队列维护。

为了计算方便，我们将攻占城市的时间放在最后计算，即不计算攻占城市的时间加 $n-1$。

可以证明，不会花费过多时间。

```cpp
#include<bits/stdc++.h>
using namespace std;
int mm[19][2]={0,0,1,2,-1,2,-1,-2,1,-2,2,1,-2,1,-2,-1,2,-1};//记录可能的行走方式
int f[159][159];//f[i][j]=0表示是空地，f[i][j]=1表示是未攻占的城市，f[i][j]=2表示已攻占
struct node{
	int x,y,no;
	node m(int xx,int yy,int o){
		node zz;
		zz.x=xx;
		zz.y=yy;
		zz.no=o;
		return zz;
	}
	bool operator<(const node dd)const{//方便priority_queue
		return no<dd.no;
	}
	bool operator>(const node dd)const{
		return no>dd.no;
	}
}zzz;
priority_queue<node,vector<node>,greater<node> > q;
int mp1[209][209];
node sd[2009];
int main(){
    std::ios::sync_with_stdio(0);
	for(int i=0;i<159;i++){
		for(int j=0;j<159;j++){
			f[i][j]=1e9;
		}
	}
	int n,m;
	cin>>n>>m;
	int inn;
	inn=0;
	int xx,yy;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			mp1[i][j]=0;
		}
	}
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		sd[i].x=x;
		sd[i].y=y;
		if(i==1){
			xx=x,yy=y;
		}
		mp1[x][y]=1;
	}
	
	f[xx][yy]=0;//攻占城市1的时间为0
	q.push(zzz.m(xx,yy,0));
	while(q.size()){
		int x,y,o;
		x=q.top().x;
		y=q.top().y;
		o=q.top().no;
		q.pop();
		
		if(mp1[x][y]==2){
			continue;
		}else if(mp1[x][y]){
			mp1[x][y]=2;//攻占
			for(int i=1;i<=8;i++){
				int xx,yy,oo;
				oo=1;
				xx=x+mm[i][0];
				yy=y+mm[i][1];
				if(xx<=m&&yy<=m&&1<=xx&&1<=yy){//如果合法
					if(oo<f[xx][yy]&&mp1[xx][yy]!=2){//可更新
						f[xx][yy]=oo;
						q.push(zzz.m(xx,yy,oo));
					}
				}
			}
			inn++;//攻占了一个城市，记录一下
			if(inn==n){//去除多余操作，以防止TLE
				break;
			}
		}else{
			for(int i=1;i<=8;i++){
				int xx,yy,oo;
				oo=o+1;
				xx=x+mm[i][0];
				yy=y+mm[i][1];
				if(xx<=m&&yy<=m&&1<=xx&&1<=yy){
					if(oo<f[xx][yy]&&mp1[xx][yy]!=2){
						f[xx][yy]=oo;
						q.push(zzz.m(xx,yy,oo));
					}
				}
			}
		}
		
	}
	int ans;
	ans=0;
	for(int i=1;i<=n;i++){
		ans+=f[sd[i].x][sd[i].y];//计算攻占所有城市所需要的时间
	}
	cout<<ans+n-1;//+n-1表示攻占时间
	return 0;
} 
```
建议时限改为 1s ~~，学国际象棋的都知道，小袁的舰队是马~~。

---

## 作者：qzmoot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9709)
# 题目大意
每次可以攻占一个城市，求攻占所有城市的最小时间。你要攻占城市，那么必定要能够全是连通的，又要求最小。我们只能选择边数最少的树为我们的攻占轨迹。
##	思路
**必会芝士：bfs，最小生成树**。

如果不会最小生成树，请直接出门右转，[P3366[模版]最小生成树](https://www.luogu.com.cn/problem/P3366)。

但是，你会发现，我们只有点，没有边权，怎么进行最小生成树算法呢？

我们只需要用 bfs 处理出所有边的边权，存进结构体，再排序，最后进行最小生成树代码即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e3 + 5; // 最大点数
const int MR = 9e6 + 5; // 最大边数
const int MN = 2e2 + 5; // 最大二维矩阵大小

int num_points, matrix_size, edge_cnt, ans; // 点数、矩阵大小、边数、答案
int matrix[MN][MN]; // 二维矩阵
int visited[MN][MN]; // 标记数组
int fa[MAXN]; // 并查集数组

struct Edge // 边的结构体
{
	int x, y, len; // 点x、点y、长度
	bool operator< (const Edge &ll) const // 重载小于号
	{
		return len < ll.len;
	}
} edges[MR];

struct Point // 点的结构体
{
	int x, y; // 横坐标、纵坐标
	bool operator< (const Point &rr) const // 重载小于号
	{
		if (x != rr.x) return x < rr.x;
		return y < rr.y;
	}
};

struct Step // 步骤的结构体
{
	int x, y, len; // 横坐标、纵坐标、步长
};

int dx[] = {-1, 1, 2, -2, -1, 1, 2, -2}; // x方向移动的增量
int dy[] = {2, 2, 1, 1, -2, -2, -1, -1}; // y方向移动的增量

void bfs(int sx, int sy) // 广度优先搜索
{
	queue<Step> q;
	q.push({sx, sy, 0});
	memset(visited, 0, sizeof(visited));
	visited[sx][sy] = 1;

	while (!q.empty())
	{
		int tx = q.front().x, ty = q.front().y, tl = q.front().len;
		q.pop();

		for (int i = 0; i < 8; i++)
		{
			int px = tx + dx[i], py = ty + dy[i];

			if (visited[px][py] || px <= 0 || py <= 0 || px > matrix_size || py > matrix_size) // 判断是否越界或已访问
				continue;

			if (matrix[px][py]) // 判断是否是有效点
				edges[++edge_cnt] = {matrix[sx][sy], matrix[px][py], tl + 1};

			visited[px][py] = 1; // 标记为已访问
			q.push({px, py, tl + 1});
		}
	}
}

int find(int u) // 查找根节点
{
	if (fa[u] == u) return u;
	return fa[u] = find(fa[u]);
}

int main()
{
	scanf("%d%d", &num_points, &matrix_size); // 输入点数和矩阵大小

	Point points[MAXN]; // 定义点的结构体数组
	for (int i = 1; i <= num_points; i++)
		scanf("%d%d", &points[i].x, &points[i].y); // 输入每个点的坐标

	sort(points + 1, points + num_points + 1); // 按照坐标排序

	for (int i = 1; i <= num_points; i++)
		matrix[points[i].x][points[i].y] = fa[i] = i; // 初始化二维矩阵和并查集

	for (int i = 1; i <= num_points; i++)
		bfs(points[i].x, points[i].y); // 进行广度优先搜索

	sort(edges + 1, edges + edge_cnt + 1); // 边排序

	for (int i = 1; i <= edge_cnt; i++)
	{
		int tx = edges[i].x, ty = edges[i].y, tl = edges[i].len;

		if (find(tx) != find(ty)) // 判断是否连通
		{
			fa[find(tx)] = find(ty); // 连接两个点
			ans += tl; // 累加答案
		}
	}
	while(1)
		malloc(1000000);//防抄袭 
	printf("%d", ans + num_points - 1); // 输出答案

	return 0;
}
```

---

## 作者：ryf_loser (赞：0)

正解：搜索+最小生成树。

~~如果不了解题目大意的，请回~~。

此题一眼看到坐标，第一感觉搜索。可是再往下看，很明显，题目还让我们求最小生成树，因为小袁需要攻打 $n-1$ 个城市，且要求耗费时间最短。所以，只选 $n-1$ 条边，且使整个图连通所要耗费的最小代价是多少。由此得出是需要求最小生成树的。

而我们该如何计算每两点之间的边权值呢？考虑到此题两点之间会有很多边权值，而我们只需要知道最短的即可，那么很显然用 bfs。因为 bfs 是搜索每一层每一层地搜，也就是说，深度（步数/两点之间权值）在逐层增加。所以当我们搜索到一个从未被搜索到的点，那么他所在的层的深度也就是两点之间权值权值的最小值。

整理一下此题思路，大体上就是，先用 bfs。求 $n$ 个点两两的最短路径，然后用最小生成树求解即可。

注意到每攻打一个城市也需要一个时间，最后答案要加上 $n-1$。我因为这个错，~~调了半个小时~~。

AC CODE

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
inline int in(){
	int x=0,f=1;char c;
	c=getchar();
	while (c<'0'||c>'9'){
		if (c=='-')f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,m,x[2001],y[2001],tot,ans,sx[]={-1,1,2,-2,-1,1,2,-2},sy[]={2,2,1,1,-2,-2,-1,-1},cnt,f[2001],mp[151][151];//sx,sy是方向数组
struct node{int x,y,v;}a[4000001];
struct node1{int x,y,step;};
queue<node1>q;
bool cmp(node a,node b){return a.v<b.v;}//排序
bool vis[151][151];
inline int find(int k){//并查集维护
	if (k==f[k])return k;
	return f[k]=find(f[k]);
}
inline void bfs(int tx,int ty){//bfs
	memset(vis,0,sizeof vis);vis[tx][ty]=1;
	q.push({tx,ty,1});
	while (!q.empty()){
		node1 tmp=q.front();q.pop();
		int x=tmp.x,y=tmp.y,step=tmp.step;
		for (int i=0;i<8;i++){
			int xx=sx[i]+x,yy=sy[i]+y;
			if (xx<1||xx>m||yy<1||yy>m||vis[xx][yy])continue;//不能越界或走到相同的点上
			if (mp[xx][yy])a[++cnt]={mp[tx][ty],mp[xx][yy],step};//如果这个点是一个城市，记录
			vis[xx][yy]=1;//标记走过
			q.push({xx,yy,step+1});
		}
	}
}
int main(){
	n=in(),m=in();
	for (int i=1;i<=n;i++){
		x[i]=in(),y[i]=in();
		mp[x[i]][y[i]]=i;//标记点的编号
		f[i]=i;//并查集初始化
	}
	for (int i=1;i<=n;i++)bfs(x[i],y[i]);
	sort(a+1,a+1+cnt,cmp);
	for (int i=1;i<=cnt&&tot<n;i++){//kruskal求解最小生成树
		int x=a[i].x,y=a[i].y;
		int xx=find(x),yy=find(y);
		if (xx!=yy){
			f[xx]=yy;
			tot++;
			ans+=a[i].v;
		}
	}
	printf ("%d",ans+n-1);//注意+n-1
	return 0;
}
```


---

## 作者：TruchyR (赞：0)

## Part 1 思路
我们可以进行以下操作 $n$ 次：  
1. 寻找**距离已攻占城市距离最小的未攻占城市**（首次为城市 $1$）并攻占，累加答案。  
2. 从找到的城市开始跑一遍 `bfs`，更新到其他城市的最小距离。  
（上面说的的距离指的是马走日的）

其实以上过程等价于 Prim 求最小生成树，只不过边权是现求的。  
不需要优化最小生成树的过程也可以通过本题，时间复杂度为 $O(n^2+nm^2)$。  
## Part 2 代码
```
#include<bits/stdc++.h>
#define GP pair<int,int>
#define MP make_pair
using namespace std;
int n,m,res,x[2005],y[2005],c[2005],f[155][155];
int fx[8][2]={{2,1},{-2,1},{2,-1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
queue<GP> q;
signed main(){
	cin>>n>>m;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	f[x[1]][y[1]]=0;
	for(int i=1;i<=n;i++){
		int mn=1145,mnid=0;//选择距离最小的城市
		for(int j=1;j<=n;j++){
			if(c[j]) continue;
			if(f[x[j]][y[j]]<mn){
				mn=f[x[j]][y[j]];
				mnid=j;
			}
		}
		int j=mnid;//bfs更新到其他城市的距离
		res+=mn;c[j]=1;f[x[j]][y[j]]=0;
		q.push(MP(x[j],y[j]));
		while(!q.empty()){
			GP top=q.front();q.pop();
			int px=top.first,py=top.second;
			for(auto o:fx){
				int dx=px+o[0],dy=py+o[1];
				if(dx<1 || dy<1 || dx>m || dy>m) continue;
				if(f[dx][dy]<=f[px][py]+1) continue;
				f[dx][dy]=f[px][py]+1;
				q.push(MP(dx,dy));
			}
		}
	}
	//由于到达后第二天才可以攻占，故结果加上n-1
	cout<<res+n-1;
	return 0;
} 
```


---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9709)

其实就是最小生成树。

我们可以先处理出两两个点之间的时间，也就是建一个图，时间为两个点之间的连边的权值。

接下来我们就可以把题目给的过程看做从已攻占的点的集合中的其中一个点到未被攻占的点中的一个点，答案加上该边权值，将该点加入已攻占的集合内，求最小答案。我们可以发现，这个过程实际上就是求最小生成树，并且是 prim 算法的实现过程，攻占的点的集合就是生成树中目前的集合。
# CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long dis[2010][2010];
int zyx[2010],zyy[2010];
int dx[8]={1,2,2,1,-1,-2,-2,-1},dy[8]={2,1,-1,-2,-2,-1,1,2};
bool b[2010][2010]={0};
int g[2010][2010];
struct aaa
{
	int x,y,s;
};
inline void bfs(int x)
{
	queue<aaa> q;
	q.push(aaa{zyx[x],zyy[x],0});
	while(!q.empty())
	{
		aaa d=q.front();
		q.pop();
		if(b[d.x][d.y]) continue;
		b[d.x][d.y]=1;
		dis[x][g[d.x][d.y]]=d.s;
		for(register int i=0;i<8;i++)
		{
			int xx=d.x+dx[i],yy=d.y+dy[i];
			if(xx<=0||yy<=0||xx>m||yy>m) continue;
			if(b[xx][yy]) continue;
			q.push(aaa{xx,yy,d.s+1});
		}
	}
	for(register int i=1;i<=m;i++)
		for(register int j=1;j<=m;j++)
			b[i][j]=0;
}
long long ans=0;
long long d[2010];
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		zyx[i]=x,zyy[i]=y;
		g[x][y]=i;
		d[i]=999999999;
	}
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			dis[i][j]=999999999;
	for(register int i=1;i<=n;i++) bfs(i);
	d[1]=0;
	bool vis[2010]={0};
	for(register int i=1;i<=n;i++)
	{
		int u=1,minn=2147483647;
		for(register int j=1;j<=n;j++) if(!vis[j]&&d[j]<minn) u=j,minn=d[j];
		vis[u]=1,ans+=d[u];
		for(register int j=1;j<=n;j++) d[j]=min(d[j],dis[u][j]);
	}
	printf("%lld",ans+n-1);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

对于这道题，首先暴力找出任意两座城市之间的最短路，跑 $n$ 次 BFS 就行。这里 BFS 的时候可以直接求第 $i$ 座城市的坐标 $(x_i,y_i)$ 到所有图上坐标的最短路，最后第 $i$ 座城市到第 $j$ 组城市的最短路就是 $(x_i,y_i)$ 到 $(x_j,y_j)$ 的最短路。

现在求出来每两座城市之间的最短路，不难想到题目求的就是这些城市通过连接成树的最小边权和。用 Kruskal 就行。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,pair<int,int>>
#define x first
#define y second

const int N=2001,M=151;
int n,m;
int dx[11]={-1,1,2,-2,-1,1,2,-2},dy[11]={2,2,1,1,-2,-2,-1,-1};
struct node{
	int x,y,id;
}a[N];
int dis[M][M],vis[M][M],dist[N][N];
int fa[N];
struct tree{
	int x,y,z;
}tr[N*N];int idx;

il void bfs(int s){
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	queue<PII> qu;
	qu.push({0,{a[s].x,a[s].y}});
	dis[a[s].x][a[s].y]=0;
	while(!qu.empty()){
		PII now=qu.front();qu.pop();
		if(vis[now.y.x][now.y.y]) continue;
		vis[now.y.x][now.y.y]=1;
		for(re int i=0;i<8;++i){
			int x=now.y.x+dx[i],y=now.y.y+dy[i];
			if(x<=0||y<=0||x>m||y>m) continue;
            if(dis[x][y]>now.x+1)
			dis[x][y]=now.x+1,qu.push({now.x+1,{x,y}});
		}
	}
    return ;
}

il bool cmp(tree a,tree b){return a.z<b.z;}
il int find(int x){return (fa[x]==x)?x:(fa[x]=find(fa[x]));}

il void solve(){
	cin>>n>>m;
	for(re int i=1;i<=n;++i) cin>>a[i].x>>a[i].y,a[i].id=i;
	for(re int i=1;i<=n;++i){
		bfs(i);
		for(re int j=1;j<=n;++j) 
            dist[i][j]=dis[a[j].x][a[j].y];
	}
	int ans=0;
	for(re int i=1;i<=n;++i)
		for(re int j=i+1;j<=n;++j)
			tr[++idx]={i,j,dist[i][j]+1};
	sort(tr+1,tr+idx+1,cmp);
	for(re int i=1;i<=n;++i) fa[i]=i;
	for(re int i=1;i<=idx;++i){
		int x=find(tr[i].x),y=find(tr[i].y);
		if(x!=y) ans+=tr[i].z,fa[x]=y;
	}
	cout<<ans;
    return ;
}

signed main(){
	solve();
    return 0;
}
```


---

## 作者：DecemberFox (赞：0)

# P9709 题解

## 题目分析

本题的大致意思是给定一个大小为 $m \times m$ 的方格以及 $n$ 个分别位于不同坐标的城市，要求每次从任意一个已被占领的城市出发，到达其他城市进行攻打并将其占领，每次移动和攻打都需要耗费 $1$ 天的时间。

要求出攻打下所有城市的最少时间。

## 解法分析

一开始可以确定的是，从某一个城市去攻打另外一个城市所花费的时间是不变的，并且由于攻打都只花费 $1$ 天，想要尽快攻打完所有城市，就要贪心最小化行进的距离。

根据上述贪心的想法，在第一次进行攻打时，需要从 $1$ 号城市出发，前往距离 $1$ 号城市最近的城市并攻打下来（假设距离 $k$ 号城市距离 $1$ 号城市最近）。

而在第二轮攻打时，需要从已经被攻打的城市出发，即从 $1$ 号或者是 $k$ 号城市开始出发，攻打一个最近的城市。

以此类推，直到攻打下所有城市。

这样看来，这种贪心方法就与最小生成树 Prim 算法非常相似。

因此，我们可以先用广度优先搜索算法求出每两点之间的距离，时间复杂度为 $O(nm^2)$，然后对每个点之间都建一条边，建一张完全图，再使用 Prim 或者是 Kruskal 求最小生成树即可。

最终时间复杂度为 $O(nm^2+m\operatorname{log}n)$。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<utility>
#include<climits>
#include<vector>
#include<cstdio>
#include<queue>
namespace io
{
	void read()
	{
		return;
	}
	template<typename nowtype,typename ...nexttype>
	void read(nowtype &now,nexttype &...next)
	{
		register char c=getchar();
		register int n(1);
		now=0;
#define isdigit(c) ((c)>='0'&&(c)<='9')
		while(!isdigit(c)){if(c=='-') n=-1;c=getchar();}
		while(isdigit(c)){now=(now<<1)+(now<<3)+(c^48);c=getchar();}
#undef isdigit
		now*=n;
		read(next...);
	}
	template<typename type>
	void write(type num,char end='\n')
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
	}
	template<typename type,typename ...nexttype>
	void write(type num,char end,nexttype ...next)
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
		write(next...);
	}
}
//以上为快读快写
using namespace io;
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	const int const1=2500;
	int map[const1][const1],a[const1],b[const1],f[const1],mov[8][2]={{-1,2},{1,2},{2,1},{-2,1},{-1,-2},{1,-2},{2,-1},{-2,1}},m;
	bool vis[const1][const1];
	std::queue<std::pair<std::pair<int,int>,int> > q;
	struct edges
	{
		int from,to,dist;
	};
	std::vector<edges> e;
	void bfs(int start)                          //广搜将以 start 号城市为起点到达其他城市的最短路径搜索出来
	{
		while(!q.empty()) q.pop();
		std::memset(vis,false,sizeof vis);
		q.push(std::make_pair(std::make_pair(a[start],b[start]),0));
		vis[a[start]][b[start]]=true;
		int i,x,y,nx,ny,dist;
		while(!q.empty())
		{
			x=q.front().first.first;
			y=q.front().first.second;
			dist=q.front().second;
			q.pop();
			for(i=0;i<8;++i)
			{
				nx=x+mov[i][0];
				ny=y+mov[i][1];
				if(!vis[nx][ny]&&nx>0&&ny>0&&nx<=m&&ny<=m)
				{
					vis[nx][ny]=true;
					if(map[nx][ny])
					{
						q.push(std::make_pair(std::make_pair(nx,ny),dist+2));
						e.push_back({start,map[nx][ny],dist+2});
					}
					else q.push(std::make_pair(std::make_pair(nx,ny),dist+1));
				}
			}
		}
	}
	int find(int x)                              //并查集
	{
		if(f[x]!=x) return f[x]=find(f[x]);
		return f[x];
	}
	void merge(int x,int y)
	{
		f[x]=f[y];
	}
	inline bool cmp(edges x,edges y)
	{
		return x.dist<y.dist;
	}
	void solve()
	{
		int i,n,ans(0),cnt(0);
		read(n,m);
		for(i=1;i<=n;++i)
		{
			read(a[i],b[i]);
			map[a[i]][b[i]]=i;           //在图上标注城市
			f[i]=i;                      //并查集初始化
		}
		for(i=1;i<=n;++i) bfs(i);
		std::sort(e.begin(),e.end(),cmp);    //将边进行排序
		for(edges i:e)
		{
			if(find(i.from)!=find(i.to))
			{
				++cnt;
				merge(find(i.from),find(i.to));
				ans+=i.dist;
			}
			if(cnt==n-1) break;
		}
		write(ans);
	}
}
int main()
{
	SOLVE::solve();
	return 0;
}
```

---

