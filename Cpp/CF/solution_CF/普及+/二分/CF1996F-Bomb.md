# Bomb

## 题目描述

你有两个长度为 $n$ 的数组 $a$ 和 $b$。最初，你的分数是 $0$。每一次操作中，你可以选择一个 $a_i$ 加到你的分数上。然后 $a_i$ 将会更新为 $\max(0,a_i-b_i)$。

现在你只能执行 $k$ 次操作。那么你能得到的最大分数是多少？

## 样例 #1

### 输入

```
5
3 4
5 6 7
2 3 4
5 9
32 52 68 64 14
18 14 53 24 8
5 1000
1 2 3 4 5
5 4 3 2 1
1 1000000
1000000
1
10 6
3 3 5 10 6 8 6 8 7 7
6 1 7 4 1 1 8 9 3 1```

### 输出

```
21
349
27
500000500000
47```

# 题解

## 作者：Meickol (赞：5)

本题比较经典。

由于 $1≤k≤10^9$，显然无法使用优先队列的做法。

基于题意，要使获得的总分数越高，那么自然要保证每次优先选择较大的数。

我们可以想到使用二分答案加速统计选取操作的过程。

具体地说，就是二分答案寻找一个 $x$，使得在有限次选择和操作过程中都不会使用比 $x$ 更小的数。

二分答案函数直接上代码，可结合注释理解。

```c++
auto check=[&] (LL x){
    LL cnt=0; //表示在限定条件 "所有选择和操作过程中不会使用比x更小的数" 下一共最多会有多少次操作数
    rep(i,1,n) if(a[i]>=x) cnt+=(a[i]-x)/b[i]+1; //a[i]、a[i]-b[i]、…，即对于当前枚举的a[i]，其可得到的≥x的数中一共有(a[i]-x)/b[i]+1个，即进行了(a[i]-x)/b[i]+1次操作
    return cnt>=k;
};
LL l=0,r=1e9; //特别注意二分左边界需要从0开始，因为 a[i] = max(0,a[i]-b[i])，即a[i]在操作过程中可取到0
while(l<r){
    LL mid=l+r+1>>1;
    if(check(mid)) l=mid;
    else r=mid-1;
}
```



最终代码

