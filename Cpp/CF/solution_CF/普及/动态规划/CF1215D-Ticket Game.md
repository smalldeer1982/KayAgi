# Ticket Game

## 题目描述

``Monocarp``和``Bicarp``生活在``Berland``。``Berland``的每一张公交车票都包含$n$（$n$是偶数）位数。

在晚上散步时，``Monocarp``和``Bicarp``发现了一张有某些位被擦掉而空着（擦掉的位数也是偶数）的公交车票。

``Monocarp``讨厌“高兴”的车票，而``Bicarp``则喜欢并收集它们。我们称一张车票“高兴”是说前$\frac n 2$位数之和和后$\frac n 2$位数之和相等。

``Monocarp``和``Bicarp``轮流进行操作（``Monocarp``先手），每次操作，当前进行操作的玩家会在一个被空着的数位填上$0$到$9$。当所有数位都被填满，游戏结束。

如果这张车票在游戏结束后“高兴”，那么``Bicarp``胜利；否则``Monocarp``胜利。如果两人都足够聪明，请你确定谁会胜出。

## 说明/提示

样例一中没有任何问号，所以赢家在游戏开始前就决定了，显然就是``Bicarp``。

在样例二中，``Bicarp``也会赢。在``Monocarp``在一个空位填上一个数之后，``Bicarp``可以在另一个空位填上一个一样的数，于是车票就变得“高兴”了。

## 样例 #1

### 输入

```
4
0523
```

### 输出

```
Bicarp
```

## 样例 #2

### 输入

```
2
??
```

### 输出

```
Bicarp
```

## 样例 #3

### 输入

```
8
?054??0?
```

### 输出

```
Bicarp
```

## 样例 #4

### 输入

```
6
???00?
```

### 输出

```
Monocarp
```

# 题解

## 作者：Su_Zipei (赞：6)

## 分析
~~这道题算是一道比较水的博弈论？~~不知道为啥我写了一个很清奇的思路。。。。

首先数据中的给出的一串字符串没必要都存，只保存两边分别的？数量和总的数字和。

最简单的就是样例一的情况，如果没有问号，显然在这种情况下只有两边的数字和$cnt$初始不等时，才会有$Monocarp$赢，这种情况非常特殊，那能不能推广到一般呢？这里用到我xjb推出的一个结论，左边的？和右边的？是等价的。为什么呢？如果$Monocarp$从$cnt$大的一边来填数，它肯定要去拉大差距，即填9，那另一边的$Bicarp$为了缩小差距也会填9，当$Monocarp$从小的那边开始填也是一样，也就是说假如左边有5个？，右边有3个，就等价于左边有2个？。于是样例一的情况推广到当**两边的？数量相同时，如果$cnt$不等，则$Monocarp$赢。**

接下来考虑不等的情况。根据上边的结论，我们可以把两侧的博弈转换成一侧的博弈。

假设剩下一侧的等价问号数量为$w$，举个例子，若$w$为4，则$Bicarp$操作次数为2，若为5，他还是操作2次，因为$Monocarp$会先手。

下面来考虑等价的问号在哪一侧，这里以在左边为例，假设左边的数字和为$cnt1$右边的为$cnt2$，如果$cnt1$最开始就大于$cnt2$那么很抱歉$Bicarp$不可能赢，因为$Monocarp$可以一直填9，对于剩下的情况，可以只考虑极限情况，因为中间的博弈过程两个人都是选最优操作，因此可以不用考虑，极限的情况有两种，一是$Monocarp$疯狂填9，另外一个拦都拦不住只能填0，填到最后$cnt1$大于$cnt2$了，二是$Bicarp$疯狂填9，另一个一直填0，然而填到最后也达不到$cnt2$，这两种情况都是$Monocarp$赢，剩下的就只需要判断了。
```cpp
#include<cstdio>
const int N=2e5+10;
char s[N];
int main(){
    int cnt1,cnt2,w1,w2;
    int n;
    cnt1=cnt2=w1=w2=0;
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        if(i<=n>>1){
            if(s[i]=='?')w1++;
            else cnt1+=s[i]-'0';
        }else {
            if(s[i]=='?')w2++;
            else cnt2+=s[i]-'0';
        }
    }
    bool flag=1;
    if(w1==w2){
        if(cnt1!=cnt2)flag=0;
    }
    else if(w1>w2){
        int w=w1-w2;w>>=1;
        if(cnt1>cnt2)flag=0;
        else if(cnt1+w*9<cnt2 || cnt1+(w1-w2-w)*9>cnt2)flag=0;//Monocarp的操作次数可能比w大1.
    }else {
        int w=w2-w1;w>>=1;
        if(cnt2>cnt1)flag=0;
        else if(cnt2+w*9<cnt1 || cnt2+(w2-w1-w)*9>cnt1)flag=0;
    }
    if(flag)printf("Bicarp\n");
    else printf("Monocarp\n");
}
```
## 最后
因为是自己写的所以可能有Bug，如果有hack数据可以找我~

