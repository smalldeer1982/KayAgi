# Prime Problem

## 题目描述

In Berland prime numbers are fashionable — the respectable citizens dwell only on the floors with numbers that are prime numbers. The numismatists value particularly high the coins with prime nominal values. All the prime days are announced holidays!

Yet even this is not enough to make the Berland people happy. On the main street of the capital stand $ n $ houses, numbered from 1 to $ n $ . The government decided to paint every house a color so that the sum of the numbers of the houses painted every color is a prime number.

However it turned out that not all the citizens approve of this decision — many of them protest because they don't want many colored houses on the capital's main street. That's why it is decided to use the minimal possible number of colors. The houses don't have to be painted consecutively, but every one of $ n $ houses should be painted some color. The one-colored houses should not stand consecutively, any way of painting is acceptable.

There are no more than 5 hours left before the start of painting, help the government find the way when the sum of house numbers for every color is a prime number and the number of used colors is minimal.

## 样例 #1

### 输入

```
8```

### 输出

```
1 2 2 1 1 1 1 2```

# 题解

## 作者：龙神哈迪斯 (赞：11)

###  [题面](http://codeforces.com/contest/45/problem/G)

你需要给$n$栋屋子刷颜色，每栋屋子的序号为$i$

要求用尽量少的颜色，使得同种颜色的屋子序号之和为质数

注意：1不是质数

### Sol

多久以前的构造题了(~~要不是今天考试考到构造我是绝不会来做的~~)

不网上翻题解根本不会啊，~~毕竟自己太菜了~~

首先你需要良好的数学知识，知道哥赫巴德猜想的推论

就放个度娘在这吧 https://zhidao.baidu.com/question/5394605.html

然后是它的推论:每个大于2的偶数可以拆成两个质数之和

我们首先算出$1-n$的和$m=(n+1)*n/2$

然后分三种情况

１．$m$本身是质数，那么所有的屋子可以刷同一颜色

２．$m$是偶数，那么所有屋子最少刷两种颜色，我们可以$O(n)$的找到哪一间屋子需要刷第二种颜色

３．$m$是奇数，如果可以拆成一个２和一个奇质数的形式，就只需要两种颜色；否则我们将$m$减去３，然后此时$m$一定是偶数，我们再用讨论二即可

上代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int _=6005;
inline int read()
{
	char ch='!';int z=1,num=0;
	while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch=='-')z=-1,ch=getchar();
	while(ch<='9'&&ch>='0')num=(num<<3)+(num<<1)+ch-'0',ch=getchar();
	return z*num;
}
int n,ans[_];
void Print()
{
	for(int i=1;i<=n;++i)
		printf("%d ",ans[i]);
	puts("");
}
bool check(int x)
{
	int q=sqrt(x);
	for(int i=2;i<=q;++i)
		if(!(x%i))return 0;
	return 1;
}
int main()
{
	n=read();
	int m=(n+1)*n/2;
	for(int i=1;i<=n;++i)ans[i]=1;
	if(check(m)){Print();return 0;}
	if(m&1&&!check(m-2))ans[3]=3,m-=3;
	for(int i=2;i<=n;++i)
		if(check(i)&&check(m-i))
		{ans[i]=2;break;}
	Print();
	return 0;
}

```


---

## 作者：chihik (赞：5)

#### 前置知识：哥德巴赫猜想：任一大于2的偶数都可写成两个质数之和

~~然后，这道题就非常水了。~~

令$S=1+2+...+n$ , 我们分类讨论$S$的情况就好了。

1.$S$为一个质数

这时将所有数加起来，分为一个区间。

2.$S~ \equiv ~0 (mod~~2) $

根据哥猜，我们将$S$分解为两个质数，分别标记。

这里有一个小结论：$S$分成的两个质数中，有一个小质数一定小于$n$。

至于证明$emmm...$，~~用计算机暴力吧（$n \le 6000$)~~

3.$S~ \equiv ~1 (mod~~2) $

(1)$S-2$为一个质数，分为两个区间:$2$与$S-2$

(2)不然，将$S-3$ , 它是一个偶数，按情况2分解，这时需要三个区间，3 和 哥猜分出的两个质数。



```cpp
#include <cstdio>

