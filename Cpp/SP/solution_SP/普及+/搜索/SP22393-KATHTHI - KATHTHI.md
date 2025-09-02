# KATHTHI - KATHTHI

## 题目描述

```
         Kathiresan is initially locked at cell (0,0) in a highly guarded rectangular prison of order RxC. He must reach the gate at (R-1,C-1) in order to escape from the prison. Kathiresan can move from any cell, to any of it's 4 adjacent cells (North, East, West and South). If Kathiresan is currently at (x1,y1), then he can move to (x2,y2) if and only if abs(x2-x1)+abs(y2-y1) == 1 and 0<=x2<R and 0<=y2<CKathiresan somehow manages to get the map of the prison.
If map[x1][y1] == map[x2][y2] then Kathiresan can move from (x1,y1) to (x2,y2) without killing any guards.
If map[x1][y1] != map[x2][y2], then Kathiresan can move from (x1,y1) to (x2,y2) by killing a guard.

Given the map of the prison, find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input:
The first line consists of an integer t, the number of test cases. For each test case, the first line consists of two integers R and C representing the order of the rectangular prison followed by R strings representing the map of the rectangular prison.
 
Output:
For each test case find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input Constraints:
1 <= t <= 10
2 <= R <= 1000
2 <= C <= 1000
'a' <= map[i][j] <= 'z'
Sample Input:
4
2 2
aa
aa
2 3
abc
def6 6akacccaaacfcamdfccaokhddzyxwdpzyxwdd5 5abbbcabaccaaaccaefcicdgdd Sample Output:
0
322
```

## 样例 #1

### 输入

```
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd
```

### 输出

```
0
3
2
2```

# 题解

## 作者：fls233666 (赞：6)

很容易发现，因为有 $2 \le R,C \le 1000$，我们可以考虑**广度优先搜索**。

进一步分析可以发现，如果使用普通的广度优先搜索，我们**不能保证队列的队首存的就是当前的最优方案**。

这个时候，有两种解决方案：

第一种方案：**把队列改成优先队列**。保证了队首就是最优的方案。但是这个方案的时间复杂度为 $O(tRC \log (RC))$, 常数不好很容易被卡掉。

第二种方案：**把队列改成双端队列**。我们注意到，**从一个点转移到另一个点的代价只有 $0$ 或 $1$** 。那我们可以**把转移代价为 $0$ 的点放到队首，把转移代价为 $1$ 的点放到队尾**。这样也能保证队首就是最优方案。而双端队列算法的时间复杂度为 $O(tRC)$，可以稳过此题。

下面给出双端队列的解法代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<deque>
#define ll long long
#define rgt register int
#define pir pair<int,int>
using namespace std;
const int mxn = 1111;

char mp[mxn][mxn];  //存储字符网络
int n,m,lz,f[mxn][mxn];  //f[i][j]存储到达点(i,j)的最小代价
int px[4]={-1,1,0,0};
int py[4]={0,0,-1,1}; 
pir g;
struct que_mode{
	int x;
	int y;
	char c;
}z[mxn*mxn],to;  //记录点坐标和当前点的字符

