# [EC Final 2021] Future Coder

## 题目描述

共 $T$ 组数据，每组给出一个数 $n$ 和 $n$ 个数 $a_1,a_2,...,a_n$，求有多少个二元组 $(a_i,a_j)$ 满足 $a_ia_j<a_i+a_j$。

## 样例 #1

### 输入

```
2
8
3 -1 4 1 -5 9 2 -6
1
0
```

### 输出

```
19
0
```

# 题解

## 作者：liuyi0905 (赞：3)

从序列中选出一对二元组 $(a,b)$，且 $a\times b<a+b$，求有几组满足条件的二元组。

首先考虑暴力解法，时间复杂度 $O(Tn^2)$，完全超时，所以只有可能是数学解法了。

众所周知，一个非正数乘一个正数一定小于两者之和，所以直接统计一下序列中负数和正数的个数，答案即为两者乘积。

代码：
```cpp
cin>>n;
for(int i=1;i<=n;i++)cin>>x,x>0?z++:f++;
cout<<z*f<<"\n";
```
~~然后发现样例都没过~~

为何错了呢？

我们发现 $1$ 乘一个正数也小于两者之和，所以 $1$ 的个数也是需要额外统计的。输出就要改为：
```cpp
cout<<z*f+v1*(z-v1)<<"\n";
```
~~然后发现又WA了~~

别忘了，如果序列中有多个 $1$，不同位置的 $1$ 也是可以匹配的，公式：
$$\frac{v1\times(v1-1)}{2}$$
别忘了开 `long long`。

全部代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,z,f,v1;
signed main(){
	for(cin>>t;t;z=f=v1=0,t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>x,x>0?z++:f++,v1+=x==1;
		cout<<z*f+v1*(z-v1)+v1*(v1-1)/2<<"\n";
	}
	return 0;
}
```

---

## 作者：Dream_poetry (赞：1)

### 题意：
从序列中任选两值 $a,b$，使得 $a \times b < a+b$。

输出共有多少组符合条件。

### 思路：
暴力是行不通的，考虑优化。

首先知道，一个负数乘一个正数肯定小于两者之和，那么分别统计负数和正数的个数（这里把 $0$ 算作负数，可以自己推一下）。

输出负数个数乘正数个数。

等等，还没完。

$1$ 也需要特别考虑。

$1$ 乘一个正数也是比两者之和小的，所以还要统计 $1$ 的个数，乘正数的个数 $-1$ 的个数。

还没完，$1$ 也是可以两两配对的，所以还要算。

现在就完成了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,z,f,T,o,op;
int a[500005];
signed main(){
	cin>>T;
	while (T--){
		z=0,f=0,o=0;
		cin>>n;
		for (int i=1;i<=n;i++){
			cin>>op;
			if (op<=0) f++;
			else z++;
			if (op==1) o++;
		}
		cout<<z*f+o*(z-o)+(o*(o-1)/2)<<endl;
	}
	return 0;
}
```


---

## 作者：猜一猜我是谁 (赞：1)

# 分析
由于 $a\times b-a-b=(a-1)(b-1)-1$，所以 $a\times b<a-b$ 可化为 $(a-1)(b-1)<1$。

分别讨论两种情况：

