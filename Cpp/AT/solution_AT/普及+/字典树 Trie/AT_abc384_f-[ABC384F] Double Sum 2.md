# [ABC384F] Double Sum 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc384/tasks/abc384_f

正整数 $ x $ に対して $ f(x) $ を「 $ x $ が偶数である間 $ x $ を $ 2 $ で割り続けたときの、最終的な $ x $ の値」として定義します。例えば $ f(4)=f(2)=f(1)=1 $ 、 $ f(12)=f(6)=f(3)=3 $ です。

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,\ A_N) $ が与えられるので、 $ \displaystyle\ \sum_{i=1}^N\ \sum_{j=i}^N\ f(A_i+A_j) $ を求めてください。

## 说明/提示

### 制約

- $ 1\le\ N\le\ 2\times\ 10^5 $
- $ 1\le\ A_i\le\ 10^7 $
- 入力は全て整数
 
### Sample Explanation 1

$ f(A_1+A_1)=f(8)=1 $ 、 $ f(A_1+A_2)=f(12)=3 $ 、 $ f(A_2+A_2)=f(16)=1 $ です。したがって、 $ 1+3+1=5 $ を出力してください。

## 样例 #1

### 输入

```
2
4 8```

### 输出

```
5```

## 样例 #2

### 输入

```
3
51 44 63```

### 输出

```
384```

## 样例 #3

### 输入

```
8
577752 258461 183221 889769 278633 577212 392309 326001```

### 输出

```
20241214```

# 题解

## 作者：KazamaRuri (赞：20)

## 题意

求序列中每个有序对的和抹去二进制末尾后连续的 $0$ 后的和。

## 分析

简单题，考虑转化贡献，两个数的和末尾有 $k$ 个 $0$，那么直接右移 $k$ 就是贡献。借此想到枚举末尾有多少 $0$，然后用桶或者 trie 简单计算末尾至少有 $k$ 个 $0$ 的和，差分就一下就是恰好 $k$ 位的和，右移 $k$ 统计入答案即可。时间复杂度 $O(n\log V)$。

## 代码


```cpp
#include <bits/stdc++.h>
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
using namespace std;
using ll=long long;
const int N=2e5+5,V=1e7+5;
ll n,a[N],t[1<<24],c[1<<24],f[25],ans;
inline ll inv(ll x,ll s){ return s&(s+1-(x&s)); }
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	reverse(a+1,a+1+n);
	for(int k=24;~k;k--){
		ll s=(1<<k)-1;
		for(int i=1;i<=n;i++){
			t[a[i]&s]+=a[i],c[a[i]&s]++,
			f[k]+=t[inv(a[i],s)]+c[inv(a[i],s)]*a[i];
		}
		for(int i=1;i<=n;i++) t[a[i]&s]=c[a[i]&s]=0;
		ans+=f[k]-f[k+1]>>k;
	}
	return printf("%lld",ans)&0;
}
```

---

## 作者：Moya_Rao (赞：9)

# 前言

题目已经够简洁了，不给题目大意啦。

作者是蒟蒻，原本不会做此题，看题解，结果一篇都看不懂！实在有点儿抽象了，咋用那么多位运算呢，对我这种菜鸡有点儿不有好了。

因此经过自己一整天的琢磨，终于想透了做法，于是准备梳理一遍，顺便给各位想做此题的蒟蒻们一个友好的帮助。

# 思路开端

此题，如果正着做，为什么觉得时间复杂度永远都只能停留在 $O(N^2)$ 了呢？当然，别的题解有正着做的，可以学一学，但是菜鸡作者不会啊。

俗话说：“正难则反”。好，正难则反！那我们反过来吧，用一个容斥的思想。具体怎么做，就跟着我一步步来吧。

# 正难则反

回到“正难则反”这个原则，到底要怎么“反”呢？

来，各位，排除掉自己结合自己的话，算个数吧。想一想，下面这个东西好不好算呢？

$$\sum _ {i = 1} ^ N\sum _ {j = i+1} ^ N ( a_i + a_j ) $$

是不是很好算？对，其实上就是：

$$\sum _ {i = 1} ^ N (a_i \times (N-1))$$

