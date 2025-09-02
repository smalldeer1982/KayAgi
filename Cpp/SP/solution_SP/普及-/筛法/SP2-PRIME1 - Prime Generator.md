# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5```

### 输出

```
2
3
5
7

3
5```

# 题解

## 作者：子谦。 (赞：41)

# 入门难度？？？
你们怕是在逗我？

再怎么样也是普及-的好吧

下面那些完全是在逗你们吧，全靠~~数据水~~A掉可不是个好习惯

先来说一下做法，首先一看数据范围就应该能知道直接筛肯定是不行的，下面那些直接强行一个一个判素数的更是不可能的好吧。$O(n\sqrt n)$的复杂度不是乱来的好吧。那么当然还是筛，但是不能把1~$10^9$这范围内的数全部筛出来，而是先筛$\sqrt n$的，也就是先筛个35000就OK。因为一个数的除1以外的最小因数一定是一个不大于根下它的一个质数，所以用筛出来的这些质数，就可以排除1~$10^9$内所有的合数了。

下放代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=35000;
int n,x,y,pri[10000],pr;
bool p[maxn];
void sss(){//线性筛，筛出所需的所有素数
	for(int i=2;i<=maxn;i++){
		if(!p[i])pri[pr++]=i;
		for(int j=0;j<pr&&i*pri[j]<maxn;j++){
			p[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
}
void shai(int m){//判素数（用素数判要快得多）
	if(m==1)return;
	int z=sqrt(m);
	for(int i=0;i<pr&&pri[i]<=z;i++)
		if(m%pri[i]==0)return;//明确非素数后就返回
	printf("%d\n",m);
}
int main(){
	sss();
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		for(int j=x;j<=y;j++)
			shai(j);
		printf("\n");
	}
	return 0;
}
```
## **不喜勿喷**

**谢谢观看**

---

## 作者：wzm2007 (赞：9)

    #include<bits/stdc++.h>
    using namespace std;
    int prime(int x)
    {
        int t=sqrt(x);
        for(int i=2;i<=t;i++)
            if(x%i==0)return 0;
        return 1;
    }
    int main() 
    {
        int n,x,y;
        cin>>n;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&x,&y);
            for(int j=x;j<=y;j++)
                if(prime(j)&&j!=1)printf("%d\n",j);
            cout<<endl;
        }
        return 0;
    }

---

## 作者：Violette (赞：7)

这道题的数据是不是有点水啊？

总之，思路就是写一个判断素数的函数，

注意：1.要特判1！

2.减少时间复杂度，判断到sqrt(a)即可！

3.一定要全部判断完再返回true！

最后压一下行应该20行可以搞定。。

附上代码吧

```cpp
#include<iostream>
using namespace std;
int x,y;
int n;
bool prime(int a)
{
	if(a==1) return false;//特判一下。。 
	for(int i=2;i*i<=a;i++)
	{
		if(a%i==0) return false;
	}
	return true;
}
int main() 
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		for(int j=x;j<=y;j++)
		{
		if(prime(j)) cout<<j<<endl;
		}
		cout<<endl;//用puts("")也ok 
	}
	return 0;
}

