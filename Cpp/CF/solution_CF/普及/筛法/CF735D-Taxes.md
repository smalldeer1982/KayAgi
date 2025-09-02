# Taxes

## 题目描述

Mr. Funt now lives in a country with a very specific tax laws. The total income of mr. Funt during this year is equal to $ n $ ( $ n>=2 $ ) burles and the amount of tax he has to pay is calculated as the maximum divisor of $ n $ (not equal to $ n $ , of course). For example, if $ n=6 $ then Funt has to pay $ 3 $ burles, while for $ n=25 $ he needs to pay $ 5 $ and if $ n=2 $ he pays only $ 1 $ burle.

As mr. Funt is a very opportunistic person he wants to cheat a bit. In particular, he wants to split the initial $ n $ in several parts $ n_{1}+n_{2}+...+n_{k}=n $ (here $ k $ is arbitrary, even $ k=1 $ is allowed) and pay the taxes for each part separately. He can't make some part equal to $ 1 $ because it will reveal him. So, the condition $ n_{i}>=2 $ should hold for all $ i $ from $ 1 $ to $ k $ .

Ostap Bender wonders, how many money Funt has to pay (i.e. minimal) if he chooses and optimal way to split $ n $ in parts.

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
27
```

### 输出

```
3
```

# 题解

## 作者：yyyer (赞：38)

~~欸~终于发现黑色水题啦~~

### 数论

哥德巴赫猜想

分成自身为质数，大于2的偶数，大于2的奇数，需要注意奇数中拆分出2的情况。

所以答案只有1、2、3

结果决定于(n-2)是否为素数。

```cpp
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <iomanip>
#include <ios>
#include <sstream>
#include <stack>
#include <algorithm>
#include <bitset>
#include <cctype>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <utility>
#include <vector>
#include <iosfwd>
#include <cerrno>
#include <clocale>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <istream>
#include <ostream>
#include <queue>
#include <set>
#include <cwchar>
#include <cwctype>
#include <complex.h>
#include <fenv.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <tgmath.h>

//我不喜欢万能库（

//好好打头文件不好吗QAQ

using namespace std;
bool isprime(int n)//判断是不是质数
{
	if(n<2)return false;
	for(int i=2;i*i<=n;i++) if(n%i==0)return false;
return true;
}
int main()
{
	int n;
	cin>>n;
	if(isprime(n)) cout<<"1"<<endl; //n自身为质数
		else if(n%2==0) cout<<"2"<<endl; //n是偶数
			else if(isprime(n-2)) cout<<"2"<<endl; //n-2是质数
				else
					cout<<"3"<<endl; //都不满足，直接输出3
                    
	return 0; //养成打return 0; 的好习惯
}

```

---

## 作者：shenmadongdong (赞：11)

~~既然没有Pascal的题解，那本蒟蒻来水一发~~

1、n=1或n=2时，显然只用付1单位税；

2、当n为偶数时，根据哥德巴赫猜想，可以分解成两个质数；而要是不分解的话，最大公因数一定不小于2，故此时要付2单位税；

3、当n是奇数时，若n为质数，显然只用付1单位税；否则至少要付2单位税，要是n-2不是质数的话，就无法分解成两个质数，但可以分解成3+一个偶数，因此要付3单位税。

代码：
```pascal
var a,n,i,k:longint;
begin
  read(n);
  if (n=1)or(n=2) then write('1')//特判
  else if (n mod 2=0) then write('2')//当n为偶数时付2单位税
    else begin
      k:=0;
      a:=trunc(sqrt(n));
      for i:=1 to a do if (n mod i)=0 then begin k:=1; break; end;//判断是否质数
      if k=0 then begin write('1'); exit; end;//当n为质数时付1单位税
      k:=0;
      n:=n-2;
      a:=trunc(sqrt(n));
      for i:=1 to a do if (n mod i)=0 then begin k:=1; break; end;//判断是否质数
      if k=1 then write('3') else write('2');//当n-2为质数时付2单位税，否则付3单位税；
    end;
