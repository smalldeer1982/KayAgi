# Inna and Dima

## 题目描述

Inna and Dima bought a table of size $ n×m $ in the shop. Each cell of the table contains a single letter: "D", "I", "M", "A".

Inna loves Dima, so she wants to go through his name as many times as possible as she moves through the table. For that, Inna acts as follows:

1. initially, Inna chooses some cell of the table where letter "D" is written;
2. then Inna can move to some side-adjacent table cell that contains letter "I"; then from this cell she can go to one of the side-adjacent table cells that contains the written letter "M"; then she can go to a side-adjacent cell that contains letter "A". Then Inna assumes that she has gone through her sweetheart's name;
3. Inna's next move can be going to one of the side-adjacent table cells that contains letter "D" and then walk on through name DIMA in the similar manner. Inna never skips a letter. So, from the letter "D" she always goes to the letter "I", from the letter "I" she always goes the to letter "M", from the letter "M" she always goes to the letter "A", and from the letter "A" she always goes to the letter "D".

Depending on the choice of the initial table cell, Inna can go through name DIMA either an infinite number of times or some positive finite number of times or she can't go through his name once. Help Inna find out what maximum number of times she can go through name DIMA.

## 说明/提示

Notes to the samples:

In the first test sample, Inna cannot go through name DIMA a single time.

In the second test sample, Inna can go through the infinite number of words DIMA. For that, she should move in the clockwise direction starting from the lower right corner.

In the third test sample the best strategy is to start from the cell in the upper left corner of the table. Starting from this cell, Inna can go through name DIMA four times.

## 样例 #1

### 输入

```
1 2
DI
```

### 输出

```
Poor Dima!
```

## 样例 #2

### 输入

```
2 2
MA
ID
```

### 输出

```
Poor Inna!
```

## 样例 #3

### 输入

```
5 5
DIMAD
DIMAI
DIMAM
DDMAA
AAMID
```

### 输出

```
4
```

# 题解

## 作者：Komorebi_03 (赞：3)

在找概率论的题目时发现了这道~~看似很水但让我调了半个下午的题~~。
## 思路
题意可以简单概括为在一张 $n \times m$ 的图上，你只能按顺序从 $D$ 走到 $I$ 再走到 $M$ 再走到 $A$，再从 $A$ 走向 $D$ 这样一直循环下去，求最多能走几组 DIMA。

考虑 DFS 找最长路。

那么如何建图？

先看数据范围 $1 \le n,m \le 10^3$，可以考虑把图上每个点标号，如果满足前进条件，就从 $i$ 号点向 $j$ 号点连一条有向边，这样经过处理后可以得到一个非负的有向有环图。

在建图过程中可以发现图中存在环，所以需要判环，如果有环则说明他可以无限走。

```cpp
//By:Komorebi_03
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M = 1e3+10;
const int N = 1e6+10;
int n,m,ans,e_cnt,dis[N],head[N<<2],mp[M][M];
int nx[5]={0,0,1,-1};
int ny[5]={1,-1,0,0};
bool flag,vis[N];
char s[M][M];
struct edge{
    int v;
    int nxt;
}e[N<<2];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

void add(int u,int v)
{
    e[e_cnt].v=v;
    e[e_cnt].nxt=head[u];
    head[u]=e_cnt++;
}

void build_mp()
{
    int js=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            mp[i][j]=++js;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            for (int k=0;k<4;k++)
            {
                int x=i+nx[k];
                int y=j+ny[k];
                if(x<1 || x>n || y<1 || y>m)
                    continue;
                //D-->I  I-->M  M-->A  A-->D
                if(s[i][j]=='D' && s[x][y]=='I')
                    add(mp[i][j],mp[x][y]);
                if(s[i][j]=='I' && s[x][y]=='M')
                    add(mp[i][j],mp[x][y]);
                if(s[i][j]=='M' && s[x][y]=='A')
                    add(mp[i][j],mp[x][y]);
                if(s[i][j]=='A' && s[x][y]=='D')
                    add(mp[i][j],mp[x][y]);
            }
        }
    }
}

void DFS(int u)
{
    if(dis[u])
        return ;
    dis[u]=1;
    vis[u]=true;
    for (int i=head[u];i!=-1;i=e[i].nxt)
    {
        int v=e[i].v;
        if(vis[v])
        {
            flag=true;
            vis[u]=false;
            return ;
        }
        DFS(v);
        if(flag)
        {
            vis[u]=false;
            return ;
        }
        dis[u]=max(dis[u],dis[v]+1);
    }
    vis[u]=false;
}

int main()
{
    memset(head,-1,sizeof head);
    n=read();
    m=read();
    for (int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    build_mp();//建图
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            if(s[i][j]!='D')
                continue;
            DFS(mp[i][j]);//对每个 D 点搜索 
            if(flag)//有环的情况 
            {
                puts("Poor Inna!");
                exit(0);
            }
            ans=max(ans,dis[mp[i][j]]);
            //注意，这里统计的是走了多少步，所以最后输出的时候要除4 
        }
    }
    ans/=4;
    if(ans)
        cout<<ans<<"\n";
    else
        puts("Poor Dima!");
    return 0;
    //Amireux_35
}
```


