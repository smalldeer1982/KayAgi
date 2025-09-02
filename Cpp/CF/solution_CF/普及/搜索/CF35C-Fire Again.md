# Fire Again

## 题目描述

**题目大意：**

有 $n\times m$ 棵树组成的矩形，初始时有 $K$ 棵树被点燃了。如果一棵树有相邻的树被点燃，在一分钟之后，这棵树也会被点燃。问最晚点燃的树的坐标（输出任意一个）。

## 样例 #1

### 输入

```
3 3
1
2 2
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
3 3
1
1 1
```

### 输出

```
3 3
```

## 样例 #3

### 输入

```
3 3
2
1 1 3 3
```

### 输出

```
2 2```

# 题解

## 作者：OnlyU (赞：8)

本蒟蒻又来写（shui）题解了。这道题虽然是一道蓝题，但说实话最难的就是翻译。这题就是一道BFS的入门题。实在没什么好讲的。
下为完整AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int v[2001][2001];
int dx[4]= {0,0,1,-1},dy[4]= {1,-1,0,0};
struct node{
	int x,y;
}a,b,c;
queue<node>que;
int ansx,ansy;
void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		int xi,yi;
		cin>>xi>>yi;
		a.x=xi;
		a.y=yi;
		que.push(a);
		v[a.x][a.y]=1;	
	}
	while(!que.empty()){
        b=que.front();
        que.pop();
        ansx=b.x,ansy=b.y;
        for(int i=0; i<4; i++) {
            c.x=b.x+dx[i];
            c.y=b.y+dy[i];
            if(c.x<1||c.x>n||c.y<1||c.y>m)continue;
            if(v[c.x][c.y]==0) {
                v[c.x][c.y]=1;
                que.push(c);
            }
        }
	}	
	cout<<ansx<<" "<<ansy<<endl;
	return;
}
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    solve();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```


---

## 作者：清小秋ovo (赞：7)

# CF35C 题解

**前排提示: 此题要加如下代码 (C++)！！！！**

```cpp
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

比较简单的多源点广搜题目。

火势从一张地图的多个点开始扩散，每一次扩散往上，下，左，右四个方向扩散，求最后一个被覆盖点的位置。

## 解题思路

直接套广搜模板就好了，直接输出队列中的最后一个点做为答案。

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef queue<int> qi;

#define dbg(x) cout<<#x<<" = "<<x<<endl
#define PB push_back
#define MP make_pair
#define sz(x) (int)(x).size()

inline int read()
{
    int f = 1, x = 0; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar();}
    return f * x;
}

int vis[2005][2005]; //标记数组
int d[4][2] = {{1,0},{0,1},{-1,0},{0,-1}}; //4个方向

struct node{
    int x , y; 
};

int n, m, k;

queue<node> q;

int ans_x, ans_y; 

