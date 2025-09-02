# [USACO13MAR] Poker Hands S

## 题目描述

Bessie and her friends are playing a unique version of poker involving a deck with N (1 <= N <= 100,000) different ranks, conveniently numbered 1..N (a normal deck has N = 13). In this game, there is only one type of hand the cows can play: one may choose a card labeled i and a card labeled j and play one card of every value from i to j.  This type of hand is called a "straight".

Bessie's hand currently holds a\_i cards of rank i (0 <= a\_i <= 100000). Help her find the minimum number of hands she must play to get rid of all her cards.


## 说明/提示

Bessie can play a straight from 1 to 5, a straight from 1 to 2, a straight from 4 to 5, two straights from 2 to 2, and a straight from 5 to 5, for a total of 6 rounds necessary to get rid of all her cards.


## 样例 #1

### 输入

```
5 
2 
4 
1 
2 
3 
```

### 输出

```
6 
```

# 题解

## 作者：k3v1n070828 (赞：47)

## 一道~~非常简单~~的贪心题

说下思路：

可以发现填平一个坑的同时，旁边的坑也会连带着被填一些。

∴旁边没填满的那个大坑会连带减少减少a[i]-a[i-1]的深度。

从第一个坑开始用循环：下一个坑是否能被连带着填满，如果不是的话，用ans记录每次的a[i]-a[i-1]。最后输出第一个坑的深度（无法被连带着填满）+ans(后面的坑需要的天数)。

用贪心做代码十分的简洁，唯一需要注意的一点是**需要开long long**。

话不多说，上代码：
```cpp
#include<cstdio>
using namespace std;
long long n,a[100005];//十年OI一场空，不开long long见祖宗
long long ans=0;
int main(){
    scanf("%lld",&n);//输入
    for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);//输入
    for(int i=2;i<=n;i++)
		if(a[i]>a[i-1]) ans+=a[i]-a[i-1];//如果旁边坑没被填满，那就增加a[i]-a[i-1]天
    printf("%lld\n",a[1]+ans);//输出
    return 0;
}
```

**蒟蒻的第一篇黄题题解，给蒟蒻点个赞呗**

最后，望管理员通过，谢谢！

---

## 作者：封禁用户 (赞：30)

**贪心**

**我们利用贪心求解，但要注意答案的类型要开到int64，否则会WA一个点～**

**我们先以第一个点为答案，然后记录这个点，与下一个点比较，如果下一个点比这个点多的话，答案就加上多的部分。最后直接输出答案即可。**

```cpp
var n,i,x,y:longint;
    s:int64;
begin
  readln(n);readln(s);x:=s;//读入第一个点，当作答案，记录下来。
  for i:=2 to n do
    begin
      readln(y);//读入下一个数据。
      if y>x then s:=s+y-x;//加上多的部分
      x:=y;
    end;
  writeln(s);
end.
```

---

## 作者：Plus_Ultra (赞：25)

刚学完 **差分** 就遇到了这道题

于是乎这道题迎刃而解。。。

- 我们统计一个差分数组， cf[i] = d[i] - d[i - 1].特别的， cf[0] = 0.

- 我们只需要像RMQ那样区间修改即可， 修改i--j区间（都减1）;只需把cf[i] - 1,  cf[j + 1] + 1就可以了;（差分数组性质）

- 为了得到最优解， cf[i]要为正数， cf[j + 1]要为负数;所以最后一正一负；

- 我们记正数总和为sum1，负数总和为 sum2,

