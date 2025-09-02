# Money Transfers

## 题目描述

There are $ n $ banks in the city where Vasya lives, they are located in a circle, such that any two banks are neighbouring if their indices differ by no more than $ 1 $ . Also, bank $ 1 $ and bank $ n $ are neighbours if $ n&gt;1 $ . No bank is a neighbour of itself.

Vasya has an account in each bank. Its balance may be negative, meaning Vasya owes some money to this bank.

There is only one type of operations available: transfer some amount of money from any bank to account in any neighbouring bank. There are no restrictions on the size of the sum being transferred or balance requirements to perform this operation.

Vasya doesn't like to deal with large numbers, so he asks you to determine the minimum number of operations required to change the balance of each bank account to zero. It's guaranteed, that this is possible to achieve, that is, the total balance of Vasya in all banks is equal to zero.

## 说明/提示

In the first sample, Vasya may transfer $ 5 $ from the first bank to the third.

In the second sample, Vasya may first transfer $ 1 $ from the third bank to the second, and then $ 1 $ from the second to the first.

In the third sample, the following sequence provides the optimal answer:

1. transfer $ 1 $ from the first bank to the second bank;
2. transfer $ 3 $ from the second bank to the third;
3. transfer $ 6 $ from the third bank to the fourth.

## 样例 #1

### 输入

```
3
5 0 -5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
-1 0 1 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
1 2 3 -6
```

### 输出

```
3
```

# 题解

## 作者：DennyQi (赞：3)

显然一段长度为$l$的和为0的序列最多转移$l-1$次，因为相互之间你给我我给你可以只做一次。因此我们的任务是求出怎样划分使得和为0的序列尽量多。