end.
```

---

## 作者：lgnotus (赞：7)

## 题目简述

某人要交税，交的税钱是收入n的最大因子（!=n，若该数是质数则是1），

但是现在这人为了避税，把钱拆成几份，使交税最少，输出税钱。

#### 举个样例方便理解题意

假设$n=6$，那么$6$可以被被拆成$3$和$3$,
因为3是质数，所以它的最大因子是1，那在$n=6$的情况，最少要缴2元。


------------
*	如果$n$为质数，那显而易见就输出1；
*	根据哥德巴赫猜想，假设这个数为偶数就一定可以拆成两个质数之和。每个质数的最大因子是$1$，所以，当$n\ \%2==0$时就输出2；
*	剩了奇数，根据（奇数-偶数=奇数），如果$(n-2)$是一个质数（因为二是一个偶数并且它是最小的质数）就输出2；
*	如以上条件都不符合，那这个数就可以被分成$3+$一个偶数，所以输出$(1+2=3)$

## 贴代码

```
#include<bits/stdc++.h>
using namespace std;
long long n;
bool prime(long long num)
{
    for(long long i=2;i*i<=num;i++)
    {
        if(num%i==0)return 0;
    }
    return 1;
}
int main()
{
    cin>>n;
    if(prime(n))cout<<1<<endl;
    else if(n%2==0)cout<<2<<endl;
    else if(prime(n-2))cout<<2<<endl;
    else cout<<3<<endl;
    return 0;
}

```

管理员们辛苦了qwq


---

## 作者：インデックス (赞：4)

### 这道题理解题意后真的不难
### 关键在于质数的判断
### ~~之前因为发现有漏洞修改了一下~~ 
### 质数定义：一个大于1的自然数，除了1和它本身外，不能被其他自然数（质数）整除
****
### 介绍几种方法
1. **遍历2以上N的平方根以下的每一个整数，是不是能整除N;(这是最基本的方法）**
2. **遍历2以上N的平方根以下的每一个素数，是不是能整除N;(这个方法是上面方法的改进，但要求N平方根以下的素数已全部知道)**
3. ** ~~打表吧~~ **
![](https://pic.baike.soso.com/ugc/baikepic2/14408/20170602194504-2046158474.jpg/0)
**可以在网上找一下**
### 判断是否为质数
```
#include<bits/stdc++.h>//万用头文件
using namespace std;
int main()
{	int a,i;
	bool flag=true;
	cin>>a;
	for(register i=2;i<=sqrt(a);++i)//只需循环到根号a，register为临时寄存器变量
		if(a%i==0)
			{flag=false;
			 break;//结束循环
			}
	if(flag==false) cout<<"no";
	else cout<<"yes";
return 0;
}
```

****
### AC代码
### ~~之前不小心CE了~~
### 记得开“long long” 和 “cout<<endl;//换行”
****
```
#include<bits/stdc++.h>//万用头文件
#pragma GCC optimize(2)//手动开O2优化
using namespace std;
bool ljzzm(long long  a)//定义bool数组
{
    int i;
	for(i=2;i<=sqrt(a);++i)//只需循环到a
		if(a%i==0)
			{return false;
			 break;//结束循环
			}
			return true;
}
int main()//主程序开始
{	
    long long  n;
    
    scanf("%lld",&n);
    
    if(ljzzm(n)){
	printf("%d",1); cout<<endl;}
    
	else if(n%2==0){printf("%d",2);cout<<endl;}
    
	else if(ljzzm(n-2)){printf("%d",2);cout<<endl;}
    
    else printf("%d",3);cout<<endl;//一定要记得换行
    
return 0;
}

