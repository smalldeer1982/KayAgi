# Cutting Figure

## 题目描述

You've gotten an $ n×m $ sheet of squared paper. Some of its squares are painted. Let's mark the set of all painted squares as $ A $ . Set $ A $ is connected. Your task is to find the minimum number of squares that we can delete from set $ A $ to make it not connected.

A set of painted squares is called connected, if for every two squares $ a $ and $ b $ from this set there is a sequence of squares from the set, beginning in $ a $ and ending in $ b $ , such that in this sequence any square, except for the last one, shares a common side with the square that follows next in the sequence. An empty set and a set consisting of exactly one square are connected by definition.

## 说明/提示

In the first sample you can delete any two squares that do not share a side. After that the set of painted squares is not connected anymore.

The note to the second sample is shown on the figure below. To the left there is a picture of the initial set of squares. To the right there is a set with deleted squares. The deleted squares are marked with crosses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF193A/cc2de3ad5afd093ec1251f928cbdde2a451e56d2.png)

## 样例 #1

### 输入

```
5 4
####
#..#
#..#
#..#
####
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
#####
#...#
#####
#...#
#####
```

### 输出

```
2
```

# 题解

## 作者：_StarBird_ (赞：9)

### 写在前面的闲话
~~这题翻译我写的~~

本文在博客食用更佳https://www.luogu.org/blog/jch2008/

第一篇题解，求支持qwq

声明：这篇题解很长，可能会占用您的时间，敬请谅解！

-----------------------------------------------------分割线---------------------------------------------------

咳咳，这题，如果直接暴力枚举每一个点是否擦掉，如果没成功就继续枚举，成功了就取min，时间复杂度就会十分难算，极不稳定~~虽然可能能卡过~~。因此，为了~~装逼~~锻炼思维，我们需要优化该算法。

聪明的你一看样例，发现输出都是2，而你也知道存在输出是1的情况，顿时来了灵感,：我们能否证明，最多删除两个，就能使这个图变得不连通呢？

### 华丽丽的证明过程：
现在，你拥有一个3*4的长方形，1表示涂色，0表示不涂色。
```
1111
1111
1111
```
那么， 请把目光聚焦在四个角落上， 只要有任意一个角落是1，我们就可以将他它相邻的两个点擦掉（这里选的是右下角），形成
```
1111
1110
1101
```
这样的局面，于是，整个图就变得不联通了。

很好，那么，要是4个角都没有涂色，该怎么办呢？

先画出图：
```
0110
1111
0110
```

于是，你又将目光聚焦在落单的，最边上的6个点上。我的表述可能不清楚，就是位于{1,2}、{1,3}、{2,1}、{2,4}、{3,2}、{3,2}这几个点。它们本有三个相邻点，但现在因为角上的被擦掉，只剩两个了。于是，我们又可以将这两个点擦掉，形成

```
0100
1011
0110
```

这样的局面，于是，整个图就又变得不联通了。

虽然在这个图里，最外面的边上点已经擦完了，但为了思维的严谨性，我们还需证明更大的图。稍微想一下便可得知，在更大的图里，如果我们把与角相邻的边上点擦去，最外面的边上，还会有靠边的点，本来有三个相邻。现在因角相邻的边上点被擦去了，只剩两个相邻了……于是，我们就可以“断绝它的后路”，使得图变得不联通。

Q:那么，如果把整一圈边都擦去呢？

A:那么，你就得到了一个更小的长方形。那么现在， 请把目光聚焦在小长方形的四个角落上，只要有任意一个角落是1，我们就可以将他它相邻的两个点擦掉……

**于是，我们得出了这道题的证明过程。**

看到这里，你瞬间想到了思路：只要求出每个点相邻的点数，然后求一个min，就可以保证把这个点封死，得到这题的正确答案了！于是，你迫不及待地开始敲了起来，边敲边想：不对呀，这种做法跟刚才的证明过程没关系呀，我白看了这么长的题解！写题解的一看就是个菜鸡！结果一交，听取WA声一片。。。

别急，让本蒟蒻造个数据。
```
5 5
11111
11111
00100
11111
11111

AC answer:
1
YOUR answer:
2
```

是不是崩溃了。。。

所以，有强迫症的同学（我绝对不会告诉你说的就是我）请注意了，装逼一时爽，一直装逼。。。两行泪。所以，请牺牲一些时间复杂度，写一个dfs。

