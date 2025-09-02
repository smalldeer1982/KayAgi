# [ABC253G] Swap Many Times

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc253/tasks/abc253_g

$ 2 $ 以上の整数 $ N $ に対し、$ 1\ \leq\ x\ \lt\ y\ \leq\ N $ を満たす整数の組 $ (x,\ y) $ は $ \frac{N(N\ -\ 1)}{2} $ 個あります。

これらを辞書順で小さい順に並べたもののうち $ L $ 番目、$ L+1 $ 番目、$ \ldots $、$ R $ 番目のものをそれぞれ $ (x_1,\ y_1),\ \dots,\ (x_{R\ -\ L\ +\ 1},\ y_{R\ -\ L\ +\ 1}) $ とおきます。数列 $ A\ =\ (1,\ \dots,\ N) $ に対し、$ i\ =\ 1,\ \dots,\ R-L+1 $ の順に以下の操作を行います。

- $ A_{x_i} $ と $ A_{y_i} $ を入れ替える

操作後の $ A $ を求めてください。

なお、$ (a,\ b) $ が $ (c,\ d) $ よりも辞書順で小さいとは、以下のいずれかが成り立つことをいいます。

- $ a\ \lt\ c $
- $ a\ =\ c $ かつ $ b\ \lt\ d $

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ L\ \leq\ R\ \leq\ \frac{N(N-1)}{2} $
- 入力は全て整数

### Sample Explanation 1

$ 1\ \leq\ x\ \lt\ y\ \leq\ N $ を満たす整数の組を辞書順で小さい順に並べたもののうち $ 3,\ 4,\ 5,\ 6 $ 番目のものはそれぞれ $ (1,\ 4),\ (1,\ 5),\ (2,\ 3),\ (2,\ 4) $ です。 これらについて順に操作を行うと、$ A $ は次のように変化します。 $ (1,\ 2,\ 3,\ 4,\ 5)\ \rightarrow\ (4,\ 2,\ 3,\ 1,\ 5)\ \rightarrow\ (5,\ 2,\ 3,\ 1,\ 4)\ \rightarrow\ (5,\ 3,\ 2,\ 1,\ 4)\ \rightarrow\ (5,\ 1,\ 2,\ 3,\ 4) $

## 样例 #1

### 输入

```
5 3 6```

### 输出

```
5 1 2 3 4```

## 样例 #2

### 输入

```
10 12 36```

### 输出

```
1 10 9 8 7 4 3 2 5 6```

# 题解

## 作者：Erinyes (赞：6)

## 思路

考虑如下的一个序列：

$$1,2,3,4,5$$

我们把 $l=1,r=2\sim5$ 的操作都执行一遍，则原序列变为：

$$5,1,2,3,4$$

可以发现 $1\sim4$ 每个数都向后移了一位，第 $5$ 个数移到了第一个位置。

再试着把 $l=2,r=3\sim5$ 的操作都执行一遍，原序列变为：

$$5,4,1,2,3$$

发现同样满足刚才的性质，把 $2\sim3$ 每个数向后移一位，$4$ 移到第 $2$ 个位置。

我们分析一下对于 $n=5,l=3,r=8$ 需要进行的操作：

$$(1,4),(1,5),(2,3),(2,4),(2,5),(3,4)$$

发现 $l=2$ 的操作是完整的，即 $r$ 取遍所有合法的数。所以不难想到一个简单的思路：把完整的操作一起处理，再进行不完整的操作即可。

## 实现

首先不难发现对于一个 $l$，合法的 $r$ 是 $l+1\sim n$，所以每一个 $l$，共有 $n-l$ 个合法的 $r$。

```cpp
//记录完整操作的前缀和，用来后续二分查找
for(int i=1;i<=n;i++) sum[i]=sum[i-1]+n-i;
```
- 找到完整操作之前与之后的位置

```cpp
int lpos=lower_bound(sum+1,sum+n+1,l)-sum;
int rpos=lower_bound(sum+1,sum+n+1,r)-sum;
```
- 处理不完整的操作

既然我们已经找到两段的 $l$ 了，而每段的个数是 $\Theta(n)$ 级别的，所以直接暴力交换就可以了。

