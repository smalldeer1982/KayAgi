# [ABC249F] Ignore Operations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc249/tasks/abc249_f

高橋君は整数 $ x $ を持っています。はじめ、$ x\ =\ 0 $ です。

$ N $ 個の操作があります。$ i\ \,\ (1\ \leq\ i\ \leq\ N) $ 個目の操作は整数 $ t_i,\ y_i $ を用いて以下のように表されます。

- $ t_i\ =\ 1 $ のとき、$ x $ を $ y_i $ で置き換える。
- $ t_i\ =\ 2 $ のとき、$ x $ を $ x\ +\ y_i $ で置き換える。

高橋君は $ 0 $ 個以上 $ K $ 個以下の好きな個数の操作を無視することができます。残った操作を一度ずつ順序を変えずに行ったとき、最終的な $ x $ の値としてあり得る最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ N $
- $ t_i\ \in\ \{1,2\}\ \,\ (1\ \leq\ i\ \leq\ N) $
- $ |y_i|\ \leq\ 10^9\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数

### Sample Explanation 1

$ 5 $ 個目の操作を無視すると、$ x $ は $ 0\ \rightarrow\ 4\ \rightarrow\ 1\ \rightarrow\ 2\ \rightarrow\ 3 $ と変化し、最終的な $ x $ の値は $ 3 $ となります。これが最大です。

## 样例 #1

### 输入

```
5 1
2 4
2 -3
1 2
2 1
2 -3```

### 输出

```
3```

## 样例 #2

### 输入

```
1 0
2 -1000000000```

### 输出

```
-1000000000```

## 样例 #3

### 输入

```
10 3
2 3
2 -1
1 4
2 -1
2 5
2 -9
2 2
1 -6
2 5
2 -3```

### 输出

```
15```

# 题解

## 作者：liangbowen (赞：7)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc249_f)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17320550.html)

很好玩的贪心。

update 2024/07/14：被人叉了，，，远古题解随便改了下。

## 思路

如果第 $i$ 次操作为覆盖操作，那么 $1 \sim i-1$ 次操作都是无效的，原因显然。

这启示我们**从后往前扫**（前面的会被忽略，后面的不会啊！）。

在此基础上，就是分类讨论一下（假设当前的最大答案为 $sum$）：

+ 当前操作是覆盖操作：
  + 如果不删 $a_i$，那么 $(sum + a_i)$ 就是最终答案，因为更前面的操作会被省略。
  + 如果删 $a_i$，那么这次操作无效，但是能操作的次数少了。所以 $k \gets k-1$，继续。
+ 当前操作时增加操作：
  + 如果 $a_i \ge 0$，加了肯定时好的，所以直接 $sum \gets sum + a_i$。
  + 如果 $a_i < 0$，加了肯定变差，所以我们试图不加它。但是当不加的数量超过 $k$ 时，不得不把某些操作重新加上。

对于最后一项，我们可以把 $sum$ 重新加上**当前最大的元素**。所以只需要一个优先队列，当 $\text{size} > k$ 时就扔掉 $\max\limits_{x \in \text{queue}} x$。

当 $k < 0$ 的时候就不能操作了，请直接退出程序。另外操作完全部后，如果 $k\ge0$，那么 $sum$ 也是可以作为答案的，记得更新一下。

## 代码

