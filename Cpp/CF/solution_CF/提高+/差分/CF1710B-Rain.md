# Rain

## 题目描述

You are the owner of a harvesting field which can be modeled as an infinite line, whose positions are identified by integers.

It will rain for the next $ n $ days. On the $ i $ -th day, the rain will be centered at position $ x_i $ and it will have intensity $ p_i $ . Due to these rains, some rainfall will accumulate; let $ a_j $ be the amount of rainfall accumulated at integer position $ j $ . Initially $ a_j $ is $ 0 $ , and it will increase by $ \max(0,p_i-|x_i-j|) $ after the $ i $ -th day's rain.

A flood will hit your field if, at any moment, there is a position $ j $ with accumulated rainfall $ a_j>m $ .

You can use a magical spell to erase exactly one day's rain, i.e., setting $ p_i=0 $ . For each $ i $ from $ 1 $ to $ n $ , check whether in case of erasing the $ i $ -th day's rain there is no flood.

## 说明/提示

In the first test case, if we do not use the spell, the accumulated rainfall distribution will be like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/40bd9aae46d3e796ba1ad418de0578aa41ab0c1c.png)If we erase the third day's rain, the flood is avoided and the accumulated rainfall distribution looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/d422db8867ffc7f0ea195742c50ffb3752e7d523.png)In the second test case, since initially the flood will not happen, we can erase any day's rain.

In the third test case, there is no way to avoid the flood.

## 样例 #1

### 输入

```
4
3 6
1 5
5 5
3 4
2 3
1 3
5 2
2 5
1 6
10 6
6 12
4 5
1 6
12 5
5 5
9 7
8 3```

### 输出

```
001
11
00
100110```

# 题解

## 作者：ethan_zhou (赞：50)

说一个代码简单的做法。~~本题解数形结合，容易理解。~~

## 题解