这个值，计算起来是 $O(n)$ 的，可以在输入的时候就算出来。

至于我们上面没有考虑到的，也就是自己和自己结合的那种情况，其实也可以直接算啦，就是算 $f(a_i \times 2)$，其实上就是 $f(a_i)$ 啦，因为按照 $f$ 函数的计算原则，那个 $\times 2$ 会被消掉呀。把这些也加进目前的 $ans$ 里，就能生成出最开始的 $ans$ 啦。

接下来只需要减去 $ans$ 里的多余部分就可以了。

# 先来考虑超时做法

来，我们先来考虑一下那个会超时的 $O(N^2)$ 算法吧。

直接讲不好讲啊，我来举个例子吧。

这里，$n = 4$，$a=\{1,4,3,5\}$。

首先我们可以 $O(N^2)$ 生成出一个 $s$ 数组，存储一下这个 $a$ 数组中两两之间的和。

那么对于这个例子，$s=\{5,4,6,7,9,8\}$。

接下来我们来想一想，一个数值，比方说 $24$，当然这是随便举的例子啦，它是怎么变成 $f(24)$，即 $3$ 的呢？减少了 $21$ 对不对？

其实上，它拥有一个 $2$ 的整次幂因子，是谁？对，是 $2^3$，也就是 $8$。

那我们可以用 $8$ 去消掉它多余的部分呀，对不对？是的，其实上就是让 $24$ 减少了 $\frac{8-1}{8}$，是吧？算一算，诶，好像还真是！

但是这个什么 $\frac{8-1}{8}$，感觉怪讨厌的，要是能拆成一些几分之一加起来就好了。这不好办吗？有点儿数学基础的就知道，其实上 $\frac{8-1}{8}=\frac{1}{8}+\frac{1}{4}+\frac{1}{2}$！

那就好处理了，而且刚才所说的 $24$ 其实上不只是 $8$ 这一个 $2$ 的整次幂的倍数嘛，也是 $4$ 以及 $2$ 的倍数呀！分数里边，作为分母的也有 $4$ 和 $2$！这就好办啦，懂了没，各位？

推广一下，也就是说，$s$ 数组里的每个数，都要找到它对应的一些 $2^k$，当然要保证 $k$ 为正整数，然后根据上面的公式计算需要减少多少，就好啦！

我们可以枚举每个 $k$，再去 $s$ 数组里一个一个数字比对，就行咯！

# 但如何不超时呢

可是，上面讨论的都是 $O(N^2)$ 的呀，不能接受！怎么办？

对，现在要讲的就是，如何使我们上面所讨论的那种算法，不超时。

这好办，只需要请出一位嘉宾：余数！

什么，余数？对呀，想起来没有，两个数的和是不是另一个数的倍数，不是可以通过这两个数对这另一个数的余数来判断吗？哇！反应过来没有？

好好好，先别激动，让我阐述一下到底该怎么做。

还是拿上面的那个 $a=\{1,4,3,5\}$ 的例子来说。

我们首先可以让 $k=1$，那我们要处理的这个数就是 $2^1$ 即 $2$，这里就用 $g$ 代替吧，目前 $g$ 是 $2$ 哟。

当然在此之前要准备好两个数组，一个 $sum$ 数组，一个 $cnt$ 数组，其中 $sum_i$ 存储的是，目前考虑到的所有数中，对 $g$ 取模为 $i$ 的数的总和，而 $cnt_i$ 存储的则是目前考虑到的所有数中，对 $g$ 取模为 $i$ 的数的总个数。一开始要先清空他们两个哦。

接下来开始遍历 $a$ 数组！

首先 $i=1$，遍历到的 $a_i$ 是 $1$，这个 $1$ 对 $2$ 取模是 $1$，反过来，跟它拼起来是 $2$ 的倍数的那个数，对 $2$ 取模就是 $2-1$ 咯。  
但是由于刚刚才开始遍历，所以什么收获都没有，只是单单把 $a_1$ 的数据记录进两个数组中。

