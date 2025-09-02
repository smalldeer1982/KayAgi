# The Labyrinth

## 题目描述

You are given a rectangular field of $ n×m $ cells. Each cell is either empty or impassable (contains an obstacle). Empty cells are marked with '.', impassable cells are marked with '\*'. Let's call two empty cells adjacent if they share a side.

Let's call a connected component any non-extendible set of cells such that any two of them are connected by the path of adjacent cells. It is a typical well-known definition of a connected component.

For each impassable cell $ (x,y) $ imagine that it is an empty cell (all other cells remain unchanged) and find the size (the number of cells) of the connected component which contains $ (x,y) $ . You should do it for each impassable cell independently.

The answer should be printed as a matrix with $ n $ rows and $ m $ columns. The $ j $ -th symbol of the $ i $ -th row should be "." if the cell is empty at the start. Otherwise the $ j $ -th symbol of the $ i $ -th row should contain the only digit —- the answer modulo $ 10 $ . The matrix should be printed without any spaces.

To make your output faster it is recommended to build the output as an array of $ n $ strings having length $ m $ and print it as a sequence of lines. It will be much faster than writing character-by-character.

As input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 说明/提示

In first example, if we imagine that the central cell is empty then it will be included to component of size $ 5 $ (cross). If any of the corner cell will be empty then it will be included to component of size $ 3 $ (corner).

## 样例 #1

### 输入

```
3 3
*.*
.*.
*.*
```

### 输出

```
3.3
.5.
3.3
```

## 样例 #2

### 输入

```
4 5
**..*
..***
.*.*.
*.*.*
```

### 输出

```
46..3
..732
.6.4.
5.4.3
```

# 题解