```

---

## 作者：ADivT (赞：2)

这是一道非常有**水**平的黑题(~~已经变成橙题了~~)。

来讲一讲这题的思路，首先先了解一下本题的核心——**哥德巴赫猜想**：
```
1.任一大于2的偶数都可写成两个质数之和。（规定1为质数的情况下）
```
```
2.任一大于5的整数都可写成三个质数之和。
```
我们知道对于一个数n，至多也就只需要交3的税钱（由上猜想2知），故我们讨论交的税钱分别为1,2,3时的情况：
- 1： 此时该数为质数。
- 2：这个数为偶数（据猜想1）或这个数减2为质数。
- 3：其余情况。

由此，我们可以写出代码：
```cpp
#include<bits/stdc++.h>

bool prime(int a) {
	for(int i=2; i*i<=a; ++i)
		if(a%i==0) {
			return 0;
		}
	return 1;
}
int main() {
	int n;
	scanf("%d",&n);
	if(prime(n))printf("%d\n",1);
	else if(n%2==0||prime(n-2))printf("%d\n",2);
	else printf("%d\n",3);
	return 0;
}
```
## 完结撒花,谢谢观看。


---

## 作者：wurzang (赞：1)

根据哥德巴赫猜想，一个偶数可以被分解成两个质数，于是偶数的答案就是 $2$...如果这个偶数是质数的话（即 $2$ 的情况），那么答案是 $1$，特判即可。

根据哥德巴赫猜想，任意一个数都可以拆分为 $3$ 个质数之和，所以答案至多是 $3$。

如果 $n$ 是奇数且 $n-2$ 是质数的话，答案显然是 $2$。否则答案就是 $3$。

至于如何判断质数，直接 `Miller_Rabin` 一发即可。

~~什么$\mathcal{O}(\sqrt{n})$判断质数我没有听说过我没有~~


代码如下：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll rankdom(ll l,ll r){
	ll res=(ll)INT_MAX*rand();
	if(res<0) res=-res;
	return res%(r-l+1)+l;
}
ll gsc(ll a,ll b,ll mod){
	ll res=0;
	while(b){
		if(b&1) res=(res+a)%mod;
		a=(a+a)%mod;b>>=1;
	}
	return res;
}
bool check(ll a,ll mod){
	ll n=mod-1,res=1,now;
	a=(a%mod+mod)%mod;
	if(a==0) return 1;
	while(n){
		if(n&1) res=gsc(res,a,mod);
		now=a; a=gsc(a,a,mod); n>>=1;
		if(a==1&&now!=mod-1&&now!=1) return 0;
	}
	if(res!=1) return 0;
	return 1;
}
bool prime(ll x){
	for(int i=1;i<=10;++i){
		ll a=rankdom(1,x-1);
		if(check(a,x)==0) return 0;
	}
	return 1;
}
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}
int main(){
	srand(time(0));
//	freopen("taxes.in","r",stdin);
//	freopen("taxes.out","w",stdout);
	long long n;
	int T;T=1;
	while(T--){
		read(n);
		if(n==2||n==1){
			write(1);puts("");continue;
		}
		if(n%2==0) write(2);
		else{
			if(prime(n)) write(1);
			else if(prime(n-2)) write(2);
			else write(3);
		}
		puts("");
	}
	return 0;
}
```


因为 $n$ 过大直接用了龟速乘。这种做法可以适用于 $n \leq 10^{18}$  的情况。

---

## 作者：SqrtSecond (赞：1)

这道题也很简单。

易知，$n$最好是分解成几个质数。

则若$n$为质数，那么就不用分成几份，直接输出$1$即可。

如果$n$不为质数，那么根据哥德巴赫猜想，若$n$为偶数，则$n$可以拆分成两个质数，输出$2$。

如果都不行的话，即$n$为奇数，那么同理，$n$可以拆分成三个质数之和,输出3。

