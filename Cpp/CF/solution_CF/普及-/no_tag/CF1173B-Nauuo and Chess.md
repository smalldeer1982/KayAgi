# Nauuo and Chess

## 题目描述

Nauuo is a girl who loves playing chess.

One day she invented a game by herself which needs $ n $ chess pieces to play on a $ m\times m $ chessboard. The rows and columns are numbered from $ 1 $ to $ m $ . We denote a cell on the intersection of the $ r $ -th row and $ c $ -th column as $ (r,c) $ .

The game's goal is to place $ n $ chess pieces numbered from $ 1 $ to $ n $ on the chessboard, the $ i $ -th piece lies on $ (r_i,\,c_i) $ , while the following rule is satisfied: for all pairs of pieces $ i $ and $ j $ , $ |r_i-r_j|+|c_i-c_j|\ge|i-j| $ . Here $ |x| $ means the absolute value of $ x $ .

However, Nauuo discovered that sometimes she couldn't find a solution because the chessboard was too small.

She wants to find the smallest chessboard on which she can put $ n $ pieces according to the rules.

She also wonders how to place the pieces on such a chessboard. Can you help her?

## 说明/提示

In the first example, you can't place the two pieces on a $ 1\times1 $ chessboard without breaking the rule. But you can place two pieces on a $ 2\times2 $ chessboard like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1173B/19a9324ad1d9f76a12004b1e06e1a6fc8ea5363a.png)

In the second example, you can't place four pieces on a $ 2\times2 $ chessboard without breaking the rule. For example, if you place the pieces like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1173B/dd0c838eb5fa429a4dd839467d147e6034fac9bb.png)

then $ |r_1-r_3|+|c_1-c_3|=|1-2|+|1-1|=1 $ , $ |1-3|=2 $ , $ 1<2 $ ; and $ |r_1-r_4|+|c_1-c_4|=|1-2|+|1-2|=2 $ , $ |1-4|=3 $ , $ 2<3 $ . It doesn't satisfy the rule.

However, on a $ 3\times3 $ chessboard, you can place four pieces like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1173B/b7f6bf4dffb399263283db89988092d0fdbbac58.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
2
1 1
1 2```

## 样例 #2

### 输入

```
4
```

### 输出

```
3
1 1
1 3
3 1
3 3```

# 题解

## 作者：VenusM1nT (赞：7)

```
我喜欢 2B (chess)。不太难想的构造，但在 div.2 场 有一定的区分作用。
 - By Sooke
```

结论题。

题目的要求是两点的曼哈顿距离大于等于两点的编号差，显然，一个边长为 $m$ 的棋盘，最多可以容纳 $m\times 2-1$ 个棋子，用贪心的思想我们可以把第 $1$ 个棋子和第 $n$ 个棋子分别放到棋盘的左上角和右下角，就可以很容易地得到这个结论。

那么确定了边长之后，就是怎么摆的问题了。这点非常容易，直接沿着边摆过去就行了。

```cpp
#include<bits/stdc++.h>
#define MAXN 1005
#define reg register
#define inl inline
using namespace std;
int n,ans[MAXN][MAXN];
int main()
{
	scanf("%d",&n);
	reg int m=n/2+1;
	printf("%d\n",n/2+1);
	for(reg int i=1;i<=m && i<=n;i++) printf("%d %d\n",1,i);
	for(reg int i=2;i<=n-m+1;i++) printf("%d %d\n",i,m);
	return 0;
}
```

---

## 作者：mulberror (赞：2)

老实说，暴力确实可以过呀。。。qwq  
首先推（xia）导（cai）答案是边长为$n/2+1$的矩阵。  
然后，然后如果实在想不到结论，就一个一个塞就可以了。  
贪心塞进去的一定是正解。     
复杂度是$O(?)$，理论复杂度应该是$O(n^4)$，但是还是过掉了，应该没有跑满，因为是找最小的那一个嘛。。。    
跑得还挺快的貌似。。。  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5; 
int ans, x[N], y[N];
int main() {
	ios::sync_with_stdio(false); 
	int n; cin >> n; ans = n / 2 + 1; 
	x[1] = 1; y[1] = 1; 
	for (int i = 2; i <= n; i ++) {
		bool fg = 0; 
		for (int xx = 1; xx <= ans; xx ++) {
			for (int yy = 1; yy <= ans; yy ++) {
				fg = 1; 
				for (int j = 1; j < i; j ++) {
					if (abs(x[j] - xx) + abs(y[j] - yy) < abs(i - j)) {
						fg = 0; break;
					}
					if (j == i - 1) x[i] = xx, y[i] = yy; 
				}
				if (fg) break;
			}
			if (fg) break;
		}
	}
	cout << ans << '\n'; 
	for (int i = 1; i <= n; i ++) cout << x[i] << ' '<< y[i] << '\n'; 
	return 0; 
}
```

---

## 作者：ouuan (赞：2)

1. $m\ge\left\lfloor\frac n 2\right\rfloor+1$

   $\because\begin{cases}|r_1-r_n|+|c_1-c_n|\ge n-1\\|r_1-r_n|\le m-1\\|c_1-c_n|\le m-1\end{cases}$

   $\therefore m-1+m-1\ge n-1$

   $\therefore m\ge\frac{n+1}2$

   $\because m\text{是整数}$

   $\therefore m\ge\left\lfloor\frac n 2\right\rfloor+1$

