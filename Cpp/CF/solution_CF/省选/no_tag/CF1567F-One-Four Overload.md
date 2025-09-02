# One-Four Overload

## 题目描述

Alice 有一个 $n$ 行 $m$ 列的矩阵，矩阵中有些单元格被标记了，而有的没有。在与矩阵边缘相邻的单元格总是没有被标记的。（当且仅当两个单元格共边时，我们称这两个单元格式相邻的）。

Alice 想往每个单元格里填入一个数字，使得该矩阵满足以下条件：
- 每个没标记的格子只能填入 $1$ 或者 $4$；
- 每个标记的格子的数字必须为**与它相邻的没有被标记的格子之和**；
- 每个标记的单元格的数字必须为 $5$ 的倍数。

Alice 是蒟蒻，做不出来，于是找你来帮忙 ~~（实际上是找的 Bob 然后让你来帮忙，但不如你直接帮 Alice）~~。

## 样例 #1

### 输入

```
5 5
.....
.XXX.
.X.X.
.XXX.
.....```

### 输出

```
YES
4 1 4 4 1
4 5 5 5 1
4 5 1 5 4
1 5 5 5 4
1 4 4 1 4```

## 样例 #2

### 输入

```
5 5
.....
.XXX.
.XXX.
.XXX.
.....```

### 输出

```
NO```

## 样例 #3

### 输入

```
3 2
..
..
..```

### 输出

```
YES
4 1
4 1
1 4```

## 样例 #4

### 输入

```
9 9
.........
.XXXXX.X.
.X...X...
.X.XXXXX.
.X.X.X.X.
.X.XXX.X.
.X.....X.
.XXXXXXX.
.........```

### 输出

```
YES
4 4 4 1 4 1 4 1 4
1 5 5 5 5 5 4 10 1
4 5 1 4 1 5 4 4 4
4 5 1 5 5 0 5 5 1
4 5 1 5 4 5 1 5 4
4 5 1 5 5 5 4 5 1
1 5 4 4 1 1 4 5 1
4 5 5 5 5 5 5 5 4
1 1 1 1 4 4 1 1 4```

# 题解

## 作者：Leap_Frog (赞：8)

