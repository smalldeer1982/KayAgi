# n^p mod m

## 题目描述

求 $n^p$ $mod$ $m$ 的值

## 说明/提示

对于100%的数据 $1≤n,m≤10^9$ $1≤p≤10^{14}$

翻译提供者：Ryan_wxn_

## 样例 #1

### 输入

```
12 15 7```

### 输出

```
3```

## 样例 #2

### 输入

```
123456789 234567894 6574837563712```

### 输出

```
120678297```

# 题解

## 作者：ShineEternal (赞：117)

~~既然没人，我来写吧~~


------------
# 显然，这是一道同余问题。



------------
## 针对此题，我先来举个栗子。
### 以下的=代表同余（蒟蒻不会打同余符号）

如何求3^89 mod 7呢？

3^1=3(mod 7)

3^2=3^2(mod 7)=2(mod 7)

3^4=(3^2)^2(mod 7)=2^2(mod 7)=4(mod 7)



------------
## 请谅解，实在太长了，之后的mod 7省略了。

3^8=(3^4)^2=4*2=2=2；

3^16=(3^8)^2=2^2=4;

3^32=(3^16)^2=4^2=2;

3^64=(3^32)^2=2^2=4;

3^89=(3^64)(3^16)(3^8)(3^1)=4x4x2x3=96=5;(没错，x是乘号。。。）

------------
## 下面开始文字解说 

所以，首先将p分解成2的幂次方，存放在一个数组r中，r【i】=1表示有n^i这一项。然后用递推的方法从小到大逐个求出n^i mod m 的值（j从i到1）存放在数组d中。



------------

## 然而，我们还可以利用以下递归公式进行求解：

x^y=

1、1(如果y=0)

2、x*x^(y-1)  (如果y是基数）

3、(x^2)^(y div 2)  (如果y是偶数)



### 刚才的div是除法的意思'/'

### 即y div 2=y/2；


------------
#### 也就是递归地对n进行二进制分解，同时计算。等价于将表达式分解成下面的形式：


------------
# 前方高能，做好准备！！！


------------
3^89

=(3^44)^2*3

=((3^22)^2)^2*3

=(((3^11)^2)^2)^2*3

=((((3^5)^2*3)^2)^2)^2)*3

=(((((3^2)^2*3)^2)^2)^2)*3



------------
###### 讲解结束，下面就是大家期待的代码 


```
#include<cstdio>
using namespace std;
long long m,n,p;
int main()
{
	scanf("%lld%lld%lld",&n,&m,&p);
	//n^p%m
	int ans=1;
	for(;p;p>>=1,n=n*n%m)
	{
		if(p&1)
			ans=ans*n%m;
	} 
	printf("%d\n",ans);
	return 0;
}
```

求过求赞

---

## 作者：weak_ddb (赞：22)

### 这就是一道典型的快速幂模板

以下是快速幂的全部推导过程：

$a$的$b$次方对$p$取模

每一个十进制数$b$都可以表示为$k$位的二进制数。

则$b=c_k2^{k-1}+c_{k-1}2^{k-2}+...+c_12^0$

可以推出

$a^b=a^{c_k*2^{k-1}}*a^{c_k*2^{k-2}}*...*a^{c_0}*2^0$

位数$k=log_2(b+1)$向上取整

而且 $a^{2^i}=(a^{2^{i-1}})^2$

在运算中我们要遍历所有的$c_i$

所以代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,p,m;
int main()
{
    cin>>n>>m>>p;
    ll ans=1;
    while(p>0)
	{
        if(p&1)ans=ans*n%m;
        p=p/2;
        n=n*n%m;
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：蕙兰居士 (赞：7)

当一进来（kan ti mu）的时候，我~~就知道是模版快速幂取余运算那题的翻版~~，且有异曲同工之妙，于是似乎明白了些什么：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m,p;
    cin>>n>>m>>p;
    long long sum=n%m*n%m,jsq=1;
    n%=m;
    while(sum!=n){
        sum*=n;
        sum%=m;
        jsq++;
    }
    sum=1;
    for(long long i=1;i<=p%jsq;i++){
        sum*=n;
        sum%=m;
    }
    cout<<sum%m<<endl;
    return 0;
}

```
结果——2个点T掉了——呜呜～
## 后来，我反思了一下（原来要用递归！a^bc=a^b·a^c!）
### 于是，代码君出现——
```
#include<bits/stdc++.h>
using namespace std;
long long n,p,m;
long long mi(long long x){
    if(x==0)
        return 1;
    long long ss=mi(x/2);
    if(x%2==1)
        return ss%m*ss%m*n%m;
    return ss%m*ss%m;
}
int main(){
    cin>>n>>m>>p;//一定要注意顺序！
    cout<<mi(p)%m<<endl;//一定要加换行！不然全WA！
    return 0;
}

```

---

## 作者：ueettttuj (赞：5)

嗯???本题都是快速幂的解法???那本蒟蒻来分享欧拉定理的解法

前置知识：欧拉函数，欧拉定理 ~~(不会请自行学习)~~

由欧拉定理的扩展可知：

 $n^p\  \ mod\ \ m=\begin{cases}n^p\ \ mod\ \ m&p\leqslant\varphi(m)\\n^{p\ mod\ \varphi(m)\ +\varphi(m)\ }\ mod\ \ m&p>\varphi(m)\end{cases}$ 
 
所以我们可以先算出$\varphi(m)$ ，再通过欧拉定理的推论算出答案。

贴代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,p,phi,mod;
long long poww(long long x,long long y){ //快速幂 
	long long anss=1,res=x;
	while(y){
		if(y%2) anss=anss*res%mod;
		res=res*res%mod;
		y>>=1;
	}
	return anss;
}
int main(){
	scanf("%lld %lld %lld",&n,&m,&p);
	mod=m;
	phi=m;
	for(long long i=2;i*i<=m;i++){
		if(m%i==0){
			phi=phi/i*(i-1);
			while(m%i==0) m/=i;   //算出 phi(m) 
		}
	} 
	if(m>1) phi=phi/m*(m-1);
	if(p>=phi) printf("%lld\n",poww(n,p%phi+phi));  //运用欧拉定理的推论 
	else printf("%lld\n",poww(n,p));
	return 0;
}
```
虽然在此题直接快速幂也能过。但是如果指数很大，可以用这种方法将指数缩小到容易计算的范围。

[推荐题目](https://www.luogu.org/problem/P5091)

---

## 作者：空城旧梦— (赞：5)

## 还是少不了pascal滴
这是一道的的确确的快速幂，本题有中文版模板题P1226

这种算法在复赛还是会用到的而且2017年pascal语言的初赛也考了程序填空，所以不懂的同学还是要抓紧学起来啦

快速幂简单来说就是将指数进行二进制分解

见例

  3^10
  
=(3^5)^2

=((3^2)^2×3)^2

下面详看代码

```pascal
var  n,m,p,ans,k:int64;//由于数据很大需要用int64且要用快速幂
begin
  readln(n,m,p);
  ans:=1;
  k:=n;//初始化
  while  p>0  do
    begin
      if  p mod 2=1  then//有余数就提取当前的数先乘，取模
        ans:=ans*k mod m;
      p:=p div 2;//指数向下取整
      k:=k*k mod m;//注意乘数也要mod不然就炸了
    end;
  writeln(ans);
end.

```

---

## 作者：jbc392 (赞：4)

此题就是快速幂取模

先简单讲一讲快速幂

首先，快速幂的目的就是做到快速求幂，假设我们要求a^b,按照朴素算法就是把a连乘b次，这样一来时间复杂度是O(b)也即是O(n)级别，快速幂能做到O(logn)，快了好多好多。它的原理如下：

　　假设我们要求a^b，那么其实b是可以拆成二进制的，该二进制数第i位的权为2^(i-1)，例如当b=11时

　　　　　　　　　　　　　　　　　　　　　　　　　　   a11=a(2^0+2^1+2^3)
                             
　　11的二进制是1011，11 = 2³×1 + 2²×0 + 2¹×1 + 2º×1，因此，我们将a¹¹转化为算 a2^0   *   a2^1   *   a2^3，也就是a1* a2* a8 ，看出来快的多了吧原来算11次，现在算三次，但是这三项貌似不好求的样子....不急，下面会有详细解释。                                
  
  由于是二进制，很自然地想到用位运算这个强大的工具：&和>>     &运算通常用于二进制取位操作，例如一个数 & 1 的结果就是取二进制的最末位。还可以判断奇偶x&1==0为偶，x&1==1为奇。 >>运算比较单纯,二进制去掉最后一位，不多说了，先放代码再解释。
  
  ```
int poww(int a, int b) {
    int ans=1,base=a;
    while(b!=0){
        if (b & 1 != 0)
            ans *= base;
            base *= base;
            b >>= 1;
    }
    return ans;
}
```
代码很短，死记也可行，但最好还是理解一下吧，其实也很好理解，以b==11为例，b=>1011,二进制从右向左算，但乘出来的顺序是 a^(2^0)* a^(2^1)* a^(2^3)，是从左向右的。我们不断的让base*=base目的即是累乘，以便随时对ans做出贡献。

　　其中要理解base* =base 这一步：因为 base* base==base2，下一步再乘，就是base2* base2==base4，然后同理  base4*  base4=base8，由此可以做到base-->base2-->base4-->base8-->base16-->base32.......指数正是 2^i ，再看上面的例子，a¹¹= a1* a2* a8，这三项就可以完美解决了，快速幂就是这样。
  
  
### 于是可得以下AC代码

```
#include<bits/stdc++.h>
using namespace std;
long long n,m,p;
long long quick_pow(){
    long long ans=1;//记录结果
    while(p){
        if(p%2){//如果p%2是1，那么我们的结果是要参与运算的
            ans*=n;
            ans%=m;
        }
        p/=2;//每次除以2
        n=n*n%m;//不断的加倍
    }
    return ans%m;
}
int main(){
    cin>>n>>m>>p;
    cout<<quick_pow()<<endl;
    return 0;
}
```


---

## 作者：醉梦未苏 (赞：4)

> # 快速幂

~~发现没有$python$题解，为广大$py$党提供优质代码~~

关于快速幂的思想，自己看书去吧~

蒟蒻只提供具体实现方法~~(就是代码)~~
```python
#输入
n,m,p=map(int,input().split(' '))
#初始化
ans=1
while p>0 :
    if(p%2==1):
        ans=ans*n%m
    #注意!!!此处要有`//`(即div),用'/'就错了
    p=p // 2
    n=n*n%m
#输出
print (ans)
```

> ~~看在稀有语言上，求过~~

---

## 作者：Jelly_Goat (赞：1)

好吧  
这里题解详细一点的空空如也......  
那我说一下快速幂的经典做法。

---------

定义：$quickpow=a^k(mod\space p)$
### 先说利用二进制的循环做法：
这个二进制的循环做法是指：  
将k拆分成二进制，然后分部分乘起来。  
#### 举个小栗子：
比如$2^{10}$, 可以拆分成$2^{(1010)_2}$,我们将二进制转换成十进制，即  
$2^{8\times 1+4\times 0+2\times 1+1\times 0}$
于是换一个表达方式即$2^{8\times 1}\times 2^{4\times 0}\times 2^{2\times 1}\times 2^{1\times 0}$。  

我们可以从最低位开始，先初始化`ans=1`
1. 求出`k%2`（可以用位运算优化成`k&1`），如果是1，就将`ans*=a^当前二进制位`
2. 换到下一个位，即`k>>1,a=a*a`。

反复执行上面的操作，直到k被移成0。  
代码还是挺短的qwq  
**Code:**
```cpp
typedef long long int lli;
lli quick_pow(lli a,lli p,lli mod)
{
    lli res=1;
    while (p)
    {
        if (p&1)res=res*a%mod;
        a=a*a%mod;
        p>>=1;
    }
    return res;
}
```

------

### 然后是分治的递归算法
~~就是上面的变种。~~  
我们将k拆开，然后算左边，右边，最后乘起来，就完成了。  
~~最菜的小金羊学不会写这种代码~~

--------

**注：数据有毒！**  
我和同机房的GRY_4524dalao都中招了QAQ  
注意：最后数据输出一定要加一个换行，这玩意吃换行w......  
另外，还要注意数据的数据顺序和实际操作顺序不匹配！  
（毒翻译+毒评测=全WA）

-------

最后放上我的AC代码：
```cpp
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long int lli;

inline lli quick_pow(lli a,lli k,lli mod)
{
	lli ans=1;
	while (k)
	{
		if (k&1)ans=ans*a%mod;
		a=a*a%mod;
		k>>=1;
	}
	return ans;
}

int main()
{
	lli n,p,m;
	scanf("%lld%lld%lld",&n,&m,&p);
	printf("%lld\n",quick_pow(n,p,m)%m);
	return 0;
}
```

---

## 作者：人间凡人 (赞：1)

这道题就是一道**快速幂**的模板题呀！

我就来举一个例子 : 5^10=(5^5)^2=((5^2)^2×5)^2

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,p,ans;
int main() {
	scanf("%lld%lld%lld",&n,&p,&m);
	ans=1;
	while(m){
		if(m%2==1)ans=ans*n%p;
		n=n*n%p;
		m/=2;
	}
	printf("%lld\n",ans);
	return 0;
}

```

推荐题目：[【模板】快速幂||取余运算](https://www.luogu.org/problem/P1226)

---

## 作者：moqizhu2005 (赞：0)

# 一道模板题
### 原题：[P1226 【模板】快速幂||取余运算](https://www.luogu.org/problemnew/show/P1226)
## 原理：a的（b * c）次方=a的b次方 * a的c次方
###### 代码如下
```cpp
#include<iostream>
using namespace std;
long long b,p,t;
long long f(long long o)
{
	if(o==0)
		return 1;
	long long x=f(o/2)%t;
	long long ans=x*x%t;
	if(o%2==1)
		ans=ans*b%t;
			return ans;
}
int main()
{
	cin>>b>>t>>p;
	cout<<f(p)<<endl;
	return 0;
}
```


---

## 作者：leozhang (赞：0)

快速幂是分治思想的一个经典应用，整数快速幂可以推广到矩阵快速幂等更诡异的地方

所以什么是快速幂？

我们知道，a^p=(a^(p/2))^2=(a^2)^(p/2)（p为偶数）

于是我们可以将a变为a^2,将p变为p/2，那么表达式与原来等价

至于p是奇数的情况，a^p=(a^2)^(p/2)·a，（其中p/2向下取整）

那么我们用ans累计外面丢掉的a，剩下的继续处理即可

由于每次将p变成p/2，所以时间复杂度O（log2p）

建议写成模板，不建议使用递归（否则矩阵快速幂递归的常数你是可以想象的
...）

```cpp
#include <cstdio>
#define ll long long
ll n,m,p;
ll pow_mul()
{
	ll ans=1;
	while(p)
	{
		if(p%2)
		{
			ans*=n;
			ans%=m;
		}
		p/=2;
		n*=n;
		n%=m;
	}
	return ans%m;
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&p);
	printf("%d\n",pow_mul());
	return 0;
}
```

---

