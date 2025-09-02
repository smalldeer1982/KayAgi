# [NOI Online #1 提高组] 冒泡排序

## 题目描述

给定一个 $1 ∼ n$ 的排列 $p_i$，接下来有 $m$ 次操作，操作共两种：
1. 交换操作：给定 $x$，将当前排列中的第 $x$ 个数与第 $x+1$ 个数交换位置。
2. 询问操作：给定 $k$，请你求出当前排列经过 $k$ 轮冒泡排序后的逆序对个数。
对一个长度为 $n$ 的排列 $p_i$ 进行一轮冒泡排序的伪代码如下：
```
for i = 1 to n-1:
  if p[i] > p[i + 1]:
    swap(p[i], p[i + 1])
```

## 说明/提示

#### 样例一解释
第一次操作：排列为 $\{1,2,3\}$，经过 0 轮冒泡排序后为 $\{1,2,3\}$，$0$ 个逆序对。

第二次操作：排列变为 $\{2,1,3\}$。

第三次操作：排列变为 $\{2,3,1\}$。

第四次操作：经过 $0$ 轮冒泡排序后排列变为 $\{2,3,1\}$，$2$ 个逆序对。

第五次操作：经过 $1$ 轮冒泡排序后排列变为 $\{2,1,3\}$，$1$ 个逆序对。

第六次操作：经过 $2$ 轮冒泡排序后排列变为 $\{1,2,3\}$，$0$ 个逆序对。

---

#### 数据范围与提示
对于测试点 1 ∼ 2：$n,m \leq 100$。

对于测试点 3 ∼ 4：$n,m \leq 2000$。

对于测试点 5 ∼ 6：交换操作个数不超过 $100$。

对于所有测试点：$2 \leq n,m \leq 2 \times 10^5$，$t_i \in \{1,2\}$，$1 \leq x < n$，$0 \leq k < 2^{31}$。

## 样例 #1

### 输入

```
3 6
1 2 3
2 0
1 1
1 2
2 0
2 1
2 2```

### 输出

```
0
2
1
0```

# 题解

## 作者：万万没想到 (赞：118)

~~前言：这里有一只考场上以为打了20分部分分民间数据只有10分赛后100分的蒟蒻。~~

