# [USACO08NOV] Guarding the Farm S

## 题目描述

The farm has many hills upon which Farmer John would like to place guards to ensure the safety of his valuable milk-cows.

He wonders how many guards he will need if he wishes to put one on top of each hill. He has a map supplied as a matrix of integers; the matrix has N (1 < N <= 700) rows and M (1 < M <= 700) columns. Each member of the matrix is an altitude H\_ij (0 <= H\_ij <= 10,000). Help him determine the number of hilltops on the map.

A hilltop is one or more adjacent matrix elements of the same value surrounded exclusively by either the edge of the map or elements with a lower (smaller) altitude. Two different elements are adjacent if the magnitude of difference in their X coordinates is no greater than 1 and the magnitude of differences in their Y coordinates is also no greater than 1.


## 说明/提示

There are three peaks: The one with height 4 on the left top, one of the points with height 2 at the bottom part, and one of the points with height 1 on the right top corner.


## 样例 #1

### 输入

```
8 7 
4 3 2 2 1 0 1 
3 3 3 2 1 0 1 
2 2 2 2 1 0 0 
2 1 1 1 1 0 0 
1 1 0 0 0 1 0 
0 0 0 1 1 1 0 
0 1 2 2 1 1 0 
0 1 1 1 2 1 0 
```

### 输出

```
3 
```

# 题解

## 作者：素质玩家孙1超 (赞：12)

这题原来我没看懂题目意思，被坑了好久。

~~其实题目意思不是非常明确（疯狂甩锅）~~

**题意：**

在矩阵中，如果一个元素的高度大于等于其他邻接的 八个 元素（其中有可能有

边界），那么他可以作为一个山丘的顶，并那八个元素可以向外扩散，形成严格

不上升的区块。

![](https://i0.hdslb.com/bfs/album/873c6da51c42e392cae8d736bac9771f9b6b8e60.png)


**要点：**

注意，由于一个山丘里面可能包含另一个山丘，所以如果不处理的话，答案会

偏大。正确的做法是从最大的开始搜索，可以有效防止重复。

代码：~~我对我的代码还是有点信心的~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int R()//快读 
{
	char c;int sign=1,res=0;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;
	res+=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;	
}
const int dx[8]={1,-1,0,0,1,1,-1,-1};
const int dy[8]={0,0,1,-1,-1,1,1,-1};
struct point//用来排序的结构体 
{
	int x,y,h;	
}a[1010*1010];
bool cmp(point x,point y)
{
	return x.h>y.h; 
} 
int n,m,ans;
int q[1010][1010];//矩阵 
bool flag[1010][1010];//记录 
void dfs(int x,int y)
{
	if(x>n||y>m||!x||!y) return;//越界 
	flag[x][y]=1;//标记 
	for(int i=0;i<8;i++)//搜索 
		if(!flag[x+dx[i]][y+dy[i]]&&q[x+dx[i]][y+dy[i]]<=q[x][y])
			dfs(x+dx[i],y+dy[i]);
}
int main()
{
	n=R();m=R();
	int o=0;
	for(int i=1;i<=n;i++)	
		for(int j=1;j<=m;j++)
		{
			q[i][j]=R();
			a[++o].h=q[i][j];
			a[o].x=i;a[o].y=j;
		}
//以上是读入 
	sort(a+1,a+1+o,cmp);
	for(int i=1;i<=o;i++)//从最大的开始搜 
	{
		int x=a[i].x,y=a[i].y;
		if(!flag[x][y])//如果没去过 
		{
			bool f=1;
			for(int p=0;p<8;p++)//判断是否可以作为山顶 
				if(q[x][y]<q[x+dx[p]][y+dy[p]])
					f=0;
			if(f)
				dfs(x,y),ans++;//搜索出整个山丘 
		}
	}
	cout<<ans;
}

```




---

## 作者：沉辰 (赞：11)

说一下思路，我们可以把获取的高度从高到底排一下序，然后从高到低依次去扩展，这样的话就省了很多问题；最后统计答案就好了；

含要注意：它可以向八个方向扩展

***************************************************************************************

        
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
#include<queue>
#define mod 100000007
#define inf 336860180
#define PI 3.1415926
#define ll long long
using namespace std;
int n,m,ans,H,tot,h[702][702];
struct po{int x,y,h;}a[703*703];
queue<int>qx,qy;
int fx,fy,rx,ry;
bool v[1000][1000];
bool cmp(po xx,po yy){return xx.h>yy.h;}
int X[8]={0,0,1,-1,1,-1,1,-1};
int Y[8]={1,-1,0,0,1,1,-1,-1};
void bfs(int x,int y)
{
    qx.push(x);qy.push(y);
    v[x][y]=1;
    while(!qx.empty())
    {
      fx=qx.front();qx.pop();
      fy=qy.front();qy.pop();
      H=h[fx][fy];
      for(int i=0;i<=7;i++)
      {
        rx=X[i]+fx;ry=Y[i]+fy;
        if(rx<1 || rx >n || ry<1 || ry>m) continue;
        if(v[rx][ry]) continue;    //呼应下文 
        if(h[rx][ry]<=H)//关键，只有比他低才属于这一座山峰 
        {
          qx.push(rx);qy.push(ry);
          v[rx][ry]=1;    
        }
      }    
    }
}
int main()
{
    //请忽略de-bug 
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
     for(int j=1;j<=m;j++)
     {
        tot++;
        scanf("%d",&a[tot].h);
        h[i][j]=a[tot].h;
        a[tot].x=i;a[tot].y=j;
     } 
    sort(a+1,a+tot+1,cmp);//关键所在 
    //for(int i=1;i<=tot;i++)
    // cout<<a[i].h<<endl;
    memset(v,0,sizeof(v));
    for(int i=1;i<=tot;i++)
    {
      int xx=a[i].x,yy=a[i].y;
      if(v[xx][yy]) continue;//如果他之前被扩展到过，说明它属于另一个山峰
      //那就没有必要以他为山峰去扩展了 
     // cout<<xx<<" "<<yy<<" "<<h[xx][yy]<<endl;
      bfs(xx,yy);
      ans++;//break;//答案加加 
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：ouuan (赞：9)

我其实也想过从高到低搜索这种做法，~~但总感觉自己会写错..~~

言归正传，我的做法的核心就在于

### 凡是周围八格有比自己高的，这个格子所在的等高连通块就不可能是一座山丘，反之肯定是

首先我这里说的山丘是严格按照题面意思来的，即比周围都高的等高连通块，而不是从高到低一整个。然后这句话的正确性..~~需要我证吗？自己想想就好了。~~

所以先扫一遍看看哪些连通块不是答案，然后剩下的数连通块就行了

代码：
```
#include <iostream>
#include <cstdio>

using namespace std;

void dfs(int x,int y);

int n,m,a[710][710],ans,dir[8][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}}; //dir数组记录八个方向，之后就只用一个for而不用手写八遍了
bool vis[710][710];

