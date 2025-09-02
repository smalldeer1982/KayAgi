# Wonderful Gloves

## 题目描述

你是许多彩色手套的骄傲拥有者，并将它们存放在一个抽屉里。每只手套的颜色编号为 $1$ 到 $n$。具体来说，对于每个 $i$（从 $1$ 到 $n$），你有 $l_i$ 只左手手套和 $r_i$ 只右手手套，颜色均为 $i$。

不幸的是，现在是深夜，你无法看清任何手套的颜色。换句话说，只有当你从抽屉中取出手套时，才能知道它的颜色和类型（左手或右手）。

颜色为 $i$ 的一副匹配手套由一只左手手套和一只右手手套组成（颜色均为 $i$）。请计算你需要从抽屉中取出的最少手套数量，以确保至少有 $k$ 副不同颜色的匹配手套。

形式化地说，找到最小的正整数 $x$，满足：
- 无论你从抽屉中取出哪 $x$ 只手套，总能保证至少有 $k$ 副不同颜色的匹配手套。

## 说明/提示

在第一个测试用例中，你必须取出所有手套，因此答案是 $6$。

在第二个测试用例中，答案是 $101$。如果你取出 $100$ 只或更少的手套，那么可能所有取出的都是左手手套，这意味着你无法得到任何一副匹配手套。

在第三个测试用例中，答案是 $303$。如果你只取出 $302$ 只手套，那么可能出现以下情况：
- 颜色 $1$：$100$ 只左手手套，$200$ 只右手手套
- 颜色 $2$：$1$ 只左手手套，$0$ 只右手手套
- 颜色 $3$：$0$ 只左手手套，$1$ 只右手手套

