# Thanos Nim

## 题目描述

Alice 和 Bob 正在玩一个有 $n$ 堆石子的游戏。保证 $n$ 是一个偶数。第 $i$ 堆有 $a_i$ 个石子。

Alice 和 Bob 轮流进行操作，Alice 先手。

每位玩家在自己的回合，必须选择恰好 $\frac{n}{2}$ 个非空石子堆，并且从每个被选中的堆中独立地取走任意正整数个石子。每个堆取走的石子数可以不同。在某一回合，如果剩下的非空石子堆少于 $\frac{n}{2}$ 个，则无法进行操作，该玩家判负。

给定初始局面，判断谁会获胜。

## 说明/提示

在第一个样例中，每位玩家每次只能从一堆石子中取石子（$\frac{2}{2}=1$）。Alice 会输，因为 Bob 可以模仿 Alice 在另一堆的操作，这样 Alice 会先无路可走。

在第二个样例中，Alice 可以在第一回合从第一堆取走 $2$ 个石子，从第三堆取走 $3$ 个石子，从而保证获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
8 8
```

### 输出

```
Bob
```

## 样例 #2

### 输入

```
4
3 1 4 1
```

### 输出

```
Alice
```

# 题解

## 作者：fighter (赞：8)

## 题意

[传送门](https://www.luogu.org/problemnew/show/CF1147C)

有$n$堆石子($n$为偶数)，每次玩家要选择恰好$\frac{n}{2}$堆石子，并从每一堆中任意拿走数量大于$0$的石子（每堆拿的数量可以不同）。问先手是否必胜。

## 分析

先上结论：当石子数最小的堆数量不超过$\frac{n}{2}$时，先手必胜，否则先手必败。

接下来是**感性理解**时间。

我们考虑最小堆数量超过$\frac{n}{2}$的情况。那么此时先手不管如何选取，都会选到一个最小堆，由于要求每轮取得石子数量大于$0$，那么最小堆的石子数必然会减少，而且此时取完后最小堆的数量就不会超过$\frac{n}{2}$。

然后到了下一轮，那么此时后手可以选择不包含最小堆的$\frac{n}{2}$堆，把它们全部变成最小堆，那么此时显然最小堆数量又将大于$\frac{n}{2}$。那么就将进入一个循环。

但是这个循环总会有终止的时刻，也就是当最小堆石子数量为$0$且堆数超过$\frac{n}{2}$时，游戏结束，最后操作的人获胜。观察上面的过程，我们发现只有后手才能把最小堆的数量变为超过$\frac{n}{2}$，而先手只能被动地将最小值变小，所以最后胜利者一定是后手。

所以得出结论：当石子数最小的堆数量不超过$\frac{n}{2}$时，先手必胜，否则先手必败。

```cpp
#include <bits/stdc++.h>
#define MAX 105
using namespace std;

int n;
int a[MAX];

int main()
{
    cin >> n;
    
    int mn = 0x3f3f3f3f, cnt = 0;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        if(a[i] < mn) mn = a[i], cnt = 1;
        else if(a[i] == mn) cnt++;
    }
    
    if(cnt <= n/2) puts("Alice");
    else puts("Bob");

    return 0;
}
```



---

## 作者：AKPC (赞：6)

### 题意
有 $n$ 个数字组成的数列 $a$，保证 $2\mid n$，要求两名玩家轮流操作，每次操作选取 $\dfrac{n}{2}$ 个数字并对于每个数字 $a_i$ 单独减去任意一个 $\geq1$ 且 $\leq a_i$ 的数，无法执行操作者失败，求先手是否必胜。先手为 Alice，后手 Bob。
### 思路
博弈论问题，显然总会有技巧。

先考虑 $n=2$。

我们假设 $a_2\geq a_1$，显然有两种情况：$a_1=a_2$ 和 $a_1<a_2$。

先考虑前者，Alice 肯定不能把 $a_1$ 减到 $0$，因为 Bob 在这之后可以把 $a_2$ 减到 $0$ 从而后手必胜，但是每次无论 Alice 减去什么数，Bob 都可以一次操作让 $a_1=a_2$，所以后手必胜。

考虑后者，则 Alice 可以选择 $a_2$ 并减去 $a_2-a_1$ 的值，构成 $a_1=a_2$，让 Bob 来到第一种情况，此时先手必胜。

然后延伸到 $n\geq 2$ 情况。

还是可以从某个数值变成 $0$ 的情况着手。如果有数字变成 $0$ 之后，则轮到谁，谁就可以把非 $0$ 的 $\dfrac{n}{2}$ 个数字改成 $0$ 然后获胜。

我们可以记录当前 $a$ 中值为 $\min\{a\}$ 的数字个数即 $cnt$，显然如果 $cnt>\dfrac{n}{2}$，则轮到的人不得不选到 $\min\{a\}$ 从而改变 $\min\{a\}$ 的值，这样之后 $cnt$ 最多只可能有 $\dfrac{n}{2}$ 了。

如果 $cnt\leq\dfrac{n}{2}$，则可以故意让 $cnt>\dfrac{n}{2}$ 来造成前面的局面。

如此往复总会出现 $cnt>\dfrac{n}{2}$ 的时候，轮到的人被迫把某个数改成 $0$。

再往前推算，可以得出最终结论：**如果数列最小值个数 $\leq\dfrac{n}{2}$ 则先手必胜，反之后手必胜。**

得出结论后直接模拟就行。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
int n,x,minn=1e18,cnt=1;
signed main(){
	n=read();
	for (int i=1;i<=n;i++){
		x=read();
		if (x<minn) cnt=1,minn=x;
		else if (x==minn) cnt++;
	}
	if (cnt*2<=n) cout<<"Alice";
	else cout<<"Bob";
	return 0;
}
```

