# Fillomino 2

## 题目描述

Fillomino is a classic logic puzzle. (You do not need to know Fillomino in order to solve this problem.) In one classroom in Yunqi town, some volunteers are playing a board game variant of it:

Consider an $ n $ by $ n $ chessboard. Its rows are numbered from $ 1 $ to $ n $ from the top to the bottom. Its columns are numbered from $ 1 $ to $ n $ from the left to the right. A cell on an intersection of $ x $ -th row and $ y $ -th column is denoted $ (x, y) $ . The main diagonal of the chessboard is cells $ (x, x) $ for all $ 1 \le x \le n $ .

A permutation of $ \{1, 2, 3, \dots, n\} $ is written on the main diagonal of the chessboard. There is exactly one number written on each of the cells. The problem is to partition the cells under and on the main diagonal (there are exactly $ 1+2+ \ldots +n $ such cells) into $ n $ connected regions satisfying the following constraints:

1. Every region should be connected. That means that we can move from any cell of a region to any other cell of the same region visiting only cells of the same region and moving from a cell to an adjacent cell.
2. The $ x $ -th region should contain cell on the main diagonal with number $ x $ for all $ 1\le x\le n $ .
3. The number of cells that belong to the $ x $ -th region should be equal to $ x $ for all $ 1\le x\le n $ .
4. Each cell under and on the main diagonal should belong to exactly one region.

## 说明/提示

The solutions to the examples are illustrated in the following pictures: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517C/9c1f0c1849ccf4ce0e7b23176bd91c953e348595.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517C/9e88a2fdc4b038adc182da7d0d66d5d0dcc6a27e.png)

## 样例 #1

### 输入

```
3
2 3 1```

### 输出

```
2
2 3
3 3 1```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
1
2 2
3 3 3
4 4 4 4
5 5 5 5 5```

# 题解

## 作者：Gokix (赞：5)

[CF1517C](https://www.luogu.com.cn/problem/CF1517C)

------------

方法：对于每个连通块，如果左边有空隙就往左延伸，否则向下延伸。按此方法，本题必然有解。、

![](https://cdn.luogu.com.cn/upload/image_hosting/dqqkefg7.png)

------------

正确性证明：

1. 考虑一件事，就是无论怎么填，一定不会出现某个连通块向右填的情况。

	比如你现在填到第 $i$ 个数。右边的数要么填满了格子，要么还有剩余。因为格子数是 $n + (n-1) + \space ··· \space + (n-i+1)$，这正好对应了排列 $p$ 中前 $i$ 大的数。因此格子剩余最少的情况（剩0个）就是 $p_i=n-i+1$，即 $p$ 为降序排列。否则一定会有剩余。故一定没有连通块向右填的。
    
2. 由上得,每个连通块只会向左或向下拐，而每个块都不会影响下一个块。虽然怪多少次未知（如下图的5），但一定会尽可能填满之前留下的空隙。所以最后每个块都可以连续生成，也就是说本题恒有解。

![](https://cdn.luogu.com.cn/upload/image_hosting/9al35n1m.png)

------------

CODE：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long n,a[510][510];
int main(){
	long long i,j,u,v;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i][i];
	}
	for(i=1;i<=n;i++){
		u=i;v=i;
		for(j=1;j<a[i][i];j++){
			if(a[u][v-1]==0 && v-1>=1){
				a[u][v-1]=a[i][i];
				v--;
			}
			else if(a[u+1][v]==0 && u+1<=n){
				a[u+1][v]=a[i][i];
				u++;
			}
			else{
				cout<<-1<<endl;
				return 0;
			}
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=i;j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

------------



---

## 作者：Ratio_Y (赞：4)

## 思路
倒序考虑，在第 $n$ 行一定只能向左扩展。

类似于俄罗斯方块，这里我们被硬性要求不能留空，所以为避免出现一种数将三角形“隔断”，我们应优先在边缘区域放数。

形象一下，我们在能向下扩展时向下走，才能给上面的数“腾更多的空间”，如此便得到了最优决策，复杂度 $\mathcal{O(n^2)}$。

## 实现
```
#include<bits/stdc++.h>
 
