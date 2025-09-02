# [USACO05DEC] Scales S

## 题目描述

约翰有一架用来称牛的体重的天平。与之配套的是 $ N \ ( 1 \leq N \leq 1000 ) $ 个已知质量的砝码（所有砝码质量的数值都在 $32$ 位带符号整数范围内）。

每次称牛时，他都把某头奶牛安置在天平的某一边，然后往天平另一边加砝码，直到天平平衡，于是此时砝码的总质量就是牛的质量（约翰不能把砝码放到奶牛的那边，因为奶牛不喜欢称体重，每当约翰把砝码放到她的蹄子底下，她就会尝试把砝码踢到约翰脸上）。

天平能承受的物体的质量不是无限的，当天平某一边物体的质量大于 $ C \ ( 1 \leq C \leq 2^{30} ) $ 时，天平就会被损坏。砝码按照它们质量的大小被排成一行。并且，这一行中从第 $3$ 个砝码开始，每个砝码的质量至少等于前面两个砝码（也就是质量比它小的砝码中质量最大的两个）的质量的和。

约翰想知道，用他所拥有的这些砝码以及这架天平，能称出的质量最大是多少。由于天平的最大承重能力为 $C$，他不能把所有砝码都放到天平上。

现在约翰告诉你每个砝码的质量，以及天平能承受的最大质量，你的任务是选出一些砝码，使它们的质量和在不压坏天平的前提下是所有组合中最大的。

## 样例 #1

### 输入

```
3 15
1
10
20
```

### 输出

```
11```

# 题解

## 作者：StudyingFather (赞：90)

乍一看，感觉和[装箱问题](/problemnew/show/P1049)一样，但是仔细看一下数据范围，就知道背包的做法是不可行的。

虽然题目中说 $ n \leq 1000 $ ，但考虑到“每个砝码的质量至少等于前面两个砝码的质量的和”这一条件，可以推出 $ n \leq 30 $ 。

在这么小的数据范围下，我们考虑用搜索的方法来解决这道题。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
long long sum[1005],a[1005],ans,n,c;
void dfs(int cur,long long x)
{
 if(x>c)return;
 if(sum[cur-1]+x<=c)
 //一个剪枝：如果前面那些砝码可以全部取走，那直接取走即可。
 {
  ans=max(ans,sum[cur-1]+x);
  return;
 }
 ans=max(ans,x);
 for(int i=1;i<cur;i++)
  dfs(i,x+a[i]);
 return;
}
int main()
{
 cin>>n>>c;
 for(int i=1;i<=n;i++)
 {
  cin>>a[i];
  sum[i]=sum[i-1]+a[i];
 }
 dfs(n+1,0);
 cout<<ans<<endl;
 return 0;
}
```

---

## 作者：代码练习生 (赞：41)

### 学习dfs主要就是学习剪枝：

+ **首先，既然是求最大，那么就应该从后往前搜索，能够避免很多不必要的递归；然后，弄一个一个前缀和数组，显然，当cur+b[index]即当前加上位置i的前缀和如果小于max时，就不用继续往下了，因为就算你把它们全部都选上也不会比max大，故是无用功，剪掉;至于cur+fama[index]>C则更不用说了，这应该是很容易想得到的。**

+ **由于要累计前缀和以及判断C，所以主要要用long long（long应该也行吧）**

+ **注意，斐波拉契大约到40多就大于2的30次幂了，所以题目给的N<=1000是唬人的，用不到这么多。**


```
#include<stdio.h>

long long  b[50],max=0,fama[50];
int N,C;

void
dfs(long long cur,int index){
    if(cur+b[index]<=max)
        return ;
    max=cur<max?max:cur;         //千万要把这一句放到下面这个if的上面，，，那一天，我可能比较饿，头晕眼花，结果因为这个找了一个小时，，，
    if(index==0)
        return ;
    if(cur+fama[index]<=C)   
    	dfs(cur+fama[index],index-1);
    dfs(cur,index-1);
}

