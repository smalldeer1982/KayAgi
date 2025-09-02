# [ARC183A] Median of Good Sequences

## 题目描述

给定正整数 $N,K$ ，如果一个长度为 $NK$ 的序列中 $1$ 以上 $N$ 以下的整数分别出现了 $K$ 次，则称这个序列为良好序列，设有 $S$ 个良好序列，则输出按字典序从小到大第  floor $((S+1)/2)$ 个良好序列。其中， floor $(x)$ 表示不超过 $x$ 的最大整数。

## 说明/提示

#### 约束

 $1≤N≤500$ 

 $1≤K≤500$ 

输入的所有值均为整数

#### 示例解释1

 $6$ 个良好序列如下：
 $(1,1,2,2)$ 
 $(1,2,1,2)$ 
 $(1,2,2,1)$ 
 $(2,1,1,2)$
 $(2,1,2,1)$
 $(2,2,1,1)$ 
 
因此，按字典顺序排列的第 $3$ 个良好序列 $(1,2,2,1)$ 就是答案。

## 样例 #1

### 输入

```
2 2```

### 输出

```
1 2 2 1```

## 样例 #2

### 输入

```
1 5```

### 输出

```
1 1 1 1 1```

## 样例 #3

### 输入

```
6 1```

### 输出

```
3 6 5 4 2 1```

## 样例 #4

### 输入

```
3 3```

### 输出

```
2 2 2 1 3 3 3 1 1```

# 题解

## 作者：zlqwq (赞：5)

提供一个时间复杂度为 $O(N\times K)$ 的做法。

第一次首个元素一定是 $\frac{N}{2}$ 上取整。

如果 $N$ 为奇数，就填入 $k$ 个 $\frac{N}{2}$ 上取整。

如果 $N$ 为偶数，直接贪心放就行了。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[505];
signed main(){
	cin>>n>>k;
	if(n==1){
		while(k--){
			cout<<1<<" ";
		}
		return 0;
	}
	for(int i=1;i<=n;++i)a[i]=k;
	if(n%2){
		for(int i=1;i<=k;++i)cout<<n/2+1<<" ";
		a[n/2+1]=0;
		cout<<n/2<<" ";
		a[n/2]--;
		for(int i=n;i>=1;--i){
			while(a[i]){
				a[i]--;
				cout<<i<<" ";
			}
		}
	}
	else{
		cout<<n/2<<" ";
		a[n/2]--;
		for(int i=n;i>=1;--i){
			while(a[i]){
				a[i]--;
				cout<<i<<" ";
			}
		}
	}
	return 0;
}

