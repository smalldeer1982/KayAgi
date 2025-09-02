# Kolya and Tanya

## 题目描述

Kolya loves putting gnomes at the circle table and giving them coins, and Tanya loves studying triplets of gnomes, sitting in the vertexes of an equilateral triangle.

More formally, there are $ 3n $ gnomes sitting in a circle. Each gnome can have from $ 1 $ to $ 3 $ coins. Let's number the places in the order they occur in the circle by numbers from $ 0 $ to $ 3n-1 $ , let the gnome sitting on the $ i $ -th place have $ a_{i} $ coins. If there is an integer $ i $ ( $ 0<=i&lt;n $ ) such that $ a_{i}+a_{i+n}+a_{i+2n}≠6 $ , then Tanya is satisfied.

Count the number of ways to choose $ a_{i} $ so that Tanya is satisfied. As there can be many ways of distributing coins, print the remainder of this number modulo $ 10^{9}+7 $ . Two ways, $ a $ and $ b $ , are considered distinct if there is index $ i $ ( $ 0<=i&lt;3n $ ), such that $ a_{i}≠b_{i} $ (that is, some gnome got different number of coins in these two ways).

## 说明/提示

 $ 20 $ ways for $ n=1 $ (gnome with index $ 0 $ sits on the top of the triangle, gnome $ 1 $ on the right vertex, gnome $ 2 $ on the left vertex): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF584B/e820d83cdfe0c59fc424109c332a1fb6000d6a18.png)

## 样例 #1

### 输入

```
1
```

### 输出

```
20```

## 样例 #2

### 输入

```
2
```

### 输出

```
680```

# 题解

## 作者：Lauzun (赞：6)

不知道为什么挺水一道题没人做$qwq$~~**（是因为我菜所以只配做水题吗）**~~

这个题，我一看就晓得

显然是用总的方案数减去总和都为$6$的方案数

 _so，让我们来**举个栗子**_ 
 
 如果只有一个三角形的话，总方案数显然为$3 * 3 * 3 = 27$种 _**（小学乘法原理）**_ ，而所有总和都为$6$的方案显然是$1 + 2 + 3 = 6  $ $or$ $  2 + 2 + 2 = 6$，前者方案数为$6$种 _**（依旧是乘法原理）**_ ，后者方案数为$1$种。
 
 所以显然的，**当三角形只有一个的时候，答案为$27 - 6 - 1 = 20$种。**
 
 进一步分析可以得到，当三角形个数为$2$时，总方案数$27 * 27 - 7 * 7 = 680$种
 
 所以我们会发现一个结论：**当三角形个数为n时，满足题意的方案数为$27 ^ n - 7 ^ n$种。**
 
 等等，这个结论为什么这么草率啊喂！！！这个题好歹也是个绿题诶，是不是搞错了？？？
 
##  然鹅，其实答案真的就是这样

so，记得加个快速幂，快速幂的写法请自行查阅$qwq$ _~~（因为我还要赶着去吃饭呢）~~_ 

AC代码如下（真的就是如此简洁）

```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define mod 1000000007
using namespace std;
long long n, m;

long long calculate( long long x, long long a ) {
	long long ans = 1;
	while( a ) {
		if( a & 1 ) ans = ( ans * x ) % mod;
		x = ( x * x ) % mod;
		a >>= 1;
	}
	return ans % mod;
}

int main() {
	cin >> n;
	cout << ( calculate( 27, n ) % mod - calculate( 7, n ) % mod + mod ) % mod << endl; 
} 
```

---

## 作者：云浅知处 (赞：2)

本题考查排列组合。不难。
***
很明显，一个三角形的合法方案数＝**所有方案数－不合法的方案数（废话）。**

对于每个三角形，每个点上都有$3$种可能，总方案数就是$3\times3\times3=27$（种）。

而不合法的方案（也就是和为$6$的方案）有两种情况：$1+2+3=6$或$2+2+2=6$。

$1+2+3=6$的方案总数为$A_3^3=6$种，$2+2+2=6$的方案总数为$1$种，所以说，不合法的方案总数为$6+1=7$种。

