# Dominated Subarray

## 题目描述

Let's call an array $ t $ dominated by value $ v $ in the next situation.

At first, array $ t $ should have at least $ 2 $ elements. Now, let's calculate number of occurrences of each number $ num $ in $ t $ and define it as $ occ(num) $ . Then $ t $ is dominated (by $ v $ ) if (and only if) $ occ(v) > occ(v') $ for any other number $ v' $ . For example, arrays $ [1, 2, 3, 4, 5, 2] $ , $ [11, 11] $ and $ [3, 2, 3, 2, 3] $ are dominated (by $ 2 $ , $ 11 $ and $ 3 $ respectevitely) but arrays $ [3] $ , $ [1, 2] $ and $ [3, 3, 2, 2, 1] $ are not.

Small remark: since any array can be dominated only by one number, we can not specify this number and just say that array is either dominated or not.

You are given array $ a_1, a_2, \dots, a_n $ . Calculate its shortest dominated subarray or say that there are no such subarrays.

The subarray of $ a $ is a contiguous part of the array $ a $ , i. e. the array $ a_i, a_{i + 1}, \dots, a_j $ for some $ 1 \le i \le j \le n $ .

## 说明/提示

In the first test case, there are no subarrays of length at least $ 2 $ , so the answer is $ -1 $ .

In the second test case, the whole array is dominated (by $ 1 $ ) and it's the only dominated subarray.

In the third test case, the subarray $ a_4, a_5, a_6 $ is the shortest dominated subarray.

In the fourth test case, all subarrays of length more than one are dominated.

## 样例 #1

### 输入

```
4
1
1
6
1 2 3 4 5 1
9
4 1 2 4 5 4 3 2 1
4
3 3 3 3
```

### 输出

```
-1
6
3
2
```

# 题解

## 作者：registerGen (赞：2)

### 发一篇尺取法（双指针，$\text{two pointers}$ ）的题解

先介绍一下双指针：

双指针能解决一些区间的问题，但**有局限性：**

**双指针的题，必须能从一个区间转移到与它相邻的区间，例如 $[l,r]\to[l,r+1],\ [l,r]\to[l+1,r],\ [l,r]\to[l+1,r+1]$，而且复杂度最好为 $\text{O}(\log n)$ 或 $\text{O}(1)$**

实现：开两个指针 $l,r$，通过移动指针（转移）**枚举**所有情况，得出答案。

双指针实际上是优雅的暴力。

**例如，给你一个序列 $\{a_n\}$ 和 $k$，现在，**
$$\forall i \in [1,n-k+1]$$
**求出**
$$\sum_{j=i}^{i+k-1}a_j\left(\text{or }\prod_{j=i}^{i+k-1}a_j\right)$$

以和为例：

~~前缀和水过~~

显然有
$$\sum_{i=2}^{k+1}a_i=\sum_{i=1}^{k}a_i-a_1+a_{k+1},$$
$$\sum_{i=3}^{k+2}a_i=\sum_{i=2}^{k+1}a_i-a_2+a_{k+2},$$
等等，而这个转移的复杂度为 $\text{O}(1)$。

核心代码：(此为蒟蒻现写，如发现问题请指出)
```cpp
int l=1,r=k,s=0;
for(int i=1;i<=k;i++)
	s+=a[i];
while(r<=n)
{
	printf("%d\n",s);
	s-=a[l++];
	s+=a[++r];
}
```
**关于本题：**

其他题解已经指出，本题实际上是要求一个最短的序列 $t'$，$\text{s.t.}\ t'$ 的众数为 $2$。

这类题有 **$\text{O}(n)$ 通解：**
>**1**. 向右移动 $r$ 直到满足条件
>
>**2**. `if(不满足条件)then break`
>
>**3**. 更新 $ans$
>
>**4**. 将 $l$ 右移一位，并将该更新的更新

至于正确性和时间复杂度的证明，留给读者思考。

---

