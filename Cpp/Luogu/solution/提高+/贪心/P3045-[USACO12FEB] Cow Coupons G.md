# [USACO12FEB] Cow Coupons G

## 题目背景

Subtask 0 为原数据，Subtask 1,2 为 hack 数据。

## 题目描述

Farmer John needs new cows! There are N cows for sale (1 <= N <= 50,000), and FJ has to spend no more than his budget of M units of money (1 <= M <= 10^14).  Cow i costs P\_i money (1 <= P\_i <= 10^9), but FJ has K coupons (1 <= K <= N), and when he uses a coupon on cow i, the cow costs C\_i instead (1 <= C\_i <= P\_i). FJ can only use one coupon per cow, of course.

What is the maximum number of cows FJ can afford? 

FJ 准备买一些新奶牛。市场上有 $N$ 头奶牛，第 $i$ 头奶牛价格为 $P_i$。FJ 有 $K$ 张优惠券，使用优惠券购买第 $i$ 头奶牛时价格会降为 $C_i$，当然每头奶牛只能使用一次优惠券。FJ 想知道花不超过 $M$ 的钱最多可以买多少奶牛？

- $1 \le K \le N \le 5 \times 10^4$
- $1 \le C_i \le P_i \le 10^9$
- $1 \le M \le 10^{14}$

## 说明/提示

FJ has 4 cows, 1 coupon, and a budget of 7.


FJ uses the coupon on cow 3 and buys cows 1, 2, and 3, for a total cost of 3 + 2 + 1 = 6.


## 样例 #1

### 输入

```
4 1 7 
3 2 
2 2 
8 1 
4 3 
```

### 输出

```
3 
```

# 题解

## 作者：人间温柔 (赞：62)

这是反悔贪心的一道好题。

有人问，反悔贪心是什么？

其实贪心本身不带有反悔，是因为此时的贪心可以从局部最优解推出全局最优解。但当有些时候局部最优解推不出全局最优解时，就要用反悔贪心，在适当的时候撤销之前做出的决策。

我们先选取 $c$ 最小的 $k$ 个物品使用优惠劵，当前已经使用的价格是 $tot$。下文为方便表述，记使用优惠劵的物品集合为 $A$，他在求解过程中不是固定不变的。

当前考虑第 $i$ 个物品，由于 $k$ 张优惠券已经用完了，所以只能以原价 $p_i$ 购买物品 $i$。现在考虑反不反悔的条件是什么。

如果要反悔，那么用优惠券买 $i$ 的价格一定要小于用原价买 $i$。当 $i$ 用了优惠券，那么 $A$ 势必要有一个物品（记为 $j,j \in A$）做出退让，用原价来买 $j$。（其实相当于用 $i$ 来代替 $j$），那么一定满足以下不等式：

$$
tot-c_j+p_j+c_i<tot+p_i
$$

意思是：$i$ 代替 $j$ 用优惠券的价格比用原价买 $i$ 便宜，这个时候就需要反悔。

发现 $tot$ 可以消去：

$$
-c_j+p_j+c_i<p_i
$$

然后把下标相同的归在小于号的同一侧：

$$
p_j-c_j<p_i-c_i
$$

他们的形式是相同的，所以我们可以设 $\Delta_i=p_i-c_i$：

$$
\Delta_j<\Delta_i
$$

所以只要在已经使用优惠券的物品里面，存在一个 $j$，使得 $\Delta_j<\Delta_i$，我们就需要用 $i$ 代替 $j$ 使用优惠券。也就是 $k$ 个物品中，$(\Delta_j)_{\min}<\Delta_i$ 。注意这个不是恒等式，因为 $i \notin A$，但是 $j\in A$。

最小值可以用优先队列来求。

话不多说，上代码，代码中用 $delta$ 优先队列存储了上文中提到的 $\Delta_j,j\in A$，$P$ 存储原价 $p_i$，$C$ 存储优惠价 $c_i$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=50010;

int n,k,m;
int p[maxn],c[maxn];
bool buy[maxn];//buy[i] 表示第 i 个物品是否被买过
int ans=0;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >P,C;
priority_queue<int,vector<int>,greater<int> >delta;

signed main(){
	cin>>n>>k>>m;
	for(int i=1;i<=n;++i){
		cin>>p[i]>>c[i];
		P.push(make_pair(p[i],i));
		C.push(make_pair(c[i],i));
	}
	for(int i=1;i<=k;++i) delta.push(0);
	while(!P.empty()){
		pair<int,int> x1=P.top();
		pair<int,int> x2=C.top();
		if(buy[x1.second]){//如果被买过了，就跳过
			P.pop();
			continue;
		}
		if(buy[x2.second]){
			C.pop();
			continue;
		}
		if(delta.top() > x1.first-x2.first){//这个式子和上文推的式子时相反的，表示用原价买 i 更划算
			m-=x1.first;
			P.pop();
			buy[x1.second]=true;
		}
		else{//否则的话，就是用优惠券买 i 更划算
			m-=x2.first+delta.top();
			delta.pop();
			C.pop();
			buy[x2.second]=true;
			delta.push(p[x2.second]-c[x2.second]);
		}
		if(m>=0) ans++;
		else break;
	}
	cout<<ans<<endl;
	return 0;
}
```
最后，希望大家都能真正理解返回贪心，它的精髓就是“常思己过”！

>静坐常思己过，闲谈莫论人非。——明 · 罗洪先《醒世诗》

---

## 作者：Cuxhin (赞：37)

# P3045 [USACO12FEB] Cow Coupons G(详细推导题解)

感觉本题写题解的大佬们讲的不够清楚，题解说的反悔贪心看得懂，但是在代码里面就看不到反悔的过程，而且反悔也不知道反悔的什么，百思不得其解。希望我这篇题解能详细地将本题的贪心讲明白。

## 贪心阶段一。

一开始，我们可以很容易地想到最简单的贪心策略。**基础贪心策略**：

1. 将 每头牛 用优惠券买的价格 和 不用优惠券买的价格 统计在一起。

2. 每次取出花钱最少的一个价格，如果剩下的钱不够买这头牛就结束，够买则判断；

3. 如果这个价格不用优惠券买，就直接买；

   如果这个价格需要用优惠券买，如果还有优惠券就用掉一个优惠券来买，没优惠券了就跳过。

## 贪心阶段二。

但是自造数据测试，我们很快就能发现这个策略不是最优的。

> 3 2 6
>
> 5 1 (差为4)
>
> 3 1 (差为2)
>
> 6 2 (差为4)

如果我们采取刚才的策略，因为第一头和第二头牛用优惠券买的价格最小，我们会用掉两个优惠券买第一头和第二头牛，剩下来的钱不够买第三头牛，于是最终买了两头牛。但是如果我们用优惠券买第一头和第三头牛，最后会剩下三块钱，刚好能卖第二头牛，可以买三头牛。

哪个环节出问题了呢？用优惠券买第一头牛可以省下四块钱，用优惠券买第二头牛可以省下两块钱，用优惠券买第三头牛可以省下四块钱。我们可以发现，第三头牛省下的四块钱完全够买下第二头牛。这里就出问题了，**优惠券的使用不是最佳的**。于是我们用到**反悔贪心**，在先前的基础贪心策略上考虑上优惠券使用的策略。

划重点，这里我们反悔的不是 之前某头奶牛买不买，而是**优惠券使用在哪头奶牛上**，原因之后再阐释。通过转移优惠券的使用，我们可以省下优惠券省钱的差价，用于便宜购买新的奶牛。

例如刚才的数据，当我们进行基本贪心策略到了第三步，我们没有优惠券可以用了，这时我们发现如果在第三头牛上用优惠券，可以省下四块钱，而用在第二头奶牛上的优惠券只省下了两块钱。我们决定第二头牛不用优惠券，会多花 之前省下来的两块钱，将这个优惠券用在第三头奶牛上，我们会省下四块钱，$(-2)+(4)=2$，我们多省了两块钱，而第三头奶牛用优惠券买刚好用了两块钱，就可以多买一头牛了。这个转移优惠券过程中，第二头依然买下不动。即**买的过程中，已经买的牛不会再变化，买的牛只会越来越多。**

看不懂？我们将省钱换成赚钱理解。第二头奶牛不用优惠券，我们花了两块钱 $(-2)$；第三头奶牛用优惠券，我们赚了四块钱 $(-2+4)$；用优惠券买第三头奶牛，我们花了两块钱  $(-2+4-2)$。最终花的钱没有变化，但是我们多买了一头牛。

总结一下换票的过程。如果 **$C_j + (P_i - C_i) < P_j$**($P$代表原价，$C$代表用券买的价格)。够钱没票的情况下，考虑第j头奶牛时，一种情况是用原价卖，另一种情况是转移优惠券，转移优惠券到这头牛上，用的钱为 这头牛用优惠券的价格 加上 前面用优惠券的第 i 头奶牛省下的差价。两种情况都会比之前多买第 j 头奶牛，这里采用贪心，取花钱更少的情况。

但是，这里我们出现了问题。用原价用的是什么原价呢？第j头奶牛的原价？显然，不用优惠券买第j头牛不等于要用原价买第j头牛，同样是用原价，我们为什么不选择更便宜的用原价买的牛呢？因此，这里的原价是**最便宜的原价**。这里也是理解的关键点。转换下语意，我们要将 采用 最便宜的优惠价 的 转移优惠券 的 情况 与 选择 最便宜的原价 的 情况作比较，**原价和优惠价都是最便宜的价格，同时，转移优惠券时选择的优惠券应该也是省钱最少的优惠券**，这是我们贪心的关键之一。修改下公式，**$C_j + (P_i - C_i) < P_k $**（$C_j$指最便宜的优惠价，$(P_i-C_i)$指优惠最少的优惠券省下的钱，$P_k$指最便宜的原价）时，我们进行优惠券转移。

为什么我们不反悔买不买奶牛呢？这非常复杂。如果我们不卖第二头奶牛，我们不是可以省下四块钱和一张优惠券吗吗？当我们排除第二头奶牛，用这个券买第三头奶牛。然后剩下来三块钱。这三块钱我们显然可以买第二头奶牛，最终我们还是买了三头牛。但是这个过程，发生了钱的变化，优惠券的变化，买奶牛头数的变化，同时我们考虑的价格也有顺序的调整（第二头牛不考虑就扔后面了）。既然如此，我们为什么不只考虑转移优惠券来省钱呢？反正我们不买这头牛，我们总会接着考虑剩下的钱能不能买这头牛。我们不妨将买过的牛固定，只考虑未买的牛和优惠券。这是一种**固定变量**，一种贪心思路的简化。（竞赛时我很可能想不到简化喵，这也是贪心的难点了。）

总结下**改进后的贪心策略**：

1. 将每头牛用优惠券和价格和不用优惠券的价格按从小到大排序（同样价格的不用优惠券的放前面），放在两个队列里（此处用优先队列），按从小到大遍历两个队列。取最便宜的优惠价与最便宜的原价。同时我们用一个优先队列存储优惠券省下的钱（因为买下的牛，不管用不用券就不会再动，所以我们不需要考虑这个优惠券用在哪，只用考虑这个券省下多少钱就行了），并找到优惠最小的牛优惠了多少（差价）。
2. 如果原价比优惠价便宜，钱够就直接买。钱不够就结束。
3. 如果优惠价比原价便宜。
   1. 还有优惠券用，钱够就用优惠券买，不够就结束。
   2. 如果没优惠券用了，就比较之前优惠最小的牛。如果转移优惠券到这头牛，再补回之前优惠的差价，比用(最便宜)原价买更省钱的话，就转移优惠券。
   3. 如果转移优惠券不如原价买，就用原价买。不够就结束。

## 贪心阶段三。

理解刚才**改进贪心策略**后。在此基础上，我们还能进行优化。为何不一开始就将优惠券固定，将每个优惠券初始化为省了 0 元？这样我们就不用判断优惠券还有没有，可以空转优惠券。可以理解成如果还有剩余的优惠券，这个优惠券省钱为0，一定是省钱最少的那个，代入公式 **$C_j + (P_i - C_i) < P_k $**，则 **$(P_i - C_i)$** 等于0， 等效于 **$C_j < P_k$** ，就是我们改进贪心策略中原价与优惠价的比较。因此我们还可以少去一步比较原价与优惠价的过程，将其直接融入反悔。**优化后的改进贪心策略**如下：

1. 将每头牛用优惠券和价格和不用优惠券的价格按从小到大排序（同样价格的不用优惠券的放前面），放在两个队列里（此处用优先队列），按从小到大遍历两个队列。取最便宜的优惠价与最便宜的原价。同时我们用一个优先队列存储 **每个优惠券省下的钱，默认为0**。并找到优惠最小的牛优惠了多少（差价）。
2. **如果转移优惠券到这头牛，再补回之前优惠的差价，比用(最便宜)原价买更省钱的话，就转移优惠券。**

两种方法其实本质上是一样的，我看许多题解都直接跳到了改良之后，有点难以理解，于是我将**基本贪心策略**和**改进贪心策略**列了出来，方便理解。

## 代码实现。

然后用程序实现，两种策略都写了，可对照注释理解。
>代码不算长的，只是为了可读性稍微多换了行，就不扔云剪贴板了（

改进后贪心策略写法：

```cpp
//https://www.luogu.com.cn/problem/P3045
//Cuxhin、初心
#include<bits/stdc++.h>
#define N 500010
using namespace std;

