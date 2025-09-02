# ぶんたん

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2012-final/tasks/tenka1_2012_final_a

 フィボナッチ数列は、以下のような漸化式で表される数列 $ F_0,\ F_1,\ F_2,\ …\ (=0,\ 1,\ 1,\ 2,\ 3,\ 5,\ 8,\ 13,\ …) $ であり、フィボナッチ数はこの数列に現れる数 $ F_i\ (i\ \geq\ 0) $ です。

- $ F_{0}\ =\ 0 $
- $ F_{1}\ =\ 1 $
- $ F_{i+2}\ =\ F_{i}\ +\ F_{i+1} $ ($ i\ \geq\ 0 $)

 ある正整数 $ n $ をいくつかのフィボナッチ数の和として表すことを考えます。  
 このとき、和が正整数 $ n $ となるフィボナッチ数の個数として考えられる最小の値を答えなさい。  
 ただし、同じフィボナッチ数を複数回用いることもできるものとし、複数回用いた場合はそれぞれ別々に数えるものとします。

 入力は以下の形式で標準入力から与えられる。 > $ n $

- 正整数 $ n $ ($ 1\ \leq\ n\ \leq\ 10^{10} $) が $ 1 $ 行で与えられる。
 
 与えられる数が小さい入力 ($ 1\ \leq\ N\ \leq\ 10^5 $) のみ正解すると、$ 100 $ 点満点に対して部分点として $ 50 $ 点が与えられる。 和が正整数 $ n $ となるフィボナッチ数の個数として考えられる最小の値を $ 1 $ 行で出力せよ。  
 なお、行の終端には改行が必要である。

# 题解

## 作者：infinities (赞：7)

和楼上一样，依然是贪心，不过~~自认为~~比楼上的好理解些：
- 只要能选大的数，绝不选小的。
- 所以这就要求我们倒序枚举
- 由于斐波那契数列的数增长快，所以时间复杂度不会太高
- 其实按我的思路有两种实现方法。

核心代码之一（一般人都会写）：
```cpp
    for(int i=1;i<=l;i++){//考虑最坏情况，就是n只能用很小的数累加，即n较小
        for(int j=m;j>=1;j--){//从大数向小数一个个枚举
            if(a[j]<=n){n-=a[j],k++;break;}//如果减去这个数n不会变成负数，计数器加1，n减去对应数
        }
        if(n==0)break;//如果减完了，break
    }
```
核心代码之二：
```cpp
    for(int j=m;j>=1;j--){
        while(n-a[j]>=0)n-=a[j],k++;//能减就使劲减
        if(n==0)break;//减完了跳出循环
    }
```
完整代码之一：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[111]={0,1,1}/*斐波那契数列*/,n,m,k=0,l;//l是防止n的值被改变
int main(){
    cin>>n;
    l=n;//将n赋值给l
    for(int i=3;i<=100;i++){
        a[i]=a[i-1]+a[i-2];//斐波那契数列
        if(a[i]>n){m=i;break;}//因为比n还大的数用不到，所以一旦过大，直接break
    }
    for(int i=1;i<=l;i++){//考虑最坏情况，就是n只能用很小的数累加，即n较小
        for(int j=m;j>=1;j--){//从大数向小数一个个枚举
            if(a[j]<=n){n-=a[j],k++;break;}//如果减去这个数n不会变成负数，计数器加1，n减去对应数
        }
        if(n==0)break;//如果减完了，break
    }
    cout<<k<<"\n";//输出最后结果以及换行
    return 0;
}
```
这里是经过一点优化的简便写法（即，第二种写法，可以AC）:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[111]={0,1,1},n,m,k=0,l;//操作和前面一样不多讲
int main(){
    cin>>n;
    l=n;
    for(int i=3;i<=100;i++){
        a[i]=a[i-1]+a[i-2];
        if(a[i]>n){m=i;break;}//不多讲
    }
    for(int j=m;j>=1;j--){
        while(n-a[j]>=0)n-=a[j],k++;//能减就使劲减
        if(n==0)break;//减完了跳出循环
    }
    cout<<k<<"\n";//输出换行
    return 0;
}
```
好了，两次AC

