# [AGC061A] Long Shuffle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc061/tasks/agc061_a

配列 $ A_1,\ \ldots,\ A_N $ があり、はじめ全ての $ i $ について $ A_i\ =\ i $ です。手順 $ \mathrm{shuffle}(L,\ R) $ を以下として定義します。

- $ R\ =\ L\ +\ 1 $ なら、$ A_L $ と $ A_R $ の値を入れ替えて終了する。
- そうでないなら、$ \mathrm{shuffle}(L,\ R\ -\ 1) $ を実行してから $ \mathrm{shuffle}(L\ +\ 1,\ R) $ を実行する。

$ \mathrm{shuffle}(1,\ N) $ を行うとします。手順終了後の $ A_K $ の値を出力してください。

各入力ファイルについて、テストケースを $ T $ 個解いてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 1000 $
- $ 2\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ K\ \leq\ N $

### Sample Explanation 1

$ N=2 $ のときは、以下を行って $ A=(2,1) $ を得ます。 - $ \mathrm{shuffle}(1,\ 2) $ を実行し、$ A_1 $ と $ A_2 $ を入れ替える。 $ N=5 $ のときは、以下を行って $ A=(2,4,1,5,3) $ を得ます。 - $ \mathrm{shuffle}(1,\ 5) $ を実行する。 - $ \mathrm{shuffle}(1,\ 4) $ を実行する。 - $ \mathrm{shuffle}(1,\ 3) $ を実行する。 - $ \vdots $ - $ \mathrm{shuffle}(2,\ 4) $ を実行する。 - $ \vdots $ - $ \mathrm{shuffle}(2,\ 5) $ を実行する。 - $ \mathrm{shuffle}(2,\ 4) $ を実行する。 - $ \vdots $ - $ \mathrm{shuffle}(3,\ 5) $ を実行する。 - $ \vdots $

## 样例 #1

### 输入

```
7
2 1
2 2
5 1
5 2
5 3
5 4
5 5```

### 输出

```
2
1
2
4
1
5
3```

# 题解

## 作者：Francais_Drake (赞：2)

# [[AGC061A] Long Shuffle](https://www.luogu.com.cn/problem/AT_agc061_a)
考虑进行 `shuffle(1,2n)` 后，一定有且只有某些 $a_{2i-1},a_{2i}$ 互换。

证明：考虑将 `shuffle(1,2n)` 拆成 `shuffle(1,2n-2)`、`shuffle(2,2n-1)`、`shuffle(2,2n-1)`、`shuffle(3,2n)`。考虑归纳，设 `shuffle(1,2n-2)` 时只会对某些 $a_{2i-1},a_{2i}$ 互换，则中间两个 `shuffle(2,2n-1)` 可以抵消，而 `shuffle(1,2n-2)` 和 `shuffle(3,2n)` 均只会将某些 $a_{2i-1},a_{2i}$ 互换；且 `n=1` 时只会交换 $a_1,a_2$；所以该命题成立。

