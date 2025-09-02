# Coins

## 题目描述

In Berland a money reform is being prepared. New coins are being introduced. After long economic calculations was decided that the most expensive coin should possess the denomination of exactly $ n $ Berland dollars. Also the following restriction has been introduced for comfort: the denomination of each coin should be divisible by the denomination of any cheaper coin. It is known that among all the possible variants the variant with the largest number of new coins will be chosen. Find this variant. Print in the order of decreasing of the coins' denominations.

## 样例 #1

### 输入

```
10
```

### 输出

```
10 5 1
```

## 样例 #2

### 输入

```
4
```

### 输出

```
4 2 1
```

## 样例 #3

### 输入

```
3
```

### 输出

```
3 1
```

# 题解

## 作者：ShineEternal (赞：12)

这个题应该不难。

### 但是关键的一点就是别理解错题意。

- 翻译有点误导性，让我第一眼以为是所有的约数之类

然后一看样例1就不对了，再对照一下原文，发现其实题意是：

> 给定一个数 $n$，求一个数列，使得数列中的后一个数都是前一个数的因数，求这个数列元素最多的情况。

然后设前一个数为后一个的x倍，我们让x递增就行。



```cpp
#include<cstdio>
using namespace std;
int main()
{
	int n,x=2;
	scanf("%d",&n);
	while(n>1)
	{
		if(n%x!=0)x++;
		else
		{
			printf("%d ",n);
			n=n/x;
		}
	}
	printf("1\n");
	return 0;
}
```

---

## 作者：「已注销」 (赞：5)

设前一个数是后一个数的$k$倍

$k$显然是$n$的一个质因数$($如果是合数，一定存在更优解$)$

不妨使$k$递增

```cpp
#include<iostream>
using namespace std;
int n,x=2;
int main(){
    cin>>n;
    while(n>1)
        if(n%x)++x;
        else{
            cout<<n<<' ';
            n/=x;
        }
    cout<<1;
}
```
$O(n)$

显然$n$至多只有一个质因子$>\sqrt{n}$

$k$只需在$[2,\lfloor\sqrt{n}\rfloor]$枚举即可

```cpp
#include<cmath>
#include<iostream>
using namespace std;
long long n,s,x=2;
int main(){
	cin>>n;
	s=sqrt(n);
	while(n>1&&x<=s)
		if(n%x)++x;
		else{
			cout<<n<<' ';
			n/=x;
		}
	if(n>1)cout<<n<<' ';
	cout<<1;
}
```
$O(\sqrt{n})$

---

## 作者：lixiao189 (赞：2)

## 题目大意：
如果我们有一个数 $ n $ ，求一个数组，数组中的后一个数都是前一个数的因数，求一个数组元素最多的那个数组。
## 思路：
首先这个数列中的每一个数都是第一个数的因子

然后如果有一个数，我们都可以分解质因数，比如说下图

![](https://cdn.luogu.com.cn/upload/pic/32600.png )

所以可以知道当这个数列中的数最多的情况的时候一定是每个数都是前一个数除以前一个数的最小质因子。

原因就是因为首先这样做就可以满足数组中的数都是第一个数的因子，并且数组中的每一个数都是通过前一个数除以一个数得到，所以都是前一个数的因子。如果我们要想要这个数组最长，那么我们只能够每次除以一个比当前数小的最小的一个质数。那么我们为什么要除以一个。因为所有的数都可以被分解质因数，所以每次数组中的后一个数等于前一个数除以一个比它小的质数一定有解。除以质数的原因就是假如说我们数组中的一个数可以通过前一个数除以合数得到，但是很显然一个合数可以被分解质因数，假如我们除这个合数，那还不如除以这个合数分解出来的最小质因数了。

然后我们按照上面的要求求出这个数组就可以了。

## 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector <int> ans;

bool check(int x){
	if(x<2) return false;
	for(register int i=2;i*i<=x;i++){
		if(x%i==0) return false;
	}
	return true;
}

void solve(int x){
	for(register int i=2;i<=x;i++){
		if(check(i) && x%i==0){
			ans.push_back(x/i);
			if((x/i)==1) return;
			solve(x/i);
			break;
		}
	}
}

int main(){
	scanf("%d",&n);
	ans.push_back(n);
	solve(n);
	vector <int> :: iterator it;
	for(it=ans.begin();it!=ans.end();it++) printf("%d ",*it);
	printf("\n");
	return 0;
}
```


---

