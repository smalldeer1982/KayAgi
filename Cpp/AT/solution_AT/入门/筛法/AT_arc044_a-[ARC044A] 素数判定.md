# [ARC044A] 素数判定

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc044/tasks/arc044_a

高橋君は素数判定アルゴリズムが大好きです。毎日さまざまな素数判定アルゴリズムを実装して遊んでいます。 しかし、高橋君は素数判定をしすぎてしまったので、素数判定に飽きてしまいました。 そこで高橋君は、「素数っぽく見える数」判定をすることにしました。

$ 1 $以上の整数$ N $は、以下のように「素数っぽい」かどうかが判定されます。

- $ N $が素数であるなら、$ N $は「素数っぽい」
- $ N $が合成数であるなら、$ N $を$ 10 $進表記した時の$ 1 $の位が偶数でも$ 5 $でもなく、各桁の和が$ 3 $で割り切れないならば、$ N $は「素数っぽい」
- それ以外の場合、$ N $は「素数っぽくない」

整数$ N $が与えられるので、$ N $が「素数っぽい」場合は"Prime"、そうでない場合は"Not Prime"と出力してください。

## 说明/提示

### Sample Explanation 1

$ 42 $は合成数かつ$ 1 $の位が偶数なので、「素数っぽくない」と判定されます。

### Sample Explanation 2

$ 49 $は素数ではありませんが、「素数っぽい」と判定されます。

### Sample Explanation 3

$ 3 $は素数なので、「素数っぽい」と判定されます。

### Sample Explanation 4

$ 1 $は素数でも合成数でもないので、「素数っぽくない」と判定されます。

## 样例 #1

### 输入

```
42```

### 输出

```
Not Prime```

## 样例 #2

### 输入

```
49```

### 输出

```
Prime```

## 样例 #3

### 输入

```
3```

### 输出

```
Prime```

## 样例 #4

### 输入

```
1```

### 输出

```
Not Prime```

# 题解

## 作者：C20210404杜铖昊 (赞：16)

本蒟蒻认为：

这道题根本不用判断素数，只要判断n能否不被2，3，5整除（2，3，5）(因为有类似素数)

但是1,2,3,5需要特判
代码如下：
```cpp
#include<cstdio>
#include<cmath>
int main(){
	int n;
	scanf("%d",&n);
	if(n==1){
		printf("Not Prime\n");
		return 0;
	}
	if(n==2||n==3||n==5){
		printf("Prime\n");
		return 0;
	}
	if(n%2!=0&&n%3!=0&&n%5!=0){
		printf("Prime\n");
	}
	else{
		printf("Not Prime\n");
	}
	return 0;
}
```

---

## 作者：Black_Gzombie (赞：8)

