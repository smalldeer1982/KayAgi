# 通学経路

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2007yo/tasks/joi2007yo_f

太郎君の住んでいる JOI 市は，南北方向にまっすぐに伸びる $ a $ 本の道路と，東西方向にまっすぐに伸びる $ b $ 本の道路により，碁盤の目の形に区分けされている．

南北方向の $ a $ 本の道路には，西から順に $ 1,\ 2,\ \ldots,\ a $ の番号が付けられている．また，東西方向の $ b $ 本の道路には，南から順に $ 1,\ 2,\ \ldots,\ b $ の番号が付けられている．西から $ i $ 番目の南北方向の道路と，南から $ j $ 番目の東西方向の道路が交わる交差点を $ (i,\ j) $ で表す．

太郎君は，交差点 ($ 1,\ 1 $) の近くに住んでおり，交差点 ($ a,\ b $) の近くの JOI 高校に自転車で通っている．自転車は道路に沿ってのみ移動することができる．太郎君は，通学時間を短くするため，東または北にのみ向かって移動して通学している．

現在，JOI 市では，$ n $ 個の交差点 $ (x_1,\ y_1),\ (x_2,\ y_2),\ \ldots,\ (x_n,\ y_n) $ で工事を行っている．太郎君は工事中の交差点を通ることができない．

太郎君が交差点 $ (1,\ 1) $ から交差点 $ (a,\ b) $ まで，工事中の交差点を避けながら，東または北にのみ向かって移動して通学する方法は何通りあるだろうか．太郎君の通学経路の個数 $ m $ を求めるプログラムを作成せよ．

- - - - - -

## 说明/提示

### Sample Explanation 1

