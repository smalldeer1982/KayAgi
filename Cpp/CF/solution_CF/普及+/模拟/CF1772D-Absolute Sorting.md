# Absolute Sorting

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. The array is sorted if $ a_1 \le a_2 \le \dots \le a_n $ .

You want to make the array $ a $ sorted by applying the following operation exactly once:

- choose an integer $ x $ , then for every $ i \in [1, n] $ , replace $ a_i $ by $ |a_i - x| $ .

Find any value of $ x $ that will make the array sorted, or report that there is no such value.

## 说明/提示

In the first test case, after using $ x = 4 $ , the array becomes $ [1, 1, 1, 1, 1] $ .

In the third test case, after using $ x = 0 $ , the array becomes $ [1, 2, 3, 4, 5, 6, 7, 8] $ .

In the fourth test case, after using $ x = 42 $ , the array becomes $ [32, 37, 38, 39, 40, 41] $ .

## 样例 #1

### 输入

```
8
5
5 3 3 3 5
4
5 3 4 5
8
1 2 3 4 5 6 7 8
6
10 5 4 3 2 1
3
3 3 1
3
42 43 42
2
100000000 99999999
6
29613295 52036613 75100585 78027446 81409090 73215```

### 输出

```
4
-1
0
42
2
-1
100000000
40741153```

# 题解

## 作者：Composite_Function (赞：13)

数学结论水题一道

------------

$$\text{思路}$$

对于 $1 \le i < n$，有 $|x - a_i| \le |x - a_{i+1}|$。

两边平方，得到 $x^2 - 2xa_i + a_i^2 \le x ^ 2 - 2xa _ {i + 1} + a _ {i + 1}^2$

$2(a _ {i + 1} - a_i)x \le (a_{i + 1} - a _ i)(a_{i + 1} + a _ i)$

- $a_i < a_{i + 1} ~~ x \le \dfrac{a_{i + 1} + a _ i}{2}$
- $a_i = a_{i + 1} ~~ x$ 取任意整数
- $a_i > a_{i + 1} ~~ x \ge \dfrac{a_{i + 1} + a _ i}{2}$

最后取个交集即可

------------

```
l = 0, r = 4e18;
for (int i = 1; i < n; ++i) {
	if (a[i] < a[i + 1]) r = min(r, (a[i] + a[i + 1]) / 2);
	if (a[i] > a[i + 1]) l = max(l, (a[i] + a[i + 1] + 1) / 2);
}
if (l <= r) cout << l << endl;
else cout << -1 << endl;
```

完结撒花

---

## 作者：loser_seele (赞：6)

观察相邻两项会对答案造成什么影响。

不难发现，如果 $ a_i > a_{i-1} $，则 $ x $ 必须至少为 $ \lceil \frac{a_i+a_{i-1}}{2} \rceil $，否则将 $ a_i,a_{i-1} $ 分别修改后一定不满足条件。

同理，如果 $ a_i < a_{i-1} $，则 $ x $ 至多为 $ \lfloor \frac{a_i+a_{i-1}}{2} \rfloor $，理由同上。

事实上我们讨论了方程 $ \mid a_i-x \mid = \mid a_{i-1} -x \mid $ 的解，设其中较大的为 $ a $，较小的为 $ b $，则 $ 2\times x=a-b $，分类讨论即可。

实现上，维护两个值 $ l,r $，当 $ a_i > a_{i-1} $ 的时候令 $ l=\max\{l, \lceil \frac{a_i+a_{i-1}}{2} \rceil\} $，否则令 $ r=\min \{r,  \lfloor \frac{a_i+a_{i-1}}{2} \rfloor \} $，最后如果 $ l>r $ 则显然无解，否则答案一定在 $ [l,r] $ 之间，输出 $ l $ 即可。

