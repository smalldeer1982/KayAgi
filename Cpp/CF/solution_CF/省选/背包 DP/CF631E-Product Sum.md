# Product Sum

## 题目描述

有一个长为 $n$ 的序列 $A_{i}$​，定义这个序列的价值为$\sum_{i=1}^n i*A_{i}$。

------------
现在对这个序列进行一次操作：
将序列中的某个数移到序列中的某一个位置，例如 $1,2,3,4$ 将 $4$ 移到 $1$ 位置上，序列就变成了 $4,1,2,3$。

现要进行一次操作，使得这个序列的价值最大

------------

## 说明/提示

$2 \leq n \leq 2*10^{5}$  $|A_{i}| \leq 10^{6}$

## 样例 #1

### 输入

```
4
4 3 2 5
```

### 输出

```
39```

## 样例 #2

### 输入

```
5
1 1 2 7 1
```

### 输出

```
49```

## 样例 #3

### 输入

```
3
1 1 2
```

### 输出

```
9```

# 题解

## 作者：灵茶山艾府 (赞：10)

### 公式推导

首先计算不操作（或者原地不动）时的答案，然后计算操作对答案的**最大增量**。

有向左移动和向右移动两种情况，但其实两种情况可以用同一个式子表示，推导过程如下：

设 $a$ 的 [前缀和](https://leetcode.cn/problems/range-sum-query-immutable/solution/qian-zhui-he-ji-qi-kuo-zhan-fu-ti-dan-py-vaar/) 数组为 $s$。

- 向左移动：假设 $a_i$ 移动到 $a_j$，那么下标在 $[j,i-1]$ 中的数的下标都加一，同时 $a_i\cdot i$ 减少为 $a_i\cdot j$，所以答案增加 $s_i - s_j - a_i\cdot(i-j)$。
- 向右移动：假设 $a_i$ 移动到 $a_j$，那么下标在 $[i+1,j]$ 中的数的下标都减一，同时 $a_i\cdot i$ 增加为 $a_i\cdot j$，所以答案增加 
  
    $$
    \begin{aligned}
        & -(s_{j+1} - s_{i+1}) + a_i\cdot(j-i)      \\
    ={} & -(s_{j+1} - s_{i+1} + a_i) + a_i + a_i\cdot(j-i)        \\
    ={} & -(s_{j+1} - s_i) + a_i\cdot(j+1-i)        \\
    ={} & -(s_{j'} - s_i) + a_i\cdot(j'-i)        \\
    ={} & s_i-s_{j'} - a_i\cdot(i-j')        \\
    \end{aligned}
    $$
    
    其中 $j'=j+1$（变量替换）。

可以发现两个式子是一样的，所以问题变成最大化

$$
s_i - s_j - a_i\cdot(i-j)
$$

其中 $0\le i\le n-1$，$0\le j\le n$。（本文讨论的下标从 $0$ 开始）

### 几何意义

把上式改成点积的形式，这样我们能得到来自几何意义上的观察。

设向量 $\mathbf{p} = (a_i, 1)$，向量 $\mathbf{v}_j = (j,-s_j)$。

那么

$$
\begin{aligned}
    & s_i - s_j - a_i\cdot(i-j)      \\
={} & a_i\cdot j - s_j - a_i\cdot i + s_i         \\
={} & \mathbf{p}\cdot \mathbf{v}_j - a_i\cdot i + s_i       \\
\end{aligned}
$$

根据点积的几何意义，我们求的是 $\mathbf{v}_j$ 在 $\mathbf{p}$ 方向上的投影长度，再乘以 $\mathbf{p}$ 的模长 $||\mathbf{p}||$。由于 $||\mathbf{p}||$ 是个定值，所以要最大化投影长度。

考虑 $\mathbf{v}_j$ 的**上凸包**（用 Andrew 算法计算），在凸包内的点，就像是山坳，比凸包顶点的投影长度短。所以只需考虑凸包顶点。

这样有一个很好的性质：顺时针遍历凸包顶点，$\mathbf{p}\cdot \mathbf{v}_j$ 会先变大再变小（单峰函数）。那么要计算最大值，就类似 [852. 山脉数组的峰顶索引](https://leetcode.cn/problems/peak-index-in-a-mountain-array/)，**二分**首个「下坡」的位置，具体见 [我的题解](https://leetcode.cn/problems/peak-index-in-a-mountain-array/solutions/2984800/er-fen-gen-ju-shang-po-huan-shi-xia-po-p-uoev/)。

AC 代码（Golang）：

```go
package main
import("bufio";."fmt";"os";"sort")

type vec struct{ x, y int }
func (a vec) sub(b vec) vec { return vec{a.x - b.x, a.y - b.y} }
func (a vec) dot(b vec) int { return a.x*b.x + a.y*b.y }
func (a vec) det(b vec) int { return a.x*b.y - a.y*b.x }

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, tot, mx, s int
	Fscan(in, &n)
	a := make([]int, n)
	q := []vec{{-1, 0}} // s[-1] = 0
	for i := range a {
		Fscan(in, &a[i])
		tot += a[i] * (i + 1)
		s += a[i]
		v := vec{i, -s} // 由于 i 是单调递增的，求上凸包无需排序
		for len(q) > 1 && q[len(q)-1].sub(q[len(q)-2]).det(v.sub(q[len(q)-1])) >= 0 {
			q = q[:len(q)-1]
		}
		q = append(q, v)
	}

	s = 0
	for i, x := range a {
		p := vec{x, 1}
		j := sort.Search(len(q)-1, func(j int) bool { return p.dot(q[j]) > p.dot(q[j+1]) }) // 二分找峰顶
		s += x
		mx = max(mx, p.dot(q[j])-x*i+s)
	}
	Print(tot + mx)
}
```

**时间复杂度**：$\mathcal{O}(n\log n)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：panyf (赞：9)

斜率优化写挂了，于是改用好写好调的李超线段树。

先考虑将 $i$ 移动到 $j$ 的情况 ($i<j$) ，对数组 $a$ 做前缀和，记为数组 $s$ ，那么增加的价值即为 $a_i\times(j-i)-(s_j-s_i)$ 。

去掉与 $j$ 无关的项，即为 $a_i\times j-s_j$ 。令 $k=j$ ， $b=-s_j$ ，原式相当于直线 $y=kx+b$ 在 $x=a_i$ 时的值。

用李超线段树维护所有直线的最大值即可，不会李超线段树的可以去做[P4254](https://www.luogu.com.cn/problem/P4254)。

$i>j$ 的情况也差不多，这里就不赘述了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+3,P=1e6+3; 
ll a[N],s[N],K[N],b[N],u,v;
int g[P*5],p;
#define f(i,j) (K[i]*(j)+b[i])
void upd(int k=1,int l=-P,int r=P){//插入直线
	int m=l+r>>1;
	if(f(p,m)>f(g[k],m))swap(p,g[k]);
	if(l!=r)K[p]>K[g[k]]?upd(k*2+1,m+1,r):upd(k*2,l,m);
}
void qry(int k=1,int l=-P,int r=P){//查询最大值
	if(u=max(u,f(g[k],v)),l==r)return;
	int m=l+r>>1;
	v>m?qry(k*2+1,m+1,r):qry(k*2,l,m);
}
int main(){
	int n,i,j,t=0;
	ll o=0,w=0;
	cin>>n,b[0]=-1e18;
	for(i=1;i<=n;++i)cin>>a[i],s[i]=s[i-1]+a[i],o+=i*a[i];
	for(i=1;i<=n;++i)u=-1e18,v=a[i],qry(),w=max(w,u+s[i-1]-a[i]*i),K[++t]=i,b[p=t]=-s[i-1],upd();//i>j的情况
	memset(g,t=0,sizeof(g));
	for(i=n;i;--i)u=-1e18,v=a[i],qry(),w=max(w,u+s[i]-a[i]*i),K[++t]=i,b[p=t]=-s[i],upd();//i<j的情况
	cout<<w+o;
	return 0;
}
```


---

## 作者：DPair (赞：8)

//20200804update：抱歉，提交次数有点多是因为Markdown爆炸了（本机AC提交RE那种），带来的麻烦请管理员谅解。
## 【前言】

似乎楼下那篇斜率优化没有A啊。。。那是不是我这篇AC了的更有发言权呢？而且写法显然要好得多，码量似乎是楼下的一半。

## 【题意】

题意似乎挺简单的，给你$n$个数的一个序列，权值为$\sum_{i=1}^na_i*i$，让你把一个数移到另一个位置，使得权值最大。注意也可以不移。

## 【思路】

首先我们考虑$O(n^2)$的暴力做法。

很显然，由于我们只移动一个数，因此只需要枚举起点$i$与终点$j$就可以了，对于每一个起点，设移动它能**增加**的最大权值为$ans_i$，最后答案即为$max(max\{ans_i\},0)$（注意这里是**增加**的权值，即在原序列基础上最多能加多少权值，因此需考虑所有$ans_i$都小于$0$时不如不动，并同时考虑了所有不动的情况）。

这里我们分类讨论。

对于$i$向前移动（假设$i$移到了$j$的后面，把$j+1$向后挤），我们有：

$$ans_i=max\{\sum_{k=j+1}^{i-1}a[k]-(i-(j+1))*a[i]\}(j\in[0, i-1])$$

其中$\sum_{k=j+1}^{i-1}a[k]$表示第$j+1$个数一直到第$i-1$个数，每一个数都向后移动了一位，即系数都增加了$1$，也就是它的贡献增加了它本身的权值，故总权值增加$\sum_{k=j+1}^{i-1}a[k]$，而第$i$个数$a[i]$，会因为向前移动而减小系数，从$i$变为$j+1$故总权值减少$(i-(j+1))*a[i]$。

对于$i$向后移动（同样假设$i$移到了$j$的后面，但这次把$j$向前挤了），此时我们有：

$$ans_i=max\{(j-i)*a[i]-\sum_{k=i+1}^{j}a[k]\}(j\in[i+1, n])$$

具体的推导就不再赘述了，与上文类似，留给读者自行思考。

### 【化简】

我们发现这甚至不是一个$O(n^2)$的算法，但容易想到前缀和。

考虑设$b[i]=\sum_{k=1}^i$。

我们有：
$$ans_i=max\{b[i-1]-b[j]-(i-(j+1))*a[i]\}(j\in[0, i-1])$$

$$ans_i=max\{(j-i)*a[i]-(b[j]-b[i])\}(j\in[i+1, n])$$

结果写完现在的两个式子之后，我们发现了一些很有趣的事情：

$$ans_i=max\{b[i-1]-b[j]-(i-(j+1))*a[i]\}(j\in[0, i-1])$$

$$=max\{b[i-1]-b[j]-(i-j-1)*a[i]\}$$

$$=max\{b[i-1]-b[j]+(j+1-i)*a[i]\}$$

$$=max\{b[i-1]-b[j]+a[i]+(j-i)*a[i]\}$$

$$=max\{b[i]-b[j]+(j-i)*a[i]\}$$


$$ans_i=max\{(j-i)*a[i]-(b[j]-b[i])\}(j\in[i+1, n])$$

$$=max\{b[i]-b[j]+(j-i)*a[i]\}$$

于是我们惊奇地发现两个式子**完 全 一 致**。

因此码量**大 大 减 少**（有用部分大概$30$多行）。

## 【优化】

式子化简完了，考虑优化。

这个式子符合斜率优化的特点，显然可以斜率优化。

考虑化开，不妨设$x < y$且$x$更优，那么对于：
$$ans_i=max\{b[i]-b[j]+(j-i)*a[i]\}$$
有：
$$b[i]-b[x]+(x-i)*a[i]>b[i]-b[y]+(y-i)*a[i]$$

移项、消元得：
$$-b[x]+x*a[i]>-b[y]+y*a[i]$$

$$(x-y)*a[i]>b[x]-b[y]$$

$$a[i]>\frac{b[x]-b[y]}{x-y}$$

设斜率$k=a[i]$，点坐标为$(j, b[j])$，跑斜率优化即可，复杂度$O(n)$。

由于一开始所有$j$都可用，因此先把所有$j$入队，然后直接每一个$i$扫一遍取最大值即可，由于斜率不单调，需要二分。复杂度$O(nlogn)$，可以通过本题。

## 【代码】

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef unsigned int UI;

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
template <typename T>
inline T min(T x, T y) {return x < y ? x : y;}
template <typename T>
inline T max(T x, T y) {return x > y ? x : y;}
template <typename T>
inline void chmin(T &x, T y) {(x > y) && (x = y);}
template <typename T>
inline void chmax(T &x, T y) {(x < y) && (x = y);}
//有效代码从这里开始
LL b[200010], n, a[200010], ans = 0, ret = 0;
int ed = 1, q[200010];
inline LL X(int x) {return x;}
inline LL Y(int x) {return b[x];}
inline LL slope_fz(int x, int y) {return Y(x) - Y(y);}//维护斜率，写分子分母的原因在于这样可以避免精度爆炸
inline LL slope_fm(int x, int y) {return X(x) - X(y);}

inline int solve (LL val){//二分找斜率
    int L = 2, R = ed, cur = 1;
    while(L <= R){
        int mid = (L + R) >> 1;
        if(slope_fz(q[mid], q[mid - 1]) <= val * slope_fm(q[mid], q[mid - 1])) L = mid + 1, cur = mid;
        else R = mid - 1;
    }
    return q[cur];
}

int main(){
    read(n);
    for (register int i = 1;i <= n;i ++){read(a[i]);b[i] = b[i - 1] + a[i];ans = ans + i * a[i];}//求前缀和与原序列权值（毕竟是在此基础上增加）
    for (register int i = 1;i <= n;i ++){//每个j入队
        while(ed > 1 && slope_fz(q[ed], q[ed - 1]) * slope_fm(i, q[ed]) >= slope_fz(i, q[ed]) * slope_fm(q[ed], q[ed - 1])) ed --;
        q[++ ed] = i;
    }
    for (register int i = 1;i <= n;i ++){//每个i扫一遍
        int j = solve(a[i]);
        chmax(ret, (j - i) * a[i] + b[i] - b[j]);
    }
    fprint(ans + ret);putchar(10);
}
```

---

## 作者：jiangchenyangsong (赞：4)

### 前言
不知道为什么题解里的李超线段树都要分两种情况讨论，我觉得的大可不必，其实一遍就好了。

## 分析
设 $ans_i$ 为 $i$ 移动到 其他位置时获得的最大取值，$sum_i$ 为 $a_i$ 的前缀和。

对于 $ i < j $，$ans_i=\max \{(j-i)\times a_i-(sum_j-sum_i)\}$。

对于 $i > j$，$ans_i=\max \{ sum_i-sum_j+[(i-(j+1))]\times a_i\}$。

将两式化简会发现它们都是 $ans_i=\max \{sum_i-sum_j+(j-i)\times a_i\}$ 。

发现好像没有单调性，并且二分的斜率优化我也不会，就去考虑李超线段树。

将与 $j$ 相关的式子提出为 $a_i\times j-sum_j$，令 $k=j$，$b=-sum_j$，就可以开始打李超线段树了。

这里大多题解都用了两次 for 循环，正着反着都做了一遍，其实可以将线段先全部插入，再查询，就可以枚举一次了，详见代码，~~好像还是两次 for 循环~~。

$code$
```c
#include<bits/stdc++.h>
#define N 200005
#define T 2000005
#define int long long
#define ls u<<1
#define rs u<<1|1
#define INF 1e13
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int n,ans1,ans2;
int tree[T<<2];
int a[N],sum[N],k[N],b[N];
int calc(int x,int id){return x*k[id]+b[id];}
int Query(int u,int l,int r,int x){
	if(l==r) return calc(x,tree[u]);
	int mid=(l+r)>>1,res=calc(x,tree[u]);
	if(x<=mid) res=max(res,Query(ls,l,mid,x));
	else res=max(res,Query(rs,mid+1,r,x));
	return res;
}
void UpDate(int u,int l,int r,int id){
	if(!tree[u]) return void(tree[u]=id);
	if(calc(l,id)>calc(l,tree[u])&&calc(r,id)>calc(r,tree[u])) return void(tree[u]=id);
	else if(calc(l,id)<=calc(l,tree[u])&&calc(r,id)<=calc(r,tree[u])) return ;
	int mid=(l+r)>>1;
	if(k[id]>k[tree[u]]){
		if(calc(mid,id)>calc(mid,tree[u])) UpDate(ls,l,mid,tree[u]),tree[u]=id;
		else UpDate(rs,mid+1,r,id);
	}else{
		if(calc(mid,id)>calc(mid,tree[u])) UpDate(rs,mid+1,r,tree[u]),tree[u]=id;
		else UpDate(ls,l,mid,id);
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read(),sum[i]=sum[i-1]+a[i],ans2+=i*a[i];
	for(int i=1;i<=n;++i){
		k[i]=i,b[i]=-sum[i]; 
		UpDate(1,-1e6,1e6,i);
	}
	for(int i=1;i<=n;++i){
		int x=Query(1,-1e6,1e6,a[i]);
		ans1=max(ans1,x-i*a[i]+sum[i]);
	}
	printf("%lld\n",ans2+ans1);
	return 0;
}
```


---

## 作者：吹雪吹雪吹 (赞：4)

[${\large \color{#ff7daf}{\text{CF631E Product Sum}}}$](http://xc.fubuki.cn/2019/%E6%96%9C%E7%8E%87%E4%BC%98%E5%8C%96/)

题意：整个序列的分数为 $\sum\limits_{i=1}^{n}a_i·i$ ，你可以将某个元素向任意方向移动任意位，求一次该操作后可获得的最大分数。

设 $sum_i = \sum\limits_{j=1}^{i}a_i$

接下来以将第 $i$ 个元素向前移动**到**第 $j$ 个位置为例：

将 $a_i$ 移到 $j$ 增加的分数： $(j-i)·a_i-(sum_j-sum_i)$

尝试斜率优化，设 $k > j$ 且选择 $k$ 要优于选择 $j$：

$(j-i)·a_i-(sum_j-sum_i)<(k-i)·a_i-(sum_k-sum_i)$

移项后合并同类项：

$j·a_i-sum_j<k·a_i-sum_k$

再移项：

$sum_k-sum_j<(k-j)·a_i$

$\frac{sum_j-sum_k}{j-k}<a_i$

维护上凸壳，二分进行决策即可。

将某一元素向后移动类似，此处不做赘述。

代码（不可AC，但是正确(^_^)）：

```cpp

#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 200005
#define K(x, y) ((1.0 * w[x] - w[y]) / (1.0 * (x) - (y)))
#define Calc1(x, y) (sum[(x) - 1] - sum[(y) - 1] - a[x] * ((x) - (y)))
#define Calc2(x, y) (a[x] * ((y) - (x)) - (sum[(y)] - sum[(x)]))

using namespace std;
typedef int LL;

int n, stk[maxn], top = 0;
LL a[maxn], sum[maxn], ans = 0, w[maxn], res = 0;

inline int read()
{
    char ch = getchar();
    int ret = 0, f = 1;
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        ret = ret * 10 + ch - '0', ch = getchar();
    return ret * f;
}

int main()
{
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        sum[i] = sum[i - 1] + a[i];
        ans += 1ll * i * a[i];
    }
    stk[1] = 1, stk[2] = 2, top = 2;
    w[1] = sum[0], w[2] = sum[1];
    res = max(0ll, Calc1(2, 1));
    for (int i = 3; i <= n; ++i)
    {
        int l = 1, r = top - 1, j = stk[top];
        while (l <= r)
        {
            int mid = (r - l >> 1) + l;
            if (K(stk[mid + 1], stk[mid]) > a[i])
                r = mid - 1, j = stk[mid];
            else
                l = mid + 1;
        }
        res = max(res, Calc1(i, j));
        w[i] = sum[i - 1];
        while (top > 1)
        {
            if (K(i, stk[top]) > K(stk[top], stk[top - 1]))
                break;
            --top;
        }
        stk[++top] = i;
    }
    stk[1] = n, stk[2] = n - 1, top = 2;
    w[n] = sum[n], w[n - 1] = sum[n - 1];
    res = max(res, Calc2(n - 1, n));
    for (int i = n - 3; i > 0; --i)
    {
        int l = 1, r = top - 1, j = stk[top];
        while (l <= r)
        {
            int mid = (r - l >> 1) + l;
            if (K(stk[mid + 1], stk[mid]) < a[i])
                r = mid - 1, j = stk[mid];
            else
                l = mid + 1;
        }
        res = max(res, Calc2(i, j));
        w[i] = sum[i];
        while (top > 1)
        {
            if (K(i, stk[top]) < K(stk[top], stk[top - 1]))
                break;
            --top;
        }
        stk[++top] = i;
    }
    printf("%I64d\n", ans + res);
    return 0;
}

```

多一句嘴，网上三分什么的显然是错的，有兴趣的可以去叉一下。$\color{white}{\text{上面的代码开下 long long 就能过了}}$

---

## 作者：Terac (赞：3)

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF631E)

## 题意

给定一个长度为 $n$ 的序列 $a$，定义该序列的权值为 $\sum\limits_{i=1}^n i \cdot a_i$，现有一次将序列中某个数移动到任意位置的机会，可以移回原位，求操作后序列 $a$ 最大权值。

数据范围：$2 \leq n \leq 2\times10^{5},|a_i|\le10^6$

## 题解

考虑先算出未操作时的权值，再去算操作后能使答案增加的最大值。

设 $f_i$ 表示移动 $a_i$ 对答案的最大贡献值，若 $a_i$ 移到了位置 $j$，我们分类讨论：
- 当 $i< j$ 时，$f_i=\max\{a_i\times(j-i)-\sum\limits_{k=i+1}^ja_k\}$
- 当 $i\ge j$ 时，$f_i=\max\{\sum\limits_{k=j}^{i-1}a_k-a_i\times(i-j)\}$

后面那个求和可以用前缀和弄掉，设 $sum_i=\sum\limits_{j=1}^ia_j$，则：

$$f_i=\begin{cases}\max\{a_i\times(j-i)-sum_j+sum_i\}&j\in\left(i,n\right]\\\max\{a_i\times(j-i)-sum_{j-1}+sum_{i-1}\}& j\in\left[1,i\right]\end{cases}$$

于是我们得到一个 $O(n^2)$ 的做法。

其实化成这样也可以做，但比较麻烦。

观察到上下两个形式很相近，考虑当 $j\in\left[1,i\right]$，令 $j\gets j-1$ 转化成和上面一样的形式。

$$\begin{aligned}f_i&=\max\{a_i\times(j-i)-sum_{j-1}+sum_{i-1}\}\ \ \ \ \ \ \ j\in\left[1,i\right]\\&=\max\{a_i\times(j+1-i)-sum_{j}+sum_{i-1}\}\ \ \ \ \ \ \ j\in\left[0,i\right)\\&=\max\{a_i\times(j+1-i)-sum_{j}+sum_{i}-a_i\}\ \ \ \ \ \ \ j\in\left[0,i\right)\\&=\max\{a_i\times(j-i)-sum_{j}+sum_{i}\}\ \ \ \ \ \ \ j\in\left[0,i\right)\end{aligned}$$

发现 $j\in\left[0,i\right)$ 和 $j\in\left(i,n\right]$ 时的计算方式一样，我们便大大简化了过程。

于是 $f_i=\max\{a_i\times(j-i)-sum_j+sum_i\}$。

拆开后 $f_i=\max\{a_i\times j-sum_j\}+sum_i-a_i\times i$。

这个形式显然可以斜率优化，若 $j_1<j_2$ 且 $i$ 移到 $j_2$ 时比移到 $j_1$ 时贡献要大，有：
$$a_i\times j_1-sum_{j_1}<a_i\times{j_2}-sum_{j_2}$$
$$\therefore a_i\times (j_1-j_2)<sum_{j_1}-sum_{j_2}$$
$$\therefore a_i>\dfrac{sum_{j_1}-sum_{j_2}}{j_1-j_2}$$

维护 $(j,sum_{j})$ 这些点组成的下凸壳即可，因为点坐标与 $f_j$ 无关，可以先把这些点加进来，注意 $a_i$ 不一定是单增的，可以有两种处理方式。

- 二分下凸壳，找到比 $a_i$ 小的最大斜率。

- 因为答案与计算顺序无关，先将 $a$ 排序后再上单调队列。

这两种我都写了，二分复杂度 $O(n\log n)$，排序后单调队列可以用基排做到 $O(n)$，不过我懒得写了，貌似单调队列的做法会快（？

只贴单调队列的代码了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
const int N = 1e6 + 10;
int n;
int q[N], head, tail;
ll sum[N], ans, base;
struct node {
	int v, id;
	friend bool operator < (const node &qwq, const node &awa) {
		return qwq.v < awa.v;
	}
} a[N];
ld slope(int i, int j) {
	return (1. * sum[i] - sum[j]) / (i - j);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i].v);
		sum[i] = sum[i - 1] + a[i].v, base += 1ll * i * a[i].v;
		a[i].id = i;
	}
	head = tail = 1;
	for(int i = 1; i <= n; i++) {
		while(tail > 1 && slope(q[tail - 1], i) < slope(q[tail - 1], q[tail])) tail--;
		q[++tail] = i;
	}
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; i++) {
		while(head < tail && slope(q[head], q[head + 1]) < a[i].v) head++;
		ans = max(ans, 1ll * (q[head] - a[i].id) * a[i].v + sum[a[i].id] - sum[q[head]]);
	}
	printf("%lld\n", ans + base);
}
```


---

## 作者：Hell0_W0rld (赞：1)

不妨设将 $a_i$ 移动到 $j$ 号位置。

若 $i>j$，则得分为 
$$\sum^{j-1}_{x=1} x\times A_x +\sum^n_{x=i+1}x\times A_x+A_i\times j+\sum^{i-1}_{x=j} (x+1)\times A_x\\
=\sum^n_{i=1}i\times A_i+(j-i)\times A_i+\sum_{x=i}^{j-1}A_x$$

不妨看做直线 $y=jx-\sum_{x=1}^{j-1}A_x+\sum^n_{i=1}i\times A_i$，用李超线段树维护，查询横坐标为 $x=A_i$ 的所有纵坐标中最大值再减去 $i\times A_i$ 即可。

若 $i<j$ 同理即可。

---

## 作者：Kketchup (赞：1)

## CF631E Product Sum

- 斜率优化DP
- *2600

[传送门](https://codeforces.com/contest/631/problem/E)

### 闲话

模拟赛 D 题。感觉是个斜优的比较板的题。

开始写了一发错误的贪心，Wa on 9，后来改成 DP 才过。

场上过了 $5$ 个，拜谢 AK 爷 [@Helloworld_wuyuze](https://www.luogu.com.cn/user/593274) [@RailgunZzzz](https://www.luogu.com.cn/user/586905) [@秦屎皇](https://www.luogu.com.cn/user/536743)。

### 题意

给定一个长度为 $n$ 的序列，序列的价值定义为 $\sum_{i=1}^na_i\times i$。允许至多一次操作，把一个元素移动到任意一个序列中的位置，求最大的序列价值。

$2\le n\le 2\times 10^5，|a_i|\le 10^6$。

### 解析

先考虑 naive 做法。对于每个 $a_i$，枚举其移动到的位置位置 $j$，每次计算贡献的变化，时间复杂度 $O(n^2)$。

具体地，分两种情况讨论。对于向前移动，即 $j<i$，从 $i$ 移到 $j$ 后面，会使位于 $[j+1,i-1]$ 的元素贡献多一次，然后 $i$ 的贡献转化到了 $j+1$。

也就是 $s_{i-1}-s_{j}-(i-(j+1))\times a_i$。这里的 $s_i$ 表示 $a_i$ 的前缀和。

对于向后移动，移动到位置 $j$，会使 $[i+1,j]$ 的元素贡献少一次，再算上 $i$ 到 $j$ 的贡献。

$-(s_j-s_i)+(j-i)\times a_i$，即 $s_i-s_j+(j-i)\times a_i$。

尝试化简一下第一个式子。
$$
\begin{aligned}
&s_{i-1}-s_{j}-(i-(j+1))\times a_i\\
=&s_{i-1}-s_j-(i-j-1)\times a_i\\
=&s_{i-1}-s_j+a_i-(i-j)\times a_i\\
=&s_i-s_j-(i-j)\times a_i\\
=&s_i-s_j+(j-i)\times a_i
\end{aligned}
$$
我们推导可以发现，向前移动与向后移动的式子等价。这样的话，两个转移被合并成了一个转移，方便很多。

我们还需要优化。把括号拆开，变成 $s_i-s_j+a_i\times j-a_i\times i$。发现此时的方程中只有一个与 $i,j$ 都有关的项 $a_i\times j$ 和几个只与 $i$ 或 $j$ 有关的项。是斜率优化的经典形式，此处不赘述斜优过程。

数据没有单调性，所以可以用二分凸包或者李超树维护。

### 代码实现

考场上没想到可以变一个式子，正反做了两遍，二分+栈。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define endl '\n'
#define pii pair<int,int>
#define eb emplace_back
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define fo(i,x,y) for(int i=(x);i>=(y);--i)
constexpr int N=2e5+10;
constexpr int M=5e5+10;
constexpr int mod=1e9+7;
constexpr int inf=0x3f3f3f3f;
constexpr ll INF=0x3f3f3f3f3f3f3f3f;
constexpr db eps=1e-8;
#define int long long
int a[N],f[N];
struct line{
	int k,b;
	line(){}
	line(int _k,int _b){
		k=_k,b=_b;
	}
	int calc(int x){
		return k*x+b;
	}
};
struct tree{
	#define t1 s.size()-1
	#define t2 s.size()-2
	vector<line> s;
	bool cmp(line x,line p1,line p2){
		return (p2.b-x.b)*(p1.k-p2.k)<=(p2.b-p1.b)*(x.k-p2.k);
	}
	void insert(line x){
		while(s.size()>=2&&cmp(x,s[t1],s[t2])) s.pop_back();
		s.eb(x);
	}
	int query(int x){
		int l=0,r=t1;
		while(l<r){
			int mid=(l+r)>>1;
			if(s[mid].calc(x)>=s[mid+1].calc(x)) r=mid;
			else l=mid+1;
		}
		return s[r].calc(x);
	}
	#undef t1
	#undef t2
}t1,t2;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,res=0,ans=0;
	cin>>n;
	F(i,1,n){
		cin>>a[i];
		f[i]=f[i-1]+a[i];
		res+=i*a[i];
	}
	t1.insert(line(1,-f[0]));
	F(i,2,n){
		ans=max(ans,-a[i]*i+f[i-1]+t1.query(a[i]));
		t1.insert(line(i,-f[i-1]));
	}
	t2.insert(line(-n,-f[n]));
	fo(i,n-1,1){
		ans=max(ans,-a[i]*i+f[i]+t2.query(-a[i]));
		t2.insert(line(-i,-f[i]));
	}
	cout<<ans+res<<endl;
	return 0;
}
```
赛后用李超树写了第二种实现，$k=j,b=-s_j$，查询 $x=a_i$ 处的最值。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define endl '\n'
#define pii pair<int,int>
#define eb emplace_back
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define fo(i,x,y) for(int i=(x);i>=(y);--i)
constexpr int N=2e5+10;
constexpr int M=1e6;
constexpr int mod=1e9+7;
constexpr int inf=0x3f3f3f3f;
constexpr ll INF=0x3f3f3f3f3f3f3f3f;
constexpr db eps=1e-8;
#define int long long
int k[N],b[N],s[N],a[N];
int calc(int i,int x){return k[i]*x+b[i];}
int t[M<<4];
void update(int p,int l,int r,int x){
    if(l==r){
        if(calc(x,l)>calc(t[p],l)) t[p]=x;
        return ;
    }
    int mid=(l+r)>>1;
    if(calc(x,mid)>calc(t[p],mid)) swap(t[p],x);
    if(calc(x,l)>calc(t[p],l)) update(p<<1,l,mid,x);
    else if(calc(x,r)>calc(t[p],r)) update(p<<1|1,mid+1,r,x);
}
int query(int p,int l,int r,int x){
    if(l==r) return calc(t[p],x);
    int mid=(l+r)>>1;
    int res=calc(t[p],x);
    if(x<=mid) return max(res,query(p<<1,l,mid,x));
    else return max(res,query(p<<1|1,mid+1,r,x));
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,res=0,ans=0;
	cin>>n;
	F(i,1,n){
		cin>>a[i];
		res+=i*a[i];
		s[i]=a[i]+s[i-1];
		k[i]=i;
		b[i]=-s[i];
		update(1,-M,M,i);
	}
	F(i,1,n){
		int tmp=query(1,-M,M,a[i]);
		ans=max(ans,s[i]-a[i]*i+tmp);
	}
	cout<<ans+res<<endl;
	return 0;
}
```
---
完结撒花！题解不易，望管理通过。

---

## 作者：XeniaF (赞：1)

考虑一次移动会给总价值带来什么影响。

假设一个本来在位置 $i$ 上的数 $a_i$ ，移动到位置 $j$ 。

若 $j<i$ ，则给总价值带来的贡献为 $a_j+a_{j+1}+...+a_{i-1}+a_i\times (j-i)$ 。

设 $s_i$ 为 $a_i$ 的前缀和，则式子变为 $s_{i-1}-s_{j-1}+a_i\times (j-i)$ 。发现与 $j$ 有关的项只有 $a_i\times j-s_j$ ，不妨令 $k_j=j,b_j=-s_{j-1}$ ，则式子变为了求当 $x=a_i$ 时，在所有 $y_j=k_jx+b_j,j<i$ 的直线中求一个最大的 $y$ 值。这个东西很显然可以用李超线段树维护。

同理，当 $j>i$ 时，给总价值带来的贡献为 $a_i\times (j-i)-(s_{j}-s_{i})$ ，发现与 $j$ 有关的项为 $a_i\times j-s_j$ ，同样令 $k_j=j,b_j=-s_j$ ，李超线段树维护即可。

时间复杂度 $\mathcal{O}(n\log n)$ 。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define maxn 200010
using namespace std;
const ll maxm=1e6+10;
const ll INF=1e18;

ll n,c[maxn];
ll t[maxn];
ll a[maxn];
ll b[maxn];
ll u;

inline ll read(){
    ll x=0,f=0;char c=getchar();
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?-x:x;
}

struct LC_Tree{

    ll s[maxn*40];

    #define lc k<<1
    #define rc k<<1|1

    inline void init(){memset(s,0,sizeof(s));}

    inline ll F(ll x,ll y){return a[x]*y+b[x];}

    inline void ins(ll l,ll r,ll k,ll x){
        if(l==r) return s[k]=(F(s[k],l)>F(x,l))?x:s[k],void();
        ll mid=(l+r)>>1;
        if(F(x,mid)>F(s[k],mid)) swap(x,s[k]);
        if(F(x,l)>F(s[k],l)) ins(l,mid,lc,x);
        else if(F(x,r)>F(s[k],r)) ins(mid+1,r,rc,x);
    }

    inline ll qry(ll l,ll r,ll k){
        ll res=F(s[k],u);
        if(l==r) return res;
        ll mid=(l+r)>>1,ans=res;
        ans=max(ans,u<=mid?qry(l,mid,lc):qry(mid+1,r,rc));
        return ans;
    }


}tr;

ll sm;
ll las;

int main(){
    n=read();
    for(register int i=1;i<=n;++i) c[i]=read(),sm+=i*c[i];
    for(register int i=1;i<=n;++i) t[i]=t[i-1]+c[i],a[i]=i,b[i]=-t[i-1];
    b[0]=-INF;tr.ins(-maxm,maxm,1,1);las=sm;
    for(register int i=2;i<=n;++i){
        u=c[i];las=max(las,sm+tr.qry(-maxm,maxm,1)+t[i-1]-c[i]*i);
        tr.ins(-maxm,maxm,1,i);
    }
    tr.init();
    for(register int i=1;i<=n;++i) a[i]=i,b[i]=-t[i];
    b[0]=-INF;tr.ins(-maxm,maxm,1,n);
    for(register int i=n-1;i>=1;--i){
        u=c[i];las=max(las,sm+tr.qry(-maxm,maxm,1)+t[i]-c[i]*i);
        tr.ins(-maxm,maxm,1,i);
    }
    printf("%lld\n",las);
    return 0;
}
```



---

## 作者：Leeb (赞：0)

### 题目描述

[题目链接 - Luogu](https://www.luogu.com.cn/problem/CF631E)

[题目链接 - Codeforces](http://codeforces.com/problemset/problem/631/E)
### 解题思路

令 $S=\sum\limits_{i=1}^n i\cdot a_i$。
考虑当前位置 $i$ 的数插到位置 $j$ 时，权值的变化：
-  $j\lt i$，位置 $i$ 的数往前插。
	- $\forall k\in [1,j) \cup (i,n]$，$k\cdot a_k$ 没有变化。
	- $\forall k\in [j,i)$，则每个数都会往后移一位，$k\cdot a_k \leftarrow (k+1)\cdot a_k$，$S$ 增加 $\sum\limits_{k=j}^{i-1} a_k$。
	- $i$ 前移 $i-j$ 位到 $j$，$i\cdot a_i \leftarrow j\cdot a_i$，$S$ 减少 $(i-j)\cdot a_i$。
	- 设 $f_i$：考虑第 $i$ 个位置往前移动到某个位置时的权值最大值，$sum_i=\sum\limits_{j=1}^i a_j$。
	- 从小到大枚举 $i$ 。
	- $f_i=\min \{S+sum_{i-1}-sum_{j-1}+(i-j)\cdot a_i\}=S+sum_{i-1}+a_i\cdot i+\min\{-i\cdot a_i-sum_{j-1}\}$。
	- $-j$ 看做直线斜率 $k$，$-sum_{j-1}$ 看做直线截距 $b$，$a_j$ 就是因变量 $x$。
- $j>i$，位置 $i$ 的数往后插。
	- $\forall k\in [1,i)\cup(j,n]$，$k\cdot a_k$ 没有变化。
	- $\forall k\in (i,j]$，每个数都会往前移一位，$k\cdot a_k \leftarrow (k-1)\cdot a_k$，$S$ 减少 $\sum\limits_{k=i+1}^j a_k$。
	- $i$ 后移 $j-i$ 位到 $j$，$i\cdot a_i \leftarrow j\cdot a_i$，$S$ 增加 $(j-i)\cdot a_i$。
	- 设 $f_i$：考虑第 $i$ 个位置往移动后到某个位置时的最大权值，$sum_i=\sum\limits_{j=1}^i a_j$。
	- 从大到小枚举 $i$。
	- $f_i=\min\{S-(sum_j-sum_i)+(j-i)\cdot a_i\}=S+sum_i-i\cdot a_i+\min\{j\cdot a_i-sum_j\}$。
	- $j$ 看做直线斜率 $k$，$-sum_j$ 看做直线截距 $b$，$a_i$ 就是因变量 $x$。
### 参考代码

```cpp
// Code by Leeb
// Powered by Visual Studio Code
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 2000005
#define M 1000000
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define pii pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, ans, tot, a[N], sum[N];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
namespace Seg {
    struct Node {
        int k, b;
        Node(){}
        Node(int _k, int _b) {
            k = _k, b = _b;
        }
    } tree[N << 2];
    inline int calc(Node q, int x) {
        return q.k * x + q.b;
    }
    inline bool check(Node a, Node b, int x) {
        return calc(a, x) < calc(b, x);
    }
    inline void build(int x, int l, int r) {
        tree[x] = Node(0, -inf);
        if (l == r) return ;
        int mid = l + r >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
    }
    inline void update(int x, int l, int r, Node k) {
        if (check(tree[x], k, l) && check(tree[x], k, r)) {
            tree[x] = k; return ;
        }
        if (l == r) return ;
        int mid = l + r >> 1;
        if (check(tree[x], k, mid)) swap(tree[x], k);
        if (check(tree[x], k, l)) update(ls, l, mid, k);
        if (check(tree[x], k, r)) update(rs, mid + 1, r, k);
    }
    inline int query(int x, int l, int r, int k) {
        if (l == r) return calc(tree[x], k);
        int mid = l + r >> 1, res = 0;
        if (k <= mid) res = query(ls, l, mid, k);
        else res = query(rs, mid + 1, r, k);
        return max(res, calc(tree[x], k));
    }
}
using namespace Seg;
inline void init() {
    n = in();
    for (int i = 1; i <= n; ++i) a[i] = in();
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + a[i];
    for (int i = 1; i <= n; ++i) tot += i * a[i];
}
inline void work() {
    ans = tot;
    build(1, -M, M);
    update(1, 1, n, Node(1, 0));
    for (int i = 2; i <= n; ++i) {
        ans = max(ans, tot + sum[i - 1] - a[i] * i + query(1, -M, M, a[i]));
        update(1, -M, M, Node(i, -sum[i - 1]));
    }
    build(1, -M, M);
    update(1, -M, M, Node(n, -sum[n]));
    for (int i = n - 1; i; --i) {
        ans = max(ans, tot + sum[i] - a[i] * i + query(1, -M, M, a[i]));
        update(1, -M, M, Node(i, -sum[i]));
    }
    out(ans, endl);
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```

---

## 作者：raincity (赞：0)

[更好的阅读体验](https://blog.calvincheng1231.org.cn/default/262.html)

## 分析
设 $sum$ 为 $a$ 的前缀和数组。

下面只考虑 $u>v$ 的情况。$u<v$ 时类似。

考虑将 $a_u$ 移动到 $a_v$ 会给答案带来多大的贡献。

显然是 $a_u\times(v-u)+sum_{u-1}-sum_{v-1}$。

整理得 $(-a_u\times u+sum_{u-1})+a_u\times v-sum_{v-1}$。

也就是所有直线 $y=vx-sum_{v-1}$ 在 $x=a_u$ 时的最大取值。

可以用李超线段树维护。时间复杂度 $O(n\log n)$。

实际有效代码只有 25 行，而且我用的是大括号换行的码风，所以其实很好写。

## 解决
```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
using LL = long long;
using LLL = __int128;

const int N = 2e5 + 5, S = 1e6 + 5;
int n, a[N];
LL sum[N], ans;

class LCST
{
private:
    int mx[N], ls[N], rs[N], k[N], cnt, root, tot;
    LL b[N];

    int New(int _k, LL _b)
    {
        cnt++, k[cnt] = _k, b[cnt] = _b;
        return cnt;
    }

    LL y(int id, int x)
    {
        return 1LL * x * k[id] + b[id];
    }

    void insert(int &k, int l, int r, int id)
    {
        if (!k)
            k = ++tot;
        if (l == r)
        {
            if (y(id, l) > y(mx[k], l))
                mx[k] = id;
            return;
        }
        int mid = ((l + r) >> 1);
        if (y(id, mid) > y(mx[k], mid))
            swap(id, mx[k]);
        if (y(id, l) > y(mx[k], l))
            insert(ls[k], l, mid, id);
        if (y(id, r) > y(mx[k], r))
            insert(rs[k], mid + 1, r, id);
    }

    LL query(int k, int l, int r, int x)
    {
        if (!k)
            return -1e18;
        if (l == r)
            return y(mx[k], x);
        int mid = ((l + r) >> 1);
        if (x <= mid)
            return max(y(mx[k], x), query(ls[k], l, mid, x));
        else
            return max(y(mx[k], x), query(rs[k], mid + 1, r, x));
    }

public:
    void insert(int _k, LL _b)
    {
        insert(root, -S, S, New(_k, _b));
    }

    LL query(int x)
    {
        return query(root, -S, S, x);
    }

    void init()
    {
        cnt = 0, tot = 1, root = 0, b[0] = -1e18;
        memset(mx, 0, sizeof(mx));
        memset(ls, 0, sizeof(ls));
        memset(rs, 0, sizeof(rs));
    }
} lcst;

template<class T>
void read(T &ret)
{
    ret = 0;
    char ch = getchar(), flag = 0;
    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if (ch == '-')
        ch = getchar(), flag = 1;
    while (ch >= '0' && ch <= '9')
        ret = ret * 10 + ch - '0', ch = getchar();
    if (flag)
        ret = -ret;
}

template<class T, class... Args>
void read(T &ret, Args &... rest)
{
    read(ret);
    read(rest...);
}

int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    lcst.init();
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, -1LL * a[i] * i + sum[i - 1] + lcst.query(a[i]));
        lcst.insert(i, -sum[i - 1]);
    }
    lcst.init();
    for (int i = n; i >= 1; i--)
    {
        ans = max(ans, -1LL * a[i] * i + sum[i] + lcst.query(a[i]));
        lcst.insert(i, -sum[i]);
    }
    for (int i = 1; i <= n; i++)
        ans += 1LL * i * a[i];
    cout << ans << endl;
    return 0;
}
```

---

## 作者：crashed (赞：0)

# 题目
  
[点这里](https://www.luogu.com.cn/problem/CF631E)看题目。  
  
# 分析
     
设未交换时的结果为 $c$，记 $s$ 为前缀和数组。   
   
那么考虑将 $i$ 交换到 $j$ 之后（$j<i$），交换的变化量为：   
   
$$
\begin{aligned}
&\Delta=(s_i-s_j-A_i)+(j+1-i)A_i\\
\Rightarrow &\Delta=(jA_i-s_j)+(s_i-iA_i)
\end{aligned}
$$

可以发现前面的括号内是关于 $j$ 和 $i$ 的函数，且不看 $A_i$ 则是 $j$ 的一次函数。   
   
因此我们可以使用李超线段树维护 $0\sim i-1$ 的这些一次函数。当然，由于斜率单调，这里可以使用单调栈维护下凸包。   
   
反过来 $j>i$ 的情况是类似的，化简的结果为：
   
$$
\Delta=(jA_i+s_j)+(-s_i-iA_i)
$$     
   
类似维护即可。时间是 $O(n\log_2n)$。   
   
# 代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

const LL INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 2e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) putchar( '-' ), x = -x;
	if( 9 < x ) write( x / 10 );
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
void swapp( _T &x, _T &y )
{
	_T t = x; x = y, y = t;
}

struct Linear
{
	LL k, b;
	Linear() { k = b = 0; }
	Linear( LL K, LL B ) { k = K, b = B; }
	LL operator () ( const LL x ) const { return k * x + b; }
};

Linear f[MAXN], func[MAXN];

LL su[MAXN], val[MAXN];
int A[MAXN], pos[MAXN], coe[MAXN];
int N, tot;

void Build( const int l, const int r )
{
	if( l > r ) return ; 
	int mid = l + r >> 1;
	f[mid] = Linear( 0, -INF );
	Build( l, mid - 1 );
	Build( mid + 1, r );
}

void Update( const int l, const int r, Linear nw )
{
	if( l > r ) return ;
	int mid = l + r >> 1;
	if( f[mid]( val[mid] ) < nw( val[mid] ) ) swapp( f[mid], nw );
	if( f[mid]( val[l] ) <= nw( val[l] ) ) Update( l, mid - 1, nw );
	else Update( mid + 1, r, nw );
}

LL Query( const int l, const int r, const int p )
{
	if( l > r ) return -INF;
	int mid = l + r >> 1; LL ret = f[mid]( val[p] );
	if( p < mid ) ret = MAX( Query( l, mid - 1, p ), ret );
	if( mid < p ) ret = MAX( Query( mid + 1, r, p ), ret );
	return ret;
}

void Discrete()
{
	tot = 0; for( int i = 1 ; i <= N ; i ++ ) val[++ tot] = A[i];
	sort( val + 1, val + 1 + tot ); tot = unique( val + 1, val + 1 + tot ) - val - 1;
	for( int i = 1 ; i <= N ; i ++ ) pos[i] = lower_bound( val + 1, val + 1 + tot, A[i] ) - val;
}

int main()
{
	read( N ); LL ans = 0, base = 0;
	for( int i = 1 ; i <= N ; i ++ ) read( A[i] ), coe[i] = i, base += 1ll * i * A[i];
	
	Discrete(), Build( 1, tot ), func[0] = Linear( 0, 0 ), Update( 1, tot, func[0] );
	for( int i = 1 ; i <= N ; i ++ ) func[i] = Linear( i, - ( su[i] = su[i - 1] + A[i] ) );
	for( int i = 1 ; i <= N ; i ++ ) ans = MAX( ans, Query( 1, tot, pos[i] ) + su[i] - 1ll * i * A[i] ), Update( 1, tot, func[i] );
	Build( 1, tot ), func[N + 1] = Linear( N + 1, 0 ), Update( 1, tot, func[N + 1] );
	for( int i = N ; i ; i -- ) func[i] = Linear( i, su[i] = su[i + 1] + A[i] );
	for( int i = N ; i ; i -- ) ans = MAX( ans, Query( 1, tot, pos[i] ) - su[i] - 1ll * i * A[i] ), Update( 1, tot, func[i] );
	
	write( ans + base ), putchar( '\n' );
	return 0;
}
```

---

