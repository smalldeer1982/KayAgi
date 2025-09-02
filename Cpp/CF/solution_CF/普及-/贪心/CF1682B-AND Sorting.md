# AND Sorting

## 题目描述

You are given a permutation $ p $ of integers from $ 0 $ to $ n-1 $ (each of them occurs exactly once). Initially, the permutation is not sorted (that is, $ p_i>p_{i+1} $ for at least one $ 1 \le i \le n - 1 $ ).

The permutation is called $ X $ -sortable for some non-negative integer $ X $ if it is possible to sort the permutation by performing the operation below some finite number of times:

- Choose two indices $ i $ and $ j $ $ (1 \le i \lt j \le n) $ such that $ p_i \& p_j = X $ .
- Swap $ p_i $ and $ p_j $ .

Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Find the maximum value of $ X $ such that $ p $ is $ X $ -sortable. It can be shown that there always exists some value of $ X $ such that $ p $ is $ X $ -sortable.

## 说明/提示

In the first test case, the only $ X $ for which the permutation is $ X $ -sortable are $ X = 0 $ and $ X = 2 $ , maximum of which is $ 2 $ .

Sorting using $ X = 0 $ :

- Swap $ p_1 $ and $ p_4 $ , $ p = [2, 1, 3, 0] $ .
- Swap $ p_3 $ and $ p_4 $ , $ p = [2, 1, 0, 3] $ .
- Swap $ p_1 $ and $ p_3 $ , $ p = [0, 1, 2, 3] $ .

Sorting using $ X = 2 $ :

- Swap $ p_3 $ and $ p_4 $ , $ p = [0, 1, 2, 3] $ .

In the second test case, we must swap $ p_1 $ and $ p_2 $ which is possible only with $ X = 0 $ .

## 样例 #1

### 输入

```
4
4
0 1 3 2
2
1 0
7
0 1 2 3 5 6 4
5
0 3 2 1 4```

### 输出

```
2
0
4
1```

# 题解

## 作者：yitian_ (赞：8)

## 题目分析

这道题目要求找到一个最大的整数 $X$，使得给定的排列 $p$ 可以通过一系列操作变成有序的。每次操作可以选择两个下标 $i$ 和 $j$，满足 $p_i \mathbin{\&} p_j = X$，然后交换这两个数。

## 思路

首先，我们得知道，如果两个数的二进制表示在某一位上都为 $1$，那么它们的按位与运算的结果就在该位上也为 $1$，否则为 $0$。因此，如果一个排列可以通过一系列这样的操作变成有序的，那么它的每一对相邻元素在二进制表示上的某一位必须有共同的 $1$，否则无法通过操作使它们交换位置。

因此，我们可以遍历排列中相邻的两个数，找到它们的二进制表示中最高位相同的位置，然后取这些位置中的最小值作为 $X$。这样，我们就可以保证通过一系列操作将排列变成有序的。

步骤如下：

1. 遍历排列中的每一对相邻元素。
2. 对于每一对相邻元素，找到它们的二进制表示中最高位相同的位置。
3. 记录所有相邻元素的最高位相同的位置中的最小值，作为 $X$。

通过这个思路，我们可以保证选取的 $X$ 能够满足通过一系列操作将排列变成有序的要求。

## C++ 代码实现

```c
#include<bits/stdc++.h>
using namespace std;

int p[200010]; // 声明一个数组 p，用于存储排列的元素

int main() 
{
    int t,n; // t 为测试用例的数量，n 为当前测试用例的排列长度
    cin >> t; // 读取测试用例数量
    while(t--) // 遍历每个测试用例
    {
        cin >> n; // 读取当前测试用例的排列长度
        int ans=-1; // 初始化 ans 为 -1，用于存储最终的结果
        for(int i=0;i<n;i++) // 遍历当前排列的每个元素
        {
            cin >> p[i]; // 读取当前排列的第 i 个元素
            if(p[i]!=i) // 如果当前元素不等于它在排列中的位置 i
            {
                if(ans==-1) // 如果 ans 尚未被赋值
                {
                    ans=p[i]; // 将 ans 赋值为当前元素的值
                }
                else // 如果 ans 已经被赋值
                {
                    ans&=p[i]; // 对 ans 和当前元素进行按位与操作，并更新 ans 的值
                }
            }
        }
        cout << ans << endl; // 输出当前测试用例的结果
    }
    return 0; // 程序正常结束
}
```

