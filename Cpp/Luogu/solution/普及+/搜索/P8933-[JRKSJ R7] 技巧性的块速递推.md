# [JRKSJ R7] 技巧性的块速递推

## 题目背景

充分必要，切比雪夫。

原来还是，不需要了。

## 题目描述

一个 $n\times m$ 的棋盘，对每个格子染上黑白两色之一。

询问有多少种染色方式，使得不存在横、竖、斜连续四个格子中存在至少三个相同颜色的格子，并且不存在横、竖、斜连续三个格子的颜色相同。

若设棋盘的左上角为 $(1,1)$，右下角为 $(n,m)$，则称 $\{(x,y),(x+1,y),(x+2,y)\}$ 为横的连续三个格子，$\{(x,y),(x,y+1),(x,y+2)\}$ 为竖的连续三个格子、$\{(x,y),(x+1,y+1),(x+2,y+2)\}$ 和 $\{(x,y),(x+1,y-1),(x+2,y-2)\}$ 为斜的连续三个格子（以上格子均在棋盘内）。

连续四个格子同理。

## 说明/提示

### 样例解释

样例 $1$：显然任意染色均合法，答案为 $2^4=16$。

样例 $2$：

```
101
110
010
```

这是合法方案之一。

```
111
110
011
```

这是不合法方案之一，因为 $\{(1,1),(1,2),(1,3)\}$、$\{(1,2),(2,2),(3,2)\}$ 和 $\{(1,1),(2,2),(3,3)\}$ 均不满足条件。

### 数据规模

本题采用捆绑测试。
| $\text{Subtask}$ | $n,m\le$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | 
| $1$ | $30$ | $40$ |
| $2$ | $10^9$ | $60$ |

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le n,m\le 10^9$。

## 样例 #1

### 输入

```
1
2 2```

### 输出

```
16```

## 样例 #2

### 输入

```
1
3 3```

### 输出

```
32```

# 题解

## 作者：__ex (赞：9)

用 $1$ 表示黑棋，用 $0$ 表示白棋。

首先，不考虑斜向的情况，如果一个格子在左边或上面存在 $3$ 个已确定的格子，则当前的格子是确定的，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nw7zfa2k.png)

同理，我们只需要确定一个 $3\times 3$ 的区域，其他向外延伸格子都是确定的。

![](https://cdn.luogu.com.cn/upload/image_hosting/0o8h3m5z.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/nb8lqly5.png)

在向外的扩展中，也有可能在斜向上出现问题，导致一些原本的合法解被排除，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jg2lwazt.png)

这个 $3\times 3$ 目前是合法的，但是在向外扩展的时候会变得不合法：

