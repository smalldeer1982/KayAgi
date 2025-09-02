# Lieges of Legendre

## 题目描述

Kevin and Nicky Sun have invented a new game called Lieges of Legendre. In this game, two players take turns modifying the game state with Kevin moving first. Initially, the game is set up so that there are $ n $ piles of cows, with the $ i $ -th pile containing $ a_{i} $ cows. During each player's turn, that player calls upon the power of Sunlight, and uses it to either:

1. Remove a single cow from a chosen non-empty pile.
2. Choose a pile of cows with even size $ 2·x $ ( $ x&gt;0 $ ), and replace it with $ k $ piles of $ x $ cows each.

The player who removes the last cow wins. Given $ n $ , $ k $ , and a sequence $ a_{1},a_{2},...,a_{n} $ , help Kevin and Nicky find the winner, given that both sides play in optimal way.

## 说明/提示

In the second sample, Nicky can win in the following way: Kevin moves first and is forced to remove a cow, so the pile contains two cows after his move. Next, Nicky replaces this pile of size 2 with two piles of size 1. So the game state is now two piles of size 1. Kevin then removes one of the remaining cows and Nicky wins by removing the other.

## 样例 #1

### 输入

```
2 1
3 4
```

### 输出

```
Kevin
```

## 样例 #2

### 输入

```
1 2
3
```

### 输出

```
Nicky
```

# 题解

## 作者：VinstaG173 (赞：5)

~~这题能有 2200 CF 的人均博弈论水平堪忧~~

一道简单 SG 定理题。

考虑计算 SG 函数：

当 $x$ 为偶数时

$$\operatorname{SG}(x)=\operatorname{mex}(\{(\operatorname{SG}(x/2))^{k\oplus},\operatorname{SG}(x-1)\})$$

其中 $a^{k\oplus}$ 表示 $k$ 个 $a$ 的异或和。很容易发现

$$
a^{k\oplus}=
\begin{cases}
a, & k \equiv 1 \pmod{2} \\
0, & k \equiv 0 \pmod{2} \\
\end{cases}
$$

当 $x$ 为奇数时

$$\operatorname{SG}(x)=\operatorname{mex}(\{\operatorname{SG}(x-1)\})$$

于是我们分 $k$ 的奇偶讨论。

当 $k$ 为偶数时我们很容易发现

$$
\operatorname{SG}(x)=
\begin{cases}
0, & k=0 \lor (k \equiv 1 \pmod{2} \land k>1) \\
1, & k=1 \lor (k \equiv 0 \pmod{2} \land k>2) \\
2, & k=2 \\
\end{cases}
$$

当 $k$ 为奇数时我们可以直接递归处理，由于很容易推出大于 $3$ 的奇数的 SG 值都为 $0$，所以对于偶数只要递归计算 $\operatorname{SG}(x/2)$ 即可。

时间复杂度 $O(n\log{\max\{a_i\}})$。

Code:
```cpp
#include<cstdio>
int n,k,a,r;
int sg(int x)
{
    if(x&1)
    {
        if(x==1||x==3)return 1;
        else return 0;
    }
    if(x==0||x==2)return 0;
    if(x==4)return 2;
    else return (sg(x/2)==1)?2:1;
}
int main()
{
    scanf(" %d %d",&n,&k);
    if(k&1)
    {
        while(n--)
        {
            scanf(" %d",&a);
            r^=sg(a);
        }
        printf("%s\n",r?"Kevin":"Nicky");
    }
    else
    {
        while(n--)
        {
            scanf(" %d",&a);
            if(a==0)continue;
            if(a==1){r^=1;continue;}
            if(a==2){r^=2;continue;}
            r^=(a&1^1);
        }
        printf("%s\n",r?"Kevin":"Nicky");
    }
    return 0;
}
```

---

## 作者：「已注销」 (赞：1)

SG定理很容易解决

对于一个游戏，其SG函数值为所有子游戏的SG函数值异或

$0$至$4$的SG函数值可以手算

对于其他情况：

若$k$为偶数，$x$为奇数，$SG(x)=mex\{SG(x-1)\}=0$

若$k$为偶数，$x$为偶数，$SG(x)=mex\{SG(x-1),0\}=1$

若$k$为奇数，$x$为奇数，$SG(x)=mex\{SG(x-1)\}=0$

