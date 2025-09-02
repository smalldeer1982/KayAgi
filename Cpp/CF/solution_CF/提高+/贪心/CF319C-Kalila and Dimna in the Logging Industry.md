# Kalila and Dimna in the Logging Industry

## 题目描述

Kalila and Dimna are two jackals living in a huge jungle. One day they decided to join a logging factory in order to make money.

The manager of logging factory wants them to go to the jungle and cut $ n $ trees with heights $ a_{1},a_{2},...,a_{n} $ . They bought a chain saw from a shop. Each time they use the chain saw on the tree number $ i $ , they can decrease the height of this tree by one unit. Each time that Kalila and Dimna use the chain saw, they need to recharge it. Cost of charging depends on the id of the trees which have been cut completely (a tree is cut completely if its height equal to 0). If the maximum id of a tree which has been cut completely is $ i $ (the tree that have height $ a_{i} $ in the beginning), then the cost of charging the chain saw would be $ b_{i} $ . If no tree is cut completely, Kalila and Dimna cannot charge the chain saw. The chainsaw is charged in the beginning. We know that for each $ i $ < $ j $ , $ a_{i}&lt;a_{j} $ and $ b_{i}&gt;b_{j} $ and also $ b_{n}=0 $ and $ a_{1}=1 $ . Kalila and Dimna want to cut all the trees completely, with minimum cost.

They want you to help them! Will you?

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 3 2 0
```

### 输出

```
25
```

## 样例 #2

### 输入

```
6
1 2 3 10 20 30
6 5 4 3 2 0
```

### 输出

```
138
```

# 题解

## 作者：Warriors_Cat (赞：6)

一个较为普通的斜率优化？不过转换问题还是有点巧的。

[题目传送门](https://www.luogu.com.cn/problem/CF319C)

### $Solution:$

由于 $b_n=0$ 且 $n$ 为这些点编号的最大值，所以我们就把问题转换为砍倒第 $n$ 棵树的最小成本。

考虑定义 $f_i$ 为砍倒第 $i$ 棵树的最小成本，枚举一个小于 $i$ 的 $j$，钦定 $j$ 为次大编号值，于是可以列出状态转移方程：

$$f_i = \min_{j=1}^{i-1}\{f_j+b_j\times a_i\}$$

很显然单纯暴力是 $O(n^2)$ 的，不足以通过此题，于是考虑优化，这里运用的是斜率优化。

若有 $k < j$ 且 $k$ 比 $j$ 更优，那么有不等式：

$$f_k + b_k\times a_i < f_j + b_j\times a_i$$

然后整理不等式：

$$\dfrac{f_j - f_k}{b_k - b_j} > a_i$$

这已经是一个标准的斜率优化式了。

因为这里 $a_i$ 是单调递增的，所以维护一个斜率值单调递增的单调队列即可，时间复杂度为 $O(n)$。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define ll long long
#define x1 x_csyakioi_1
#define x2 x_csyakioi_2
#define y1 y_csyakioi_1
#define y2 y_csyakioi_2
#define y0 y_csyakioi_0
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 100010;
int n, a[N], b[N], q[N], head, tail; ll f[N];
inline double calc(int x, int y){ return 1.0 * (f[y] - f[x]) / (b[x] - b[y]); } // x < y 
int main(){
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) b[i] = read();
	q[head = tail = 1] = 1;
	for(int i = 2; i <= n; ++i){
		while(head < tail && calc(q[head], q[head + 1]) < a[i]) ++head;//这里运用了 a_i 单调递增的性质
		f[i] = f[q[head]] + 1ll * a[i] * b[q[head]];
		while(head < tail && calc(q[tail], i) < calc(q[tail - 1], q[tail])) --tail;
		q[++tail] = i;
	}
	printf("%lld", f[n]);
	return 0;
}
```


---

## 作者：whiteqwq (赞：3)

