# [ARC005C] 器物損壊！高橋君

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc005/tasks/arc005_3

 良く見てみるとカードの有効期限が切れていたので、高橋君は諦めて魚屋に直接うなぎを買いに行くことにしました。  
 彼の住む街は長方形の形をしており、格子状の区画に区切られています。区画は道または塀のどちらかであり、高橋君は道を東西南北に移動できますが斜めには移動できません。また、塀の区画は通ることができません。高橋君の家から魚屋までの道のりは非常に複雑なため、単純に歩くだけでは辿り着くことは困難です。  
 しかし、高橋君は腕力には自信があるので道に上下左右で面している塀を $ 2 $ 回までなら壊して道にすることができます。  

 高橋君が魚屋に辿り着くことができるかどうか答えてください。 入力は以下の形式で標準入力から与えられる。

> $ H $ $ W $ $ c_{(0,0)}c_{(0,1)} $ … $ c_{(0,W-1)} $ $ c_{(1,0)}c_{(1,1)} $ … $ c_{(1,W-1)} $ : : $ c_{(H-1,0)}c_{(H-1,1)} $ … $ c_{(H-1,W-1)} $

- 入力は $ H+1 $ 行ある。
- $ 1 $ 行目は、街の南北の長さとして整数 $ H(1≦H≦500) $ と東西の長さとして整数 $ W(1≦W≦500) $ が空白で区切られて与えられる。
- $ 2 $ 行目からの $ H $ 行には、格子状の街の各区画における状態 $ c_{(i,j)}(0≦i≦H-1, $ $ 0≦j≦W-1) $ が与えられる。
- $ i $ 行目 $ j $ 文字目の文字 $ c_{(i,j)} $ はそれぞれ `s`, `g`, `.`, `#` のいずれかで与えられ、座標 $ (j,i) $ が下記のような状態であることを表す。
- `s` : その区画が家であることを表す。
- `g` : その区画が魚屋であることを表す。
- `.` : その区画が道であることを表す。
- `#` : その区画が塀であることを表す。

- 高橋君は家?魚屋?道は通ることができるが、塀は通ることができない。
- 与えられた街の外を通ることはできない。
- `s` と `g` はそれぞれ $ 1 $ つずつ与えられる。

 塀を $ 2 $ 回まで越えることで、家から魚屋まで辿り着くことができる場合は `YES`、辿りつけない場合は `NO` を標準出力に $ 1 $ 行で出力せよ。  
 なお、最後には改行を出力せよ。 

```
4 5
s####
....#
#####
#...g
```

```
YES
```

- $ (1,2), $ $ (2,2), $ $ (3,2) $ のいずれかの塀を壊すことで、魚屋に到達することができます。 

```
4 4
...s
....
....
.g..
```

 ```
YES
 ```

- 塀が無いので到達することができます。


```
10 10
s.........
#########.
#.......#.
#..####.#.
##....#.#.
#####.#.#.
g##.#.#.#.
###.#.#.#.
###.#.#.#.
#.....#...
```

```
YES
```

- $ (1,6), $ $ (2,6) $ の $ 2 $ つの塀を壊すことで到達することができます。


```
6 6
.....s
###...
###...
######
...###
g.####
```

 ```
YES
 ```

- 一例として $ (3,3) $, $ (2,3), $ の $ 2 $ つの塀を壊すと、到達することができます。

```
1 10
s..####..g
```

 ```
NO
 ```

- 塀を $ 2 $ つ壊しても魚屋に到達することができません。

# 题解

## 作者：CrTsIr400 (赞：2)

6种不同做法。

# 1.dfs做法

从初始点出发，不断寻找通往终点的路径。

小剪枝：

标记每个点，$b[x][y][flag]$ 表示 $(x,y)$ 点跨过障碍 $flag(flag∈[0,1])$ 次时有没有访问过。

时间复杂度 $O(nm)$ 。

# 2.bfs做法

两次宽搜，一次从起始点出发，一次从终点出发，遇到障碍停下来。

再枚举每个障碍的两侧，看看翻过这个障碍能否到达终点宽搜的这颗搜索树的某个节点。

换句话说，从起始点染色，从终止点染上另一种颜色，枚举每个障碍物的两侧，判断两侧是否是访问过而且染上了不同颜色。

时间复杂度 $O(nm)$ 。

# 3.SPFA做法

建图：对于每个枚举的点，往4个方向判断，如果碰到障碍就当它边权为1，没有碰到就是边权为0。

