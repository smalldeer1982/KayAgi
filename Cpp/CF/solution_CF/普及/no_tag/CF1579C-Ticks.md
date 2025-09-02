# Ticks

## 题目描述

Casimir has a rectangular piece of paper with a checkered field of size $ n \times m $ . Initially, all cells of the field are white.

Let us denote the cell with coordinates $ i $ vertically and $ j $ horizontally by $ (i, j) $ . The upper left cell will be referred to as $ (1, 1) $ and the lower right cell as $ (n, m) $ .

Casimir draws ticks of different sizes on the field. A tick of size $ d $ ( $ d > 0 $ ) with its center in cell $ (i, j) $ is drawn as follows:

1. First, the center cell $ (i, j) $ is painted black.
2. Then exactly $ d $ cells on the top-left diagonally to the center and exactly $ d $ cells on the top-right diagonally to the center are also painted black.
3. That is all the cells with coordinates $ (i - h, j \pm h) $ for all $ h $ between $ 0 $ and $ d $ are painted. In particular, a tick consists of $ 2d + 1 $ black cells.

An already painted cell will remain black if painted again. Below you can find an example of the $ 4 \times 9 $ box, with two ticks of sizes $ 2 $ and $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1579C/b2b898f1569af103ffaf93cfc9bbbe7d51da03c3.png)You are given a description of a checkered field of size $ n \times m $ . Casimir claims that this field came about after he drew some (possibly $ 0 $ ) ticks on it. The ticks could be of different sizes, but the size of each tick is at least $ k $ (that is, $ d \ge k $ for all the ticks).

Determine whether this field can indeed be obtained by drawing some (possibly none) ticks of sizes $ d \ge k $ or not.

## 说明/提示

The first sample test case consists of two asterisks neither of which can be independent ticks since ticks of size $ 0 $ don't exist.

The second sample test case is already described in the statement (check the picture in the statement). This field can be obtained by drawing ticks of sizes $ 2 $ and $ 3 $ , as shown in the figure.

The field in the third sample test case corresponds to three ticks of size $ 1 $ . Their center cells are marked with $ \color{blue}{\text{blue}} $ , $ \color{red}{\text{red}} $ and $ \color{green}{\text{green}} $ colors:

\*.\*.\* $ \color{blue}{\textbf{*}} $ \*\*. $ \color{green}{\textbf{*}}\color{red}{\textbf{*}} $ .....The field in the fourth sample test case could have been obtained by drawing two ticks of sizes $ 1 $ and $ 2 $ . Their vertices are marked below with $ \color{blue}{\text{blue}} $ and $ \color{red}{\text{red}} $ colors respectively:

.....\*...\*.\*.\*... $ \color{red}{\textbf{*}} $ .\*... $ \color{blue}{\textbf{*}} $ .The field in the fifth sample test case can not be obtained because $ k = 2 $ , and the last asterisk in the fourth row from the top with coordinates $ (4, 5) $ can only be a part of a tick of size $ 1 $ .

The field in the sixth sample test case can not be obtained because the top left asterisk $ (1, 1) $ can't be an independent tick, since the sizes of the ticks must be positive, and cannot be part of a tick with the center cell in the last row, since it is separated from it by a gap (a point, '.') in $ (2, 2) $ .

In the seventh sample test case, similarly, the field can not be obtained by the described process because the asterisks with coordinates $ (1, 2) $ (second cell in the first row), $ (3, 1) $ and $ (3, 3) $ (leftmost and rightmost cells in the bottom) can not be parts of any ticks.

## 样例 #1

### 输入

```
8
2 3 1
*.*
...
4 9 2
*.*.*...*
.*.*...*.
..*.*.*..
.....*...
4 4 1
*.*.
****
.**.
....
5 5 1
.....
*...*
.*.*.
..*.*
...*.
5 5 2
.....
*...*
.*.*.
..*.*
...*.
4 7 1
*.....*
.....*.
..*.*..
...*...
3 3 1
***
***
***
3 5 1
*...*
.***.
.**..```

### 输出

```
NO
YES
YES
YES
NO
NO
NO
NO```

# 题解

## 作者：EternalHeart1314 (赞：5)

### [题目传送门](https://www.luogu.com.cn/problem/CF1579C)

# 思路

此题 $n$ 和 $m$ 都很小，考虑枚举每个位置，然后尽可能地往上找，如果向上的次数大于等于 $k$，就说明可以被染色到，打上标记。最后有黑色格子没有被打上标记，就是 `NO`，否则就是 `YES`。