下図は $ a\ =\ 5,\ b\ =\ 4,\ n\ =\ 3 $ で，工事中の交差点が $ (2,\ 2),\ (2,\ 3),\ (4,\ 2) $ の場合を表している． !\[route-fig1.png\](https://img.atcoder.jp/joi2007yo/route-fig1.png) この場合，通学経路は $ m\ =\ 5 $ 通りある．$ 5 $ 通りの通学経路を全て図示すると，以下の通り． !\[route-fig2.png\](https://img.atcoder.jp/joi2007yo/route-fig2.png)

## 样例 #1

### 输入

```
5 4
3
2 2
2 3
4 2```

### 输出

```
5```

# 题解

## 作者：Kle1N (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_joi2007yo_f)
# 观前提示
本蒟蒻没怎么写过题解，如有错误或建议，欢迎私信交流！

---
设从 $(1,1)$ 到 $(i,j)$ 的路径数为 $w(i,j)$，可以得出以下结论：

1. 若 $(i,j)$ 不能走，则 $w(i,j)=0$，因为没有任何一条路径可以到达该点；
2. 若 $(i,j)$ 能走，则 $w(i,j)=w(i,j-1)+w(i-1,j)$，具体原因见下：

因为只能向东或向北走，所以能到 $(i,j)$ 的路径必然都是从 $(i,j-1)$ 和 $(i-1,j)$ 来的，而 $(i,j-1)$ 的每条路径都只需再往东走一步就能到达 $(i,j)$，所以能从 $(i,j-1)$ 到达 $(i,j)$ 的路径数就是 $w(i,j-1)$；同理，能到 $(i-1,j)$ 的每条路径都只需再往北走一步就能到达 $(i,j)$，所以能从 $(i-1,j)$ 到达 $(i,j)$ 的路径数就是 $w(i-1,j)$。根据[加法原理](https://baike.baidu.com/item/%E5%8A%A0%E6%B3%95%E5%8E%9F%E7%90%86#1)，能到达 $(i,j)$ 的路径数就等于能从 $(i,j-1)$ 到达 $(i,j)$ 的路径数加上能从 $(i-1,j)$ 到达 $(i,j)$ 的路径数，即：$w(i,j)=w(i,j-1)+w(i-1,j)$。

此外，除非 $(1,1)$ 不能走，否则 $w(1,1)=1$。

还有一点，这是 AT 的题，输出答案时别忘了加个换行。

结合上述所有的要点，我们就可以高高兴兴地 AC 了！

---
# AC代码
~~因为递推的做法已经有大佬发过了，所以就只能写递归了QAQ~~
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,b;
bool f[17][17];
int w(int x,int y){
	if(x<0 || x>a || y<0 || y>b){
		return 0;
	}
	if(f[x][y]){
		return 0;
	}
	if(x==1 && y==1){
		return 1;
	}
	return w(x,y-1)+w(x-1,y);
}
int main(){
	cin>>a>>b;
	cin>>n;
	for(int i=1;i<=n;i++){
		int t1,t2;
		cin>>t1>>t2;
		f[t1][t2]=1;
	}
	cout<<w(a,b)<<endl;
	return 0;
}

```
感谢观看！

---

## 作者：ZnHF (赞：3)

萌新的第一篇题解，如有不足请多多包涵。

### 题意简述：
给定一张 $a \times b$ 的地图，在其中加入 $n$ 个不可通过的地块，求从起点走到终点的路径总数。

### 题目分析：
这是一道 DP 题，与[P1958 上学路径](https://www.luogu.com.cn/problem/P1958)几乎完全一样。不妨设 $\mathit{f}_{i,j}$ 为从起点到当前坐标的路径总数。

状态转移方程为 $\mathit{f}_{i,j}={f}_{i-1,j}+{f}_{i,j-1}$。

初始状态 $\mathit{f}_{1,1}=1$。

### 最后附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,maze[20][20],f[200][200];
int main(){
	cin>>n>>m>>a;
	int t1,t2;
	for(int i=0;i<a;i++){
		cin>>t1>>t2;
		maze[t1][t2]=-1;
	}
	f[1][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i!=1 && maze[i-1][j]!=-1) f[i][j]+=f[i-1][j]; //注意判断maze[i-1][j]是否能走，注意不要越界。
			if(j!=1 && maze[i][j-1]!=-1) f[i][j]+=f[i][j-1];
		}
	}
	cout<<f[n][m]<<endl;
	return 0;
}
```

---

## 作者：S__X (赞：2)

居然没有人写 $dfs$！那我来发一篇 $dfs$ 题解。

## 简要题意：
![](https://img.atcoder.jp/joi2007yo/route-fig1.png)

如图：有一个棋盘，起点为 $(1,1)$，终点为 $(n,m)$，还有 $t$ 个障碍物。你现在要从起点到终点，只能向右或向上走，且不能经过障碍物，问你有多少中行走方案。

## 思路：
把所有障碍物标记一下，从起点向终点进行深搜，如果当前点为终点方案 $+1$。

**注意**：搜索的方向只有两个，向上和向右

## $\texttt{code:}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,a[50],b[50],flag[50][50],ans;
int dx[5]={0,1};//两个方向
int dy[5]={1,0};
void dfs(int x,int y){
	if(x==n&&y==m) {//当前点为终点
		ans++;//方案数+1
		return;
	}
	for(int i=0;i<2;i++){
		int nx=dx[i]+x,ny=dy[i]+y;
		if(nx>0&&ny>0&&nx<=n&&ny<=m&&!flag[nx][ny]){
			flag[nx][ny]=1;//回溯
			dfs(nx,ny);
			flag[nx][ny]=0;
		}
	}
	return;
}
int main(){
	cin>>n>>m>>t;
	for(int i=1;i<=t;i++) {
		cin>>a[i]>>b[i];
		flag[a[i]][b[i]]=1;//对障碍物进行标记
	}
	dfs(1,1);
	cout<<ans<<endl;输出方案数
	return 0;
}
```

---

## 作者：朱屹帆 (赞：2)

### 题目：[AT2512 通学経路](https://www.luogu.com.cn/problem/AT2512)
### 题意：这一题翻译讲的不是很清楚，我来翻译一下：
在一个$ a*b $的地图里添加几个障碍，在只能往上和右方向行进的情况下，问从$(1,1)$到$(a,b)$究竟有多少走法。

### 思路：
这一题实际很类似[P1002 过河卒](https://www.luogu.com.cn/problem/P1002)，甚至比过河卒还简单一些，直接递推可以走的方法数量。

先定义一个$bool$的二维数组，初始为false，来判断是否有障碍；

再定义一个$int$的二维数组，初始为0，来递推方法数；

递推主代码如下：
```cpp
const long long N = 1e4+5;
long long s[N][N]; //记录方案数
bool judge[N][N]={false}; //判断障碍
......
int main(){
	......
	s[1][1]=1; //递推初始
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			if(i==1&&j==1)continue; //(1,1)方案数1
			if(judge[i][j]==true)continue; //有障碍
			s[i][j]=(s[i][j-1]+s[i-1][j]);//递推式
		}
	}
	cout<<s[a][b]<<endl; //输出答案
	return 0;
}
```
这一道题目就基本可以过了。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long q=0,w=1;
	char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')q=q*10+ch-'0',ch=getchar();
	return q*w;
} //这一道题卡不了快读，所以没用 
const long long N = 1e4+5;
long long s[N][N]; //记录方案数
bool judge[N][N]={false}; //判断障碍
long long a,b,n,x,y;
int main(){
	cin>>a>>b>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		judge[x][y]=true; //设置障碍 
	}
	s[1][1]=1; //递推初始
	for(int i=1;i<=a;i++){
		for(int j=1;j<=b;j++){
			if(i==1&&j==1)continue; //(1,1)方案数1
			if(judge[i][j]==true)continue; //有障碍
			s[i][j]=(s[i][j-1]+s[i-1][j]); //递推式 
		}
	}
	cout<<s[a][b]<<endl; //输出答案
	return 0;
}
```
### 推荐：
与其类似的题有很多，以下题目比较经典：
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)