---

## 作者：zjyqwq (赞：6)

### AT269 ぶんたん题解

C++题解。

本题没有样例，希望管理员增添一组样例。

------------
#### 解题思路

先构造斐波那契~~肥不拉几~~数列。

这里可以通过单判当前这个斐波那契数是否大于 $n$ ，是的话记录当前这个数的位置，并退出循环，这样可以省时间~~虽然省不了多少~~。

接着，重点来了。要想用的数最少，是不是这个数取得越大越好？
##### 越大的数取得越多，总数取得越少。
我们这里就可以用贪心的思想做。我们就把上文记录的位置倒着循环，从大循环到小，每个数都要取到不能再取为止。比如 $10$ ,能取 $8$、$2$ 就不要变成 $5$、$3$、$2$。这道题目就迎刃而解了。

------------
#### 注意事项

 - AT要换行。
 - 十年OI一场空，不开longlong见祖宗，建议开long long。
 - 贪心时要倒着循环。
 
------------
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register //骚气宏定义，这个关键字可以提速。
#define w_ putchar(' ') //能用字符输入输出就不要用cincout。
#define wn putchar('\n')//同理，这个比endl要快得多。
inline int mmax(R int x,R int y){return x>y?x:y;}
inline int mmin(R int x,R int y){return x<y?x:y;}
inline void swap(R int &x,R int &y){R int t=x;x=y;y=t;}//卡常加卡常，拒绝STL，因为STL太慢了。
inline void read(R long long &y){
   R long long s=0,w=1;
   R char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   y=s*w;
}
inline void write(R int x){
    if(x < 0){
        putchar('-');
        write(-x);
        return;
    }
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}//我可能有重度卡常症（瞎编的），为了速度，坚持原则。
 int main(){
 	R long long a[105]={0},n;
 	R int k=0,m=0;
	read(n);//输入n。
	a[1]=1;a[2]=1;//将数组赋初值，前两个赋值好，方便后面递推。
	for(R int i=3;i<=100;++i){//小伙汁，++i比i++快哦。
		a[i]=a[i-1]+a[i-2];//将斐波那契数列推出来。
		if(a[i]>n){
		m=i;break;
	    } //一个小优化。
    }
	for(R int j=m;j>=1;--j){
		while(n>=a[j]){//能取大的就不要取小的。
			n-=a[j];
			++k;
		}
		if(n==0)break;//亿个小优化，如果n已经被取完了，就可以退出循环了。
	}
	write(k);wn;//输出。
 	return 0;
}

```


------------
结束了！！！

---

## 作者：RioBlu (赞：5)

贪心：要是$n-f[s]>0$ 那么：要不要选$f[s-1]$呢？

不要，这样使得k更大

万万没想到AC了
```
#include<bits/stdc++.h>
using namespace std;
long long a,now,f[100]={1,1},ans;
int main()
{
	cin>>a;
	for(int s=2;s<60;s++)//之前开到40，WA了一半
	{
		f[s]=f[s-1]+f[s-2];//斐波那契数列
	}
	now=59;
	while(a>0)
	{
		if(f[now]>a)
		{
			now--;
		}
		else a-=f[now],ans++;
	}
	cout<<ans<<endl;//输出答案
	return 0;
}
```

---

## 作者：_Arahc_ (赞：2)

本题没有样例，这里随便先给四个样例供各位测试，一个正常样例，两个特殊样例，一个大样例：

样例1：
$in:$ 30，$out:$ 3

样例2：
$in:$ 13，$out:$ 1

样例3：
$in:$ 1，$out:$ 1

样例4：
$in:$ 314159265，$out:$ 11

都能过就差不多了

---

看到“同一个数可以使用多次”就可以推测出这题是贪心了。

不然$10^{10}$的数据你也不好$DP$，再说这道题很明显就具备贪心选择性。

这道题可以直接推出来斐波那契数列，反正复杂度不高。

不过既然斐波那契数列递推不是很麻烦，所以可以提前打表，避免毒瘤出题人出的卡常数优化的数据。

虽然这道题不需要表，但这是一个技巧，考试可以用到。

所以先贴上打表代码：

 ```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[65];
