# Preparing for the Contest

## 题目描述

Monocarp 正在为一场大型比赛做准备。他计划解决 $n$ 道题目来确保自己已经准备充分。这些题目的难度等级分别为：第一道题的难度为 $1$，第二道题的难度为 $2$，以此类推，直到最后一题（第 $n$ 题），其难度为 $n$。

Monocarp 会选择一种顺序来解决这 $n$ 道题。每当他解决的题目的难度比他上一次解决的题目更高时，他会感到兴奋，因为他觉得自己在进步。当他解决他选择的顺序中的第一道题时，他不会感到兴奋。

例如，如果 Monocarp 按顺序 $[3, \underline{5}, 4, 1, \underline{6}, 2]$ 解决题目，他会兴奋两次（下划线标记的题目）。

Monocarp 希望在练习过程中恰好兴奋 $k$ 次。请你帮助他选择解决题目的顺序！

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
6 2
5 4
5 0```

### 输出

```
3 5 4 1 6 2
1 2 3 4 5
5 4 3 2 1```

# 题解

## 作者：_fallen_leaves_ (赞：1)

# 题目:[CF1914B Preparing for the Contest](https://www.luogu.com.cn/problem/CF1914B)
## 思路
首先我们先把后 $k+1$ 个数给从小到大输出，这就保证了有 $k$ 个后面的数大于前面的数，剩下的再从 $1$ 到 $n-k-1$ 个数从大到小输出，这就保证后面不会出现后面的数大于前面的数这种情况了。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;//有t组数据 
	while(t--)
	{
		int n,k;
		cin>>n>>k;//输入 
		for(int i=n-k;i<=n;i++) cout<<i<<" ";//从n-k开始到n输出 
		for(int i=n-k-1;i>=1;i--) cout<<i<<" ";//从n-k-1开始到1输出 
		cout<<endl;//多组数据必须要换行 
	}
	return 0;
}
```

---

## 作者：Kle1N (赞：1)

## 题目翻译
这道题的翻译其实是有问题的，所以我又翻译了一遍。

- 给定正整数 $n$ 和 $k$，求一个 $n$ 的**排列** $a$ 使得恰好有 $k$ 个不同的 $a_i$ 满足 $a_i<a_{i+1}$。
## 思路
首先，根据题意我们可以发现，对于一个长度为 $x$ 的序列，若其单调递减，则没有任何一个 $a_i$ 满足 $a_i<a_{i+1}$；若其单调递增，则会有 $x-1$ 个 $a_i$ 满足。

所以我们只要使答案有 $k+1$ 个相邻的数单调递增，剩余部分单调递减即可满足题意。

因为答案序列是一个 $n$ 的排列，那最简单的方案就是前 $k+1$ 个数为 $n-k$ 到 $n$，后面为 $n-k-1$ 到 $1$了。

