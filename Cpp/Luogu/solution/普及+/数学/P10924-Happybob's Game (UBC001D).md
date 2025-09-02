# Happybob's Game (UBC001D)

## 题目描述

**注：本题中所有 $i,j$ 均默认 $1\le i,j\le n$ 且 $i\not = j$。**

Happybob 的游戏角色正在进行战争。

他有 $n$ 个部队，每个部队有 $a_i$ 个人，并且有消耗值 $m_i$，表示每过 $1$ 分钟第 $i$ 个部队的人会变成 $⌊\frac{a_i}{m_i}⌋$，一旦其中一支部队人数变成 $0$，Happybob 就失败了。设一开始为第 $0$ 分钟，定义存活时间为 Happybob 的其中一支部队人数变成 $0$ 的上一分钟。**可参考样例解释。**

但是 Happybob 不甘就这样就被消灭，他想到了好办法：他可以在**任意不是整数分钟**的时间将一个部队的人调一部分到另一个部队。形式化来说，取两支军队 $a_i, a_j$ 以及一个调换人数 $x$ 满足 $1\le x\le a_i$，使 $a_i,a_j$ 分别变成 $a_i-x,a_j+x$。注意，在两个整数分钟间，他可以调换任意多次。

Happybob 发现，这样可以有效地提升部队存活时间。现在你作为 Happybob 最信任的参谋长，你可以帮他调兵遣将。

接下来给你 $q$ 次操作，每次操作是以下操作中的一个：

- 操作 $1$，形如 `1 i x`，表示 Happybob 的第 $i$ 支部队的人数 $a_i$ 变成了 $x$ （$1\le x\le 10^9$）。
- 操作 $2$，形如 `2 i x`，表示 Happybob 的第 $i$ 支部队的消耗值 $m_i$ 变成了 $x$（$1\le x\le 10^6$）。
- 操作 $3$，形如 `3`，表示让你输出 Happybob 理论上通过上述调兵遣将法最久的存活时间。注意，此操作**不会**改变 $a_i$ 或 $m_i$ 的值。


## 说明/提示

### 样例说明

对于第一个操作 $3$，Happybob 可以这样调动军队：

| 时刻（分） | 第一支军队人数 | 第二支军队人数 |
| :----------: | :----------: | :----------: |
| $0$ | $29$ | $3$ |
| $0.5$ | $10$ | $22$ |
| $1$ | $3$ | $11$ |
| $1.5$ | $6$ | $8$ |
| $2$ | $2$ | $4$ |
| $2.5$ | $3$ | $3$ |
| $3$ | $1$ | $1$ |
| $3.5$ | $1$ | $1$ |
| $4$ | $0$ | $0$ |


### 数据范围

对于 $100\%$ 的数据，$1\le n \le 5\times 10^6$，$1\le q \le 10^5$。保证对于所有 $a_i,m_i$，$1\le a_i\le 10^9$，$1\le m_i\le 10^6$。



## 样例 #1

### 输入

```
2 10
29 5
7 2
1 2 3
2 1 3
3
1 1 1
1 2 1
2 1 1
2 2 1
3
2 1 2
3```

### 输出

```
3
-1
0```

# 题解

## 作者：cosf (赞：2)

## [「UOI」Beginner Contest 001 & Round 3](https://www.luogu.com.cn/contest/101609) [Happybob's Game](https://www.luogu.com.cn/problem/T317317)

首先先说一下这一道题的数据范围。

$1 \le n \le 5 \times 10^6$，$O(n\log n)$ 会比较吃力，故这题是常数比较大的 $O(n)$。

$1 \le q \le 10^5$，显然大约是 $O(q\log n)$ 这个量级的。

故我的做法复杂度是 $O(n + q(1 + \log n + \log sum))$（$1, \log n, \log sum$ 分别对应操作 $1, 2, 3$）。

---

## 思路

我们先考虑操作 $3$。

如果只有操作 $3$，则相当于 $a_i$ 和 $m_i$ 是定值。原来的题是这样的，不过太水，所以加了询问。

我们要求 $a_i$ 在以 $m_i$ 为分母时的能存活的天数，相当于求以 $m_i$ 为分母过多少天至少需要的人数为 $\sum a_i = sum$。

换句话说，就是求能活 $k$ 天的最少军队人数。令其为 $d_k$。若存在一 $k$ 使得 $d_{k - 1} \le sum \lt d_k$，则 $k-1$ 就是所求的答案。

因为每分钟都可以任意地调换军队的人，所以 $a_i$ 的具体内容是不重要的，只需记录它的和，令设 $1 \le m_1 \le \dots \le m_n$。

显然 $\{d_k\}$ 存在递推关系，$d_1 = \sum m_i$。

