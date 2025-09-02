# Arthur and Walls

## 题目描述

Finally it is a day when Arthur has enough money for buying an apartment. He found a great option close to the center of the city with a nice price.

Plan of the apartment found by Arthur looks like a rectangle $ n×m $ consisting of squares of size $ 1×1 $ . Each of those squares contains either a wall (such square is denoted by a symbol "\*" on the plan) or a free space (such square is denoted on the plan by a symbol ".").

Room in an apartment is a maximal connected area consisting of free squares. Squares are considered adjacent if they share a common side.

The old Arthur dream is to live in an apartment where all rooms are rectangles. He asks you to calculate minimum number of walls you need to remove in order to achieve this goal. After removing a wall from a square it becomes a free square. While removing the walls it is possible that some rooms unite into a single one.

## 样例 #1

### 输入

```
5 5
.*.*.
*****
.*.*.
*****
.*.*.
```

### 输出

```
.*.*.
*****
.*.*.
*****
.*.*.
```

## 样例 #2

### 输入

```
6 7
***.*.*
..*.*.*
*.*.*.*
*.*.*.*
..*...*
*******
```

### 输出

```
***...*
..*...*
..*...*
..*...*
..*...*
*******
```

## 样例 #3

### 输入

```
4 5
.....
.....
..***
..*..
```

### 输出

```
.....
.....
.....
.....
```

# 题解

## 作者：Take_A_Single_6 (赞：10)

~~话说cf水题真多~~
## 题意概括
给你一个由`.`和`*`构成的矩阵，求让`.`能构成一些矩形且将`*`改为`.`次数最少的矩阵。
## 解题思路
需要注意的是**一个**`.`**也是矩形。**  
那么要改变只有以下四种情况：  
```
*.  .*  ..  ..
..  ..  .*  *.
```
改变一个`*`可能会使八个方向有所变化，所以我们可以遍历一遍矩阵，如果是`*`就8个方向DFS拓展并判断是否是要改变。  
## 代码实现
DFS时要注意**如果是**`.`**立即跳出。**  
code（含注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char a[2005][2005];
void dfs(int x,int y)
{
    if(x<0||x>=n||y<0||y>=m||a[x][y]=='.')return;//防越界和.跳出
    if((a[x+1][y]=='.'&&a[x+1][y+1]=='.'&&a[x][y+1]=='.')||(a[x-1][y]=='.'&&a[x-1][y-1]=='.'&&a[x][y-1]=='.')||(a[x+1][y]=='.'&&a[x+1][y-1]=='.'&&a[x][y-1]=='.')||(a[x-1][y]=='.'&&a[x-1][y+1]=='.'&&a[x][y+1]=='.'))a[x][y]='.';//可以分四个if写
    else return;//不需要改变就跳出
    dfs(x+1,y);//可以用方向数组
    dfs(x-1,y);
    dfs(x+1,y+1);
    dfs(x-1,y-1);
    dfs(x+1,y-1);
    dfs(x-1,y+1);
    dfs(x,y+1);
    dfs(x,y-1);
}
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            a[i][j]=getchar();//输入时无空格，所以cin不方便
			if(a[i][j]=='\n')//输入时注意换行
			a[i][j]=getchar();
		}
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(a[i][j]=='*')
                dfs(i,j);
    for(int i=0;i<n;i++)//输出矩阵而不是次数
    {
        for(int j=0;j<m;j++)
            cout<<a[i][j];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：When (赞：6)

#### 细节题

本文会把作者踩到的坑指出，以便您调试

#### 思路

贪心+$DFS$染色，算法其实很好想，考虑哪些$*$点是必须被替换的：

通过观察，我们发现，一个$*$点要被替换，当且仅当有一个包含它的$2\times 2$的矩阵中除它之外全是$.$点（当我们已经将其他需要替换的$*$点替换掉时）

**证明：** 当一个$*$点联通块需要被替换时，块内必然有一个$*$点被$.$点半包围（因为只有这样它才会阻碍$.$点组成矩形），于是我们将改点替换成$.$点。不难发现，块内剩下的$*$点又可以通过同样的方式判断

#### 坑

+ $DFS$每次应向周围$8$个点拓展；
+ 判断半包围时请老老实实列举每一种情况；
+ 判断或拓展新点时应确保其在图内
+ 只能$*$换$.$不能反过来换

#### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n,m;
char a[2020][2020];
int mx[8] = {0, 1, -1, 0, 1, -1, -1, 1};
int my[8] = {1, 0, 0, -1, 1, -1, 1, -1};

int check(int x, int y){
    if(x < 1 || x > n) return 0;
    if(y < 1 || y > m) return 0;
    return (a[x][y] == '.');
}

int exam(int i, int j){
    if(check(i - 1, j) && check(i, j - 1) && check(i - 1, j - 1)) return 1;
    if(check(i - 1, j) && check(i, j + 1) && check(i - 1, j + 1)) return 1;
    if(check(i + 1, j) && check(i, j - 1) && check(i + 1, j - 1)) return 1;
    if(check(i + 1, j) && check(i, j + 1) && check(i + 1, j + 1)) return 1;
    return 0;
}

void DFS(int x, int y){
    for(int i = 0; i < 8; ++ i){
        int nx = x + mx[i];
        int ny = y + my[i];
        if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && a[nx][ny] == '*' && exam(nx, ny))
            a[nx][ny] = '.', DFS(nx, ny);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j) 
            cin >> a[i][j];
    
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j)
            if(a[i][j] == '*'){
                if(exam(i, j)) a[i][j] = '.', DFS(i, j);
            }    
    
    for(int i = 1; i <= n; ++ i){
        for(int j = 1; j <= m; ++ j)
            cout << a[i][j];
        cout << endl;
    }
    return 0;
}
```



---

## 作者：D2T1 (赞：4)

### 思路：

贪心+DFS。

首先，在一个 $2*2$ 的矩阵里有三个 $'.'$，一个 $'*'$ 时，这个 $'*'$ 就要被替换。

例如下图 4 种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/lxtorsyi.png)

其中 $'.'$ 所形成的区域一定不为一个矩形，所以当整个矩阵出现上图 4 种情况时就要替换 $'*'$。

但是，替换掉一个 $'*'$ 以后又可能会在它的周围 8 个格子内形成上图 4 种情形，这时可以使用 DFS 解决。

### 代码

```cpp
//CF525D
#include <iostream>
using namespace std;

