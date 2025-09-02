# Valera and Tubes

## 题目描述

有一个n×m的矩形网格


定义“管道”如下：


是一些格子组成的序列 序列长度至少为2


序列中任意相邻两个格子必须在网格中也相邻（四联通）


序列中不能出现重复的格子


现在要给出k个管道使得每个格子恰好属于一个管道

## 样例 #1

### 输入

```
3 3 3
```

### 输出

```
3 1 1 1 2 1 3
3 2 1 2 2 2 3
3 3 1 3 2 3 3
```

## 样例 #2

### 输入

```
2 3 1
```

### 输出

```
6 1 1 1 2 1 3 2 3 2 2 2 1
```

# 题解

## 作者：Aw顿顿 (赞：14)

不错的一道构造题，难度不高。

## 题意

对于 $n\times m$ 的矩形网格，需要你给出 $k$ 个管道使得每个格子恰属于一个管道，管道的定义如下：

- 由连续格子组成的长度至少为 $2$ 的序列。

要求输出 $k$ 行，第一个数 $r$ 代表格子数，接下来 $r$ 个二元组 $(x_i,y_i)$ 表示格子坐标。

保证 $2\le n,m\le 300$ 且 $2\le 2k\le n\times m$。

## 解法

由于闲的比较慌，因此写一个比较详细的题解。


有很多种的构造方法，为什么我们偏偏选择蛇形构造？除了方便写代码以外，还因为一些看似可行的构造实际上是有着他们特殊的不方便之处：

