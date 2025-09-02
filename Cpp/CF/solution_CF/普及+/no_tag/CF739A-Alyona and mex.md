# Alyona and mex

## 题目描述

Alyona's mother wants to present an array of $ n $ non-negative integers to Alyona. The array should be special.

Alyona is a capricious girl so after she gets the array, she inspects $ m $ of its subarrays. Subarray is a set of some subsequent elements of the array. The $ i $ -th subarray is described with two integers $ l_{i} $ and $ r_{i} $ , and its elements are $ a[l_{i}],a[l_{i}+1],...,a[r_{i}] $ .

Alyona is going to find mex for each of the chosen subarrays. Among these $ m $ mexes the girl is going to find the smallest. She wants this minimum mex to be as large as possible.

You are to find an array $ a $ of $ n $ elements so that the minimum mex among those chosen by Alyona subarrays is as large as possible.

The mex of a set $ S $ is a minimum possible non-negative integer that is not in $ S $ .

## 说明/提示

The first example: the mex of the subarray $ (1,3) $ is equal to $ 3 $ , the mex of the subarray $ (2,5) $ is equal to $ 3 $ , the mex of the subarray $ (4,5) $ is equal to $ 2 $ as well, thus the minumal mex among the subarrays chosen by Alyona is equal to $ 2 $ .

## 样例 #1

### 输入

```
5 3
1 3
2 5
4 5
```

### 输出

```
2
1 0 2 1 0
```

## 样例 #2

### 输入

```
4 2
1 4
2 4
```

### 输出

```
3
5 2 0 1```

# 题解

## 作者：Alex_Wei (赞：26)

挺有意思的一道题目

#### 首先你应该知道：

$$ans=\min_{i=1}^{m}(r_i-l_i+1)$$

一个区间 $[l_i,r_i]$ 最多只有 $r_i-l_i+1$ 个数

要使该区间的 $mex$ 值大，区间  $[l_i,r_i]$ 应当包含 $[0,r_i-l_i]$ 

此时 $mex$ 值为 $r_i-l_i+1$

那么该如何构造这个序列？

轮流输出 $0$ 到 $ans-1$ 即可，**这样可以保证每个 $[l_i,r_i]$ 的区间都包含 $[0,r_i-l_i]$**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r,x=1e9;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>l>>r,x=min(x,r-l+1);
	cout<<x<<endl;
	for(int i=1;i<=n;i++)cout<<i%x<<" ";
}
```

求赞 $qwq$

---

## 作者：风中の菜鸡 (赞：2)

题意简化

给你 $m$ 个区间，让你构造出一个长度为 $n$ 的序列，要你分别求出这 $m$ 个区间中未出现的最小自然数，再输出所有最小自然数中最大的那个和构造出的数列，并使它尽可能大。 $($ 区间的左右端点是指 $n$ 数组的下标 $)$  

思路

构造题。

易发现 $mex$ 的值与区间长度有关，所以 $mex$ 最小值的最大值就为所有区间长度中的最小值。

想出上述思路的关键在于未出现过的最小自然数。若不把 $0,1,2,3$ 这种小的数填进去的话就会导致 $mex$ 取到这些较小数。而一个区间内也最多只能填区间长度那么多个，所以 $mex$ 最小值的最大值才是所有区间长度中的最小值。

对于构造序列，只需把  $0$ 到 $mex$ $-$ $1$  均匀的输出 $n$ 个即可。 $($ 输出更大的不仅对答案无帮助，反而会使答案变小 $)$ 

代码

虽然思路较难，但代码十分容易实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mex=1e9;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		mex=min(mex,b-a+1);//求mex值
	}
	cout<<mex<<endl;
	for(int i=1;i<=n;i++){
		cout<<i%mex<<' ';//轮流输出
	}
	return 0;
} 
```



---

## 作者：hh弟中弟 (赞：1)

简单构造，首先我们知道一个区间 $[l,r]$ 内的最大答案为为这个区间的长度 $len$，因为其中可以包括 $[0,r-l+1]$ 这些数。所以 $ans=\min{len_i}$。