const int maxn=2010;
int dx[8]={-1,-1,-1,0,0,1,1,1},dy[8]={-1,0,1,-1,1,-1,0,1};
char a[maxn][maxn];
inline bool judge(int i,int j){//判断是否是那4种情况
	if(a[i][j]!='*') return false;
	if(a[i-1][j-1]=='.'&&a[i][j-1]=='.'&&a[i-1][j]=='.') return true;
	if(a[i+1][j-1]=='.'&&a[i][j-1]=='.'&&a[i+1][j]=='.') return true;
	if(a[i-1][j+1]=='.'&&a[i][j+1]=='.'&&a[i-1][j]=='.') return true;
	if(a[i+1][j+1]=='.'&&a[i][j+1]=='.'&&a[i+1][j]=='.') return true;
	return false;
}
inline void dfs(int i,int j){//DFS
	if(!judge(i,j)) return;
	a[i][j]='.';
	for(int k=0; k<8; ++k) dfs(i+dx[k],j+dy[k]);//注意一个点可以影响它周围8个点而不是4个
	return;
}

int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=1; i<=n; ++i)//从1开始，相当于构建一圈虚拟边框，防止越界
		for(int j=1; j<=m; ++j)
			cin>>a[i][j];
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			dfs(i,j);
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j)
			cout<<a[i][j];
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：撤云 (赞：2)

