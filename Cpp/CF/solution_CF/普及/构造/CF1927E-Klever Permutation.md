# Klever Permutation

## 题目描述

You are given two integers $ n $ and $ k $ ( $ k \le n $ ), where $ k $ is even.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation (as $ 2 $ appears twice in the array) and $ [0,1,2] $ is also not a permutation (as $ n=3 $ , but $ 3 $ is not present in the array).

Your task is to construct a  $ k $ -level permutation of length $ n $ .

A permutation is called  $ k $ -level if, among all the sums of continuous segments of length $ k $ (of which there are exactly $ n - k + 1 $ ), any two sums differ by no more than $ 1 $ .

More formally, to determine if the permutation $ p $ is  $ k $ -level, first construct an array $ s $ of length $ n - k + 1 $ , where $ s_i=\sum_{j=i}^{i+k-1} p_j $ , i.e., the $ i $ -th element is equal to the sum of $ p_i, p_{i+1}, \dots, p_{i+k-1} $ .

A permutation is called  $ k $ -level if $ \max(s) - \min(s) \le 1 $ .

Find any  $ k $ -level permutation of length $ n $ .

## 说明/提示

In the second test case of the example:

- $ p_1 + p_2 = 3 + 1 = 4 $ ;
- $ p_2 + p_3 = 1 + 2 = 3 $ .

 The maximum among the sums is $ 4 $ , and the minimum is $ 3 $ .

## 样例 #1

### 输入

```
5
2 2
3 2
10 4
13 4
7 4```

### 输出

```
2 1
1 3 2
1 8 4 10 2 7 5 9 3 6
4 10 1 13 5 9 2 12 6 8 3 11 7
1 6 3 7 2 5 4```

# 题解

## 作者：2huk (赞：10)

## 题意

给定两个整数 $n, k$，其中 $k$ 是偶数。

你需要构造一个 $1 \sim n$ 的排列 $p$，使得：

$$
\max_{j = 1}^{n - k + 1} \left\{ \sum_{l = j}^{j + k - 1} p_l \right\} - \min_{j = 1}^{n - k + 1}\left\{ \sum_{l = j}^{j + k - 1} p_l \right\}\le 1
$$

多测。$t \le 10^4$，$2 \le k \le n \le 2 \times 10^5$，$k$ 为偶数，$\sum n \le 2 \times 10^5$。

## 分析

首先观察在 $j = x$ 和 $j = x + 1$ 时，$\sigma_j = \sum_{l = j}^{j + k - 1} p_l$ 有什么关系：

当 $j = x$ 时：

$$
\sigma_q = \sum_{l = q}^{q + k - 1} p_l = p_q + \sum_{l = q + 1}^{q + k - 1} p_l
$$

当 $j = x + 1$ 时：
$$
\sigma_{q + 1} = \sum_{l = q + 1}^{q + k} p_l = p_{q+k} + \sum_{l = q + 1}^{q + k - 1} p_l
$$

那么有：

$$
\sigma_q - \sigma_{q + 1} = \left(p_q + \sum_{l = q + 1}^{q + k - 1} p_l \right) - \left(p_{q+k} + \sum_{l = q + 1}^{q + k - 1} p_l\right) = p_q - p_{q + k}
$$

而因为 $p$ 是排列，所以一定有 $p_x \ne p_{x + k}$。在最好情况下 $|p_x - p_{x + k}| = 1$。

而为了满足题目中最大值减最小值小于等于 $1$，所以我们应该让所有的 $|p_x - p_{x + k}| = 1$。

例如，在 $n = 9, k = 4$ 时，我们应该这样填：

![](https://cdn.luogu.com.cn/upload/image_hosting/i3m6ilxe.png)

然后你会发现这样是不对的。因为我们一直让 $p_x - p_{x + k} = 1$，而没有让 $p_x - p_{x + k} = -1$。

方法就是把上面 $4,5$ 和 $8,9$ 顺序换过来。即：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ld55mtl.png)

即在第偶数个过程中将填的数翻转。

```cpp
int a[N];
 
void solve() {
	int n = read(), k = read();
	int cnt = 0;
	bool flg = false;		// 是否要翻转
	int st = 1;
	while (cnt != n) {
		while (a[st]) ++ st;
		int now = st;
		vector<int> pos;
		while (now <= n) {
			pos.push_back(now);
			now += k;
		}
		if (flg) reverse(pos.begin(), pos.end());
		for (int &t : pos) a[t] = ++ cnt;
		flg ^= 1;
	}
	wel(a + 1, a + n + 1);
	fup (i, 1, n) a[i] = 0;
	return;
}
```