![3.png](https://i.loli.net/2021/10/09/HWOj6PiIALNl3fQ.png)

考虑到上图所示的内容，我们可以考虑一种抖机灵的分配方法：前 $k-1$ 个格子全部采取长度为 $2$ 的情况，而最后一个格子则是剩下的所有格子组成的序列。

![2.PNG](https://i.loli.net/2021/10/09/BkERZVgmJy1nej3.png)

因此，我们接下来考虑怎么确定应该要往左还是往右呢？

![4.PNG](https://i.loli.net/2021/10/09/bGMjVmJCkFaYHLI.png)

那么我们进一步思考代码应该如何实现，首先用结构体 $\texttt{struct}$ 存储坐标的想法是显然的，其次考虑换行的实现：

![5.PNG](https://i.loli.net/2021/10/09/fZaPjBSJnx5m4hG.png)
![6.PNG](https://i.loli.net/2021/10/09/splEPt8Zm7zKX23.png)

而如果没有在换行，也可以类似地使用 $y\gets y+1$ 或者 $y\gets y-1$ 来移动到下一格，那么这样的函数就实现完毕了。

接下来，我们考虑应该要怎样在主函数中进行实现。首先读入数据后，先进行一次长度为 $k-1$ 的循环，每一次先输出 $2$ 然后输出一组 $(x,y)$，之后转移到下一个格子再输出一组 $(x,y)$，这样就完成了一个管道的构造。

而完成这个管道构造之后换行，再用同样的步骤实施这样的构造即可。

构造完了这一些长度为 $2$ 的管道，我们就需要实现剩下管道的模拟，而这样的模拟依然依赖我们的函数，通过一个一个输出，一次次挪移到下一个位置以完成任务。而这个过程需要多少的格子呢？

由于总共的格子有 $n\times m$ 个，因此前面的 $k-1$ 个管道就有 $2(k-1)$ 个格子，那么剩下的格子数就是 $n\times m-2(k-1)$。由此我们可以实现出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct grid{int x,y;};
void move(grid &cur){
	if(cur.x%2==1){
		if(cur.y==m)++cur.x;
		else ++cur.y;
	}else{
		if(cur.y==1)++cur.x;
		else --cur.y;
	}
}int main(){
	scanf("%d%d%d",&n,&m,&k);
	grid a=(grid){1,1};
	for(int i=1;i<k;i++){
		printf("2 ");
		printf("%d %d ",a.x,a.y);move(a);
		printf("%d %d\n",a.x,a.y);move(a);
	}printf("%d ",n*m-2*(k-1));
	for(int i=1;i<=n*m-2*(k-1);i++)
		printf("%d %d ",a.x,a.y),move(a);
	return 0;
}
```

其中的 $\texttt{move}$ 函数通过取引用，可以直接修改变量 $a$，这样就实现了一次次的挪动，这份代码可以再 $\small{\texttt{700 ms}}$ 内通过数据。

感谢阅读，不妨给一个赞吧。

---

## 作者：rui_er (赞：7)

**upd(2020.10.5)：修复一个手贱错误。**

题意：一个 $m\times n$ 的网格图，每次连一条线，要求这条线：

- 至少包含两个点。
- 必须连续：也就是说，每一步可以继续向前画，也可以向左或向右转弯 $90\degree$。
- 不与以前画过的线重复。

构造一种包含 $k$ 条线的画法，把整个图覆盖。

---

显然构造题。

一种容易想到的方法是：我们使前 $k-1$ 条线每条经过两个点，最后一条线将剩余所有点连接。为了方便描述，我们以 $5\times 5$ 的网格图为例，对其进行编号：

![](https://cdn.luogu.com.cn/upload/image_hosting/nerfbeur.png)

假设 $k=4$，则四条线段分别经过如下点：

- $\operatorname{Line}1:(1,2)$
- $\operatorname{Line}2:(3,4)$
- $\operatorname{Line}3:(5,6)$
- $\operatorname{Line}4:(7,8,\cdots,25)$

基础思路有了，问题转化为如何根据点的编号求出其坐标。发现对于奇数行，编号正序；偶数行为倒序。我们根据这一特点对编号的行数进行分类，经过一定的数学推导，就可以得到行数和列数了。

```cpp
pair<int, int> calcPos(int x) {
	int div = (x - 1) / n + 1, pos = (x - 1) % n + 1;
	if(div & 1) return make_pair(div, pos);
	return make_pair(div, n-pos+1);
}
```

然后根据上面说过的思路，计算出所有线的情况，输出即可。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
pair<int, int> calcPos(int x) {
	int div = (x - 1) / n + 1, pos = (x - 1) % n + 1;
	if(div & 1) return make_pair(div, pos);
	return make_pair(div, n-pos+1);
}

int main() {
	scanf("%d%d%d", &m, &n, &k);
	for(int i=1;i<k;i++) {
		printf("2 ");
		pair<int, int> _;
		_ = calcPos((i<<1)-1);
		printf("%d %d ", _.first, _.second);
		_ = calcPos(i<<1);
		printf("%d %d\n", _.first, _.second);
	}
	printf("%d ", n*m-((k-1)<<1));
	for(int i=(k<<1)-1;i<=n*m;i++) {
		pair<int, int> _;
		_ = calcPos(i);
		printf("%d %d ", _.first, _.second);
	}
	puts("");
	return 0;
}
```

---

## 作者：pikabi (赞：6)

### 一道简单的构造题

考虑到每次选择的管道要连续，且长度大于等于 2

不妨将前 $k - 1$ 根管道的长度都设为 2，则最后一根管道为 $n * m - 2 * (k - 1)$ 

于是产生了各种各样的构造，如蜗牛壳型，反蜗牛壳型，蛇型之类

我们选择蛇型进行构造

只需要判断当前第 $i$ 行是奇数还是偶数从而对 $y$ 进行加减就好了。同时对 $y$ 到达边界的情况使 $x++$ 即可。

code $-->$

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cctype>
#define ll long long
#define inf 1023456789

using namespace std;

inline int read(){
	int x=0,w=0;char ch=getchar();
	while (!isdigit(ch))w|=ch=='-',ch=getchar();
	while (isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return w?-x:x;
}

int n, m, k, x, y;

int main(){
	n = read(), m = read();
	k = read();
	x = 1, y = 1;
	for(int i = 1; i < k; i++){
		printf("2 ");
		for(int j = 1; j <= 2; j++){
			printf("%d %d ",x, y);
			if(x & 1)
			y++;
			else y--;
			if(y > m) y--, x++;
			if(!y) y++, x++;
		}
		puts("");
	}
	printf("%d ",n * m - 2 * (k - 1));
	while(x != n + 1){
		printf("%d %d ",x, y);
		if(x & 1)
		y++;
		else y--;
		if(y > m) y--, x++;
		if(!y) y++, x++;
	}
}

```

完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：信息向阳花木 (赞：2)

### 题目大意：
一个有 $n \times m$ 个格子的图，求一种包含 $k$ 条线的画法，覆盖整个图。
### 构造方案
显然，有一种明显的构造方案：让前 $k-1$ 条线每次经过两个点，最后一条线链接剩下 $n \times m - 2 \times(k-1)$个点（总共有 $n \times m$ 个点，前 $k-1$ 条线每条连 $2$ 个，前 $k-1$ 条线总共连 $2 \times (k-1)$ 条线，则第 $k$ 个点连 $n \times m - 2 \times(k-1)$ 个点）。

好了，这种方案很可行啊，但怎么输出呢？让我提供一种方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/9mhcaefu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

注意：每次输出的是 $x_i$ 和 $y_i$，就是按照管道穿过的顺序输出格子编号，一行一个管道。

---

## 作者：guozhetao (赞：1)

## 题目大意
有一个 $n×m$ 的矩形网格。

定义“管道”如下：

是一些格子组成的序列 序列长度至少为 $2$。

序列中任意相邻两个格子必须在网格中也相邻（四联通），

序列中不能出现重复的格子，

现在要给出 $k$ 个管道使得每个格子恰好属于一个管道。
## 思路
首先，这题需要提供一种方法，使每个管道有且不少与 $2$ 个格子，且每个格子必须相连。

这里题目的图片给了我们很多启发：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF441C/3f3cf9e7a269d57bcef72e627d73c51ecbb74bd7.png)

没错，前 $k - 1$ 个管子都只联通 $2$ 个格子，总体呈蛇形。最后一个管子联通剩下所有管子 。
## 代码
（本代码相较于其他题解较为繁琐，建议参考其他题解）
```cpp
#include<bits/stdc++.h> 
using namespace std;
int main() {
	int a,b,c;
	cin>>b>>a>>c;
	int x = 1,y = 1;
	bool k = 1;
	for(int i = 1;i <= c;i++){
		if(i != c){
			cout<<"2 ";
			cout<<y<<" "<<x;
			if(k == 1){
				x++;
			}
			else{
				x--;
			}
			if(x > a){
				x--;
				y++;
				k = 0;
			}
			if(x < 1){
				x++;
				y++;
				k = 1;
			}
			cout<<" "<<y<<" "<<x;
			if(k == 1){
				x++;
			}
			else{
				x--;
			}
			if(x > a){
				x--;
				y++;
				k = 0;
			}
			if(x < 1){
				x++;
				y++;
				k = 1;
			}
		}
		else{
			cout<<(a * b - (c - 1) * 2);
			for(int j = 1;j <= a * b - (c - 1) * 2;j++){
				cout<<" "<<y<<" "<<x;
				if(k == 1){
					x++;
				}
				else{
					x--;
				}
				if(x > a){
					x--;
					y++;
					k = 0;
				}
				if(x < 1){
					x++;
					y++;
					k = 1;
				}
			}
		}
		cout<<endl;
	}
} 
```


---

## 作者：qwq___qaq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF441C)

一个构造题，还是比较简单。

首先，因为 $2\le2\times k\le n\times m$，所以一定有解。

贪心地想：前 $k-1$ 个必须取 $2$，这样即使在极限情况（$2\times k=n\times m$）时也有解。

然后我们可以采用一种蛇形的构造，具体方法可参考样例 $2$，我们的操作时这样的：

1. 首先记录有管道的点的总数 $tot$。

因为前 $k-1$ 次都是 $2$，所以 $tot$ 的初值为 $2\times(k-1)$。

2. 输出当前到达的点 $(x,y)$。

因为多到达了一个点，所以 $tot\gets tot+1$。

3. 记录方向 $p$。

$1$ 从左向右，$y\gets y+1$；$0$ 从右向左，$y\gets$。

4. 越界时要处理。

此时返还上一步操作，到达下一行（$x\gets x+1$），并且改变方向（`p^=1`）。

时间复杂度 $O(n\times m)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x=1,y=1,tot;
bool p=1; 
int main(){
	scanf("%d%d%d",&n,&m,&k);		
	for(int i=1;i<k;++i){
		printf("2 %d %d ",x,y);
		if(p){
			++y;
			if(y>m){
				++x;
				y=m;
				p^=1;
			}
		} else{
			--y;
			if(y<1){
				++x;
				y=1;
				p^=1;
			}
		}
		printf("%d %d\n",x,y);
		if(p){
			++y;
			if(y>m){
				++x;
				y=m;
				p^=1;
			}
		} else{
			--y;
			if(y<1){
				++x;
				y=1;
				p^=1;
			}
		}
		tot+=2;
	}
	printf("%d ",n*m-2*(k-1));
	while(tot!=n*m){
		printf("%d %d ",x,y);
		if(p){
			++y;
			if(y>m){
				++x;
				y=m;
				p^=1;
			}
		} else{
			--y;
			if(y<1){
				++x;
				y=1;
				p^=1;
			}
		}
		++tot;
	}
	return 0;
} 
```

---

## 作者：xfrvq (赞：1)

## 满水的构造题

### 思路

假设前$k-1$ 个管道长度均为$2$ ，最后一个长度为$n-(k-1)\times2$

用蛇形图铺设管道，蛇形图如下：（$n=3,m=3$）

![](https://cdn.luogu.com.cn/upload/image_hosting/xbhv2gk0.png)


铺出来的管道如下：（$k=3$）

![](https://cdn.luogu.com.cn/upload/image_hosting/sfh0ko5y.png)

先输出$k-1$ 条长度为$2$ 的管道（用一个函数求得下一个位置）

再输出$n-(k-1)\times2$ ，

最后重复$n-(k-1)\times2$ 次输出当前点的$x,y$ ，并跳转到下一个点

### 代码

唯一要注意的点是下一个位置的计算

定义一个$nxt$ 函数用于计算当前$x,y$ 的下一个位置是哪里

**AC代码**:

```cpp
#include<stdio.h>
int n,m,k,c;
struct point{
	int x,y;
	point(int x,int y) : x(x),y(y){}
}; 
#define pt point
point nxt(point p){
	if(p.y == m && p.x % 2 == 1) ++p.x;
	else if(p.y == 1 && p.x % 2 == 0) ++p.x;
	else if(p.y != m && p.x % 2 == 1) ++p.y;
	else if(p.y != 1 && p.x % 2 == 0) --p.y;
	return p;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	c = n * m;
	point ptr(1,1);
	while(--k){
		printf("2 %d %d %d %d\n",ptr.x,ptr.y,nxt(ptr).x,nxt(ptr).y);
		ptr = nxt(nxt(ptr)),c -= 2;
	}
	printf("%d ",c);
	while(c--) printf("%d %d ",ptr.x,ptr.y),ptr = nxt(ptr);
	return 0;
}
```

---

## 作者：yzh_Error404 (赞：1)

题目一开始没看懂

理解一下就好了

大致的意思：

一个$n×m$的矩阵里有$k$条管道

要求用这$k$条管道占据所有格子

要注意的是管道最短为$2$

了解完题意之后，就可以想一想解决方法了

于是奇葩方法诞生了：

前$k-1$条管道长度都为$2$

第$k$条管道将剩下的所有数都覆盖

##### 按照蛇形来模拟的蒟蒻就是我

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[307],y[307];
int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    if(k>1)//前k-1条长度为2的管道
    {
        int count=0,x,y,flag=0;
        for(register int i=1;i<=n;i++)
        {
            for(register int j=1;j<=m;j++)
            {
                if(count%2==0)printf("2");
                count++;
                if(i&1)printf(" %d %d",i,j);
                else printf(" %d %d",i,m-j+1);
                if(count%2==0)printf("\n");
                if(count==(k-1)*2)
                {
                    x=i,y=j;
                    flag=1;
                    break;
                }
            }
            if(flag)break;
        }
        int a=m*n-count;
        printf("%d",a);
        for(register int i=x;i<=n;i++)
        {
            for(register int j=y+1;j<=m;j++)
            {
                if(i&1)printf(" %d %d",i,j);
                else printf(" %d %d",i,m-j+1);
                y=0;
            }
            y=0;
        }
        printf("\n");
    }
    else//第k条管道将剩下的格子覆盖
    {
        printf("%d",n*m);
        for(register int i=1;i<=n;i++)
            for(register int j=1;j<=m;j++)
                if(i&1)printf(" %d %d",i,j);
                else printf(" %d %d",i,m-j+1);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Zxsoul (赞：0)

> 没有题解，赶紧来水一波

**思路**

不难发现，要想联通，就得走**蛇形**轨迹，我们分类讨论

- 当 $k$ 和 行数相同时，按列数输出
- 当 $k$ 和 列数相同时，按行数输出
- 都不符合是，前 $k-1$ 个长度为 $2$ 蛇形输出，最后一个长度为 $n\times m -2\times(k-1)$,蛇形输出

蛇形输出的代码
```c
if (x1&1) y1++;
else y1--;
if (y1>m) y1--,x1++;
if (!y1) x1++,y1++;
```
**代码**
```c
/*
	先判断 是否和 n,m相同 相同直接输出
	否则就按照蛇形输出，单反不是最后一个，都按长度2算 
*/
#include <bitset>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e7+10;
const int B = 1e6+10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

int n,m,k;
int main()
{
	n=read(),m=read(),k=read();
	if (n==k)
	{
		for (int i=1;i<=n;i++)
		{
			printf("%d ",m);
			for (int j=1;j<=m;j++) printf("%d %d ",i,j);
			puts("");
		}
	}
	else if (m==k)
	{
		for (int i=1;i<=m;i++)
		{
			printf("%d ",n);
			for (int j=1;j<=n;j++) printf("%d %d ",j,i);
		}
		puts("");
	}
	else 
	{
		int x1=1,y1=1;
		for (int i=1;i<k;i++)
		{
			printf("2 ");
			for (int j=1;j<=2;j++)
			{
				printf("%d %d ",x1,y1);
				if (x1&1) y1++;
				else y1--;
				if (y1>m) y1--,x1++;
				if (!y1) x1++,y1++;
			}
			puts("");
		}
		printf("%d ",n*m-2*(k-1));
		while (x1!=n+1)
		{
			printf("%d %d ",x1,y1);
			if (x1&1) y1++;
			else y1--;
			if (y1>m) y1--,x1++;
			if (!y1) y1++,x1++;
		}
	}
} 

```

---

## 作者：BreakPlus (赞：0)

这是一道构造题，比较神奇吧！

--------------------------------------

首先我们来看一下题目中给定的这个条件：$2 \le 2k \le nm$ ,不妨考虑前 $k-1$ 个管道的长度可以全部设置为 $2$ ，剩下的归类为第 $k$ 个管道。

关于顺序，为了四联通，可以考虑蛇形。自己画一个图就会发现蛇形是满足四联通的。

然后就是一个暴力枚举，注意题目中的 $n,m$ 与我们中文题面中的意思是反的。

上代码啦

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
typedef pair<int,int> P;
#define maxn 310
int n,m,k,x=1,y,dy=1; bool vis[maxn][maxn];
int main(){
    scanf("%d%d%d",&m,&n,&k);
    for(register int i=1;i<k;i++){
        printf("2 ");
        y+=dy;
        if(y>n){
            dy=-dy;
            x++; y=n;
        }
        if(y<1){
            dy=-dy;
            x++; y=1;
        }
        printf("%d %d ",x,y);
        vis[x][y]=true;
        y+=dy;
        if(y>n){
            dy=-dy;
            x++; y=n;
        }
        if(y<1){
            dy=-dy;
            x++; y=1;
        }
        printf("%d %d ",x,y);
        vis[x][y]=true;
        puts("");
    }
    printf("%d ",n*m-(k-1)*2);
    for(register int i=1;i<=n*m-(k-1)*2;i++){
        y+=dy;
        if(y>n){
            dy=-dy;
            x++; y=n;
        }
        if(y<1){
            dy=-dy;
            x++; y=1;
        }
        printf("%d %d ",x,y);
    }
    puts("");
    return 0;
}
```

---

