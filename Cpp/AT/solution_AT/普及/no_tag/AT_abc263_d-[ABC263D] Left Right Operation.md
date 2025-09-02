# [ABC263D] Left Right Operation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc263/tasks/abc263_d

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。

あなたは以下の連続する操作をちょうど一度だけ行います。

- 整数 $ x\ (0\leq\ x\ \leq\ N) $ を選ぶ。$ x $ として $ 0 $ を選んだ場合何もしない。 $ x $ として $ 1 $ 以上の整数を選んだ場合、$ A_1,A_2,\ldots,A_x $ をそれぞれ $ L $ で置き換える。
- 整数 $ y\ (0\leq\ y\ \leq\ N) $ を選ぶ。$ y $ として $ 0 $ を選んだ場合何もしない。 $ y $ として $ 1 $ 以上の整数を選んだ場合、$ A_{N},A_{N-1},\ldots,A_{N-y+1} $ をそれぞれ $ R $ で置き換える。

操作後の $ A $ の要素の総和として考えられる最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ -10^9\ \leq\ L,\ R\leq\ 10^9 $
- $ -10^9\ \leq\ A_i\leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ x=2,y=2 $ として操作をすると、数列 $ A\ =\ (4,4,0,3,3) $ となり、要素の総和は $ 14 $ になります。 これが達成可能な最小値です。

### Sample Explanation 2

$ x=0,y=0 $ として操作をすると、数列 $ A\ =\ (1,2,3,4) $ となり、要素の総和は $ 10 $ になります。 これが達成可能な最小値です。

### Sample Explanation 3

$ L,R,A_i $ は負であることがあります。

## 样例 #1

### 输入

```
5 4 3
5 5 0 6 3```

### 输出

```
14```

## 样例 #2

### 输入

```
4 10 10
1 2 3 4```

### 输出

```
10```

## 样例 #3

### 输入

```
10 -5 -3
9 -6 10 -1 2 10 -1 7 -15 5```

### 输出

```
-58```

# 题解

## 作者：allenchoi (赞：10)