于是我写出了如下的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}//快读
bool prime(int n)
{
	int k=sqrt(n);
	for(int i=2;i<=k;++i)
	if(n%i==0)return false;
	return true;
}
int n;
int main()
{
	n=read();
	if(prime(n)){
		printf("1");return 0;
	}
	if(n%2==0){
		printf("2");return 0;
	}
	printf("3");
	return 0;
}
```
但是这段代码WA了。

后来我又分析了一下，才发现即使$n$为奇数且$n$不是质数，也可能分解成2与另一个质数的和。

AC代码如下：
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}//快读
bool prime(int n)
{
	int k=sqrt(n);
	for(int i=2;i<=k;++i)
	if(n%i==0)return false;
	return true;
}//判断是不是质数 
int n;
int main()
{
	n=read();
	if(prime(n)){
		printf("1");return 0;
	}
	if(n%2==0||prime(n-2)){
		printf("2");return 0;
	}
	printf("3");
	return 0;
}
```
# The end

---

## 作者：xujian (赞：1)

本题思路：哥德巴赫猜想，具体的就不深进行解释了。

## 本篇主要引申介绍一下质数的判定方法。

首先是最基础的$O(n)$的算法了，直接从2枚举到n减1，判断是否有数可以被整除。

代码：
```
bool zs(int x){
    for(int i=2;i<x;i++)
        if(x%i==0)return false;
    return x>1;
}
```
经过稍稍思考便可以发现，在2~n-1内即使有质数，就会成对出现，即可优化成$O(\sqrt{n})$的算法。

代码：
```
bool zs(int x){
    for(int i=2;i<=sqrt(x);i++)
        if(x%i==0)return false;
    return x>1;
}
```
再进行深入拓展，便可发现，一个数若除6的余数不为1且不为5，则也不是质数。据此，代码的速度又可以提高大约3倍。

代码：
```
bool zs(int num){
    if(num==2||num==3)return 1;
    if(num%6!=1&&num%6!=5)return 0;
    int tmp=sqrt(num);
    for(int i=5;i<=tmp;i+=6)
        if(num%i==0||num%(i+2)==0)return 0; 
    return 1;
} 
```

最后是终极版本，可以根据质数密度，将质数进行预处理，会更快一些。代码复杂度约为$O(\frac{\sqrt{n}}{log(n)})$

代码：
```
bool zs(int x){
    if(x<2)return 0;
    rg int sqrtx=sqrt(x+1);
    for(rg int i=1;pr[i]<=sqrtx&&i<=len;i++)
    if(x%pr[i]==0)return 0;
    pr[++len]=x;
    return 1;
}
```
说了这么多，有兴趣的同学还可以去了解更深奥的算法，如米勒-拉宾等。

接下来是本题的代码。

```
#include<bits/stdc++.h>
using namespace std;
bool zs(int num){
    if(num==2||num==3)return 1;
    if(num%6!=1&&num%6!=5)return 0;
    int tmp=sqrt(num);
    for(int i=5;i<=tmp;i+=6)
        if(num%i==0||num%(i+2)==0)return 0; 
    return 1;
}
int main(){
	long long n;
	cin>>n;
	if(zs(n))cout<<1;
    else if(n%2==0)cout<<2;
    else if(zs(n-2))cout<<2;
    else cout<<3;
	return 0;
}
```

### 感谢您的阅读，若有疑问，欢迎指出。

---

## 作者：Smallbasic (赞：1)

## 终于找到一道不水的黑题了，做着真爽

我A的第一道黑题

其实这题挺难的，说简单的各位谁能证明它？反正我确信我已经找到了一种美的证法，可惜这里空间太小，写不下。

废话少说，其实这题是关于哥德巴赫猜想的题的。

首先，这题可以分为几种情况：

当$n$为素数时，显然答案为$1$。重点来讨论$n$为合数时的情况。

根据哥德巴赫猜想，任何一个充分大的偶数都能分解成两个素数之和，因此$n$为偶数时，答案为$2$。

当$n$为奇数时，因为$\text{奇数-偶数=奇数}$，而唯一的偶质数为$2$，所以若$n-2$时素数，答案也为$2$

其他情况，$n$都可以被分解为$3+$一个偶数，因此答案为$3$。

壮哉我大$JAVA$:

