# Buy Low Sell High

## 题目描述

你可以完美地预测某只股票接下来 $N$ 天的价格，你想利用这一知识盈利，但你每天只想买卖一股，这表明你每天要么什么都不干，要么买入一股，要么卖出一股。起初你没有股票，你也不能在没有股票时卖出股票。你希望在第 $N$ 天结束时不持有股票，并最大化盈利。

## 样例 #1

### 输入

```
9
10 5 4 7 9 12 6 2 10
```

### 输出

```
20
```

## 样例 #2

### 输入

```
20
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4
```

### 输出

```
41
```

# 题解

## 作者：逃离地球 (赞：79)

前几天校内考试里出现了一道反悔贪心的题，我发现我还不太会这个知识点，于是来学一下。这题是反悔贪心的模板题。

### 题意

已知 $n$ 天内的股票价格，每一天可以选择买进、卖出或不做，最初有无限的钱，最大化收益。$n\le 3\times 10^5$。



### 题解

一个简单的贪心想法就是把每一天都看作一个物品，从前向后遍历每一天并在所有可选的物品中选择价格最小的，并获得两个股票价格之差的收益。

但是这个贪心并没有考虑这样的选择对后面的影响，比如，这样一组数据就可以卡掉这个贪心：

```
3
1 2 100
```

我们选择让 $2$ 与 $1$ 获得 $1$ 的收益，而使 $100$ 无法获得收益。但事实上 $100$ 与 $1$ 可以获得 $99$ 的收益，显然更优。

于是我们考虑修正这个做法，加上一个「反悔」的操作。具体来说，我们对于每一个形如「在第 $i$ 天买入，在第 $j$ 天卖出」的决策，假想出一个价格为 $val$ 的物品，使得「在第 $i$ 天买入，在第 $j$ 天卖出，同时买入这个价格为 $val$ 的物品，并在第 $k$ 天卖出」，等价于「在第 $i$ 天买入，在第 $k$ 天卖出」。这样，我们选择买入这样一个物品，也就相当于撤销了「在第 $i$ 天买入，在第 $j$ 天卖出」这个决策，而改为「在第 $i$ 天买入，在第 $k$ 天卖出」，反悔操作得以实现。

那么这个物品的价值 $val$ 究竟应该是多少呢？设第 $i$ 天的价格为 $a_i$，则有 $a_j-a_i+a_k-val=a_k-a_i$，化简得 $val=a_j$。于是，我们便设计出了一个新的算法：维护一个可重集合，代表「可选的物品的价格」。从前向后遍历每一天，对于第 $i$ 天，找到集合中最小的价格 $a_j$，并向集合中插入 $a_i$，代表 $a_i$ 这一天可选。若 $a_i>a_j$，则把答案加上 $a_i-a_j$，并向集合中再次加入 $a_i$，代表假想的反悔物品，并将 $a_j$ 从集合中删除。我们可以使用堆维护这个集合，时间复杂度 $\mathcal{O}(n\log n)$。

为了保证这个算法的正确性，我们还要解决如下几个问题：

**Q1：**如果我只选了那个可选物，而不选反悔物，那么这一天岂不是又买入又卖出？与题意不符。

**A1：**事实上，由于可选物与反悔物的价格相同，我们可以认为优先选择反悔物，而不会出现冲突。

**Q2：**为何被反悔的物品不能选择一个次优的物品买入？在此算法中一个物品被反悔后只能作为价格低的物品被买入。

**A2：**我们可以注意到，一个物品的决策被反悔当且仅当它是这个集合中最小的数，即没有比它更小的数供它选择买入、同时也没有比它更小的，在它后面的数抢它的东西。

**Q3：**为何一个物品不被反悔就只能作为较大数卖出？这个物品作为较小数买入为何不可能更优？

**A3：**因为一个物品被反悔与一个物品作为较小数买入更优的条件一样。

事实上，本题的反悔贪心做法正确性不是非常显然，大家应该仔细思考，对于自己的疑点，通过尝试制造 Hack 数据的方式，帮助自己解决疑问，并更好的理解反悔贪心的思路。



### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int read() {
    int ret = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') f = (ch == '-') ? -f : f, ch = getchar();
    while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
    return ret * f;
}

