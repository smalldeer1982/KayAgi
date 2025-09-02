# Roof Construction

## 题目描述

It has finally been decided to build a roof over the football field in School 179. Its construction will require placing $ n $ consecutive vertical pillars. Furthermore, the headmaster wants the heights of all the pillars to form a permutation $ p $ of integers from $ 0 $ to $ n - 1 $ , where $ p_i $ is the height of the $ i $ -th pillar from the left $ (1 \le i \le n) $ .

As the chief, you know that the cost of construction of consecutive pillars is equal to the maximum value of the bitwise XOR of heights of all pairs of adjacent pillars. In other words, the cost of construction is equal to $ \max\limits_{1 \le i \le n - 1}{p_i \oplus p_{i + 1}} $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find any sequence of pillar heights $ p $ of length $ n $ with the smallest construction cost.

In this problem, a permutation is an array consisting of $ n $ distinct integers from $ 0 $ to $ n - 1 $ in arbitrary order. For example, $ [2,3,1,0,4] $ is a permutation, but $ [1,0,1] $ is not a permutation ( $ 1 $ appears twice in the array) and $ [1,0,3] $ is also not a permutation ( $ n=3 $ , but $ 3 $ is in the array).

## 说明/提示

For $ n = 2 $ there are $ 2 $ sequences of pillar heights:

- $ [0, 1] $ — cost of construction is $ 0 \oplus 1 = 1 $ .
- $ [1, 0] $ — cost of construction is $ 1 \oplus 0 = 1 $ .

For $ n = 3 $ there are $ 6 $ sequences of pillar heights:

- $ [0, 1, 2] $ — cost of construction is $ \max(0 \oplus 1, 1 \oplus 2) = \max(1, 3) = 3 $ .
- $ [0, 2, 1] $ — cost of construction is $ \max(0 \oplus 2, 2 \oplus 1) = \max(2, 3) = 3 $ .
- $ [1, 0, 2] $ — cost of construction is $ \max(1 \oplus 0, 0 \oplus 2) = \max(1, 2) = 2 $ .
- $ [1, 2, 0] $ — cost of construction is $ \max(1 \oplus 2, 2 \oplus 0) = \max(3, 2) = 3 $ .
- $ [2, 0, 1] $ — cost of construction is $ \max(2 \oplus 0, 0 \oplus 1) = \max(2, 1) = 2 $ .
- $ [2, 1, 0] $ — cost of construction is $ \max(2 \oplus 1, 1 \oplus 0) = \max(3, 1) = 3 $ .

## 样例 #1

### 输入

```
4
2
3
5
10```

### 输出

```
0 1
2 0 1
3 2 1 0 4
4 6 3 2 0 8 9 1 7 5```

# 题解

## 作者：Jorge_Filho (赞：13)

# CF1632B Solution

## 题意:
这题英文题面不啰嗦，翻译的也很精髓，去掉了需许多无用信息，直接读题就好了。

## 解析:

设 $k=\max\{2^m|2^m<n∧m \in N\}$ ( 即 $k$ 为 $<n$ 的最大的 $2$ 的整数次幂 )，得：

$\min\{\max\{p_i \oplus p_{i+1} \in [1,n)\}|\operatorname{permutation}(p)\}=k$ 
( 即 $k$ 也为英文题面中所述的最小cost，其中 $\operatorname{permutation}(p)$ 表示 $p$ 的全排列 )

证：因为至少有一对 $\ge k$ 的数 $a$ 与 $<k$ 的数 $b$ 相邻，此时 $a \oplus b \ge k$ ( 最高位 $1 \oplus 0=1$ )

而剩下的 $<k$ 的数两两异或都 $<k$ ( 最高位 $0 \oplus 0=0$ )，$ \ge k$ 的数两两异或也都 $<k$ ( 最高位$1 \oplus 1=0$ )

所以 $\max\{p_i \oplus p_{i+1}|i \in [1,n)\} \ge k$

而我们可以构造一个序列使得每一对相邻的 $ \ge k$ 的数 $a$ 和 $<k$ 的数 $b$ 都满足 $a \oplus b=k$

证毕.

不难发现当 $a=k+x$，$b=x$，时：$a \oplus b=k$ ($0 \le x \le n-k$) ( 后面的 $x \oplus x=0$ 抵消了 ).

方便起见，这里假设只有一对这样的 $a$ 和 $b$，并令$x=0$，那么最终序列只需将 $ \ge k$ 的数放在一边，$<k$ 的数放在另一边，交界处为 $k$ 和 $0$。