时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
		int l=0,r=2e9;
		bool flag=0;
		for(int i=1;i<n;i++)
		{
			if(a[i]>a[i+1])
				l=max(l,(a[i]+a[i+1]+1)/2);
			if(a[i]<a[i+1])
				r=min(r,(a[i]+a[i+1])/2);
		}
		if(l>r) 
		puts("-1");
		else 
		cout<<l<<endl; 
	}
}
```


---

## 作者：FQR_ (赞：4)

## 思路

题目中提到，操作后的序列要满足 $a_i \le a_{i+1}$。所以，我们只需要比较相邻的两个数字即可。

当 $a_i = a_{i+1}$ 时，无论 $x$ 取何值，都可以满足 $a_i \le a_{i+1}$。所以 $x$ 的取值范围是 $0 \le x < +\infty$。

当 $a_i<a_{i+1}$ 时，要使 $|a_i - x| \le |a_{i+1}-x|$，$x$ 的取值范围为 $0 \le x \le \frac{\lfloor a_i+a_{i+1} \rfloor}{2}$。

当 $a_i>a_{i+1}$ 时，要使 $|a_i - x| \le |a_{i+1}-x|$，$x$ 的取值范围为 $\frac{\lceil a_i+a_{i+1} \rceil}{2} \le x < +\infty$。

遍历所有相邻的数字，计算 $x$ 的每一个取值范围。如果有公共部分，则输出公共部分中任意一个数字即可。如果没有公共部分，则输出 $-1$。

时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
void solve()
{
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int l=0,r=1e9;
	for(int i=1;i<n;i++)
	{
		int ll,rr;
		if(a[i]==a[i+1]) continue;
		if(a[i]<a[i+1]) ll=0,rr=(a[i]+a[i+1])/2;
		else if(a[i]>a[i+1]) rr=1e9,ll=(a[i]+a[i+1]+1)/2;
		if(rr<l||r<ll){cout<<-1<<endl;return;}
		l=max(l,ll);r=min(r,rr);
	}
	cout<<l<<endl;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0; 
}
```

---

## 作者：tallnut (赞：3)

建议降黄。
# 思路
采用**维护交集**的方式。我们研究所有相邻两项的大小关系：
- $a_i<a_{i+1}$：初始就是小于的，因此 $x=0$ 即可满足要求；至于最大值，如果 $x=\lfloor(a_i+a_{i+1})\div 2\rfloor$ 还能勉强满足要求，再往后就不行了。本人太弱证不出来，可以手玩几组数据发现结论。
- $a_i=a_{i+1}$：初始就相等，无论怎么办都还是相等。
- $a_i>a_{i+1}$：初始小于，至少需要 $\lceil(a_i+a_{i+1})\div 2\rceil$ 才行，最大就大到哪里都可以。

每次对当前可用的最值和本次的最值求交集，最后判断一下这个交集是否不存在，如果存在就随意输出集合内的任意数字。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/147143139)。
```
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
int t,n;
bool flag;
int a[N];
struct range
{
	int l;
	int r;
} ok,tmp;
void qiujiaoji(const range& a,const range& b)
{
	range ans;
	ans.l = max(a.l,b.l);
	ans.r = min(a.r,b.r);
	if (ans.l > ans.r) flag = false;
	else ok = ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1;i <= n;i++)
			cin >> a[i];
		ok.l = 0;
		ok.r = 1e9;
		flag = true;
		//���μ������Ԫ��
		for (int i = 1;i < n;i++)
		{
			if (a[i] < a[i + 1])
			{
				tmp.l = 0;
				tmp.r = ((a[i] + a[i + 1]) >> 1);
			}
			else if (a[i] == a[i + 1])
			{
				tmp.l = 0;
				tmp.r = 1e9;
			}
			else
			{
				tmp.l = (a[i] + a[i + 1] + 1) >> 1;
				tmp.r = 1e9;
			}
			qiujiaoji(ok,tmp);
			if (flag == false) break;
		}
		if (flag) cout << ok.l << '\n';
		else cout << "-1\n";
	}
} 
```

---

## 作者：2huk (赞：3)

# CF1772D

