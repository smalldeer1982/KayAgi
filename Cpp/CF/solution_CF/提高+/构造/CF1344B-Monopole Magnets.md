# Monopole Magnets

## 题目描述

**单极磁铁**，顾名思义，就是只有一个磁极（N 或 S）的磁铁，~~他们在实际生活中是不存在的，不过……不要在意那些细节。~~

我们有一个 $n$ 行 $m$ 列的方格图，要在里面放一些单极磁铁，你可以随便放置，甚至把多个磁铁放在同一个格子里。

单极磁铁的**吸引**是这么定义的：任选一个 N 极磁铁和一个 S 极磁铁，如果它们两个**恰好处于同一行或同一列中**，那 N 极磁铁会向**靠近 S 极磁铁**的方向**前进一格**。当然，如果它们两个处于同一个格子，什么也不会发生。注意 **S 极磁铁的位置是永远不会变化的**。

这个方格图里的每一个格子都涂成了**黑色**或**白色**。磁铁的放置必须要**遵守以下规则**：

1. 每行每列都必须至少有一个 S 极磁铁。
2. 对于每个黑色格子，必须有某个 N 极磁铁通过一系列的吸引操作经过它。
3. 对于每个白色格子，无论 N 极磁铁的位置怎样变化，都不能经过它。

现在我们想知道：要满足以上三条规则，至少要放几个 N  极磁铁。如果无论怎么放都不能满足规则，请输出 $-1$。

## 样例 #1

### 输入

```
3 3
.#.
###
##.```

### 输出

```
1```

## 样例 #2

### 输入

```
4 2
##
.#
.#
##```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 5
....#
####.
.###.
.#...```

### 输出

```
2```

## 样例 #4

### 输入

```
2 1
.
#```

### 输出

```
-1```

## 样例 #5

### 输入

```
3 5
.....
.....
.....```

### 输出

```
0```

# 题解

## 作者：Priori_Incantatem (赞：2)

首先我们考虑合法的地图需要满足的条件

1. 在任意一行或一列中，不存在两个不相邻的黑色方块 $A,B$。因为，根据题目中规则，每行每列上都至少有一个南极磁铁。所以不管这个南极磁铁在那里，都会有至少一个北极磁铁可以到达 $A,B$ 之间的白方块上。例如，样例 $2$ 就是不合法的
2. 对于一个方格 $(x,y)$，只有当 $(x,y)$ 为黑格，或者它所在行列（包括 $(x,y)$）上没有黑格时，才能在 $(x,y)$ 上放南极磁铁。因为不能把北极磁铁吸到白方格上

