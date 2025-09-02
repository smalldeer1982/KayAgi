# [USACO08NOV] Toys G

## 题目描述

贝茜的生日快到了，她希望在接下来的 D 天（1 <= D <= 100,000；70% 的测试数据满足 1 <= D <= 500）里庆祝。奶牛们注意力短暂，所以贝茜想要提供玩具来娱乐它们。她计算出她在第 i 天需要 T_i（1 <= T_i <= 50）个玩具。

贝茜的幼儿园为其有抱负的牛程序员提供许多服务，包括一个玩具店，玩具售价为 Tc（1 <= Tc <= 60）美元。贝茜希望通过重复使用玩具来省钱，但农夫约翰担心传染病，要求玩具在使用前进行消毒。（玩具店在销售玩具时会对其进行消毒。）

农场附近的两个消毒服务提供便捷的全套服务。第一个服务收费 C1 美元，需要 N1 个晚上完成；第二个服务收费 C2 美元，需要 N2 个晚上完成（1 <= N1 <= D；1 <= N2 <= D；1 <= C1 <= 60；1 <= C2 <= 60）。贝茜在派对后将玩具送去消毒，如果是一个晚上的服务，她可以在第二天早上支付并取回玩具，或者如果需要更多晚上的消毒，则在之后的早晨取回。

作为一头有学问的奶牛，贝茜已经学会了节省金钱的价值。帮助她找到为她的派对提供玩具的最便宜的方法。

POINTS: 400

## 说明/提示

贝茜希望庆祝 4 天，第一天需要 8 个玩具，第二天需要 2 个玩具，第三天需要 1 个玩具，第四天需要 6 个玩具。第一个消毒服务需要 1 天，收费 2 美元，第二个需要 2 天，收费 1 美元。购买一个新玩具需要 3 美元。

第 1 天 早上购买 8 个玩具，花费 24 美元；下午开派对。将 2 个玩具送去快速清洗（过夜），其余 6 个玩具送去慢速清洗（两晚）。

第 2 天 从快速清洗处取回 2 个玩具；支付 4 美元。下午开派对。将 1 个玩具送去慢速清洗。

第 3 天 从慢速清洗处取回 6 个玩具并支付 6 美元。下午开派对。