![](https://cdn.luogu.com.cn/upload/image_hosting/h63qy7wv.png)

这样在斜向就出问题了。

于是我们可以得出一个结论：在 $n,m\ge3$ 的棋盘中，最多不超过 $32$ 种解（~~样例给的~~），模数是虚假的

而且，对于棋盘任意一个位置 $a_{i,j}\ (i,j\ge 5)$ 它必定等于左边 $3$ 个位置只有一个的 $a$ ， $a\in\{0,1\}$ 。同理，对于  $a_{i,j-4}$ ，它也等于右边 $3$ 个位置只有一个的 $a$ 。这两个 $a$ 是完全相同的，所以 $a_{i,j}=a_{i,j-4}$ ，棋盘以 $4\times 4$ 为一个周期循环。

而斜面上由于循环，所以我们只用考虑与左上角的 $4\times 4$ 有关系的斜向线段，最多可以到 $(4,4),(5,5),(6,6),(7,7)$ 有问题，那么只用弄出前 $7\times 7$ 的方案数，则 $n,m\ge 7$ 的情况就等于 $7\times 7$ 的方案数了。（一个出问题的斜向线段必定可以包含在一个 $4\times 4$ 的棋盘中，而 $7\times 7$ 枚举了循环中的所有可能出现的 $4\times 4$ 小区域，故使用 $7\times 7$ ）。

对于 $n,m$ 其中一个小于 $7$ 的情况，只用搜出 $1\times 1,\ 1\times 2,\ \cdots,\ 1\times 7,\ 2\times 2\ \cdots,\ 2\times 7\cdots,\ 3\times 3\cdots,\ 3\times 7\cdots,\ 7\times 7$ 特判就好了，因为 $2\times 100$ 之类的方案数肯定等于 $2\times 7$ 的。

下面有一个爆搜预处理代码，来预处理出 $1\times 1$ 到 $7\times 7$ 棋盘的方案数的，结果存在 $o$ 数组里面，剩下的就自己发挥   ~~可以打表~~，可以直接用它预处理。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>inline T read(){
    T a=0;bool s=0;
    char ch=getchar();
    while(ch>'9' || ch<'0'){
        if(ch=='-')s^=1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        a=(a<<3)+(a<<1)+(ch^48);
        ch=getchar();
    }
    return s?-a:a;
}
int n,m,a[10][10],o[10][10],ans=0;
bool check(int x,int y){
	if(x+2<=n && a[x][y]==a[x+1][y] && a[x][y]==a[x+2][y])return 0;
	if(y+2<=m && a[x][y]==a[x][y+1] && a[x][y]==a[x][y+2])return 0;
	if(x+3<=n){
		int t=0;
		for(int i=x;i<=x+3;i++)
			if(a[i][y])t++;
		if(t!=2)return 0;
	}
	if(y+3<=m){
		int t=0;
		for(int i=y;i<=y+3;i++)
			if(a[x][i])t++;
		if(t!=2)return 0;
	}
	if(x+3<=n && y+3<=m){
		int t=0;
		for(int i=0;i<4;i++)
			if(a[x+i][y+i])t++;
		if(t!=2)return 0;
	}
	if(x+3<=n && y-3>=1){
		int t=0;
		for(int i=0;i<4;i++)
			if(a[x+i][y-i])t++;
		if(t!=2)return 0;
	}
	if(x+2<=n && y+2<=m){
		int t=0;
		for(int i=0;i<3;i++)
			if (a[x+i][y+i])t++;
		if(t==0 || t==3)return 0;
	}
	if(x+2<=n && y-2>=1){
		int t=0;
		for(int i=0;i<3;i++)
			if(a[x+i][y-i])t++;
		if(t==0 || t==3)return 0;
	}
	return 1;
}
void dfs(int x,int y){
	if(x>n)x=1,y++;
	if(y>m){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!check(i,j))return ;
		ans++;
		return;
	}
	if(x>=4){//必要的剪枝，不然2^(nm)
		int sum=0;
		for(int i=x-3;i<=x-1;i++)
			sum+=a[i][y];
		if(!sum || sum==3)return;
		if(sum==1)a[x][y]=1;
		else a[x][y]=0;
		dfs(x+1,y);
		return;
	}
	a[x][y]=0;dfs(x+1,y);
	a[x][y]=1;dfs(x+1,y);
}
int main(){
	for(int i=1;i<=7;i++)
		for(int j=i;j<=7;j++){
			n=i,m=j;ans=0;
			dfs(1,1);
			o[i][j]=ans;
		}
	// while(1)getchar();
	return 0;
}
```



---

## 作者：zhangxiao666 (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P8933)

### 题意：

+ 简单来说就是一个涂色游戏。

+ 有一个 $n\times m$ 的棋盘需要涂色。

+ 每格只能涂黑色或白色两种颜色。

+ 横、竖、斜连续 $3$ 格颜色不能相同。

+ 横、竖、斜连续 $4$ 格颜色不能有 $3$ 个相同颜色，即只能是 $2$ 个黑和 $2$ 个白。
 
+ 最后让你统计出所有符合条件的涂色方式的方案数，并对于 $998244353$ 取模。

### 思路：
+ 因为连续四个格子一定是 $2$ 黑 $2$ 白，所以如果确定了 $(i,j)$ 点任意方向上与其连续的三个点的颜色，就可以推出 $(i,j)$（即确定的三个中较少的那种颜色）。例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/qi8dbj90.png)

上图中第一行，由于前三个格子已经确定，要想符合条件，第四个只能是较少的黑色。

竖和斜也是同理，~~图有点丑，就不放了~~。
 
+ 利用上一个条件我们还可以知道一件事，$(i-4,j)$ 格点与 $(i,j)$ 格点的颜色一定相同。因为根据三个连续格点的颜色就能确定与其相邻的第四个点的颜色，由于这两个点中间三个点是一定的，所以确定的第四个点的颜色也是一定的，所以这两个点的颜色一定一样的。因此这个棋盘其实是由一个 $4\times4$ 的小棋盘循环构成的。

+ 利用上面的条件就可以扩展出整个棋盘，不过在斜方向上可能会出问题，我们知道，所有斜行出问题的情况最多只会到 $7\times7$ 的范围，因此当 $n$ 或者 $m$ 超过 $7$ 时，可以转化为 $7$。例如：$n=5$，$m=20$ 的情况就相当于 $n=5$，$m=7$ 的情况。
 
+ 利用这几个条件就可以开始搜索了：

1. 搜索的简单框架还是很好想的：每次搜一个点，枚举是黑是白，然后接着搜下一个点，当整个棋盘搜索完之后，再去 check 一下，符合的话方案数就加 $1$。

1. 接下来还要加一个剪枝：因为上面推出的第二个条件，所以当一个点的横坐标 $\geq4$ 时（即存在 $(i-3,j)$），就可以直接根据 $(i-3,j)$ 点一直到 $(i,j)$ 点间的点求出 $(i,j)$ 点的颜色，没必要再枚举。

1. 不过不能问一次搜一次，因为 $T\leq10^5$，会时超。这时可以先预处理出 $7\times7$ 范围所有大小的方阵答案，询问时直接输出，就不会时超了。

### 代码：
请勿抄袭。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;//矩阵的长宽，方案数 
int a[10][10];//矩阵，1表示黑，0表示白 
int p[10][10];//预处理数组，记录答案 
inline bool check()//判断当前填法是否合法 
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i+2<=n)//横向3个颜色不能一样 
			{
				if(a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j]) return 0;
			}
			if(j+2<=m)//竖向3个颜色不能一样  
			{
				if(a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2]) return 0;
			}
			if(i+2<=n&&j+2<=m)//右下斜线向3个颜色不能一样 
			{
				if(a[i][j]==a[i+1][j+1]&&a[i][j]==a[i+2][j+2]) return 0;
			}
			if(i-2>=1&&j+2<=m)//右上斜线向3个颜色不能一样  
			{
				if(a[i][j]==a[i-1][j+1]&&a[i][j]==a[i-2][j+2]) return 0;
			}
			/*上面四个条件之所以不判断前面的方向，是因为在前面的循环已经判断过了，向后判断即可*/
			if(i+3<=n)//横向4个不能有3个一样 
			{
				int sum1=0,sum2=0;//黑与白的个数 
				for(int k=i;k<=i+3;k++)
				{
					if(a[k][j]) sum1++;
					else sum2++;
				} 
				if(sum1>=3||sum2>=3) return 0; 
			}
			if(j+3<=m)//同上 
			{
				int sum1=0,sum2=0;
				for(int k=j;k<=j+3;k++)
				{
					if(a[i][k]) sum1++;
					else sum2++;
				} 
				if(sum1>=3||sum2>=3) return 0; 
			}
			if(i+3<=n&&j+3<=m)
			{
				int sum1=0,sum2=0;
				for(int k=0;k<=3;k++)
				{
					if(a[i+k][j+k]) sum1++;
					else sum2++;
				} 
				if(sum1>=3||sum2>=3) return 0;
			}
			if(i-3>=1&&j+3<=m)
			{
				int sum1=0,sum2=0;
				for(int k=0;k<=3;k++)
				{
					if(a[i-k][j+k]) sum1++;
					else sum2++;
				} 
				if(sum1>=3||sum2>=3) return 0;
			}
		}
	}
	return 1;//前面都没return说明合法 
}
inline void dfs(int x,int y)//搜索，x和y表示当前搜索的点 
{
	if(y>m) y=1,x++;//搜完一行则换行 
	if(x>n)//说明全搜完了 
	{
		if(check()) ans++;//合法则方案数加1 
		return;
	}
	if(y>=4)//剪枝，≥4则可以直接确定 
	{
		int sum1=0,sum2=0;
		for(int i=y-3;i<=y-1;i++)//统计颜色 
		{
			if(a[x][i]) sum1++;
			else sum2++;
		}
		if(!sum1||!sum2) return;//如果不合法，则没有搜的必要，直接return 
		if(sum1==1) a[x][y]=1;
		if(sum2==1) a[x][y]=0;
		//取少的作为当前点的颜色 
		dfs(x,y+1);//继续搜索 
		return;
	}
	a[x][y]=1;dfs(x,y+1);
	//涂黑 
	a[x][y]=0;dfs(x,y+1);
	//涂白 
}
int main()
{
	for(int i=1;i<=7;i++)
	{
		for(int j=1;j<=7;j++)
		{
			n=i,m=j;
			ans=0;
			dfs(1,1);
			p[i][j]=ans%998244353;
		}
	}//预处理 
	int T;
	cin>>T;
	while(T--)//询问 
	{
		scanf("%d%d",&n,&m);
		if(n>7) n=7;
		if(m>7) m=7;
		//>7 时可以转化为7的情况 
		printf("%d\n",p[n][m]);
	}
	return 0;
} 
```

