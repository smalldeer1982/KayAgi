# Sonya and Matrix

## 题目描述

由于 Sonya 刚刚学习了矩阵的基础知识，她决定稍微玩一下矩阵。

Sonya 想象出了一种新型的矩阵，她称之为菱形矩阵。这种矩阵中恰好有一个格子的值为 $0$，而其他所有格子的值都是它们到该 $0$ 所在格子的曼哈顿距离。所有值相同的格子会形成一个菱形，这也是 Sonya 给这种矩阵命名的原因。

两个格子 $(x_1, y_1)$ 和 $(x_2, y_2)$ 之间的曼哈顿距离定义为 $|x_1 - x_2| + |y_1 - y_2|$。例如，格子 $(5, 2)$ 和 $(7, 1)$ 之间的曼哈顿距离为 $|5-7|+|2-1|=3$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1004D/af239337063966fb68bfc5febfa06333254657a0.png)

菱形矩阵示例。注意，菱形矩阵由 $n$、$m$ 以及 $0$ 所在格子的坐标唯一确定。

她画了一个 $n\times m$ 的菱形矩阵。她认为，如果只给你这个矩阵中所有元素的一个无序序列（即 $n\cdot m$ 个数的序列），你无法还原出这个矩阵。注意，Sonya 不会告诉你 $n$ 和 $m$，你只能得到矩阵中所有数的一个序列。

请编写程序，找出一个 $n\times m$ 的菱形矩阵，使得其元素与给定序列中的元素相同（顺序可以不同）。

## 说明/提示

你可以在题面中的示例图中看到第一个样例的解。你也可以选择 $(2, 2)$ 作为 $0$ 所在格子。你还可以选择一个 $5\times 4$ 的矩阵，$0$ 在 $(4, 2)$。

在第二个样例中，有一个 $3\times 6$ 的矩阵，$0$ 在 $(2, 3)$。

在第三个样例中，无解。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
20
1 0 2 3 5 3 2 1 3 2 3 1 4 2 1 4 2 3 2 4
```

### 输出

```
4 5
2 2
```

## 样例 #2

### 输入

```
18
2 2 3 2 4 3 3 3 0 2 4 2 1 3 2 1 1 1
```

### 输出

```
3 6
2 3
```

## 样例 #3

### 输入

```
6
2 1 0 2 1 2
```

### 输出

```
-1
```

# 题解

## 作者：Linune_Gump (赞：9)

# CF1004D Sonya and Matrix 题解

## 题意

有 $t$个数字，要求把这些数字依次填入一个 $n\times m$的矩形。要求矩形中有且仅有一个 $0$，每个位置到 $0$的曼哈顿距离为这个位置的值。请问是否存在这样的矩阵。存在，输出其中一种矩阵的规模和 $0$所在的位置，不存在，输出 $-1$。

## 思路

不妨设 $0$所在的位置是 $(x, y)$,这个矩阵的规模是 $n\times m$,保证 $0$所在的位置处于左上角。（如果不处于左上角，可以通过旋转的方式调整到左上角。）

假设 $0$所在的位置到 $(1, 1)$的曼哈顿距离为 $a$，到 $(n, m)$的曼哈顿距离为 $b$。

因为 $0$处在左上角， $b$一定是给定的序列中最大的那个，因此 $b$可以预处理。

由上述定义可知：

$a = |x - 1| + |y - 1| = x + y - 2$  -①

$b = |n - x| + |m - y| = n + m - x - y$  -②

~~我不会你谷大括号呜呜呜~~

联立上式得 $a + b = n + m - 2$

变形得 $a = n + m - b - 2$

带回①式得 $n + m - b = x + y$

变形得 $y = n + m - b - x$

对于上面的这个式子， $b$已知， $n$和 $m$可以低复杂度枚举，因此只需要确定 $x$即可获得 $y$。

那么怎么求 $x$呢？不妨引理：在**矩阵足够大的前提下**，到 $0$的曼哈顿距离为 $x$的点一定有 $x \times 4$个，相当于每个点向每个方向扩散一个。这一点在下面会有具体解释。

因此，如果某个数值出现的次数小于 $x \times 4$，这个数值一定**被矩阵大小限制**了。如果数量少了，离 $0$远的点一定优先减少。怎样才会离 $0$最远呢？当然就是纵方向不承担曼哈顿距离，全部由横向承担。因此 $x$的值就是第一个被限制的数值。

这样，只要枚举每个 $n$和 $m$，判断是否可行。如果可行，就直接输出。

### 引理直观解释

假设矩阵无穷大，可以得到下面的矩阵：

```
   3
  323
 32123