int main(){

	int test,sg;
	char ch;
	scanf("%d",&test);  //读入测试数据组数
    
	while(test--){
    
		scanf("%d%d",&n,&m);
		for(rgt i=1;i<=n;i++){
			scanf("%c",&ch);
			for(rgt j=1;j<=m;j++){
				scanf("%c",&mp[i][j]);
			}
		} //读入字符网络
        
		memset(f,127,sizeof(f));
		deque <pir> que;
		lz=1;
		z[lz].x=1;
		z[lz].y=1;
		z[lz].c=mp[1][1];
		f[1][1]=0;
		que.push_front(make_pair(0,1));
                //建双端队列并初始化
        
		while(!que.empty()){
        
			g=que.front();  //取出队首
			que.pop_front();  //删除队首
            
			if(z[g.second].x==n&&z[g.second].y==m)
				break;
                        //如果已经到达终点(n,m)，证明找到最优方案，跳出循环
                
			for(rgt i=0;i<4;i++){
				to.x=z[g.second].x+px[i];
				to.y=z[g.second].y+py[i];
                                //生成新的点坐标
                
				if(to.x>=1&&to.x<=n&&to.y>=1&&to.y<=m){  //判断是否越界
                
					to.c=mp[to.x][to.y];
					sg=to.c==z[g.second].c?g.first:g.first+1;  //计算转移需要的代价
                    
					if(sg<f[to.x][to.y]){  //如果可以更新代价
						lz++;
						z[lz]=to;  //存储点坐标
						f[to.x][to.y]=sg;  //更新最优方案
						if(to.c==z[g.second].c)   //入队
							que.push_front(make_pair(sg,lz));
						else
							que.push_back(make_pair(sg,lz));
					}
				}
			}
		}
		printf("%d\n",f[n][m]);  //输出答案
	}
	return 0;
}
```


---

## 作者：Mr_think (赞：5)

## [SP22393 KATHTHI - KATHTHI](https://www.luogu.com.cn/problem/SP22393)
## 题目大意：
给定一个 $n \times m$ 的网格，每个位置有一个小写字母，每次可以上下左右走，如果 $s[x][y]=s[nx][ny]$ 则这步花费为 $0$ ，否则为  $1$ 。求从 $(1,1)$ 到 $(n,m)$ 的最小花费。

## solution:
翻译的题面非常友善，给了一句话 
  
        `提示：不要用某些“活着”的最短路算法`
所以我们考虑其他最短路的方法，我们可以用 $\text{BFS}$ 来求最短路。但普通的 $\text{BFS}$ 时间复杂度爆炸。考虑优化，发现在 $\text{BFS}$ 的队列中，取出队头并不能确保它是最优的。所以一种新的方法出现了——**双端队列** $\text{BFS}$ $(\text{deque}+\text{BFS})$ ,这样我们能保证，任意时刻广搜队列中节点对应的距离值都有“两端性”和“单调性”，每个节点第一次被访问时，就能得到最短距离。

### 正确性证明：

由于我们最终目标是求路径权值和，而权值为$0$的边无论走多少条权值和依旧是 $+0$ ，因此我们可以优先走权值为 $0$ 的边，更新与这些边相连的点 $x$ 的 $d[x]$（ $d[i]$ 为从 $s$ 到 $i$ 最小权值和），此时 $d[x]$ 一定是最小的，因为它是由尽可能多的权值为0的边更新而来。所以在队列中取出的节点同时满足“连通性”和“权值最小”，因此每个节点仅需被更新一次。（引自CSDNhttps://valen.blog.csdn.net/）

## 接下来是细节的处理：
- 多组输入记得 $dis$ 要初始化(较大值 $0x3f3f3f3f$ )


[同类题推荐](https://www.luogu.com.cn/problem/P4554)

看到这的同学，可以自己去写代码了(~~tf口吻~~)

[code](https://www.luogu.com.cn/paste/cyzj33yn)

### End

## 作者的碎碎念：

有用留赞(~~言简意赅~~)

---

## 作者：Isshiki·Iroha (赞：3)

## 题解

[传送门](https://www.luogu.com.cn/problem/SP22393)

[Blog](https://www.luogu.com.cn/blog/yousa22/solution-sp22393)

## 开始的思路

这个题是 01BFS，就是最短路，看大佬们都用 01BFS（ $O(n+m)$ 复杂度）求，而我用 SPFA，都是普通的 SPFA 会 TLE，毕竟是网格图嘛，我们注意讲一下 SPFA 的优化。或者看一看[这个](https://www.zhihu.com/question/292283275?sort=created)。为什么网格图 SPFA 会死？因为网格图四通八达，你的入队次数非常庞大，你发现你很久以前更新的点被更新并且重新入队就很烦。网格图平均时间复杂度为 $O(nm)$，会炸。

## 优化
### 回忆
我们回忆一下 SPFA 是如何入队的，SPFA 是判断能否更新最短路并且是否访问就入队，这一点和 Dij 很像，但是 Dij 有贪心的思想（在正权图中，如果你当前路径比这个点以前的路径还大，你后面肯定也会变大）。但是 SPFA 是可以处理负边权的（因为它把当前的点设为没有访问，给了后面更新的机会）。

### 方法
我们可以模拟优先队列，使值小的在前面，这样可以使得后面更新的次数变少。有几种方法可以优化。


- SLF 优化：每次将入队结点距离和队首比较，如果更大则插入至队尾。

代码:
```cpp
inline void spfa(){
	deque<node>q;
	dis[1][1]=0;
	vis[1][1]=1;
	q.push_back({1,1});
	while(!q.empty()){
		reg node T=q.front();
		q.pop_front();
		vis[T.x][T.y]=0;
		for(ri i(0);i<4;++i){
			ri tx=T.x+dx[i];
			ri ty=T.y+dy[i];
			ri w=!(a[T.x][T.y]==a[tx][ty]);
			if(dis[tx][ty]>dis[T.x][T.y]+w){
				dis[tx][ty]=dis[T.x][T.y]+w;
				if(!vis[tx][ty]){
					vis[tx][ty]=1;
					if(!q.empty()&&dis[tx][ty]<dis[q.front().x][q.front().y]){
						q.push_front({tx,ty});
					}
					else {
						q.push_back({tx,ty});
					}
				}
			}
		}
	}
}
```


这样可以使点被更新的次数减小。（原因见上）
~~好像会 TLE，我忘记了。~~

- SLF + Swap（很强）跟 SLF 差不多，每当队列改变时，如果队首距离大于队尾，则交换首尾。

#### 警告：输入输出一定要关闭同步！

下面贴一下我 SLF + Swap 的代码（大佬们可以优化一下）：
```cpp