const int MAXN = 6000;
int n , sum , belong[ MAXN + 5 ];

bool zs( int x ) {
    if( x == 1 ) return 0;
    for( int i = 2 ; i * i <= x ; i ++ )
        if( x % i == 0 ) return 0;
    return 1;
}
void Make( int x ) {	//将一个数分解成两个质数之和
    for( int i = 2 ; i <= n ; i ++ )
        if( belong[ i ] == 1 && zs( i ) && zs( x - i ) ) {
            belong[ i ] = 2;
            return;
        }
}
int main( ) {
    scanf("%d",&n);
    sum = n * ( n + 1 ) / 2;
    for( int i = 1 ; i <= n ; i ++ )
        belong[ i ] = 1;
    if( zs( sum ) )
        1;
    else if( sum % 2 == 0 )
        Make( sum );
    else {
        if( zs( sum - 2 ) )
            belong[ 2 ] = 2;
        else
            belong[ 3 ] = 3 , Make( sum - 3 );
    }
    for( int i = 1 ; i < n ; i ++ )
        printf("%d ",belong[ i ]);
    printf("%d",belong[ n ]);
    return 0;
}
```


---

## 作者：MY（一名蒟蒻） (赞：2)

[CF45G Prime Problem](https://www.luogu.com.cn/problem/CF45G)

构造好题。

构造题常规操作：**对于某些不知道有没有可能无解的题，大胆猜测一定有解。不要上来就骗分输出无解。**

---
接下来我们慢慢分析做法。

定义 $sum$ 为这个数列的和。
### 分一组
最简单的情况。 $sum$ 为质数。

那么用等差数列求和求出来之后直接判断一下即可。
### 分两组
1.  $sum$ 是偶数的情况

引入[哥德巴赫猜想](https://baike.baidu.com/item/%E5%93%A5%E5%BE%B7%E5%B7%B4%E8%B5%AB%E7%8C%9C%E6%83%B3/72364?fr=aladdin)。

好像已经证明了哥德巴赫猜想在某个挺大的范围内是正确的了，具体我也不太清楚。

~~我觉得是它一定是对的。~~

于是带着这种信念，枚举其中较小的质数，然后把它单独拎出来分一个组即可。

较小的质数一定小于 $n$ ，~~我不会证明。~~

2. $sum$ 是奇数的情况，当且仅当 $\text{sum-2}$ 是质数时成立。

### 分三组
 $sum$ 是奇数的情况，而且此时分两组情况不满足。

考虑让 $sum$ 变成偶数，由于最小的奇质数是 $3$ ，所以多分一组给 $3$ ，然后按照偶数情况处理。

---
至此可以发现我们已经讨论完了所有情况，不存在无解的情况。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int n,sum,ans[6010];
inline bool is_prime(int x)
{
	if(x < 2) return false;
	for(int i=2;i*i<=x;i++) if(x%i == 0) return false;
	return true;
}

inline void draw(int x)
{
	for(int i=2;i<=x>>1;i++)
		if(ans[i] == 1 && is_prime(i) && is_prime(x-i)) {ans[i]=2; return ;}
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	sum=(n*(n+1))>>1;
	for(int i=1;i<=n;i++) ans[i]=1;
	if(!is_prime(sum))
	{
		if(sum&1)
		{
			if(is_prime(sum-2)) ans[2]=2;
			else {ans[3]=3; draw(sum-3);}
		}
		else draw(sum);
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
线性筛没必要，实测根号暴力甚至更快。
## $\text{Thank you for your reading!}$
您的点赞和评论是对作者最大的支持！

---

## 作者：东灯 (赞：2)

本题考虑哥猜构造

哥德巴赫猜想即“任何一个一大于2的偶数都可写成两个质数之和”

即如果
$$A>2 \ \cap \ A  \ mod \ 2 =0$$
那么设$B,C$是两个符合条件的质数，一定存在
$$A=B+C$$

回到本题，我们可以尝试假设
$$U=\sum^n_{i=1}i$$

根据高斯的
$$\sum^n_{i=1}=(n+1)n /2$$
我们可以快速的计算$U$的值

即1~$n$的整数和，那么我们就可以对$U$进行分类讨论

1.如果
$$U \ mod \ I \in R >0\ \cap \ I>1$$
那么这就是一组合理的分配方案，直接出就可以了

2.如果
$$U \ mod \ 2=0$$
那么我们可以得出，$U$一定可以被分割成两个质数，而且这两个质数一定都小于$U$,其中一个一定也$<n$，因为无论在$2<=n<=6000$范围内两个质数组合总会有一个非常小的质数可以$<n$，关于证明就不在这里写了。

3.如果
$$U \ mod \ 2=1$$

那么我们可以尝试先把$U-2$，这样我们就能得到一个另外的质数和一个2，否则我们继续把$U$减去3,然后以此类推，就可以把偶数带入讨论2,质数带入讨论1,奇数继续讨论3。

代码就不贴了，实现这边比较重要的是需要线性的筛子预处理，毕竟$n$也确实不大，可能$N^2$的筛子都能过吧，筛完之后就按照上述讨论模拟即可。

---

## 作者：XL4453 (赞：1)

### 题目分析：

显然是构造。

脑子一抽想到哥猜。~~我自己也不知道我怎么想到的就不分析怎么想到的了~~。

首先发现这 $n$ 个数的和是很好求的，直接有总和等于 $\dfrac{n\times(n+1)}{2}$。

然后分情况，假如这本身就是个质数那么直接全放到一组即可。

假如是一个偶数，易知不可能只通过一组数就成功构造出符合条件的组别。这时，根据哥德巴赫猜想（这个正确性是可以保证的，在本题的数据范围内，哥猜已经验证完了），一定有这个偶数可以分成两个质数之和。那么找出这两个质数然后随便把其中一个拆成两个就行了。

否则只有一种可能，那就是总和是一个非质奇数。这样的一个奇数只可能分解为一个奇数和一个偶数，如果偶数为 $2$，且剩下的那一个奇数恰好是一个质数，那么只需要分成两组。否则一定要把这个大奇数分成三个奇素数，然后发现，可以从大奇数里提取一个小的奇素数，然后再把问题转化为一个偶数的分解问题。

这样的一个奇素数可以取很多，随便取一个就行，注意不要太大，当然最简单的就是取 $3$ 了。

------------
### 代码：

```
#include<cstdio>
using namespace std;
bool check(int num){
	for(int i=2;i*i<=num;i++)
	if(num%i==0)return 0;
	return 1; 
}
int n,m,rec[6006];
void work(){
	if(check(m))return;
	if(m&1){
		if(check(m-2)){
			rec[2]=2;
			return;
		}
		rec[5]=3,m-=5;//五也是可以的
	}
	for(int i=2;i<=n;i++)
	if(check(i)&&check(m-i)){
		rec[i]=2;
		return;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)rec[i]=1;
	m=n*(n+1)/2;
	work();
	for(int i=1;i<=n;i++)printf("%d ",rec[i]);
	return 0;
}
```


---

## 作者：Durancer (赞：1)

#### 前言

翻译有误，坑死我了，没有说是最小

~~想看题解先去学哥德巴赫猜想（30min）~~

~~你看完应该也不用我了~~

#### 题面

给定 $1-n$ ,$n$ 个的数，要求求出最小分成几组，可以是每一组都是一个质数

#### 前置知识

1、求1-n前缀和公式

首先，根据从 $1-n$ 的求和公式，可以得出$sum= \dfrac{n\times (n-1)}{2}$

2、
[哥德巴赫猜想（世界近代三大数学难题之一）](https://baike.baidu.com/item/%E5%93%A5%E5%BE%B7%E5%B7%B4%E8%B5%AB%E7%8C%9C%E6%83%B3/72364?fr=aladdin)

首先让我们研究一下这个哥德巴赫给大数学家欧拉的信，提取一些有关信息

1742年，哥德巴赫给欧拉写的信之中，写到猜测任何大于二的整数都可以写成三个质数之和的形式,那么这个就是解题的关键了，所以可以得出，分组最多会有三种

根据哥德巴赫猜想，任意 $>2$ 的一个偶数都可以被表示成两个质数的和的形式

   - 总和本来就是一个质数，全输出 $1$
   
   - 总和是一个偶数，那么从 $1-n$ 里面找，知道有一个数字 $i$ 可以满足 $i$ 为素数，并且 $sum-i$ 也是一个质数
   
   - $sum$ 是一个奇数 
        
     $sum$ 是一个奇数，那么就 $n-3$ 也是个偶数，那么就可以分成两个是质数的形式，就可以分为三个区间
        
看到这里你就可以过前四个点了hhh

我们还需要满足最小分组这个条件，可以想一下第三种情况，如果 $sum-2$
 是一个质数，那么就可以分成两组了，而不是分成三组，所以要记得判断这个条件
 
#### 代码实现

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=6e3+9;
int poi[N];
int n,sum;
int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
    return x*f;
}
bool prime(int x)
{
    if(x==1) return false;
    for(int i=2;i*i<=x;i++)
        if(x%i==0) return false;
    return true;
}
void check(int x)
{
    for(int i=2;i<=n;i++)
        if(poi[i]==1&&prime(i)&&prime(x-i))
        {
            poi[i]=2;
            return;
        }
}
int main()
{
    n=read();
    sum=n*(n+1)/2;
    for(int i=1;i<=n;i++)
        poi[i]=1;//memset貌似不能赋1 
    if(prime(sum)) goto Here;
    if(sum%2==0)
    {
        check(sum);
        goto Here; 
    } 
    if(sum%2==1)
    {
        if(prime(sum-2))
        {
            poi[2]=2;
            goto Here;
        }
        sum-=3;
        poi[3]=3;
        check(sum);
        goto Here;
    }
    Here:;
    for(int i=1;i<=n;i++)
        printf("%d ",poi[i]); 
    return 0;
}
```