利用前缀和的性质，和为0意味着前缀和的值相等。因此对于每一个前缀和的值用`map`求出与它相等的值有多少个，巧妙地解决了“环”的问题。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
#define int long long
using namespace std;
const int N = 100010;
const int P = 998244353;
const int INF = 0x3f3f3f3f;
inline int mul(const int& a, const int& b){ return 1ll*a*b%P; }
inline int add(const int& a, const int& b){ return (a+b>=P)?a+b-P:a+b; }
inline int sub(const int& a, const int& b){ return (a-b<0)?a-b+P:a-b; }
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,x,s,ans;
map <int,int> S;
signed main(){
	// freopen("file.in","r",stdin);
	n = read();
	for(int i = 1; i <= n; ++i){
		x = read();
		s += x;
		++S[s];
		ans = max(ans,S[s]);
	}
	printf("%lld\n",n-ans);
	return 0;
}
```

---

## 作者：a_girl (赞：1)

[CF675C Money Transfers](https://www.luogu.com.cn/problem/CF675C)

## 题意
有 $n$ 家银行，第 $i$ 家银行有 $a_i$ 元钱，相邻两家银行可以转账，第 $1$ 家和第 $?$ 家也可以转账，问需要多少次转账可以使得所有银行的余额都为 $0$？

## 思路
我们拿一个前缀和，求出这些银行的前缀和，注意 $a_i$ 的值会非常的大，所以我们要拿 $map$ 来存储，最后取 $map$ 中的数字的最大值，**注意：这道题因为数据过大，所以要开 long long。**

## 代码

```cpp
#include<bits/stdc++.h>万能头 
using namespace std;
map<long long,long long> mp； //map 
long long n,x[100005],sum=INT_MIN,ans=0;
int main()
{
	cin>>n;
	for(long long i=1;i<=n;i++)
	{
		cin>>x[i];//输入 
        ans+=x[i]; 
		mp[ans]++;//前缀和 
	}
	ans=0;
	for(long long i=1;i<=n;i++)
	{
	    ans+=x[i];
	    sum=max(sum,mp[ans]);//求最大值 
	}
	cout<<n-sum； 
	return 0;
}
```

---

## 作者：_fallen_leaves_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF675C)

## 分析&&思路
我们用出每一个前缀和的值，再用每一个前缀和的值，再从相等的前缀和中取出最大值，算出来的结果就是本题的答案。
### 最后再说一句十年 oi 一场空，不开 long long 见祖宗。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
map<long long,long long> mp;//一句十年oi一场空，不开longlong见祖宗。话说回来为什么我写的每一篇题解都要开longlong？ 
long long n,x[100005],sum=INT_MIN,ans=0;
int main()
{
	cin>>n;
	for(long long i=1;i<=n;i++)
	{
		cin>>x[i];//用数组保存每一个数 
        ans+=x[i]; 
		mp[ans]++;//前缀和保存数字 
	}//先输入并用前缀和保存数字 
	ans=0;
	for(long long i=1;i<=n;i++)
	{
	    ans+=x[i];
	    sum=max(sum,mp[ans]);//求出每一个数相等的最大值 
	}//再来一个循环来找出答案 
	cout<<n-sum;//完美散花 
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
很经典的一个题，显然的前缀和操作题。
## 分析。
这个很像均分纸牌那道题，可以采用离散化，加之贪心的思路，但是写起来比较麻烦。显然 $1$ 到 $n$ 家银行构成了一个环，那么我们既然要使每一家的银行的=账户都是 $0$ 则不妨把这个环断裂成 $k$ 个区间，在每个区间内，每一家的银行的钱数相加都等于 $0$ 此时 $k$ 个区间中每个区间的值都是 $0$ 则满足题意。只要我们确定好 $k$ 则可以在每一个区间内进行转账操作即可。我们假设第 $i$ 个区间的长度为 $l_i$，那么需要移动的次数就是 $l_i-1$ 次。那么 $k$ 个区间所有移动次数的加和就是：
$$\sum_{i-1}^k l_i-k=n-k$$
此时我们成功转化了过来，直接求出 $k$ 就能得知最小次数了。那么求 $k$ 我们可以这么考虑：我们显然要让 $k$ 尽可能大，显然一个比较大的数可以分给几个比较小的数。而且最后的那个银行对于的前缀和必定为 $0$。我们给予样例：
```
1 2 3 0 1 -1 -2 3 -1 -3 -3
```
对应的下标：
```
1 2 3 4 5 6 7 8 9 10 11
```
那么对应的前缀和就是：
```
1 3 6 6 7 6 4 7 6 3 0
```
我们观察到此时显然要让相邻的两个互补的进行转账，那么之中情况为 $1$ 种，而对应到前缀和中就是 ```6 7``` 这个区间，其它的只能靠近者传递，此时就是先让 $7$ 和 $9$ 号去补 $8$ 的，此时前缀和就是 ```4 7 6```。再让 $10$ 到 $11$ 然后在将这些钱一步步转移到从 $1$ 到 $3$ 不全，对应的前缀和就是 ```3 0 1 3 6```。一共操作 $7$ 次，观察到前缀和中 $6$ 出现的次数最多并且为 $4$ 次，同时我们发现每一个前缀和的区间内，必定存在一个 $6$。事实上，我们可以证明前缀和中出现次数最多的那个数字出现的次数就是 $k$ 因为只有这样才能在两个相邻的前缀和中隔的数尽可能少，划分的区间尽可能多。同时因为在这个数字又一次出现说明在这个区间内可以做到转移为 $0$ 所以得证。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
long long n,x;
map<long long,long long> t;
long long sum,k=1;
int main(){
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>x;
        sum+=x;
        t[sum]++;
        k=max(k,t[sum]);
    }
    cout<<n-k<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：ACtheQ (赞：0)

### 题目梗概

有 $n$ 家银行，第 $i$ 家银行有 $a[i]$ 元，相邻两家银行可以相互转账，第 $1$ 家和第 $n$ 家也可以，问最少需要多少次转账可以使得所有银行的余额都变成 $0$？

### 思路

由于我们的目的是把余额都变成 $0$。

首先，我们可以利用前缀和的性质。我们就可以求出对于每一个前缀和的值，再用求出与它相等的值，最后取最大值。

由于前缀和的性质，若是前缀和相等，那么代表两数之和为 $0$。

因此，对于所有的答案等于 $n-(\sum_{i=1}^n mp[sum[i]])$。

其中 $mp$ 为桶数组，而 $sum[i]$ 为 $\sum_{j=1}^i a[i]$。

AC 代码如下：
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,int> mp;
signed main()
{
	int n;
	cin>>n;
	int ans=-1e9;
        int sum=0;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
                sum+=x;
		mp[sum]++;
		ans=max(ans,mp[sum]);
	}
	cout<<n-ans;
	return 0;
}
```

---