# Code
```
#include<bits/stdc++.h>
using namespace std;

const int N(17), M(20);
int t, n, m, k, x, y, z, cnt;
string s[N];
bool a[N][M], flag;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> n >> m >> k;
		memset(a, 0, sizeof a);
		flag = true;
		for(int i(1); i <= n; ++ i) {
			cin >> s[i];
			s[i] = ' ' + s[i];
		}
		for(int i(1); i <= n; ++ i) {
			for(int j(1); j <= m; ++ j) {
				if(s[i][j] == '*') {
					cnt = 0, x = i, y = z = j;
					while(-- x && -- y && ++ z <= m && s[x][y] == '*' && s[x][z] == '*') {
						++ cnt;
					}
					if(cnt >= k) {
						a[i][j] = true;
						x = i, y = z = j;
						while(-- x && -- y && ++ z <= m && s[x][y] == '*' && s[x][z] == '*') {
							a[x][y] = a[x][z] = true;
						}
					}
				}
			}
		}
		for(int i(1); i <= n && flag; ++ i) {
			for(int j(1); j <= m && flag; ++ j) {
				flag = (s[i][j] != '*') || a[i][j];
			}
		}
		cout << (flag ? "YES" : "NO") << '\n';
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：M_CI (赞：3)

### 思路

首先看到数据范围，观察到 `n`、`m` 都不大，所以考虑模拟染色过程。

遍历每个点，然后枚举以该点为左上角的勾形的大小，如果可行，则将这块勾形区域标记。

最后遍历一遍原图，如果有没标记过的需染色点，则输出 `NO`，否则输出 `YES`。

### 代码

纯暴力，就按照思路中的流程来，所以不加注释。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,m,k;
char c[30][30],f[30][30];

int main () {
	cin>> t;
	while (t--) {
		cin>> n>> m>> k;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) {
				cin>> c[i][j];
				f[i][j]='.';
			}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++) {
				for (int u=k;i+u<=n&&j+2*u<=m;u++) {
					bool fl=1;
					int x=i,y=j;
					for (int v=1;v<=u+1;v++) {
						if (c[x][y]!='*') {
							fl=0;
							break;
						}
						x++;
						y++;
					}
					x-=2;
					for (int v=1;v<=u;v++) {
						if (c[x][y]!='*') {
							fl=0;
							break;
						}
						x--;
						y++;
					}
					if (fl) {
						x=i; 
						y=j;
						for (int v=1;v<=u+1;v++) {
							f[x][y]='*';
							x++;
							y++;
						}
						x-=2;
						for (int v=1;v<=u;v++) {
							f[x][y]='*';
							x--;
							y++;
						}
					}
				}
			}
		bool fl=1;
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=m;j++)
				if (c[i][j]!=f[i][j]) {
					fl=0;
					break;
				}
			if (!fl) break;
		}
		puts (fl? "YES": "NO");
	}
	return 0;
}
```

---

## 作者：漠寒 (赞：3)

## 分析

### 题意

给出 $n$，$m$，$k$,给出一个大小为 $nm$ 的矩形。矩形仅包含 " \* " 和 " . "。需要你用任意个仅包含 " \* " 的开口向上 v 形结构，两边斜率为1，且边长严格大于 $k$（包含交点），来包含所有矩形的 " \* "。

### 做法

用 $vis(i,j)$ 表示第 $i$ 第 $j$ 列有没有被涵盖。

