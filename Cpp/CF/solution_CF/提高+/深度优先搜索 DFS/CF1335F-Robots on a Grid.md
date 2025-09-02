# Robots on a Grid

## 题目描述

There is a rectangular grid of size $ n \times m $ . Each cell of the grid is colored black ('0') or white ('1'). The color of the cell $ (i, j) $ is $ c_{i, j} $ . You are also given a map of directions: for each cell, there is a direction $ s_{i, j} $ which is one of the four characters 'U', 'R', 'D' and 'L'.

- If $ s_{i, j} $ is 'U' then there is a transition from the cell $ (i, j) $ to the cell $ (i - 1, j) $ ;
- if $ s_{i, j} $ is 'R' then there is a transition from the cell $ (i, j) $ to the cell $ (i, j + 1) $ ;
- if $ s_{i, j} $ is 'D' then there is a transition from the cell $ (i, j) $ to the cell $ (i + 1, j) $ ;
- if $ s_{i, j} $ is 'L' then there is a transition from the cell $ (i, j) $ to the cell $ (i, j - 1) $ .

It is guaranteed that the top row doesn't contain characters 'U', the bottom row doesn't contain characters 'D', the leftmost column doesn't contain characters 'L' and the rightmost column doesn't contain characters 'R'.

You want to place some robots in this field (at most one robot in a cell). The following conditions should be satisfied.

- Firstly, each robot should move every time (i.e. it cannot skip the move). During one move each robot goes to the adjacent cell depending on the current direction.
- Secondly, you have to place robots in such a way that there is no move before which two different robots occupy the same cell (it also means that you cannot place two robots in the same cell). I.e. if the grid is "RL" (one row, two columns, colors does not matter there) then you can place two robots in cells $ (1, 1) $ and $ (1, 2) $ , but if the grid is "RLL" then you cannot place robots in cells $ (1, 1) $ and $ (1, 3) $ because during the first second both robots will occupy the cell $ (1, 2) $ .

The robots make an infinite number of moves.

