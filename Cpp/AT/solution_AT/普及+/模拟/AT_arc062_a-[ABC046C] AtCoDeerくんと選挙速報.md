# [ABC046C] AtCoDeerくんと選挙速報

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc046/tasks/arc062_a

シカのAtCoDeerくんは選挙速報を見ています。選挙には二人の候補高橋くんと青木くんが出ています。速報では、現在の二人の得票数の比が表示されていますが、得票数そのものは表示されていません。AtCoDeerくんは $ N $ 回画面を見て、 $ i(1≦i≦N) $ 回目に見たときに表示されている比は $ T_i:A_i $ でした。ここで、AtCoDeerくんが選挙速報の画面を$ 1 $回目に見た段階で既にどちらの候補にも少なくとも一票は入っていたことがわかっています。 $ N $ 回目に画面を見たときの投票数(二人の得票数の和)として考えられるもののうち最小となるものを求めてください。ただし、得票数が途中で減ることはありません。

## 说明/提示

### 制約

- $ 1≦N≦1000 $
- $ 1≦T_i,A_i≦1000\ (1≦i≦N) $
- $ T_i $ と $ A_i $ は互いに素 $ (1≦i≦N) $
- 答えが $ 10^{18} $ 以下になることは保証されている

### Sample Explanation 1

二人の得票数が $ 2,3 $ -&gt; $ 3,3 $ -&gt; $ 6,4 $ と動くと投票数は $ 10 $ になって、これが最小値です。

### Sample Explanation 2

一度画面を見てからもう一度画面を見るまでに一票も入ってないことがありえます。

## 样例 #1

### 输入

```
3
2 3
1 1
3 2```

### 输出

```
10```

## 样例 #2

### 输入

```
4
1 1
1 1
1 5
1 100```

### 输出

```
101```

## 样例 #3

### 输入

```
5
3 10
48 17
31 199
231 23
3 2```

### 输出

```
6930```

# 题解

## 作者：Ezio__Auditore (赞：4)

## AT2140 [ARC062A] AtCoDeerくんと選挙速報
[[Statment]](https://www.luogu.com.cn/problem/AT2140)

$Date:\ Dec.\ 10th$

---
#### 题意：
 &emsp;&emsp;Deer 们的 AtCoDeer 选举正在进行。高橋くん和青木くん这两位候选人正在竞选中。 公告显示了两个人当前得票数的比率，但不显示确切的得票数。 AtCoDeer 看了 $n$ 次公告屏幕，当他第 $i$ 次看屏幕时显示的比率为 $T_i$：$A_i$ ($A_i, T_i$ 互质)。当 AtCoDeer 第 $1$ 次看到选举公告屏幕时，两位候选人都已经拥有至少一票。 AtCoDeer 想知道第 $n$ 次看屏幕时，最小可能的票数（两个人获得的票数之和）。但是请注意，获得的票数不会在中途减少。
 
P.S.原翻译有误，故在此写出完整题面，建议替换原翻译。
 
---

#### 思路：

&emsp;&emsp;设 $A$，$B$ 分别是上一轮结束时满足只前所有比例的高桥君和青木君的得票，本轮要满足的比例是 $a : b$。

&emsp;&emsp;由于票数满足比例关系，所以**最小化当前的票数总和就相当于最小化各自的票数**。
即只要让本论的总得票尽可能小，就一定是让 $A$, $B$ 分别最小的最优方案。

所以题意变成了：

&emsp;&emsp;**给出两个数 $A$， $B$。只可以对 $A$，$B$ 进行加操作，使其满足 $A$ ：$B$ = $a$ : $b$ 且操作后 $A$， $B$ 最小。**

- 为了满足比例， 我们先让 A 为 a 的倍数, B 为 b 的倍数。
这一步可以通过 $A = a \times \lceil \frac{A}{a} \rceil$, 
$B = b \times \lceil \frac{B}{b} \rceil$ 做到。

&emsp;然后比较 $\frac{A}{a}$ 和 $\frac{B}{b}$ 的大小：
- 若 $\frac{A}{a} < \frac{B}{b}$ 则说明 $A$ 偏小， 令 $A = \frac{B}{b} \times a$, 

- 否则说明 $B$ 偏小， 令 $B = \frac{A}{a} \times b$。

&emsp;这样即可满足 $A : B = a : b$，且 $A$, $B$ 最小。


&emsp;&emsp;按以上策略操作，保证每一轮得票数最少，重复 $n$ 次后仍是最小。
所以只要每一次继承上一轮结束时的 $A$, $B$， 完成 $n$ 次上述问题后，$A + B$ 即为最小答案。

复杂度 $O(n)$。

---
### Code: 
---

```cpp
#include <bits/stdc++.h>

template<class _Tp = int> _Tp read() {
  _Tp w = 0;
  bool f = 0;
  char ch = getchar();
  while (!isdigit(ch)) f |= ch == '-', ch = getchar();
  while (isdigit(ch)) w = (w << 3) + (w << 1) + (ch ^ 48), ch = getchar();
  return f ? -w : w;
}
typedef long long ll; // 题目保证 ans <= 1e18 注意开 long long
int n;
ll A = 1, B = 1;
int a, b;
int main() {
  auto _ceil = [](ll A, ll a) -> ll { return (A + a - 1) / a; }; // 实现 A / a 后向上取整的函数
  n = read();
  while (n--) {
    a = read(), b = read();
    A = a * _ceil(A, a);
    B = b * _ceil(B, b);
    if (A / a > B / b) {
      B = A / a * b;
    } else
      A = B / b * a;
  }
  printf("%lld\n", A + B);
  return 0;
}

```

---

## 作者：猜一猜我是谁 (赞：0)

# 思路
这道题翻译有问题，不过楼上已经说了正确的翻译，所以这里就不再赘述了。

显然，要使票数总和最小，肯定先要两个人的得票数最小。所以我们可以设两个变量 $u,v$ 作为目前两个人的得票数然后在每一步中满足 $u:v=T_i:A_i$。

先把 $u$ 和 $v$ 都分别变成 $T_i$ 和 $A_i$ 的倍数。因为题目要求票数不会减少，所以 $u$ 和 $v$ 应变为大于它们的最小的 $T_i$ 或 $A_i$ 的倍数。所以这一步要 $u=T_i\times\left\lceil\dfrac{u}{T_i}\right\rceil,v=A_i\times\left\lceil\dfrac{v}{A_i}\right\rceil$（注：表示 $\left\lceil\dfrac{u}{T_i}\right\rceil$ 方法是：$(u-1)/T_i+1$，细想一下就能明白）。

接着比较 $\dfrac{u}{T_i}$ 和 $\dfrac{v}{A_i}$ 的大小。如果第一个小，那么说明 $\dfrac{u}{T_i}$ 的比值小，根据比例的基本性质，$u=\dfrac{v\times T_i}{A_i}$。否则，同理 $v=\dfrac{u\times A_i}{T_i}$。

最后的答案即 $u+v$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t[1005],a[1005];
long long ceilll(long long u,long long v){//计算向上取整
    return (u-1)/v+1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>t[i]>>a[i];
    long long u=t[1],v=a[1];//先赋值为两人第一次的得票数
    for(int i=2;i<=n;i++){
        u=t[i]*ceilll(u,t[i]);v=a[i]*ceilll(v,a[i]);//把 u 和 v 分别变成大于它们的最小的 t[i] 和 a[i] 的倍数
        if(u/t[i]<v/a[i]) u=v/a[i]*t[i];
        else v=u/t[i]*a[i];
    }
    cout<<(u+v)<<endl;
}
```

---

