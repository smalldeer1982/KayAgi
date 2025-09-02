# [ABC312E] Tangency of Cuboids

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc312/tasks/abc312_e

$ 3 $ 次元空間内に $ N $ 個の直方体があります。

直方体同士は重なっていません。厳密には、相異なるどの $ 2 $ つの直方体の共通部分の体積も $ 0 $ です。

$ i $ 番目の直方体は、$ 2 $ 点 $ (X_{i,1},Y_{i,1},Z_{i,1}),\ (X_{i,2},Y_{i,2},Z_{i,2}) $ を結ぶ線分を対角線とし、辺は全ていずれかの座標軸に平行です。

各直方体について、他のいくつの直方体と面で接しているか求めてください。  
 厳密には、各 $ i $ に対し、$ 1\leq\ j\ \leq\ N $ かつ $ j\neq\ i $ である $ j $ のうち、$ i $ 番目の直方体の表面と $ j $ 番目の直方体の表面の共通部分の面積が正であるものの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ X_{i,1}\ <\ X_{i,2}\ \leq\ 100 $
- $ 0\ \leq\ Y_{i,1}\ <\ Y_{i,2}\ \leq\ 100 $
- $ 0\ \leq\ Z_{i,1}\ <\ Z_{i,2}\ \leq\ 100 $
- 直方体同士は体積が正の共通部分を持たない
- 入力は全て整数である
 
### Sample Explanation 1

$ 1 $ 番目の直方体と $ 2 $ 番目の直方体は、$ 2 $ 点 $ (0,0,1),(1,1,1) $ を結ぶ線分を対角線とする長方形を共有しています。 $ 1 $ 番目の直方体と $ 3 $ 番目の直方体は、点 $ (1,1,1) $ を共有していますが、面で接してはいません。

## 样例 #1

### 输入

```
4
0 0 0 1 1 1
0 0 1 1 1 2
1 1 1 2 2 2
3 3 3 4 4 4```

### 输出

```
1
1
0
0```

## 样例 #2

### 输入

```
3
0 0 10 10 10 20
3 4 1 15 6 10
0 9 6 1 20 10```

### 输出

```
2
1
1```

## 样例 #3

### 输入

```
8
0 0 0 1 1 1
0 0 1 1 1 2
0 1 0 1 2 1
0 1 1 1 2 2
1 0 0 2 1 1
1 0 1 2 1 2
1 1 0 2 2 1
1 1 1 2 2 2```

### 输出

```
3
3
3
3
3
3
3
3```

# 题解

## 作者：Moyou (赞：20)

## **E - Tangency of Cuboids**

观察到 $M\le 100\Longrightarrow M^3\le 10^6$，考虑每一个单位格子。

由于立方体不相交，所以一个单位格子最多属于一个立方体，枚举每一个单位格子的四周，如果有一个单位格子的四周有单位格子属于不同的立方体，那么这两个立方体有相同的面。

对于格子 $(x, y, z)$，需要枚举的方位有：$(x\pm1,y,z), (x, y\pm1, z), (x, y, z\pm1)$。

看似需要枚举六个方位，实际上 $(x+1, y, z), (x-1,y,z)$ 是等价的，因为对于 $(x-1,y,z)$，它也会枚举到 $(x, y, z)$，就不用再向下看了，所以只需要枚举三个方位即可。

统计的时候可以每个立方体开一个 `std::set`，`std::set` 里面存储所有相邻的立方体，并且使用 `std::set` 的好处之一是可以自动去重，输出时直接输出 `s[i].size()` 即可。

时间复杂度：$O(N + M^3\log N)$。

注意题目中给的是点的坐标，为了转化为格子的坐标，需要考虑边界问题。