[广告](https://www.cnblogs.com/hbxblog/p/11412615.html)

### $Solution$

如果一个`#`要更改，那么一个四个格子的正方形只有他一个是`#`,bfs弄一下就好了

### $Code$

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9,mod=1e9+7;
typedef long long ll;
int read() {
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?-1:1,c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}
struct node {
	int x,y;
};
queue<node> q;
int n,m;
char a[3001][3001];
int c[3001][3001];
int b[10];
int fx[10]= {0,0,0,1,-1};
int fy[10]= {0,1,-1,0,0};
void bfs() {
	while(!q.empty()) {
		node now=q.front();
		q.pop();
		int x=now.x,y=now.y;
		b[1]=b[2]=b[3]=b[4]=0;
		if(x!=1&&y!=1)
			b[1]=c[x-1][y-1]+c[x-1][y]+c[x][y-1];
		if(x!=1&&y!=m)
			b[2]=c[x-1][y+1]+c[x-1][y]+c[x][y+1];
		if(x!=n&&y!=1)
			b[3]=c[x+1][y-1]+c[x+1][y]+c[x][y-1];
		if(x!=n&&y!=m)
			b[4]=c[x+1][y+1]+c[x+1][y]+c[x][y+1];
		if(b[1]==1) {
			if(c[x-1][y-1]) q.push((node){x-1,y-1}),c[x-1][y-1]=0;
			if(c[x-1][y]) q.push((node){x-1,y}),c[x-1][y]=0;
			if(c[x][y-1]) q.push((node){x,y-1}),c[x][y-1]=0;
		}
		if(b[2]==1) {
			if(c[x-1][y+1]) q.push((node){x-1,y+1}),c[x-1][y+1]=0;
			if(c[x-1][y]) q.push((node){x-1,y}),c[x-1][y]=0;
			if(c[x][y+1]) q.push((node){x,y+1}),c[x][y+1]=0;
		}
		if(b[3]==1) {
			if(c[x+1][y-1]) q.push((node){x+1,y-1}),c[x+1][y-1]=0;
			if(c[x+1][y]) q.push((node){x+1,y}),c[x+1][y]=0;
			if(c[x][y-1]) q.push((node){x,y-1}),c[x][y-1]=0;
		}
		if(b[4]==1) {
			if(c[x+1][y+1]) q.push((node){x+1,y+1}),c[x+1][y+1]=0;
			if(c[x+1][y]) q.push((node){x+1,y}),c[x+1][y]=0;
			if(c[x][y+1]) q.push((node){x,y+1}),c[x][y+1]=0;
		}
	}
}
main() {
	n=read(),m=read();
	for(int i=1; i<=n; i++) {
		scanf("%s",a[i]+1);
		for(int j=1; j<=m; j++){
			if(a[i][j]=='.')
				q.push((node) {i,j});
			else c[i][j]=1;
		}
	}
	bfs();
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=1;j<=m;j++)
			if(c[i][j]==1)
				cout<<"*";
			else cout<<"."; 
}
```

---

## 作者：zzqDeco (赞：1)

今天折磨了2个多小时

首先，这个点变成```.```的条件就是所在的某一个`2*2`的矩形除了他都是```.```

上面的大概理解起来就是分形，一个`2*2`的矩形是最小的有强制要求的矩形，并且可以发现其他矩形如果包含这个图形无论如何都不能变成矩形，必须将其填满，又因为你填的这一步是有价值且必要的，那也就保证是最小填充法

那么和在他周围一个九宫格都会以为这个点的改变而有可能改变，在代码实现的时候就可以用 bfs 加入`.`周围的点，来进行松弛

（用cin一定要关同步，TLE原来是因为这个）

```cpp

#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int n,m;

char map[5000][5000];

queue<pair<int,int>>q;

int dx[]={1,-1,0,0,1,-1,1,-1};
int dy[]={0,0,1,-1,1,-1,-1,1};

bool check(int i,int j)
{
  if(i<1||i>n||j<1||j>m) return 0;
  if((map[i-1][j]=='.'&&map[i][j-1]=='.'&&map[i-1][j-1]=='.')||(map[i+1][j]=='.'&&map[i][j-1]=='.'&&map[i+1][j-1]=='.')||(map[i-1][j]=='.'&&map[i][j+1]=='.'&&map[i-1][j+1]=='.')||(map[i+1][j]=='.'&&map[i][j+1]=='.'&&map[i+1][j+1]=='.')) return 1;
  return 0;
}

