# [ABC334C] Socks 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc334/tasks/abc334_c

高橋君は $ N $ 組の靴下を持っており、$ i $ 番目の組は色 $ i $ の靴下 $ 2 $ 枚からなります。 ある日タンスの中を整理した高橋君は、色 $ A_1,A_2,\dots,A_K $ の靴下を $ 1 $ 枚ずつなくしてしまったことに気づいたので、残っている $ 2N-K $ 枚の靴下を使って、靴下 $ 2 $ 枚ずつからなる $ \lfloor\frac{2N-K}{2}\rfloor $ 個の組を新たに作り直すことにしました。 色 $ i $ の靴下と色 $ j $ の靴下からなる組の**奇妙さ**は $ |i-j| $ として定義され、高橋君は奇妙さの総和をできるだけ小さくしたいです。

残っている靴下をうまく組み合わせて $ \lfloor\frac{2N-K}{2}\rfloor $ 個の組を作ったとき、奇妙さの総和が最小でいくつになるか求めてください。 なお、$ 2N-K $ が奇数のとき、どの組にも含まれない靴下が $ 1 $ 枚存在することに注意してください。

## 说明/提示

### 制約

- $ 1\leq\ K\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_1\ <\ A_2\ <\ \dots\ <\ A_K\ \leq\ N $
- 入力は全て整数

### Sample Explanation 1

以下、色 $ i $ の靴下と色 $ j $ の靴下からなる組を $ (i,j) $ と表記します。 色 $ 1,2,3,4 $ の靴下がそれぞれ $ 1,2,1,2 $ 枚ずつあります。 $ (1,2),(2,3),(4,4) $ の $ 3 $ 組を作ると、奇妙さの総和は $ |1-2|+|2-3|+|4-4|=2 $ となり、これが最小です。

### Sample Explanation 2

$ (1,1),(3,3),(4,4),(5,5) $ の $ 4 $ 組を作り、色 $ 2 $ の靴下を $ 1 $ 枚余らせる（どの組にも入れない）のが最適です。

## 样例 #1

### 输入

```
4 2
1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5 1
2```

### 输出

```
0```

## 样例 #3

### 输入

```
8 5
1 2 4 7 8```

### 输出

```
2```

# 题解

## 作者：Albatross_LC (赞：6)

## 题意：

一个人有 $N$ 双袜子，丢了 $K$ 种颜色的袜子各一只，求剩下袜子匹配的最小差异。最小差异：两种袜子颜色差的绝对值。

## 分析：

这一题我们只需处理对应颜色只剩下一只袜子的部分即可，因为颜色对应的一双袜子差异值为 $0$。

