# Send Boxes to Alice (Easy Version)

## 题目描述

有 $n$ 个盒子，每个盒子有 $a_i$ 个糖果，你每一次可以将第 $i$ 个盒子里的糖果放到第 $i-1$ 或 $i+1$ 个盒子中（如果盒子存在）。最后要存在一个整数 $k(k>1)$，使得每个盒子的糖果数量都被 $k$ 整除 （注意盒子可以为空），问最小操作数。

## 说明/提示

$1 \le n \le 10^5$

$0 \le a_i \le 1$

## 样例 #1

### 输入

```
3
1 0 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
-1
```

# 题解

## 作者：Hovery (赞：3)

## Problem

[Send Boxes to Alice (Easy Version)](https://www.luogu.com.cn/problem/CF1254B1)

## Sol

先判无解的情况，就是若序列中只有一个 $1$，那么显然不行，否则必定有解。

整除 $k$ 的话我们可以考虑枚举这个 $k$ 去统计答案。

假设我们现在已经知道了这个 $k$。

那么显然就要把每 $k$ 个 $1$ 都弄到一起。

对于一个序列，最后肯定会把所有的 $1$ 都堆到原来为 $1$ 的地方。

举个例子。

例如 $1001001$ 它最后肯定是堆成 $3000000$，$0000003$ 和 $0003000$ 中的一种。

所以每次我们枚举堆到的位置，再去统计答案即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, a[100010], b[100010], now, cnt;

signed main()
{
    cin >> n;
    int x = 0;
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i];
        x += a[i];
        if (a[i])
        {
            b[++cnt] = i;
        }
    }
    if (x == 1)
    {
        cout << -1;
        return 0;
    }
    int Minn = (int)1e18;
    for (int i = 2;i <= x;i++)
    if (x % i == 0)
    {
        now = i;
        long long ans = 0;
        for (int i = now;i <= cnt;i += now)
        {
            int sum = 0, sum1 = 0, Min = (int)1e18;
            for (int j = i - now + 1;j <= i;j++)
            {
                sum1 += b[j];
            }
            for (int j = i;j > i - now;j--)
            {
                Min = min(Min, (j + now - i) * b[j] - sum1 + sum - (i - j) * b[j]);
                sum += b[j];
                sum1 -= b[j];
            }
            ans += Min;
        }
        Minn = min(Minn, ans);
    }
    cout << Minn;
}
```

上面的代码复杂度是 $O(n\sqrt{n})$ 的，因为 $i$ 是每次加上 $now$ 的。

---

## 作者：Licykoc (赞：3)

reference：Codeforces Tutorial。

先来考虑固定 $k$ 时怎么做。设 $b_i = \sum_{j = 1}^{i} a_j$，发现：

$$\forall 1 \le i \le n ,{k \mid a_i} \Longleftrightarrow \forall 1 \le i \le n, k \mid b_i$$

同时可以发现：

1. 将 $a_i$ 取出 $1$ 并放入 $a_{i+1}$ 这个操作等价于 $b_i \gets b_i - 1$。

2. 将 $a_{i+1}$ 取出 $1$ 放入 $a_i$ 等价于 $b_i \gets b_i + 1$。

那么当固定 $k$ 时，答案：

$$ans = \sum_{i=1}^n \min(b_i \bmod k, k - b_i \bmod k)$$

至此，本题关键已经解决。

对于 `Easy Version` 我们只需 $O(\sqrt{b_n})$ 枚举 $k$，对所有情况取 $\min$ 即可。

而对于 `Hard Version` 需要观察到，所有的合数 $k$ 都是没有必要的，将其替换成其最小质因子答案不会变劣。于是我们只需枚举 $b_n$ 的质因子即可。

参考实现：

```cpp
#include <bits/stdc++.h>
#define int long long 

using namespace std;

using int64 = long long;

const int inf = 5e18 + 10;

signed main () {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;

  cin >> n;

  vector<int> a(n + 1);
  int sum = 0;

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sum += a[i];
  }

  if (sum == 1) {
    cout << -1 << '\n';
    return 0;
  }

  int res = inf;
  vector<int> factor;

  factor.emplace_back(sum);
  for (int i = 2; i * i <= sum; ++i) {
    if (sum % i == 0) {
      factor.emplace_back(i);
      while (sum % i == 0) {
        sum /= i;
      }
    }
  }
  if (sum > 1) {
    factor.emplace_back(sum);
  }

  auto calc = [&](int x) -> int{
    vector<int> b(n + 1);
    int res = 0;

    for (int i = 1; i <= n; ++i) {
      b[i] = b[i - 1] + a[i] % x;
      b[i] %= x;
      res += min(b[i], x - b[i]);
    }

    return res;
  };

  for (int x : factor) {
    res = min(res, calc(x));
  }

  cout << (res == inf ? -1 : res) << '\n';
}
```


---

## 作者：Saber_Master (赞：0)

## 传送门

[CF1254B1 Send Boxes to Alice (Easy Version)](https://www.luogu.com.cn/problem/CF1254B1)


挺容易的一道题吧.这题就是给你$n$个盒子,第$i$个盒子里有至多一个球,每次可以选择一个非空盒子并将其中一个球移动到相邻盒子里.问你至少要移动几次才能使得所有非空盒子球数量的最大公约数大于$1$.



------------
先判一下无解的情况吧，很简单，显然，如果你把所有的球塞一个盒子里，这个，那最大公约数就是总球数，如果此时还不大于$1$的话，那么无解.

对于有解的情况，设总球数为$sum$，那么对于结果的最大公约数$k$一定是$sum$的约数.假设合并完后第$i$个非空盒子的球数为$c_i \cdot k$,显然有$c_i=1$,因为根据贪心策略移动我们要尽量移动更少的求.所以$k$是$sum$的一个质因子.我们枚举$k$，然后把序列分成$\frac{sum}{k}$段，对于每一段求答案即可.

每一段的答案和很好求，就是维护最中间那个$1$，然后把旁边那些$1$尽量往中间靠就能得到最优策略了.

$O(n\cdot d(n))$，$d(n)$为$n$质因子个数.

核心代码:

```cpp
ll n;
ll num[N], sum;
ll pos, res, cnt, ans, l, r;

