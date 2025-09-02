# Nauuo and Portals

## 题目描述

Nauuo 是一个喜欢玩与传送门相关游戏的女孩。

有一天，她玩了这样一个游戏。

在一个 $n\times n$ 的网格中，行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $n$。我们用 $(r,c)$ 表示第 $r$ 行第 $c$ 列的格子。

一个传送门由一对门组成。你可以从其中一扇门传送到另一扇门，并且不会改变你的前进方向。更正式地说，如果你走进一个有门的格子，你会被传送到同一传送门的另一扇门所在的格子，然后继续以原来的方向进入下一个格子。一个格子里不能有多于一扇门。

“下一个格子”指的是你面朝的方向上最近的格子。例如，如果你面朝下方，$(2,5)$ 的下一个格子是 $(3,5)$。

如果你走进一个没有门的格子，你必须继续以当前方向进入下一个格子。如果下一个格子不存在，你就会离开网格。

你需要在网格中设置一些（可能为零）传送门，使得：如果你从 $(i,1)$ 面朝右进入，你最终会从 $(r_i,n)$ 离开网格；如果你从 $(1,i)$ 面朝下进入，你会从 $(n,c_i)$ 离开网格。

保证 $r_{1..n}$ 和 $c_{1..n}$ 都是 $n$ 的一个排列。$n$ 的一个排列是一个长度为 $n$ 的数列 $p_1,p_2,\ldots,p_n$，其中每个 $1$ 到 $n$ 的整数恰好出现一次。

她在玩游戏时感到困惑，你能帮她找到一种方案吗？

## 说明/提示

示例 1

带有相同字母的格子是一对传送门。你可以这样设置传送门：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1172D/de3b611b4d4e6cd05ce6ba2b1f72d4389000aa30.png)

它满足要求，因为：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1172D/49650c112ee3bd1b70e4b7de2986ac0cdfbc6ade.png)

示例 2

你可以这样设置传送门：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1172D/a92305b6c403f6d70c71ef63077c9a38589be5ff.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 3 2
3 1 2
```

### 输出

```
2
1 1 1 3
2 2 3 1```

## 样例 #2

### 输入

```
5
3 1 5 4 2
4 2 1 3 5
```

### 输出

```
3
1 1 3 4
2 2 3 2
2 3 5 1
```

# 题解

## 作者：mrsrz (赞：6)

考虑把 $n\times n$ 的问题转化为 $(n-1)\times(n-1)$ 的问题。

以最开始为例，我们考虑要走到 $(1,n+1)$ 的人所在行 $p$ 和要走到 $(n+1,1)$ 的人所在列 $q$。

那么我们如图所示，建造传送门 $(p,1),(1,n)$ 以及 $(1,q),(n,1)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/y83sdfs4.png)

那么，行 $p$ 和列 $q$ 的人显然能够走到它的合法位置，而原来在第一行的人将会到第 $n$ 行，第 $n$ 行的人将会到第 $p$ 行。同理在第一列的人将会到第 $n$ 列，第 $n$ 列的人将会到第 $q$ 列。

再考虑一些特殊情况，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/40akdmt6.png)

表示有一个人是从第 $n$ 行走到第一行（或者第 $n$ 列走到第一列，同理）。那么只需要开一对传送门即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/qa5rhn1c.png)

这种情况就无需开传送门了。

以上，我们花费了 $0\sim 2$ 扇传送门，使得最终到第一行和第一列的人满足了条件，并令第 $2\sim n$ 行和 $2\sim n$ 列都保持每行/列有且仅有一个人。那么我们就转化为了一个 $(n-1)\times (n-1)$ 的子问题。继续按照上述方法讨论即可。到 $1\times 1$ 的时候停止。

时间复杂度 $O(n)$。

## Code：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1005;
int n,R[N],C[N],top,iR[N],iC[N];
struct doors{
    int r1,c1,r2,c2;
}d[N<<1];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>R[i],iR[R[i]]=i;
    for(int i=1;i<=n;++i)cin>>C[i],iC[C[i]]=i;
    for(int i=1;i<n;++i){
        if(R[i]==i&&C[i]==i)continue;
        if(iR[i]==n&&iC[i]==n){
            d[++top]=(doors){i,n,n,i};
            R[n]=R[i],C[n]=C[i];
            iR[R[n]]=n;iC[C[n]]=n;
            continue;
        }
        if(iC[i]==n){
            d[++top]=(doors){iR[i],i,i,n};
            C[n]=C[i];iC[C[n]]=n;
            R[iR[i]]=R[i],iR[R[iR[i]]]=iR[i];
            continue;
        }
        if(iR[i]==n){
            d[++top]=(doors){i,iC[i],n,i};
            R[n]=R[i];iR[R[n]]=n;
            C[iC[i]]=C[i],iC[C[iC[i]]]=iC[i];
            continue;
        }
        d[++top]=(doors){iR[i],i,i,n},
        d[++top]=(doors){i,iC[i],n,i};
        int r=iR[i],c=iC[i];
        R[r]=R[n],R[n]=R[i];
        C[c]=C[n],C[n]=C[i];
        iR[R[r]]=r,iC[C[c]]=c;
        iR[R[n]]=n,iC[C[n]]=n;
    }
    cout<<top<<'\n';
    for(int i=1;i<=top;++i)
        cout<<d[i].r1<<' '<<d[i].c1<<' '<<d[i].r2<<' '<<d[i].c2<<'\n';
    return 0;
}
```

---

## 作者：ouuan (赞：3)

考虑一个 $n*n$ 的问题如何转化成 $(n-1)\times(n-1)$：满足第一行和第一列。

