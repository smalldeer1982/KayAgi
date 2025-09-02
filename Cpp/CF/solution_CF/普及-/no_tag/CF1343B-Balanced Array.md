# Balanced Array

## 题目描述

You are given a positive integer $ n $ , it is guaranteed that $ n $ is even (i.e. divisible by $ 2 $ ).

You want to construct the array $ a $ of length $ n $ such that:

- The first $ \frac{n}{2} $ elements of $ a $ are even (divisible by $ 2 $ );
- the second $ \frac{n}{2} $ elements of $ a $ are odd (not divisible by $ 2 $ );
- all elements of $ a $ are distinct and positive;
- the sum of the first half equals to the sum of the second half ( $ \sum\limits_{i=1}^{\frac{n}{2}} a_i =         \sum\limits_{i=\frac{n}{2} + 1}^{n} a_i $ ).

If there are multiple answers, you can print any. It is not guaranteed that the answer exists.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2
4
6
8
10```

### 输出

```
NO
YES
2 4 1 5
NO
YES
2 4 6 8 1 3 5 11
NO```

# 题解

## 作者：PersistentLife (赞：5)

如果 $\LaTeX$ 炸了的话请到我的[博客](https://www.luogu.com.cn/blog/302837/solution-cf1343b)查看。

----------------

我们要构造一个长度为 $n$ 且左右两边相等的序列。

但是，前一半为偶数后一半为奇数，怎么办呢？

观察样例发现，后一半的每一个奇数和对应的前一半的偶数都相差 $1$，最后一个数把差值补回来即可。

但什么情况无解呢？

仔细看看样例，当 $\dfrac{n}{2}\%2=1$ 时，无解。

下面是对于无解的证明：

-----------------

法一：

$\because$ $\dfrac{n}{2}\%2=1$ 。

$\therefore$ 左右两边均有奇数个数 。

$\therefore$ 左边和为偶数，右边和为奇数 。

$\because$ 奇数 $≠$ 偶数 。

$\therefore$ $\dfrac{n}{2}\%2=1$ 时无解 。

----------------

法二：

$\because$ $\dfrac{n}{2}\%2=1$ 。

$\therefore$ 左右两边均有奇数个数 。

$\therefore$ 最后一个数要补回来的差值为奇数 。

$\because$ 奇数 $+$ 奇数 $=$ 偶数 。

$\therefore$ 构成的序列不符合要求 。

$\therefore$ $\dfrac{n}{2}\%2=1$ 时无解 。

----------------

咱们来看一下代码：

首先，我们读入每一个 $n$ 后做一个判断，即是否满足 $\dfrac{n}{2}\%2=1$，如果满足的话直接输出 `NO`。

```cpp
int n;
cin>>n;
if((n/2)%2==1)
{
	cout<<"NO"<<endl;
	continue;
}
```

接着，我们输出 `YES` 后开始构造序列，先输出 $\dfrac{n}{2}$ 个连续的偶数，即 $2,4,6,8,...,n-2,n$。

```cpp
cout<<"YES"<<endl;
for(int i=2,j=1;j<=n/2;j++,i+=2) cout<<i<<" ";
```

然后，我们输出 $\dfrac{n}{2}-1$ 个连续奇数，即 $1,3,5,...,n-5,n-3$，最后一个数加上 $\dfrac{n}{2}$，即补上之前的差值。

```cpp
for(int i=1,j=1;j<=n/2;j++,i+=2)
{
	if(j==n/2) i+=(n/2);
	cout<<i<<" "; 
}
cout<<endl;//记得加换行
```
最后，献上完整代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		if((n/2)%2==1)
		{
			cout<<"NO"<<endl;
			continue;
		}
		cout<<"YES"<<endl;
		for(int i=2,j=1;j<=n/2;j++,i+=2) cout<<i<<" ";
		for(int i=1,j=1;j<=n/2;j++,i+=2)
		{
			if(j==n/2) i+=(n/2);
			cout<<i<<" "; 
		}
		cout<<endl;
	}
}
```


---

## 作者：zhzzhzzzz (赞：4)

CF的AB都是看样例找规律呗

样例比较良心~~一直都很良心~~，可以直接得出 $n\%4\space!=0$ 时，直接输出 $NO$。
那么剩下的就是构造答案序列了。

同样的，根据题意，先来 $\frac{n}{2}$ 个连续偶数，再来 $\frac{n}{2}$ 个连续奇数。