然后，可以观察到，如果 $A_i$ **参与匹配时**能找到一个**存在的** $A_j$，使得 $\left | A_i - A_j\right | $ 最小，那么将数组排序后，$A_i$ 与 $A_j$ 一定相邻。所以，将数组从小到大排序，逐个将 $A_{i + 1}$ 与 $A_i$ 的差相加即可，以下为实现代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, k, a[N], ans;
int b[N], e[N];
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= k; i ++ ) cin >> a[i];
	sort(a + 1, a + 1 + k);
	for (int i = 1; i < k; i += 2) ans += a[i + 1] - a[i];
	cout << ans;
}
```

然而，我们并没有AC。再看一遍题目，可以注意到题目中没有限制 $K$ 不为奇数，也就是说，当配对完 $\frac{K - 1}{2}$ 双袜子后，还有一只袜子袜子没有其它的袜子与它配对。这次，我们要求的是：当 $K$ 为奇数时，如何去掉一只颜色为 $A_i$ 的袜子，使得剩下的袜子匹配差异和最小。

如果直接逐个枚举，时间复杂度为 $O(K^2)$，显然会超时；但如果我们预先将前缀和求出来，求值部分时间复杂度就可降低到 $O(K)$。

设从 $1$ 开始往后求前缀和的数组为 $b$，从 $K$ 往前求前缀和的数组为 $e$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/at53au5x.png)

如果我们要删除的是图中黑色部分，那么剩下的差异和就为`e[1] + b[1] + a[4] - a[2]`。

也就是说，如果要删除第 $i$ 个颜色，当 $i$ 为偶数时，差异和为`b[i - 2] + e[i + 2] + a[i + 1] - a[i - 1]`；$i$ 为奇数时，差异和为`b[i - 1] + e[i + 1]`。

代码很好实现，如下所示：


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, k, a[N], ans;
int b[N], e[N];
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= k; i ++ ) cin >> a[i];
   	sort(a + 1, a + 1 + k);
	if (k % 2 == 0) for (int i = 1; i <= k; i += 2) ans += a[i + 1] - a[i];//k为偶数
	else {//k为奇数
		ans = INT_MAX;
		for (int i = 2; i <= k; i += 2)//前缀和b
		    b[i] = b[i - 2] + a[i] - a[i - 1];
		for (int i = k - 1; i > 0; i -= 2)//前缀和e
		    e[i] = e[i + 2] + a[i + 1] - a[i];
		for (int i = 1; i <= k; i += 2)//删除奇数位数
		    ans = min(ans, b[i - 1] + e[i + 1]);
		for (int i = 2; i <= k; i += 2)//删除偶数位数
		    ans = min(ans, b[i - 2] + e[i + 2] + a[i + 1] - a[i - 1]);
	}
	cout << ans;//输出
}
```

---

## 作者：FReQuenter (赞：4)

不难发现如果有成对的袜子互相匹配是最优的。

那么就剩下来 $k$ 只落单的如何匹配。

一个显然的方法是将所有袜子升序排列，则相邻的两个配对。

在 $k$ 是偶数时，这个方式显然最优。

那么 $k$ 是奇数，就需要扔掉一只袜子。

扔哪只呢？我们枚举扔了哪只袜子。容易证明扔掉的袜子在 $a$ 中的编号为奇数。

那么剩下的序列就可以用上面的方法计算贡献，之后取 $\min$ 就行了。

这样是 $O(n^2)$ 的。我们注意到重复计算了很多遍形如 $\{1,2\},\{3,4\},\cdots$ 这样的组合。

所以考虑给原序列按照最初的配对方式做一个关于贡献的前缀和和后缀和。这样子就 $O(n)$ 了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[200005],zs[200005],ds[200005];
signed main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++) cin>>a[i];
	if(k%2==0){
		int sum=0;
		for(int i=1;i<=k;i+=2)sum+=a[i+1]-a[i];
		cout<<sum;
	}
	else{
		for(int i=2;i<=k;i+=2) zs[i]=zs[i-2]+a[i]-a[i-1];
		for(int i=k-1;i>=1;i--) ds[i]=ds[i+2]-a[i]+a[i+1];
		int ans=0x3f3f3f3f3f3f3f3fll;
		for(int i=1;i<=k;i+=2) ans=min(ans,zs[i-1]+ds[i+1]);
		cout<<ans;
	}
}
```

---

## 作者：heyx0201 (赞：2)

# ABC334C Socks 2 题解
## Description
> 给定 $N,K$ 和 $K$ 个递增的整数 $A_1, A_2, \dots ,A_K$，表示总共 $2N$ 只袜子，$A_1 \sim A_k$ 颜色的袜子各丢了一只，设一双袜子为 $i, j$，一双袜子的怪异值为 $|i-j|$，现在要把袜子重新组合，求最小怪异值。注意如果 $2N-K$ 为奇数，那么会多出一只袜子不用配对。

## Solution
看到题解区好像没人写 DP，我来写一发。

这题用 DP 写是最简单的。把袜子丢掉以后，最多只会多出一只袜子，所以可以设计一个状态：
- $dp_{i,0} = dp_{i-2,0} + a_i - a_{i - 1}$
- $dp_{i,1} = \min \{dp_{i-1,0}, dp_{i-2,1} + a_i - a_{i-1}\}$

但是要注意边界情况，所以要判断一下。

## Accept Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;

int n, k, a[MAXN], dp[MAXN][2];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= k; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; i++) {
    if (i - 2 >= 0) {
      dp[i][0] = dp[i - 2][0] + a[i] - a[i - 1];
      dp[i][1] = min(dp[i - 1][0], dp[i - 2][1] + a[i] - a[i - 1]);
    } else {
      dp[i][1] = dp[i - 1][0];
    }
  }
  cout << dp[k][k % 2];
  return 0;
}
```

