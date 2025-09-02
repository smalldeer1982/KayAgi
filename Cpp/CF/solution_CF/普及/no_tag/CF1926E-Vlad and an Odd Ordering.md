# Vlad and an Odd Ordering

## 题目描述

Vlad有 $n$ 张牌，编号为 $1,2,...,n$。他想把这些牌按如下方法排成一排：

- 首先，他把所有奇数牌从小到大依次铺开。

- 接着，他从小到大铺开所有奇数的 $2$ 倍（即 $2$ 乘以奇数）的牌。

- 接着，他从小到大铺开所有是奇数的 $3$ 倍（即 $3$ 乘以奇数）的牌。

- 接着，他从小到大铺开所有是奇数的 $4$ 倍（即 $4$ 乘以奇数）的牌。

- 依此类推，直到所有的牌都放完。

在这个过程中，他放下的第 $k$ 张牌是什么？

一旦Vlad放下一张牌，他就不能再用这张牌了。

## 样例 #1

### 输入

```
11
7 1
7 2
7 3
7 4
7 5
7 6
7 7
1 1
34 14
84 19
1000000000 1000000000```

### 输出

```
1
3
5
7
2
6
4
1
27
37
536870912```

# 题解

## 作者：RyanLi (赞：6)

传送门：洛谷 [Vlad and an Odd Ordering](https://www.luogu.com.cn/problem/CF1926E) | Codeforces [E. Vlad and an Odd Ordering](https://codeforces.com/contest/1926/problem/E)

更佳的阅读体验：[CF1926E 题解](https://blog.ryanli.top/index.php/archives/39/)

---

**简要题意**：有 $n$ 张牌，按照编号为奇数、二倍奇数、三倍奇数、四倍奇数……的顺序出牌，直到出完所有的牌。求出的第 $k$ 张牌是什么。

手模一下样例中 $n = 7$ 的情况，不难发现，我们令第 $i$ 轮出牌数量后剩下 $m_i$ 张牌，则可以得到第一轮出牌 $\left \lceil \tfrac{n}{2} \right \rceil$ 张，$m_1 = \left \lfloor \tfrac{n}{2} \right \rfloor$ ，第二轮出牌 $\left \lceil \tfrac{m_1}{2} \right \rceil$ 张，$m_2 = \left \lfloor \tfrac{m_1}{2} \right \rfloor$，以此类推。

因此，我们只需要一轮一轮地出牌，并给 $k$ 减去这一轮出牌的数量，直到 $k$ 不大于当前剩余的牌数。

| 出牌次数      | 这一轮的牌的编号   | 牌编号之间的差 |
| :------------ | :----------------- | :------------- |
| 第 $1$ 次出牌 | $1$、$3$、$5$、$7$ | $2$            |
| 第 $2$ 次出牌 | $2$、$6$           | $4$            |
| 第 $3$ 次出牌 | $4$                |                |

可以发现，第 $i$ 轮出的牌编号的差为 $2^i$，这一轮出的第一张牌的编号是 $2^{i - 1}$，因此在经过上面的处理后就可以得到第 $k$ 张牌了。

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int t;
ll n, k;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        cin >> n >> k;
        ll cnt = 1, tmp = n;
        while (k > (tmp + 1) >> 1) {
            k -= tmp + 1 >> 1;
            tmp >>= 1, cnt <<= 1;
        } cout << (k * cnt << 1) - cnt << '\n';
    } return 0;
}
```





---

## 作者：Eason_cyx (赞：1)

赛时就感觉有点板。

---

容易发现，很多操作是无法取出任何牌的。例如奇数倍的奇数操作，由于奇数 $\times$ 奇数一定等于奇数，所以这些牌一定已经被取过了。再比如，$6$ 倍的奇数，可以分解成 $3\times2\times$ 奇数，也就是 $2\times$ 奇数，所以这些牌也已经被取过了。

综上，根据手动模拟，只有 $2^x\times$ 奇数的操作才有可能取出牌。

那么，我们可以进行循环，枚举 $2^x$，累加取出牌的张数。如果这个张数 $\ge k$，那么跳出循环。这说明在当前的取牌过程中达到了 $k$ 张，所以一定是在 $2^{x-1}$ 倍的奇数这一次操作之后。然后就可以枚举出这一张牌了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int t; cin >> t;
	while(t--) {
		long long n,k; cin >> n >> k;
		long long x = n,cur = 2,y = 0;
		while(true) {
			if(cur == 0) {
				cout << "NO!!!";
				break;
			}
			if((x % cur) >= (cur/2)) {
				y += x / cur + 1;
			}
			if((x % cur) < (cur/2)) {
				y += x / cur;
			}
			if(y >= k) break;
			cur *= 2;
		}
		// cur /= 2;
		// long long qu = 0;
		// if(cur != 1) {
			// if((x % cur) >= (cur/2)) {
				// qu = x - (x / cur + 1); 
			// }
			// else qu = x - (x / cur);
		// }
		// long long cha = k - qu;
		if((x % cur) >= (cur/2)) {
			y -= x / cur + 1;
		}
		if((x % cur) < (cur/2)) {
			y -= x / cur;
		}
		long long cha = k - y;
		long long st = -cur;
		cur *= 2;
		for(int i = 1;i <= cha;i++) {
			st += cur;
		}
		cout << st / 2 << endl;
	}
	return 0;
}
```

