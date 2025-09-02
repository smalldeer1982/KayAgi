# Permutations & Primes

## 题目描述

You are given a positive integer $ n $ .

In this problem, the $ \operatorname{MEX} $ of a collection of integers $ c_1,c_2,\dots,c_k $ is defined as the smallest positive integer $ x $ which does not occur in the collection $ c $ .

The primality of an array $ a_1,\dots,a_n $ is defined as the number of pairs $ (l,r) $ such that $ 1 \le l \le r \le n $ and $ \operatorname{MEX}(a_l,\dots,a_r) $ is a prime number.

Find any permutation of $ 1,2,\dots,n $ with the maximum possible primality among all permutations of $ 1,2,\dots,n $ .

Note:

- A prime number is a number greater than or equal to $ 2 $ that is not divisible by any positive integer except $ 1 $ and itself. For example, $ 2,5,13 $ are prime numbers, but $ 1 $ and $ 6 $ are not prime numbers.
- A permutation of $ 1,2,\dots,n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, there are $ 3 $ pairs $ (l,r) $ with $ 1 \le l \le r \le 2 $ , out of which $ 2 $ have a prime $ \operatorname{MEX}(a_l,\dots,a_r) $ :

- $ (l,r) = (1,1) $ : $ \operatorname{MEX}(2) = 1 $ , which is not prime.
- $ (l,r) = (1,2) $ : $ \operatorname{MEX}(2,1) = 3 $ , which is prime.
- $ (l,r) = (2,2) $ : $ \operatorname{MEX}(1) = 2 $ , which is prime.

 Therefore, the primality is $ 2 $ .In the second test case, $ \operatorname{MEX}(1) = 2 $ is prime, so the primality is $ 1 $ .

In the third test case, the maximum possible primality is $ 8 $ .

## 样例 #1

### 输入

```
3
2
1
5```

### 输出

```
2 1
1
5 2 1 4 3```

# 题解

## 作者：wanghaoran00 (赞：3)

### 思路
$1$ 不是质数，$2$ 和 $3$ 是最小的两个质数，若使更多的集合满足 $\operatorname {MEX}$ 为质数，就让更多的集合包含 $1$ 不包含 $2$ 和 $3$，让 $1$ 在中间，$2,3$ 在两端即可。（设前半段 $a$，后半段 $b$，$a+b$ 和恒定，由基本不等式得 $a=b$ 时 $a\times b$ 最大，即 $1$ 在中间，$2,3$ 在两端。）

ACcode
```
#include<bits/stdc++.h>
using namespace std;
int n,t,x;
int main(){
    cin>>t;
    while(t--){
        x=4;
        scanf("%d",&n);
        if(n==1){
            printf("1\n");
        }
        else if(n==2){
            printf("2 1\n");
        }
        else{
            printf("2 ");
            for(int i=2;i<=n/2;i++){
                printf("%d ",x);
                x++;
            }
            printf("1 ");
            for(int i=n/2+2;i<n;i++){
                printf("%d ",x);
                x++;
            }
            printf("3\n");
        }
    }
    return 0;
}
```

---

## 作者：Larryyu (赞：1)

## _Description_
你需要构造一个长度为 $n$ 的序列，使其满足以下条件：
- 包含 $1\sim n$ 的所有数
- 最大化满足如下条件的 $(l,r)$ 的对数：$1\leq l\leq r\leq n$ 且 $\operatorname{MEX}(a_l,a_{l+1}\dots a_{r-1},a_r)$ 为质数

在此题中 $\operatorname{MEX}$ 的定义是第一个不在序列的正整数（而非非负整数）。

构造任意一种即可。
## _Solution_
对于 $n=1$，排列只有一种，输出即可。

对于 $n=2$，两种排列答案都是一，直接输出任意一种即可。

思考 $\operatorname{MEX}$ 的定义是什么，是第一个不在序列的正整数（仅对此题而言）。所以当 $1$ 在序列时，$\operatorname{MEX}=2$，而 $2$ 又是质数，所以我们使包含 $1$ 的 $l,r$ 对数越多越好。