#include<bits/stdc++.h>
#define ll long long
#define reg register
#define ri reg int
using namespace std;
const int maxn=1001;
const int INF=0x3f3f3f3f;
int dis[maxn][maxn],a[maxn][maxn],n,m,vis[maxn][maxn];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
struct node {
	int x,y;
};
inline void spfa(){
	deque<node>q;
	dis[1][1]=0;
	q.push_back({1,1});
	while(!q.empty()){
		node T=q.front();
		q.pop_front();
		ri X=T.x;
		ri Y=T.y;
		vis[X][Y]=0;//system("pause");
		for(ri i(0);i<4;++i){
			ri tx=X+dx[i];
			ri ty=Y+dy[i];
			if(tx<1||ty<1||tx>n||ty>m)continue;
			ri w=!(a[X][Y]==a[tx][ty]);
			if(dis[tx][ty]>dis[X][Y]+w){
				dis[tx][ty]=dis[X][Y]+w;
				if(!vis[tx][ty]){
					vis[tx][ty]=1;
					q.push_back({tx,ty});
					if(!q.empty()&&dis[q.back().x][q.back().y]<dis[q.front().x][q.front().y]){
						swap(q.front(),q.back());
              //Swap
					}
				}
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	ri T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(ri i(1);i<=n;++i){
			for(ri j(1);j<=m;++j){
				char t;
				cin>>t;
				a[i][j]=t-'a'+1;
				dis[i][j]=INF;
				vis[i][j]=0;
           //Memset
			}
		}
		spfa();
		cout<<dis[n][m]<<endl;
	}
	return 0;
}
}
```

参考：[如何看待 SPFA 算法已死这种说法？](https://www.zhihu.com/question/292283275?sort=created)




---

## 作者：Leap_Frog (赞：2)

# SP22393 KATHTHI - KATHTHI（题解）
## Link.
[点我](https://www.luogu.org/problem/SP22393)
## PS.
根本不用楼下的什么$\texttt{01}$矩阵的做法。  
只要按照套路来思考就可以了。  
## Problem.
给你一个字符矩阵，你刚开始在$\texttt{(1,1)}$这个点，你需要去$\texttt{(n,m)}$这个点。  
如果你现在的点上的字符和你上一步的字符不相同，你需要付出一个金币，否则不需要。  
求你从起点到终点最少需要花费多少个金币。  
## Solution.
### 思路1.
此题一看就是广搜，但是可惜边权不唯一，可能是0或者1。  
**显然**，在一个出发点，扩散出0的肯定比扩散出1的更优。  
所以，权值为1的指向的点一定要在权值为0的后面。  
**显然**，如果已经从队首弹出一个元素了，那么肯定它是当前最小的元素。  
所以我们可以维护一个一定单调的队列（不是单调队列）来充当广搜中的队列。  
首先从队首弹出一个元素，然后把扩展出来权值+0的放回队首，权值+1的放至队尾。  
然后就可以维护广搜了。  
### 思路2.
此题虽然翻译者认为不要用一些最短路算法，但是其实也可以用$\texttt{spfa}$草过去。  
当然，裸的$\texttt{spfa}$是不行的，那么我们需要做一些优化。  
就是可以把扩展出去的元素，把比当前小的放在队首，当前大的放在队尾。  
然后就可以用优化的$\texttt{spfa}$草过去了![](https://upload.orzsiyuan.com/images/emotions/cy.png]  
## Coding
```cpp
#include<bits/stdc++.h>
using namespace std;	//我爱万能头
const int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};	//四个方向
const int N=1005;	//n和m的最大值
struct point{int x,y;};		//点的结构体
char a[N][N];int t,n,m,dis[N][N];	//a是字符矩阵，dis是spfa里的距离或者广搜的距离
inline char inmap(int x,int y) {return x>=1&&x<=n&&y>=1&&y<=m;}		//一个点是否在矩阵里面
inline int bfs()
{
	deque<point>q;q.push_back((point){1,1}),dis[1][1]=0;	//定义一个deque
	while(!q.empty())	//bfs经典操作
	{
		point t=q.front();q.pop_front();
		for(int i=0;i<4;i++)	//遍历方向
		{
			int x=t.x+dx[i],y=t.y+dy[i],z=a[x][y]!=a[t.x][t.y];
			if(!inmap(x,y)||dis[x][y]<=dis[t.x][t.y]+z) continue;else dis[x][y]=dis[t.x][t.y]+z;	//判断能否进队
			if(!z) q.push_front((point){x,y});else q.push_back((point){x,y});	//入队
		}
	}
	return dis[n][m];	//返回答案
}
int main()
{
	for(scanf("%d",&t);t--;)	//多组数据的压行
	{
		ios::sync_with_stdio(false);	//我太菜了，遇到字符题目都要用cin
		cin>>n>>m,memset(dis,0x3f,sizeof(dis));		//读入，然后赋极值
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];	//读入字符矩阵
		cout<<bfs()<<endl;	//输出答案
	}
	return 0;	//完美的结束程序
}
```

---

## 作者：xukuan (赞：2)

这题的样例被莫名其妙的吃了换行，在此发一个正常一点的版本：

输入
```pascal
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd
```

输出
```pascal
0
3
2
2
```

题解正文：

最短路无疑，但怎么写？

网格图还要用spfa的怕不是想死

咋一眼看上去像dijkstra，但$O(Tnm log_2(nm))$的时间复杂度在SPOJ老爷机上可以TLE到飞起

所以这是一道01BFS的模板题。

01BFS可以在$O(n+m)$的时间内求出边权只有0/1的最短路

具体的操作办法：

当我们对一个点进行bfs的时候

**先出队**

这个时候，假设这个点的值是x，那么别的点的值要么是x,要么是x+1

bfs后的节点的权值也是要么是x，要么是x+1

所以我们可以考虑把bfs后距离是x的加在队首，x+1的加在队尾

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=1010,dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
ll n,m,d[N][N];
char s[N][N];
struct node{
    ll x,y;
};
deque<node> q;

inline ll read(){
    ll x=0,tmp=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') tmp=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return tmp*x;
}

inline void write(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<3)+(y<<1);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}

inline void bfs(ll x,ll y){
    q.push_back(node{1,1});
    while(!q.empty()){
        ll x=q.front().x,y=q.front().y; q.pop_front();
        for(ll i=0; i<4; i++){
            ll X=x+dx[i],Y=y+dy[i],z=s[x][y]!=s[X][Y];
            if(X>=1&&X<=n&Y>=1&Y<=m&&d[X][Y]>d[x][y]+z){
                d[X][Y]=d[x][y]+z;
                if(z) q.push_back(node{X,Y});
                else q.push_front(node{X,Y});
            }
        }
    }
}

int main(){
    for(ll T=read(); T; T--){
        memset(d,0x3f,sizeof(d));
        d[1][1]=0;
        n=read(); m=read();
        for(ll i=1; i<=n; i++) scanf("%s",s[i]+1);
        bfs(1,1);
        write(d[n][m]); putchar('\n');
    }
    return 0;
}
```