介绍一种素数判定的方法：
## Miller-Rabbin素数测试
时间复杂度可以达到O(slogn）级别，s是测试次数，一般取在30次左右便已足够，因此这是一个logn级别的算法

首先根据费马小定理，当p是素数时有：

$a^{p-1}\equiv1(\mod p)$

即

$a^{p-1}\mod p =1$

那么如果有此式成立，是否p一定为质数？答案是否定的。但是，我们可以多测试几次，即随机选取a值进行测试，提高准确率。测试次数越大，正确率越高。（当然也就越慢）

测试次数一般选在30左右。

那么我们就可以用快速幂求出$a^{p-1}\mod p$的值，判断其是否为1即可。

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll num;

ll qpow(ll a,ll b,ll mod)
{
    ll res=1;
    while(b)
    {
        if(b&1)res=(res%mod*a)%mod;
        a=(a%mod)*a%mod;
        b>>=1;
    }
    return res;
}

bool MRT(ll x)
{
    if(x==2)return true;
    if(x==1)return false;
    for(int i=1;i<=30;i++)
    {
        ll base=rand()%(x-2)+2;
        if(qpow(base,x-1,x)!=1)return false;
    }
    return true;
}

int main()
{
    scanf("%lld",&num);
    if(MRT(num)||(num%2!=0&&num%3!=0&&num%5!=0&&num!=1))printf("Prime\n");
    else printf("Not Prime\n");
    return 0;
}

```




---

## 作者：Cinderella (赞：7)

本蒟蒻又来发题解啦！

本题其实就是让我们判断素数，但是题目中还要我们判断类似素数，那么类似素数是什么呢？

### 是类似素数的要同时满足两个条件：①这个数是一个合数且②这个数既不是偶数也不是5的倍数，并且如果每个数字的和不能被3整除

那接下来就开始讲思路了，其实本题的思路有两种，我们一一来讲：

## 第一种

1.输入n

2.先特判1，因为1既不是质数也不是合数

3.先判断它是否为素数，如果是，则输出“Prime”并退出程序，否则继续
（PS:我for循环的终值用的是n的开方）

4.如果它不是个素数，则判断它是否为类似素数，如果是，则输出“Prime”，否则输出“Not Prime”

献上第一种思路的代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>

using namespace std;
long long n,p,ans;
int main()
{
 scanf("%I64d",&n);
 if(n==1)
 {
  cout<<"Not Prime"<<endl;
  return 0;
 }//特判1
  for(int i=2;i<=sqrt(n);i++)
 {
    if(n%i==0) 
    {
      p=1;
      break;
    }
 }
 if(p==0) 
 {
  cout<<"Prime"<<endl;
  return 0;
 }//判断它是否为素数
 else
 {
  long long x=n,g;
  while(x>0)
  {
   g=x%10;
   ans+=g;
   x=x/10;
  }
  if(ans%3!=0&&n%2!=0&&n%5!=0) cout<<"Prime"<<endl;//如果它不是素数，则判断它是否为类似素数
  else cout<<"Not Prime"<<endl;
 }
 return 0;
}
```

## 第二种
第二种的思路相对对一种是简单很多的，就是直接判断它是否符合类似素数就OK啦！（因为只要素数就符合类似素数的条件，但不能说类似素数就是素数）

献上代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>

using namespace std;
long long n;
int main()
{
 scanf("%I64d",&n);
 if(n==1)
 { 
  cout<<"Not Prime"<<endl;
  return 0;
 }//特判1
 if(n==2||n==3||n==5) 
 {
  cout<<"Prime"<<endl;
  return 0;
 }//特判2、3、5
 if(n%2!=0&&n%3!=0&&n%5!=0)
 {
  cout<<"Prime"<<endl;
  return 0;
 }//判断它是否为2、3、5的倍数
 cout<<"Not Prime"<<endl;
 return 0;
}


```

最后，还要提醒大家一点的就是：

# 记得换行！

以上就是AT1476 【素数判定】的题解，如有不足，请各位dalao在右边→评论区指出！

---

## 作者：还是那只三水 (赞：5)

# 见到这个题，少不了筛素数的板子
------------
## 首先给大家介绍几个筛素数的板子
### 引用于[zybnxy的线性筛素数模板](https://www.luogu.org/problemnew/solution/P3383)
在此膜拜[zybnxy大佬](https://www.luogu.org/space/show?uid=51645)
------------
1.    根据定义：素数就是一个数除了1和他本身没有其他因数的数叫做质数。
于是我们对于一个n,可以可以从2枚举到n−1，从而判断这个数是不是质数。
------------
那这个的时间复杂度就是**O（n）**
显而易见，当n足够大时，我们的程序就会爆掉
------------
```cpp
bool prime1(int x)//O(n)
{
	if(x<2) return false;
	if(x==2) return true;
	for(int i=2;i<=x;i++)
		if(x%i==0) return false;
	return true;
}
```
#### 优化一
我们不难发现n的因数是成对出现的，所以对于任何一个整数n，我们只需要从1枚举到根号下n就可以了。
------------
所以这个的时间复杂度就是**O（根号下n）**
```cpp
bool prime2(int x)//O(根号下n)
{
	if(x<2) return false;
	if(x==2) return true;
	for(int i=2;i<=sqrt(x);i++)
		if(x%i==0) return false;
	return true;
}
```
根据本蒟蒻多年的经验，**O(根号下n)**
的算法已经是最快的了，直到有一天看到了[这篇文章](https://blog.csdn.net/huang_miao_xin/article/details/51331710)
------------
此方法的时间复杂度就大大减小，为**O（三分之根号下n）**
```cpp
bool quick_prime(int x)//O(三分之根号下n) 
{
	if(x==2||x==3) return true;
	if(x%6!=1&&x%6!=5) return false;
	for(int i=5;i<=sqrt(x);i+=6)
		if(x%i==0||x%(i+2)==0) return false;
	return true;
}
```
##### 小结：在对于素数的判断时，一般用第一种的优化方法就可以了，但是如果遇到了毒瘤出题人，最好是用第二种方法。
-----
### 那本题的思路就出来了，先判断这个数是不是素数，
```cpp
ull prime(ull x){
	if(x==2||x==3) return 1;
	if(x%6!=1&&x%6!=5) return 0;
	for(int i=5;i<=sqrt(x);i+=6)
	if(x%i==0||x%(i+2)==0) return 0;
	return 1;
}
```
### 再判断这个数是不是类似素数
```cpp
ull simple_prime(ull k){
	if(!prime(k)){
	if(k%2!=0&&k%5!=0&&k%3!=0){
		return 1;
		}
	}
	return 0;	
}
```


------------

### 最后特判一下“1”即可
```cpp
if(prime(n)||simple_prime(n))
	{
		if(n==1) cout<<"Not Prime"<<endl;
		else cout<<"Prime"<<endl;
	} 
	else cout<<"Not Prime"<<endl;
```
------------
#### 最后递交完整代码（有防抄袭bug，小心提交哦！twt）
```cpp
#include<iostream>
#include<bits/stdc++.h>
use nameplace std;
typedef unsigned long long ull;
ull prime(ull x){
	if(x==2||x==3) return 1;
	if(x%6!=1&&x%6!=5) return 0;
	for(int i=5;i<=sqrt(x);i+=6)
	if(x%i==0||x%(i+2)==0) return 0;
	return 1;
}
ull simple_prime(ull k){
	if(!prime(k)){
	if(k%2!=0&&k%5!=0&&k%3!=0){
		return 1;
		}
	}
	return 0;	
}
int main()
{
	int n;
	cin>>n;
	if(prime(n)||simple_prime(n))
	{
		if(n==1) cout<<"Not Prime"<<endl;
		else cout<<"Prime"<<endl;
	} 
	else cout<<"Not Prime"<<endl;
	return 0;
}
```
求管理大大通过qwq

---

## 作者：____OccDreamer (赞：4)

某蒟蒻认为不需要那么麻烦
```
#include<iostream>
using namespace std;
int main()
{
	long long n;
	cin>>n;
	if (n==2||n==3||n==5) 
    	{cout<<"Prime"<<endl;return 0;}//特判
	if (n<=1) {cout<<"Not Prime"<<endl;return 0;}//同上
	if (n%2==0||n%5==0||n%3==0) 
  	{cout<<"Not Prime"<<endl;return 0;}//完全不需要循环
	else cout<<"Prime"<<endl;//不能被2、3、5整除即可
	return 0;
}
```
是我太菜了吗？没想到循环......一次过，注意加endl，所有AT的题都要加！！！

---

## 作者：da32s1da (赞：4)

好吧，其实这道题不必要判断素数！！！

因为大于5的素数也是似素数！

其次，各位数字之和能被3整除就是该数能被3整除。
```
#include<cstdio>
int main(){
    int n;
    scanf("%d",&n);
    if(n==2||n==3||n==5) puts("Prime");  //特判2,3,5
    else if(n%2&&n%3&&n%5&&n!=1) puts("Prime");//似素数及非1
    else puts("Not Prime");//否则
}
```

---

## 作者：焖炒小土豆 (赞：2)

费马小定理：
当 n 为整数，p 为质数时，满足 n^(p−1)=1(mod p)
可以化成 n^p=n(mod p)，只不过因为有可能 n>p 而通常不使用这种形式。

费马小定理的逆命题：
若 n^p =n(mod p) ，则 p为质数
这个命题是错的，但是错的概率较小。
所以我们可以利用这个命题来判断 pp 是否为质数。
具体：

随机选择n，若 np(mod p)≠n 那么 p 不为质数。
但是因为有可能出错，所以我们试多几次。如果每次结果都等于 n ，我们可以认为 p 是一个质数。次数按 n 的范围具体定义。试20次可以保证在int内不出错。

时间复杂度：
由于有快速幂这玩意儿，所以每次判断用时为 log(n)。就算要试多几次，也比原来的 √n 算法好上不少。唯一的缺憾是这是一个伪判定方法。

---

## 作者：Ykimna (赞：2)

```cpp
#include<iostream>
using namespace std;
int main()
{	
	int i=2,n,sum=0;
	cin>>n;
	if(n==1)//特判1 
	{
		cout<<"Not Prime"<<endl;
		return 0;
	}
	while(i<=n-1)//枚举i，判断n是否为质数 
	{
		if(n%i==0&&(n%3==0||n%5==0||n%2==0))//筛掉类质数 
		{	
			cout<<"Not Prime"<<endl;
			break;
		}
		i++;
	}
	if(i==n||(n%3!=0&&n%5!=0&&n%2!=0))//判断类质数和质数 
	{
		cout<<"Prime"<<endl;
	}
	return 0;
}     
```

---

## 作者：LW_h_FP (赞：2)

被前面的假翻译坑了。一道水题，按照题意就可以做出来了

但是这里面有一个巨坑，那就是1，想必进来看的人都是这里错了

```
#include<iostream>
using namespace std;

long long a;

int f(int a){
    if(a==1) return 0;
    for(int i=2;i*i<=a;i++)    //判断质数
        if(a%i==0)
            return 0;
    return 1;
}

int main(){
    cin>>a;
    if(f(a)) {cout<<"Prime"<<endl;return 0;}  //当是质数时直接输出
    int i=a,sum=0;
    while(i){
        sum+=i%10;         //求每一位的和
        i/=10;
    }
    if(a<=1||a%2==0||a%10==5||sum%3==0){  //不满足那些条件的合数直接输出
        cout<<"Not Prime"<<endl;  //这里要说说为什么1不行了，虽然1满足那些，但是学习质数的时候老师有没有说过1既不是质数也不是合数
    }
    else cout<<"Prime"<<endl;
    return 0;
} 
```
搞清楚1之后这题就没什么了

---

## 作者：bym666 (赞：1)

# AT1476 【素数判定】
这道题题意很清楚，只需判断n是否是素数或相似素数即可。这道题很简单，这里就不详细说了，注释看代码。↓↓↓

代码如下：
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
bool prime(int x)//判断素数 
{
	int i;
	for(int i=2;i*i<=x;i++)
	{
		if(x%i==0) return 0;//如果x能整除i则不是素数 
	}
	if(x<2) return 0;//如果x小于2则不是素数 
	return 1;//剩下的都是素数 
} 
int main()
{
	long long n;
	cin>>n;//输入 
	if(n<2)//1不是合数 
	{
		cout<<"Not Prime"<<endl;//输出 
		return 0;//结束程序 
	}
	if(prime(n)==1) cout<<"Prime"<<endl;//如果是素数，输出 
	else
	{
		if(n%2!=0&&n%3!=0&&n%5!=0) cout<<"Prime"<<endl;//如果是相似素数，输出 
		else cout<<"Not Prime"<<endl;//都不是，输出 
	}
	return 0;//结束程序 
}
```


---

## 作者：逸少 (赞：1)

从 2 到sqrt(n)


```cpp
#include <bits\stdc++.h>
using namespace std;
bool panduan(unsigned long long a) {
    unsigned long long b = sqrt(a);
    for(unsigned long long i = 2;i <= b;i++) {
        if(a % i == 0) {
            return false;
        }
    }
    return true;
}
int main() {
    unsigned long long n;
    cin >> n;
    for(int i =1;i <= n;i++) {
        unsigned long long a;
        cin >> a;
        if(panduan(a)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
} 
```

---

## 作者：TRZ_2007 (赞：1)

啊，~~$C++$党的题解怎么这么多啊~~  
~~$C$党的同学们要加油了~~  
——————————————————————以上是吐槽。  
题目需要用$3$个$if$语句  
第一个：判断它是否等于$1$。（$1$不是素数）  
第二个：判断它是否是素数。（需要一个子函数来判断）
第三个：判断它是否是类似素数。  
如果都不满足条件输出“$Not Prime$”。  
分析完毕，接下来上代码：  
```
#include <stdio.h>
bool pd(int n)//判断n是否是素数
{
	int i;
	if(i==2) return true;//2需要特判
	for(i=2;i*i<=n;i++)//只要枚举到sqrt(n)就够了
		if(n%i==0) return false;//如果能被整除，就说明n不是素数
	return true;//n是素数
}
int main()//注意岛国的题需要换行
{
	int n;
	scanf("%d",&n);//读入
	if(n==1) printf("Not Prime\n");//n是否等于1
	else if(pd(n)) printf("Prime\n");//n是否是素数
	else if(n%3!=0&&n%5!=0&&n%2!=0) printf("Prime\n");//n是类似素数
	else printf("Not Prime\n");//都不是
}
```

---

## 作者：LiHaoYu0512 (赞：1)

这道题只需要判断素数和似素数。可以写两个子函数来判断素数和似素数！

程序如下！！！

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<cmath>
using namespace std;
bool isPrime(int x)
{
	if(x==0||x==1) return false;
    for(int i=2;i<=sqrt(x);i++)
    	if(x%i==0) return false;
    return true;
}//判断素数
bool sIsPrime(int x)
{
	if(x%2!=0&&x%3!=0&&x%5!=0&&x!=1)
    	return true;
    else
    	return false;
}//判断似素数
int main()
{
    int n；
    cin>>n;
    if(isPrime(n)) cout<<"Prime"<<endl;//判断素数
    else if(sIsPrime(n))cout<<"Prime"<<endl;//判断似素数 
    else cout<<"Not Prime"<<endl;
    return 0;//程序拜拜！！！
}
```

---

## 作者：不到前10不改名 (赞：1)

//纯c党来了！！  
//这题本意不需要筛法！！！   
//下面由我来介绍一下黑科技QAQ~
//加上了一个小改动QAQ
```
#include<stdio.h>
//bool srx[100000001];
int main()
{
    long long n//,i,j;
    scanf("%lld",&n);
    if(n%2==0&&n!=2)//特判把2,3,5去掉的原因是它们是素数
    {printf("Not Prime\n");
    return 0;}
    if(n%3==0&&n!=3)//并且如果每个数字的和不能被3整除的意思就等同于不是3的倍数
    {printf("Not Prime\n");
    return 0;}
    if(n%5==0&&n!=5)
    {printf("Not Prime\n");
    return 0;}
    if(n==1)//惯例：只要是素数1都是例外
    {printf("Not Prime\n");
    return 0;}
    /*for(i=2;i*i<=10000000;i++)
    {if(srx[i]==0)
    for(j=i*2;j<=10000000;j+=i)
    if(srx[j]==0)
    srx[j]=1;}
    if(srx[n]==0)*///这段就是筛法了，不过没什么用呢！
    printf("Prime\n");//在这里我们可以发现剩下的数好像————都是素数或类素数呢！
    //其实道理很简单，就是因为根据素数的定义，素数肯定不会还有2,3,5这样的因数
    //当然它本身就是除外QAQ~，所以才会有前面的特判
    return 0;
}
```

---

## 作者：wubaiting2020 (赞：1)

思路：先读入，**再特判1**，很多人都是这样错的（~~包括我~~）然后枚举判断素数，最后判断似素数。


------------

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
    int i,n,bj=0;
    cin>>n;
    if(n==1)bj=1;//特判1 
    for(i=2;i<=n-1;i++)
        if(n%i==0){bj=1;break;}//枚举判断它的因数 
    if(bj==0)
    cout<<"Prime"<<endl;
    else if(n%2!=0&&n%3!=0&&n%5!=0&&n!=1)cout<<"Prime"<<endl;//判断似素数 
    else cout<<"Not Prime"<<endl;
    return 0;
}
```

---

## 作者：durbin中将 (赞：1)

大家怎么都做得那么麻烦
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;//输入这个数
    if((n==2||n==3||n==5)or(n%2!=0&&n%3!=0&&n%5!=0&&n!=1)) cout<<"Prime"<<endl; //这个数是否能被2，3，5整除（不含2，3，5和1）是就输出素数 
    else cout<<"Not Prime"<<endl//否则就不是
    return 0;//结束
}
```

---

## 作者：在下互质数 (赞：0)

### 非常出名的一道题，直接上题解
```
#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if(n==0||n==1){      //特殊情况
        cout<<"No Prime";
        return 0;
    }
    if(n==2){
        cout<<"Yes";   //特殊情况（判定2为素数）
        return 0;
    }
    for(int i=2;i*i<=n;i++){
        if(n%i==0){     //辗转相除法
            cout<<"No Prime";
            return 0;
        }
    }
    cout<<"Prime";
}
```
#### 蒟蒻题解，大佬勿喷

---

## 作者：sunchenyi (赞：0)

整个题解区竟然没有P党题解！！（可怜呐~）

那本蒟蒻也就来发一篇吧

让入门的P党可以参考一下

这道题目其实并不是纯粹的判断素数

因为它只要不被2、3、5整除它都可以算为相似素数

这样就更简单了

更详细的解释请看代码

```pascal
var n:longint;
begin
  readln(n);//读入n
  if n=1 then writeln('Not Prime')//千万要注意特判，1不是素数！！！（第一个坑点）
  else//否则的话就继续判断
  begin
    if (n=2)or(n=3)or(n=5) then writeln('Prime')//这里也是一个特判，如果是2、3、5就输出Prrime
    else 
    begin
      if (n mod 2<>0)and(n mod 3<>0)and(n mod 5<>0) then//只要n不被2、3、5整除就输出Prime 
      begin
        writeln('Prime');
      end
      else
      begin
        writeln('Not Prime');//否则输出Not Prime
      end;
    end;
  end;
