# [入门赛 #14] 魔法少女扶苏 (Hard Version)

## 题目描述

给定一个 $n$ 行 $m$ 列的数字矩阵，第 $i$ 行第 $j$ 列的数称为 $a_{i,j}$。

扶苏可以释放任意多次魔法，每次施放魔法，矩阵里的**每个**数字都会被减去 $1$。

现在扶苏想知道，她至少需要释放几次魔法，才能让矩阵中存在至少 $k$ 个位置 $(x, y)$，满足 $a_{x, y}$ 大于或等于它所在行和列的元素之和。

形式化地，你需要计算最小的魔法释放次数使得施放魔法后存在至少 $k$ 个位置 $(x, y)$，满足 $a_{x, y} \geq \sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i}$。

## 说明/提示

### 样例 1 解释

释放 $3$ 次魔法后，矩阵变为

$$\begin{matrix}-2 & -1 & 0\\1& 2&3\\\end{matrix}$$

于是 $a_{1,1} = -2 > (-1) + (-3) = \sum\limits_{i =1}^n a_{i,1} + \sum\limits_{i = 1}^m a_{1, i}$。

### 数据规模与约定

- 对 $100\%$ 的数据，保证 $1 \leq n, m \leq 3 \times 10^3$，$1 \leq k \leq n \times m$，$0 \leq a_i \leq 10^{11}$。

### 提示

**请使用合理的读入方式，避免超时。**

## 样例 #1

### 输入

```
2 3 1
1 2 3
4 5 6
```

### 输出

```
3```

# 题解

## 作者：FFTotoro (赞：7)

一道很好的大眼观察题。

对于每个元素 $a_{x,y}$，令 $s_{x,y}=\sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i}$；考虑每一次操作对 $s_{x,y}$ 与 $a_{x,y}$ 相对大小的影响。显然的一次操作会使 $s_{x,y}$ 减少 $n+m$，使 $a_{x,y}$ 减少 $1$，所以它们的相对大小 $s_{x,y}-a_{x,y}$ 会减少 $n+m-1$。

因为我们想让 $a_{x,y}\ge s_{x,y}$，即让 $s_{x,y}-a_{x,y}$ 尽快减到 $0$，所以需要的操作数即为 $\left\lceil\dfrac{s_{x,y}-a_{x,y}}{n+m-1}\right\rceil$。$s_{x,y}$ 很容易计算出，令 $r_x=\sum\limits_{i=1}^m a_{x,i}$，$c_y=\sum\limits_{i=1}^n a_{i,y}$，则 $s_{x,y}=r_x+c_y$，操作数 $\left\lceil\dfrac{s_{x,y}-a_{x,y}}{n+m-1}\right\rceil=\left\lceil\dfrac{r_x+c_y-a_{x,y}}{n+m-1}\right\rceil$。

最后考虑操作次数第 $k$ 小的数，它的操作数即为需要的操作数。找到 $k$ 小数可以使用 STL 的 `std::nth_element()` 函数。

