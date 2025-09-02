# Integer Game

## 题目描述

This is an interactive problem.

Anton and Harris are playing a game to decide which of them is the king of problemsetting.

There are three piles of stones, initially containing $ a $ , $ b $ , and $ c $ stones, where $ a $ , $ b $ , and $ c $ are distinct positive integers. On each turn of the game, the following sequence of events takes place:

- The first player chooses a positive integer $ y $ and provides it to the second player.
- The second player adds $ y $ stones to one of the piles, with the condition that he cannot choose the same pile in two consecutive turns.

The second player loses if, at any point, two of the piles contain the same number of stones. The first player loses if $ 1000 $ turns have passed without the second player losing.

Feeling confident in his skills, Anton decided to let Harris choose whether he wants to go first or second. Help Harris defeat Anton and become the king of problemsetting!

## 说明/提示

In the sample input, the piles initially have $ 5 $ , $ 2 $ , and $ 6 $ stones. Harris decides to go first and provides the number $ 2 $ to Anton. Anton adds $ 2 $ stones to the third pile, which results in $ 5 $ , $ 2 $ , and $ 8 $ .

In the next turn, Harris chooses $ 3 $ . Note that Anton cannot add the stones to the third pile since he chose the third pile in the previous turn. Anton realizes that he has no valid moves left and reluctantly recognizes Harris as the king.

## 样例 #1

### 输入

```
5 2 6


3

0```

### 输出

```
First
2

3```

# 题解

## 作者：rui_er (赞：14)

题意：**交互题**，三堆石子，石子个数分别为 $a,b,c\in\left[1,10^9\right]\cap\rm{Z}$，选择先手或者后手进行游戏。先手给定一个数 $k\in\left[1,10^{12}\right]\cap\rm{Z}$，后手将一堆石子个数增加 $k$，不能连续增加同一堆两次。如果有两堆石子个数一样，后手输；如果 $10^3$ 次内先手没有赢，则后手赢。问谁有必胜策略。

---

首先，我们考虑什么时候后手会输。

假设此时 $a\lt b\lt c$：

1. 如果 $b-a\ne c-b$，则不论可以修改哪个，后手均不会输。
2. 如果 $b-a=c-b$，此时如果不能修改 $c$，则可以构造出 $k=b-a=c-b$ 使得后手必败；如果可以修改 $c$，则不能保证。

得出结论：**当且仅当 $a,b,c$ 成等差数列，且最大数不能被修改时后手败。**

我们考虑是否能构造一种方法，使得在若干步后，三堆石子满足这一条件。

考虑如何能得到等差数列，且最大数不能修改？设原来三堆石子为 $a\lt b\lt c$ 且 $x=c-b,y=c-a$，并且最大数不能被修改，那么就可以构造 $k=x+y=c\times 3-(a+b+c)$ 满足条件。

为啥？假设修改 $a$，则三个数变为 $a+c\times 3-(a+b+c),b,c$，即为 $2\times c-b,b,c$，其中 $(2\times c-b)-c=c-b$，符合上面的描述。修改 $b$ 同理。

此时我们发现，中位数为 $c$，即原来的最大数；公差可以根据这一点推出：用 $c$ 减去另一个没有变化的数。

问题转化为如何固定最大值不能动。我们一开始构造 $k=\inf$，即大于任何一个数的数，此时被修改的不管是哪个，都是修改后的最大值。记录这个最大值，然后按照上面说的做即可。

---

总结：首先构造 $k=\inf$，获得最大值位置，用指针记录。然后根据最大值，构造 $k=c\times 3-s$，其中 $c$ 为这个最大值，$s$ 为三个数的和。最后得到一个最大数不能修改的等差数列，构造 $k$ 为公差即可。

~~没错你没看错，先手在三步以内必胜。~~

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1e10;

ll a[3], *p, k, s;
ll interact(ll x) {
	printf("%lld\n", x);
	fflush(stdout);
	ll res;
	scanf("%lld", &res);
	if(!res) exit(0);
	a[--res] += x;
	return res;
}

