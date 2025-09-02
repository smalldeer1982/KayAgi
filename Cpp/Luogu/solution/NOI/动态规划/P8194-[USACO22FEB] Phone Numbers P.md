# [USACO22FEB] Phone Numbers P

## 题目描述

Bessie 获得了一个九键的新手机，键位如下所示：

```
123
456
789
```

Bessie 正在匆忙中尝试打出一个给定的电话号码，所以她决定通过用她的其中一个蹄子一次按下多个按钮的方式来节省时间。具体来说，Bessie 的蹄子可能按下一个键，两个共用一条边的键（总共有 $12$ 种可能），或者形成一个正方形的四个键（$1245$，$2356$，$4578$，$5689$）

例如，如果 Bessie 要打的电话号码是 $123659874$，她可能通过如下方法按键来尝试节省时间：

1. 同时按下 $1$ 和 $2$。
2. 按下 $3$。
3. 同时按下 $6,5,9,8$。
4. 同时按下 $7$ 和 $4$。

不幸的是，Bessie 大大高估了她执行这项任务的技能——如果 Bessie 的蹄子同时按下多个按键，那么所有这些按键会以任意顺序输入。所以如果 Bessie 尝试按上述按键顺序，结束时她输入的电话号码可能是 $123596847$ 或 $213659874$（或者其他可能的序列）。

给定一个 Bessie 已经输入的序列，请计算她可能想输入的电话号码的数量对 $10^9+7$ 取模后的值。

## 说明/提示

**【样例解释】**

对于第一组数据。Bessie 可能想输入如下五个电话号码之一：

```plain
1478
1487
4178
4187
1748
```

例如，如果 Bessie 想输入 $4187$，她可能会尝试同时按下 $1$ 和 $4$，然后同时按下 $7$ 和 $8$。

对于第三组数据，因为这些数字组成了一个正方形，Bessie 可能想输入的电话是输入序列的任何排列。

**【数据范围】**

- 对于第 $2\sim 3$ 组数据，所有电话号码的长度最多为 $8$。
- 对于第 $4\sim 5$ 组数据，电话号码只包含 $1,2$ 和 $3$。
- 对于第 $6\sim 7$ 组数据，电话号码不包含 $5$。
- 对于第 $8\sim 9$ 组数据，电话号码只包含 $5,6,8,9$。
- 对于第 $10\sim 12$ 组数据，电话号码总长度不超过 $10^2$。
- 对于第 $13\sim 15$ 组数据，电话号码总长度不超过 $10^3$。
- 对于第 $16\sim 18$ 组数据，电话号码总长度不超过 $10^4$。
- 对于第 $19\sim 21$ 组数据，无附加限制。

## 样例 #1

### 输入

```
5
1478
4455
5968
31313211
123659874```

### 输出

```
5
2
24
3
255```

# 题解

## 作者：panyf (赞：15)

考虑从前到后 dp。当前 dp 了长度为 $i$ 的前缀，记 $f_{u_1,u_2,u_3,v_0,v_1,v_2,v_3}$ 表示第 $i-2$ 位为 $u_1$，第 $i-1$ 位为 $u_2$，第 $i$ 位为 $u_3$,长度为 $i-3$ 的前缀能否匹配（$v_0=1$ 表示能匹配，$v_0=0$ 表示不能），$i-2$ 能否匹配，$i-1$ 能否匹配，$i$ 能否匹配。转移时枚举第 $i+1$ 位的值，判断 $[i-2,i+1],[i,i+1],[i+1,i+1]$ 这三个区间能否匹配。时间复杂度 $O(n)$。

算一下这个做法的常数，状态数 $2^4\times 9^3$，转移数 $9$。显然 TLE。

考虑优化。首先容易发现若 $v_0=0$，那么 $u_1$ 就没用了，就不用记录了。若 $v_0=v_1=0$，那么 $u_2$ 也就没用了。若 $v_0=v_1=v_2=0$，那么 $u_3$ 也就没用了，若 $v_0=v_1=v_2=v_3=0$，那么这个状态不合法。但是 $v_0=1$ 的时候还是要记 $u_1,u_2,u_3$，状态数只减少了不到一半。

若 $v_0=1$，但是 $u_1,u_2,u_3$ 再加上任何一个数，都不能和 $[i-2,i+1]$ 匹配上，那么可以把 $v_0$ 改成 $0$。或者如果 $[i-2,i+1]$ 的数不在一个正方形内，也可以把 $v_0$ 改成 $0$。同理 $v_1,v_2$ 也可以这样做。