题目传送门：[P6186 [NOI Online 提高组]冒泡排序](https://www.luogu.com.cn/problem/P6186)

解题思路：

我们要做出这道题目，首先要发现冒泡排序的本质，我们知道冒泡排序外层循环最多跑 $n-1$ 次（实际上是 $n$ 次，只不过最后一次序列已经是有序的了，可以省去）。

例子：4 3 5 2 1

那么这个序列进行一次冒泡之后是这个样子的。

第一轮后：3 4 2 1 5

我们发现，4与3交换，5与2与1交换，但2却没有和1交换，所以一个数可以同自己右边的数进行交换当且仅当左边没有比它大的数，形象化为当你的左手边没有比你更强的人碾压你，你就可以一路向右碾压，直到碰到一个比你强的人，我们将此类数的状态称为可以碾压别人，非此类数称为不可碾压别人，这个就是冒泡排序的本质。

本质弄清了，我们还要处理的是，每次冒泡会减少多少逆序对，如果当前有 $x$ 个可以碾压别人的数，则这 $x$ 个数在此轮都不会被碾压，则有 $n-x$ 个数会被碾压，逆序对就减少了 $n-x$ 个。

所以当一个数前面有 $y$ 个比它大的数的话，这个数会在第 $y+1$ 轮冒泡中碾压别人。

用树状数组算出从未开始（第 $1$ 轮）一直到第 $n$ 次冒泡（第 $n+1$ 轮）每一轮的逆序对个数，这个是初始化，即不进行交换的每轮冒泡的逆序对数。

进行交换的话如何修改？我们设数组 $a$ 是每一个元素， 数组 $b$ 是此元素前有几个比它大的元素。

如果 $a_x < a_{x+1}$ ，那么交换 $a$ 和 $b$ 数组之后初始的逆序对个数就会 $+1$ ， $b_{x+1}$ 也会 $+1$ 也会但这个逆序对个数的 $+1$ 会在什么时候失效呢？我们发现交换后 $b_{x+1}+1$ ，当交换前的 $a_{x}$ 可以碾压别人的时候，也就是可以冒泡的时候，多出的逆序对就没有影响了，即在 $b_{x+1}+1$ 前在树状数组中减去 $1$ ，为什么没有其他修改了呢？因为交换两个相邻的数只会影响一个逆序对，对前后的逆序对个数没有多余影响。

考虑这个序列：2 1 3

交换后面两个元素：2 3 1

当序列为：1 2 3的时候逆序对个数恢复原状。

如果 $a_x > a_{x+1}$ ，那么交换 $a$ 和 $b$ 数组之后初始的逆序对个数就会 $-1$ ， $b_{x}$ 也会 $-1$ 也会但这个逆序对个数的 $-1$ 会在什么时候失效呢？我们发现交换后 $b_{x}-1$ ，当交换后的 $a_x$ 可以碾压别人的时候，也就是可以冒泡的时候，减去的逆序对个数就没有影响了，即在 $b_{x}-1$ 后在树状数组中加上 $1$ ，为什么没有其他修改了呢？因为交换两个相邻的数只会影响一个逆序对，对前后的逆序对个数没有多余影响。

考虑这个序列：2 3 1

交换后面两个元素：2 1 3

当序列为：1 2 3的时候逆序对个数恢复原状。

也就是说比较交换前后的 $a$ ，较小的在前面的 $a$ 的 $b$ 数组就是逆序对最早不产生影响的地方。

最后利用差分思想查询即可。

如果看一遍看不懂，请细品。

如果还是看不懂，建议思考交换后 $a_x$ 前面的数对于后面的逆序对产生的影响。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m,a[maxn],b[maxn],d[maxn];
long long c[maxn],ans;
inline int lowbit(int x){
	return x&(-x);
}
inline void update(int x,long long val){
	while(x<=n){
		c[x]+=val;
		x+=lowbit(x);
	}
}
inline long long getsum(int x){
	long long res=0;
	while(x>0){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	int opt,x,tmp=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		b[i]=i-1-getsum(a[i]);
		ans+=b[i],++d[b[i]];
		update(a[i],1);
	}
	memset(c,0,sizeof(c));
	update(1,ans);
	for(int i=0;i<n;++i){
		tmp+=d[i];
		update(i+2,-(n-tmp));
	}
	for(int i=1;i<=m;++i){
		scanf("%d%d",&opt,&x);
		x=min(x,n-1);
		if(opt==1){
			if(a[x]<a[x+1]){
				swap(a[x],a[x+1]);
				swap(b[x],b[x+1]);
				update(1,1);
				update(b[x+1]+2,-1);
				b[x+1]++;
			}
			else{
				swap(a[x],a[x+1]);
				swap(b[x],b[x+1]);
				update(1,-1);
				b[x]--;
				update(b[x]+2,1);
			}
		}
		else printf("%lld\n",getsum(x+1));
	}
	return 0;
}
```


---

## 作者：little_prince (赞：97)

（这个题我觉得非常锻炼思维能力~~当然我当时考试冥思苦想1个多小时想不出来~~）

（本篇题解可能说有抄袭之嫌，但我想说，这些话都是我自己很通俗的理解（因为自己的OI能力还太弱），希望给予大家更多的帮助，仅此而已）

[冒泡序列](https://www.luogu.com.cn/problem/P6186)

题目的难点：在O（logn）（~~不然绝对T飞~~）的时间内求出第k次冒泡排序后数组的逆序对，并且还有相邻交换数值的操作要处理。

乍一看要在O（logn）内处理操作，瞬间脑子里蹦出了线段树树状数组的这些数据结构，然后由于之前写过了树状数组求逆序对（可参考这篇博客[树状数组的小整理](https://www.luogu.com.cn/blog/wqqakioi/shu-zhuang-shuo-zu-bit-di-xiao-zheng-li)），于是就想到了用树状数组来写这道题。

但是，我们要注意，写题不应该是**拿数据结构去套题目所给的操作，先去想了优化再踌躇满志地去想题目该怎么写**。我们应该做的（仅作者一家之言），是先去想**如何处理题目给出的问题，想一个解决办法，再联想到对这个解决办法有帮助的工具，即数据结构**。我想这种想法，应该适用于我们所有的题目中，不仅仅只是数据结构的题目。

所以，自己以后得改正这种想法，并多多练习啦！

好我们来看这道题。为了方便，我们先不做任何交换的修改操作，光是这个O（logn）时间复杂度内求k次冒泡排序后的逆序对就够我们喝一壶了。

### 一.思路初探

一个一个去换肯定是不行的，不过我们可以想到，**我们可能要存一下k次冒泡排序对每个数的影响**，这样才能不受k数值的限制，才不会一直苦想怎么在这k次变换的方式里做文章。

那么，既然是要存起来每个数的影响，我们就可以先去求出原数组的逆序对数量，然后再处理影响，输出答案。**这就是一个大致的思路，也就是说，我们相当于要先算出原数组的逆序对（假设有tot个），再去标记，每一轮冒泡排序给每个数造成的影响，算上影响后再输出答案**。

### 二.处理每个数的影响

怎么去处理k次冒泡排序对每个数的影响呢？
先来举个例子玩玩，，，

1 4 5 2 3 （这是原数组）

向下经过1轮排序——

1 4 2 3 5 （分析一下，2,3 动了，总逆序对失去了2个（5,2和5,3），并且2和3都是**前面有2个数比它大**的数。

向下，第2轮——

1 2 3 4 5 （还是2,3在动，他们是**前面有2个数比它大**的数）

诶，好像有点规律，似乎跟**该数字前面（也就是左边）有多少个数比它大有关**？

再来看：

5 1 2 4 3

第1轮后——

1 2 4 3 5 （**前面有1个数比它大的1,2，4 和前面有2个数的3动了，，，**）

第2轮——

1 2 3 4 5 （**在原数组里看，前面有2个数比它大的3动了**）

诶好像真的与这个有关系耶！
我们尝试着想到一般上去。

对于一个数，如果说**它前面有多少个数比它大，那么它将会在这个数值的那一轮里最后记一次影响，然后停下来**。为什么会这样呢？不妨讨论一下，，，

case 1，假设这个数左边相邻的数比它大，那么这个相邻的数必然会记到原数的影响里；

case 2 左边相邻的数比它小，仔细一想发现不影响啊！比原数大的数必然可以换到这里来，除非出现一个数挡住它（那个比原数大的数），那这个数不也比原数大，记到影响里了嘛！

所以，到这里似乎有了点感觉，似乎明白该怎么去处理这个影响了。我们的做法是：

1.用before[i]表示**位置i的数a[i]的前面，有多少个数比它大**。显然，总逆序对数的每一个i的before[i]的和。那么对于每一次冒泡排序，before[i]的变化是，

### before[i] = max(before[i]-1,0)

这里一定要想明白这个方程式为啥哦！

2.用record[i]表示，**有i个数在前面比它大的数 的数量**。这里想清楚哦！

3.记record[i]是干啥的？就是为了计算**当前这一轮会有多少个数处于影响范围内，丢失一个逆序对**。我们利用前缀和的形式（即注意点1的操作，好好体会一下）能够记下，**前面有小于等于i个数比它大的数的数量**，记做tot，那么**前面有大于i个数比它大的数的数量，即在本轮会丢失1个逆序对的数的数量**，就是（n-tot）啦！

此时再联想到，我们可以利用树状数组进行一个O（logn）的差分操作，把第一位的值赋上初始的总逆序对数，从第二位开始（第二位表示进行第一轮冒泡排序）O（logn）的时间复杂度内，存下每轮的总影响。
嗯，就这些！没事的，这里可能要多想想咯。

### 三.执行交换操作，我该怎么搞

因为只是交换相邻两项，所以我们想，**除这两项以外的其他项的逆序对数和其他信息不会有变化**。
那么我们来看，

1.a[x] < a[x+1]。

首先交换x和x+1的a值和before值。

然后注意，x+1的位置上多了一个比它大的数。所以before[x+1]++;

总逆序对数+1，即add（1，1）；

**我们还得考虑第k轮冒泡排序的影响。before[x]不会受到影响，所以到第before[x+1]轮时冒泡排序，我们得把这个1再减回来，即add(before[x+1] + 1,-1)，注意一下树状数组内的坐标哦**！

2.a[x] > a[x+1]。同上反过来咯，注意细节！

这里可能要详细解释一下注意点2。

在a[x] < a[x+1]的时候，我们要明白，before[x] 必然 >= before[x+1],那么在交换位置时，因为多了一个比它大的数，beforex[x+1]（原来的a[x]的信息）++,那么原来的a[x]的before[x] > before[x+1]（原来a[x+1]的信息），即现在的before[x] < before[x+1]，但这个操作并没有影响到**原来a[x+1]的信息，所以要处理的是原来的a[x]的信息的影响,即处理现在的before[x+1]。**  比如1,2,3，若交换2,3，换过来以后变成1,3,2，那么2的影响值便在**当前的**before[2]轮上，所以有先before[x+1]++,再add(before[x+1]+1,-1）；

同样，在a[x] > a[x+1]的时候，我们和上面同理意会一下，是不是**原来a[x]的信息（现在交换后的a[x+1],before[x+1]）是不是没有动**呀。那么这个交换，同样，就对**冒泡排序对这个数的影响**没有任何作用在上面。**有影响的就变成原来的a[x+1]（现在的a[x],before[x]）了**。至于具体影响在哪一轮，这个说老实话确实非常非常不好想，我们可以结合下面的例子去理解就行，

比如6,5,4,3,2,1，交换3,2，变成6,5,4,2,3,1，那么在原来的第before[2] （原来before[2] = 4）轮上，原来因（3,2）在树状数组里给到的一个逆序对的影响**在新的数组里没有了，不在算总逆序对时再算上一遍，这个，在现在的数组里不存在的一个逆序对**。 所以，在这里，先add(before[x]+1,1),再before[x]--；

如果小结一下上面这段话是想提醒什么，那就是：

### 交换操作，是需要去在最初始时的数组里的影响里修改。

好啦，本题大功告成，还得多加训练！

附上代码：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 2e5 + 7;
inline LL read(){
	LL f=1,r=0;char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){r=r*10+c-'0';c=getchar();}
	return f*r;
}
LL a[MAXN];
LL t[MAXN];
LL n,m;
inline LL lowbit(LL x){return x & (-x);}
void add(LL x,LL v){
	for(;x <= n;x += lowbit(x)) t[x] += v;
}
LL ask(LL x){
	LL res = 0;
	for(;x > 0;x -= lowbit(x)) res += t[x];
	return res;
}
LL x,op;
LL tot,record[MAXN],before[MAXN];
int main(){
	n = read();m = read();
	for(LL i = 1;i <= n; i++) a[i] = read();
	for(LL i = 1;i <= n; i++)
	{
		before[i] = i-1-ask(a[i]);
		tot += before[i];
		record[before[i]]++;
		add(a[i],1);
	}
	memset(t,0,sizeof(t));
	add(1,tot);
	tot = 0;
	for(LL i = 1;i <= n; i++)
	{
		tot += record[i-1];//注意点1
		add(i+1,-(n-tot));
	}
	for(LL i = 1;i <= m; i++)
	{
		op = read();x = read();
		x = min(x,n-1);
		if(op == 2){cout<<ask(x+1)<<endl;}
		else if(op == 1)
		{
			if(a[x] < a[x+1])
			{
				swap(a[x],a[x+1]);
				swap(before[x],before[x+1]);
				
				before[x+1]++;
				add(before[x+1]+1,-1);
				add(1,1);
			}
			else{
				swap(a[x],a[x+1]);
				swap(before[x],before[x+1]);
				//注意点2
				add(before[x]+1,1);//注意一下这里和上面的顺序，多想想！
				before[x]--;
				add(1,-1);
			}
		}
	}
	return 0;
}

```



 _这次没什么名言了，_
 
 _不过在这个特殊的时期里，还是想，_
 
  _向此时此刻仍然奋战在抗疫一线的医护人员致敬。_ 

---

## 作者：Macesuted (赞：68)

[题面](https://www.luogu.com.cn/problem/P6186)

大意就是给定一个序列，对其进行两个操作，交换相邻的两个数，或者对全序列进行**一遍**冒泡排序。

观察题面可以发现

- 当ti=1时我们需要交换相邻的两个数
- 当ti=2时我们需要对全序列进行冒泡排序

由于数据量极大，显然暴力的模拟一定不行

我们记录第i位数前面比它大的数的数量为$before[i]$，显然，当前序列的总逆序对数量就是所有的$before$之和

通过对冒泡排序的观察，我们可以发现，每一遍冒泡排序都会使得所有$before[i]=max(before[i]-1,0)$

我们采用树状数组差分维护这一操作，令$sum(t)$为当$ti=2$，$k=t$时的答案

在数组最前面加入当前序列总逆序对数量，然后在第$i$位放$before$大于$i$的数字的数量的相反数，因为这些数字在第$i$轮逆序对数均会减$1$

最后利用差分直接求解即可

```cpp
#include <bits/stdc++.h>
using namespace std;

int input[200005], before[200005], record[200005];
int n;

long long tree[200005];
inline int lowbit(int x)
{
	return x & (-x);
}
void add(int x, long long val)
{
	for (; x <= n; x += lowbit(x))
		tree[x] += val;
	return;
}
long long sum(int x)
{
	long long res = 0;
	for (; x > 0; x -= lowbit(x))
		res += tree[x];
	return res;
}

int main()
{
	int m;
	scanf("%d%d", &n, &m);
	long long tot = 0; //先记录初始状态下的逆序对数量
	for (int i = 0; i < n; i++)
	{
		scanf("%d", input + i);
		before[i] = i - sum(input[i]); //记录比它小的数字数量
		tot += before[i];			   //最开始tot记录初始的答案
		record[before[i]]++;		   //桶，record[i]=前面有i个数字比它大的数字的数量
		add(input[i], 1);			   //树状数组作桶
	}
	memset(tree, 0, sizeof(tree)); //清空
	add(1, tot);				   //实现差分，先把序列总逆序对数量放在最前面
	tot = 0;
	for (int i = 0; i < n; ++i)
	{
		tot += record[i]; //每次tot记录的是前面有小于等于i个数字比它大的数字的数量
		//则n-tot即为前面有大于i个数字比它大的数字的数量
		add(i + 2, -(n - tot)); //实现差分，在这一个位置会有n-tot个数字逆序对数减1
								//由于下标问题，i必须+2，这样当i=0时就会储存在第2位，而第1位是放总逆序对数的
	}
	for (int i = 0, opt, x; i < m; i++)
	{
		scanf("%d%d", &opt, &x);
		x = min(x, n - 1); //对opt=2的情况进行优化
		if (opt == 1)
		{
			x--;
			if (input[x] < input[x + 1])
			{
				swap(input[x], input[x + 1]);
				swap(before[x], before[x + 1]);
				add(1, 1);					//逆序对总数量增加1
				add(before[x + 1] + 2, -1); //由于before[x+1]增加了，所以在原before[x+1]轮时也可以使逆序对-1，所以记录-1
				before[x + 1]++;			//input[x]交换到x+1位上后，前面比它大的数量增加了1
			}
			else
			{
				swap(input[x], input[x + 1]);
				swap(before[x], before[x + 1]);
				add(1, -1);			   //逆序对总数量减少1
				before[x]--;		   //input[x+1]交换到x位上后，前面的比它大的数量减少了1
				add(before[x] + 2, 1); //由于before[x]减少了，所以在原before[x]轮时无法使逆序对减少，所以记录1
			}
		}
		else
			printf("%lld\n", sum(x + 1)); //直接输出答案
	}
	return 0;
}
```

---

## 作者：xht (赞：38)

考虑冒泡排序一轮对逆序对的变化。

首先给出结论：假设原本在位置 $i$ 上的逆序对数为 $c_i$，冒泡排序一轮后，位置 $i$ 上的逆序对数变为 $\max(0, c_{i+1}-1)$。

相当于一个**左移，减一，与 $0$ 取 $\max$** 的过程。

为什么呢？

冒泡排序一轮的本质，其实就是从第一个数开始，将其拿出来，放到它后面第一个比它大的数之前，然后将比它大的那个数拿出来，再往后放，以此类推。

假设我们拿出来的数原本的下标为 $i$，要放到下标为 $j$ 之前的位置，则 $(i,j)$ 这个里面的数全部往前移了一位，同时在它们上面的逆序对数少了一个。

而拿出来的数一定是逆序对数为 $0$ 的位置，否则前面一定有比它大的数，它就一定不会被拿出来。

因此**左移，减一，与 $0$ 取 $\max$** 的过程就是逆序对数变化的过程。

有了这个结论，剩下的就好做了，用树状数组维护每个逆序对数的个数以及它们对答案的贡献即可。

```cpp
const int N = 2e5 + 7;
int n, m, a[N], b[N], c[N];
ll s[N];

inline void add(int x, int k, ll w = 0) {
	while (x <= n) c[x] += k, s[x] += w, x += x & -x;
}

inline pair<int, ll> ask(int x) {
	int k = 0;
	ll w = 0;
	while (x) k += c[x], w += s[x], x -= x & -x;
	return mp(k, w);
}

int main() {
	rd(n), rd(m), rda(a, n);
	for (int i = 1; i <= n; i++)
		b[i] = ask(n).fi - ask(a[i]).fi, add(a[i], 1);
	for (int i = 1; i <= n; i++) c[i] = 0;
	for (int i = 1; i <= n; i++)
		if (b[i]) add(b[i], 1, b[i]);
	while (m--) {
		int o, x;
		rd(o), rd(x);
		if (o == 1) {
			if (a[x] < a[x+1]) {
				if (b[x]) add(b[x], -1, -b[x]);
				++b[x];
				if (b[x]) add(b[x], 1, b[x]);
			} else {
				if (b[x+1]) add(b[x+1], -1, -b[x+1]);
				--b[x+1];
				if (b[x+1]) add(b[x+1], 1, b[x+1]);
			}
			swap(a[x], a[x+1]), swap(b[x], b[x+1]);
		} else {
			if (x >= n) print(0);
			else {
				pair<int, ll> p1 = ask(n), p2 = ask(x);
				print(p1.se - p2.se - 1ll * (p1.fi - p2.fi) * x);
			}
		}
	}
	return 0;
}
```

---

## 作者：ix35 (赞：19)

## P6186 冒泡排序

一道比较无聊的题目，比较常规，考到一个半小时左右的时候会的。

考虑一轮冒泡排序对逆序对数的影响，举个栗子：

$$4\ \ 3\ \ 2\ \ 5\ \ 1$$

经过一轮冒泡排序变成了：

$$3\ \ 2\ \ 4\ \ 1\ \ 5$$

设一轮冒泡排序前的序列为 $A$，冒泡排序后的序列为 $B$。

**观察 $1$：$B$ 中所有逆序对都在 $A$ 中出现。**

证明略。

继续观察，$A$ 中有哪些逆序对到 $B$ 中消失了呢？可以发现是 $(4,3),(4,2),(5,1)$ 这三对。

**观察 $2$：对于 $A$ 中每一个不是前缀最大值的 $a_i$，$B$ 中以 $a_i$ 作为后项的逆序对比 $A$ 中少一组。**

证明：由于 $a_i$ 不是前缀最大值，设 $a_j$ 是 $a_1$ 到 $a_{i-1}$ 的最大值，那么有 $a_j>a_i$，且在冒泡排序过程中，$a_j$ 会浮到 $a_i$ 后面，所以 $(a_j,a_i)$ 这对逆序对消失，同时，其他的以 $a_i$ 为后项的逆序对 $(a_k,a_i)$ 由于 $a_j$ 将会和 $a_i$ 在 $i$ 位置交换一次，所以不会造成 $a_k$ 跑到 $a_i$ 之后的情况。

有了这个结论，我们可以得到如下推论：

**推论 $1$：对 $A$ 进行一轮冒泡排序，逆序对数的减小量是 $n-C$，其中 $C$ 为 $A$ 中前缀最大值的个数。**

然而这样我们只能处理冒泡一轮的情况，多轮冒泡排序更加复杂一些，但是根据观察 $2$ 的证明，我们可以得到一个更强的结论：

**推论 $2$：如果在原序列中，在 $a_i$ 之前有 $p_i$ 个数比 $a_i$ 大，则 $a_i$ 将在 $p_i$ 轮冒泡排序后成为前缀最大值。**

证明：每一轮有一个 $a_i$ 之前比 $a_i$ 大的数浮到 $a_i$ 之后，这样 $p_i$ 轮之后 $a_i$ 之前比 $a_i$ 大的数全都到 $a_i$ 后面了，在前缀 $i$ 中 $a_i$ 就是最大值。

到这里，需要的结论就全部有了，下面开始推式子。

$$Ans=\sum\limits_{i=1}^n p_i-\sum\limits_{i=1}^k (n-C_i)$$

其中 $C_i$ 表示第 $i$ 轮冒泡排序之前 $A$ 中前缀最大值的个数，$k$ 表示冒泡排序的轮数。

考虑每一个 $a_i$ 对于 $\sum\limits_{i=1}^k C_i$ 的贡献，由于 $a_i$ 在 $p_i$ 轮后成为前缀最大值，所以对于 $p_i$ 到 $k$ 中间的每一轮都会有 $1$ 的贡献，即：

$$Ans=\sum\limits_{i=1}^np_i-nk+\sum\limits_{i=1}^n \max(0,k-p_i)$$

要和 $0$ 取 $\max$ 是因为，如果 $k<p_i$，则 $a_i$ 对答案的减量没有贡献。

进一步化简一下：

$$Ans=\sum\limits_{i=1}^n p_i-nk+kX-Y$$

其中 $X$ 是 $p_i\leq k$ 的 $p_i$ 的数量，$Y$ 是 $p_i\leq k$ 的 $p_i$ 的和。

由于都是全局的信息，直接开一棵权值线段树或权值树状数组即可维护 $X$ 和 $Y$。

相邻项的交换非常容易实现，都是 $p_i$ 的单点修改。

时间复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=200010;
int n,m,x,y,a[MAXN],p[MAXN],c[MAXN];
ll val[MAXN*4],siz[MAXN*4];
int query (int x) {
	int res=0;
	for (int i=x;i;i-=(i&(-i))) {res+=c[i];}
	return res;
}
void modify (int x,int v) {
	for (int i=x;i<=n;i+=(i&(-i))) {c[i]+=v;}
	return;
}
void modify_t (int p,int l,int r,int pos,int v,int w) {
	val[p]+=w,siz[p]+=v;
	if (l==r) {return;}
	int mid=(l+r)>>1;
	if (pos<=mid) {modify_t(p<<1,l,mid,pos,v,w);}
	else {modify_t((p<<1)|1,mid+1,r,pos,v,w);}
	return;
}
ll query_t (int p,int l,int r,int xl,int xr,int typ) {
	if (xr<l||r<xl) {return 0;}
	if (xl<=l&&r<=xr) {return (typ?val[p]:siz[p]);}
	int mid=(l+r)>>1;
	return query_t(p<<1,l,mid,xl,xr,typ)+query_t((p<<1)|1,mid+1,r,xl,xr,typ);
}
int main () {
	freopen("bubble.in","r",stdin);
	freopen("bubble.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		p[i]=query(n)-query(a[i]);
		modify_t(1,0,n,p[i],1,p[i]);
		modify(a[i],1);
	}
	for (int i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		if (x==1) {
			if (a[y]<a[y+1]) {
				modify_t(1,0,n,p[y],-1,-p[y]);
				p[y]++;
				modify_t(1,0,n,p[y],1,p[y]);
			} else {
				modify_t(1,0,n,p[y+1],-1,-p[y+1]);
				p[y+1]--;
				modify_t(1,0,n,p[y+1],1,p[y+1]);
			}
			swap(a[y],a[y+1]);
			swap(p[y],p[y+1]);
		} else {
			ll ans1=val[1],ans2=query_t(1,0,n,0,y,1);
			ll ans3=(1ll*n*y),ans4=(1ll*y*query_t(1,0,n,0,y,0));
			printf("%lld\n",ans1+ans4-ans2-ans3);
		}
	}
	return 0;
}
```





---

## 作者：littleKtian (赞：16)

本来比赛时能A的，结果最后改线段树查询手抽打错了，而且错的还交上去了，完美爆零。

---------------------------

设 $a[i]$ 表示 $i$ 在排列中在 $i$ 前面大于 $i$ 的数字的个数，易得总的逆序对个数就是 $\sum\limits_{i=1}^na[i]$。

考虑每轮冒泡排序对 $a[i]$ 的影响。

如果 $a[i]>0$，说明在 $i$ 前面存在数字大于 $i$，那么在这一轮冒泡排序的过程中一定会有一个大于 $i$ 的数从 $i$ 前面换到后面，也就是 $a[i]$ 变成 $a[i]-1$。

如果 $a[i]=0$，说明在 $i$ 前面没有数比 $i$ 大，而所有比 $i$ 大的数在冒泡排序的过程中并不会从 $i$ 后面换到前面，所以 $a[i]$ 不变仍为 $0$。

设 $b[i]$ 表示 $a[j]=i$ 的个数，答案转化为 $\sum\limits_{i=k}^{n-1}(i-k)\times b[i]$。

用线段树维护即可。

开始计算 $a[i]$ 可用树状数组。

```
#include<bits/stdc++.h>
#define ll long long
#define ls(w) w<<1
#define rs(w) (w<<1)^1
using namespace std;
struct xds{
	int l,r;
	ll x,y;
};
xds tree[800005];
ll sz[200005],nxd[200005],t[200005];
int n,m,p[200005];
int dr()
{
	int xx=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')xx=(xx<<1)+(xx<<3)+ch-'0',ch=getchar();
	return xx*f;
}
void xg(int w,ll x){while(w<=n)sz[w]+=x,w+=w&-w;}
ll cx(int w){ll x=0;while(w)x+=sz[w],w-=w&-w;return x;}
void u(int w){tree[w].x=tree[ls(w)].x+tree[rs(w)].x,tree[w].y=tree[ls(w)].y+tree[rs(w)].y;}
void csh(int w,int l,int r)
{
	tree[w].l=l,tree[w].r=r;
	if(l==r)
	{
		tree[w].x=t[l]*l,tree[w].y=t[l];
		return;
	}
	int mid=(l+r)>>1;
	csh(ls(w),l,mid),csh(rs(w),mid+1,r);
	u(w);
}
void xg_2(int w,int xh,ll x)//不要问我为什么是2，我原来写过一个区间修改发现没用删了
{
	if(tree[w].l==tree[w].r)
	{
		tree[w].y+=x,tree[w].x=tree[w].y*tree[w].l;
		return;
	}
	int mid=(tree[w].l+tree[w].r)>>1;
	if(xh<=mid)xg_2(ls(w),xh,x);
	else xg_2(rs(w),xh,x);
	u(w);
}
ll cx_1(int w,int l,int r)
{
	if(r<l)return 0; 
	if(l<=tree[w].l&&tree[w].r<=r)return tree[w].x;
	int mid=(tree[w].l+tree[w].r)>>1;ll x=0;
	if(l<=mid)x+=cx_1(ls(w),l,r);
	if(mid<r)x+=cx_1(rs(w),l,r);
	return x;
}
ll cx_2(int w,int l,int r)
{
	if(r<l)return 0;
	if(l<=tree[w].l&&tree[w].r<=r)return tree[w].y;
	int mid=(tree[w].l+tree[w].r)>>1;ll x=0;
	if(l<=mid)x+=cx_2(ls(w),l,r);
	if(mid<r)x+=cx_2(rs(w),l,r);
	return x;
}
int main()
{
	//freopen("bubble.in","r",stdin);
	//freopen("bubble.out","w",stdout);
	n=dr(),m=dr();
	for(int i=1;i<=n;i++)
	{
		p[i]=dr();
		nxd[p[i]]=cx(n)-cx(p[i]),++t[nxd[p[i]]];
		xg(p[i],1);
	}
	csh(1,0,n-1);
	while(m--)
	{
		int opt=dr();
		if(opt==1)
		{
			int x=dr();
			if(p[x]>p[x+1])xg_2(1,nxd[p[x+1]],-1),xg_2(1,nxd[p[x+1]]-1,1),--nxd[p[x+1]];
			else xg_2(1,nxd[p[x]],-1),xg_2(1,nxd[p[x]]+1,1),++nxd[p[x]];
			swap(p[x],p[x+1]);
		}
		if(opt==2)
		{
			int k=dr();
			printf("%lld\n",cx_1(1,k,n-1)-k*cx_2(1,k,n-1)); 
		}
	}
}
```


---

## 作者：Thinking (赞：13)

首先冒泡排序肯定跟逆序对有关。

我们记 $cnt_i$ 满足 $a_j>a_i,j<i$ 的个数，然后观察一下每遍冒泡排序对 $cnt$ 的影响：

```
a   3 4 2 1
cnt 0 0 2 3
```

一遍冒泡排序之后：

```
a   3 2 1 4
cnt 0 1 2 0
```

不难得（cai）出 $cnt$ 的变化为整体前移一位，所有正值减一。

简证：观察冒泡排序的过程，我们发现 $[1,i]$ 区间内只有最大值会被移到 $i$ 后面去（如果 $i$ 就是最大值，那么 $cnt_i=0$，没有讨论意义），显然 $cnt_i$ 会减少一，同时 $i$ 会向前移动到 $i-1$，证毕。

同时，一个显然的优秀性质是：$cnt_1=0$。也就是说前移不会导致逆序对数减少，因此$k$次冒泡排序后的逆序对数就是 $\sum\max(cnt_i-k,0)$，可以用树状数组维护。

而交换只会引发 $cnt_x$ 和 $cnt_{x+1}$ 的变化，因此总复杂度 $O((n+m)logn)$。

```cpp
#include<cstdio>
#include<cstring>
#define For(i,A,B) for(i=(A);i<=(B);++i)
typedef long long ll;
const int N=200050;
const int BUF=1<<21;
char rB[BUF],*rS,*rT,wB[BUF+50];
int wp=-1;
inline char gc(){return rS==rT&&(rT=(rS=rB)+fread(rB,1,BUF,stdin),rS==rT)?EOF:*rS++;}
inline void flush(){fwrite(wB,1,wp+1,stdout);wp=-1;}
inline int rd(){
    char c=gc();
    while(c<48||c>57)c=gc();
    int x=c&15;
    for(c=gc();c>=48&&c<=57;c=gc())x=(x<<3)+(x<<1)+(c&15);
    return x;
}
short buf[25];
inline void wt(ll x){
    if(wp>BUF)flush();
    short l=-1;
    while(x>9){
        buf[++l]=x%10;
        x/=10;
    }
    wB[++wp]=x|48;
    while(l>=0)wB[++wp]=buf[l--]|48;
    wB[++wp]='\n';
}
int a[N],p[N],c[N],n;
ll C[N],ans[N];
inline void Swap(int &a,int &b){int t=a;a=b;b=t;}
inline void add(int x,int ck,int sk){
    for(;x;x^=x&-x){c[x]+=ck;C[x]+=sk;}
}
inline void ask(int x,int &cnt,ll &sum){
    sum=cnt=0;
    for(;x<=n;x+=x&-x){cnt+=c[x];sum+=C[x];}
}
int main(){
    int m,i,cnt,opt,x;
    ll sum;
    n=rd();m=rd();
    For(i,1,n)a[i]=rd();
    For(i,1,n){
        ask(a[i],p[i],sum);
        add(a[i],1,0);
    }
    memset(c,0,sizeof(c));
    For(i,1,n)add(p[i],1,p[i]);
    while(m--){
        opt=rd();x=rd();
        if(opt==1){
            if(a[x]<a[x+1]){
                add(p[x],-1,-p[x]);
                ++p[x];
                add(p[x],1,p[x]);
            }else{
                add(p[x+1],-1,-p[x+1]);
                --p[x+1];
                add(p[x+1],1,p[x+1]);
            }
            Swap(a[x],a[x+1]);
            Swap(p[x],p[x+1]);
        }else if(opt==2)if(x>=n)wt(0ll);
        else{
            ask(!x?1:x,cnt,sum);
            wt(sum-(ll)cnt*x);
        }
    }
    flush();
    return 0;
}
```


---

## 作者：zhengrunzhe (赞：10)

来一波真爱平衡树

首先考虑一轮冒泡排序会发生什么

$1 \ 1 \ 4 \ 5 \ 1 \ 4 \rightarrow 1 \ 1 \ 4 \ 1 \ 4 \ 5$

假设我们搞一个数组表示每个数前面有多少个比他大的数记作$w_i$

$0 \ 0 \ 0 \ 0 \ 2 \ 1 \rightarrow 0 \ 0 \ 0 \ 1 \ 0 \ 0$

由于数字被交换了，所以我们把新的数组与原本位置对应来看

$0 \ 0 \ 0 \ 0 \ 2 \ 1 \rightarrow 0 \ 0 \ 0 \ 0 \ 1 \ 0$

也就是相当于每个非零位置上-1

先预处理出原数组的逆序对个数，一轮冒泡对答案的减少量就是有多少个非零的$w$

考虑k轮会发生什么，$\leq k$的部分被减掉$w_i$次变为0，$>k$的部分最多被减掉k次

**所以k轮冒泡对答案的减少量是(<=k的和)+k(>k的个数)**

考虑交换会发生什么，一开始我以为是交换任意两个，还在想树套树完怎么查答案，后来发现只交换相邻的、、、、

交换相邻两个数($a_x,a_{x+1}$)，分类讨论一下


$1.a_x>a_{x+1}$，原本$x$对$x+1$是有贡献的，交换之后不影响$x+1$之后的数，因为后面的数的前面的数并没有改变，$x$前面的数又不会影响到，所以只会少一对逆序对，答案$--$，并且$w_{x+1}--$

$2.a_{x+1}>x$，同理，多一对逆序对，答案$++$，$w_x++$

如何预处理$w$？——开局树状数组维护即可

然后后面数据结构随便维护就好了，支持单点修改、查$\leq k$的和，$>k$的个数，我选择平衡树~~(虽然说值域都不超过n直接树状数组就好了)~~

```cpp
#include<cstdio>
#include<cstdlib>
typedef long long ll;
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<1)+(in<<3)+(ch&15),ch=getchar();
}
template<class type>inline const void swap(type &a,type &b){const type c(a);a=b;b=c;}
const int N(2e5+5);
namespace Treap
{
	struct tree
	{
		ll sum;
		int val,size,pro,cnt;
		tree *son[2];
		static tree *null;
		void *operator new(size_t size);
		void operator delete(void *ptr);
		inline tree():val(0),sum(0ll),size(0),pro(0),cnt(0)
		{
			static bool init(0);
			if (!init)
				init=1,
				null=new tree,
				null->son[0]=null->son[1]=null;
			son[0]=son[1]=null;
		}
		inline tree(const int &val):val(val),sum(val),size(1),cnt(1),pro(rand())
		{
			son[0]=son[1]=null;
		}
		inline const void pushup()
		{
			sum=son[0]->sum+1ll*val*cnt+son[1]->sum;
			size=son[0]->size+cnt+son[1]->size;
		}
	}*root,*tree::null;
	#define null tree::null
	char memory_pool[N*sizeof(tree)],*tail(memory_pool+sizeof memory_pool);
	void *recycle[N],**top(recycle);
	inline void *tree::operator new(size_t size){return top!=recycle?*--top:tail-=size;}
	inline void tree::operator delete(void *ptr){*top++=ptr;}
	inline const void init()
	{
		root=null=new tree;
	}
	inline const void rotate(tree *&fa,const bool &f)
	{
		tree *p(fa->son[f]);
		fa->son[f]=p->son[!f];
		p->son[!f]=fa;
		fa->pushup();(fa=p)->pushup();
	}
	inline const void insert(tree *&p,const int &x)
	{
		if (p==null)return p=new tree(x),void();
		if (p->val==x)return p->cnt++,p->pushup();
		const bool f(p->val<x);
		insert(p->son[f],x);
		p->pushup();
		if (p->son[f]->pro<p->pro)rotate(p,f);
	}
	inline const void remove(tree *&p,const int &x)
	{
		if (p==null)return;
		if (p->val^x)return remove(p->son[p->val<x],x),p->pushup();
		if (p->cnt>1)return p->cnt--,p->pushup();
		if (p->son[0]==null&&p->son[1]==null)return delete p,p=null,void();
		if (p->son[0]==null)return p=p->son[1],void();
		if (p->son[1]==null)return p=p->son[0],void();
		const bool f(p->son[0]->pro>p->son[1]->pro);
		rotate(p,f);remove(p,x);
	}
	inline const ll queryl(tree *p,const int &x)
	{
		if (p==null)return 0ll;
		if (x<p->val)return queryl(p->son[0],x);
		if (x==p->val)return p->son[0]->sum+1ll*p->val*p->cnt;
		return queryl(p->son[1],x)+p->son[0]->sum+1ll*p->val*p->cnt;
	}
	inline const int queryr(tree *p,const int &x)
	{
		if (p==null)return 0;
		if (x>p->val)return queryr(p->son[1],x);
		if (x==p->val)return p->son[1]->size;
		return queryr(p->son[0],x)+p->son[1]->size+p->cnt;
	}
}using namespace Treap;
ll tot;
int n,m,a[N],w[N];
class Binary_Indexed_Tree
{
	private:
		int t[N];
		inline const int lowbit(const int &x){return x&-x;}
	public:
		inline const void insert(int x)
		{
			for (;x<=n;x+=lowbit(x))t[x]++;
		}
		inline const int query(int x)
		{
			int sum(0);
			for (;x;x-=lowbit(x))sum+=t[x];
			return sum;
		}
}bit;
int main()
{
	//freopen("bubble.in","r",stdin);freopen("bubble.out","w",stdout);
	init();
	read(n);read(m);
	for (int i(1);i<=n;i++)read(a[i]);
	for (int i(1);i<=n;i++)
		w[i]=i-bit.query(a[i])-1,
		bit.insert(a[i]);
	for (int i(1);i<=n;i++)if (w[i])insert(root,w[i]),tot+=w[i];
	for (int opt,x;m--;)
		if (read(opt),read(x),opt&1)
		{
			if (a[x]>a[x+1])
			{
				tot--;
				remove(root,w[x+1]);
				if (--w[x+1])insert(root,w[x+1]);
			}
			else
			{
				tot++;
				if (w[x])remove(root,w[x]);
				insert(root,++w[x]);
			}
			swap(a[x],a[x+1]);
			swap(w[x],w[x+1]);
		}
		else
			printf("%lld\n",tot-queryl(root,x)-1ll*queryr(root,x)*x);
	return 0;
}
```


---

## 作者：Zlc晨鑫 (赞：7)

### 引入

随便给出一组数据：

`5 3 1 2 4`

初始逆序对数量：6。

---

冒泡排序

一轮：`3 1 2 4 5` 

$6-4=2$。

两轮：`1 2 3 4 5` 

$2-2=0$。

---

### 逆序对块

观察会发现，数 $x$ 会一直后退，直到有一个大于 $x$ 的数 $y$，$y$ 也会一直后退……

后退数将区间划分成了一个个**逆序对块**。

![](https://cdn.luogu.com.cn/upload/image_hosting/koq13q4t.png)

上图是序列中数的大小的柱状图，其中，不同颜色分别代表了不同逆序对块。

为什么要定义逆序对块呢？其实这是我为了分析方便自己编的一个东西（）。

逆序对块的性质：

1. 逆序对块第一个的数是逆序对块中数的最大值。
2. 每个逆序对块的第一个数单调递增。
3. 每个逆序对块的第一个数 $a_x$ 是 $max(a_i), 1 \le i \le x$。

性质1是由定义导出的。

性质2：假设不成立，那么存在两个逆序对块，使得块1的第一个数 $x$ 大于 块2的第一个数 $y$，根据性质1，第二个块中所有数都严格小于 $x$，所以块2可以接到块1后面。

性质3：由性质2，对于任何一个逆序对块的第一个数 $a_x$，一定大于它前面任何一个逆序对块的第一个数；而根据性质1，每个逆序对块中的第一个数都是块的最大数，所以 $a_x$ 前面的逆序对块中的所有数都小于 $a_x$。

---

### 分析

我们发现，逆序对 $(x,y)$ 是一个二元组，直接统计是 $O(N^2)$ 的，考虑将其归类为一个一维的集合。

PS：其实归并排序求逆序对也是对逆序对进行了分类统计。

将逆序对 $(x, y)$ 归类到 以 $y$ 结尾的逆序对集合。

定义数 $f(x)$ 是以 $x$ 结尾的逆序对集合的元素个数（方便后面分析）。

容易发现，每个**逆序对块**中，进行一轮冒泡排序之后，除了第一个数，后面的数的 $f(x)$ 都会减一。

假设第一个数是 $a_1$，那么它一定大于逆序对块中的其它数，所以对于其它数的 $f(x)$ 有大小为 $1$ 的贡献，而排序之后它会一直后退，这个大小为 $1$ 的贡献就没了，所以要减一。

也就是下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/coi3a37l.png)

---

根据定义，一开始的逆序对个数就是 $sum(f(i)), 1 \le i \le n$。

第一轮排序之后，逆序对个数变成了 $f_1 + f_2 - 1 + ... + f_n$ ，由上面的分析，除了逆序对块第一个数，其 $f(x)$ 都会减一；由性质3，$f(x)=0$ 的数就是逆序对块的第一个数，所以答案总共减去了 $n - cnt(f(x)==0)$。

第二轮排序同理，就是在第一轮排序的基础上进行这个操作。

...

---
数学化：

设 $s[i]$ 为 $f[x] = i$ 的 $x$ 个数。

第一轮排序 $f_1 + f_2 + ... + f_n - (n - s[0]) = f_{1-n} - n + s[0]$。

第二轮中新增的 $f_x = 0$ 的个数就是原来 $f_x = 1$ 的个数，因为 $1 - 1 = 0$。

第二轮排序 $f_{1-n} - n + s[0] - (n - s[0] - s[1]) = f_{1-n} - 2n + (2s[0] + s[1])$

形式化的，第 $k$ 轮排序之后就会是 $f_{1-n} - kn + ks[0] + (k-1)s[1] + ... + s[k - 1]$。

这样讨论修改时就可以不去想象逆序对的变化了，只要对着式子分析即可。

记 $ans_i$ 为第 $i$ 轮排序后的答案。

由冒泡排序相关知识，只要记录到 $ans_{n-1}$即可。

容易发现，$s[i]$ 只会对 $ans_{j}, i+1 \le j \le n-1$ 产生影响。

---

交换 $w[a]$ 和 $w[b]$ ，一下讨论 $w[a] > w[b]$ 的情况，另一种情况类似。

注意这里的变量名都是交换前的变量名。

交换之后 $f[b] -- $，导致 $f_{1-n} -- $，也就是 $ans_{0-n-1} -- $。

这样会导致 $s[f[b]] -- , s[f[b] - 1] ++ $，先看前者。

$s[f[b]]$ 对 $ans[f[b]+1]$及其后面产生影响。

$ans[f[b]+1] = ... + s[f[b]]$，$-1$。

$ans[f[b]+2] = ... + 2s[f[b]] + s[f[b]+1]$，$2(s[f[b]]-1)=2s[f[b]]-2$，整体 $-2$。

依此类推……

![](https://cdn.luogu.com.cn/upload/image_hosting/4vbe9n09.png)

我们会发现，这两个操作合在一起，会让 $ans_j ++ , f_b \le j \le n - 1$

---

代码实现：

求 $f(x)$，可以在值域上建立树状数组统计。
修改操作是区间修改，每次查询是单点查询，可以用树状数组维护一个差分数组 $B$ ，前缀和就是变化量，加上原值就是答案。

需要注意的是，因为树状数组的下标最小是1，而 $ans$ 的下标最小是0，所以要加上1个偏移量（+1）。

```cpp
/*
id: luogu P6186
start: 0:01
end: 0:31
debug: 
ver: II
*/

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 5e5 + 10;