Your task is to place the maximum number of robots to satisfy all the conditions described above and among all such ways, you have to choose one where the number of black cells occupied by robots before all movements is the maximum possible. Note that you can place robots only before all movements.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
3
1 2
01
RL
3 3
001
101
110
RLL
DLD
ULL
3 3
000
000
000
RRD
RLD
ULL```

### 输出

```
2 1
4 3
2 2```

# 题解

## 作者：syksykCCC (赞：9)

一直无限走下去实在玄学，看看能不能转化一下。

因为格子有限，所以 **无限 $=$ 循环**。

换一种方法，我们可以先把每个位置都摆上机器人，一直走起来，删去会重复的。

显然，每个机器人都是先经过一些奔波，然后在一个环里面一直走下去。

比如我们现在随便弄来两个机器人，怎么知道它们会不会重复呢？

首先，假设两个机器人各自奔波时没相遇，也就是到了自己的目标环中，那么它们就永远不会相遇了。这很好理解，如果它们不在一个环中，那显然不可能碰到；如果在一个环中（当然前提是不在一个位置），那么他们之间的距离就永远不会变了，也不会相遇。

所以，两个机器人相遇的充要条件就是在奔波的路途上相遇，而且之后，该相遇的就一直在一起走了，不该相遇的就永远碰不到了。

所以，每一条道路的长度肯定不会超过图的总大小（即 $nm$），所以我们只要让每一个位置的机器人都走 $nm$ 步，然后统计位置就行了。

至于具体怎么统计，可以弄一个 $have_{0/1, \text{pos}}$ 表示最终 $\text{pos}$ 这个位置有没有黑 / 白色的机器人，然后令 $tot$ 表示总数，$black$ 表示总黑色机器人数，那么就是：

$$\begin{array}{l|l}1 & \textbf{for } i \gets 1 \textbf{ to } nm \textbf{ do} \\ 2 & \qquad \textbf{if } have_{0, i} = \text{true} \textbf{ then } tot \gets tot + 1, black \gets black + 1 \\ 3 & \qquad \textbf{else if } have_{1, i} = \text{true} \textbf{ then } tot \gets tot + 1 \\ 4 & \qquad \textbf{end if} \\ 5 & \textbf{end for}\end{array}$$

代码仅供参考。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int NM = 1e6 + 5, LGSZ = 21;
int n, m, nxt[LGSZ][NM];
char dir[NM], col[NM], buf[NM];
bool have[2][NM];
int main() 
{
	int t;
	scanf("%d", &t);
	while(t--) 
	{
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n * m; i++)
			have[0][i] = have[1][i] = false;
		for(int i = 1; i <= n; i++) 
		{
			scanf("%s", buf + 1);
			for(int j = 1; j <= m; j++)
				col[(i - 1) * m + j] = buf[j];
		}
		for(int i = 1; i <= n; i++) 
		{
			scanf("%s", buf + 1);
			for(int j = 1; j <= m; j++)
				dir[(i - 1) * m + j] = buf[j];
		}
		for(int i = 1; i <= n * m; i++)
			switch(dir[i])
			{
				case 'U': nxt[0][i] = i - m; break;
				case 'D': nxt[0][i] = i + m; break;
				case 'L': nxt[0][i] = i - 1; break;
				case 'R': nxt[0][i] = i + 1; break;
			}
		for(int i = 1; i < LGSZ; i++)
			for(int j = 1; j <= n * m; j++)
				nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
		for(int i = 1; i <= n * m; i++)
		{
			int pos = i;
			for(int j = LGSZ - 1; ~j; j--)
				if(n * m >> j & 1) pos = nxt[j][pos];
			have[col[i] ^ 48][pos] = true;
		}
		int black = 0, tot = 0;
		for(int i = 1; i <= n * m; i++)
		{
			if(have[0][i]) tot++, black++;
			else if(have[1][i]) tot++;
		}
		printf("%d %d\n", tot, black);
	}
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF1335F) 

看到很多题解都是写的 $\operatorname{O}(nm\cdot \log nm)$ 的倍增，这里将一种 $O(nm)$ 的做法

首先，我们可以将给出的网格图转化为若干棵形如下图的**内向基环树**    
为了方便理解，我们将环上的节点从 $0$ 开始依次编号。满足对于环上的每一条边 $[x \rightarrow y]$，$x+1=y$

![image.png](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pLmxvbGkubmV0LzIwMjAvMDcvMDkvTEVqZmVwbnZhUG9iR2xGLnBuZw?x-oss-process=image/format,png)
接着，我们让环上点的编号每秒钟沿着**环上的边**移动一次  

![image.png](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pLmxvbGkubmV0LzIwMjAvMDcvMDkvR0NpY0tETVpibXY0OWZ4LnBuZw?x-oss-process=image/format,png)

这样，对于所有点，我们都可以求出来他最后到达的环上的点的编号，从而计算此基环树上有多少个机器人可以放在黑色点上  
举个栗子：对于一个在点 $x$ 上的机器人，设他到环上的最短距离为 $cur$，环上点的个数为 $val$，离他最近的环上的点的编号为 $pos$。那么，它在 $cur$ 秒后遇到的环上点的编号即为 $(pos-cur) \mod val$。**注意负数的取模！**

----

上面声明了一个较复杂的概念，下面是做法

首先分别建出正向和反向图。  
设 $flag[i]=0/1$ 表示是否存在一个从黑色点出发的机器人，满足可以到达环上的编号为 $i$ 的点。$sum = \sum flag[i]$ 即为最多的从黑色点出发的机器人

接着，使用 dfs 寻找出每个基环树中的环。找到后，以环为起点开始反向遍历，求出 $flag$ 数组并累及答案（$flag$ 每次找到一棵基环树后都要清空）

最后，可放置的最多的机器人数就是所有基环树的环的大小之和。最多的黑色点出发的机器人数就是 $\sum sum$

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int Maxn=1000000+10,Maxm=1010;
const int dx[]={1,-1,0,0},dy[]={0,0,-1,1};
int head[Maxn],nxt[Maxn],to[Maxn];
bool vis[Maxn],a[Maxn];
bool flag[Maxn<<1];
int id[Maxn],d[Maxn];
int n,m,tot,val,ans;
int pos,w,e;
int dfn[Maxn],cnt,edgecnt=1;
inline int get(int x,int y)
{
	return (x-1)*m+y;
}
inline void add(int x,int y)
{
	++edgecnt;
	nxt[edgecnt]=head[x];
	to[edgecnt]=y;
	head[x]=edgecnt;
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void rev(int x,int cur) // 反向遍历
{
	vis[x]=1;
	if(a[x])flag[((pos-cur)%val+val)%val]=1; // 注意负数的取模
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(id[y]>=w && id[y]<=e)continue; // 不要重复遍历环上的点
		rev(y,cur+1);
	}
}
void init()
{
	ans=tot=cnt=0,edgecnt=1;
	for(int i=0;i<=n*m+5;++i)
	{
		head[i]=0;
		flag[i]=vis[i]=a[i]=d[i]=0;
		id[i]=-1;
	}
}
bool dfs(int x,int y)
{
	id[get(x,y)]=cnt;
	vis[get(x,y)]=1;
	dfn[cnt++]=get(x,y); // 模拟栈
	int u=x+dx[d[get(x,y)]],v=y+dy[d[get(x,y)]];
	if(id[get(u,v)]!=-1)
	{
		int l=id[get(u,v)],r=id[get(x,y)];
		val=(r-l+1); // 环上的点数
		for(int i=l;i<=r;++i)
		{
			pos=i-l,w=l,e=r;
			rev(dfn[i],0);
		}
		id[get(x,y)]=-1,--cnt;
		return 1;
	}
	bool tmp=dfs(u,v);
	id[get(x,y)]=-1,--cnt;
	return tmp;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int T=read();
	while(T--)
	{
		n=read(),m=read();
		init();
		for(int i=1;i<=n;++i)
		{
			char s[Maxn];
			scanf("%s",s+1);
			for(int j=1;j<=m;++j)
			if(s[j]=='0')a[get(i,j)]=1;
		}
		for(int i=1;i<=n;++i)
		{
			char s[Maxn];
			scanf("%s",s+1);
			for(int j=1;j<=m;++j)
			{
				if(s[j]=='U')d[get(i,j)]=1;
				if(s[j]=='D')d[get(i,j)]=0;
				if(s[j]=='L')d[get(i,j)]=2;
				if(s[j]=='R')d[get(i,j)]=3;
				int k=d[get(i,j)];
				int u=i+dx[k],v=j+dy[k];
				int x=get(i,j),y=get(u,v);
				add(y,x);
			}
		}
		for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			if(vis[get(i,j)])continue;
			if(!dfs(i,j))continue;
			ans+=val;
			for(int i=0;i<val;++i)
			{
				if(flag[i])++tot;
				flag[i]=0;
			}
		}
		printf("%d %d\n",ans,tot);
	}
	return 0;
}
```


