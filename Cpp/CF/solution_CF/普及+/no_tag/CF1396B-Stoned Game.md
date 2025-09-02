# Stoned Game

## 题目描述

T is playing a game with his friend, HL.

There are $ n $ piles of stones, the $ i $ -th pile initially has $ a_i $ stones.

T and HL will take alternating turns, with T going first. In each turn, a player chooses a non-empty pile and then removes a single stone from it. However, one cannot choose a pile that has been chosen in the previous turn (the pile that was chosen by the other player, or if the current turn is the first turn then the player can choose any non-empty pile). The player who cannot choose a pile in his turn loses, and the game ends.

Assuming both players play optimally, given the starting configuration of $ t $ games, determine the winner of each game.

## 说明/提示

In the first game, T removes a single stone from the only pile in his first turn. After that, although the pile still contains $ 1 $ stone, HL cannot choose from this pile because it has been chosen by T in the previous turn. Therefore, T is the winner.

## 样例 #1

### 输入

```
2
1
2
2
1 1```

### 输出

```
T
HL```

# 题解

## 作者：SSerxhs (赞：12)

对其他题解稍微补充一个证明

不妨设第 $i$ 堆石子最多，$sum=\sum\limits_{j\ne i}a_j$

当 $a_i>sum$ 时，先手只需要占住第 $i$ 堆必胜

否则，考虑最终状态必定只有一堆石子，现证明双方都可以通过设定操作策略为取走目前可取的石子最多的那堆做到最后一堆石子被拿干净：

假设不被拿干净，必定是出现了最多石子的那堆石子数目大于其他之和的状态（例如最终状态），逆推回去可以发现每两次取石子就有一个人取了这堆，逆推至初始状态与“否则”矛盾，不成立

故 $a_i\le sum$ 时最终状态必定是全部石子被取完，只需判断总石子数奇偶即可

```
#include <stdio.h>
int a[102];
int i,t,n,j,c;
int main()
{
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d",&n);
		for (i=1;i<=n;i++) scanf("%d",a+i);j=1;
		for (i=2;i<=n;i++) if (a[i]>a[j]) j=i;c=0;
		for (i=1;i<=n;i++) if (i!=j) c+=a[i];
		if ((a[j]>c)||((c^a[j])&1)) puts("T"); else puts("HL");
	}
}
```

---

## 作者：钓鱼王子 (赞：12)

看上去是一个博弈论的题，仔细分析一下。

如果某一堆比其他堆加起来还要多，那么先手必胜，可以一直选这一堆。

否则，两人不可能让某一堆比其他堆加起来还要多这种情况出现，否则自己必败，所以所有石子都会被取完，直接判断奇偶性即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t; 
}
int n,a[1000002],t,ans;
signed main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=read();
		sort(a+1,a+n+1);
		re int sum=0;
		for(re int i=1;i<n;++i)sum+=a[i];
		if(sum<a[n])puts("T");
		else{
			sum+=a[n];
			if(sum&1)puts("T");
			else puts("HL");
		}
	}
}
```


---

## 作者：寒鸽儿 (赞：9)

拿到题一脸懵逼。不过看一下数据范围 , $a_i \leqslant 100$ , $n \leqslant 100$ 。 这几乎说明我们需要模拟整个游戏的过程。  
那么最优方案可能就是取走某一个特定的石子。  
实际上取走当前可选的最高的那堆一定是最优方案。每次取走一颗石子之后 , 相当于我们在1轮之内锁定了这个堆。对方不能取 , 而我们仍然可以在下一轮继续取这一堆 , 当然我们也可以取别的堆。己方失败的情况只可能是己方将当前可选的最后一堆石子取完 , 在下一个对方的行动中对方仍然锁定了一堆石子还有的取。由于堆大小的变化只能是 $1$ , 易证锁定最高的石子一定是最优的方案 , 它能增加我们可能的行动步数。  
根据每次取可选的石子中最高的一堆的最优策略进行模拟即可通过。复杂度 $\mathcal{O((\sum a_i) \log n)}$ 
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define repp(i,a,b) for(int i=(a);i<(b);++i)
#define perr(i,a,b) for(int i=(b);i>(a);--i)

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<long long> VL;
typedef vector<double> VD;
typedef vector<int>::iterator itra;

priority_queue<int> q;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    int tests;
    cin >> tests;
    while(tests--) {
        int n, tmp;
        cin >> n;
        rep(i,1,n) {
            cin >> tmp;
            q.push(tmp);
        }
        bool flg = true;
        while(!q.empty()) {
            if(q.size() >= 2) {
                int r = q.top(); q.pop();
                int l = q.top(); q.pop();
                --r; --l;
                if(r) q.push(r);
                if(l) q.push(l);
            } else if(q.size() == 1) {
                cout << "T\n"; flg = false;
                q.pop();
            }
        }
        if(flg) cout << "HL\n";
    }
    return 0;
}
```

