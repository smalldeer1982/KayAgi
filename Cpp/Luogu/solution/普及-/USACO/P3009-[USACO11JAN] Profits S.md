# [USACO11JAN] Profits S

## 题目描述

The cows have opened a new business, and Farmer John wants to see how well they are doing. The business has been running for N (1 <= N <= 100,000) days, and every day i the cows recorded their net profit P\_i (-1,000 <= P\_i <= 1,000).

Farmer John wants to find the largest total profit that the cows have made during any consecutive time period. (Note that a consecutive time period can range in length from one day through N days.) Help him by writing a program to calculate the largest sum of consecutive profits.


奶牛们开始了新的生意，它们的主人约翰想知道它们到底能做得多好。这笔生意已经做了N（1≤N≤100,000）天，每天奶牛们都会记录下这一天的利润Pi（-1,000≤Pi≤1,000）。


约翰想要找到奶牛们在连续的时间期间所获得的最大的总利润。（注：连续时间的周期长度范围从第一天到第N天）。


请你写一个计算最大利润的程序来帮助他。


## 说明/提示

The maximum sum is obtained by taking the sum from the second through the sixth number (4, 9, -2, -5, 8) => 14.

感谢@smartzzh 提供的翻译。


## 样例 #1

### 输入

```
7 
-3 
4 
9 
-2 
-5 
8 
-3 
```

### 输出

```
14 
```

# 题解

## 作者：QianianXY (赞：384)

看到题解区没什么简短的dp代码，处理过程有的地方复杂化了，于是忍不住来一发水文。

~~这是道线性dp~~（废话），所以可以边读入边输出。本题也不需要一个a数组，一个f数组，直接合成一个数组凑合着用。

a[i]表示前i个数的最大子段和。

转移方程：a[i] = max(a[i], a[i] + a[i - 1])

由于a[n]不一定是最大值，所以设变量ans随循环更新最大值。

最后注意处理全负数的情况就好了。

总而言之，一个循环丰衣足食。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100001], ans = -0x7fffffff;
int main()
{
	scanf("%d", &n);
	for (register int i = 1; i <= n; i++) 
	{
		scanf("%d", &a[i]);
		a[i] = max(a[i], a[i] + a[i - 1]);
		ans = max(a[i], ans);
	}
	printf("%d\n", ans);
	return 0;
}
```

~~小蒟蒻写得那么认真，就不给个赞吗QwQ~~ 算了，写得那么烂，就不好意思求赞了（~~还是给一个再走吧~~）...

---

## 作者：In_blue (赞：31)

本题其实不需要用到线性DP，在这里，介绍一种简单的贪心思想，思路如下：

+  首先，这是求区间最大值的题目，我们可以定义一个变量来保存一段区间的和，每一次将这个和与目前最大的值相比较，若是目前区间的值大于已知最大值，那么就更换。

+ 但是，如果此时区间的值小于零，那么我们可以想到，就算此时你再加上其他数，结果也是不会比之后的区间大，反而之后的区间会因此儿变小。所以，此时我们将这个区间的值归零，重新计数；

### 但是要注意!!!以下是重点！以下是重点！以下是重点！
#### ~~重要的事情说三遍~~

- 如果所有的利润都为负数，那么就要取最大的一个利润！！！即我们可以定义一个bool类型的变量，并保存下目前变量的最大值。若是没有出现>=0的数字，就输出此时的最大值。


--------------------完美的分割线----------------------

---

接下来是代码：
```cpp
#include<iostream>
using namespace std;
int n;
int a[100010];
int Max=-0xfffffff;
int t;
bool bol;
int num=-0x7fffffff;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		t+=a[i];
		if(t<0)t=0;
		Max=max(Max,t);
		if(a[i]>0)bol=1;
		num=max(num,a[i]);
	}
	if(bol)cout<<Max<<endl;
	else cout<<num<<endl;
	return 0;
}
```

##### 求管理员大大放行QAQ。

**~~来都来了，不点个赞再走嘛~~**

---

## 作者：午尘 (赞：15)

P3009的题目是道
 **最大子段和**
的模板啦~

------------

状态：f[i]表示以a[i]结尾的最大子段和 

------------

转移：

```cpp
f[i]=max(f[i-1]+a[i],a[i]);
```
对于每个f[i]，

可以从前面的那段加上a[i]得到（f[i-1]与a[i]是连续的），

也可以自己新起一个子段

------------
初始：f数组为0。

需要注意的是，

答案会有负数！！

所以：

```cpp
  ans=-1000000000;
