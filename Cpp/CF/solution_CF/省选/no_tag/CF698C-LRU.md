# LRU

## 题目描述

While creating high loaded systems one should pay a special attention to caching. This problem will be about one of the most popular caching algorithms called LRU (Least Recently Used).

Suppose the cache may store no more than $ k $ objects. At the beginning of the workflow the cache is empty. When some object is queried we check if it is present in the cache and move it here if it's not. If there are more than $ k $ objects in the cache after this, the least recently used one should be removed. In other words, we remove the object that has the smallest time of the last query.

Consider there are $ n $ videos being stored on the server, all of the same size. Cache can store no more than $ k $ videos and caching algorithm described above is applied. We know that any time a user enters the server he pick the video $ i $ with probability $ p_{i} $ . The choice of the video is independent to any events before.

The goal of this problem is to count for each of the videos the probability it will be present in the cache after $ 10^{100} $ queries.

## 样例 #1

### 输入

```
3 1
0.3 0.2 0.5
```

### 输出

```
0.3 0.2 0.5 ```

## 样例 #2

### 输入

```
2 1
0.0 1.0
```

### 输出

```
0.0 1.0 ```

## 样例 #3

### 输入

```
3 2
0.3 0.2 0.5
```

### 输出

```
0.675 0.4857142857142857 0.8392857142857143 ```

## 样例 #4

### 输入

```
3 3
0.2 0.3 0.5
```

### 输出

```
1.0 1.0 1.0 ```

# 题解

## 作者：弦巻こころ (赞：6)

~~一道非常意识流的状压概率dp题()~~

有  $n$ 种物品和一个大小为  $k$ 的队列，有  $p_i$ 的概率会选择第  $i$ 种物品放入队列，如果队列已经有  $i$ 则将队列中的  $i$ 移到队尾。

如果队列中元素个数超过  $k$ 则弹出队首。

求  $10^{100}$ 次操作后每种物品留在队列的概率。

 $n,k \le 20$
 
 ### translate by yijan(斤老师yyds)
 
 首先考虑如果没有超过k弹出队首的限制怎么做,设dp[s]为当前队列状态出现的概率,那么转移方程比较显然.
 
$$
dp[s]=\sum_{i=1}^ndp[s-1<<(i-1)]/(1-\sum_{i=1}^np[i])(s\&1<<(i-1)) 
$$

就直接从之前状态转移在除上转移到自己的概率就行了.

考虑如果有k的限制怎么办,我们考虑倒着看这个序列,发现只有最后k个值是有用的,因为每得到一个数就会直接把他放到队尾,也就是说一旦倒着经过k种数,那么最后队列里就是这k个数.

所以相当于操作数其实没有什么太大影响,那么直接套用前面的dp转移方程就行了.

还有一种比较感性的证明,就是你假如 队列中队首为3剩下的两个数1,2.
那其实你3,1,2 与3,2,1 出现的比例与1,2和2,1是相同的,也就是说你弹出队首后其实就是之前k-1的情况,而这种情况在前面已经转移过了,所以不需要算k与k之间的转移.

