# Complex Market Analysis

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609C/18b254da391d541c237ec2ae3c537650bfbdb064.png)While performing complex market analysis William encountered the following problem:

For a given array $ a $ of size $ n $ and a natural number $ e $ , calculate the number of pairs of natural numbers $ (i, k) $ which satisfy the following conditions:

- $ 1 \le i, k $
- $ i + e \cdot k \le n $ .
- Product $ a_i \cdot a_{i + e} \cdot a_{i + 2 \cdot e} \cdot \ldots \cdot a_{i + k \cdot e}  $ is a prime number.

A prime number (or a prime) is a natural number greater than 1 that is not a product of two smaller natural numbers.

## 说明/提示

In the first example test case two pairs satisfy the conditions:

1. $ i = 2, k = 1 $ , for which the product is: $ a_{2} \cdot a_{5} = 2 $ which is a prime number.
2. $ i = 3, k = 1 $ , for which the product is: $ a_{3} \cdot a_{6} = 19 $ which is a prime number.

In the second example test case there are no pairs that satisfy the conditions.

In the third example test case four pairs satisfy the conditions:

1. $ i = 1, k = 1 $ , for which the product is: $ a_{1} \cdot a_{4} = 2 $ which is a prime number.
2. $ i = 1, k = 2 $ , for which the product is: $ a_{1} \cdot a_{4} \cdot a_{7} = 2 $ which is a prime number.
3. $ i = 3, k = 1 $ , for which the product is: $ a_{3} \cdot a_{6} = 2 $ which is a prime number.
4. $ i = 6, k = 1 $ , for which the product is: $ a_{6} \cdot a_{9} = 2 $ which is a prime number.

In the fourth example test case there are no pairs that satisfy the conditions.

In the fifth example test case five pairs satisfy the conditions:

1. $ i = 1, k = 1 $ , for which the product is: $ a_{1} \cdot a_{2} = 2 $ which is a prime number.
2. $ i = 1, k = 2 $ , for which the product is: $ a_{1} \cdot a_{2} \cdot a_{3} = 2 $ which is a prime number.
3. $ i = 1, k = 3 $ , for which the product is: $ a_{1} \cdot a_{2} \cdot a_{3} \cdot a_{4} = 2 $ which is a prime number.
4. $ i = 2, k = 1 $ , for which the product is: $ a_{2} \cdot a_{3} = 2 $ which is a prime number.
5. $ i = 2, k = 2 $ , for which the product is: $ a_{2} \cdot a_{3} \cdot a_{4} = 2 $ which is a prime number.

In the sixth example test case there are no pairs that satisfy the conditions.

## 样例 #1

### 输入

```
6
7 3
10 2 1 3 1 19 3
3 2
1 13 1
9 3
2 4 2 1 1 1 1 4 2
3 1
1 1 1
4 1
1 2 1 1
2 2
1 2```

### 输出

```
2
0
4
0
5
0```

# 题解

## 作者：智子 (赞：2)

## 题意

给定长为 $n$ 的正整数序列 $a$ 和一个正整数 $e$，求满足以下规定的有序数对 $(i,k)$ 的数量：

- $i,k\ge 1$
- $i+e\times k\le n$
- $\prod\limits_{j=0}^ka_{i+e\times j}$ 是质数


## 思路

因为第三条规则要求这一串数的乘积必须是质数，所以这些必须是中间一个质数，左右两边都是 $1$。

所以我们可以直接枚举每一个质数，如果这个质数左边每隔 $e$ 个数有 $a$ 个 $1$，右边每隔 $e$ 个数有 $b$ 个 $1$，那么左边就有 $a + 1$ 种选法，右边有 $b + 1$ 种选法，根据乘法原理，这个质数对答案的贡献为 $(a + 1)(b + 1) - 1$。（$-1$ 是因为如果两边都是 $0$，序列的长度就是 $1$，不符合题意。）

一个数是不是质数可以直接线性筛，一个数每次往左跳 $e$ 个位置有多少个 $1$、每次往右跳 $e$ 个位置有多少个 $1$ 都可以预先处理出来，总时间复杂度 $O(n + w)$， $w$ 表示值域大小。

## 代码