---

## 作者：Mr_Vatican (赞：3)

## 思路
首先，口胡一下可以发现每一对**相邻的模 $k$ 同余的**位置的值的差不超过 $1$。然后就写了个每次跳着填数的代码，样例都过不去。
```cpp
for(int i=1;i<=k;i++) for(int j=i;j<=n;j+=k) a[j]=++now;
```
发现这样只能保证两个相邻的段的差不超过 $1$，不能保证所有的段都满足。

只能尝试调整构造方法：对于模 $k$ 余奇数的位置，正着填过去；对于模 $k$ 余偶数的位置，反着填。

容易证明这是对的（但是如果是考场的话主要靠口胡）。
```cpp
void solve()
{
    scanf("%d%d",&n,&k);
    int now=0;
    for(int i=1;i<=k;i++)
    {
        int tmp=n/k*k+i;if(tmp>n) tmp-=k;//这个是从后往前第一个模 k 余 i 的位置
        if(i&1) for(int j=i;j<=n;j+=k) a[j]=++now;
        else for(int j=tmp;j>0;j-=k) a[j]=++now;
    }
    for(int i=1;i<=n;i++) cout << a[i] << " \n"[i==n];
}
```
点个赞再走吧。

---

## 作者：__Dist__ (赞：3)

搬个样例过来：

```
n = 10, k = 4
ans = {1,8,4,10,2,7,5,9,3,6}
```

先看第 $1$ 段长度为 $k$ 的区间 $ans_1 \sim ans_4$ 和第 $2$ 段长度为 $k$ 的区间 $ans_2 \sim ans_5$。两段区间的差其实就是 $ans_5 - ans_1 = 1$。

先看第 $2$ 段长度为 $k$ 的区间 $ans_2 \sim ans_5$ 和第 $3$ 段长度为 $k$ 的区间 $ans_3 \sim ans_6$。两段区间的差其实就是 $ans_6 - ans_2 = -1$。

以此类推，最后 $+1-1+1-1+\cdots$，极差就 $\le 1$ 啦。

所以，遍历 $1 \sim n$，每隔 $k$ 个输出一次，先递增输，后递减输。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int T;
int n, k;
int ans[MAXN];

