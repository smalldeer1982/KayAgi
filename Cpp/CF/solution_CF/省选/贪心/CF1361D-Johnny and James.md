# Johnny and James

## 题目描述

James Bond, Johnny's favorite secret agent, has a new mission. There are $ n $ enemy bases, each of them is described by its coordinates so that we can think about them as points in the Cartesian plane.

The bases can communicate with each other, sending a signal, which is the ray directed from the chosen point to the origin or in the opposite direction. The exception is the central base, which lies at the origin and can send a signal in any direction.

When some two bases want to communicate, there are two possible scenarios. If they lie on the same line with the origin, one of them can send a signal directly to the other one. Otherwise, the signal is sent from the first base to the central, and then the central sends it to the second base. We denote the distance between two bases as the total Euclidean distance that a signal sent between them has to travel.

Bond can damage all but some $ k $ bases, which he can choose arbitrarily. A damaged base can't send or receive the direct signal but still can pass it between two working bases. In particular, James can damage the central base, and the signal can still be sent between any two undamaged bases as before, so the distance between them remains the same. What is the maximal sum of the distances between all pairs of remaining bases that 007 can achieve by damaging exactly $ n - k $ of them?

## 说明/提示

In the first example, in an optimal solution Bond doesn't destroy bases with indices $ 4 $ and $ 6 $ (marked in orange):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361D/29ad68544f86790b6a0b555f8c0a2679b5e08738.png)The following picture represents an optimal solution for the second example. These bases are are not destroyed: $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ (marked in orange).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361D/92cf75fde42075888e781e37ed18062bceac6b94.png)An optimal solution for the third test is visible in the picture. Only bases $ 3 $ , $ 4 $ , $ 5 $ are destroyed. Again, the not destroyed bases are marked in orange.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361D/123419ed05a0a9745e9c96cf4f22f1857630f66d.png)

## 样例 #1

### 输入

```
6 2
0 0
1 1
2 2
3 3
0 1
0 2```

### 输出

```
6.24264069```

## 样例 #2

### 输入

```
6 5
0 0
1 1
2 2
3 3
0 1
0 2```

### 输出

```
32.62741700```

## 样例 #3

### 输入

```
13 10
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0
8 0
9 0
0 -2
0 1
0 2```

### 输出

```
237.00000000```

## 样例 #4

### 输入

```
10 5
2 2
4 4
3 5
6 10
0 5
0 0
5 0
10 0
0 10
4 7```

### 输出

```
181.52406315```

# 题解

## 作者：enucai (赞：2)

## Preface

不知道另一篇题解在写啥，为啥点编号能当作个数来乘的。

## Analysis

首先有一个事实，这棵树是有一堆链直接与根相连构成的。

考虑每个被选中的点对答案的贡献。我们称一个点 $u$ 到原点的距离是 $dis_u$。

假设这个点所在的链上的点的个数是 $U$，这个点的儿子数量（包括她自己）是 $V$，除这个点所在链外的选中的点个数是 $W$，那么这个点对答案的贡献是：

$$
W\cdot dis_u-(V-1)\cdot dis_u+(U-V)\cdot dis_u
$$

解释一下：

- 第一部分表示这个点到别的链上的点的距离贡献。即对于一对不在同一个链上的点，她们的距离可以被拆成两个点分别到根的距离之和。因此是 $W\cdot dis_u$。

- 后两部分是同一条链上的点的贡献。即对于在同一链上的一对点，距离是深度大的点到根的距离 $-$ 深度小的点到根的距离。他作为深度小的点出现过 $V-1$ 次，深度大的点出现过 $U-V$ 次，因此贡献是 $-(V-1)\cdot dis_u+(U-V)\cdot dis_u$。

将式子化简一下，得到一个点得贡献：

$$
(W-2V+U+1)\cdot dis_u=(k-2V+1)\cdot dis_u
$$

所以一个点对答案的贡献就清晰了。

我们发现如果一个点的儿子个数 $\le\lfloor\frac{k}{2}\rfloor$，那么这个点对答案的贡献是正的，否则是非正的。

于是我们得出了选点的策略：每条链上先选深度最大的 $\lfloor\frac{k}{2}\rfloor$ 个点，再选深度小的点（这些点贡献是非正的）。

那么我们可以算出选择每个点后答案的变化量：

- 对于前 $\lfloor\frac{k}{2}\rfloor$ 个深度从大向小取的点，贡献对着式子直接算即可。

- 对于深度从小向大取的点，首先对于她上面的点，子树大小都 $+1$，所以要减两倍的祖先节点深度和，再加上自己的贡献。

将所有点的 “增加后对答案的变化量” 从大到小排序，取前 $k$ 大的即可。

## Code