3210123
 32123
  323
   3
```

我们惊奇的发现，如果这样画下去，居然是一个菱形！这不就是题目中说的菱形矩阵嘛！说明我们做到这一步是正确的。同时不难发现，这个矩阵每个数据的个数都等于这个数据的四倍。为什么呢？可以用初中学过的代数表达式来证明。这里就不再赘述。

对于限制的说法，不妨截取上面的菱形的一部分：

```
  *
 212
*101*
 212
  *
```

会发现，第一个被截掉的是 $2$，而 $2$被截掉的刚好是最出头的四个位置（也就是标星号的位置）。刚好， $0$的横坐标就是 $2$，这究竟是巧合还是必然呢？各位读者不妨自己思考，在上面的文字中也有所提示。

这样，我们就得到了 $x$的数值。

得到了 $x$的数值，一切就迎刃而解了。具体的可以看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;

int t;
int cnt[N], ct[N];
int a, b, x, y;

bool check()
{
	for(int i = 0; i <= b; i++)
		if(cnt[i] != ct[i])
			return false;
	return true;
}
int main()
{
	scanf("%d", &t);
	for(int i = 1; i <= t; i++)
	{
		scanf("%d", &x);
		cnt[x]++;
		b = max(b, x);
	}
	x = 0;
	for(int i = 1; i <= t; i++)
	{
		if(cnt[i] < i * 4)
		{
			x = i;
			break;
		}
	}
	for(int i = 1; i <= t; i++) // 低复杂度枚举n, m
	{
		if(t % i == 0)
		{
			int n, m;
			n = i, m = t / i, y = n + m - x - b;
			memset(ct, 0, sizeof(ct));
			if(abs(n - x) + abs(m - y) == b)
			{
				for(int j = 1; j <= n; j++)
					for(int k = 1; k <= m; k++)
						ct[abs(j - x) + abs(k - y)]++;
				if(check())
				{
					printf("%d %d\n%d %d\n", n, m, x, y);
					return 0;
				}
			}
		}
	}
	printf("-1\n");
	return 0;
}
```

---

## 作者：Alan_Zhao (赞：3)

**[在我的 cnblogs 中查看](https://www.cnblogs.com/alan-zhao-2007/p/cf1004d-sol.html)**

## 题解

设矩阵是 $n$ 行 $m$ 列的，且唯一的值为 $0$ 的点在 $(x,y)$。不妨设 $x\le n-x+1,y\le m-y+1$，因为可以通过旋转和翻转矩阵将 $(x,y)$ 放到这个区域内。

于是，矩阵中离 $(x,y)$ 最远的点一定是 $(n,m)$。它们之间的距离是 $\lvert n-x\rvert+\lvert m-y\rvert=n+m-x-y$。找到给定的 $t$ 个数中的 $\max$，设为 $\alpha$，则有 $\alpha=n+m-x-y$。

可以发现，矩阵中值为 $a$ 的数（也即和 $(x,y)$ 的距离为 $a$ 的位置）**在不卡边界的情况下**有 $4a$ 个。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3h51220l.png)

图中 $1,2$ 各有 $4,8$ 个，而从 $3$ 开始就卡了边界，因此 $3$ 只有 $8$ 个而不是 $12$ 个。

设最小的被卡边界的数是 $v$，易知 $\min(x,y)=v$。不妨设 $x=v$，根据上面讨论过的 $\alpha=n+m-x-y$，可以算出 $y$。

此时，枚举 $n\times m$ 个位置，并检查其是否与给定的 $t$ 个数 $a_1,a_2,\dots,a_t$ 相同即可。

由于需要满足 $n\times m=t$，所以枚举 $t$ 的约数作为 $n,m$ 的值即可。

时间复杂度 $\mathcal{O}(t\operatorname{d}(t))$，$\operatorname{d}$ 是约数个数函数。

## 代码


