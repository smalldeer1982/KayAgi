# k-LCM (hard version)

## 题目描述

It is the hard version of the problem. The only difference is that in this version $ 3 \le k \le n $ .

You are given a positive integer $ n $ . Find $ k $ positive integers $ a_1, a_2, \ldots, a_k $ , such that:

- $ a_1 + a_2 + \ldots + a_k = n $
- $ LCM(a_1, a_2, \ldots, a_k) \le \frac{n}{2} $

Here $ LCM $ is the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of numbers $ a_1, a_2, \ldots, a_k $ .

We can show that for given constraints the answer always exists.

## 样例 #1

### 输入

```
2
6 4
9 5```

### 输出

```
1 2 2 1 
1 3 3 1 1```

# 题解

## 作者：Yizhixiaoyun (赞：6)

[更好的阅读体验](https://yizhixiaoyun.blogspot.com/2022/04/cf1497c2-k-lcm-hard-version.html)

## 前置题目

[CF1497C1 (easy version)](https://www.luogu.com.cn/problem/CF1497C1)

## 题目分析

不难发现，$1$ 不会影响最小公倍数，所以我们先进行处理。输出 $k-3$ 个 $1$ ，然后 $n = n - k + 3$ 。

然后我们就将题目简化为了上面那道题，做法可以看[简单版题解](https://www.luogu.com.cn/blog/yizhixiaoyun/solution-cf1497c1) 。

## 贴上代码

```cpp
#include<iostream>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		int n,k;
		cin>>n>>k;
		for(register int i=k;i>3;--i){
			n--;
			cout<<"1 ";
		}
		if(n%2==1) cout<<"1 "<<n/2<<" "<<n/2<<endl;
		else if(n%4!=0) cout<<"2 "<<n/2-1<<" "<<n/2-1<<endl;
		else cout<<n/2<<" "<<n/4<<" "<<n/4<<endl;
	}
}
```

---

## 作者：EuphoricStar (赞：2)

## 思路

因为 $1$ 不会影响最终的最小公倍数，所以我们先输出 $k - 3$ 个 $1$，并 $n \gets n - (k - 3)$。

然后就跟 [CF1497C1](https://www.luogu.com.cn/problem/CF1497C1) 一样了。

剩下的做法可以参考[我这篇题解](https://zltlittleboy.blog.luogu.org/solution-cf1497c1)。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, k;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        n -= (k - 3);
        for (int i = k; i > 3; --i) {
            printf("1 ");
        }
        if (n & 1) {
            printf("1 %d %d\n", n / 2, n / 2);
        } else if ((n / 2) & 1) {
            printf("2 %d %d\n", n / 2 - 1, n / 2 - 1);
        } else {
            printf("%d %d %d\n", n / 2, n / 4, n / 4);
        }
    }
    return 0;
}
```


---

## 作者：coldy_rainy (赞：1)

**前言**

[洛谷题目链接](https://www.luogu.com.cn/problem/CF1497C2)

[AC记录](https://www.luogu.com.cn/record/100068050)

[本题的简单版本](https://www.luogu.com.cn/problem/CF1497C1)

就是在简单版本的基础上加了一点东西，本质并没有太大改变。

另外，力推我简单版本的 [题解](https://www.luogu.com.cn/blog/cloudy-rainy123/solution-cf1497c1) ，本题要用到里面的结论。

**题目大意**

给定一个整数 $n$，请找到 $k$ 个和为 $n$ 的正整数 $a_1,a_2,\dots,a_k$，使得 $\operatorname{lcm}\{a_1,a_2,\dots,a_k\}\leqslant \dfrac n2$。

**分析**

这题与简单版本的唯一不同就是 $k$ 的大小。由于在 $\operatorname{lcm}$ 中加入数字 $1$ 并不影响最小公倍数。因此可以考虑在 $3$ 个数字的基础上，将答案加入 $k-3$ 个 $1$，最小公倍数不会改变，这题就转换为简单版本一样的方法了。

当然，因为和还是为 $n$，所以在进行和简单版本相同的构造时，要将 $n$ 减去 $k-3$，其他的不变。

直接上代码。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main()
{
   cin>>t;
   while(t--)
   {
    cin>>n>>k;
    for(int i=1;i<=k-3;i++)cout<<1<<' ';//本题新增，输出k-3个1
    n-=k-3;//将n减去k-3
    if(n%2)cout<<1<<' '<<n/2<<' '<<n/2<<'\n';
    else if(n%4)cout<<2<<' '<<n/2-1<<' '<<n/2-1<<'\n';
    else cout<<n/2<<' '<<n/4<<' '<<n/4<<'\n';
   }
   return 0;
}
```

**后记**

抄袭是不好的习惯哦。


---

## 作者：江户川·萝卜 (赞：1)

让我们先看看 [C1](https://www.luogu.com.cn/problem/CF1497C1)。

简单构造。

出题人很良心，样例把构造方法全点到了。

- 当 $n$ 为奇数，即样例中的 `3 3`，输出 $1,\lfloor\frac n2\rfloor,\lfloor\frac n2\rfloor$，此时 $\operatorname{lcm}=\lfloor\frac n2\rfloor$，即样例中的 `1 1 1`。
- 当 $\frac n2$ 为奇数，即样例中的 `14 3`，输出 $2,\frac n2-1,\frac n2-1$，此时 $\operatorname{lcm}=\frac n2$，即样例中的 `2 6 6`。
- 当 $\frac n2$ 为偶数，即样例中的 `8 3`，输出 $\frac n4,\frac n4,\frac n2$，此时 $\operatorname {lcm}=\frac n2$，即样例中的 `4 2 2`。

再看看C2。

同样简单构造。

同样良心出题人。

同样样例点明构造方法。

即不断放 $1$，直到剩下数的个数为 $3$ 时按照上面方法构造。

### Code

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i=k;i>3;i--) n--,printf("1 ");
		if(n&1) printf("1 %d %d\n",n/2,n/2);
		else{
			int t=n/2;
			if(t&1) printf("2 %d %d\n",t-1,t-1);
			else printf("%d %d %d\n",t/2,t/2,t);
		}
	}
	return 0;
}
```

---

## 作者：Evitagen (赞：1)

## CF1497 C1,C2

### 题目大意：
存在 $k$ 个数 $a_1,a_2...a_n$ 他们的总体的最小公倍数不大于 $\dfrac{n}{2}$ ，求出这个序列。

### 思路：
观察一下样例，我们可以发现，当 $k=3$ 时，后两个数一样，第一个数是 $2$ 的倍数，这是为什么呢，可以通过分析来解决：

我们知道，$2$ 的整数次幂的加和可以表示为任何一个正整数，我们需要其来帮忙，因此第一个数应是2的整数次幂。

此外，剩下两个数，这两个数如果相同，那么对于最小公倍数的增加最少。如果不相同，还会出现其他因数，因此应该相同。

所以，我们得到了[简单版](https://www.luogu.com.cn/problem/CF1497C1)的题解：

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,T;
typedef long long ll;
ll lcm(ll a,ll b){
    return a*b/__gcd(a,b);
}
bool check(ll a,ll b,ll c)
{
    if(a+b+c!=n) return false;//因为直接除会有不等于n的情况，因此需要判断
    if(lcm(lcm(a,b),c)>n/2) return false;
    return true;
}
int main()
{
    cin>>T;
    while(T--){
        cin>>n>>k;
        ll base=1;
        do{
            if(check(base,(n-base)/2,(n-base)/2)){
                cout<<base<<" "<<(n-base)/2<<" "<<(n-base)/2<<endl;
                break;
            }
            base=base*2;
        }while(1);
    }
    //system("pause");
    return 0;
}
```

### [困难版](https://www.luogu.com.cn/problem/CF1497C2)：

其实跟普通版思路差不多，题目中还有一个性质，就是：
**当 $a_i=1$时，对最小公倍数的大小没有增加，而总体的值增加了1。**

因此，困难版只比简单版多了几行：
```cpp
n-=(k-3);
while(k>3){
    cout<<1<<" ";k--;
}
```
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,T;
typedef long long ll;
ll lcm(ll a,ll b){
    return a*b/__gcd(a,b);
}
bool check(ll a,ll b,ll c)
{
    if(a+b+c!=n) return false;
    if(lcm(lcm(a,b),c)>n/2) return false;
    return true;
}
int main()
{
    cin>>T;
    while(T--){
        cin>>n>>k;
        n-=(k-3);
        while(k>3){
            cout<<1<<" ";k--;
        }
        ll base=1;
        do{
            if(check(base,(n-base)/2,(n-base)/2)){
                cout<<base<<" "<<(n-base)/2<<" "<<(n-base)/2<<endl;
                break;
            }
            base=base*2;
        }while(1);
    }
    //system("pause");
    return 0;
}
```

完美的切掉这道题！！

---

## 作者：LBYYSM_123 (赞：0)

### 推荐阅读
[k-LCM (easy version)](https://www.luogu.com.cn/problem/CF1497C1)       
[CF1497C1题解](https://www.luogu.com.cn/blog/windows88/solution-cf1497c1)
### 思路
众所周知，$1$ 是不影响**最小公倍数**的。   
所以就先输出 $k-3$ 个 $1$。   
剩下的内容按简单版本处理即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int i=t;i>=1;i--){
		int n,k;
		cin>>n>>k;
		for(;k>3;k--)
			n--,cout<<1<<" ";
		if(n%2==1) cout<<"1 "<<n/2<<" "<<n/2<<endl;
		else if(n%4!=0) cout<<"2 "<<n/2-1<<" "<<n/2-1<<endl;
		else cout<<n/2<<" "<<n/4<<" "<<n/4<<endl;
	}
	return 0;
} 
```

---

## 作者：Silence_water (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1497C2)

---

**Analyse**

本题在 [$\text{C1}$](https://www.luogu.com.cn/problem/CF1497C2) 的基础上做就容易很多。

让 $a_1=a_2=\ldots=a_{k-3}=1$，那么问题就转化为了：

求三个数 $a,b,c$，使得 $a+b+c=n-k+3$，且 $\operatorname{lcm}(a,b,c)\le \dfrac{n}{2}$。

用 $\text{C1}$ 的方法求解，得到的 $\operatorname{lcm}(a,b,c)\le \dfrac{n-k+3}{2}\le \dfrac{n}{2}$，满足条件。因此本构造方法成立。

---

**Solution**

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);
		for(int i=1;i<=k-3;i++)
			printf("1 ");
		n=n-k+3;
		if(n&1)
			printf("%d %d %d\n",1,n/2,n/2);
		else if(n%4==0)
			printf("%d %d %d\n",n/2,n/4,n/4);
		else printf("%d %d %d\n",2,(n-2)/2,(n-2)/2);
	}
	return 0;
}
```

---

**The end**

感谢您的观看！如有不足，请麻烦指正哦。

---

## 作者：y0y68 (赞：0)

只需将 $k$ 变为 $3$ 即可方便地讨论。考虑到任意 $a_i$ 为 $1$ 时，对 $LCM$ 没有影响，于是可取 $k-3$ 个 $a_i$ 为 $1$，将 $n$ 减去 $k-3$，然后化为 $k=3$ 的情况，即此题的 [easy version](https://www.luogu.com.cn/problem/CF1497C1)。$k=3$ 时的做法见[这里](https://wo-shi-qu-ruo.blog.luogu.org/solution-cf1497c1)。

放上AC代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n,m;
int main(){
	for(cin>>T;T;T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m-3;i++)
			printf("1 ");
		n-=(m-3);
		if(n&1){
			printf("1 %d %d\n",(n-1)/2,(n-1)/2);
		}
		else if(n%4==0){
			printf("%d %d %d\n",n/2,n/4,n/4);
		}
		else{
			printf("2 %d %d\n",(n-2)/2,(n-2)/2);
		}
	}
	return 0;
}
```

