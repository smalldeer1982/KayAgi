# Make a Palindrome

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

Let the function $ f(b) $ return the minimum number of operations needed to make an array $ b $ a palindrome. The operations you can make are:

- choose two adjacent elements $ b_i $ and $ b_{i+1} $ , remove them, and replace them with a single element equal to $ (b_i + b_{i + 1}) $ ;
- or choose an element $ b_i > 1 $ , remove it, and replace it with two positive integers $ x $ and $ y $ ( $ x > 0 $ and $ y > 0 $ ) such that $ x + y = b_i $ .

For example, from an array $ b=[2, 1, 3] $ , you can obtain the following arrays in one operation: $ [1, 1, 1, 3] $ , $ [2, 1, 1, 2] $ , $ [3, 3] $ , $ [2, 4] $ , or $ [2, 1, 2, 1] $ .

Calculate $ \displaystyle \left(\sum_{1 \le l \le r \le n}{f(a[l..r])}\right) $ , where $ a[l..r] $ is the subarray of $ a $ from index $ l $ to index $ r $ , inclusive. In other words, find the sum of the values of the function $ f $ for all subarrays of the array $ a $ .

## 样例 #1

### 输入

```
4
3
2 1 3
4
1 1 1 1
5
4 2 3 1 5
4
1 2 1 2```

### 输出

```
3
0
14
5```

# 题解

## 作者：灵茶山艾府 (赞：23)

合并操作，每次可以减少一个数字。

分解操作，比如最左边是 $2$，最右边是 $5$，我们分解大的那个数，得到 $3$ 和 $2$。这等价于去掉最左边的数，并修改最右边的数。所以每次操作也可以减少一个数字。

所以两种操作效果是相同的，不妨只考虑合并操作。

长为 $m$ 的子数组 $b$，操作 $m-1$ 次可以变成一个数，此时一定是回文的。

能否减少操作次数呢？

比如 $b=[2,2,1,3]$，左右都可以合并成 $4$，最后得到 $[4,4]$，这样只需操作 $2$ 次而不是 $3$ 次，减少了 $1$ 次操作。

又比如 $b=[2,2,9,1,3]$，左右都可以合并成 $4$，最后得到 $[4,9,4]$，这样只需操作 $2$ 次而不是 $4$ 次，减少了 $2$ 次操作。

一般地，如果前缀 $[0,i]$ 与后缀 $[j,m-1]$ 的元素和相同，那么可以减少 $1$ 次操作。注意前后缀**可以相交**，在 $b=[2,2,9,1,3]$ 这个例子中，我们有 $2+2=1+3$，同时还有 $2+2+9=9+1+3$，所以可以减少 $2$ 次操作。 

考虑贡献法，如果有两个非空子数组 $[i_1,j_1],[i_2,j_2]$ 的元素和相同，那么对于下标从 $i_1$ 到 $j_2$ 的子数组 $b$ 来说，可以减少 $1$ 次操作，对答案的贡献就是 $-1$。

所以只需统计非空子数组和的个数 $\textit{cnt}_s$。遍历到子数组 $[i,j]$ 时，设其元素和为 $s$，那么它与之前统计过的 $\textit{cnt}_s$ 个子数组和相同，对答案的贡献就是 $j-i-\textit{cnt}_s$。其中 $j-i$ 是不考虑相同前后缀时，长为 $j-i+1$ 的子数组所需的操作次数。

```go
package main
import ."fmt"

func main() {
	var T, n int
	for Scan(&T); T > 0; T-- {
		Scan(&n)
		a := make([]int, n)
		for i := range a {
			Scan(&a[i])
		}
		ans := 0
		cnt := map[int]int{}
		for i := 0; i < n; i++ {
			s := 0
			for j := i; j < n; j++ {
				s += a[j] // s 等于从 a[i] 到 a[j] 的子数组和
				ans += j - i - cnt[s]
				cnt[s]++
			}
		}
		Println(ans)
	}
}
```