---

## 作者：suxxsfe (赞：3)

**比较简单的倍增**  
~~但还是看了题解才会~~  

## 题意  

给出一个 $n\times m$ 的网格，每个格子有颜色，$0$ 黑 $1$ 白，每个格子还有一个方向，表示这个格子上的机器人会向那个方向走，并保证不会走出格子  
摆放机器人，它们同时开始运动，在任意时刻不能有两个机器人在同一个格子里  
先最大化机器人个数，如果多种方案机器人个数相等，再最大化摆在黑格子里的机器人数量  

---------  

首先，这个路线肯定是循环的，如果不循环，就会走到无限多个格子，不合理  
然后，对于任意一个格子，从那里开始走到完成一个完整的循环，步数肯定小于等于 $nm$，显然它不能走了比 $nm$ 还多的格子仍然不开始循环  
而对于两个不同的循环，它们一定**没有交点（就是一个相同的格子）**，如果有，肯定就不会行成两个循环了  

如果有两个机器人分别走了至少 $nm$ 步，那么它们肯定已经各子循环了一次或以上了  
所以，如果它们不在同一个循环，显然不会相遇  
如果在一个循环，且没有在 $nm$ 步内相遇，说明这时它们已经“同步”了，就是会一直保持这一个距离不断的走，永不相遇  
当然，如果在 $nm$ 步之前就已经相遇，那么它们会一直一起走，不会有影响  

至此，我们判断两个格子上的机器人是否会相遇的方法，就是看它们走了 $nm$ 步以后，是不是在同一个格子  

所以，假设我们在所有格子都摆上机器人，让他们走，一旦有几个相遇了，就说明我们要去掉这些机器人只剩下其中的一个  
这时，给这 $nm$ 个点编号 $1\ldots nm$，并用$white_i,black_i$表示的分别是有没有从白/黑格出发的机器人，$nm$ 格后会走到这里  

然后从 $1$ 到 $nm$ 统计答案，如果某个格子可以由黑色格子中的机器人走来，就保留黑色格子的那个，否则任意保留  
就可以计算出答案了  

