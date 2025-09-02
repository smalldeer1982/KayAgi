# King's Path

## 题目描述

有一个国王站在一个 $10^9 \times 10^9$ 的国际象棋棋盘上。

规定第 $i$ 行第 $j$ 列的位置表示为 $(i, j)$。

在给定的国际象棋棋盘上有一些格子是允许通过的。

国际象棋棋盘的所有允许通过的格子都以下面所述的形式的形式给出。

一共 $n$ 段，每段用三个整数 $r_i, a_i, b_i\ (a _ i \le b _ i)$ 表示，意思是在 $r_i$ 行中第 $a_i$ 个格子到第 $b_i$ 个格子是允许通过的。

国王可以移动到与它相邻的任意一个格子里（只能走一步）。

如果两个格子有至少一个公用的点，那么就认为他们是相邻的。

求出国王从 $(x _ 0, y _ 0)$ 移动至 $(x _ 1, y _ 1)$ 的最少步数。

## 说明/提示

$1 \le x_0, y_0, x_1, y_1 \le 10^9$

$1\le n \le 10^5$

$1 \le r_i, a_i, b_i \le 10^9$

$a_i \le b_i$


保证国王的初始和最终位置是允许通过的格子。

保证国王的初始和最终位置不一致。

保证所有给定部分的总长度不超过 $10^5$ 。

## 样例 #1

### 输入

```
5 7 6 11
3
5 3 8
6 7 11
5 2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4 3 10
3
3 1 4
4 5 9
3 10 10
```

### 输出

```
6
```

## 样例 #3

### 输入

```
1 1 2 10
2
1 1 3
2 6 10
```

### 输出

```
-1
```

# 题解

## 作者：Alex_Wei (赞：6)

观察到一句话：

```It is guaranteed that the total length of all given segments doesn't exceed 100000```

即线段总长不超过 $10^5$

那还等什么？！直接 ```bfs``` 暴力艹啊！

因为坐标很大，所以把坐标 ```hash``` 之后存到一个 ```map``` 里面即可

---

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct pos{
	ll x,y,val,st;
};
queue <pos> q;
map <ll,bool> mp;
ll a,b,c,d,n,aim;
ll get(ll x,ll y){return x*1e9+y;}
int main()
{
	cin>>a>>b>>c>>d>>n,aim=get(c,d);
	if(c-a>n)cout<<-1,exit(0);
	for(int i=0;i<n;i++){
		ll w,l,r;
		cin>>w>>l>>r;
		for(ll j=l;j<=r;j++)
			mp[get(w,j)]=1;
	}
	q.push((pos){a,b,get(a,b),0}),mp[get(a,b)]=0;
	while(q.size()){
		pos t=q.front();
		q.pop();
		if(t.val==aim)cout<<t.st,exit(0);
		for(int i=-1;i<2;i++)
			for(int j=-1;j<2;j++)
				if(i!=0||j!=0){
					ll xx=t.x+i,yy=t.y+j,k=get(xx,yy);
					if(xx>0&&yy>0&&xx<=1e9&&yy<=1e9&&mp[k])
						mp[k]=0,q.push((pos){xx,yy,k,t.st+1});
				}
	}
	cout<<-1;
	return 0;
}
```


---

## 作者：ATION001 (赞：5)

## 题目描述
现在给你一个棋盘，这个棋盘上有一个棋子，每次棋子可以向周围八个方向走一步，初始时棋子在坐标 $x_0,y_0$，你想要移动棋子使其到达坐标 $x_1,y_1$，问最少要移动几次？如果不能到达，请输出 $-1$。
## 思路
~~这显而易见就是搜索。~~

这题就是用 bfs 遍历一下，开个队列，把每次到达的合法的点都扔进去，记录步数开个数组记录一下承接上一步的值 $+1$。

但由于数据范围特别~~凉~~良心，达到了恐怖的 $10^9$，很显然普通数组逆天了也不可能开到 $10^9\times 10^9$，于是我就开了个 map 类型，不知道 map 的用法的童鞋[点这里](https://blog.csdn.net/aoying2450/article/details/101860376)。

为啥用 map 来存储呢？因为   map 类型很神奇,而且  unordered_map **不支持** pair 类型。map 大小取决于你定义的范围，比如你定义的第一个类型是 int，那么它的范围就是 $-2^{31}$ 到 $2^{31}-1$。**请注意，这里是指下标**。

解决了存储范围的难题剩下的就是 bfs 模板，**有八个方向**，然后就是代码啦。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int xa,xb,ya,yb,n,r,a,b,xyx[10][10]={{1,1},{1,0},{1,-1},{0,-1},{0,1},{-1,-1},{-1,0},{-1,1}};
map<pair<int,int>,int>mp,b2;
queue<pair<int,int>>q;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>xa>>xb>>ya>>yb>>n;
	for(int i=1;i<=n;i++){
		cin>>r>>a>>b;
		for(int j=a;j<=b;j++){
			b2[{r,j}]=1;
		}
	}
	q.push({xa,xb});
	while(q.size()){
		auto p=q.front();
		q.pop();
		for(int i=0;i<8;i++){
			int dx=p.first+xyx[i][0],dy=p.second+xyx[i][1];
			if(b2[{dx,dy}]&&!mp[{dx,dy}]){
				mp[{dx,dy}]=mp[{p.first,p.second}]+1;
				q.push({dx,dy});
			}
		}
	}
	cout<<(mp[{ya,yb}]?mp[{ya,yb}]:-1);
	return 0;
}
```