所以合法方案共有$27-7=20$ 种。

有多个三角形时也很简单啦，依然是**所有方案数－不合法的方案数。**

例如有两个三角形时，总方案数为：$27\times27=729$（种）

不合法的方案数为：$7\times7=49$（种）

所用到的知识仍旧是小学学过的[乘法原理](https://baike.baidu.com/item/乘法原理)。

由于对于第一个三角形，有$27$种情况；对于第二个三角形，也有$27$种情况，所以总共有$27\times27=729$种情况。同理，不合法的方案总数是$7\times7=49$种情况。

所以合法的方案总数为$729-49=680$（种）

这里有一个易错点就是有些人可能算成了$20\times20=400$种情况。那这样为什么不对呢？

**因为，当我们这么算的时候，计算出来的实际上是两个三角形都合法的情况！**

仔细想一想，我们现在要求的是至少有一个三角形合法的情况，那怎么能把每个三角形的合法情况相乘呢？而且题目中还有一句话：

>在n个三角形中只要有一个等边三角形满足条件，当前情况就是合法的。

当然，这么算也是可以的，只不过需要考虑许多其他条件。比如在有两个三角形时需要考虑只有一个三角形合法的情况，在有三个三角形的时候需要考虑只有两个三角形合法的情况、只有一个三角形合法的情况......总之十分繁琐。

（顺便提一句，这就是小学数学中十分重要的“**正难则反**”思想）

综上所述，对于$n$个三角形的情况，一共有$27^n-7^n$种可能。

至于快速幂取余，写一个[快速幂||取余](https://www.luogu.com.cn/problem/P1226)就好啦。题解里面的大佬解释的非常清楚。
***
最后，附上代码：

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
long long quickpower_and_remainder(long long x,long long y){//快速幂取余
	long long ans=1,cnt=x;
	while(y){
		if(y&1){
			ans*=cnt;
			ans%=mod;
		}
		cnt*=cnt;
		cnt%=mod;
		y>>=1;
	}
	return ans%mod;
}
int main(){
	long long n;//记得开long long
	cin>>n;//输入
	cout<<(quickpower_and_remainder(27,n)%mod-quickpower_and_remainder(7,n)%mod+mod)%mod;//输出
	return 0;//完结撒花
}
```

$\text{The end.}$

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现**符合条件的方案数=全部方案数-不符合条件的方案数**。而三角形的每个角的值都有三种可能，所以一个三角形的方案数为 $3^3$，即为 $27$。而不符合条件的方案数包括 $1+2+3$ 和 $2+2+2$。$1+2+3$ 有 $6$ 种情况，$2+2+2$ 有 $1$ 种情况，不符合条件的方案数即为 $7$ 种。答案即为 $27^n-7^n$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,sum27=1,sum7=1,mod=1000000007;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		sum27=sum27*27%mod;
		sum7=sum7*7%mod;
	}
	cout<<(sum27-sum7+mod)%mod;
	return 0;
}
```


---

## 作者：HadrianZhang (赞：0)

# 思路

一道比较水的数学题。

重要的数量关系：**至少有一个满足的情况数=总数-全都不满足的情况数**。

知道了这个，这道题就简单了。

- 总数：一个三角形分配硬币的方案有 $3^3=27$ 种，根据乘法原理， $n$ 个就有 $27^n$ 种。
- 全都不满足的情况数：一个三角形硬币数之和等于 $6$ 的情况有 $7$ 种，即：

$1 , 2 , 3$

$1 , 3 , 2$

$2 , 1 , 3$

$2 , 3 , 1$

$3 , 1 , 2$

$3 , 2 , 1$

$2 , 2 , 2$

同理，$n$ 个三角形全都不满足的情况数为 $7^n$。

所以，答案即为 $27^n-7^n$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,mod=1e9+7;
int f(int a,int b)
{
	int ans=1;
	for(int i=1;i<=b;i++)
		ans=ans*a%mod;
	return ans;
}
signed main()
{
	cin>>n;
	cout<<(f(27,n)-f(7,n)+mod)%mod;
	return 0;
}
```

---

## 作者：ImposterAnYu (赞：0)

# 解析
我们根据乘法原理，可以推出一共有 $3^3 = 27$ 种不同的等边三角形。但是样例告诉我们只有 $20$ 种是满足条件的，剩下的 $7$ 种都不满足条件。

只要知道了这个，这道题就很简单了。

题目里说让我们求**至少**有一个等边三角形合法的方案数，所以我们只需要求出所有的方案数，最后减去没有一个等边三角形合法的方案数即可。

也就是求

$$27^n-7^n$$

即可。

# AC code

这题的数据范围比较小，所以我们可以直接暴力求。

```c++
#include<bits/stdc++.h>
#define int1 long long
#define mod 1000000007
#define N 100005
using namespace std;
int1 n,a = 1,b = 1,s;
int1 read(){//暗羽牌快读，你不值得拥有！
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//暗羽牌快写，你更不值得拥有！
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
	n = read();
	while(n--){
		a = a * 27 % mod,b = b * 7 % mod;//直接暴力算。
	}
	print((a - b + mod) % mod);//因为a和b取完模后b可能比a大，所以要先将结果加上1e9+7后再取模。
  	return 0;
}
```

当然，如果你愿意，也可以用快速幂。

```c++
#include<bits/stdc++.h>
#define int1 long long
#define mod 1000000007
#define N 100005
using namespace std;
int1 n,a = 1,b = 1,s;
int1 read(){//暗羽牌快读，你不值得拥有！
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//暗羽牌快写，你更不值得拥有！
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int1 quick_pow(int1 a,int1 b,int1 p){//快速幂（计算a的b次方对p取模后的值）
	int1 s = 1;
	while(b){
		if(b & 1){
			s = s * a % p;
		}
		a = a * a % p,b >>= 1;
	}
	return s;
}
int main(){
	n = read();
	print((quick_pow(27,n,mod) - quick_pow(7,n,mod) + mod) % mod);
  	return 0;
}
```

---

## 作者：Arghariza (赞：0)

正面考虑太麻烦，直接反面考虑，答案即为三角形的总数减去不合法三角形的总数。

由于每个点都可以选 $1,2,3$ ，所以 $1$ 个三角形一共有 $3^3=27$ 种选择，所以 $n$ 个三角形就一共有 $3^{3^n}=27^n$ 种选择。

不合法三角形就是三边和为 $6$ 的三角形，而 $6=1+2+3=2+2+2$  ，前一种情况有$A_3^3=6$ 种方法，而后一种情况只有 $1$ 种方法，所以一共 $7$ 种方法。所以 $n$ 个三角形中不合法三角形的个数即为 $7^n$。

所以直接求 $27^n-7^n$  即可，记得加上取模。

```cpp
#include <bits/stdc++.h>
#define mod 1000000007
#define int long long// 记得开long long
using namespace std;

int n, ans;

int ksm(int p, int q) {// 快速幂
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % mod;
		p = p * p % mod;
		q >>= 1;
	}
	return res;
}

signed main() {
	cin >> n;
	ans = ksm(27, n) - ksm(7, n);// 计算结果
	while (ans < 0) ans += mod;// ans可能是负数，此时需要转成正余0数。
	cout << ans;
	return 0;
}
```

---

## 作者：Mine_King (赞：0)

比较裸的一道容斥原理题。  

考虑容斥原理，我们只要求出总的方案数和全都是和为 $6$ 的方案数，再让他们相减即可。

一个三角形的所有方案共 $27$ 个，其中 $7$ 个和为 $6$ 的方案。  
那么如果是 $n$ 个三角形，总方案数就是 $27^n$，而全都是和为 $6$ 的总方案数就是 $7^n$。所以最终答案就是 $27^n-7^n$。  
这个用快速幂求一下就行。  

**注意取模，注意不要爆ll。**  
code：
```cpp
#include<cstdio>
#include<algorithm>
const int mod=1e9+7;
using namespace std;
int n;
int power(int a,int b,int c)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%c;
		a=1ll*a*a%c;
		b>>=1;
	}
	return ans%c;
}
int main()
{
	scanf("%d",&n);
	printf("%d",(power(27,n,mod)-power(7,n,mod)+mod)%mod);
	return 0;
}
```

---

## 作者：GaryH (赞：0)

# 题解

~~数论题做起来脑阔真的痛QWQ~~

## 1.题意

定义每三个只能为$1$,$2$或$3$且所有元素和**不为6**的数为一个集合，问当有$n$个这样的集合时有一个及以上集合合法的不同可能性。

## 2.分析

先讨论$n=1$的情况。

我们知道，取三个数，每个数可以是$1$,$2$或$3$，则每个数都有$\large C_{3}^{1} = 3$种可能。那取三个数，就有$\large (C_{3}^{1})^{3}=3^{3}=3 \times 3 \times 3=27$种可能。但又因为要至少一个集合合法，即至少一个集合的所有元素和大于$6$，又因为现在只有一个集合，那就必须让现在的集合合法。那我们就需要扣除元素和等于$6$的可能。而等于$6$的可能，我们是可以枚举的，即：

1. $1+2+3=6$	
2. $1+3+2=6$
3. $2+1+3=6$
4. $2+3+1=6$
5. $3+1+2=6$
6. $3+2+1=6$
7. $2+2+2=6$

枚举得，元素和为$6$的可能性为$7$种。所以，当前符合要求的可能性为：
$27-7=20$，即$n=1$时答案为$20$。

在分析了$n=1$的情况后，我们再进一步分析$n>1$的情况。

当$n>1$时，由题意得，我们只需使其中一个集合合法即可。那可能性就应该是所有可能(不管合不合法)与所有集合都不合法的可能的差。用数学表达式即为：

$\large ((C_{3}^{1})^{3})^{n}-7^{n}=27^{n}-7^{n}$种可能。

公式推出来了，代码也就好写了。

由于这里的$n$是小于$10^{5}$的，所以用$O(n)$的算法也能过。但是，我在这里还是分别介绍一下$O(n)$,$O(logn)$与$O(1)$的算法。

## 3. 代码

1. 时间复杂度：$O(n)$； 空间复杂度：$O(1)$

这个算法很朴素，我们只需用循环或$pow$函数解决，我也不再多讲。

### code:

$pow$函数

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n,p;
int main(){
	cin>>n;
	p=int(pow(27,n))%mod;
	p=(p-int(pow(7,n))%mod+mod)%mod;
	cout<<p;
	return 0;
}
```
循环

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n,p1=1,p2=1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		p1=(p1*27)%mod;
		p2=(p2*7)%mod;
	}
	cout<<(p1%mod-p2%mod+mod)%mod;
	return 0;
}
```

2. 时间复杂度：$O(logn)$； 空间复杂度：$O(1)$

这个算法即为我们经常提到的**快速幂**。

快速幂的原理简单说，就是将$\large x^{y}$ 拆解成很多个$x$的$2$的次方的次方......算了，我也解释的不是太清楚，你们就看[【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)这里的题解吧，他们讲的比我清楚。

### code:

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
inline long long q_pow(long long k,long long p){
	long long cnt=k,ans=1,m=p;
	while(m>0){
		if(m%2==1)ans=(ans*cnt)%mod;
		cnt=(cnt*cnt)%mod;
		m/=2;
	}
	return ans%mod;
}
long long n;
int main(void){
	cin>>n;
	cout<<(q_pow(27,n)%mod-q_pow(7,n)%mod+mod)%mod;
	return 0;
}

```
3. 时间复杂度：$O(1)$； 空间复杂度：$O(n)$


没错，$O(1)$的算法，就是**打表**。

打表过程中，你只需要吧程序挂着，~~自己去颓废~~直到算出$1$到$10^{5}$的答案，再新建一个代码，把结果放进数组即可。这里我就不放表了，表生成器就是前面的代码。

## 4.AC

[AC #3](https://www.luogu.com.cn/record/28575722)


------------


好了，题解结束了，大家再见！

---