接下来 $i=2$，遍历到的 $a_i$ 是 $4$，现在这个 $4$ 对 $2$ 取模变成 $0$ 啦，反过来跟它拼起来的（之后称为“反模数”），会是取模为 $2-0=2$ 的吗？不可能，因为对 $2$ 取模，这个数一定会变得比 $2$ 小才对呀，所以还要再对 $2$ 取一次模，变成 $0$。  
调查一下，$cnt_0$ 以及 $sum_0$ 里，什么数据都没有存储，没东西哟，那还是只能记录当前情况，不能使 $ans$ 减少。

然后遍历到 $i=3$ 啦，$a_i$ 是 $3$，它的模数是 $1$，反模数也是 $1$ 咯。这次的 $1$ 数据库里存了东西吗？存啦，存了之前 $i=1$ 时记录下的数据呀！  
那么就可以产生一次贡献了，这个贡献其实上是 $(cnt_1 \times a_3 + sum_1) \div 2$。可是，为什么要这么干？  
因为这一次是特殊情况，$cnt_1$ 里边只有 $1$，也就是说当前可以和它相加成功的只有一个数，但如果有多个，这个 $a_3$ 就得累加多次了，累加 $cnt_1$ 次嘛。不过这个 $sum_1$ 存的是之前那些数的和，可以直接加进去。  
至于那个 $\div 2$，其实上等同于 $\times \frac{1}{2}$ 呀，不过是更好在代码里体现罢了。如果你不清楚这里为什么要 $\times \frac{1}{2}$，请返回去再看一看哟，前面讲过滴！

最后 $i=4$ 的情况，应该不需要我再说一遍吧，上面讲得已经够清楚啦。如果还是有点儿迷惑，可以自己摇一摇 $i=4$ 的情况来辅助理解。

接下来升级 $k$ 和 $g$，就直接让 $k$ 变成 $k+1$，$g$ 变成 $g \times 2$ 即可。还可以发现 $k$ 其实是没有用的，所以可以直接用 $g$ 来做循环变量，从 $2$ 开始，依次 $\times 2$。

对了，那这个 $g$ 枚举到什么时候就打断循环呢？如果设 $mx$ 为 $a_i$ 中的最大值，那么这个 $g$ 只要不超过 $mx \times 2$，就可以继续，超过了就跳出循环。  
为什么？因为 $mx$ 是最大的呀，它自己和自己相加一定是和里边最大的了吧。如果 $g$ 都超过 $mx$ 自己和自己相加，也就是 $mx \times 2$ 了，那还能有哪个两个数之和会是 $g$ 的倍数呢？这就没有枚举的必要了呀，所以是这个限制。

说到现在，你一定知道怎么做了，代码编起来很简单，就别看我的了吧！不过，我还是会把代码贴上哟。

# 代码
注意代码里的 $k$ 其实指的就是思路里所说的 $g$，其他变量名都统一。随你怎么看吧！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5 , M = 2e7+5;
long long n,a[N],cnt[M],sum[M],mx,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];mx=max(mx,a[i]);
        ans+=a[i]*(n-1);
        long long tmp=a[i];
        while(tmp%2==0)tmp/=2;
        ans+=tmp;
    }
    for(int k=2;k<=mx*2;k*=2){
        memset(cnt,0,sizeof(cnt));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            int zm=a[i]%k,fm=(k-a[i]%k)%k;
            if(cnt[fm])ans-=(sum[fm]+cnt[fm]*a[i])/k;
            cnt[zm]++,sum[zm]+=a[i];
        }
    }
    cout<<ans;
    return 0;
}
```
如果看懂了就给个赞吧，谢谢！

---

## 作者：2022dyx (赞：9)

# [ABC384F] Double Sum 2 题解
### solution
题目里的 $f$ 函数正着做显然性质很不好，$O(n ^ 2) $ 的暴力几乎没有优化余地。正难则反，$\displaystyle \sum _ {i = 1} ^ {N} \displaystyle \sum _ {j = i} ^ {N} (A _ i + A _ j)$ 显然是好求的，设它为 $ans$，考虑减掉多的部分。

可以发现，如果设 $x$ 最低位的 $1$ 所在的位为 $y$， 那么有 $f(x) = \frac {1} {2 ^ y} x$，也就是需要减掉 $\frac {2 ^ y - 1} {2 ^ y} x$，但是这样还是没法做，因为最低位的 $1$ 这个东西的性质还是不太好。看到 $x$ 前的系数，我们可以敏锐地想到这个东西等于 $\displaystyle \sum _ {k = 1} ^ {y} \frac {1} {2 ^ k} $，此时对 $k$ 的约束相当于 $x$ 是 $2 ^ k$ 的倍数。

换个角度想，也就是说对于每个 $2 ^ k$，设所有和为其倍数的 $(i, j)$ 对权值之和为 $sum$，答案就要减去 $\frac {sum} {2 ^ k}$，这就可以通过开 `map` 记录每一个权值下的个数与权值和来做了。
### code
与上文变量名不同，请注意分辨。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N], ans;
unordered_map <int, int> cnt, mp;
signed main() {
	cin.tie(0) -> sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	int now = 0;
	for (int i = 1; i <= n; ++i) now += a[i], ans += now + i * a[i];
	for (int i = 2; i < 2e7; i <<= 1) {
		int now = 0;
		for (int j = 1; j <= n; ++j) {
			++cnt[a[j] % i];
			mp[a[j] % i] += a[j];
			now += mp[(i - a[j] % i) % i] + a[j] * cnt[(i - a[j] % i) % i];
		}
		for (int j = 1; j <= n; ++j) {
			--cnt[a[j] % i];
			mp[a[j] % i] -= a[j];
		}
		ans -= now / i;
	}
	cout << ans;
}
```