int
main(){
    int i;
    
    scanf("%d %d",&N,&C);    
    i=1;
    while(i<=N){
        scanf("%lld ",fama+i);
        if(fama[i]>C)
            break;
        b[i]=b[i-1]+fama[i];
        i++;
    }
    dfs(0,i-1);
    printf("%lld",max);
    return 0;
}
```

---

## 作者：薛定谔的鱼 (赞：31)

这题作为一个紫题实在是过分了吧。。。
绿的了不起了。
——————————————————————————

看题第一眼，01背包无误。2min打好一交全屏紫色（所以这就是这题是紫色的原因233？）

re原因：即使压掉一维，dp数组的下标也有1e10 * 2 以上，不MLE就不错了。

肯定是动态规划一类的东西了。根据题目这一句话：这一行中从第3个砝码开始，每个砝码的质量至少等于前面两个砝码（也就是质量比它小的砝码中
质量最大的两个）的质量的和。是不是很像斐波那契？于是推出来：n的真实值其实也很小，大约在30左右吧。但是朴素搜索也会原地爆裂。

怎么剪枝呢？大约有三个剪枝。

#1：输入的时候，如果当前的重量已经大于限制了，就停止，把砝码总数重新定义。

#2：题目里所有的砝码都是单调递增的，所以不会出现去掉前面某一个砝码然后取后面一个来找到最大值（可能表述有些问题，或者我根本理解错了，欢迎指正）所以维护一个前缀和，如果这个能拿，就把前面的全都拿了（或者说当前的砝码一定大于等于前面所有的砝码重量和）

#3:因为找最大，所以从后往前搜索。

大概就是这样。


```cpp
#include<bits/stdc++.h>
//变量解释：a数组存题目给定值，b数组为前缀和数组，n为砝码数量，m为限制重量
using namespace std;
const int maxn=500005;
int n,m;
long long ans,a[maxn],b[maxn];
void dfs(int now,long long ma)//当前砝码序号和最大值
{
    if(ma+b[now]<=ans)//剪枝#2
    return;
    ans=max(ans,ma);
    for(int i=now;i;i--)//剪枝#3
    if(ma+a[i]<=m)
    dfs(i-1,ma+a[i]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        if(a[i]>m)
        {
        	n=i-1;//剪枝#1
        	break;
        }
        b[i]=b[i-1]+a[i];//剪枝#2
    }
    dfs(n,0);
    printf("%lld",ans);
    return 0;
}
```
应该就是这样吧。。。
（完）

---

## 作者：SweatBoy (赞：15)

斐波那契数列，很快就会超过2^30，N<40
------------
所以题目的（1<=n<=1000)是来吓人的
------------
所有题目变得简单一点了
------------




---------------------------好，进入正题-----------------------------

上代码

```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
const int N = 5101000;
int ans[N],n,C,m,a[N];
void DFS(int step,int lim,int w){
	if(step>lim){
		ans[m++]=w;
		return;
	}
	DFS(step+1,lim,w);//递归 
	DFS(step+1,lim,w+a[step]);//递归
}
int main() {
	scanf("%d%d",&n,&C);//输入，同cin>>n>>C; 
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);.//输入，同cin>>a[i]; 
	}
	DFS(1,n/2,0);
	int left =m;
	DFS(1+n/2,n,0);
	sort(ans,ans+left);//排序，前left-1 
	sort(ans+left,ans+m);//排序，从left到m-1 
	int res=0;
	int j=m-1;
	for(int i=0;i<left;i++){
		while(ans[i]+ans[j]>C&&j>left){
			j--;
		}
		if(ans[i]+ans[j]<=C){
			res=max(res,ans[i]+ans[j]);//c++自带的max 
		}
	}
	printf("%d\n",res);//输出，同cout << res << endl; 
	return 0;
}
```

希望各位同志能看懂！！！
------------

希望管理员给通过！！！
------------

谢谢各位！！！

---

## 作者：Plozia (赞：10)

更好的阅读体验->[传送门](https://blog.csdn.net/BWzhuzehao/article/details/104565196)

这道题是一道搜索题，一种思路是直接对每一个数做出选与不选的判断，时间复杂度 $O(2^n)$ 。在这种时间复杂度下，只能通过 $n \leq 30$ 的数据。

如何进行优化呢？以下是我的优化：

1. 改变搜索顺序。这一道题的输入数据是一个不下降序列，如果我们把小的数放在前面，而 $C$ 又比较大的话，前面的小数就会有很多的空间进行选择，极限数据下甚至可以卡死代码。为了避免这种情况，我在读入的时候从 $a_n$ 开始倒着读，这样 a 数组中就是一个不上升子序列，前面的大数很容易就因为 $C$ 的限制失去很多选择，节省了很多的时间。其中 a 数组是我存放数的数组。
2. 模拟可行性剪枝，我们不妨这么想：如果说**当前所选的数的总和**加上**后面的数的总和，即后缀和**都没有超过 $C$ 的话，那么当前的和就是在这种选择下可以达到的最大值。既然我们已经知道了最大值，并且题目所求的就是最大值，此时我们可以直接去更新答案， 然后退出这一层搜索。面对数很多的时候，这个剪枝会发挥出极大的威力。

在这些优化下，搜索的复杂度会变得很低。当然，如果您有什么更好的优化方法或剪枝，请私信我，感谢！

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000+10;
int n,c,a[MAXN];//n c 如题 a 存放数 
typedef long long LL;
LL sum[MAXN],ans;//sum 后缀和 ans 答案 
LL Max(LL fir,LL sec)
{
	return (fir>sec)?fir:sec;
}
void dfs(int k,int now)
{
	if(k>n)//选完了 
	{
		ans=Max((LL)now,ans); 
		return;
	}
	if(now+sum[k]<=c)//优化2 
	{
		ans=Max(now+sum[k],ans);
		return;
	}
	if(now+a[k]<=c) dfs(k+1,now+a[k]);
	dfs(k+1,now);
}
int main()
{
	scanf("%d %d",&n,&c);
	for(int i=n;i>=1;i--) scanf("%d",&a[i]);//优化1 
	for(int i=n;i>=1;i--) sum[i]=sum[i+1]+a[i];
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：hylong (赞：9)

这是道搜索题，用DFS可以跑到25ms甚至更快 ~~（当然，我没有跑到过）。~~
#### 阅读题目：
天平能承受的物体的质量不是无限的，当天平某一边物体的质量大于 $C ( 1 \leq C \leq 2^{30} )$时，天平就会被损坏。砝码按照它们质量的大小被排成一行。**并且，这一行中从第3个砝码开始，每个砝码的质量至少等于前面两个砝码（也就是质量比它小的砝码中质量最大的两个）的质量的和**。

想到了什么？（斐波那契数列）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()//求斐波那契数列代码
{
	long long i,j,k,n=47,a=1,b=1,c;
	for(i=3;i<=n;i++)
	{
	 c=a+b;
	 a=b;
	 b=c;
	}
	cout<<b<<endl;
	cout<<(long long)pow(2,30)<<endl;
	cout<<(long long)pow(2,31)<<endl;
	return 0;
}
```
* fib(47)=2971215073;
* $ 2^{30}$=1073741824;
* $ 2^{31}$=2147483648;
* 所以n最多为47，搜索就可以解决。
#### 得分历程:
1. 打了个搜索还打错了，得了10分。
2. 打了个对的暴搜，60分（及格了）
3. 用前缀和优化了一下，100分（25ms）
#### 代码：
60分代码（TLE3个点）
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[101],n,c,ans;
void dfs(long long xh,long long w)
{
	ans=max(ans,w);
	if(xh==0)
	 return ;
	if(w+a[xh]<=c)
	 dfs(xh-1,w+a[xh]);
	dfs(xh-1,w);
}
inline long long read()
{
	long long x=0;
	char b=getchar();
	while(b>'9' || b<'0')
	 b=getchar();
	while(b>='0' && b<='9')
	{
	 x=x*10+b-'0';
	 b=getchar();
	}
	return x;
}
int main()
{
	long long i,maxn=0;
	n=read();c=read();
	for(i=1;i<=n;i++)
	{
	 a[i]=read();
	 if(a[i]<c)
	  maxn=i;
	}
	dfs(maxn,0);
	cout<<ans<<endl;
	return 0;
}
```
100分代码（没开O2，25ms）
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[101],n,c,ans;
long long sum[101];//前缀和
void dfs(long long xh,long long w)
{
	ans=max(ans,w);
	if(xh==0)
	 return ;//边界
	if(sum[xh]+w<=c)
	{
	 ans=max(ans,sum[xh]+w);
	 return ;
	}//剪枝
	if(w+a[xh]<=c)//也算是一个剪枝吧
	 dfs(xh-1,w+a[xh]);
	dfs(xh-1,w);
}//深搜+剪枝
inline long long read()
{
	long long x=0;
	char b=getchar();
	while(b>'9' || b<'0')
	 b=getchar();
	while(b>='0' && b<='9')
	{
	 x=x*10+b-'0';
	 b=getchar();
	}
	return x;
}//玄学快读（加inline可能会更慢）
int main()
{
	long long i,maxn=0;
	n=read();c=read();
	for(i=1;i<=n;i++)
	{
	 a[i]=read();
	 sum[i]=sum[i-1]+a[i];//保存前缀和
	 if(a[i]<c)
	  maxn=i;
	}
	dfs(n,0);//其实相当于dfs(maxn,0)，之前maxn忘记删了，现在有懒得删了
	cout<<ans<<endl;//输出
	return 0;
}
```


