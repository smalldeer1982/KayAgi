# Berland Poker

## 题目描述

The game of Berland poker is played with a deck of $ n $ cards, $ m $ of which are jokers. $ k $ players play this game ( $ n $ is divisible by $ k $ ).

At the beginning of the game, each player takes $ \frac{n}{k} $ cards from the deck (so each card is taken by exactly one player). The player who has the maximum number of jokers is the winner, and he gets the number of points equal to $ x - y $ , where $ x $ is the number of jokers in the winner's hand, and $ y $ is the maximum number of jokers among all other players. If there are two or more players with maximum number of jokers, all of them are winners and they get $ 0 $ points.

Here are some examples:

- $ n = 8 $ , $ m = 3 $ , $ k = 2 $ . If one player gets $ 3 $ jokers and $ 1 $ plain card, and another player gets $ 0 $ jokers and $ 4 $ plain cards, then the first player is the winner and gets $ 3 - 0 = 3 $ points;
- $ n = 4 $ , $ m = 2 $ , $ k = 4 $ . Two players get plain cards, and the other two players get jokers, so both of them are winners and get $ 0 $ points;
- $ n = 9 $ , $ m = 6 $ , $ k = 3 $ . If the first player gets $ 3 $ jokers, the second player gets $ 1 $ joker and $ 2 $ plain cards, and the third player gets $ 2 $ jokers and $ 1 $ plain card, then the first player is the winner, and he gets $ 3 - 2 = 1 $ point;
- $ n = 42 $ , $ m = 0 $ , $ k = 7 $ . Since there are no jokers, everyone gets $ 0 $ jokers, everyone is a winner, and everyone gets $ 0 $ points.

Given $ n $ , $ m $ and $ k $ , calculate the maximum number of points a player can get for winning the game.

## 说明/提示

Test cases of the example are described in the statement.

## 样例 #1

### 输入

```
4
8 3 2
4 2 4
9 6 3
42 0 7```

### 输出

```
3
0
1
0```

# 题解

## 作者：xiaomuyun (赞：6)

# CF1359A Berland Poker 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1359A)
## 正文
本蒟蒻第一次写正式的题解，如果有些繁琐，请见谅。~~请细嚼慢咽~~

细心的 OIer 们都知道，题面中有这样一个括号：

> $(n$ is divisible by $k)$

意思就是说 $n$ 能被 $k$ 整除。所以每个人拿的牌的数量肯定是一样的。然后我们又已经知道每个人拿的牌的数量（即 $\dfrac{n}{k}$，$n/k$，接下来我会将它称为 $c$），就会发现答案只有以下几个情况：