---

## 作者：灵茶山艾府 (赞：6)

根据规则，若一开始有一堆石子数量超过了其他石子的数量之和，那么 T 一直取这堆石子，HL 必然最后无石子可取，T 即可胜利。

否则，这两人总是可以选除了对方上一轮选过的那堆石子之外的最大的一堆石子。在这个过程中，没有一堆石子数量能超过其他石子的数量之和，两人可以把所有石子取完。由于每人一次只能取一枚石子，当石子个数之和为奇数时，T 获胜，否则 HL 获胜。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	var t, n, v int
	for Fscan(in, &t); t > 0; t-- {
		sum, max := 0, 0
		for Fscan(in, &n); n > 0; n-- {
			Fscan(in, &v)
			sum += v
			if v > max {
				max = v
			}
		}
		if max > sum-max || sum&1 > 0 {
			Println("T")
		} else {
			Println("HL")
		}
	}
}
```


---

## 作者：45dinо (赞：3)

奇怪的题目。

首先发现有两种结束的可能：
- 只剩一堆石子，一个人在上一轮取过了这一堆。
- 没有石子。

设第 $x$ 堆为石子最多的一堆，$s$ 表示 $\sum_{i=1}^{x-1}a_i+\sum_{i=x+1}^n a_i$，如果 $a_x>s$，先手必胜，因为此时第 x 堆比其它堆的石子加起来还多，先手只要一直取这一堆的石子即可。

如果 $a_x\leq s$ 又是什么情况呢？此时可以说明，结束游戏只有可能是因为第二种情况，因此只要讨论总石子数的奇偶性即可。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum=0,maxx=0,n,a,t;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		sum=maxx=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a);
			sum+=a;
			maxx=max(maxx,a); 
		}
		if(sum-maxx<maxx||sum&1)
			puts("T");
		else
			puts("HL");
	}
	return 0;
}
```


---

## 作者：king_xbz (赞：2)

# 前言

题解区都是博弈论？本蒟蒻~~十分懵逼~~。假如有想我一样不会博弈论，那就只能望题兴叹了吗？且看今日的**爆搜出奇迹**！

# 错误的贪心

说实话，每个萌新都有一个博弈梦，我也是这样的。拿到这道显然是结论题的题目，我便开始想，HL和T这二位的最佳策略是什么呢？手模一下发现，策略好像是**每次取最多的那一堆(maxn)一个**，这样的话，下家的剩余 可取棋子为$tot-maxn$，对方就更有可能会面临失利。我们使用大根堆来维护最大的一堆。

上一段**错误代码**：

```cpp
while(T--)
{
	priority_queue <int>q;
	int n;
	cin>>n;
	int x,tot=0;
	for(fint i=1;i<=n;i++)
	cin>>x,q.push(x),tot+=x;
	int ff=0,now=tot;//T went first
	while(!q.empty())
	{
		int hea=q.top();
		q.pop();
		tot-=1,hea-=1;
		now=tot-hea;
		if(now<=0||tot<=0)
		break;
		if(hea>0)
		q.push(hea);
		ff=ff^1;
	}
	if(ff==0)
	puts("T");
	else
	puts("HL");
}
```

我和同机房的dalao这样写都**WA**了。

# 暴力出奇迹

众所周知，搜索是个好东西，尤其是在$n≤100$的范围内。

既然每次取最大的一堆的结果是错的，那么我们就枚举每一种选取的情况，把每一个结果都遍历到。这样一定能拿到最优解。

代码非常短：

```cpp
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		int x,tot=0;
		for(fint i=1;i<=n;i++)
		cin>>a[i];
		int ans=dfs(0);
		ans==0?puts("HL"):puts("T");
	}
	return 0;
}

inline int dfs(int num)
{
	bool ff=0;
	for(fint i=1;i<=n;i++)
	if(a[i]!=0&&num!=i)
	a[i]--,dfs(i)==0?ff=1:ff=0;
	return ff;
}
```

# 贪心策略的改进

打完比赛后，看到题解区竟然有用堆AC的代码，不由感到**十分钦佩**。那么，我们究竟应该怎么改变呢？
我们有一个锁堆的操作，也就是这次我取得那一堆你下次不能取（~~霸气侧漏~~）而**我单纯的只是判断下一步能不能取而不是下一步的最优策略**，所以，~~我WA了，他AC了，我们都有光明的前程~~

