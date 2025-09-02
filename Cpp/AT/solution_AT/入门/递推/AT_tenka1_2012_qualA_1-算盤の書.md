# 算盤の書

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2012-qualA/tasks/tenka1_2012_qualA_1

ある数学者は次の問題を考案したという。

- $ 1 $ つがいの兎は、産まれて $ 2 $ か月後から毎月 $ 1 $ つがいずつの兎を産む。
- 兎が死ぬことはない。
- この条件のもとで、産まれたばかりの $ 1 $ つがいの兎は $ 1 $ 年の間に何つがいの兎になるか？

※つがい:オスとメスの一組

   
 この問題は上の問題をもとにした問題です。  
 今、 $ 1 $ つがいの産まれたばかりの兎がいるとします。  
 上の問題の条件と同様に兎が増えるとすると、 $ n $ ヶ月後に何つがいの兎がいるでしょう？  
 このとき、 $ n $ ヶ月後ちょうどに産まれた兎のつがいも数に含めます。

 入力は以下の形式で標準入力から与えられる。 > $ n $

- 何ヶ月後かを表す整数 $ n $ ($ 0\ \leq\ n\ \leq\ 45 $) が $ 1 $ 行で与えられる。
 
 $ n $ ヶ月後の兎のつがいの数を標準出力に $ 1 $ 行で出力せよ。  
 なお、行の終端には改行が必要である。 ```


## 说明/提示

样例 2：

$ 2 $ ヶ月後に $ 1 $ つがい、 $ 3 $ ヶ月後に $ 1 $ つがい、  
   $ 4 $ ヶ月後に $ 2 $ つがい、 $ 5 $ ヶ月後に $ 3 $ つがいが産まれ、  
   初めにいた $ 1 $ つがいと合わせて、合計 $ 8 $ つがいとなる。

## 样例 #1

### 输入

```
0```

### 输出

```
1```

## 样例 #2

### 输入

```
5```

### 输出

```
8```

## 样例 #3

### 输入

```
45```

### 输出

```
1836311903```

# 题解

## 作者：Shiloh (赞：14)

这是道简单的斐波那契题，基本没有不会写的，这里给出一些不同的方法。

```cpp
//循环

#include<iostream>

using namespace std;

int main(void)
{
	int n = 0, f[50] = {1, 1, 2};
    cin >> n;
    for(int i = 3; i <=n; ++i)
    {
    	f[i] = f[i - 1] + f[i - 2];
    }
    cout << f[n] << endl;
}

//三变量法
#include <iostream>

int main(void)
{
    register int f0 = 0, f1 = 1, f2 = 1, n;
    std::cin >> n;
    for(register int i = 0; i < n ;++i)
    {
        f2 = f0;
        f0 = f1;
        f1 = f1 + f2;
    }
    std::cout << f1 << std::endl;
    return 0;
}

//两变量法
#include <iostream>

int main(void)
{
    register int f1 = 1, f2 = 1, n = 0;
    std::cin >> n;
    for(register int i = 1; i < n ;++i)
    {
        f2 = f1 + f2;
        f1 = f2 - f1;
    }
    std::cout << f2 << std::endl;
    return 0;
}

//递归

#include<iostream>

using namespace std;

/*int fab(register int n) //树形递归
{
	if(n == 1||n == 2) 
    {
    	return 1;
    }
	else
    {
    	return fab(n - 1) + fab(n - 2);
}*/
unsigned long long f(register unsigned long long i, register unsigned long long n1, register unsigned long long n2) //迭代递归（尾递归）
{
	return i == 1 ? n2 : f(i - 1, n2, n1 + n2);
}
unsigned long long fab(register unsigned long long i)
{
	return f(i, 1, 1); //封装一下
}
int main()
{
	register int n = 0;
	cin >> n;
	cout << fab(n) << endl;
	return 0;
}

//大斐波那契取余（P4000)
#include <iostream>
#define ll long long

using namespace std;

    const ll maxn = 1e5+5;
    ll dp[maxn * 10] = {}, prime[maxn] = {}, s = 0;
    bool vis[maxn] = {};
    char ch[30000005] = {};
    int len = 0;