```cpp
#include<cstdio>
using namespace std;

const int MAXN = 1000000 + 5;

bool vis[MAXN];
int a[MAXN], pri[MAXN], pre[MAXN], suf[MAXN];
int n, e;
int tot;

void init(int n = MAXN - 1) {
    vis[1] = true;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            pri[++tot] = i;
        }
        for(int j = 1; j <= tot && i * pri[j] <= n; j++) {
            vis[i * pri[j]] = true;
            if(i % pri[j] == 0) {
                break;
            }
        }
    }
}

int main() {
    int T;

    init();
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &e);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 1; i <= n; i++) {
            if(i > e && a[i - e] == 1) {
                pre[i] = pre[i - e] + 1;
            } else {
                pre[i] = 0;
            }
        }
        for(int i = n; i >= 1; i--) {
            if(i + e <= n && a[i + e] == 1) {
                suf[i] = suf[i + e] + 1;
            } else {
                suf[i] = 0;
            }
        }
        long long ans = 0;
        for(int i = 1; i <= n; i++) {
            if(!vis[a[i]]) {
                ans += (long long)(pre[i] + 1) * (suf[i] + 1) - 1;
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}

```

---

## 作者：XL4453 (赞：1)

### 解题思路：

首先发现，其实每一组之间是互不干扰的，所以先考虑分组然后做。

那么问题就可以转化为在一个序列中选择一个长度不少于 $2$ 的子串并要求乘积为质数。

这样问题就显然了，如果有两个或者以上非 $1$ 的数或者一个合数在这个序列中就一定不可以。考虑先求出所有的范围内的质数，然后从质数开始向两边拓展，一旦碰到非 $1$ 的数就退出。

若设向左的长度为 $cnt_1$ 向右的为 $cnt_2$，则不考虑长度至少为 $1$ 的限制就有 $(cnt_1+1)\times (cnt_2+1)$ 种，减去一个恰好为一的，就是：$cnt_1\times cnt_2+cnt_1+cnt_2$ 种方案。

由于算法从每一个质数开始拓展，然后一旦遇到非 $1$ 的就退出，那么，每一个 $1$ 最多被左边的和右边的第一个质数遍历到一次，所以总复杂度是 $O(n)$ 的。


---
### 代码：
```cpp
#include<cstdio>
using namespace std;
#define int long long
int T,n,k,e,a[200005],num[200005],cnt,ans,c[1000006],pri[1000006],tot;
void work(){
	for(int i=1;i<=cnt;i++){
		if(c[num[i]]==0){
			int cnt1=0,cnt2=0;
			for(int j=i-1;j>=1;j--){	
				if(num[j]==1)cnt1++;
				else break;
			}
			for(int j=i+1;j<=cnt;j++){
				if(num[j]==1)cnt2++;
				else break;
			}
			ans+=cnt1*cnt2+cnt1+cnt2;
		}
	}
}
signed main(){
	scanf("%I64d",&T);
	c[1]=1;
	for(int i=2;i<=1000000;i++){
		if(c[i]==0)pri[++tot]=i;
		for(int j=1;j<=tot;j++){
			if(i*pri[j]>1000000)break;
			c[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	while(T--){
		ans=0;
		scanf("%I64d%I64d",&n,&e);
		for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
		for(int i=1;i<=e;i++){
			cnt=0;
			for(int j=i;j<=n;j+=e)num[++cnt]=a[j];
			num[cnt+1]=0;
			work();
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
```


---

## 作者：czh___ (赞：0)

思路：

若干个数相乘为质数，那么只有一个数为质数，其余数都为 $1$。

所以：

对于 $a_i$ 为质数，就需要计算后面连续的 $a_{i+km}$ 为 $1$ 的个数。
对于 $a_i$ 为 $1$，那么需要找到后面连续的 $a_{i+km}$ 的个数，保证 $a_{i+km}$ 中只有一个质数。
那么
如果 $a_i$ 为质数，那么其后面的满足的连续的 $1$ 可以作贡献，同时前面连续的 $1$ 也可以作贡献。
假设该质数位置前面连续的 $1$ 为 $cnt1$ 个，后面连续的 $1$ 为 $cnt2$ 个，那么通过这个质数得到的数对个数就为 $cnt2 + cnt1 \times (cnt2 + 1)$。

代码：

