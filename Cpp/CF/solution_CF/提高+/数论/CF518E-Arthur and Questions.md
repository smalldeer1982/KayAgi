# Arthur and Questions

## 题目描述

After bracket sequences Arthur took up number theory. He has got a new favorite sequence of length $ n $ ( $ a_{1},a_{2},...,a_{n}) $ , consisting of integers and integer $ k $ , not exceeding $ n $ .

This sequence had the following property: if you write out the sums of all its segments consisting of $ k $ consecutive elements $ (a_{1} + a_{2} ... + a_{k}, a_{2} + a_{3} + ... + a_{k+1}, ..., a_{n-k+1} + a_{n-k+2} + ... + a_{n}) $ , then those numbers will form strictly increasing sequence.

For example, for the following sample: $ n=5, k=3, a=(1, 2, 4, 5, 6) $ the sequence of numbers will look as follows: ( $ 1 + 2 + 4, 2 + 4 + 5, 4 + 5 + 6 $ ) = ( $ 7, 11, 15 $ ), that means that sequence $ a $ meets the described property.

Obviously the sequence of sums will have $ n-k+1 $ elements.

Somebody (we won't say who) replaced some numbers in Arthur's sequence by question marks (if this number is replaced, it is replaced by exactly one question mark). We need to restore the sequence so that it meets the required property and also minimize the sum $ |a_{i}| $ , where $ |a_{i}| $ is the absolute value of $ a_{i} $ .

## 样例 #1

### 输入

```
3 2
? 1 2
```

### 输出

```
0 1 2 
```

## 样例 #2

### 输入

```
5 1
-10 -9 ? -7 -6
```

### 输出

```
-10 -9 -8 -7 -6 
```

## 样例 #3

### 输入

```
5 3
4 6 7 2 9
```

### 输出

```
Incorrect sequence
```

# 题解

## 作者：yyandy (赞：2)

[**题目链接**](https://www.luogu.com.cn/problem/CF518E) 
## 思路
首先连续区间的和递增，这不太好计算，所以应当转换为一些数之间的关系。   
设数列 $a$ 为符合条件的数列，$p_i$ 为第 $i$ 个连续区间的和，连续区间长度为 $k$。   
则  
$p_1=a_1+a_2+\cdots+a_k$   
$p_2=a_2+a_3+\cdots+a_{k+1}$  
$\cdots$  
$p_{n-k+1}=a_{n-k+1}+a_{n-k+2}+\cdots+a_n$  
$p_1<p_2<p_3<\cdots<p_{n-k+1}$  
移项可得  
$a_1<a_{k+1}<a_{2 \times k+1}< \cdots $  
$a_2<a_{k+2}<a_{2 \times k+2}< \cdots $  
$\cdots$  
$a_{k-1}<a_{2 \times k-1}<a_{3 \times k-1}< \cdots $   
于是我们构造的数列就需要满足这 $k$ 组关系，而这显然很容易构造。  
不过题目要求 $\mid a_i \mid$ 最小，这就有一点麻烦了，首先要判断是否合法。    
如果合法，那么可以分成下面几类。  
**前一个确定数字是非负数，后一个数字是非负数。**  
那么就从前一个确定数字位置后面一个位置位开始填，每填一个格子填入的值加上 $1$。  
**前一个确定数字是负数，后一个数字是负数。**  
那么就从后一个位置前面一个位置开始填，每填一个格子填入的值减去 $1$。  
**前一个确定数字是负数，后一个数字是非负数。**  
那么中间一定要填 $0$，要先找到 $0$ 的位置。  
对于一般情况，$0$ 在最中间的位置，如下图。  
![](https://cdn.luogu.com.cn/upload/image_hosting/blq72hpa.png)   
但是有些情况，如果 $0$ 在中间时填不下，就要适当调整 $0$ 的位置，如图。   
![](https://cdn.luogu.com.cn/upload/image_hosting/j8tivclj.png)   
这样就完成了，不过为了方便实现，我在数列最前面加上一个极小的数，最后面加上了一个极大的数。  
其他应该问题不大了，具体实现见代码。   
## Code  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[1200000],i,j,kk,p[1200000],e,lst,s,pl[1200000];
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		if(ch=='?')
			return 2e9+1;//为了方便?的值是2e9+1
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int main() {
	cin>>n>>k;

	for(i=1; i<=n; ++i)
		a[i]=read();
	for(i=1; i<=k; ++i) {//k组关系
		s=i;
		e=0;
		lst=0;
		while (s<=n) {
			p[++e]=a[s];
			if(p[e]!=2e9+1)pl[e]=lst,lst=e;//找出上一个确定的数
			s+=k;
		}
		p[0]=-2e9-2;
		p[e+1]=2e9+2;
		pl[e+1]=lst;//加入极大的数和极小的数
		for(j=1; j<=e+1; ++j) {
			if(p[j]!=2e9+1) {//
				if(p[j]-p[pl[j]]<j-pl[j]) {
					cout<<"Incorrect sequence";
					return 0;
					//判断是否合法
				}
				if(p[j]>=0&&p[pl[j]]>=0) {
					for(kk=pl[j]+1; kk<j; ++kk)
						p[kk]=p[pl[j]]+kk-pl[j];
					//均为非负数
				} else if(p[j]<0&&p[pl[j]]<0) {
					for(kk=j-1; kk>pl[j]; --kk)
						p[kk]=p[j]-j+kk;
					//均为负数
				} else {
					int mid=(pl[j]+j)>>1;
					if(mid-pl[j]>=-p[pl[j]])
						mid=pl[j]-p[pl[j]];//调整0的位置
					if(j-mid>p[j])
						mid=j-p[j];//调整0的位置
					for(kk=j-1; kk>pl[j]; --kk)
						p[kk]=kk-mid;
					//一个负数，一个非负数
				}
			}
		}
		for(j=1; j<=e; ++j)
			if(p[j]<=p[j-1]||p[j]>2e9||p[j]<-2e9) {
				cout<<"Incorrect sequence";
				return 0;
				//这个其实是用来保险的，防止有不合法情况出现
			} else
				a[(j-1)*k+i]=p[j];//填回去
	}
	for(i=1; i<=n; ++i)
		printf("%lld ",a[i]);
}
```

如果代码有什么问题或者思路有什么问题，请指正。

---

## 作者：BYR_KKK (赞：1)

duel 到的，对面过了以后不 judge，愤怒。

手模一下区间的移动，可以发现存在形如 $a_i\ge a_{i-k}$ 的关系。于是只考虑这些同余类，按照**给定的数**作为间隔来填未知的数。显然**每段填的数都是连续的**。

设上一个给定的数为 $x$，现在给定的数为 $y$，去填中间没有给定的 $s$ 的个数。如果无论怎么填都无法使这 $s$ 个合法，则无解。否则考虑使填的绝对值最小。当 $y\le 0$ 时，必然是填尽量大的数；当 $y>0$ 时，尽量填 $0$ 两边的数，此时 $0$ 的最佳填放位置就是 $\lceil\dfrac{s}{2}\rceil$，但是如果填在这以后前面或者后面不符合要求就要进行一定的微调，这并不困难。

最后判断一下填完以后的数是否合法即可，时间复杂度 $O(n)$。

---