此题dfs的思路很简单，就是枚举删掉的点，跑一遍dfs,看看能否使得只删掉这一个点，使图变得不连通。
 
但是，此题有一坑点，就是我翻译的输出部分那块。要输出-1的！当一共只有0个，1个，2个时，无论怎么删，也都不能成功！（ps:“根据定义，只有一个方格的集合或者不包含任何方格的集合也是联通的。”看到没！？）
 
 好，思路就讲到这儿，接下来是你们最喜欢的部分——~~求点赞关注~~上代码。
#  code:

=

```cpp
//建议的阅读程序顺序：头文件区（自己编的）->主程序->主程序顺序下的子函数 
#include<iostream>//鄙人不喜欢万能库，一个是map重定义的原因，另一个是窝有强迫症（捂嘴） ,另外，本菜鸡还喜欢用short鸭，register鸭，宏定义鸭，但为了水题解，还是删掉了 
#include<cstring>
using namespace std;
int n,m;
char map[51][51];//输入的图 
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};//行走数组（窝取的名） 
bool vis[51][51];//标记数组 
void dfs(int x,int y)
{
	if (x<1||x>n||y<1||y>m) return;//判断出界，可有可无 
	vis[x][y]=true;//打标记 
	for(int w=1;w<=4;++w)//这个1到4还是0到3看个人喜好吧 
	{
		int xx=x+dx[w],yy=y+dy[w];//行走数组，模拟每种步数可能出现的情况，十分好用 
		if (map[xx][yy]=='#'&&!vis[xx][yy]) dfs(xx,yy);//如果符合，继续深搜 
	}
	return;
}
inline bool check(int x,int y)//inline优化，看看就好 
{
	memset(vis,false,sizeof(vis));//清空标记数组
	bool flag=false;//这货的用处往下看就知道了 
	vis[x][y]=true;//打上该点的标记 
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			if (map[i][j]=='#'&&!vis[i][j])//如果找到了未改变的点 
			{
				if (flag) return true;//第一次警告（试跑一遍删除该点后剩下的点，看能否一次性连光） 
				else flag=true;//第二次驱离（成功） 
				dfs(i,j);//跑dfs 
			}
		}
	return false;//如果没找到（依然全部连通），wasted 
}
int main(void)
{
	ios_base::sync_with_stdio(false);//cin优化，看看就好，适合窝这样的强迫症（再次捂嘴） 
	cin.tie(0);
	cin>>n>>m;//读入尺寸（废话） 
	int cnt=0;//涂色格子数 
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			cin>>map[i][j];//读图 
			if (map[i][j]=='#') ++cnt;//统计涂色格子数 
		}
	if (cnt<3) {cout<<"-1\n";return 0;}//本题坑点：个数<=2，要输出-1的！（看到这里感到意外的，说明您没有仔细阅读本题解，请翻到代码上方） 
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(map[i][j]=='#')//枚举 
				if (check(i,j)) {cout<<"1\n";return 0;}//如果成功，立刻输出-1 
	cout<<"2\n";//没有成功过，输出 2
	return 0;
}
```
代码在此，切勿copy~

### 附录（虽然对于您们这些巨佬可能没什么用）：

dfs模板：

```
int dfs(int num)
{
    if(满足输出条件)
    {
        输出解或记录解；
    }
    else
    {
        for(int w=1;w<=尝试方法数;w++)
            if(满足进一步搜索条件)
            {
                为进一步搜索所需要的状态打上标记;
                dfs(t+1);
                恢复到打标记前的状态;//也就是说的{回溯一步}
            }
    }
}
```
ps:转载自@ybb756032937巨佬的P1605题解，如有不当之处请联系我删除


~~呼，终于看完了~~

~~呼，终于写完了~~

再次含泪声明，这是本蒟蒻第一次写题解，如有不当或可改进之处，请在此（或私信我）之处，谢谢大家的时间，再见！

---

## 作者：AC_love (赞：1)

如果把本题的数据开到 $2000 \times 2000$，很多暴力的题解就不那么好通过了，这时候应该怎么办呢？

首先不难发现：当点数大于等于 $3$ 时，答案最大为 $2$，最小为 $1$，因此我们只要考虑答案什么时候为 $2$，什么时候为 $1$ 即可。

考虑答案为 $1$ 时的状况：切掉某个点后，整个连通块被分成了两块。

不难发现，此时这个点就是图的点双连通分量。