对于走 $nm$ 步那个操作，就要用倍增实现  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int black[1000006],white[1000005];
int nex[24][1000006];
int color[1000006];
char s[1000006];
int main(){int T=read();while(T--){
	int n=read(),m=read();
	for(reg int i=1;i<=n;i++){
		std::scanf("%s",s+1);
		for(reg int j=1;j<=m;j++) color[(i-1)*m+j]=s[j]=='0'?0:1;
	}
	for(reg int i=1;i<=n;i++){
		std::scanf("%s",s+1);
		for(reg int j=1;j<=m;j++){
			int now=(i-1)*m+j;
			if(s[j]=='U') nex[0][now]=now-m;
			else if(s[j]=='D') nex[0][now]=now+m;
			else if(s[j]=='L') nex[0][now]=now-1;
			else nex[0][now]=now+1;
		}
	}
	n*=m;
	for(reg int i=1;i<=20;i++)
		for(reg int j=1;j<=n;j++) nex[i][j]=nex[i-1][nex[i-1][j]];
	for(reg int j=1;j<=n;j++){
		int to=j;
		for(reg int i=20;~i;i--){//倒着循环，倍增传统套路，不过想想也能知道，要先走大的步数 
			if((1<<i)&n) to=nex[i][to];
		}
		color[j]?white[to]=1:black[to]=1;
	}
	int ans=0,black_num=0;
	for(reg int i=1;i<=n;i++)
		if(black[i]) black_num++,ans++,black[i]=white[i]=0;
		else if(white[i]) ans++,black[i]=white[i]=0;
	std::printf("%d %d\n",ans,black_num);
}
	return 0;
}
```

---

## 作者：do_it_tomorrow (赞：2)

[更哈的阅读体验](https://doittomorrow.xyz/post/cf1335f-ti-jie/)
# 题目大意
给出一个 $n\times m$ 的网格，每个格子被染成黑色或白色，并且在每个格子上都有一个方向。你可以在一些格子中放置机器人，但要求所有的格子内的机器人均可以一直走走下去，一直不与其他机器人相撞。要求在满足上述条件的情况下使得机器人数量和机器人占据的黑格数量均最多。

# 思路
因为格子的数量是有限的，而机器人却需要重复无限次的行走，所以显然所有的机器人在最后都会汇聚到环上。因为整个图的可以行走的格子数量不会超过 $n\times m$，所以在机器人行走 $n\times m$ 步之后，所有应该重复的机器人应该已经重合了。

所以我们假设所有的格子在一开始都有机器人，那么在走了 $n\times m$ 步之后，所有应该相遇的机器人应该已经全部相遇了。如果在最后有机器人相遇了，那么就说明这些格子只能放置一个机器人。因为需要将黑色格子放置的机器人最大化，那么如果有来自黑色格子的机器人，那么就将这个格子让给黑色格子的机器人。

因为要模拟 $n\times m$ 个机器人走 $n\times m$ 步，所以直接模拟会超时，需要考虑倍增。预处理出数组 $f$，其中 $f_{i,j}$ 表示编号为 $i$ 的机器人走 $2^j$ 步到达的格子。

这样就可以快速的知道在 $n\times m$ 秒后的答案，时间复杂度为 $O(nm\log n)$。

# AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int t,n,m,c[N],f[N][22],cnt[N][2];
char a[N];
void solve(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>a;
		for(int j=0;j<m;j++) c[i*m+j]=a[j];
	}for(int i=0;i<n;i++){
		cin>>a;
		for(int j=0;j<m;j++){
			if(a[j]=='U') f[i*m+j][0]=(i-1)*m+j;
			if(a[j]=='D') f[i*m+j][0]=(i+1)*m+j;
			if(a[j]=='L') f[i*m+j][0]=i*m+j-1;
			if(a[j]=='R') f[i*m+j][0]=i*m+j+1;
		}
	}for(int i=0;i<n*m;i++) cnt[i][0]=cnt[i][1]=0;
	int p=log2(n*m)+1;
	for(int i=1;i<=p;i++){
		for(int j=0;j<n*m;j++){
			f[j][i]=f[f[j][i-1]][i-1];
		}
	}for(int i=0;i<n*m;i++){
		int k=f[i][p];
		if(c[i]==48) cnt[k][0]++;
		else cnt[k][1]++;
	}int ans1=0,ans2=0;
	for(int i=0;i<n*m;i++){
		if(cnt[i][0]||cnt[i][1]) ans1++;
		if(cnt[i][0]) ans2++;
	}cout<<ans1<<" "<<ans2<<endl;
}
signed main(){
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：_lqs_ (赞：1)

### solution

根据题意，在若干次移动后所有 bot 都会到某个简单环上。

那么我们先把所有的环用 dfs 找出来。考虑“不能相遇”这个设问，我们在每个环中随便钦定一个点 $x$，求出 $x$ 可达的所有点的路径长度，这个可以通过建反图实现。

则有以下性质：设 $x$ 所在环的点数为 $c$，点 $x$ 到点 $a$ 和 $b$ 的路径长度分别为 $dis_{a}$ 和 $dis_{b}$。则若 $dis_{a}≡dis_{b} \pmod c$，$a$ 和 $b$ 不可同时作为 bot 出生点。

证明的话画个图手玩一下就好了，这个取模操作应该还是很好理解的。

然后处理连通块，对每个块内路径取模后的剩余系分组，同余的只能选 $1$ 个点，那么贪心地有黑选黑即可。

时间复杂度 $O(nm)$，代码不好写。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
#define pb push_back
int n,m,i,j,ans,sum,t,a,k,ru[N],dis[N],v[N],to[N],vis[N],u[N],rev[N],ls[N],flag[N];
int X,Y,par[N];
char dig[N],mp[N],sq[N];
std::queue<int>q;
std::vector<int>s,g,G[N];
std::stack<int>stk;
struct ren{
	int ds,w;
}d[N];
bool cmp(ren x,ren y){
	return x.ds < y.ds;
}
void dfs(int x){
	v[x]=1;
	if(!v[to[x]]) par[to[x]]=x,dfs(to[x]);
	else if(v[to[x]]==1){
		int c=x;
		while(c!=to[x]){
			vis[c]=2;
			c=par[c];
		}
		vis[to[x]]=2;
	}
	v[x]=2;
}
void f(int x){
	s.clear();
	while(!u[x]){
		u[x]=1,s.pb(x);
		x=to[x];
	}
	int c=s.size();
	for(int y:s) ls[y]=c;
}
void chk(int p,int n,int m){
	Y=p%m;
	if(!Y) Y=m;
	X=(p-Y)/m+1;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++){
			scanf("%s",sq+1);
			for(j=1;j<=m;j++) dig[(i-1)*m+j]=sq[j];
		}
		for(i=1;i<=n;i++){
			scanf("%s",sq+1);
			for(j=1;j<=m;j++) mp[(i-1)*m+j]=sq[j];
		}
		for(i=1;i<=n*m;i++) v[i]=0,par[i]=0,G[i].clear(),dis[i]=-1,vis[i]=0,u[i]=0,ru[i]=0,flag[i]=0;
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				char c=mp[(i-1)*m+j];
				if(c=='D') to[(i-1)*m+j]=i*m+j,G[i*m+j].pb((i-1)*m+j);
				if(c=='U') to[(i-1)*m+j]=(i-2)*m+j,G[(i-2)*m+j].pb((i-1)*m+j);
				if(c=='L') to[(i-1)*m+j]=(i-1)*m+j-1,G[(i-1)*m+j-1].pb((i-1)*m+j);
				if(c=='R') to[(i-1)*m+j]=(i-1)*m+j+1,G[(i-1)*m+j+1].pb((i-1)*m+j);
			}
		}
		for(i=1;i<=n*m;i++){
			if(!v[i]) dfs(i);
		}
		for(i=1;i<=n*m;i++){
			if(vis[i]==2 && !u[i]) flag[i]=1,f(i);
		}
		ans=0,sum=0;
		for(i=1;i<=n*m;i++){
			if(flag[i]){
				int x=i;
				dis[x]=0,q.push(x),s.clear(),k=0;
				while(!q.empty()){
					a=q.front(),q.pop(),s.pb(a);
					for(int y:G[a]){
						if(dis[y]==-1){
							dis[y]=dis[a]+1;
							q.push(y);
						}
					}
				}
				for(int y:s) dis[y]%=ls[x];
				for(int y:s) d[++k].ds=dis[y],d[k].w=y;
				sort(d+1,d+1+k,cmp),d[0].ds=-1,d[k+1].ds=-1;
				int p=-1;
				for(j=1;j<=k+1;j++){
					if(d[j].ds!=d[j-1].ds && p!=-1){						
						ans++,chk(p,n,m);
						if(dig[(X-1)*m+Y]=='0') sum++;
						p=-1;
					}
					if(p==-1) p=d[j].w;
					else{
						chk(d[j].w,n,m);
						if(dig[(X-1)*m+Y]=='0') p=d[j].w;
					}
				}
			}
		}
		printf("%d %d\n",ans,sum);
	}
	return 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
$n \times m$ 的黑白网格，给出每个格子的颜色以及下一步移动的方向。当给一个位置放一个机器人，它会按照每个位置的信号移动，可以放多个机器人，但要求相同时刻一个位置不能出现两个机器人。求最多可以放多少个机器人，机器人数量相同时最多有多少个机器人放在黑格子上。
## 分析
样例是个好东西（但有时也要小心被坑）。

观察样例发现，这些控制指令可以使整个网格看作一个有向图，某些指令会构成一个环，到环上各点的只能是一条简单通路。因为有环所以 $nm$ 步后机器人一定进入环中，所以我们可以用倍增的方法求每个点到 $(2^{i})$ 的位置。然后就可以得到每个位置机器人在 $nm$ 步后的位置。这些位置的个数就是机器人总数，如果是从黑格子出发到达的就算在黑格子机器人数量中。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i = a; i <= n; ++ i);
#define per(i,a,n) for(int i = n; i >= a; -- i);
typedef long long ll;
const int N = 1e6 + 105;
const int mod = 998244353;
const double Pi = acos(- 1.0);
const int INF = 0x3f3f3f3f;
const int G = 3, Gi = 332748118;
ll qpow(ll a, ll b) { ll res = 1; while(b){ if(b) res = (res * a) % mod; a = (a * a) % mod; b >>= 1;} return res; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
int T, n, m;
int f[N][50];
int col[N], B[N], W[N];
int res1, res2;
char s[N];
int main(){
    scanf("%d",&T);
    while(T --){
        res1 = res2 = 0;
        scanf("%d%d",&n,&m);
        for(int i = 1; i <= n; ++ i){ 
            scanf("%s",s + 1);
            for(int j = 1; j <= m; ++ j){
                int v = (i - 1) * m + j;
                col[v] = (s[j] == '0');
            }
        }
        for(int i = 1; i <= n; ++ i){
            scanf("%s",s + 1);
            for(int j  = 1; j <= m; ++ j){
                int v = (i - 1) * m + j;
                if(s[j] == 'U') f[v][0] = v - m;
                else if(s[j] == 'D') f[v][0] = v + m;
                else if(s[j] == 'R') f[v][0] = v + 1;
                else if(s[j] == 'L') f[v][0] = v - 1;
            }
        }
        for(int j = 1; j <= 20; ++ j)
            for(int i = 1; i <= n * m; ++ i)
                f[i][j] = f[f[i][j - 1]][j - 1];
        for(int i = 1; i <= n * m; ++ i){
            int to = i;
            for(int j = 20; j >= 0; -- j){
                if((1 << j) & (n * m)) to = f[to][j];
            }
            if(col[i]) B[to] = 1;
            else W[to] = 1;
        }
       for(int i = 1; i <= n * m; ++ i){
           if(B[i]) res1 ++, res2 ++, B[i] = W[i] = 0;
           else if(W[i]) res1 ++, W[i] = B[i] = 0;
       }
       printf("%d %d\n",res1,res2);
    }
    return 0;
}
```

