# [EC Final 2021] Prof. Pang and Poker

## 题目描述

庞教授正在和他的两个朋友 Alice 和 Bob 玩纸牌游戏。所有的牌都从一副标准的 52 张牌的牌堆中抽取。一副标准的 52 张牌的牌堆由四种法式花色中的 13 个等级组成：梅花 ($\clubsuit$)、方块 ($\diamondsuit$)、红心 ($\heartsuit$) 和黑桃 ($\spadesuit$)。每种花色包括一张 A（Ace）、一张 K（King）、一张 Q（Queen）和一张 J（Jack），每张牌旁边都有其花色的符号；以及从 2 到 10 的数字牌，每张牌上都有相应数量的花色符号（点数）。**没有一张牌可以被抽取多于一次。**

![](https://cdn.luogu.com.cn/upload/image_hosting/3xtu6g4z.png)

单张牌的等级如下（从高到低）：A、K、Q、J、10、9、8、7、6、5、4、3、2。**花色不影响牌的等级。**例如，方块 A 和梅花 A 具有相同的等级。它们之间没有一个严格高于另一个。

最初，Alice 和 Bob 将持有一张或多张牌，而庞教授将持有恰好一张牌。**每个玩家可以看到自己和其他玩家持有的牌。**他们将按照以下多轮规则进行游戏：

- 先手玩家选择一张牌并打出以开始一轮。
- 下一个玩家可以选择过牌或打出新牌，然后下一个玩家也可以选择过牌或打出新牌，依此类推。唯一的限制是，新打出的牌的等级必须严格高于本轮中所有之前的牌。
- 当两名玩家连续选择过牌时，本轮结束。最后打出牌的玩家在下一轮中成为先手玩家。
- 如果有人打出了手中的所有牌，游戏立即结束。

在这个游戏中，Alice 是第一轮的先手玩家。Bob、庞教授和 Alice 分别是 Alice、Bob 和庞教授的下一个玩家。庞教授只有在他是第一个打出所有牌的人时才会感到高兴。（庞教授当然想要高兴。）Alice 想喝奶茶，所以她决定让庞教授高兴，然后让他给她买奶茶。然而，Bob 不想让这种情况发生，所以他决定避免庞教授感到高兴。如果他们都为自己以最佳方式玩游戏，庞教授最后会高兴吗？

## 说明/提示

- 对于第一个案例，庞教授总是可以打出他唯一的牌 “4S”。
- 对于第二个案例，无论 Alice 在第一轮打出什么牌，Bob 都可以打出 “4D” 并在第二轮成为先手玩家，然后 Bob 打出 “3H”，游戏结束。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
2 2
2H 2D
3H 3D
4S
2 2
2H 2D
3H 4D
4S```

### 输出

```
Pang
Shou```

# 题解

## 作者：Wilderness_ (赞：3)

题目链接：[Luogu](https://www.luogu.com.cn/problem/P9876)

### 题意
~~（竟然是卢本伟的翻译~~ 

题面意思其实就是三人打一种花色不计、只出单牌的斗地主。牌面数字或字母从小到大依次为 $2,3,4,5,6,7,8,9,\texttt{T},\texttt{J},\texttt{Q},\texttt{K},\texttt{A}$。现在 Prof.Pang（也就是题面中的卢本伟，后称 P）、Alice（即题面中的舒克，后称 A）、Bob（即题面中的贝塔，后称 B）三人打牌，A 和 P 希望 P 赢，B 希望 A 或 B 赢，现在给出每个人手上的牌，问绝顶聪明时（最优策略时） P 能否赢。

### 思路
分类讨论（只有这么大的分类讨论才可能评蓝吧）。

我们现将 $\texttt{T},\texttt{J},\texttt{Q},\texttt{K},\texttt{A}$ 对应为 $10,11,12,13,14$，且设 $n$ 为 A 手中的牌数，$m$ 为 B 手中的牌数，$A[i]$ 是 A 第 $i$ 大的手牌，$B[i]$ 是 B 第 $i$ 大的手牌，$B_{Smaller}$ 表示 B 比 P 小的牌数，$A_{No}$ 表示 A 比 P 大的牌，$A_{Max}$ 表示 A 比 P 小的牌中最大的那一张。

1. 当 A 手里只剩一张牌时（即 $n=1$ 时），那么 A 一出牌游戏就会结束，P 不可能胜利；
2. 当 A 手里剩的牌都比 P 的大时（即 $A_{No}=n$ 时），那么 A 不论怎么出 P 都不可能出掉手里的牌，P 不可能胜利；
3. 当 B 手里的牌有至少 $2$ 张比 P 的牌小时（即 $B_{Smaller} \ge 2$ 时），那么他出牌时一定会有一次出牌使得 P 手上的牌能够出掉，P 一定胜利；
4. 当 B 手里的牌全部比 P 手上的牌大时（即 $B_{Smaller} = 0$ 时），那么 A 怎么出都会被 B 出的牌压住，使得 P 无法出掉手中的牌，P 不可能胜利；
5. 当 B 只剩一张牌时（即 $m=1$ 时）：

   1.如果 A 有比 B 大的牌，但比 P 小的牌（即 $A_{Max}\ge B[1]$ 时），那么只要 A 出那张比 B 大的牌，但比 P 小的牌，就可以让 P 出完牌，P 一定胜利；
   
   2.如果 A 没有比 B 大的牌，但比 P 小的牌（即 $A_{Max}< B[1]$ 时），那么 A 出大于等于 P 的牌 P 出不出去，出小于 P 的牌又会让 B 出完，P 不可能胜利；
   
6. 如果 A 只有一张牌比 P 小（即 $A_{No}=n-1$ 时），那么 A 出大于等于 P 的牌 P 出不出去，出小于 P 的牌又会被 B 压住，P 不可能胜利；

7. 当 A 的最大牌大于 B 的最大牌，A 比 P 小的牌中最大的那一张牌大于等于 B 最小的那一张牌，同时 A 至少有 $4$ 张牌时（即 $A[n]>B[m]$ 且 $A_{Max} \ge B[1]$ 且 $n \ge 4$ 时），A 只要出一张 $A[1]$，这时 B 就要用大牌压住A 来不让 P 出完。之后 A 和 P 等到 B 出掉所有大牌，A 再出 $A[n]$ 压住 B，这时 A 再出 $A_{Max}$，而 B 并没有更大的牌，P 就可以出完，P 一定能赢。
8. 其余情况，P 都不可能赢。

### Code:
```
#include<bits/stdc++.h>
#define M 114514
using namespace std;
int T,n,m,Shook[M],Beta[M],LBW;
string Pokers;
int Poker_to_Number(char ch)
{
	switch(ch)
	{
		case 'T':return 10;
		case 'J':return 11;
		case 'Q':return 12;
		case 'K':return 13;
		case 'A':return 14;
		default:return ch-'0';
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)cin>>Pokers,Shook[i]=Poker_to_Number(Pokers[0]);
		sort(Shook+1,Shook+n+1); 
		for(int i=1;i<=m;i++)cin>>Pokers,Beta[i]=Poker_to_Number(Pokers[0]);
		sort(Beta+1,Beta+m+1);
		cin>>Pokers,LBW=Poker_to_Number(Pokers[0]);
		int Beta_Smaller=0,Shook_Max=0,Shook_No_Use=0;
		for(int i=1;i<=m;i++)Beta_Smaller+=(Beta[i]<LBW?1:0);
		for(int i=1;i<=n;i++)
		{
			if(Shook[i]>=LBW)Shook_No_Use++;
			else Shook_Max=max(Shook_Max,Shook[i]);
		}
		if(n==1)//case 1:当舒克手里只剩一张牌时，他一出游戏就结束，卢本伟不可能胜利。 
		{
			printf("Shou\n");continue;
		}
		if(Shook_No_Use==n)//case 2:当舒克手里剩的牌都比卢本伟的大时，他怎么出卢本伟都不可能出掉手里的牌。 
		{
			printf("Shou\n");continue;
		}
		if(Beta_Smaller>=2)//case 3:当贝塔手里的牌有至少2张比卢本伟的牌小时，那么他出牌时一定会有一次出牌使得卢本伟手上的牌能够出掉 
		{
			printf("Pang\n");continue;
		}
		if(Beta_Smaller==0)//case 4:当贝塔手里的牌全部比卢本伟手上的牌大时，那么舒克怎么出都会被贝塔出的牌压住，使得卢本伟无法出牌 
		{
			printf("Shou\n");continue;
		}
		if(m==1)
		{
			if(Shook_Max>=Beta[1])//case 5.1:当贝塔只剩一张牌时，如果舒克有比贝塔大的牌，但比卢本伟小的牌，那么卢本伟能出完 
			{
				printf("Pang\n");continue;
			}
			else//case 5.2:否则贝塔一定比卢本伟先出完 
			{
				printf("Shou\n");continue;
			}
		}
		if(n-Shook_No_Use==1)//case 6:如果舒克只有一张牌比卢本伟小，那么他会先出较大的牌来防止贝塔出完，使得卢本伟比舒克晚出完 
		{
			printf("Shou\n");continue;
		}
		//case 7:就是舒克用小牌先钓出贝塔的打牌，后等到贝塔手中牌均比卢本伟小时，舒克压住贝塔，再打一张大于贝塔手中牌且小于卢本伟手中的牌 
		if(Beta[m]>=Shook[n])
		{
			printf("Shou\n");continue;
		}
		if(Shook_Max>=Beta[1]&&n>3)
		{
			printf("Pang\n");continue;
		}
		else//case 8:其余情况 
		{
			printf("Shou\n");continue;
		}
	}
}