---

## 作者：Fading (赞：4)

博弈论。

我们先预处理出前半部分已知数的和，已经后半部分的和，设为$\text{sum}_0,\text{sum}_1$。

如果$\text{sum}_0>\text{sum}_1$，那么 Monocarp  就会在左半边处加$9$。这对于他而言是最优的（拉大距离）

然后 Bicarp 就会在右半边处加$9$，拉回距离。

最后只剩下一边有$?$。不妨设左半边仍有$k$个问号。

如果$\text{sum}_0>\text{sum}_1$，显然 Monocarp 赢。

否则就是一个对决时刻，设$\text{sum}_0-\text{sum}_1=D$。

这其实就是经典的取火柴问题。但是现在我们取火柴的次数是固定的。

如果$D\bmod9\not=0$，那么一定是 Monocarp 赢（取火柴问题的结论）。

否则和取火柴问题一样，如果 Monocarp 取$x$，Bicarp 取$9-x$即可。

可以发现只有$\frac {9k}2=D$时才会赢。证明其实很简单，如果$\frac {9k}2\leq D$，Monocarp 就疯狂取$0$，否则就疯狂取$9$，这样就永远不可能相等了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
/*
*/
#define gc getchar
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int n,cnt[2],sum[2];
char s[1010101];
signed main(){
	n=read();
	scanf("%s",s+1);
	for (int i=1;i<=n;i++){
		char ch=s[i];
		if (i*2<=n){
			cnt[0]+=(ch=='?');
			sum[0]+=(isdigit(ch)?ch-'0':0);
		}else{
			cnt[1]+=(ch=='?');
			sum[1]+=(isdigit(ch)?ch-'0':0);
		}
	}
	ll det=min(cnt[0],cnt[1]);
	cnt[0]-=det,cnt[1]-=det;
	int op=(cnt[0]==0?1:0);
	sum[op]+=cnt[op]/2*9;
	puts(sum[1]!=sum[0]?"Monocarp":"Bicarp");
	return 0;
}
```

其实有更加小清新的结论，是$ljc$考场上猜的（就是官方题解）：

设左半边有$cnt_0$个$?$，右半边有$cnt_1$个$?$

$Bicarp$能赢当且仅当$\text{sum}_0+\frac {9cnt_0}2=\text{sum}_1+\frac {9cnt_1}2$

其实本质上是一样的，就是约掉了两边都取$9$的部分而已。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
/*
*/
#define gc getchar
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int n,cnt[2],sum[2];
char s[1010101];
signed main(){
	n=read();
	scanf("%s",s+1);
	for (int i=1;i<=n;i++){
		char ch=s[i];
		if (i*2<=n){
			cnt[0]+=(ch=='?');
			sum[0]+=(isdigit(ch)?ch-'0':0);
		}else{
			cnt[1]+=(ch=='?');
			sum[1]+=(isdigit(ch)?ch-'0':0);
		}
	}
	sum[0]+=cnt[0]/2*9,sum[1]+=cnt[1]/2*9;
	puts(sum[1]!=sum[0]?"Monocarp":"Bicarp");
	return 0;
}
```


---

## 作者：caidzh (赞：4)

一道比较好想的博弈论？~~反正我是想了好久~~

下面都是个人理解，如果有问题请私信我

首先考虑一种比较容易想的情况，如果一开始两边和就相等，那么双方就要保证在两边放的数的和是相等的。实际上只有在两边的$?$数相等时才能成立，这是很好理解的，因为$Monocarp$可以把相等局势破坏，而$Bicarp$只能填先手的坑（$Monocarp$一旦填上$9$，$Bicarp$只能填$9$补回），如果两边不等，说明只要一边被填满，另一边$Monocarp$必定对于这个相等状态先手，随意破坏局势即可

