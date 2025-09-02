# Make It Permutation

## 题目描述

You have an integer array $ a $ of length $ n $ . There are two kinds of operations you can make.

- Remove an integer from $ a $ . This operation costs $ c $ .
- Insert an arbitrary positive integer $ x $ to any position of $ a $ (to the front, to the back, or between any two consecutive elements). This operation costs $ d $ .

You want to make the final array a permutation of any positive length. Please output the minimum cost of doing that. Note that you can make the array empty during the operations, but the final array must contain at least one integer.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the array is already a permutation, so there's no need for operations.

In the second test case, we can remove numbers $ 5 $ , $ 6 $ to get the permutation $ [1,2,3] $ in cost $ 2 $ . Note that we can also get a permutation by inserting a number $ 4 $ , but it costs $ 5 $ .

In the third test case, we can just remove all the numbers except for the first number $ 1 $ . It costs $ 8 $ , and the final array is $ [1] $ , which is a permutation of length $ 1 $ .

In the fourth test case, we can remove all the numbers except for $ 2 $ , and insert a number $ 1 $ to the first position. It costs $ 4+10=14 $ , and the final array is $ [1,2] $ , which is a permutation of length $ 2 $ .

## 样例 #1

### 输入

```
8
3 3 3
1 2 3
5 1 5
1 2 3 5 6
5 2 3
1 1 1 3 3
5 1 10
2 4 6 8 10
6 2 8
7 3 5 4 4 8
4 10 1
1 2 6 7
4 3 3
2 5 8 7
2 1000000000 1
1000000000 1```

### 输出

```
0
2
8
14
20
3
12
999999998```

# 题解

## 作者：ttq012 (赞：1)

容易发现，一个排列中不能有重复的数字。所以排列中所有的重复的数字都要被删除。

然后枚举每一个数字 $x$，计算 $1\sim x$ 的排列的代价即可。

~~时间复杂度 $O(n^2)$ 没错我在逗你~~

考虑优化。

首先将 $a$ 数组去重并排序。

然后枚举每一个数字 $x$，容易发现需要补全 $[1,x]$ 中的数，并且删除 $[x+1,+\infty)$ 中的数。

这个鬼玩意用线段树随便算一下就可以了。

时间复杂度 $O(n\log n)$。

---

## 作者：abensyl (赞：1)

原题：[CF1810C Make It Permutation](https://www.luogu.com.cn/problem/CF1810C)。

## 思路

首先，作为一个 permutation，一定不能有重复元素，所以先对数组进行去重，然后将重复数字删掉，这些花费是不论什么方案都需要做的。

其次，我们可以依次遍历整个数组，对于每个元素 $a_i$，构造一个 $[1,a_i]$ 的 permutation 需要的花费是 $c\times(n-i)+d\times(a_i-i)$，取其中的最小值。

但是，本题最坑人的地方在于，我们有可能把数组中全部的数都删掉，然后加入一个 $1$，构成一个排列，所以我们需要再将答案和 $d + c\times n$ 进行取最小值。

然后输出答案即可。

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
const int N = 200005;
int a[N];
signed main() {
  int TT;
  cin >> TT;
  while (TT--) {
    int n, c, d;
    cin >> n >> c >> d;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int res = d * 1 + c * n;
    sort(a + 1, a + n + 1);
    int len = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= len; ++i) res = min(res, c * (n - i) + d * (a[i] - i));
    cout << res << '\n';
  }
  return 0;
}
```
我的 [AC 记录](https://codeforces.com/contest/1810/submission/199985169)。

---

## 作者：_Z_F_R_ (赞：0)

### 题目大意
给你 $N$ 个数，第 $i$ 个数为 $a_i$，有下列两种操作：

- 删掉一个数，代价为 $c$；
- 在这集合中加入一个正整数，代价为 $d$。

求最小让这些数变成一个排列的代价。
### 定义
- 若 $P$ 是一个排列，定义 $f_P$ 为这个排列中最大的数。
- 用 $\operatorname{del}(x)$ 表示删了 $x$ 的操作，用 $\operatorname{add}(x)$ 在集合中加入 $x$ 的操作。
### 思路
如果最终的**最优**排列为 $B$，有两种情况：

1. $f_B$ 是原集合中已有的数。就把集合中大于 $f_B$ 的正整数删去，把等于 $f_B$ 的数保留一个，把小于 $f_B$ 的正整数有的保留一个，没的加上一个，代价取最小值即可。
2. $f_B$ 不是原集合中已有的数。则一定有 $f_B = 1$。

证明：若 $f_B \not = 1$，那么 $f_B \ge 2$，那么一定有一操作为 $\operatorname{add}(f_B)$，若去掉这个操作，则 $f_B \gets f_B - 1$，还是一个排列，相比于原操作少了代价 $d$，则 $B$ 不是最优排列。

情况一可以从小到大枚举，再与情况二取 $\min$ 即可。

------------
代码如下：
```
//By @_Z_F_R_ in 2023
#include <bits/stdc++.h>
#define ll long long
#define rep(i,x,y,z) for(i = x;i <= y;i += z)
#define REP(i,x,y,z) for(i = x;i >= y;i -= z)
using namespace std;