因此我们找一下图上有没有点双，如果有那么答案为 $1$，如果没有那么答案为 $2$。

Tarjan 求点双，复杂度为 $O(nm)$，可以轻易通过大数据，你值得拥有。

[代码实现](https://codeforces.com/contest/193/submission/247735962)

---

## 作者：cyz_czy (赞：1)

# CF193题解

>我是 cyz,这期带你看题解

## 题目分析

首先我们需要知道的是，我们需要两个数组，一个是记录原地图的 $l_{i,j}$，一个是用来标记深搜的时候走过的路线，同时用来判断有没有联通，避免重复走同一个格子的 $p_{i,j}$，本人建议都用`bool`数组，毕竟都只有两种状态。

然后我们需要深搜进行判断更改后的地图有没有联通，也就是需要判断两次，第一次将所有的在一起的染色格子 $p_{i,j}$ 从 `false` 换成 `true`，再进行枚举，若还有染色格子 $l_{x,y}$ 且 $p_{x,y}$ 为 `false`，那么在这种情况下是没有联通的。

注意：答案只有 $3$ 种：$-1$，$1$ 和 $2$，只要染色格子数小于 $3$ 个，那么直接输出 $-1$；再进行枚举，将每一个染色格子 $p_{x,y}$ 都换成 `true` 后进行判断，若没有联通则输出 $1$，否则输出 $2$。

## Code:

```cpp
#include <iostream>
#include <cstring>  //我们需要清空p数组 

const int N=5e2+1e1;  //养成好习惯 

bool l[N][N];
bool p[N][N];

const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};  //方向标 

int n,m;
int c;  //记录染色格子数 

void input(){
	scanf("%d%d",&n,&m);
	
	char k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			
			std::cin>>k;  //字符输入最好用cin
			if(k=='#')
				l[i][j]=true,c++;
		}
	
	return ;  //养成好习惯 
}

void dfs(int x,int y){
	p[x][y]=true;  //换成非染色格子 
	
	for(int i=0;i<4;i++){
		
		int tx=x+dx[i];
		int ty=y+dy[i];
		if(tx<1||ty>m||tx>n||ty<1)
			continue;  //越界停止 
		if(l[tx][ty]&&!p[tx][ty])  //两个数组全是染色格子 
			dfs(tx,ty);  //继续 
	}
	
	return ;  //养成好习惯 
}

bool pd(int x,int y){
	memset(p,false,sizeof(p));  //别忘记清空数组 
	
	bool a=false;  //进行两次搜索的工具 
	p[x][y]=true;  //换成非染色格子 
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(l[i][j]&&!p[i][j]){  //如果是染色格子 
				if(a)
					return true;  //第二次，则没有联通 
				else
					a=true;  //第一次 
				dfs(i,j);  //将该格子与之相连的染色格子全部换成非染色格子 
			}
	
	return false;
}

int main(){
	input();
	
	if(c<3){  //如果小于3直接输出 
		printf("-1");
		return 0;
	}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)	
			if(l[i][j])  //有染色格子就进行判断 
				if(pd(i,j)){  //没有关联 
					printf("1");
					return 0;
				}
	
	printf("2");
	
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/110446286)

>我是 cyz,下期带你看题解

---

## 作者：幻想繁星 (赞：1)

我们考察图中最右边的方块中最下面的 # 方格，设为 $x$。则 $x$ 下方和右方都为空。设图中 # 个数为 $k$。

若 $k>3$，则除了 $x$ 还有其他 # 方格。这时我们只要把 $x$ 上方的 #（如果有的话）、$x$ 左方的 #（如果有的话）删去，就能使图不连通。因此必有解答案最多为 $2$；当 $k=3$ 时，答案为 $1$；当 $k<3$ 时，答案为 $-1$。

我们可以发现，无论什么图，答案都是三种情况： $-1,1,2$。

所以我们分类讨论：

1. 答案为 $-1$：就是 # 小于 $3$ 个的时候。

1. 答案为 $1$：我们删去每一个 #，再进行 dfs，判断是否为联通图。

1. 答案为 $2$：就是其他的情况。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[100],b[100];
int n,m,s;
const int t[4][2]={0,1,1,0,0,-1,-1,0};//预处理方向 
void dfs(int x,int y)
{
	if(b[x][y]!='#'||x<1||y<1||x>n||y>m) return;//dfs边界 
	b[x][y]='.';
	for(int i=0;i<4;i++) dfs(x+t[i][0],y+t[i][1]);
}//dfs
bool ch(int x,int y)
{
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) b[i][j]=a[i][j];
	b[x][y]='.';
	int s=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(b[i][j]=='#')
	{
		s++;
		dfs(i,j);//深搜dfs 
	}
	return s>1;
}//枚举
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]=='#') s++;//统计 # 
	if(s<3)//第一种 
	{
		puts("-1");
		return 0;
	}
	int ans=2;//预设第三种
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]=='#'&&ch(i,j)) ans=1;//改为第二种
	cout<<ans;
	return 0;
}
```


---

## 作者：baiABC (赞：1)

我们考察图中最右边的方块中最下面的 ``#`` 方格，设为 $x$。则 $x$ 下方和右方都为空。设图中 ``#`` 个数为 $k$。

若 $k>3$，则除了 $x$、$x$ 上方的 ``#``（如果有的话）（设为 $u$）、$x$ 左方的 ``#``（如果有的话）（设为 $l$），还有其他 ``#`` 方格。这时我们只要把 $u$、$l$ 删去，就能使图不连通。因此必有解答案最多为 $2$。

当 $k=3$ 时，答案为 $1$；当 $k<3$ 时，答案为 $-1$。

判断有无解后，怎么知道答案是 $1$ 还是 $2$ 呢？只要暴力枚举每个 ``#`` 方块，把它删除，判断原图是否连通即可。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, fx[] = {-1,0,1,0}, fy[] = {0,-1,0,1};
char s[50][51];
bool vis[50][50];
int main()
{
   scanf("%d%d", &n, &m);
   for(int i = 0; i < n; ++i)
      scanf("%s", s[i]);
   int cnt = 0, a[2][2];
   for(int i = 0; i < n; ++i)
      for(int j = 0; j < m; ++j)
         if(s[i][j] == '#')
         {
            if(cnt <= 1) a[cnt][0] = i, a[cnt][1] = j;
            ++cnt;
         }
   if(cnt < 3) {puts("-1"); return 0;}
   for(int i = 0; i < n; ++i)
      for(int j = 0; j < m; ++j)
         if(s[i][j] == '#')
         {
            s[i][j] = '.';
            memset(vis[0], false, sizeof vis);
            queue <pair <int, int> > q;
            if(a[0][0]==i&&a[0][1]==j) q.push(make_pair(a[1][0],a[1][1]));
            else q.push(make_pair(a[0][0],a[0][1]));
            vis[i][j] = true;
            int tot = 1;// bfs
            while(!q.empty())
            {
               int x = q.front().first, y = q.front().second;
               q.pop();
               for(int k = 0; k < 4; ++k)
               {
                  int tx = x+fx[k], ty = y+fy[k];
                  if(tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
                  if(s[tx][ty] == '#' && !vis[tx][ty])
                  {
                     vis[tx][ty] = true;
                     ++tot;
                     q.push(make_pair(tx,ty));
                  }
               }
            }
            if(tot < cnt) {puts("1"); return 0;}
            s[i][j] = '#';
         }
   puts("2");
   return 0;
}
```

---

## 作者：世末OIer (赞：1)

题目大意：

有一张图，让你用最小的次数使它不连通。

题解：

我们很容易可以证明最多切掉两个就可以使得它不连通了。


```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<string>
#include<set>
#include<map>
#include<ctime>
#include<cstring>
#include<cassert>
#include<bitset>
#include<sstream>
#include<queue>

using namespace std;

typedef long long ll;
typedef long double ld;

char a[55][55];
int is[55][55];
int n,m;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};

inline void work(int x,int y)              //dfs
{
	if(is[x][y]==1) return;
	if(a[x][y]!='#') return;
	is[x][y]=1;
	int i;
	for(i=0;i<4;i++)
		work(x+dx[i],y+dy[i]);
}

inline bool check(int x,int y)            //dfs判断
{
	a[x][y]='.';
	int kk=0;
	memset(is,0,sizeof(is));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		if(a[i][j]=='#' && (is[i][j]==0))
		{
			kk++;
			work(i,j);
		}
	}
	a[x][y]='#';
	return kk>1;
}