---

## 作者：Constant (赞：3)

# 题意简述：
以地图上每个为D的格子为起点，按照DIMA的顺序依次上下左右走，求出最多能走完多少个完整的DIMA名字。

# Solution:

不是我说，这真是一道好题。

看见题面最长路径，还让我们判断有没有无限走下去的情况，这显然给了我们暗示，可以 $SPFA$ 跑最长路。

如何建图呢？由于每次只能按照DIMA的顺序行走，有非常明显的行走过程，于是我们遍历一遍整个地图，对于每个格子，判断是否能走到旁边的格子，如果能走到，就从当前格子向旁边格子连一条边。

但如何知道当前格子代表点的编号呢，这里有一个小技巧，用行列进行编号，按从上到下，从左往右的顺序数，数到第几个，编号就是对应的数的个数。一般地，在 $N$ 行 $M$ 列的地图中，有一个坐标为 $(i,j)$ 的点，那么编号就是 $(i-1)m+j$ 。

解决了建图的问题，自然就可以跑最长路了，如果出现环，那么就代表出现了永远走下去的情况，判断即可，但这样有一个问题，跑最长路时每次都需要memset，时间复杂度就是 $O(N^3)$ 的，对于本题数据 $N,M=10^3$ ，是过不了的。

用一个简单的方法就可以解决本题，就是 $DFS$ ，跑最长路改为 $DFS$ 后，用一个数组记录当前点是否访问过，如果访问到一个已经访问的点，那么说明存在环。

最后找出每个起点，用 $DFS$ 搜索即可，时间复杂度 $O(N^2)$ 。