具体见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,k;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=n-k;i<=n;i++){
			cout<<i<<" ";
		}
		for(int i=n-k-1;i>=1;i--){
			cout<<i<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：BinSky (赞：1)


[原题传送门](https://www.luogu.com.cn/problem/CF1914B)

### 题目大意：
输入 $t$ 组数据，每行包括序列长度 $n$ 与后一个数比前一个数大的次数 $k$，要我们构造一个后一个数比前一个数大的次数为 $k$ 的序列并输出。

### 解题思路：
我们可以试着举一个较简单的例子，如当 $n=6$，$k=2$ 时，可以有 `4 5 6 3 2 1` 。这个序列满足上面的条件，还可以进行归纳：

+ 令此序列为 $a$
+ 从左往右数 $1\sim k+1$ 个数，满足 $a_{i}<a_{i+1}$
+ 从左往右数 $k+2\sim n$ 个数，满足 $a_{i}>a_{i+1}$
+ 全序列中，$a_{1}= a_{k+2}+1$

但是，$k=0$ 时此归纳就不满足了，所以在写的时候要特判。

顺着归纳的式子，便可以轻松码出来啦！

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n,k,t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n>>k;
		if(k==n-1)
		{
			for(int j=1;j<=n;j++)
				cout<<j<<" ";
			cout<<endl;
		}
		else if(k==0)//特判
		{
			for(int j=n;j>=1;j--)
				cout<<j<<" ";
			cout<<endl;
		}
		else
		{
			for(int j=n-k;j<=n;j++)//递增
			{
				cout<<j<<" ";
			}
			for(int j=n-k-1;j>=1;j--)//递减
			{
				cout<<j<<" ";
			}
			cout<<endl;
		}
	}
	
	return 0;//好习惯
}
```


---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷原题面](//www.luogu.com.cn/problem/cf1914b)

[CodeForces 原题面](//codeforces.com/problemset/problem/1914/B)

给定 $n,k$，构造一个长度为 $n$ 的排列 $a$，使得排列中满足 $2\le i\le n,a_i > a_{i-1}$ 的 $i$ 的个数恰好为 $k$。


# 分析

转换一下题意，我们只需要构造出一个长度为 $k$ 的升序序列，和一个长度为 $n-k$ 的降序序列即可。

那么构造数列 ${1,2,\dots k,n,n-1,\dots,k+1}$ 即可。

时间复杂度 $O(n)$。

空间复杂度：$O(1)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int n, k;
void Solve(){
  cin >> n >> k;
  for (int i = 1; i <= k; i++){
    cout << i << ' ';
  }
  for (int i = n; i > k; i--){
    cout << i << ' ';
  }
  cout << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：indream (赞：0)

## CF1914B Preparing for the Contest 题解
[RMJ](https://www.luogu.com.cn/problem/CF1914B) | [CF](http://codeforces.com/problemset/problem/1914/B) | [AC](https://www.luogu.com.cn/record/140547052)

### 思路
构造水题。

首先，另前 $k+1$ 个数字递增，应从 $n-k$ 递增至 $n$，便可满足增加了 $k$ 次之条件；剩下 $n-k-1$ 个数字，可从 $n-k-1$ 递减至 $1$，这样满足了后面的数字均没有增加，且凑齐了 $1$ 至 $n$ 的自然数。

时间复杂度 $O(Tn)$，可以通过此题。

本题方法不唯一。
### AC
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main(){
    scanf("%d\n",&t);
    while(t--){
        scanf("%d %d\n",&n,&k);
        for(int i=n-k;i<=n;++i)
            printf("%d ",i);
        for(int i=n-k-1;i>0;--i)
            printf("%d ",i);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：InversionShadow (赞：0)

构造出一个数组 $a$，满足 $\sum\limits_{i=2}^{n}[a_i>a_{i-1}]=k$，$T$ 组数据。

------------------

我们钦定第一位是 $1$，$a_i>a_{i-1}$ 叫做顺序对。那么现在要构造 $k$ 组“顺序对”，即 $a$ 中正好有 $k$ 个 $a_i>a_{i-1}$，所以顺序构造出 $n-k+1\sim n$，这里面正好有 $k$ 组“顺序对”，逆序构造出 $n-k\sim2$，这里面没有“顺序对”，那么总“顺序对”就是 $k$ 组，满足题意。

注意特判 $k=0$ 的情况。

```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, k;

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		if (k == 0) {
			for (int i = n; i >= 1; i--) {
				cout << i << ' ';
			}
			cout << '\n';
			continue;
		}
		cout << 1 << ' ';
		for (int i = n - k + 1; i <= n; i++) {
			cout << i << ' ';
		}
		for (int i = n - k; i >= 2; i--) {
			cout << i << ' ';
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：minVan (赞：0)

**解题思路**

不难想到单峰函数，前一段为 $n-k\sim n$，后一段为 $n-k-1\sim1$。此时前一段除第一个都满足条件，后一段都不满足条件。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    int n, k;
    cin >> n >> k;
    for(int i = n - k; i <= n; i++) {
      cout << i << ' ';
    }
    for(int i = n - k - 1; i >= 1; i--) {
      cout << i << ' ';
    }
    cout << '\n';
  }
  return 0;
}

```

---

## 作者：myyyIisq2R (赞：0)

## [CF1914B Preparing for the Contest](https://www.luogu.com.cn/problem/CF1914B)
## 题意
给出一个长度为 $n$ 的序列，使序列中后一个数比前一个数大的次数为 $k$。

## 思路

考虑一种构造，使序列分成单调递增和单调递减的两部分，那么单调递增的长度需要为 $k$。

举个例子，对于 $6$ $2$ 的情况，可以构造如下序列：$\color{red}12\color{blue}6543$。

发现满足题意时单调递增部分长度正好为 $k$，那么枚举构造即可。

## 细节
```cpp
#include  <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e5+5;
int n,k;
signed main()
{	
	cin.tie(0); cout.tie(0); 
	int T;
	cin>>T;	
	while(T--)
	{

		cin>>n>>k;
		if(!k) 
		{
			for(int i{n};i>=1;i--) cout<<i<<" "; cout<<endl;
			continue;
		}
		for(int i{1};i<=k;i++)cout<<i<<" ";
		for(int i{n};i>k;i--) cout<<i<<" ";
		cout<<endl;
	}
 } 
```


---