---

## 作者：AKPC (赞：2)

### 思路
由于 $\sum_{i=1}^n(b_i-a_i)\leq10^5$，即最多只能走 $10^5$ 个格子，那么显然用 `bfs` 就能解决问题，注意如果你用 `dfs` 会爆栈！难得写一次 `bfs` 啊。

但是这道题 $1\leq r_i,a_i,b_i\leq10^9$，因此我们要开 $10^{18}$ 大小的数组保存标记和答案，但是如果开普通数组显然不行，因此可以很容易的想到 `map` 来存储。我们可以开以 `pair<int,int>` 作为下标的 `map`，用来保存每个下标对应的值。然后保存每个格子是否可以走，是否走过的状态，以及从出发点到这个格子所需的步数。特判如果走到目标格子就直接输出答案然后退出程序，搜不到直接输出 `-1`。

关于 `pair` 的存储，这边只用了以下几点，其他的大家自行百度。

```cpp
pair<int,int>Pair(x,y);
Pair=make_pair(x,y);
//上两行用途相同，将 (x,y) 存储至 Pair 内
int a=Pair.first,b=Pair.second;
//上面一行中 a 表示 Pair 前面那个值，b 表示 Pair 后面那个值
map<pair<int,int>,bool>mp;
//上面一行使用 pair<int,int> 类型作为下标存储状态
mp[make_pair(x,y)]=1;
//上面一行将 (x,y) 建成 pair<int,int> 类型，然后直接调用它。
//make_pair() 建成的 pair 可以直接被调用。
```
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
const int dx[8]={1,1,1,0,0,-1,-1,-1},dy[8]={1,0,-1,1,-1,1,0,-1};
int ax=read(),ay=read(),bx=read(),by=read(),n=read();
map<pair<int,int>,bool>mp,tmp;
map<pair<int,int>,int>dep;
void bfs(){
	queue<pair<int,int> >que;
	que.push(make_pair(ax,ay));
	while (!que.empty()){
		int x=que.front().first,y=que.front().second;
		que.pop();
		if (x==bx&&y==by){
			cout<<dep[make_pair(x,y)];
			exit(0);
		}
		for (int i=0;i<8;i++){
			pair<int,int>Pair(x+dx[i],y+dy[i]);
			if (mp[Pair]&&!tmp[Pair]){
				tmp[Pair]=1;
				dep[Pair]=dep[make_pair(x,y)]+1;
				que.push(Pair);
			}
		}
	}
	cout<<-1;
}
signed main(){
	while (n--){
		int r=read(),a=read(),b=read();
		for (int i=a;i<=b;i++) mp[make_pair(r,i)]=1;
	}
	bfs();
	return 0;
}
```
### 后续
其实这题如果你不想用 `pair` 也是可以的，把数据类型开成 `long long`，然后如果你想存储 $(x,y)$ 这个坐标，那你可以访问下标 $10^9x+y$ 来存储，这也是万无一失的。但是如果再开大一点就麻烦了，那就要用哈希或者 `__int128`。所以 `pair` 在特定情况下，作用还是很大的。

---

## 作者：xiazha (赞：2)

## 思路

首先，看到题目，你会发现 $n\le 10^5$。所以，这是一个简单的 ```bfs``` 搜索题，~~并且没有任何思维难度~~。

但是，这题有一个值得注意的地方，$r_i$，$a_i$，$b_i \le 10^9$。也就是说，为了不让数组爆掉，此题需要用 ```map``` 来存储棋盘的信息，而且为了存储两个坐标，还需要用到 ```pair``` 与 ```map``` 搭配使用，```map``` 想必大家都会，[这里](https://blog.csdn.net/sevenjoin/article/details/81937695)给大家提供了一些 ```pair``` 的用法，不会的同学可以看看。

另外，题目说国王可以移动到与它相邻的任意一个格子里，这也就意味着此题是八方向搜索，这是一个坑点，要注意千万不要写成四方向。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,s1,s2,e1,e2,p,l,r,nxt[8][2]={0,1,1,0,0,-1,-1,0,-1,-1,1,1,1,-1,-1,1};//nxt 是方向数组 
map<pair<int,int>,int> a,vis,dis;//定义套用 pair 的 map ，a 是记录能走不能走 ，vis 是记录有没有走过 ，dis 是记录走到某点的步数  
void bfs()
{
	queue<pair<int,int>> q;//定义套用 pair 的 map 
	q.push(make_pair(s1,s2));//压队 
	while(!q.empty())
	{
		int x=q.front().first;//上一步行坐标 
		int y=q.front().second;//上一步列坐标 
		q.pop();
		if(x==e1&&y==e2)//判断终点 
		{
			cout<<dis[make_pair(e1,e2)];
			exit(0);
		}
		for(int i=0;i<=7;i++)
		{
			int tx=x+nxt[i][0];//当前行坐标 
			int ty=y+nxt[i][1];//当前列坐标 
			if(a[make_pair(tx,ty)]&&vis[make_pair(tx,ty)]==0)//要能走且之前没走过 
			{
				vis[make_pair(tx,ty)]=1;//标记走过了 
				dis[make_pair(tx,ty)]=dis[make_pair(x,y)]+1;//更新走到当前点用的步数 
				q.push(make_pair(tx,ty));//压队
			}
		}
	}
	cout<<"-1";//走不到就输出 -1 
}
signed main()
{
	cin>>s1>>s2>>e1>>e2>>n;
	for(int k=1;k<=n;k++)
	{
		cin>>p>>l>>r;
		for(int i=l;i<=r;i++) a[make_pair(p,i)]=1;//标记能走 
	}
	bfs();
	return 0;
}
```