```cpp
#include <iostream>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 2e5 + 5;
int op[N], a[N];
int main() {
	priority_queue <int> q;
	int n, k; long long ans = -9e18, sum = 0;
	scanf("%d%d", &n, &k), op[0] = 1;
	for (int i = 1; i <= n; i++) scanf("%d%d", &op[i], &a[i]);

	for (int i = n; i && k >= 0; i--) {
		if (op[i] == 1) ans = max(ans, a[i] + sum), k--;
		else if (op[i] == 2) {
			if (a[i] >= 0) sum += a[i];
			else q.push(a[i]);
		}
		while ((int)q.size() > k && !q.empty()) sum += q.top(), q.pop(); //把比较大的元素扔掉
	}
	if (k >= 0) ans = max(ans, sum);
	cout << ans;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Hovery (赞：4)

## Problem

[Ignore Operations](https://www.luogu.com.cn/problem/AT_abc249_f)

## Sol

我们可以发现，对于每次 $1$ 操作来说，删去其前面的操作显然是多余的。

为方便统计答案，我们在最前面加一个 ```1 0``` 的操作。

那么对于一个 $1$ 操作来说，它要产生贡献，必须先把后面所有的 $1$ 操作删除，然后再贪心地去删一些不优的 $2$ 操作。

由此可以发现，前面的不会影响后面的，但后面会影响前面的，考虑倒着做。

倒着做的时候维护一个堆，每次碰到一个 $2$ 就判断把它删了会不会有贡献，若有就放入堆，并从堆里取出一个最大的扔了。否则就不管它。

对于 $1$ 操作来说，就先把在它后面 $1$ 操作全部删了，看剩下还有几次操作，然后贪心地从堆里删。

这样说可能不好理解，具体还是看代码。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

pair<int, int> a[200010];

signed main()
{
    int n, k, ans = -1e17, now = 0;
    multiset<int> _1;
    cin >> n >> k;
    a[0].first = 1;
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = n; ~i ;i--)
    if (a[i].first == 1)
    {
        if (k < 0)
        continue;//k表示还剩下几次操作。
        ans = max(ans, a[i].second + now);
        k--;//因为对于在它前面的1操作来说要把它删了，所有就减一。
        while (_1.size() > k)//删的数的数量不能超过k 。
        {
            now += *_1.rbegin();
            _1.erase(prev(_1.end()));
        }
    }
    else
    {
        now += a[i].second;
        if (a[i].second < 0 && _1.size() < k)//当前堆里数的个数小于k就可以放进堆里。
        {
            now -= a[i].second;
            _1.insert(a[i].second);
        }
        else
		if (a[i].second < 0)
		{
            if (!_1.empty() && a[i].second < *_1.rbegin())//若堆满了，但是放这个数会更优，就把这个数放进去，把不优的扔掉。
            {
                now += *_1.rbegin();
                now -= a[i].second;
                _1.erase(prev(_1.end()));
                _1.insert(a[i].second);
            }
        }
    }
    cout << ans << '\n';
}
```

---

## 作者：__xxy_free_ioi__ (赞：2)

# 题解：AT\_abc249\_f \[ABC249F] Ignore Operations

**前置芝士：反悔贪心**

## 解法

先看到操作一，我们发现但凡使用了操作一那么就意味着其前面的操作就全部作废了，那么这就其实我们从后往前扫描数组。设从后往前扫描时的总价值是 $tot$，最终答案是 $res$，那么，接受这个操作的代价就是 $tot + a_i$，$res$ 直接对其取最值，忽略的话就只好 $k - 1$，然后继续。

再看操作二，我们发现，当 $a_i \ge 0$ 时，加上自然是最好的。当 $a_i < 0$ 时，我们会尽可能的不加上它，但是 $k$ 的大小是有限的，所以我们要尽可能的选大的数加入，这里就可以用优先队列维护。

## 代码

```
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, k, tot = 0, res = -1e18;
    cin >> n >> k;
    vector<int> a(n + 10), op(n + 10);

    for (int i = 1; i <= n; i++) 
        cin >> op[i] >> a[i];
    
    priority_queue<int> q;
    for (int i = n; i && ~k; i--) {
// k始终保持>=0的状态。
        if (op[i] == 1) res = max(res, tot + a[i]), k--;
        else if (a[i] >= 0) tot += a[i];
        else q.push(a[i]);
        while (q.size() && q.size() > k) 
            tot += q.top(), q.pop();
// 发现必须要加入负权值的数了，尽可能选大的加入。
    }

    if (~k) res = max(res, tot);
// 如果k>=0的话，再取一次最值。
    return cout << res, 0;
}
```

---

## 作者：yinbe (赞：2)

## 题目描述

存在变量 $x$，初始时 $x = 0$。给定 $n$ 次操作按序进行，存在两种，`1 y` 表示 $x \leftarrow y$，`2 y` 表示 $x \leftarrow x + y$，你可以从中删除不超过 $k$ 个操作，要求最大化操作后的 $x$，输出最大值。

