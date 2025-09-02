# [LnOI2019SP] 快速多项式变换(FPT)

## 题目背景

![avartar](https://cdn.luogu.com.cn/upload/pic/52800.png)

## 题目描述

这是一道构造题。

诗乃在心中想了一个$n+1$项的多项式$f(x)$。第$i$项次数为$i$，系数为$a_i$：

$$f(x)=a_0+a_1x+a_2x^2+a_3x^3+ \cdots +a_nx^n$$

给定$m$以及$f(m)$的值（即当$x=m$时此多项式的值），请构造多项式，满足任意$0 \leq a_i < m$且$a_i$为非负整数。

设你构造的多项式项数为$n$，则必须满足$1 ≤ n ≤ 100$且最高项系数不为零。

## 说明/提示

对于20%的数据， $ 2 ≤ m ≤ 5. $

对于100%的数据，
 $ 2 ≤ m,f(m) ≤ 10^{18}.$

所有数据的时间限制为 $1000ms$，空间限制为 $256MB$，可开启O2优化。

## 样例 #1

### 输入

```
10 10```

### 输出

```
2
0 1```

# 题解

## 作者：诗乃 (赞：50)

对于100%的数据，将m带入此多项式，

$$f(m)=a_0+a_1m+a_2m^2+a_3m^3+ \cdots +a_nm^n$$

不难发现，设$a_na_{n-1}\cdots a_2a_1a_0$是一个$m$进制数，将此数转换为10进制即为$f(m)$的值。因此只需要倒序输出$f(m)$在$m$进制下每一位的值即可。

总复杂度$O(logn)$

当然你也可以模拟过
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long n, m, fm, a[100050];
int main() {
	cin >> m >> fm;
	for(; fm; fm /= m) a[++n] = fm % m;
	printf("%d\n", n);
	for(int i = 1; i < n; ++i) cout << a[i] << " ";
	cout << a[n];
}

```

---

## 作者：yuy_ (赞：12)

看到题面上的多项式

$f(x)=a_0+a_1x+a_2x^2+a_3x^3+ \cdots +a_nx^n$

就能想到这和进制转换有些像,不对啊好像这就是k进制转10进制的式子。

比如说：


二进制数：10100(2)=$0*2^0+0*2^1+1*2^2+0*2^3+1*2^4=20$

就相当于读入的是:

$2$   $20$

那输出就是:

$5$

$0$ $0$ $1$ $0$ $1$

就是求一个10进制数是怎么从m进制计算而来的。

code:
```cpp
#include<cstdio>
#include<cmath>
#define ll long long
using namespace std;
inline ll read() {
    ll ans=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') {f=-1;}ch=getchar();}
    while(ch>='0'&&ch<='9') {ans=ans*10+ch-48;ch=getchar();}
    return ans*f;
}
inline ll ksm(int a,int b){
    ll ans=1,base=a;
    while(b){
        if(b&1){
            ans*=base;
        }
        base*=base;
        b>>=1;
    }
    return ans;
}
ll x,m,y;
ll ans[105],cnt;
ll xx[105];
int main() {
    x=read();
    m=read();
    y=(int)(log(m)/log(x)+0.5);//注意这里的y有可能是比位数要多的，我们只需要在最后处理一下最高位的零把它删除后所得到的长度就是位数了。
    xx[0]=1;
    for (int i=1;i<=y;i++){
        xx[i]=xx[i-1]*x;
    }
    for (int i=y;i>=0;i--){
        ll temp=0;
        temp=m/xx[i];
        m%=xx[i];
        ans[++cnt]=temp;
    }
    ll c=1;
    while(!ans[c]){
    	c++;
	}
	printf("%lld\n",cnt-c+1);//这就是所求的位数
    for (int i=cnt;i>=c;i--){
        printf("%lld ",ans[i]);
    }
    printf("\n");
    return 0;
} 
```



---

## 作者：defense (赞：8)

~~之前讲的不是很清楚，因为自己不是很懂QWQ~~
现在重说一遍。
### 首先看到题目给的这个多项式：
$f(x)=a_0+a_1x+a_2x^2+a_3x^3+...+a_nx^n$

运用小学知识，得到:

$f(x)=a_0+x(a_1+a_2x+a_3x^2+...+a_nx^{n-1})$

发现了什么？对，$a_0$是一个常数项。由于题目说```x=m```,所以

$f(x) \bmod m=a_0$

这是一个很重要的结论。因为再看这个多项式：

$a_1+a_2x+a_3x^2+...+a_nx^{n-1}$

他本质上不就是$a_0+a_1x+a_2x^2+a_3x^3+...+a_nx^n$吗？

于是乎递归求解



------------

```
#include<cstdio>
define LL long long
LL fx,x;
LL temp;
void change(LL f){
	if(f == 0){return;}
	LL f_next = f % x;
	printf("%lld ",f_next);
	change(f / x);
}
int main(){
	scanf("%lld%lld",&x , &fx);
	for(register LL i = 1 ; i <= fx ; i *= x){//求项数
		temp++;
	}
   printf("%lld\n",temp);
	change(fx);
	return 0;
}

```


---

## 作者：ACgod (赞：6)

一道水题。下面讲思路。


------------
第一眼的想法，就是让a[0]=f(m)%s.然后后面不断除$m$取余就好了。

为什么是对的呢？

$f(x)={a_0}+{a_1*x}+{a_2*x^2}+...+{a_n*x^n}$

$\frac{f(x)-a_0}{m}=a_1+a_2*x+a_3*x^3+...+a_n*x^{n-1}$

是不是和原来一样了？

而每次的系数取模，就能保证后来的和能被整除！

# So easy!

~~短小精悍的~~代码

```cpp
#include <iostream>
using namespace std;
long long m,s,n,a[10001],i=0;
int main()
{
    cin>>m>>s;
    a[0]=s%m;
    s-=a[0];
    while(s){
        s/=m;
        i++;
        a[i]=s%m;
        s-=a[i];
    }
    cout<<i+1<<endl;
    for(int j=0;j<=i;j++)cout<<a[j]<<" ";
}
```

比赛想了20分钟结果发现没开long long...

~~十年OI一场空，不开long long见祖宗~~

---

## 作者：Therese (赞：4)

# 这道题目不难，但思路要理一理。
首先，这个多项式有一个很重要的特征，只要发现，题目就迎刃而解了。

在认识这个特征之前，我们需要了解一个很重要的概念：
# 位值原理。

不懂位值的戳[这里](https://wenku.baidu.com/view/d53f367fcc7931b765ce15b1.html)

如果懒得点链接的话，也可以看这个公式：

一个一位数 = 个位数

一个两位数 = 十位数 * 10 + 个位数

一个三位数 = 百位数 * 100 + 十位数 * 10 + 个位数

以此类推。

辣么再看这个多项式，可以发现这个多项式刚好就是位值！

这样这题就好办了。

先处理fm，将它分解成位值的形式：

```
while (fm) { 
	a[temp] = fm % m; //存储fm的最后一位
	fm /= m; //甩掉最后一位
	temp++; //temp一定要记得自增，否则将始终在a[0]这里
}
```
ok，这样a这个数组就将fm的每一位存储下来啦~

最后就简单了，先输出temp，再for循环输出a这个数组的每一位即可~

下面附上完整代码（目测当前最短）：
```
#include <iostream>
using namespace std;
int main() {
	long long fm, m, a[100001], temp = 0;
	cin >> m >> fm;
	while (fm) { a[temp] = fm % m; fm /= m; temp++; }
	cout << temp << endl;
	for (int i = 0; i < temp; i++) cout << a[i] << " ";
	return 0;
}
```
# 这是本人第一篇题解，望过！！！

---

## 作者：Cola (赞：4)

## 本题本人感觉配不上绿题

因为只有$a_0$为常数项，所以$f(x)$%$x$就一定是$a_0$

求出$a_0$后，把它减掉，剩下的都有$x$项，所以就可以愉快的除以一个$x$

那么，现在又只有$a_1$是常数项了，所以$f(x)$%$x$就是一定是$a_1$

求出$a_1$后，把它减掉，剩下的都有$x$项，所以就可以愉快的除以一个$x$（没错，跟第一次一样）

### 所以可以发现，这是一个重复的过程，于是就可以循环解决

循环条件也很简单，只要$f(x)$没变成$0$，那就说明还有数

至于有多少项，因为每遍循环都消掉一项，所以每次循环$+1$即可

代码很简单，只有18行
```
#include<cstdio>
int main()
{
	long long a[101] = {0};//系数
	long long m, fm;//如题
	scanf("%lld%lld",&m,&fm);
	int t = 0;//计数器(有多少项）
	while(fm)
	{
		a[t] = fm % m;//求系数
		fm -= a[t];//减掉
        fm /= m;//除掉
		t++;//加1
	}
	printf("%d\n",t);
	for(int i = 0;i < t;i++) printf("%lld ",a[i]);
	return 0;
}
```

---

## 作者：zi小眼聚光 (赞：4)

~~其实这道题我第一眼看觉得是暴搜的~~

那么仔细看题的话，发现系数是从0次项开始输出的，但一般不是习惯从高次写到低次吗？从高向低就凉了啊！因为你根本不知道最高项是多少啊！

那么考虑一下指数从低到高，题里说了要求ai<m,想到什么？模！

那么模完之后呢？假设这个数是k，k mod m之后得到了当前这一次项的系数，于是发现 k / m就是更高一次项的系数

（m* m^n==m^(n+1)）

于是就得到正解了，从低次项想高次项推，如果当前一项系数大于m，把多出来的加到更高项就行了

AC代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll m,fm,k;
ll c[105],tot,a,b;
int main(){
	scanf("%lld%lld",&m,&fm);
	if(fm<m){
		printf("1\n%lld",fm);
		return 0;
	}
	c[++tot]=fm%m;
	c[++tot]=fm/m;
	while(c[tot]>=m){//这就是递推部分了
		c[tot+1]=c[tot]/m;
		c[tot]%=m;
		tot++;
	}
	printf("%lld\n",tot);
	for(register int i=1;i<=tot;i++){
		printf("%lld ",c[i]);
	}
	return 0;
}
```




---

## 作者：xyj1 (赞：3)

# 这是一道签到题,所以还是满水的.
## 思路
### 1.求出它每一项的大小:
```cpp
 for(i = 1;i <= 2000001;i++)
    {
        f[i] = f[i - 1] * n;
        if(f[i] >= ans)break; 
    }
```
### 2.如果最高项等于f(x)，直接输出
```cpp
if(f[i] == ans)
    {
        printf("%lld\n" , i + 1);
        out[i] = 1;
        for(int j = 0; j <= i;j++)
        printf("%lld ",out[j]);
        return 0;
    }
```
### 3.否则使最高项的系数最大，不断循环，直到和为f(x)。
```cpp
for(int j = i;j >= 0;j--)
    {
        out[j] = ans / f[j];
        ans = ans % f[j];
        if(ans == 0)break;
    }
```


------------


# 完全代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans; 
long long f[2000002];
long long out[2000002];
int main()
{
    scanf("%lld%lld",&n,&ans);
    f[0] = 1;
    int i;
    for(i = 1;i <= 2000001;i++)
    {
        f[i] = f[i - 1] * n;
        if(f[i] >= ans)break; 
    }
    if(f[i] == ans)
    {
        printf("%lld\n" , i + 1);
        out[i] = 1;
        for(int j = 0; j <= i;j++)
        printf("%lld ",out[j]);
        return 0;
    }
    i--;
    for(int j = i;j >= 0;j--)
    {
        out[j] = ans / f[j];
        ans = ans % f[j];
        if(ans == 0)break;
    }
    printf("%lld\n",i + 1);
    for(int j = 0; j <= i;j++)
        printf("%lld ",out[j]);
    return 0;
}
```



---

## 作者：zzy2333 (赞：3)

可以首先预处理出m从1到100的次方，然后看f(m)减去这个值是否大于0，由于系数都是非负的，所以m的n次幂一定不能大于f(m)，否则就要在后面减去一些数。
这样就可以把最高次幂求出来了。
然后就从最高位开始把每一位系数求出来就行。
具体见代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long m,fm;
long long ans[200],power[200];
int n=1;
int main(){
	scanf("%lld%lld",&m,&fm);
	power[0]=1;
	for(int i=1;i<=100;i++){
		power[i]=power[i-1]*m;//预处理每一个次方
	}
	for(int i=0;i<=100;i++){
		if(power[i]>0&&fm-power[i]>=0){//求最高次项，注意判有没有爆，否则。。。
			n=i;
		}
		else break;
	}
	printf("%d\n",n+1);
	for(int i=n;i>=0;i--){
		ans[i]=fm/power[i];//这一项系数显然就是f(m)整除这一次幂，这样可以使后面的系数尽可能小，不然会超过m
		fm=fm%power[i];//把剩下的数继续用更低次幂表示
	}
	for(int i=0;i<=n;i++){
		printf("%lld ",ans[i]);//输出
	}
	return 0;
}
```
这样满足f(m)尽可能用更高次幂表示，在有解的情况下，系数一定是会小于m的

~~然而我太蒟了并不会后三题~~

---

## 作者：Sober_Clever (赞：3)

进制转化（别忘了开long long）
```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
int main()
{
	ll m,n,cnt=0,a[200];
	scanf("%lld%lld",&n,&m);
	while(m)
	{
		a[++cnt]=m%n;
		m/=n;
	}
	printf("%lld\n",cnt);
	for(int i=1;i<cnt;i++)
		printf("%lld ",a[i]);
	printf("%lld\n",a[cnt]);
	return 0;
}
```


---

## 作者：_MRCMRC_ (赞：3)

# 我们发现，对于一个多项式：
## $f(x)=a_0+a_1x+a_2x^2+a_3x^3+\cdots+a_nx^n$
### 它是一个升幂排列的多项式  

### 不难发现，这个多项式的各项其实就是$x$进制的每一位
### 只不过顺序与$x$进制各项顺序相反（$x$进制各项序列是降幂排列的）

### 那么我们依据求$x$进制的算法，将$x$循环求余数，即可得到一个升幂排列的多项式，即每一项的系数：

## 贴上本蒟蒻丑陋的代码：

```cpp
#include<bits/stdc++.h>
#define in inline
#define reg register
#define int long long
using namespace std;
namespace qwq{
    in int read(int &o)
    {
        o=0;
        int w=1;
        char c=getchar();
        while(c<'0'||c>'9')
        {
            if(c=='-')w=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')
        {
            o=(o<<3)+(o<<1)+(c^48);
            c=getchar();
        }
        return o*w;
    }
    in void write(int x)
    {
    	if(x>9)write(x/10);
    	putchar(x%10+48);
    }
    in int max(int x,int y)
    {
        return x>y?x:y;
    }
    in int min(int x,int y)
    {
        return x<y?x:y;
    }
}
using namespace qwq;
int m,fm,t;
int ans[500005];
signed main()
{
    read(m),read(fm);
    while(fm)
    {
        t++;
        ans[t]=fm%m;
        fm/=m;
    }
    write(t);
    putchar('\n');
    for(reg int i=1;i<=t;++i)
    {
        write(ans[i]);
        putchar(' ');
    }
    return 0;
}
```
# 谢谢观看!


---

## 作者：哦，天哪 (赞：2)

这题看到第一眼我是绝望的。。FPT是啥？？？

后来看了看题发现这题不“简单”  qwq

## ~~模拟 就完了~~

预处理出m的i次幂，用 for/while 找出第一个m^i>fm的i 

所以m^(i-1)就是最大的了。。

然后fm/m^(i-1)求出系数 用答案数组存下，最后fm-=m^(i-1) * 系数 

结束一轮循环 直到fm<m时退出 直接让a0=fm就ok了

以下看代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#define int unsigned long long//不要在意这些细节
using namespace std;

int cnt;
int a[310];int powm[310];
int m,fm;

void pre()//预处理 O（n）递推
{
	powm[0]=1;
	powm[1]=m;
	for(int i=2;i<=95;i++)
	{
		powm[i]=powm[i-1]*m;
	}
}

signed main()
{
	ios::sync_with_stdio(0);//懒得scanf
	cin>>m>>fm;
	pre();
	int i;
	while(fm>=m) //一定要大于等于！不然样例都会WA
	{
		for(i=0;;++i)
		{
			if(powm[i]>fm) break;//直到大于时退出
		}
		i--;
		a[i]=(fm/powm[i])?(fm/powm[i]):1;
		fm=fm-(powm[i])*a[i];
	}
	a[0]=fm;
	for(int i=95;i>=0;--i)//找项数
	{
		if(a[i]) 
		{
			cnt=i;
			break;
		}
	}
	cout<<++cnt<<endl;//这里要+1
	for(int i=0;i<=cnt-1;++i)//这里要-1 否则会多输出一个前导0
	{
		cout<<a[i]<<' ';
	}
	return 0;
} 
```


---

## 作者：shuiyuhan (赞：2)

   这题好像没有pascal题解啊，那我来水一发
   
   ~~感觉没看懂出题人的题解啊~~
   
   显然，这题一个明显的想法是暴力算出x,x^2,...,x^n，然后再计算a0,a1...am，

   那就这么做呗，因为f(m)<=10^18，所以不用高精度，直接依次计算即可。

   但如果每次都用ans:=x^(n-1)*n这个算法的话，
   
   显然很可能会出现2^18乘2^18的爆int64的情况，

   所以要特判一下(具体见代码和注释)，最后用f(m) mod a[m]作为ans[m]，
   
   f(m) mod a[m-1]作为ans[m-1]...依次类推即可。
  
显然，当m>f(m)时，答案即为f(m)
   
如果还是没搞懂，那就举个~~栗子~~吧

比如m=12 f(m)=169,

题意即为169=ans[0]+ans[1]*12^1+ans[2]*12^2，求ans[0],ans[1],ans[2];

那么就用a数组储存12的平方次，即a=[0,12,144];

用169先除以144，得ans[3]=169 div(整除) 144=1,相应的要把169-144*1=25；

再用25 div 12=2,即ans[2]=2,25-12*2=1;

最后剩下一个1就是ans[1]了，
```pascal
var
  n,j,k,m,s,t,t1:int64;//f(m),m<=10^18，要开int64/long long
  i:longint;
  a,b:array[0..1000005] of int64;//a数组表示0，x,x^2...x^n得值,b即为上面的ans数组
begin
  readln(n,m);
  t:=n;
  t1:=m;//用t和t1代替n,m去做处理
  s:=1;
  if n>m then//特判一下m>f(m)这种特殊情况
  begin
    writeln(1);
    writeln(m);
    halt;
  end;
  while true do
  begin
    inc(s);
    a[s]:=t;
    if t1 div t<n then break;//防爆int64做的特判
    // t1:=t1-t;
    t:=t*n;//每次*n代表多项式的系数扩大n倍，即题中的x^n
  end;
  if a[s]=0 then dec(s);//0*任何正数=0，故可以省略(这句其实可以不加吧，反正加不加都对)
  writeln(s);
  //for i:=1 to s do write(a[i],' ');
  for i:=s downto 2 do//从最高位除起，防止出现答案>m的情况
  begin
    b[i]:=m div a[i];
    m:=m mod a[i];
  end;
  b[1]:=m;//最后剩下一个常数作为ans[0]
  for i:=1 to s do write(b[i],' ');
end.
```

---

## 作者：xsI666 (赞：2)

这是一道数学题。

在输入完后，我们先预处理处≤f(m)的所有m的次方，然后以次计算a0到an（n为≤f(m)的m的次方的最大指数），注意a0到an都不能≥m,开long long！！！

最后，特判一下m>f(m)的情况就可以AC啦！

附AC代码：
```cpp
#include <bits/stdc++.h>//万能头文件
#define int long long //把int都定义成 long long

using namespace std;//使用标准名字空间

inline int read()//快速读入
{
    int f = 1, x = 0;
    char c = getchar();

    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }

    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }

    return f * x;
}