---

## 作者：Somusomunia (赞：1)

## 一些发现
题目中，棋盘的大小是 $10^9\times 10^9$ 的，如果直接存，很明显会直接爆掉。

但是题面中这样有一句话在似乎暗示着什么。

It is guaranteed that the total length of all given segments doesn‘t exceed $10^5$。

这就说明我们根本就不需要存整个棋盘，直接存可以走的格子的坐标即可。

## 实现
由于可走的格子不超过 $10^5$ 个，我们直接使用 bfs 搜索。
存坐标的时候用 pair，然后再丢到一个 map 里本题就结束了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct site{
	ll x,y,step;
	site(){step=0;}
	site(ll xx,ll yy,ll st){
		x=xx,y=yy,step=st;
	}
}s,e,now,ne;
ll n,l,r,h;
map<pair<ll,ll>,bool> vis;
queue<site> q;
bool judge(site bej){
	return bej.x>0&&bej.x<=1e9&&bej.y>0&&bej.y<=1e9;
}
int mov[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
void bfs(){
	q.push(s);
	vis[make_pair(s.x,s.y)]=false;
	while(!q.empty()){
		now=q.front();
		q.pop();
		for(int i=0;i<8;i++){
			ne=site(now.x+mov[i][0],now.y+mov[i][1],now.step+1);
			if(ne.x==e.x&&ne.y==e.y){
				cout<<ne.step;
				return ;
			}
			if(vis[make_pair(ne.x,ne.y)]&&judge(ne)){
				vis[make_pair(ne.x,ne.y)]=false;
				q.push(ne);
			}
		}
	}
	cout<<-1;
}
int main(){
	cin>>s.x>>s.y>>e.x>>e.y;
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>h>>l>>r;
		for(ll j=l;j<=r;j++) vis[make_pair(h,j)]=true;
	}
	bfs();
	return 0;
}
```


---

## 作者：CR7_siu (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF242C)

这题要求我们求出移动的最少次数，也就是求最短路，那么我们就考虑 $\texttt{BFS}$ 广度优先搜索来做这道题。

但是，由于这题的棋盘非常的大，有 $10^9 \times 10^9$ 之大，所以我们统计答案该怎么处理呢？

这个时候我们就可以用到 $\texttt{STL}$ 中的 $\texttt{map}$ 来记录答案和标记，并且 unordered_map 是不支持 $\texttt{pair}$ 类型的，所以我们是只能用 $\texttt{map}$ 的。

代码就是一道广搜模板题，只是将二维数组改为了 $\texttt{map}$ 而已，所以不贴。

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF242C)

### $\texttt{Description}$

给定一个棋盘，棋盘上有一个棋子，每次可以向周围八个方向行走，求最少移动的次数。

### $\texttt{Solution}$

这题就是显然易见的广搜求最短路。就是个模板题。

但是由于数据范围非常大，有 $10^9$ 之多，所以我们得开 $10^{18}$ 大小的数组来边界和存储答案，显然是不行的。但是我们还有一个工具 $\texttt{map}$ 可以使用。我们可以用 $\texttt{pair}$ 来存行和列的坐标。 

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;

typedef pair<int, int> Pair;
map<Pair, int> l;
map<Pair, bool> vis;

int n;
int sx, sy, ex, ey;

const int inf = 1e9; // 棋盘大小
const int fx[] = {0, 0, 1, 0, -1, -1, -1, 1, 1};
const int fy[] = {0, 1, 0, -1, 0, -1, 1, -1, 1};

bool check(int xx, int yy) { // 判断点是否能走
	if (xx <= 0 || xx > inf || yy <= 0 || yy > inf) return 0;
	if (vis[{xx, yy}] == false) return 0;
	return 1;
}

void bfs() { // 广搜模板
	queue<Pair> q;
	q.push({sx, sy});
	vis[{sx, sy}] = false;
	
	while (q.empty() == false) {
		Pair u = q.front(); 
		q.pop();
		for (int i = 1; i <= 8; i++) {
			int tx = u.x + fx[i];
			int ty = u.y + fy[i];
			
			if (check(tx, ty) == true) {
				l[{tx, ty}] = l[{u.x, u.y}] + 1;
				vis[{tx, ty}] = false;
				q.push({tx, ty});
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> sx >> sy >> ex >> ey >> n;
	
	while (n--) {
		int r, lt, rt;
		cin >> r >> lt >> rt;
		
		for (int i = lt; i <= rt; i++) vis[{r, i}] = true;
	}
    // 标记能走
	
	bfs();
	cout << (l[{ex, ey}] ? l[{ex, ey}] : -1);
	return 0;
}

```

