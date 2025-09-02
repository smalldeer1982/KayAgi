# Perfect Permutation

## 题目描述

You are given a positive integer $ n $ .

The weight of a permutation $ p_1, p_2, \ldots, p_n $ is the number of indices $ 1\le i\le n $ such that $ i $ divides $ p_i $ . Find a permutation $ p_1,p_2,\dots, p_n $ with the minimum possible weight (among all permutations of length $ n $ ).

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the only valid permutation is $ p=[1] $ . Its weight is $ 1 $ .

In the second test case, one possible answer is the permutation $ p=[2,1,4,3] $ . One can check that $ 1 $ divides $ p_1 $ and $ i $ does not divide $ p_i $ for $ i=2,3,4 $ , so the weight of this permutation is $ 1 $ . It is impossible to find a permutation of length $ 4 $ with a strictly smaller weight.

## 样例 #1

### 输入

```
2
1
4```

### 输出

```
1
2 1 4 3```

# 题解

## 作者：diqiuyi (赞：3)

修改了一些错误。

[题目传送门](https://www.luogu.com.cn/problem/CF1711A)

**题意**

有多组数据，每组数据给定一个正整数 $n$，求 $n$ 的排列 $p$ 中，$\sum [p_i\mid i]$ 的最小值，输出这个排列。

**思路**

可以考虑一种构造方式，使得 $p_i=i+1$，显然 $p_i \nmid i$。

此时 $p_n=1$，所以答案就是 $1$。

因为 $1$ 整除任意正整数，所以答案的最小值就是 $1$。

**另一种思路**

考虑到当 $i \ge 2$ 时，$2i-1 \nmid 2i$，且对于任意的 $i$，都有 $2i \nmid 2i-1$。

于是，就衍生出了另一种做法，即当 $n$ 为偶数时，就交换相邻的两数。

当 $n$ 为奇数时，显然有 $n \nmid 2$，因此可以令 $p_n=2$，$p_1=n$，$p_2=1$，此时答案仍然是 $1$。

此时注意特判 $n=1$ 的情况。

**CODE**

太短了就不放了吧。

---

## 作者：shenyiran (赞：2)

### 题目描述
给你一个长度为 $n$ 的序列，$p_i$ 的值为 $i$。对这个序列重新构造使满足 $p_i\bmod i=0$ 的数量最少。
### 思路
因为任何数正整数模 $1$ 的值都是 $0$，所以关键在于后面的 $n-1$ 个数。我们可以想到用偶数来模奇数，这样模数不可能为 $0$，反之亦然。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n-1;i++){
			printf("%d ",i+1);//输出它+1的数，使得他们不满足条件
		}
		printf("1 ");//最后处理
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：sw2022 (赞：2)

## 题意简析

给定一个排列 $a\ (|a|=n,n>0)$ 的长度 $n$，定义一个排列的权值为排列中能被序号整除的元素数量，构造一个有最小权值的排列。

显然，对于序号为 $1$ 的元素，无论元素值为多少都能被序号整除。所以只要保证剩余元素都不能被它们对应的序号整除，以顺序排列为初始排列，然后按照顺序进行操作即可。以下给出两种方法，都用到了任意两相邻整数互质的性质使得所有序号大于 $1$ 的元素都无法被他们的序号整除。

## 代码/解释
### 方法一：调换法
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,i;
    cin>>t;
    while(t--)
    {
        cin>>n;
        if(n%2)
        {
            printf("1 ");//占位
            for(i=1;i<n;i+=2)
            printf("%d %d ",i+2,i+1);//将接下来的两个元素互换位置
        }
        else for(i=0;i<n;i+=2)
        printf("%d %d ",i+2,i+1);//同上
        cout<<endl;
    }
    return 0;
}
```
### 方法二：错位法
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,i;
    cin>>t;
    while(t--)
    {
        cin>>n;
        printf("%d",n);//占位
        for(i=1;i<n;i++)
        printf(" %d",i);//剩余元素从原来的位置后移一格
        cout<<endl;
    }
    return 0;
}

---

## 作者：arkerny (赞：1)

## 解题思路：

题意明确，对于一个长度为 $n$ 的排列，构造出使其权重最小的排列。

关于权重的定义如下：

$$
\sum^{n}_{i=1} {p_i | i}
$$

其中 $p_i | i$ 表示 $p_i | i$ 时 $p_i \div i$ 的值。

显然易得：

当 $i$ 的值为 $1$ 时，无论 $p_i$ 为多少都能被 $i$ 整除。

根据任意两相邻整数互质可得：

将元素错位排列以后，所得的权重最小，以下代码给出了一种解决方案。

## 代码：

``` cpp
#include<bits/stdc++.h>
using namespace std;