int main(){
   f[0]=f[1]=1;
   printf("1,1,");
   for(register int i=2;i<65;++i){
		f[i]=f[i-1]+f[i-2];	//斐波那契递推公式
		printf("%lld,",f[i]);
	}
	return 0;
}

```
把表运行一下，简单整理即可

现在来处理贪心策略：

既然我要让最终结果，也就是选的数量尽量少，该怎么办呢？

结论是：每次选择中选数字尽量大的。

本来这里想写我不会证的，本着做良心题解的观念，我摸索出了大致的证明：

---

**证明：**

首先直接上$\color{purple}\text{齐肯多夫定理}$：

齐肯多夫定理表示任何正整数都可以表示成若干个不连续的斐波那契数（不包括第一个斐波那契数）之和。这种和式称为齐肯多夫表述法。

#### 齐肯多夫表述法可以通过贪心得到：每次选最大的。

现在证明为什么这样是个数最小的：

假设有两个数相邻：

直接$f_{i}+f_{i+1}=f_{i+2}$ 合并。

所以不是齐肯多夫表述法的分解方法一定不是最小的。

继续证……

假设一个斐波那契数$m$，在不超过$m$的斐波那契数中选若干不连续的，最大和是多少呢？

举个例子，$m=13$。在$1,1,2,3,5,8$里面怎么选呢？当然是$8+3+1=12$。

这是一个简单的结论，在不超过$m$的斐波那契数中选若干不连续的，最大和是$m-1$

所以一个数$i$，我想找到它的$2$种齐肯多夫表述法，现已用贪心找到一种。

假设贪心出来要分$f_{j}$，但我不想分$f_{j}$，那么剩下的分法中，最大和是？

当然是$f_{j-1}+f_{j-3}+f_{j-5}+......+1$。

这一坨加起来是$f_{j}-1$。

所以如果我不分出$f_{j}$，随我怎么分我也凑不出一个$f_{j}$。

到这里我们证了一个推论：齐肯多夫分解是唯一的。

而刚刚我们还证出不是齐肯多夫表述法的分解方法一定不是最小的。

所以得出结论了，齐肯多夫表述法的分解方法一定是最小的，而且是唯一的。

这个齐肯多夫表述法怎么来的？看看上文……

用贪心，每次选最大的。

得证：每次选最大的数的策略一定可以得到最少的分解数字数量。

---

那么找到比$n$小（或相等）的最大的斐波那契数，顺序查找、二分、STL……都可以解决。

既然其他题解都是顺序查找，那我上一个$\color{Green}\text{二分}$代码吧，顺带练习二分。

 ```cpp
inline int bs(){
	int l=0,r=64;  //待会解释为什么是0和64
	while(l<=r){
		int m=(l+r)>>1;  //位运算，等价于（l+r）/2
		if(f[m]<=a && f[m+1]>a) return m;
		if(f[m]<=a) l=m+1;
		else r=m-1;
	}
}
```
$\color{Green}\text{最终代码（注释版）：}$

（注意：代码不完整，缺少快读快写函数和那张超级丑的表）

 ```cpp
#include<bits/stdc++.h> //万能头，CSP可以用，亲测
using namespace std;

// 省去快读快写函数

long long a;// 省去表
int n,s;

inline int bs(){
	int l=0,r=64;  //0和64分别为数组的首项与末项下标
	while(l<=r){
		int m=(l+r)>>1;
		if(f[m]<=a && f[m+1]>a) return m;
		if(f[m]<=a) l=m+1;
		else r=m-1;
	}
}

// 二分，不熟练者可以请教神犇或者直接百度

int main(){

	a=read(); //已经很少遇见如此简单的输入了
   
    while(a>0){
        n=bs();	// 二分找到小于等于 a 的最大的斐波那契数是第几项
        a-=f[n];	// 贪心，直接减不用管
        s++;	//统计我选了几个数
    }

   write(s),putchar('\n');
  
// 不要忘记AT的题目在末尾要输出一个换行，不然会WA
	return 0;
}

