# [ABC272D] Root M Leaper

## 题目描述

有一个大小为 $N\times N$ 的方格图（网格）。在本题中，我们所说的方格 $(i,j)$ 指网格从上往下数第 $i$ 行，从左往右数第 $j$ 列。

最开始，有一个棋子位于方格 $(1,1)$ 。现在你可以进行下面这个操作若干次：

+ 当前棋子位于 $(i,j)$ ，那么移动它到一个距离它刚好 $\sqrt{M}$ 的点（不超出网格）。

本题中的“**距离**”，指欧几里得距离。即方格 $(i,j)$ 与 $(k,l)$ 的距离是 $\sqrt{(i-k)^2+(j-l)^2}$ 。

现在对于整个网格，请你确定棋子能否到达方格 $(i,j)$ 。如果可以，输出到达它的最少操作次数；如果不行，输出 ```-1``` 。

## 说明/提示

- $ 1\ \le\ N\ \le\ 400 $
- $ 1\ \le\ M\ \le\ 10^6 $
- 输入全为整数


对于**样例1**，你可以把棋子通过一定次数的操作挪到这个方格图的任意位置。

比如说，我们可以通过如下操作把棋子移到 $(2,2)$ ：

1. 开始棋子在 $(1,1)$ 。 $(1,1)$ 到 $(1,2)$ 的距离刚好是 $\sqrt 1$ ，所以我们把它移到 $(1,2)$ 。
1. 现在棋子在 $(1,2)$ 了。$(1,2)$ 到 $(2,2)$的距离也刚好是 $\sqrt 1$ ，所以我们就把它移到了 $(2,2)$ 。

## 样例 #1

### 输入

```
3 1```

### 输出

```
0 1 2
1 2 3
2 3 4```

## 样例 #2

### 输入

```
10 5```

### 输出

```
0 3 2 3 2 3 4 5 4 5
3 4 1 2 3 4 3 4 5 6
2 1 4 3 2 3 4 5 4 5
3 2 3 2 3 4 3 4 5 6
2 3 2 3 4 3 4 5 4 5
3 4 3 4 3 4 5 4 5 6
4 3 4 3 4 5 4 5 6 5
5 4 5 4 5 4 5 6 5 6
4 5 4 5 4 5 6 5 6 7
5 6 5 6 5 6 5 6 7 6```

# 题解

## 作者：DYYqwq (赞：11)

# 题意

你每步可以走 $\sqrt{M}$ 格。求问对于点 $(i , j)$ 最少走多少步，若走不到，输出 $-1$。

# Solution

很明显，这是一道 dfs 或 bfs，但是 dfs 会重复算很多遍，时间复杂度是错的，所以只能用 bfs。

根据题目， $\sqrt{M}$ 格指的是**欧几里得距离**，即

$$ \sqrt{ (i - k) ^ 2 + (j - l) ^ 2 } = \sqrt{M} $$

$$ (i - k) ^ 2 + (j - l) ^ 2 = M $$
我们不需要对于每个节点都计算出可以向哪里走，**只**需要一个初始化算出 dfs 或 bfs 模板中所需的偏移量 $dx$ $dy$。那究竟怎么办呢？我们就假设我们处在 $(0 , 0)$ 点，那原方程就变为了：

$$ (0 - k) ^ 2 + (0 - l) ^ 2 = M $$

$$ k ^ 2 + l ^ 2 = M $$

那我们直接 $O(n^2)$ 枚举 $k,l$ ，判断 $ k ^ 2 + l ^ 2 $ 是否为 $M$，将 $k,l$ 记录下来， **接着找**就可以了。