---

## 作者：EternalHeart1314 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF1682B)

# 思路

由于最后要求排列有序，所以一开始没有被排好序的数，都要进行交换，至于具体怎么交换，并不重要，最大答案就是将它们都按位与一次的数。

就拿样例为例：
```
7
0 1 2 3 5 6 4
```
其中，$\{4,5,6\}$ 都没有被排好序，所以不管怎么样，他们必须进行交换，最大答案即为 $4\And5\And6=4$。

# Code
```
#include<bits/stdc++.h>
using namespace std;

const int N(2e5 + 7);
int t, n, x, tot, a[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> n;
		tot = 0;
		for(int i(0); i < n; ++ i) {
			cin >> x;
			if(x != i) {
				a[tot ++] = x;
			}
		}
		for(int i(1); i < tot; ++ i) {
			a[0] &= a[i];
		}
		cout << a[0] << '\n';
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：听取MLE声一片 (赞：4)

update：修改逻辑问题。

直接送我 -83 的一道题。

首先不难看出所有不在原位置的所有数都要进行交换，还有 & 满足结合律，所以所有不在位置上的数 & 起来即可。

我们来证明一下一定有解，排列一定有一个 0，将它和所有不在位置的数交换，& 显然结果都为 0，就能证明出一定有解。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
int n,a[N];
int main()
{
	int t=read();
	while(t--){
		n=read();
		vector<int>b;
		for(int i=0;i<n;i++){
			a[i]=read();
			if(a[i]!=i)
				b.push_back(i);
		}
		//cout<<b.size()<<' ';
		int ans=b[0];
		for(int i=1;i<b.size();i++)
			ans&=b[i];
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：zhangzirui66 (赞：2)

# 思路
这题的思路很简单，没在该在的位置上，就要去[按位与](https://blog.csdn.net/wan_ide/article/details/81108941)。关于是否有解，由于它是 $0∼n-1$ 的排列，所以一定可以排序，也一定有解。

---
**code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005], cnt;
int main(){
	int t, n;
	cin >> t;
	while(t --){
		int ans;
		cnt = 0;//多测要清空
		cin >> n;
		for(int i = 0; i < n; i ++){
			int x;
			cin >> x;
			if(x != i) a[++ cnt] = x;//不在位置上
		}
		ans = a[1];
		for(int i = 2; i <= cnt; i ++) ans = ans & a[i];
		cout << ans << "\n";
	}
	return 0;
}

```

---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1682B)

## 思路

每次输入 $a_i$，如果 $a_i$ 不在自己的位置上，也就是 $a_i\ne i$，那么就用 $ans\mathbin{\&}a_i$，得到答案。

要注意 $2$ 个点：

+ 如果找到的是第 $1$ 个不在位置上的 $a_i$，要把 $a_i$ 赋值给 $ans$，否则直接按位与会错。
+ 下标问题：$0\le i<n$。