```c++
#include<bits/stdc++.h>
using namespace std;
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define IOS std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define endl '\n'
typedef long long LL;
const int N=2e5+5;
LL n,k;
LL a[N],b[N];
void solve()
{
    cin>>n>>k;
    rep(i,1,n) cin>>a[i];
    rep(i,1,n) cin>>b[i];
    auto check=[&] (LL x){
		LL cnt=0;
		rep(i,1,n) if(a[i]>=x) cnt+=(a[i]-x)/b[i]+1;
		return cnt>=k;
    };
    LL l=0,r=1e9;
    while(l<r){
    	LL mid=l+r+1>>1;
    	if(check(mid)) l=mid;
    	else r=mid-1;
    }
    LL used=0,sum=0; //used变量统计在前面二分得到的界限中一共会使用的操作次数，sum统计基于used个操作数的情况下获得分数总和。
    rep(i,1,n){
    	LL cnt=0;
    	if(a[i]>=l) cnt+=(a[i]-l)/b[i]+1; //cnt的统计在前面二分答案函数部分已解释过
    	LL p=a[i]-(cnt-1)*b[i]; //p表示a[i]递减操作过程中最后一个≥x的数的具体值
    	sum+=(p+a[i])*cnt/2; //等差数列求和
    	used+=cnt; //统计过程中使用了多少次操作
    }
    cout<<sum+l*(k-used); //输出答案
}
int main(){
	IOS;
	int T;
	cin>>T;
	// T=1;
	while(T--){
		solve();
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：dwj601 (赞：4)

## 原题链接

https://codeforces.com/contest/1996/problem/F

## 题意

给定两个含有 $n$ 个数的序列 $a$ 和 $b$ 以及最大操作次数 $k$，问在不超过最大操作次数的情况下，最多可以获得多少收益？收益的计算方法为：每次选择 $a$ 中一个数 $a_i$ 加入收益，并将该数减去 $b_i$ 直到为 $0$。

## 思路

- 暴力抬手：最暴力的做法是我们每次操作时选择 $a$ 中的最大值进行计数并对其修改，但是显然 $O(nk)$ 会超时，我们考虑加速这个过程。
- 加速过程：由于最终结果中每次操作都是最优的，因此操作次数越多获得的收益就越大，具备单调性。如何利用这个单调性呢？关键在于全体数据的操作次数，我们记作 $k'$。假设我们对 $a$ 中全体数据可取的范围设置一个下限 $lower$，那么显然的 $lower$ 越高，$k'$ 越小，$lower$ 越低，$k'$ 越大。于是根据单调的传递性可知 $lower$ 也和最终的收益具备单调性，$lower$ 越高，收益越小，$lower$ 越低，收益越大。因此我们二分 $lower$，使得 $k'$ 左逼近 $k$。
- 细节处理：二分的边界是什么？这需要从计算最终结果的角度来思考。对于二分出的下界 $lower$，即 $r$，此时扫描一遍计算出来的操作次数 $k'$ 一定是 $k'\le k$。也就是说我们还需要操作 $k-k'$ 次，显然我们可以将每个数操作后维护到最终的结果，然后执行上述的暴力思路，但是这样仍然会超时，因为 $k-k'$ 的计算结果最大是 $n$，此时进行暴力仍然会达到 $O(n^2)$。正难则反，我们不妨将上述二分出的 $lower$ 减一进行最终答案的计算，这样对应的操作次数 $k'$ 一定会超过 $k$，并且对于超过 $k$ 的操作，累加到答案的数值一定都是 $lower-1$，这一步也是本题最精妙的一步。从上述分析不难发现，二分的下界需要设定为 $1$，因为后续累加答案时会对 $lower$ 进行减一操作；二分的上界需要设定为严格大于 $10^9$ 的数，比如 $10^9+1$，因为我们需要保证 $lower-1$ 后对应的操作次数 $k'$ 严格大于 $k$。

## 时间复杂度

$O(n\log k)$

## 参考代码

```cpp
#include <bits/stdc++.h>

using ll = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) std::cin >> a[i];
    for (int i = 0; i < n; i++) std::cin >> b[i];
    
    auto chk = [&](int x) {
        ll cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] < x) continue;
            cnt += (a[i] - x) / b[i] + 1;
        }
        return cnt;
    };
    
    int l = 1, r = 1e9 + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (chk(mid) <= k) r = mid;
        else l = mid + 1;
    }
    
    int best = r - 1;
    ll res = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < best) continue;
        ll t = (a[i] - best) / b[i] + 1;
        cnt += t;
        res += t * a[i] - t * (t - 1) / 2 * b[i];
    }
    res -= (cnt - k) * best;
    
    std::cout << res << "\n";
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    std::cin >> T;
    while (T--) solve();
    return 0;
}
```

---

## 作者：yegengghost (赞：1)

首先看到这个题，您可能会口出狂言：就这 Div.3 还能拦着我？！

但是您再看一眼这是 F 题您就得三思了。

因为您直接暴力打法会喜提 TLE。

我们对于该题可以使用二分。

在该题中，我们的操作数是有限的，那么我们就需要看对当前数字的操作次数**最少次数的最大次数**来统计及答案，故可以二分。

由于我们二分的是要处理的数字的次数，所以我们不妨设次数为 $num$，二分的数为 $mid$，于是答案就变成了：

$$\sum_{i=1}^n(\lfloor\frac{a_i-mid}{b_i}\rfloor+1)$$

最后二分模拟即可。

---

## 作者：ZhaoV1 (赞：1)

### 题目大意

分别给出大小为 $n$ 的数组 $a$ 和 $b$，进行 $k$ 次操作，每次操作选取 $a_i$（其中 $1≤i≤n$），使结果加上 $a_i$，与此同时更改 $a_i$ 为 $0$ 和 $a_i-b_i$ 的最大值。

### 解析

对该题做分析之前，我们先做一组测试：

```
a[i] = 17
b[i] = 4