---

## 作者：Tachibana27 (赞：0)

## 题目大意

给定一个起始坐标，一个终止坐标，以及可行走的格子。问从起始坐标到达终止坐标的最少步数。

## 提要

棋子是可以斜着走的，所以会有 $8$ 个坐标。注意数据范围，棋盘大小是 $10^9\times 10^9$。~~可怜的同学因为这个原地爆炸~~

## 思路

使用 `pair` 来记录当前格子是否可以行走，是否来过，用 `map` 代替原来的二维数组，防止炸空间。最后别忘记要返回 `-1`。其它套板子，详见代码。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

map<pair<int,int>,bool>a,vis;

map<pair<int,int>,int>stp;//a的作用是记录能不能走，vis代表是否来过，stp记录步数 

inline int read(){

   	int s=0;

   	int w=1;

   	char ch=getchar();

   	for(;ch<'0'||ch>'9';ch=getchar())

    	if(ch=='-')

			w=-1;

   	for(;ch>='0'&&ch<='9';ch=getchar())

		s=s*10+ch-'0';

   	return s*w;

}//快读，自动掠过 

int sx,sy,ex,ey;

int n;

queue<pair<int,int> >q;//最好加上空格，否则容易判成位移 

int dx[10]{0,0,0,1,1,1,-1,-1,-1};