## 作者：yaolibo (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF616C)
### 题意解释：
给定一张n\*m的图，其中 '.' 代表空地，'\*' 代表墙，求把当前位置的墙改为空地，包含当前块的连通块有多少个（包含当前块的周围联通的空地共有多少个），注意如果当前位置是 '.' 就直接输出 '.' 。
### 思路 & 方法：
一个个遍历 '\*' 肯定会超时，于是我们便不从 '\*' 入手，转而从 '.' 入手，先用dfs计算连通块有多少部分，并把每一部分标上号，计算其连通块的个数，储存在ans数组里。然后遍历每一个 '\*' ，看它的四周（上下左右）的标记的那一部分连通块的个数，然后把它们累加（注意是同一部分的只要加一次），最后加上本身的1就是答案。
### 举个例子：如下图：
红色块为当前遍历到的墙，空地连通块共被分为三部分：  
①：1块；  
②：5块；  
③：5块；  
（1）当前块的上方是②号连通块，答案加上5；  
（2）当前块的左方和下方都是三号连通块，只加一次，答案加上5；  
（3）当前块的右方是墙，答案加上0；  
（4）最后加上本身的1；  
所以红色块的答案为5+5+1=11。  
![](https://cdn.luogu.com.cn/upload/image_hosting/pjsm6096.png)
#### PS：具体细节见代码注释。
------------
### Code:
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
int n, m, cnt, res, sum, x, y, i, j, k, f[4], ans[5100000], vis[1100][1100], lx[4] = {-1, 0, 1, 0}, ly[4] = {0, 1, 0, -1};
//vis数组存储连通块的部分的编号，ans数组存储每一部分连通块的个数
char s[1100][1100];
void dfs(int x, int y) { //本次dfs遍历到的所有符合条件的块在vis中均为同一个编号
	int nx, ny, i;
	vis[x][y] = cnt; //把当前块标上号
	res++; //累加器加1
	for (i = 0; i < 4; i++) {
		nx = x + lx[i];
		ny = y + ly[i]; //向四周移动
		if (nx > 0 && nx <= n && ny > 0 && ny <= m && s[nx][ny] == '.' && !vis[nx][ny]) //判断是否不越界，是空地且没有访问过
			dfs(nx, ny); //dfs递归回溯
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); //加速命令
	cin >> n >> m;
	for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            cin >> s[i][j]; //输入
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (s[i][j] == '.' && !vis[i][j]) { //如果当前块是 '.' ，并且还没有被访问过，说明找到了一个新的连通块部分
				res = 0; //res存储当前部分连通块个数
				cnt++; //cnt表示这一部分连通块的编号
				dfs(i, j); //dfs搜索，把与当前块联通的 '.' 全部标记
				ans[cnt] = res; //第cnt部分连通块的个数是res
			}
		}
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) { //遍历每一个格子
			f[0] = f[1] = f[2] = f[3] = 0; //f[0..3]分别用来存储四周连通块的编号，防止重复计算同一个编号的连通块
			sum = 0; //当前块的答案
			if (s[i][j] == '*') { //如果当前块是墙才计算
				for (k = 0; k < 4; k++) { //遍历当前块的四个方向
					x = i + lx[k];
					y = j + ly[k];
					if (s[x][y] == '#') continue; //如果得到的这个格子是墙的话就无需计算
					if (vis[x][y] == f[0] || vis[x][y] == f[1] || vis[x][y] == f[2] || vis[x][y] == f[3]) continue; //如果得到的这个连通块的编号之前已经出现过，就无需计算
					f[k] = vis[x][y]; //标记编号
					sum += ans[vis[x][y]]; //答案加上这个连通块编号的连通块个数
				}
				cout << (sum + 1) % 10; //模10输出（要记得加上本身）
			}
			else cout << '.'; //如果是空地就直接输出 '.'
		}
		cout << '\n'; //记得输出完一行要换行
	}
	return 0;
}
```
### 结束~Over~

---

## 作者：ImposterAnYu (赞：2)

# 题目大意
给你一张 $n \times m$ 的图，其中 `*` 表示墙，`.` 表示空地。当 $a_{i,j}$ 为 `*` 时，你需要计算当 $a_{i,j}$ 变成 `.` 时，$a_{i,j}$ 所在的连通块（四连通）有多少个 `.`；否则，直接输出 `.`。

# 解析
因为每个 `*` 都需要单独处理，所以在最坏情况下，处理每个 `*` 时都要将整个图都遍历一遍，在 $1 \leq n,m \leq 1000$ 的情况下一定会超时。

所以，我们可以考虑从 `.` 入手，先将所有的连通块里 `.` 的个数以及每个 `.` 分别属于第几个连通块给存起来，再处理每个 `*`。

具体过程如下：

1. 读入，区分 `*` 和 `.`。

2. 搜索，将每个 `.` 遍历一遍，求出每个 `.` 分别属于哪个连通块。每遍历完一个连通块后，就记录这个连通块里 `.` 的个数。

3. 处理每个 `*`。先将每个 `*` 上下左右的连通块找出来，判断是否有重复的，因为重复的只能记一次。

至此，~~我又水了一篇题解~~我们就可以愉快地 AC 啦![](//图.tk/4)
# code
```c++
#include<bits/stdc++.h> 
#define int1 long long
//#define p 1145141919810114514
using namespace std;
int1 n,m,i,j,k,l,a[1005][1005],b[1005][1005],c[1000005],d[4],s,p,e,f;
//b[i][j] 用来记录 a[i][j] 属于哪个连通块，c[i] 用来记录第 i 个连通块里'.'的个数。
char ch;
int1 read(){//快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
void dfs(int1 x,int1 y){
	s++,b[x][y] = p;//s 为当前连通块'.'的个数。
	for(int1 t = 0; t < 4; t++){//遍历。
		int1 xx = x + (t < 2) - ((t == 1) << 1),yy = y + (t > 1) - ((t == 3) << 1);//为了装逼没开数组，但其实开个数组更简单。
        //相当于定义变量时加了个 dx[4] = {1,-1},dy[4] = {0,0,1,-1}，然后这里写 int1 xx = x + dx[t],yy = y + dy[t];。
		if(a[xx][yy] > 1 && !b[xx][yy]){//如果下一个点是'.'且还未被遍历过，
			dfs(xx,yy);//遍历该点。
		}
	}
	return ;
}
int main(){
	n = read(),m = read();
	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			ch = getchar();
			while(ch != '*' && ch != '.'){
				ch = getchar();
			}
			a[i][j] = (ch == '.') + 1;//因为不喜欢字符，就用整数代替了。a[i][j] = 1 表示这是'*'，a[i][j] = 2 表示这是'.'。
		}
	}
	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			if(a[i][j] > 1 && !b[i][j]){//如果这个`.`还未被遍历过，
				p++;//连通块个数 + 1。
				dfs(i,j);//遍历整个连通块。
				c[p] = s,s = 0;//记录连通块个数。
			}
		}
	}
	for(s = i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			if(a[i][j] < 2){//处理`*`
				for(k = 1; k <= 4; k++){
					e = i + (k < 3) - ((k == 2) << 1),f = j + (k > 2) - ((k == 4) << 1);//同第 37 行，只是写法稍有不同。
					for(l = 0; l < k; l++){//判重。
						if(b[e][f] == d[l]){
							break;
						}
					}
					if(l == k){//如果没重复，
						s += c[b[e][f]],d[k - 1] = b[e][f];//统计`.`的个数。
					}
				}
				print(s % 10);
				s = 1,d[0] = d[1] = d[2] = d[3] = 0;//重置。
			}else{
				putchar('.');
			}
		}
		putchar('\n');
	}
  	return 0;
}
```

---

## 作者：开始新的记忆 (赞：2)

题目大意：给你一张n*m的地图，每个点由“ . ”或者“ * ”组成， . 代表空地， * 代表障碍。现在要你对于每个障碍都做如下判断：如果把当前障碍改成空地，那么当前块所在连通块的个数是多少个。

大致思路：如果对于每个点都扫一遍，那么在时间复杂度上是肯定不行的，我们发现每次遍历都会重复运算每个块，于是我们可以预处理————把当前区域连通块的个数记下并标号，最后我们只需对每个块往上下左右判断即可。

```
#include<bits/stdc++.h>
using namespace std;
int a[1010][1010],ans[1000010],num[1010][1010];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
bool visited[1010][1010];
int n,m,cnt=1,anss;

