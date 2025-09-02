# [JOI Open 2023] 花园 / Garden

## 题目背景

**译自 [JOI Open 2023](https://contests.ioi-jp.org/open-2023/index.html) T3 「[庭園](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2023/garden/2023-open-garden-statement.pdf) / [Garden](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2023/garden/2023-open-garden-statement-en.pdf)」**

## 题目描述

JOI 王国是一个神秘的王国，疆域辽阔无边。JOI 君是 JOI 国国王，他在计划分割疆域的一部分来建造他的花园。

JOI 网络可以考虑成一个充分大的二维网格，网格由从上到下和从左到右的正方形单元格密铺而成。有一个单元格是坐标原点。令 $(x,y)$ 表示表示从原点向右移动 $x$ 个单元格，再向上移动 $y$ 个单元格所到达的单元格。这里，向左移动 $a$ 个单元格意味着向右移动 $-a$ 个单元格。类似地，向下移动 $a$ 个单元格意味着向上移动 $-a$ 个单元格。

在领土内有一些艺术品。这些艺术品根据放置在领土上的方式分为 **A 类**和 **B 类**。

- 有 $N$ 种 A 类艺术品。第 $i$ 种艺术品（$1\le i\le N$）放在每个形如 $(P_i+kD,Q_i+lD)$ 的单元格上，其中 $k,l$ 为整数。
- 有 $M$ 种 B 类艺术品。第 $j$ 种艺术品（$1\le j\le M$）放在每个形如 $(R_j+kD,y)$（其中 $k,y$ 为整数）或 $(x,S_j+lD)$（其中 $l,x$ 为整数）的单元格上。

注意一个单元格中可能包含多种不同类别的艺术品。

JOI 君计划在网格中选择一个矩形区域建造花园。换句话说，他会选择四个整数 $a,b,c,d$。然后形如 $(x,y)$ 的单元格将构成 JOI 君的花园，其中 $x,y$ 是满足 $a\le x\le b,c\le y\le d$ 的整数。因为 JOI 君喜欢看到多种艺术品，对于任意 $N+M$ 种艺术品中的一种，JOI 君的花园中需要至少包含这种艺术品中的一个。另一方面，如果 JOI 君计划要建的花园过大，JOI 国的居民就会生气。因此，JOI 君希望最小化花园包含的单元格数使得满足上述条件。

给定艺术品的信息，写一个程序计算 JOI 君的花园所包含的最小单元格数。

## 说明/提示

**【样例解释 #1】**

下图展示了 JOI 国领土中的满足 $0\le x<10,0\le y<10$ 的单元格 $(x,y)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/pnsc7qm4.png)

在本图中，圆形和菱形分别表示 A 类和 B 类艺术品。圆形或菱形中的整数表示艺术品的种数。如果 JOI 君选择 $a=1,b=2,c=2,d=5$，JOI 君的花园就是黑色矩形区域。这种情况下，对于这三种艺术品，JOI 君的花园中至少会有每种中的一个。花园所占单元格数为 $8$。因为没有比这个花园占地更小且满足条件的花园了，因此输出 $8$。

这组样例满足所有子任务的限制。

**【样例解释 #2】**

这组样例满足子任务 $1,4,5,6$ 的限制。

**【样例解释 #3】**

这组样例满足子任务 $1,5,6$ 的限制。

**【数据范围】**

对于所有数据，满足：

- $N,M\ge 1$
- $N+M\le 5\times 10^5$
- $1\le D\le 5\ 000$
- $0\le P_i,Q_i,R_j,S_j<D$

详细子任务附加限制及分值如下表所示。

| 子任务 |        附加限制        | 分值 |
| :----: | :--------------------: | :--: |
|  $1$   |        $M\le 8$        | $15$ |
|  $2$   | $D\le 10,N+M\le 5000$  | $6$  |
|  $3$   | $D\le 50,N+M\le 5000$  | $8$  |
|  $4$   | $D\le 100,N+M\le 5000$ | $16$ |
|  $5$   |     $N+M\le 5000$      | $30$ |
|  $6$   |       无附加限制       | $25$ |

## 样例 #1

### 输入

```
2 1 5
1 4
2 2
0 0
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 4 100
20 26
81 56
20 3
58 71
74 82
95 61
95 61
```

### 输出

```
2840
```

## 样例 #3

### 输入

```
5 7 5000
1046 365
4122 1166
4009 2896
1815 4065
4372 1651
2382 123
1475 836
3313 4005
2579 568
4300 4867
1050 3214
3589 4653
```

### 输出

```
10543092
```

# 题解

## 作者：EXODUS (赞：8)

# Part 1：前言
CNOI 風味の強い日本名物！