long long n,k,m,s[N],sum=0,cnt=0;
//n头奶牛，k条券，m块钱，s代表第i个商品省下的钱，sum代表花的钱总数，cnt代表买了几头牛 
bool dic[N]={false};
//用来标记哪头奶牛买过的字典，买过就返回i

//奶牛 
class Cow{
public:
	long long page,value;
	//奶牛在字典上对应第几个，和买该奶牛需要用的钱（用优惠券或者不用优惠券的） 
	
	//无参构造 
	Cow(){}
	//有参构造 
	Cow(long long a,long long b):page(a),value(b){	}
	//奶牛是否买过（字典上是否标记） 
	bool check(){return dic[page];}
	//要买这头奶牛，在字典上标记它 
	void write(){dic[page]=true;return ;}
	//这头奶牛能省下多少钱 
	long long save(){return s[page];}
	//优先队列的比较函数，用的钱比较少的奶牛扔前面 
	//（用优惠券或者不用优惠券的） 
	friend bool operator<(Cow a,Cow b){
		return a.value>b.value;
	}
};

//优惠券 
class Ticket{
public:
	long long value;//这个优惠券省下来的钱 
	//无参构造 
	Ticket(){}
	//有参构造 
	Ticket(long long a):value(a){}
	//省下来的钱，const是因为优先队列内的Ticket是静态 
	long long save() const{return value;}
	//优先队列的比较函数，省钱比较少的奶牛扔前面 
	friend bool operator<(Ticket a,Ticket b){
		return a.value>b.value;
	}
};
//奶牛不用优惠券和用优惠券的临时变量 
Cow p_tmp,c_tmp;
//奶牛不用优惠券和用优惠券的优先队列 
priority_queue<Cow> p_que,c_que;
//优惠券的优先队列 
priority_queue<Ticket> ticket;
int main(){
	//优化输入 
	ios::sync_with_stdio();
	cin.tie(0);
	cout.tie(0);
	//输入奶牛数，优惠券数和钱数 
	cin>>n>>k>>m;
	//每个优惠券扔进队列，默认所有优惠券都没有省钱 
	for(int i=1;i<=n;i++){
		//输入第i头奶牛不用优惠券和用优惠券的价钱 
		long long p_itmp,c_itmp;
		cin>>p_itmp>>c_itmp;
		//第i头牛省下的钱 
		s[i]=p_itmp-c_itmp;
		//不用优惠券和用优惠券的钱分别扔进相关队列 
		p_que.push(Cow(i,p_itmp));
		c_que.push(Cow(i,c_itmp));
	}
/*未优化之前的朴素写法，用于理解贪心*/	//如果省钱和不省钱的队列其中一个为空，则所有奶牛都买过了
	while(!p_que.empty() and !c_que.empty()){
		//临时保存不用优惠券买奶牛需要花最少的钱
		//和用优惠券买奶牛需要花费最少的钱 
		p_tmp=p_que.top(),c_tmp=c_que.top();
		//如果用优惠券买过了 
		if(p_tmp.check()){
			p_que.pop();
			continue;
		}
		//如果不用优惠券买过了 
		if(c_tmp.check()){
			c_que.pop();
			continue;	
		} 
		if(p_tmp.value<c_tmp.value){//原价更便宜 
			sum+=p_tmp.value;//总花钱增加 
			p_que.pop();//原价的队列弹出 
			p_tmp.write();//字典标记这头奶牛表示已经买过 
		}
		else{//优惠券更便宜 
			if(ticket.size()<k){//还有优惠券 
				sum+=c_tmp.value;//总花钱增加 
				c_que.pop();//用优惠券买的队列弹出 
				c_tmp.write();//字典标记这头奶牛表示已经买过 
				//修改优惠券的队列 
				ticket.push(Ticket(c_tmp.save()));//用这个优惠券买这头奶牛省的钱弹进去 
			}
			else if(c_tmp.value + ticket.top().save() < p_tmp.value){//转移优惠券更便宜 
				sum+=c_tmp.value+ticket.top().save();//总花钱增加 
				c_que.pop();//用优惠券买的队列弹出 
				c_tmp.write();//字典标记这头奶牛表示已经买过 
				//修改优惠券的队列 
				ticket.pop();//优惠券的队列队头弹出 
				ticket.push(Ticket(c_tmp.save()));//用这个优惠券买这头奶牛省的钱弹进去 
			}
			else{//原价更便宜 
				sum+=p_tmp.value;//总花钱增加 
				p_que.pop();//原价的队列弹出 
				p_tmp.write();//字典标记这头奶牛表示已经买过 
			}
		}
		if(sum<=m){
			cnt++;//如果钱还够，就买成，总买的牛加一。 
		}
		else{
			break;//钱不够了，以后都买不成了。 
		}
	} 

	cout<<cnt;//输出能买的最多的牛 
	return 0;//剧终 
}
```
优化后的写法：
```cpp
//https://www.luogu.com.cn/problem/P3045
//Cuxhin、初心
#include<bits/stdc++.h>
#define N 500010
using namespace std;

long long n,k,m,s[N],sum=0,cnt=0;
//n头奶牛，k条券，m块钱，s代表第i个商品省下的钱，sum代表花的钱总数，cnt代表买了几头牛 
bool dic[N]={false};
//用来标记哪头奶牛买过的字典，买过就返回i

//奶牛 
class Cow{
public:
	long long page,value;
	//奶牛在字典上对应第几个，和买该奶牛需要用的钱（用优惠券或者不用优惠券的） 
	
	//无参构造 
	Cow(){}
	//有参构造 
	Cow(long long a,long long b):page(a),value(b){}
	//奶牛是否买过（字典上是否标记） 
	bool check(){return dic[page];}
	//要买这头奶牛，在字典上标记它 
	void write(){dic[page]=true;return ;}
	//这头奶牛能省下多少钱 
	long long save(){return s[page];}
	//优先队列的比较函数，用的钱比较少的奶牛扔前面 
	//（用优惠券或者不用优惠券的） 
	friend bool operator<(Cow a,Cow b){
		return a.value>b.value;
	}
};

//优惠券 
class Ticket{
public:
	long long value;//这个优惠券省下来的钱 
	//无参构造 
	Ticket(){}
	//有参构造 
	Ticket(long long a):value(a){}
	//省下来的钱，const是因为优先队列内的Ticket是静态 
	long long save() const{return value;}
	//优先队列的比较函数，省钱比较少的奶牛扔前面 
	friend bool operator<(Ticket a,Ticket b){
		return a.value>b.value;
	}
};
//奶牛不用优惠券和用优惠券的临时变量 
Cow p_tmp,c_tmp;
//奶牛不用优惠券和用优惠券的优先队列 
priority_queue<Cow> p_que,c_que;
//优惠券的优先队列 
priority_queue<Ticket> ticket;
int main(){
	//优化输入 
	ios::sync_with_stdio();
	cin.tie(0);
	cout.tie(0);
	//输入奶牛数，优惠券数和钱数 
	cin>>n>>k>>m;
	//每个优惠券扔进队列，默认所有优惠券都没有省钱 
	for(int i=1;i<=n;i++){
		//输入第i头奶牛不用优惠券和用优惠券的价钱 
		long long p_itmp,c_itmp;
		cin>>p_itmp>>c_itmp;
		//第i头牛省下的钱 
		s[i]=p_itmp-c_itmp;
		//不用优惠券和用优惠券的钱分别扔进相关队列 
		p_que.push(Cow(i,p_itmp));
		c_que.push(Cow(i,c_itmp));
	}

/*优化后的写法*/
    //初始化优惠券队列。
	for(int i=1;i<=k;i++) ticket.push(Ticket(0));
	//如果省钱和不省钱的队列其中一个为空，则所有奶牛都买过了
	while(!p_que.empty() and !c_que.empty()){
		//临时保存不用优惠券买奶牛需要花最少的钱
		//和用优惠券买奶牛需要花费最少的钱 
		p_tmp=p_que.top(),c_tmp=c_que.top();
		//如果用优惠券买过了 
		if(p_tmp.check()){
			p_que.pop();
			continue;
		}
		//如果不用优惠券买过了 
		if(c_tmp.check()){
			c_que.pop();
			continue;	
		} 
		//不用优惠券更省钱 
		if(p_tmp.value<c_tmp.value+ticket.top().save()){
			sum+=p_tmp.value;//总花钱增加 
			p_que.pop();//原价的队列弹出 
			p_tmp.write();//字典标记这头奶牛表示已经买过 
		}
		else{
			sum+=c_tmp.value+ticket.top().save();//总花钱增加 
			c_que.pop();//用优惠券买的队列弹出 
			c_tmp.write();//字典标记这头奶牛表示已经买过 
			//修改优惠券的队列 
			ticket.pop();//优惠券的队列队头弹出 
			ticket.push(Ticket(c_tmp.save()));//用这个优惠券买这头奶牛省的钱弹进去 
		}
		if(sum<=m){
			cnt++;//如果钱还够，就买成，总买的牛加一。 
		}
		else{
			break;//钱不够了，以后都买不成了。 
		}
	}
	cout<<cnt;//输出能买的最多的牛 
	return 0;//剧终 
}
```

## 总结反思。

本题是很好的一道练习反悔贪心的题目，在思考贪心策略的时候应该循序渐进，步步深入改良，不要一步登天。我们可以通过固定一些变量来辅助我们明确贪心策略。如本题固定了奶牛数量。然后在一些关键的值考虑取最值来实现贪心。就到这了吧，谢谢观看。

---

## 作者：XLao (赞：16)

来点没脑子的暴力做法，不过估计这篇题解也没人看到吧。。

正解是：$C$ 值前 $K$ 小一定买，然后反悔贪心，确实润。但是我没发现。

考虑我们能够 wqs 二分求出“买 $x$ 头奶牛，用恰好 $K$ 个优惠券时的最小花费”，这个 最小花费-K 图像是下凸的（感觉一下，就是越到后面能优惠的幅度越小），所以可以 wqs 二分。

那既然这样，外层再二分答案 $x$ 就好了。$O(n\log^2 n \log V)$。其中 $V=10^9$，有两个 $\log n$ 是因为 wqs 二分的 `check` 里面用堆写了。需要吸氧，但是不需要脑子（。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define mkp make_pair
#define fr first
#define sc second
const int N=5e4+1;

int n,K,a[N],b[N]; ll m,ans;
bool check(int cost,int x)
{
	priority_queue< pii,vector<pii>,greater<pii> > q;
	for(int i=1;i<=n;++i)
	{
		if(b[i]+cost<a[i]) q.push(mkp(b[i]+cost,1));
		else q.push(mkp(a[i],0));
	}
	int cnt=0; ans=0;
	for(int i=1;i<=x;++i)
	{
		cnt += q.top().sc;
		ans += q.top().fr; q.pop();
	} return cnt>K;
}
ll get(int x)
{
	int l=0, r=1e9;
	while(l<r)
	{
		int mid=(l+r)>>1;
		check(mid,x) ? l=mid+1 : r=mid;
	} check(l,x);
	return ans - 1ll*K*l;
}

int main()
{
	scanf("%d %d %lld",&n,&K,&m);
	for(int i=1;i<=n;++i) scanf("%d %d",&a[i],&b[i]);
	int l=1, r=n+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		get(mid)<=m ? l=mid+1 : r=mid;
	} printf("%d\n",l-1);
}
```