1. $m\le c$，这样只需把所有 joker 给一个人即可，因此得分是 $m$。
1. $m>c$，这样就要先尽量给一个人 joker，等他拿的 joker 的总数达到上限 $c$ 时，他手里的 joker 数量就变成了 $c$，然后就要将剩下的 joker **平均分**给其他人。如果我们设剩下的 joker 的数量为 $s$，则得分为 $c-\left\lceil\dfrac s{k-1}\right\rceil$【（**知道为什么用向上取整的同学可以跳过**）'$\lceil$' 和 '$\rceil$' 是[**向上取整**](https://baike.baidu.com/item/ceil/10931457?fr=aladdin)的意思，用这个东西是因为：如果 $s$ 能够整除 $k-1$，即剩下的 joker 数量正好能够平分给其他人，则这个式子的答案就和 $c-\dfrac s{k-1}$ 相等了；但是如果 $s$ 除以 $k-1$ 之后还有余数的话，那么这剩下的 $s\bmod k-1$ 个 joker 就再分散开分给 $k-1$ 个人（当然有些人没有再获得，但只要有一个人获得了就行了，那样拿了第二多 joker 的人手上 joker 的数量就改变了），因此拿了第二多 joker 的人手上 joker 的数量又加了 $1$，向上取整正好能体现这一点】。

代码如下：
```cpp
#include<cstdio>
#include<cmath>
 
using namespace std;
 
int n,m,k,t;
 
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;++i){
		scanf("%d%d%d",&n,&m,&k);//输入不解释
		int c=n/k,s=m-c;
		if(m<=c) printf("%d\n",m);//第一种情况
		else printf("%d\n", ceil((double)(s/(k-1))) );//第二种情况,ceil是向上取整函数,因此需要调用cmath库
	}
	return 0;
}抄代码可耻
```
## 总结
写完这短短的题解，本蒟蒻也对这题有了更深刻的理解。最后感谢大家的阅读，制作不易，走之前不要忘了点个赞哦。

共勉。

---

## 作者：BMTXLRC (赞：3)

$\texttt{Upd 2021/07/15}$ 修改了部分公式

### 分析：

如果有一个人拿的牌非常好，首先他最多有 $\dfrac{n}{k}$ 张牌。

讨论：

1. $m<\dfrac{n}{k}$，即他把所有的王都拿走了，还不够他自己的牌数。

2. $m\geqslant \dfrac{n}{k}$，即他可以拿走一部分的王，但是有一些王因为他自己的牌数限制而拿不到。\
此时拿到的第二多王的玩家将会拿走 $\left\lceil\dfrac{m-maxn}{k-1}\right\rceil$ 张牌，$maxn$ 表示拿到最多王的玩家拿到的王数。

总结一下就是：

$\begin{cases}maxn=\max\left(m,\dfrac{n}{k}\right)\\\\minn=\max\left(0,\left\lceil\dfrac{m-maxn}{k-1}\right\rceil\right)\end{cases}$

答案为 $maxn-minn$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,T;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&n,&m,&k);
		int maxn=min(n/k,m);
		int minn=max(0,(m-maxn+k-2)/(k-1));
		printf("%d\n",maxn-minn);
	}
}
```


---

## 作者：copper_ingot (赞：1)

这题是一道比较简单的思维题。

如果要让第一和第二名差距最大，那么肯定是要第一拿的尽量多，第二拿尽量少。

分两种情况考虑：

+ $m \le \frac{n}{k}$ 时，让第一名拿走全部的王牌，得分是 $m$。

+ $m > \frac{n}{k}$ 时，首先让第一名拿满 $\frac{n}{k}$ 张王牌，剩下 $k - 1$ 个人平分其他 $m - \frac{n}{k}$ 张牌，得分是 $\frac{n}{k} - \frac{m - \frac{n}{k}}{k - 1}$ 分，化简得到 $\frac{n - m}{k - 1}$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t; double n, m, k;
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%lf%lf%lf", &n, &m, &k);
		if (m <= n / k){printf("%d\n", (int)m); continue;}
		printf("%d\n", (int)((n - m) / (k - 1)));
	}
	return 0;
}
```

---

## 作者：asas111 (赞：1)

### 思路

这题有 $2$ 种情况，需要分类讨论。
- $m\le\frac{n}{k}$，所有的王都可以在一个人手上，答案就为 $m$。
- $m>\frac{n}{k}$，这时手上第一多王的人最多有 $\frac{n}{k}$ 个王。余下的王均分给剩下 $k-1$ 个人，每个人有 $\frac{m-\frac{n}{k} }{k-1}$ 个王，答案为 $\frac{n}{k} -\frac{m-\frac{n}{k} }{k-1}$，化简后答案就是 $\frac{n-m}{k-1}$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		double n,m,k;
		cin>>n>>m>>k;
		cout<<((m<=n/k)?m:(int)((n-m)/(k-1)))<<" ";
	}
	return 0;
}
```



---

## 作者：帝千秋丶梦尘 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1359A)

因为减的是第一多的纸牌减第二多的纸牌

所以第一多的要分最多的纸牌，而另外的剩下人员分掉

$n/k$就是每个人能分到的纸牌个数

那当这个数比$m$大的时候，这个人能拿到的牌比王牌多

那就可以把王牌全给他

所以最大值就是$m$

而当这个数比$m$小时

那就给第一多的$n/k$张王卡

剩下的$(m-n/k)$张王卡就平均分给其他人（全员$-1$）

最后减一减就好了

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,sum;
int main(void)
{
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k;
		sum=n/k;
		if(sum<m)
		{
			m-=sum;
			if(m%(k-1)==0) m=m/(k-1);
			else m=m/(k-1)+1;
			cout<<sum-m<<endl;
		}
		else cout<<m<<endl;
	}
	return 0;
}
```


---

## 作者：Werner_Yin (赞：1)

## 题意
给出 $n,m,k$ ，表示 $k$ 名玩家打牌，共 $ n$ 张牌，$m$ 张王，保证 $k|n$ ，记得分为 拿到最多王的玩家手中王数 $-$拿到第二多王的玩家手中的王数，求得分最大值
## 思路
首先，每人有 $n/k$ 张牌，

假设有玩家手气特好，抽一张一个王，那他最多有 $maxn=\max\{m,n/k\}$ 张牌，