但我们知道，偶数总是比奇数大一，所以在最后一个奇数上补上 $\frac{n}{2}$ 的差值就行了。具体详细的证明请去别楼QAQ

简洁的code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    scanf("%d", &T);
    while (~--T)
    {
        int n;
        scanf("%d", &n);
        if (n % 4 != 0)
        {
            puts("NO");
            continue;
        }
        else
        {
            puts("YES");
            for (int i = 1, x = 2; i <= n / 2; i++, x += 2)
                printf("%d ", x);
            for (int i = 1, x = 1; i <= n / 2 - 1; i++, x += 2)
                printf("%d ", x);
            printf("%d\n", n - 1 + n / 2);//这里的 n - 1 就很好想了
        }
    }
    return 0;
}
```
~~多刷CF有益于身体健康~~

---

## 作者：_jimmywang_ (赞：3)

首先，我们要发现一个规律：当$n$%$4$不是$0$时绝对$NO$

很简单：因为如果$n$%$4$不是$0$，那就是$2$，就是每边有奇数个。

那么，左边的和是偶数，右边的是奇数，好，$NO$了

那$n$%$4$是$0$呢？

反正任意一种情况，左半边直接$2,4,6,8,10……$去了，右半边就$1,3,5,7,9……$就行了。

但是，左半边每个数会比右半边大$1$,总共就差了$n/2$了。。。

那就在右半边的最后一个数上加$n/2$不就行了？反正$n$%$4$是$0$，$n/2$是个偶数。

于是，就完了。。。

```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll t;
int main(){
    t=d;
    while(t--){
        ll n=d;
        if(n%4!=0)cout<<"NO\n";
        else {
            ll sum=0;
            cout<<"YES\n";
            f(i,1,n/2)cout<<i*2<<" ";
            f(i,1,n/2-1)cout<<i*2-1<<" ";
            cout<<n-1+n/2<<endl;
        }
    }
    return 0;
}


```


---

## 作者：Sora1336 (赞：2)

这道题可以将前 $\frac{n}{2}$ 个数的和（即$2,4,6,8,10...n$）存起来，最后令后$\frac{n}{2}-1$个数（即$1,3,5,7,9...n-3$）的和减去前 $\frac{n}{2}$ 个数的和，得到第 $n$ 个数的值。而且另外地，如果$\frac{n}{2} \bmod 2=1$直接输出 NO 。

$Code:$

```
#include <iostream>
using namespace std;
int main() {
	int t;
	cin>>t;
	for(int i=1; i<=t; i++) {
		int n;
		cin>>n;
		if((n/2)%2==1) {			//特判
			cout<<"NO"<<endl;
		} else {
			int ans=0,aans=0;
			cout<<"YES"<<endl;
			for(int j=2; j<=n; j+=2) {			//偶数
				cout<<j<<' ';
				ans+=j;						//累加
			}
			for(int j=1; j<=n; j+=2) {
				if(n<=j+1)
					cout<<ans-aans<<endl;		//第n个数的值
				else {
					cout<<j<<' ';				//奇数
					aans+=j;
				}
			}
		}
	}
}
```


---

## 作者：andyli (赞：2)

题意：  

给出正偶数 $n$，你想要构造一个长度为 $n$ 的序列 $a$ 使得：  
- $\forall i \in \left[1,\frac{n}{2}\right], 2 \mid a_i$
- $\forall i \in \left[\frac{n}{2}+1, n\right], \left. 2 \nmid a_i\right.$
- 所有 $a_i$ 均不相同且为正整数
- $\sum\limits_{i=1}^{\frac{n}{2}} a_i = \sum\limits_{i=\frac{n}{2} + 1}^{n} a_i$

若存在，则输出 `YES` 并在接下来一行输出序列 $a$ ，否则输出 `NO`。  

$2\leq n\leq 2\times 10^5, 1\leq a_i\leq 10^9$。  

分析：  

当 $4\mid n$ 时有解，否则无解。  
有解时，$\forall i\in \left[1,\frac{n}{2}\right], a_i=2i$，$\forall i \in\left[\frac{n}{2}+1, n-1\right], a_i=2(i-\frac{n}{2})-1, a_n=\dfrac{3}{2}n-1$ 即可。  

时间复杂度 $\mathcal O(n)$。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        if (n % 4) {
            writeln("NO");
            continue;
        }
        writeln("YES");
        for (int i = 1; i <= (n >> 1); i++)
            io.write(i << 1, " ");
        for (int i = (n >> 1) + 1; i < n; i++)
            io.write((i << 1) - n - 1, " ");
        writeln((n >> 1) * 3 - 1);
    }
    return 0;
}
```