(其实考场上你猜猜结论就好了 雾)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double
const int N=(1<<21);
const db eps=1e-12;
db f[N],p[N],as[N];
int n,k,tp;
int ct(int x){int k=0;
	while(x)k++,x-=x&(-x);return k;
}
int main(){
	scanf("%d%d",&n,&k);f[0]=1;
	for(int i=1;i<=n;i++)scanf("%lf",&p[i]),tp+=(p[i]>=eps);
	if(tp<=k){
		for(int i=1;i<=n;i++)if(p[i]>=eps)printf("1.00 ");else printf("0.00 ");exit(0);
	}for(int i=0;i<(1<<n);i++){if(ct(i)>k)continue;
		if(ct(i)==k){
			for(int j=0;j<n;j++)if(i&(1<<j))as[j+1]+=f[i];
			continue;
		}db tp=0;
		for(int j=0;j<n;j++)if(i&(1<<j))tp+=p[j+1];
		f[i]/=(1-tp);
		for(int j=0;j<n;j++)if(~i&(1<<j))f[i|(1<<j)]+=f[i]*p[j+1];
	} for(int i=1;i<=n;i++)printf("%.10lf ",as[i]);
}
```


---

## 作者：duyi (赞：3)

[洛谷的 latex 不行，请务必前往我的博客园查看！](https://www.cnblogs.com/dysyn1314/p/14297318.html)

# CF698C LRU

## 题目大意

[题目链接](https://codeforces.com/contest/698/problem/C)

有一个初始为空的队列，容量为 $k$。有 $n$ 种物品。

接下来会进行 $10^{100}$ 次操作。每次选择一个物品，物品 $i$ 有 $p_i$ 的概率被选中。如果被选中的物品不在队列中，则将它加入队列。此时如果队列长度大于 $k$，则弹出“上一次被选中的时间”最早的物品。

问所有操作结束后，每个物品仍在队列中的概率。保留 $6$ 位小数。

数据范围：$1\leq k\leq n\leq 20$，$0\leq p_i\leq 1$，$\sum p_i = 1$。

## 本题题解

考虑对每个物品分别求答案。那么有两种情况：

1. 操作结束时，队列内不到 $k$ 种物品。
2. 操作结束时，队列内有 $k$ 种物品（是满的）。

如果 $p_i \neq 0$ 的物品数 $< k$，显然只能是情况 1。因为操作次数极大，而且不发生弹出，所以所有 $p_i\neq 0$ 的物品答案都是 $1$。

否则，在经过了 $10^{100}$ 次操作后，情况 1 出现的概率可以近似视为 $0$。故以下只考虑情况 2。

考虑最终的队列里有哪些物品。发现就是最后加入的 $k$ **种**物品。例如，$k = 3$，若操作序列（每次选择的物品）为：$\dots ,2,2,1,5,1,3,3,4$，则最终队列里就是：$\{1,3,4\}$。

考虑状压 DP。设 $\text{dp}(s)$ 表示操作序列的一个**后缀**里，物品集合为 $s$ 的概率。$s$ 是一个二进制状压。

转移时，枚举下一个还未在 $s$ 内出现过的物品，记为物品 $u$（其实是操作序列更前面的物品，因为根据状态设计，我们是从后往前 DP 的）。设 $\text{sum}(s) = \sum_{v\in s}p_v$。则：
$$
\forall u\notin s, p_u\neq 0: \quad \text{dp}(s)\cdot (p_u + \text{sum}(s)\cdot p_u + \text{sum}(s)^2\cdot p_u + \dots) \to \text{dp}(s \cup \{u\})
$$
括号里的式子，表示：【下一次就选中 $u$ 的概率】 $+$ 【先选中一个已有的数，再下次才选中 $u$ 的概率】 $+$ 【下下下次才选中 $u$ 的概率】 $\dots$。因为操作次数极大，所以有：
$$
\begin{align}
&\text{dp}(s) \cdot \sum_{i = 0}^{\infty} \text{sum}(s)^i \cdot p_u\\
=& \text{dp}(s)\cdot p_u\cdot \sum_{i = 0}^{\infty} \text{sum}(s)^i\\
=& \text{dp}(s)\cdot p_u\cdot \frac{1}{1 - \text{sum}(s)}
\end{align}
$$
也可以这样理解上述的转移式：只要选到 $s$ 里的数，我们就**假装无事发生，再选一次**。浪费的这一次操作对答案没有影响，因为总操作次数近似无穷大。所以这就等价于，我们**强行把 $s$ 集合里已有的数，被抽到的概率视为 $0$**。剩下的数概率对应地变为：$\displaystyle p_u' = \frac{p_u}{\sum_{v\notin s}p_v} = \frac{p_u}{1 - \text{sum}(s)}$。

于是就可以转移了。

边界是：$\text{dp}(0) = 1$。物品 $i$ 的答案就是 $\displaystyle \sum_{i\in s, |s| = k}\text{dp}(s)$。

时间复杂度 $\mathcal{O}(2^nn)$。

## 参考代码

```cpp
// problem: CF698C
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 20;

int n, K;
int hibit[1 << MAXN], bitcnt[1 << MAXN];
double p[MAXN + 5], sum[1 << MAXN];
double f[1 << MAXN];