其中一个可行的序列为：$[n-1,n-2,n-3,...,k,0,1,2,3,...,k-1]$

输入 $n$ 后直接输出序列即可( 注意有 $t$ 组数据 )，详见代码。

渐进时间复杂度：$O(nt)$

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int T=1e4,N=2e5;
int t,n,k,a[N+5],top;

int  main()
{
 scanf("%d",&t);
 while(t--)
 {
  scanf("%d",&n);
  k=1;
  top=0;//多组数据这里记得初始化.
  while(k<n)
  {
   k<<=1;
  }
  k>>=1;//循环结束后的k是>n的最小的2的整数次幂,还需/2才能得到n的最大的2的整数次幂
  for(int i=n-1;i>=k;i--)//>=k的数
  {
   a[++top]=i;
  }
  for(int i=0;i<k;i++)//<k的数
  {
   a[++top]=i;
  }
  for(int i=1;i<=top;i++)//其实可以直接在上面两个循环就输出了
  {
   printf("%d ",a[i]); 
  }
  printf("\n");//换行开始下一组数据
 }
 return 0;
}
/*
4
2
3
5
10
//
0 1
2 0 1
3 2 1 0 4
4 6 3 2 0 8 9 1 7 5
*/
```
[AC记录](https://codeforces.com/problemset/submission/1632/145906615)

## 特别鸣谢
@[nemonadeMC](https://www.luogu.com.cn/user/389797) 帮助了本篇题解的Latex编写工作。

@[水逆还再超](https://www.luogu.com.cn/user/128310) 帮助检查了本篇题解的语法错误。

---

## 作者：include_BM (赞：6)

假设 $n-1$ 最高位为 $k$，则最终结果最小值为 $k$（例如 $n-1=(1011010)_2$ 时 $k=(1000000)_2$。），理由如下：

最终的序列中所有 $\ge k$ 的数中至少会有一个数 $x$ 与一个 $<k$ 的数 $y$ 相邻，而 $x$ 的最高位 $k$ 不会因为与 $y$ 异或而被消去，故 $x\oplus y\ge k$；又因 $\ge k$ 的数两两异或得到的数 $<k$，$<k$ 的数两两异或得到的数 $<k$，故最终的结果 $\ge k$，在 $x\oplus y=k$ 时取等。

因为 $k\oplus 0=k$，所以可以得到一个符合要求的序列 $n-1,n-2,\dots,k,0,1,2,\dots,k-1$。

---

## 作者：我梦见一片焦土 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF1622B)

---

# 思路：

这道题目我们想要使得答案最小，就要让相邻两个数的高位尽量相等，连续的数必然也是要与其它数交界的，可以选择一端在边界，另一端也必须要与最高位不是 $1$ 的数接触，那么异或之后最高位的 $1$ 必然存在，要让剩下的位最小就只能让最大数和最小数接触。剩下的数随便排，无论怎么排都不会比最大值更大。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int t,n;
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        int x=1;
        while(x<n){
            x<<=1;
        }
        x>>=1;
        for(int i=1;i<x;i++){
            cout<<i<<" ";
        }
        cout<<0;
        for(int i=x;i<n;i++){
            cout<<" "<<i;
        }
        cout<<endl;
    }
    return 0;
}
```

完结撒花~

---

## 作者：qzhwlzy (赞：2)

### 题目大意
$t$ 组数据，给定 $n$，输出一种 $0\sim n-1$ 的排列 $p$，使得 $\max\limits_{1\le i\le n-1}{p_i\oplus p_{i+1}}$ 最小。
### 思路
记 $k$ 为 $n-1$ 二进制形式的最高位，即 $k$ 满足 $2^k\le n-1 < 2^{k+1}$。  
对于任意排列，我们发现，所求的代价一定不小于 $2^k$。因为大于等于 $2^k$ 的数的个数一定小于等于总数，所以不管怎么排列，一定有至少一个大于等于 $2^k$ 的数与小于 $2^k$ 的数相邻，此时最高位上由于 $1\oplus 0 = 1$，所以此时 $p_i\oplus p_{i+1}\ge 2^k$，所以总代价也 $\ge 2^k$ 。  
因此我们考虑最小代价为 $2^k$，构造符合条件的排列。显然可以把数分成大于等于 $2^k$ 和小于 $2^k$ 两类。显然每一类中任两数进行按位异或操作结果都小于 $2^k$：
- 大于等于 $2^k$ 的数第 $k$ 位都为 $1$，$1\oplus 1=0$，所以 $p_i\oplus p_{i+1}< 2^k$;
- 小于 $2^k$ 的数第 $k$ 位都为 $0$，$0\oplus 0=0$，所以 $p_i\oplus p_{i+1}< 2^k$。

