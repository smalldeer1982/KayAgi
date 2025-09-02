# MloVtry的咸鱼树

## 题目背景

签到~


## 题目描述

俗话说种瓜得瓜，种豆得豆，MloVtry 把自己砍掉一半埋进了土里，于是它得到了一颗 $n$ 个点的咸鱼树。

但是问题是由于 MloVtry 只舍得埋下一半的自己，所以这个咸鱼树是不完整的---甚至它碎裂成了 $m$ 条边。

作为一条能够致癌的咸鱼，MloVtry 当然想要一颗咸鱼树来标榜自己的身份。

MloVtry 大概估计出了连接两个点之间的代价，它想知道，最少需要多少代价才能拼出咸鱼树？

值得注意的是，咸鱼树上的咸鱼边们对于 MloVtry 是很有意见的，所以每条边都会制定一个点集 $S$，只有 MloVtry 将 $S$ 这个特殊点集里的所有点都接入某个集合 $T$ 之后，这条边才可以被加入 $T$ 这个集合。

MloVtry 把脑子埋进了地里，所以这个问题只能由你来解决了。


## 说明/提示

$1\le n\le 15$，$1\le m\le n\times (n+10)$。

数据保证所有数值在 int 范围内。


## 样例 #1

### 输入

```
2 7
1 2 1 14
2 1 2 11
2 2 1 18
2 1 2 16
2 1 2 12
2 1 2 16
2 1 3 13```

### 输出

```
11```

# 题解

## 作者：JZYshuraK (赞：6)

没人写题解我就胡一个吧

这个题真的是.....一言难尽

首先先明确一下题意：

要求一个最小生成树，其中每条边有选取条件$S$，当$S$代表的所有点连通时，这条边才能被选。

**不保证$S$包含这条边的两个端点.....**

这太自闭了.....

意识到这个情况直接$A$，意识不到就剩$10$分/xk

由于$n$非常小，不难想到状压。

设$f[S]$表示使得$S$代表的所有点连通的最小代价

考虑从$S$往外转移，边$j$可以往外转移需要满足$S \& e[j].S == e[j].S$

然后再判一下，$S$是不是至少包含着边$j$的一个端点即可。

$Code:$

```c++
#include <bits/stdc++.h>
#define N 20 
using namespace std;
int bin[N];
int f[33000];
struct Edge{int x,y,S,z;}e[N*N];
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int rd() {int x=0,f=1; char c=nc(); while(c<48) {if(c=='-') f=-1; c=nc();} while(c>47) x=(((x<<2)+x)<<1)+(c^48),c=nc(); return x*f;}
int main()
{
	int n=rd(),m=rd();
	bin[1]=1; for(int i=2;i<=n;i++) bin[i]=bin[i-1]<<1;
	for(int i=1;i<=m;i++)
	{
		e[i].x=rd(),e[i].y=rd(),e[i].S=rd(),e[i].z=rd();
	}
	int all=(1<<n)-1;
	memset(f,0x3f,sizeof f);
	f[0]=0;
	for(int i=1;i<=n;i++) f[bin[i]] = 0;
	for(int i=0;i<=all;i++)
	{
		// f[i] ->
		for(int j=1;j<=m;j++)
		{
			if((i & e[j].S) == e[j].S)
			{
				if(((i & bin[e[j].x]) == bin[e[j].x]) || ((i & bin[e[j].y]) == bin[e[j].y]))
				{
					f[i | (bin[e[j].x] | bin[e[j].y])] = min(f[i] + e[j].z , f[i | (bin[e[j].x] | bin[e[j].y])]);
				}
			}
		}
	}
	if(f[all]==0x3f3f3f3f) puts("-1");
	else cout << f[all] << endl ;
	return 0;
}
```



我也不知道为啥这个题是个黑题.....

推销个人[Blog](https://www.cnblogs.com/shurak)

---