**时间复杂度**：$\mathcal{O}(n^2)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：wrkwrkwrk (赞：3)

根据数据范围，考虑处理出每个字串的答案并求和。

显然，长度 $\leq 1$ 的时候答案为 $0$。对每个串的答案不超过长度 $-1$。

考虑从其他短串的答案构造为长串的答案赋值。由回文串的定义可知对一个回文串的两端加上同一个数仍是回文串。

因此，对于每个串，我们需要找到两边不交且和相等的两个子串。

接下来认为一个区间为 $[l,r)$。

此时，认为里面的区间为 $[l',r')$，我们发现赋值有 $dp_{l,r} \gets_{\min} dp_{l',r'}+r-r'+l'-l-2$。达成这一条件的要求是 $\sum_{i=l}^{l'-1}a_i=\sum_{i=r'+1}^{r-1}a_i$。

此时，记 $b_i$ 为前缀和，得到 $b_{l'-1}-b_{l-1}=b_{r-1}-b_{r'-1}$，即 $b_{l'-1}+b_{r'-1}=b_{r-1}+b_{l-1}$。

此时，我们发现所有 $b_{l-1}+b_{r-1}$ 相等的满足要求，且由于 $a_i > 0$，当 $l$ 递增时 $r$ 递减，单向满足条件。 

由于互相包含，一次跨过一个选内部的答案是会更劣的，于是对以上过程得到的数组后面的放到上前面的即可。最后求和就是答案。

