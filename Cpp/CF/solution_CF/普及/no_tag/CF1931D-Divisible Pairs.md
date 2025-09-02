# Divisible Pairs

## 题目描述

Polycarp has two favorite integers $ x $ and $ y $ (they can be equal), and he has found an array $ a $ of length $ n $ .

Polycarp considers a pair of indices $ \langle i, j \rangle $ ( $ 1 \le i < j \le n $ ) beautiful if:

- $ a_i + a_j $ is divisible by $ x $ ;
- $ a_i - a_j $ is divisible by $ y $ .

For example, if $ x=5 $ , $ y=2 $ , $ n=6 $ , $ a= $ \[ $ 1, 2, 7, 4, 9, 6 $ \], then the only beautiful pairs are:

- $ \langle 1, 5 \rangle $ : $ a_1 + a_5 = 1 + 9 = 10 $ ( $ 10 $ is divisible by $ 5 $ ) and $ a_1 - a_5 = 1 - 9 = -8 $ ( $ -8 $ is divisible by $ 2 $ );
- $ \langle 4, 6 \rangle $ : $ a_4 + a_6 = 4 + 6 = 10 $ ( $ 10 $ is divisible by $ 5 $ ) and $ a_4 - a_6 = 4 - 6 = -2 $ ( $ -2 $ is divisible by $ 2 $ ).

 Find the number of beautiful pairs in the array $ a $ .

## 样例 #1

### 输入

```
7
6 5 2
1 2 7 4 9 6
7 9 5
1 10 15 3 8 12 15
9 4 10
14 10 2 2 11 11 13 5 6
9 5 6
10 7 6 7 9 7 7 10 10
9 6 2
4 9 7 1 2 2 13 3 15
9 2 3
14 6 1 15 12 15 8 2 15
10 5 7
13 3 3 2 12 11 3 7 13 14```

### 输出

```
2
0
1
3
5
7
0```

# 题解

## 作者：jiangxinyang2012 (赞：7)

其实这道题还是挺简单的。

首先考虑暴力。每次枚举所有的 $i$，$j$，满足 $1 \le i < j \le n$，根据题目，如果 $a_i + a_j$ 是 $x$ 的倍数且 $a_i - a_j$ 是 $y$ 的倍数，则答案加一。

时间复杂度 $O(n^{2})$。
```
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 200005;
const int INF = 0x3f3f3f3f;
ll a[N];
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int n;
        ll x, y;
        scanf("%d%lld%lld", &n, &x, &y);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if ((a[i] + a[j]) % x == 0 && (a[i] - a[j]) % y == 0) {
                    ans++;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}

```

接下来考虑优化。

我们设 $s1 = a_i$，$s2 = a_j$。如果 $s1 + s2 \equiv 0 \pmod x$，那么很容易发现，如果确定了 $s1$，那么满足条件的 $s2$ 一定满足 $s2 \bmod x = (x - s1 \bmod x) \bmod x$，$s2 \bmod y = s1 \bmod y$。因为只有这样，才是满足要求的数对。

这样，我们就可以从 $n$ 到 $1$ 每次枚举一个 $a_i$，使用 map 存储取模 $x,y$ 的情况，这样就可以求出在 $a_i$ 之后满足条件的 $a_j$ 的数量，将它加到答案里。

时间复杂度 $O(n \log{n})$。
```
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 200005;
const int INF = 0x3f3f3f3f;
ll a[N];
map<pair<ll, ll>, int> mp;
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        mp.clear();
        int n;
        ll x, y;
        scanf("%d%lld%lld", &n, &x, &y);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        ll ans = 0;
        for (int i = n; i >= 1; i--) {
            int s1 = (x - a[i] % x) % x, s2 = a[i] % y;
            ans += mp[{s1, s2}];
            mp[{a[i] % x, a[i] % y}]++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

```

---

## 作者：zhuweiqi (赞：7)