```

---

## 作者：Diaоsi (赞：1)

[Prof. Pang and Poker](https://www.luogu.com.cn/problem/P9876)

邪恶分讨/fn/fn/fn

花色没有用可以丢掉了，以下默认牌大小为 $1\sim 13$ ，设教授拿的牌为 $x$，对于 Alice 和 Bob 拿的所有牌：

Alice 和 Bob 的总牌数分别记为 $N_A$ 和 $N_B$，将 Alice 手上 $< x$ 的牌的个数记为小 $A$，$\geq x$ 的牌记的个数为大 $A$，小 $B$ 和大 $B$ 同理，然后进行分类讨论。

**第一种情况：** 小 $B=0$

此时教授必败，因为无论 Bob 出什么牌教授都接不了，所以教授无法出牌。

**第二种情况：** 小 $B\geq 2$

1. 当小 $A\geq1$ 且 $N_A\geq2$ 时，教授必胜
1. 当小 $A=0$ 时，教授必败
1. 当 $N_A=1$ 时，教授必败

**第三种情况：** 小 $B=1$

将此时的唯一一个小 $B$ 记为 $y$，然后对小 $A$ 继续分类，将大小在 $[1,y-1]$ 范围内的 $A$ 记为小小 $A$，大小在 $[y,x-1]$ 范围内的 $A$ 记为中小 $A$。

将 Alice 和 Bob 的手牌中最大的两张牌记为 $M_A$ 和 $M_B$ ，满足以下**任一**条件时，教授必胜。

1. $N_A\geq 4$ 且中小 $A\geq 1$ 且 $M_A>M_B$ 且小 $A\geq 2$
1. $N_B\geq 4$ 且中小 $A\geq 1$ 且 $N_A\geq 2$

否则教授必败。

Code:

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,na,nb,x,y,a[N],b[N];
int a0,b0,a1,b1,a00,a01,ma,mb;
char s[10];
void calc(int &x){
	scanf("%s",s+1);
	if(s[1]=='2')x=1;
	if(s[1]=='3')x=2;
	if(s[1]=='4')x=3;
	if(s[1]=='5')x=4;
	if(s[1]=='6')x=5;
	if(s[1]=='7')x=6;
	if(s[1]=='8')x=7;
	if(s[1]=='9')x=8;
	if(s[1]=='T')x=9;
	if(s[1]=='J')x=10;
	if(s[1]=='Q')x=11;
	if(s[1]=='K')x=12;
	if(s[1]=='A')x=13;
}
void solve(){
	a0=b0=a1=b1=a00=a01=ma=mb=0;
	scanf("%d%d",&na,&nb);
	for(int i=1;i<=na;i++)calc(a[i]);
	for(int i=1;i<=nb;i++)calc(b[i]);
	calc(x);
	sort(a+1,a+na+1);
	sort(b+1,b+nb+1);
	ma=a[na];mb=b[nb];
	for(int i=1;i<=na;i++)a[i]<x?a0++:a1++;
	for(int i=1;i<=nb;i++)b[i]<x?b0++:b1++;
	if(!b0){
		puts("Shou");
		return;
	}
	else if(b0>=2){
		if(a0>=1&&na>=2){
			puts("Pang");
			return;
		}
		if(!a0){
			puts("Shou");
			return;
		}
		if(na==1){
			puts("Shou");
			return;
		}
	}
	else{
		for(int i=1;i<=nb;i++)
			if(b[i]<x)y=b[i];
		for(int i=1;i<=na;i++)
			if(1<=a[i]&&a[i]<=y-1)a00++;
			else if(y<=a[i]&&a[i]<=x-1)a01++;
		int flg=0;
		if(na>=4){
			flg|=(a01>=1&&ma>mb&&a0>=2);
		}
		if(nb==1){
			flg|=(a01>=1&&na>=2);
		}
		puts(flg?"Pang":"Shou");
	}
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：xiaobeng_0912 (赞：0)

## $\mathbf{Knowledge}$

1. 分类讨论

## $\mathbf{Solution}$

~~这翻译的挺好啊~~

首先说明一点，中文题面中的卢本伟是英文题面中的 Prof.Pang、舒克是英文题面中的 Alice、贝塔是英文题面中的 Bob。

然后，这道题是个分类讨论，分为以下几类：

1. 如果舒克手中只有一张牌，因为他是第一个出牌的，所以在这种情况下卢本伟不可能赢。
2. 如果舒克最小的牌也比卢本伟大，那么舒克无论怎么出牌卢本伟都没有办法接上，这种情况下卢本伟也不可能赢。
3. 如果贝塔有两张及以上比卢本伟那张牌小的牌，那么他一定会有一次出牌导致卢本伟能够打出自己的牌，在这种情况下卢本伟必胜。
4. 如果贝塔最小的牌也比卢本伟大，那么舒克就通过无法打出一张小牌或者过掉自己的回合来使卢本伟赢，所以这种情况下卢本伟同样不可能赢。
5. 当贝塔只剩一张牌时，如果舒克有至少一张比贝塔大但比卢本伟小的牌，那么舒克只需要出那些牌中的任意一张，就可以让卢本伟出掉他的牌，这种情况下卢本伟必赢。
6. 当贝塔只剩一张牌时，如果舒克没有比贝塔大但比卢本伟小的牌，那么舒克就会发现他无法在贝塔不打完自己的牌的情况下让卢本伟打出自己的牌，这种情况下卢本伟不可能赢。
7. 如果舒克只有一张牌比卢本伟小，那么舒克会发现，他出那张比卢本伟的牌小的牌，会被贝塔给压住；但是如果出比卢本伟大的牌，卢本伟又无法接上，这种情况下卢本伟也不可能赢。
8. 当舒克的最大牌大于贝塔的最大牌，并且舒克比卢本伟小的牌中最大的那一张牌大于等于贝塔最小的那一张牌，同时舒克至少有四张牌时，舒克可以在压制贝塔的同时让卢本伟出掉他的牌，卢本伟也一定能赢。
9. 对于其它的情况，卢本伟不可能赢。


## $\mathbf{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[100001],b[100001],c;
int b_smaller_than_c,a_max_but_smaller_than_c,a_big_than_c;
map <char,int> mp={{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'T',10},{'J',11},{'Q',12},{'K',13},{'A',14}};
string s;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			cin>>s;
			a[i]=mp[s[0]];//字符转化为数字
		}
		sort(a+1,a+n+1);//排序后，能够更快定位最小、大的牌在哪里
		for(int i=1;i<=m;i++){
			cin>>s;
			b[i]=mp[s[0]];//字符转化为数字
		}
		sort(b+1,b+m+1);//排序后，能够更快定位最小、大的牌在哪里
		cin>>s;
		c=mp[s[0]];
		b_smaller_than_c=a_max_but_smaller_than_c=a_big_than_c=0;
		for(int i=1;i<=m;i++){//统计贝塔比卢本伟小的牌数
			b_smaller_than_c+=b[i]<c;
		}
		for(int i=1;i<=n;i++){//记录舒克比卢本伟小的最大牌和舒克比卢本伟大的牌数
			if(a[i]>=c){
				a_big_than_c++;
			}else{
				a_max_but_smaller_than_c=max(a_max_but_smaller_than_c,a[i]);
			}
		}
		if(n==1){//情况1
			printf("Shou\n");
		}else if(a_big_than_c==n){//情况2
			printf("Shou\n");
		}else if(b_smaller_than_c>=2){//情况3
			printf("Pang\n");
		}else if(b_smaller_than_c==0){//情况4
			printf("Shou\n");
		}else if(m==1&&a_max_but_smaller_than_c>=b[1]){//情况5
			printf("Pang\n");
		}else if(m==1){//情况6
			printf("Shou\n");
		}else if(n-a_big_than_c==1){//情况7
			printf("Shou\n");
		}else if(a[n]>b[m]&&a_max_but_smaller_than_c>=b[1]&&n>3){//情况8
			printf("Pang\n");
		}else{//情况9
			printf("Shou\n");
		}
	}
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

翻译可能比较奇怪，简单来说就是 A、B、P 三个人打牌，最初由 A 开始。当前玩家可以选择一张比上一张更大的牌（忽略花色）出，也可以跳过（每轮第一个玩家不能跳过）。如果另外两个人都跳过了那么下一轮就从这个人开始。先打完所有牌的赢，每个人都知道所有人的牌，A 和 P 希望 P 赢，B 希望 A 或 B 赢，问如果都采取最优策略 P 能否赢。

这道题是一道比较复杂的分类讨论，我们先定义一些基本符号。

$c$ 表示 P 的那张牌大小（$T,J,Q,K,A=10\sim14$），$a_<$ 表示 A 的所有牌中比 $c$ 小的数量，$a_\ge$ 表示大于等于，$b_<$ 表示 B 的所有牌中比 $c$ 小的数量，$b_\ge$ 表示大于等于，$a_m$ 表示 A 最大的那张比 $c$ 小的牌，$a_{\max}$ 表示 A 的最大牌，$b_{\max}$ 表示 B 的最大牌，$a_1$ 和 $b_1$ 代表最小牌。$n$ 和 $m$ 同题目。小的牌和大的牌分别指 $<c$ 和 $\ge c$ 的牌。

接下来从最基本的情况开始，下面每个条件都默认已经不满足前面的条件。

1. $n=1$：A 出完这张牌就赢了，P 输。
2. $a_\ge=n$：A 根本没有机会让 P 出牌，B 更不会这么做，P 输。
3. $b_<\ge2$：B 有两张及以上的小的牌，而 A 可以通过第一次出一张小的牌，之后 A 和 P 一直跳过，等到 B 把任意一张小的牌出完，P 就可以出牌然后赢了。注意这时必须至少两张，否则有可能 B 出完小的牌就直接赢了。
4. $b_<=0$：如果 A 出小牌 B 就直接拦下转为大牌，否则跳过，这样在轮到 P 之前一定有一个人先出完牌，P 输。
5. $m=1$：根据前面的条件能够发现 $b_<=1$，因此 B 只有一张小牌。只有 $a_m\ge b_{\max}$ 才能让 P 出牌然后赢。
6. $a_<=1$：A 和 B 都有一张小牌和一些大牌。只要 A 出小牌 B 就可以用大牌换掉这张小牌，否则跳过，这样一直轮不到 P 出牌。
7. $a_{\max}>b_{\max},a_m\ge b_1,n>3$：这三个需要同时满足。A 只要出一张最小的牌，这时 B 就要换为大牌。之后 A 和 P 等到 B 出掉所有大牌，A 再出 $a_{\max}$ 压住 B，这时 A 再出 $a_m$ 而 B 并没有更大的牌，P 就可以赢。$n>3$ 时因为去掉要打出的这三张以外还要有牌，不然打完 $a_m$ 就自己先赢了（这里容易挂掉）。
8. 其它情况都为 P 输。

总的来说这题还是有一定难度，因为思考的时候要想到所有细节，实现相对容易。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[55],b[55],c;
string s;
int C(char c){
	if(c=='A')return 14;
	if(c=='K')return 13;
	if(c=='Q')return 12;
	if(c=='J')return 11;
	if(c=='T')return 10;
	return c-'0';
}
bool solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s,a[i]=C(s[0]);
	for(int i=1;i<=m;i++)cin>>s,b[i]=C(s[0]);
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	cin>>s,c=C(s[0]);
	int bm=0,amx=0,ge=0;
	for(int i=1;i<=m;i++)bm+=b[i]<c;
	for(int i=1;i<=n;i++){
		if(a[i]>=c)ge++;
		else amx=max(amx,a[i]);
	}
	if(n==1||ge==n)return 0;
	if(bm>=2)return 1;
	if(!bm)return 0;
	if(m==1)return amx>=b[1];
	if(n-ge==1) return 0;
	if(b[m]>=a[n])return 0;
	return amx>=b[1]&&n>3;
}
int main(){
	int T;cin>>T;
	while(T--)puts(solve()?"Pang":"Shou");
	return 0;
}
```