然后直接跑SPFA。。。

---

或者说在SPFA的过程中直接处理边权，更香。

---

这个SPFA应该不会被卡（

时间复杂度 $O(tnm)$  ，$t$ 应该是非常小的一个常数。

# 4.dijkstra做法(1)

考虑使用SPFA框架。

使用优先队列进行优化，在松弛周围4个节点时算出边权，然后跑普通的dijkstra。

时间复杂度 $O(nm \log(4nm))$ 。

# 5.dijkstra做法(2)

使用普通dijkstra框架。

老规矩，松弛时算出边权，然后发现选 $dis[i][j]$ 最小值还是要使用暴力。怎么办呢？

线段树/zkw线段树/堆 呗。

使用线段树，只用解决单点修改、全局查询即可。

使用堆，只用支持任意元素修改操作即可。注意堆中的值不是dist值。

时间复杂度 $O(nm\log(nm))$ 。

# 6.bfs/SPFA+LLL/SLF（？）

双端队列bfs，权值为0丢到队首，权值为1丢到队尾。

或者开两个队列，一个权值为 0 的，一个权值为1的。

处理完权值为 0 的再处理权值为1的。

时间复杂度 $O(nm)$ 。

---

## 作者：QwQ蒟蒻wjr (赞：2)

我发现这题可以打SPFA，dfs容易堆栈溢出，所以，这道题可以跑SPFA~~恶意评分的题随便写方法，看着像蓝题就行~~
SPFA本来死了，~~然后永存~~然后在这题我差点打挂掉了详细请见[SPFA打挂现场](https://www.luogu.org/record/21966218)
```
#include<cstdio>
#include<queue>
#include<iostream>
#define re register
using namespace std;
int n,m,w;
char s[1010][1010];
int f[1010][1010],qix,qiy,zhongx,zhongy;
int fx[4]= {0,0,1,-1},
           fy[4]= {1,-1,0,0};
bool exist[1010][1010];
struct node
{
	int x,y;
} u,v;
queue<node>q;
int main()
{
	cin>>n>>m;
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=m; j++)
			f[i][j]=3;
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=m; j++)
		{
			cin>>s[i][j];
			if(s[i][j]=='s')
			{
				qix=i;
				qiy=j;
			}
			else if(s[i][j]=='g')
			{
				zhongx=i;
				zhongy=j;
			}
		}
	u.x=qix;
	u.y=qiy;
	q.push(u);
	f[u.x][u.y]=0;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		exist[u.x][u.y]=false;
		for(re int i=0; i<4; i++)
		{
			v.x=u.x+fx[i];
			v.y=u.y+fy[i];
			w=f[u.x][u.y];
			if(s[v.x][v.y]=='#')
				w++;
			if(w<f[v.x][v.y])
			{
				f[v.x][v.y]=w;
				if(v.x==zhongx&&v.y==zhongy)
				{
					printf("YES\n");
					return 0;
				}
				if(!exist[v.x][v.y])
				{
					q.push(v);
					exist[v.x][v.y]=true;
				}
			}
		}
	}
	printf("NO\n");
	return 0;
}
```


---

## 作者：Doveqise (赞：1)

啊 又是一道模拟题（AT好题）（入门必备233）   
这道题也是只要按照题意写一下就好 见代码（代码较全）  
（dx dy 吹爆LRJ！）
```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,a,b,v[505][505];
int dy[4]={0,0,1,-1},dx[4]={1,-1,0,0};//移动
bool flag;
char m[505][505];//图
void dfs(int y,int x,int f){//dfs搜索
	if(y<0||y>=h||x<0||x>=w||(v[y][x]&&f>=v[y][x]))return;//判断是否违法
	if(m[y][x]=='g'){flag=1;return;}//到达终点
	if(m[y][x]=='#'){if(f==3)return;f++;}//跨越障碍
	v[y][x]=f;//记录步数
	for(int i=0;i<4;i++)
		dfs(y+dy[i],x+dx[i],f);//扩展
}
int main(){
	scanf("%d%d",&h,&w);
	for(int i=0;i<h;i++){
		scanf("\n");//再次万恶scanf读入空行
		for(int j=0;j<w;j++){
			scanf("%c",&m[i][j]);//读入图
			if(m[i][j]=='s')a=i,b=j;//记录起点
		}
	}
	dfs(a,b,1);//开始遍历
	flag?puts("YES"):puts("NO");//判断是否有路径
}

```


---

## 作者：L7_56 (赞：0)

~~其实有点水~~

只是比较普通的搜索，在搜索参数中加上一个**还能跨越的障碍数** $t$ 就可以

再用数组记忆一下到当前的最大$\,t$，不然过不了

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstdlib>
using namespace std;

const int maxn=510;
int n,m;
int mp[maxn][maxn];
bool vis[maxn][maxn];
int mt[maxn][maxn];
int sx,sy,ex,ey;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

void dfs(int x,int y,int t){
//	printf("(%d, %d):%d\n", x, y, t);
	if(x<1||x>n||y<1||y>m) return;
	if(mt[x][y]>=t&&vis[x][y]) return;
	if(x==ex&&y==ey) printf("YES\n"),exit(0);	
	if(mp[x][y]) {if(t==0) return; --t;}
	
	vis[x][y]=1,mt[x][y]=t;
	for(int i=0;i<4;++i){
		int cx=x+dx[i],cy=y+dy[i];
		dfs(cx,cy,t);
	}
	return;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;++i){
		string s;cin>>s;
		for(int j=1;j<=m;++j){
			switch(s[j-1]){
				case 's' : sx=i,sy=j;break;
				case 'g' : ex=i,ey=j;break;
				case '#' : mp[i][j]=1;break;
				default : break; 
			}
		}
	}

	dfs(sx,sy,2);
	printf("NO\n"); 
	return 0;
}