int n, m, a[105], fm, S = 1, s[105], cnt = -1;

signed main()//注意不能用int main()，因为我们已经在一开始把int都转换成了long long
{
    m = read(), fm = read();//读入m和f(m)

    if (m > fm)//特判m>f(m)的情况
    {
        printf("1\n%lld", fm);//直接输出1和f(m)

        return 0;
    }

    while(true)//预处理处所有≤f(m)的m的次方
    {
        if (S > fm)//如果已经比f(m)大了
        {
            break;//就退出
        }
        else
        {
            s[++cnt] = S;//否则记录下这个数

            S = S * m;//将它*m
        }
    }

    int b = fm;//b为f(m)的复制品

    a[++n] = fm % m;//预处理处a0(常数项)

    b = b - fm % m;//减去常数项

    for (register int i = 1; i <= cnt; i++)
    {
        a[++n] = (b / s[i]) % m;//依次计算每一位
    }

    printf("%lld\n", n);//输出n

    for (register int i = 1; i <= n; i++)
    {
        printf("%lld ", a[i]);//输出a[i]
    }

    return 0;//结束
}
```

---

## 作者：Charles_2016 (赞：2)

这道题看上去没地方入手，但我们仔细想想，多项式函数在计算时我们希望用到快速幂的算法，那我们为什么不用相同的思想来凑这个系数呢？  
我们求以m为底，f（m）的对数，可以得到n的最大值，因为如果存在更大的n，就会使得这个对数的整数部分+1，从而使我们的多项式函数最高次项增加，并且在我们这种做法下，系数a永远不会大于等于m，因为如果最高次项的系数a大于等于m了，那么我们就可以使最高次项的次数上升而使其系数下降到(0,m)∩N范围之内。  
这应是不难想的，接下来是常数项的问题，我们把小于m的部分全部变成常数项即可。  
我在考场上被c++ log的精度问题搞崩了（log2（2^50-1）竟然等于50）
下面上代码。  
```cpp
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
const int MAXN = 88;