bool judge(int x,int y)
{
	if(x<1 || x>n || y<1 || y>m)
		return 1;
	return 0;
}

void dfs(int x,int y)
{
	++anss;
	visited[x][y]=1;
	num[x][y]=cnt;
	for(int i=0;i<4;++i)
	{
		int tx=dx[i]+x,ty=dy[i]+y;
		if(judge(tx,ty))
			continue;
		if(a[tx][ty]==0 && !visited[tx][ty])
			dfs(tx,ty);
	}
}

int main()
{	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		string s;
		cin>>s;
		for(int j=1;j<=m;++j)
			if(s[j-1]=='*')
				a[i][j]=1;
			else
				a[i][j]=0;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(!visited[i][j] && a[i][j]==0)
			{
				anss=0;
				dfs(i,j);
				ans[cnt]=anss;
				++cnt;
			}
			/*
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
			cout<<ans[i][j];
		cout<<endl; 
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
			cout<<num[i][j];
		cout<<endl; 
	}*/
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
			if(a[i][j]==0)
				cout<<'.';
			else
			{
				anss=1;
				set <int> s;
				for(int k=0;k<4;++k)
				{
					int tx=i+dx[k],ty=j+dy[k];
					if(!judge(tx,ty) && a[tx][ty]==0)
						s.insert(num[tx][ty]);
				}
				for(set<int>::iterator it=s.begin();it!=s.end();it++)
        			anss+=ans[*it];
				anss%=10;
				cout<<anss;
			}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：hxhhxh (赞：1)

## 大意

给定一个地图全部由`*`或`.`组成，要求输出一个同样大小的地图，你要将`*`替换成一个数字，表示**假设**它是`.`，它所在的`.`连通块的大小模 $ 10 $ 的余数。

## 思路

将一个`*`替换成一个`.`时，它所在连通块由：

+ 它本身，，大小恒定为 $ 1 $ ；
+ 它上面，如果上面是`.`，大小为该联通块大小；
+ 它下面，如果下面是`.`，大小为该联通块大小；
+ 它左边，如果左边是`.`，大小为该联通块大小；
+ 它右边，如果右边是`.`，大小为该联通块大小；

组成。同一个联通块不重复计算，如果不想判，推荐使用`set`。

求原本的联通块大小可以`dfs`或`bfs`，但我选择二维带权并查集。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,siz[1005][1005];
char ch[1005][1005];
struct st{
	int x,y;
	bool operator ==(const st&r)const{
		return x==r.x&&y==r.y;
	}
	bool operator <(const st&r)const{
		return x==r.x?y<r.y:x<r.x;
	}
}f[1005][1005];
st find(st x){
	if(f[x.x][x.y]==x) return x;
	return f[x.x][x.y]=find(f[x.x][x.y]);
}
int solve(int x,int y){
	set<st>s;
	int ans=0;
	if(ch[x-1][y]=='.') s.insert(f[x-1][y]);
	if(ch[x][y-1]=='.') s.insert(f[x][y-1]);
	if(ch[x+1][y]=='.') s.insert(f[x+1][y]);
	if(ch[x][y+1]=='.') s.insert(f[x][y+1]);
	for(st i:s) ans+=siz[i.x][i.y];
	return ans+1;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>ch[i]+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) f[i][j]=(st){i,j};
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='.'){
				if(ch[i-1][j]=='.') f[find((st){i,j}).x][find((st){i,j}).y]=find((st){i-1,j});
				if(ch[i][j-1]=='.') f[find((st){i,j}).x][find((st){i,j}).y]=find((st){i,j-1});
			}
		}
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(ch[i][j]=='.') siz[find((st){i,j}).x][find((st){i,j}).y]++;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='.') putchar('.');
			else printf("%d",solve(i,j)%10);
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：wind_whisper (赞：1)

