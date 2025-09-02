# [USACO09NOV] The Grand Farm-off S

## 题目描述

Farmer John owns 3\*N (1 <= N <= 500,000) cows surprisingly numbered 0..3\*N-1, each of which has some associated integer weight W\_i (1 <= W\_i <= d). He is entering the Grand Farm-off, a farming competition where he shows off his cows to the greater agricultural community.

This competition allows him to enter a group of N cows. He has given each of his cows a utility rating U\_i (1 <= U\_i <= h), which

represents the usefulness he thinks that a particular cow will have in the competition, and he wants his selection of cows to have the maximal sum of utility.

There might be multiple sets of N cows that attain the maximum utility sum. FJ is afraid the competition may impose a total weight limit on the cows in the competition, so a secondary priority is to bring lighter weight competition cows.

Help FJ find a set of N cows with minimum possible total weight among the sets of N cows that maximize the utility, and print the remainder when this total weight is divided by M (10,000,000 <= M <= 1,000,000,000).

Note: to make the input phase faster, FJ has derived polynomials which will generate the weights and utility values for each cow. For each cow 0 <= i < 3\*N,

 $$W_i=(a\times i^5+b\times i^2+c)\mod d$$
 
 $$U_i=(e\times i^5+f\times i^3+g)\mod h$$
 
 $$(0\le a,b,c,d,e,f,g,h\le 10^9)$$

The formulae do sometimes generate duplicate numbers; your algorithm should handle this properly. 

农夫约翰有3N(1 < N < 500000)头牛，编号依次为1..#N，每头牛都有一个整数值的体 重。约翰准备参加农场技艺大赛，向广大的农业社区展示他的奶牛.
大赛规则允许约翰带N头牛参赛.约翰给每头牛赋予了一个“有用度”Ui，它表 示了某头牛在比赛中的有用程度.约翰希望他选出的奶牛的有用度之和最大.

有可能选出很多组的N头牛都能达到有用度最大和.约翰害怕选出的N头牛的总重量会给大赛 带来震撼，所以，要考虑优先选择体重轻的奶牛.

帮助约翰选出N头总重量最轻，并且有用度之和最大的奶牛.输出体重模M后的余数.

注意：为了使输入更快，约翰使用了一个多项式来生成每头牛的体重和有用度.对每头牛/， 体重和有用度的计算公式为：



 $$W_i=(a\times i^5+b\times i^2+c)\mod d$$
 
 $$U_i=(e\times i^5+f\times i^3+g)\mod h$$
 
 $$(0\le a,b,c,d,e,f,g,h\le 10^9)$$

## 说明/提示

The functions generate weights of 5, 6, 9, 14, 21, and 30 along with utilities of 0, 1, 8, 27, 64, and 125.


The two cows with the highest utility are cow 5 and 6, and their combined weight is 21+30=51.


## 样例 #1

### 输入

```
2 0 1 5 55555555 0 1 0 55555555 55555555 
```

### 输出

```
51 
```

# 题解

## 作者：Qing_s (赞：4)

### P2965 【[USACO09NOV]The Grand Farm-off S】

### 挺水的PJ-。

u1s1，第一眼看见题面把我吓到了。

但是！作为新时代的良好青年，要发扬不屈不挠的进取精神！

~~然后我就把它A了。~~

### 分析题意：

>农夫约翰有 $3 * N $ (1 < N < 500000)头牛，编号依次为1..#N，每头牛都有一个整数值的体 重。约翰准备参加农场技艺大赛，向广大的农业社区展示他的奶牛. 大赛规则允许约翰带N头牛参赛.约翰给每头牛赋予了一个“有用度”Ui，它表 示了某头牛在比赛中的有用程度.约翰希望他选出的奶牛的有用度之和最大.

人话翻译：

>在 $3 * N$ 个数中，每个数有对应的 $u_i$ 和 $w_i$ , 求 N 个 $u_i$ 的最大值，最大值相同时让 $w_i$ 最小 。

这不就好起来了？我们只需要使用一个结构体来存 $u_i$ 和 $w_i$ ，使用 sort 排一遍序。
然后输出前 $N$ 个 $u_i$ 的和即可。

那么我们的 $u_i$ 和 $w_i$ 怎么求呢？

题干中给出了公式：

```
W_i = (a*i^5+b*i^2+c) mod d 
and   U_i = (e*i^5+f*i^3+g) mod h 
 (0 <= a <= 1,000,000,000; 0 <= b <= 1,000,000,000; 0 <= c <= 1,000,000,000; 0 <= e <= 
1,000,000,000; 0 <= f <= 1,000,000,000; 0 <= g <= 1,000,000,000; 10,000,000 <= d <= 1,000,000,000; 10,000,000 <= h <= 1,000,000,000).
```

嗯... ~~还不如不给。~~

