# Divide and Multiply

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609A/ed5b77bcb83c3732516ccac033270f15c3ac243c.png)William has array of $ n $ numbers $ a_1, a_2, \dots, a_n $ . He can perform the following sequence of operations any number of times:

1. Pick any two items from array $ a_i $ and $ a_j $ , where $ a_i $ must be a multiple of $ 2 $
2. $ a_i = \frac{a_i}{2} $
3. $ a_j = a_j \cdot 2 $

Help William find the maximal sum of array elements, which he can get by performing the sequence of operations described above.

## 说明/提示

In the first example test case the optimal sequence would be:

1. Pick $ i = 2 $ and $ j = 1 $ . After performing a sequence of operations $ a_2 = \frac{4}{2} = 2 $ and $ a_1 = 6 \cdot 2 = 12 $ , making the array look as: \[12, 2, 2\].
2. Pick $ i = 2 $ and $ j = 1 $ . After performing a sequence of operations $ a_2 = \frac{2}{2} = 1 $ and $ a_1 = 12 \cdot 2 = 24 $ , making the array look as: \[24, 1, 2\].
3. Pick $ i = 3 $ and $ j = 1 $ . After performing a sequence of operations $ a_3 = \frac{2}{2} = 1 $ and $ a_1 = 24 \cdot 2 = 48 $ , making the array look as: \[48, 1, 1\].

The final answer $ 48 + 1 + 1 = 50 $ .

In the third example test case there is no way to change the sum of elements, so the answer is $ 10 $ .

## 样例 #1

### 输入

```
5
3
6 4 2
5
1 2 3 4 5
1
10
3
2 3 4
15
8 8 8 8 8 8 8 8 8 8 8 8 8 8 8```

### 输出

```
50
46
10
26
35184372088846```

# 题解

## 作者：WRuperD (赞：2)

简单思维题