考虑如何满足这个条件，设最小长度为 $len_{min}$，我们可以轮流输出 $[0,len_{min}]$，因为 $len_{min}$ 是最小长度，所以可以保证每个区间内都存在 $[0,len_{min}]$ 这些数。
```cpp
#include<bits/stdc++.h>
#define endl '\n'
inline int read(){
    char ch=getchar();int x=0,f=1;
    for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
int main(){
    //freopen("in.in","r",stdin),freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0),std::cout.tie(0);
    int n=read(),m=read(),ans=1e9;
    for(int i=1;i<=m;++i){
        int a=read(),b=read();
        ans=std::min(ans,b-a+1);
    }
    int p=0;
    std::cout<<ans<<'\n';
    for(int i=1;i<=n;++i){
        std::cout<<(p%=ans)<<' ';p++;
    }
}
```
赛时降智，想复杂了，耻辱。

---

## 作者：Vsinger_洛天依 (赞：1)

~~之前模拟赛T1。~~

# 题目大意

你有 $m$ 个区间，要求构造一个长度为 $n$ 的序列使得这 $m$ 个区间中 $\text{mex}$ 最小的最大（$\text{mex}$ 定义为一个区间内没有出现过的最小自然数）。

# 思路

- 考场解法
    - 先强行去对所有询问进行离线，按照区间长度去排序，判断区间内那些数已被填，然后从小到大去在没有被填的位置填没有被填过的数。
    - 不确定正不正确。
- 正解
    - 思路上不难，首先对于所有的区间，先考虑求 $\text{mex}$，发现可以比较简单的解决。  
    - 容易有 $\text{mex}=\min(\text{mex},l-r+1)$。
    - 那怎么构造序列呢？
    - 只要考虑能对 $\text{mex}$ 做贡献就行，其他位置无论是填 $0$ 还是 $\text{INF}$ 并没有特别大的区别。   
    - 那么我们可以直接循环输出 $\{0\sim \text{mex}-1\}$，这样可以保证对于无论怎么取 $l$ 和 $r$ 都能拿到上面求出来的 $\text{mex}$。
    
# 核心代码
        
```cpp
int ans=INF,n=read();
for(int i=read();i;i--)
    ans=min(ans,abs(read()-read())+1);
write(ans);puts("");
for(int i=1;i<=n;i++)
    write(i%ans),putchar(' ');
```


---

## 作者：wanghaoran00 (赞：1)

### 翻译
~~题面里有。~~

### 思路
易知，$mex$ 的最小值与数列的长度有关，每个区间有 $r-l+1$ 个数，而在寻找最小自然数时，需要寻找每个序列长度的最小值即可，即 $mex= \min(r_i-l_i+1,mex)$，构造序列时循环输出 $0$ 到 $mex-1$。

AC code
```
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r,x;
signed main(){
	x=1000000000;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&l,&r);
		x=min(x,r-l+1);
	}
	cout<<x<<endl;
	for(int i=1;i<=n;i++){
        printf("%d ",i%x);
	}
	return 0;
}

```

---

## 作者：ZLCT (赞：0)

# CF739A Alyona and mex
## 题意
给定 $m$ 个区间，求构造一个长度为 $n$ 的序列，满足这 $m$ 个区间 $\operatorname{mex}$ 的最小值最大。
## 喜闻乐见的构造题
### 关于 $\operatorname{mex}$
这个题首先要理解 $\operatorname{mex}$ 的定义以及一些性质。
#### 定义
首先 $\operatorname{mex}$ 表示序列内没有出现过的最小非负整数。
举个例子：$[0,1,4,1,3,1]$ 这个序列的 $\operatorname{mex}$ 就是 $2$。
#### 性质
通过定义和上面的例子我们可以发现：
- 一个序列的 $\operatorname{mex}$ 只与比 $\operatorname{mex}$ 小的数有关。
- 一个数字无论出现多少遍都只相当于 $1$ 个。
- 长度为 $n$ 的序列 $\operatorname{mex}$ 最大为 $n$。

