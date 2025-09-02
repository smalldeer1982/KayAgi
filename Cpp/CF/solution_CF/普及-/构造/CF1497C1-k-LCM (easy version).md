# k-LCM (easy version)

## 题目描述

It is the easy version of the problem. The only difference is that in this version $ k = 3 $ .

You are given a positive integer $ n $ . Find $ k $ positive integers $ a_1, a_2, \ldots, a_k $ , such that:

- $ a_1 + a_2 + \ldots + a_k = n $
- $ LCM(a_1, a_2, \ldots, a_k) \le \frac{n}{2} $

Here $ LCM $ is the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of numbers $ a_1, a_2, \ldots, a_k $ .

We can show that for given constraints the answer always exists.

## 样例 #1

### 输入

```
3
3 3
8 3
14 3```

### 输出

```
1 1 1
4 2 2
2 6 6```

# 题解

## 作者：EuphoricStar (赞：4)

## 思路

观察样例找规律，我们可以发现：

- 当 $n$ 为奇数时，输出 $1, \left\lfloor\dfrac{n}{2}\right\rfloor, \left\lfloor\dfrac{n}{2}\right\rfloor$；
- 当 $n$ 为偶数但是不能被 $4$ 整除时，输出 $2,\dfrac{n}{2} - 1,\dfrac{n}{2} - 1$；
- 当 $n$ 能被 $4$ 整除时，输出 $\dfrac{n}{2},\dfrac{n}{4},\dfrac{n}{4}$。

于是题目就变得非常简单了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, k;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
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

## 作者：Yizhixiaoyun (赞：3)

[更好的阅读体验](https://yizhixiaoyun.blogspot.com/2022/04/cf1497c1-k-lcm-easy-version.html)

## 题目分析

本题的三个样例正好就是本题的三种情况：

1. $n$ 为奇数，输出 $1 , \dfrac{n}{2} , \dfrac{n}{2}$ 。

2. $\dfrac{n}{2}$ 为奇数，输出 $2 , \dfrac{n}{2} - 1 , \dfrac{n}{2} - 1$ 。

3. $\dfrac{n}{2}$ 为偶数，输出 $\dfrac{n}{2} , \dfrac{n}{4} , \dfrac{n}{4}$ 。

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
		if(n%2==1) cout<<"1 "<<n/2<<" "<<n/2<<endl;
		else if(n%4!=0) cout<<"2 "<<n/2-1<<" "<<n/2-1<<endl;
		else cout<<n/2<<" "<<n/4<<" "<<n/4<<endl;
	}
}
```

---

## 作者：江户川·萝卜 (赞：3)

简单构造。

出题人很良心，样例把构造方法全点到了。

- 当 $n$ 为奇数，即样例中的 `3 3`，输出 $1,\lfloor\dfrac n2\rfloor,\lfloor\dfrac n2\rfloor$，此时 $\operatorname{lcm}=\lfloor\dfrac n2\rfloor$，即样例中的 `1 1 1`。
- 当 $\dfrac n2$ 为奇数，即样例中的 `14 3`，输出 $2,\dfrac n2-1,\dfrac n2-1$，此时 $\operatorname{lcm}=\dfrac n2$，即样例中的 `2 6 6`。
- 当 $\dfrac n2$ 为偶数，即样例中的 `8 3`，输出 $\dfrac n4,\dfrac n4,\dfrac n2$，此时 $\operatorname {lcm}=\dfrac n2$，即样例中的 `4 2 2`。

### Code:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,k;
		scanf("%d%d",&n,&k);//k=3
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

## 作者：StayAlone (赞：3)

$2021/7/9$ 更改部分 LaTex 格式。
*****
### 题意

请找到一个长度为 $k$ 的序列 $a$，使得$\sum\limits_{i=1}^{k}a_i = n \land \texttt{lcm}(a_1,a_2,\cdots ,a_k) \leqslant \dfrac{n}{2}$。  

$t$ 组测试数据，保证有解，且 $k = 3$。

### 思路

这道题是一道~~找规律~~构造题，虽然样例给出了所有的 $3$ 种情况，导致我们很好找规律，然而证明是做题时一个很重要的步骤。  

- 当 $n$ 为奇数时，我们令这三个数的最小公倍数为 $\left\lfloor \dfrac{n}{2} \right\rfloor$。则这三个数分别为$1,\left\lfloor \dfrac{n}{2} \right\rfloor,\left\lfloor \dfrac{n}{2} \right\rfloor$。
- 当 $n$ 为偶数但 $n$ $\bmod$ $4 \ne 0$时，我们令这三个数的最小公倍数为 $\dfrac{n}{2}$。则这三个数分别为 $2,\dfrac{n}{2}-1,\dfrac{n}{2}-1$。
- 其他情况下，即 $n$ $\bmod$ $4 = 0$ 时，我们令它们的最小公倍数为 $\dfrac{n}{2}$。则这三个数分别为 $\dfrac{n}{2},\dfrac{n}{4},\dfrac{n}{4}$。

其正确性在 $n \geqslant 3$ 时显然。
到这里我们也就知道题目中所说的保证有解是指 $n \geqslant 3$。

[AC code记录](https://www.luogu.com.cn/record/50923689)  

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
		if (n % 2) printf("1 %d %d\n", n / 2, n / 2); // n 为奇数
		else if (n % 4) printf("2 %d %d\n", n / 2 - 1, n / 2 - 1); // n 为偶数但 n % 4 != 0
		else printf("%d %d %d\n", n / 2, n / 4, n / 4); // n % 4 == 0
	}
	return 0;
} 
```

