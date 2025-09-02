# [ABC286D] Money in Hand

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc286/tasks/abc286_d

高橋君は $ N $ 種類の硬貨をそれぞれ何枚か持っており、 具体的には、$ 1\leq\ i\leq\ N $ について $ A_i $ 円硬貨を $ B_i $ 枚持っています。

高橋君が現在持っている硬貨を用いて、（お釣りが出ないように）ちょうど $ X $ 円を支払うことができるか判定してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 50 $
- $ 1\leq\ X\leq\ 10^4 $
- $ 1\leq\ A_i\leq\ 100 $
- $ 1\leq\ B_i\leq\ 50 $
- $ A_i $ はすべて異なる。
- 入力はすべて整数
 
### Sample Explanation 1

高橋君は $ 2 $ 円硬貨を $ 3 $ 枚、$ 5 $ 円硬貨を $ 6 $ 枚持っています。 このうち、$ 2 $ 円硬貨を $ 2 $ 枚、$ 5 $ 円硬貨を $ 3 $ 枚用いることでちょうど $ 2\times\ 2+5\times\ 3=19 $ 円を支払うことができます。 よって、`Yes` を出力します。

### Sample Explanation 2

持っている硬貨をどのように組み合わせてもちょうど $ 18 $ 円を支払うことはできません。 よって、`No` を出力します。

### Sample Explanation 3

$ 1 $ 枚も使用しない硬貨が存在しても構いません。

## 样例 #1

### 输入

```
2 19
2 3
5 6```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 18
2 3
5 6```

### 输出

```
No```

## 样例 #3

### 输入

```
3 1001
1 1
2 1
100 10```

### 输出

```
Yes```

# 题解

## 作者：__Allen_123__ (赞：12)

### 题意简述

- 有 $n$ 种纸币，其中对于第 $i(1\le i\le n)$ 种纸币，它的面值是 $a_i$ 元，我们有 $b_i$ 张这种纸币。
- 请求出在不找零的情况下，用这些纸币能否**正好**付 $x$ 元，如果能则输出 `Yes`，不能则输出 `No`。
- $1 \le n \le 50, 1\le x \le 10^4, 1\le a_i \le 100, 1\le b_i\le 50$。

### 题目分析

仔细看题可以看出，本题与动态规划中的多重背包问题比较相似，具体我们可以这样实现：

我们可以创建一个二维的数组 $f$，这个数组的每一个下标中存放一个布尔值。对于每一个下标 $i, j$，$f_{i, j}$代表使用前 $i$ 种纸币，不找零的情况下能否正好付 $j$ 元。那么问题就转化为了求 $f_{n, x}$ 的布尔值，也就是使用这全部的 $n$ 种纸币，不找零的情况下能否正好付 $x$ 元。

那么如何得到这个答案呢？

首先，我们应设计一个最初状态。显而易见地，在我们不使用任何纸币的情况下，能付的钱数只有 $0$ 元，所以我们设计的最初状态就是将 $f_{0, 0}$ 设置为 true，其他均设置为 false。

其次，我们应该设置 $n$ 个阶段，对于第 $i$ 个阶段，我们用一个变量 $j$ 枚举从 $0$ 到 $b_i$ 的每一个数，代表使用了 $j$ 张这种纸币。我们再使用一个变量 $k$ 从 $0$ 枚举到 $x$，验证在前面的基础上使用 $j$ 张该种纸币的时候，能否正好付 $k$ 元。容易得到，为了在前面的基础上使用 $j$ 张这种纸币能正好付 $k$ 元，应该使得 $f_{i-1, k - a_i\times j}$ 为真（即在加入这些纸币之前能正好付 $k-a_i\times j$ 元），才能使 $f_{i, k}$ 为真。

最后，在第 $n$ 个阶段结束以后，我们就可以得出 $f_{n, x}$ 的值，按要求输出即可。

最坏时间复杂度 $O(n\times b_i\times x)$，这种做法不会超时。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define Yes cout << "Yes"
#define No cout << "No" // 方便答案输出
const int MAXX = 1e4 + 5, MAXN = 55;
int n, x, a[MAXX], b[MAXX];
bool dp[MAXN][MAXX]; // 第 1 维最大下标为 n，第 2 维最大下标为 x
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> x;
	for(int i = 1;i <= n;i++){
		cin >> a[i] >> b[i];
	}
	dp[0][0] = 1; // 设计初始状态
	for(int i = 1;i <= n;i++){
		for(int j = 0;j <= b[i];j++){
			for(int k = 0;k <= x;k++){ // 三重循环，前面有提到
				if(k >= a[i] * j && dp[i - 1][k - a[i] * j]){ // 前一个条件防止越界，后一个条件前文有提到
					dp[i][k] = 1;
				}
			}
		}
	}
	if(dp[n][x]){ // 求出最终答案
		Yes;
	}
	else{
		No;
	}
	return 0;
}
```

