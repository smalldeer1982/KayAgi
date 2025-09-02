# Jeopardy!

## 题目描述

题意简述

“Jeopardy！”的决赛将有n问题，每个问题都有对应的得分ai，其中有m个问题可以选择不得分，而将现有总得分翻倍。你可以安排关卡的通过顺序和策略，求最大得分。

## 样例 #1

### 输入

```
4 1
1 3 7 5
3
```

### 输出

```
18
```

## 样例 #2

### 输入

```
3 2
10 3 8
2 3
```

### 输出

```
40
```

## 样例 #3

### 输入

```
2 2
100 200
1 2
```

### 输出

```
400
```

# 题解

## 作者：muyang_233 (赞：6)

[原题传送门](https://www.luogu.com.cn/problemnew/show/CF413C)  

贪心算法。  

首先考虑贪心策略，其实非常好想。  
令前 $i$ 个数所得到的 **最大** 得分为 $ans$ ，  
对于 **不能** 进行翻倍的位置 $i$ ， $ans$ **直接加上** $a_i$ 就可以了。  
对于 **能** 进行翻倍的位置 $i$ ， **分别** 考虑是否进行翻倍的两种情况，翻倍则为 $ans*2$ ，不翻倍则为 $ans+a_i$ ，于是此时即为 $ans=max(ans*2,ans+a_i)$ 。

再考虑 **排序** 策略，必然是 **能翻倍** 的那些位置在排序之后放在 **后** 面，然后对于是否能翻倍的性质相同的位置，进行 **降** 序排列。  
为什么能翻倍的一定在最后面呢？  
我们举一个 $m=1$ 的例子。  
```
4 1
5 7 3 1
3
```
如果按照上文给出的排序方法，我们得到序列 $\text{7 5 1 3}$ ，再按照贪心策略， $ans=(7+5+1)*2=26$ 。  
而如果能翻倍的不在最后，比如我们得到序列 $\text{7 5 3 1}$ ，再按照贪心策略， $ans=(7+5)*2+1=25$ ，答案就不正确了。  

最后，为了方便排序，我们用一个 **结构体** 存储每一个 $i$ 的 $a$ 值以及它是否能够进行翻倍，如下：  
```cpp
struct node{
	int a;//a值
	bool ok;//是否能够进行翻倍，为true即可以
}
```
根据上述排序策略写出的 $\text{cmp}$ 函数就如下：  
```cpp
bool cmp(node _1,node _2){
	if (_1.ok!=_2.ok) return _1.ok<_2.ok; //能翻倍的ok=true即1，故按ok升序就是把能够进行翻倍的往后放
	return _1.a>_2.a;//对于ok性质相同的，按a值从大到小排序
}
```
最后要注意的是，由于 $a_i \le 10^7,m \le min(n,30)$ ，$ans$ 最大可能会达到 $10^7*2^{30}$ ，显然超过 $int$ 最大值，需要开 $long\ long$ 。  

AC代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
struct node{
	int a;//a值
	bool ok;//是否能够进行翻倍，为true即可以
}qaq[105];
ll ans;
int n,m;
bool cmp(node _1,node _2){
	if (_1.ok!=_2.ok) return _1.ok<_2.ok;//能翻倍的ok=true即1，故按ok升序就是把能够进行翻倍的往后放
	return _1.a>_2.a;//对于ok性质相同的，按a值从大到小排序
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%d",&qaq[i].a);
	}
	for (int i=1;i<=m;i++){
		int b;
		scanf("%d",&b);
		qaq[b].ok=true;//能进行翻倍的ok标记为true
	}
	sort(qaq+1,qaq+n+1,cmp);
	for (int i=1;i<=n-m;i++){//不能翻倍的
		ans+=qaq[i].a;//直接加
	}
	for (int i=n-m+1;i<=n;i++){//能翻倍的 
		if (ans*2>ans+qaq[i].a){//翻倍大
			ans*=2;
		}
		else{//直接加大
			ans+=qaq[i].a;
		}
	}
	printf("%lld",ans);//输出
	return 0;
}

