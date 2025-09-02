# Alyona and Numbers

## 题目描述

After finishing eating her bun, Alyona came up with two integers $ n $ and $ m $ . She decided to write down two columns of integers — the first column containing integers from $ 1 $ to $ n $ and the second containing integers from $ 1 $ to $ m $ . Now the girl wants to count how many pairs of integers she can choose, one from the first column and the other from the second column, such that their sum is divisible by $ 5 $ .

Formally, Alyona wants to count the number of pairs of integers $ (x,y) $ such that $ 1<=x<=n $ , $ 1<=y<=m $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF682A/bb850c8c10ee7a9c00e5b1ff3da7605a7415f98c.png) equals $ 0 $ .

As usual, Alyona has some troubles and asks you to help.

## 说明/提示

Following pairs are suitable in the first sample case:

- for $ x=1 $ fits $ y $ equal to $ 4 $ or $ 9 $ ;
- for $ x=2 $ fits $ y $ equal to $ 3 $ or $ 8 $ ;
- for $ x=3 $ fits $ y $ equal to $ 2 $ , $ 7 $ or $ 12 $ ;
- for $ x=4 $ fits $ y $ equal to $ 1 $ , $ 6 $ or $ 11 $ ;
- for $ x=5 $ fits $ y $ equal to $ 5 $ or $ 10 $ ;
- for $ x=6 $ fits $ y $ equal to $ 4 $ or $ 9 $ .

Only the pair $ (1,4) $ is suitable in the third sample case.

## 样例 #1

### 输入

```
6 12
```

### 输出

```
14
```

## 样例 #2

### 输入

```
11 14
```

### 输出

```
31
```

## 样例 #3

### 输入

```
1 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
3 8
```

### 输出

```
5
```

## 样例 #5

### 输入

```
5 7
```

### 输出

```
7
```

## 样例 #6

### 输入

```
21 21
```

### 输出

```
88
```

# 题解

## 作者：tanghg (赞：2)

这道题还算简单吧，在写这篇的时候洛谷爬 CF 没有爬出来，所以我把 AC 放到剪贴板里。

