# Climbing the Tree

## 题目描述

蜗牛在爬树。树高为 $ h $ 米，每只蜗牛从 $ 0 $ 米高处开始爬。

每只蜗牛有两个属性 $ a $ 与 $ b \text{ } ( a > b ) $。从第 $ 1 $ 天开始，每只蜗牛会以以下方式爬树：在白天，蜗牛向上爬 $ a $ 米； 在晚上，蜗牛会休息，而它每晚会向下滑 $ b $ 米。如果在第 $ n $ 天，蜗牛首次到达第 $ h $ 米的高度（也就是树顶），它就会结束爬行，此时我们称此蜗牛花了 $ n $ 天来爬树。注意，在最后一天，只要蜗牛离树顶的高度小于 $ a $ 米，它就不需要正好再向上爬 $ a $ 米。

起初，你并不知道树高 $ h $，你只知道 $ h $ 是一个正整数。接下来会发生以下两种类型的事件，事件件数总和为 $ q $。

- 事件 $ 1 $：有一只属性为 $ a $， $ b $ 的蜗牛声称它花了 $ n $ 天来爬树。如果这条信息与之前的已知信息有冲突（即根据之前信息确定的树高范围与当前信息所确定的树高范围有冲突），则忽略该信息，否则采纳该信息。

- 事件 $ 2 $：有一只属性为 $ a $， $ b $ 的蜗牛前来询问你它需要花几天来爬树。你只能根据当前你已采纳的信息来推测答案。如果仅根据已有信息无法给出精确的答案，则回答 $ -1 $。

你需要按顺序处理所有事件。




保证单个测试点内 $ q $ 的总和不超过 $ 2 \times 10 ^ 5 $。

## 说明/提示

在第一个测试样例中，我们可以从第一条信息确定 $ h = 7 $，所有我们可以知道第二条蜗牛和第三条蜗牛各自需要 $ 2 $ 天和 $ 5 $ 天来爬树。

对于第一个样例中的第二只蜗牛，有：

- 在第 $ 1 $ 天的白天：这只蜗牛向上爬了 $ 4 $ 米，现在它在 $ 4 $ 米高处。
- 在第 $ 1 $ 天的晚上：这只蜗牛向下滑了 $ 1 $ 米，现在它在 $ 3 $ 米高处。
- 在第 $ 2 $ 天的白天：这只蜗牛向上爬了 $ 4 $ 米，现在它在 $ 7 $ 米高处（即爬到树顶）。

在第三个测试样例中，第二只蜗牛的信息与第一只蜗牛的信息有冲突，因为第二支蜗牛说它花了 $ 3 $ 天爬树，而它在前 $ 3 $ 天最多可以爬 $ 1 + 1 + 2 = 4 $ 米，而第一只蜗牛只需要花 $ 1 $ 天就能爬 $ 4 $ 米。

## 样例 #1

### 输入

```
5
3
1 3 2 5
2 4 1
2 3 2
3
1 6 5 1
2 3 1
2 6 2
3
1 4 2 2
1 2 1 3
2 10 2
9
1 7 3 6
1 2 1 8
2 5 1
1 10 9 7
1 8 1 2
1 10 5 8
1 10 7 7
2 7 4
1 9 4 2
9
1 2 1 6
1 8 5 6
1 4 2 7
2 9 1
1 5 1 4
1 5 2 7
1 7 1 9
1 9 1 4
2 10 8```

### 输出

```
1 2 5
1 -1 1
1 0 1
1 0 -1 0 0 0 1 8 0
1 0 0 1 0 0 0 0 1```

# 题解

## 作者：SunnyYuan (赞：9)