17 -> 13 -> 9 -> 5 -> 1 -> 0 -> 0 ......
其中“->”表示对 a[i] 进行一次操作。
```
可见，$a_i$ 呈现一个递减的等差数列，由此可以判断我们能找到某个最小值 $mid$，使得 $a_i≥mid$ 的 $a_i$ 个数最接近 $k$（但不大于 $k$，可以相等）。用二分找 $mid$，需要推一个简单的式子：$num=\lfloor\frac{a_i-mid}{b_i}\rfloor+1$

```cpp
bool check(int mid){
	int num = 0;
	for(int i=1;i<=n;i++){
		if(mid < a[i] && a[i]) num += (a[i]-mid)/b[i] + 1;
	}
	return num <= k;
}
```
接下来按部就班就行了，我们得到了最多能从 $a_1$ 到 $a_n$ 经过操作或不操作取得的大于 $mid$ 的个数以及他们的值：$\sum_{i = 1}^{n}\frac{cnt×(a_i+a_i-b_i×(cnt-1))}{2}$（这是经过简单推导得到，如果公式看着头晕建议自己推一推），其中 $cnt$ 指的是对于 $a_i$ 满足条件的数的个数（由之前的求 $num$ 公式得到）。  
如果还需要操作若干剩余次数，由于这个时候剩余次数一定小于或等于 $n$，我们就可以用优先队列取若干次数。


AC Code
---


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int t,n,k;
int a[N], b[N];
int c[N];//剩余的值

bool check(int mid){
//找到一个最小mid，表示一个值，用大于等于该值且能从a[i]中得到的值的总个数与k相比
//个数num = (a[i]-mid)/b[i] + 1（如果严格大于不等于也可以换成(a[i]-mid-1)/b[i]+1）
	int num = 0;
	for(int i=1;i<=n;i++){
		if(mid < a[i] && a[i]) num += (a[i]-mid)/b[i] + 1;//取了大于等于mid的值的个数 
	}
	return num <= k;//看个数是否小于等于k 
}

void solve(){
	cin >> n >> k;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=n;i++) cin >> b[i];

	int left = 0, right = 1e9+1;
	while(left + 1 < right){
		int mid = (left+right) >> 1;
		if(check(mid)){
			right = mid;
		}else{
			left = mid;
		}
	}

	int num = right;//找出所有大于等于right的值 
	int res = 0;
	int mem = 0;
	for(int i=1;i<=n;i++){
//个数cnt = (a[i]-num)/b[i] + 1
//总数sum += 个数*(a[i]+a[i]-b[i]*(个数-1))/2 等差数列
		int cnt = 0;
		if(num < a[i] && a[i]) cnt = (a[i]-num)/b[i] + 1;
		mem += cnt;
		res += cnt*(a[i]+a[i]-b[i]*(cnt-1))/2;
		c[i] = max(0ll,a[i] - b[i]*cnt);//剩余的a[i]的最大值
	}
	if(mem < k){//缺少的部分个数用用c数组装进优先队列里找 
		priority_queue<int> que;
		for(int i=1;i<=n;i++) que.push(c[i]);
		while(!que.empty()){
			res += que.top();
			que.pop();
			mem++;
			if(mem == k) break;
		}
	}
	
	cout << res << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：jhdrgfj (赞：1)

考虑 $O(k)$ 做法。显然我们每一次选择当前最大的数是最优的。所以最终选择的会是能够产生的前 $k$ 大数。

发现直接找不好想。所以考虑二分出一个 $x$ 使得 $x-1$ 是能够产生的第 $k$ 大数。 

考虑如何 ``check``。显然对于每个 $a_i$，其能产生 $\frac {\lfloor a_i - x - 1 \rfloor} {b_i} + 1 $ 个严格大于 $x$ 的数，把所有数的结果加一起看是否小于 $k$ 即可。

再考虑如何统计答案。我们设 $a_i$ 取了 $c_i$ 次，则由等差数列求和公式得其对答案产生的贡献为 $c_ia_i - \frac{c_i(c_i-1)}{2}b_i$。最后由于 $x-1$ 才是第 $k$ 大数，答案加上 $(x-1)(k-\sum c)$ 即可。

[代码和上面略有出入，但做法一样。](https://codeforces.com/contest/1996/submission/272835414)

---

## 作者：wht_1218 (赞：0)

[题目传送门（洛谷）](https://www.luogu.com.cn/problem/CF1996F)

[题目传送门（CF）](https://codeforces.com/contest/1996/problem/F)

---
考察二分答案和贪心。

$k\le 10^9$，暴力不可。

贪心，每次找最大的 $a_i$，不多解释，还是会超时。

由于每次取的 $a_i$ 具有单调不增的性质，所以要使答案最大，我们要用二分答案找所有 $a_i$ 的**最小值最大是多少**（最小值最大化），注意 $a_i$ 的最小值有可能是 $0$。

最后要利用等差数列的公式求答案，不然会超时。

---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Solution]}}$

首先考虑如果 $k$ 较小如何暴力处理。

显然，每次操作肯定是选择是最大的 $a_{i}$。只需要用一个优先队列即可求出答案。

然后再考虑 $k$ 这么大如何处理。

~~然后你就会发现暴力对正解似乎没有任何帮助。~~

其实还是有一些的。每次操作选择的是最大的 $a_{i}$，也就是对于任意的一个 $x$，如果 $\exist i \quad \text{s.t.} \quad a_{i} \leq x$，那么我们就一定不会选择小于 $x$ 的 $a_{i}$ 进行操作。

利用这个性质我们就自然而然地想到了二分。

维护一个关于 $x$ 的函数 $\text{cnt}$，表示使得每个 $a_{i}$ 通过足够次操作后小于 $x$ 所需要的**总**操作数。

利用二分，我们可以求出 $x_{0}$，$x_{0}$ 是使得 $\text{cnt}(x) \geq k$ 的**最大**的 $x$。

这个 $x_{0}$ 就是这么一条线：最优方案下只要一个 $a_{i}$ 通过若干次操作后比 $x_{0}$ 小，那么一定不会再被操作。

但是，**把每一个 $a_{i}$ 都进行足够次操作使得其小于 $x_{0}$ 所需要的总操作数 $\text{cnt}(x_{0})$ 却完全可以大于 $k$**。题目的要求是最多只能进行 $k$ 次，显然要把多余的 $(\text{cnt}(x_{0})-k)$ 次剔除。

不能暴力！

那怎么办？这是最巧妙的地方。多余的 $(\text{cnt}(x_{0})-k)$ 次操作的收益一定**都是** $x_{0}$。

为什么？

根据我们的定义：$x_{0}$ 是使得 $\text{cnt}(x) \geq k$ 的**最大**的 $x$。如果多余的 $(\text{cnt}(x_{0}) -k)$ 次操作有某一次操作的收益 $x_{1}$ 比 $x_{0}$ 大，那么 $\text{cnt}(x_{1})$ 一定也比 $k$ 大，那么 $x_{0}$ 就不是满足条件的最大的 $x$。

$\color{blue}{\text{Code}}$

```cpp
const int N=2e5+100;
typedef long long ll;

