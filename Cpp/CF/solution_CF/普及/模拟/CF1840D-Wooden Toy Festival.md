# Wooden Toy Festival

## 题目描述

In a small town, there is a workshop specializing in woodwork. Since the town is small, only three carvers work there.

Soon, a wooden toy festival is planned in the town. The workshop employees want to prepare for it.

They know that $ n $ people will come to the workshop with a request to make a wooden toy. People are different and may want different toys. For simplicity, let's denote the pattern of the toy that the $ i $ -th person wants as $ a_i $ ( $ 1 \le a_i \le 10^9 $ ).

Each of the carvers can choose an integer pattern $ x $ ( $ 1 \le x \le 10^9 $ ) in advance, different carvers can choose different patterns. $ x $ is the integer. During the preparation for the festival, the carvers will perfectly work out the technique of making the toy of the chosen pattern, which will allow them to cut it out of wood instantly. To make a toy of pattern $ y $ for a carver who has chosen pattern $ x $ , it will take $ |x - y| $ time, because the more the toy resembles the one he can make instantly, the faster the carver will cope with the work.

On the day of the festival, when the next person comes to the workshop with a request to make a wooden toy, the carvers can choose who will take on the job. At the same time, the carvers are very skilled people and can work on orders for different people simultaneously.

Since people don't like to wait, the carvers want to choose patterns for preparation in such a way that the maximum waiting time over all people is as small as possible.

Output the best maximum waiting time that the carvers can achieve.

## 说明/提示

In the first example, the carvers can choose patterns $ 1 $ , $ 7 $ , $ 9 $ for preparation.

In the second example, the carvers can choose patterns $ 3 $ , $ 30 $ , $ 60 $ for preparation.

In the third example, the carvers can choose patterns $ 14 $ , $ 50 $ , $ 85 $ for preparation.

## 样例 #1

### 输入

```
5
6
1 7 7 9 9 9
6
5 4 2 1 30 60
9
14 19 37 59 1 4 4 98 73
1
2
6
3 10 1 17 15 11```

### 输出

```
0
2
13
0
1```

# 题解

## 作者：MornStar (赞：7)

# CF1840D Wooden Toy Festival 题解