const int N = 100005;
ll t,n,c,d,a[N];

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> c >> d;
        int i,j;
        memset(a,0,sizeof(a));
        rep(i,1,n,1)
            cin >> a[i];
        sort(a + 1,a + n + 1);//排序，以便从小到大枚举
        a[0] = a[1] - 1;//小技巧，防止 i=1 时误判
        ll ans = 0,cnt_del = 0,cnt_pl = 0;//cnt_del 为 del 操作的次数，cnt_pl 为 add 操作的次数
        ans = n * c + d;//第二种情况
        rep(i,1,n,1)
        {
            if(a[i] == a[i - 1])//有重复的
                cnt_del++;
            if(a[i] > a[i - 1] + 1)//有需要加的
                cnt_pl += a[i] - a[i - 1] - 1;
            ans = min(ans,(cnt_del + n - i) * c + (cnt_pl + a[1] - 1) * d);//枚举第一种情况，取 min
        }
        printf("%lld\n",ans);
    }
}

```

---

## 作者：sto_5k_orz (赞：0)

$1\leq a_i\leq 10^9,1\leq n \leq 10^5$。

多半是 $O(n\log n)$ 的。

考虑最后的答案一定是以 $a_i$ 或者 $1$ 为结尾的，那么首先删掉重复数字，可以用 unique 函数解决。

那么以 $a_i$ 为结尾的排列需要删掉后 $n-i$ 个数，还需要补全之前空着的 $a_i-i$ 个数。 所以花费是 $(n-i)c+(a_i-i)d$

当然，我们会发现，样例的数据 $6$ 是全都删了留一个 $1$ 下来的，这种方案的花费是 $nc+d$ 的。

复杂度是排序的 $O(n\log n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
#define pb push_back
#define int long long
namespace SlowIO{
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
} using namespace SlowIO;
const int N = 100010; int a[N], b[N], n;
signed main() {
	int t, c, d; Read(t);
	W(t--) {
		Read(n, c); Read(d);
		for(int i = 1; i <= n; i++) Read(a[i]), b[i] = a[i]; int mi = n * c + d; // 特判全删留 1 的情况
		sort(b + 1, b + 1 + n); int m = unique(b + 1, b + 1 + n) - b - 1;
		for(int i = 1; i <= m; i++) {
//			cout << i << ' ' << b[i] << endl;
			mi = min(mi, (n - i) * c + (b[i] - i) * d);
		}
		cout << mi << endl;
	}
	return 0;
}
```

---

## 作者：inc1ude_c (赞：0)

首先，想让最终序列是一个排列，那么一定不会有重复的元素，所以第一步就应该把重复的元素都只保留一个，其余全删掉。

设去重后序列长度为 $l$，然后将去重后的序列排序。

