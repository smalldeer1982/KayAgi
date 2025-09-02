# 与えられた数より小さい素数の個数について

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2012-qualC/tasks/tenka1_2012_9

 素数とは、$ 1 $ と自分自身以外に正の約数を持たない、$ 1 $ 以外の自然数のことをいいます。

 自然数 $ n $ が与えられるので、 $ n $ よりも小さい素数の数は何個存在するかを求めてください。

 入力は以下の形式で標準入力から与えられる。 > $ n $

- 自然数 $ n $ ( $ 1\ \leq\ n\ \leq\ 10,000 $ ) が $ 1 $ 行で与えられる。
 
 $ n $ よりも小さい素数の個数を標準出力に $ 1 $ 行で出力せよ。  
 なお、行の終端には改行が必要である。 ```

11
```

 ```

4
```

- $ 11 $ よりも小さい素数は、 $ 2 $ , $ 3 $ , $ 5 $ , $ 7 $ の $ 4 $ つです。
- ※ 「$ 11 $ よりも小さい」なので、$ 11 $ は含みません。
 
```

100
```

 ```

25
```

 ```

10000
```

 ```

1229
```

# 题解

## 作者：МiсDZ (赞：6)

### 数据小，这道题可以用暴力的算法，也可以用更加高级一点的素数筛法
暴力做法已经有了，线性筛的算法有了，这里给出一个简单一点的但比暴力算法快一点的算法：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[10000010];//合数表
int main()
{
    long long n;
    scanf("%lld",&n);
    for(int i=2;i<=n;i++){
        if(a[i])continue;//如果已经在合数表里了，相当于下面动图中有颜色的部分
        for(int j=i;j<=n;j+=i){//如果不满足，就一定是质数
            if(a[j])continue;
            a[j]=1;//将找到的这个质数的倍数全部上色，即加入合数表
        }
        b[i]=1;
    }
    long long ans=0;
    for(int i=2;i<=n-1;i++){
        if(b[i])ans++;
    }//统计即可
    cout<<ans<<endl;
}
```
就是一个与线性筛极其类似的埃氏算法，可以叫做伪线性筛，它们两个之间是常数关系

这里的意思很简单，通过一个小动图即可了解

![](https://s1.ax2x.com/2018/03/10/EzR2Y.gif)

在这里用这个代码可以直接过[P3383](https://www.luogu.org/problemnew/show/P3383)。注意：有一个小地方不同。

Update：2018.3.12//补充完善内容

---

## 作者：wpy233 (赞：5)

emmm...对于这种题。。。

数据范围只有$10,000$，时限还有$2,000ms$的题目。。。

# 暴力万岁！！！！！

很简单的题啊，就要注意一下是搜到$n-1$而不是$n$，就结束了。。。

**PS：本蒟蒻在此翻车两次，最后才发现~~岛国~~数据竟然输出必须要换行。。。晕了QAQ**
```
#include <bits/stdc++.h>//万能头文件万岁！
using namespace std;
bool ss(int n)//素数判断
{
    if(n==2)
        return true;
    for(int i=2;i<=sqrt(n);i++)//从2搜到n的平方根
        if(n%i==0)
            return false;
    return true;
}
int main()
{
    int n;
    cin>>n;//输入
    int s=0;
    for(int i=2;i<=n-1;i++)//暴力万岁！
        if(ss(i))
            s++;//计数
    cout<<s<<endl;//啊啊啊这什么渣数据不带换行都能全错，服了
    return 0;
}
```

---

## 作者：da32s1da (赞：3)

若数k为质数，则前k个数所含质数为前k-1个数所含质数+1，否则为前k-1个数所含质数。
```
#include<bits/stdc++.h>
using namespace std;
int a[10005],b;
int main(){    //预处理 
	for(int i=2;i<=10000;i++){      //枚举 
		for(int j=2;j<=sqrt(i);j++)
		if(i!=j&&(i%j==0)) {a[i]=a[i-1];break;}   //若该数为合数，则到i的质数为i-1的质数个数 
		if(!a[i]) a[i]=a[i-1]+1;   //若该数为质数， 则到i的质数为i-1的质数个数+1
	}
	scanf("%d",&b);
	printf("%d\n",a[b-1]);
}
```

---

## 作者：AC基德 (赞：2)

# 一道典型的质数题！
### 题意：
#### 求 2~N-1 中的质数个数（只有1和本身两个因数）
### 思路：
#### 用删数做，用for循环，把一个数的倍数（除它本身）删去，剩下的数都是质数!

##### 本人为您献上一篇AC代码：

```c
#include<iostream>
using namespace std;
int a[1000000];//定义数组(要定的稍微大一点，防止数组越界)