```cpp
//前
for(int i=1;i<=sum[lpos]-l+1;i++) swap(a[lpos],a[lpos+l-sum[lpos-1]+i-1]);
//后
for(int i=1;i<=r-sum[rpos-1];i++) swap(a[rpos],a[rpos+i]);
```
但是这里有一个小问题，如果题目给出的 $l$ 和 $r$ 所对应的操作的 $l$ 是相同的，即在一个块里，两段就会出现重叠，所以需要特殊处理。

```cpp
//其实比较类似于分块算法的处理
if(sum[lpos]>=r){
	//暴力交换
	for(int i=l;i<=r;i++) swap(a[lpos],a[lpos+i-sum[lpos-1]]);
	for(int i=1;i<=n;i++) cout<<a[i]<<' '; cout<<endl;
	return 0;
}
```


- 处理完整的操作

这里发现一个问题，单个完整操作也是 $\Theta(n)$，总共 $\Theta(n^2)$，不能接受。

所以考虑把多个完整操作一起处理。

回到刚才的序列 $1\sim5$，把 $l=1\sim3$ 的完整操作都执行一遍：

$$1,2,3,4,5 \longrightarrow 5,1,2,3,4 \longrightarrow 5,4,1,2,3 \longrightarrow 5,4,3,1,2$$

可以发现进行 $l=p\sim q$ 的完整操作就是把原序列 $p\sim q-1$ 每个数向后移动 $n-q+1$ 位，然后将 $q\sim n$ 每个数倒序放进 $p\sim p+(n-q)$ 每个位置里。

$$1,2,3,4,5$$

$$?,?,?,?,? \longrightarrow ?,?,?,1,2 \longrightarrow 5,4,3,1,2$$

```cpp
//p=x,q=x+tot-1
int x=lpos+1,tot=rpos-1-lpos;
for(int i=x;i+tot<=n;i++) b[i+tot]=a[i];
for(int i=x;i<=x+tot-1;i++) b[i]=a[n-(i-x+1)+1];
for(int i=x;i<=n;i++) a[i]=b[i];
```
## 代码

