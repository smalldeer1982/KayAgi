# 题目信息

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

# AI分析结果

### 题目翻译

# 糖果派对（简单版）

## 题目描述

有 $n$ 个人，第 $i$ 个人有 $a_i$ 颗糖。在派对上，每个人 **会且仅会做下面的事情恰好一次** ：

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

### 算法分类
数学、位运算

### 题解分析与结论

本题的核心在于通过位运算和数学分析，判断每个人能否通过恰好一次给糖和一次收糖操作，使得最终每个人的糖果数量相同。具体来说，每个人需要满足 $a_i - avg$ 可以被表示为 $2^x - 2^y$，其中 $avg$ 是平均值。通过统计每个人需要给出和收到的 $2^x$ 的数量是否相等，来判断是否有解。

### 所选题解

#### 1. 作者：Alex_Wei (赞：7)
- **星级**: 5
- **关键亮点**: 通过位运算和数学分析，详细解释了如何判断每个人能否通过恰好一次给糖和一次收糖操作，使得最终每个人的糖果数量相同。代码简洁高效，时间复杂度为 $\mathcal{O}(n\log V)$。
- **个人心得**: 无

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

#### 2. 作者：One_JuRuo (赞：4)
- **星级**: 4
- **关键亮点**: 通过二进制的方式分析每个人需要给出和收到的糖果数，使用 `lowbit` 函数判断是否为二次幂，代码清晰易懂。
- **个人心得**: 无

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

#### 3. 作者：Z1qqurat (赞：2)
- **星级**: 4
- **关键亮点**: 通过位运算和数学分析，判断每个人能否通过恰好一次给糖和一次收糖操作，使得最终每个人的糖果数量相同。代码简洁高效。
- **个人心得**: 无

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

### 最优关键思路或技巧

1. **位运算与数学分析**: 通过位运算（如 `lowbit`）和数学分析，判断每个人能否通过恰好一次给糖和一次收糖操作，使得最终每个人的糖果数量相同。
2. **统计与匹配**: 统计每个人需要给出和收到的 $2^x$ 的数量，判断是否相等，从而判断是否有解。

### 可拓展之处

类似的问题可以通过位运算和数学分析来解决，特别是在涉及到二进制表示和幂次运算的场景中。例如，判断一个数是否可以表示为两个幂次数的差，或者统计某些特定幂次数的出现次数等。

### 推荐题目

1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

---
处理用时：65.76秒