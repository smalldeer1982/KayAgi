# [USACO10FEB] Chocolate Eating S

## 题目描述

Bessie has received N (1 <= N <= 50,000) chocolates from the bulls, but doesn't want to eat them too quickly, so she wants to plan out her chocolate eating schedule for the next D (1 <= D <= 50,000) days in order to maximize her minimum happiness level over the set of those days.

Bessie's happiness level is an integer that starts at 0 and halves (rounding down if necessary) over night as she sleeps. However, when she eats chocolate i, her happiness level increases by integer H\_i (1 <= H\_i <= 1,000,000). If she eats chocolates on a day, her happiness for that day is considered the happiness level after she eats the chocolates. Bessie insists that she eat the chocolates in the order that she received them.

If more than one optimal solution exists, print any one of them.

Consider a sequence of 5 chocolates to be eaten over a period of 5 days; they respectively bring happiness (10, 40, 13, 22, 7).

If Bessie eats the first chocolate (10 happiness) on the first day and then waits to eat the others, her happiness level is 10 after the first day.

Here is the complete schedule which turns out to maximize her minimum happiness:

Day  Wakeup happiness   Happiness from eating   Bedtime happiness 1            0                10+40                  50

2           25                 ---                   25

3           12                  13                   25

4           12                  22                   34

5           17                   7                   24

The minimum bedtime happiness is 24, which turns out to be the best Bessie can do.

Bessie 拿到了 $N$（$1 \leq N \leq 5\times 10 ^ 4$）块巧克力。她决定想个办法吃掉这些巧克力，使得它在吃巧克力的这段时间里，最不开心的一天尽可能的开心。并且一共吃 $D$（$1 \leq D \leq 5\times 10 ^ 4$）天。

每块巧克力有一个开心值 $H_i$（$1 \leq H_i \leq 10 ^ 6$），当某天你吃下那块巧克力时，你将获得那块巧克力的开心值。每一天的开心值是所有当天吃掉的巧克力的总开心值之和。每天晚上 Bessie 睡觉之后，它的开心值会减半。也就是说，比如昨天 Bessie 的开心值为 $50$，那么今天早上一醒来就会有 $25$ 点的开心值，舍去小数点后数字。另外，Bessie 还有一个怪癖，她喜欢按照巧克力本来的排列顺序吃。

Bessie 第一天的开心值为 $0$，求一个每天吃巧克力的方案，使得 Bessie 最不开心的一天尽可能的开心。


## 样例 #1

### 输入

```
5 5 
10 
40 
13 
22 
7 
```

### 输出

```
24 
1 
1 
3 
4 
5 
```

# 题解

## 作者：Yae_Sakura (赞：23)

~~吐槽：这题难度应该是黄色吧~~   

本题最大的坑点是记录食用日期 ( check函数不会太难写的 )    

我个人的想法是先后求解两个子问题   
1. 先二分求出最不开心那天的最大开心值ans
2. 再对ans重新check一遍以记录正确日期    

原因：借鉴楼上：“因为这个程序会不管三七二十一地把所有的日期记录下来，不管可行与否”，所以只有当求出最优解ans后，check记录的日期才会是正解


```cpp
#include<cstdio>
#define ll long long
//N<=50000 H_i<=1000000 累加起来将超过int范围
using namespace std;
const int N=50005;
inline ll read()
{
    ll s=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
    return s*f;
}
ll l,r,mid,ans;
ll n,d,a[N],day[N];
inline bool check(ll x)
{
    ll tot=0,sum=0;
    for(int i=1;i<=d;i++){
        sum=sum>>1;
        //">>1"表示除以2的一次方
        while(sum<x){
            sum+=a[++tot];
            if(tot>n) return false;
            //达不到检查值x便返回
            if(x&&x==ans) day[tot]=i;
            //if保证仅对ans记录日期
            //(当然可以去掉if，不过反复记录非正解很浪费)
        }
    }
    return true;
}
int main()
{
    n=read();d=read();
    for(int i=1;i<=n;i++)
    a[i]=read(),r+=a[i];
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    //二分最低开心值的区间
    printf("%lld\n",ans);
    check(ans);
    for(int i=1;i<=n;i++){
        if(day[i]) printf("%lld\n",day[i]);
        else printf("%lld\n",d);
        //最后一个小坑点：在最后一天要吃完剩下的全部巧克力
        //“剩下”即未标记过食用日期的巧克力
    }
    return 0;
}
```
 