好了，这道直奔主题的 $DFS$ 题目就这样结束了，下面上代码。

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int bj,ans,path[N],c,st[N],cnt[N],vis[N],que[N],num,n,m,first[N],nex[4*N],f[1005][1005],v[4*N];
int dt[4][4]={{1,0},{0,1},{-1,0},{0,-1}};
char a[1005][1005];
int S(char ch) //这是一个小技巧，转化成数字方便处理 
{
	if(ch=='D') return 1;
	if(ch=='I') return 2;
	if(ch=='M') return 3;
	if(ch=='A') return 4;
}
int F(int x,int y)
{
	return (x-1)*m+y;
}
void Add(int s,int e)
{
	nex[++num]=first[s];
	first[s]=num;
	v[num]=e;
}
int pd(int x)
{
	if(x==4) return 1;
	else return x+1;
}
void dfs(int s) 
{
    if(path[s]) return;
    vis[s]=1;
    path[s]=1;
    for(int i=first[s];i!=-1;i=nex[i]) 
	{
        int j=v[i];
        if(vis[j]) 
		{
			bj=1;
			vis[s]=0;
			return;
		}
        dfs(j);
        if(bj==1)
		{
			vis[s]=0;
			return;
		}
        path[s]=max(path[s],path[j]+1);
    }
    vis[s]=0;
}
int main()
{
	memset(first,-1,sizeof(first));
	cin>>n>>m;
	getchar();
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		for(int j=0;j<=strlen(a[i])-1;j++)
		{
			f[i][j+1]=S(a[i][j]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=0;k<=3;k++) 
			{
                int dx=i+dt[k][0];
                int dy=j+dt[k][1];
                if(dx<1||dx>n||dy<1||dy>m) continue;              
                if(pd(f[i][j])==f[dx][dy]) Add(F(i,j),F(dx,dy));
            }
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(f[i][j]!=1) continue;
			dfs(F(i,j));
		    if(bj==1)
		    {
			   cout<<"Poor Inna!";
			   return 0;
		    }
		    if(path[F(i,j)]>ans) ans=path[F(i,j)];
		}	
	}
	ans=ans/4;//不要忘记除以4！ 
    if(ans!=0) printf("%d",ans);
    else printf("Poor Dima!");
	return 0;
}
```


---

## 作者：zhouzihang1 (赞：1)

# [CF374C Inna and Dima](https://www.luogu.com.cn/problem/CF374C) 题解

## 题意

给出 $n$ 行 $m$ 列的地图，地图只包含 $\texttt{DIMA}$ 四个字符。

从所有的字符 $\texttt{D}$ 开始，以 $\texttt{D} \to \texttt{I} \to \texttt{M} \to \texttt{A} \to \texttt{D}$ 的顺序行走。

问能否走出一个完整的 $\texttt{DIMA}$，或能否走无限个 $\texttt{DIMA}$，或能走几个 $\texttt{DIMA}$。

## 思路

这显然是一个图论题，求一张图的最长路。

如果可以走无限个，说明这张图中有环且换种包含了 $2$ 个及以上的 $\texttt{DIMA}$ 首尾相连。

否则只需记录沿 $\texttt{D}$ 开始，以 $\texttt{D} \to \texttt{I} \to \texttt{M} \to \texttt{A} \to \texttt{D}$ 的顺序走的最长路为长度为 $L$，答案即为 $\lfloor \frac{L}{4} \rfloor$。

对于最长路，可以使用 toposort 或 dfs 解决，这里以 dfs 为例。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e3+10;
int n,m,res;
string s[N];
void R(string &t){char ch=getchar();t=" ";while(ch<'A'||ch>'Z') ch=getchar();while(ch!='\n') t+=ch,ch=getchar();t+=' ';}
struct node{int first,second;};
//由于 pair 打出'.'后不能显示出 first 和 second，只好手打，方便些。
vector<node> vc[N][N];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
//dx 和 dy 是 x 和 y 的变化量
map<char,char> nxt;
bool vis[N][N];
int dis[N][N];
bool dfs(node u)
{
	if(dis[u.first][u.second]) return 1;
	dis[u.first][u.second]=vis[u.first][u.second]=1;
	for(node v:vc[u.first][u.second])
	{
		int x=v.first,y=v.second;
		if(vis[x][y]) return vis[u.first][u.second]=0,0;//有环
		if(!dfs(v)) return 0;
		dis[u.first][u.second]=max(dis[u.first][u.second],dis[x][y]+1);
	}
	return vis[u.first][u.second]=0,1;
  //vis[u.first][u.second]=0;
  //return 1;
}
int main()
{
	nxt['D']='I';
	nxt['I']='M';
	nxt['M']='A';
	nxt['A']='D';
  //nxt[A]=B 表示 A 的下一个字符是 B。
	scanf("%d%d",&n,&m);
	for(int i=0;i<=m+1;i++) s[0]+=' ';s[n+1]=s[0];
	for(int i=1;i<=n;i++) R(s[i]);
  //输入。
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++)
				if(s[i+dx[k]][j+dy[k]]==nxt[s[i][j]])
					vc[i][j].push_back((node){i+dx[k],j+dy[k]});
	//建图，自行理解。
//	for(int i=1;i<=n;i++)
//		for(int j=1;j<=m;j++)
//		{
//			printf("(%d,%d) : ",i,j);
//			for(node v:vc[i][j])
//				printf("(%d,%d) ",v.first,v.second);
//			puts("");
//		}puts("");
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='D')
			{
				bool f=dfs((node){i,j});
				if(f==0){puts("Poor Inna!");return 0;}
				else res=max(res,dis[i][j]/4);//答案即为 dis/4 向下取整。
			}
	if(res) printf("%d",res);
	else puts("Poor Dima!");
	return 0;
}
```