struct BinTree
{
    LL c[N];
    int n;

    BinTree(int n = 0)
    {
        this->n = n;
    }

    void add(int x, LL k)
    {
        while (x <= n)
        {
            c[x] += k;
            x += x & -x;
        }
    }

    // 返回[1,x]的和
    LL ask(int x)
    {
        LL ans = 0;
        while (x)
        {
            ans += c[x];
            x -= x & -x;
        }
        return ans;
    }
};

BinTree tr, B;
int w[N], n, q;
LL ans[N]; // 第k轮冒泡后的答案
int f[N]; // f[i]: w[i]前面大于w[i]的数的个数
int s[N]; // s[i] 表示f[j]=i的f[j]的个数

void inp()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
}

void init()
{
    tr.n = n;
    for (int i = 1; i <= n; i ++ )
    {
        f[i] = i - 1 - tr.ask(w[i]); // [1,w[i]]
        s[f[i]] ++ ;
        ans[0] += f[i];
        tr.add(w[i], 1);
    }

    // 最多进行i-1轮
    LL t = s[0]; // 初始逆序对块的第一个数的个数
    for (int i = 1; i < n; i ++ )
    {
        ans[i] = ans[i - 1] - n + t;
        t += s[i];
    }
}

void out()
{
    B.n = n;
    while (q -- )
    {
        int t, c;
        scanf("%d%d", &t, &c);
        // 别忘记这句!
        c = min(c, n - 1);
        if (t == 1)
        {
            int a = c, b = c + 1;
            if (w[a] > w[b])
            {
                B.add(1, -1);
                B.add(f[b] + 1, 1);
                f[b] -- ;
                swap(w[a], w[b]);
                swap(f[a], f[b]);
            }
            else
            {
                B.add(1, 1);
                B.add(f[a] + 2, -1);
                f[a] ++ ;
                swap(w[a], w[b]);
                swap(f[a], f[b]);
            }
        }
        else printf("%lld\n", ans[c] + B.ask(c + 1));
    }
}

