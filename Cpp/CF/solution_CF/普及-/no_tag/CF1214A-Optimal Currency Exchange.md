# Optimal Currency Exchange

## 题目描述

Andrew参加了Olympiad of Metropolises，现准备回国，需要兑换货币。

现有如下面额的美元纸币：$1 , 2 , 5 , 10 , 20 , 50 , 100$，以及以下面额的欧元纸币：$5 , 10 , 20 , 50 , 100 , 200$（注意，不考虑$500$欧元纸币，因为在货币兑换窗口很难找到这种）。已知兑换$1$美元需要$d$卢布，$1$欧元需要$e$卢布，而Andrew有$n$卢布。

他可以兑换任意数量的美元和欧元（一种纸币可以兑换多次，可以美元和欧元混合），并且，他希望使兑换后手里剩余的卢布数尽可能少。请你写一个程序帮他解决问题（只需求出最小的剩余卢布数）。

## 说明/提示

$1 \leq n \leq 10^8$

$30 \leq d,e \leq 100$

## 样例 #1

### 输入

```
100
60
70
```

### 输出

```
40
```

## 样例 #2

### 输入

```
410
55
70
```

### 输出

```
5
```

## 样例 #3

### 输入

```
600
60
70
```

### 输出

```
0
```

# 题解

## 作者：andyli (赞：4)

答案需要我们计算最小的卢布数，换句话说，我们需要最大化美元和欧元的总金额，而在如果已知其中任意一种的相应货币钱数，即可算出在总答案最大的情况下另外一种货币的钱数。所以我们可以枚举美元换取的钱数，同时算出相应的欧元钱数，选取总金额最大的方案即为答案。注意只能换取$5$的倍数的欧元，所以**实际能换取的欧元钱数**为剩余可换取欧元的钱数与它之差绝对值最小且不大于它的数。
主程序代码如下：  
```cpp
int main()
{
    int n, d, e;
    read(n, d, e); // 输入数据
    int x = n / d, ans = 0; // x为最大能换取的美元数量
    for (int i = 0; i <= x; i++) // 换取i美元
        ans = max(ans, i * d + (n - i * d) / e / 5 * 5 * e); // (n - i * d) / e 为剩余可换取欧元的钱数, /5*5的操作是为了计算实际能换取的欧元钱数
    writeln(n - ans); // 输出答案
    return 0;
}
```

---

## 作者：big_news (赞：1)

emm，这题我的解法题解里居然没有，可能是我做复杂了......

