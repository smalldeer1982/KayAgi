# Hot and Cold

## 题目描述

This is an interactive problem.

After emigrating to another country, little Hanna came across the fact that playing "Hot and cold" became more difficult: she does not understand the hint phrases! You are to write a helping program for her.

The playground where the game happens is a rectangle, and the treasure is hidden in some point with integer coordinates between 0 and $ 10^6 $ , inclusive. Hanna visits several points with valid coordinates. If the visited point contains the hidden treasure, she receives the phrase "Found!" in the local language. Fortunately, the intonations allow her to recognize this phrase — in this problem it will be denoted by an exclamation mark.

Otherwise, for each visited point except for the first one, Hanna receives a phrase in the local language stating whether she is now "Closer", "Further", or "At the same distance" from the treasure, compared to the previous point. The distances are measured in Euclidean metric. After the first visited point, in case of no treasure there, Hanna receives the phrase "Not found" in the local language.

Your program must help Hanna find the treasure by visiting at most 64 points.

## 样例 #1

### 输入

```
Tabilmadi

Daha yakin

Daha yakin

Sama distanco

Dalej

Znaydeno!```

### 输出

```
500 200

560 230

566 240

566 238

30 239

566 239```

## 样例 #2

### 输入

```
You are lucky today!```

### 输出

```
777777 777777```

# 题解

## 作者：rui_er (赞：3)

赛时跟队友一起摆烂了，于是没做出来，回来补题。

如果询问到了答案，可以直接判断并退出，因此下文的询问过程并没有考虑这一点。

显然“$(1,1)$ 比 $(0,0)$ 离所求位置更近”对于几乎所有点成立，因此我们可以依次询问 $(0,0),(1,1),(0,0)$，忽略第一次的回答，则后两次回答分别对应 `Closer` 和 `Further`，记为 $c$ 和 $f$。我们说“几乎所有点”，因为存在两个反例 $(0,1),(1,0)$。容易发现反例情况 $c=f$（因为其实都对应 `At the same distance`），此时把两种情况都问一下即可得到答案。

通过以上过程，我们排除了平凡情况，并确定了 $c$ 和 $f$。考虑二分，设所求位置在 $(x_l,y_l)\sim(x_r,y_r)$ 的子矩形中，求出中点 $(x_m,y_m)$，依次询问 $(x_m,y_m),(x_m+1,y_m),(x_m+1,y_m+1)$，忽略第一次的回答，则后两次的回答分别可以使 $x$ 和 $y$ 的范围减半。于是我们可以在 $3\lceil\log_210^6\rceil+4=64$ 次询问内确定所求点。

有两点需要注意：

- 可以发现询问次数上限卡得很紧，要精细实现不要写丑多询问。
- 需要特判当 $x_m$ 或 $y_m$ 恰好等于 $10^6$ 的情况，此时会涉及到坐标 $10^6+1$ 从而导致不合法询问。