枚举每一个点作为 "V" 的交点，尽可能地延伸，即尽量地去找更长的满足条件的边，如果长度小于 $k$ 就找到不为 " * " 的点，就不更新，否则就一直往上找，不断地更新 $vis$ 数组。最后判断所有需涵盖是否全部涵盖就行了。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
inline void read(int &res){
	res=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int mp[25][25];
int vis[25][25];
int T;
int n,m,k;
char c[25];
inline int check(int x,int y){//是否满足基础条件时就会越位 
	if(x-k+1<=0||y-k+1<=0||y+k-1>m)return 0;
	return 1;
}
inline int dcheck(int x,int y){//检查是否能至少延伸出k+1的长度 
	for(int i=x,j=y,l=y,t=1;t<=k;i--,j--,l++,t++){
		if(!mp[i][j]||!mp[i][l])return 0;
	}
	return 1;
}
signed main()
{
	read(T);
	while(T--){
		memset(vis,0,sizeof(vis));
		read(n);read(m);read(k);
		k++;
		for(int i=1;i<=n;i++){
			scanf("%s",c+1);
			for(int j=1;j<=m;j++){
				if(c[j]=='*')mp[i][j]=1;
				else mp[i][j]=0;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(!check(i,j))continue;
				if(!dcheck(i,j))continue;
				int x=i,y=j,l=j,t=1;
				for(;t<=k;x--,y--,l++,t++){//先处理k+1 
					vis[x][y]=vis[x][l]=1;
				}
				for(;x>=1;x--,y--,l++,t++){//再尽可能改 
					if(!mp[x][y]||!mp[x][l])break;
					vis[x][y]=vis[x][l]=1;
				}
			}
		}
		int bo=0;
		for(int i=1;i<=n;i++){
			if(bo)break;
			for(int j=1;j<=m;j++){
				if(bo)break;
				if(mp[i][j]&&(!vis[i][j])){//需要改却未改 
					bo=1;
				}
			}
		}
		if(bo)puts("NO");
		else puts("YES");
	}
	return 0;
}

```


---

## 作者：Super_Builder (赞：2)

## 思路
依次枚举每一个黑色点，然后一枚举到的点为勾最靠下的那个点，如图种红色圈的部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/loayct9u.png)

然后搜索左上角和右上角，判断是否合法，即连续格子长度符合要求。

因为他的连续格子长度不一定是 $d$，而长度越长是对其他勾没有影响，而覆盖的越多一定不或更差，所以我们就想要这个连续格子长度尽量长。而两边长度需要对称，所以取最小的一边。这个操作可以在判断时求。

如果判断合法，则把这个勾能够染成黑色的格子标记。

最后看一下是不是所有黑色格子都被标记过就好了。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,d,dx[4]={-1,-1,1,1},dy[4]={-1,1,-1,1},vis[20][20],vis2[20][20],minn=1e9;
char c[20][20];
bool dfs(int x,int y,int f,int t){//左上角或右上角方向染色格子长度是否大于等于d
	x+=dx[f];
	y+=dy[f];
	if(vis[x][y]==0){
		if(t<d)return false;
		minn=min(minn,t);
		return true;
	}
	if(x<1||y<1||y>m)return false; 
	dfs(x,y,f,t+1);
}
void dfs2(int x,int y,int f,int t){//标记勾能染到的格子
	if(t>minn)return;
	vis2[x][y]=1;
	x+=dx[f];
	y+=dy[f];
	dfs2(x,y,f,t+1);
}
int main(){
	int T;
	cin>>T;
	while(T--){
		memset(vis,0,sizeof vis);
		memset(vis2,0,sizeof vis2);
		cin>>n>>m>>d;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>c[i][j];
				if(c[i][j]=='*')vis[i][j]=1;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(vis[i][j]){
					minn=1e9;
					if(dfs(i,j,0,0)&&dfs(i,j,1,0)){//判断
						vis2[i][j]=1;//标记
						dfs2(i,j,0,0);
						dfs2(i,j,1,0);
					}
				}	
			}
		}
		bool ok=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(c[i][j]=='*'){//所有黑色格子是否被标记
					if(!vis2[i][j])ok=0;
				}
			}
		} 
		if(ok)cout<<"YES";
		else cout<<"NO";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：_GW_ (赞：1)

## 思路
看到题的第一眼：！什么鬼！

看到数据范围：！暴力啊！

具体方案：

首先，我们枚举对勾图案的起点。

然后，如果从此点出发，对勾图案的大小能达到 $k$，则能染多少格就染多少格，并用数组记录。

最后，判断那个数组与原数组是否完全相同，即可 AC。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=25,M=25;
int a[N][N],vis[N][N],T,num,val,n,m,k;
string s;
bool get(int x,int y)//传入坐标，如果从此点出发，延伸出去k格（k是给定的）就会越界，返回0；反之，返回1. 
{
	if(x-k+1<=0||y-k+1<=0||y+k-1>m) return 0;return 1; 
}
bool check(int x,int y) //若要从此点延伸k格，是否有在给定的图中有。
{
	int i=x,j=y,l=y;
	for(int now=1;now<=k;now++,i--,j--,l++) if(!a[i][j]||!a[i][l]) return 0;
	return 1;
} 
int main()
{
	cin>>T;
	while(T--)
	{
		memset(vis,0,sizeof vis);memset(a,0,sizeof a);
		cin>>n>>m>>k;
		k++;
		for(int i=1;i<=n;i++)
		{
			cin>>s;s=" "+s;
			for(int j=1;j<=m;j++)
			{
				a[i][j]=(s[j]=='*'?1:0);//输入。 
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(!get(i,j)||!check(i,j)) continue;//不符条件。 
				int x=i,y=j,l=j,now=1;
				for(;now<=k;x--,y--,l++,now++) vis[x][y]=vis[x][l]=1;
				for(;x>=1;x--,y--,l++,now++)
				{
					if(!a[x][y]||!a[x][l]) break;vis[x][y]=vis[x][l]=1;//从(i,j)出发，能走到的点全部标记上。 
				}
			}
		}
		bool flag=1;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]&&!vis[i][j]) flag=0;
		if(flag) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：SSL_wj (赞：1)

## 题意
给你一种图形，这种图形是由一个中心点向左上和右上各延伸 $k$ 个格子组成的，现在给你一个网格图，问能否用这个图形叠出网格图。**不能越界。**

图形示例：
```
.......
.*...*.
..*.*..
...*...
.......
```
该图即为一个合法图形，且其 $k$ 为 2。
## 做法
枚举每个点，如果该点可以作为中心点（不越界，大小为 $k$）就模拟覆盖这个图形，最后判断有没有完全覆盖即可。
## 正确性证明
首先，这种方法显然是不会覆盖到不应被覆盖的点的。然后，因为一个图形加入后不会使一个原本被覆盖过的点被取消覆盖，因此加入一个图形总是有利于确认这个网格图是可以拼成的。

时间复杂度为 $O(nmk)$。

## code
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int T,n,m,k,x;
char c;bool vis[15][25],a[15][25];
inline int check1(register int x,register int y){register int s=-1;while(x&&y&&a[x][y])--x,--y,++s;return s;}
inline int check2(register int x,register int y){register int s=-1;while(x&&y<=m&&a[x][y])--x,++y,++s;return s;}
inline void color1(register int x,register int y,register int z){vis[x][y]=1;while(z--)vis[--x][--y]=1;}
inline void color2(register int x,register int y,register int z){while(z--)vis[--x][++y]=1;}
inline void test()
{
	cin>>n>>m>>k,memset(vis,0,sizeof(vis));
	for(register int i=1;i<=n;++i)for(register int j=1;j<=m;++j)cin>>c,a[i][j]=(c=='*');
	for(register int i=1;i<=n;++i)for(register int j=1;j<=m;++j)if((x=min(check1(i,j),check2(i,j)))>=k)color1(i,j,x),color2(i,j,x);
	for(register int i=1;i<=n;++i)for(register int j=1;j<=m;++j)if(a[i][j]&&!vis[i][j]){printf("NO\n");return;}
	printf("YES\n");
}
int main()
{
	ios::sync_with_stdio(0),cin>>T;
	while(T--)test();
	return 0;
}
```

---

## 作者：Zhangikun (赞：0)

## 思路
本人下文所说的释放涂色意思是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/b7w92rhr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

大小为 $2$ 的涂色：

![](https://cdn.luogu.com.cn/upload/image_hosting/6ab6v0t4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们做这题需要写四个函数：
1. `ok` 判断一个坐标可不可以释放涂色。
2. `ok2` 判断一个坐标释放涂色的每个点是否在要求的数组里面都是黑色，换句话说就是涂了会不会错。
3. `getans` 让一个坐标释放涂色。
4. `ff` 判断涂完色的数组和要求的数组是否相符。

只要我们把每个可以涂的点都涂了，那么肯定不会出现任何一个点涂成了黑色，但目标是白色的；但是有可能一个点目标是黑色的，但是整个数组涂完后是白色，这种情况就无能为力了。

另外，由于大小不固定，所以——
### 方法
对于每个点，从 $k$ 到 $m$ 枚举一下涂色的大。至于为什么是 $k$ 到 $m$，是因为一个点要放大小为 $d$ 的涂色，如果 $d$ 都大于了 $m$，那么必然会出界。如果你足够自信，你可以优化一下，比如循环条件设为 $j+k+k\le m$。如果 $ok(i,j)=1$ 并且 $ok2(i,j)=1$ 就说明可以涂。枚举完用 $ff()$ 判一下即可。
## 代码：
```cpp
#include<bits/stdc++.h>
#define kk k+k
#define int long long
using namespace std;
const short cxk=25;
bool a[cxk][cxk],b[cxk][cxk];
int n,m,k,_k;
bool ok(int x,int y)
{
  return x+k<=n&&y+kk<=m;
}
bool ok2(int x,int y)
{
  for(int j=y,i=x;j<=y+kk;j++)
  {
    if(a[i][j]==0)
    {
      return 0;
    }
    if(j>=y+k)//确保是'v'字形，i要特判
    {
      i--;
    }
    else
    {
      i++;
    }
  }
  return 1;
}
void getans(int x,int y)
{
  for(int j=y,i=x;j<=y+kk;j++)
  {
    b[i][j]=1;
    if(j>=y+k)
    {
      i--;
    }
    else
    {
      i++;
    }
  }
}
bool ff()
{
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      //cout<<b[i][j];
      if(a[i][j]!=b[i][j])
      {
        return 0;
      }
    }
    //cout<<"\n";
  }
  return 1;
}
void help()
{
  memset(a,0,sizeof(a));
  memset(b,0,sizeof(b));
  cin>>n>>m>>_k;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      char c;
      cin>>c;
      a[i][j]=(c=='.'?0:1);
    }
  }
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      for(k=_k;k<=m;k++)
      {
        if(a[i][j]&&ok(i,j)&&ok2(i,j))
        {
          getans(i,j);
        }
      }
      
    }
  }
  cout<<(ff()?"YES\n":"NO\n");
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  for(cin>>t;t--;)
  {
    help();
  }
}
```

---

## 作者：wangyibo201026 (赞：0)

## 思路

我们看到一个没有标记过的 ```*``` 时，就把他左上方和右上方延伸，直到不能延伸为止。再全部标记，最后看所有的 ```*``` 都标记过没有就可以了。

请注意 $k$ 的限制。

## 代码

代码：

```
#include<bits/stdc++.h>

using namespace std;

int t;
bool vis[25][25];    //标记数组

void Solve(){
  cin >> t;
  while(t--){
    int n, m, d;
    char a[25][25];
    cin >> n >> m >> d;
    for(int i = 1; i <= n; i++){
      for(int j = 1; j <= m; j++){
        cin >> a[i][j];
        vis[i][j] = 0;    //标记清空
      }
    }
    for(int i = 1; i <= n; i++){
      for(int j = 1; j <= m; j++){
        if(a[i][j] == '*'){
          int i1 = i, j1 = j, sum1 = 0, sum2 = 0, i2 = i, j2 = j;
          while(i1 >= 1 && j1 >= 1){     /左上角延伸
            if(a[i1][j1] == '*'){
              sum1++;
            }
            else{
              break;
            }
            i1--;
            j1--;
          }
          while(i2 >= 1 && j2 <= m){   //右上角延伸
            if(a[i2][j2] == '*'){
              sum2++;
            }
            else{
              break;    //及时推出
            }
            i2--;
            j2++;
          }
          sum1--;
          sum2--;
          if(min(sum1, sum2) >= d){
            for(int l = j, k = i; l >= j - min(sum1, sum2), k >= i - min(sum1, sum2); l--, k--){     //标记左上角
              vis[k][l] = true;
            }
            for(int l = j, k = i; l <= j + min(sum1, sum2), k >= i - min(sum1, sum2); l++, k--){     //标记右上角
              vis[k][l] = true;
            }
          }
        }
      }
    }
    bool f = false;
    for(int i = 1; i <= n; i++){
      for(int j = 1; j <= m; j++){    //查找所有 *
        if(a[i][j] == '*' && !vis[i][j]){
          cout << "NO\n";
          f = true;
          break;
        }
      }
      if(f){
          break;
      }
    }
    if(!f){
      cout << "YES\n";
    }
  }
}

int main(){
  Solve();
  return 0;
}
```

---

## 作者：minVan (赞：0)

**解题思路**

枚举每个对勾图案最下面的顶点，向上枚举。令 $l$ 为向上的长度，如果 $i-l < 0$ 或 $j-l<0$ 或 $j+l\ge m$ 或 $c_{i-l,j-l}\neq *$ 或 $c_{i-l,j+l}\neq *$，则退出循环。

最后如果还有 `*` 没被标记过，则无法满足条件。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[20][20];
bool f[20][20];
int main() {
  int t;
  cin >> t;
  while(t--) {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        cin >> c[i][j];
        f[i][j] = 0;
      }
    }
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        if(c[i][j] == '*') {
          int l = 0;
          for(; l <= min(n, m); l++) {
            if(i - l < 0 || j - l < 0 || j + l >= m || c[i - l][j - l] != '*' || c[i - l][j + l] != '*') {
              break;
            }
          }
          l--;
          if(l < k) {
            continue;
          }
          for(int d = 0; d <= l; d++) {
            f[i - d][j - d] = f[i - d][j + d] = 1;
          }
        }
      }
    }
    bool flag = 0;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        if(c[i][j] == '*' && !f[i][j]) {
          flag = 1;
          break;
        }
      }
      if(flag) {
        break;
      }
    }
    if(!flag) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
```

---