---

## 作者：_caiji_ (赞：0)

此题与 [CF1497C1](/problem/CF1497C1) 有异曲同工之妙。

我们知道，$\operatorname{lcm}(1,x)=x$，不难想到，$\operatorname{lcm}(1,1,...,1,x)$ 也等于 $x$，有多少个 $1$ 不影响结果。那么我们可以输出 $k-3$ 个 $1$，并将 $n$ 减去 $k-3$，然后按照 [CF1497C1](https://www.luogu.com.cn/blog/caijianhong/solution-cf1497c1) 中 $k=3$ 的情况处理即可。

```cpp
int n,k;
int mian(){
	scanf("%d%d",&n,&k);
	while(k>3) n--,k--,printf("1 ");//while循环更容易理解
	if(n&1) printf("%d %d 1",n/2,n/2);
	else if(n%4==0) printf("%d %d %d",n/2,n/4,n/4);
	else printf("%d %d 2",n/2-1,n/2-1);
	return puts(""),0;
}
```


---

## 作者：StayAlone (赞：0)

### 题意

请找到一个长度为 $k$ 的序列 $a$，$\texttt{s.t.}\sum\limits_{i=1}^{k}a_i = n \land \texttt{lcm}(a_1,a_2,\cdots ,a_k) \leqslant \frac{n}{2}$。  

$t$ 组测试数据，保证有解。

### 思路

这道题就是[CF1497C1](https://www.luogu.com.cn/problem/CF1497C1)的一点点加强。

**以下描述均默认包含 $k = 3$ 的限制。**

这道题是一道~~找规律~~构造题，虽然[C1](https://www.luogu.com.cn/problem/CF1497C1)的样例给出了所有的 $3$ 种情况，导致我们很好找规律，然而证明是做题时一个很重要的步骤。  

- 当 $n$ 为奇数时，我们令这三个数的最小公倍数为 $\lfloor \frac{n}{2} \rfloor$。则这三个数分别为 $1,\lfloor \frac{n}{2} \rfloor,\lfloor \frac{n}{2} \rfloor$。
- 当 $n$ 为偶数但 $n$ $\texttt{mod}$ $4 \ne 0$时，我们令这三个数的最小公倍数为 $\frac{n}{2}$。则这三个数分别为 $2,\frac{n}{2}-1,\frac{n}{2}-1$。
- 其他情况下，即 $n$ $\texttt{mod}$ $4 = 0$ 时，我们令它们的最小公倍数为 $\frac{n}{2}$。则这三个数分别为 $\frac{n}{2},\frac{n}{4},\frac{n}{4}$。

其正确性在 $n \geqslant 3$ 时显然。到这里我们也就知道题目中所说的保证有解是指 $n \geqslant 3$。  

**现在我们看回原题，即 $k \geqslant 3$。**  

那就是在[C1](https://www.luogu.com.cn/problem/CF1497C1)的基础上，加一行代码：
```cpp
while (k > 3) printf("1 "), --k, --n;
```
其正确性很好证明：

1. 一个序列的最小公倍数和这个序列与 $1$ 的最小公倍数相等。
2. 此行代码保证在 $k = 3$ 时，$n$ 尽量大。因为前 $k - 3$ 个数必定为正整数，则最小为 $1$，前面的这 $k - 3$ 个数均为 $1$，则 $n$ 最大。
3. $n$ 尽量大时，$n \geqslant 3$，因为题目保证有解。

[AC code记录](https://www.luogu.com.cn/record/50923824)  

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k;

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &k);
		while (k > 3) printf("1 "), --k, --n;
        if (n % 2) printf("1 %d %d\n", n / 2, n / 2); // n 为奇数
        else if (n % 4) printf("2 %d %d\n", n / 2 - 1, n / 2 - 1); // n 为偶数但 n % 4 != 0
        else printf("%d %d %d\n", n / 2, n / 4, n / 4); // n % 4 == 0
	}
	return 0;
} 
```

---