- [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)

- [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)

- [P1191 矩形](https://www.luogu.com.cn/problem/P1191)

### 注：
这一题我也分不太清是递推还是DP，反正比较水，数据也不卡，怎么解都可以过。

居然是第一个发题解的！

---

## 作者：_zhx (赞：1)

# 题目大意

题目中说了一大堆，但我概括出来就这么多：一个 $a$ 行 $b$ 列的矩阵，给定 $n$ 个点的坐标，对应坐标不能走，问有几种方法？

## 题目思路

其实这就是一道深搜题，只要在深搜模板上改一改就行了。

先输入 $a$ 行 $b$ 列和 $n$ 个点不能走。$n$ 次循环，输入 $c$，$d$ 后用数组标记。然后进入深搜。深搜结束后再输出 $s$。

## 深搜思路

先判断是否达到终点，如果达到终点，$s$ 加一后，在结束这次深搜。

如果没有达到，就进行两次循环，定义 $nx$ 和 $ny$，计算出 $nx$ 和 $ny$ 后，判断有没有超出边界和这个点是否走过，如果都符合，就把这个点标记成已走过，进行下一次深搜，再把这个点标记成没走过。（回溯）

### 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,s=0;//a行b列的矩阵，s来记录方案数量
int dx[2]={0,1},dy[2]={1,0};//搜索的方向
int c,d;//第c行d列不能走
bool f[50][50]={false};//标记这个点是否走过的数组
void dfs(int x,int y)
{
	if(x==a&&y==b)//如果到达终点
	{
		s++;//次数加1
		return ;//结束这一次dfs
	}
	for(int i=0;i<2;i++)
	{
		int nx=dx[i]+x,ny=dy[i]+y;
		if(nx>0&&nx<=a&&ny>0&&ny<=b&&f[nx][ny]==false)
		//判断是否出界和这个点是否走过
		{
			f[nx][ny]=true;//已经走过了，标记一下
			dfs(nx,ny);//下一次dfs
			f[nx][ny]=false;//回溯
		}
	}
	return ;
}
int main()
{
	cin>>a>>b>>n;//输入a行b列和n个点不能走
	for(int i=1;i<=n;i++)
	{
		cin>>c>>d;//第c行d列不能走
		f[c][d]=true;//把这个点标记
	}
	dfs(1,1);//从第1行1列开始搜索
	cout<<s<<endl;//输出方案数
	//（AT不换行，亲人两行泪）
	return 0;
}
```


---

## 作者：_s_z_y_ (赞：1)

## 思路
一道 dp 题。

先定义一个数组记录有工程的位置。

因为只能向东方或北方移动，所以转移方程为：

- 如果 $a(i,j)$ 有工程，$a(i,j) = 0$。

- 如果 $a(i,j)$ 没有工程，$a(i,j) = a(i,j-1)+a(i-1,j)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[20][20],A,B,x,y;
bool b[20][20];
int main()
{
	cin>>x>>y>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>A>>B;
		b[A][B]=1;
	}
	a[1][0]=1;
	for(int i=1;i<=x;i++)
		for(int j=1;j<=y;j++)
			if(b[i][j]==0)
				a[i][j]=a[i-1][j]+a[i][j-1];
	cout<<a[A][B];
}
```

---

## 作者：Shadow_T (赞：1)

## 题目大意：
有一个网格，太郎君可以向上走或向右走，但是有些点是不能走的，求太郎君从 $(1,1)$ 到 $(n,m)$ 有多少种方案。
## 思路分析：
一眼朴素 dp。

设太郎君走到 $(x,y)$ 的方案数为 $f_{x,y}$，然后进行如下操作：

+ 如果 $(x,y)$ 不能走，$f_{x,y}=0$。

+ 如果 $(x,y)$ 可以走，$f_{x,y}=f_{x-1,y}+f_{x,y-1}$。

然后按上述思路操作即可。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,n,x,y,f[41][41];
bool st[41][41];
int main()
{
	cin>>a>>b>>n;
	for(int i=0;i<n;i++)
	{
	    cin>>x>>y;
	    st[x][y]=1;
	}
	f[0][1]=1;
	for(int i=1;i<=a;i++)
	for(int j=1;j<=b;j++)
	if(!st[i][j]) f[i][j]=f[i-1][j]+f[i][j-1];
	cout<<f[a][b]<<"\n";
	return 0;
}
```

---

## 作者：_7Mr (赞：1)

# 思路
小学三年级的奥数题目，一眼看穿，一道朴素 dp。

因为只能向北走或者向东走，所以这些地方只有一种方法走到那儿，因此最左边一列全是 $1$ 最底下一排也全是 $1$。那么我们就可以开始 dp 操作了。因为只能向北走或者向东走，所以一个点只可能从下面来，也就是 $A_{i-1,j}$ 或者从左边来，也就是 $A_{i,j-1}$ 那么我们的 dp 也就操作完成了。

**遇到施工的区域我们直接跳过，因为正在施工所以到达那个点的方案数量就是 $0$。**

这句话稍微有点绕，没有理解的同学，自己模拟一下。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
int a,b,n;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>a>>b>>n;
	vector<vector<int>>s(a);
	for (int k = 0; k < a; k++) {
		vector<int>p(b);
		s[k]=p;
	}
	map<vector<int>,bool> d;
	for (int e=0;e<n;e++) {
		vector<int>f(2);
		int z,q;
		cin>>z>>q;
		z--;
		q--;
		f[0]=z;
		f[1]=q;
		d[f]=true;
	}
	for (int g = 0; g < a; g++) {
		for (int h = 0; h < b; h++) {
			vector<int>i(2);
			i[0]=g;
			i[1]=h;
			if(d[i]) s[g][h]=0;
			else {
				if(g&&h) s[g][h]=s[g - 1][h]+s[g][h - 1];
				else if(g) s[g][h]=s[g - 1][h];
				else if(h) s[g][h]=s[g][h - 1];
				else s[g][h]=1;
			}
		}
	}
	cout<<s[a-1][b-1]<<endl;
	return 0;
}

```

---

## 作者：yangmingshuo114514 (赞：1)

## 题意

在一个网格上，太郎君的家在 $(1,1)$，学校在 $(a,b)$，已知一些坐标是不能走的，且太郎君只能往上或往右走，问太郎君有多少种走的方案。

## 思路

此题类似 [ P1002 过河卒 ](https://www.luogu.com.cn/problem/P1002)，用一个 $dp$ 数组存当太郎君走到某个坐标时的方案总数。答案即为 $\mathit{dp}_{x,y}$。

状态转移方程为：

1. 如果 $(x,y)$ 不能走，那么 $\mathit{dp}_{x,y}=0$；

2. 如果 $(x,y)$ 可以走，那么 $\mathit{dp}_{x,y}=\mathit{dp}_{x-1,y}+\mathit{dp}_{x,y-1}$。

## 代码

此处我设 $\mathit{dp}_{0,1}$ 的初始值为 $1$，这样就可以在无需特判的情况下保证 $\mathit{dp}_{1,1}$ 的值为 $1$。

下面我提供两种实现方法：

1. 直接枚举：

```cpp
#include<cstdio>
int a,b,n,x,y,dp[45][45];
bool vis[45][45];
int main(){
	scanf("%d%d%d",&a,&b,&n);
	while(n--) scanf("%d%d",&x,&y),vis[x][y]=1;
	dp[0][1]=1;
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			if(!vis[i][j]) dp[i][j]=dp[i-1][j]+dp[i][j-1];
	printf("%d\n",dp[a][b]);
	return 0;
}
```

2.记忆化搜索：

```cpp
#include<cstdio>
int a,b,n,x,y,dp[45][45];
bool vis[45][45];
void dfs(int x,int y){
	if(vis[x][y]||dp[x][y]||x==0||y==0) return;
	dfs(x-1,y);
	dfs(x,y-1);
	dp[x][y]=dp[x-1][y]+dp[x][y-1];
}
int main(){
	scanf("%d%d%d",&a,&b,&n);
	while(n--) scanf("%d%d",&x,&y),vis[x][y]=1;
	dp[0][1]=1;
	dfs(a,b);
	printf("%d\n",dp[a][b]);
	return 0;
}
```

---