---

## 作者：youdu666 (赞：0)

### 思路：Tarjan 缩点，dfs

本题大致意思就是说给定每个点上走的路线，求任意点永远不会相撞时最多放的点数以及该点数下最多放在 0 处的点数。

先把平面图以方向为有向边构造出一张图。

第一问比较简单，即环上点的和，重头戏在第二问上。

永远不相撞即某一个点到环的距离加上这个环上的点到环的基准点（随便设一个即可）要走的步数（不是距离）对这个环的大小取模后的值不相等。若任意两个结束在同一个环里的点要都放置，必须满足该条件。

然后实现起来也非常阴间，我调了前后快两个小时。

首先为了找到环，可以使用时间复杂度比较优的 Tarjan 来写。

随后直接把 Tarjan 出口的地方设为基准点，然后在Tarjan出栈操作时同步标好该点到所在环的基准点的距离，这样可以直接保证求出距离。

然后对于每一个在环上的点进行 DFS，处理整张图每一个点到环的距离。

最后用 STLmap 来记录某一个环上的点是否可以被 0 出发的点占领，统计答案，输出即可。

代码中含注释，可辅助理解。

### 代码

```
#include <bits/stdc++.h>
#define m(a,b) make_pair(a,b)
using namespace std;
const int N=1e6+5;
inline int read()
{
	int x=0,y=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
		y=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*y;
}
int n,m;
bool a[N];
int g[N],dfn[N],low[N],dfstime,co[N];
int dk[N];
int ds[N];
bitset<N> vis;
vector<int> h[N];
vector<int> fa[N];
map<pair<int,int>,bool> mp;
int hn;
int stk[N],top;
inline int dt(int x,int y)//把坐标转化成点方便计算
{
	return (x-1)*m+y;
}
void tarjan(int u)//Tarjan缩点板子
{
	dfn[u]=low[u]=++dfstime;
	stk[++top]=u;
	int v=g[u];
	if(!dfn[v])
	{
		tarjan(v);
		low[u]=min(low[u],low[v]);
	}
	else
		if(co[v]==0)
			low[u]=min(low[u],low[v]);
	if(low[u]==dfn[u])
	{
		if(stk[top]==u)
		{
			top--;
			co[u]=-2e9;
			return;
		}
		hn++;
		int dkn=-1;
		h[hn].clear();
		while(stk[top]!=u)
		{
			h[hn].emplace_back(stk[top]);
			co[stk[top]]=hn;
			ds[stk[top]]=0;
			dk[stk[top]]=++dkn;
			top--;
		}
		h[hn].emplace_back(stk[top]);
		co[stk[top]]=hn;
		dk[u]=++dkn;
		ds[u]=0;
		top--;
		return;
	}
}
int root,rooth,cnt;
void dfs(int u)
{
	vis[u]=1;
	for(auto v:fa[u])
	{
		if(vis[v]||co[v]>0)continue;
		ds[v]=ds[u]+1;
		if(a[v]==0)//记录该位置可被环外的点占领
			mp[m(rooth,(dk[root]+ds[v])%h[rooth].size())]=true;
		dfs(v);
	}
}
signed main()
{
	int T=read();
	while(T--)
	{
		cnt++;
		
		mp.clear();
		n=read(),m=read();
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char c=getchar();
			while(c!='0'&&c!='1')
				c=getchar();
			a[dt(i,j)]=(c-'0')==1;
		}
		top=0;
		hn=0;
		for(int i=1;i<=n*m;i++)
		fa[i].clear(),vis[i]=0;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char c=getchar();
			while(c!='L'&&c!='R'&&c!='D'&&c!='U')
				c=getchar();
			if(c=='L')g[dt(i,j)]=dt(i,j-1),fa[(dt(i,j-1))].emplace_back(dt(i,j));
			if(c=='R')g[dt(i,j)]=dt(i,j+1),fa[(dt(i,j+1))].emplace_back(dt(i,j));
			if(c=='D')g[dt(i,j)]=dt(i+1,j),fa[(dt(i+1,j))].emplace_back(dt(i,j));
			if(c=='U')g[dt(i,j)]=dt(i-1,j),fa[(dt(i-1,j))].emplace_back(dt(i,j));
		}
		int w=n*m;//多测不清空，爆零两行泪
		for(int i=1;i<=w;i++)
		co[i]=dfn[i]=low[i]=0;
		
		for(int i=1;i<=w;i++)//tarjan找环
		if(!dfn[i])
		tarjan(i);
		
		int ans=0;
		for(int i=1;i<=hn;i++)
		ans+=h[i].size();
		printf("%d ",ans);
		for(int i=1;i<=w;i++)//dfs处理每一个点到环的距离
			if(co[i]>0)
			{
				if(a[i]==0)
				mp[m(co[i],dk[i])]=true;//记录该位置可被自己占领
				root=i;
				rooth=co[i];
				dfs(i);
			}
		ans=0;
		for(int i=1;i<=hn;i++)
		for(int j=0;j<h[i].size();j++)
		if(mp[m(i,j)])
		ans++;
		printf("%d\n",ans);
	}
}
/*
1
3 2
00
11
11
RD
UL
RL
*/
```


