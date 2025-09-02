# [ABC268E] Chinese Restaurant (Three-Star Version)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc268/tasks/abc268_e

回転テーブルの周りに人 $ 0 $、人 $ 1 $、$ \ldots $、人 $ N-1 $ がこの順番で反時計回りに等間隔で並んでいます。また、人 $ i $ の目の前には料理 $ p_i $ が置かれています。  
 あなたは次の操作を $ 0 $ 回以上何度でも行うことが出来ます。

- 回転テーブルを反時計回りに $ 1 $ 周の $ \frac{1}{N} $ だけ回す。これによって、(この操作の直前に)人 $ i $ の目の前にあった料理は人 $ (i+1)\ \bmod\ N $ の目の前に移動する。

操作を完了させた後において、人 $ i $ の不満度は料理 $ i $ が人 $ (i-k)\ \bmod\ N $、人 $ (i+k)\ \bmod\ N $ のいずれかの目の前に置かれているような最小の非負整数 $ k $ です。  
 $ N $ 人の不満度の総和の最小値を求めてください。

  $ a\ \bmod\ m $ とは 整数 $ a $ と正整数 $ m $ に対し、$ a\ \bmod\ m $ は $ a-x $ が $ m $ の倍数となるような $ 0 $ 以上 $ m $ 未満の整数 $ x $ を表します。(このような $ x $ は一意に定まることが証明できます)

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ p_i\ \leq\ N-1 $
- $ i\ \neq\ j $ ならば $ p_i\ \neq\ p_j $
- 入力はすべて整数

### Sample Explanation 1