### 思路
首先我们可以吧每个数都分解成 $x \cdot 2^y$ 形式。我们把这些数按 $x$ 排序，再把这些2次幂全乘到最大的那个 $x$ 上即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[20];
int main(){
	int t;
	cin>>t;
	while(t--){
		long long ans = 0;
		int n;
		cin>>n;
		long long cnt =  0;
		for(int i = 1; i <= n; i++){
			cin>>a[i];	
			while(a[i] % 2 == 0){
				a[i] /= 2;
				cnt++;
			}	
		}
		sort(a+1, a+n+1);
		a[n] *= pow(2, cnt);
		for(int i = 1; i <= n; i++){
			ans += a[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：智子 (赞：1)

## 题意

输入 $n$ 个数 $a_i$，可以进行若干次操作，每次操作将 $a$ 中的一个偶数除以 $2$，将另一个数乘 $2$。求 $a$ 中所有数的总和最大是多少。

## 思路

我们首先可以将 $a$ 中所有的 $2$ 的因子都提取出来，直到这剩下奇数，再分配这些 $2$。

当 $a_i > a_j$ 时，让 $a_i$ 乘 $2$ 显然比让 $a_j$ 乘 $2$ 更优。所以我们可以将所有的 $2$ 全都分配给剩下的奇数中最大的数。

## 代码

```cpp
#include<cstdio>
using namespace std;

const int MAXN = 20 + 5;

long long a[MAXN];

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        int n, cnt = 0, p = 1;

        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            while(a[i] % 2 == 0) {
                a[i] /= 2;
                cnt++;
            }
        }
        for(int i = 2; i <= n; i++) {
            if(a[i] > a[p]) {
                p = i;
            }
        }
        a[p] <<= cnt;
        long long ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += a[i];
        }
        printf("%lld\n", ans);
    }

    return 0;
}

```

---

## 作者：qwq___qaq (赞：0)

对于本题，首先考虑贪心：

因为 $1\le a_i\le15$，我们可以发现每个数最多除 3 次，我们就可以先把 2 除尽，记录所有的 2 的次数 cnt。然后，我们可以考虑对除尽的 2 的最大值后，把所有的 2 全部乘在最大值上。因为最大值乘 2 之后更大，可以保证这样更优。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,a[20];
inline int qpow(int a,int b){
	int num=1;
	while(b){
		if(b%2)
			num=num*a;
		a=a*a;
		b>>=1;
	}
	return num;
}//快速幂（不加也行）
signed main(){
	scanf("%lld",&T);
	while(T--){
		int sum=0,cnt=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]);
		for(int i=1;i<=n;++i)
			while(a[i]%2==0){
				a[i]/=2;
				++cnt;
			}
		stable_sort(a+1,a+n+1);
		a[n]*=qpow(2,cnt);
		for(int i=1;i<=n;++i)
			sum+=a[i];
		printf("%lld\n",sum);
	}
	return 0;
}
```

---

## 作者：方塘 (赞：0)


### 思路：

这道题还是比较巧妙的。

首先，操作是不在乎顺序的，我们完全可以先把所有的 **2** 剥离出来，再找一个最大的基数把它全都乘上去。

为什么全都乘到一个数上呢？因为这样才收益最大。

所以我需要记录当前最大基数，当找到比它还大的时，只需要把它直接加进 **ans** 里就可以了（新数小就把新数加进去）

最后把所有 **2** 乘到最后的最大值上加入 **ans** ，输出即可。

### AC代码：

```cpp
#include<stdio.h>

int T,n,k,c,ma;
long long ans,er[100]={1};

int main(){
	
	scanf("%d",&T);
	
	for(int i=1;i<=50;i+=1) er[i]=er[i-1]*2;
	
	while(T--){
		
		ma=0,ans=0,c=0;
		scanf("%d",&n);
		
		for(int i=1;i<=n;i+=1){
			scanf("%d",&k);
			while(k%2==0) k/=2,c+=1;
			if(k>ma) ans+=ma,ma=k;
			else ans+=k;
		}
		
		ans+=er[c]*ma;
		printf("%lld\n",ans);
	}
	
	return 0;
}
```


---

## 作者：Marsrayd (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1609A)

## 题意简述


给定长度为 $n$ 的序列 $a$，可以进行任意次操作，最大化 $\sum\limits_{i=1}^n a_i$。

- 操作：选则两个数 $a_i,a_j$，其中 $a_i$ 是偶数，令 $a_i/2,a_j\times 2$。


## $\texttt{SOLUTION}$

我们可以计算出序列中所有数含有因子 $2$ 总数并记录下来，然后将原序列的所有数去除所的有因子 $2$ ，这样，这些 $2$ 是自由的，它们可以乘在任意数上，因为题目要求最后的总和最大，所以将它们乘在去除 $2$ 因子后最大的 $a_i$ 上即可。


$\texttt{AC CODE}$

```cpp

//由于考场写得太急，代码实现稍微有点复杂……

//不过思想是一样的。

//其实是我太菜了。

#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n;
struct node{
	int c,d;
}a[30];
bool cmp(node x,node b)
{
	return x.d<b.d;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		scanf("%llu",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%llu",&a[i].c);
			a[i].d=a[i].c;
			while(!(a[i].d&1))
			{
				a[i].d>>=1;
			}
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<n;i++)
		{
			while(!(a[i].c&1))
			{
				a[i].c>>=1,a[n].c<<=1;
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++) ans+=a[i].c;
		printf("%llu\n",ans);
	}
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑贪心。

先将所有的 $2$ 提取出来，然后乘到一个最大的数上就行了。

这样的证明也很简单，若将一个 $2$ 乘到一个非最大的数上，获得的价值一定不优于乘到最大的数上的方法。

总复杂度 $O(n\log a)$。

由于本题 $a$ 的范围比较小，所以直接除就行了，否则需要用位运算优化。

注意本题数据范围较大，需要用长整型变量存贮数据。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,T,a[10005],cnt,sum;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		sum=0;cnt=0;
		for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
		for(int i=1;i<=n;i++){
			while(a[i]%2==0){
				a[i]/=2;cnt++;
			}
		}
		sort(a+1,a+n+1);
		a[n]=a[n]<<cnt;
		for(int i=1;i<=n;i++)
		sum+=a[i];
		printf("%I64d\n",sum);
	}
	return 0;
}
```


---