---

## 作者：mydcwfy (赞：0)

**update on 2022/10/02：好像原来贴错代码了（**

## 1. 题意

- 给定一个 $n\times m$ 的黑白网格，每一个点都会有一个方向，如果放置的机器人走到这里的话，将会按照该方向走下去。现在要放置最多的机器人，使得机器人永远不会走到同一个点上（每一步中间相遇的不算）。在放置最多的基础上，要求最开始放在黑色上的机器人最多。
- 有 $t$ 组数据，$n\times m\leq10^6,\sum n\times m\leq10^6,t\leq5\times10^4$。

## 2. 思路

其实如果想到图论的话，就比较简单了。

首先，我们考虑怎样才能 **永远不相撞**。

所有的机器人最后一定是在环上一直绕圈，又由于速度相同，所以永远不会相撞。

易得第一问答案不可能大于环上点的数量（因为如果有多的话，走到最后，一定会有两个机器人在同一个点，明显不符合条件）。

注意到每一个点有且只有一个出边，所以原图一共有 $n\times m$ 个点，同样也有 $n\times m$ 条边。

？这不就是基环树吗？

通过基环树的方法，我们可以简单的找出所有的环。不考虑第二问的话，我们直接将所有的机器人放在环上，这个就是一个最优解。

那么第一问就解决了，答案就是环的数量。