int main() {
	scanf("%lld%lld%lld", &a[0], &a[1], &a[2]);
	puts("First"); fflush(stdout);
	s = a[0] + a[1] + a[2] + inf;
	k = interact(inf);
	p = &a[k];
	k = interact((*p)*3-s);
	ll _ = 3 - (p - a) - k;
	k = interact((*p)-a[_]);
	return 0;
}
```

---

## 作者：Andrewzdm (赞：11)

又是一道构造题……

读完题目看样例，似乎发现了什么不得了的东西。

思考为什么样例里最后先手赢了：
* 最后一步，石子数变为 $5,2,8$，先手给了 $3$ 颗石子，因为 $8-5=5-2=3$，所以后手只要放在第一堆或第二堆上都必输。
* 另外上一步中 $8$ 被操作过了，所以可怜的 Anton 不能继续在第三堆石子上继续放石子，只能认输。

这给了我们启示：**当这三个数构成等差数列，且最大数不能操作时，后手必败**。

于是我们充当先手，通过构造方案击败后手。我们的目标是，通过添加石子，让三个数构成等差数列并且操作的数是等差数列中最大的那个。

设三个数分别为 $a,b,c$，且满足 $a < b < c$。分类讨论：

设给后手的数为 $x$，
1. 若后手将数添加在了 $a$ 上，那么由题意得，$a+x+b=2c$，解得 $x=2c-a-b$；
2. 若后手将数添加在了 $b$ 上，那么由题意得，$b+x+a=2c$，解得 $x=2c-a-b$；
3. 若后手将数添加在了 $c$ 上……很遗憾，我们不一定能满足条件。

对策略进行调整：如果后手将石子添加在了较小的两堆上，那么先手必胜。

既然这样，为什么我们不再加一步操作，使后手无法操作最大的那一堆呢？

于是我们可以添加一个很大的数，比如 $10^{11}$，这样不管哪一堆添加过后都会成为最大数。

注意这个数不要太大，不然会超出 $y \le 10^{12}$ 的限制。

之后我们再给后手一个等差数列的公差，后手必败。

于是……这道题变成了顺序结构的程序题？！
```cpp
#include<cstdio>
typedef long long ll; 

void write(ll x)
{
	if(x == 0)
		return;
	write(x / 10);
	putchar(x % 10 + 48);
	return;
}

signed main()
{
	ll a[4];
	scanf("%lld%lld%lld", a + 1, a + 2, a + 3);
	puts("First");
	fflush(stdout);
	//加上一个特别大的数，使最大的一堆无法操作
	write(1e11);
	putchar('\n');
	fflush(stdout);

	int pile;
	scanf("%d", &pile);
	int mxp = pile;
	a[mxp] += 1e11;
	//使三个数成为等差数列并且让操作的一堆最大
	write(3 * a[mxp] - a[1] - a[2] - a[3]);
	putchar('\n');
	fflush(stdout);	

	scanf("%d", &pile);
	int x = pile;
	//加上公差，后手必败
	write(a[mxp] - a[6 - x - mxp]);
	putchar('\n');
	fflush(stdout);
	
	scanf("%d", &pile);
	//胜利的曙光
	return 0;
}
```

---

## 作者：duyi (赞：10)

# 进来看看吧↓

[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/13246102.html)



尝试通过构造，让先手赢。

考虑什么情况下，后手不得不让两个堆数量相等。假设某个局面下，三堆里分别有$a,b,c$个石头，不妨设$a>b>c$。那么如果上一轮的操作对象是$a$（这一轮不能对$a$操作），且$a-b=b-c$。那么此时，如果先手报：$a-b$，后手就不得不让两堆数量相等：他要么把$b$变成$a$，要么把$c$变成$b$。

总结一下这个条件，就是让**上一次的操作对象，变成当前最大的数**，且当前三个数从大到小依次**差相等**。那么此时，只需要一次操作，先手就赢了。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/29c0ukjy.png)

我们进一步思考，如何达到上述的局面呢？还是假设$a>b>c$且$a$在上一轮被用过。设$x=a-b$, $y=a-c$。此时先手可以报$x+y$。那么后手要么让$b\texttt{+=}x+y$，要么让$c\texttt{+=}x+y$，无论哪种情况，被操作的数都会成为最大值，且三个数从大到小依次差相等！于是就变成了上一种必胜的局面。

![](https://cdn.luogu.com.cn/upload/image_hosting/y1y86kyf.png)

由此可知，只要**上一次的操作对象是当前最大的数**，先手就一定能用两次操作获胜。

这个条件比第一个条件弱很多，这个局面也很好达到。一开始的时候，不妨还是设$a>b>c$，先报$a-b$。此时，$a-b$要么被作用于$a$上（达到效果，使上一次操作对象是当前最大的数），要么被作用于$c$上。如果被作用于$c$上，下一轮就只能操作$a$或$b$，我们再报$a-b$，后手不能对$b$操作（否则$a=b$就直接输了），所以后手只能对$a$操作，达到了我们希望的局面。

综上所述，我们选先手，在$4$步以内，就能获胜。

参考代码：

```cpp
//problem:F
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
 
