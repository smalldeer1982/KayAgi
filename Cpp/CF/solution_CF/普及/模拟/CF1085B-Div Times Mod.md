# Div Times Mod

## 题目描述

给定n,k(1≤n≤$10^6$,2≤k≤$10^3$)

已知i，ans $\in$ Z，S.T. i | n（1≤i)&&ans $\equiv$ i(mod k)&&ans / k == n / i

求ans的最小值

## 样例 #1

### 输入

```
6 3
```

### 输出

```
11
```

## 样例 #2

### 输入

```
1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 6
```

### 输出

```
10
```

# 题解

## 作者：Fat_Fish (赞：5)

这道题思维难度不高，代码难度也不太高，个人认为橙题差不多了。

思路：因为 $a \times b = n$ ，所以我们要使 $x$ 尽可能小，即 $a$ 尽可能的小，就要使 $b$ 尽可能大。又因为 $a$ 和 $b$ 皆为整数，所以有：
 - $b\equiv0\pmod{n}$
 
 - $0 < b < k$
 
最后枚举到合适的 $b$ 计算出答案，即 $n / b \times k + b$ 。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-') {
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch)) {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}//快读
int n,k,ans,tmp;
signed main() {
	n=read(),k=read();
	for(int i=k-1;i>0;--i){//从大到小枚举
		if(n%i==0){//符合条件
			tmp=i;//记录答案
			break;//直接退出
		}
	}
	printf("%d\n",n/tmp*k+tmp);//输出答案
	return 0;//结束程序！( •̀ ω •́ )y
}
```


---

## 作者：little_sun (赞：3)

## B. Div Times Mod

明显要使$x$最小，一定要使$x \mod k$最大

从$n-1$到$1$找能被$n$整除的最大数$y$

答案即为$(n/y)*k+y$

**Code：**

```c++
# include <bits/stdc++.h>
# define ll long long
int main()
{
    ll n, k;
    ll ans = 0;
    scanf("%I64d%I64d", &n, &k);
    for(int i = 1; i < k; i++)
        if(n % i == 0)
            ans = i;
    printf("%I64d", (((n / ans) * k) + ans));
    return 0;
}
```


---

## 作者：吴思诚 (赞：3)

## CF1085B Div Times Mod 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1085B)

### 思路:
$b$ 的范围较小，考虑从大到小枚举 $b$。因为 $ab=n$，故枚举 $b$ 应判断是否能被 $n$ 整除，接着把 $a$ 求出来。因为 $a=\dfrac{x}{k}$，而 $b$ 的范围最大不超过 $k-1$，求 $x$ 时 $a$ 需乘 $k$，可以证明，必须让 $a$ 尽可能小，使 $b$ 尽可能大。用 $a$ 和 $b$ 来求 $x=ak+b$，因为 $a$ 需乘 $k$，所以要将 $a$ 尽可能调小，所以第一次满足条件，即可停下。

------------

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k,a,x,b;
	cin>>n>>k;
	for(b=k-1;b>0;b--){//枚举b
		if(n%b==0){//b可行
			a=n/b;
			x=a*k+b;
		}
		if(a*b==n){
				cout<<x;
				break;
		}
	}
    return 0;
}
```


---

