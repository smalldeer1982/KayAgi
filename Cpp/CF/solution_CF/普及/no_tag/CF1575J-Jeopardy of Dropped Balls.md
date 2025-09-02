# Jeopardy of Dropped Balls

## 题目描述

Mr. Chanek has a new game called Dropping Balls. Initially, Mr. Chanek has a grid $ a $ of size $ n \times m $

Each cell $ (x,y) $ contains an integer $ a_{x,y} $ denoting the direction of how the ball will move.

- $ a_{x,y}=1 $ — the ball will move to the right (the next cell is $ (x, y + 1) $ );
- $ a_{x,y}=2 $ — the ball will move to the bottom (the next cell is $ (x + 1, y) $ );
- $ a_{x,y}=3 $ — the ball will move to the left (the next cell is $ (x, y - 1) $ ).

Every time a ball leaves a cell $ (x,y) $ , the integer $ a_{x,y} $ will change to $ 2 $ . Mr. Chanek will drop $ k $ balls sequentially, each starting from the first row, and on the $ c_1, c_2, \dots, c_k $ -th ( $ 1 \leq c_i \leq m $ ) columns.

Determine in which column each ball will end up in (position of the ball after leaving the grid).

## 说明/提示

In the first example, the first ball will drop as follows. Note that the cell $ (1, 1) $ will change direction to the bottom direction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575J/fa2adb81fdf96ce1b92e46629bbcb5cf70e88c62.png)The second and third balls will drop as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575J/7c28f503603add2e57bd518e7c027aa1a32b9f99.png)All balls will be dropped from the first row and on the $ c_1, c_2, \dots, c_k $ -th columns respectively. A ball will stop dropping once it leaves the grid.

## 样例 #1

### 输入

```
5 5 3
1 2 3 3 3
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
1 2 1```

### 输出

```
2 2 1```

## 样例 #2

### 输入

```
1 2 2
1 3
1 2```

### 输出

```
1 2```

# 题解

## 作者：RE_Prince (赞：4)

# CF1575J Jeopardy of Dropped Balls 题解