实际上首先想到的是背包，这个大概都能想出来就不多讲，写起来长这样：
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=7;j++)
        if(i-D[j] >= 0) f[i] = max(f[i], f[i-D[j]]+D[j]);
    for(int j=1;j<=5;j++)
        if(i-E[j] >= 0) f[i] = max(f[i], f[i-E[j]]+E[j]);
}  
```
然后10e8的数据范围妥妥的RE了。

### 回到正题

首先观察到一个结论：对于美元来讲，所有的面值都是一美元面值的倍数啊...也就是说换美元的话，不管你换到多少张不同面值的钞票，实际上都可以看成换了一堆面值为一美元的钞票。对于欧元也同理。
那么也就是说，我们只需要考虑换成一美元和五欧元两种面值就好了。

于是把这两种钞票分别所需要的卢布的数量表示出来，不妨设$x=d,y=5e$。设美元换了$a$张，欧元换了$b$张，那么剩下的钱数就是$n-(ax+by)$。设$c=n-(ax+by)$，实际上就是要最小化$c$。

然后$c=n-(ax+by)$不觉得很眼熟么...移项后就是$ax+by=n-c$，其中$x,y,n$已知，可以看作关于$a,b$的不定方程。**但是$c$呢？**$c$可能有很多取值，但是不难发现，某一$c$值可行的条件是$ax+by=n-c$这个关于$a,b$的不定方程有$a,b$同为非负整数的解。

### 怎么判定？

由裴蜀定理的推广我们知道不定方程有整解的条件是$(a,b)|c$，但是非负这个条件怎么保证呢？

不定方程的整数通解是：针对于某一特解$(x0,y0)$，$( x0+i(b/(a,b)), y0-i(a/(a,b)) )$是方程的通解（注意：其中$i∈Z$，除号后面的$(a,b)$实际表示$gcd(a,b)$）。

那么显然，若$x0,y0$同时$⩾0$，则一定有非负整数解；若$x0,y0$同时$<0$，则一定没有非负整数解，因为即使让$x0,y0$中的一者变得$⩾$0，另一者也只会越来越小。那么对于$x0,y0$中有一者$<0$，另一者$⩾$0的情况呢？

不妨假定$x0⩾0$而$y0<0$。我们希望让$y0⩾0$，于是不妨设$y0+i(a/(a,b))⩾0$。那么对于整数$i$，如果$i$最小时，也有$x0-i(b/(a,b))<0$的话，那么我们就肯定不能通过调整特解来使得解均为非负数，反之则一定可以。$x0<0$而$y0⩾0$的情况也同理。

那么实际上就是几个判断的事：
```cpp
bool check(){
    ...
    int k = c/g,kx = b/g,ky = a/g;
    x = x0*k,y = y0*k;
    if(x>=0 && y>=0) return true;
    if(x<0 && y<0) return false;
    int i = 0;
    if(x < 0){
        while(x < 0) x += kx,i++; //调整特解使得x非负
        if(y-i*ky < 0) return false; //此时另一解为负，则一定无非负整数解
        return true;
    }
    while(y < 0) y += ky,i++; //反之同理
    if(x-i*kx < 0) return false;
    return true;
}
```

然后就好了，我们知道了如何判断一个$c$可行与否。不难发现有$ c \leqslant \text{min} (n\text{ mod } a, n \text{ mod } b ) $，后面那个东西不会大于100，于是枚举$c$就好了啊。

上面的内容用到了一点解不定方程的知识，顺手推推博：[1](https://big-news.cn/2019/07/22/%E6%A8%A1%E7%BA%BF%E6%80%A7%E6%96%B9%E7%A8%8B%E7%BB%84%E4%B8%8E%E4%B8%AD%E5%9B%BD%E5%89%A9%E4%BD%99%E5%AE%9A%E7%90%86/),[2](https://big-news.cn/2019/05/19/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E4%B8%8E%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E5%AE%9A%E7%90%86/)。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
 
int n,a,b,r = 0;

int gcd(int a,int b) {return b?gcd(b,a%b):a;}
void exgcd(int a,int &x,int b,int &y){ //exgcd递归
    if(!b){x = 1; y = 0; return;}
    exgcd(b,x,a%b,y);
    int t = x; x = y; y = t-(a/b)*y;
}
bool ExGcd(int a,int &x,int b,int &y, int c){ //解不定方程并判断有无非负整数解
    int g = gcd(a,b);
    if(c % g) return false; //无整数解
    int x0,y0; exgcd(a,x0,b,y0); //转化为求解ax+by=gcd(a,b)
    int k = c/g,kx = b/g,ky = a/g;
    x = x0*k,y = y0*k; //得到ax+by=c的特解(x,y)
 
    //判定部分
    if(x>=0 && y>=0) return true;
    if(x<0 && y<0) return false;
    
    int i = 0;
    if(x < 0){
        while(x < 0) x += kx,i++; //调整特解使得x非负
        if(y-i*ky < 0) return false; //此时另一解为负，则一定无非负整数解
        return true;
    }
    while(y < 0) y += ky,i++; //同理
    if(x-i*kx < 0) return false;
    return true;
}
 
int main()
{
    scanf("%d%d%d",&n,&a,&b);
    b *= 5; //乘上面值
 
    int x,y;
    while(!ExGcd(a,x,b,y,n-r)) r++; //找到最小的r
 
    printf("%d",r);
 
    return 0;
}
```

---

## 作者：Meatherm (赞：1)

很明显买 $>1$ 的美元和 $>5$ 的欧元不会更优。

容易发现，$>1$ 的美元都可以用若干个 $1$ 美元拼起来得到；$>5$ 的欧元都可以用若干个 $5$ 欧元拼起来得到。

于是暴力枚举买 $x(0\leq x\leq \left\lfloor \frac nd\right \rfloor)$ 个 $1$ 美元，剩下的全部买 $5$ 欧元剩下的卢布数量。

时间复杂度：$O(\frac n{30})$。很明显可以通过这道题。

```cpp
# include <bits/stdc++.h>
# define rr register
int n,a,b;
int minx;
int main(void){
	scanf("%d%d%d",&n,&a,&b);
	minx=1e9;
	for(rr int i=0;i<=(n/a);++i){
		minx=std::min(minx,(n-(i*a))%(b*5));
	}
	printf("%d",minx);
	return 0;
}
```

---

