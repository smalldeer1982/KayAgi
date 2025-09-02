# [USACO05NOV] 奶牛玩杂技

## 题目背景

Farmer John 养了 $N$ 头牛，她们已经按 $1\sim N$ 依次编上了号。FJ 所不知道的是，他的所有牛都梦想着从农场逃走，去参加马戏团的演出。可奶牛们很快发现她们那笨拙的蹄子根本无法在钢丝或晃动的的秋千上站稳（她们还尝试过把自己装在大炮里发射出去，但可想而知，结果是悲惨的） 。最终，她们决定练习一种最简单的杂技：把所有牛都摞在一起， 比如说， 第一头牛站在第二头的身上， 同时第二头牛又站在第三头牛的身上...最底下的是第 $N$ 头牛。

## 题目描述

每头牛都有自己的体重以及力量，编号为 $i$ 的奶牛的体重为 $W_i$，力量为 $S_i$。

当某头牛身上站着另一些牛时它就会在一定程度上被压扁，我们不妨把它被压扁的程度叫做它的压扁指数。对于任意的牛，她的压扁指数等于摞在她上面的所有奶牛的总重（当然不包括她自己）减去它的力量。奶牛们按照一定的顺序摞在一起后， 她们的总压扁指数就是被压得最扁的那头奶牛的压扁指数。

你的任务就是帮助奶牛们找出一个摞在一起的顺序，使得总压扁指数最小。

## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 5\times 10^4$，$1 \le W_i \le 10^4$，$1 \le S_i \le 10^9$。

## 样例 #1

### 输入

```
3
10 3
2 5
3 3```

### 输出

```
2```

# 题解

## 作者：liuzitong (赞：62)

感觉其他dalao讲的不是很明白啊,我这样的蒟蒻看不懂啊.
在luogu这个dalao遍地的地方我蒟蒻看个题解也不明白,我为跟我同病相怜的蒟蒻写一篇吧

~~其实真是不太明白~~,大部分题解都是只说

体重大的在下面

力量大的在下面

(和)

没有证明啊....

----
设wa + sa > wb + sb且a与b相邻

### a在上面,b在下面时

那么a和b上面的牛总重为w

a的压扁指数为w - sa
b为w + wa - sb

因为wa + sa > wb + sb

那么wa - sb > wb - sa

因为wb >= 0,所以wa - sb > - sa

所以w + (wa - sb) > w - (sa),所以当a在上时,总压扁指数为w + wa - sb(不考虑上面的牛的压扁指数)

### b在上面,a在下面时

a -> w + wb - sa

b -> w - sb

因为wa + sa > wb + sb

所以wb - sa < wa - sb

又因为wa > 0

所以wb - sa < -sb

所以w + (wb - sa) < w + (-sb),所以当b在上时,总压扁指数为w - sb(不考虑上面的牛的压扁指数)

### 综上

当a在上时w + wa - sb

b在上时 w - sb

所以力量加体重大(w + s 大)的在下面比在上面更优

### 如果考虑上面的牛的话.
若上面牛的总压扁指数比a和b的大,那么交换了也不会变差(即无所谓).

如果不如a和b的大的话,就成了我说的这种情况

```cpp
#include<bits/stdc++.h>

#define AC 0

using namespace std;

inline int read(){int s=0,w=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();return s*w;}

struct po
{
	int w,s;
};
po a[50001];

bool cmp(po a,po b){
	return a.w + a.s < b.w + b.s;
}

int main(int argc, char const *argv[])
{
	int n;
	cin>>n;
	for(int i = 1;i <= n;++i){
		a[i].w = read();
		a[i].s = read();
	}
	sort(a + 1,a + 1 + n,cmp);//贪心排序
	int tot = 0,ans = -99999999;//一个数减另一个数,不排除负数的可能,ans要弄负值
	for(int i = 1;i <= n;++i){
		ans = max(ans,tot - a[i].s);
		tot += a[i].w;
	}
	cout<<ans<<endl;
	return AC;
}
```

给像我一样的蒟蒻的题解,dalao勿喷


---

## 作者：Tarsal (赞：32)

本蒟蒻又双叒叕被爆踩辣！

Solution：

我们先看数据，50000，那么O(n)或者O(n log(n))是可以过的,非严格O(n * sqrt(n))要卡卡常，说不定也可以过。

那么什么算法可以在解决这道题的同时来达到期望复杂度嘞？