```


------------
答案：把f[i]都扫一遍：

最大子段和可没规定一定要以哪个数为结尾啊~



------------


qwq放代码~

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,i,j,k,s,ans,a[100001],f[100001];
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	for (i=1;i<=n;i++)
	  f[i]=max(f[i-1]+a[i],a[i]);
	  ans=-1000000000;
	for (i=1;i<=n;i++) 
	   ans=max(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：Y15BeTa (赞：9)

（本文倒叙qvq）

# Step3 不用数组的优化！

* a[i]直接用x代替即可

* 我们可以在输入的同时维护temp变量，相当于dp[i]，求出dp[i]后随即更新ans，之后dp[i]就没必要存了，因为只对dp[i+1]有影响，循环到i+1时直接使temp=max(x,temp+x)即可。

# Step2 第三个点太坑了

> 5 -52 -65 -23 -24 -47 

> -23

所以我们一定要考虑到这种情况

* ans初值要足够小，不能是0

* WA了第三个点之后看看题才发现不能一天都不选，因此状态转移方程不可以误写为dp[i]=max(0,dp[i-1]+a[i])或temp=max(0,temp+x)

# Step1 dp思路

dp[i]表示以第i个数为结尾的最大子段和

转移时dp[i]=max(a[i],dp[i-1]+a[i])

a[i]指从这一个开始，dp[i-1]+x指接上一个，取这两种情况的较优者

# 附AC代码

```
#include<cstdio>
#include<algorithm>
using std::max;

int n,temp,ans=-2147483647;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		temp=max(temp+x,x);
		ans=max(ans,temp);
	}
	printf("%d\n",ans); 
}
```


---

## 作者：Victorique_De_Blois (赞：5)

这道题目让我们求最大的子段和。注意全是负数的情况下也是要输出一个最小的负数的。

$N \le 100,000$就告诉了我们暴力搜索会完蛋。所以我们选择动态规划。

动态规划的思想是`继续选亦或重新开始选择`。想到转移方程是比较难的。

我们 设♂$a_i$为第$i$个数，$f_i$为当前选到$i$的最大和。因此可以得出:

$$f_i=Max(f_i,f_{i-1}+a_i)$$

完整代码如下：

```cpp
#include<cstdio>
#define N 1000100
#define ll long long
//#define file
namespace Long
{
	inline ll max(ll a,ll b)
	{
	    return a>b?a:b; 
	}
	inline ll read()
	{
	    ll p=0,s=1;
	    char ch=getchar();
	    for(;ch<'0'||ch>'9';ch=getchar())
	        if(ch=='-')
	            s*=-1;
	    for(;ch<='9'&&ch>='0';ch=getchar())
	        p=p*10+ch-48;
	    return p*s;
	}
}
ll a[N],f[N];//f[i]表示选到的数列结尾下标为i时的最大和的一个状态 
int main()
{
	#ifdef file
		freopen("3009.in","r",stdin);
		freopen("3009.out","w",stdout);
	#endif
    ll n;
    n=Long::read();
    for(ll i=1;i<=n;i++)
        a[i]=Long::read(),f[i]=a[i];//首先将f数组初始化为本身 
    for(ll i=1;i<=n;i++)
        f[i]=Long::max(f[i],f[i-1]+a[i]);//从这里开始重新选择亦或继续选择 
    ll mx=f[1];
    for(ll i=2;i<=n;i++)
        mx=Long::max(f[i],mx);
    printf("%lld",mx); 
    return 0;
}
```

还有二分查找的代码：

```cpp
#include<cstdio>
#define N 1000100
//#define file
int a[N];
int max(int a,int b)
{
	return a>b?a:b;
}
int find(int l,int m)
{
    if(l==m)
        return a[l];
    int mid=(l+m)/2;
    int left=find(l,mid),right=find(mid+1,m);
    int Left=0,Right=0,ltmp=-2147483648,rtmp=-2147483648;
    for(int i=mid;i>=l;i--)
    {
        Left+=a[i];
        ltmp=max(Left,ltmp);
    }
    for(int i=mid+1;i<=m;i++)
    {
        Right+=a[i];
        rtmp=max(Right,rtmp);
    }
    left=max(left,ltmp+rtmp);
    return max(left,right);
}
int main()
{
	#ifdef file
		freopen("3009.in","r",stdin);
		freopen("3009.out","w",stdout);
	#endif
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    printf("%d",find(1,n));
    return 0;
}
```
相对dp来说会跑得慢一点,但是这种思路在考试的时候比较容易想到，并且也容易打出来。

提交记录：

![](https://s2.ax1x.com/2019/04/27/EujLSU.png)

$$Thanks!$$

---

## 作者：合451518 (赞：5)

真的很水．．．

这一题边读边处理。

ｍａｘ是最终输出最大值，ｔ是每次读入的结果，ｓ是选中一段利润综合。

每一次读入ｔ后ｉｎｃ（ｓ，ｔ）。

如果ｔ比ｍａｘ还大，替换ｍａｘ．

下一句话if s<0 then s:=0;是程序重点。

可以这样理解：

此时利润是负的，若后面加一个整数，这里的负数就为后面“拖后腿”，肯定比放弃前面的负利润直接加上后面的利润要小；

如果后面也是负的，那么结果肯定还是负的，做下去没有意义。

其实这一题１０００００的数据一点用都没有．．．

 
 
```cpp
var
 t,s,max,n,i:longint;