int main()
{
	int i,j,k;
	
	cin>>n>>m;
	
	for (i=1;i<=n;++i)
	{
		for (j=1;j<=m;++j)
		{
			cin>>a[i][j];
		}
	}
	
	for (i=1;i<=n;++i)
	{
		for (j=1;j<=m;++j)
		{
			for (k=0;k<8;++k)
			{
				if (a[i][j]<a[i+dir[k][0]][j+dir[k][1]])
				{
					dfs(i,j); //如果周围八格有比自己高的就把整个连通块的vis设为true
				}
			}
		}
	}
	
	for (i=1;i<=n;++i)
	{
		for (j=1;j<=m;++j)
		{
			if (!vis[i][j]) //还没有被排除在答案外的连通块就全是答案了
			{
				++ans; 
				dfs(i,j);
			}
		}
	}
	
	cout<<ans;
	
	return 0;
}

void dfs(int x,int y)
{
	if (vis[x][y]||x==0||y==0||x>n||y>m)
	{
		return;
	}
	
	vis[x][y]=true;
	
	for (int i=0;i<8;++i)
	{
		if (a[x][y]==a[x+dir[i][0]][y+dir[i][1]])
		{
			dfs(x+dir[i][0],y+dir[i][1]);
		}
	}
}
```

---

## 作者：Khassar (赞：8)

/\*
看这道题的题解有点少贡献一个。

其实这题也不算难（也别想太简单了->白WA四次）

这题就是告诉你每个点的高度，如果一个点的周围八个方向的点的高度都小于它（或者是边界）那它就是一个山顶，最后求山顶的总数。

显然我们从最高的点依次找下去，扩展出所有的属于这个山的点，把所有扩展到的点都标记上，

表示它已经属于一座山了，然后ans+1，等所有的点都已经属于各自的山了，ans就是山顶数了(注意一定要从高往低找啊，不然会增解)

楼下两位用的都是dfs，这里我就贡献一个bfs的做法

顺便安利一下Blog：https://dedsecr.github.io/

\*/









```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<vector>
#include<ctime>
#define ll long long
#define R register
#define Rf(a,b,c) for(R int (a)=(b);(a)<=(c);++(a))
#define Tf(a,b,c) for(R int (a)=(b);(a)>=(c);--(a))
#define D double
using namespace std;
const int N=705;
int w[N][N],n,m,ans,vis[N][N],tot;
//w存图，vis用来记这个点有没有以及属于一座山 
int dx[8]={0,1,0,-1,1,1,-1,-1};//宽搜用的方向数组 
int dy[8]={1,0,-1,0,1,-1,1,-1};//一开始这里写错了233 
struct node{
    int x,y,h;
}a[N*N];//用来重新存一下图，方便排序 
queue <int> q1,q2;
inline int read() {//读入及输出优化 
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
    return x*f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
void bfs(int si,int sj) {//宽搜以(si,sj)为山顶的山 
    q1.push(si);q2.push(sj);
    while(!q1.empty()) {
        R int nowx=q1.front(),nowy=q2.front();q1.pop();q2.pop();
        Rf(i,0,7) {//寻找八个方向 
            R int x=nowx+dx[i],y=nowy+dy[i];
            if(x>0&&x<=n&&y>0&&y<=m&&w[x][y]<=w[nowx][nowy]&&!vis[x][y]) {
            //如果这个点没有越界，高度偏小，不属于任何一座山 
                vis[x][y]=1;
                q1.push(x);q2.push(y);//就加进当前这座山 
            }
        }
    }
}
bool cmp1(node x,node y) {return x.h>y.h;}//按高度从大到小排序 
int main()
{
    n=read();m=read();
    Rf(i,1,n) Rf(j,1,m) {
        a[++tot].x=i;a[tot].y=j;//把图读进来，同时装进a数组用来排序 
        w[i][j]=a[tot].h=read();
    }
    sort(a+1,a+1+tot,cmp1);//排序 
    Rf(i,1,tot) {//从大到小枚举每个点 
        if(!vis[a[i].x][a[i].y]) {//如果这个点不属于任何一座山
        //那么它就是当前最高的点 
            vis[a[i].x][a[i].y]=1;
            bfs(a[i].x,a[i].y);//把这个点作为山顶宽搜 
            ans++;//山顶数+1 
        }
    }
    write(ans);
    return 0;
}

```

---

## 作者：DR安 (赞：4)

## 听说NOIP前写题解可以增加RP

除了题目有些歧义以外，这是一个较简单的深搜

要找最少且尽量高的小山丘数量，首先想到了按照点的高度排序

然后从最高点开始搜索

然鹅这是一个二维地图，怎样能快速排序呢

自然是用一个结构体，存下每个点的信息（x,y,h）

用sort按照h从大到小排序

然后开始搜索，并且用一个vis数组来记录某个点是否被搜索过

在主函数中写一个循环，一个山丘找完后继续找下一个山丘

```cpp
for(int i=1;i<=n*m;i++) //从高到低搜索未搜过的点 
		if(!vis[hi[i].x][hi[i].y]){ dfs(hi[i].x,hi[i].y); ans++;}//累加答案 
```

这样就可以找到所有的山丘辣

具体内容看代码

帖上我29行的未压行代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct H{ int x,y,h; }hi[500000];//结构体方便排序 
bool cmp(H x,H y){ return x.h>y.h;}
int n,m,cnt,vis[1000][1000],ans,mp[800][800];
int mox[10]={0,1,-1,0,0,1,-1,1,-1},moy[10]={0,0,0,-1,1,-1,-1,1,1};//点的转移 
void dfs(int x,int y){
	vis[x][y]=1;//标记已经搜过 
	for(int i=1;i<=8;i++)
		for(int j=1;j<=8;j++){//八个方向 
			int xx=x+mox[i],yy=y+mox[j];//下一个要搜的点的行和列 
			if(xx>n or xx<0 or yy<0 or yy>m) continue;//判断是否越界 
			if(mp[xx][yy]<=mp[x][y] and !vis[xx][yy]) dfs(xx,yy);//继续搜索 
		}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){//结构体记录行，列，高度 
			hi[++cnt].x=i; hi[cnt].y=j; scanf("%d",&hi[cnt].h);
			mp[i][j]=hi[cnt].h; //记录高度 
		}
	sort(hi+1,hi+n*m+1,cmp);//按照高度排序 
	for(int i=1;i<=n*m;i++) //从高到低搜索未搜过的点 
		if(!vis[hi[i].x][hi[i].y]){ dfs(hi[i].x,hi[i].y); ans++;}//累加答案 
	cout<<ans;
}
```

---

## 作者：吉瑞降临 (赞：4)

这道题是一道典型的递归的，可以一个一个搜索，
搜索时要注意边界，同时还有一种可能，就是找到一个比它高且没访问过的时侯，直接不能访问且这次不能累加，如果加上这一次，就无法达到题目要求中最优的结果。

访问周围的地方时，有八个方向，依次寻找就可以了,运用偏移量使代码更简洁。

本以为这个代码要优化，没想数据简单很容易就过了。

DFS 的暴力枚举方法。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int X[]={-1,-1,-1,0,0,1,1,1};  // 行的偏移量
int Y[]={-1,0,1,-1,1,-1,0,1};  // 列的偏移量
int vis[10001][10001],map[10001][10001],n,m;
bool check(int x,int y)
{
	if(x>=1&&x<=n&&y>=1&&y<=m)
	    return true;
	return false;
}  // 判断是否超出边界
bool dfs(int x,int y,int h)
{
	bool flag=true;  // 先定义为真
	if(map[x][y]==h&&vis[x][y])
	    return true;   // 已经访问过了
	if(map[x][y]>h)
	    return false;  // 如果比它高，就不能访问
	if(map[x][y]<h)
	    return true;  // 可以访问的
	vis[x][y]=true;  // 标记访问过了
	for(int i=0;i<8;i++)  // 向相邻的地方寻找
	    if(check(x+X[i],y+Y[i]))
	        flag=flag&dfs(x+X[i],y+Y[i],h);  // 判断是否可行，并运用 & 运算保留结果
return flag;   // 返回结果
}
int main()
{
	int ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
	        cin>>map[i][j];   // 输入地图
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
	        if(!vis[i][j]) // 只有没访问过的才行
	        {
	        	if(dfs(i,j,map[i][j]))
	        	    ans++;  // 累加结果
			}
	cout<<ans<<endl;  // 输出答案
	return 0;
}
```

就这样，一篇代码就写完了，希望对你能有点帮助。


---

## 作者：Xhesika_Frost (赞：3)

这道题的题面真的有歧义

体面说是更低，但是事实上我们在搜索的时候需要把和当前点一样高的一起扩展了。

这个小山丘是个啥玩意，我的理解就是再这个图上倒水（雾），水可以往更低或一样低的地方流，问至少几桶水可以把地图覆盖。

这样题面好理解多了

~~农夫john的奶牛确实值钱，因为可以用他们出各种题~~

```cpp
#include <iostream> 
#include<cstdio>
#include<algorithm>
using namespace std;
struct so{
	int x;
	int y;
	int v;
}s[500000];
int ma[800][800];
bool cmp(so x,so y){
	return x.v>y.v;
}
int vis[800][800];
int x,y,n,m,now;
int ans;
int p;
int xc[8]={1,1,0,-1,-1,-1,0,1};
int yc[8]={0,1,1,1,0,-1,-1,-1};
void dfs(int x,int y){
	if(x<0||y<0||x>n||y>m){
		return ;
	}
	vis[x][y]=1;
	for(int i=0;i<=7;++i){
		if(ma[x+xc[i]][y+yc[i]]<=ma[x][y]&&!vis[x+xc[i]][y+yc[i]])
		dfs(x+xc[i],y+yc[i]);
	}
	return ;
	
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%d",&now);
			ma[i][j]=now;
			p++;
			s[p].x=i;
			s[p].y=j;
			s[p].v=now;
		}
	}
	sort(s+1,s+p+1,cmp);
	for(int i=1;i<=p;++i){
		if(!vis[s[i].x][s[i].y]){
			ans++;
			dfs(s[i].x,s[i].y);
		}
	}	cout<<ans;
	return 0;
	
	
}
```


---

## 作者：巨型方块 (赞：3)

想了半天才想到一个比较简单的方法

就是大力枚举每一个色块，判断色块是否为答案

就好了。。。。。

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=1e3+5;
int xxx[]{0,0,1,1,1,-1,-1,-1};
int yyy[]{1,-1,1,0,-1,1,0,-1};
int a[N][N];
bool vi[N][N];
int n,m,ans;
bool dfs(int xx,int yy){
    vi[xx][yy]=1;
    bool ok=1;
    for(int i=0;i<8;i++){
        int x=xx+xxx[i];
        int y=yy+yyy[i];
        if(x<1||y<1||x>n||y>m)continue;
        if(a[x][y]>a[xx][yy])ok=0;
        if(a[x][y]==a[xx][yy]&&!vi[x][y])ok=ok&dfs(x,y);
    }return ok;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!vi[i][j])
                if(dfs(i,j))ans++;
    printf("%d",ans);
}
```