```
结果：AC，全部 1ms。

---

题解修改史：

updata：$2020.1.15$ 修改了一个错别字和部分句子

updata：$2020.1.15$（深夜）题解审核失败，原因【排版不整齐】，修改了题解部分内容

$2020.1.18$ 再次丑拒，放弃本题。

updata：$2020.1.27$ 抱着最后一丝希望，重构题解，提交……

---

## 作者：Dark_Sky (赞：1)

#### 这是本蒟蒻的第一篇题解，如果写的不好，请各位神犇和大佬们指教

思路：先把fibo数组中全装上斐波那契数，然后和输入的数比较大小，
若fibo大于n（输入的数）执行下一次循环，若fibo小于等于n，就让n减去
fibo，然后接着循环，直到n被减成0，break掉，循环结束。（为了节省时间，这里用了记忆化搜索来赋值fibo数组）

```
#include <iostream>

using namespace std;
typedef long long ll;
ll memo[10086];//记忆化搜索
ll s;//计数器，记了n被减了几次(全局变量自动初始化为0)
ll i;
ll fib(ll n){//给fibo数组赋值用
	if(memo[n] != 0)return memo[n];//记忆化搜索(一个小小的优化)
	if(n == 1 || n == 2)return memo[n] = 1;
	return memo[n] = fib(n-1) + fib(n-2);
}

int main(){
	ll n;
	cin>>n;
	long long fibo[10086];//装斐波那契数列的数组
	for(i = 1;i <= 10086;i++){
		fibo[i] = fib(i);//往斐波那契数列的数组中装斐波那契数
		if(fibo[i] > n){//如果一个斐波那契数大于n，停止循环
			break;
		}
	}
	for(int j = i;;j--){//无限次循环，直到n被减成零时结束（其实写j >= 0也行）
		while(n - fibo[j] >= 0){
			n -= fibo[j];//n开始被减
			s++;//减一次,s记一次
		}
        	if(n == 0)break;//当n被减光了,跳出循环
	}
    
	cout<<s<<endl;//输出
	
	return 0;
}
```
提交代码后,所有测试点几乎都是1ms(第120个点2ms)

还有记得开long long，我最早开的都是int，WA了20个点。

---

## 作者：vectorwyx (赞：1)

## 贪心


------------
读题，抽象出来就是：

给定一个正整数$n$，

求**至少**需要多少个斐波那契数才能使其和等于$n$

斐波那契数**可以重复使用**

------------
我们一开始想到的方法应该是完全背包

但是，转念一想，能不能贪心呢？

事实上，能！

贪心的方法：

**尽可能多的选最大的数，再考虑次大的数**

直到无法再选

------------
为什么呢？

考虑一下斐波那契数列的性质，有这么一条：

**对于数列中的任意一项$F(i)$，$F(i)$总能由其余项求和或求差得到**

那假如现在有$F(i)$<$n$ 
             
我们要不要改为选$F(i-1)$呢？

换句话说，选$F(i-1)$会不会得到优于$F(i)$的解呢？

不会。因为如果我们改为选$F(i-1)$，那还差$F(i)$-$F(i-1)$

这意味着我们至少又要选一个数来“弥补”空缺

**显然$k$的值会更大**


------------
故本题可以用贪心解决

首先用递推预处理出斐波那契数列

然后贪心**从大到小**选数（也就是**逆序遍历**）

能选就ans++

------------
代码如下：
```cpp
#include<iostream> 
#include<cstdio>
#define maxn 1001
#define ll long long//宏定义ll 省事
using namespace std;
ll a[maxn];//存储斐波那契数列
int main(){
	ll n,x=2,t,ans=0;//注意数据范围要用long long
	a[0]=0;//递推初始化
	a[1]=1;//
	cin>>n;
	while(1){//递推
		a[x]=a[x-1]+a[x-2];
		if(a[x]>n) break;//大于n就不用再推了
		++x;
	}
	t=n;//代替n作为循环条件
	for(register ll i=x-1;i>0;--i){//逆序遍历斐波那契数列
		while(n-a[i]>=0){//只要还能选就可着劲的选
			ans++;
			n-=a[i];
		}
	}
	cout<<ans<<endl;//千万要输出换行！！！否则会爆
	return 0;
}
```


---

## 作者：_ZhouYuHan_ (赞：0)

实际上，这道题还是很水的。

我们只需运用贪心思想，从大到小枚举减的数，直到无法再减为止。

实验证明，这样做不会变劣。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long fib[101]= {0,1,1},n; //斐波纳契数
int k;//计加的次数
int j;//减到哪一位
int main() {
	cin>>n;
	for(int i=3; i<=100; i++) {
		fib[i]=fib[i-1]+fib[i-2];//递推公式 
		if(fib[i]>=n) {
			j=i;
			break;
		}
	}//生成斐波纳契数列
	while(n>0) {
		while(n-fib[j]>=0)
			n-=fib[j],k++;//贪心，从大到小依次枚举 
		j--;//减小
	}
	cout<<k<<"\n";//AT不换行见祖宗
	return 0; 
}
```