```
~~这里有AC代码哦，但我相信你不会抄题解的！~~

---

## 作者：sinsop90 (赞：5)

我们考虑一个贪心策略：

我们会发现, 对于那些可以翻倍的东西, 我们改变不了 $A_i$, 那我们就可以改变对 $A_i$ 进行操作时的值啊!

因此我们想到先将不能翻倍的所有数加起来, 接着再对那些可以翻倍的进行操作

对于那些可以进行翻倍的 $A_i$ 进行操作

我们再次考虑贪心:

如果我们从可以翻倍的 $A_i$ 中小的进行操作, 到了 $A_i$ 中较大的, 可以占到的便宜自然小了

因而我们将可以翻倍的 $A_i$ 从大到小排序一次进行操作

自然如果我们的得分小于当前可以翻倍的 $A_i$ 我们肯定选择加上 $A_i$ 而不是翻倍

因而有了如下代码:

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int mps[10005], fb[100005];
bool cmp(int x, int y) {
	return x > y;
}
signed main() {
	int n, m, ans = 0;
	cin >> n >> m;
	for(int i = 1;i <= n;i++) {
		cin >> mps[i];
		ans += mps[i];
	}
	for(int i = 1;i <= m;i++) {
		cin >> fb[i];
		ans -= mps[fb[i]];
		fb[i] = mps[fb[i]];
	}
	sort(fb + 1, fb + 1 + n, cmp);
	for(int i = 1;i <= m;i++) {
		if(fb[i] > ans) {
			ans += fb[i];
		}
		else {
			ans *= 2;
		}
	}
	cout << ans << endl;
}
```


---

## 作者：asasas (赞：3)

这题是在校内由题解第一位神仙给我们做的，是一道注重思维而不是代码难度的题。

首先看到题目，我们首先要想到**贪心**算法。

首先用将每个位置的数值以及是否能翻倍的信息记录下来，如果可以翻倍，就将这个数存入另一个数组，否则就将这个数加入答案。然后按照数值从大到小将第二个数组进行排序，接着从$1$~$m$遍历第二个数组。处理到第$i$个位置时，有两种方式：

① 翻倍，即将答案$\times2$

② 不加倍，即直接将第$i$个数加入答案。

取上面两种方案的较大值即可，最后输出答案。


**注意**：这题要开$long long !!!$

代码：
```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
long long a[3000005],b[3000005],dp[100005],c[300005],ans,ok[10005];
int n,m;
inline bool cmp(long long a,long long b){
	return a>b;//排序函数
}
int main(){
	int len=0;
	scanf("%d %d",&n,&m);
	for (register int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		ans+=a[i];//记录总和
	}
	for (register int i=1;i<=m;i++){
		int x;
		scanf("%lld",&c[i]);//读入
		b[++len]=a[c[i]];//记下这个数，存入b数组
		ans-=a[c[i]];//总和减掉这个数
}
	sort(b+1,b+1+m,cmp);//排序
	for (register int i=1;i<=m;i++){
		if (ans+b[i]>ans*2) ans+=b[i];
		else ans*=2;//比较哪种方案更大
	}
	printf("%lld",ans);输出答案
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：1)

看到这题，一看就想到的是排序+贪心

首先，不能翻倍的物品，直接全部加起来。在顺序处理时，为使翻倍后结果更大，排序时把不能翻倍的排在最前面，（先加完，最后再翻倍，结果可以更大）。还是为了使结果更大，把得分高的放在低的前面。

我们用结构体表示每个问题。结构体中设两个变量$val$表示得分，$ok$表示能否翻倍，1表示能

写出结构体
```cpp
struct rec {
	int val;
	bool ok;//1表示能翻倍，0表示不能
	bool operator < (const rec &a) const {
		return ok < a.ok || (ok == a.ok && val > a.val);
	} 
} a[220];
```
我们用数组$a$表示每道题目的信息


最后一个个考虑过来，如果不能翻倍就直接加，否则就比较加了和翻倍那个得分更大

确切点说，设当前位置为$i$,当$ok_i = 1$时，如果$val_i > ans$ 

$ans = ans +val_i$

否则$ans = ans \times 2$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
long long ans;
struct rec {
	int val;
	bool ok;//1表示能翻倍，0表示不能
	bool operator < (const rec &a) const {
		return ok < a.ok || (ok == a.ok && val > a.val);
	} 
} a[220];
int main() {
	cin >> n >> m;
	for (register int i = 1; i <= n; ++i) cin >> a[i].val, a[i].ok = 0;
	for (register int i = 1; i <= m; ++i) {
		int x;
		scanf("%d", &x);
		a[x].ok = 1;
	}
	sort(a + 1, a + n + 1);
	for (register int i = 1; i <= n; ++i) {
		if (!a[i].ok) {
			ans = ans + a[i].val;
		} else {//可以翻倍 
			if (ans > a[i].val) ans *= 2;//翻倍比直接加答案更大 
			else ans = ans + a[i].val;
		}
	}
	cout << ans; 
}
```