int main()
{
	cin>>n>>m;
	int kk=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='#') kk++;
		}
	}
	if(kk<3)
	{
		cout<<-1<<endl;
		return 0;
	}
	int ans=2;
	for(int i=0;i<=n;i++)
	{
		for(int j=1;j<=m;j++) if(a[i][j]=='#')
		{
			if(check(i,j)) ans=1;             //尝试切掉哪一个
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：qusia_MC (赞：0)

## 题意
求能不能把**至少一个** `#` 把所有的 `#` 变成一个不连通的呢？输出最少的个数否则输出 `-1`。

## 思路

首先呢，`#` 的个数少于 $3$ 个肯定是不行，因为 $0,1$ 个你没法删，没有 `#` 就谈不上联通了。$2$ 个的话你删去一个剩下一个肯定联通，删去两个是一样的。

---

我敲了好几组数据（暴力）结果发现输出结果大部分都是 $2$。剩下的全部都是 $1$。

那么为什么呢？

学围棋的肯定都知道角有特殊性吧，没学过也不要紧，接着往下看：

我们可以关注一下边角的一些 `#`。

就比方说我有这么个矩阵吧：

```
####
####
####
####
```

那么我很容易发现四个角上的只需要删去相邻的两个就行，必定不连通。

就是这样：

```
#.##
.###
####
####
```

那么有人会问了：如果角不是 `#` 呢？

那也好办，既然这个矩阵不能是圆形的，那么它一定会有角，我们只需要找到角上的那个然后删掉两个相邻的就行了。

但是当你信心满满输出 $2$ 时肯定不对。不信你测测这个：

```
###
#.#
```
一眼输出 $1$ 啊！

所以思路就出来了：

---

既然范围很小 $\le 50$，那么我直接 $O((nm)^2)$ 不就行了？？

我们首先判断能不能只删除 $1$ 个能不能成功，能就输出，不能就输出 $2$。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
int vis[1010][1010], n, m, sum;
char a[1010][1010];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int ok (int x, int y)
{
	memset (vis, 0, sizeof (vis));
	int cnt = sum;
	a[x][y] = '.';
	queue <pair <int, int> > q;
	for (int i = 1; i <= n; i++)
	{
		bool f = 0;
		for (int j = 1; j <= m; j ++)
		{
			if (a[i][j] == '#' && (i != x || j != y))
			{
				q.push({i, j});
			//	cout << i << " " << j << endl;
				vis[i][j] = 1;
				f = 1;
				break;
			}//随意找一个开始“洪水填充”
		}
		if (f) break;
	}
	cnt -= 2;
	while (q.size())
	{
		auto t = q.front ();
		q.pop ();
		for (int k = 0; k <= 3; k ++)
		{
			int i = t.first + dx[k], j = t.second + dy[k];
			if (i < 1 || j < 1 || i > n || j > m || a[i][j] != '#' || vis[i][j]) continue;
			q.push({i, j});
			vis[i][j] = 1;
			cnt --;
		}
	}
	a[x][y] = '#';//回溯
//	cout << cnt << endl;
	return cnt > 0;
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
		{
			cin >> a[i][j];
			if (a[i][j] == '#')sum ++;
		}
	if (sum <= 2)
	{
		cout << -1;
		return 0;
	}
	for (int i = 1; i <= n; i ++)
	{
		for (int j = 1; j <= m; j ++)
		{
			if (ok(i, j) && a[i][j] == '#')//可以
			{
				cout << 1;
				return 0;
			}
		}
	}
	cout << 2;
	return 0;
}
```

---

## 作者：_szs9601 (赞：0)

#### 题意
给出一个图，为一个 `#` 号的连通块，求至少去掉几个 `#` 才能使得图不连通。
#### 思路
通过枚举我们可以发现，无论什么图，答案都是三种情况： -1,1,2。

所以我们分类讨论：

第一种：答案为 -1。显然，这种情况就是 `#` 小于 3 个的时候。

第二种：答案为 1。我们枚举每一个 `#`，假设将它删去，再进行深搜，判断是否为联通图。

第三种：答案为 2。就是不满足第一种也不满足第二种的情况。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100][100],b[100][100];
int n,m,i,j,s;
const int tag[4][2]={0,1,1,0,0,-1,-1,0};
void sc(int x,int y){
	if(b[x][y]!='#'||x<1||y<1||x>n||y>m) return;
	b[x][y]='.';
	for(int i=0;i<4;i++) sc(x+tag[i][0],y+tag[i][1]);
}//深搜
bool check(int x,int y){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) b[i][j]=a[i][j];
	b[x][y]='.';
	int s=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(b[i][j]=='#'){s++;sc(i,j);}
	return s>1;
}//枚举
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%s",a[i]+1);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i][j]=='#') s++;
	if(s<3){printf("-1\n");return 0;}//第一种
	int ans=2;//第三种
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i][j]=='#'&&check(i,j)) ans=1;//第二种
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：qjxqjx (赞：0)

