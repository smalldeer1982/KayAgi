# Lexicographically Largest

## 题目描述

Stack has an array $ a $ of length $ n $ . He also has an empty set $ S $ . Note that $ S $ is not a multiset.

He will do the following three-step operation exactly $ n $ times:

1. Select an index $ i $ such that $ 1 \leq i \leq |a| $ .
2. Insert $ ^\dagger $ $ a_i + i $ into $ S $ .
3. Delete $ a_i $ from $ a $ . Note that the indices of all elements to the right of $ a_i $ will decrease by $ 1 $ .

Note that after $ n $ operations, $ a $ will be empty.

Stack will now construct a new array $ b $ which is $ S $ sorted in decreasing order. Formally, $ b $ is an array of size $ |S| $ where $ b_i $ is the $ i $ -th largest element of $ S $ for all $ 1 \leq i \leq |S| $ .

Find the lexicographically largest $ ^\ddagger $ $ b $ that Stack can make.

 $ ^\dagger $ A set can only contain unique elements. Inserting an element that is already present in a set will not change the elements of the set.

 $ ^\ddagger $ An array $ p $ is lexicographically larger than a sequence $ q $ if and only if one of the following holds:

- $ q $ is a prefix of $ p $ , but $ p \ne q $ ; or
- in the first position where $ p $ and $ q $ differ, the array $ p $ has a larger element than the corresponding element in $ q $ .

Note that $ [3,1,4,1,5] $ is lexicographically larger than $ [3,1,3] $ , $ [\,] $ , and $ [3,1,4,1] $ but not $ [3,1,4,1,5,9] $ , $ [3,1,4,1,5] $ , and $ [4] $ .

## 说明/提示

In the first test case, select $ i=1 $ in the first operation, insert $ a_1 + 1 = 3 $ in $ S $ , and delete $ a_1 $ from $ a $ . After the first operation, $ a $ becomes $ a=[1] $ . In the second operation, we select $ i=1 $ again and insert $ a_1 + 1 = 2 $ in $ S $ . Thus $ S=\{2, 3\} $ , and $ b = [3, 2] $ .

Note that if you select $ i=2 $ in the first operation, and $ i=1 $ in the second operation, $ S=\{3\} $ as $ 3 $ will be inserted twice, resulting in $ b=[3] $ .

As $ [3,2] $ is lexicographically larger than $ [3] $ , we should select $ i=1 $ in the first operation.

In the second test case, in each operation, select the last element.

## 样例 #1

### 输入

```
3
2
2 1
5
1 100 1000 1000000 1000000000
3
6 4 8```

### 输出

```
3 2 
1000000005 1000004 1003 102 2 
11 7 6```

# 题解

## 作者：JiuZhE66666 (赞：5)

