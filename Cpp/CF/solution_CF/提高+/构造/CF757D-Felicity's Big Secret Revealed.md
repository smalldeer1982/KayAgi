# Felicity's Big Secret Revealed

## 题目描述

The gym leaders were fascinated by the evolutions which took place at Felicity camp. So, they were curious to know about the secret behind evolving Pokemon.

The organizers of the camp gave the gym leaders a PokeBlock, a sequence of $ n $ ingredients. Each ingredient can be of type $ 0 $ or $ 1 $ . Now the organizers told the gym leaders that to evolve a Pokemon of type $ k $ ( $ k>=2 $ ), they need to make a valid set of $ k $ cuts on the PokeBlock to get smaller blocks.

Suppose the given PokeBlock sequence is $ b_{0}b_{1}b_{2}...\ b_{n-1} $ . You have a choice of making cuts at $ n+1 $ places, i.e., Before $ b_{0} $ , between $ b_{0} $ and $ b_{1} $ , between $ b_{1} $ and $ b_{2} $ , ..., between $ b_{n-2} $ and $ b_{n-1} $ , and after $ b_{n-1} $ .

The $ n+1 $ choices of making cuts are as follows (where a | denotes a possible cut):

 $ |\ b_{0}\ |\ b_{1}\ |\ b_{2}\ |\ ...\ |\ b_{n-2}\ |\ b_{n-1}\ | $ Consider a sequence of $ k $ cuts. Now each pair of consecutive cuts will contain a binary string between them, formed from the ingredient types. The ingredients before the first cut and after the last cut are wasted, which is to say they are not considered. So there will be exactly $ k-1 $ such binary substrings. Every substring can be read as a binary number. Let $ m $ be the maximum number out of the obtained numbers. If all the obtained numbers are positive and the set of the obtained numbers contains all integers from $ 1 $ to $ m $ , then this set of cuts is said to be a valid set of cuts.

For example, suppose the given PokeBlock sequence is $ 101101001110 $ and we made $ 5 $ cuts in the following way:

 $ 10\ |\ 11\ |\ 010\ |\ 01\ |\ 1\ |\ 10 $ So the $ 4 $ binary substrings obtained are: $ 11 $ , $ 010 $ , $ 01 $ and $ 1 $ , which correspond to the numbers $ 3 $ , $ 2 $ , $ 1 $ and $ 1 $ respectively. Here $ m=3 $ , as it is the maximum value among the obtained numbers. And all the obtained numbers are positive and we have obtained all integers from $ 1 $ to $ m $ . Hence this set of cuts is a valid set of $ 5 $ cuts.

A Pokemon of type $ k $ will evolve only if the PokeBlock is cut using a valid set of $ k $ cuts. There can be many valid sets of the same size. Two valid sets of $ k $ cuts are considered different if there is a cut in one set which is not there in the other set.

Let $ f(k) $ denote the number of valid sets of $ k $ cuts. Find the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757D/752917f3f08a748323db829d6086efa4b31f63b6.png). Since the value of $ s $ can be very large, output $ s $ modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the sets of valid cuts are:

Size $ 2 $ : |1|011, 1|01|1, 10|1|1, 101|1|.

Size $ 3 $ : |1|01|1, |10|1|1, 10|1|1|, 1|01|1|.

Size $ 4 $ : |10|1|1|, |1|01|1|.

Hence, $ f(2)=4 $ , $ f(3)=4 $ and $ f(4)=2 $ . So, the value of $ s=10 $ .

In the second sample, the set of valid cuts is:

Size $ 2 $ : |1|0.

Hence, $ f(2)=1 $ and $ f(3)=0 $ . So, the value of $ s=1 $ .

## 样例 #1

### 输入

```
4
1011
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2
10
```

### 输出

```
1
```

# 题解

## 作者：泠小毒 (赞：4)

# T2-Felicity's Big Secret Revealed
给定一个01串，一个有效的n切割定义如下：一个横杠代表一次切割，第一条横杠前面的01串不算，最后一条横杠后面的01串不算，将两个横杠中的01串转化成十进制数字，假设这些数字的最大值是MAX且这些数字囊括了1-MAX的所有数字，则称为一次有效切割。求2~n+1次有效切割的切法总数。
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190513/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190513.html)
## 解法
由于题目要求包含所有1—MAX的数字，且n<=75，所以MAX<=20。

dp[i][k]表示第i位前有一次切割且状态为k，接着从第i位开始枚举到第j位为下一个横杆的位置，设这两段横杆之间的数字为p（十进制），则