写题解不易，点个赞呗。

---

## 作者：critnos (赞：7)

注意到 $n=m=4$ 的时候只有 $10$ 种方案。对于下面这两种对称的方案，是没有办法成为更大的棋盘的子矩形的：

```
1010
0011
1100
0101

0101
1100
0011
1010
```

对于其他的 $8$ 种方案，容易发现可以进行归纳。以一种矩形加一行为例：

```
1100
0011
1100
0011
abcd
```

显然 $a=b=1$，$c=d=0$，原因是上面的跳三。

对于这些方案都只有唯一的拓展方式。所以 $\forall n,m\ge 4\land (n,m)\neq (4,4)$，答案为 $8$。

不妨设 $n\le m$，那么 $n\ge 4$ 的情形已经解决了。

考虑 $n=3$，当 $m=4$ 时，有 $20$ 种方案，其中 $4$ 种无法拓展。对于其他的，只有唯一拓展方式。所以 $n=3,m\ge 5$ 时，均只有 $16$ 种方案。

考虑 $n=1$ 和 $n=2$，都是类似的。

所以预处理 $n,m$ 小的情况即可。

---

## 作者：WER_very_fox (赞：2)

## P8933 [JRKSJ R7] 技巧性的块速递推
仔细观察条件，发现任意连续 $4$ 个格子都必须为 $2$ 个黑格，$2$ 个白格。  
也就意味着当行数（或列数）大于等于 $5$ 时，有：  
- 第 $i$ 行 $j$ 列与第 $i+4$ 行 $j$ 列颜色相同
- 第 $i$ 行 $j$ 列与第 $i$ 行 $j+4$ 列颜色相同