int main()
{
	int n;
	cin >> n;//输入
	for (int i = 2;i < n ; i ++)//循环删数
	{
		if (a[i] == 0)//如果你没有被删去，就去删别人(别把自己删了)
			for (int j =  i + i; j <= n; j += i)//删数
				a[j] = 1;//被删去
	}
	int m = 0;//统计质数个数
	for(int i = 2;i < n;i ++)
	{
		if(a[i] == 0)
			m ++;
	}
	cout << m << endl;//完结撒花
    
    while(1)//防止抄袭
    
	return 0;
}
```
#### 珍爱生命，远离抄袭！
#### 本人努力发的第一篇题解，希望管理员给予通过！

---

## 作者：　　　吾皇 (赞：2)

又是一道求区间素数个数的题目，下面会给出多种算法
### 一.单素数测试
**即对2到n-1的每个数进行一遍测试判断是否为素数，有多种写法**
#### 1.最简单的
根据素数的定义，可以对2-n-1进行枚举，如果(n%i==0)，那么n就不是质数，写法如下
```
inline bool prime(int n){
    for(register int i=2;i<n;i++)
        if(n%i==0) return false;
    return true;
}
```
但这段代码在n为素数的时候复杂度会达到O(n)，显然我们需要优化
#### 2.基本优化
由于n的最大因数小于等于$\sqrt{(n)}$，所以只要循环到sqrt(n)即可，写法如下
```
inline bool prime(int n){
    for(register int i=2;i<=sqrt(n);i++)
        if(n%i==0) return false;
    return true;
}
```
在n为素数时复杂度降至了O($\sqrt{(n)}$)，但我们还能继续优化
#### 3.高级优化
这里复制了网上的一段话，找不到原作者出处因此没有挂链接
```
首先看一个关于质数分布的规律：大于等于5的质数一定和6的倍数相邻。例如5和7，11和13,17和19等等；

