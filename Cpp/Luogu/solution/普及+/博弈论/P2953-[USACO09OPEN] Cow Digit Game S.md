# [USACO09OPEN] Cow Digit Game S

## 题目描述

Bessie is playing a number game against Farmer John, and she wants you to help her achieve victory.

Game i starts with an integer N\_i (1 <= N\_i <= 1,000,000). Bessie goes first, and then the two players alternate turns. On each turn, a player can subtract either the largest digit or the smallest non-zero digit from the current number to obtain a new number. For example, from 3014 we may subtract either 1 or 4 to obtain either 3013 or 3010, respectively. The game continues until the number becomes 0, at which point the last player to have taken a turn is the winner.

Bessie and FJ play G (1 <= G <= 100) games. Determine, for each game, whether Bessie or FJ will win, assuming that both play perfectly (that is, on each turn, if the current player has a move that will guarantee his or her win, he or she will take it).

Consider a sample game where N\_i = 13. Bessie goes first and takes 3, leaving 10. FJ is forced to take 1, leaving 9. Bessie takes the remainder and wins the game.

贝茜和约翰在玩一个数字游戏．贝茜需要你帮助她．

游戏一共进行了G(1≤G≤100)场．第i场游戏开始于一个正整数Ni(l≤Ni≤1,000,000)．游

戏规则是这样的：双方轮流操作，将当前的数字减去一个数，这个数可以是当前数字的最大数码，也可以是最小的非0数码．比如当前的数是3014，操作者可以减去1变成3013，也可以减去4变成3010．若干次操作之后，这个数字会变成0．这时候不能再操作的一方为输家．    贝茜总是先开始操作．如果贝茜和约翰都足够聪明，执行最好的策略．请你计算最后的赢家．

比如，一场游戏开始于13.贝茜将13减去3变成10．约翰只能将10减去1变成9．贝茜再将9减去9变成0．最后贝茜赢．


## 说明/提示

For the first game, Bessie simply takes the number 9 and wins. For the second game, Bessie must take 1 (since she cannot take 0), and then FJ can win by taking 9.


## 样例 #1

### 输入

```
2 
9 
10 
```

### 输出

```
YES 
NO 
```

# 题解

## 作者：konjacq (赞：14)

每种状态可以转移出两个新状态。博弈论的结论：

当某种状态的后继状态**都是必败状态**时，该状态为必胜状态；

当某种状态的后继状态**有一种是必胜状态**时，该状态为必败状态。

所以先将0标记为必败，1-9标记为必胜（显然），从10-1000000遍历一遍，用f数组存必败或必胜，然后输出就可以了。在求f[i]的时候只会用到f[i-max/min],而max/min必然大于0，所以顺序遍历即可。
```cpp
#include <cstdio>
using namespace std;

int q,n;
bool f[1000020];

inline int fmax(int x)
{
	int m=0;
	while (x) {if (x%10>m) m=x%10; x/=10;}
	return m;
}

inline int fmin(int x)
{
	int m=10;
	while (x) {if (x%10<m&&x%10) m=x%10; x/=10;}
	return m;
}

int main()
{
	//f[0]=false 不做处理（因为f默认为false）
	for (int i=1;i<10;i++) f[i]=true;
	for (int i=10;i<1000001;i++)
	{
		if (f[i-fmax(i)]&&f[i-fmin(i)])；//不做处理（因为f默认为false）
		else f[i]=true;
	}
	scanf ("%d",&q);
	for (int i=0;i<q;i++)
	{
		scanf ("%d",&n);
		if (f[n]) printf ("YES\n");
		else printf ("NO\n");
	}
	return 0;
}
```
然而还有更快的方法：
```cpp
#include <cstdio>
using namespace std;

bool f[1000020];

inline int fmax(int x)
{
	int m=0;
	while (x) {if (x%10>m) m=x%10; x/=10;}
	return m;
}

inline int fmin(int x)
{
	int m=10;
	while (x) {if (x%10<m&&x%10) m=x%10; x/=10;}
	return m;
}

int main()
{
	freopen (".txt","w",stdout);
	for (int i=1;i<10;i++) f[i]=true;
	printf ("f[1000020]={0,1,1,1,1,1,1,1,1,1");
	for (int i=10;i<1000001;i++)
	{
		if (f[i-fmax(i)]&&f[i-fmin(i)]) f[i]=false;
		else f[i]=true; printf (",%d",f[i]);
	}
	printf ("};"); return 0;
}
```
配合
```cpp
#include <cstdio>
using namespace std;

int g,n;
bool //将上一个程序运行后的文件内容粘贴在这里

int main()
{
	scanf ("%d",&g);
	for (int i=0;i<g;i++)
	{
		scanf ("%d",&n);
		if (f[n]) printf ("YES\n");
		else printf ("NO\n");
	}
	return 0;
}
```
只是洛谷不让交……