---

## 作者：无钩七不改名 (赞：1)

很有趣的一道贪心题！

先讲一下和赛时代码不太一样的思路吧。

如果为偶数个，则可以正确配对的袜子就正确配对，其余的按照 $(a_1,a_2),(a_3,a_4),...,(a_{k-1},a_k)$ 的顺序配对。

如果为奇数个，则是去掉一个不能正确配对的袜子后按照偶数个配对。具体操作是先统计 $(a_1,a_2),(a_3,a_4),...,(a_{k-2},a_{k-1})$ 时候的答案，然后统计对于每个为奇数的 $i$ 的初始不匹配度（即同组的 $a_i$ 和 $a_{i+1}$ 的差值）的后缀和（含当前组），再统计对于每个为偶数的 $i$ 作 $(a_i,a_{i+1}),(a_{i+2},a_{i+3}),...,(a_{k-1},a_k)$ 匹配时的不匹配度和。即可统计删去每个为奇数的 $i$ 的袜子 $a_i$ 时候的最小答案。

### 正确性证明

对于每个匹配 $(a_i,a_{i+1})$，和不同的匹配 $(a_j,a_{j+1})$ 交换袜子，只会使得答案更劣。那如果和匹配 $(k,k)$ 交换，当 $a_i<k<a_{i+1}$ 时候，答案不会更优，否则答案一定会更劣。

+ 关于删去第奇数个：设当前匹配为 $(a_i,a_{i+1})$。显然在一对匹配中删去前者比删去后者更优。因为删去后者会比删去前者少 $a_{i+1}-a_i$ 点不匹配度。可以自己思考一下。

### 赛时思路

我们对剩下的袜子记录为从小到大排序的数组 $b_i$，设剩下的袜子数量为 $m$。

若 $m$ 为偶数，匹配则为 $(b_1,b_2),(b_3,b_4),...,(b_{m-1},b_m)$。正确性证明同理，可以通过交换证明。

否则就是去掉一个袜子按照上述方法匹配。处理方式同上面的思路。

### 赛时代码

其实是两个思路的结合。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=200005;