int dy[10]{0,-1,1,1,0,-1,-1,0,1};//可以斜着走，所以有8个坐标
	
int bfs(int sx,int sy){
	
	q.push(make_pair(sx,sy));//入队 
	
	while(!q.empty()){
		
		int x=q.front().first;
		
		int y=q.front().second;
		
		q.pop();
		
		if(x==ex&&y==ey)//判断是不是走到目标位置了 
			
			return stp[make_pair(ex,ey)];//走到就返回步数 
			
		for(int i=1;i<=8;i++){
			
			if(!a[make_pair(x+dx[i],y+dy[i])]||vis[make_pair(x+dx[i],y+dy[i])])
			
				continue;
			
			vis[make_pair(x+dx[i],y+dy[i])]=true;//标记来过 
				
			stp[make_pair(x+dx[i],y+dy[i])]=stp[make_pair(x,y)]+1;//记录步数 
				
			q.push(make_pair(x+dx[i],y+dy[i]));//入队 		
			
		}
		
	} 
	
	return -1;//走不到就返回-1 
	
}

int main(){

	sx=read();
	
	sy=read();
	
	ex=read();
	
	ey=read();
	
	n=read();//输入，可简写成cin>>sx>>sy>>ex>>ey>>n; 
	
	for(int i=1;i<=n;i++){
		
		int op,l,r;
		
		op=read();
		
		l=read();
		
		r=read();//输入 
		
		for(;l<=r;l++)
		
			a[make_pair(op,l)]=true;//标记能走 
		
	}
	
	cout<<bfs(sx,sy);//广搜 

	return 0;//撒花！ 
	
}

```

## 总结

~~这是我见过最水的绿题~~只要将二维数组替换成 `map`，其他就是 `BFS` 板子。


---

## 作者：tmp_get_zip_diff (赞：0)

## 思路

1. 用 $vis$ 标记可以走的地方，可以即为 true，不可以即为 false。
2. 由于数据范围很大，所以我们将 $x,y$ 对应成一个数，$vis$ 用 map 即可。
2. 直接 BFS，走过的将 $vis$ 标记为 false，这样就不会 TLE。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long

__inline__ __attribute__((always_inline)) int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch-'0'),ch=getchar();
	return x*f;
}

inline void _write(int x)
{
	if(x>9)_write(x/10);
	putchar((x%10)+'0');
}

__inline__ __attribute__((always_inline)) void write(int x,int f=0)
{
	if(x<0)putchar('-'),x=-x;
	_write(x);
	if(f!=0)putchar(char(f));
}

int n,aa,b,cc,d;
map<int,bool>vis;
struct Node
{
	int x,y,step;
};
int dx[]={0,0,1,-1,1,1,-1,-1};
int dy[]={1,-1,0,0,1,-1,1,-1};

int getdis(int x,int y)
{
	return x*1e9+y;
}

int bfs(int sx,int sy)
{
	queue<Node>q;
	Node cur={sx,sy,0};
	vis[getdis(sx,sy)]=false;
	q.push(cur);
	while(!q.empty())
	{
		cur=q.front();
		q.pop();
		if(cur.x==cc&&cur.y==d)
			return cur.step;
		for(int i=0;i<=7;i++)
		{
			int nx=cur.x+dx[i];
			int ny=cur.y+dy[i];
			if(nx>=0&&ny>=0&&vis[getdis(nx,ny)]==1)
			{
				Node nxt={nx,ny,cur.step+1};
				vis[getdis(nx,ny)]=false;
				q.push(nxt);
			}
		}
	}
	return -1;
}

signed main()
{
	aa=read(),b=read(),cc=read(),d=read(),n=read();
	for(int i=1;i<=n;i++)
	{
		int hang,lt,rt;
		hang=read(),lt=read(),rt=read();
		for(int j=lt;j<=rt;j++)
			vis[getdis(hang,j)]=true;
	}
	write(bfs(aa,b));
	return 0;
}
```