加上这两个优化以后，再分析一下状态数。若 $v_0=1$，那么 $u_1,u_2,u_3$ 一定是从数字串的区间 $[i-2,i+1]$ 中选出三个数，有 $24$ 种方案，并且 $v_1$ 一定等于 $0$（因为），$v_2,v_3$ 不确定，有 $4\times 24=96$ 种方案。若 $v_0=0,v_1=1$，则 $u_2,u_3$ 一定是 $[i-1,i+2]$ 中选出的两个数，有 $12$ 种方案，$v_2,v_3$ 不确定，有 $4\times 12=48$ 种方案。若 $v_0=v_1=0,v_2=1$，有 $2\times 4=8$ 种方案。若 $v_0=v_1=v_2=0,v_3=1$，有 $1$ 种方案。总状态数就是 $96+48+8+1=153$。实际上跑不满，按照官方题解的说法数据中状态不超过 $50$。可以写一个哈希表压缩状态。

$10\times 100000\times 153\times 9\approx 1.4\times 10^9$，然后时限 $4s$，就过了。

---

## 作者：happybob (赞：1)

如果给定了想输入的序列，怎么判定合法？显然是一个 DP，考虑 $f_i$ 表示前 $i$ 个是否可以完全匹配。$f_i$ 从 $f_{i-1},f_{i-2},f_{i-4}$ 转移而来。需要判定数字可重集是否相等。

考虑原计数问题，将判定性问题的值作为状态。具体地，记 $f_{i,a,b,c,0/1,0/1,0/1,0/1}$ 表示前 $i$ 个字符，倒数三个分别是 $a,b,c$，目前 $[1,i-3],[1,i-2],[1,i-1],[1,i]$ 能否恰好完全匹配。转移枚举 $i+1$ 的数字是什么即可。

这个复杂度已经达到了 $O(n)$，不能再低了。但是状态数上的常数有点大。具体来说是 $9^3 \times 2^4$ 这么多。估计不太可过。考虑一些可以合并的状态。

设 $i+1$ 位的数字为 $d$。注意到 $a$ 的作用仅在于 $a,b,c,d$ 四个一起合并。若 $[1,i-3]$ 无法恰好匹配，那么 $a$ 无论是多少答案都一样，直接合并。同样若 $[1,i-3]$ 与 $[1,i-2]$ 都无法完全匹配。$b$ 也是可以合并的。同理，$c$ 和 $d$ 也是这样。

进一步，我们发现若 $a,b,c$ 不同时在题面中要求的四个连通块中，那么 $a$ 也没有意义。同理，若 $b,c$ 不在一起，$b$ 也没有意义。这样大部分状态都被合并了。

这么写一下发现最高状态数大概是 $150$ 的样子，已经可以通过了。不推荐使用 `unordered_map` 代替 DP 数组，常数过大。空间开不下可以考虑滚动数组。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <climits>
#include <queue>
#include <map>
#include <set>
#include <random>
#include <unordered_map>
using namespace std;

using ll = int;
using ull = unsigned long long;

const int N = 1e5 + 5;
const ll MOD = 1e9 + 7;

int t, n;
string s;
hash<int> hsi;
hash<bool> hsb;
int R1 = 6172, R2 = 38182, R3 = 192838, R4 = 91922;

mt19937 rnd(114514);
uniform_int_distribution<ull> rg(1, ULLONG_MAX);

struct State
{
	int a, b, c;
	bool d, e, f, g;
	State() = default;
	State(int a, int b, int c, bool d, bool e, bool f, bool g)
		: a(a), b(b), c(c), d(d), e(e), f(f), g(g)
	{
	}
	bool operator==(const State& other) const
	{
		return a == other.a && b == other.b && c == other.c && d == other.d && e == other.e && f == other.f && g == other.g;
	}
};

struct MyHash
{
	size_t operator()(const State& x) const
	{
		return hsi(x.a) ^ hsi(x.b) ^ hsi(x.c) ^ hsb(x.d) * R1 ^ hsb(x.e) * R2 ^ hsb(x.f) * R3 ^ hsb(x.g) * R4;
	}
};

ll f[10][10][10][2][2][2][2], g[10][10][10][2][2][2][2];
ull wv[10];