---

## 作者：kfhkx (赞：7)

看到题解里没有Pascal，就来一波吧~

刚开始看到这一题的数据范围就被吓懵了 

1<=C<=2^30~~这还能做吗~~

不过再仔细看题就发现题目中有一句这样的话

- 并且，这一行中从第3个砝码开始，每个砝码的质量至少等于前面两个砝码（也就是质量比它小的砝码中质量最大的两个）的质量的和。

即a[3]>=a[2]+a[1]取等时

这不就是暗示我们是某Fibonacci数列吗！！！


在32位范围内不就只有不到50个数吗，发现这个之后这题就好办了~

## 即我们只要爆搜小于50次就能找到答案

### 补充一点小优化~
- 计算前缀和可以边读入边累加
- 特判一：如果读入的数恰好等于m就直接输出m并退出
- 特判二：如果读入的数大于了m就把他删去，并要:
1. 在前缀和里面去掉

2. a[i]:=0;

3. 因为读入是递增的所以直接退出循环并将n赋值为i+1

多的不用说了，下面就是爆搜（dfs）+小优化的代码

#### p5194.pas


------------

```pascal
var
        i:longint;
        n,m,ans:int64;//这里和下面几个地方一定要开int64，不然只有60分
        a,sum:array[0..10000] of int64;
function max(x,y:int64):int64;//自定义max函数
begin
        if x>y then exit(x) else exit(y);
end;
procedure dfs(x,y:int64);//爆搜开始
var
        i:longint;
begin
        if y>m then exit;//如果当前y>m那么就证明继续也找不到解，故直接exit掉
        if sum[x-1]+y<m then begin
                ans:=max(ans,sum[x-1]+y);
                exit;
        end;
        ans:=max(ans,y);
        for i:=1 to x-1 do dfs(i,a[i]+y);
        exit;
end;
begin
        read(n,m);
        for i:=1 to n do begin
                readln(a[i]);
                sum[i]:=sum[i-1]+a[i];//前缀和预处理
                if a[i]=m then begin//特判一
                        writeln(m);
                        exit;
                end else if a[i]>m then begin//特判二
                        a[i]:=0;
                        sum[i]:=sum[i]-a[i];//减去无用数据
                        break;
                end;
        end;
        n:=i+1;//特判二之后能减少一些没有用的数据
        dfs(n,0);
        writeln(ans);
end.
```