证明：令x≥1，将大于等于5的自然数表示如下：
······ 6x-1，6x，6x+1，6x+2，6x+3，6x+4，6x+5，6(x+1），6(x+1)+1....
可以看到，不在6的倍数两侧，即6x两侧的数为6x+2，6x+3，6x+4，由于2(3x+1)，3(2x+1)，2(3x+2)，所以它们一定不是素数，再除去6x本身，显然，素数要出现只可能出现在6x的相邻两侧。这里有个题外话，关于孪生素数，有兴趣的道友可以再另行了解一下，由于与我们主题无关，暂且跳过。这里要注意的一点是，在6的倍数相邻两侧并不是一定就是质数。
此时判断质数可以6个为单元快进，即将方法（2）循环中i++步长加大为6，加快判断速度，原因是，假如要判定的数为n，则n必定是6x-1或6x+1的形式，对于循环中6i-1，6i，6i+1,6i+2，6i+3，6i+4，其中如果n能被6i，6i+2，6i+4整除，则n至少得是一个偶数，但是6x-1或6x+1的形式明显是一个奇数，故不成立；另外，如果n能被6i+3整除，则n至少能被3整除，但是6x能被3整除，故6x-1或6x+1（即n）不可能被3整除，故不成立。综上，循环中只需要考虑6i-1和6i+1的情况，即循环的步长可以定为6，每次判断循环变量k和k+2的情况即可
```
所以我们的代码可以这么写
```
inline bool prime(int n){
    if(n==2||n==3) return true;
    if(n%6!=1&&n%6!=5) return false;
    for(register int i=5;i<=sqrt(n);i+=6)
        if(num%i==0||num%(i+2)==0) return false;
    return true;
}
```
这个算法的复杂度大约为O($\frac{\sqrt{(n)}}{3}$),可以说很快了
#### 4.更高级的优化
这是由Michael O. Rabin教授 提出的一种判断质数的方法。

这种方法一个重要的引理即费马小定理 :

当n为素数时,$a^{n-1}$ $\equiv$ 1 (mod n)

剩下的请自行查阅..[传送门](https://baike.baidu.com/item/%E7%B1%B3%E5%8B%92-%E6%8B%89%E5%AE%BE%E7%B4%A0%E6%80%A7%E6%A3%80%E9%AA%8C/22719763?fromtitle=Miller%20Rabin%E7%AE%97%E6%B3%95&fromid=7918305)

实现如下
```
#define ll long long
#define il inline
ll Random(ll n){return ((double)rand()/RAND_MAX*n+0.5);}//该函数返回一个随机值
il ll q_mul(ll a, ll b, ll mod){
    ll z=(long double)a/mod*b;
    ll res=(un ll)a*b-(un ll)z*mod;
    return (res+mod)%mod;
}//该函数求得a×b%mod        O(1)快速乘 你值得拥有
il ll q_pow(ll a,ll b,ll mod){
    ll ans=1;
    while(b)
    {
        if(b&1) ans=q_mul(ans,a,mod );
        b>>=1;
        a=q_mul(a,a,mod);
    }
    return ans;
}//该函数求得a^b%mod       O(log n)快速幂 你值得拥有
il bool witness(ll a,ll n){
    ll tem=n-1;
    int j=0;
    while(!(tem&1)){
        tem>>=1;
        j++;
    }
    ll x=q_pow(a,tem,n);
    if(x==1||x==n-1) return true;
    while(j--)
    {
        x=q_mul(x,x,n);
        if(x==n-1)return true;
    }
    return false;
}
il bool prime(ll n){
    if(n==2)return true;
    if(n<2||n%2==0)return false;
    for(register int i=1;i<=times;i++){
        ll a=Random(n-2)+1;
        if(!witness(a,n))return false;
    }//进行times次判断
    return true;
}
```
单次的复杂度大概为O(k log$^3$n),k是我们测试的不同的a的值

------------
那么我们的程序就可以这么写
```
....
....
....
int n,ans;
int main(){
    scanf("%d",&n);
    for(register int i=2;i<n;i++)
        if(prime(i)) ans++;
    printf("%d\n",ans);
}
```
### 二.筛法
**即快速筛出2-n的所有素数**
#### 1.埃氏筛
对于一个素数，它的所有倍数定然不是素数，因此当筛到一个素数的时候，只要枚举它的倍数标记为false即可。代码实现如下
```
bool prime[N+1];
inline void Eratosthenes(){
    memset(prime,true,sizeof(prime));
    prime[1]=false;//1不是素数要事先标出
    for(register int i=2;i<=N;i++)
        if(prime[i]) for(register int j=2*i;j<=N;j+=i) prime[j]=false;//将素数不大于N的所有倍数标位false
}
```
算法的复杂度为O(n $log$$log$ n).但不难看出，这段筛法在时间上有很大的浪费，例如6，会被2和3筛到，所以我们需要
#### 2.欧拉筛
我们只要让每个合数只被最小的质因子筛一遍即可
```
int p[MAXN];
bool prime[N+1];
inline void Euler(){
	int tot=0;
	memset(prime,false,sizeof(prime));
	for (register int i = 2;i<=N;i++){
 	 	if (!prime[i]) p[tot++]=i;
  		for (register int j=0;j<tot;j++){
        if (i*p[j]>N) break;
        prime[i*p[j]]=true;
        if(i%p[j]==0) break;
  }
}
```
这段算法的复杂度就只有O(n)了


------------
综上，还可以这么写
```
....
....
....
int ans,n;
....
int main(){
    scanf("%d",&n);
    ...();//具体看你选哪种了
    for(register int i=2;i<n;i++)
        if(prime[i]) ans++;
    printf("%d\n",&ans);
}
```


------------

总体来讲，无论哪种方法都能通过本题，但在求区间质数个数时建议用筛法(可以直接在函数内统计1-i的质数个数只是我懒给不出代码),在判断一个较小的数是否为质数时可以用方法一.2或一.3,好写，在判断一个大数字时建议用一.4

---

## 作者：丁丁の丁丁 (赞：2)

咳咳！这道题重复了三次（蒟蒻做了三次这种题）代码贼短并且通俗易懂。
## 代码君来了
~~~~
#include<bits/stdc++.h>//“亿”能头文件，懒人专属。
using namespace std;
int main()
{
	long long n,i,j,x=0,s;
	cin>>n;
	for(i=2;i<=n-1;i++)//到n-1个数
	{
		s=0;//清零的位置很重要
		for(j=2;j<=i/2;j++)
		{
			if(i%j==0) s=1;
		}
		if(s==0) x++;//此段可以写成for(j=2;i<=i;i++){if i%j==0) s++;}if(s==2) x++;但更耗时间！！！
	 } 
	 cout<<x<<endl;
	 return 0;
}
~~~~

---

## 作者：czy0407 (赞：1)

大家好！我又来刷岛国水题了！

题目：AT261

算法：素数表

思路：这就是一道考素数的题目。只要我们用素数表，筛出哪些是素数，哪些不是，再用一个变量统计出一共有几个素数就大功告成了！

## 注意！！！题目说的是2~n-1，不是n！这很容易搞错！


------------
好了，~~废话~~也不多说，上代码。

```cpp
#include<iostream>
#include<cstdio>

using namespace std;
int n,a[1000010],g;//定义n、a数组和g，即到2~n-1的素数、素数表数组和个数统计变量。
int main()
{
	cin>>n;//输入n
	for(int i=2;i<n;i++)//循环筛出素数
	{
		if(a[i]==0)//判断当前数是否为素数
		{
			g++;//素数个数+1
			for(int j=i*2;j<=n;j+=i)a[j]=1;//筛去这个数的所有倍数
		}
	}
	cout<<g<<endl;//输出，注意AT题要回车
    return 0;//完美结束
}
```


---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题属于判断素数的题目，我们只需枚举每个数是否是素数即可。

	#include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    long long n,s,pd;//定义变量
    int main()
    {
    cin>>n;//输入n
    for(int i=2; i<=n-1; i++)//从2循环到n-1
    {
        for(int j=2; j<=sqrt(i); j++)//注意从2开始，我们也不需要循环到i-1
        {
            if(i%j==0){pd=1;break;}//如果除了1和它本身还有因数，pd变1，退出此循环
        }
        if(pd==0)s++;//如果这个数是素数，累加器加1
        pd=0;//记得归零
    }
    cout<<s<<endl;//输出结果，记得换行
    return 0;//要有好习惯
    }
好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：zzhz (赞：0)

# ~~又是一道AT水题~~    
这题不难，是求2~n-1的质数     
注意：
## 是n-1！    不是n！       
~~（差点就WA了）~~     
双手奉上代码       
代码如下：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//命名空间
int n,ans=1;//2自动算为质数
bool s[10001];//false为质数，true为合数
int main(){
    cin>>n;//输入
    n-=1;//是n-1
    for(int i=3;i<=n;i++){//防止爆掉，从3开始
        for(int j=2;j<i;j++){
            if(i%j==0)s[i]=true;//true非质数
        }
    }
    for(int i=3;i<=n;i++){
        if(s[i]==false)ans++;//是false时为质数
    }
    cout<<ans<<endl;//输出
    return 0;
}
```


---

## 作者：真·峭岩仙道 (赞：0)

其实这题并不难，可以定义一个bool类型，如果能整除，就跳过；如果一直不能，就ans++。

注意，每次外循环都要新定义一个bool，否则会bug。

最后输出ans即可。

上代码吧：
```
#include <bits/stdc++.h>
using namespace std;
int main() {
    long long m,ans=0;
    cin>>m;
    for(long long j=2;j<=m-1;j++){
        bool x=true;
        for(long long i=2;i<j;i++){
        if(j%i==0){
            x=false;
            break;
        }
    }
if(x){
    ans++;
}
}
cout<<ans<<endl;
}
```


---

## 作者：Jinyeke (赞：0)

### 题目：求 2~N-1 中的质数个数（只有1和本身两个因数）
#### 人家pascal大佬（巨佬）用筛法，本小蒟蒻偏用暴力枚举，以下为代码（pascal）
```
var
 i,j,n,k,s:longint;
 p:boolean;
begin
 read(n);
 for i:=2 to n-1 do//2~n-1枚举下去（注意：是2~n-
 1）
  begin 
   p:=true;//默认它是一个素数
   k:=i;//i赋值给k
   for j:=2 to trunc(sqrt(k)) do //暴力枚举，注意要trunc（sqrt（K））因为数据范围是<=10000，直接2~n-1枚举可能超时
   if k mod j=0 then p:=false;//如果它除以一个数没有余数，就说明它是一个数（2和本身除外）的倍数，所以它不是素数，并标记
   if p then inc(s);//是素数就+1
  end;
 writeln(s);//输出素数的个数（注意：AT大坑换行输出）
end.
```
### 共建文明洛谷，请勿Ctrl+C！

---

## 作者：LJY_ljy (赞：0)

## 就是判断两个数之间有多少个质数就行了。
~~很简单。~~

------------
#### 判断质数程序：

因数是一对一对的找的，只要在2~sqrt(x)之间找到一个x的因数就可以说明x质数了（返回false），最后返回true。
上代码：
```cpp
bool hs(int x)
{
    for (int i=2;i<=sqrt(x);i++)
    {
        if (x%i==0)
            return false;
    }
    return true;
}
```


上主代码：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
bool hs(int x)//判断质数函数，bool型。
{
    for (int i=2;i<=sqrt(x);i++)
    {
        if (x%i==0)
            return false;
    }
    return true;
}
int main()
{
    int n;
    cin>>n;
    int cnt=0;//一定要记住，cnt一定要赋值为0，否则会很可怕！
    for (int i=2;i<n;i++)//2~n-1,注意看题。
    {
    	if (hs(i))
    		cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}
```
### # 思路极其简单，此题也比较水，不要不想就直接抄代码，请大家创造一个美好的洛谷！！！

---

## 作者：xyn0901 (赞：0)

这道题最骚的地方是它的数据

1和2不加特判会错

我用的筛法，数据大一点应该就超时了qwq
```pascal
var i,j,n,max:longint;
b:boolean;
begin
readln(n);
max:=1;
if (n=2)or(n=1) then begin writeln(0); halt; end;
if (n=3) then begin writeln(1); halt; end;
for i:=3 to n-1 do
begin
b:=true;
for j:=2 to trunc(sqrt(i)) do
if i mod j=0 then begin b:=false; break; end;
if b then max:=max+1;
end;
writeln(max);
end.
```

---

## 作者：Aehnuwx (赞：0)

一个简单的素数判断。

我就写了个最暴力的素数判断，$dalao$勿喷。

话不多说，上代码，代码中有注释，自己看。

$code$

```
#include<cstdio>
using namespace std;
bool is_prime(int);//素数判断的函数
void work();
int n;
int main() {
	work();
	return 0;
}
bool is_prime(int x) {
	if(x==1) return false;//众所周知，1不是个素数！
	for(int i=2; i*i<=x; i++)
		if(x%i==0) return false;//如果发现这个数不止有2个因数，那么它就不是个素数。
	return true;
}
void work() {
	int ans=0;
	scanf("%d", &n);
	for(int i=2; i<=n-1; i++)
		if(is_prime(i)) ans ++;//如果它是个素数，ans++
	printf("%d\n", ans);//貌似AT这个OJ上输出的时候后面必须要加个回车，不然就WA了。害得我也WA了一次
}
```

---

## 作者：char32_t (赞：0)

# 题解 AT261 【与えられた数より小さい素数の個数について】
------------
我来补充线性筛素数的方法

线性筛素数的模版题

code：
```cpp
#include<cstdio>
#include<cstring>
#define _max 10000//注意范围 
bool prime[_max];
int primes[_max];
int num_prime=0;//质数表
int count=0;
void make_prime() {//线性筛素数
    memset(prime, true, sizeof(prime));
    prime[0]=prime[1]=false;
    for(int i=2; i<=_max; i++) {
        if(prime[i]) primes[num_prime++]=i;
        for(int j=0; j<num_prime&&i*primes[j]<_max; j++) {
            prime[i*primes[j]]=false;
            if(!(i%primes[j])) break;
        }
    }
    return;
}
int main(){
    make_prime();//打出质数表
    int n;
    scanf("%d", &n);//读入n 
    for(int i=2; i<n; i++)
		if(prime[i]==true) count++;//扫描并计数 
	printf("%d\n", count);//输出结果 
    return 0;
}
```

---

## 作者：PC_DOS (赞：0)

本题目为一道模拟题，由于数据量比较小(最多仅10000个数)，我们只需要枚举每个数并判断其是不是素数即可。

但是请注意，从样例1我们可以知道，本题目要求的是计算区间[1,n)内的素数的个数，而不是区间[1,n]以内的。

代码:
```
#include <iostream>
#include <cmath>
using namespace std; //头文件和命名空间
inline bool IsPrime(int iNum){ //穷举因数法判断素数
	register int i;
	if (iNum <= 1)
		return false;
	for (i = 2; i <= sqrt(iNum); ++i){
		if (iNum%i == 0)
			return false;
	}
	return true;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	register int i; //循环计数器
	int iEnd, nCount=0; //iEnd-终止数；nCount-个数
	while (cin >> iEnd){ //读入终止数
		for (i = 1; i < iEnd; ++i){ //枚举区间[1,iEnd)中的每一个数
			if (IsPrime(i)) //如果是素数
				++nCount; //计数器加一
		}
		cout << nCount << endl; //输出答案
		nCount = 0; //清零计数器
	}
	return 0; //结束
}
```

---