黄吧。

---

## 作者：No_Rest (赞：1)

## 思路

发现只有放奇数的 $2^x$ 倍时才会真正放牌，因为只要放奇数的 $y$ 倍且 $y$ 有奇因子时，奇数的 $y$ 倍这些牌之前一定放过。

这样，我们令第 $i$ 轮为放 $2^{i - 1}$ 倍的那一轮。

显然，第一轮放的都是 $\bmod 2 = 1$ 的数，那么第二轮放的就是 $\bmod 4 = 1 \times 2$ 或 $3 \times 2$（因为第一轮放的数都是 $\bmod 4 = 1$ 或 $3$ 的）即 $\bmod 4 = 2$ 的数，这些数 $\bmod 8 = 2$ 或 $6$。那么，第三轮放的就都是 $\bmod 8 = 2 \times 2$ 或 $6 \times 2$ 即 $\bmod 8 = 4$ 的数。

可以发现，第 $i$ 轮放的都是首项为 $2^{i - 1}$，公差为 $2^i$ 的等差数列，一共有 $\lfloor \frac{n - 2^{i - 1}}{2^i}\rfloor$ 项。于是我们求一个前缀和 $sum_i = \sum^{i}_{j = 1} \lfloor \frac{n - 2^{j - 1}}{2^j}\rfloor$ 便可以愉快的二分啦。

若是知道第 $k$ 张是在第 $ans$ 轮放下的，那么可以算出答案就是 $2^{ans  - 1} + (k - sum_{ans - 1} - 1) \times 2^{ans}$。

一道数学加二分就这么结束了，时间复杂度 $\mathcal O(T \log n)$。

~~其实可以不二分，直接枚举的，这里做麻烦了。~~

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
ll t = read(), n, k, ans, sum[maxn], p2[maxn];
vector <ll> v[maxn];
map <ll, ll> mp;
void solve(){
	n = read(), k = read();
	for(ll i = 1; i <= 31; ++i) sum[i] = sum[i - 1] + (n + p2[i - 1]) / p2[i];//计算前缀和
	ll l = 1, r = 31, mid;
	while(l <= r){//二分，但是可以直接枚举，因为一共就 log n 项
		mid = (l + r) >> 1;
		if(sum[mid] >= k) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%lld\n", p2[ans - 1] + (k - sum[ans - 1] - 1) * p2[ans]);//输出
}
int main(){	
	p2[0] = 1;
	for(ll i = 1; i <= 31; ++i) p2[i] = p2[i - 1] + p2[i - 1];//预处理 2 的 n 次方
	for(; t; --t) solve(); 
    return 0;
}
```

---

## 作者：_Delete_ (赞：0)

## 思路

一眼找规律题。

不难发现，只有删除轮数是 $2$ 的幂次时，删除才能删到数。对于每轮有效删数，如果要删除数字在本次删除范围内，则通过每轮删除规律找出需求数字。

#### 每轮规律

第一轮删除的数都是奇数，第二轮删除的是奇数乘二，第四轮删除的是奇数乘四。由第一轮可得 $2×i-1$ 的规律，第二轮可得 $2×(2×i-1)$ 的规律。由此可得删除的第 $i$ 个数为 $t×(2×i-1)$ 的规律，其中 $t$ 是删除轮数，

## 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 


//function 
void solve(){
	int n,k;
	cin>>n>>k;
	int tmp=n;//剩余未删除数
	int i=1;//删除轮数
	while(tmp!=0){
		if(k<=((tmp-1)/2+1)){
			//如果本轮删除到第k个数
			cout<<i*(2*k-1)<<endl;
			break;
		}
		k-=(tmp-1)/2+1;
		//已删除的数要减去
		tmp-=(tmp-1)/2+1;
		i*=2;
	}
	
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	int T;
	cin>>T;
	while(T--)solve();
	
	return 0;
}


```



---

## 作者：minVan (赞：0)

**题目大意**

一个序列 $1,2,\cdots,n$，第 $p$ 轮操作取走所有奇数乘 $p$，求第 $k$ 个被取走的元素是多少。

**解题思路**

如果 $p=2^x\cdot q$（$q$ 为大于 $1$ 的奇数，$x\in\mathbb{N}$），那么任意奇数 $r$ 将变为 $pr=2^x\cdot qr$ 为 $2^x$ 乘上一个奇数，那么一定在 $p=2^x$ 时出现过了。

从而每次 $p$ 都变为 $2p$（初始为 $1$）才能保证所有该取走的数都没被取过。

令此时 $n=m$，则这一轮要取出 $\left\lceil\dfrac {m+1}2\right\rceil$ 个，然后 $n$ 变为 $\left\lceil\dfrac m2\right\rceil$。

最终结果为 $p\cdot(2k-1)$。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    int n, k, m = 0;
    cin >> n >> k;
    while(k > (n + 1) / 2) {
      k -= (n + 1) / 2;
      n >>= 1;
      ++m;
    }
    cout << ((k * 2 - 1) << m) << '\n';
  }
  return 0;
}
```

---