```

本人可能有点懒，不想打缩进。。。

p.s.最近迷上了做SPOJ的题目，嘻嘻

---

## 作者：HPXXZYY (赞：4)

思路：首先看一个定理：任何合数a都有一个不超过$\sqrt a$的质因子，所以n到m中的所有合数都有至少一个小于等于$\sqrt m$的质因子

证明：若原命题不成立，则一定存在两个质数b和c，使$c> \sqrt a$，$b> \sqrt a$，且 $b\times c=a$,但$b\times c>a$，所以原命题成立！

算法：1、求1到40000间的所有质因子

2、用这些质因子去塞除n到m中的合数

3、输出n到m中的所有质数

代码（有解释）：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=40100;
const int M=40000;
const int L=1e5+1e3;
int n,m,a[N],tot,i;
bool b[N],v[L];
int test_number,j;
void get_all_the_prime(){
	memset(b,true,sizeof(b));
	b[0]=b[1]=false;//0和1不是质数 
	for(int i=2;i<=M;i++)
	if (b[i]){
		a[++tot]=i;//把所有质数都放入a数组 
		for(int j=i;j<=M/i;j++)
		b[i*j]=false;//质数的倍数不是质数 
	}
}
//求1到sqrt(n)中所有的质数 
int calc_first(int k){
	if (n==k||n<k) return 2*k;
	//n==k，代表n是质数，不能删去
	//n<k，代表k在n到m中，不能删除k，所以从2k开始删除 
	else if (n%k==0) return n;
	//否则，若n%k==0，代表n是合数，需要删除 
	else return (n/k+1)*k;
	//n%k!=0，从大于n的第一个k的倍数开始枚举 
}//求枚举的起点，优化时间  
int main(){
	get_all_the_prime();
	//预处理，求所有的质数 
//	freopen("t1.in","r",stdin);
	scanf("%d",&test_number);
	//输入有多少组数据  
	while (test_number--){
		scanf("%d%d",&n,&m);
		//输入每组数据的上下界 
		memset(v,true,sizeof(v));
		//当n到m中所有数都是质数 
		for(i=1;i<=tot;i++){
	//		if (a[i]>m) break;
			int f1=calc_first(a[i]);
			//枚举的起点  
			if (f1>m) break;
			for(j=f1;j<=m;j+=a[i])
			v[j-n]=false;//删去不是质数的数 
		}
		for(i=n;i<=m;i++)
		if (v[i-n]&&i>1)
		printf("%d\n",i);
		//输出n到m中所有的质数 
		printf("\n");//别忘了还有一个换行  
	}
	return 0;//退出程序  
}
```
最后讲讲万能头<bits/stdc++.h>，听说noip不能用，所以大家平时用用就好，考试尽量别用！

---

## 作者：不到前10不改名 (赞：3)

//话说这题不是练习线筛的吗，非要用暴力233...  
//先上一个暴力的吧！
```
#include<stdio.h>
int t,srx,sry,i,j;
int lgx(int x)
{
    for(int i=2;i*i<=x;i++)//i*i永远比sqrt快
    if(x%i==0)
    return 0;
    return 1;
}
int main() 
{
    scanf("%d",&t);//t组数据
    for(i=1;i<=t;i++)
    {scanf("%d%d",&srx,&sry);//左右值
    for(j=srx;j<=sry;j++)
    if(lgx(j)&&j!=1)//1当然是要特判断的
    printf("%d\n",j);
    printf("\n");}
    return 0;
}
```
//再上一个黑科技QAQ~,不过这题有个bug，自测从1亿到10亿都过（别的题解就是10000ms都过不了），时速稳定在800~900ms，但提交上去是错的，如果有大佬知道还请多多指教
```
#include<stdio.h>
bool a[1000000001];//反正给了1536mb，就是用来开筛法数组的qwq
int main()
{
    long long n,m,i,j,t;
    scanf("%lld",&t);
    for(i=2;i*i<=100000000;i++)//直接预处理筛法10亿之内的素数
    {if(a[i]==0)
    for(j=i*2;j<=100000000;j+=i)
    if(a[j]==0)
    a[j]=1;}
    for(j=1;j<=t;j++)//这里就只是一个查询，无论两个数之间多大都没有影响
    {scanf("%lld%lld",&n,&m);
    for(i=n;i<=m;i++)
    if(a[i]==0&&i!=1)//查找so easy！
    printf("%lld\n",i);
    printf("\n");}
    return 0;
}

```

---

## 作者：yu__xuan (赞：2)