```cpp
#include <iostream>
#include <set>
using namespace std;
const int N = 100 + 10, M = 1e5 + 10;

set<int> s[M];
int dx[] = {1, 0, 0}, dy[] = {0, 1, 0}, dz[] = {0, 0, 1}, n, a[N][N][N]; // 等价于六个方向

signed main()
{
    cin >> n;
    for(int y = 1; y <= n; y ++) {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        for(int i = x1 + 1; i <= x2; i ++)    
            for(int j = y1 + 1; j <= y2; j ++)
                for(int k = z1 + 1; k <= z2; k ++)
                    a[i][j][k] = y;
    }
    for(int i = 1; i <= 100; i ++)
        for(int j = 1; j <= 100; j ++)
            for(int k = 1; k <= 100; k ++)
                for(int p = 0; p < 3; p ++)
                    if(a[i][j][k] && a[i + dx[p]][j + dy[p]][k + dz[p]] && a[i][j][k] != a[i + dx[p]][j + dy[p]][k + dz[p]]) // 需要特判有的格子没有被立方体覆盖的情况
                        s[a[i][j][k]].insert(a[i + dx[p]][j + dy[p]][k + dz[p]]),
                        s[a[i + dx[p]][j + dy[p]][k + dz[p]]].insert(a[i][j][k]);
    for(int i = 1; i <= n; i ++)
        cout << s[i].size() << '\n';
    return 0;
}
```


---

## 作者：Genius_Star (赞：4)

### 题意：

有 $N$ 矩形立方体，每一个立方体给出对角线两点的坐标 $(x_1,y_1,z_1),(x_2,y_2,z_2)$，并且其边都与一个坐标轴平行。

保证两两不同立方体之间没有重叠的体积，让我们求对于每个立方体，找到与之共享一个面的其他立方体的数量。

### 思路：

~~刚开始没看懂题意，赛时没切掉……~~

这题 $n$ 的数据很大，如果直接 $O(n^2)$ 暴力的话是肯定会超时的，所以考虑优化。

注意到，虽然 $n$ 的数据很大，但是发现这坐标点都在 $100$ 以内，于是考虑点标记，什么意思？

就是对于第 $i$ 个立方体，在一个三维数组 $a$ 中，将这个立方体所在的所有点都赋值为 $i$，但是我们怎么知道这些范围呢，现在我们知道了对角线两点的坐标 $(x_1,y_1,z_1),(x_2,y_2,z_2)$，怎么求所有 $8$ 个点的坐标呢？

1. 先定义一下变量：
   - $x_{min}$：取 $x_1$ 和 $x_2$ 中较小的值。
   - $x_{max}$：取 $x_1$ 和 $x_2$ 中较大的值。
   - $y_{min}$：取 $y_1$ 和 $y_2$ 中较小的值。
   - $y_{max}$：取 $y_1$ 和 $y_2$ 中较大的值。
   - $z_{min}$：取 $z_1$ 和 $z_2$ 中较小的值。
   - $z_{max}$：取 $z_1$ 和 $z_2$ 中较大的值。
2. 八个顶点的坐标如下：
   - $(x_{min}, y_{min}, z_{min})$
   - $(x_{max}, y_{min}, z_{min})$
   - $(x_{min}, y_{max}, z_{min})$
   - $(x_{max}, y_{max}, z_{min})$
   - $(x_{min}, y_{min}, z_{max})$
   - $(x_{max}, y_{min}, z_{max})$
   - $(x_{min}, y_{max}, z_{max})$
   - $(x_{max}, y_{max}, z_{max})$

~~因为自己想偷懒，就懒的证明了……~~

这样，我们就可以得到立方体的八个顶点的坐标。

自己手推一下，就可以知道，我们将 $a_{x,y,z}$ 标记为 $i+1$（循环从 $0$ 开始），其中 $x_1 \le x < x_2,y_1 \le y < y_2,z_1 \le z < z_2$。

这样，将 $n$ 个立方体都标记进三维数组中了，我们可以逐一遍历每一个点，对于一个点，其上面这个点和后面这个点和右边这个点就是与其相邻的点，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p4j7fmlq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以我们只需要判断 $a_{x+1,y,z},a_{x,y+1,z},a_{x,y,z+1}$ 是否和 $a_{x,y,z}$ 相等即可，如果不相等，那么将两者的计数器累加，这对吗？

不对，因为在后面其他点的遍历中也可能这两者不同，这样就会重复加了。

那我们怎么进行去重呢？其实 ``STL`` 库里面有一个容器 ``set``，这个容器中如果有重复的数字插入，那么只会保留一个。