## 作者：B_Qu1e7 (赞：1)

思路：从$0$开始枚举可以换多少美元，再对"$5$欧元"取模即可。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int N,D,E,ans;
int main()
{
	scanf("%d%d%d",&N,&D,&E);
	ans=N;
	//最坏的情况就是什么都换不了，所以ans初值为n
	for(int i=0;i<=N/D;i++)
	{
		ans=min(ans,(N-D*i)%(5*E));
		//枚举换0,1,...美元，剩下全换欧元，取最小值
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：___cjy__ (赞：0)

# CF1214A Optimal Currency Exchange 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1214A)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/cf1214a)

### 题目大意：

有如下面额的美元纸币：$1$ , $2$ , $5$ , $10$ , $20$ , $50$ , $100$ 以及如下面额的欧元纸币：$5$ , $10$ , $20$ , $50$ , $100$ , $200$。已知兑换 $1$ 美元要 $d$ 卢布，$1$ 欧元要 $e$ 卢布。需要将 $n$ 卢布兑换成美元和欧元，求最少可以剩下多少卢布。

### 正文：

明显可以发现，兑换 $1$ 美元或 $5$ 美元面额的钱比其余的兑换其余的面额的钱更划算。因为其余所有美元的面额都是 $1$ 美元的倍数，所有欧元的面额都是 $5$ 欧元的倍数。所以我们可以分别求出 $1$ 美元和 $5$ 欧元的价格，枚举其中之一的个数并用剩余的钱去模另一个价格，找到最小的余数。另外，因为欧元最小面额为 $5$，所以在任何情况下 $5$ 欧元的价格总是比 $1$ 美元的价格高的。这样我们就可以枚举 $5$ 欧元的数量，使得枚举的次数尽可能少。

### 总结：

枚举 $5$ 欧元的数量，用剩下的数模 $1$ 美元的价格，找到最少的余数。

### AC Code：


```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
#define int long long
#define N 114514
#define INF 0xffffffff
#define bug printf("..........bug!..........\n");
using namespace std;
int n,d,e,Min=INF; 
signed main(){
	cin>>n>>d>>e;
	e*=5;//现在的 e 表示 5 欧元的价格。 
	for(int i=0;i<=n;i+=e)//枚举 e 的个数。 
		Min=min((n-i)%d,Min);//找最小值。 
	cout<<Min;
	return 0;
}
```


---

## 作者：Jerrlee✅ (赞：0)

## 题意
有翻译了，不写了。
## 思路
如果我们购买了价值两美元或更多美元的美元钞票，我们可以将其换成一美元的钞票。欧元也是一样，我们可以用几个欧元纸币代替所有的 $5$ 欧元纸币。

现在我们可以简单地尝试购买一些五欧元的钞票，然后用一美元的钞票购买所有剩余的钞票。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
    int n,d,e; //这题不是 t 组数据，注意不要多打
    cin>>n>>d>>e;
    int ans=n;
    for(int i=0;i*5*e<=n;i++){
        ans=min(ans,(n-i*5*e)%d);
    }
    cout<<ans;
}
```
复杂度是 $O(n)$。

[AC记录（洛谷）](https://www.luogu.com.cn/record/59401094)

[AC记录（CF）](https://codeforces.com/contest/1214/submission/131049971)

---

## 作者：X2H_tato (赞：0)

这个A题稍微有点思维难度。

贪心的思路是，我们换面值越小的货币越优。如有$1,2,5,10,20,50$，那么我们尽量用面值为$1$的。如果我们把原始货币换成面值为$x$的货币，设汇率为$d$,那么需要的原始货币为$dx$的倍数。显然$dx$越小，剩下的钱，即$n$取模$dx$会尽量小。

然后就可以枚举换某一种货币的数量，时间复杂度$O(n/d)$

代码：
```
#include<iostream>
#include<cstdio>
#define INF 0x3f3f3f3f
using namespace std;
int n,d,e;
int main(){
	scanf("%d %d %d",&n,&d,&e);
	e*=5;
	int ans=INF;
	for(int i=0;i*d<=n;i++){
		ans=min(ans,n-i*d-(n-i*d)/e*e);
	}
	printf("%d\n",ans);
}

```


---

## 作者：叶ID (赞：0)

题目链接：[此处](https://www.luogu.org/problem/CF1214A)

---

题意翻译：

### 题目描述

Andrew参加了Olympiad of Metropolises，现准备回国，需要兑换货币。

现有如下面额的美元纸币：$1 , 2 , 5 , 10 , 20 , 50 , 100$，以及以下面额的欧元纸币：$5 , 10 , 20 , 50 , 100 , 200$（注意，不考虑$500$欧元纸币，因为在货币兑换窗口很难找到这种）。已知兑换$1$美元需要$d$卢布，$1$欧元需要$e$卢布，而Andrew有$n$卢布。

他可以兑换任意数量的美元和欧元（一种纸币可以兑换多次，可以美元和欧元混合），并且，他希望使兑换后手里剩余的卢布数尽可能少。请你写一个程序帮他解决问题（只需求出最小的剩余卢布数）。

### 输入格式

3行，3个正整数$n,d,e$。

### 输出格式

1行，1个非负整数表示最小剩余量。

### 数据范围

$1 \leq n \leq 10^8$

$30 \leq d,e \leq 100$

---

这题看似一个背包做的“最小剩余”问题，但是$n$太大，其实背包做不了。

我们注意到每种纸币可以兑换无限的数量。我们假设只兑换美元，那么美元数肯定是1的倍数；如果只兑换欧元，欧元数一定是5的倍数。

因此，我们暴力枚举，将$x$卢布用于兑换美元，那么这$x$卢布的剩余量是，$x\ mod\ (d \times 1)$。同理，$n-x$卢布会用于兑换欧元，剩余量是$(n-x)\ mod\ (e \times 5)$。

枚举的同时，我们维护$ans=INF$，并且枚举$x$是，更新$ans$为$min(ans,x\ mod\ (d \times 1)+(n-x)\ mod\ (e \times 5))$，最后输出ans，即可解决这个问题。容易发现，最多只要枚举$10^8$次，完全可以通过。

---

```cpp
// status: [Accepted]
// oj:     [Codeforces]
#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
    #define cerr if(0)cerr
#endif
// #ifndef OFFLINE_JUDGE
//     #define freopen if(0)freopen
// #endif
typedef long long ll;
typedef unsigned long long ull;
#define lll __int128_t
#define int ll
// #define int lll
#define For(i,ak,ioi) for(i=(ak);(((ak)<(ioi)) ? i<=(ioi) : i>=(ioi));i+=(((ak)<(ioi)) ? 1 : -1))
#define Rep(i,ak,ioi) for(int i=(ak);(((ak)<(ioi)) ? i<=(ioi) : i>=(ioi));i+=(((ak)<(ioi)) ? 1 : -1))
#define Range(i,ak,ioi,again) for(i=(ak);(((again)>0) ? i<=(ioi) : i>=(ioi));i+=(again))
#define Rap(i,ak,ioi,again) for(int i=(ak);(((again)>0) ? i<=(ioi) : i>=(ioi));i+=(again))
#define Memset(xt,ak) memset(xt,ak,sizeof(xt))
#define Reset(xt,ak,ioi,again) \
    for(int __reset_idx=ak;__reset_idx<=ioi;__reset_idx++) \
        xt[__reset_idx] = again
#define iter iterator
#define memgua memset
template<class _Tp>
inline _Tp readInteger() {
    _Tp ret=0,f=1;char c=getchar();
    while(c<'0' || c>'9') {if(c=='-') f*=-1; c=getchar();}
    while(c>='0' && c<='9') {ret=ret*10+f*(c-'0'); c=getchar();}
    return ret;
}
template<class _Tp>
void read(_Tp &x)  {x=readInteger<_Tp>();}
char readChar() { char c=getchar();while(isspace(c)) c=getchar();return c; }
void writeStr(char *s,int len,char _end='\0')
{for(int i=0;i<len;i++) putchar(s[i]);if(_end) putchar(_end);}
void writeStr(string s,char _end='\0') 
{for(unsigned i=0;i<s.length();i++) putchar(s[i]);if(_end) putchar(_end);}
template<class _Tp>
void writePositiveInteger(_Tp val)
{if(val==0)return;writePositiveInteger(val/10);putchar('0'+val%10);}
template<class _Tp>
void write(_Tp val,char _end='\0') {
    if(val==0) putchar('0');
    else if(val<0) {putchar('-');writePositiveInteger(-val);}
    else writePositiveInteger(val);
    if(_end) putchar(_end);
}

const int INF=7e14;
int v;
int c1;
int c2;
int arr[13] = {1,2,5,10,20,50,100,5,10,20,50,100,200};

signed main() {
    read(v);read(c1);read(c2);
    // for(int i=0;i<7;i++) arr[i]*=c1;
    // for(int i=7;i<13;i++) arr[i]*=c2;

    int ans=INF;
    for(int l=0;l<=v;l++) {
        int r=v-l;
        ans=min(ans,l%c1+r%(5*c2));
    }

    write(ans,'\n');
}
```


---

## 作者：Victory_Defeat (赞：0)

本题还是比较水的

题目大意：

给定$n$元钱，要换成另两种货币，汇率分别为$d,e$，货币面额分别为$1,2,5,10,20,50,100$（汇率为$d$的）和$5,10,20,50,100,200$（汇率为$e$的）

求出换后$n$的最小值

显然易见，暴力模拟即可

步骤：

1. 枚举$d$的兑换数（考虑到可以兑换任意数量，直接枚举即可）

2. 剩下的换成$e$（注意：此处只能换成$5$的倍数）

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double lf;
#define reg register
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define input(a){a=0;char c=gc();int f=1;while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+(c&15);c=gc();}a*=f;}
static char buf[1<<21],*p1=buf,*p2=buf;
char bu[1<<21],cha[20];int p,pp=-1;
#define flush(){fwrite(bu,1,pp+1,stdout),pp=-1;}
#define output(x){if(pp>1<<20)flush();if(x<0)bu[++pp]=45,x=-x;do{cha[++p]=x%10+48;}while(x/=10);do{bu[++pp]=cha[p];}while(--p);}
#define Endl bu[++pp]='\n'
#define Space bu[++pp]=' '
#define pc(c) bu[++pp]=c
const int N=100010;
//自行忽略此注释以上
int n,d,e,ans=1<<30;
//定义，答案初始化为无穷大
int main()
{
	input(n);input(d);input(e);
    //输入
	for(int i=0;i<=n/d;++i)ans=min(ans,(n-d*i)%(5*e));//对于每一个d的情况，去掉以后%(5*e)即为n
	output(ans);
    //输出答案
	flush();
	return 0;
}
```

---

## 作者：逃课小姐MS (赞：0)

其实这个题目很简单的：

已经知道了美元欧元都可以不限数量的换取，那么我换2张5元的欧元和换1张10元的欧元是没有区别的。

那么我们就可以很清楚的知道，肯定是要换面额最小的以保证最优。

那么我们可以考虑所有的情况，就是枚举我要换多少张美元1元的钞票，那么剩下的钱就全部换成欧元，这样枚举下来时间复杂度才$O(\frac{n}{d})$。

代码里面就不多做解释了，很简短的。
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstring>

using namespace std;
const int INF=2147483647;

int n,d,e,ans=INF;

int main(){

    scanf("%d%d%d",&n,&d,&e);

    e*=5;

    for(int i=0;i<=n;i+=d) ans=min(ans,(n-i)%e);

    printf("%d\n",ans);

    return 0;
}
```

---

## 作者：BrokenSword (赞：0)

**题意**

Andrew有$n$卢布，他想把卢布换成美元和欧元。

美元有$1,2,5,10,20,100$这几种面额,欧元有$5,10,20,50,100,200$这几种面额，每一种面额都可以兑换任意次。

Andrew希望使兑换完之后他手上剩余的卢布最少。

**输入格式**

第一行一个整数$n$（$1≤n≤10^8$），表示Andrew现有的卢布数。

第二行一个整数$d$（$30≤n≤100$）,表示一美元对卢布的单价。

第三行一个整数$e$（$30≤n≤100$）,表示一欧元对卢布的单价。

**输出格式**

一个整数表示Andrew在兑换完欧元和美元后可以拥有的最少卢布数。

---

因为每一种面额都可以兑换任意次，所以我们自动无视非最小面额。

此时$d$为美元单价，$5*e$为欧元单价。（因为欧元最小面额是5元）

然后暴力求解即可（方法不唯一）。答案可为$min_{0≤i≤\frac{n}{d}}((n-i*d) \bmod{e})$。时间复杂度为 $O(\frac{n}{d})$.

放一下核心代码吧。↓

```cpp
int　main(){　
	q=read();　
	w=read();　
	e=read();　
	e*=5;　
	RE int a=max(q/w,1),b=max(q/e,1);　
	for(RE int i=0;i*w<=q;i++){　
		ans=min(ans,(q-w*i)%e);　
	}　
	printf("%d\n"，ans);　
	return　0;　
}
```


---