[更好的阅读体验](https://www.cnblogs.com/PlayWithCPP/p/17278417.html)

### 原题：

![](https://cdn.luogu.com.cn/upload/image_hosting/j300v4xr.png)

### 思路:

经典的小学数学奥数题。

设 $a$ 为每天往上爬的高度，$b$ 为每天向下降的高度，$n$ 为给定的需要爬上去的天数。

请注意，第 $n$ 天爬上去了，就不会下降了。

![](https://cdn.luogu.com.cn/upload/image_hosting/sj6zgu5g.png)

对于操作为 $1$ 的，我们可以确定其范围。

因为要保证第 $n$ 天就可以到达，且第 $n - 1$ 天不能到达，所以其范围为标红部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/szavuzz9.png)

用表达式表示为 $[(a - b) \times (n - 2) + a + 1, (a - b) \times (n - 1) + a]$，其中 $(a - b) \times (n - 2) + a$ 为第 $n - 1$ 天可以到达的最大高度 $+1$ 才可以符合题意；$(a - b) \times (n - 1) + a$ 为第 $n$ 天可以到达的最大高度。

需要特判 $n = 1$ 的情况，此时其范围为 $[1, a]$。

如果这个区间与之前之前计算的结果有交集，那么就是可以保留的，并更新区间，否则就丢弃之。

---

对于操作类型为 $2$ 的，我们先计算出爬上 $l$ 的高度需要的时间 $t$，计算方法如下。

> 假设高度为 $h$。
> 
> 1. 首先要预留一个 $a$。
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/5e9pl2xq.png)
> 
> 2. 然后计算 $\left\lfloor\frac{h - a}{a - b}\right\rfloor$ 表示到达小于等于 $h - a$ 的位置所需要的时间。
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/41ihon21.png)
> 
> 3. 如果刚好到达 $h - a$ 的位置 $+1$ 就可以了，否则 $+2$。
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/jscuc802.png)
> 
> 注意最好不要直接上取整，因为容易引起精度问题。

这样就计算出了 $t$，然后计算出花 $t + 1$ 天爬上的高度范围是否与已知范围 $[l, r]$ 有交集，计算方法与前面的操作 $1$ 类似，如果有那么证明不能准确获取其天数，输出 $-1$，否则输出天数。

注意我们不能直接判断已知范围 $l$ 是否等于 $r$，因为有可能对于这一组询问在该区间内只有一种可能性，也是满足题意的。

### 代码:

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

bool check(int& l1, int& r1, int l2, int r2, bool flag) {
    int ll = max(l1, l2);
    int rr = min(r1, r2);
    if (ll > rr) return false;
    if (flag) {
        l1 = ll;
        r1 = rr;
    }
    return true;
}

