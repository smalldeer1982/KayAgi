# [ONTAK2015] OR-XOR

## 题目描述

给定一个长度为 $n$ 的序列 $a_1, a_2, \cdots, a_n$，请将它划分为 $m$ 段连续的区间，设第 $i$ 段的费用 $c_i$ 为该段内所有数字的异或和，则总费用为 $c_1 \operatorname{or} c_2 \operatorname{or} \cdots \operatorname{or} c_m$。请求出总费用的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq m \leq n \leq 5 \times 10^5$，$0 \leq a_i \leq 10^{18}$。

## 样例 #1

### 输入

```
3 2
1 5 7```

### 输出

```
3```

# 题解

## 作者：云殊呀 (赞：25)

## 题解

#### 前置知识：

做这个题之前我们先要了解与按位异或相关的两个性质：

1. $b=a\oplus b\oplus a$

1. $0\oplus1=1,0 \oplus 0=0$

以及按位或的一个性质：多个数按位或，任意一个数的第 $i$ 位为 $1$，则结果的第 $i$ 位为 $1$。

#### 题目分析：

回到题目本身，要求将数列分成 $M$ 段，求每段的异或和，让最后每段异或和的按位或最小。首先每段异或和，根据上面异或的第一条性质，我们很容易想到前缀异或和，结合按位或的性质，我们可以按位从高往低贪心，尽量保证高位为 $0$，也就是说，让分成的 $M$ 段，每段都为 $0$。

#### 代码设计：

对于第 $j$ 位，从前往后异或，统计出现 $0$ 的次数，若小于 $M$，则说明该位无论怎么分最后按位或结果都是 $1$。这里要注意的是，$0$ 的次数可能会大于 $M$，因为我们用的是前缀和，所以两个相邻 $0$ 区间合并之后异或和还是 $0$。

因为贪心思想为尽量保证高位为 $0$，所以低位的分发不能与高位相冲突，否则也是 $1$。

那么我们需要将高位不能作为 $M$ 段断点的位置标记下来，在枚举低位的时候，要同时异或和为 $0$ 以及该点是否为高位断点。

如果第 $j$ 位的结果能为 $0$，那么需要更新断点标记。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define N 500010
ll n,m,a[N],flag[N],ans;
//flag数组为断点标记数组
int main(){
	ll i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	for(j=62;j>=0;j--){
		ll tmp=0,sum=0;
		for(i=1;i<=n;i++){
			tmp ^= (a[i]>>j) & 1;
  			//判断第j位的异或和是否为1
			if(!tmp && !flag[i]) sum++;
  			//同时要保证不与高位冲突
		}
		if((tmp&1) || (sum<m)){
         //如果该位最终结果为1，或者不能分成超过M段
			ans+= 1ll<<j;
			continue;
		}
		tmp=0;
      //将第j为的断点标记加上去
		for(i=1;i<=n;i++){
			tmp^= (a[i]>>j) & 1;
			if(tmp && !flag[i]) flag[i]=1;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Unordered_OIer (赞：7)

# P8019 Solution

这么老这么经典的题怎么出现在这里（

## Description

将一个长度为 $n$ 的序列 $a$ 划分为 $m$ 段，使每段异或和的或和最小。

即让下面这个式子的值最小：

$$(a_1 \oplus a_2 \oplus \cdots \oplus a_{x_1}) \vee (a_{x_1+1} \oplus \cdots \oplus a_{x_2}) \vee \cdots \vee (a_{x_{m-1}}+1 \oplus \cdots \oplus a_n)$$

其中 $x_0 \sim x_m$ 自己构造，$x_0=0,x_m=n$。

## Solution

首先异或有一个非常显然的性质：$a \oplus a =0,a \oplus 0=a$，所以记序列 $a$ 的前缀异或和 $g_i=(a_1 \oplus a_2 \oplus \cdots \oplus a_i)$，那么原式就变成了 $g_{x_1} \vee g_{x_2} \vee \cdots \vee g_{x_{m-1}} \vee g_n$，把这个式子最小化就行了。

这就变成了一个非常经典的按位贪心，对于每一位我们都希望是 $0$，从高位往低位贪心就行了。

复杂度 $\mathcal O(62n)$

## Code

```cpp
	for(ll now_pos = 1ll << 62; now_pos; now_pos>>=1)
	{
		for(sum = 0, tmp = 1; tmp <= n; tmp++)
			sum += (val[tmp] & now_pos) > 0;
		if(sum & 1) ans ^= now_pos;
		else
		{
			for(flag = sum = 0, tmp = 1; tmp < n; tmp++)
			{
				flag ^= (val[tmp] & now_pos);
				xp[tmp] += flag, sum += (xp[tmp] == 1) & flag;
			}
			if(sum + tot + m > n)
			{
				ans ^= now_pos;
				for(flag = sum = 0, tmp = 1; tmp < n; tmp++)
				{
					flag ^= (val[tmp] & now_pos);
					xp[tmp] -= flag;
				}
			}
			else tot += sum;
		}
	}
	printf("%lld\n", ans);
```

---