本题可以这样做，对于数组中的每个元素 $a_i$，求出位于其后面的元素 $a_j$（$i<j\leq n$）且满足 $a_j \bmod x=(x-a_i\bmod x)\bmod x$（即题目中要求的 $(a_i+a_j)\bmod x=0$，通过同余定理及移项可以得到）以及 $a_j\bmod y=a_i \bmod y$（即 $(a_i-a_j)\bmod y=0$）的数量，我们可以用 map 嵌套二元对作为存储这些信息的数据结构（详见代码），逆序处理累计贡献即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
map<pair<int,int>,int> p;
int a[200002];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,x,y;
		cin>>n>>x>>y;
		p.clear();
		long long ans=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=n;i>=1;i--){
			ans+=p[{(x-a[i]%x)%x,a[i]%y}];
			p[{a[i]%x,a[i]%y}]++;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：信息向阳花木 (赞：2)

$(a_i+a_j) \bmod x = [(a_i \bmod x) + (a_j \bmod x)] \bmod x$，$(a_i - a_j) \bmod x$ 不考虑负数的情况下也等于 $(a_i \bmod x) - (a_j \bmod x)$。所以我们可以先预处理每个数分别模 $x,y$ 的余数。然后直接用桶统计一下各个余数的个数。比如一个数模 $x,y$ 的值分别是 $p,q$，和它能组成“美丽数对”的数个数就是模 $x,y$ 的值为 $(x-p) \bmod x,q$ 的数的个数。可以用 map 记录模 $x,y$ 值为 $p,q$ 的数的个数。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<int, int> PII;

const int N = 200010;

int t, n, x, y;
int a[N];
PII p[N];
map<PII, int> mp;

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		scanf("%d%d%d", &n, &x, &y);
		mp.clear(); long long res = 0;
		for (int i = 1; i <= n; i ++ )
		{
			scanf("%d", &a[i]);
			int p = x - a[i] % x;
			if(p == x) p = 0;
			res += mp[{p, a[i] % y}];
			mp[{a[i] % x, a[i] % y}] ++;
		}
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：yyrwlj (赞：1)

## 思路

题目中说要让 $a_i + a_j$ 能被 $x$ 整除，也就是 $(a_i + a_j) \operatorname{mod} x = 0$。

进一步转换，可以得到 $(a_i \operatorname{mod} x + a_j \operatorname{mod} x) \operatorname{mod} x=0$。

因为加号两边都肯定小于 $x$，所以括号里面的和只能是 $x$ 或 $0$，若是 $0$，则加号两边的结果都应该为 $0$。

同理可得 $a_i \operatorname{mod} y - a_j \operatorname{mod} y=0$，移项得 $a_i \operatorname{mod} y=a_j \operatorname{mod} y$。

我们可以使用 STL 中的 `map<pair<int, int>, int>` 来维护。

设当前枚举的 $a_j$ 模 $x$ 和 $y$ 的结果分别是 $b$ 和 $c$，则往前找的 $i$ 要满足 $a_i \operatorname{mod} x=x-b$ 且 $a_i \operatorname{mod} y = c$。

要特判如果 $b=0$，则 $a_i \operatorname{mod} x$ 应该等于 $0$。

## Code

```cpp
typedef long long LL;
typedef pair<int, int> PII;
void work()
{
    map<PII, int> cnt;
    cnt[{a[1] % x, a[1] % y}] = 1;
    LL ans = 0;
    for (int i=2;i<=n;i++)
    {
        int A = x - a[i] % x;
        if (a[i] % x == 0)
            A = 0;
        ans += cnt[{A, a[i] % y}];
        cnt[{a[i] % x, a[i] % y}] ++;
    }
}
```

---

## 作者：IANYEYZ (赞：1)

考虑转化题目条件。

容易发现 $x \mid a_i + a_j$ 等价于 $a_i \equiv -a_j \pmod x$。

同样的 $y \mid a_i - a_j$ 等价于 $a_i \equiv a_j \pmod y$。

我们发现同余是非常好处理的，直接设一个 $b_{i,j}$ 表示满足 $a_k \equiv i \pmod x$ 并且 $a_k \equiv j \pmod y$ 的 $k$ 的数量（数组显然是开不下的，`map` 就行了）。

随后扫一遍 $a$ 数组，每次加上 $b_{x - a_i \bmod x,a_i \bmod y}$（如果$(i,i)$ 是 beautiful 就要减去），最后除二（每一对算了两遍）就行了。

代码（自行忽略 `debug` 库）：

```cpp
#include <iostream>
#include <map>
#ifndef ONLINE_JUDGE
#include "../../../debug.hpp"
#else
#define debug(...)
#define debugArr(...)
#endif
#define int long long
using namespace std;
int a[200010],t,n,x,y,ans;
map<pair<int,int>,int> mp3;
signed main()
{
	cin >> t;
	while (t--) {
		mp3.clear();
		ans = 0;
		cin >> n >> x >> y;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			mp3[{a[i] % x,a[i] % y}]++;
		}
		debug(mp3);
		for (int i = 1; i <= n; i++) {
			int r3 = mp3[{(x - (a[i] % x) == x ? 0 : x - (a[i] % x)),a[i] % y}] - ((a[i] + a[i]) % x == 0);
			debug(i, r3);
			ans += r3;
		}
		ans /= 2;
		cout << ans << "\n";
	}
}
```

---

## 作者：mayike (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1931D)

## 思路

我们知道对于满足条件的 $i,j$，$(a_i+a_j) \bmod x = 0,(a_i-a_j) \bmod y = 0$，推得：

$$a_i \bmod x + a_j \bmod x = 0$$

$$a_i \bmod x = (x - (a_j \bmod x)) \bmod x$$ 

$$a_i \bmod y = a_j \bmod y$$

要满足两个条件，用哈希记录一下即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<20+5];
inline int read(){
	int x=0,f=1;
	char c=gc();
	while(!isdigit(c)){
		if(c=='-')f=-1;
		c=gc();
	}while(isdigit(c)){
		x=x*10+(c^48);
		c=gc();
	}return x*f;
}
const int N=2e5+5;
int T,n,x,y,ab,ans;
map<int,map<int,int> >mp;//二维map
signed main(){
   //ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		mp.clear();//记得清空
		n=read(),x=read(),y=read(),ans=0;
		for(int i=1;i<=n;i++)
            ab=read(),ans+=mp[(x-ab%x)%x][ab%y],mp[ab%x][ab%y]++;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

$a_i+a_j$ 可被 $x$ 整除 $\to (a_i\bmod x + a_j\bmod x)\bmod x=0$。

$a_i-a_j$ 可被 $y$ 整除 $\to a_i\equiv a_j \pmod y$。

那么对于每个 $a_j$ 符合要求的 $i$ 就需要满足上述条件，也就是 $a_i\bmod x=(x-a_j\bmod x)\bmod x$ 并且 $a_i\bmod y=a_j\bmod y$。

所以对于每个 $a_i$ 先查询满足条件的对数，然后存下模 $x$ 和 $y$ 的余数，考虑使用 map 实现。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
int T,n,x,y,a[200005];
long long ans;
map<pii,int>m;
inline void sol()
{
	scanf("%d%d%d",&n,&x,&y),m.clear(),ans=0;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),ans+=m[mp((x-a[i]%x)%x,a[i]%y)],++m[mp(a[i]%x,a[i]%y)];
	printf("%lld\n",ans);
}
int main()
{
	scanf("%d",&T);
	while(T--) sol();
	return 0;
}
```

---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://codeforces.com/contest/1931/problem/D)

我们发现，对于每两个数 $a$ 和 $b$，如果这两个数符合题目要求，就表明：
$a$ 除以 $y$ 的余数等于 $b$ 除以 $y$ 的余数，$a$ 除以 $x$ 的余数加上 $b$ 除以 $x$ 的余数要么为 $0$，要么为 $x$。

有了这个结论，就可以开始编码。我们可以将数按除以 $y$ 的余数排序，这样保证除以 $y$ 的余数相等的数都挨在一起。再找到每一个连续的除以 $y$ 相等的区间，对于每一个除以 $x$ 的余数为 $p$ 的数，让答案加上数列里除以 $x$ 余数为 $x - p$ 的数的个数，如果 $p=x-p$，说明加上了自己，要减去 $1$，此外，如果 $p=0$，我们就要找除以 $x$ 余数为 $0$ 的个数，同样要减去一。

注意：要开长整型，注意边界问题。

## AC Code：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
int t, n, x, y;
struct node{
	int a, mod_x, mod_y;
};
node a[200100];
bool cmp(node a, node b) {
	return a.mod_y < b.mod_y;
}
long long ans;
map<int, int> cnt;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		ans = 0;
		cin >> n >> x >> y;
		for (int i = 1; i <= n; i ++) cin >> a[i].a;
		for (int i = 1; i <= n; i ++) {
			a[i].mod_x = a[i].a % x;
			a[i].mod_y = a[i].a % y;
		}
		sort(a + 1, a + n + 1, cmp);
		int i = 1;
		while (i <= n) {
			int l = i, r = i;
			while (a[l].mod_y == a[r].mod_y && r <= n) r++;
			r--;
			if (l == r) {
				i = r + 1;
				continue;
			}
			for (int j = l; j <= r; j++) {
				cnt[a[j].mod_x]++;
			}
			for (int j = l; j <= r; j++) {
				if (a[j].mod_x == 0) {
					ans += cnt[0];
					ans--;
				}
				else {
					ans += cnt[x - a[j].mod_x];
					if (a[j].mod_x * 2 == x) ans--;
				}
			}
			i = r + 1;
			cnt.clear();
		}
		ans /= 2;
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：I_am_kunzi (赞：0)

# CF1931D 题解

### 题目翻译

给你一个长度为 $ n $ 的数组 $ a$，求出满足以下条件的二元组 $ ( i , j ) $ 的数量：

+ $ 1 \le i < j \le n$；

+ $ (a_i + a_j) \bmod x = 0$；

+ $ (a_i - a_j) \bmod y = 0$。

### 题目思路

首先，我们将第一个式子变形，可得：$(a_i \bmod x + a_j \bmod x) \bmod x = 0$；

然后可得：$(a_i \bmod x + a_j \bmod x) = p \cdot x$，而且 $ p $ 是个整数；

因为：$0 \le a_i \bmod x < x $，$ 0 \le a_j \bmod x < x$；

所以：$0 \le a_i \bmod x + a_j \bmod x < 2 \cdot x$；

即：$0 \le p \cdot x < 2 \cdot x$；

上文说过，$p $ 是个整数，所以 $ p = 0 $ 或 $ 1$；

也就得到了：$(a_i \bmod x + a_j \bmod x) = 0 $ 或 $(a_i \bmod x + a_j \bmod x) = x$；

分别可以得到：$ a_i \bmod x = a_j \bmod x = 0 $ 和 $ a_i \bmod x = x - a_j \bmod x$；

又因为 $ (x - 0) \bmod x = 0$，所以两个式子的结构就被统一成了 $ a_i \bmod x = (x - a_j \bmod x) \bmod x$。

所以第一个式子变形完毕，相当于给定你 $ a_i \bmod x$，求出满足 $ a_i \bmod x = (x - a_j \bmod x) \bmod x$ 的 $ j $ 的个数。这个东西可以存到 ``` map < int , int > m; ``` 里。

同理，第二个式子，可得：$a_i \bmod y - a_j \bmod y = 0$；

所以：$a_i \bmod y = a_j \bmod y$。

这时我们发现，这个式子相当于给定你 $ a_i \bmod y$，求满足 $ a_i \bmod y = a_j \bmod y $ 的 $ j $ 的个数。这个东西可以和第一个结合起来，它们共同存到一个 ``` map < int , pair < int , int > > m; ``` 里。

所以此时这两个式子就相当于，给定你 $ a_i \bmod x $ 和 $ a_i \bmod y$，求满足以下条件的 $ j $ 的个数：

+ $ j < i$；

+ $ a_i \bmod x = (x - a_j \bmod x) \bmod x$；

+ $ a_i \bmod y = a_j \bmod y$。

所以我们每次查询 $ m_{(x - a_i \bmod x) \bmod x , a_i \bmod y} $ 的值，并让 $ m_{a_i \bmod x , a_i \bmod y} $ 的值增加 $ 1$。注意条件是 $ j < i$，所以要先查询后修改。

### 题目代码

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
#include<set>
#include<stack>
#include<limits.h>
#include<list>
using namespace std;
void solve()
{
	int n;
	long long x , y;
	scanf("%d%lld%lld" , &n , &x , &y);
	vector < long long > a(n);
	map < pair < int , int > , long long > m;
	for(int i = 1 ; i <= n ; i++)
	{
		scanf("%lld" , &a[i - 1]); // vector 从 0 下标开始，所以后面都是 a[i - 1]
	}
	long long ans = 0;
	for(int i = 1 ; i <= n ; i++) // 用推出来的式子求解，注意先查询后修改
	{
		ans += m[make_pair((x - a[i - 1] % x) % x , a[i - 1] % y)];
		m[make_pair(a[i - 1] % x , a[i - 1] % y)]++;
	}
	printf("%lld\n" , ans);
}
signed main()
{
	int t;
	scanf("%d" , &t);
	while(t--)
	{
		solve();
	}
	return 0;
}
```


