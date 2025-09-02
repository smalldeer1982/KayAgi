# [USACO17FEB] Why Did the Cow Cross the Road III S

## 题目描述

奶牛为什么要过马路？其中一个原因是 Farmer John 的农场有很多道路，使得他的奶牛在四处走动时不可避免地要穿过许多道路。

FJ 的农场被安排成一个 $N \times N$ 的方形网格田地（$2 \leq N \leq 100$），某些相邻的田地（例如南北向或东西向）被道路分隔，整个网格的外部有一圈高高的围栏，防止奶牛离开农场。奶牛可以从任何田地自由移动到相邻的田地（北、东、南或西），尽管它们除非绝对必要，否则不愿意穿过道路。

农场上有 $K$ 头奶牛（$1 \leq K \leq 100, K \leq N^2$），每头奶牛位于不同的田地。如果一头奶牛要拜访另一头奶牛时必须至少穿过一条道路，那么这对奶牛被称为“远距离”对。请帮助 FJ 计算远距离奶牛对的数量。

## 样例 #1

### 输入

```
3 3 3
2 2 2 3
3 3 3 2
3 3 2 3
3 3
2 2
2 3```

### 输出

```
2```

# 题解

## 作者：Annam (赞：15)

蒟蒻的第五篇题解

目录

1.思路

2.代码

一.思路

关于每个格子是否有道路相隔可以那一个三维数组记一下，这题跟[P1457 城堡 The Castle](https://www.luogu.com.cn/problem/P1457)比较像

之后再把牛的方位记一下

然后用dfs染色，最后统计每个连通块上的牛的个数，最后在把他们两两相乘的积相加得出答案

二.代码

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
int n,k;
int road;
int a[105][105][4];//北东西南 
int color[105][105];
int b[105][105];
int x,y,x1,y1;
int num;
int all;
long long ans;
vector<int> area;
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};//北东西南 
void dfs(int x,int y)
{
	if(x<1||y<1||x>n||y>n){
		return;
	}
	if(color[x][y]!=-1){
		return;
	}
    color[x][y]=num;	
	if(b[x][y]==1){
		all++;
	}
	for(int i=0;i<4;i++){
		if(a[x][y][i]==1){
			continue;
		}
		int xx=x+dx[i];
		int yy=y+dy[i];
		dfs(xx,yy);
	}
}
int main()
{
	cin>>n>>k>>road;
	for(int i=1;i<=road;i++){
		cin>>x>>y>>x1>>y1;
		if(x==x1){
			a[x][min(y,y1)][1]=1;
			a[x][max(y,y1)][3]=1;
		}else{
			a[min(x,x1)][y][2]=1;
			a[max(x,x1)][y][0]=1;
		}
	}
	for(int i=1;i<=k;i++){
		cin>>x>>y;
		b[x][y]=1;
	}
	area.push_back(0);
	memset(color,-1,sizeof(color));
	for(int i=1;i<=n;i++){
		for(int i1=1;i1<=n;i1++){
			if(color[i][i1]==-1){
				all=0;
				num++;
				dfs(i,i1);
				area.push_back(all);
			}
		}
	}
	for(int i=1;i<num;i++){
		for(int i1=i+1;i1<=num;i1++){
			ans+=area[i]*area[i1];
		}
	}
	cout<<ans;
	return 0;
}
```

~~莫抄袭，没了AC记录，空悲切~~

---

## 作者：李不似 (赞：5)

-  楼上有一篇大佬的题解用w[L][L][L][L]存图，我试着提交了一下，发现MLE爆了五个点。于是我就调整了一下，用w[L][L][4]存图。
- 事实上，两个区域是四连通的，即选定(r1,c1)后(r2,c2)只会出现在(r1,c1)的上、下、左或右。所以用w[L][L][0]、w[L][L][1]、w[L][L][2]、w[L][L][3]存储r1=r2+1,r1=r2-1,c1=c2+1,c1=c2-1四种情况。
- 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int L=105;
int n,k,r,w[L][L][4],vis[L][L],ans,dx[L*L],dy[L*L],group[L][L],cnt,r1,c1,r2,c2,xx,yy;
void dfs(int x,int y)
{
    group[x][y]=ans;
    vis[x][y]=1;
    if(w[x][y][0]!=1&&!vis[x-1][y])
        dfs(x-1,y);
    if(w[x][y][1]!=1&&!vis[x+1][y])
        dfs(x+1,y);
    if(w[x][y][3]!=1&&!vis[x][y+1])
        dfs(x,y+1);
    if(w[x][y][2]!=1&&!vis[x][y-1])
        dfs(x,y-1);
}
int main()
{
	cin>>n>>k>>r;
    for(int i=1;i<=n;i++)
        vis[0][i]=vis[i][0]=vis[n+1][i]=vis[i][n+1]=1;
    for(int i=1;i<=r;i++)
    {
        cin>>r1>>c1>>r2>>c2;
        if(r1+1==r2)w[r1][c1][1]=w[r2][c2][0]=1;
        if(r1==r2+1)w[r1][c1][0]=w[r2][c2][1]=1;
        if(c1+1==c2)w[r1][c1][3]=w[r2][c2][2]=1;
        if(c1==c2+1)w[r1][c1][2]=w[r2][c2][3]=1;
    }
    for(int i=1;i<=k;i++)
    {
        cin>>xx>>yy; 
        dx[i]=xx;dy[i]=yy;
    }
    for(int i=1;i<=k;i++)
        if(!vis[dx[i]][dy[i]])
        {
            ans++;
            dfs(dx[i],dy[i]);
        }
    for(int i=1;i<=k;i++)
        for(int j=i+1;j<=k;j++)
            if(group[dx[i]][dy[i]]!=group[dx[j]][dy[j]])
                cnt++;
    cout<<cnt;
    return 0;
}
```