int main() {
	cin >> n >> K;
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
		cnt += (p[i] != 0);
	}
	if (cnt < K) {
		for (int i = 1; i <= n; ++i) {
			cout << (p[i] == 0 ? 0 : 1) << ".00000000" << " \n"[i == n];
		}
		return 0;
	}
	
	for (int i = 1; i <= n; ++i) {
		hibit[1 << (i - 1)] = i;
	}
	for (int i = 1; i < (1 << n); ++i) {
		bitcnt[i] = bitcnt[i - (i & (-i))] + 1;
		sum[i] = sum[i - (i & (-i))] + p[hibit[i & (-i)]];
	}
	
	f[0] = 1;
	for (int i = 1; i < (1 << n); ++i) {
		if (bitcnt[i] > K)
			continue;
		for (int _j = i; _j; _j -= (_j & (-_j))) {
			int j = hibit[_j & (-_j)];
			
			assert((1 << (j - 1)) == (_j & (-_j)));
			
			if (p[j] == 0)
				continue;
			
			f[i] += f[i ^ (1 << (j - 1))] * (p[j] / sum[((1 << n) - 1) ^ i ^ (1 << (j - 1))]);
		}
	}
	cout << setiosflags(ios :: fixed) << setprecision(10);
	
	for (int i = 1; i <= n; ++i) {
		/*
		double ans = pow(1.0 - p[i], 100000000); // 没出现过 
		for (int s = 0; s < (1 << n); ++s) {
			if (((s >> (i - 1)) & 1) == 0 && bitcnt[s] >= K) {
				ans += p[i] / sum[((1 << n) - 1) ^ s] * f[s]; // 出现了但被代替 
			}
		}
		ans = 1.0 - ans;
		cout << ans << " \n"[i == n];
		*/
		
		double ans = 0;
		for (int s = 0; s < (1 << n); ++s) {
			if (((s >> (i - 1)) & 1) && bitcnt[s] == K) {
				ans += f[s];
			}
		}
		cout << ans << " \n"[i == n];
	}
	return 0;
}
```











---

## 作者：qianfujia (赞：3)

看到这题没题解，吓得我赶紧来水一发

因为$10^{100}$灰常大，所以最后还没有填满k个的概率很小（当然概率不为0的数的个数$<=k$的情况除外）

所以我们只需强行在上面跑概率dp即可，注意在对于一个已选集合$S$，还是由于$10^{100}$是一个极大值，所以强制其向后转移，所以要对$dp[S]$进行$dp[S]=dp[S]/\sum_{i\notin S} p[i]$

$p.s.\ $附上提醒：此题精度要求较高，$eps$要小一点

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-12;
int n, k;
double dp[1<<20], p[21], ans[21];
inline int count1(int x){
	int tmp = 0;
	while(x)x-=(x&(-x)), ++tmp;
	return tmp;
}
int main(){
	int tmp = 0;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++ i)scanf("%lf", &p[i]), tmp += (p[i] >= eps);
	if(tmp <= k){
		for(int i = 1; i <= n; ++ i)printf(p[i] >= eps ? "1 " : "0 ");
		return 0;
	}
	dp[0] = 1;
	for(int i = 0; i < (1 << n); ++ i){
		if(count1(i)==k){
			for(int j = 0; j < n; ++ j)
				if(i&(1<<j)) ans[j+1] += dp[i];
			continue;
		}
		if(dp[i]<eps) continue;
		double tmp = 0;
		for(int j = 0; j < n; ++ j)if(i&(1<<j))tmp+=p[j+1];
		dp[i]/=(1-tmp);
		for(int j = 0; j < n; ++ j)if(~i&(1<<j))dp[i|(1<<j)]+=dp[i]*p[j+1];
	}
	for(int i = 1; i <= n; ++ i)
		printf("%.8lf ", ans[i]);
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：2)

~~看到1e100的第一眼是懵逼的~~

但我们稍加推理后发现，经过1e100次计算后，只有两种情况，

- 队列未填满
- 队列已满


------------


对于情况一
,很明显的是，如果概率大于0的物品件数 ≤ k ,队列就不可能被填满，概率大于0的物品一定会被选中，即
$$\sum_{i=1}^n sgn(p_i) \leq k$$
那么很显然物品i的概率为
$$sgn(p_i)$$
sgn()的的定义[戳](https://baike.so.com/doc/6702853-6916804.html)




------------


情况二就要开始~~乱搞~~严谨dp了

在1e100次操作后，某样物品的概率十分接近于此物品队列已满情况下概率，我们可以认为两数相等

用集合A表示当前队列的状态,集合B表示未选的集合，那么很容易推出，选到x(x∈B)的概率为
$$\frac{p_x}{\sum_{i∈B}pi} $$

那么如果用f(A)表示A状态的概率，那么它对f(A∪{x})的贡献就为
$$f_A*\frac{p_x}{\sum_{i∈B}pi}$$
那么最终的答案就是
$$ans_i=\sum_{i∈A,|A|=k}f_A$$

然后我们只剩下了最后一个问题，如何在C++里表示集合

由于这道题的n很小，完全可以用状压，用一个数来表示某个状态，然后就可以愉快的dp了
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=21;
int n,k;
long double p[maxn],f[1<<maxn];
long double ans[maxn];
/*
f[x]表示 S状态的概率
x=Σ2^Si  状压
若a不在集合S中
f[x|(2^a)]= f[x]*(Pa/ΣPa)
*/
//#define debug 1
void dp(int x){
	//处理x状态
	int cnt=0;
	long double tot=0;
	for(int i=1;i<=n;i++){
#ifdef debug
		cout<<i<<" "<<(x&(1<<(i-1)))<<endl;
#endif
		if((x&(1<<(i-1)))==0)
			tot+=p[i];
		else
			cnt++;
	}
#ifdef debug
	cout<<x<<" "<<tot<<" "<<cnt<<endl;
#endif
	if(cnt>k)
		return;
	else if(cnt==k)
		for(int i=1;i<=n;i++){
			if(x&(1<<(i-1)))
				ans[i]+=f[x];
		}
	else
		for(int i=1;i<=n;i++)
			if((x&(1<<(i-1)))==0)
				f[x|(1<<(i-1))]+=f[x]*(p[i]/tot);
}
signed main(){
	f[0]=1;int __tmp__=0;
	cin>>n>>k; 
	for(int i=1;i<=n;i++){
		cin>>p[i];
		if(p[i]>1e-8)__tmp__++;
		//cout<<p[i]<<endl;
	} 
	if(__tmp__<=k){//不可能填满 
		//printf ("No way to fill\n");
		for(int i=1;i<=n;i++){
			if(p[i]>1e-8)
				printf("1 ");
			else
				printf("0 ");
		}
		return 0;
	}
	//一定能填满
	for(int i=0;i<(1<<n);i++)
	 	dp(i);//处理i状态
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" "; 
} 
```