部分代码：

```cpp
while(!q.empty()) 
{
	if(q.size()>=2) 
 	{
        int ta=q.top(); 
		q.pop();
        int tb=q.top(); 
		q.pop();
        ta-=1,tb-=1;
        if(tb>0) 
		q.push(tb);
        if(ta>0) 
		q.push(ta);
    } 
	else 
	if(q.size() == 1) 
    ff=0,q.pop();
}
```

# 正解的博弈

- **先手必胜**

在当有一堆石子数大于其他堆石子数的和时，先手必胜。因为先手可以一直取这堆石子，后手无法获胜。

```cpp
for(fint i=1;i<=n;i++)
    a[i]=read(),tot+=a[i],maxxs=max(maxxs,a[i]);
if(maxxs>tot-maxxs)
    cout<<"T";
```



- **分别的最优策略**

否则，两人不可能让某一堆比其他堆加起来还要多这种情况出现，否则自己必败。

- **其他情况的博弈**

所以所有石子都会被取完，直接判断奇偶性即可。

```cpp
if(tot%2==1)
    cout<<"T"<<endl;
else
    cout<<"HL"<<endl;
```



希望大家能够理解暴力，贪心，博弈这三种方法，并用代码实践出来。

祝大家AC愉快！



---

## 作者：Mars_Dingdang (赞：1)