inline bool check4(int a, int b, int c, int d)
{
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (a > d) swap(a, d);
	if (b > c) swap(b, c);
	if (b > d) swap(b, d);
	if (c > d) swap(c, d);
	if (a == 1 && b == 2 && c == 4 && d == 5) return 1;
	else if (a == 2 && b == 3 && c == 5 && d == 6) return 1;
	else if (a == 4 && b == 5 && c == 7 && d == 8) return 1;
	else if (a == 5 && b == 6 && c == 8 && d == 9) return 1;
	return 0;
}

inline bool check2(int a, int b)
{
	if (a > b) swap(a, b);
	if (b == a + 1 && (a % 3)) return 1;
	if (b - a == 3) return 1;
	return 0;
}

bool ok[10][10][10];
bool ok2[10][10];
inline bool check4_2(int a, int b)
{
	if (a > b) swap(a, b);
	return ok2[a][b];
}

inline bool check4_3(int a, int b, int c)
{
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);
	return ok[a][b][c];
}

inline State trans(State x)
{
	if (!check4_3(x.a, x.b, x.c)) x.a = x.d = 0;
	if (!check4_2(x.b, x.c)) x.b = x.e = 0;
	if (!x.d) x.a = 0;
	if (!x.d && !x.e) x.b = 0;
	if (!x.d && !x.e && !x.f) x.c = 0;
	if (!x.d && !x.e && !x.f && !x.g) x.a = x.b = x.c = 0;
	return x;
}

ull ss[N];

inline bool chk(int l, int r, ull sum)
{
	if (l <= 0 || r > n) return 0;
	return ss[r] - ss[l - 1] == sum;
}

