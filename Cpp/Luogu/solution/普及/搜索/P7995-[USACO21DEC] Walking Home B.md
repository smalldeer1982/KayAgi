# [USACO21DEC] Walking Home B

## 题目描述

奶牛 Bessie 正准备从她最喜爱的草地回到她的牛棚。

农场位于一个 $N \times N$ 的方阵上（$2 \leq N \leq 50$），其中她的草地在左上角，牛棚在右下角。Bessie 想要尽快回家，所以她只会向下或向右走。有些地方有草堆（haybale），Bessie 无法穿过；她必须绕过它们。

Bessie 今天感到有些疲倦，所以她希望改变她的行走方向至多 $K$ 次（$1 \leq K \leq 3$）。

Bessie 有多少条不同的从她最爱的草地回到牛棚的路线？如果一条路线中 Bessie 经过了某个方格而另一条路线中没有，则认为这两条路线不同。

## 说明/提示

【样例解释】

我们将使用一个由字符 D 和 R 组成的字符串来表示 Bessie 的路线，其中 D 和 R 分别表示 Bessie 向下（down）或向右（right）移动。

第一个子测试用例中，Bessie 的两条可能的路线为 DDRR 和 RRDD。

第二个子测试用例中，Bessie 的四条可能的路线为 DDRR，DRRD，RDDR 和 RRDD。

第三个子测试用例中，Bessie 的六条可能的路线为 DDRR，DRDR，DRRD，RDDR，RDRD 和 RRDD。

第四个子测试用例中，Bessie 的两条可能的路线为 DDRR 和 RRDD。

第五和第六个子测试用例中，Bessie 不可能回到牛棚。

第七个子测试用例中，Bessie 的六条可能的路线为 DDRDRR，DDRRDR，DDRRRD，RRDDDR，RRDDRD 和 RRDRDD。

【数据范围】

- 测试点 2 满足 $K = 1$。
- 测试点 3-5 满足 $K = 2$。
- 测试点 6-10 满足 $K = 3$。

## 样例 #1

### 输入

```
7
3 1
...
...
...
3 2
...
...
...
3 3
...
...
...
3 3
...
.H.
...
3 2
.HH
HHH
HH.
3 3
.H.
H..
...
4 3
...H
.H..
....
H...```

### 输出

```
2
4
6
2
0
0
6```

# 题解

## 作者：BetaCutS (赞：16)

[题目传送门](https://www.luogu.com.cn/problem/P7995)

这道题的大意是要从地图的 $(1, 1) $ 点起，走到 $(n, n)$ 点，要求不能走在草堆上，并且转弯不能超过 $k$ 次，求有多少种可行的方案。

很明显，这是一道搜索题。我们可以在 dfs 函数中定义四个参数：$x$，$y$，$t$，$way$ ，分别表示当前的行、当前的列、当前转弯次数和方向（$0$ 代表往右走，$1$ 代表往下走）。代码如下：

```cpp
//省略缺省源
int T,n,k,a[100][100];
int dfs(int x,int y,int t,int way)
{
	int sum=0;
	if(t>k||a[x][y])//如果转弯次数超过k次，或者该点是个草堆
		return 0;
	if(x==n&&y==n)//如果到达终点，方案数加一
		return 1;
	if(x<n&&!a[x+1][y])
		sum+=dfs(x+1,y,way?t:t+1,1);//往右走
	if(y<n&&!a[x][y+1])
		sum+=dfs(x,y+1,way?t+1:t,0);//往下走
	return sum;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read(),k=read();
		char chr;
		for(int i=1;i<=n;i++)//输入地图
		{
			for(int j=1;j<=n;j++)
			{
				chr=getchar();
				if(chr=='.')
					a[i][j]=0;
				else
					a[i][j]=1;
			}
			chr=getchar();
		}
		printf("%d\n",dfs(1,2,0,0)+dfs(2,1,0,1));
	}
	return 0;
}

```

额，这就 $90$ 分, TLE 了。

我们会发现：在 dfs 的求解过程中，有许多重复的子问题。

记忆化搜索能很好的解决这种问题：开一个四维数组，如果之前没有求解过该状态的，就把该状态的方案数记录下来。以后如果遇到同样的状态的话，就可以直接返回该状态的方案数了。~~这有点绕~~

并且，在开始的时候，我们要把整个记忆化数组初始化为 $-1$。代码如下：

```cpp
//省略缺省源
int T,n,k,a[100][100],g[100][100][10][5];//记忆化数组
int dfs(int x,int y,int t,int way)
{
	int sum=0;
	if(t>k||a[x][y])
		return 0;
	if(g[x][y][t][way]!=-1)//如果该状态求解过
		return g[x][y][t][way];//直接返回该状态的方案数
	if(x==n&&y==n)
		return 1;
	if(x<n&&!a[x+1][y])
		sum+=dfs(x+1,y,way?t:t+1,1);
	if(y<n&&!a[x][y+1])
		sum+=dfs(x,y+1,way?t+1:t,0);
	g[x][y][t][way]=sum;//标记
	return sum;
}
//主函数见上

```



---

## 作者：Reseamus (赞：14)

在这里提供一种模拟的解法。

### 题意简述

输入 $T$ 组数据。对于每一组数据，输入一个 $n\times n$ 的字符矩阵以及可以转向的次数 $K$。矩阵中有若干障碍和空地，求左上角在 $K$ 次转向内有几条不同的路径走到右下角。

### 题目分析：

分析数据范围，发现 $K\leq 3$。由于 $K$ 只有 $K=1$，$K=2$，$K=3$ 三个取值，可以分别枚举 $K=1$，$K=2$，$K=3$ 的情况。

当 $K=1$ 时，可以改变方向 $1$ 次。即只能走矩阵边缘两条路径。如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ymj3sgqk.png)

所以，只需遍历这两条路径，分别统计有无障碍即可。

#### 代码：
```cpp
if(k==1)
{
        bool flag_1=false,flag_2=false;//第一条和第二条路径有无障碍的标记
        for(int i=1;i<=n;i++)
            if(a[1][i]=='H')
                flag_1=true;//统计第一条路径
        for(int i=1;i<=n;i++)
            if(a[i][1]=='H')
                flag_2=true;//统计第二条路径
        for(int i=1;i<=n;i++)
            if(a[i][n]=='H')
                flag_1=true;//统计第一条路径
        for(int i=1;i<=n;i++)
            if(a[n][i]=='H')
                flag_2=true;//统计第二条路径
        ans=!flag_1+!flag_2;
        //由于只需统计有无障碍，所以重复统计并无影响
}
```

当 $K=2$ 时，可以改变方向两次。即可以在矩阵上面的边和左边的边上任意一点转向，直走到它的对边，再走到终点。如图所示（图中只画出两条路径）：

