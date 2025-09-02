# Battleship

## 题目描述

Arkady is playing Battleship. The rules of this game aren't really important.

There is a field of $ n \times n $ cells. There should be exactly one $ k $ -decker on the field, i. e. a ship that is $ k $ cells long oriented either horizontally or vertically. However, Arkady doesn't know where it is located. For each cell Arkady knows if it is definitely empty or can contain a part of the ship.

Consider all possible locations of the ship. Find such a cell that belongs to the maximum possible number of different locations of the ship.

## 说明/提示

The picture below shows the three possible locations of the ship that contain the cell $ (3, 2) $ in the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF965B/b7c4313703d490a5e475cf95767f647ad1140332.png)

## 样例 #1

### 输入

```
4 3
#..#
#.#.
....
.###
```

### 输出

```
3 2
```

## 样例 #2

### 输入

```
10 4
#....##...
.#...#....
..#..#..#.
...#.#....
.#..##.#..
.....#...#
...#.##...
.#...#.#..
.....#..#.
...#.#...#
```

### 输出

```
6 1
```

## 样例 #3

### 输入

```
19 6
##..............###
#......#####.....##
.....#########.....
....###########....
...#############...
..###############..
.#################.
.#################.
.#################.
.#################.
#####....##....####
####............###
####............###
#####...####...####
.#####..####..#####
...###........###..
....###########....
.........##........
#.................#
```

### 输出

```
1 8
```

# 题解

## 作者：_Cloud_ (赞：5)

# 枚举
不用记忆化这么麻烦，直接暴力枚举哪些位置可以放船：有条理枚举，先**横向枚举**所有**横着放**的船，再**纵向枚举**所有**竖着放**的船。最后再依次寻找哪个点被覆盖最多次。

### 特别注意：当一组数据为n=1,k=1时，输出0 0是会WA的,因为它不在任何单元中。  机翻↓

```cpp
如果有多个答案，请输出其中任何一个。 特别是，如果没有船只可以放置在现场，则可以输出任何单元。
```
所以我的代码特判了这个数据，输出n n。或者将答案初始化成任意一个坐标都可以防这组hack数据。

###### 题外话：目前这个是最快的，比记忆化还快。。。

### $Code$
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 105;

char s[N][N];
int a[N][N], ans, ansi, ansj;

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	
	for (int i = 1; i <= n; i++) {//枚举横向放船 
		for (int j = 1; j + k - 1 <= n; j++) {//因为从j开始数k个为： j+0, j+1, j+2 ...j+k-1，故循环到j+k-1 
			bool ok = true;
			for (int p = 0; p < k; p++) {//同理 
				if (s[i][p + j] == '#') { ok = false; break; }//不满足放船，退出 
			}
			if (ok == true) { for (int p = 0; p < k; p++) a[i][p + j]++; }//满足，每个点答案+1 
		}
	}
	
	for (int i = 1; i + k - 1 <= n; i++) {//枚举纵向放船,因为是纵向，所以i+k-1<=n 
		for (int j = 1; j <= n; j++) {
			bool ok = true;
			for (int p = 0; p < k; p++) {
				if (s[i + p][j] == '#') { ok = false; break; }//不满足，退出 
			}
			if (ok == true) { for (int p = 0; p < k; p++) a[i + p][j]++; }//满足，记录答案 
		}
	}
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (ans < a[i][j]) { ans = a[i][j]; ansi = i, ansj = j; }//枚举每个点的覆盖次数，找最大的 
	
	if (ans == 0)//特判
		printf("%d %d\n", n, n);
	else
		printf("%d %d\n", ansi, ansj);//正常输出
	return 0;
} 
```

###### ~~求管理大大通过o(*￣▽￣*)ブ~~


---

## 作者：zgy_123 (赞：1)

CSP 考前 45days 写题解，增加 rp。

此题是个十分明显的模拟题，直接暴力即可，在此我提供一种不同的解法，个人认为更为直接：我们发现题目中需要找到覆盖次数最多的点，大多数人肯定一开始都会想先把能放的都放了，最后统一处理。但是，我想到的是一个类似于在线处理的做法。

具体做法：对于每个点，挨个计算起上下左右四个方向的连续的 `.` 数量，进而处理出放置在这个点上的船的数量，随后就可以统计了。

举个例子：如果某个点及其上方连续的 `.` 个数为 $u$，下方为 $d$，则对此点放船数量的贡献为：

$$\left\{\begin{matrix}u+d-1<k&0\\u+d-1\ge k&u+d-k\end{matrix}\right.$$

另外，注意当 $k=1$ 时要特判。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[105][105];
int n,k;
int getmax(int dx,int dy,int x,int y){
	int ans=0,nx=x,ny=y;
	while(nx>0&&ny>0&&nx<=n&&ny<=n&&!a[nx][ny]&&ans<k)
		nx+=dx,ny+=dy,ans++;
	return ans;
}
#define m(a,b) getmax(a,b,i,j)
int main(){
	int ansx=1,ansy=1,maxx=-2e9;
	char x;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			cin>>x;
			if(x=='#') a[i][j]=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(a[i][j]) continue;
			int u=m(-1,0),d=m(1,0),l=m(0,-1),r=m(0,1);
			int cnt=max(0,u+d-k)+max(0,l+r-k);
			if(k==1) cnt=1;
			if(cnt>maxx) maxx=cnt,ansx=i,ansy=j;
		}
	cout<<ansx<<' '<<ansy;
	return 0;
}

```

