# Sherlock and his girlfriend

## 题目描述

Sherlock 有一个新女朋友。现在情人节就要到了，他想送给她一些珠宝。 

他买了几件首饰。第 $i$ 件的价格等于 $i+ 1$，也就是说，珠宝的价格分别为 $2,3,4,n + 1$ 。

现在需要给这些珠宝首饰上色。**当一件珠宝的价格是另一件珠宝的价格的素因子时，这两件的颜色就不允许相同。** 此外，要最少化使用的颜色数量。

## 说明/提示

在第一个样例中，第一、第二和第三件首饰的价格分别为 $2$、$3$、$4$,它们的颜色分别为 $1$ 、$1$ 和 $2$。

在这种情况下，由于 $2$ 是 $4$ 的因子，所以具有因数 $2$ 和 $4$ 的珠宝的颜色必须是不同的。

Translated by @皎月半洒花。

## 样例 #1

### 输入

```
3
```

### 输出

```
2
1 1 2 ```

## 样例 #2

### 输入

```
4
```

### 输出

```
2
2 1 1 2
```

# 题解

## 作者：Juanzhang (赞：20)

## 吐槽题目难度！线性筛难度都为$\color{red}\colorbox{white}{普及-}$!

**进入正题**

因为一个数不能与自己的**质因子**同色，所以所有**质数**可以同色。

又因为所有**质因数**已被染色，所以就不需要对其他数染色了。

所以要找出$[2,n+1]$的所有质数

果断使用**筛法**

[P3383 【模板】线性筛素数](https://www.luogu.org/problemnew/show/P3383)

埃氏筛：

基本思想：素数的倍数一定不是素数

实现方法：用一个$bool$数组保存信息是否是合数，先假设所有的数都是素数（初始化为$false$），从第一个素数$2$开始，把$2$的倍数都标记为非素数（置为$true$），一直到大于$n$；然后进行下一趟，找到$2$后面的下一个素数$3$，进行同样的处理，直到最后，数组中依然为$false$的数即为素数。

（来源：$dormantbs$）

由于一个数的一定有不大于$\sqrt n$的质因子，所以只用筛到$\sqrt n$

- 注意$n<3$时特判。

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int n;
bool flag[maxn];

int main() {
	scanf("%d", &n);
	flag[0] = flag[1] = 1;
	for (int i = 2; i * i <= n + 1; i++) {
		if (!flag[i]) {
			for (int j = i << 1; j <= n + 1; j += i) {
				flag[j] = 1;
			}
		}
	} // 埃氏筛的优化：一个数的最大因子不会超过sqrt(n)
	puts(n < 3 ? "1" : "2");
	for (int i = 2; i <= n + 1; i++) {
		printf("%d ", flag[i] + 1);
	}
	return 0;
}
```

---

## 作者：应吟吟 (赞：11)

## 前言

题目翻译有问题

>  Watson给Sherlock一个挑战：给这些珠宝首饰上色，当一件的价格是另一间的价格的因子时，使得这两件两件没有相同的颜色。此外，Watson要求他使用的尽量少种颜色。

其实应该是

>  Watson给Sherlock一个挑战：给这些珠宝首饰上色，当一件的价格是另一件的价格的质因子时，使得这两件首饰没有相同的颜色。此外，Watson要求他尽量使用少种颜色。

~~(错别字看着难受)~~

## 正题

### 分析题目

我们看一下数据大小 ~~(标签)~~，$1<=n<=100000$，这不是可以写暴力吗？

我们可以现在手动模拟一下

![](https://i.loli.net/2019/03/29/5c9e1e35da1f7.png)



在理解一下题意并手动模拟一下后，不难发现只有在$n<3$时颜色数为$1$，其余情况颜色数均为$2$~~(惊不惊喜，意不意外)~~。

### ~~快乐的~~分析代码~~时间~~

```cpp
#pragma GCC optimize(3)//O3优化
#include<bits/stdc++.h>
#define ll long long

using namespace std;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
template < class T > inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    x = f ? -x : x;
}
#undef getchar()

template < class T > inline void write(T x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}//输入输出优化

const ll FFF=1000000+5;

ll n;
ll ans=1;

struct node
{
    ll price,color;
}zb[FFF];//price表示珠宝的价格，color表示珠宝的颜色
//zb表示珠宝(拼音应该看得懂吧)