int T,n;

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%d ",n);
        for(int i=1;i<n;i++)
        {
            printf("%d ",i);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Shimotsuki (赞：1)

题意：一个排列的定义如下：

- 该排列的数字必须小于等于排列的长度 $n$

- 该排列的数字必须从包含小于等于 $n$ 的所有元素

一个排列的权值定义：$\sum_{i=1}^{n}[p_i \mid i]$

给定 $n$，求权值最小的排列。

思路：显然，每个排列的最小权值都至少是 $1$，因为 $1$ 可以被任何整数整除。考虑构造一个权值为 $1$ 的排列：因为互质的数中的一方无法被另外一方整除，所有可以将奇数下标位置上的数字赋值为相邻的偶数下标，偶数下标同理。当 $n$ 为奇数时，这种方案可构造出最小权值排列。当 $n$ 为奇数时，我们可以将 $p_n$ 赋值为 $1$，将 $p_2$ 赋值为 $n$，其他按照原方案执行，这样保证了权值为 $1$。

代码很好写就不放了。

---

## 作者：封禁用户 (赞：1)

# 1.0 [题目传送门](https://www.luogu.com.cn/problem/CF1711A)
# 2.0 思路
这是一道~~毒瘤~~经典的构造题。
## 2.1 构造
首先我们可以肯定的是，任意正整数都可以被 $1$ 整除，所以第一个位置填任意小于等于 $n$ 的正整数都行。

所以我们将第一个数设为 $n$，然后接下来 $n-1$ 个数设为 $1,2,3 \cdots n-1$，这样可以得到 $1 \mid n,2 \nmid 1,3 \nmid 2 \cdots n \nmid n-1$，所以重量为 $1$，且满足是 $n$ 的排列这一条件，显然这是最优解。构造完毕。

## 2.2 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;//多组测试数据 
	while(t--){
		cin>>n;
		cout<<n<<" ";//n放在第一位 
		for(int i=1;i<=n-1;i++){
			cout<<i<<" ";//构造全排列 ，这样保证weight=1 ，是最优解 
		}
		cout<<endl;//注意换行（本蒟蒻在这里挂了，罚时吃饱） 
	}
	return 0;
} 
```


# 3.0 总结
对于这一类的构造题，我们可以从最小的情况入手，然后慢慢推，直到推出一个最优结果，类似于贪心的策略。这样构造题就能被轻易解决。

# 4.0 最后，大佬们既然看都看了，给个赞再走呗~

---

## 作者：Jeremiahy (赞：0)

## 题意

构造一个长度为 $n$ 的序列 $a$（$1\le a_i\le n$），$a$ 中元素互不相同。使得 $a_i$ 能被 $i$ 整除的数量最少。

# 分析

序号为 $1$ 时，$a_1$ 总会被整除，我们只需要去考虑以后的。根据一种性质：相邻的两个数互质，我们可以想到如下构造方法：

将 $a_i$ 赋值为 $i+1$，而 $a_n$ 为 $1$，来保证除 $a_1$ 外 $a$ 序列中其他数都不能被 $i$ 整除。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
signed main() {
    cin >> t;
    while(t--) {
        cin >> n;
        for (register int i = 2; i <= n; i++)//a[i] 为 i+1
        	cout << i << ' ';
        puts("1");//a[n] 为 1
    }
    return 0;
}
```

#### 习题

下面这道题同样利用了这种性质：

[P5436 【XR-2】缘分](https://www.luogu.com.cn/problem/P5436)

---

## 作者：_Ad_Astra_ (赞：0)

一道很好的~~脑筋急转弯~~构造+数论题。

首先我们知道任何数都可以被 $1$ 整除，所以 $p_1$ 不论是哪个数都会产生贡献。那么我们需要尽可能使得剩下的数的贡献最小化。由于相邻的两个数互质，所以我们可以尽可能让剩下来的 $p_2$ 到 $p_n$ 等于相邻的数。

由此就可以产生一种构造方案：$p_1 = n$ ，对于剩下来的 $2 \le i \le n$，$p_i = i-1$，这样总贡献只有 $p_1$ 贡献的 $1$。

复杂度 $O(n)$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cout<<n<<" ";
		for(int i=1;i<n;i++)cout<<i<<" ";
		cout<<endl;
	}
	return 0;
} 
```

---

## 作者：qip101 (赞：0)

**Solution：**

对于任意的一个排列，显然其权值最小为一。

对于一个数，只需要输出其加一即不会增加权值。

于是便构造出如下排列。

**Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main()
{
	cin >> T;
	while(T--)
	{
		int n;
		cin >> n;
		cout << n << endl;
		for(int i=1;i<n;i++)
			cout << i << " ";
		cout<<endl;
	}
	return 0;
}

```



