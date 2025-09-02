# Permutation Cycle

## 题目描述

**【题意】：**

我们有一个序列$P$，对于任意整数$i(1 \leq i \leq N)$，满足$1 \leq P_i \leq N$。

我们定义一个函数$f$，其中$f_{i,j}$的值满足：

- 当$j=1$时，$f_{i,j}=P_i$。
- 当$j\neq 1$时，$f_{i,j}=f_{P_i,j-1}$。

我们记$G_i$表示令$f_{i,j}=i$成立的最小的$j$。我们可以证明$G_i$是一定存在的。

输入$N,A,B$。$A,B$表示$G_i$只能等于$A$或$B$。求一个可能的$P$，使得对于任意$i(1 \leq i \leq N)$，都有$f_{i,j}=i$。

## 样例 #1

### 输入

```
9 2 5
```

### 输出

```
6 5 8 3 4 1 9 2 7```

## 样例 #2

### 输入

```
3 2 1
```

### 输出

```
1 2 3 ```

# 题解

## 作者：Brilliant11001 (赞：7)

## [题目传送门](https://www.luogu.com.cn/problem/CF932C)

### [更好的阅读体验](https://www.cnblogs.com/Brilliant11001/p/18325857)

### 思路：

个人认为构造题全靠感性理解，理解对了问题就迎刃而解了。（有点像做阅读理解）

我们先感性地理解题目中所有变量和函数的含义。

#### $f$ 函数是什么？

当 $j \neq 0$ 时，$f(i, j) = f(p_i, j - 1)$，就是使 $j$ 花费了 $1$ 的代价，然后使 $i$ 变为了 $p_i$。

这就可以联想到在一张图上移动，那么 $f(i, j)$ 中的 $j$ 就相当于剩余步数，$i$ 就相当于目前的位置。

那么当 $j = 1$ 时也可以这样来解释。

注意到每次移动为 $i \rightarrow p_i$，可以理解为 $i$ 向 $p_i$ 连了一条有向边，那么 $p$ 数组的含义也就得以解释。

将整个问题放在一张有向图上，所以 $f(i, j)$ 表示**从点 $i$ 出发，走 $j$ 步到达的点的编号**，这恰好印证证了 $1\le p_i\le n$ 这一条件。

#### $G$ 数组是什么？

根据我们对 $f$ 函数的定义，那么 $G$ 数组的含义即为：**从 $i$ 出发走回到点 $i$ 的最小步数。**

综上所述，问题变成了：**构造一个含有 $n$ 个点的有向图，使得图中每个点都能在走 $A$ 步或 $B$ 步后回到原点。**

手玩一下样例一，发现它构造的有向图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/1o2hilp1.png)

发现是一个长度为 $5$ 的环和两个长度为 $2$ 的环！

从中我们可以得到启发：**在图中构造两种环，一种长度为 $A$，一种长度为 $B$**。

设构造了 $x$ 个长度为 $A$ 的环，$y$ 个长度为 $B$ 的环。

所以解不定方程：

$$Ax + By = n$$

即可。

其中 $x,y$ 都为非负整数。

由于输出一种方案即可，数据范围也不大，可以暴力枚举 $x$。

最后构造就行了。

$\texttt{Code:}$

```cpp
#include <iostream>
using namespace std;

const int N = 1000010;

int n, a, b;
int p[N];

int main() {
    scanf("%d%d%d", &n, &a, &b);
    bool flag = false;
    int x, y;
    for(x = 0; x <= n / a; x++) //枚举 x
        if((n - x * a) % b == 0) {
            flag = true;
            y = (n - x * a) / b;
            break; //随便找一个解
        }
    if(!flag) puts("-1"); //找不到解
    else {
        int id = 1;
        for(int i = 1; i <= x; i++) { //构造 x 个长度为 a 的环
            for(int j = 1; j < a; j++)
                p[id] = id + 1, id++;
            p[id] = id - a + 1, id++;
        }
        for(int i = 1; i <= y; i++) { //构造 y 个长度为 b 的环
            for(int j = 1; j < b; j++)
                p[id] = id + 1, id++;
            p[id] = id - b + 1, id++;
        }
        for(int i = 1; i <= n; i++) printf("%d ", p[i]);
    }
    return 0;
}
```

### 总结一下如何做构造题（仅供参考）：

1. 先理解清楚题中每个定义的含义；
2. 根据定义大胆发挥联想；
3. 从样例和样例解释找灵感。

---

## 作者：dormantbs (赞：3)

手玩一下题目中的函数,
$ f(i,j) $ 就是 沿着 $i$ -> $p_i$ 的方向一直走 $j-1$ 步最后得到的  
$p_i$ 值。  

那么要让 $ f(i,j) = i$ ，就显然是要构成一个大小为 $j$ 的环。  
  
即要让 $g(i) = j$, 我们需要让 $i$ 这个点在一个大小为 $j$ 的环上。  

那么如何构造让每个点都满足呢?

如图:  (画图水平太差不要在意)
![](https://cdn.luogu.com.cn/upload/pic/14944.png )  

这样的话可以看到3个点都处在大小为3的环上。  

接下来就很简单了吧。

先让$g(i)=a$一直构造大小为$a$的环，直到剩下的点数可以整除$b$,就一直构造  
大小为$b$的环知道结束。  

若到最后都会有多余,就是无解。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int N=2e6+10;
int p[N];
int main(){
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	int t=n,i=1;
	bool flag=0;
	if(t%a==0) flag=1;
	if(t%b==0) a=b,flag=1;
	while(i<=n){
		p[i]=i+a-1;
		if(p[i]>n) break;
		for(int j=p[i];j>i;--j) p[j]=j-1;
		i+=a;
		if(!flag){
			t-=a;
			if(t%b==0) a=b,flag=1;
		}
	}
	if(!flag) return puts("-1")&0;
	for(int i=1;i<=n;++i) printf("%d ",p[i]);
}
```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF932C)

## 题意
对于从 $1$ 到 $N$ 的整数排列 $p_1,p_2,\dots,p_n$ ，定义函数 $f$ 如下：如果 $j=1$ 则 $f(i,j)=p_i$，当 $j>1$ 时 $f(i,j)=f(p_i,j−1)$。 用 $g(i)$ 表示满足 $f(i,j)=i$ 的最小正整数 $j$。可以证明这样的 $j$ 总是存在。给定 $N$，$A$ 和 $B$，找到一个从 $1$ 到 $N$ 的整数排列 $P$，使得对于 $1\le i\le N$，$g(i)$ 等于 $A$ 或 $B$。

## 思路
通过题目我们就可以得知：
- $f(i, j)$ 表示从点 $i$ 出发，走 $j$ 步到达的点的编号。
- $g(i)$ 表示从 $i$ 出发走回到点 $i$ 的最小步数。

所以我们需要在图中构造两种长度环，一种长度为 $a$，一种长度为 $b$。我们可以先构造大小 $a$ 的，直到可以整除 $b$，构造到大小为 $b$ 的结束。

---