---

## 作者：zr太弱了 (赞：5)

#本题题意还是较为简单的，把核心公式推出来就A了，具体的核心公式楼下两位巨佬都给出来了：

#### 如果石子数最小的堆小于等于$\frac{n}{2}$,则先手胜利，反之则先手必败

为什么呢？

当石子数最小堆数量超过$\frac{n}{2}$时

此时，先手一定会选到最小堆，即
#### 最小堆石子一定会减少
，此时后手可以将非最小堆的其他$\frac{n}{2}$堆更改为最小堆，所以最小堆数量又大于$\frac{n}{2}$了，然而因为最小堆石子数量被减少了，我们可以想象把这个循环一直延续下去，在之后的某个回合，最小堆石子数一定会变成0，后手最后一步操作将堆数减少到小于$\frac{n}{2}$即可获胜

以此推理，剩下所有情况都是先手获胜，即

#### 如果石子数最小的堆小于等于$\frac{n}{2}$,则先手胜利，反之则先手必败

要注意的是输出有一个换行

AC代码（~~我知道你们只会看这个~~）

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010],n;//本题数据好小啊
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
    sort (a+1, a+n+1);
    if (a[1]==a[n/2+1])
		cout<<endl<<"Bob"<<endl;
    else
    	cout<<endl<<"Alice"<<endl;
    return 0;
}
```


---

## 作者：liuyi0905 (赞：5)

很明显的一道博弈论，题目大意就不说了，下面我们来分析一下改如何解题。

假设最小堆数的数量超过了 $\frac{n}{2}$，那么先手一定会先将最小的堆数移走，这样的话最小堆数的数量最后会大于 $\frac{n}{2}$，最后终止的时候，最小堆数的数量会等于 $0$。

所以我们发现，每次操作都是后者将最小堆数的数量变成 $\frac{n}{2}$，先手只会被动的将最小堆数移走。

因此得出结论：如果最小堆数的数量超过了 $\frac{n}{2}$，那么后者胜；否则先者胜。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);//将a数组排序
    if(a[1]==a[n/2+1])cout<<"Bob";//如果最小堆数超过了一半，则输出Bob
    else cout<<"Alice";//否则输出Alice
    return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1147C Thanos Nim 题解
### 思路：
我们先假设最小堆数量超过一半，这个时候先手一定会选择最小堆去移走石头，最小堆石子数则被减少。这样循环往复，总有一次最小堆石子数会变为 $0$，这时后手只要把堆数减少到不足一半即可获胜，这是后手的必胜策略，后手赢，输出 `Bob`。

剩下的情况就全是先手必胜了（毕竟没有平局），先手赢输出 `Alice`。

注意：要先输出一个换行再输出答案。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1005], n;
signed main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    sort(a,a+n);
    if(a[0]==a[n/2])
    {
        cout<<endl<<"Bob";
    }
    else
    {
        cout<<endl<<"Alice";
    }
    return 0;
}

---

## 作者：big_news (赞：1)

发一下自己的做题思路

考虑若存在石子个数为 1 的堆，设堆数为 $x(x>0)$，则有情况如下：
1. $x > n/2$，则先手必败，因为无法避免在操作中形成空堆；
2. $x\le n/2$，则先手必胜，因为先手只要令操作后 $x>n/2$ 即可

剩下的唯一问题是不存在石子个数为 1 的堆的情况。

可以考虑放宽限制，即考虑石子个数为 2 的堆的情况。容易发现石子个数为 2 的情况依然可以归结到上述的两种讨论，因此直接猜出结论：先手必胜当且仅当石子个数最小的堆的数量 $\le n / 2$。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

int read(){
    int s = 0,ne = 1; char c = getchar();
    while(c < '0' || c > '9') ne = c == '-' ? -1 : 1, c = getchar();
    while(c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
    return s * ne;
}

int n, h, cnt, ai, mn = 101; // 无须数组

int main()
{
    freopen("_in.in", "r", stdin);
    n = read(), h = n >> 1;
    for(int i = 1; i <= n; i++) ai = read(), mn = ai < mn ? cnt = 1, ai : (ai == mn ? cnt++, mn : mn);
    if(cnt && cnt <= h) puts("Alice");
    else puts("Bob");
}
```