[题目](https://www.luogu.com.cn/problem/CF1575J)

## 题目大意

给你一个矩阵，每个点有一个点值（ $1$ $2$ $3$ ），每个点值分别会让球的坐标进行一些操作，球经过的地方会变成 $2$ ，问你最后球在哪个列上。

## 思路

大模拟，如果纯暴力的话时间复杂度 $O(mk)$ ，进行一些优化后可能会变成 $O(mk/v)$ （ $v$ 为小常数）。这题时限是 $2.0s$ ，两种方法均可过。

## Algorithm 1

模拟，按照题目要求的一步一步做，准没问题。

code：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1009;
int n, m, i, j, k, a[N][N];
int cnt, sum;
signed main()
{
    int T;
    cin >> n >> m >> T;
    int x, y;
    ios::sync_with_stdio(0);//加速读入
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            cin >> a[i][j];
    while (T--)
    {
        int col;
        cin >> col;
        x = 1, y = col;
        while (x <= n)
        {
            int s = a[x][y];//记录原来的值
            a[x][y] = 2;//覆盖，变成2
            if (s == 1) y++;//三种操作
            if (s == 2) x++;
            if (s == 3) y--;
        }
        cout << y << " ";
    }
    return 0;
}
```

## Algorithm 2

经过读题，我们发现，球经过一个点时，这个点就会变成 $2$ ，也就是垂直往下走。因此，利用这个特性，在全盘都为 $2$ 时，就直接输出输入的那个数。

### 实现

用 $a$ 记录还没有变成 $2$ 的点的个数，每经过一个不是 $2$ 的点时，把它变成 $2$ ， $a$ 减 $1$ 。

code：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1009;
int n, m, i, j, k, a[N][N];
int cnt, sum;
signed main()
{
    int T;
    cin >> n >> m >> T;
    int x, y;
    ios::sync_with_stdio(0);
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            if (a[i][j] != 2) cnt++;//记录不是2的个数
        }
    }
    while (T--)
    {
        int col;
        cin >> col;
        if (!cnt)//全变成2了
        {
            cout << col << " ";
            goto end;//直接跳过，节约时间
        }
        x = 1, y = col;
        while (x <= n)
        {
            int s = a[x][y];//记录初始值
            if (a[x][y] != 2) a[x][y] = 2, cnt--;//注意cnt--，否则不会起到优化作用
            if (s == 1) y++;//三种操作
            if (s == 2) x++;
            if (s == 3) y--;
        }
        cout << y << " ";
    end:;//也可以加一个continue
    }
    return 0;
}
```

---

## 作者：LJ07 (赞：2)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/CF1575J)

## 思路简述
这里介绍一个比较差的想法。

容易发现，进行多次操作后，球会连续往下。

我们对于每一列维护并查集，父亲即为连续往下的最底端。

然后我们分两种情况讨论:

+ 若该球还未位于连续下落的最低端，那么就直接跳过中间过程直接到达最低端。

+ 若该球已经位于最低端，则更新该列最低端的位置且通过 $a[][]$ 确定移动方向并移动。

时间复杂度 $O(nm\alpha(m))$。

## 丑陋の代码
没有刻意压行，可读性还可以。
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int init(){
	char c;
	while (!isdigit(c = getchar()));
	int x (c ^ 48);
	while (isdigit(c = getchar())) x = x * 10 + (c ^ 48);
	return x;
}
const int N (1e3);
const int D[4][2] = {{0, 0}, {0, 1}, {1, 0}, {0, -1}};
int n, m, k, f[N * N + N + 5], a[N + 5][N + 5];
int getf(int x){return f[x] == x ? x : f[x] = getf(f[x]);}
int zip(int x, int y){return x * m + y - m;}
pair<int, int> unzip(int p){
	if (p % m)return {p / m + 1, p % m};
	return {p / m, m};
}
int Func(int x, int y){
	if (x > n)return y;
	if (getf(zip(x, y)) == zip(x, y)){
		f[zip(x, y)] = getf(zip(x + 1, y));
		return Func(x + D[a[x][y]][0], y + D[a[x][y]][1]);
	}else {
		pair<int, int> tmp (unzip(getf(zip(x, y))));
		return Func(tmp.first, tmp.second);
	}
}
int main()
{
	n = init(), m = init(), k = init();
	for (int i(1); i <= n; ++i)
		for (int j(1); j <= m; ++j)
			a[i][j] = init();
	for (int i(n * m + m); i; --i)	f[i] = i;
	while (k--)printf("%d ", Func(1, inti()));
	return 0;
}

```

---

## 作者：wdgm4 (赞：1)

这道题其实真挺简单的，~~我才不会告诉你我调这道题的错要调傻了~~。

------------

我是用搜索做的。

个人认为搜索算是一种~~优雅的~~暴力，较为简单的搜索只需按照题目的要求，去模拟一些题目要求的步骤，有时加一~~亿~~点剪枝，很容易就能 AC。

## 思路

按照题意，小球有三种移动方式，分别为向左，向右和向下。
而数组 $a$ 控制着小球的移动方向。
此题唯一特殊的地方是小球经过的地方会改变 $a_{ij}$ 的值。
我们只需用搜索维护小球的移动和 $a_{ij}$ 的改变即可。

下面代码中的 ```dfs``` 函数是搜索的核心，```x``` 表示小球在 x 轴的坐标，```y``` 表示小球在 y 轴的坐标。

## code
```cpp
#include<bits/stdc++.h>
#define XD 114514
#define yee 1919810

using namespace std;
int n,m,k,a[1010][1010],ans;
void dfs(int x,int y){//搜索
	if(x>n or y>m){
		ans=y;
		return;
	}
	if(a[x][y]==1){//把小球向右移动
		a[x][y]=2;
		y++;
	}else if(a[x][y]==2){//把小球向下移动
		x++;
	}else if(a[x][y]==3){//把小球向左移动
		a[x][y]=2;
		y--;
	}
	dfs(x,y);
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=k;i++){
		int nem;
		scanf("%d",&nem);
		ans=0;//初始化，其实没有也可以
		dfs(1,nem);
		cout<<ans<<" ";
	}
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/89653049)

---

## 作者：dfgz (赞：1)


------------

## 题意


一开始所有小球从第一行第 $c_i$ 列落下。

位置 $(x,y)$ 里面包含一个整数 $a_{x,y}$，表示在该坐标下的小球将要到达的位置。

具体要求：

$1$：如果 $a_{x,y} = 1$，这个小球向右移动一位。

$2$：如果 $a_{x,y} = 1$，这个小球向下移动一位。

$3$：如果 $a_{x,y} = 1$，这个小球向左移动一位。

特殊：如果经过了 $(x,y)$，则 $a_{x,y}$ 变为 $2$。

求出 $k$ 个小球最后会落在哪一列。