---

## 作者：attack (赞：2)

01BFS的裸题，感觉这个点子还是很妙的

01BFS可以在$O(n+m)$求出边权只有$0 / 1$的最短路

我们维护一个双端队列，如当前可以进行松弛那么就进行更新，更新完后判断一下，若边权为$1$，则在队尾加入下一个点，否则在队首加入下一个点

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
//#define int long long 
using namespace std;
const int MAXN = 1001;
inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}
int N, M;
struct Node {
	int x, y, s;
};
deque<Node> q;
int dis[MAXN][MAXN], xx[] = {-1, +1, 0, 0}, yy[] = {0, 0, -1, +1};
char s[MAXN][MAXN];
void OneZeroBFS() {
	q.push_back((Node) {1, 1, 0});
	while(!q.empty()) {
		Node p = q.front(); q.pop_front();
		for(int i = 0; i < 4; i++) {
			int wx = p.x + xx[i], wy = p.y + yy[i];
			int w = (s[wx][wy] != s[p.x][p.y]);
			if(dis[wx][wy] > dis[p.x][p.y] + w && (wx > 0 && wy > 0 && wx <= N && wy <= M))
				dis[wx][wy] = dis[p.x][p.y] + w,
				w == 1 ? q.push_back((Node) {wx, wy, w}) : q.push_front((Node) {wx, wy, w});
		}
	}
}
main() {
	int QwQ = read();
	while(QwQ--) {
		memset(dis, 0xf, sizeof(dis));
		dis[1][1] = 0;
		N = read(); M = read();
		for(int i = 1; i <= N; i++)	
			scanf("%s", s[i] + 1);
		OneZeroBFS();
		printf("%d\n", dis[N][M]);
	}
	return 0;
}
/*
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd
*/
                            ```

---