---

## 作者：lory1608 (赞：1)

这题比较简单，看到样例就知道$std$如何构造的。

对于$(n/2)\%2==1$的数，是不可能实现的，因为此时有奇数个奇数，奇数和为奇数，偶数和为偶数，显然不成立。

对于$n\%4==0$的数，可以成立，具体构造方式看代码。

复杂度$\Theta(Tn)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int getint()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return f?x:-x;
}
int main()
{
	int T,n;
	T=getint();
	while(T--)
	{
		n=getint();
		if((n/2)%2)printf("NO\n");
		else
		{
			printf("YES\n");
			int sum=0;
			for(int i=1;i<=n/2;++i)printf("%d ",i*2),sum+=i*2;
			for(int i=1;i<=n/2-1;++i)printf("%d ",i*2-1),sum-=i*2-1;
			printf("%d\n",sum);
		}
	}
	return 0;
}

```

---

## 作者：Cult_style (赞：1)

题目大意：给定一个偶数n，要使它的左半边全是偶数，右半边全是奇数，并且左半边偶数和要等于右半边奇数和。

思路：先把左半边的偶数凑出来，2、4、6、8、10······这样按顺序输出，用sum数组存住左半边全部数的和，再输出右半边前n/2-1个数，也是1、3、5、6、9······这样输出，但最后一个先不输出，也用一个cnt数组存着右半边,输出sum-cnt，这样可以保证左半边的数之和与右半边的数之和相等。

献上代码：

```
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%d",&n);
		n/=2;
		if(n%2==0){
			printf("YES\n");
			int sum=0;
			for(int i=2;i<=2*n;i+=2){
				printf("%d ",i);
				sum+=i;
			}
			int cnt=0;
			for(int i=1;i<=2*n-2;i+=2){
				printf("%d ",i);
				cnt+=i;
			}
			printf("%d ",sum-cnt);
			printf("\n");
		}
		else
			printf("NO\n");
	}
	
	return 0;
}
```


---

## 作者：CSP_Sept (赞：1)

### 题意简述

给定 $n(n\bmod 2=0)$，要求构造一个长度为 $n$ 的数列 $\{a_n\}$，使其满足以下条件：

- 前 $\dfrac{n}{2}$ 个数为偶数，后 $\dfrac{n}{2}$ 个数为奇数。

- 前 $\dfrac{n}{2}$ 个数的和等于后 $\dfrac{n}{2}$ 个数的和。

- $a_i\ne a_j(1\le i,j\le n)$。

### 思路

前 $\dfrac{n}{2}$ 个数构造成 $2,4,6,\dots,n$，令它们的和为 $s_1$。接下来 $\dfrac{n}{2}-1$ 个数构造为 $1,3,5,\dots,n-3$，令它们的和为 $s_2$，最后一个数为 $s_1-s_2$。

**注意：如果 $\dfrac{n}{2}\bmod 2=1$ 则输出 `NO`**。

### 代码 $\And$ 讲解

```cpp
#include <cstdio>