在此情形下，还剩 $m-maxn$ 张王，则拿到第二多王数应该为 $\left\lceil\dfrac{m-maxn}{k-1}\right\rceil$ 。

于是，两者相减，这题就没了。
## 代码
```cpp
#include<bits/stdc++.h>
#define re read()
using namespace std;
const int MAXN=1e5;
int read(){
	#define ge getchar()
	int x=0,sgn=1;char ch=ge;
	for(;!isdigit(ch);ch=ge)if(ch=='-')sgn=-1;
	for(;isdigit(ch);ch=ge)x=(x<<1)+(x<<3)+(ch^48);
	return x*sgn;
}
int n,m,k,T;
int main (){
	T=re;
	while(T--){
		n=re;m=re;k=re;
		int maxn=min(n/k,m),minn=max(0,(m-maxn+k-2)/(k-1));
		printf("%d\n",maxn-minn);
	}
	return 0;
}
```


---

## 作者：Pink_Cut_Tree (赞：0)

# CF1359A Berland Poker 题解

### 优质好题意（含划重点）

给出 $n,m,k$，表示 $k$ 名玩家打牌，共 $n$ 张牌，$m$ 张王，保证 $k\mid n$，记得分为 拿到**最多**王的玩家手中王数 $-$ 拿到**第二**多王的玩家手中的王数，求得分最大值。

题目翻译漏掉的一点是，共有 $T$ 组测试数据，在此加上。

### 解析

观察题目，发现 $k\mid n$，算出如果平均分配这些牌，大家能拿多少（为了方便表示，下文将其称为 $pj$），然后分类讨论。

1. $m\leq pj$。即所有牌都分给一个叫做 PCT 的人（不用管他是谁），其余人都拿 $0$ 张。输出 $pj$ 即可。

1. $pj<m$。那就将 $\frac{n}{k}$ 张牌分给 PCT，其余牌平均分给剩余的人。需要计算一下，小心**精度误差**。

### 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int T,n,m,k;
int main(){
	ios::sync_with_stdio(0); //关闭读写同步 
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		int pj=n/k; //计算平均分 
		if(pj>=m){
			cout<<m<<"\n"; //直接输出m 
		}
		else{
			cout<<pj-ceil(1.0*(m-pj)/(k-1))<<"\n"; //另外的情况 
		}
	}
return 0;
}
```


---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1359A)&[CF 链接](http://codeforces.com/problemset/problem/1359/A)

## 题目简述

共有 $T$ 组数据。

对于每组数据给出 $n,m,k$，表示 $k$ 名玩家打牌，共 $n$ 张牌，$m$ 张王，保证 $k \mid n$，记得分为**拿到最多王的玩家手中王数减去拿到第二多王的玩家手中的王数**，求得分**最大值**。

## 思路

经典贪心题。

首先需特判**两种情况**：

1. $m$ 为 $0$。

2. $n \div k \ge m$。

首先对于情况 $1$，直接输出 $0$ 即可，因为**没有王**。

对于情况 $2$，直接输出 $m$ 即可，构造就是**把 $m$ 张王全给一个人，这样最大差就是** $m$。

对于一般情况，就先把**能给的王全给一个人**，**其余王平均分即可**。

具体**代码**实现如下：

```cpp
#include<iostream>
using namespace std;

int T, n, m, k;

int main(){
	cin >> T;
	while(T --) {
		cin >> n >> m >> k;
		int num = n / k; // 计算每个人牌数
		if(m == 0) { cout << "0\n"; continue; } // 特判情况 1
		if(num >= m) { cout << m << endl; continue; } // 特判情况 2
		cout << num - (m - num) / (k - 1) - ((m - num) % (k - 1) != 0) << endl; // 公式，上有构造及证明
	}
	return 0;
}