int main()
{
    inp();
    init();
    out();
    return 0;
}
```

---

如果觉得这篇题解写得好，不要忘记点个赞。

---

## 作者：良心WA题人 (赞：7)

# 简洁描述：
对一个序列给定两种操作，交换两个相邻的数，求经过$k$轮冒泡排序后逆序对个数。一轮冒泡排序指的是冒泡排序内层循环执行一遍。
# 分析：
可以发现，一个数能进行交换，当且仅当前面没有比它大的数。而且每轮前面比它大的数都会少$1$，因为前面有且仅有一个最大的数到它的后面，其他较大且能交换的数一定遇到这个最大的数停止交换。所以一个数在第几轮被放在正确位置就看它前面数的个数。
再来研究交换。每次交换如果$a<b$，则逆序对加一，左边的数比它大的数加一。如果$a>b$，则逆序对减一，右边的数比它大的数减一。
再发现，想知道某一轮的逆序对个数那么就是总的逆序对个数减去它前面每轮交换个数即可。每轮交换的个数就是$n-$放正确的个数。因为没放正确的都会和一个放正确大的做交换，所以就是求一个前缀和，要求前缀和用树状数组啊！把第一个设为总的逆序对，后面的都是这一轮少的逆序对个数。交换一次就更新一下变化的数。因为我们要在求逆序对的同时求出前面比它大的个数，就刚好用树状数组求很好。不知道怎么求的，参考我写的[专辑：树状数组](https://blog.csdn.net/weixin_44043668/article/details/106591704)。
细节问题：因为最开始我们在全部的逆序对进行修改，这样后面的所有的逆序对个数都有了变化。那么什么时候变化要还原呢？过了交换之后的轮数就和原来是一样的了。因为到了那个轮数把它们原来该交换的地方交换了要么就换回去，要么就原序列换成新序列，所以在该轮结束后要还原逆序对。
时间复杂度$\Theta(m\log n)$。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+5;
int n,m,a[NN],b[NN],num[NN];
long long c[NN];
int lowbit(int x)
{
    return x&-x;
}
void add(int x,long long sum)
{
    while(x<=n)
	{
        c[x]+=sum;
        x+=lowbit(x);
    }
}
long long find(int x)
{
    long long res=0;
    while(x>0)
	{
        res+=c[x];
        x-=lowbit(x);
    }
    return res;
}
int main()
{
    scanf("%d%d",&n,&m);
    long long res=0;
    for(int i=1;i<=n;i++)
	{
        scanf("%d",&a[i]);
        b[i]=i-1-find(a[i]);
		++num[b[i]];
        res+=b[i];
        add(a[i],1);
    }
    memset(c,0,sizeof(c));
    add(1,res);
    int t=0;
    for(int i=1;i<=n;i++)
	{
        t+=num[i-1];
        add(i+1,-(n-t));
    }
    for(int i=1;i<=m;i++)
	{
		int opt,x;
        scanf("%d%d",&opt,&x);
        x=min(x,n-1);
        if(opt==1)
		{
            if(a[x]<a[x+1])
			{
                swap(a[x],a[x+1]);
                swap(b[x],b[x+1]);
                add(1,1);
                b[x+1]++;
                add(b[x+1]+1,-1);
            }
            else
			{
                swap(a[x],a[x+1]);
                swap(b[x],b[x+1]);
                add(1,-1);
                add(b[x]+1,1);
                b[x]--;
            }
        }
        else
			printf("%lld\n",find(x+1));
    }
    return 0;
}
```

---

## 作者：DeNeRATe (赞：6)

CSP的时候被unsigned long long坑的死去活来。

这次考试又被LL坑得不要不要的(~~三年OI一场空，不开LL见祖宗~~)

(终究还是我太蒟蒻了|stO AK Orz|)

刚开始考的时候就觉得这道题emm。。。


------------


考场上的**思路**：

1.首先康到时逆序对，就肯定想到了树状数组。

2.接下来就是如何处理这个冒泡排序k轮之后逆序对的对数(~~手动模拟即可~~)，

因为每次冒泡排序是把Num[i]>Num[i+1]的交换一次，

由树状数组的过程可知每次对于Num[i],找到1~i-1中比Num[i]大的数的个数。

因为Num[1]~Num[i-1]中一定有一个最大的(这i-1个数中有比第i个数大的)Num[j]，

而在一次冒泡排序过程中这个Num[j]一定会和Num[i]交换一次，

所以我们就可以统计对于每一个i，Num[1]~Num[i-1]中比Num[i]大的数的个数，

那么每次冒泡排序就会使得它减1。

3.我们就可以模拟一下这个过程，看下还缺什么。

Total=15,Test=10,Num[]={3 5 1 4 10 14 11 12 13 6 8 9 2 15 7}。

先是每个的逆序对个数Inv[]={0 0 2 1 0 0 1 1 1 5 5 5 11 0 8}。

在进行完第一次冒泡排序后，Inv[]={0 0 1 0 0 0 0 0 0 4 4 4 10 0 7}。

发现确实是每个Inv[i]>0的都减少了1。

那么现在需要的就是如何来快速求出这个Inv数组变化k次之后的总和。

因为这个题是1~n的排列，且n最大是2e5，那么就可以直接用线段树维护。

具体的，L=R时,Tree[X]=Cnt[L],Cnt[i]即为逆序对个数为i的数有多少个。


------------


All in all，整个题就变成了**树状数组**和**线段树**的emm题了。。。

那么就直接上**代码**了。。。

```cpp
//bubble
#include <iostream>
#include <cstdio>
// #include <windows.h>
#include <cstring>
#include <cmath>
#include <algorithm>

#define LL long long
#define INF 0x7fffffff
#define FOR(i,A,B) for(LL i=A;i<=B;i++)
#define BOR(i,A,B) for(LL i=A;i>=B;i--)
#define Cl(X,Y) memset((X),(Y),sizeof(X))
#define Lson (X<<1)
#define Rson (X<<1|1)
#define Lowbit(X) (X&(-X))
using namespace std;
const LL MAXn=2e5+10;

LL Total,Test,Num[MAXn],Cnt[MAXn],Inv[MAXn];
LL Opt,Fro[MAXn],Loc;
struct Node {
    LL Zero,Tot,Mine;
}Tree[MAXn<<2];

inline void File() {
    freopen("bubble.in","r",stdin);
    freopen("bubble.out","w",stdout);
}

inline LL Read() {
    LL Temp=0,Fac=1;
    char Ch=getchar();
    while(Ch<'0' || Ch>'9') { if(Ch=='-') Fac=-1; Ch=getchar(); }
    while(Ch>='0' && Ch<='9') { Temp=(Temp<<1)+(Temp<<3)+Ch-'0'; Ch=getchar(); }
    return Temp*Fac;
}

inline void Push_up(LL X) { Tree[X].Zero=Tree[Lson].Zero+Tree[Rson].Zero; Tree[X].Tot=Tree[Lson].Tot+Tree[Rson].Tot; Tree[X].Mine=Tree[Lson].Mine+Tree[Rson].Mine; }
inline void Renew(LL Temp) { while(Temp<=Total) { Fro[Temp]++; Temp+=Lowbit(Temp); } }
inline LL Get(LL Temp) { LL Res=0; while(Temp) { Res+=Fro[Temp]; Temp-=Lowbit(Temp); } return Res; }
inline void Build_Tree(LL L,LL R,LL X) {
    if(L==R) { Tree[X].Tot+=Cnt[L]; if(!Tree[X].Tot) Tree[X].Zero=1; Tree[X].Mine+=L*Tree[X].Tot; return; }
    LL Mid=(L+R)>>1;
    Build_Tree(L,Mid,Lson); Build_Tree(Mid+1,R,Rson);
    Push_up(X);
}

inline LL Query(LL L,LL R,LL From,LL To,LL Temp,LL X) {
    if(L>To || R<From) return 0;
    if(L>=From && R<=To) return Tree[X].Mine-Tree[X].Tot*Temp;
    LL Mid=(L+R)>>1,Res=0;
    if(From<=Mid) Res+=Query(L,Mid,From,To,Temp,Lson);
    if(To>Mid) Res+=Query(Mid+1,R,From,To,Temp,Rson);
    return Res;
}

inline void Update(LL L,LL R,LL Dir,LL Temp,LL X) {
    if(L==R && L==Dir) { 
		if(Temp==1) if(Tree[X].Tot==0) { Tree[X].Tot++; Tree[X].Zero--; Tree[X].Mine+=L; } else Tree[X].Tot++,Tree[X].Mine+=L;
		if(Temp==-1) if(Tree[X].Tot==1) { Tree[X].Tot--; Tree[X].Zero++; Tree[X].Mine-=L; } else Tree[X].Tot--,Tree[X].Mine-=L;
		return ;
	}
    LL Mid=(L+R)>>1;
    if(Dir<=Mid) Update(L,Mid,Dir,Temp,Lson);
    else Update(Mid+1,R,Dir,Temp,Rson);
    Push_up(X);
}

inline void Change(LL Temp) {
    if(Num[Temp]>Num[Temp+1]) {
        Update(0,Total,Inv[Temp+1],-1,1); 
        Inv[Temp+1]--;
        Update(0,Total,Inv[Temp+1],1,1);
    } else {
        Update(0,Total,Inv[Temp],-1,1); 
        Inv[Temp]++;
        Update(0,Total,Inv[Temp],1,1);
    }
    swap(Inv[Temp],Inv[Temp+1]);
    swap(Num[Temp],Num[Temp+1]);
}

int main() {
    File();
    Total=Read(); Test=Read();
    FOR(i,1,Total) {
        Num[i]=Read();
        Inv[i]=Get(Total+1-Num[i]); Renew(Total+1-Num[i]);
        Cnt[Inv[i]]++;
    }
    Build_Tree(0,Total,1);
    while(Test--) {
        Opt=Read(); Loc=Read();
        if(Opt==1) Change(Loc);
        else printf("%lld\n",Query(0,Total,Loc+1,Total,Loc,1));
    }
    fclose(stdin); fclose(stdout);
    // system("pause");
    return 0;
}
/*
15 10
3 5 1 4 10 14 11 12 13 6 8 9 2 15 7 
*/
```
害，还是败在了LL上。。。太蒟蒻了o(╥﹏╥)o

---

## 作者：Durancer (赞：4)




### 标签： 树状数组 结论
---

#### 前言

一个极具思维难度的题目，做线段树正好碰见了，就用树状数组把他艰难地A掉了（雾

#### 思路

**结论一**：对于冒泡排序，可以知道，有实际意义的最多是循环 $n-1$ 次 。

**结论二**：对于每一遍冒泡排序，手模几组样例可以发现，对于某一个位置的**某一个数的逆序对**，只要它当前的逆序对个数不为 $0$，那么一遍冒泡排序以后，它贡献的逆序对数量必定减一。

几个例子： $4 \ 3 \ 1 \ 2 $，$1$ 贡献的逆序对为 $2$ ,经过一遍冒泡排序成为 $3\ 1\ 2\ 4$, $1$ 贡献的逆序对为 $1$。

**结论三**：对于交换两个位置的数,分为两种情况：

$$a[x]>a[x+1]$$

这种情况下交换以后，原先 $a[x]$ 代表的数贡献的逆序对的数量不变，原先 $a[x+1]$ 代表的数贡献的逆序对的数量 $-1$。

$$a[x]<a[x+1]$$

这种情况下交换以后，原先 $a[x]$ 的数贡献的逆序对的数量 $+1$，原先 $a[x+1]$ 代表的数贡献的逆序对的数量不变。

**结论四**：如果一个数贡献的逆序对的数量为 $k$ 的话，那么他只会对前 $i$ 次冒泡排序有贡献。

#### 做法

**第一阶段**为预处理初始序列的值，用权值树状数组求出每个位置的数贡献的逆序对的数量。并且记录每一个贡献的个数，（比如贡献为 $3$ 的有 $2$ 个，就把他们存桶里）。

**第二阶段**为初始化树状数组：可以把树状数组的每个位置 $i$ 定义为第$i-1$ 次操作的修改值，为了方便处理，$1$ 位置暂且放上初始的逆序对值。

**第三阶段**来上传每次冒泡排序的修改值，可以用这么一个思维来处理他:把我们刚才存的桶拿过来用一下，循环枚举 $0…n-1$ 的值，并用一个变量 $cnt$ 记录前 $i$ 个的总和，有什么用呢？模拟一下就知道了。

假设枚举到了 $i=0$ 此时 加上这个值之后，$cnt=3$，假设 $n=5$,那么可推出第一轮的需要修改的值为 $-(n-cnt)$，因为 $0$ 的一定不会有贡献了，一次类推即可。

**第四阶段**是最重要的修改操作了，根据上面的结论，可以不考虑位置了，只用考虑逆序对的个数来修改。

当一个数贡献的逆序对个数 $+1$ 之后，如果本来贡献的逆序对个数为 $0$ ,那么现在可以给 $i=2$ 也就是第一轮贡献一个 $-1$ 修改值了。

当一个数贡献的逆序对个数 $-1$ 之后，如果本来贡献的逆序对个数为 $3$ 那么就要对 $i=4$ 的贡献就没有了，就 $+1$ 。

**第五阶段**查询，输出 $sum(x+1)$

#### 代码实现

```cpp
/*
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#define int long long 
using namespace std;
const int N=2e5+9;
int t[N];
int a[N];
int n,m; 
int biger[N];//记录一下每个位置逆序对的个数的个数，桶存每个个数的数量
//K个一定会在第k次冒泡中全部消去 
int ans;//初始序列逆序对的个数 
int imp[N];//每个位置逆序对的个数 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();} 
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
} 
int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int val)
{
	while(x<=n)
	{
		t[x]+=val;
		x+=lowbit(x);
	}
}
int query(int x)
{
	int ret=0;
	while(x)
	{
		ret+=t[x];
		x-=lowbit(x);
	}
	return ret;
}
signed main()
{
	n=read();
	m=read();
	//考虑到记录逆序对的问题，序号从0开始 
	for(int i=0;i<n;i++)
	{
		a[i]=read();
		imp[i]=i-query(a[i]);//查找逆序对个数
		ans+=imp[i];//记录逆序对总个数 
		biger[imp[i]]++;//桶存这个数量
		add(a[i],1);//上传	 
	} 
	memset(t,0,sizeof(t));//一次不清空，OI一场空
	//从现在开始t数组，定义改变，为 query(x) 为x次冒泡排序后的逆序对个数
	add(1,ans);//1 为 没有操作，为了方便，用 0 不行，所以都把操作数+1
	int cnt=0;
	for(int i=0;i<n;i++)//预处理实现差分
	{
		cnt+=biger[i];
		add(i+2,-(n-cnt));//用于计算第k轮会有多少个减少
		/*
		
		cnt 所记录的是逆序对数<=i的，则大于i的就是在第i轮中减去的数量
		就比如，知道了逆序对为0的数量num，则在第一轮中减去的个数一定是 （n-num）;
		其他的同理可得 
		
		*/	
	}  
	while(m--)
	{
		int opt=read();
		int x=min(read(),n-1);//最多会有n-1轮排序
		if(opt==1)
		{
			x--;
			if(a[x]<a[x+1])//解析看上面
			{
				swap(a[x],a[x+1]);
				swap(imp[x],imp[x+1]);
				add(1,1);//这种情况会多一个逆序对
				add(imp[x+1]+2,-1);
				/*
				
				假设imp[x+1]=0，通过转换，多了个1。
				那么就会在第一轮发挥作用，下标从0开始的，所以 
				会在+2轮发挥作用，多减去个1 
				
				*/	
				imp[x+1]++;
			}	
			else 
			{
				swap(a[x],a[x+1]);
				swap(imp[x],imp[x+1]);
				add(1,-1);
				imp[x]--;
				add(imp[x]+2,1);
				/*
				
				假设本来imp[x]=1，那么 会在第一轮（i=2）的时候会被-1
				而现在 imp[x]=0,了，那么 就要在 (i=0+2) 轮的时候+1 减去这个效应 
				
				*/
			}
		} 
		else printf("%lld\n",query(x+1)); 
	} 
	return 0;
}
```