设 $1$ 在一个长度为 $x$ 的序列中的第 $i$ 位，所以包含 $1$ 的对数应该为 $(i-1)\times (x-i)$ 个。

因为和一定，差小积大（相关证明可以学习一下），所以当 $i=\lceil \dfrac{x-1}{2}\rceil$ 时个数最多。 

而如果 $1,2,3$ 都在序列里 $\operatorname{MEX}$ 就会变成 $4$，不是质数，所以我们让 $3,2$ 分别在第一个和最后一个即可。

其他位置随便填。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
void solve(){
	int n;
	cin>>n;
	int now=3;
	if(n<3){
		for(int i=1;i<=n;i++){
			cout<<i<<" ";
		}
		return;
	}
	cout<<"3 ";
	for(int i=1;i<n-1;i++){
		if(i+1==ceil((float)n/2)) cout<<"1 "; //i+1是因为前面有个3
		else cout<<++now<<" ";
	}
	cout<<2<<endl;
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Walrus (赞：1)

## 简要分析题意
给定 $n$，要求构造一个关于 $n$ 的排列，使得数组的**素数属性最大化**。

## 初步分析
阅读题目发现，我们首先需要研究出 $a$ 数组的素数属性，虽然 CF 的题目翻译不是很清楚，但是不妨碍发现开头所说的**素数属性**。

- 对于任意一个子区间 $1 \leq l \leq r \leq n$，数组 $a_l \sim a_r$ 的 MEX 为素数的区间个数，也就是说一个区间的子区间的 MEX 值为素数时，会对答案产生贡献。
- 一个数组的 MEX 指的是 数组中第一个没出现的非负整数。例如 $[1,4]$ 的 MEX 为 $2$，因为 $2$ 是此数组中第一个未出现的非负整数。

这让我想到了很久以前参加的[小猴编程 4 月月赛 I & GMOI Round 2 的 T2](https://www.luogu.com.cn/problem/P9199?contestId=104457)。其实关于 MEX 的做题思路大多都一样。

## 整体思路
不难发现，这显然是一道**贪心与构造的题，毕竟有 SPJ**。

#### Top1
首先想到 $1$ 不是素数，那就要考虑 $1$ 摆放的位置，为了使贡献最优化，我们应该将 $1$ 放在中间，换句话说，$1$ 的位置具有特殊性。

#### Top2
$1$ 的位置考虑完了，很容易联想到 $2$ 和 $3$ 同样具有特殊性。

我们尽量不把 $2$ 和 $3$ 放一起，也就是说让所有区间能不同时包含 $2$ 和 $3$，就不同时包含 $2$ 和 $3$。所以考虑将 $2$ 和 $3$ 放在数组两端，这样区间同时包含上述两者的概率就会大大减小，这正是我们想要的。

## 参考代码

```
if (n >= 2) 
	cout << 2;
......
if (n >= 3)
	cout << 3;
cout << '\n';
```
先分别判断 $n$ 是否大于 $2$ 和 $3$，再考虑是否输出。

```
for (int i = 4; i <= (n >> 1) + 2; i++) 
	cout << ' ' << i;
if(n > 1)
	cout << ' ' << 1;
else
	cout << 1;
for (int i = (n >> 1) + 3; i <= n; i++) 
	cout << ' ' << i;
```
头和尾处理完了，接下来就是处理中间，尽量 $1$ 放中间，其余随便放。

感谢观看。

---

## 作者：Crazyouth (赞：1)

Update on 7.25：修正了一点笔误。

**翻译**

给定 $n$，求一个 $1$ 到 $n$ 的排列使满足这个排列的一个子区间 $[l,r]$ 的 $\operatorname{MEX}$ 为质数的正整数对 $(l,r)$ 尽可能多（$\operatorname{MEX}$ 指最小的未在序列中出现的正整数）。

**分析**

首先易证满足条件的 $[l,r]$ 中一定要有 $1$，所以为使 $(l,r)$ 多，就要让 $1$ 摆在中间。其次，假如 $[l,r]$ 中还有其他质数，那它的 $\operatorname{MEX}$ 就不一定是质数了，因此要尽可能避免这种情况，一种解决方法是把最小的两个质数，即 $2,3$ 放在头尾两端，这样可以使较多的 $[l,r]$ 的 $\operatorname{MEX}$ 是 $2$ 或 $3$，其他数随便摆就行。

P.S. 赛时怕吃罚时，于是顺道加了个 $n\le4$ 的特判，现在想来只需要判 $n\le2$ 就行。下面给出的是我赛时的代码。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n==1)//特判
		{
			cout<<1<<endl;
			continue;
		}
		if(n==2)
		{
			cout<<"1 2"<<endl;
			continue;
		}
		if(n==3)
		{
			cout<<"2 1 3"<<endl;
			continue;
		}
		if(n==4)
		{
			cout<<"3 1 4 2"<<endl;
			continue;
		}
		cout<<"2 ";//最小质数
		for(int i=1;i<=(n-3)/2;i++) cout<<3+i<<' ';
		cout<<"1 ";//1在中间
		for(int i=4+(n-3)/2;i<=n;i++) cout<<i<<' ';
		cout<<"3"<<endl;//次小质数
	}
	return 0;
} 