---

## 作者：LiteratureCollege (赞：0)

显然的贪心+排序题目 

对于不能翻倍的数字，我们显然应当将其先加到答案里面，再去考虑那些可以翻倍的数字。

显然， 我们应当先把他们
从大往小排序，因为如果我先加上了大的数，后面翻倍就会更加划算，然后就是一个一个枚举，如果翻倍更划算，那么
我们就翻倍，反之就加上这个数。

这个贪心策略是因为我们如果在前面就翻倍了，而有一些大的数字还没有加上，那么
答案肯定不是最优的。所以如果一个数不要翻倍，那么一定尽量把它往前送。 


那么代码就呼之欲出了
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define re return
ll n,m,a[416],b[416],zjy,t,x;//记得开long long 
bool f[416];
bool cmp(ll x,ll y)
{
	re x>y;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>x;
		f[x]=1;//标记所有可以翻倍的数字 
	}
	for(int i=1;i<=n;i++)
	{
		if(!f[i])
		{
			zjy+=a[i];//如果不能翻倍，直接加上 
		}
		else
		{
			b[++t]=a[i];//否则，将他放到另外一个数组里去 
		}
	}
	sort(b+1,b+1+t,cmp);//我们将所有可以翻倍的数从大往小排序 
	for(int i=1;i<=t;i++)
	{
		if(zjy+b[i]>zjy*2)//如果加上更划算 
		{
			zjy+=b[i];
		}
		else//翻倍更划算 
		{
			zjy*=2;
		}
	}
	cout<<zjy;
    return 0;
}
```


---

## 作者：傅思维666 (赞：0)

## 题解：

贪心题。

对于那些不能翻倍的直接加一起。

对于能翻倍的，肯定要考虑翻不翻倍对答案的贡献哪个大。

那么，发现大的翻倍肯定更大，所以在排序的过程中，把所有能翻倍的按权值从大到小排序。然后从大到小依次判断到底要不要翻倍。这样的决策一定是最优的。

~~所以这题在考结构体排序~~

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
long long ans;
struct node
{
	int val;
	bool f;
	bool operator < (const node &a) const {
		return f < a.f || (f == a.f && val > a.val);
	} 
}a[220];
int main() 
{
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= n; ++i) 
        cin >> a[i].val, a[i].f = 0;
	for (int i = 1; i <= m; ++i) 
    {
		int x;
		scanf("%d", &x);
		a[x].f = 1;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) 
    {
		if (!a[i].f)
			ans = ans + a[i].val;
        else
        {
			if (ans > a[i].val) ans *= 2;
			else ans = ans + a[i].val;
		}
	}
	printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：KEBrantily (赞：0)

# 正文
### 题意：
给 n 个关卡，每个关卡得分为 ai，有 m 次机会可以选择一
个关卡通过后不得分，而将现有得分翻倍

你可以安排关卡的通过顺序和策略，求最大得分.

------------
### 分析:
看到这道题首先想到的就是贪心，贪心不仅是最好想也是最好写的。

- 开始我们可以确定的是，如果有个关卡不能翻倍，那你只能把他的分值加上；
- 另外，我们知道，如果基数越大，那他翻倍后的数就越大，
这也是贪心的核心所在，如果我们想要更大的值，就要先得到更大的基数再把它翻倍，所以我们应先把所有只能加的数加起来在翻倍（因为题目给定分值不会为负数）；
- 还有，在遇到能翻倍的关卡的时候，也要判断一下到底是翻倍后得的分多还是不翻倍加上当前关卡分得的分多。

知道这些了以后，我们可以写代码了


------------
### 做法
- 我这里是一开始把所有关卡的分全都加上，再减去可以翻倍的关卡的分，作为开始的基数；
- 然后新开一个数组专门存能翻倍的关卡的分，并从大到小排序，还是遵循了先基数大优先的准则，如果把大的放后面，那他能作为基数扩大后面的值的可能性就会变小，所以先放前面并每次比较加上它后的值与翻倍的值，取较大的那个；
- **注意**：我这里本来想用计数器记录翻倍关卡的数量，在排序时按照它的数量排，但是我这里赋值后关卡分值在数组里的分布是不定的，有的会排不到，所以要把所有的数组全排一遍。


------------
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring> 
#include<cmath>
#include<algorithm>
#define maxn 1000010

using namespace std;

long long n,m,a[maxn],b[maxn],c[maxn],cnt,ans;

int cmp(int x,int y){
	return x>y;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans+=a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		for(int j=1;j<=n;j++){
		    if(b[i]==j){
		    	c[j]=a[b[i]];
		    	ans-=a[b[i]];
		    	cnt++;
		    } 
		}
	}
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=cnt;i++){
		if(ans*2>=ans+c[i]) ans*=2;
		else ans+=c[i];
	}
	cout<<ans;
	return 0;
} 
```