```cpp
#include<cstdio>

const int N=2e5,INF=2e9;

int a[N+10],h[N+10]; // h_i 代表 i 在 a 中出现的次数

template<typename T>
inline T min(const T& a,const T& b)
{
	return a<b?a:b;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",a+i);
			h[i]=0;
		}
		if(n==1)
		{
			puts("-1");
			continue;
		}
		int l=1,r=1,ans=INF;
		bool f; // f 代表是否可行
		while(1)
		{
			// Step 1
			while(r<=n&&!f)
				if(++h[a[r++]]==2)
				{
					f=true;
					break;
				}
			// Step 2
			if(r>n&&(!f))break;
			// Step 3
			ans=min(ans,r-l);
			// Step 4
			if(--h[a[l++]]==1)f=false;
		}
		printf("%d\n",ans==INF?-1:ans);
	}
	return 0;
}
```
最后，我有[推荐题目](http://poj.org/problem?id=3061)

---

## 作者：B_Qu1e7 (赞：2)

~~翻译差评 不知道是谁翻的~~

题意：给定一个序列，求所有只有唯一众数的子序列中**最小长度**的一个，并输出其长度。若不存在，输出$-1$。

简化：求任意头尾元素相同的序列中最小长度的一个。

对于正确性证明，我们考虑任意一个序列$A$，其由头尾相同的元素为$S$和中间的序列$O$组成 ~~SOS~~，且序列$O$中包含一个头尾也有相同元素$T$的序列$C$。

可以发现，无论序列$O$中包不包含元素$S$，序列$C$总是满足条件，并且长度比$A$小。所以，用$A$来更新答案并不影响最终答案的构成。

因此，用一个$pre[i]$数组记录数$i$上次出现的位置，更新答案，并更新$pre[i]$即可。

```
#include<cctype>
#include<cstdio>
#define R register
int T,N,A[200005];
template<class T>inline void read(R T &m)
{
	m=0;
	R char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
int main()
{
	read(T);
	while(T--)
	{
		int pre[200005]={0},ans=998244353;//注意题目要求最小值，所以INF
		read(N);
		for(R int i=1; i<=N; ++i)
		{
			read(A[i]);
			if(pre[A[i]]/*出现过*/&&i-pre[A[i]]+1<ans)
			{
				ans=i-pre[A[i]]+1;
			}
			pre[A[i]]=i;
		}
		printf("%d\n",ans==998244353?-1:ans);
	}
}
```

---

## 作者：Wind_love (赞：0)

## 思路
题目要求求最长度最短的子序列，使得众数唯一。  
因为题中要求长度至少为二，并且要求使序列长度最短，所以此时众数的出现次数一定为两次。  
接下来我们考虑这个问题如何解决，对于每一个数，我们保存它上一次出现的位置，若它曾出现过，那么尝试更新答案为它上一次出现的位置到当前位置的长度。  
简单说明一下为什么这样能更新到最小值，因为我们每次更新当前数的出现位置，所以可以保证一定可以包含所有众数唯一的区间，且不会包括使得答案更小的众数不唯一情况，因此成立。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],las[200005];
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        int ans=1e9;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(las[a[i]])ans=min(i-las[a[i]]+1,ans);
            las[a[i]]=i;
        }
        if(ans==1e9)ans=-1;
        cout<<ans<<"\n";
        for(int i=1;i<=n;i++)las[a[i]]=0;
    }
    return 0;
}

---

## 作者：PeterBei (赞：0)

这题可以直接贪心，但题解区里的贪心不是不正确就是不充分，所以写一篇严谨一点的。

---

我们发现，当一个区间中存在唯一众数时，当且仅当该数出现次数大于等于 $2$ 且没有与该众数出现次数相同的数。

由此显然可得，答案区间开头的数字必定等于结尾的数字，该数即为答案区间的众数，且该数字出现次数**等于二**，同时区间中没有第二个出现次数大于一的数。

注意到，若一个符合该要求（开头结尾的数字相同）的父区间包含一个同样符合该要求的子区间，则子区间的答案长度一定优于父区间，因此可以直接记录每个开头结尾数字相同的区间，答案即为这些区间长度的最小值。

---

Python 代码：

``` py
T = int(input())
for TT in range(1, T + 1):
    minn = 0x3f3f3f3f
    to = [-1] * 200010
    n = int(input())
    lis = list(map(int, input().split()))
    #print(lis)
    for i in range(1, n + 1):
        if to[lis[i - 1]] == -1:
            to[lis[i - 1]] = i
        else:
            minn = min(minn, i - to[lis[i - 1]] + 1)
            to[lis[i - 1]] = i
    if minn == 0x3f3f3f3f:
        print(-1)
    else:
        print(minn)
```