简单证明一下最后一个性质。我们考虑假设 $\operatorname{mex}>n$，则根据定义至少有 $[0,n]$ 这 $n+1$ 个数出现过，这与条件矛盾，于是性质成立。
### 回到本题
根据最后一条性质，我们可以知道答案最大就是 $maxans=\min_1^m(r_i-l_i+1)$。\
我们希望构造出这样的序列，又秉持着不浪费的原则，于是我们只可能用 $[0,maxans-1]$ 的数字。\
然后我们考虑到在 $r_i-l_i+1=maxans$ 的区间必须出现 $[0,maxans-1]$ 的排列，而对于 $r_i-l_i+1>maxans$ 的区间，一定会出现浪费的情况，于是我们可以想到把每个 $r-l+1=maxans$ 的区间都构成合法区间，这样答案一定是 $maxans$。
### 激动人心的构造过程
首先前 $maxans$ 个数先进行任意一个 $[0,maxans-1]$ 的排列，那么考虑第 $maxans+1$ 位就一定要填第一位，这样才能保证序列仍然是一个排列。接下来就和滑动窗口一样每次把首元素放到队尾。
### 一些小问题
1. Q：为什么**把每个 $r-l+1=maxans$ 的区间都构成合法区间，这样答案一定是 $maxans$**？\
A：因为我们这个约束是严格强于原题约束的，所以它是原题的一个充分条件。
2. Q：为什么我们的构造方法一定是合法的呢？\
A：因为我们的构造方法使得在窗口滑动的时候区间总是一个 $[0,maxan-1]$ 的排列。
## code
这题代码你当然可以先随机出一个排列，但是~~不想被老师同学以及读者口诛笔伐~~为了优雅，我还是选择简单的正序排列。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=1e9+7;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int l,r;cin>>l>>r;
        ans=min(ans,r-l+1);
    }
    cout<<ans<<'\n';
    const int mod=ans;
    for(int i=0;i<n;++i){
        cout<<i%mod<<' ';
    }
    return 0;
}
```

---

## 作者：自由软件Free (赞：0)

# [CF739A Alyona and mex](https://www.luogu.com.cn/problem/CF739A)

## 题意

给定 $m$ 个区间，构造出一个长度为 $n$ 的序列，使得这 $m$ 个区间的最小 $mex$ 最大。 $mex$ 定义为最小的没有出现过的自然数。

## 题解

先观察样例，发现两次输出的 $mex$ 均等于**最短的区间长度**，显然这不是巧合。

首先很容易得出 $mex(S) \le \lvert S \rvert$，且当 $S$ 覆盖 $0$ 到 $\lvert S \rvert - 1$ 时取等，所以最终答案不会超过最短的区间的长度，然后思考如何构造出答案等于最短区间长度的情况。

求出最短的区间长度为 $x$，只要让这个区间完全覆盖 $0, 1, 2, ..., x - 1$ ，就可以取到 $mex$ 的最大值，所以则只要在数组中循环填入 $0, 1, 2, ..., x - 1$，就能保证每一个长度大于等于 $x$ 的区间 $mex$ 一定都等于 $x$，因为每一个长度大于等于 $x$ 的区间都至少覆盖一次 $0, 1, 2, ..., x - 1$。（可以自己手搓几个样例试试）

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int minlen = INT_MAX;
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        minlen = min(minlen, r - l + 1);
    }
    printf("%d\n", minlen);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        printf("%d ", i % minlen);
    return 0;
}
```

---

---

## 作者：chenhouyuan (赞：0)

显然一个 $\begin{bmatrix} l , r \end{bmatrix}$ 的区间最多只能包含 $r-l+1$ 个数，因此该区间的 $\operatorname{mex}$ 最大值为 $r-l+1$。