那么如果两边和不等，接下来$Bicarp$的任务就是将填入的数两边之差变为$|sumr-suml|$，那么对于$Monocarp$来说只要每次都在和大的一边填上$9$拉大差距，接下来对于$Bicarp$来说就只能在和小的一边填上$9$来弥补

所以我们可以知道最后的状态肯定是其他$?$都是$9$，仅仅只有左区间和右区间其中一个有若干个$?$，那么接下来的问题不就是$Monocarp$先手，轮流取$0-9$中的数，使得和为$|sumr-suml|$嘛！这是个很经典的问题，请读者自己思考

代码如下：
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define INF 2147483647
#define LLINF 9223372036854775807
#define LL long long
#define xyx AKIOI
#define Dilute AKIOI
#define Chtholly_Tree AKIOI
#define time_interspace AKIOI
#define memset0 AKIOI
#define Isonan AKIOI
#define Sooke AKIOI
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
int n,totl,totr,suml,sumr;
int main()
{
	n=read();
	for(int i=1;i<=n/2;i++){
		char c;cin>>c;
		if(c!='?')suml+=c-'0';else totl++;
	}
	for(int i=1;i<=n/2;i++){
		char c;cin>>c;
		if(c!='?')sumr+=c-'0';else totr++;
	}
	if(suml<sumr){
		int ans=sumr-suml,num=(totl-totr)/2;
		if(num*9==ans)printf("Bicarp");else printf("Monocarp");
	}
	if(sumr<suml){
		int ans=suml-sumr,num=(totr-totl)/2;
		if(num*9==ans)printf("Bicarp");else printf("Monocarp");
	}
	if(suml==sumr){
		if(totl!=totr)printf("Monocarp");else printf("Bicarp");
	}
	return 0;
}
```


---

## 作者：YouXam (赞：2)

# 题解

三种情况

1. 如果最开始左半部分数字之和等于右半部分数字之和,左右问号数量相等Bicarp赢;数量不等Monocarp赢.

应该很好理解,Monocarp先手,无论Monocarp填什么,Bicarp的最优策略都是在另一边填一样的,这样可以一直保证左右数字之和相等,因为Bicarp最后一个填,所以Bicarp赢.

当然,如果数量不等,Bicarp自然赢不了.

--------

**当两边数字和不等,且Monocarp可以在数字和大的部分填数字时,他一定会填9以拉开差距,那么Bicarp如果能在另半部分填,一定也会填9.**

**这就是两部分的问号不断抵消的情况,抵消到只有一边有问号为止,这时候就可以继续思考了,下面所有情况都是假定只有一边有问号**

2. 如果左半部分数字之和大于右半部分数字之和

若只有左边有问号,无论Bicarp如何决策也无法使左半部分减少,右半部分又无法增加,那么Monocarp赢

若只有右边有问号,那么Monocarp一定会填0拉开差距,而Bicarp一定会填9,那么看一下Bicarp能填的数量即可,若能填$n$个问号,$n \times 9$与左右之差相等,Bicarp赢,反之Monocarp赢.

注意写代码时,"只有左边有问号"的情况可以和"只有右边有问号"的情况合并,因为这时候看作右边的问号数量为负数即可,为负数肯定无法与正数的数量差相等,Monocarp赢一定会赢.


3. 如果左半部分数字之和小于右半部分数字之和

可以看作为第2种情况的镜像,同理可以解决

# 代码

```cpp
#include <bits/stdc++.h>
#define t(i) int(((double)(i) / (n)) + 0.5)
using namespace std;
char s[200005];
int main() {
    int n, mark[2] = {0, 0}, sum[2] = {0, 0};
    scanf("%d%s", &n, s);
    for (int i = 0; i < n; i++)
        if (s[i] == '?') mark[t(i)]++;
        else sum[t(i)] += s[i] - '0';
    puts((mark[0] == mark[1] && sum[0] == sum[1] ||
          sum[0] > sum[1] && sum[0] - sum[1] == (mark[1] - mark[0]) / 2 * 9 ||
          sum[1] > sum[0] && sum[1] - sum[0] == (mark[0] - mark[1]) / 2 * 9) ? "Bicarp" : "Monocarp");
    return 0;
}
```

---

## 作者：弦巻こころ (赞：1)

~~我的蓝名就这么离我而去了!~~

###### 写完后发现我sb了不用写那么复杂就又重写了一遍

这道题是个~~简单(duliu~~)的思路题.每次写思路题我都要被叉,我太难了.

我猜有人会交翻译就~~懒得写翻译~~ 直接说思路就是了.

我们第一步要做的就是记录下前半部分问号个数与数值和 和 后半部分问号个数与数值和.

处理好这个后我们就开始判断.

首先我们要明确的是因为Monocarp先取所以如果有奇数步的话,Monocarp就一定赢.

然后我们就将问号和相减 * 9 如果它等于数值和之差,拿就输出Bicarp.如果不等,就输出Bicarp.

为什么呢?

如果两边都有? Bicarp可以复制Monocarp的操作使得差值不变,当只有一边有问号的时候,显然我们可以将每一轮操作的和控制为9.所以就得出结论了

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005];
int n;
int can1,can2,bc;
int sum;
int main()
{
	cin>>n>>s;
	for(int i=0;i<n/2;i++)
	{
		if(s[i]=='?')
		{
			can1++;
		}else
		{
			sum+=s[i]-'0';
		}
	}
	for(int i=n/2;i<=n-1;i++)
	{
		if(s[i]=='?')
		{
			can2++;
		}else
		{
			sum-=s[i]-'0';
		}
	}//前面是预处理
	if((can1+can2)%2==1)//如果为奇数
	{
		cout<<"Monocarp";
		return 0;
	}
	bc=(can2-can1)/2*9;//计算差值
	if(bc==sum)//比较
	{
		cout<<"Bicarp";
		return 0;
	}else
	{
		cout<<"Monocarp";
		return 0;
	}
    return 0;
}
```
听说CYJian神仙 Rank16上橙了%%%%