---

## 作者：_ZSR_ (赞：15)

### [P3045 [USACO12FEB]Cow Coupons G](https://www.luogu.com.cn/problem/P3045)

读完题后我们发现并没有什么好的思路，可以考虑先把 $k$ 张优惠卷用在 $k$ 个最小的 $c$ 的奶牛上，然后再做调整。

那么该如何调整优惠券的使用呢？我们可以开三个优先队列，一个存每一头牛的原价，一个存每一头奶牛使用优惠卷后的价格，一个存放原价和使用优惠卷后的价格的差。一开始先把所有的原价和优惠价放入队列，然后在存放差值的队列中放入 $k$ 个 $0$，表示使用 $k$ 张优惠卷，即不用补差价。

接着便是调整优惠卷的使用。我们每一次取出存放原价和优惠价的队列的队头，根据贪心，如果按原价买更便宜，我们就按原价买，如果按优惠价买并且补上差价更便宜，我们就使用优惠卷。最后，我们把这头奶牛打上标记，防止之后再被取出。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=50010;
typedef pair<int,int> pii;
int n,k,m;
int p[N],c[N];
bool st[N];
priority_queue<pii,vector<pii>,greater<pii>> qp,qc;
priority_queue<int,vector<int>,greater<int>> qd;
signed main()
{
	scanf("%lld%lld%lld",&n,&k,&m);
	for (int i=1;i<=n;++i)
	{
		scanf("%lld%lld",&p[i],&c[i]);
		qp.push({p[i],i});
		qc.push({c[i],i});
	}
	for (int i=1;i<=k;++i) qd.push(0);
	int sum=0,tot=0;
	while (qp.size())
	{
		auto tp=qp.top();
		auto tc=qc.top();
		if (st[tp.second])//之前用过
		{
			qp.pop();
			continue;
		}
		if (st[tc.second])//之前用过
		{
			qc.pop();
			continue;
		}
		if (tp.first<tc.first+qd.top())//按原价更便宜
		{
			if (sum+tp.first>m) break;
			sum+=tp.first;
			tot++;
			qp.pop();
			st[tp.second]=true;
		}
		else //拿一张之前用过的优惠卷过来用到这头奶牛上
		{
			if (sum+tc.first+qd.top()>m) break;
			sum+=tc.first+qd.top();
			tot++;
			qc.pop();
			st[tc.second]=true;
			qd.pop();
			qd.push({p[tc.second]-c[tc.second]});
		}
	}
	printf("%lld\n",tot);
	return 0;
}
```


---

## 作者：Hoks (赞：8)

## 前言
[题目链接](https://www.luogu.com.cn/problem/P3045)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-p3045)内食用也许更佳。

~~P.S.暑假集训的时候的一道模拟赛中的题，用集训给的有且仅有的一次超强数据干爆了一些题解，现在也来补篇题解。~~
## 思路分析
看到这个题面的瞬间相信大家都会想到贪心。但是写完贪心后一测，不难发现直接贪心得到的不一定是最优解，所以这个贪心是需要反悔的。

首先考虑正常的贪心，用两个堆压入用了券的值和不用券的值，每次选择最小价格的牛买入。最后就可以得到这种情况下最多能买多少牛。

接着考虑反悔，对于我们反悔的代价便是用券的值减去不用券的值，也就是多花费的钱数。多开一个堆，在每次买牛的把这个反悔代价放入堆中。

对于每头牛都先考虑买下来，如果没钱了考虑反悔一个然后用优惠券买下来。如果都不行了那就肯定买不了更多的牛了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,m,ans;
struct node{int p,c;}a[50010];
priority_queue<int> q;
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
bool cmp1(node tmp1,node tmp2){return tmp1.c<tmp2.c;}
bool cmp2(node tmp1,node tmp2){return tmp1.p<tmp2.p;}
signed main()
{
    n=read(),k=read(),m=read();
    for(int i=1;i<=n;i++) a[i].p=read(),a[i].c=read();
    sort(a+1,a+1+n,cmp1);
    if(k<n) sort(a+k+1,a+1+n,cmp2);
    for(int i=1;i<=n;i++)
    {
        if(k)
        {
            if(m<a[i].c) break;
            k--,ans++,m-=a[i].c;
            q.push(-a[i].p+a[i].c);
        }
        else if(m>=a[i].p)
        {
            ans++,m-=a[i].p;
            if(!q.empty()&&a[i].p-a[i].c+q.top()>0) m+=a[i].p-a[i].c+q.top(),q.pop(),q.push(-a[i].p+a[i].c);
        }
        else if(!q.empty()&&m+a[i].p-a[i].c+q.top()>=a[i].p)
        {
            ans++,m+=-a[i].c+q.top();
            q.pop(),q.push(-a[i].p+a[i].c);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：xiezheyuan (赞：7)

**摘要：本文将从模拟费用流的角度来研究本题。**

## 简要题意

有 $n$ 头牛，$K$ 张优惠券，$M$ 块钱。购买第 $i$ 头牛有两种方法：

- 花费 $p_i$ 元。
- 花费一张优惠券，然后只需要花费 $c_i$ 元。

求最终钱数非负的前提下，最多可以购买多少头牛。

$1\leq K\leq n\leq 5\times10^4,1\leq c_i\leq p_i\leq 10^9,1\leq M\leq 10^{14}$

## 思路

看到这道题，不难想到一个经典的费用流模型。大概长这样（以 $4$ 头牛为例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/do76itf6.png)

[Graphviz 链接](http://u5a.cn/itIMB)

其中形如 Ix 的点表示牛。形如 Ox 的点表示牛选择使用原价购买，C 表示牛选择使用优惠券购买。S 和 T 分别表示超级源点和超级汇点。边上的二元组中，第一个表示容量，第二个表示费用。

原问题就转变成了限制总费用 $\leq M$ 的最大流问题。

先考虑随便选择一种方案，然后再逐步进行调整。假如我们选择 $c$ 的前 $k$ 小选择使用优惠券，其他的暂时不知道怎么选。

考虑新的一个点我们该如何选择，说白了就是如何在图上增广。我们事实上有下面几种增广情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/6vasly90.png)

第一种，如上图所示，直接原价购买。

第二种情况显然需要使用优惠券，但是优惠券已经被我们提前用光了，所以只能通过先走反悔边退流，让出 $1$ 个单位的流量。

实际上还有一种情况，就是干脆以前的点不选了，改选其他点，这种决策会导致答案不变，而费用增加，我们就没必要干了（具体原因和之后的贪心策略有关，假如之前选择 C 现在还选 C 反而更优，则违反堆性质，假如之前选 C 现在改选 P 反而更优，则违反先选择最小的这一性质，其余情况同理，不过现在请大家忽略这一种情况）。

第一部分，退流：

![](https://cdn.luogu.com.cn/upload/image_hosting/m9eltpfj.png)

第二部分，重新走 C 点：

![](https://cdn.luogu.com.cn/upload/image_hosting/v33mrboj.png)

分析完这些情况后，我们再来看一下费用的变化：

- 第一种情况，需要增加 $p_i$ 的费用。
- 第二种情况，假设被退流的是 $j$，则需要增加 $p_j-c_j+c_i$ 的费用。

第一种情况，我们可以开一个关键字为 $p$ 的小根堆。第二种情况，由于选择哪个 $j$ 只对费用产生影响，所以我们可以用小根堆找出走过 C 的点中 $p-c$ 最小值。至于 $c_i$，我们同样可以开一个关键字为 $c$ 的小根堆。

对于之后 $k+1\sim n$，我们找出 $p,c$ 关键字小根堆各自的堆顶，$p$ 对应增加 $p_i$ 费用，$c$ 对应增加 $p_j-c_j+c_i$ 费用，找出最小值，对这个最小值对应的增广路进行增广即可。

注意题目要求费用 $\leq M$，而之后的过程中我们不可能减少费用（题目限制 $p,c$ 均为正数，且 $p\geq c$）。所以只要当前费用 $>M$ 就结束循环是靠谱的。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e4 + 5;
struct cow { int c, p; } a[N];
int n, m, k, ans;

template<class T> using heap = priority_queue<T, vector<T>, greater<T> >;
bitset<N> used;
heap<int> q;
heap<pair<int,int> > sp, sc;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> k >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i].p >> a[i].c;
    }
    sort(a+1, a+n+1, [](cow x, cow y){return x.c < y.c;});
    for(int i=1;i<=k;i++){
        if(m < a[i].c) break;
        ans++; m -= a[i].c;
        q.push(a[i].p - a[i].c); used[i] = 1;
    }
    for(int i=(k+1);i<=n;i++){
        sp.push({a[i].p, i});
        sc.push({a[i].c, i});
    }
    for(int i=(k+1);i<=n;i++){
        while(!sc.empty() && used[sc.top().second]) sc.pop();
        while(!sp.empty() && used[sp.top().second]) sp.pop();
        // cout << sc.size() << sc.top().second << ' ' << sp.size() << sp.top().second << '\n';
        int xc = sc.top().second, xp = sp.top().second;
        int yc = (q.empty() ? LLONG_MAX : (q.top() + a[xc].c)), yp = a[xp].p;
        if(yc < yp){
            // cout << xc << '\n';
            if(m < yc) break;
            ans++; m -= yc;
            q.pop(); used[xc] = 1; q.push(a[xc].p - a[xc].c); sc.pop();
        }
        else{
            // cout << xp << '\n';
            if(m < yp) break;
            ans++; m -= yp; used[xp] = 1; sp.pop();
        }
    }
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：C_Pos_Princess (赞：6)

# P3045 [USACO12FEB] Cow Coupons G

#### 化简题意：

商场里共 $N$ 件商品，对于第 $i$ 件商品，价格为  $c_i$ ，会员价为  $p_i$ ，保证会员价 不会比原价高。

会员最多只能享受 $K$ 次会员价。

小明是会员，他有 $M$ 元钱。

问：他最多可以买多少件商品？

#### 算法   ： 反悔贪心

#### 思路流程：

既然可以享受 $k$ 次，不如考虑极端情况，先使用 $k$ 个最小的优惠券，再考虑更改

那么更改的条件是什么样的呢。

用 $tot$ 表示现在用了多少钱，$i$ 为已使用的优惠券之一，$j$ 为未购买的一个物品。

如果用原价买 $j$ ：需要用  $ tot+pj $ 元。

如果用优惠价买 $j$ : 需要用  $tot - ci + pi + cj$  元。

如果要换成用原价买 $i$ ，用优惠价买 $j$ 。

则必须满足  $ tot - ci + pi + cj <  tot+pj $ 。

消去 $tot$  ,移项，得到 $pi - ci < pj - cj$ 。

所以记录 优先队列 $delta$  , 维护即可。



#### 代码实现

关于其他题解一些模糊的地方，这里都讲解了。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long   //注意long long
const int maxn = 50010;
int n, k, m;
int p[maxn], c[maxn];
bool buy[maxn];
int ans = 0;
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > P, C;
priority_queue<int, vector<int>, greater<int> > delta;

signed main() {
	cin >> n >> k >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld", &p[i], &c[i]);
		P.push({p[i], i});    //自动调用函数 
		C.push({c[i], i});
	}
	for (int i = 1; i <= k; i++) delta.push(0);
	//初始化k个，这个样子可以保证后面delta里面一共就k个 

	while (!P.empty()) {
		//每次循环加入一个物品，直到m<0 
		pii x1 = P.top();
		pii x2 = C.top();
		if (buy[x1.second]) {    //买过的不要了 
			P.pop();
			continue;
		}
		if (buy[x2.second]) {
			C.pop();
			continue;
		}

		//如果用优惠券，则需要delta.top+x2.first
		//原价，需要x1.first
		//比较即可 
		if (delta.top() + x2.first> x1.first ) {
			m -= x1.first; //原价买比较好
			P.pop();
			buy[x1.second] = true;
		} else {
			m -= x2.first + delta.top(); //用优惠券 另一个原价
			delta.pop();
			C.pop();
			buy[x2.second] = true;
			delta.push(p[x2.second] - c[x2.second]);
		}

		if (m >= 0) ans++;
		else break;

	}
	cout << ans << endl;


	return 0;
}
```