第 4 天 从慢速清洗处取回最后一个玩具（将现场玩具数量恢复到 6 个）；支付 1 美元。开心地开派对，意识到花费了最少的钱。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 1 2 2 1 3 
8 
2 
1 
6 
```

### 输出

```
35 
```

# 题解

## 作者：米斯兰达 (赞：10)

## 算法：三分+贪心

### 1.读题之后的第一件事是**明确目标和问题**：

&ensp;&ensp;&ensp;&ensp;第一步有同学可能会往DP的方向思考（比如蒟蒻我）。因为我们要处理的问题是我需要买多少个玩具，并且每天分别分多少个给n1，多少个给n2才能使得总和最小。
但是，在DP之前一定要仔细想一想，有一个算法也可以处理部分DP问题但是比DP更优秀，那就是**贪心**。

&ensp;&ensp;&ensp;&ensp;但是我们要证明贪心是正确的。我们不妨假设c1与c2是商店里玩具的另一种价格且数量有限，sum为1~D天派对所需要的玩具总量，无论如何我们都要从c1,c2,tc这三种价格购买sum个玩具，显然买价格越便宜的越好。

### 2. 第二步将**问题拆分**，往简单的方向去思考

&ensp;&ensp;&ensp;&ensp;关于拆分的方向，这里是根据算法以及自身经验来的（如果是大佬的话完全可能能够一次性到位吧）因为我们要让总的金额最少，并且要让每天派对拥有足够的玩具，我们必须要选择最便宜的方案。

###### &ensp;&ensp;&ensp;&ensp; **为了说明方便，我们这里的所有玩具消毒只按天数付钱。也就是我可以先把所有玩具免费消毒，然后根据取回当天距离消毒当天的天数，划分n1，n2两个档次。如果n1=1，n2=2，一个玩具在第一天送去消毒，在第二天取出来的价格就是c1，但是如果在第三天取出来价格就是c2了（相当于玩具不用立刻在n1天或者n2天取出，可以存放很长一段时间）**

设$c1>c2$（接下来的分析是对于每天单独贪心的情况）

如果$c2>tc$ 也就表明与其送去消毒不如天天买新玩具，这个时候只需要输出$tc*sum$就可以啦

如果$c1>tc>c2$或者$tc>c1>c2$且c2要快一些那么我们只需要将玩具分给从商店买，和n2天消毒就行

如果$tc>c1>c2$ 且c2 比较慢，这个时候我们要仔细斟酌一下啦。

&ensp;&ensp;&ensp;&ensp; 到这里与其考虑每天的分配方式，我们不如从总量分析（因为这里每天分析会变的很麻烦）我们不妨假设我们一共要买x个玩具，那么我们**设f(x)表示满足每天需求前提所需要的最小费用，其中x表示购买的的新玩具的个数。g(x)表示在1~D天内把认为需要送去消毒的旧玩具送去消毒花费的费用。从商店购买的费用算为$tc*x$,总共的费用就可以算为：$f(x)=g(x)+tc*x$，并且这函数的斜率是单调的。**
#### 为什么？！
&ensp;&ensp;&ensp;&ensp;如果新玩具很多，那么g(x)就会特别小。因为新玩具已经满足了派对的需求所以不需要在送一些去洗了。并且存在$g(x-1)-g(x)>=g(x)-g(x+1)$可以这样来考虑，因为玩具数少需要快洗，花的钱就比较多。并且abs(k)就要大一些，函数图像也要抖一些。但是如果玩具数量多，就会选择慢洗。所以abs(k)就要小一些，函数图像也就要缓一些。

&ensp;&ensp;&ensp;&ensp;反向表示带入可得：$f(x)-f(x-1)<=f(x+1)-f(x)$于是f(x)的斜率也是单调递增的。那么为什么会是单峰的呢，同学们可以试着画一下斜率单增的函数的图像（比如二次函数）。


&ensp;&ensp;&ensp;&ensp; 如果这里理解不了的同学可以这样意会：**如果玩具买多了就会浪费一部分钱，因为多买的部分可以用消毒的费用来代替，如果买少了反而要在消毒上面花更多的钱。所以这个函数就是单峰的！**

---
单峰的函数自然而然会联想到三分，所以这道题到这里已经解决了一半了。

### 3.接下来要完成的任务便是怎么求出这个总花费。

&ensp;&ensp;&ensp;&ensp;我们依旧在$tc>c1>c2$ 且c2 比较慢这情况下面思考。

&ensp;&ensp;&ensp;&ensp;那么只考虑**对每天进行贪心**，就是每天都洗最便宜的衣服，求出来的答案是否是最优的呢？

&ensp;&ensp;&ensp;&ensp;很明显**不完全正确！** 我这里举个例子：D=4,N1=1,N2=3,C1=3,C2=1,Tc=4,D1=3,D2=1,D3=1,D4=4;当我们按照上述方法贪心的时候求出来的结果是27，但是正解是25，原因就是我们在第三天的时候，贪心会选择来自第一天的玩具（因为这个贪心只考虑当前最便宜的玩具不考虑天数）。

&ensp;&ensp;&ensp;&ensp;但是如果我们选择跟第一天玩具相同价格的第二天的玩具。虽然对于第三天来说花费是相通的，但是对第四天来说花费就有所不同了（大家可以手工模拟一下这里就不再做详细解释了）。

&ensp;&ensp;&ensp;&ensp;所以我们从上面的例子得到了一个结论，在价格相同的情况下我们应该选择消毒时间最近的玩具，这样消毒时间远的玩具价格就会降低。

---
算法到这里大概就解释清楚了 ~~（吧）~~然后是代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5;
const int inf=1000000000; 
int d,n1,n2,c1,c2,tc,l,r,t[maxn];
struct code
{int Day,toys;};
deque<code> n,o,m;
//我们这里用了三个双端队列，表示n,o,m。
//n表示从开始消毒的那天到今天少于n1天的玩具
//m表示消毒了至少有n1天但是不满足n2天的玩具
//o表示已经消毒了至少n2天的玩具 
void add(int day,int toy)
{
	code now;
	now.Day=day,now.toys=toy;
	n.push_back(now);
}
void newch (int x)
{
	while (n.size()&&x-n.front().Day>=n1)//这里从队首开始讨论，因为队首都是早先被压入的，时间比较久 
	m.push_back(n.front()),n.pop_front();
	while (m.size()&&x-m.front().Day>=n2)
	o.push_back(m.front()),m.pop_front();
}
int Find(int x)
{
	while (n.size()) n.pop_front();//记得清零！ 
	while (o.size()) o.pop_front();
	while (m.size()) m.pop_front();
	int money=(tc-c2)*x;
	//因为在下面的讨论里面我们要把所有的玩具当成消毒过的。
	//但这里是直接购买的玩具，所以要减去c2 
	add(-200000,x); //设成-200000是为了方便讨论（不清楚的可以手工模拟一下） 
	for (int i=1;i<=d;i++)
	{
		int rest=t[i];
		newch(i);//在这里进行新旧交替的操作，相当于题解中我们按照天数堆对消毒进行付款，而不明确的分类 
		while (rest&&o.size())//先选择便宜的 
		{
			if (o.back().toys>rest)//这里从back弹出就是相同价格选择清洗时间比较近的（下同） 
			o.back().toys-=rest,money+=rest*c2,rest=0;
			else 
			rest-=o.back().toys,money+=c2*o.back().toys,o.pop_back();
		}
		while (rest&&m.size())
		{
			
			if (m.back().toys>rest)
			m.back().toys-=rest,money+=rest*c1,rest=0;
			else 
			rest-=m.back().toys,money+=c1*m.back().toys,m.pop_back();
		}
		if (rest) return inf;//inf就表示玩具数量不足以满足派对的需求 
		add(i,t[i]);
	}
	return money;
}
int three()
{
	 r=r+1;
	while (r-l>2)//当l和r足够接近的时候就可以手工跳出了 
	{
		int x=(2*l+r)/3,y=(2*r+l)/3;
		int a=Find(x);
		if (a!=inf&&a<=Find(y)) r=y; 
		else l=x;
	}
	int ans=Find(l);
	for (int i=l+1;i<=r;i++)
		ans=min(ans,Find(i));
	return ans;
}
int main()
{
	scanf("%d%d%d%d%d%d",&d,&n1,&n2,&c1,&c2,&tc);
	if (n1>n2)//保证n1是快洗 
	swap(n1,n2),swap(c1,c2);
	if (c1<c2) c2=c1;//如果快的价格反而要低一些为什么不选择快的呢
	//因为后面的讨论是根据慢的比较低这个条件来的，所以这里需要赋值。 
	for (int i=1;i<=d;i++) scanf("%d",&t[i]),r+=t[i];
	//为什么二分的上限是玩具的总数，因为我最多把所有玩具买下来啊 
	printf("%d",three()); 
}
```