int n, ans;
priority_queue<int, vector<int>, greater<int> > q;
signed main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        int k = read();
        if (!q.empty() && q.top() < k) ans += k - q.top(), q.pop(), q.push(k);
        q.push(k);
    }
    printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：SJC_03 (赞：46)

这道题是今天讲课的一道原题，于是蒟蒻突发奇想决定写一篇题解，如有不适还请大佬们轻喷

------

我的思路是**贪心**

我们将每天的价格视为一个个"选项"， 压入小根堆中，为了保证买入操作在卖出操作之前，我们从前往后扫描$p$，对于现在的价格 $p_i$，如果堆顶元素$p_j$ 满足  $p_{j}<p_i$ ，那么，我们取出堆顶，在第$j$天买入股票，在第$i$天卖出股票，此时，我们就可以获得$p_i - p_j$ 的收益

然而，如果之后有$p_k$ 满足$p_k > p_i$ ，辣么，我们当前作出的决策可能并不是最优的，如何反悔呢？

 于是，当我们进行上述操作时，我们将$p_i$也压入堆中，增加一个$p_i$的选项，弹出时，我们相当于将$p_j$按照$p_i$的价格又买了回来

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxN = 300001;

int n, pi;
long long ans = 0;

priority_queue< int, vector<int>, greater<int> > Q; \\小根堆

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) { 
		cin >> pi;
		if (!Q.empty() && (Q.top() < pi)) {
			ans += (pi - Q.top());
			Q.pop(); 
			Q.push(pi);
		}
		Q.push(pi);
	}
	cout << ans << endl;
	return 0;
}
```

同时感谢洛谷，同机房的大佬，以及另一篇题解的作者



---

## 作者：nth_element (赞：14)

想要更丰富的展示，请点击[我的Blog](https://www.cnblogs.com/nth-element/p/11792218.html)

***

若想要深入学习反悔贪心，[传送门](https://www.cnblogs.com/nth-element/p/11768155.html)。

***

**Description**:

已知接下来 $n$ 天的股票价格，每天可以买入当天的股票，卖出已有的股票，或者什么都不做，求 $n$ 天之后最大的利润。

**Method**：

我们可以快速想出一种贪心策略：买入价格最小的股票，在可以赚钱的当天卖出。

显然我们可以发现，上面的贪心策略是错误的，因为我们买入的股票可以等到可以赚最多的当天在卖出。

我们考虑设计一种反悔策略，使所有的贪心情况都可以得到全局最优解。（即设计反悔自动机的反悔策略）

定义 $C_{buy}$ 为全局最优解中买入当天的价格， $C_{sell}$ 为全局最优解中卖出当天的价格，则：
$$
C_{sell}-C_{buy}=\left(C_{sell}-C_i\right)+\left(C_i-C_{buy}\right)
$$


$C_i$ 为任意一天的股票价格。

即我们买价格最小的股票去卖价格最大的股票，以期得到最大的利润。我们先把当前的价格放入小根堆一次（这次是以上文的贪心策略贪心），判断当前的价格是否比堆顶大，若是比其大，我们就将差值计入全局最优解，再将当前的价格放入小根堆（这次是反悔操作）。相当于我们把当前的股票价格若不是最优解，就没有用，最后可以得到全局最优解。

上面的等式即被称为反悔自动机的反悔策略，因为我们并没有反复更新全局最优解，而是通过差值消去中间项的方法快速得到的全局最优解。

（假如还没有理解这道题，可以看一看代码，有详细的注释）

**Code**:

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
priority_queue<int,vector<int>,greater<int> >qu;//开一个小根堆 
int n;
int ans=0;//全局最优解 
signed main()
{
    read(n);
    ans=0;
    for(int i=1,x;i<=n;i++)
    {
        read(x);//当前的股票价格 
        qu.push(x);//贪心策略：买价格最小的股票去买价格最大的股票 
        if(!qu.empty()&&qu.top()<x)//假如当前的股票价格不是最优解 
        {
            ans+=x-qu.top();//将差值计入全局最优解 
            qu.pop();//将已经统计的最小的股票价格丢出去 
            qu.push(x);//反悔策略：将当前的股票价格再放入堆中，即记录中间变量（等式中间无用的Ci） 
        }
    }
    printf("%lld\n",ans);//输出全局最优解 
    return 0;
} 
```



---

## 作者：西卡洛斯 (赞：11)

# CF865D Buy Low Sell High

反悔贪心模板题（确信）