[CF319C Kalila and Dimna in the Logging Industry](https://www.luogu.com.cn/problem/CF319C)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1750042)

## 题意
- 给定$n$棵树，高度为$a_1$到$a_n$，权值为$b_1$到$b_n$，当一颗树的$a$为$0$时就说它被砍倒了；
- 有一个电锯，每一次砍伐树会让一棵树的高度$-1$；
- 砍伐的费用为当前砍倒的编号的最大的树的$b$，第一次砍伐不需要费用；
- 保证$a_i<a_{i+1},b_i>b_{i+1},a_1=1,b_n=0$，求砍倒所有树的最小费用。
- 数据范围：$1\leqslant n\leqslant 10^5$。

## 分析
很显然，我们第一次砍的一定是第一棵树，且砍倒最后一棵树以后就不需要任何费用了，这样，题意就转化为如何花费最小的费用砍倒第$n$棵树。

有一个很显然的贪心思想，我们砍树一定从前往后砍（中间可以跳过一些树），因为我们砍这棵树一定无法更新砍树的费用。

设$f_i$为砍倒第$i$棵树的费用，那么可以列出转移方程$f_i=\min_{j=1}^{i-1}\{f_j+b_j\cdot a_i\}$。

这个$O(n^2)$一定无法通过题目，因此需要优化。

考虑斜率优化：设$j,k$两个$i$的决策点满足$k<j<i$，且$j$比$k$更优，那么有：

$$f_j+b_j\cdot a_i\leqslant f_k+b_k\cdot a_i$$

变一下形式：$f_j+b_j\cdot a_i\leqslant f_k+b_k\cdot a_i$ $\Rightarrow f_j-f_k\leqslant a_i\cdot(b_k-b_j)$ $\Rightarrow \frac{f_j-f_k}{b_k-b_j}\leqslant a_i$ $\Rightarrow -\frac{f_j-f_k}{b_j-b_k}\leqslant a_i$ $\Rightarrow\frac{f_j-f_k}{b_j-b_k}\geqslant -a_i$。

化成斜率式之后，由于$a$是递增的，因此用单调队列维护一个上凸壳就好了。

时间复杂度：$O(n)$。

## 代码
记得开$\text{long long}$，$inf$开大一点。
```
#include<stdio.h>
#include<string.h>
#define int long long
#define inf 1000000000000000000
const int maxn=100005;
int n,l,r;
int a[maxn],b[maxn],f[maxn],q[maxn];
inline int min(int a,int b){
	return a<b? a:b;
}
inline int x(int p){
	return b[p];
}
inline int y(int p){
	return f[p];
}
inline double slope(int a,int b){
	if(x(a)==x(b))
		return y(a)>y(b)? inf:-inf;
	return 1.0*(y(a)-y(b))/(x(a)-x(b));
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++)
		f[i]=inf;
	f[1]=b[1],q[++r]=0;
	for(int i=1;i<=n;i++){
		while(l<r&&slope(q[l+1],q[l])>=-a[i])
			l++;
		f[i]=f[q[l]]+b[q[l]]*a[i];
		while(l<r&&slope(q[r-1],i)>=slope(q[r],q[r-1]))
			r--;
		q[++r]=i;
	}
	printf("%lld\n",f[n]);
 	return 0;
}
```

---

## 作者：xixiup (赞：1)

## 思路分享

我们可以发现，我们只要砍倒了第 $n$ 棵树，就可以免费砍完其他所有的树，所以我们就可以将问题转化为，求如何以最小的代价砍完第 $n$ 棵树。

然后我们可以发现，由于 $b_i$ 单调下降，所以我们在砍完第 $n$ 棵树前肯定不会往回砍，因为这样对当前的充电价格没有任何贡献。

进一步思考，我们发现，只要我们开始砍一棵树了，就要将这棵树砍完，不然对当前充电价格也没有任何贡献。

于是，我们可以设 $dp_i$ 表示砍倒第 $i$ 棵树所需的最小成本。

经过思考，我们就可以列出动态转移方程：

$$
dp_i=\max\left(dp_i,dp_j+a_i \times b_j\right)\left|\right.j\in \left[ 1,i \right)
$$

但是这样转移是 $\Theta\left( n^2 \right)$ 的，会妥妥地 $TLE$，故我们需要优化。

我们设 $j,k$ 使得 $k < j < i$。

然后我们假设：

$$
dp_j+a_i \times b_j \geqslant dp_k+a_i \times b_k
$$

继续简化，则有：

$$
dp_j-dp_k \geqslant a_i \times \left( b_k-b_j \right)
$$

再简化时，需要注意，因为 $b$ 单调递减，所以 $b_k-b_j < 0$，所以有：

$$
\dfrac{dp_j-dp_k}{b_k-b_j} \leqslant a_i
$$

为了更好看，两边同时乘上 $-1$

$$
\dfrac{dp_j-dp_k}{b_j-b_k} \geqslant -a_i
$$

这样，我们就可以使用斜率优化了。

## 代码展示

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100100,inf=200000000000000;//inf需要开到1e14
int n,a[maxn],b[maxn],dp[maxn],dque[maxn],l,r;
int cal(int x,int y){//计算前文的公式
	if(dp[x]==dp[y]){
		return (x<y?-inf:inf);
	}
	return 1.*(dp[x]-dp[y])/(b[x]-b[y]);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	//这里我没有给dp赋初值，因为我们在后面不需要取min或max
   //但是众所周知，memset跑得巨慢
   l=0,r=1;
	dque[r]=1;//先将1加入队列
	for(int i=2;i<=n;i++){
		while(l<r&&cal(dque[l+1],dque[l])>=-a[i]){//处理符合条件的j
			l++;//由于a单调上升，所以这里时有单调性的
		}
		int j=dque[l];
		dp[i]=dp[j]+b[j]*a[i];
		while(l<=r&&cal(i,dque[r-1])>=cal(dque[r],dque[r-1])){
			r--;//注意这里要l<=r，因为你是可以将整个队列删完的
		}
		r++;
		dque[r]=i;
	}
	cout<<dp[n];
	return 0;
}
```


---

## 作者：smoothset (赞：1)

#### 题目分析
因为有 $ b[n] = 0 $ ，所以当砍掉第$ n $棵树时就不需要花钱了。

从这个角度入手，可以考虑定义 $ dp[i] $ 为砍第$i$棵树的花费，那么就可以轻松的得到一个 $ O(n^2) $ 的状态转移方程式：

$ dp[i] = min(dp[i], dp[j] + a[i]*b[j]),\ j < i $

但是一看数据范围  $ n \le 1e5 $，朴素的 $dp$ 明显行不通

我们再来看这个转移式，因为每次转移只跟 $ i,j $ 有关，我们考虑使用斜率优化

假设有：$j < k$ 且 $j$ 比 $k$ 优

那么有：
$ dp[j] +a[i]*b[j]<dp[k]+a[i]*b[k] $

移项过后就是：
$ \frac{dp[k]-dp[j]}{b[j]-b[k]}>a[i] $

这个就是我们的斜率式了

维护一个队列就可以使复杂度降低到 $ O(n) $
####  代码
具体实现请看代码
~~~cpp
const int N = 1e5 + 5;
ll dp[N];
int n, a[N], b[N], q[N], head, tail;
double getk(int x, int y)
{
    return 1.0 * (dp[y] - dp[x]) / (b[x] - b[y]);
}//计算斜率
int main()
{
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    q[++tail] = 1;
    head = 1;
    for (int i = 2; i <= n; i++)
    {
        while (head < tail && getk(q[head], q[head + 1]) < a[i])
            head++;
        dp[i] = dp[q[head]] + 1ll * a[i] * b[q[head]];
        while (head < tail && getk(q[tail], i) <= getk(q[tail - 1], q[tail]))
            tail--;
        q[++tail] = i;
    }
    cout << dp[n];
    return 0;
}
~~~

---

## 作者：Luciylove (赞：0)

题解区全是斜率优化，交个超哥树上来。

考虑 $a_i$ 递增，那么就可以一次性砍掉一段的树，然后我们就可以有如下方程 ：

$$f_i = f_j + b_i\times a_j$$

考虑这个看成斜率为 $a_j$ 的直线，截距为 $f_j$，然后单点求一次函数最小值即可。

时间复杂度 ：$n\log_2 n$。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define ls u << 1
#define rs u << 1 | 1

using namespace std;

const int N = 2e5 + 5, MOD = 998244353, INF = 1e15;

int n, tot, a[N], b[N], c[N], f[N];

struct line {
	int k, b;
	line (int k = 0, int b = 1e15) : k(k), b(b) {}
	inline int val (int pos) { return k * pos + b; }
} t[N * 4], p;
	
inline void insert (int u, int l, int r, line x) {
	int mid = (l + r) >> 1;
	if (l == r) { if (x.val(c[l]) < t[u].val(c[l])) t[u] = x; return ; }
	if (x.val(c[mid]) < t[u].val(c[mid])) swap(t[u], x);
	if (x.val(c[l]) < t[u].val(c[l])) insert(ls, l, mid, x);
	if (x.val(c[r]) < t[u].val(c[r])) insert(rs, mid + 1, r, x);
}	
inline int query (int u, int l, int r, int pos) {
	if (l == r) return t[u].val(c[pos]);
	int mid = (l + r) >> 1;
	if (pos <= mid) return min(t[u].val(c[pos]), query(ls, l, mid, pos));
	else return min(t[u].val(c[pos]), query(rs, mid + 1, r, pos));
}
                  
// 李超树
                  
signed main () {
	ios :: sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i], c[++ tot] = a[i];
	for (int i = 1; i <= n; i ++) cin >> b[i], c[++ tot] = b[i];
	sort(c + 1, c + 1 + tot), tot = unique(c + 1, c + 1 + tot) - (c + 1);
	for (int i = 1; i <= n; i ++) {
		a[i] = upper_bound(c + 1, c + 1 + tot, a[i]) - (c + 1), b[i] = upper_bound(c + 1, c + 1 + tot, b[i]) - (c + 1);
 	}
	insert(1, 1, tot, line(c[b[1]], 0));
	for (int i = 2; i <= n; i ++) {
		f[i] = query(1, 1, tot, a[i]);
		insert(1, 1, tot, line(c[b[i]], f[i]));
	}
	cout << f[n];
	return 0;
}

```

注意离散化的使用。

---