using namespace std;
typedef long long LL;
int t,n;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        int sum=0;
        if((n/2)%2){puts("NO");continue;}
        puts("YES");
        for(int i=2;i<=n;i+=2){
            printf("%d ",i);
            sum+=i;
        }
        for(int i=1;i<n-2;i+=2){
            printf("%d ",i);
            sum-=i;
        }
        printf("%d\n",sum);
    }
    return 0;
}
```

---

## 作者：do_while_true (赞：1)

给出一个 $n$ （$n$ 为偶数），构造一个长度为 $n$ 的数列 $a$ ，使得满足一下两个条件：

1. 前 $\frac{n}{2}$ 个为偶数，后 $\frac{n}{2}$ 个为奇数
1. 满足 $\sum\limits_{i=1}^{\frac{n}{2}}a_i=\sum\limits_{i=\frac{n}{2}+1}^{n}a_i$

如果不能构造输出 "NO"，反之第一行输出 "YES"，第二行输出构造的数列。

说成人话就是偶数的和 和 奇数的和相等。

对于前半数列的每一个偶数，如果想两半的数的和尽量接近，对应位置的也应该尽量接近。所以我们对于前半部分的每一个偶数，它的对应的奇数，一半是偶数-1，一半是偶数+1，这样-1和+1互相抵消，两部分就可以相等。无解情况可以很容易看出来就是一半不能再分成一半的情况，也就是 $n$ 不能被 $4$ 整除。

### $\mathcal{Code:}$
```cpp
if(n%4!=0) puts("NO");
else {
	puts("YES");
	for(int i=1;i<=n/2;i++)
		printf("%d ",i*2);
	for(int i=1;i<=n/4;i++)
		printf("%d ",i*2-1);
	for(int i=n/4+1;i<=n/2;i++)
		printf("%d ",i*2+1);
	puts("");
}
```


---

## 作者：Elma_ (赞：1)

## Description

给你一个正整数$n$，满足$2 \mid n$，你需要构造一个长度为$n$的序列$a$满足：

- 序列$a$的前$\frac{n}{2}$个数为偶数

- 序列$a$的后$\frac{n}{2}$个数为奇数

- 序列$a$中的所有数都是不同的正整数

- $\sum\limits_{i=1}^\frac{n}{2}a_i$ $=$ $\sum\limits_{i=\frac{n}{2}+1}^na_i$

## Solution

若$2 \nmid \frac{n}{2}$，因为偶数个奇数和为偶数，奇数个奇数和为奇数，所以有
$2 \mid \sum\limits_{i=1}^\frac{n}{2}a_i$，$2 \nmid \sum\limits_{i=\frac{n}{2}+1}^na_i$，此时$\sum\limits_{i=1}^\frac{n}{2}a_i$ $\neq$ $\sum\limits_{i=\frac{n}{2}+1}^na_i$。所以当$2|\frac{n}{2}$，即$4|n$时有解。

提供一种构造的思路：

使前$\frac{n}{2}$个数为$2$，$4$，$6$，$…$，$2 \times \frac{n}{2}$，后$\frac{n}{2}$个数为$1$，$3$，$5$，$…$，$2 \times \frac{n}{2}-1$。

由于
$$a_i = a_{\frac{n}{2}+i}+1$$
此时有： 
$$\sum\limits_{i=1}^\frac{n}{2}a_i = \sum\limits_{i=\frac{n}{2}+1}^na_i+\frac{n}{2}$$

为了使它们相等，只需要让$a_n = 2 \times \frac{n}{2}-1+\frac{n}{2}$就可以了。

## Code

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long t, n;

int main(void)
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		int sum = 2;
		
		if(n%4 != 0)
			printf("NO\n");
		else
		{
			printf("YES\n");
			for(int i=1;i<=n/2;i++)
			{
				printf("%d ", sum);
				sum += 2;
			}
			
			sum = 1;
			
			for(int i=2;i<=n/2;i++)
			{
				printf("%d ", sum);
				sum += 2;
			}
			
			sum += n/2;
			printf("%d\n", sum);
		}
	}
	
	return 0;
}
```


---

## 作者：TLMPEX (赞：1)

如果n/2是奇数，就输出NO。否则输出YES。

若果是偶数，则第1个偶数可以置为2，剩下n/2-1个偶数都是上一个偶数加2。用变量a把这些偶数的和都记录下来。

剩下就是奇数了，第n/2+1个数可以置为1，以后每个数（除了最后一个数）都是上一个数加2，并用变量b把它们的和记录下来，最后一个数就是a-b了。

下面上代码。
```c
#include<bits/stdc++.h>
using namespace std;
int k[200001];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,i,x;
		cin>>n;
		x=n/2;//记录n/2
		if(x%2!=0)cout<<"NO\n";//判断是否是奇数，如果是则输出‘NO’并换行
		else{
			int a,b;
			k[1]=2;//把第一个偶数置为1
			a=k[1];
			for(i=2;i<=x;i++){
				k[i]=k[i-1]+2;//剩下的偶数为上一个加2
				a+=k[i];
			}
			k[x+1]=1;//第一个奇数为1
			b=k[x+1];
			for(i=x+2;i<n;i++){
				k[i]=k[i-1]+2;//剩下的奇数（除了最后一个）为上一个加2
				b+=k[i];
			}
			k[n]=a-b;//最后一个为偶数的和减去x-1个奇数的和
			cout<<"YES\n";
			for(i=1;i<=n;i++)
				cout<<k[i]<<" ";
			cout<<endl;
		}
	}
}
```


---