此时设 $P_{i,j}$ 为 `shuffle(1,2i)` 时 $a_{2j-1}$ 和 $a_{2j}$ 是否互换，则有 $P_{i,j}=P_{i-1,j}\oplus P_{i-1,j-1}$（非法 $P$ 值可以设为 $0$），初值有 $P_{1,1}=1$。此时可以发现递推方式类似组合数（其实 $P_{i,j}$ 就是 $\binom{i-1}{j-1}\bmod 2$ 的值），就很好处理了。然后 $n$ 为奇数时可以拆成 `shuffle(1,n-1)` 和 `shuffle(2,n)` 也很好处理。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int t; ll n,k,a;
inline bool P(ll i,ll j){
	ll si=0,sj=0,k=i-j;
	while(i>>=1) si+=i;
	while(j>>=1) sj+=j;
	while(k>>=1) sj+=k;
	return si==sj;
}
inline ll S(ll i,ll j){
	return ((j-1)^P((i-1)>>1,(j-1)>>1))+1;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&n,&k);
		if(n&1){
			if(k!=n) a=S(n-1,k);
			if(k!=1&&S(n-1,k-1)!=k-1){
				if((k^=1)!=n) a=S(n-1,k);
				else a=n;
			}
		}
		else a=S(n,k); printf("%lld\n",a);
	}
	return 0;
}
```

---

## 作者：Leasier (赞：1)

~~快乐打表找规律题。~~

打表可以发现：

- $n$ 为偶数时 $|a_k - k| \leq 1$。
- $n$ 为奇数时 $|a_k - k| \leq 2$。

而 $n$ 为奇数时我们只需要将其拆分为两个偶数的情况，下面讨论 $n$ 为偶数的情况。

对 `shuffle` 执行过程中相邻项交换的情况进行分析：

- 现在执行 `shuffle(l, l + 2k - 1)`。
- 第一步 `shuffle(l, l + 2k - 2)`，即先 `shuffle(l, l + 2k - 3)`、再 `shuffle(l + 1, l + 2k - 2)`。
- 第二步 `shuffle(l + 1, l + 2k - 1)`，即先 `shuffle(l + 1, l + 2k - 2)`、再 `shuffle(l + 2, l + 2k - 1)`。

注意到中间有两步是一模一样的。经归纳，我们发现可以这两步可以**抵消**，且实际**可能**有效的交换操作都发生在某些 $l + 2i - 2, l + 2i - 1$ 之间，且交换次数为 $C_{k - 1}^{i - 1}$。

于是我们判断这个组合数的奇偶性即可。奇偶性的判断可以判断子集关系。

代码：
```cpp
#include <iostream>

using namespace std;

typedef long long ll;

int a[7];

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		ll n, k;
		cin >> n >> k;
		if (n % 2 == 0){
			ll x = (k - 1) / 2;
			if (((n / 2 - 1) & x) != x){
				cout << k << endl;
			} else if (k % 2 == 0){
				cout << k - 1 << endl;
			} else {
				cout << k + 1 << endl;
			}
		} else if (k == 1){
			cout << 2 << endl;
		} else if (k == n){
			cout << n - 2 << endl;
		} else {
			ll x = (n - 1) / 2 - 1;
			a[1] = -2;
			a[2] = -1;
			a[3] = 0;
			a[4] = 1;
			a[5] = 2;
			if (k % 2 == 0){
				ll y = k / 2 - 1, z = y + 1;
				if ((x & y) == y) swap(a[2], a[3]);
				if ((x & z) == z) swap(a[4], a[5]);
				if ((x & y) == y) swap(a[3], a[4]);
			} else {
				ll y = (k - 1) / 2, z = y - 1;
				if ((x & z) == z) swap(a[1], a[2]);
				if ((x & y) == y) swap(a[3], a[4]);
				if ((x & z) == z) swap(a[2], a[3]);
			}
			cout << k + a[3] << endl;
		}
	}
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

## 题意

给定一个满足 $A_i=i$ 的排列 $A$，求对其进行一次 $\mathrm{shuffle}(1,N)$ 操作后其第 $K$ 项的值。其中 $\mathrm{shuffle}(L,R)$ 的定义如下：
- 若 $R = L + 1$，那么交换 $A_L$ 和 $A_R$ 的值
- 否则，依次执行 $\mathrm{shuffle}(L,R-1)$, $\mathrm{shuffle}(L+1,R)$

（$1 \le T \le 1000, 1 \le K \le N \le 10^{18}$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-AGC061A.html)

通过计算出 $N$ 较小时的情况我们可以发现若 $N$ 为偶数，对于一对下标，在执行操作 $\mathrm{shuffle}(1,n)$ 操作后，有 $2i - 1, 2i$，有 $A_{2i - 1} = 2i - 1, A_{2i} = 2i$ 或 $A_{2i - 1} = 2i, A_{2i} = 2i - 1$ 成立。换句话说，就是在 $N$ 为偶数时，只会交换一些相邻且互不相交的数对。