---

## 作者：Failure_Terminator (赞：0)

## Problem

给定一个整数 $n$，构造一个长度为 $n$ 的排列（即长度为 $n$ 且正好由 $1 \sim n$ 组成，不重复的序列），使其权重最小。

## Solution

数列的权重至少为 $1$，因为 $1$ 能被任何整数整除。

对于满足 $q \ge 2$ 的整数，$q+1$ 一定无法被 $q$ 整除。

因此，$[n,1,2,...n-1]$ 是一个合法的构造，且权重为 $1$，达到最小。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9')if(c=='-'){nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<3)+(now<<1)+(c&15);c=getchar();}
	return now*nev;
}
int main()
{
	int t=read();
	while(t--){
		int n=read();
		printf("%d ",n);
		for(int i=1;i<n;i++)
			printf("%d ",i); 
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：zhicheng (赞：0)

### 思路

首先，对于 $p_1$，$1$ 一定能整除任何数，因此这个数列的“重量”至少为 $1$。 然后我们就要最小化后面的增量。而最简单的一种方法就是在 $p_i$ 的地方放 $i-1$。这样我们就能保证 $p_i$ 一定比下标 $i$ 小 $(2 \leq i \leq n)$，所以 $i$ 一定不能整除 $p_i$。最后还剩一个 $n$，我们就在第一个输出它。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a;
	scanf("%d",&a);
	while(a--){
		scanf("%d",&n);
		printf("%d ",n);   //先输出
		for(int i=1;i<=n-1;i++){
			printf("%d ",i);  //依次输出比下标少一的数。
		}
		printf("\n");
	}
}
```

---

## 作者：Scorilon (赞：0)

### 题意

给定一个正整数 $n$，构造一个排列（一个长度为 $n$ 的序列，其中由 $1 \sim n$ 构成，不重复）使其权重最小。

### 思路

既然要使权重最小，那么就让每一个位置 $i$ 上的元素为 $i+1$ 或 $i-1$，且保证不重复（开个数组记重），可以证明当 $i$ 大于等于 $2$ 时，$i-1 \perp i$ 且 $i+1 \perp i$。

那么就特判一下当 $n=1$ 的情况，剩下情况如上构造。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int t;
int n;
int vis[100005];//判重

int main()
{
	scanf("%d",&t);
	
	while(t--)
	{
		memset(vis,0,sizeof(vis));//记得初始化！！
		
		scanf("%d",&n);
		
		if(n==1)//特判1
		{
			puts("1");
			continue;
		}
		
		for(register int i=1;i<=n;i++)
		{
			if(!vis[i+1]&&i+1<=n)//未使用且不越界
			{
				printf("%d ",i+1);
				vis[i+1]=1;
				continue;
			}
			if(!vis[i-1]&&i-1>=1)//未使用且不越界
			{
				printf("%d ",i-1);
				vis[i-1]=1;
				continue;
			}
			if(!vis[1])//最后肯定会剩一个为1
			{
				printf("1 ");
				vis[1]=1;
			}
		}
		
		printf("\n");
	}
	
	return 0;
} 
```


---

## 作者：__KrNalty__ (赞：0)

### 题意简述：

给你一个正整数 $n$， 你需要构造出一个 $1 \dots n$ 的排列 $p_1, p_2, \dots,p_n$。使得对于所有的 $1 \leq i \leq n$，$p_i$ 能被 $i$ 整除的数量最少。

### 思路简述：

首先我们需要明确，相邻的两个大于 $1$ 的正整数是互质的，并且所有正整数都能被 $1$ 整除。所以最少的数量永远是 $1$。

然后进行分类讨论：

- 如果 $n$ 是偶数，那么只需要交换两个相邻的正整数输出即可。

这种情况的代码如下：

```cpp
for (int i = 1; i <= n; i++) {
	if (i % 2 == 1) {
		cout << i + 1 << " ";
	} else {
		cout << i - 1 << " ";
	}
}
```
- 如果 $n$ 是奇数，那么当 $i=1$ 时输出 $1$，剩下的就可以当做 $n$ 为偶数的情况，即交换相邻两个正整数。

这种情况的代码：

```cpp
cout << 1 << " ";
for (int i = 2; i <= n; i++) {
	if (i % 2 == 0) {
		cout << i + 1 << " ";
	} else {
		cout << i - 1 << " ";
	}
}
```

---

