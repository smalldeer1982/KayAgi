# カンガルー

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2012/tasks/joisc2012_kangaroo



# 题解

## 作者：喵仔牛奶 (赞：1)

# Description

有 $n$ 个套娃，每个套娃都有外体积与内体积，内体积严格小于外体积。你可以把一个娃套到另一个内体积比它的外体积大的娃里面，并且需要套到不能再套为止。求出有多少种套娃方案。

对于所有数据，$1\leq n\leq 300$。

题目链接：[JOI](https://www2.ioi-jp.org/camp/2012/2012-sp-tasks/2012-sp-day3-kangaroo-slides.pdf)、[AtCoder](https://atcoder.jp/contests/joisc2012/tasks/joisc2012_kangaroo)、[洛谷](https://www.luogu.com.cn/problem/AT_joisc2012_kangaroo)

# Solution

下文将每个套娃拿出来套，称等待被套的套娃为“单套娃”，已经拿出来的套娃为“组合套娃”。

将单套娃按外体积排序，则每个单套娃都只能套在前面的单套娃里面。处理 $\text{cnt}_i$ 为能将第 $i$ 个单套娃套入的单套娃数。

观察限制“需要套到不能再套为止”，发现组合套娃可以分为两类：
1. 合法组合套娃：其他组合套娃不能放进该组合套娃内
2. 非法组合套娃：其他组合套娃可以放进改组合套娃内

最终所有组合套娃都必须是合法套娃。

考虑 DP。设 $f_{i,j,k}$ 为前 $i-1$ 个单套娃，套成了 $j$ 个组合套娃，有 $k$ 个是非法的。转移
- 将第 $i$ 个单套娃放入非法组合套娃内：$f_{i+1,j,k-1}\gets f_{i,j,k}\times k$。
- 将第 $i$ 个单套娃放入合法组合套娃内：$f_{i+1,j,k}\gets f_{i,j,k}\times (\text{cnt}_i-(i-1-j)-k)$，其中 $i-1-j$ 是 $1\sim i-1$ 被套掉的单套娃数，这些单套娃一定能够将 $i$ 套入，$\text{cnt}_i-(i-1-j)$ 即当前的组合套娃中能够套入 $i$ 的个数，$\text{cnt}_i-(i-1-j)-k$ 即当前的合法组合套娃中能够套入 $i$ 的个数。
- 将第 $i$ 个单套娃变为一个组合套娃：$f_{i+1,j+1,\text{cnt}_i-(i-1-j)}\gets f_{i,j,k}$。

答案为 $\displaystyle\sum_{i=1}^{n}f_{n+1,i,0}$。

时间复杂度 $\mathcal{O}(n^3)$。

# Code
```cpp
#include <bits/stdc++.h>
#define Up(i, l, r) for (int i = (l); i <= (r); i ++)
#define fi first
#define se second
using namespace std;
namespace Milkcat {
	typedef long long LL;
    typedef pair<LL, LL> pii;
	const int N = 305, mod = 1e9 + 7;
    LL n, ans, cnt[N], f[2][N][N]; pii a[N]; 
    void add(LL& x, LL y) { x = (x + y) % mod; }
    int main() {
    	cin >> n, f[1][0][0] = 1;
    	for (int i = 1; i <= n; i ++)
    		cin >> a[i].fi >> a[i].se;
    	sort(a + 1, a + 1 + n, greater<pii>());
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j < i; j ++)
				if (a[i].fi < a[j].se) cnt[i] ++;
    	for (int i = 1; i <= n; i ++){
    		int now = i & 1, nxt = now ^ 1;
    		Up(j, 0, n) Up(k, 0, n) f[nxt][j][k] = 0;
    		Up(j, 0, i - 1) Up(k, 0, j) {
				if (k) add(f[nxt][j][k - 1], f[now][j][k] * k);
				add(f[nxt][j][k], f[now][j][k] * (cnt[i] - (i - 1 - j) - k));
				add(f[nxt][j + 1][cnt[i] - (i - 1 - j)], f[now][j][k]);
			}
		}
		for (int i = 1; i <= n; i ++)
			ans = (ans + f[(n + 1) & 1][i][0]) % mod;
		cout << ans << '\n';
        return 0;
    }
}
int main() {
	freopen("dolls.in", "r", stdin);
	freopen("dolls.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    int T = 1;
    while (T --) Milkcat::main();
    return 0;
}

/*
5
4 3
3 1
6 5 
2 1
4 2
*/
```

---

## 作者：SFlyer (赞：0)

$\mathcal{O}(n^3)$ 方法就不再赘述（前 $i$ 个，$j$ 条链，$k$ 个不满足）。

考虑 $a,b$ 分开来排序，从小到大，如果相同先排 $b$。比如说 `3 2`、`2 1` 排成 `1 2(b) 2(a) 3`，$a$ 写成 `)`，$b$ 写成 `(`，就是 `(())`。那么现在问题变成了：一个袋鼠可以塞进另一个袋鼠就是两个括号严格在前面，塞完了不能还有没有被塞的可以塞前面的括号。

发现合不合法只和最靠前的没有被塞的括号有关。设 $dp_{i,j,0/1}$ 为前 $i$ 个括号（一共 $2n$ 个），还有 $j$ 个要被塞，现在有没有出现“没有被塞”这个情况了。因为是排好序的，所以后面的 `(` 一定可以塞得下前面的 `)`。分情况转移：

- 如果是 `)`。那么我们可以决定钦不钦定是不是没有被塞，那么 $dp_{i,j+1,k}+=dp_{i-1,j,k}$ 或 $dp_{i,j,1}+=dp_{i,j,k}$。
- 如果是 `(`。只有在 $k=0$ 的之后我才可以不塞东西。因此 $dp_{i,j-1,0/1}+=dp_{i-1,j,0/1}\times j$（选择哪个塞），和 $dp_{i,j,0}+=dp_{i-1,j,0}$。

因此得到一个 $\mathcal{O}(n^2)$ 的算法。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e3+3;
const ll mod = 1e9+7;

ll n,dp[N][2],f[N][2];
vector<pair<int,int> > p;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=1; i<=n; i++){
		int a,b;
		cin>>a>>b;
		p.push_back({a,1});
		p.push_back({b,0});
	}
	sort(p.begin(),p.end());
	dp[0][0]=1;
	for (int i=1; i<=n*2; i++){
		for (int j=0; j<=n; j++){
			f[j][0]=dp[j][0],f[j][1]=dp[j][1];
			dp[j][0]=dp[j][1]=0;
		}
		if (p[i-1].second){
			for (int j=0; j<=n; j++){
				for (int k=0; k<2; k++){
					dp[j+1][k]=(dp[j+1][k]+f[j][k])%mod;
					dp[j][1]=(dp[j][1]+f[j][k])%mod;
				}
			}
		}
		else{
			for (int j=0; j<=n; j++){
				for (int k=0; k<2; k++){
					if (j) dp[j-1][k]=(dp[j-1][k]+f[j][k]*j%mod)%mod;
				}
				dp[j][0]=(dp[j][0]+f[j][0])%mod;
			}
		}
	}
	cout<<dp[0][1]<<endl;
	return 0;
}
```

---