一般想到的的贪心策略是，低价买入高价卖出，能赚钱就赚钱，差值计入 $ans$ 里。

但如果遇到了一个更高价的物品，那这种方法就不是最优解，于是可以实现反悔，将高价买入再以更高价卖出，这样 $ans$ 就是最大的了。

上代码：


```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#define LL long long
using namespace std;
priority_queue<LL,vector<LL>,greater<LL> > q;
int main()
{
	LL n;
	scanf("%lld",&n);
	LL ans=0;
	for(int i=1;i<=n;i++)
	{
		LL x;
		scanf("%lld",&x);
		if(!q.empty()&&q.top()<x)//遇到更高价物品
		{
			ans=ans+x-q.top();//计入差值
			q.pop();//弹出最小价格
			q.push(x);//反悔
		}
		q.push(x);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：xixiup (赞：7)

## 前置芝士

**反悔贪心**是一种十分有用的算法，适合于在处理一些贪心处理问题时，若无法得到贪心的正确性，那么反悔贪心是一个不错的选择。

反悔贪心的核心就是在贪心时加入一些特定的值，使得你在贪心处理下一个点时可以直接使用处理普通点的方法处理这个特殊的点使得可以得到更优的答案。

具体的方法因题而异，具体方案在题目中会讲。

## 思路分享

我们首先可以考虑，我们可以贪心地对于每一天 $i$，如果我们可以卖出，那么贪心的选择之前的价格最小的一天 $j$，然后若 $p_j<p_i$，则就可以在 $j$ 天买入一股，然后在第 $i$ 天卖出，这时候就仅需要一个 $priority\_queue$ 就可以了。

但是还有一个问题，如何考虑下面这组数据呢？

`1 2 3`

可以发现，若贪心处理，则仅会在第 $1$ 天买入一股，并在第 $2$ 天卖出，赚到了 $1$ 元。但是若将第 $1$ 天的股票在第 $3$ 天卖出，则可以获得高达 $2$ 元的利润，~~是原答案的足足两倍！~~

所以这时候我们就可以请出我们的主角：反悔贪心。

可以考虑，对于 $i,j,k \in \left[ 1,n \right],i<j<k$ 且 $p_i<p_j<p_k$，这个贪心就会认为 $i$ 买 $j$ 卖，对答案的贡献为 $\boxed{p_j-p_i}$ 。而正确答案却是 $i$ 买 $k$ 卖，对答案贡献为 $\boxed{p_k-p_i}$ 。那么我们可以考虑，若我们在已经考虑完 $i$ 买 $j$ 卖，再来考虑 $i$ 买 $k$ 卖，在考虑答案时，贡献就为 $\boxed{p_k-p_i-p_j+p_i=p_k-p_j}$，即可以看作先 $i$ 买 $j$ 卖，再 $j$ 买 $k$ 卖，就可以处理了。

但是还有一个点需要注意，就是当我们反悔完一次之后，我们还需要加入一次当前的数，因为这个数转完一次之后是还可以买卖的，因为事实上这一天是没有进行过任何一次买卖的，所以需要多加入一次我们的堆。

题目到这里就没有别的问题了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxn=300100;
ll n,ans;
priority_queue<ll,vector<int>,greater<int> >q;//一个堆
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		ll x;
		scanf("%lld",&x);
		if(!q.empty()&&x>q.top()){
			ans+=x-q.top();
			q.pop();
			q.push(x);
            //需要多加入一次。
		}
		q.push(x);
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：Little09 (赞：6)

反悔贪心。

先贪心地考虑，每次考虑股票 $i$ 如果前面有比它便宜的 $j$，就在买 $j$ 卖掉 $i$。每次用堆维护。

但是这个贪心显然是错误的，考虑反悔。比如 $i$ 后面有一个点 $k$，最优方案是在 $k$ 卖出 $j$ 买入，这里理解为在 $j$ 买，在 $i$ 卖出又买进，在 $k$ 卖出。为了弥补 $i$，所以要把 $i$ 多放一个到堆里，表示反悔。

代码通俗易懂。实现的时候小根堆我是用负数实现的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
priority_queue<ll>q;
ll n,x,ans;
int main()
{
	scanf("%lld",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld",&x);
		if (q.size()&&-q.top()<x)
		{
			ans+=x+q.top();
			q.pop();
			q.push(-x);
		}
		q.push(-x);
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：l_water (赞：5)

```
考前发题解是不是rp++。。。。明天我们市赛......我滚出来发篇题解吧QAQAQ
```
咳咳言归正传.....这个是一道求最优值的题目~~废话~~。我们可以怎么写呢?
dfs?bfs?dp?~~模拟退火~~..........好吧其实这个题目是一个关于优先队列的~~裸题~~.....(那你还卡了那么久？)。其实这样的要求什么最大值哇，最优方案啊很有可能都是优先队列的哦！咳咳言归正传了.......


------------
思路：假设每一次都进行买入，压入优先队列（压成负数因为是买入），在以后没经过一次可买卖的地方去除对头进行操作（因为这样一定是最优方案）。一定要压两次！（PS:第二次被弹出才表示卖出。）
```
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000100],ans,cnt;
priority_queue<long long> q;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
    {
        q.push(-a[i]);q.push(-a[i]);
        ans+=a[i]+q.top();
        q.pop();
    }
    printf("%lld",ans);
    return 0;
}
```
完结散花

---

## 作者：zythonc (赞：4)

## 【思路分析】

很明显，贪心，对于每天的价格，我们可以搜索之前的，遇到比它小的价格就加上差值

利用小根堆可以做到 $O(n)$

**但是很明显是不行的，因为：**

```
3
11 12 31
```

显然答案是 $31-11=20$，但是按照刚才的贪心思路我们会发现答案是 $1$

**用式子写写看看？**

我们要的是 $C_3-C_1$

但是实际上算的是 $C_2-C_1$

我们做变换发现可以 $(C_3-C_2)+(C_2-C_1)$

所以反悔贪心的思路很明显了：

**在满足条件的情况下依然将其加入小根堆，目的是如果后面有更优情况，就将其买回来**

先卖再买，不就相当于没做吗？

### 注意long long！！！

## 【代码实现】

```
#include<iostream>
#include<queue>
#define int long long
using namespace std;
int n,in[1000001],ans;
priority_queue<int,vector<int>,greater<int> >q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>in[i];
	for(int i=1;i<=n;i++){
		q.push(in[i]);
		if(in[i]>q.top()){
			ans+=in[i]-q.top();
			q.pop();
			q.push(in[i]);
		}
	}
	cout<<ans;
}
```

---

## 作者：JeffWang2019 (赞：4)

[CF865D Buy Low Sell High](https://www.luogu.com.cn/problem/CF865D)

给大家提供一种时间、空间复杂度都很低的方法。（貌似目前没有别的题解时空比我更优）

## 主要思路：反悔贪心

反悔贪心就是假设先处理，但是可以撤回的一种思想。如果撤回了，就相当于不操作。

因此我们明显需要优先队列这一数据结构。

```cpp
priority_queue<int>q;//优先队列
```
读入每日数据的时候，将其压入优先队列（压两次，第二次弹出才算卖出）。后面如果发现更优方案，就不断地将 $ans$ 的值加上队列顶与当前股票价格的和。

另外，由于是买入，钱数减少，所以一定要压入负数（表示钱数减少）。后面的卖出操作则是加钱。

**坑点：十年OI一场空，不开longlong见祖宗。ans在变化的时候一定要开longlong，否则会溢出（都猜得到）。**

## 完整代码；

```cpp
#include <bits/stdc++.h>
using namespace std;
priority_queue<int>q;//优先队列
int n,x;//x存储每个时段的股票价格,不开数组,省空间(废话)
long long int ans=0;//十年OI一场空，不开longlong见祖宗
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        q.push(-x);
        q.push(-x);//压入两次,才能实现"反悔贪心"
        ans+=q.top()+x;//如果发现更优方案，就不断地将ans的值加上队列顶与当前股票价格的和。
        q.pop();//弹出一次
        //再弹出一次才算卖出
    }
    printf("%lld\n",ans);
    return 0;
}
```

[彩蛋](https://www.luogu.com.cn/blog/paiwyz314/)


---

## 作者：尹昱钦 (赞：2)

## 先介绍一下错误思路
错误思路：对于每天的股票，若比当前入手的最低价股票高，则入手前面的，并在今天卖出去，再把今天的买入，为以后做准备。

即能卖股票就卖（能赚钱就赚钱），然后把此股票扔进去。

因为a[k]-a[i]=(a[j]-a[i])+(a[k]-a[j])。

## 错误代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=300005;
int a[maxn],n;
long long ans;
priority_queue<int,vector<int>,greater<int> > q;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        if(!q.empty()&&q.top()<a[i]){
            ans+=a[i]-q.top();
            q.pop();
        }
        q.push(a[i]);
    }
    cout<<ans;
    return 0;
}
```
## 为什么错误了呢？
我们看这一组样例：
```latex
4
1 2 4 5
```

