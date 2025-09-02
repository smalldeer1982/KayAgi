# Candy Party (Easy Version)

## 题目描述

有 $n$ 个人，第 $i$ 个人有 $a_i$ 颗糖，在派对上，每个人 **会且仅会做下面的事情恰好一次** ：

- 选一个正整数 $p\ (\ 1 \leq p \leq n\ )$ 和一个非负整数 $x$ ，然后把 $2^x$ 颗糖给第 $p$ 个人。注意任意时刻一个人手上的糖不能变成负数，并且一个人不能把糖给自己。
  

你需要回答能否在上述操作后让每个人手中的糖果数量相同。

注意本题和 Hard Version 不同的是本题中每个人必须从他人处接受恰好一次糖果，给出恰好一次糖果。

## 样例 #1

### 输入

```
6
3
2 4 3
5
1 2 3 4 5
6
1 4 7 1 5 4
2
20092043 20092043
12
9 9 8 2 4 4 3 5 1 1 1 1
6
2 12 7 16 11 12```

### 输出

```
Yes
Yes
No
Yes
No
No```

# 题解

## 作者：Alex_Wei (赞：7)

### [CF1868B1 Candy Party (Easy Version)](https://www.luogu.com.cn/problem/CF1868B1)

如果 $i$ 给 $j$ $2 ^ x$，那么从 $i$ 向 $j$ 连权值为 $2 ^ x$ 的边。

算出每个人和平均值的差 $b_i$。

如果 $b_i = 0$，那么它可以被写成任何 $2 ^ x - 2 ^ x$，插在任何边的中间。直接忽略掉所有 $0$。

如果 $b_i > 0$，那么如果它不能被写成 $2 ^ x - 2 ^ y$，则无解。否则 $x, y$ 是唯一的（其中 $2 ^ y$ 是 $b_i$ 的 $\mathrm{lowbit}$，$2 ^ x$ 是 $b_i + 2 ^ y$），一定会给出 $2 ^ x$ 收到 $2 ^ y$。

算出 “给出 $2 ^ x$” 和 “收到 $2 ^ x$” 的人数是否相等，若不等则无解，否则一定有解：因为每个环上必然有小于 $0$ 的数，那就存在指向小于 $0$ 的数 $b_j$ 的大于 $0$ 的数 $b_i$。设 $avg$ 为平均值，$2 ^ x$ 为不小于 $avg$ 的最小的 $2$ 的幂，那么 $b_i\to b_j$ 的权值不大于 $2 ^ x$，因为 $b_j > -avg$。又因为 $b_i > 0$ 且 $b_i$ 给出了 $2 ^ x$，所以 $b_i\geq 2 ^ {x - 1}$，又因为 $avg\geq 2 ^ {x - 1}$，所以 $a_i = b_i + avg\geq 2 ^ x$，$i$ 可以给 $j$ $2 ^ x$，这样 $j$ 的入度变成了 $0$。从 $j$ 开始依次给下去即可。