时间复杂度 $O(nm)$，足以通过。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int div_ceil(int x,int y){
  return x/y+!!(x%y);
} // 整数除法向上取整函数
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,m,k; cin>>n>>m>>k;
  vector<vector<int> > a(n,vector<int>(m));
  for(auto &i:a)for(auto &j:i)cin>>j;
  vector<int> r(n),c(m),d;
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      r[i]+=a[i][j],c[j]+=a[i][j];
      // 预处理 r,c 数组
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      d.emplace_back(div_ceil(r[i]+c[j]-a[i][j],n+m-1));
      // 将所有操作数放进一个 std::vector
  nth_element(d.begin(),d.begin()+k-1,d.end());
  cout<<d[k-1]<<endl;
  // 找出 k 小数并输出
  return 0;
}
```

---

## 作者：cjh20090318 (赞：4)

**Update on 2023/7/16 21:51 发现优先队列的英文写错了，已经更正。**

## 分析

首先我们对于 $a_{x,y}$ 设需要至少进行 $c$ 次操作才能满足 $a_{x, y} \geq \sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i}$。

进行 $k$ 次操作后，需要满足：

$$
a_{x, y} - c \geq \sum \limits _{i = 1}^n a_{i,y} -nc + \sum \limits _{i = 1}^m a_{x,i} - mc
$$

移一下项可以得到：

$$
(n + m - 1)c \ge \sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i} - a_{x,y}
$$

因为 $n + m - 1 > 0$，所以又可以得到：

$$
c \ge \dfrac{\sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i} - a_{x,y}}{n+m-1}
$$

所以：

$$
c = \left\lceil\dfrac{\sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i} - a_{x,y}}{n+m-1}\right\rceil
$$

接着对每一个进行计算，取第 $k$ 小即可。

我用的是优先队列 `std::priority_queue`，时间复杂度 $O(nm \log k)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<queue>
int n,m,k;
long long a[3003][3003],s[3003],q[3003];//s[i] 表示第 i 行的元素之和，q[j] 表示第 j 列的元素之和。
std::priority_queue<long long> Q;//建立一个大根堆。
// #define DEBUG 1  // 调试开关
struct IO {//快读快输，这一部分可以跳过。
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
  char buf[MAXSIZE], *p1, *p2;
  char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}

  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
  char gc() {
#if DEBUG  // 调试，可显示字符
    return getchar();
#endif
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? ' ' : *p1++;
  }

  bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r';
  }

  template <class T>
  void read(T &x) {
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc());
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
  }

  void push(const char &c) {
#if DEBUG  // 调试，可显示字符
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }

  template <class T>
  void write(T x) {
    if (x < 0) x = -x, push('-');  // 负数输出
    static T sta[35];
    T top = 0;
    do {
      sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) push(sta[--top] + '0');
  }

} io;

int main(){
	io.read(n),io.read(m),io.read(k);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)io.read(a[i][j]),s[i]=s[i]+a[i][j],q[j]=q[j]+a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		Q.push((s[i]+q[j]-a[i][j]+n+m-2)/(n+m-1));//因为要向上取整，所以要加上 n+m-2。
		while((int)Q.size()>k) Q.pop();超出 k，将堆顶弹出。
	}
	io.write(Q.top());//取出第 k 小。
	return 0;
}

```

---

## 作者：sto_5k_orz (赞：3)

傻逼题，我都会。

首先，先预处理出每行和每列的和，记为 $r_i,c_j$。

然后我们考虑次数：

$$r_i+c_j-a_{i,j}$$

那么我们操作一次后，

就变成了

$$(r_i-n)+(c_j-m)-(a_{i,j}-1)$$

$$=(r_i+c_j-a_{i,j})-(n-m+1)$$

所以说，一次减少 $n+m-1$。

那么 $r_i+c_j-a_{i,j}\le 0$ 就需要操作

$$\max(0,\lceil \dfrac{r_i+c_j-a_{i,j}}{n+m-1}\rceil)$$

然后对每项排序，第 $k$ 项就是答案。

复杂度 $\mathcal{O}(nm\log nm)$，由于常数小所以能过。

[代码 1.52KB](https://www.luogu.com.cn/paste/aqtv4emf)

---

## 作者：fish_love_cat (赞：2)

数学题？

---

**思路：**

可以看出，每释放一次魔法，这个点会减一，所在行列之和会减 $n+m$。那么要让一个不满足要求的点满足要求，显然就得释放

$$\left \lceil \sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i}-a_{x,y} \right \rceil\div( n+m-1)$$ 

次魔法。