参考资料：官方标准程序

---
&ensp;&ensp;&ensp;&ensp;因为本蒟蒻太菜了，所以一来想到的是Dp（可能DP做多了，都忘了老本行贪心了），然后搞了个五维的出来，并且还不能优化（那么问题来了，为什么会有状态压缩的标签呢），总之就是我太菜了第一次没做出来。

&ensp;&ensp;&ensp;&ensp;于是本蒟蒻就很不要脸的去网上找题解了（emm）,可能是年代太早了，网络上的题解相当的少，而且相当的简洁。可能一般做到这里的人，都已经学会网络流了（餐巾问题呢）所以本蒟蒻看不懂呢qwq。花了一天的时间终于把这道题A掉了，然而为了造福后面解这道题的人，这篇题解就写的特别的**啰嗦**（害怕有人看不懂emm）

&ensp;&ensp;&ensp;&ensp;另外是关于函数的部分，其实之前有很多博客都证明了单峰函数，但是函数的含义并没有详细的给出。这里进行了比较详细的说明

---

## 作者：GoAway (赞：6)

  
**欢迎访问我的博客：[传送门][1]**

 
- 题意

餐巾计划问题（费用流经典题），数据加强（$1 \le N \le 10^5$）。


- Solution

设$f(x)$代表购买$x$个新玩具所需要的最小花费，那么$f$是一个单峰的函数，可以使用三分法求解。

