# Dora and C++

## 题目描述

Dora 刚学了编程语言C++！

但是，她一点也不明白C++的含义。 她认为C++是两种在长度为 $n$ 的数组 $c$ 上的加法操作。Dora 有两个整数 $ a $ 与 $ b $ 。 每一次操作，她可以选择一件事情去做。

- 选择一个整数 $ i $ ，其中 $ 1 \leq i \leq n $ ，然后把 $ c_i $ 加上 $ a $ 。
- 选择一个整数 $ i $ ，其中 $ 1 \leq i \leq n $ ，然后把 $ c_i $ 加上 $ b $ 。

注意，这里 $ a $ 与 $ b $ 是常数，且他们可以相同。

让我们规定一个数组的值域 $ d $ 为 $ \max(d_i) - \min(d_i) $ 。仅举几例：数组 $ [1, 2, 3, 4] $ 的值域是 $ 4 - 1 = 3 $ ，数组 $ [5, 2, 8, 2, 2, 1] $ 的值域是 $ 8 - 1 = 7 $ ， 数组 $ [3, 3, 3] $ 的值域是 $ 3 - 3 = 0 $ 。

经过若干次操作 (可能是 $ 0 $ )， Dora 计算出了新数组的值域。 请你帮助 Dora 最小化其值，但是自从 Dora 爱上了仅凭自己探索，你只需要告诉她最小化后的值。

## 样例 #1

### 输入

```
10
4 5 5
1 3 4 4
4 2 3
1 3 4 6
4 7 7
1 1 2 6
3 15 9
1 9 5
3 18 12
1 4 5
7 27 36
33 13 23 12 35 24 41
10 6 9
15 5 6 9 8 2 12 15 3 8
2 1 1000000000
1 1000000000
6 336718728 709848696
552806726 474775724 15129785 371139304 178408298 13106071
6 335734893 671469786
138885253 70095920 456876775 9345665 214704906 375508929```

### 输出

```
3
0
3
2
3
5
1
0
17
205359241```

# 题解

## 作者：panyibo (赞：8)

# CF2007C Dora and C++
## 题意简析
$n$ 个数，每次可以把一个数加 $a$ 或者加 $b$，求进行若干次操作后序列的极差 $(\max {-} \min)$ 的最小值。
## 大致思路
假设原本序列中一个数是 $c$，如何判断是否可能变为 $d$？
设变量 $x,y$ 表示用了 $x$ 个 $+a$ 和 $y$ 个 $+b$。

$ax + by = d - c$ 有解条件为 $ \gcd(a,b) | (d-c)$，但是没有保证 $x,y$ 非负。

所以只需要 $d$ 尽量大，那么一直整体加 $a$ 和 $b$ 即可。

这样相当于在模 $a$ 和 $b$ 的最小公约数的意义下做这个题。