```

[提交记录](https://www.luogu.com.cn/record/118591572)

$$\text{The End!}$$

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1359A) & [CF链接](http://codeforces.com/problemset/problem/1359/A)

## 题意简述：

把 $n$ 张牌平均分给 $k$ 个人，求拿到最多王的玩家手中王数 $-$ 拿到第二多王的玩家手中的王数的最大值。

## 思路分析：

如果没有王，直接输出 $0$，如果每个人平均分得的牌数大于 $m$，那就把 $m$ 张牌全部分给一个人，所以输出 $m$。否则就计算一下，先把 $n/k$ 张牌分给一个人，再把剩下的牌类似于抽屉原理分给 $n-1$ 个人。

## 代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,m,k;
int main(){
	int T;
	cin>>T;//T组数据
	while(T--){
		cin>>n>>m>>k;
		if(m==0){//如果没有王
			cout<<0<<endl;//输出0
			continue;
		}
		int x=n/k;//x表示每人有几张牌
		if(x>=m){//如果王数不够x
			//就是把所有王都给一个人
			cout<<m<<endl;//输出m
			continue;
		}	
		cout<<x-ceil(1.0*(m-x)/(k-1))<<endl;//否则把牌尽量平均分给剩下k-1个人
	}
	return 0;
}
```

---

## 作者：stswkl (赞：0)

# CF1359A Berland Poker 题解

## 题意：

有 $n$ 张牌，其中有 $m$ 张王，还有 $k$ 个人，求得到王数最大的人得到的王数减去得到王数第二大的人得到的王。

## 思路：

贪心。要想让这个数最大，王数最大的人得到的王数要**尽可能大**，王数第二大的人得到的王数要**尽可能小**，题目保证了 $n$ 可以整除 $k$ ，所以每个人得到的牌数是**一样**的，设这个牌数为 $tmp$ 。先给一个人分尽量多的王，保证他的王数最多，此时会出现两种情况：

- $m \le tmp$ ，代表可以把王**全部**给他，其他人没有王，答案为 $m$ 。
- $m > tmp$ ，代表即使他的手牌全是王，即他手上有 $tmp$ 张王，但还剩 $m-tmp$ 张王，剩余的王要**平均**分配给剩下的人，以保证王数第二大的人得到的王数要**尽可能小**，王数第二大的人得到的王数即为 $tmp - \left \lceil \cfrac{m - tmp}{k - 1} \right \rceil$ （ $\left \lceil \right \rceil$ 为向上取整符号）。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n,m,k,tmp,ans;
int mian()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>k;
        tmp=n/k; //算出每个人可以分到几张牌
        if(m<=tmp)ans=m; //可以把王全部给第一个人
        else ans=tmp-(m-tmp+k-2)/(k-1); //不可以把王全部给第一个人，剩下的牌平均分
        cout<<ans<<'\n';
    }
    return O;
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，$n/k$ 是每名玩家手中牌的数量。设 $f=\frac{n}{k}$，有两种情况：

- 当 $m\le f$ 时，把王全部给一名玩家，这时得分是 $f$。
- 当 $m>f$ 时，把 $f$ 张王给一名玩家，再把剩下的王分给其他玩家，因为第二多的玩家分到 $\lfloor\frac{m-f}{k-1}\rfloor$ 张无法保证分完，所以第二多的玩家应该分到 $\lceil\frac{m-f}{k-1}\rceil$ 张，这时得分是 $f-\lceil\frac{m-f}{k-1}\rceil$。

另外，注意向上取整的写法。
## 代码
```python
a=int(input())
for b in range(a):
    c,d,e=map(int,input().split())
    f=int(c/e)
    if f>=d:
        print(d)
    else:
        g=(d-f)/(e-1)
        if g%1==0:
            g=int(g)
        else:
            g=int(g)+1
        print(f-g)
```

---

## 作者：zgy_123 (赞：0)

首先，我们读完题就可以想到这是一道贪心 + 构造题。

将数据分两种情况：

（为了方便，这里将 $n/k$ 替换为 $x$）

1. 王可以只在一个玩家的手中，即 $m \le x$，这是只需输出 $m$ 即可。

2. $m > x$，这时候，其他玩家也必须得到一些牌，为了让结果尽量大，其他玩家要分摊。计算一下，得到以下结果：
- 如果 $(m-x) \mod (k-1) = 0$，即剩下的王能够分完，这时候答案就是 $x-(m-x)/(k-1)$。
- 其他情况，答案为 $x-(m-x)/(k-1)-1$。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,m,k;
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		if(m<=x) cout<<m<<endl;//可以满足所有王都在同一名玩家手中
		else{
			m-=x,k--;//先给一名玩家分满
			int y=(m%k==0)?(m/k):(m/k+1);//计算剩下玩家牌数的最大值
			cout<<x-y<<endl;
		}
	}
	return 0;
}