此时你只有颜色 $1$ 的多副匹配手套，无法满足至少 $2$ 副不同颜色匹配手套的要求。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3 3
1 1 1
1 1 1
1 1
100
1
3 2
100 1 1
200 1 1
5 2
97 59 50 87 36
95 77 33 13 74
10 6
97 59 50 87 36 95 77 33 13 74
91 14 84 33 54 89 68 34 14 15```

### 输出

```
6
101
303
481
1010```

# 题解

## 作者：_Star_Universe_ (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF2096B)

### 题意 & 思路
现在你拥有 $n$ 只彩色手套，编号从 $1$ 到 $n$。$i$ 代表一种颜色。对于每个 $i$，有 $l_i$ 只左手套和 $r_i$ 只右手套。现在请你求出最小的正整数 $x$，满足：
- 无论你从抽屉中取出哪 $x$ 只手套，总能匹配出 $k$ 副不同颜色的手套。

这道题的最坏情况是：你取了每种颜色的左/右手套中数量多的那个，即对于每个 $i$ 取 $\max(l_i,r_i)$ 加到 $ans$ 中，剩下的部分再取每种颜色的左/右手套中少的部分，存在数组 $a$ 中，即 $a_i=\min(l_i,r_i)$，因为 $ans$ 要最小需将 $a$ 数组升序排列，最后再将前 $k-1$ 个 $a_i$ 加到 $ans$ 中，再随便拿一个，可以保证匹配成功，答案是按照上述方法得到的 $ans+1$。

[代码](https://www.luogu.me/paste/3btx8eh4)。

---

## 作者：Baiqi_0327 (赞：1)

CF2096B
---

### 题目概述
你有 $n$ 种颜色的手套，每个手套为颜色 $i$ 左手有 $l_i$ 只，右手有 $r_i$ 只。但是伸手不见五指，你只能凭最坏的情况凑出至少 $k$ 副手套，求问最少要摸出来多少只？

### 思路
最坏的情况清晰可见：把一边的手套全部抽完了，也就是一幅配对的可能都没有，为 $\sum^n_{i=1}\max(l_i,r_i)$，我们用 $M$ 表示。在这个条件下，之后的每一次抓取都会出现配对，这个时候求 $\sum^n_{i=1}\min(l_i,r_i)$ 的前面 $k-1$ 项并用 $S$ 表示（和），最后输出 $M+S+1$ 即可，因为需要额外那出来的配对数量至少为 $S+1$。

### 代码
#include 
```cpp
<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200000;
ll l[N], r[N], b[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n >> k;
        for(int i = 0; i < n; i++) cin >> l[i];
        for(int i = 0; i < n; i++) cin >> r[i];
        ll M = 0;
        for(int i = 0; i < n; i++){
            M += max(l[i], r[i]);
            b[i] = min(l[i], r[i]);
        }
        sort(b, b + n, greater<ll>());
        ll S = 0;
        for(int i = 0; i < k-1; i++) S += b[i];
        cout << M + S + 1 << "\n";
    }
    return 0;
}
```

---

## 作者：cute_zczc_qwq (赞：1)

# [CF2096B](https://www.luogu.com.cn/problem/CF2096B) Wonderful Gloves

刚开始先说两句闲话，发现有些题解的代码样例都过不了，应该在每个测试用例开始前先清空答案，还有排序左手和右手中的最小值时应该从大到小，并非从小到大。

## 题意分析
你有 $n$ 种手套，编号从 $1$ 到 $n$，第 $i$ 种手套左手有 $l_{i}$ 只，右手有 $r_{i}$ 只，你要找到最小的 $ans$ 使从手套中取出任意 $ans$ 只手套都能凑出 $k$ 对 __不同__ 颜色的手套。拿出一副匹配手套指你拿出了至少 $1$ 只第 $i$ 种左手手套和至少 $1$ 只第 $i$ 种右手手套。

### 思路
我们很容易就能想到如何保证能拿到 $k$ 中不同颜色手套。考虑最不利的情况。我们拿出 $n$ 种手套中左右手中的最大值，即如果左手比右手多，我们就把全部左手拿走，其它情况我们就把全部右手拿走。

我们目前仍凑不出任意一副手套。接下来，我们把每种手套左右手数量中的最小值存到 $a$ 数组中，从大到小排序。接着我们从数组中依次拿出 $k-1$ 只左右手手套中的最小值。

现在我们已经有了 $k-1$ 对不同颜色的手套。因为我们已经有了其它我们还没有的颜色的手套的某只手的全部，所以我们现在随便拿一只剩下的手套就是最终答案。时间复杂度 $O(nt)$。 

代码仅供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct cf2096b{
    int l;
    int r;
}a[200005];
bool cmp(int a,int b){
    return a > b;
}
int main(){
    long long t,n,k,ans;
    int b[200005];
    cin>>t;
    for(int i = 1;i <= t;i++){
        cin>>n>>k;
        ans = 0;
        for(int j = 1;j <= n;j++){
        	cin>>a[j].l;
		}
		for(int j = 1;j <= n;j++){
			cin>>a[j].r;
		}
		for(int j = 1;j <= n;j++){
			ans += max(a[j].l,a[j].r);
			b[j] = min(a[j].l,a[j].r);
		}
		sort(b+1,b+n+1,cmp);
		for(int j = 1;j < k;j++){
			ans += b[j];
		}
        ans++;
        cout<<ans<<endl;
    }
    return 0;
}
//通过样例，其它暂时不知道。
```

---

## 作者：Eason_cyx (赞：1)

第 $\bf{103}$ 篇题解。

----

抽屉原理板子题。