ll a[4];
void work(){
	//上一次的操作对象,在操作后是最大值
	for(int i=1;i<=3;++i){
		if(a[i]==max(a[1],max(a[2],a[3]))){
			int j=1,k=2;
			if(i==j)j=3;
			if(i==k)k=3;
			cout<<(a[i]-a[j])+(a[i]-a[k])<<endl;
			int l;
			cin>>l;
			assert(l!=i);
			if(l==0)return;
			if(l==k)swap(j,k);
			//l=j
			a[j]+=(a[i]-a[j])+(a[i]-a[k]);
			cout<<a[i]-a[k]<<endl;
			cin>>l;
			assert(l==0);
			return;
		}
	}
}
int main() {
	cin>>a[1]>>a[2]>>a[3];
	cout<<"First"<<endl;
	for(int i=1;i<=3;++i){
		if(a[i]==max(a[1],max(a[2],a[3]))){
			int j=1;
			if(i==1)j=2;
			cout<<a[i]-a[j]<<endl;
			int k;
			cin>>k;
			a[k]+=a[i]-a[j];
			assert(k!=j);
			if(k==0)return 0;
			else if(k==i)work();
			else{
				if(a[k]>a[i])work();
				else{
					cout<<a[i]-a[j]<<endl;
					int l;
					cin>>l;
					a[l]+=a[i]-a[j];
					assert(l!=k);
					assert(l!=j);
					if(l==0)return 0;
					else work();
				}
			}
			return 0;
		}
	}
	return 0;
}
```



---

## 作者：WYXkk (赞：7)

神仙交互题，场上没想出来，第二天早上 5min 想出来，身败名裂

首先思考什么时候玩家二失败。

可以发现，玩家二失败，当且仅当 **三个数成等差数列且上一次操作的为目前最大的数**。

于是再思考前一步发生了什么。

发现玩家一只要让 **可选的两个数操作后都必定成为等差数列的最大项** 即可。

假如可选的是 $a,b$，上一次操作了 $c$ 且 $c$ 是目前最大的，可以发现玩家一只需要选择 $2c-a-b$ 就能满足条件。

那么，玩家一只需要让 **一个数操作后成为最大数** 即可。

这个直接随便加一个很大的数（例如 $10^{10}$）即可。

于是我们得出结论……先手三步必胜？！？

是的，确实是这样。

按上面的步骤模拟即可。

$\texttt{code:}$

```cpp
int main()
{
    ll a[5];
    F(i,1,3) rd(a[i]);
    const ll M=10000000000ll;
    puts("First");
    printf("%lld\n",M);
    fflush(stdout);
    ll x1=rd();a[x1]+=M;
    ll t=3*a[x1]-a[1]-a[2]-a[3];
    printf("%lld\n",t);
    fflush(stdout);
    ll x2=rd();a[x2]+=t;
    printf("%lld\n",a[x1]-a[6-x1-x2]);
    return 0;
}
```



---

## 作者：Rosent (赞：2)

upd on 2024.7.25：修改笔误

[Link](https://www.luogu.com.cn/problem/CF1375F)

『我看不出先手有任何赢的可能性』——@zmwang。

先手赢最多需要三步。

通过~~瞎猜~~观察样例可以发现先手可以赢时如下性质：

- 三个数形成等差数列。

- 上一个操作操作的是三个数中的最大数。

所以我们只需要先构造出一个等差数列来就行了。

不妨设三个数为 $a,b,c$，且 $a<b<c$。

容易想到，我们可以在第一步给出 $2c-a-b$，此时，若：

- 后手选择的是 $a$，我们只需要在第二步给出 $c-b$ 即可。

- 后手选择的是 $b$，我们只需要在第二步给出 $c-a$ 即可。

- 后手选择的是 $c$，此时我们在第三步无论给出什么都无法构造出等差数列，但是注意到后手**不能**连续对同一堆石子进行操作。与大部分题解处理方法不同的是，我们只需要重复第一步即可。

代码（写的很丑见谅）：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[10];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>a[1]>>a[2]>>a[3];
	cout<<"First"<<endl;
	int maxx=max({a[1],a[2],a[3]}),minn=min({a[1],a[2],a[3]}),midd=a[1]+a[2]+a[3]-minn-maxx;
	cout<<maxx*2-midd-minn<<endl;
	int t;
	cin>>t;
	if(a[t]==minn)
		cout<<maxx-midd<<endl;
	else if(a[t]==midd)
		cout<<maxx-minn<<endl;
	else
	{
		a[t]+=maxx*2-midd-minn;
		maxx=a[t];
		cout<<maxx*2-midd-minn<<endl;
		cin>>t;
		if(a[t]==minn)
			cout<<maxx-midd<<endl;
		else if(a[t]==midd)
			cout<<maxx-minn<<endl;
	}
	cin>>t;
	return 0;
}
```