dp[j+1][k|(1<<p-1)]+=dp[i][k]，k为1～（1<<20）的状态。最后把dp[i][(1<<t)-1]（0<=i<=n，1<=t<=20）加起来就可以了。
## ac代码
```cpp
#include<bits/stdc++.h> 
#define mod 1000000007
#define lim 1048576
using namespace std;
int n,ans,a[100],dp[100][lim+10];
int main()
{
	memset(dp,0,sizeof(dp)),scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%1d",&a[i]);
	for(int i=0;i<n;i++)
	{
		dp[i][0]=1;
		for(int k=0;k<lim;k++)
		{
			if(!dp[i][k])continue;
			for(int j=i,p=a[i];j<n&&p<=20;j++,p=(p*2+a[j]))
				if(p)dp[j+1][k|(1<<(p-1))]=(dp[j+1][k|(1<<(p-1))]+dp[i][k])%mod;
		}
	}
	for(int i=0;i<=n;i++)for(int k=1;k<=20;k++)ans=(ans+dp[i][(1<<k)-1])%mod;
	printf("%d\n",ans);
}
```

---

## 作者：Mihari (赞：2)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF757D)

# 题解

有个极为显然的想法：定义 $f[i][j]$ 为最后一下划分到 $i$ 之前的位置，前面的划分使得出现方案为 $j$ 的合法方案数。

但是 $j$ 应该开多大？我们可以计算一下：设 $f(x)$ 为 $x$ 的二进制长度，那么有
$$
\sum_{i=1}^{21}f(i)=78
$$
显然，划分出来的数组中，最大的数不能超过 $20$，不然显然无解