![](https://cdn.luogu.com.cn/upload/image_hosting/n4ddnjie.png)

分别遍历这 $2n-1$ 条路径，统计可以走到的数量。

#### 代码：
```cpp
if(k==2)
{
    for(int i=1;i<=n;i++)
    {
        bool flag=false;
        for(int j=1;j<=i;j++)
            if(a[1][j]=='H') flag=true;
        for(int j=1;j<=n;j++)
            if(a[j][i]=='H') flag=true;
        for(int j=i;j<=n;j++)
            if(a[n][j]=='H') flag=true;
        ans+=!flag;
    }//统计第一次改变方向在矩阵上面的边的路径
    for(int i=2;i<n;i++)
    {
        bool flag=false;
        for(int j=1;j<=i;j++)
            if(a[j][1]=='H') flag=true;
        for(int j=1;j<=n;j++)
            if(a[i][j]=='H') flag=true;
        for(int j=i;j<=n;j++)
            if(a[j][n]=='H') flag=true;	
        ans+=!flag;			
    }//统计第一次改变方向在矩阵左边的边的路径
}
```

当 $K=3$ 时，可以改变方向三次。即可以在矩阵上面的边和左边的边上任意一点转向，直走到它的对边，再走到终点。同时，在矩阵中心 $(n-1)\times (n-1)$ 的范围内，还可以再转向一次。如图所示（只画出了两条路径）：

![](https://cdn.luogu.com.cn/upload/image_hosting/vlehwbnf.png)

可以发现，路径可以由路径的转折点（即图中紫色三角形所框出的点）唯一确定，只需枚举矩阵中心 $(n-1)\times (n-1)$ 的范围即可。

#### 代码：
```cpp
if(k==3)
{	
    for(int i=2;i<n;i++)
    {
        for(int j=2;j<n;j++)
        {
            bool flag=false;
            for(int k=1;k<=j;k++)
                if(a[1][k]=='H') flag=true;
            for(int k=1;k<=i;k++)
                if(a[k][j]=='H') flag=true;
            for(int k=j;k<=n;k++)
                if(a[i][k]=='H') flag=true;
            for(int k=i;k<=n;k++)
                if(a[k][n]=='H') flag=true;
            ans+=!flag;
        }
    }//从矩阵上方的边折入矩阵中心
    for(int i=2;i<n;i++)
    {
        for(int j=2;j<n;j++)
        {
            bool flag=false;
            for(int k=1;k<=j;k++)
                if(a[k][1]=='H') flag=true;
            for(int k=1;k<=i;k++)
                if(a[j][k]=='H') flag=true;
            for(int k=j;k<=n;k++)
                if(a[k][i]=='H') flag=true;
            for(int k=i;k<=n;k++)
                if(a[n][k]=='H') flag=true;
            ans+=!flag;
        }
    }//从矩阵左边的边折入矩阵中心
}
```
### [Ac代码](https://www.luogu.com.cn/paste/tab6zyw5)

---

## 作者：徐晨轩✅ (赞：8)

一道普普通通的搜索题。

根据题目，本题只有两个方向：向下或向右。

本题还有一个特殊的要求：转弯次数不得大于 $K$，所以 `dfs` 中还要增加两个参数：总转弯次数，上一次的方向（$0$ 为右，$1$ 为下）。开始设定值为 $0,-1$，即总转弯次数为 $0$，方向为 $-1$（即没有前一步）。

在搜索时，如果转弯次数 $\geq K$ 时要及时剪枝，但仅仅只有这一个剪枝是不够的，会 `TLE`。所以还需要剪枝。我的方法是：如果还没有到边界（即 $x \ne N,y \ne N$），并且总转弯次数 $=K$ 时，减掉（因为至少还要在转一次弯才能到终点）。

![](https://cdn.luogu.com.cn/upload/image_hosting/8l80kjt0.png)

（图中蓝色点为搜索道的点，其他颜色的线条为该点到终点的路径，可见都必须要拐一次弯）

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k,ans;
char mtx[52][52];
const int dx[]={0,1};
const int dy[]={1,0};
void dfs(int x,int y,int p,int dir)/*0:D 1:R*/
{
//	cout << "in dfs " << x << " " << y << " " << p << " " << dir << endl;
	if(x==n&&y==n&&p<=k)
	{
		ans++;
		return;
	}
	if(x>n||y>n)return;
	if(p>k)return;
	if(x!=n&&y!=n&&p==k)return;
	for(int i=0;i<2;i++)
	{
		int a=x+dx[i];
		int b=y+dy[i];
		if(mtx[a][b]!='H')
			dfs(a,b,p+(i!=dir&&dir!=-1),i);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
//	freopen("USACO 2021 Dec Bronze C.out","w",stdout);
	cin >> t;
	while(t--)
	{
		ans=0;
		memset(mtx,'#',sizeof mtx);
		cin >> n >> k;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin >> mtx[i][j];
//		cout << "end input" << endl;
		dfs(1,1,0,-1);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：uid_310801 (赞：6)

身边做这道题的，有许多人都是靠搜索卡过去的。这让我这个用 DP 做的人很不爽......

来说一下我的做法吧：

设 $dp[i][j][l][dis]$ 表示从左上角走到第 $i$ 行第 $j$ 列 ，此时已经拐了 $l$ 个弯，目前方向是 $dis$ ($dis=0:$ 当前朝向向右；$dis=1:$ 当前朝向向下)的不同的路线有几种。 

借鉴经典 DP 题目过河卒的思想，设计转移方程如下：

- 从左上到右下遍历 $(i,j)$，表示第 $i$ 行第 $j$ 列的格子:

 如果 $(i,j)$ 是稻草，不能走，则 $dp[i][j][*][*]$都是零；
	
- 否则将 $l$ 从 $0$ 遍历到 $k$：
    
1.从左面的格子走来：$dp[i][j][l][0]+=dp[i][j-1][l][0]$； 

2.从左面的格子走来，且拐了弯：所以在左面的格子那里需要你面朝下方：$dp[i][j][l][0]+=dp[i][j-1][l-1][1]$；

3.从上面的格子走来：$f[i][j][l][1]+=f[i-1][j][l][1]$；

4.从上面的格子走来，且拐了弯：所以在上面的格子那里需要你面朝右方：$dp[i][j][l][1]+=dp[i-1][j][l-1][0]$；

#### 一些特判：

1. 当 $l$ 等于 $0$ 时，$l-1$ 会导致奇怪的溢出，所以需要特判。

2. 由于初始的方向是不确定的，所以初始化时 $dp[1][1][0][0]$ 和 $dp[1][1][0][1]$ 都等于 $1$。

3. $dp[1][2][0][0]=dp[2][1][0][1]=1$。

为什么要加上第3条？因为如果将这两个格子连同其他的格子一起转移时，会分别将 $dp[1][1][0][1]$ 和 $dp[1][1][0][0]$ 转移到 $dp[1][2][1][0]$ 和 $dp[2][1][1][1]$,也就是说，你开始面向右方，但是你决定向下拐走下面那个格子，使用了一次拐弯的机会，导致出现奇怪的错误。当然，在特判时需要判断这两个格子上有没有稻草。

~~p.s 我也不知道上面那段话有没有讲清楚......而且貌似加上第3条后，第2条就没有存在的必要了？~~

最后需要输出的答案便是：

$$\sum^k_{l=0} {dp[n][n][l][0]+dp[n][n][l][1]}$$

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=55;
ll a[N][N],f[N][N][4][2],n,k,ans,t;
char c[N];
ll st(ll x){//start的意思，判断第x行应该从第几列开始
	if(x==1)	return 3;
	if(x==2)	return 2;
	return 1;
}
void init(){
	memset(f,0,sizeof(f));
	memset(a,0,sizeof(a));
	n=k=ans=0;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		init();
		scanf("%lld %lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%s",c);
			for(int j=0;j<n;j++){
				if(c[j]=='.')	a[i][j+1]=0;
				else a[i][j+1]=1;
			}
		}
		f[1][1][0][0]=f[1][1][0][1]=1;//没错，这一行应该可以删掉（吧
		if(a[1][2]==0){
			f[1][2][0][0]=1;
		} 
		if(a[2][1]==0){
			f[2][1][0][1]=1;
		}
		for(int i=1;i<=n;i++){
			for(int j=st(i);j<=n;j++){
				if(a[i][j]==1)	continue;
				f[i][j][0][0]+=f[i][j-1][0][0];
				f[i][j][0][1]+=f[i-1][j][0][1];
				for(int l=1;l<=3;l++){
					f[i][j][l][0]+=f[i][j-1][l][0];
					f[i][j][l][1]+=f[i-1][j][l][1];
					f[i][j][l][0]+=f[i][j-1][l-1][1];
					f[i][j][l][1]+=f[i-1][j][l-1][0];
				}
			}
		}
		for(int i=0;i<=k;i++){//貌似从1开始遍历也可以？不过没关系啦
			ans+=f[n][n][i][0]+f[n][n][i][1];
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

本算法时间复杂度为 $O(Tn^2k)$，暴打爆搜！

---

## 作者：幸存者 (赞：5)

## 思路
一看到这道题，就想到了 dfs 的做法。

定义一个变量 $cnt$ 计数，直接枚举每一步向哪个方向走，如果都走不了就返回即可。

注意：这里需要使用剪枝，如果已经达到了 $k$ 次，并且不在最后一行或最后一列，直接返回即可。
## AC Code
```cpp
#include <iostream>
using namespace std;
int n, k, cnt = 0;
bool a[60][60];
void dfs(int x, int y, int w, int s)
{
	if (s > k) return;
	if (s == k && x != n && y != n) return;
	if (x == n && y == n)
	{
		cnt++;
		return;
	}
	if (!a[x + 1][y] && !a[x][y + 1]) return;
	if (x == 1 && y == 1)
	{
		if (a[x + 1][y]) dfs(x + 1, y, 1, s);
		if (a[x][y + 1]) dfs(x, y + 1, 0, s);
	}
	else
	{
		if (a[x + 1][y])
		{
			if (w == 1) dfs(x + 1, y, 1, s);
			else dfs(x + 1, y, 1, s + 1);
		}
		if (a[x][y + 1])
		{
			if (w == 0) dfs(x, y + 1, 0, s);
			else dfs(x, y + 1, 0, s + 1);
		}
	}
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cnt = 0;
        cin >> n >> k;
        for (int j = 1; j <= n; j++) for (int k = 1; k <= n; k++)
        {
            char c;
            cin >> c;
            if (c == '.') a[j][k] = 1;
            else a[j][k] = 0;
        }
        dfs(1, 1, 1, 0);
        cout << cnt << endl;
    }
    return 0;
}
```

---

## 作者：Jorisy (赞：2)

考场上唯一会的题目。

---

显然是 dfs 爆搜。  
准备四个参数：行、列、可转向次数、当前方向，然后分四种情况：
- 向右，改变方向
- 向右，不改变方向
- 向下，改变方向
- 向下，不改变方向

一个一个做即可。  
![](https://cdn.luogu.com.cn/upload/image_hosting/bfu2uyqt.png)  
然而不知怎的（大概 USACO 评测机波动）A 了。  
[这是考场 AC 代码](https://www.luogu.com.cn/record/65670044) 结果发现在尼姑 TLE 了。  
于是开始了劲爆卡常。  
好吧其实不止卡常，还有剪枝。

---

如果把一些条件（如越界、不符合要求的格子、到达终点、改变方向次数等）放在函数开头，则会多递归一次，增加常数，从而导致 TLE。  
因此我们要在递归前判断。  
部分代码：
```cpp
void dfs(int x,int y,int k,int fx)
{
	if(fx==2)//两种情况（向下、向右）
	{
		if(x+1<=n&&!a[x+1][y])//不改变方向
		{
			if(x+1==n&&y==n) ++ans;//到达终点，下同
			else dfs(x+1,y,k,2);
		}
		if(y+1<=n&&k&&!a[x][y+1])//改变方向
		{
			if(x==n&&y+1==n) ++ans;
			else dfs(x,y+1,x==1&&y==1?k:k-1,1);//起点的转向不计入 k 内，下同
		}
	}
	else
	{
		if(y+1<=n&&!a[x][y+1])//不改变方向
		{
			if(x==n&&y+1==n) ++ans;
			else dfs(x,y+1,k,1);
		}
		if(x+1<=n&&k&&!a[x+1][y])//改变方向
		{
			if(x+1==n&&y==n) ++ans;
			else dfs(x+1,y,x==1&&y==1?k:k-1,2);
		}
	}
}
```
[AC 记录。](https://www.luogu.com.cn/record/65670607)

---

## 作者：gaochunzhen (赞：2)

**~~话说 USACO 上时限不是 2s 吗……~~**

其实这道题用搜索就能过。

~~对，就是最朴素的搜索。~~

在 dfs 时，我们需要四个参数：横坐标、纵坐标、转弯次数、方向。

下面就是代码 **（别滑走，后面还有）**：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int inf = 0x7FFFFFFF;
int q, n, k;
LL ans = 0;
bool a[60][60];
void dfs(int x, int y, int t, bool d) { // d 为真即为向下走
    if (t > k) return;
    if (x > n || y > n || a[x][y]) return; //出界 or 不合法
    if (x == n && y == n) { //搜到终点
        ans++;
        return;
    }
    if (x == 1 && y == 1) { //在 (1,1) 时特判
        dfs(x + 1, y, t, 1);
        dfs(x, y + 1, t, 0);
    } else {
        if (d) {
            dfs(x + 1, y, t, 1);
            dfs(x, y + 1, t + 1, 0);
        } else {
            dfs(x + 1, y, t + 1, 1);
            dfs(x, y + 1, t, 0);
        }
    }
}
int main() {
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &n, &k);
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                char w;
                scanf(" %c", &w);
                if (w == 'H') a[i][j] = true;
            }
        }
        ans = 0;
        dfs(1, 1, 0, 0);
        printf("%lld\n", ans);
    }
    return 0;
}
```

但是直接这样搜是会 T 掉最后一个点的（本机耗时约 5 秒），所以要 ~~放弃~~ 大力剪枝。

可以注意到，如果**转弯次数已经用完**，Bessie 还**没有走到最后一行或最后一列**，那么这就是不合法的，可以直接跳出。

所以需要加上这行代码：

```cpp
if (t == k && x != n && y != n) return;
```

dfs 代码如下（其他都是一样的）：

```cpp
void dfs(int x, int y, int t, bool d) {
    if (t > k) return;
    if (x > n || y > n || a[x][y]) return;
    if (t == k && x != n && y != n) return; //剪枝
    if (x == n && y == n) {
        ans++;
        return;
    }
    if (x == 1 && y == 1) {
        dfs(x + 1, y, t, 1);
        dfs(x, y + 1, t, 0);
    } else {
        if (d) {
            dfs(x + 1, y, t, 1);
            dfs(x, y + 1, t + 1, 0);
        } else {
            dfs(x + 1, y, t + 1, 1);
            dfs(x, y + 1, t, 0);
        }
    }
}
```


---

## 作者：SUNCHAOYI (赞：2)

一道很普通的计数 $\texttt{dp}$。设 $dp_{i,j,k,l}$ 表示在 $(i,j)$ 位置上，还剩下 $k$ 次行走方向改变，当前的方向为 $l$ 时的方案数。因为只能够向下走，则令 $l \in \{0,1\}$ 表示这两种方向。那么显然从起点开始初始化，对于一个草堆的格子，方案数一定为 $0$，对于其它格子，就会有更改方向或不更改方向的两种转移：

```cpp
for (int l = 0;l <= k;++l)
{
		dp[i][j][0][l] += dp[i][j - 1][0][l];
		dp[i][j][1][l] += dp[i - 1][j][1][l];//方向不变
		if (l == k) continue;//次数耗尽
		dp[i][j][0][l] += dp[i][j - 1][1][l + 1];
		dp[i][j][1][l] += dp[i - 1][j][0][l + 1];//更改方向
}
```

最后就是答案的统计，根据状态的含义则有 $\sum_{i = 1}^{K} dp_{n,n,i,0} + dp_{n,n,i,1}$。这样就解决了问题，代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 55;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,k,ans,dp[MAX][MAX][2][5];
char s[MAX][MAX];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();k = read ();
		ans = 0;
		init (dp);
		for (int i = 1;i <= n;++i) scanf ("%s",s[i] + 1);
		if (s[1][2] != 'H') dp[1][2][0][k] = 1;
		if (s[2][1] != 'H') dp[2][1][1][k] = 1;
		for (int i = 1;i <= n;++i)
		{
			for (int j = 1;j <= n;++j)
			{
				if (i == 1 && j == 1) continue;
				if (i == 1 && j == 2) continue;
				if (i == 2 && j == 1) continue;
				if (s[i][j] == 'H') continue;
				for (int l = 0;l <= k;++l)
				{
					dp[i][j][0][l] += dp[i][j - 1][0][l];
					dp[i][j][1][l] += dp[i - 1][j][1][l];
					if (l == k) continue;
					dp[i][j][0][l] += dp[i][j - 1][1][l + 1];
					dp[i][j][1][l] += dp[i - 1][j][0][l + 1];
				}
					
			}
		}
		for (int i = 0;i <= k;++i)
			ans += dp[n][n][0][i] + dp[n][n][1][i];
		printf ("%d\n",ans);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：Goodrage (赞：2)

有生之年第一场USACO.

#### 题目大意
从一个方阵的左上角走到右下角，其中有些格子是不能走的，而且至多拐 $k$ 次弯，求路径个数。

#### 思路分析
原本会想到这是推式子，但是别忘了这是青铜组，题目难不到哪里去。再看看数据范围，$2 \leqslant N \leqslant 50$, $1 \leqslant k \leqslant 3$, $1 \leqslant T \leqslant 50$

**果断大爆搜**

我们像正常DFS一样，记录位置并下传，但同时要记录拐多少次弯。

那么如何判断这次是否拐弯呢？我们要用到 $lst$ 记录前进的方向，0为上下，1为左右。如果循环到的 $i$ （决定前进方向）与 $lst$ 相同则不拐弯，否则拐弯。

$lst$ 要赋给一个不同于0或1的初值，作为初始方向（无方向）。

```cpp
void dfs(int row,int col,int turns,int lst)//行，列，拐弯数，方向
{
	if(turns>k) return;//拐弯次数太多了！
	if(row==n&&col==n)//走到终点
	{
		ans++;
		return;
	}
	if(row<=0||col<=0||row>n||col>n) //走出边界return;
	for(register int i=0;i<=1;i++)//访问所有方向
	{
		if(mp[row+dx[i]][col+dy[i]]!='H')//如果可以走
		{
			if(i!=lst&&lst!=114514)//注意！要判一下lst是否为初始值，因为初始时选择方向并不需要拐弯。
				dfs(row+dx[i],col+dy[i],turns+1,i);//拐弯
			else dfs(row+dx[i],col+dy[i],turns,i);//不拐弯
		}
	}
}
```
#### 整个代码1
```cpp
using namespace std;
char mp[60][60];
int dx[2]={0,1};
int dy[2]={1,0};
int n,k;
int ans;
void dfs(int row,int col,int turns,int lst)
{
	if(turns>k) return;
	if(row==n&&col==n)
	{
		ans++;
		return;
	}
	if(row<=0||col<=0||row>n||col>n) return;
	for(register int i=0;i<=1;i++)
	{
		if(mp[row+dx[i]][col+dy[i]]!='H')
		{
			if(i!=lst&&lst!=114514)
				dfs(row+dx[i],col+dy[i],turns+1,i);
			else dfs(row+dx[i],col+dy[i],turns,i);
		}
	}
}
int main()
{
	int T;
	scanf("%d",&T);
	for(register int asdf=1;asdf<=T;asdf++)
	{
		scanf("%d%d",&n,&k);
		ans=0;//多测！要！清！
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=n;j++)
				cin>>mp[i][j];
		}
		dfs(1,1,0,114514);//赋lst初值为114514
		printf("%d\n",ans);
	}
	return 0;
}
```
结果发现，[完美TLE](https://www.luogu.com.cn/record/65675926)

怎么办呢？

#### 剪枝
我们发现，如果我们在第 $x$ 行 $y$ 列，而我们要去的目的地在 $a$ 行 $b$ 列，而且 $x \neq a$, $y \neq b$，那么我们至少要拐一次弯。

所以，假设我们现在在第 $x$ 行 $y$ 列，但不是最后一行也不是最后一列，而且 $k$ 次拐弯已经用完，那么无论如何我们都是回不去的。

所以只要在dfs中加上一句

```cpp
if(turns==k&&(row!=n&&col!=n)) return;
```
就可以卡进时长。

#### 最终代码
```cpp
char mp[60][60];//地图
int dx[2]={0,1};//左右
int dy[2]={1,0};//上下
int n,k;
int ans;
void dfs(int row,int col,int turns,int lst)//行，列，拐弯数，方向
{
	if(turns>k) return;
    if(turns==k&&(row!=n&&col!=n)) return;//剪枝
	if(row==n&&col==n)
	{
		ans++;
		return;
	}
	if(row<=0||col<=0||row>n||col>n) return;
	for(register int i=0;i<=1;i++)
	{
		if(mp[row+dx[i]][col+dy[i]]!='H')
		{
			if(i!=lst&&lst!=114514)
				dfs(row+dx[i],col+dy[i],turns+1,i);
			else dfs(row+dx[i],col+dy[i],turns,i);
		}
	}
}
int main()
{
	int T;
	scanf("%d",&T);
	for(register int asdf=1;asdf<=T;asdf++)
	{
		scanf("%d%d",&n,&k);
		ans=0;//多测！要！清！
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=n;j++)
				cin>>mp[i][j];
		}
		dfs(1,1,0,114514);//赋lst初值为114514
		printf("%d\n",ans);//回车！！
	}
	return goodrage; //回家良怒去啦！
}
```

[AC](https://www.luogu.com.cn/record/65674555)。

---

## 作者：lsj2009 (赞：1)

[更好的阅读体验。](https://www.luogu.com.cn/blog/lvsiji/solution-p7995)

看到这题，我的第一反应就是——BFS！然而打完交上去之后发现……TLE!

不过思考过后，可以剪枝优化：当位于 $(x,y)$ 面向 $w$（0表示右，1表示下），还剩 $k$ 步时，则

- 当 $x \ne n$ 且 $y \ne n$ 并 $k=0$ 时此状态不可以到达终点 $(n,n)$；
- 当 $x \ne n$ 且 $w = 1$ 并 $k=0$ 时此状态不可以到达终点 $(n,n)$；
- 当 $y \ne n$ 且 $w = 0$ 并 $k=0$ 时此状态不可以到达终点 $(n,n)$。

那么，就可以打出代码了，~~最后一个点1.00s闪过~~。

## AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100;
struct node {
	int x,y,w,turn; //x和y表坐标；w表方向；turn表已转弯几次
};
bool Cango[N][N];
int n,k,T;
bool check(int x,int y) { //此点是否可以到达（存在）
	return(x>=1&&x<=n&&y>=1&&y<=n&&Cango[x][y]);
}
bool ReadBit() { //读入字符串函数
	char c;
	for( ; ; ) {
		c=getchar();
		if(c!=' '&&c!='\n'&&c!='\r')
			return c=='.';
	}
}
int Bfs() { //广搜
	queue<node> Q;
	Q.push(node{1,1,-1,0});
	int ans=0;
	while(!Q.empty()) {
		node t=Q.front(); Q.pop();
		if(t.y!=n&&t.x!=n&&k-t.turn==0) continue; //剪枝
		if(t.y!=n&&t.w==1&&k-t.turn==0) continue;
		if(t.x!=n&&t.w==0&&k-t.turn==0) continue;
		if(t.x==n&&t.y==n) { //方案数+1
			++ans; continue;
		}
		if(t.w==-1) { //最初方向任意
			if(check(t.x,t.y+1)) //向右
				Q.push(node{t.x,t.y+1,0,0});
			if(check(t.x+1,t.y)) //向下
				Q.push(node{t.x+1,t.y,1,0});
		}
		if(t.w==0) { //当前向右
			if(check(t.x,t.y+1)) //继续向右
				Q.push(node{t.x,t.y+1,0,t.turn});
			if(check(t.x+1,t.y)&&t.turn!=k) //改变方向向下
				Q.push(node{t.x+1,t.y,1,t.turn+1});
		}
		if(t.w==1) { //当前向下
			if(check(t.x+1,t.y)) //继续向下
				Q.push(node{t.x+1,t.y,1,t.turn});
			if(check(t.x,t.y+1)&&t.turn!=k) //改变方向向右
				Q.push(node{t.x,t.y+1,0,t.turn+1});
		}
	}
	return ans;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				Cango[i][j]=ReadBit();
		printf("%d\n",Bfs());
	}
	return 1;
}


```


---

## 作者：CANTORSORT (赞：1)

关于这一题，我们可以先考虑一下 **广度优先搜索**。

我们定义一个结构体，用它表示 **当前状态下** 的位置、转身次数、方向以及之前走过的路线。

广搜部分可以先套上模板，再慢慢修改。

```
#include<bits/stdc++.h>
#define int long long
#define mkp make_pair
using namespace std;
int t,n,k,ans;
char s[55][55];
struct node
{
	int x,y,cnt;
	pair<int,int>dir;
	string way;
};
void bfs()
{
	unordered_map<string,bool>road;
	queue<node>q;
	q.push((node){1,2,0,mkp(0,1),(string)"R"});
	q.push((node){2,1,0,mkp(1,0),(string)"D"});
	while(!q.empty())
	{
		node tmp=q.front();
		q.pop();
		int x=tmp.x,y=tmp.y,cnt=tmp.cnt,dx=tmp.dir.first,dy=tmp.dir.second;
		string way=tmp.way;
		if(cnt>k||s[x][y]=='H'||way.size()>n*n)
			continue;
		if(x==n&&y==n&&cnt<=k)
		{
			if(!road[way])
				++ans,road[way]=1;
			continue;
		}
		if(x+dx<=n&&y+dy<=n)
			q.push((node){x+dx,y+dy,cnt,mkp(dx,dy),way+(dx?"D":"R")});
		if(x+dy<=n&&y+dx<=n&&cnt<k)
			q.push((node){x+dy,y+dx,cnt+1,mkp(dy,dx),way+(dx?"R":"D")});
	}
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		ans=0;
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%s",s[i]+1);
		if((s[1][2]=='H'&&s[2][1]=='H')||(s[n-1][n]=='H'&&s[n][n-1]=='H'))
		{
			puts("0");
			continue;
		}
		bfs();
		printf("%lld\n",ans);
	}
	return 0;
}
```
能拿下 **50分**。

[提交记录](https://www.luogu.com.cn/record/65724413)

### 显然，我们需要一种更高效的方法。
其实，我们可以使用 **动态规划** 来解决这题。

设 $dp_{x,y,k,d}$ 代表此时在格子 $(x,y)$，已转弯 $k$  次，现在朝着方向 $d$ 的路线数 (当 $d=0$ 时，代表 **向下**，当  $d=1$ 时，代表 **向右**)。

于是，我们可以从 **左边的格子** 和 **上面的格子** 转移到 **当前格子**，转移时需要考虑 **是否转弯**。

时间复杂度为 $O(T\times n^2\times k)$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,dp[55][55][4][2];
char s[55][55];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		int ans=0;
		memset(dp,0,sizeof dp);
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%s",s[i]+1);
		dp[1][1][0][0]=dp[1][1][0][1]=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(s[i][j]=='.')
				{
					for(int cnt=0;cnt<=k;cnt++)
					{
						dp[i][j][cnt][0]+=dp[i-1][j][cnt][0];
						if(cnt)
							dp[i][j][cnt][0]+=dp[i][j-1][cnt-1][1];
						dp[i][j][cnt][1]+=dp[i][j-1][cnt][1];
						if(cnt)
							dp[i][j][cnt][1]+=dp[i-1][j][cnt-1][0];
					}
				}
			}
		}
		for(int cnt=0;cnt<=k;cnt++)
			ans+=dp[n-1][n][cnt][0]+dp[n][n-1][cnt][1];
		printf("%lld\n",ans);
	}
	return 0;
}
```
[提交记录](https://www.luogu.com.cn/record/65725068)

---

## 作者：Ginger_he (赞：1)

# 题目描述
在一个 $n\times n$ 的方阵上，从 $(1,1)$ 走到 $(n,n)$，每步只能往右或往下走，且转弯次数不能超过 $k$，求总方案数。
# 题解
记忆化搜索模板题。（听说有人用爆搜过了%%%）  
$f(x,y,l,t)$ 记录走到 $(x,y)$，上一步方向为 $l$，转了 $t$ 次弯的方案数。在实现过程中，我用 $l=1$ 表示向右走，$l=2$ 表示向下走。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,f[55][55][5][5];
int dx[]={0,1},dy[]={1,0};
char s[55][55];
int dfs(int x,int y,int l,int t)
{
	if(t>k)
		return 0;
	if(x==n&&y==n)
		return 1;
	if(f[x][y][l][t])
		return f[x][y][l][t];
	int res=0;
	for(int i=0;i<2;i++)
	{
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(nx>0&&nx<=n&&ny>0&&ny<=n&&s[nx][ny]!='H')
		{
			int tmp=dx[i]-dy[i];
			tmp=tmp>0?1:2;
			if(!l) res+=dfs(nx,ny,tmp,t);//特判第一步
			else
			{
				if(tmp==l) res+=dfs(nx,ny,l,t);//方向一致
				else res+=dfs(nx,ny,tmp,t+1);//方向不一致
			}
		}
	}
	return f[x][y][l][t]=res;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		memset(f,0,sizeof(f));//别忘了初始化
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%s",s[i]+1);
		printf("%d\n",dfs(1,1,0,0));
	}
	return 0;
}
```
附上[广搜超时代码](https://www.luogu.com.cn/paste/4ng36kq8)

---

## 作者：Eason_AC (赞：1)

[Advertisement](https://www.cnblogs.com/Eason-AC/p/15718313.html)

## Content
$T$ 组询问，每组询问给定一个大小为 $n\times n$ 的地图，仅包含空地（用 `.` 表示）和障碍（用 `H` 表示），求在转弯不超过 $k$ 次的情况下从 $(1,1)$ 到 $(n,n)$ 有多少种路线。

**数据范围：$2\leqslant n\leqslant 50$，$1\leqslant k\leqslant 3$。**
## Solution
你想着通过暴力 dfs 过这道题目，然而你发现最终 T 了两个点。然后你就想着用 dp 来解决了。

我们设 $dp_{x,y,i,j}$ 表示从 $(1,1)$ 到 $(x,y)$，$i=0/1/2$ 分别表示朝向为下/右/移动开始，转弯了 $j$ 次的路线数。另令 $dx_0=1$，$dx_1=0$，$dy_0=0$，$dy_1=1$ 方便后面的转移。然后分两种情况讨论：

- 不转弯，则 $dp_{x+dx_i,y+dy_i,i,j}\leftarrow dp_{x+dx_i,y+dy_i,i,j}+dp_{x,y,i,j}$，特别地，如果 $x=1,y=1$，不要忘记加上 $dp_{1,1,2,0}$。
- 转弯，只能够在 $(x,y)\neq(1,1)$ 时进行，此时 $dp_{x+dx_i,y+dy_i,i,j+1}\leftarrow dp_{x+dx_i,y+dy_i,i,j+1}+dp_{x,y,1-i,j}$。

初始化为 $dp_{1,1,2,0}=1$，答案即为 $\sum\limits_{i=0}^1\sum\limits_{j=1}^k dp_{n,n,i,j}$。
## Code
赛时代码。
```cpp
namespace Solution {
	const int dx[2] = {1, 0};
	const int dy[2] = {0, 1};
	const int N = 57;
	int n, k, ans, dp[N][N][3][7];
	char a[N][N];
	
	iv Main() {
		MT {
			read(n, k), memset(dp, 0, sizeof(dp)), ans = 0;
			F(int, i, 1, n) scanf("%s", a[i] + 1);
			dp[1][1][2][0] = 1;
			F(int, i, 1, n) F(int, j, 1, n) if(a[i][j] != 'H') F(int, l, 0, 1) {
				int x = i + dx[l], y = j + dy[l];
				if(x < 1 || x > n || y < 1 || y > n || a[x][y] == 'H') continue;
				F(int, t, 0, k) {
					dp[x][y][l][t] += dp[i][j][l][t];
					if(i == 1 && j == 1 && t == 0) dp[x][y][l][t] += dp[1][1][2][0];
				}
				if(i != 1 || j != 1) F(int, t, 0, k - 1) dp[x][y][l][t + 1] += dp[i][j][1 - l][t];
			}
			int ans = 0;
			F(int, i, 0, 1) F(int, j, 1, k) ans += dp[n][n][i][j];
			println(ans);
		}
		return;
	}
}
```

---

## 作者：tzyt (赞：1)

update： 2022/4/17 增加了博客地址以及题目链接

[博客](https://ttzytt.com/2021/12/P7995/)中观看体验更佳

[题目链接](https://www.luogu.com.cn/problem/P7995)

# 1：题意
给定一个 $N \times N$ 的区域，区域中的每个点由 0 或 1 组成，1 类点不能走 0 类点可以走。问你从左上角走到右下角，并且最多转向 $K$ 次有多少种走法。
# 2：分析
看到在格子图中问有多少走法的题目，可以比较容易的想到使用 dp 算法解决，具体做法参考 [P1002过河卒](https://www.luogu.com.cn/problem/P1002)，但是本题的难点以及本题解的重点在于如何处理对于转向次数的限制。
![](https://cdn.luogu.com.cn/upload/image_hosting/wv4kqqh6.png)
根据上图，我们可以看到，路径是否包含转向不仅跟从哪个点转移来有关，还和转移来的那个点是从哪个点转移来的有关（从左边或是从右边）。具体的判断规则如下，可以对照着图来理解：

1. 如果当前点是从上面的点 `map[i - 1][j]` 转移来的，并且上面那个点是从他的左边转移来的，那么会发生一次转移。（图中当前点上方的蓝色虚线）
2. 如果当前点是从左边的点 `map[i][j - 1]` 转移来的，并且左边那个点是从他的上方转移来的，那么会发生一次转移。（图中当前点左方的蓝色虚线）
3. 其他所有情况不会发生转向

我们让 `dp[i][j][k][t]` 表示走到 $(i,j)$ ，花费了 $k$ 次转向，并且是从左边 (0) ，或是上面 (1) 的格子转移来的。 

有了以上的判断规则，我们可以写出 dp 的转移方程。

发生转向的情况:
```cpp
dp[i][j][k][0] += dp[i][j - 1][k - 1][1];
dp[i][j][k][1] += dp[i - 1][j][k - 1][0];
```
不发生转向的情况：
```cpp
dp[i][j][k][0] += dp[i][j - 1][k][0];
dp[i][j][k][1] += dp[i - 1][j][k][1];
```
其中，我们需要注意如果一个点如果是从 $(1,1)$ ，也就是起点转移过来的话，是不可能发生转向的。并且如果循环中的 $k=0$ 的话也是不可能发生转向的（$k$ 代表转向次数）。所以我们还需要在发生转向时的状态转移方程加入如下的判断语句：

```cpp
if (k != 0 && i != 1 && j != 1)
```

最后，还需要注意一点。因为题目问的是“至多转向 $k$ 次”，所以最后输出时需要把所有符合条件的情况加起来再一起输出。

# 3：程序实现
完整代码及注释如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;
int n, k;
int t, mp[MAXN][MAXN];
int dp[MAXN][MAXN][4][2]; //dp[i j k t]是到i，j，转了k次的方法数量，并且上次是从左/上边的格子转移来的

void calc_dp()
{
    memset(dp, 0, sizeof(dp));
    dp[1][1][0][0] = dp[1][1][0][1] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (mp[i][j])
                for (int k = 0; k <= 3; k++)
                {
                    dp[i][j][k][0] += dp[i][j - 1][k][0];
                    dp[i][j][k][1] += dp[i - 1][j][k][1];
                    if (k != 0 && i != 1 && j != 1)
                    {
                        dp[i][j][k][0] += dp[i][j - 1][k - 1][1];
                        dp[i][j][k][1] += dp[i - 1][j][k - 1][0];
                    }
                }
        }
    }
}
void input()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        char temp[MAXN];
        scanf("%s", temp + 1);
        for (int j = 1; temp[j]; j++)
        {
            if (temp[j] == 'H')
                mp[i][j] = 0;
            else
                mp[i][j] = 1;
        }
    }
}

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        input();
        calc_dp();
        if (k == 3)
            printf("%d\n", dp[n][n][0][0] + dp[n][n][0][1] + dp[n][n][1][0] + dp[n][n][1][1] +
                             dp[n][n][2][0] + dp[n][n][2][1] + dp[n][n][3][0] + dp[n][n][3][1]);
        if (k == 2)
            printf("%d\n", dp[n][n][0][0] + dp[n][n][0][1] + dp[n][n][1][0] + dp[n][n][1][1] +
                             dp[n][n][2][0] + dp[n][n][2][1]);
        if (k == 1)
            printf("%d\n", dp[n][n][0][0] + dp[n][n][0][1] + dp[n][n][1][0] + dp[n][n][1][1]);
    }
    system("pause");
}
```
如果题解有问题或者没看懂的欢迎在评论区和私信中指出。

---

## 作者：ttq012 (赞：0)

这个题是可以使用深度优先搜索通过的。

我们记录当前点的坐标，当前走的步数和当前转了几次弯。

如果当前转弯的次数大于贝希想要走的步数，那么就直接返回。

如果当前贝希走到了终点，那么就将答案自增 $1$。

```cpp
// C++20 + 吸氧O2（不加会TLE）