---

## 作者：hht2005 (赞：5)

这道题要我们求遥远的牛，其实就是把道路当成障碍，去统计每个连通块有多少头牛，不在一个连通块的牛都是遥远的，可以用乘法直接计算。

在找连通块时用bfs搜索，暴力统计连通块。存图时可以用三维数组存它能否走到相邻的格子，但我用的是二维数组进行二进制压缩，可以省空间，也好看一些。

具体还有一些细节和优化，代码里有注释。
```cpp
#include<cstdio>
int c[110][110],q[210][2];//c存能否走到相邻的格子，q是循环队列
bool f[110][110],b[110][110];//f为有无牛，b标记是否被扩张过
const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};\\东南西北
int bfs(int ii,int jj)//寻找连通块
{
    int q1=0,q2=1,sum=0;
    b[ii][jj]=1;
    q[0][0]=ii;
    q[0][1]=jj;
    while(q1!=q2)
    {
        int x=q[q1][0],y=q[q1][1];
        if(++q1==210)q1=0;//循环
        sum+=f[x][y];
        for(int i=0;i<=3;i++)
        {
            int xx=x+dx[i],yy=y+dy[i];
            if(!(c[x][y]&1<<i/*二进制压缩*/)&&!b[xx][yy])
            {
                b[xx][yy]=1;
                q[q2][0]=xx;
                q[q2][1]=yy;
                if(++q2==210)q2=0;//循环
            }
        }
    }
    return sum;
}
int main()
{
    int n,k,r,x1,x2,y1,y2,ans=0;
    scanf("%d%d%d",&n,&k,&r);
    for(int i=1;i<=n;i++)
    {
    	//边界
        c[i][1]|=4;
        c[i][n]|=1;
        c[1][i]|=8;
        c[n][i]|=2;
    }
    for(int i=1;i<=r;i++)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        for(int i=0;i<=3;i++)
            if(dx[i]+x1==x2&&dy[i]+y1==y2)
            {
                c[x1][y1]|=1<<i;//道路
                c[x2][y2]|=1<<(i+2&3);
            }
    }
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&x1,&y1);
        f[x1][y1]=1;//牛的位置
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(!b[i][j])//如果当前连通块未被扩张，就扩张
            {
                int t=bfs(i,j);
                ans+=t*(k-t);//统计与当前连通块遥远的牛
            }
    printf("%d\n",ans>>1);//每头牛自己计算一次，被其他牛计算一次，所以除以二
}

```

---

## 作者：狸狸养的敏敏 (赞：3)

这一题的题意很好理解