begin
 readln(n);
 max:=-maxlongint;
 s:=0;
 for i:=1 to n do begin
  readln(t);
  inc(s,t);
  if s>max then max:=s;
  if s<0 then s:=0;
 end;
 write(max);
end.
```

---

## 作者：Jelly_Goat (赞：3)

来一发线段树求最大子段和的标准姿势。  

~~智商不够，数据结构来凑~~  

首先我们让线段树节点记录一下几个值：  

区间和、区间最大连续前缀和、区间最大连续后缀和、最大连续子段和 ~~和左端点、右端点~~  

然后我们合并区间的信息只需要让区间最大子段和与各种信息取max就好了   
其中`各种信息`指的是`左子树的最大连续子段和`、`右子树的最大连续子段和`、`左子树的最大连续后缀和+右子树的最大连续前缀和`三个  

很明显我们query的时候由于要用到不止一个信息  

因此结构体节点是个好习惯  

代码的话......  
```cpp
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long int lli;
lli Max(int a,int b,int c)
{
    return max(max(a,b),c);
}
//线段树节点
struct seg
{
    int l, r;
    lli ldata, rdata, data, sum;
    inline int mid() { return (this->l + this->r) >> 1; }
    seg() { l = r = ldata = rdata = data = sum = 0; }
};
//线段树主体
seg tree[100011 << 2];
int n, m, a[100011];
//建树
void build_tree(int rt, int l, int r);
//更新
inline void update(int rt);
//区间查询
seg query(int rt, int l, int r);

