# Dyn-scripted Robot (Hard Version)

## 题目描述

这是该问题的困难版本。唯一的区别在于本版本中 $k \le 10^{12}$。只有当你同时解决了两个版本的问题时，才能进行 hack。

给定一个 $w \times h$ 的矩形，位于 $Oxy$ 平面上，左下角为点 $(0, 0)$，右上角为点 $(w, h)$。

你还有一个初始位于点 $(0, 0)$ 的机器人，以及一个长度为 $n$ 的脚本 $s$。脚本 $s$ 由 $n$ 个字符组成，每个字符为 L、R、U 或 D，分别表示机器人向左、右、上、下移动。

机器人只能在矩形内部移动；如果它试图移出矩形，则会按如下方式更改脚本 $s$：

- 如果它试图越过垂直边界，则将所有 L 字符变为 R（反之亦然，将所有 R 变为 L）。
- 如果它试图越过水平边界，则将所有 U 字符变为 D（反之亦然，将所有 D 变为 U）。

然后，机器人会从无法执行的那个字符开始，执行更改后的脚本。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F2/ff49f6aa11a19418f77260f4c00c02fa1a42de65.png)  
这是机器人的移动过程示例，$s = \texttt{"ULULURD"}$。

脚本 $s$ 会连续执行 $k$ 次。所有对字符串 $s$ 的更改在每次重复时都会保留。在这个过程中，机器人总共会有多少次移动到点 $(0, 0)$？注意，初始位置不计入。

## 说明/提示

在第一个测试用例中，机器人前两次只会向上和向右移动。之后，它会停在 $(2, 2)$。接下来的两次执行中，它会向下和向左移动，最终回到 $(0, 0)$。所以答案是 $1$。

在第二个测试用例中，每次执行脚本时，机器人都会访问原点两次。由于 $k=2$，所以总共访问原点 $2 \cdot 2 = 4$ 次。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F2/4c04dc66914a3e1ee672ced7111b24a5891eec80.png)  
在第三个测试用例中，移动过程可视化如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F2/354b17fd45a6d2914b35f5325993193690563e94.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
2 4 2 2
UR
4 2 1 1
LLDD
6 3 3 1
RLRRRL
5 6 3 3
RUURD
7 5 3 4
RRDLUUU
7 123456789999 3 2
ULULURD```

### 输出

```
1
4
3
1
1
41152263332```

# 题解

## 作者：Register_int (赞：10)

E 不会，F2 一眼秒了，调啊调啊调，调啊调啊调，没调出来，寄！

本题最麻烦的是这个翻转操作。但是我们可以选择不将路径翻转，而是将整个矩形翻转。大概是长这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/lltz2nrq.png)

发现一个矩形翻两次就回到原来的样子。问题变为：将原来的路径重复 $k$ 遍，问最终有多少个 $(x,y)$ 满足 $2w\mid x$ 且 $2h\mid y$。

先 $w\gets2w$，$h\gets2h$，枚举路径上第 $i$ 个点 $(x_i,y_i)$。那么这个点在整条路径上对应的就是 $(x_i,y_i),(x_n+x_i,y_n+y_i),\cdots,((k-1)x_n+x_i,(k-1)y_n+y_i)$。

这里有两维限制，先把两维分别类欧解出来 $k$ 在 $w,h$ 模意义下的数值，再 exCRT 合并。最后可以算出 $k\bmod p=q$ 的形式，答案累加上 $\lfloor\frac{k+p-q}{p}\rfloor$ 即可。总时间复杂度 $O(n\log V)$。

---

## 作者：hongzy (赞：3)

可以遇到边界不反射，直接在镜像空间中走。

原过程中的点走到 $(0,0)$，相当于直接在镜像空间中走到某个原点的对称点 $(x,y)$，满足 $(2w)\mid x, (2h)\mid y$。

那么问题就变得容易，注意到轮数 $k$ 较大，不能枚举，故枚举走到序列的第 $i\ (1\le i\le n)$ 个位置后走到了满足条件的 $(x,y)$。那么设这是第 $x\ (0\le x < k)$ 轮，记 $dx,dy$ 为走 $1..i$ 这些步后的坐标偏移，$sx,sy$ 为走完一轮所有步后的唯一，那么轮数需要满足

$$
x\cdot sx+dx\equiv 0 \pmod{2w} \\
y\cdot sy+dy\equiv 0 \pmod{2h}
$$

这是经典的同余方程组，可以使用扩展中国剩余定理 excrt 求解。具体而言，对于方程 $ax\equiv b \pmod {m}$，为了转换为标准形式，我们先对 $ax+my=b$ 进行 exgcd，求出解 $x_0$，那么根据二元一次不定方程通解的形式，该方程可以转换为

$$
x\equiv x_0 \pmod {\frac{m}{\gcd(m,a)}}
$$

即为 excrt 标准形式。

求出最小的解 $x\equiv x_0 \pmod {m}$ 后，答案即为 $x_0,x_0+m,x_0+2m,...$ 中有多少个在 $[0,k-1]$ 中，其答案为 $\lfloor \frac{k-1-x_0}{m} \rfloor +1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, w, h;
ll k;
string s;
ll Mod(ll x, ll y) {
  return (x % y + y) % y;
}

ll c[4], d[4]; //x = d[i] (mod c[i])
ll mul(ll a, ll b, ll p) {
  ll r = a * b - (ll)((long double)a * b / p + 0.5) * p;
  return r < 0 ? r + p : r;
}
void exgcd(ll a, ll b, ll &x, ll &y, ll &g) {
  if(!b) x = 1, y = 0, g = a;
  else exgcd(b, a % b, y, x, g), y -= a / b * x;
}
ll excrt(ll &mod) {
  ll a = c[1], b = d[1];
  for (int i = 2; i <= 2; i ++) {
    ll k, t, g;
    exgcd(a, c[i], k, t, g);
    if ((d[i] - b) % g != 0)
      return -1;
    t = c[i] / g;
    k = mul(k, (d[i] - b) / g, t);
    ll na = a * t;
    b = (mul(a, k, na) + b) % na;
    a = na;
  }
  mod = a;
  return (b % a + a) % a;
}


ll crt(ll a1, ll b1, ll m1, ll a2, ll b2, ll m2) {
  a1 = Mod(a1, m1); b1 = Mod(b1, m1);
  a2 = Mod(a2, m2); b2 = Mod(b2, m2);
  ll x, y, g;
  exgcd(a1, m1, x, y, g);
  if (b1 % g)
    return 0;
  c[1] = m1 / g;
  d[1] = mul(x, b1 / g, c[1]);

  exgcd(a2, m2, x, y, g);
  if (b2 % g)
    return 0;
  c[2] = m2 / g;
  d[2] = mul(x, b2 / g, c[2]);

  ll mod;
  ll r = excrt(mod);
  if (r == -1)
    return 0;
  if (r >= k)
    return 0;
  return (k - 1 - r) / mod + 1;
}
void solve() {
  cin >> n >> k >> w >> h;
  cin >> s;
  ll ans = 0;
  ll dx = 0, dy = 0;
  for (char c: s) {
    if (c == 'L') dx --;
    if (c == 'R') dx ++;
    if (c == 'D') dy --;
    if (c == 'U') dy ++;
  }
  ll sx = dx, sy = dy;
  dx = 0, dy = 0;
  for (char c: s) {
    if (c == 'L') dx --;
    if (c == 'R') dx ++;
    if (c == 'D') dy --;
    if (c == 'U') dy ++;
    ll res = crt(sx, -dx, 2*w, sy, -dy, 2*h);
    ans += res;
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int test;
  cin >> test;
  while(test --) {
    solve();
  }
  return 0;
}
```