---

## 作者：qzhwlyn (赞：7)

这道题一开始看觉得是DFS,但是一看数据l≤Ni≤1,000,000，就排除这个可能。

我一开始是把每个数的每位数都计算一遍，如果这个数减去每位数都是必胜的，那么这个数就必输。
# 40分代码
```c
#include<bits/stdc++.h>
using namespace std;
int a[101];
int f[1000001];
int n,maxx,tot1,tot2,sum;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]>maxx) maxx=a[i];
	}
	for(int i=1;i<=9;i++){
		f[i]=1;
	}
	for(int i=10;i<=maxx;i++){
		tot1=i;
		while(tot1>0){
			tot2=tot1%10;
			tot1/=10;
			if(f[i-tot2]==0&&tot2!=0){
				f[i]=1; 
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(f[a[i]]==1) printf("YES\n");
		else printf("NO\n");
	}
}
```
超时了，于是，通过博弈论我们可以知道：

### 如果一个数无论减去任何数都是必败的，那么这个数就是必胜；

### 如果一个数只要减去一个数是必胜的，那么这个数就是必败；

所以先将0标记为必败，1-9标记为必胜，从10-maxx遍历一遍，用f数组存必败或必胜，然后输出就可以了。

# AC代码
```c
#include<bits/stdc++.h>
using namespace std;
int a[101],n,m1,m2,tot;
bool f[100001];
int minn,maxx; 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]>maxx) maxx=a[i];
	}
	for(int i=1;i<=9;i++){
		f[i]=1;
	}
	for(int i=10;i<=maxx;i++){
		m1=0;
		tot=i;
		while(tot){
			if(tot%10>m1) m1=tot%10;
			tot/=10;
		}
		m2=10;
		tot=i;
		while(tot){
			if(tot%10<m2&&tot%10) m2=tot%10;
			tot/=10;
		}
		if(f[i-m1]&&f[i-m2]);
		else f[i]=1;
	}
	for(int i=1;i<=n;i++){
		if(f[a[i]]==1)printf ("YES\n");
		else printf ("NO\n");
	}
	return 0;
}
```


---

## 作者：UperFicial (赞：5)

# 博弈论

### 前言

很一眼的博弈，但因为审错题意害得这个菜鸡 $\texttt{\color{red}WA}$ 了半天。

~~之后加了点优化就最优解了~~


远古时期出过一道貌似类似的博弈（？）~~不过准备放到gks~~。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/P2953)

### 题意简述

形式化题面：给定正整数 $x$，一次操作可将 $x$ 更改为 $x-maxn$ 或 $x-minn$，两个足够聪明的人轮流操作，谁先得到 $0$ 谁胜。问谁必胜。

$minn$ 为 $x$ 的各个位上除了 $0$ 的最小的数，$maxn$ 为 $x$ 的各个位上除了 $0$ 的最大的数。

### 题目解析

做博弈论的老套路其实就一句话：

> 必胜态至少有一个后继是必败态，必败态的所有后继都是必胜态。

这里就不对这句话做更多的阐释了，想想就能明白。

这道题就可以很好的应用这个结论了。