bool isprime(int x){
    if(x==1)
        return false;
    if(x==2||x==3)
        return true;
    if(x%6!=1&&x%6!=5)
        return false;
    int s=sqrt(x);
    for(int i=5;i<=s;i+=6)
        if(x%i==0||x%(i+2)==0)
            return false;
    return true;
}//(龟速)判断素数(想要快一点的话可以去学一学埃氏筛，MR等等快一点的筛法)

int main()
{
    if(fopen("aaa.in", "r"))
    {
        freopen("aaa.in", "r", stdin);
        freopen("aaa.out", "w", stdout);
    }
    ios::sync_with_stdio(false);//关闭流同步，还是输入输出优化
    read(n);
    for(int i=1;i<=n;++i)
    {
        zb[i].price=i+1;
        zb[i].color=1;
    }//初始化，定义珠宝i的价格为i+1,颜色为1
    for(int i=1;i<=n/2;++i)//只需要从1搜索到n/2，因为n/2+1到n这个区间中是不可能互相为质因子的
    {
        if(isprime(zb[i].price)==true)//如果i是质数，那它可能是作为某一个数的质因子
        {
            ll now=1;//现在进行枚举，枚举一个数的质因子为zb[i].price，now表示倍数
            while(now*zb[i].price<=n+1)//如果枚举的数不大于n(即价格不大于n+1)，就说明zb[i].price是这个数的质因数
            {
                now+=1;//倍数+=1，
                zb[now*zb[i].price-1].color=zb[i].color==1?2:1;//zb[now*zb[i].price-1].color要与zb[i].color不同，所以当zb[i].color==1时zb[now*zb[i].price-1].color=2.否则zb[now*zb[i].price-1].color=1
            }
        }
    }
    write(n<3?1:2);//根据上面的结论，当n<3时输出1，否则输出2
    putchar('\n');
    for(int i=1;i<=n;++i)
    {
        write(zb[i].color);//输出第i个珠宝的颜色
        putchar(' ');
    }
    return 0;
}
```



---

## 作者：一只萌新 (赞：2)

[CF776B Sherlock and his girlfriend](https://www.luogu.org/problemnew/show/CF776B)

实际上的题面

> 给序列 2~n+1 染色,同时要求每个数和他的质因数的颜色不同 

注意是**质因子**

样例输入似乎也有点问题，我们不用管样例，题中已说明 

> 如果有多种方法，则可以输出它们中的任何一种。

~~乱搞开始~~

* 首先注意到，**为使所用颜色尽量少，所有质数染同一种颜色**

想想看是不是这么回事 

质数的约数只有1和本身，所有质数当然可以染同一种颜色 

- 我们令质数的颜色为1 

* 接下来考虑合数。**由于质数已被染上1，合数的质因子是质数，故合数只要不染1就可以**

再提一句：题面说的是质因子，即 4和8可以染同一种颜色

- 那就让合数染上2就好了 

~~乱搞结束~~

$AC$ $Code$

```cpp
#include<iostream>
#include<cstdio>
#define re register
#define il inline
#define ll long long
using namespace std;

inline int read(){
    int s=0,f=0;char c=getchar();
    while(c<'0'||c>'9') f=(c=='-'),c=getchar();
    while(c>='0'&&c<='9') s=(s<<3)+(s<<1)+(c^'0'),c=getchar();
    return f?-s:s;
}