那么，$d_{k+1} = \sum_{i=1}^n m_id_{k,i}$，其中 $d_{k, i}$ 为和为 $d_k$ 的正整数列。

容易证明，$d_{k, 2} = d_{k, 3} = \dots = d_{k, n} = 1, d_{k, 1} = d_k - n + 1$ 时 $d_{k + 1}$ 取到最小值 $m_1(d_k - n + 1) + (\sum_{i=1}^n m_i - m_1) = m_1(d_k - n) + \sum_{i=1}^n m_i$。

那么，我们可以得出 $\{d_k\}$ 的通项公式：

$$
d_k = nm_1^k + \frac{m_1^k - 1}{m_1 - 1}(\sum_{i=1}^n m_i - m_1)
$$

显然，当 $m_1 \gt 1$ 时这是个（快于）指数级增长的数列，故时间复杂度 $\gt O(\log_{m_1}sum) \ge O(\log sum)$。可以优化到 $O(\log\log sum)$，不过没必要。

当 $m_1 = 1$ 时可以直接解一元一次方程，复杂度为 $O(1)$。

至此，操作 $3$ 已经考虑完毕。

显然（又是显然），操作 $1$ 只需要简单地维护一下 $a_i$ 的值（修改需要记录差）和 $sum$ 就可以了。

而操作 $2$ 则需要用一些特殊的数据结构维护最小值（达到 $O(1)$ 插入和算 `min`）。

这可以用配对堆等数据结构完成。`set` 维护前 $q$ 大也可行，也可以过，也好写，但比我这个慢一点。

最后，参考代码：

## [AC Code](https://hydro.ac/d/uoi233/record/645f7123e3f1072df0b1db0c)

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;
inline long long read() {} // 快读
template <typename T = int, typename C = less<int>, int S = 1000006> class Heap {}; // 堆

long long as;
long long a[5000006];
Heap<int, less<int>, 5000006> mt; // 堆
long long sm;