end.
```

思路就是这样

千万不要ctrl+c,ctrl+v哦！

不懂得可以在评论区问我哦！

（管理员，就给过QAQ~）

---

## 作者：真·峭岩仙道 (赞：0)

其实这题并不难，逐个考虑就行。

保险起见，先编一个函数，计算数字和
```cpp
long long he(long long a){
	long long s=0;
	while(a!=0){
		s+=a%10;
		a/=10;
	}
	return s;
}
```
如果N是1，直接输出，结束
```cpp
	if(n==1){
		cout<<"Not Prime"<<endl;
		return 0;
	}
```
然后先判断质数
```cpp
	bool x=true;
	for(long long i=2;i<n;i++){
		if(n%i==0){
			x=false;
			break;
		}
	}
```
最后再考虑一下特殊情况就行了，完整代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long he(long long a){
	long long s=0;
	while(a!=0){
		s+=a%10;
		a/=10;
	}
	return s;
}
int main(){
	long long n;
	cin>>n;
	if(n==1){
		cout<<"Not Prime"<<endl;
		return 0;
	}
	bool x=true;
	for(long long i=2;i<n;i++){
		if(n%i==0){
			x=false;
			break;
		}
	}
	if(x) cout<<"Prime"<<endl;
	else {
		if(n%2!=0&&n%5!=0&&he(n)%3!=0){
			cout<<"Prime"<<endl;
		}
		else cout<<"Not Prime"<<endl;
	}
	return 0;
}
```
本蒟蒻第一次发题解，请多指教~

---

