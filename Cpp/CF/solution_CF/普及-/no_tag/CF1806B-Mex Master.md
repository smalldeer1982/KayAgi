# Mex Master

## 题目描述

You are given an array $ a $ of length $ n $ . The score of $ a $ is the MEX $ ^{\dagger} $ of $ [a_1+a_2,a_2+a_3,\ldots,a_{n-1}+a_n] $ . Find the minimum score of $ a $ if you are allowed to rearrange elements of $ a $ in any order. Note that you are not required to construct the array $ a $ that achieves the minimum score.

 $ ^{\dagger} $ The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ , and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, it is optimal to rearrange $ a $ as $ [0,0] $ , the score of this array is the MEX of $ [0+0]=[0] $ , which is $ 1 $ .

In the second test case, it is optimal to rearrange $ a $ as $ [0,1,0] $ , the score of this array is the MEX of $ [0+1,1+0]=[1,1] $ , which is $ 0 $ .

## 样例 #1

### 输入

```
3
2
0 0
3
0 0 1
8
1 0 0 0 2 0 3 0```

### 输出

```
1
0
1```

# 题解

## 作者：lichenzhen (赞：3)

## 题目大意
有 $t$ 个长度为 $n$ 的序列，求重新排列后的最小`mex`值。
## 题目解法
一道比较简单的思维题，分情况讨论一下。

我们把序列中 $0$ 的数量定义为 $a_0$，把序列中 $1$ 的数量定义为 $a_1$，$(n+1) \div 2$ 定义为 $b$。

若 $a_0=n$，也就是序列中全部都是 $0$，此时最小`mex`值肯定是 $1$，因为任意两个数字相加结果都是 $0$。

若 $a_0 \le b$，也就是序列中一半或者一少半的数字是 $0$ 时，我们将所有的 $0$ 与一个非零的数放在一起相加，这样序列中的两个数的和全都 大于 $0$ 了，最小`mex`值就是 $0$ 了。

若 $b < a_0 < n$，此时有两种情况：

- 若 $a_0+a_1=n$，也就是序列中只有数字 $0$ 或 $1$，且 $0$ 的数量比 $1$ 多。此时我们把所有的 $1$ 分别与 $0$ 放在一起，无论如何都有剩余的 $1$，所以此时最小`mex`为 $2$。

- 否则，我们把所有非零的数两两结合，$0$ 互相结合，这样就能使最小`mex`值为 $1$ 了。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a0,a1,s;
int main()
{
    cin>>T;
    while(T--){
    	a0=a1=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>s;
            if(s==1) a1++;
            if(s==0) a0++;
        }
        if(a0==n) puts("1");
        else if(a0<=(n+1)/2) puts("0");
        else if(a0+a1==n) puts("2");
        else puts("1");
    }
    return 0;
}
```


---

## 作者：Jorisy (赞：3)

一道分讨。

看到样例，首先考虑 $0$ 的情况。

如果令 $s=\sum\limits_{i=1}^n[a_i=0]$，易得出，当 $s\le\lceil\dfrac{n}{2}\rceil$ 时，我们可以构造 $0,x_1,0,x_2,\cdots$ 或者 $x_1,0,x_2,0,\cdots$ 的序列（$x_i$ 是序列 $a$ 中的元素且 $x_i>0$，下同），来使得其 $\text{mex}=0$。

那如果 $s>\lceil\dfrac{n}{2}\rceil$ 呢？

首先考虑全 $0$，必定为 $1$。

然后考虑到，如果存在 $a_i>1$，那么，我们可以构造 $0,0,\cdots,0,a_i,x_1,x_2,\cdots$ 得到 $\text{mex}=1$。

而剩下的情况，就是 $01$ 序列，输出 $2$ 即可。

赛时 AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int a[200005];

void sol()
{
	int n,s=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],s+=!a[i];//统计 0 个数
	if(n%2==0&&s<=n/2||n%2&&s<=(n+1)/2) puts("0");//0 个数少
	else 
	{
		if(s==n) puts("1");//全 0
		else
		{
			for(int i=1;i<=n;i++)
			{
				if(a[i]>1)
				{
					puts("1");
					return;
				}
			}
			puts("2");//01 序列
		}
	}
}

int main()
{
	int t;
	cin>>t;
	while(t--) sol(); 
 	return 0;
}
```