对于时空复杂度，发现都是 $n^2$ 级别的，可以通过此题。

---

## 作者：_Sonnet (赞：1)

# 思路
考虑 **dfs** 跑最长路

我们在跑最长路时，用 $ans$ 记录走的步数。因为题目求 $dima$ 出现的次数，所以最后 $ans$ 要除以四。若 $ans$ 
小于 $4$ ，则输出 Poor Dima!  。

#### 那么如何建边？

将每个点编号，可走的两个点进行建单相边，比如：

D -> I
I -> M
M -> A
A -> D

那么显然，在有环的情况下。Inna 是可以走 **无限次** 的。

#### 如何判环？

用 vis 数组记录走过的点，如果这个点已经走过了，但我们又走了一次，则有环。

#### AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 100;
const int N = 1e3 + 100;
const int M = 1e6 + 100;
int a[N][N] , ans , dis[M] ;
char s[N][N];
int xx[5] = {0 , 0 , 1 , -1};
int yy[5] = {1 , -1 , 0 , 0};
int head[M << 2] , to[M << 2] , ne[M << 2] , id;
bool vis[M] , flag;
int n , m;
//快读快写
namespace IO{
	template <typename T>
	inline void read(T &x){
		x = 0;
	    register int t = 1;
	    register char ch = getchar();
	    while(ch < '0' || ch > '9'){
	        if(ch == '-')
	            t = -1;
	        ch = getchar();
	    }
	    while(ch >= '0' && ch <= '9'){
	        x = (x << 3) + (x << 1) + ch - '0';
	        ch = getchar();
	    }
	    x *= t;
	}
	
	template <typename T>
	inline void write(T x){
	    if(x < 0){
	    	putchar('-');
			x = -x;
		}
	    if(x > 9) 
			write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace IO;
void add(int x , int y)
{
    to[++ id] = y;
    ne[id] = head[x];
    head[x] = id;
}
void build()
{
    int cnt = 0;
    // 标号
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= m ; j ++)
        {
            a[i][j] = ++ cnt;
        }
    }
    for(int i = 1 ; i <= n; i ++)
    {
        for(int j = 1 ; j <= m; j ++)
        {
            for(int k = 0 ; k < 4; k ++) 
            {
                int dx = i + xx[k] , dy = j + yy[k];
                if(dx < 1 || dy < 1 || dx > n || dy > m) 
                    continue;
                //连边
                if(s[i][j] == 'D' && s[dx][dy] == 'I') 
                    add(a[i][j] , a[dx][dy]);
                if(s[i][j] == 'I' && s[dx][dy] == 'M') 
                    add(a[i][j] , a[dx][dy]);
                if(s[i][j] == 'M' && s[dx][dy] == 'A') 
                    add(a[i][j] , a[dx][dy]);
                if(s[i][j] == 'A' && s[dx][dy] == 'D') 
                    add(a[i][j] , a[dx][dy]);
            }
        }
    }
}
void dfs(int s) {
    if(dis[s]) 
        return;
    vis[s] = 1;
    dis[s] = 1;
    for(int i = head[s]; ~ i; i = ne[i]) 
    {
        int v = to[i];
        if(vis[v]) //有环的情况
        {
			flag = 1;
			vis[s] = 0;
			return;
		}
        dfs(v);
        if(flag) 
        {
			vis[s] = 0;
			return;
		}
        //记录步数
        dis[s] = max(dis[s], dis[v] + 1);
    }
    vis[s] = 0;
}
signed main()
{
    read(n) , read(m);
    for (int i = 1 ; i <= n ; i ++)
    {
        scanf("%s" , s[i] + 1);
    }
    memset(head , -1 , sizeof(head));
    build();
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= m ; j ++)
        {
            if(s[i][j] =='D')
            {
                dfs (a[i][j]);
                if(flag)
                {
                    puts("Poor Inna!");
                    return 0;
                }
                ans = max(ans , dis[a[i][j]]);
            }  
        }
    }
    ans /= 4; //记得除以4
    if(ans)
        write(ans);
    else
        puts("Poor Dima!");
    return 0;
}