---

## 作者：lyzhsxx (赞：0)

### 思路
这题我们发现被 $v$ 支配的最短子串有一个特点，两头一样！！！用这个规律 + map 就可以过了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
void f(){
	map<int,int> mp;//定义map
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}//输入
	if(n<2){
		cout<<-1<<endl;
		return ;
	}//没有
	int ans=INT_MAX;
	for(int i=1;i<=n;i++){
		if(mp[a[i]]==0) mp[a[i]]=i;//现在位置
		else{
			ans=min(ans,i+1-mp[a[i]]);//求最小值
			mp[a[i]]=i;//同第17行
		}
	}
	if(ans!=INT_MAX) cout<<ans<<endl;//有解
	else cout<<-1<<endl;//无解
}//核心
int main(){
	int n;
	cin>>n;
	while(n--){
		memset(a,0,sizeof a);
		f();
	}//n个样例
	return 0;
}
```

---

## 作者：ATION001 (赞：0)

## 题目描述
一个长度为 $n$ 的序列，请判断是否存在一个子串，这个子串**有且仅有一个众数**。

如果存在这样的子串，请输出这个子串的最小长度。如果不存在，请输出 $-1$。

本题有多组测试数据。
## 思路
先来看一组数据：
```cpp
1
4
5 3 5 2
```
```cpp
3
```
可以发现，序列 $[5,3,5]$ 是最短的。

那么得出一个结论：
>开头和结尾相同的子串长度是最短的。

我们边遍历数组 $a$ 边更新 $a_i$ 最后一次出现的位置（注意：计算完了再更新），第二次出现直接计算中间的距离即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],b[200005];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(cin>>t;t;t--){
		int ans=INT_MAX; // 下面要取最小值且要输出 -1，方便输出直接取最大值 
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		fill(b,b+200005,0); // 注意每次计算都需要初始化   
		for(int i=1;i<=n;b[a[i]]=i,i++){
			if(b[a[i]]){ // 如果之前出现过
				ans=min(ans,i-b[a[i]]+1); // 更新距离
			}
		}
		cout<<(ans!=INT_MAX?ans:-1)<<'\n'; // 不是最大值照常输出，否则输出 -1 
	}
	return 0;
}
```

---

## 作者：liangbob (赞：0)

### CF1257C 题解

#### 思路分析

首先我们需要证明一个结论：首尾相同，且其中间的连续子序列（$a_2$ 到 $a_{n-1}$）不含有其首位的数的子序列必然为可能的满足题目条件最小子序列。

证明如下：

设这个序列为 $a$，长度为 $n$，$a_1 = a_n=x$。

记这个序列的子序列 $a_2$ 到 $a_{n-1}$ 为 $b$。

1. 如果 $b$ 中有出现次数大于 $x$ 的，则此为众数。（不用担心有等于此数的出现的数在 $b$ 中出现。如果有，由于 $x$ 的出现次数至少为二，所以此数出现次数必然大于二，则任取出现这个数的两个位置，此连续子序列必然比该序列长度小，所以这种序列不会成为最终结果，不可能为可能的满足条件最小子序列）
2. 如果 $b$ 中有出现 $x$，则取从头到这个 $x$ 出现的任一位置这一连续子序列，此连续子序列的长度比 $a$ 小，不可能为可能的满足条件最小子序列。
3. 否则，$x$ 为该序列唯一众数，得证。

接着继续证明：设相邻两个的 $x$ 出现的位置为 $i$，$j$。则从 $i$ 到 $j$ 这一连续子序列必然为满足上述条件的可能的满足题目条件最小子序列。

证明如下：

1. 首尾相同显然。

2. 若从 $i$ 到 $j$ 这一连续子序列中出现了 $x$，则设第一次出现的位置为 $k$，则 $i$ 和 $k$ 为相邻两个的 $x$ 出现的位置，则 $i$ 和 $j$ 不为相邻两个的 $x$ 出现的位置，矛盾。

3. 证毕。

所以，依据上述结论，我们只需要维护一个数组，记录给定的序列中每个数上一次出现的次数，然后每次遍历到一个数，就用这个数到上个数这个连续子序列的长度去更新最小值，这个区间其实就是满足第二个结论的条件的区间，最后输出最小值即可。