---

## 作者：saixingzhe (赞：2)

# 思路
找规律分讨题。

观察样例不难发现：

* 当 $n$ 为奇数时，输出 $1$，$\frac{n}{2}$，$\frac{n}{2}$。
* 当 $\frac{n}{2}$ 为奇数时，输出 $2$，$\frac{n}{2}-1$，$\frac{n}{2}-1$。
* 如果不是以上两种情况。输出 $\frac{n}{2}$，$\frac{n}{4}$，$\frac{n}{4}$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k;
int main() {
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        if(n&1) cout<<1<<' '<<n/2<<' '<<n/2<<endl;
        else if((n/2)&1)    cout<<2<<' '<<n/2-1<<' '<<n/2-1<<endl;
        else    cout<<n/2<<' '<<n/4<<' '<<n/4<<endl;
    }
    return 0;
}
```

---

## 作者：FwbAway (赞：1)

我们可以发现，当 $k=3$ 时，后面的两个数一样，第一个数是 $2$ 的倍数，简单分析一下：

这样知道，$2$ 的整数幂加和可以表示为任何一个正整数，我们需要其来帮忙，因此第一个数就是2的整数幂了。

注意还有两个数！对于最小公倍数的增加最小的。如果不相同，就出现其他因数，因此相同。代码如下。

```c++
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main() {
	cin>>t;
	while (t--) {
		cin>>n>>k;
		if(n%2==1)cout<<1<<' '<<n/2<<' '<<n/2<<endl;
		else if(n%4!=0)cout<<2<<' '<<n/2-1<<' '<<n/2-1<<endl;
		else cout<<n/2<<' '<<n/4<<' '<<n/4<<endl;
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

---

## 作者：coldy_rainy (赞：1)

**前言**

[题目链接](https://www.luogu.com.cn/problem/CF1497C1)

[CF原题链接](https://codeforces.com/problemset/problem/1497/C1)

[AC记录原版](https://www.luogu.com.cn/record/100063424)

[AC记录（快读）](https://www.luogu.com.cn/record/100063017)

就是个要分类讨论的构造题，虽然可以直接从样例中看出来，但每种情况还是会给出弱弱的证明。

**题目大意**

给定一个整数 $n$，请找到 $k$ 个和为 $n$ 的正整数 $a_1,a_2,\dots,a_k$，使得 $\operatorname{lcm}\{a_1,a_2,\dots,a_k\}\leqslant \dfrac n2$。

**分析**

$\operatorname{lcm}$ 表示最小公倍数。

正整数无非就有三种情况：不能被 $2$ 整除，能被 $2$ 整除但无法被 $4$ 整除以及能被 $4$ 整除，对以上情况进行讨论。

- 不能被 $2$ 整除

此时的 $\dfrac n2$ 不是一个整数，而最小公倍数只能是整数，因此最小公倍数最大只能取 $\left\lfloor\dfrac{n}{2}\right\rfloor$，可以看做是 $\dfrac n2-\dfrac 12$。考虑最简单的方法，即最小公倍数就是 $\left\lfloor\dfrac{n}{2}\right\rfloor$，三个答案中有两个是 $\left\lfloor\dfrac{n}{2}\right\rfloor$，此时的和为 $n-1$，则第三个数取 $1$。

则此时的答案为 $1,\left\lfloor\dfrac{n}{2}\right\rfloor,\left\lfloor\dfrac{n}{2}\right\rfloor$。

- 能被 $2$ 整除但不能被 $4$ 整除

此时的 $\dfrac n2$ 是一个整数，但只是一个奇数。若将它作为最小公倍数，那么三个约数就只能都是奇数（不然最小公倍数一定是个偶数，与前面矛盾），但这三个奇数相加，和也为奇数，而 $n$ 却是一个偶数，前后又有矛盾。所以只能往后退一位 ，将 $\dfrac n2-1$ 作为它的最小公倍数，像上面一样考虑后，发现可行。

仍然考虑最简单的情况，答案中有两个 $\dfrac n2-1$，此时的和为 $n-2$，则第三个数取 $2$。

则此时的答案为 $2,\dfrac n2-1,\dfrac n2-1$。

- 能被 4 整除

此时的 $\dfrac n2$ 是一个偶数，仍然考虑最简单的情况，答案中有一个 $\dfrac n2$，那么接下来两个都可取 $\dfrac n4$。因为 $\dfrac n2=\dfrac n4 \times 2$，所以这样取得后最小公倍数为 $\dfrac n2$，且 $\dfrac n2 + \dfrac n4 +\dfrac n4=n$，可行。

则此时的答案为 $\dfrac n2,\dfrac n4,\dfrac n4$。

根据以上结论，我们可以很简单地得出代码。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t/*数据组数*/,n,k;
int main()
{
   cin>>t;
   while(t--)
   {
    cin>>n>>k;
    if(n%2)cout<<1<<' '<<n/2<<' '<<n/2<<'\n';//情况1：不能被2整除
    else if(n%4)cout<<2<<' '<<n/2-1<<' '<<n/2-1<<'\n';//情况2：能被2整除但不能被4整除
    else cout<<n/2<<' '<<n/4<<' '<<n/4<<'\n';//情况3：能被4整除
   }
   return 0;
}
```

**后记**

可以看看 [本题的加强版](https://www.luogu.com.cn/problem/CF1497C2) ，其实就是在本题上改动了一下。

抄袭是不好的习惯哦。

谢谢观看！

---

## 作者：Silence_water (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1497C1)

---

**Analyse**

分类讨论。

1. 如果 $n$ 是奇数，那么 $3$ 个数分别为 $1$，$\lfloor\dfrac{n}{2}\rfloor$，$\lfloor\dfrac{n}{2}\rfloor$。

2. 如果 $n$ 是偶数且为 $4$ 的倍数，那么 $3$ 个数分别为 $\dfrac{n}{4}$，$\dfrac{n}{4}$，$\dfrac{n}{2}$。

3. 如果 $n$ 是偶数且不为 $4$ 的倍数，那么 $3$ 个数分别为 $2$，$\dfrac{n-2}{2}$，$\dfrac{n-2}{2}$。

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

## 作者：_caiji_ (赞：1)

看数据范围，$1\leq T\leq10^4$，$1\leq n\leq 10^9$，显然是构造题。

我们分三类讨论：
1. $n\bmod 2=1$：显然可以先提出一个 $1$，再把 $n-1$ 分成两半，$\operatorname{lcm}(1,\frac{n-1}{2},\frac{n-1}{2})=\frac{n-1}{2}\leq\frac{n}{2}$，符合题意。这样构造出的解是 $(1,\frac{n-1}{2},\frac{n-1}{2})$ 也就是 $(1,\left\lfloor\frac{n}{2}\right\rfloor,\left\lfloor\frac{n}{2}\right\rfloor)$。
1. $n\bmod 4=0$：可以把 $n$ 拆成 $(\frac{n}{2},\frac{n}{4},\frac{n}{4})$，显然它们一定是正整数（$n\bmod 4=0$）且符合题意。
1. $n\bmod 4\neq 0$ 且 $n\bmod 2=0$：看上去我们只能把它分成 $(\frac{n}{2},\frac{n}{2})$，我们换个思路，从两个 $\frac{n}{2}$ 中各提出一个 $1$，把 $n$ 拆成 $(2,\frac{n}{2}-1,\frac{n}{2}-1)$。为什么这样是正确的呢？因为 $n\bmod 4\neq 0$，所以 $n\div 2$ 一定是奇数，可以列几个数试试看。又有 $\operatorname{lcm}(2,\text{奇数}-1,\text{奇数}-1)=\text{奇数}-1$，所以符合题意。

```cpp
int n,k;
int mian(){
	scanf("%d%d",&n,&k);
	if(n%2==1) printf("1 %d %d",n/2,n/2);
	else if(n%4==0) printf("%d %d %d",n/2,n/4,n/4);
	else printf("2 %d %d",n/2-1,n/2-1);
	return puts(""),0;
}
```


---

## 作者：blsya23a2 (赞：0)

## 分析
这是一道构造题，分三类情况讨论：

- 当 $n\bmod2\not=0$ 时，输出 $1,\frac{n}{2}-0.5,\frac{n}{2}-0.5$，$\operatorname{lcm}(1,\frac{n}{2}-0.5,\frac{n}{2}-0.5)=\frac{n}{2}-0.5$，符合条件。

- 当 $n\bmod2=0$ 时，
  - 当 $n\bmod4=0$ 时，输出 $\frac{n}{2},\frac{n}{4},\frac{n}{4}$，$\operatorname{lcm}(\frac{n}{2},\frac{n}{4},\frac{n}{4})=\frac{n}{2}$，符合条件。
  - 当 $n\bmod4\not=0$ 时，输出 $2,\frac{n}{2}-1,\frac{n}{2}-1$，$\operatorname{lcm}(2,\frac{n}{2}-1,\frac{n}{2}-1)=\frac{n}{2}-1$，符合条件。

另外，这道题有 [hard version](https://www.luogu.com.cn/problem/CF1497C2)，可以转化为这道题的情况。
## 代码
```python
a=int(input())
for b in range(a):
    c,d=map(int,input().split())
    if c%2!=0:
        print(1,int(c/2-0.5),int(c/2-0.5))
    elif c%4==0:
        print(int(c/2),int(c/4),int(c/4))
    else:
        print(2,int(c/2)-1,int(c/2)-1)
```

---

## 作者：scpchangyi (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1497C1)

### Solution

从数据的大小可以看出这是一道构造题。

接着用列举法列举出符合题目的几种情况：

- 判断 $n$ 不是 $2$ 的倍数，合法就输出 $1,\dfrac{n}{2},\dfrac{n}{2}$。

- 判断 $n$ 不是 $4$ 的倍数，合法就输出 $2,\dfrac{n}{2}-1,\dfrac{n}{2}-1$。

- 其他情况，输出 $\dfrac{n}{2},\dfrac{n}{4},\dfrac{n}{4}$。

### Code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
int t,n,k;
signed main() 
{
	scanf("%lld",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%lld",&n,&k);
		if(n%2!=0)printf("1 %lld %lld",n/2,n/2);
		/*判断n不是2的倍数*/
		else if(n%4!=0)printf("2 %lld %lld",n/2-1,n/2-1);
		/*判断n不是4的倍数*/
		else printf("%lld %lld %lld",n/2,n/4,n/4);
		/*其他情况*/
		printf("\n");//记得换行 
	}
	return 0;//好习惯 
}
```

---

## 作者：LBYYSM_123 (赞：0)

### 思路  
让我们运用**瞪眼法**，便可从样例中得知：   
+ 当 $n$ 为奇数时，输出为：$1,\frac{n}{2},\frac{n}{2}$。   
+ 当 $n\bmod4=0$ 时,输出为：$\frac{n}{2},\frac{n}{4},\frac{n}{4}$。
+ 否则，输出为：$2,\frac{n}{2}-1,\frac{n}{2}-1$。     
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
		if(n%2==1) cout<<"1 "<<n/2<<" "<<n/2<<endl;
		else if(n%4!=0) cout<<"2 "<<n/2-1<<" "<<n/2-1<<endl;
		else cout<<n/2<<" "<<n/4<<" "<<n/4<<endl;
	}
	return 0;
} 
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1497C1)

### 分析

由于已知 $k=3$，这道题我们就可以直接去试规律。

首先，构造的三个数不能超过 $\frac{n}{2}$，否则他们的最小公倍数就会超过 $\frac{n}{2}$。

然后是最优方案。我们要让构造的三个数中最小的数能够被最大的数整除。这样就能减少对他们最小公倍数的贡献。

接着是分类讨论。~~样例告诉了我们一切。~~

#### 样例1：

$n$ 为奇数，所以最小的数为 $1$，满足能够被最大的数整除，接着输出两个 $\frac{n}{2}$。

#### 样例2：

$n$ 能整除 $4$。输出一个 $\frac{n}{2}$ 和两个 $\frac{n}{4}$，就能满足最优方案。

#### 样例3

$n$ 能整除 $2$ 但不能整除 $4$，那么输出 $2$，两个 $\frac{n}{2}-1$，就能满足最优方案。

最后，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		if(n%2==1)
		{
			cout<<1<<" "<<n/2<<" "<<n/2<<endl;
		}
		else if(n%2==0&&n%4==0)
		{
			cout<<n/2<<" "<<n/4<<" "<<n/4<<endl;
		}
		else
		{
			cout<<2<<" "<<n/2-1<<" "<<n/2-1<<endl;	
		}
	}
	return 0;
}
```


---