[CF题面](https://codeforces.com/problemset/problem/1840/D)
## 题目大意
给定 $n$ 和一个长度为 $n$ 的序列 $k$，然后选择任意三个数 $a$，$b$，$c$，使得 $\max_{i=1}^{n}\{\min\{\left | k_i-a \right |$，$\left | k_i-b \right |$，$\left | k_i-c \right |\}\}$ 最小。

输出这个最小值。

$1\le n\le2\times 10^5$。

$1\le k_i\le10^9$。
## 思路
将数组从小到大排序。

容易发现，整个序列可以分成连续三部分。在第一部分中：$\min\{\left | k_i-a \right |$，$\left | k_i-b \right |$，$\left | k_i-c \right |\}=\left | k_i-a \right |$，另外两个部分同理。

而对于第一个区间 $[1,r]$，因为其单调不递减，容易得到 

$$\begin{aligned} \max_{i=1}^{r}\{\min\{\left | k_i-a \right |,\left | k_i-b \right |,\left | k_i-c \right |\}\} &= \max_{i=1}^{r}\{\left | k_i-a \right |\} \\ &=\max\{\left | k_1-a \right |,\left | k_r-a \right |\} \end{aligned}$$

这时候，问题来到了如何找到一个 $a$ 使得 $\max\{\left | k_1-a \right |,\left | k_r-a \right |\}$ 最小。

很明显，当 $a=\lceil \frac{k_1+k_r}{2} \rceil$ 时这个值最小，为 $\lceil \frac{k_r-k_1}{2} \rceil$，另外两个区间以此类推。

借此，我们可以枚举三个区间的两个交界处来确定三个区间 $O(1)$ 计算贡献。

于是，我们可以写出以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans;
int main(){
	int T;
	cin>>T;
	while(T--){
		bool flag=0;
		ans=INT_MAX;
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>a[i];
		if(n<=3){
			cout<<0<<"\n";
			continue;
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n-2;i++){
		//i为第一个区间的右端点
			if((a[i]-a[1]+1)/2>=ans)	break;
			//如果前面的区间和已经大于目前最优答案，在枚举下去就没有必要了。
			for(int j=i+1;j<=n-1;j++){
			//j为第二个区间的右端点
				if((a[j]-a[i+1]+1)/2>=ans)	break;
				ans=min(ans,(max(max(a[i]-a[1],a[j]-a[i+1]),a[n]-a[j+1])+1)/2);
			}
		}
		cout<<ans<<"\n";
	}
}
```
时间复杂度 $O(n^2)$，并不能通过此题。

让我们想一想如何去优化。

首先，在第一个区间右端点确定的情况下，剩下的两个区间最大值要尽可能小，那么剩余两个区间产生的贡献就要尽可能相等（想一想，为什么）。

因为第二个区间的右端点越往后，$k_r$ 的值就越大，即第二个区间的贡献越来越大，同时第三个区间的贡献越来越小。

于是，我们可以想到一个思路——二分。

如果第二个区间的贡献比第三个区间的贡献小，则第二个区间的右端点还可以往后移。

否则第二个区间的右端点只能往前移。

## AC code
```cpp
// by mornstar
// Jun/07/2023 00:27
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans;
int main(){
	int T;
	cin>>T;
	while(T--){
		ans=INT_MAX;
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>a[i];
		if(n<=3){
			cout<<0<<"\n";
			continue;
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n-2;i++){
			if((a[i]-a[1]+1)/2>=ans)	break;
			//同上
			int l=i+1,r=n;
			while(l<r){
				int mid=(l+r)>>1;
				ans=min(ans,(max(max(a[i]-a[1],a[mid]-a[i+1]),a[n]-a[mid+1])+1)/2);
				if((a[mid]-a[i+1]+1)/2<=(a[n]-a[mid+1]+1)/2)	l=mid+1;
				else	r=mid;
			}
			//二分
		}
		cout<<ans<<"\n";
	}
}
```
时间复杂度 $O(n\log n)$。


---

## 作者：xing_yue (赞：5)

# Wooden Toy Festival题解
[题目传送门](https://www.luogu.com.cn/problem/CF1840D)
## 大致题意
给定一个 $n$ 和一个长度为 $n$ 的序列 $k$。对于这个序列，我们需要选数任意三个数 $a$，$b$，$c$，使得 max{min{$\mid$$k_i - a$$\mid$,$\mid$$k_i - b$$\mid$,$\mid$$k_i - c$$\mid$}} 最小。

其中  $1 \le n \le 2 * 10^5$，$1 \le k_i \le 10^9$。

## 解题思路
首先，我们看到题目中要求**最大的最小**，也就是答案具有单调性，所以我们考虑使用**二分答案**。

那么，我们就需要考虑：

1. **二分边界**

	因为我们是二分这个答案，所以 $l$（左边界）应该为 $0$，而 $r$（右边界）就应该为答案可能达到的最大值 $10^9$。

2. **$check()$函数**

	根据绝对值的意义，我们可以把 check 转化为**区间选点**问题，只要我们最终选出来的点数**不超过 $3$ 个**，就是一个可行的答案了。而第 $i$ 个区间的左端点 $l_r$ 则为 $k_i - mid$， 右端点 $r_i$ 则为 $k_i + mid$。
    
## 代码实现
```cpp
/*CN*/
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
int n, T, a[N];
struct xs {
	int l, r;
}t[N];
bool cmp(xs a, xs b) {
	return a.r < b.r;
}
bool check(int x) {   //转化为区间选点，是否能选不超过3个点
	for (int i = 1; i <= n; i++) {
		t[i].l = a[i] - x;
		t[i].r = a[i] + x; 
	}
	sort(t + 1, t + n + 1, cmp);
	int ans = 1, f = t[1].r;
	for (int i = 2; i <= n; i++) {
		if (t[i].l > f) {
			f = t[i].r;
			ans++;
		} 
	}
	return ans <= 3;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) { //注意多组测试数据
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		int l = 0, r = 1e9;//二分边界
		while (l <= r) {
			int mid = (l + r) / 2;
			if (check(mid)) {
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		cout << r + 1 << "\n"; 
	}
	return 0;
}

```


---

## 作者：Jerry_heng (赞：5)

（一）

比赛结束前 $5$ 分钟才调出来。

二分答案。先排序，然后从左往右搜，看是否能在 $3$ 次以内处理完。

由于是绝对值，控制左右数之差 $\le$ 选定的数 $x$。

每次固定左节点 $l$，搜右节点 $r$，越远越好。

搜完后 $l=r+1$，继续搜。

特判 $n\le3$ 的情况。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200001],sum;
int up(int x){
	if(x&1)return x/2+1;
	else return x/2;
}
bool check(int x){
	int l=1,r=1;
	int cnt=0;
	while(++cnt){
		if(cnt==4)return 0;
		while(r<n&&a[r+1]<=a[l]+2*x)r++;
		if(r==n)break;
		l=r+1,r++;
	}
	return 1;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		if(n<=3){
			puts("0");
			continue;
		}
		sort(a+1,a+n+1);
		int l=0,r=up(a[n]-a[1]),ans;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid))ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：escapist404 (赞：4)

### Statement

$T$ 组评测，每组数据给定长度 $n$ 与长度为 $n$ 的序列 $a$，你需要选三个数 $x,y,z$，输出可得到的最小的 $\max\{\min\{|a_i-x|,|a_i-y|,|a_i-z|\}\}$。

### Solution

如果只要我们选一个数，显然我们要选中位数。

如果只要我们选两个数，排序后将序列下标分为 $[0, \mathrm{index})$ 和 $[\mathrm{index}, n)$，分别选两个区间的中位数。

问题是要选三个数，不能朴素地枚举分界的下标。

发现对于某个答案的值，比它大的答案也是存在的，即答案在值域上连续，且有单调性。

二分答案 $s$，考虑对一个 $s$，从小到大覆盖整个序列。

保证 $a$ 有序后，第一次选择 $a_0 + s$ 最大能够覆盖到 $[a_0, a_0 + 2s]$。

假设 $a_i$ 是第一个大于 $a_0 + 2s$ 的数，第二次选择 $a_i + s$ 最大能够覆盖到 $[a_i, a_i + 2s]$。

最后假设 $a_j$ 是第一个大于 $a_i + 2s$ 的数，剩下的区间即为 $[a_j, a_{n-1}]$，判断能否被选完（$a_{n-1} - a_j + 1 \le 2s$ 是否成立）即可。

不难证明该策略最优，因此我们能在 $\mathcal{O}(\log^2{(\max a - \min a)})$ 的时间内处理单个询问。

### Code

```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int& i : a) std::cin >> i;
	std::sort(a.begin(), a.end());

	int l = 0, r = a[n - 1] - a[0];
	while (l < r) {
		int mid = (l + r) / 2;
		int pos = std::upper_bound(a.begin(), a.end(), a[0] + 2 * mid) - a.begin();
        pos = std::upper_bound(a.begin() + pos, a.end(), a[pos] + 2 * mid) - a.begin();
        if (pos == n || a[n - 1] - a[pos] <= 2 * mid) {
            r = mid;
        } else {
            l = mid + 1;
        }
	}
	std::cout << l << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int tt;
	std::cin >> tt;
	while (tt--) solve();
	return 0;
}
```


---

## 作者：rui_er (赞：2)

不妨设 $a$ 单调递增（无重复），显然如果 $n\le 3$ 答案就是 $0$。

显然答案 $k$ 具有可二分性。也就是说，当 $k < k_0$ 时一定不存在合法的 $x,y,z$，当 $k\ge k_0$ 时一定存在，$k_0$ 就是答案。

因此二分答案，只需要验证答案 $k$ 是否存在合法的 $x,y,z$。

为了覆盖到 $a_1$，且 $x$ 尽量往大取（这样可以覆盖更多的 $a_i$），我们令 $x=a_1+k$。接下来一段区间的 $a_i$ 会被 $[x-k,x+k]$ 覆盖，我们跳过这段区间，找到下一个未被覆盖的 $a_i$。类似于刚刚的思路，我们令 $y=a_i+k$，再找到下一个未被覆盖的 $a_j$，令 $z=a_j+k$。如果此时所有 $a_i$ 都被覆盖了，那么就合法，否则不合法。

时间复杂度 $\mathcal O(n\log w)$，其中 $w$ 为值域。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 2e5+5, inf = numeric_limits<ll>::max();

ll T, n, a[N];

bool check(ll M) {
    ll x = a[1] + M, y = inf, z = inf;
    rep(i, 1, n) {
        if(abs(a[i] - x) <= M);
        else if(y == inf) y = a[i] + M;
        else if(abs(a[i] - y) <= M);
        else if(z == inf) z = a[i] + M;
        else if(abs(a[i] - z) <= M);
        else return false;
    }
    return true;
}

int main() {
    for(scanf("%lld", &T); T; T--) {
        scanf("%lld", &n);
        rep(i, 1, n) scanf("%lld", &a[i]);
        sort(a+1, a+1+n);
        n = unique(a+1, a+1+n) - a - 1;
        if(n <= 3) {puts("0"); continue;}
        ll L = 0, R = a[n] - a[1] + 1;
        while(L < R) {
            ll M = (L + R) >> 1;
            if(check(M)) R = M;
            else L = M + 1;
        }
        printf("%lld\n", L);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

## 分析

我们考虑二分最小的最大可行差值。

先不考虑其他因素，在某个二分到的差值为 $x$ 时，我们知道一个定理：在某一段区间内，一旦最大值减去最小值的差小于等于 $x$ 的二倍，则一定能找到一个值 $y$，使最大值最小值分别与 $y$ 相减后的绝对值都不大于 $x$。所以，在判断某个差值是否可行时，我们只需要找出某两个分割点，将序列分成三段后看其各自的最大最小值之差是否满足条件。在这里有个贪心的策略，也就是我们要尽可能地使每一段的差值最小，直接排序就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int t,n;
int a[N];
int check(int mid){
	int k=1;
	int now_where=1;
	while(now_where+1<=n&&a[now_where+1]-a[k]<=mid*2){
		now_where++;
	}
	if(now_where>=n){//一整段都满足，任意分给3个人都行 
		return 1;
	}
	k=now_where+1;
	while(now_where+1<=n&&a[now_where+1]-a[k]<=mid*2){
		now_where++;
	}
	if(now_where>=n){//分成两段满足，将第二段任意分给3个人都行 
		return 1;
	}
	k=now_where+1;
	if(a[n]-a[k]<=mid*2){//因为要分完，所以最后一段一定是k~n，这是最大上限 
		return 1;
	}
	return 0;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		int l=0,r=1145141919810,ans=0;
		while(l<=r){//二分答案 
			int mid=l+r>>1;
			if(check(mid)){//可行，更新答案 
				ans=mid,r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：sz_jinzikai (赞：1)

[洛谷传送门](/problem/CF1840D) &[CF 传送门](//codeforces.com/problemset/problem/1840/D)
# 思路
首先，我们很容易想到可以先把这个序列排序，然后分成三段，一段是和 $x$ 作比较的，一段和 $y$ 作比较，另一端和 $z$ 作比较。三段的分界点使用暴力枚举，这样时间复杂度是 $O(n^2)$ 的，肯定会超时。我们现在又想到了二分答案，二分答案的格式这里不多说了，我们看看 check 函数怎么写。check 函数主要讲究一个贪心策略，即可以选上的都选上，所以我们也要排个序。我们先贪心第一段，再贪心第二段，这样我们最后只要判断剩下的第三段合不合法即可。
# 代码
```cpp
# include <bits/stdc++.h> //万能头 
using namespace std;
typedef long long ll; //现在开始 long long 可以缩写成 ll 了 
ll t, n, a[200005], l, r, mid, best; //定义变量 
bool check () { //定义二分的时候用于判断是否合法的函数 
	int i, last; //定义变量 
	for (i = 1; i < n; ++ i) //枚举第 1 个分界点 
		if (a[i] - a[0] > mid << 1) //如果当前数再选下去就不合法了 
			break ; //直接弹出 
	if (i >= n) //如果第 1 段就可以选完所有数 
		return 1; //提前返回合法 
	last = i; //记录第 2 段的第 1 个元素 
	for (++ i; i < n; ++ i) //枚举第 2 个分界点 
		if (a[i] - a[last] > mid << 1) //如果当前数再选下去就不合法了 
			break ; //直接弹出 
	if (i >= n) //如果第 2 段就可以选完所有数 
		return 1; //提前返回合法 
	return a[n - 1] - a[i] <= mid << 1; //判断最后一段是否合法 
}
int main () { //定义主函数 
	cin >> t; //输入数据组数 
	while (t --) { //多组数据的经典写法 
		cin >> n; //输入序列长度 
		l = r = 0; //多组数据要清空 
		for (int i = 0; i < n; ++ i)
			cin >> a[i], r = max (r, a[i]); //输入序列元素，更新二分答案的最大可能值 
		sort (a, a + n); //排序 
		while (l <= r) { //二分继续条件 
			mid = l + r >> 1; //计算中间值 
			if (check ()) //如果这个答案合法 
				r = mid - 1, best = mid; //继续搜左半边，更新当前最优解 
			else //如果不合法 
				l = mid + 1; //继续搜右半边 
		}
		cout << best << '\n'; //输出最优解 
	}
	return 0; //结束程序 
}
```

---

## 作者：Scean_Tong (赞：0)

## CF1840D Wooden Toy Festival 题解

### 题意

每组长度为 $n$ 的序列 $a$，你需要选三个数 $x,y,z$，求可得到的最小的 $\max\{\min\{|a_i-x|,|a_i-y|,|a_i-z|\}\}$。

### 思路

看到最大值最小，一眼二分答案。

考虑 $\operatorname{check}$ 函数怎么写，只需要求出对于每一个答案需要选几个数，而且求这个东西其实根本用不到区间选点，动态维护一个要必须加入新的数的 $now$ 即可，$a$ 数组排序后如果当前 $a_i$ 和 $now$ 的差值大于当前二分的答案，那么就更新 $now$，并多使用一个数，最后判断使用的数是否小于等于 $3$ 即可。

二分边界无脑使用 $0$ 和 $10^{18}$，[提交记录](https://codeforces.com/contest/1840/submission/290062277)。


```cpp
#include <bits/stdc++.h>
#define int long long
const int maxn = 2e5 + 7;
int T, n, a[maxn];
bool check(int x){
	int now = -1e18;
	int use = 0;
	for(int i = 1; i <= n; i++){
		if(a[i] - now > x){
			now = a[i] + x;
			use ++;
			if(use > 3) return 0;
		}
	}
	return use <= 3;
}
void solve(){
	std::cin >> n;
	for(int i = 1; i <= n; i++){
		std::cin >> a[i];
	}
	std::sort(a + 1, a + n + 1);
	int l = 0, r = 1e18, ans = 0;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid)){
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	std::cout << ans << std::endl;
}
int32_t main(){
	std::cin.tie(nullptr) -> std::ios::sync_with_stdio(false);
	std::cin >> T;
	for(; T--; ){
		solve();
	}
	return 0;
}