---

## 作者：Ofnoname (赞：1)

先手希望两边不等，后手希望两边相等

我们把字符串分为左右两半，用左边的数字和减去右边的数字和得到`sum`，左边的问号相当于增加`sum`的机会(0~9)，右边的问号相当于减少`sum`的机会。显然左右问号可以互相抵消，那么设左边问号减右边问号数目为`mx`。

若mx和sum同号（比如和大于0,左边问号还多），那么显然是不可能相等的，Monocarp胜。

否则就是一个取石子问题了，若sum为9的先手的步数倍（刚好可以取完）并且mx为偶数（这样可以保证正负抵消后Bicarp先），那么Bicarp嬴，否则Monocarp胜。

0可以特判一下。

```cpp
#include <bits/stdc++.h>
#define MAX (200000 + 7)
using namespace std;

long long N,sum,mx,ma,mb;
char c[MAX];

int main()
{
	cin >> N >> c;
	for (int i = 0; i < N>>1; i++)
		c[i]=='?' ? mx++ : sum += c[i]&15;
	for (int i = N>>1; i < N; i++)
		c[i]=='?' ? mx-- : sum -= c[i]&15;
	if(!mx)
	{
		puts(sum?"Monocarp":"Bicarp");
		return 0;
	}
	if (mx * sum > 0)
	{
		puts("Monocarp");
		return 0;
	}
	sum = sum>0 ? sum : -sum;
	mx = mx>0 ? mx : -mx;
	mb = mx >> 1, ma = mx - mb;
	if (ma * 9 != sum)
	{
		puts("Monocarp");
		return 0;
	}
	if (ma != mb)
	{
		puts("Monocarp");
		return 0;
	}
	puts("Bicarp");
}

```

---

## 作者：hzoi_liuchang (赞：1)


## 分析

**一句话题意：一张票有n位数，如果这张票的前一半数字的和等于后一半数字的和(n一定是偶数)，就称这张票为快乐票。有些数被擦除了，标记为’?’(’?‘的个数也是偶数)，现在Monocarp 和 Bicarp 进行一个游戏，两人轮流将’?'变换成0到9的任意一个数，Monocarp先手，如果最后票为快乐票则Bicarp赢，否则Monocarp赢。**

我们分情况来考虑一下

1、左边的数字之和等于右边的数字之和