int T,n,k,a[N],b[N];

bool check(int mid){
	ll ret=0;//开 ll
	for(int i=1;i<=n;i++)
		if (a[i]>=mid) ret+=(a[i]-mid)/b[i]+1;
	return ret>=k;
}

inline ll calc(int mid){
	ll ans=0,cnt=0;
	for(int i=1;i<=n;i++)
		if (a[i]>=mid){
			int tmp=(a[i]-mid)/b[i]+1;
			cnt+=tmp;
			ans+=1ll*a[i]*tmp-1ll*tmp*(tmp-1)/2*b[i];
		}
	
	return ans+1ll*(k-cnt)*mid;
}

int main(){
	T=read();
	while (T--){
		int l=1,r=0,res=0;
		
		n=read();k=read();
		for(int i=1;i<=n;i++)
			r=max(r,a[i]=read());
		for(int i=1;i<=n;i++)
			b[i]=read();
		
		while (l<=r){
			int mid=(l+r)>>1;
			if (check(mid)){
				l=mid+1;
				res=mid;
			}
			else r=mid-1;
		}//这是一种不需要考虑最终合法解是 l 还是 l+1 还是 r 还是 r-1 的比较方便的二分写法
		
		printf("%lld\n",calc(res));
	}
	
	return 0;
}

