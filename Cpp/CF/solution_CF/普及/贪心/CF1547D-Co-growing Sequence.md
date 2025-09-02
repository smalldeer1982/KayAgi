# Co-growing Sequence

## 题目描述

A sequence of non-negative integers $ a_1, a_2, \dots, a_n $ is called growing if for all $ i $ from $ 1 $ to $ n - 1 $ all ones (of binary representation) in $ a_i $ are in the places of ones (of binary representation) in $ a_{i + 1} $ (in other words, $ a_i \:\&\: a_{i + 1} = a_i $ , where $ \& $ denotes [bitwise AND](http://tiny.cc/xpy9uz)). If $ n = 1 $ then the sequence is considered growing as well.

For example, the following four sequences are growing:

- $ [2, 3, 15, 175] $ — in binary it's $ [10_2, 11_2, 1111_2, 10101111_2] $ ;
- $ [5] $ — in binary it's $ [101_2] $ ;
- $ [1, 3, 7, 15] $ — in binary it's $ [1_2, 11_2, 111_2, 1111_2] $ ;
- $ [0, 0, 0] $ — in binary it's $ [0_2, 0_2, 0_2] $ .

The following three sequences are non-growing:

- $ [3, 4, 5] $ — in binary it's $ [11_2, 100_2, 101_2] $ ;
- $ [5, 4, 3] $ — in binary it's $ [101_2, 100_2, 011_2] $ ;
- $ [1, 2, 4, 8] $ — in binary it's $ [0001_2, 0010_2, 0100_2, 1000_2] $ .

Consider two sequences of non-negative integers $ x_1, x_2, \dots, x_n $ and $ y_1, y_2, \dots, y_n $ . Let's call this pair of sequences co-growing if the sequence $ x_1 \oplus y_1, x_2 \oplus y_2, \dots, x_n \oplus y_n $ is growing where $ \oplus $ denotes [bitwise XOR](http://tiny.cc/bry9uz).

You are given a sequence of integers $ x_1, x_2, \dots, x_n $ . Find the lexicographically minimal sequence $ y_1, y_2, \dots, y_n $ such that sequences $ x_i $ and $ y_i $ are co-growing.

The sequence $ a_1, a_2, \dots, a_n $ is lexicographically smaller than the sequence $ b_1, b_2, \dots, b_n $ if there exists $ 1 \le k \le n $ such that $ a_i = b_i $ for any $ 1 \le i < k $ but $ a_k < b_k $ .

## 样例 #1

### 输入

```
5
4
1 3 7 15
4
1 2 4 8
5
1 2 3 4 5
4
11 13 15 1
1
0```

### 输出

```
0 0 0 0 
0 1 3 7 
0 1 0 3 2 
0 2 0 14 
0```

# 题解

## 作者：KSToki (赞：6)

# 题目大意
给定一个长度为 $n$ 的数组 $a$，你需要构造一个字典序最小的数组 $b$，使得对于任意 $1\le i<n$，$(a_i \operatorname{xor} b_i)\operatorname{and} (a_{i+1}\operatorname{xor}b_{i+1})=(a_i \operatorname{xor} b_i)$。
# 题目分析
这玩意肯定有解，那 $b_1=0$ 一定是字典序最小的，可以发现只需要将 $a_2$ 对应在 $(a_1 \operatorname{xor} b_1)$ 中是 $1$ 的 $0$ 改成 $1$ 是充要的，直接扫过去模拟即可，而且不需要手动拆二进制，可以借助位运算。
# 代码
主函数特别短。
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,x,y;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		x=read();
		printf("0");
		while(--n)
		{
			y=read();
			printf(" %d",((y|x)^y));
			x|=y;
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Forever1507 (赞：2)

这场比赛貌似是这个菜鸡的第一场 CF 呢。

回归正题，我们可以发现，对于一个满足题意的数组，二进制下所有的 $a_{i-1} ~\operatorname{xor}~ b_{i-1}$ 中有的 $1$ ，$a_i~\operatorname{xor}~b_i$里必须也有，那么，可以发现 $b_i$ 只要把 $a_{i-1}~\operatorname{or}~a_i$ 中 $a_i$ 所没有的 $1$ 全补齐就行了

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],ans[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int now;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=2;i<=n;i++){
			int tmp=a[i];
			now=a[i]|a[i-1];
			ans[i]=now-tmp;//计算能补完1的最小的b[i]
			a[i]=a[i]^ans[i];//要记得异或一下
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		puts("");
	} 
	return 0;
}

```


---

## 作者：Meaninglessness (赞：1)

## D. Co-growing Sequence
**题目大意:**
> 有一种特殊关系：两个数 $a$,$b$ 如果在二进制下 $b$ 与 $a$ 公共位 $b$ 都比 $a$ 大，则满足此关系。如：$a=(1100)_2,b=(1110)_2$，$a=(1000)_2,b=(101000)_2$ 等。
> 现给出一个数组 $x$，输出相配的最小字典序数组 $y$，使得 $a=x_i \oplus y_i$ 与 $b=x_{i+1} \oplus y_{i+1}$ 满足特殊要求。

**解题思路:**

这题有一个关键：输出**最小字典序**数组。

则要保证靠前的数尽量要小，由于 $y_1$ 一定没有限制，故 $y_1=0$。

然后我们记 $last_j$ 表示 $x_1$ 的第 $j$ 位与 $y_1$ 的第 $j$ 位 $(0)$ 的异或值。

对于以后的答案，分为一些情况：
记 $a_i(2\le i \le n)$ 转化二进制后的第 $j$ 位为 $pos_j$。

1. 若 $last_j=0,pos_j=0$ 则答案此位可以取 $0$，$last_j$ 仍为 $0$。
2. 若 $last_j=0,pos_j=1$ 则答案此位可以取 $0$，$last_j$ 改为 $1$。
3. 若 $last_j=1,pos_j=0$ 则答案此位需取 $1$，$last_j$ 仍为 $1$。
4. 若 $last_j=1,pos_j=1$ 则答案此位可以取 $0$，$last_j$ 仍为 $1$。

把每次求出的答案输出即可。

**代码实现:[Code](https://www.luogu.com.cn/paste/2ukhufqg)　时间复杂度$O(Tn$ $\log n)$**

---

## 作者：__HHX__ (赞：0)

# 思路
因为字典序最小,我们只需要让 $b_i$ 越小越好。

很明显 $b_1 = 0$ 是一定合法且字典序最小的。

$$(a_i \oplus b_i) \& (a_{i + 1} \oplus b_{i + 1}) = a_i$$

$$(a_i \oplus b_i) \& (a_{i + 1} \oplus a_i) = b_{i + 1}$$

因为上一个数的 $b_i$ 和 $a_i$ 还有此数 $a_{i+1}$ 都是已知的，所以这道题变成了简单的递推。
# 代码 
```cpp
#include <iostream>

using namespace std;

const int MaxN = 2e5 + 3;

int a[MaxN];

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    cout << "0 ";
    for (int i = 2; i <= n; i++) {
      cout << ((a[i] ^ a[i - 1]) & a[i - 1]) << ' ';
      a[i] |= ((a[i] ^ a[i - 1]) & a[i - 1]);
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：Saber___ (赞：0)

## 思路

一个数 $xor \ 0$ 等于它本身

一个数 $and$ 本身等于 $0$

那么为了**字典序最小**，$b_1$ 肯定是 $0$，后面答案**唯一**。为了使 $a_i$ $and$ $a_{i - 1}\ =\ a_i$，将 $a_i $ 和 $ a_{i-1}$ 换成二进制，使 $ a_{i-1}$ 有 $1$ 的位置，$a_i$ 也要是 $1$，那么就用 $a_{i-1}\ or\ a_i$，找出所有有 $1$ 的位置，然后再减去 $a_i$ 上原本有的 $1$，这样这个数与 $a_i$ $xor$ 后所有 $1$ 的位置肯定都包含了 $a_{i-1}$ 上有 $1$ 的位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/my70phfq.png)

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin >> t;
	while (t -- )
	{
		int n;
		cin >> n;
		int a[n + 10] ;
		for (int i = 1; i <= n; i ++ )
		{
			cin >> a[i];
		}
		cout << 0 << " ";
		for (int i = 2; i <= n; i ++ )
		{
			int x = (a[i] | a[i - 1]) - a[i];
			a[i] ^= x;
			cout << x << " ";
		}
//		cout << endl;
//		for (int i = 1; i <= n; i ++ ) cout << a[i] << " ";
		cout << endl;
	}
	return 0;
}
```
## 总结

**位运算**，要好好琢磨琢磨。

---

## 作者：dalao_see_me (赞：0)

## 题目大意
给一个序列 $x$，你需要求出序列 $y$（字典序最小），使得新序列（$x_i$ 和 $y_i$ 异或）满足性质 $a_i\  \&\  a_{i+1}=a_i$（其中 $\&$ 为按位与）。
## 做法
因为要 $y$ 字典序最小，所以 $x_1$ 不动，$x_i$（$i>1$）只需要把 $x_{i-1}$ 是 $1$ 的位，$x_i$ 是 $0$ 的位改为 $1$ 就好了。此时计算 $y_i$ 的值就好了。

上代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int _, n;
struct Node {
	int len;
	int w[33];
} a[N];
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -f; c = getchar();}
	while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}
int main() {
	_ = read();
	while (_--) {
		n = read();
		for (int i = 1; i <= n; i++) {
			memset(a[i].w, 0, sizeof(a[i].w));
			int d = read(), x = 0;
			int &len = a[i].len;
			len = 0;
			while (d) {
				a[i].w[++len] = d % 2 + x;
				d >>= 1;
				x = a[i].w[len] / 2;
				a[i].w[len] %= 2;
			}
			if (x) a[i].w[++len] = 1;
		}
		putchar('0');
		for (int i = 2; i <= n; i++) {
			int y = 0;
			for (int j = 1; j <= 30; j++)
				if (a[i - 1].w[j] > a[i].w[j])
					y += 1 << j - 1, a[i].w[j] = 1;
			printf(" %d", y);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：YuanZihan1225 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1547D)

# 题意分析：

由题显然，我们要让 $(a _ {i - 1} \oplus b _ {i - 1})$ 中有的 1 在 $(a _ {i} \oplus b _ {i}$ 才能够保证满足题目所给的式子，所以我们要用 $b _ i$ 来补齐 $a _ i\ or \ a _ {i - 1}$ 中 $a _ {i}$ 缺少的 1 即可，所以代码也很短，只需要存两个数，再利用位运算输出即可。

# 代码见下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a, b;
inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
inline void print(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
signed main()
{
	t = read();
	while(t--)
	{
		n = read(), a = read(), putchar('0'), putchar(' ');//先输入一个a，再输出0，因为第一个b一定是0
		for(int i = 2; i <= n; i++)
		{
			b = read();
			print((b | a) ^ b), putchar(' ');//b要补齐a中没有的1
			a |= b;//把a中的1补齐
		}
		puts("");
	}
	return 0;
}
```

---