$f(x)$可以通过贪心的方法求出，这个稍后详细介绍。


————


- 接下来简单说明一下这个单峰。假设当$x=t$时有最优解$f(t)$。若取$x = t+1$，那么就会多了一个新买的玩具没有用，浪费了，不会出现更优解，不难发现当$x = t + k ( k \in N^* )$，该结论均成立；若取$x = t - 1$，考虑使用费用流求解时，也就是有有一条在最短路上的边没有走，可能走的是其他最短路径或者次短路，也不会出现更优解，$x = t-k$时类似。


————


- 然后说说贪心法计算$f(x)$。为了方便描述，不妨设$c1 \le c2$不难发现，当前所需要的玩具，首先应该考虑已经购买但是还没有使用的新玩具，因为额外花费为0；在这之后，再考虑便宜点的$c1$，而且是离当前越近越好，因为再往前的天数可能没有足够的脏玩具用来洗；最后再考虑贵的$c2$，这时候应该离当前越远越好，因为越往前靠的话，洗好的玩具就有更大的机会用来用$c1$洗，可以为以后减少花费。



```cpp
#include <bits/stdc++.h>
using namespace std ;
void Read ( int &x, char c = getchar() ) {
    for ( x = 0 ; !isdigit(c) ; c = getchar() ) ;
    for ( ; isdigit(c) ; c = getchar() ) x = 10*x + c - '0' ;
}
const int maxn = 1e5+5, zhf = 0x3f3f3f3f ;
int n, m, t[maxn], s[maxn], tc, n1, n2, c1, c2 ;
struct node {
    int id, val ;
} ;
deque <node> Q ;
int calc ( int x ) {
    int rec = (tc - c2)*x, i, k ;
    node tmp ;    
    Q.clear() ;    
    Q.push_front( (node){-n2, x} ) ;    
    for ( i = 1 ; i <= n ; i ++ ) {
        m = t[i] ;
        if ( i - n1 >= 1 ) Q.push_front( (node){i - n1, t[i - n1]} ) ; 
        while(m) {
            if ( Q.empty() ) return zhf ;
            tmp = Q.back() ;
            if ( tmp.id + n2 <= i && c1 > c2 ) {
                k = min(m, tmp.val) ;
                m -= k ; tmp.val -= k ;
                rec += k*c2 ;
                Q.pop_back() ;
                if ( tmp.val ) Q.push_back(tmp) ;
            } else {
                tmp = Q.front() ;
                k = min(m, tmp.val) ;
                m -= k ; tmp.val -= k ;
                rec += k*c1 ;
                Q.pop_front() ;
                if ( tmp.val ) Q.push_front(tmp) ;
            }
        }
    }
    return rec ;
}
int main() {
    int i, k, l = 1, r = 0, mid1, mid2 ;
    Read(n) ; Read(n1) ; Read(n2) ; Read(c1) ; Read(c2) ; Read(tc) ;
    if ( n1 > n2 ) swap(n1, n2), swap(c1, c2) ;
    for ( i = 1 ; i <= n ; i ++ ) {
        Read(t[i]) ;
        r += t[i] ;
    }
    while ( r - l > 20 ) {
        mid1 = (l*2 + r)/3 ;
        mid2 = (l + r*2)/3 ;
        if ( calc(mid1) >= calc(mid2) ) l = mid1 ;
        else r = mid2 ;
    }
    k = zhf ;
    for ( i = l ; i <= r ; i ++ )
        k = min(k, calc(i)) ;    
    printf ( "%d\n", k ) ;    
    return 0 ;
}

```


[1]: http://blog.csdn.net/wt\_cnyali


---

## 作者：暗影之梦 (赞：2)

## 题目描述：

