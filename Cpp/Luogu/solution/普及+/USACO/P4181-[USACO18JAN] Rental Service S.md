# [USACO18JAN] Rental Service S

## 题目描述

Farmer John 意识到牛奶生产的收入不足以支持农场的扩展，因此为了赚取额外收入，他推出了一项奶牛租赁服务，称为“USACOW”（发音为“Use-a-cow”）。

Farmer John 有 $N$ 头奶牛（$1 \leq N \leq 100,000$），每头奶牛每天可以生产一定量的牛奶。附近的 $M$ 家商店（$1 \leq M \leq 100,000$）每家都愿意以一定价格购买一定量的牛奶。此外，Farmer John 的 $R$ 个邻居（$1 \leq R \leq 100,000$）每家都愿意以一定价格租赁一头奶牛。

Farmer John 需要决定每头奶牛是用于产奶还是租给附近的农民。请帮助他计算每天可以赚取的最大金额。

## 说明/提示

Farmer John 应该让奶牛 #1 和 #4 产奶，每天生产 $13$ 加仑牛奶。他应该完全满足 $10$ 加仑的订单，赚取 $250$ 美分，并以每加仑 $15$ 美分的价格出售剩余的 $3$ 加仑，总共赚取 $295$ 美分的牛奶利润。

然后，他应该将其他三头奶牛分别以 $250$、$80$ 和 $100$ 美分的价格租出，赚取额外的 $430$ 美分。（他应该忽略 $40$ 美分的租赁请求。）这样，他每天的总利润为 $725$ 美分。

## 样例 #1

### 输入

```
5 3 4
6
2
4
7
1
10 25
2 10
15 15
250
80
100
40```

### 输出

```
725
```

# 题解

## 作者：俺是小程 (赞：10)

挺好玩的一道题。   
我有个直观一些~~(大概)~~的思路，时空界也还不错。(截止2018.8.6，空间3.24MB rank1，没用fread时间128ms rank2)


------------

先考虑对于一头牛的操作。    

一头牛卖奶还是租很明显要看哪个赚得钱更多。但是，对于某一头牛来说，假如它的产奶量高，虽然目前卖的钱更多，但是如果我贪心的卖了它，导致后期没牛卖得出去了(邻居个数是固定的)，后面的牛产的奶也没它多，那不是亏惨了吗? 我不如把它先留着，卖产奶量少的牛，因为**每头牛卖出去的价格是相同的，无论产奶量多少**。

那么贪心策略也就呼之欲出了。对于牛的产奶量排序，维护一前一后两个指针，先尝试让它产奶并记录这个收益，然后假如有一个邻居出价比这个值还要高，那么就卖掉**产奶量最少的一头牛**，反之说明让这头牛产奶最优，于是让它产奶，然后初始化收益即可。

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;
typedef long long ll;
const int MAXN = 1e5 + 20;