![](https://pic.imgdb.cn/item/62e13a21f54cd3f937715f80.jpg)

首先，题目所求就是上述不等式对哪个 $i$ 成立。

发现式中只有第 $2$ 项是随着 $i$ 而变化的。而第 $1$ 项虽然不变，但是较为复杂，与第 $2$ 项相减的结果不好快速计算，因此不妨将第 $2$ 项移项到右边。

![](https://pic.imgdb.cn/item/62e13ca0f54cd3f9378c5ba2.jpg)

是不是突然发现这下不等式两边都比较简单了？如果看不出来，我们不妨把式子左右的图叠在一起看：

![](https://pic.imgdb.cn/item/62e140c4f54cd3f937b1c1cb.jpg)

**下文中称 $(x_i,p_i+m)$ 点为蓝色山顶（图中标出）**

我们考虑右边能把左边盖住的条件：

- 对于左边高度小于等于 $m$ 的点，显然不用考虑
- 对于左边高度大于 $m$ 的某一点，蓝色山顶必须位于下图红色阴影区域内：

![](https://pic.imgdb.cn/item/62e1426ff54cd3f937bd9d1b.jpg)

显然，只要左边的所有极值点都满足上述条件，那么左边的所有点都满足上述条件。到了这里，做法就显而易见了。我们只需要枚举所有左侧的极值点，然后把他们的红色阴影区域求交，再判断某个 $i$ 对应的蓝色山顶是否在这个区域内即可。

至于维护红色阴影的交，可以把这个区域看成两个斜率分别为 $\pm1$ 的一次函数取 max，因此求交的时候只需要对应截距取 max 即可。

剩下的就是一些简单的技术问题，比如离散化，差分，不再赘述。

复杂度 $O(n\log n)$，瓶颈在离散化。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
using ll = long long;
void umx(ll &x, const ll &y) { x = max(x, y); }
const char nl = '\n';
const ll INF = 1e18;
const ll MXN = 1e6 + 5;

ll n, m;
map<ll, ll> delt;
ll x[MXN], p[MXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        delt.clear();
        cin >> n >> m;
        for (ll i = 1; i <= n; i++) {
            cin >> x[i] >> p[i];
            delt[x[i] - p[i] + 1]++;
            delt[x[i] + 1] -= 2;
            delt[x[i] + p[i] + 1]++;
        }
        ll b = 0, k = 0, lastx = -INF;
        ll b_1 = -INF, b1 = -INF;
        for (auto it : delt) {
            b += k * (it.fi - lastx);
            k += it.se;

            if (b > m) {
                umx(b1, b - it.fi + 1);
                umx(b_1, b + it.fi - 1);
            }

            lastx = it.fi;
        }
        for (ll i = 1; i <= n; i++) cout << ((p[i] + m - x[i] >= b1) && (p[i] + m + x[i] >= b_1));
        cout << nl;
    }
    return 0;
}
```

---

## 作者：enucai (赞：10)

## Analysis

容易发现：删去一次降水后降水量最高的位置在删去前一定是某次降水的中心。

于是考虑如何算出原始状态下每个降水中心位置的降水量。由于每次降水是在两个区间分别加公差为 $1$ 与 $-1$ 的等差数列，则每个位置加的值 加或减 她的位置是定值。于是用两个差分数组就可以 $O(n\log n)$ 求出每个降水中心的降水量（$\log n$ 用于二分查找），设其为数组 $a$。

对于一个原先降水量 $>m$ 的位置 $u$，若删去一个位置 $v$ 后她的降水量 $\le m$，则必然有 $a_u-(p_v-|x_v-x_u|)\le m$。将绝对值拆开：

$$
\begin{cases}
a_u-x_u\le p_v-x_v+m\\
a_u+x_u\le p_v+x_v+m
\end{cases}
$$

因此只需求出 $a_u-x_u$ 与 $a_u+x_u$ 得最大值分别为 $mx_1$，$mx_2$。只有满足 $p_i-x_i+m\ge mx_1\land p_i+x_i+m\ge mx_2$ 的 $i$ 才符合条件。

时间复杂度 $O(n\log n)$。

## Code

```cpp
#define int long long
int n,m,a[200010],b[200010],c[200010];
struct node{
	int x,p,id,ans;
	bool operator<(const node &pp)const{
		if(x!=pp.x) return x<pp.x;
		return p<pp.p;
	}
}op[200010];
bool cmp(node x,node y){
	return x.id<y.id;
}
void work(){
	cin>>n>>m;
	For(i,1,n) cin>>op[i].x>>op[i].p;
	For(i,1,n) op[i].id=i;
	sort(op+1,op+n+1);
	mem(b,0),mem(c,0);
	For(i,1,n){
		int tmp=lower_bound(op+1,op+n+1,(node){op[i].x-op[i].p,0,0})-op;
		b[tmp]+=op[i].p-op[i].x,b[i+1]-=op[i].p-op[i].x;
		c[tmp]++,c[i+1]--;
	}
	For(i,1,n){
		int tmp=upper_bound(op+1,op+n+1,(node){op[i].x+op[i].p,0,0})-op-1;
		b[i+1]+=op[i].p+op[i].x,b[tmp+1]-=op[i].p+op[i].x;
		c[i+1]--,c[tmp+1]++;
	}
	For(i,1,n) b[i]+=b[i-1],c[i]+=c[i-1];
	For(i,1,n) a[i]=b[i]+c[i]*op[i].x;
	int mx1=-1e16,mx2=-1e16;
	For(i,1,n) if(a[i]>m){
		mx1=max(mx1,a[i]-op[i].x);
		mx2=max(mx2,a[i]+op[i].x);
	}
	For(i,1,n){
		if(op[i].p-op[i].x+m>=mx1&&op[i].p+op[i].x+m>=mx2) op[i].ans=1;
		else op[i].ans=0;
	}
	sort(op+1,op+n+1,cmp);
	For(i,1,n) cout<<op[i].ans; cout<<"\n";
}
signed main(){IOS;
	int T; cin>>T;
	while(T--) work();
}
```

---

## 作者：览遍千秋 (赞：2)

### 题意简述

给出若干个雨中心 $x_i$ 与降雨强度 $p_i$。

对于每场雨 $x,p$，对位置 $i$ 积水的贡献为 $\max \{0, |x-i|+p \}$

任意一个位置积水大于 $m$ 就会发洪水，问抹去一场降雨，是否不会发洪水。

---

### 问题分析

首先，发洪水的地方一定是某个降雨中心。

本质上，每个位置的积水深度是若干个绝对值函数 $f(x)=|x-x_i|$ 叠加的结果。容易知道类似的函数在零点取到极值。

可以通过离散化，将值域缩小到 $n$。

维护两个差分数组：斜率和截距，可以算出每个位置的积水量。

如果一个降水中心 $i$，原来的积水量为 $R_i>m$，去掉降雨 $k$ 后积水量不超过 $m$，则有 $R_i - |x_j-x_i| - p_j \le m$。

这里不处理 $\max$ 的原因是：若题目中 $\max$ 的式子在这里取零，即有 $R_i \le m$，与 $R_i > m$ 矛盾，故题目中的式子在这里 $>0$。

拆开绝对值有：

$$\begin{cases} R_i - x_j + x_i - p_j \le m \\ R_i - x_i + x_j - p_j \le m \end{cases}$$

移项，有

$$\begin{cases} R_i + x_i \le x_j + p_j +m \\ R_i - x_i \le -x_j + p_j + m \end{cases}$$

维护 $R_i+x_i$ 和 $R_i-x_i$ 的最大值即可。

一个注意点：多测清空时，差分数组要清到 $n+1$ 的位置。

---

### Codes

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
typedef long long LL;

template < typename Tp >
void read(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

const int maxn = 200000 + 7;

int T, n, m;
struct rain {
	int x, p, id;
	bool ans;
}a[maxn];

void Init(void) {
	read(T);
}

bool cmp(rain a, rain b) {
	return a.x == b.x ? a.p < b.p : a.x < b.x;
}

bool comp(rain a, rain b) {
	return a.id < b.id;
}

int sk[maxn], sb[maxn], r[maxn];

int lfind(rain t) {
	int l = 1, r = n, mid, res = n;
	while(l <= r) {
		mid = ((l + r) >> 1);
		if(a[mid].x >= t.x - t.p) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

int rfind(rain t) {
	int l = 1, r = n, mid, res = 1;
	while(l <= r) {
		mid = ((l + r) >> 1);
		if(a[mid].x <= t.x + t.p) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

void Work(void) {
	while(T--) {
		for(int i = 1; i <= n + 1; i++) {
			sb[i] = sk[i] = r[i] = 0;
//			a[i].x = a[i].p = a[i].id = a[i].ans = 0;
		}
		read(n); read(m);
		for(int i = 1; i <= n; i++) {
			read(a[i].x); read(a[i].p);
			a[i].id = i;
		}
		sort(a + 1, a + n + 1, cmp);
		for(int i = 1; i <= n; i++) {
			int lb = lfind(a[i]), rb = rfind(a[i]);
			sk[lb]++, sk[i + 1] -= 2, sk[rb + 1]++;
			sb[lb] += a[i].p - a[i].x;
			sb[i + 1] -= a[i].p - a[i].x;
			sb[i + 1] += a[i].p + a[i].x;
			sb[rb + 1] -= a[i].p + a[i].x;
		}
		for(int i = 1; i <= n; i++) {
			sk[i] += sk[i - 1];
			sb[i] += sb[i - 1];
			r[i] = sb[i] + sk[i] * a[i].x;
//			cout << r[i] << " ";
		}
		int mx1 = -0x3f3f3f3f3f3f3f3fll, mx2 = -0x3f3f3f3f3f3f3f3fll;
		for(int i = 1; i <= n; i++) {
			if(r[i] > m) mx1 = max(mx1, r[i] - a[i].x);
			if(r[i] > m) mx2 = max(mx2, r[i] + a[i].x);
		}
		for(int i = 1; i <= n; i++) {
			if(a[i].p - a[i].x + m >= mx1 && a[i].x + a[i].p + m >= mx2) a[i].ans = true;
			else a[i].ans = false;
		}
		sort(a + 1, a + n + 1, comp);
		for(int i = 1; i <= n; i++) printf("%d", a[i].ans);
		puts("");
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}
```

---

## 作者：Doubeecat (赞：2)

> 有 $n$ 天在下雨，每一天，雨会在第 $x_i$ 个地方降落，降雨量为 $p_i$。降雨量会累加，对于一个地方 $j$，它的总降雨量为 $a_j$，每一次降雨其能接收到的降雨量为 $\max(0,p_i-|x_i-j|)$ 。
>
> 一个地方为**发大水**的定义为：在任何时间段有 $a_j > m$ .
>
> 你需要求出：对于每一天，独立地将该天的降雨量撤销之后，这一天是否还有地方是发大水的。
>
> $n \leq 2\times 10^5,p_i \leq 10^9,m \leq 10^9$

以下称第 $i$ 天降雨的位置 $x_i$ 为关键点 $i$。

首先观察到一个性质：我们只需要对每个降雨的 $x_i$ 讨论是否发大水。

> 简略证明：
>
> 我们可以通过讨论相邻的两个关键点 $x_i,x_j (x_i < x_j)$ ，降雨量分别为 $p_i,p_j$ ，假设他们中间隔着一个点 $pos$.
>
> 可以得出，
> $$
> a_{x_i} = p_i + p_j - (x_j - x_i), \\
> a_{pos} = p_i + p_j - (pos - x_i + x_j - pos) = p_i + p_j - (x_j - x_i) = a_{x_i},\\
> a_{y_i} = p_j + p_i - (x_j - x_i)
> $$
> 这个实际上证明了，对于两个关键点之间的所有点受到的降雨量都是相同的。
>
> 故我们只需要讨论每个关键点即可。

接下来，每次降雨实际上可以看成加一个起点为 $x_i - p_i$，首项为 $0$，公差为 $1$，项数为 $p_i - x_i$ 的 等差数列，以及一个起点为 $x_i + 1$ ，首项为 $p_i$，公差为 $-1$，项数同样为 $p_i - x_i$ 的等差数列。

接下来我们发现，去掉一个降雨的地方其实是很复杂的，如果要强行上线段树的话会相对复杂，这里我们不妨转化一下。

我们考虑对于一个关键点 $x$，如果去掉第 $i$ 天的降雨可以让其变为不发大水的当且仅当 $p_i-|x_i-j| \geq a_j-m$，这个的证明直接展开即可。

接下来我们考虑把上面的几个东西综合一下，做一个扫描线。我们按照上面所说把每个降雨过程拆成两条线段（其实就像官方题解，是一个 $k = \pm 1$ 的斜线），再把每个关键点排序，考虑每次把关键点之前的直线都计算对关键点的影响。这是可以通过上面的计算式做到的。（这段不是很理解可以看代码）

这样我们就计算出了 $a_i$，最后判断一下即可。

时间复杂度为 $\mathcal{O}(n\log n)$

```cpp
//Every night that summer just to seal my fate
//And I scream, "For whatever it's worth
//I love you, ain't that the worst thing you ever heard?"
#pragma GCC optimize(2)
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define ll long long
#define int long long

char buf[1 << 20], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)?EOF: *p1++)
template <typename T> inline void read(T &t) {
	int v = getchar();T f = 1;t = 0;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {t = t * 10 + v - 48;v = getchar();}
	t *= f;
}
template <typename T,typename... Args> inline void read(T &t,Args&... args) {
	read(t);read(args...);
}

const int N = 2e5 + 10;

struct node {
    int id,pos,cnt;
    friend inline bool operator < (const node &a,const node &b) {
        return a.pos < b.pos;
    };
}q[N];

struct que {
    int pos,cnt,opt,flag;
    friend inline bool operator < (const que &a,const que &b) {
        return a.pos < b.pos;
    };
}l[N<<3];

int n,m,x[N],pos[N],pre[N],suf[N],tot = 0;
unordered_map <int,int> ans;

void add(int i) {
    l[++tot] = (que){x[i] - pos[i],pos[i] - x[i],1,1};
    //上升端的一段，位置可以延伸到x[i] - pos[i]，题目中绝对值拆一部分是pos[i] - x[i]
    l[++tot] = (que){x[i] + 1,x[i] + pos[i],0,1};
    l[++tot] = (que){x[i] + 1,- x[i] + pos[i],1,0};
    //转变一下上升下降 两个最终会相加得到2*x[i]
    l[++tot] = (que){x[i] + pos[i] + 1,x[i] + pos[i],0,0};
    //下降
}

void solve() {
    read(n,m);ans.clear();tot = 0;
    for (int i = 1;i <= n;++i) {
        read(x[i],pos[i]);
        q[i] = (node){i,x[i],0};
        add(i);
    }
    sort(q+1,q+1+n);sort(l+1,l+1+tot);
    int now = 1;
    int c1 = 0,c2 = 0,s1 = 0,s2 = 0;
    for (int i = 1;i <= n;++i) {
        while (now <= tot && l[now].pos <= q[i].pos) {
            if (l[now].opt) {
                if (l[now].flag) ++c1,s1 += l[now].cnt;
                else --c1,s1 -= l[now].cnt;
            } else {
                if (l[now].flag) ++c2,s2 += l[now].cnt;
                else --c2,s2 -= l[now].cnt;
            }
            ++now;
        }
        q[i].cnt = q[i].pos;
        q[i].cnt *= (c1 - c2);
        q[i].cnt += s1 + s2;
    }
    //q[i].cnt 求出最大覆盖
    for (int i = 1;i <= n;++i) {
        if (q[i].cnt > m) {
            suf[i] = (q[i].cnt - m) + q[i].pos;
            pre[i] = (q[i].cnt - m) - q[i].pos;
        } else {
            pre[i] = suf[i] = -1e18;
        }
    }
            pre[0] = suf[n+1] = -1e18;
    for (int i = 1;i <= n;++i) pre[i] = max(pre[i],pre[i-1]);
    for (int i = n;i >= 1;--i) suf[i] = max(suf[i],suf[i+1]);
    for (int i = 1;i <= n;++i) {
        ans[q[i].pos] = max(ans[q[i].pos],
                max(suf[i] - q[i].pos,pre[i] + q[i].pos));
    }
    for (int i = 1;i <= n;++i) {
        if (pos[i] >= ans[x[i]]) putchar('1');
        else putchar('0');
    }
    puts("");
}

signed main() {
    int T;read(T);
    while (T--) solve();
	return 0;
}

```



---

## 作者：Engulf (赞：1)

记 $a_{i}$ 表示数轴上的 $i$ 这个点的总降雨量。

对于每一天 $i$，只要数轴上存在一个点 $t$ 使得去掉第 $i$ 天后仍然满足 $a_t > m$，那么第 $i$ 天的答案就是 $0$，否则就是 $1$。也就是说只需要维护降雨量的最大值。

现在考虑怎么在这宽广的数轴上找到降雨量最大值。

最大值在极大值中产生。考虑找出所有极大值点。

> 猜想：极大值点一定只在某些降雨中心 $x_i$，非降雨中心一定不是极大值点。

直觉告诉我们猜想是正确的。[证明](https://www.luogu.com.cn/paste/hjo6p407)。

现在只需维护 $n$ 个 $x_i$ 即可，先离散化一下。

---

考虑怎么维护 $a$。

先将所有降雨中心按 $x$ 从小到大排序。

对于一场雨 $(x_i, p_i)$，考虑它能影响哪些降雨中心。
- 设 $l$ 为最小的使得 $a_l \ge x_i - p_i + 1$ 的 $l$；
- 设 $l$ 为最大的使得 $a_r \le x_i + p_i - 1$ 的 $r$；

已经排序，二分即可找到。$[l, r]$ 中的降雨中心将会被影响。

- 对于任意的 $j \in [l, i]$，$a_j$ 的增量为 $x_j + p_i - x_i$；
- 对于任意的 $j \in [i + 1, r]$，$a_j$ 的增量为 $-x_j + p_i + x_i$；

发现每个 $j$ 最终都可以用一次函数 $a_j = k_ja_j + b_j$ 表示。差分维护斜率和截距即可。

---

枚举去掉第 $i$ 场雨。

如果对于任意降雨中心 $j$ 满足 $a_j > m$，都满足 $a_j - (p_i - |x_i - x_j|) \le m$，这场雨的答案就是 $1$，否则是 $0$。

拆掉绝对值，再整理可得两条式子：
- $a_j - x_j \le m + p_i - x_i$
- $a_j + x_j \le m + p_i + x_i$

右边只与 $i$ 相关，左边只与 $j$ 相关且都算出来了，只需维护全局 $a_j - x_j$ 和 $a_j + x_j$ 的最大值即可。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int n, m;

struct Drop {
    int x, p, id;
} a[N];

ll k[N], b[N];

int getLeft(int i) {
    int l = 1, r = n, res = n;
    while (l <= r) {
        int mid = l + r >> 1;
        if (a[mid].x >= a[i].x - a[i].p + 1) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    return res;
}
int getRight(int i) {
    int l = 1, r = n, res = 1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (a[mid].x <= a[i].x + a[i].p - 1) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n >> m;

        for (int i = 1; i <= n; i++) {
            cin >> a[i].x >> a[i].p;
            a[i].id = i;
        }

        sort(a + 1, a + 1 + n, [&](const Drop &x, const Drop &y) {return x.x < y.x;});

        for (int i = 1; i <= n; i++) {
            int l = getLeft(i), r = getRight(i);
            k[l]++, k[i + 1]--;
            k[i + 1]--, k[r + 1]++;

            b[l] += a[i].p - a[i].x, b[i + 1] -= a[i].p - a[i].x;
            b[i + 1] += a[i].p + a[i].x, b[r + 1] -= a[i].p + a[i].x;
        }

        ll mx1 = -1e18, mx2 = -1e18;
        for (int i = 1; i <= n; i++) {
            k[i] += k[i - 1];
            b[i] += b[i - 1];
            ll c = k[i] * a[i].x + b[i];
            if (c > m) {
                mx1 = max(mx1, c - a[i].x);
                mx2 = max(mx2, c + a[i].x);
            }
        }

        sort(a + 1, a + 1 + n, [&](const Drop &x, const Drop &y) {return x.id < y.id;});

        for (int i = 1; i <= n; i++)
            cout << (1ll * m + a[i].p - a[i].x >= mx1 && 1ll * m + a[i].p + a[i].x >= mx2);
        cout << "\n";

        for (int i = 1; i <= n + 1; i++)
            k[i] = b[i] = 0;
    }
    return 0;
}
```

---

## 作者：y0y68 (赞：1)

数学题。

首先如果坐标的数量是一个可以线性扫的数量级，考虑怎么做。

自然想到先把每个位置最终的汇集的雨给算出来，计算方式可以是两次差分或线段树。将某一天不下雨视为在这天的对应位置上做一次与下雨相反的删雨操作。对于每个位置，处理出要使没有洪水泛滥，这个位置做删雨操作的雨的大小至少是多少。

设这个位置为 $p$，雨的大小为 $x$，那么对于每个位置 $p'$，设这个位置上的雨比 $m$ 大 $t'$，也就是要给这个位置至少删 $t'$。若 $t'<0$ 直接不考虑这个位置。

于是我们列出了一个不等式：$x-|p-p'| \ge t'$

当 $p' \ge p$ 时，$x+p \ge t'+p'$；当 $p'<p$ 时，$x-p \ge t'-p'$。

可以维护出 $t'+p'$ 的前缀最大值和 $t'-p'$ 的后缀最大值，判断一下就好了。

但是位置的数量非常大，不能每个都维护，所以只能维护有代表性的点。

样例解释画的折线图很好地帮我们解决了这个问题。

考虑将最终每个位置及其雨的大小画在坐标系里，描点，连线，显然会得到一个分段函数。那么这个分段函数的转折点一定是所有的 $p-x,p,p+x$（ $p$ 为位置，$x$ 为大小）。感性理解一下只要这些转折点满足上面列的不等式，那么其他点一定满足。

转折点的横坐标排排序去重就可以了，算纵坐标可以维护每一段的斜率。

显然每一场雨都对应着自己的分段函数，这些分段函数是倒 V 形，前半段斜率 $1$，后半段斜率 $-1$，那么总的分段函数的每段斜率就很好算了。不理解可以看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nsfxyop4.png)

显然离散化差分即可。

我们知道第一个转折点纵坐标为 $0$，那么根据斜率和横坐标差就可以依次算出每个转折点坐标。

然后就没了，时间复杂度 $O(n\log n)$，十分合理。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int T,n,m,num[N],d[N];
ll t[N],f[N],g[N];
struct Node{
	int l,r,opt;
}a[N];
struct Query{
	int p,x,id;
}q[N];
int main(){
	for(cin>>T;T;T--){
		cin>>n>>m;
		int cnt=0,_n=0;
		for(int i=1,p,x;i<=n;i++){
			scanf("%d%d",&p,&x);
			a[++_n]=Node{p-x,p,1};
			a[++_n]=Node{p,p+x,-1};//拆成两段差分
			num[++cnt]=p-x,num[++cnt]=p,num[++cnt]=p+x;
			q[i]=Query{p,x,0};
		}
		sort(num+1,num+cnt+1);
		cnt=unique(num+1,num+cnt+1)-num-1;
		for(int i=1;i<=cnt;i++)
			d[i]=0;
		for(int i=1;i<=_n;i++){
			a[i].l=lower_bound(num+1,num+cnt+1,a[i].l)-num;
			a[i].r=lower_bound(num+1,num+cnt+1,a[i].r)-num;
			d[a[i].l]+=a[i].opt,d[a[i].r]-=a[i].opt;//注意这里是差分每一段，所以是a[i].r不是a[i].r+1
		}
		for(int i=1;i<=n;i++)
			q[i].id=lower_bound(num+1,num+cnt+1,q[i].p)-num;
		for(int i=1;i<cnt;i++)
			d[i]+=d[i-1];
		for(int i=2;i<=cnt;i++)
			t[i]=t[i-1]+1ll*(num[i]-num[i-1])*d[i-1];
		for(int i=1;i<=cnt;i++)
			t[i]=max(0ll,t[i]-m);
		f[0]=-1e18;
		for(int i=1;i<=cnt;i++){
			if(t[i]>0)f[i]=max(f[i-1],t[i]-num[i]);
			else f[i]=f[i-1];
		}
		g[cnt+1]=-1e18;
		for(int i=cnt;i>=1;i--){
			if(t[i]>0)g[i]=max(g[i+1],t[i]+num[i]);
			else g[i]=g[i+1];
		}
		for(int i=1;i<=n;i++)
			putchar((q[i].x-q[i].p>=f[q[i].id]&&q[i].x+q[i].p>=g[q[i].id])?'1':'0');
		puts("");
	}
	return 0;
}
```

---

## 作者：Jeefy (赞：0)

考虑整个图长什么样子，发现峰值（很多个）一定是某个 $x_i$ 上。

![](https://gitlab.com/jeefies/image-repo/uploads/66a10ea4e256a2229b05be5893cc5655/202310241913318.png)

于是求出每一个 $x_i$ 对应的降雨 $h_i$，这可以通过二分和差分很容易的求出（考虑每一次增加的是一个一次函数，这可以通过 $k, b$ 简单的维护）

于是考虑对于删除一个后 $m$ 的限制。

如果 $h_i \le m$，自然不需要关注，删除一个 $k$ 之后 $h_i \to h_i - \max(0, p_k - |x_k - x_i|)$。

我们需要 $h_i - \max(0, p_k - |x_k - x_i|) \le m$ 也就是 $h - (p_k - |x_k - x_i|) \le m$，考虑原本 $h_i > m$，如果后者不满足，那么必定不满足。

于是就是 $h_i - p_k \le m + |x_k - x_i|$，考虑绝对值又是 $\max(x_k - x_i, x_i - x_k)$，于是两边同时都需要满足，也就是：

$$
\begin{cases}
h_i + x_i \le m + x_k + p_k \\
h_i - x_i \le m - x_k + p_k
\end{cases}
$$
分别记录 $h_i + x_i$ 和 $h_i - x_i$ 的最大值即可判断 $k$ 删除后是否满足条件。

代码（我在乱搞……所以代码有些抽象）：<https://codeforces.com/problemset/submission/1710/229413132>


---

## 作者：fanypcd (赞：0)

给个不过脑子的做法。适合我这种没有长脑子的人。

首先考虑算出每个位置最终的降雨量。注意到如果一个位置不是某天的中心，它最终的降雨量肯定是不优于两边的，原因显然。所以只用考虑所有降雨中心最终的降雨量。

先将所有天的降雨按中心位置从小到大排序。这样每一次降雨能影响到的位置范围是数组中连续的一段，不妨记为 $[L_i,R_i]$。

将绝对值号拆开分类讨论，先处理位置在第 $x_i$ 前的情况，每个位置的增量为 $(p_i-x_i)+x_j$，括号内的为定值，$x_j$ 对于每一位也是定值，用两个数组差分即可。

位置在 $p_i$ 后的同理，详见文末代码链接。

现在已有每个位置的降雨量 $v_i$，仍然是依次枚举撤销 $i$ 天的影响：

如果影响范围外有大于限制的值，即 $\exists j \in\Big([1,L_i) \cup (R_i,n]\Big)\cap \mathbb{N_+},v_j>m$，当前位置答案为 0。

如果影响范围内存在，即 $\exists j \in [L_i,R_i]\cap \mathbb{N_+},v_j-(p_i-|x_i-x_j|)>m$，当前位置答案为 0。

思路仍然是分类讨论拆绝对值，维护区间 $v_i+x_i,v_i-x_i$ 的最大值即可，st 表和线段树等数据结构任选。

[Code](https://codeforces.com/contest/1710/submission/175198252)

---

## 作者：CReatiQ (赞：0)

### 题意概述

给定 $n$ 对正整数 $x_i$ 与 $p_i$，每对 $x_i$ 与 $p_i$ 代表位置 $x_i$ 为中心发生一次强度为 $p_i$ 的降雨，场上每个位置 $j$ 会增加 $\max \{ 0,p_i-|x_i-j| \}$ 的积水。

如果降水过后有位置积水超过 $m$，则会发生洪水。

对于每一场降雨，求其如果被单独消除，能否使得场上不会发生洪水。

$( 1 \leq n \leq 2 \cdot 10^5 , 1 \leq m,x_i,p_i \leq 10^9 )$

---

### 思路

一场降雨消除，显然比下 $n-1$ 场雨处理起来方便，我们先从下完 $n$ 场雨的状态入手。

考虑求下完 $n$ 场雨后场上的积水情况，但是 $10^9$ 级的数据范围显然是我们不能承受的，应该需要寻找特殊性质，另其与 $n$ 同级。

可观察得：在场上有积水时，积水最多的位置一定是此前某次降雨发生的中心。（此结论并非解题必须，后面会讲可以替代它的结论）

下面是略篇感性的理解，可以自行选择阅读或跳过：

形象一些来想象，每次发生一场降雨，场上就多出一座“雨峰”，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/s2zyt0bg.png)

如果多场降雨发生，可能“雨峰”相叠成山，相连成片，或者相互独立等，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/8vfp2o4k.png)

观察图中各条折线的斜率，可以发现：如果我们新增一座“雨峰”，因为新增的峰向两边展开的斜率小于等于原有峰的斜率（可能与新峰一样，都与水平面成 45 度角，也可能与其它峰重叠而斜率增加），它要么不能使得非“峰顶”的位置超越积水最多的位置，要么自己的“峰顶”就成为了降水最多的位置。

所以就有了前面那句：

> 在场上有积水时，积水最多的位置一定是此前某次降雨发生的中心。

由此，我们可以把 $10^9$ 级别的范围缩小到最坏 $2 \cdot 10^5$ 个点来考虑。

毕竟题目中的降雨算是区间操作，所以我选择了用线段树维护，可以把降雨拆成两段，看成一次函数的叠加，线段树维护一次函数的斜率与截距即可。



前面说到，积水最多位置在中心的结论可以被替代，其实就是用一个常见的令巨大范围降至操作次数同级的方法——离散化。

我们将 $n$ 次降雨影响的中心，左端点，右端点记录下来离散化（其实就类似于刚才将降雨拆成两段）。

离散化后，相邻两个位置之间的部分斜率是唯一的，也就意味着相邻两点一定包含它们为端点的闭区间上的积水最多位置，点数降至最坏 $6 \cdot 10^5$，虽然比刚才的方法略差，但能够接受，同样可以用线段树解决。

在知道每个可能的积水最多位置的最终积水 $y$ 后，我们就可以大力推导积水，消除降雨，洪水之间的关系了。

假设有 $n$ 次降雨后积水大于 $m$ 的位置 $j$，且消除降雨 $i$ 后 $j$ 处的积水小于等于 $m$ ，则有 $y_j-j+x_i-p_i \leq m$ 或 $y_j+j-x_i-p_i \leq m$ （代表在 $j$ 降雨 $i$ 的中心两侧的情况）。

将与 $i$ 和与 $j$ 有关的量移向等式两边，利用求出的 $y$ 数组对与 $j$ 有关的部分 $\mathcal{O}(n)$ 预处理最大值，再判断每场降雨是否符合要求即可，具体可见代码。

因为有线段树更新，查询以及前面的离散化两个过程，算法的时间复杂度为 $\mathcal{O}(n \log n)$。

---

### Code

为了方便，这里直接用线段树维护了文中的 $y$ 数组而非斜率截距。

看到代码，你可能会有疑问：`id` 的合并并不满足结合律，这样上传会出错。

但实际上这种错误是 `query` （区间查询）操作标记不能完全下传带来的，此处只需要用到 `get` （单点查询），每次查询都会将路径上的标记完全下传，所以并不会出现问题。


```cpp
#include <algorithm>
#include <iostream>
#include <cstring> 
#include <cstdio>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <set>
#include <map>
using namespace std;
#define int long long
#define MAXN (int)(3e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)

namespace crq
{

	inline long long read()
	{
		long long x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
		return f*x;
	}

	template <typename T> inline T max(T x,T y) { return x>y?x:y; }
	
	template <typename T> inline T min(T x,T y) { return x<y?x:y; }
	
	template <typename T> inline T abs(T x) { return x>0?x:-x; }
	inline int zero() { return 0ll; }

	template <typename A,typename... B>
	A max(A first,B... others)
	{ return max(first,max(others...)); }
	
	template <typename A,typename... B>
	A min(A first,B... others)
	{ return min(first,min(others...)); }
	
	template<typename V_crq,V_crq(*V_op)(V_crq,V_crq),V_crq (*V_e)(),
	typename T_crq,T_crq(*T_op)(T_crq,T_crq),T_crq (*T_e)(),V_crq(*F)(T_crq,V_crq)>
	struct lazy_Seg
	{
		
		//Tips: The id of this Segment Tree is begin at 1 but not 0.
		//All T_op-based assignment operations in this Segment Tree
		//are in the following form : "Tag_A=T_op(Tag_B,Tag_A)" .
		
		#define ls (now<<1)
		#define rs (now<<1|1)
		
		public:
			
			void init(int n,V_crq *poi)
			{
				init_pow2();
				h=ceil_log2(n);
				SIZE=1<<h;
				val=std::vector<V_crq>(SIZE<<1,V_e());
				tag=std::vector<T_crq>(SIZE,T_e());
				for (int i=0;i<n;i++) val[SIZE+i]=*(poi+i);
				for (int i=SIZE-1;i>=1;i--) pushup(i);
			}
			
			void modify(int k,V_crq x)
			{
				k+=SIZE-1;
				for (int i=h;i>=1;i--) pushdown(k>>i);
				val[k]=x;
				for (int i=1;i<=h;i++) pushup(k>>=1);
			}
			
			V_crq get(int k)
			{
				k+=SIZE-1;
				for (int i=h;i>=1;i--) pushdown(k>>i);
				return val[k];
			}
			
			void update(int l,int r,T_crq x)
			{
				if (l>=r+1) return;
				l+=SIZE-1,r+=SIZE;
				for (int i=h;i>=1;i--)
				{
					if (((l>>i)<<i)!=l) pushdown(l>>i);
					if (((r>>i)<<i)!=r) pushdown((r-1)>>i);
				}
				int tl=l,tr=r;
				while (tl<tr)
				{
					if (tl&1) update_by_tag(tl++,x);
					if (tr&1) update_by_tag(--tr,x);
					tl>>=1,tr>>=1;
				}
				for (int i=1;i<=h;i++)
				{
					if (((l>>i)<<i)!=l) pushup(l>>i);
					if (((r>>i)<<i)!=r) pushup((r-1)>>i);
				}
			}
			
			V_crq query(int l,int r)
			{
				if (l==r+1) return V_e();
				l+=SIZE-1,r+=SIZE;
				for (int i=h;i>=1;i--)
				{
					if (((l>>i)<<i)!=l) pushdown(l>>i);
					if (((r>>i)<<i)!=r) pushdown((r-1)>>i);
				}
				V_crq sl=V_e(),sr=V_e();
				while (l<r)
				{
					if (l&1) sl=V_op(val[l++],sl);
					if (r&1) sr=V_op(val[--r],sr);
					l>>=1,r>>=1;
				}
				return V_op(sl,sr);
			}
			
		private:
		
			int SIZE,h,pow2[27];
			std::vector<V_crq> val;
			std::vector<T_crq> tag;
			
			void init_pow2()
			{
				pow2[0]=1;
				for (int i=1;i<=25;i++) pow2[i]=pow2[i-1]<<1;
			} 
			
			int ceil_log2(int x)
			{
				for (int i=25;i>=1;i--)
					if (pow2[i]>=x&&pow2[i-1]<x)
						return i;
				return 0;
			}
			
			inline void update_by_tag(int k,T_crq x)
			{
				val[k]=F(x,val[k]);
				if (k<SIZE) tag[k]=T_op(x,tag[k]);
			}
			
			inline void pushup(int now) { val[now]=V_op(val[ls],val[rs]); }
			
			inline void pushdown(int now)
			{
				update_by_tag(ls,tag[now]);
				update_by_tag(rs,tag[now]);
				tag[now]=T_e();
			}
			
		#undef ls
		#undef rs
		
	};
	
}

using crq::read;
using crq::lazy_Seg;

struct Node { int val,id; } A[MAXN];

struct Tag { int bas,rat; };

inline Node opt1(Node x,Node y)
{ return x.val>y.val?x:y; }

inline Tag opt2(Tag x,Tag y)
{ return Tag{x.bas+y.bas,x.rat+y.rat}; }

inline Node N_e() { return Node{0,0}; }

inline Tag T_e() { return Tag{0,0}; }

inline Node F(Tag x,Node y)
{ return Node{y.val+x.bas+y.id*x.rat,y.id}; }

int T,n,m,len,f[MAXN],x[MAXN],p[MAXN];
lazy_Seg<Node,opt1,N_e,Tag,opt2,T_e,F> s;

void R()
{
	cin>>n>>m;
	rep(i,1,n)
	{
		A[i].val=0;
		f[i]=x[i]=read();
		p[i]=read();
	}
	sort(f+1,f+n+1);
	len=unique(f+1,f+n+1)-(f+1);
	rep(i,1,len) A[i].id=f[i];
	s.init(len,A+1);
	rep(i,1,n)
	{
		int l=lower_bound(f+1,f+len+1,x[i]-p[i])-f,
		r=upper_bound(f+1,f+len+1,x[i]+p[i])-f-1,
		now=lower_bound(f+1,f+len+1,x[i])-f;
		s.update(l,now,Tag{p[i]-x[i],1});
		s.update(now+1,r,Tag{p[i]+x[i],-1});
	}
	int tmp1=-1e9-7,tmp2=-1e9-7;
	rep(i,1,len)
	{
		if (s.get(i).val>m)
		{
			tmp1=crq::max(tmp1,s.get(i).val-s.get(i).id);
			tmp2=crq::max(tmp2,s.get(i).val+s.get(i).id);
		}
	}
	rep(i,1,n)
		printf("%d",(p[i]-x[i]>=tmp1-m)&&(p[i]+x[i]>=tmp2-m));
	putchar('\n');
}

signed main()
{
	cin>>T;
	while (T--) R();
	return 0;
}
```


---