### 科技：  
前缀数组~~和脑子~~  
### 思路：   
先令 $x+y\le N$ ，并定义前缀和数组 $s$ 。  
于是乎题意就变成了：  
定义 $f(x,y)=L\times x+R\times y+s_{N-y}-s_x$ ，其中 $x,y$ 为非负整数，求 $f_{x,y}$ 的最小值。  
枚举 $x,y$ 是 $O(N^2)$ 的，肯定不行。  
考虑之枚举 $x$ ，那么 $L\times x-s_x$ 是定值，最小化 $R\times y+s_{N-y}$ 即可。由于 $x+y\le N$ 所以 $y$ 的取值范围为 $[0,N-x]$ ，设前缀数组 $minn_i$ 表示 $\min_{j=0}^{i}R\times j+s_{N-j}$ ，这个显然可以 $O(N)$ 预处理，于是答案就变成了 $\min_{i=0}^{N}L\times x-s_x+minn_{N-i}$ ，时间复杂度 $O(N)$ 。   
### 代码：  
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n,l,r,a[N];
long long s[N],minn[N],ans;
int main()
{
	cin >> n >> l >> r;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	ans = 1e17,minn[0] = s[n];
	for(int i = 1;i <= n;i++) minn[i] = min(minn[i - 1],1LL * i * r + s[n - i]);
	for(int i = 0;i <= n;i++) ans = min(ans,1LL * i * l - s[i] + minn[n - i]);
	cout << ans << endl;
	return 0; 
}
```

---

## 作者：TigerTanWQY (赞：6)

# AtCoder ABC 263 D 题解

## 前言

本蒟蒻的第一篇题解，大佬勿喷 QwQ

---

## 传送门们

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc263_d)

[AtCoder 传送门](https://atcoder.jp/contests/abc263/tasks/abc263_d)

[更好的阅读体验？](https://www.cnblogs.com/TigerTanWQY/p/18012594)

---

## 正文

设有 $x$ 使得 $x\leq k$ 时，令 $f(k)$ 为对 $A'$ 进行运算后 $A'=(A_1,A_2,\ldots,A_k)$ 的最小和。

同理，对于 $y$ 使得 $y\leq k$ 时，令 $g(k)$ 为对 $A''$ 进行运算后 $A''=(A_{N-k+1},\ldots,A_N)$ 的最小和。

如果我们能求出 $f(0),f(1),\ldots,f(N),g(0),g(1),\ldots,g(N)$，那么答案就是 $\min(f(i)+g(N-i))$。

我们设 $f(0)=0$。要想求得 $f(k+1)$，我们需要先求得 $f(k)$。这取决于是否有 $x<k+1$。

### 分类讨论

- 如果 $x<k+1$，则最小和为 $f(k)+A_{k+1}$。

- 如果 $x=k+1$，则最小和为 $L(k+1)$。

因此，我们可以求得 $f(k+1)=\min(f(k)+A_{k+1},L(k+1))$。

同理可求得 $g(k)$，时间复杂度 $\mathrm{O}(N)$。

---

## AC Code

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, l, r;
    cin >> n >> l >> r;
    long long pre = 0, ans = 1LL * r * n;
    for(int i = 1, a; i <= n; ++i) {
        cin >> a;
        pre = min(pre + a, 1LL * i * l);
        ans = min(ans, pre + 1LL * (n - i) * r);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：WaterSun (赞：4)

# 思路

首先，不难发现最终的序列一定是形如下面的序列：

$$
l,\dots,l,a_i,a_{i + 1},\dots,a_{i + j},r,\dots r
$$

那么，我们就可以将其分为三段，每段都单独维护。

首先，对于第一段，我们可以枚举出最后一个 $l$ 的位置 $x$，那么和为 $x \times l$。

对于第二段显然可以用前缀和维护，但是有一个问题，我们还不知道这一段的末尾位置在哪里。换而言之，我们需要确定 $r$ 的起始位置。

那么，对于每一个位置 $i$，我们都可以 $\Theta(1)$ 查询出将 $i \sim n$ 全都修改为 $r$ 能够使序列变小多少，记作 $d_i$。

因此，我们可以用一个 `pair` 数组 $mx$ 维护 $d_i$ 的后缀最大值，那么 `mx.fst` 记录的是后缀最大值的值，`ms.snd` 记录的是后缀最大值的位置。

那么，要想使答案最小，我们在枚举 $i$ 时，就要是 $r$ 对答案的贡献小，即选择一个位置 $j$ 使得 $d_j$ 最大，那么，这个操作，我们可以直接使用 $mx$ 来查询。

最后所有求出的值，取 $\min$ 即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10,inf = 1e18 + 10;
int n,x,y,ans = inf;
int arr[N],sp[N],sn[N];//sp 为前缀和，sn 为后缀和 
pii mx[N];

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
	x = read();
	y = read();
	for (re int i = 1;i <= n;i++){
		arr[i] = read();
		sp[i] = sp[i - 1] + arr[i];
	}
	for (re int i = n;i;i--) sn[i] = sn[i + 1] + arr[i];
	mx[n + 1] = {0,n + 1};
	for (re int i = n;i;i--){
		int t = sn[i] - (n - i + 1) * y;
		if (mx[i + 1].fst < t) mx[i] = {t,i};
		else mx[i] = mx[i + 1];
	}
	for (re int i = 0;i <= n;i++){
		int id = mx[i + 1].snd;
		int sum = sp[id - 1] - sp[i] + i * x + (n - id + 1) * y;
		ans = min(ans,sum);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_qingshu_ (赞：2)

# 题意：

给定一个长度为 $N$ 的数列。你可以进行两种操作。

 - 选择数列的一个前缀数组，最后一项下标为 $x$，把它们全部变成 $l$。
 
 - 选择数列的一个后缀数组，开始一项下标为 $y$，把它们全部变成 $r$。
 
 询问操作后数列总和最小值。
 
# 思路：

考虑动态规划，定义两个 dp 数组 $lefmin,rigmin$。

我们把最后的结果视为 $l,l,l,l \dots a_{x+1},a_{x+2},\dots,a_{y-1},r,r,r$。我们把他们分成 $a_1\sim a_i$ 与 $a_{i+1} \sim a_n$ 两组，这两组以 $i$ 为分界，满足 $x\le i\le y$。

考虑转移，先考虑前缀数组。显然我们存在当前位置不被覆盖和被覆盖两种情况，我们分类讨论：

- 当前位置被覆盖：

	那么说明该位置前全部被覆盖，所以值为 $i\times l$。
    
- 当前位置未被覆盖：

	那么我们可以无视前面究竟有没有被覆盖，只需要用最小值加上 $a_i$ 就好了。
    
所以对于每一个点的前缀数组的最小值为:

$$lefmin_i=\min(lefmin_{i-1}+a_i,i\times l)$$

后缀数组同理，改变一下覆盖范围就好了。

最后用 $O(N)$ 去遍历一下 $i$ 点。

# Code：

```cpp

