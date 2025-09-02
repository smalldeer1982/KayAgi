# Charming Meals

## 题目描述

The Czech cuisine features $ n $ appetizers and $ n $ main dishes. The $ i $ -th appetizer has spiciness $ a_i $ , and the $ i $ -th main dish has spiciness $ b_i $ .

A typical Czech meal consists of exactly one appetizer and one main dish. You want to pair up the $ n $ appetizers and $ n $ main dishes into $ n $ meals with each appetizer and each main dish being included in exactly one meal.

Your meals shall surprise the diners, so you want the spiciness levels of the two parts of the same meal to be as different as possible. The charm of a meal is the difference (in absolute value) between the spiciness of the appetizer and the spiciness of the main dish. So, a meal consisting of an appetizer with spiciness $ x $ and a main dish with spiciness $ y $ has charm equal to $ |x-y| $ .

You want to maximize the minimum charm of the resulting $ n $ meals. What is the largest possible value of the minimum charm that you can achieve?

## 说明/提示

In the first test case, no matter how you pair up the appetizers with the main dishes, each meal will have an appetizer with spiciness $ 0 $ and a main dish with spiciness $ 1000000000 $ , so the charm of each meal will be $ 1000000000 $ .

In the second test case, one optimal way to pair up appetizers and main dishes is: $ (1, 5) $ , $ (2, 4) $ , $ (3, 1) $ , $ (4, 2) $ , $ (5, 3) $ . The corresponding meals have charms: $ 4 $ , $ 2 $ , $ 2 $ , $ 2 $ , $ 2 $ . The resulting minimum charm is $ 2 $ .

In the third test case, one way to maximize the minimum charm is to pair up the three appetizers with spiciness $ 0 $ with the three main dishes with spiciness $ 100 $ , and the three appetizers with spiciness $ 100 $ with the three main dishes with spiciness $ 0 $ . Doing so, the charm of each meal will be exactly $ 100 $ .

## 样例 #1

### 输入

```
4
3
0 0 0
1000000000 1000000000 1000000000
5
1 2 3 4 5
1 2 3 4 5
6
0 0 0 100 100 100
100 100 100 0 0 0
7
14 25 62 74 86 95 12
51 62 71 72 92 20 84```

### 输出

```
1000000000
2
100
30```

# 题解

## 作者：OIer_Hhy (赞：4)

一看题目，就知道这道题肯定是贪心。

我们先把数组 `a`、`b` 按从小到大的顺序排序。

之后，肯定是用 `b` 的最大的几个数和 `a` 最小的几个数相减，用 `b` 的最小的几个数和 `a` 最大的几个数相减。

但究竟把哪一个数作为折点呢？

枚举 `a` 数组的每一个数，尝试把这个数当作折点。即在这个数前（包括这个数），用 `b[j]` 减去 `a[j]`；这个数之后的数，用 `a[j]` 减去 `b[j]`。

用一个数记录最大值，每次循环都更新一次。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010],b[100010];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1); // 排序
	int ans=0;
	for(int i=1;i<=n;i++){ // 枚举折点
		int tmp=INT_MAX; 
		for(int j=1;j<=i;j++)
			tmp=min(tmp,abs(a[j]-b[n-i+j]));
		for(int j=i+1;j<=n;j++)
			tmp=min(tmp,abs(a[j]-b[j-i]));
		ans=max(ans,tmp);
	}
    cout<<ans<<endl;
}
signed main(){
	cin>>t;
	while(t--)
		solve();
	return 0;
}

```

管理员审核辛苦了

---

## 作者：Erica_N_Contina (赞：3)

## 思路

把 $a,b$ 从小到大排序，考虑匹配。

那么怎么样匹配呢？我们假设 $a_i$ 和 $b_{p_i}$ 匹配，那么一种是前者大于后者，一种是后者大于前者。

如果我们现在要贪心地让最小的差值最大，那么我们应该选择 $a$ 中的前几项和 $b$ 中的最后几项匹配（后附证明）。具体来说，就是

- 设定一个 $p$，让 $a_{1\sim t}$ 按顺序和 $b_{n-p+1\sim n}$ 匹配

- 剩下的同样按顺序匹配。

那么我们怎么样知道一个最优的 $p$ 呢？枚举就好了！

所以我们只需要枚举 $p$ 的值，对于每一个 $p$，我们计算每一对匹配的差值，取其中最小值作为这个 $p$ 的答案。在所有的答案中选择最大的即可。

---

证明我们应该选择 $a$ 中的前几项和 $b$ 中的最后几项匹配：

![image.png](https://cdn.luogu.com.cn/upload/image_hosting/c5a0ghkm.png)

设对于当前的 $p$，最佳情况下匹配为 $(A,A')(B,B')$，调整后匹配为 $(A,A'+A'')(B,B'+B'')$，其中 $A'+A''$ 表示将区间 $A',A''$ 顺次连接。

那么我们就发现，如果 $B$ 与 $B''$ 匹配，其中的匹配的差值的最小值一定劣于（即小于）$B$ 与 $A''$ 匹配的情况。所以应当与 $A''$ 匹配。对 $A$ 的证明也相同。

```C++
void check(int t){
    int res=INF;
    for(int i=1;i<=t;i++){
        res=min(res,abs(a[i]-b[i+n-t]));
    }
    for(int i=t+1;i<=n;i++){
        res=min(res,abs(a[i]-b[i-t]));
    }
    ans=max(ans,res);
}

