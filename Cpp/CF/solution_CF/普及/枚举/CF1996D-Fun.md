# Fun

## 题目描述

Counting is Fun!

— satyam343



Given two integers $ n $ and $ x $ , find the number of triplets ( $ a,b,c $ ) of positive integers such that $ ab + ac + bc \le n $ and $ a + b + c \le x $ .

Note that order matters (e.g. ( $ 1, 1, 2 $ ) and ( $ 1, 2, 1 $ ) are treated as different) and $ a $ , $ b $ , $ c $ must be strictly greater than $ 0 $ .

## 说明/提示

In the first test case, the triplets are ( $ 1, 1, 1 $ ), ( $ 1, 1, 2 $ ), ( $ 1, 2, 1 $ ), and ( $ 2, 1, 1 $ ).

In the second test case, the triplets are ( $ 1, 1, 1 $ ), ( $ 1, 1, 2 $ ), ( $ 1, 1, 3 $ ), ( $ 1, 2, 1 $ ), ( $ 1, 2, 2 $ ), ( $ 1, 3, 1 $ ), ( $ 2, 1, 1 $ ), ( $ 2, 1, 2 $ ), ( $ 2, 2, 1 $ ), and ( $ 3, 1, 1 $ ).

## 样例 #1

### 输入

```
4
7 4
10 5
7 1000
900000 400000```

### 输出

```
4
10
7
1768016938```

# 题解

## 作者：fengxiaoyi (赞：6)