如果已经满足直接变成 $(n-1)\times(n-1)$。

否则找到第一行中应该放在第一列那个和第一列中应该放在第一行那个，这两个位置各放一个传送门即可。

这题可以 $\mathcal O(n)$ 做，但 checker 要 $\mathcal O(n^2)$。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1010;

struct Portal
{
	int x, y, p, q;
	Portal(int _x, int _y, int _p, int _q): x(_x), y(_y), p(_p), q(_q) {}
};
vector<Portal> ans;
int n, a[N], b[N], c[N], d[N], ra[N], rb[N], rc[N], rd[N];

int main()
{
	int i;
	
	scanf("%d", &n);
	
	for (i = 1; i <= n; ++i)
	{
		scanf("%d", b + i);
		rb[b[i]] = i;
	}
	for (i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		ra[a[i]] = i;
	}
	for (i = 1; i <= n; ++i) c[i] = d[i] = rc[i] = rd[i] = i;
	
	for (i = 1; i < n; ++i)
	{
		if (c[i] == ra[i] && d[i] == rb[i]) continue;
		ans.push_back(Portal(i, rc[ra[i]], rd[rb[i]], i));
		int t1 = c[i];
		int t2 = d[i];
		swap(c[i], c[rc[ra[i]]]);
		swap(d[i], d[rd[rb[i]]]);
		swap(rc[ra[i]], rc[t1]);
		swap(rd[rb[i]], rd[t2]);
	}
	
	printf("%d\n", ans.size());
	for (auto k : ans) printf("%d %d %d %d\n", k.x, k.y, k.p, k.q);
	
	return 0;
}
```

---

## 作者：skydogli (赞：2)

有点震撼的构造题……

如果考虑整体构造的话非常难办，所以我们考虑能否一层层处理，每次处理之后转化成一个子问题。

假设我们当前处理到第 $i$ 行第 $i$ 列，我们显然要把 $r_j=i$ 及 $c_k=i$ 的光线转过来（如果 $j=i$ 且 $k=i$ 的话不管就好了）。我们在第 $i$ 行第 $j$ 列放一个，第 $k$ 行第 $i$ 列放一个，这样的话这一行这一列的限制就满足了，而且传送门都放在第 $i$ 行与第 $i$ 列，不会对其它光线造成影响，只是原本在这一行/列的光线到了别的地方，交换一下即可。我为了方便，直接用了 $O(n^2)$ 的实现方式。

~~构造题怎么做啊/ll~~

```cpp#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define piii pair<pii,pii >
#define mp make_pair
#define x first
#define y second
#define MN 1005
int n,a[MN],b[MN];
vector<piii >ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&b[i]);
	}

	for(int i=1;i<n;++i){
		if(a[i]==i&&b[i]==i)continue;
		int ma=0,mb=0;
		for(int j=i;j<=n;++j)
			if(a[j]==i)ma=j;
		for(int j=i;j<=n;++j)
			if(b[j]==i)mb=j;
		assert(ma&&mb);
		assert(i!=mb||i!=ma);
		ans.push_back(mp(mp(i,mb),mp(ma,i)));
		swap(a[ma],a[i]);
		swap(b[mb],b[i]);
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<ans.size();++i){
		printf("%d %d %d %d\n",ans[i].x.x,ans[i].x.y,ans[i].y.x,ans[i].y.y);
	}
	return 0;
}

```

---

## 作者：LCuter (赞：1)

先不看竖着的限制，如果仅需要满足横着的限制，那么我们每次在同一列放下一个传送门，相当于交换排列的两个位置，我们要通过这种操作把一个顺序的排列变成给定的排列。这样是容易达成的，我们考虑每次将一个数换到它本来的位置，那么只需要至多 $n-1$ 次，所以我们可以将这些传送门放在不同列中。

现在加入了竖着的限制，考虑一对传送门 $(x_1,y_1),(x_2,y_2)$，它的实际意义是交换横着的排列的 $(x_1,x_2)$，交换竖着的排列 $(y_1,y_2)$。

我们希望依次将 $1\sim n$ 的位置填好，假设现在是第 $i$ 次操作，横目标排列的第 $i$ 位是 $x$，竖目标排列的第 $i$ 位是 $y$。我们先找到 $x$ 在横现在排列中的位置 $p_x$ 与 $y$ 在竖现在排列中的位置 $p_y$，然后 $(i,p_x),(p_y,i)$ 就行了，注意判掉两点相等的情况。

PS：题目中给出的排列并非目标排列，只是说某个值要在某个位置。

---

## 作者：NKL丶 (赞：0)

## Description

给出一个 $n \times n$ 的网格和 $n$ 个形如 $(r_i,n)$ 和 $n$ 个形如 $(c_i,n)$ 的要求，现在求一种建立若干对传送门的方案，使得对于第 $i$ 个要求，有从 $(i,1)$ 开始向右走能走到 $(r_i,n)$，从 $(1,i)$ 开始向下走能走到 $(n,c_i)$。（$1 \le n \le 10^3$）

## Solution

我们将原问题逐层考虑，把 $n \times n$ 的问题转化为 $(n-1) \times (n-1)$ 的问题。这时候只需要考虑满足第 1 行和第 1 列的限制，即找到到达第 1 行的那一行 $r$，以及到达第 1 列的那一列 $c$，建立一对坐标为 $(r,1),(1,c)$ 的传送门即可，然后处理放置传送门后限制的变化即可。

## [Code](https://www.luogu.com.cn/paste/k5y2w5f1)

---