---

## 作者：yemuzhe (赞：2)

### 简化题意

- 有 $N$ 个物品，有 $B _ i$ 个第 $i$ 种物品，第 $i$ 种物品的体积为 $A _ i$。
- 问是否能从中选出若干个物品的总和为 $X$？如果可以输出 `Yes`，不行输出 `No`。
- $1 \le N \le 50, 1 \le X \le 10 ^ 4, 1 \le A _ i \le 100, 1 \le B _ i \le 50$。

### 解题思路

我们可以把这道题看成一个多重装箱问题：有 $N$ 种物品，第 $i$ 种物品的体积为 $A _ i$，有 $B _ i$ 个第 $i$ 种物品，求能否选出若干个物品使得这些物品的体积和为 $X$。

我们设 $f[i][j]$ 为从前 $i$ 种物品中选出若干个物品使得这些物品的体积和为 $X$，$f[i][j] = 1$ 则可以，$f[i][j] = 0$ 则不行，起初 $f[0][0] = 1$，其它都等于 $0$。则 $f[i][j] = f[i - 1][j - A _ iB _ i] \big | f[i - 1][j - A _ i(B _ i - 1)] \big | \cdots \big | f[i - 1][j - A _ i] \big | f[i - 1][j]$，其中 $|$ 是逻辑或。这代表着如果可以在前 $i - 1$ 种物品的基础上选出 $0 \sim B _ i$ 个 $A _ i$ 来得到 $j$，那么 $f[i][j] = 1$；否则 $f[i][j] = 0$。

我们可以考虑优化。首先，类似多重背包，$j$ 倒序循环 $B _ i$ 次 $f[i][j] = f[i][j] \big | f[i][j - A _ i]$ 可以得到与上面相同的效果。然后可类似背包地倒序循环 $j$，可舍去第一维 $i$。

于是我们对于每一个 $i$ 可执行 $B _ i$ 次如下操作：

>  从 $X$ 到 $A _ i$ 倒序循环 $j$，然后令 $f[j] = f[j] \big | f[j - 1]$。

这样，我们得到求解此题的方法。时间复杂度为 $\text O \big (X \sum B _ i \big)$，空间复杂度 $\text O (X)$。

### AC Code

```cpp
#include <cstdio>
#define M 10005
using namespace std;

int n, m, a, b, f[M] = {1}; // f[0] = 1

int main ()
{
    scanf ("%d%d", &n, &m);
    while (n --)
    {
        scanf ("%d%d", &a, &b);
        while (b --) // 循环 B[i] 次
        {
            for (int i = m; i >= a; i --) // 倒序循环
            {
                f[i] |= f[i - a]; // f[i] = f[i] | f[i - a[i]]
            }
        }
    }
    puts (f[m] ? "Yes" : "No"); // 如果 f[m] = 1，那么可以选出若干个物品的总和为 m；否则不行
    return 0;
}
```

---

## 作者：Neil_Qian (赞：2)

# [ABC286D] Money in Hand 题解
数学化题意：给你 $n$ 个数字，每个数字是 $a_i$，可以用 $b_i$ 次，问是否可以凑出给定的 $x$。

很容易发现，$b$ 个 $a$ 可以当成单独的数进行处理。所以现在问题变成用 $n$ 个数组合出 $x$。

对于这种问题我们考虑动态规划。先说状态，很简单，$dp_i$ 表示 $i$ 是否能被凑出来。再说转移，对于数 $a$，对于 $i\in[a,x]$，有 $dp_i=dp_{i-a}$，实现时可以使用或运算，即如果 $i-a$ 可以被凑出来，那么再加上一个 $a$ 即可凑出 $i$。初始条件 $dp_0=1$，都能理解。时间复杂度 $O(n\times b\times x)$，可以通过。