```cpp
#include <iostream>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int ans = 0;
        bool First = false;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x != i) {
                if (!First) ans = x, First = true;
                else ans &= x;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：hdkghc (赞：1)

CF1682B 题目传送门：[CF1682B](https://www.luogu.com.cn/problem/CF1682B)。

# 题意简化

给定一个 $0 \sim n - 1$ 的排列 $p$，定义一次操作为对满足 $p_i \operatorname{and} p_j = X$ 的两数，交换 $p_i$ 和 $p_j$。问在若干次操作后（也可以不操作）能使原排列 $p$ 有序的最大的 $X$。

# 前置知识

$-1$ 的补码是 $(11111111111111111111111111111111)_2$（对 $32$ 位整数 `int` 而言）。

按位与：[OI Wiki 与](https://oi-wiki.org/math/bit/#%E4%B8%8E%E6%88%96%E5%BC%82%E6%88%96)

按位与满足：

$$a \operatorname{and} b = b \operatorname{and} a$$

即满足交换律。同时也满足结合律：

$$(a \operatorname{and} b) \operatorname{and} c = a \operatorname{and} ( b \operatorname{and} c)$$

我们暂且叫它 $1$ 式。当然，还有很重要的，我们叫 $2$ 式，~~但是像废话~~：

$$a \operatorname{and} a = a$$

当然，还有一个和 $-1$ 的补码有关：

$$-1 \operatorname{and} a = a$$

研究完这些奇奇怪怪的东西以后，就可以上代码了。

# 思路

首先先观察是否有解。~~既然题目没有说无解输出什么就说明肯定有解……~~  
我们可以发现，总有一个 $X = 0$ 满足题目要求。

现在再看题目。题目是可选取任意满足 $p_i \operatorname{and} p_j = X$ 的数，并不是相邻的两数，所以只需将位置不对的数【即 $p_i \ne i$（$i$ 从 $0$ 开始）】排序，使其所在位置正确即可。  
所以答案就是把位置不正确的数两两按位与后再按位与。再用 $1$ 式和 $2$ 式化简一下就变成了**把所有的位置不正确的数都按位与一遍！** 利用此性质，我们可以写出~~精简的~~代码。

会有一些注释。

# 代码

```cpp
/*********************************************************************
    程序名: 
    版权: Copyright (c) 2023~9999 hdkghc
    作者: hdkghc
    日期: 2023-10-09 21:04
    说明: This is a codeforces program.
*********************************************************************/
#include <bits/stdc++.h>
#define f1() for(int i = 1; i <= n; i++)
#define f2(i) for(int i = 1; i <= n; i++)
#define f3(i, from, to) for(int i = from; (from <= to) ? (i <= to) : (i >= to); i += (from <= to ? 1 : -1))
#define f4(i, from, to, step) for(int i = from; (from <= to) ? (i <= to) : (i >= to); i += (from <= to ? 1 : -1) * step)
#define f5(i, from, to, comp, cng) for(int i = from; comp(i, to); cng(i))
#define leq(tp) [](tp a, tp b) { return a <= b; }
#define geq(tp) [](tp a, tp b) { return a >= b; }
#define neq(tp) [](tp a, tp b) { return a != b; }
#define add1(tp) [](tp &a) { a++; }
using namespace std;
int t;

int _main()
{
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		int ans = -1; // -1 按位与上任何数都是它本身
		f3(i, 0, n - 1)
		{
			int x;
			cin >> x;
			if(x != i) // 位置不正确
			{
				ans &= x; // 全都按位与一遍
			}
		}
		cout << ans << endl; // 输出 X
	}
	return 0;
}
#ifdef _LOCAL_TEST
int main()
{
	string fn = (string)__FILE__ + (string)".out.txt";
	system(((string)"type nul > \"" + fn + (string)"\"").data());
	ofstream fout(fn);
	streambuf *outbuf = cout.rdbuf();
	cout.rdbuf(fout.rdbuf());
	clock_t st = clock();
	_main();
	clock_t tim = clock() - st;
	fout.close();
	cout.rdbuf(outbuf);
	system(("start notepad " + fn).data());
	cout << "Execute Time: " << (static_cast<double>(tim) / 1000.0) << endl;
	system("pause > nul");
	return 0;
}
#elif defined(INTERACTIVE)
int main()
{
    _main();
    system("pause > nul");
    return 0;
}
#else
int main()
{
	_main();
	return 0;
}

#endif
```

---

## 作者：xujingyu (赞：0)

因为 $n$ 个数都是在 $1$ 到 $n$ 之间，在不正确位置上的数都是要交换的，所以把每个不在正确位置上的数都与一遍即可，即若 $p_i\ne i$，则用答案与上它。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,p,ans;

signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		ans = -1e9;
		for(int i = 0;i < n;i++)
		{
			scanf("%d",&p);
			if(p != i)
			{
				if(ans == -1e9) ans = p;
				else ans &= p;
			}
		}
		printf("%d\n",ans);
	}
    return 0;
}
```