long long m,f;
int n;
long long a[MAXN];

int SlowLog(long long x,long long y){
	int a = 0;
	long long lent = 1;
	while (lent <= x){
		a++;
		lent *= y;
	}
	return a;
}

long long QuickPow(long long b,int p){
	long long result = 1;
	long long base = b;
	while(p > 0){
		if (p & 1){
			result *= base;
		}
		base *= base;
		p >>= 1;
	}
	return result;
}

long long ans;
int main(){
	cin >> m >> f;
	if (f == 0){
		cout << 1 << endl;
		cout << 0;
		return 0;
	}
	int k = SlowLog(f,m);//运行结果好像也是一样的有bug
	
	for (int i = k ; i >= 0 ; i--){
		if (QuickPow(m,i) <= f){
			a[i] = f / QuickPow(m,i);
			f %= QuickPow(m,i);
		}
		else {
			a[i] = 0;
		}
	}
	while (a[k] == 0){
		k--;
	}//我们可以这样防止被bug卡到（k卡bug只大不小）
	cout << k + 1 << endl;
	for (int i = 0 ; i <= k ; i++){
		cout << a[i] << " ";
	}
	return 0;
}
```
就是这样了 如果有大佬知道怎么解决log2（2^50-1）=50的问题可以私信我

---

## 作者：hanzhongtlx (赞：1)

蒟蒻的第一篇题解——————————————大佬勿喷：  
~~否则会自闭~~  
好不容易有道水题  
题目链接：[P5248 [LnOI2019SP]快速多项式变换(FPT) ]   (https://www.luogu.org/problem/P5248)    
这题难在思路，我们观察样例发现正是逆序输出10的十进制的每一位！  
再回想一下，我们是怎么学习进制转换的：   
举个栗子：将二进制的10110转换成十进制，不就是将倒数第n 位的数乘上2^（n-1）吗？即为1* 16+0* 8+1* 4+1* 2+0* 0=22   
这道题中中的公式好眼熟，so……   
此题不正是上述算法的逆运算吗？   
提一句可转化为将十进制下的f(m)转化为m进制吗？  
还有一些细节，那就代码见吧：    
```
#include<bits/stdc++.h>//万能头文件 
using namespace std;
typedef long long ll;//自定义一个数据类型，只因long long太难写，大题中有大用 
int main()
{
	ll m,fm;
	ll sum=1;//位数 
	ll a[105];//每位的数字 
	cin>>m>>fm;//输入 
	while(fm!=0)
	{
		a[sum]=fm%m;//存入余数 
		fm/=m;
		sum++;//每次将总数加一 
	}
	sum--;//最后一次循环之后没有数了，但最后多了一个，要减去！！！！ 
	cout<<sum<<"\n"; 
	for(int i=1;i<=sum;i++)
	{
		cout<<a[i]<<" ";
	}//输出记得格式要符合题意 
	return 0;//这是个好习惯 
}
```
好了，妥妥普及-的难度，祝大家AC渡劫成功！！！  
欢迎私聊我呦(｀・ω・´)   
→[my blog(欢迎光临寒舍）](https://www.luogu.org/blog/hanzhongtlx-juruo/)

---

## 作者：杨铠远 (赞：1)

# 比赛的时候交了十几遍 debug真爽
```
#pragma GCC optimize("Ofast","inline","-ffast-math")