---

## 作者：0zhouyq (赞：2)

### CF1806B 题解

[传送门](https://www.luogu.com.cn/problem/CF1806B)

### 思路：

能不把两个 $0$ 挨在一起就不要挨在一起。

分类讨论一下就好了。

如果 $0$ 的个数小于等于 $\lfloor \dfrac{n+1}{2}\rfloor$ 的时候，我们可以使 $0$ 都分开来，答案也就是 $0$。

如果 $0$ 的个数等于 $n$ 的时候，答案就是 $1$。

此时我们先把所有 $0$ 都排在序列的前边。

如果有大于 $1$ 的数，就把它接到 $0$ 的后面。此时这个数后面产生的每个参与 mex 运算的数都大于等于 $1+1=2$，所以答案就是 $1$。

如果原序列完全是由 $0$ 和 $1$ 构成的，答案就是 $2$。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll t;
	scanf("%lld",&t);
	while(t--){
		ll n;
		scanf("%lld",&n);
		ll cnt=0,cnt2=0;
		for(ll i=1;i<=n;i++){
			ll x;
			scanf("%lld",&x);
			if(x==0) cnt++;//计算0的个数
			if(x>1) cnt2++;//计算>1的数的个数
		}
		if(cnt<=(n+1)/2) printf("0\n");
		else if(cnt2>0||cnt==n) printf("1\n");
		else printf("2\n");
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

挺水一道结论题，竟然没有题解，所以写一篇吧。

目测难度红到橙？

------------

题意：给定一个长度为 $n$ 的数组，可以以任意顺序排列元素。求出所有排列中每两个相邻元素之和组成的新序列中未出现的最小的非负整数的最小值。

显然，$ans\leq2$。

若没有两个相邻的 $0$，$ans$ 可以取 $0$，此时 $0$ 的个数一定小于等于 $\lceil\frac{n}{2}\rceil$。

若没有 $0$ 和 $1$ 相邻，$ans$ 可以取 $1$，此时一定存在除 $0$ 和 $1$ 以外的数隔开它们。

否则，$ans$ 可以取 $2$，只用将 $0$ 和 $1$ 交替防止，然后剩下全填 $0$ 即可。

还要特判一种情况，不然连样例都过不了，当全为 $0$ 时，$ans=1$。

输出时统计一下 $0$ 和 $1$ 的个数，然后分类讨论答案，此题结束。

------------

这么简单的题应该没人看代码吧
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,cnt0,cnt1;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        cnt0=cnt1=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a);
            cnt0+=a==0;
            cnt1+=a==1;
        }
        if(cnt0<=(n-1)/2+1)
            puts("0");
        else if(cnt0+cnt1<n||cnt0==n)
            puts("1");
        else
            puts("2");
    }
    //tjn&&lyy--1314
    return 0;
}
```


---

## 作者：_5t0_0r2_ (赞：1)

分析：因为 $0$ 和 $1$ 在任何时候都比较特殊，所以我们从它们开始特判。

首先对于答案为 $0$ 的情况，数列应满足不能有两个 $0$ 挨在一起，即 $0$ 的数量比其他数的数量加一要少，满足以下形式：

$[0,a_2,0,a_4,...,0,a_{n - 1},0]$

对于答案为 $1$ 的情况，数列应满足不能有 $0$ 和 $1$ 挨在一起，即要么数列中没有 $1$，要么除了 $0$ 和 $1$，还能有其他数把它们分开。

否则，数列中就只有 $0$ 和 $1$。根据情况 $1$，此时 $0$ 的数量 $1$ 数量加一要要多，所以我们一定可以保证两个 $1$ 不挨到一起。答案就为 $2$。

---

## 作者：Enoch006 (赞：1)

### 题目大意：
给你一个数组，你可以随意排列里面的元素，使得 $[a_1+a_2,a_2+a_3,\ldots,a_{n-1}+a_n]$ 中所有元素中不含有较小的自然数。即 MEX 值。到这里可能有点看不懂，我们来看看样例解释：

一个数组：$[0,0,1]$ 将他随意排序后可以变成 $[0,1,0]$。他的 MEX 数组即为 $[0+1,1+0]=[1,1]$。他没有包含 $0$，也就是说他的 MEX 值为 $0$。

### 题目思路：
1. 当总数减 $0$ 的个数大于等于总数的一半，MEX 值一定为 $0$。若不能理解，请看这个例子：

 若总数为 $2$ 的倍数，极端情况可以构造数组为：

$[0,a_1,0,a_2,\ldots,0,a_{\frac{n}{2} }]$。
MEX 数组即为 $[0+a_1,a_1+0,0+a_2,a_2+0,\ldots,]=[a_1,a_1,a_2,a_2,\ldots,a_{\frac{n}{2} }]$，因为$a_1,a_2,\ldots,a_{\frac{n}{2} }$ 都大于等于 $1$。所以 MEX 值为 $0$

若不为 $2$ 的倍数，在构造数组时在最后添一个 $0$，易得，MEX 值仍然为 $0$。

2. 反之，MEX 值一定不为 $0$，此时要分三种情况。

若数组里面的数全部为 $0$，易得，MEX 值为 $1$。

若数组中的数全部为 $0$ 或 $1$，将每一个 $1$ 放进两个 $0$，里，此时，MEX 值为 $2$。

若是其他情况，可以构造数组：$[0,0,\ldots,0,a_k ,a_{k+1},\ldots,a_p]$。因为我们排除了除 $0$ 之外全是 $1$ 的情况。所以让 $a_k \geqslant 2$，所以MEX 数组即为 $[0,0,\ldots,0,a_k+0,\ldots,a_p+a_{p-1}]$，因为任意两正整数相加一定大于 $1$，所以 MEX 数组为 $[0,0,\ldots,0,\geqslant 2,\ldots,\geqslant 2,\geqslant 2]$。MEX 值为 $1$。

### 题目代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,a[210000],sum,ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		sum=0;
		ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==0){
				sum++;
			}
			if(a[i]==1){
				ans++;
			}
		}
		if((n-sum)>=n/2)cout<<0<<endl;
		else{
			if(sum==n)cout<<1<<endl;
			else if(sum+ans==n)cout<<2<<endl;
			else cout<<1<<endl;
		}
	}
	return 0;
} 
```