评测结果：AC 68ms（不上不下的）

---

## 作者：青无常 (赞：17)

第一眼看这道题，嗯，最小值最大，二分搞起来。

我一开始是这么想的：r是总和，l是最小的H_i，在二分的时候，每次将mid作为每晚最少获得的开心值，check中，如果发现开心值不够就吃，开心值够就下一天，在下一天的时候，如果之前留下来的开心值大于mid就除2

然后就蒙了，样例都没过

原因在于，如果第一天留下来的开心值一直大于mid就要一直除

然后又懵了，错4个点，下载样例一看后：

excuse me?

最小的H_i是14，答案却是8，等等，开心值一直除的确有可能小于最小的H_i！！woc！！果断把l改成1

然后70。

再一次下载样例。

然后一看。

——————系统崩溃中，正在重新连接——————

好的那么我们继续，原来只有200天，我输出了208

于是果断将记录答案的数组中凡是只要超过最多天数的全改为最多天数。

来一波玄学尬舞，心中默数321

提交！
### 天 火 出 鞘 ！

A了

下面上~~塞西莉亚~~代码

```

#include<cstdio>
using namespace std;
int n,d,b[50002],c[50002];
long long a[50002],l,r,m,ans;
bool check(long long p){
	int s=0;
	long long sum=a[1];
	b[1]=1;
	for(int i=2;i<=n;++i){
		while(sum>=p){
			++s;
			sum=sum/2;
		}
		sum+=a[i];
		b[i]=s+1;
	}
	while(sum>=p){
		++s;
		sum=sum/2;
	}
	if(s>=d){
		for(int i=1;i<=n;++i){
			c[i]=b[i];
		}
		return 1;
	}
	return 0;
}
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		r+=a[i];
	}
	l=1;
	while(l<=r){
		m=(l+r)/2;
		if(check(m)) l=m+1,ans=m;
		else r=m-1;
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;++i){
		if(c[i]>d) c[i]=d;
		printf("%d\n",c[i]);
	}
	return 0;
}

```

$\color{green}\text{奥托大人，加油啊！}\ $

---

## 作者：philosopherchang (赞：9)

这题的思路就是二分，前面的dalao讲的已经很清楚了，。左边界先设为0，右边界就是所有巧克力开心值的累加和，二分出mid，如果开心值小于mid就吃，大于等于就不吃。

这题的实际难度其实就差不多是普及+/提高，但因为坑多的要命，所以难度被强行提到了提高+/省选。

先给出核心代码：

```cpp
int check(unsigned long long x)
{
	for(int i=1;i<=n;i++)
	day[i]=0;
	unsigned long long kx=0,j=0;
	for(int i=1;i<=d;i++)
	{
		kx=kx>>1;
		while(kx<x)
		{
			j++;
			kx+=qiaokeli[j];
			day[j]=i;
			if(j>n)
			{
				return 0;
			}
		}
	}
	return 1;
}
```

以上代码的意思和上面讲的相同，但是要在每次循环前加一个for来给day从新赋值为0，以避免输出时出现少一块巧克力或者多一块巧克力的尴尬情况。

接下来楼主会为大家盘点一下坑都是些什么。

先放一个10分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,qiaokeli[500001],day[500001],n,d,mid,ans;
int check(int x)
{
	for(int i=1;i<=n;i++)
	day[i]=0;
	long long kx=0,j=0;
	for(int i=1;i<=d;i++)
	{
		kx=kx>>1;
		while(kx<x)
		{
			j++;
			kx+=qiaokeli[j];
			day[j]=i;
			if(j>n)
			{
				return 0;
			}
		}
	}
	return 1;
}
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>qiaokeli[i];
		k+=qiaokeli[i];
	}
	long long l=0,r=k;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(!check(mid))
		{
			r=mid-1;
		}
		if(check(mid))
		{
			l=mid+1;
			ans=mid;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<day[i]<<endl;
	}
}
```

我们学校一个学长说,usaco有个习惯：第一个测试点永远是样例，所以这个代码也就过了个样例而已QAQ。

但看着挺对的是不是，但如果出几个稍微bt点的数据的话，你会发现最后输出的全是0，为什么？因为巧克力没吃完。

正如题中所给：“她决定想个办法吃掉这些巧克力”，说明要把所有巧克力吃完，那么之前没吃的巧克力都要在最后一天吃完。

于是我们就有了20分代码（只粘贴了较上一代码的改动部分）：

```cpp
	for(int i=1;i<=n;i++)
	{
		if(day[i]!=0)
		cout<<day[i]<<endl;
		else
		cout<<d<<endl;
	}