我们定义一个布尔数据 $dp$，$dp[x]$ 若为 $\texttt{true}$ 则表示 $x$ 为必胜态，反之则为必败态。

显然我们可以定义初始值，对于正整数 $x$ 满足 $1\le x\le 9$，$x$ 就是 一个必胜态，自己直接减去自己就是 $0$。

而对于其它的状态呢？显然通过上面那个结论，我们可以通过状态之间的关联来进行递推。

对于枚举的 $x$，我们很容易可以知道它如上文所述的 $minn$ 和 $maxn$。

那么根据题意 $x$ 的两个后继就是 $x-minn$ 和 $x-maxn$。

若两个后继都是必胜态即 `dp[x-minn]=1` 且 `dp[x-maxx]=1`，那么当前状态就是必败态即 `dp[x]=0`，反之 `dp[x]=1`。这只是套用了上面那句话。

当然可以加一些~~无关紧要的~~优化：

- 优化 $1$：$dp$ 的递推可以直接用一句话来解决：`dp[x]=(dp[x-minn]&dp[x-maxn])^1`。

- 优化 $2$：取 $\min$ 和 $\max$ 的时候手写函数加 $\text{inline}$。

于是就得到了代码：[$code$](https://paste.ubuntu.com/p/tWkj98kP5Y/)

~~但我们交上去发现，不是最优解~~

~~那就继续优吧~~

我们来考虑我们的时间浪费在了哪里，没错，也就是初始化。

当给定的数 $x$ 都在很小的范围以内，预处理那么多就浪费时间了。

> 时间不够，离线来凑。

我们可以记录询问的 $x$ 中的最大值 $maxval$，预处理只需在 $maxval$ 以内即可。

[$code$](https://paste.ubuntu.com/p/FDjVXp6QtC/)

时间复杂度：$O(maxval)$。

空间复杂度：$O(10^6)$。

于是乎就抢到了最优解/cy

$$\texttt{The End.by UF}$$

---

## 作者：Henry_he (赞：4)

这道题的数据范围是可以用dfs轻松A掉的啦

但是那样子做的细节处理比较多，而且比较长

我们可以使用无脑的sg函数

# sg函数的使用说明:

1. 当一个问题可以拆成许多个互不相关联的子问题时，此问题的sg为子问题的异或和

2. 当一个问题不能拆成子问题时，此问题的sg为其后继状态的sg取mex
(最小未出现的自然数)

3. 每一个状态sg若大于零，则该状态为必胜态，若为零则为必败态

4. 至于为什么，可以去网上找论文，这里不加赘述

### 那么回到本题 ，本题是有许多局所组成，那么我们用石头的数字来表示状态，即sg[i]表示有i个石头的状态，然后对后继状态进行处理

先预处理:我们知道sg[0]肯定是先手必败态，所以sg[0]=0

然后用递推来求出sg[n],用max来表示最大数码，用min来表示最小数码，我们可以得到式子

# sg[n]=mex(sg[n-max],sg[n-min])

由于是递推，sg[n-max]和sg[n-min]是肯定已知的，而求mex，只要用桶把它装起来再扫一遍就可以了

代码:

```pascal
var g,n,k,x,i,max,min:longint;
    sg:array[0..1000000]of longint;
    p:array[0..1000000]of longint;
begin
  readln(g);
  sg[0]:=0;
  for i:=1 to 1000000 do//由于知道最大一百万，先求出所有的sg就可以啦
  begin
    k:=i;
    max:=0;
    min:=maxlongint;
    while k>0 do//找出max，min
    begin
      x:=k mod 10;
      if x>max then max:=x;
      if (x>0)and(x<min) then min:=x;
      k:=k div 10;
    end;
    p[sg[i-max]]:=i;//入桶
    p[sg[i-min]]:=i;//入桶
    for k:=0 to 1000000 do//求mex
      if p[k]<>i then
      begin
        sg[i]:=k;
        break;
      end;
  end;
  while g>0 do
  begin
    dec(g);
    readln(n);
    if sg[n]>0 then writeln('YES')//判断+输出
               else writeln('NO');
  end;
end.
```

---

## 作者：beng (赞：4)

# 记忆化搜索就行啦~

我们先来复习一下博弈论的两个规则：

1. 一个状态是必败状态当且仅当它的所有后继都是必胜状态；
2. 一个状态是必胜状态当且仅当他至少有一个后继是必败状态。

那么我们知道了这两点，就可以DFS他的两个后继（因为只可以取最小数和最大数）来推出当前状态啦~

注意一下记忆化就可以了~

---

pascal代码如下：

```pascal
var n,m,i:longint;
a:array[1..1000000]of longint;//我规定0为还没有搜到答案，1为必胜态，-1为必败态
function go(x:longint):longint;
var i,j,k,max,min:longint;
begin
  if x=0 then//如果当前数字为0，那一定是必败态
  exit(-1);
  if a[x]<>0 then//如果当前状态已经被搜过，直接返回答案
  exit(a[x]);
  k:=x;
  max:=0;
  min:=maxlongint;
  while k>0 do//求最大最小值
  begin
    j:=k mod 10;
    if j>max then
    max:=j;
    if (j>0)and(j<min) then//注意最小值不能为0
    min:=j;
    k:=k div 10;
  end;
  i:=go(x-max);//i为减去最大数的状态
  j:=go(x-min);//j为减去最小数的状态
  if (i=-1)or(j=-1) then//根据规则判断当前状态
  begin
    a[x]:=1;
    go:=1;
  end
  else
  begin
    a[x]:=-1;
    go:=-1;
  end;
end;
begin
  readln(n);
  for m:=1 to n do
  begin
    readln(i);
    if go(i)=-1 then
    writeln('NO')
    else
    writeln('YES');
  end;
end.
```

---

## 作者：环日加速器 (赞：3)

# 本蒟蒻的第二篇题解
我们机房考试的时候出了一样的题，就写了一篇题解。
考场懵逼（大雾）

骗了Ni小于100的数据（居然有40分）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		if(k%10!=0)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

LJ我错了，别打我。

（假装哪个数都可以取）

后来，李老师讲题了：@%￥#&%#@￥%。

就是这样的：

1.如果这个数的2个后继都为一定胜利，那么这个数一定失败；

2.如果这个数的2个后继有一个为一定失败，那么这个数一定胜利；

于是我就写了一个O（GNi*Ni位数）的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1000009];
int main()
{
	int n;
	scanf("%d",&n);
	int k;
	f[1]=1;
	f[2]=1;
	f[3]=1;
	f[4]=1;
	f[5]=1;
	f[6]=1;
	f[7]=1;
	f[8]=1;
	f[9]=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		for(int j=10;j<=k;j++)
		{
			int x1=j;
			int ma=0,mi=10;
			while(x1!=0)
			{
				ma=max(ma,x1%10);
				if(x1%10!=0)mi=min(mi,x1%10);
				x1=x1/10;
			}
			if(mi==10)
			{
				if(f[j-ma]==1)f[j]=0;
				else f[j]=1;
			}
			else
			{
				if(f[j-ma]==1&&f[j-mi]==1)f[j]=0;
				else f[j]=1;
			}
			
		}
		if(f[k]==1)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

很明显，它T了
![](https://cdn.luogu.com.cn/upload/pic/70225.png)

但是我吸了一口氧，它A了
![](https://cdn.luogu.com.cn/upload/pic/70222.png )

但在考试中

很明显你不能吸氧，再强的氧也不行。

所以我们预处理一下
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1000009];
int main()
{
	int n;
	scanf("%d",&n);
	int k;
	f[1]=1;
	f[2]=1;
	f[3]=1;
	f[4]=1;
	f[5]=1;
	f[6]=1;
	f[7]=1;
	f[8]=1;
	f[9]=1;
	for(int i=10;i<=1000000;i++)
	{
		int x1=i;
		int ma=0,mi=10;
		while(x1!=0)
		{
			ma=max(ma,x1%10);
			if(x1%10!=0)mi=min(mi,x1%10);
			x1=x1/10;
		}
		if(mi==10)
		{
			if(f[i-ma]==1)f[i]=0;
			else f[i]=1;
		}
		else
		{
			if(f[i-ma]==1&&f[i-mi]==1)f[i]=0;
			else f[i]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		if(f[k]==1)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

![](https://cdn.luogu.com.cn/upload/pic/70230.png )
愉快地A了

---

## 作者：Refined_heart (赞：2)

题目大意：给一个数$n<=10^6$,每次减去它数位上的最大值或非$0$的最小值，问谁先取成$0$.

$\text{Solution:}$

设$sg_i$表示$i$是不是必胜。（这里的$sg$只是一个数组，不是那个$\text{SG}$函数）

那么，我们暴力把$i$的每一位拆分出来，看看减去它的最小值和最大值后的状态是不是有**必败状态**。

若有必败状态，则本状态是必胜状态，因为他们显然会选择那个必败态使得游戏对自己有利。

否则，因为它的前驱都是必胜态，到了它只能必败。

这题做完了。代码是直接处理完了$10^6$以内的所有情况，复杂度不大于$O(7*10^6).$

```cpp
#include<bits/stdc++.h>
using namespace std;
int sg[1000001],T;
void solve(int x){
	int n=x;
	int mx=1,mi=10;
	while(x>0){
		int num=x%10;
		x/=10;
		if(num!=0&&num<mi)mi=num;
		if(num>mx&&num!=0)mx=num;
	}
	if(sg[n-mx]==0||sg[n-mi]==0)sg[n]=1;
}
int main(){
	sg[0]=0;
	for(int i=1;i<10;++i)sg[i]=1;
	for(int i=10;i<=1000000;++i)solve(i);
	scanf("%d",&T);
	while(T--){
		int G;
		scanf("%d",&G);
		puts(sg[G]?"YES":"NO");
	}
	return 0;
}
```


---

## 作者：Aryzec (赞：2)

### [题面](https://www.luogu.org/problemnew/show/P2953)
### [博客食用](https://www.luogu.org/blog/41834/solution-p2953)
---
## 大致题意

有一个正整数，两个人轮流操作，轮到你时你可以将这个数减去它每个数位上的数中最小或最大的数，最后谁使得这个数变为 $0$ 则为胜利。比如说现在轮到你操作，有一个三位数 $123$ ，那么，你可以选择将这个数减去 $1$ 或 $3$ ，但不可以减去 $2$ 。两个人都足够聪明，都会按照最优的决策操作。

---
## 思路

有多组数据，读一个计算一个可能会比较慢。我们考虑预处理出对于每个数字 $Bessie$ 是否能赢。当然，你也可以用**记忆化搜索** ,而且记搜跑起来会更快。

我们不难想到，一个数 $x$ 只可能从 $x+1$ ~ $x+9$ 中的数字得到。用 $f_i$ 表示对于 $i$ 这个数字 $Bessie$ 能否赢，一开始 $f_0=0$ 。从 $0$ 到 $Maxn$ 循环，循环到 $i$ 时 $check$ 能否由 $i+add ( 1\leq add \leq 9 ) $ 这个数得到 $i$ ，如果能，那么就有 $f[i+add]=!f[i]$。

具体请见代码 $↓$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1000005],n,x;
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
bool check(int x,int in){
	if(x>1000000)return 0;//防止越界
	register int Min=10,Max=0;
	while(x){
		if(x%10)Min=min(Min,x%10),Max=max(Max,x%10);//更新最大值和最小值
		x/=10;
	}
	return (Min==in||Max==in);//最大或最小的数等于add
}
int main(){
	for(int i=0;i<=1000000;++i){
		if(f[i])continue;//如果当前f[i]=1，那么!f[i+add]=0，就算check后能通过i得到i+add，但是f[i+add]=!f[i]=0，所以没有继续算下去的意义
		for(int add=1;add<=9;++add){//枚举
			if(check(i+add,add))f[i+add]=1;//如果可以由i得到i+add，就可以更新f[i+add]
		}
	}
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&x);
		if(f[x])puts("YES");else puts("NO");//之前已经预处理好了，直接输出就行了
	}
	return 0;
}
```

---

## 作者：Exber (赞：1)

这道题是一道 DP 题。我们设 $win_{i}$ 为 true 时表示 $n$ 为 $i$ 时奶牛贝茜能赢，为 false 时表示当 $n$ 为 $i$ 时奶牛贝茜不能赢，那么状态转移方程就是：

$win_{i}=\urcorner win_{i-maxx}\lor\urcorner win_{i-minx}$ （$maxx$ 表示 $i$
的最大数码，$minx$ 表示 $i$ 的最小数码）

我们只要预处理好 $win$ 数组，询问的时候 $O(1)$ 判断就行了。

DP 部分代码：
```cpp
for(int i=1;i<=9;i++)
{
	win[i]=true; // 初始化，一位数时贝茜一定能赢
}
for(int i=10;i<=1000003;i++)
{
	int maxx=1,minn=9,tmp=i;
	while(tmp)
	{
		// 求最大数码和最小数码
		int k=tmp%10;
		tmp/=10;
		if(k>maxx)
		{
			maxx=k;
		}
		if(k!=0&&k<minn)
		{
			minn=k;
		}
	}
	if(!win[i-maxx]||!win[i-minn]) // 状态转移
	{
		win[i]=true;
	}
}
```

---

## 作者：qzhwlzy (赞：1)

# [传送器](https://www.luogu.com.cn/problem/P2953)  
## 思路
看到题目，很明显是一道递推（~~DP~~）题，对于某一个点来说，其必胜或否就是取决于它减去数码之后的数的必胜或否。  
对于数 $x$ ，其必胜或否就是下面两种情况（假设最大数码为 $maxdigit$ ，最小非零数码为 $mindigit$ ）：  
1. 若 $x$ - $maxdigit$ 和 $x$ - $maxdigit$ 中**两个都是必胜**的，那么 $x$ **必输无疑**。毕竟不管你减哪个对方都必胜。  
2. 若 $x$ - $maxdigit$ 和 $x$ - $maxdigit$ 中**有一个不是必胜**，则么 $x$ **必胜**。毕竟你减去之后就给了对手一个必输的数。
## 代码（可能有点繁杂）
```cpp
#include<iostream>
#include<cstdio>
#define maxn 1000005
using namespace std;
int g;
int n[maxn],mmax=-1;
int f[maxn];
int ma,mi;
void digit(int x){//找最大最小数码
	while(x>0){
		int xx=x%10;
		ma=max(ma,xx);
		if(xx<mi&&xx!=0){
			mi=xx;
		}
		x/=10;
	}
}
int main(){
	//freopen("cdgame.in","r",stdin);
	//freopen("cdgame.out","w",stdout);
	scanf("%d",&g);
	int sum=g;
	int ii=1;
	while(g--){
		scanf("%d",&n[ii]);
		mmax=max(mmax,n[ii]);
		ii++;
	}
	f[0]=0;
	for(int i=1;i<=9;i++){
		f[i]=1;
	}
	for(int i=10;i<=mmax;i++){
		ma=0;
		mi=10;
		digit(i);
		if(f[i-ma]==0||f[i-mi]==0){//第二条
			f[i]=1;
		}else{//第一条
			f[i]=0;
		}
	}
	for(int i=1;i<=sum;i++){//输出
		if(f[n[i]]){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}

```


---

## 作者：heheheheehhejie (赞：1)

这道题拿到一看，第一秒想到了深搜，然后第二秒就想到了

#直接跑出所有的数字贝茜能不能赢

然后每问一次就根据情况回答能否胜利

怎么跑？

首先对于1-9，谁先遇到这个数字，谁就赢了。

那么我们定义数组ifncan[i][2]//不要在意这个数组名字

ifncan[i][0]表示贝茜先遇到数字i能不能赢。

ifncan[i][1]表示约翰先遇到数字i能不能赢。

那么对于数字i,找到他的最大的数字ma和最少的数字mi

那么ifncan[i][0]的状态就可以用ifncan[i-ma][1]和ifncan[i-mi][1]来得到

约翰的状态以此类推。

具体细节要想清楚（怎么得到）

#多思考，你会发现其实非常简单

//写完了突然发现约翰的完全没必要，但这样还是能过，理解度更强

Code
`


```cpp
#include <iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;
bool ifncan[1000010][2];
struct ss{int minx,maxy;};//用来返回值的结构体
ss getmix(int x)//获得最小的非零数和最大数，用结构体直接返回两个值
{
    int wow=0,ooomax=0,ooomin=0xfffffff;
    ss ooooooo;
    while(x>=1)
    {
        int p=x%10;
        ooomax=max(ooomax,p);
        if(p!=0)
            ooomin=min(ooomin,p);
        x/=10;
    }
    ooooooo.minx=ooomin;
    ooooooo.maxy=ooomax;
    return ooooooo;
}
void hhhhhhhh()
{
    for(int i=10;i<=1000000;i++)
    {
        ss wo=getmix(i);
        int chos1=wo.maxy,chos2=wo.minx;
        if(!ifncan[i-chos1][1]||!ifncan[i-chos2][1])
            ifncan[i][0]=1;
        if(!ifncan[i-chos1][0]||!ifncan[i-chos2][0])
            ifncan[i][1]=1;
    }
}
int main()
{
    for(int i=1;i<=9;i++)
        ifncan[i][0]=true,ifncan[i][1]=true;
    hhhhhhhh();
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int x;
        scanf("%d",&x);
        if(ifncan[x][0])
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
`
```

---

## 作者：AKSCP_J2019 (赞：1)

## 用f数组存储能不能必胜和必败状态嘛
# 一点都不花里胡哨
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int f[1000005];
int maxx,minn;
void check(int x)
{
	maxx=0,minn=10;
	int v=x;
	while(v>0)
	{
		int c=v%10;
		maxx=max(maxx,c);if(c!=0)minn=min(minn,c);
		v/=10;
	}
	return;
}
int main() {
	for(int i=1;i<=9;i++)f[i]=1;
	for(int i=10;i<=1000000;i++){
		check(i);
		f[i]=(!f[i-minn]||!f[i-maxx]);//前一个状态必败，下一个状态必胜
	}
	cin>>t;
	while(t--) {
		int n;
		cin>>n;
		if(f[n])cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}
```


---

## 作者：PersistentLife (赞：0)

这是一道必胜必败点搜索的题。

我们将 $1$ 至 $9$ 都标记为必胜点，因为这样进行任意一种操作都可以变成 $0$。

然后我们从 $10$ 遍历到 $10^6$，根据必胜必败点的性质，如果 $i-maxx(i)$ 和 $i-minx(i)$ 都是必胜点的话，那么就无法进入对手的必败点，所以这个点是必败点，否则就可以进入对手的必胜点，也就是说它是必胜点，其中 $maxx(i)$ 和 $minx(i)$ 分别表示 $i$ 每一位上最大的数和每一位上除 $0$ 之外的最小数。

```cpp
void getans()
{
	for(int i=10;i<=1000000;i++)
	{
		if(win[i-maxx(i)]&&win[i-minx(i)]) win[i]=0;
		else win[i]=1;
	}
}
```

然后，我们把 $maxx$ 和 $minx$ 写一下，注意，$minx$ 要特判这一位是 $0$ 的情况。

$maxx$ 如下：

```cpp
int maxx(int x)
{
	int ret=0;
	while(x)
	{
		ret=max(ret,x%10);
		x/=10;
	}
	return ret;
}
```

$minx$ 如下：

```cpp
int minx(int x)
{
	int ret=10;
	while(x)
	{
		if(x%10!=0) ret=min(ret,x%10);//特判
		x/=10;
	}
	return ret;
}
```

最后，放上完整代码，记得初始化。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,win[1234567];
int maxx(int x)
{
	int ret=0;
	while(x)
	{
		ret=max(ret,x%10);
		x/=10;
	}
	return ret;
}
int minx(int x)
{
	int ret=10;
	while(x)
	{
		if(x%10!=0) ret=min(ret,x%10);
		x/=10;
	}
	return ret;
}
void getans()
{
	for(int i=10;i<=1000000;i++)
	{
		if(win[i-maxx(i)]&&win[i-minx(i)]) win[i]=0;//无法进入对手的必败点
		else win[i]=1;//可以进入对手的必败点
	}
}
int main()
{
	for(int i=1;i<=9;i++) win[i]=1;//不能忘记初始化，而且要放在getans前
	getans();
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(win[n]) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：何卓然 (赞：0)

分析题目，我们发现，对于当前的一个数字，必然是从之前的一些数字得到的。


比如我们举 2017 为例，

2017                                                     // 第一层 ： A 玩家 将数字减到了 2017

2016                                    2010                              // 第二层 ： B 玩家 可以将数字减到 这两个新数字

2015              2010            2009              2008                     // 第三层 ： A 玩家 可以将数字减到 这四个可能的值


我们发现了一个结论， 如果在 2016 转移出得两个数，和 2010 转移出的两个数，其中都至少有一个是我必胜的，那么 2017 这个数字，

无论对手选择 到 2016 还是 到 2010 我都有必胜的做法，这是 2017 是我的必胜数字的充要条件。





**Code**











```cpp
#include<bits/stdc++.h>
using namespace std;
#define REP(i,a,b) for (int i=(a);i<(b);++i)
bool f[1000005];
int n;
int max_dig(int x)
{
    int ret = 0;
    while(x){
        ret = max(ret, x % 10);
        x /= 10;
    }
    return ret;
}
int min_dig(int x)
{
    int ret = 9999;
    while(x){
        if (x % 10 != 0) ret = min(ret, x % 10);
        x /= 10;
    }
    return ret;
}
int main()
{
    f[0] = true, f[10] = true;
    REP(i,1,10) f[i] = false;
    REP(i,10,1000005)
    {
        bool f1 = false, f2 = false, g1 = false, g2 = false;
        int a = i - min_dig(i),b = i - max_dig(i);
        if (f[a - min_dig(a)]) f1 = true;
        if (f[a - max_dig(a)]) f2 = true;
        if (f[b - min_dig(b)]) g1 = true;
        if (f[b - max_dig(b)]) g2 = true;
        if ((f1 && g1) || (f1 && g2) || (f2 && g1) || (f2 && g2)) f[i] = true;
    }
    scanf("%d",&n);
    while(scanf("%d",&n) != EOF)
    {
        if (f[n]) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}

```

---

## 作者：Skywalker_David (赞：0)

先算出一个数字能减的数字


然后从以前的状态转移而来


在自己先手的时候如果能把数字改成先手必输的状态，那么这个状态先手必胜


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctime>
#include<set>
#define LL long long
#define MX 1000010
using namespace std;
inline LL read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
bool win[1000010];
int T,n,mx,mn;
int main()
{
    scanf("%d",&T);
    for (int i=1;i<=9;i++)win[i]=1;
    for (int i=10;i<=MX;i++)
    {
        int s=i,t;
        mx=-1;mn=10;
        while (s)
        {
            t=s%10;
            if (t>mx&&t)mx=t;
            if (t<mn&&t)mn=t;
            s/=10;
        }
        if (mx!=-1)win[i]|=(!win[i-mx]);
        if (mn!=10)win[i]|=(!win[i-mn]);
    }
    while (T--)
    {
        int x=read();
        if (win[x])printf("YES\n");
        else printf("NO\n");
    }
}
```

---