## Description

给定一个长度为 $n$ 的序列 $a$，找到一个 $x$，使得 $b_i = |a_i - x|$，且 $b_i$ 单调递增。

## Solution

单调递增的要求为 $|a_i - x| \le |a_{i + 1} - x|$，那么当每个 $a_i$ 和 $a_{i + 1}$ 都满足这个条件时，就说明找到了正确的 $x$。那么我们只需要对于每两个相邻的 $a_i$ 和 $a_{i + 1}$ 求出合法的所有的 $x$，再把全部的取交集即可。

令 $a_i = p$，$a_{i + 1} = q$，那么我们现在要找的为 $|p - x| \le |q - x|$ 的 $x$ 的所有可能，或者说找到 $x$ 的可能的范围 $[l, r]$。

如果 $p = q$，则 $x$ 的范围显然为 $[-\infty, +\infty]$。否则我们对式子 $|p - x| \le |q - x|$ 进行处理：

将两边同时平方，得：
$$
|p-x|^2 \le |q-x|^2 \Longleftrightarrow p^2 + x^2 - 2px \le q^2 + x^2 - 2qx
$$
两边同时 $-x^2$，得：
$$
p^2 - 2px \le q^2 - 2qx \Longleftrightarrow p^2 - q^2 \le 2x(p - q) \Longleftrightarrow (p - q)(p + q) \le 2x(p - q)
$$

---

此时，若 $p - q > 0$，即 $p > q$，那么将两边同时消掉 $(p - q)$ 后，得到
$$
p + q \le 2x \Longleftrightarrow x \ge \left\lceil\dfrac{p + q}2\right\rceil
$$


所以当 $p > q$ 时 $x \in \left[ \left\lceil\dfrac{p + q}2\right\rceil, +\infty \right)$。

---

否则，若 $p - q < 0$，即 $p < q$，由于这个值是负数，所以将两边同时消掉 $(p - q)$ 后小于等于变成了大于等于，即：
$$
p + q \ge 2x \Longleftrightarrow x \le \left\lfloor\dfrac{p + q}2\right\rfloor
$$
所以当 $p < q$ 时 $x \in \left(-\infty,  \left\lfloor\dfrac{p + q}2\right\rfloor \right]$。

---

在每个可能的 $x$ 之间取交集即可。

## Code

取交集可以维护左右端点 $l, r$，表示当前的 $x$ 应该在 $[l, r]$ 范围内，每次将 $l, r$ 向中间移动（尝试将 $l$ 变大，$r$ 变小），如果最后 $r > l$ 表示不存在答案，否则输出 $l \sim r$ 中的任意一点即可。

注意算 $\left\lceil\dfrac{p + q}2\right\rceil$ 时可以写成 $\left\lfloor\dfrac{p + q + 1}2\right\rfloor$。

```cpp
int T, n, a[N];

int Solve()
{
	n = read();
	
	fup (i, 1, n)
		a[i] = read();
	
	int l = 0, r = INF;
	fup (i, 1, n - 1)
		if (a[i] < a[i + 1]) r = min(r, (a[i] + a[i + 1]) / 2);
		else if (a[i] > a[i + 1]) l = max(l, (a[i] + a[i + 1] + 1) / 2);
	
	if (l <= r) return l;		// 可以取 l ~ r 中的任意一点
	return -1;
}
```

---

## 作者：GenesisCrystal (赞：1)

一道挺好的数学题。

## Solution

尝试暴力拆解式子。

由题可知，若有一个 $x$，则有 $|a_i-x|\le|a_{i+1}-x|$。