[更糟的阅读体验](https://blog.csdn.net/BUG_Creater_jie/article/details/122254012)
## $\text{Descripion}$
给你一张图，`*` 表示墙，`.`表示空地，问每个 `*` 周围的联通快中 `.` 的数量和模 $10$ 的结果，属于同一个连通快的只计算一次。
$n,m\le 1000$
## $\text{Solution}$
bfs 一遍求出每个连通块的大小，求出每个点四周的大小之和即可。  
可以利用 set 方便去重。

## $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

const int N=1050;

int n,m;
int a[N][N],bel[N][N],siz[N*N],tot,vis[N][N];
int dx[5]={0,0,-1,0,1},dy[5]={0,-1,0,1,0};
inline bool exi(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m;}
void bfs(int x,int y,int f){
  vis[x][y]=1;bel[x][y]=f;siz[f]++;
  for(int i=1;i<=4;i++){
    int xx=x+dx[i],yy=y+dy[i];
    if(vis[xx][yy]||a[xx][yy]||!exi(xx,yy)) continue;
    bfs(xx,yy,f);
  }
  return;
}
set<int>s;

signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      char c;scanf(" %c",&c);
      a[i][j]=(c=='*');
    }
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      if(a[i][j]||vis[i][j]) continue;
      ++tot;bfs(i,j,tot);
    }
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      if(!a[i][j]){
	putchar('.');continue;
      }
      for(int k=1;k<=4;k++){
	int x=i+dx[k],y=j+dy[k];
	if(a[x][y]||!exi(x,y)) continue;
	s.insert(bel[x][y]);
      }
      int ans(1);
      for(int x:s) ans+=siz[x];
      printf("%d",ans%10);
      s.clear();
    }
    putchar('\n');
  }
  return 0;
}
/*
 */

```

---

## 作者：pengzy (赞：0)

### 题意：

给你一张 $n\times m$ 的地图，```.``` 表示空地，```*``` 表示障碍。要你求出如果把当前位置的障碍变成空地后联通块的个数。

### 思路：

此题如果暴力枚举每一个点显然是超时的。会发现每一次搜索都会重复某些部分，导致时间复杂度过高。我们可以先记录下当前联通块的个数，然后对不同联通块的点打上标记，每次只要判重即可。

使用 ```set``` 进行判重。

记得对 $10$ 取模。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=1e3+5;
int a[MAX][MAX],ans[MAX*2],cnt[MAX][MAX];//a 是输入的地图，ans 记录答案，cnt 预处理，要判重
int dx[4]={0,+1,0,-1},dy[4]={+1,0,-1,0};
bool vis[MAX][MAX];//标记走没走过
int n,m,tot=1,t=0;
bool judge(int x,int y)
{
	return x<1||x>n||y<1||y>m;
}
void dfs(int x,int y)
{
	t++;
	vis[x][y]=1;
	cnt[x][y]=tot;
	for(int i=0;i<4;i++) {
		int xx=dx[i]+x,yy=dy[i]+y;
		if(judge(xx,yy))continue;
		if(!a[xx][yy]&&!vis[xx][yy])dfs(xx,yy);
	}
}
int main()
{	
    cin>>n>>m;
	for(int i=1;i<=n;i++) {
		string s;
		cin>>s;
		for(int j=1;j<=m;j++)
			if(s[j-1]=='.')a[i][j]=0;
			else a[i][j]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!vis[i][j]&&!a[i][j]) {
				t=0;
				dfs(i,j);
				ans[tot]=t;
				tot++;
			}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++)
			if(!a[i][j])cout<<'.';
			else{
				t=1;
				set<int>s;
				for(int k=0;k<4;k++) {
					int xx=i+dx[k],yy=j+dy[k];
					if(!judge(xx,yy)&&!a[xx][yy])
						s.insert(cnt[xx][yy]);
				}
				for(set<int>::iterator it=s.begin();it!=s.end();it++)
        			t+=ans[*it];
				t%=10;
				cout<<t;
			}
		cout<<endl;
	}
	return 0;
}
```

（是错的，别急着复制

---

## 作者：HMZHMZHMZ (赞：0)

### 题意

给定一个只包含 `*`，`.`的图。如果原数组中的元素为 `*`，那么输出将这一位置变成 `.`后连通块的大小。

### 思路

对于每一个 `*`，它的答案就是旁边的所有连通块的个数之和。