即如果输入为$p,q,x,y$，表示$(p,q)$这个格子不能到达$(x,y)$这个格子

我们要是用一个四维数组存储的话，可行是可行，但并不是最优的方案

我们可以把整个图看成有$N^2$个点的无向图，每个点向它周围四个点连边，统计出每一个联通块有多少点，然后用乘法原理做即可

这里提供一种题解里没有的，用$Vector+$迭代器删边来减少占用的做法

具体实现请看代码

```
//Copyright (c) 2019 by xiao_mmQF. All Rights Reserved.
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define inl inline
#define reg register
#define db long double
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
inl int read(){ int x=0,f=0; char ch=0; while(!isdigit(ch))f|=(ch=='-'),ch=getchar(); while(isdigit(ch))(x*=10)+=(ch^48),ch=getchar(); return f?-x:x; }
inl void Ot(reg int x) { if(x<0)putchar('-'),x=-x; if(x>=10)Ot(x/10); putchar(x%10+'0'); }
inl void Print(reg int x,char til='\n'){Ot(x);putchar(til);}
inl int Max(reg int x,reg int y){return x>y?x:y;}
inl int Min(reg int x,reg int y){return x<y?x:y;}
inl int Abs(reg int x){return x<0?-x:x;}

const int MAXN=10010;

int n,k,r,ans;
int tot,pos[MAXN];
bool mark[MAXN],is[MAXN];
vector<int>G[MAXN];

#define It vector<int>::iterator

int get(int r,int c){return (r-1)*n+c;}
//得到第r行第c列的点的编号

void del(int x,int y){
    for(It iter=G[x].begin();iter!=G[x].end();iter++)
        if(*iter==y){G[x].erase(iter);break;}
}
//删边操作

int bfs(int x){
    int tmp=0;
    queue<int>que;
    que.push(x);
    mark[x]=1;
    while(!que.empty()){
        int h=que.front();
        que.pop();
        if(is[h])tmp++;
        for(It iter=G[h].begin();iter!=G[h].end();iter++){//迭代器真好用.jpg
            int to=*iter;
            if(!mark[to])mark[to]=1,que.push(to);
        }
    }
    return tmp;
}
//简单的bfs染色

signed main() {
    n=read(),k=read(),r=read();
    for(reg int i=1;i<=n;i++)
        for(reg int j=1;j<=n;j++){
            if(i-1>0)
                G[get(i,j)].push_back(get(i-1,j));
            if(j-1>0)
                G[get(i,j)].push_back(get(i,j-1));
            if(i+1<=n)
                G[get(i,j)].push_back(get(i+1,j));
            if(j+1<=n)
                G[get(i,j)].push_back(get(i,j+1));
        }
        
        //向自己周围四个点连边
        
    for(reg int i=1;i<=r;i++){
        int p=read(),q=read(),x=read(),y=read();
        del(get(p,q),get(x,y));
        del(get(x,y),get(p,q));
    }
    //删边操作，因为是双向的所以要删两次
    
    for(reg int i=1;i<=k;i++){
        int p=read(),q=read();
        is[pos[i]=get(p,q)]=1;
    }
    
    for(reg int i=1;i<=k;i++){
        if(!mark[pos[i]]){
            int k=bfs(pos[i]);
            ans+=k*tot;
            tot+=k;
            //乘法原理计算
        }
    }
    
    Print(ans);
    
	return 0 ;
}

```


---

## 作者：Numenor (赞：2)

    只需要用bfs求联通块染色，最后二重for求解即可。（为啥这题是个蓝题）
    直接存下标什么的太麻烦了，我们可以用2017NOIP（队列）一题中题面给出的方法：对每个点进行编号，用一个cut数组存下从哪个编号的点不能走到哪个编号的点，在bfs时判断一下就行了
    
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=11000;
int a[maxn*maxn];
int col[maxn*maxn],color;
int n,k,r;
bool cut[maxn][maxn];
int ans;

int get_num(int x,int y)
{
	return (x-1)*n+y;//用下标取出每个点的编号
}

int dx[5]={0,0,1,-1};
int dy[5]={1,-1,0,0};

bool check(int x,int y)
{
	if(x>=1&&y>=1&&x<=n&&y<=n)return 1;
	return 0;
}