----

---

## 作者：Allanljx (赞：0)

## 思路
因为给定部分的总长度小于等于 $10^5$，所以可以直接 bfs 暴力找。用 $3$ 个 map 分别存当前位置是否走过、当前位置是否允许走、走到当前位置需要多少步。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
map<pair<int,int>,int> p1,p2,dp;
int a1,a2,b1,b2;
int n;
queue<pair<int,int> > q;
int fx[10][2]={1,0,-1,0,0,1,0,-1,-1,-1,-1,1,1,-1,1,1};
void bfs()
{
	q.push(mp(a1,b1));
	while(q.size())
	{
		int x=q.front().first;
		int y=q.front().second;
		q.pop();
		if(x==a2&&y==b2) return;
		for(int i=0;i<8;i++)//枚举下一步 
		{
			int xx=x+fx[i][0];
			int yy=y+fx[i][1];
			if(p1[mp(xx,yy)]&&!p2[mp(xx,yy)])//可以走并且没走过 
			{
				p2[mp(xx,yy)]=1;//标记走过 
				q.push(mp(xx,yy));
				dp[mp(xx,yy)]=dp[mp(x,y)]+1;//步数 
			}
		}
	}
	puts("-1");
	exit(0);
}
signed main()
{
	cin>>a1>>b1>>a2>>b2;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int r,a,b;
		cin>>r>>a>>b;
		for(int j=a;j<=b;j++)
		{
			p1[mp(r,j)]=1;
		}
	}
	bfs();
	cout<<dp[mp(a2,b2)];
}
```

---

## 作者：TsH_GD (赞：0)

### 题意：

给出一个 $ 10^9 \times 10^9 $ 的图，以及两个点的坐标 $(x1,y1)$，$(x2,y2)$，再给出 $n$ 行数，每行有 $r$，$a$，$b$ 三个数，代表第 $r$ 行的第 $a$ 到 $b$ 列是可以走的，现在要从 $(x1,y1)$ 到 $(x2,y2)$，每次能走相邻的 $8$ 个格子，问最小步数，如果不能到达，输出 $-1$。

## 思路：

如果不考虑图的大小的话，是一个十分基础的 bfs 题，但图的范围到 $10^9$，无法开那么大的数组

用 map + pair ，这样一来，即可将 pair 表达的点在 map 中映射为步数，将所有可走的点都标记为 $-1$，如果这个点为 $-1$ 才可以走，然后进行 bfs 即可

### Code:
```cpp
#include<bits/stdc++.h>
const int MOD = 1E9+7;
const int N = 1000000+5;
const int dx[] = {-1,1,0,0,-1,-1,1,1};
const int dy[] = {0,0,-1,1,-1,1,-1,1};
using namespace std;
#define x first
#define y second
map<pair<int,int>,int> mp;
int bfs(pair<int,int> start,pair<int,int> endd) {
	queue<pair<int,int>> Q;
	Q.push(start);
	mp[start]=0;
	while(!Q.empty()) {
		pair<int,int> now=Q.front();
		Q.pop();
		if(now.x==endd.x&&now.y==endd.y)
			return mp[now];
		for(int i=0; i<8; i++) {
			int nx=now.x+dx[i];
			int ny=now.y+dy[i];
			pair<int,int> next(nx,ny);

			if(mp[next]==-1) {
				mp[next]=mp[now]+1;
				Q.push(next);
			}
		}
	}
	return -1;
}
int main() {
	pair<int,int> start,endd;
	int n;
	scanf("%d%d%d%d",&start.x,&start.y,&endd.x,&endd.y);
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		int r,a,b;
		scanf("%d%d%d",&r,&a,&b);
		for(int i=a; i<=b; i++) {
			pair<int,int> temp(r,i);
			mp[temp]=-1;
		}
	}

	int res=bfs(start,endd);
	printf("%d\n",res);
	return 0;
}
```

---

