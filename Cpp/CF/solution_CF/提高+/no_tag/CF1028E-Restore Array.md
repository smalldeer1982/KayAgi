# Restore Array

## 题目描述

在讨论 Codeforces Round 的合适 A 题时，Kostya 创建了一个循环正整数数组 $a_1, a_2, \ldots, a_n$。由于讨论时间很长且没有进展，Kostya 又创建了一个新的循环数组 $b_1, b_2, \ldots, b_n$，其中 $b_i = (a_i \bmod a_{i+1})$，这里 $a_{n+1} = a_1$。其中 $mod$ 表示[取模运算](https://en.wikipedia.org/wiki/Modulo_operation)。当讨论变得有趣时，Kostya 完全忘记了数组 $a$ 的样子。突然，他想到从数组 $b$ 恢复数组 $a$ 可能是一个有趣的问题（可惜不是 A 题）。

## 说明/提示

在第一个样例中：

- $1 \bmod 3 = 1$
- $3 \bmod 5 = 3$
- $5 \bmod 2 = 1$
- $2 \bmod 1 = 0$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 3 1 0
```

### 输出

```
YES
1 3 5 2
```

## 样例 #2

### 输入

```
2
4 4
```

### 输出

```
NO
```

# 题解

## 作者：极寒神冰 (赞：7)

首先考虑$\forall i,b_i=M(1\leq i\leq n)$这种特殊的情况，显然当且仅当$M=0$时有解，证明可以考虑因为是一个环，所以总会存在一个$a_{i\bmod n}=kM,a_{(i \bmod n)+1}=M(1\leq i < n)$此时$b_i=0$。

令$M=\max\limits_{i=1}^n b_i$，然后找到一个下标$i(1\leq i\leq n)$满足$b_{(i-1) \bmod n}<M$且$b_{i\bmod n}=M$（这里认为$b_0=b_n$）。假设这个下标是$n$，如果不是可以则通过平移数组平移到$n$。

然后考虑构造$a$数组：

$$

a_i=\begin{cases} \sum_\limits{j=i}^{n-1}b_j+2b_n & i<n \\ b_n  & i=n \end{cases}

$$

这样的$a$数组满足所有条件。因为：

- $a_n<a_1$
- $a_i-a_{i+1}=b_i(i<n)$
- $b_{i}<a_{i+1}(i<n-1)$因为$b_n$是最大的数，且$b_n>0$
- $b_{n-1}<b_n=M$
- $b_n<a_1$因为$b_n<2b_n$

以及，如果数组中除了$1$都是$0$，那么$b_n$前面的系数$2$并没有什么作用，因为此时$a_n \bmod a_1=0$。以及事实上可以用$b_n+10^{10}$代替$2b_n$，显然此时构造方法仍然成立。

```cpp
int n;
int a[155555],b[155555];
int mxv,mxp=-1;
inline int tp(int x)
{
    if(!x) return n;
    return x;
}
signed main()
{
    n=read();
    R(i,1,n) a[i]=b[i]=read();a[0]=b[0]=b[n];
    mxv=*max_element(b+1,b+n+1);
    R(i,1,n) if(b[i]==mxv&&b[i-1]^mxv) {mxp=i;break;}
    if(!~mxp)
    {
        if(!mxv) 
        {
            puts("YES");
            R(i,1,n) writesp(1);puts("");
        }
        else puts("NO");
        return 0;
    }
    a[tp((mxp-1+n)%n)]+=mxv;
    R(i,1,n-1) a[tp((mxp-i+n)%n)]+=a[tp((mxp-i+1+n)%n)];
    puts("YES");
    R(i,1,n) writesp(a[i]);puts("");
}
```





---

## 作者：ethan0328 (赞：0)

## 思路

有一个简单的想法是构造一个序列满足 $a_i<a_{i+1}$ 且 $a_{i+1}-a_i=b_i$。容易想到构造 $a_i=\sum_{j=i}^{n}b_i$。

但如果存在 $a_{i+1} \mid a_i$ 是会爆。所以我们可以把 $b$ 中的最大值移到 $b_n$ 的位置，同时要满足 $b_{n-1}\neq b_n$，这样就能保证不存在整除关系。

如果 $b_1=b_2=...=b_{n-1}=0$ 是会爆，因为 $b_n \bmod b_1=0$。所以我们让 $a_i=(\sum_{j=i}^{n}b_i)+b_n$，$a_n=b_n$ 就行了。

但当所有 $b$ 相等时不存在一个这么一个最大值。可以证明，只有 $b_1=b_2=...=b_n=0$ 时才有解。

如果 $b_1=b_2=...=b_n=x$（$x$ 不为 $0$），一定存在 $a_i<a_{i+1}$，即 $a_i=x$，那所以 $a_j$ 必为 $x$ 的倍数，则必有 $a_i \bmod a_{i+1}=0$，所以不成立。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,mx,cnt,a[N],b[N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	mx=cnt=1;
	for(int i=2;i<=n;i++)
	{
		if(b[i]>b[mx])
		{
			cnt=1;
			mx=i;
		}else if(b[i]==b[mx])
		{
			cnt++;
		}
	}
	if(cnt==n)
	{
		if(b[1]!=0)
		{
			cout<<"NO\n";
			return 0;
		}
		cout<<"YES\n";
		for(int i=1;i<=n;i++)
		{
			cout<<1<<" ";
		}
		return 0;
	}
	cnt=b[mx];
	b[0]=b[n];
	for(int i=1;i<=n;i++)
	{
		if(b[i]==cnt&&b[i]!=b[i-1])
		{
			mx=i;
			break;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=mx;i++)
	{
		a[i+n-mx]=b[i];
	}
	for(int i=mx+1;i<=n;i++)
	{
		a[i-mx]=b[i];
	}
	a[n-1]+=a[n];
	for(int i=n-1;i;i--)
	{
		a[i]+=a[i+1];
	}
	for(int i=1;i<=mx;i++)
	{
		cout<<a[i+n-mx]<<" ";
	}
	for(int i=mx+1;i<=n;i++)
	{
		cout<<a[i-mx]<<" ";
	}
}
```

---