------------

## 思路：

分析题意可得，$a_{x,y}$ 控制着小球的移动方向，但是所有经过的位置上的整数都会变成 $2$，因此我们需要修改再维护。至于时间复杂度的话，数据范围很小，所以搜索是可以通过。
可以一个一个遍历，因为他是一个一个
地扔下去的所以可以打个循环，输入之后遍历一遍，然后再遍历下一个。



------------

```cpp
for(int i=1;i<=k;i++)
{
	int u;
	cin>>u;
	dfs(1,u);//遍历每个小球
}
```


------------

## $ACcode$

```
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[1009][1009];
void dfs(int x,int y)
{
	if(x==n+1||y==m+1)	
	{
		cout<<y<<" ";//输出答案
		return ;
	}
	if(a[x][y]==1)
	{
		a[x][y]=2;//走过的变2
		dfs(x,y+1);//向右走
	}
	else if(a[x][y]==2)
	{
		a[x][y]=2;
		dfs(x+1,y);//下
	}
	else if(a[x][y]==3)
	{
		a[x][y]=2;
		dfs(x,y-1);//左
	}
}
int main()
{
	
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
	{
		cin>>a[i][j];//输入（绝不是手懒不打scanf
	}
	for(int i=1;i<=k;i++)
	{
		int u;
		cin>>u;
		dfs(1,u);//遍历每个小球
	}
	
	return 0;
}
```



---

## 作者：wenlebo (赞：0)

简单的按题意模拟即可，建立二维数组储存网格图，在不停进行坐标移动即可，没有卡时不会超。

上代码：

```
#include <bits/stdc++.h>
using namespace std;
int dt[1200][1200];
int m,n,k,x,y,a;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>dt[i][j];
		}
	}
	for(int i=0;i<k;i++){
		cin>>a;
		x=1;
		y=a;
		while(x!=n+1){
			switch(dt[x][y]){
				case 1:
					dt[x][y]=2;
					y++;
					break;
				case 2:
					dt[x][y]=2;
					x++;
					break;
				case 3:
					dt[x][y]=2;
					y--;
					break;
			}
		}
		cout<<y<<" ";
	}
	return 0;
}
```


---

## 作者：kimi0705 (赞：0)

# Jeopardy of Dropped Balls
## 大模拟
**其实只要模拟** 这几句话就行了。
- 如果 $a_{x,y}=1$，则这个小球将会向右移动到 $(x,y+1)$。
- 如果 $a_{x,y}=2$，则这个小球将会向右移动到 $(x+1,y)$。
- 如果 $a_{x,y}=3$，则这个小球将会向右移动到 $(x,y-1)$。
- 特别地，如果一个小球经过了 $(x,y)$，则 $a_{x,y}$ 变为 $2$。
## code
 ```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000 + 100;
int n, m, k;
short Map[N][N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) // 输入。
		for (int j = 1; j <= m; ++j)
			cin >> Map[i][j];
	while(k--) { 
		int x = 1, y;
        cin >> y;
        while(x <= n) {
            if(Map[x][y] == 1) Map[x][y] = 2, y++; // 模拟
            else if(Map[x][y] == 2) Map[x][y] = 2, x++;// 模拟
            else if(Map[x][y] == 3) Map[x][y] = 2, y--;// 模拟
        }
        cout << y << ' ';
	}
    return 0;
}

```

---

## 作者：Tear_stains (赞：0)

本题为一个比较简单的深搜，甚至都不用剪枝。

正题开始：
本题中小球有三种选择：向下，向右，向左。每经过一个点，点的权值就变成了 $2$。