int main()
{
#ifdef WIN32
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    scanf("%d", &n);
    for (register int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build_tree(1, 1, n);
    printf("%lld\n", query(1, 1, n).data);
    return 0;
}

inline void update(int rt)
{
    int lson = rt << 1, rson = lson | 1;
    tree[rt].sum = tree[lson].sum + tree[rson].sum;
    tree[rt].ldata = max(tree[lson].ldata, tree[lson].sum + tree[rson].ldata);
    tree[rt].rdata = max(tree[rson].rdata, tree[rson].sum + tree[lson].rdata);
    tree[rt].data = Max(tree[lson].data, tree[rson].data, tree[lson].rdata + tree[rson].ldata);
}

void build_tree(int rt, int l, int r)
{
    tree[rt].l = l, tree[rt].r = r;
    if (l == r)
    {
        tree[rt].sum = tree[rt].data = tree[rt].ldata = tree[rt].rdata = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(rt << 1, l, mid);
    build_tree(rt << 1 | 1, mid + 1, r);
    update(rt);
}

seg query(int rt, int l, int r)
{
    if (tree[rt].l == l && tree[rt].r == r)
    {
        return tree[rt];
    }
    int mid = (tree[rt].l + tree[rt].r) >> 1;
    if (r <= mid)
        return query(rt << 1, l, r);
    else if (l > mid)
        return query(rt << 1 | 1, l, r);
    else
    {
        seg ans, lson, rson;
        lson = query(rt << 1, l, mid);
        rson = query(rt << 1 | 1, mid + 1, r);
        ans.sum = lson.sum + rson.sum;
        ans.ldata = max(lson.ldata, lson.sum + rson.ldata);
        ans.rdata = max(rson.rdata, rson.sum + lson.rdata);
        ans.data = Max(lson.data, rson.data, lson.rdata + rson.ldata);
        return ans;
    }
}
```
应该写的还是挺清晰的  

~~三倍经验，A了这个还有P1115和GSS1~~

---

## 作者：littlegagaduck (赞：3)

~~作为dp一直很差的蒟蒻，想写篇题解加强记忆，大佬请自觉跳过。~~

这道题其实就是最大子段和的模板。

O(n)的循环，每一次比较存下这个位置的数，和前面数的和加上这个数，或许有疑问，这样写会不会sum(1~5)的解没有sum(3~5)的解优，而最后存下了sum(1~5)的解。

可以证明不会有这样的情况。如果sum(3~5)的解更优，那么在i=3时就会更新这个状态，i=3时就会因为a[3]>sum(1~3)而更新。

最后，注意负数的情况。

```cpp
#include<iostream>
using namespace std;
int a[200010]= {0},f[200010]= {0};
int main()
{
	int n,maxn=-999999999;
	cin>>n;
	for(int i=0;i<=n+1;i++)
	{
		f[i]=-999999999;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		f[i]=max(f[i-1]+a[i],a[i]);
		maxn=max(maxn,f[i]);
	}
	cout<<maxn<<endl;
	return 0;
}
```


---

## 作者：Dr_殇 (赞：3)

#这题就是一个简单的最大子段和，n=100000，很小的数，但如果死穷举就会爆。因为时间复杂度为O(n^2)会超时，但如果边读边做的话时间复杂度就只有O(n)了，不会超时。


##代码如下：





```cpp
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>//头文件准备
using namespace std;
int n,ans=-2147483647;//ans定义的初值要特别小，然后求最大值
int main(){
    freopen ("3009.in","r",stdin);
    freopen ("3009.out","w",stdout);
    scanf ("%d",&n);
    int b=0;
    for (int i=1;i<=n;i++){//边读边做
        int a;
        scanf ("%d",&a);
        if (b>0)b+=a;//如果b不大于0，就不加。因为无论a是正数还是负数，如果不大于零，相加肯定不会很大
        else b=a;
        ans=max(ans,b);//求b和ans的最大值
    }
    printf ("%d\n",ans);
        while (1);//反抄袭
    return 0;
}
```
#珍爱生命，拒绝抄袭！

---

## 作者：YueYang1235 (赞：1)

题解里似乎没有分治的做法？？？


------------
### 分治求解法

    考虑将数组从中间分为两个子数组，则最大子数组必然出现在以下三种情况之一：
   
1 完全位于左边的数组中。
 
2 完全位于右边的数组中。

3 跨越中点，包含左右数组中靠近中点的部分。

递归将左右子数组再分别分成两个数组，直到子数组中只含有一个元素，退出每层递归前，返回上面三种情况中的最大值。
    
贴个代码

```cpp
int work(int l, int r){
  int le,ri;//存放左边、右边最大和
  int ml=0,mr=0;//存放中间向左最大和，存放中间往右最大和
  int Le=0,Ri=0;//临时记录从中间向左、向右的和
  if(l==r){//只有一个元素的情况
    if(a[l]>0)return a[l];
    else return 0;
  }
  int mid=(l+r)/2;
  le=work(l,mid);//左边数组最大值 
  ri=work(mid+1,r);//右边数组最大值
	//横跨两边的最大和
  for(int i=mid;i>=l;i--){
    Le+=a[i];
    if(Le>ml)ml=Le;
  }
  for(int i=mid+1;i<=r;i++){
    Ri+=a[i];
    if(Ri>mr)mr=Ri;
  }
  return max(le,max(ri,ml+mr));
}
```


---

## 作者：光和热 (赞：1)

蒟蒻刚自学完$dp$，然后就找到了这道题，

## $First_-step$

把状态转移方程列出来：

$f[i]=max(f[i],f[i]+f[i-1])$

($f[i]$是前$i$个数的最大和)

注意:这里我是把$f$数组和记录一天的利润的数组合并一起用的


## $The_-second_-step$

打好代码，提交

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int n,ans;
int f[100000+10];
//混合数组
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>f[i];
        //输入每天能获得的利润
	}
    for(int i=1;i<=n;i++){
    	f[i]=max(f[i],f[i]+f[i-1]);
        //利用状态转移方程
		ans=max(f[i],ans);
        //求出ans的最大值
    }
	cout<<ans;
    //最后输出
	return 0;
}
```

然后，就可以$WA$啦！(差点气死)

## $The_-third_-step$

查错！

我先下载了样例$3$(就是我错了的)

打开发现是这样的:

$5-52-65-23-24-47$

~~草~~，有**负数**

那么我们再看看$ans$的赋值:

	int n,ans;
    //因为是在int main()外，所以默认是0
    
啊啊啊啊**要定负数！**

## $The_-fourth_-step$

提交改完的代码&&$AC:$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int n,ans=-2147483647;
//改过来了，下面的注释懒得删qwq
int f[100000+10];
//混合数组
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>f[i];
        //输入每天能获得的利润
	}
    for(int i=1;i<=n;i++){
    	f[i]=max(f[i],f[i]+f[i-1]);
        //利用状态转移方程
		ans=max(f[i],ans);
        //求出ans的最大值
    }
	cout<<ans;
    //最后输出
	return 0;
}
```

## $Last_-step$

~~不要脸地求赞~~

---

## 作者：doby (赞：1)

本题==p1115……

就是求最大子段和……

数据还比最大子段和少了一半……

```cpp
#include<iostream>
using namespace std;
int a,b=0,n,maxx=-2333333;
int maxn(int a,int b){if(a>b){return a;}else{return b;}}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;//输入
        if(b>0){b=b+a;}//取当前的最大和
        else{b=a;}
        maxx=maxn(maxx,b);//更新最大子段和
    }
    cout<<maxx;
    return 0;
}
```

---

## 作者：会打沙包的猫 (赞：1)

这道题和1115差不多呀

~~直接提交了1115的代码~~

~~其实就是裸的最大字段和~~

代码很简洁

~~三目运算符很快乐~~

~~我没有恶意压行~~

~~删除线真好玩~~
~~~cpp
#include <cstdio>
#include <iostream>
using namespace std;
int n,a,sum,minn,ans=-2e9;
int main()
{
    cin>>n;
    while(n--)
    {
        cin>>a;//输入
        sum+=a;
        ans=ans>(sum-minn)?ans:(sum-minn);//关键语句，取最大连续字段和
        minn=minn<sum?minn:sum;//判断是否更新
    }
    cout<<ans<<'\n';
    exit(0);
}
~~~

---

## 作者：jijidawang (赞：0)

- [博客体验](https://www.luogu.com.cn/blog/writeSTL/solution-p3009)

## 前置知识

- $1$：动态规划（dp）

> 用递推或记忆化搜索的形式把多阶段过程转化为一系列单阶段问题，利用各阶段之间的关系，逐个求解。

- $2$：一些数学符号

> 第一个：$\sum$
>
> > 第一种形式：$\sum\limits_{\textsf{变量=底值}}^{\textsf{顶值}}\textsf{式子}$
> >
> > 表示把变量从底值到顶值循环，求每个式子的值之和，相当于 `for (int 变量=底值;变量<=定值;变量++) ans+=式子;`
> >
> > ---
> > 
> > 第二种形式：$\sum\limits_{\textsf{变量的取值范围}}\textsf{式子}$
> >
> > 表示将 $i$ 取边取值范围，求每个式子的值的值之和，相当于 `while (变量在取值范围内){ans+=式子;变量遍历下一个值;}`
> 
> ----
> ----
> 第二个：$\max$
> 
> > 和 $\sum$ 用法一样，就是求和改成了求 $\max$。
> >
> > ---
> >
> > 顺便介绍几个类似的：
> >
> > | 编号 | 读法 | 写法 | 作用 |
> > | :---: | :---: | :---: | :---: | :---: |
> > | 1 | `sigma`($\sigma$) | $\sum$ `\sum` | 求和 |
> > | 2 | `min` | $\min$ `\min` | 取最小值 |
> > | 3 | `max` | $\max$ `\max` | 取最大值 |
> > | 4 | `pi`($\pi$)| $\prod$ `\prod` | 求积 |
> > 在 $\LaTeX$ 书写中行内模式 (一个美元符号) 中，在符号后加上 `\limits` 可以使上下居中，即 $\sum_{i=0}^n$ 变成 $\sum\limits_{i=0}^n$（居中的模式两个美元符号默认上下居中）


## 算法分析

> 在这个问题中，我们均设序列 $P$ 的下标是从 $0$ 开始的。

这个题目要求最大连续子串和，即找到一组 $l,r$ 使 $\sum\limits_{i=l}^rP_i$ 最大，所以答案让我们求的是 $\max\limits_{0\le l,r<n\;\;l,r\in\mathbb{N^*}}\left\{\sum\limits_{i=l}^rP_i\right\}$（~~然而列出这个式子并没有什么用~~）

### 1.暴力做法

我们可以暴力枚举 $l,r$，时间复杂度为 $\mathcal{O}(n^2)$。

---

### 2.暴力的优化

每次 $l,r$ 可以考虑二分求解，它本来就是 $l,r$ 正好还方便二分，排序一下保证单调性即可。

时间复杂度 $\mathcal O(\log^2 n)$

### 3.普通 dp 做法

我们设 $f(l,r)$ 为 $P_l\sim P_r$ 序列内的最优解。

如果原序列有一个子串 $P_l\sim P_r$ 是最优解，那么在一个包含于它的更大的子串 $P_x\sim P_y$（$x\le l$ 且 $r\le y$） 中，$f(l,r)$ 必然 $\le f(x,y)$，因为如果 $f(l,r)<f(x,y)$ ，又因为 $x\le l$ 且 $r\le y$，所以 $f(x,y)$ 里必须有一部分 $f(l,r)$，所以$f(l,r)$ 必然 $\le f(x,y)$。 

所以这个问题具有 **最优子问题性质**。

这个问题最优子问题性质，考虑 dp 求解。

转移方程分析如下：

我们用 $dp_i$ 代表序列中 $0\sim n-1$ 部分的最优解，也就是 $f(0,n-1)$。

- 如果不选这个元素，那么它的值就是 $dp_{i-1}$，因为第 $i$ 个元素不选所以不做贡献，则做贡献的只有前 $i-1$ 个。

- 如果选这个元素，那么它的贡献是它本身的贡献加上他前面的贡献，即 $dp_i+dp_{i-1}$。

并且注意这句话：
> 材料一：
>
> > $(-10^3 \le P_i \le 10^3)$
> 
> 材料二：
> 
> > 约翰想要找到奶牛们在连续的时间期间所获得的最大的总利润。（注：连续时间的周期长度范围从第一天到第 $n$ 天）。

这句话说明最大总利润 *必须取一些值*，如果没有注意这一点，就会被天天赔钱的数据卡掉。

取最优解，转移方程就得到了：

$$dp_i=\max\{dp_{i-1},dp_i+dp_{i-1}\}$$

答案为 $\max\limits_{0\le i<n}\{dp_i\}$，也就是所有 $dp_i$ 的最大值（$0\le i < n$）。

现在来考虑边界条件：

显然，$dp_0=P_0$，因为只有它一个元素。

其次，$dp_i\ge P_i$，因为如果 $0\sim i-1$ 区间内的最优解只含有 $P_i$ 一个元素，等号成立，因为 $P_i \in \{P_x\mid 0\le x <i-1,x\in\mathbb{N^*}\}$，即使有一个 $k$ 使 $P_i>P_k$，我们求的还是最优解，即 $dp_i\ge P_i>P_k$。

所以说 $dp_i$ 的初始值应为 $P_i$，因为这样可以保证 $dp_i\ge P_i$（注意状态转移方程中的 $dp_i+dp_{i-1}$ 可以体会）

此算法时间复杂度为 $\mathcal O(n)$，空间复杂度为 $\mathcal{O}(n)$（因为 dp 数组初始值和 $P$ 序列一样，可以合并，优化一半空间）

代码如下：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100001;
//the "dp" array=the input array.
int dp[N],n;
template<typename T>
inline T Max(T a,T b){return a<b?b:a;}
int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",dp+i);
	for (int i=1;i<n;i++) //dp
		dp[i]=Max(dp[i],dp[i]+dp[i-1]);
	int ans=-1001;        //mini ans=-1000.
	for (int i=0;i<n;i++)
		ans=Max(ans,dp[i]);
	printf("%d",ans);
	return 0;
}
```