void bfs(){ //常规广搜板子
    while(!q.empty()){
        node cur = q.front();
        ans_x  = cur.x, ans_y = cur.y ;
        q.pop();
        vis[cur.x][cur.y]=1;
        for(int i=0;i<4;i++){
            int x1 = cur.x+d[i][0];
            int y1 = cur.y+d[i][1];
            if(vis[x1][y1])continue;
            if(x1<1||y1<1||x1>n||y1>m)continue;
            node nxt;
            nxt.x = x1, nxt.y = y1;
            vis[x1][y1]=1;
            q.push(nxt);
        }
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    n = read(), m = read(), k = read();
    for(int i=1;i<=k;i++){ //一边读入所有的起点一边推入队列，多源点bfs经典做法
        node n;
        n.x  = read(),n.y = read();
        vis[n.x][n.y]=1;
        q.push(n);
    }
    bfs();
    cout<<ans_x<<" "<<ans_y<<endl;
   return 0;
}


```

然后就可以轻松切掉一题！

---

## 作者：QianianXY (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF35C)

## 前言

比广搜思维和代码难度都更优的解法，一发最优解。

## 题目分析

直接枚举即可。

由题知向上下左右拓展，且每次拓展一格。

则初始点 $A(x_1,y_1)$ 覆盖 $B(x_2,y_2)$ 的拓展次数为曼哈顿距离 $|x_1-x_2|+|y_1-y_2|$。

因此直接枚举所有点 $P(x,y)$ 和初始点，算出离**最近初始点距离最远**的点 $P$，即为答案。

复杂度 $O(nmK)$。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 55
using namespace std;
typedef long long ll;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, m, k, X[N], Y[N], ansx = 1, ansy = 1, ans;

inline int dist(int xa, int ya, int xb, int yb) {return abs(xa - xb) + abs(ya - yb);}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	read(n); read(m); read(k);
	for (rei i = 1; i <= k; i++) read(X[i]), read(Y[i]);
	for (rei i = 1; i <= n; i++)
	{
		for (rei j = 1; j <= m; j++)
		{
			int minn = 1e9;
			for (rei l = 1; l <= k; l++)
				minn = min(minn, dist(X[l], Y[l], i, j));
			if (minn > ans) ansx = i, ansy = j, ans = minn;
		}
	}
	printf("%d %d", ansx, ansy);
	return 0;
}
```


---

## 作者：Grisses (赞：4)

[题面](https://www.luogu.com.cn/problem/CF35C)

本题其实与 [血色先锋队](https://www.luogu.com.cn/problem/P1332) 差不多，就打一个 BFS 就可以了。我们找到最后一个处理的位置，输出就可以了（根据 BFS 的原理，最后一个一定是最远的）。

代码
```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  int n,m,A,ans_a,ans_b;
  struct node{
      int x,y,k;
      node(){}
      node(int a,int b,int c){x=a,y=b;k=c;}
  };
  bool ans[2005][2005];//标记
  queue<node>q;
  signed main()
  {
      freopen("input.txt","r",stdin);
      freopen("output.txt","w",stdout);//题目要求
      scanf("%lld%lld%lld",&n,&m,&A);
      int x,y;
      for(int i=1;i<=A;i++){
          scanf("%lld%lld",&x,&y);
          q.push(node(x,y,1));
      }
      while(!q.empty()){
          node t=q.front();
          q.pop();
          if(ans[t.x][t.y])continue;
          ans[x][y]=1;//标记
          ans_a=t.x,ans_b=t.y;//更新答案
          int x=t.x,y=t.y,k=t.k;
          if(x>1)q.push(node(x-1,y,k+1));
          if(x<n)q.push(node(x+1,y,k+1));
          if(y>1)q.push(node(x,y-1,k+1));
          if(y<m)q.push(node(x,y+1,k+1));//BFS
      }
      printf("%lld %lld",ans_a,ans_b);
      return 0;
  }
```

---

## 作者：Qwertyhero (赞：2)

**题目大意**

- 给定一个 $n\times m$ 的长方形。
- 给定 $K$ 个 **燃烧点** ，每个 **燃烧点** 每个时间单位都会向上下左右延伸,延伸出来的新的 **燃烧点** 也会获得此效果，以此类推。
- 问哪个点被烧着的时间最晚。
- 数据范围：$1 \le n, m \le 2000$，$1 \le k \le 10$。
- 初始燃烧点坐标保证在长方形范围内且不重合。
- 需要加文件读入与输出。

------------

**前提概要**

本蒟蒻第一次写题解，有何不合理的地方请指出，谢谢！

看了一下各位神犇写的题解，大多数是 BFS ，这里再向大家推荐一下曼哈顿算法 （也有一个 dalao 是用曼哈顿做的，不过程序写得比较高深~~上面有一大段我看不懂~~，本蒟蒻写了一个比较简单的版本 ）。

------------

**曼哈顿算法**

曼哈顿算法离不开绝对值。

当我们要求 $(a ,b)$ 点与 $(c, d)$ 点的最短路径且没有障碍时，最短路径一定是 $|a - c| + |b - d|$。

我们要到达目标点，必须竖向到，横向也要到。

这样这道题的难度就从省选降到了入门了。

------------

**对比**

详细的 BFS 算法可以参考其他神犇的题解，蒟蒻在此将 BFS 和曼哈顿算法进行对比。

BFS 算法可以用 queue 进行宽度优先搜索（又称广度优先搜索）一圈一圈地模拟下去，直到找到最优解，相比较曼哈顿算法，用途更为广泛，适用的题目也很多，十分适合“找最优解”。

而曼哈顿就比较局限，只有在没有限制，没有障碍的状态下才成立。但它也有自己的好处，只要可以用它，就可以做的很快，代码也会更加简洁。

综上，BFS 以及曼哈顿各有利弊，适用的范围有所不同，大家可以根据题目理性选择。

**AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
   freopen("input.txt","r",stdin);
   freopen("output.txt","w",stdout);//文件读入输出
	int m,n,k,q,w;
	cin>>m>>n;//读入长方形大小
	cin>>k;//读入有几个初始燃烧点
	int a[k],c[k];
	for(int i=0;i<k;i++)
	cin>>a[i]>>c[i];//初始点坐标（AC出现，好运连连）
	int minn,maxx=-1;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)//枚举所有点
		{
			minn=1e5;//对于这个点最少几个时间单位能烧到
			for(int p=0;p<k;p++)
			{
				if((abs(a[p]-i)+abs(c[p]-j))<minn)
				minn=abs(a[p]-i)+abs(c[p]-j);
			}//核心曼哈顿
			if(minn>maxx)
			{
				maxx=minn;
				q=i;
				w=j;
			}//比较之前枚举过的点，如果时间比其他点还长，就更新maxx；同时q,w记录坐标
		}
	}
	cout<<q<<' '<<w<<endl;//输出完结
	return 0;//养成好习惯
 } 