const int N=1e5+5;
int n,k;
il bool prime(int x){		//这个函数是用来判断素数的  
	if(x==1||x==0) return 0;
	if(x==2||x==3) return 1;
	if(x%6!=1&&x%6!=5) return 0;
	for(re int i=5;i*i<=x;i+=6) if((!(x%i))||(!(x%(i+2)))) return 0;
	return 1;
}
int main(){
	n=read();
	if(n<=2){	//n<=2 时 序列中只有质数,特判   
		puts("1");
		for(re int i=1;i<=n;++i) puts("1");
		return 0;
	}
	puts("2");	//n>2 有质数有合数   
	for(re int i=2;i<=n;++i){
		if(prime(i)) printf("1 ");
		else printf("2 ");
	}
	if(prime(n+1)) printf("1\n");
	else printf("2\n");
    return 0;
}
/*
prime 1
not_prime 2  
*/
```

还有什么问题可以评论哦~ 

---

## 作者：二哥啃菜包 (赞：2)

众所周知，这道题翻译有点小问题。

$Description:$

> 题目要求给序列 2~n+1 涂色，同时要求每个数和他的质因数的颜色不同

$Sample$ $Input:$

> 3

$Sample$ $Output$:

> 2
> 1 1 2 

我一看，好一题分解质因数，看我$o(n\sqrt n)$ 随便*。

好吧，好像写不出来，那么考虑别的做法。

首先观察质因数的定义：

#### 百度百科：

> 每个合数都可以写成几个质数相乘的形式，这几个质数就都叫做这个合数的质因数。如果一个质数是某个数的，那么就说这个质数是这个数的质因数；而这个因数一定是一个质数。

简单来讲各位都知道质因数一定是质数。那么质数直接又互质，所以可以分为同一种颜色。

那么再考虑不可能有一个合数为另一个合数的质因数。

显然成立。那么其实只有质数和合数两种颜色。

筛法筛一遍，然后质数合数判一判。

一般都有质数合数。

但一个序列没有,对于本题是：

2，3

因为这个序列没有合数。

那么特判一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt;
const int MAXN=1e5;
int vis[MAXN+5],p[MAXN+5];
int main(){
    scanf("%d",&n);
    for(int i=2;i<=n+1;++i){
        if(!vis[i])p[++cnt]=i;
        for(int j=1;j<=cnt && i*p[j]<=n+1;++j){
            vis[i*p[j]]=1;
            if(i%p[j]==0)break;
        }
    }
    if(n<3)putchar('1');
    else putchar('2');
    putchar('\n');
    for(int i=2;i<=n+1;++i)
        if(!vis[i])printf("1 ");
        else printf("2 ");
    putchar('\n');
    return 0;
}
```



---

## 作者：四氧化二磷 (赞：2)

# Sherlock and His Girlfriend
【题目描述】

　　Sherlock 有了一个新女友（这太不像他了！）。情人节到了，他想送给女友一些珠宝当做礼物。

　　他买了 n 件珠宝。第 i 件的价值是 i+1。那就是说，珠宝的价值分别为 2,3,4,⋯,n+1。

　　Watson 挑战 Sherlock，让他给这些珠宝染色，使得一件珠宝的价格是另一件的质因子时，两件珠宝的颜色不同。并且，Watson 要求他最小化颜色的使用数。

　　请帮助 Sherlock 完成这个简单的任务。
  

------------


　
 
　　算法：依旧埃氏筛
  
　　题目看着像个巨难的dp,其实就是一个筛素数的过程。
  
　　我们需要明确，**所有素数互质**。题意是**让我们把所有的数划分在不同的组内，且使得每个组内的数两两之间互质或均为合数（使得一件珠宝的价格是另一件的质因子时，两件珠宝的颜色不同即存在至少一个质数）**。既然所有素数互质，那么灵活应用贪心的策略，把它们放在一个组里，剩下的....
  
　　似乎刚好全是合数啊....
  
　　那就丢在一个组里，反正不可能出现质数。
  
　　然后我们惊喜地发现，只可能存在一或两种颜色。
  
　　那么什么时候有一组？
  
　　全是质数的时候。而最小的合数4是第三个，所以n<=2时可以用TP（特判）算法。
  
code:
```
#include<bits/stdc++.h>  
using namespace std;
int n,a[100005];
bool b[100005];
inline void mkprim(){
	for(int i=2;i<=n+1;i++){
		if(!b[i]){
			printf("%d ",1);
			for(int j=i*2;j<=n+1;j+=i)b[j]=1;
		}
		else printf("%d ",2);
	}
	return ;
} 
int main(){
	scanf("%d",&n);
	if(n-1==0)printf("1\n1"),exit(0);
	if(n-2==0)printf("1\n1 1"),exit(0);
	printf("2\n");mkprim();
	return 0;
}
```

---

## 作者：冒泡ioa (赞：2)

# 题解
显然如果$i + 1$是一个质数，那么只有价格为$i + 1$的倍数的珠宝必须具有不同的颜色  
所以我们枚举$2$到$n+1$，并且如果枚举到的珠宝没涂色，说明是个质数，让他的倍数涂色  
最后我们留下来的就是质数和非质数，而质数之间不可能互为质因数，非质数之间也不能为质因数，所以只要你将他们分别输出不同的数字就行  
## 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
bool s[100005];