void solve(){
    ans=0;
    n=rd;//快读
    for(int i=1;i<=n;i++){
        a[i]=rd;
    }
    for(int i=1;i<=n;i++){
        b[i]=rd;
    }

    sort(a+1,a+n+1);
    sort(b+1,b+n+1);

    for(int t=1;t<=n;t++){
        check(t);
    }
    cout<<ans<<endl;
}

```

---

## 作者：ღꦿ࿐ (赞：3)

本题可以做到低于 $O(n^2)$。

最大化最小值，考虑二分答案 $v$ 变为检查可行性：每个主菜匹配的开胃菜的两个值都要在 $(-\infty,x-v],[x+v,+\infty]$ 间选取，问是否存在主菜与开胃菜的完美匹配。

对开胃菜排序，得到第 $i$ 个主菜可以匹配到的开胃菜集合为一个后缀和一个前缀：$[1,L_i]\cup [R_i,n]$。


---
做法一


考虑使用霍尔定理检查完美匹配：枚举 $S$ 并检查 $|f(S)|-|S|$ 的最小值是否为 $0$，其中 $f(S)$ 表示与左部点 $S$ 存在连边的右部点集合。

枚举 $S$ 是困难的，$S$ 总共有 $2^n$ 种，不妨枚举 $f(S)$，并考虑最大的 $|S|$，首先 $f(S)$ 一定是若干前缀和后缀的并，所以 $f(S)$ 的形态为 $[1,l]\cup [r,n]$。

枚举 $l$，$r$，对于一个 $f(S)=[1,l]\cup [r,n]$ 最大的 $|S|$ 即 所有点 $u$ 满足存在连边的右部点 $e(u)\in f(S)$  的 $u$ 构成的集合，即 $\sum[L_i\leq l\land R_i\geq r]$，直接做可以 $O(n^2\log a)$。

使用线段树在扫描 $l$ 时维护 $r$ 的答案，支持区间加区间最值，容易做到 $O(n\log n\log a)$。

---

做法二，还能再快一点。

该问题弱于 [AGC076F](https://www.luogu.com.cn/problem/AT_arc076_d)，使用反悔贪心即可。时间复杂度 $O(n\log n\log a)$，注意到每个点不能匹配的区间是单调的，所有优先队列可以换成队列，时间复杂度 $O(n\log a)$。

---

## 作者：ST_AS_IS_ZHY (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1949B)

### update:2024.5.21 删除反抄袭

## 题意

给与两个数组 $a$ 和 $b$，将其中的数两两匹配，要求匹配后每组数字的差值中最小值最大，求这个值。

## 思路

首先将 $a$ 和 $b$ 升序排序，此时取任意 $p$ 满足 $1 \le p \le n$，可证对于 $1 \le i \le p$，最佳匹配为 $a_i$ 与 $b_{p + i}$ 匹配， $b_i$ 与 $a_{p + i}$ 匹配。

#### 证明部分

若存在 $i + p \le j \le n$
使得 $a_i$ 与 $b_j$ 匹配优于 $a_i$ 与 $b_{p + i}$ 匹配，则改变匹配使得$a_i$ 与 $b_j$ 匹配， $a_{j - p}
$ 与 $b_{p + i}$ 匹配，此时因为 $a_i - b_j$ 优于 $a_i - b_{p+i}$，固 $a_{j - p} - b_{p + i}$ 必然劣于 $a_{j - p}$ $ - $  $b_j$。对于全体匹配最小值来说贡献为负，固该种匹配劣于原匹配。对于 $1 \le j \le n$ 同理。

#### 证毕

所以只需要枚举每一个 $p$ ，取答案最大值即可。复杂度为
${O} (n^ 2)$.

## 代码部分

```cpp
// Problem: Charming Meals
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1949B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const int M = 5e3 + 10;

int n, a[N], b[N], vis[M], ans;

// bool check(int mid)
// {
	// memset(vis, 0, sizeof vis);
	// if(max(abs(a[1] - b[n]), abs(a[n] - b[1])) < mid) return false;
	// cout << "mid = " << mid << '\n';
	// for(int i = 1; i <= n; i ++)
	// {
		// int cnt = upper_bound(b + 1, b + n + 1, a[i]) - b, f1 = 0, f2 = 0;
		// for(int j = cnt; j <= n; j ++) if(b[j] - a[i] >= mid && !vis[j]) {vis[j] = true, f1 = j; break;}
		// for(int j = cnt - 1; j >= 1; j --) if(a[i] - b[j] >= mid && !vis[j]) {vis[j] = true, f2 = j; break;}
		// cout << "f1 = " << b[f1] << " f2 = " << b[f2] << '\n';
		// if(!f1 && !f2) return false;
		// else if((f1 && !f2) || (!f1 && f2)) continue;
		// else 
		// {
			// if(b[f1] - a[i] > a[i] - b[f2]) vis[f1] = false;
			// else vis[f2] = false;
		// }
	// }
	// return true;