inline void init_prime(void)
{
    for(ll i = 2; i < maxn; ++i)
    {
        if(!vis[i]) 
        {
        	prime[s]=i;
            ++s;
        }
        for (ll j=0; j < s && i * prime[j] < maxn; ++j)
        {
            vis[i * prime[j]] = 1;
            if(i % prime[j] == 0) 
            {
            	break;
            }
        }
    }
    return;
}
inline ll pow_mod(ll a1,ll b1)
{
    ll ans=1;
    while(b1)
    {
        if(b1 & 1) 
        {
        	ans = ans * a1;
        }
        b1 >>= 1;
        a1 *= a1;
    }
    return ans;
}
ll pow_mod2(ll a,ll b,ll p)
{
    ll ans = 1;
    while(b)
    {
        if(b & 1) 
        {
        	ans = ans * a % p;
        }
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
inline ll gcd(ll a,ll b)
{
    return b ? gcd(b, a % b) : a;
}
inline bool f(ll n,ll p)
{
    return pow_mod2(n, (p - 1) >> 1, p) == 1;
}
struct matrix
{
    ll x1,x2,x3,x4;
};
    matrix matrix_a,matrix_b,matrix_c;
inline matrix M2(matrix aa,matrix bb,ll mod)
{
    matrix tmp;
    tmp.x1 = (aa.x1 * bb.x1 % mod + aa.x2 * bb.x3 % mod) % mod;
    tmp.x2 = (aa.x1 * bb.x2 % mod + aa.x2 * bb.x4 % mod) % mod;
    tmp.x3 = (aa.x3 * bb.x1 % mod + aa.x4 * bb.x3 % mod) % mod;
    tmp.x4 = (aa.x3 * bb.x2 % mod + aa.x4 * bb.x4 % mod) % mod;
    return tmp;
}
inline matrix M(ll n,ll mod)
{
    matrix a,b;
    a = matrix_a;
    b = matrix_b;
    while(n)
    {
        if(n&1)
        {
            b = M2(b, a, mod);
        }
        n >>= 1;
        a = M2(a, a, mod);
    }
    return b;
}
    ll fac[100][2], l, x, fs[1000];
void dfs(ll count,ll step)
{
    if(step == l)
    {
        fs[x] = count;
        ++x;
        return ;
    }
    ll sum = 1;
    for(ll i = 0; i < fac[step][1]; ++i)
    {
        sum *= fac[step][0];
        dfs(count * sum, step + 1);
    }
    dfs(count, step + 1);
}
inline ll solve2(ll p)
{
    if(p < 1e6 && dp[p]) 
    {
    	return dp[p];
    }
    bool ok = f(5, p);
    ll t;
    if(ok) 
    {
    	t = p -  1;
    }
    else 
    {
    	t = 2 * p + 2;
    }
    l = 0;
    for(ll i = 0; i<s && prime[i] <= t / prime[i]; ++i)
    {
        if(t % prime[i] == 0)
        {
           	ll count = 0;
           	fac[l][0] = prime[i];
           	while(t % prime[i] == 0)
           	{
               	++count;
                t /= prime[i];
            }
           	fac[l][1] = count;
            ++l;
        }
    }
    if(t > 1)
    {
        fac[l][0] = t;
        fac[l][1] = 1;
        ++l;
    }
    x = 0;
    dfs(1, 0);
    sort(fs, fs + x);
    for(ll i = 0; i < x; ++i)
    {
        matrix m1 = M(fs[i], p);
        if(m1.x1 == m1.x4 && m1.x1 == 1 && m1.x2 == m1.x3 && m1.x2 == 0)
        {
            if(p < 1e6) 
            {
            	dp[p] = fs[i];
            }
            return fs[i];
        } 
    }
}
inline ll solve(ll n)
{
    ll ans = 1, cnt;
    for(ll i = 0; i < s && prime[i] <= n/prime[i]; ++i)
    {
        if(n % prime[i] == 0)
        {
            ll count=0;
            while(n % prime[i] == 0)
            {
                ++count;
                n /= prime[i];
            }
            cnt = pow_mod(prime[i], count - 1);
            cnt *= solve2(prime[i]);
            ans = (ans / gcd(ans, cnt)) * cnt;
        }
    }
    if(n > 1)
    {
        cnt = 1;
        cnt *= solve2(n);
        ans = ans / gcd(ans, cnt) * cnt;
    }
    return ans;
}
int main(){
    ll t, n, MOD, num = 0;
    init_prime();
    matrix_a.x1 = matrix_a.x2 = matrix_a.x3 = 1;  
    matrix_a.x4 = 0;
    matrix_b.x1 = matrix_b.x4 = 1;  
    matrix_b.x2 = matrix_b.x3 = 0;
    dp[2] = 3;
    dp[3] = 8;
    dp[5] = 20;
    scanf("%s", ch + 1);
    len = strlen(ch + 1);
    scanf("%lld", &n);
    MOD = solve(n);
    for(int i = 1; i <= len; ++i)
    {
        num = num * 10 + ch[i] - '0';
        while(num >= MOD) 
        {
        	num -= MOD;
        }
    }
    matrix_c = M(num, n);
    printf("%lld", matrix_c.x2); 
    return 0;
}


```

---

## 作者：Invalid_index (赞：3)

日常AT水题   
斐波那契数列呀！！！    
居然一次没过？！！！    
~~直接递归即可~~
```
long long fib(int n){
	if(n==1||n==0){
		return 1;
	}
	return fib(n-1)+fib(n-2);
}
```

什么！！！   
这题卡递归！！！   
TLE了三个点！！！    
记忆化即可
```
int main(){
    int f[100];
    memset(f,0,sizeof(f));
    f[0]=f[1]=1;
    int n;
    cin>>n;
    for(int i=2;i<=50;i++){
        f[i]=f[i-1]+f[i-2];
    }
    cout<<f[n]<<endl;
    return 0;
}
```
这才是真正的AC码
# 记得AT卡换行！！！

---

## 作者：Cambridge (赞：1)


小学生又来发题解了！

这是一道典型得不能再典型的斐波那契数列了，相信各位大佬也都知道如何计算。具体请看下方代码······

	#include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int n;
    int a[1000];//定义变量
    int main()
    {
    cin>>n;//读入n
    a[0]=1,a[1]=1,a[2]=2;//特殊的数
    for(int i=3; i<=n; i++)
    a[i]=a[i-1]+a[i-2];//这个数等于前两个数的和。
    cout<<a[n]<<endl;//输出结果并换行
    return 0;//要有好习惯
    }
# AT不换行，爆零两行泪
好了，本蒟蒻就讲到这里，希望对读者有所帮助


---

## 作者：封禁用户 (赞：1)

这道题好lj啊
```
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c;
int main()
{
    cin>>n;
    a=1;b=2;
    for(int i=2;i<n;i++)
    {
        c=a+b;
        swap(b,c);
        swap(a,c);
    }
    if(n!=1&&n!=2)
    cout<<b;
    if(n==1)
    cout<<1;
    if(n==2)
    cout<<2;
    return 0;
}
```

简单易懂的程序~

---

## 作者：CZQ_King (赞：1)

# 此题无须用$for$!!!
用公式就搞~~腚~~定了。


------------
### 公式：
斐波那契数列第$n$项：$\frac{1}{\sqrt{5}}[(\frac{1+\sqrt{5}}{2})^n-(\frac{1-\sqrt{5}}{2})^n]$
### 还有一个更简单的：
斐波那契数列第$n$项：$round(\frac{1.618^n}{\sqrt{5}})$，$round()$为四舍五入。
### 蒟蒻这里只使用第一个公式，代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int n;//第n项
double ans;//答案
int main(){
    cin>>n;//输入第n项
    n++;
    
    ans+=pow((1+sqrt(5))/2,n);
    ans-=pow((1-sqrt(5))/2,n);
    ans/=sqrt(5);
    /*按照公式模拟*/
    cout<<fixed<<setprecision(0)<<ans<<endl;//输出答案
    return 0;//结束
}
```

---

## 作者：起名困难症 (赞：1)

真的好水啊，纯属斐波那契数列日本版

开始吧，一看就发现了规律，当前等于前两个数的和。

上代码吧：

```cpp
#include<iostream>//文件头
#include<cstdio>//文件头
#include<cmath>//文件头
using namespace std;
int n,ans;//定义
int a[1000100]; //定义
int main()
{
    cin>>n;//读入
    if(n==0){cout<<1<<endl;return 0;}//如果等于0，直接输出1，结束。
    a[1]=1;//1位置=1
    a[2]=2;//2位置=2
    for(int i=3;i<=n;i++)//规定了前两个，要从第三个开始
    {
    	a[i]=a[i-1]+a[i-2];//当前等于前两个数的和
    }
    cout<<a[n]<<endl;//输出N的位置的数
	return 0;
}
```
# 拜拜了，好水

---

## 作者：紫金依旧 (赞：0)

今日第三弹题解。

只需要注意一个点—— 
# 不开long long见祖宗。

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,feibo[50]={1,1,2},ans;
int main()
{
    cin>>n;
    for(int i=3;i<=n;i++)
        feibo[i]=feibo[i-1]+feibo[i-2];
    ans=feibo[n];
    cout<<ans<<endl;
    return 0;
}
```

祝各位OIer们OI愉快。

祝自己RP++。

---

## 作者：有限光阴 (赞：0)

# ~~如此水的一道水题~~
相信没人能看到我这篇题解了
#### 因为......
斐波那契数列实在是太水了%%%

废话不多说,上代码;
```
#include<bits/stdc++.h>//万能头文件;
using namespace std;
long long f[100001];//数组;
int main(){
	long long a;
	cin>>a;
	f[0]=1;
	f[1]=1;
	for(int i=2;i<=a;i++)
	  f[i]=f[i-1]+f[i-2];//斐波那契数列的推导;
	cout<<f[a]<<endl;//AT的题目一定要换行;
	return 0;//好习惯;
}
```
~~不喜勿喷~~

------------
这里告诉一些不怎么做AT题的朋友

AT题都需要--**换行**

---

## 作者：zzhz (赞：0)

说实话这题很水     
话不多说，直接上代码     
代码如下：    
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//命名空间
int main(){
    int n,a[10001]={1,1};
    cin>>n;//输入
 列
        for(int j=2;j<=n;j++){
            a[j]=a[j-1]+a[j-2];//斐波那契数列      }
        cout<<a[n]<<endl;//输出斐波那契数列的第n项
    return 0;//结束
}
```

简单易懂的程序~

---

## 作者：我是蒟弱 (赞：0)

## 这道题，在此提供三种方法：

### 1.用a,b,c模拟斐波那契数列操作

想法： 设 两个连续的斐波那契数 a=1,b=2

    第一步，令c=b      即 a=1,b=2,c=2
    第二步，令b=a+b    即 a=1,b=3,c=2
    第三步，令a=c      即 a=2,b=3,c=2

其中，第一步c是临时变量，存储原来b的值

第二步让b变成下一项

第三步让a变成下一项（原来的b）

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int main(){
	int a=1,b=2,c,n;//设定变量a,b,c
	cin>>n;//输入项数
	if(n==0||n==1){
		cout<<1<<endl;
		return 0;
	}else if(n==2){
		cout<<2<<endl;
		return 0;
	}//特判
	for(int i=3;i<=n;i++){
		c=b;
		b+=a;
		a=c;
	}//进行模拟操作
	cout<<b<<endl;//输出b，因为b是大的数，是我们要求的数
	return 0;
}
```

### 2.用数组模拟斐波那契数列

想法：设定一个f数组，使f[i]=斐波那契数列第i项的值

先初始化：f[0]=1,f[1]=1,f[2]=2

详见代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int main(){
	int f[46]={},n;//设定一个数组
	f[0]=f[1]=1;
	f[2]=2;//初始化
	cin>>n;//输入要求的项
	for(int i=3;i<=n;i++){
		f[i]=f[i-1]+f[i-2];//用数组进行模拟
	}
	cout<<f[n]<<endl;//输出所求的项
	return 0;
}
```

### 3.打表

考验数学的时间到了！

打表实际上并不难，只要算对数。 ~~算错WA了不关我事（逃）~~

代码：
```
#include<iostream>
using namespace std;
int a[46]={1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903};//打表
int main(){
	int n;
	cin>>n;//输入要求的项
	cout<<a[n]<<endl;//输出所求的项
	return 0;
}
```


---

## 作者：TCZN (赞：0)

## 坑

刚刚看见这道题是十分激动，[双倍经验](https://www.luogu.org/problemnew/show/P1720)

后来才发现，这不是正常的斐波拉契啊

**正常的斐波拉契数列**：当n=1时，f(n)=1；|| n=2时，f(n)=2;|| n=3，f(n)=4...以此类推 

但是这道题是**不正常的斐波拉契数列**：当n=1时，f(n)=1； ||   n=2时，f(n)=**3**；|| n=3，f(n)=**6**...以此类推

这还不是最大的坑，因为题目中写出了这道题的斐波拉契数列，可以看到只有一个1，而最大的坑，就在n的数据范围 ```( 0 ≤ n ≤ 45 ) ```，有0，而这时f(n)就=1了，所以：
```pascal
var
  a:array[1..50] of int64;
  i,n:longint; //注意，循环变量不支持int64类型
begin
 readln(n);
  a[1]:=1;a[2]:=2; //初始化，因为第二项是2
  if n=0 then //打个表
   begin
    writeln(1);
    halt; //使用halt会直接结束程序，不会继续执行下面的语句
   end;
  for i:=3 to n do
   a[i]:=a[i-1]+a[i-2]; //正常的斐波拉契数列累加
   writeln(a[n]);//输出
end.
```


---

## 作者：judgejudge (赞：0)

# 动态规划
此处我们根据公式f[n]=f[n-1]+f[n-2]来进行编写：

首先我们利用**动态规划会保存的思想**：首先从大往小推，直推到n==0||n==1||n==2的时候，再return 1或return 2，这样就可以了。

主要是用一个数组存储，并且此题数据范围是0<=n<=45不会爆！！！

注意一开始数组要赋值为-1.

下面奉上AC代码：
```cpp
#include <iostream>
using namespace std;
int a[1000];
int f(int n){
	int i,k=0;
	if(a[n]==-1){//此处根据动规思想节省时间
		if(n==0||n==1)a[n]=1;
		if(n==2)a[n]=2;//发现是0，1，2就return
		if(n>2)a[n]=f(n-1)+f(n-2);//其他的利用公式计算
	}
	return a[n];
}
int main(){
	int i,j,k,n;
	cin>>n;
	for(i=0;i<=n;i++)a[i]=-1;//初始值为-1
	cout<<f(n)<<endl;
	return 0;
}
```


---

## 作者：硫酸钒酰 (赞：0)

$\Huge\text{首先，}$

$\Huge\text{要在输出后换行！！！}$

大家是不是都被坑了?实际上，ATの题~~好像~~都要在输出后换行……

首先，这是道水题，但是有坑：

>1.岛国の题，一定、一定、一定记得换行！！！！（我就因为没换行，死了一次……）

>2.斐波那契数列，注意用递推，代码少，不占空间。（虽然现在的内存已经不珍贵了，但在之前，呵呵，我家的台式电脑购买时赠的U盘只有240MB……所以你懂的）

>3.注意会有“0”的情况！易知，N=0时，ans=1，加入特判或将递推是往前写一位即可。

讲一下递推的用处吧：

>1.上面说过了，省内存。

>2.用有限的语句，能表述出无穷的情况，是数学上很有用的方法。

但是要想用递推，必须写函数（不会的同学快去学……）

好了，不废话了，上代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>    //因为学校的OJ上不让用#include<bits/stdc++.h>，所以每次写代码必写这五个头文件
using namespace std;
int fbnq(long long n)    //函数来了
{
    long long a0=1,a1=1,a2=2;
    if(n==0) return 1;
    if(n==1) return 1;    //两次特判，n=0和1时的情况
    while(n>=2)
    {
        a0=a1;a1=a2;a2=a0+a1;
        n--;     //递推
    }
    return a1;    //返回值
}
int main()    //主函数
{
    long long n,ans;
    scanf("%lld",&n);
    ans=fbnq(n);
    printf("%lld\n",ans);    //用scanf和printf速度更快
    return 0;    //结束程序
}
```

就是这样，喵~~

---

## 作者：一飞冲天666 (赞：0)

第一次题解，望通过QAQ

显然 fib（n）=fib（n-1）+fib（n-2）

斐波那契可以用递归和递推

注意第0项是1

# 递归
code
```
#include<iostream> 
using namespace std;

int fib(int n)
{
	if(n==1||n==0)//递归出口
	{
		return 1;
	}
	if(n==2)//递归出口
	{
		return 2;
	}
	else
	{
		return fib(n-1)+fib(n-2);//套用公式
	}
}

int main()
{
	int n;
	cin>>n;
	cout<<fib(n)<<endl;/
	return 0;
}
```

~~超时了。。。~~

# 递推

```
#include<iostream> 
using namespace std;
int main()
{
    int n;
    int fib[50];//定义数组
    cin>>n;
    fib[0]=fib[1]=1;//初始化
    fib[2]=2;//初始化
    int a,b;
    for(int i=3;i<=n;++i)
    {
        fib[i]=fib[i-1]+fib[i-2];//再次套用公式
    }
    cout<<fib[n]<<endl;
    return 0;
}
```
# 当然
```
#include<iostream> 
using namespace std;
int main()
{
    int n;
    int fib[50]={1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903};
    cin>>n;
    cout<<fib[n]<<endl;
    return 0;
}
```
# 打表大法吼！！！

---

## 作者：快乐的坤 (赞：0)

    var a:array[0..45] of int64;//（其实斐波拉契数列的第一二个数都是1的）n<45，所以直接最大45就好了。
    n,i:int64;//定的大一点才保险啊。
    begin
      a[0]:=1;//千万别被这里坑了，也是有a0的呀。
      a[1]:=1;//这个可不要放到for里呦。
      for i:=2 to 45 do//直接从2开始，不然会倒霉，并且to45是万能的呀。
        a[i]:=a[i-1]+a[i-2];//直接暴力计算，-1、-2可是前两个呀。
      readln(n);//输入n以便输出
      writeln(a[n]);//最后就是输出语句了。
    end.

---

## 作者：Soyilieber (赞：0)

我敢打赌这是数据最小的斐波那契了，只有45……

pascal最简洁代码：

```pascal
var
    i,n:longint;
    a:array[0..45]of longint;
begin
    a[0]:=1;//初  化
    a[1]:=1;//  始  哟
    readln(n);                     / /输入
    for i:=2 to n do a[i]:=a[i-2]+a[i-1];//累加前两项
    writeln(a[n]);//输出
end.
```

---

## 作者：幻蓝 (赞：0)

超短p党代码
```pascal
var
        n,i:longint;
        a:array[0..10000]of longint;
        ans:int64;
begin
        readln(n);
        a[0]:=1; a[1]:=1;
        for i:=2 to n do
                a[i]:=a[i-1]+a[i-2];
        writeln(a[n]);
end.
```

---

## 作者：远山淡影 (赞：0)

直接上代码。
```cpp
#include<cstdio>  
#include<cstring>  
#include<cstdlib> 
#include<cmath> 
using namespace std;  
int n;
int a[2100];
int main()
{
	scanf("%d",&n);
	a[0]=1;a[1]=1;//第0项和第1项都是1。 
	for(int i=2;i<=n;i++)//从第2项开始循环。 
	{
		a[i]=a[i-1]+a[i-2];//斐波那契公式：第i项=第i-1项+第i-2项。 
	}
	printf("%d\n",a[n]);//输出。 
	return 0;
}
```

---

## 作者：char32_t (赞：0)

# 题解 AT240 【算盤の書】
------------
这道题的数列其实是从**斐波那契数列**的第二项开始的，那么就可以使用矩阵求解

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<vector<long long int> > mul(vector<vector<long long int> > &a, vector<vector<long long int> >&b) {//计算a*b 
	vector<vector<long long int> > c(a.size(), vector<long long int>(b[0].size()));
	for(int i=0; i<a.size(); i++)
		for(int k=0; k<b.size(); k++)
			for(int j=0; j<b[0].size(); j++) c[i][j]=(c[i][j]+a[i][k]*b[k][j]);
	return c;
}
vector<vector<long long int> > pow(vector<vector<long long int> > a, long long int n) {//计算a^n 
	vector<vector<long long int> > b(a.size(), vector<long long int>(a.size()));
	for(int i=0; i<a.size(); i++) b[i][i]=1;
	while(n>0) {
		if(n&1) b=mul(b, a);
		a=mul(a, a);
		n>>=1;
	}
	return b;
}
long long int n;
int main() {
	scanf("%lld", &n);//输入 
	vector<vector<long long int> > a(2, vector<long long int>(2));
	a[0][0]=1;
	a[0][1]=1;
	a[1][0]=1;
	a[1][1]=0;
	a=pow(a, n+1);//注意是从第二项开始的 
	printf("%lld\n", a[1][0]);//输出
	return 0;
}
```

---

## 作者：TomLovesRita (赞：0)

打表打表~
```
#include <iostream>
#include <cstdio>
using namespace std;
int fib[9999]={1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903};//可爱的表~~
int a;
int main() {
	scanf("%d", &a);
	printf("%d\n", fib[a]);//输出
	return 0;
}
```

---

## 作者：人间凡人 (赞：0)

大家一定很熟悉斐波那契数列吧。

规律就是第$0$项为$1$,第$1$项为$1$,从第二项开始,这一项为前两项之和。

现在我就来给大家展现斐波那契的三种写法。

第一种：**数组递推(便捷)**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[50];
int main() {
	scanf("%d",&n);a[0]=1;a[1]=1;
	for(int i=2;i<=n;i++)a[i]=a[i-1]+a[i-2];
	printf("%d\n",a[n]);
	return 0;
}

```

第二种：**递归(超时)**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[50];
int dfs(int x){
	if(x==0||x==1)return 1;
	return dfs(x-1)+dfs(x-2);
}
int main() {
	scanf("%d",&n);
	printf("%d\n",dfs(n));
	return 0;
}

```

第三种：**变量递推(省时+省空)**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,b,c;
int main() {
	scanf("%d",&n);
	if(n==0||n==1)printf("1\n");
	else{
		a=1;b=1;
		for(int i=1;i<n;i++){
			c=a+b;
			a=b;b=c;
		}
		printf("%d\n",c);
	}
   return 0;
}

```



---

## 作者：封禁用户 (赞：0)

### ~~又是一岛国水题QAQ~~


##### 这道题看似~~“十分复杂”~~其实就是典型的斐波那契数列

斐波那契数列还有一个名字叫兔子繁殖问题QAQ

啥话也不说啦先附上代码

	#include<cstdio>
	#include<cstring>//字符串处理需用库QAQ
	#include<iostream>
	#include<algorithm>//stl库
	using namespace std;
	int main(){
		int f[2333],n;//定义变量2333
		cin>>n;//读入n
		f[0]=f[1]=f[2]=1;//将当n等于0,1,2时的值赋为1
 	//这个题还有个坑是如果n=0是输出一，欸我就是卡在这个坎上啦
		for(int i=2;i<=n;i++){//进入循环
			f[2]=f[0]+f[1];//同下
			f[0]=f[1];//同下
			f[1]=f[2];//实现斐波那契数列换算
		}
		cout<<f[2]<<endl;//输出
		return 0;//程序结束
	}
 ### 但是不要忘了岛国的题目都需要换行
### 不然就会——~~稻花香里说丰年~~

---