---

### 4.dp 的优化

这个 dp 还是可以优化的。

可以轻易发现：dp 时 $dp_i$ 的取值只与 $dp_{i-1}$ 有关。

所以只需要存储 $dp_i$ 和 $dp_{i-1}$ 滚动使用空间即可。

取 $\max$ 也可以滚动进行，又优化了常数。

用这两点就可以将空间复杂度优化到 $\mathcal O(1)$，时间复杂度只优化了些常数（QAQ）。 

---

所以目前的最快时间复杂度是 $\mathcal{O}(n)$，可以轻松跑过 $10^5$ 的数据，但是空间用 $\mathcal O(n)$ 是可以过的，这也降低了这个题的难度。

只给第三种解答，因为前两种是~~基本~~能力，第四种只要明白了第三种就能轻松写出。

---

## 作者：Hokage (赞：0)

### 1.(~~这题的T3很坑，需要将ans开到很小~~)
### 2.话不多说，进入正题。
输入数组 w[i]，随后每一次维护 w[i] :

如果此时 w[i-1]是正数，就将 w[i]+=w[i-1]。

此时新的 w[i]一定大于旧的 w[i]，故选这个一定有助于达到最大值。

随后我们就可以找到每一次 w[i] 的最大值，记为ans。

（ans要一个很小的值）