---

## 作者：Brute_Force (赞：0)

### 题意
通俗的讲，就是使一个自然数排列变得有序，而操作排列交换两数的前提是使 $p_1$ $p_2$ 指向一个数 $X$，并且 $p_1$ 按位与 $p_2$ 等于 $X$，问：$X$ 最大是多少？
### 前置知识
为了防止新手不懂，特意加入了按位与的知识。

$\&$ 这个符号代表按位与，把两个数转换成二进制，对应各位后开始按位与，如果两个数都为 $1$，才能使结果为 $1$，例如：$5$ 按位与 $9$。

先将 $5$ 转换成二进制即 $0101$；再将 $9$ 转换为二进制即 $1001$。再将它们按位与可知答案为 $0001$。
### 思路
选择一个存储器 $ans$ 设为 $-1$，因为 $0$ 按位与任何数都是 $0$。在排序的过程中储存每一次结果。

**本题多测！这一句话都要说吐血了！**

---

## 作者：CarrotMeow (赞：0)

## [CF1682B AND Sorting](https://www.luogu.com.cn/problem/CF1682B)

> 给定一个 $0 \sim n - 1$ 的序列 $p$，保证 $p$ 不是递增序列（即不完全有序）。可以选定一个自然数 $X$，进行有限次操作：
>
> - 选定 $i, j ~ (1 \leq i < j \leq n)$，调换 $p_i, p_j$。
> - 限定 $p_i \operatorname{bitand} p_j = X$。
>
> 求最大的可以使 $p = \{0, 1, \ldots, n - 1\}$ 的 $X$。

显而易见，有

$$ \forall x, y \in \mathbb N, ~ x \operatorname{bitand} y < x $$

令 $S \gets p_1 \operatorname{bitand} p_2 \operatorname{bitand} \cdots \operatorname{bitand} p_n$，根据上式，我们知道一定有 $X \leq S \leq n - 1$。

只有不处于正确位置（$p_i \neq i - 1$）的值需要调换。当我们需要调换 $p_i, p_j$ 时，必须满足 $p_i \operatorname{bitand} X = X$ 且 $p_j \operatorname{bitand} X = X$。将 $X$ 作为中间值，执行以下步骤：

- 调换 $p_i$ 和 $X$ 的位置；
- 调换 $p_i$ 和 $p_j$；
- 调换 $p_j$ 和 $X$ 的位置。

即可。可以发现，以上每一次交换的两个值进行 $\operatorname{bitand}$ 都为 $X$。