#### 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#define IL inline
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int a[N], p[N]; //给定数组和维护数组

void solve()
{
	memset(a, 0x0, sizeof(a));
	memset(p, 0x0, sizeof(p)); //多测清空
	int n;
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	int minv = INF; //最小值
	for(int i = 1;i <= n;i++)
	{
		if(!p[a[i]])
		{
			p[a[i]] = i; //第一次出现，上一次出现的位置为这个位置
		}
		else
		{
			minv = min(minv, i - p[a[i]] + 1); //用这个数到上个数这个连续子序列的长度去更新最小值
			p[a[i]] = i; //更新上一次出现的位置
			if(minv == 2) break; //区间最短为 2，如果更新到了这个值就不用继续更新了，必然为最小
		}
	}
	if(minv >= INF) minv = -1;  //无解
	cout << minv << endl;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}
```



---

## 作者：songhn (赞：0)

### 题解：
首先考虑一下假如有一段连续相同的数字 那么答案就一定是2 即从连续的一段中随便挑连续的两个 那么众数就是这个数 那么接下来只剩下没有连续相同数字的情况

那么我们可以考虑一下答案是怎么构成的 因为是最短 所以肯定是首位两个的数字相同 中间是其他的数字 那么我们就可以扫一遍数组 每次对于数字相同的相邻的两个位置做差取最小值 那么就肯定可以得到答案了

### AC代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<map>
#include<set>
using namespace std;
template<class T>inline void read(T &x) {
    x=0; int ch=getchar(),f=0;
    while(ch<'0'||ch>'9'){if (ch=='-') f=1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    if(f)x=-x;
}
const int inf=0x3f3f3f3f;
const int maxn=200050;
int T,n;
int a[maxn];
int last[maxn];
int main()
{
	cin>>T;
	while(T--)
	{
		
		read(n);
		for(int i=1;i<=n;i++) read(a[i]);
		for(int i=0;i<=n;i++) last[i]=0;
		if(n==1) puts("-1");
		else
		{
			int ans=inf;
			for(int i=1;i<=n;i++)
			{
				if(last[a[i]]!=0)
				{
					ans=min(ans,i-last[a[i]]+1);
				}
				last[a[i]]=i;
			}
			if(ans==inf) puts("-1");
			else cout<<ans<<endl;
		}
	}
	return 0;
}

```

---

## 作者：Ludo (赞：0)

$Part$ $I.$ 题意简述

求一个数组的最长子序列，其中这一子序列需要满足只有唯一的众数。

$Part$ $II.$ 思考过程

我们考虑一种情况：会不会存在一个序列存在一个数出现多于两次但不符合条件？

显然不存在。

我们尝试举例出一种最坏的情况，构造出这样一种序列，使得序列中出现次数最多与出现次数次多的一样多。

我在脑中想了一下，认为$[2,3,2,3]$这样的序列可能是有这么一种情况的。

但是，$[2,3,2]$就是最短的。那么我们就感性理解完毕了。

所以只要有出现多于两次的数，都能构成要求的子序列。我们取最接近的两个一样的数的距离，长度是$min(ans,$第二个数的位置$-$第一个数的位置$+1)$。

------------

怎么实现快速查找最接近的一样的数的位置？

拿个数组，记录数最后一次出现的位置，顺便统计答案。

反正数在之前就已经统计过了，保留没有用，已经一点都不靠近了，那肯定有比它优的答案。

那么只要拿现在数的位置减去上次的位置就能得到序列长度了。


$Part$ $III.$ 代码

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
int T,n,a[200001],rec[200001],ans; a是序列 rec[i]记录i的直到k之前最后一次出现的位置
int main(void)
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n); ans=2147483647; //ans初始化为一个很大的数
		memset(rec,0,sizeof(rec)); //数组记得清零
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if (rec[a[i]]!=0) ans=min(ans,(i-rec[a[i]]+1)); // rec[i]记录a[i]直到i之前最后一次出现的位置
			rec[a[i]]=i; //做完了,更新位置
		}
		if (ans==2147483647) printf("-1\n"); //没被更新过,因此输出无解
		else printf("%d\n",ans);
	}
}


```


---