简单排序即可求解。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 100;
int T,n,a,b,t[N],g;
inline int read()
{
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int gcd(int a, int b) 
{
    return b == 0 ? a : gcd(b, a%b);
}
signed main()
{
    T =read();
    while(T --)
    {
        n = read(); a = read(); b = read(); 
        int p = gcd(a,b);
        for(int i = 1;i <= n;i++)
        {
            t[i] = read();
            t[i] %= p;//模p意义下，p = gcd(a,b)
        }
        sort(t + 1,t + n + 1);//排序
        int ans = t[n] - t[1];
        for(int i = 1;i < n;i++) ans = min(ans,t[i] + p - t[i + 1]);
        cout << ans << endl; 
    }
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：6)

挺好的一道题。比较有思维。

首先，我们考虑，将某个数加 $b$，剩下的数全加上 $a$，其实就等价于将这个数加上 $b - a$。我们另 $c = b - a$。将某个数加上 $c$，其他的都加上 $b$，那么等价于将这个数增加 $c - a$。同样的，$c - b, c - a - b, c - b - b$ 等等都是可以构造得到的。

我们发现上面的过程等价于更相减损术。因此该问题等价于：另 $t = \gcd(a, b)$。每次可以将一个数加上或减去 $t$。最小化极差。

这个问题是好做的。将所有数加到某个极差 $< t$ 的状态并排序。接下来，不断的将最小的数加上 $t$ 并维护极差即可。[Submission](https://codeforces.com/contest/2007/submission/278801323)。

---

## 作者：chenxi2009 (赞：4)

# 思路

我们可以无限次地将一个数加上 $a$ 或者加上 $b$。

既然我们要使极差最小，所以本质上我们要关心的只是数字之间的相对差距而非其值的大小。发现这相当于我们可以无限次地改变相对误差，每次改变的值为 $\gcd(a,b)$。将所有数字对 $\gcd(a,b)$ 取模后排序，**最小的**极差就是相邻的两个数字的差值的最小值。这里我们令第 $1$ 个数字和第 $n$ 个数字相邻。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,b,c[100001],g,mn,mx,ans;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%d%d%d",&n,&a,&b);
		g = __gcd(a,b);
		mn = g - 1,mx = 0;
		for(int i = 1;i <= n;i ++){
			scanf("%d",&c[i]);
			c[i] %= g;
		}
		sort(c + 1,c + n + 1);
		ans = c[n] - c[1];
		for(int i = 1;i < n;i ++){
			ans = min(ans,c[i] + g - c[i + 1]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：GY程袁浩 (赞：1)

实际上，我们不仅可以加 $a$，或者加 $b$。

由于我们只在乎相对差，所以我们可以做减 $a$，减 $b$，加 $\lvert a-b\rvert$ 等更多操作。

发现实际上，我们如果一直计算类似两个数相减的值，最终得到的一个数就会是 $\gcd(a,b)$，这是由于辗转相除法。我们同样可以知道，所有数都是 $\gcd(a,b)$ 的倍数。因此，考虑只对原数进行无限次加 $\gcd(a,b)$ 的操作得到的答案和原问题的答案相等，也就是说，这两个问题等价。

接下来，求我们可以对每个数加或减 $\gcd(a,b)$ 的答案。

两个数 $x,y(x>y)$ 的差在模 $\gcd(a,b)$ 意义下分别是 $(x-y) \bmod \gcd(a,b),\gcd(a,b)-(x-y) \bmod \gcd(a,b)$。

我们将所有 $x \bmod \gcd(a,b)$ 从小到大排序作为 $B$，然后最大值减最小值就是所有差全部取第一种的答案。

即 $B_{n}-B_{1}$。

如果想取第二种，那么我们可以证明，只有寻找一个分割点，左边的全部加 $\gcd(a,b)$，右边的全部不变才有可能取到答案。

即 $\min\{B_{i}+\gcd(a,b)-B_{i+1}\}$。

两种情况继续取最小值。

```cpp
// Problem: C. Dora and C++
// Contest: Codeforces - Codeforces Round 969 (Div. 2)
// URL: https://codeforces.com/contest/2007/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
const int N = 1e6 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int ac[N], n, a, b;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int ans = INF;
        cin >> n >> a >> b;
        int gcdd = __gcd(a, b);
        int maxn = -INF, minn = INF;
        upp(i, 1, n) {
            int x;
            cin >> x;
            ac[i] = x % gcdd;
        }
        sort(ac + 1, ac + 1 + n);
        ans = min(ans, ac[n] - ac[1]);
        upp(i, 1, n - 1) { ans = min(ans, ac[i] + gcdd - ac[i + 1]); }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Milthm (赞：1)

这题的重点就是从“相对”的角度来考虑问题。虽然题目只有加法，但是从相对的角度看，我们把其它所有数都加 $x$，就相当于给这个数减 $x$。

所以现在题目被转化成了有加有减，也就是说，我们可以制造任意的为 $\gcd(a,b)$ 倍数的变化量。

所以我们考虑把原数组对 $\gcd(a,b)$ 取模，然后问题就转化为了，每次可以给某个数加上或减去 $\gcd(a,b)$，最小化极差。

显然可以先排序，每次枚举某一个前缀全部加 $\gcd(a,b)$ 的答案。时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
int T,n,a,b,c[N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>a>>b;int d=__gcd(a,b);
		for(int i=1;i<=n;++i)cin>>c[i],c[i]%=d;
		sort(c+1,c+n+1);int ans=1e9;
		for(int i=1;i<n;++i)ans=min(ans,c[i]-c[i+1]+d); 
		ans=min(ans,c[n]-c[1]);
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

我们可以无限次地将一个数加上 $x$ 或者 $y$，最后求若干次操作后序列的极差的最小值。

既然我们要使极差最小，所以要关心的数字之间的相对差距。不难发现，每次更改的值就是 $\gcd (x, y)$。所以，将所有数字对 $\gcd (x, y)$ 取模后排序，最小的极差就是相邻两个数字差值的最小值。

这里可以直接使用求最大公因数的封装函数 `__gcd ()` 去做。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 1e5 + 10;
ll T, n, x, y, shu[MAXN], gcdd = 0, ans = 0;
void read () {
	scanf ("%lld%lld%lld", &n, &x, &y);
	gcdd = __gcd (x, y);
	for (ll i = 1; i <= n; i ++) {
		scanf ("%lld", &shu[i]);
		shu[i] %= gcdd;
	}
	sort (shu + 1, shu + n + 1);
	ans = shu[n] - shu[1];
	for (ll i = 1; i <= (n - 1); i ++) ans = min (ans, shu[i] + gcdd - shu[i + 1]);
	printf("%lld\n",ans);	
}
int main () {
	scanf ("%lld", &T);
	while (T --) read ();
	return 0;
}

```

---

