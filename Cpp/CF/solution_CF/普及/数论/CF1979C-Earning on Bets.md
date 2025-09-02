# Earning on Bets

## 题目描述

You have been offered to play a game. In this game, there are $ n $ possible outcomes, and for each of them, you must bet a certain integer amount of coins. In the event that the $ i $ -th outcome turns out to be winning, you will receive back the amount of coins equal to your bet on that outcome, multiplied by $ k_i $ . Note that exactly one of the $ n $ outcomes will be winning.

Your task is to determine how to distribute the coins in such a way that you will come out ahead in the event of any winning outcome. More formally, the total amount of coins you bet on all outcomes must be strictly less than the number of coins received back for each possible winning outcome.

## 说明/提示

In the first test case, the coins can be distributed as follows: $ 27 $ coins on the first outcome, $ 41 $ coins on the second outcome, $ 12 $ coins on the third outcome. Then the total amount of coins bet on all outcomes is $ 27 + 41 + 12 = 80 $ coins. If the first outcome turns out to be winning, you will receive back $ 3 \cdot 27 = 81 $ coins, if the second outcome turns out to be winning, you will receive back $ 2 \cdot 41 = 82 $ coins, if the third outcome turns out to be winning, you will receive back $ 7 \cdot 12 = 84 $ coins. All these values are strictly greater than $ 80 $ .

In the second test case, one way is to bet one coin on each of the outcomes.

## 样例 #1

### 输入

```
6
3
3 2 7
2
3 3
5
5 5 5 5 5
6
7 9 3 17 9 13
3
6 3 2
5
9 4 6 8 3```

### 输出

```
27 41 12 
1 1 
-1
1989 1547 4641 819 1547 1071 
-1
8 18 12 9 24```

# 题解

## 作者：Just_A_Sentence (赞：11)

# 题意翻译

你正在玩一个游戏，在这个游戏中，一共有 $n$ 个可能的结果。你需要在每一种结果上下注一定量的硬币，如果第 $i$ 种结果胜利了，那么你将获得在这种结果上下注的硬币数的 $k_{i}$ 倍个硬币。请你设计一种下注的方案，使其确保你得到的硬币数大于你在每一种结果上下注的硬币和。

对于 $100\%$ 的数据，$1\le n\le 50,2\le k_{i}\le 20$；输入有 $t$ 组，$1\le t\le 10^4$，所有 $n$ 之和小于 $2\cdot 10^5$。

# 分析

对于第 $i$ 个结果，每下注 $\displaystyle \frac{1}{k_{i}}$ 个硬币就能期望获得 $1$ 个硬币，所以我们可以得到：设 $S=\sum_{i=1}^{n}{\displaystyle \frac{1}{k_{i}}}$，当 $S\ge 1$ 时，本题无解，当 $S<1$ 时，每种结果下注 $\displaystyle \frac{1}{k_{i}}$ 个硬币即可。但题目要求每种结果下注的硬币数必须是整数。所以要把每个 $\displaystyle \frac{1}{k_{i}}$ 乘上 $\operatorname{lcm}(k_1,k_2,\dots,k_n)$。由于 $k_{i}\le 20$，所以 $\operatorname{lcm}(k_1,k_2,\dots,k_n)$ 的最大值是 $\operatorname{lcm}(5,7,9,11,13,16,17,19)=232792560$，总和在 `long long` 范围内。

附代码：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long a[55];
long long gcd(long long a,long long b){
	if(b!=0) return gcd(b,a%b);
	return a;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		if(n==1){
			printf("1\n");
			continue;
		}
		if(n>=20){
			printf("-1\n");
			continue;
		}
		long long LCM=a[1]*a[2]/gcd(a[1],a[2]);
		for(int i=3;i<=n;i++){
			LCM=LCM*a[i]/gcd(LCM,a[i]);
		}
		long long ans=0;
		for(int i=1;i<=n;i++){
			ans+=LCM/a[i];
		}
		if(ans>=LCM){
			printf("-1\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			printf("%lld ",LCM/a[i]);
		}
		printf("\n");
	}
	return 0;
}
~~~

---

## 作者：wmrqwq (赞：10)

# 题目链接