---

## 作者：xyta (赞：0)

## 思路
这道题不涉及到任何算法，仅仅就是一道分类讨论的题。

但是我们会发现，$2\le n \le 2\times 10^5$ 并且 $1\le t\le  10^4$，而又因为输入的原因复杂度只能 $O(nt)$ 所以不能完全暴力。

我们可以把数据的情况分为以下几种并求出对应的答案：

- 序列中 $0$ 的个数小于等于序列总长度的一半（奇数自动加一），此时所有不为 $0$ 的数的数量一定大于 $0$ 的数量，这样就可以将每个 $0$ 都和一个不为 $0$ 的数挨着，这样只会出现 $0$ 和不为 $0$ 挨着，或者不为 $0$ 和不为 $0$ 的挨着，这样和永远大于 $0$，所以答案就为 $0$。
- 如果不是第一种方法且有大于 $1$ 的元素，那么答案就是 $1$。因为只需要将 $0$ 都放在最左边，$1$ 都放在最右边，中间隔着一个大于 $1$ 的，这样只会出现 $0$ 和大于 $1$ 的和，所以答案为 $1$ 。
- 再一种就是全为 $0$，很显然这样答案为 $1$ 。
- 剩下的所有情况就都是一个 $0$ 的个数大于总长度一半的 $01$ 字符串了。这样因为 $1$ 的个数小于 $0$ 的个数，所以可以把所有 $1$ 用至少 $1$ 个 $0$ 给隔开，这样只会出现 $0$ 和 $1$ 的和，故答案为 $2$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int main()
{
	int t,n;
	cin>>t;
	while(t--)//多组数据 
	{
		int zero,moreone;//来记录0和大于1的数的数量 
		zero=moreone=0;//初始为0 
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			zero+=(a[i]==0);//判断是否为0，为0加1 
			moreone+=(a[i]>1);//同理，判断是否大于1，大于1加1 
		}
		//第一种情况 
		if(zero<=n/2 and n%2==0) cout<<0<<endl;
		else if(zero<=(n+1)/2 and n%2==1) cout<<0<<endl;
		//if(zero<=(n+1)/2) cout<<0<<endl;
		else if(moreone!=0) cout<<1<<endl;//第二种 
		else if(zero==n) cout<<1<<endl;//第三种 
		else cout<<2<<endl;//剩下的即最后一种 
	}
	return 0;
}
```
完结撒花！

---

## 作者：skyskyCCC (赞：0)

## 前言。
一道比较简单的分类讨论题。
## 分析。
首先我们先统计出非 $0$ 的数有多少个，下文中用 $sum$ 表示，然后统计出为 $0$ 的数有多少个，下文中用 $cut$ 表示。

第一种情况：  
当 $sum$ 大于等于 $cut-1$ 时，此时因为要求最小的权值，所以我们可以将每一个非零数穿插在每两个 $0$ 之间，此时在新序列中，任意两个相邻的数之和都是非零数，没有在新序列中出现的最小整数即为 $0$。

第二种情况：  
当 $sum$ 小于 $cut-1$ 时，此时易证有两个 $0$ 相邻，那就一定在新序列中有至少一个 $0$。  
为了使答案最小，我们可以将所有非零数在同一个区间内以升序相加使其加出来的数尽量大，那此时的答案就在非 $0$ 数与 $0$ 的交界处。在这种情况下，还有两种情况:

- 若存在非零数且所有非零数都是 $1$ 时，注意到我们可以尽可能将 $1$ 穿插到两个 $0$ 之间时更优，新序列交界处就一定为 $0$ 与 $1$ 相接，答案为 $2$。
- 若存在大于 $1$ 的非零数，就将它作为与 $0$ 的分界线，新序列中不存在 $1$ 的结果，此时答案为 $1$。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int t,n,a[200005],pd,pd2,flag;
int main(){
    cin>>t;
    while(t--){
    	pd=pd2=flag=0;
        cin>>n;
        for (int i=1;i<=n;i++){
            cin>>a[i];
            if (a[i]) pd++;
            else pd2++;
            if (a[i]>1) flag=1;
        }
        if (pd>=pd2-1) cout<<"0\n";
        else if (pd&&!flag) cout<<"2\n";
        else cout<<"1\n";
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：inc1ude_c (赞：0)

纯思维题，分类讨论即可。

如果 $0$ 的个数等于 $n$，那么答案就是 $1$。

如果 $0$ 的个数小于等于 $\lceil \frac{n}{2} \rceil $，那么我们将每个 $0$ 与一个非零数配对，这样 $0$ 与非零数相加得出非零数，非零数与非零数相加等于非零数，所以答案为 $0$。

否则，如果剩下的都是 $1$，那么 $0$ 与 $1$ 依次配对后，还会剩下一些 $0$，不得不将它们安排在一起，所以答案是 $2$。

如果都不是这些情况，那么就将序列排成 $0,0,\cdots,0,x,1,1,\cdots,1$，其中 $x$ 是大于 $1$ 的数。此时答案为 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MT int _T;cin>>_T;while(_T--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
int cnt0=0,cnt1=0,n;
int main(){
	MT{
		scanf("%d",&n);cnt0=0;cnt1=0;
		rep(i,1,n){
			int a;scanf("%d",&a);
			if(a==0)cnt0++;
			if(a==1)cnt1++;
		}
		if(cnt0==n)puts("1");
		else if(cnt0<=(n+1)/2)puts("0");
		else if(cnt0+cnt1==n)puts("2");
		else puts("1");
	}
	return 0;
}
```