2024/9/26：将 $x-a\times b$ 更改为 $n-a\times b$，感谢 @[5t0_0r2](https://www.luogu.com.cn/user/999274)。

先枚举 $a$，再枚举 $b$，然后求出 $c$ 的范围就可以统计答案了。

看似会超时，但是这个 $b\le \min\{x-a,\frac{n}{a}\}$，所以时间过得去。

对于确定的 $a,b$，就能求出 $1\le c\le \min\{x-a-b,\frac{n-a\times b}{a+b}\}$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void ri(int &_a){
	int res=0,f=1;
	char c;
	for(;(c=getchar())<'0'||c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9') res=(res<<1) + (res<<3) + c-'0',c=getchar();
	_a=res*f;
}
inline void rll(long long &_a){
	long long res=0ll,f=1;
	char c;
	for(;(c=getchar())<'0'||c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9') res=(res<<1) + (res<<3) + c-'0',c=getchar();
	_a=res*f;
}
/*-----------------*/
int t,n,x;
int main(){
	ri(t);
	while(t--){
		ri(n),ri(x);
		long long ans=0;
		for(int i=1;i<=x;i++){
			for(int j=1;1ll*j*i<=n&&i+j<=x;j++){
				int p=(n-i*j)/(i+j),q=x-i-j;
				ans+=min(p,q);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Defy_HeavenS (赞：2)

## 题意
给定 $n$ 和 $x$，求满足 $ab+ac+bc \le n$ 且 $a+b+c \le x$ 的 $(a,b,c)$ 三元组数量，其中 $a,b,c > 0$。

## 暴力
分别枚举 $a,b,c$。
$$
\begin{array}{c}
\because a+b+c \le x \\
\therefore a,b,c < x
\end{array}
$$
即从 $1$ 枚举到 $x$。若满足条件计入答案。时间复杂度 $\mathcal{O}(n^3)$。
```cpp
void solve(){
	int n,x,ans=0;
	cin>>n>>x;
	for(int a=1;a<x;a++){
		for(int b=1;b<x;b++){
			for(int c=1;c<x;c++){
				if(a*b+a*c+b*c<=n&&a+b+c<=x){
					ans++;
				}
			}
		}
	}
	cout<<ans<<"\n";
}
```

## 正解
考虑只枚举 $a,b$。
$$
\begin{array}{c}
\because a+b+c \le x \\
\therefore c\le x-a-b \\ \\
\because ab+ac+bc \le n \\
\therefore ab+(a+b)c \le n \\
\therefore c\le \frac{n-ab}{a+b}
\end{array}
$$
因此 $c$ 可能的个数为 $\min(x-a-b,\frac{n-ab}{a+b})$。
这样时间复杂度还是 $\mathcal{O}(n^2)$ 的，但是不是所有的 $a,b$ 都能有合法的 $c$。
$$
\begin{array}{c}
\because ab+ac+bc \le n \\
\therefore ab \le n-a-b \\
\therefore ab \le n \\
\therefore b \le \frac{n}{a} \\
\end{array}
$$
即当确定了 $a$，$b$ 的可能个数为 $\frac{n}{a}$，那么合法 $b$ 的总数量为 $\sum_{a=1}^{n} \frac{n}{a}$，这是什么？调和级数啊！总数量约为 $n\log n$。
所以只要保证 $ab\le n$，那时间复杂度为 $\mathcal{O}(n\log n)$，可通过此题。
```cpp
void solve(){
	int n,x,ans=0;
	cin>>n>>x;
	for(int a=1;a<x;a++){
		for(int b=1;b<x;b++){
			if(a*b>n){
				break;
			}
			int c=max(0,min(x-a-b,(n-a*b)/(a+b)));
			ans+=c;
		}
	}
	cout<<ans<<"\n";
}
```

---

## 作者：___w (赞：2)

[CF1996D Fun](https://codeforces.com/contest/1996/problem/D)

有一个很奇葩的做法，跟官方做法完全不一样，一定要来分享一下。

由 $ab+ac+bc\le n$ 我们可以得出 $a(b+c)+bc\le n$。所以我们考虑枚举 $a$ 和 $b,c$ 的和 $k$，由于有 $ak\le n$ 的限制，所以这样枚举的复杂度为 $\lfloor\frac{n}{1}\rfloor+\lfloor\frac{n}{2}\rfloor+\lfloor\frac{n}{3}\rfloor+\dots=O(n\log n)$。

接下来我们考虑数出满足这样条件的 $b,c$。问题转化为两个数的和为定值，求两个数的乘积 $\le n-ak$。我们设一个数为 $x$，注意 $x$ 的定义域为 $[1,k-1]$。则 $x(k-x)\le n-ak$，化简为 $x^2-kx+n-ak\ge 0$，$\Delta$ 为 $k^2-4(n-ak)$。若 $\Delta\le0$，则上式是恒成立的，答案直接加上 $k-1$ 即可。若 $\Delta>0$，我们能够求出两个根 $x_1,x_2$，那么答案为 $[1,x_1]$ 和 $[x_2,k-1]$ 中的整数个数。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

typedef vector <int> vi;
typedef pair <int, int> pii;

inline int rd() { int x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
template <typename T> inline void write(T x) { if (x < 0) x = -x, putchar('-'); if (x > 9) write(x/10); putchar(x%10+48); }

void solve() {
	int n, x, ans = 0; cin >> n >> x;
	for (int a = 1; a <= x; ++a)
		for (int k = 2; a+k <= x && a*k <= n-1; ++k) {
			int r = n-a*k, d = k*k-4*r;
			if (d <= 0) ans += k-1;
			else {
				double x1 = (k-sqrt(d))/2, x2 = (k+sqrt(d))/2;
				ans += max((int)floor(x1), 0ll)+max((int)(k-ceil(x2)), 0ll);
			}
		}
	cout << ans << '\n';
}

signed main() {
	int t = rd();
	while (t--) solve();
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

这题就是是直接暴力出奇迹。开始我们 $a,b,c$ 一个也不知道，那么肯定要先枚举一个字母 $a$。接着枚举 $b$。由于 $ab+ac+bc\le n$，那么 $ab\le n$。所以 $b\le\displaystyle\frac{n}{a}$。容易看出枚举 $ab$ 的复杂度就是调和级数级别的。最后考虑 $c$。我们把 $a,b$ 代入得到两个不等式。

$$\begin{cases}c\le \displaystyle\frac{n-ab}{a+b}\\c\le x-a-b\end{cases}$$

所以 $1\le c\le\min\Big(\displaystyle\frac{n-ab}{a+b},x-a-b\Big)$，就可以得出正整数 $c$ 的个数了。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int n,x;
void solve()
{
  int ans=0;
	cin>>n>>x;
  for(int i=1;i<=n;i++)
  {
    for(int j=i;j<=n;j+=i)
    {
      int a=i,b=j/i,u=(n-a*b)/(a+b),v=x-a-b;
      ans+=max(0,min(u,v));
    }
  }
  cout<<ans<<"\n";
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：CEFqwq (赞：1)

赛时没做出来，真是无药可救。

考虑枚举 $a$ 和 $b+c$，然后就知道了 $bc=n-a(b+c)$。

知道了这些，直接二分 $c$，统计就好了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, lans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while (t--){
		int n, x;
		lans = 0;
		cin >> n >> x;
		for (int i = 1; i <= n && i <= x - 2; i++){
			for (int jpk = 2; i * jpk <= n && i + jpk <= x; jpk++){
				int sy = n - (i * jpk);
				if (sy == 0)
					break;
				int l = 1, r = (jpk >> 1), ans = 0;
				while (l <= r){
					int mid = (l + r) >> 1;
					if (mid * (jpk - mid) <= sy)
						ans = mid, l = mid + 1;
					else
						r = mid - 1;
				}
				lans += (ans << 1);
				if (ans == (jpk >> 1) && !(jpk & 1))//b 和 c 相同，减掉重复的
					lans--;
			}
		}
		cout << lans << "\n";
	}
}
```

---

## 作者：GoldenCreeper (赞：0)

假设我们确定了未知数 $a,b$ 的值，那么这个问题是好做的。

容易得到：$\left\{\begin{matrix}
c \le x-a-b
 \\c\le \dfrac{n-ab}{a+b}
\end{matrix}\right.$，所以答案等于 $\min\{x-a-b,\left \lfloor\dfrac{n-ab}{a+b}  \right \rfloor \}$。

我们尝试枚举所有可能的 $a$，发现此时的 $b$ 需要满足 $b\le\min\{\dfrac{n}{a},x-a\}$。事实上，我们可以据此来枚举所有的 $b$，并根据上述分析计算所有的 $c$。当 $n,x$ 均为 $10^6$ 时，即使每次只使用 $\left \lfloor\dfrac n a \right \rfloor$ 来枚举，那么共进行 $13970034$ 次枚举，实际的操作会取一次 $\min$，所以实际操作数会小于这个值，这个复杂度是我们可以接受的，[AClink](https://codeforces.com/contest/1996/submission/272831561)。

---

## 作者：Guchenxi0971 (赞：0)

赛时 $20$ 分钟想出思想，可没有勇气，差一个时间复杂度分析，被硬控 $2$ 个小时。

### 题意

给定 $n$ 和 $x$ 求满足 $ab + ac + bc \le n$ 且 $a + b + c \le x$ 的有序三元组个数 $(a,b,c)$。

### Sol

考虑在确定了 $a$ 和 $b$ 以后，我们可以 $O(1)$ 求出 $c$ 的上界，因为 $c\leq x-a-b$ 且 $c\leq \frac{n-ab}{a+b}$，那么 $c=\min(x-a-b,\frac{n-ab}{a+b})$ 可是 $10^6$ 的数据根本不允许我们枚举 $a$ 和 $b$。

考虑优化枚举，可以发现在确定 $a$ 之后可以缩小 $b$ 的枚举范围。因为如果在不考虑 $c$ 时，$b$ 可以取到最大值，可以发现 $b\leq x-a$ 且 $b\leq\frac na$ ，那么 $b=\min(x-a,\frac na)$ 考虑这个式子，假设 $b$ 全部选 $\frac na$，可以发现其总量是 $\sum\limits_{i=1}^n \frac ni$ 这显然是调和数，其是 $O(n\log n)$ 级别的。并且实际上 $b$ 的量会更少，于是我们可以枚举 $a$ 和 $b$ 去计算 $c$，时间复杂度是 $O(n\log n)$ 的。

### Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define int long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
const int Max=2e5+10;
const int mod=1e9+7;
const int inf=1e9+10;



inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

int sum[Max];
map <int,int>num;
char c[Max];

void work(){
	int n=read();
	int x=read();
	int ans=0;
	for(int a=1;a<x;++a){
		int mb=min(x-a-1,n/a); //计算b的上线
		for(int b=1;b<=mb;++b){
			int c=min((n-a*b)/(a+b),x-a-b);//O(1) 计算c的取值
			if(c>0)ans+=c;
		}
	}
	cout << ans << '\n';
}

signed main(){
	int t=read();
	while(t--)work();
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## CF1996D

先把题目的两个约束推一下式子：

$$ab+ac+bc\le n \iff c(a + b) \le n - ab \iff c \le \dfrac{n - ab}{a + b}$$

$$a + b + c \le x \iff c \le x - a - b$$

综上，$c\le \min \{\lfloor\dfrac{n - ab}{a + b}\rfloor,x-a-b \}$。

观察第一项，由于 $c$ 是正整数，要保证 $\dfrac{n - ab}{a + b} \ge 1$，所以 $n-ab\ge a + b \ge 0 \iff ab \le n \iff b \le \dfrac na$。

所以对于一个 $a$，最多有 $\lfloor \dfrac na \rfloor$ 个 $b$ 满足条件，则 $b$ 的个数是 $O(\sum_{i=1}^{n}\dfrac ni)=O(n\sum_{i=1}^{n}\dfrac 1i) = O(n\log n)$ 级别的，可以枚举 $a, b$，计算 $c$ 的取值范围，求出最终答案。时间复杂度 $O(n\log n)$。

代码：

```cpp
void Main() {
  int n = read(), x = read();
  ll res = 0;
  for (int a = 1; a <= n; a++)
    for (int b = 1; b <= n && n - a * b >= a + b && x - a - b > 0; b++)
      res += min((n - a * b) / (a + b), x - a - b);
  printf("%lld\n", res);
}
```

---

## 作者：_O_v_O_ (赞：0)

很明显，我们假如知道 $a,b$，那么我们可以直接算出 $c$ 的范围，也就是 $\min\{x-a-b,\lfloor \frac{n-ab}{a+b}\rfloor\}$。

那么我们就可以暴力枚举 $a,b$，我们注意到如果 $a\times b>n$，那么更大的 $a,b$ 肯定也不能满足条件，那么我们就直接退出循环。

时间复杂度为 $O(\sum_{i=1}^n\frac{n}{i})=O(n\log n)$，可以通过。

---