```


---

## 作者：EuphoricStar (赞：1)

BFS 模板题。

定义 $f_{i,j}$ 为第 $i$ 行第 $j$ 个点被覆盖的时间。

初始时将所有 $f_{i,j}$ 设为 `INF`，读入初始点 $X_i,Y_i$ 时将 $X_i,Y_i$ 入队。

```cpp
    memset(f, 0x7f, sizeof(f));
    scanf("%d%d%d", &n, &m, &k);
    while (k--) {
        int x, y;
        scanf("%d%d", &x, &y);
        q.push({x, y});
        vis[x][y] = 1;
    }
```


之后就是常规的广搜。

```cpp
    while (q.size()) {
        node u = q.front();
        q.pop();
        f[u.x][u.y] = u.step;
        for (int i = 0; i < 4; ++i) {
            int nx = u.x + dx[i], ny = u.y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m) {
                continue;
            }
            if (vis[nx][ny]) {
                continue;
            }
            vis[nx][ny] = 1;
            q.push({nx, ny, u.step + 1});
        }
    }
```

最后取最大的 $f_{i,j}$ 即可。

```cpp
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (f[i][j] > res) {
                res = f[i][j];
                ansx = i;
                ansy = j;
            }
        }
    }
    printf("%d %d", ansx, ansy);