再让我们用人话翻译一下：

>$w_i$ = ( a * $i^5$ + b * $i^2$ + c ) % d

>$u_i$ = ( e * $i^5$ + f * $i^3$ + g ) % h

瞬间就清醒了呢！

代码也就很好写啦！

但是还是有 __小坑点__ 的 ：
1. 循环的下标是从 0 开始，这点题目中没有给出来。
2. 一定一定一定要开 __longlong__ 。
3. 注意 N 的范围是 $N≤50000$ , 但是你要求的是 $3 * N$ 的数据！所以数组要不少于 1500000 。
4. 使用 C++ 库函数 pow 会出锅（起码我是 。

除此之外就没什么问题了。

#### 关于sort

由于我们使用结构体来存 $u_i$ 和 $w_i$ 。

所以我们要手写一个 cmd (很简单！

```cpp
bool cmd( node x , node y ){
    if( x.u != y.u )
        return x.u > y.u ;//如果有用度不等，将有用度大的放前面。
    else
        return x.w < y.w ;//如果有用度相等，将体重小的放前面。
}
```


第一遍我是用 pow 写的，只得了 ~~10~~ 分（丢人 。

代码如下：
```cpp
#include<bits/stdc++.h>

using namespace std ;

struct node{
    long long u ; long long w ;
}cow[1510000] ;

long long n , a , b , c , d , e , f , g , h , m ;

long long ans ;

bool cmd( node x , node y ){
    if( x.u != y.u )
        return x.u > y.u ;
    else
        return x.w < y.w ;
}

int main(){
    cin >> n >> a >> b >> c >> d >> e >> f >> g >> h >> m ;
    for( int i = 0 ; i < 3 * n ; i++ ){
        cow[i].w = ( a * pow( i , 5 ) + b * pow( i , 2 ) + c ) ;
        cow[i].w %= d ;
        cow[i].u = ( e * pow( i , 5 ) + f * pow( i , 3 ) + g ) ;
        cow[i].u %= h ;
        cout << cow[i].w << " " << cow[i].u << endl ;
    }
    sort( cow , cow + 3 * n , cmd ) ;
    for( int i = 0 ; i < n ; i++ ){
        // cout << cow[i].u << " " ;
        ans += cow[i].w ;
        ans %= m ;
    }
    cout << ans % m ;
    return 0 ;
}
```
然后。。。[(雾](https://www.luogu.com.cn/record/41004372)

经过深刻的思索，我认为是 pow 和 数组大小还有 int 把我 残害（bushi 了。

然后改成了这样：
```cpp
#include<bits/stdc++.h>

using namespace std ;

struct node{
    long long u ; long long w ;
}cow[1510000] ;

long long n , a , b , c , d , e , f , g , h , m ;

long long ans ;

bool cmd( node x , node y ){
    if( x.u != y.u )
        return x.u > y.u ;
    else
        return x.w < y.w ;
}

int main(){
    cin >> n >> a >> b >> c >> d >> e >> f >> g >> h >> m ;
    a %= d ;b %= d ; c %= d ; e %= h ; f %= h ; g %= h ;
    for( int i = 0 ; i < 3 * n ; i++ ){
        long long i1 = i % d , ii1 = i % h ;
        long long i2 = i1 * i % d , ii2 = ii1 * i % h ;
        long long i3 = i2 * i % d , ii3 = ii2 * i % h ;
        long long i4 = i3 * i % d , ii4 = ii3 * i % h ;
        long long i5 = i4 * i % d , ii5 = ii4 * i % h ;
        cow[i].w = ( a * i5 + b * i2 + c ) ;
        cow[i].w %= d ;
        cow[i].u = ( e * ii5 + f * ii3 + g ) ;
        cow[i].u %= h ;
    }
    sort( cow , cow + 3 * n , cmd ) ;
    for( int i = 0 ; i < n ; i++ ){
        ans += cow[i].w ;
        ans %= m ;
    }
    cout << ans % m ;
    return 0 ;
}
```

自认为做了比较多的优化。

一步取模，步步取模！

然后就A了！[虽然有点慢。](https://www.luogu.com.cn/record/41006768)

这道题考察的小细节相对于其他pj-来说还是多那么一些的。

关于 pow，能不用就不用。

撒花✿✿ヽ(°▽°)ノ✿。

求通过QAQ，这是我写的最多的一篇题解。

---

## 作者：Suiseiseki (赞：3)

很简单，按照题意算一遍

排序，优先u，再排w

u降序，w升序

前n个一定最优

#算时一定要从0下标开始

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct P{
    int w,u;
    friend bool operator <(P p,P q){
        if(p.u==q.u){
            return p.w<q.w;
        }
        return p.u>q.u;
    }
}array[3*500000+5];
int main(){
    int n,a,b,c,d,e,f,g,h,m;
     scanf("%d%d%d%d%d%d%d%d%d%d",&n,&a,&b,&c,&d,&e,&f,&g,&h,&m);
    long long i2,i3,i5;
    for(long long i=0;i<3*n;i++){//零下标
        i2=(i*i)%d;
        i3=(i2*i)%d;
        i5=((i3*i)%d*i)%d;
        array[i+1].w=((a*i5)%d+(b*i2)%d+c%d)%d;
        i2=(i*i)%h;
        i3=(i2*i)%h;
        i5=((i3*i)%h*i)%h;
        array[i+1].u=((e*i5)%h+(f*i3)%h+g)%h;
    }
    sort(array+1,array+1+3*n);
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=array[i].w;
        ans%=m;
    }
    printf("%lld\n",ans);
    return 0;
}
```
其实这题主要是题意理解，还有，要用**long long**


---

## 作者：FourteenObsidian (赞：1)

考试时以为很难但随便做过了的题……

按照题意模拟即可，不要想太多，sort可以过的。

按体重从小到大排序，若相同则有用度大的在前。

最后记得**开long long**,下标从**0**开始。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,c,d,e,f,g,h,m;
long long ans=0;
struct COW{
	long long w,u;
}a1[1500010];
inline long long cmp(COW x,COW y){
	if(x.u==y.u)
		return x.w<y.w;
	else
		return x.u>y.u;	
}
signed main(){
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d,&e,&f,&g,&h,&m);
	a%=d;
	b%=d;
	c%=d;
	e%=h;
	f%=h;
	g%=h;
	for(register long long i=0;i<3*n;++i){
		long long i1=i%d,i11=i%h;
		long long i2=(i1*i1)%d,i3=(i1*i2)%d,i5=(i2*i3)%d;
		long long i22=(i11*i11)%h,i33=(i11*i22)%h,i55=(i22*i33)%h;//怕pow超时，结果与楼上dalao意外地写得差不多
		a1[i].w=(((a*i5)%d+(b*i2)%d)%d+c)%d; 
		a1[i].u=(((e*i55)%h+(f*i33)%h)%h+g)%h; 
	}
	sort(a1,a1+(n*3),cmp);
	for(register long long i=0;i<n;++i){
		a1[i].w%=m;
		ans=(ans+a1[i].w)%m;//记得取模
	}
	printf("%lld\n",ans);
	return 0;
} 
```


---

## 作者：zy小可爱ღ (赞：1)

emmmmmmmm.......  
这题确实比较烦，花了半个多小时。。  
好，下面先把题目的思路理一下  
这题的读入和预处理我就不多说了，说一下排序的规则吧  
先比较有用度utility，大的在先，如果utility一样，再比较体重weight  
至于这题为啥写了这么长时间嘞，我还是把中途的错误全列出来，提醒新手吧  
1.变量要开longlong！！一定要记住  
2.一定要看清楚数据，数组要开到3倍n，还有。。看好有几个0。。  
3.w和u的取模是d和h，不是同一个  
4.就是排序规则了  
5.下标从0开始，因为每一个w和u跟i是有关的  
好了，错这么多，也没脸再列下去了（~~捂脸~~）  
下面上代码：
```cpp
#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<cmath>
#include<ctime>
#include<vector>
#include<bitset>
#include<memory>
#include<utility>
#include<cstdio>
#include<sstream>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>//。。。
using namespace std;

long long n,a,b,c,d,f,e,g,h,m,ans;
struct node{
	long long w,u;
}l[1500005];//记得开longlong

bool cmp(node a,node b){//排序规则，上面有提
	return (a.u==b.u?a.w<b.w:a.u>b.u);
}

int main(){
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d,&e,&f,&g,&h,&m);
	for(int i=0;i<3*n;i++){
		l[i].w=((a%d)*(((((i%d)*i%d)*i%d)*i%d)*i%d)+(b%d)*((i%d)*i%d)+(c%d))%d;//w是模d
		l[i].u=((e%h)*(((((i%h)*i%h)*i%h)*i%h)*i%h)+(f%h)*(((i%h)*i%h)*i%h)+(g%h))%h;//u是模h，要分开取模
	}
	sort(l,l+3*n,cmp);//排序
	for(int i=0;i<n;i++){
		ans+=l[i].w;
		ans%=m;//体重模m
	}
	printf("%lld\n",ans);//输出
	return 0;
}
/*
W_i = (a*i^5+b*i^2+c) mod d 
and   U_i = (e*i^5+f*i^3+g) mod h 这个是单纯的懒，不想到题目里看
*/
```
嗯嗯，看了一下楼下大佬的，其实觉得i2，i3，i5的设计蛮方便的，值得学习。。  
顺便留一下QQ号：2124652975，觉得题解哪里不好的欢迎骚扰~~

---