---

## 作者：田大坑 (赞：2)

前言：每道题目都可以搜索，这道也不例外

看到题目，大家都可以想到搜索，只要对于每一个山顶坐标（最高且没有别染色的点）进行枚举，然后把旁边比他矮的全部染成一个颜色，就可以水过这道题目了

楼下的题解都用的sort，我用的堆维护，总之，每次选取最高的点，然后用dfs跑一遍就可以了


```
#include<bits/stdc++.h>
using namespace std;
int dx[9]={0,1,0,-1,0,1,1,-1,-1},
    dy[9]={0,0,1,0,-1,1,-1,1,-1};
int h[701][701],n,m,ans;
struct mout{
    int high,x,y;
}e[50001];
struct cmp{
    bool operator ()(mout a,mout b)
    {return a.high<b.high;}
};//自定义函数
bool vis[701][701];
priority_queue<mout,vector<mout>,cmp > pq;//大根堆
void dfs(int x,int y)
{
    for(int i=1;i<=8;i++)
    {
        int ex=x+dx[i],ey=y+dy[i];
        if(!vis[ex][ey]&&h[ex][ey]<=h[x][y]&&ex>0&&ey>0&&ex<=n&&ey<=m)//判断是否越界已经是否符合条件
        {
            vis[ex][ey]=1;//打个标记
            dfs(ex,ey);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        scanf("%d",&h[i][j]);
        pq.push((mout){h[i][j],i,j});//丢到堆里面
    }
    for(int i=1;i<=n*m&&!pq.empty();i++)
    {
        mout tt=pq.top();//取出元素
        pq.pop();
        if(!vis[tt.x][tt.y])
        {
            ans++;//233
            dfs(tt.x,tt.y);//当前最高的点，对周围进行dfs
        }
    }
    printf("%d",ans);
    return 0;//qwq bye
}
```