---

## 作者：__O_v_O__ (赞：6)

假设 $g_x$ 表示所有能被 $2^x$ 整除的 $A_i+A_j$ 的和，那么答案就是 $\sum\limits_{i=0}\frac{g_i-g_{i+1}}{2^i}$。

怎么理解？因为 $g_i$ 是被 $2^i$ 整除的和，$g_{i+1}$ 是被 $2^{i+1}$ 整除的和，那么 $g_i-g_{i+1}$ 就是刚好含有 $i$ 个因子 $2$ 的和。也就是说，$g_i-g_{i+1}$ 中的数的 $f$ 值都是该数除以 $2^i$，$f$ 值之和就是 $\frac{g_i-g_{i+1}}{2^i}$。

现在考虑计算 $g_x$。我们需要计算以下两个东西：$p_i$ 为 $A_i+A_j$ 整除 $2^x$ 的 $j$ 的个数，$q_i$ 为 $A_i+A_j$ 整除 $2^x$ 的 $A_j$ 的和，那么 $g_x=\sum\limits_{i=1}^np_iA_i+q_i$。

如何处理 $p,q$？只需从前往后遍历数组，同时使用桶记录前面模 $2^x$ 的个数与和，然后 $O(1)$ 计算即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e7+5;
int n,a[200001],su;
int p[N],q[N],la,g[200001];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=0;i<=25;i++){
		int k=(1ll<<i),an=0;
		for(int j=1;j<=n;j++){
			int no=a[j]%k;
			p[no]++;
			q[no]+=a[j];
			an+=(p[(k-no)%k]*a[j]+q[(k-no)%k]);
		}
		for(int j=1;j<=n;j++)p[a[j]%k]=q[a[j]%k]=0;
		g[i]=an;
	}
	for(int i=0;i<=25;i++){
		su+=(g[i]-g[i+1])/(1ll<<i);
	}
	cout<<su;
	return 0;
}
```

---

## 作者：ForgetOIDuck (赞：3)

看题解区似乎都是好多神奇做法我看不懂，我直接正着做。

首先按照 $\operatorname{lowbit}$ 从小到大排序，假设我们当前考虑到位置 $a_i$，前面的某个数为 $a_j(j<i)$。

若他们 $\operatorname{lowbit}(a_j)>\operatorname{lowbit}(a_i)$，则 $\operatorname{lowbit}(a_i+a_j)$ 必定等于 $\operatorname{lowbit}(a_i)$。这很好维护。重点在于 $\operatorname{lowbit}(a_j)=\operatorname{lowbit}(a_i)$ 的情况。

假设现在有两个数 `101100` `110100`，他们的 $\operatorname{lowbit}$ 是相等的，于是我们考虑 $\operatorname{lowbit}$ 后面的部分，看有没有可能产生更多的末尾 $0$。容易发现只要从 $\operatorname{lowbit}$ 后一位开始从低到高若他们的每一位一直都是不一样的，那么可以一直产生 $0$。

如刚刚的两个数，他们的和是 `1100000`, 在从低到高第 $5$ 位出现了 $1$，这也是他们从 $\operatorname{lowbit}$ 开始第一个一样的地方。

有点最大异或和那味了，发现这东西可以用 trie 树维护。

当然还有一些细节处理一下就完了。时间复杂度 $O(n\log V)$，最慢点 276 ms。

trie 需要开到 $9\times10^6$。

附上马蜂不优良 `AC` 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node {
	ll sum, cnt, s0, s1;
}trie[9000002];
ll n, a[200002], ans, r, idx, now;
ll lowbit(ll x) {
	if (! x) return 114514;
	return x & (-x);
}
bool cmp(ll az, ll bz) {
	return lowbit(az) > lowbit(bz); 
}
ll s0(ll x) {
	if (! trie[x].s0) trie[x].s0 = ++ idx;
	return trie[x].s0;
}
ll s1(ll x) {
	if (! trie[x].s1) trie[x].s1 = ++ idx;
	return trie[x].s1; 
} 
ll fd(ll x, ll p, ll d) {
	if (d > 30) return 0; 
	if (x & (1 << d)) return ((trie[s1(p)].sum + trie[s1(p)].cnt * now) >> d) + fd(x, s0(p), d + 1);
	return ((trie[s0(p)].sum + trie[s0(p)].cnt * now) >> d) + fd(x, s1(p), d + 1);
}
void update(ll x, ll p, ll d) {
	if (d > 30) return;
	if (d > 1) trie[p].sum += x, trie[p].cnt ++;
	if (x & (1 << d)) update(x, s1(p), d + 1);
	else update(x, s0(p), d + 1);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (ll i = 1; i <= n; i ++ ) cin >> a[i];
	sort(a + 1, a + n + 1, cmp);
	for (ll i = 1, sum1 = 0, cnt1 = 0, sum2 = 0, cnt2 = 0; i <= n; i ++ ) {
		ans += (sum1 + cnt1 * a[i]) / lowbit(a[i]);
		cnt2 ++, sum2 += a[i]; 
		now = a[i] / lowbit(a[i]);
		update(now, r, 1);
		ans += fd(now, r, 1);
		if (lowbit(a[i]) != lowbit(a[i + 1])) cnt1 += cnt2, sum1 += sum2, cnt2 = 0, sum2 = 0, r = ++ idx;
	}
	cout << ans;
}
```