```

---

## 作者：清清老大 (赞：0)

## 思路

因为要使差尽量大，所以要让减数尽量小，被减数尽量大。

所以，拿到最多王的玩家拿到的王的数量就要尽量多，一共有 $m$ 张王，每人 $\frac{n}{k}$ 张牌，最多可以拿 $\min(m,\frac{n}{k})$ 张大王。

拿到第二多王的玩家手中的王数要尽量少，如果大王都被拿完了，只能拿 $0$ 张，如果没有被拿完，能拿 $\lceil \frac{m - \min(m,\frac{n}{k})}{k - 1 } \rceil$ 张牌。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T --)
    {
        int n,m,k;
        cin >> n >> m >> k;
        cout << min(n / k,m) - max(0,(m - min(n / k,m) + k - 2) / (k - 1)) << endl; // 加上 k-2 是为了向上取整
    }
}
```


---

## 作者：银河AI (赞：0)

### 解题思路

首先考虑 $m \le \frac{n}{k}$ 的情况。

那么显然，最优策略就是让一个人拿走所有的王，那么答案就是 $m$ 。

然后再考虑 $m > \frac{n}{k}$ 的情况。

如果 $m \equiv 0 \pmod {k-1} $ 那么显然均摊是最好的选择,此时答案就为 $\frac{n}{k}-\frac{m-\frac{n}{k}}{k-1}$。

反之，则由抽屉原理可知最后答案是 $\frac{n}{k}- \lfloor \frac{m-\frac{n}{k}}{k-1} \rfloor+1$。

### AC代码

```cpp
//l=n/k;
//if  m<=l   ->ans=m
//else      qwe=m-l   
//    if  qwe%(k-1)==0     ->ans=l-qwe/(k-1)
//    else                 ->ans=l-(1+qwe/(k-1))
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m,k;
int main(){
	scanf("%d",&t);
	while(t--){
		int ans;
		scanf("%d%d%d",&n,&m,&k);
		int l=n/k;
		if(m<=l) ans=m;
		else{
			int qwe=m-l;
			if(qwe%(k-1)==0) ans=l-qwe/(k-1);
			else ans=l-(qwe/(k-1)+1);
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：Fan_Tuan (赞：0)

# CF1359A题解

## 思路 ：
开始我们可以算出每个人分完牌之后手中的牌数**p**，当**m** <= **p**时， 那么答案就是**m**。
否则，当**m** > **p** 时， **拿到最多王的玩家手中王数** = **p**，
**第二
多的手中王数** = m/(k - 1) 【注意当m%(k - 1) == 1时，**第二多的手中王数**要+1】。


------------


# 代码

```c
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int t;
int main() {
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		int n, m, k, max1, max2;
		scanf("%d%d%d", &n, &m, &k);
		if (m >= n/k)  {
			m = m - n/k, max1 = n/k;
			if (m % (k - 1) == 0)
			max2 = m/(k - 1);
			else max2 = m/(k - 1) + 1;
			printf("%d\n", max1 - max2);
		}
		else {
			printf("%d\n", m); 
		} 
	}
	return 0;
}
```


---

## 作者：LucasXu80 (赞：0)

PY 档福利，来看看 Python 3 代码吧！

~~（自学 PY 蒟蒻调了20分钟）~~

### 声明：本题解大致思路与 @Werner_Yin 大佬的一致，只不过对萌新更为友好，包含更多的分析和讲解。

让我们开始吧，先看思路。

首先拿到题目，你需要看懂题目后看样例。CF 的题比较友好，大多都有样例解释。

看完题，你大致知道这题应该是让你分别算最大和次大分数然后作差。先来看最大，因为相对简单。

第一反应是：他把$m$张王全拿走不就好了吗。

但是样例$2$就会把你打脸了。因为总共有$2$张王牌，但是每位玩家却只能分到$1$张牌。

想到这里，我们就大致知道：这个最大值和$m,n/k$这两个数有关。由于$k|n$，$n/k$一定是整数，无需考虑是否向上取整等。

重点在于是取**最大值还是最小值**，这时候需要你静下心来思考一下。

你会发现，根据样例$2$，有$2$张王牌、每位玩家拿$1$张，而最后最大值是$1$。可见需要用**最小值**。

$maxx=min(m,n/k)$.

------------

接下来是次大值。注意到此时应该还剩下$(m-maxx)$张王牌，设之为$x$。

此时，根据**抽屉原理**（不熟悉的同学可以去[这里](https://baike.baidu.com/item/%E6%8A%BD%E5%B1%89%E5%8E%9F%E7%90%86/233776?fr=aladdin)），必定有一个人拿到至少$\left\lceil\dfrac x{k-1}\right\rceil$张王牌。

对这个结论的证明使用反证法：（证明中的“所有人”指除了王牌数最多者的所有人，即$k-1$人）

------------

假设没有人拿到了$\left\lceil\dfrac x{k-1}\right\rceil$张或更多的王牌，那么最多的情况下所有人都拿到了$\frac x {(k-1)}-1$张王牌。这个式子$=\frac {x-k+1} {k-1}$。

那么所有人总共拿到$x-k+1$张王牌。由于$k>=2$（题面中有），所以$x-k+1<x$，与“所有人共拿到$x$张王牌矛盾。”

所以假设不成立。原命题得证。

------------

当然这一证明可能有一些漏洞，主要是让大家感受一下这一结论，勿喷。

这样我们把两个数一减，就可以了。

我们来看代码。

```python
def ceil(a,b): #定义向上取整函数
    if a%b==0: return a//b #可以被整除，直接输出两数的商（//运算符指自动向下取整的除法）
    else: return a//b+1 #向上取整，即向下取整+1
