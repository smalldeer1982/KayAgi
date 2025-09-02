# Drone Photo

## 题目描述

Today, like every year at SWERC, the $ n^2 $ contestants have gathered outside the venue to take a drone photo. Jennifer, the social media manager for the event, has arranged them into an $ n\times n $ square. Being very good at her job, she knows that the contestant standing on the intersection of the $ i $ -th row with the $ j $ -th column is $ a_{i,j} $ years old. Coincidentally, she notices that no two contestants have the same age, and that everyone is between $ 1 $ and $ n^2 $ years old.

Jennifer is planning to have some contestants hold a banner with the ICPC logo parallel to the ground, so that it is clearly visible in the aerial picture. Here are the steps that she is going to follow in order to take the perfect SWERC drone photo.

- First of all, Jennifer is going to select four contestants standing on the vertices of an axis-aligned rectangle.
- Then, she will have the two younger contestants hold one of the poles, while the two older contestants will hold the other pole.
- Finally, she will unfold the banner, using the poles to support its two ends. Obviously, this can only be done if the two poles are parallel and do not cross, as shown in the pictures below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/0c66204e6b46ec54ef4970646675d11080bec4fc.png)Being very indecisive, Jennifer would like to try out all possible arrangements for the banner, but she is worried that this may cause the contestants to be late for the competition. How many different ways are there to choose the four contestants holding the poles in order to take a perfect photo? Two choices are considered different if at least one contestant is included in one but not the other.

## 说明/提示

In the first sample, there are $ 4 $ contestants, arranged as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/e7e2a81b002e3a2bac197b62545c6ad11a69f7a8.png)There is only one way to choose four contestants, with one pole held by contestants aged $ 1 $ and $ 2 $ and the other one by contestants aged $ 3 $ and $ 4 $ . But then, as we can see in the picture, the poles cross.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/626f6c3701e63bf775605758d69491672a9a7858.png)Since there is no valid way to choose four contestants, the answer is $ 0 $ .

In the second sample, the $ 4 $ contestants are arranged as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/52911f8374a060499e28117449cb8c5d56740ef4.png)Once again, there is only one way to choose four contestants, but this time the poles don't cross.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/3dbefc9c39c8ce185cc2f953aaf6d4a443ef99d4.png)Therefore, the answer is $ 1 $ .

In the third sample, the $ 9 $ contestants are arranged as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/0b2bd9d2be4297c7b6df8f81316d0db59aa26e9e.png)There are $ 6 $ ways of choosing four contestants so that the poles don't cross, as shown in the following pictures.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1662N/72f4724e30f1d908a8873c65b21364979d578b9b.png)

## 样例 #1

### 输入

```
2
1 3
4 2```

### 输出

```
0```

## 样例 #2

### 输入

```
2
3 2
4 1```

### 输出

```
1```

## 样例 #3

### 输入

```
3
9 2 4
1 5 3
7 8 6```

### 输出

```
6```

# 题解

## 作者：I_am_Accepted (赞：3)

### Preface

这谁又想得到呢！（哭腔）

### Analysis

考虑如何简化这个举横幅 $4$ 人的年龄关系。

------------

**引理：** 给矩形四条边定向，从年轻 $\to$ 年长（这样明显是 DAG），将 $4$ 人分为了

* $\mathtt{A}$ 入度 $2$ 出度 $0$

* $\mathtt{B}$ 入度 $1$ 出度 $1$

* $\mathtt{C}$ 入度 $0$ 出度 $2$

三类。其中 $\mathtt{B}$ 类点 $0$ 或 $2$ 个，且当且仅当 $\mathtt{B}$ 类点在总共 $4$ 个中有 $2$ 个时，横幅有效。

**证明：** 首先显然由点的度得出 $\mathtt{B}$ 类点 $0$ 或 $2$ 个。

若 $0$ 个，则必然是类似如下形态的↓