ans记为答案。

```
#include<iostream>
#include<cstring>
using namespace std;

const int N=1000005;
int n;
int w[N];
int ans=-1000000;

int main()
{
    
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
		if(w[i-1]>0)
		{
			w[i]+=w[i-1];
		}
		ans=max(ans,w[i]);
 	}
	cout<<w[n]<<endl;
	return 0;
}
```

---

## 作者：林与向 (赞：0)

~~本蒟蒻终于自己独立完成了一道dp题~~  
我们会发现此题求的是最大子段和。  
后来看惹一下好像我的思路众大佬的题解的思路不太一样（有些怕怕）   

———————————————好了开始讲思路——————————————  
- 我们用结构体结构体定义数组 **f[i]**  表示：  
*以i结尾位置的子段上的信息* 像这样：
```cpp
struct Joe{
	int data;//该子段中各数的和
	int len;//该子段的长度
}f[100005];
```
那么我们要用这两个值来干什么呢
我们建立一个双重循环。  
每一次，我都从位置 i 向前拓展到位置 j ，如果f[i].data<f[i].dataf[j].data 则将f[j].data加进f[i].data中；与此同时，我还要将以j结尾的子段的长度加进以i结尾位置的子段的长度中。
~~（其实说白了就是吸引附属势力）~~  
我们要存储长度的目的是：***使我们每一次都就向前拓展一个子段而不仅仅是一个数***  
详见代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct lll{
	int data;
	int len;	
}f[100005];
inline int read(){
    int x=0,w=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;
    for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
    return x*w;
}
int main(){
	int n;
	int ans=0xc0c0c0c0;
	n=read();
	for(int i=1;i<=n;i++){
		f[i].data=read();
		f[i].len=1;
	}
	for(int i=1;i<=n;i++){
		int j=i-1;
		while(j>=1){
			if(f[i].data<f[i].data+f[j].data){
				f[i].data+=f[j].data;
				f[i].len+=f[j].len;
				j=j-f[j].len;
			}
			else break;
		}
		ans=max(f[i].data,ans);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：RainFestival (赞：0)

最大子段和，我用dp（二重循环超时，我没试过多少分，请大家不要尝试用二重循环解决）

[推荐1115，你会发现与本题惊人地相似](https://www.luogu.org/problemnew/show/P1115)

边读边做 x

设a[i]为最后一个是i的最大子段和

a[i]=max(x,a[i-1],x)//要么继承a[i-1],要么从x开始

每次用maxs扫一遍

下面是代码：

```pascal
var
  n,i,x,maxs:longint;
  a:array[0..10000005] of longint;
begin
  readln(n);
  maxs:=$80000000;
  for i:=1 to n do
    begin
      read(x);
      if a[i-1]+x>x then a[i]:=a[i-1]+x
                    else a[i]:=x;
      if a[i]>maxs then maxs:=a[i];
    end;
  writeln(maxs);
end.
```

谢谢管理员的审核与巨佬们的观赏！！！！

---

## 作者：A_konjac (赞：0)

****这道题不要用暴搜，会超时，本人的思路是从头到尾加一遍，如果加到负数就判断是不是比当前最大值大，大就更改数值，否则就加上****这个数

#include<bits/stdc++.h>//万能头文件

using namespace std；

```cpp
int n,a[100001],ans;
void input() {
    ans=-10000;//ans需要一个非常小的数值
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
}
void output() {
    printf("%c",ans);
}
void work() {
    int sum=0;
        for (int i=1; i<=n; i++){
            if (sum>0)sum+=a[i];//没加到负数
            else sum=a[i];//加到负数就重置sum
            ans=max(ans,sum);
    }
}
int main() {
    input();//输入
    work();//程序主体
    output();//输出
    return 0;
}
```

---

## 作者：户山香澄 (赞：0)

这题很水……

也许是最近被各种树蛊惑了，第一眼看到这道题竟然只想到用线段树做。

写到一半看了一眼题解，WTF?暴力？

好吧我还是写完了。

不过
#这不是一个模板

因为我没有写修改操作。

好吧我要放代码了








```cpp
#include<bits/stdc++.h>
using namespace std;
#define max3(x,y,z) max((x),max((y),(z)))
const int maxn=1e5 + 5;
struct Tree
{
    int val,maxall,all,pre,suf;
} tree[maxn<<2];
void build(int cur,int l,int r)
{
    if (l==r) 
    {
        cin>>tree[cur].all;
        tree[cur].maxall=tree[cur].pre=tree[cur].suf=tree[cur].all;
    }
    else
    {
        int mid=l+r>>1;
        build(cur<<1,l,mid);
        build(cur<<1|1,mid+1,r);
        tree[cur].all=tree[cur<<1].all+tree[cur<<1|1].all;
        tree[cur].pre=max(tree[cur<<1].pre,tree[cur<<1].all+tree[cur<<1|1].pre);
        tree[cur].suf=max(tree[cur<<1|1].suf,tree[cur<<1].suf+tree[cur<<1|1].all);
        tree[cur].maxall=max3(tree[cur<<1|1].maxall,tree[cur<<1].maxall,tree[cur<<1].suf+tree[cur<<1|1].pre);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    memset(tree,0,sizeof(tree));
    build(1,1,n);
    cout<<tree[1].maxall<<endl;
    return 0;
}
```

---

## 作者：PTC06 (赞：0)

这题很水啊..怎么会是大牛分站里面的呢...而且标签太吓人了，做起来却发现很水...

裸的最大字段和。和1115一毛一样。

最大子段和有很多方法。用分治，动规，以及最朴素的算法（本题会TLE）都行。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000000],b[1000000],i,ans;           //请忽视number_2，这是我刚开始编时用的一个变量，想删掉的，可不知为什么，一旦去掉就会有2个点RE，一个点TLE..
int main()
{
    cin>>n;              //读入N
    for (i=1;i<=n;i++)
    {
        cin>>a[i];           //输入
    }
    b[1]=a[1];           //初始化
    ans=a[1];            //初始化，当然这个地方你写ans=一个很小的负数，这样也没问题。
    for (i=2;i<=n;i++)              //从2开始循环，循环到N。
    {
        if (b[i-1]>0)
        {
            b[i]=b[i-1]+a[i];
        } else  b[i]=a[i];            //这个的作用就等于动态转移方程，应该不难理解吧。不懂的人就先跳过，我会在下面讲解。
        if (b[i]>ans) ans=b[i];             //找最大值
    } 
    cout<<ans;            //输出
 } 
```
这里是为刚才没看懂的人写的。
程序里的那条语句：

```cpp
        if (b[i-1]>0)
        {
            b[i]=b[i-1]+a[i];
        } else  b[i]=a[i];
```
正版：
if (b[i-1]+a[i]>a[i]) b[i]=b[i-1]+a[i]; else b[i]=a[i];

那么，什么情况下b[i-1]+a[i]会小于a[i]呢？

当然只有b[i-1]是负数的情况下。

那么问题也就解决了。只用判断b[i-1]是否小于0就可以判断出b[i]应该选哪个了。


下面附上一个更简洁明了的程序，这个更容易看懂。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000000],b[1000000],i,ans;
int main()
{
    cin>>n;
    for (i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    b[1]=a[1];
    ans=a[1];
    for (i=2;i<=n;i++)
    {
        if (b[i-1]+a[i]>a[i]) b[i]=b[i-1]+a[i]; else b[i]=a[i];
        if (b[i]>ans) ans=b[i];
    }
    cout<<ans;
}
```

---

## 作者：飞翔 (赞：0)

水水的最大子段和。

但是第二个点输出的是负数有点坑。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[100001],f[100001];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    f[1]=a[1];
    for (int i=2;i<=n;i++) f[i]=max(f[i-1]+a[i],a[i]);
    int ans=f[1];
    for (int i=2;i<=n;i++) ans=max(ans,f[i]);
    printf("%d",ans);
}
```

---

## 作者：fighter_OI (赞：0)

最大子段和。

用f[i]表示前i个数的最大子段和，其中第i个必选。

则
 f[i]=f[i-1]+a[i]                  f[i-1]>0

       a[i]                            f[i-1]<=0

可以发现只需保留f[i-1]即可

标程：

```cpp
uses math;
var n,maxn,s,k,i:longint;
begin
 read(n);
 s:=0;
 maxn:=-2147483640;
 for i:=1 to n do
  begin
   read(k);
   inc(s,k);
   maxn:=max(maxn,s);
   s:=max(s,0);
  end;
 write(maxn);
end.
```

---

