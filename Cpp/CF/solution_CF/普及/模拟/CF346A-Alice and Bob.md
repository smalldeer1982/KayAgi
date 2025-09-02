# Alice and Bob

## 题目描述

It is so boring in the summer holiday, isn't it? So Alice and Bob have invented a new game to play. The rules are as follows. First, they get a set of $ n $ distinct integers. And then they take turns to make the following moves. During each move, either Alice or Bob (the player whose turn is the current) can choose two distinct integers $ x $ and $ y $ from the set, such that the set doesn't contain their absolute difference $ |x-y| $ . Then this player adds integer $ |x-y| $ to the set (so, the size of the set increases by one).

If the current player has no valid move, he (or she) loses the game. The question is who will finally win the game if both players play optimally. Remember that Alice always moves first.

## 说明/提示

Consider the first test sample. Alice moves first, and the only move she can do is to choose 2 and 3, then to add 1 to the set. Next Bob moves, there is no valid move anymore, so the winner is Alice.

## 样例 #1

### 输入

```
2
2 3
```

### 输出

```
Alice
```

## 样例 #2

### 输入

```
2
5 3
```

### 输出

```
Alice
```

## 样例 #3

### 输入

```
3
5 6 7
```

### 输出

```
Bob
```

# 题解

## 作者：liuyi0905 (赞：10)

# [CF346A](/problem/CF346A) solution：
一道博弈论裸题。
### 题目大意：
从 $n$ 个数字中选出两个整数 $x,y$，并且 $|x-y|$ 不在序列中，就将 $|x-y|$ 加入序列。如果有一方无法操作时，对方获胜。`Alice` 为先手，且双方都是最有策略。要你求出胜者是谁。
### 思路：
我们照题目里做一遍，发现操作过程很想**辗转相除法**，应为 $d|x,d|y\Rightarrow d|(|x-y|)$，$x|y$，表示 $x$ 整除 $y$，所以 $d=\gcd\{a_i\}$。可以枚举一遍用库函数求出 $\gcd\{a_i\}$。

设 $m=\max\{a_i\}$，在其中一个玩家无法操作时，剩下的数列一定是 $[d,2d,3d,...,m]$，也就是一个公差为 $d$ 的等差数量，各位 $\mathsf{OIer}$ 可以自己去证明一下。

最后得出结论：
> 应为最后总操作次数为 $\lfloor\frac{m}{d}\rfloor-n$，如果为奇数，则先手胜；否则后手胜。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,m,d;//m为序列最大值，d为序列最大公因数
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x,m=max(m,x),d=__gcd(x,d);
	puts((m/d-n)%2?"Alice":"Bob");//判断答案的奇偶性
	return 0;
}
```

---

## 作者：b6e0_ (赞：5)

[CF题面传送门](https://codeforces.com/contest/346/problem/A) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF346A) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF346A)

这题不该评蓝啊？

我们可以发现最终无法操作的序列的形式一定是这样的：$k,2k,3k,\cdots nk$。否则有两种情况：

1. 数列中有一个数 $x$ 不是 $k$ 的倍数。这时，可以构造出 $x\bmod k$ 和 $k-x\bmod k$，如果这两个数都存在，也可以构造出 $k\bmod(k-x\bmod k)$ 等；
2. 数列中跳过了某些数。这时，可以构造出排序后两个相邻的数之间的差，进而构造出小于最大数的所有 $k$ 的倍数。

所以，我们只要找出所有数的最大公因数和最大值，计算还有几个数没有出现，判断奇偶就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int gcd(int x,int y)
{
	if(!y)
		return x;
	return gcd(y,x%y);
}
int main()
{
	int n,i,gc,maxv;
	cin>>n>>a[1];
	gc=maxv=a[1];//先赋值为第一个数
	for(i=2;i<=n;i++)
	{
		cin>>a[i];
		gc=gcd(gc,a[i]);
		maxv=max(maxv,a[i]);
	}
	if((maxv/gc-n)&1)
		cout<<"Alice";
	else
		cout<<"Bob";
	return 0;
}
```
时间复杂度为 $\mathcal O(n\log a_i)$。

---

## 作者：dyc2022 (赞：4)

## 写在前面：