今天刚学了学找素数的方法就来练练手了。
这题，emm,$1<=m<=n<=1000000000$&$n-m<=100000$,范围这么大诶。但这题有点眼熟，哦是[这道题](https://www.luogu.org/problemnew/show/P1835)去看了看我是怎么做的。哦，$Miller-Rabin$算法。这是一个判断是否为素数的算法，挺快的。

$Miller-Rabin$算法：

先特判一下$2$。对于费马小定理中的$p-1$次方，因为$p$是质数，所以$p-1$一定是偶数($p$为$2$时除外所以前面要先特判)，因此我们让$p-1$不断除以$2$，直到除成奇数$t$，我们就可以把$p-1$写成$t * 2^k$(k是除了几次二)的形式。那么我们随机一个质数$a$，计算出$a^t$，然后不断将其平方，利用二次探测定理判断是否为质数。最后算到$a^{p-1}$，用[费马小定理](https://baike.baidu.com/item/费马小定理)判断是否为质数。

$Miller-Rabin$素数测试不是一个确定算法，其单次测试有不超过$1/4$的概率会将一个合数误判为一个质数，但多次迭代后判断错误的概率极低。$Miller-Rabin$算法的最坏情况时间复杂度是$O(lg3(n))$
$lg$是以$2$为底的.
当$N<4759123141$，选取$a=2,7,61$即可确保算法得出正确结果。

当$N<3825123056546413051≈3* 10^{18}$选取$a=2,3,5,7,11,13,17,19,23$即可确保算法得出正确结果。

当$N<18446744073709551616=2^{64}$，选取 $a=2,3,5,7,11,13,17,19,23,29,31,37$即可确保算法得出正确结果。
所以我们不用随机数，直接给把这些数放到$test$数组里就好了

二次探测定理：若$p$为质数，且$x^2≡1(modp)$，那么$x≡1(mod p)$和$x≡p-1(mod p)$中的一个成立。
会了这玩意，就可以做很多数据很大的题了！
此题代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
using namespace std;
int test[15]= {2,7,61};
inline int read()//读入优化。 
{
    int x=0;
    bool f=0;
    char c=getchar();
    while(c<'0'&&c>'9') f=!f,c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return f?-x:x;
}
inline void write(int n)//写优化。 
{
    if(n<0)
    {
        putchar('-');
        write(-n);
    }
    else
    {
        if(n/10) write(n/10);
        putchar(n%10+'0');
    }
}
long long qpow(int a,int b,int c) {//快速幂。不会的可以去做一下P1226 
    if(b==0) return 1%c;
    long long ans=1,base=a;
    while(b) {
        if(b & 1) ans*=base;
        ans%=c;
        base*=base;
        base%=c;
        b>>=1;
    }
    return ans;
}
bool mb(int p) {//Miller-Rabin算法。 
    if(p==1) return 0;
    int t=p-1,k=0;
    while(!(t&1)) {
        k++;
        t>>=1;
    }
    for(int i=0; i<=2; ++i) {
        if(p==test[i]) return 1;
        long long a = qpow(test[i],t,p),nx=a;
        for(int j = 1; j <= k; ++j) {
            nx = (a * a) % p;
            if(nx == 1 && a != 1 && a != p - 1) return 0;
            a = nx;
        }
        if(a != 1) return 0;
    }
    return 1;
}

int main() {//主函数。 
	int k;
	k=read();
    long long n,m,ans=0;
    for(int i=1;i<=k;++i)
    {
    	n=read();m=read();
   		for(int j=n;j<=m;++j)
   		{
   			if(mb(j))
			{
				write(j);
				puts("");
			}
   		}
      	puts("");
    }
    return 0;
}
```
关于快速幂，安利一下自己博客。[传送门](https://www.cnblogs.com/poi-bolg-poi/p/10784919.html)

$updata:2019.07.01$

---

## 作者：sunwuyi (赞：2)

当我第一眼看到1 <= m <= n <= 1000000000这个数据范围的时候，我瞬间就懵逼了，10亿的范围，完全过不了啊，然而当我往下看到n-m<=100000之后，我悬着的心就下来了，这不就是一道简单的判断素数题吗

好了，废话不多说，下面附上我的源代码
```pascal
var n,x,y,i,j,k:longint;
f:boolean;
begin
readln(n);
for i:=1 to n do
  begin
  readln(x,y);
  for j:=x to y do
    begin
    f:=true;
    for k:=2 to trunc(sqrt(j)) do
      if j mod k=0 then
        begin
        f:=false;break;
        end;//判断素数
    if f and (j<>1) then writeln(j);//记住，1的情况要特殊判断一下
    end;
  writeln;
  end;
end.
```

---

## 作者：zrz_orz (赞：1)

# 简单的模拟学~~（滑稽）~~
## 记住1的判断
## 别想线性筛
##### ~~10^9是你能撼动的？？~~


------------


```cpp
#include <bits/stdc++.h>
using namespace std;
bool check(int a) {
	if (a == 1) return 1;
	for (int i = 2; i * i <= a; i++) {
		if (a % i == 0) return 1;
	}
	return false;
}
int main() {
	int t;
	scanf("%d", &t);
	for (int j = 1; j <= t; j++) {
		int n, m;
		scanf ("%d%d", &n, &m);
		for (int i = n; i <= m; i++) {
			if (!check(i)) {
				printf("%d\n", i);
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：lili_flyingcutter (赞：1)

# 第一次第一个发题解！
## 这题不难，枚举即可，适合新手
## 每次判断是否为素数，是，输出

bool is_p(int n){

    for(int i=2;i*i<=n;i++)//如果有数（>=2）是n的因数，则不是素数
       if(n%i==0)return 0;//判素数，这个不难
    return 1;
}

int main(){

    int t,n,m;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        if(n==1)n++;//一不是素数！！
        if(n==2)printf("%d\n",n++);//二特判
        if(n%2==0)n++;//保持n为奇数，方便后面枚举
        for(int i=n;i<=m;i+=2)//我优化了，i第一次为奇数，只用枚举奇数
           if(is_p(i)) printf("%d\n",i);//枚举
        printf("\n");//换行
    }
    return 0;
}

---

## 作者：AutumnTripod906 (赞：0)

一道练习**素数基础**的好题目。

[SP2 PRIME1 - Prime Generator](https://www.luogu.org/problemnew/show/SP2)

### 首先，先来看看素数是个啥。

质数（素数）定义为在**大于1的自然数**中，除了**1和它本身以外**不再有其他因数。

注意上面的加粗字体。



------------


### 判断素数的基本方法

根据素数的定义，可以得出最简单的方法：
	
```cpp

//伪代码
for i ... n-1
   if n%i==0
     不是素数
是素数
```
好的。这种方法最简单易懂。从2...n逐个枚举，如果n可以整除i，那么n就不是素数。但是，这种方法效率**极低**。

用这种方法提交：

![](https://cdn.luogu.com.cn/upload/pic/55972.png)

代码：

```cpp
#include<cstdio>
using namespace std;
bool isprime(int n)
{
    if(n==1) return 0;
    for(int i=2;i<=n-1;++i)
        if(n%i==0)
            return 0;
    return 1;
}
int main()
{
    int s;
    scanf("%d",&s);
    while(s--)
    {
        int m,n;
        scanf("%d%d",&m,&n);
        while(m<=n)
        {
            if(isprime(m))
                printf("%d\n",m);
            ++m;
        }
        putchar('\n');
    }
    return 0;	
}
```


因为循环从2开始，到(n-1)结束，共循环了(n-2)次，做了很多不必要的判断。时间复杂度O(N)

所以，需要**优化算法**。

我们可以猜想，循环到n/2行不行(整除，向下取整）？

举例：

16/2=8 循环从2开始，发现16不是素数；

17/2=8 循环从2开始，到8时发现没有数被17整除，所以17是素数；

1000/2=500 循环从2开始，发现2可以被1000整除，所以1000不是素数。

可得循环从2开始，到n/2结束,为了保险，我们多循环一次，到(n/2+1)结束。

提交：

![](https://cdn.luogu.com.cn/upload/pic/55974.png)

代码：

```cpp
#include<cstdio>
using namespace std;
bool isprime(int n)
{
    if(n==1) return 0;
    int k=n/2+1;    //也可写成 int k=(n>>1)+1; 位运算更快
    for(int i=2;i<=k;++i)
        if(n%i==0)
            return 0;
    return 1;
}
int main()
{
    int s;
    scanf("%d",&s);
    while(s--)
    {
        int m,n;
        scanf("%d%d",&m,&n);
        while(m<=n)
        {
            if(isprime(m))
                printf("%d\n",m);
            ++m;
        }
        putchar('\n');
    }
    return 0;	
}
```

仍然超时。同样也是因为循环次数过多。时间复杂度O(N/2)

再根据数学分析，可以发现数的因数（约数）是成对出现的（证明过程略），所以我们只需判断至√n。时间复杂度O(√N)

提交：

![](https://cdn.luogu.com.cn/upload/pic/55975.png)

代码：

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
inline bool isprime(int n)
{
    if(n==1) return 0;
    if(n==2||n==3||n==5) return 1;
    int k=sqrt(n);
    for(int i=2;i<=k;++i)
        if(n%i==0)
            return 0;
    return 1;
}
int main()
{
    int s;
    scanf("%d",&s);
    while(s--)
    {
        int m,n;
        scanf("%d%d",&m,&n);
        while(m<=n)
        {
            if(isprime(m))
                printf("%d\n",m);
            ++m;
        }
        putchar('\n');
    }
    return 0;	
}
```

同时注意inline不要乱用。

可见这种方法灰常优秀。顺利AC。
同时还有更快的方法，请dalao们自行百度了解。



---

## 作者：Jinyeke (赞：0)

### 注意：本题是入门难度，传说中的红题，红题！
#### 题目：求给定两个数之间的素数。
如果不知道素数是什么（应该都知道吧），阅读下面的文字，您将解决疑惑（取材自网络）

####    素数的定义：质数(prime number)又称素数，有无限个。一个大于1的自然数，除了1和它本身外，不能被其他自然数整除，换句话说就是该数除了1和它本身以外不再有其他的因数;否则称为合数。

#### 这是pascal求素数的函数写法
```pascal
p:=true;//先默认这个数是素数（质数）
for j:=2 to trunc(sqrt(i)) do //枚举，不用我多说了吧
  if i mod j=0 then //判断i是不是j的因子
   begin
    p:=false;//是的话表示i除了1和本身外还有其他因子，所以它不是一个素数
    break;//不是素数直接退出判断的循环，节省时间
   end;
  if i=1 then p:=false;//特判：如果i=1，i也不是素数
  if p then writeln(i);//如果只有1和本身两个因子，i就是一个素数，因此按照题目意思输出
    end;
```
#### 懂了上面的算法，那么代码就很好写了，纯粹只是再求素数的函数外面再加一层循环和补充一下细节
完整代码如下（pascal）:


```pascal
var//定义
 t,m,n,i,j,k:longint;
 p:boolean;
begin 
 readln(t);//输入组数
 for k:=1 to t do //一共有t组
  begin
   readln(m,n);//输入m，n
   for i:=m to n do //枚举m~n
    begin//以下是判断素数的过程，上面已经介绍了
     p:=true;
     for j:=2 to trunc(sqrt(i)) do 
      if i mod j=0 then 
       begin
        p:=false;
        break;
       end;
     if i=1 then p:=false;
     if p then writeln(i);//按题目意思输出
    end;
   writeln;//每一组结束都要换行
  end;
end.
```
### 共建文明洛谷，请勿抄袭！


---

## 作者：heziqi (赞：0)

AC代码：
```
#include<bits/stdc++.h>
using namespace std;
int ifs(int n){
    if(n==1)return 0;
    for(int i=2;i*i<=n;i++)if(n%i==0)return 0;
    return 1;
}
int main(){
    int n;
    cin>>n;
    int first,end;
    for(int i=0;i<n;i++){
        cin>>first>>end;
        for(int j=first;j<=end;j++)if(ifs(j))cout<<j<<endl;
        cout<<endl;
    }
    return 0;
}
```
（代码好像和BoB差不多）

---

## 作者：Arvin2018 (赞：0)

## 千万不能%1%2%3%4
### ~~我TLE10遍了才AC~~

应该

for(int i=2；i<= sqrt(x);i++)

或者

for（int i=2；i * i <= x;i++）

下面上代码(已挖坑，请勿copy）
~~~cpp

#include <iostream>
#include <cmaths>
using namespace std;

bool isPrime(int x){
	if(x == 1) return false;
	if(x == 2 || x == 3) return true;
	for(int i = 2; i <= sqrt( double(x) ) ; i++){
		if( x % i == 0 ){
			return false;
		}
	}
	return true;
}

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int a,b;
		cin>>a>>b;
		for(int j=a;j<=b;j++){
			if(isPrime(j)){
				cout<<j<<endl;
			}
		}
		cout<<endl;
	}
}
~~~

---

## 作者：Chiaro (赞：0)

### 暴力啊

## 暴力啊

# 暴力啊!!!

###### ~~能暴力为什么要写正解~~

直接暴力枚举判断是不是素数就可以了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define sc scanf
#define pr printf
#define inf 1000000000
#define ll long long
#define il inline
using namespace std;
int t,a,b;
bool pri(int x){//判断素数的函数,是素数返回1,不是返回0
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			return 0;
	return 1;
}
int main(){
	sc("%d",&t);
	for(int i=0;i<t;i++){
		sc("%d%d",&a,&b);
		if(a==1)a=2;//1不是素数,从2开始判断
		for(int k=a;k<=b;k++)//暴力!!!!枚举!!!!!
			if((k&1)||(k==2))//优化一下,偶数都不是素数(2除外)
				if(pri(k))
					cout<<k<<'\n';//是素数输出
		cout<<'\n';
	}
	return 0;
} 
```

###### _ ~~求过~~ _

---

## 作者：myfly (赞：0)

## 暴力预警 
（~~复杂度好一些？~~）

题目数据n-m<=100000，暴力随便过，蒟蒻只是顺带优化一下。
```cpp
//SP2 PRIME1 - Prime Generator
# include <iostream>
# include <cmath>
using namespace std;
bool Prime(int);
int main() {
    int N; cin>>N;
    for (int i=0,s,t; i<N; i++) {
        cin>>s>>t;
        for (int j=s; j<=t; j++) {
            if (Prime(j)) cout<<j<<endl;
        }
        cout<<endl;
    }
    return 0;
}
bool Prime(int n) {
    if (n==3 || n==2) return true;
    if (n==1 || (n%6!=1&&n%6!=5)) 
        return false;
    for (int i=5; i<=sqrt(n); i+=6) 
        if (n%i==0 || n%(i+2)==0)
            return false;
    return true;
}
```

---

## 作者：loi_hjh (赞：0)

~~请忽略那些奇奇怪怪的头文件~~

附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,p,q; 
void gg(){
	scanf("%d%d",&p,&q);//区间 
	for(int i=p;i<=q;i++){
		if(i>1){//0，1，负数都不是质数 
			bool x=true;
			for(int j=2;j*j<=i;j++)
				if(i%j==0){
				x=false;
				break;
			}
			if(x) printf("%d\n",i);//是质数 
		}
	}
	putchar('\n');//比printf快 
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)//开个函数好看 
		gg();
	return ~~(0-
```

---

## 作者：MaoHanKun (赞：0)

	**//切记不可打素数表。** 
    #include<cstdio>//因为n-m<=100000，所以直接暴力。 
	using namespace std;
	int t,n,m;
	bool xx(int x){//素数判断。 
		for(int i=2;i*i<=x;++i)//在数据较大的时候++i比i++稍微快一点。 
			if(x%i==0) return 0;
		return 1;
	}
	int main(){
		//freopen("ab.in","r",stdin);文件格式，无需添加。 
		//freopen("ab.out","w",stdout);
		scanf("%d",&t);
		while(t--){
			scanf("%d%d",&n,&m);
			if(n==1) n=2;//特判，去掉1。 
			for(int i=n;i<=m;++i)
				if(xx(i)) printf("%d\n",i);//每输出一个素数就要换行。 
			printf("\n");//样例中每组答案中间空了一行。 
		}
		return 0;
	}//完美结束。

---

## 作者：_FILARET_ (赞：0)

所以说这道题就是区间素数问题可以用线性筛法做……但是我选择暴力qwq因为这题~~数据和时间太水~~
```
#include <iostream>  //这两个头文件可以用bits的万能头文件
#include <cmath>     //这两个头文件可以用bits的万能头文件
using namespace std;
bool prime(int x)    //自定义函数素数判断
{
    if(x<2) return 0;     //如果这个数小于2那么它肯定不是素数因为最小的素数是2
    if(x==2) return 1;    //2是素数
    for(int i=2;i<=sqrt(x);i++) if(x%i==0) return 0; 
    //这里从2判断到x的平方根可以有效将把O(n)变为O(log n)
    return 1;
}
int main()
{
    int k;           //毒瘤的多组数据
    cin>>k;
    while(k--)
    {
        int n, m;    //两个区间
        cin>>n>>m;
        for(int i=n;i<=m;i++)
        {
            if(prime(i)) cout<<i<<endl;  //调用子程序
        }
        cout<<endl;
    }
    return 0;        //回家吃糖去了
}
```

顺便翻译一下题：

皮特想要为他的加强版密码系统弄点素数，帮帮他吧！帮他生成在n和m区间内的所有素数。

---

## 作者：Aehnuwx (赞：0)

这道题，比那道试机题又难一点了。

素数判断即可。

$code$

```
#include <cstdio>
using namespace std;
bool prime(int x) { //判断素数的函数，一定记住1要特判
	if(x == 1) return false;
	for(int i = 2; i * i <= x; i ++)
		if(x % i == 0) return false;
	return true;
}
int main() {
	int n, a, b;
	scanf("%d", &n);
	while(n --) {
		scanf("%d%d", &a, &b);
		for(int i = a; i <= b; i ++)
			if(prime(i)) printf("%d\n", i); //是素数就输出，也要换行！
		printf("\n"); //这里的换行也别忘了！
	}
	return 0;
}
```

---