- 配对为min(sum1, abs(sum2)）即可， 还有剩下的正（负）数， 即为abs(sum1 - abs(sum2）），单独记一下答案， 

- so最后的答案为min(sum1, abs(sum2)）+abs(sum1 -  abs(sum2））= max(sum1， abs（sum2）)；

下面是代码:
```cpp
#include<iostream>

using namespace std;

long long n,d[100005],ans,cf[100005]={0},sum1,sum2;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)  cin>>d[i];
    
	for(int i=1;i<=n;i++)
	{
		cf[i]=d[i]-d[i-1];
		if(cf[i]<0)  sum1-=cf[i];
		if(cf[i]>0)  sum2+=cf[i];
	} 
    
	cout<<max(sum1,sum2)<<endl;
    
   return 0;
}
```

---

## 作者：pomelo_nene (赞：12)

~~说实话，我也是三倍经验过来的~~

---

## 解法1.0——朴素递归

当初我看到这道题的时候，第一反应不是贪心，而是递归带一点贪心思想。

思路如下：

我们知道我们当然是一次出更多的牌是最好的。所以说，我们从$cards[1]$ 到 $cards[n]$进行递归，找到区间中的最小值，将区间里面的每一个数都减去他们。

思路简单，代码也很好打

```cpp
#include<cstdio>
#define MinToChange(a,b,x,i) a<b?b=a,x=i:b
long long cards[100005],tot,n;
inline void Poker(int l,int r)
{
	if(l<1 || r>n || r<l)	return ;//递归边界。我第一次没加r<l RE了
	int minn=999999999,x;//minn记录最小值，x记录最小值的位置
	for(int i=l;i<=r;++i)	MinToChange(cards[i],minn,x,i);
	for(int i=l;i<=r;++i)	cards[i]-=minn;	//从l到r每个地方减去最小值
	tot+=minn;//全局变量次数加上最小值
	Poker(l,x-1);Poker(x+1,r);//递归左边的和右边的
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i)	scanf("%lld",&cards[i]);
	Poker(1,n);
	printf("%lld",tot);//输出答案
	return 0;
}
```

期望得分：80

---

## 解法1.5——优化递归

我们T了两个点（T飞了) 原因是区间里面可能有很多很多数是和我们区间最小值一样的，出现了$0$，多次减去$0$，会有一些不必要的计算。

举个例子

$cards[1\text{ }to\text{ }n=5]=5,4,3,3,4$

最终程序里面的$minn$和$x$分别等于$3$和$3$

区间里面的每一个数减去$minn$之后：

$cards[1\text{ }to\text{ }n=5]=2,1,0,0,1$

我们再次进行递归

$cards[1\text{ }to\text{ }x-1=2]$是没问题的，但是$cards[x+1=3\text{ }to\text{ }n=5]$中，$minn=0,x=4$，又多进行了冗余的二次运算。

这样我们的优化就有方向了：

如果扫到$0$，就在循环中立刻递归并$return\text{ };$

```cpp
#include<cstdio>
#define MinToChange(a,b,x,i) a<b?b=a,x=i:b
long long cards[100005],tot,n;
inline void Poker(int l,int r)
{
	if(l<1 || r>n || r<l)	return ;//递归边界。我第一次没加r<l RE了
	int minn=999999999,x;//minn记录最小值，x记录最小值的位置
	for(int i=l;i<=r;++i)//枚举
	{
		if(!cards[i])//如果找到0了
		{
			Poker(l,i-1);Poker(i+1,r);//就只需要再找一次左边，一次右边就可以return了
			return ;
		}
		MinToChange(cards[i],minn,x,i);
	}
	for(int i=l;i<=r;++i)	cards[i]-=minn;	//从l到r每个地方减去最小值
	tot+=minn;//全局变量次数加上最小值
	Poker(l,x-1);Poker(x+1,r);//递归左边的和右边的
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i)	scanf("%lld",&cards[i]);
	Poker(1,n);
	printf("%lld",tot);//输出答案
	return 0;
}
```

预计得分：90

---

## 解法1.8——线段树递归

对于这个优化，大家应该会熟悉。线段树优化进行区间操作，我就不多阐述了。

预计得分：100

---

## 解法2.0——贪心

对于这道题的贪心证明，当时我在我们模拟赛的时候真的没想出来，而是用的解法1.5过了数据弱的模拟赛数据和另外的两倍经验

于是题解区里面已经有大佬证明了这个贪心是正确的，于是这道题就被解决了

贴上我的七行代码：

```cpp
#include<cstdio>
long long ans,n,a[100005];
int main() {
    scanf("%lld",&n);
	for(long long i=1;i<=n;++i)	scanf("%lld",&a[i]),ans+=a[i]>a[i-1]?a[i]-a[i-1]:0;
	return printf("%lld",ans),0;
}
```

预计得分：100

---

题外话：

这道题的贪心的气味还是很浓烈的哈～

但是细细一想，从最朴素的递归，一步一步优化，一直到线段树（其实里面的区间修改让线段树的气味也很浓烈）其实让我懂到了很多

是呀，贪心七行代码，想到了一分钟就可以打完，但是这两个小时的调试，让我有了更广阔的思维和更纯澈的理性

~~其实后来看到别人七行的AC代码差点晕在那儿~~

---

## 作者：Limit (赞：7)

本题有$O(N)$的优秀做法,但是因为在考场上不一定能想到,就来分享一种$O(N\log_2N)$的做法.虽然有点慢,但是可以过.
# 前置芝士
1. [线段树](https://baike.baidu.com/item/线段树/10983506?fr=aladdin):提高组及以上必备内容,不会的同学可以[学习一下](https://www.cnblogs.com/Sxy_Limit/p/12176423.html).
# 具体做法
~~只要会线段树就珂以了,是不是很简单.~~
先考虑贪心,连续的一定是一次去掉,不可能分成多次去取.

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200125172600906.jpg)

于是答案就是每一行连续的段数之和.
如图,第一行为$1$段,第二行$2$段,第三行$2$段,第四行为$1$段,所以答案就是$1+2+2+1=6$.然后再考虑怎么去算出每一行的段数,如果暴力去求肯定是会T的需要$O(N^2)$的时间复杂度,好像也没有什么其他的快速求法,于是再考虑分治,没一次将最下方的若干个完整的一行去掉后就将问题分为若干个子问题,暴力的方法就可以跑过更多的点了,但还是可能被一些特殊的数据卡掉.

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200125180735344.jpg)

如这样一个数据,每一次查找当前区间最低的高度需要$O(N)$的时间复杂度,最终的时间复杂度就会退化成$O(N^2)$.于是可以用线段树优化.时间复杂度就是$O(N\log_2N)$(~~大概~~).
# 代码
```cpp
#include<bits/stdc++.h>
#define rap(i,first,last) for(int i=first;i<=last;++i)
//线段树标准define
#define Lson (now<<1)
#define Rson (now<<1|1)
#define Middle ((left+right)>>1)
#define Left Lson,left,Middle
#define Right Rson,Middle+1,right
#define Now nowleft,nowright
using namespace std;
const int maxN=5e5+7;
const int INF=123123123;//一个极大值
int N;
int tree[maxN*4];
int arr[maxN];
void PushUp(int now)//查询区间最大值
{
	tree[now]=min(tree[Lson],tree[Rson]);
}
void Build(int now=1,int left=1,int right=N)//建树
{
	if(left==right)
	{
		tree[now]=arr[left];
		return;
	}
	Build(Left);
	Build(Right);
	PushUp(now);
}
//不需要修改
int Query(int nowleft,int nowright,int now=1,int left=1,int right=N)//查询区间最小值
{
	if(right<nowleft||nowright<left)return INF;
	if(nowleft<=left&&right<=nowright)
	{
		return tree[now];
	}
	return min(Query(Now,Left),Query(Now,Right));
}
int QueryPlace(int nowleft,int nowright,int m,int now=1,int left=1,int right=N)
//查询区间下一个最小值的位置,m为最小值
{
	if(right<nowleft||nowright<left)return INF;
	if(left==right)
	{
		if(tree[now]==m)
		return left;
		return INF;
	}
	int result=INF;
	if(tree[Lson]<=m)//如果左区间可能存在就先查找左区间
	{
		result=QueryPlace(Now,m,Left);
	}
	if(result!=INF)return result;//存在就返回
	return QueryPlace(Now,m,Right);//不存在查找右区间
}
long long get(int l,int r/*当前的区间*/,int delhigh/*当前减去的高度*/)
{
	if(l>r)return 0;
	if(l==r)return arr[l]-delhigh;//l=r时就为当前剩余高度
	int minhigh=Query(l,r);
	int now=l-1,place;
	if(arr[l]==minhigh)now++;//为了防止陷入死循环
	long long result=(minhigh-delhigh);//先将最下方可以取的部分直接取掉
	while(1)//通过线段树将每一段区间找出并继续加上答案
	{
		place=QueryPlace(now+1,r,minhigh);
		if(place==INF)break;//如果没有下一个位置就退出
		result+=get(now+1,place-1,minhigh);//有就加上答案
		now=place;
	}
	if(arr[r]==minhigh)//为了防止陷入死循环
	result+=get(now+1,r-1,minhigh);
	else
	result+=get(now+1,r,minhigh);
	return result;//返回答案
}
int main()
{
	scanf("%d",&N);//读入
	rap(i,1,N)
	scanf("%d",&arr[i]);
	Build();//建树
	printf("%lld\n",get(1,N,0));//输出
	return 0;
}
```

---

## 作者：石不转 (赞：6)

兄弟们，~~四倍经验的~~题解来了。


------------
归入正题，这题主要就是一个贪心。
是的，很弱智的贪心，然后呢很快乐。

NOIP 2018第一天我居然打线段树！虽说能过但是……我打错了！

回来之后以泪洗面。

好吧，这下我只能老实做人了，下面是贪心题解。
```cpp
// luogu-judger-enable-o2
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 100005 
using namespace std;
long long n,a[MAXN],s;//n是有多少个堆，a是储存
int main()
{
	long long i;
	cin>>n;
	for(i=1;i<n;i++)
	{
		cin>>a[i];
	}
	//sort(a+1,a+n+1);
    //在此想说些东西，sort这个，是我原来思路的错误，然后呢我就不打算删掉了。
    //我们来分析一下，为什么不能用sort，其实很简单。
    //如果你使用sort，那么凸凹不平的区间就会变得非常有序。
    //有序到爹妈（评测机）都认不得你，然后你就会发现，
    //啊，原来只需要修这几次就行了。
    //后来打出来之后发现换种算法其实sort也行，但是……那是另一个思路。
    //不说了哭去了。
	s=a[1];//首先需要这个，最起始的值，不加上……那每个答案都会少这个值。
    //你也可以理解为，a[1]-0.
	for(i=2;i<=n;i++)
	{
		if(a[i]>a[i-1])//重点！判断上一个是不是比当前这个小。
        //如果小，那么就开始贪心，贪心的过程中，我们会加上前一个和后一个的差值。
        //其实就是这样，很弱智很简单。
			s+=a[i]-a[i-1];//累加。
	}
	cout<<s;//输出，不用说了。
}
```
如果是大佬，那么加个读入优化或者输出优化都挺好。

哦哦哦程序中有个坑呀，请自己找一下，我就不搞了……

毕竟我们这也在严抓作弊，以身作则是不是呀/滑稽.

至于四倍的经验，自己去2018 NOIP第一题的讨论里面看吧……

我就是这样过来的。

反正我是跪了。嗯，蒟蒻此。

//by 石不转

---

## 作者：qwaszx (赞：5)

双倍经验[P1969积木大赛](https://www.luogu.org/problemnew/show/P1969)

首先把序列差分一下，$a[i]=w[i]-w[i-1]$，那么$[l,r]$区间减就变成$a[r+1]++,a[l]--$

然后最终要求a全变成0

而$\sum_1^{n+1} a_i=0$，每一个大于0的$a_i$后面一定存在一个小于0的$a_j$

显然l和r的选取是任意的，那么我们直接选择所有大于0的$a_i$使其减一，故答案就是差分后所有正数的和

区间问题转化成差分往往会大大简化问题

使用一些$Splay$之类的数据结构可以做到区间维护(翻转，区间加等)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,a[200000],f[200000];
long long ans;
int getin()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x;
}
int main()
{
	n=getin();
	for(int i=1;i<=n;i++)a[i]=getin(),f[i]=a[i]-a[i-1];
	for(int i=1;i<=n;i++)if(f[i]>0)ans+=f[i];
	cout<<ans<<endl;
}
```

---

## 作者：Y_B_Y (赞：4)

这种给一个序列的题目,可以先设法用**dp(或递归)**,于是我们设$h[i]$表示每堆牌的数量(当然,$h[0]=0$),设$f[i]$表示前$i$张牌最少几次打完;

我们先看一个例子

$13$

$5~4~3~ 2~ 1~ 1~ 0~ 9~ 5~ 8~ 7~ 6~ 4$



然后手算一下得:

$f[1]=5,f[2]=5,f[3]=5,f[4]=5,f[5]=5,f[6]=5,f[7]=5$

$f[8]=14,f[9]=14$

$f[10]=17,f[11]=17,f[12]=17,f[13]=17$

**所以答案就是$17$**,我们发现所有$f[i]$的取值分成了三种:$5,14,17$,再观察发现只有当$h[i]>[i-1]$时,$f[i]$的值相较$f[i-1]$会增加,而且增加的值恰好就是$h[i]-h[i-1]$,所以我们可以先猜测当$h[i]>[i-1]$时,$f[i]=f[i-1]+(h[i]-h[i-1])$,否则,$f[i]=f[i-1]$

证明:

我们发现对于一个不上升的序列(就是后一个数一定**小于等于**前一个数),如:$5~ 4~ 3~ 2~ 1~ 1~ 0$,其实打完所要的次数就是第一个数(从尾到头慢慢都化为0,比如先从第一张到第六张,再第一张到第五张,等等),所以$f[i]=f[i-1]$(值从子序列头到尾都一样是5),刚好这里都满足$h[i]>h[i-1]$,所以**猜测成立了一半**

再看像:$9~5~8$这样一个数列,显然这个数列有两个**最大不上升子序列**,$<9,5>$和$<8>$我们发现在使第一个不上升子序列的$5$消为$0$时,$5$顺便还可以拖$8$一把,使$8$变为$3$,于是$f[3]=f[2]+3=12$

刚好对应前面当$h[i]>[i-1]$时,$f[i]=f[i-1]+(h[i]-h[i-1])$

但是如果一个像$9~ 5~ 8~ 7~ 6$,这样的数列还成立吗,显然这个数列有两个最大不上升子序列,$<9,5>$和$<8,7,6>$,所以,$5$在托$8$一把时,还可以拖$7$和$6$一把,这样后面还是一个不上升子序列$<3,2,1>$,整个答案并没有被影响(原本应该是$f[5]=f[4]=f[3]=12$,现在还是一样)

~~这种方法勤俭节约不浪费,所以是最优的~~

### 上代码

标准版

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
#define ll long long
ll h[N],n,f[N];
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&h[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(h[i]>h[i-1]) f[i]=f[i-1]+(h[i]-h[i-1]);
		else f[i]=f[i-1];
	}
	cout<<f[n];
	return 0;
}
```

精简版

```cpp
#include<bits/stdc++.h>
long long n,h[2],f,z;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&h[1]),f+=std::max(z,h[1]-h[0]),h[0]=h[1];
	return printf("%lld",f),0;
}
```



---

## 作者：HuangBo (赞：4)

哪里需要什么线段树、DP……

估计一下数据范围，

好像int够用……

然而一开始我居然是90分

下载测试点发现
 
#  要开long long!

直接“模拟”(贪心的思想)

类似的题如——

### 均分纸牌(Noip2002) 

### P1969 积木大赛(NOIP2013)……

```cpp
/*
5 
2 
4 
1 
2 
3 

//6
*/
//贪心、模拟
#include <cstdio>
using namespace std;
long long n,a,l,ans;
int main()
{
	scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
		scanf("%lld",&a);
        if(a>l)ans+=(a-l);
        l=a;
    }
	printf("%lld",ans);
	return 0;
}
//实在不理解可以去做我说的2题，马上就理解了~0~
```

---

## 作者：时崎狂三老公 (赞：4)

```cpp
//思路就是模拟。
//步骤一.每次找一段连续不为0区间然后将整个区间全部减去这个区间的最小值，同时更新答案。
//步骤二.找到步骤一后，其区间出现了0的位置（即步骤一中其区间最小值的位置）；
//步骤三.将此位置左右两边当做一段不为0的区间重复步骤一。
//发现，此题我们需要更新一个区间最小值的信息，维护一个最小值编号，步骤三可以用递归进行。
//于是此题用线段树+dfs即可。 
//题解最不正常，代码也不简洁。 
#include<bits/stdc++.h>
#define maxn 100000*4+9
#define mid ((l+r)>>1)
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
using namespace std;
int m,n,pre,a[maxn],minn=maxn,lazy[maxn];
long long cnt,ans;
void cin_(int &x)
{
    int k=0,kk=1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            k=0,kk=1;
    char c;
    c=getchar();
    while(c>'9' || c<'0')
    {
        if(c=='-') kk=-1;
        c=getchar();
    }
    while(c>='0' && c<='9')
    {
        k=k*10+c-'0';
        c=getchar();
    }
        x=k*kk;
}                                                           //速读。 
struct node
{
    int w,num;
}min_[maxn];                                                //记录区间最小值的信息。 
void build(int rt,int l,int r)
{
        if(l==r) 
    {
        min_[rt].w=a[l];
        min_[rt].num=l;
        return ;
    }
        build(lson);
        build(rson);                                        //到这一行是建树过程。 
        if(min_[rt<<1].w>min_[rt<<1|1].w)
            {    
                min_[rt].w=min_[rt<<1|1].w;
                min_[rt].num=min_[rt<<1|1].num;    
            }
        else
            {
                min_[rt].w=min_[rt<<1].w;
                min_[rt].num=min_[rt<<1].num;
            }
}                                                          //初始化线段树区间最小值位置信息。 
void pushdown(int rt,int l,int r,int k)
{    
    lazy[rt]+=k;
    min_[rt].w-=k;
}                                                  
void update(int rt,int l,int r,int L,int R,int k)
{
    if(L<=l && r<=R)
        {
            min_[rt].w-=k;
            lazy[rt]+=k;
            return ;
        }
    if(lazy[rt])
        {
            pushdown(lson,lazy[rt]);
            pushdown(rson,lazy[rt]);
            lazy[rt]=0;
        }
    if(L<=mid) update(lson,L,R,k);
    if(mid+1<=R) update(rson,L,R,k);
    min_[rt].w=(min_[rt<<1].w,min_[rt<<1|1].w);
}                                               
void query(int rt,int l,int r,int L,int R)
{
        if(L<=l && r<=R)
    {
            if(cnt>min_[rt].w)
                {
                    cnt=min_[rt].w;
                    pre=min_[rt].num;    
                }    
            return ;
    }  if(lazy[rt])
            {
                pushdown(lson,lazy[rt]);
                pushdown(rson,lazy[rt]);
                lazy[rt]=0;
            }    
        if(L<=mid) query(lson,L,R);
        if(R>=mid+1) query(rson,L,R);
}                                                       //最标准的线段树模板打法。不过在更新的时候，同时要更新最小值位置信息。 
void dfs(int l,int r)                                   
{      
        if(l>r) return ;               
        query(1,1,m,l,r);
        update(1,1,m,l,r,cnt);
        ans+=cnt;
        cnt=maxn;
        int pre2=pre;
        dfs(l,pre-1);
        dfs(pre2+1,r);        
}                                                       //递归更新答案。 
int main()
{
    cin_(m);
    for(int i=1;i<=m;i++)
        cin_(a[i]);
    build(1,1,m);
    dfs(1,m);
    printf("%lld\n",ans);
    return 零;                                          //给个零，自己体会什么意思。 
}
```

---

## 作者：Pheasant_YQ (赞：2)

~~我摊牌了 我也是三倍经验过来的~~
~~还得copy提交三遍~~

本题的主要为使用贪心算法。
何为贪心？？？

在对问题求解时，总是做出在当前看来是最好的选择。也就是说，不从整体最优上加以考虑，它所做出的是在某种意义上的局部最优解。

以当前点（也就是第一个点）为单位，然后记录这个点，与下一个点做比较，如果下一个点比这个当前点大（先减再判断正负），如果为正，则加上大的部分，最后即可输出答案。

主代码如下

```
for (ll i = 0; i < n; ++ i) a [i] = read (),f [i] = a [i] - a [i - 1];
//如果下一个点比这个当前点大（先减再判断正负）
for (ll i = 0; i < n; ++ i) if (f [i] > 0) ans += f [i];
//如果为正，加上大的部分，最后即可输出答案。
```

个人建议数组不要开太小 不然可能WA几个点

~~第一次提交 f[i]开小一位 WA一个点 （丢人）~~

~~还有就是 不开 ll 爆祖宗~~

AC代码：

```
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n;
ll a [100010];
ll f [100010];
ll ans = 0;

int read(){
    int x = 0,f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
        f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
} 

void init(){
	n = read ();
	for (ll i = 0; i < n; ++ i) a [i] = read (),f [i] = a [i] - a [i - 1];
}

void solve(){
	for (ll i = 0; i < n; ++ i) if (f [i] > 0) ans += f [i];
    cout << ans << endl;
}

int main(){
	init();
    solve();
    return 0;
}
```

---

## 作者：Atmizz (赞：1)

## 这个题完全可以贪心AC
#### 吐槽一下：
数据较大，必须开**long long**，为此我可怜的WA了1个点，然后我就深思，不对啊，我咋在三倍经验的道路上走不动了呢！？

#### 提醒一下：
这个题如果看不懂的话，没关系，去**P1969积木大赛**和**P5019铺设道路**看一下，完全一个意思(~~我才不给传送门呢~~）。

#### 解题思路：
首先先设立一个变量 l=0，作为最左边的值，然后在每一次输入中更新。如果输入的当前数大于上一次的牌，就加上差值，小于的话就跳过，不管他。代码中有详细解释。

### code：
```cpp
/*此题与考试的铺设道路以及之前的积木大赛类似，思路相同*/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<stack>
#include<cstring>
#include<algorithm>
#include<iomanip>
using namespace std;				//n是牌数，h是每次输入的牌的张数 
long long n,h,l=0;					//l是最左边的牌，假设一开始它只有零张 
long long ans=0;					//ans是最终的答案 ,可能比较大，所以用long long 
int main()							
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&h);
		if(h>l)						//如果这一次的牌数大于上一次的牌数，那么加差值 
			ans+=h-l;
		l=h;						//更新上一次为现在的牌 
	}
	printf("%lld",ans);				//输出最后的答案 
	return 0;						//结束 
}
```

---

## 作者：Caishifeng666 (赞：0)

直接贪心，详情见代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,ans;
signed main(){	
	scanf("%lld",&n);scanf("%lld",&a);ans=a;
	for (int i=2;i<=n;i++){scanf("%lld",&b);ans+=max(b-a,(int)0);a=b;}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：乱世浮生 (赞：0)

本题一个坑点就是要开
### long long
其他没有什么难的，模拟就能水过吧。

代码：（code c）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long//long long一定要牢记
inline ll read(){//快读没意见吧……
    ll x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^'0');c=getchar();}
    return x*ff;
}
int main(){
    ll n,x,s=0,l=0;
    n=read();
    for(ll i=1;i<=n;i++){//从1到n枚举
        x=read();//输入
        if(x>l){
            s+=x-l;//答案s进行改变
        }
        l=x;//注意！这里一定要把l赋为上一次的x！！
    }
    printf("%lld\n",s);//打印
    return 0;
}
```
黄题。。

仔细想想，其实不难的……

---