---

## 作者：Drinkkk (赞：4)

## $\text{Description}$

约翰有一架用来称牛的体重的天平。与之配套的是 $N$  ( $1 \leq N \leq 1000$ )个已知质量的砝码（所有砝码质量的数值都在 ``32`` 位带符号整数范围内）。

每次称牛时，他都把某头奶牛安置在天平的某一边，然后往天平另一边加砝码，直到天平平衡，于是此时砝码的总质量就是牛的质量（约翰不能把砝码放到奶牛的那边，因为奶牛不喜欢称体重，每当约翰把砝码放到她的蹄子底下，她就会尝试把砝码踢到约翰脸上）。

天平能承受的物体的质量不是无限的，当天平某一边物体的质量大于 $C$ ( $1 \leq C \leq 2^{30}$ ) 时，天平就会被损坏。砝码按照它们质量的大小被排成一行。并且，这一行中从第3个砝码开始，每个砝码的质量至少等于前面两个砝码（也就是质量比它小的砝码中质量最大的两个）的质量的和。

约翰想知道，用他所拥有的这些砝码以及这架天平，能称出的质量最大是多少。由于天平的最大承重能力为 $C$ ，他不能把所有砝码都放到天平上。

现在约翰告诉你每个砝码的质量，以及天平能承受的最大质量，你的任务是选出一些砝码，使它们的质量和在不压坏天平的前提下是所有组合中最大的。