---

## 作者：BotDand (赞：0)

# $\text{Problems}$
求 $n$ 被分为多个斐波那契数相加的最小个数。
# $\text{Answer}$
暴力枚举出斐波那契数列。

因为要求最小个数，可以贪心。

从大的枚举到小的，如果 $n$ 大于当前值，则不断减，小于则找前一个。

因为 $f_{1}=1$，所以枚举到最后 $n$ 一定为 $0$。

此情况一定最优。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int f[102];
int ans;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
signed main()
{
    n=read();
    f[1]=1;f[2]=1;
    for(int i=3;i<=100;++i) f[i]=f[i-1]+f[i-2];
    for(int i=100;i>=1;--i)
    {
        ans+=n/f[i];
        n%=f[i];
        if(!n) break;
    }
    print(ans);
    return 0;
}
```


---

## 作者：lytqwq (赞：0)

只会自己想的~~简单~~方法/kk

先来结论：任何斐波拉契数最多只用1次

~~显然成立~~

当第n个斐波拉契数用两次时，可以转化成用第n+1个斐波拉契数和第n-2个斐波拉契数。

把第n个斐波拉契数表示成 $ F[n] $

根据斐波拉契数的定义 $ F[n] $ $=$ $F[n-1]$ $+$ $ F[n-2] $

所以 $ 2 $ $ * $ $ F[n] $ $ = $ $ F[n] $ $ + $ $ F[n-1] $  $ + $  $ F[n-2] $ 

就等于 $ F[n+1] $ $ + $ $F[n-2]$

所以两个相同的斐波拉契数可以转换的。。。

我们先计算出所有 $ <= N $ 的 斐波拉契数然后从大到小贪心判断就行了。。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100000
long long int n,a[N],p;
int ans;
int main()
{
	scanf("%lld",&n);
	a[1]=1;
	a[2]=1;
	for(int i=3;;i++)
	{
		a[i]=a[i-1]+a[i-2];
		if(a[i]>n)
		{
			p=i-1;
			break;
		}
	}
	for(int i=p;i>=1;i--)
	{
		if(n>=a[i])
		{
			n-=a[i];
			ans++;
		}
	}
	printf("%d\n",ans);
}
```




---

## 作者：cjZYZtcl (赞：0)

## 这题正解为贪心。
由于要斐波那契数最少，所以每次取的数要尽量大，我们可以从大到小枚举斐波那契数。

由于 $n$ 比较小，所以直接枚举斐波那契数并不会超时，而且斐波那契数增长非常快，空间也很省。

我们在贪心之前，需要先枚举出斐波那契数，再贪心。

#### 注意：AT输出换行！！！（本蒟蒻就是这里卡了好久）

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int f[1000005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), m = 2, k = 0;
	f[1] = 1;
	f[2] = 1;
	while(f[m] < n){
		m++;
		f[m] = f[m - 1] + f[m - 2];
	}
	for(int i = m; i >= 1; i--){
		while(n >= f[i]){
			n -= f[i];
			k++;
		}
		if(n == 0) break;
	}
	write(k);
	putchar('\n');
}
```


---

