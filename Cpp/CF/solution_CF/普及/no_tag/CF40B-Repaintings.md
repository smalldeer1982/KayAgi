# Repaintings

## 题目描述

有一个 $n×m$ 的棋盘，左上角的格子被认为是黑色的。在第 $0$ 分钟时，我们会把所有棋盘上的黑色格子染成 $0$ 号颜色。这时，我们一直重复这样的操作：在第 $i$ 分钟时，如果其中一个格子所有相邻格的颜色都为 $i-1$ 时，并且这个格子最开始是一个黑色的格子，我们就会把这个格子涂成 $i$ 号颜色。（注：两个格子有一个公共点时，两个格子就是相邻的）

## 样例 #1

### 输入

```
3 3
1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 3
2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1 1
1
```

### 输出

```
1
```

# 题解

## 作者：liuli688 (赞：4)

### 思路：
先摆一张图。
![](https://cdn.luogu.com.cn/upload/image_hosting/5yucrpsi.png)
这张图是本题 \#5 测试点的数据的染色情况。从中我们可以看出，染色次数越多的格子越靠近中心。

如果本题没有说这是一个棋盘（黑白交错的），那么它就变得非常简单：只要求以 $x$ 为边的矩形面积减以 $x
+1$ 为边的矩形面积即可。求棋盘的面积也一样，看下面是如何求 `1` 有多少个的：
```
1.1.1.    11111.
.2.2.1    12.2..
1.3.2. => 1.3.2.
.2.3.1 => 12.3..
1.2.2.    1.2.2.
.1.1.1    1.....
```
我们把下边和右边的 `1` 挪到了上边和左边，若棋盘长为 $n$，宽为 $m$，易得 `1` 的个数为 $n+m-2$。

下面两种情况也一样：
```
1.1.1.1    1111111
.2.2.2.    12.2.2.
1.3.3.1 => 1.3.3..
.2.3.2. => 12.3.2.
1.2.2.1    1.2.2..
.1.1.1.    .......

1.1.1.    111111
.2.2.1    12.2..
1.3.2.    1.3.2.
.2.3.1 => 12.3..
1.3.2.    1.3.2.
.2.2.1    12.2..
1.1.1.    ......
```
那么面积就很好求了。不过有一个需要注意的地方：最后输出时要输出 $\max\{n+m-2,1\}$，不然有可能因为 $n$ 和 $m$ 很小时输出负数或 $0$。
### 代码：
```cpp
#define speedup ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define namesp using namespace std

#include <bits/stdc++.h>
namesp;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;

const int INF = INT_MAX;
const int UINF = INT_MIN;
const ll LINF = LONG_LONG_MAX;
const ll ULINF = LONG_LONG_MIN;

#define fp(i,a,b) for(i = a;i < b;i++)
#define fm(i,a,b) for(i = a;i > b;i--)
#define fl(i,a,b) for(i = a;i <= b;i++)
#define fg(i,a,b) for(i = a;i >= b;i--)
#define bk break
#define ctn continue
#define reg register

#define freo(n,m) freopen(n,"r",stdin),freopen(m,"w",stdout)
#define frec(n) fclose(stdin),fclose(stdout)

#define mp make_pair
#define fir first
#define sec second

#define pb push_back
#define pf push_front

int n,m,x;

signed main()
{
    speedup;
    cin >> n >> m >> x;
    n -= --x << 1;//将棋盘缩小，方便求面积
    m -= x << 1;
    if(min(n,m) < 0)//如果棋盘太小，出现负数，说明 x 太大，无解
        cout << 0;
    else
        cout << max(n + m - 2,1);//否则正常输出
    return 0;
}
```

---

## 作者：kevin1616 (赞：4)

### 审题
有一个 $n\times m$ 的棋盘，左上角的格子被认为是黑色的。在第 $0$ 分钟时，我们会把所有棋盘上的黑色格子染成 $0$ 号颜色。此后一直重复这样的操作：在第 $i$ 分钟时，如果其中一个格子所有相邻格的颜色都为 $i-1$ 时，并且这个格子最开始是一个黑色的格子，我们就会把这个格子涂成 $i$ 号颜色。求有多少个格子刚好被染了 $x$ 次颜色。
***
### 方法
【找规律】看到所有格子的染色问题，首先想到的是枚举样例，发现规律。时间复杂度 $O(1)$，故该方法可行。
***
### 思路
在第 $i$ 分钟时，重新着色的所有格子将位于一个矩形中，格子 $(i,i)$ 和 $(n-i,m-i)$ 里有顶点。

此时，答案将被我们转换成到边缘的最小距离正好为 $x$ 的格子数量。最终即可求出答案。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x;
int main(){
    cin >> n >> m >> x;
    n -= 2 * x - 1; //改变n
    m -= 2 * x - 1; //改变m
    if(min(n,m) < 0) cout << 0 << endl; //有任意一个小于0时，直接输出0
    else cout << max(n + m,1) << endl; //否则输出答案
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：lsihsp1313 (赞：1)

### 思路

找规律的题。

因此可以设计出 $O(1)$ 时间复杂度的算法。

不难发现越靠近棋盘中心的染色次数都很多，而且每次向相邻格子染色都是将其颜色加 $1$，因此可以将棋盘缩小，找到距离边缘为 $x$ 的格子就可以啦。

### 代码

```cpp
#include <iostream>
int n, m, x;
int main () {
    cin.tie (0) -> sync_with_stdio (false);
    std::cin >> n >> m >> x;
    n -= x << 1 - 1;
    m -= x << 1 - 1;
    if(std::min (n, m) < 0)
     	std::cout << 0;
    else
     	std::cout << std::max (1, n + m);
    return 0;
}
```

---

## 作者：_Maverick_ (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF40B)

## 题意

有一个 $n×m$ 的棋盘，左上角的格子被认为是黑色的。在第 $0$ 分钟时，我们会把所有棋盘上的黑色格子染成 $0$ 号颜色。这时，我们一直重复这样的操作：在第 $i$ 分钟时，如果其中一个格子所有相邻格的颜色都为 $i-1$ 时，并且这个格子最开始是一个黑色的格子，我们就会把这个格子涂成 $i$ 号颜色。求有几个格子刚好被染了 $x$ 次颜色。

## 思路

看样例

##### 样例 #1
```
3 3
1
```
```
4
```
通过找规律，我们得出：

越靠中间部分的格子染色次数越多。

那我们可以通过将棋盘面积缩小，然后求出到边缘的最小距离正好为 $x$ 的格子数量就行了。

## ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, x;
int main() {
	cin >> n >> m >> x;
	n = n - x * 2 - 1;
	m = m - x * 2 - 1;
	if (min(n, m) < 0) {
		cout << 0;
	} else {
		cout << max(n + m, 1);
	}
	return 0;
}//完结撒花！
```

---

## 作者：zym20249_ (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF40B)
## 题目翻译：
给定一个大小为 $n×m$ 的棋盘。在零分钟内，我们将所有黑色方块重新涂成 $0$ 号颜色。在第 $i$ 分钟内，我们将初始为黑色的方块重新涂成i号颜色，这些方块正好有四个角邻接方块被涂成 $i-1$ 号颜色 ( 所有这些方块同时被重新涂色 ) 。这个过程无限循环进行。你需要计算出我们重新涂色了多少个方块恰好 $x$ 次。
棋盘的左上角方块始终被假设为黑色。如果两个方块恰好有一个公共点，则称它们为角邻接方块。
## 思路：
所以在第 $i$ 分钟时，重新着色的所有格子将位于一个矩形中，答案到边缘的最小距离正好为 $x$ 的格子数量。
## AC代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//不用多说
int n,m,x;//数据范围不大，放心int
int main()
{
    scanf("%d%d%d",&n,&m,&x);//建议使用scanf,和cin一样
    n-=2*x-1; 
    m-=2*x-1; 
    if(min(n,m)<0)printf("0\n");//建议使用printf,和cout一样
    else printf("%d\n",max(n+m,1));//printf和scanf时间更快
    return 0;//完结撒花
}//仅供参考

``````

---

## 作者：fyn1234 (赞：1)

题目传送门（[CF](https://codeforces.com/problemset/problem/40/B)）（[洛谷](https://www.luogu.com.cn/problem/CF40B)）

~~[可能更好的食用体验](https://www.luogu.com.cn/article/a6a88553)~~

### 题意

有一个 $n \times m$ 的棋盘，左上角的格子在开始时是黑色的。一开始，我们会把所有棋盘上的黑色格子染成 $0$ 号颜色。然后，我们一直重复这样的操作：在第 $i$ 分钟时，如果其中一个格子所有相邻格的颜色都为 $i−1$ 时，并且这个格子最开始是黑色的，我们就会把这个格子涂成 $i$ 号颜色。（注：两个格子有一个公共点时，两个格子就是相邻的）你要判断，几个格子刚好被染了 $x$ 次颜色。

~~好像啥也没说~~

### 思路

不难发现越靠中间部分，格子染色次数越多。因此我们求出到边缘的最小距离正好为 $x$ 的格子数量就行了。

### AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, x;
int main(){
   cin>>n>>m>>x;
    n -= 2 * x - 1;
    m -= 2 * x - 1;
    if(min(n, m) < 0) cout<<0;
    else cout<<max(n+m,1);
    return 0;
}
```

---

## 作者：LINYUHENG2 (赞：0)

## 思路
我们发现，越靠近中间的部分，格子染色次数就越多。因此我们求出到边缘的最小距离正好为 $x$ 的格子数量就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, x;
int main(){
   cin>>n>>m>>x;
    n -= 2 * x - 1;
    m -= 2 * x - 1;
    if(min(n, m) < 0) cout<<0;
    else cout<<max(n+m,1);
    return 0;
}

---

## 作者：duanjingxiao (赞：0)

# [Repaintings](https://www.luogu.com.cn/problem/CF40B)

### 题目描述

有一个 $n×m$ 的棋盘，左上角的格子被认为是黑色的。在第 $0$ 分钟时，我们会把所有棋盘上的黑色格子染成 $0$ 号颜色。这时，我们一直重复这样的操作：在第 $i$ 分钟时，如果其中一个格子所有相邻格的颜色都为 $i-1$ 时，并且这个格子最开始是一个黑色的格子，我们就会把这个格子涂成 $i$ 号颜色。

求几个格子刚好被染了 $x$ 次颜色。


### 思路：
找规律，通过分析数据样例，我们可以发现越靠中间部分的格子染色次数越多。我们可以通过把棋盘面积缩小来求边缘的最小距离正好为 $𝑥$ 的格子数量。
  
## 代码：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n , m , x;
int main()
{
  cin >> n >> m >> x;
  int a = 2 * x - 1;
  m -= a;
  n -= a;
  if(min(n , m) < 0)
    	cout << 0;
   else
     	cout << max(n + m , 1);
  return 0;	
}
```

---

## 作者：封禁用户 (赞：0)

简单规律题。

通过模拟数据，不难发现在整张图中，越靠中间部分的格子染色次数越多。那我们可以通过将棋盘面积缩小，然后求出到边缘的最小距离正好为 $x$ 的格子数量就行了。

**注意点：如果 $x$ 的值太大，已经超过了 $n$ 和 $m$，那么此数据就肯定无解。**

**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, x;
int main()
{
    cin >> n >> m >> x;
    n = n - x * 2 - 1;
    m = m - x * 2 - 1;
    if(min(n, m) < 0) cout << 0;
    else cout << max(n + m,1);
    return 0;
}
```

---

## 作者：MsgNotFound (赞：0)

# 理解题意

有一个 $n\times m$ 的棋盘，左上角的格子被认为是黑色的。在第 $0$ 分钟时，我们会把所有棋盘上的黑色格子染成 $0$ 号颜色。这时，我们一直重复这样的操作：在第 $i$ 分钟时，如果其中一个格子所有相邻格的颜色都为 $i-1$ 时，并且这个格子最开始是一个黑色的格子，我们就会把这个格子涂成 $i$ 号颜色。（注：两个格子有一个公共点时，两个格子就是相邻的）

# 思路分析
一个染色找规律问题。通过分析几组样例可以发现如下规律：

在第 $i$ 分钟时，重新进行染色的所有格子位于一个矩形中，我们假设 $(1,1)$ 是左上角，$(n,m)$ 是右下角。则 $(i,i)$ 和 $(n-i,m-i)$ 中有顶点。在这种情况下答案是计算到侧面的最小距离为 $x$ 的单元格数量

根据这个，就可以写出代码了：

# 核心代码
```cpp
    int n,m,x;
    cin>>n>>m>>x;
    int a=2*x-1;
    m-=a,n-=a;
    if(min(n,m)<0)cout<<0;
    else cout<<max(n+m,1);
```

---

## 作者：yhx0322 (赞：0)

## Description
有一个 $n \times m$ 的棋盘，左上角的格子被认为是黑色的。在第 $0$ 分钟时，我们会把所有棋盘上的黑色格子染成 $0$ 号颜色。这时，我们一直重复这样的操作：在第 $i$ 分钟时，如果其中一个格子所有相邻格的颜色都为 $i-1$ 时，并且这个格子最开始是一个黑色的格子，我们就会把这个格子涂成 $i$ 号颜色。

求：有多少个格子刚好被染了 $x$ 次颜色。
## Solution
首先要注意的是，在第 $i$ 步中，所有重新着色的单元格将位于一个矩形中，单元格 $(i,i)$、$(n-i,m-i)$ 中有顶点（如果我们假设 $(1, 1)$ 是左上角的单元格，$(n,m)$ 是右下角的单元格）。

在这种情况下，解决方案是计算到侧面的最小距离正好为 $x$ 的类型的单元格数量。也就是说，对于单元格 $(a, b)$，$x = \min(\min(a,b),\min(n - a + 1,m - b + 1))$。

最终即可求出答案。
## Code
代码就不贴了，实现比较简单。

---

## 作者：封禁用户 (赞：0)

## 思路

有一个 $n×m$ 的棋盘，左上角的格子被认为是黑色的。在第 $0$ 分钟时，我们会把所有棋盘上的黑色格子染成 $0$ 号颜色。这时，我们一直重复这样的操作：在第 $i$ 分钟时，如果其中一个格子所有相邻格的颜色都为 $i-1$ 时，并且这个格子最开始是一个黑色的格子，我们就会把这个格子涂成 $i$ 号颜色。（注：两个格子有一个公共点时，两个格子就是相邻的）

## 代码

```cpp

#include<bits/stdc++.h> 
using namespace std;
int main()
{
    int n , m , x;
    cin >> n >> m >> x;
    int a = 2 * x - 1;
    m -= a , n -= a;
    if(min(n , m) < 0)
	cout << 0;
    else
	cout << max(n + m , 1);
	return 0;	
}
```
~~记得点个赞哩~~

---