const int Ratio=0;
const int N=505;
int n;
int a[N],dh[N][N];
namespace Wisadel
{
    short main()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=n;i>=1;i--)
        {
            dh[i][i]=a[i];
            int sum=1,x=i,y=i;
            while(sum<a[i])
            {
                if(x<n&&!dh[x+1][y]) dh[x+1][y]=a[i],x=x+1,sum++;
                else dh[x][y-1]=a[i],y=y-1,sum++;
            }
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=i;j++)
            printf(j!=i?"%d ":"%d\n",dh[i][j]);
        return Ratio;
    }
}
int main(){return Wisadel::main();}
```


---

完结撒花~

---

## 作者：Macesuted (赞：2)

[点击此处以获得更佳阅读体验](https://www.macesuted.cn/article/cf1517c/)

---

[题目链接](https://www.luogu.com.cn/problem/CF1517C)

# 分析

从左下往右上依次考虑每一条从左上至右下的对角线。

显然在 $y-x+1=v$ 的对角线上只能放置值在 $[v,n]$ 范围内的数字。

同时显然每一条对角线上的数字的相对排列顺序一定与输入的相对排列顺序相同。

按照我们上面考虑的顺序遍历每一条对角线，并动态维护该对角线上的数字序列：当前对角线上的数字序列仅会比上一条访问到的对角线的数字序列多一个数字。将该数字按照输入的相对排列顺序插入到对应位置即可。

如果觉得解释比较抽象可以对着样例，或是自己手造几个输出对着看一看，就能看出上面说的几个规律了。

# 代码

~~代码比解释简洁很多~~

CF 比赛时打的比较急，直接写 sort 了。可以使用插入排序以获得更好的时间复杂度。

```cpp
/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {

// fread

}  // namespace io
using io::getch;
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 505

int a[maxn][maxn], pos[maxn];

vector<int> vec;

inline bool cmp(int a, int b) { return pos[a] < pos[b]; }

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) pos[read<int>()] = i;
    for (register int t = 1; t <= n; t++) {
        vec.push_back(n - t + 1);
        sort(vec.begin(), vec.end(), cmp);
        for (register int i = 0; i < t; i++) a[n - t + i + 1][i + 1] = vec[i];
    }
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= i; j++)
            write(a[i][j]), putch(" \n"[j == i]);
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

## 题面描述

有一个网格。

在$(x,x)$（$x \leq n$）中填有$n$的排列。

请你构造一个网格，使得

1）所有标为$i$的格子联通。

2）有$i$个标为$i$的节点

## 解决方法

贪心小题。

从$(1,1)$点开始遍历至$(n,n)$。

每个点往下或左涂色。

一旦左边是空格子，就涂左边。

否则再往下面涂色。

可以证明，不会出现-1的情况。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int b[1005][1005];
signed main() {
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
	    b[i][i]=a[i];
		int k=a[i]-1,nm=a[i];
		int j=i;
		int i2=i;
		while(k){
		while(k&&j>1&&b[i2][j-1]==0){
			j--;
			k--;
			b[i2][j]=nm;
		}
		while(k&&(b[i2][j-1]!=0||j==1)){
			k--;
			i2++;
			b[i2][j]=nm;
		}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}

	return 0;
}