int main()
{
    int n = read(), q = read();
    for (int i = 1; i <= n; i++)
    {
        as += a[i] = read();
    }
    long long mi;
    for (int i = 1; i <= n; i++)
    {
        mi = read();
        mt.push(mi);
        sm += mi;
    }
    while (q--)
    {
        int op = read(), i, x;
        if (op == 1)
        {
            i = read();
            x = read();
            as = as - a[i] + x;
            a[i] = x;
        }
        else if (op == 2)
        {
            i = read();
            x = read();
            sm = sm - mt.dts[i]->a + x;
            mt.modify(mt.dts[i], x);
        }
        else if (op == 3) // 注意递推的公式
        {
            long long mm = mt.top();
            long long ca = as;
            if (sm == n)
            {
                if (ca >= n)
                    cout << -1 << endl;
                continue;
                cout << 0 << endl;
            }
            else if (mm == 1)
            {
                ca -= n;
                ca /= (sm - n);
                cout << ca << endl;
                continue;
            }
            long long mc = -1;
            long long cur = n;
            while (cur <= ca)
            {
                mc++;
                cur = cur * mm + sm - mm * n;
            }
            cout << mc << endl;
        }
    }
    return 0;
}
```

运行时间和空间：$\textsf{350ms, 300MiB}$。

---

## 作者：sbno333 (赞：1)

我们考虑操作 $3$ 贪心，发现因为可以随时调度，所以只关心 $\sum a_i$。

然后我们要让每次清剿后 $\sum a_i$ 最大，我们为了都能活，所以第 $i$ 个位置要放 $m_i$，剩下的兵都放到 $m_i$ 最小的位置。

我们发现只需要维护 $\sum m_i$，和 $\min m_i$。

考虑推式子，记 $\sum a_i$ 为 $s$。

于是乎我们要再除了 $\min m_i$ 的位置都放 $m_i$，$\min m_i$ 的位置是 $s-\sum m_i+\min m_i$。

然后和变成 $s\gets\frac{s-\sum m_i+\min m_i}{\min m_i}+n-1$。

这个显然小于等于 $\frac{s}{\min s_i}$。

当 $\min s_i\not=1$ 时，暴力即可。

否则我们可以推式子，变成每一次减去一个数，答案和商有关。

然后为了能安排，需要保证 $s\ge\sum m_i$。

然后最小 $m_i$ 优先队列维护即可，和直接变量维护即可。

这道题输入量大，记得稍微卡一卡常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int a[5000009];
int m[5000009];
int f[49];
int me[49];
int z;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > qq;
inline void _main(){
	z=0;
	int n,q;
	cin>>n>>q;
	int sum,um;
	sum=um=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>m[i];
		z+=(m[i]==1);
		um+=m[i];
		qq.push({m[i],i});
	}
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x,y;
			cin>>x>>y;
			sum-=a[x];
			a[x]=y;
			sum+=a[x];
		}else if(op==2){
			int x,y;
			cin>>x>>y;
			z-=(m[x]==1);
			um-=m[x];
			while(qq.top().second==x){
				qq.pop();
			}
			m[x]=y;
			z+=(m[x]==1);
			um+=m[x];
			qq.push({m[x],x});
		}else{
			if(z==n){
				cout<<-1<<endl;
				continue;
			}
			if(z>=1){
				cout<<max((sum-um-1)/(um-n)+1,0ll)<<endl;
				continue;
			}
			int ans;
			ans=-1;
			int mm;
			mm=sum;
			int c;
			c=qq.top().first;
			while(mm){
				ans++;
				
				if(mm<um){
					break;
				
				}mm=(mm-um+c)/c+n-1;
			}
			cout<<ans<<"\n";
		}
	}
}
signed main(){
    std::ios::sync_with_stdio(0);
	int t;
	//cin>>t;
	t=1;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：modfish_ (赞：1)

## 思路
对于同样的 $x$。若 $m_i>m_j$，则 $\lfloor\frac{x}{m_i}\rfloor<\lfloor\frac{x}{m_j}\rfloor$，所以 $m$ 越大，这个部队里单次损失的人数就越多。由此不难想出一个贪心策略：将大部分的人都集中在 $m$ 最小的部队里，剩余的部队都只留恰好 $m_i$ 个人，以保证人数不会减为 $0$。

于是只要维护 $a_i$ 的和、$m_i$ 的和 以及 $m_i$ 的最小值即可。

如何统计答案呢？当 $\min_{i=1}^nm_i>1$ 时，每次人数都要除掉一个至少为 $2$ 的数，直接暴力模拟即可，复杂度 $O(\log V)$。

当 $min_{i=1}^nm_i=1$ 时，每次都相当于减去一个 $\sum_{i=1}^nm_i-n$（因为每一个数除过一轮都会变成 $1$，即减少 $m_i-1$。最小的 $m$ 是 $1$，所以除以 $1$ 也相当于减去 $1-1$），所以，经过

$$\lfloor\frac{\sum_{i=1}^na_i-\sum_{i=1}^nm_i}{\sum_{i=1}^nm_i-n}\rfloor$$

轮后，$a_i$ 的总和就小于 $2\sum_{i=1}^nm_i$ 了。再除一轮后，必定无法使得每个部队的人数都大于等于 $m_i$，于是游戏结束。答案为：

$$\lfloor\frac{\sum_{i=1}^na_i-\sum_{i=1}^nm_i}{\sum_{i=1}^nm_i-n}\rfloor+1$$

总时间复杂度 $O(q(\log n+\log V))$（那个 $\log n$ 是因为我太菜了，实在想不到除了线段树怎么维护全局最小）。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 5e6 + 5;

ll a[maxn], m[maxn];

namespace seg{
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
ll min1[maxn << 2];
void build(int x, int l, int r){
	if(l == r){
		min1[x] = m[l];
		return;
	}
	int mid = l + r >> 1;
	build(l(x), l, mid), build(r(x), mid + 1, r);
	min1[x] = min(min1[l(x)], min1[r(x)]);
}
void update(int x, int l, int r, int id, ll k){
	if(l == r){
		min1[x] = k;
		return;
	}
	int mid = l + r >> 1;
	if(id <= mid) update(l(x), l, mid, id, k);
	else update(r(x), mid + 1, r, id, k);
	min1[x] = min(min1[l(x)], min1[r(x)]);
}}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	ll suma = 0, summ = 0;
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]), suma += a[i];
	for(int i = 1; i <= n; i ++) scanf("%lld", &m[i]), summ += m[i];
	seg::build(1, 1, n);
	while(q --){
		int op, x;
		ll k;
		scanf("%d", &op);
		if(op == 1){
			scanf("%d %lld", &x, &k);
			suma += k - a[x], a[x] = k;
		}else if(op == 2){
			scanf("%d %lld", &x, &k);
			summ += k - m[x], m[x] = k, seg::update(1, 1, n, x, k);
		}else{
			if(seg::min1[1] == 1){
				if(summ == n) printf("-1\n");
				else printf("%lld\n", (suma - summ) / (summ - n) + 1);
			}else{
				ll x = suma, ans = 0;
				while(x >= summ){
					x -= summ - seg::min1[1];
					x /= seg::min1[1];
					x += 1ll * n - 1;
					ans ++;
				}
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
```
比赛结束后才仔细想了一下，发现这玩意比上一题好写多了……

---