## $\text{Solution}$

观察一下题目的限制。

> 并且，这一行中从第3个砝码开始，每个砝码的质量至少等于前面两个砝码（也就是质量比它小的砝码中质量最大的两个）的质量的和。

$Fib()?$

于是我们就可以得出

$$\text{第}\;i\;\text{个砝码的重量}>fib(i)$$

$$fib(1)=fib(2)=1$$

$$fib(n)=fib(n-1)+fib(n-2)\;\;\;|\;\;\;n>2$$

然后这道题的 $N$ 就可以成功缩小了。

然后就用最优化剪枝和前缀和维护一下就可以啦！

## $\text{Code}$

```cpp
#include <cstdio>
#include <cstdlib>
#include <cmath>
long long su[1000001],a[1000001],t[1000001];
long long ans=0,n=0,c=0;
long long max(long long x,long long y)
{
	return x>y?x:y;
}
void dfs(long long x,long long y)
{
	if(y+su[x]<=ans)
	{
		return ;
	}
	if(y>c)
	{
		return ;
	}
	ans=max(ans,y);
	if(x==0)
	{
		return ;
	}
	dfs(x-1,y+a[x]);
	dfs(x-1,y);
}
int main()
{
	scanf("%lld %lld",&n,&c);
	su[0]=0;
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		su[i]=su[i-1]+a[i];
	}
	while(a[n]>c)
	{
		n--;
	}
	dfs(n,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：muller (赞：4)

根据题目条件：

并且，这一行中从第3个砝码开始，每个砝码的质量至少等于前面两个砝码（也就是质量比它小的砝码中质量最大的两个）的质量的和。

然后max为1e9

我们可以证明有复杂度保证

有点玄学

所以我们可以直接爆搜

注意两个剪枝，可以适当提速

```
if (a[i] > C) {
    n = i - 1; break;
}
```
```cpp
if (res + s[l] <= ans) return;
```
比较显然吧

code:

```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define				MAXN				1010
LL a[MAXN], s[MAXN], C, ans = 0;
int n;
template <typename T> void read(T &x) {
	x = 0;int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-')f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
void work(register int l, LL res) {
	if (res + s[l] <= ans) return;
	ans = max(ans, res);
	for (register int i = l; i; i--)
		if (res + a[i] <= C) work(i - 1, res + a[i]); 
}
int main() {
	read(n); read(C);
	for (register int i = 1; i <= n; i++) {
		read(a[i]);
		if (a[i] > C) {
			n = i - 1; break;
		}
		s[i] = s[i - 1] + a[i];
	}
	work(n, 0);
	printf("%d\n", ans); 
	return 0;
}

```



---