```java
import java.util.*;

class Prime {
	public boolean isprime(int n) {
		if (n == 2) return true;
		if (n == 1) return false;
		for (int i = 2; i * i <= n; i++) if (n % i == 0) return false;
		return true;
	}
}


public class First extends Prime{
	int n;
	
	public First() {
		Scanner sc = new Scanner(System.in);
		this.n = sc.nextInt();
	}
	
	public static void main(String[] args) {
		First a = new First();
		System.out.println(a);
	}
	
	public String toString() {
		if (super.isprime(n)) return "1";
		else if (n % 2 == 0 || super.isprime(n - 2)) return "2";
		return "3";
	}	
}
```

本地无误，洛谷上老是UKE。。。

---

## 作者：⚡进击_蒟蒻⚡ (赞：1)

根据哥德巴赫猜想，分成自身为质数，大于2的偶数，大于2的奇数，需要注意奇数中拆分出2的情况。

于是，得到答案1，2，3。

结果决定于(n-2)是否为素数。

~~上一波代码狂潮。~~

```cpp
#include<iostream>
using namespace std;
bool isPrime(int x){
    for(int _i=2;_i*_i<=x;_i++){
        if(x%_i==0)return false;
    }
    return true;
}
int main(){
    int x;
    cin>>x;
    if(isPrime(x)){cout<<"1";return 0;}
    if(x%2==0){cout<<"2";return 0;}
    if(isPrime(x-2)){cout<<"2";return 0;}
    cout<<"3";
    return 0;
}
```


---

## 作者：YUYGFGG (赞：0)

$update\space 2020.7.21$ 修了一些手滑，把漏加的$\LaTeX$加上了，补充了一句话

解题的关键是这一句话
> 若该数是质数则是$1$

所以判断一

- 自身是质数 $ans=1$

我们要尽量多拆出质数，有关拆出质数的理论（猜想）有啥？对!**哥德巴赫猜想**!

猜想告诉我们：一个大于$2$的偶数可以拆分成$2$个质数之和（本题中即税费为$2$）。

所以判断二

- 大于二的偶数 $ans=2$

奇数可以拆成$1$和$n-1$两个数，税费分别是$1$和$2$，和为$3$，不过如果$n-2$为质数税费是$2$（拆成$n-2$和$2$，代价都是$1$，和为$2$）

所以判断三和四

- 大于$2$但$n-2$为质数 $ans=2$

- 大于$2$但$n-2$不为质数 $ans=3$

最后$n=1$那$ans$自然也是$1$啦

汇总一下

- 自身是质数 $ans=1$

- 大于二的偶数 $ans=1$

- 大于$2$但$n-2$为质数 $ans=2$

- 大于$2$但$n-2$不为质数 $ans=3$

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
bool isprime(int n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0) return false;
    }
    return true;
}
int main(){
    int n,m;
    cin>>n;
    if(isprime(n)){
        cout<<1<<endl;
        return 0;
    }
    if(n%2==0){
        cout<<2<<endl;
        return 0;
    }
    if(n%2==1){
        if(isprime(n-2)) cout<<2<<endl;
        else cout<<3<<endl;
        return 0;
    }
    if(n==1) cout<<1<<endl;
    return 0;
}
```


---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/07/30/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces735D%20Taxes)

### Solution

1. 当$n$为素数时，显然答案为$1$；

1. 当$n$为偶数时，可以分成两个素数，也就是两个$1$，所以答案为$2$；

1. 当$n$为奇数且$n - 2$为素数时，也就是它能分成两个素数，也就是两个$1$，所以答案也是$2$；

1. 当$n$为奇数且$n - 2$不是素数时，可以分成$3$和一个偶数，偶数又可以分成$2$个素数。所以总共分成了$3$个素数，因此答案为$3$。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

int n;
inline bool check(int x) {//判断素数
    if (x < 2) return 0;
    for (int i = 2; i <= (int)sqrt(x); i++)
        if (x % i == 0) return 0;
    return 1;
}
int main() {
    scanf("%d", &n);
    if (check(n)) {
        printf("1\n");
        return 0;
    }
    if (!(n & 1) || check(n - 2)) printf("2\n"); else printf("3\n");//这里使用快速幂，应为!的优先级比&高所以必须加括号
    return 0;
}
```