```cpp
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
template<typename T> void Read(T &_x){
	_x=0;int _f=1;
	char ch=getchar();
	while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();
	while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();
	_x*=_f;
}
template<typename T,typename... Args> void Read(T &_x,Args& ...others){
	Read(_x);Read(others...);
}
typedef long long ll;
const int T=1e6+5;
int t,cnt[T],mx,cnt_[T];
int Abs(int x){
	return x<0?-x:x;
}
int main(){
	Read(t);
	For(i,1,t){
		int x;Read(x);
		++cnt[x],mx=max(mx,x);
	}
	int x=0;
	For(i,1,t){
		if(cnt[i]!=4*i){
			x=i;break;
		}
	}
	For(n,1,t){
		if(t%n) continue;
		int m=t/n,y=n+m-x-mx;
		if(x>n||y<=0) continue;
		memset(cnt_,0,sizeof cnt);
		For(i,1,n)
			For(j,1,m) ++cnt_[Abs(i-x)+Abs(j-y)];
		if(memcmp(cnt,cnt_,sizeof cnt)==0){
			printf("%d %d\n%d %d\n",n,m,x,y);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：hgckythgcfhk (赞：2)

首先，先观察到一个突破口，$n$ 和 $m$ 一定是 $t$ 的约数，考虑到约数个数函数并不大，所以时间复杂度可以和约数个数有关，于是就有了一个很自然的想法，我们可以猜测正解是每举约数，然后 $O(n)$ 的判断，这个时间复杂度是 $O(n\operatorname{d}(n))$ 的，发现这个东西并不大下面这个程序的输出结果是 $479001600$。
```cpp
inline unsigned d(int x){int s=__builtin_ctz(x);x>>s,++s;
	for(int i=3;i*i<=x&&i<=23;i+=2)if(x%i==0){int t=1;
		while(x%i==0)x/=i,++t;s*=t;
	}if(x>1)s<<=1;return s;}void max(int&a,cit b){a<b?a=b:0;}
signed main(){open;int ans=0;
	for(int i=1;i<=1e6;++i)max(ans,d(i)*i);
	cout<<ans;
}
```
注：这个程序不能正确的求约数个数，但在数据范围内可以正确求出时间复杂度的最大值，这样卡常是因为电脑慢。

观察题意，给定的数组其实是乱序的曼哈顿距离，于是，容易想到先画图（观察到题面中“菱形矩阵也有一定的提示作用”），假设不考虑边界，以 $(x,y)$ 为原点，整个平面的曼哈顿距离如下：
```cpp
          5
        5 4 5
      5 4 3 4 5
    5 4 3 2 3 4 5
  5 4 3 2 1 2 3 4 5 
5 4 3 2 1 0 1 2 3 4 5
  5 4 3 2 1 2 3 4 5
    5 4 3 2 3 4 5
      5 4 3 4 5
        5 4 5
          5