注意 $l$ 和 $r$ 都是 $\Theta (n^2)$ 级别的，有可能爆 `int`，所以要开 `long long`。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
int n,l,r;
int a[200005],b[200005],sum[200005];
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>l>>r;
    for(int i=1;i<=n;i++) a[i]=i;
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+n-i;
    int lpos=lower_bound(sum+1,sum+n+1,l)-sum;
    int rpos=lower_bound(sum+1,sum+n+1,r)-sum;
    if(sum[lpos]>=r){
        for(int i=l;i<=r;i++) swap(a[lpos],a[lpos+i-sum[lpos-1]]);
        for(int i=1;i<=n;i++) cout<<a[i]<<' '; cout<<endl;
        return 0;
    }
    for(int i=1;i<=sum[lpos]-l+1;i++) swap(a[lpos],a[lpos+l-sum[lpos-1]+i-1]);
    int x=lpos+1,tot=rpos-1-lpos;
    for(int i=x;i+tot<=n;i++) b[i+tot]=a[i];
    for(int i=x;i<=x+tot-1;i++) b[i]=a[n-(i-x+1)+1];
    for(int i=x;i<=n;i++) a[i]=b[i];
    for(int i=1;i<=r-sum[rpos-1];i++) swap(a[rpos],a[rpos+i]);
    for(int i=1;i<=n;i++) cout<<a[i]<<' '; cout<<endl;
    return 0;
}
```


---

## 作者：WaterSun (赞：5)

# 思路

首先，不难看出一个规律，就是对于一个序列 $a$，如果它将操作所有以 $x$ 为第一关键字的二元组，那么序列的 $a_{x \sim n}$ 将循环右移一位。（注意，在这里的 $x$ 指的是在 $1 \sim (n - 1)$ 中的任意一个定值）

那么，我们就可以将编号分别为 $l \sim r$ 的这些二元组分为三组：

1. $(x_1,y_1) \sim (x_1,n)$，其中 $(x_1,y_1)$ 为编号为 $l$ 的二元组。

2. $(x_1 + 1,x_1 + 2) \sim (x_2,n)$，其中 $(x_2,n)$ 为编号不大于 $r$ 的最后一个完整操作区间的最后一个二元组。（完整操作区间表示对于一个 $x$，$(x,x + 1) \sim (x,n)$ 都会被取到的二元组区间）

3. $(x_2 + 1,x_2 + 2) \sim (x_2 + 1,y_2)$，其中 $(x_2 + 1,y_2)$ 为编号为 $r$ 的二元组。

然后分别维护这三种情况即可：

1. 首先，定义 $sum_i = \sum_{j = 1}^{n - i}(n - j)$，那么，我们可以二分得出二元组 $(x_1,y_1)$，然后暴力维护 $(x_1,y_1) \sim (x_1,n)$ 即可。时间复杂度 $\Theta(n)$。

2. 由上文的规律，我们只需要将每种状态循环右移一位即可，时间复杂度 $\Theta(n \sqrt n)$，考虑优化。在这里先举一个[例子](https://www.luogu.com.cn/paste/hl0138yf)，那么我们可以用两个 `vector` $A,B$ 维护此过程（其中 $A$ 表示循环右移时最后的元素走到序列前面的元素，$B$ 表示循环右移时没有走到序列前面的元素），对于每一次循环右移，都会将 $B$ 中的最后一个元素放在 $A$ 的末尾，时间复杂度 $\Theta(\sqrt n)$。然后将 $A,B$ 拼起来得到当前序列 $a$。**需要注意的是，$B$ 的初始状态是将 $x_1 \sim n$ 放入，因为在 $x_1$ 之前的根本不会动。**

3. 将剩下的操作次数全部花光即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10;
int n,l,r;
int sum[N],arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void init(){//预处理 sum 数组 
	for (re int i = 1,k = n - 1;i < n;i++,k--) sum[i] = sum[i - 1] + k;
}

signed main(){
	n = read();
	l = read();
	r = read();
	init();
	for (re int i = 1;i <= n;i++) arr[i] = i;
	int a = lower_bound(sum + 1,sum + n/*注意这里只能不能写 + 1，因为 sum[n] = 0，加上后 sum 数组不有序无法二分*/,l) - sum;//找出 (x1,y1) 
	int b = a + l - sum[a - 1];
	int cnt = 1;
	while (cnt <= (r - l + 1) && b <= n){//暴力维护 (x1,y1) ~ (x1,n) 
		swap(arr[a],arr[b]);
		cnt++;
		b++;
	}
	int i = a + 1;
	vector<int> A,B;//维护中间完整段 
	for (re int j = i;j <= n;j++) B.push_back(arr[j]);
	while (sum[i] <= r && i < n){
		if (B.empty()) break;
		A.push_back(B.back());
		B.pop_back();
		i++;
	}
	for (auto x:A) arr[++a] = x;//更新新的序列 
	for (auto x:B) arr[++a] = x;
	cnt = r - sum[i - 1];
	for (int j = 1,k = i + 1;j <= cnt && k <= n;j++,k++) swap(arr[i],arr[k]);//暴力维护剩余的操作次数 
	for (re int i = 1;i <= n;i++) printf("%lld ",arr[i]);
	return 0;
}
```

---

## 作者：Elairin176 (赞：2)