制作不易，若有错请各位指正

---

## 作者：Suzt_ilymtics (赞：0)

# “日拱一卒，功不唐捐”

## [-->题目传送门<--](https://www.luogu.com.cn/problem/CF413C)
## [博客食用更加哦~](https://www.luogu.com.cn/blog/Silymtics/cf413c-jeopardy-ti-xie)

## 下面简述一下思路

通过读题不难看出，这是个贪心

### ~~只要你够贪，贪心胜DP~~

为了赢得“Jeopardy！”的决赛，我们要拿最大分，现在有两种加分途径：

```cpp
1、直接加上关卡分

2、将现有分翻倍
```
首先，因为通关顺序是按我们心情的，所以先排序，反正不亏，那么我们应该按什么规则排序呢？


因为有的关卡根本就不能翻倍，所以我们最好是直接加上

考虑翻倍的关卡，我们最好把能翻倍的且分值小的放在后面翻倍，把分值大的放在前面直接加上，毕竟我们的翻倍次数也是有限的哈

如果能翻倍，标记个1，然后按照能否翻倍为第一关键字，关卡价值为第二关键字排序

## 实现代码：

```cpp
struct node{
	int jz;	bool fb;
	bool operator < (const node & b) const {return fb == b.fb ? jz > b.jz : fb < b.fb ;}//按能翻倍的在后面，价值高的在前面进行排序 
}a[110];
```

所以直接前n-m个加起来，后m个翻倍就好了吗？

 **不不不，先别急，想想我们够不够贪**

### 注意特判：
如果对于下一关的分数来说 加分 比 翻倍 优，那么我们如果选择在上一关翻倍，这一关直接加上会比原来的情况更优

## 实现代码：

```cpp
if(ans  < a[n - m + 1].jz ){//如果对于下一关的分数来说加分比翻倍优的话要进行特判 
		if(a[n-m].fb) ans = (ans - a[n - m].jz) * 2 + a[n - m + 1].jz;//如果上一关可以翻倍就翻倍（因为翻倍更优） 
		else ans += a[n - m + 1].jz;//否则直接加上即可 
		flag = 1;
	} 
```

因为我们是从小到大排序的，所以这种情况只会在第n-m+1个关卡出现，我们只需要做一次就好了