---

## 作者：庄nnnn额 (赞：0)

### 题目大意
给你一个长为 $n$ 的数组 $a$，请你重排 $a$，让 $\{a_1+a_2,a_2+a_3,\cdots,a_{n-1}+a_n\}$ 的 $\operatorname{mex}$ 值（一个非负整数序列中最小的没有出现的非负整数）最小，并输出这个最小值。多组数据。

### 解题思路
我们分三种情况讨论。
1. $a$ 中的 $0$ 个数小于等于 $\left\lceil\dfrac{n}{2}\right\rceil$。我们可以让任意两个 $0$ 不相邻，这样就没有相邻两数的和等于 $0$，$\operatorname{mex}$ 值就是 $0$，达到最小。
2. $a$ 中的 $0$ 个数大于 $\left\lceil\dfrac{n}{2}\right\rceil$，且至少有一个大于 $1$ 的数。此时我们可以把所有的 $0$ 排在前面，紧接着一个大于 $1$ 的数，剩下的数随便排。这时，有相邻两数的和等于 $0$，但没有相邻两数的和等于 $1$，$\operatorname{mex}$ 值就是 $1$，达到最小。
3. $a$ 中的 $0$ 个数大于 $\left\lceil\dfrac{n}{2}\right\rceil$，且没有一个大于 $1$ 的数。这时数组里只有 $0$ 和 $1$，且 $0$ 比 $1$ 多。我们可以让任意两个 $1$ 不相邻，这样，有相邻两数的和等于 $0$ 和 $1$，但没有相邻两数的和等于 $2$，$\operatorname{mex}$ 值就是 $2$，达到最小。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005];
int main(){
	int tt,n,p;
	bool q;
	scanf("%d",&tt);
	while(tt--){
		scanf("%d",&n),p=q=0;
		for(int i=1;i<=n;i++)scanf("%d",a+i),p+=!a[i],q|=(a[i]>1);
		if(p<=(n+1)/2)printf("0\n");//1
		else if(q)printf("1\n");//2
		else printf(n-p?"2\n":"1\n");//3
	}
	return 0;
}

