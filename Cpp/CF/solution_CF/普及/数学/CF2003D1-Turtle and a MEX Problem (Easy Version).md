# Turtle and a MEX Problem (Easy Version)

## 题目描述

The two versions are different problems. In this version of the problem, you can choose the same integer twice or more. You can make hacks only if both versions are solved.

One day, Turtle was playing with $ n $ sequences. Let the length of the $ i $ -th sequence be $ l_i $ . Then the $ i $ -th sequence was $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i} $ .

Piggy gave Turtle a problem to solve when Turtle was playing. The statement of the problem was:

- There was a non-negative integer $ x $ at first. Turtle would perform an arbitrary number (possibly zero) of operations on the integer.
- In each operation, Turtle could choose an integer $ i $ such that $ 1 \le i \le n $ , and set $ x $ to $ \text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}) $ .
- Turtle was asked to find the answer, which was the maximum value of $ x $ after performing an arbitrary number of operations.

Turtle solved the above problem without difficulty. He defined $ f(k) $ as the answer to the above problem when the initial value of $ x $ was $ k $ .

Then Piggy gave Turtle a non-negative integer $ m $ and asked Turtle to find the value of $ \sum\limits_{i = 0}^m f(i) $ (i.e., the value of $ f(0) + f(1) + \ldots + f(m) $ ). Unfortunately, he couldn't solve this problem. Please help him!

 $ ^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k) $ is defined as the smallest non-negative integer $ x $ which does not occur in the sequence $ c $ . For example, $ \text{mex}(2, 2, 0, 3) $ is $ 1 $ , $ \text{mex}(1, 2) $ is $ 0 $ .

## 说明/提示

In the first test case, when $ x $ is initially $ 2 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 3 $ , so $ f(2) = 3 $ .

It can be seen that $ f(0) = 3 $ , $ f(1) = 3 $ , $ f(2) = 3 $ , $ f(3) = 3 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16 $ .

In the second test case, when $ x $ is initially $ 1 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(1, 1, 3, 0, 3, 3) = 2 $ , and choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(2, 1, 3, 0, 3, 3) = 4 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 4 $ , so $ f(1) = 4 $ .

It can be seen that $ f(0) = 4 $ , $ f(1) = 4 $ , $ f(2) = 4 $ , $ f(3) = 4 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 4 + 4 + 4 + 4 = 20 $ .

In the fourth test case, it can be seen that $ f(0) = 3 $ and $ f(1) = 3 $ . So $ f(0) + f(1) = 3 + 3 = 6 $ .

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556```

### 输出

```
16
20
1281
6
6556785365
1842836177961```

# 题解

## 作者：Exp10re (赞：1)

EZ.ver 和 HD.ver 都是巧妙题啊。

### 解题思路

对于 EZ.ver，每一个数列可以被选取多次。

记一个数列的最小未出现非负整数为 $u_i$，次小未出现非负整数为 $v_i$，则初始值为 $x$ 时答案一定不小于 $\max\limits_{1\leq i \leq n} v_i$。

证明：考虑如何得到 $\max\limits_{1\leq i \leq n} v_i$：记 $v_p=\max\limits_{1\leq i \leq n} v_i$，则取 $x=\operatorname{mex}(x,a_p)$ 一定可以得到 $u_p$ 或 $v_p$，若是 $u_p$，再进行一次操作就可以得到 $v_p$。

故 $\sum\limits_{i=0}^n f(i)=\sum\limits_{i=0}^n \max(i,v_p)$，对小于等于 $v_p$ 的部分求和，大于 $v_p$ 的部分等差数列求和即可。

时间复杂度 $O(\sum l_i)$。

有趣的是，取 $x=\operatorname{mex}(x,a_i)$ 可以得到 $u_i$ 或 $v_i$ 在 HD.ver 是一个很有用的性质，感兴趣可以去看一下 [CF2003D2](https://www.luogu.com.cn/problem/CF2003D2)。

---

## 作者：Defy_HeavenS (赞：1)

# 题意

给定 $n$ 个序列，其第 $i$ 个序列的长度为 $l_i$，第 $i$ 个序列为 $a_{i,1},a_{i,2},\dots,a_{i,l_i}$。

一开始给定一个非负整数 $x$，要对这个整数进行任意次的运算（可能为零次）。

- 每次运算选择一个整数 $i$，使得 $1\le i\le n$，并将 $x$ 设为 $\mathrm{mex}(x,a_{i,1},a_{i,2},\dots,a_{i,l_i})$（$\mathrm{mex}$ 为不出现的最小**非负**整数，如 $\mathrm{mex}(0,2,1,5,5,21)=3$）。
  进行任意次后，求 $x$ 的最大值，并把其定义为 $f(x)$。

然后给定一个非负整数 $m$，要求 $\sum_{i=0}^{m} f(i)$。Easy Version 保证可以两次或更多次选择同一个 $i$。

# 思路

Easy Version 可以两次或更多次选择同一个 $i$，这就启示我们如果一直选一个 $i$ 会发生什么？如果一直选一个 $i$ 那么对于任意的 $x$ 得到的 $f(x)$ 都相同，而且都是不出现的第二小**非负**整数。

首先固定一个 $i$，并且设 $val$ 为 $\mathrm{mex}(a_{i,1},a_{i,2},\dots,a_{i,l_i})$，设定两种情况：情况一 $x=val$，情况二 $x\ne val$。

1. 第一次运算，情况一则把 $x$ 设为 $\mathrm{mex}(x,a_{i,1},a_{i,2},\dots,a_{i,l_i})$。情况二则把 $x$ 设为 $\mathrm{mex}(a_{i,1},a_{i,2},\dots,a_{i,l_i})$。
2. 第二次运算，情况一就变成了情况二（因为 $x$ 变了），所以答案不如以前优。情况二就变成了情况一，把 $x$ 设为 $\mathrm{mex}(x,a_{i,1},a_{i,2},\dots,a_{i,l_i})$，这时的 $x$ 也是最大的（因为若在做一次运算，就会像情况二的第二次操作一样，不如以前优了）。
   那么无论 $x$ 是多少，选定一个 $i$ 一直做，$x$ 肯定是 $\mathrm{mex}(\mathrm{mex}(a_{i,1},a_{i,2},\dots,a_{i,l_i}),a_{i,1},a_{i,2},\dots,a_{i,l_i})$，也就是不出现的第二小**非负**整数。

那么我们发现其实只有一个序列是有效的，那么我们找出那个 $\mathrm{mex}(\mathrm{mex}(a_{i,1},a_{i,2},\dots,a_{i,l_i}),a_{i,1},a_{i,2},\dots,a_{i,l_i})$ 最大的序列，把他作为答案即可。

怎么处理 $\sum_{i=0}^{m} f(i)$ 这个呢？我们先设 $ma$ 为 $\max_{i=1}^{n} \mathrm{mex}(\mathrm{mex}(a_{i,1},a_{i,2},\dots,a_{i,l_i}),a_{i,1},a_{i,2},\dots,a_{i,l_i})$，那么对于 $\sum_{i=0}^{m} f(i)$ 所有 $i\le ma$ 答案就是 $ma$，所有 $i>ma$ 答案就是 $i$（做 $0$ 次运算）。

# 代码

怎么求 $mex$？有两种常用方法：`set` 和权值线段树。

这里用 `set` 求。注意到一个序列 $\mathrm{mex}$ 不会超过 $n$，则若有大于 $n$ 的数可赋值为 $n+1$。先把 $0$ 至 $n+1$ 所有数加进 `set`，来看删除和加入两种操作：

- 加入 $x$ 操作：在 `set` 中删除 $x$，前提是 $x$ 这个数出现第一次。
- 删除 $x$ 操作：在 `set` 中加入 $x$，前提是 $x$ 这个数是剩下的唯一一个 $x$。
- 查询操作：只需要查询 `set` 里的第一个数。

赛时代码。

```cpp
#include<bits/stdc++.h>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define pb push_back