这时，如果左右两边$'？'$的个数相等的话，后手赢，因为先手无论放什么数，后手都可以放一个相同的数来平衡

如果不相等，则先手必胜，因为最后肯定只能在一边放，只要先手能放，就一定会打破平衡

2、左边的数字之和小于右边的数字之和

如果左边$'？'$的个数大于等于右边的个数，那么先手必胜，因为先手可以一直在左边放9，后手只能不断在右边放9维持差距，但始终不能弥补差距

如果左边$'？'$的个数小于右边的个数，我们设左边$'？'$的个数为a，右边$'？'$的个数为b，那么前2a回合，策略同上；2a回合之后，先手放一个数x，后手唯一的选择就是放一个y，使x+y=9，所以当左右两边数字之差为9的倍数时，后手胜，否则先手胜

3、右边的数字之和小于左边的数字之和（同上）

## 代码

``` cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
char c[300000];
int lefw,rigw,lef,rigt;
int main(){
    int n;
    scanf("%d",&n);
    getchar();
    for(int i=1;i<=n/2;i++){
        scanf("%c",&c[i]);
        if(c[i]=='?'){
            lefw++;
        } else {
            lef+=(c[i]-'0');
        }
   }
   for(int i=n/2+1;i<=n;i++){
        scanf("%c",&c[i]);
        if(c[i]=='?'){
            rigw++;
        } else {
            rigt+=(c[i]-'0');
        }
   }
   if(lef==rigt){
        if(lefw==rigw) printf("Bicarp\n");
        else printf("Monocarp\n");
    }
    else if(lef>rigt){
       int cha=rigw-lefw;
       if(cha<=0){
            printf("Monocarp\n");
            return 0;
       }
       int chaa=lef-rigt;
       if(cha%2==0 && cha/2*9==chaa) printf("Bicarp\n");
        else printf("Monocarp\n");
    } else {
        int cha=lefw-rigw;
       if(cha<=0){
            printf("Monocarp\n");
            return 0;
       }
       int chaa=rigt-lef;
       if(cha%2==0 && cha/2*9==chaa) printf("Bicarp\n");
        else printf("Monocarp\n");
    }
    return 0;
}
```


---

## 作者：世末OIer (赞：1)

~~蛤蛤蛤蛤这题还能作为D2D,我昨晚A了A后，花了5min就解决了~~

---

我们可以知道，后手如果可以确定一个数（前后的差），那么只能是9*(差的"?"数/2)

运用博弈的思想，无论你置换成那个数，都可以通过再置换一个9-那个数来护额的9的和


```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
#define endl '\n'
using namespace std;
int n;
string s;
int main(){
	cin>>n>>s;
	int sm0=0,sm1=0,wh0=0,wh1=0;
	for(int i=0;i<s.size()/2;++i){ //统计问号的个数和和
		if(s[i]=='?')++wh0;
		else sm0+=s[i]-'0';
	}
	for(int i=s.size()/2;i<s.size();++i){
		if(s[i]=='?')++wh1;
		else sm1+=s[i]-'0';
	}
	int t=min(wh0,wh1);  //可以先抵消掉
	wh0-=t,wh1-=t;
	if((wh0+wh1)%2==1){ //无法确定
		cout<<"Monocarp\n";
		return 0;
	}
	if(!wh0 and !wh1){
		if(sm0==sm1)cout<<"Bicarp\n";
		else cout<<"Monocarp\n";
		return 0;
	}
	if(wh0){
		if(sm0>=sm1){
			cout<<"Monocarp\n";
			return 0;
		}
		int cha=sm1-sm0;
		if(cha==9*(wh0/2)){
			cout<<"Bicarp\n";
		}else cout<<"Monocarp\n";
	}else{
		if(sm1>=sm0){
			cout<<"Monocarp\n";
			return 0;
		}
		int cha=sm0-sm1;
		if(cha==9*(wh1/2)){
			cout<<"Bicarp\n";
		}else cout<<"Monocarp\n";
	}
}
```

---

## 作者：开始新的记忆 (赞：0)

题目大意：现在给你n个位置（n%2==0），每个位置上要么有数（0~9），要么为‘？’，现在有两个人Monocarp和Bicarp，Bicarp想令前n/2位数的各位数之和等于后n/2位数的各位数字之和，而Monocarp不想。现在由Monocarp先手，每次操作可以令其中一个‘？’改成0~9中的一个数，问如果Bicarp可以保证最后的和相等，输出Bicarp，反之则输出Monocarp。