## 题目大意：
现在给你一个图，为一个 # 号的****连通块****，求至少去掉几个 # 才能使得图****不连通****。

## 题目思路：
看起来很难，但是还是可以找找规律。

枚举几次可以发现，无论是什么图的答案都是三种情况： -1,1,2。

那么会分成三种情况：

第一种：去掉最多的情况，把图形的角的方格两边得连通块去掉，就是用 2 个。

第二钟：那么 -1 的情况就是 # 小于 3 个的时候。

第三种：枚举所有 # 号位置，如果去掉该位置连通块是 2 个以上就直接输出 1，否则输出 2 即可。

综上，代码如下：

## 代码：
```c
#include<bits/stdc++.h>
//#include<cstdio>
using namespace std;
#define ll long long
int dirx[4]={0,0,-1,1};
int diry[4]={1,-1,0,0};//这个建议对齐写
char s[55][55];
int vis[55][55];
int n,m,ans;
void dfs(int x,int y){
    ans++;
    int xx,yy,i;
    for(i=0;i<4;i++){
        xx=dirx[i]+x;
        yy=diry[i]+y;
        if(xx>=0&&yy>=0&&xx<n&&yy<m&&!vis[xx][yy]&&s[xx][yy]=='#'){
            vis[xx][yy]=1;
            dfs(xx,yy);
        }
    }
}
int main(){
    int i,j,num=0;
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++){
        scanf("%s",s[i]);
        for(j=0;j<m;j++){
            if(s[i][j]=='#'){
                num++;
            }
        }
    }
    if(num<3){
        printf("-1\n");
        return 0;
    }//这是第二钟情况
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(s[i][j]=='#'){
                memset(vis,0,sizeof(vis));
                vis[i][j]=1;
                ans=0;
                for(int p=0;p<n;p++){
                    for(int q=0;q<m;q++){
                        if(s[p][q]=='#'&&!vis[p][q]){
                            vis[p][q]=1;
                            dfs(p,q);
                            goto loop;
                        }
                    }
                }
                loop:;
                if(ans!=num-1){
                    printf("1\n");
                    return 0;
                }//这是第一种情况
            }
        }
    }
    printf("2\n");//第三种，直接输出
    return 0;
}
```