void solve() {
    int q;
    cin >> q;
    int opt, a, b, c;
    int l = -1, r = 1e18;
    while (q--) {
        cin >> opt;
        if (opt == 1) {
            cin >> a >> b >> c;
            int lnew = -1, rnew = -1;
            if (c == 1) lnew = 1, rnew = a;
            else lnew = (a - b) * (c - 2) + a + 1, rnew = (a - b) * (c - 1) + a;
            if (check(l, r, lnew, rnew, true)) cout << "1 ";
            else cout << "0 ";
        }
        else {
            cin >> a >> b;
            int x = l, res = 0;
            if (a >= l) {
                res = 1;
            }
            else {
                x -= a;
                res = x / (a - b);
                x = res * (a - b);
                if (x == l - a) res++;
                else res += 2;
            }
            
            c = res + 1;
            int lnew = -1, rnew = -1;
            if (c == 1) lnew = 1, rnew = a;
            else lnew = (a - b) * (c - 2) + a + 1, rnew = (a - b) * (c - 1) + a;
            if (check(l, r, lnew, rnew, false)) res = -1;
            cout << res << ' ';
        }
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
```

**点个赞再走吧**

---

## 作者：Xy_top (赞：3)

上下界不等式题，建议评黄。

## 题意
有一些蜗牛要爬树，每只蜗牛都有属性 $a$，$b$，意味着它白天会向上爬 $a$，晚上会下滑 $b$，现在还有一棵不知道高度的树。

每次输入操作序号 $1$ 或 $2$，操作序号为 $1$ 时输入三个整数 $a$ $b$ $n$，告诉你蜗牛的属性为 $a$ $b$，爬这棵树花了 $n$ 天。如果这个信息和前面产生矛盾，输出 $0$ 并忽略，否则输出 $1$。

操作序号为 $2$ 时输入两个正整数 $a$ $b$，代表一只蜗牛的属性，问的是根据现在的信息能否知道蜗牛需要爬几天，能知道就输出需要爬的天数，否则输出 $-1$。

## 思路

先来解决一个问题：有一只属性为 $a$ $b$ 的蜗牛，爬高度为 $h$ 的树需要几天。答案显然为 $\lceil\frac{h-a}{a-b}\rceil + 1$。

操作 $1$，告诉了我们 $a$ $b$ 和 爬了 $n$ 天，也就是 $\lceil\frac{h-a}{a-b}\rceil + 1=n$，凭借着这些东西不能确定 $h$ 的值，但是可以确定 $h$ 的取值范围。

移项得：$\lceil\frac{h-a}{a-b}\rceil=n-1$，易求出 $h$ 最小为 $(a-b)\times (n - 1) + a$，最大就加上除数减去 $1$，为 $(a-b)\times (n - 1) + a + a - b - 1$。

如何看当前的信息和前面的有没有矛盾？假如求得之前树高度的取值范围 $l$，$r$，当前信息得到树高度范围 $l'$，$r'$，如果有交集就没有矛盾，$l$，$r$ 都要改变，否则就有矛盾输出 $0$。

如何求交集：显然 $\min(r, r') - \max(l, l')$。

再来看操作 $2$，假如我们求出树高的取值范围 $l$，$r$ 如何判断能否确定蜗牛要爬几天？
把 $h=l$ 带入算一下要爬几天，$h=r$ 带入算一下要爬几天，如果一样就能确定了，否则不能。

[AC 链接](https://codeforc.es/contest/1810/submission/199999685)（抢到了很接近 $2$ 亿的提交记录）： 

赛时代码（很乱勿喷）：

```cpp
#include <cmath>
#include <iostream>
#define int long long
using namespace std;
int t, q, op;
int a, b, n;
int l, r;
int fun (int h, int x, int y) {
	if (h <= x) return 1;
	return ceil ( (h - x) * 1.0 / (x - y) ) + 1;
}
signed main () {
	cin >> t;
	while (t --) {
		cin >> q;
		bool f = false;
		while (q --) {
			cin >> op >> a >> b;
			if (op == 1) {
				cin >> n;
				if (!f) {
					if (n == 1) {
						l = 1;
						r = a;
					}
					else {
						l = a * n - b * n - a + 2 * b + 1;
						r = a * n - b * n + b;
					}
					f = true;
					cout << 1 << " ";
				}
				else {
					int x, y;
					if (n == 1) {
						x = 1;
						y = a;
					}
					else {
						x = a * n - b * n - a + 2 * b + 1;
						y = a * n - b * n + b;
					}
					if (max (x, l) > min (y, r) ) cout << 0 << " ";
					else {
						l = max (x, l);
						r = min (y, r);
						cout << 1 << " ";
					}
				}
			}
			else {
				if (!f) cout << -1 << " ";
				else {
					if (fun (l, a, b) == fun (r, a, b) ) cout << fun (l, a, b) << " ";
					else cout << -1 << " ";
				}
			}
		}
		cout << "\n";
	}
	return 0;
}
```


---

## 作者：tallnut (赞：2)

挺好的一道~~小学生~~数学题。
## 整体思路
基本的变量，输入什么的就不专门说了。
### 操作1
用 $curl,curr$ 存储当前指令所允许的树高区间    $[curl,curr]$，原来的区间为 $[l ,r]$。

首先注意 $n=1$ 时的特判，此时
$$curl=1,curr=a$$
因为只用一天就能爬上的话最低也得有 $1$ 米，若超过 $a$ 米则需要至少两天。

然后对于普通情况而言，最矮的情况是在第 $n-1$ 天爬到了距离顶端 $1$ 米的地方，
$$curl=(a-b)\times(n-2)+a+1$$
最高的情况是第 $n$ 天刚好爬到顶端，
$$curr=(a-b)\times(n-1)+a$$

算出了 $curl$ 和 $curr$ 之后，用这个区间与原来区间进行比对，取出 $\max(l,curl)$ 记为 $lmax$ 和 $\min(r,curr)$ 记为 $rmin$（因为 $l$ 越大或 $r$ 越小则该区间范围越小），判断：如果 $lmax>rmin$ 则不符合，否则将 $l$ 赋值为 $lmax$，$r$ 赋值为 $rmin$。
### 操作2
设总共需要 $x$ 天爬完，列出方程
$$(a-b)\times(x-1)+a\ge height$$
且
$$(a-b)\times(x-2)+a<height$$
这两个方程含义为在第 $n$ 天白天至少能够刚好到达树顶，而在 $n-1$ 天白天无法到达树顶。

两个式子分别移项化简为
$$x\ge\frac{height-a}{a-b}+1$$
和
$$x<\frac{height-a}{a-b}+2$$
容易解得
$$x=\lceil \frac{ height-a}{a-b} \rceil+1$$
但是注意要手写 $ceil$ 函数，否则会被卡精度。

注意 $a\ge l$ 和 $a\ge r$ 时的特判。
## AC 代码
[AC 记录](https://www.luogu.com.cn/record/123702586)
，代码中有注释。
```
#include <iostream>
using namespace std;
typedef unsigned long long ull;
//可能的范围[l,r]
ull l,r;
//输入所需数字
ull t,q,type,a,b,n;
//临时变量，存储如果当前蜗牛所说的是对的话它的可能范围
ull curl,curr;
//临时变量，存储对于最小值和最大值需要多少天爬上
ull mindays,maxdays;
//当前和原来l中较大者和当前和原来r中较小者
ull lmax,rmin;
ull ceil_divide(ull a,ull b) { return (a + b - 1) / b; }
int main()
{
	//IO加速
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> q;
		//l,r初始化为可能的最大范围
		l = 1ull;
		r = 1e18;
		while (q--)
		{
			cin >> type >> a >> b;
			if (type == 1ull)
			{
				cin >> n;
				//特判：n=1时
				if (n == 1ull)
				{
					curl = 1ull;
					curr = a;
				}
				else
				{
					//计算可能的范围
					//最矮的情况：在第n-1天的白天爬到了距离顶端1米的地方
					curl = (a - b) * (n - 2ull) + a + 1ull;
					//最高的情况：在第n天白天刚好爬到树顶
					curr = (a - b) * (n - 1ull) + a;
				}
				lmax = max(l,curl);
				rmin = min(r,curr);
				if (lmax > rmin) cout << "0 ";
				else
				{
					cout << "1 ";
					l = lmax;
					r = rmin;
				}
			}
			else
			{
				//计算对于最小值和最大值蜗牛需要多少天来爬
				//（总共需要x天来爬）列出方程：(a-b)*(x-1)+a>=height，也就是x>=(height-a)/(a-b)+1
				//且                           (a-b)*(x-2)+a< height，也就是x< (height-a)/(a-b)+2
				//得x=ceil((height-a)/(a-b))+1
				//记得加特判！
				if (a >= l) mindays = 1;
				else mindays = ceil_divide(l - a,a - b) + 1ull;
				if (a >= r) maxdays = 1;
				else maxdays = ceil_divide(r - a,a - b) + 1ull;
				if (mindays == maxdays) cout << mindays << ' ';
				else cout << "-1 ";
			}
		}
		cout << '\n';
	}
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 CF1810D Climbing the Tree](https://www.luogu.com.cn/problem/CF1810D)

## 解题思路

设当前可能的树高范围为 $[L,R]$。

初始时，树高可能为任意正整数，所以令 $L=1,R=\infty$。

### 1. 事件 $1$

> 一只属性为 $a,b$ 的蜗牛声称花了 $n$ 天爬树。

设符合条件的树高范围为 $[H_{min},H_{max}]$。

前 $n-1$ 天，白天上爬 $a$ 米，晚上下滑 $b$ 米，每天爬 $a-b$ 米；最后 $1$ 天最多爬 $a$ 米。所以 $H_{max}=(a-b)(n-1)+a$ 米。

爬了 $n$ 天意味着第 $n-1$ 天没有爬到树顶，同理 $n-1$ 天最多爬 $(a-b)(n-2)+a$ 米。所以 $H_{min}=(a-b)(n-2)+a+1$ 米。

计算 $[L,R]$ 和 $[H_{min},H_{max}]$ 的交集，如果为空，说明该信息有冲突，直接忽略；否则树高范围需要同时满足这两个集合，即将 $[L,R]$ 设为两者的交集。

### 2. 事件 $2$

> 一只属性为 $a,b$ 的蜗牛询问爬树所需天数。

当树高为 $h$ 米时，设所需天数为 $n$ 天。

最后 $1$ 天爬 $a$ 米，还剩 $h-a$ 米；前面每天爬 $a-b$ 米，需要 $\left\lceil \frac{h-a}{a-b} \right\rceil$ 天。所以 $n=\left\lceil \frac{h-a}{a-b} \right\rceil+1$ 天。

显然，当 $h=L$ 时，所需天数最少；当 $h=R$ 时，所需天数最多。如果两者相等，便可以得出精确的答案。

### 3. 注意事项

- 在事件 $1$ 中，当 $n=1$ 时，最小树高 $H_{min}=1$ 米。
- 在事件 $2$ 中，显然所需天数至少为 $1$ 天。
- 使用 `double` 类型，可能会导致精度丢失。建议根据以下公式手写取上整函数：

$$
\left\lceil \frac{a}{b} \right\rceil=\left\lfloor \frac{a+b-1}{b} \right\rfloor
$$

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const ll inf=0x3f3f3f3f3f3f3f3f;
const int mod=1e9+7;
const int N=200005;
ll up(ll a,ll b){return (a+b-1)/b;}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		ll L=1,R=inf;
		int q;
		cin>>q;
		while(q--)
		{
			int op;
			ll a,b,n;
			cin>>op;
			if(op==1)
			{
				cin>>a>>b>>n;
				ll mn=(n==1?1:(a-b)*(n-2)+a+1);
				ll mx=(a-b)*(n-1)+a;
				if(mx<L||mn>R)
				{
					cout<<0<<' ';
				}
				else
				{
					cout<<1<<' ';
					L=max(L,mn);
					R=min(R,mx);
				}
			}
			else
			{
				cin>>a>>b;
				ll mn=max(up(L-a,a-b)+1,1ll);
				ll mx=max(up(R-a,a-b)+1,1ll);
				cout<<(mn==mx?mn:-1)<<' ';
			}
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
如果一只蜗牛在第 $n$ 天爬到了顶，说明它在 $n-1$ 天还没爬到，也就是说这棵树的高度在 $(n-2)(a-b)+a+1\sim(n-1)(a-b)+a$ 之间。然后更新当前上下界（下界取较大值，上界取较小值），此时如果上界比下界还小说明矛盾，不采用，否则就采用这只蜗牛的说法。

然后如果有蜗牛来询问，那么就只要看它爬上界的天数和爬下界的天数是否相等即可，如果不相等说明有多种可能，回答 $-1$，否则就回答天数 $\max(0,\lceil\frac{l-b-1}{a-b}\rceil)+1$。
# 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int t, q, op;
ll l, r, x, y, a, b, n;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		l = 0, r = 1e18;
		cin >> q;
		while (q --) {
			cin >> op >> a >> b;
			if (op ^ 2) {
				cin >> n;
				x = max (l, (n ^ 1 ? (n - 2) * (a - b) + a + 1 : 0ll)), y = min (r, (n - 1) * (a - b) + a);
				if (x > y)
					cout << "0 ";
				else
					cout << "1 ", l = x, r = y;
			} else {
				x = max (0ll, (l - b - 1) / (a - b)) + 1, y = max (0ll, (r - b - 1) / (a - b)) + 1;
				if (y > x)
					cout << "-1 ";
				else
					cout << x << ' ';
			}
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题目简述

有一些蜗牛从 $0$ 米开始爬树……

你在知道蜗牛们一天早上可以爬 $a$ 米，晚上滑下 $b$ 米。蜗牛们依次爬上来，向你汇报：本蜗爬了 $n$ 天。可能是假的，所以你要判断。

这时，“叮”的很多声，你又依次收到很多封信，很多蜗牛询问你：它需要爬多少天？可能不确定，所以你也要判断。

## 做法

小学数学题。注意如果它爬到了顶部，就不会再下滑了。定义 $l$ 和 $r$ 分别为当前树的高度的区间（初始为 $1$ 和无穷大），$x$ 为 $a-b$。

这时爬上来一直蜗牛，告诉你了一个 $n$。根据已知条件，你可以知道：

* $l1=x(n-2)+a+1(n>1)$

* $r1=x(n-1)+a$

因为最小的树的高度就是爬上去且滑下来后，刚刚爬上昨晚滑下来的距离做一点就到终点；最大的高度就是刚刚爬到极限，准备往下滑的时候就到了。

若 $\max(l,l1)>\min(r,r1)$，我们就不能相信它！否则更新 $l$ 和 $r$。

你又收到一封信，这时你有了一个高度区间，所以你希望帮助蜗牛计算爬上来的天数。你开始计算天数的左右区间：

* $s1=\left\lceil{\dfrac{l-a}{x}}\right\rceil + 1(a<l)$

* $s2=\left\lceil{\dfrac{r-a}{x}}\right\rceil + 1(a<r)$

原理是，先假设 $l$ 是高度，再假设 $r$ 是高度。计算过程是总高度除以每天爬的高度。

若两左右区间重合，就可以确定；否则输出 $-1$。

[代码](https://codeforces.com/contest/1810/submission/254045068)

---

## 作者：Lv_Boxiu (赞：0)

## 思路

### 区间的调整

首先，它能在第 $n$ 天到达顶端，就说明它在第 $n-1$ 天还没有登顶，就可以求出距离的上界和下界：

$$[(a-b)\times(n-2)+a+1,(a-b)\times(n-1)+a]$$

只要已知区间与根据新信息得出的区间有重叠部分，那就说明根据新信息得出的区间是有效的，应该对区间两端进行更新。

### 回答的套路

我们可以根据现有区间的上界和下界，分别求出所用时间的上界 $l$ 和下界 $r$，如果 $l=r$，那么时间是个确定值，否则不是确定值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r,a,b,n,l1,r1,t,q,l2,r2;
int main(){
    cin>>q;
    while(q--){
        l=1;
        r=8e18;//初始化的数值一定要大，否则会 Wrong answer on test 5
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>t>>a>>b;
            if(t==1){
                cin>>t;
                r1=(a-b)*(t-1)+a;
                l1=(a-b)*(t-2)+a+1;
                if(t==1){
                    l1=1;
                    r1=a;
                }
                if(max(l,l1)>min(r,r1)){
                    cout<<"0 ";
                }
                else{
                    cout<<"1 ";
                    l=max(l,l1);
                    r=min(r,r1);
                }
            }
            else{
                l2=l-a;
                r2=r-a;
                if(l2%(a-b)==0){
                    l1=l2/(a-b)+1;
                }
                else{
                    l1=l2/(a-b)+2;
                }
                if(r2%(a-b)==0){
                    r1=r2/(a-b)+1;
                }
                else{
                    r1=r2/(a-b)+2;
                }
                if(l2<=0){
                    l1=1;
                }
                if(r2<=0){
                    r1=1;
                }
                if(l1!=r1){
                    cout<<"-1 ";
                }
                else{
                    cout<<l1<<" ";
                }
            }
        }
        cout<<endl;
    }
    return 0;
}
```

**完结**

---

## 作者：jhdrgfj (赞：0)

## 思路

小学奥数题。

但是懒得推公式怎么办？

容易发现，如果 $i$ 天可以爬上树，$i+1$ 天一定也能爬上树。而如果第 $i$ 天爬不上树，$i-1$ 一定也不能爬上树。于是它启发我们使用二分。

## 解法

先考虑一个简单的问题，如果给定 $a,b,h$，如何计算所需天数？

因为最后一天并不会下降，于是我们可以看作在一棵 $h-a$ 高的树上爬，并且每天都要下落。那么所需的天数即为 $\max(\lceil (h-a) \div (a-b) \rceil,0) + 1$。

我们设 $dl,dr$ 表示当前确定的树高范围为 $[dl,dr]$。

对于每个 $op=1$，我们二分出树高范围为 $[lans,rans]$，如果它与当前范围有交集，则置 $dl=\max(dl,lans)$，$dr=\min(dr,rans)$，否则输出 $0$。

对于每个 $op=2$，我们判断以 $dl$ 为树高和以 $dr$ 为树高所需的天数是否一样即可。

总体复杂度为 $O(q\log a)$，其中 $a$ 为二分值域，这里为 $10^{18}$，喜提最劣解。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int d(int a,int b,int h)
{
	return max(0ll,(h-a)/(a-b))+(max((h-a)%(a-b),0ll)!=0)+1;       //注意不要使用 ceil，否则很可能会被卡精度。
}
signed main()
{
	int t;
	cin>>t;
	while (t--){
		int dl=0,dr=1e18,q;
		cin>>q;
		while (q--){
			int op;
			cin>>op;
			if (op==1){
				int a,b,n;
				cin>>a>>b>>n;
				int l1=0,r1=1e18,la=0,l2=0,r2=1e18,ra=0;
				while (l1<=r1){
					int mid=(l1+r1)/2;
					if (d(a,b,mid)<n){
						l1=mid+1;
					}else{
						la=mid;
						r1=mid-1;
					}
				}
				while (l2<=r2){
					int mid=(l2+r2)/2;
					if (d(a,b,mid)<=n){
						l2=mid+1;
						ra=mid;
					}else{
						r2=mid-1;
					}
				}
				if (la>dr || ra<dl){
					cout<<0<<" ";
				}else{
					cout<<1<<" ";
					dr=min(dr,ra);
					dl=max(dl,la);
				}
			}else{
				int x,y;
				cin>>x>>y;
				if (d(x,y,dl)==d(x,y,dr)){
					cout<<d(x,y,dl)<<" ";
				}else{
					cout<<-1<<" ";
				}
			}
		}
		cout<<endl;
	}
}
```

---

## 作者：masonpop (赞：0)

实际上，我们只需要解决两类问题：

① 给定 $\{a,b\}$，求井深的范围使得**恰好** $n$ 天爬完。

② 给定 $\{a,b\}$ 及井深，求至少多少天爬完。

第一类问题只需求出 $n-1$ 天最多能爬完的高度 $s$，以及 $n$ 天最多能爬完的高度 $t$，则井深范围是 $[s+1,t]$。第二类是典题，运用~~小学奥数~~数学 $O(1)$ 求解即可。

这样，就可以动态维护当前可以得出的井深范围，询问直接令井深取到上下界，检查得出的天数是否相同即可。复杂度 $O(q)$。注意一个很恶心的地方是本题卡精度，不能用 `std::ceil`，需要手写。[代码](https://codeforces.com/contest/1810/submission/220473708)。

---