### Link.
[Codeforces](https://codeforces.com/problemset/problem/1567/F)  
[Luogu](https://www.luogu.com.cn/problem/CF1567F)  

### P.S.
给个证明？

### Description.
给定一个 $n\times m$ 的矩阵，每个元素是 `X` 或 `.`。  
共两种颜色，对每个 `.` 染上一种颜色，使得所有 `X` 周围不同颜色出现次数相同。  

### Solution.
对于一个 `X` 周围有奇数个 `.` 的情况，显然直接无解。  
一个 `X` 周围有 $0$ 个 `.`，显然不用考虑。  
一个 `X` 周围有 $2$ 个 `.`，一个是黑另一个就是白，直接二分图染色即可。  
一个 `X` 周围有 $4$ 个 `.`，有点麻烦。  

结论是一个 `X` 周围有 $4$ 个 `.` 时。  
钦定 $(x-1,y)\Leftrightarrow(x,y-1)$ 和 $(x+1,y)\Leftrightarrow(x,y+1)$ 即可。  

**证明如下：**  
证明原结论，只需要证明这样构造不存在奇环即可。  
用反证法：假设有奇环。  
首先，有两种边，第一种是 $(x,y)\Leftrightarrow(x\pm1,y\pm1)$ 的边，称为斜边。  
第二种是 $(x,y)\Leftrightarrow(x\pm2,y)$ 或 $(x,y)\Leftrightarrow(x,y\pm2)$ 的边，称为直边。  
定义一个坐标的奇偶性为它横坐标的奇偶性。  
那斜边会改变一个坐标的奇偶性，而直边不会。  
因为成环，所以起点终点坐标和奇偶性相同。  
所以肯定有偶数调斜边，那就有奇数条直边。  
考虑如果存在了一条直边，那直边两点中间至少存在长度为 $3$ 的连续 `X`。  
然后最旁边的两个 `X` 周围有 $3$ 个 `.`，然后会继续往旁边扩展。  
同时两刀是不能合并成同一刀的，那样会出现一个格子是奇数。  
脑补一下这个长什么样，显然就是把原图切成了网格。  
每个网格的边缘可以通过一个空心闭合宽为 $1$ 的截。  
产生了两个，但是其实并不会影响，因为走进去不管在那边都还需要走出来。  
每条直边是一个连接两个网格的边。  
所以从一个网格走回这个网格会跨过偶数个边界。  
与环上有奇数条直边矛盾。  
所以它肯定是二分图。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int n,m,cl[250005],vv[505][505];char ch[505][505];
struct edge{int to,nxt;}e[500005];int et,head[250005];
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
#define ID(i,j) ((i-1)*m+(j))
inline void dfs(int x)
{
	for(int i=head[x];i;i=e[i].nxt)
		if(!~cl[e[i].to]) cl[e[i].to]=cl[x]^1,dfs(e[i].to);
		else if(!(cl[x]^cl[e[i].to])) puts("NO"),exit(0);
}
int main()
{
	read(n,m);for(int i=1;i<=n;i++) scanf("%s",ch[i]+1);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(ch[i][j]=='X')
	{
		vector<int>v;int cnt=0;for(int k=0;k<4;k++)
		{
			int nx=i+dx[k],ny=j+dy[k];
			if(nx<1||nx>n||ny<1||ny>m) continue;
			if(ch[nx][ny]=='.') cnt++,v.push_back(ID(nx,ny));
		}
		if(cnt&1) return puts("NO"),0;else vv[i][j]=cnt/2*5;
		for(int i=0;i<(int)v.size();i+=2) adde(v[i],v[i+1]),adde(v[i+1],v[i]);
	}
	memset(cl,-1,sizeof(cl));for(int i=1;i<=n*m;i++) if(!~cl[i]) cl[i]=0,dfs(i);
	puts("YES");for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
		printf("%d%c",ch[i][j]=='X'?vv[i][j]:cl[ID(i,j)]?4:1,j==m?'\n':' ');
	return 0;
}
```

---

## 作者：installb (赞：4)

这里首先把与某个被标记的格子**相邻的未被标记的格子**数量记作这个格子的**度数**。我们分别考虑度数为 $0$ 到 $4$ 的格子。

- 对于度数为 $0$ 的格子，必定填 $0$。
- 对于度数为 $1$ 或 $3$ 的格子，很明显只要这样的格子存在，就必然无解。
- 对于度数为 $2$ 的格子，与它相邻的两个未被标记的格子一个是 $1$，另外一个是 $4$。
- 对于度数为 $4$ 的格子，与它相邻的四个未被标记的格子两个是 $1$，另外两个是 $4$。

如果没有度数为 $4$ 的格子，我们可以把每个格子当作一个点，然后对于所有度数为 $2$ 的格子，把与它相邻的两个未被标记的格子连边，跑一遍二分图染色，直接做就行了。

这里我们可以发现，这样连出来的图**一定是二分图**。尝试反证，假设我们连出来了一个奇环，首先环上会出现两类边，第一类是直着连的，例如连接 $(x,y)$ 和 $(x+2,y)$，第二类是连接对角线的，例如连接 $(x,y)$ 和 $(x+1,y+1)$。第二类边**一定会出现偶数个，否则连不成环**，因此这里只需要考虑第一类边。

环在网格上会围成一个简单多边形。对于每个第一类边，都会对应一个标记过的格子，并且这个格子在**多边形内外各有一个**相邻的标记过的格子。根据题目已知信息，每个被标记的格子度数都是偶数，因此每个连通块中，被标记的格子对应的点可以形成一个**欧拉回路**。这个欧拉回路一定是会**进出这个多边形若干次**，假定这个回路从多边形外出发，那么它最终一定会回到多边形外，反之亦然。但是如果第一类边只有奇数个，那么在多边形**上**的点也只有奇数个，这里我们**暂时先假设这些点处于同一连通块**。但是由于**每个在多边形上的点只能经过一次**，因此从多边形外出发，无法回到多边形外，欧拉回路不存在，与实际情况矛盾。所以没有奇环。

上面的证明假设了这些点处于同一连通块的情况，还需要考虑这些点处于不同连通块的情况，不过其实都是一样的，每个连通块会用掉偶数个点，本质还是奇偶性不满足。

![CF1567F_proof.png](https://i.loli.net/2021/09/09/E72AR3nSBudjz6U.png)

接下来考虑把度数为 $4$ 的格子加入，总共有两种情况，图 $1$ 的对位填的数相同和图 $2$ 的邻位填的数相同。

![CF1567F.png](https://i.loli.net/2021/09/09/zUe2Tacypx4u7ho.png)

这样看起来不太可做，但实际上，加上度数为 $4$ 的格子之后还是一定有解，并且一定存在一种方案，使得所有度数为 $4$ 的格子周围的格子都以图 $1$ 的方式（即相对的两个格子数字相同）填数。这样我们就可以像下图方式一样连边。

![CF1567F_2.png](https://i.loli.net/2021/09/09/Acm9DJnIbd6o7G8.png)

连完之后，同样可以证明，最后的图还是一个二分图。因此这样连边虽然让限制更加严格了，但是仍然保证能求出一组解。

说到这里也差不多了，下面是代码：  
写得比较丑。。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ec = 0,to[1000005],nxt[1000005],hed[250005],col[250005];
ll n,m,flg;
char ch[505][505];
void add_edge(ll f,ll t){
	++ ec; to[ec] = t; nxt[ec] = hed[f]; hed[f] = ec;
	++ ec; to[ec] = f; nxt[ec] = hed[t]; hed[t] = ec;
}

void dfs(ll u){
	for(ll v,i = hed[u];i;i = nxt[i]){
		v = to[i];
		if(col[v]) continue;
		col[v] = 5 - col[u];
		dfs(v);
	}
}

ll get_id(ll x,ll y){
	return (x - 1) * m + y;
}

int main(){
	ios::sync_with_stdio(false);
	flg = 1;
	cin >> n >> m;
	for(ll i = 1;i <= n;i ++){
		for(ll j = 1;j <= m;j ++){
			cin >> ch[i][j];
		}
	}
	for(ll i = 2;i < n;i ++){
		for(ll tmp,tu,tv,j = 2;j < m;j ++){
			if(ch[i][j] != 'X') continue;
			tmp = (ch[i - 1][j] == 'X') + (ch[i][j - 1] == 'X') + (ch[i + 1][j] == 'X') + (ch[i][j + 1] == 'X');
			if(tmp == 1 || tmp == 3) flg = 0;
			if(tmp == 0){
				add_edge(get_id(i - 1,j),get_id(i,j - 1));
				add_edge(get_id(i - 1,j),get_id(i,j + 1));
				add_edge(get_id(i + 1,j),get_id(i,j - 1));
				add_edge(get_id(i + 1,j),get_id(i,j + 1));
			}
			if(tmp == 2){
				tu = tv = -1;
				if(ch[i - 1][j] == '.'){
					if(tu == -1) tu = get_id(i - 1,j);
					else tv = get_id(i - 1,j);
				}
				if(ch[i][j - 1] == '.'){
					if(tu == -1) tu = get_id(i,j - 1);
					else tv = get_id(i,j - 1);
				}
				if(ch[i + 1][j] == '.'){
					if(tu == -1) tu = get_id(i + 1,j);
					else tv = get_id(i + 1,j);
				}
				if(ch[i][j + 1] == '.'){
					if(tu == -1) tu = get_id(i,j + 1);
					else tv = get_id(i,j + 1);
				}
				add_edge(tu,tv);
			}
		}
	}
	if(!flg){
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n";
	for(ll u,i = 1;i <= n;i ++){
		for(ll j = 1;j <= m;j ++){
			if(ch[i][j] == 'X') continue;
			u = get_id(i,j);
			if(!col[u]){
				col[u] = 1;
				dfs(u);
			}
		}
	}
	for(ll i = 1;i <= n;i ++){
		for(ll tmp,j = 1;j <= m;j ++){
			tmp = (ch[i - 1][j] == 'X') + (ch[i][j - 1] == 'X') + (ch[i + 1][j] == 'X') + (ch[i][j + 1] == 'X');
			if(ch[i][j] == 'X') cout << ((4 - tmp) >> 1) * 5;
			else cout << col[get_id(i,j)];
			cout << (j == m ? '\n' : ' ');
		}
	}
	return 0;
}
```

---

## 作者：云浅知处 (赞：3)

[题目 Link](https://codeforces.com/contest/1567/problem/F)

首先是一些显而易见的事实：

- 如果一个 `X` 旁边有奇数个 `.` 那么肯定无解
- 如果一个 `X` 旁边有偶数个 `.`，那么必然是一半 $1$ 一半 $4$。

我们先考虑 $2$ 个 `.` 的情形：此时这两个 `.` 上必然是一个 $1$ 一个 $4$。

此时如果不存在一个 `X` 旁边全是 `.`，那么我们就可以直接连边建图，然后用简单的 $\text{dfs}$ 过掉这个题。

但如果 `X` 旁边全是 `.` 那么我们发现可能的连边方式有三种，如果一一枚举，那么复杂度将会是指数级的。

然后我场上的思路就到这里了。。

其实解决办法也很简单：我们直接连接「左边和上边」以及「右边和下边」，然后用之前的办法就行。

正确性的证明 CF 网友告诉我 [Editorial](https://codeforces.com/blog/entry/94581) 里面写的有，这里就不再放了（

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>

#define int long long
const int MN=1005*1005;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

vector<int>G[MN];
int n,m,N;
char str[1505][1505];
int a[1505][1505],id[1505][1505];
int memx[MN],memy[MN],ans[MN];
bool vis[MN];

int dx[]={0,1,0,-1};//dX 女装
int dy[]={1,0,-1,0};

vector<int>v;

int val(int x,int y){return id[x][y];}
int geti(int x){return memx[x];}
int getj(int x){return memy[x];}

void adde(int x,int y,int xx,int yy){
    G[val(x,y)].push_back(id[xx][yy]);
    G[val(xx,yy)].push_back(id[x][y]);
}

bool dfs(int u){
    v.push_back(u);vis[u]=1;
    for(int i=0;i<G[u].size();i++){
        int to=G[u][i];
        if(vis[to]&&ans[to]==ans[u])return 0;
        if(vis[to])continue;
        ans[to]=ans[u]^1;
        if(!dfs(to))return 0;
    }
    return 1;
}

signed main(void){

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>str[i][j];
            if(str[i][j]=='.')id[i][j]=++N,memx[N]=i,memy[N]=j;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(str[i][j]!='X'){N++;continue;}
            v.clear();
            for(int k=0;k<4;k++){
                int I=i+dx[k],J=j+dy[k];
                if(I<=0||I>n||J<=0||J>m)continue;
                if(str[I][J]=='.')v.push_back(id[I][J]);
            }
            if((int)(v.size())&1){puts("NO");return 0;}
            if(v.size()==4)adde(i-1,j,i,j-1),adde(i+1,j,i,j+1);
            if(v.size()==2)G[v[0]].push_back(v[1]),G[v[1]].push_back(v[0]);
            a[i][j]=(int)(v.size())/2*5;
        }
    }

    for(int i=1;i<=N;i++){
        if(!vis[i]){
            v.clear();ans[i]=1;
            if(dfs(i))continue;
            for(int i=0;i<v.size();i++)vis[v[i]]=0,ans[v[i]]=0;
            v.clear();ans[i]=0;
            if(!dfs(i)){puts("NO");return 0;}
        }
    }
     
    puts("YES");
    for(int i=1;i<=N;i++)a[memx[i]][memy[i]]=((ans[i]==1)?4:1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)cout<<a[i][j]<<" ";puts("");
    }

    return 0;
}
```

---

## 作者：262620zzj (赞：1)

# 做法

显然，每个被标记的格子，如果周围有 1 或 3 个 `.` 那么必定无解；如果周围有 2 个 `.`，那么一个 1 一个 4，如果周围有 4 个 `.` 那么两个 1 两个 4。

我们可以先判断是否有解。然后不难发现对于每个 `X` 周围有 2 个 `.`  的话可以把他们连一条边，周围有 4 个 `.` 的话可以连两条斜边，类似于 $(i-1,j)\leftrightarrow (i,j-1),(i+1,j)\leftrightarrow (i,j+1)$，一条边连接的两个格子相加等于 5，也就是两个格子互补。根据这个限制填完所有格子就可以了。

# 证明

形如 $(i-1,j)\leftrightarrow (i+1,j)$ 的边称为“直边”，形如 $(i-1,j)\leftrightarrow (i,j-1)$ 的边称为“斜边”。

这样做为什么不会产生奇环呢，首先一个环斜边的个数必然是偶数。因为斜边连接的格子，横坐标奇偶性会变，而直边连接的格子横坐标奇偶性不变。如果斜边数量为奇数则无法从起点绕回终点。

所以只需证直边个数也为偶数。我们来看看直边形成的条件，直边出现必然有三个 `X` 连续出现。

如果这个图有解，那么所有 `X` 度数为偶数，它们构成了若干欧拉回路，欧拉回路经过每条边恰好一次。欧拉回路穿过这个环只能从直边穿过，且欧拉回路必然穿过这个环偶数次，与奇数条直边矛盾。故这样的图不存在奇环。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>void read(T &x){
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x*=f;
}
template<typename T,typename ...Args>
void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=505;
char mp[N][N];
int n,m,ans[N*N];
struct edge{int to,nx;}e[4*N*N];
int head[N*N],tot;
int get(int x,int y){return (x-1)*m+y;}
void add_edge(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void paint(int u){
	for(int i=head[u];~i;i=e[i].nx){
		int v=e[i].to;
		if(ans[v]==-1){
			ans[v]=5-ans[u];
			paint(v);
		}
	}
}
int main(){
	srand(time(0));
	memset(ans,-1,sizeof(ans));
	memset(head,-1,sizeof(head));
	read(n,m);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>mp[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(mp[i][j]=='X'){
			int tim=0,a=0,b=0;
			if(mp[i-1][j]=='.')tim++,a=get(i-1,j);;
			if(mp[i+1][j]=='.')tim++,a?b=get(i+1,j):a=get(i+1,j);
			if(mp[i][j-1]=='.')tim++,a?b=get(i,j-1):a=get(i,j-1);
			if(mp[i][j+1]=='.')tim++,b=get(i,j+1);
			if(tim%2){
				puts("NO");
				return 0;
			}
			ans[get(i,j)]=tim*5/2;
			if(tim==2){
				add_edge(a,b);
				add_edge(b,a);
			}
			if(tim==4){
				add_edge(get(i-1,j),get(i,j-1));
				add_edge(get(i,j-1),get(i-1,j));
				add_edge(get(i+1,j),get(i,j+1));
				add_edge(get(i,j+1),get(i+1,j));
			}
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(ans[get(i,j)]==-1){
			ans[get(i,j)]=rand()&1?1:4;
			paint(get(i,j));
		}
	}
	puts("YES");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)printf("%d ",ans[get(i,j)]);
		printf("\n");
	}
	return 0;
}
```

---