#include<bits/stdc++.h>
using namespace std;
long long n,l,r;
int a[5200010];
long long lefmin[5200010],rigmin[5200010];
long long ans;
int main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++){
		cin>>a[i];ans+=a[i];
	}
	for(long long i=1;i<=n;i++){
		lefmin[i]=min(lefmin[i-1]+a[i],i*l);
		rigmin[(n-i+1)]=min(rigmin[(n-i+1)+1]+a[(n-i+1)],i*r);
	}
	for(int i=0;i<=n;i++){
		ans=min(ans,lefmin[i]+rigmin[i+1]);
	} 
	cout<<ans;
}
```

---

## 作者：kczw (赞：1)

# 题意分析
让我们用 $l$ 和 $r$ 替换 $a$ 数列的前缀和后缀，并且让 $a$ 数列的总和尽可能小。

# 思路
那为了让结果变小，在替换前、后缀时，我们首先要保证替换后的前缀和与后缀和的总和小于原数组被替换数的总和，否则替换将没有意义。最后我们只要枚举替换前缀和和替换后缀和时对答案的贡献，就可以得出答案。

在实现思路的过程中，我们可以存储前 $i$ 位替换前缀和的最优策略的值，整体思路是动规，公式为 $Ldp_i=\min(Ldp_{i-1}+A_i,L\times i)$，意为是在覆盖 $i$ 的前缀与不覆盖 $i$ 中择更优。
然后在枚举后缀的同时就可以枚举答案，枚举后缀的公式与上文基本一致 $Rdp_i=\min(Rdp_{i-1}+A_i,R\times i)$。
# 实现
```cpp
#include<iostream>

#define int long long

#define N 200005

using namespace std;

int ans=1e18,n,l,r,a[N],L[N],R[N];

signed main()
{
	scanf("%lld%lld%lld",&n,&l,&r);
	
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		
		L[i]=min(L[i-1]+a[i],l*i);
	}
	for(int i=n;i>=1;i--)
	{
		R[i]=min(R[i+1]+a[i],r*(n-i+1ll));
		
		ans=min(ans,L[i-1]+R[i]);
		
	}
	ans=min(ans,L[n]);//循环中的枚举漏掉了L[n]
	
	printf("%lld",ans);	
	
	return 0;
}
```


---

## 作者：chengning0909 (赞：1)

# abc 263 d

## 题意

给定一个长度为 $N$ 的序列 $A$。有两种操作，各做一次：

1. 选择一个整数 $x \ (0 \le x \le N)$，将 $A_1, A_2, \dots , A_x$ 替换为 $L$。

2. 选择一个整数 $y \ (0 \le y \le N)$，将 $A_N, A_{N - 1}, \dots , A_{N - y + 1}$ 替换成 $R$。

请你求出操作后的 $A$ 序列的最小数字和。

## 思路

首先，我们可以想到：我们选择改变的两个前缀和后缀是不会重叠的。

因为如果重叠了，就会有一个覆盖另一个，完全没有必要。

那么，我们可以把答案分成两段，$1 \sim i$ 和 $i + 1 \sim N$。

我们就可以分别求出 $1 \sim i$ 的最小数字和，把它记作 $g_i$。

那么就有 $g_i = \min(g_{i - 1} + A_i, i \times L)$，$g_{i - 1} + A_i$ 是不变为 $L$ 的情况，$i \times L$ 是前 $i$ 个全变成 $L$ 的情况。

同理，我们将 $i \sim N$ 的最小数字和记作 $f_i$。

那么就有 $f_i = \min(f_{i + 1} + A_i, (N - i + 1) \times R)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, l, r, a[N];
long long g[N], f[N], ans = 1e18;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> l >> r;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    g[i] = min(g[i - 1] + a[i], 1ll * i * l);
  }
  for (int i = n; i >= 1; i--) {
    f[i] = min(f[i + 1] + a[i], 1ll * (n - i + 1) * r);
  }
  for (int i = 0; i <= n; i++) {
    ans = min(ans, g[i] + f[i + 1]);
  }
  cout << ans;
  return 0;
}
```

---