我们可以预处理出 $\sum \limits _{i = 1}^n a_{i,y}$ 和 $\sum \limits _{i = 1}^m a_{x,i}$，然后把每个点要释放的魔法数进行记录，然后排序一遍，输出第 $k$ 小的方案数即可。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[3005][3005];
int lie[3005],hang[3005];//记录
int f[10000005],top;
signed main(){
    int n,m,k; scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        scanf("%lld",&a[i][j]),hang[i]+=a[i][j],lie[j]+=a[i][j];
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        f[++top]=ceil(max((long long)0,hang[i]+lie[j]-a[i][j])*1.0/(n+m-1));//柿子
    }
    sort(f+1,f+1+top);
    printf("%lld",f[k]);//输出
	return 0;
}
```

慎用 `map` 啊！

---

## 作者：JackMerryYoung (赞：2)

# 前言

听说这题卡二分，特意来砸个场。

# 正文

最小的合法操作数？怎么又是二分？

思路非常简单，check 里面直接暴力。但是这题值域很大，显然会超时。

考虑一个小小优化。读入时直接预处理每一列和每一行的数字和。然后当 check 时减去 $(N + M) \times \operatorname{mid}$ 即可。最后统计合法数目是否大于 $K$ 即可。

由于这题卡了二分，需要加快读快输和值域取最大的 $a_i$。

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define __int128_t __int128_t
#define rint register __int128_t

__int128_t N, M, K;
__int128_t arr[3005][3005], colsum[3005], rowsum[3005];

bool check(__int128_t mid)
{
    __int128_t cnt = 0;
    for(__int128_t i = 1; i <= N; ++ i)
    {
        for(__int128_t j = 1; j <= M; ++ j)
        {
            if((arr[i][j] - mid) >= ((colsum[i] + rowsum[j]) - ((N + M) * mid))) ++ cnt;
        }
    }

    return cnt >= K;
}

char *p1,*p2,buf[100];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++)
__int128_t fastread()
{
    __int128_t x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57)
    {
        if(ch=='-')
            f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57)
        x=x*10+ch-48,ch=nc();
    return x*f;
}

void fastwrite(__int128_t x)
{
    if(x < 0) x = -x, putchar('-');
    if(x >= 10) fastwrite(x / 10);
    putchar((x % 10) ^ 48);
}

signed main()
{
    __int128_t l = 1, r = -1;
    N = fastread(), M = fastread(), K = fastread();
    for(__int128_t i = 1; i <= N; ++ i)
        for(__int128_t j = 1; j <= M; ++ j)
            arr[i][j] = fastread(), r = max(r, arr[i][j]);
    
    for(__int128_t i = 1; i <= N; ++ i)
    {
        for(__int128_t j = 1; j <= M; ++ j)
        {
            colsum[i] += arr[i][j];
            rowsum[j] += arr[i][j];
        }
    }

    // r *= 2e4;
    while(l < r)
    {
        __int128_t mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }

    fastwrite(r);
    return 0;
}
```

---

## 作者：wangif424 (赞：2)

## 过程 or 思路

- 在读入数据的同时可以处理出每行的和 $l_n$ 与每列的和 $r_m$。
- 设释放了 $c$ 次魔法，即矩阵的每一项都减去 $c$。
- 将题目中的不等式转化成 $a_{x,y} - c \ge l_x + r_y - (n+m) \times c$。
- 解不等式，得 $c \ge \frac{l_x+r_y-a_{x,y}}{n+m-1}$，得出对于每个点 $c$ 的最小取值 $c_{x,y}$，因为是大于等于，所以要对右式向上取整。
- 得出了每个点至少在 $c_{x,y}$ 次魔法后才能符合条件，于是原题目转化为：已知 $n \times m$ 个数，求第 $k$ 小的数值，直接排序解决。

## 代码附上
```cpp
#include<bits/stdc++.h>
#define R(x) x=read()
#define P(x) put(x)
#define ENDL putchar('\n');
#define SPACE putchar(' ');
#define int long long
using namespace std;
inline int read() {
	register int r=0,f=1;
	register char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0') {
		r=(r<<1)+(r<<3)+c-'0';
		c=getchar();
	}
	return r*f;
}
inline void put(int x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x>9) {
		put(x/10);
		x%=10;
	}
	putchar(x+'0');
	return;
}
int n,m,k;
int a[3100][3100];
int l[3100],r[3100];
int c[3100][3100]; 
int q[10001000],len;
signed main() {
	R(n);
	R(m);
	R(k);
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			R(a[i][j]);
			l[i]+=a[i][j];
			r[j]+=a[i][j];
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			c[i][j]=ceil((l[i]+r[j]-a[i][j])*1.0/(n+m-1));
			q[++len]=c[i][j];
		}
	}
	sort(q+1,q+1+len);
	P(q[k]);
	return 0;
}
```

---

