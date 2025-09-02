# Shinju and the Lost Permutation

## 题目描述

Shinju loves permutations very much! Today, she has borrowed a permutation $ p $ from Juju to play with.

The $ i $ -th cyclic shift of a permutation $ p $ is a transformation on the permutation such that $ p = [p_1, p_2, \ldots, p_n]  $ will now become $  p = [p_{n-i+1}, \ldots, p_n, p_1,p_2, \ldots, p_{n-i}] $ .

Let's define the power of permutation $ p $ as the number of distinct elements in the prefix maximums array $ b $ of the permutation. The prefix maximums array $ b $ is the array of length $ n $ such that $ b_i = \max(p_1, p_2, \ldots, p_i) $ . For example, the power of $ [1, 2, 5, 4, 6, 3] $ is $ 4 $ since $ b=[1,2,5,5,6,6] $ and there are $ 4 $ distinct elements in $ b $ .

Unfortunately, Shinju has lost the permutation $ p $ ! The only information she remembers is an array $ c $ , where $ c_i $ is the power of the $ (i-1) $ -th cyclic shift of the permutation $ p $ . She's also not confident that she remembers it correctly, so she wants to know if her memory is good enough.

Given the array $ c $ , determine if there exists a permutation $ p $ that is consistent with $ c $ . You do not have to construct the permutation $ p $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3, 4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the permutation $ [1] $ satisfies the array $ c $ .

In the second test case, the permutation $ [2,1] $ satisfies the array $ c $ .

In the fifth test case, the permutation $ [5, 1, 2, 4, 6, 3] $ satisfies the array $ c $ . Let's see why this is true.

- The zeroth cyclic shift of $ p $ is $ [5, 1, 2, 4, 6, 3] $ . Its power is $ 2 $ since $ b = [5, 5, 5, 5, 6, 6] $ and there are $ 2 $ distinct elements — $ 5 $ and $ 6 $ .
- The first cyclic shift of $ p $ is $ [3, 5, 1, 2, 4, 6] $ . Its power is $ 3 $ since $ b=[3,5,5,5,5,6] $ .
- The second cyclic shift of $ p $ is $ [6, 3, 5, 1, 2, 4] $ . Its power is $ 1 $ since $ b=[6,6,6,6,6,6] $ .
- The third cyclic shift of $ p $ is $ [4, 6, 3, 5, 1, 2] $ . Its power is $ 2 $ since $ b=[4,6,6,6,6,6] $ .
- The fourth cyclic shift of $ p $ is $ [2, 4, 6, 3, 5, 1] $ . Its power is $ 3 $ since $ b = [2, 4, 6, 6, 6, 6] $ .
- The fifth cyclic shift of $ p $ is $ [1, 2, 4, 6, 3, 5] $ . Its power is $ 4 $ since $ b = [1, 2, 4, 6, 6, 6] $ .

Therefore, $ c = [2, 3, 1, 2, 3, 4] $ .

In the third, fourth, and sixth testcases, we can show that there is no permutation that satisfies array $ c $ .

## 样例 #1

### 输入

```
6
1
1
2
1 2
2
2 2
6
1 2 4 6 3 5
6
2 3 1 2 3 4
3
3 2 1```

### 输出

```
YES
YES
NO
NO
YES
NO```

# 题解

## 作者：JS_TZ_ZHR (赞：3)

## 题意：

对于一个长为 $n$ 的排列 $p$，其前缀最大值为序列 $a$，定义排列 $p$ 的权值为 $a$ 中不同数的个数。现在对于 $0\le i\le n-1$ 的每个 $i$，给出 $[p_{n-i+1},\dots,p_n,p_1,p_2,\dots,p_{n-i}]$ 的权值，问是否有符合条件的排列 $p$。

## 题解：

显然当且仅当 $p_1=n$ 时 $p$ 的权值为 $1$，所以有解的一个必要条件就是给出的权值中有且仅有一个 $1$。

然后我们从这个 $1$ 开始考虑。由于每次向后相当于给出当前排列最后一个数放到第一个，所以权值的增加肯定不可能大于 $1$，于是可以~~合理猜想~~排除掉这个情况，剩下的都是符合要求的。[证明](https://codeforces.ml/blog/entry/101302?#comment-899523)

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int T,n,a[N],p;
bool flag;
signed main() {
	cin>>T;
	while(T--){
		flag=1,p=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==1&&!p)p=i;
			else if(a[i]==1)flag=0;
		}
		if(!p)flag=0;
		if(!flag){
			puts("NO");
			continue;
		}
		for(int i=1,pos=p;i<=n;i++){
			int nxt=pos+1;
			if(nxt==n+1)nxt=1;
			if(a[nxt]-a[pos]>1)flag=0;
			pos=nxt;
		}if(!flag){
			puts("NO");
			continue;
		}
		puts("YES"); 
	}
}
```


---

## 作者：E1_de5truct0r (赞：0)

## 思路

首先，由于 $p$ 在这里轮换了 $n$ 次，所以一定有且只有一次 $n$ 开头的情况，这个时候 $c_i=1$。如果没有 $c_i=1$ 或者有好几个 $c_i=1$，那么显然无解。

然后，我们从这个 $1$ 的位置开始找。我们考虑怎么排除不合法的情况。

- $\forall i,c_i-c_{i-1}\leq 1$。

	证明：每次移动相当于把队尾移到队头。
    
    1. 如果队尾是最大值：则队尾是 $n$，移到队头之后 $c_i=1$，不可能会比 $c_{i-1}$ 大超过 1。
    
    2. 如果队尾不是最大值：则去掉之后对于后面的 $c_i$ 个数没有影响，放到队头最多增加一个 $c_i$。
    
	综上，证毕。


---

那么，其他的情况是否都有解呢？

答案是肯定的。因为无论如何，每次按照前面的 $c$ 构造，要么放大的要么放小的，总之能够造出来一个解。

## 代码实现

我们只需要完成两个操作：

- 判断 $c$ 数组中是否恰好只有一个 $1$，并记录 $1$ 的位置。

	如果没有找到 $1$ 或者有很多个 $1$，那么输出 `NO`。

- （假设找到了）那么从这个唯一的**环上**找一整圈。

	如果有，输出 `NO`；否则输出 `YES`。

实现比较简单，就不放代码了。

---