```

---

## 作者：HMP_Haoge (赞：0)

~~先自我介绍一下，我叫**大法师**，我擅长于打各种**DFS**~~

进入正题，这个题是一个很板的走迷宫型DFS题目，但是这个人可以开2次挂，可以穿墙两次，因此这个题求得就从最小步数变成了一个判断性问题。

就算如此，也不能小瞧它！因为**正常的DFS会T得很惨烈**：

测试点#15   TLE代码
```cpp
for(ri i=1; i<=4; ++i)
{
	int xx=nx+dx[i],yy=ny+dy[i];
	if(xx>=1 && xx<=h && yy>=1 && yy<=w && !vis[xx][yy])
	{
		if(a[xx][yy]==1)
		{
			vis[xx][yy]=1;
			dfs(xx,yy,k+1);
			vis[xx][yy]=0;
		}
		else
		{
			vis[xx][yy]=1;
			dfs(xx,yy,k);
			vis[xx][yy]=0;
		}
	}
}
```
经过一番考虑，我发现这个题可以经过记忆化从起点到每个经过了的点所剩下的穿墙次数来实现优化，于是，完整代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define MAXN 510

int h,w,a[MAXN][MAXN],sx,sy,ex,ey,f[MAXN][MAXN];
int dx[]= {0,1,0,-1,0},dy[]= {0,0,1,0,-1};
bool vis[MAXN][MAXN];
char s[MAXN];

template <typename T> inline void read (T &x)
{
	x=0;
	int f=1;
	char c=getchar();
	for(; !isdigit(c); c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c); c=getchar()) x=(x<<3)+(x<<1)+(c^48);
	if(f<0) x=-x;
}
template <typename T> inline void write(T x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
inline void dfs(int nx,int ny,int k)
{
	if(nx<1 || nx>h || ny<1 || ny>w || (vis[nx][ny] && k<=f[nx][ny])) return;
	if(nx==ex && ny==ey)
	{
		printf("YES\n");
		exit(0);
	}
	if(a[nx][ny])
	{
		if(k==0) return;
		--k;
	}
	vis[nx][ny]=1;
	f[nx][ny]=k;  //记忆化优化操作
	for(ri i=1;i<=4;++i)
		dfs(nx+dx[i],ny+dy[i],k);
}

int main()
{
	read(h);
	read(w);
	for(ri i=1; i<=h; ++i)
	{
		scanf("%s",s+1);
		for(ri j=1; j<=w; ++j) //分解字符串存图
		{
			if(s[j]=='s')
				sx=i,sy=j;
			else if(s[j]=='g')
				ex=i,ey=j;
			else if(s[j]=='.')
				a[i][j]=0;
			else if(s[j]=='#')
				a[i][j]=1;
		}
	}
	dfs(sx,sy,2);
	printf("NO\n");
	return 0;
}
```

**Last but not the least**，如果你多次提交并且从第一个就开始WA，请一定再看一眼题目

```
输出"YES"，否则输出"NO"（输出的最后换一行）
```


---