---

## 作者：zheng_zx (赞：0)

## P9876 [EC Final 2021] Prof. Pang and Poker

[题目传送门](https://www.luogu.com.cn/problem/P9876)

### 题意

---

```Alice```，```Bob``` 和 ```Prof.Pang``` 三个人在打牌，```Alice``` 先出牌，然后是 ```Bob```，最后是 ```Prof.Pang```，一直这样轮着来。但是 ```Prof.Pang``` 只有一张牌了。出的牌必须比当前回合内出的牌都要大，才能出牌，否则就只能空过。一个人空过两次后，当前回合结束，由上一个出牌的人重新出牌。```Alice``` 想要 ```Prof.Pang``` 赢，```Bob``` 想要 ```Prof.Pang``` 输，给你 ```Alice```，```Bob``` 和 ```Prof.Pang``` 的牌，问最后 ```Alice``` 和 ```Bob``` 谁赢。

### 分析

---

这种分类讨论的题最切记的是什么情况都要枚举，导致什么情况都漏了。所以只需要枚举赢的情况，其他的情况都是输的了。（当然，几个前置条件先判一下）

1. ```Alice``` 就 $1$ 张牌——输出 ```Shou```；

2. ```Alice``` 最小的牌也比 ```Prof.Pang``` 最大的牌大——输出 ```Shou```；

3. ```Bob``` 有两张及以上比 ```Prof.Pang``` 小的牌——输出 ```Pang```；

4. ```Bob``` 最大的牌比 ```Prof.Pang``` 的牌还要小，同时```Alice```有 $1$ 张比 ```Bob``` 的牌大，比 ```Prof.Pang``` 的牌小的牌——输出 ```Pang```；

5. ```Bob``` 只有一张比 ```Prof.Pang``` 小，```Alice``` 有 $1$ 张比 ```Bob``` 的牌大，有一张比 ```Prof.Pang``` 的牌小，还有一张在 $\operatorname{min}B \le now<P$ 这样的牌。——输出 ```Show```；

6. ```Bob``` 只有 $1$ 张比 ```Prof.Pang``` 小，```Alice``` 有 $1$ 张比 ```Bob``` 的牌大，有 $1$ 张比 ```Prof.Pang``` 的牌小，还有 $1$ 张在 $\operatorname{min}B \le now<P$ 这样的牌，同时还有 $1$ 张牌以上——输出 ```Pang```；

7. 其他情况——输出 ```Shou```；

---