int main()
{
  ios::sync_with_stdio(false);
  cin>>n>>m;
  for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) 
  {
    cin>>map[i][j];
    if(map[i][j]=='.') q.push(make_pair(i,j));
  }
  while(!q.empty())
  {
    int i=q.front().first,j=q.front().second;
    q.pop();
    for(int now=0;now<8;now++)
    {
      if(map[i+dx[now]][j+dy[now]]=='*'&&check(i+dx[now],j+dy[now]))
      {
        map[i+dx[now]][j+dy[now]]='.';
        q.push(make_pair(i+dx[now],j+dy[now]));
      }
    }
  }
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++) cout<<map[i][j];
    cout<<"\n";
  }
}
```

---

## 作者：清平乐 (赞：1)

首先要清楚这样一个性质：在一个 $2\times2$ 的矩形中，当且仅当这个矩形中只有一个 $*$ 时我们对其进行修改，任何一个大于 $2\times2$ 的矩形都可以拆分成若干相交的 $2\times2$ 的矩形

比如下面这种情况我们会进行修改：

```cpp
. *
. .
```


而这几种情况我们不对其进行操作：
```cpp
. *     * *     * *
. *     . *     * *
```

~~其实具体证明我也不会~~，但可以自己感性理解一下

具体的实现过程我们可以使用 BFS 进行染色

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

const int N=2005;
const int dx[]={0,1,1,1,0,-1,-1,-1},dy[]={1,1,0,-1,-1,-1,0,1};
int n,m;
char s[N][N];
bool visit[N][N];
queue<pair<int,int> > q;

inline bool check(int x,int y)
{
	return (s[x-1][y-1]=='.'&&s[x-1][y]=='.'&&s[x][y-1]=='.')||(s[x-1][y+1]== '.'&&s[x-1][y]=='.'&&s[x][y+1]== '.')||(s[x+1][y-1]=='.'&&s[x+1][y]=='.'&&s[x][y-1]=='.')||(s[x+1][y+1]=='.'&&s[x+1][y]=='.'&&s[x][y+1]=='.');
}

inline bool BFS(void)
{
	while(!q.empty())
	{
		pair<int,int> u=q.front();
		q.pop();
		s[u.first][u.second]='.';
		visit[u.first][u.second]=true;
		for(register int i=0;i<8;++i)
		{
			int nx=u.first+dx[i];
			int ny=u.second+dy[i];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&!visit[nx][ny]&&check(nx,ny))
			{
				q.push(make_pair(nx,ny));
				visit[nx][ny]=true;
			}
		}
	}
}

int main(void)
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=m;++j)
			if(s[i][j]=='.') visit[i][j]=true;
			else if(check(i,j)) q.push(make_pair(i,j));
	BFS();
	for(register int i=1;i<=n;++i)
		puts(s[i]+1);
	return 0;
}
```


---

## 作者：Sternenlicht (赞：0)

思路：贪心 + DFS。

在 $2 \times 2$ 的矩阵中，若其中有 $3$ 个 `.`，则剩下的 `*` 需改为 `.` 。且改变一个 `*` 可能会使周边八个方向有变动，需 DFS 枚举修改。

注意 DFS 时，若当前点为 `.`，则无需修改，直接退出，防止爆栈。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

