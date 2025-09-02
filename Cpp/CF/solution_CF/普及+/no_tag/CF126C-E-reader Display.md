# E-reader Display

## 题目描述

给定一个 $n \times n$ 的正方形，初始时每个点都是 `0`。当接收到 $(x,y)$ 的命令时，$(x,x) \rarr (x,y)$ 和 $(x,y) \rarr (y,y)$ 段（包括两端点）中的每个点均发生反转（`1` 变 `0`，`0` 变 `1`）。 计算使输入的表每个点都变为 0 所需的最少命令数 $s$，并输出。

## 说明/提示

$1 \leq n \leq 2 \times 10^3$，输入的数组只由 ```0``` 或 ```1``` 组成。

## 样例 #1

### 输入

```
5
01110
10010
10001
10011
11110
```

### 输出

```
4
```

# 题解

## 作者：lzqy_ (赞：2)

遇到这种01矩阵翻转成目标矩阵的最优性决策，一般套路都是找到一种遍历方式，使得当遍历到点 $(x,y)$ 时，能影响 $(x,y)$ 的操作只有一种，且该操作能影响到的点都是未被遍历到的。

用人话说就是找到没有后效性的遍历方式。

对于这道题，看到 $(x,x),(y,y)$，考虑先把对角线画出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/okfyq148.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果用点对 $(x,y)$ 来唯一描述一个翻转操作，那么该操作就是从 $(x,y)$ 扩展到对角线上的两段翻转，大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ewh9to00.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

考虑将对角线，对角线左侧，对角线右侧分开处理。只需要先处理完对角线两侧，然后对于对角线上仍然不为 $0$ 的地方单独进行操作即可。

大致的遍历顺序如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/x26tipqs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

即左侧从左往右、从下到上，右侧从右往左、从上到下。

至于维护当前点是否为 $1$，由于操作没有后效性，所以只需要记录当前行、列分别被翻转了多少次即可。

但是本人非常愚蠢地用 $2n^2$ 个树状数组维护了区间异或和，警钟撅烂。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=2010;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	return c-'0';
}
int n,ans;
int Tree1[maxn][maxn];
int Tree2[maxn][maxn];
il int Sum1(int t,int k,int sum=0){for(;k;k-=k&-k)sum^=Tree1[t][k];return sum;}
il int Sum2(int t,int k,int sum=0){for(;k;k-=k&-k)sum^=Tree2[t][k];return sum;}
il void Add1(int t,int k,int x){for(;k<=n+1;k+=k&-k) Tree1[t][k]^=x;}
il void Add2(int t,int k,int x){for(;k<=n+1;k+=k&-k) Tree2[t][k]^=x;}
il void Addh(int t,int l,int r){Add1(t,r+1,1),Add1(t,l,1);}
il void Addl(int t,int l,int r){Add2(t,r+1,1),Add2(t,l,1);}
int Query(int x,int y){return Sum1(x,y)^Sum2(y,x);}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(read()) Addh(i,j,j);
	for(int i=1;i<=n;i++)
		for(int j=n;j>i;j--)
			if(Query(i,j))
				Addh(i,i,j),Addl(j,i,j),ans++;
	for(int i=n;i;i--)
		for(int j=1;j<i;j++)
			if(Query(i,j))
				Addh(i,j,i),Addl(j,j,i),ans++;
	for(int i=1;i<=n;i++)
		if(Query(i,i)) ans++;
	printf("%d\n",ans);
	return 0;
}
```

---