---

## 作者：Zzzzzzzm (赞：0)

## 思路
**哥德巴赫猜想：任一大于 $2$ 的偶数都可写成两个素数之和。**

根据哥德巴赫猜想至今为止的证明，已证明的数据范围肯定远大于这道题的数据了，所以可以放心使用。

设 $S=1+2+\dots+n$，那么有以下几种情况。

+ 若 $S$ 为质数(实质上只有 $n=2$ 的时候可能出现)，那么直接将其分为一组。
+ 若 $S$ 为偶数，那么根据哥德巴赫猜想，可以断定$S$能分为两个素数之和，并且这两个素数中有一个是可以小于 $n$ 的。枚举找素数，然后构造出来就可以了。
+ 若 $S$ 为非素奇数，分两种情况：
  1. 取出一个 $2$ 以后就是质数，就直接取 $2$ 即可。(不可或缺，否则可能无解)
  2. 可以从中取一个奇素数(方便起见取 $3$)，然后转化为问题 $2$。

注意如果进行了 $3$ 的第二步操作应该加一个标记再进行 $2$，搜索时搜到 $3$ 直接跳过，保证答案的正确性。可以用线筛预处理出所有素数，当然也可以算到的时候再枚举。

## $Code$

```c++
#include<bits/stdc++.h>
using namespace std;

int prime[1900005], cnt;
bool nprime[18500005];
int n, sum;
int pos[6005];
bool flag;

template<typename T>
inline void read(T&x){
	x = 0; char q; bool f = 1;
	while(!isdigit(q = getchar()))	if(q == '-')	f = 0;
	while(isdigit(q)){
		x = (x<<1) + (x<<3) + (q^48);
		q = getchar();
	}
	x = f?x:-x;
}

template<typename T>
inline void write(T x){
	if(x < 0){
		x = -x;
		putchar('-');
	}
	if(x > 9)	write(x/10);
	putchar(x%10^48);
}

inline void init(){								//线筛预处理
	for(register int i = 2; i <= 18500005; ++i){
		if(!nprime[i])	prime[++cnt] = i;
		for(register int j = 1; j <= cnt; ++j){
			if(prime[j]*i > 18500005)	break;
			nprime[prime[j]*i] = 1;
			if(i%prime[j] == 0)	break;
		}
	}
}

inline void ans(){								//求解
	if(!nprime[sum])	return;						//如果是就直接返回
	if(sum&1){								//若为奇数
		if(!nprime[sum-2]){						//如果32是素数直接修改2的pos返回
			pos[2] = 2;
			return;
		}
		sum -= 3;							//否则-3，打标记
		pos[3] = 3;
		flag = true;
	}
	for(register int i = 1; i <= cnt; ++i){
		if(flag && i == 2)	continue;				//如果用过3了就跳过
		if(!nprime[sum-prime[i]]){
			pos[prime[i]] = 2;					//如果减去一个素数仍是素数就修改素数位置并返回。
			return;
		}
	}
}

int main(){
	init();
	read(n);
	sum = (n+1)*n/2;							//求和
	for(register int i = 1; i <= n; ++i)	pos[i] = 1;
	ans();
	for(register int i = 1; i <= n; ++i){
		write(pos[i]);
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：MuYC (赞：0)

#### 哥德巴赫猜想:

一个大于 $2$ 的偶数能够表示为两个奇质数的和的形式。

#### 一个 trick:

在 $[1,n]$ 每个数只能用一次的前提下，$[1$, $\frac{(n + 1) \times n}{2}]$ 的正整数都能表示为 $[1,n]$ 中若干数的和的形式。

#### 关于本题

首先 **$n \ge 2$ 一定有解**

这道题一定有解（除非 $n = 1$），证明的话如下：

显然 $n = 2$ 或者 $n = 3$ 的时候 一定有解。

用数学归纳法来看，假设 $n$ 有解，那么考虑假设现在变为 $n + 1$。

将大于等于 $n + 1$ 的最小的质数设为 $P$ ，那么 $P < 2 \times (n + 1)$ ，也就是意味着 $P - (n + 1)$ 一定位于 $[1,n]$ 中，设为 $x$，然后我们让 $x$ 与 $n + 1$ 配对，然后 $x + 1$ 和 $n$ 配对以此类推。

因为 $P$ 为奇数，所以只会出现奇数偶数配对，所以一定可以配对完 $[x,n + 1]$，那么剩下的数变为了 $[1,x - 1]$，可以发现一定有解。 

但是我们构造的时候可以不用这个方法，因为其实本题有个要求就是，如果可行，那么将 $[1,n]$ 要分成尽量少的集合。

**哥德巴赫猜想** 构造答案。

设 $S = \frac{(n + 1) \times n }{2}$

+ 如果 $S$ 是一个质数，那么所有的数都选在一个集合就好了。

+ $S$ 是一个偶数，根据哥德巴赫猜想和上面提到的 trick 可以知道一定可以把 $S$ 分成两个奇质数的和，又因为 $[1,S]$ 的每个数都能被 $[1,n]$ 中若干数的和表示，所以可以得到解。

	ps.如何把一个数 $T \in [1,S]$ 拆分为 $[1,n]$ 中若干数的和的形式？就不断的减去小于等于它的最大的那一个 $i$ ($i$ 是 $[1,n]$ 中的正整数)即可。

+ 如果 $S$ 是一个奇数，倘若 $S - 2$ 是一个质数，直接分为 $2$ 和 $S - 2$ 两个集合。如果 $S - 2$ 不是一个质数，那么我们把 $S - 3$，也就是提出一个 $3$ 出来，然后按照哥德巴赫猜想做就完事了。值得注意的是，我们把 $3$ 去掉后，$[1,S]$ 的任意数还是能够被表示出来，这个不难证明。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, S;
int pd(int x) {
	for(int i = 2 ; i * i <= x ; i ++) if(x % i == 0) return 0;
	return 1;
}
const int MAXN = 2e7;
int P[1 << 21], tot = 0;
bool bk[MAXN], is[6050];
void GetPrime(int N) {
	for(int i = 2 ; i <= N ; i ++) {
		if(!bk[i]) P[++ tot] = i;
		for(int j = 1 ; j <= tot && P[j] * i <= N ; j ++) {
			bk[P[j] * i] = 1;
			if(i % P[j] == 0) break;
		}
	}
	return ;
}

int main() {
	cin >> n; S = (n + 1) * n >> 1, GetPrime(18003000);
	if(pd(S) == 1) { for(int i = 1 ; i <= n ; i ++) printf("1 "); return 0;}
	if(S % 2 == 1 && pd(S - 2) == 0) {
		S -= 3;
		int t = 1;
		for(int i = 1 ; i <= tot ; i ++) 
		if(bk[S - P[i]] == 0) { t = i; break; }
		S = P[t];
		for(int i = n ; i >= 1 ; i --) 
		if(S - i >= 0 && i != 3) S -= i, is[i] = 1;
		for(int i = 1 ; i <= n ; i ++) {
			if(i == 3) { printf("1 "); continue; }
			is[i] ? printf("2 ") : printf("3 "); 
		}
	}
	else if(S % 2 == 1 && pd(S - 2) == 1) 
    for(int i = 1 ; i <= n ; i ++) i == 2 ? printf("2 ") : printf("1 ");
	else {
		int t = 1;
		for(int i = 1 ; i <= tot ; i ++) 
		if(bk[S - P[i]] == 0) { t = i; break; }
		S = P[t];
		for(int i = n ; i >= 1 ; i --) 
		if(S - i >= 0) S -= i, is[i] = 1;
		for(int i = 1 ; i <= n ; i ++)
		is[i] ? printf("1 ") : printf("2 "); 
	}
	return 0;
}
```

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF45G)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;根据哥德巴赫猜想的部分数据正确性，我们可以得到如下方法：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$S=\sum_{i=1}^ni$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.如果$S$是质数，则可以直接作一组输出。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.如果$S$是偶数，根据哥德巴赫猜想，可以直接分成两个质数，其中一个在$[1,n]$中。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.如果$S$是偶数，先判断这个和能否被拆成$2$加一个质数，如果不行，就先从中拆出一个$3$，然后再按照$S$是偶数的方法拆分。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于小于等于$n$的质数，我们用筛法预处理。对于大于$n$的质数，我们用$O(\sqrt n)$的方法暴力。
# 代码
```cpp
#include <cstdio>

const int MAXN = 6005;

template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
    while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}

int prime[MAXN], tot;
int N, sum;
bool isPrime[MAXN];

void EulerSieve( const int siz )
{
	isPrime[1] = true;
	for( int i = 2 ; i <= siz ; i ++ )
	{
		if( ! isPrime[i] )
		{
			prime[++tot] = i;
		}
		for( int j = 1 ; j <= tot && 1ll * i * prime[j] <= siz ; j ++ )
		{
			isPrime[i * prime[j]] = true;
			if( ! ( i % prime[j] ) ) break;
		}
	}
}

bool chk( const int x )
{
	if( x <= 1 ) return false;
	for( int i = 2 ; 1ll * i * i <= x ; i ++ )
	{
		if( ! ( x % i ) ) return false;
	}
	return true;
}

int split( const int num, const int unallowed )
{
	for( int i = 2 ; i <= N ; i ++ )
	{
		if( unallowed ^ i && ! isPrime[i] && chk( num - i ) )
		{
			return i;
		}
	}
	return -1;
}


int main()
{
//	freopen( "data.out", "w", stdout );
	read( N );
	sum = ( N + 1 ) * N / 2;
	EulerSieve( N );
	if( chk( sum ) )
	{
		for( int i = 1 ; i <= N ; i ++ )
		{
			write( 1 ), putchar( i == N ? '\n' : ' ' );
		}
		return 0;
	}
	else if( sum & 1 )
	{
		if( chk( sum - 2 ) )
		{
			for( int i = 1 ; i <= N ; i ++ )
			{
				if( i ^ 2 ) write( 1 );
				else write( 2 );
				putchar( i == N ? '\n' : ' ' );
			}
			return 0;
		}
		else
		{
			int tmp = split( sum - 3, 3 );
			if( tmp == -1 ) return puts( "-1" );
			for( int i = 1 ; i <= N ; i ++ )
			{
				if( i == tmp ) write( 2 );
				else if( i == 3 ) write( 3 );
				else write( 1 );
				putchar( i == N ? '\n' : ' ' );
			}
			return 0;
		}
	}
	else
	{
		int tmp = split( sum, 0 );
		if( tmp == -1 ) return puts( "-1" );
		for( int i = 1 ; i <= N ; i ++ )
		{
			if( i ^ tmp ) write( 1 );
			else write( 2 );
			putchar( i == N ? '\n' : ' ' );
		}
		return 0;
	}
	return 0;
}
```