int n,k,a[N],b[N<<1],qwq;
long long sum[N],sum2[N];
long long ans;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int main(){
	n=read();k=read();
	if(k==1)return puts("0"),0;
	for(int i(1);i<=k;++i){
		a[i]=read();
		for(int j(a[i-1]+1);j<a[i];++j)b[++qwq]=j,b[++qwq]=j;
		b[++qwq]=a[i];
	}
	for(int i(2);i<=qwq;i+=2)ans+=b[i]-b[i-1];
	if(k%2==0)return printf("%lld",ans),0;
	for(int i(k-1);i;i-=2)sum[i]=sum[i+2]+a[i]-a[i-1];
	for(int i(k);i>0;i-=2)sum2[i]+=sum2[i+2]+a[i]-a[i-1];
	long long www=ans;
	for(int i(1);i<k;i+=2)
		www=min(www,ans-sum[i+1]+sum2[i+2]);
	printf("%lld",www);
	return 0;
}
```


---

## 作者：xz001 (赞：0)

- 首先我们发现若 $k$ 为偶数，直接将还有的袜子编号排序，相邻的配对即可。
- 所以问题就出在 $k$ 是奇数的情况，我们可以排序后枚举丢弃哪一只，然后将其前方的袜子相邻配对，后方的袜子相邻配对，预处理一个前缀最小值和后缀最小值即可。
- 以上操作要保证其前方的袜子数和后方的袜子数均为偶数。

---

## 作者：ny_Dacong (赞：0)

先贴一个题目翻译：

## 题目翻译

高桥有 $N$ 对袜子，第 $i$ 对由颜色为 $i$ 的两只袜子组成。一天，整理抽屉后，高桥发现丢失了颜色为 $A_1,A_2,…,A_k$ 的袜子，于是他决定用剩下的 $2N-K$ 只袜子做 $\left\lfloor\dfrac{2N-K}{2}\right\rfloor$ 对新的袜子，每对都由两只袜子组成。 一对颜色为 $i$ 和颜色为 $j$ 的袜子的奇怪程度定义为 $\left|i-j\right|$，高桥希望最小化总奇怪程度。

在用剩下的袜子做 $\left\lfloor\dfrac{2N-K}{2}\right\rfloor$ 对时，找出可能的最小总奇怪程度。 注意，如果 $2N-K$ 是奇数，会有一只袜子没有被包含在任何一对中。

***

我们会发现，如果有两只颜色一样的袜子，那我们肯定会让这两只袜子配对。这样，奇怪度就是 $0$，肯定是最优的。

所以我们要做的，就是配对**没有另一只颜色相同的袜子**，也就是题目给出来的 $A$ 数组。因此，我们接下来说的“袜子”，**指的是 $A$ 数组中的元素。**

我们可以把相邻两只袜子配为一对。因为 $A$ 是有序的，所以把相邻的袜子配对肯定是最优的。

接下来，我们分类讨论。

* 如果 $2N-K$ 是偶数，那么这个分法下，总奇怪度就是答案。
* 如果 $2N-K$ 是奇数，那么我们需要枚举哪个袜子需要去掉。

很快，我们会写出一个朴素代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,sum = 0,ans = 0;
int Lost[200005];
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1; i <= k; i++){
		scanf("%d",&Lost[i]);
	}
	for(int i = 1; i <= k; i += 2){
		sum += abs(Lost[i]-Lost[i+1]);
	}
	if((2*n-k)%2 == 0){
		printf("%d",sum);
		return 0;
	}
	ans = 0x3f3f3f3f;
	for(int i = 1; i <= k; i++){
		sum = 0;
		for(int j = 1; j <= k; j += 2){
			if(j == i){
				j++;
			}
			sum += abs(Lost[j]-Lost[j+1]);
		}
		ans = min(ans,sum);
	}
	printf("%d",ans);
	return 0;
}
```

然而提交会超时。

这时候，我们注意到了求和这个操作。很明显，可以用前缀和优化。因为去掉一只袜子后，求和的区间被分成了两段，所以要从两个方向求前缀和。

最终优化后的 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans = 1e9;
int Lost[200005],sum[200005],summ[200005];
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1; i <= k; i++){
		scanf("%d",&Lost[i]);
	}
	for(int i = 2; i <= k; i += 2){
		sum[i] = sum[i-2]+Lost[i]-Lost[i-1];
	}
	for(int i = k-1; i >= 0; i -= 2){
		summ[i] = summ[i+2]+Lost[i+1]-Lost[i];
	}
	for(int i = 0; i <= k-k%2; i += 2){
		ans = min(ans,sum[i]+summ[i+1+k%2]);
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc334_c)

一道贪心题。

数量为 $2$ 的袜子不用考虑，因为最好的情况就是相同颜色的配一对。

我们只需要考虑那 $k$ 种只有 $1$ 个的袜子，如果 $k$ 为偶数，答案为相邻两数之差之和；如果 $k$ 为奇数，就枚举删掉一个数，让剩下的数按照 $k$ 为偶数的情况做，最后取一个最小值。这个过程可以使用前缀和维护。

### Code