read() 是快读函数
```

---

## 作者：oliver326 (赞：0)

# CF1996F 题解

## 题目大意

你有两个长度为 $n$ 的数组 $a$ 和 $b$。最初，你的分数是 $0$。每一次操作中，你可以选择一个 $a_i$ 加到你的分数上。然后 $a_i$ 将会更新为 $\max(0,a_i-b_i)$。

现在你只能执行 $k$ 次操作。那么你能得到的最大分数是多少？

## 贪心思路

首先很显然的一件事情：每次选择当前权值（指 $a_i$）最大的位置贡献答案，最后的总和一定是最优的，这是因为选择了这个值并不会让其他任何地方的其他选择变劣。

于是我们可以用堆维护这个最大权值。具体来说，一开始我们将每个 $a_i$ 加入大根堆，每次取出最大的 $a_i$，贡献答案后，将其减去 $b_i$ 后再插回去。重复执行这种操作 $k$ 次后就得到了答案。

但是注意到我们的时间复杂度其实是和 $\min(k,\frac{a_i}{b_i})$ 正相关的，$a_i,b_i,k$ 都在 $10^9$ 级别，出题人一卡就超时了。代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;
const int maxn = 5e5 + 5, mod = 1e9 + 7;
int T, n, k;
int a[maxn], b[maxn];
int ans;

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
        }
        priority_queue<pair<int, int>> pq;
        for (int i = 1; i <= n; i++) {
            pq.push({a[i], i});
        }
        ans = 0;
        for (int i = 1; i <= k && !pq.empty(); i++) {
            auto tp = pq.top();
            pq.pop();
            ans += tp.first;
            int x = tp.second;
            a[x] -= b[x];
            if (a[x] > 0) pq.push({a[x], x});
        }
        cout << ans << '\n';
    }
    return 0;
}
```

## 正解

既然无法通过，我们考虑优化。

我们思考每一个位置 $i$ 上对答案的贡献，它其实长成这个样子：

$$sum = a_i+(a_i-b_i)+(a_i-2b_i)+...$$

上面的贪心其实相当于一项一项地暴力计算了这个式子。但是很显然这是一个等差数列，可以快速求值。

问题转化为了求这个等差数列到底有几项。由于我们每次操作都选择了最大的值，所以我们选择出来的所有值其实都应该大于等于所有操作结束后 $a$ 序列剩下的数。假设当我们确定了选出来的所有值当中的最小值为 $x$，根据上面的分析 $a$ 数组中残余的那些值都小于等于 $x$，选出来的所有值都大于等于 $x$，这样其实每个位置选了多少值是可以算出来的。

我们二分答案，二分求出让所有位置选的值的个数之和不少于 k 的最大的 $x$。求得 $x$ 后，根据上面的分析每个位置选了几个值都知道了，分别等差数列求和计算答案就行啦。

注意特判一下有多个位置都贡献出 $x$ 的情况，要保证正好选出 $k$ 个值。

考场代码码风稀烂不要在意。

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;
const int maxn = 5e5 + 5;
int T, n, k;
int a[maxn], b[maxn];
int ans, cnt;

int check(int m) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= m) {
            sum += (a[i] - m) / b[i] + 1;
        }
    }
    return sum;
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
        }
        int l = 0, r = 1e10;
        while (r > l) {
            int mid = ((l + r) >> 1) + 1;
            if (check(mid) < k) {
                r = mid - 1;
            } else {
                l = mid;
            }
        }
        ans = 0;
        cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] >= l) {
                int tot = (a[i] - l) / b[i] + 1;
                cnt += tot;
                if (tot != 0) ans += a[i] * tot - tot * (tot - 1) / 2 * b[i];
            }
        }
        if (cnt > k) ans -= (cnt - k) * l;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：syp11 (赞：0)

~~赛时想出来的，然鹅没调出来……~~

## 题面简述

给定两个长度为 $n$ 数组 $\{a_i\}$ 和 $\{b_i\}$ ，每次操作可以选择一个 $i$，获得 $a_i$ 分，并令 $a_i\gets max(0,a_i-b_i)$，求 $k$ 次操作以后的最大得分。

## 算法分析

首先如果 $k$ 不是特别大的情况，比如 $k\leqslant2\times10^5$ 这种，可以使用贪心，优先队列维护 $a$ 数组每一个元素当前的值，每次操作取最大值即可，时间复杂度 $O(k\log n)$。