```cpp
#include<bits/stdc++.h>
#define Ios ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
const int N = 1000020, mod = 1e9+7;
int T,n,m,f[N],a[N],prim[N];
void init(){
	f[0] = f[1] = 1;
	n=1e6+1;
	for(int i=2;i<=n;i++)
		if(f[i]) 
			continue;
		else
			for(int j=i+i;j<=n;j+=i) 
				f[j]=1;
}
signed main(){
	Ios;
	init();
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		int ans=0;
		for(int i=1;i<=n;i++){
			int cnt1=0, cnt2=0;
			if(!f[a[i]]){
				for(int j=i+m;j<=n;j+=m)
					if(a[j]==1) cnt2++;
					else break;
				for(int j=i-m;j>=1;j-=m)
					if(a[j]==1) cnt1++;
					else break;
			}
			ans+=cnt2+cnt1*(cnt2+1);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```
[改编于](https://blog.csdn.net/Mr_dimple/article/details/122338612?ops_request_misc=&request_id=&biz_id=102&utm_term=Complex%20Market%20Analysis&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-5-122338612.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

## 作者：QWQ_123 (赞：0)

由于 $\Pi_{j=0}^{k} a_{i+e\times j}$ 要是质数，也就是说，在 $a_{i + e \times j}$ 中**恰好**有一个非零数，且是质数。  
所以考虑先预处理出质数，然后对于每组询问，预处理出：$ne_i$ 表示 $1$ 的下一个非 $1$ 的数字是第几个，然后 $ne1_i$ 表示非 $1$ 的后面有多少个间隔为 $e$ 的 $1$。  
那么对于每个 $i$。
*	若 $a_i \not = 1$，也就是说，只要他是质数，那么总方案数就可以加上 $ne_i$（由于 $k \ge 1$，所以不能选它本身），否则不变。
*	若 $a_i = 1$，那么就是跳到第一个不是 $1$ 的位置，然后按照 $a_i \not=1$ 来做即可。但是：这里是先从 $1$ 跳过去的，长度至少为 $1$，所以方案应增加 $ne_i+1$。

还有，开 `long long`。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int T;
int n, e;
int ne[200010], ne1[200010], a[200010];
bool st[1000010];

void prime() {
	st[0] = st[1] = true;
	for (int i = 2; i <= 1000000; ++i) {
		if (!st[i]) {
			for (int j = 2; i * j <= 1000000; ++j)
				st[i * j] = true;
		}
	}
}

signed main() {
	prime();
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld%lld", &n, &e);
		for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
		for (int i = n; i >= 1; --i) {
			if (a[i] != 1) ne[i] = i;
			else {
				if (i + e > n) ne[i] = n + 1;
				else ne[i] = ne[i + e];
			}
		}

		for (int i = n; i >= 1; --i) {
			if (i + e > n) ne1[i] = 0;
			else if (a[i + e] == 1) ne1[i] = ne1[i + e] + 1;
			else ne1[i] = 0;
		}

		int ans = 0;

		for (int i = 1; i <= n; ++i) {
			if (a[i] != 1) {
				ans += (1 - st[a[i]]) * ne1[i];
				// cout << ne1[i] << ' ' << i << ' ' << a[i] << ' ' << st[a[i]] << ' ' << ans << endl;
			} else {
				if (ne[i] > n) continue;
				ans += (1 - st[a[ne[i]]]) * (ne1[ne[i]] + 1);
				// cout << i << ' ' << ne[i] << ' ' << a[ne[i]] << ' ' << ne1[ne[i]] << endl;
			}
		}

		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：LinkZelda (赞：0)

- **做法**：

好像大家的解法都很方便。

看到这种东西，我会奇奇怪怪地想到根号算法。

考虑对 $e$ 的大小分类讨论，首先是 $e\geq \sqrt{n}$。

对于这种情况，我们发现对于每个位置 $i$，$k$ 的取值只有至多 $\sqrt{n}$ 种，于是我们可以直接暴力枚举这个 $k$ 直到中间出现过大于一个质因数为止，统计其中刚好只有一个质因数的 $k$。

然后考虑 $e< \sqrt{n}$ 的情况。

考虑把每个 $i$ 对 $e$ 取模之后，大小都是小于 $\sqrt n$ 的。那么我们枚举每个余数 $d\in [0,e-1]$，然后枚举这个 $k$，考虑每个对于这个 $d$ 的每个位置 $i=k\cdot e+d$ ，发现我们能选的数的左右端点一定满足：中间跨过的数的乘积只有一个质因子。那么我们只需要扫描一下这些数算贡献即可（具体可以看看代码）。

线性筛预处理质数。

时间复杂度为 $O(n\sqrt n+10^6)$。

[代码](https://www.luogu.com.cn/paste/dzccy2sp)

---

