# Magic Tricks

## 题目描述

Masha is going to participate in a talent show conducted by the university she studies at. She wants to impress the audience with lots of different magic tricks!

For one of her tricks, she uses $ n $ sponge balls, one of which is a special one. First, she arranges the balls in a row in such a way that the special ball is put on position $ k $ (positions are numbered from $ 1 $ to $ n $ from left to right). After that, she performs $ m $ swaps: during the $ i $ -th swap, she chooses the ball on position $ x_i $ and the ball on position $ y_i $ , and swaps them.

Since Masha is a magician, she fakes some of her actions to trick the audience — when she starts performing a swap, she may fake it, so it is not performed (but it looks like it is performed for the audience). There are no constraints on which swaps Masha should fake or should actually perform — for example, she may fake all of the swaps, or even not fake anything at all.

For the trick to work perfectly, the special ball should end up on a specific position — Masha has not decided yet, which position is perfect. Since faking swaps is difficult, for each position she wants to know the minimum number of swaps she has to fake so that the special ball ends up there.

Unfortunately, Masha is a magician, neither a mathematician nor a programmer. So she needs your help in calculating what she wants!

## 样例 #1

### 输入

```
4 5 1
3 4
2 1
4 1
3 1
3 1```

### 输出

```
2 0 3 1```

## 样例 #2

### 输入

```
5 7 4
3 2
3 2
4 2
3 4
4 1
3 2
5 2```

### 输出

```
2 2 0 3 1```

## 样例 #3

### 输入

```
7 15 5
5 3
4 2
6 1
2 4
1 6
3 7
5 6
4 2
6 4
2 6
6 3
6 3
7 6
2 6
7 2```

### 输出

```
-1 1 1 1 2 1 0```

# 题解

## 作者：igAC (赞：1)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1346E)

[CFlink](https://codeforces.com/problemset/problem/1346/E)

简要题意：

有 $n$ 个碗，一开始球在第 $k$ 个碗里。

第 $i$ 次操作会交换 $x_i,y_i$，你可以花费 $1$ 的代价使这次操作无效。

对于每个 $i,i=1,2,\dots,n$ 求出球最后在第 $i$ 个碗里的最小花费，若不能达到输出 ``-1``。

# $\text{Solution}$

简单 dp 题，但是不会 Kotlin 语言。

设 $f_{i,j}$ 表示第 $i$ 次操作后，球在 $j$ 的最小花费。

转移显然：

$$
f_{i,x_i}=\min(f_{i-1,x_i}+1,f_{i-1,y_i})
\\
f_{i,y_i}=\min(f_{i-1,y_i}+1,f_{i-1,x_i})
$$

然后发现第一维没什么用，把它去掉，这道题就做完了。

具体实现可参考代码（C++）。

# $\text{Code}$

```cpp
#include<bits/stdc++.g>
#define INF 1e9
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,k,f[N];
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;++i) f[i]=INF;
	f[k]=0;
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		int f1=f[x],f2=f[y];
		f[x]=min(f1+1,f2);
		f[y]=min(f2+1,f1);
	}
	for(int i=1;i<=n;++i){
		if(f[i]==INF) printf("-1 ");
		else printf("%d ",f[i]);
	}
	return 0;
}
```

---