inline int read()
{
	int x = 0; char ch = getchar(); bool f = false;
	while(!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}

int N, M, R;
int buy[MAXN]; P shop;
int cow[MAXN];
priority_queue<P> q;

int main()
{
	cin>>N>>M>>R;
	for(int i = 1; i <= N; i++) cow[i] = read();
	for(int i = 1; i <= M; i++) 
		shop.second = read(), shop.first = read(), q.push(shop);
	for(int i = 1; i <= R; i++) buy[i] = read();
	sort(cow + 1, cow + N + 1);
	sort(buy + 1, buy + R + 1);

	int l = 1, r = N, b = R; 
	ll ans = 0, tmp = -1; 
	for(int i = 1; i <= N; i++){
		if(tmp == -1) while(!q.empty() && cow[r]) {
			if(tmp == -1) tmp = 0;
			if(q.top().second > cow[r]) {
				P p = q.top(); q.pop();
				tmp += 1LL * cow[r] * p.first,
				p.second -= cow[r], cow[r] = 0;
				q.push(p);
			}
				
			else 
				tmp += 1LL * q.top().first * q.top().second,
			    cow[r] -= q.top().second, q.pop();
		} 
		if(tmp != -1 && tmp >= buy[b])
			ans += tmp, tmp = -1, --r;
		else if(b != 0) ans += buy[b--], ++l;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：AOTO (赞：9)

题意翻译

farmer john有N（1≤N≤100,000）头牛，他想赚跟多的钱，所以他准备买牛奶和出租牛。有M(1≤M≤100,000 )家商店想买牛奶，每家商店的进货价不同。有R(1≤R≤100,000 )户邻居想租牛，每户人家的租价不同。 问他最多能赚多少钱。

输入：输入的第1行包含n,m,r三个整数。紧接着的n行每一行有1个整数Ci (1≤Ci≤1,000,000)，表示第i头牛产出Ci加仑奶。再下面的m行每行有两个整数Qi与Pi (1≤Qi,Pi≤1,000,000)，表示第i个商店最多以Pi美分每加仑的价格购买Qi加仑牛奶。FJ可销售0~Qi加仑牛奶到一个商店。然后的r行每行有一个整数Ri，表示FJ的第i个邻居想以Ri(1≤Ri≤1,000,000 ), 的价格租一头牛。

输出：仅一行。表示一天最多获得多少钱。


说明： FJ 需要挤一号和四号奶牛的奶，共可得牛奶13加仑。他可以先买给出价最高的10加仑，赚250美分，然后把剩下的按每加仑15美分去卖，共有295美分的利润。 然后，他要把其他三头以250,80，和100美分的价格分别卖出，赚430美分。所以他一共可得725美分/日的利润。

输入输出样例
输入样例#1：

5 3 4
6
2
4
7
1
10 25
2 10
15 15
250
80
100
40

输出样例#1：

725
注意：int类型不够大！！！

这道题有三种地方用到了贪心:
1.留下产奶量多的奶牛;
2.卖牛奶先卖给出价高的商铺;
3.把奶牛租给出价高的邻居。

而为了节省时间，就可以用前缀和。
注意程序中的这一句：mm=max(mm,zqs+c[min(n-i,k)]);
c中保存将不产奶的n-i头奶牛租给邻居的可得的最大金额，因为前缀和后直接取c[min(n-i,k)]，求个min是因为n-i可能不k大，说明租给邻居后还有奶牛剩余。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ll{            
//全部用long long（只要个别用就可以，这里为了节约做题时间）
	long long zl,qian;
}b[1000001];
long long n,m,k,z,zqs,mm,t,a[1000001],c[1000001];
bool cmp(long long x,long long y)
{
	return x>y;
}
bool cmp2(ll x,ll y)
{
	return x.qian>y.qian;
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
    //读入奶牛的产奶量，从大到小排序（贪心）
	cin>>a[i];
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=m;i++)
    //读入商铺买奶牛的信息，按钱从大到小排序（再次贪心）
	cin>>b[i].zl>>b[i].qian;
	sort(b+1,b+1+m,cmp2)；
	for(int i=1;i<=k;i++)
    //读入邻居租奶牛的金钱，从大到小排序（又一次贪心）
	cin>>c[i];
	sort(c+1,c+1+k,cmp);
	for(int i=1;i<=k;i++)//节省时间而用的前缀和
	c[i]=c[i-1]+c[i];
	t=1; //t代表当前卖个第几个商铺
	for(int i=0;i<=n;i++)//枚举留下i头奶牛产奶
	{
		z=z+a[i];//第i头牛产奶
		while((t<=m)&&(z>=b[t].zl))
        //商铺还能卖且可以将商铺的需求量全部完成，则全部买。
		{
			zqs=zqs+b[t].zl*b[t].qian;
			z=z-b[t].zl;
			t++;
		}
		if(t<=m)//没做完的话，将剩余的牛奶买出去。
		{
			zqs=zqs+z*b[t].qian;b[t].zl-=z;z=0;
		}
		mm=max(mm,zqs+c[min(n-i,k)]);
	}
	cout<<mm;
	return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：6)

## 题目分析

很显然，这是一道贪心题。主要用了三次贪心：
1.  用 sort 排一下 $C_n$ ,只把产奶量较小的卖给邻居，其他挤奶供应商店。
2.  用 sort 把商店给出的价格从大到小排,只把奶卖给出价高的，出价低的不卖，当然，这会用到结构体的知识。
3.  用 sort 排一下 $R_r$ ，只给出价高的邻居奶牛，而且只给产奶量低的奶牛。

然后很明显，在奶牛之间存在一个分界点使得分界点左边的奶牛(产奶量小的)都卖给邻居，其他供应商店。枚举这个分界点即可。

最后，记得开 long long !!!

## 代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
const int MAXN=1e6+5;
int n,m,r;
ll rmb=0;
ll ans=0;//答案
int num=1,have=0;//记录当前商店编号,商店已有牛奶
int c[MAXN];//每头奶牛的挤奶量
ll d[MAXN];//农场的价格
struct shop{
	int p;//单价
	int q;//需要牛奶
}a[MAXN];
bool cmp(shop x,shop y){
	return x.p>y.p;
}
bool clr(int x,int y){
	return x>y;
}
int main(){
	cin>>n>>m>>r;
	for(int i=1;i<=n;i++)
		cin>>c[i];
	for(int i=1;i<=m;i++)
		cin>>a[i].q>>a[i].p;
	for(int i=1;i<=r;i++)
		cin>>d[i];
	sort(c+1,c+n+1,clr);
	sort(a+1,a+m+1,cmp);
	sort(d+1,d+r+1,clr);
	for(int i=1;i<=r;i++)
		d[i]+=d[i-1];
	//排序&输入
	
	for(int i=0;i<=n;i++){
		while(num<=m){
			if(c[i]+have>=a[num].q){
				c[i]=c[i]-a[num].q+have;
				rmb+=(a[num].q-have)*1ll*a[num].p;
				num++;
				have=0;
			}
			else{
				rmb+=c[i]*1ll*a[num].p;
				have+=c[i];
				break;
			}
		}//如果供应商电所带来的金钱
		if(d[min(n-i,r)]+rmb>ans)//还没有达到分界点
		    ans=rmb+d[min(n-i,r)];//更新答案
		else break;//越过分界点,没有必要继续了
	}
	cout<<ans;
}

```


---

## 作者：elijahqi (赞：3)

http://www.elijahqi.win/2018/02/02/luogu4181-usaco18janrental-service/ ‎

http://blog.csdn.net/elijahqi/article/details/79242813
题意翻译

farmer john有N（1≤N≤100,000）头牛，他想赚跟多的钱，所以他准备买牛奶和出租牛。有M(1≤M≤100,000 )家商店想买牛奶，每家商店的进货价不同。有R(1≤R≤100,000 )户邻居想租牛，每户人家的租价不同。 问他最多能赚多少钱。

输入：输入的第1行包含n,m,r三个整数。紧接着的n行每一行有1个整数Ci (1≤Ci≤1,000,000)，表示第i头牛产出Ci加仑奶。再下面的m行每行有两个整数Qi与Pi (1≤Qi,Pi≤1,000,000)，表示第i个商店最多以Pi美分每加仑的价格购买Qi加仑牛奶。FJ可销售0~Qi加仑牛奶到一个商店。然后的r行每行有一个整数Ri，表示FJ的第i个邻居想以Ri(1≤Ri≤1,000,000 ), 的价格租一头牛。

输出：仅一行。表示一天最多获得多少钱。

注意：int类型不够大！！！

说明： FJ 需要挤一号和四号奶牛的奶，共可得牛奶13加仑。他可以先买给出价最高的10加仑，赚250美分，然后把剩下的按每加仑15美分去卖，共有295美分的利润。 然后，他要把其他三头以250,80，和100美分的价格分别卖出，赚430美分。所以他一共可得725美分/日的利润。

---by 风格雨关、WuYongxuan、毕沁露
题目描述

Farmer John realizes that the income he receives from milk production is insufficient to fund the growth of his farm, so to earn some extra money, he launches a cow-rental service, which he calls "USACOW" (pronounced "Use-a-cow").

Farmer John has
NN

N cows (
1≤N≤100,0001 \leq N \leq 100,000

1≤N≤100,000 ), each capable of producing some amount of milk every day. The
MM

M stores near FJ's farm (
1≤M≤100,0001 \leq M \leq 100,000

1≤M≤100,000 ) each offer to buy a certain amount of milk at a certain price. Moreover, Farmer John's
RR

R (
1≤R≤100,0001 \leq R \leq 100,000

1≤R≤100,000 ) neighboring farmers are each interested in renting a cow at a certain price.

Farmer John has to choose whether each cow should be milked or rented to a nearby farmer. Help him find the maximum amount of money he can make per day.
输入输出格式

输入格式：
The first line in the input contains
NN

N ,
MM

M , and
RR

R . The next
NN

N lines each contain an integer
cic_i

ci​ (
1≤ci≤1,000,0001 \leq c_i \leq 1,000,000

1≤ci​≤1,000,000 ), indicating that Farmer John's
ii

i th cow can produce
cic_i

ci​ gallons of milk every day. The next
MM

M lines each contain two integers
qiq_i

qi​ and
pip_i

pi​ (
1≤qi,pi≤1,000,0001 \leq q_i, p_i \leq 1,000,000

1≤qi​,pi​≤1,000,000 ), indicating that the
ii

i th store is willing to buy up to
qiq_i

qi​ gallons of milk for
pip_i

pi​ cents per gallon. Keep in mind that Farmer John can sell any amount of milk between zero and
qiq_i

qi​ gallons to a given store. The next
RR

R lines each contain an integer
rir_i

ri​ (
1≤ri≤1,000,0001 \leq r_i \leq 1,000,000

1≤ri​≤1,000,000 ), indicating that one of Farmer John's neighbors wants to rent a cow for
rir_i

ri​ cents per day.

输出格式：
The output should consist of one line containing the maximum profit Farmer John can make per day by milking or renting out each of his cows. Note that the output might be too large to fit into a standard 32-bit integer, so you may need to use a larger integer type like a "long long" in C/C++.
输入输出样例

输入样例#1： 复制

5 3 4
6
2
4
7
1
10 25
2 10
15 15
250
80
100
40

输出样例#1： 复制

725

说明

Farmer John should milk cows #1 and #4, to produce 13 gallons of milk. He should completely fill the order for 10 gallons, earning 250 cents, and sell the remaining three gallons at 15 cents each, for a total of 295 cents of milk profits.

Then, he should rent out the other three cows for 250, 80, and 100 cents, to earn 430 more cents. (He should leave the request for a 40-cent rental unfilled.) This is a total of 725 cents of daily profit.

填坑ing zhx巨佬很早之前A过的题 经过了thuwc的被血虐 今天一直自己想题所以做题速度放慢了很多 此题有两种模式 1、可以卖牛奶2、可以出租奶牛 根据直觉可以感觉到 我出租奶牛一定得是出租

那些产奶量偏少的 然后靠产奶为收入的那么一定得是 产奶量多的奶牛 那么就针对两部分分别计算 如果i头奶牛全产奶 我最多获得的经济收益是多少然后再枚举一下我i头奶牛全出租获得的收益是多少 那么这时候再枚举一下 我几头奶牛出租几头奶牛产奶 选最大即可
```
#include<cstdio>
#include<algorithm>
#define ll long long
#define N 110000
using namespace std;
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
inline int read(){
	int x=0,f=1;char ch=gc();
	while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=gc();}
	while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
	return x*f;
}
struct node{
	int nd,pri;
}s[N];
int n,m,r,milk[N],price[N];ll sum[N],sum1[N];
inline bool cmp1(const int &a,const int &b){return a>b;}
inline bool cmp(const node &a,const node &b){return a.pri>b.pri;}
int main(){
	freopen("rental.in","r",stdin);
	freopen("rental.out","w",stdout);
	n=read();m=read();r=read();
	for (int i=1;i<=n;++i) milk[i]=read();sort(milk+1,milk+n+1,cmp1);
	for (int i=1;i<=m;++i) s[i].nd=read(),s[i].pri=read();
	sort(s+1,s+m+1,cmp);int now=1,now1=1;
	for (int i=1;i<=r;++i) price[i]=read();sort(price+1,price+r+1,cmp1);ll ans=0;
	for (int i=1;i<=r;++i) sum[i]=sum[i-1]+price[i];
	for (int i=1;i<=n;++i){
		ll tmp1=0;int c=milk[i],pre=now;node e=s[now];
		while(c>=s[now].nd&&now<=m){
			tmp1+=(ll)s[now].nd*s[now].pri;
			c-=s[now].nd;++now;e=s[now];
		}tmp1+=(ll)c*s[now].pri;e.nd-=c;
		sum1[i]=sum1[i-1]+tmp1;s[now]=e;
	}
	for (int i=1;i<=n;++i) ans=max(ans,sum1[i]+sum[n-i]);
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：s5_gan (赞：2)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Max_Cows=100000+10;

int Read()
{ int Digital=0,Symbol=1;  char gc=getchar();
  while (gc<'0'||gc>'9') {if(gc=='-')Symbol=-Symbol; gc=getchar();}
  while (gc>='0'&&gc<='9') Digital=Digital*10+gc-'0',gc=getchar();
  return Digital*Symbol;
}

int Yield[Max_Cows],Rental[Max_Cows];
long long S_Yield[Max_Cows],S_Need[Max_Cows];
long long S_Rental[Max_Cows],S_Stores[Max_Cows];
struct Node{int Need,Price;}Stores[Max_Cows];
int N_Cows,M_Stores,R_Rental;long long Max_Money=0;

inline bool Compare(int X,int Y){return X>Y;}
inline bool Compare_Price(Node X,Node Y){return X.Price>Y.Price;}
int main()
{
  int i; 	
  //freopen("rental.in","r",stdin);freopen("rental.out","w",stdout);
  N_Cows=Read(),M_Stores=Read(),R_Rental=Read();
  for (i=1;i<=N_Cows;++i) Yield[i]=Read(); 
  sort(Yield+1,Yield+N_Cows+1,Compare);//按牛奶产量降序 
  for (i=1;i<=N_Cows;++i) S_Yield[i]=S_Yield[i-1]+Yield[i];
  for (i=1;i<=M_Stores;++i) Stores[i].Need=Read(),Stores[i].Price=Read();
  sort(Stores+1,Stores+M_Stores+1,Compare_Price);
  //按商店需要牛奶量降序
  for (i=1;i<=M_Stores;++i) 
    {S_Need[i]=S_Need[i-1]+Stores[i].Need;
     S_Stores[i]=S_Stores[i-1]+(long long)Stores[i].Need*Stores[i].Price;}
  for (i=1;i<=R_Rental;++i) Rental[i]=Read();
  sort(Rental+1,Rental+R_Rental+1,Compare);
  for (i=1;i<=R_Rental;++i) S_Rental[i]=S_Rental[i-1]+Rental[i];
  for (i=0;i<=N_Cows;++i)
   { if (N_Cows-i>R_Rental)continue;//考虑租赁需求N_Cows-i<=R_Rental到N_Cows 
     long long Now_Money=S_Rental[N_Cows-i];
     int Pos=upper_bound(S_Need+1,S_Need+M_Stores+1,S_Yield[i])-(S_Need+1);
     //按前i头奶牛产量总和搜索商店需求牛奶量 
     Now_Money+=S_Stores[Pos];//加入卖给商店的盈利 
     if (Pos!=M_Stores) 
	   Now_Money+=(long long)Stores[Pos+1].Price*(S_Yield[i]-S_Need[Pos]);
     Max_Money=max(Max_Money,Now_Money);
   }
 printf("%lld\n",Max_Money);
 return 0;
}
```

---

## 作者：金银花露 (赞：1)

[[USACO18JAN]Rental Service S](https://www.luogu.com.cn/problem/P4181)

### 前言

这道题的算法最基础的应该是贪心，但在实现上，总有许多不一样（清奇）的思路。

后来发现题解区里面有一个大佬用二分法解决的，但没有详细的分析，对于像我这样的蒟蒻来说实在是看不懂的，所以才有了这篇题解。

码风有点相似，但确确实实是我自己打的。

## 1.审题

给出一些牛，你可以将他们租出获得收益，也可以通过卖他们的牛奶获得收益，问这个收益的最大值。

## 2.贪心

### 2.1对于卖他们的牛奶

对一加仑的牛奶和想要它的商店来说，这一加仑的牛奶无论如何都要卖出去，可是怎样才能让收益最大呢？

当然是让**出价最高**的商贩将他购买走。

### 2.2对于将他们出租

与上面基本同理，也可以确定贪心策略：**租给价格高的**。

还有一个小点：每次出租**奶产的最少的**，最大限度让出租相同数量的奶牛后，剩下的产的牛奶最多。

## 3.实现

### 3.1数据的基础处理

排序，用C++的STL中的sort函数。~~STL大法好~~

将所有数据从大到小排序，商店按价格排序（不是容量）

前缀和，求出以下数组。

$need_i$ ：前 $i$ 头奶牛的产奶量。

$lend_i$ ：前 $i$ 个租户给出的租贷总和。

$milk_i$ ：前 $i$ 个商店所需容量总和。

$milkadd_i$ ：**刚好满足**前 $i$ 个商店可获得的利润。

### 3.2基础代码实现（20分）

暴力枚举将产奶量最少的 $i$ 头奶牛出租。

对于每种情况：

出租获得的利润： $lend_i$

得到的牛奶 $m$： $need_{N-i}$ 

再次暴力计算：从1开始到 M ,用第二部分的贪心策略计算其总的利润。

每次更新答案即可。

时间复杂度为：$O(\min(N,R)M)$

肯定是要~~狠狠的~~超时的。

### 3.3优化

我们观察到 $milk_i$ 是一个上升序列，那怎样快速找出得到的牛奶在哪个商店停止卖出呢？

~~lower_bound&upper_bound：选我！~~

其实两个都是可以的，如果你还不知道这两个函数，[点我](https://www.luogu.com.cn/problem/solution/P1020)

两个差一个等于号其实不算太重要，只是在计算时有些细微的差别。

这里用 lower_bound 做例子。

找出数字下标 $t$ 后，$milkadd_{t-1}$就是前 $t-1$ 个商店的总和。

而剩下的牛奶就用 $(m-milk_{t-1})\times shopp_t$ ,其中 $shopp_t$ 表示第 $i$ 个商店价格是多少。

现在的时间复杂度就是：$O(\min(N,R)\log M)$ 

## 4.代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long N,M,R;
long long m_milk[100005];
struct P
{
	long long q,p;
}milk_shop[100005];
long long cow_lend[100005];
bool cmp(long long a,long long b){return a>b;}
bool cmp2(P a,P b){return a.p>b.p;}
long long ans=-1,money=0;
long long sum_need[100005];
long long sum_lend[100005];
long long sum_milk[100005];
long long sum_milkadd[100005];
int main()
{
	scanf("%lld%lld%lld",&N,&M,&R);
	for(long long i=1;i<=N;i++)scanf("%lld",&m_milk[i]);
	for(long long i=1;i<=M;i++)scanf("%lld%lld",&milk_shop[i].q,&milk_shop[i].p);
	for(long long i=1;i<=R;i++)scanf("%lld",&cow_lend[i]);
	sort(m_milk+1,m_milk+N+1,cmp);
	sort(cow_lend+1,cow_lend+R+1,cmp);
	sort(milk_shop+1,milk_shop+M+1,cmp2);
	for(long long i=1;i<=N;i++)sum_need[i]=sum_need[i-1]+m_milk[i];
	for(long long i=1;i<=R;i++)sum_lend[i]=sum_lend[i-1]+cow_lend[i];
	for(long long i=1;i<=M;i++)sum_milk[i]=sum_milk[i-1]+milk_shop[i].q;
	for(long long i=1;i<=M;i++)sum_milkadd[i]=sum_milkadd[i-1]+milk_shop[i].q*milk_shop[i].p;
	for(long long i=0;i<=min(R,N);i++)
	{
		long long milk=sum_need[N-i];
		long long t=lower_bound(sum_milk+1,sum_milk+M+1,milk)-sum_milk;
		long long tot=sum_milkadd[t-1]+(milk-sum_milk[t-1])*milk_shop[t].p;
		ans=max(ans,tot+sum_lend[i]);
	}
	cout<<ans;
	return 0;
}
```




---

## 作者：zxf_272 (赞：1)

这道题目是一道比较简单的贪心。
步骤：
S1 输入
S2 预处理：根据产奶量排序奶牛，根据收购价格排序商店，根据租金排序neighbour。
S3 贪心：交易当前收益最大的
S4 输出
下面上代码(c++)，不懂得可以问，不喜勿喷
_____
```
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;
int N,M,R;
int r[maxn],c[maxn];
long long sum=0;
int sl=1,rl=1,tj,lq;
//tj记录当前尝试交易的最后一家商店位置，sl记录前一次交易完成商店的编号，rl记录待租奶牛 ，lq为剩余需求量 
struct store{
    int p,q;
}s[maxn];
int cmp1(store a,store b){//排序商店的价格 
    return a.p>b.p;
}
int cmp2(int a,int b){
    return a>b;
}
long long rent(int i){
    return (long long)r[rl];
}
long long sell(int i){
    int flag=0,left=c[i];long long tot=0;
    tj=sl;
    while(left>=s[tj].q&&tj<=M){//剩余奶量卖给商店 
        left-=s[tj].q;tot+=s[tj].q*s[tj].p;tj++;
    }
    if(tj>M){//牛奶供过于求 
        return tot;
    }
    lq=s[tj].q-left;tot+=left*s[tj].p;//lq表示这头牛的牛奶卖的最后一家商店还需要多少牛奶 
    return tot;
}
int main(){
    cin>>N>>M>>R;
    int i,j,k;
    for(i=1;i<=N;i++){
        scanf("%d",&c[i]);
    }
    sort(c+1,c+N+1);
    for(i=1;i<=M;i++){
        scanf("%d%d",&s[i].q,&s[i].p);
    }
    for(i=1;i<=R;i++)scanf("%d",&r[i]);
    sort(s+1,s+M+1,cmp1);
    sort(r+1,r+R+1,cmp2);
    i=1;j=N;int w=0;
    while(i<=j){
        long long a=rent(i),b=sell(j);
        if((a>=b||sl>M)&&rl<=R){//出租目前产奶量最少的奶牛比较合算 
            rl++;
            sum+=a;
            i++;
        }
        else if(sl<=M){//卖牛奶合算 
            sl=tj;if(tj<=M)s[tj].q=lq;//更新指针，修改商店需求 
            sum+=b;--j;
        }
        w++;
        if(w>N)break;//供过于求，退出循环 
    }
    cout<<sum<<endl;
    return 0;
}
```

---