---

## 作者：small_turtle (赞：1)

数据范围挺小，可以直接爆搜。
***
只需要对每个点向左边和下边搜索，判断是否能放下 $1\times k$ 的船，如可以则将船覆盖的地方的覆盖数加一，最后求一遍最大值即可。
***
**特别注意：**
```
If there are multiple answers, output any of them. In particular, if no ship can be placed on the field, you can output any cell.
```
我们需要特判 $n=1,k=1$ 的数据，这时候我们不应该输出 `0 0`。
***
### CODE：
```cpp
/*
Author:xwg
Time:2022.10.1
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define unordered_map map
const int inf=2147483647;
const double eps=1e-6;
using namespace std;
//#define DEBUG aerr();
int DEBUG_NUM=1;

void err(auto serr)
{
	cerr<<serr<<"\n";
}

void aerr()
{
	cerr<<"The "<<DEBUG_NUM++<<" line of debug information:\n";
}

int n,k,maxx,maxy,a[105][105];
char tmp;
bool g[105][105];

void ldfs(int step, int x, int y)
{
	if(x>n||y>n||x<1||y<1)
	{
		return;
	}
	if(!g[x][y])
	{
		return;
	}
	if(step==k)
	{
		int o=x-k+1;
		for(int i=x;i>=o;--i)
		{
			++a[i][y];
		}
		return;
	}
	ldfs(step+1, x+1, y);
}

void ddfs(int step, int x, int y)
{
	if(x>n||y>n||x<1||y<1)
	{
		return;
	}
	if(!g[x][y])
	{
		return;
	}
	if(step==k)
	{
		int o=y-k+1;
		for(int i=y;i>=o;--i)
		{
			++a[x][i];
		}
		return;
	}
	ddfs(step+1, x, y+1);
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			cin>>tmp;
			if(tmp=='.')
			{
				g[i][j]=true;
			}
			else
			{
				g[i][j]=false;
			}
		}
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			ldfs(1, i, j);
			ddfs(1, i, j);
		}
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			if(a[i][j]>a[maxx][maxy])
			{
				maxx=i;
				maxy=j;
			}
		}
	}
	printf("%d %d", max(1, maxx), max(1, maxy));
	return 0;
}
```
管理辛苦了 QAQ。

---

## 作者：sinsop90 (赞：1)

这道题并不需要 $DFS$ , 主要的核心思想是暴力