// }

int work(int t)
{
	int minn = 2e9 + 10;
	for(int i = 1; i <= t; i ++) minn = min(minn, abs(a[i] - b[n - t + i]));
	for(int i = t + 1; i <= n; i ++) minn = min(minn, abs(b[i - t] - a[i]));
	return minn;
}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T --)
	{
		cin >> n; ans = -1;
		for(int i = 1; i <= n; i ++) cin >> a[i];
		for(int i = 1; i <= n; i ++) cin >> b[i];
		sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
		for(int i = 1; i <= n; i ++) ans = max(ans, work(i));
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Star_F (赞：0)

> 本题解是 $\mathcal{O}(n\log^2V)$ 的二分做法。

## 题目大意：
有两个数组 $a$ 和 $b$，可以任意交换进行匹配，最大化 $\min_{i=1}^{n} |a_i-b_i|$。

## 题目分析：
首先看到最小值最大，可以考虑二分。

结论性的，把所有配对分为 $a<b$ 和 $a>b$ 两类，那么每一类内部肯定都是顺次匹配。换句话说，最优解就是将 $a$ 的一个前缀和 $b$ 等长的后缀顺次匹配，再将 $a$ 剩余的后缀和 $b$ 剩余的前缀顺次匹配。关键就是要寻找这个断点，暴力枚举取答案即可做到 $\mathcal{O}(n^2)$。

考虑优化，二分答案，再二分前缀长度看这个前缀是否可以满足答案的需求，找出满足需求的最长前缀，在此基础上再看后缀是否合法，即可判定答案是否合法，从而加速到  $\mathcal{O}(n\log^2V)$。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
inline ll read() {
	ll x(0),f(1);
	char c=getchar();
	while(!isdigit(c)) {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c)) {
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
const int N=5050;
const int M=8e6+100;
const int mod=1e9+7;

int n;
int a[N],b[N];
bool calc1(int p,int w){
	for(int i=1;i<=p;i++){
		if(b[n-p+i]-a[i]<w) return false;
	}
	return true;
}
bool calc2(int p,int w){
	for(int i=p+1;i<=n;i++){
		if(a[i]-b[i-p]<w) return false;
	}
	return true;
}
bool check(int w){
	int st=0,ed=n;
	while(st<ed){
		int mid=(st+ed+1)>>1;
		if(calc1(mid,w)) st=mid;
		else ed=mid-1;
	}
	return calc2(st,w);
}
signed main() {
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=n;i++) b[i]=read();
		sort(a+1,a+1+n);
		sort(b+1,b+1+n);	
		int st=0,ed=1e9;
		while(st<ed){//二分答案
			int mid=(st+ed+1)>>1;
			if(check(mid)) st=mid;
			else ed=mid-1;
		}
		printf("%d\n",st);
	} 
}
```

---

## 作者：JiuZhE66666 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/pure4knowledge/p/18286752)

[原题链接](https://codeforces.com/problemset/problem/1949/B)

# HINT 1:

给定升序数组 $a,b$，已知 $b_i \geq a_i$，请任意排列 $a,b$ 使得

+ $b_i \geq a_i$ 对所有 $i$ 都成立。

+ 最大化  $\min(b_i-a_i)$。

请问该如何排列？

答案是就让 $a,b$ 升序排列，举反例可以任意交换两个 $b_i,b_j$ 验证。

# HINT 2:

假设我们已知最优配对和最优值 $k$，那么一定存在 $t$ 个小配对使得 $a_i+k \leq b_i$，$n-t$ 个大配对使得 $a_i-k \geq b_i$。

+ 对于小配对，为了最优，一定是最小的 $t$ 个 $a_i$ 去配对最大的 $t$ 个 $b_i$。

+ 对于大配对，为了最优，一定是最大的 $n-t$ 个 $a_i$ 去配对最小的 $n-t$ 个 $b_i$。

# 题解
根据上述提示，我们遍历所有的 $t$ 即可。


# code
```
#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll a[5005], b[5005];

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        for (ll i = 1; i <= n; i++) cin >> a[i];
        for (ll i = 1; i <= n; i++) cin >> b[i];

        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + n);

        ll ans = 0;
        for (ll len = 0; len <= n; len++) // 有len个小配对
        {
            ll flag = 1;
            ll val = 2e15;
            for (ll i = 1; i <= len; i++)
            {
                if (a[i] > b[n - len + i]) flag = 0;
                else val = min(val, b[n - len + i] - a[i]);
            }
            for (ll i = 1; i <= n - len; i++)
            {
                if (b[i] > a[i + len]) flag = 0;
                else val = min(val, a[i + len] - b[i]);
            }
            if (flag) ans = max(ans, val);
        }

        cout << ans << '\n';
    }
    return 0;
}

```

---