我们可以使用这个容器来实现去重的功能，如果两者不相同，将这两者所在的立方体的容器都添加一个对面立方体的编号，这样以后重复加的时候，不会多算。

输出答案的时候，输出每一个立方体容器中的元素个数。

时间复杂度：$O(M^3)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=105,M=100100;
inline ll read(){ //快读 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){ //快输 
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll a[N][N][N];
ll n;
set<ll> t[M];
int main(){
	n=read();
	for(int i=0;i<n;i++){
		ll x1,y1,z1,x2,y2,z2;
		x1=read(),y1=read(),z1=read(),x2=read(),y2=read(),z2=read(); 
		for(ll x=x1;x<x2;x++)
		  for(ll y=y1;y<y2;y++)
		    for(ll z=z1;z<z2;z++)
		      a[x][y][z]=i+1;
	}
	for(ll x=0;x<100;x++){
		for(ll y=0;y<100;y++){
		    for(ll z=0;z<100;z++){
			    if(a[x][y][z]){
					if(a[x+1][y][z]&&a[x+1][y][z]!=a[x][y][z]){
						t[a[x][y][z]].insert(a[x+1][y][z]);
						t[a[x+1][y][z]].insert(a[x][y][z]);
					}
					if(a[x][y+1][z]&&a[x][y+1][z]!=a[x][y][z]){
						t[a[x][y][z]].insert(a[x][y+1][z]);
						t[a[x][y+1][z]].insert(a[x][y][z]);
					}
					if(a[x][y][z+1]&&a[x][y][z+1]!=a[x][y][z]){
						t[a[x][y][z]].insert(a[x][y][z+1]);
						t[a[x][y][z+1]].insert(a[x][y][z]);
					}
				}
			}			
		}
	}
	for(int i=1;i<=n;i++){
		write(t[i].size());
		putchar('\n');
	}
	return 0;
}
```



---

## 作者：xrk2006 (赞：0)

# 【题解】[ABC312E] Tangency of Cuboids

[博客园食用效果更佳](https://www.cnblogs.com/xrkforces/p/ABC312E.html)

少见的 at 评分 $2000+$ 的 ABC E 题，非常巧妙的一道题。

特别鸣谢：@[dbxxx](https://www.luogu.com.cn/user/120868) 给我讲解了他的完整思路。

## 题目链接

[ABC312E - Tangency of Cuboids](https://atcoder.jp/contests/abc312/tasks/abc312_e)

## 题意概述

给定三维空间中的 $n$ 个长方体，每个长方体以其一条体对角线的两个端点的坐标形式给出，即对于每一个长方体 $i$，给定其体对角线端点的坐标 $(x_{i,1},y_{i,1},z_{i,1})$ 和 $(x_{i,2},y_{i,2},z_{i,2})$。

要求对于给定的每一个长方体，求出给定的其它长方体中，与其共享一个面的长方体数量。

具体地说，对于每个 $i(1 \le i \le n)$，找到 $1≤j≤n$ 且 $j≠i$ 的 $j$ 的数量，使得第 $i$ 个长方体和第 $j$ 个长方体的表面有一个正面积的交集。

**题目保证每个长方体两两不交，即对于任意两个长方体，它们的交集体积为 $0$。**

## 数据范围

- $1\le n \le 10^5$
- $0 \le x_{i,1}<x_{i,2}\le 100$
- $0 \le y_{i,1}<y_{i,2}\le 100$
- $0 \le z_{i,1}<z_{i,2}\le 100$

## 思路分析

$n$ 的范围很大，但是观察长方体体对角线端点的坐标范围只有 $100$，容易想到最终的时间复杂度应该是 $100^3$ 或者 $100^4$，启示我们要处理**单位小正方体**的信息。

> 注：单位小正方体指的是坐标范围内棱长为 $1$ 的正方体。

可以考虑将题目中所有已知的长方体，都分解成多个单位小正方体处理。即，对于长方体 $i$，我们把这个长方体中包含所有单位小正方体都染色成 $i$。

换句话说，我们定义体对角线端点坐标为 $(i,j,k)$ 和 $(i+1,j+1,k+1)$ 的单位小正方体的坐标为 $(i,j,k)$，$col_{i,j,k}$ 表示坐标为 $(i,j,k)$ 的单位小正方体被染成的颜色。那么对于体对角线端点坐标为 $(x_{t,1},y_{t,1},z_{t,1})$ 和 $(x_{t,2},y_{t,2},z_{t,2})$ 的长方体 $t$，就将所有坐标为 $(i,j,k)$，其中 $x_{t,1}\le i <x_{t,2},y_{t,1} \le j < y_{t,2},z_{t,1} \le k < z_{t,2}$ 的单位小正方体都染成 $t$，即让 $col_{i,j,k}=t$。

> 注意：这里 $i,j,k$ 条件是 $x_{t,1}\le i <x_{t,2},y_{t,1}\le j<y_{t,2},z_{t,1} \le k <z_{t,2}$，而不是 $x_{t,1}\le i \le x_{t,2},y_{t,1}\le j \le y_{t,2},z_{t,1} \le k \le z_{t,2}$。因为当 $i=x_{t,2}$ 或 $j=y_{t,2}$ 或 $k=z_{t,2}$ 时，对应的单位小正方体已经不属于这个长方体内了。所以必须是小于，不能是小于等于。

接下来，我们枚举坐标范围（即 $[0,100)$ 内）的每一个单位小正方体的坐标 $(i,j,k)$，那么如果这个小正方体和它相邻小正方形，即 $(i+1,j,k)$ 或 $(i,j+1,k)$ 或 $(i,j,k+1)$ 颜色不同，则说明它们所在的长方体有公共面。那么这样的方法就可以找到所有的有公共面长方体。

我们考虑对于每一个长方体开一个 set，如果长方体 $i$ 与长方体 $j$ 有公共面。那么就往 $i$ 对应的 set 里扔一个 $j$，同时往 $j$ 对应的 set 里面扔一个 $i$，由于 set 无重复元素，这样顺便也完成了去重。那么最后输出 $1$ 到 $n$ 的每个正方体 $i$ 的 set 的 size 就好了。

>注意：如果题目不保证给定长方体两两不交，就不能这么做了。因为如果有交，同一个单位小正方形就可以同时被染成多种颜色，染色复杂度就变成 $O(100^3 n)$，就不能通过这道题了。

时间复杂度 $O(100^3 \log n)$（set 是 $\log n$ 的复杂度）。

## 代码实现

```cpp
//E
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
#include<set>
using namespace std;
const int maxn=1e5+10;
const int maxx=105;
int X1[maxn],X2[maxn],Y1[maxn],Y2[maxn],Z1[maxn],Z2[maxn];
int col[maxx][maxx][maxx];

set<int>s[maxn];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void work(int xx,int xy,int yx,int yy,int zx,int zy,int t)
{
	for(int i=xx;i<xy;i++)
	{
		for(int j=yx;j<yy;j++)
		{
			for(int k=zx;k<zy;k++)
			{
				col[i][j][k]=t;
			}
		}
	}
}

int main()
{
	int n=read();
	for(int i=1;i<=n;i++)
	{
		X1[i]=read();Y1[i]=read();Z1[i]=read();
		X2[i]=read();Y2[i]=read();Z2[i]=read();
		work(X1[i],X2[i],Y1[i],Y2[i],Z1[i],Z2[i],i);
	}
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
		{
			for(int k=0;k<100;k++)
			{
				if(col[i][j][k]!=col[i+1][j][k])
				{
					if(col[i][j][k]&&col[i+1][j][k])
					{
						s[col[i][j][k]].insert(col[i+1][j][k]);
						s[col[i+1][j][k]].insert(col[i][j][k]);
					}
				}
				if(col[i][j][k]!=col[i][j+1][k])
				{
					if(col[i][j][k]&&col[i][j+1][k])
					{
						s[col[i][j][k]].insert(col[i][j+1][k]);
						s[col[i][j+1][k]].insert(col[i][j][k]);
					}
				}
				if(col[i][j][k]!=col[i][j][k+1])
				{
					if(col[i][j][k]&&col[i][j][k+1])
					{
						s[col[i][j][k]].insert(col[i][j][k+1]);
						s[col[i][j][k+1]].insert(col[i][j][k]);
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<s[i].size()<<'\n';
	return 0;
}
```



---