按照这种调换方法，可以将 $p$ 排序。[代码](https://codeforces.com/contest/1682/submission/246425050)。

---

## 作者：2021zjhs005 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1682B)。

题目大意
------------
给出长度为 $n$ 的序列 $a$，其中序列 $a$ 为 $0\sim n-1$ 的排列。

每次可以交换 $a_i$，$a_j$，使得序列升序。

请求出最大的 $X$，使得每个交换的 $a_i$，$a_j$ 都满足 $a_i\operatorname{and} a_j = X$。

solution
------------
首先我们需要了解按位与，可以[百度一下](https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E4%B8%8E/9601818?fr=ge_ala)。

其实 $a\operatorname{and} b$ 就是将 $a$，$b$ 转成二进制，然后**右对齐**，做“且”运算，得到的二进制**转换为十进制**的值就是 $a\operatorname{and} b$ 的值。

我们还需要知道按位与的几个性质：

- 交换律：$a\operatorname{and}b = b\operatorname{and}a$

- 结合律：$(a\operatorname{and}b)\operatorname{and}c = a\operatorname{and}(b\operatorname{and}c)$

- $a\operatorname{and}a = a$ ~~（我也不知道叫什么。。。）~~


------------

然后，对于每个交换的 $a_i$，$a_j$，一定都是和原本对应位置不符的，也就是 $a_i \ne i-1$（应为是 $0\sim n-1$，而不是 $1\sim n$，所以要减 $1$）。

由于可能有一个 $a_i$ 交换了多次，所以可以根据上面的性质 $3$，只保留 $1$ 个。

接着根据性质 $1$ 和性质 $2$，就可以得出结论：**把位置不正确的数全部按位与一遍**，即为答案。

~~（似乎答案只有一个。。。）~~


实现步骤
------------

注意 $T$ 组数据！

- 读入。

- 判断每个 $a$ 序列的数是不是原本位置。

  - 是，跳过。
  
  - 不是，存进一个数组或者 `vector` 里。
  
- 将所有数的结果按位与一遍。注意初始化：$ans\gets b_0$ ，然后从 $2$ 开始！


------------

代码就不给了，实现起来很简单，码量很少。


---

## 作者：shredded_beef_qwq (赞：0)

## 具体思路
我们可以先根据题目的意思进行思考，但我们思考后不难发现如果按照题目的意思写代码的话很麻烦，不好写，所以我们可以从样例分析。

通过观察样例 $1$ 中第一次询问，我们可以发现最终结果是输入的 $p$ 中与下标 $i$ 不同的数按位与之和，但一个样例并不能代表什么，所以我们可以继续观察一下下面几次询问，经观察后发现与我们前面所得到的结论相符合，所以我们这道题就可以按这一结论写。
## 提示
这道题下标从 $0$ 开始，而不是从 $1$ 开始。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n;
	cin>>t;
	while(t--){
		cin>>n;
		int x;
		int sum=-1;
		for(int i=1;i<=n;i++){
			cin>>x;
			if(x!=i-1){
				if(sum==-1) sum=x;
				else sum&=x;
			}
		}
		cout<<max(sum,0)<<endl;
	}
	return 0;
}
```

---

## 作者：__int127 (赞：0)

## CF1682B AND Sorting 题解

[**题目传送门**](https://www.luogu.com.cn/problem/CF1682B)

### 题目大意

本题有多组数据。

给定一个 $0\sim n-1$ 的排列 $p_1,p_2,\dots,p_{n-1},p_n$，保证初始序列无序。

你可以进行若干次操作，对于每次操作，你可以指定一个 $X$，在 $p_i\ \text{and}\ p_j=X$（$\text{and}$ 表示按位与）的情况下交换 $p_i$ 和 $p_j$，求出要使序列升序，每次操作最大的 $X$。

$1\le t\le10^4,2\le n\le2\times10^5,0\le p_i\le n-1$。

### 思路

~~一道水题。~~

不难发现已经有序的 $p$ 的前缀序列，是可以搁置在一边的，对于无序的 $p$ 的子序列是需要挨个按位与的，其实这道题不用求最大值，因为挨个按位与后最后的结果就是最大的。

所以我们需要开一个数组记录无序的子序列。

这里拓展一下按位与，你也可以[戳这里](https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E4%B8%8E/9601818?fr=ge_ala)或[戳这里](https://blog.csdn.net/m0_61567378/article/details/121991196)来了解。

按位与是位运算的一种，它表示两个数在二进制下每一位进行与运算，例如 $(7)_{10}$ 和 $(10)_{10}$，二进制表示为 $(7)_{10}=(111)_2,(10)_{10}=(1010)_2$）进行位与运算：

![](https://cdn.luogu.com.cn/upload/image_hosting/jo1o4sgf.png)

你需要知道的：$1\ \text{and}\ 1=1,1\ \text{and}\ 0=0,0\ \text{and}\ 1=0,0\ \text{and}\ 0=0$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, t, a[200005], k = 1, c;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1; i <= n; i++){
			cin >> t;
			if (i - 1 != t){
				a[k] = t;
				k++;
			}
		}
		c = a[1];
		for (int i = 2; i < k; i++){
			c &= a[i];
		}
		cout << c << "\n";
		k = 1;
	}
	return 0;
}
```

### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：Dreamer_Boy (赞：0)