总共 $ D $ 天，第 $ i $ 天里需要 $ T_i $ 个玩具，玩具玩完后需要消毒才能再次使用。买一个干净的玩具（可以直接使用）的价格是 $ T_c $ 。将一个用过的玩具清理有两种方式，第一种耗时 $ N_1 $ 天消毒好，价格为 $ C_1 $ ；第二种耗时 $ N_2 $ 天消毒好，价格为 $ C_2 $ 。请问在 $ D $ 天的需求都满足的情况下的最小消费。

## 题目解法：

这一题解法为**贪心+二分斜率**。

先考虑玩具购买的总量。如果玩具购买太多或太少都会导致总价太高，因此可以判断出购买总量与最小价值的函数存在唯一极小值。然后便可通过二分斜率查找出在总共买 $ [1,\sum_{i=1}^D T_i] $ 个玩具中最优的选项了。

现在的关键在于如何用贪心最小化总共买 $ k $ 个玩具时的花费。

首先，能买就先买玩具。在不得不洗的情况下，先将消毒方式分为快和慢两种。快的消毒速度较快，慢的则反之。特殊的，如果快消毒的价格与慢消毒价格低，则将快消毒方式覆盖掉慢的，因为这种情况下选择快的绝对占优。

其次，则能用慢消毒满足则用慢消毒。因为慢消毒的耗费相对较低。

因此，最后可以用双端队列模拟出消毒操作来完成此题。具体操作看代码。

## 代码实现：
```c
#include<iostream>
#include<queue>
#include<cstdio>
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9)
    {
        write(x/10);
        putchar(x%10+'0');
        return;
    }
    putchar(x+'0');
}
struct node
{
	int t,c;//需消毒玩具的时间与数量 
};
int n,m1,m2,c1,c2,p,a[100001],sum;
deque<node> qbuy,qmx,qkx;
int mins(int num)
{
	while(!qbuy.empty()) qbuy.pop_back();
	while(!qmx.empty()) qmx.pop_back();
	while(!qkx.empty()) qkx.pop_back();//先清空所有队列 
	int ans=num*p;//买入num个玩具的消费 
	for(int i=1;i<=n;i++)
	{
		while(!qbuy.empty()&&qbuy.front().t+m2<=i) qkx.push_back(qbuy.front()),qbuy.pop_front();//把旧玩具放入快消毒 
		while(!qkx.empty()&&qkx.front().t+m1<=i) qmx.push_back(qkx.front()),qkx.pop_front();//把旧玩具中慢消毒也可以消完的放入慢消毒 
		int ai=a[i];
		int buynum=min(ai,num);//如果还可以买就先买（买的钱开头便已计算） 
		ai-=buynum;
		num-=buynum;
		while(ai&&!qmx.empty())//先慢消毒 
		{
			int mxnum=min(ai,qmx.back().c);
			ai-=mxnum;
			ans+=mxnum*c1;
			if(qmx.back().c==mxnum) qmx.pop_back();
			else qmx.back().c-=mxnum;
		}
		while(ai&&!qkx.empty())//后快消毒 
		{
			int kxnum=min(ai,qkx.back().c);
			ai-=kxnum;
			ans+=kxnum*c2;
			if(qkx.back().c==kxnum) qkx.pop_back();
			else qkx.back().c-=kxnum;
		}
		if(ai) return 1e16;//无法成功完成需求，将总值记为无限大（因为都无法完成所以不能选） 
		qbuy.push_back((node){i,a[i]});
	}
	return ans;
}
signed main()
{
	n=read(),m1=read(),m2=read(),c1=read(),c2=read(),p=read();
	for(int i=1;i<=n;i++) a[i]=read(),sum+=a[i];
	if(m1<m2)
	{
		swap(m1,m2);
		swap(c1,c2);
	}
	if(c1>c2)
	{
		m1=m2;
		c1=c2;
	}
	int l=0,r=sum+1;
	while(l<r-1)//二分找出最小值 
	{
		int mid=(l+r)>>1;
		if(mins(mid)<mins(mid+1)) r=mid;
		else l=mid;
	}
	write(mins(r));
	return 0;
}
```