## 下面放AC代码：
```cpp
/*
Work by: Suzt_ilymtics
*/ 
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int jz;	bool fb;
	bool operator < (const node & b) const {return fb == b.fb ? jz > b.jz : fb < b.fb ;}//按能翻倍的在后面，价值高的在前面进行排序 
}a[110];
int n,m,flag;
long long ans = 0;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; ++i)	scanf("%d",&a[i].jz);
	for(int i = 1, x; i <= m; ++i) scanf("%d",&x),a[x].fb = 1;
	sort(a+1,a+n+1);
	for(int i = 1; i <= n - m; ++i) ans += (long long)a[i].jz;//因为只能翻倍m次，所以前n-m个都是直接加上 
	if(ans  < a[n - m + 1].jz ){//如果对于下一关的分数来说加分比翻倍优的话要进行特判 
		if(a[n-m].fb) ans = (ans - a[n - m].jz) * 2 + a[n - m + 1].jz;//如果上一关可以翻倍就翻倍（因为翻倍更优） 
		else ans += a[n - m + 1].jz;//否则直接加上即可 
		flag = 1;
	} 
	for(int i = n - m + 1; i <= n; ++i) ans*=2;
	if(flag) ans /= 2; //如果以前要特判，就会多乘一次，所以要除以2
	printf("%lld",ans);
	return 0;
}
```

## The end


注：感谢您的阅读，如果您有什么不懂得地方，直接私信或评论即可。

---

## 作者：蒟蒻lxy (赞：0)

by QAQer


------------

这题是**贪心**。

首先我们可以发现：题目分为2种，可以翻倍和不可以翻倍  
那我们就一定要先取完所有不能翻倍的再说。

证明：   
>假设原数为$x$,可以加上$y$、乘上$z$
>
>当先加$y$时，结果为：$(x+y)*z=xz+yz$   
>当先乘$z$时，结果为：$xz+y$   
>因为$x,y,z>0 $  
>所以先加更优

加完所有不能翻倍的之后，就要考虑能加倍的了

能加倍的分$2$种情况：  
设ans为原数，这个数为x，则处理完这个数后的答案为：
>1.$ans+x$  
>2.$ans+ans(ans*2)$

所以当$ans$比$x$大时用翻倍操作，否则加$x$

又可以简单地证明：一号操作放在越前面越好，方法同上

所以思路就出来了。

最后，对于n==m时特判一下，取最大值后剩下的一只翻倍就可以了。

### 代码：

```
#include<bits/stdc++.h>
using namespace std;
long long ans=0,n,m,maxa,sum,a[10005],b[10005],lb;
//ans：答案 n、m：题数、可翻倍题数
//a[]：题的得分 b:存储可翻倍的题
bool cmp(long long aa,long long bb)
{
	return a[aa]>a[bb];//将b数组按a[b[i]]从大到小排序
}
int main()
{
	cin >> n >> m;
	for(int i=1;i<=n;i++)
		cin >> a[i];sum+=a[i];//读入，sum累加
	for(int i=1;i<=m;i++)
	{
		int x;
		cin >> x；
		maxa=max(maxa,a[x])；//求出最大值为下面特判服务
		sum-=a[x]；//累加和扣去可翻倍的题
		b[++lb]=x；
	}
	sort(b+1,b+lb+1,cmp);//对b[]排序，从小到大
	if(n!=m)
	{
		for(int i=1;i<=lb;i++)
			sum+=max(a[b[i]],sum)；
		cout << sum << endl；
	}
	else
	{
		cout << (maxa<<(n-1)) << endl；
//一开始先加上最大值，后面再不断翻倍
//“<<”指右移，<<x就是 *(2^x)，所以<<(n-1)就是*(2^(n-1))的意思
		return 0;
	}
	return 0;
};

```
-------------
其实还有一个修改版，但是由于CF太卡了无法提交,无法判断是否正确就先放在这里了（
```
#include<bits/stdc++.h>
using namespace std;
long long ans=0,n,m,sum,a[10005],b[10005],lb;
bool cmp(long long aa,long long bb)
{
	return a[aa]>a[bb];
}
int main()
{
	cin >> n >> m;
	for(int i=1;i<=n;i++)
		cin >> a[i],sum+=a[i];
	for(int i=1;i<=m;i++)
	{
		int x;
		cin >> x;
		sum-=a[x];
		b[++lb]=x;
	}
	sort(b+1,b+lb+1,cmp);
   //n==m的特判可能可以去掉（
	for(int i=1;i<=lb;i++)
		sum+=max(a[b[i]],sum);
	cout << sum << endl;
	return 0;
}

```

---