#include <bits/stdc++.h>
using namespace std;

int n, k;
struct Node
{
    int x, y;
};
long long ans = 0;
Node a[1000010];
char s[55][55];

void dfs(int x, int y, int dep = 1, int qt = 0)
{
    if (x == n && y == n)
    {
        ans ++;
        return ;
    }
    a[dep].x = x;
    a[dep].y = y;
    if (dep == 1)
    {
        if (y + 1 <= n && s[x][y + 1] == '.')
            dfs(x, y + 1, 2, 0);
        if (x + 1 <= n && s[x + 1][y] == '.')
            dfs(x + 1, y, 2, 0);
    }
    else
    {
        if (y + 1 <= n && s[x][y + 1] == '.')
        {
            if (a[dep - 1].x != x && a[dep - 1].y != y + 1 && qt < k)
                dfs(x, y + 1, dep + 1, qt + 1);
            else if (a[dep - 1].x == x || a[dep - 1].y == y + 1)
                dfs(x, y + 1, dep + 1, qt);
        }
        if (x + 1 <= n && s[x + 1][y] == '.')
        {
            if (a[dep - 1].x != x + 1 && a[dep - 1].y != y && qt < k)
                dfs(x + 1, y, dep + 1, qt + 1);
            else if (a[dep - 1].x == x + 1 || a[dep - 1].y == y)
                dfs(x + 1, y, dep + 1, qt);
        }
    }
}