#pragma GCC target("avx,sse2,sse3,sse4,mmx")//ofast了解一下 
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;
long long x,fx,flag;
long long a[101],b[101];
inline void w(long long x)//快输 
{
	if(x==0)return;
	w(x/10);
	putchar(x%10+'0');
}
signed main()
{
	cin>>x>>fx;
	a[1]=x;
	for(long long i=2;i<=100;i++)//预处理出x的每个次方 
	{
		a[i]=a[i-1]*x;
		if(a[i]>fx){//已经不需要再处理了，已经不可能选上了 
			flag=i-1;//记录最高次项 
			break;
		}
	}
	long long now=0;
	for(long long i=flag;i>0;i--)
	{
		if(now+a[i]>fx)//不能选 
		{
			b[i]=0;
		}
		else{
			long long j=1;
			while(now+a[i]*j<=fx)b[i]=j,j++;//能塞几个塞几个 
			//b[i]=j;
			now+=a[i]*b[i];
		}
	}
	b[0]=fx-now;
	flag++;
	w(flag);
	putchar('\n');
	for(long long i=0;i<flag;i++)
	{
		if(b[i]>0)w(b[i]);//本快输的弱点 不能输出0 
		else printf("0");
		putchar(' ');
	}
	return 0;
}//赢了！ 
```
有点慌 成绿题了

---

## 作者：DQYdqy (赞：1)

题目名字给人一种不可写的感觉...

不过其实很好写...

因为$a_i<m$，所以$f(x)/m$的值会舍去当前第一个$a$的值

那么再用$f(x)$减去当前的值乘$m$即可得到第一个$a$

依次推下去就行了

## **Code**:
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m,f,t,ans[101];
int main(){
    scanf("%lld%lld",&m,&f);
    while(f){
        ll tmp=f;tmp/=m;
        ans[++t]=f-tmp*m;
        f/=m;
    }if(!ans[t]) --t;
    printf("%lld\n",t);
    for(int i=1;i<=t;i++) printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：万万没想到 (赞：1)

~~比赛开始前还真以为难度是PJT1，看来是想多了~~  
~~实际难度真是PJT1~~  

话不多说，开始说我这个蒟蒻的思路：  
比赛的时候，并没有注意到这个式子是个m进制的式子...  
随后，我用了一种非常奇怪的方式来求这个m进制。  
从小到大枚举n也就是这个ai序列的长度，再倒序从高位到低位枚举数字能在高位便在高位，最后判断第一位是<m。可行再输出。
代码如下：
  
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
long long m,n,a[201],ans;
long long mm(long long a,long long b){
    long long r=1,base=a;
    while(b) {
        if(b&1) r*=base;
        base*=base;
        b>>=1;
    }
    return r;
}
int main() {
    cin>>m>>n;
    for(register long long i=1;i<=100;++i){
        memset(a,0,sizeof(a));
        ans=n;
        for(register long long j=i-1;j>0;--j){
            long long p=1;
            while(p<m&&mm(m,j)*p<=ans){
                ++p;
            }
            --p;
            a[j]=p;
            ans=ans-(mm(m,j)*a[j]);
        }
        if(ans<m)a[0]=ans,ans=0;
        if(ans==0){
            cout<<i<<endl;
            for(register long long j=0;j<i;++j)cout<<a[j]<<" ";
            cout<<endl;
            return 0;
        }
    }
    return 0;
}
```