---

## 作者：wzm2007 (赞：0)

    如果n为质数,那就输出1
    根据哥德巴赫猜想，假设这个数为偶就可以分成两个质数之和。每个质数的最大因子是1,所以,若n%2==0时输出2
    若为奇,如果n-2是一个质数就输出2；
    若都不符合，输出3

------------

    #include<bits/stdc++.h>
    using namespace std;
    int isprime(int x)  //判断质数的函数
    {
        int t=sqrt(x);
        for(int i=2;i<=t;i++)
            if(!(x%i))return 0;
        return 1;
    }
    int main()
    {
        int n;
        cin>>n;
        if(isprime(n))cout<<1;  //是质数
        else if(!(n%2))cout<<2;  //偶数
        else if(isprime(n-2))cout<<2;
        else cout<<3;  //都不符合
        return 0;
    }

---

## 作者：Catreap (赞：0)

判断质数就行了

一个判断质数的函数证明：
令x≥1，将大于等于5的自然数表示如下：
······${{6x-1}}$ ，${{6x}}$，${{6x+1}}$，${{6x+2}}$，${{6x+3}}$，${{6x+4}}$，${{6x+5}}$，${{6(x+1)}}$，${{6(x+1)+1}}$ ······
可以看到，不在6的倍数两侧，即6x两侧的数为${{6x+2}}$，${{6x+3}}$，${{6x+4}}$，由于${{2(3x+1)}}$，${{3(2x+1)}}$，${{2(3x+2)}}$，所以它们一定不是素数，再除去${{6x}}$本身，显然，素数要出现只可能出现在6x的相邻两侧。这里要注意的一点是，在6的倍数相邻两侧并不是一定就是质数。

此时判断质数可以6个为单元快进，循环中只需要考虑${{6i-1}}$和${{6i+1}}$的情况，即循环的步长可以定为6，每次判断循环变量${{k}}$和${{k+2}}$的情况即可。

```cpp
bool Prime(ll num) {//判断质数函数 最好开long long
    if(num==0 || num==1) return 0;//0,1特殊判断
    if(num==2 || num==3) return 1;//2,3打表判断
    if(num%6!=1 && num%6!=5) return 0;
    ll tmp=sqrt(num);//开方
    for(ll i=5; i<=tmp; i+=6) {//6个为单元快进
        if(num%i==0 || num%(i+2)==0) return 0;
    }//考虑6i-1和6i+1的情况
    return 1;//质数！QwQ
}
```

哥德巴赫猜想

若为质数，直接输出1;

若n-2为质数或能被2整除，输出2;

否则，输出3。

附上~~高清无码~~代码

## Code
```cpp
#include<cstdio>
#include<cmath>
#define ll long long
#define SIZE 100000
bool Error=0;
inline char nc() {
#ifdef WIN32
    return getchar();
#endif
    static char buf[SIZE],*p1=buf+SIZE,*pend=buf+SIZE;
    if (p1==pend) {
        p1=buf,pend=buf+fread(buf,1,SIZE,stdin);
        if (pend==p1) {
            Error=1;
            return -1;
        }
    }
    return *p1++;
}
inline void read(ll &x) {
    bool sign=0;
    char ch=nc();
    x=0;
    for (; ch==' '||ch=='\n'||ch=='\r'||ch=='\t'; ch=nc());
    if (Error)return;
    if (ch=='-')sign=1,ch=nc();
    for (; ch>='0'&&ch<='9'; ch=nc())x=x*10+ch-'0';
    if (sign)x=-x;
}
bool _____(ll ___) {
    if(___==0 || ___==1) return 0;
    if(___==2 || ___==3) return 1;
    if(___%6!=1 && ___%6!=5) return 0;
    ll ____=sqrt(___);
    for(ll i=5; i<=____; i+=6) {
        if(___%i==0 || ___%(i+2)==0) return 0;
    }
    return 1;
}
int main(int argc,char *argv[]) {
	ll ________________;
	read(________________);
	if(_____(________________)) printf("1\n");
	else if(!(________________%2)) printf("2\n");
	else if(_____(________________-2)) printf("2\n");
	else printf("3\n");
	return 0;
}
```