[AC记录](https://www.luogu.com.cn/paste/5bmfndul)

### 思路：

这道题的思路就是如何凑出五的倍数，而我们在小学就已经学过了一个数想被五整除末尾只能是 5 或 0。而我们希望 $a+b\bmod 5=0$ 就需要让 $a+b$ 的末尾为 0 即可。
也就是 $a\bmod 5 +b\bmod 5$ 是五的倍数。末尾就这几种情况：

>0,0 或 1,4 或 2,3 或 3,2 或 4,1

而我的程序时间复杂度为 $O(\max(n,m))$。

因为小一点的数字中符合条件的数大一点的数当然也有，所以从小一点的数往后看大数即可。

最后的答案就用最简单的排列组合情况输出就行。
```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll a,b,num1,num2,num3,num4,num0,num1_1,num1_2,num1_3,num1_4,num1_0;
int main() {
    cin>>a>>b;
    ll first= min(a,b),last= max(a,b);
    for (int i = 1; i <=first ; ++i) {
        if(i%5==0)num0++;
        if(i%5==1)num1++;
        if(i%5==2)num2++;
        if(i%5==3)num3++;
        if(i%5==4)num4++;
    }
    //先从1到min{a,b}去看。
    num1_0=num0;
    num1_1=num1;
    num1_2=num2;
    num1_3=num3;
    num1_4=num4;
    //将小一点的符合情况的数字放到大数之中。
    for (ll i = first+1; i <=last ; ++i) {
        if(i%5==0)num1_0++;
        if(i%5==1)num1_1++;
        if(i%5==2)num1_2++;
        if(i%5==3)num1_3++;
        if(i%5==4)num1_4++;
    }
    cout<<num0*num1_0+num1*num1_4+num2*num1_3+num3*num1_2+num4*num1_1;
    return 0;
}
```

---

## 作者：kbzcz (赞：2)

## 这是蒟蒻的第一篇题解，写的不好请见谅。

#### [题目](https://www.luogu.com.cn/problem/CF682A)

做这道题首先要了解[同余定理](https://wenku.baidu.com/view/c985cdd07f1cfad6195f312b3169a4517723e5c5.html)。

题目让我们求能被五整除的和，设两个数a,b,如果a,b的和能被五整除，则这a,b除以五所得的的余数的和也能被五整除。

可以表示为：

如果
$$ {(a+b)\%5=0} $$ 
则
$${(a\%5+b\%5)\div5=0}$$
也无余数。

这道题其实就是反了过来。

如果
$${(a\%5+b\%5)\div5=0}$$
则
$$ {(a+b)\%5=0} $$ 


于是这道题就变成了分别求1到n,1到m内有多少个被五除余0的，余1的，直到余4的数，再把n内余0的个数和m内余0的个数相乘，把n内余1的个数和m内余4的个数相乘，最后全部加起来就是答案。

而求个数的问题就是小学奥数题了，不会的话可以问问小学生。

最后附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum1[6],sum2[6];
int main(){
	long long n,m;
	cin>>n>>m;
	for(int i=0;i<5;i++)
	{
		sum1[i]=n/5;
		sum2[i]=m/5;
		if(i!=0&&n%5>=i)
		{
			sum1[i]++;
		}
		if(i!=0&&m%5>=i)
		{
			sum2[i]++;
		}
      //最后sum1[i]就是n中除以5余i的数的个数，sum2[i]就是m中除以5余i的数的个数
	}
	long long ans=sum1[0]*sum2[0];
	for(int i=1;i<5;i++)
	{
		ans=ans+sum1[i]*sum2[5-i];//不理解可以参考排列组合有多少种可能这种题
	}
	cout<<ans;
	return 0;
} 
```










---

## 作者：thomas_zjl (赞：1)

这道题挺好想的。

题解大部分都比较复杂。

我的思路是找 $n,m$ 中较小的一个数。

然后从 $1$ 枚举到 $n$。

每次找的时候，在用 ans 记录答案。

每个数加上一个数的为 $5$ 的倍数最小值是 $ 5-i\%5 $

再 ans 加上较大的数减去 $ 5-i\%5 $ 再除以 $5$。

但是不要忘了这个数加$ 5-i\%5 $ 也等于五，所以还要加一。

别忘了 ```long long```

接下来就是代码了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m;
    scanf("%lld%lld",&n,&m);
    if(m<n)
        swap(n,m);//使较小的数为n,较大的为m。
    long long ans=0;
    for(long long i=1;i<=n;i++){
        long long x=5-i%5;//上面有过讲解。
        if(m>=x)
            ans+=((m-x)/5)+1;//如果要记录必须要m>=x才行，不然的话不够加。
    }
    printf("%lld",ans);
}
```


---

## 作者：SIXIANG32 (赞：1)

今天把这道题AC了，自认为自己的做法很好玩，跟大家分享一下。    
闲话少说，切入正题——

------------
首先这题乍一看好像很简单，不就是 $O(nm)$ 暴力嘛~  
然后再定睛一看数据范围，好了炸了……  
那么我们改怎么做呢？这就是这道题的重头戏了——


------------
众所周知，$5$ 的倍数末尾一定是 $5$ 或者是 $0$（废话，这不是常识吗）。  
那么怎么判断两数相加是不是 $5$ 呢？  
根据小学数学列竖式，我们可以轻易的知道，当
$ 0\equiv[(x\mod10+y\mod10)\mod10]\pmod5$  
时，$x+y$ 必然是5的倍数。   

~~然后下面画风逐渐走向诡异了~~  

那么我们要怎么办呢？简单，打表！  

我们现在要做的事情就是寻找在 $0$~$9$ 之间哪两个数相加取余 $5$ 等于 $0$，这里我们用 $10$ 来代替 $0$，在后面会说明这样做的原因。  

献上打表的程序：  
```cpp
for(int p=0;p<=9;p++)
	for(int i=0;i<=9;i++)
		if((p+i)%5==0)
			cout<<p<<',';
cout<<endl;
for(int p=0;p<=9;p++)
	for(int i=0;i<=9;i++)
		if((p+i)%5==0)
			cout<<i<<',';
```  
为了更加直观这里直接枚举 $0$~$9$之间的，得到表后要把表里的 $0$ 换成 $10$。  

然后我们要统计 $1$~$n$ 和 $1$~$m$ 之间以 $0$~$9$ 做个位数的个数，这里就要用 $10$ 代替 $0$（这很好想吧），统计还是很简单的，就不细讲了。  

统计过后我们挨个枚举已经得到的两个数的组合，然后得出这两个数做个位数的次数的乘积，也就是以这两个数字做个位数能得到的相加是 $5$ 的倍数的数量，累加起来就能得到结果。  

上代码！
```cpp
#include<iostream>
#define int long long //防炸利器/xyx
using namespace std;
int nmod[100],mmod[100];
//nmod存储n以内每个数字做个位出现的次数
//mmod存储m以内每个数字做个位出现的次数
int ch1[30]={0,10,10,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9};
int ch2[30]={0,10,5,4,9,3,8,2,7,1,6,10,5,4,9,3,8,2,7,1,6};
//上面是刚才说的表
signed main()
{
	int n,m,ans=0;
	cin>>n>>m;
   //下面是统计
	for(int p=1;p<=10;p++)
		if(n%10>=p)nmod[p]=n/10+1;//当个位数还能有一个要记得+1
		else nmod[p]=n/10;//否则就除以10
	for(int p=1;p<=10;p++)
		if(m%10>=p)mmod[p]=m/10+1;
		else mmod[p]=m/10;
   //m的操作和上面同理
	for(int p=1;p<=20;p++)
		ans=ans+nmod[ch1[p]]*mmod[ch2[p]];//计算
	cout<<ans<<endl;	
}
```
统计要花 $O(20)$，更新要花 $O(20)$，一共 $O(40)$，已经很快惹。    

---

## 作者：sysu_yzc (赞：1)

## 思路
先求出1~n和1~m中除以$5$余$1,2,3,4,0$的数的个数，然后再利用余数的可加性计算出结果。
## 上代码
```cpp
#include<iostream>
using namespace std;
long long a[5][2];//分别记录1~n和1~m中除以5余1,2,3,4,0的数的个数
int main(){
	long long n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i<=5;i++){
		a[i-1][0]=n/5+bool(n%5>=i);
		a[i-1][1]=m/5+bool(m%5>=i);
	}
	for(int i=0;i<4;i++) ans+=a[i][0]*a[3-i][1];
	ans+=a[4][0]*a[4][1];
	cout<<ans;
	return 0;
}
```

---

## 作者：Patricky (赞：0)

~~只能说其他题解写得不够优美，早该水水题解了~~

## 题意
计算

$$
\sum_{i = 1} ^ {n}
\sum_{j = 1} ^ {m}
[\;{i + j \equiv 0 \pmod 5}\;]
$$

## 解答

组合出 $i + j \equiv 0 \pmod 5$ 只有 $5$ 种情况，
问题转化为怎么分别计算出这些数的个数来。

考虑代码 `for (int i = 5; i <= n; i += 5)` 运行次数，
这很容易，是 $\Big\lfloor \dfrac{n}{5} \Big\rfloor$ 次。
对应 $1 \sim n$ 中 $5$ 的倍数个数。

+ 如果增加偏移呢？

如 `for (int i = 5 - 4; i <= n; i += 5)`，
可以令其多走 $4$ 格，
从而转换为上一个问题，于是答案为 $\Big\lfloor \dfrac{n + 4}{5} \Big\rfloor$。
对应 $1 \sim n$ 中模 $5$ 余 $1$ 的数个数。

----

因而问题即：

$$
\Big\lfloor \dfrac{n}{5} \Big\rfloor
\Big\lfloor \dfrac{m}{5} \Big\rfloor
+
\sum_{i = 1} ^ 4 
\Big\lfloor \dfrac{n}{5} \Big\rfloor 
\times 
\Big\lfloor \dfrac{m + 5 - i}{5} \Big\rfloor
$$

----

## 参考代码

值得说明的是，对于 $C$++ 来说，默认的正整数之除是向下取整的。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0), ios::sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  long long ans = 1LL * (n / 5) * (m / 5);

  for (int i = 1; i < 5; ++i) {
    ans += 1LL * ((n + i) / 5) * ((m + 5 - i) / 5);
  }

  cout << ans << "\n";

  return 0 ^ 0;
}
```

---

## 作者：Sternenlicht (赞：0)

题解里好像还没有与我做法相似的，就来水一发。

思路：

$1\le n,m\le 10^6$，因此要考虑 $O(n)$ 做法。根据同余性质可知，若 $x+y\equiv0\pmod{5}$，则 $x$ 和 $y$ 有一下几种可能：

1. $x\equiv1\pmod{5}$，$y\equiv4\pmod{5}$。
2. $x\equiv2\pmod{5}$，$y\equiv3\pmod{5}$。
3. $x\equiv3\pmod{5}$，$y\equiv2\pmod{5}$。
4. $x\equiv4\pmod{5}$，$y\equiv1\pmod{5}$。
5. $x\equiv0\pmod{5}$，$y\equiv0\pmod{5}$。

则我们可以枚举 $1$ ~ $n$，用五个计数器分别统计 $n$ 中模 $5$ 余 $0$ 的数，模 $5$ 余 $1$ 的数，模 $5$ 余 $2$ 的数，模 $5$ 余 $3$ 的数和模 $5$ 余 $4$ 的数。$m$ 同理。

统计结束后，根据乘法原理，我们作如下几个操作：

1. $n$ 中模 $5$ 余 $0$ 的数的个数与 $m$ 中模 $5$ 余 $0$ 的数的个数相乘。

2. $n$ 中模 $5$ 余 $1$ 的数的个数与 $m$ 中模 $5$ 余 $4$ 的数的个数相乘。

3. $n$ 中模 $5$ 余 $2$ 的数的个数与 $m$ 中模 $5$ 余 $3$ 的数的个数相乘。

4. $n$ 中模 $5$ 余 $3$ 的数的个数与 $m$ 中模 $5$ 余 $2$ 的数的个数相乘.

5. $n$ 中模 $5$ 余 $4$ 的数的个数与 $m$ 中模 $5$ 余 $1$ 的数的个数相乘。

再根据加法原理，将这 $5$ 个操作的结果相加，即为答案。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
#define lowbit(x) (x&-x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define INF 0x3f3f3f3f
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

//计数器要开longlong，防止相乘相加时溢出int
LL yu0n,yu1n,yu2n,yu3n,yu4n;//分别统计n中模5余01234的数的个数 
LL yu0m,yu1m,yu2m,yu3m,yu4m;//分别统计m中模5余01234的数的个数 
int n,m;
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++)//枚举1~n 
		if (i%5==0)yu0n++;//余0的计数器++ 
		else if (i%5==1)yu1n++;//余1的计数器++ 
		else if (i%5==2)yu2n++;//余2的计数器++ 
		else if (i%5==3)yu3n++;//余3的计数器++ 
		else yu4n++;//余4的计数器++
	for (int i=1;i<=m;i++)//枚举1~m，同上 
		if (i%5==0)yu0m++;
		else if (i%5==1)yu1m++;
		else if (i%5==2)yu2m++;
		else if (i%5==3)yu3m++;
		else yu4m++;
	write(yu0n*yu0m+yu1n*yu4m+yu2n*yu3m+yu3n*yu2m+yu4n*yu1m);
    return 0;
}
```