---

## 作者：Yuno (赞：1)

看见这种 $10^{100}$ 的，一般当作 $\infty$ 来做就行。

所以一个元素已经在队列内，就可以把它的概率当作$0$，并按比例提高其他元素的概率。

考虑一个元素在队列内要满足什么情况。

略加思考就会发现一个元素在队列内，当且仅当最后 $k$ 次入队操作里有出现这个元素。

于是我们的目标就是求出所有 $A_n^k$ 种队列方案的概率。

假如已知一个状态下的概率，那么这个状态再加一个物品的概率是很好求的。

但是这个状态太多了，有 $A_n^k$ 个，考虑简化状态。

发现顺序是可以不用考虑的。

设 $dp_S$ 表示状态为 $S$ 时的概率（不考虑顺序，也就是说每种顺序都要算）。

设 $T$ 表示从 $S$ 中去掉一个元素的状态，并且那个元素的下标为 $i$。

那么 $dp_S=\sum dp_T\times P(i,T)$

这里 $P(i,T)$ 表示在 $T$ 这个状态下选到 $i$ 的概率。

答案 $ans_i$ 就等于每个包含 $k$ 个元素且包含 $i$ 元素的状态的概率之和。

注意：

1.空间，别开 $long\ double$

2.假如概率大于 $0$ 的元素不足 $k$ 个，假设有 $cnt$ 个，要把 $k$ 赋值成 $cnt$。

3.枚举状态不能按照普通的状压 $dp$， 要按每个状态中的元素个数排序后枚举。

复杂度：$O(n\times 2^k)$

$Code:$