然鹅，在赛后才想到这个多项式实际上就是m进制的一个式子，将其转换十进制输出即可，代码如下：
  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,ans,a[101];
int main() {
    scanf("%lld%lld",&n,&m);
    while(m!=0){
    	a[++ans]=m%n;
    	m/=n;
	}
	printf("%lld\n",ans);
	for(register int i=1;i<=ans;++i)printf("%lld ",a[i]);
    return 0;
}
```
谢谢观看

---

## 作者：LevenKoko (赞：1)

[更好的阅读体验~~（推销博客）~~](https://www.cnblogs.com/zhenglw/p/10505881.html)

## 本片题解设计两种解法

~~果然是签到题...~~

因为返回值问题T了好久...

## 第一眼：搜索大水题？

~~ 然后...竟然A了~~

```
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
inline int read(){
    int ans=0,f=1;char chr=getchar();
    while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
    while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
    return ans*f;
}int fm,m,tot,a[105],x,ff,p[105],q[105];
void dfs(int x,int now){
    if(ff) return;
    if(x==0&&now>=m) return;
    if(now<m){
        ff=1;
        int t=100;
        while(p[t]==0) t--;
        cout<<t+1<<endl<<now<<" ";
        for(int i=1;i<=t;i++) cout<<p[i]<<" ";
        return;
    }
    int t=now/a[x];
    for(int i=t;i>=0;i--)    p[x]=i,dfs(x-1,now-a[x]*i);
}
signed main(){
    m=read(),fm=read();
    x=1;a[0]=1;
    while(x<fm&&tot<=101){a[++tot]=x*m;x=x*m;}
    dfs(tot,fm);
    return 0;
}
```
 但其实只要分析一下，就发现式子跟进制转换有很大关系啊，我们只要把fm当做m进制数来处理即可
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib> 
#include<ctime>
#define int long long
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
	while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}void write(long long x){
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}int n,m,a[505],tot;
signed main(){
    m=read(),n=read();
    while(n){a[++tot]=n%m;n/=m;}
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++)write(a[i]),putchar(' ');
    return 0;
}
 ```