```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1517/C)
就是构造一个三角形，使其第 $i$ 行最后一个数为给出的 $p_i$，并将其扩展为联通块，使每个连通块**大小等于** $p_i$，三角形必须填满。

## 思路
首先用一个二维数组 $board$ 来保存三角形。

因为是三角形，我们可以先将每个 $p_i$ 放置在末尾，再每次向左或向下扩展。

尝试一种构造思路：尽可能的**向左扩展**，如果无法继续则向下。

可以证明，这种做法可以填满整个三角形。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int p[505],board[505][505] ;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
	}
	for (int i = 1; i <= n; ++i) {
		int x = i, y = i; // 从主对角线开始
		int value = p[i];
		int count = 1; // 已经占据一个单元格
		board[x][y] = value;
		// 向下和向右填充
		while (count < value) {
			if (y > 1 && board[x][y - 1] == 0) {
				y--; // 向左填充
			} else {
				x++; // 向下填充
			}
			board[x][y] = value;
			count++;
		}
	}
	// 输出结果
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			cout << board[i][j] << " ";
		}
		cout << '\n';
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(n^2) $，可以通过本题。

---

## 作者：Charlie_ljk (赞：1)

从后往前处理，能往下铺就往下铺，否则就往左铺，当然反过来也一样，可以证明其一定恰好铺完所有位置且联通。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=510;
template<typename Tp> inline void read(Tp&x)
{
	x=0;register bool z=true;
	register char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
	for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x)
{if(x>9)wt(x/10);putchar((x%10)+'0');}
template<typename Tp> inline void write(Tp x)
{if(x<0)putchar('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar(' ');write(y...);}
int n,a[N],ans[N][N];
void dfs(int pos,int sum,int x,int y)
{
	if(sum==0) return ;
	ans[x][y]=pos;
	if(!ans[x+1][y]&&x+1<=n) dfs(pos,sum-1,x+1,y);
	else dfs(pos,sum-1,x,y-1);
}
signed main()
{
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=n;i>=1;i--) dfs(a[i],a[i],i,i);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
			write(ans[i][j]),putchar(' ');
		puts("");
	}
}
```

---

## 作者：ETHANK (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1517C)

### 思路

如果左边有位置就往左边填充，否则往下填充，不难说明正确性。填充方式可以使用dfs。

时间复杂度：$O(n^2)$

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int p[505],a[505][505],cnt[505];
void dfs(int i,int j,int col){
    //cout<<i<<" "<<j<<" "<<col<<endl;
    if(!a[i][j]){
        cnt[col]++;a[i][j]=col;
    }
    if(!a[i][j-1]&&j>1&&cnt[col]<col)dfs(i,j-1,col);
    else if(cnt[col]<col)dfs(i+1,j,col);
}
int main(){
    int n=read();
    rep(i,1,n){
        a[i][i]=p[i]=read();
        cnt[p[i]]=1;
    }
    rep(i,1,p[1])a[i][1]=p[1];
    rep(i,2,n){
        dfs(i,i,p[i]);
    }
    rep(i,1,n){
        rep(j,1,i)cout<<a[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
```



---

## 作者：Booksnow (赞：0)

# Fillomino

## 题目大意

给定长度为 $n$ $(1\leq n\leq 500)$ 的排列 $p$ ，要求构造一个三角形，满足一下条件：

- 三角形共 $n$ 行，第 $i$ 行有 $i$ 个数，第 $i$ 行最后一个数是 $p_i$ 。

- 接下来构造 $n$ 个连通块。对于第 $x$ $(1\leq x\leq n)$ 个连通块，每个元素、连通块大小都必须等于 $x$ 。

- 三角形每个格子都必须恰好填一个数。

## 分析

### 如何构造

此题显然是一道构造题，具体构造的方法就是**从左往右**遍历 $p$ 数组，挨个构造连通块。此时，对于每个连通块的形成过程，需要满足以下条件：

- **能够向左延伸就向左延伸**。

- **不能往左延伸的就向下延伸即可**。

### 证明

为什么这么构造是对的？

想象我们上述的这个过程，它满足一个性质，在填充的过程中绝不影响右边一列的格子，而且由于我们是从最大的几列一次填充的，所以他是绝对能够填下的。

又因为我们每次能左拐则左拐，则要么目前为止填充的数列刚好就直接被填充完了，要么肯定会留下一行让后面的连通块能够填充以前的空缺。

所以这个题**必然有解**，而按照这个方法也能够构造出合法解。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e2+10;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w*=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int n;
int p[N],ans[N][N];
int main()
{
	n=read();
	for(register int i=1;i<=n;i++) p[i]=read();
	for(register int i=1;i<=n;i++){
		ans[i][i]=p[i];
		int nx=i,ny=i;
		for(register int j=2;j<=p[i];j++){
			if(ny-1>0&&!ans[nx][ny-1]) ny--;
			else nx++;
			ans[nx][ny]=p[i]; 
		}
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=i;j++) printf("%d ",ans[i][j]);
		puts("");
	}
	return 0;
}
```


---