```cpp
// Problem: CF1773H Hot and Cold
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1773H
// Memory Limit: 1000 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

string c, f;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
string ask(int x, int y) {
	printf("%d %d\n", x, y);
	fflush(stdout);
	string res;
	getline(cin, res);
	return res;
}
bool success(string s) {
	return s.find('!') != string::npos;
}

int main() {
	if(success(ask(0, 0))) return 0;
	if(success(c = ask(1, 1))) return 0;
	if(success(f = ask(0, 0))) return 0;
	if(c == f) return assert(success(ask(0, 1)) || success(ask(1, 0))),0;
	int xl = 0, xr = 1000001, yl = 0, yr = 1000001;
	while(xl < xr || yl < yr) {
		int xm = (xl + xr) >> 1, ym = (yl + yr) >> 1;
		string res1, res2;
		if(success(ask(xm, ym))) return 0;
		if(xm == 1000000 && ym == 1000000) res1 = res2 = f;
		else if(xm == 1000000) {
			res1 = f;
			if(success(res2 = ask(xm, ym+1))) return 0;
		}
		else if(ym == 1000000) {
			if(success(res1 = ask(xm+1, ym))) return 0;
			res2 = f;
		}
		else {
			if(success(res1 = ask(xm+1, ym))) return 0;
			if(success(res2 = ask(xm+1, ym+1))) return 0;
		}
		if(res1 == c) xl = xm + 1;
		else xr = xm;
		if(res2 == c) yl = ym + 1;
		else yr = ym;
	}
	assert(success(ask(xl, yl)));
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

考虑信息的本质。

设上一次询问 $(ax, ay)$，本次询问 $(x, y)$，它们连线段的垂直平分线为 $l$。若返回 `Closer`，则答案在 $l$ 包含 $(x, y)$ 一侧的半平面内。若返回 `Further`，则答案在 $l$ 包含 $(ax, ay)$ 一侧的半平面内。若返回 `At the same distance`，则答案在 $l$ 上。

我们肯定要尽快确定 `Closer` 和 `Further` 的短语 $c, f$。可以想到询问 $(0, 0)$ 后再询问 $(1, 1)$，则当且仅当答案为 $(1, 0)$ 和 $(0, 1)$ 时 $c$ 不为返回值，可以直接枚举。接下来询问 $(1, 1)$ 后再询问 $(0, 0)$，得到返回值为 $f$。我们用了 $6$ 次询问得到 $c, f$。实际上可以更优，但已经足够了：询问 $(0, 0)$，询问 $(1, 1)$，返回值作为 $c$，询问 $(0, 0)$，返回值作为 $f$。若 $c = f$ 说明答案为 $(0, 1)$ 或 $(1, 0)$。这样只需要 $3$ 次询问。

考虑二分横坐标 $x$。

设上一次询问 $(l, 0)$，本次询问 $(r, 0)$。若返回 $c$，说明 $2x > l + r$。若返回 $f$，说明 $2x < l + r$。否则，$2x = l + r$。这样，我们可以用两次询问确定 $x$ 在 $\frac {l + r} 2$ 左侧还是右侧。

加上纵坐标，总询问次数为 $4\lceil\log_2 V\rceil$，无法接受。但注意到我们的第一次询问总没有产生任何信息，很浪费，能不能利用起来呢？

设上一次询问 $(p, 0)$，当前区间为 $[l, r]$。注意 $p$ 不一定等于 $l, r$。设 $m = \lfloor\frac {l + r} 2\rfloor$，则询问 $(2m - p, 0)$ 即可直接确定。问题在于 $2m - p$ 不一定符合 $[0, 10 ^ 6]$ 的限制，且 $p$ 可能等于 $m$。没关系，我们只需令 $p = m - 1$ 或 $m + 1$ 先询问一次即可。这样的情况发生的次数很少，大部分时候 $p$ 在 $m$ 附近震荡，读者可以想象一下。感性理解当坐标靠近边界时询问次数会稍微多一点，但依然可以接受。

官方正解应该是将横坐标和纵坐标放在一起二分，这样只需要 $3\lceil\log_2 V\rceil$ 次询问。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e6;
bool debug;
int Q, ax = -1, ay = -1, bx, by;
ll dis(int x, int y) {return 1ll * (x - bx) * (x - bx) + 1ll * (y - by) * (y - by);}
bool ill(int x) {return x < 0 || x > N;}
string clo, fur;
string query(int x, int y) {
  assert(++Q <= 64 && 0 <= x && x <= N && 0 <= y && y <= N);
  cout << x << " " << y << endl;
  string res;
  if(debug) {
    if(x == bx && y == by) cout << "Found!\nQuery count: " << Q << endl, exit(0);
    if(ax == -1) res = "Not found";
    else if(dis(ax, ay) < dis(x, y)) res = "Further";
    else if(dis(ax, ay) > dis(x, y)) res = "Closer";
    else res = "At the same distance";
    ax = x, ay = y;
  }
  else {
    getline(cin, res);
    if(res.find('!') != -1) exit(0);
  }
  return res;
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
    debug = true;
  #endif
  if(debug) cin >> bx >> by;
  query(0, 0), clo = query(1, 1), fur = query(0, 0);
  if(clo == fur) query(1, 0), query(0, 1);
  if(debug) cout << "Closer: " << clo << " Further: " << fur << "\n";

  int lx = 0, rx = N, lst = -1;
  while(lx < rx) {
    int m = max(1, lx + rx >> 1);
    if(lst == -1 || lst == m || ill(2 * m - lst))
      query(lst = m * 2 > N ? m - 1 : m + 1, 0);
    string res = query(lst = 2 * m - lst, 0);
    if(res == clo) {
      if(lst < m) rx = m - 1;
      else lx = m + 1;
    }
    else if(res == fur) {
      if(lst < m) lx = m + 1;
      else rx = m - 1;
    }
    else lx = rx = m;
  }

  int ly = 0, ry = N; lst = -1;
  while(ly < ry) {
    int m = max(1, ly + ry >> 1);
    if(lst == -1 || lst == m || ill(2 * m - lst))
      query(lx, lst = m * 2 > N ? m - 1 : m + 1);
    string res = query(lx, lst = 2 * m - lst);
    if(res == clo) {
      if(lst < m) ry = m - 1;
      else ly = m + 1;
    }
    else if(res == fur) {
      if(lst < m) ly = m + 1;
      else ry = m - 1;
    }
    else ly = ry = m;
  }
  query(lx, ly);
  if(debug) cout << "Oops! Not found!\n";
  return 0;
}
/*
g++ H.cpp -o H -std=c++14 -O2 -DALEX_WEI
*/
```

---