int main()
{
    int T;
    cin >> T;
    while (T --)
    {
        ans = 0;
        scanf ("%d%d", &n, &k);
        for (int i = 1; i <= n; i ++)
            scanf ("%s", s[i] + 1);
        dfs(1, 1);
        printf ("%lld\n", ans);
    }
    return 0;
}

```

---

## 作者：SSqwq_ (赞：0)

# DFS
这道题目出现在USACO的铜组还是有一定的挑战性的。

我们使用的算法是DFS（深度优先搜索）。很明显，遇到干草垛就返回，越界返回，看起来确实挺简单。于是就有了下面的代码。

**需要注意的是，需要记录当前的方向，以便于统计转向次数。**
```cpp
void dfs(int p,int tim,int dir,int x,int y) 
{//p表示第p组询问，tim表示转向的次数，dir是当前方向（0是右，1是下），x和y就是当前坐标 
	if(mp[p][x][y]=='H')return; //干草垛，返回 
	if(x>n[p]||y>n[p])return;//越界，返回 
	if(x==n[p]&&y==n[p])
	{
		ans++;//到终点 答案+1 这题不能走回头路 所以不用去重 
		return;
	}
	if(dir==1)//如果当前方向向右 
	{
		if(x<n[p]&&mp[p][x+1][y]!='H')dfs(p,tim,1,x+1,y);//继续向右走 
		if(y<n[p]&&tim<k[p]&&mp[p][x][y+1]!='H')dfs(p,tim+1,0,x,y+1);//变向，向下走 
	}
	if(dir==0)//如果当前方向向下 
	{
		if(x<n[p]&&tim<k[p]&&mp[p][x+1][y]!='H')dfs(p,tim+1,1,x+1,y);//继续向下走 
		if(y<n[p]&&mp[p][x][y+1]!='H')dfs(p,tim,0,x,y+1);//变向，向右走 
	}
}
```
之后，我们就发现了问题所在：

**如果从（1，1）点开始进行两种方向的DFS，那么如果（2，1）点是干草垛，则会导致往下的那一组DFS被迫转向，从而会与往右的那一组产生重复。**

对于这个问题，解决的方法也不难想到：
**往右的那一组从（1，2）点开始搜，往下的那一组从（2，1）点开始搜。**
如下是在main函数调用搜索的代码：
```cpp
for(int i=1;i<=t;i++)
{
	ans=0;//将当前询问的答案初始化为0 
	dfs(i,0,0,1,2);//要注意如果向右走应从（1，2）点开始 
	dfs(i,0,1,2,1);//同理向下走应从（2，1）点开始 
	cout<<ans<<endl;
}
```
但是当我们提交的时候，居然发现**不开O2优化会T掉最后一个点！**

这是我不能接受的，所以就开始思考怎么剪枝，而方法也是显而易见的：

**只要当前转向次数已到达最多能转向的次数，则无论如何也不可能到达终点，可以剪掉。**

于是乎我们就在DFS函数中插入了如下代码：
```cpp
if(tim==k[p]&&x!=n[p]&&y!=n[p])return;
```
于是就愉快地AC啦~

## 完整AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n[51],k[51],ans;
char mp[51][51][51];
void dfs(int p,int tim,int dir,int x,int y) //p表示第p组询问，tim表示转向的次数，dir是当前方向（0是右，1是下），x和y就是当前坐标 
{
	if(mp[p][x][y]=='H')return; //干草垛，返回 
	if(x>n[p]||y>n[p])return;//越界，返回 
	if(tim==k[p]&&x!=n[p]&&y!=n[p])return;//这里的剪枝优化：已转向到最多转向次数 却仍不与终点在同一直线上就可以剪掉（AC的关键） 
	if(x==n[p]&&y==n[p])
	{
		ans++;//到终点 答案+1 这题不能走回头路 所以不用去重 
		return;
	}
	if(dir==1)//如果当前方向向右 
	{
		if(x<n[p]&&mp[p][x+1][y]!='H')dfs(p,tim,1,x+1,y);//继续向右走 
		if(y<n[p]&&tim<k[p]&&mp[p][x][y+1]!='H')dfs(p,tim+1,0,x,y+1);//变向，向下走 
	}
	if(dir==0)//如果当前方向向下 
	{
		if(x<n[p]&&tim<k[p]&&mp[p][x+1][y]!='H')dfs(p,tim+1,1,x+1,y);//继续向下走 
		if(y<n[p]&&mp[p][x][y+1]!='H')dfs(p,tim,0,x,y+1);//变向，向右走 
	}
}
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n[i]>>k[i];
		for(int j=1;j<=n[i];j++)
		{
			for(int l=1;l<=n[i];l++)
			{
				cin>>mp[i][j][l];//输入 
			}
		}
	}
	for(int i=1;i<=t;i++)
	{
		ans=0;//将当前询问的答案初始化为0 
		dfs(i,0,0,1,2);//要注意如果向右走应从（1，2）点开始 
		dfs(i,0,1,2,1);//同理向下走应从（2，1）点开始 
		cout<<ans<<endl;
	}
	return 0;
}
```
完美收官！