又抢到了截止到2021年1月13日16点41分一道题的[最优解](https://www.luogu.com.cn/record/list?pid=CF1396B&orderBy=1&status=&page=1)，发篇题解纪念下。基础博弈论题目。

## 题目大意
有 $n$ 堆石子，每堆分别有 $a_i$ 个石子。

两者轮流取其中一个石子。但不能取上次对手取过的那一堆。特殊的，第一次取可以取任何一堆的石子。

当前先手取完要取的石子之后使对手无路可走时，先手获胜。

## 大体思路
1. 首先进行特判：

记 $sum=\sum\limits_{i=1}^n a_i$，则若有一堆石子比剩余所有石子都多，即 $\max\limits_{i=1}^n\{a_i\}>sum-\max\limits_{i=1}^n\{a_i\}$，则先手只需一直取这堆石子必胜。

2. 若不存在上述情况：

显然，最终必然仅存在一堆石子，参考 @[SSerxhs](https://www.luogu.com.cn/user/29826) 的证明方法：

>考虑最终状态必定只有一堆石子，现证明双方都可以通过设定操作策略为取走目前可取的石子最多的那堆做到最后一堆石子被拿干净。

>假设不被拿干净，必定是出现了最多石子的那堆石子数目大于其他之和的状态（例如最终状态），逆推回去可以发现每两次取石子就有一个人取了这堆，逆推至初始状态与“否则”矛盾，不成立。

可得结论：当 $\max\limits_{i=1}^n\{a_i\}\le sum-\max\limits_{i=1}^n\{a_i\}$，所有石子均被取完。因此只需判断 $sum$ 的奇偶性，若为奇数则先手取胜，否则后手取胜。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii=aa;ii<=bb;ii++)
#define Rep(ii,aa,bb) for(re int ii=aa;ii>=bb;ii--)
typedef long long ll;
typedef unsigned long long ull;
const int maxn=105;
namespace IO_ReadWrite{
	#define re register
	#define gg getchar()
	template <typename T>
	inline void read(T &x){
		x=0;re T f=1;re char c=gg;
		while(c>57||c<48){if(c=='-') f=-1;c=gg;}
		while(c>=48&&c<=57){x=(x<<1)+(x<<3)+(c^48);c=gg;}
		x*=f;return;
	}
	inline void ReadChar(char &c){
		c=gg;
		while(!isalpha(c)) c=gg;
	}
	template <typename T>
	inline void write(T x){
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar('0'+x%10);
	}
	template <typename T>
	inline void writeln(T x){write(x);putchar('\n');}
}
using namespace IO_ReadWrite;//习惯卡常
int a[maxn],n,T;
int main(){
	read(T);
	while(T++){//好多组数据
		int sum=0;//记录Σa[i]
		read(n);rep(i,1,n) read(a[i]),sum+=a[i];//输入
		sort(a+1,a+n+1,greater<int>());//从大到小排序
		if(a[1]>sum-a[1]) puts("T");//特判
		else if(sum&1) puts("T");
		else puts("HL");//判断奇偶
	}
	return 0;//完美
}
```

---

## 作者：Elma_ (赞：1)

## Description

[题目描述](https://www.luogu.com.cn/problem/CF1396B)

## Solution

一道很简单的博弈论。

首先考虑一种情况，即其中有一堆石子比其他所有堆的石子加起来还要多，显然，那么只要先手一直取这一堆中的石子，就能够必胜。

那么对于其他情况呢？似乎不是很好想。

我们可以手造几组样例玩一下，既然双方都不想让对方赢，那么他们就会保证任何时候都不会有任何一堆石子比其他所有的石子加起来更多。而在这种情况下，容易知道石子最终一定会被两人取完。所以只需要判断所有石子的总和的奇偶性即可。

## Code

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxn 105
using namespace std;

inline int read()
{
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}

int n, t;
int a[maxn];

int main(void)
{
	t = read();
	while (t--)
	{
		n = read();int sum = 0, maxa = 0;
		for (int i = 1;i <= n;i++)
			a[i] = read(), sum += a[i], maxa = max(maxa, a[i]);
		if (sum - maxa < maxa || sum & 1) puts("T");
		else puts("HL");
	}
	return 0;
}
```


---

## 作者：Strelitzia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1396B)

---

最近做博弈论刷到的题，写一下题解，记录下生活。

首先，对于 $n = 1$ 时，先手赢，这个很好分析吧。

然后，然后$\dots$

f-word,f-word,f-word,f-word

我们想一想，还可以发现一个事，如果有一堆的数量大于总和的一半，那么，你先手一直抓这堆就可以了。

但是后手怎么办呢，后手肯定要避免有一堆数量大于总和的一半，不然就输了。

先手亦是如此，所以判读综合奇偶就好了。


```cpp
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<typename T>void Swap(T &x,T &y) {T z = x;x = y;y = z;}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}
template<typename T>T Abs(T x) {return x < 0 ? -x : x;}

const int N = 100 + 5;

int T,n,sum;
int a[N];

int main () {
	read(T);
	while (T --) {
		read(n);
		sum = 0;
		for (int i = 1 ; i <= n ; ++ i) read(a[i]),sum += a[i];
		sort(a + 1,a + 1 + n);
		puts(n == 1 || a[n] > sum - a[n] || sum & 1 ? "T" : "HL");
	}
	return 0;
}
```

---

## 作者：Star_Cried (赞：0)

## 题意

题意的话我已经交了翻译了。在通过前引用一下：

>有$n$堆石子，每堆分别有$a_i$个石子。

>两者轮流取其中一个石子。但不能取上次对手取过的那一堆。特殊的，第一次取可以取任意一堆的石子。

>当前先手取完要取的石子之后使对手无路可走时，先手获胜。

>t组数据，每组数据给出n和a，输出谁必会胜利。若先手胜利输出“T”，若后者胜利输出“HL”。无引号。

>数据范围请参考原题。

做的时候真的就是猜结论，没想到一猜就中XD

## 做法

分两种情况：

1. 必胜态：当有一堆石子数大于其他堆石子数的和时，先手必胜。因为先手可以一直取这堆石子。
2. 其他情况，也就是不存在这样一堆石子时，石子总数奇数时先手必胜，偶数时先手必败。

对于2的情况，我们可以这样想：先手不可能去构造必胜态，因为这样操作后他就变成了后手；所以他只能尽可能远离第一种情况。每次操作的先手都会这样操作。于是石子最后会被取完。

取完的话用奇偶性判断就好了。

（这数据范围吓死了一大堆人……成功让输入成为时间复杂度瓶颈XD）

* 注意多组数据需要清零。（本人没清零使100%通过率降为90%）

虽然代码很简单，放一下吧。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,w=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	int n,mx,sum;
	inline void work(){
		n=read();
		mx=sum=0;
		for(int x,i=1;i<=n;i++)x=read(),sum+=x,mx=max(mx,x);
		if(mx>sum-mx)return (void)puts("T");
		if(sum&1)puts("T");
		else puts("HL");
	} 
}
signed main(){
	int T=read();
	while(T--)star::work();
	return 0;
}
```

---

## 作者：引领天下 (赞：0)

首先，如果所有石子堆里最大的一堆的石子数量超过了总量的一半，则一定是 `T` 胜利：他可以一直拿最大的一堆，必然会出现他的那一堆还没拿完，其他的石子都全部拿完了，即 `HL` 没得拿了。

否则考虑两个人的战况只取决于总数：总数是奇数，由于 `T` 是先手故 `T` 胜利；总数是偶数，则 `HL` 胜利。

```python
for _ in range(int(input())):
    n=int(input())
    a=list(map(int,input().split()))
    mx=max(a)
    sm=sum(a)
    if (mx<<1)>sm:
        print('T')
    else:
        print('T' if sm&1 else 'HL')
```

---