int main(){
	int n;
	cin>>n;
	for(int i=2;i<=n+1;i++){
		if(!s[i]){
			for(int j=i<<1;j<=n+1;j+=i)s[j]=1;
		}
	}
	if(n>2)cout<<"2\n";
	else cout<<"1\n";
	for(int i=2;i<=n+1;i++){
		if(!s[i])cout<<"1 ";
		else cout<<"2 ";
	}
	return 0;
}
```

---

## 作者：RainFestival (赞：1)

很简单嘛

我们把质数合数分开放就行啦

下面是代码：

```pascal
var
  n,i,j,pn,m,x:longint;
  mindiv,pr:array[0..10000005] of longint;
  b:array[0..100000005] of boolean;
begin
  readln(n);
  inc(n);
  inc(n);
  for i:=2 to n do
    begin
      if mindiv[i]=0 then
        begin
          inc(pn);
          pr[pn]:=i;
          mindiv[i]:=i;
        end;
      for j:=1 to pn do
        begin
          if pr[j]>mindiv[i] then break;
          if i*pr[j]>=n then break;
          mindiv[i*pr[j]]:=pr[j]; 
        end;
    end;
  for i:=1 to pn do
    b[pr[i]]:=true;
  if n-2<3 then writeln(1)
           else writeln(2);
  for i:=2 to n-1 do
    if b[i] then write(1,' ')
            else write(2,' ')
   

end.
```

时间3054ms,空间176136kb,代码长度0.68kb

谢谢巨佬大佬神犇们的欣赏！！！

---

## 作者：leoair (赞：0)

# Sherlock and his girlfriend

题目大意:给定$n$个数，第$i$个数的值是$i+1$。如果是质数则把这个点染成$1$，否则染成$2$。

既然要判断是否是质数，那我们就来研究研究**线性筛数法**。

线性筛数法通过"从大到小累积质因子"的方式标记每个和数，即让$12$只有$3 \times 2 \times 2$这一种产生方式。(摘自**算法竞赛进阶指南**)

接下来看看实现:

### Code:

```cpp
#include <bits/stdc++.h>
#define REP(i, a, b) for (long long i = a; i <= b; ++i)
#define ll long long
#define N 100010									//1e5+10，我之前只开了1e3+10，后果惨重 
using namespace std;

ll n, m, a[N], b[N];

inline ll read(){									//快读 
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') w *= -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

inline void xxssf(ll k){							//线性筛数法
	for (ll i = 1; i <= m && b[i] * k <= n; ++i){
		a[k * b[i]] = 2;							//染色 
		if (k % b[i] == 0) break;					//如果k是b[i]的倍数，说明这个点已经被修改过了 
	}
}

inline void work(){									//操作 
	n = read();
	if (n < 3){										//打表 
		puts("1");
		if (n == 2) puts("1 1");
		else puts("1");
		exit(0);
	}
	n++;											//因为第i个首饰的价格=i+1 
	REP(i, 2, n){
		if (!a[i]) a[i] = 1, b[++m] = i;			//判断是否是质数 
		xxssf(i);
	}
	puts("2");
	REP(i, 2, n) printf("%lld ", a[i]);				//输出 
	puts("");
}

int main(){
	work();
	return 0;
}
```



---

## 作者：andyli (赞：0)

题意：  
有$n$个点，编号$2..n+1$，给这些点染色，要求若$a$是$b$的质因子，则$a$和$b$的颜色不同，求一种颜色数最少的方案。  
$n\leq 10^5$  

注意到这是二分图，一边是质数，一边是合数。  
把质数都染成$1$，合数都染成$2$即可。  

代码如下（[快读模板](https://andyli.blog.luogu.org/read-template)）：  
```cpp
const int maxn = 100005;

bool vis[maxn];
vector<int> primes;
void init(int n)
{
    vis[0] = vis[1] = true;
    for (int i = 2; i <= n; i++) {
        if (!vis[i])
            primes.push_back(i);
        for (size_t j = 0; j < primes.size() && i * primes[j] <= n; j++) {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}
int main()
{
    int n;
    io.read(n);
    init(n + 1);
    if (n <= 2) {
        writeln(1);
        for (int i = 1; i <= n; i++)
            io.write(1, " \n"[i == n]);
        return 0;
    }
    writeln(2);
    for (int i = 2; i <= n + 1; i++)
        io.write(vis[i] + 1, " \n"[i == n + 1]);
    return 0;
}
```

---