---

## 作者：feicheng (赞：0)

# P7995 [USACO21DEC] Walking Home B

## Description

给定一个  $n\times n$ 的方格，有障碍，只能向下或向右走，且改变方向的次数不能超过 $k$ 次，求从 $(1,1)\rightarrow(n,n)$ 的方案数。

多测。

**限制：**$2\le n\le 50$，$1\le k\le 3$，$1\le T\le 50$

## Solution

一开始以为爆搜能过，所以冲了一波，结果过不了。。

爆搜代码如下：

```cpp
void dfs(int x, int y, int tim, int past_direction) {
  // cout << x << " " << y << " " << tim << " " << past_direction << '\n';
  if (tim > K) {
    return;
  }
  if (x == n && y == n) {
    ++answer;
    return;
  }
  for (int i = 0; i < 2; ++i) {
    int X = x + dx[i], Y = y + dy[i];
    if (X <= n && Y <= n && M[X][Y] == '.' && !vis[X][Y]) {
      vis[X][Y] = 1;
      dfs(X, Y, tim + (past_direction != i && past_direction != -1), i);
      vis[X][Y] = 0;
    }
  }
}

```

发现过不了，于是考虑 dp，设 $f_{i,j,k,w}$ 表示点 $(i,j)$ 处，已经转了 $k$ 次，下次转的方向为 $w$ 的方案数（令 $w=0$ 为向右）。