我们考虑枚举每一个点,在每一个点上都枚举以这个点为开始点来放置船只

如果这个船只是可以放下的,就将船覆盖的位置的值增加

于是我们便会遇到一个问题,如果 $k = 3$

那么我在 $(1, 4)$ 能放下从 $(1, 4)$ 到 $(1, 7)$ 的船只

那么我在 $(1, 7)$ 遍历时,也会放下船只, 就会导致从 $(1, 4)$ 到 $(1, 7)$的值增加 $2$

因此我们考虑遍历每一个点时,只往下面和右边进行遍历,看能不能放置船只

因此有了代码:

```
#include<bits/stdc++.h>
using namespace std;
char mps[1005][1005];
int ans[1005][1005], maxn = -1;
int fx[2][2] = {1, 0, 0, 1};//往下面和右边枚举
signed main() {
	int n, m, o, p;
	scanf("%d%d",&n, &m);
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			cin >> mps[i][j];
		}
	}
	o = n;
	p = n;
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			if(mps[i][j] != '#') {
				for(int k = 0;k <= 1;k++) {
					bool flag = true;
					int x = i, y = j;
					for(int l = 1;l <= m - 1;l++) {
						x += fx[k][0];
						y += fx[k][1];
						if(mps[x][y] != '.' || x==0 || y == 0 || x == n+1 || y == n+1) {
							flag = false;//如果放不了船只...
							break;
						}
						
					}
					if(flag == true) {//如果可以放下船只
						x = i;
						y = j;
						ans[x][y] ++;
						if(ans[x][y] > maxn) {
							o = x;
							p = y;
							maxn = ans[x][y];
						}
						for(int l = 1;l <= m-1;l++) {
							x += fx[k][0];
							y += fx[k][1];
							ans[x][y] ++;//值增加1
							if(ans[x][y] > maxn) {
								o = x;
								p = y;
								maxn = ans[x][y];
							}
						}
					}
				}
			}
		}
	}
	cout << o << " " << p << endl;
}
```


---

## 作者：_HiKou_ (赞：0)

~~想不到吧这道题可以用前缀和~~

~~但是挺麻烦的~~

思路：

1. 把字符输进来，如果是障碍则把它变成 1，否则为 0。
2. 对这个矩阵进行横向的一维前缀和（其实二维也可以，只用做一次，但是这道题没必要）
3. 从**第 0 个**开始枚举所有横着放的船（这里坑了我好久，因为 $a[i][j+k]-a[i][j]$ 的差应该为 $x[i][j+1]$ 到 $x[i][j+k]$ 的和。如果从 1 开始，那么就会从第 2 个开始计算，第二个点就会 WA），如果可以放就把 ans 数组里同样位置的数 +1。
4. 竖向操作同理。
5. 找寻最大坐标，输出。结束。

整体思路还是比较简单，如果这道题不是 $1×k$ 的话可能要用二维前缀和，但是如果是 $1×k$ 的话那就用用一维吧！（实际上只是我懒而已）

当然，如果 $n＜k$ 的话那么即使全是空的也放不下。所以就随便输出一个坐标就好了.（但是这个坐标必须在矩阵里所以输出两个 1 是最好的）

CODE：