- $1\ \leq\ N\ \leq\ 2\ \times\ 10^5$
- $0\ \leq\ K\ \leq\ N$
- $|y_i|\ \leq\ 10^9\ \,\ (1\ \leq\ i\ \leq\ N)$

## 思路

因为 $1$ 操作前的操作都对之后的答案没有影响，所以我们可以从后往前倒序考虑所有操作。

### $1$ 操作

- 删除：没了这个操作，$x$ 不变，为 $\max_{后面的答案}$，$k\leftarrow k-1$。
- 不删除：$x$ 变为 $y+\max_{后面的操作}$。

然后在这里更新 $ans \leftarrow \max(ans,x)$

### $2$ 操作

考虑贪心，显然如果 $y \ge 0$，进行操作后 $x$ 不会变小，可以全部加上。

如果 $y<0$，我们可以尽量删除掉，删除不的优先删除 $y$ 小的，保留大的，这样一定是最优的，我们可以使用优先队列维护要删掉的 $2$ 操作对应的 $y$，每次碰到 $y<0$ 的 $2$ 操作就把 $y$ 加入优先队列，如果优先队列的大小超过的 $k$，就相当于没办法全部删完，我们可以让优先队列的顶部弹出加到 $x$ 上，也就是让删掉的 $2$ 操作中找一个 $y$ 最大的撤销删除。

### 其他细节

退出循环除了遍历完所有操作，还有一种情况就是 $k<0$ 时，因为 $k<0$ 时就是 $k=0$ 时碰到了 $1$ 操作并试图删除它，这个 $1$ 操作无法删除，再往前的操作对答案就没有影响，就没有必要再往前了。

还有就是退出循环后如果 $k \ge 0$，相当于就是没有提前退出遍历完了所有操作，此时 $x$ 也可以作为最后的答案更新 $ans$，还有一种处理方法是在一开始加一个操作 `1 0`，这样不影响答案，并且也能和 $k\ge 0$ 的特判达到一样的效果。

## 代码

```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,k,op[200005];
long long a[200005],x=0,ans=-(1ll<<62);
priority_queue<int>pq;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%lld",&op[i],&a[i]);
	for(int i=n;i>=1&&k>=0;i--)
	{
		if(op[i]==1)
		{
			ans=max(ans,a[i]+x);
			k--;
		}
		else
		{
			if(a[i]>=0)
				x+=a[i];
			else
				pq.push(a[i]);
		}
		while((int)(pq.size())>k)
		{
			x+=pq.top();
			pq.pop();
		}
	}
	if(k>=0)
		ans=max(ans,x);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：returnzheng (赞：2)

**注意到在最后一次操作一前的操作都是无效的，会被赋值覆盖。**

所以可以倒序枚举操作，枚举最后一个操作一，用**小根堆**辅助计算第一个操作一后的所有操作的值（后面的其他操作一删除，消耗一次删除次数，剩下的删除操作删 $y < 0$ 的操作二）。

代码实现
``` cpp
#include <bits/stdc++.h>
using namespace std;
long long t[300000];
long long a[300000];
int main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	long long n, k;
	cin >> n >> k;
	priority_queue<long long> p;
	for (long long i = 1; i <= n; i++){
		cin >> t[i] >> a[i];
	}
	long long sum = 0;
	long long ans = -4e18;
	for (long long i = n; i >= 1; i--){
		if (k < 0){
			break;
		}
		if (p.size() > k){
			sum += p.top();
			p.pop();
		}
		if (t[i] == 1){
			ans = max(ans, sum + a[i]);
			k--;
		}
		else if (t[i] == 2){
			if (a[i] >= 0){
				sum += a[i];
				continue;
			}
			p.push(a[i]);
		}
	}
	if (p.size() > k){
		sum += p.top();
		p.pop();
	}
	ans = max(ans, sum);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：cdx123456 (赞：2)

**Problem**