2. $m$ 可以取到 $\left\lfloor\frac n 2\right\rfloor+1$

   在每一斜行放一颗棋子即可，即：$r_i+c_i=i+1$。因为 $|r_i-r_j|+|c_i-c_j|\ge|r_i+c_i-r_j-c_j|$。
   
   
```cpp
#include <cstdio>

using namespace std;

int main()
{
    int n, i, ans;

    scanf("%d", &n);
    ans = n / 2 + 1;

    printf("%d", ans);

    for (i = 1; i <= ans; ++i) printf("\n%d 1", i);
    for (i = 2; i <= n - ans + 1; ++i) printf("\n%d %d", ans, i);

    return 0;
}
```

---

## 作者：xh39 (赞：1)

观察公式|ri−rj|+|ci-cj|>=|i-j|

于是可以把公式翻译为中文:i与j的距离>=i与j的编号差。

接下来不难想到,可以这样排列

这样,公式两边正好相等。

```
1 2 3 ... m
          m+1
          m+2
          ...
          2m-1
//没写东西的地方表示不放棋子。
```

于是我们可以对m进行枚举,找到m,然后输出就行了。题目中说:If there are multiple answers, print any.于是输出任意一个就可以了。

ac代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,i,m;
	cin>>n;
	for(i=1;i*2-1<n;i++){
	}
	m=i;
	cout<<m<<endl;
	for(i=1;i<=n;i++){ //输出。
		if(i<=m){ //靠着上面一行的时候。
			cout<<"1 "<<i;
		}else{ //靠着右边一行的时候。
			cout<<i-m+1<<" "<<m;
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：xxxalq (赞：0)

[洛谷题目链接](https://www.luogu.com.cn/problem/CF1173B)&[CF题目链接](http://codeforces.com/problemset/problem/1173/B)

## 思路分析：

转化一下求 $m$ 的最小值，其实就是给定一个 $m\times m$ 的棋盘，求最多能摆多少枚棋子，也就是 $n$ 的最大值，但是 $n$ 已经给出，于是可以倒推求 $m$ 的值。

这道题就是要保证任意两点的曼哈顿距离大于等于它们坐标值之差，根据贪心很明显第一列和最后一行要全部摆满。所以 $m=2n-1$，直接枚举输出即可。

## 代码：

```cpp
#include<iostream>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	int m=n/2+1;//计算m
	printf("%d\n",m);
	for(int i=1; i<=n&&i<=m;i++)printf("%d %d\n",1,i);//输出第一列
	for(int i=2;i<=n-m+1;i++)printf("%d %d\n",i,m);//输出最后一行
	return 0;
}
```


---

## 作者：To_Carpe_Diem (赞：0)

## 题目简述

题目要求在一个 $m\times m$ 的棋盘上放置 $n$ 个棋子，使得满足以下规则：对于任意的两个棋子 $i$ 和 $j$ ，有 $|r_i-r_j|+|c_i-c_j|\geq|i-j|$。

## 思路简述

$m$ 的最小值为 $\frac{n}{2}+1$。
接下来我们详细解释一下为什么这样的放置方式能够满足规则。

## 思路讲解

首先我们观察到，棋子的坐标差的绝对值最大为 $m-1$。那么为了满足规则 $|r_i-r_j|+|c_i-c_j|\geq|i-j|$，我们可以将棋子按照 $i$ 的顺序依次放在第 $i$ 行和第 $1$ 列。这样就能保证对于任意的两个棋子 $i$ 和 $j$，有 $|r_i-r_j|+|c_i-c_j|\geq|i-j|$。

假设有两个棋子 $i$ 和 $j (i<j)$，它们的坐标分别是 $(r_i,c_i)$ 和 $(r_j,c_j)$。由于棋子按照 $i$ 的顺序依次放置，所以 $r_i\leq r_j$，那么根据放置方式可知，那么根据放置方式可知，$r_i=i$ 且 $r_j=j$。因此有 $|r_i-r_j|=|i-j|$，同理 $ |c_i-c_j|\geq0$。所以对于任意的两个棋子 $i$ 和 $j$，有 $|r_i-r_j|+|c_i-c_j|\geq|i-j|$ 成立。

## 代码实现

```cpp
#include<iostream>
using namespace std;

int n,m;

int main() {
    cin >> n;
    m=n/2+1;
    cout<<m<<endl;
    for(int i=1;i<=m;i++) 
    	cout<<i<<" "<<1<<endl;
    for(int i=2;i<=n-m+1;i++)
        cout<<m<<" "<<i<<endl;
    return 0;
}
```

---

## 作者：StudyingFather (赞：0)

**Unofficial Solution to this contest also available in [Studying Father's Blog](https://studyingfather.com/archives/1304).**

------------

一种构造方式是这样的：将前 $ \left\lfloor\frac n 2\right\rfloor+1 $ 个棋子按编号顺序从左往右放在第一行，剩下的棋子按编号顺序从上往下放在最后一列。（也就是摆成L形）

事实上，一切满足 $ r_i+c_i=i+1 $ 的方案都是可行解。证明可以参考官方题解的思路，这里略去。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
 int r,c;
}a[1005];
int main()
{
 int n;
 scanf("%d",&n);
 a[1].r=a[1].c=1;
 int mid=n/2+1;
 printf("%d\n",mid);
 for(int i=1;i<=mid;i++)
  printf("1 %d\n",i);
 for(int i=mid+1;i<=n;i++)
  printf("%d %d\n",i-mid+1,mid);
 return 0;
}
```


---