```

---

## 作者：lichenxi111 (赞：3)

注：本文中引用了部分官方题解。

## 题意

$1$ 到 $N$ 之间的每一个整数都给你 $k$ 个。让你求出所有排列中，按字典序排序第 $\lfloor \dfrac {s+1} {2} \rfloor$ 个排列。

## 思路

朴素做法：对于每一个位置，枚举选哪个数，然后一直往后选，当我发现目前的字典序已经超过要求时，回溯。时间复杂度：上天。

正解：考虑我会选到那个**位置**，在 $N$ 为偶数时，开头为 $1,2,\cdots,\dfrac N 2$ 的排列的数目正好等于开头为 $\dfrac N 2+1,\cdots,N$ 的排列的数目。所以 $\lfloor \dfrac {s+1} {2} \rfloor$ 会选到开头为 $\dfrac N 2$ 的字典序最大的排列。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/l46vd4o0.png)

当 $N$ 为奇数时，开头为 $1,2,\cdots,\dfrac{N-1} {2}$ 的排列数与开头为 $\dfrac{N+3} {2},\cdots,N$ 的排列数完全一致，$\lfloor \dfrac{s+1} {2} \rfloor$ 会选到以 $\dfrac {N+1} {2}$ 为开头的中间的字典序排中间的排列。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/r85s69ii.png)

我们发现，对于以 $i$ 为开头的所有排列，字典序中间的排列的的前 $k$ 项都是 $i$。那么以 $\dfrac {N+1} {2}$ 为开头的中间的字典序排中间的排列的前 $k$ 项都是 $\dfrac {N+1} {2}$。对于剩下 $(N-1)k$ 个数选中间排列的问题，就转换为了 $N$ 为偶数的问题。

期望复杂度：$O(Nk)$。

---

## 作者：Presentation_Emitter (赞：3)

考虑 $\lfloor \frac{S+1}{2} \rfloor$ 意味着什么：

注意到将字典序第 $k$ 小的序列的每一位翻转（定义 $x$ 翻转后为 $N+1-x$）后，它会变成字典序第 $S+1-k$ 小的序列。

那么待求序列满足其翻转后为其本身或字典序第 $\lfloor \frac{S+1}{2} \rfloor+1$ 的序列。前者当且仅当 $N=1$ 时才可能发生。下面讨论后者。

首先因为翻转后字典序只变动 $1$，所以首个元素必定为 $\lceil \frac{N}{2} \rceil$。若 $N$ 为奇数，则这一位翻转后不变，于是我们首先可以填入 $K$ 个 $\lceil \frac{N}{2} \rceil$，然后剩余的元素就是 $N$ 为偶数的情况。若 $N$ 为偶数，考虑最小化原序列与翻转后序列的字典序差，发现最大化剩余部分的字典序是充要的，于是直接贪心放就行了。

时间复杂度 $\Theta(NK)$。

[Code](https://atcoder.jp/contests/arc183/submissions/57167113)

---

## 作者：xxxaIq (赞：2)

考虑每一个位置填什么值合适。

首先给出一个结论，若一个长度为 $n$ 的数列中存在第 $1$ 类元素 $m_1$ 个（它们数值相等，彼此之间不可辨别，就是重复，下同），第 $2$ 类元素 $m_2$ 个，第 $k$ 类元素 $m_k$ 个，那么这个数列一共存在 $\frac{n!}{m_1!m_2!\dots m_k!}$ 种不同的全排列。

显然这道题中 $n=NK$ 且 $m_1,m_2,\dots,m_k=2$。

对于每一个位置 $i$，我们可以从 $1$ 到 $n$ （已经填过的元素除外）枚举这个位置可能的值，我们可以根据上面的可重排列公式的到如果当前位置填入每一个值的最大字典序的排名 $p_1$ 和最小字典序的排名 $p_2$，显然我们需要使得 $p_1,p_2$ 满足 $p1<\lfloor\frac{S+1}{2}\rfloor<p_2$，即可确定位置 $i$ 要填的值。当然也可以使用二分查找，但是本题不需要。

最后我们就可以确定整个序列，时间复杂度 $O(NK)$。

---

## 作者：JXR_Kalcium (赞：2)

## 题目大意

给定一个 $N$ 和 $K$，定义一个长度为 $NK$ 的字符串为 “好串”，当且仅当由 $1\sim N$ 每一个数刚好出现 $K$ 次组成，令 $S$ 为 “好串” 个数，问按字典序升序排列后第 $\lceil\frac{S}{2}\rceil$ 个 “好串” 是什么，数据范围有 $1\le N,K\le 500$。

## 解题思路

首先肯定不能直接暴力枚举所有的 “好串”，于是这一题肯定是道**数学/找规律**题。我们可以先通过一遍全排列得出一个表（斜杠代表我没表）：

| $N/K$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $1$ | $1,2$ | $2,1,3$ | $2,4,3,1$ | $3,2,5,4,1$ | $3,6,5,4,2,1$ | $4,3,7,6,5,2,1$ |
| $2$ | $1,1$ | $1,2,2,1$ | $2,2,1,3,3,1$ | $2,4,4,3,3,2,1,1$ | $3,3,2,5,5,4,4,2,1,1$ | $3,6,6,5,5,4,4,3,2,2,1,1$ | $/$ |
| $3$ | $1,1,1$ | $1,2,2,2,1,1$ | $2,2,2,1,3,3,3,1,1$ | $2,4,4,4,3,3,3,2,2,1,1,1$ | $/$ | $/$ | $/$ |
| $4$ | $1,1,1,1$ | $1,2,2,2,2,1,1,1$ | $2,2,2,2,1,3,3,3,3,1,1,1$ | $/$ | $/$ | $/$ | $/$ |
| $5$ | $1,1,1,1,1$ | $1,2,2,2,2,2,1,1,1,1$ | $/$ | $/$ | $/$ | $/$ | $/$ |
| $6$ | $1,1,1,1,1,1$ | $1,2,2,2,2,2,2,1,1,1,1,1$ | $/$ | $/$ | $/$ | $/$ | $/$ |

显然，$N$ 的奇偶性会导致答案发生明显的变化，所以我们分开讨论。当 $N$ 为奇数且 $N>1$ 时，若 $K=1$，可以发现答案的前两个数分别为 $\lceil\frac{N}{2}\rceil$ 和 $\lfloor\frac{N}{2}\rfloor$，而剩下的数就是 $1\sim N$ 中除了这两个数以外降序排序的结果。对于 $K>1$ 的情况，显然除了第二个数之外的其它数都重复了 $K$ 次，而第二个数会在 $K=1$ 的答案序列中 $\lceil\frac{N}{2}\rceil+1$ 和 $\lceil\frac{N}{2}\rceil+2$ 中间的位置重复 $K-1$ 次（对于 $N=1$ 的情况，特判一下即可）。

当 $N$ 为偶数时，若 $K=1$，类比于 $N$ 为奇数的情况，此时答案的第一个数就为 $\frac{N}{2}$，剩下的数就是 $1\sim N$ 中除了这个数以外降序排序的结果。再看对于 $K>1$ 的情况，除了第一个数之外的其它数都重复了 $K$ 次，而第一个数会在原来 $K=1$ 的答案序列中 $\frac{N}{2}$ 和 $\frac{N}{2}+1$ 中间的位置重复 $K-1$ 次，这就是所有的规律了，模拟即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,k,cnt;

int main()
{
    n=read(); k=read();
    
    if(n<2)
    {
        for(R int i=1; i<=k; ++i)
        write(1), spc; exit(0);
    }
    
    if(n&1)
    {
        for(R int i=1; i<=k; ++i)
        write(n+1>>1), spc; write(n>>1); spc;
        
        for(R int i=n; i; --i)
        {
            if(i!=n>>1 && i!=n+1>>1)
            {
                for(R int j=1; j<=k; ++j)
                write(i), spc;
            }

            if(++cnt==n>>1)
            {
                for(R int j=1; j<k; ++j)
                write(n>>1), spc;
            }
        }
    }

    else
    {
        write(n>>1); spc;

        for(R int i=n; i; --i)
        {
            if(i!=n>>1)
            {
                for(R int j=1; j<=k; ++j)
                write(i), spc;
            }
            
            if(cnt++==n>>1)
            {
                for(R int j=1; j<k; ++j)
                write(n>>1), spc;
            }
        }
    }
    
    return 0;
}
```