---

## 作者：RocksonLee (赞：0)

 


## Problem

[Luogu](https://www.luogu.com.cn/problem/CF1375F)

[Codeforces](https://codeforces.com/problemset/problem/1375/F)

## Solution

刚开始这道题的思考还有些问题。博弈？还是什么？

先观察样例看看先手怎么赢的？

> 石子数为：5 2 8，给出 3 就可以胜利

因为交互库会保证自己能赢，那这种情况是怎么必赢呢？

因为上一步加了 2 给 6，得到的 8 无法操作，所以他就只能对 **小点** 的两个数二选一咯。

那么我们需要构造一个等差数列，这个等差数列的最大数必须是上一个的操作过的。

先设一下三个数：分别为 $a$，$b$，$c$，我们先对这个排个序，$a < b < c$。

分类一下试试看？设我们输入的数为 $x$。

> 如果操作在 $a$，那么 $b < c < a+x$，故 $a+x+b=2c$，即 $x=2c-a-b$。
> 如果操作在 $b$，那么 $a < c < b+x$，故 $a+x+b=2c$，即 $x=2c-a-b$。
> 如果操作在 $c$，那么 貌似没办法往下构造。

我们需要把 $c$ 设置为最大的那个数即可！

那么我们在进行这个操作之前还需要把 $c$ 作为最大的那个数，这貌似不难啊。

那么满足了这个条件后，后面一连串都可以完成，答案就迎刃而解了。

就搞一个极大值进去就好了！

于是这道题就写完了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define il inline
#define INF 1e11
#define cl(a, b) memset(a, b, sizeof(a))
typedef long long ll;
typedef unsigned long long ull;

int main()
{
    ll a[10], qwq = INF, temp1, temp2;
    cin >> a[1] >> a[2] >> a[3];
    cout << "First" << endl;
    cout << qwq << endl;
    fflush(stdout);

    cin >> temp1;
    a[temp1] += qwq;
    qwq = 3 * a[temp1] - a[3] - a[2] - a[1];
    cout << qwq << endl;
    fflush(stdout);

    cin >> temp2;
    a[temp2] += qwq;
    qwq = a[temp1] - a[6 - temp1 - temp2];
    cout << qwq << endl;
    fflush(stdout);
    return 0;
}
```


---

## 作者：suxxsfe (赞：0)

https://www.cnblogs.com/suxxsfe/p/15497102.html  

[CF1375F Integer Game](http://codeforces.com/problemset/problem/1375/F)  
三堆石子分别有 $a,b,c$ 个，游戏规则：  

- 先手选择一个数 $k$
- 后手把他加到任意一堆石子上，但不能连续对同一堆石子操作两次
- 如果有两堆石子数量相同，先手赢；回合数超过 $1000$，后手赢

交互，自选先后手  
$a,b,c\le 10^9,k\le 10^{12}$  

考虑先手赢的最后一部肯定是有局面 $(n-k,n,n+k)$，并且上一步操作的是 $n+k$，此时只要加上 $k$ 即可  
或者说存在 $a+c=2b$ 且上一步操作的是当前最大的那一堆  

考虑上一步要求操作的数是 $p$，有局面 $(n-k,n,n+k-p)$：  

- 此时如果把 $p$ 加到第一堆上，有 $(n-k+p,n,n+k-p)$，发现只要有 $k<p$，就仍然可以获胜（获胜需要 $n-k+p>n+k-p)$
- 此时如果把 $p$ 加到第二堆上，有 $(n-k,n+p,n+k-p)$，发现这样不太能必胜，于是此时需要让再上一步操作必定对第二堆进行  

考虑再上一步操作给出的是 $q$，有局面 $(n-k,n-q,n+k-p)$：  

- 如果加到第一堆上，有 $(n-k+q,n-q,n+k-p)$
	- 此时如果有 $(n-k+q)+(n+k-p)=2(n-q)$ 可以是一种必胜情况，解出此时 $p=3q$
   - 另有要求 $n-k+q>n+k-p \Rightarrow 2k<p+q\Rightarrow k<\frac{2}{3}p$
- 如果加到第三堆上，有 $(n-k,n-q,n+k-p+q)$
	- 此时根据之前解的 $p=3q$，仍然是一三堆的和是二堆的两倍
   - 但需保证 $n+k-p+q>n-k\Rightarrow k>\frac{1}{3}p$  

现在若存在合理的 $n,k,p,q$ 并且使得上面的条件全都满足，就逐个操作 $q,p,k$ 即可，整理出条件是：  

$$
\begin{cases}
a=n-k\\
b=n-q\\
c=n+k-p\\
p=3q\\  
k<\frac{2}{3}p\\
k>\frac{1}{3}p\\
\end{cases}$$

这样根据前面几个等式解出来就是  

$$
\begin{cases}
n=3b-2a-c\\  
q=2b-a-c\\
k=3b-2a-c\\
\end{cases}$$  

此时只要钦定 $b>c> a$，即可满足两个不等式  

```cpp  
long long aa,bb,cc;
inline void change(int o,long long p){
	if(!o) exit(0);
	else if(o==1) aa+=p;
	else if(o==2) bb+=p;
	else if(o==3) cc+=p;
}
inline int fuck(){
	int ff=0;
	if(aa+bb==(cc<<1)) printf("%lld\n",lib::max(aa,bb)-cc),ff=1;
	else if(aa+cc==(bb<<1)) printf("%lld\n",lib::max(aa,cc)-bb),ff=1;
	else if(bb+cc==(aa<<1)) printf("%lld\n",lib::max(bb,cc)-aa),ff=1;
	if(ff) return fflush(stdout),1;
	return 0;
}
int main(){
	long long a=read(),b=read(),c=read();
	aa=a;bb=b;cc=c;
	if(a>c) lib::swap(a,c);
	if(c>b) lib::swap(b,c);
	if(a>c) lib::swap(a,c);
	if(c>b) lib::swap(b,c);
	if(a>c) lib::swap(a,c);
	if(c>b) lib::swap(b,c);
	if(a>c) lib::swap(a,c);
	if(c>b) lib::swap(b,c);
	long long n=3*b-a-c,k=3*b-2*a-c,q=2*b-a-c,p=q*3;
	puts("First");fflush(stdout);
	printf("%lld\n",q);fflush(stdout);
	change(read(),q);
	if(fuck()) return 0;
	printf("%lld\n",p);fflush(stdout);
	change(read(),p);
	if(fuck()) return 0;
	printf("%lld\n",k);fflush(stdout);
	assert(fuck());
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

先钦点 $a<b<c$，不失一般性。

选择成为先手，如果出现等差数列，且后手上一次不能对最大的进行操作，那么输出公差就赢了。

发现如果让 $a,b$ 变成等差数列最后一项，都是让它们加上 $2c-a-b$．

那么先输出 $2c-a-b$，如果后手让 $a,b$ 增加的话就赢麻了，否则就是让 $c$ 增加。

那么再输出新的 $2c-a-b$，后手不能让 $c$ 增加，只能给 $a,b$ 增加，这样就又赢麻了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
#define mp std::make_pair
#define pb push_back
#define fir first
#define sec second
typedef std::pair<int, int> pii;
#define flh fflush(stdout);
int t;
pii a[4];
#define print(x) do{\
	int y = x;\
	printf("%lld\n", y);flh;\
	scanf("%lld", &t); if(!t) return 0;\
	for(int i = 1; i <= 3; ++i) if(a[i].sec == t) a[i].fir += y;\
	std::sort(a + 1, a + 4);\
}while(0)
signed main() {
	for(int i = 1; i <= 3; ++i) scanf("%lld", &a[i].fir), a[i].sec = i;
	std::sort(a + 1, a + 4);
	puts("First");
	print(a[3].fir*2 - a[2].fir - a[1].fir);
	if(t != a[3].sec) print(a[2].fir - a[1].fir);
	print(a[3].fir*2 - a[2].fir - a[1].fir);
	print(a[2].fir - a[1].fir);
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/1375/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1375F)

一个奇怪的做法。

首先我们猜测答案总是 First。考虑什么样的情况能够一步把对方一步干掉。方便起见我们假设 $a<b<c$，那么如果 $b-a=c-b$，并且上一步后手选择操作 $c$，那么我们只需令 $y=b-a$，不论后手再选择了哪一堆，总会出现两个石子数相同的堆，后手也就挂了。我们考虑怎样将所有情况归约到这种情况，经过仔细（反正这一步我是想了 ~1h）的思考，我发现对于 $a,b,c$ 成等差数列，且上一步选择的是 $a$ 对应的堆的情况也能把对方干掉，具体构造就是

> 令 $d=b-a$，然后
>
> - 第一步，选择 $y=d$，那么此时后手只能选 $c$​ 对应的堆，此时三堆分别是 $a,a+d,a+3d$
> - 第二步，选择 $y=5d$，那么如果后手选择第一堆，那么三堆分别是 $a+5d,a+d,a+3d$，回到了上面一次操作即可挂掉的情况。如果后手选择第二堆，那么三堆分别是 $a,a+6d,a+3d$，也回到了上面的情况。

我们考虑如何将一般性的情况归约到上面两种情况。我们假设 $d_1=b-a,d_2=c-b$，那么我们考虑这样一个做法，令 $y=d_1-d_2$，那么

- 如果后手选第一堆，就回到了上面等差数列、且一步即可干掉的情况
- 如果后手选第三堆，就回到了上面等差数列、且两步（第一次 $y=d$，第二次 $y=5d$）可以干掉的情况
- 如果后手选择第二堆，那么我们再次假设 $d_1’=b-a,d_2’=c-b$，并且假设 $b+d_1-d_2<c$ 恒成立，那么我们再令 $y=d’_1-d’_2$，就回到了上面的情况，又因为此时后手显然不能选第二堆，因此不会出现递归，也就证明了构造的正确性。

但是这个做法要能够行得通需要有一些条件，首先你第一次必须有 $y>0$，因此需有 $d_1>d_2$，还有就是第二步中我们有 $b+d_1-d_2<c$ 的假设，即 $d_1<2d_2$，因此该做法行得通的条件是 $d_2\le d_1<2d_2$（至于为什么左边可以取等，是因为 $d_1=d_2$ 的情况本身就是等差数列，可以归约到上面的第二种情况）。考虑怎样将其他情况转化为这两种情况，每次只需令 $y=d_1+d_2$ 直到 $d_2\le d_1<2d_2$ 成立即可。证明大概就，从第一次操作结束以后开始，我们每次操作的元素肯定会成为三个数的最大值对吧，那么从第一轮以后后手只能操作中间那个元素，因此问题可以转化为这样一个问题，有两个数 $x,y$，每次操作需执行 $\text{swap}(x,y)$，并令 $x\leftarrow x+y$，问什么时候 $y\le x<2y$ 成立，如果 $x\ge 2y$，那么进行一次操作以后 $x\le x+y<2x$ 符合条件；如果 $x<y$，那么换完以后 $x\leftarrow x+y,y\leftarrow x$，回到了 $x\ge 2y$ 的情况，因此我们总可以将问题转化为 $d_2\le d_1<2d_2$ 的情况。

```cpp
int _1,_2,_3;
pair<ll,int> a[4];int flg=0;
void getid(){sort(a+1,a+4);_1=a[1].se,_2=a[2].se,_3=a[3].se;}
void prt(){
	for(int i=1;i<=3;i++) for(int j=1;j<=3;j++) if(a[j].se==i)
		printf("%d%c",a[j].fi," \n"[i==3]);
	printf("%d %d %d\n",_1,_2,_3);
}
void oper(ll x){
	if(!x) return;
	printf("%lld\n",x);fflush(stdout);
	int p;scanf("%d",&p);
	if(!p) exit(0);
	if(p==_1) a[1].fi+=x,flg=1;
	if(p==_2) a[2].fi+=x,flg=2;
	if(p==_3) a[3].fi+=x,flg=3;
//	prt();
	getid();
}
void work(int stage){
	if(stage==2){
		oper(abs(a[3].fi-a[2].fi));
	} else {
		oper(abs(a[3].fi-a[2].fi));
		oper(5*abs(a[2].fi-a[1].fi));
		work(2);
	}
}
int main(){
	scanf("%lld%lld%lld",&a[1].fi,&a[2].fi,&a[3].fi);puts("First");
	a[1].se=1;a[2].se=2;a[3].se=3;getid();
	if(2ll*a[2].fi==a[1].fi+a[3].fi) work(1);
	else{
		ll d1=abs(a[2].fi-a[1].fi),d2=abs(a[3].fi-a[2].fi);
		while(d2*2<d1||d1<d2){
			oper(d1+d2);d1=abs(a[2].fi-a[1].fi);
			d2=abs(a[3].fi-a[2].fi);
		} //puts("-1");
		oper(abs(d1-d2));
		if(flg==1) work(1);
		else if(flg==2){
			d1=abs(a[2].fi-a[1].fi),d2=abs(a[3].fi-a[2].fi);
			oper(abs(d1-d2));
			if(flg==1) work(1);
			else work(2);
		} else work(2);
	}
	return 0;
}
```



---

## 作者：CSP_Sept (赞：0)

- **UPD20201009** 发现文章语言有事实性错误，~~及时~~修改，望通过！
- **UPD20201120** 发现排板出锅且文章语言有误，恳请通过！

___

这是对 @[WYXkk](/user/130151) 巨佬的[题解](/blog/WYXkk/solution-cf1375f)的详细说明。

___

给定 $a_1,a_2,a_3$ 三堆的数量，先返回一个很大的 $k$，假定后手把这 $k$ 个石子加入第 $x$ 堆（$1\le x\le 3$）。

此时更新：$a_x=a_x+k$。

再次返回 $2a_x-a_y-a_z(1\le x,y,z\le 3,x\ne y\ne z)$，为了方便，我们在代码里表示成 $3a_x-a_1-a_2-a_3$。

此时后手再加入到第 $i(1\le i\le 3)$ 堆，此时 $a_i=3a_x-a_1-a_2-a_3+a_i$。

当然下一轮后手只能加入第 $6-x-i$ 或第 $x$ 堆。

假定 $x=1,i=3$，则 $a_2=a_2,a_3=2a_1-a_2$，

- 下一轮后手加入第 $2$ 堆，显然我们只要返回 $k=a_1-a_2$ 即可。此时第 $1,2$ 堆相等，先手胜。
- 下一轮后手加入第 $1$ 堆，显然也只要返回 $k=a_1-a_2$。此时第 $1,3$ 堆相等，先手胜。

经过 $\sout{114514}$ 多次探究，我们发现，第三轮只要返回 $k=a_x-a_{6-x-i}$。

所以先手 $3$ 轮必胜。

所以可以得出 $\mathcal{Code:}$

```cpp
#include <cstdio>

#define Upd fflush(stdout)
#define ll long long
using namespace std;
const ll M = 200709131128;
ll a[10];
int main(){
	scanf("%lld%lld%lld", &a[1], &a[2], &a[3]);
	puts("First");
	printf("%lld\n", M);
	Upd;
	ll x;
	scanf("%lld", &x);
	a[x] += M;
	ll tmp = 3 * a[x] - a[1] - a[2] - a[3];
	printf("%lld\n", tmp);
	Upd;
	ll y;
	scanf("%lld", &y);
	a[y] += tmp;
	printf("%lld", a[x] - a[6 - x - y]);
	return 0;
}
```

---

## 作者：Clever_Jimmy (赞：0)

CF1375F 【Integer Game】

### 题意简述：

**这是一道交互题。**

给定三堆数量分别为 $a, b, c$ 的石子，先手每轮将给后手 $y_i$ 个石子，后手将这些石子合并到某一堆里。

后手不能在相邻的两轮中将先手给的石子合并到同一堆里，如果有两堆石子个数相同，则先手胜；若经过 $1000$ 轮后先手仍未获得胜利，则后手胜。

如果是你，你怎么保证你必胜？

$1 \le a, b, c \le 10^9$，$1 \le y \le 10^{11}$，保证 $a, b, c$ 两两不同。

[题目链接](https://codeforces.ml/contest/1375/problem/F)

### 解题思路：

不妨设 $a < b < c$，三堆名称分别为 $A, B, C$，可以证明，先手能在 $3$ 轮之内获胜。

取 $y_1 = 2c - a - b$：

- 若后手合并到 $A$ 中，则此时三堆石子分别为：$2c - b, b, c$。

  取 $y_2 = c - b$，则无论是合并到 $B$ 中，还是 $C$ 中，都会导致有两堆石子个数相同。

- 若后手合并到 $B$ 中，则此时三堆石子分别为：$a, 2c - a, c$。

  取 $y_2 = c - a$，则无论是合并到 $A$ 中，还是 $C$ 中，都会导致有两堆石子个数相同。

- 若后手合并到 $C$ 中，则此时三堆石子分别为 $a, b, 3c - a - b$。

  显然此时有 $a < b < 3c - a - b$，令 $a' = a, b' = b, c' = 3c - a - b$，则取 $y_2 = 6c - 3a - 3b$：

  - 若后手合并到 $a$ 中，则此时三堆石子分别为：$6c - 2a - 3b, b, 3c - a - b$。

    取 $y_3 = 3c - a - 2b$，则无论是合并到 $B$ 中，还是 $C$ 中，都会导致有两堆石子个数相同。

  - 若后手合并到 $b$ 中，则此时三堆石子分别为：$a, 6c - 3a - 2b, 3c - a - b$。

    取 $y_3 = 3c - 2a - b$，则无论是合并到 $A$ 中，还是 $C$ 中，都会导致有两堆石子个数相同。

至此，先手必胜。

### 参考代码：


```cpp
#include <bits/stdc++.h>
#define LL long long

LL a[4], x;
int rk[4] = { 0, 1, 2, 3 };

bool cmp(LL tx, LL ty) {
	return a[tx] < a[ty];
}

int32_t main() {
	scanf("%lld %lld %lld", &a[1], &a[2], &a[3]);
	puts("First"), fflush(stdout);
	
	std::sort(rk + 1, rk + 4, cmp);
	
	printf("%lld\n", 2 * a[rk[3]] - a[rk[1]] - a[rk[2]]), fflush(stdout);
	
	while(~scanf("%lld", &x) && x) {
		if(x == rk[1])
			printf("%lld\n", a[rk[3]] - a[rk[2]]), fflush(stdout);
		else if(x == rk[2])
			printf("%lld\n", a[rk[3]] - a[rk[1]]), fflush(stdout);
		else {
			a[rk[3]] += 2 * a[rk[3]] - a[rk[1]] - a[rk[2]];
			printf("%lld\n", 2 * a[rk[3]] - a[rk[1]] - a[rk[2]]), fflush(stdout);
		}
	}
	return 0;
}
```


---

