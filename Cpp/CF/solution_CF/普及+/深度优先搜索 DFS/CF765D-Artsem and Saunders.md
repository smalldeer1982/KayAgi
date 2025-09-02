# Artsem and Saunders

## 题目描述

令 $ [n] $ 表示整数集 $ \{1,...,n\} $ ，令 $f:[x]\rightarrow[y]$ 表示函数 $f$ 的定义域为整数 $\{1,...,x\}$ 并且它的所有函数值在 $\{1,...,y\}$ 中。

现在，给定一个函数 $f:[x]\to[y]$ ，你的任务是找出一个正整数 $m$ ，和两个函数 $g:[n]\to[m]$、$h:[m]\to[n]$ ，满足对于任意 $x\in[m]$ ，有 $g(h(x))=x$ ；对于任意 $x\in[n]$ ，有 $h(g(x))=f(x)$ 。或者判定无解。

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
3
1 2 3
1 2 3
```

## 样例 #2

### 输入

```
3
2 2 2
```

### 输出

```
1
1 1 1
2
```

## 样例 #3

### 输入

```
2
2 1
```

### 输出

```
-1
```

# 题解

## 作者：TUIFEI_oier (赞：2)

## 题解 【Artsem and Saunders】
[题目链接](https://www.luogu.com.cn/problem/CF765D)

### 题目分析
首先，我们把函数关系看成一条有向边，则原题等价于：
> 构造一张二分图，其左部有 $n$ 个节点，右部有 $m$ 个节点，每个节点出度恰为 $1$，且满足题目条件。

接下来，我们考虑题目的两个限制：
1. $g(h(x))=x$，这意味着右部点连出的边一定会由左部点指回来，即连成双向边；
2. $h(g(x))=f(x)$，这意味着左部点 $i$ 顺着出边走到达的第一个左部点恰为 $f(i)$。

例如，当 $f(1)=2,f(2)=2,f(3)=2$ 时，我们可以构造出这样的二分图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/g2aa4wrw.png)

于是，如果 $f(f(x))\ne f(x)$ 时，必然无解。  
否则，我们一定可以通过以下方式构造合法解：

考虑动态在右部加点来满足左部：  
对于每一个 $x\rightarrow f(x)$，我们分三种情况讨论：
1. $f(x)$ 没有向右部点连边，于是我们新建一个右部点 $y$，在 $f(x),y$ 之间双向连边，然后 $x$ 向 $y$ 连边；
2. $f(x)$ 与所连右部点之间为双向边，则我们直接由 $x$ 向 $f(x)$ 所连右部点连边；
3. $f(x)$ 与所连右部点为单向边，则无解。

代码实现上，在读入的过程中，我们就可以顺便维护连边关系。  
时间复杂度 $O(n)$。

### 代码实现
其实是相当好写的。  
```c++
#include <bits/stdc++.h>
using namespace std;
// 快读部分
#define ch getchar
template<typename T> void read(T &x){
	x = 0; int f(1); char c = ch();
	for(;!isdigit(c);c = ch()) if(c == '-') f = -1;
	for(;isdigit(c);c = ch()) x = x*10+c-'0';
	x *= f;
}
template<typename T,typename... Args>
inline void read(T &x,Args&... args){
	read(x); read(args...);
}

const int maxn = 100005;
int n,g[maxn],h[maxn],tot;
// g[x] 为左部点 x 向右部点的连边。
// h[y] 为右部点 y 向左部点的连边。
// tot 为右部点数。
int main(){
	read(n);
	for(int i(1);i <= n;++i){
		int x; read(x);
		if(!g[x])	g[x] = ++tot,h[tot] = x,g[i] = tot;
		else if(h[g[x]] == x)	g[i] = g[x];
		else	return puts("-1"),0;
	}
	printf("%d\n",tot);
	for(int i(1);i <= n;++i)	printf("%d ",g[i]);
	puts("");
	for(int i(1);i <= tot;++i)	printf("%d ",h[i]);
	puts("");
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：1)

# 题目大意

令 $ [n] $ 表示整数集 $ \{1,...,n\} $ ，令 $f:[x]\rightarrow[y]$ 表示函数 $f$ 的定义域为整数 $\{1,...,x\}$ 并且它的所有函数值在 $\{1,...,y\}$ 中。

现在，给定一个函数 $f:[x]\to[y]$ ，你的任务是找出一个正整数 $m$ ，和两个函数 $g:[n]\to[m]$、$h:[m]\to[n]$ ，满足对于任意 $x\in[m]$ ，有 $g(h(x))=x$ ；对于任意 $x\in[n]$ ，有 $h(g(x))=f(x)$ 。或者判定无解。

# 题目分析

看到“$[n]\to[m]$”“$[m]\to[n]$” 这类的字眼，自然地想到建图。

若 $h(g(x))=x$，表示 $x$ 对应的右部节点对应的左部节点为 $x$，说明存在两条边 $left\to right,right\to left$。

我们每输入一个数，就动态在右端更新节点，注意判断无解的情况。

然后这道题就做完了，具体看代码吧。

# 代码

```cpp
//2022/1/14

const int ma=1e5+5;

int left_mat[ma],right_mat[ma];
//left_mat[i]:左部点 i 的对应点
//right_mat[i]:右部点 i 的对应点 

int n,m;

int main(void)
{
	n=read();
	
	for(register int i=1;i<=n;i++)
	{
		int x=read();
		
		if(left_mat[x]==0)
		{
			left_mat[x]=++m;
			
			right_mat[m]=x;
			
			left_mat[i]=m;
		}
		
		else if(right_mat[left_mat[x]]==x)
		{
			left_mat[i]=left_mat[x];
		}
		
		else
		{
			puts("-1");
			
			return 0;
		}
	}
	
	printf("%d\n",m);
	
	blow(left_mat,1,n," ");
	
	putchar('\n');
	
	blow(right_mat,1,m," ");
	
	return 0;
} 
```

---