枚举一个 $i$，计算要把序列搞成是一个长度为 $a_i$ 的排列，需要多少花费。想让排列长度为 $a_i$，首先就要补齐 $1\sim a_i$ 中缺失的数，但你现在只有 $i$ 个数，所以要增加 $a_i-i$ 个数；其次需要把 $a_i$ 后面存在的数字全删掉，也就是删掉 $l-i$ 个数。总花费即为 $(a_i-i)\times d+(l-i)\times c$。

每枚举一次后更新答案即可。记得这个答案要与第一步去重所用的花费相加！

注意还有一种需要特判的特殊情况：将序列删完后再补上一个 $1$。

有人可能会问为什么最终排列长度一定是一个在序列中的某个元素的值（排除最终需要特判的特殊情况）。因为如果长度是 $x$，而 $a_{i-1}<x<a_{i}$，那么你为啥不把排列长度搞成 $a_{i-1}$？搞成长度为 $x$ 的话你还要用一些花费去增加一下 $a_{i-1}+1\sim x$ 这些元素啊。

[Code](https://codeforces.com/contest/1810/submission/200098422)

---

## 作者：_299817_ (赞：0)

## Part 1: 题意简述

你现在有一个长度为 $n$ 的数组，现在有 $2$ 种操作：
+ 从数组中去掉一个数，这个操作的代价为 $c$。
+ 在数组的任意的一个地方插入任意的一个数，这个操作的代价为 $d$。

现在，你最少需要多少的代价能把这个数组变成一个任意正长度的排列。

排列指对于一个长度为 $n$ 的数组，如果 $1 \dots n$ 每个数都出现且仅出现一次， 那么这个数组就是一个排列。

注意，这道题中虽然最后的结果中数组的长度不能为 $0$，但是过程中长度是可以为 $0$ 的，也就说明你可以先删掉所有数，接着再添加一个 $1$，这种操作方法是合法的。

## Part 2: 思路
在这道题中，我们很容易就可以发现数组中每个数的顺序对最后结果没有任何影响，所以我们就可以先将数组排序。

接着，我们再做一个预处理，我们先开一个二维的动态数组，二维数组中的每个数组存重复的数，每个数组中的数都相同，不同数组的数都不同。

然后我们可以遍历二维数组，我们假设我们最后形成的排列的长度就是现在遍历到的那个数组中的数的值，在每次循环的时候算出最小值。

## Part 3: 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

ll T;
ll n, c, d;
ll a[200010];
vector<vector<ll> > book;
ll ans;

void init(){
    book.clear();
    ans = 0x3f3f3f3f;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        init();
        cin >> n >> c >> d;
        for(ll i = 1; i <= n; i++){
            cin >> a[i];
        }
        sort(a + 1, a + n + 1);
        vector<ll> ve;
        ll now = a[1];
        ve.push_back(now);
        for(int i = 2; i <= n; i++){
            if(a[i] != now){
                book.push_back(ve);
                ve.clear();
                now = a[i];
            }
            ve.push_back(a[i]);
        }
        book.push_back(ve);
        ve.clear();
        ll cnt1 = 0; // 重复
        ll cnt2 = 0; // 到现在为止有多少个数
        ans = d + c * n;
        for(int i = 0; i < book.size(); i++){
            cnt1 += book[i].size() - 1;
            cnt2 += book[i].size();
            ans = min(ans, cnt1 * c + (book[i][0] - i - 1) * d + (n - cnt2) * c);
        }
        cout << ans << endl;
    }
    return 0;
}
 
```

---

## 作者：qfpjm (赞：0)

# 题解

- 显然，想变为一个排列，$a$ 应该先去重，直接算花费，没有更优的花费了。

- 排序，方便处理。

- 显然，将一个没有重复数字的序列通过删数或添数变为一个排列，要么填补空缺，要么删掉多余的数。

- 我们可以枚举这个断点，对这个断电前面的进行填补操作，后面的全部删掉，花费可以 $O(1)$ 求出，取最小值即可。

- 最后，记得开 `long long`，代码不放了。

---