考虑使用归纳法证明，设 $N = 2K$，当 $K = 1$ 时命题成立，对于 $K > 1$ 的情况，可以发现会依次执行如下操作：

- $\mathrm{shuffle}(1,2K-2)$
- $\mathrm{shuffle}(2,2K-1)$
- $\mathrm{shuffle}(2,2K-1)$
- $\mathrm{shuffle}(3,2K)$

可以发现中间两次 $\mathrm{shuffle}(2,2K-1)$ 操作相互抵消，所以只会剩下两个操作区间长度为 $N - 2$ 的子操作，故命题成立。

因此在 $N = 2K$ 的情况下，只要计算出数对 $2i - 1, 2i$ 被操作的次数即可计算出对应位置的值。可以发现在初始时区间长度为 $2K$，至最后会缩减至 $2$，每次缩减有两种方案：右移左边界和左移右边界，那么从 $N = 2K$ 缩减至数对 $2i - 1, 2i$ 共需要缩减 $K - 1$ 次，只有恰好缩减 $i - 1$ 次右边界才能使得最终操作的数对为 $2i - 1, 2i$，可以计算出方案数为 $\dbinom{K - 1}{i - 1}$。由于交换只有两种状态，那么我们只需要计算出 $\dbinom{K - 1}{i - 1} \bmod 2$ 即可。使用卢卡斯定理直接计算即可在 $\mathcal{O}(\log N)$ 的时间内完成计算。但是存在如下结论：

$$\dbinom{n}{m} \equiv 1 \bmod 2 \Leftrightarrow n \operatorname{AND} m = m$$

其中 $\operatorname{AND}$ 表示按位与操作。

证明可以考虑卢卡斯定理的过程，设二进制下 $n$ 的每一位依次为 $a_i$，$m$ 的每一位依次为 $b_i$，那么有

$$\dbinom{n}{m}\bmod 2 = \prod\limits_{i}\dbinom{a_i}{b_i}$$

那么 $\dbinom{n}{m} \equiv 1 \bmod 2$ 的充要条件即为 $\forall i, \dbinom{a_i}{b_i} = 1$，即 $a_i \operatorname{AND} b_i = b_i$，即 $n \operatorname{AND} m = m$。

因此我们可以快速计算 $\dbinom{K - 1}{i - 1} \bmod 2$ 的值，若 $N$ 为奇数那么分别计算两次区间长度为偶数的情况即可。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;

valueType query(valueType N, valueType K) {
    if (((N / 2 - 1) & ((K + 1) / 2 - 1)) == ((K + 1) / 2 - 1))
        return (K & 1) ? K + 1 : K - 1;
    else
        return K;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, K;

        std::cin >> N >> K;

        if (N & 1)
            std::cout << query(N - 1, query(N - 1, K - 1) + 1) << std::endl;
        else
            std::cout << query(N, K) << std::endl;
    }

    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
啊，这就是 AGC 的第一题吗。~~不愧是我做不了的题目。~~