using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;

const LL N=2e5+5;
LL n,m,ans;
vector<LL>a[N];
void solve(){
	cin>>n>>m;
	for(LL i=1,len;i<=n;i++){
		cin>>len;
		for(LL j=1,val;j<=len;j++){
			cin>>val;
			a[i].pb(val);
		}
	}
	ans=-1;
	for(LL i=1;i<=n;i++){
		int n=a[i].size();
		set<LL>s;s.clear();    //set求mex
		vector<int>cnt(n+5,0);
		for(int i=0;i<=n+2;i++) s.insert(i);
		for(auto val:a[i]){
			if(val>n+2) val=n+2;
			if(!cnt[val]){
				s.erase(s.find(val));
			}
			cnt[val]++;
		}
		int val=*s.begin();
		if(!cnt[val]){
			s.erase(s.find(val));    //加入mex，求第二个mex
		}
		cnt[val]++;
		ans=max(ans,*s.begin());    //更新答案
	}
	LL len=min(ans+1,m+1);    //i<=ma的数量
	LL sec=max((m+ans+1)*(m-ans)/2,0ll);    //i>ma
	cout<<ans*len+sec<<"\n";
	for(int i=1;i<=n;i++) a[i].clear();
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	LL t=1;cin>>t;
	while(t--) solve();
	return 0;
}
/*

*/
```

---

## 作者：_O_v_O_ (赞：1)

好牛。

结论：$f(x)$ 为 $\max\{x,\max_{i=1}^n\operatorname{popcount}\{\operatorname{popcount}\{p_{i,1},p_{i,2},\cdots p_{i,l_i}\},p_{i,1},p_{i,2},\cdots p_{i,l_i}\}\}$。

为什么？因为为了想要达到若干次操作后的最大值，我们只用在 $\operatorname{popcount}\{\operatorname{popcount}\{p_{i,1},p_{i,2},\cdots p_{i,l_i}\},p_{i,1},p_{i,2},\cdots p_{i,l_i}\}$ 最大的 $i$ 操作两遍就行了。

那么我们拆一下原来的柿子（设 $k=\max_{i=1}^n\operatorname{popcount}\{\operatorname{popcount}\{p_{i,1},p_{i,2},\cdots p_{i,l_i}\},p_{i,1},p_{i,2},\cdots p_{i,l_i}\}$）：$\sum_{i=0}^{k-1} k+\sum_{i=k}^m i=k^2+(m+k)\times (m-k-1)$。

我们发现上面这玩意儿能 $O(1)$ 求出，所以我们就做完了。

时间复杂度 $O(\sum_{i=1}^n l_i)$。

---