---

## 作者：林蔭 (赞：4)

# **三棵树油漆**
提供一个常规的做法的线段树写法

由于树状数组还要差分(至少我看到的题解是这样)，那么我们就用线段树实现

做法大家肯定也都清楚,每一轮冒泡排序，对于每一个元素，都会使其逆序对减少一个(如果它还有逆序对的话)。因为每次都将这个元素前面一个比它大的移到了它后面(如果有的话)。

那么我们如果把逆序对个数提出来，视为一个数列，那么K轮操作就相当于把每个元素后移K位，并且元素的值b=max(0,b-k)

那么我们构造出b数列后就可以直接使用线段树找数列上大于K的值的个数以及它们的和就好

构造b数列相当于求每个数前面比它大的数的个数——权值线段树

记录b数列元素个数：因为逆序对个数小于n,对于每个b数列元素b[i]，将b[i]+1的位置+1(b[i]有可能为0，因此+1)——权值线段树

记录b数列元素和:同上，+1变成+b[i]——权值线段树

三棵树建立完成！！！

下面的代码里，t1是构造b数列的线段树，t2是记录b[i]之和的线段树，t3是记录b[i]个数的线段树

关于交换操作，就两种情况

1.V[a]<V[a+1]

显然，交换后原来V[a]的逆序对多出来一个，只不过这时a和a+1已经换位置了，就把原来b[a]从两棵树中删掉，b[a]++,再加入两棵树(因为两棵树中元素储存实际上只和元素的值有关)，交换a和a+1的V和b值

2.V[a]>V[a+1]

同上，不过这次变成原来V[a+1]的逆序对少了一个

具体细节代码中也有一部分注释
```cpp
#include<iostream>
#include<cstdio>
#define int long long int
using namespace std;
int n,m,a1,a2,t1[800001],t2[800001],t3[800001],v[200001],b[200001];
int ls(int x)
{
	return x<<1;
}
int rs(int x)
{
	return x<<1|1;
}
void pushup1(int x)
{
	t1[x]=t1[ls(x)]+t1[rs(x)];
}
void pushup2(int x)
{
	t2[x]=t2[ls(x)]+t2[rs(x)];
}
void pushup3(int x)
{
	t3[x]=t3[ls(x)]+t3[rs(x)];
}
void T1ADD(int x,int l,int r,int p)
{
	if(l==r)
	{
		t1[x]++;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)
		T1ADD(ls(x),l,mid,p);
	else
		T1ADD(rs(x),mid+1,r,p);
	pushup1(x);
} 
int Query1(int x,int l,int r,int nl,int nr)
{
	if(nl<=l&&nr>=r)
	{
		return t1[x];
	}
	int mid=(l+r)>>1,res=0;
	if(nl<=mid)
		res+=Query1(ls(x),l,mid,nl,nr);
	if(nr>mid)
	{
		res+=Query1(rs(x),mid+1,r,nl,nr);
	}
	return res;
}
void Change2(int x,int l,int r,int p,int Val)
{
	if(l==r)
	{
		t2[x]+=Val;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)
		Change2(ls(x),l,mid,p,Val);
	if(p>mid)
	{
		Change2(rs(x),mid+1,r,p,Val);
	}
	pushup2(x);
}
int Query2(int x,int l,int r,int nl,int nr)
{
	if(nl<=l&&nr>=r)
	{
		return t2[x]; 
	}
	int mid=(l+r)>>1,res=0;
	if(nl<=mid)
	{
		res+=Query2(ls(x),l,mid,nl,nr);
	}
	if(nr>mid)
	{
		res+=Query2(rs(x),mid+1,r,nl,nr);
	}
	return res;
}
void Change3(int x,int l,int r,int p,int Val)
{
	if(l==r)
	{
		t3[x]+=Val;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)
		Change3(ls(x),l,mid,p,Val);
	if(p>mid)
	{
		Change3(rs(x),mid+1,r,p,Val);
	}
	pushup3(x);
}
int Query3(int x,int l,int r,int nl,int nr)
{
	if(nl<=l&&nr>=r)
	{
		return t3[x]; 
	}
	int mid=(l+r)>>1,res=0;
	if(nl<=mid)
	{
		res+=Query3(ls(x),l,mid,nl,nr);
	}
	if(nr>mid)
	{
		res+=Query3(rs(x),mid+1,r,nl,nr);
	}
	return res;
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&v[i]);
		b[i]=(i-1)-Query1(1,1,n,1,v[i]);//查询出已出现比v[i]小的数个数 
		T1ADD(1,1,n,v[i]); 
		Change2(1,1,n,b[i]+1,b[i]);//避开b[i]为0的情况 
		Change3(1,1,n,b[i]+1,1);//避开b[i]为0的情况 
	}
	/*
	主体思想为构造两颗权值线段树
	t2:保存权值在l到r之间的b[i]的和
	t3:保存权值在l到r之间的b[i]的个数 
	*/
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&a1,&a2);
		if(a1==1)
		{
			if(v[a2]>v[a2+1])
			{
				Change2(1,1,n,b[a2+1]+1,-b[a2+1]);
				Change3(1,1,n,b[a2+1]+1,-1);
				b[a2+1]--;
				Change2(1,1,n,b[a2+1]+1,b[a2+1]);
				Change3(1,1,n,b[a2+1]+1,1);
				swap(b[a2],b[a2+1]);
				swap(v[a2],v[a2+1]); 
			}
			else
			{
				Change2(1,1,n,b[a2]+1,-b[a2]);
				Change3(1,1,n,b[a2]+1,-1);
				b[a2]++;
				Change2(1,1,n,b[a2]+1,b[a2]);
				Change3(1,1,n,b[a2]+1,1);
				swap(b[a2],b[a2+1]);
				swap(v[a2],v[a2+1]);
			}
		}
		else
		{
			if(a2>=n)
			{
				printf("%d\n",0);
			}
			else
			{
				printf("%lld\n",Query2(1,1,n,a2+1,n)-a2*(Query3(1,1,n,a2+1,n))); 
			} 
		}
	} 
	return 0;
}
```


---

## 作者：te5555 (赞：3)

# NOI Online T2 冒泡排序题解&反思
## 题目描述
给定一个 $1 ∼ n$ 的排列 $p_i$，接下来有 $m$ 次操作，操作共两种：
1. 交换操作：给定 $x$，将当前排列中的第 $x$ 个数与第 $x+1$ 个数交换位置。
2. 询问操作：给定 $k$，请你求出当前排列经过 $k$ 轮冒泡排序后的逆序对个数。
对一个长度为 $n$ 的排列 $p_i$ 进行一轮冒泡排序的伪代码如下：(略)
## Solution
   作为一个蒟蒻,我从自己思路上分析一下这道好题
首先暴力还是比较好想的,按题意模拟即可.

### 一:$\mathcal{O} (n\log_n)$求逆序对
有归并排序和树状数组两种方法,因为后面要用树状数组所以选ta

更主要的原因是可以求出$i$位置前大于此数的数的个数

我们记初始序列为$p[i]$,每次向BIT(树状数组)中$p[i]$的位置上加一

(具体可以看逆序对的题解,大佬们绝对比我写的好)

code:
```	cpp
 for (register int i = 1; i <= n; i++)
    {
        add(p[i], 1);
        ni[i] = i - query(p[i]);
        cnt += ni[i];
        ++d[ni[i]];
    }
  ```
  
    其中$d[i]$是桶,统计$ni[i]$个数,$ni[i]$表示$i$前比它大的数的个数
   ### 二:维护每次交换后的$d[i]$
	用树状数组维护
    
    其实一开始蒟蒻维护了ni[i],也错算了复杂度(爆零了)
    
    为什么不能维护ni[i]我们在第三块讲
$d[i]$也表示答案中第k轮后还能成为答案的数

开始直接插入$cnt$,也就是总逆序对数

然后在$d[i+2]$上插入比当前的轮数小的$ni[i]$**的个数**的相反数,也就是减去这个个数

这样就减去了$k$轮后已经变成$0$的$ni[i]$

确定了初始的BIT,我们就可以实现操作1了

分类讨论$p[i]$与$p[i+1]$的大小

若是$p[i]$大于$p[i+1]$,则交换后比$i+1$位置上的数大的数要减少,同时逆序对数也会减少

反之同理

### 三:维护答案
规律:每进行一次冒泡排序,ni[i]--(前提是大于0)且左移

证明参考二中的维护操作一

至于为什么不能维护$ni[i]$,则是ni[i]不能快速的求出小于k的ni[i],会T

由于k可能很大,要分类讨论k大于n的情况

答案即为query(k+1)
## 总结

个人认为难点有二:(可能是我太蒻)

一是找出规律

二是用树状数组维护答案

## 代码(参考了一些题解)
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 200010
#define ll long long
inline ll read()
{
    ll res = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        res = res * 10 + ch - 48, ch = getchar();
    return res * f;
}
ll n, m, p[maxn], ans[maxn << 2], cnt, ni[maxn], d[maxn], tmp;
inline void swap(ll &a, ll &b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}
inline int lowbit(int x)
{
    return x & (-x);
}
inline void add(int x, ll k)
{
    while (x <= n)
    {
        ans[x] += k;
        x += lowbit(x);
    }
}
inline ll query(ll x)
{
    ll res = 0;
    while (x)
    {
        res += ans[x];
        x -= lowbit(x);
    }
    return res;
}
inline ll max(ll a, ll b)
{
    return a > b ? a : b;
}
inline ll min(ll a, ll b)
{
    return a < b ? a : b;
}
int main()
{
    n = read();
    m = read();
    for (register int i = 1; i <= n; i++)
    {
        p[i] = read();
    }
    for (register int i = 1; i <= n; i++)
    {
        add(p[i], 1);
        ni[i] = i - query(p[i]);
        cnt += ni[i];
        ++d[ni[i]];
    }
    memset(ans, 0, sizeof ans); //重复利用ans
    add(1, cnt);                //一轮后所有的逆序对都可以成为答案(减去k)
    for (register int i = 0; i < n; i++)
    {
        for (register int j = 1; j <= n; j++)
            cout << ans[j] << ' ';
        cout << endl;
        tmp += d[i];
        add(i + 2, tmp - n); //i+2是一个映射,因为是从0开始,加上
    }
    while (m--)
    {
        int t = read();
        ll c = read();
        c = min(n - 1, c);
        if (t == 1)
        {
            if (p[c] < p[c + 1])
            {
                swap(p[c], p[c + 1]);
                swap(ni[c], ni[c + 1]);
                add(1, 1);
                add(ni[c + 1] + 2, -1);
                ni[c + 1]++;
            }
            else
            {
                swap(p[c], p[c + 1]);
                swap(ni[c], ni[c + 1]);
                add(1, -1);
                ni[c]--;
                add(ni[c] + 2, 1);
            }
        }
        if (t == 2)
        {
            cout << query(c + 1) << endl;
        }
    }
    return 0;
}

```
**限于笔者水平,难免出现纰漏,欢迎各位大佬指出**

---

## 作者：BFqwq (赞：3)

## T2
首先预处理出每个点前面有多少比它大的点。

显然可以推出，如果前面有 $b_i$ 个比 $i$ 大的点，则前 $b_i$ 轮中它将不会向后移，因为与它相比的点一定大于它。

而若不会变化，则代表会被前面的某个大于它点在冒泡的过程中经过，因此会使得逆序对 $-1$。

然后开一棵线段树维护一下，维护两个信息，一个是在一段值域范围内有多少个点，一个是这些点的贡献（个数乘以值）。

然后查询的时候计算一下即可。用当前的逆序对个数，减去变化中会减少的逆序对个数。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std; 
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(long long x,char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=200005;
struct seg{
	int v;
	long long sum;
}t[maxn<<3][2];
void change(int o,int l,int r,int q,int v,int wh){
	if(l==r){
		t[o][wh].v+=v;
		t[o][wh].sum+=l*v;
		return ;
	}
	int mid=l+r>>1;
	if(q<=mid) change(o<<1,l,mid,q,v,wh);
	else change(o<<1|1,mid+1,r,q,v,wh);
	t[o][wh].v=t[o<<1][wh].v+t[o<<1|1][wh].v;
	t[o][wh].sum=t[o<<1][wh].sum+t[o<<1|1][wh].sum;
}
int query1(int o,int l,int r,int ql,int qr,int wh){
	if(ql<=l&&r<=qr){
		return t[o][wh].v;
	}
	int mid=l+r>>1,res=0;
	if(ql<=mid) res+=query1(o<<1,l,mid,ql,qr,wh);
	if(qr>mid) res+=query1(o<<1|1,mid+1,r,ql,qr,wh);
	return res;
}
long long query2(int o,int l,int r,int ql,int qr,int wh){
	if(ql<=l&&r<=qr){
		return t[o][wh].sum;
	}
	int mid=l+r>>1;
	long long res=0;
	if(ql<=mid) res+=query2(o<<1,l,mid,ql,qr,wh);
	if(qr>mid) res+=query2(o<<1|1,mid+1,r,ql,qr,wh);
	return res;
}
int a[maxn],b[maxn],n,m;
long long ni,ans;
signed main(){
//	freopen("bubble.in","r",stdin);
//	freopen("bubble.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=query1(1,1,n,a[i]+1,n,0);
		ni+=b[i];
		change(1,1,n,a[i],1,0);
		change(1,0,n,b[i],1,1);
	}
	for(int i=1;i<=m;i++){
		int opt=read(),x=read();
		if(opt==1){
			if(a[x]>a[x+1]){
				change(1,0,n,b[x+1],-1,1);
				b[x+1]--;
				ni--;
				change(1,0,n,b[x+1],1,1);
				swap(a[x],a[x+1]);
				swap(b[x],b[x+1]);
			}
			else{
				change(1,0,n,b[x],-1,1);
				b[x]++;
				ni++;
				change(1,0,n,b[x],1,1);
				swap(a[x],a[x+1]);
				swap(b[x],b[x+1]);
			}
		}
		else{
			if(x==0){
				print(ni);
				continue;
			}
			ans=ni;
			ans+=(long long)x*query1(1,0,n,0,x,1);
			ans-=n*x;
			ans-=query2(1,0,n,0,x,1);
			print(ans);
		}
	}
	return 0;
}
```
然而考场上写出来了但没调完，期望得分 $0$。

---

## 作者：NoGoshPlease (赞：2)

这是一道 ~~较难~~ 很难 的题目，题中要求冒泡排序后逆序对的个数。

定义$b_i$为前$(i-1)$个数中比$i$大的数的个数

# **先求出$b_i$：**

定义$tr1$存输入，也是单点修改区间查询

求逆序对的经典操作：


```cpp
for(int i=1;i<=n;i++)
{
	scanf("%lld",&a[i]);
	update(tr1,a[i],1);
	long long s=(long long)i-ask(tr1,a[i]);
	tr2[i]=s;
}
```
# **下面主攻排序后逆序对个数的问题：**

明显可知，经过$k$轮冒泡排序后，每个$>k$的$b_i$都会减$k$。不到的清零。(因为这个数每轮只能与前面交换最多$1$次)

例子：$7,2,6,4,1,10,9,8,3,5$

$k=3$时有$1+3+2=6$个逆序对


我们怎样确定不同$k$对应的值呢？

别急，定两个单点求和，区间修改的树状数组(为了避免坐标为$0$的$RE$，地址都要加$1$)

$tr3_{i+1}$:$b$数组中值为$i$的数的个数，

$tr4_{i+1}$:$b$数组中值为$i$的所有数的和，

**怎么生成？？**
```cpp
update(tr3,b[i]+1,1);
```
```cpp
update(tr4,b[i]+1,b[i]);
```
**怎么求？？**
```cpp
(ask(tr4,N-1)-ask(tr4,k))-k*(ask(tr3,N-1)-ask(tr3,k));
```

解释：每个$>k$的数都要$-k$(其他不计算在内),那就算出它们的和，再减去(个数乘$k$ )即可，用树状数组，$O(logn)$。

# **还有一个问题，交换怎么办？**

显然：$a$数组(存输入数据)和$b$数组要先换(现在不影响$tr3$和$tr4$，但之后影响)

后面分类讨论,注意现在已换完：

左大于右：$b_c--;$

右大于左：$b_{c+1}++;$

然后改动$tr3$和$tr4$。

**题目就~~愉快地~~解决了**

下面是我的代码：