bool vis[10][10][10][2][2][2][2];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	ok[1][2][4] = ok[1][2][5] = ok[2][4][5] = ok[1][4][5] = ok[2][3][5] = ok[2][3][6] = ok[2][5][6] = ok[3][5][6] = 1;
	ok[4][5][7] = ok[4][5][8] = ok[4][7][8] = ok[5][7][8] = 1;
	ok[5][6][8] = ok[5][6][9] = ok[5][8][9] = ok[6][8][9] = 1;
	ok2[1][2] = ok2[1][4] = ok2[1][5] = ok2[2][4] = ok2[2][5] = ok2[4][5] = 1;
	ok2[2][3] = ok2[2][5] = ok2[2][6] = ok2[3][5] = ok2[3][6] = ok2[5][6] = 1;
	ok2[4][5] = ok2[4][7] = ok2[4][8] = ok2[5][7] = ok2[5][8] = ok2[7][8] = 1;
	ok2[5][6] = ok2[5][8] = ok2[5][9] = ok2[6][8] = ok2[8][9] = ok2[6][9] = 1;
	for (int i = 0; i <= 9; i++) wv[i] = rg(rnd);
	cin >> t;
	while (t--)
	{
		cin >> s;
		n = s.size();
		s = " " + s;
		vector<State> all;
		f[0][0][0][1][1][1][1] = 1;
		all.emplace_back(0, 0, 0, 1, 1, 1, 1);
		for (int i = 1; i <= n; i++) ss[i] = ss[i - 1] + wv[s[i] - '0'];
		//int res = 0;
		for (int i = 0; i < n; i++)
		{
			vector<State> nse;
			for (auto& x : all)
			{
				auto& [a, b, c, d, e, f, g] = x;
				if (!d && !e && !f && !g) continue;
				for (int na = 0; na <= 9; na++)
				{
					State ns;
					ns.a = b, ns.b = c, ns.c = na;
					ns.d = e, ns.e = f, ns.f = g;
					ns.g = (d && check4(a, b, c, na) && chk(i - 2, i + 1, wv[a] + wv[b] + wv[c] + wv[na])) || (f && check2(c, na) && chk(i, i + 1, wv[c] + wv[na])) || (g && na == s[i + 1] - '0');
					//cout << "!!!: " << i + 1 << " " << ns.a << " " << ns.b << " " << ns.c << " " << ns.d << " " << ns.e << " " << ns.f << " " << ns.g << "\n";
					//cout << "na: " << na << " " << s[i + 1] - '0' << "\n";
					//cout << "!!!!!!!: " << (ns.g && na == s[i + 1] - '0') << "\n";
					//system("pause");
					ns = trans(ns);
					if (!vis[ns.a][ns.b][ns.c][ns.d][ns.e][ns.f][ns.g])
					{
						nse.emplace_back(ns);
						vis[ns.a][ns.b][ns.c][ns.d][ns.e][ns.f][ns.g] = 1;
					}
					::g[ns.a][ns.b][ns.c][ns.d][ns.e][ns.f][ns.g] = (::g[ns.a][ns.b][ns.c][ns.d][ns.e][ns.f][ns.g] + ::f[a][b][c][d][e][f][g]) % MOD;
				}
			}
			for (auto& [a, b, c, d, e, ff, g] : all) f[a][b][c][d][e][ff][g] = 0ll;
			for (auto& [a, b, c, d, e, f, gg] : nse) ::f[a][b][c][d][e][f][gg] = g[a][b][c][d][e][f][gg], vis[a][b][c][d][e][f][gg] = 0, g[a][b][c][d][e][f][gg] = 0;
			all.swap(nse);
		}
		ll ans = 0ll;
		for (auto& x : all)
		{
			if (x.g) ans = (ans + f[x.a][x.b][x.c][x.d][x.e][x.f][x.g]) % MOD;
			f[x.a][x.b][x.c][x.d][x.e][x.f][x.g] = 0;
		}
		//cout << "max_state: " << res << "\n";
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：qiuzx (赞：0)

## 题意

有一个九键手机，一次可以同时按一个，相邻两个，或一圈四个键，但同时按的时候显示的顺序是随意的。给定打出来的数字串 $s$，求有多少种可能的本来想打的数字串，模 $10^9+7$。$|s|\le 10^5$。

## 思路

考虑判定一个 $t$ 是否合法，容易想到 $dp_i$ 表示长度为 $i$ 的前缀是否合法。则若 $t_i=s_i$，那么 $f_{i-1}\to f_i$，若 $\{t_{i-1},t_i\}=\{s_{i-1},s_i\}$ 且这两个字符相邻，则 $f_{i-2}\to f_i$，四个的转移也是同理。回到这个计数问题，由于字符集不大，可以想到 dp 套 dp。具体来说，记 $(i,t_{i-2},t_{i-1},t_i,f_{i-3},f_{i-2},f_{i-1},f_i)$ 为一个状态，其含义显然，则确定了 $t_{i+1}$ 之后就有唯一的下一个状态。然而这个状态数是 $O(n\times 9^3\times 2^4)$，转移有 $9$ 种，不能通过。

看起来没有什么从复杂度上能做的优化了，所以考虑从常数上做一些优化。首先若这四个值都是 $0$ 则显然没用了。类似地还可以去掉一些显然不会导致后面合法的状态。然后感觉上这个就是跑不满的，所以可以开桶只记录存在的状态，这样可以发现能够获得很高的分数，但还是不足够。

然而我们发现还有一个显然的优化没有做，就是枚举的转移边字符如果根本没有在 $s$ 的对应范围内出现，那么这次转移显然是无效的。一次转移的有效范围至多是 $7$ 个字符，所以至少有一个 $\frac 79$ 的常数。且如果这 $7$ 个字符全部不同，那么放法实际上几乎是唯一的，所以可能存在的有效状态很少。加上这个优化之后打一个表可以发现状态数不超过 $200$，因此可以通过。

[代码](https://www.luogu.com.cn/paste/bvx7lqin)

---

## 作者：Petit_Souris (赞：0)

卡常大赛。

首先考虑怎么判定一个串是否合法，显然可以线性 dp。由于每次转移的串长只可能是 $1,2,4$，这启发我们 dp 套 dp，直接把前面三位是什么以及前面四位的 dp 值记下来。

即设 $f_{i,a,b,c,x,y,z,w}$ 表示考虑长度为 $i$ 的前缀，第 $i-2$ 位为 $a$，第 $i-1$ 位为 $b$，第 $i$ 位为 $c$，$dp_{i-3}=x,dp_{i-2}=y,dp_{i-1}=z,dp_{i}=w$，转移显然，请读者自行思考。

时间复杂度 $\mathcal O(n)$，然而常数为状态数 $9^3\times 2^4$ 乘上转移数 $9$，无法通过。~~致敬传奇线性过不了 $10^4$。~~

考虑压缩状态。

第一个优化是，观察到，当 $x=0$ 时，不会转移 $[i-2,i+1]$ 这段了，因此 $a$ 是多少根本不重要，可以把所有的不同的 $a$ 压缩成一个状态；$x=y=0$ 时压缩 $b$，$x=y=z=0$ 时压缩 $c$，$x=y=z=w=0$ 时直接把这个状态删了，因为已经不合法了。

第二个优化是，当 $a,b,c$ 已经不可能在一个正方形内的时候，$a$ 就没用了，也可以压缩掉 $a$ 和 $x$，同理可以压缩 $b$ 和 $y$。

这样状态就压缩到一个比较小的数量级了，大约在 $200$ 以内。

直接做还有被卡常的可能性。我们还可以优化转移，因为只可能转移 $[i-3,i+3]$ 中的元素，所以可以乘上一个 $\frac{7}{9}$ 的常数。

实现的时候要把所有状态压成一个数，这样常数更小。这样差不多就能通过了。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int N=1e5+9,Mod=1e9+7;
int T,n,a[N];
char s[N];
bool chk2(array<int,2> a){
    sort(a.begin(),a.end());
    if(a[0]+3==a[1])return 1;
    if(a[0]+1==a[1]){
        if(a[0]!=3&&a[0]!=6)return 1;
    }
    return 0;
}
bool chk4(array<int,4> a){
    sort(a.begin(),a.end());
    if(a[0]==1&&a[1]==2&&a[2]==4&&a[3]==5)return 1;
    if(a[0]==2&&a[1]==3&&a[2]==5&&a[3]==6)return 1;
    if(a[0]==4&&a[1]==5&&a[2]==7&&a[3]==8)return 1;
    if(a[0]==5&&a[1]==6&&a[2]==8&&a[3]==9)return 1;
    return 0;
}
bool equ(vector<int>a,vector<int>b){
    sort(a.begin(),a.end()),sort(b.begin(),b.end());
    return a==b;
}
void Upd(int&x,int y){
    x+=y;
    if(x>=Mod)x-=Mod;
}
const int B=1400;
int f[2][16005],cur,tot;
vector<int>S;
bool vis[16005],ck2[N],ck4[N];
bool good1[10][10][10],good2[10][10];
int H(int x,int y,int z,int a,int b,int c,int d){
    return x*1600+y*160+z*16+a*8+b*4+c*2+d;
}
mt19937 rnd(time(0));
void solve(){
    scanf("%s",s+1),n=strlen(s+1);
    rep(i,1,n)a[i]=s[i]-'0';
    memset(f,0,sizeof(f)),cur=0;
    memset(vis,0,sizeof(vis));
    f[0][1]=1;
    S.push_back(1);
    rep(i,0,n+1)ck2[i]=ck4[i]=0;
    rep(i,2,n)ck2[i]=chk2({a[i-1],a[i]});
    rep(i,4,n)ck4[i]=chk4({a[i-3],a[i-2],a[i-1],a[i]});
    rep(i,1,n){
        memset(f[cur^1],0,sizeof(f[cur^1]));
        vector<int>nS;
        for(int s:S)vis[s]=0;
        vector<int>trs;
        rep(j,max(1,i-3),min(n,i+3))trs.push_back(a[j]);
        sort(trs.begin(),trs.end());
        trs.resize(unique(trs.begin(),trs.end())-trs.begin());
        for(int s:S){
            int a3=(s>>4)/100,a2=(s>>4)/10%10,a1=(s>>4)%10,f3=(s>>3)&1,f2=(s>>2)&1,f1=(s>>1)&1,f0=s&1;
            int val=f[cur][s];
            for(int a0:trs){
                int nf=0;
                if(a[i]==a0)nf|=f0;
                if(!nf){
                    if(i>1&&ck2[i]&&equ({a[i-1],a[i]},{a1,a0}))nf|=f1;
                    if(!nf){
                        if(i>3&&ck4[i]&&equ({a[i-3],a[i-2],a[i-1],a[i]},{a3,a2,a1,a0}))nf|=f3;
                    }
                }
                if(f2+f1+f0+nf==0)continue;
                int na2=a2,na1=a1,na0=a0,nf2=f2,nf1=f1;
                if(!f2)na2=0;
                if(!f2&&!f1)na1=0;
                if(!f2&&!f1&&!f0)na0=0;
                if(!good1[na2][na1][na0])na2=0,nf2=0;
                if(!good2[na1][na0])na1=0,nf1=0;
                int nH=H(na2,na1,na0,nf2,nf1,f0,nf);
                if(!vis[nH])vis[nH]=1,nS.push_back(nH);
                Upd(f[cur^1][nH],val);
            }
            f[cur][s]=0;
        }
        S=nS;
        cur^=1;
    }
    int ans=0;
    for(int s:S){
        if(s&1)Upd(ans,f[cur][s]);
    }
    write(ans),putchar('\n');
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    rep(i,0,9){
        rep(j,0,9){
            rep(k,0,9){
                rep(l,0,9){
                    if(chk4({i,j,k,l}))good1[i][j][k]=good2[i][j]=1;
                }
            }
        }
    }
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