为了通过 $k\leqslant10^9$ 的情况，分析上面的贪心过程，由于每次取得数组的最大值，那么在 $k$ 次操作取完之后，必然存在一个分界线 $x$ ，使得所有分数 $\geqslant x$ 的全部被取到，分数恰好为 $x-1$ 的可能取到，分数 $\leqslant x-2$ 的不会被取到。

为此，可以二分查找到这个分界线 $x$，并且直接取得 $\geqslant x$  的分数，扣除得分次数以后剩下的再使用优先队列维护贪心的方式即可（其实不用也可以）。二分的时间复杂度为 $O(n\log V)$，其中 $V=10^9+1$ 为值域。

因为队列至多有 $n$ 个元素，而 $b_i\geqslant1$，所以分数恰好为 $x-1$ 的元素至多只有 $n$ 个，获取这些得分以后不会产生新的 $x-1$，所以使用优先队列维护贪心的复杂度为 $O(n\log n)$。

整体时间复杂度为 $O(n\log n+n\log V)$，可以通过本题。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int T,n,k,a[N],b[N];
bool check(int x)
{
	int t=0;
	for(int i=1;i<=n;i++)
	{
		t+=max(0ll,(a[i]-x)/b[i]+(a[i]>=x));
	}
	return t<=k;
}
int getl()
{
	int l=0,r=1e9+1;
	while(l<r)
	{
		int mid=l+r>>1;
		if(check(mid))
		{
			r=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	return l;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<=n;i++)
		{
			cin>>b[i];
		}
		int x=getl();
		int res=0;
		priority_queue<int>q;
		for(int i=1;i<=n;i++)
		{
			int c=max(0ll,(a[i]-x)/b[i]+(a[i]>=x));
			res+=(2*a[i]-(c-1)*b[i])*c/2;
			k-=c;
			if(a[i]-c*b[i]>=0)
			{
				q.push(a[i]-c*b[i]);
			}
		}
		while(k&&!q.empty())
		{
			int v=q.top();
			q.pop();
			res+=v;
			k--;
		}
		cout<<res<<'\n';
	}
	cout<<flush;
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## CF1996F

考虑贪心，每次选当前 $a$ 最大的，再将 $a-b$ 放入堆里，重复 $k$ 次。时间复杂度太大，不能接受。

但是由此可以发现，每次选的一定是最大值，那么随着操作次数的增加，最大值一定不增。可以二分操作后的序列的最大值，根据 $k$ 次操作后的最大值计算每个元素的贡献即可。

有一些细节，看一下代码：

```cpp
bool Check(int x) {
  ll cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] <= x) continue;
    cnt += (a[i] - x - 1) / b[i] + 1;
    if (cnt > k) return false;
  }
  return true;
}

ll Calc(int x) {
  /* 这里计算的是最大值小于 x，操作数比二分出来的要多一点，是由 x 变为更小数，
     但是还有值为 x 的数造成的，这种情况下把所有大于等于 x 的数都预先减去，
     并统计操作数量，最后多于 k 的操作一定是因为 x 变小操作造成的。
     因为是二分答案，最大值一定不会小于x，这样可以保证不重不漏。*/
  ll res = 0, tot = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] < x) continue;
    ll cnt = (a[i] - x) / b[i] + 1;
    res += cnt * a[i] - (cnt * (cnt - 1) / 2) * b[i];
    tot += cnt;
  }
  if (tot > k) res -= (tot - k) * x;
  return res;
}

void Main() {
  n = read(), k = read(), ans = 0;
  for (int i = 1; i <= n; ++i) a[i] = read();
  for (int i = 1; i <= n; ++i) b[i] = read();
  int l = 0, r = 1E9;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (Check(mid))
      r = mid;
    else
      l = mid + 1;
  }
  printf("%lld\n", Calc(l));
}

```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1996F](https://codeforces.com/contest/1996/problem/F)

# 解题思路

考虑二分。

我们发现，我们肯定是拿此时的价值最大的物品。

因此，当所有的物品再拿一次后会小于等于 $x$ 时拿走的物品数量，在 $x$ 缩小时，答案是**单调不减**的。

因此，我们可以令二分当所有的物品再拿一次后会小于等于 $x$ 时的物品总价值是多少，注意这里要判断取的物品的数量是否合法。

由于 $b_i$ 是固定的，因此直接使用等差数列求和公式来给每个数计算贡献即可。

时间复杂度 $O(n \log V)$，其中 $V$ 为值域。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);init();
#define endl '\n'
#define QwQ return 0;
#define db long double
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
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll t;
ll n,m;
ll a[200010],b[200010];
/**
bool cmp(node x,node y){
	return x.x>y.x;
}*/
ll ans,L,R;
void _clear(){ans=0;L=R=0;}
ll f(ll l,ll r,ll x){//l+..+r gongchawei x
	return (l+r)*((r-l)/x+1)/2;
}
ll f2(ll l,ll r,ll x){//xiangshu
	return ((r-l)/x+1);
}
ll check(ll Mid)
{
	ll sum=0,sum2=0,sum3=0;
	//_1,sum,val 
	forl(i,1,n)
	{
		if(a[i]<Mid)
			continue;
		ll num=a[i]-(a[i]-Mid)/b[i]*b[i];
		sum+=(num==Mid);
		sum2+=f2(num,a[i],b[i]);
		sum3+=f(num,a[i],b[i]);
	}
	//cout<<sum<<' '<<sum2<<endl;
	if(sum2<m)
	{
		Max(ans,sum3);
		return -2;
	}
	if(sum2-sum>m)
		return -1;
	Max(ans,sum3-(sum2-m)*Mid);
	return -2;
}
/*
1
2 1
20 20 
10 4 
*/
void solve()
{
	_clear();
	cin>>n>>m;
	forl(i,1,n)
		cin>>a[i],Max(R,a[i]);
	forl(i,1,n)
		cin>>b[i];
	while(L<=R)
	{
		ll Mid=(L+R)/2;
	//	cout<<Mid<<endl;
		ll ck=check(Mid);
		if(ck==-2)
			R=Mid-1;
		else
			L=Mid+1;
	}
	cout<<ans<<endl;
}
void init(){}
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