---

## 作者：kczw (赞：1)

# 题意简述
共 $D$ 天，每天须用 $T_i$ 个物品，这种物品的价格为 $T_c$。同时这 $T_i$ 个物品被使用后消毒能再使用。现有两种消毒方式：
- 收费 $C_1$，需要 $N_1$ 个晚上。
- 收费 $C_2$，需要 $N_2$ 个晚上。

问最小花费。
# 思路 网络流 费用流 dinic 
先说建模。

首先，因为这道题有早晚之分，所以须拆点。这里我们令 $i$ 为第 $i$ 天早上，而 $i+n$ 为第 $i$ 天晚上。

其次：
- 购买物品的行为，即从源点 $S$ 到 $i$ 有一条边权为 $T_c$ 且有极大容量的边。
- 使用物品的行为，即 $i$ 到汇点 $T$ 有一条边权为 $0$ 且容量为 $T_i$ 的边。
- 消毒的行为，即从 $i+n$ 到 $i+N_1$ 有一条边权为 $C_1$ 且有极大容量的边以及从 $i+n$ 到 $i+N_2$ 有一条边权为 $C_2$ 且有极大容量的边。
- 而每天早上没有被用的物品，会留到第二天早上，所以 $i$ 到 $i+1$ 应有一条边权为 $0$ 且有极大容量的边。