如果每个点都暴力做不现实，所以要预处理，对于每一个连通块内的元素都打上标记，然后查询时判断有没有重复的即可。

时间复杂度 $ O( nm ) $。

### 代码

```cpp

#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb(x) push_back(x)
using namespace std;
const int N=1e3+10;
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};
ll ans;
char ch[N][N];
//bused 数组用于判断是否重复，为了不使用memset，我是用了一个时间戳
int n,m,T,used[N][N],siz[N*N],t,bused[N*N];
inline int read(){
	int s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
void dfs(int x,int y){
	++siz[t],used[x][y]=t;
	for(register int i=0;i<4;++i){
		int nx=x+dx[i],ny=y+dy[i];
		if(ch[nx][ny]=='.'&&!used[nx][ny]) dfs(nx,ny);
	}
}
int main(){
	n=read(),m=read();
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=m;++j){
			while(ch[i][j]!='*'&&ch[i][j]!='.') ch[i][j]=getchar();
		}
	}
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=m;++j){
			if(!used[i][j]&&ch[i][j]=='.'){
				t++;
				dfs(i,j);
			}
		}
	}
	int p=0;
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=m;++j){
			if(ch[i][j]=='*'){
				++p;
				ans=0;
				if(bused[used[i-1][j]]!=p&&i-1>=1) bused[used[i-1][j]]=p,ans+=siz[used[i-1][j]];
				if(bused[used[i+1][j]]!=p&&i+1<=n) bused[used[i+1][j]]=p,ans+=siz[used[i+1][j]];
				if(bused[used[i][j-1]]!=p&&j-1>=1) bused[used[i][j-1]]=p,ans+=siz[used[i][j-1]];
				if(bused[used[i][j+1]]!=p&&j+1<=m) bused[used[i][j+1]]=p,ans+=siz[used[i][j+1]];
				cout<<(ans+1)%10;
			}else putchar(ch[i][j]);
		}
		cout<<endl;
	}
	return 0;
}

---

## 作者：Insouciant21 (赞：0)

这一道题目如果每一个 `*` 都扫描一遍 `.`，肯定会超时

所以要先BFS预处理出每一个连通块

在 $1000\times1000$ 的方阵中最多有 $500000$ 个由 `.` 构成的联通块，所以储存 `.` 的数组只需要开到 $500000$。

在扫描联通块时要注意去除四周为同一个连通块的情况，以免重复计算。

``` cpp
#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, y;
};

char maze[1010][1010];
int vis[1010][1010];
int ans[500010]; // 以id形式储存连通块数量

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int n, m;
int cnt;

void bfs(Node st) {
    queue<Node> q;
    q.push(st);
    int block = 1;
    cnt++;
    vis[st.x][st.y] = cnt;
    while (q.size()) {
        Node prs = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            Node ftr = prs;
            ftr.x += dx[i], ftr.y += dy[i];
            if (ftr.x < 1 || ftr.y < 1 || ftr.x > n || ftr.y > m)
                continue;
            if (maze[ftr.x][ftr.y] != '.')
                continue;
            if (vis[ftr.x][ftr.y])
                continue;
            vis[ftr.x][ftr.y] = cnt;
            q.push(ftr);
            block++;
        }
    }
    block %= 10;
    ans[cnt] = block;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> maze[i][j];
        }
    }
    int now = 1;
    for (int i = 1; i <= n; i++) { // 预处理连通块
        for (int j = 1; j <= m; j++) {
            if (maze[i][j] == '.' && !vis[i][j]) {
                bfs({i, j});
            }
        }
    }
    for (int i = 1; i <= n; i++) { // 计算个数
        for (int j = 1; j <= m; j++) {
            if (maze[i][j] == '*') {
                long long block = 1;
                int id[4] = {-1, -1, -1, -1}; // 去重数组
                for (int k = 0; k < 4; k++) {
                    Node ftr;
                    ftr.x = i, ftr.y = j;
                    ftr.x += dx[k], ftr.y += dy[k];
                    if (ftr.x < 1 || ftr.y < 1 || ftr.x > n || ftr.y > m)
                        continue;
                    bool ok = false;
                    for (int p = 0; p < k; p++) { // 去除相同情况
                        if (vis[ftr.x][ftr.y] == id[p]) {
                            ok = true;
                            break;
                        }
                    }
                    if (ok)
                        continue;
                    block += ans[vis[ftr.x][ftr.y]];
                    id[k] = vis[ftr.x][ftr.y];
                }
                block %= 10;
                maze[i][j] = block + '0';
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
    return 0;
}
```

---