话说stl正好用

---

## 作者：Hiraeth (赞：1)

## rt 

### 若地图中一个元素所邻接的所有元素都比这个元素高度要小（或它邻接的是地图的边界），则该元素和其周围所有按照这样顺序排列的元素的集合称为一个小山丘。

那么我们可以用一个结构体类型记录所有非零高度的横纵坐标以及相应的高度值

然后对高度进行排序 对每一次高度进行$dfs$ 及时删除所有的联通高度的小山丘

很显然 如果从一个给定高度的山丘的最高高度进行$dfs$ 一定可以将该山丘的所有高度清零

### 犯了一个很zz的错误

在递归调用的时候 $tmp$定义的全局变量 然后在递归调用的时候 在下一次递归结束

之后 tmp的值已经被改变了 而当前层的tmp还未判断完成 

我发誓我以后在$dfs$里面只用局部变量 ~~手动再见~~

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[705][705],ans,px,py,tot,m,n;
int dx[]={0,0,1,1,1,-1,-1,-1};
int dy[]={1,-1,0,1,-1,0,1,-1};
struct p{
    int x,y,num;
}f[490005];
void dfs(int x,int y){
    int tmp=a[x][y];//在删除之前保存数据 
    //!!!每次循环都要调用tmp 在下一次递归结束之后 tmp的值已经被改变了 而当前层的tmp还未判断完成 
    a[x][y]=0;
    for (int i=0;i<=7;i++){
        px=x+dx[i];py=y+dy[i];
        if (px>0&&px<=n&&py>0&&py<=m&&tmp>=a[px][py]&&a[px][py]!=0) dfs(px,py);
    }
}
bool cmp(p a,p b){
    return a.num>b.num; 
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            if (a[i][j]) {
                tot++;
                f[tot].x=i;
                f[tot].y=j;
                f[tot].num=a[i][j];
            } 
        }
    sort(f+1,f+tot+1,cmp);
    for (int i=1;i<=tot;i++)
        if (a[f[i].x][f[i].y]) {//如果在删除过程当中没有被删除 
            ans++;
            dfs(f[i].x,f[i].y);
        } 
    printf("%d\n",ans);
    return 0;
}