---

## 作者：JustinXiaoJunyang (赞：0)

这题作为一道小奥难度的数学题，用的是余数的可加性。

前排芝士：

Q：余数有甚么定律？

A：余数的三大定律（俗称三文鱼）分别指的是：可加性、可减性、可乘性。

追问 Q：可除性？

A：额，除不一定整除，不整除的话会很糊涂……

这题用可加性来做。

思路分析： 

$x$ 表示从 $1$ 到 $n$ 中除以 $5$ 余 $i$ 的数的个数，

$y_i$ 表示从 $1$ 到 $m\bmod5$ 余 $i$ 的数的个数，那么答案就等于 $x_0×y_0+x_1×y_4+x_2×y_3+x_3×y_2+x_4×y_1$。

上面就是余数可加性的应用。

有这样的思路，离 AC 就不远了。

WARNING ：十年 OI 一场空，不开 long long 见祖宗！

参考代码：

```cpp
#include <iostream>
using namespace std;

long long x[5], y[5];

int main()
{
    long long n, m;
    cin >> n >> m;
    long long ans = 0;
    if (n % 5 == 0)
    {
        for (long long i = 0; i <= 4; i++)
        {
            x[i] = n / 5;
        }
    }
    else
    {
        x[0] = n / 5;
        for (long long i = 1; i <= 4; i++)
        {
            x[i] = n / 5;
            if (i % 5 <= n % 5) x[i]++;
        }
    }
    if (m % 5 == 0)
    {
        for (long long i = 0; i <= 4; i++)
        {
            y[i] = m / 5;
        }
    }
    else
    {
        y[0] = m / 5;
        for (long long i = 1; i <= 4; i++)
        {
            y[i] = m / 5;
            if (i % 5 <= m % 5) y[i]++;
        }
    }
    for (long long i = 0; i < 5; i++)
    {
        ans += x[i] * y[(5 - i) % 5];
    }
    cout << ans << endl;
    return 0;
}
```