---

## 作者：OIer_ACMer (赞：5)

# 题目解析：


本题一开始，我们可以直接发现我们先贪心找出优惠券和原价相比**优惠券永远是最小的**，那么，我们直接排序，然后，取出 $k$ 个优惠券序列的最小值，加入答案。接着，再对原序列排序，同样在保证还有钱的情况下取出剩余的牛，代码，便完成了，吗？

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, k, m;
struct node
{
    int p, c;
    bool b = 0;
} cows[1000009], cow[1000009];
priority_queue<int, vector<int>, greater<int>> q;
bool cmp(node a, node b)
{
    return a.c < b.c;
}
bool cmp1(node a, node b)
{
    return a.p < b.p;
}
int ans = 0;
signed main()
{
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> cows[i].p >> cows[i].c;
        cow[i].p = cows[i].p;
        cow[i].c = cow[i].c;
    }
    sort(cows + 1, cows + n + 1, cmp);
    for (int i = 1; i <= k; i++)
    {
        if (m >= cows[i].c && cows[i].b == 0)
        {
            ans++;
            m -= cows[i].c;
            cows[i].b = 1;
        }
    }
    sort(cows + 1, cows + n + 1, cmp1);
    for (int i = 1; i <= n; i++)
    {
        if (m >= cows[i].p && cows[i].b == 0)
        {
            ans++;
            m -= cows[i].p;
            cows[i].b = 1;
        }
        if (m <= 0)
        {
            break;
        }
    }
    cout << ans;
    return 0;
}

```

很好，我们发现，我们可以过原来的数据，但是还不能通过全部，这时，我们就要来分析一下，是否还存在别的情况。

一开始，我们当然要用贪心消耗掉我们手上的优惠券，毕竟我们已经知道优惠券一定与原来相比划算，但是，如果我们遇上这样的数据：

![](https://cdn.luogu.com.cn/upload/image_hosting/2qihizqq.png)

那么，我们原来的代码**会直接选中第二头牛，但是第一头与第三头加起来才是最小的**，面对这种情况，我们就要在第一次贪心完成之后**进行反悔**，具体内容如下。

首先，在第一次贪心的同时，我们用一个**优先队列储存每一只选中的牛的价格差值**，怎么用看下面的解释。

其次，我们要用两个优先队列保存原来的价格与原来的优惠价格（用优先队列的原因是因为无论什么时候我们都要选取最小的原价优惠价格），之后，我们可以在 $k$ 个之后进行比较，当我们发现目前如果我们**扔掉原先选择的牛的最小差值（也就是第一个优先队列的队首），补齐它的差价，也就是反悔了，再加上目前这头牛的优惠价小于这头牛的原价，就说明我们有了比直接买下这头牛更好的选择**。这时，我们就像前面所说的一样，扔点原先选的，补齐差价，再将此时的这头刚被选的牛的差价放入差价队列，就是第一个优先队列。

如果没有这种情况，那么直接扫码付款，毕竟有钱为什么不花呢？

------------


## 注意四个点

一个是在第一次贪心的时候如果已经发现钱不够了，直接输出，毕竟**连优惠价格都买不下还谈什么原价**？

如果优惠券的张数为总共的牛数，直接输出，毕竟，优惠价一定小于原价。

再就是，在第二次遍历的过程中，如果钱不够，直接输出，避免越界。

一定要记得在删牛的时候加上记录是否被删的标签！！！

------------
# 代码如下：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int ans = 0;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int p, c;
} cows[1000009];
struct nx
{
    int first, second;
};
priority_queue<int, vector<int>, greater<int>> q;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q1, q2;
int vis[1000009];
bool cmp1(node a, node b)
{
    return a.c < b.c;
}
// bool cmp2(node a, node b)
// {
//     return a.p < b.p;
// }
int n, k, m;
void zzx()
{
    sort(cows + 1, cows + 1 + n, cmp1); // 情况1：当用优惠券买牛时
    int dj = 0;
    for (int i = 1; i <= k; i++)
    {
        dj += cows[i].c;

        if (dj > m)
        {
            cout << i - 1 << endl;
            return; // 用优惠券的情况已经超过了农夫的余额（优惠的不彻底）
        }
        q.push(cows[i].p - cows[i].c); // 为之后在没优惠券的情况下，通过比较之后的优惠价格与现在的差额之和的大小买牛
    }
    if (k == n)
    {
        cout << n << endl;
        return; // 用有限的优惠券买下全部的牛
    }
    ans = k;
    // sort(cows + 1 + k, cows + n + 1, cmp2);
    // for (int i = k + 1; i <= n; i++)
    // {
    //     int dj = q.top();
    //     // cout << dj << endl;
    //     if (dj < cows[i].p - cows[i].c && !q.empty())
    //     {
    //         dj += dj;
    //         dj += cows[i].c;
    //         q.pop();
    //         q.push(cows[i].p - cows[i].c);
    //     }
    //     else
    //     {
    //         dj += cows[i].p;
    //     }
    //     if (dj > m)
    //     {
    //         return;
    //     }

    //     ans++;
    // }历史遗迹
    for (int i = k + 1; i <= n; i++) // 情况2：当用原价买牛时
    {
        q1.push(make_pair(cows[i].c, i));
        q2.push(make_pair(cows[i].p, i));
    }
    for (int i = k + 1; i <= n; i++)
    {
        while (vis[q1.top().second])
        {
            q1.pop();
        }
        while (vis[q2.top().second])
        {
            q2.pop();
        }
        int p1 = q1.top().second;
        int p2 = q2.top().second;
        int xianzai = q1.top().first;
        int chazhi = q.top();
        int xianzaiyuan = q2.top().first;
        if (xianzai + chazhi < xianzaiyuan)//差值+现在的优惠价格
        {
            dj += xianzai + chazhi;
            q.pop();
            q1.pop();
            q.push(cows[p1].p - cows[p1].c);
            vis[p1] = 1;
        }
        else // 有钱且现在付得起就买牛
        {
            dj += xianzaiyuan;
            q2.pop();
            vis[p2] = 1;
        }
        ans++;
        if (dj > m) // 没钱了
        {
            cout << ans - 1 << endl;
            return;
        }
    }
    cout << n << endl;
    return;
}
signed main()
{
    n = read();
    k = read();
    m = read();
    for (int i = 1; i <= n; i++)
    {
        cows[i].p = read();
        cows[i].c = read();
    }
    zzx();

    // cout << ans << endl;
    return 0;
}

```

---

## 作者：A_small_WA (赞：5)

这题是一道有趣的反悔贪心。

## 一、反悔贪心

 什么是反悔贪心呢？贪心是一种基础算法，**通过每一步都取当前最优解**来做到最优策略。只要保证每一步的策略都是最优的，那么即使不关注全局，也能保证当前的这种方案最优。
 
 但是当由于某种原因（如本题的总价格限制）不能够在每一步都取最优解时，就需要从之前已经选好的方案中放弃一些，来加入当前的最优解。与回溯不同的是，反悔贪心并不需要从头开始，而是**从所有已经选择的方案中找出最劣的并放弃**即可。
 