```
仅考虑 $(x,y)$ 尽可能靠近左上角的情况，因为其他情况是对称的，发现，碰到边界最远的一定是 $(n,m)$，最近的一定是 $(x,1)$ 或者 $(1,y)$。

先在我们假设最近最远的碰到边界的距离分别是 $a$ 和 $b$，先只考虑最近的是 $(x,1)$ 有：
$$\begin{cases}x=a\\y=n+m-b-x\end{cases}$$
另一种情况只是把 $x,y$ 互换一下，枚举的时候直接交换 $x,y$ 然后再判断一遍就好了。

求出的这个东西还不能保证一定正确，我们需要暴力的检查一下，具体根据题意模拟即可。

不过我看到其他题解有一个更优雅的处理方法，我最开始的思路是枚举到 $\sqrt t$ 这样就需要中途交换一次判两遍，而其他题解的方法是直接枚举到 $t$ 判一遍，可以避开很多讨论，同时可以减小码量，这启示我们未必需要一见到这种 $i$ 和 $\dfrac{n}{i}$ 对称的就直接考虑枚举到根号，也许全都枚举一遍会更好写。

防止由于火车头被打回，这里直接放 CF 上的 [提交记录](https://codeforces.com/contest/1004/submission/256742022)。

---

## 作者：yimuhua (赞：2)

## 题意

要求将 $t$ 个数字填入一个 $n\times m$ 的矩阵中，满足矩阵中有且仅有一个 $0$，且每个位置上的值就是它到 $0$ 的曼哈顿距离。若存在则输出 $n,m$ 以及 $0$ 的位置 $x,y$。

## 思路：

下文中 $d(x)$ 表示 $x$ 的因数个数。

可以发现满足 $n\times m=t$ 的正整数对 $(n,m)$ 的个数即 $d(t)$ 是很小的：

定理：若 $n=\prod_{i=1}^kp_i^{c_i}$ 则 $
d(n)=\prod_{i=1}^k(c_i+1)$。

$2\times 3\times 5\times 7\times 11\times 13\times 17\times 19=9,699,690>10^6$，此时 $k=8,d(10^6)<2^k$

这提示我们可以枚举 $n,m$，并用较大的时间复杂度判断。

不妨设 $x\leq n-x+1,y\leq m-y+1$，因为显然可以旋转矩阵做到，即：

$x\leq \left\lfloor{\dfrac{n}{2}}\right\rfloor,y\leq \left\lfloor{\dfrac{m}{2}}\right\rfloor$

于是，矩阵中离 $(x,y)$ 最远的点必定是 $(n,m)$，距离为 $\left|n-x\right|+\left|m-y\right|=n+m-x-y$，此时则有式一：$\max\limits_{i=1}^{t}a_i=n+m-x-y$

可以发现，在不管边界的情况下，与一点距离为 $dis$ 的点数为 $4dis(k\geq1)$。

于是找到最小的受到边界影响的数 $dis$，可知 $min(x,y)=dis$，可设 $x=dis$，可由式一解出 $y$，然后枚举 $a_i\ O(t)$ 判断即可。

时间复杂度为 $O(t\times d(t))$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, x, maxi, a[1000005], cnt[1000005];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    for(int i = 1; i <= t; i++)
        cin >> x, cnt[x]++, maxi = max(maxi, x);
    if(cnt[x = 0] ^ 1) {
        cout << -1;
        return 0;
    }
    for(int i = 1; i <= t; i++)
        if(cnt[i] ^ (4 * i)) {
            x = i;
            break;
        }
    for(int n = 1; n <= t; n++)
        if(!(t % n)) {
            int m = t / n, y = n + m - x - maxi;
            if(x <= n && y > 0) {
                memset(a, 0, sizeof(cnt));
                for(int i = 1; i <= n; i++)
                    for(int j = 1; j <= m; j++)
                        if(abs(i - x) + abs(j - y) < 1e6 + 5)
                            a[abs(i - x) + abs(j - y)]++;
                if(!memcmp(cnt, a, sizeof(cnt))) {
                    cout << n << ' ' << m << '\n' << x << ' ' << y;
                    return 0;
                }
            }
        }
    cout << -1;
    return 0;
}
```


---

## 作者：Vistarin (赞：0)

考虑从 $0$ 开始往四周扩展。如果我们能模拟这个扩展过程，就可以直接得出答案。并且，如果我们知道边界位置，就可以方便地进行模拟。

设 $now_i$ 为：扩展数字 $i$ 时，假设它不会越过我们“不知道”的边界，那么 $i$ 的出现次数是多少。例如，如果我们知道 $1$ 已经越过上边界（即，上边界是已知的），我们会考虑这样扩展 $2$：

$$
\begin{array}{}
\hline
\cdots & 2 & 1 & 0 & 1 & 2 & \cdots \\
\cdots &   & 2 & 1 & 2 &   & \cdots \\
\cdots &   &   & 2 &   &   & \cdots \\
& \vdots & \vdots & \vdots & \vdots & \vdots & \\
\end{array}
$$

此时 $now_2 = 5$。显然 $now_i$ 易求。

如果数字 $i$ 新越过 $x$ 条边界，则它的出现次数会变为 $now_i - x$。假设刚刚扩展 $2$ 时，新越过了左边界和下边界，那么实际出现次数（即输入中 $i$ 的出现次数）为 $3$，$now_2 = 5$，$x = 5 - 3 = 2$。

$$
\begin{array}{|}
\hline
1 & 0 & 1 & 2 & \cdots \\
2 & 1 & 2 &   & \cdots \\
\hline
\end{array}
$$

由此，已知之前的边界情况，我们就可以得到下次扩展时，新越过边界的数量。

然而，怎么知道越过的边界是哪一条 or 哪几条呢？很简单，枚举所有情况即可。由于只有 $4$ 条边界，总时间复杂度为 $O(4! \times n \times m)$，可以通过。