```cpp
#define int long long
const int N=500010;
int n,m,k,tot,cur[N];
struct node{
  int x,y,dx,dy;
  double dis(){
    return sqrt(x*x+y*y);
  }
}a[N];
map<pair<int,int>,int> mp;
vector<int> v[N];
vector<double> ans;
void solve(int id){
  m=0;
  for(int i:v[id]) cur[++m]=i;
  sort(cur+1,cur+m+1,[](int x,int y){
    return a[x].dis()>a[y].dis();
  });
  int lim=min(k/2,m);
  double sum=0;
  rep(i,1,lim){
    int idx=cur[i];
    ans.eb(a[idx].dis()*(k-2*i+1));
  }
  per(i,m,lim+1){
    int idx=cur[i];
    double sub=2*sum,add=(k-2*(lim+1)+1)*a[idx].dis();
    ans.eb(add-sub),sum+=a[idx].dis();
  }
}
signed main(){IOS;
  cin>>n>>k;
  rep(i,1,n){
    cin>>a[i].x>>a[i].y;
    if(a[i].x==0&&a[i].y==0){
      a[i].dx=a[i].dy=0;
    }else if(a[i].x==0){
      a[i].dx=0,a[i].dy=a[i].y/abs(a[i].y);
    }else if(a[i].y==0){
      a[i].dx=a[i].x/abs(a[i].x),a[i].dy=0;
    }else{
      int d=gcd(a[i].x,a[i].y);
      a[i].dx=a[i].x/d,a[i].dy=a[i].y/d;
    }
    if(!mp[mkp(a[i].dx,a[i].dy)])
      mp[mkp(a[i].dx,a[i].dy)]=++tot;
    v[mp[mkp(a[i].dx,a[i].dy)]].eb(i);
  }
  rep(i,1,tot) solve(i);
  sort(ALL(ans)),reverse(ALL(ans));
  double res=0;
  rep(i,0,k-1) res+=ans[i];
  cout<<fixed<<setprecision(8)<<res;
}
```

---

## 作者：loveJY (赞：0)

首先不难想出建树方法：处理出原点到所有点的射线的方向向量，然后如果这个向量相同就说明他们在一条射线上，存入一个vector即可，而方向向量的表示可以钦定$x=1$然后$y=x/y$，是高中数学基础。。。

处理好这样几个vector后,每个vector内要按照到原点的距离排序，那么每个树链就是从vector顶到底

然后我们在考虑选取k个使得他们两两在树上的距离和最大

发现：$n \leq 1e6,k \leq 1e6$/jk

朴素的树形DP是O(nk)的，所以考虑这个树的特殊性质：完全由链构成

既然由链构成其实我们能很容易算出**每个点到根的距离**对于答案的贡献,这一定是他儿子中选的点数$i*(k-i)$

又不难看出，在一条链上，这个"**每个点到根的距离**"是单调递减的，也就是说：我们在一条链上的选择方案可能是确定的，而且大概率是从链底到链顶这样选

设树链包括点的集合为S，假如我们按照深度依次访问的话，贡献是：

$$\sum_{u \in S}u*(k-u)*dis_u$$

其中$u*(k-u)$就是上面说的那个

$u*(k-u)$好像当u在$[1,k/2]$变化时单调递增

而当$u>k/2$的时候，好像又递减了，当然不行，所以我们要确保每时每刻这个$u$都小于$k/2$

那么一条链上选择的方案就能看出了：

> 先选择最深的$\frac k 2$个点，如果还能选的话再选最浅的$\frac k 2$个点

于是？一个自然的想法是看看**能选**的条件是什么，于是我们要计算一个点选后的**增量**

1. 最深的$\frac k 2$个点

此时我们选中这个点可以放心的用$(k-u)$(因为他下面的点一定都选了)计算一部分贡献

然而这样会多算，因为相当于在链上选的点多了一个，而他下面那些点v对于他的贡献还是$dis_v$，现在应该是$dis_v-dis_u$了

所以是$(k-u)*dis_u-u*dis_u$

2. 最浅的$\frac k 2$个点

显然第一类情况也是一样的

而此时我们又要考虑他上面的点v对于他的贡献要减小。。。

原来是$dis_v$，现在变成了$dis_u-dis_v$

差值是$dis_u-2*dis_v$

统计一个$dis_v$的前缀和即可！

code:


```cpp

#include<bits/stdc++.h>
#define int long long
#define db double
#define mkp(x,y) (make_pair(x,y))
#define pii pair<int,int>
using namespace std;
const int MAXN=5e5+7;
const db eps=1e-9;
int n,k,tot,sm;
map<pii,int> mp;
db ans;
struct rec {
	int x,y;
	db dis;
	inline void gdis() {
		dis=sqrt(x*x+y*y);
	}
} e[MAXN];
db mv[MAXN];
vector<int> v[MAXN];
inline bool qwq(int x,int y) {
	return e[x].dis-e[y].dis<eps;
}
inline int gcd(int x,int y) {
	if(x<0)x=-x;
	if(y<0)y=-y;
	return y==0?x:gcd(y,x%y);
}
inline void solve(int o) {
	int m=v[o].size();
	sort(v[o].begin(),v[o].end(),qwq);
	reverse(v[o].begin(),v[o].end());
	db s=0;
	for(int i=0; i<min(m,k/2); ++i) {
		int u=v[o][i];
		mv[++sm]=e[u].dis*(k-i-1)-e[u].dis*i;
	}
	for(int i=k/2; i<m; ++i) {
		int u=v[o][m-i+k/2-1];
		mv[++sm]=e[u].dis*(k-i-k/2-1)-s*2+e[u].dis*(i-k/2);
		s+=e[u].dis;
	}
	return;
}
signed main() {
	scanf("%lld%lld",&n,&k);
	for(int i=1,x,y; i<=n; ++i) {
		scanf("%lld%lld",&x,&y);
		e[i].x=x;
		e[i].y=y;
		e[i].gdis();
		if(x==0 && y==0) {
			v[++tot].push_back(i);
			continue;
		}
		int d=gcd(x,y);
		x/=d;
		y/=d;
		if(mp.find(mkp(x,y))!=mp.end()) {
			v[mp[mkp(x,y)]].push_back(i);
		} else {
			++tot;
			mp[mkp(x,y)]=tot;
			v[tot].push_back(i);
		}
	}
	for(int i=1; i<=tot; ++i)solve(i);
	sort(mv+1,mv+sm+1);
	for(int i=sm; i>=sm-k+1; --i)ans+=mv[i];
	printf("%.10lf\n",ans);
	return 0;
}


```


---