最坏的情况显然是先把每种颜色的较多的那一半全部都拿了出来，也就是 $\sum \max(l_i,r_i)$。然后此时，因为题目要求是颜色不一样的 $k$ 双手套，所以再将 $\min(l_i,r_i)$ 中前 $k-1$ 个拿出来，再随便拿一只，就可以保证满足题目条件了。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[200005], b[200005], c[200005];
signed main() {
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        for(int i = 1;i <= n;i++) cin >> a[i];
        for(int i = 1;i <= n;i++) cin >> b[i];
        int sum = 0;
        for(int i = 1;i <= n;i++) sum += max(a[i], b[i]);
        for(int i = 1;i <= n;i++) c[i] = min(a[i], b[i]);
        sort(c+1, c+n+1, greater<int>());
        for(int i = 1;i < k;i++) sum += c[i];
        cout << sum+1 << endl;
    }
    return 0;
}
```

---

## 作者：Yuexingfei_qwq (赞：1)

咕值一落兆丈了。
## 思路  
问题总体可以转化为：找到最小的 $x$，使得取出 $x$ 只手套时，无论如何分配，都能保证至少有 $k$ 对匹配手套。换句话说，如果取出 $x - 1$ 只手套时，可能存在最多 $k - 1$ 对匹配手套的情况。因此，需要计算在最多 $k - 1$ 对匹配手套的情况下，最多能取出多少只手套 $y$，然后答案就是 $y + 1$。

接着可以发现，对于每种颜色 $i$，可以选择只取左手手套或只取右手手套（避免形成匹配对），此时取出的数量 $ma_i = max\{l_i, r_i\}$。剩余的未取出的手套数量为 $mi_i = min\{l_i, r_i\}$，这些手套可以用于形成匹配对。如果允许最多 $m = k - 1$ 对匹配手套，那么可以从 $b_i$ 中选择最多 $m$ 个最大的值，将这些手套也取出（即形成匹配对）。

代码就不讲了，自己看吧。

## AC CODE  
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a / __gcd(a, b) * b
#define setp(x) fixed << setprecision(x)
#define getmid(l, r) l + (r - l) / 2

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned long long;

int t;
int n, k;
int l[210000], r[210000], mi[210000];

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> k;
		F(i, 1, n, 1) {
			cin >> l[i];
		}
		int tot = 0;
		F(i, 1, n, 1) {
			cin >> r[i];
			mi[i] = std::min(l[i], r[i]);
			tot += std::max(l[i], r[i]);
		}
		std::sort(mi + 1, mi + n + 1, std::greater<int>());
		F(i, 1, k - 1, 1) {
			tot += mi[i];
		}
		cout << tot + 1 << el;
	}
	r0;
}
//Yuexingfei_qwq is a flying-wind
```