这里说一些可能的重点。首先，要维护建边时点的边界，因为 $i+N_1,i+N_2,i+1$ 都是有可能超过它逻辑上的范围的。其次，这里的费用流应使用 dinic()，否则可能会 TLE。
```cpp
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int N=400005,inf=0x3f3f3f3f;
int n,m,tot=1,vis[N],cur[N],dis[N],head[N],a,b,F,Fa,Fb,s=400001,t=400002;
long long ans;
int vv[N<<3],cc[N<<3],nxt[N<<3],ww[N<<3];
inline void add(int u,int v,int c,int w){
	vv[++tot]=v;cc[tot]=c;nxt[tot]=head[u];ww[tot]=w;head[u]=tot;
	vv[++tot]=u;cc[tot]=0;nxt[tot]=head[v];ww[tot]=-w;head[v]=tot;
}
inline bool spfa(){
	for(int i=1;i<=n+n;i++){
		dis[i]=inf;
		vis[i]=0;
	}
	dis[t]=inf;
	vis[t]=0;
	queue<int>q;
	q.push(s);
	dis[s]=0;
	vis[s]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=nxt[i]){
			int v=vv[i];vis[v]=0;
			if(cc[i]&&dis[v]>dis[u]+ww[i]){
				dis[v]=dis[u]+ww[i];
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return (dis[t]!=inf);
}
inline int dfs(int u,int now){
	if(u==t)return now;
	int st=now;
	vis[u]=1;
	for(int i=cur[u];i;i=nxt[i]){
		int v=vv[i];cur[u]=i;
		if(dis[v]==dis[u]+ww[i]&&!vis[v]&&cc[i]){
			int f=dfs(v,min(now,cc[i]));
			cc[i]-=f;
			cc[i^1]+=f;
			now-=f;
			ans+=(long long)f*ww[i];
			if(now==0)break;
		}
	}
	vis[u]=0;
	return st-now;
}
inline void dinic(){
	while(spfa()){
		for(int i=1;i<=n+n;i++)cur[i]=head[i];
		cur[s]=head[s];cur[t]=head[t];
		dfs(s,inf);
	}
}
int main(){
    scanf("%d%d%d%d%d%d",&n,&a,&b,&Fa,&Fb,&F);
    for(int i=1,ned;i<=n;i++){
    	scanf("%d",&ned);
    	add(s,i,inf,F);
    	add(i,t,ned,0);
    	add(s,i+n,ned,0);
    	if(i+1<=n)
    		add(i,i+1,inf,0);
    	if(a+i<=n)
    		add(i+n,i+a,inf,Fa);
    	if(b+i<=n)
    		add(i+n,i+b,inf,Fb);
    }
	dinic();
	printf("%lld",ans);
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

# 多倍经验

- [P1251 餐巾计划问题](https://www.luogu.com.cn/problem/P1251)
- [P2223 [HNOI2001] 软件开发](https://www.luogu.com.cn/problem/P2223)
- [P2917 [USACO08NOV] Toys G](https://www.luogu.com.cn/problem/P2917)
- [P4480 [BJWC2018] 餐巾计划问题](https://www.luogu.com.cn/problem/P4480)

# 题目思路

约定 $p$ 为干净玩具价格，$m_1,m_2$ 为快消毒慢消毒所需要的天数，$c_1,c_2$ 为快消毒慢消毒一个的代价，$m_1\leq m_2,c_1\geq c_2$，不满足的话自己 swap 一下即可。

一个显然的性质是我们可以把要用的玩具一次性买好。考虑如果我们知道了具体要买多少玩具。设要买 $x$ 条，$f(x)$ 表示买了 $x$ 条玩具最后的总花费。如果不够用为 $+\infty$。手玩几个找找规律~~或者是靠小学数学题告诉你的经验~~可以发现这是个单谷函数，有一个极点。显然我们要找出这个极点并且求出对应的函数值。

单谷函数，显然是需要三分的。那么这个 $f(x)$ 到底应该怎么算呢？

先思考，每天可以用的玩具从哪里来？

1. 买来的新的没用完。

2. 快消毒消毒完的。

3. 慢消毒消毒完的。

之后会发现优先使用新的玩具会更优，这个是先用的。

然后在可以的情况下优先使用较晚慢消毒好的。慢消毒全用完之后用较晚快消毒好的。

优先使用较晚得到的玩具，可以尝试让更早的玩具去慢消毒，最小化代价。

优先用慢消毒可以尽量减少消费，和上面一个道理，可能能让快消毒玩具去慢消毒。

这时很显然这就是贪心的过程，~~因为这题是洛谷秋令营提高组贪心课后作业。~~

注意到我们需要从头放，从尾巴取，所以我们实现的时候可以使用双端队列模拟这一贪心过程，即使用 C++ 的 STL 容器 deque。

# 丑陋代码

[Luogu record 128374807](https://www.luogu.com.cn/record/128374807)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define upd1(a, b, c)                            \
    while (!a.empty() && a.front().day <= i - c) \
    {                                            \
        b.push_back(a.front());                  \
        a.pop_front();                           \
    }
#define upd2(a, b)                   \
    while (cnt > 0 && !a.empty())    \
    {                                \
        mn = min(cnt, a.back().cnt); \
        ret += mn * b;               \
        cnt -= mn;                   \
        if (!(a.back().cnt -= mn))   \
            a.pop_back();            \
    }
struct info
{
    int day, cnt;
};
int n, m1, m2, c1, c2, p;
deque<info> buy;
deque<info> fst;
deque<info> slw;
int a[200020];
int f(int k)
{
    buy.clear();
    fst.clear();
    slw.clear();
    int ret = k * p;
    for (int i = 1; i <= n; i++)
    {
        upd1(buy, fst, m1);
        upd1(fst, slw, m2);
        int cnt = a[i];
        int mn = min(cnt, k);
        cnt -= mn;
        k -= mn;
        upd2(slw, c2);
        upd2(fst, c1);
        if (cnt > 0)
            return INT_MAX;
        buy.push_back({i, a[i]});
    }
    return ret;
}
int main()
{
    cin >> n >> m1 >> m2 >> c1 >> c2 >> p;
    if (m1 > m2)
        swap(m1, m2), swap(c1, c2);
    if (c1 < c2)
        m2 = m1, c2 = c1;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int l = 0, r = accumulate(a + 1, a + n + 1, 0);
    while (l <= r)
    {
        int ml = l + (r - l) / 3;
        int mr = r - (r - l) / 3;
        int vl = f(ml), vr = f(mr);
        if (vl >= vr)
            l = ml + 1;
        else
            r = mr - 1;
    }
    cout << min(f(l), f(r)) << endl;
    return 0;
}
```



---