```cpp
#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
long long n,m,a[N],tr1[N],tr2[N],tr3[N],tr4[N],tr5[N],ni;//tr1:数字桶，tr2[i]:以i为截止的逆序对个数
int lowbit(int x){return x&-x;}
void update(long long tr[],long long x,long long y)
{
	for(;x<=N;x+=lowbit(x)) tr[x]+=y;
}
long long ask(long long tr[],long long x)
{
	if(x==0) return 0;
	long long res=0;
	for(;x;x-=lowbit(x)) res+=tr[x];
	return res;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		update(tr1,a[i],1);
		long long s=(long long)i-ask(tr1,a[i]);
		tr2[i]=s;
		ni+=s;
		if(tr2[i])
			update(tr3,tr2[i]+1,1),
			update(tr4,tr2[i]+1,tr2[i]);
	}
	for(int i=1;i<=m;i++)
	{
			/*for(int j=1;j<=n;j++)
			{
				printf("%d ",tr2[j]);
			}
			printf("\n");
			for(int j=1;j<=n;j++)
			{
				printf("%d ",ask(tr3,j+1)-ask(tr3,j));
			}
			printf("\n");
			for(int j=1;j<=n;j++)
			{
				printf("%d ",ask(tr4,j+1)-ask(tr4,j));
			}
			printf("\n");
			for(int j=1;j<=n;j++)
			{
				printf("%d ",(ask(tr4,N-1)-ask(tr4,j))-j*(ask(tr3,N-1)-ask(tr3,j)));
			}
			printf("\n\n\n");*/
		long long t,c;
		scanf("%lld%lld",&t,&c);
		if(t==1)
		{
			swap(a[c],a[c+1]);
			swap(tr2[c],tr2[c+1]);
			if(a[c+1]>a[c])
			{
				tr2[c]--;
				update(tr3,tr2[c]+2,-1);
				update(tr3,tr2[c]+1,1);
				update(tr4,tr2[c]+2,-tr2[c]-1);
				update(tr4,tr2[c]+1,tr2[c]);
				ni--;
			}
			else if(a[c+1]<a[c])
			{
				tr2[c+1]++;
				update(tr3,tr2[c+1],-1);
				update(tr3,tr2[c+1]+1,1);
				update(tr4,tr2[c+1],-tr2[c+1]+1);
				update(tr4,tr2[c+1]+1,tr2[c+1]);
				ni++;
			}
		}
		if(t==2)
		{
			if(c>=n) printf("0\n");
			if(c==0) printf("%lld\n",ni);
			else printf("%lld\n",((ask(tr4,N-1)-ask(tr4,c))-c*(ask(tr3,N-1)-ask(tr3,c))));
		}
	}
	return 0;
}
```


---

## 作者：YellowBean_Elsa (赞：2)

说道逆序对，基本上不是归并就是树状数组。

然后我们来看冒泡排序每一轮的特点。

发现对于每个数，如果它前面有更大的数，那么每一轮就会有一个被换到他后面。

换言之，记 $uper_i$ 表示第 i 个数前面有几个数比他大，则每一轮冒泡之后， 有：
$$uper_i = \max(uper_i-1,0)$$
这玩意用树状数组维护很方便！

用差分，前缀记录第 i 轮后剩下的逆序对数，那么我们要算出在每一轮会有多少个数的 $uper$ 会清零，也就是要用 $rec_i$ 记录 $uper$ 为 i 的数有几个。

然后对于每个 i，查询就直接树状数组前缀求和，修改就 swap 再改变逆序对总数和差分的位置即可。

```cpp
//coder: Feliks*GM-YB
#include<bits/stdc++.h>
#define fu(i,a,b) for(register int i = a, I = (b) + 1; i < I; ++i)
#define fd(i,a,b) for(register int i = a, I = (b) - 1; i > I; --i)
typedef long long ll;
using namespace std;
const int N=2e5+10;
inline void Swap(int &x,int &y){
	x^=y,y^=x,x^=y;
}template <class T> inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(!isdigit(ch))f=ch=='-'?-1:1,ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    x*=f;
}int n,m,p[N],op,x;
ll c[N],ans;
inline int lowbit(int x){
	return x&-x;
}inline void add(int x,ll k){
	for(;x<=n;x+=lowbit(x))c[x]+=k;
}inline ll qry(int x){
	ll res=0;
	for(;x;x-=lowbit(x))res+=c[x];
	return res;
}int uper[N],rec[N];
//前面比 i大的个数 & 前面有 i个比她大的数的个数 
int main(){
	read(n),read(m);
	//先跑一遍树状数组逆序对板子
	fu(i,1,n){
		read(p[i]);
		ans+=(uper[i]=i-qry(p[i])-1);
		add(p[i],1);
		rec[uper[i]]++;
		//仔细思考 rec 的定义 
	}memset(c,0,sizeof(c));
	add(1,ans);ans=n;
	fu(i,0,n-1){
		ans-=rec[i];//还有几个数在第i+1轮会减少逆序对 (uper)
		add(i+2,-ans);
		//树状数组的一些下标毛病
		//i+1轮的答案存在了 i+2中，千万注意！！！ 
	}while(m--){
		read(op),read(x);
		if(x>n)x=n;
		if(op==1){
			if(p[x]<p[x+1]){
				swap(p[x],p[x+1]);
				swap(uper[x],uper[x+1]); 
				add(1,1);//逆序对总个数++ 
				add((++uper[x+1])+1,-1);//改变差分的位置和uper 
			}else{//与上相反 
				swap(p[x],p[x+1]);
				swap(uper[x],uper[x+1]);
				add(1,-1);
				add(1+(uper[x]--),1);
			}
		}else printf("%lld\n",qry(x+1));
	}
	return 0;
}
```


---

## 作者：gSE2xWE (赞：2)

# 题目

[传送门](https://www.luogu.com.cn/problem/P6186)

# 思路

不好想到

定义t数组，其中$t_i$表示在$1\le j<i$中有多少个大于$a_i$的$a_j$

那么逆序对就是$\sum_{i=1}^n{t_i}$

考虑一操作

交换$a_i$和$a_{i+1}$

因为只是交换这两个数

所以除了这两个数之外的$t_j$不会发生任何变化

而维护$t_i$和$t_{i+1}$只需要考虑$a_i$和$a_{i+1}$的大小就可以了

再考虑二操作

注意到一个性质

一轮冒泡排序会让$t_i=max(t_i-1,0)$

其理由是在任何一轮的冒泡排序之中，我们我们最多只会让$1\le j <i$的一个$a_j$跑到$a_i$的右边

而如果要让$a_j$跑到$a_i$右边，那么一定有$a_j>a_i$，所以此时$t_i$会减1

那k轮呢？

应当有$t_i=max(t_i-k,0)$

看上去有一个max很难维护

但其实用权值线段树就好了

最后的答案就是询问值域$k+1\rightarrow n$的和减去k乘上值域$k+1\rightarrow n$有多少个$t_i$

 总时间复杂度为$O(n*log_n)$

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
struct node
{
    int l;
    int r;
    int tot;
    long long s;
}tre[1000005];
int n,m;
int a[200005];
int b[200005];
long long bit[200005];
int lowbit(int x)
{
    return x&(-x);
}
void update(int x,int val)
{
    for(int i=x;i<=n;i+=lowbit(i))
        bit[i]+=val;
}
long long solve_s(int x)
{
    long long ret=0;
    for(int i=x;i>0;i-=lowbit(i))
        ret+=bit[i];
    return ret;
}   
void build(int l,int r,int k)
{
    //cout<<k<<'\n';
    tre[k].l=l;
    tre[k].r=r;
    tre[k].s=0;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    build(l,mid,k<<1);
    build(mid+1,r,k<<1|1);
}
void add(int a,int f,int k)
{
    if(tre[k].l>a||a>tre[k].r)
        return;
    if(tre[k].l==tre[k].r)
    {
        tre[k].tot+=f;
        tre[k].s=tre[k].s+tre[k].l*f;
        return;
    }
    add(a,f,k<<1);
    add(a,f,k<<1|1);
    tre[k].tot=tre[k<<1].tot+tre[k<<1|1].tot;
    tre[k].s=tre[k<<1].s+tre[k<<1|1].s;
}
long long ask(int l,int r,int k)
{
    if(l>r)
        return 0;
    if(l>tre[k].r||tre[k].l>r)
        return 0;
    if(l<=tre[k].l&&tre[k].r<=r)    
        return tre[k].s-1ll*tre[k].tot*(l-1);
    return ask(l,r,k<<1)+ask(l,r,k<<1|1);
}
int main()
{
    //freopen("bubble.in","r",stdin);
    //freopen("bubble.out","w",stdout); 
    scanf("%d %d",&n,&m);
    build(0,n,1);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        b[i]=i-1-solve_s(a[i]);
        update(a[i],1);
        add(b[i],1,1);
    }
    for(int i=1;i<=m;i++)
    {
        int t;
        long long c;
        scanf("%d %lld",&t,&c);
        if(t==1)
        {
            if(a[c]>a[c+1])
            {
                add(b[c],-1,1);
                add(b[c+1],-1,1);
                int x=b[c];
                int y=b[c+1];
                b[c]=y-1;
                b[c+1]=x;
                add(b[c],1,1);
                add(b[c+1],1,1);
                swap(a[c],a[c+1]);
            }
            else if(a[c]<a[c+1])
            {
                add(b[c],-1,1);
                add(b[c+1],-1,1);
                int x=b[c];
                int y=b[c+1];
                b[c]=y;
                b[c+1]=x+1;
                add(b[c],1,1);
                add(b[c+1],1,1);
                swap(a[c],a[c+1]);
            }
        }
        else
        {
            printf("%lld\n",ask(c+1,n,1));
        }
    }
    return 0;
}


```

---

## 作者：warzone (赞：2)

这一题主要考的是对于冒泡排序中逆序对的认识

首先可以得到如下结论：

1. 一次修改只会影响一个逆序对(即 $p_{k}$ 和 $p_{k+1}$ ),对于其他逆序对不会有任何影响		

2. 在一轮冒泡排序中，对于每个数 $p_i$，相当于消去  
   “以 $p_i$ 为右端点的逆序对中，左端点离 $p_i$ 最近的逆序对”。  
   (如果没有则不会消去)

   因为在一轮冒泡中，对于每次交换，右边的数最多只会交换一次，  
   左边的数可能会继续向右交换下去。

于是流程大致如下：

1. 用权值线段树求出以每一个 $p_i$ 为右端点的逆序对数，存在数组 $sum$ 中。	

2. 对于每一次修改,更新这两个数的逆序对数(注意右端点)。

3. 对于每一次求值，就是求解 $\sum\limits^n_{i=1} sum[i]>k? sum[i]-k:0$ 。  

对于流程3，这里的计算是 $\Theta(n)$ 的，需要优化到 $\Theta(\log n)$ 级别

1. 开一个桶 $pocket$，将 $sum$ 中的数存入桶中。我们可以 $\Theta(1)$ 更新桶。  

2. 设答案为 $f(k)$，则 $f(k)=\sum\limits^n_{i=k}pocket[i]\times(i-k)$，  
	不难发现 $f(k)=f(k+1)+(\sum\limits^n_{i=k}pocket[i])$，相当于做两次前缀和

3. 这时 $pocket[i]$ 给 $f(0)\sim f(k)$ 的贡献是一段**等差数列**，  
	此时已经可以用线段树 $\Theta(\log n)$ 解决了，模板如下  
    [【P1438 无聊的数列】](https://www.luogu.com.cn/problem/P1438) (orz yyb)
	
代码 (2.48s,26,63MB)

```cpp
#include<stdio.h>
#include<string.h>
typedef unsigned char byte;
typedef unsigned short hword;
typedef unsigned int word;
typedef unsigned long long ull;
typedef long long ll;
//注意最后开long long
struct READ{//快读，同cin
	//inline READ(){
	//	freopen("bubble.in","r",stdin);
	//	freopen("bubble.out","w",stdout);
	//}
	template<typename type>
    inline READ& operator >>(type & num){
        register char c=getchar(),w=1;
        while('0'>c||c>'9'){
            if(c==EOF) return *this;
            w=c=='-'? -1:1;
            c=getchar();
        }
        num=0;
        while('0'<=c&&c<='9'){
            num=(num*10)+(c-'0');
            c=getchar();
        }
        return num*=w,*this;
    }
}cin;
class WRITE{//快写，同cout
	private:
		char out[1<<20],*top;
	public:
		inline WRITE(){top=out;}
		inline ~WRITE(){
			if(top!=out) fwrite(out,1,top-out,stdout);
		}
		inline WRITE& operator <<(char c){
			*top=c,top++;
			if(top==out+(1<<20))
				fwrite(top=out,1,1<<20,stdout);
			return *this;
		}
		inline WRITE& operator <<(const char c[]){
			for(register word i=0;c[i]!='\0';i++) *this<<c[i];
			return *this;
		}
		inline WRITE& operator <<(ull num){
			if(num==0) return *this;
			return *this<<num/10<<(char)(num%10+'0');
		}
		template<typename type>
		inline WRITE& operator <<(type num){
			if(num==0) return *this<<'0';
			if(num>0) return *this<<(ull)(num);
			return *this<<'-'<<(ull)(-num);
		}
}cout;
byte pool[1<<25],*top=pool+(1<<25);
inline void* operator new(size_t size){
    return top-=size;
}//重载new，方便线段树使用
struct point{//求逆序对的权值线段树
	point *l,*r;
	word from,to;
	long long h;
	inline point(word f,word t){
		from=f,to=t,h=0;
		if(f!=t){
            l=new point(f,(f+t)>>1);
			r=new point(l->to+1,t);
        }	
	}
    inline void is(word id,long long num){//单点修改
        if(from==to){h=num;return;}
        if(id<=l->to) l->is(id,num);
        else r->is(id,num);
        h=l->h+r->h;
    }
	inline long long sum(word f,word t){//区间求和
		if(f==from&&t==to) return h;
		if(t<=l->to) return l->sum(f,t);
		if(r->from<=f) return r->sum(f,t);
		return l->sum(f,l->to)+r->sum(r->from,t);
	}
}*tree;
struct anspoint{//计算答案的线段树
	anspoint *l,*r;
	int from,to;
	ll h,firsttag,plustag;
	inline anspoint(int f,int t){
		from=f,to=t,h=firsttag=plustag=0;
		if(f!=t){
            l=new anspoint(f,(f+t)>>1);
		    r=new anspoint(l->to+1,t);
        }
	}
	inline void plus(int f,int t,ll first,ll p){//加上等差数列
		if(f==from&&t==to){
			h+=(p*(t-f>>1)+first)*(t-f+1);
			if(f!=t) firsttag+=first,plustag+=p;
			return;
		}
		if(t<=l->to) l->plus(f,t,first,p);
		else if(r->from<=f) r->plus(f,t,first,p);
		else{
			l->plus(f,l->to,first,p);
			r->plus(r->from,t,(r->from-f)*p+first,p);
		}
	}
	inline ll sum(int id){//区间求和
		if(from==to) return h;
		else{
		    if(firsttag!=0||plustag!=0){
			    l->plus(l->from,l->to,firsttag,plustag);
			    r->plus(r->from,r->to,plustag*(r->from-l->from)+firsttag,plustag);
	    		firsttag=plustag=0;
		    }
		    if(id<=l->to) return l->sum(id);
		    return r->sum(id);
		}
	}
}*anstree;
word n,m;
ll num[200010],pocket[200010],sum[200010];
int main(){
    cin>>n>>m;
    tree=new point(1,n);
    for(register word i=1;i<=n;i++){
        cin>>num[i];
        sum[i]=tree->sum(num[i],n);//计算对于每个右端点的逆序对数
        pocket[sum[i]]++;//放入桶中
		tree->is(num[i],1);//将其作为左端点放入线段树
    }
	top=pool+(1<<25);//重用旧的内存
    anstree=new anspoint(0,n);
    for(register int i=n;i>=0;i--)//计算桶中的数对答案的贡献
        anstree->plus(0,i,pocket[i]*i,-pocket[i]);
    for(int t,k,l,r;m>0;m--){
        cin>>t>>k;
        if(t==1){
            l=sum[k],r=sum[k+1];
            if(num[k]<num[k+1]){//修改逆序对数和贡献
                anstree->plus(0,l,-l,1);
                l++,anstree->plus(0,l,l,-1);
            }
            else{
                anstree->plus(0,r,-r,1);
                r--,anstree->plus(0,r,r,-1);
            }
			sum[k]=r,sum[k+1]=l;
            t=num[k];
            num[k]=num[k+1];
            num[k+1]=t;

        }
        else if(k>n) cout<<'0'<<'\n';//注意特判
        else cout<<anstree->sum(k)<<'\n';
    }
    return 0;
}
```

---

## 作者：谁是鸽王 (赞：2)

## 【题解】NOIO2020 冒泡排序(树状数组)

考虑在k次冒泡后的排列中的一个逆序对$i<j,a_i>a_j$。

因为这个$a_i$的存在，意味着$a_j$没有被往右边交换过(否则不会存在一个$a_i>a_j$)。

对于每个没有被交换到右边的数，他前面总共有$k$个比他大的数被交换走了。记$ans[i]$表示原序列$i$位置和之前的数构成的逆序对个数，那么$k$次交换后，对答案的贡献是$ans[i]-k$。

那么答案就是
$$
\sum \max(0,\text{ans}[i]-k)
$$
对$ans[i]$的值域开两个树状数组，每次取所有大于$k$的所有$ans$之和，再减去$ans[i]>k$的个数乘以$k$就是答案。两个操作都是取一段后缀，直接树状数组即可。

至于交换操作，由于只影响了两个$ans$，所以直接模拟一遍就行。

复杂度$O(n\log n)$。注意$k$要对$n-1$取min。

```cpp
//@winlere
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;  typedef long long ll;  
inline int qr(){
	int ret=0,f=0,c=getchar();
	while(!isdigit(c)) f|=c==45,c=getchar();
	while( isdigit(c)) ret=ret*10+c-48,c=getchar();
	return f?-ret:ret;
}
const int maxn=2e5+5;
int data[maxn],n,m;
ll seg1[maxn],seg2[maxn];
void add(ll*seg,int pos,ll val){
	++pos;
	for(int t=pos;t<=n+1;t+=t&-t)
		seg[t]+=val;
}
ll que(ll*seg,int pos){
	++pos;
	ll ret=0;
	for(int t=pos;t>0;t-=t&-t)
		ret+=seg[t];
	return ret;
}
ll que(ll*seg,int l,int r){return que(seg,r)-que(seg,l-1);}
int ans[maxn];
void del(int pos){add(seg1,ans[pos],-ans[pos]); add(seg2,ans[pos],-1);}
void add(int pos){add(seg1,ans[pos],ans[pos]); add(seg2,ans[pos],1);}

