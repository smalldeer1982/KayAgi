# Boboniu and String

## 题目描述

Boboniu defines BN-string as a string $ s $ of characters 'B' and 'N'.

You can perform the following operations on the BN-string $ s $ :

- Remove a character of $ s $ .
- Remove a substring "BN" or "NB" of $ s $ .
- Add a character 'B' or 'N' to the end of $ s $ .
- Add a string "BN" or "NB" to the end of $ s $ .

Note that a string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

Boboniu thinks that BN-strings $ s $ and $ t $ are similar if and only if:

- $ |s|=|t| $ .
- There exists a permutation $ p_1, p_2, \ldots, p_{|s|} $ such that for all $ i $ ( $ 1\le i\le |s| $ ), $ s_{p_i}=t_i $ .

Boboniu also defines $ \text{dist}(s,t) $ , the distance between $ s $ and $ t $ , as the minimum number of operations that makes $ s $ similar to $ t $ .

Now Boboniu gives you $ n $ non-empty BN-strings $ s_1,s_2,\ldots, s_n $ and asks you to find a non-empty BN-string $ t $ such that the maximum distance to string $ s $ is minimized, i.e. you need to minimize $ \max_{i=1}^n \text{dist}(s_i,t) $ .

## 说明/提示

In the first example $ \text{dist(B,BN)}=\text{dist(N,BN)}=1 $ , $ \text{dist(BN,BN)}=0 $ . So the maximum distance is $ 1 $ .

## 样例 #1

### 输入

```
3
B
N
BN```

### 输出

```
1
BN```

## 样例 #2

### 输入

```
10
N
BBBBBB
BNNNBBNBB
NNNNBNBNNBNNNBBN
NBNBN
NNNNNN
BNBNBNBBBBNNNNBBBBNNBBNBNBBNBBBBBBBB
NNNNBN
NBBBBBBBB
NNNNNN```

### 输出

```
12
BBBBBBBBBBBBNNNNNNNNNNNN```

## 样例 #3

### 输入

```
8
NNN
NNN
BBNNBBBN
NNNBNN
B
NNN
NNNNBNN
NNNNNNNNNNNNNNNBNNNNNNNBNB```

### 输出

```
12
BBBBNNNNNNNNNNNN```

## 样例 #4

### 输入

```
3
BNNNBNNNNBNBBNNNBBNNNNBBBBNNBBBBBBNBBBBBNBBBNNBBBNBNBBBN
BBBNBBBBNNNNNBBNBBBNNNBB
BBBBBBBBBBBBBBNBBBBBNBBBBBNBBBBNB```

### 输出

```
12
BBBBBBBBBBBBBBBBBBBBBBBBBBNNNNNNNNNNNN```

# 题解

## 作者：WYXkk (赞：25)

首先，我们关注一下“相似”是什么意思：它等价于，两个字符串中 `B` 和 `N` 的数量分别相同。

显然地我们可以发现，每次操作，相当于给字符串加或减一个 `B` 或 `N` 或`BN`。

把每个字符串中 `B` 的个数作为横坐标，`N` 的个数作为纵坐标，找到其对应点。

那么，每次操作，就相当于把这个点的位置往左或右或上或下或右上或左下移动一步，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/72611aky.png)

由于两个点都操作和仅操作一个点没有区别，因此，等价于我们要找到一个点 $T$，其到 $n$ 个点的“距离”的最大值最小。

显然想到二分，因此只需要判断距离 $n$ 个点 $l$ 的区域有没有交集即可。

观察可知，这个区域长下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ral9cxsl.png)

如何限定这个区域呢？由于它是凸的，所以可以用线性规划描述，如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/s6ctcmbz.png)

即可得到六个限制条件：
$$\begin{cases}x\le x_0+l\\x \ge x_0-l\\y\le y_0+l\\y\ge y_0-l\\x-y \le x_0-y_0+l\\x-y \ge x_0-y_0-l\end{cases}$$

将 $n$ 个限制条件取交集，就可以得到 $x,y,x-y$ 分别的取值范围。

假设 $x\in[xi,xa],y\in[yi,ya],x-y\in[zi,za]$（这里 $i,a$ 分别是 $\min,\max$ 的简写），那么：

- 三个区间如果有任意一个为空，则不成立
- 假如三个都非空，则若 $[xi-ya,xa-yi]$ 与 $[zi,za]$ 不相交则不成立，否则成立。