## 作者：fengxiaoyi (赞：0)

考虑 $k$ 比较小时怎么做。

不难想到每次贪心的取当前 $a_i$ 最大的一定是最优的。于是可以用堆来维护当前最大值。

接着考虑 $k$ 比较大时怎么做。

注意到每次取的 $a_i$ 一定是单调不增的，那只要确定最后一个取得值，就能算出最终的答案。

所以考虑二分最后一个取的 $a_i$，判断此时取的次数 $x$，如果 $x\le k$，那么这个 $x$ 就是满足的条件。找到最大的 $x$ 即可。

那怎么求这个 $x$ 呢？假设二分的值为 $e$，则 $x=\sum^n_{i=1}(\lfloor\frac{a_i-e}{b_i}\rfloor+1)$。

最终算答案时就用等差数列求和的方法即可，具体见代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200010],b[200010];
bool check(long long mid){
	long long sum=0;
	for(int i=1;i<=n;i++){
		if(a[i]<mid) continue;
		long long x=(a[i]-mid)/b[i]+1;
		sum+=x;
	}
	return sum<=k;
}
long long cnt(long long x){
	long long sum=0;
	for(int i=1;i<=n;i++){
		if(a[i]<x) continue;
		long long y=(a[i]-x)/b[i]+1;
		sum+=y;
	}
	return sum;
}
long long work(long long x){
	long long ans=0;
	for(int i=1;i<=n;i++){
		if(a[i]<x) continue;
		long long l,r,p=(a[i]-x)/b[i];
		l=a[i],r=a[i]-p*b[i];
		ans+=1ll*(l+r)*(p+1)/2;
	}
	return ans;
}
int main(){
    scanf("%d",&t);
	while(t--){
	    scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) scanf("%d",&b[i]);
		long long l=0,r=1e9+1;
		while(l<r-1){
			long long mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=mid;
		}
		if(check(l)) printf("%lld\n",work(l));
		else printf("%lld\n",work(r)+max(1ll*(k-cnt(r)),0ll)*l);
	}
	return 0;
}
```

---