我们会在第一天买入，入队1，然后第二天卖出，出队1入队2，赚1差价，然后第三天买入第二天的，再卖出，出队2入队4，赚2，然后在第四天买入第三天的再卖出，入队4出队3，赚1。

一共赚了1+2+1=4。

但是很显然可以第一天买入第三天卖出，赚3，第二天买入第四天卖出，赚3，一共赚3+3=6。

Q：差在哪里呢？

A：第二天的邮票再做中间量后其实是可以再购买的。
所以
## 正解
- **做法一**：就是加一个vis的数组，表示买没买此邮票。优先队列中的变量可以改成pair。
- **做法二**：不需要vis也可，只需要对于中间量在优先队列里加入两遍。（第一遍相当于可换，第二遍相当于可买），对于非中间量加入一遍（相当于可买）。

## AC代码
~~因为大部分大佬都用做法二，所以放了做法一的代码~~
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=300005;
int a[maxn],n;
bool vis[maxn];
long long ans;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(!q.empty()&&q.top().first<a[i]){
			vis[q.top().second]=!vis[q.top().second];
			ans+=a[i]-q.top().first;
			if(vis[q.top().second]) q.push(q.top());
			q.pop();
			q.push(make_pair(a[i],i));
		}else{
			q.push(make_pair(a[i],i));
			vis[i]=1;
		}
	}
	cout<<ans;
	return 0;
}