如果有和我一样不知道为啥**接着找**而不是 **break** 的同学，看[这里](https://www.luogu.com.cn/paste/x9tc7g5e)。

那还有一个问题，万一我找不到怎么办？没有符合要求的   $k,l$ 怎么办？比如说 $M = 6$ 的情况？显然，你就一步都走不出去了，所以除了第 $1$ 个点输出 $0$ 之外，其他点都无法到达，输出 $-1$。

记录完 $k,l$ 即偏移量 $dx$ $dy$ 后，就是正常的 bfs  了，没什么可说的，直接上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int x , y;
};
queue<node> q;
int n , m;
bool flag = false; // 是否能走出去
int a , b;
int cnt = 0; // 每一步有几种走法
int dx[100010] , dy[100010]; // 偏移量，100000个 应该够了吧
int ans[410][410]; // 走到每个点所需的最小步数
bool in(int x , int y) // 是否在边界内
{
    return x <= n && x >= 1 && y <= n && y >= 1;
}
void bfs() // 正常bfs，不解释
{
    q.push({1 , 1});
    ans[1][1] = 0;
    while(!q.empty())
    {
        node tmp = q.front();
        q.pop();
        for(int i = 1 ; i <= cnt ; i ++)
        {
            int nx = tmp.x + dx[i];
            int ny = tmp.y + dy[i];
            if(in(nx , ny) && ans[nx][ny] > ans[tmp.x][tmp.y] + 1)
            {
                ans[nx][ny] = ans[tmp.x][tmp.y] + 1;
                q.push({nx , ny});
            }
        }
    }
}
void init() // 每一步的走法
{
	// x+ , y+
    dx[++ cnt] = a;
    dy[cnt] = b;
    
    // x+ , y-
    dx[++ cnt] = a;
    dy[cnt] = -1 * b;
    
    // x- , y+
    dx[++ cnt] = -1 * a;
    dy[cnt] = b;
    
    // x- , y-
    dx[++ cnt] = -1 * a;
    dy[cnt] = -1 * b;
}
int main()
{
    scanf("%d%d" , &n , &m);
    for(int i = 0 ; i <= n ; i ++)
    {
        for(int j = 0 ; j <= n ; j ++)
        {
            if(i * i + j * j == m)
            {
                a = i; // 行数 + a
                b = j; // 列数 + b
                init(); // 进行dx,dy的
                flag = true; // 有可以走的地方啦qwq
            }
        }
    }
    if(!flag) // 走不出去力（悲
    {
        for(int i = 1 ; i <= n ; i ++)
        {
            for(int j = 1 ; j <= n ; j ++)
            {
                if(i == 1 && j == 1) printf("0 "); // 初始点
                else printf("-1 "); // 除了初始点，都是-1
            }
            printf("\n");
        }
        return 0;
    }
    memset(ans , 0x3f , sizeof(ans));
    ans[1][1] = 0;
    bfs();
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= n ; j ++)
            printf("%d " , ans[i][j] == 0x3f3f3f3f ? -1 : ans[i][j]); // 有的地方由于特殊原因哪怕可以走，也到不了，所以需要特判一下qwq
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Tmbcan (赞：4)

