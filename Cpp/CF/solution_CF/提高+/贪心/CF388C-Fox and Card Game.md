# Fox and Card Game

## 题目描述

Fox Ciel is playing a card game with her friend Fox Jiro. There are $ n $ piles of cards on the table. And there is a positive integer on each card.

The players take turns and Ciel takes the first turn. In Ciel's turn she takes a card from the top of any non-empty pile, and in Jiro's turn he takes a card from the bottom of any non-empty pile. Each player wants to maximize the total sum of the cards he took. The game ends when all piles become empty.

Suppose Ciel and Jiro play optimally, what is the score of the game?

## 说明/提示

In the first example, Ciel will take the cards with number 100 and 1, Jiro will take the card with number 10.

In the second example, Ciel will take cards with numbers 2, 8, 6, 5, 9 and Jiro will take cards with numbers 4, 7, 1, 3.

## 样例 #1

### 输入

```
2
1 100
2 1 10
```

### 输出

```
101 10
```

## 样例 #2

### 输入

```
1
9 2 8 6 5 9 4 7 1 3
```

### 输出

```
30 15
```

## 样例 #3

### 输入

```
3
3 1 3 2
3 5 4 6
2 8 7
```

### 输出

```
18 18
```

## 样例 #4

### 输入

```
3
3 1000 1000 1000
6 1000 1000 1000 1000 1000 1000
5 1000 1000 1000 1000 1000
```

### 输出

```
7000 7000
```

# 题解

## 作者：dottle (赞：37)

先来考虑所有堆均有偶数张牌的情形。

我们将要证明，最终 C 会取走每堆牌顶端一半的牌，J 会取走每堆牌底端一半的牌。将这个局面简称为 $\star$。

考虑 $\star$ 局面的特殊性质：

1.  无论 J 如何操作，C 都可以迫使局面到达 $\star$。
2.  无论 C 如何操作，J 都可以迫使局面到达 $\star$。

1 情形中 C 的策略为，每次取牌时，若已经取过的所有牌对称，则任意取一张；否则从 J 上次取牌的牌堆取牌。2 情形中 J 的策略为：每次从 C 取牌的牌堆取牌。

因此，考虑任意一个与 $\star$ 不同的最终局面 $\circ$ 。若 J 在 $\circ$ 中的得分比他在 $\star$ 中的得分低，则他一定不会让游戏以 $\circ$ 结束；对于 C 也是同理。这样看来，所有其他的局面都不可能成为结束局面，最终的局面就是 $\star$ 了。 

注意这里的过程与先后手无关。

---

接下来我们考虑有奇数的情形。

因为每堆牌堆是相互独立的，所以对于那些偶数堆的牌，我们可以放在一边了。最后直接顶一半给 C，底一半给 J。

考虑 C 取一堆奇数的牌会发生什么？