---

## 作者：Rainybunny (赞：0)

# 哥猜+构造
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到题面, 第一想法一定是利用[哥德巴赫猜想](https://baike.baidu.com/item/%E5%93%A5%E5%BE%B7%E5%B7%B4%E8%B5%AB%E7%8C%9C%E6%83%B3/72364?fr=aladdin)构造答案. 于是, 令$s=\sum_{i=1}^ni$, 分三种情况讨论:  
1. $s$是素数.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;比较简单, 全部归为同一集合即可.  

2. $s$是偶数  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;根据哥猜, 一定能把$s$分为两个素数. 且可以证明 ( 嘤我不会$w$ ) 可以在$[2,n]$的范围内找到其中一个素数. 枚举以哪个数作为其中一个素数即可.  

3. $s$是奇数  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;若$s-2$是素数, 则$2$独成集合, 其余数成另一集合; 否则, 则选出$3$独成集合, 并带入第$2$种情况.  

~~所以这道题为什么是紫的, 难点是证哥猜么? /滑稽.~~

```cpp
#include <cstdio>

#define Int register int

const int MAXN = 6000, MAXP = 783;
int n, pn, Prime[MAXP + 5] = {};
bool Vis[MAXN + 5] = {};

inline bool Isprime ( const int x ) {
	for ( Int i = 2; 1LL * i * i <= x; ++ i ) {
		if ( ! ( x % i ) ) {
			return false;
		}
	}
	return x > 1;
}

inline void Sieve ( const int n ) {
	for ( Int i = 2; i <= n; ++ i ) {
		if ( ! Vis[i] ) {
			Prime[++ pn] = i;
		}
		for ( Int j = 1; j <= pn && 1LL * i * Prime[j] <= n; ++ j ) {
			Vis[i * Prime[j]] = true;
			if ( ! ( i % Prime[j] ) ) break;
		}
	}
}

inline void Work () {
	scanf ( "%d", &n );
	Sieve ( n );
	const int s = n * ( n + 1 ) >> 1;
	if ( Isprime ( s ) ) {
		for ( Int i = 1; i <= n; ++ i ) {
			putchar ( '1' ), putchar ( i ^ n ? ' ' : '\n' );
		}
	} else if ( ! ( s & 1 ) ) {
		for ( Int i = 2; i <= n; ++ i ) {
			if ( ! Vis[i] && Isprime ( s - i ) ) {
				for ( Int j = 1; j <= n; ++ j ) {
					printf ( "%d", i ^ j ? 1 : 2 ), putchar ( j ^ n ? ' ' : '\n' );
				}
				return ;
			}
		}
	} else {
		if ( Isprime ( s - 2 ) ) {
			for ( Int i = 1; i <= n; ++ i ) {
				printf ( "%d", i ^ 2 ? 1 : 2 ), putchar ( i ^ n ? ' ' : '\n' );
			}
		} else {
			for ( Int i = 2; i <= n; ++ i ) {
				if ( i ^ 3 && ! Vis[i] && Isprime ( s - i - 3 ) ) {
					for ( Int j = 1; j <= n; ++ j ) {
						printf ( "%d", j == 3 ? 3 : ( j ^ i ? 1 : 2 ) ), putchar ( j ^ n ? ' ' : '\n' );
					}
					return ;
				}
			}
		}
	}
}

int main () {
	Work ();
	return 0;
}
```

---