```


---

## 作者：cqbzhyf (赞：0)

首先学习**文件输入输出**，像这样：

```cpp
freopen("你要输入的文件名","r",stdin);
freopen("你要输出的文件名","w",stdout);
```

然后这道题就是简单的搜索了，几个技巧如下：

1.传入队列元素可以直接如下：

```cpp
q.push(Q{x,y});
```

不用单独定义结构体，只不过需要 `c++11`，普通编译器会警告！

2.遍历可以使用一个方向数组，方便又快捷：

```cpp
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};//这是上下左右四个方向
for(int i=0;i<4;++i){
	int dx=t1.x+dir[i][0],dy=t1.y+dir[i][1];
	if(dx>=1&&dx<=n&&dy>=1&&dy<=m&&!vis[dx][dy]){
		vis[dx][dy]=1,++k;
		q.push(Q{dx,dy});
	}
}//使用时这样……
```

然后就没了……

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){int num=0,ch=0;char c=getchar();while(!isdigit(c))ch|=(c=='-'),c=getchar();while(isdigit(c))num=(num<<1)+(num<<3)+(c^48),c=getchar();return ch?-num:num;}
inline void write(int x){if(x>=10)write(x/10);putchar(x%10+'0');}
int n,m,k,dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
bool vis[2005][2005];
struct Q{int x,y;};
queue<Q>q;
inline void bfs(){
	int ax,ay;
	while(q.size()){
		Q t1=q.front();q.pop();
		ax=t1.x,ay=t1.y;
		for(int i=0;i<4;++i){
			int dx=t1.x+dir[i][0],dy=t1.y+dir[i][1];
			if(dx>=1&&dx<=n&&dy>=1&&dy<=m&&!vis[dx][dy]){
				vis[dx][dy]=1,++k;
				q.push(Q{dx,dy});
			}
		}
	}
	write(ax),putchar(' '),write(ay);
}
signed main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1;i<=k;++i){
		int x=read(),y=read();
		q.push(Q{x,y}),vis[x][y]=1;
	}
	bfs();
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

首先，我们发现这道题与 [P1332 血色先锋队](https://www.luogu.com.cn/problem/P1332) 很像，只是在它的基础上求最小值即可，时间复杂度 $O(n\times m\times k)$，具体细节见代码：
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,ans[2005][2005];
struct node{
	int x,y,step;	
};//表示坐标为 (x,y) 时的步数 step
queue<node> q;
inline void bfs(int x,int y){//广度优先搜索模拟蔓延
	q.push(node({x,y,0}));//初始化起点为 0
	while(!q.empty()){
		int x=q.front().x,y=q.front().y,z=q.front().step;
		q.pop();//取出队首
		if((x<1||x>n||y<1||y>m)||ans[x][y]!=-1&&ans[x][y]<=z)
			continue;//当越界或没有已经求得的答案更优时不需要遍历
		ans[x][y]=z;//更新答案
		q.push(node({x-1,y,z+1}));
		q.push(node({x+1,y,z+1}));
		q.push(node({x,y-1,z+1}));
		q.push(node({x,y+1,z+1}));//将它相邻的点入队
	}
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//注意本题要加文件
	scanf("%d%d%d",&n,&m,&a);
	memset(ans,-1,sizeof(ans));
	for(int i=1,x,y;i<=a;++i){
		scanf("%d%d",&x,&y);
		bfs(x,y);//从每个点向外蔓延
	}
	int ax=-1e9,xx,yy;//初始化答案位置以及答案赋极小值
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(ans[i][j]>ax){
				xx=i,yy=j;
				ax=ans[i][j];//更新答案
			}
	printf("%d %d\n",xx,yy);//因为有 SPJ，任意一组答案均可
	return 0;
}
```

---

## 作者：1lgorithm (赞：0)

## ~~广搜模板题~~
就是将每个点入队，然后进行广搜，最后输出队尾元素就行了。

### 上代码
```cpp
#include<iostream>
#include<queue>
using namespace std;
queue <int> quex;
queue <int> quey;
int a[2001][2001],vis[2001][2001];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int n,m,k;
int z;
void bfs(){
	while(quex.size()){
		int xx=quex.front();
		int yy=quey.front();
		quex.pop();
		quey.pop();
		z--;
		if(z==0){
			cout<<xx<<' '<<yy;
			return ;
		}
		for(int i=0;i<4;i++){
			int xxx=xx+dx[i];
			int yyy=yy+dy[i];
			if(xxx<1||xxx>n||yyy<1||yyy>m) continue;
			if(vis[xxx][yyy]==0){
				vis[xxx][yyy]=1;
				quex.push(xxx);
				quey.push(yyy);
			}
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>m>>k;
	z=n*m;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		quex.push(x);
		quey.push(y);
		vis[x][y]=1;
	}
	bfs();
	fclose(stdin);
	fclose(stdout);
}

```


---

## 作者：TLMPEX (赞：0)