## [AT_abc272_d [ABC272D] Root M Leaper](https://www.luogu.com.cn/problem/AT_abc272_d)
### 题目描述
给定一个 $N \times M$ 的网格，起始时棋子在网格左上角，每次可以移动 $\sqrt M$ 的欧几里得距离，问到达每个格子最少的移动次数。
### 思路
首先考虑预处理出棋子所有可行的移动方式。  
对于每种距离为 $\sqrt M$ 的移动，棋子都可以从左上、左下、右上、右下四个方向移动过来。  
然后做一遍最短路就可以了。
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<queue>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T&x){
	int w=0;x=0;
	char ch = getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9'){
		x = (x<<1)+(x<<3)+(ch^48);
		ch = getchar();
	}
	if(w) x=-x;
}
template <typename T,typename...Args>
inline void read(T&t,Args&...args){
	read(t);read(args...);
}
const int N = 410;
int n,m;
struct node{
	int x,y;
};
queue <node> q;
int dx[N*N],dy[N*N],dis[N][N],cnt;
inline void bfs(int x,int y){
	q.push({x,y});
	while(q.size()){
		node now = q.front();
		q.pop();
		for(int i=1;i<=cnt;++i){
			int tx = now.x+dx[i];
			int ty = now.y+dy[i];
			if(tx<1 || ty<1 || tx>n || ty>n) continue;
			if(dis[tx][ty]>dis[now.x][now.y]+1 || dis[tx][ty]==-1){
				dis[tx][ty] = dis[now.x][now.y]+1;
				q.push({tx,ty});
			}
		}
	}
}
int main(){
	read(n,m);
	for(int i=0;i<=n;++i){
		for(int j=0;j<=n;++j){
			if(i*i+j*j==m){//移动方式
				dx[++cnt] = i;dy[cnt] = j;
				dx[++cnt] = -1*i;dy[cnt] = j;
				dx[++cnt] = -1*i;dy[cnt] = -1*j;
				dx[++cnt] = i;dy[cnt] = -1*j;
			}
		}
	}
	memset(dis,-1,sizeof(dis));//无法到达时答案为-1
	dis[1][1] = 0;
	bfs(1,1);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			printf("%d ",dis[i][j]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：_qingshu_ (赞：2)

# 题意：

有一个 $N\times N$ 的方格图，你一开始在点 $(1,1)$，你每一次可以移动到距离当前点欧几里得距离为 $\sqrt{M}$ 的一个点上，询问到达每一个点的最小步数。

# 思路：

类似单源最短路，我们使用 BFS 完成。

对于一个点距离它欧几里得距离为 $\sqrt{m}$ 的点不会太多，而且 $x$ 与 $y$ 的变化量一定，所以我们经过预处理之后可以节省下大量时间。

然后再 BFS 中判断是否在界内与是否先前被经过，如果都没有就记录最小步数就好了，不用多次经过一个点取 $\min$ 是因为在 BFS 中栈中点的最小步数一定有升序的，所以后面到达该点的步数一定更劣。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int mp[5200][5200];
int tot,x[5200010],y[5200010];
long long cnt=0;
void bfs(){
	queue<pair<int,int> >q;
	q.push({1,1});
	while(!q.empty()){
		auto t=q.front();
		cnt++;
		q.pop();
		for(int i=1;i<=tot;i++){
			int nowx=t.first+x[i],nowy=t.second+y[i];
			if(!mp[nowx][nowy]&&(nowx!=1||nowy!=1)&&nowx<=n&&nowy<=n&&nowx>=1&&nowy>=1){
				mp[nowx][nowy]=mp[t.first][t.second]+1;
				q.push({nowx,nowy});
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(i*i+j*j==m){
				x[++tot]=i;y[tot]=j;
				x[++tot]=-i;y[tot]=-j;
				x[++tot]=i;y[tot]=-j;
				x[++tot]=-i;y[tot]=j;
			}
		}
	}
	bfs();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=1||j!=1){
				cout<<(mp[i][j]==0?-1:mp[i][j])<<" ";
			}
			else{
				cout<<0<<" ";
			}
		}
		cout<<endl;
	}
} 
```

update：

- 修改了文章实质性错误。

---

## 作者：BLuemoon_ (赞：2)

$$\because \sqrt{M} = \sqrt{(i-k)^2+(j-l)^2}$$

$$\therefore M = (i-k)^2+(j-l)^2$$

正常的宽搜偏移量是以 $(i,j)$ 为 $(0,0)$，向四（八）个方向延伸，在这里也一样。

$$\quad \therefore M = (-k)^2+(-l)^2$$

$$\,\, =k^2+l^2$$

直接枚举 $\sqrt{M} = \sqrt{10^6} = 10^3$ 即可，别忘记往回走，也就是 $-10^3$。

然后就是正经的宽搜模版。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> dx,dy; //偏移量，不知道个数，直接用vector存
queue<pair<int,int> > q; //bfs队列，注意空格
int n,m,cnt,a[405][405];
void bfs() //用求出的偏移量bfs
{
  fill(a[0],a[403]+403,-1);
  a[0][0]=0;
  q.push(make_pair(0,0));
  while(q.size())
  {
    pair<int,int> x;
    x=q.front();
    q.pop();
    for(int i=0;i<cnt;i++)
    {
      int xx=x.first+dx[i],yy=x.second+dy[i];
      if(xx>=0&&xx<n&&yy>=0&&yy<n&&a[xx][yy]==-1)
      {
        a[xx][yy]=a[x.first][x.second]+1;
        q.push(make_pair(xx,yy));
      }
    }
  }
}
int main()
{
  cin>>n>>m;
  for(int i=-1000;i<=1000;i++) //枚举i^2+j^2
  {
    for(int j=-1000;j<=1000;j++)
    {
      if(i*i+j*j==m)
        cnt++,dx.push_back(i),dy.push_back(j); //可以达到，加入vector
    }
  }
  bfs();
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
      cout<<a[i][j]<<" ";
    cout<<"\n";
  }
  return 0;
}
```