```

为什么是20分呢，因为数据范围，int不够，long long 好像也不够，所以我们用“unsigned long long”。

然后我们变成了30分（就改个数据范围，不粘代码了）。

最后，我们来看看100分（再不写100分我就要被打死了QAQ）（下面会讲下代码构成）：

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long k,qiaokeli[500001],day[500001],n,d,mid,ans;//k是计数器，一会儿会赋值给右边界，day[]是指当前这块巧克力是第几天吃的；
int check(unsigned long long x)//核心函数
{
	for(int i=1;i<=n;i++)
	day[i]=0;
	unsigned long long kx=0,j=0;
	for(int i=1;i<=d;i++)
	{
		kx=kx>>1;
		while(kx<x)
		{
			j++;
			kx+=qiaokeli[j];
			day[j]=i;
			if(j>n)
			{
				return 0;
			}
		}
	}
	return 1;
}
int main()
{
	std::ios::sync_with_stdio(false);//最好加上，小技巧，省时间（加上以后cin比scanf还快你信吗）。
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>qiaokeli[i];
		k+=qiaokeli[i];//累加开心值。
	}
	unsigned long long l=0,r=k;
	while(l<=r)
	{
		mid=(l+r)>>1;//”>>1”就相当于“/2”，这样写节省运行时间（给像1个月之前的我一样没见过的解释下，dalao勿喷QAQ）
		if(!check(mid))//改边界
		{
			r=mid-1;
		}
		if(check(mid))
		{
			l=mid+1;
			ans=mid;
		}
	}
	cout<<ans<<endl;
	check(ans);//看见没有，其实就改的这，再扫一遍ans。为什么呢，因为如果不扫一遍的话day[]的值可能还会停留在上一阶段。
	for(int i=1;i<=n;i++)//输出
	{
		if(day[i]!=0)
		cout<<day[i]<<endl;
		else
		cout<<d<<endl;
	}
	return 0;
}
```

100分完毕。
管理员大大求过，前两次都没过这次一定要过啊QwQ（抱佛脚）。


---

## 作者：funky_monkey (赞：5)

# P2985 题解