const int N = 2e3+10;
const int dx[] = {0,1,-1,1,-1,1,-1,0,0};
const int dy[] = {0,0,0,1,-1,-1,1,1,-1};
char a[N][N];int n,m;
bool check(int x,int y)//判断是否越界或当前点为. 
{return (x>=1&&x<=n&&y>=1&&y<=m&&a[x][y]!='.');}
void dfs(int x,int y){//遍历更改*为. 
	if (!check(x,y))return;
	//更新 
	if (a[x+1][y]=='.'&&a[x][y+1]=='.'&&a[x+1][y+1]=='.')a[x][y]='.';
	if (a[x-1][y]=='.'&&a[x][y-1]=='.'&&a[x-1][y-1]=='.')a[x][y]='.';
	if (a[x+1][y]=='.'&&a[x][y-1]=='.'&&a[x+1][y-1]=='.')a[x][y]='.';
	if (a[x-1][y]=='.'&&a[x][y+1]=='.'&&a[x-1][y+1]=='.')a[x][y]='.';
	if (a[x][y]!='.')return;//若没有更新，直接退出
	for (int i=1;i<=8;i++)dfs(x+dx[i],y+dy[i]);//遍历八个方向更新 
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			cin>>a[i][j];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]=='*')
				dfs(i,j);//若当前点是*，就dfs更新，贪心
	for (int i=1;i<=n;i++,puts(""))
		for (int j=1;j<=m;j++)
			cout<<a[i][j];
	return 0;
}
```

---

## 作者：XL4453 (赞：0)


题目分析：

考虑贪心。

结论是当出现仅有一个星号处于一个二阶矩阵的一个角时，将其改成点。

也就是：

	.*	*.	..	..
    ..	..	*.	.*
这四种情况中的任意一个。

------------
为什么这样是对的。

首先是充分性。发现如果这样的小矩形一定是最小的一种构不成矩形的情况，而且一定不存在避开这种情况的且无法构成矩形的方案。

然后是必要性。同样是因为这样的矩形是最小的可能的无法构成矩形情况，将所有的小矩形更改完后一定是合法情况，所以再进行额外更改一定是不优的。

感性理解。

------------
代码:

```cpp
#include<cstdio>
using namespace std;
char m[2005][2005];
int n,mm,dx[8]={0,0,1,-1,1,1,-1,-1},dy[8]={1,-1,0,0,-1,1,1,-1};
void dfs(int x,int y){
	if(m[x][y]=='.'||x>n||x<=0||y>mm||y<=0)return;
	if(	(m[x+1][y]=='.'&&m[x][y+1]=='.'&&m[x+1][y+1]=='.')||
		(m[x+1][y]=='.'&&m[x][y-1]=='.'&&m[x+1][y-1]=='.')||
		(m[x-1][y]=='.'&&m[x][y+1]=='.'&&m[x-1][y+1]=='.')||
		(m[x-1][y]=='.'&&m[x][y-1]=='.'&&m[x-1][y-1]=='.')){
		m[x][y]='.';
		for(int i=0;i<=7;i++)
		dfs(x+dx[i],y+dy[i]);
	}
}
int main(){
	scanf("%d%d",&n,&mm);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=mm;j++){
			scanf("%c",&m[i][j]);
			if(m[i][j]=='\n')
			scanf("%c",&m[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=mm;j++){
			if(m[i][j]=='*')
			dfs(i,j);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=mm;j++){
			printf("%c",m[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Level_Down (赞：0)

题意很明确，不再阐述了，这里说一下方法以及一些其他。

因为题意中明确说要输出变化最少的解，所以我们考虑贪心。

对于每一个 $*$，当且仅当只有它所在的每一个 $2 * 2$ 的矩形中只有它一个是 $*$，我们才将它变成 $.$，并且没有例外，因为如果不变换，必然会有一个 $.$ 的矩阵的一角有缺口，可以证明这个贪心是正确的。

再仔细讲一下这个贪心方法：

现在有一个矩阵：

```
ABC
DEG
HIJ
```

我们需要判断 $E$ 是否需要被替换（$E$ 是 $*$）那么我们需要判断矩形 $ABDE$、$BCEG$、$DEHI$、$EGIJ$ 中只要有任意一个矩形中只有 $E$ 是 $*$，那么 $E$ 就需要被替换。

然后边DFS边判断是否需要被替换就可以AC这道题了。

还要注意一下DFS得向 8 个方向DFS，否则会WA。

还有一些坑点写在代码里：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
char a[2005][2005];
int ck(int i,int j)
{
	if (a[i][j] == '.') return 0;//这个写不写都行。
	if (a[i][j + 1] == '.' && a[i + 1][j + 1] == '.' && a[i + 1][j] == '.') return 1;
	else if (a[i][j + 1] == '.' && a[i - 1][j + 1] == '.' && a[i - 1][j] == '.') return 1;
	else if (a[i][j - 1] == '.' && a[i - 1][j - 1] == '.' && a[i - 1][j] == '.') return 1;
	else if (a[i][j - 1] == '.' && a[i + 1][j - 1] == '.' && a[i + 1][j] == '.') return 1;
    //以上4行是对4个矩形分别的判断，也就是贪心。
	return 0;
} 
void dfs(int i,int j)
{
	if (i < 1 || i > n || j < 1 || j > m || a[i][j] == '.') return;
    //判断越界。
	if (ck(i,j)) a[i][j] = '.';
	else return;//这里一定要return，否则12个点会RE。
	dfs(i + 1,j);
	dfs(i - 1,j);
	dfs(i,j + 1);
	dfs(i,j - 1);
	dfs(i + 1,j + 1);
	dfs(i + 1,j - 1);
	dfs(i - 1,j + 1);
	dfs(i - 1,j - 1);//向8个方向DFS。
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				{
					a[i][j] = getchar();//这里用cin和cout也不会超时。
					if (a[i][j] == '\n') a[i][j] = getchar();
				}
		}
	for (int i = 1; i <= n; i++)//DFS全过程。
		{
			for (int j = 1; j <= m; j++)
				{
					if (ck(i,j))
					{
						dfs(i,j);
					}
				}
		}	
	for (int i = 1; i <= n; i++)//输出。
		{
			for (int j = 1; j <= m; j++)
				{
					putchar(a[i][j]);
				}
			printf("\n");	
		}		
	return 0;//AC！		
}
```

希望我的题解对大家有帮助。


---