---

## 作者：robinyqc (赞：2)

[我的翻译！](https://www.luogu.com.cn/blog/robinyqc-blog/abc272d-root-m-leaper)

## 思路
考虑广搜，棋子第一次到达某个方格用的步数就是这个方格的答案。但不要盲目地搜，需要纸上计算一下位于 $(X,Y)$ 的棋子，如果已知目标点的横坐标 $x$，求目标点的纵坐标 $y$。下面是推导过程：


------------


1. 求出 $x$ 的范围。设 $L=\sqrt M$，因为距离为 $L$，$x$ 是整数，横坐标应满足 
$$\hspace9ex\lceil X-L\rceil \le x \le \lfloor X+L\rfloor\hspace10ex (1)$$
即
$$\hspace10ex\  X-\lfloor L\rfloor \le x \le  i+\lceil L\rceil\hspace10ex (2)$$

2. 由题意可知:
$$\hspace4ex \sqrt {(X-x)^2+(Y-y)^2}=\sqrt M \hspace10ex(3)$$
$$ \ \ \iff (X-x)^2+(Y-y)^2=M \hspace11ex(4)$$

现在 $M,(X-x)^2$ 是已知的，我们假设 $\Delta=M-(X-x)^2$，由 $(2)$ 可得， $\Delta \ge 0$。
$$(4) \iff Y^2-2Yy+y^2=\Delta \hspace15ex (5)$$

把 $y$ 当成**主元**，求解一元二次方程 $y^2-2Yy+(Y^2-\Delta)=0$。

解得： 
$$\hspace12ex y=Y\pm \sqrt \Delta \hspace20ex (6)$$

显然，若 $\Delta> 0$，一个 $x$ 对应两个 $y$。

实际上，这个题也可以用圆的方程数形结合来考虑：目标点**共圆**，半径为 $\sqrt M$，由一个单位圆投影加平移得到。过程计算量差不多。


------------
由于 $(x,y)$ 是整点，应当满足 $\sqrt\Delta\in\mathbb{N}_+$ 且 $x,y\in[1,N]$，这里特判一下即可。如果不满足，就不加入广搜队列。复杂度： $O(N^2\sqrt M)$。实际上会低一些，因为在极限情况下，$\sqrt M$ 远远超过方阵最远距离（对角线），可以在代码里优化到最多 $O(N^3)$。并且时限 2000ms，可过。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,step;
	node(int x,int y,int step):x(x),y(y),step(step){}//构造函数
};queue<node>q;
bool check(int d){//判断Δ是否是完全平方数
	int sd=sqrt(d);
	if(sd*sd==d)return true;
	return false;
}int n,m,mp[405][405];
void Upd(int x,int y,int data){
	if(y<=n&&y>=1&&mp[x][y]==-1){
		mp[x][y]=data;
		q.push(node(x,y,data));
	}
}