有如下 dp 方程
$$
\left\{
\begin{aligned}
f_{i,j,k,0}=f_{i,j-1,k,0}+f_{i,j-1,k-1,1}\\
f_{i,j,k,1}=f_{i-1,j,k,1}+f_{i-1,j,k-1,0}
\end{aligned}
\right.
$$
转移即可。

时间复杂度：$\mathcal O(Tn^2k)$

dp 代码：

```cpp
void Dp() {
  dp[1][1][0][0] = 1;
  dp[1][1][0][1] = 1;
  for (int i = 1; i <= n; ++i) { 
    for (int j = 1; j <= n; ++j) { 
      if (M[i][j] == 'H') {
        continue;
      }
      if (i != 1 && j != 1) {
        for (int k = 1; k <= K; ++k) {
          dp[i][j][k][1] = dp[i - 1][j][k][1] + dp[i - 1][j][k - 1][0];
          dp[i][j][k][0] = dp[i][j - 1][k][0] + dp[i][j - 1][k - 1][1];
        }
        continue;
      }
      for (int k = 0; k <= K; ++k) {
        dp[i][j][k][1] += dp[i - 1][j][k][1];  
        dp[i][j][k][0] += dp[i][j - 1][k][0];
      }
    }
  }
}
```



---

## 作者：AdGats (赞：0)

~~有朋友最近在打USACO，居然看到一个自己会的dp~~
心血来潮决定发份题解
~~刷估值~~

题面一改USACO的花里胡哨，由于只能走右下，没有后效性，很难不发现就是一道加了几个特判的路径数dp（雾

于是我们就需要整整五秒的时间推出换向和不换向的状态转移方程
分别是

```
case 1:
dp[0][l][i][j]+=dp[0][l][i-1][j];				
dp[1][l][i][j]+=dp[1][l][i][j-1];
case 2:
dp[0][l][i][j]+=dp[1][l-1][i-1][j];
dp[1][l][i][j]+=dp[0][l-1][i][j-1];
```

于是就有了如下的代码，具体细节见注释
```
#include<bits/stdc++.h>
using namespace std;
const int K=15,N=55;
int t,n,k,dp[2][K][N][N],ans;//第一维表示到(x,y)的方向,第二维表示换向次数,第三四维表示(x,y)
bool vis[N][N];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		ans=0;
		memset(dp,0,sizeof(dp));
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				char c;
				cin>>c;
				if(c=='.')	vis[i][j]=1;
			}
		if(vis[1][1])	dp[0][0][1][1]=1;
		if(vis[1][2])	dp[1][0][1][2]=1;
		if(vis[2][1])	dp[0][0][2][1]=1;//初始化，循环一定不要从头开始推，否则会乱，因为最开始的状态和过程中不太一样
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int l=0;l<=k;l++){
					if(i==1&&j==1||i==1&&j==2||i==2&&j==1||!vis[i][j])	continue;
					dp[0][l][i][j]+=dp[0][l][i-1][j];
					dp[1][l][i][j]+=dp[1][l][i][j-1];//case 1:不换向
					if(!l)	continue;
					dp[0][l][i][j]+=dp[1][l-1][i-1][j];
					dp[1][l][i][j]+=dp[0][l-1][i][j-1];//case 2:换向
				}
		for(int i=0;i<=k;i++)	ans+=dp[0][i][n][n]+dp[1][i][n][n];//求和
		printf("%d\n",ans);
	}
	return 0;
}
```

由于博主代码风格非常毒瘤，建议新学dp的朋友自己打打

原题面:http://usaco.org/index.php?page=viewproblem2&cpid=1157

---

## 作者：Gaode_Sean (赞：0)

一眼秒了是 dp 。

刚开始做用 $dp_{i,j,k}$ 表示走到第 $i$ 行第 $j$ 列，改变方向 $k$ 次，有多少条不同的路线。

手画一下发现要多加一维记录每一步走的方向。

$dp_{i,j,k,0}=dp_{i-1,j,k-1,1}+dp_{i-1,j,k,0}$

$dp_{i,j,k,1}=dp_{i,j-1,k-1,0}+dp_{i,j-1,k,1}$

注意先初始化 $(1,2)$ 和 $(2,1)$ 两个位置，因为第一步是可以向任意方向走的。

时间复杂度：$O(n^2k)$

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,dp[51][51][4][2],ans;
char ch[51][51];
int main()
{
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>ch[i][j];
				for(int k=0;k<=m;k++) dp[i][j][k][0]=dp[i][j][k][1]=0;
			}
	    }
	    for(int i=1;i<=n;i++){
	    	for(int j=1;j<=n;j++){
	    		if(ch[i][j]=='H') continue;
	    		else if(i==2&&j==1) dp[2][1][0][0]=1;
	    		else if(i==1&&j==2) dp[1][2][0][1]=1;
	    		else{
	    			for(int k=0;k<=m;k++){
	    			    if(i>=2&&j>=2&&k>=1){
	    			    	dp[i][j][k][0]+=dp[i-1][j][k-1][1];
	    			    	dp[i][j][k][1]+=dp[i][j-1][k-1][0];
	    			    }
	    			    if(i>=3) dp[i][j][k][0]+=dp[i-1][j][k][0];
	    			    if(j>=3) dp[i][j][k][1]+=dp[i][j-1][k][1];
	    		    }
	    		}
	    	}
	    }
	    ans=0;
	    for(int i=0;i<=m;i++) ans+=dp[n][n][i][0]+dp[n][n][i][1];
	    cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：heaksicn (赞：0)