int main(){
	n=qr(); m=qr();
	for(int t=1;t<=n;++t)
		data[t]=qr(),ans[t]=t-1-que(seg1,data[t]),add(seg1,data[t],1);
	memset(seg1,0,sizeof seg1);
	for(int t=1;t<=n;++t) add(t);
	for(int t=1;t<=m;++t){
		int op=qr(),x=min(qr(),n);
		if(op==1){
			del(x),del(x+1);
			ans[x+1]-=data[x]>data[x+1];
			swap(data[x],data[x+1]); swap(ans[x],ans[x+1]);
			ans[x+1]+=data[x]>data[x+1];
			add(x),add(x+1);
		}else{
			ll ret=que(seg1,x,n)-que(seg2,x,n)*x;
			printf("%lld\n",ret);
		}
	}
	return 0;
}

```





---

## 作者：RyexAwl (赞：1)

我们考虑一轮冒泡排序对逆序对个数的影响:
每轮冒泡排序进行的操作即从左到右依次交换元素相邻的逆序对。 ~~我们发现其对整个序列的逆序对个数的影响十分抽象。~~

我们来分析一下相邻的逆序对和非相邻逆序对的关系：
我们考虑固定右端点的逆序对。 假定当前右端点为$k$，在其前面一共有$p$个位置与之构成逆序对，$(pos[1],k),(pos[2],k),(pos[3],k)...(pos[p],k)$。我们发现$\forall 1\le i < p,$一定存在逆序对$(pos[i],pos[i+1])$,$\forall p + 1\le j < k$一定存在逆序对$(p,j)$。

那么每轮冒泡排序接替的给每个左端点$\text{ntr}$，直到交换到右端点前面与右端点交换，那么其可以看成给其右端点构成的逆序对减一,并且每轮冒泡排序一定不会增加逆序对。


那么我们目前的目标就很明确了

总的逆序对个数$cnt=\sum_{r=2}^nct[r]$，其中$ct[r]$表示以$r$为右端点的逆序对个数。

根据加法交换律$ct=\sum_kcv[k]\times k$其中$cv[k]$表示以其为逆序对右端点逆序对个数恰好为$k$的位置个数。

那么
$$
ans[k]=\sum_{i=k+1}^{n-1}cv[i]\times i
$$

可以直接权值线段树维护，对于修改直接线段树上修改即可。


```cpp
#include <iostream>
#include <cstring>

namespace wxy{
const int N = 2e5 + 5;
#define int long long
struct node{int l,r,cnt,sum;}t[N << 2];
int a[N],w[N],c[N],n,m;
inline void pushup(int u){
    t[u].cnt = t[u << 1].cnt + t[u << 1 | 1].cnt;
    t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
}
inline void build(int u,int l,int r){
    t[u].l = l; t[u].r = r;
    if (l == r){t[u].cnt = w[l]; t[u].sum = t[u].cnt * l; return;}
    int mid = l + r >> 1;
    build(u << 1,l,mid);
    build(u << 1 | 1,mid + 1,r);
    pushup(u);
}
inline void plus(int u,int x,int v){
    if (t[u].l == x && t[u].r == x){
        t[u].cnt += v;
        t[u].sum = t[u].cnt * t[u].l;
        return;
    }
    int mid = t[u].l + t[u].r >> 1;
    if (x <= mid) plus(u << 1,x,v);
    if (x > mid) plus(u << 1 | 1,x,v);
    pushup(u);
}
inline int qcnt(int u,int l,int r){
    if (t[u].l == l && t[u].r == r) return t[u].cnt;
    int mid = t[u].l + t[u].r >> 1;
    if (r <= mid) return qcnt(u << 1,l,r);
    else if (l > mid) return qcnt(u << 1 | 1,l,r);
    else return qcnt(u << 1,l,mid) + qcnt(u << 1 | 1,mid + 1,r);
}
inline int qsum(int u,int l,int r){
    if (t[u].l == l && t[u].r == r) return t[u].sum;
    int mid = t[u].l + t[u].r >> 1;
    if (r <= mid) return qsum(u << 1,l,r);
    else if (l > mid) return qsum(u << 1 | 1,l,r);
    else return qsum(u << 1,l,mid) + qsum(u << 1 | 1,mid + 1,r);
}
inline void main(){
    std::cin >> n >> m;;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    memset(w,0,sizeof w);
    build(1,1,n);
    for (int i = 1; i <= n; i++){
        c[i] = qcnt(1,a[i],n);
        plus(1,a[i],1);
    }
    for (int i = 1; i <= n; i++) w[c[i]]++;
    build(1,0,n-1);
    while (m--){
        int op,x; std::cin >> op >> x;
        if (op == 2){
            if (x >= n - 1) std::cout << 0 << std::endl;
            else std::cout << qsum(1,x+1,n-1) - qcnt(1,x+1,n-1) * x << std::endl;
        }else{
            plus(1,c[x],-1);plus(1,c[x+1],-1);
            if (a[x] > a[x+1]) c[x+1]--;
            else c[x]++;
            std::swap(c[x],c[x+1]);
            std::swap(a[x],a[x+1]);
            plus(1,c[x],1);plus(1,c[x+1],1);
        }
    }
}
}signed main(){wxy::main();return 0;}
```


---

## 作者：Tangent233 (赞：1)

### 题目传送门：

[[NOI Online #1 提高组]冒泡排序](https://www.luogu.com.cn/problem/P6186)

### 思路：

假定我们已经知道排列中每个数字逆序对的数量$iv_i$

首先从相对简单的询问操作开始思考：

```
for i = 1 to n-1:
  if p[i] > p[i + 1]:
    swap(p[i], p[i + 1])//单轮冒泡排序伪代码
```
不难想到，它每一轮排序的时候，若$p_i$与$p_{i+1}$构成逆序对，则交换他们。**也就是若$p_{i+1}$有逆序对，则让$iv_{i+1}-1$**。用数学语言形式化的讲就是$iv_i=max(0,iv_i-1)$。

而题目中给定的是$k$轮排序，**因此排完序后对于每一个$i$,$iv_i$ 小于等于 $k$的不会对答案做出任何贡献，而$iv_i$ 大于 $k$ 的做出的贡献则是$iv_i-k$。** 也就是$iv_i=max(0,iv_i-k)$。所以最终结果就是

$ans=\sum_{i=1}^nmax(0,iv_i-k)$

但这样的公式对我们写程序似乎没有任何帮助？让我们变一下形

$ans=\sum_{iv_i>k}iv_i-\sum_{iv_i>k}k$

我们可以把这东西理解成**将所有大于$k$的$iv_i$累加，最后减去大于$k$的$iv_i$的个数乘$k$**

询问操作解决了，接下来思考交换：

题目给定交换$p_x$与$p_{x+1}$，显然有两种情况

1. $p_x$与$p_{x+1}$是逆序对
2. $p_x$与$p_{x+1}$不是逆序对

针对这两种情况我们可以用一个简单的样例去探究规律
[![rrLtQ1.png](https://s3.ax1x.com/2020/12/22/rrLtQ1.png)](https://imgchr.com/i/rrLtQ1)

发现了吗？


**1. 若$p_x$与$p_{x+1}$是逆序对，则$iv_{x+1}-1$并交换$iv_x$与$iv_{x+1}$**

**2. 若$p_x$与$p_{x+1}$不是逆序对，则$iv_{x+1}+1$并交换$iv_x$与$iv_{x+1}$**


那以上两个问题都解决了，我们可以来看代码的实现了

#### 实现：
翻回询问操作最后推导出的式子，显然是有区间求和的部分，再加上逆序对，你能想到什么数据结构呢？显然是**树状数组**（当然线段树也行，但是蒟蒻不会写，而且代码量相比树状数组直线上天）。

于是我们需要以下的数组

- $a$，用来储存原来的排列
- $ivtree$，用来计算逆序对的树状数组
- $ivcnt$，统计每位数字的逆序对个数
- $ivcnttree$，对于每一个$i$,$ivcnttree[i]$为逆序对数从$1$到$i$的数字的贡献和，用树状数组维护
- $cntcnttree$，对于每一个$i$,$cntcnttree[i]$为逆序对从$1$到$i$的数字的个数和，用树状数组维护

对于每个询问操作，我们只需要求得逆序对为$n$到$k$这个区间的贡献和，然后求出这个区间的数字个数$×k$的值，然后相减，即为答案。

对于每个交换操作，按照上文规律模拟即可。

还有一部分小细节，具体看代码和注释吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2*1e5+10;
long long a[maxn],n;
long long ivtree[maxn],ivcnt[maxn],ivcnttree[maxn],cntcnttree[maxn];
//计算数列逆序对所用的树状数组，统计每位数字的逆序对个数，计算逆序对为k的数字的贡献的树状数组，计算逆序对为k的数字的个数的树状数组
inline int lowbit(int x)
{
    return x&(-x);
}
void add(long long *ac,int p,int v)
{
    if(p<=0) return;//防止卡死
    while(p<=n)
    {
        ac[p]+=v;
        p+=lowbit(p);
    }
}
long long q(long long *ac,int p)
{
    if(p<=0) return 0;//防止卡死
    long long ans=0;
    while(p)
    {
        ans+=ac[p];
        p-=lowbit(p);
    }
    return ans;
}//树状数组基本操作
void qswap(int x)
{
    int x1=x,x2=x+1;
    if(a[x1]>a[x2])
    {
        add(ivcnttree,ivcnt[x2],-ivcnt[x2]);
        add(cntcnttree,ivcnt[x2],-1);//先把原来的值给删除
        ivcnt[x2]--;
        add(ivcnttree,ivcnt[x2],ivcnt[x2]);
        add(cntcnttree,ivcnt[x2],1);//然后更新新的值
        swap(ivcnt[x1],ivcnt[x2]);
    }
    else
    {
        add(ivcnttree,ivcnt[x1],-ivcnt[x1]);
        add(cntcnttree,ivcnt[x1],-1);
        ivcnt[x1]++;
        add(ivcnttree,ivcnt[x1],ivcnt[x1]);
        add(cntcnttree,ivcnt[x1],1);
        swap(ivcnt[x1],ivcnt[x2]);//和上面大致相似
    }
    swap(a[x1],a[x2]); 
}
int main()
{
    int m;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    long long total=-1;
    for(int i=1;i<=n;i++)
    {
        add(ivtree,a[i],1);
        long long ret=i-q(ivtree,a[i]);//求逆序对
        total=max(ret,total);//求最大的逆序对个数，即冒泡最多可以有多少轮
        ivcnt[i]=ret;
        add(ivcnttree,ret,ret);
        add(cntcnttree,ret,1);//同时对别的数组进行初始化
    }
    int t,c;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&t,&c);
        if(t==1) qswap(c);//cout<<endl;
        else if(c<=0) cout<<q(ivcnttree,n)<<endl;//若一轮冒泡都没有逆序对个数就是原数组逆序对个数
        else if(c>=total) cout<<0<<endl;//若k达到或超过了最多可进行的冒泡轮，则逆序对个数为0
        else
            cout<<max((q(ivcnttree,n)-q(ivcnttree,c))-(q(cntcnttree,n)-q(cntcnttree,c))*c,0ll)<<endl;
    }
}
```
（2kb出头，对我来说写的算多了）

因为每个操作都是$O(log\,n)$级别的，所以这道题复杂度是$O(n\,log\,n+m\,log\,n)$的，能过！

#### 结语：
这是本蒟蒻非常难得的能提交题解的机会，也是第一次提交题解，希望大家有任何看着不舒服的地方都可以告诉我。私信，评论都可以。

---

## 作者：Arghariza (赞：1)

~~找规律~~

假设数列为2 3 1

- 当冒泡排序**0**轮之后，共**2**个逆序对

- 当冒泡排序**1**轮之后，还剩**1**个逆序对

- 当冒泡排序**2**轮之后，**没有逆序对了**

这就非常明显了吧？

也就是说：

### 假设初始逆序对个数为k, 当n轮冒泡排序之后，还剩k - n组逆序对

所以我们只需要求**初始逆序对的个数**即可

求逆序对有几种方法：线段树，归并排序，树状数组

~~感觉树状数组最好写，不接受反驳~~

所以我们就用树状数组，这样维护数组也很方便

- 首先宏定义ll, N：

```
#define ll long long
#define N 200010
```

- 定义一些变量：

```
ll a[N], t[N], n, m, x, y, cnt, ccnt[N], tmp[N];//t表示树状数组
```

- lowbit（没啥好说的）：

```
inline int lowbit(int w) {
    return w & (-w);
}
```

- 然后是query询问（也没啥好说的）：

```
ll query(ll x) {
    ll ans = 0;
    for (ll i = x; i >= 1; i -= lowbit(i)) ans += t[i];
    return ans;
}
```

- 接着就是update：

```
void update(ll x, ll val) {
    for (ll i = x; i <= n; i += lowbit(i)) t[i] += val;
}
```

- 然后就是最后的main函数（注释在代码里面）：

```
int main() {
    cin >> n >> m;//输入
    for (ll i = 1; i <= n; i++) cin >> a[i];//输入
    for (ll i = 1; i <= n; i++) {//初始化树状数组，逆序对
        tmp[i] = i - query(a[i]) - 1;//一个数的逆序对
        cnt += tmp[i];
        ccnt[tmp[i]]++;//+1
        update(a[i], 1);//更新
    }
    memset(t, 0, sizeof(t));//树状数组清空
    update(1, cnt);//update
    cnt = 0;//清零
    for (ll i = 1; i <= n; i++) {
        cnt += ccnt[i - 1];//加逆序对
        update(i + 1, -(n - cnt));//update
    }
    while (m--) {
        cin >> y >> x;//输入
        x = min(x, n - 1);//取最小，否则有可能溢出
        if (y == 2) cout << query(x + 1) << "\n";//查询
        else if (y == 1) {//交换
            if (a[x] < a[x + 1]) {
                swap(a[x], a[x + 1]);//交换
                swap(tmp[x], tmp[x + 1]);//交换
                tmp[x + 1]++;//逆序对++
                update(tmp[x + 1] + 1, -1);//更新
                update(1, 1);//更新
            } else {
                swap(a[x], a[x + 1]);//交换
                swap(tmp[x], tmp[x + 1]);//交换
                update(tmp[x] + 1, 1);//更新
                tmp[x]--;//逆序对
                update(1, -1);//更新
            }
        }
    }
    return 0;
}
```

- 所以最后就是：