signed main(){
	cin>>n>>m;
	memset(mp,-1,sizeof(mp));
  	/*小技巧：初始化为-1，既可以判断是否访问，
  	又可以在无法访问时报错*/
	mp[1][1]=0;
	q.push(node(1,1,0));
	while(!q.empty()){
		node h=q.front();q.pop();
		int lim=sqrt(m),i=h.x,j=h.y;//int 类型已经帮我们向下取整了
		for(int k=max(1,h.x-lim);k<=min(n,h.x+lim);k++){//max 和 min 函数帮我们逃离过大的 m 导致的问题
			int delta=m-(i-k)*(i-k);
			if(check(delta)){
				Upd(k,j+sqrt(delta),h.step+1);
				Upd(k,j-sqrt(delta),h.step+1);
			}
		}//这里的 k 相当于枚举可能的 x
	}for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",mp[i][j]);
		}puts("");
	}
	return 0;
}

```


---

## 作者：liruixiong0101 (赞：2)

## 题意简述：
给你一个 $n\times n$ 的矩阵，再给你一个数 $m$ 你可以移动恰好 $\sqrt{m}$ 的距离（这里的距离指的是欧几里得距离，[不会的戳这里](https://blog.nowcoder.net/n/d3761629c51649e897e7d3ff2a72763d)），请问你从 $(1,1)$ 开始，到每个点的距离是多少（不能达到的输出 $-1$）。

## 思路：
这道题没有告诉你移动的行与列的数值，由于 $(i,j)$ 与 $(k,l)$ 的距离为 $\sqrt{(i-k)^2+(j-l)^2}$，由此我们可以求出移动的行与列的数值，不懂得可以化个式子理解一下。
$$\sqrt{(i-k)^2+(j-l)^2}=\sqrt{m}$$
$$(i-k)^2+(j-l)^2=m$$
所以我们可以枚举 $i-k$ 的数值若 $\sqrt{m-(i-k)^2}$ 是一个整数，那么 $\pm{(i-k)}$ 和 $\pm{(n-l)}$ 就是移动的行与列的数值。  
代码如下：
```cpp
const int N = 405 , M = 1e6 + 5;
int dx[M] , dy[M] , td;
void getd(){
	for(int i = 0; i * i <= m; i++){//枚举i-k
		int x = i , y;
		if(sqrt(m - x * x) != (int)sqrt(m - x * x)) continue;//若不为整数跳过
		y = sqrt(m - x * x);
		dx[++td] = x , dy[td] = y;
		dx[++td] = x , dy[td] = -y;
		dx[++td] = -x , dy[td] = y;
		dx[++td] = -x , dy[td] = -y;//把所有的移动的行与列的数值全算出来
	}
	return;
}
```
求出了移动的行与列的数值可以直接 bfs 一遍，求出 $(1,1)$ 到所有点的最短距离即可。  
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 405 , M = 1e6 + 5;
int dx[M] , dy[M] , td;
int n , m;
void getd(){
	for(int i = 0; i * i <= m; i++){
		int x = i , y;
		if(sqrt(m - x * x) != (int)sqrt(m - x * x)) continue;
		y = sqrt(m - x * x);
		dx[++td] = x , dy[td] = y;
		dx[++td] = x , dy[td] = -y;
		dx[++td] = -x , dy[td] = y;
		dx[++td] = -x , dy[td] = -y;
	}
	return;
}
void bfs(){}//bfs代码就不写了
int main(){
	scanf("%d%d" , &n , &m);
	getd();
	bfs();
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			printf("%d " , dis[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[[ABC272D] Root M Leaper](https://atcoder.jp/contests/abc272/tasks/abc272_d)

Atcoder problems 评分：$\color{SeaGreen}{804}$。

一道不错的广搜题目。

首先考虑什么情况下移动的距离刚好是 $\sqrt{M}$。根据勾股定理，不难发现当横坐标变化 $x$，纵坐标变化 $y$ 时只要满足 $x^2+y^2=M$，就刚好移动了 $\sqrt{M}$ 个单位长度。

枚举 $x,y$，将满足条件的 $x,y$ 存进方向数组里，对于每组 $(x,y)$ 都有 $8$ 个方向。枚举 $(x,y)$ 的时间复杂度为 $O(\sqrt{M})$。

```cpp
for(int i=1;i*i<=m;i++)
{
	int j=sqrt(m-i*i);
	if(j*j==m-i*i)
	{
		if(i!=j) r[++tot]={i,j};r[++tot]={-i,j};r[++tot]={i,-j};r[++tot]={-i,-j};
		r[++tot]={j,i};r[++tot]={-j,i};r[++tot]={j,-i};r[++tot]={-j,-i};
	}
}
```

广搜。从 $(1,1)$ 开始搜起，对于队列中每个点 $(x,y)$，枚举 $(x,y)$ 移动 $\sqrt{M}$ 个长度可以到达的所有点。若枚举到的点未到达，则该点到达的步数为到达点 $(x,y)$ 的步数加 $1$，并将该点加入队列。
```cpp
queue<pii>q;
	q.push(mp(1,1));d[1][1]=0;vis[1][1]=1;
	while(!q.empty())
	{
		int x=q.front().first,y=q.front().second;q.pop();
		for(int i=1;i<=tot;i++)
		{
			int xx=x+r[i].dx,yy=y+r[i].dy;
			if(xx>=1&&xx<=n&&yy>=1&&yy<=n)
			{
				if(!vis[xx][yy]) d[xx][yy]=d[x][y]+1,vis[xx][yy]=1,q.push(mp(xx,yy));
			}
		}
	}