t=int(input()) #输入t
for i in range(t): #t组数据
    n,m,k=map(int,input().split()) #输入三个数
    maxx=min(m,n//k) #套公式
    minn=ceil(m-maxx,k-1) #套公式
    print(maxx-minn) #输出两数之差，print()函数自带换行
```

这篇题解就到这里了，求赞！

---

## 作者：Ash_Dr (赞：0)

**大致题意就是将n个牌分给k名玩家(n个牌中包含m张Joker牌)，求手持最多Joker牌与手持第二多Joker牌的人的差值的最大值**

首先特判m=0这种情况，然后判断$\large\frac{n}{k}$是否大于m，如果大于m，证明手持最多牌的那个人一定能拿上所有Joker 直接输出m即可，否则我们让手持最多牌的那个人手里全拿Joker即$\large\frac{n}{k}$

然后我们需要确定排名第二的人，首先我们做一个取模运算，我们要尽量将剩余牌均摊到每个人身上。

如果剩余的$(m-\frac{n}{k})<k-1$ 则证明剩下的人不能保证人手一张 输出$\large\frac{n}{k}-1$即可 

否则 我们需要进一步判断均摊最多的拿那个人手里有几张Joker
具体细节见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main() {
    cin>>t;
    while(t--) {
        int n,m,k;
        cin>>n>>m>>k;
        if(m==0) {
            cout<<0<<endl;
            continue;
        }//特判1
        else {
            if(n/k>=m) {
                cout<<m<<endl;
                continue;
            }//特判2
            else {
                if(m-n/k<=k-1) {
                  cout<<n/k-1<<endl;  
                }
                else {
                    int t;
                    if((m-n/k)%(k-1)==0) t = (m-n/k)/(k-1);
                    else t = (m-n/k)/(k-1)+1;//是否刚好整除还是多了一点
                    cout<<n/k-t<<endl;
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：45dinо (赞：0)

很久没写题解了。。。

由于有这样一句话：

>记得分为 拿到最多王的玩家手中王数 - 拿到第二多王的玩家手中的王数。

得分可以写成 $a-b$ 。

所以可以想到要在最大化 a 的前提下，降低 $b$ 。

分情况讨论：

- $m\leq\frac n k$， 此时 $a=m,b=0$。
- $m>\frac n k$， 此时 $a=\frac n k$，为了让b尽可能小，应该让后 $k-1$ 个人拿的王数尽可能相同，所以 $b=\lceil \dfrac {m-\frac n k} {k-1} \rceil$ 。

---

## 作者：ys_kylin__ (赞：0)

这一道题是一道简单的思维题。

首先，我们先思考：如何使第一与第二差距最大，那当然是把全部王分给第一个人，而之后所有王要让剩下的人领的最少，自然就是平均分配。也就是说，若每人领到的牌数都是 $n/k$，判断两种情况：

1. 王的数量不如 $n/k$，则答案为 $m$。
2. 王的数量比 $n/k$ 多，则答案为`n/k-(m-n/k+k-2)/(k-1)`，也就是 $n/k$ 减去平均分配后每人领的王的数量。

注意：有多组数据，翻译没提到。

代码很简单，接下来贴上：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m,k;
		scanf("%d%d%d",&n,&m,&k);
		if(n/k>=m) printf("%d\n",m);//王比人均牌多
		else printf("%d\n",n/k-(m-n/k+k-2)/(k-1));//公式
	}
}
```

---