大致思路：先计算前n/2位的和 和‘？’的个数，然后统计后n/2位的和 和‘？’的个数。设两个数的和为ans1，ans2，‘？’的个数为num1，num2，我们假设每次Monocarp把一个‘？’改成了9，然后Bicarp也进行同样的操作，最后结果不变，但是数值变小。若ans1>ans2 && ans1-ans2>(num2-num1)*9，代表bicarp不可能胜利，其他情况则都是Bicarp胜利。

code：

```
#include<bits/stdc++.h>
using namespace std;
int n,ans1=0,ans2=0,num1=0,num2=0;
string a;
 
int main()
{	cin>>n>>a;
	for(int i=0;i<a.size()/2;++i)
	{
		if('0'<=a[i] && a[i]<='9')
			ans1+=a[i]-'0';
		else
			num1++;
	}
	for(int i=a.size()/2;i<a.size();++i)
	{
		if('0'<=a[i] && a[i]<='9')
			ans2+=a[i]-'0';
		else
			num2++;
	}
	while(ans1>9 && num2>2)
		ans1-=9,num2-=2;
	while(ans2>9 && num1>2)
		ans2-=9,num1-=2;
	if(ans1==ans2 && num1==num2)
		cout<<"Bicarp"<<endl;
	else if(ans1-ans2>(num2-num1)/2*9 || ans2-ans1>(num1-num2)/2*9)
		cout<<"Monocarp"<<endl;
	else
		cout<<"Bicarp"<<endl;
	return 0;
}
```


---

## 作者：DarthVictor (赞：0)