## 作者：fls233666 (赞：0)

看到求最大得分，考虑进行**贪心**。

我们知道，如果想要得到更多的分，肯定要在总得分尽可能大的情况下进行翻倍。那么，可以先得到所有不能翻倍的题目的得分，然后再考虑是否进行翻倍，这样是最优的。

对于每道可以翻倍的题，单独放入一个大根堆中，按分值**从大到小**考虑是否翻倍，有两种情况：
- 这题的得分比当前总得分多，选择得分更优
- 这题的得分比当前总得分少，选择翻倍更优

按上述想法进行实现，得到如下代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define rgt register int
#define ll long long
using namespace std;
const int mxn = 111;
ll f[mxn],s;
//f[i]为第i题的得分，s为总得分
bool g[mxn];  //g标记是否可以翻倍
int n,m;
priority_queue<ll>fs;  //存所有可以翻倍的题的分数
int main(){
  
    scanf("%d%d",&n,&m);
    for(rgt i=1;i<=n;i++)
        scanf("%lld",&f[i]);
    for(rgt x,i=1;i<=m;i++){
        scanf("%d",&x);
        g[x]=true;
        fs.push(f[x]);
    }//读入数据+预处理
  
    for(rgt i=1;i<=n;i++)
        if(!g[i])
            s+=f[i];
    //先得到所有不能翻倍的题目
                         
    ll tf;
    while(!fs.empty()){
        tf=fs.top();
        fs.pop();
        if(s<=tf)
            s+=tf;
        else
            s*=2;
    }
    //按上述策略进行决策得分
  
    printf("%lld",s);  //输出答案
    return 0;
}

```


---

## 作者：Terrific_Year (赞：0)

贪心：

先将不翻倍的拿到手

从大到小比较翻倍的：必当前分高则拿，反之翻倍

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long s=0;//答案
int a[101],c[31],n,m,i,cs,t;//c放翻倍数值；
bool b[101];//是否可翻倍
int main(){
	cin>>n>>m;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=m;i++){
		cin>>t;
		b[t]=true;//a[t]可选翻倍
		cs=cs+1;//翻倍队列加
		c[cs]=a[t];
	}
	for(i=1;i<=n;i++)if(!b[i])s+=a[i];//不翻倍先拿
	sort(c+1,c+cs+1);排序翻倍
	for(i=cs;i>=1;i--)//从大到小
		if(c[i]>s)s+=c[i];//比分大：不翻倍
		else s*=2;//反之翻倍
	cout<<s;//打印
	return 0;
}
```
~~再也不见~~

---

## 作者：XL4453 (赞：0)



------------
题目分析：

本题可以考虑贪心。

将序列按照是否可以将分数翻倍为第一关键字（从小到大），将分数作为第二关键字（从大到小）排序。

然后将所有的不能翻倍值累加，在可以翻倍的关卡上判断是直接加分更好还是翻倍更好。



------------

然后解释一下为什么这么做：

首先可以发现对于所有的不可翻倍关卡，将其放在翻倍关前面是显然成立的，否则将放到后面的某一个不能翻倍关放到前面一定不会更劣。

对于翻倍关，假设当前的分数总和不及当前关卡分数，那么不翻倍而是将分数直接加上当前翻倍关的分数是显然成立的。那么这样的一个翻倍关反而成了普通的加分关，由之前的结论可知，应当将其放到前面。

同时，我们又希望这样的关卡尽量多，所以应当将大的翻倍关放到前面，反正加分关无所谓顺序。



------------
提示：开 long long。

------------
代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int num,c;
}x[105];
bool cmd(node a,node b){
	if(a.c!=b.c)
	return a.c<b.c;
	return a.num>b.num;
}
int n,m,u;
long long ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&x[i].num);
	for(int i=1;i<=m;i++){
		scanf("%d",&u);
		x[u].c=1;
	}
	sort(x+1,x+n+1,cmd);
	for(int i=1;i<=n;i++){
		if(x[i].c){
			ans=max(ans*2,ans+(long long)x[i].num);
		}
		else{
			ans+=(long long)x[i].num;
		}
	}
	printf("%lld",ans);
	return 0;
}

```


---