void bfs(int x,int y)
{
	color++;
	queue<int>q1,q2;
	q1.push(x);q2.push(y);
	while(!q1.empty())
	{
		int u=get_num(q1.front(),q2.front());
		col[u]=color;
		for(int i=0;i<4;i++)
		{
			int xx=q1.front()+dx[i];
			int yy=q2.front()+dy[i];
			int v=get_num(xx,yy);
			if(check(xx,yy)&&!cut[u][v]&&!cut[v][u]&&!col[v])//转移时用cut数组判断
			{
				q1.push(xx);q2.push(yy);
				col[v]=color;
			}
		}q1.pop();q2.pop();
	}
}

int main()
{
	scanf("%d%d%d",&n,&k,&r);
	for(int i=1;i<=r;i++)
	{
		int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		int num1=get_num(x1,y1);
		int num2=get_num(x2,y2);
		cut[num1][num2]=cut[num2][num1]=1;
	}
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[i]=get_num(x,y);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(!col[get_num(i,j)])
			{
				bfs(i,j);
			}
		}
	}
	for(int i=1;i<k;i++)
	{
		for(int j=i+1;j<=k;j++)
		{
			if(col[a[i]]!=col[a[j]])ans++;
		}
	}cout<<ans;
	
}
```
~~最后吐槽一下题目给的数据范围，，，为啥不开到10000不给过~~

---

## 作者：曹老师 (赞：2)

~~好久没写题解了~~ 来一份炒鸡简单易懂的代码

**知识点：DFS 联通块**

dfs的时候直接找就可以 用group数组记下属于哪个连通块

跑完一遍dfs 再枚举一下多少连通块即可： j 起点i+1 （小小的剪枝

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=105;
int n,k,r,w[L][L][L][L],vis[L][L],ans,dx[L*L],dy[L*L],group[L][L],cnt;
void dfs(int x,int y,int fx,int fy)
{
    group[x][y]=group[fx][fy];
    vis[x][y]=1;
    if(w[x][y][x-1][y]!=1&&!vis[x-1][y])
        dfs(x-1,y,x,y);
    if(w[x][y][x+1][y]!=1&&!vis[x+1][y])
        dfs(x+1,y,x,y);
    if(w[x][y][x][y+1]!=1&&!vis[x][y+1])
        dfs(x,y+1,x,y);
    if(w[x][y][x][y-1]!=1&&!vis[x][y-1])
        dfs(x,y-1,x,y);
}
int main()
{
    scanf("%d%d%d",&n,&k,&r);
    for(int i=1;i<=n;i++)
        vis[0][i]=vis[i][0]=vis[n+1][i]=vis[i][n+1]=1;
    for(int i=1;i<=r;i++)
    {
        int r1,c1,r2,c2;
        scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
        w[r1][c1][r2][c2]=w[r2][c2][r1][c1]=1;
    }
    for(int i=1;i<=k;i++)
    {
        int xx,yy;
        scanf("%d%d",&xx,&yy);
        dx[i]=xx;dy[i]=yy;
    }
    for(int i=1;i<=k;i++)
        if(!vis[dx[i]][dy[i]])
        {
            ans++;
            group[0][0]=ans;
            dfs(dx[i],dy[i],0,0);
        }
    for(int i=1;i<=k;i++)
        for(int j=i+1;j<=k;j++)
            if(group[dx[i]][dy[i]]!=group[dx[j]][dy[j]])
                cnt++;
    printf("%d",cnt);
    return 0;
}
```

---

## 作者：小手冰凉 (赞：2)

我很奇怪这题为什么会有提高+/省选-（貌似题意理解有那么难？？）


大力BFS/DFS找每个连通块的牛数，然后大力求解不同连通块的牛对即可（乘法原理+加法原理可以优化）