---

## 作者：Lcm_simida (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_arc183_a)

通过观察数据范围我们可以发现全排列~~不超时我吃~~。我们根据答案是中间的性质，可以发现如下规律：

1. 当 $n$ 为奇数时，答案的前 $k$ 位就是 $\frac{n+1}{2}$，
2. 当 $n$ 为偶数时，答案的首位就是 $\frac{n}{2}$。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,ans=0,a[250005];
int main(){
	cin>>n>>m;
	if(n==1){
		for(int i=1;i<=m;i++) cout<<"1 ";
		return 0;
	}
	if(n%2==0){
		cout<<n/2<<" ";
		int flag=0;
		for(int i=n;i>=1;i--){
			for(int j=1;j<=m;j++){
				if(flag==1||i!=n/2) cout<<i<<" ";
				else flag=1;
			}
		}
	}else{
		for(int i=1;i<=m;i++) cout<<(n+1)/2<<" ";
		cout<<n/2<<" ";
		for(int i=n;i>=1;i--){
			if(i==(n+1)/2) continue;
			for(int j=1;j<=m;j++){
				if(j==1&&i==n/2) continue;
				cout<<i<<" ";
			}
		}
	}
	return 0;
}
```

---

## 作者：yangdezuo (赞：0)

# 题意
一个长度为 $NK$ 的序列中 $1$ 到 $N$ 的整数分别出现了 $K$ 次，我们要输出字典序从小到大的第 $((S + 1)/2)$ 下取整。

# 思路
在我们多枚举几种情况后就能发现：

- 首先第一个数要是 $((N + 1)/2)$。

- 当 $N$ 为偶数时，后面的数从大到小输出就行。

- 当 $N$ 为奇数时，先输出完 $K$ 个 $((N + 1)/2)$ 和一个 $((N + 1)/2 - 1)$，再把剩下的数从大到小输出。

# 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,s,x;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	if(n==1){//特判 n==1 
		for(int i=1;i<=k;i++) cout<<"1 ";
		return 0;
	}
	x=(n+1)/2;
	cout<<x<<" ";
	if(n%2==0){//偶数 
		for(int i=n;i>=1;i--)
			for(int j=(i==x?k-1:k);j>=1;j--)
				cout<<i<<" ";
		return 0;
	}
	for(int i=2;i<=k;i++) cout<<x<<" ";
	cout<<x-1<<" ";
	for(int i=n;i>=1;i--)
		for(int j=(i==x?0:i==x-1?k-1:k);j>=1;j--)
			cout<<i<<" ";
} 
```

---

## 作者：HNOIRPplusplus (赞：0)

当 $N$ 为偶数的时候，对于任何一个可行的序列，用 $N$ 减去其中的每一个数可以得到另一个序列。所以，较小的那一半中，开头的元素都是 $\frac N 2$ 及以下的；另一半则是以上的。

所以当 $N$ 为偶数的时候，找出 $\frac N 2$ 开头的最大的序列即为答案，把剩下的元素按照从大到小的顺序输出即可。

当 $N$ 为奇数的时候，对于任何一个可行的序列，用 $N$ 减去其中的每一个不是 $\frac{N+1}2$ 的元素，可以得到另一个序列。所以，所有开头小于 $\frac{N+1}2$ 的序列可以和所有开头大于 $\frac{N+1}2$ 的序列一一对应，则它们都不可能是正中间那个我们要求的序列。

因此序列的第一位必须是 $\frac{N+1}2$。类似的，只要还有 $\frac{N+1}2$ 能够被放置，就必须被放置在开头。于是在开头放了 $K$ 个 $\frac{N+1}2$ 之后，剩下的元素又是偶数个了，按照上面 $N$ 为偶数的方式处理即可。

小心处理 $N=1$ 的情况。

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
  int n, k;
  cin >> n >> k;
  if(n == 1) {
    for(int i = 1; i <= k; i++) {
      cout << "1 ";
    }
    return 0;
  }
  if(n % 2) {
    for(int i = 1; i <= k; i++) {
      cout << (n + 1) / 2 << ' ';
    }
  }
  cout << n / 2 << ' ';
  for(int i = n; i; i--) {
    for(int j = 1; j <= k - (i == n / 2); j++) {
      if(2 * i - 1 != n) {
        cout << i << ' ';
      }
    }
  }
}
```

---