---

## 作者：隐仞Mrsu (赞：0)

# 题意
给定 $n$ 长的数组 $a$，要求输出该数组的**最小**得分。

求出数组的得分：
- 第一步，可以任意重新排序原数组 $a$；
- 第二步，将排序后的数组构造出新数组 $a_1+a_2,a_2+a_3,\ldots,a_{n-1}+a_n$；
- 第三步，新数组中未出现的**最小非负整数**就是该数组的得分。

# 分析
因为得分为最小非负整数，而不考虑数组的情况下，最小的非负整数为零，所以我们要尽量使得分尽可能接近零。

令 $num_0,num_1,ng_1$ 分别为原数组值为零的个数，值为一的个数，以及值大于一的个数。

### 答案为零
由于新数组各项是排序后的 $a$ 数组中**为邻居的两元素之间的和**，所以要让零在新数组中不出现，需要把原数组的零与正整数做邻居。

当 $num_0 \le \frac{n+1}{2}$ 时，表示有足够的正数与值为零的元素做邻居，从而使零在新数组中未出现，那么答案就为零。

### 答案为一
当不满足答案为零的情况，即值为零的元素过多，那么我们要尽量使得分接近一。

当 $num_1=0$ 时，即在值为零的元素出现了的情况下，值为一的元素没有出现，那么答案就是一。

当 $ng_1>0$ 时，则即便值为一的元素在原数组中出现了，都有比一大的数与一做邻居，使两者加和大于一，在新数组中就不会出现值为一的元素了，所以答案也是一。