void solve() {
	int cnt = 0;
	cin >> n >> k;
	for (int i = 1; i <= k; i++) {
		if(i & 1) {
			int j = i;
			while(j <= n) {
				ans[j] = ++cnt;
				j += k;
			}
		}
		else {
			int j = i;
			int x = cnt;
			while(j <= n) {
				x++;
				j += k;
			}
			int xx = x;
			j = i;
			while(j <= n) {
				ans[j] = x--;
				j += k;
			}
			cnt += xx;
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " \n"[i == n];
	}
}

int main() {
	cin >> T;
	while(T--) solve();
	return 0;
}
```



---

## 作者：No_Rest (赞：0)

## 思路

注意到 $|s_i - s_{i + 1}| = |\sum^{i + k - 1}_{j = i} p_j - \sum^{i+k}_{j = i + 1} p_j| = |p_i - p_{i + k}|$。因为 $p$ 是一个排列，所以显然 $p_i \ne p_{i + k}$，那么为了使 $\max(s) - min(s) \le 1$，$|p_i - p_{i + k}|$ 只能为 $1$。

我们又可以发现，如果 $p_i - p_{i + k} = p_{i + 1} - p_{i + k + 1} = 1$ 或  $p_i - p_{i + k} = p_{i + 1} - p_{i + k + 1} = -1$，那么 $s_i = s_{i + 1} + 1 = s_{i + 2} + 2$ 或 $s_i = s_{i + 1} - 1 = s_{i + 2} - 2$，不符题意。

所以 $p_i - p_{i+k}$ 要交替为 $1,-1,1,-1,\dots$

一种简单的构造是：当 $i$ 是奇数时，$p_i = i, p_{i + k} = i + 1, p_{i + 2k} = i + 2\dots$；当 $i$ 是偶数时，$p_i = i, p_{i + k} = i - 1, p_{i + 2k} = i - 2\dots$。

之后的模拟构造就比较简单了，要注意细节。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 2e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll t = read(), n, k, a[maxn], cnt, now;
void solve(){
	n = read(), k = read(), cnt = 0, now = 1;
	for(ll i = 1; i <= n; ++i) a[i] = 0;
	for(ll i = 1; i <= k; ++i){
		if(i & 1){
			now = i;
			while(now <= n) a[now] = ++cnt, now += k;
		} else {
			now = n / k * k + i;
			if(now > n) now -= k;
			while(now > 0) a[now] = ++cnt, now -= k;
		}
	}
	for(ll i = 1; i <= n; ++i) printf("%lld ", a[i]);
	putchar('\n');
}
int main(){
	for(; t; --t) solve();
    return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# solution
题意已经非常清楚了，应该不用解释。

---

首先对于两个相邻的序列 $[l,l+k-1]$ 和 $[l+1,l+k]$。

发现 $|(a_l+a_{l+1}+\cdots+a_{l+k-1})-(a_{l+1}+a_{l+2}+\cdots +a_{l+k})|\le 1$。

即 $|a_l-a_{l+k}|\le 1$。

那么每两个间隔 $k$ 个的数都要相差 $1$。

这是一个很强的条件，考虑直接构造。

即对于每一个关于 $k$ 的余数都顺序填入。

$e.g.$ 对于 $n=8,k=4$，是 $1,5,1+1,5+1,1+2,5+2,1+3,5+3$，就是 $1,5,2,6,3,7,4,8$。

在代码上就是：
```cpp
for(int j=1;j<k;j++)
	for(int i=j;i<=n;i+=k)
    		a[i]=++cnt;
```

但是这样答案打出来会十分丑陋，发现虽然两两相差 $1$，但是全局不是。

所以我们可以让两个相邻序列的差为 $1,-1,1,-1,\dots$。

也就是直接填入，但是在偶数次填入时由大到小填入。

在代码上可以先跑一遍看一下有多少个能够填入，然后再从后往前填入。

在代码上就是：
```cpp
for(int j=1;j<=k;j++){
        if(j%2)
            for(int i=j;i<=n;i+=k)
                a[i]=++cnt;
        else{
            int rcnt=cnt;
            for(int i=j;i<=n;i+=k)rcnt++;
            int now=rcnt;
            for(int i=j;i<=n;i+=k)a[i]=rcnt--;
            cnt=now;
        }
    }
```

注意：每一次需要将 $cnt$ 清零。

---

## 作者：apiad (赞：0)

你要构造 $n$ 个数，其中任意一个长度为 $k$ 的子段和为 $S$，$\max(S) - \min(S) \le 1$。我们可以让每一段，一个小的，一个大的，然后交替着接着，每相邻的就相差 $1$。

考虑如何构造。

由于 $k$ 是偶数，所以可以分奇偶来构造。

例如：$n = 9,k = 4$。


```
1 9 * * 2 8 * *
```

这是前面的一部分。如果此时的区间是 $(1,4)$ 那么其和为 $1+9$ 再加两个星号，然后滑动窗口到了 $(2,5)$，此时的变化是 $-1+2$，也就是 $+1$。然后再往后是 $-9+8$，就是 $-1$。一个 $+1$，一个 $-1$。正好符合题意，于是直接模拟即可。

我们枚举 $i$ 是在 $k$ 的区间内，处理每一段中的第 $i$ 个，若 $i$ 是奇数，直接用一个变量一直累加并填写即可，如果是偶数，那么一个变量递减并填写。

[code](https://codeforces.com/contest/1927/submission/245292928)。

---

## 作者：SamHJD (赞：0)

## Klever Permutation

### Description

构造一个长为 $n$ 的序列，使**连续 $k$ 个数的和**的最大值与最小值相差 $1$。保证 $k$ 为偶数。

### Solution

转化题意，设 $f_i=a_i-a_{i+k}$，我们需使 $|f_i|=1$，并且 $f_i+f_{i+1}=0$。

因为 $k$ 是偶数，所以 $f_i=f_i+k$，因此 $a_i,a_{i+k},a_{i+2\times k}\dots$ 为等差数列，公差为 $f_i$。

按此构造即可，设一个左指针和右指针，初始为 $1,n$。公差为 $1$ 则选左指针，否则选右指针。

### [code](https://codeforces.com/contest/1927/submission/245175922)

---

## 作者：Dream_poetry (赞：0)

### 题意：

构造一个长度为 $n$ 的序列，包含 $1$ 到 $n$ 的所有整数，使得该序列的长度为 $k$ 的子序列的最大值和最小值的差**不大于** $1$。

### 思路：

构造题，题意有点绕，但是思路和代码都比较好想。

先说结论：

+ 先在下标为 $1$ 处向后摆数，从 $1$ 开始，正着**从小到大**摆，隔 $k$ 个摆一个。计最后一个为 $x_1$。

+ 然后在下标为 $2$ 处从 $n$ 开始，**从大到小**摆，也是隔 $k$ 个摆一个。计最后一个为 $y_1$。

+ 继续在下标为 $3$ 处接着摆，从 $x_1+1$ 开始，**从小到大**摆，依旧隔 $k$ 个摆一个。计最后一个为 $x_2$。

以此类推。

**证明：**

令任意两个相邻的子序列为 $l_1,r_1$ 和 $l_1+1,r_1+1$，它们的差值就是 $a_{r_1+1}-a_{l_1}$，而为了使差值不超过 $1$ ，每个元素又只能用一次，所以得出结论 $a_{r_1+1}$ 和 $a_l$ 是两个相邻的数。

再类推一下，得出了隔 $k$ 个数接着放下一个数的结论。

假如全部递增放或者全部递减放，最大值和最小值就不可能差值为 $1$，所以就要一次正着放，一次反着放。

至于为什么分别从 $1$ 和 $n$ 开始放，相信大家都知道，这里就不证明了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
int n,k;
int a[500005];
int st,en;
 
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		st=0;
		en=n;
		for (int i=1;i<=k;i++){
			for (int j=i;j<=n;j+=k){
				if (i%2==1){
					a[j]=++st;
				}
				else{
					a[j]=en--;
				}		
			}
		}
		for (int i=1;i<=n;i++){
			cout<<a[i]<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：0)

一眼了。

------------

显然对于一个长度为 $k$ 的序列，接下来一个数一定是序列第一个数加一或减一才能让两个序列和的差为 $1$。

同时对于所有连续 $k$ 个数，最后一个数与上个序列第一个数的关系一定是加减交替，否则差大于 $1$。

那么我们先构造出第一个序列，让后面新加入的数恰好填满两个数之间的空隙即可。

由于题目保证 $k$ 是偶数，每个数一定是一直加或一直减且加减交替。

每个数加减的个数是整个序列中包含 $k$ 的个数，注意可能有余数。

------------

构造结论描述得不大好，可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+26;
int T,n,k,a[maxn];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        for(int i=1,now=1;i<=k;i+=2,now++){
            a[i]=now;
            now+=n/k*2+(i<=n%k)+(i<n%k)-1;
            a[i+1]=now;
        }
        for(int i=1;i<=n;i++)
            printf("%d ",a[(i-1)%k+1]+((i&1)?(i-1)/k:-(i-1)/k));
        puts("");
    }
    return 0;
}
```


---

## 作者：strcmp (赞：0)

**题目大意：**

给定 $n,\,k$。求长度为 $n$ 的，满足所有长度为 $k$ 的区间各自的和的 $\max - \min \le 1$ 的任意一个排列。

------------

在排列上滑动窗口，注意到因为我们是一个排列，每次末尾加入一个数，头部删除一个数，当前区间和必然会改变。再下次滑动窗口又会变回去。

所以我们滑动窗口的区间和，按顺序排列必然是类似 $\{s,\,s+1,\,s,\,s+1,\,\dots\}$ 或者 $\{s,\,s-1,\,s,\,s-1,\,\dots\}$.

不妨钦定 $1$ 位置是 $1$，考虑第一种区间和的形式。

那么显然 $k + 1$ 位置应当比 $1$ 位置大 $1$，这样我们删除 $1$ 位置，加上 $k + 1$ 位置，新的区间和恰好比原来的大 $1$。所以 $k + 1$ 位置是 $2$。

$k + 2$ 位置应当比 $2$ 位置少 $1$，这样加入 $k + 2$ 位置，删除 $2$ 位置，恰好区间和比原来少 $1$。

以此类推，因为 $k$ 是偶数，所以 $(a + 1)k + b$ 位置应该比 $ak + b$ 位置多 $1$（$b$ 为奇数），或者少 $1$（$b$ 为偶数）。

这就得到我们的构造方法：枚举 $b$，若 $b$ 为奇数则所有 $ak + b$ 位置都是上一个位置加 $1$。否则 $ak + b$ 位置都是上一个位置减 $1$。

比如对于 $n = 8,\,k = 3$：

```
1 0 0 2 0 0 3 0
1 6 0 2 5 0 3 4
1 6 7 2 5 8 3 4
```

不难验证这个排列是符合要求的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
using pll = pair<ll, ll>;
const int maxn = 1e6 + 10;
const ll mod = 1e9 + 7;
const ll inf = 114514191981052013LL;
int T, n, k, a[maxn], b[maxn];
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k); int v = 1;
        for (int i = 1; i <= k; i++) {
            int p = i, d = 0;
            while (p <= n) a[p] = v, p += k, ++v;
            if (i % 2 == 0) {
                p = i;
                while (p <= n) b[++d] = a[p], p += k;
                reverse(b + 1, b + d + 1); d = 1; p = i;
                while (p <= n) a[p] = b[d], p += k, ++d;
            }
        }
        //1 3 6
        for (int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
    }
    return 0;
}
```

---

## 作者：atomic_int (赞：0)

把长度为 $k$ 的序列看作是一个窗口，从左往右每次移动一个格子。假设 $n=6,k=3$，窗口为 $[a_1,a_2,a_3],[a_2,a_3,a_4],[a_3,a_4,a_5],[a_4,a_5,a_6]$，发现每次都是删掉窗口末尾元素，然后加入后面的元素。我们需要保证这两个元素相差 $1$ 或 $-1$。

可以构造 $[1,2\times k,\dots],[2,2 \times k-1,\dots],\dots,[k,k+1,\dots]$，这样区间和总是 $+1,-1,\cdots$ 不断重复，相差不会超过 $1$。这里是将序列按照 $k$ 个为一块划分的，如果序列长度不是 $k$ 的倍数，当最后一块（长度 $<k$） 满的时候，继续填前面的块即可。细节请参考代码。

```cpp
void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> ans(n + 1);
  int x = 1;
  for (int i = 1; i <= k; i++) {
    if (i % 2 == 1) {
      for (int j = 0; j <= n / k + 1; j++) {
        if (i + j * k > n) break;
        ans[i + j * k] = x;
        x++;
      }
    } else {
      for (int j = n / k + 1; j >= 0; j--) {
        if (i + j * k > n) continue;
        ans[i + j * k] = x;
        x++;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
}
```

---

## 作者：Wei_Han (赞：0)

## 题目大意
有 $t$ 组数据，每组构造长度为 $n$ 的排列，使得所有长度为 $k$ 的区间和的最大值与最小值的差不超过 $1$，$k$ 为偶数。
## Solution
从两个 $k-1$ 个数相交的区间开始考虑，假设排列为 $a$，那么会有 $a_i=a_{i+k}\pm 1$（中间和相等）。该条件对任意 $a_i$ 都成立，此时所有 $a_{i+p\times k}$ 就成了单调递增或者递减的序列。

为了使得每个区间之间和差值不超过 $1$，构造使得奇数位置单调递增，偶数位置单调递减就好了。

实现时按照长度为 $k$ 的区间构造，记录每个位置能取到的界值，当 $i$ 为奇数时，$a_i$ 取到 $i\times k$，当为偶数时，$a_i$ 取到 $(i-1)\times k+1$ 之后按照递增递减构造后面的区间即可，对于最后不满一个区间的位置，在预处理界值时加上即可。
## Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
using namespace std;
typedef int ll;
typedef double db;
const int N=2e5+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,k,a[N],b[N];
int main(){
	read(t);
	while(t--){ 
		read(n),read(k);
		ll op=n%k,sum=n/k,nw=0;
		fo(1,i,k){
			if(i&1) b[i]=sum*i+nw;
			else b[i]=sum*(i-1)+1+nw;
			if(i<=op&&(i&1)) b[i]++;
			if(i<=op) nw++;
		}
		fo(1,i,sum) fo(1,j,k){
			if(j&1) wr(b[j]),pp,b[j]--;
			else wr(b[j]),pp,b[j]++;
		}
		fo(1,i,op) wr(b[i]),pp;pr;
	}
	return 0;
}
``````


---

## 作者：aeiouaoeiu (赞：0)

首先发现从 $[i,i+k-1]$ 变成 $[i+1,i+k]$ 时，和 $s\leftarrow s-p_i+p_{i+k}$，这要求 $p_{i+k}-p_i$ 形如 $[-1,1,-1,1,\ldots]$。

建图方便理解。连边 $(i,i+k)$，边权为 $(-1)^{i\bmod 2}$（$k$ 为偶数，保证了赋边权的正确性），这样形成了数条边权均为 $1$ 的链和数条边权均为 $-1$ 的链。

考虑贪心地给点赋值。对于边权均为 $1$ 的链，从 $1$ 开始赋值；对于边权为 $-1$ 的链，从 $n$ 开始赋值。

赋值后 $p_i$ 的值即为点 $i$ 所赋的值。[Link](https://codeforces.com/contest/1927/submission/245197761)（实现时不用真正建图）。

---

## 作者：Linge_Zzzz (赞：0)

# 题意简述

给你 $n,k$，要求构造一个 $n$ 的排列，使得长度为 $k$ 的子段的和中，最大值与最小值相差不超过 $1$， $k$ 是偶数。

数据范围：$\sum n \leq 2\times 10^5$。

# 解法

为了便于描述，设构造出来的序列为 $a$，记 $s_i=\sum_{j=i}^{i+k-1} a_i$。

注意到：$a_i$ 和 $a_{i+k}$ 一定相差 $1$。

这一点读者可以自己思考一下。简单来说，就是因为中间的 $[i+1,i+k-1]$ 不变，而排列中没有相同的数，所以必定差 $1$，也最多只能差 $1$。

有了这点，我们再来考虑如何构造序列。

假设 $k=4$，因为 $a_1$ 和 $a_5$ 一定相差 $1$，不妨设 $a_5=a_1+1$，再设 $s_1=x$，那么就有 $s_2=x+1$。

因为所有的 $s_i$ 最多相差 $1$，就必然有 $s_3=x$， $s_4=x+1$，$\cdots $

由此可得，$a_6=a_2-1$，$a_7=a_3+1$，$a_8=a_4-1$， $\cdots$

到这里，相信你们就发现规律了：

如果 $i \bmod 2 =1$，那么 $a_{i+k}=a_i+1$。

如果 $i \bmod 2 =0$，那么 $a_{i+k}=a_i-1$。

那我们就可以让 $a_1=1$，然后开始构造了，构造的时候注意边界的判断，具体见代码。

#代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=2e5+10,M=2e6+10;
int n,k;
int ans[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int cur=0;
		cin>>n>>k;
		int x=n%k; 
		int d=n/k;
		for(int i=1;i<=k;i++){
			if(i%2==1){
				for(int j=i;j<=n;j+=k){
					ans[j]=++cur;
				}
			}else{
				if(i<=x){
					for(int j=k*d+i;j>=1;j-=k){
						ans[j]=++cur;
					}
				}else{
					for(int j=k*d+i-k;j>=1;j-=k){
						ans[j]=++cur;
					}
				}
			}
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

为了构造一个置换，我们发现：

$s_i≠s_{i+1}$，由于数组只能包含两个不同的值，它只能是 $[x,x+1,x,x+1,...] ~\text{or} ~[x,x-1,x,x-1,...]$。

我们来构造第一种形式的排列。

由于 $s_1+1=s_2$，则 $a_1+1=a_{k+1}$。

由于 $s_2=s_3+1$，则 $a_2=a_{k+2}+1$。

由于 $s_3+1=s_4$，则 $a_3+1=a_{k+3}$。

...

由于 $s_{k}=s_{k+1}+1$，则 $a_k=a_{k+k}+1$。

...

所以对于所有奇数 $i$，$a_i+1=a_{i+k}$，对于所有偶数 $i$，$a_i=a_{i+k}+1$。

为了构造这样一个置换，我们遍历所有 $1\leq i\leq k$ 在 $i,i+k,i+2k,...$ 的位置上。

```python
def solve():
    n, k = map(int, input().split())
    l, r = 1, n
    ans = [0] * n
    for i in range(k):
        for j in range(i, n, k):
            if i % 2 == 0:
                ans[j] = l
                l += 1
            else:
                ans[j] = r
                r -= 1
    print(*ans)
    
    
for _ in range(int(input())):
    solve()
```


---