这要放 CNOI 高低得给你套点超级数据结构，就题而言这道题还是挺不错的/kx。


# Part 2：正文

下文中令 $d=D,n=N,m=M$。

不妨从部分分入手。由于子任务 1 和该题正解做法关联性较低，故不再赘述，我们从子任务 2 开始看起。

我们先偷看一眼样例解释，发现第一种纪念品是一堆相邻最近点对距离为 $D$ 的点阵，第二种则是一个以若干条相邻之间距离为 $D$ 的水平线和竖直线构成的网格，因此不难想到如果我们把平面划分为若干个大小为 $D\times D$ 的方形，每个方形内部都是一样的。故我们只需要考虑任意一个大小为 $2D\times 2D$ 的方形即可（不是 $D\times D$ 的原因是因为选超过边界的答案可能更优）。

因此我们有了一个 $O(d^4(n+m))$ 的暴力做法。具体而言是枚举每一个矩形和纪念品，判断其是否在这个矩形中即可。

然后我们想起来了我们在噗叽组的时候学过的最大子矩形之类的题目，我们现在试图去枚举三个边界，然后考虑每个纪念品是否已经被包含在当前矩形里。每个纪念品都会对下一个边界产生一个不等式的限制条件，对这些不等式求交即可获得一个 $O(d^3(n+m))$ 的做法。

我们试着再少扫一个边界，如果你像我一样只扫左上边界的话，你会获得一个没有前途的答辩 $O(d^2m)$ 的做法。因此我们考虑只扫左右边界。我们将纵轴看作是一个环，考虑此时的限制条件是什么。对于每一个一类纪念品，其相当于要求上下边界构成的弧包含其纵坐标。对于每一个二类纪念品，如果当前没有竖直线与其相交，则也是一个和一类纪念品一样的区间限制。这其实是一个环上的覆盖问题，可以以和环长线性相关的复杂度求出。具体而言，我们每次枚举相邻两个点，计算覆盖除去其中间一段的所有位置的答案。时间复杂度 $O(d^2(d+n+m))$。

再少扫一个边界感觉就彻底没救了。我们现在试图把固定左端点扫一轮右端点的复杂度降低为 $O(d+n+m)$，即把枚举并计算答案的复杂度均摊出去。不妨倒序枚举右端点，维护当前的每一个限制点。这其实相当于是加入若干关键点然后统计答案的问题。可以通过链表，每次删去一个点后用前驱后继的答案更新答案即可做到单次删除均摊 $O(1)$。总时间复杂度 $O(d(d+n+m))$。

那么最后的做法就呼之欲出了。注意到对于每一个位置其实只需要有一个未被覆盖的就需要从链表中被删除。而在所有这样的纪念品中对每一列保留行号最靠右的即可，那么每次均摊的东西由 $O(n+m)$ 变成了 $O(d)$，所以总时间复杂度是 $O(d^2)$。


# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

const int N=5e5+7,D=5e3+7;

int n,m,d,P[N],Q[N],R[N],S[N],lst[D][D*2];
bool visx[D],visy[D];
vector<int>vu[D*2];

struct List{
	int pre[N],nxt[N],hd,tl,len;
	void build(){for(int i=0;i<d;i++)pre[i]=i-1,nxt[i]=i+1;hd=0,tl=d-1,len=1e9;}
	void del(int x){
		int l=pre[x],r=nxt[x];
		if(l!=-1)nxt[l]=r;
		if(r!=d)pre[r]=l;
		if(pre[r]==-1)hd=r;
		if(nxt[l]==d)tl=l;
		if(l!=-1&&r!=d)len=min(len,d-(r-l)+1);
	}
}lis;


int main(){
	read(n,m,d);
	rep(i,1,n)read(P[i],Q[i]);
	rep(i,1,m)read(R[i],S[i]);
	rep(i,1,n)visx[P[i]]=1,visy[Q[i]]=1;
	rep(i,1,m)lst[S[i]][R[i]]=R[i],lst[S[i]][R[i]+d]=R[i]+d;
	rep(i,0,d-1)rep(j,1,2*D-1)lst[i][j]=max(lst[i][j-1],lst[i][j]);
	int ans=1e9;
	rep(l,0,d){
		lis.build();int bg=0;
		per(r,l-1+d,0)if(visx[r%d]){bg=r;break;}
		rep(i,0,d-1)if(!visy[i]){
			if(lst[i][l-1+d]<bg)lis.del(i);
			else vu[lst[i][l-1+d]].eb(i);
		}
		rep(r,bg,l-1+d){
			for(auto x:vu[r])lis.del(x);
			ans=min(ans,(r-l+1)*min(lis.len,(lis.tl-lis.hd+1)));
			vu[r].clear();
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