---

## 作者：Zimo_666 (赞：0)

## B. Permutations & Primes

考虑对于 $1$ 来说，必须要尽可能的区间包含它。我们对于 $a$ 左边的区间设为 $l_1$，对于 $a$ 右边的区间设为 $l_2$。

显然 $l_1+l_2$ 是定值，我们考虑包含 $1$ 的区间数目为 $l_1\times l_2$。显然我们有当 $l_1=l_2$ 时，区间数目取到最大值。

再考虑 $2,3$ 的位置，显然要求离 $1$ 越远越好。不如放在首尾。

最后其他数随便填即可，因为不管怎么样这些数区间内的子区间的 $\text{mex}$ 一定不合法。

[Code](https://codeforces.com/contest/1844/submission/223179793)

---

## 作者：Coffee_zzz (赞：0)

### 分析

我们首先分析 $\operatorname{MEX}(a_l,\dots,a_r)$ 什么时候能取到质数。

我们知道，$1$ 不是质数，所以如果 $a_l,\dots,a_r$ 不包含 $1$，则 $\operatorname{MEX}(a_l,\dots,a_r)$ 就一定为 $1$，不是质数。

我们还知道，$2$ 和 $3$ 都是质数，所以如果 $a_l,\dots,a_r$ 包含 $1$ 且不包含 $2$ 或 $3$，$\operatorname{MEX}(a_l,\dots,a_r)$ 就一定为 $2$ 或 $3$，是质数。

所以，我们要让包含 $1$，且不包含 $2$ 或 $3$ 的子序列尽可能多，那我们就把 $2$ 和 $3$ 放到排列的两侧，$1$ 放到正中间（如果 $n$ 是偶数的话就放在 $\dfrac{n}{2}$ 或 $\dfrac{n}{2}+1$ 的位置）即可。正确性显然。

### 代码

```c++
int a[200005];
void solve(){
	int n=read();
	if(n==1) cout<<"1\n";
	else if(n==2) cout<<"1 2\n";
	else{
		int cnt=1;
		for(int l=1,r=n;l<r;l++,r--) a[l]=++cnt,a[r]=++cnt;
		a[n/2+1]=1;
		for(int i=1;i<=n;i++) cout<<a[i]<<' ';
		cout<<endl;
	}
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

注意到**如果一个子区间内不含 $1$，那么它的 $\operatorname{mex}$ 一定为 $1$，对答案的贡献为 $0$**。因此我们考虑让包含 $1$ 的子区间尽可能多，即把 $1$ 放在排列正中间（$\lfloor \dfrac{n+1}{2} \rfloor$）。

进一步发现 $2,3$ 都是质数，因此如果一个子区间包含 $1$ 而不同时包含 $2,3$，那么它对答案就有贡献。容易想到的思路是把 $2,3$ 分别放在排列第一个和末尾。其他位置随意填即可。

至此，做完了。



---