手打 `gcd` 切忌**撞关键字**！！！！！[后果自负](https://www.luogu.com.cn/record/116686632)。

本题解为[绿色健康食品](https://www.luogu.com.cn/record/116686798)，请放心食用。

## 我们使用“由特殊到一般”的推导方法。

从两个数字开始，通过列举模拟几组特殊样例，我们可以发现：

$2$ 和 $3$ 可以拓展到的数字有 $\{ 1,2,3 \}$，除去原来的数字 $2$ 和 $3$，只剩下一个 $1$，因此先手必胜。

$4$ 和 $6$ 可以拓展到的数字有 $\{ 2,4,6 \}$，除去原来的数字 $4$ 和 $6$，只剩下一个 $2$。因此先手必胜。

$15$ 和 $21$ 可以拓展到的数字有 $\{ 3,6,9,12,15,18,21\}$，除去 $15$ 和 $18$，剩下 $5$ 个数字。~~因此还是先手必胜~~。

总而言之，两个数 $a$、$b$ 可以拓展出来的数字，是一个等差数列，这个等差数列的首项是 $\gcd(a,b)$，末项是 $\max(a,b)$，公差是 $\gcd(a,b)$，项数为 $\dfrac{\max(a,b)}{\gcd(a,b)}$。如果 $\dfrac{\max(a,b)}{\gcd(a,b)} - 2 \equiv 0 \pmod 2$，那么后手必胜。否则先手必胜。
***
两个数的结论是毋庸置疑的了，但是我们还需要把它推广到 $n$ 个数字情况。

先给结论，设这 $n$ 个数是为 $A = \{a_1,a_2,a_3....a_n\}$，则他们能扩展的的数字也是一个等差数列，首项是 $\gcd(A)$，末项是 $\max(A)$，公差是 $\gcd(A)$。

## 证明：数学归纳法

我们要证明上述命题，那么首先设 $\gcd(A) = k$，则 $A = \{kb_1,kb_2,kb_3...kb_n\}$，其中 $B = \{b_1,b_2,b_3...b_n\}$ 集合中的元素两两互质。

那么我们就转换成证明 $B$ 集合中的元素能不能通过加减运算得到 $1$。

- 对于两个数 $a$ 和 $b$，假设 $a > b$，则可以使用类似更相减损术或辗转相除法的方法得到 $1$。

具体过程：将辗转相除法中的取模运算换成减法，也就是 $a \bmod b$ 换成 $a$ 减去若干个 $b$，直到不能再减。由于 $a$、$b$ 互质，因此最后辗转相除的结果是 $1$。

综上所述，两个互质的整数可以通过加减运算得到 $1$。

- 我们现在假设含有 $n$ 个两两互质的数的集合已经可以通过加减运算得到 $1$，那么我们只要证明再加入一个互质的数字，还能通过加减运算得到 $1$。

证法同前，或用扩欧或中国剩余定理解决。

回到命题，如果我们已经可以使 $B = \{b_1,b_2,b_3...b_n\}$ 集合中的元素通过加减运算得到，那么我们也可以知道 $A$ 集合中的元素可以通过加减运算得到 $k$，也就是 $\gcd(A)$。那么我们就自然可以得到 $[k,\max(A)]$ 中的每一个 $k$ 的倍数。

设扩展可以得到 $m$ 个整数，原来的集合 $A$ 中有 $n$ 个整数，那么如果 $m - n\equiv 0 \pmod 2$，那么后手必胜。否则先手必胜。

AC 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,maxn,gCd;
int GCD(int x,int y)
{
	if(y==0)return x;
	else return GCD(y,x%y);
}
main()
{
	scanf("%d%d",&n,&k);
	maxn=k,gCd=k;
	for(int i=1;i<n;i++)
	{
		scanf("%d",&k);
		maxn=max(maxn,k);
		gCd=GCD(gCd,k);
	}
	if((maxn/gCd-n)&1)puts("Alice");
	else puts("Bob");
	return 0;
}
```

---

## 作者：离散小波变换° (赞：3)

我愿称之为伪博弈论题。

## 题解

注意到题设所给过程很像辗转相除法。由于 $d\mid x,d\mid y\Rightarrow d\mid (x-y)$，所以最终整个序列里，每个元素都是它们的最大公因数 $d=\gcd_i \{a_i\}$ 的倍数。同时总是可以按照辗转相除的方法，使得 $d$ 在最终的序列里。

接着注意到 $|x-y|< x$ 且 $|x - y|<y$，所以最后整个序列最大值就是原来的最大值 $m=\max_i \{a_i\}$。

当一名玩家无法操作时，整个序列肯定是 $[d,2d,3d,\cdots,m]$，否则如果 $kd$ 不在序列里而 $(k+1)d$ 在序列里，总是可以选择 $(k+1)d$ 和 $d$ 将 $kd$ 添加进去。所以最终局面是唯一确定的。

所以操作了恰好 $\dfrac{m}{d}-n$ 次后一定会到达最终局面。而在此之前一定可以进行操作。

所以根据 $\dfrac{m}{d}-n$ 的奇偶性输出结果就行，和两人采取什么策略完全没有关系。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int main(){
    int n = qread(), d = 0, m = 0;
    up(1, n, i){
        int a = qread(); m = max(m, a);
        d = __gcd(a, d);
    }
    puts((m / d - n) % 2 == 1 ? "Alice" : "Bob");
    return 0;
}
```

---

## 作者：sun_of_Ice (赞：2)

咸鱼来给冷门水题发个题解(〜￣△￣)〜

依照题意，最后序列中任何两个数的差的绝对值都可以在这个序列中找到，所以这个序列最后一定会变成一个**公差为首项的等差数列**，确定这个首项即可根据原序列中的最大值得出项数，进而得到允许的操作次数，这个操作次数的奇偶决定了谁能获胜。

先考虑原序列只有两个数的情况，我们不难发现整个整个过程与辗转相减求最大公约数的过程是一致的，最后得到的那个最小的数就是两数的最大公约数。由辗转相减法的原理，无论数的个数是多少，无论怎样选取，你也只可能得到它们的最大公约数及其倍数。这个最大公约数就是我们要找到首项。
```c++
    int gcd(int a, int b)
    {
        if(b == 0)
            return a;
        else
            return gcd(b, a % b);
    }
    int main()
    {
        int a[105], n, d, m;
        cin >> n;
        for(int i = 0;i < n;i++)
            cin >> a[i];
        d = a[0];
        m = a[0];
        for(int i = 1;i < n;i++)
        {
            d = gcd(d, a[i]);//找出所有数的最大公约数
            m = max(m, a[i]);//找出最大值
        }
        int ans = (m - d) / d + 1 - n;//操作次数
        if(ans & 1)
            cout << "Alice\n";
        else
            cout << "Bob\n";
    }
```

---

## 作者：yyz_100110 (赞：1)

# [CF346A Alice and Bob](https://www.luogu.com.cn/problem/CF346A)

### 题面：

Alice 和 Bob，在玩游戏，给出  $n$ 个数 ，从中找到两个整数 $x$ 和 $y$，且 $\lvert x-y \lvert$ 不在已给出的序列之中，所以要求把 $\lvert x-y \lvert$ 加入序列，当有一方无法操作时，就算失败，Alice 先手操作。

### 思路：

很常见的博弈论问题，我们要求出必胜策略，再看哪一方能够获胜。我们可以自己尝试一下这个游戏，比如，给出 $x$ 和 $y$ 分别为 $2$ 和 $5$，那么序列为 $1$ $2$ $3$ $4$ $5$。那么理解了这个游戏就可以来找最优方案的做法了。

样例： 看第一个样例，$x$ 和 $y$ 分别为 $2$ 和 $3$,，那么这个序列就为 $1$ $2$ $3$，取出 $2$ 和 $3$，那么就只剩下 $1$，此时 Bob 无法操作，所以 Alice 获胜。

### 做法:

我们可以发现根据命题，有一个集合 $\gcd(A) = x$，则 $A = \{xb_1,xb_2,xb_3 \cdots xb_n\}$，其中集合 $B = \{b_1,b_2,b_3 \cdots b_n\}$。

此时就需要运用到其他大佬都有讲到的辗转相除法，不会的[戳这里](https://zhuanlan.zhihu.com/p/324578532)，他还有一个名字大家可能就比较常见，叫欧吉里得算法（Euclidean algorithm）。那在这个欧几里得算法中有一句关键句为：`两个数的最大公约数等于其中较小的数字和二者之间余数的最大公约数`。而这个公式就能运用在我们这道博弈论题目上，其实这道题更加偏向于数论，而不是博弈论。那这个无伤大雅，我们还是重要内容看过程是如何推导的，能理解并运用就可以了。

按照我们提到的这个欧几里得算法，带入这道题中后。我们可以发现一个规律。这个序列的首项就为，$x$ 和 $y$ 的**最大公因数**（最大公约数），$\operatorname{gcd}(x,y)$。末尾为 $x$ 和 $y$ 的**最大值**，$\operatorname{max}(x,y)$。这就是个**等差数列**，所以他的公差就等于 $\operatorname{gcd}(x,y)$。最后我们在判断剩下数字的奇偶，就可以推断出最优策略了。

为了证明我们推出的结论，我们把结论带入样例 1。
样例 1，的序列如上为：$1$ $2$ $3$ $4$ $5$。

按照我们的推论，首项为 $\operatorname{gcd}(2,3)$，即为 $1$。末项为 $\operatorname{max}(2,3)$，即为 $5$。公差为 $\operatorname{gcd}(2,3)$，即为 $1$。推论得到了证明之后，就可以去根据思路编写代码了。

#### 数据范围: 

- $n(2 \le n \le 100)$

- $a_1,a_2,a_3,\cdots,a_n (1 \le a_i \le 10^9)$


最大公约数函数 $\operatorname{gcd}$：

```cpp
int gcd(int x,int y){
	if(!y) return x;
	return gcd(y,x%y);
}
```

最大值函数 $\operatorname{max}$：

```cpp
int max(int a, int b){
	if(a>b) return a;
   return b;
}
```

### Accode

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,s,c;
int gcd(int x,int y){
	if(!y)
		return x;
	return gcd(y,x%y);
}
int max(int a, int b){
	if(a>b) return a;
   return b;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
	    cin>>x;
	    s=max(s,x);
	    c=gcd(x,c);
	}
	return puts((s/c-n)%2?"Alice":"Bob"),0;
}
```

奉上 [AC 记录](https://www.luogu.com.cn/record/123109275)。

辛苦管理员了。


---

## 作者：Stars_visitor_tyw (赞：0)

## CF346A Alice and Bob 题解
### 思路
我们发现操作过程很像小学奥数的辗转相除法，可以得到大致思路：求 $n$ 个数的 $\gcd$ 最后的数列必然是一个以 $n$ 个数的 $\gcd$ 为首的等差数列。所以此题就是求 $n$ 个数的 $\gcd$，然后求出这个数列最长是多少，再减掉初始的 $n$，判断是否满足此条件：`(mx/gc-n)%2!=1`，若满足，输出 `Bob`，否则输出 `Alice`。

### 代码

```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,mx,gc;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	n=read();
	for(int i=1;i<=n;i++)
	{
		int x;
		x=read();
		mx=max(mx,x);
		gc=__gcd(x,gc);
	}
	if((mx/gc-n)%2!=1)
	{
		cout<<"Bob";
	}
	else
	{
		cout<<"Alice";
	}
	return 0;
}
```

---

## 作者：huangmingyi (赞：0)

这是蒟蒻的第一篇题解，求通过。   
这题是求 $n$ 个数的 $\gcd$ 最后的数列必然是一个以 $\gcd$ 为首的等差数列。例如 $3$ $2$ $4$  $6$ 就结束了。但是 $3$ $1$  $3$  $5$ 还可以继续。   
所以此题就是求 $n$ 个数的 $\gcd$，然后求出这个数列最长是多少，再减掉初始的 $n$。代码如下。
```
#include<bits/stdc++.h>//万能头
using namespace std;
int n,mx,gc;//n个数,mx取最大值,gc为公差
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;//没必要开数组，应为在这只用一次。如果想排序就开数组
		cin>>x;//输入
		mx=max(mx,x);//取最大值
		gc=__gcd(x,gc);//一定要打两个下划线不然CE
	}
	if((mx/gc-n)%2==1){//如果最大值除公差减初始的n为奇数
		cout<<"Alice";//则Alice赢
	}else{
		cout<<"Bob";//否则Bob赢
	}
	return 0;
}
```


---

## 作者：BADFIVE (赞：0)

**题意**： 给出一个长 $N$ 的序列，然后 Alice 与 Bob 每次要轮流从中取两个数。   
如果 $|x-y|$ 已经存在与序列中，那么操作无效，不存在则有效。并且把得到的差值加入到序列中。   
**思路**： 因为要使得最后一个人操作无效，所以该序列已经成为一个 $1$ 到 $N$ 的等差数列。   
我们需要求的就是成为这种序列的次数。两个数相减必定是公约数的倍数，我们知道最小的数一定是这 $n$ 个数的最大公约数 。   
然后计算奇偶的次数，就求出来了等差，所以就可以得到最终序列的个数。   
```
#include <bits/stdc++.h>
using namespace std;
int arr[10001];
int gcd(int a,int b){
    return b==0? a:gcd(b,a%b);
}
int main() {
	int n;
	cin>>n;
	for(int i =0; i < n; i++) {
		cin>>arr[i];
	}
	sort(arr,arr+n);
	int g = arr[0];
	for(int i = 1; i<n; i++) {
		g = gcd(arr[i],g);
	}
	int ans = arr[n-1]/g - n;
	if(ans&1) cout<<"Alice";
	else cout<<"Bob";
}
```

---