[Ignore Operations](https://www.luogu.com.cn/problem/AT_abc249_f)

**Solution**

其他巨佬用的各种高级数据结构给本蒻蒟看呆了，自己来写一发。

本题主要有两种操作，分别是修改与增加，并允许删除 $0$ $\sim$ $k$ 个，求最大结果。

因为前面的操作不影响后面的，所以从后往前遍历操作。

对于每一次修改，如果不删除，则前面的操作无效，可以用优先队列记录后面的最优删除，并更新答案。如果删除，$k$ 减去1，再计算前面的。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000010],b[1000010];         //不开long long见祖宗
int main(){
	priority_queue<long long> q;
	long long n,k,ans=-1e15,x=0;
	cin>>n>>k;
	a[0]=1;                       //初值赋为0，为方便统计答案，所以放这了
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(int i=n;i>=0;i--){             //从后往前遍历
		if(a[i]==1){
			ans=max(ans,x+b[i]);         //更新答案
			k--;
			if(k<0) break;             //没得删了就跳出
			while(q.size()>k){          //需删队列大小超过k，需要调整
				x+=q.top();
				q.pop();
			}
		}else{
			x+=b[i];
			if(b[i]<0){                  //大于等于0的删了一定不更优
				if(q.size()<k){
					q.push(b[i]);          //能删直接删
					x-=b[i];
				}else if(k && q.top()>b[i]){  //选这个更优
					x+=q.top();
					q.pop();
					x-=b[i];
					q.push(b[i]);
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Tsawke (赞：2)

# [[ABC249F] Ignore Operations](https://www.luogu.com.cn/problem/AT_abc249_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC249F)

## 题面

存在变量 $ x $，初始时 $ x = 0 $。给定 $ n $ 次操作按序进行，存在两种，`1 y` 表示 $ x \leftarrow y $，`2 y` 表示 $ x \leftarrow x + y $，你可以从中删除不超过 $ k $ 个操作，要求最大化操作后的 $ x $，输出最大值。

## Solution

这题比 E 简单多了。。
观察发现如果有一个 $ 1 $ 操作被我们保留，那么它将覆盖所有在其之前的操作。所以我们不难想到可以考虑以每个 $ 1 $ 操作为分割点，考虑是否保留这个操作。

显然我们希望让这个东西无后效性，所以具体地，我们将整个操作逆序遍历。如果为 $ 2 $ 操作则记录，如果为 $ 1 $ 操作则先假设我们保留这个操作，那么之后的所有都可以忽略了。此时我们只需要在前面记录的所有 $ 2 $ 操作中的所有**负数**中找到前 $ k $ 小的将其删除，此时剩下的即为当前的最优操作。然后考虑如果不保留这个操作，此时首先需要保证 $ k > 0 $，然后令 $ k \leftarrow k - 1 $，也就是将这个 $ 1 $ 操作删除，只剩下后面的 $ 2 $ 操作，然后按照刚才的做法继续遍历下去。

有个细节就是注意当删 $ 1 $ 操作的时候已经把 $ k $ 用完了之后，就应该直接 `break` 了，因为此时无法将当前的 $ 1 $ 删掉，自然后面的所有操作就无效了。

然后我们刚才找到前 $ k $ 小的和这个操作，不难想到用平衡树或者权值线段树就行。权值线段树比较好写一些，但是注意需要离散化做个映射。具体地，权值线段树维护每个位置有多少个数，以及区间和，查询的时候就是在权值线段树上二分即可。

显然这个东西的复杂度最坏是 $ O(n \log n) $ 的。

然后还有两个老生常谈的 AtCoder 独有的问题，一个就是 C++17 似乎不支持 `basic_string < pair < int, int > >`，大概的原因时 `is_trivial < pair < int, int > >::value` 为 `false`，所以会报 CE，这个东西在 [[ABC248Ex] Beautiful Subsequences 题解](http://blog.tsawke.com/?t=ABC248Ex) 也提到过。然后就是 AtCoder 里面 data 似乎时保留字符。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, K;
ll sum(0);
ll ans(LONG_LONG_MIN);
int mp[210000];
struct Pair{int first, second;};
basic_string < Pair > opt;
basic_string < int > _data;

class SegTree{
private:
    int tr[210000 << 2];
    ll sum[210000 << 2];
    #define LS (p << 1)
    #define RS (LS | 1)
    #define MID ((gl + gr) >> 1)
public:
    void Pushup(int p){
        tr[p] = tr[LS] + tr[RS];
        sum[p] = sum[LS] + sum[RS];
    }
    void Modify(int pos, int p = 1, int gl = 1, int gr = N){
        if(gl == gr)return tr[p]++, sum[p] += mp[pos], void();
        if(pos <= MID)Modify(pos, LS, gl, MID);
        else Modify(pos, RS, MID + 1, gr);
        Pushup(p);
    }
    ll Query(int K, int p = 1, int gl = 1, int gr = N){
        if(tr[p] <= K)return sum[p];
        if(gl == gr)return 0;
        if(tr[LS] > K)return Query(K, LS, gl, MID);
        else return sum[LS] + Query(K - tr[LS], RS, MID + 1, gr);
    }
}st;

int main(){
    // freopen("in.txt", "r", stdin);
    N = read(), K = read();
    opt += {1, 0};
    for(int i = 1; i <= N; ++i){
        int f = read(), v = read();
        opt += {f, v};
        if(f == 2)_data += v;
    }sort(_data.begin(), _data.end());
    _data.erase(unique(_data.begin(), _data.end()), _data.end());
    // N = _data.size();
    for(auto &op : opt){
        if(op.first == 1)continue;
        int dis = distance(_data.begin(), upper_bound(_data.begin(), _data.end(), op.second));
        mp[dis] = op.second, op.second = dis;
    }
    for(auto it = opt.rbegin(); it != opt.rend(); ++it){
        if(it->first == 1){
            ans = max(ans, (ll)it->second + sum - st.Query(K--));
            if(K < 0)break;
            // printf("cur, ans = %lld\n", it->second + sum - st.Query(K + 1));
        }else{
            sum += mp[it->second];
            if(mp[it->second] < 0)st.Modify(it->second);
        }
    }printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_11_30 初稿

---

## 作者：Red_river (赞：1)

### 问题分析

给定一个操作序列，你的目标是通过执行这些操作来最大化最终的 $x$ 值。操作有两种类型：

1. **一操作**：将 $x$ 设为某个给定值 $y$，即 $x \leftarrow y$。
2. **二操作**：将 $x$ 增加一个给定值 $y$，即 $x \leftarrow x + y$。

同时可以删除最多 $k$ 个操作。最大化最后得到的 $x$ 值。

### 策略
考虑**贪心**和分类讨论：
- 从**右到左**处理操作，可以**避免重复**计算。我们从最后一个操作开始，逐步分析每个操作的影响，并决定是否删除。
- 使用**堆来存储**所有负数加法操作，以便我们能够选择删除对结果影响最大的负数加法操作。

### 主要步骤
从后往前遍历操作：
- 对于类型一操作，直接更新 $ans$ 的最大值。
- 对于类型二操作，若是负数，则加入最大堆。
- 对于类型二操作，若是正数，则加到当前的 $sum$，毕竟能不删且还是正数肯定是要的。
- 在堆中的元素数量超过 $k$ 时，弹出堆顶元素，更新 $sum$。

### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define N 200005

using namespace std;
ll n,m,k,jk,ans,sum,num,cnt,tot;
ll head[N],dis[N],vis[N],wis[N],f[N];

void read(ll &x) {
    x = 0;
    ll ff = 1;
    char ty;
    ty = getchar();
    while (!(ty >= '0' && ty <= '9')) {
        if (ty == '-') ff = -1;
        ty = getchar();
    }
    while (ty >= '0' && ty <= '9')
        x = (x << 3) + (x << 1) + ty - '0', ty = getchar();
    x *= ff;
    return;
}

void write(ll x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    char asd[201];
    ll ip = 0;
    while (x) asd[++ip] = x % 10 + '0', x /= 10;
    for (ll i = ip; i >= 1; i--) putchar(asd[i]);
    return;
}

priority_queue<ll> q;
struct P {
    ll x, y;
} v[N];

int main() {
    read(n), read(m); 
    sum = 0;
    ans = -1e18;
    v[0].x = 1;
    for (ll i = 1; i <= n; i++) read(v[i].x), read(v[i].y);
    
    for (ll i = n; i >= 1 && m >= 0; i--) {
        if (v[i].x == 1) ans = max(ans, sum + v[i].y), m--;//更新后，因为如果还要往下遍历，所以当前这个点一定要删掉。
        else {
            if (v[i].y >= 0) sum += v[i].y;//更新。
            else q.push(v[i].y);//加入。
        }
        while (q.size() > m && !q.empty())
            sum += q.top(), q.pop();//取出来加入当前最大值里。
    }wh(max(ans, sum));
    return 0;
}

---

## 作者：elbissoPtImaerD (赞：1)

题目有两种操作，分别是赋值和加。

显然如果最终操作序列有赋值的话，这次赋值操作之前的所有操作都是无效的。  
即最终有效操作序列有且仅有一个赋值操作，而且必在操作序列的第一个。

那么问题就转化为，对于原操作序列的某一个以复制操作为首的操作序列，无视其中不多于 $k$ 个加操作，能得到的最大值。

等价于：给定序列 $a$，求 $\sum\limits a_ic_i$ 最大值，其中有不大于 $k$ 个 $c_i=0$，其余 $c_i=1$。  
经典反悔贪心。

复杂度 $\mathcal{O(n\log n)}$。

细节看代码。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc249/submissions/39837693)

---

## 作者：WaterSun (赞：0)

# 思路

反悔贪心套路题。

发现一个性质，当一个操作 1 生效意味着在这一步之前的所有操作都没用。

那么考虑倒着枚举，对于每一个操作 1 的选取状态做一个简单的分讨：

1. 如果保留，那么这种情况下的答案就是之前的 $sum$ 加上当前的 $y$。

2. 如果不保留，继续往前走，$k \leftarrow k - 1$。

那么对于已经遍历的操作 2，显然如果 $y \geq 0$ 直接加到答案中，否则我们显然选出前 $k$ 小的操作消除，这个东西直接用堆维护一下即可。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register
#define int long long

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10,inf = (int)(1e18) + 10;
int n,k,ans = -inf,sum;
pii arr[N];
priority_queue<int> q;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

signed main(){
    n = read();
    k = read();
    for (re int i = 1;i <= n;i++){
        arr[i].fst = read();
        arr[i].snd = read();
    }
    for (re int i = n;i && ~k;i--){
        if (arr[i].fst == 1){
            ans = max(ans,sum + arr[i].snd);
            k--;
        }
        else{
            if (arr[i].snd >= 0) sum += arr[i].snd;
            else q.push(arr[i].snd);
        }
        while ((int)(q.size()) > k){
            sum += q.top();
            q.pop();
        }
    }
    printf("%lld",max(ans,sum));
    return 0;
}
```

---

## 作者：wnsyou (赞：0)

# [Ignore Operations](https://vjudge.csgrandeur.cn/problem/AtCoder-abc249_f)
## 题意
Takahashi 有一个整数 $x$，初始 $x = 0$。

有 $n$ 次操作。第 $i$ 次操作用两个整数 $t_i, y_i$ 描述：

- 如果 $t_i = 1$，将整数 $x$ 替换为 $y_i$。
- 如果 $t_i = 2$，将整数 $x$ 替换为 $x + y_i$。

Takahashi 可以跳过其中至多 $K$ 次操作。对于剩下的没跳过的操作序列，按顺序执行操作，并求出最终 $x$ 的可能最大值。
### 数据范围

- $0 \leqslant k \leqslant n \leqslant 2 \times 10^5, n \geqslant 1$
- $t_i \in \{ 1, 2\}, |y_i| \le 10^9$
## 思路
我们肯定不会跳过那些对答案有正面作用的操作，那其他的呢？

来看一张草图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ok74u4yh.png)

显然，在最后一次赋值操作以前，所有操作**均可视为没有**。

那么在最后一次赋值操作之后的那些操作呢？跳过第 $i$ 次操作的话，对答案的贡献就是：$-y_i$，当我们跳过次数超过 $k$ 时，我们要做出取舍：把对答案贡献最小的那一次放弃。

那么，我们可以推出第一步：从后往前找，用堆来存储每次操作对答案的贡献，模拟一下上面的那种操作即可。

那问题是，处理好了最后一次赋值操作以后的所有，那前面的怎么办呢？

这也不难，令 $sum_i$ 表示从操作 $1$ 执行到操作 $i$、一次也不跳过的情况下的答案，那么删除最后一次赋值操作($j$)对答案的贡献就是 $sum_{i - 1} - sum_i$，**且这次操作是不可逆的，即永久消耗这次操作**。

统计答案即可。
### 复杂度
- 时间：$O(n \log n)$
- 空间：$O(n)$
## Code

```cpp
#include <iostream>
#include <queue>

using namespace std;
using ll = long long;

const int N = 2e5 + 10;

struct Node {
  int op, t;
} a[N];

int n, k;
ll x, y, sum[N], ans, num;
priority_queue<int> pq; // 堆维护

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].op >> a[i].t;
    if (a[i].op == 1) { // 预处理 sum
      sum[i] = a[i].t;
    } else {
      sum[i] = sum[i - 1] + a[i].t;
    }
    ans = sum[i];
  }
  for (int i = n; k && i >= 1; i--) {
    if (a[i].op == 2 && a[i].t < 0) { // 操作 2
      pq.push(a[i].t); // 答案贡献，这里取了个反
      num += a[i].t; // 贡献之和
      if (pq.size() > k) { // 操作次数超过 k
        num -= pq.top(), pq.pop(); // 去掉答案贡献最小的
      }
    } else if (a[i].op == 1) { // 操作 1
      num += sum[i] - sum[i - 1];
      if (pq.size() == k) {
        num -= pq.top(), pq.pop();
      }
      k--; // 不可逆的操作
    }
    ans = max(ans, sum[n] - num); // 计算答案最大值
  }
  cout << ans;
  return 0;
}
```

---

## 作者：西瓜nd (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc249_f)

## 题意简述

存在变量 $x$ ，初始时 $x=0$ 。给定 $n$ 次操作按序进行，操作类型以下有两种：

- ```1 y``` 表示将 $x$ 赋值为 $y$ 
- ```2 y``` 表示将 $x$ 加上 $y$

你可以从中删除不超过 $k$ 个操作，使得最终的 $x$ 最大，输出最大值。

## 题目分析

首先可以发现，当一个赋值操作被保留时，对于这个赋值操作，它前面的操作都可以忽略，可以把它当做一个“新的开始”，删除它前面的操作是多余的。

这时我们可以考虑从后往前枚举操作，因为前面的操作不影响后面的操作，且后面的赋值和相加操作对结果的影响更大。

为了使结果尽可能大，我们可以贪心选取相加操作中对结果负贡献尽可能小的，正的直接计入和，负的用一个优先队列处理就行；而对于赋值操作，讨论删或不删的情况，取最大值即可，并且要保证在当前赋值操作后的赋值操作都被删除。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
int n,k;
long long sum,ans=-0x3f3f3f3f3f3f3f;
int t[maxn],a[maxn];
priority_queue<int> q;


int main(){
    ios::sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>t[i]>>a[i];

    for(int i=n;i>=1;i--){
        if(t[i]==1){
            ans=max(ans,sum+a[i]);
            k--;
            if(k<0)break;
            while(q.size()>k){	//保证元素个数不超过k，超过k时则弹出队首
                sum+=q.top();
                q.pop();
            }
        }
        else{
            if(a[i]>=0)sum+=a[i];//正的直接加入
            else {
                q.push(a[i]);	 //负的丢进优先队列
                while(q.size()>k){
                    sum+=q.top();
                    q.pop();
                }
            }
        }
    }
    ans=max(ans,sum);
    cout<<ans<<endl;
    return 0;
}
```



---