时间复杂度 $O(n^2 \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace _wrk{;
#define int long long
int a[2003];
int dp[2003][2003];
int p[2003][2003];
int q[2003][2003];
map<int,vector<pair<int,int>>>w;
signed main(){
	int t;
	cin>>t;
	while(t--){
		w.clear();
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dp[i][j]=max(0ll,j-i);
				p[i][j]=q[i][j]=0;
			}
		}
		for(int i=1;i<=n;i++){
			a[i]+=a[i-1];
		}
		for(int i=1;i<=n;i++){
			for(int j=i-1;j<=n;j++){
				w[a[i-1]+a[j]].push_back({i,j});
			}
		}
		for(auto &x:w){
			auto &ff=x.second;
			sort(ff.begin(),ff.end());
			for(int i=0;i<ff.size()-1;i++){
				p[ff[i].first][ff[i].second]=ff[i+1].first-ff[i].first;
				q[ff[i].first][ff[i].second]=ff[i].second-ff[i+1].second;
			}
		}
		int ans=0;
		for(int l=n;l>=1;l--){
			for(int r=l;r<=n;r++){
				if(p[l][r])dp[l][r]=min(dp[l][r],p[l][r]+q[l][r]-2+dp[l+p[l][r]][r-q[l][r]]);
				ans+=dp[l][r];
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
}
signed main(){
	   return _wrk::main();
}
```
[AC](https://codeforces.com/contest/2004/submission/276741375) 记录。

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/CF2004F)

**题目大意**

> 对于数组 $a$，一次操作可以把 $a_i,a_{i+1}$ 替换成 $a_i+a_{i+1}$ 或进行逆操作。
>
> 定义数组权值和为：令数组回文的最小操作数，求 $a$ 的每个子区间权值和。
>
> 数据范围：$n\le 2000$。

**思路分析**

用这样的方式刻画数组 $b_1\sim b_m$：有 $B=\sum b_i$ 个球，球中间有 $m-1$ 个隔板，第 $i-1$ 个和第 $i$ 个隔板之间的距离是 $b_i$。

设 $b_i$ 前缀和为 $s_i$，那么 $s_1\sim s_{m-1}$ 即为隔板位置。

那么一次操作就是插入或删除一个隔板，而数组回文当且仅当隔板序列回文。

那么每个隔板都要在对面操作一次，除非其对面的位置恰好有隔板，即 $s_j=B-s_i$ 时对答案产生 $-2$ 贡献（如果 $s_j=s_i=\dfrac B 2$ 答案 $-1$）。

容易发现两个和相等的不相邻子区间恰好对答案产生 $-2$ 贡献，因此扫描线维护 $a[1,i)$ 中每个区间和的出现次数。

注意相邻的两个子区间对答案产生 $-1$ 贡献。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
const int MAXN=2005;
int a[MAXN];
void solve() {
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) ans+=(i-1)*(n-i+1);
	gp_hash_table <int,int> cnt;
	for(int i=1;i<=n;++i) {
		for(int j=i,s=0;j<=n;++j) ans-=cnt[s+=a[j]];
		for(int j=i,s=0;j>=1;--j) ++cnt[s+=a[j]];
		for(int j=i-1,s=0;j>=1;--j) ++cnt[s+=a[j]];
	}
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：tokitsukaze (赞：2)

考虑求出所有子串的结果。

- 首先发现一个结论：合并操作和分解操作是等价的。

  感性理解：考虑把子串的一个数分解成若干个数，使得子串变成回文，那么在这个数的另一侧，必定存在同样的合并操作。

  分解操作感觉很不好处理，于是我们只考虑合并操作。

- 由于是回文，考虑从短的回文子串往外扩展：两端放上相同的数，变成更长的回文子串。所以我们可以从短到长地求每个子串变成回文的答案。即第一步为，从小到大枚举长度！

- 现在考虑区间 dp，我们的思路为：从小到大枚举长度，根据回文子串往外扩展的过程进行转移，即在两侧加上一些和相等的数。

- 具体的，设 $dp_{l,r}$ 表示子串 $s_{l,r}$ 变成回文的最小合并次数，初始 $dp_{i,i}=0$。

  先考虑暴力 dp 如何实现。

  根据区间 dp 的模板，第一个循环枚举长度 $len$，第二个循环枚举左端点 $l$，根据左端点计算出右端点 $r$。由 dp 的定义可得初始值为 $r-l$，表示把这个子串合并成了一个数。

  由于要从短的回文子串变成当前的回文子串，所以需要枚举短的回文子串是谁。于是再写两个循环枚举 $x$ 与 $y$ 表示回文子串 $s_{x,y}$。那么如果 $\sum_{i=l}^{x-1}{a_i}$ 与 $\sum_{i=y+1}^{r}{a_i}$ 相等，则可以通过回文子串 $s_{x,y}$ 的两侧增加相同的一个数来得到回文子串 $s_{l,r}$。然后把两侧分别变为一个数的代价是 $(x-1-l)+(r-y-1)$。

  于是转移就是：

  $dp_{l,r} \gets \min(dp_{l,r},dp_{x,y}+(x-1-l)+(r-y-1))$

  实现如下：

  ```cpp
  for(i=1;i<=n;i++) dp[i][i]=dp[i][i-1]=0;
  for(len=2;len<=n;len++)
  {
      for(l=1;l+len-1<=n;l++)
      {
          r=l+len-1;
          dp[l][r]=r-l;
          for(x=l;x<=r;x++)
          {
              for(y=x-1;y<r;y++)
              {
                  if(bit[x-1]-bit[l-1]!=bit[r]-bit[y]) continue;
                  dp[l][r]=min(dp[l][r],dp[x][y]+(x-1-l)+(r-y-1));
              }
          }
      }
  }
  ```
  其中`bit`为前缀和数组。

  然后会发现上述代码里的 $y$ 从 $x-1$ 开始，这是因为空串也可以在两边添加一个相同的数变成回文，所以用 $dp_{x,x-1}$ 表示空串。

- 现在时间复杂度的瓶颈在于需要枚举 $x$ 和 $y$ 从 $dp_{x,y}$ 转移，考虑如何优化。

  发现 dp 的转移条件与等式有关。当出现等式相关的式子时，有一种经典的优化方式：把等式的一边装入桶，另一边就可以在桶里进行查询。

  dp 转移条件为：`bit[x-1]-bit[l-1]==bit[r]-bit[y]`。

  将式子移项，把 $l$ 和 $r$ 放在等式的一边，把 $x$ 和 $y$ 放在等式的另一边，即原式变为：`bit[x-1]+bit[y]==bit[l-1]+bit[r]`。

  这样我们就能将`bit[x-1]+bit[y]`作为桶的下标，将 $dp_{x,y}$ 更新进桶里。

  但我们发现在 dp 转移方程中还有与 $x$ 和 $y$ 有关的量，所以我们需要将这些量也与 $dp_{x,y}$ 一起更新进桶。

  我们将 $dp_{x,y}+(x-1-l)+(r-y-1)$ 看作 $(dp_{x,y}+x-y-1)+(r-l-1)$。这样我们就能将 $dp_{x,y}+x-y-1$ 更新进桶，转移时再加上 $r-l-1$ 即可。

  实现如下：

  ```cpp
  map<ll,int> mp;
  for(i=1;i<=n;i++)
  {
      dp[i][i]=0;
      mp[bit[i-1]+bit[i]]=dp[i][i]+(i-i-1);
      dp[i][i-1]=0;
      mp[bit[i-1]+bit[i-1]]=dp[i][i-1]+(i-(i-1)-1);
  }
  for(len=2;len<=n;len++)
  {
      for(l=1;l+len-1<=n;l++)
      {
          r=l+len-1;
          if(!mp.count(bit[l-1]+bit[r])) mp[bit[l-1]+bit[r]]=INF;
          dp[l][r]=min(r-l,mp[bit[l-1]+bit[r]]+r-l-1);
          mp[bit[l-1]+bit[r]]=min(mp[bit[l-1]+bit[r]],dp[l][r]+l-r-1);
      }
  }
  ```

  由于用了 `map` 当桶，桶内最多有 $O(n^2)$ 种元素，所以时间复杂度为 $O(n^2\log n^2)$。

  [AC记录](https://codeforces.com/contest/2004/submission/284269154)

---

## 作者：happybob (赞：0)

题意：

给定一个由 $n$ 个整数组成的数组 $a$ 。

定义函数 $f(b)$ 为数组 $b$ 变为回文数组所需的最少运算次数。可以进行的运算有：

- 选择两个相邻的元素 $b_i$ 和 $b_{i+1}$，删除它们，并用一个等于 $b_i + b_{i + 1}$ 的元素替换它们。
- 或选择一个元素 $b_i > 1$，将其删除，并用两个正整数 $x$ 和 $y$（$x > 0$ 和 $y > 0$）替换，使得 $x + y = b_i$。

计算 $\displaystyle \left(\sum_{1 \le l \le r \le n}{f(a[l\dots r])}\right)$ ，其中 $a[l\dots r]$ 是 $a$ 的从 $l$ 到 $r$ 的子串，边界包括在内。换句话说，求数组 $a$ 中所有子串的函数 $f$ 值之和。

多组数据，$1\leq t \leq 1000$，$1\leq n \leq 2000$，$1\leq a_i \leq 10^5$，$\sum n \leq 2000$。

解法：

首先两种操作互逆，容易发现一种操作是没有用的。我们可以只使用第二种操作，因为所有第一种操作都可以在中心对称的位置执行操作二。

对于一个序列，其 $f$ 值容易递归计算。若开头和结尾相同，则删去开头与结尾，否则考虑将较大的分裂并将较小的删去。这样可以做到 $O(n^3)$。

然后考虑区间 DP，发现一个子区间若有一段前缀与后缀和相同，则操作若干次后会得到一个更小的子区间。使用哈希维护即可做到 $O(n^2)$。

[Submission Link.](https://codeforces.com/contest/2004/submission/298682152)

---