所以我们只需要让两部分中的数分别在一起即可。  
之后我们只要使得两部分相邻处的异或值等于 $2^k$ 即可（因为一部分第 $k$ 位为 $0$，一部分为 $1$，$0\oplus 1 = 1$，所以 $p_i\oplus p_{i+1}\ge 2^k$，最小为 $2^k$），一种最简单的方法就是让 $2^k$ 与 $0$ 相邻，这样两部分交界处就是 $2^k \oplus 0=2^k$，满足条件。

所以，我们最后的排列就**可以**是（中括号里的数可任意排列，答案不限于此）：
$$[2^k-1,2^k-2,2^k-3,…,1],0,2^k,[2^k+1,2^k+2,…,n-1]$$
### 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,n;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int k=0;
		while(1<<(k+1)<=(n-1)) k++;
		for(int i=(1<<k)-1;i>=0;i--) printf("%d ",i);
		for(int i=(1<<k);i<n;i++) printf("%d ",i);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：midsummer_zyl (赞：1)


## 题意：

按照一定顺序重新排列这 $n$ 个整数，使得 $\max\limits_{1\leqslant i\leqslant n-1} p_i\oplus p_{i+1}$ 最小，其中 $\oplus$ 表示按位异或运算。请求出**任意一个**满足该要求的重新排列后的数组。

## 理解：

读完题目，思考后我们可以构造出最小值为 $k$ 的一个序列：

$(2^k - 1 \hspace{0.5cm} 2^k - 2 \hspace{0.5cm} 2^k - 3\hspace{0.5cm}\dots \hspace{0.5cm}2\hspace{0.5cm}1)\hspace{0.5cm}0\hspace{0.5cm}2^k\hspace{0.5cm}(2^k + 1\hspace{0.5cm}2^k + 2\hspace{0.5cm}2^k + 3\hspace{0.5cm}\dots \hspace{0.5cm}n - 2\hspace{0.5cm}n - 1)$


此序列便是能够 AC 的序列了。


## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n; scanf("%d", &n);
		int s = 1;
		while(2 * s < n)
			s *= 2;
		for (int i = s - 1; i >= 0; i--)
			printf("%d ", i);
		for (int i = s; i < n; i++)
			printf("%d ", i);
		printf("\n");
	}
	return 0;
}
```

是不是很简单明了？快去 $AC$ 吧！

---

## 作者：happy_dengziyue (赞：1)

### 1 题意

第 $1$ 行一个整数 $t$ 表示数据组数，接着 $t$ 行一个整数 $n(n\ge2)$。

有一个由小于 $n$ 的所有自然数组成的数列。现在，你要重排它。

规定一个数列的“花费”为相邻两数异或值的最大值。请通过重排，使得花费最小。输出任意一个满足要求的数列。

### 2 思路

为了简单一点，**从现在起将 $n$ 自减 $1$**，也就是 $0$ 到 $n$ 的自然数数列。

设 $x$ 为满足 $2^x\le n$ 的最大自然数，并且设 $k=2^x$。很明显，$k=n\operatorname{and}(-n)$（也就是树状数组里的 $\operatorname{lowbit}(n)$）。可以证明，**最优数列的花费必定为 $k$。**

**请记住 $k$ 的定义，后面很多的不等式都要用到。**

很明显，必定存在一对相邻的数，一个大于等于 $k$，一个小于 $k$。这两个数相异或的值必定大于等于 $k$。

那么我们怎么把花费控制到 $k$ 呢？

我们可以发现，当 $n$ 和 $n\oplus k$ 相邻时，他们的异或值为 $0$。那么就先输出它们。

然后我们要做个特判。当 $n=k$ 时，我们的输出是 $n$ 和 $0$，那么我们可以从 $1$ 输出到 $n-1$。事实上，从 $1$ 到 $n-1$ 的数无论以什么顺序排都没关系。这个程序就可以结束了。

那么当 $n\not=k$ 时呢？

首先，我们要将 $1$ 到 $k-1$ 的数（$n\oplus k$ 例外）输出一遍（顺序你开心就好）。因为可以证明：

$$\operatorname{max}^{k-1}_{i=1}\operatorname{max}^{k-1}_{j=1}i\oplus j<k$$

同时也可以发现，$1\le n\oplus k<k$，所以，可以用上一条证明：

$$\operatorname{max}^{k-1}_{i=1}n\oplus k\oplus i<k$$

然后，我们输出 $0$ 和 $k$。可以证明：

$$\operatorname{max}^{k-1}_{i=1}i\oplus 0=k-1<k$$

且：

$$0\oplus k=k$$

接着，我们将 $k+1$ 到 $n-1$ 的数（$n\oplus k$ 例外）按次序输出。可以证明：

$$\operatorname{max}^{n-1}_{i=k}\operatorname{max}^{n-1}_{j=k}i\oplus j<k$$

同时，可以用上一条证明：

$$\operatorname{max}^{n-1}_{i=k+1}k\oplus i<k$$

那么此题完成。

我们可以分为以下 $4$ 个阶段：

1. $n$ 和 $n\oplus k$；

2. $1$ 到 $k-1$ 的所有整数（$n\oplus k$ 例外）；

3. $0$ 和 $k$；

4. $k+1$ 到 $n-1$ 的所有整数（$n\oplus k$ 例外）。

这 $4$ 个阶段的顺序只能反过来，最好不要打乱。

当然了，还可能有更简单的解法。

### 3 代码与记录

```cpp
#include<cstdio>
using namespace std;
#define max_n 200000
int t;
int n;
int k;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1632B_1.in","r",stdin);
	freopen("CF1632B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		--n;
		k=2;
		while(k<=n)k<<=1;
		if(k>n)k>>=1;
		printf("%d %d ",n,n^k);
		if(n==k){
			for(int i=1;i<n;++i)printf("%d ",i);
		}
		else{
			for(int i=1;i<k;++i){
				if(n^k^i)printf("%d ",i);
			}
			printf("0 %d ",k);
			for(int i=k+1;i<n;++i){
				if(n^k^i)printf("%d ",i);
			}
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/68455316)

By **dengziyue**

---

## 作者：zhangmuning1016 (赞：0)

## 题意
第 $1$ 行一个整数 $t$ 表示数据组数，接着 $t$ 行一个整数 $n(n\ge2)$。有一个由小于 $n$ 的所有自然数组成的数列。一个数列的“花费”是相邻两数异或值的最大值。请通过重排，使得花费最小。输出任意一个满足要求的数列。
## 思路
若使 $k$ 为 $(n−1)_2$ 的最高位，也就是 $2k\le n−1<2k+1$，可发现其值一定 $\ge2k$。所以我们先思考：是否有一种排列，其值为 $2k$。

经过思考，我们可构造出以下排列：  
$2k−1,2k−2,2k−3\dots3,2,1,0,2k,2k+1,2k+2,2k+3\dots n−3,n−2,n−1$。
## 代码
```#include<bits/stdc++.h>
using namespace std;
int main() {
	int T;
	cin>>T;
	while(T--) {
		int n,k=1;//k要初始化
		cin>>n;//输入
		while(1) { //求k值
			if(k*2<n) {
				k*=2;
			} else {
				break;
			}
		}
		for(int i=k-1; i>=0; i--) {
			cout<<i<<' ';
		}
		for(; k<n; k++) {
			cout<<k<<" "; //构造排列
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：yzm0325 (赞：0)

### 题意

给定 $n$，求一个 $0 \sim n-1$ 的排列 $p$，使得 $\max\limits_{1\leqslant i\leqslant n-1} p_i\oplus p_{i+1}$ 最小。

### 思路

首先证明引理：设 $k$ 为 $n-1$ 二进制形式的最高位（即 $k \leq n-1 < 2 \times k$ 且 $k$ 为 $2$ 的正整数次幂），则答案最小为 $k$。

证明：因为 $n \geq 2$，所以序列里一定存在至少一个数 $<k$，也就一定存在一个 $\geq k$ 的数 $p_i$ 与一个 $<k$ 的数 $p_j$ 相邻，此时 $p_i \oplus p_j \geq k$。所以最终答案一定 $\geq k$。

接下来考虑如何将答案最小化为 $k$。发现 $k \oplus 0=k$，而对于两个均 $\geq k$ 或均 $<k$ 的数，异或的结果都会 $<k$。所以考虑把 $k$ 和 $0$ 放在一起，所有 $\geq k$ 的数放在一起，所有 $<k$ 的数放在一起，构造出如下序列（中括号内的数可任意排列）：

$$[k+1 \sim n-1],k,0,[1 \sim k-1].$$

### 代码

RMJ 炸了导致不保证 AC，等可以交了会重测的。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        int k1 = int(log(n - 1) / log(2));
        int k = 1 << k1; // 变量 k 如上所述
//      cout << k << '\n'; 调试所加
        for(int i = n - 1; i >= k; i--) cout << i << ' ';
        for(int i = 0; i < k; i++) cout << i << ' ';
        // 此处为了方便输出了 n-1,n-2,...,k,0,1,...,k-1 这个序列，符合上述序列的格式
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：beigongbaishan (赞：0)

# 题目大意
将 $0$ 到 $n-1$ 的数字重新排列，使得 $ \max\limits_{1 \le i \le n - 1}{p_i \oplus p_{i + 1}} $ 的值最小。

tips：$\oplus$ 表示异或。
## 浅浅讲下异或
异或，是一种位运算符，运算规则如下：
+ $0\oplus 0 = 0$
+ $1\oplus 1 = 0$
+ $0\oplus 1 = 1$
+ $1\oplus 0 = 1$

即相同为假，不同为真。
# 解题思路
若使 $k$ 为 $(n-1)_2$ 的最高位，也就是 $2^k\le n-1< 2^{k+1}$，则可发现：

**其值一定 $\ge 2^k$！**

所以我们先思考：是否有一种排列，其值为 $2^k$。  
经过思考，我们可构造出以下排列：

$2^k-1,2^k-2,2^k-3\dots3,2,1,0,2^k,2^k+1,2^k+2,2^k+3\dots n-3,n-2,n-1$

那么用代码实现就很简单了！
# CODE
```cpp
#include<iostream>
using namespace std;
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,k=1;//k记得赋值 
		cin>>n;
		for(k=1;k*2<n;k*=2);//求k值
		for(int i=k-1;i>=0;i--)cout<<i<<' ';
		for(;k<n;k++)cout<<k<<' ';//构造排列
		cout<<'\n';//热知识：比 endl 快 
	}
}
```
祝大家 RP++~

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给你一个 $0$ 到 $n-1$ 的排列，要求你构造出 最大相邻亦或值最小的排列顺序。
## 分析
~~当有点看不懂题目时，我们要思维活跃，大胆猜测。~~

由题给样例的输出结果 $2$，$4$，$8$ 大胆猜测答案一定是 $2$ 的幂次。

要使相邻数的亦或值最小，势必要尽可能消去二进制表达中最高位的 $1$。

我们拿 $8$ 举例：
$$
000001010011100101110111
$$
要使相邻的异或值最小，最高位是 $1$ 的所有数应该放在一起相互抵消，但是一定有一个数的最高位是是抵消不掉的。要使这个值尽可能小，我们应该使亦或的结果只保留最高位的 $1$。最简单的方法就是让 $0$ 和状如 $100000$ 的数，此处 $1$ 是最高位其他位均为 $0$，相邻摆放，小于 $100000$ 的数放 $0$ 一侧，大于的放另一侧。这样构造的结果可以保证答案不超过 $100000$。
## 代码

```cpp
int main (){
    cin >> t;
    while (t --){
        cin >> n;
        int m = 1;
        for (int i = 1 ; i <= n + 3; i *= 2){
            if (i * 2 > n - 1){
                m = i;
                break;
            }
        }
        for(int i = 1 ; i < m ; i ++) cout << i << ' ';
        cout << 0 << ' ';
        for (int i = m ; i < n ; i ++) cout << i << ' ';
        cout << endl;
    }
    return 0;
}