若$k$为奇数，$x$为偶数，$SG(x)=mex\{SG(x-1),SG\left(\dfrac{x}{2}\right)\}=mex\{0,SG\left(\dfrac{x}{2}\right)\}$，可以递归求解

时间复杂度$O(n\log a)$
```cpp
#include<cstdio>
using namespace std;
int n,k,a,ans;
int sg(int x){
    if(x<2)return x;//特判
    if(k){
        if(x<5)return x-2;//特判
        if(x&1)return 0;
        int t=sg(x>>1);
        return t>1?1:t+1;
    }
    if(x==2)return 2;//特判
    return !(x&1);
}
int main(){
    scanf("%d%d",&n,&k);
    k&=1;
    for(int i=1;i<=n;++i){
        scanf("%d",&a);
        ans^=sg(a);
    }
    puts(ans?"Kevin":"Nicky");
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

好的既然 ChiFAN 没来写题解，那我来写。

首先发现这是一道博弈论，于是我们通读 OI-Wiki 博弈论方面的知识，发现可以运用 SG 函数解决这个问题。

SG 函数的值则等于后继状态的 SG 值的 $\text{mex}$，于是我们根据 $x$ 不同的奇偶性给你 SG 转移式（以下 $x^y$ 的意义均为 $x$ 经 $y$ 次异或得到的值）：

当 $x$ 为偶数时：

$$SG(x) = \text{mex}(SG(\frac{x}{2})^k, SG(x - 1))$$

当 $x$ 为奇数时：

$$SG(x) = SG(x - 1)$$

但是我们发现 $a_i$ 高达 $10^9$，直接暴力做肯定不行。

首先注意到 $x$ 为奇数时，$SG(x) = 0$。其次，当 $k$ 是偶数时，$SG(\frac{x}{2})^k = 0$，$k$ 是奇数时：$SG(\frac{x}{2})^k = SG(\frac{x}{2})$，由于当 $x$ 为偶数时 $x - 1$ 一定为奇数，所以其中转移式中的 $SG(x - 1) = 0$。

于是我们发现转移式中 $SG(x - 1)$ 的项全部消掉了，我们就可以 $\log V$ 计算 $SG(x)$ 了，注意预处理前几项的 SG 值。

---

## 作者：lfxxx (赞：0)

首先写出 $SG$ 函数的转移式：$SG(x) = \oplus_{i=1}^k SG(\frac{x}{2}) \oplus SG(x-1)$，当 $x$ 不是偶数时没有 $\oplus_{i=1}^k SG(\frac{x}{2})$ 这一项。由于是异或，所以 $k$ 先对 $2$ 取模。

然后打表发现如下事实：

1. $k = 0$ 且 $x > 2$ 时 $SG(x)$ 为 $x$ 对 $2$ 取模的结果取反。

2. $k = 1$ 且 $x$ 为比较大的奇数时，$SG(x)$ 为 $0$。

于是当满足上面的条件时直接返回，那么对于每个数暴力求解 $SG$ 函数实际上只会递归 $O(\log V)$ 次，因为每次递归 $SG(\frac{x}{2})$ 时大小折半，而递归 $SG(x-1)$ 时可以直接得到答案。

由于我用了 map 存了下值，所以时间复杂度是 $O(n \log^2 V)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
map<int,int> sg,vis;
int n,k;
int solve(int u){
	if(vis[u]==1) return sg[u];
	vis[u]=1;	
	if(k%2==0) return sg[u]=(u<=2?u:((u%2)^1));
	if(k%2==1&&u>=10&&u%2==1) return (sg[u]=0); 
	if(u==0){
		return (sg[u]=0);
	}
	int cnt[4]={0,0,0,0};
	int res=solve(u/2);
	int ans=0;
	for(int i=1;i<=(k%2);i++) ans^=res;
	if(u%2==0) cnt[ans]++;
	cnt[solve(u-1)]++;
	while(cnt[sg[u]]!=0) sg[u]++;
	return sg[u];
}
//k%2==0
//sg(i)=[i<=2?i:i%2^1]
//k%2==1
//比较小直接暴力 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	int Nim=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		Nim^=solve(x); 
	}
	cout<<(Nim!=0?"Kevin\n":"Nicky\n");
	return 0;
}

```

---