# 题目
[原题链接](https://www.luogu.com.cn/problem/CF1215D)
# 解说
## 前置
翻译什么的链接里已经说的很清楚了,这里不再赘述,看题吧。

~~一看见这博弈论模样的题就知道又是思维题了。~~

设身处地想一想，假如你是游戏里的人你会怎么让自己赢。首先，开局时左右两边数字和肯定有一个大小关系，假如我是$Monocarp$,我先手，我肯定会在大的一边把$?$改成$9$以拉大差距,而接下来的$Bicarp$最好的策略就是先在小的一边把$?$改成$9$补回差距。

基本战略确定了，接下来就能讨论了。

根据上面的推论，我们基本可以确定首先要统计两边开局的数字和以及问号个数。

```cpp
	cin>>n>>s+1;
	for(int i=1;i<=n/2;i++){
		if(s[i]!='?') suml+=s[i]-'0';
		else l+=1;
	}
	for(int i=n/2+1;i<=n;i++){
		if(s[i]!='?') sumr+=s[i]-'0';
		else r+=1;
	}
```
P.S. 下面说明情况都是在排除了已经给出的情况之后。
## 情况一
我能想到的最简单情况就是两边开局就相等，这时只有两边问号也相等$Bicarp$才能胜利。为什么？~~显然~~问号不相等的话$Monocarp$在一边加了数$Bicarp$无法在另一边用等量的问号补齐，自然无法平衡。

```cpp
	if(suml==sumr){
		if(l==r) cout<<"Bicarp";
		else cout<<"Monocarp";
		return 0;
	}
```

## 情况二
既然开局两边不平衡，那么假如这时两边问号相等会怎么样？

$Monocarp$会在大的一边加$9$，$Bicarp$又在小的一边补$9$，由于问号数相等，最后左右的两边问号都用完了两边的数量差还是没变，因此$Monocarp$赢。

```cpp
	if(l==r){
		cout<<"Monocarp";
		return 0;
	}
```

## 情况三
现在我们进行到左右大小不等，问号也不等的情况了，那么很容易想到两个分支，第一种是一边数大问号也多，另一种是一边数大但是问号少。情况三我们讨论第一种。

首先两个人左一个$9$右一个$9$把一边的问号消耗完了，但是两边数字差没有丝毫变化，这时只有数字大的一边有问号了，$Bicarp$无法在数小的一边补$9$填坑，无力回天，只可能是$Monocarp$赢。

```cpp
	if((sumr>suml&&r>l)||(suml>sumr&&l>r)){
		cout<<"Monocarp";
		return 0;
	}
```

## 情况四
最后的最恶心的情况：一边数大但是问号少，另一边数少问号多。

首先肯定还是两个人一次左一次右把一边的$?$消完了，大的一边没问号了，只有小的有，也就是说我们可以把初始情况看成两边的差还是原来的差，但是只有小的一边有数量为$abs(l-r)$个问号。这时两人会怎么做？显然$Monocarp$操作会把问号变为$0$尽力阻止小的一边扩张，而$Bicarp$会在还没有超越界限的前提下尽量补$9$让小的追上大的一边。也就是说每过一轮就消去两个问号，同时，差减九。

```cpp
	int a=abs(suml-sumr),b=abs(l-r);
	while(1){
		a-=9;
		b-=2;
		if(a<0||b<0) break;
	}
	a+=9; b+=2;
```

这时再分出两个情况：$b==1$和$b==0$。

若是$b$为一，则说明只剩一个问号了。由于前面都是偶数次消除，现在该$Monocarp$了，他可以随意加一个数反正只要不让和相等就行了，肯定赢。（这是我做的时候忽略了问号个数为偶数想到的情况，问号为偶数的话这应该是不成立的，但是反正加上也没事是吧那就加上吧）

若$b$为零，则说明两边都没问号了，谁都无法操作了，那我们就看两边平没平决胜负就行了。

```cpp
	if(!b){
		if(a!=0) cout<<"Monocarp";
		else cout<<"Bicarp";
	}
	else cout<<"Monocarp";
```

# 代码
把上面那一大堆拼起来就行。
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=2000000+5;
char s[maxn];
int n,suml,sumr,l,r;
int main(){
	cin>>n>>s+1;
	for(int i=1;i<=n/2;i++){
		if(s[i]!='?') suml+=s[i]-'0';
		else l+=1;
	}
	for(int i=n/2+1;i<=n;i++){
		if(s[i]!='?') sumr+=s[i]-'0';
		else r+=1;
	}
	if(suml==sumr){
		if(l==r) cout<<"Bicarp";
		else cout<<"Monocarp";
		return 0;
	}
	if(l==r){
		cout<<"Monocarp";
		return 0;
	}
	if((sumr>suml&&r>l)||(suml>sumr&&l>r)){
		cout<<"Monocarp";
		return 0;
	}
	int a=abs(suml-sumr),b=abs(l-r);
	while(1){
		a-=9;
		b-=2;
		if(a<0||b<0) break;
	}
	a+=9; b+=2;
	if(!b){
		if(a!=0) cout<<"Monocarp";
		else cout<<"Bicarp";
	}
	else cout<<"Monocarp";
	return 0;
}
```

# 尾声
大家可能会发现情况二三就是情况四的特殊情况，用情况四的代码稍作修改判断也可以，但是能提前结束谁想用到$while$呢？

幸甚至哉，歌以咏志。

---

## 作者：RiverFun (赞：0)

非常不错的一道博弈论题目，模型有点像Bash博弈。

首先这道题我们可以这么理解：有两堆石头，其中一堆有 $x$ 个石头，只能放 $n$ 次石头，每次能放的石头数量不超过 $9$ 个，另一堆有 $y$ 个石头，能放 $m$次，每次能放的石头数量也不超过 $9$ 个。每次操作可以放 $0$ 个石头 。先手后手轮流操作，两堆石头都可以放，如果两堆石头能放的次数用完了，当且仅当两堆石头个数相等时后手赢，问后手是否有必胜策略。

根据题意我们可以得出这样一个结论：当且仅当 $n=m$ 以及 $x=y$ 时，后手必赢。

所以我们为了达到这个局面，必须要让其中一堆石头的个数小于另一堆石头并且这一堆石头能放的次数大于另一堆石头，或者是两堆石头的石头个数以及能放的次数均相等。

我们再来看题目，题目中说了 $n + m$ 是偶数，所以又可以得出 $|n - m|$ 一定是偶数。

所以如果出现了 $n < m$ 且 $x > y$ 的局面，要想让后手必赢，必须满足 $x - y = 9 * (m - n)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200010
char a[MAXN];
int n, p, q, x, y;
int main() {
	scanf("%d", &n);
	scanf("%s", a + 1);
	for (int i = 1; i <= n / 2; i++) {
		if (a[i] != '?') p += a[i] - '0';
		else x++;
	}
	for (int i = n / 2 + 1; i <= n; i++) {
		if (a[i] != '?') q += a[i] - '0';
		else y++;
	}
	if (x < y) std::swap(x, y), std::swap(p, q);
	if (p > q) {
		puts("Monocarp");
		return 0;
	}
	if (p == q && x == y) {
		puts("Bicarp");
		return 0;
	}
	x -= y;
	q -= p;
	if (q == (x / 2) * 9) {
		puts("Bicarp");
		return 0;
	}
	else {
		puts("Monocarp");
		return 0;
	}
}

```


---

## 作者：little_sun (赞：0)

我们定义$sum_{left}=$左半部分已知数的和，$sum_{right}=$右半部分已知数的和;

定义$cnt_{left}$=左半部分`?`的个数，$cnt_{right}=$右半部分`?`的个数

那么我们通过分析题目发现：`Bicarp`胜利当且仅当
$9 \times cnt_{left} + 2 \times sum_{left} = 9 \times cnt_{right} + 2 \times sum_{right}$

然后依题意模拟即可


``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) ((a + b) % mod)