复杂度只有O（n^2+k^2）（优化后只有O(n^2+O(连通块数））

```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int b[105][105][4];
int x[105],y[105];
int vis[105][105];
int ans,t,n,k,r;
struct xxx{
    int x,y;
}q[10005];
void bfs(int s)//大力BFS
{
    int head=1;
    int tail=1;
    q[head].x=x[s];
    q[head].y=y[s];
    vis[x[s]][y[s]]=++t;
    for(;head<=tail;head++){
//        cout<<head<<' '<<tail<<endl;
  //      cout<<' '<<q[head].x<<':'<<q[head].y<<endl;
        int xx=q[head].x;
        int yy=q[head].y;
        for(int i=0;i<4;i++)
            if(b[xx][yy][i]==0){
                int tx=xx+dx[i];
                int ty=yy+dy[i];
                if(tx<1||ty<1||tx>n||ty>n)continue;
                if(vis[tx][ty])continue;
                vis[tx][ty]=t;
                q[++tail].x=tx;
                q[tail].y=ty;
            }
    }
}
int main()
{
    scanf("%d%d%d",&n,&k,&r);
    memset(b,0,sizeof(b));
    for(int i=1;i<=r;i++){
        int x,y,tx,ty;
        scanf("%d%d%d%d",&x,&y,&tx,&ty);
        if(x==tx){
            if(y<ty)b[x][y][0]=1,b[tx][ty][2]=1;
            else b[x][y][2]=1,b[tx][ty][0]=1;
        }
        else{
            if(x<tx)b[x][y][1]=1,b[tx][ty][3]=1;
            else b[x][y][3]=1,b[tx][ty][1]=1;
        }
    }
    for(int i=1;i<=k;i++){
        scanf("%d%d",&x[i],&y[i]);
    }
    for(int i=1;i<=k;i++)
        if(!vis[x[i]][y[i]])bfs(i);
    for(int i=1;i<=k;i++)
        for(int j=i+1;j<=k;j++)
            if(vis[x[i]][y[i]]!=vis[x[j]][y[j]])
                ans++;//大力求解
    printf("%d",ans);
    return 0;
}
```

---

## 作者：OfstAutomataMachine (赞：1)

觉得这道题很简单欸……

用DFS染色，算同一个连通块里有几个奶牛，两两相乘就行了。

主要就是如何存墙

一开始，我就是用一个思维数组来存，就像这样：
```
int wall[101][101][101][101];
……
int main()
{
	cin>>n>>k>>r;
	while(r--)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		wall[a][b][c][d]=wall[c][d][a][b]=1;
	}
	……
}
```
结果……MLE。

MLE 3个点的代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,k,r,cnt,ans,num[100001],col[101][101],wall[101][101][101][101];
void dfs(int x,int y)
{
	col[x][y]=cnt;
	if(x-1>=1)
		if(!wall[x][y][x-1][y]&&!col[x-1][y])
			dfs(x-1,y);
	if(x+1<=n)
		if(!wall[x][y][x+1][y]&&!col[x+1][y])
			dfs(x+1,y);
	if(y-1>=1)
		if(!wall[x][y][x][y-1]&&!col[x][y-1])
			dfs(x,y-1);
	if(y+1<=n)
		if(!wall[x][y][x][y+1]&&!col[x][y+1])
			dfs(x,y+1);
}
int main()
{
	cin>>n>>k>>r;
	while(r--)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		wall[a][b][c][d]=wall[c][d][a][b]=1;
	}
	for(int x=1;x<=n;x++)
		for(int y=1;y<=n;y++)
			if(!col[x][y])
			{
				cnt++;
				dfs(x,y);
			}
	while(k--)
	{
		int a,b;
		cin>>a>>b;
		num[col[a][b]]++;
	}
	for(int i=1;i<cnt;i++)
		for(int l=i+1;l<=cnt;l++)
			ans+=num[i]*num[l];
	cout<<ans;
	return 0;
}
```

解决方案：把四位数组变成三维，就像这样：
```
int wall[101][101][5];
……
int main()
{
	cin>>n>>k>>r;
	while(r--)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if(a==c+1)
			wall[a][b][1]=wall[c][d][2]=1;
		if(c==a+1)
			wall[a][b][2]=wall[c][d][1]=1;
		if(b==d+1)
			wall[a][b][3]=wall[c][d][4]=1;
		if(d==b+1)
			wall[a][b][4]=wall[c][d][3]=1;
	}
	……
}
```
可以画图来理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/qa4pzsl4.png)

（个数分别代表对于四个位置wall[2][3]的第三个下标）

于是，这个问题就成了模板题难度。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,k,r,cnt,ans,num[100001],col[101][101],wall[101][101][5];
void dfs(int x,int y)
{
	col[x][y]=cnt;
	if(x-1>=1)
		if(!wall[x][y][1]&&!col[x-1][y])
			dfs(x-1,y);
	if(x+1<=n)
		if(!wall[x][y][2]&&!col[x+1][y])
			dfs(x+1,y);
	if(y-1>=1)
		if(!wall[x][y][3]&&!col[x][y-1])
			dfs(x,y-1);
	if(y+1<=n)
		if(!wall[x][y][4]&&!col[x][y+1])
			dfs(x,y+1);
}
int main()
{
	cin>>n>>k>>r;
	while(r--)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if(a==c+1)
			wall[a][b][1]=wall[c][d][2]=1;
		if(c==a+1)
			wall[a][b][2]=wall[c][d][1]=1;
		if(b==d+1)
			wall[a][b][3]=wall[c][d][4]=1;
		if(d==b+1)
			wall[a][b][4]=wall[c][d][3]=1;
	}
	for(int x=1;x<=n;x++)
		for(int y=1;y<=n;y++)
			if(!col[x][y])
			{
				cnt++;
				dfs(x,y);
			}
	while(k--)
	{
		int a,b;
		cin>>a>>b;
		num[col[a][b]]++;
	}
	for(int i=1;i<cnt;i++)
		for(int l=i+1;l<=cnt;l++)
			ans+=num[i]*num[l];
	cout<<ans;
	return 0;
}
```