具体证明：  
取连续 $4$ 格 $(i,j),(i+1,j),(i+2,j),(i+3,j)$，根据条件这 $4$ 格为 $2$ 黑格 $2$ 白格，而看 $(i+1,j),(i+2,j),(i+3,j),(i+4,j)$ 这 $4$ 格，也为 $2$ 黑格 $2$ 白格。  
因此推出 $(i,j)$ 与 $(i+4,j)$ 颜色相同。第 $2$ 个结论同理。  
所以当询问的 $m$ 或 $n$ 大于等于5时，染色种数可以由 $m=5$ 或 $n=5$ 得出，只需打 $m,n\leq5$ 的表即可。（为防止出错，代码中打表范围为 $n,m\leq6$。）  
接下来用 dfs 深搜即可。

打表代码见下：
```cpp
#include<cstdio>
using namespace std;
int m,n,a[7][7],sum;
bool pd(int x,int y)
{
	if(x>=3&&a[x][y]==a[x-1][y]&&a[x][y]==a[x-2][y])
		return 0;
	if(y>=3&&a[x][y]==a[x][y-1]&&a[x][y]==a[x][y-2])
		return 0;
	//等于6的原因是2个白格2个黑格 
	if(x>=4&&a[x][y]+a[x-1][y]+a[x-2][y]+a[x-3][y]!=6)
		return 0;
	if(y>=4&&a[x][y]+a[x][y-1]+a[x][y-2]+a[x][y-3]!=6)
		return 0;
	if(x>=3&&y>=3&&a[x][y]==a[x-1][y-1]&&a[x][y]==a[x-2][y-2])
		return 0;
	if(x>=3&&m-y>=2&&a[x][y]==a[x-1][y+1]&&a[x][y]==a[x-2][y+2])
		return 0;
	if(x>=4&&y>=4&&a[x][y]+a[x-1][y-1]+a[x-2][y-2]+a[x-3][y-3]!=6)
		return 0;
	if(x>=4&&m-y>=3&&a[x][y]+a[x-1][y+1]+a[x-2][y+2]+a[x-3][y+3]!=6)
		return 0;
	return 1;
}
void dfs(int x,int y)
{
	if(x==n&&y==m+1)
	{
		sum++;
		return;
	}
	if(y==m+1) y=1,x++;
	a[x][y]=1;//设白格为1 
	if(pd(x,y)) dfs(x,y+1);
	a[x][y]=2;//设黑格为2 
	if(pd(x,y)) dfs(x,y+1);
	a[x][y]=0;//记得返回初始值 
	return;
}
int main()
{
	int i,j;
	for(n=1;n<=6;n++)
	{
		printf("{");
		for(m=1;m<=6;m++)
		{
			sum=0;
			dfs(1,1);
			printf("%d",sum);
			if(m!=6) printf(",");
		}
		printf("},");
	}
	return 0;
}
```
AC代码：
```cpp
#include<cstdio>
using namespace std;
int T,m,n;
int a[6][6]={{2,4,6,6,6,6},{4,16,36,36,36,36},{6,36,32,20,16,16},{6,36,20,10,8,8},{6,36,16,8,8,8},{6,36,16,8,8,8}};
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		if(n>6) n=6;
		if(m>6) m=6;
		printf("%d\n",a[n-1][m-1]);
	}
	return 0;
}
```

---