现在只需要构造答案了。

假设我们如上求出了 $x,y,x-y$ 的范围，那么显然有 $x \in[yi+zi,ya+za]$，与 $[xi,xa]$ 取交集后求出 $x$ 的一个值，然后便有 $y\in[x-za,x-zi]$，与 $[yi,ya]$ 取交集后求出  $y$ 的一个值，即可。

于是这题就做完了。代码见 [Codeforces submission 89750872](https://codeforces.com/contest/1394/submission/89750872)（主站上不去请换成镜像站试试）。



---

## 作者：Froranzen (赞：3)

半平面交有点太极端了。

因为要使得操作次数最大值最小，所以二分操作次数至多几次，设为 $w$。

容易发现，“相似”即为 $s$ 中 $B,N$ 的数量与 $t$ 中的一致。

于是以 $B$ 的数量为横坐标，$N$ 的数量为纵坐标建立坐标系。

分析一下各种操作。这等同于我们一次可以向上、下、左、右、左下、右上方向走一步。
 

对于一个点 $P$，至多走 $x$ 步能到达它的点的范围如下图：

![描述](https://cdn.luogu.com.cn/upload/image_hosting/wsash3el.png?x-oss-process=image/resize,m_lfit,h_680,w_900)
 

如果这个六边形能把所有的点都包含，那么就是合法的。

我们贪心地让下边界贴到某个点上，这一定不劣。

设其纵坐标最小的点为 $q$，$q$ 的纵坐标为 $d$。不妨假设 $q$ 贴在六边形的左下边界，那么此时已经固定了六边形的下边界。同时设六边形的左边界的横坐标为 $L$。我们肯定希望左边界越靠右越好。

那么对于一个位于六边形左半边的点 $i$，要满足 $ y_i \leq d + w +  x_i - L \leq d + 2w$，不然就会超出上边界。移项可得 $L \leq d +w+ x_i - y_i$。于是我们可以得到一个最大的 $L$。那么我们就已经确定了这个六边形。

对于右半边的点，要满足 $x_i - (L + w) + d \leq y_i \leq d + 2w$。

但是有可能 $q$ 并不在六边形的左下部分，这就会导致 $q$ 低于六边形的右下边界，此时就需要进行调整。

（下面的图里面， $q$ 写成 $p$ 了，问题不大）

![描述](https://cdn.luogu.com.cn/upload/image_hosting/pph8f386.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

发现这个时候，所有点的一定都在六边形的上边界之下，那么我们将六边形往下平移，直到碰到一个点。

![描述](https://cdn.luogu.com.cn/upload/image_hosting/a9yrzbyf.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

此时如果右半边仍然有不合法的点，因为已经无法再调整了，所以 $w$ 就是非法的。



复杂度 $O(n \log n)$。

```cpp

const int N = 5e5 + 5;
int n;
char s[N];
int lx, ly, mn;
int x[N], ny[N], y[N], m;

struct node {
    int a, b;
}p[N];

bool cmp (node a, node b) { 
    if(a.a == b.a) return a.b < b.b;
    return a.a < b.a;
}

int d[N];

bool check (int res) {
    if((x[m] - x[1] + 1) / 2 > res) return 0;
    int L = x[1];
    re(i, m) {
        d[i] = y[i] - res;
        L = min(L, x[i] - d[i]);
        if(d[i] > res) return 0;
        if(2 * res < y[i]) return 0;
    }
    int lc = inf;
    re(i, m) {
        if(L + res >= x[i]) {
            int w = res + x[i] - L - y[i];
            lc = min(lc, w);
        }
        else {
            int w = 2*res - y[i];
            lc = min(lc, w);
        }
    } 
    re(i, m) {
        if(L + res < x[i]) {
            int dis = x[i] - (L + res); 
            if(ny[i] < mn + dis - lc) return 0;
        } 
    } 
    lx = L + res, ly = mn - lc + res;
    return 1;
}

int main () {
    read(n); 
    mn = inf;
    re(i, n) {
        scanf("%s", s + 1);
        int m = strlen(s + 1);
        re(j, m) {
            if(s[j] == 'B') ++p[i].a;
            else ++p[i].b;
        }  
        mn = min(mn, p[i].b);
    }    
    sort(p + 1, p + n + 1, cmp); 
    p[0].a = -1;
    p[n+1].a = -1;
    re(i, n+1) {
        if(p[i].a != p[i-1].a) {
            if(i != 1) {
                ++m;
                x[m] = p[i-1].a;
                y[m] = p[i-1].b - mn;
            }
            ny[m+1] = p[i].b;
        }
    } 
    int l = 0, r = 500000, res = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid - 1, res = mid;
        else l = mid + 1;
    } 
    outn(res);
    check(res);
    re(i, lx) printf("B");
    re(i, ly) printf("N");
} 
```


---

## 作者：do_while_true (赞：3)

orz qyc

两个串相似实际上是两个字符串 'N' 和 'B' 的数量一致。

设 $s_i$ 有 $x_i$ 个 'N'，$y_i$ 个 'B'，$t$ 有 $x$ 个 'N'，$y$ 个 'B'。

分类讨论一下 $dist(s,t)$ 在 $x,x_i$ 以及 $y,y_i$ 大小关系不同的四种情况下的取值。

发现四种情况分别为：

$x-y-x_i+y_i,-(x-y)+x_i-y_i,\max(x_i-x,y_i-y),\max(x-x_i,y-y_i)$

对出现的六个式子求 $\max$ 恰好为答案，具体为何同样可以分类讨论四种情况。

二分答案转判定，就变成要求 $\max$ 里面六个值都 $\geq mid$。

发现实际上是对 $x,y,x-y$ 的取值范围作出限制。

后面就很简单了，算出各自的取值范围，然后看前两项不等式的差出来的范围是否和后一项的范围有交即可，构造方案枚举个 $x$ 随便怎么构造都可。

其实分类讨论有很多细节，但是这里仅给出主要思路不商讨细节部分。

```cpp
//Code by do_while_true
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Abs(T x) { return x < 0 ? -x : x; }
template <typename T> T chkmax(T &x, T y) { return x = x > y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 300010;
const int INF = 100000000;
int n, a[N], b[N];
//a:N  b:B
char ch[N];
bool check(int x) {
	int l1, r1, l2, r2, l3, r3;
	l1 = -INF, r1 = INF; l2 = 0, r2 = INF; l3 = 0; r3 = INF;
	for(int i = 1; i <= n; ++i) {
		l1 = Max(l1, a[i]-b[i]-x);
		r1 = Min(r1, a[i]-b[i]+x);
		l2 = Max(l2, a[i]-x);
		r2 = Min(r2, a[i]+x);
		l3 = Max(l3, b[i]-x);
		r3 = Min(r3, b[i]+x);
	}
	if(l2 < 0 || l3 < 0) return 0;
	if(l1 > r1 || l2 > r2 || l3 > r3) return 0;
	int l4 = l2 - r3, r4 = r2 - l3;
	return r1 >= l4 && l1 <= r4;
}
signed main() { //freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
	read(n);
	if(n == 1) {
		scanf("%s", ch+1);
		puts("0");
		printf("%s\n", ch+1);
		return 0;
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%s", ch+1);
		int len = std::strlen(ch+1);
		for(int j = 1; j <= len; ++j)
			if(ch[j] == 'N') ++a[i];
			else ++b[i];
	}
	int l = 0, r = INF, mid, ans = 0;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid-1;
		else l = mid+1;
	}
	printf("%d\n", ans);
	int l1, r1, l2, r2, l3, r3;
	l1 = -INF, r1 = INF; l2 = 0, r2 = INF; l3 = 0; r3 = INF;
	for(int i = 1; i <= n; ++i) {
		l1 = Max(l1, a[i]-b[i]-ans);
		r1 = Min(r1, a[i]-b[i]+ans);
		l2 = Max(l2, a[i]-ans);
		r2 = Min(r2, a[i]+ans);
		l3 = Max(l3, b[i]-ans);
		r3 = Min(r3, b[i]+ans);
	}
	int l4 = l2 - r3, r4 = r2 - l3;
	l = Max(l1, l4); r = Min(r1, r4);
	for(int i = l2; i <= r2; ++i) {
		int _l = i - r3, _r = i - l3;
		if(Max(_l, l) <= Min(r, _r)) {
			int p = Max(_l, l);
			if(i || (i-p)) {
				for(int j = 1; j <= i-p; ++j) printf("B");
				for(int j = 1; j <= i; ++j) printf("N");
				return 0;
			}
			else {
				p = Min(r, _r);
				if(i || (i-p)) {
					for(int j = 1; j <= i-p; ++j) printf("B");
					for(int j = 1; j <= i; ++j) printf("N");
					return 0;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：Zhddd_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1394C)

前置知识：模拟退火（Simulate Anneal）。

设给定的串为 $s$，答案串为 $t$，$s$ 串中 $\texttt{N}$ 的个数为 $s_{\texttt{N}}$，$\texttt{B}$ 的个数为 $s_{\texttt{B}}$，$t$ 串同理。那么观察一下题目，可发现一些性质：

1. 每个串各个字母的排列顺序并不影响答案和操作方案。所以每个串可以用两种字母出现次数来代表。

2. 若 $s$ 串的两种字母都比 $t$ 多，那么必然可以通过 $\max(s_{\texttt{N}}-t_{\texttt{N}},s_{\texttt{B}}-t_{\texttt{B}})$ 步让它们相似。即使用操作 $2$ 直到 $s$ 只有一种字母比 $t$ 多，该种字母再用操作 $1$ 消掉。两种字母都比 $t$ 少的情况同理。

3. 若 $s$ 串的一种字母比 $t$ 多（不妨设是 $\texttt{N}$），另一种比 $t$ 少，那么必然可以通过 $s_{\texttt{N}}-t_{\texttt{N}}+t_{\texttt{B}}-s_{\texttt{B}}$ 步让它们相似。即使用操作 $1$ 和 $3$。

综上所述，只需要预处理每个 $s$ 中两种字母出现次数，枚举 $t$ 中两种字母出现次数，然后 $O(n)$ 查询答案就行了。

这样可能有 $25\times10^{10}$ 种情况，考虑模拟退火。

细节见代码实现。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <string>
using namespace std;
typedef pair<int, int> PII;
int n, x, y, cnt[300005][2], cnt1[300005][2], top, ans = 2147483647, ax, ay;
// ans, ax, ay 分别表示目前的最优解，最优解 B 的数量和 N 的数量。
string a;
set<PII> mp;
mt19937 gen(time(NULL));
int query(int x, int y)
{
    int ans = 0;
    for (int i = 1; i <= top; ++i)
        if ((cnt1[i][0] < x) != (cnt1[i][1] < y))
            ans = max(ans, abs(cnt1[i][0] - x) + abs(cnt1[i][1] - y));
        else
            ans = max(ans, max(abs(cnt1[i][0] - x), abs(cnt1[i][1] - y)));
    return ans;
}
double rd(double l, double r) // 随机。
{
    uniform_real_distribution<> dis(l, r);
    return dis(gen);
}
void simulate_anneal()
{
    double T = 5e5, k = 0.999;
    int last = 0, now, nx, ny, d;
    x = 0, y = 0;
    while (T > 1e-6) {
        nx = x + rd(-5e5, 5e5) * T;
        ny = y + rd(-5e5, 5e5) * T;
        nx = max(nx, 0), ny = max(ny, 0);
        now = query(nx, ny);
        d = now - last;
        if (now < ans)
            ans = now, ax = nx, ay = ny;
        if (d < 0)
            last = now, x = nx, y = ny;
        else if (rand() < exp(-1.0 * d / T) * RAND_MAX)
            last = now, x = nx, y = ny;
        T *= k;
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a;
        for (int j = 0; j < int(a.size()); j++)
            if (a[j] == 'N')
                cnt[i][0]++;
            else
                cnt[i][1]++;
        mp.insert((PII) { cnt[i][0], cnt[i][1] });
    }
    for (auto i : mp) { // set 去重。
        cnt1[++top][0] = i.first;
        cnt1[top][1] = i.second;
    }
    simulate_anneal();
    // 此题甚至不用卡时，做一次就能过。
    if (ax == 0 && ay == 0) {
        cout << ans << "\nBN"; // 如果退火得到了空串，就要特判。
    } else {
        cout << ans << '\n';
        for (int i = 1; i <= ay; i++)
            cout << 'B';
        for (int i = 1; i <= ax; i++)
            cout << 'N';
    }
    return 0;
}
```

---

## 作者：_abcd_ (赞：1)

## [[CF1394C] Boboniu and String](https://codeforces.com/problemset/problem/1394/C)

为什么题解都带 $ \log $ 啊，是否有点极端了。

为了方便起见，下文将 $ \rm BN $ 串替换为 $ 01 $ 串。注意到“相似的”的判定相当于 $ 0 $ 和 $ 1 $ 的个数都相等。并且，若设 $ 0 $ 的个数为 $ c_0 $，$ 1 $ 的个数为 $ c_1 $，每次操作都可以将 $ c_0 $ 或 $ c_1 $ 加一或减一，或者将 $ c_0 $ 和 $ c_1 $ 同时加一或减一。

那么将 $ ( c_0, c_1 ) $ 变成 $ ( x, y ) $ 的步数显然是：若 $ ( c_0 - x ) ( c_1 - y ) \ge 0 $，则答案为 $ \max( | c_0 - x |, | c_1 - y | ) $，否则答案为 $ | c_0 - x | + | c_1 - y | $。手玩以下就能发现答案等同于 $ \max( c_0 - x, x - c_0, c_1 - y, y - c_1, c_0 - x + y - c_1, x - c_0 + c_1 - y ) $。

考虑设 $ x_1, x_2, y_1, y_2, s_1, s_2 $ 分别表示 $ c_0, c_1, c_0 - c_1 $ 的最小值和最大值，那么答案就可以表示成 $ \max( x - x_1, x_2 - x, y - l, r - y ) $，其中 $ l = \min( y_1, x - s_2 ), r = \max( y_2, x - s_1 ) $。显然当 $ y = \frac{l+r}{2} $ 时最优。直接枚举 $ x $ 并计算即可。复杂度为 $ O(n) $。

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define all(a) a.begin(),a.end()
#define fls() fflush(stdout)
#define maxn 500005
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
void gx(int &x,int y)
{
    if(y>x)
        x=y;
}
void gn(int &x,int y)
{
    if(y<x)
        x=y;
}
int n;
char a[maxn];
signed main()
{
    n=re();
    int x1=1e9,x2=0,y1=1e9,y2=0,s1=1e9,s2=-1e9;
    while(n--)
    {
        scanf("%s",a+1);
        int m=strlen(a+1);
        int c1=0,c2=0;
        for(int i=1;i<=m;i++)
        {
            if(a[i]=='B')
                c1++;
            else
                c2++;
        }
        gn(x1,c1),gx(x2,c1);
        gn(y1,c2),gx(y2,c2);
        gn(s1,c1-c2),gx(s2,c1-c2);
    }
    int ans=1e9,x,y;
    for(int i=x1;i<=x2;i++)
    {
        int l=min(y1,i-s2),r=max(y2,i-s1);
        int j=l+r>>1;
        int t=max({i-x1,x2-i,j-l,r-j});
        if(t<=ans)
        {
            ans=t;
            x=i,y=j;
        }
    }
    printf("%d\n",ans);
    while(x--)
        putchar('B');
    while(y--)
        putchar('N');
    pn;
    return 0;
}
```

---

## 作者：紊莫 (赞：0)

洛谷最劣解，$O(n \log^2 n)$，但是题解区没有。

首先题目的要求实际上就是 $B$ 和 $N$ 的个数分别相等，那么已知两者个数的时候可以直接分讨然后计算，时间复杂度 $O(n)$。

考虑三分套三分，第一次三分 $B$ 的个数，第二次三分 $N$ 的个数。

感性理解一下，我们最后计算的式子都是类似 $|x - a|$ 的形式，是单峰的，所以可以三分，严谨证明的话我也不会，有大佬会的话可以私信联系我。

代码很好写，但是常数比较大。

[My submission.](https://codeforces.com/contest/1394/submission/264844098)

---

## 作者：jifbt (赞：0)

目前本题题解区的做法都是 $O(n \log n)$ 的。事实上，本题有 $O(n)$ 的做法（~~虽然意义可能不大~~）。

如果您不会 $O(n\log n)$ 的做法，建议先看看其他题解。

---

设二分时的 `mid` 为 $k$，我们有六个不等式
$$\begin{cases}
x \ge \max x_i-k\\
x \le \min x_i+k \\
y \ge \max y_i-k\\
y \le \min y_i+k\\
x-y \ge \max x_i-y_i-k\\
x-y \le \min x_i-y_i+k
\end{cases}$$
其中 $\max$ 和 $\min$ 都取遍 $1 \sim n$ 中的所有 $i$。（参考了 [这篇题解](https://www.luogu.com.cn/blog/WYXkk/solution-cf1394c)。）

我们可以选择每次暴力计算不等式右侧的值（这正是其他题解的做法）。更快的做法是，预处理出 $x_i$、$y_i$、$x_i-y_i$ 的最小值和最大值，这样每次只需 $O(1)$ 即可计算出来。总时间复杂度 $O(n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5, V = 1e6 + 5;
int n, ax, ay;
int X[2], Y[2], D[2];

bool judge(int x, int y, int k) {
    return x >= 0 && y >= 0 && (x || y) && X[0] <= x && X[1] >= x &&
           Y[0] <= y && Y[1] >= y && D[0] <= x - y && D[1] >= x - y;
}

bool calc(int k) {
    int x, y;
    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            if (judge(x = X[i], y = Y[i], k)) return ax = x, ay = y, true;
            if (judge(x = X[i], y = X[i] - D[i], k))
                return ax = x, ay = y, true;
            if (judge(x = Y[i] + D[i], y = Y[i], k))
                return ax = x, ay = y, true;
        }
    }
    return false;
}

int main() {
    X[0] = Y[0] = D[0] = -V;
    X[1] = Y[1] = D[1] = V;
    scanf("%d", &n);
    getchar();
    for (int i = 1; i <= n; ++i) {
        int a = 0, b = 0;
        char ch;
        while (true) {
            ch = getchar();
            if (ch == 'B')
                ++a;
            else if (ch == 'N')
                ++b;
            else
                break;
        }
        X[0] = max(X[0], a), Y[0] = max(Y[0], b), D[0] = max(D[0], a - b);
        X[1] = min(X[1], a), Y[1] = min(Y[1], b), D[1] = min(D[1], a - b);
    }
    int l = -1, r = V;
    while (r - l > 1) {
        int k = (l + r) >> 1;
        X[0] -= k, Y[0] -= k, D[0] -= k;
        X[1] += k, Y[1] += k, D[1] += k;
        calc(k) ? r = k : l = k;
        X[0] += k, Y[0] += k, D[0] += k;
        X[1] -= k, Y[1] -= k, D[1] -= k;
    }
    printf("%d\n", r);
    for (int i = 1; i <= ax; ++i)
        putchar('B');
    for (int i = 1; i <= ay; ++i)
        putchar('N');
}
```

轻松拿下最优解。

---

## 作者：EXODUS (赞：0)

# Part 1：前言

完全不是字符串的字符串题/cf。

# Part 2：正文

注意到相似的定义本质上是字符串中 $\texttt{B}$ 和 $\texttt{N}$ 的数量相同。而操作也是围绕着 $\texttt{B}$ 和 $\texttt{N}$ 的数量进行的，所以每个字符串实质上等价于一个二元组 $(b,n)$，分别表示字符串中 $\texttt{B}$ 的数量和 $\texttt{N}$ 的数量。考虑此时操作的本质是什么，相当于是让 $(b,n)$ 转移到 $(b±1,n),(b,n±1),(b±1,n±1)$。

那么此时进一步考虑计算答案。看到最小化最大值想到套路二分。考虑每个二元组对答案的限制是什么。假设当前二分到一个答案 $x$，前两种转移是容易处理的，也就是说对于一个合法答案 $(b_0,n_0)$，其有 $b_0\in[\max\limits_{i=1}^n (b_i-l),\min\limits_{i=1}^n (b_i+l)],n\in[\max\limits_{i=1}^n (n_i-l),\min\limits_{i=1}^n (n_i+l)]$，但加上第三种限制可能有点难以直观理解，我们不妨将其看为一个三元组 $(b,n,b-n)$，那么此时对第三维的限制就变成了 $b_0-n_0\in[\max\limits_{i=1}^n (b_i-n_i-l),\min\limits_{i=1}^n (b_i-n_i+l)]$。也就是说我们得到了三个关于 $b$ 和 $n$ 的区间。判断这三个区间是否有交即可。

最后的问题是构造方案。根据上面的我们得出了一个区间，那么任取在区间中的两点即可，可能要同时注意一下第三维对答案的限制，具体细节实现可以见代码。


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


const int N=3e5+7;
int n,x[N],y[N];
string s[N];
pair<int,int>res;

bool check(int mid){
	int lx=0,rx=1e9,ly=0,ry=1e9,L=-1e9,R=1e9;
	auto chx=[&](int &X,int Y){X=X>Y?X:Y;};
	auto chn=[&](int &X,int Y){X=X<Y?X:Y;};
	for(int i=1;i<=n;i++)
		chx(lx,x[i]-mid),chx(ly,y[i]-mid),chx(L,x[i]-y[i]-mid),
		chn(rx,x[i]+mid),chn(ry,y[i]+mid),chn(R,x[i]-y[i]+mid);
	auto chk=[&](int l,int r){return l<=r;};
	if(!(chk(lx,rx)&&chk(ly,ry)&&chk(L,R)))return 0;
	// cout<<lx<<" "<<rx<<" "<<ly<<" "<<ry<<" "<<L<<" "<<R<<endl;
	if(!((lx-ry>R)||(rx-ly<L)))res=make_pair(min(ry+R,rx),min(min(ry+R,rx)-L,ry));
	return !((lx-ry>R)||(rx-ly<L));
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)
		for(int j=0;j<(int)s[i].length();j++)
			if(s[i][j]=='B')x[i]++;
			else y[i]++;
	int l=0,r=1e6,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans<<'\n';
	for(int i=1;i<=res.first;i++)cout<<'B';
	for(int i=1;i<=res.second;i++)cout<<'N';
	cout<<'\n';
	fflush(stdout);
	return 0;
}
```

---

## 作者：白鲟 (赞：0)

### 前言
有段时间没写题解了。

### 分析
注意到相似事实上指的是 $\texttt{N}$ 的个数与 $\texttt{B}$ 的个数分别相等，与字母顺序无关。

又注意到任意时刻只要序列中同时存在 $\texttt{N}$ 和 $\texttt{B}$，就可以同时删去一个 $\texttt{N}$ 与一个 $\texttt{B}$。于是操作事实上也与字母顺序无关。

于是可以把一个序列用二元组 $(x,y)$ 表示，其中 $x$ 为 $\texttt{N}$ 的个数，$y$ 为 $\texttt{B}$ 的个数。

单调性很明朗，考虑二分答案 $ans$。

考虑求出每个序列通过在答案范围的步数内可以生成的序列 $(x',y')$ 的集合，再求出所有序列生成集合的交集以判断和构造解。

对于每一维，偏移量不会超过 $ans$。同时由于两维每一步偏移方向不能相反，两维的差偏移量也不会超过 $ans$。可以发现条件是充要的，同时由于是线性规划的约束形式，通过几何表示可以直观理解。

因此将每一维的合法区间求交，差偏移量的合法区间求交，再判断在两维合法的情况下是否存在合法的差偏移量。若悉数满足，则根据条件构造合法方案。

### 代码
```cpp
#include<bits/stdc++.h>
#define loop(i,from,to) for(int i=(from);i<=(to);++i)
using namespace std;
const int maxn=5e5,inf=0x3f3f3f3f;
int n,len,l,r,ans,ans0,ans1,cnt[maxn+1][2];
char s[maxn+1];
bool check(int now){
	int lx=-inf,rx=inf,ly=-inf,ry=inf,lxy=-inf,rxy=inf;
	loop(i,1,n)
		lx=max(lx,cnt[i][0]-now),rx=min(rx,cnt[i][0]+now),ly=max(ly,cnt[i][1]-now),ry=min(ry,cnt[i][1]+now),
		lxy=max(lxy,cnt[i][0]-cnt[i][1]-now),rxy=min(rxy,cnt[i][0]-cnt[i][1]+now);
	if(rx<lx||ry<ly||rxy<lxy||min(rx-ly,rxy)<max(lx-ry,lxy))return false;
	ans0=min(ry+rxy,rx),ans1=min(ans0-lxy,ry);
	return true;
}
int main(){
	scanf("%d",&n),r=n;
	loop(i,1,n){
		scanf("%s",s+1),r+=len=strlen(s+1);
		loop(j,1,len)++cnt[i][s[j]=='B'];
	}
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
	loop(i,1,ans0)putchar('N');
	loop(i,1,ans1)putchar('B');
	return 0;
}
```

---