```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;
const long long MOD = 998244353;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define REP(i, l, r) for (auto i = (l); i <= (r); i++)
	#define PER(i, r, l) for (auto i = (r); i >= (l); i--)
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
ll n, k, ans;
ll a[200005], sum[200005], pre[200005];
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> k;
	REP(i, 1, k) {
		cin >> a[i];
		if (i & 1) sum[i] = sum[i - 1] - a[i];
		else sum[i] = sum[i - 1] + a[i];
	}
	PER(i, k, 1) {
		if (i & 1) pre[i] = pre[i + 1] - a[i];
		else pre[i] = pre[i + 1] + a[i];
	}
	if (k & 1) {
		ans = LMX;
		REP(i, 1, k) ans = Min(ans, sum[i - 1] - pre[i + 1]);
	}
	else {
		for (int i = 2; i <= n; i += 2) ans += a[i] - a[i - 1];
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Esperance (赞：0)

很恶心的一道题啊。

### 题意

总共有 $N$ 双袜子，$K$ 只丢了，问其他的袜子两两重组后的最小怪异值多少（如果剩下奇数只袜子那必有一个袜子无法配对）。袜子 $i$ 和 $j$ 配对的怪异值为 $|i-j|$。

### 思路

贪心。

假设有一双袜子 $p$ 与 $a,b(a<b)$ 重组使 $|p-a|+|p-b|$ 最小，则通过绝对值的性质显然能得出 $a\leq p\leq b$，怪异值为 $b-a$。

而与此同时，不拆散 $p$，直接让 $a$ 和 $b$ 配对时的怪异值也是 $b-a$。因此让一只单独的袜子与它相邻的袜子配对一定是最优解。

做一遍差分。总数为偶就从 $2$ 开始把每个偶数下标的袜子的差累加即可。

总数为奇是可以发现答案总为被舍弃袜子前偶数编号的差之和加上被舍弃袜子后奇数编号的和。做一遍前缀和一遍后缀和，然后枚举被舍弃的袜子编号求最小怪异值。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k, a[200005], b[200005], ans = 0;
int ji[200005], ou[200005];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	int mxx = 0, mi = 0, mk = 0;
	for (int i = 1;i <= k;i++) cin >> a[i];
	for (int i = 2;i <= k;i++) b[i] = a[i]-a[i-1]; // 差分
	if (k % 2 == 0) {
		for (int i = 2;i <= k;i+=2) ans += b[i]; // 偶数直接累加差
		cout << ans;
	}
	else {
		ans = INT_MAX;
		for (int i = k;i >= 1;i-=2) ji[i-1] = ji[i] = ji[i+2]+b[i]; // 奇数编号后缀和
		for (int i = 2;i <= k;i+=2) ou[i+1] = ou[i] = ou[i-2]+b[i]; // 偶数编号前缀和
		for (int i = 1;i <= k;i++) {
			//cout << ji[i+1] << ou[i] << '\n';
			int tmp = ou[i]+ji[i+1];
			ans = min(ans,tmp); // 求最小值
		}
		cout << ans;
	}
	return 0;
}

```

---

## 作者：yanhao40340 (赞：0)

本题思维难度较高，代码实现难度较低。

## 题意

有 $2n$ 个数，其中 $1$ 到 $n$ 各 $2$ 个。现在拿走其中 $k$ 个互不重复的数，然后将剩下 $2n-k$ 个数两两配成 $\displaystyle\lfloor\dfrac{2n-k}{2}\rfloor$ 组。一组的差异值为同组两数的差的绝对值。最小化总差异值。

## 分析

考虑将剩下的数从小到大排序 $a_{1,2,\cdots,2n-k}$。

记 $f(i)$ 代表前 $2i$ 个数最小总差异值的分组方案。观察样例可知 $f(i)=\{(a_1,a_2),(a_3,a_4),\cdots,(a_{2i-1},a_{2i})\}$。下面将对其进行证明。

当 $i=1$ 时，$f(i)=\{(a_1,a_2)\}$。

假设 $i \le k$ 时，结论均成立。

考虑 $i=k+1$ 时，如果将 $f(k)$ 中第 $j$ 项拆开与 $(a_{2i-1},a_{2i})$ 重组，即构成 $(a_{2j-1},a_{2i-1}),(a_{2j},a_{2i})$ 或 $(a_{2j-1},a_{2i}),(a_{2j},a_{2i-1})$。