![img](https://cdn.luogu.com.cn/upload/image_hosting/l3q5tkv2.png)

C 从奇数堆中取走第一张牌，把它变成偶数堆的时候，最中间这张牌的归宿就已经确定了，然后这堆牌变成了偶数我们就不管了。也就是说，对于奇数堆来讲，谁先从中取牌，谁就会最终取走中间那个牌。那么这一步的策略显然应该是贪心，C 先从中间那个数最大的奇数堆取牌，然后轮到 J 取，直到没有奇数堆了，就转化为先前的问题了。因为前面那个问题先后手无关，因此这里我们不需要额外考虑是谁取了最后一个奇数堆的石子。

这时候还有一个问题，如果在最开始轮流取奇数堆的时候有人突然跑去取偶数堆了怎么办？这样的策略是不优的，因为你的对手可以取走对称的牌来抵消你的操作，因此这样的策略不可能使得分变高，还可能使得分变低，因此不会出现。

这样，我们就完成了对整个游戏过程的分析：

1.  双方玩家轮流选择中间的牌价值最高的、含有奇数张的牌堆，取走此牌堆中间的牌。
2.  剩下的牌，牌堆顶的一半由 C 获得，底的一半由 J 获得。

第一部分可以将所有中间的牌放进一个数组从大到小排序，双方轮流取走剩下的最大的数。

---

## 作者：ql12345 (赞：5)

# 题解
#### 翻译已经提供
## 贪心解决

贪心是指考虑小A小B拿牌过程

### 分析：
每个人肯定都想要大的分数的牌，如果这张牌在小A这边（在某一堆中位置更靠近上部），小A显然不会放弃这张牌，即她看到小B取这堆的堆底时，也可取堆顶，防止小B那道那张牌

### 结论：
谁都不放弃自己的大牌，就导致小A和小B能且只能拿到离自己近的牌

### 解决：
对于有偶数张牌的堆：小A小B各拿一半，答案加上这些牌的分数即可

对于有奇数张牌的堆：小A和小B先按照策略拿得只剩中间一张，最后会剩下“奇数堆数”张的“中间”。
对于这些牌，按分数从大到小排序，小A小B依次拿，直至拿完，答案也很好统计

说明：为什么对于“中间”牌是小A先拿呢？
因为之前小A拿一张，小B拿一张，完全对称，所以取到最后局面的时候，仍是小A先拿

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,mid[110],ans1,ans2,tot;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&m);
		for(int j=1;j<=m>>1;++j)
			scanf("%d",&a),ans1+=a;
		if(m&1)
			scanf("%d",&mid[++tot]);
		for(int j=1;j<=m>>1;++j)
			scanf("%d",&a),ans2+=a;
	}
	sort(mid+1,mid+tot+1);
	for(int i=tot;i>0;i-=2)
		ans1+=mid[i];
	for(int i=tot-1;i>0;i-=2)
		ans2+=mid[i];
	printf("%d %d",ans1,ans2);
	return 0;
}
```


---

## 作者：CaiXY06 (赞：5)

非常明显的一道贪心题。

显然两人会采取这样的策略：对于每一堆牌，保护属于自己容易取到的那一半不被对方取走。

那么如果牌数是奇数的牌堆的中间那一张，就会陷入两难的境地。

所以我们考虑把中间牌的权值塞入一个大根堆，两人轮流取最大值，这样就能保证两人所得分数最大。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,A,B;
priority_queue<int>Q;//大根堆
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&m);
		for(int j=1,x;j<=m;j++){
			scanf("%d",&x);
			if(m&1&&j==(m+1)>>1)Q.push(x);//中间牌
			else{//非中间牌
				if(j<=m>>1)A+=x;
				else B+=x;
			}
		}
	}
	int p=1;
	while(!Q.empty())p?A+=Q.top():B+=Q.top(),Q.pop(),p^=1;//轮流取最大值
	printf("%d %d",A,B);
	return 0;
}
```


---

## 作者：DPair (赞：2)

代码实现无大区别，但思路略有不同。

## 【思路】
个人优先从状态的得分情况来讨论。

首先发现对于一个大小为 $k$ 的牌堆，无论 $k$ 是奇数 还是偶数，双方都必定有策略使得靠近自己的 $\lfloor\frac{k}{2}\rfloor$ 张牌不被对手拿到。

这个结论应该不需要详细说吧，要是我真的想要保留自己这边的牌那么对手每次拿一张这个牌堆的牌，我就可以去拿同一牌堆的最后一张，一直拿到不剩或者剩最后一张。

进一步可以发现，每个人都必定会拿到靠近自己的 $\lfloor\frac{k}{2}\rfloor$ 张牌。

这个也不难分析，首先对手不可能来抢你一个 **可以放弃** 的牌堆，这里 **可以放弃** 是指你不需要保护你自己这个牌堆，也就是说如果对手来抢，那么必然在另一个牌堆中有一张 **你原来够不到，对手给机会之后你就够得到了的，比你当前牌堆保护的牌更大的牌**（有点绕，自行理解一下），由于双方都是最优策略，对手一定不会给你机会，而去攻另一个牌堆，而不是你这个可以放弃的牌堆。