---

## 作者：SamHJD (赞：0)

## Divisible Pairs

### Description

一对 $(i,j)$ 是美丽的仅当 $a_i+a_j\equiv0\pmod x$ 并且 $a_i-a_j\equiv0\pmod y$。找出序列 $a$ 中美丽的 $(i,j)$ 的个数。

### Solution

发现 $a_i-a_j\equiv0\pmod y$ 仅当 $a_i,a_j$ 模 $y$ 下同余，因此将 $a$ 以模 $y$ 的余数分组。

用 map 标记每一个数模 $x$ 下的余数，并记录每一个余数的出现次数。在某一组内，若 $a_i\equiv k\pmod x$，则调取模 $x$ 的余数为 $x-k$ 的数的个数计入答案。注意 $k=0$ 和 $2\times k=x$（不计算自己） 的情况。最终答案除以 $2$。

### [code](https://codeforces.com/contest/1931/submission/246350096)

---

## 作者：__Dist__ (赞：0)

数学题/oh

先考虑第一个条件：$a_i + a_j$ 能被 $x$ 整除。

可以转化为 $(a_i + a_j)\bmod x = 0$。

$$\because (a_i + a_j) \bmod x = 0$$

$$\therefore (a_i \bmod x + a_j \bmod x)\bmod x = 0$$