[AC 记录](https://codeforces.com/problemset/submission/2096/317574033)

--- 
完结~~不~~散花。

---

## 作者：co7ahang (赞：0)

# 题意

给你 $n$ 种手套，第 $i$ 种手套有左手套 $l_i$ 只，右手套 $r_i$ 只。找到最小值 $x$ 使得选择任意 $x$ 只手套，总能保证有 $k$ 副不同的手套。

# 思路

数学题，贪心。

这道题需要使用[抽屉原理（鸽巢原理，the pigeonhole principle）](https://oi-wiki.org/math/combinatorics/drawer-principle/)进行贪心。

> 把多于 $n$ 个的物体放到 $n$ 个抽屉里，则至少有一个抽屉里的东西不少于两件。
>
> 证明（反证法）：如果每个抽屉至多只能放进一个物体，那么物体的总数至多是 $n$，而不是题设的 $n + k \ (k \geq 1)$，故不可能。

如果每副手套左右各只有一只，答案为 $n + k$。此时的策略是先取每种手套的一只，然后取 $k$ 次另外一只。此时种类数为 $k$。

如果每副手套左右有若干只，考虑最差的情况，先取完每种手套的某一只手，再选取 $k$ 种手套取另外一只手。使用贪心法，先取每种手套较多的一只手，再降序排列取 $k - 1$ 种另一只手，最后再任意取 $1$ 只，此时种类数为 $k$。若 $(l_i, r_i)$ 按照 $\min(l_i, r_i)$ 降序排序，答案就是 $\sum_{i = 1}^n \max(l_i, r_i) + \sum_{i = 1}^{k - 1} \min(l_i, r_i) + 1$。

# 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdint>
const int N = 2e5 + 10;
const int P = 1e9 + 7;
#define int int64_t
namespace IO {
	inline int read() {
		int x = 0, f = 1; char ch = getchar();
		while(ch > '9' || ch < '0') {
			if(ch == '-') f = -1; 
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch - 48), ch = getchar();
		return x * f;
	}
	void write(int x) {
		if(x < 0) {
			x = -x;
			putchar('-');
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
		return;
	}
}
namespace math {
	int qpow(int a, int x){
		int ans = 1;
		while(x) {
			if(x & 1) ans = ans % P * a % P;
			a = a * a % P;
			x >>= 1;
		}
		return ans;
	}
	int exgcd(int a, int b, int &x, int &y) {
		if(b == 0) {
			x = 1, y = 0;
			return a;
		}
		int d = exgcd(b, a % b, x, y);
		int xp = x;
		x = y;
		y = xp - a / b * y;
		return d;
	}
}
using namespace std;
using IO::read, IO::write;
using math::qpow;
int n, k;
int l[N], r[N];
void solve() {
	//clear
	//end clear
	n = read(); k = read();
	for(int i = 1; i <= n; i++) l[i] = read();
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		r[i] = read();
		if(l[i] > r[i]) swap(l[i], r[i]);
		ans += r[i];
	}
	sort(l + 1, l + n + 1, greater <int> ());
	for(int i = 1; i < k; i++) ans += l[i];
	ans++;
	cout << ans << "\n";
	return void(0);
}
int32_t main() {
	//int T = read();
	int T = read();
	while(T--) solve();
	return 0;
}//qwq
```
通过记录： <https://codeforces.com/contest/2096/submission/319027880>

---

## 作者：Never_care (赞：0)

根据题意可知此题为最不利原则。为了使取出的手套尽可能不配对，每种颜色取出 $\min(l_i,r_i)$，即每种颜色中左手和右手相比较多的数量，一共要取 $k$ 种颜色的手套。然后再在 $k-1$ 种颜色的手套中取出左手和右手象鼻较少的数量。对于剩下的手套任意取出一只肯定可以构成配对。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
using namespace std;
const int N=2e5+5;
int a[N],b[N],c[N];
int t,n,k;
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		int cnt=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
			cnt+=max(a[i],b[i]);
			c[i]=min(a[i],b[i]);
		}
		sort(c+1,c+n+1,cmp);
		for(int i=1;i<k;i++){
			cnt+=c[i];
		}
		cout<<cnt+1<<'\n';
	}
  return 0;
}
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
你有 $n$ 种不同颜色的袜子，每种颜色的左袜子和右袜子分别有 $l_i$ 只和 $r_i$ 只。问你最少要拿出多少只袜子才能使得一定有 $k$ 种不同颜色的袜子至少有一双。
## 题目解法
一个十分明显的数学题，我们思考什么情况最倒霉呢？那就是你拿了每种袜子左右只数的最大数量，拿了 $k-1$ 种袜子左右只数的最小数量，最后你不管拿哪种袜子总会使得有 $k$ 种不同颜色的袜子至少有一双。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 2e5 + 10;

int a[kMaxN], t, n, k, ans;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; ans = 0) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1, x; i <= n; i++) {
      cin >> x, ans += max(a[i], x), a[i] = min(a[i], x);
    }
    sort(a + 1, a + 1 + n, [](int x, int y) { return x > y; });
    for (int i = 1; i < k; i++) {
      ans += a[i];
    }
    cout << ans + 1 << '\n';
  }
  return 0;
}
```

---

## 作者：TLE_qwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2096B)
#### 核心思路
- 最坏情况计算：首先假设我们尽可能取不配对的手套，也就是每种颜色都取较多的一侧。
- 确保配对：为了确保 $k$ 对配对，我们需要：
   - 选择 $k$ 种颜色，在这些颜色上额外取手套。
   - 优先选择 $L[i]$ 和 $R[i]$ 的较小值较大的颜色（因为这些颜色更容易形成配对）。

#### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> L(n), R(n);
    for (int i = 0; i < n; ++i) cin >> L[i];
    for (int i = 0; i < n; ++i) cin >> R[i];
    long long s = 0;
    vector<int> m;
    for (int i = 0; i < n; i++) {
        s += max(L[i], R[i]);
        if (L[i] && R[i]) {
            m.push_back(min(L[i], R[i]));
        }
    }
    sort(m.begin(), m.end(), greater<int>());
    for (int i = 0; i < k - 1; i++) {
        s += m[i];
    }
    cout << s + 1 << endl;
}
int main(void) {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---

## 作者：chatoudp (赞：0)

首先，我们先取出尽量多的手套使得没有一对同色的，也就是把每种颜色的左、右中那个多就加到 $ans$ 里。

然后我们取出 $k-1$ 种颜色的一对手套，排个序就好，然后无论取那个都一定会达成要求了。

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,n,a[200005],b[200005],k,c[200005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		long long sum=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) scanf("%d",&b[i]),sum+=max(a[i],b[i]),c[i]=min(a[i],b[i]);
		sort(c+1,c+n+1); 
		for(int i=n;i>=n-k+2;i--) sum+=c[i];
		printf("%lld\n",sum+1);
	}
	return 0;
}

```

---