```

然后输出到达每个点所需要的步数即可。对于没到达的点，输出 $-1$。

[完整代码](https://atcoder.jp/contests/abc272/submissions/46050804)

如果觉得这篇题解写得好，请不要忘记点赞，谢谢！

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[[ABC272D] Root M Leaper](https://www.luogu.com.cn/problem/AT_abc272_d)

## 分析
宽搜板子，提前预处理好到所有能到达的所形成的向量就好了，存储向量的坐标就行，每次沿着预处理好的能到达的向量走就好了。

每次遍历到某一个点时就更新该点，如果该点记录的最小值比当前更劣，则存入队列中等待处理。

然后在队列中一直弹出点并且处理该点，一直到队列没点了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int mp[410][410];
pair < int , int > nxt[1000000];
int cnt;
queue < pair < int , int > > q;
void bfs()
{
	while(!q.empty())
	{
		pair < int , int > tmp;
		tmp=q.front();
		q.pop();
		int x=tmp.first,y=tmp.second;
//		printf("x=%d y=%d\n",x,y);
		for(int xx=1;xx<=cnt;xx++)
		{
			int i=nxt[xx].first+x,j=nxt[xx].second+y;
//			printf("%d %d %d %d\n",x,y,i,j);
			if(i<1||j<1)continue;
			if(i>n||j>n)continue;
			if(mp[i][j]==0||mp[i][j]>mp[x][y]+1)
			{
				mp[i][j]=mp[x][y]+1;
				q.push(make_pair(i,j));
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i*i+j*j==m)
			{
				mp[i+1][j+1]=1;
				nxt[++cnt]=make_pair(i,j);
				nxt[++cnt]=make_pair(i,-j);				
				nxt[++cnt]=make_pair(-i,j);				
				nxt[++cnt]=make_pair(-i,-j);
				q.push(make_pair(i+1,j+1));
				
			}
		}
	}
	bfs();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==1&&j==1)printf("0 ");
			else if(mp[i][j]==0)
			{
				printf("-1 ");
			}
			else printf("%d ",mp[i][j]);
		}
		putchar(10);
	} 
	return 0;
 } 
```

---

## 作者：kczw (赞：0)

# 题意
从起点 $(1,1)$ 开始，每次只能走到直线距离**刚刚好**为 $m$ 的另外一个点。问每一个点最早多久能够遍历到。

# 思路
看到**最早**和**遍历**，很容易就能想到 BFS。

其次，有一个需要维护的是遍历时移动，因为遍历图时有一个**直线距离刚刚好为** $m$ 的限制，所以我们需要将所有类 $x^2+y^2=m$ 的 $x$ 和 $y$ 的移动时偏移的量求出来。看到 $m$ 的极限大小为 $10^6$，只需要跑一个 $\sqrt{m}$ 的循环枚举一下就可以了。