[原题链接](https://codeforces.com/problemset/problem/1930/C)

[更好的阅读体验](https://www.cnblogs.com/pure4knowledge/p/18252628)


# 题解
1.第 $i$ 个位置上的数，对 $S$ 的贡献最大不会超过 $a_i+i$，我们令其为 $c_i$。

2.我们不去细想如何操作才能得到最优解，而是去想第一大的 $b$ 是多少？第二大的 $b$ 是多少？

3.对 $c_i$ 降序排序得到 $b_i$，如果所有 $b_i$ 都不同，那么直接输出即可。

4.但如果存在 $k$ 个 $b_i$ 相同，那么我们先将这 $k$ 个数标为 $b_j,b_{j+1},b_{j+2}...b_{j+k-1}$，易得 $[1,j]$ 的 $b$ 不变，而从 $b_{j+1}$ 开始，每个数最大可以为前面一个数减一。

# code
```
#include<bits/stdc++.h>
using namespace std;
int a[300006];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            a[i]+=i;
        }

        sort(a+1,a+1+n,greater<int>());

        for(int i=2;i<=n;i++) a[i]=min(a[i],a[i-1]-1);
        for(int i=1;i<=n;i++) cout<<a[i]<<" \n"[i==n];
    }
    return 0;
}

```

---

## 作者：HomuraAkemi (赞：1)

困难题。

> $\textbf{Observation 1.}$ 每一个 $a_i$ 对答案的贡献为 $a_i+c_i$，其中 $1\le c_i\le i$。

进一步地，有重要结论：

> $\textbf{Lemma 1.}$ 任意一个符合 $1\le c_i\le i$ 的序列 $c$，都存在一种操作方式被构造出来。
> 
> $\textbf{Proof.}$ 考虑归纳。$n=1$ 时显然成立。
> 
> 设 $\le n-1$ 时成立（$n\ge 2$）。考虑 $c_n$，它可以取 $1\le c_n\le n$。
>
> 考虑到对 $a_n$ 的操作不会影响到前面的，而前面 $(n-1)$ 个元素的每一次操作都会影响到 $a_n$。也就是说，在对前面 $(n-1)$ 个元素操作的过程中，$c_n$ 会从 $n\to 1$，到想要的值的时候直接操作一下 $c_n$ 即可。
>
> $\square$

于是我们得到算法：从小到大遍历 $i$，然后找出最大的 $j$（$1\le j\le i$）满足 $a_i+j\not \in S$，插入 $j$。

这个维护非常困难，可以利用 $\texttt{std::set}$ 维护。

具体地说，维护两个 $\texttt{set}$，一个表示用过的元素，一个表示还没用的元素。

每次对于 $a_i$，若 $a_i+i$ 未被用过，则直接插入后一个 $\texttt{set}$；然后对于每一个 $a_i$，找到 $\le a_{i}+i$ 的最大的在后一个 $\texttt{set}$ 中的元素 $x$，将其加入答案，然后将 $x-1$ 插入（若未被用过的话）即可。

---

## 作者：M1saka16I72 (赞：0)

## 前言

很有意思的一道题。
做法参考了 CF 官方题解。

[更可爱的阅读体验](https://misaka16172.github.io/solution-CF1930C.html)


## 思路

考虑进行一次操作会对其他元素造成的影响。

删除 $a_i$ 会使其右边的所有元素下标减少 $1$，而我们的任务是让最后得到的集合 $S$ 字典序最大，所以我们希望每个数的下标都尽量不要减少。

但问题在于 $S$ 并不是一个可重集，故我们不能直接从右往左执行操作，因为这样给 $S$ 带来的元素虽然是最大的，但可能会出现重复的情况，例如样例里的 `2 1`，如果先删右边的 $1$ 再删 $2$ 就会带来两个重复的 $3$，去重后字典序小于答案 `3 2`。

于是我们可以考虑每个数的下标减小了几次，记作 $c_i\ (0\leq c_i<i)$，则任务就变成了对于每个 $a_i$ 找到最小的 $c_i$，使得对于任意 $j<i$，$a_i+i-c_i≠a_j+j-c_j$。发现无论求解 $c_i$ 的顺序如何，答案最优性都不会受到影响。

同时，由于 $c_1=0$，如果 $a_1$ 在 $a_2$ 之前删除则 $c_2=1$（反之 $c_2=0$），继续推导可得任意一个满足 $0\leq c_i<i$ 的序列 $c$ 都是可以被某种操作顺序构造出来的，于是答案的可行性也得到了保证。

现在的问题就变成了怎么找当前最小的 $c_i$，满足 $a_i+i-c_i$ 还没有在答案里出现过。

如果对于所有 $c_i\in [0,x)$，$a_i+i-c_i$ 都出现过，则存在 $j<i$ 使得 $a_i+i-(x-1)=a_j+j+c_j$ 且不存在 $k<i$ 使 $a_i+i-x=a_k+k-c_k$。第一个式子可以化简为 $a_i+i-x=a_j+j+c_j-1$。也就是说，当前的答案 $v_i$ 只有两种情况，如果是 $a_i+i$ 没有出现过则 $c_i=0$，$v_i$ 直接等于 $a_i+i$，否则 $v_i=\max\{v_j-1\}\ (j<i,a_i+i\leq v_j-1)$。

实现方面可以用两个 set 维护之前出现过的答案和待选的答案集合，如果 $a_i+i$ 出现过就在待选的集合里二分查找需要的答案。

于是这道题我们就做完了，代码比较好写。

## 代码
```cpp
void solve(){
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		a[i]+=i;
		}
	vector<ll> sol;
	set<ll> vis,now;
	for(int i=1;i<=n;i++){
		ll v;
		if(!vis.count(a[i])) v = a[i];
		else{
			auto it = now.upper_bound(a[i]);it--;
			v = *it;
		}
		sol.pb_(v);
		vis.insert(v);now.erase(v);
		if(!vis.count(v-1)) now.insert(v-1);
	}
	sort(sol.begin(),sol.end(),greater<ll>());
	for(ll i:sol) cout<<i<<" ";
	cout<<"\n";
}
```

---