$$ \because |a_i-x|\le|a_{i+1}-x| $$
$$ \therefore (a_i-x)^2\le(a_{i+1}-x)^2 $$
$$ \therefore a_{i}^2-2\cdot a_i\cdot x+x^2\le a_{i+1}^2-2\cdot a_{i+1}\cdot x+x^2$$
$$ \therefore a_{i}^2-2\cdot a_i\cdot x\le a_{i+1}^2-2\cdot a_{i+1}\cdot x $$
$$ \therefore a_{i}^2-a_{i+1}^2 \le 2\cdot a_{i}\cdot x-2\cdot a_{i+1}\cdot x $$
$$ \therefore (a_i - a_{i+1})\cdot(a_i + a_{i+1})\le 2 \cdot x \cdot (a_{i}-a_{i+1}) $$

考虑到不等式同乘或除要变号，所以分类讨论。

此时两边同除以 $a_i-a_{i+1}$。

### 1. $a_i > a_{i+1}$

$$ \therefore a_i+a_{i+1}\le2\cdot x $$
此时 $ x \ge \big \lfloor\dfrac{a_i+a_{i+1}}{2} \big \rfloor $。

用一个 $maxl$ 来存下这种情况最大的 $\big \lfloor\dfrac{a_i+a_{i+1}}{2} \big \rfloor$。

### 2. $a_i \le a_{i+1}$

此时要变号。

$$ \therefore a_i+a_{i+1}\ge2\cdot x $$
此时 $ x \le \big \lfloor\dfrac{a_i+a_{i+1}}{2} \big \rfloor $。

用一个 $minr$ 来存下这种情况最小的 $\big \lfloor\dfrac{a_i+a_{i+1}}{2} \big \rfloor$。

---

最后，用 $minr$ 再检验一遍就行了。

## Code

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int kMaxN = 2e5 + 1;

int t, n;
ll a[kMaxN];