因为
$$|a_{2i-1}-a_{2j-1}|+|a_{2i}-a_{2j}|=a_{2i-1}-a_{2j-1}+a_{2i}-a_{2j}\ge a_{2i}-a_{2i-1}+a_{2j}-a_{2j-1}=|a_{2i}-a_{2i-1}|+|a_{2j}-a_{2j-1}|$$

$$|a_{2i-1}-a_{2j}|+|a_{2i}-a_{2j-1}|=a_{2i-1}-a_{2j}+a_{2i}-a_{2j-1}\ge a_{2i}-a_{2i-1}+a_{2j}-a_{2j-1}=|a_{2i}-a_{2i-1}|+|a_{2j}-a_{2j-1}|$$

所以重组后一定不会更优。根据数学归纳法，证毕。

那么我们其实已经解决了 $k$ 为偶数时的情况。

而当 $k$ 为奇数时，考虑动态规划。

设 $p_i$ 表示从小到大 $2i$ 个数最小总差异值，$q_i$ 表示从大到小 $2i$ 个数最小总差异值，那么答案即为 $\min p_i+q_{s-i}$，其中 $s=\displaystyle\lfloor\dfrac{2n-k}{2}\rfloor$。

时间复杂度：$\Theta(n)$。

## 代码

实现略有不同，仅供参考。

```cpp
//已省略快读快输
#include <iostream>
#include <vector>
#define int long long
using namespace std;
const int maxn=2e5+5;
int mp[maxn],f[maxn],g[maxn];
vector<int> v;
signed main(){
	int n=read(),k=read();
	for (int i=1;i<=k;++i) v.push_back(read());
	if (v.size()&1){
		for (int i=0;i<v.size()-1;i+=2)
			if (i==0) f[i]=v[i+1]-v[i];
			else f[i]=f[i-2]+v[i+1]-v[i];
		for (int i=v.size()-1;i;i-=2)
			g[i-1]=g[i+1]+v[i]-v[i-1];
		int ans=g[1];
		for (int i=0;i<v.size()-1;i+=2)
			ans=min(ans,f[i]+g[i+3]);
		write(ans);
	}
	else{
		int ans=0;
		for (int i=0;i<v.size();i+=2)
			ans+=v[i+1]-v[i];
		write(ans);
	}
	return 0;
}

```

---

## 作者：Expert_Dream (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。有大量 at 题目的题解。

首先，我们可以分两种情况讨论，如果是偶数，那么排完序之后 $a_i - a_{i-1}$ 算出来即可。

奇数我们可以预处理一个前缀和和一个后缀和。然后枚举中间哪一个是不用取的，然后使用 $O(n)$ 时间复杂度解决。

注意一下细节，首先你遍历的时候一定是 $+2$ 这样跳的，如果是 $+1$ 的跳就会错，我被卡了很久。