操作を $ 1 $ 回行うと下の画像のようになります。 !\[\](https://img.atcoder.jp/abc268/70536a7b7fad87d6a49ad00df89a4a30.png) この時、不満度の総和が $ 2 $ になることを以下のように確かめられます。 - 人 $ 0 $ の不満度は、料理 $ 0 $ が人 $ 3\ (=(0-1)\ \bmod\ 4) $ の目の前に置かれているので $ 1 $ です。 - 人 $ 1 $ の不満度は、料理 $ 1 $ が人 $ 1\ (=(1+0)\ \bmod\ 4) $ の目の前に置かれているので $ 0 $ です。 - 人 $ 2 $ の不満度は、料理 $ 2 $ が人 $ 2\ (=(2+0)\ \bmod\ 4) $ の目の前に置かれているので $ 0 $ です。 - 人 $ 3 $ の不満度は、料理 $ 3 $ が人 $ 0\ (=(3+1)\ \bmod\ 4) $ の目の前に置かれているので $ 1 $ です。 不満度の総和を $ 2 $ より小さくすることは出来ないため、答えは $ 2 $ です。

## 样例 #1

### 输入

```
4
1 2 0 3```

### 输出

```
2```

## 样例 #2

### 输入

```
3
0 1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
10
3 9 6 1 7 2 8 0 5 4```

### 输出

```
20```

# 题解

## 作者：YxYe (赞：5)

# [[ABC268E] 中国餐馆（三星版本）题解](https://www.luogu.com.cn/problem/AT_abc268_e)

很妙的一道思维题，细节比较多。

## 题意

$n$ 个人围圆桌吃饭，每个人有一个最喜欢的菜在转盘上，定义一个菜和人的距离为他们最少需要转几个单位的转盘才能重合，求转动转盘所能达到的最小距离和。

## 思路

我会暴力！直接暴力跑每次求答案 $O(n^2)$ 肯定会超时。

我会优化！考虑每次答案能否转移。对于每一个人，考虑其对于答案的影响，显然其产生的贡献是一段单增一段单减的函数。那么，我们只需要维护单增和单减的中转点的时刻即可！这样就可以优化掉求答案的一维啦！

我会细节！我们需要维护一个偏移量 $dx$ 表示上一次中转点到这一次中转点之间会发生的单位贡献偏移，同时维护上次的位置 $pre$，记这一次的位置为 $now$，这样每轮的偏移答案即为 $(now-pre)\times dx$。对于维护中转点，本蒟蒻使用了优先队列维护其位置编号和单位偏移量，因为懒得写小根堆，所以存了负数。关于 $n$ 为奇数，注意中间中转点有两个，这中间不产生贡献偏移！

我会画图！看看图片有助于理解：

（考虑 $n=5$，对于点 $3$ 的转移情况，注意 $3$ 本身也是中转点）

![](https://cdn.luogu.com.cn/upload/image_hosting/wj33zhra.png)

我会实现！以下为本蒟蒻的代码，自认为比较精简。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
#define int long long
#define db double
#define pii pair<int, int>
#define fir first
#define sec second
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
const int maxn=2e5+10;
int n,sum,dx,a[maxn];
priority_queue<pii >q;
signed main(){
	n=read();
	for(int i=0;i<n;i++){
		a[i]=read();
		int ld=(a[i]-i+n)%n,rd=(ld+n/2)%n;
		if(ld<=n-ld){
			sum+=ld;
			dx--;
			q.push(pii(-ld,2));//+2一个抵消一个贡献
			if(rd!=0){//记得特判！ 
				if(n&1)q.push(pii(-rd,-1)),q.push(pii(-(rd+1),-1));//单数中转段为0贡献 
				else q.push(pii(-rd,-2)); //-2一个抵消一个贡献
			}
		}else{
			sum+=n-ld;
			dx++;
			if(n&1)q.push(pii(-rd,-1)),q.push(pii(-(rd+1),-1));//单数中转段为0贡献 
			else q.push(pii(-rd,-2));//-2一个抵消一个贡献
			q.push(pii(-ld,2));//+2一个抵消一个贡献
		}
	}
	int ans=sum,pre=0;
	while(!q.empty()){
		if(pre^(-q.top().fir)){//统计总转移答案 
			sum+=(-q.top().fir-pre)*dx;ans=min(ans,sum);
			pre=-q.top().fir;
		}
		dx+=q.top().sec;//更新单位偏移量 
		q.pop();
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：cosf (赞：3)

二阶差分。

令 $s_j$ 表示逆时针旋转餐桌 $j$ 次的结果（$0 \le j \lt n$）。可以发现，$s_j$ 可以描述为 $n$ 个人的和。

如果 $n$ 为偶数，则对于每个人，假设他的菜初始在他右侧 $p_0(p_0 \le \frac{n}{2})$ 处，则他对 $s_j$ 的贡献为：

$$
s_j(0) = \{p_0, p_0 + 1, \dots, \frac{n}{2}, \frac{n}{2} - 1, \dots, 0, 1, \dots, p_0 - 1\}
$$

求个差分：

$$
\Delta s_j(0) = \{p_0, 1, 1, \dots, 1, -1, -1, \dots, -1, 1, 1, \dots, 1\}
$$

再求一次：

$$
\Delta(\Delta s_j(0)) = \{p_0, 1 - p_0, 0, 0, \dots, 0, -2, 0, 0, \dots, 0, 2, 0, \dots, 0\}
$$

可以发现只有 $O(1)$ 个地方是有值的了。

对于左侧 $p_0 \le \frac{n}{2}$ 的情况：

$$
s_j(0) = \{p_0, p_0 - 1, \dots, 1, 0, 1, \dots, \frac{n}{2}, \frac{n}{2} - 1, \dots, p_0 + 1\}
$$

求二阶差分：

$$
\Delta(\Delta s_j(0)) = \{p_0, -1-p_0, 0, 0, \dots, 0, 2, 0, 0, \dots, 0, -2, 0, \dots, 0\}
$$

如果 $n$ 是奇数，情况稍多，但情况类似，不再赘述。

因此，对于每一个人，把他对答案的二阶差分加起来，再算两次前缀和，求 $\min$ 即答案，时间复杂度 $O(n)$。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 400005

using ll = long long;

int n;

ll s[MAXN];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll p;
        cin >> p;
        int d = (i + n - p) % n;
        s[d + 1] += 2;
        if (d <= n / 2)
        {
            s[0] += d;
            s[1] -= d;
            s[1]--;
            s[d + 1 + n / 2]--;
            if (n % 2)
            {
                s[d + 2 + n / 2]--;
            }
            else
            {
                s[d + 1 + n / 2]--;
            }
        }
        else
        {
            s[0] += n - d;
            s[1] -= n - d;
            s[1]++;
            s[d + 1 - n / 2]--;
            if (n % 2)
            {
                s[d - n / 2]--;
            }
            else
            {
                s[d + 1 - n / 2]--;
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        s[i] += s[i - 1];
    }
    for (int i = 1; i < n; i++)
    {
        s[i] += s[i - 1];
    }
    cout << *min_element(s, s + n) << endl;
    return 0;
}

```

---

## 作者：Expert_Dream (赞：3)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

首先，对于每一个人 $i$ 都有自己想要匹配的 $i$ 餐桌。于是想到，转动餐桌会使得餐盘离这个人出现两种情况：

- 先递减再递增
- 先递增再递减

很容易想到，这其实可以看作一个很多条一次函数的直角坐标系。我们需要手推一下每一个点的地方，然后跑两遍前缀和就可以解决。由于奇偶的情况不一样，所以要分讨，但其实我们只需要建立顶点 $i+\dfrac{n}{2}+1$ 和 $i+\dfrac{n+1}{2}+1$ 即可。

因为我们想要把直线直接延伸到比 $n$ 大的地方以免发生取模错误。所以直接 $+n$ 地套上去。

[link](https://atcoder.jp/contests/abc268/submissions/49023244)。

---

## 作者：Tsawke (赞：2)

#  [[ABC268E] Chinese Restaurant (Three-Star Version)](https://www.luogu.com.cn/problem/AT_abc268_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC268E)

## 题面

$ n $ 个人进行圆排列，即围坐在圆桌周围，位置编号依次为 $ [0, n - 1] $，给定序列 $ P_n $ 表示第 $ i $ 个人喜欢的菜品在 $ P_i $ 处，$ P_i \in [0, n - 1] $ 且各不相同。定义每个人的沮丧值为其位置与 $ P_i $ 的距离。你可以任意旋转圆桌，以最小化所有人的沮丧值之和，求最小值。

## Solution

可以说是一道思路较为简单但**细节巨多**，**非常难调**的题，到处各种加加减减与分类讨论，这么一道水题最后我写了一个半点。

首先我们可以想到，我们认为初始状态为 $ i $ 在 $ i - 1 $，然后认为初始状态之后转的格数为 $ x $ 轴，对于一个特定的人的沮丧值为 $ y $ 轴，不难想到图像应为至多三段斜率为 $ 1 $ 或 $ -1 $ 的线段组成，同时若点数为奇数，那么在距离 $ P_i $ $ \lfloor \dfrac{n}{2} \rfloor $ 和 $ \lceil \dfrac{n}{2} \rceil $ 的对应位置的值是相同的，也就是此时斜率应为 $ 0 $，但有且仅有这么一段。对于答案我们只需要将每个人的情况都合并起来求一下最小值即可，考虑如何维护。

于是我们直接考虑 $ y $ 轴的值，对于一个人的变化量显然是类似 $ -1, -1, -1, 1, 1, 1, 0, 1, \cdots $ 等，这个东西等于是做了个差分。不难发现这东西如果用线段树维护区间修改，那么最终复杂度应为 $ O(n \log n) $ 的，不过我不想写线段树，于是考虑另一种写法，不难发现这东西是很多个区间修改，所以可以对差分数组再次做差分，即二阶差分，此时我们只需要在转折点处做一下修改即可，这样最后做两次前缀和求个最大值即可。

不难发现这东西思路显然看起来很简单，但是当实现的时候就会发现阴间的地方在哪了。首先我们发现有四种情况，即 $ i $ 与 $ p_i $ 的偏序关系，和 $ (i - p_i) \bmod{n} $ 与 $ (p_i - i) \bmod{n} $ 的偏序关系。但是经过讨论我们会发现，前者的偏序关系是无意义的，因为我们求距离时可以直接转正，即 $ dis = (i - p_i + n) \bmod{n} $，所以此时优化情况为两种。

具体情况可以自己画一下然后看看代码，还是比较显然的，只是细节太多了。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N;
int P[210000];
ll d[210000];
ll ans(LONG_LONG_MAX);

int main(){
    N = read();
    for(int i = 0; i <= N - 1; ++i)P[i] = read();
    for(int i = 0; i <= N - 1; ++i)d[0] += min((i - P[i] + N) % N, (P[i] - i + N) % N);
    d[1] = -d[0];
    for(int i = 0; i <= N - 1; ++i)
        if((P[i] - i + N) % N <= (i - P[i] + N) % N){
            int dis = (P[i] - i + N) % N;
            d[1]--, d[dis + 1]++;
            d[dis + 1]++, d[dis + (N >> 1) + 1]--;
            d[dis + (N >> 1) + 1 + (N & 1 ? 1 : 0)]--;
        }else{
            int dis = (i - P[i] + N) % N;
            d[1]++, d[(N >> 1) - dis + 1]--;
            d[(N >> 1) - dis + 1 + (N & 1 ? 1 : 0)]--;
            d[N - dis + 1]++, d[N - dis + 1]++;
        }
    for(int i = 1; i <= N - 1; ++i)d[i] = d[i - 1] + d[i];
    for(int i = 1; i <= N - 1; ++i)d[i] = d[i - 1] + d[i];
    for(int i = 0; i <= N - 1; ++i)ans = min(ans, d[i]);
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_18 初稿

---

## 作者：hyxgg (赞：1)

[题目](https://www.luogu.com.cn/problem/AT_abc268_e)

## 思路
其实没必要动脑子，暴力使用***线段树***。

我们可以先将菜品位置与人菜距离的关系转化成旋转距离与人菜距离的关系。

可以开一个数组:$a_i$ 表示旋转 $i$ 个人的距离时的沮丧值之和。

此时我们发现每个菜品对于 $a$ 数组的贡献必然是两个等差数列。

于是可以通过在一个区间里维护端点上的值和公差来维护 $a$ 数组，线段树可以无脑解决（其实可以不用线段树，但线段树最无脑）。

值得注意的是其为一个环状的数组，可以通过将环上的一个等差数列分段来解决。

## 代码
```c++
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll n, p[200005];
struct xds {
    ll l, r, z, bj[2], zl[2];
} yd[800005];
void js(ll b, ll l, ll r) {
    yd[b] = { l, r, 0, 0, 0 };
    if (l == r)
        return;
    ll mid = (l + r) >> 1;
    js(b << 1, l, mid), js(b << 1 | 1, mid + 1, r);
}
void down(ll b) {
    ll lz = b << 1, rz = b << 1 | 1;
    yd[lz].bj[0] += yd[b].bj[0], yd[lz].zl[0] += yd[b].zl[0],
        yd[lz].bj[1] += yd[b].bj[1] + yd[b].zl[1] * (yd[b].r - yd[lz].r);
    yd[lz].zl[1] += yd[b].zl[1];
    yd[rz].bj[1] += yd[b].bj[1], yd[rz].zl[1] += yd[b].zl[1],
        yd[rz].bj[0] += yd[b].bj[0] + yd[b].zl[0] * (yd[rz].l - yd[b].l);
    yd[rz].zl[0] += yd[b].zl[0];
    yd[b].bj[1] = yd[b].bj[0] = yd[b].zl[0] = yd[b].zl[1] = 0;
}
void gc(ll b, ll x, ll y, ll lx, ll kz) {
    if (x > y)
        return;
    if (yd[b].l >= x && yd[b].r <= y) {
        yd[b].bj[lx] += (lx == 0) ? (kz + yd[b].l - x) : (kz + y - yd[b].r), yd[b].zl[lx]++;
        return;
    }
    down(b);
    if (yd[b << 1].r >= x)
        gc(b << 1, x, y, lx, kz);
    if (yd[b << 1].r < y)
        gc(b << 1 | 1, x, y, lx, kz);
}
ll cd(ll b, ll x) {
    if (yd[b].l == yd[b].r) {
        return yd[b].bj[1] + yd[b].bj[0];
    }
    down(b);
    if (yd[b << 1].r >= x)
        return cd(b << 1, x);
    else
        return cd(b << 1 | 1, x);
}
int main() {
    scanf("%lld", &n);
    js(1, 1, n);
    const ll zc = (n - 1) / 2;
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &p[i]);
        p[i]++;
        ll bs = (p[i] - i + n - 1) % n + 1, wz = (bs - zc + n - 1) % n + 1;
        if (wz < bs) {
            gc(1, wz, bs - 1, 1, 1);
            gc(1, bs + 1, n, 0, 1);
            gc(1, 1, wz - 1, 0, (n - bs) + 1);
        } else {
            gc(1, 1, bs - 1, 1, 1);
            gc(1, wz, n, 1, bs);
            gc(1, bs + 1, wz - 1, 0, 1);
        }
    }
    ll ans = 1145141919810;
    for (ll i = 1; i <= n; i++) {
        ans = min(ans, cd(1, i));
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：bryce (赞：1)

## [[ABC268E] Chinese Restaurant (Three-Star Version)](https://www.luogu.com.cn/problem/AT_abc268_e)
### 思路
由于沮丧值与菜的移动的次数有关，所以求出每个移动次数的贡献，而每个移动次数的贡献又由前一个移动次数的贡献转移而来。

所以，当一个菜移动时，会对一个人产生连续的沮丧值增加或减少，特别地，当 $n$ 为奇数时，会有沮丧值不变的情况，这些改变沮丧值走向的端点可以分类讨论快速求出，于是考虑差分，当第 $i$ 个人的菜靠近他时，沮丧值会 $-1$，反之会 $+1$，有时还会不变，即为 $0$，对差分数组求前缀和即为当前这个菜移动此时次数对沮丧值增加或减少了多少。那么先求出初始状态的总的沮丧值，由于 $+1$，$-1$ 都是连续的，可以用线段树实现，然后在 $n$ 为奇数时特判 $0$ 的情况，最后统计答案时对每个移动次数做一次前缀和，即为总的沮丧值改变量，用初始状态的沮丧值加上它求最小值即可。
### 代码
```cpp
#include<iostream>
#include<cmath>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 2e5 + 10;
int n, sum, ans = 0;
int a[N];
int get(int a, int b){
    if (a < 0) return (a % b == 0 ? a / b : a / b - 1);
    return a / b;
}
struct tree{
    int sum, tag;
}t[N << 2];
void pushup(int now){
    t[now].sum = t[now << 1].sum + t[now << 1 | 1].sum;
}
void pushdown(int now, int l, int r){
    int mid = (l + r) >> 1;
    t[now << 1].sum += t[now].tag * (mid - l + 1), t[now << 1 | 1].sum += t[now].tag * (r - mid);
    t[now << 1].tag += t[now].tag, t[now << 1 | 1].tag += t[now].tag;
    t[now].tag = 0;
}
void modify(int now, int l, int r, int x, int y, int k){
    if (x <= l && r <= y){
        t[now].sum += k * (r - l + 1);
        t[now].tag += k;
        return;
    }
    pushdown(now, l, r);
    int mid = (l + r) >> 1;
    if (x <= mid) modify(now << 1, l, mid, x, y, k);
    if (mid + 1 <= y) modify(now << 1 | 1, mid + 1, r, x, y, k);
    pushup(now);
}
int query(int now, int l, int r, int x, int y){
    if (x <= l && r <= y){
        return t[now].sum;
    }
    pushdown(now, l, r);
    int mid = (l + r) >> 1, res = 0;
    if (x <= mid) res += query(now << 1, l, mid, x, y);
    if (mid + 1 <= y) res += query(now << 1 | 1, mid + 1, r, x, y);
    return res;
}

signed main(){
    n = read();
    for (int i = 0; i < n; i++){
        a[i] = read();
        int x = min(i, a[i]), y = max(i, a[i]);
        sum += min(y - x, x + n - y);
    }
    for (int i = 0; i < n; i++){
        if (n & 1){
            if (i <= a[i]){
                int k = get(n + 2 * i - 2 * a[i], 2), g = get(3 * n + 2 * i - 2 * a[i], 2);
                if (1 <= min(k, n)) modify(1, 1, n, 1, min(k, n), 1);
                if (1 <= k + 1 && k + 1 <= n) modify(1, 1, n, k + 1, k + 1, 0);
                if (max(k + 2, 1ll) <= min(n + i - a[i], n)) modify(1, 1, n, max(k + 2, 1ll), min(n + i - a[i], n), -1);
                if (max(n + i - a[i] + 1, 1ll) <= min(g, n)) modify(1, 1, n, max(n + i - a[i] + 1, 1ll), min(g, n), 1);
                if (1 <= g + 1 && g + 1 <= n) modify(1, 1, n, g + 1, g + 1, 0);
                if (max(g + 2, 1ll) <= n) modify(1, 1, n, max(g + 2, 1ll), n, -1);
            }else{
                int k = n / 2, g = get(2 * i - n - 2 * a[i], 2);
                if (1 <= min(g, n)) modify(1, 1, n, 1, min(g, n), 1);
                if (1 <= g + 1 && g + 1 <= n) modify(1, 1, n, g + 1, g + 1, 0);
                if (max(g + 2, 1ll) <= min(i - a[i], n)) modify(1, 1, n, max(g + 2, 1ll), min(i - a[i], n), -1);
                if (max(i - a[i] + 1, 1ll) <= min(i - a[i] + k, n)) modify(1, 1, n, max(i - a[i] + 1, 1ll), min(i - a[i] + k, n), 1);
                if (1 <= i - a[i] + k + 1 && i - a[i] + k + 1 <= n) modify(1, 1, n, i - a[i] + k + 1, i - a[i] + k + 1, 0);
                if (max(i - a[i] + k + 2, 1ll) <= n) modify(1, 1, n, max(i - a[i] + k + 2, 1ll), n, -1);
            }
        }else{
            if (i <= a[i]){
                int k = get(n + 2 * i - 2 * a[i], 2), g = get(3 * n + 2 * i - 2 * a[i], 2);
                if (1 <= min(k, n)) modify(1, 1, n, 1, min(k, n), 1);
                if (max(k + 1, 1ll) <= min(n + i - a[i], n)) modify(1, 1, n, max(k + 1, 1ll), min(n + i - a[i], n), -1);
                if (max(n + i - a[i] + 1, 1ll) <= min(g, n)) modify(1, 1, n, max(n + i - a[i] + 1, 1ll), min(g, n), 1);
                if (max(g + 1, 1ll) <= n) modify(1, 1, n, max(g + 1, 1ll), n, -1);
            }else{
                int k = n / 2, g = get(2 * i - n - 2 * a[i], 2);
                if (1 <= min(g, n)) modify(1, 1, n, 1, min(g, n), 1);
                if (max(g + 1, 1ll) <= min(i - a[i], n)) modify(1, 1, n, max(g + 1, 1ll), min(i - a[i], n), -1);
                if (max(i - a[i] + 1, 1ll) <= min(i - a[i] + k, n)) modify(1, 1, n, max(i - a[i] + 1, 1ll), min(i - a[i] + k, n), 1);
                if (max(i - a[i] + k + 1, 1ll) <= n) modify(1, 1, n, max(i - a[i] + k + 1, 1ll), n, -1);
            }
        }
    }
    for (int i = 1; i <= n; i++) ans = min(ans, query(1, 1, n, 1, i));
    cout << min(sum, sum + ans);
    return 0;
}
```

---