# 实现
```cpp
#include<iostream>
#include<math.h>
#include<queue>
#define N 405
#define M 100005
using namespace std;
int n,m,tot,map[N][N],X[M],Y[M];//开大一点点，防爆
void bfs(int x,int y){
	queue<pair<int,int>> q;
	q.push({x,y});
	while(!q.empty()){
		x=q.front().first;y=q.front().second;q.pop();
		for(int j=1;j<=tot;j++){
			if(x-X[j]>=1&&y-Y[j]>=1&&map[x-X[j]][y-Y[j]]>map[x][y]+1)q.push({x-X[j],y-Y[j]}),map[x-X[j]][y-Y[j]]=map[x][y]+1;
			if(x+X[j]<=n&&y+Y[j]<=n&&map[x+X[j]][y+Y[j]]>map[x][y]+1)q.push({x+X[j],y+Y[j]}),map[x+X[j]][y+Y[j]]=map[x][y]+1;
			if(x+X[j]<=n&&y-Y[j]>=1&&map[x+X[j]][y-Y[j]]>map[x][y]+1)q.push({x+X[j],y-Y[j]}),map[x+X[j]][y-Y[j]]=map[x][y]+1;
			if(x-X[j]>=1&&y+Y[j]<=n&&map[x-X[j]][y+Y[j]]>map[x][y]+1)q.push({x-X[j],y+Y[j]}),map[x-X[j]][y+Y[j]]=map[x][y]+1;
		}
	}
}int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i*i<=m;i++){
		int j=sqrt(m-i*i);//是否合格
		if(j*j+i*i==m){
			X[++tot]=i;
			Y[tot]=j;
			X[++tot]=j;
			Y[tot]=i;
		}
	}for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		map[i][j]=1e9;//初始值
	map[1][1]=0;
	bfs(1,1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)printf("%d ",map[i][j]==1e9?-1:map[i][j]);
		printf("\n");
	}return 0;
}
```


---

## 作者：Hog_Dawa_IOI (赞：0)

使用 **BFS** 求解，从点 $(1,1)$ 开始更新每个点。      
### Part1：考虑如何转移。      
由题可得：对于当前的点 $(i,j)$，如果我们想要移动到 $(k,l)$，那么必须满足  $ \sqrt{(i-k)^2+(j-l)^2} = \sqrt M$。      
两边平方，得 $(i-k)^2+(j-l)^2=M$。    
那么我们可以直接暴力枚举 $i-k$ 和 $j-l$，找到所有满足要求的解。    
注意只需枚举正整数解即可，因为负整数解就是对应正整数解的相反数。  
还有就是 $\begin{cases}i-k=x,\\j-l=y.\end{cases}$ 和 $\begin{cases}i-k=y,\\j-l=x.\end{cases}$ 是不同的两组解。   
因为 $M \leq 10^6$，所以只需枚举到 $1000$ 即可。
### Part2：开始搜索。
假设此时我们已经求出了 $n$ 组正整数解，第 $a$ 组解为 $\begin{cases}i-k=x_a,\\j-l=y_a.\end{cases}$   
那么对于点 $(i,j)$ ，我们可以到达 $(i+x_a,j+y_a),(i+x_a,j-y_a),(i-x_a,j+y_a),(i-x_a,j-y_a)$ 这四个点。     
更新最小步数即可。    