[link](https://atcoder.jp/contests/abc334/submissions/48764163)。

---

## 作者：jubingkun (赞：0)

## 题目大意
$1$ 到 $n$ 中，每个数都有两个。但现在少了 $k$ 个数，它们分别是 $a_1,a_2,\cdots,a_k$，定义两个数合并的代价是 $\left\vert i-j \right\vert$，问所有剩下的数合并成 $ \lfloor\frac{2N-K}{2}\rfloor $ 个数的最小代价。

## 题目分析
显然此题与 $n$ 无关，因为直接合并 $a_i$ 和 $a_{i+1}$ 与通过 $a_i$ 到 $a_{i+1}$ 之间未缺少的的数合并的效果是相同的。

那么问题就转化为缺少的这 $k$ 个数的合并，他们会合并成 $\lfloor \frac{k}{2}\rfloor$ 个数。

分别考虑 $k$ 为奇数和 $k$ 为偶数的情况。

当 $k$ 为偶数时，直接两两配对就好（即 $a_1$ 与 $a_2$ 配对，$a_3$ 与 $a_4$ 配对，以此类推）。

当 $k$ 为奇数时，由于我们并不知道舍去那个会更优，所以考虑枚举舍去的点。

对于舍去的点的位置也有两种情况，一是其为奇数，二是其为偶数。
![](https://cdn.luogu.com.cn/upload/image_hosting/xtapztso.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/5n25idji.png)

可以观察到当舍去的点的位置为奇数时，左右两端的点的个数均为偶数；但舍去的点的位置为偶数时，其左右两边点的个数均为奇数。

当舍去的点的位置为奇数时，显然左边两两配对，右边也两两配对；当舍去的点的位置为偶数时，左边两两配对后会剩下一个点，右边也会剩下一个点，这两个点配对。又由于相邻的数配对最优，所以假设舍去 $i$ 点，则 $a_{i-1}$ 与 $a_{i+1}$ 配对。

这时候你就会发现：不对啊，这 $k$ 的数据范围也不允许枚举舍去的点后再进行暴力计算啊。

### 考虑优化
前缀和是个好用的东西。

我们先正着跑，舍去 $k$ 这个点，处理出前缀和，在倒着跑，舍去 $1$ 这个点，再处理出一个前缀和（这两个前缀和用两个数组存）。

假设我们舍去了 $i$ 这个点。

当 $i$ 为奇数时，代价为 $i$ 前面的数以舍去 $k$ 这个点的当前点的前缀和加上 $i$ 后面的数以舍去 $1$ 这个点的当前点的前缀和（这个可以照着图理解，假设 $k$ 为 $7$，$i$ 为 $3$，那么 $i$ 前面有 $2$ 个数，直接返回这两个数配对所对应的前缀和即可，$i$ 后面同理）。

当 $i$ 为偶数时，$i-1,i+1$ 都是奇数，$i-1$ 用奇数时处理，但不加上 $i-1$ 后面的数；$i+1$ 也用奇数时处理，但不加上 $i+1$ 前面的数（这个思考一下就明白了）。

## Code
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN = 2e5 + 5;
int n, k;
int a[MAXN], pre_f[MAXN], pre_b[MAXN];
//pre[i]表示合并成i个数时的代价
int main() {
	ios::sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 1; i <= k; ++i)	cin >> a[i];
	if (k & 1) {
		int ans = 0x7fffffff;
		for (int i = 2; i <= k; i += 2)	pre_f[i >> 1] = pre_f[(i >> 1) - 1] + a[i] - a[i - 1];
		for (int i = k; i >= 1; i -= 2)	pre_b[((k - i) >> 1) + 1] = pre_b[(k - i) >> 1] + a[i] - a[i - 1];//这样处理是为了让下标从1开始，方便查询
		for (int i = 1; i <= k; ++i) { //枚举舍去的点
			int sum = 0;
			if (i & 1) {
				sum += pre_f[(i - 1) >> 1];
				sum += pre_b[(k - i) >> 1];
			} else {
				sum += pre_f[(i - 2) >> 1];
				sum += pre_b[(k - i - 1) >> 1];
				sum += a[i + 1] - a[i - 1];
			}
			ans = min(ans, sum);
		}
		cout << ans;
	} else {
		int ans = 0;
		for (int i = 2; i <= k; i += 2)	ans += a[i] - a[i - 1];
		cout << ans;
	}
	return 0;
}
```

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

这里需要分类讨论一下：

如果剩余袜子的数量为偶数：将剩余袜子按照颜色值排序，然后每两个为一组。

如果剩余袜子的数量为奇数：将剩余袜子按照颜色值排序，然后求出一个前缀和，$p_i$ 表示前 $i$ 个袜子拼凑的最小值（注意这里 $i$ 必须是偶数），在求出一个后缀和，$s_j$ 表示从第 $j$ 个到第 $n$ 个袜子拼凑的最小值（注意这里 $j$ 必须时偶数）。最后我们枚举一下不与其他袜子配对的袜子 $k$，如果 $k$ 为奇数，那此时最小值就是 $p_{k - 1} + s_{k + 1}$；如果 $k$ 为偶数，那此时最小值就是 $p_{k - 2} + c_{k + 1} - c_{k - 1} + s_{k + 2}$（这里的 $c$ 是指颜色值）。

下面给一个为什么每相邻两个每一组就是对的的证明：

![](https://cdn.luogu.com.cn/upload/image_hosting/g4v7iefj.png)

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2e5 + 5;
vector<long long> G;
int n, k;
long long p[N * 4], s[N * 4];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> k;
	int now = 1;
	G.push_back(0);
	For(i, 1, k) {
		int a;
		cin >> a;
		while (now < a) {
			G.push_back(now);
			G.push_back(now);
			now++;
		}
		G.push_back(a);
		now++;
	}
	while (now <= n) {
		G.push_back(now);
		G.push_back(now); 
		now++;
	}
	sort(range(G));
	if ((int)G.size() % 2 == 1) {
		long long ans = 0;
		for (int i = 2; i <= (int)G.size() - 1; i += 2) {
			ans += G[i] - G[i - 1];
		} 
		cout << ans;
	} else {
		for (int i = 2; i < G.size(); i += 2) {
			p[i] = p[i - 2] + G[i] - G[i - 1];
		}
		for (int i = G.size() - 2; i >= 1; i -= 2) {
			s[i] = s[i + 2] + G[i + 1] - G[i];
		}
		long long ans = 1e18;
		for (int i = 1; i < G.size(); i++) {
			if (i % 2 == 0) {
				ans = min(ans, p[i - 2] + s[i + 2] + G[i + 1] - G[i - 1]);
			} else {
				ans = min(ans, p[i - 1] + s[i + 1]);
			}
		}
		cout << ans;
	}
	return 0;
}
```

### 谢谢观看！

---

## 作者：fcy20180201 (赞：0)

有点难度，反正比 D 难（？）。
## 题意
有 $N$ 双袜子，第 $i$ 双的颜色是 $i$。现在有 $K$ 双袜子只剩一只。若要把剩余的袜子重新配对（如果剩下奇数只袜子，多余的一只不配对），问所有袜子的 _怪异值_ 的和的最小值。

每双袜子的怪异值：两只袜子颜色编号的差的绝对值。
## 思路
要想让怪异值和最小，显然去掉不配对的袜子后，每双袜子要么**颜色尽量相邻**，要么**颜色相同**，所以将现有袜子的颜色全算出后将袜子按颜色排序。分类讨论：

- 如果剩下偶数只袜子，直接算。

- 否则用前后缀和求出**前几双袜子的怪异值和**和**后几双袜子的怪异值和**，再枚举不配对的袜子，用前后缀和计算每一种方案的答案。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b[400005],cur,dif[400005],cnt1[400005],cnt2[400005];
//空间记得开 2*N ！！！
int main(){
	scanf("%d%d%d",&n,&m,&a);
	for(int i=1,j=0;i<=n;i++){
		if(a==i)b[++cur]=i,(++j<m) && (scanf("%d",&a));
		else b[++cur]=i,b[++cur]=i;
	}//求所有袜子的颜色
	//由于前面颜色从小到大枚举，所以不用排序。
	if(!(cur&1)){//如果剩下偶数双袜子，直接算
		int ans=0;
		for(int i=2;i<=cur;i+=2)ans+=b[i]-b[i-1];
		printf("%d",ans);
		return 0;
	}	
	for(int i=1;i<=cur;i++)dif[i]=b[i]-b[i-1];//两只袜子的颜色差
	for(int i=2;i<=cur;i+=2)cnt1[i]=cnt1[i-2]+dif[i];
	//前几双袜子的怪异值和
	for(int i=cur;i>0;i-=2)cnt2[i]=cnt2[i+2]+dif[i];
	//后几双袜子的怪异值和
	int ans=1e9;
	for(int i=1;i<=cur;i+=2)ans=min(ans,cnt1[i-1]+cnt2[i+2]);
	//枚举不配对的袜子
	printf("%d",ans);
	return 0;
}
```

---