$$\therefore (a_i \bmod x + a_j \bmod x) \in \{0, x\}$$

所以对于一个 $j$，若满足 $a_i \bmod x = (x - a_j \bmod x) \bmod x$，那么 $a_i \bmod x + a_j \bmod x = 0$。

再考虑第二个条件。$a_i - a_j$ 能被 $y$ 整除。

第二个就简单多了。

$$\because(a_i - a_j) \bmod y = 0$$

$$\therefore a_i \bmod y - a_j \bmod y = 0$$

$$\therefore a_i \bmod y = a_j \bmod y$$

因为 $i < j$，所以从前往后遍历 $j$，用一个 `map` 记录前面符合条件的组数，每次增加答案即可。

```cpp
#include <bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long

using namespace std;

const int MAXN = 2e5 + 5;

ll n;
ll a[MAXN];
ll x, y;

ll read() {
	ll x = 0, f = 1;char ch = gt();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1;ch = gt();}
	while (ch >= '0' && ch <= '9') {x *= 10;x += ch - '0';ch = gt();}
	return x * f;
}

void solve() {
	n = read(); x = read(); y = read();
	for (int i = 1; i <= n; i++) {
		a[i] = read();
	}
	ll ans = 0;
	map<pair<ll, ll>, ll> mp;
	for (int i = 1; i <= n; i++) {
		ll p = a[i] % x, q = a[i] % y;
		ans += mp[{(x - p) % x, q}];
		mp[{p, q}]++;
	}
	cout << ans << '\n';
}

int main() {
	ll T = read();
	while(T--) 
		solve();
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

对于 $p$，$q$ 能和 $p$ 匹配的条件是 

$$\begin{cases}
q \equiv x-p \pmod x \\
q \equiv p \ \ \ \ \ \ \ \pmod y
\end{cases}$$

直接开桶记录每个数模 $x$ 和 $y$ 的余数，当前的数对答案的贡献就是前面的能匹配上的个数

```cpp
map <pii, int> mp;
void solve() {
	mp.clear();
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) cin >> a[i];
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += mp[{(x - a[i] % x) % x, a[i] % y}];
		mp[{a[i] % x, a[i] % y}]++;
	}
	cout << ans << '\n';
}
```

---

## 作者：wyyqwq (赞：0)

题意：给定序列 $a$ ，求序列中 $a[i] + a[j]$ 能被 $x$ 整除，$a[i] - a[j]$ 能被 $y$ 整除的对数。

 $a[i] - a[j]$ 被 $y$ 整除，即为 $a[i]$ 和 $a[j]$ 关于 $y$ 同余。对于关于 $y$ 同余的每对统计 $a[i] + a[j]$ 被 $x$ 整除的个数，用桶维护即可。

```c++
void solve() {
	map<int, map<int, int> > cnt;
	map<int, vector<int>> g;
	int n, x, y;
	cin >> n >> x >> y;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	int sum = 0;
	for(int i = 1; i <= n; i ++) {
		sum += cnt[a[i] % y][(x - a[i] % x) % x];
		cnt[a[i] % y][a[i] % x] ++;
		
	}
	cout << sum << endl;
}
```



---

## 作者：minVan (赞：0)

**题目大意**

$(p,q)$ 称作**好的**当且仅当 $x\mid p+q,y\mid p-q$。问 $\{a_i\}$ 中有多少对 $(a_i,a_j)$（$i<j$）是好的。

**解题思路**

用一个 map 来存 $a_i$ 分别模 $x,y$ 结果这一个数对的个数，对于 $a_i$，与其配成**好的**的个数为 `mp[{(x - a[i] % x) % x, a[i] % y}]`。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, x, y, a[N], b[N];
map<pair<int, int>, int> mp;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    mp.clear();
    cin >> n >> x >> y;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
      b[i] = a[i] % y;
      a[i] %= x;
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
      ans += mp[{(x - a[i]) % x, b[i]}];
      ++mp[{a[i], b[i]}];
    }
    cout << ans << '\n';
  }
  return 0;
}
```

ps：赛时脑回路新奇，用 map + bitset 成功 TLE on 3。

---