蒟蒻的数学很菜，不要乱喷……

---

## 作者：千年陈皮精 (赞：0)

这一题比较水，但也需要动点脑筋。
### 思路
想要两个数相加为 $5$ 的倍数，那它们除 $5$ 的**余数**相加必须等于 $5$。例如，一个**余数**是 $1$ 的数加一个**余数**是 $4$ 等于 $5$,那这两个数相加就等于 $5$。题目还说 ```a+b, b+a视为不同的数对```~~，这样还可以让我们不用考虑太多~~，但如果余数为 $0$ 的话，就不用乘 $2$ 了。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long a[5],b[5];
int main(){
	cin>>n>>m;
	for(int i=0;i<5;i++)
	{
		a[i]=n/5; 
		b[i]=m/5;
		if(n%5>=i&&i!=0)a[i]++;
		if(m%5>=i&&i!=0)b[i]++;
	} //算出余数
	cout<<a[0]*b[0]+a[1]*b[4]+a[2]*b[3]+a[3]*b[2]+a[4]*b[1]; //乘法原理算出结果
	
	
	return 0; //完结撒花
}
```


---

## 作者：一只大龙猫 (赞：0)

设 $(x+y) \bmod 5=0$，不难发现有以下规律：

| $x \bmod 5$ | $y \bmod 5$ |
| :----------: | :----------: |
| $0$ | $0$ |
| $1$ | $4$ |
| $2$ | $3$ |
| $3$ | $2$ |
| $4$ | $1$ |

我们只需统计一下从 $1$ 到 $n$ 以及从 $1$ 到 $m$ 中各个数除以 $5$ 的余数的情况，再用乘法原理就能解决了。

我们可以开两个桶 $sum1$ 和 $sum2$ ，$sum1_i$ 表示从 $1$ 到 $n$ 中除以 $5$ 余 $i$ 的数的个数，$sum2_i$ 表示从 $1$ 到 $m$ 中除以 $5$ 余 $i$ 的数的个数，那么答案就等于

$$\sum_{i=0}^4 sum1_i \times sum2_{(5 - i) \bmod 5}$$

为什么是 $sum2$ 的下标是 $(5-i) \bmod 5$，而不是 $5-i$ 呢？不难发现当 $1 \le i \le 4$ 时，$5-i$ 确实与 $(5-i) \bmod 5$ 相等，但是当 $i=0$ 时，$5-i$ 却为 $5$，与上面我们找到的规律不符。所以我们需要将 $5-i$ 对$5$ 取模，防止这种情况发生。

那么，如何计算 $sum1_i$ 和 $sum2_i$ 呢？

下面以 $n$ 和 $sum1_i$ 举例，$m$ 与 $sum2_i$ 同理。

首先不难发现，若 $n$ 为 $5$ 的倍数时，$sum1_i$ 的值是 $\lfloor \frac{n}{5} \rfloor$。但是，如果 $n$ 不是 $5$ 的倍数呢？

这时 $sum1_i$ 的值至少是 $\lfloor \frac{n}{5} \rfloor$，但是在以下情况下，$sum1_i$ 的值为 $\lfloor \frac{n}{5} \rfloor+1$：

| $n$ 除以 $5$ 的余数 | $i$ |
| :----------: | :----------: |
| $1$ | $1$ |
| $2$ | $1,2$ |
| $3$ | $1,2,3$ |
| $4$ | $1,2,3,4$ |

容易看出 $i \neq 0$ 且 $i \bmod 5 \le n \bmod 5$。 

总结一下：

若 $n$ 为 $5$ 的倍数，此时 $sum1_i$ 为 $\lfloor \frac{n}{5} \rfloor$；

若 $n$ 不为 $5$ 的倍数，有两种情况：

1. $i \neq 0$ 且 $i \bmod 5 \le n \bmod 5$，此时 $sum1_i$ 为 $\lfloor \frac{n}{5} \rfloor+1$。

2. 否则 $sum1_i$ 为 $\lfloor \frac{n}{5} \rfloor$。

$m$ 与 $sum2_i$ 同理。

AC 代码如下：

```cpp
#include<iostream>
using namespace std;
long long n,m,sum1[5],sum2[5],ans;
int main(){
    cin>>n>>m;
    if(n%5==0){
        for(long long i=0;i<5;i++){
            sum1[i]=n/5;
        }
    }else{
        sum1[0]=n/5;
        for(long long i=1;i<5;i++){
            sum1[i]=n/5;
            if(i%5<=n%5)sum1[i]++;
        }
    }
    if(m%5==0){
        for(long long i=0;i<5;i++){
            sum2[i]=m/5;
        }
    }else{
        sum2[0]=m/5;
        for(long long i=1;i<5;i++){
            sum2[i]=m/5;
            if(i%5<=m%5)sum2[i]++;
        }
    }
    for(long long i=0;i<5;i++){
        ans+=sum1[i]*sum2[(5-i)%5];
    }
    cout<<ans;
    return 0;
}
```

虽然有些复杂，但是程序时间复杂度很低，为 $O(1)$。且常数很小，在未经 O2 优化或 I/O 优化的情况下就拿到了最优解（在写这篇题解时）。

---

## 作者：ViXpop (赞：0)

有一个卑微 afo 蒟蒻前来写题解

纯粹是想回坑练练手找了个这么个题来做，看了一眼题目以为是个暴力，再一看 $1e6$ 的数据 , $O(mn)$ 暴力不用想就知道肯定爆炸，那么就是个妥妥的数论水题了（误

既然是数论题，那么肯定有规律，通过观察样例解释我们不难发现，对于     $\bmod5$ 后结果相等的数，他们能找到的匹配数字个数是一样的,而且一个数字在一个 $T=5$ 的周期内一定可以找到一个匹配的数字
 
那不就随便乱切了，先对 $m,n$ 中较大的数字处理（这里假设是 $m$ )，找出其有几个 $T=5$ 的周期（这里假设有 $x$ 个），那么 $n$ 中的每个数至少有 $x$ 个匹配结果，至于多出来的匹配结果显然在 $m\bmod5$ 中寻找

再通过肉眼观察可发现第$i$个数只有满足条件 $m\bmod 5\geq abs(5-i)\bmod 5$ 时才存在一个匹配数字，那么结论已经出来了，分析结束

但是我为了使整个过程便于~~自己~~理解，我选择仅对第一个周期进行预处理，然后重复所有完整周期，最后对多余的不完整周期进行单独计算

上代码

```
#include <bits/stdc++.h> 
#define int long long//纯粹因为偷懒不想每个int都换long long
using namespace std;
int read(){
	char ch=' ';int res=0,f=1;
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
int n,m,num3,num4,ans=0,flag[6];
#undef int
int main()
{
	n=read(),m=read();
	if(n>m)swap(n,m);//确保m是较大的数字
	num3=m/5,num4=m%5;
	long long cmp;
	if(n>5)cmp=5;else cmp=n;//很特殊的一点是当n<5时就不需要预处理第一个完整周期了，因为一个完整周期都没有
	for(register int i=1;i<=cmp;i++){
		ans+=num3;flag[i]+=num3;
		if((num4>=abs(5-i)%5)&&(i%5))ans++,flag[i]++;
	}//对第一个周期进行预处理
	for(register int i=1;i<=5;i++)ans+=(n-5)/5*flag[i];//后面所有完整周期的答案必定和第一个周期一样
	if(n>5)for(register int i=n/5*5+1;i<=n;i++)ans+=flag[i%5];//不完整周期计算
	cout<<ans<<endl; 
	return 0;
} 
```

afo两年以来的回坑之作，代码能力基本得从头再来了，求勿喷

---

## 作者：Arvin2018 (赞：0)

看了原来唯一 一篇题解后感觉~~身体被掏空~~还有其他的方法，于是自己找了个规律：
```
m:1 2 3 4 5 6 7 8 9 -> i
n:1 2 3 4 5 6 7 8 9 10 11 -> j
      i  j         
1st:  1, 4 -- int((11+1)/5) = 2
2nd:  1, 9  /

3rd:  2, 3 -- int((11+2)/5) = 2
4th:  2, 8  /

5th:  3, 2 -- int((11+3)/5) = 2
6th:  3, 7  /

7th:  4, 1  \
8th:  4, 6 -- int((11+4)/5) = 3 
9th:  4, 11 /

······
```

看着很完美，是不是？

每一次total += int((n + i)/5) ？
# 错！
让我们接下来继续看：
```
.th:  9, 1  \
.th:  9, 6 -- int((11+9)/5) = 4????
.th:  9, 11 /
```
对吗？

其实应该是这样：
```
.th:  9, 1  \
.th:  9, 6 -- int((11+(9%5))/5) = 3
.th:  9, 11 /
```
所以最关键的代码就出来了：
```
for(int i = 1; i <= m; i++){
	total += ((n + (i%5))/5);
}
```
附上完整AC代码：
```
#include <bits/stdc++.h>
using namespace std;
int main(){
	int m, n;
	long long total = 0;
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		total += ((m + (i%5))/5);
	}
	cout << total;
	return 0;
}
```

---