[CF1979C (codeforces)](https://codeforces.com/contest/1979/problem/c)

[CF1979C (luogu)](https://www.luogu.com.cn/problem/CF1979C)

# 解题思路

我们发现，如果答案序列的和小于等于 $x$ 时是合法的，那么容易得出答案序列的和小于等于 $x + 1$ 时也是合法的。

因此我们发现答案序列的和的合法性是具有单调性的。

直接二分即可，答案中的每个数可以贪心 $O(1)$ 求出。

总时间复杂度 $O(n \log_2 V)$，其中 $V$ 为答案上界，这里我取了 $10^{12}$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n,a[100010],ans[100010];
bool check(ll Mid)//总和<=Mid 
{
	ll sum=0;
	forl(i,1,n)
	{
		ans[i]=ceil(1.0*Mid/a[i]);
		if(ans[i]<1)
			ans[i]=1;
		if(ans[i]>1e9)
			ans[i]=1e9;
		sum+=ans[i];
	}
	forl(i,1,n)
		if(sum>=ans[i]*a[i])
			return 0;
	return sum<=Mid;
}
void solve()
{
	cin>>n;
	forl(i,1,n)
		cin>>a[i];
	ll L=0,R=1e12;
	while(L<R)
	{
		ll Mid=(L+R+1)/2;
		if(check(Mid))
			L=Mid;
		else
			R=Mid-1; 
	}
	if(check(L))
	{
		forl(i,1,n)
			cout<<ans[i]<<' ';
		cout<<endl;
	}
	else
		cout<<-1<<endl;
}
int main()
{
	IOS;
	t=1;
	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1979C)

### 思路

首先需要判断是否全都能获胜。最终答案 $\times k_i$，所以在判断是否有解时应 $\times \frac{1}{k_i}$。第 $i$ 次下注的 $\frac{1}{k_i}$ 枚硬币都希望有收获。设 $S=\sum_{i=1}^n\frac{1}{k_i}$，若 $S\ge1$，那么无解。

求最后的答案，要求答案必须是整数，则要取它们的最小公倍数。设 $L=\operatorname{lcm}\left(k_1,k_2,K_3,\ldots,k_{n}\right)$，用一个变量 $ans$ 记录最终答案，则 $ans=\sum_{i=1}^n\frac{L}{x_i}$。

**注意事项**

- 不开 `long long` 见祖宗。

---

## 作者：Fesdrer (赞：6)

设对每个结果下注 $x_i$，则需满足：$\forall i,k_ix_i>S$，其中 $S=\sum x_i$。这一条件也可以写作 $x_i\ge\lfloor \frac S{k_i}\rfloor+1$。

因此对于一个 $S$，存在一种合法的下注方案当且仅当 $\sum_{i=1}^n(\lfloor\frac S{k_i}\rfloor+1)\ge S$。

此时对 $\sum \frac 1{k_i}$ 分类讨论。如果 $\sum \frac 1{k_i}<1$，则取 $S=\lceil\frac n{(1-\sum\frac 1{k_i})\operatorname{lcm}k_i}\rceil\operatorname{lcm}k_i$ 即可合法，只需要再取 $x_i=\lfloor \frac S{k_i}\rfloor+1$ 即可得到答案，如果此时的 $\sum x_i$ 比 $S$ 少则把少的部分补到 $x_1$ 即可。否则若 $\sum \frac 1{k_i}\ge1$，因为 $\lfloor \frac S{k_i}\rfloor+1>\frac S{k_i}$，因此无解。

```c++
#include<bits/stdc++.h>
using namespace std;
int k[30],ans[30];
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>k[i];
		int lcm=1;
		double now=0;
		for(int i=1;i<=n;i++){
			lcm=1ll*lcm*(k[i])/__gcd(lcm,k[i]);
			now+=1.0/k[i];
		}
		if(now>=1||fabs(now-1)<=1e-8){
			cout<<-1<<endl;
			continue;
		}
		lcm=lcm*ceil(n*1.0/lcm/(1-now));
		int sum=0;
		for(int i=1;i<=n;i++){
			ans[i]=lcm/k[i]+1;
			sum+=ans[i];
		}
		cout<<ans[1]+lcm-sum<<" ";
		for(int i=2;i<=n;i++)	cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：freoepn (赞：2)

设构造总和为 $sum$，第 $i$ 盘成功可以翻 $a_i$ 倍，构造中在第 $i$ 盘下注 $b_i$ 元。

可知对于 $\forall i$，$a_i \times b_i > sum$，即 $  b_i > \frac{sum}{a_i}$，因为 $sum = \sum_{i=1}^{n} b_i$，代入 $  b_i > \frac{sum}{a_i}$ 后可得 $sum >  \ sum \times \sum_{i=1}^{n}  \frac{1}{a_i}$，化简可得当 $\sum_{i=1}^{n}  \frac{1}{a_i} \geq 1$ 时，无获利方案。

对于有解情况，可以提出 $a_i$ 的最小公倍数 $e$ ，令 $ \forall  b_i = \frac{e}{a_i}$，则无论哪盘赢都可以得到 $e$ 的收益，又因为 $\sum_{i=1}^{n}  \frac{1}{a_i} < 1$，$sum $ 一定小于 $e$，即任何情况都获利。

---

## 作者：zhanglh (赞：2)

猜结论。

对 $k_1, k_2, \dots, k_n$ 求 $\text{LCM}$，记为 $L$。考虑给第 $i$ 个的花费为 $\lfloor \displaystyle \frac{L}{k_i} \rfloor$。

若任意 $i$ 都满足 $k_i \times \lfloor \displaystyle \frac{L}{k_i} \rfloor$ 严格大于 $\sum_{i = 1}^{n}~\lfloor\displaystyle \frac{L}{k_i} \rfloor$，则有解，反之无解。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#define pb push_back

using namespace std;

typedef long long ll;

const int N = 60;

ll n, a[N];

inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

inline ll f(ll x) {
    ll res = x;
    for (int i = 3; i <= n; i ++ ) res = res * a[i] / gcd(res, a[i]);
    return res;
}

inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    if (n == 1) {
        puts("1");
        return;
    }
    ll lcm = f(a[1] * a[2] / gcd(a[1], a[2]));
    vector<ll> v;
    ll sum = 0;
    for (int i = 1; i <= n; i ++ ) {
        sum += lcm / a[i];
        v.pb(lcm / a[i]);
    }
    for (int i = 0; i < n; i ++ ) {
        if (a[i + 1] * v[i] <= sum) {
            puts("-1");
            return;
        }
    }
    for (int i = 0; i < n; i ++ ) cout << v[i] << " ";
    puts("");
}

int main() {
    int T; cin >> T;
    while (T -- ) solve();
    return 0;
}
```

---

## 作者：ttq012 (赞：1)

upd：已通过题解更新了一点 typo。

又是猜结论题。设 $L=\operatorname{lcm}(k_1,k_2,k_3,\ldots,k_n)$ 的值。很显然有 $L\le \text{lcm}(2^4,3^2,5,7,11,13,17,19)<10^9$。然后考虑给每一个位置分配 $\frac{L}{k_i}$ 的钱，最后 check 一下是否是满足条件的一组方案即可。

时间复杂度为 $O(n)$。

```cpp
auto main() [[O3]] -> signed {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        F(i, 1, n) cin >> a[i].x, a[i].id = i;
        // stable_sort(a + 1, a + n + 1, [&](auto l, auto r) {
        //     return l.x < r.x;
        // });
        int res = a[1].x;
        F(i, 2, n) res = ll(res, a[i].x);
        F(i, 1, n) b[i] = res / a[i].x;
        int s = accumulate(b + 1, b + n + 1, 0ll);
        bool ok = true;
        F(i, 1, n) {
            if (s >= b[i] * a[i].x) {
                ok = false;
                break;
            }
        }
        if (ok) {
            F(i, 1, n) {
                cout << b[i] << ' ';
            }
            cout << '\n';
        } else {
            cout << "-1\n";
        }
    }
}
```

---

## 作者：DDF_ (赞：0)

## 题面

给定长度为 $n$ 一个数组 $k$，构造一个长度也为 $n$ 的数组 $s$，使得 $\forall i \in [1,n],~ s_{i} \times k_{i}> \sum_{j=1}^{n}s_{j}$。

## 题解

设 $m=\sum_{j=1}^{n}s_{j}$。

则有 $\forall i \in [1,n],~ s_{i}> \frac{m}{k_{i}}$。

为了使得 $m$ 可整除所有的 $k_{i}$，令 $m=\operatorname{lcm}_{i=1}^{n}{k_{i}}$。

此时设数组 $t$ 满足 $\forall i \in [1,n],t_{i}=\frac{m}{k_{i}}$，则有 $\forall i \in [1,n],s_{i}>t_{i}$。

若 $\sum_{i=1}^{n} t_{i} \ge m$，那么就有 $\sum_{i=1}^{n}s_{i} > m$，与一开始 $m$ 的定义产生矛盾，无解。

若 $\sum_{i=1}^{n} t_{i} < m$，有解，考虑构造 $s$ 数组。

发现 $m> \sum_{i=1}^{n} t_{i}$ 时，$\frac{m}{k_{i}} >\frac{\sum_{i=1}^{n} t_{i}}{k_{i}}$，那么就有 $t_{i} \times k_{i}> \sum_{i=1}^{n} t_{i}$，这就是题面中要求的式子。

所以令 $s_{i}=t_{i}$ 即为一种可行解。

注意开 `long long`。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
ll n,k[52];
ll m,s[52],sum;
int gcd(int a,int b) {
	if(b==0) return a;
	return gcd(b,a%b);
}
void work() {
	scanf("%lld",&n),m=1,sum=0;
	for(int i=1;i<=n;i++) scanf("%lld",&k[i]),m=m?m*k[i]/gcd(m,k[i]):k[i];
	for(int i=1;i<=n;i++) sum+=m/k[i];
	if(sum>=m) {puts("-1");return;}
	for(int i=1;i<=n;i++) printf("%lld ",m/k[i]);
	puts("");
	return;
}
int main() {
	scanf("%d",&t);
	while(t--) work();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

人类智慧题。

结论很好想，对于每一次下注的整数 $a_i$，设 $ans=\operatorname{lcm}(a_1,a_2,\dots,a_n)$，当第 $i$ 种结果为赢的时候需要将 $\lfloor ans \div a_i \rfloor$，则另开一个变量 $tot$，循环累积 $\lfloor ans \div a_i \rfloor$，再将 $tot$ 和 $ans$ 进行比较即可。若 $ans \le tot$，则输出 $-1$，反之输出 $\lfloor ans \div a_i \rfloor$。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[55];
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int lcm(int a,int b){
	return a*b/gcd(a,b);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int ans=a[1];
		for(int i=2;i<=n;i++){
			ans=lcm(ans,a[i]);
		}
		int tot=0;
		for(int i=1;i<=n;i++){
			tot+=ans/a[i];
		}
		if(tot>=ans){
			cout<<-1<<"\n";
			continue;
		}
		for(int i=1;i<=n;i++){
			cout<<ans/a[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Beacon_wolf (赞：0)

## 题目思路
猜结论。

对 $k_1,k_2,\dots,k_n,k_n$，求最小公倍数，设此值为 $x$，则累加 $x$ 分别除以 $k_1,k_2,\dots,k_n$ 的和，如果此值大于 $x$，则无解。否则，给第每个位置分配 $\frac{x}{k_i}$ 数量的钱即可。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[55];
long long gcd(long long a,long long b){
	if(b == 0) return a;
	return gcd(b,a % b); 
}
long long lcm(long long a,long long b){
	return a * b / gcd(a,b);
} 
void solve(){
	int n;
	cin >> n;
	bool ok = 0;
	long long g = 0,sum = 0;
	cin >> a[1];
	g = a[1];
	for(int i = 2;i <= n;i++){
		cin >> a[i];
		g = lcm(g,a[i]);
	}
	for(int i = 1;i <= n;i++){
		sum += g / a[i];
	}
	for(int i = 1;i <= n;i++){
		if(g <= sum){
			cout << -1;
			ok = 1;
			break;
		}
	}
	if(!ok){
		for(int i = 1;i <= n;i++){
			cout << g / a[i] << " ";
		}
	}
	cout << endl;
}
int main(){
	int t;
	cin >> t; 
	while(t--){
		solve();
	}
	return 0;
} 
```

---

## 作者：ZhongYuLin (赞：0)

我们把事件按 $k_i$ 从小到大排序。

我们不妨假设你现在在**第一个**下注总共 $x_1$ 个硬币。更强一点，同时也为了方便说明与实现，$x_1=10^9$。为了尽可能节省硬币，显然你在第 $i$ 个只会下注 $\frac{x_{i-1}}{a_{i-1}}a_i$ 个硬币。依次把硬币数算出来，再扫一遍检查是否成立即可。

---

## 作者：weilycoder (赞：0)

赛时 A 了，但我不敢保证这是正解（但是求过方便大家 Hack）。

显然要保证每个 $k_ix_i$ 都大于某个特定的数，即 $S=x_1+x_2+\dots+x_n$。由于题目未要求给出最小解，又保证了 $x_i\le 10^9$，我们不妨令 $M=\min\{k_i\}\times 10^9$，$y_i=\left\lceil\dfrac{M}{k_i}\right\rceil$，若 $\sum y_i<M$，则构造成功。

不幸的是，这样的算法无法通过测试。

可是数据范围只有 $2\times 10^5$，而我们的算法是 $O(n)$ 的！

我们还有充足的时间乱搞。

显然错误的原因是误判了本来能构造的数据，不妨多取一些 $M$，全部构造失败再输出 $-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const long long M = 1000000000;
const int N = 54;
long long n, a[N], b[N];
 
bool check(long long k) {
  for (int i = 1; i <= n; ++i) b[i] = ceill((long double)k / a[i]);
  long long sum = 0;
  for (int i = 1; i <= n; ++i) sum += b[i];
  for (int i = 1; i <= n; ++i)
    if (a[i] * b[i] <= sum) return false;
  return true;
}
 
void solve() {
  cin >> n;
  long long m = 20;
  for (int i = 1; i <= n; ++i) cin >> a[i], m = min(a[i], m);
  m *= M;
  for (long long i = 0; i <= 200; ++i) {
    if (check(m - i)) {
      for (int i = 1; i <= n; ++i) cout << b[i] << " ";
      cout << "\n";
      return ;
    }
  }
  cout << "-1\n";
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--) solve();
  return 0;
}
```

最后提一句正解，官方题解说 $M$ 使用 $\operatorname{lcm}(k_1,k_2,\dots,k_n)$ 即可。

---