---

## 作者：_Clown_ (赞：0)

# C.Thanos Nim
先说结论：
> 如果石子最小堆数量不超过 $\frac{n}{2}$ 时，先手必胜，反之后手必胜

如果石子最小堆数量超过了 $\frac{n}{2}$，

那么先手无论怎么选，

一定会选到一些最小堆，

这就会使得最小堆的数量减少。

然后后手不妨将其余的非最小堆的一部分变成最小堆，

但是当最小堆数量变为 $0$ ，

而剩余堆超过  $\frac{n}{2}$ 时，

再操作一次即可获胜，

经过观察可知最后胜利者一定是后手。

那么我们就得到了结论：
> 如果石子最小堆数量不超过 $\frac{n}{2}$ 时，先手必胜，反之后手必胜

代码就不难写出了。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,A[1001];
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("IN.in","r",stdin);
	#endif
	register int i;cin>>N;
	for(i=1;i<=N;i++)cin>>A[i];
	sort(A+1,A+N+1);
	if(A[1]!=A[N/2+1])puts("Alice");
	else puts("Bob");
	return 0;
}
```

---

## 作者：shengheng (赞：0)

## 题意

$n$ 个石堆，每堆石头有 $a_i$ 个，两人轮流从 $\frac{n}{2}$ 个石堆中拿若干个石头，至少一个。移完后堆数小于 $\frac{n}{2}$ 者胜。

## 思路

若最小堆数的数量超过了 $\frac{n}{2}$，则 Alice 必取最小堆数。那么后面最小堆数的数量会大于 $\frac{n}{2}$ 。最小堆数的数量会变为 $0$。

结论：如果最小堆数的数量超过了 $\frac{n}{2}$ 则 Bob 胜，否则 Alice 胜。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
int n,a[1005];
int mian(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);
    if(a[1]==a[n/2+1])cout<<"Bob";
    else cout<<"Alice";
    return 0;
}
```


---

## 作者：DevOvO (赞：0)

$\huge{\text{题意}}$

$Alice$和$Bob$在$van$取石子游戏，共$N$堆石子（$N$保证为偶数），每次必须选$\frac{N}{2}$堆石子取出任意数量的石子，但不能取出$0$颗。$Alice$先手。问谁必胜。

---------------------------------

可以看出谁先取光了某一堆石子谁就输了。

一开始也没什么头绪。问了下旁边的神仙，说可以从序列中的最小值考虑。（怎么想到的？懵圈$ing$...）

设序列中最小值有$cnt$个。先$sort$一下$a_i$。

分两类考虑。

如果$cnt\le\frac{N}{2}$，那么先手可以把序列的后半部分取得和前半部分一样，然后每次都模仿后手做出的行为，这样就会保证后手首先取光某一堆石子。先手必胜。

如果$cnt>\frac{N}{2}$，那么先手无论怎么取，都必然会导致$cnt\le\frac{N}{2}$。因为先手不可避免的要改变$cnt-\frac{N}{2}$个最小石子堆，使得序列中的最小值改变，又因为先手改变的只有$\frac{N}{2}$个堆的值，所以新的最小值在序列中也必然不会超过 $\frac{N}{2}$个。然后此时的情况正好是$cnt\le\frac{N}{2}$的情况，也就是上面的那一种先手必胜的情况。此时先手必败。

核心就这三句。

```cpp
	sort (a+1, a+n+1);
	if (a[1]==a[n/2+1]) puts ("Bob");
	else puts ("Alice");
```

---