## 作者：arrow_king (赞：1)

发现没人写二分，我来胡一个。

# 题意

给定一个 $n\times m$ 的矩阵 $a$，第 $i$ 行 $j$ 列的数是 $a_{i,j}$。

现在要求找到最小的整数 $t$，使得将每个 $a_{i,j}$ 重赋值为 $a_{i,j}-t$ 后，存在至少 $k$ 个有序数对 $(x,y)$ 使得

$$a_{x,y}\ge\sum_{i=1}^{n}a_{i,y}+\sum_{i=1}^{m}a_{x,i}$$

# 解法

显然每当 $t$ 增加 $1$ 时，$a_{x,y}$ 会减少 $1$，同时 $\sum\limits_{i=1}^{n}a_{i,y}+\sum\limits_{i=1}^{m}a_{x,i}$ 这个式子会减少 $(n+m)$。所以可以发现，$t$ 增加时，满足条件的点数一定不降。这满足单调性，所以可以二分。

二分 $t$，预处理每行每列的和，每次 check 时直接暴力统计满足条件的点数。时间复杂度是 $\mathcal O(nm\log w)$ 的，其中 $w$ 是值域上界。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 3005
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
ll n,m,k;
ll a[N][N],w[N],h[N];
il bool check(ll t) {		//二分的check函数
	ll tot=0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(a[i][j]-t>=h[j]+w[i]-(n+m)*t) tot++;
		}
	}
	return tot>=k;
}
int main() {
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
		a[i][j]=read(); 
		w[i]+=a[i][j];
		h[j]+=a[i][j];
	}
	ll l=0,r=1e11,best=0;
	while(l<=r) {			//二分
		ll mid=(l+r)>>1;
		if(check(mid)) {
			r=mid-1;
			best=mid;
		}
		else l=mid+1;
	}
	printf("%lld\n",best);
	return 0;
}

```

---

## 作者：MornStar (赞：1)

# [入门赛 #14] 魔法少女扶苏 (Hard Version) 题解
## 题面
[link](https://www.luogu.com.cn/problem/P9457)
## 思路
对于 $a_{x,y}$，如果其满足要求，即 $a_{x, y} \geq \sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i}$。

则 $0 \geq \sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i}-a_{x,y}$。

对于每一次操作，不等式右边都会减少 $n+m-1$。

所以我们只需要找到第 $k$ 小的 $\sum \limits _{i = 1}^n a_{i,y} + \sum \limits _{i = 1}^m a_{x,i}-a_{x,y}$ 计算答案就行了，注意要向上取整。
## code

```cpp
//by MornStar
#include<bits/stdc++.h>
using namespace std;
//以下read与write函数为快读快写
long long a[3005][3005],sumh[3005],suml[3005],sum[3005*3005];
int main(){
	int n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			sumh[i]+=a[i][j];
			suml[j]+=a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum[(i-1)*m+j]=sumh[i]+suml[j]-a[i][j];
		}
	}
	sort(sum+1,sum+n*m+1);
	write((sum[k]+n+m-2)/(n+m-1));
}
```

---

## 作者：c1ampy (赞：1)

在扶苏释放 $ c $ 次魔法后，对于满足条件的位置 $ (x, y) $ 有
$$
a_{x, y} - c \ge \sum_{i = 1}^n a_{i, y} - nc + \sum_{i = 1}^m a_{x, i} - mc
$$

解不等式，得
$$
c \ge \frac{\sum_{i = 1}^n a_{i, y} + \sum_{i = 1}^m a_{x, i} - a_{x, y}}{n + m - 1}
$$

由 $ c \in \mathbb{N} $ 且最小，可知
$$
c = \left \lceil \frac{\sum_{i = 1}^n a_{i, y} + \sum_{i = 1}^m a_{x, i} - a_{x, y}}{n + m - 1} \right \rceil
$$

我们在读入时顺便预处理 $ \sum_{i = 1}^n a_{i, y} $ 与 $ \sum_{i = 1}^m a_{x, i} $，就可以在 $ \mathcal{O}(1) $ 的时间内对每个 $ a_{x, y} $ 计算出对应的最小的 $ c $。计算出 $ nm $ 个 $ c $ 值的总时间复杂度为 $ \mathcal{O}(nm) $。

求出所有的 $ c $ 后，只需找出其中第 $ k $ 小的即可。

至此，这道题就转化成了[P1923 求第 k 小的数](https://www.luogu.com.cn/problem/P1923)，敲板子即可，时间复杂度为 $ \mathcal{O}(nm) $。（虽然直接 $ \mathcal{O}(nm\log(nm)) $ 排序好像也可以卡过去）

（不过本着“不要重复造轮子”的原则我们还是果断选择 `std::nth_element`）

代码如下：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

const int max_r = 3e3 + 10;
const int max_c = 3e3 + 10;

long long a[max_r][max_c];
long long sum_r[max_r];
long long sum_c[max_c];
std::vector <long long> ans;

long long fast_read();

int main() {

	int r = fast_read(), c = fast_read(), k = fast_read();
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			a[i][j] = fast_read();
			sum_r[i] += a[i][j];
			sum_c[j] += a[i][j];
		}
	}

	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			ans.push_back((long long)ceil((double)(sum_r[i] + sum_c[j] - a[i][j]) / (r + c - 1)));
		}
	}

	std::nth_element(ans.begin(), ans.begin() + k - 1, ans.end());

	printf("%lld\n", std::max(*(ans.begin() + k - 1), 0ll));

	return 0;
}

inline long long fast_read() {
	char ch = getchar();
	while (ch < '0' || '9' < ch) {
		ch = getchar();
	}
	long long res = 0;
	while ('0' <= ch && ch <= '9') {
		res = (res << 3) + (res << 1) + (ch ^ 48);
		ch = getchar();
	}
	return res;
}
```

