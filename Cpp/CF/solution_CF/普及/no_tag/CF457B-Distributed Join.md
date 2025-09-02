# Distributed Join

## 题目描述

Piegirl was asked to implement two table join operation for distributed database system, minimizing the network traffic.

Suppose she wants to join two tables, $ A $ and $ B $ . Each of them has certain number of rows which are distributed on different number of partitions. Table $ A $ is distributed on the first cluster consisting of $ m $ partitions. Partition with index $ i $ has $ a_{i} $ rows from $ A $ . Similarly, second cluster containing table $ B $ has $ n $ partitions, $ i $ -th one having $ b_{i} $ rows from $ B $ .

In one network operation she can copy one row from any partition to any other partition. At the end, for each row from $ A $ and each row from $ B $ there should be a partition that has both rows. Determine the minimal number of network operations to achieve this.

## 说明/提示

In the first example it makes sense to move all the rows to the second partition of the second cluster which is achieved in $ 2+6+3=11 $ operations

In the second example Piegirl can copy each row from $ B $ to the both partitions of the first cluster which needs $ 2·3=6 $ copy operations.

## 样例 #1

### 输入

```
2 2
2 6
3 100
```

### 输出

```
11
```

## 样例 #2

### 输入

```
2 3
10 10
1 1 1
```

### 输出

```
6
```

# 题解

## 作者：AFewSuns (赞：3)

### 题意简述

给定数组 $a$ 和 $b$，大小为 $n$ 和 $m$，每次操作可以把 $a$ 数组或 $b$ 数组里的任意位置的数复制到任意其他位置，其代价为该位置的值。最后需要满足 $a$ 数组的任意位置与 $b$ 数组的任意位置都被复制到了同一个地方。求最小代价。

### 题目分析

考虑 $a$ 数组的位置 $i$ 和 $b$ 数组的位置 $j$，要将这两个位置复制到同一个地方，有两种情况：

1. 直接把 $a_i$ 复制到 $b_j$（假设 $a_i \leq b_j$，反之同理）

2. 将 $a_i$ 复制到另一个地方 $a_k$，再把 $b_j$ 复制到 $a_k$（也可以复制到 $b_k$，同理）

第二种情况看似代价更大一点，但实际上同时满足了 $b_j$ 与 $a_i$，$a_k$ 复制到同一地方的条件。

于是考虑贪心。

令 $sum_b$ 为 $b$ 数组所有元素的和，$max_a$ 为 $a$ 数组的最大值，$pos_a$ 为 $a$ 数组中最大值的位置。

假设将 $b$ 数组的所有位置复制到 $a$ 的所有位置上，因为 $b$ 中每个数都要复制到 $a$ 上 $n$ 次，所以总的操作代价是 $n \times sum_b$。当然这只用到了情况1，还没有用到情况2。

**在上面的情况下**，$b$ 数组的所有位置都已经复制到了 $a_k$ 上，那如果我们把 $a_i$ 复制到 $a_k$ 呢？那是不是 $b$ 数组就不用了复制到 $a_i$ 了，因为它们都在 $a_k$ 上。这样的代价是 $a_i$，但我们的总代价又减少了复制到 $a_i$ 上的代价 $sum_b$。于是当 $a_i \leq sum_b$ 时，考虑用情况2。

怎么取 $a_k$ 呢？可以将 $k$ 取 $pos_a$，即 $a_k$ 为 $max_a$。因为这样总代价肯定会更小一点。

Q ： 有没有可能可以先把 $a_i$ 复制到 $b_j$ 上，再把 $b_j$ 复制到 $a_k$ 上呢（即互相复制到对方数组上）？这样上面的做法就考虑不到这种情况了。

A ： 可能，但是这等价于第2种情况，代价也一样。

Q ： 为什么不能将 $a$ 数组复制到 $b$ 数组上呢？

A ： 同理，两种情况取 $\min$ 即可。

于是就做完了。时间复杂度 $O(n)$，绰绰有余。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll long long
	#define pc putchar
	#define fr(i,x,y) for(register ll i=(x);i<=(y);i++)
	#define il inline
	il ll read(){
		ll sum=0,f=1;
		char ch=0;
		while(!isdigit(ch)){
			if(ch=='-') f=-1;
			ch=getchar();
		}
		while(isdigit(ch)){
			sum=sum*10+(ch^48);
			ch=getchar();
		}
		return sum*f;
	}
	il void write(ll x){
		if(x<0){
			x=-x;
			pc('-');
		}
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
}
using namespace my_std;
ll n,m,a[100010],b[100010],maxa=0,posa,maxb=0,posb,suma=0,sumb=0,ans1=0,ans2=0;
//maxa：最大值 posa：最大值的位置 suma：a 数组所有数的和 ans1：把 b 复制到 a 的最小代价 
int main(){
	n=read();
	m=read();
	fr(i,1,n){
		a[i]=read();
		suma+=a[i];
		if(a[i]>maxa){
			maxa=a[i];
			posa=i;
		}
	}
	fr(i,1,m){
		b[i]=read();
		sumb+=b[i];
		if(b[i]>maxb){
			maxb=b[i];
			posb=i;
		}
	}
	fr(i,1,n){//分类讨论
		if(i==posa) ans1+=sumb;//如果 i 已经是最大值的位置了，就不用复制到自己 
		else if(a[i]<=sumb) ans1+=a[i];
		else ans1+=sumb;
	}
	fr(i,1,m){//同理 
		if(i==posb) ans2+=suma;
		else if(b[i]<=suma) ans2+=b[i];
		else ans2+=suma;
	}
	write(min(ans1,ans2));//取最小值 
}
```

---