开始搜索：先特判是否越界，越界直接返回，并更新答案。否则看当前位置上的数字是几，判断是往下或左或右搜。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, k;
int ans;
int a[1005][1005];
void dfs(int x, int y) {
	if(x>n || y>m) {//越界就return 
		ans = y;//更新答案 
		return;
	} if(a[x][y] == 1) {//向右移动
		a[x][y] = 2;//改变权值 
		++y;//处理下次的位置 
	} else if(a[x][y] == 2) {//向下移动（本来就是2，不用更改） 
		++x;//处理下次的位置 
	} else if(a[x][y] == 3) {//向左移动
		a[x][y] = 2;//改变权值 
		--y;//处理下次的位置 
	}
	dfs(x, y);//dfs开始 
}
int main(){
	cin >> n >> m >> k;
	for(int i = 1;i <= n; ++i) {
		for(int j = 1;j <= m; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	for(int i = 1;i <= k; ++i) {
		int c;
		scanf("%d", &c);
		dfs(1, c);
		cout << ans << " ";
	}
	return 0;
}
```


---

## 作者：xzy090626 (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1575J)

------------
## 题目大意
有 $k$ 个小球从一个 $n \times m$ 的方阵的第一行某一列 $(1,c_i)$ 出发，球所移动的方向由该位置的数字 $a_{i,j} (1 \le a_{i,j} \le 3)$ 决定，求每个小球最终落点（小球无法再走的地方，即当 $i > n$ 或 $j > m$ 时）。

------------

## 思路
用一个二维数组来模拟该方阵，然后模拟每个小球移动的过程，每次移动判断当前位置是否合法（判断越界），最后输出。由于时限为 2.0s，因此不会超时。

------------
## 时间复杂度的分析
本题没有太大的难度，思路也很简单、清晰。因此，我来讲一下关于本题时间复杂度的分析，帮助大家日后更好地分析。

从题目给出的提示图里，我们可以看出小球的路线大致是自上至下的，而方阵共有 $m$ 列。又因为共有 $k$ 个小球，所以时间复杂度是 $O(mk)$。

那么为什么小球会一直向下呢？

由题意我们可知，若要使小球向下移动，则要它处于对应数字为 2 的地方。但是，我们知道每个小球走过的地方都会变成 2，所以 2 的数量会越来越多，小球往下走的几率也越来越高，所以小球会一直向下。

------------
## 代码实现
### 方法一：递归模拟
对每个小球的移动进行递归，每一层递归都是一次移动，边界条件就是对数组越界的检查。

```cpp
#include<bits/stdc++.h>
#define MAX 1007
using namespace std;
int s[MAX][MAX];
int n,m;
int k;
void dfs(int x,int y){
    if(!(x<=n && y<=m)){
        cout<<y<<' ';
        return ;
    }
    int tmp = s[x][y];
    s[x][y] = 2;
    if (tmp==1) dfs(x,y+1);
    else if(tmp==2) dfs(x+1,y);
    else dfs(x,y-1);
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j){
            cin>>s[i][j];
        }
    }
    for(int i=1;i<=k;++i){
        int t;
        cin>>t;
        dfs(1,t);
    }
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/72735010)

------------
### 方法二：while 模拟
与递归类似，但是将递归改成 while，效率也经常会更高（然而时间复杂度 $O(mk)$ 是一样的，所以有时区别不大），也更加易懂、好写（强推）。

```cpp
#include<bits/stdc++.h>
#define MAX 1007
using namespace std;
int s[MAX][MAX];
int n,m;
int k;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=m; ++j) {
			cin>>s[i][j];
		}
	}
	for(int i=1; i<=k; ++i) {
		int t;
		cin>>t;
		int x=1,y=t;
		while(x<=n && y<=m) {
			int tmp = s[x][y];
			s[x][y] = 2;
			if(tmp==1) y++;
			else if(tmp==2) x++;
			else y--;
		}
		cout<<y<<' ';
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/72746328)

------------
## 总结
本题其实是一道不太难的小模拟，上述两种方法也差距不大，因此是一道模拟的好题。同时，如果用递归做的话，其实可以锻炼写搜索的能力，更锻炼思维，因此建议大家两种方法都试一试。

---

## 作者：徐天乾 (赞：0)

# 思路
直接按题目给定要求进行处理（PS：建议评红或者黄）。

时间复杂度：由于每个小球经过一个点后，该点会变为 $2$,而 $2$ 会让球向右走，$1$ 和 $3$ 会让球往上下走。那么小球向上下的次数最多为 $O(nm)$，即每个点遍历一次，每个小球向右的次数为 $m$，时间复杂度为 $O(mk)$，由于时限为 2.0s 且程序常数小，所以可以过。

# 程序
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,n,m,k,x,y,v,a[1010][1010];
int main(){
	scanf("%d %d %d",&n,&m,&k);
	for (i=1;i<=n;i++)	
		for (j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for (i=1;i<=k;i++){
		x=1;scanf("%d",&y); //一开始在 (1,y)
		while (x<=n){
			v=a[x][y];a[x][y]=2;
			if (v==1) y++;
			if (v==2) x++;
			if (v==3) y--; //按题目操作进行处理
		}
		printf("%d ",y); //输出最后的列数
	}
	return 0;
}
```


---