那么，由于对手攻的每一个牌堆都 **不可放弃** ，你就必定和对手会互相拿走靠近自己的 $\lfloor\frac{k}{2}\rfloor$ 张牌 。

最后考虑 $k$ 为奇数的情况。

已经很简单了。

由于所有牌堆都只剩下一张牌或一张也不剩，而且显然拿完偶数张牌后，先手还是先手。

那么双方的最优策略都是直接拿当前所有牌中最大的就行了。

然后就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}

int n, ans1, ans2;
vector <int> vec;
int main(){
    read(n);
    while(n --){
        int k;read(k);
        for (register int i = 1;i <= k;i ++){
            int x;read(x);
            if(i <= (k >> 1)) ans1 += x;
            else if((k & 1) && i == ((k + 1) >> 1)) vec.push_back(x);
            else ans2 += x;
        }
    }
    sort(vec.begin(), vec.end());
    int it = 1;
    while(!vec.empty()){
        if(it) ans1 += vec.back();
        else ans2 += vec.back();
        vec.pop_back();it ^= 1;
    }
    fprint(ans1, 32);fprint(ans2, 10);
    return 0;
}
```

---

## 作者：quest_2 (赞：2)

简单题，水评$\texttt\color{blueviolet}\colorbox{white}{紫}$。

方法和楼上 $dalao$ 差不多，本文重在思路。

------------

### 样例手玩：

我们分别以 $A$、$B$ 两人的主视角来尝试想出思路，用的是第3组样例：

```
3
3 1 3 2
3 5 4 6
2 8 7
```

我们首先清楚，倘若一张牌在牌堆中的位置是靠 $A$ 这一边的，我们可以断定 $A$ 在拿这张牌时**更有优势**。

对于 $A$ 来说，他在**拿牌方面**比较占优势的有：堆1中的点数为1的牌（以下以 $(1,1)$ 形式表示）， $(2,5)$ ， $(3,8)$ 。

对于 $B$ 来说，他在**拿牌方面**比较占优势的有：$(1,2)$ ， $(2,6)$ ，$(3,7)$ 。

而之于 $(1,3)$ 和 $(2,4)$ ，则两边的优势相等，互不吃亏。

-------

### 策略模拟：

现在我们从 $A$ 开始。$A$ 认为，拿一张对方有优势的卡要付出的**步数的代价**必然很大，对方如果看出了这一意图，必能以**较少的步数**采取保卫措施。所以 $A$ 决定拿自己**掌握优势**的牌。他先拿了一张 $(3,8)$ 。

回合轮到 $B$ ，他也认为拿自己掌握优势的牌更为划算，所以他拿了一张 $(3,7)$ 。

两人你来我往了几个回合。自己最初有优势的牌都已经被拿完了。

**注意**：”拿完有优势的牌“这一情况必然在**相邻**的两回合发生，且这一情况结束后**必为 $A$ 的回合**，因为两人最开始的优势牌数是**相等**的。

现在场上剩下两张牌，$(1,3)$ 和 $(2,4)$ ，如果 $A$ 睡眠充足，他不用想也知道该拿最大的那张。

为什么他**可以拿到**最大的那张？

因为优势均等的牌，在每一堆中都最多只有**一个**（倘若有两个就必然分靠两方），故最后剩下的这些牌，相互之间必然没有条件关系。那他取哪张都是合法的。

最后两个人轮流取完当时情况下点数最大的牌，游戏结束了。

------

### 实现有关：

我们回想这一过程，前面的你来我往实则可以归结为一句话：**两个人都把自己有优势的牌给拿完了**。

对于每个人，有优势的牌是必然确定的，就是每一堆中**靠上的一半**和**靠下的一半**。

此外，倘若牌堆中牌的数量是奇数，则最中间的那张被定为**优势均等的牌**。

我们先把优势牌的点数加到 $A$ 、 $B$ 的得分上去。

对于优势均等的牌，我们每次都取点数最大的，可以用**优先队列**来维护这一最大值。

直到优先队列为空，游戏即可结束。

------------

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 107;
int N;
int card[MAX][MAX], num[MAX];
int A, B;
priority_queue<int> q;
int main()
{
	cin >> N;
    
	for (int i = 1; i <= N; i++)
	{
		cin >> num[i];
        
        /*输入数据*/
		for (int j = 1; j <= num[i]; j++)
		{
			cin >> card[i][j];
		}
        
        /*拿优势牌*/
		for (int j = 1; j <= num[i] / 2; j++)
		{
			A += card[i][j];
			B += card[i][num[i] - j + 1];
		}
        
        /*优势均势牌入优先队列*/
		if (num[i] % 2)
		{
			q.push(card[i][num[i] / 2 + 1]);
		}
        
	}
	int turn = 1;
    
    /*拿当前最大牌*/
	while (!q.empty())
	{
		if (turn)
		{
			A += q.top();
		}
		else
		{
			B += q.top();
		}
		q.pop();
		turn = 1 - turn;
	}
	cout << A << ' ' << B << endl;
}
```