下面我们来看第二问：怎样让最多的机器人在黑色点上？

已经是黑色点的我们可以不管了，我们可以将一些白色的点替换为非环的黑点。

我们画一个图，来看一下需要满足什么样的条件才可以。

![](https://cdn.luogu.com.cn/upload/image_hosting/l9i17lnm.png)

当前，如果我们将一个机器人放在 b 点，经过两步之后，就会走到 c 点，如果最开始放在 a 点，也会走到 c 点。

所以其实 a 点和 b 点是等价的，换句话说，他们最后在环上的位置是等价的。

推广一下，对于任意一个点，假设他向上走走到环里需要的步数为 $x$，那么他就等价于环里距他最近的点往回走 $x$ 步得到的点。

转化为代码，就是：`cir[((dep - from) % sz + sz) % sz + 1]`，其中 $cir$ 存的是环的编号，从 1 开始，$sz$ 是指环的大小，$from$ 是指离他最近的点**是环中的第几个。**

这几个都是可以在第二次遍历基环树的时候很简单的得到。具体可以看代码。

## 3. 代码

注意由于有多组数据，不能使用 `memset` 之类的，而且读入的时候要直接转化为基环树上的编号。

码风略丑，请见谅。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1e6 + 10, M = N << 1;
int h[N], e[M], ne[M], idx;
int cir[N], tot, ed[N], cnt, fu[N];
int n, m, blk[N];
char str[N];
bool ins[N], vis[N], onc[N], abl[N];

void dfs_c(int x, int from)//找环
{
	ins[x] = vis[x] = true;
	for (int i = h[x]; ~i; i = ne[i])
	{
		int j = e[i];
		if (i == (from ^ 1)) continue;
		fu[j] = x;
		if (!vis[j]) dfs_c(j, i);
		else if (ins[j]){
			for (int k = x; k != j; k = fu[k]) cir[++ cnt] = k, onc[k] = true;
			cir[++ cnt] = j, onc[j] = true;
			ed[++ tot] = cnt;
			if ((i & 1)) reverse(cir + ed[tot - 1] + 1, cir + ed[tot] + 1);
		}//注意此时如果 i & 1 的话，找到的环和我们的环是相反的，我们要调换过来
	}
	ins[x] = false;
}

void dfs_d(int x, int cirst, int dep, int sz)//cirst 表示环在 cir 数组里开始的位置，dep 是指当前的深度（我为了方便，加上了出发点的编号，方便直接计算，无需多余传参）
{
	abl[cirst + (-1 * dep % sz + sz) % sz] |= blk[x];
	vis[x] = 1;
	for (int i = h[x]; ~i; i = ne[i])
	{
		if (vis[e[i]] || onc[e[i]]) continue;
		dfs_d(e[i], cirst, dep - 1, sz);
	}
}

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void link(int a, int b){add(a, b), add(b, a);}
int get(int i, int j){return (i - 1) * m + j;}//转换编号

int main()
{
	int t;cin >> t;
	while (t --)
	{
		scanf("%d %d", &n, &m);
		idx = cnt = tot = 0;
		for (int i = 1; i <= n * m; ++ i) h[i] = -1, blk[i] = onc[i] = abl[i] = 0;
		for (int i = 1; i <= n; ++ i)
		{
			scanf("%s", str + 1);
			for (int j = 1; j <= m; ++ j) blk[get(i, j)] = str[j] == '0';
		}
		for (int i = 1; i <= n; ++ i)
		{
			scanf("%s", str + 1);
			for (int j = 1; j <= m; ++ j)
				switch (str[j])
				{
					case 'L' : link(get(i, j), get(i, j - 1));break;
					case 'R' : link(get(i, j), get(i, j + 1));break;
					case 'U' : link(get(i, j), get(i - 1, j));break;
					case 'D' : link(get(i, j), get(i + 1, j));break;
				}
		}
		for (int i = 1; i <= n * m; ++ i) vis[i] = 0;
		for (int i = 1; i <= n * m; ++ i)
			if (!vis[i]) dfs_c(i, -1);
		for (int i = 1; i <= n * m; ++ i) vis[i] = 0;
		for (int i = 1; i <= tot; ++ i)
			for (int j = ed[i - 1] + 1; j <= ed[i]; ++ j) dfs_d(cir[j], ed[i - 1] + 1, j - ed[i - 1] - 1, ed[i] - ed[i - 1]);
		int tblk = 0;
		for (int i = 1; i <= cnt; ++ i) tblk += abl[i];
		printf("%d %d\n", cnt, tblk);
	}
	return 0;
}
```



---