```
祝大家顺利AC

---

## 作者：XL4453 (赞：1)

题目分析：

考虑贪心。

维护一个小根堆，用以维护当前可以买的股票价格，需要购买时，直接取出元素购买，相当于影响之前的决策。

对于每一天，先从当前可以买的股票中选出一个价格最低的，将其与当前股票比较。

若当前股票价格小于堆中股票价格，则直接将当前股票加入堆中，表示无法购买。

否则当前股票价格大于堆中股票价格，则买下股票，统计答案，然后从堆中删除买入元素，并将当前股票变成两份价格都等于原来股票价格的股票加入堆中，其中一份表示直接购买当前股票，另一个表示反悔决策。

反悔决策的意义是这样的：对于某股股票，在买入后的某一天卖出了，然后将后一天卖出的股票再次买入，卖出当前股票，其实也就相当于在之前的那一天买入股票，在当前卖出股票。换句话说，也就是之前的一次卖出和之后的一次买入相抵消，结果上相当于没买入也没有卖出。

------------
代码：


```cpp
#include<cstdio>
#include<queue>
using namespace std;
priority_queue <int,vector<int>,greater<int> > q;
int n,a[300005];
long long ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(q.empty()){
			q.push(a[i]);
			continue;
		}
		if(q.top()>a[i]){
			q.push(a[i]);
			continue;
		}
		ans+=a[i]-q.top();
		q.pop();
		q.push(a[i]);
		q.push(a[i]);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：lndjy (赞：0)

### 贪心+堆

纪念品那题，物体个数为 1 时，有一个贪心是如果明天比今天贵就都买了今天明天再卖，如果第三天更贵可以看成第二天卖了又买，没有影响，和直接第一天买第三天卖一样。也就是说，是可以后悔的。

这题也是同理。区别是一天只能操作一次，那么就是操作利润最大的一次。假设今天卖利润最大，那买入那一天一定是价格最低差最大。这个可以用堆维护。但是操作完要把当前放回去，这样以后更高的时候可以后悔。

**坑点：long long**

代码：
```cpp
#include<iostream>
#include<queue>
#include<vector>
#define int long long
using namespace std;
signed main()
{
	priority_queue<int,vector<int>,greater<int> > q;
	int n;
	cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(!q.empty()&&q.top()<x)
		{
			ans+=x-q.top();
			q.pop();
			q.push(x);
			//cout<<x<<' '<<ans<<endl;
		}
		q.push(x);
	}
	cout<<ans;
	return 0;
}
```


---