思路：其实本题就是求最后被覆盖的点，具体思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ax,ay,vis[2001][2001];//vis为标记数组
int a[4]={-1,0,0,1},b[4]={0,-1,1,0};//方向数组
struct wak{
	int x,y;//坐标
};
queue<wak> q;
int bfs(){
	while(!q.empty()){
		wak f=q.front();
		q.pop();
		ax=f.x,ay=f.y;//置为现在位置，等到最后就是最后覆盖的点的坐标
		for(int i=0;i<4;i++){
			int nx=f.x+a[i],ny=f.y+b[i];
			if(nx>=1&&ny>=1&&nx<=n&&ny<=m&&!vis[nx][ny]){//判断是否在边界条件以内，如果是，则标记次位置，并把此位置入队列
				vis[nx][ny]=1;
				wak t;
				t.x=nx,t.y=ny;
				q.push(t);
			}
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);//文件输入
	freopen("output.txt","w",stdout);//文件输出
	int a,b;
	wak t;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		cin>>a>>b;
		t.x=a,t.y=b;
		vis[a][b]=1;
		q.push(t);
	}
	bfs();
	cout<<ax<<" "<<ay;//输出最后覆盖的点坐标
}
```


---

## 作者：cz666 (赞：0)

## 题意：

一个 $N*M$ 大小的矩阵区域， $K$ 个点在一开始就着火了，之后每一秒都会向四个方向扩展一格，问这个区域里最后被烧到的地方是哪个（显然有多个但是只要求任意输出一个）。

## 思路：

#### 方法一：

由于 $N$ 和 $M$ 都只有 $2000$ 嘛，考虑按照题意模拟，将矩阵区域每个点着火的时间都算出来，然后找一下最后着火的那些点，任意输出即可。时间复杂度 $O(N*M+N*M*K)$ ，空间复杂度 $N*M$ 。

#### 方法二：

上面的方法不难看出对于空间是十分浪费的，稍稍想一想应该就能发现其实每个点着火的时间就是这个点离所有最初着火点的最小曼哈顿距离，所以完全没必要建 $N*M$ 的图去模拟，直接枚举每个点算它们的最小曼哈顿距离，将过程中拥有最大的最小曼哈顿距离的点坐标输出即可。时间复杂度 $O(N*M*K)$ ，空间复杂度 $K*2+3$ 。 

##### ~~比上面的方法好多了~~

## 简短的AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int L=1000000;
char LZH[L],*SSS,*TTT;
inline char gc(){if (SSS==TTT) TTT=(SSS=LZH)+fread(LZH,1,L,stdin);return *SSS++;}
inline int read(){int x=0,f=1;char c=gc();for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) x=(x<<1)+(x<<3)+c-48;return x*f;}
inline void write(int x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar(x%10+48);}
inline void wln(int x){write(x);putchar(10);}
inline void wlk(int x){write(x);putchar(32);}//极丑的快速输入输出
int a[13][3],ans,ansx=1,ansy=1;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);//注意看题。
	int n=read(),m=read(),K=read();
	for (int i=1;i<=K;++i) a[i][0]=read(),a[i][1]=read();
	for (int i=1;i<=n;++i)
	 for (int j=1;j<=m;++j){
	 	int now=0x3f3f3f3f;
	 	for (int k=1;k<=K;++k) now=min(now,abs(a[k][0]-i)+abs(a[k][1]-j));//算出每个点的最小曼哈顿距离
	 	if (now>ans) ans=now,ansx=i,ansy=j;//更新答案
	}
	return wlk(ansx),wln(ansy),0;
}
```

~~完结撒花~~

---

## 作者：米奇奇米 (赞：0)

一题假的蓝题，最多一道黄题吧!
# 用暴力模拟点就可以过
```cpp
#include <bits/stdc++.h>
using namespace std;
struct point {//写个结构体，方便点
    int x, y;
} pt[11];
const int maxn = 2500;
int mp[maxn][maxn];
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);//这次不是防抄袭
    ios_base::sync_with_stdio(false);//输入优化，让cin，cout与scanf，printf差不多
    int n, m, k;
    cin >> n >> m >>k;
    for(int i = 1; i <= k ; i++)
        cin >> pt[i].x >> pt[i].y;
    for(int i = 1 ; i <= n ; i++) {
        for(int j = 1 ; j <= m ; j++) {
            mp[i][j] = 1e6;
        }
    }//初始化，mp数组让其足够大
    for(int l = 1 ; l <= k ; l++) {
        for(int i = 1 ; i <= n ; i++) {
            for(int j = 1 ; j <= m ; j++) {
                int _x = abs(i - pt[l].x);
                int _y = abs(j - pt[l].y);
                mp[i][j] = min(_x+_y, mp[i][j]);
            }
        }
    }////枚举着火点的时间
    int ans = INT_MIN;
    int ans_x, ans_y;
    for(int i = 1 ; i <= n ; i++) {
        for(int j = 1; j <= m ; j++) {
            if(ans < mp[i][j]) {
                ans = mp[i][j];
                ans_x = i;
                ans_y = j;//记录当前的坐标
            }
        }
    }
    cout<<ans_x <<" "<< ans_y<<endl;
    return 0;
}
```


---