```

---

## 作者：Norsuman371 (赞：0)

# 思路

首先按照题意找到一个排列中相邻两数异或的最大值最小的排列，发现不论在本位为 $1$ 的数怎么排列，至少有一个数会接触到本列为 $0$ 的数，因此答案的本位必然是 $1$。既然这样，就把这部分排到最后面，让这部分最靠左的数与这个数最高位 $1$ 取反的数相邻，遍得能到满足题目要求的排列。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[200005];
int count(int x) {
    int ans = 0;
    while (x) {
        ans += (x & 1);
        x >>= 1;
    }
    return ans;
}
vector<int> cnt[32];
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        memset(cnt, 0, sizeof(cnt));
        int hi = 0;
        for (int i = 0; i <= n - 1; i++) {
            for (int j = 0; j < 32; j++) {
                if ((i >> j) & 1) {
                    cnt[j].push_back(i);
                    hi = max(hi, j);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            a[i] = i;
        }
        swap(a[(1 << hi) ^ cnt[hi][0]], a[cnt[hi][0] - 1]);
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

# 记录

[AC](https://www.luogu.com.cn/record/165236546)

---

## 作者：GoodLuckCat (赞：0)

## 题目大意

重新排列从 $0$ 到 $n-1$ 的这 $n$ 个整数，使 $\max\limits_{1\leqslant i\leqslant n-1} p_i\oplus p_{i+1}$ 的值最小，$\oplus$ 表示异或运算。请求出任意一个满足该要求的排列。

## 思路

设 $k$ 为满足 $2^k\le n-1<2^{k+1}$ 的自然数。很明显，$\max\limits_{1\leqslant i\leqslant n-1} p_i\oplus p_{i+1}$ 这个算式的值不可能小于 $2^k$。所以我们来讨论有没有值等于 $2^k$ 的情况。

经过分析，得出结论，答案等于 $2^k$ 的排列是存在的。它的公式如下：

$$2^k-1,2^k-2,2^k-3,\cdots,3,2,1,0,2^k,2^k+1,2^k+2,2^k+3,\cdots,n-3,n-2,n-1$$

也就是说，只要求出 $k$，就可以求出这个排列，而它一定是满足要求的。

## 代码

```cpp
#include<iostream>
#include<cmath>
int main()
{
	int t,n,k;
	scanf("%d",&t);
	while(t--)
	{
		k=1;
		scanf("%d",&n);
		while((k<<1)<n)k=k<<1;
		for(int i=k-1;i>=0;--i)printf("%d ",i);
		for(int i=k;i<n;++i)printf("%d ",i);
		printf("\n");
	}
}
```

## 小提示

一开始 $k$ 忘记赋值了，调了十几次，每次总是超时。**一定要赋初值！！！** 祝大家不再重蹈覆辙。

---

## 作者：zhongcy (赞：0)

### Problem


------------

给定一个 $ n $，构造一个 $ 0 $ 到 $ n-1 $ 的序列 $ p $，使 $ \max_{1 \le i \le n-1} p_i \oplus p_{i+1} $ 最小。


### Solution


------------

设 $ k $ 为不超过 $ n $ 且满足 $ k=2^m ( m \in N^* )$ 的最大值。序列中总会有一对相邻的元素，其中一个第 $ k $ 位为 1，另一个为 0。因此答案最小值为 $ k $。据此可以构造一个满足条件的序列 $ p = [ 2^k-1 , 2^k-2 , \dots , 0 , 2^k+1 , \dots , n-1 ] $。    


根据上述过程模拟即可，时间复杂度为 $ O( t n ) $。


### Code


------------



```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)
	{
		int n,k=1;cin>>n;
		for(k=1;2*k<n;k*=2);//求k的值
		for(int i=k-1;i>=0;i--)
			cout<<i<<' ';
		 for(int i=k;i<n;i++)
			cout<<i<<' ';//根据上述过程构造出序列
		cout<<'\n';
	} 
	return 0;
}
```


---

## 作者：Deuteron (赞：0)

## 题意简述：

[传送门](https://www.luogu.com.cn/problem/CF1632B)

## solution

我们可以得到答案为 $2^k$ , 其中 $k$ 表示 $n-1$ 的二进制表达的最高位。

至于这个结论的证明，可以分两步走

#### 1.证明 $2^k$ 是最优答案

我们可以看到这个序列不管怎么排列，一定会有一个 $\ge 2^k$ 与一个 $\le 2^k$ 的数相邻。于是答案一定 $\ge 2^k$ 。

#### 2.构造出 $p$ 使得答案为 $2^k$ 

我们可以将 $1$ 至 $n-1$ 的数分为两类：$\ge 2^k$ 的与 $< 2^k$ 的。 

每一类之间的异或值一定 $\le 2^k$。

又由于$0 \oplus 2^k=2^k$

可以给出构造 $1,2,3\dots0,2^k,2^k+1\dots n-2,n-1$ 

## code

```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
int t;
signed main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int k=log2(n-1);//计算出k 
		int l=1<<k;//计算出2^k 
		for(int i=1;i<l;i++) cout<<i<<" ";//从1到2^k-1 
		cout<<0<<" "<<l<<" ";//0和2^k 
		for(int i=l+1;i<n;i++) cout<<i<<" ";//从2^k+1到n-1 
		cout<<endl;
	}
	return 0;
}

```




---

