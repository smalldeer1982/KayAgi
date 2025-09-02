# Ehab and a 2-operation task

## 题目描述

有一个长度为$n$的序列$a$,你可以在这个序列上做两种操作:

+ 选择下标 $i(1 \leq i \leq n) $ 和一个整数$x(0 \leq x \leq 10^6)$,然后对每一个下标$j(1 \leq j \leq i)$,把所有的$a_j$换成$a_j+x$,也就是说,给序列中以$i$为最后一个元素的前缀中的每一个元素加上$x$.
+ 选择一个下标$i,(1 \leq i \leq n) $,一个整数$x(0 \leq x \leq 10^6)$,然后对每一个下标$j(1 \leq j \leq i)$,把$a_j$换成  $a_j \% s$,也就是说，把序列中以$i$为最后一个元素的前缀中的每一个元素对$x$取模.

你能在不超过$n+1$次操作之内把这个序列变成严格递增的吗?

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
0```

## 样例 #2

### 输入

```
3
7 6 3
```

### 输出

```
2
1 1 1
2 2 4
```

# 题解

## 作者：米奇奇米 (赞：2)

## 题解-CF1088C Ehab and a 2-operation task

### 题目意思：
现在存在两种操作：

* $A,l,v$：就是将$[1..l]$的数字加上$v$
* $B,l,v$：就是将$[1..l]$的数字膜上$v$

让你经过$\leq n+1$的不输把原序列边成**严格递增**

### $Solution$

* 很好的**思维题**

我们把$[1..n]$的数字都加上一个很大的数$\leq long long$

* **如何理解这样的操作呢？**

因为要保证严格上升，我们只要让最后一个足够大，让前面$n-1$个数以$1..n-1$排列即可。

* **那么如何做到以$1..n-1$排列呢？**

我们只要每次读入一个数$x$,对它膜上一开始加的很大的数$(+x-1)$即可

对于样例里的$7.6.3$我们只要

* $A,3,10000$原序列变为$10007,10006,10003$
* $B,1,10006$原序列变为$1,10006,10003$
* $B,2,10004$原序列变为$1,2,10003$

这样就做到了严格递增。

### $Code$
```cpp
#include <bits/stdc++.h>
using namespace std;

int n; 

inline int read() {
	#define gc getchar
	int sum=0,ff=1;
	char ch=gc();
	while(!isdigit(ch)) {
		if(ch=='-') ff=-1;
		ch=gc();
	}
	while(isdigit(ch)) 
		sum=sum*10+(ch^48),ch=gc();
	return sum*ff;
}

int main() {
	n=read();
	printf("%d\n",n);
	printf("1 %d 99999\n",n);
	for ( int i=1;i<n;i++ ) {
		int x=read();
		printf("2 %d %d\n",i,x+99999-i);
	}
	return 0;
}
```





---

## 作者：Lyw_and_Segment_Tree (赞：1)

## 题意简述
> 现在有一个长度为 $n$ 的序列 $a$，你可以对这个序列做两种操作，内容如下：
> - 选择一个下标 $i$ 和一个整数 $x$，然后将 $a_1 \sim a_i$ 中所有数加上 $x$。
> - 选择一个下标 $i$ 和一个整数 $x$，然后将 $a_1 \sim a_i$ 中的所有数对 $x$ 取模，即在 $1\le j \le i$ 的情况下，令 $a_j = a_j \bmod x$。  
>
> 请问能否在 $n + 1$ 次操作内使得该数列严格递增。

## 开始解题
首先，这是一道很好的思维题。  
首先，我们考虑把整个数列变为 $1,2 \dots n$ 的形式。那么接下来就转变成如何将 $a_i$ 变为 $i$ 的问题了。  
那么经过简单的运算，我们就可以知道将 $a_i \bmod (a_i - i)$ 就可以使其变为 $i$ ，至于原因其实也特别简单，首先我们假设 $a_i > i$，然后我们发现 $a_i -i$ 它其实只能被用一次，特别是 $a_i$ 非常大而 $i$ 非常小的时候特别明显，所以原式就被化成了这样：
$ a_i \bmod (a_i - i) = a_i-(a_i -i) = a_i - a_i + i = i $。  
然后我们考虑 $a_i \le i$ 的情况，此时就可以使用操作 1 让整个数列加上一个特别大的数，从而让 $a_i > i$。  
然后我们再次审题，发现我们的操作次数就是 $n + 1$ 次，并没有超出限制，因此该思路正确。  
整理一下，可得代码如下：  
```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;
    cin >> n;
    cout << n + 1 << endl;
    cout << "1 " << n << " 114514" << endl;
    for(int i = 1, x; i <= n; i++) {
        cin >> x;
        cout << "2 " << i << " " << x + 114514 - i << endl;
    }
}
```

---

## 作者：little_sun (赞：1)

## 题解 CF1088C 【Ehab and a 2-operation task】

怎么把一个序列弄成单调递增的呢？当然是把它搞成$1 \cdots n$啦

我们显然可以找到这样一种构造

* 对于每个数$a_i$，通过$\mod a_i - i + 1$让它变成$i$

这样有一个漏洞：当前的$a_i$小于$i$怎么办？

我们发现我们还有一次操作机会

所以我们把这次给$1$操作：把整个序列加上一个特别大的数（但要满足题目条件）

这样就刚好用了$n+1$次操作


```cpp
# include <bits/stdc++.h>

int a[2010];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]); 
    printf("%d\n", n + 1);
    printf("1 %d %d\n", n, 899999);
    for(int i = 1; i <= n; i++)
    {
        a[i] += 899999;
        printf("2 %d %d\n", i, (a[i] - i + 1));
        a[i] %= (a[i] - i + 1);
    }
    return 0;
}
```

---

## 作者：Epoch_L (赞：0)

## Solution
一个很简单的想法就是将整个序列变成 $1$ 到 $n$，这时我们需要对每个 $a_i$ 执行 $\bmod (a_i-i)$ 的操作，但是可能 $a_i<i$，所以我们只需要在一开始加上一个极大值即可，刚好 $n+1$ 次操作。

事实上，前面的构造并不完全正确，例如我们无论如何也不能将 $4$ 通过取模变成 $2$，即 $2k\equiv k\pmod p(k\in \mathbb{N}^+)$ 永远不成立，但是我们可以通过加极大值来避免，这个极大值应至少大于 $2\times 2000$，所以这个极大值至少得开到 $4001$，实测 $4001$ 可过，$4000$ 会 WA。

## Code
代码很短，甚至不用开数组。
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
int main(){
  int n;read(n);
  printf("%d\n",n+1);
  printf("1 %d 4001\n",n);
  for(int i=1,x;i<=n;i++){
    read(x);
    printf("2 %d %d\n",i,x+4001-i);
  }
  return 0;
}
```

---