1. $(a-1)(b-1)<0$，可以分别统计正数和负数的数量，然后相乘即可。
2. $(a-1)(b-1)=0$，每找到一个 $0$，就统计剩下的非零数的数量，最后相加即可

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a[1000005],n,b,c,d,ans; //注意开 long long
int main(){
    cin>>t;
    while(t--){
        b=0;    //注意要清零
        c=0;
        d=0;
        ans=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++){
            if(a[i]-1>0) b++;
            if(a[i]-1<0) c++;
            if(a[i]-1==0){
                d++;
                ans+=n-d;  //统计剩下的非零数的数量
            }
        }
        ans+=b*c;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：BugGod (赞：0)

分三种情况讨论。首先，一个正数乘一个负数，一定满足要求。接着，讨论 $1$。$1$ 乘正数一定比两者之和小一，所以也要算。还有 $1\times 1$ 的情况，也要算上。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int juruo,n,a[1000010],zheng,fu,yi;//zheng是正数数量，fu是负数数量，yi是1的数量
void solve()
{
	zheng=fu=yi=0;//多测
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(a[i]==1)yi++;
		if(a[i]>0)zheng++;
		else fu++;
	}
	cout<<zheng*fu/*正数乘负数*/+yi*(zheng-yi)/*1乘上正数（不是1的）*/+yi*(yi-1)/2/*1和1相乘，注意一组1会被统计两次，所以还要除以2*/<<'\n';
}
signed main()
{
	cin>>juruo;
	while(juruo--)solve();
	return 0;
}
```

---

## 作者：denominator (赞：0)

> [原题](https://www.luogu.com.cn/problem/P9880)
>
> - **本题一个测试点内有多组测试数据**。
> - 给定长度为 $n$ 的整数序列 $a$。
> - 求满足以下条件的数对 $i,j$ 个数：
> 	- $a_i\cdot a_j<a_i+a_j$。
> - $1\leq n,\sum n\leq10^6$。

---

众所周知，这是因为当年 EC Final 压难度加进去的一道题，应该按照一般做法，没什么难度。但是以下是这道题的另一种推导。

$$
\begin{array}{rcll}
a_i\cdot a_j & < & a_i+a_j & \qquad(1) \\
a_i\cdot a_j-a_i-a_j & < & 0 & \qquad(2) \\
a_i\cdot a_j-a_i-a_j+1 & < & 1 & \qquad(3) \\
(a_i-1)\cdot(a_j-1) & < & 1 & \qquad(4) \\
(a_i-1)\cdot(a_j-1) & \leq & 0 & \qquad(5) \\
\end{array}
$$

其中 $(3)\to(4)$ 是一个非常基础的因式分解；$(4)\to(5)$ 是因为左边为整数。

那我们就把 $a$ 中所有元素减 $1$，题目则化为求满足 $a_i\cdot a_j\leq0$ 的数对 $i,j$ 个数。

考虑有哪些情况：

1. 正数 $\times$ 负数；
1. 非零数 ${}\times0$；
1. $0\times0$。

只需要统计出整数个数 $n_+$，负数个数 $n_-$，$0$ 的个数 $n_0$，总数 $n=n_++n_-+n_0$，则有（编号分别对于前面三种情况的编号）：

1. 个数为 $n_+\cdot n_-$；
1. 个数为 $(n-n_0)\cdot n_0$；
1. 个数为 $\dbinom{n_0}{2}$。

答案即为以上三种相加。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, n;
ll a, b, c;
// a 为正的个数，b 为负的个数，c 为 0 的个数。
int main () {
	scanf ("%d", &T);
	while (T --> 0) {
		scanf ("%d", &n);
		a = b = c = 0;
		for (int i = 1; i <= n; i++) {
			int x;
			scanf ("%d", &x);
			if (x > 1) { // 这里已经隐式地减掉了 1，下同。
				a++;
			} else if (x < 1) {
				b++;
			} else {
				c++;
			}
		}
		printf ("%lld\n", a * b + c * (n - c) + c * (c - 1) / 2); // 即为三种相加。
	}
	return 0;
}
```

可以发现，其实是和另一篇题解的代码等价的。

（不要骂我没有交过，上面那份代码在 gym 上测试是珂以 AC 的）

---

## 作者：Vct14 (赞：0)

### 题目描述

给定一个长为 $n$ 的数列 $a$，求满足 $a_ia_j<a_i+a_j$ 的二元组 $(a_i,a_j)$ 的个数。每个测试点中有多组测试数据。

### 思路

~~因式分解~~易得 $(a_i-1)(a_j-1)<1$。由于左式为整数，因此左式小于或等于 $0$。我们分类讨论：

- 左式等于 $0$。则 $a_i=1$ 或 $a_j=1$（至少满足一个）。设共有 $x$ 个数为 $1$，则共有 $n-x$ 个数不为 $1$。由乘法原理，一个数等于 $1$ 的情况共 $x(n-x)$ 种；两个数等于 $1$ 的情况共有 $C_x^2=\dfrac{x(x-1)}{2}$ 种。答案为 $x(n-x)+\dfrac{x(x-1)}{2}$。
- 左式为负数。此时 $a_i<1$ 或 $a_j<1$（仅满足一个）。即在所有数中选择一个小于 $1$ 的数与一个大于 $1$ 的数相乘。设共有 $y$ 个数小于 $1$，则有 $n-x-y$ 个数大于 $1$，则由乘法原理得答案为 $y(n-x-y)$。