```
#include<bits/stdc++.h>
using namespace std;
int x[114][514];//这里以及下面两行都是恶臭数组，不要看了
int a[114][514];
int ans[114][514];
int main(){
	int n,k,i,j;
	scanf("%d%d",&n,&k);
	if(n<k)//这里是特判
	{
		printf("1 1");
		return 0;
	}
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	{
		char w;
		cin>>w;//由于scanf好像会把回车一起输进去所以我用了 cin
		if(w=='#')x[i][j]=1;//为前缀和做好准备
	}
	
    
    
    
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	a[i][j]=a[i][j-1]+x[i][j];//横向一维前缀和
	
	for(i=1;i<=n;i++)
	for(j=0;j<=n-k;j++)//防止越界 以及 从 0 开始
	{
		if(a[i][j]==a[i][j+k])//如果相等，代表他们
		for(int l=j+1;l<=j+k;l++)ans[i][l]++;//标记
	}
    
    
    

	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	a[i][j]=a[i-1][j]+x[i][j];/同理，这次求竖向前缀和
	
	for(i=0;i<=n-k;i++)//因为是竖向所以竖向的应该为 0
	for(j=1;j<=n;j++)
	{
		if(a[i][j]==a[i+k][j])
		{
			for(int l=i+1;l<=i+k;l++)ans[l][j]++;
		}
	}
	int dx=1,dy=1;//先预设坐标
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	{
		if(ans[dx][dy]<ans[i][j])//如果小于它就赋值成新的
		{
			dx=i,dy=j;
		}
	}
	
	
	
	printf("%d %d",dx,dy);
	
	
	return 0;
}
```

---

## 作者：zery (赞：0)



------------

## 先解释一下题目的大概意思：
- 有一个n维方正阵图，‘#’是障碍，‘.‘是空位置 ，一艘长为k的船在矩阵内可以任意朝向的放置（不能斜着）。

- 找出可以放船的点，**如果有多个点，优先选择船覆盖
该点时放置方法最多的点！！（能被船覆盖次数最多的点）**这个是一个大坑千万别忽略了。
- 如果没的放就随便输出一个点。


------------
## 方法：记忆化搜索：
- 不难想到是沿着一个方向一直搜下去，而且只有搜到底才是对的，不过我们没有必要每次都搜到底，**以点为单位4个方向分别记忆是否经过这个点朝某个方向搜过**。当然也要分别记录某点4个方向跑到底的长度以便返回值。

- 因为题目最后有一个优选点的限制，因为运用了记忆化很多地方我们是直接返回记忆值的，那些点被船覆盖了几次我们只好**重新统计**。


------------
以下是有注解的代码：
```cpp
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <functional>
#include <math.h>
#include <memory.h>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include<memory>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n,k,ansx=1,ansy=1,dx[]={-1,0,1,0},dy[]={0,1,0,-1},maxx;
struct node{
  char key;//用来存图
  int dis[5]={1,1,1,1,0};//前4是记忆距离第5来存覆盖次数
  bool ok[4]={0};//4个方向是否搜过
};  
vector<vector<node>> m;
int search(int x,int y,int kk)
{
  int nx=x+dx[kk],ny=y+dy[kk];
  if(nx<0||nx>=n||ny<0||ny>=n||m[nx][ny].key=='#') return 0;
  if(m[nx][ny].ok[kk]) return m[nx][ny].dis[kk];
  m[nx][ny].dis[kk]+=search(nx,ny,kk);//记忆
  m[nx][ny].ok[kk]=1;//记忆
  return m[nx][ny].dis[kk];
  
}
int main()
{cin>>n>>k;
m.resize(n);
for(auto&i:m)
{
  i.resize(n);
  for(auto&j:i) cin>>j.key;
}//读入
for(int i=0;i<n;++i)
{
  for(int j=0;j<n;++j)
  {   if(m[i][j].key=='#')continue;
      for(int kk=0;kk<=3;++kk)//枚举4个方向
      {
        if(!m[i][j].ok[kk])//这里不能直接continue
        {
        m[i][j].dis[kk]+=search(i,j,kk);
        m[i][j].ok[kk]=1;       
        }  
        if(m[i][j].dis[kk]>=k)//更新覆盖
        {
          for(int p=0;p<k;++p)
          {
            m[i+dx[kk]*p][j+dy[kk]*p].dis[4]++;
           if(m[i+dx[kk]*p][j+dy[kk]*p].dis[4]>maxx)//寻找最优点
            maxx=m[i+dx[kk]*p][j+dy[kk]*p].dis[4],ansx=i+dx[kk]*p+1,ansy=j+dy[kk]*p+1;
          }
        }
      }
    
  }
}
 cout<<ansx<<" "<<ansy;
return 0;
}

```

---

