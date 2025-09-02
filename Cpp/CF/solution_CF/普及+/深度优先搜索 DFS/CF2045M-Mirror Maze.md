# Mirror Maze

## 题目描述

# 镜子迷宫


给定一个有\(R\)行（从北到南编号为\(1\)到\(R\)）和\(C\)列（从西到东编号为\(1\)到\(C\)）的网格。这个网格中的每个方格大小相同。位于第\(r\)行和第\(c\)列的方格表示为\((r,c)\)。每个方格要么为空，要么在方格的一条对角线上有一面镜子。每面镜子由一条线段表示。如果镜子是从西南角到东北角斜着放置的，则为\(1\)型镜子；如果是另一条对角线方向，则为\(2\)型镜子。

这些镜子遵循反射定律，即反射角等于入射角。正式地说，对于\(1\)型镜子，如果一束光线从方格的北、南、西或东方向射入，那么它将分别被反射到方格的西、东、北和南方向。类似地，对于\(2\)型镜子，如果一束光线从方格的北、南、西或东方向射入，那么它将分别被反射到方格的东、西、南和北方向。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/5f7b63f0fb5656735a6c59d6b7204c8e210c6d4c.png)你想要在网格外放置一个激光发射器，使得激光束能击中所有的镜子。有\(2\cdot(R + C)\)个可能放置激光发射器的位置：

- 从网格北侧的第\(c\)列（\(1\leq c\leq C\)），向南发射激光束；
- 从网格南侧的第\(c\)列（\(1\leq c\leq C\)），向北发射激光束；
- 从网格东侧的第\(r\)行（\(1\leq r\leq R\)），向西发射激光束；
- 从网格西侧的第\(r\)行（\(1\leq r\leq R\)），向东发射激光束。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/29c68e47c3b155b917aa2d4237fa93819b498fc4.png)确定所有可能放置激光发射器的位置，使得激光束能击中所有的镜子。

## 说明/提示

样例输入/输出 #1的解释

下面的图示展示了这个样例的一个解决方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/e36d02e4bf94a08c27da9c9fd00e9bc42d7a4647.png)样例输入/输出 #2的解释

下面的图示展示了这个样例的一个解决方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/35fe527ce8ee213e9ba2c6ba34c9f6c589c7585c.png)

## 样例 #1

### 输入

```
4 4
.//.
.\\.
.\/.
....```

### 输出

```
2
N3 W2```

## 样例 #2

### 输入

```
4 6
./..\.
.\...\
./../\
......```

### 输出

```
2
E3 S2```

## 样例 #3

### 输入

```
4 4
....
./\.
.\/.
....```

### 输出

```
0```

# 题解

## 作者：lfxxx (赞：0)

直接按照题意 dfs 即可。

那会不会遇到一个环走进去就出不来了呢？