![](https://cdn.luogu.com.cn/upload/image_hosting/e0i9qpny.png)

不成立。

若 $2$ 个，则必然是类似如下两种形态之一的↓

![](https://cdn.luogu.com.cn/upload/image_hosting/88gyy3hg.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/b02pa97y.png)

成立。

------------

所以，统计每个人当 $\mathtt{B}$ 类点的次数之和除以 $2$ 即为答案。

而一个人当 $\mathtt{B}$ 类点的次数为

$$
a(n-1-b)+b(n-1-a)
$$

其中 $a,b$ 分别表示这个人当前行、列比她年纪小的人数。

### Code

```cpp
int r[N],c[N],n; 
pair<int,int> pos[N*N];
signed main(){IOS;
	cin>>n;
	int x,y;
	For(i,1,n){
		For(j,1,n){
			cin>>x;
			pos[x]=mkp(i,j);
		}
	} 
	int ans=0;
	For(i,1,n*n){
		x=r[pos[i].fir]++;
		y=c[pos[i].sec]++;
		ans+=x*(n-1-y)+y*(n-1-x); 
	}
	cout<<ans/2<<endl;
return 0;}
```

---

## 作者：lsj2009 (赞：2)

### Problem

人类智慧题。

我们考虑对于一个矩形的一个角，我们将其向两个与他相邻的角当中比他小的连边，如果说存在一个点出度为 $2$，我们称这为一个不合法角；显然一个不合法矩阵里恰有两个不合法角，一个合法矩形里恰有一个不合法角。

设有 $a$ 个不合法矩形，$b$ 个合法矩形，$c$ 个不合法角，易得方程：

$$
\begin{cases}
 & 2a+b=c\\
 & a+b=\frac{n^2(n-1)^2}{4}
\end{cases}
$$

得 $b=\frac{n^2(n-1)^2}{2}-c$。

那么我们只需要求出不合法角数量即可。

考虑将所有点按从小到大的顺序加入，每当加入一个点时，如果同行被加进来的点已经有 $x$ 个，同列已经被加进来的点已经有 $y$ 个，则在 $x$ 个点中任选一个、$y$ 个点中任选一个，都可以和刚才加入得点组成一个不合法角，即不合法角个数为 $\sum xy$，$x$ 和 $y$ 可以用桶时时统计。

然后就做完了，复杂度 $\Theta(n^2\log{n^2})$，瓶颈在于排序，桶排可以做到 $\Theta(n^2)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e3+5;
int a[N],b[N];
struct node {
    int val,x,y;
    bool operator < (const node &tmp) const {
        return val<tmp.val;
    }
}; vector<node> vec;
signed main() {
    int n;
    scanf("%lld",&n);
    rep(i,1,n) {
        rep(j,1,n) {
            int x;
            scanf("%lld",&x);
            vec.push_back({x,i,j});
        }
    }
    sort(vec.begin(),vec.end());
    int ans=0;
    for(auto t:vec) {
        int x=t.x,y=t.y;
        ans+=a[x]*b[y];
        ++a[x]; ++b[y];
    }
    printf("%lld\n",(n-1)*n*(n-1)*n/2-ans);
    return 0;
}
```

---

## 作者：周子衡 (赞：2)

一道小清新题。

直接枚举是 $O(n^4)$ 的，显然会超时，我们需要进一步观察性质。可以发现，我们很关心同一行、同一列两个数的大小关系。不妨对同一行的两个数之间，从小的向大的连一条有向边。可以发现：

- 对于符合要求的情况，如下左图（这里我们假设上面两个数比下面两个数小），那么不论上、下两个数之间具体的大小关系，一定在恰好 $1$ 个顶点处形成了“大大角”（也就是一个数比这个矩形中同行、同列的对应元素都大）。
- 对不符合要求的情况，如下右图，那么一定在恰好 $2$ 个顶点处形成“大大角”。

![](https://cdn.luogu.com.cn/upload/image_hosting/mcm6xyn6.png)

我们可以计算出所有“大大角”的数量。具体而言，对每个元素 $i$，计算与其同行的元素中比该元素小的数量，记为 $a_i$；与其同列的元素中比该元素小的数量，记为 $b_i$；那么在 $i$ 处总共形成了 $a_ib_i$ 个“大大角”，总的数量即为 $S=\sum a_ib_i$。设总共的子矩形数量为 $C=(\dfrac{n(n-1)}{2})^2$，解二元一次方程可得答案 $=2C-S$。

```cpp
#include<cstdio>
#include<vector>

using namespace std;

pair<int,int> P[3000000];
long long r[3000],c[3000];
int a[3000][3000];

int main()
{
	int n=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++){scanf("%d",&a[i][j]);P[a[i][j]]=make_pair(i,j);}
	}
	long long cnt_ang=0;
	for(int i=1;i<=n*n;i++)
	{
		int x=P[i].first,y=P[i].second;
		cnt_ang+=r[x]*c[y];
		r[x]++,c[y]++;
	}
	long long sum=(long long)n*(n-1)/2*n*(n-1)/2;
	printf("%lld",2*sum-cnt_ang);
}
```

---

## 作者：daniEl_lElE (赞：0)

设符合要求的矩形共有 $x$ 个，则不符合要求的矩形共有 $tot-x$ 个，其中 $tot$ 表示总的矩形数量。

考虑从小到大添加每个数。对于符合要求的矩形，我们发现在加点过程中，该点与其他点形成直角三角形的方案只有 $1$ 种（即，加入最大的点时才会与其他两个点形成直角三角形），而对于不符合要求的矩形，这样的直角三角形方案共有 $2$ 种（加入次大及最大的点时符合要求）。计算出直角三角形的数量 $cnt$，我们得到 $x+2(tot-x)=cnt$，即 $x=2tot-cnt$。

总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int valx[3000005],valy[3000005];
int cntx[2005],cnty[2005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n; cin>>n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		int a; cin>>a;
		valx[a]=i,valy[a]=j;
	}
	int tot=n*(n-1)/2*n*(n-1)/2,num=0;
	for(int k=1;k<=n*n;k++){
		int i=valx[k],j=valy[k];
		num+=cntx[i]*cnty[j];
		cntx[i]++,cnty[j]++;
	}
	cout<<2*tot-num;
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

## sol

结论题。

观察合法矩阵的四个角，对于相邻的两个角，从较小向较大的连一条有向边。

把一条入边一条出边的称为特殊点，分类：

- $0$ 个特殊点：只有一种可能，且不合法；

![QQ截图20240320144834.png](https://cdn.acwing.com/media/article/image/2024/03/20/139576_e6195ea9e6-QQ截图20240320144834.png) 

- $1$ 个特殊点：没有；
- $2$ 个特殊点：两种情况，均合法；

![QQ截图20240320145316.png](https://cdn.acwing.com/media/article/image/2024/03/20/139576_8c6e5c70e6-QQ截图20240320145316.png) 

![QQ截图20240320145200.png](https://cdn.acwing.com/media/article/image/2024/03/20/139576_92659ef3e6-QQ截图20240320145200.png) 

- $3$ 个特殊点：没有；
- $4$ 个特殊点：没有。

所以一个矩阵为合法矩阵当且仅当有 $2$ 个特殊点，由于不存在有 $1,3,4$ 个特殊点的矩阵，所以计算的是有特殊点的矩阵个数。

对于一个点 $(x,y)$ 我们累加它在几个矩阵中为特殊点，设 $x$ 行有 $c$ 个数小于 $a_{x,y}$，$y$ 行有 $d$ 个数小于 $a_{x,y}$，那么 $ans$ 就累加

$$c(n-d-1)+d(n-c-1)$$

最后答案除以 $2$，因为每个矩阵被计算了两次。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1510;
int n, a[N][N], x[N][N], y[N][N];
int tr[N * N];

void add(int x, int k) {
	for (int i = x; i <= n * n; i += i & -i) tr[i] += k;
}

int qry(int x) {
	int res = 0;
	while (x) {
		res += tr[x];
		x -= x & -x;
	}
	return res;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ )
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 1; j <= n; j ++ ) add(a[i][j], 1);
		for (int j = 1; j <= n; j ++ ) x[i][j] = qry(a[i][j] - 1);
		for (int j = 1; j <= n; j ++ ) add(a[i][j], -1);
	}
	for (int j = 1; j <= n; j ++ ) {
		for (int i = 1; i <= n; i ++ ) add(a[i][j], 1);
		for (int i = 1; i <= n; i ++ ) y[i][j] = qry(a[i][j] - 1);
		for (int i = 1; i <= n; i ++ ) add(a[i][j], -1);
	}
	long long ans = 0;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ )
			ans += x[i][j] * (n - 1 - y[i][j]) + y[i][j] * (n - 1 - x[i][j]);
	printf("%lld\n", ans / 2);
	return 0;
}
```

---