---

## 作者：CReatiQ (赞：1)

### 题意概述

有 $n$ 堆牌，每堆牌中有 $s_i$ 张牌，每张牌上有一个数字 $c_i$ 。

$( 1 \leq n \leq 100 , 1 \leq s_i \leq 100 , 1 \leq c_i \leq 1000 )$

现有 A 先手，B 后手轮流从牌堆中抽牌。A 只能从牌堆顶抽起，B 只能从牌堆底抽起。

A B 两人均贪婪，即期望所抽牌上的数字之和最大，且均做完全理性决策，求两人各自所抽取的牌上的数字之和。

---

### 思路

根据抽牌的规则，一堆牌一定能被通过以下的方式抽取结束：

本堆牌的前 $\lfloor \frac{n}{2} \rfloor$ 张牌被 A 抽取，后 $\lfloor \frac{n}{2} \rfloor$ 张牌被 B 抽取。

如果有一张牌剩余，则被开始抽取本堆牌时的先手方抽取。

因为两者均贪婪，所以可能有一者试图用自己一侧的一张牌去“换取”对方一侧的一张数字更大的牌。

我们举出例子：

有两堆牌，分别为 $\{ 5,6,1,5\}$ 与 $\{ 5,2,6,5\}$。

此时 B 可能会试图放弃第一堆中的 $1$ 以换取第二堆中的 $2$ 。

但因为 A 同样贪婪，所以 A 绝不会让 B 得手。

因为 A 与 B 轮流抽牌，起初后手方可以一直跟先手方对称抽牌。

假如后手方不跟着先手方对称抽牌了，先手方就可以反过来跟着后手方对称抽牌，使得后手方总是没有机会换走先手方一侧的优势牌。

所以在 B 抽走第二堆的 $6$ 时，A 就会立刻把 $2$ 抽走，让 B 无法得逞。

那反过来，如果后手方一侧拿到了优势牌，只要它一直与先手方对称出牌，先手方也是永远换不走他的优势牌的。

综上，**换牌有盈有亏，而贪婪的双方总是会保护自己不受亏损，所以换牌是不可能实现的。**

但我们还没考虑每堆牌剩下的单张牌。

其实我们不难发现，当一堆牌的牌数为偶数时，交换先后手没有什么区别。

但是当一堆牌为奇数时，剩下的一张牌会被先手方抽取，并且使它在新的一个牌堆里变为后手方。

因为没有规定必须抽完一个牌堆才能开下一个牌堆，所以这时每个奇数牌数的牌堆，都可以把它的中间这张牌先抽出来，左 A 右 B，最后再来考虑怎么取这些中间牌。