```

---

## 作者：hycqwq (赞：0)

## Problem

给定 $n$ 个数 $a_1, a_2, a_3, \cdots, a_n$，自选 $3$ 个数 $x, y, z$ 使

$$\max\limits_{i = 1}^{n} \{\min\{|a_i - x|, |a_i - y|, |a_i - z|\}\}$$

最小。求这个最小值。

## Solution

考虑将 $a$ 分为 $3$ 个区间，使区间中最大数与最小数之差不超过 $m$，利用二分法求 $m$ 的最小值，可以确定唯一的分割方法。

$x, y, z$ 分别取 $3$ 个区间中最大值与最小值的平均数。最后直接算出结果即可。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
#define elif else if
#define il inline

int t, n;
int a[200005];

int nxt(int x)
{
    int l = 0, r = n + 1;
    while (r - l > 1)
    {
        int m = (l + r) / 2;
        if (a[m] < x)
            l = m;
        else
            r = m;
    }
    return a[r];
}
int pre(int x)
{
    int l = 0, r = n + 1;
    while (r - l > 1)
    {
        int m = (l + r) / 2;
        if (a[m] < x)
            l = m;
        else
            r = m;
    }
    return a[l];
}

bool chk(int d)
{
    int i = 1;
    for (int c = 1; c <= 3; c++)
        i = nxt(nxt(i) + d);
    return i > a[n];
}
vector<vector<int> > get(int d)
{
    vector<vector<int> > vv(3, vector<int>()); 
    int i = 1, j = 1;
    for (int c = 1; c <= 3; c++)
    {
        i = nxt(nxt(i) + d);
        for (; a[j] < i && j <= n; j++)
            vv[c - 1].push_back(a[j]);
    }
    return vv;
}

int sum(vector<int> &v, int c)
{
    int ans = 0;
    for (auto i : v)
        ans = max(ans, abs(c - i));
    return ans;
}
int cal(vector<int> &v)
{
    if (v.size() <= 1)
        return 0;
    return sum(v, (v[0] + v[v.size() - 1]) / 2);
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        a[0] = a[n + 1] = inf;
        sort(a + 1, a + n + 1);
        int l = 0, r = 1e9;
        while (r - l > 1)
        {
            int m = (l + r) / 2;
            if (chk(m))
                r = m;
            else
                l = m;
        }
        vector<vector<int> > vv = get(r);
        int ans = 0;
        for (auto i : vv)
        {
//            if (!i.empty())
//            {
//                cout << "  ";
//                for (auto j : i)
//                    cout << j << " ";
//                cout << endl;
//                cout << "  " << (i[0] + i[i.size() - 1]) / 2 << " " << cal(i) << endl;
//            }
            ans = max(ans, cal(i));
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