```cpp
#include <bits/stdc++.h>
#define ld long double
 
using std::cin;
using std::cout;
 
const int N = 21, maxn = 7 + (1 << 20);
 
struct node{
	int id, val;
	bool operator < (const node &a)const {
		if (val == a.val) return id < a.id;
		else
		return val < a.val;
	}
}q[maxn];
 
int n, k;
double a[N], p[N][maxn], dp[maxn], ans[N];
bool vis[N];
 
int main() {
	std::ios::sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 0; i < n; ++ i) cin >> a[i];
	int res = 0;
	for (int i = 0; i < n; ++ i) res += (a[i] > 0);
	k = std::min(k, res);
	for (int S = 0; S < (1 << n); ++ S) {
		memset(vis, 0, sizeof(vis));
		double sum = 0;
		for (int i = 0; i < n; ++ i) {
			if (S & (1 << i)) continue;
			vis[i] = 1;
			sum += a[i];
		}
		for (int i = 0; i < n; ++ i) {
			if (!vis[i]) {
				p[i][S] = 0;
				continue;
			}
			if (sum == 0) p[i][S] = 0;
			else p[i][S] = a[i] / sum;
		}
	}
	int cnt = 0;
	for (int S = 0; S < (1 << n); ++ S) {
		q[++ cnt].id = S;
		q[cnt].val = __builtin_popcount(S);//用STL算元素个数
	}
	std::sort(q + 1, q + 1 + cnt);
	dp[0] = 1.0;
	for (int i = 2; i <= cnt; ++ i) {
		int S = q[i].id;
		for (int j = 0; j < n; ++ j) {
			if (!(S & (1 << j))) continue;
			int T = S ^ (1 << j);
			dp[S] += dp[T] * p[j][T];
		}
		if (i == cnt) break;
		if (q[i + 1].val > k) break;
	}
	for (int S = 0; S < (1 << n); ++ S) {
		if (__builtin_popcount(S) != k) continue;
		for (int i = 0; i < n; ++ i) {
			if (!(S & (1 << i))) continue;
			ans[i] += dp[S];
		}
	}
	for (int i = 0; i < n; ++ i) cout << std::setprecision(10) << ans[i] << ' ';
	return 0;
} 
```



---

## 作者：幻影星坚强 (赞：1)

最后留下了k个的概率其实相当于一开始k个的概率（即将所有操作倒着来考虑）。

发现$n$只有20，所以我们可以通过状态压缩来保存队列中的状态。假如当前状态为$dp_i$，接下来要插入$p_j$概率这个物体，$w_i$代表队列中的数的概率和。那么插入这个物品的概率即为$p_j$（第一轮就选到）+$p_j*w_j$（前一轮只选到队列中的数，这一轮选到）+$p_j*w_j^2$（前两轮只选到队列中的数，这一轮选到）……

也就是：

$\sum\limits_{k=0}p_j*w_i^k = p_j / (1 - w_j)$

（由于操作次数很大所以视为无穷大）

而操作次数很大所以只要能取得物品超过k队列就一定会满，每个物体出现概率即为每个包含它满队列的状态的概率之和

若能取物品不超过k那么所有能取得物品必然会出现在队列里

```
#include <iostream>
#include <cstdio>
using namespace std;
int n, k, tot, num[1 << 21];
double p[30], dp[1 << 21], z[1 << 21], a[30];
int cnt(int o)
{
	int ans = 0;
	while(o > 0)
	{
		++ ans;
		o -= (o & (-o));
	}
	return ans;
}
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++ i)
	{
		scanf("%lf", &p[i]);
		if(p[i] > 0)
		++ tot;
		num[(1 << (i - 1))] = i;
	}
	if(tot <= k)
	{
		for (int i = 1; i <= n; ++ i)
		{
			printf("%d ", p[i] > 0 ? 1 : 0);
		}
		return 0;
	}
	for (int i = 1; i < (1 << n); ++ i)
	{
		z[i] = z[i - (i & (-i))] + p[num[i & (-i)]];
	}
	dp[0] = 1;
	for (int i = 0; i < (1 << n); ++ i)
	{
		int c = cnt(i);
		if(c >= k)
		{
			if(c == k)
			{
				for (int j = 1; j <= n; ++ j)
				{
					if(i & (1 << (j - 1)))
					a[j] += dp[i];
				}
			}
			continue;
		}
		for (int j = 1; j <= n; ++ j)
		{
			if(i & (1 << (j - 1)))continue;
			dp[i | (1 << (j - 1))] += dp[i] * p[j] / (1.0 - z[i]);
		}
	}
	for (int i = 1; i <= n; ++ i)
	{
		printf("%.10lf ", a[i]);
	}
}
```