#### 这道题显然是二分答案，但是，有很多的坑点。
[题目传送门](https://www.luogu.org/problemnew/show/P2985)

二分答案一般运用于求最优解的题目中。其思路为：在答案可能成立的区间[L,R]中进行二分，每次将mid=(L+R)/2作为答案进行验证，如果不能成立，则寻找更劣的答案，否则二分寻找更优的答案。这样你就可以得到最优的答案。一般情况下，在验证答案是否成立时，需要用到贪心的思想。

有很多同学在写二分时，会出现死循环的现象。建议大家按照一种固定的格式做题，以避免这种情况。

这道题的注意点：

1、由于题目要求的是将吃巧克力的方法列举出来，所以很多同学会这样干：
```cpp
inline bool check(int x)
{
	int th=0,flag=0;//记录当前开心值和当前吃到了第flag块巧克力。
	for(ll i=1;i<=d;i++)
	{
		th/=2;
		while(th<x)
		{
			flag++;
			th+=a[flag];
			f[flag]=i;
			if(flag>n)
			{
				return false;
			}
		}
	}
	return true;
}

```
然鹅，这样是错误的。因为这个程序会不管三七二十一地把所有的答案记录下来，不管可行与否。

2、有很多同学非常可惜，他们注意了上面的一点，但还是有若干个点WA。

他们发现，提交上去的程序输出一开始没有错，但是到了后面几行，输出的就全都是0。

这是因为，巧克力必须要吃完。有可能最后一天还剩了几个巧克力没有吃，这个时候要把剩下的巧克力都设置为在最后一天吃的。

----------
下面贴代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN=50000+10,MAXM=300+10;//记录答案，其实只要开几十就够了。
ll n,d,a[MAXN],mx=0,ans,f[MAXN][MAXM],tf=0,as;

inline bool check(ll x)//判断答案是否成立
{
	ll th=0,flag=0; tf++;
	for(ll i=1;i<=d;i++)
	{
		th/=2;
		while(th<x)
		{
			flag++;
			th+=a[flag];
			f[flag][tf]=i;
			if(flag>n)
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
//	freopen("ceating.in","r",stdin);
//	freopen("ceating.out","w",stdout);
	scanf("%lld%lld",&n,&d);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		mx+=a[i];
	}
	ll L=0,R=mx,mid;
	while(L<=R)//二分答案
	{
		mid=(L+R)/2;
		if(check(mid)==false)
		{
			R=mid-1;
		}
		else
		{
			L=mid+1;
			ans=mid;//如果成立，将答案进行更新。
			as=tf;
		}
	}
	printf("%lld\n",ans);
	for(ll i=1;i<=n;i++)
	{
		if(f[i][as]==0)//如果巧克力还没有被吃，就设置为在最后一天吃。
		{
			printf("%lld\n",d);
		}
		else
		{
			printf("%lld\n",f[i][as]);
		}
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
```
#### 一片好心，望管理员大大采纳

---

## 作者：封禁用户 (赞：3)

**我们利用二分答案和贪心来解决这道题目。**

**当然要注意，数据大于longint，可以用int64，用qword也可。**

```cpp
var n,d,i,j:longint;
    sum,l,r,mid,ans,x:qword;
    a,b,c:array[1..50001]of qword;//a数组储存的是原始数据，b数组储存的是当前二分答案时的分配方案，c数组储存的是最后答案的分配方案。
    bo:boolean;//哨兵
begin
  readln(n,d);//读入数据
  for i:=1 to n do 
    begin
      readln(a[i]);
      r:=r+a[i];//将r算出来，r可以到所有值的和，因为可以在一天将所有巧克力都吃了。
    end;
  while l<=r do
    begin
      mid:=(l+r) div 2;//算出mid，就是当前我们尝试到的答案。
      bo:=true;//初始化。
      ans:=0;//记录高兴度。
      j:=1;//从第一个巧克力开始。
      for i:=1 to d do
        begin
          ans:=ans div 2;//根据题意，睡了觉，高兴度下降一半。
          while ans<mid do //当前的高兴度还未满足当前尝试的答案。
            begin
              ans:=ans+a[j];//加上当前巧克力的高兴度。
              b[j]:=i;//将当前的巧克力分配给当前一天。
              j:=j+1;//进入下一个巧克力。
              if j>n+1 then //巧克力若分配完了
                begin
                  bo:=false;//标记哨兵
                  break;//退出循环，再做下去不存在意义
                end;
            end;
          if not bo then break;
        end;
      if bo then//若为真，说明当前尝试的答案是可以被满足的。
        begin
          x:=mid;//记录答案
          for i:=j to n do b[i]:=d;//若最后的几块巧克力还没被吃掉，就都分配给最后一天。
          l:=mid+1;//尝试的答案可以变大
          for i:=1 to n do c[i]:=b[i];//将分配方案给答案
        end else r:=mid-1;
    end;
  writeln(x);
  for i:=1 to n do writeln(c[i]);
end.
```

---

## 作者：shiroi (赞：2)

### 题意简述
有 $n$ 块巧克力要吃 $d$ 天，并且只能按顺序吃。一块巧克力有一个开心值，一个人初始开心值为 $0$ ，且每天早上开心值变为原来的一半。问如何吃巧克力才能使开心值最小的一天开心值最大，输出方案。



### 题目分析
题目要求的是最小值最大，因此可以直接二分答案然后判定。

对于一个答案，如果开心值不够就不断的吃，输出方案时也可以用类似的方法进行贪心。

需要注意的是所有剩下的都要在最后一天吃完。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

typedef long long ll;
const int MAXN = 50005;
int h[MAXN],a[MAXN];
ll l,r,ans,n,d;

inline bool jud(ll x,bool f)
{
	ll tmp=0,cur=1;
	for(int i=1; i<=d; i++)
	{
		tmp>>=1;
		while(cur<=n && tmp<x)
		{
			tmp+=h[cur];
			if(f) a[cur]=i;
			cur++;
		}
		if(tmp<x)return 0;
	}
	if(f)
		for(int i=cur+1; i<=n; i++)
			a[cur]=d;
	return 1;
}

int main(int argc, char const *argv[])
{
	n=read(); d=read();
	for(int i=1; i<=n; i++)
		h[i]=read(),r+=h[i];
	while(l<=r)
	{
		ll mid=l+r>>1;
		if(jud(mid,0)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld\n",ans);
	jud(ans,1);
	for(int i=1; i<=n; i++)
	{
		if(!a[i]) printf("%lld\n",d);
		else printf("%d\n",a[i]);
	}
	return 0;
}
```

---

## 作者：VCVCVCFop_zz (赞：2)

bzoj上刷完才发现洛谷有这题。。

讲道理  这题坑点在long long难点在judge- -

思路应该只有二分

有一个要注意的楼下也说了，就是吃不完的要最后一天吃掉，原因在于题目要求的蜜汁字典序。。

下面贴代码


```cpp
 #include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long 
using namespace std;
ll l,r,ans;
int n,d;
int h[50005],a[50005];
bool jud(ll x,bool f)//判断是否可行
{
    ll tmp=0;
    int now=1;
    for(int i=1;i<=d;i++)
    {
        tmp>>=1;
        while(now<=n&&tmp<x)//贪心
        {
            tmp+=h[now];
            if(f)a[now]=i;
            now++;
        }
        if(tmp<x)return 0;
    }
    if(f)for(int i=now+1;i<=n;i++)a[now]=d;//全部最后吃
    return 1;
}
int main()
{
    scanf("%d%d",&n,&d); 
    for(int i=1;i<=n;i++)
        cin>>h[i],r+=h[i];
    while(l<=r)//二分
    {
        ll mid=(l+r)>>1;
        if(jud(mid,0))
        {
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    printf("%lld\n",ans);
    jud(ans,1);
    for(int i=1;i<=n;i++)
        if(!a[i])printf("%d\n",d);
        else printf("%d\n",a[i]);
    return 0;
}
```

---

## 作者：依依 (赞：2)

解：很明显，要求的是“不开心的一天尽可能的开心”

二分答案，设当前值为mid

判定：对于每一天，从前往后依次吃巧克力，

一旦超过了mid,立即停止这一天的进食

到最后剩下的都留给最后一天吃

貌似要开long long？  
[进去吧](http://www.cnblogs.com/adelalove/p/8665784.html)

---

## 作者：axs7384 (赞：0)

二分答案，贪心判定答案是否正确

```cpp
#include<iostream>
using namespace std;
int a[60000],i,j,k,m,n,ans[60000],c[60000];
long long sum,l,r,mid,xx;
bool b;
int main()
{
    cin>>m>>n;
    for(i=1;i<=m;i++)
        cin>>a[i];
    l=0;
    r=0;
    for (i=1;i<=m;i++)
        r=r+a[i];
    while(l<=r) //二分
    {
        mid=(l+r)>>1;
        j=1;
        sum=0;//开心值
        b=true;//判定是否可行
        for (i=1;i<=n;i++)
        {
            sum=sum>>1;
            while (sum<mid)
            {
                c[j]=i;
                sum=sum+a[j++];
                if (j>(m+1))
                {
                    b=false;
                    break;
                }
            }
            if (!b)
                break;
        }
        if (b)
        {
            for (;j<=m;j++) c[j]=n;//如果没吃完要在最后一天把剩下糖全部吃了
            xx=mid;
            l=mid+1;
            for (j=1;j<=m;j++)
                ans[j]=c[j];
        }
        else r=mid-1;
    }
    cout<<xx<<endl;
    for (i=1;i<=m;i++)
       cout<<ans[i]<<endl;
    return 0;
}
```

---