```
你的任务就是帮助奶牛们找出一个摞在一起的顺序，使得总压扁指数最小。
```

看到这句是不是感觉明白了什么？

是的，~~很明显~~就是贪心！期望复杂度O(n);

那么贪心策略是什么？

因为我们要求总压扁指数最小，那么我们先看看总压扁指数是如何求的？

它是与奶牛的体重有关？

还是与奶牛的力量有个？


```
对于任意的牛，她的压扁指数等于摞在她上面的所有奶牛的总重（当然不包括她自己）减去它的力量
```

看到这句话是不是都懂了，它与奶牛的体重以及力量都有关！

而且，因为我们要越高的奶牛的体重越小且力量越小。

又因为，s和w直接的转化比率是1：1（就是一单位的体重可以用一单位的力量来支撑

那么我们的贪心策略就是按照s + w来排序；

上面是对问题的感性理解，

接下来，我来讲一讲如何证明为什么要越高的奶牛的体重越小且力量越小（~~显然啊~~：

假设x, y为相邻的奶牛，

且 Wx + Sx < Wy + Sy;

那么 Wx - Sy < Wy-Sx;

那么显然是右边的情况更优，窝们就应该把x放在上面，y在下面。

那么既然这里已经想通了，就很简单辣！

Code：

```cpp
#include<bits/stdc++.h>

using namespace std;

#define maxn 50010
#define inf 1000000000

#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)

struct node{
	int w, s, sum;
}e[maxn];//w,s如题，sum是w+s； 

int n, ans = -inf, now;//ans要赋极小值。 

bool cmp(node x, node y){
	return x.sum < y.sum;
}//按w+s排序。 

int main(){
	scanf("%d", &n);//输入 
	Rep(i, 1, n){
		scanf("%d%d", &e[i].w, &e[i].s);//输入 
		e[i].sum = e[i].w + e[i].s;//求出结构体排序的条件 
		now += e[i].w;//先全部加起来，方便从倒叙求解 
	}
	sort(e + 1, e + n + 1, cmp);//按照贪心方案，从小往大排序！ 
	Dep(i, n, 1){//记得要倒序！ 
		now -= e[i].w;//在减去w 
		ans = max(now - e[i].s, ans);//求出ans最大，此时使得总压扁指数最小 
	}
	printf("%d", ans);//输出 
	return 0;
}
```
~~Ps：请看懂再抄~~

---

## 作者：设计涉及社稷 (赞：18)

### 思路：构造相邻的两头牛，看能不能贪心，且看需要满足什么条件的时候才能贪心。

设有相邻的两头牛a,b，来讨论一下在满足什么条件的的情况下a放在b上面比b放在a上面更优：

设放在a,b上面的牛的总重为W

**i：a放在b上面**

a的压扁值：W-Sa

b的压扁值：W+Wa-Sb

**ii:b放在a上面**

a的压扁值：W+Wb-Sa

b的压扁值：W-Sb

要使a放在b上面比b放在a上面更优，

则
`max(W-Sa,W+Wa-Sb,)  < max(W+Wb-Sa,W-Sb);`
易证
`W-Sa < W+Wb-Sa,W-Sb<W+Wa-Sb;`

那就转化成了使

`W+Wa-Sb<W+Wb-Sa;`

->Wa+Sa < Wb+Sb

综上，当满足这个条件的时候，a放在b上面比b放在a上面更优；

那么我们以Wi+Si为关键字从小到大排序，（此时已经确立各奶牛的位置），那我们从上到下利用前缀和扫一遍最小的压扁值就好啦。

```
int n,m;
const int N=5e4+10;
struct nainiu{
	int s,w;
	bool operator < (const nainiu &rhs)const{
		return s+w<rhs.s+rhs.w;
	}
}cow[N];

int main(){
	rd(n);
	rep(i,1,n){
		rd(cow[i].w),rd(cow[i].s);
	}
	sort(cow+1,cow+n+1);
	int sum=0,ans=INT_MIN;
	rep(i,1,n){
		ans=max(ans,sum-cow[i].s);
		sum+=cow[i].w;
	}
	printf("%d",ans);
	return 0; 
}
```

---

## 作者：帅到报警 (赞：13)

