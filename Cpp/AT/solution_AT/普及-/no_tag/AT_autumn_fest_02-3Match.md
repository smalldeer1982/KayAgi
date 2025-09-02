# 3Match

## 题目描述

有 $H$ 行 $W$ 列的矩阵，每一个矩阵都有一个数字填充。我们需要找出**连续**的横着 $3$ 个及以上或竖着 $3$ 个及以上的，由**同一数字**构成的长方形，如图：

![](https://i.bmp.ovh/imgs/2021/05/f6ceeb02fde0a293.png)

但是，这有可能会连通。那么，这些连通的**只会**变成一个。如图：
![](https://i.bmp.ovh/imgs/2021/05/87dff1f17fcc326d.png)

需要求出长方形的个数（连通的只算一个）

## 说明/提示

$3 \le H, W \le 100$。

# 题解

## 作者：zt17 (赞：3)

[查看题目](https://www.luogu.com.cn/problem/AT319)

### 题意简介
 - 给你一个填满了数字的 $H$ 行 $M$ 列的矩阵，找出连续（**横着竖着皆可**）$3$ 个或以上的，由同一数字构成的长方形（这样的长方形以下简称为长方形），输出满足条件的长方形的个数。
 
 - 如有多个满足条件且均为同一数字的长方形连结在一起，仅算 $1$ 个满足条件的长方形。
 
### 题目分析
 这道题主要难点在于如何辨别出连结在一起的长方形。
 
 我们不妨思考一下，长方形连结在一起有什么特征？
 
 - 同一数字
 
 - 坐标相邻
 
 这不也是我们的普通长方形的判定标准吗？
 
 > 一切的特殊情况，都可以用简单情况的解决方法处理。
 
 我的思路是在开始的时候输入数字矩阵，并且将矩阵存入**全局**二维数组 ```a[][]```，并且设定**全局**变量 $cnt$ 和 $ans$。
 
 接着调用一个自定义函数 ```cp（int x,int y,int x1,int y1）```，这个 ``` cp()``` 的作用是先将 ```a[x][y]``` 值设为 $-1$ (这样能区别已经使用的数字)和将 ```cnt += 1```，然后比较 ```a[x][y]``` 的数字和它四周 (```a[x+1][y]```，```a[x-1][y]```，```a[x][y+1]```，```a[x][y-1]```) 中除了 ```a[x+x1][y+y1]``` 的其他三个数字是否相同。如果三个中 ```a[m][n]``` 等于 ```a[x][y]```，则继续运行 ```cp(m,n,x-m,y-m)```，否则返回。
 
 我们用这个函数做什么呢？我们在主程序里输入矩阵后，用for循环循环遍历 ```a[][]```，每次访问一个不等于 $-1$ 的数字，它的坐标是 ```a[x][y]```。这时我们写的函数就有用场了。先将 $cnt$ 的值设为 $0$ ，然后运行函数 ```cp(x,y,0,0)```，最后如果 $cnt \geq 3$，那么 $ans + 1$。运行完后继续查找矩阵中还有没有这样的数。
 
### 正解代码
 
```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt,ans;
int a[101][101];

void cp(int x,int y,int x1,int y1)
{
    a[x][y] = -1;
    cnt ++;
    for(int i=-1;i<=1;i+=2)
    {
		for(int j=-1;j<=1;j+=2)
		{
			if(i!=x1 || j!=y1)
			{
				if(a[x+i][y+j] == a[x][y])
				{
					cp(x+i,y+i,0-i,0-j);
				}
			}
		}
	}
}

int main()
{
    int H,W;
    cin >> H >> W;
    for(int i=1;i<=H;i++)
    {
        for(int j=1;j<=W;j++)
        {
            cin >> a[H][W];
        }
    }
    for(int i=1;i<=H;i++)
    {
        for(int j=1;j<=W;j++)
        {
            if(a[i][j] != -1)
            {
                cnt == 0;
                cp(i,j,0,0);
                if(cnt >= 3) ans++; 
            } 
        }
    }
    return 0;
}
```

---

## 作者：Strelitzia_ (赞：3)

## 题目大意

------------
给定一个包含若干数字的矩阵，要我们找出连续的横着 $3$ 个及以上或竖着 $3$ 个及以上的，由同一数字构成的长方形，输出数量。联通的长方形只算一个。

## 思路

------------
用一个 ```bool``` 数组记录每个点是不是在一个矩形内。那么我们直接扫一遍，对每个点直接枚举向左或向下的 $3$ 个数字，假如相同就置为 ```true```，否则跳过。

然后处理联通的情况。我们可以对 ```bool``` 数组中每一个 ```true``` 先计数 ```ans++```，然后跑一个 $\texttt{DFS}$，对于搜到的所有联通的点置为 ```false```。

这里存储时用 ```char``` 数组，可以直接输入。

代码：

```cpp
#include<bits/stdc++.h>
#define lxl long long
#define db double
#define N 114514
#define M 1919810

using namespace std;
const double lxy=-1;

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x*f;
}

void write(int x){
	if(!x) return ;
	write(x/10);
	putchar(x%10+'0');
}

char a[107][107];
bool f[107][107];
int ans=0;
int n,m;

void dfs(int x,int y,char c){
	if(!x||!y||x>n||y>m||!f[x][y]||a[x][y]!=c) return ;//判断边界
	f[x][y]=false;
	dfs(x+1,y,c);
	dfs(x-1,y,c);
	dfs(x,y+1,c);
	dfs(x,y-1,c);
}

int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
		 cin>>a[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j]){
				f[i][j]=true;
				f[i+1][j]=true;
				f[i+2][j]=true;
			}
			if(a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2]){
				f[i][j]=true;
				f[i][j+1]=true;
				f[i][j+2]=true;//直接枚举
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(f[i][j]){
				ans++;
				dfs(i,j,a[i][j]);//计数
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Nygglatho (赞：3)

我们可以把矩阵（设为 $st$）中的**所有**长方形都在 $tf$ 中标记上去。每一次搜 $i$ 与 $j$，只要搜到（即 $st_{i, j} = st_{i, j + 1} = st_{i, j + 2}$ 或 $st_{i, j} = st_{i + 1, j} = st_{i + 2, j}$），那么我们就把 $tf_{i, j}$，$tf_{i, j + 1}$，$tf_{i, j + 2}$ 或 $tf_{i, j}$，$tf_{i + 1, j}$，$tf_{i + 2, j}$ 都设置为真。

```cpp
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= m; j++) {
		if (st[i][j] == st[i][j + 1] && st[i][j] == st[i][j + 2]) {tf[i][j] = true; tf[i][j + 1] = true; tf[i][j + 2] = true;}
		if (st[i][j] == st[i + 1][j] && st[i][j] == st[i + 2][j]) {tf[i][j] = true; tf[i + 1][j] = true; tf[i + 2][j] = true;}
	}
}
```

接下来，考虑连通。由于每一个小长方形都是 $1$，所以我们直接搜索，只要搜到满足条件，都直接 DFS 跑一遍即可。注意一定要**同一个数字**！
```cpp
void DFS(int x, int y, char ch) {
	if (x == 0 || y == 0 || x > n || y > m || !tf[x][y] || st[x][y] != ch) return;//边界
	tf[x][y] = false;//只用考虑一个，其他的为避免重复全部为0。
	DFS(x, y - 1, ch);
	DFS(x, y + 1, ch);
	DFS(x - 1, y, ch);
	DFS(x + 1, y, ch);
}

//下面是搜索代码，注意不能把搜索放在后面，不然因为搜到x,y都会把它变为0，而当前的也会变成0。
int s = 0;
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= m; j++) {
		if (tf[i][j]) {
			s++;
			DFS(i, j, st[i][j]);
		}
	}
}
printf ("%d\n", s);
```

---

## 作者：Anaxagoras (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT319)

### 0x01 思路

输入后逐个点枚举，如果发现有三个数字一样的水平或垂直长方形（以下称三联通），就标记，然后再次逐个枚举，发现一个标记就深搜染色，并把计数器加一，最后输出计数器即可。

注意本题须以 `char` 的形式输入。

### 0x02 AC Code

```cpp
//by olkieler
#include<bits/stdc++.h>
#define int unsigned
#define inf LLONG_MAX
#define ios ios::sync_with_stdio(0);cin.tie(0);
#define retrun return
#define N 105
#define M 105
#define mod 114514
using namespace std;
int n,m;
bool f[N][M];
char a[N][M];//注意数据类型
inline void dfs(int x,int y,char num)
{
	if(x<1||y<1||x>n||y>m||a[x][y]!=num)//判断边界
	{
		return ;
	}
	f[x][y]=0;
	if(f[x+1][y])
	{
		dfs(x+1,y,num);
	}
	if(f[x-1][y])
	{
		dfs(x-1,y,num);
	}
	if(f[x][y+1])
	{
		dfs(x,y+1,num);
	}
	if(f[x][y-1])
	{
		dfs(x,y-1,num);
	}
}
signed main()
{
	ios;
	int ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]==a[i][j+1]&&a[i][j+1]==a[i][j+2])
			{
				f[i][j]=f[i][j+1]=f[i][j+2]=1;
			}
			if(a[i][j]==a[i+1][j]&&a[i+1][j]==a[i+2][j])
			{
				f[i][j]=f[i+1][j]=f[i+2][j]=1;
			}//检测三联通
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(f[i][j])
			{
				dfs(i,j,a[i][j]);//染色
				ans++;
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Struggle_ong (赞：2)

### 题目大意：
给一个图，图上有若干数字，求长为 $ 3 $，宽为 $ 1 $ 的长方形的数量。注意：如果有长方形连通（如下图），则只计算一个。
```
1 1 1
1 2 3
1 5 6
1 4 9
```


### 思路
先不考虑连通的情况，把所有合法的长方形打上标记，用 $ vis [ i ]$ 来记录，再深度优先搜索（dfs），如果越过边界或已被访问过，或者根本不是一个颜色，就 ```return``` 。把已访问过的点赋为 ```false```。

#### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,m;
char a[110][110];
bool vis[110][110];//染色

inline void dfs(int i,int j,char z)//深搜
{
	if(i<1||i>n||j>m||j<1||!vis[i][j]||(a[i][j]!=z))return;//不合法情况
	else{
		vis[i][j]=0;//表示已经访问过
		dfs(i+1,j,z);dfs(i-1,j,z);
		dfs(i,j+1,z);dfs(i,j-1,z);
	}
}

int main()
{
	
	cin>>n>>m;
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2]){//合法长方形打上‘1’的标记
				vis[i][j]=1;
				vis[i][j+1]=1;
				vis[i][j+2]=1;
			}
			if(a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j]){//合法长方形打上‘1’的标记
				vis[i][j]=1;
				vis[i+1][j]=1;
				vis[i+2][j]=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(vis[i][j]==1){
				dfs(i,j,a[i][j]);//dfs，深搜
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：wtwk33 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT319)

首先这道题就是个联通块。

题目中说三个横着或纵着相同的数字相连就视为一个长方形。

那么我们可以枚举每一种情况打上标记最后搜索一下就可以了。

```cpp
if(a[i][j] == a[i][j + 1] && a[i][j + 1] == a[i][j + 2])
   vis[i][j] = vis[i][j + 1] = vis[i][j + 2] = 1;
if(a[i][j] == a[i + 1][j] && a[i + 1][j] == a[i + 2][j])
   vis[i][j] = vis[i + 1][j] = vis[i + 2][j] = 1;
```
接下来我们可以判断联通块的数量。

```cpp
for(int i = 1 ; i <= n ; i++)
   for(int j = 1 ; j <= m ; j++)
      if(vis[i][j])
         dfs(i , j , a[i][j] , ++ans); 
```
接下来本体的核心DFS判联通块。

```cpp
void dfs(int x , int y , char now , int ans)
{
   for(int i = 1 ; i <= 4 ; i++)
   {
       int fx = x + dx[i];
       int fy = y + dy[i];//打表做法由于本人很懒所以就打表了
       if(fx > 0 && fx <= n && fy > 0 && fy <= m && vis[fx][fy] && now == a[fx][fy])
       {
            vis[fx][fy] = 0;
	    dfs(fx , fy , a[fx][fy] , ans);// ans也可以不传就是想压一下行
       }
   }
}
```
下面是递归做法。

```cpp
void dfs(int x , int y , char now , int ans)
{
   if(x <= 0 || x > n || y <= 0 || y > m || !vis[x][y] || now != a[x][y])
	return ; // 不合法直接结束递归
   vis[x][y] = 0;
   dfs(x + 1 , y , now , ans);
   dfs(x - 1 , y , now , ans);
   dfs(x , y + 1 , now , ans);
   dfs(x , y - 1 , now , ans);
}

```
#### 完整代码：

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n , m;
char a[102][102] ;
int vis[102][102];
int dx[] = {0 , 0 , 0 , 1 , -1};
int dy[] = {0 , 1 , -1 , 0 , 0};

void dfs(int x , int y , char now , int ans)
{
   for(int i = 1 ; i <= 4 ; i++)
   {
	int fx = x + dx[i]; //表上下左右四个方向
	int fy = y + dy[i];
	if(fx > 0 && fx <= n && fy > 0 && fy <= m && vis[fx][fy] && now == a[fx][fy]) //注意一定要没有访问过
	{
	    vis[fx][fy] = 0; //访问过打上标记
	    dfs(fx , fy , a[fx][fy] , ans);
	}
   }
}
int main()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++) // 不知道为啥 用int型过不了 我用的是scanf("%1d" , &a[i][j]);最后只好改成char
       for(int j = 1 ; j <= m ; j++)
            cin >> a[i][j];
    for(int i = 1 ; i <= n ; i++)
	for(int j = 1 ; j <= m ; j++)
	{
	    if(a[i][j] == a[i][j + 1] && a[i][j + 1] == a[i][j + 2]) // 两种联通块情况暴力判断
		vis[i][j] = vis[i][j + 1] = vis[i][j + 2] = 1;       // 用vis数组打上标记可能是一个合法的联通块
	    if(a[i][j] == a[i + 1][j] && a[i + 1][j] == a[i + 2][j])
		vis[i][j] = vis[i + 1][j] = vis[i + 2][j] = 1;
	}
    int ans = 0;
    for(int i = 1 ; i <= n ; i++)
	for(int j = 1 ; j <= m ; j++)
	    if(vis[i][j])
		dfs(i , j , a[i][j] , ++ans); // 每递归完一次答案加以
    cout << ans << "\n";
    return 0;
}
```



---

## 作者：Lysea (赞：0)

## 思路

这题要把所有点全部遍历一遍，所以需要用到搜索，这里使用的是深搜。

每次可以向上、下、左、右四个方向拓展，如果连续搜索到 $3$ 个字符，并且周围再无相同字符，答案就加 $1$。
## 核心代码
为了防止有人抄袭，这里只放上核心代码。
```
bool check(int x,int y){
	if(x<1||y<1||x>n||y>m||a[x][y]!=c) return false;
	return !vis[x][y];
}
void dfs(int x,int y){
	if(check(x,y)){
		f[x][y]=false;
		dfs(x+1,y);
		dfs(x-1,y);
		dfs(x,y+1);
		dfs(x,y-1);
	}
}
```
其中的第一个函数用来检查是否可以访问，如果超出范围或已访问过，就不用往下遍历了。

---

## 作者：_Hu_Tao (赞：0)

# 此题略水
题目意思：有H行W列的矩阵，每一个矩阵都有一个数字填充。我们需要找出连续的横着3个及以上或竖着3个及以上的，由同一数字构成的长方形。**连通的只算一个**

————————题目意思解释————————

~~不懂？~~ 来看下面一组数据

0123

1113

0123

按理有三个由同一数字构成的长方形。

0**1**2**3**

**1113**

0**1**2**3**

但是**连通的只算一个**

那么，答案是2：

012**3**

**1113**

012**3**

————————解题思路分析————————

了解完题目意思之后，我们来分析解题思路：

基本分为以下几步：

1、输入矩阵

2、找出可能连着的三个

3、利用dfs（深搜）排除连通过的长方形

4、最后输出答案

简单来说此题还是很水的，大家平时冷静思考，编程思路一定会更上一层楼~~我除外~~。

# AC代码：
```c
#include<bits/stdc++.h>
using namespace std;
const int MAX=101;//定义常量，用于分配
int N,M,sum,book[MAX][MAX];
char mat[MAX][MAX];
void fun(int x,int y,char z) {
	if(x<1||y<1||x>N||y>M||!(mat[x][y]==z)||book[x][y]==0)return ;//判断越界和是否用过
	else{
		book[x][y]=0;//这一步很重要，用于排除已经联通的长方形
		fun(x+1,y,z);fun(x-1,y,z);//继续深搜，找左一个和右一个
		fun(x,y+1,z);fun(x,y-1,z);;//继续深搜，找上一个和下一个
	}
}
int main() {
	cin>>N>>M;
	for(int i=1; i<=N; i++){
		for(int j=1; j<=M; j++){
			cin>>mat[i][j];//输入矩阵
		}	
	}
	
	for(int i=1; i<=N; i++){//找出连续的横着3个及以上或竖着3个及以上的，由同一数字构成的长方形
		for(int j=1; j<=M; j++){
			if(mat[i][j]==mat[i][j+1]&&mat[i][j]==mat[i][j+2]){
				book[i][j]=book[i][j+1]=book[i][j+2]=1;//标记为符合的长方形
			}
			if(mat[i][j]==mat[i+1][j]&&mat[i][j]==mat[i+2][j]){
				book[i][j]=book[i+1][j]=book[i+2][j]=1;//标记为符合的长方形
			}	
		}
	}
	for(int i=1; i<=N; i++){
		for(int j=1; j<=M; j++){
			if(book[i][j]==1){//如果是符合要求的长方形
				fun(i,j,mat[i][j]);//进行深搜
				sum++;//和加1
			}	
		}
	}
	cout<<sum<<endl;//输出和
	return 0;
}
```
如果对你有帮助，点个赞吧QAQ


---