---

## 作者：ahawzlc (赞：0)

思路：搜索

----

首先我们知道，最多只需要删两个点，即可满足要求。

我们所要做的就是看看能不能少删一个点。

那怎么判断呢？

就是先把这个点标为已访问过，然后另找一个涂了色的点开始搜索，如果能搜过一遍后，还有没有访问过的点，那原先这个点肯定就是所谓的 ~~solo 之王~~单一解答案了。

那么我们读入数据，同时标注哪些点已经涂过色，然后在每个已经涂过点的基础上求解，如果这个涂色点能够满足单一解，那就输出 1 ，否则就输出 2 。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define F first
#define S second
using namespace std;
const int N=55;
const int dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};
bool map[N][N],vis[N][N];
int n,m,num;
vector< pair<int,int> > v;
void dfs(int x,int y) {//搜索
	vis[x][y]=1;
	for(int i=1;i<=4;i++) {
		int xx=x+dx[i],yy=y+dy[i];
		if(!vis[xx][yy]&&map[xx][yy]) dfs(xx,yy);
	}
}
bool solve(int x,int y) {//求单一解
	bool opt=0;
	memset(vis,0,sizeof(vis));
	vis[x][y]=1;
	for(int i=0;i<v.size();i++) {
		if(!vis[v[i].F][v[i].S]) {
			if(opt) return 1;
			opt=1;
			dfs(v[i].F,v[i].S);
		}
	}
	return 0;
}
int main() {
	char ch;
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin>>ch;
			if(ch-'.') {
				map[i][j]=1;
				num++;
				v.push_back(make_pair(i,j));
			}
		}
	}
	if(num<=2) puts("-1");//涂色点总数小于2特判无解
	else {
		for(int i=0;i<v.size();i++) {
			if(solve(v[i].F,v[i].S)) {//求单一解
				puts("1");
				return 0;
			}
		}
		puts("2");
		return 0;
	}
}
```

---