```
#include <bits/stdc++.h>
#define ll long long
#define N 200010
using namespace std;

ll a[N], t[N], n, m, x, y, cnt, ccnt[N], tmp[N];

inline int lowbit(int w) {
    return w & (-w);
}

ll query(ll x) {
    ll ans = 0;
    for (ll i = x; i >= 1; i -= lowbit(i)) ans += t[i];
    return ans;
}

void update(ll x, ll val) {
    for (ll i = x; i <= n; i += lowbit(i)) t[i] += val;
}

int main() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) cin >> a[i];
    for (ll i = 1; i <= n; i++) {
        tmp[i] = i - query(a[i]) - 1;
        cnt += tmp[i];
        ccnt[tmp[i]]++;
        update(a[i], 1);
    }
    memset(t, 0, sizeof(t));
    update(1, cnt);
    cnt = 0;
    for (ll i = 1; i <= n; i++) {
        cnt += ccnt[i - 1];
        update(i + 1, -(n - cnt));
    }
    while (m--) {
        cin >> y >> x;
        x = min(x, n - 1);
        if (y == 2) cout << query(x + 1) << "\n";
        else if (y == 1) {
            if (a[x] < a[x + 1]) {
                swap(a[x], a[x + 1]);
                swap(tmp[x], tmp[x + 1]);
                tmp[x + 1]++;
                update(tmp[x + 1] + 1, -1);
                update(1, 1);
            } else {
                swap(a[x], a[x + 1]);
                swap(tmp[x], tmp[x + 1]);
                update(tmp[x] + 1, 1);
                tmp[x]--;
                update(1, -1);
            }
        }
    }
    return 0;
}
```

---

## 作者：cirnovsky (赞：1)

## NOI-Online-T2-冒泡排序

这道题我在考场上的做法很玄，本来是奔着40pts的部分分去的，结果爆零了(至今没找到原因)

我们设

$$bigger_{i}=\sum_{j=1}^{i-1}[a_{j}>a_{i}]$$

显然逆序对数量为 $\sum bigger$

于是问题就转化为了动态维护 $bigger$。

手玩几组数据后我们可以发现，每轮冒泡 $bigger$ 都会有一下的变化：

$$bigger_{i}=\max\{bigger_{i}-1,0\}$$

于是树状数组维护即可

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

char buf[1 << 21], *p1 = buf, *p2 = buf;
#ifndef ONLINE_JUDGE
#define gc() getchar()
#else
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
#endif
#define is() (ch >= '0' && ch <= '9')
template < typename Type >
void read(Type& a) {
	a = 0; bool f = 0; char ch;
	while (!(ch = gc(), is())) if (ch == '-') f = 1;
	while (is()) a = (a << 3) + (a << 1) + (ch ^ '0'), ch = gc();
	a = (f ? -a : a);
}

template < typename Type, typename... Args >
void read(Type& t, Args&... args) {
	read(t), read(args...);
}

using namespace std;

const int MAXN = 2e5 + 5;
int n, m, bigger[MAXN], bucket[MAXN], a[MAXN];
long long bit[MAXN], init_inver_tot;

void Update(int x, long long y) {
	for (; x <= n; x += x & -x) bit[x] += y;
}

long long GetAnswers(int x) {
	long long res = 0;
	for (; x; x -= x & -x) res += bit[x];
	return res;
}

signed main() {
	read(n, m);
	for (int i = 1; i <= n; ++i) read(a[i]), init_inver_tot += (bigger[i] = i - 1 - GetAnswers(a[i])), bucket[bigger[i]]++, Update(a[i], 1);
	memset(bit, 0, sizeof bit), Update(1,  init_inver_tot), init_inver_tot = 0;
	for (int i = 0; i < n; ++i) init_inver_tot += 1LL * bucket[i], Update(i + 1 + 1, init_inver_tot - n);
	for (int i = 0, op, x; i < m; ++i) {
		read(op, x);
		if (n - 1 < x) x = n - 1;
		if (op ^ 2) {
			if (a[x + 1] > a[x]) {
				swap(a[x], a[x + 1]);
				swap(bigger[x], bigger[x + 1]);
				Update(1, 1);
				Update(bigger[x + 1]++ + 2, -1);
			}
			else {
				swap(a[x], a[x + 1]);
				swap(bigger[x], bigger[x + 1]);
				Update(1, -1);
				Update(--bigger[x] + 2, 1);
			}
		}
		else printf("%lld\n", GetAnswers(x + 1));
	}
	return 0;
}
```

---

## 作者：zrzring (赞：0)

[更好的阅读体验](http://zrzring.cn/index.php/archives/244)

先考虑手玩一下冒泡排序，然后考虑逆序对在上面有什么特殊性质，如果说逆序对通过计算每个位置的贡献的话(每个位置前面有多少数大于它)，会发现一次冒泡排序部分数字往前移了一格，并且那些大的数字往后走了很多个格

每个往前移动的数字，前面一定少了一个且仅一个比它大的，每个往后移动很多格的数字，一定是因为它前面没有比它更大的数字才会去往后走的，记一个数字$i$前面有$b_i$个数大于它，那么可以有一个结论

> 一次冒泡排序，会使得所有$b_i$变为$max(0, b_i - 1)$

因为是排列，所以$b_i$表示每个位置$i$还是每个数字$i$来计算总贡献是等价的，这样操作1就成了修改$b_x$和$b_{x + 1}$的值了，问题转变成

> 单点修改，询问全局所有元素减$k$再对$0$取$max$的和

开个值域树状数组，维护一下每个元素出现次数即可

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#define lowbit(x) (x & -x)
using namespace std;
void file() {
    freopen("std.in", "r", stdin);
    freopen("wa.out", "w", stdout);
}
const int N = 1e6 + 10, inf = 1e9;
inline int read() {
    bool sym = 0; int res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
int n, m, a[N], below[N];
struct BIT {
    long long tr[N];
    void clear() {for (int i = 1; i <= n; i++) tr[i] = 0;}
    long long query(int x) {
        if (!x) return 0; long long res = 0; for (; x; x -= lowbit(x)) res += tr[x]; return res;
    }
    void add(int x, int t) {
        if (!x) return; for (; x <= n; x += lowbit(x)) tr[x] += 1ll * t;
    }
} cnt, sum;
int main() {
    n = read(); m = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read(); cnt.add(a[i], 1); below[i] = i - cnt.query(a[i]);
    }
    cnt.clear();
    for (int i = 1; i <= n; i++) cnt.add(below[i], 1), sum.add(below[i], below[i]);
    for (int i = 1; i <= m; i++) {
        int opt = read();
        if (opt == 1) {
            int x = read();
            cnt.add(below[x], -1); sum.add(below[x], -below[x]);
            cnt.add(below[x + 1], -1); sum.add(below[x + 1], -below[x + 1]);
            swap(below[x], below[x + 1]); a[x] > a[x + 1] ? below[x]-- : below[x + 1]++;
            cnt.add(below[x], 1); sum.add(below[x], below[x]);
            cnt.add(below[x + 1], 1); sum.add(below[x + 1], below[x + 1]);
            swap(a[x], a[x + 1]);
        }
        if (opt == 2) {
            int k = read(); if (k >= n) {printf("0\n"); continue;}
            printf("%lld\n", sum.query(n) - sum.query(k) - (cnt.query(n) - cnt.query(k)) * k);
        }
    }
    return 0;
}
```

---

## 作者：xukuan (赞：0)

~~大菜鸡xukuan一开始以为一次冒泡排序只会减少一个逆序对~~

我们令$sum_i$表示第$i$个数字前有$i$个比他大的。

显然每次排序后，$sum_i$都会减少1，但$sum_i$不会小于0

证明

- 如果$sum_i=0$显然$sum_i$还是0
- 如果$sum_i>0$，那么前面肯定会有一个比他大的数字转到后面。所以$sum_i$减少1

那么转了k次后，总逆序对个数就是$\sum_{i=1}^n max(0,a_i)$

我们开两个树状数组，一个维护每个点的逆序对个数，另一个维护大于k的数的和。

至于修改：先删除原来的影响（树状数组的删除，val=-1的修改），再改值，换位，最后加回去。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=200010;
ll n,m,p[N],nxd[N]; 

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
} 

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48); 
		x%=y;
	}
}

struct BITmentTree{
	ll sum[N];
	inline ll lowbit(ll x){
		return x&(-x);
	}
	inline void update(ll x,ll val=1){
		for(ll i=x; i<=n; i+=lowbit(i)) sum[i]+=val;
	}
	inline ll query(ll x){
		ll ans=0;
		for(ll i=x; i; i-=lowbit(i)) ans+=sum[i];
		return ans;
	}
	inline ll query(ll l,ll r){
		return query(r)-query(l-1);
	}
}a,b;

inline void update(ll x,ll val=1){
	a.update(x,val);
	b.update(x,val*x);
}

inline ll query(ll l,ll r){
	return b.query(l,r)-(l-1)*a.query(l,r);
}

int main(){
	freopen("bubble.in","r",stdin);
	freopen("bubble.out","w",stdout);
	n=read(); m=read();
	for(ll i=1; i<=n; i++) p[i]=read();
	for(ll i=1; i<=n; i++){
		nxd[i]=i-a.query(p[i])-1;
		a.update(p[i]);
	}
	memset(a.sum,0,sizeof(a.sum));
	for(ll i=1; i<=n; i++){
		if(nxd[i]) update(nxd[i]);
	}
	while(m--){
		ll op=read(),x=read();
		if(op==2){
			if(x>=n){
				printf("0\n");
				continue;
			}
			write(query(x+1,n)); putchar('\n');
		}
		else{
			if(nxd[x]) update(nxd[x],-1);
			if(nxd[x+1]) update(nxd[x+1],-1);
			if(p[x]>p[x+1]) nxd[x+1]--; else nxd[x]++;
			swap(nxd[x],nxd[x+1]); swap(p[x],p[x+1]);
			if(nxd[x]) update(nxd[x],1);
			if(nxd[x+1]) update(nxd[x+1],1); 
		}
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
```

---

## 作者：C20203030 (赞：0)

刚考完，赶紧来水一波题解。。。
## 一、题目
[点此看题](https://www.luogu.com.cn/problem/P6186)
## 二、解法
首先这道题有一道[同名题](https://blog.csdn.net/C202044zxy/article/details/103439400)，很相似（推荐先看这道同名题的题解，那题是黑的，怎么这题评成蓝色了？）

逆序对转化成每一个数前面比它大的数的个数（记为$b$数组），每一轮的归并排序中，如果一个数前面有比他大的数，那么它会左移一位，然后这个数位置上的$b$减$1$，那么答案为（记轮数为$k$）：
$$\sum \min(b[i]-k,0)$$

很容易发现用权值线段树维护吧，分成大于$k$的部分和小于等于$k$的部分，算大于$k$部分的贡献即可（这里就维护个数和总和），至于修改，只交换$x$和$x+1$，显然对其它的位置是没有任何影响的，讨论一下$a[x]$和$a[x+1]$的大小关系，如果$a[x]$大那么交换后$b[x]$减$1$，如果$a[x+1]$大那么交换后$b[x+1]$加$1$，然后在权值线段树上修改就行了。

图方便我写的树状数组，时间复杂度$O(n\log n)$，代码在民间数据能够通过，并且我这个小蒟蒻还是觉得打的是对的，可以放心看$qwq$。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define ll long long
const int M = 200005;
int read()
{
    int x=0,flag=1;char c;
    while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*flag;
}
int n,m,a[M],b[M],bit[M];
ll k,sum[M],A,B;
int lowbit(int x)
{
    return x&(-x);
}
void upd(int x)
{
    for(int i=x;i<=n;i+=lowbit(i))
        bit[i]++;
}
int ask(int x)
{
    int res=0;
    for(int i=x;i>=1;i-=lowbit(i))
        res+=bit[i];
    return res;
}
void modify(int x,int f)
{
    for(int i=x+1;i<=n;i+=lowbit(i))
    {
        bit[i]+=f;
        sum[i]+=x*f;
    }
}
void query(int x)
{
    for(int i=x+1;i>=1;i-=lowbit(i))
    {
        A+=bit[i];
        B+=sum[i];
    }
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        b[i]=i-ask(a[i])-1;
        k+=b[i];
        upd(a[i]);
    }
    memset(bit,0,sizeof bit);
    for(int i=1;i<=n;i++)
    {
        modify(b[i],1);
    }
    for(int i=1;i<=m;i++)
    {
        int op=read(),x=read();
        if(op==1)
        {
            if(a[x]>a[x+1])
            {
                swap(a[x],a[x+1]);
                swap(b[x],b[x+1]);
                modify(b[x],-1);
                b[x]--;k--;
                modify(b[x],1);
            }
            else if(a[x]<a[x+1])
            {
                swap(a[x],a[x+1]);
                swap(b[x],b[x+1]);
                modify(b[x+1],-1);
                b[x+1]++;k++;
                modify(b[x+1],1);
            }
        }
        else
        {
            if(x>=n)
            {
                puts("0");
                continue ;
            }
            A=0;B=0;
            query(x);
            ll ans=(k-B)-(n-A)*x;
            printf("%lld\n",ans);
        }
    }
}

```



---

## 作者：Boring__Zheng (赞：0)

#### **P6186 [NOI Online 提高组]冒泡排序**

##### [题目描述](https://www.luogu.com.cn/problem/P6186)

##### 分析

对于这道题，我们可以先求出原序列中的逆序对数量，然后执行两个操作

为了方便进行操作，我们先将原序列离散化到1~n，然后维护一个数组con[i]表示序列的第i个数前有con[i]个数比它大，那么逆序对数量cnt=$\sum\limits_{i=1}^ncon[i]$

对于第一个操作，判断交换的两个数的大小关系，然后改变cnt和con[i]即可

对于第二个操作，由引理1可得：k轮冒泡排序后减少的逆序对数量是$\sum\limits_{con[i]\leq k}con[i]+\sum\limits_{con[i]>k}k$分别维护两个树状数组即可

###### 引理1

在一个序列进行一轮冒泡排序之后，$con[i]=max(con[i+1]-1,0)$，特别的$con[n]=max(con[1]-1,0)$

证明：

第k轮冒泡排序时，对于序列中第i个数$(i\in[2,k-2])$，要么置换到$i-1$的位置，要么置换到$i+1$的位置，前者有con[i-1]=con[i]-1，后者有con[i]=con[i+1]-1

##### 代码

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N=1e6+5;
struct Node
{
	ll val,id;
}a[N];
struct node
{
	ll x,y;
}que[N];
ll n,m,c[4*N],sq[N],con[N],cnt,c1[N],c2[N];

bool cmp(Node x,Node y)
{
	return x.val < y.val;
}

ll lowbit(ll x)
{
	return x & (-x);
}

void add(ll x,ll val,ll c[N])
{
	if( x==0 ) x=1;
	while( x <= n )
	{
		c[x]+=val;
		x+=lowbit(x);
	}
	return;
}

ll sum(ll x,ll c[N])
{
	ll tem=0;
	while( x )
	{
		tem+=c[x];
		x-=lowbit(x);
	}
	return tem;
}

void Input()
{
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i].val),a[i].id=i;
	for(ll i=1;i<=m;i++) scanf("%lld%lld",&que[i].x,&que[i].y);
	return;
}

void Prepare()
{
	sort(a+1,a+n+1,cmp);
	for(ll i=1;i<=n;i++) sq[a[i].id]=i;
	for(ll i=1;i<=n;i++) add(sq[i],1,c1),con[i]=i-sum(sq[i],c1),cnt+=con[i];
	return;
}

void deal1(ll id)
{
	add(con[id],-1,c1); add(con[id],-con[id],c2);
	add(con[id+1],-1,c1); add(con[id+1],-con[id+1],c2);
	if( sq[id] < sq[id+1] ) con[id]++,cnt++;
	else con[id+1]--,cnt--;
	swap(con[id],con[id+1]);
	swap(sq[id],sq[id+1]);
	add(con[id],1,c1); add(con[id],con[id],c2);
	add(con[id+1],1,c1); add(con[id+1],con[id+1],c2);
	return;
}

void deal2(ll k)
{
	ll tem;
	if( k >= n ) k=n-1;
	tem=sum(k,c2);
	tem+=k*(n-sum(k,c1));
	printf("%lld\n",cnt-tem);
	return;
}

void work()
{
	memset(c1,0,sizeof(c1));
	for(ll i=1;i<=n;i++) add(con[i],1,c1),add(con[i],con[i],c2);
	for(ll i=1;i<=m;i++)
	{
		if( que[i].x==1 ) deal1(que[i].y);
		else deal2(que[i].y);
	}
	return;
}

int main()
{
	Input();
	Prepare();
	work();
	return 0;
}
```



---