---

## 作者：light_searcher (赞：3)

设 $b_k =\sum \limits _{i=1}^{n} \sum \limits _{j=i}^{n}(A_i + A_j)[2^k\mid (A_i+A_j)]$，则答案为 $\sum \limits \frac{b_k-b_{k+1}}{2^k}$。

那么接下来我们考虑如何将 $b$ 求出来。

由 $2^k \mid (A_i+A_j)$，我们可以得出 $A_j \equiv -A_i \pmod {2^k}$，我们可以在枚举 $j$ 的同时维护满足要求的 $i$ 的个数与 $A_i$ 的总和，分别记为 $cnt_j$ 和 $sum_j$，则 $b_k = \sum \limits _{j=1}^n cnt_j \times A_j + sum_j$。

代码中的 $cnt,sum$ 与上文中的略有差别，实际上是两个桶。时间复杂度是 $ \mathcal O((n+V) \log V)$，然后虽然跑得挺慢但反正能过：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,M=3.5e7+5;
int n,a[N],b[N],ans,cnt[M],sum[M];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=0;i<=25;i++){
		memset(cnt,0,sizeof(cnt));
		memset(sum,0,sizeof(cnt));
		int m=1<<i;
		for(int j=1;j<=n;j++){
			cnt[(-a[j]%m+m)%m]++;
			sum[(-a[j]%m+m)%m]+=a[j];
			b[i]+=cnt[a[j]%m]*a[j]+sum[a[j]%m];
		}
	}
	for(int i=0;i<=25;i++) ans+=(b[i]-b[i+1])>>i;
	printf("%lld",ans);
	return 0;
}