输入时统计出 $x,y$，最后输出答案 $x(n-x)+\dfrac{x(x-1)}{2}+y(n-x-y)$ 即可。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

char *p1,*p2,buf[100000];
#define r() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read(){
    int x=0,f=1;
    char ch=r();
    while(ch<48||ch>57){
        if(ch=='-') f=-1;
        ch=r();
    }
    while(ch>=48 && ch<=57) x=x*10+ch-48,ch=r();
   	return x*f;
}

int main(){
	int T;cin>>T;
	while(T--){
		int n;
		scanf("%d",&n);
		long long a,x=0,y=0;
		for(int i=1; i<=n; i++){
			cin>>a;
			if(a==1) x++;
			if(a<1) y++;
		}
		cout<<x*(n-x)+x*(x-1)/2+y*(n-x-y)<<"\n";
	}
	return 0;
}
```

---

## 作者：__zfy__ (赞：0)

### 题意

共有 $T$ 组数据，每组数据共有 $n$ 个数，从这 $n$ 个数中找出两个数，$a_i$ 和 $a_j$，使得 $a_i \times a_j < a_i + a_j$，输出共有几组满足条件。

### 思路

首先最好想的就是暴力，按题意枚举即可，代码如下（每组数据）。
```cpp
	……
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		for(int j=1;j<=n;j++)
		{
			if(a[i]*a[j]<a[i]+a[j])
			{
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	……
```
这样每次求的时间复杂度达到了 $O(n^2)$，指定超时，所以我们考虑优化。

思考乘法的性质，就会轻松的得到负数选择作为一个乘数的方法可以，所以我们只要统计负数的个数在乘上这一组数的个数就可以了。

我们在想想还有没有别的满足条件的情况，如果像作者一样没有头绪，可以试试一些特殊的数，如质数或者是 $0$，$1$ 这样的。如 $0$ 不可以，再试试 $1$，发现可以，再试试其他的，似乎都不太行。同时因为每个 $1$ 和其他 $1$ 也是能配对的，需要特别考虑。这样我们就得到了一个结论：只统计负数和 $1$ 以及剩余总个数就可以了。

我们得到了一个这样的公式：$z \times f + y \times (z - y)+(y \times (y - 1) \div 2)$。

$z$，$f$，$y$ 分别是剩余总个数，负数个数和 $1$ 的个数。

### 伪代码

```cpp
for(i 1~n)
	if(ai<0) f++
   else z++
   if(ai==0) y++
cout<<z*f+y*(z-y)+(y*(y-1)/2)<<endl
```


---

## 作者：Xdwjs (赞：0)

需要特判以下情况：

- 当 $n<2$ 时，没有数对。

- 当 $a_i$ 与 $a_j$ 有一个为 $1$ 时，$a_i \times a_j$ 就等于另一个数字，$a_i + a_j$ 等于另一个数字加 $1$，所以 $a_i \times a_j < a_i + a_j$ 成立。

- 当 $a_i$ 与 $a_j$ 有一个为 $0$ 时，$a_i \times a_j$ 就等于 $0$，$a_i + a_j$ 等于另一个数字，所以当另外一个数字大于 $0$ 时 $a_i \times a_j < a_i + a_j$ 成立。

- 当 $a_i$ 与 $a_j$ 有一个是不为 $1$ 的正数，且另外一个为负数时，$a_i \times a_j$ 就小于另一个数，$a_i + a_j$ 大于另一个数，所以 $a_i \times a_j < a_i + a_j$ 成立。


其余情况 $a_i \times a_j < a_i + a_j$ 均不成立。需要开 ```long long```，注意重复计算同一个数对的情况。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005];
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        long long n;
        cin>>n;
        long long z=0,f=0,one=0,zero=0;
        for(int j=1;j<=n;j++)
        {
            cin>>a[j];
            if(a[j]>0) z++;
            if(a[j]<0) f++;
            if(a[j]==0) zero++;
            if(a[j]==1) one++;
        }
        if(n<2)
        {
            cout<<0<<endl;
            continue;
        }
        long long ans=0;
        ans+=one*(n-1)-one*(one-1)/2;//特殊处理 a[i] 和 a[j] 都等于 1 的情况
        ans+=zero*(z-one);//含有一个 1 的情况已经都处理过了，无须再处理一遍
        ans+=(z-one)*f;
        cout<<ans<<endl;
    }
    //system("pause");
    return 0;
}
```

---