```cpp
void solve()
{
	int t;
	cin >> t;

	vector<int> cnt(t);
	int mx = 0;
	for (int i = 1; i <= t; i++) {
		int a;
		cin >> a;
		cnt[a]++;
		mx = max(mx, a);
	}
	if (!cnt[0]) {
		cout << -1;
		return;
	}

	vector<int> id{ 0, 1, 2, 3 };
	do {
		vector<int> v(4, 1e9);
		bool ok = 1;
		auto check = [&](int x, int y) {
			return
				(v[id[0]] == 1e9 || v[id[0]] <= x) &&
				(v[id[1]] == 1e9 || x <= v[id[1]]) &&
				(v[id[2]] == 1e9 || v[id[2]] <= y) &&
				(v[id[3]] == 1e9 || y <= v[id[3]]);
		};
		auto sgn = [&](int x) {
			for (int i = 0; i < 4; i++) {
				if (id[i] == x) return i % 2 ? 1 : -1;
			}
		};

		for (int i = 1; i <= mx; i++) {
			int now = 0, lim = 4 - count(v.begin(), v.end(), 1e9);
			int l = (v[id[0]] == 1e9 ? -i : v[id[0]]);
			int r = (v[id[1]] == 1e9 ? +i : v[id[1]]);
			for (int j = l; j <= r; j++) {
				int x = j, y1 = i - abs(x), y2 = -y1;
				now += check(x, y1);
				if (y1 != y2) now += check(x, y2);
			}
			int sub = now - cnt[i];
			if (sub) {
				if (sub < 0 || sub + lim > 4) {
					ok = 0;
					break;
				}
				int p = 0;
				while (sub) {
					if (v[p] == 1e9) {
						v[p] = sgn(p) * (i - 1);
						sub--;
					}
					p++;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			if (v[i] == 1e9) {
				v[i] = sgn(i) * mx;
			}
		}
		int n = v[id[1]] - v[id[0]] + 1, m = v[id[3]] - v[id[2]] + 1;
		if (n * m != t) {
			ok = 0;
		}
		if (ok) {
			cout << n << ' ' << m << endl;
			cout << 1 - v[id[0]] << ' ' << 1 - v[id[2]];
			return;
		}
	} while (next_permutation(id.begin(), id.end()));

	cout << -1;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 题目思路

利用大眼法不难看出，矩阵是一个从 $(x, y)$ 不断向外扩展的菱形，每扩展一次就是距离加一。

考虑到 $t \le 10^6$，所以 $t$ 的因数实际上是很少的（大概比 $\sqrt n$ 还低），所以考虑暴力枚举 $n, m$。

考虑 $x$ 是什么，其实我们发现如果 $cnt_i \le 4 \times i$，那么这个数肯定就被 $n, m$ 给限制住了，而最小的 $i$ 其实就是 $x$（因为我要限制最紧的）。

然后考虑到 $|x - n| + |y - m| = max, |x - 1| + |y - 1| = min$，又由于 $max, min$ 已知，所以可以联立解方程，解得 $y = n + m - x - max$，又由于我们枚举 $n, m$，已知 $x$，那么 $y$ 就知道了，然后再判断其合不合法就好了。

时间复杂度 $O(t \cdot d(t))$，$d(t)$ 为 $t$ 的因数个数。

## 题目代码

Code：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long //
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )
 
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;
 
char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}
 
template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e6 + 5;

int t, x, y, maxi;
int a[N], tong[N], tmp[N];

bool Check ( int n, int m ) {
  y = n + m - x - maxi;
  memset ( tmp, 0, sizeof ( tmp ) );
  if ( 1 <= x && x <= n && 1 <= y && y <= m ) {
    for ( int i = 1; i <= n; i ++ ) {
      for ( int j = 1; j <= m; j ++ ) {
        tmp[abs ( i - x ) + abs ( j - y )] ++;
      }
    }
    for ( int i = 0; i <= maxi; i ++ ) {
      if ( tong[i] != tmp[i] ) {
        return false;
      }
    }
    return true;
  }
  return false;
}

void Solve () {
  cin >> t;
  for ( int i = 1; i <= t; i ++ ) {
    cin >> a[i];
    tong[a[i]] ++;
    maxi = max ( maxi, a[i] );
  }
  for ( int i = t; i >= 1; i -- ) {
    if ( tong[i] < 4 * i ) {
      x = i;
    }
  }
  for ( int i = 1; i <= t; i ++ ) {
    if ( t % i == 0 ) {
      if ( Check ( i, t / i ) ) {
        cout << i << " " << t / i << '\n' << x << " " << y;
        return ;
      }
    }
  }
  cout << -1;
}
 
signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
	return 0;
}
```

---