inline void solve(ll k){
	ans=0; cnt=0;
	if (k==2){
		for (R ll i=1; i<=n; i++){
			if (num[i]){
				++cnt;
				if (cnt&1) pos=i;
				else ans+=i-pos;
			}
		}
	}else {
		for (R ll i=1; i<=n; i++){
			if (num[i]){
				(++cnt)%=k;
				if ((cnt<<1)-1==k) pos=i;
				else if (cnt==1) l=i;
				else if (cnt==0){
					r=i;
					for (R ll j=l; j<=r; j++){
						if (num[j]) ans+=abs(j-pos);
					}
				}
			}
		}
	}
	chkmin(res, ans);
}

int main(){
	calc_prime();
	read(n);
	res=(1ull<<63)-1;
	for (R ll i=1; i<=n; i++) read(num[i]), sum+=num[i];
	if (sum<2) return puts("-1"), 0;
	for (R ll i=1; i<=tot; i++){
		if (sum%prime[i]==0) solve(prime[i]);
	}
	writeln(res);
}
```


---

## 作者：F_Mu (赞：0)

**题意**

有$n(1\leq n\leq 10^5)$个盒子，每个盒子有$a_i(0\leq a_i \leq 1)$个糖果，你每一次可以将第$i$个盒子里的糖果放到第$i-1$或$i+1$个盒子中（如果盒子存在）。最后要使每个盒子的糖果数量都整除$k(k>1)$（注意盒子可以为空），问最小操作数。

**分析**

$(1)$因为糖果是类似于平铺的形式，堆叠时，我们可以发现所有存在糖果的盒子中数量均为$k$。若存在一个盒子中有$2*k$个糖果，在平铺到堆叠的过程中，将另外$k$个糖果分在更近的盒子能得到更小的答案。

$(2)$设糖果总数为$cnt$，所有存在糖果的盒子数量均为$k$，我们又可以发现，最小的操作是将$1$\~$k$、$k+1$\~$2k$、……、$i*k+1$\~$(i+1)*k$放在一起，即将相邻的$k$个放在一堆。

$(3)$对于某$k$个糖果，需要找到一个盒子，这个盒子到这$k$个糖果的距离最小(~~kNN算法~~)。我们将糖果看成数轴上的点，运用高一的绝对值知识（我忘了，我向高中数学老师谢罪）。

+ 若$k$为奇数，则将该盒子设置为最中间糖果所在的盒子
+ 若$k$为偶数，则将该盒子设置为最中间两个糖果中任意一个所在的盒子

即对于$i*k+1$\~$(i+1)*k$来说，第$k-i/2$个盒子，设其坐标为$ave$。

$(4)$为降低时间复杂度，我们采取前缀的思想，$sum[i]$表示坐标$i$之前的糖果的坐标总和（没糖果的盒子不加），$num[i]$表示坐标$i$之前有多少糖果。

$(5)$枚举可以被$cnt$整除的$k$，模拟$(2)$的过程，设$first$为第$i*k+1$个糖果的坐标，$last$为第$(i+1)*k$个糖果的坐标，那么每个循环都得加上$(num[ave] - num[first - 1])*ave-(sum[ave] - sum[first - 1])+(sum[last] - sum[ave])-(num[last] - num[ave])*ave$，意思为$ave$之前的操作次数加上$ave$之后的操作次数，最后取最小值

$(6)$记得开$long\ long$，$INF$也记得开大一点。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define LL long long
#define pii pair<int,int>
#define int ll
using namespace std;
const int maxn = (ll) 1e5 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f3f3f3f3f;
int a[maxn];
int cnt = 0;
int sum[maxn];
int num[maxn];

signed main() {
    start;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        num[i] = num[i - 1] + x;//前缀数量
        if (x) {
            a[++cnt] = i;
            sum[i] = i;
        }
    }
    for (int i = 1; i <= n; ++i)//前缀坐标和
        sum[i] += sum[i - 1];
    int ans = inf;
    for (int i = 2; i <= cnt; ++i) {
        if (cnt % i == 0) {
            int tmp = 0;
            for (int k = i; k <= cnt; k += i) {//k为最后的糖果
                int first = a[k - i + 1];
                int last = a[k];
                int ave = a[k - i / 2];
                int num1 = num[ave] - num[first - 1];
                int num2 = num[last] - num[ave];
                int tot1 = sum[ave] - sum[first - 1];
                int tot2 = sum[last] - sum[ave];
                int t = num1 * ave - tot1 + tot2 - num2 * ave;
                tmp += t;
            }
            ans = min(ans, tmp);
        }
    }
    if (ans == inf)
        cout << -1;
    else
        cout << ans;
    return 0;
}
```



---