```

---

## 作者：封禁用户 (赞：1)

因为本题的数据范围为 $1\le n,m\le 10^{3}$，时限为 $1$ 秒，可得本题需要使用 $O(nm)$ 的解法。

我们可以从每一个字母 $\texttt{D}$ 开始 $\text{dfs}$，按照 $\texttt{D,I,M,A}$ 的顺序遍历。如果遍历的过程中，走到了当前 $\text{dfs}$ 路径上已经走过的点，就说明有环，输出 `Poor Inna!`，然后终止程序。否则就记录 $\frac{dis_{i,j}+1}{4}$，也就是能走到的最多的 $\texttt{DIMA}$（加 $1$ 是因为还要记录最初始的那个 $\texttt{D}$），和答案取 $\max$。

如果答案为 $0$，就代表这张网格中不存在 $\texttt{DIMA}$，输出 `Poor Dima!`，否则输出答案。

注：在 $\text{dfs}$ 的过程中有必要区分到达过的点 $vis$，处在 $\text{dfs}$ 路径上的点 $on$，和每个点的最长路 $dis$，因为它们的作用是各自不同的。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
char c[N][N];
bool vis[N][N];
bool on[N][N];
int dis[N][N];
bool f=0;
int tmp=0,n,m;
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
char targ(char c){
	if(c=='D') return 'I';
	else if(c=='I') return 'M';
	else if(c=='M') return 'A';
	else return 'D';
}
void dfs(int x,int y){
	if(f==1||vis[x][y]) return ;
	vis[x][y]=on[x][y]=1;
	for(int i=0;i<4;++i) {
        int xx=x+dx[i],yy=y+dy[i];
        if (1<=xx&&xx<=n&&1<=yy&&yy<=m&&c[xx][yy]==targ(c[x][y])){
            if(on[xx][yy]){//如果有环
            	f=1;
            	return ;
			}
            dfs(xx,yy);
			dis[x][y]=max(dis[x][y],dis[xx][yy]+1);
        }
    }on[x][y]=0;
	return ;
}
signed main(){
	int ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>c[i][j];
		}
	}for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(c[i][j]=='D'){
				dfs(i,j);
				if(f==1){
					cout<<"Poor Inna!"<<endl;
					return 0;
				}ans=max(ans,(dis[i][j]+1)/4);
			}
		}
	}if(ans==0){
		cout<<"Poor Dima!"<<endl;
	}else{
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Binary_Lee (赞：1)

## [题面传送门](https://www.luogu.com.cn/problem/CF374C)

### 解决思路

本题是找最长路的图上问题，所以先考虑如何建图。

首先把每一个字母转化为数字，然后对于每一个点枚举四个方向，如果有下一个字母，就向那个点建一条边，可以用 $vector$ 存图比较方便。用数字标号，只需要判断 $t_{x2,y2}=(t_{x1,y1}+1)\mod 4$ 是否成立即可，但直接用字母判断也是比较方便的。

然后考虑 $\text{dfs}$ 搜索可以走的最长路。有以下几个注意点：

- 开始搜索的点一定是 `D`。

- 已经更新过答案的点就不用搜了，直接 $\text{return}$，也算一个剪枝过程。

- 可以选无数个点的情况就是出现环了。所以需要 $vis$ 数组标记本次搜索经过的点，如果走到已经走过的点，直接输出 `Poor Inna!` 结束程序。同时回溯时记得要把 $vis$ 清空。

- 搜索时答案记录为走过的点数比较方便。因为从 `D` 开始，所以记 $ans=\max\{dis_{i,j}\}$。最后若 $ans<4$ 即输出 `Poor Dima!`，否则 $ans \div 4$ 就是 `DIMA` 的数量。

这样就可以愉快地通过本题了。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t[1005][1005],dis[1005][1005],ans;
bool vis[1005][1005];
char c;
int X[4]={0,0,1,-1},Y[4]={1,-1,0,0};
struct node{
	int x,y;
};
vector<node> a[1005][1005];
void read(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='D') t[i][j]=0;
			if(c=='I') t[i][j]=1;
			if(c=='M') t[i][j]=2;
			if(c=='A') t[i][j]=3;
		}
	}
} 
bool cango(int x1,int y1,int x2,int y2){   //能不能走
	if(t[x2][y2]==(t[x1][y1]+1)%4) return 1;
	return 0;
}
void build(){   //建图部分
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int z=0;z<4;z++){
				int xx=i+X[z],yy=j+Y[z];
				if(xx>n||xx<1||yy>m||yy<1) continue;
				if(cango(i,j,xx,yy)) a[i][j].push_back({xx,yy});
			}
		}
	}
}
void dfs(int sx,int sy){    //dfs
	if(dis[sx][sy]) return;
    vis[sx][sy]=1;
    dis[sx][sy]=1;
    for(int i=0;i<a[sx][sy].size();i++){
        int jx=a[sx][sy][i].x,jy=a[sx][sy][i].y;
        if(vis[jx][jy]){    //出现环
			printf("Poor Inna!");
			exit(0);
		}
        dfs(jx,jy);
        dis[sx][sy]=max(dis[sx][sy],dis[jx][jy]+1);
        ans=max(ans,dis[sx][sy]);
    }
    vis[sx][sy]=0;  //vis清零
}
int main(){
	scanf("%d%d",&n,&m);
	read();
	build();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) if(!t[i][j]) dfs(i,j); //对每一个D搜索
	}
	if(ans<4) printf("Poor Dima!");
	else printf("%d",ans/4);
	return 0;
}
```