int main() {
  for (cin >> t; t; t--) {
    cin >> n;
    vector<ll> u, o;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    ll maxl = 1e9, minr = -1e9;
    for (int i = 1; i < n; i++) {
      if (a[i] == a[i + 1]) {
        continue;
      }
      if (a[i] <= a[i + 1]) {
        maxl = min(maxl, (a[i] + a[i + 1]) / 2);
      } else {
        minr = max(minr, (a[i] + a[i + 1]) / 2);
      }
    }
    bool f = (minr <= maxl);
    if (f) {
      for (int i = 1; i <= n; i++) {
        u.push_back(abs(a[i] - maxl));
      }
      o = u;
      sort(u.begin(), u.end());
      f = u == o;
    }
    cout << (f ? maxl : -1) << '\n';
  }
  return 0;
}
```

---

## 作者：liuyi0905 (赞：0)

其实本题我们只需看每相邻两组数据  $a_i,a_{i+1}$，就可维护变量 $l$ 和 $r$ 表示答案的最小值和最大值，若 $a_i>a_{i+1}$，则 $l$ 更新为 $\max(l,\lceil a_i+a_{i+1}\rceil)$，若 $a_i<a_{i+1}$，则将变量 $r$ 更新为 $\min(r,\lfloor a_i+a_{i+1}\rfloor)$，所以最终答案一定在 $[l,r]$ 里，若 $l>r$ 则无解，否则取 $[l,r]$ 中任意一个数输出即可。

代码就很好写啦，412B 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n,a[N];
int main(){
    for(cin>>t;t;t--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        int l=0,r=1e18;
        for(int i=1;i<n;i++){
            a[i]>a[i+1]&&(l=max(l,(a[i]+a[i+1]+1)/2));
            a[i]<a[i+1]&&(r=min(r,(a[i]+a[i+1])/2));
        }
        cout<<(l<=r?l:-1)<<"\n"; 
    }
    return 0;
}
```

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1772D) & [CF 传送门](//codeforces.com/problemset/problem/1772/D)
# 思路
我们其实只要看每组相邻两数 $a_{i-1}$ 和 $a_i$ 即可。我们定义两个变量 $l$ 和 $r$，分别表示答案的最小可能值和最大可能值。如果 $a_{i-1}>a_i$，则当前 $l$ 更新为 $\max(l,\lceil\frac{a_{i-1}-a_i}2\rceil)$；如果 $a_i>a_{i-1}$，则当前 $r$ 更新为 $\min(r,\lfloor\frac{a_i-a_{i-1}}2\rfloor)$。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, l, r, a[200005];
int main () {
	cin >> t;
	while (t --) {
		cin >> n;
		l = 0, r = 1e9; //多组数据要清空
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		for (int i = 1; i < n; ++ i)
			if (a[i - 1] > a[i])
				l = max (l, a[i] + a[i - 1] + 1 >> 1);
			else if (a[i] > a[i - 1])
				r = min (r, a[i - 1] + a[i] >> 1);
		cout << (l > r ? -1 : l) << '\n';
	}
	return 0;
}
```

---

## 作者：xzy090626 (赞：0)

## CF1772D 题解
分讨好题。

我们观察题目发现，要使 $a$ 单调不递减，只要对于所有的 $i\in [1,n)$，满足 $a_i\le a_{i+1}$ 即可。那么我们就只需要相邻元素的大小关系即可。

手玩几组数对可以知道，对于每一组数对 $(a,b)$，如果
- $a>b$，那么为了使得 $|a-x|\le|b-x|$，必须使得 $x\ge \lceil{(a+b)\over 2}\rceil$；

- $a<b$，则 $x\le \lfloor{(a+b)\over 2}\rfloor$；

- $a=b$，则 $x$ 可以为任何数。

于是我们可以维护一个区间 $[l,r]$，然后每次缩短合法区间，最后判断区间是否为空，如果区间非空，那么输出 $l$ 即可，否则输出 $-1$。

代码放在这里。
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
#define pb push_back
using namespace std;
const int N = 1e6 + 7;
const int mod = 1e9 + 7;
int s[N];
int n,k;
void solve(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>s[i];
    if(is_sorted(s+1,s+n+1)){
        cout << 0 << endl;
        return;
    }
	int l = 0,r = 2e9;
	for(int i=1;i<n;++i){
		if(s[i]<s[i+1]){
			r = min(r,(s[i]+s[i+1])/2);
		}
		if(s[i]>s[i+1]){
			l = max(l,(s[i]+s[i+1]+1)/2);
		}
	}
	if(l>r) cout<<"-1\n";
	else cout<<l<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：sto_Micnation_orz (赞：0)

基本思路：考虑相邻两个数之间的答案集合，然后每个区间的重复区域即可。

- 对于 $a_i = a_{i + 1}(1 \le i < n)$，则可以使这两个数满足条件的答案区间为 $[0, +\infty)$。
- 对于 $a_i < a_{i + 1}(1 \le i < n)$，则可以使这两个数满足条件的答案区间为 $[0, \lfloor\dfrac{ a_i + a_{i + 1}}{2}]\rfloor$。
- 对于 $a_i > a_{i + 1}(1 \le i < n)$，则可以使这两个数满足条件的答案区间为 $[\lceil\dfrac{ a_i + a_{i + 1}}{2}\rceil, +\infty)$。

注意这上面的第二点是向下取整，第三点是向上取整。

最后，对这些区间取并集，若最后的区间 $l > r$，则无解，否则输出 $[l, r]$ 中的任意一个数即可。

完整代码：

```cpp
#include <iostream>

using namespace std;

const int N = 200010;
const int INF = 1e9;

int T;
int a[N];
pair<int, int> p[N];

int main() {
    cin >> T;
    while (T--) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        int tot = 0;
        for (int i = 1; i < n; i++) {
            int x = a[i], y = a[i + 1];
            if (x == y) p[++tot] = make_pair(0, INF);
            else if (x < y) p[++tot] = make_pair(0, (x + y) / 2);
            else p[++tot] = make_pair((x + y + 1) / 2, INF);
        }
        int l = p[1].first, r = p[1].second;
        for (int i = 2; i <= tot; i++) l = max(l, p[i].first), r = min(r, p[i].second);
        if (l > r) puts("-1");
        else cout << l << "\n";
    }
    return 0;
}
```

---