```


---

## 作者：Priori_Incantatem (赞：0)

#### 题目大意：
给出一个 $n \times m$ 的矩阵，矩阵中的每一格都有一个高度  
定义山丘为若干个**高度相等且相邻的**格子组成的连通块，并满足该连通块的周边的方格的高度都比连通块内方格的高度小  
一个方格与他 上、下、左、右、左上、右上、左下、右下 方的格子相邻

我们用BFS遍历连通块，并判断这个连通块是不是山丘。  
在往旁边扩展的时候，做一个判断：如果该方格高度与之前的大，就不满足山丘条件，标记$flag=0$。若遍历到边界或者高度比之前小的方格，不会影响，直接跳过继续遍历即可

注意：如果发现该连通块不为山丘，只是标记一下。无论如何一定要将该连通块遍历完

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
const int Maxn=710,Maxm=490000+20;
const int dx[]={1,-1,0,0,-1,-1,1,1},dy[]={0,0,-1,1,-1,1,-1,1}; 
// 注意是往八个方向遍历
struct node{
	int x,y;
	node(int u,int v)
	{
		x=u,y=v;
	}
};
int a[Maxn][Maxn],vis[Maxn][Maxn];
int n,m,tot,ans;
bool flag[Maxm];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline bool check(int x,int y)
{
	return (x<1 || y<1 || x>n || y>m);
}
void bfs(int sx,int sy,int k)
{
	queue <node> q;
	vis[sx][sy]=k,flag[k]=1;
	q.push(node(sx,sy));
	while(q.size())
	{
		int x=q.front().x,y=q.front().y;
		q.pop();
		for(int i=0;i<8;++i)
		{
			int u=x+dx[i],v=y+dy[i];
			if(check(u,v) || a[u][v]<a[x][y])continue;
			if(a[u][v]>a[x][y]){flag[k]=0;continue;}
			if(vis[u][v])continue;
			vis[u][v]=k,q.push(node(u,v));
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read();
	
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	a[i][j]=read();
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	if(!vis[i][j])bfs(i,j,++tot);
	
	for(int i=1;i<=tot;++i)
	if(flag[i])++ans;
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：qrcqrc (赞：0)

蒟蒻的第一篇题解，感觉还是比较简单的，而且评测结果还算比较快的，差不多能占到所有提交人员速度的前八分之一~~noip占到前八分之一省一不就轻松到手了嘛~~。

废话不多说了，本蒟蒻的做法就是DFS，从第一个点开始赋上标记然后枚举进行搜索，搜索时八个方向都要考虑到（注意边界条件），然后只要发现周围有大于它的便将pp赋值为1（这个点必不是山丘）；只要发现周围有和它相同的（两点为邻接）且没有搜索过（没有赋过标记），再对其进行相同的搜索，然后搜索完后进行判断，只要pp为0（此点周围没有比它大的）并且确保它是此次搜索一开始的那个点（我这里通过把每个点添加上唯一的编号来区分）则说明找到一个山丘，然后再枚举下一个没有标记的点进行以上相同的操作，最后输出山丘个数就OK！
代码：```cpp
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,pp,cnt;
int a[710][710];
int vis[710][710]; 
const int dx[8]={1,-1,1,-1,1,-1,0,0};
const int dy[8]={0,0,-1,1,1,-1,1,-1};//八个方向 
inline int read(){//读入 
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
void dfs(int x,int y,int f){
	vis[x][y]=1;//此点走过了 
	for(int i=0;i<8;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>m)continue;//边界判断 
		if(a[xx][yy]>a[x][y])pp=1;//周围有比它大的，此点及邻接的不为山丘 
		if(a[xx][yy]==a[x][y]&&vis[xx][yy]!=1)dfs(xx,yy,f);//有邻接的而且没走过 
	}
	if(pp==0&&f==(x-1)*m+y)cnt++;//是一开始进来的点并且保证它和它的邻接点是山丘 
}
int main(){	
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			a[i][j]=read();
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			pp=0;
			if(vis[i][j]!=1)dfs(i,j,(i-1)*m+j);//没搜索过，进行搜索 
		}
	cout<<cnt;
	return 0;
}
```
```

---