[洛谷 Link](https://www.luogu.com.cn/problem/AT_abc253_g)   
[Atcoder Link](https://atcoder.jp/contests/abc253/tasks/abc253_g)    
## 前言
为啥题解清一色是找性质呢？其实这道题可以直接暴力 ds 的，就是复杂度劣一些。   
## 解法
我们注意到，一段形如 $(i,l),(i,l+1),\dots,(i,r)$ 的操作等价于对 $a_i$ 和 $a_l,a_{l+1},\dots,a_r$ 作循环右移。形式化地：   
- $a'_i=a_r$
- $a'_l=a_i$
- $a'_p=a_{p-1}(l<p\le r)$

那么我们对于这个操作直接上平衡树就行了，复杂度 $\mathcal{O}(n\log n)$。   
这里我采用 FHQ Treap 实现。这里仅展示循环移位部分，其他部分请读者自行实现：   

```cpp
ll s=0,l,r;
for(int i=1;i<=n;i++){
  s+=n-i;
  if(s>=lp){
    l=n-s+lp;r=n;
    if(s>=rp) r=n-s+rp;
    //i l~r
    int r1,r2,r3,r4,r5,r6;
    split(r1,r2,l-1,rt);
    split(r2,r3,r-l+1,r2);
    split(r2,r6,r-l,r2);
    split(r1,r4,i-1,r1);
    split(r4,r5,1,r4);
    //r1 -> 1~i-1  r4 -> i r5 -> i+1~l-1
    //r2 -> l~r-1 r6 -> r r3 -> r+1~n
    rt=merge(r1,r6);
    rt=merge(rt,r5);
    rt=merge(rt,r4);
    rt=merge(rt,r2);
    rt=merge(rt,r3);
    if(s<rp) lp=s+1;
    else break;
  }
}
```

---

## 作者：CQ_Bab (赞：2)

# 思路
~~这道题需要一定的代码能力~~。

我们首先能发现一个规律，就是对于每一个第一位的数字若为 $i$ 那么一共有 $n-i$ 个以 $i$ 开头的，那么我们就可以先把 $l$ 和 $r$ 分别以谁为开头几录下来，然后若开头相同直接变就行，若不相同则要分三步。

- 我们把以 $x$（就是 $l$ 的第一个数） 为开头，第二位为 $l\sim n$ 的直接变一下即可。

具体代码为这样。
```cpp
rep(i,l,n) swap(a[x],a[i]);
```

- 然后我们可以发现在中间可能会存在一些完整的变化，就是第一位为 $i$ 的所有二元组都被包含在其中，那么我们就要来找一下规律了。

当原序列为 $1\;2\;3\;4\;5$ 那么我们在将首位为 $1$ 的变化完之后就能得到一个序列 $5\;1\;2\;3\;4$ 那么规律不就来了吗。我们若将首位为 $i$ 的变化完，就是讲 $a_i\sim a_n$ 整体右移一位。

这里我们若直接暴力右移会超时，所以我们再来整体起来找规律，当我们原串为 $1\;2\;3\;4\;5$ 是我们将 $1,2$ 的全部变完，那么我们就可以得到一个为 $5\;4\;1\;2\;3$ 这不就是把后面的数提到前面去要变的次数个吗，然后在将剩下的往后放即可。

这里可能口述有一些难懂，这里参考一下代码和注释。
```cpp
rep(i,bg+1,eg-1) s[++cc]=a[n-cnt++];//先把后面的数存下来
int l=n-(eg-1-(bg+1)+1)-bg;//将前面要右移的长度算出来
int tot=bg+l;//找到要右移的数的最后一位
rep1(i,n,bg+cnt+1) a[i]=a[(tot--)];//将所有右移了
int bv=false;
rep(i,bg+1,eg-1) a[i]=s[++bv];//将之前存下的给出来
```
- 这里的第三个操作其实和第一个没有本质上的区别就是讲以 $y$ 为第一位的最后几个给和上面一样操作了即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
using namespace std ;
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n,l,r;
int cnt,bg,eg,now;
int yu1,yu2,a[500100];
int s[500100];
fire main() {
	cin>>n>>l>>r;
	rep1(i,n-1,1) {
		now+=i;
		cnt++;
		if(now>=l&&!bg) bg=cnt,yu1=l-(now-i);
		if(now>=r&&!eg) {
			eg=cnt;
			yu2=r-(now-i);
			break;
		}
	}
	rep(i,1,n) a[i]=i;
	if(eg==bg) {
		rep(i,bg+yu1,bg+yu2) swap(a[bg],a[i]);
		rep(i,1,n) cout<<a[i]<<" ";
	} else {
		rep(i,bg+yu1,n) swap(a[bg],a[i]);
		int cnt=0,cc=0;
		rep(i,bg+1,eg-1) s[++cc]=a[n-cnt++];
		int l=n-(eg-1-(bg+1)+1)-bg;
		int tot=bg+l;
		rep1(i,n,bg+cnt+1) a[i]=a[(tot--)];
		int bv=false;
		rep(i,bg+1,eg-1) a[i]=s[++bv];
		rep(i,eg+1,eg+yu2) swap(a[eg],a[i]);
		rep(i,1,n) cout<<a[i]<<" ";
	}
	return false;
}
```

---

## 作者：spire001 (赞：1)

## AT_abc253_g 题解

### 前言
本题最大的难度在于代码能力。。。

### 分析
首先发现这个排名 $k$ 的 $(x,y)$ 是可以求的。

然而有左右区间的信息没有太大帮助，所以继续挖掘性质。

发现如果把 $(x,y)$ 的第一个关键字固定的话，那么交换是有规律的。

比如说只交换 $(x, x + 1), (x, x + 2), \cdots, (x, n)$ 的话，我们直接把序列中最后一个数提到前面来，然后把前面的数补到后面去就可以了。

如果是第一个关键字处在某一个范围呢？

如果我们能把这个操作在一次复制中做出来这个题就结束了，很容易发现如果 $(x,y)$ 的 $x$ 在 $[l,r]\cap \Z$ 范围中，那么就把最后 $r-l+1$ 个数提前并翻转就可以了，后面的数复制照旧。

### 代码实现

首先我们需要求 $(x,y)$ 的排名。

采取比好写的倍增法，先跳到最后一个不超过排名的 $x$ 然后确定 $y$。

这部分的代码：

```cpp
PII getk(const LL order)
{
  int pos = 0;

  for (int i = 18; i >= 0; i--)
  {
    if (pos + (1 << i) > n) // 越界判断
      continue;
    int tp = pos + (1 << i);
    if ((LL)(n * 2 - tp - 1) * tp / 2 < order) // 等差数列求和
      pos = tp;
  }

  LL tmp = order - (LL)(n * 2 - pos - 1) * pos / 2;
  pos++; // 下一个数的 first 才是
  return mp(pos, pos + tmp); // 要记得第一个 second 是 first + 1 而不是 1
}
```

然后把 $l,r$ 的不完整的部分暴力交换，中间的完整 $x$ 部分一步搞定即可。

复制时的下标判断有点恶心，但复杂度不是问题，当模拟做即可。

时空复杂度均为线性。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <numeric>
#define mp make_pair

using namespace std;

constexpr int N = 200010;

typedef long long LL;
typedef pair<int, int> PII;

int n, a[N];
LL l, r;

PII getk(const LL order)
{
  int pos = 0;

  for (int i = 18; i >= 0; i--)
  {
    if (pos + (1 << i) > n) // 越界判断
      continue;
    int tp = pos + (1 << i);
    if ((LL)(n * 2 - tp - 1) * tp / 2 < order) // 等差数列求和
      pos = tp;
  }

  LL tmp = order - (LL)(n * 2 - pos - 1) * pos / 2;
  pos++; // 下一个数的 first 才是
  return mp(pos, pos + tmp); // 要记得第一个 second 是 first + 1 而不是 1
}

int b[N];
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> l >> r;

  iota(a + 1, a + n + 1, 1); // 初始化

  PII tl = getk(l), tr = getk(r); // 左右边界

  if (tl.first == tr.first) // 两个边界相等，直接暴力
  {
    for (LL i = l; i <= r; i++) // 这个地方我写的其实是 log 的，但是你但凡看了一眼题目就知道怎么优化成线性的。。。
    {
      PII tmp = getk(i);
      swap(a[tmp.first], a[tmp.second]);
    }
    memcpy(b, a, sizeof b);
  }
  else
  {
    for (int i = tl.second; i <= n; i++)
      swap(a[tl.first], a[i]); // 交换
    tl.first++;
    int to_get = tr.first - tl.first;
    memcpy(b + 1, a + 1, sizeof(int) * (tl.first - 1)); // 复制
    memcpy(b + tl.first, a + n - to_get + 1, sizeof(int) * (to_get));
    memcpy(b + tl.first + to_get, a + tl.first, sizeof (int) * (n - tl.first - to_get + 1)); // 下标很细节，需要仔细斟酌
    reverse(b + tl.first, b + tl.first + to_get); // 翻转
    for (int i = tr.first + 1; i <= tr.second; i++)
      swap(b[tr.first], b[i]); // 交换
  }

  for (int i = 1; i <= n; i++)
    cout << b[i] << " \n"[i == n]; // 输出

  return 0;
}
```

---