那么 $j\le 2^{20}$，这个范围我们确定，而转移也很明显，枚举下一个划分点 $k$，那么有
$$
f[k+1][j']=\sum f[i][j]
$$
其中有 $[i,k]$ 这个区间的划分能使集合 $j$ 变为 $j'$，至于为什么第一维是 $k+1$，是因为我们的定义是划分到 $k+1$ 之前的位置 $k$，故而 $k+1$.

对于初始化，我们第一个划分的区间是要被舍去的，所以有 $f[i][0]$ 表示在 $i$ 位之前有一个划分，其出现方案为空集，我们将其强制为 $1$ 表示有这样一种划分方案（但是第一个区间被舍去，便没有出现的数字）

最后，有效划分为全部数字都出现过，即 $j$ 的所有元素均出现过，相当于其二进制表示下，所有位数均为 $1$，我们将这样的方案累加便可得到最终结果。

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13442698.html
*/
```



---

## 作者：tai_chi (赞：0)

注意到把所有数字按二进制字符串拼起来长度增长很快，但总长小于 $75$，可以得到结论 $num \le 20$（选取了 $1 \dots num$）。

这提示我们进行状压，令 $f_{i,j}$ 表示第 $i$ 位**前**有**最后一次**切割且得到数字 $1 \dots 20$ 的状态为 $j$，转移可表示为：

$$
f_{k + 1, j \operatorname{or} 2^{sum(i,k) - 1}} \gets f_{i,j}
$$

其中 $sum(i,j)$ 表示区间 $[i,j]$ 按二进制表示的数字，箭头表示 `+=`，这个转移方程与代码中的相同。

复杂度 $O(n^3)$，足以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;

bool st;
const int N = 85, mod = 1e9 + 7;
int n;
string s;

int a[N];
int f[N][1500005];
int sum[N][N];

int get(int l, int r)
{
	int ret = 0;
	for (int i = l; i <= r; i++)
	{
		ret = ret * 2 % mod + a[i];
		ret %= mod;
	}
	return ret;
}
bool ed;

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cerr << (&ed - &st) / 1024.0 / 1024.0 << endl;
	cin >> n >> s;
	for (int i = 1; i <= n; i++)
	{
		if (s[i - 1] == '0') a[i] = 0;
		else a[i] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			int cnt = get(i, j);
			if (cnt > 20) break;
			sum[i][j] = cnt;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = 1;
		for (int j = 0; j <= (1 << 20) - 1; j++)
		{
			if (!f[i][j]) continue;
			for (int k = i; k <= n; k++)
			{
				if (sum[i][k])
				{
					int &to = f[k + 1][j | (1 << (sum[i][k] - 1))];
					to = (to + f[i][j]) % mod;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n + 1; i++)
	{
		for (int j = 1; j <= 20; j++)
			ans = (ans + f[i][(1 << j) - 1]) % mod;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：wflhx2011 (赞：0)

## Solution

诈骗题。

第一眼看题目可能没有任何思路，$n\le75$ 怎么做？

可仔细看题，它是在一个长度为 $n$ 的字符串内进行 $n$ 次切割。

这个字符串是什么样的？对答案能有用的便是从 $1$ 到 $x$ 连续的一串数，它们的二进制拼接起来形成的字符串。

等等，长度为 $n$？$n\le75$？

那么这个 $x$ 最大是多少？手算一下，长度为 $1$ 的有 $1$ 这一个数，长度为 $2$ 的有 $2$，$3$ 两个数，以此类推，算到 $15$ 就是 $1\times1 + 2\times2+3\times4+4\times8=49$，还有 $75-49=26$，所以 $x$ 最大也就是 $15+\lfloor\frac{26}{5} \rfloor=20 $。

所以考虑动规，设 $dp[i][j]$ 表示切割在第 $i$ 位前，在两次切割间有 $j$。

然后枚举下一次切割 $k$ 的位置，设这之间的十进制数为 $o$，易得转移方程 $dp[k+1][j \operatorname{or} {2^{o-1}}]+=dp[i][j]$。

最后统计 $dp[i][2^j-1]$ 的和即可。

### 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,ans,a[105],dp[105][1048600],mod=1e9+7;
string s;
int main()
{
	cin>>n>>s;
	for(int i=0;i<s.size();i++)
		a[i]=s[i]-'0';
	for(int i=0;i<n;i++)
	{
		dp[i][0]=1;
		for(int j=0;j<(1<<20);j++)
		{
			if(!dp[i][j])
				continue;
			for(int k=i,o=a[i];k<n&&o<=20;k++,o=(o*2+a[k]))
				if(o)
					dp[k+1][j|(1<<(o-1))]=dp[k+1][j|(1<<(o-1))]%mod+dp[i][j]%mod;
		}
	}
	for(int i=0;i<=n;i++)
		for(int j=1;j<=20;j++)
			ans=ans%mod+dp[i][(1<<j)-1]%mod;
	cout<<ans%mod;
	return 0;
}
```

---

## 作者：Targanzqq (赞：0)

一道经典的状压 dp。

我们可以翻译一下原题的意思，就是说从找一些相邻的数集（不一定包含开头和结尾），把这些数集改成十进制后正好是一些从 $1$ 开始的连续的数。

我在听到老师讲解后才明白，由于 $n$ 只有 $75$，我们考虑一个式子：$\sum_{i=1}^x bit(i)\le 75$，我们得到 $x\le 20$。因此我们可以做状压 $dp$。接下来我们 $1$ 到 $20$ 放进状态数组里（放进去的时候都要减 $1$），设 $f_{i,j}$ 为前 $i-1$ 位放进集合里的数表示为 $j$ 的方案数。

这样我们能得到一个式子：设 $k$ 为下一次转移的位置，$p$ 为新加入的数，那么 $p$ 我们可以直接算，如果 $p\le 20$，那么 令 $f_{k,j|p}$ 加上 $f_{i,j}$。最后我们按照要求统计 $ans$ 并输出即可。因为前面我们不要了，所以题目要求中的 $i$ 改为从 $1$ 到 $n$。

源代码：
```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;

int n,f[76][(1<<20)],a[75];
long long ans;
char s[100];

signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s[i];a[i]=s[i]-'0';
	}
	for(int i=0;i<n;i++){
		f[i][0]=1;
		for(int j=0;j<(1<<20);j++){
			if(!f[i][j])continue;
			for(int k=i,p=a[i];k<n&&p<=20;k++,p=p*2+a[k]){
				if(p){
					f[k+1][j|(1<<(p-1))]+=f[i][j];
					f[k+1][j|(1<<(p-1))]%=mod;
				}
			}
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=1;j<=20;j++){
			ans+=f[i][(1<<j)-1];
			ans%=mod;
		}
	}
	cout<<ans;
}

```

---

## 作者：AmaoFox (赞：0)

我一开始懵懂的以为最多可以切出 $75$ 个数，然后就不会做了。但是后来发现，如果我们从 $1$ 开始全部都拼起来，那么最终会有如下的序列：

$$1|10|11|100|101|110|111|1000|1001|1010|1011|1100|1101|1110|1111|10000|10001|10010|10011|10100|10101$$

我才加到 $21$ 整个串的长度就已经有 $79$ 个数了，因此实际上最多只能切出 $20$ 个数。

那么，我们就可以开始愉快的状压 DP 了。

设 $dp_{i,j}$ 表示最后一刀切到第 $i$ 个空隙并且已有的数为 $j$ 的方案。由于数据范围很小，可以使用最朴素的方式进行一刀一刀的转移。

```
#include <bits/stdc++.h> 

using namespace std;

const int N = 80, MAX = 20, mod = 1000000007;

int a[N], dp[N][(1 << MAX) + 5];

int main() {
  int n, ans = 0;
  cin >> n;
  for(int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    a[i] = c - '0';
    dp[i][0] = 1;
  }
  for(int i = 1; i <= n; i++) {
    for(int mask = 0; mask < (1 << MAX); mask++) {
      if(!dp[i][mask]) {
        continue;
      }
      int cur = 0;
      for(int j = i; j <= n; j++) {
        cur = cur * 2 + a[j];
        if(cur > MAX) {
          break;
        }
        if(cur) {
          (dp[j + 1][mask | (1 << cur - 1)] += dp[i][mask]) %= mod;
        }
      }
    }
  }
  for(int i = 1; i <= n + 1; i++) {
    for(int mask = 1; mask <= MAX; mask++) {
      (ans += dp[i][(1 << mask) - 1]) %= mod;
    }
  }
  cout << ans;
}
```

---