因为每抽取一张中间牌，先后手就变一次，并且 A 和 B 都贪婪，所以 A 和 B 会在这些中间牌中轮流抽走最大的那张。

---

### Code

```cpp
#include <queue>
#include <cstdio>
using namespace std;

const int MAXN=3e5+10;
int T,n,a[MAXN],ansa,ansb;
priority_queue<int> q;

inline int read()
{
	int x=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x;
}

int main()
{
	T=read();
	while (T--)
	{
		n=read();
		for (int i=1;i<=(n>>1);i++) ansa+=read();
		if (n&1) q.push(read());
		for (int i=1;i<=(n>>1);i++) ansb+=read();
	}
	while (!q.empty())
	{
		ansa+=q.top();
		q.pop();
		if (!q.empty())
		{
			ansb+=q.top();
			q.pop();
		}
	}
	printf("%d %d",ansa,ansb);
	return 0;
}
```


---

## 作者：orz_z (赞：0)

### 题目大意

桌子上有 $n$ 堆牌，每张牌上都有一个正整数。

`A` 可以从任何非空牌堆的顶部取出一张牌，`B` 可以从任何非空牌堆的底部取出一张牌。

`A` 先取，当所有的牌堆都变空时游戏结束。

他们都想最大化他所拿牌的分数（即每张牌上正整数的和）。

问他们所拿牌的分数分别是多少？

### 解题思路

经典的博弈论。

显然的贪心。

显然，对于每一堆牌，两个人都要保护属于自己那一半不被拿走（上面的一半或下面的一半）。

那么如果牌堆中牌数是偶数，那么各自分一半。

否则，牌堆中牌数是奇数，那么会在中间那一张上起争执。

于是两个人就会轮流取中间牌的最大值。

用 `priority_queue` 维护当前还剩的最大值即可。


### CODE

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;

int a[100007];

int A, B;

priority_queue<int> pq;

signed main()
{
    scanf("%d", &n);
    for (int i = 1, j, x; i <= n; ++i)
    {
        scanf("%d", a + i);
        for (j = 1; j <= (a[i] >> 1); ++j)
        {
            scanf("%d", &x);
            A += x;
        }
        if (a[i] & 1)
        {
            scanf("%d", &x);
            pq.push(x);
            ++j;
        }
        for (; j <= a[i]; ++j)
        {
            scanf("%d", &x);
            B += x;
        }
    }
    int p = 1;
    while (!pq.empty())
    {
        if (p)
            A += pq.top();
        else
            B += pq.top();
        pq.pop();
        p ^= 1;
    }
    printf("%d %d\n", A, B);
    return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 前置知识
基础博弈论，贪心
## 思路
显然两个人都要保护自己应该得到的那一半（上面的一半或下面的一半）。

那么如果牌堆中牌数是偶数，那么各自分一半。

如果牌堆中牌数是奇数，那么会在中间那一张上起争执。

于是两个人就会轮流取最大值。

剩下的就是用大根堆维护当前还剩的最大值了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[100001];
int A,B;//两个人的总数 
priority_queue<int> pq;
int main(){
	scanf("%d",&n);
	for(int i=1,j,x;i<=n;++i){
		scanf("%d",a+i);
		for(j=1;j<=(a[i]>>1);++j){
			scanf("%d",&x);
			A+=x;
		}//B的
		if(a[i]&1){
			scanf("%d",&x);//中间牌 
			pq.push(x);
			++j;
		}
		for(;j<=a[i];++j){
			scanf("%d",&x);
			B+=x;
		}//B的 
	}
	int p=1;//当前谁取 
	while(!pq.empty()){
		if(p)A+=pq.top();
		else B+=pq.top();
		pq.pop();
		p^=1;
		//轮流取最大值
	}
	printf("%d %d\n",A,B);
	return 0;
}
```


---