---

## 作者：k2saki (赞：0)

若为质数，直接输出1;

若n-2为质数，或能被2整除，输出2;

否则，输出3。

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int zs(int n)//判断质数
{
    if(n==1) return 0;
    if(n==2) return 1;
    for(int i=2;i<=sqrt(n);++i)
    {
        if(n%i==0) return 0;
    }
    return 1;
}
int main(){
    int n;
    cin>>n;
    if(zs(n)) cout<<1<<endl;//判断是否为质数
    else if(n%2==0) cout<<2<<endl;//模2是否为零
    else if(zs(n-2)) cout<<2<<endl;//n-2是否为质数
    else cout<<3<<endl;
}
```

---

## 作者：CobaltChloride (赞：0)

```
直接上代码
#include<bits/stdc++.h>
using namespace std;
long long n,i;
int fun(int m){
    if(m<=1) return 0;
    for(i=2;i<=sqrt(m);i++) if(m%i==0) return 0;
    return 1;
}//质数判断 
int main(){
    cin>>n;
    if(n<=2){
    	cout<<1;
    	return 0;
    }//特判
    if(fun(n)) cout<<1;//质数的最大因子为1 
    else if(!(n&1)) cout<<2;//哥德巴赫猜想:任一大于2的偶数都可写成两个质数之和
    else if(fun(n-2)) cout<<2;//有些奇数可拆成2与另一质数 
    else cout<<3;//否则就拆成1与偶数 
    return 0;
}
```

---

## 作者：FCB_Yiyang2006✈ (赞：0)

# **恶意评分的人给我站出来**
黑水题（至少本蒟蒻这样认为）

提供两种思路，本人更喜欢第一种。
## 思路1：不用函数和高级算法（用了我也不懂，呵呵）只用用双重循环，足矣！！！

分解质因数，找出最大因数即可。。。

上这个注释有点奇葩的C++d代码
```cpp
#include<bits/stdc++.h>//万能脑袋 
using namespace std;
int n,k=2,maxn=1;
//n指收入
//k是循环变量，表示质因数，最小质数为2，所以初始值为2。
//maxn指最大因数（也就是税款），如果是质数，输出本身（初始赋值）。 
int main()//主晗二叉树 
{
	cin>>n;//鼠入 
	do
	{
		while(n%k==0)//如果是因数 
		{
			if(k>maxn&&k!=n)//如果它比最大因数还大且不是本身 
			{
				maxn=k;
			}
			n/=k;//每次都除掉这个因数 
		}
		k++;
	}
	while(n!=1);// 结束条件 
	cout<<maxn;//鼠出税款 
	return 0;//结束了！结束了！结束了！
	 
}
```
## 思路2：暴力枚举+判断质数
上代码
```cpp
#include<bits/stdc++.h>//万能脑袋 
using namespace std;
int n,maxn=1;
bool prime(int a)
{
	for(int i=2;i<=sqrt(a);i++)
	{
		if(a%i==0)
		{
			return false;  
		}
	}
	return true;  
}//判断质数 
int main()//低调的主函数 
{
	cin>>n;
	for(int i=1;i<=sqrt(n);i++)
	{
		if(n%i==0&&prime(i)==true&&i>maxn)
		{
			maxn=i;	
		}
	}
	cout<<maxn;//鼠出 
	return 0;//结束了 
}
```
最后......
# 重要的事情说三遍：不要抄题解！不要抄题解！！不要抄题解！！！



---