---

## 作者：灵梦 (赞：1)

因为 $10^{100}$ 相对于这道题要求的精度是一个很大的数，所以每个数最终在队列中的概率会趋近于一个固定的值，也就是我们要求的答案。设 $g(i,S)$ 表示进行 $i$ 次操作后，队列中元素为集合 $S$ 的概率。那么当 $i$ 趋近无穷大时，$g(i,S)=g(i+1,S)$，我们可以通过这个关系列出一组线性方程来解出它们。但是这个状态是有后效性的，而高斯消元的复杂度无法承受。所以我们改设状态为 $f(S)$ 表示经过足够多次操作后，队列中元素**包含子集 $S$** 的概率。这样我们就可以 DP 求解了：只用考虑不在这个子集内的元素，每次转移时枚举这些元素并将它们加入即可。

注意需要特判概率不为 $0$ 的元素不足 $k$ 个的情况。

```cpp
#include <cstdio>
const int MAXN=22;
const int MAXS=1100000;
double p[MAXN], f[MAXS], ans[MAXN];
int main()
{
//	freopen("C.in", "r", stdin);
//	freopen("C.out", "w", stdout);
	int n, k, cnt=0;
	scanf("%d%d", &n, &k);
	for (int i=0; i<n; i++)
	{
		scanf("%lf", &p[i]);
		if (p[i]>0) cnt++;
	}
	if (cnt<=k)
	{
		for (int i=0; i<n; i++) printf("%d ", p[i]>0);
		putchar('\n');
		return 0;
	}
	f[0]=1;
	for (int s=0; s<1<<n; s++)
	{
		if (__builtin_popcount(s)==k)
			for (int i=0; i<n; i++)
				if (s&1<<i) ans[i]+=f[s];
		double tmp=0;
		for (int i=0; i<n; i++)
			if (~s&1<<i) tmp+=p[i];
		tmp=f[s]/tmp;
		for (int i=0; i<n; i++)
			if (~s&1<<i) f[s|1<<i]+=tmp*p[i];
	}
	for (int i=0; i<n; i++) printf("%.7lf ", ans[i]);
	putchar('\n');
	return 0;
}
```


---

## 作者：Prean (赞：0)

为什么 $ n,k \leq 20 $？

我还以为是什么 $ n,k \leq 10^6 $ 的厉害题/qd

看到这个队列操作很迷惑，但是仔细看看要操作 $ 10^{100} $ 遍，所以我们可以直接将这个题意理解成在 $ n $ 个数里面选 $ k $ 个数的概率。

这就很简单了，因为 $ n \leq 20 $，所以我们直接大力枚举包含 $ i $ 的子集，然后计算选到这个子集的概率，然后就没了。

这个东西很容易用子集 dp 来转移，子集的概率之和也可以使用 FWT 来计算。

记得特判某些情况会输出 `nan`。
```cpp
#include<cstdio>
#include<cmath>
int n,x,S,cnt,siz[1<<20];double ans[20],s[1<<20],P[1<<20];
signed main(){
	int i,k,len;
	scanf("%d%d",&n,&x);S=1<<n;s[0]=1;
	for(i=0;i^n;++i)scanf("%lf",P+(1<<i)),cnt+=P[1<<i]!=0;if(cnt<x)x=cnt;
	for(len=1;len^S;len<<=1)for(k=0;k^S;k+=len<<1)for(i=0;i^len;++i)P[i|k|len]+=P[i|k];
	for(i=0;i^S;++i){
		siz[i]=siz[i>>1]+(i&1);
		for(k=0;k^n;++k)if(i>>k&1)s[i]+=s[i^1<<k]*P[1<<k]/P[S-1^i^1<<k];
		if(siz[i]==x)for(k=0;k^n;++k)if(i>>k&1)ans[k]+=s[i];
	}
	for(i=0;i^n;++i)printf("%.9lf ",ans[i]);
}
```

---