---

## 作者：PDAST (赞：0)

不得不说，这是一道好题，刷它对提升深搜的理解有着重要意义。
## 题意
求能够连续向周围的格子走 `DIMA` 的个数。
例：
输入：
```
5 5
DIMAD
DIMAI
DIMAM
DDMAA
AAMID
```
输出：
```
4
```
## 考察方向
+ 记忆化搜索、最长路；
+ 搜索判环、拓扑判环；
+ 灵活建图；
+ 优化能力。
## 思路
对每个能向相邻格子走的格子之间建边（如 `D` 格子可以连 `I` 格子），用深搜或者拓扑判断是否存在环，若存在，则说明可以一直走下去，输出 `Poor Inna!`，对每个 `D` 进行搜索，并记忆化，求出最多能走几次，若能走的次数为 $0$，则输出 `Poor Dima!`，否则输出次数。
## 注意事项
空间一定要开够，要利用 STL 合理优化，节省空间，~~别问我怎么知道的~~，判环时一定要仔细检查，我因为判环导致死循环，空间炸了，调了半小时愣是没调出来。
## 代码
~~~cpp
#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;
map<char,int>letter;
char mp[1001][1001];
int sum[1000001],dp[1000001],v[1000001],n,m,maxn;
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
vector<int>g[1000001]; 
int frac(int x,int y){
	return (x-1)*m+y;
}
void search(int x,int fa){
	if(dp[x])return ;
	dp[x]=dp[fa];
	int mx=0;
	for(int i:g[x]){
		if(!dp[i])search(i,x);
		mx=max(mx,dp[i]);
	}
	dp[x]=mx;
	if(mp[(x-1)/m+1][(x-1)%m+1]=='A')dp[x]++;
	maxn=max(maxn,dp[x]);
}
int main(){
	letter['D']=0,letter['I']=1,letter['M']=2,letter['A']=3;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>mp[i]+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<4;k++){
				int x=i+dx[k],y=j+dy[k];
				if(x>0&&y>0&&x<=n&&y<=m&&(letter[mp[i][j]]+1)%4==letter[mp[x][y]]){
					g[frac(i,j)].push_back(frac(x,y));
					sum[frac(x,y)]++;
				}
			}
		}
	}
	queue<int>q;
	for(int i=1;i<=n*m;i++){
		if(sum[i]==0)q.push(i);
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		v[u]=1;
		for(int i:g[u]){
			sum[i]--;
			if(!v[i]&&sum[i]==0)q.push(i);
		}
	}
	for(int i=1;i<=n*m;i++){
		if(!v[i]){
			cout<<"Poor Inna!";
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='D'&&!dp[frac(i,j)])search(frac(i,j),0);
		}
	}
	if(maxn==0)cout<<"Poor Dima!";
	else cout<<maxn;
}
~~~

---

## 作者：NaN_HQJ2007_NaN (赞：0)

简单搜索题。

定义 $f_{i,j}$ 表示从 $(i,j)$ 开始走，最多能走几个点。

每次遍历四个方向，看那个能走，取最大值再加一即可。