---

## 作者：ricky0916 (赞：0)

这道题为什么要SPJ啊，~~多项式显然唯一啊~~ （雾）

如果不显然，那我就来证明一下

假设$ f(m)=\sum_{i=0}^n a_im^i $

若$ f(m) $同时等于$ \sum_{i=0}^{n'} a'_im^i $

则由于$ m^i=m\times m^{i-1} $，又$ 0\leqslant a_i<m $

所以$ a_im^i>m^i=(m-1)\sum_{j=0}^{i-1}m^j $

然后就容易得到$ n=n' $

考虑将两式相减，$ \sum_{i=0}^n (a_i-a'_i)m^i=0 $

其中$ -(m-1)\leqslant a_i-a_i'\leqslant m-1 $

那么如果$ a_i-a_i'\ne0 $,不妨设$ a_i-a_i'\geqslant1 $（小于0同理），则有$ \sum_{i=0}^n(a_i-a_i')m^i\geqslant m^n-(m-1)\sum_{i=0}m^{n-1}=1 $，矛盾

所以$ a_n=a'_n $

类似的$ a_i=a'_i(0\leqslant i\leqslant n) $

所以这个多项式唯一。

~~构造方式就不多说了~~ 就是10进制转m进制的板子

---

## 作者：咯咯咯 (赞：0)

数位DP

从高位到低位二分确定每一位的值
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Ford(i,a,b) for(int i=a;i>=b;i--)
#define LL long long
LL m,fm,M[1000],a[1000];
int max,n;
int main()
{
	scanf("%lld%lld",&m,&fm);
	M[0]=1;max=0;
	For(i,1,100)
	{
		if (log10(M[i-1])+log10(m)<=log10(1LL<<62)) M[i]=M[i-1]*m,max=i;
		else break;
	}
	LL now=0;
	Ford(i,max,0)
	{
		LL l=0,r=m;
		while (l<r)
		{
			LL mid=(l+r)>>1;
			if (now+mid*M[i]<=fm&&(mid==0||log10(mid)+log10(M[i])<=log10(1LL<<62))) l=mid+1;
			else r=mid;
		}l--;
		a[i]=l;now+=l*M[i];
	}
	int n=0;For(i,0,max) if (a[i]) n=i;
	printf("%d\n",n+1);
	For(i,0,n) printf("%lld ",a[i]);putchar('\n');
}
```


---

## 作者：_虹_ (赞：0)

可以转换一下题目，发现题目相当于给定n-1（n<=100）种物品,放入一个背包内，使剩余空间最小。

贪心从大向小放就行了。

口胡一下为啥是对的。

首先f(m)=a0+k*m肯定是没毛病的。

由于“0<=ai<m"，所以我们可以把k*m换成(k%m)*m +( k/m * m^2).若k/m>m，则继续刚才的步骤。

这样我们虽然对数论和进制完全不开窍，也可以通过了。

~~差点没做出来签到题啊。~~


```cpp
#include <iostream>
using namespace std;
#define reg register
const int kmaxn=100+5;
unsigned long long ans[kmaxn];
unsigned long long data[kmaxn];
long long m,f,cnt;
unsigned long long temp;
int main()
{
	ios::sync_with_stdio(false);
	cin>>m>>f;
	temp=1;
	data[0]=1;
	for(reg int i=1;i<100;++i,++cnt)
	{
		if(temp>f/m+1)
			break;
		temp*=m;
		data[i]=temp;
	}
	for(reg int i=cnt;i>=0;--i)
	{
		ans[i]=f/data[i];
		f-=ans[i]*data[i];
	}
	cout<<cnt+1<<endl;
	for(reg int i=0;i<=cnt;++i)
	{
		cout<<ans[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```

~~不过也只做出来了签到题就是了QAQ~~


---

## 作者：partychicken (赞：0)

发现题目让做的事情就是输出 $f(m)$ $m$ 进制下的每一位

- Q: 怎么发现的？ 

- A: 不是很显然吗？

~~为了保证题解过审，开始瞎JB分析~~

首先一个很明显的提示就是要求每一个 $a_i$ 都必须 $< m$，很容易联想到进制

然后，手玩几组也能发现做法。

或者考虑从高位向低位贪心这个显然的做法（~~这个做法是我硬编的~~不知道有没有人真的这么想，貌似也能过吧。。。）。然后通过这个算法也可以想出正解

吐槽：为啥不开大数据范围上高精啊？出题人也太善良了。~~莫非，出题人不会py？？？~~

```
#include<bits/stdc++.h>

using namespace std;

long long ans[100010],cnt;

int main()
{
    long long a,b;
    cin>>a>>b;
    while(b)
    {
        ans[++cnt]=b%a;
        b/=a;
    }
    cout<<cnt<<'\n';
    for(int i=1;i<=cnt;i++)
    {
        cout<<ans[i]<<' ';
    }
}
```

---

## 作者：wlzhouzhuan (赞：0)

我们先考虑计算出 $p$ 满足$m^p<=f(m)<m^{p+1}$，

```cpp
int calc(ll c) {
	int cnt = 0;
	while (c >= m) cnt++, c /= m;
	return cnt;
}
```

然后处理出$m^1,m^2,...,m^p$

```cpp
int p = calc(fm);
while (p--)
    len++, bas[len] = bas[len - 1] * m;
	
```

最后从$m^p$开始倒序求，每次取能取到的最大值，

```cpp
for (int i = len; i >= 0; i--) {
	ans[i] = fm / bas[i];
	fm -= ans[i] * bas[i];
}
```

最后就可以愉快地输出答案啦。


$Code$:

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll m, fm, tql = 1;
ll bas[1005]; int len;
ll ans[1005];

int calc(ll c) {
	int cnt = 0;
	while (c >= m) cnt++, c /= m;
	return cnt;
}

int main() {
	scanf("%lld%lld", &m, &fm);
	bas[0] = 1ll;
	int p = calc(fm);
	while (p--) len++, bas[len] = bas[len - 1] * m;
	
	for (int i = len; i >= 0; i--) {
		ans[i] = fm / bas[i];
		fm -= ans[i] * bas[i];
	}
	
	while (ans[len] == 0 && len > 0) len--;
	printf("%d\n", len + 1);
	for (int i = 0; i <= len; i++)
		printf("%lld ", ans[i]);
	putchar('\n');
	return 0;
}
```

---

## 作者：ChengZe (赞：0)

```cpp
首先我们注意到0≤ai<m,故a[i]*m^i必定小于m^(i+1)
所以我们只要一直把f(m)/=m之后f(m)%m之后的余数就是从a[0]一直到a[n]
举个例子
f=31 m=5
31%5=1;f/=5;
f=6 m=5
6%5=1;f/=5;
f=1 m=5;
1%5=1;f/=5;
f=0,跳出，所以答案就是
3
1 1 1
```

代码其实码起来很容易


```cpp
#include <bits/stdc++.h>
using namespace std;

long long read(){
    long long res=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res;
}

int main()
{
    long long m=read(),f=read();
    long long ans=0,cnt=0;//ans和cnt一个东西，比赛时莫名其妙开了两个
    long long a[101];
    while(f){
        ++ans;
        a[++cnt]=f%m;
        f/=m;
    }
    printf("%lld\n",ans);
    for(int i=1;i<=cnt;i++)printf("%lld ",a[i]);
    return 0; 
}
```


---

## 作者：lxy__ (赞：0)

这道题全场AC？

不是很懂大佬的进制转换（~~我还是太弱了qwq~~

说一说我的做法

把$m^i$存到$w[i]$中，超过$f(m)$就不用存了（防止爆$longlong$）

然后倒着循环，能放几个$w[i]$就放几个，把每次放的个数存在$ans[i]$里面

最后输出

简单的证明：对于任何$i$，$ans[i]$都小于$m$，因为如果$>=m$，早就放了一个$w[i+1]$了。

蒟蒻的代码

```c
#include<iostream>
#include<cstdio>
using namespace std;
long long tot=0,m,f,w[105],ans[105];
int main()
{
    scanf("%lld%lld",&m,&f);
    w[0]=1;
    for(int i=1;i<=100;i++)
    {
        if(w[i-1]*m>f) break;
        w[i]=w[i-1]*m;
        tot++;//项数++
    }
    for(int i=tot;i>=0;i--)
    {
        if(!f) break;
        if(f>=w[i]) 
        {
            ans[i]=f/w[i];
            f-=ans[i]*w[i];
        }
    }
    printf("%lld\n",tot+1);
    for(int i=0;i<=tot;i++) printf("%lld ",ans[i]);
    return 0;
}
```


---