想做反悔贪心的读者可以尝试一下[P4053](https://www.luogu.com.cn/problem/P4053)，[P2107](https://www.luogu.com.cn/problem/P2107)等题。
 
## 二、本题思路

首先思考贪心策略。第一步肯定是将 $k$ 张优惠券用在 $c$ 值前 $k$ 小的牛上，然后将剩下的牛按 $p$ 值排序，每次选择 $p$ 值最小的购买，可以保证总价格最少。

但是如果按上面的方法，有一些使用了优惠券的牛优惠的价格可能不是最大化。由于优惠券的数量是有限的，所以我们希望优惠券的优惠力度尽量的大，即要从之前用过优惠券的牛中优惠力度最小的优惠券拿给之后优惠力度较大的牛使用。

## 三、代码实现

对于上面的思路，我们可以先将 $c$ 值前 $k$ 小的牛用 $c$ 的价格买下，并用一个小根堆优先队列 $p$ 储存优惠的价格（待会要用），然后考虑在 $k+1 \sim k + n$ 之间的牛进行反悔操作。以下为 $c$ 值在 $k+1 \sim k + n$ 之间的牛的具体操作。

先建立两个小根堆 $pc$ 和 $pp$ ,用来储存当前 $p$ 值最小的牛和当前 $c$ 值最小的牛。当有一头牛加入时，有两种选择：
1. 直接以 $p$ 的价格购买当前 $p$ 值最小的牛；
2. 将当前优惠价格最少的牛的优惠券拿给当前 $c$ 值最小的牛使用。

最后比较两种方案的花费，选择最小的一种进行购买。即比较 $pp.top()$ 和 $pc.top() + q.top()$ 的大小。

注意：
一、 由于 $pp$ 和 $pc$ 不能同步，所以要用一个标记数组来储存已经被买下的牛。
二、 每当有买入或反悔操作时，都要判断当前花费在不在 $m$ 之内，及时输出答案。
三、 当前价格要开`long long`。

## 四、代码

以下为主要代码部分——
```cpp
/*建立三个小根堆的部分就不展示了,cz 表示优惠价格，
pr 表示 pi，yh 表示 ci，bh 表示编号*/
int main(){
	long long n,k,m;
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i].pr>>c[i].yh;
		c[i].cz=c[i].pr-c[i].yh;
		c[i].bh=i;
	}
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=k;i++){
		dqjg+=c[i].yh;
		if(dqjg>=m){
			cout<<ans;
			return 0;
		}
		ans++;
		pyp.push(c[i].cz);
      //贪心选k个优惠后c最小的奶牛
	}
	for(int i=k+1;i<=n;i++){
		d[i].bh=i;
		d[i].yh=c[i].yh;
		d[i].pr=c[i].pr;
		d[i].cz=c[i].cz;
      //为防止编号混乱，再建一个结构体
		pp.push(d[i]);
		py.push(d[i]);
	}
	int flag=0;
	for(int i=k+1;i<=n;i++){
		while(pp.size()&&bj[pp.top().bh]!=0) pp.pop();
		while(py.size()&&bj[py.top().bh]!=0) py.pop();
		if(pp.top().pr<=py.top().yh+pyp.top()){
			dqjg+=pp.top().pr;
			bj[pp.top().bh]=1;//标记这个牛被买了
			pp.pop();
        //不用优惠券，直接买p值最小的奶牛
		}else{
			dqjg=dqjg+py.top().yh+pyp.top();
			bj[py.top().bh]=1;//标记这个牛被买了
			pyp.push(d[py.top().bh].cz);//更改最小的优惠价格
			pyp.pop(),py.pop();
        //反悔用优惠券，买c值最小的奶牛
		}
		ans++;
		if (dqjg>m){
			flag=1;
			break;
		}
	}
	if (flag==1) cout<<ans-1;
	else cout<<ans;
	return 0;
}
```
这是蒟蒻写的第三篇题解，支持一下孩子吧！

---

## 作者：tanyulin (赞：5)

记 $d_i=P_i-C_i$，表示用优惠劵能优惠的钱数。

最后会有一些牛用优惠劵买，有一些牛用原价买，那么用优惠劵买的牛的 $d$ 一定大于用原价买的牛的 $d$，否则把这张优惠劵用来买原价的这头牛肯定更优。

所以把所有牛按 $d$ 排序后，一定可以找到一个分界点 $i$，使得 $i$ 之前的牛都只用优惠劵买，$i + 1$ 及之后的牛都只用原价买，那么我们把  $1\sim i$ 的牛前 $k$ 小的**优惠价格**和 $i+1\sim n$ 的牛的**原价**拿出来排序，一个一个取直到取到总价格超过 $m$。

然后你发现，分界点 $i$ 右移的过程中，只有 $i$ 和 $i+1$ 的状态发生了切换，因此我们可以用一个数据结构来维护所有价格，支持插入删除以及查不超过 $m$ 最多选几个，可以使用权值线段树然后线段树上二分，也可以像我一样离散化后树状数组上二分。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
int n, k, tot, cnt[N], lsh[N], ans;
priority_queue<int> q;
LL m, sum[N];
struct node {
	int c, p;
	bool operator<(const node &B) {
		return p - c > B.p - B.c;
	}
}a[N];
int find(int x) {
	return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}
int lowbit(int x) {
	return x & (-x);
}
void add(int x, int v) {
	for(int i = x; i <= tot; i += lowbit(i))
		cnt[i] += v, sum[i] += lsh[x] * v;
}
int qry() {
	LL now = 0;
	int pos = 0, res = 0;
	for(int i = 18; i >= 0; i--)
		if(pos + (1 << i) <= tot && now + sum[pos + (1 << i)] <= m)
			pos += 1 << i, res += cnt[pos], now += sum[pos];
	return res;
}
int main() {
	cin>>n>>k>>m;
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i].p, &a[i].c);
		lsh[++tot] = a[i].c;
		lsh[++tot] = a[i].p;	
	}
	sort(a + 1, a + 1 + n);
	sort(lsh + 1, lsh + 1 + tot), tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
	for(int i = 1; i <= n; i++) add(find(a[i].p), 1);
	for(int i = 0; i <= n; i++) {
		ans = max(ans, qry());
		if(i < n) {
			add(find(a[i + 1].p), -1);
			add(find(a[i + 1].c), 1);
			q.push(a[i + 1].c);
			if((int)q.size() > k) {
				int val = q.top();
				q.pop();
				add(find(val), -1);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：tsqtsqtsq0309 (赞：4)

[更好的阅读体验](https://www.cnblogs.com/tsqtsqtsq/p/17832379.html)

小清新数据结构题。

令已经确定被购买的奶牛的集合为 $S$。

注意到必然存在一个最优解使得集合 $S$ 中 $P_i-C_i$ 前 $k$ 大的奶牛使用了优惠券。

证明：

令使用优惠券的集合为 $S'$，显然有 $|S'|=k$，则花费为：
$$
\sum_{i\in S\wedge i\notin S'}P_i+\sum_{i\in S'}C_i \\
=\sum_{i\in S}P_i-\sum_{i\in S'}P_i+\sum_{i\in S'}C_i \\
=\sum_{i\in S}P_i-\sum_{i\in S'}(P_i-C_i) \\
$$
其中 $\sum_{i\in S}P_i$ 为定值。

不难发现 $\sum_{i\in S'}(P_i-C_i)$ 需要取到最大值，即 $S$ 中 $P_i-C_i$ 前 $k$ 大的在 $S'$ 中。

证毕。

令 $S=\left\{1,2,\cdots,n\right\}$，试调整 $S$ 使得其最小花费小于等于 $m$。考虑从 $S$ 中删除一个元素 $x$ 对于最小花费的贡献：

1. $x\notin S'$，则最小花费减小 $P_x$。
2. $x\in S'$，此时 $x$ 被删除之后，满足 $P_i-C_i$ 最大的 $i(i\notin S')$ 被并入 $S'$，则最小花费减小 $C_x+P_i-C_i$。

则要使 $|S|$ 最大，则就要使每次选取对最小花费减小的贡献最大的 $x$ 删除，即删除 $\max_{x\notin S'}P_x$ 或 $\max_{x\in S'}C_x\max_{i\notin S'}(P_i-C_i)$，直到最小花费小于等于 $m$ 。

至于具体实现的话，可以考虑用 $3$ 个优先队列来维护。

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define MAXN 50005
using namespace std;
struct node0{
    int p, c, id;
    bool friend operator<(node0 a, node0 b){
        return a.p - a.c < b.p - b.c;
    }
}cow[MAXN];
struct node1{
    int c, id;
    bool friend operator<(node1 a, node1 b){
        return a.c < b.c;
    }
};
struct node2{
    int p, c, id;
    bool friend operator<(node2 a, node2 b){
        return a.p < b.p;
    }
};
int n, k, ans;
long long m, cost;
bool vis[MAXN];
priority_queue <node0, vector <node0>, less <node0>> q0;
priority_queue <node1, vector <node1>, less <node1>> q1;
priority_queue <node2, vector <node2>, less <node2>> q2;
int read(){
    int t = 1, x = 0;char ch = getchar();
    while(!isdigit(ch)){if(ch == '-')t = -1;ch = getchar();}
    while(isdigit(ch)){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * t;
}
long long _read(){
    long long t = 1, x = 0;char ch = getchar();
    while(!isdigit(ch)){if(ch == '-')t = -1;ch = getchar();}
    while(isdigit(ch)){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * t;
}
bool cmp(node0 a, node0 b){
    return a.p - a.c > b.p - b.c;
}
int main(){
    n = read();k = read();m = _read();
    for(int i = 1 ; i <= n ; i ++)
        cow[i].p = read(),cow[i].c = read();
    for(int i = 1 ; i <= n ; i ++)cow[i].id = i;
    ans = n;cost = 0;sort(cow + 1, cow + n + 1, cmp);
    for(int i = 1 ; i <= k && i <= n ; i ++){
        q1.push((node1){cow[i].c, cow[i].id});
        cost += (long long)cow[i].c;
    }
    for(int i = k + 1 ; i <= n ; i ++){
        q0.push((node0){cow[i].p, cow[i].c, cow[i].id});
        q2.push((node2){cow[i].p, cow[i].c, cow[i].id});
        cost += (long long)cow[i].p;
    }
    while(cost > m){
        while(!q0.empty() && vis[q0.top().id] == true)q0.pop();
        while(!q2.empty() && vis[q2.top().id] == true)q2.pop();
        if(q0.empty() || q2.empty()){
            node1 max = q1.top();q1.pop();
            cost -= (long long)max.c;ans--;
        }else{
            node0 dmax = q0.top();
            node1 cmax = q1.top();
            node2 pmax = q2.top();
            if(pmax.p > cmax.c + dmax.p - dmax.c){
                cost -= (long long)pmax.p;ans--;
                vis[pmax.id] = true;q2.pop();
            }else{
                cost -= (long long)(cmax.c + dmax.p - dmax.c);ans--;
                vis[dmax.id] = true;q0.pop();q1.pop();
                q1.push((node1){dmax.c, dmax.id});
            }
        }
    }
    cout << ans << endl;return 0;
}
```

---

## 作者：__Remake__ (赞：4)

神奇小题目。

首先我们注意到，假定已经确定被购买的奶牛的集合 $S$，则必然存在一个最优解，使得 $S$ 中 $P_i - C_i$ 前 $k$ 大的奶牛使用了优惠券，证明如下：

$\qquad$ 假设使用优惠券的集合为 $S'$，$|S'| = k$，则花费为：

$$
\begin{aligned}
& \sum_{i \in S \land i \notin S'} P_i + \sum_{i \in S'} C_i\\
= & \sum_{i \in S} P_i - \sum_{i \in S'} P_i + \sum_{i \in S'} C_i\\
= & \sum_{i \in S} P_i - \sum_{i \in S'} (P_i - C_i)
\end{aligned}
$$

$\qquad$ 其中 $\sum_{i \in S} P_i$ 为定值，则 $\sum_{i \in S'} (P_i - C_i)$ 需最大，即 $S$ 中 $P_i - C_i$ 前 $k$ 大的在 $S'$ 中。

现在我们假设 $S = \{1, 2, \cdots, N\}$，调整 $S$ 使得其最小花费 $\le m$，考虑从 $S$ 中删除一个元素 $x$ 对最小花费的贡献：

1. $x \notin S'$，则最小花费减小 $P_x$。
2. $x \in S'$，此时 $x$ 被删除后，满足 $P_i - C_i$ 最大的 $i\ (i \notin S')$ 被并入 $S'$，则最小花费减小 $C_x + P_i - C_i$。

则欲使最终 $|S|$ 最大，则需要每次选取对最小花费减小的贡献最大的 $x$ 删除，即删除 $\max_{x \notin S'} P_x$ 或 $\max_{x \in S'} C_x + \max_{i \notin S'}(P_i - C_i)$，直至最小花费 $\le m$ 时结束。

代码如下：

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>

#define MAXN 50005

using namespace std;

typedef long long ll;

struct pr {
    int p, c, id;

    bool operator < (const pr& o1) const {
        return p - c < o1.p - o1.c;
    }
} cow[MAXN];

struct pr0 {
    int c, id;

    bool operator < (const pr0& o1) const {
        return c < o1.c;
    }
};

struct pr1 {
    int p, c, id;

    bool operator < (const pr1& o1) const {
        return p < o1.p;
    }
};

int n, k;
ll m; bool vis[MAXN];
priority_queue <pr, vector <pr>, less <pr> > q;
priority_queue <pr0, vector <pr0>, less <pr0> > q1;
priority_queue <pr1, vector <pr1>, less <pr1> > q2;

bool cmp(const pr& o1, const pr& o2) {
    return o1.p - o1.c > o2.p - o2.c;
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d %d", &cow[i].p, &cow[i].c);
        cow[i].id = i;
    }
    int ans = n;
    ll cost = 0LL;
    sort(cow + 1, cow + n + 1, cmp);
    for(int i = 1; i <= k && i <= n; i++) {
        q1.push((pr0){cow[i].c, cow[i].id});
        cost += (ll)cow[i].c;
    }
    for(int i = k + 1; i <= n; i++) {
        q.push((pr){cow[i].p, cow[i].c, cow[i].id});
        q2.push((pr1){cow[i].p, cow[i].c, cow[i].id});
        cost += (ll)cow[i].p;
    }
    while(cost > m) {
        while(!q.empty() && vis[q.top().id]) q.pop();
        while(!q2.empty() && vis[q2.top().id]) q2.pop();
        if(q.empty() || q2.empty()) {
            pr0 cmax = q1.top();
            q1.pop();
            cost -= (ll)cmax.c;
            --ans;
        }
        else {
            pr1 pmax = q2.top();
            pr0 cmax = q1.top();
            pr decmax = q.top();
            if(pmax.p > cmax.c + decmax.p - decmax.c) {
                cost -= (ll)pmax.p;
                --ans;
                vis[pmax.id] = true;
                q2.pop();
            }
            else {
                cost -= (ll)(cmax.c + decmax.p - decmax.c);
                --ans;
                vis[decmax.id] = true;
                q.pop();
                q1.pop();
                q1.push((pr0){decmax.c, decmax.id});
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：快斗游鹿 (赞：4)

## 思路

首先，肯定要优先选价格小的牛，所以应当先把 $c_i$ 前 $k$ 小的牛加入答案。如果这期间需要的总价格已经超过 $m$，就直接输出，因为肯定不会有更优的策略。

然后再考虑其他的牛。每头牛有两种选择，一种是不用优惠券，直接买，还有一种是，将前面用在其他牛身上的优惠券撤回，用在自己身上。那么第一种选择总价格会加上 $p_i$，第二种则会加上 $c_i+rest$ 其中 $rest$ 是以前使用优惠券的牛的 $p_i-c_i$ 的最小值，因为撤回省的钱数最少的优惠券肯定最优。如果哪种选择都无法满足钱数限制，就直接输出。

如何维护呢？用三个优先队列分别维护 $p_i,c_i,p_i-c_i$ 就好了。需要注意的是要记录每头牛是否已经被买了，否则可能会出现重复购买的情况。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mk make_pair
using namespace std;
const int N=5e4+5;
struct Node{
	int c,p;
}e[N];
int n,k,m,wei,cnt,ans;
bool flag[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >qb,qc;
priority_queue<int,vector<int>,greater<int> >qa;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(Node xxx,Node yyy){
	return xxx.c<yyy.c;
}
signed main(){
	n=read();k=read();m=read();
	for(int i=1;i<=n;i++)e[i].p=read(),e[i].c=read();
	sort(e+1,e+1+n,cmp);
	for(int i=1;i<=k;i++){
		wei+=e[i].c;
		if(wei>m){
			cout<<i-1;return 0;
		}
		qa.push(e[i].p-e[i].c);
	}
	ans=k;
	for(int i=k+1;i<=n;i++){
		qb.push(mk(e[i].p,i));
		qc.push(mk(e[i].c,i));
	}
	for(int i=k+1;i<=n;i++){
		while(flag[qb.top().second])qb.pop();
		while(flag[qc.top().second])qc.pop(); 
		int costb=qb.top().first;
		int costc=qc.top().first;
		if(costb<=costc+qa.top()){//用不着优惠券也能买 
			wei+=costb;ans++;
			flag[qb.top().second]=1;
			qb.pop();
		}
		else{//得用优惠券 
			qa.push(e[qc.top().second].p-e[qc.top().second].c);
			wei=wei+costc+qa.top();
			flag[qc.top().second]=1;
			qa.pop();qc.pop();
		}
		if(wei>m){
			cout<<i-1;return 0;
		}
	}
	cout<<n;
	return 0;
}
```


---

## 作者：Falling_Sakura (赞：3)

> [Blog 传送门](https://white.fallingsakura.love/)

> [题目传送门](https://www.luogu.com.cn/problem/P3045)


# 解法

这很明显，是道贪心。

第一感觉是能打折的按照打折价格从低到高买了，不能打折的就按照原价从低到高买了。

很不幸，虽然过了一个 Substack，但是依旧零分（~~不让骗分呜呜呜~~）。

想想这个到底该怎么贪。

有 $K$ 张优惠券，如果只买 $K$ 头牛的话，那么一定是买优惠价为前 $K$ 的牛最优，这毋庸置疑。

那么如果是 $K+1$ 头呢？

新加了一只牛，它的优惠幅度比我优惠价为前 $K$ 的某只牛更大，也就是打的折更多，这样显然用优惠价购买优惠幅度大的用原价购买优惠幅度低的更优。

那么回到 $N$ 头牛的情况：

首先先把 $K$ 张优惠券都用到 $C$ 大小为前 $K$ 小的牛上，然后考虑转移。

对于下一头奶牛，要么就是原价购买，要么就是转移优惠券购买，取更优的情况购买。

这里维护三个优先队列，一个存储牛的优惠价，一个存储原价，一个存储优惠价与原价的差价（都是小根堆）。

每次选出差价最小的（也就是优惠幅度最低的），然后把它的优惠券转移到还没有用优惠券 $C$ 值最小的牛身上，这样总价值就是原来的加上最小的差价再加上最小的优惠价，

然后拿它和购买最小原价的情况作比较价格，谁小就按谁的方式买。

**代码：**

```cpp
#include<bits/stdc++.h>
#define LL long long//不开 long long 见祖宗
#define pa pair<LL,int>
using namespace std;
priority_queue< pa,vector<pa>,greater<pa> >h1,h2;
priority_queue< LL,vector<LL>,greater<LL> >h3;
LL p[50100],c[50100],m,sum;
bool v[50100];
LL ans;
int main(){
	int n,k;
	scanf("%d%d%lld",&n,&k,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&p[i],&c[i]);
		h1.push(pa(p[i],i));
		h2.push(pa(c[i],i));
	}
	for(int i=1;i<=k;i++) h3.push(0LL);
	while(!h1.empty()){
		pa n1=h1.top();
		pa n2=h2.top();
		if(v[n1.second]){
			h1.pop();
			continue;
		}
		if(v[n2.second]){
			h2.pop();
			continue;
		}
		if(n1.first<n2.first+h3.top()){//说明不用优惠卷，或者优惠卷用完了后的代价太大，不如直接买 
			if(sum+n1.first>m) break;
			ans++;
			sum+=n1.first;
			v[n1.second]=true;
			h1.pop();
		}
		else{//如果h3.top()不为0，说明优惠卷已经用完，这时只能回退优惠卷并承担代价 
			if(sum+n2.first+h3.top()>m) break;
			ans++;
			sum+=n2.first+h3.top();
			v[n2.second]=true;
			h3.push(p[n2.second]-c[n2.second]);//差价，相当于回退优惠卷时要返回的代价 
			h2.pop();
			h3.pop();
		} 
	}
	printf("%lld\n",ans); 
	return 0;
}
```

---

## 作者：XKJie (赞：3)

想到一个结论——$c$ 值前 $k$ 小的奶牛一定会被购买。    
考虑反证法。  
如果 $c$ 值前 $k$ 小的奶牛为被购买，那么就一定可以将其中的奶牛代替现在使用优惠的奶牛，方案更优。  
但是，$c$ 值前 $k$ 小的奶牛并不一定会使用优惠券。  
假设已经购买的奶牛中使用优惠的一头奶牛为 $x$，未使用优惠的奶牛为 $y$，那么当且仅当 $p_x-c_x<p_y-c_y$ 时，将 $x$ 的优惠给 $y$ 使用会使得整体方案更优。于是如果出现了上述情况，$c$ 值前 $k$ 小的奶牛可以考虑不使用优惠使得整体方案更优。  
考虑先将 $c$ 值前 $k$ 小的奶牛加入购买方案，全部使用优惠券，再考虑其它的奶牛。  
对于一头奶牛 $i$ 有两种方案，一种是直接购买，花费 $p_i$，另一种是取代奶牛 $j$ 的优惠券，花费为 $p_j-c_j+c_i$。  
使用三个优先队列分别维护 $p_i,c_i,p_j-c_j$ 的最小值即可。
```cpp
#include <bits/stdc++.h>
#define N 50010
#define ll long long
using namespace std;
int n,k,ans;
bool v[N];
struct node
{
    ll p,c;
    // p is value
    //c is loc
    node () {}
    node (ll _,ll __) {p=_,c=__;}
}a[N];
ll M;
bool cmp(const node &a,const node &b)
{return a.c<b.c;}
bool operator < (const node &a,const node &b)
{return a.p>b.p;}
int main()
{
    scanf("%d %d %lld",&n,&k,&M);
    for (int i=1;i<=n;i++)
        scanf("%lld %lld",&a[i].p,&a[i].c);
    sort(a+1,a+n+1,cmp);
    priority_queue <node> q1,q2,q3;
    for (int i=1;i<=n;i++)
    {
        if (i>k)
        {
            q1.push(node(a[i].p,1ll*i));
            q2.push(node(a[i].c,1ll*i));
        }
        else
        {
            v[i]=1;
            q3.push(node(a[i].p-a[i].c,1ll*i));
            if (M>=a[i].c)
            {
                M-=a[i].c;
                ans++;
            }
        }
    }
    bool fl=1;
    while (fl)
    {
        fl=0;
        node a1,a2;
        a1=a2=node(10000000000000ll,0ll);
        while (q1.size() && v[q1.top().c]) q1.pop();
        if (q1.size()) a1=q1.top();
        while (q2.size() && v[q2.top().c]) 
        {
            q2.pop();
        }
        if (q2.size()) a2=node((q2.top().p+q3.top().p),q2.top().c);
        if (a1.p==10000000000000ll && a2.p==10000000000000ll) break;
        if (a1.p<a2.p)
        {
            q1.pop();
            if (M>=a1.p)
            {
                M-=a1.p;
                v[a1.c]=1;
                fl=1;
                ans++;
            }
        }
        else
        {
            q2.pop();
            q3.pop();
            if (M>=a2.p)
            {
                M-=a2.p;
                v[a2.c]=1;
                q3.push(node(a[a2.c].p-a[a2.c].c,a2.c));
                fl=1;
                ans++;
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：caoshurui (赞：3)

#### 提示 1

直接选不好做，因此可以考虑先把所有的牛选上，然后丢弃最少的牛使得花费的钱符合要求。

#### 提示 2

既然已经全部选上了的，那么每个优惠券的贡献就是对整体的，是不是可以先把贡献大的优惠券用掉。

#### 提示 3

假设已经用掉了所有能用掉的优惠券了，那么只有两种情况了：把一个没有带着优惠券的奶牛删掉，贡献就是 $p_i$；或者把一个带着优惠卷的奶牛删掉，贡献就是 $c_i$，不过此时还有一个优惠券空着，因此还可以选一个剩下的贡献最大的优惠券用掉。

#### 提示 4

以上的操作可以使用三个堆来维护。

如果你此时已经挂了好几发了，那么可能是以下几个原因：

1. 删掉一个带优惠卷的奶牛还需要更新一个带优惠卷的奶牛，把它加进堆中，并且它不能再作为优惠卷的贡献在堆中出现，它也不能再作为没有优惠卷的贡献在堆中出现。

2. 对于一个删掉的奶牛，它在所有堆中都不能出现。

#### 提示 5

直接放代码。


```cpp

#include <algorithm>
#include <iostream>
#include <queue>
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define lop(i, x, y) for (int i = x; i >= y; i--)
#define int long long

using namespace std;

using pii = pair<int, int>;
using ll = long long;

const int MAXN = 2e5 + 5;

int n, k, m;
int ans, sum, cnt;

struct node {
  int p, c;
} a[MAXN];

struct Node {
  int v, id;
  bool operator<(const Node &x) const { return v < x.v; }
};

priority_queue<Node> q1, q2, q3;  // 带优惠券的，没有优惠券的，没有优惠券中优惠额度最大的

bool vis[MAXN];  // 带有优惠卷或者删除的

void put(priority_queue<Node> x) {
  for (; x.size(); x.pop()) {
    cout << x.top().id << ' ' << x.top().v << '\n';
  }
}

signed main() {
  // freopen(".in", "r", stdin);
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> k >> m;
  rep(i, 1, n) {
    cin >> a[i].p >> a[i].c;
    sum += a[i].p, a[i].c = a[i].p - a[i].c;
  }
  sort(a + 1, a + 1 + n, [](node x, node y) { return x.c > y.c; });
  rep(i, 1, k) {
    sum -= a[i].c, q1.push({a[i].p - a[i].c, i}), vis[i] = 1;
  }
  rep(i, k + 1, n) {
    q2.push({a[i].p, i}), q3.push({a[i].c, i});
  }
  ans = n;
  for (; sum > m;) {
    int x = 0, y = 0;

    for (; q2.size() && vis[q2.top().id]; q2.pop());
    for (; q3.size() && vis[q3.top().id]; q3.pop());

    if (q1.size()) {
      x = q1.top().v;
      if (q3.size()) x += q3.top().v;
    }
    if (q2.size()) y = q2.top().v;

    sum -= max(x, y), ans--;
    if (x > y) {  // 删除带优惠卷的，增加一个带优惠卷的
      q1.pop();
      if (q3.size()) {
        int id = q3.top().id;
        vis[id] = 1, q3.pop();
        q1.push({a[id].p - a[id].c, id});
      }
    } else {
      vis[q2.top().id] = 1, q2.pop();
    }
  }
  cout << ans;
  return 0;
}
```

#### 总结

一道很板的贪心，有一道思路跟它很相似的题目 [CF730I](https://www.luogu.com.cn/problem/CF730I)。

明天就是 CSP 了，哎，估计这是我竞赛生涯中最后一篇题解了吧。

---

## 作者：lzy_AC7 (赞：3)

[更好的阅读体验 ^-^](https://www.cnblogs.com/AC7-/p/17607474.html)
------------
## 题目分析：
这题一眼 $ 01 $ 背包，但是 $ N $ 和 $ M $ 太大，所以不行考虑贪心。

**贪心本身是没有反悔操作的，贪心求的就是当前的最优解。但当前的最优解有可能是局部最优解，而不是全局最优解，这时候就要进行反悔操作。**

------------

众所周知，正常的贪心算法是指在对问题求解时，总是做出在当前看来是最好的选择。也就是说，不从整体最优上加以考虑，算法得到的是在某种意义上的局部最优解。也就是说我们的每一步都是站在当前产生的局面上所作出的最好的选择，是没有反悔操作的。

不加反悔的一直朝着当前局面的最优解走很可能导致我们被困在局部的最优解而无法到达全局的最优解，就好像我们爬山就只爬到了一座山的山顶却没有到整片山的最高处。

但是反悔贪心允许我们在发现现在不是全局最优解的情况下回退一步或若干步采取另外的策略去取得全局最优解。就好像我们站在的一座山的山峰上，看到了还有比我们现在所在位置还高的山峰，那我们现在就肯定不是在最高的地方了，这时我们就反悔——也就是下山再爬上那座更高的山。

这就是反悔贪心的大致思路。根据反悔记录操作的不同，反悔贪心又分为反悔堆和反悔自动机。

------------

很直接的想法是将所有牛按 $ c $ 值排序买 $ k $ 个 $ c $ 值最小的，然后剩下的钱原价买。

所有钱只够买这前 $ k $ 只的情况很显然都用优惠券买。

#### 以下考虑有剩余的钱买 $ k + 1 $ 到 $ n $ 的牛：
- **这 $ k $ 个 $ c $ 值最小的一定会被买。**

反证法：如果有一种方案是这$ k $只牛中有一只 $ A $ 不买而是买其他的 $ B $，若 $ A $ 替换 $ B $ 来用优惠券，花的钱一定会更少，方案会更优，所以先将这 $ k $ 只牛用优惠券买了。
- **这 $ k $ 个 $ c $ 值最小的又不一定会用优惠券。**

这 $ k $ 个牛中所用的优惠券如果用在后面原价买的牛身上会使当前决策更优。即 $ c_x + p_y > p_x + c_y ( 1 \le x \le k , k+1 \le y \le n ) $ 这时可以将这个优惠券转移，则这只牛买来的费用为 $ p_x - c_x + c_y $ 当然如果存在用原价买比用上面这种方式买更优那就直接用原价买。
## 代码实现：
开三个小根堆：
1. 前 $ k $ 只奶牛的 $ P $ 值与 $ C $ 值之差。

1. 第 $ k + 1 $ 到第 $ n $ 只奶牛的 $ C $ 值。

1. 第 $ k + 1 $ 到第 $ n $ 只奶牛的 $ P $ 值。

先按 $ c $ 值排序。

将前 $ k $ 只奶牛的 $ P $ 值与 $ C $ 值之差存入一堆。

将第 $ k + 1 $ 到第 $ n $ 只奶牛的 $ C,P $ 值分别存入二三堆。

每次按上面两种策略的最优策略买牛直到钱不够。

**非常感谢管理员的指导！**
## std：
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;
const int N = 5e4+9;
int n,k;
ll m;
PII a[N];

bool vis[N];
ll sum;
int cnt;
priority_queue<int,vector<int>,greater<int> > d;//原价与优惠价的差值 
priority_queue<PII,vector<PII>,greater<PII> > p,c; 

int main()
{
	scanf("%d%d%lld",&n,&k,&m);
	for(int i = 1;i <= n;i++)scanf("%d%d",&a[i].second,&a[i].first);//sort排序pair<int,int>默认按first排 
	sort(a+1,a+1+n);
	for(int i = 1;i <= k;i++)
	{
		int t = a[i].second-a[i].first;
		d.push(t);
		sum += a[i].first;
		if(sum > m)printf("%d",i-1),exit(0);
	}
	if(sum > m)printf("%d",k-1),exit(0);
	
	cnt = k;
	for(int i = k+1;i <= n;i++)p.push({a[i].second,i}),c.push({a[i].first,i});
	
	while(sum < m)
	{
		//访问堆之前最好先判空
		while(!p.empty() && vis[p.top().second])p.pop();//已经买过的牛就不用再参与了 
		while(!c.empty() && vis[c.top().second])c.pop();
		
		if(c.empty() || p.empty())break;//买完了所有牛 
		
		PII tp = p.top(),tc = c.top();
		int td = d.top();//减少访问堆的次数节省时间 
		
		if(tp.first < tc.first + td)
		{
			if(sum + tp.first <= m)
			{
				cnt++;
				sum += tp.first;
				vis[tp.second] = 1;
				p.pop();
			}
			else break;//没钱了最便宜的都没不了 
		}
		else if(!d.empty())//判断还有没有优惠券 
		{
			if(sum + tc.first + td <= m)
			{
				cnt++;
				sum += tc.first + td;
				vis[tc.second] = 1;
				c.pop(),d.pop();
				d.push(a[tc.second].second-a[tc.second].first);
				//当前的决策只是局部最优之后优惠券还可能转移 
				//所以要将新的差值加入堆 
			}
			else break;//没钱了 
		}
		else //没优惠券了但还有钱，一直按原价买
		{
			while(!p.empty() && sum + p.top().first <= m)cnt++,sum += p.top().first,p.pop();
			break;
		}
	}
	
	printf("%d",cnt);
	
	return 0;
}
```

---

## 作者：云浅知处 (赞：2)

首先我们判掉 $K$ 张优惠券用不完的情况，即最小的 $K$ 个 $C_i$ 之和大于 $M$ 的情况，这种情况一定是选 $C_i$ 最小的若干头奶牛。下面我们的讨论都假设优惠券会用完。

我们考虑，如果确定了要买哪些奶牛，最小代价是多少：就是它们的 $P_i$ 之和，减去前 $K$ 大的 $P_i-C_i$。

于是我们考虑按照 $P_i-C_i$ 排序，则最优方案一定形如一个前缀里面选 $K$ 个用 $C_i$ 的价钱买下（一定是 $C$ 最小的 $K$ 个），后缀里面在价钱不超过 $M$ 的情况下，尽可能用 $P_i$ 的价钱买下更多的奶牛。

使用数据结构维护一下即可，时间复杂度 $O(N\log N)$。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

#define gc getchar
inline ll read(){
    ll x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=1e5+5;
int n,k;ll M;
struct Node{int P,C;}val[N];
bool used[N];

signed main(void){

#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    n=read(),k=read(),M=read();
    for(int i=1;i<=n;i++)val[i].P=read(),val[i].C=read();

    sort(val+1,val+n+1,[&](const Node &A,const Node &B){return A.P-A.C>B.P-B.C;});
    multiset<int>S,T1,T2;

    ll sum=0,sumR=0;
    for(int i=1;i<=k;i++)sum+=val[i].C,S.insert(val[i].C);
    for(int i=k+1;i<=n;i++)T2.insert(val[i].P);
    while(T2.size()&&M-sum>=sumR+*T2.begin()){
        T1.insert(*T2.begin()),sumR+=*T2.begin(),T2.erase(T2.begin());
    }

    int ans=0;if(sum<=M)cmax(ans,k+(int)(T1.size()));
    for(int i=k+1;i<=n;i++){
        if(val[i].C<*--S.end()){
            sum-=*--S.end(),S.erase(--S.end());
            S.insert(val[i].C),sum+=val[i].C;
        }
        if(T2.find(val[i].P)!=T2.end())T2.erase(T2.find(val[i].P));
        else sumR-=val[i].P,T1.erase(T1.find(val[i].P));
        while(T2.size()&&M-sum>=sumR+*T2.begin()){
            T1.insert(*T2.begin()),sumR+=*T2.begin(),T2.erase(T2.begin());
        }
        if(sum<=M)cmax(ans,k+(int)(T1.size()));
    }

    if(sum>M){
        assert(ans==0);
        while(*S.begin()<=M)M-=*S.begin(),ans++,S.erase(S.begin());
    }
    cout<<ans<<endl;

    return 0;
}
```

---

## 作者：Sky_Maths (赞：2)

# [0] 约定
> 费用流中建边的 $(flow,cost)$ 分别代表流量和费用。

# [1] 正文
## [1.1] 分析
若奶牛的数量增加，最小花费必然增加，想到对所有数量求最小花费。

## [1.2] 建模
反悔贪心属于模拟费用流的一种，主要可用来处理增广路种类较少的情况。

考虑本题的费用流模型。

具体的，从 $S$ 向 $S_1, S_2$  分别建边 $(K,0),(+\infty,0)$，代表优惠券的限制。

将每头奶牛拆为两个点 $X_i,Y_i$，建边 $X_i\to Y_i,(1,0)$ 代表每头奶牛至多选一次。

从 $S_1$，即有优惠的点向 $X_i$ 连 $(1,C_i)$。

从 $S_2$ 向 $X_i$ 连 $(1,P_i)$。

选这两条边代表买这头奶牛。

从 $Y_i$ 向 $T$ 连 $(1,0)$。

## [1.3] 增广路分析
增广路只有三种。

1. 显然前 $K$ 条必为 $C$ 前 $K$ 小的。
2. $S\to S_2\to X_i\to Y_i\to T$ 表示选一头新的，不用券。
3. $S\to S_2\to X_j\to S_1\to X_i\to Y_i\to T$ 表示一头已买奶牛的券给另一个未买的奶牛使用。

## [1.4] 实现
[反悔贪心直接套。](https://www.luogu.com.cn/blog/Burningstars/fan-hui-tan-xin-xiao-jie)

令 $0$ 为未买，$1$ 为直接买，$2$ 为用券。

1. $0\to 1$
2. $0\to 2, 2\to 1$

# [2] 代码
```cpp
#define fi first
#define se second
#define mp make_pair
typedef pair<ll, int> pli;

priority_queue< pli, vector<pli>, greater<pli> > q01, q02, q21;

const ll INF = 1e18;
ci N = 1e5 + 9;

int n, k, cnt;
int inq[N], p[N], c[N], o[N];
ll m, now;
ll ans[N];

void In(int i) {
	if(inq[i] == 0) q01.push(mp(p[i], i)), q02.push(mp(c[i], i));
	if(inq[i] == 2) q21.push(mp(p[i] - c[i], i));
}

void init() {
	int mx = N - 1;
	inq[mx - 0] = 0;
	inq[mx - 1] = 1;
	inq[mx - 2] = 2;
	q01.push(mp(INF, mx - 0));
	q02.push(mp(INF, mx - 0));
	q21.push(mp(INF, mx - 2));
}

int main() {
	// freopen("a.in", "r", stdin);
	init();
	rd(n); rd(k); rd(m);
	rep(i, 1, n) {
		rd(p[i]);
		rd(c[i]);
		o[i] = i;
	}
	sort(o + 1, o + n + 1, [](int t1, int t2) {return c[t1] < c[t2];});
	rep(i, 1, k) {
		now += c[o[i]];
		inq[o[i]] = 2;
		ans[i] = now;
	}
	rep(i, 1, n) In(i);
	rep(i, k + 1, n) {
		while(inq[q01.top().se] != 0) q01.pop();
		while(inq[q02.top().se] != 0) q02.pop();
		while(inq[q21.top().se] != 2) q21.pop();
		ll val1 = q01.top().fi;
		ll val2 = q02.top().fi + q21.top().fi;
		ll minn = min(val1, val2);
		now += minn;
		ans[i] = now;
		if(val1 == minn) {
			inq[q01.top().se] = 1; In(q01.top().se);
			continue;
		}
		if(val2 == minn) {
			inq[q02.top().se] = 2; In(q02.top().se);
			inq[q21.top().se] = 1; In(q21.top().se);
			continue;
		}
	}
	int mx = 0;
	rep(i, 1, n) {
		if(ans[i] <= m) {
			mx = i;
		}
	}
	pt("%d\n", mx);
	return 0;
}
```

---

## 作者：junee (赞：2)

# P3045

## 前置知识

反悔贪心。

## 题目分析

模拟赛做到了，赛时过了来写一篇题解。

如果你做过反贪的题目的话，你应该能很容易看出来这是一个反贪的题目。

首先对于同一个东西你用卷肯定不会比不用卷劣，这是题目保证的，所以我们先把所有卷都给用掉，选出所有用卷最小的。

注意！如果你卷用不完，那么你直接可以结束了。

那么现在我们所有卷都用完了，我们再来考虑不用卷，那么此时你会有两种操作：

- 我直接买一头不用卷的牛。

- 我把一头用卷买的牛换成正常价格买的牛，并且用卷买一头新的牛。

那么我们现在需要维护没有被买的牛，和被卷买的牛，维护换牛的操作。

由于我们对于同样数量的牛，我们肯定希望花的钱最少，这是显然的。

所以还需要维护的数据结构能够从小到大，这里很容易想到用到小根堆，我们用三个小根堆维护，一个维护没被买的牛不用卷卖的价格，一个维护没被买的牛用卷卖的价格
，一个维护用卷买的用卷和不用卷的差值。

然后每次比较上面的两个操作那个更有就选哪个。

时间复杂度就是一个小根堆的 $O(n\log n)$。

## Code

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
#include<queue> 
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
typedef pair<LL,LL>PLL;
const int N=2e5+10;
priority_queue<LL,vector<PLL>,greater<PLL> >q1,q2,q3;
//q1 没选的 a,q2 选 b 的 a-b，q3 没选过的 b 
LL n,k,st[N];
LL a[N],b[N],t,at=0,ans=0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k>>t;
	for(LL i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		q3.push({b[i],i});
	}
	while(at+q3.top().first<=t&&k){
		at+=q3.top().first;
		st[q3.top().second]=1;
		ans++;
		k--;
		q3.pop();
	}
	if(ans==n||k){
		cout<<ans;
		return 0;
	}
	for(LL i=1;i<=n;i++){
		if(st[i])q2.push({a[i]-b[i],i});
		else q1.push({a[i],i});
	}
	while(1){
		LL id1,t1,id3,t3,f=0;
		LL id2=q2.top().second,t2=q2.top().first;
		while(st[q1.top().second]&&q1.size())q1.pop();
		while(st[q3.top().second]&&q3.size())q3.pop();
		id1=q1.top().second,t1=q1.top().first;
		id3=q3.top().second,t3=q3.top().first;	
		if(t2+t3+at<=t&&at+t1<=t){
			if(t2+t3<t1){
				q2.pop();
				q3.pop();
				q2.push({a[id3]-b[id3],id3});
				st[id3]=1;
				ans++;
				at+=t2+t3;
				f=1;
			}
			else{
				q1.pop();
				st[id1]=1;
				ans++;
				at+=t1;
				f=1;
			}
		}
		else if(t2+t3+at<=t){
			q2.pop();
			q3.pop();
			q2.push({a[id3]-b[id3],id3});
			st[id3]=1;
			ans++;
			at+=t2+t3;
			f=1;
		}
		else if(at+t1<=t){
			q1.pop();
			st[id1]=1;
			ans++;
			at+=t1;
			f=1;
		}
		if(!f||ans==n)break;
		//cout<<ans<<'\n';
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lzt415 (赞：2)

## 思路分析
这是一道反悔贪心的题。

我们先把 $k$ 张优惠券用在 $c_{i}$ 前 $k$ 小的奶牛上，然后再根据反悔贪心的思想进行改变。

那么怎样进行调整优惠券的使用呢？

在这里我们可以开三个优先队列，第一个优先队列存每一头牛的原价，第二个优先队列存 $c_{i}$，第三个优先队列存能优惠的价格，也就是原价和优惠价的差。

注意：在第三个优先队列中存放 $k$ 个 $0$，因为使用了 $k$ 张优惠券，所以就没有补差价这一说了。

然后开始进行反悔，也就是调整使用优惠券的方法。具体操作是：我们可以每一次取出第一个优先队列和第二个优先队列的对头元素出来，按照贪心策略，如果按原价买比按优惠价买并且补上差价便宜的话，我们就就用原价买，否则就按照使用优惠卷来买。最后封印这头牛，让它永题不得再被取出。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=50010;
int n,k,m,s[N],c[N],sign[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q,p;
priority_queue<int,vector<int>,greater<int> > a;
signed main(){
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i]>>c[i];
		q.push({s[i],i}),p.push({c[i],i});
	}
	for(int i=1;i<=k;++i) a.push(0);
	int sum=0,ans=0;
	while (!q.empty()){
		pair<int,int> tp=q.top(),tc=p.top();
		if (sign[tp.second]){q.pop();continue;}
		if (sign[tc.second]){p.pop();continue;}
		if (tp.first<tc.first+a.top()){
			if(sum+tp.first>m) break;
			sum+=tp.first;
			ans++;
			q.pop();
			sign[tp.second]=true;
		}else {
			if (sum+tc.first+a.top()>m) break;
			sum+=tc.first+a.top();
			ans++;
			p.pop();
			sign[tc.second]=true;
			a.pop();
			a.push({s[tc.second]-c[tc.second]});
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_xdd_ (赞：1)

考虑反悔贪心。

首先，优惠价最小的 $k$ 个数用优惠卷，设当前已经花了 $x$ 元。

如果买 $i$ 用优惠卷的价格 $<$ 原价则反悔，反悔后第 $j$ 件物品退回原价，即：

$$x-c_j+p_j+c_i>x+p_i$$

整理得：

$$p_j-c_j>p_i-c_i$$

我们设 $p_i-c_i=pc_i$，如果存在一个 $pc_j<pc_i$ 则反悔，可以使用小根堆优化。


```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
#define maxn 50000+5
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int n,k,m,c[maxn],p[maxn],ans;
bool vis[maxn];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>qp,qc;
priority_queue<int,vector<int>,greater<int>>pc;
signed main(){
    cin >> n >> k >> m;
    for(int i=1;i<=n;i++){
        cin >> p[i] >> c[i];
        qp.push(make_pair(p[i],i));
        qc.push(make_pair(c[i],i));
    }
    for(int i=1;i<=k;i++){
        pc.push(0);
    }
    while(qp.size()){
        pair<int,int>x=qp.top(),y=qc.top();
        if(vis[x.second]){
            qp.pop();
            continue;
        }if(vis[y.second]){
            qc.pop();
            continue;
        }
        if(pc.top()>x.first-y.first){
            m-=x.first;
            qp.pop();
            vis[x.second]=1;
        }else{
            m-=y.first+pc.top();
            qc.pop();
            pc.pop();
            vis[y.second]=1;
            pc.push(p[y.second]-c[y.second]);
        }
        if(m>=0){ans++;}
        else{break;}
    }
    cout << ans;
    return 0;
}
```

---