因此有:
### $ans=\min_{i = 1}^m(r_i-l_i+1)$
 $ans$ 即为答案的上界。我们开始尝试构造一个序列来达到这个上界。我们发现轮流输出 $0$ 到 $ans-1$ 能使得对于任意的 $\begin{bmatrix} l_i , r_i \end{bmatrix}$ 均包含 $0$ 到 $ans-1$ 中的所有数。输出即可。
#### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,a=0x7fffffff,l,r,x;
int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>l>>r;
		a=min(a,r-l);
	}
	a++;
	for(int i=0;i<n;i++){
		cout<<x<<' ';
		x++;
		x%=a;
	}
	return 0;
}

```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF739A)

# 前置知识

[贪心](https://oi-wiki.org/basic/greedy/) | [构造](https://oi-wiki.org/basic/construction/)

# 解法

从贪心的角度分析，最小的 $\operatorname{mex}$ 仅会与长度最小的区间有关；另外为使得 $\operatorname{mex}$ 最大，当 $\operatorname{mex}$ 等于区间长度的时候即为所求。记 $ans$ 表示此时得到的答案。

构造序列时，长度最小的区间一定包含 $[0,ans-1]$ 的所有数。对于其他的区间，一定包含一个长度为 $ans$ 的区间，使得这个区间也包含 $[0,ans-1]$ 的所有数，剩余的部分长度如果小于 $ans$，可以任意构造；否则，构造方法同上。于是，我们得到了一种可行的构造：将 $[0,ans-1]$ 循环输出即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
int main()
{
	int n,m,l,r,i,len=0x7f7f7f7f;
	cin>>n>>m;
	for(i=1;i<=m;i++)
	{
		cin>>l>>r;
		len=min(len,r-l+1);
	}
	cout<<len<<endl;
	for(i=1;i<=n;i++)
	{
		cout<<i%len<<" ";
	}
	return 0;
}
```

---

## 作者：zfy2006 (赞：0)

##### 题意简述：

有一个长度为 $n$ 的序列，并给出 $m$ 个询问区间 $l$ 到 $r$ ，定义 $mex$ 为一段区间中未出现过的最小自然数（该自然数不要求在整个序列中出现过）。现在请你使这 $m$ 个区间的 $mex$ 的最小值最大，并输出该值与一个长度为 $n$ 的合法序列。

##### 分析：

对于每个区间 $l$ 到 $r$ ，最多只有 $r-l+1$ 个互不相同的数，则如果我们想让其 $mex$ 最大，应使这 $r-l+1$ 个数分别为 $0$ 到 $r-l$ ,这时它的 $mex$ 最大为 $r-l+1$ 。那么第一个问题我们就解决了， $ans=\min ({r_i -l_i +1})$ 。

我们再考虑第二个问题，如何构造出一个合法的序列?其实我们此时对于每一个区间只要使它的 $mex$ 满足 $ans$ 即可。因为就算使该区间的每个数不同，它的 $mex$ 更大了，但对全局的 $ans$ 毫无贡献。所以我们只需要循环输出 $0$ 到 $ans-1$ 即可，因为这样可以使任意一个长度为 $ans$ 的区间都有 $0$ 到 $ans-1$ 这几个数，并且更长的区间也会包含一个完整的“循环节”，则这样构造出的序列一定是合法的。

##### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m,ans;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        ans=min(ans,r-l+1);
    }
    cout<<ans<<'\n';
    for(int i=1;i<=n;i++){
        cout<<i%ans<<' ';
    }
    return 0;
}
```

---

## 作者：WhisperingWillow (赞：0)

首先有一个结论，**构造区间 $[l,r]$ 的最大 $\operatorname{mex}$ 为 $r-l+1$**。

设 $m$ 个区间的 $\operatorname{mex}$ 最小值最大为 $A$，则 $A=\min \limits_{i=1}^m (r_i-l_i+1)$。

令所有长度为 $A$ 的区间的 $\operatorname{mex}$ 值都为 $A$，令 $a_i = i \bmod A$ 即可。

代码不给了。

---