---

## 作者：Clown_Clear (赞：1)

（新人第一次发题解……）
本题数据比较水
考虑用二维结构体存储n*n每个点的上下左右是否有边，再记录这个点是不是牛。
再来一个结构体记录牛所在的点的横纵坐标。然后并查集枚举每个点，在记录有几个集合，每个集合里有几个数。然后每个集合数量相乘和即为正解。
代码如下：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,k,r;
int fa[10010];
int find(int x)
{
	if(fa[x]==x)
	return x;
	else
	return fa[x]=find(fa[x]);
}
void merge(int u,int v)
{
	int fau=find(u);
	int fav=find(v);
	if(fau==fav)
	return;
	else
	fa[fau]=fav;
	return ;
}
struct niu{
	bool north;
	bool south;
	bool west;
	bool east;
	bool cow;
}a[105][105];
struct node{
	int x;
	int y;
}b[10010];
int x1,x2,y1,y2;
int t[10010];
int tot=0;
int tt[10010];
int main()
{
	scanf("%d%d%d",&n,&k,&r);
	for(int i=1;i<=r;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1==x2)
		{
			if(y1+1==y2)
			{
				a[x1][y1].east=1;
				a[x1][y2].west=1;
			}

			else
			{
				a[x1][y1].west=1;
				a[x1][y2].east=1;
			}
		}
		else
		{
			if(x1+1==x2)
			{
				a[x1][y1].north=1;
				a[x2][y1].south=1;
			}
			else
			{
				a[x1][y1].south=1;
				a[x2][y1].north=1;
			}
		}
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&x1,&y1);
		b[i].x=x1;
		b[i].y=y1;
		a[x1][y1].cow=1;
	}
	for(int i=1;i<=n*n;i++)
	fa[i]=i;
	int num=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			num++;
			if(i!=n)
			if(a[i][j].north!=1)
			merge(num,num+n);
			if(j!=n)
			if(a[i][j].east!=1)
			merge(num,num+1);
		}
	}
	for(int i=1;i<=k;i++)
	{
		int sum=0;
		int xx=b[i].x;
		int yy=b[i].y;
		sum=(xx-1)*n+yy;
		if(a[xx][yy].cow==1)
		t[find(sum)]++;
	}
	for(int i=1;i<=n*n;i++)
	{
		if(t[i]!=0)
		{
		tot++;
		tt[tot]=t[i];	
		}
		
	}
	int ans=0;
	for(int i=1;i<tot;i++)
	for(int j=i+1;j<=tot;j++)
	{
		ans=ans+tt[i]*tt[j];
	}
	printf("%d",ans);
	return 0;
}
```

---