### 答案为二
当都不满足上述情况，答案就是二，构造不出更大的答案了。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e6+6;
LL _,n,a[N];
void work(){
	cin>>n;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
	}
	LL num0=0,num1=0,ng1=0;
	for(LL i=1;i<=n;i++){
		num0+=(a[i]==0);
		num1+=(a[i]==1);
		ng1+=(a[i]>1); 
	}
	if(num0<=(n+1)/2){
		cout<<"0\n";
		return;
	}
	if(!num1){
		cout<<"1\n";
		return;
	}
	if(ng1){
		cout<<"1\n";
		return;
	}
	else{
		cout<<"2\n";
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
}
```


---

## 作者：SlyCharlotte (赞：0)

# 题意描述

给你你个长度为 $n$ 的序列，你需要对其重新排序，使得相邻两数相加构成的序列的 `mex` 最小。



# 简要分析

观察到只要 $0$ 的个数小于 $\lceil \frac n 2 \rceil$ 时答案总是 $0$，我们只需要将每个 $0$ 放在两个正数之间即可。

对于答案等于 $1$ 的情况，我们只需将 $1$ 放在 $1$ 或比 $1$ 大的数旁边即可，注意序列中全部为 $0$ 也是答案等于 $1$ 的情况。

剩余情况答案总是等于 $2$。

# 代码实现

```cpp
void solve() {
  	int n;
	cin>>n;
	int sum0=0;
	bool f=false;
    for(int i=1;i<=n;i++) {
		int x;
		cin>>x;
		if(x==0) {
			sum0++;
		} else if(x>=2) {
			f=true;
		}
	}
	if(sum0<=(n+1)/2) {
		cout<<"0\n";
	} else if(f||sum0==n) {
		cout<<"1\n";
	} else {
		cout<<"2\n";
	}
}
```



---

## 作者：RandomLife (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1806B)

### 题意

给定长度为 $n$ 的数列 $a$，求 $a$ 排列后最小的 $mex(a_1+a_2,a_2+a_3,...,a_{n-1}+a_n)$。$(2 \leq n \leq 2 \cdot 10^5,0 \leq a_i \leq 2 \cdot 10^5)$

### Solution

先统计出数组中非 $0$ 的数有 $x$ 个，$0$ 有 $y$ 个。

我们可以分为两种情况：

1. $x \geq y-1$ 时，我们可以用所有非 $0$ 的数隔开所有的 $0$，使得任意两个相邻的数之和大于 $0$，此时答案为 $0$。

2. $x < y-1$ 时，必然有两个 $0$ 相邻，则集合中必然存在 $0$。为了使答案尽量小，我们可以将所有非 $0$ 的数聚在一块，这样和最大。那么，决定结果的位置在于非 $0$ 数与 $0$ 的交界处。此时还能分成两种情况：

	1. 所有非 $0$ 的数都为 $1$ 且 $x>0$，此时交界处一定为 $1$ 和 $0$，那么答案为 $2$。
    
    2. 如果存在大于 $1$ 的数，就将它作为与 $0$ 的交界处，则集合中不存在 $1$，答案为 $1$。
    
### AC code

```c++
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <string.h>
#include <vector>
#include <math.h>
#include <stdio.h>
using namespace std;
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n, cnt1 = 0, cnt2 = 0;
        bool flag = true;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            int a;
            cin >> a;
            if (a) {
                cnt1++;
            } else {
                cnt2++;
            }
            if (a > 1) {
                flag = false;
            }
        }
        if (cnt1 >= cnt2 - 1) {
            cout << 0 << endl;
        } else if (cnt1 && flag) {
            cout << 2 << endl;
        } else {
            cout << 1 << endl;
        }
    }
    return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

水题一个，但是我赛时把 `<=` 写成 `==`，还写错一个分类，痛失 rating……

## 思路

对于每组数据，统计每个数字出现的次数，再分类每种情况：

- 当数组中所有数都为 $0$，答案肯定为 $1$。

- 当数组中小于一半（向上取整）的数为 $0$ 时，把所有 $0$ 都分散开来，答案为 $0$。

- 当数组中全是 $0$ 和 $1$ 时（$0$ 的个数加 $1$ 的个数等于 $n$），将所有 $1$ 分散开来，插在 $0$ 的空子里，因为 $0$ 的个数大于 $\lceil n \div 2 \rceil$，所以此时构造出的数组，只有 $0$ 和 $1$，故答案为 $2$。

- 剩下情况，都将非 $0$ 的数聚集在边缘，与 $0$ 相接的部分用一个非 $1$ 的数，答案为 $1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010], cnt[200010];
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		memset(cnt, 0, sizeof(cnt));
		int n;
		scanf("%d",&n);
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			cnt[a[i]]++;
		}
		if(cnt[0] == n){
			puts("1");
		}else if(cnt[0] <= ceil(1.0 * n / 2)){
			puts("0");
		}else if(cnt[0] + cnt[1] == n){
			puts("2");
		}else{
			puts("1");
		}
	}
	return 0;
}
```

---