---

## 作者：HasNoName (赞：1)

### 思路

注意到时限 4s 这件事。

可能的复杂度应该是跟阈值相关的。

先到按二进制分类。

对于每一个数，如果不考虑除以二，则答案为 $\sum_{i=1}^N A_i\times N$。

考虑减去多余部分。

对于一个 $2^{k}$，可以减去的数的总和可以按余数分类。

对于余数为 $0$ 或 $2^{k-1}$ 的数单独考虑。

其他的可以按如下方法计算。

设有两个数组 $a$ 和 $b$，长度分别为 $n$ 和 $m$。

则造成的贡献为 $\sum_{i=1}^n \frac {a_i\times m+\sum_{i=1}^m b_i}{2^k}=\frac m{2^k}\times\sum_{i=1}^n a_i+\frac n{2^k}\times\sum_{i=1}^m b_i$

记录每个余数出现的次数和数字总和即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005,V=(2e7)+5;
ll a[N],v[V],cnt[V];//总和和个数
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i]*(n-1);
		ll t=a[i];
		while(!(t&1))t>>=1;//先记算a[i]+a[i]的情况
		sum+=t;
	}
	ll last=sum;
	for(int i=2;i<V;i*=2)//对于每一个二进制位2^k，O(VlogV)
	{
		memset(v,0,sizeof(v));
		memset(cnt,0,sizeof(cnt));
		for(int j=1;j<=n;j++)
		{
			if(a[j]%i==0||a[j]%i==i/2)
				sum-=(v[a[j]%i]+cnt[a[j]%i]*a[j])/i;
			v[a[j]%i]+=a[j];
			cnt[a[j]%i]++;
		}
		for(int j=1;j<i/2;j++)
			sum-=(cnt[i-j]*v[j]+cnt[j]*v[i-j])/i;
		if(sum==last)break;
		last=sum;
	}
	cout<<sum<<'\n';
	return 0;
}
```

---

## 作者：cyq32ent (赞：1)

设 $K(i,j)$ 为满足 $2^k|(A_i+A_j)$ 的最大的 $k$，题目要求的就是

$$\sum_{i=1}^N\sum_{j=i}^{N}\frac{A_i+A_j}{2^{K(i,j)}}=\sum_{i=1}^N\sum_{j=i}^{N}(A_i+A_j)(1-\sum_{l=1}^{K(i,j)}\frac{1}{2^l})$$

上式等于

$$(N+1)(\sum_{i=1}^Na_i)-(\sum_{i=1}^N\sum_{j=i}^{N}(A_i+A_j)\sum_{l=1}^{K(i,j)}\frac{1}{2^l}))$$

按 $l$ 求和，得到

$$(N+1)(\sum_{i=1}^Na_i)-\sum_{l=1}^\infin\sum_{i=1}^N\sum_{j=1}^i[2^l|(A_i+A_j)]\frac{A_i+A_j}{2^l}$$

其中，$[P]$ 为 $\left\{\begin{matrix}
 1 &\text{ if } P\\
 0 &\text{ if } \neg P
\end{matrix}\right.$。计算含 $j$ 的和式时，只需要在模 $2^l$ 意义下动态维护一个映射表，将 $-A_j$ 映射至映射到此处的 $A_j$ 的和及映射到此处的 $A_j$ 的数量即可。时间复杂度 $\mathcal O(n\log \max A_i)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200101],n;map<int,pair<int,int>>M;
signed main(){
	cin>>n;for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=1;i<=n;i++)ans+=(n+1)*a[i];
	for(int i=1;i<=25;i++){
		int mod=(1<<i);M.clear();
		for(int j=1;j<=n;j++){
			int x=-a[j];x%=mod;x+=mod;x%=mod;
			M[x].first+=a[j];M[x].second++;
			ans-=(a[j]*M[a[j]%mod].second+M[a[j]%mod].first)/(1<<i);
		}
	}cout<<ans<<endl;
	return 0;
}
```

---