### 这道题目真的真的非常有趣！！
## 前几天做过的国王の游戏跟这道题非常类似！
[国王的游戏走这里 -->](https://www.luogu.org/problemnew/show/P1080)

[本弱鸡的题解走这里 -->](https://www.luogu.org/blog/635forever/guo-wang-you-hu)

### 【题意分析】
首先，由于一只奶牛的压扁指数只取决于他自己的力量，所以前面的奶牛顺序并不影响后面奶牛的压扁指数，但会影响自己的压扁指数。然后便想到了贪心。但发现这样子并不能得出最优解。然后经过一番推导，便可以得知一只奶牛的质量与力量之和越大，就越要放到队伍后面。

**然后就开始了玄妙的数学证明时间！！**

### 【证明】
| …（设这一段的和为X1） |  …（设这一段的和为Y2）|
| :----------: | :----------: |
| L1 | R1 |
| …（设这一段的和为X2） | …（设这一段的和为Y2） |
| L2 |R2 |

##### 由上面这张表格可以知道这样的情况时：

第一个人所得的金币数为X1 - R1；

第二个人所得的金币数为X1 + L1 + X2 - R2；

所以最小值为 max(X1 - R11, X1 + L1 + X2 - R2)；



------------
 _**然后交换两个人的位置**_ 

------------
| …（这一段之和为X1） |  …（这一段乘积为Y2）|
| :----------: | :----------: |
| L2 | R2 |
| …（这一段之和为X2） | …（这一段之和为Y2） |
| L1 | R1 |

##### 由上面这张表格可以知道交换后的情况时：

第一个人所得的金币数为X1 + L2 + X2 - R1；

第二个人所得的金币数为X1 - R2；

所以此时最小值为max(X1 + L2 + X2 - R1, X1 - R2)；

### 综合上面两种情况：
如果变换之前的情况要优于变换之后的情况，那么

max(X1 - R11, X1 + L1 + X2 - R2) < max(X1 + L2 + X2 - R1, X1 - R2);

而X1 - R1 < X1 + L2 + X2 - R1 恒成立； 

X1 + L1 + X2 - R2 > X1 - R2恒成立；

所以上述条件成立时

必须有X1 + L1 + X2 - R2 < X1 + L2 + X2 - R1 恒成立；所以化简可得L1 + R1 < L2 + R2恒成立。

### 【核心代码】
这里还有一个很坑的地方，**必须要从第一头牛开始算**，不然就 WA 了！！！而且答案中有小于零的，所以定义 ans 的**初值时要很小很小的负数**！！！
```cpp
ans = -0x7fffff;
for(int i = 1; i <= n; i++)
{
	ans = _max(ans, num - cow[i].s);
	num += cow[i].w;
}
```

### 【正解】
```cpp
#include <bits/stdc++.h>
#define maxn 50010
using namespace std;

int n, ans, num;

int _max(int a, int b)
{
	return a > b ? a : b;
}

struct Cow{
	int w, s, sum;
	bool operator < (const Cow b) const{
		return sum < b.sum;
	}
}cow[maxn];

int main()
{
//	freopen("acrobat.in","r",stdin);
//	freopen("acrobat.out","w",stdout);
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> cow[i].w >> cow[i].s;
		cow[i].sum = cow[i].w + cow[i].s;
	}
	sort(cow + 1, cow + n + 1);
	ans = -0x7fffff;
	for(int i = 1; i <= n; i++)
	{
		ans = _max(ans, num - cow[i].s);
		num += cow[i].w;
	}
	cout << ans;
}
```

---

## 作者：EarthGiao (赞：10)

## 【前缀知识】   
贪心   
正常我们看到的贪心是只有一个变量的    
但是这道题目有两个      
奶牛的重量和奶牛的力气    
用贪心的思维来思考一下    
重量大的是不是应该放的更靠下？    
放的越靠下他的大重量影响的奶牛就越少    
所以 $W_i$ 越大就越要越往下放   
那么，奶牛力气越大的就越往下放是不是也是类似的道理？   
力气越大能够支持的重量越多，    
所以收重量的影响就越小，    
为了让最大值最小就应该让力气大的去承受更多的重量      
因为一个力气小的 $S_1$ 和一个 力气大的 $S_2$ 去承受同样的重量    
$W - S_1$ < $W - S_2$      
所以力气越大的就应该越往下放      
这个时候就有两个需要贪心的了    
## 【证明过程】   
假设只有两只奶牛，一只奶牛的重量为 $W_1$ ，力气为 $S_1$      
另一只奶牛的重量为 $W_2$ ,力气为 $S_2$     
如果前者在下      
压扁指数即为 $W_2 - S_1$    
如果后者在下     
压扁指数即为 $W_1 - S_2$    
假设前者在下更优     
即为前者在下压扁指数更小     
那么     
$W_2 - S_1 < W_1 - S_2$    
移项的    
$W_2 + S_2 < W_1 + S_1$    
这个时候是处于前者在下更优的情况下     
所以得出结论    
$W_i + S_i$越大就应该越往下放    

## 【引出】    
这只是有两只奶牛的情况    
可以通过这个类比出多个奶牛的情况所以     
这个结论适用      
 
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 

using namespace std;
const int Max = 50005;
struct node
{
	int w,s;
}a[Max];
bool cmp(const node x,const node y)
{
	return x.w + x.s < y.w + y.s;
}
int M = 0x7fffffff; 
int main()
{
	int n;
	cin >> n;
	for(int i = 1;i <= n;++ i)
		cin >> a[i].w >> a[i].s,M = min(M,a[i].s);//如果只有一个的话那就输出他的力气的负数所以这里需要找出最大的力气 
	M = -M;
	sort(a + 1,a + 1 + n,cmp);
	int tot = a[1].w;
	for(int i = 2;i <= n;++ i)
	{
		M = max(M,tot - a[i].s);
		tot += a[i].w;
	}
	cout << M << endl;
	return 0;
}
```

---

## 作者：Peter_Z (赞：10)

记每头牛的重量为w,力量为s,w+s=sum，存在结构体数组t中。

对每头牛的sum值进行排序，要证明sum值大的牛放在底下是最优解。

证明sum值最大的牛放在最下面最优即可。

证明：当sum值最大时，有两种可能：（注：这只是一种形象的说法）

1.若w值较大，则将其放在最下方，不让它压其他牛；

2.若s值较大，则将其放在最下方，承受其他牛的压力。

所以将sum值大的牛放在下方即可。

程序实现：

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
struct cow {        //奶牛的结构体数组 
    int w,s,sum;
} t[50002];
bool cmp(cow a,cow b) {    //根据sum排序 
    return a.sum<b.sum;
}
int max(int a,int b) {    //取出两数较大的数 
    return a>b?a:b;
}
int main() {
    int n,wt=0,min=-99999999;    //wt表示剩余牛总重，min表示总压扁指数的最小值 
```
/\*
注意：由于总压扁指数可能为负，

所以要先把min值调为负数，否则60分。

\*/
```cpp
    scanf("%d",&n);
    for(int i=1; i<=n; i++) {
        scanf("%d %d",&t[i].w,&t[i].s);
        t[i].sum=t[i].w+t[i].s;        //求和 
        wt+=t[i].w;            //求总重量 
    }
    sort(t+1,t+n+1,cmp);    //排序 
    for(int i=n; i>=1; i--) {
        wt-=t[i].w;            //剩余总重要减去此牛的重量 
        min=max(wt-t[i].s,min);    //计算这头牛的压扁值，若小于min则代替min 
    }
    printf("%d",min);
    return 0;
}
```

---

## 作者：陈昶旭 (赞：4)

解决方案：

1.贪心(不像是能用动归做)

2.以什么来贪心呢

3.重量，显然不行

4.力量也不行

5.猜测：与重量和力量都有关，再分析样例，发现是重量+力量

6.证明：设有a和b两头相邻的牛(a在下，b在上)

7.若Wa+Sa<Wb+Sb

8.交换a和b位置，设b上方牛总体重为W

9.a原：W+Wb-Sa   b原：W-sb(<W+Wb-Sa)   a改：W-Sa   b改：W+Wa-Sb(>W-Sa)

10.显然W+Wa-Sb<W+Wb-Sa

11.证毕

12.注意结果有可能是负数(不然60分)

13.AC
奉上代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct cow
{
    int w,s;
}c[50002];
long long ans=-2147483647,wt;
int n;
bool cmp(cow a,cow b)
{
    return a.w+a.s<b.w+b.s;
}
int main()
{
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>c[i].w>>c[i].s;
        wt+=c[i].w;
    }
    sort(c+1,c+n+1,cmp);
    for(int i=n; i>=1; i--)
    {
        wt-=c[i].w;
        ans=max(wt-c[i].s,ans);
    }
    cout<<ans;
    return 0;
} //为什么是普及/提高-

```

---

## 作者：qnickx (赞：3)

## 思路
一道冒泡型的贪心，按照$cow_w$与$cow_s$的和，即力量与重量的和从小到大排序，扫一遍即可得到最优答案。

贪心证明如下：

设能得到最优答案的奶牛集合

S={w1,w2,.......,$w_j$,......$w_i$.....}

其中$w_j$在$w_i$之前，$w_i$为能得到最优答案的位置

那么考虑互换$w_i$与$w_j$的位置，即可得到集合

$S_2$={w1,w2,.......,$w_i$,......$w_j$.....}

设原集合$S$中$w_i$之前的集合的体重和为$sum$,由于集合$S$比集合$S_2$更优，可以列出不等式： 

$sum-w_i+w_j-s_i<sum-s_j$

整理后得

$s_j+w_j<s_i+w_i$

因此得到和越小的应该在越前面。


## 代码


```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
using namespace std;
const int maxn=50005;
int sum,n,ans;
struct cow{
	int w;
	int s;
	int bj;
}sz[maxn];
inline bool cmp(cow cp1,cow cp2){
	return cp1.bj<cp2.bj;
}
int main(){
	ans=-999999990;
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)	scanf("%d%d",&sz[i].w,&sz[i].s),sz[i].bj=sz[i].w+sz[i].s;
	sort(sz+1,sz+n+1,cmp);
	for(register int i=1;i<=n;i++)	ans=max(ans,sum-sz[i].s),sum=sum+sz[i].w;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Partial (赞：3)

- 学习到贪心的证明方法之一，邻项交换。
- 在对于其他项不会对相邻两项产生影响的情况下可以使用。
- 其正确性可以使用归纳法证明 ~~其实我也不知道可以不可以~~ 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005;
struct node{
	int w,s;
}a[N];
int n,m;
bool cmp(node a,node b)
{
	return a.w+a.s<b.w+b.s;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&a[i].w,&a[i].s);
	}
	sort(a+1,a+n+1,cmp);
	int ans=-1e9,tmp=0;
	for(int i=1;i<=n;++i)
	{
		ans=max(ans,tmp-a[i].s);
		tmp+=a[i].w;
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：hylong (赞：3)

##### 题目背景：
  Farmer John 养了N(1<=N<=50,000)头牛，她们已经按1~N依次编上了号。FJ所不知道的是，他的所有牛都梦想着从农场逃走，去参加马戏团的演出。可奶牛们很快发现她们那笨拙的蹄子根本无法在钢丝或晃动的的秋千上站稳（她们还尝试过把自己装在大炮里发射出去，但可想而知，结果是悲惨的） 。最终，她们决定练习一种最简单的杂技：把所有牛都摞在一起， 比如说， 第一头牛站在第二头的身上， 同时第二头牛又站在第三头牛的身上...最底下的是第 N头牛。~~（为什么不现场表演制作牛轧糖？好吃又美味（滑稽））~~
##### 题目描述：
[题目](https://www.luogu.org/problem/P1842)

这道题用贪心解是很容易的。

但是！我们用什么来贪心？奶牛的体重，还是奶牛的力量？感觉都不对。再仔细看下题目，是不是感觉在哪看过？~~（如果你做过[P1080](https://www.luogu.org/problem/P1080) 的话）~~ 国王游戏了解一下？

好，言归正传，事实上我们应该用奶牛的体重和奶牛的力量之和来做贪心。
证明：实践出真知。~~（事实上我用小号把奶牛的体重和奶牛的力量之积，奶牛的体重和奶牛的力量之和都试了一次）~~
##### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct cow{
	int w;
	int s;
	int num;
	bool operator < (const cow &e)const
	{
	 return num>e.num;
	}//最低级的重载运算符（实质上就是自己写个cmp）
}a[50001];
int n,minn=-1000000,tot;//千万记住要把minn赋值为一个很小的负数，到时候60分可别怪我没提醒。
int read()
{
	int x=0,f=1;
	char b=getchar();
	while(b>'9' || b<'0')
	{
	 if(b=='-')
	  f=-1;
	 b=getchar();
	}
	while(b<='9' && b>='0')
	{
	 x=x*10+b-'0';
	 b=getchar();
	}
	return x*f;
}//快读（最好去学一学，万一有用呢？）
int main()
{
	int i,j;
	n=read();
	for(i=1;i<=n;i++)
	{
	 a[i].w=read();
	 a[i].s=read();
	 tot=tot+a[i].w;
	 a[i].num=a[i].w+a[i].s;
	}//贪心部分核心 之一（？？？）
	sort(a+1,a+n+1);//不会的贪心最好先排个序，说不定就有思路了。
	for(i=1;i<=n;i++)
	{
	 tot=tot-a[i].w;
	 minn=max(tot-a[i].s,minn);
	}//后期处理，贪心部分补充。
	printf("%d\n",minn);
	return 0;
}
```
注：
1. 写这篇博客之前，我突然忘记小号上试过乘积，又试了一遍，50分，五个五个排时WA恰好可以构成一个连通块，AC可以构成两个联通块......
2. （？？？）：就一个核心，哪来的之一？

---

## 作者：lzpclxf (赞：2)

[题面](https://www.luogu.org/problem/P1842)

 _没有新思路但是想和大家分享一下我对这道题几个很久都没明白的地方（当然也是别的题解木有的地方咯）就是一些小细节啦 希望可以帮助大家！_ 


**大家可不要一看是最小的最大值就去二分答案啊 要具体题目具体分析**， 这个题目的解题思路是贪心

我们只需算出每头牛的体重以及每头牛的承重能力的总和再来排序即可，  至于证明：

$1$.对于体重$w$来说， 我们肯定要让体重重的在下面， 来减小其他牛的压力

$2$.对于承重能力$s$来说我们肯定是要让承重能力大的在下面， 来承受其他牛的压力

综上$1$、$2$可得，让$w + s$的总和大的在下边即可。

快读真的很优秀， $oier$必备！
```cpp
long long read() {
	long long s = 0, w = 1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') w = -1;ch = getchar();}
	while(isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
	return s * w;
}
```
其实没必要开$long$ $long$ 的。我是一直60分以为自己开小了才改的$long$ $long$ 后来才知道原因， 下文中提到了， 关于压扁指数位置的问题。~~我太菜惹~~

下面就是我很久都没读懂的一个地方：

```cpp
for(int i = n; i >= 1; i--) 
sum -= e[i].w, ans = max(ans, sum - e[i].s);
```
解释一下这里的$sum$存储了所有牛的总体重，$ans$是我们要求的最下值， 我非常不明白， 都说了是最小值为啥还要取$max$??

$reason$: 

我们已经排好了序，并简单的证明了贪心思路无误， 那么可以确定在现在的牛的排列顺序中肯定有我们要的最小值！也就是说这群牛的压扁指数就是我们要的最小值！所以我们现在求出这群牛的压扁指数就好 而题目中也给出了求法。
######  奶牛们按照一定的顺序摞在一起后， 她们的总压扁指数就是被压得最扁的那头奶牛的压扁指数

注意：

### 压扁指数最大的并不一定在最底下！
所以才在$for$循环里找

The Last ：
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50005;
long long n, sum, ans = -0x3f3f3f3f;
struct node {
	int w, s, su;
}e[N];
long long read() {
	long long s = 0, w = 1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') w = -1;ch = getchar();}
	while(isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
	return s * w;
}
bool cmp(node x, node y) {
	return x.su < y.su;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) 
		e[i].w = read(), e[i].s = read(), e[i].su = e[i].s + e[i].w, sum += e[i].w;
	sort(e + 1, e + 1 + n, cmp);
	for(int i = n; i >= 1; i--) sum -= e[i].w, ans = max(ans, sum - e[i].s);
	printf("%lld\n", ans);
	return 0;
}
```
谢谢收看， 祝身体健康！


---

## 作者：24K纯AC (赞：1)

蒟蒻驾到！！~~~~~~~~~~~~

本题因该能看出来是贪心，有的大佬用动归写（太可怕了），

#### 小弟不才，带来一个利用排序贪心迅速AC的代码：
有些人第一眼看到，就立马重量or力量sort，毫无疑问，AK了
实际上，我们推理一下，就会明白排序规律：

（为了顺口，这里叫做风险值）

#### 一头奶牛的风险值，取决于上面的重量，和自身的力量，两个变量。

我们把问题简化，sort只需要考虑两头奶牛。

注意，前方高能！！！

### 考虑奶牛x和y时，只需要考虑x和y谁在上面所得的风险值最小，所以，可以这样写：
```cpp
bool cmp(const nn &x,const nn &y){
	return y.w-x.s>x.w-y.s;//按照奶牛x和y的先后顺序导致的风险度从小排序 
}
```

然后，按照当前序列模拟就ok了，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct nn{
	int w,s;
}a[50001];
long long int n,maxn;
bool cmp(const nn &x,const nn &y){
	return y.w-x.s>x.w-y.s;//按照奶牛x和y的先后顺序导致的风险度从小排序 
}
long long ans=-INT_MAX;//因为答案有可能是负数，所以max选举要赋值为-INT_MAX 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].w>>a[i].s;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		
		ans=max(ans,maxn-a[i].s);//最大的风险值选举 ，maxn是第i头奶牛上面的奶牛总重量 
		maxn+=a[i].w;
	}
cout<<ans;
return 0; 
}
```

祝大家早日AC！！！




---

## 作者：Pika_Q (赞：1)

这道题上来一看数据范围......暴力打不成qwq

然后就想贪心...

那把哪头牛放在最下面呢？力气大的还是体重大的呢？如果只把体重大的往下放的话万一它的力量太小那一定不是最优解；如果只按力气排序也是同理。

所以可以得出一个结论，最优解的状态一定同时与奶牛的重量和力气相关。这个时候收到国王游戏那道题的启发打表找规律（其实手算数据也可以），容易发现以奶牛的体重和力气之和排序即可得出最优解。（QWQ结论不会证）


------------
之前代码粘贴出锅了，现在重交一份QwQ


------------


```cpp
# pragma G++ optimize "O3"
# pragma GCC optimize "O3"
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int f=1,ANS=0; char ch;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        ANS=(ANS<<3)+(ANS<<1)+(ch^48);
        ch=getchar();
    }
    return f*ANS;
}
struct Cow
{
    int w,s;
}cow[50005];
inline bool cmp(Cow a,Cow b)
{
    return a.s+a.w>b.s+b.w;
}
int main()
{
	ios::sync_with_stdio(false);
    int n,hegt=0,maxx=-0x3f3f3f3f;
    n=read();
    for(register int i=1;i<=n;++i)
    {
        cow[i].w=read(),cow[i].s=read(),hegt+=cow[i].w;
    }
    sort(cow+1,cow+1+n,cmp);
    for(register int i=1;i<=n;i++)
    {
	    hegt-=cow[i].w;
    	maxx=max(maxx,hegt-cow[i].s);
    }
    cout<<maxx;
    return 0;
}
```


------------
完结撒fafa 
.❀.\(QwQ)/.❀.


------------


---

## 作者：hibiki (赞：1)

一个加法版非高精度版本的P1080，证明同理。假设第n头牛与第n+1头牛互换位置，设第n头牛以上的牛总重量为w,第n和第n+1头牛的重量为w1,w2,力气分别为s1,s2。所以若n在上则有压扁值n=w-s1,压扁值n+1=w+w1-s2。若n在下则有n=w+w2-s1，n+1=w-s2。因为w-s2肯定比w+w1-s2要小，而w-s1肯定比w+w2-s2要小，因此交换之后答案更优的条件就是w+w1-s2>w+w2-s1，移项之后得w1+s1>w2+s2。故以w+s为关键字对所有的数据排序，将w+s更大的放在下面。最后扫描整个数组得出答案即可。代码如下

```pascal
Type
    cow=record
        w,s:int64;
    end;
Var
    cows:array[1..50010] of cow;
    i,n:longint;
    temp,ans:int64;
Function max(a,b:int64):int64;
    begin
            if a>b then exit(a);
            exit(b);
    end;
procedure qsort(l,r:longint);
    var
        i,j,x:int64;
        y:cow;
    begin
        i:=l;
        j:=r;
        x:=cows[(l+r) div 2].w+cows[(l+r) div 2].s;
        repeat
            while cows[i].w+cows[i].s<x do inc(i);
            while x<cows[j].w+cows[j].s do dec(j);
            if not(i>j) then begin
                y:=cows[i];
                cows[i]:=cows[j];
                cows[j]:=y;
                inc(i);
                j:=j-1;
            end;
        until i>j;
        if l<j then qsort(l,j);
        if i<r then qsort(i,r);
     end;
Begin
    readln(n);
    for i:=1 to n do begin
        readln(cows[i].w,cows[i].s);
    end;
    qsort(1,n);
    ans:=-maxlongint;
    for i:=1 to n do begin
        ans:=max(temp-cows[i].s,ans);
        temp:=temp+cows[i].w;
    end;
    writeln(ans);
End.
```

---