const int MaxN = 3e5 + 10;

int n;
char s[MaxN];

int main()
{
    scanf("%d", &n), scanf("%s", s + 1);
    int d = 0;
    for (int i = 1; i <= n / 2; i++)
    {
        if (s[i] == '?')
            d += 9;
        else
            d += (s[i] - '0') * 2;
    }
    for (int i = (n / 2) + 1; i <= n; i++)
    {
        if (s[i] == '?')
            d -= 9;
        else
            d -= (s[i] - '0') * 2;
    }
    printf(d ? "Monocarp" : "Bicarp");
    return 0;
}
```

---

## 作者：Thaumaturge (赞：0)

你表面上看是毒瘤博弈论

其实是一道 * * 模拟

对于序列左右端，显然Monocarp必须要选一半，全部填9，另外一半全部填0才能保证Bicarp使序列两端平衡的可能性最小。

左右两边都试一遍都行了,$O(n)$的

```cpp
#include <bits/stdc++.h>

#define N 200010

using namespace std;

int leftq,rightq;
int leftn,rightn;

int ans1,ans2;

int n,tot,cnt;
char s[N];

bool flag;

int main(){
	scanf("%d %s",&n,s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='?')
		{
			tot++;
			if(i<=n/2)
			leftq++;
			else
			rightq++;
		}
		else {
		if(i<=n/2)
		leftn+=s[i]-'0';
		else
		rightn+=s[i]-'0';
		}

	}


	cnt=tot-tot/2;

	ans1=leftn+(cnt<leftq?cnt*9:leftq*9);
	ans2=cnt<leftq?rightq:rightq-(cnt-leftq);
	if(ans1-rightn>ans2*9) flag=1;
	
	swap(leftn,rightn),swap(leftq,rightq);
	
	ans1=leftn+(cnt<leftq?cnt*9:leftq*9);
	ans2=cnt<leftq?rightq:rightq-(cnt-leftq);
	if(ans1-rightn>ans2*9) flag=1;
	
	if(flag)	puts("Monocarp");
	else		puts("Bicarp");
	return 0;
}
```


---

## 作者：xukuan (赞：0)

博弈论

对于前半部分和后半部分，统计“？”的个数(x)和数的和(y)

性质：两个“？”的话，后手方能且仅能把和控制成9

结论：如果x/2\*9=y那么B开头的赢，否则M开头的赢

另外，班里三个人最后FST（WA#23），来组数据

```pascal
6
12????
```

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,sum,que;
string s;

inline void winfront(){
	cout<<"Monocarp"<<endl;
	exit(0);
}

inline void winback(){
	cout<<"Bicarp"<<endl;
	exit(0);
}

int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	cin>>s;
	for(ll i=0; i<n/2; i++){
		if(s[i]=='?') que++;
		else sum+=s[i]-48;
	}
	for(ll i=n/2; i<n; i++){
		if(s[i]=='?') que--;
		else sum-=s[i]-48;
	}
	if(que/2*9+sum==0) winback();
	else winfront();
	return 0;
}
```

---