如果走到了之前走过的点，说明可以无限走下去。

最后把步数除以 $4$ 输出。

复杂度 $O(n^2)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000+5;
int n,m,f[N][N],dx[]={0,0,-1,1},dy[]={-1,1,0,0};
bool vis[N][N];
char c[N][N];
map<char,char>mp;
int dfs(int i,int j){
  if(vis[i][j]){
    cout<<"Poor Inna!"<<endl;
    exit(0);
  }
  if(f[i][j])return f[i][j];
  vis[i][j]=1;
  int maxn=0;
  for(int k=0;k<4;++k){
    int x=i+dx[k],y=j+dy[k];
    if(x<1||y<1||x>n||y>m||c[x][y]!=mp[c[i][j]])continue;
    maxn=max(maxn,dfs(x,y));
  }
  vis[i][j]=0;
  return f[i][j]=1+maxn;
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m;
  mp['D']='I';mp['I']='M';mp['M']='A';mp['A']='D';
  for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)cin>>c[i][j];
  int ans=0;
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      if(c[i][j]=='D'){
        ans=max(ans,dfs(i,j));
      }
    }
  }
  if(ans<4)cout<<"Poor Dima!"<<endl;
  else cout<<ans/4<<endl;
  return 0;
}

```


---

## 作者：火羽白日生 (赞：0)

> 给出 $n$ 行 $m$ 列的地图，每个格子都有四个字母 `D` `I` `M` `A`，每次都从 `D` 开始走，能走上下左右四个方向，问：能否走完四个字母，若可以，最多能走多少次或者能否走无限次。

其实思路还挺好想的。

枚举整个地图，对于每一个字母，如果它的上下左右四个方向有它的下一个字母（`A` 的下一个字母是 `D`），就让它和它的下一个字母连一条边。

解决完建图之后，就在图上跑 DFS，分别设 $vis_i$ 和 $step_i$ 为点 $i$ 是否访问过和从 $i$ 点开始最多能走多少步。

从每个 `D` 开始遍历，如果已经有点被遍历过，那么就说明有环，直接退出，否则更新 $step$ 数组。

最后更新答案，有 $ans=\max\limits_{i\ for\ every\ D}\{step_i\}$。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=1e3+5;
	
	int n,m,tot,ans;
	int mp[maxn][maxn],uid[maxn][maxn],step[maxn*maxn],d[5][2]={{1,0},{0,1},{-1,0},{0,-1}};
	bool vis[maxn*maxn];
	namespace Graph{// 建图
		int head[maxn*maxn],id;
		struct e{int v,next;}edge[maxn*maxn<<1];
		inline void add(int u,int v){
			edge[++id].v=v;
			edge[id].next=head[u];
			head[u]=id;
		}
	}using namespace Graph;
	inline int get(char ch){// 将字母转为数字便于操作
		if(ch=='D') return 1;
		if(ch=='I') return 2;
		if(ch=='M') return 3;
		if(ch=='A') return 4;
	}
	void dfs(int u){
		if(step[u]) return;// 记忆化
		vis[u]=1; step[u]=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v;
			if(vis[v]){puts("Poor Inna!"); exit(0);}// 有环，直接输出
			dfs(v);
			step[u]=max(step[u],step[v]+1);// 最长路
		}
		vis[u]=0;
	}
	
	inline int main(){
		n=read(); m=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				char ch; cin>>ch;
				mp[i][j]=get(ch);
				uid[i][j]=++tot;// 每个格子的编号
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				for(int k=0;k<4;k++){
					int tx=i+d[k][0],ty=j+d[k][1];
					if(tx<1 || tx>n || ty<1 || ty>m) continue;
					if(mp[tx][ty]==mp[i][j]+1 || (mp[tx][ty]==1 && mp[i][j]==4))
						add(uid[i][j],uid[tx][ty]);// 如果上下左右四个方向有下一个字母就连边
				}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(mp[i][j]!=1) continue;
				dfs(uid[i][j]);
				ans=max(ans,step[uid[i][j]]);
			}
		ans/=4;
		if(ans) printf("%d\n",ans);
		else puts("Poor Dima!");
		return 0;
	}
}
signed main(){return CL::main();}
```

---