---

## 作者：Pengzt (赞：2)

# Dyn-scripted Robot (Hard Version)

[题目链接](https://www.luogu.com.cn/problem/CF1993F2)。[cnblogs](https://www.cnblogs.com/Pengzt/p/18664555)。

### Problem

Easy Version：$K \le n$。

Hard Version：$K \le 10^{12}$。

一个 $Oxy$ 平面上有一个 $w \times h$ 矩形，矩形的左下方有点 $(0, 0)$ ，右上方有点 $(w, h)$ 。

您还有一个最初位于点 $(0, 0)$ 的机器人和一个由 $n$ 个字符组成的脚本 $s$ 。每个字符都是 L、R、U 或 D，分别指示机器人向左、向右、向上或向下移动。

机器人只能在矩形内移动，否则将更改脚本 $s$ 如下：

- 如果试图向垂直边界外移动，则会将所有 `L`、`R` 取反。
- 如果尝试向水平边界外移动，则会将所有 `U`、`D` 取反。

然后，它会从无法执行的字符开始执行更改后的脚本。

![](https://espresso.codeforces.com/44058d13574b8a336b6b4ffc319b349c0a98032e.png) 

这是一个机器人移动过程的示例，其中 $s = \texttt{"ULULURD"}$ 。

脚本 $s$ 将被连续执行 $K$ 次。即使重复执行，也会保留对字符串 $s$ 的所有更改。在此过程中，机器人总共会**移动到** $(0, 0)$ 点多少次？

**注意，初始在 $(0,0)$ 的一次不计算在内**。

数据范围：$1\le n, w, h \le 10^6$。

### Sol

暴力显然是不可行的。发现这个东西会时刻将 LR/UD 取反是非常麻烦的。想想怎么不去反，发现抛开边界的限制，不取反就是做一个关于 $x/y$ 轴的镜像。然后发现这个东西在 $(x, y)$ 和 $(x - 2w, y), (x, y - 2h)$ 是等价的，即在两倍意义下同余。然后就可以做了。现在要对于一个点 $(x, y)$，以及每次移动的位置 $(a, b)$，求移动 $k$ 次的过程中，有多少次的坐标等价于 $(0, 0)$。

然后 Easy Version 就可以直接枚举走的步数，用 map 存下每个点的位置，计算偏移量后暴力相加即可，时间复杂度：$\mathcal{O}(K(\log w + \log h))$。

Hard Version 也差不多。就是知道 $x$ 在同余系下走到 $0$ 的轮数为 $k_0x + b_0$，$y$ 为 $k_1x+b_1$，大致就是最开始是第 $b$ 轮的时候开始走，然后每 $k$ 轮走回来。然后求的是有多少个 $t \in [1, K]$，使得 $\exists u,v \in [1, n] \cap \mathbb Z,t = k_0u + b_0 = k_1v + b_1$。然后就变成了 $k_0u - k_1v = b_0 - b_1$，直接用 exgcd 解出一组特解之后就可以直接算了。时间复杂度：$\mathcal{O}(n \log K)$。

感觉这场 Hard Version 能有 `*2800` 完全是因为这题细节有一点啊，就只是比 Easy Version 多了合并循环节的步骤。

### Code

F2 Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second
mt19937_64 eng(time(0) ^ clock());
template <typename T>
T rnd(T l, T r) { return eng() % (r - l + 1) + l; }
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b)
		return x = 1, y = 0, a;
	ll d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
ll lcm(ll x, ll y) { return x * y / __gcd(x, y); }
int n;
ll w, h, K;
int px[1000005], py[1000005];
char s[1000005];
void Solve() {
	scanf("%d%lld%lld%lld%s", &n, &K, &w, &h, s + 1); 
	K--;
	w <<= 1, h <<= 1;
	px[0] = py[0] = 0;
	for (int i = 1; i <= n; i++) {
		px[i] = px[i - 1], py[i] = py[i - 1];
		if (s[i] == 'L') px[i]--;
		else if (s[i] == 'R') px[i]++;
		else if (s[i] == 'U') py[i]++;
		else py[i]--;
		px[i] = (px[i] % w + w) % w;
		py[i] = (py[i] % h + h) % h;
	}
	ll dx = px[n], dy = py[n], ans = 0;
	for (int i = 1; i <= n; i++) {
		ll x, y;
		ll d0 = exgcd(dx, w, x, y);
		if (px[i] % d0)
			continue;
		ll b0 = x * (-px[i] / d0), k0 = w / __gcd(w, dx);
		b0 = (b0 % k0 + k0) % k0;
		ll d1 = exgcd(dy, h, x, y);
		if (py[i] % d1)
			continue;
		ll b1 = x * (-py[i] / d1), k1 = h / __gcd(h, dy);
		b1 = (b1 % k1 + k1) % k1;
		ll d = exgcd(k0, k1, x, y), len = lcm(k0, k1) / k0, dltx = lcm(k0, k1) / k0, dlty = lcm(k0, k1) / k1;
		if ((b1 - b0) % d)
			continue;
		x *= (b1 - b0) / d, y *= (b1 - b0) / d;
		if (y < 0) {
			ll t = (-y + dlty - 1) / dlty;
			x -= t * dltx, y += t * dlty;
		}
		if (y > 0) {
			ll t = (y + dlty - 1) / dlty;
			x += t * dltx, y -= t * dlty;
		}
		if (k0 * x + b0 > K)
			continue;
		ll limx = (K - b0) / k0;
		ans += (limx - x) / len + 1;
	}
	printf("%lld\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		Solve();
	return 0;
}
```

F1 Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 7;
int n, m, W, H, m1, m2;
int s1[N], s2[N];
char str[N];
map < int, int > mp[N << 1];
void Solve() {
    scanf("%d%d%d%d", &n, &m, &W, &H);
    m1 = 2 * W, m2 = 2 * H;
    scanf("%s", str + 1);
    for (int i = 1; i <= n; ++i) {
        s1[i] = s1[i - 1], s2[i] = s2[i - 1];
        if (str[i] == 'L') s1[i] = (s1[i - 1] + 1) % m1;
        else if (str[i] == 'R') s1[i] = (s1[i - 1] - 1 + m1) % m1;
        else if (str[i] == 'U') s2[i] = (s2[i - 1] + 1) % m2;
        else s2[i] = (s2[i - 1] - 1 + m2) % m2;
        ++mp[s1[i]][s2[i]];
    }
    ll ans = 0;
    for (int t = 0; t < m; ++t) {
        int r1 = (m1 - t * 1ll * s1[n] % m1) % m1, r2 = (m2 - t * 1ll * s2[n] % m2) % m2;
        ans += mp[r1][r2];
    }
    printf("%lld\n", ans);
    for (int i = 1; i <= n; ++i) mp[s1[i]].clear();
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) Solve();
    return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

### [CF1993F2 Dyn-scripted Robot (Hard Version)](https://www.luogu.com.cn/problem/CF1993F2)

尚不清楚 F1 存在的必要性。

本题唯一一步转化是在碰到边界时修改翻转字符等价于不翻转字符且无视边界，因为穿过边界相当于以边界为轴创造了一个镜面世界，在镜面世界的移动和原世界移动方向相反，所以需要翻转所有和所穿过边界相对应的移动。在此基础上，所有满足 $x\equiv 0\pmod {2w}$，$y\equiv 0\pmod {2h}$ 的 $(x, y)$ 都是原点。

设 $x_i$ 表示执行到 $s_i$ 时 $x$ 方向上的偏移量，设 $X$ 表示每一轮在 $x$ 坐标上的偏移量，则第 $p$ 次执行到 $s_i$ 时的 $x$ 坐标为 $(p - 1)X + x_i$。问题转化为对每个 $i$，求满足同余方程组
$$
\begin{cases}
pX + x_i\equiv 0\pmod {2w} \\
pY + y_i\equiv 0\pmod {2h}
\end{cases}
$$
且 $0\leq p < k$ 的 $p$ 的数量。

根据基础数论知识，$ax + b\equiv 0\pmod c$ 可以在 $d = \gcd(a, c)\mid b$（否则无解）时转化为 $x \equiv -\frac b d(\frac a {d}) ^ {-1} \pmod {\frac c d}$。于是问题转化为
$$
\begin{cases}
p\equiv x'_i \pmod {M_x} \\
p\equiv y'_i \pmod {M_y}
\end{cases}
$$
使用 exCRT 合并（设 $p = tM_x + x'_i$，则 $tM_x + x'_i\equiv y'_i\pmod {M_y}$）为 $p\equiv c\pmod M$ 后容易计算。

注意特判 $X = 0$ 或 $Y = 0$ 的情况。

时间复杂度 $\mathcal{O}(n + \log w + \log h)$。[代码](https://codeforces.com/contest/1993/submission/274706094)。

---

## 作者：绝顶我为峰 (赞：1)

退役选手复建，再不加训要被挂黑板了。

碰到边界反向很容易想到可以直接穿过，相当于到了一个镜像的空间里。

那么这样相当于在一个无限的二维平面上走，地图的边界被无限镜像，那么原点就会被镜像到点集 $\{(x,y)|x\equiv 0 (\mod 2w),y\equiv 0(\mod 2h)\}$ 上，现在只需要统计这些点被经过了多少次。

两维是独立的，可以拆开，预处理出这一维前 $i$ 步的偏移量 $d_i$ 和一轮的偏移量 $D$。

考虑对于所有执行到第 $i$ 步的情况计算答案，这样横坐标上相当于在解同余方程 $Dx+d_i\equiv0(\mod 2w)$，纵坐标是同理的，这容易通过 exgcd 解出。

现在我们得到了每一个维度上的通解 $x=ax_0+b$，接下来只需要合并两个维度得到新的通解即可，exgcd 和 excrt 都可以解决这个问题，笔者在实现时使用了 exgcd。

注意到所有同余方程 $ax+by=c$ 的 $a,b$ 均相同，因此只需要在开始时调用一次 exgcd，时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
int t,n,m,w,h,ans,a[1000001],b[1000001];
inline void init()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
inline int read()
{
    int x;
    cin>>x;
    return x;
}
int gcd(int x,int y)
{
    if(!x||!y)
        return x|y;
    return x%y? gcd(y,x%y):y;
}
void exgcd(int a,int b,int &x,int &y)
{
    if(!b)
    {
        x=1;
        y=0;
        return;
    }
    exgcd(b,a%b,y,x);
    y-=a/b*x;
}
signed main()
{
    init();
    t=read();
    while(t--)
    {
        n=read(),m=read(),w=read()<<1,h=read()<<1;
        for(int i=1;i<=n;++i)
        {
            char c;
            cin>>c;
            a[i]=a[i-1];
            b[i]=b[i-1];
            if(c=='L')
                a[i]=(a[i]-1+w)%w;
            if(c=='R')
                a[i]=(a[i]+1)%w;
            if(c=='D')
                b[i]=(b[i]-1+h)%h;
            if(c=='U')
                b[i]=(b[i]+1)%h;
        }
        int g1=gcd(a[n],w),g2=gcd(b[n],h),x,y,w1,w2,dx=w/g1,dy=h/g2,g=gcd(dx,dy),dw1=dy/g,dw2=dx/g;
        exgcd(a[n],w,x,*new int);
        exgcd(b[n],h,y,*new int);
        exgcd(dx,dy,w1,w2);
        for(int i=1;i<=n;++i)
        {
            a[i]=(w-a[i])%w;
            b[i]=(h-b[i])%h;
            if(a[i]%g1||b[i]%g2)
                continue;
            int xx=x*a[i]/g1,yy=y*b[i]/g2;        
            xx=(xx%dx+dx)%dx;
            yy=(yy%dy+dy)%dy;
            if((yy-xx)%g)
                continue;
            int ww1=w1*(yy-xx)/g,ww2=w2*(yy-xx)/g,tmp=ww1/dw1;
            ww1-=tmp*dw1;
            ww2+=tmp*dw2;
            if(a[n]&&ww1<0)
            {
                int cnt=(dw1-ww1-1)/dw1;
                ww1+=cnt*dw1;
                ww2-=cnt*dw2;
            }
            if(b[n]&&ww2>0)
            {
                int cnt=(dw2+ww2-1)/dw2;
                ww1+=cnt*dw1;
                ww2-=cnt*dw2;
            }
            if(ww1*dx+xx<m)
                ans+=(m-ww1*dx-xx-1)/(dw1*dx)+1;
        }
        cout<<ans<<'\n';
        ans=0;
    }
    cout.flush();
    return 0;
}
```

---

## 作者：_LSA_ (赞：1)

# Solution(Hard Version)
注：参考 ~~（翻译复述）~~ 了官方题解

我们发现每次碰到边界反转不好维护，于是我们不考虑反转，让它走出边界，再考虑它对应原矩形的哪个点。

显然行和列两个方向是独立的，我们接下来从讨论列的方向上来讨论。

我们先从简单的情况开始，令 $R$ 表示每次遇到边界**都**反转操作的机器人，$B$ 为遇到边界**不**反转操作的机器人，当他们即将越出上边界 $H$ ，而下一个操作又是往上走时，$R$ 会反转操作往下走，而 $B$ 会继续往上走，接下来在 $R$ 没有碰到下一个边界之前，我们发现，它们经过的路径是关于上边界 $H$ 成**镜像**的。

接下来如果 $B$ 继续向上走，走到 $2H$，再继续往上走，对应的，$R$ 将走到 $0$，反转为原来的操作，也继续往上走，那么它们接下来的操作将是一样的，而它们的坐标差为 $2H$。

同理当 $B$ 走到 $3H$ 时，它们的操作又会成镜像，走到 $4H$ 时，它们操作又会相同而坐标差变为 $4H$，走到 $0$ 以下，$-H$ 以下也是同理。于是我们可以归纳出以下性质：$R$ 的纵坐标 $y$ 与 $y$ 模 $2H$ 意义下同余的坐标是等价的。

横坐标也是同理，$x$ 与 $x \bmod 2H$ 是等价的。

那么我们把矩形扩大到 $2W\times 2H$，就可以在这个范围内维护出 $B$ 的运动轨迹。

回到题意，题目要求经过点 $(0,0)$ 的次数，我们发现，刚好当且仅当在 $B$ 也经过 $(0,0)$ 时，$R$ 才经过 $(0,0)$。

我们可以处理出 $B$ 沿着操作走一次的终止位置 $(x,y)$。令 $x_i=(i-1)x \bmod 2W,y_i=(i-1)y \bmod 2H$，那么第 $i$ 轮操作的起始位置就在 $(x_i,y_i)$，这轮操作走到 $(0,0)$ 的次数实际上就是第一轮操作走到 $(2W-x_i,2H-y_i)$ 的次数。

对于简单版本，我们直接枚举当前是第几轮即可。

而困难版本中 $k$ 的范围较大，那么我们换个角度，考虑每一个第一轮经过点的贡献。

令第一轮终止位置为 $(x,y)$，一个点 $(x_j,y_j)$ 在第 $(i+1)$ 轮有贡献，当且仅当：

$$
 x_j+i\times x \equiv 0 \pmod{2W}
$$
$$
 y_j+i\times y \equiv 0 \pmod{2H}
$$
也就是说，我们要对每一对 $(x_j,y_j)$ 求出有多少对满足条件的 $i$。

我们先对这个方程变形一下可以得到

$$
 i \equiv -x_j\times x^{-1} \pmod{2W}
$$
$$
 i \equiv -y_j\times y^{-1} \pmod{2H}
$$

由于逆元仅在互质的情况下存在，所以上式是不严谨的，我们需要先进行一个类似“约分”的操作，令 $g=\text{gcd}(x,2W),W'=\frac{2W}{g},c_x=-\frac{x_j}{g}(\frac{x}{g})^{-1}$，则
$$
 i \equiv c_x \pmod{W'}
$$
同理有
$$
 i \equiv c_y \pmod{H'}
$$
我们对第一个式子变形，类似解同余方程的方法可以得到
$$
i=c_x+zW'
$$
其中 $z$ 为整数。

代入第二个式子则有

$$
zW'\equiv c_y-c_x \pmod{H'}
$$
同理我们进行一次“约分”操作将 $W'$ 逆元求出来乘到对面去即可得到 $z$ 的最非负整数解 $z_0$。

那么贡献就是满足 $i=c_x+zW'$，且 $0\le i <k$ 的正整数 $i$ 的个数。由于我们求出了最小的 $z_0$，于是我们也得到了最小的 $i_0=c_x+z_0W'$，而上面方程组的循环周期为 $L=\text{lcm}(W',H')$，所以 $i=i_0+dL$，其中 $d \in \mathbb{N}$，解出有多少个 $d$ 即可。

时间复杂度 $O(n \log n)$，其中 $\log$ 在于求逆元和 $\text{gcd}$。

---

## 作者：luckydrawbox (赞：1)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1993F2)

## 题意

在平面直角坐标系中，机器人初始位于 $(0,0)$，有一段长度为 $n$ 的仅包含 $\texttt{DULR}$ 的操作序列 $s$，机器人将把此操作序列执行 $k$ 轮，要求机器人任意时刻的位置都必须在 $(0,0)-(h,w)$ 的矩形中，若按第 $i$ 个操作移动会超出矩形，那么若 $s_i$ 为 $\texttt{L/R}$，将 $s$ 中所有 $\texttt{L}$ 变成 $\texttt{R}$，所有 $\texttt{R}$ 变成 $\texttt{L}$；若 $s_i$ 为 $\texttt{U/D}$ 也同理。变换后再执行第 $i$ 个操作，注意变换对操作序列的影响会保留到下一轮。

求机器人在移动过程中经过 $(0,0)$ 的次数（不包括初始状态）。

数据范围：$t$ 为数据组数，$1 \le t \le 10^4,1 \le \sum n,w,h \le 10^6,1 \le k \le 10^{12}$。

由于神秘原因，本题解的 $h,w$ 对应原题中的 $w,h$。

## 分析

场上想不出 F1 的简单做法，但会了 F2，然而由于时间原因最终没有调出来。

先考虑一个简单的转化：带限制走到 $(0,0)$ 相当于不带限制走到 $(2ah,2bw)\ (a,b\in \mathbb{Z})$。

简单证明一下，假设一次 $\texttt{U}$ 时超出了矩阵，那么 $\texttt{L,R}$ 不受影响，若不改变操作序列，则相当于把走到 $(0,0)$ 改为了走到 $(0,2w)$；$\texttt{D,L,R}$ 也以此类推，所以转化成立。

于是问题要求经过 $(2ah,2bw)\ (a,b\in \mathbb{Z})$ 的次数，显然一轮后的位移是固定的，令其为 $(X,Y)\ (0\le X< 2h,0\le Y<2w)$，所以我们枚举一轮中第 $i$ 个操作作为结尾，设第一轮中第 $i$ 次操作后位于 $(x_i,y_i)$，那么在第 $j+1\ (0\le j\le k-1)$ 轮中机器人位于 $(x_i+jX,y_i+jY)$。

先将 $x,y$ 分开考虑，那么 $x_i+jX=2ah,y_i+jY=2bw$。

可以转化为同余方程 $jX\equiv -x_i\pmod {2h},jY\equiv -y_i\pmod {2w}$，用两次 $\texttt{exgcd}$ 分别算出两个方程的通解，再用一次 $\texttt{exgcd}$ 合并即可。

时间复杂度 $O(n\log k)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define PY puts("YES")
#define PN puts("NO")
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch))
	{if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e6+10;
int t,n,h,w;
ll k,ans; 
string s;
int fx[4]={0,0,-1,1};
int fy[4]={-1,1,0,0};
struct Node{
	int x,y;
}a[N];
Node forward(Node p,int t){
	return (Node){p.x+fx[t],p.y+fy[t]};
}
int turn(char c){
	if(c=='D')return 0;
	if(c=='U')return 1;
	if(c=='L')return 2;
	return 3;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(!b){
        x=1;y=0;
        return a;
    }
    long long d=exgcd(b,a%b,x,y);
    long long z=x;x=y;y=z-y*(a/b);
    return d;
}
ll solve(Node p,ll k){
	int vv=(p.x==0&&p.y==0);
	p.x=h-p.x;p.y=w-p.y;
	ll hx0,hy0,hd,hB;
	hd=exgcd(a[n].x,h,hx0,hy0);
	if(p.x%hd)return vv;
	hB=h/hd;
	hx0*=p.x/hd;hx0=(hx0%hB+hB)%hB;
	ll wx0,wy0,wd,wB;
	wd=exgcd(a[n].y,w,wx0,wy0);
	if(p.y%wd)return vv;
	wB=w/wd;
	wx0*=p.y/wd;wx0=(wx0%wB+wB)%wB;
	ll x0,y0,d,B,xy;
	if(wx0<hx0)swap(wx0,hx0),swap(hB,wB);
	xy=(wx0-hx0)%wB;
	d=exgcd(hB,wB,x0,y0);
	if(xy%d)return vv;
	B=wB/d;
	x0*=xy/d;x0=(x0%B+B)%B;
	ll u=k-hx0;if(u<0)return vv;
	u=(u/hB-x0);if(u<0)return vv;
	u/=B;
	return u+vv+(x0*hB+hx0!=0&&x0*hB+hx0<=k);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	t=read();
	while(t--){
		cin>>n>>k>>h>>w>>s;
		a[0]=(Node){0,0};
		h*=2;w*=2;
		for(int i=1;i<=n;i++){
			a[i]=forward(a[i-1],turn(s[i-1]));
			a[i].x=(a[i].x%h+h)%h;
			a[i].y=(a[i].y%w+w)%w;
		}
		ans=0;
		for(int i=1;i<=n;i++)
			ans+=solve(a[i],k-1);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1993F2)

**题目大意**

> 给定 $w\times h$ 矩形网格，以及一条长度为 $q$ 的操作序列，一个点从 $(0,0)$ 开始按操作序列向上下左右运动，当一个点超出左右边界，就翻转操作序列中的左右操作，当一个点超出上下边界，就翻转操作序列中的上下操作。
>
> 查询执行 $k$ 次操作序列后会经过多少次原点。
>
> 数据范围：$n\le 10^6$。

**思路分析**

如果遇到边界后不翻转操作，那么这个点会在无穷大网格上运动，划分成若干 $w\times h$ 的矩形区域。

如果这个点当前位置和起点左右间隔奇数个区域，那么当前经过奇数条左右边界，同理如果这个点当前位置和终点上下间隔奇数个区域，那么当前经过奇数条上下边界。

因此每个点都唯一对应原始 $w\times h$ 区域的一个点，即左右间隔奇数个区域时左右对称，上下间隔奇数个区域时上下对称。

那么对应 $(0,0)$ 的点就是所有 $(x,y)$ 满足 $2w \mid x,2h \mid y$ 的点。

因此枚举操作序列的位置，相当于求有多少个 $i<k$ 满足 $sx+i\times dx\equiv 0\pmod{2w},sy+i\times dy\equiv 0\pmod{2h}$，先简化直接关于 $i$ 的方程，然后 exgcd 求最小解和周期，即可计算 $i$ 的个数。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll exgcd(ll a,ll b,ll &x,ll &y) {
	if(!b) return x=1,y=0,a;
	ll g=exgcd(b,a%b,y,x);
	return y-=a/b*x,g;
}
ll inv(ll a,ll p) {
	ll x,y; exgcd(a,p,x,y);
	return (x%p+p)%p;
}
const int MAXN=1e6+5;
int px[MAXN],py[MAXN];
char str[MAXN];
void solve() {
	ll _,k,n,m,ans=0;
	cin>>_>>k>>m>>n>>(str+1),n*=2,m*=2;
	for(int i=1;i<=_;++i) {
		px[i]=(px[i-1]+(str[i]=='D'?n-1:str[i]=='U'))%n;
		py[i]=(py[i-1]+(str[i]=='L'?m-1:str[i]=='R'))%m;
	}
	ll dx=px[_],dy=py[_],gx=__gcd(dx,n),gy=__gcd(dy,m);
	ll p=n/gx,q=m/gy,ix=inv(dx/=gx,p),iy=inv(dy/=gy,q);
	ll u,v,d=exgcd(p,q,u,v),e=p/d*q;
	for(int i=1;i<=_;++i) {
		ll rx=(n-px[i])%n,ry=(m-py[i])%m;
		if(rx%gx||ry%gy) continue;
		rx=rx/gx*ix%p,ry=ry/gy*iy%q;
		//k mod p = rx, k mod q = ry
		if((ry-rx)%d) continue;
		ll z=q/d,s=((ry-rx)/d*u%z+z)%z,k0=s*p+rx;
		if(k0<k) ans+=(k-k0-1)/e+1;
	}
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Albert_van (赞：0)

[题](https://www.luogu.com.cn/problem/CF1993F2) [题](https://mirror.codeforces.com/contest/1993/problem/F2)。发现两维方向上的位移和修改均互相独立，于是讨论一维情况，以 $x$ 轴方向为例。既要折返又要反转操作序列，这有一种镜像的美。考虑创造一个机器人 $B$（题目中的机器人称为 $A$），它同样从 $(0,0)$ 出发跟随操作序列位移，但跨出边界不折返，且不修改操作序列，一直走下去。手动模拟知，$B$ 和 $A$ 的位置关系总是形如：

- 平移：$x_B=x_A+2kw,k\in \Z$；或者
- 镜像：$x_B=2kw-x_A,k\in \Z$。

以数学归纳证明：初始 $A$ 和 $B$ 满足平移关系；若一次操作没有使 $A$ 即将跨出边界，那么性质仍然满足；否则，对 $A$ 的操作序列将反转，平移关系会变为镜像关系（反之亦然），此时由于 $x_A=kw,k\in\{0,1\}\subseteq \Z$，易知上面性质没有被破坏。

进一步地，$w\mid x_A\Longleftrightarrow w\mid x_B$。在 $w\mid x_A$ 时，总有 $\frac {x_A}w\equiv \frac {x_B}w\pmod 2$，又 $x_A\in[0,w]$，则可以由 $x_B$ 唯一确定 $x_A$。于是
$$
x_A=0\Longleftrightarrow x_B=2kw,k\in\Z
$$
对 $y$ 同理。问题得到简化。

对 $j\in[1,n]$ 求出从 $(0,0)$ 出发，对 $B$ 进行了 $j$ 次操作后 $B$ 的位置 $(x_j,y_j)$。令操作步数 $i=an+b(i\in[1,kn],b\in[1,n])$，题目即要求满足
$$
\begin{cases}x_na+x_b\equiv 0\pmod{2w}\\y_na+y_b\equiv 0\pmod{2h}\end{cases}
$$
的 $i$ 的个数。

枚举 $b$，以上即为关于 $a$ 的不定方程组（以第一条为例，其等价于关于 $(a,u)$ 的方程 $x_na+2wu=-x_b$），解法见 [题](https://www.luogu.com.cn/problem/P5656) 或 [博客](https://www.cnblogs.com/vanspace/p/Naive-Number-Theory.html)。解方程组得
$$
\begin{cases}a\equiv r_1\pmod {m_1}\\a\equiv r_2\pmod {m_2}\end{cases}
$$
使用 [exCRT](https://www.luogu.com.cn/problem/P4777)（[博客](https://www.cnblogs.com/vanspace/p/Naive-Number-Theory.html)）合并得 $a\equiv r\pmod m$，在 $[0,k)$ 中求满足条件的 $a$ 的个数，对所有 $b$ 加和即为答案，复杂度 $\mathcal O(n \log n)$。

```cpp
#include <cstdio>
#define int long long

int g;void exgcd(int a,int b,int &x,int &y){
	if(!b) return g=a,x=1,y=0,void();
    exgcd(b,a%b,x,y);
    int t=x;x=y;y=t-a/b*y;
}

struct res{int a,m;};bool flg;

res ieq(int a,int b,int c){
    int x,y;exgcd(a,b,x,y);int m=b/g;
	if(c%g!=0){flg=1;return (res){0,0};}
    return (res){(c/g*x%m+m)%m,m};
}

int a[2],m[2];

void mrg(int i){
    int k=ieq(m[i],m[i+1],a[i+1]-a[i]).a;
    int d=m[i]/g*m[i+1];m[i+1]=d;
    a[i+1]=(((k%d+d)%d*m[i]%d+a[i])%d+d)%d;
}

const int N=1048576;

int x[N],y[N];char s[N];

signed main()
{
	int T;scanf("%lld",&T);while(T--){
		int n,k,w,h,ans=0;scanf("%lld%lld%lld%lld%s",&n,&k,&w,&h,s+1);
		w<<=1;h<<=1;--k;for(int i=1;i<=n;++i)
		x[i]=x[i-1]+(s[i]=='R'?1:(s[i]=='L'?-1:0)),
		y[i]=y[i-1]+(s[i]=='U'?1:(s[i]=='D'?-1:0));
		bool rvx=0,rvy=0;
		int xx=x[n]>0?x[n]:(rvx=1,-x[n]),
			yy=y[n]>0?y[n]:(rvy=1,-y[n]);
		for(int i=1;i<=n;++i){
			flg=0;res r=ieq(xx,w,rvx?x[i]:-x[i]%w+w);
			if(flg) continue;
			a[0]=r.a;m[0]=r.m;
			r=ieq(yy,h,rvy?y[i]:-y[i]%h+h);
			if(flg) continue;
			a[1]=r.a;m[1]=r.m;
			mrg(0);if(flg) continue;
			ans+=k/m[1]+(k%m[1]>=a[1]);
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：_Ch1F4N_ (赞：0)

首先需要一个关键结论，所谓碰壁后翻转操作序列，实际上等价于碰壁后不做改变继续操作，但是走到的所有形如 $(2 \times l_1 \times w,2 \times l_2 \times h)$ 的位置都与位置 $(0,0)$ 等价。

考虑枚举是在某次执行中的第几次操作带来的贡献，也就是时间对 $n$ 取模后的余数，我们假定这个值为 $i$。

加入已经操作了 $k$ 次，那么当前走到的点就是 $(k \times \Delta_x,k \times \Delta_y)$，这里 $\Delta x,\Delta y$ 分别表示一次执行带来的位置偏移量，令 $\delta_x,\delta_y$ 表示考虑一次执行的前 $i$ 个操作带来的位置偏移量，那么其可以产生贡献当且仅当 $k \times \Delta_x + \delta_x \bmod 2 \times w = 0$ 且 $k \times \Delta_y + \delta_y \bmod 2 \times h = 0$，解两个同余方程得到关于 $k$ 的两个同余方程，再使用扩展中国剩余定理合并同余方程即可计数。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+114;
#define int long long
int n,k;
int deltax[maxn],deltay[maxn];
int w,h;
int exgcd(int a,int b,int &x,int &y){
    //ax+by=gcd(a,b)
	bool flag=false;
	if(a<b) swap(a,b),flag=true;
    if(b==0){
        x=1;
        y=0;
		if(flag==true) swap(x,y);
        return a;
    }else{
        int k=a/b;
        int d=exgcd(b,a%b,y,x);
        y-=k*x;
		if(flag==true) swap(x,y);
        return d;
    }
}
int mul(int a,int b,int c){
	int res=0,sum=a;
	for(int i=0;i<63;i++){
		if((1ll<<i)&b) res=(res+sum)%c;
		sum=(sum+sum)%c;
	}
	return res;
}
void work(){
    int answer=0;
    cin>>n>>k>>w>>h;
    w*=2;
    h*=2;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        if(c=='L') deltax[i]=deltax[i-1]-1,deltay[i]=deltay[i-1];
        if(c=='R') deltax[i]=deltax[i-1]+1,deltay[i]=deltay[i-1];
        if(c=='U') deltax[i]=deltax[i-1],deltay[i]=deltay[i-1]+1;
        if(c=='D') deltax[i]=deltax[i-1],deltay[i]=deltay[i-1]-1;
    }
    for(int i=1;i<=n;i++){
        if(deltax[i]<0) deltax[i]=(deltax[i]+n*w)%w;
        if(deltay[i]<0) deltay[i]=(deltay[i]+n*h)%h;
        if(deltax[i]>0) deltax[i]%=w;
        if(deltay[i]>0) deltay[i]%=h;
        if(deltax[i]==0) deltax[i]+=w;
        if(deltay[i]==0) deltay[i]+=h;
    }
    for(int i=1;i<=n;i++){
        //横坐标限制
        //k'*deltax[n] = (2*w)*y-detlax[i]
        int a=deltax[n],b=w,c=(w-deltax[i])%w;
        if(c%__gcd(a,b)!=0) continue;
        int x0=0,y0=0;
        exgcd(a,b,x0,y0);
        x0*=c/__gcd(a,b);
        y0*=c/__gcd(a,b);
        int stx=b/__gcd(a,b);
        int sty=a/__gcd(a,b);
        x0%=stx;
        //k'=x0+stx*L
        int M=stx,ans=x0;
        //纵坐标限制
        //k'*deltay[n] = (2*h)*y'-detlay[i]
        int A=deltay[n],B=h,C=(h-deltay[i])%h;
        if(C%__gcd(A,B)!=0) continue;
        int X0=0,Y0=0;
        exgcd(A,B,X0,Y0);
        X0*=C/__gcd(A,B);
        Y0*=C/__gcd(A,B);
        int stX=B/__gcd(A,B);
        int stY=A/__gcd(A,B);
        X0%=stX;
        //k'=X0+stX*L'
        //cout<<i<<' '<<x0<<' '<<stx<<' '<<X0<<' '<<stX<<'\n';
        int cc=((X0-ans)%stX+stX)%stX;
        int x=0,y=0;
        if(cc%__gcd(M,stX)!=0) continue;
		int g=exgcd(M,stX,x,y);
        int p=stX/g;
        x=mul(x,cc/g,p);
        ans+=x*M;
        M*=p;
        ans=(ans%M+M)%M;
        //cout<<ans<<' '<<M<<'\n';
        //k=L*M+ans;
        //L*M+ans<K
        if(k<ans) continue;
        answer+=(k-ans)/M+1-((k-ans)%M==0?1:0);
    }
    cout<<answer<<'\n';
}
signed main(){
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
5 6 3 3
RUURD
*/

```

---

## 作者：Computer1828 (赞：0)

考虑通过类似**镜像**的方式解决脚本的修改。

举个例子，假如机器人 A 站在矩形右边界执行操作 `R`，那么它事实上会往左边走一步。但是如果我们把矩形右边界看成镜子，那么机器人的镜像 B 会往右边走一步。

撞到右边界后，A 会修改脚本。接下来考虑在什么时候 A 会撞到左边界，显然是当 B 的横坐标是 $2w$ 的时候。考察 B 从 A 撞右边界到 A 撞左边界的移动，会发现：B 执行的是**未修改的脚本**。

更进一步地，**如果 B 是一个从未修改过脚本的机器人（也就是它无视边界按初使脚本运动），那么当它所处的位置的横坐标 $x'$ 满足 $x'\equiv 0\pmod{2w}$ 的时候，真正的机器人 A 就会在 $x=0$ 上。**

这个镜像的想法有点像平抛运动题（球平抛入井，碰壁则水平方向速度反向）：

![](https://cdn.luogu.com.cn/upload/image_hosting/tbmfw886.png)

当然，以上思考可以拓展到矩形的每个边界。

于是我们设 $(x_i,y_i)$ 表示那个无视边界无视脚本修改的机器人 B，执行了 $i$ 个命令后所处的位置。根据以上讨论，当 $x_i \equiv 0\pmod{2w}$ 且 $y_i \equiv 0\pmod{2h}$ 的时候，真正的机器人 A 会回到原点。

与此同时，我们知道，如果设 $i = tn+j(t\in\{0,1,2,\cdots,k-1\},j\in\{1,2,3,\cdots,n\})$，那么 $x_i = tx_n+x_j,y_i = ty_n+y_j$。

结合以上两式，进行一些移项，我们得到：

$$x_nt\equiv-x_j\pmod{2w}$$

$$y_nt\equiv-y_j\pmod{2h}$$

枚举 $j$，问题转化为求关于未知数 $t$ 的同余方程组当 $t\in\{0,1,2,\cdots,k-1\}$ 的时候有多少解。

用中国剩余定理即可求解。

[我自己写的又丑又长的代码](https://codeforces.com/contest/1993/submission/275042157)。

---