不会，因为你将每个格子按照进入方向拆为 $4$ 个点后，一个点至多只有一个入度，这个图是一个外向基环树森林，你从一个叶子出发根本不可能走到任何一个环上。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 214;
char c[maxn][maxn];
int vis[maxn][maxn];
int n,m;
void dfs(int u,int v,int ty){//0 1 2 3 上下左右
    if(u<1||u>n||v<1||v>m) return ;
    vis[u][v]=1;
    if(c[u][v]=='/'){
        if(ty==0) ty=3;
        else if(ty==1) ty=2;
        else if(ty==2) ty=1;
        else if(ty==3) ty=0;
    }
    if(c[u][v]=='\\'){
        if(ty==0) ty=2;
        else if(ty==1) ty=3;
        else if(ty==2) ty=0;
        else if(ty==3) ty=1;
    }
    if(ty==0) dfs(u-1,v,ty);
    if(ty==1) dfs(u+1,v,ty);
    if(ty==2) dfs(u,v-1,ty);
    if(ty==3) dfs(u,v+1,ty);
}
vector< pair<char,int> > ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) cin>>c[i][j];
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        dfs(i,1,3);
        bool flag=true;
        for(int x=1;x<=n;x++)
            for(int y=1;y<=m;y++)
                if(vis[x][y]==0&&c[x][y]!='.') flag=false;
        if(flag==true) ans.push_back(make_pair('W',i));
    }
    for(int i=1;i<=m;i++){
        memset(vis,0,sizeof(vis));
        dfs(1,i,1);
        bool flag=true;
        for(int x=1;x<=n;x++)
            for(int y=1;y<=m;y++)
                if(vis[x][y]==0&&c[x][y]!='.') flag=false;
        if(flag==true) ans.push_back(make_pair('N',i));
    }
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        dfs(i,m,2);
        bool flag=true;
        for(int x=1;x<=n;x++)
            for(int y=1;y<=m;y++)
                if(vis[x][y]==0&&c[x][y]!='.') flag=false;
        if(flag==true) ans.push_back(make_pair('E',i));
    }
    for(int i=1;i<=m;i++){
        memset(vis,0,sizeof(vis));
        dfs(n,i,0);
        bool flag=true;
        for(int x=1;x<=n;x++)
            for(int y=1;y<=m;y++)
                if(vis[x][y]==0&&c[x][y]!='.') flag=false;
        if(flag==true) ans.push_back(make_pair('S',i));
    }
    cout<<ans.size()<<'\n';
    for(pair<char,int> s:ans) cout<<s.first<<s.second<<' ';
    return 0;
}
```

---

## 作者：mnlbnkk (赞：0)

# 题意
给你一个地图，这个地图由三种状态组成，空，左斜的镜片，和右斜的镜片，这里有一束激光射入迷宫，从一个地方射出迷宫，求是否能让这一束激光正好照到了所有镜片，输出所有的方案。
# 做法
其实很简单，直接模拟就可以了，首先对于每一次 DFS，记录位置和方向，然后分类讨论，如果没有遇到镜片，就照常沿着方向走，如果遇到镜片了，就分类讨论，比如讨论遇到了左斜的镜片，那么讨论这束光是从左边照过来还是右边照过来，反射应该把光反射到那个地方去。\
上述是搜索部分，接下来是思路，我们输入完了后，有两个循环，我们每一次循环都要计算，从这个地图的最上沿往下射，和这个地图的左边往右射均能否找到所有的镜片，然后记住需要去重，其实并不难，建议评绿。
# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=209;
ll n,m,a[N][N],f[N][N],num,gx[9]={0,0,-1,1},gy[9]={-1,1,0,0};
//0:left
//1:right
//2:up
//3:down
string ans[N*4][4];pair<int,int>Runout;
map<pair<ll,ll>,ll>mp;
inline string change(int x,int y)
{
	ll js;
	string tmp="";
	if(x<1) tmp="N",js=1;
	else if(y<1) tmp="W",js=0;
	else if(x>n) tmp="S",js=1;
	else tmp="E",js=0;
	string numm="";
	if(js==0)while(x){numm=char(x%10+'0')+numm;x/=10;}
	else while(y){numm=char(y%10+'0')+numm;y/=10;}
	return tmp+numm;
}
inline bool check()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!f[i][j] && a[i][j])
				return 0;
	return 1;
}
inline void output()
{
	cout<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			cout<<f[i][j];
		cout<<endl;
	}
	cout<<endl;
}
inline void dfs(int x,int y,int dir)
{
	if(x==0 || y==0 || x==n+1 || y==m+1) return Runout={x,y},void();
	f[x][y]=1;
	if(a[x][y]==0)dfs(x+gx[dir],y+gy[dir],dir);
	else 
	{
		if(a[x][y]==1)
		{
			if(dir==0) dir=3;
			else if(dir==3) dir=0;
			else if(dir==1) dir=2;
			else if(dir==2) dir=1;
		}
		else
		{
			if(dir==0) dir=2;
			else if(dir==2) dir=0;
			else if(dir==1) dir=3;
			else if(dir==3) dir=1;
		}
		dfs(x+gx[dir],y+gy[dir],dir);
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char s;
			cin>>s;
			if(s=='.') a[i][j]=0;
			else if(s=='/') a[i][j]=1;
			else a[i][j]=2;
		}
//	dfs(1,3,3);
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=m;j++)
//			cout<<f[i][j];
//		cout<<endl;
//	}
	for(int i=1;i<=n;i++)
	{
		memset(f,0,sizeof(f));
		dfs(1,i,3);
		if(check() && !mp[{0,i}] && !mp[Runout])
		{
			num++;
			ans[num][1]=change(0,i);
			ans[num][2]=change(Runout.first,Runout.second);
			mp[{0,i}]=mp[Runout]=1;
		}
		memset(f,0,sizeof(f));
		dfs(n,i,2);
		if(check() && !mp[{n+1,i}] && !mp[Runout])
		{
			num++;
			ans[num][1]=change(n+1,i);
			ans[num][2]=change(Runout.first,Runout.second);
			mp[{n+1,i}]=mp[Runout]=1;
		}
	}	
	for(int i=1;i<=n;i++)
	{
		memset(f,0,sizeof(f));
		dfs(i,1,1);
		if(check() && !mp[{i,0}] && !mp[Runout])
		{
			num++;
			ans[num][1]=change(i,0);
			ans[num][2]=change(Runout.first,Runout.second);
			mp[{i,0}]=mp[Runout]=1;
		}
		memset(f,0,sizeof(f));
		dfs(i,m,0);
		if(check() && !mp[{i,m+1}] && !mp[Runout])
		{
			num++;
			ans[num][1]=change(i,m+1);
			ans[num][2]=change(Runout.first,Runout.second);
			mp[{i,m+1}]=mp[Runout]=1;
		}
	}	
	cout<<num*2<<endl;
	for(int i=1;i<=num;i++)
		cout<<ans[i][1]<<' '<<ans[i][2]<<endl;
	return 0;
}
```

---