## 1 题意
在一个 $n* n$ 矩阵中存在一些障碍物，每次移动只能向下或向右。求从 $(1,1)$ 走到 $(n,n)$ 在最多转向 $k$ 次的情况下的方案数。
## 2 思路
考虑 $dp$。  
设 $dp_{i,j,k,l}$ 表示走到 $(i,j)$，转向 $k$ 次，上一次从 $l$ 方向转移的方案数。（ $l=0$ 表示从上方转移， $l=1$ 表示从左方转移）  
初始化时，对于第 $1$ 行和第 $1$ 列，只要没有遇到障碍物， $dp_{1,i}=dp{i,1}=1$。  
对于一个点 $(i,j)$，有以下几种转移：
1.  $(i,j)$ 是障碍物，此时 $dp_{i,j,k,l}=0$
2. 从上方转移，不转向： $dp_{i,j,k,0}+=dp_{i-1,j,k,0}$
3. 从上方转移，转向： $dp_{i,j,k,0}+=dp_{i-1,j,k-1,1}$
4. 从左方转移，不转向： $dp_{i,j,k,1}+=dp_{i,j-1,k,1}$
5. 从左方转移，转向： $dp_{i,j,k,1}+=dp_{i,j-1,k-1,0}$
最后答案为 $\sum\limits_{i=0}^{k}\sum\limits_{j=0}^1 dp_{n,n,i,j}$。  
时间复杂度 $O(n^2k)$。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[51][51];
int n,k;
int ans;
int dp[51][51][4][3];
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){//输入
				cin>>a[i][j];
			}
		}
		memset(dp,0,sizeof(dp));
		dp[1][1][0][0]=dp[1][1][0][1]=1;
		for(int i=2;i<=n;i++){//初始化第一行
			if(a[1][i]=='H') break; 
			if(a[1][i]!='H')dp[1][i][0][1]=1;
		}
		for(int i=2;i<=n;i++){//初始化第一列
			if(a[i][1]=='H') break;
			if(a[i][1]!='H')dp[i][1][0][0]=1;
		}
		for(int i=2;i<=n;i++){//dp
			for(int j=2;j<=n;j++){
				if(a[i][j]=='H'){//为障碍物
					for(int l=0;l<=k;l++) dp[i][j][l][0]=dp[i][j][l][1]=0;
					continue;
				}
				if(i-1>0){//从上方转移
					for(int l=0;l<k;l++){
						dp[i][j][l][0]+=dp[i-1][j][l][0];//不转向
						dp[i][j][l+1][0]+=dp[i-1][j][l][1]; //转向
					}
					dp[i][j][k][0]+=dp[i-1][j][k][0];
				}
				if(j-1>0){//从左方转移
					for(int l=0;l<k;l++){
						dp[i][j][l][1]+=dp[i][j-1][l][1];//不转向
						dp[i][j][l+1][1]+=dp[i][j-1][l][0]; //转向
					}
					dp[i][j][k][1]+=dp[i][j-1][k][1];
				}
			}
		}
		int ans=0;
		for(int i=0;i<=k;i++){//统计答案
			ans+=dp[n][n][i][0]+dp[n][n][i][1];
		}
		cout<<ans<<endl;//输出
	}
	
	return 0;
}
```


---