下面是参考代码。    
需要注意初始化，把答案数组初始化为 $-1$。   
祝大家 **AC** 快乐。
```cpp
#include<stdio.h>
#include<string.h>
long long n,m,s[405][405],i,j=1,ss1[1005],ss2[1005];
struct sss{int s1,s2;}data[1000005];
bool check(long long a,long long b)
{
    if(a<1||a>n) return 0;
    if(b<1||b>n) return 0;
    if(s[a][b]^(-1)) return 0;
    return 1;
}
int main()
{
    memset(s,-1,sizeof(s)),s[1][1]=0;
    scanf("%lld%lld",&n,&m);
    for(int num1=0;num1<=1000&&num1*num1<=m;num1++) for(int num2=0;num2<=1000&&num1*num1+num2*num2<=m;num2++) if(num1*num1+num2*num2==m) ss1[++ss1[0]]=num1,ss2[++ss2[0]]=num2;
    data[1].s1=1,data[1].s2=1;
    while(i<j)
    {
        i++;
        for(int k=1;k<=ss1[0];k++)
        {
            if(check(data[i].s1+ss1[k],data[i].s2+ss2[k])) data[++j].s1=data[i].s1+ss1[k],data[j].s2=data[i].s2+ss2[k],s[data[i].s1+ss1[k]][data[i].s2+ss2[k]]=s[data[i].s1][data[i].s2]+1;
            if(check(data[i].s1-ss1[k],data[i].s2-ss2[k])) data[++j].s1=data[i].s1-ss1[k],data[j].s2=data[i].s2-ss2[k],s[data[i].s1-ss1[k]][data[i].s2-ss2[k]]=s[data[i].s1][data[i].s2]+1;
            if(check(data[i].s1+ss1[k],data[i].s2-ss2[k])) data[++j].s1=data[i].s1+ss1[k],data[j].s2=data[i].s2-ss2[k],s[data[i].s1+ss1[k]][data[i].s2-ss2[k]]=s[data[i].s1][data[i].s2]+1;
            if(check(data[i].s1-ss1[k],data[i].s2+ss2[k])) data[++j].s1=data[i].s1-ss1[k],data[j].s2=data[i].s2+ss2[k],s[data[i].s1-ss1[k]][data[i].s2+ss2[k]]=s[data[i].s1][data[i].s2]+1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) printf("%lld ",s[i][j]);
        printf("\n");
    }
}
```

---

## 作者：DengDuck (赞：0)

大水题，就是一个搜索，类似于朴素的骑士最短路问题。

我们从 $(1,1)$ 开始更新每一个点。

由于我们要求走到距离其欧式距离为 $M$ 的点，设我们横坐标移动的距离为 $x$，纵坐标移动距离为 $y$。

则我们需要寻找这个方程的所有解：

$$
x^2+y^2=M
$$

我们可以只枚举正整数 $x,y$ 其他负数的解也顺便出来了。

但是枚举 $x,y$ 加上 BFS 时间复杂度为 $O(n^4)$，需要优化。

发现枚举 $x$ 即可找出对应的 $y$ 或判断无解，所以只枚举 $x$ 即可，时间复杂度 $O(n^3)$，足已通过。 

```cpp
#include<bits/stdc++.h>
#define LL int
using namespace std;
const LL N=505;
LL n,m,dis[N][N],vis[N][N];
queue<pair<LL,LL> >q;
void tr(LL x,LL y,LL xx,LL yy)//尝试使用 (x,y) 的答案更新 (xx,yy)
{
	if(xx<=0||yy<=0||n<xx||n<yy)return;
	if(dis[xx][yy]<=dis[x][y]+1)return;
	dis[xx][yy]=dis[x][y]+1;
	if(!vis[xx][yy])q.push({xx,yy});
	vis[xx][yy]=1;
}
int main()
{
	scanf("%d%d",&n,&m);
	memset(dis,127,sizeof(dis));
	dis[1][1]=0;
	q.push({1,1});
	while(!q.empty())
	{
		LL x=q.front().first,y=q.front().second;
		vis[x][y]=0;
		q.pop();
		for(int i=0;i<=n;i++)
		{
			if(i*i>m)continue;
			LL t=sqrt(m-i*i);
			if(t*t+i*i!=m)continue;
			tr(x,y,x+i,y+t);
			tr(x,y,x-i,y+t);
			tr(x,y,x+i,y-t);
			tr(x,y,x-i,y-t);
			tr(x,y,x+t,y+i);
			tr(x,y,x-t,y+i);
			tr(x,y,x+t,y-i); 
			tr(x,y,x-t,y-i);
		} 
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(dis[i][j]==dis[0][0])printf("-1 ");
			else printf("%d ",dis[i][j]);
		}
		printf("\n"); 
	}
}
```

---