但是，有一个细节。如果在转移的时候 $i$ 从小到大枚举，对于一个数 $a$，观察以下效果： $dp_0=1\to dp_a=1\to dp_{2\times a}=1\to\dots$，这样，一个 $a$ 却达到了无数个 $a$ 的效果。因此我们要倒着枚举 $i$，这样就不会重复使用 $a$ 了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a,b;bool dp[10002];//dp数组
int main(){
	scanf("%d%d",&n,&x),dp[0]=1;//初始化
	while(n--){
		scanf("%d%d",&a,&b);//读入
		while(b--)for(int j=x;j>=a;j--)dp[j]|=dp[j-a];//变成b个->转移
	}
	return printf("%s\n",(dp[x]?"Yes":"No")),0;//输出
}
```

你以为这篇文章完了吗？显然没有！在枚举每一个数是否使用的时候，会发现，对于相等的数，每个数不管是否使用的情况如何，只要使用的个数相同，都是一样的，和都是 $a\times y$，其中 $y$ 是使用的个数。

我们可以使用二进制的方法，枚举使用 $1,2,4,8,\dots$ 个 $a$，最后会剩下一个数，在转移这个数的数量的 $a$ 即可。这就是二进制优化背包。具体代码，可参考下面的链接（我以前的文章，格式不太对，但还能看）。由于原来枚举 $b$ 个现在变成了对数级别，所以时间复杂度为 $O(n\times x\times \log(b))$，时间更优。不过对于本题 $b\le50$ 没有太大意义。

[https://www.luogu.com.cn/blog/Neil-Qian/er-jin-zhi-you-hua-bei-bao](https://www.luogu.com.cn/blog/Neil-Qian/er-jin-zhi-you-hua-bei-bao)

此题由于不需要二进制优化，所以我只写了朴素动态规划，不过上面的这道题更难，相信你可以写成优化版本的代码。

---

## 作者：12345678hzx (赞：2)

## 题目大意
有 $n$ 种纸币，第 $i$ 种纸币面值为 $a_i$ 元，有 $b_i$ 张。问能否不找零完整地付 $m$ 元。 
## 思路
这一题明显是道多重背包的题目，对于每张纸币只有选与不选两种状态，所以将每张纸币看成一个物品，再用背包问题求解就行了，时间复杂度是 $O(x\sum b_i)$。

对于多重背包，还有一种二进制拆解的算法，能使时间复杂度降低，实现也很简单，将物品件数分为 $1$ 件、$2$ 件、$4$ 件、$8$ 件等，就可以凑出 $1$ 至 $b_i$ 种物品，时间复杂度是 $O(x\sum \log b_i)$。

然后要注意每种物品只能取一次，所以循环要倒序循环。
## 代码
在实现上，作者采用一个 `bool` 数组，将每种价格能否满足要求存进去在循环时，用 $|$ 运算就行了。
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

int n,m,a[55],b[55],f[10005];
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	f[0]=1;
	for(int i=1;i<=n;i++) for(int k=m;k>=a[i];k--) for(int j=1;j<=b[i];j++) if(k>=j*a[i]) f[k]|=f[k-j*a[i]];
	cout<<(f[m]==1? "Yes":"No");
	return 0;
}
```

---

## 作者：VitrelosTia (赞：1)

题链：[AT](https://atcoder.jp/contests/abc286/tasks/abc286_d)/[Luogu](https://www.luogu.com.cn/problem/AT_abc286_d)

### 题意
第一行给定 $n,x$，代表有 $n$ 种商品，你有 $x$ 元钱。接下来 $n$ 行，第 $i$ 行给定 $a_i,b_i$，代表第 $i$ 个物品的价格是 $a_i$，数量是 $b_i$ 个。
现在问你是否有正好把钱花完的方法？

### 思路
一眼看出这道题实际上就是一个背包问题，可以参照[P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)的做法，只需要把输出最小剩余空间改成判断最小剩余空间是否为 $0$ 即可。

需要注意的是，由于读入方式不一样，在读入时需要稍做处理。

### code
```
#include <bits/stdc++.h>
 
using namespace std;
 
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;i++)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;i--)
#define yes puts("Yes")
#define no puts("No")
#define ll long long
#define endl putchar('\n')
 
const int M=1e5+5,INF=1e9;
int n,val,v[M],f[M];

void solve(){
	int t=0,cnt=1;//t记共有多少个物品，cnt记现在是第几个物品
	scanf("%d%d",&n,&val);
	up(1,n,i){
		int x,y;
		scanf("%d%d",&x,&y);
		while(y--){
			v[cnt]=x;
			cnt++;
			t++;
		}
	}
	up(1,t,i){ dn(val,v[i],j) f[j]=max(f[j],f[j-v[i]]+v[i]); }//装箱问题
	if(val-f[val]==0) yes; else no;//判断
}
 
int main(){
    int t;
    //scanf("%d",&t);
    t=1;
    while(t--) solve();
    return 0;
}
```

---