首先，我们按照题意，可以用 $0$ 来作为中间的一个数来交换其他两个数，这种元素肯定是有的，那就是所有不在正确位置上的所有数的 AND 值，我们可以开一个数组 $a$ 来模拟这个过程，$a_i \mathbin{\&} a_j = X$，那这里的 $X$ 就起到我们的 $0$ 的作用了。

代码：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10;
int a[N];
int T, n;
int main() {
    cin >> T;
    while(T--) {
        cin >> n;
        int ans = INT_MIN;
        for(int i = 0 ;i < n;i ++ ){
            cin >> a[i];
            if(ans == INT_MIN && a[i] != i) ans = a[i];
            else if(a[i] != i) ans &= a[i];
        }
        cout << max(0, ans) << endl;
    }
    return 0;
}

```

---

## 作者：eb0ycn (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1682B)

## 主要思路
一开始我以为这是个排序题：只要元素 $p_i$ 和它排好序后的位置不一样，就让答案 $X$ 和 $p_i$ 做与运算。因为不管你怎么交换，那些不在原来位置的元素肯定都是要交换一遍的。

众所周知，任何几个正整数做与运算，结果一定不大于其中最小的数。再加上与运算的结合律，所以最终答案就是所有不在规定位置的 $p_i$ 做与运算。

另外这里要注意 $X$ 的初始值必须设为 $2^k-1$（$k$ 是正整数且 $X\ge2×10^5$）。这样任何一个不超过 $2\times10^5$ 的数跟 $X$ 做与运算，所得的数都是它本身。

------------

## 优化
偶然间，我看到了题目有个很特殊的条件：“给出一个 $0\sim n-1$ 的数列”。

也就是说，这个数列排好序以后一定是 $0,1,2,3,\cdots,n-1$。

所以我们就免去排序这一步了，只要 $p_i \ne i$，就让 $X$ 与上 $p_i$。


------------


## 上代码！
```c
#include <stdio.h>
int t,n,s[200000],ans;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        ans=(1<<20)-1;
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            scanf("%d",&s[i]);
            if(i-s[i])//判断s[i]的位置是否在规定位置
            {
                ans&=s[i];
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
//2023年6月就发了题解，但没通过，今天再发一遍！
//留作纪念。
```

众所周知，[CF](https://codeforces.com/)的题目一般很考验思维。

---

## 作者：_Glassy_Sky_ (赞：0)

这道题主打的就是一个位运算。

首先我们要先了解一下按位与：按位与的符号是 $\&$。其实就是把两个数先转换为二进制，然后逐位比较，如果相同的一位上都是 $1$，结果就是 $1$，否则为 $0$。

下面举一个小小的例子：

$3\&2$

$3$ 的二进制是 $(11)_2$，$2$ 的二进制是 $(10)_2$。我们从最后一位比起，$3$ 二进制的最后一位是 $(1)_2$，$2$ 的是 $(0)_2$，不是两位都是 $(1)_2$，此位为 $(0)_2$。再比较第二位，都是 $(1)_2$，结果是 $(1)_2$。合起来就是二进制中的 $(10)_2$，也就是十进制中的 $2$，也就是说，$3\&2$ 的结果是 $2$。

而此题具体的思路就是边输入边扫，如果此数的数值不等于它的位置，那我们的变量 $j$ 就加一，并且把这个值存进 $a$ 数组里，最后把所有存在 $a$ 数组里的元素全部扫一遍，每一遍都 $\&$ 一下，输出最后的值，就是最后的答案啦！

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int a[MAXN];
int main()
{
	int t, n, tot, j = 0, sum;
	cin >> t;
	while(t --)
	{
		j = 0;
		cin >> n;
		for(int i = 1; i <= n; i ++)
		{
			cin >> tot;
			if(tot != i - 1)
			{
				j ++;
				a[j] = tot;
			}
		}
		sum = a[1];
		for(int i = 2; i <= j; i ++)
			sum &= a[i];
		cout << sum << "\n";
	} 
	return 0;
}
```


---