题目很清晰，不多赘述。刚开这道题的时候，感觉和之前做到的序列的翻转和异或有一定的相似之处。很有意思的一道题，比较考查数学分析归纳能力和总结性结论分析，同时还需要一点点的分类讨论的思想。
## 分析。
没有什么思路先考虑暴力：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int a[1005];
void work(int l,int r){
	if(l+1==r){
		swap(a[l],a[r]);
	}
	else{
		work(l,r-1);
		work(l+1,r);
	}
}
int main(){
	int t,n,k;
	cin>>t;
	for (int i=1;i<=t;i++){
		for (int i=1;i<=1005;i++){
		    a[i]=i;
	    }
		cin>>n>>k;
		work(1,n);
		cout<<a[k]<<"\n";
	}
	return 0;
}
```
坚持不懈地进行计算后整理得到一张表（仅展示前面的一部分）：
```
2 1
2 3 1
2 1 4 3
2 4 1 5 3
2 1 3 4 6 5 A
2 3 1 4 6 7 5 A
2 1 4 3 6 5 8 7
2 4 1 6 3 8 5 9 7
2 1 3 4 5 6 7 8 10 9 B
2 3 1 4 5 6 7 8 10 11 9 B
2 1 4 3 5 6 7 8 10 9 12 11 B
2 4 1 5 3 6 7 8 10 12 9 13 11 B
2 1 3 4 6 5 7 8 10 9 11 12 14 13 B
2 3 1 4 6 7 6 8 10 11 9 12 14 15 13 B
2 1 4 3 6 5 8 7 10 9 12 11 14 13 16 15 
```
考虑分析奇偶性。我们可以发现，当 $n$ 比较小且为偶数时，必定会在 $a_{2\times i-1}$ 和 $a_{2\times i}$ 两个数之间上交换。此时在偶数行中，要么是相邻的互换，要么不变。此时我们发现已经无法进展下去了，注意到表里后面有字母的的数字行，其中貌似有一些规律，比如在 $A$ 组中，我们观察到第一行出现了 $3$ 和 $4$ 同时第二行有 $4$。而 $B$ 组则更为明显，第一行存在 ```3 4 5 6 7 8``` 然后下一行存在 ```4 5 6 7 8``` 以此类推。其实如果我们数据多了，我们发现这个现象是很普遍的，并且形式上相近与三角形。

那么我们考虑换个思路，不妨用归纳法和找规律解决。接下来题目中的操作均用 $S\left(i,j\right)$ 来代替。

设 $n$ 为偶数，那么操作 $S\left(1,n\right)$ 相当于连续操作 $S\left(1,n-2\right)$ 和 $S\left(3,n\right)$。接下来的操作就比较难想了。我们考虑对在偶数行中的变的位置和不变的位置进行操作，我们之间将其变为二进制的形式。这样做的理由是：如果 $a_{2\times i-1}$ 和 $a_{2\times i}$ 进行操作，交换后就是 $1$ 所以可以将 $n$ 次操作后的位置上的数的结果看做是一个二进制数。我们设这个二进制数为 $M$ 则这两个操作就等价于在每一个位置上异或。根据异或的学习，我们不难发现（其中的 $zy$ 表示左移操作）：
$$M^\prime=M\oplus\left(M \ zy  \ 1\right)$$
然后之间把左移的操作放在每一个异或里面去，由于异或的分配律，然后展开式子，观察前面的系数，我们整理到一起可以发现这个正好是杨辉三角形的样子。近一步归纳我们可以得到：
- 当 $a_{2\times i-1}$ 和 $a_{2\times i}$ 的位置交换时，必定存在 $\binom{\frac{n}{2}-1}{i-1}$ 为奇数。

此时我们就分析完了偶数行的情况。奇数行同理，我们可以看成 $S\left(1,n-1\right)$ 和 $S\left(2,n\right)$ 的两次操作，同样分析我们将其转化为上一个偶数行的情况，分类讨论即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
long long t,n,k;
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
//bool cheak(int l,int r){
//	if(((l/2-1)&(r/2))==r/2){
//		return true;
//	}
//	return false;
//}
int main(){
	read(t);
	while(t--){
		cin>>n>>k;
		k--;
		//开始分类讨论。 
		if(n%2==0){
			if(((n/2-1)&(k/2))==k/2){
			    k^=1;
			}
			write(k+1);
			printf("\n");
		}
		else{
			if(k){
				k--;
				if(((n/2-1)&(k/2))==k/2){
				    k^=1;
				}
				//不要忘了在操作后加回去。 
				k++;	
			}
			if(((n/2-1)&(k/2))==k/2){
				k^=1;
			}
			write(k+1);
			printf("\n");
		}
	}
	return 0;
}
```
## 后记。
讨论区里提到了许多高水平选手只用了半小时，那么像我这样前前后后用了将近两个个半小时的菜鸡是不是没有救了。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