注：代码中 `r` 对应题目中的 $ n $，`c` 对应题目中的 $ m $。

---

## 作者：Halberd_Cease (赞：0)

## 解析
 
因为每个数字同时减去 $1$，所以我们可以用两个数组分别表示每一行和每一列的和。

对于每一个数，如果直接满足条件的话答案就是 $0$。

否则我们可以把这一行的和这一列的总和加起来，减去当前的数字，可以表示总共需要减去多少，而一次减去的数，就是行数加列数在减去 $1$。

可以参考代码理解一下:
```cpp
int x=a[i][j];
if(x>=sum_x[i]+sum_y[j])ans[i*m+j-m]=0;
else
{
     int now=sum_x[i]+sum_y[j]-a[i][j];
     now=ceil(now*1.0/(n+m-1));
     ans[i*m+j-m]=now;
}
```

然后我们就得到了一个数组，存的是所有数要满足条件的答案。

因为所有的操作是共享的，所以说答案排序后的第 $k$ 个，即是最少得操作次数。

---

## 作者：technopolis_2085 (赞：0)

通过分析，可以知道：

当施展魔法的次数越多时，越有可能实现目标。

所以答案具有单调性。可以通过二分答案求出。

由于涉及到行和列的和，我们可以预处理出每行、每列的和。

假设当前二分到的答案是 $x$。

所以当满足如下条件时，本位置符合要求。

```cpp
a[i][j]-x>=row[i]+col[j]-n*x-m*x
```

所以，当符合要求的数量大于等于 $k$ 时，本答案符合要求。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int maxn=3e3+10;
int a[maxn][maxn];
int row[maxn],col[maxn];
int n,m,k;

bool check(int x){
	int cnt=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (a[i][j]-x>=row[i]+col[j]-n*x-m*x) cnt++;
		}
	}
	return cnt>=k;
} 

signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) scanf("%lld",&a[i][j]);
	}
	
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) row[i]+=a[i][j];
	}
	
	for (int j=1;j<=m;j++){
		for (int i=1;i<=n;i++) col[j]+=a[i][j];
	//	printf("%lld\n",col[j]);
	}
	
	int l=0,r=1e12;
	int ans=1e12;
	
	while (l<=r){
		int mid=(l+r)/2;
		
		if (check(mid)){
			ans=mid;
			r=mid-1;
		}else l=mid+1;
	}
	
	printf("%lld\n",ans);
	return 0;
}
```


---