在确定地图合法后，因为每个黑格上都可以放南极磁铁，所以只需要在每个黑色连通块中放一个北极磁铁。那么，最后的答案就是黑色连通块的个数啦

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int Maxn=1010,inf=0x3f3f3f3f;
const int dx[]={1,-1,0,0},dy[]={0,0,-1,1};
bool vis[Maxn][Maxn],a[Maxn][Maxn];
bool r[Maxn],c[Maxn],flag[Maxn][2];
int n,m,ans;
inline bool check(int x,int y)
{
	return (x<1 || y<1 || x>n || y>m || vis[x][y] || !a[x][y]);
}
void dfs(int x,int y)
{
	vis[x][y]=1;
	for(int i=0;i<4;++i)
	{
		int u=x+dx[i],v=y+dy[i];
		if(check(u,v))continue;
		dfs(u,v);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		char s[Maxn];
		scanf("%s",s+1);
		for(int j=1;j<=m;++j)
		if(s[j]=='#')
		{
			a[i][j]=1;
			r[i]=c[j]=1;
		}
	}
	for(int i=1;i<=n;++i)
	{
		int pos=0;
		for(int j=1;j<=m;++j)
		if(a[i][j]){pos=j;break;}
		if(!pos)continue;
		for(int j=pos+2;j<=m;++j)
		if(a[i][j] && !a[i][j-1])
		{puts("-1");return 0;}
	}
	for(int j=1;j<=m;++j)
	{
		int pos=0;
		for(int i=1;i<=n;++i)
		if(a[i][j]){pos=i;break;}
		if(!pos)continue;
		for(int i=pos+2;i<=n;++i)
		if(a[i][j] && !a[i-1][j])
		{puts("-1");return 0;}
	}
	
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	if(a[i][j] || (!r[i] && !c[j]))
	flag[i][0]=flag[j][1]=1;
	for(int i=1;i<=n;++i)
	if(!flag[i][0]){puts("-1");return 0;}
	for(int i=1;i<=m;++i)
	if(!flag[i][1]){puts("-1");return 0;}
	
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	{
		if(vis[i][j] || !a[i][j])continue;
		dfs(i,j),++ans;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty  : 2000}$
---
### 解题思路：

挺有趣的题。

考虑某一列或者某一排。发现如果出现至少两段不相交的黑色段，则一定无解。这是因为这一列中一定有至少一个 $\text{S}$ 磁铁，则无论这个磁铁放到哪个位置，都不可能出现不连通的黑色段。这个命题的正确性是显然的。

还有一种无解的情况是 $\text{S}$ 无处安放导致的。对于某一排或者某一列，如果当前排或者列上没有任何一个黑色，而且无论这个放在哪里都会使得当前地方的格子可以被到达，则也会导致无解。

对于其它情况，可以给出以下构造方案使其有解。将一个 $\text{N
}$ 放置在一个黑色连通块中的任意一个位置上，并将所有的黑色块上都放置上 $\text{S}$ 磁铁即可。

这样的 $\text{N}$ 磁铁数量就是黑色联通块的数量，容易发现这样一定有最少的 $\text{N}$ 磁铁放置。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n,m,cnt,a[1005][1005],v[1005][1005],flag,f_1[1005],f_2[1005],fr1,fr2;
int dx[5]={0,0,1,-1};
int dy[5]={1,-1,0,0};
char get(){
	char c=getchar();
	while(c=='\n'||c==' '||c=='\r')c=getchar();
	return c;
}
void dfs(int x,int y){
	if(x==0||x==n+1||y==0||y==m+1)return;
	v[x][y]=1;
	for(int i=0;i<=3;i++){
		if(v[x+dx[i]][y+dy[i]]==0&&a[x+dx[i]][y+dy[i]]==1)
		dfs(x+dx[i],y+dy[i]);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		if(get()=='#'){
			a[i][j]=1;
			f_1[i]=1;
			f_2[j]=1;
		}
		else a[i][j]=0;
	}
	fr1=fr2=1;
	for(int i=1;i<=n;i++)fr1&=f_1[i];
	for(int j=1;j<=m;j++)fr2&=f_2[j];
	if(fr1^fr2)flag=1;
	for(int i=1;i<=n;i++){
		cnt=0;
		for(int j=1;j<=m;j++)
		if(a[i][j]==1&&a[i][j-1]==0)
		cnt++;
		if(cnt>1)flag=1;
	}
	for(int j=1;j<=m;j++){
		cnt=0;
		for(int i=1;i<=n;i++)
		if(a[i][j]==1&&a[i-1][j]==0)
		cnt++;
		if(cnt>1)flag=1;
	}
	if(flag==1){
		printf("-1\n");
		return 0;
	}
	
	cnt=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(a[i][j]==1&&v[i][j]==0){
		cnt++;
		dfs(i,j);
	}
	printf("%d\n",cnt);
	return 0;
}
```


---

## 作者：_Lazy_zhr_ (赞：0)

首先，我们要判断给出的地图是否合法。

对于每一行和每一列，都要满足必须有黑格子且是连续的。特别的，如果有一个全是白格子的行和一个全是白格子的列相交，那这一行和这一列也是合法的。

判完后就是相对简单的统计连通块个数了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mx[4]={-1,1,0,0};
const int my[4]={0,0,-1,1};
int n,m,ans;
char f[1005][1005];
queue< pair<int,int> > q;
bool r[1005],c[1005];
void solve(){
	int s; 
	bool x;
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		cin>>f[i][j];
		if(f[i][j]=='#') r[i]=true,c[j]=true;
	}
	for(int i=1;i<=n;i++){
		x=false,s=0;
		for(int j=1;j<=m;j++) if(!r[i]&&!c[j]){
			x=true;
			break;
		} if(x) continue;
		x=false;
		for(int j=1;j<=m;j++) if(f[i][j]=='#'){
			x=true;
			if(s&&j-s>1){
				cout<<"-1\n";
				return ;
			} s=j;
		} if(!x){
			cout<<"-1\n";
			return ;
		}
	} for(int j=1;j<=m;j++){
		x=false,s=0;
		for(int i=1;i<=n;i++) if(!r[i]&&!c[j]){
			x=true;
			break;
		} if(x) continue;
		x=false;
		for(int i=1;i<=n;i++) if(f[i][j]=='#'){
			x=true;
			if(s&&i-s>1){
				cout<<"-1\n";
				return ;
			} s=i;
		} if(!x){
			cout<<"-1\n";
			return ;
		}
	}//判图。
  for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(f[i][j]=='#'){
		ans++;
		f[i][j]='.';
		q.push({i,j});
		while(q.size()){
			int fx=q.front().first,fy=q.front().second;
			q.pop();
			for(int k=0;k<4;k++){
				int nx=fx+mx[k],ny=fy+my[k];
				if(nx>0&&nx<=n&&ny>0&&ny<=m&&f[nx][ny]=='#'){
					q.push({nx,ny});
					f[nx][ny]='.';
				}
			}
		}
	}//遍历图并统计连通块。
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/1344/304504147)

---

## 作者：Jorisy (赞：0)

随机开题时因为没想全 corner cases，被罚了若干发，遂被机房同学嘲讽了。

首先贪心地，对于每个连通块我们必然只会放一个 N 极磁铁，因为多放的那一个的路径必然包含于原来的那个。因此对于合法的答案就是连通块数量。

其次，为了每行每列至少一个 S 极磁铁，对于全白的行（列），我们一定会把 S 极磁铁放在所在列（行）也全白的位置，因为黑的地方 N 极磁铁走过时，可能会被其吸引。

接着，我们考虑每个黑色连通块内的情况。不难发现，我们在连通块内四周围一圈就可以使得 N 极磁铁自由走动。与此同时，也不难想到，连通块不能是凹多边形（因为磁铁会越过凹下去的那一部分）。

进一步地，如果一行（列）存在多个连续的黑色块，就不合法（因为连通块间可以穿过）。

于是就做完了。

我写的太丑陋了，所以就不放代码了。

---

## 作者：pzc2004 (赞：0)

# 题目分析
N表示北极，S表示南极。  
可以发现，N最小的数量就等于黑色方块的连通块数，所以只需要考虑判断-1的情况。  
我们可以先考虑要求1：每行每列都得有至少一个S。所以如果有任何一行或一列放不了一个S，那么就得输出-1，否则就是可以的。  
如果一个格子是黑色的，那么一定会有N到达这个格子。因此S的同行同列不能有其他段黑色格子。  
看图感受一下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/ny7jexe5.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/y5k084sc.png)  
因此，我们只需要用前缀和预处理一下对于 $(i,j)$，从行首、行位、列首、列尾各有多少块黑色方块，然后判断一下即可。
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1005
int n,m,ans,h1[N][N],l1[N][N],h2[N][N],l2[N][N];
char s[N][N];
bool b[N][N];
inline void dfs(int x,int y)//dfs找联通快
{
	b[x][y]=1;
	if(s[x][y-1]=='#' && !b[x][y-1])dfs(x,y-1);
	if(s[x][y+1]=='#' && !b[x][y+1])dfs(x,y+1);
	if(s[x-1][y]=='#' && !b[x-1][y])dfs(x-1,y);
	if(s[x+1][y]=='#' && !b[x+1][y])dfs(x+1,y);
}
signed main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='#' && !b[i][j])dfs(i,j),++ans;//联通快
			if(s[i][j]=='#' && s[i-1][j]!='#')l1[i][j]=l1[i-1][j]+1;else l1[i][j]=l1[i-1][j];//预处理
			if(s[i][j]=='#' && s[i][j-1]!='#')h1[i][j]=h1[i][j-1]+1;else h1[i][j]=h1[i][j-1];
		}
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=m;j>=1;j--)
		{
			if(s[i][j]=='#' && s[i+1][j]!='#')l2[i][j]=l2[i+1][j]+1;else l2[i][j]=l2[i+1][j];//预处理
			if(s[i][j]=='#' && s[i][j+1]!='#')h2[i][j]=h2[i][j+1]+1;else h2[i][j]=h2[i][j+1];
		}
	}
	for(int i=1;i<=n;i++)
	{
		bool bbb=0;
		for(int j=1;j<=m;j++)
		{
			if(h1[i][m]==h1[i][j] && h2[i][1]==h2[i][j] && l1[n][j]==l1[i][j] && l2[1][j]==l2[i][j]){bbb=1;break;}
		}
		if(!bbb){printf("-1");return 0;}//放不了就输-1
	}
	for(int j=1;j<=m;j++)
	{
		bool bbb=0;
		for(int i=1;i<=n;i++)
		{
			if(h1[i][m]==h1[i][j] && h2[i][1]==h2[i][j] && l1[n][j]==l1[i][j] && l2[1][j]==l2[i][j]){bbb=1;break;}
		}
		if(!bbb){printf("-1");return 0;}//放不了就输-1
	}
	printf("%d",ans);//输出答案
	return 0;
}
```

---