时间复杂度 $\mathcal{O}(n\log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;

int n, a[N], cnt[31];
void mian() {
  long long sum = 0;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
  if(sum % n) return cout << "no\n", void();
  sum /= n;
  memset(cnt, 0, sizeof(cnt));
  for(int i = 1; i <= n; i++) {
    a[i] -= sum;
    if(!a[i]) continue;
    if(a[i] > 0) {
      int p = __lg(a[i] & -a[i]);
      a[i] += 1 << p, cnt[p]--;
      p = __lg(a[i] & -a[i]);
      a[i] -= 1 << p, cnt[p]++;
    }
    if(a[i] < 0) {
      a[i] = -a[i];
      int p = __lg(a[i] & -a[i]);
      a[i] += 1 << p, cnt[p]++;
      p = __lg(a[i] & -a[i]);
      a[i] -= 1 << p, cnt[p]--;
    }
    if(a[i]) return cout << "no\n", void();
  }
  for(int i = 0; i < 31; i++) {
    if(cnt[i]) return cout << "no\n", void(); 
  }
  cout << "yes\n";
}
int main() {
  int T = 1;
  cin >> T;
  while(T--) mian();
  return 0;
}
```

---

## 作者：One_JuRuo (赞：4)

## 思路

首先想要均分糖果，那么必须满足糖果总数 $sum$ 是人数 $n$ 的倍数。

然后我们再取平均值，令 $s=\frac{sum} n$。

因为每个人必须收到一次糖果且只能送出一次糖果，所以对于每一个 $a_i$，我们首先需要满足 $a_i-s$ 可以被表示为 $2^x-2^y$。

令 $k=|a_i-s|$。

以二进制的方式来看，$\operatorname{lowbit}(k)$ 应该就是其中一个二次幂，是给出的还是收到的糖果数要看 $a_i$ 和 $s$ 的大小关系，那么 $k+\operatorname{lowbit}(k)$ 就应该是另外一个二次幂。

所以，如果 $k+\operatorname{lowbit}(k)$ 不是二次幂，就可以肯定无解。

那么我们再统计每个人需要接受和送出的糖果数的个数，如果接受和送出的糖果数的个数也不相等，那么就无解，否则，有解。

其实还有个特殊情况，那就是原本就有的糖与平均数相同，但是思考一下就会发现不影响结果。

我们只需要把原本就有的糖与平均数相同的人放在给糖过程中间，过一下手就好，比如 $a$ 要给 $b$ 一颗糖，而 $k$ 刚好拥有的糖就是平均数，那么只需要让 $a$ 给 $k$ 一颗糖，然后再由 $k$ 给 $b$ 一颗糖就好，可以发现这样增加一个转手的过程不影响答案，并且也满足了 $k$ 的需求，所以原本就有的糖与平均数一样不需要考虑，可以直接忽略

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long lowbit(long long x){return x&(-x);}
long long T,n,a[200005],sum,flag,k,low;
map<long long,long long>m1,m2;
inline bool sol()
{
	scanf("%lld",&n),m1.clear(),m2.clear(),flag=sum=0;//多测记得清空
	for(long long i=1;i<=n;++i) scanf("%lld",&a[i]),sum+=a[i];
	if(sum%n) return 1;
	sum/=n;
	for(long long i=1;i<=n;++i)
	{
		a[i]-=sum;k=abs(a[i]);low=lowbit(k);k+=low;
		if(k!=lowbit(k)) return 1;//直接使用lowbit判断是不是二次幂
		else if(a[i]>0) ++m1[k],++m2[low];
		else if(a[i]<0) ++m1[low],++m2[k];
	}
	for(auto i=m1.begin(),j=m2.begin();i!=m1.end()&&j!=m2.end();++i,++j) if(flag||i->first!=j->first||i->second!=j->second) return 1;//接受和送出的糖果数的个数是否一样
	return 0;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
		if(sol()) printf("NO\n");
		else printf("YES\n");
	return 0;
}
 
```

---

## 作者：Z1qqurat (赞：2)

喵喵题。考虑先求出目标状态，也就是每个数都相同，都为平均值 $avg$，如果 $avg$ 不是一个整数那自然无解。考虑到每个人必须给出一次糖果，收下一次糖果，设 $b_i = a_i - avg$，表示 $a_i$ 需要变成目标态，需要失去的糖果。我们将 $b_i = 2^x - 2^y$，如果 $b_i > 0$ 则表示需要给出 $2^x$ 个糖果，收到 $2^y$ 个糖果。$b_i < 0$ 同理，最终我们对于每个 $x$，判断需要得到 $2^x$ 个糖果和失去 $2^x$ 个糖果的人数是否相等就可以了。具体实现看代码，自认为写得比较简洁。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define NO return cout << "No\n", void()
#define YES return cout << "Yes\n", void()
using namespace std;
const int N = 2e5 + 5;
int t, n, a[N], b[N], cnt[33];
ll sum, avg;

void solve() {
    cin >> n;
    sum = avg = 0;
    for (int i = 0; i <= 32; ++i) cnt[i] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; sum += a[i];
    }
    if(sum % n) NO; 
    avg = sum / n;
    for (int i = 1; i <= n; ++i) {
        b[i] = a[i] - avg;
        if(b[i] == 0) continue;
        int c = abs(b[i]);
        int x = log2(c) + 1, y = log2((1 << x) - c);
        if((1 << x) - (1 << y) != c) NO;
        if(b[i] < 0) swap(x, y);
        cnt[x]++, cnt[y]--;
    }
    for (int i = 0; i < 32; ++i) {
        if(cnt[i] != 0) NO;
    }
    YES;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}
```

---

