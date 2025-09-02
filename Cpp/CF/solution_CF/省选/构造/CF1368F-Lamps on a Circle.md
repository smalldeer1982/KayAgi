# Lamps on a Circle

## 题目描述

This is an interactive problem.

John and his imaginary friend play a game. There are $ n $ lamps arranged in a circle. Lamps are numbered $ 1 $ through $ n $ in clockwise order, that is, lamps $ i $ and $ i + 1 $ are adjacent for any $ i = 1, \ldots, n - 1 $ , and also lamps $ n $ and $ 1 $ are adjacent. Initially all lamps are turned off.

John and his friend take turns, with John moving first. On his turn John can choose to terminate the game, or to make a move. To make a move, John can choose any positive number $ k $ and turn any $ k $ lamps of his choosing on. In response to this move, John's friend will choose $ k $ consecutive lamps and turn all of them off (the lamps in the range that were off before this move stay off). Note that the value of $ k $ is the same as John's number on his last move. For example, if $ n = 5 $ and John have just turned three lamps on, John's friend may choose to turn off lamps $ 1, 2, 3 $ , or $ 2, 3, 4 $ , or $ 3, 4, 5 $ , or $ 4, 5, 1 $ , or $ 5, 1, 2 $ .

After this, John may choose to terminate or move again, and so on. However, John can not make more than $ 10^4 $ moves.

John wants to maximize the number of lamps turned on at the end of the game, while his friend wants to minimize this number. Your task is to provide a strategy for John to achieve optimal result. Your program will play interactively for John against the jury's interactor program playing for John's friend.

Suppose there are $ n $ lamps in the game. Let $ R(n) $ be the number of turned on lamps at the end of the game if both players act optimally. Your program has to terminate the game with at least $ R(n) $ turned on lamps within $ 10^4 $ moves. Refer to Interaction section below for interaction details.

For technical reasons hacks for this problem are disabled.

## 说明/提示

When $ n = 3 $ , any John's move can be reversed, thus $ R(3) = 0 $ , and terminating the game immediately is correct.

 $ R(4) = 1 $ , and one strategy to achieve this result is shown in the second sample case.

Blank lines in sample interactions are for clarity and should not be printed.

## 样例 #1

### 输入

```
3```

### 输出

```
0```

## 样例 #2

### 输入

```
4

1```

### 输出

```
2 1 3

0```

# 题解

## 作者：DJRzjl (赞：6)

# [CF1368F](https://www.luogu.com.cn/problem/CF1368F)  Lamps on a Circle
我们想要让最后留下的灯尽可能多，那么每回合都应该使灯数变多，那么我们肯定不想让局面上存在 $k$ 个连续的亮灯，否则对方将这 $k$​ 个删掉局面就没有变优了，于是在我们操作后能达到的最优局面即为：

```
1 1 ... 1 0 1 1 ... 1 0 1 1 ... 1 0 1 ... 1 0  （其中1表示亮的灯，0表示灭的灯）
|-k-1个-|    |-k-1个-|   |-k-1个-|
```

注意最后的位置一定得是 $0$，即使最后一段不足 $k-1$ 个，这是由于是环形，首尾相连也不能超过 $k-1$，所以我们可以把这个局面看成长为 $n-1$，周期为 $k$​，每个周期先有 $k-1$ 个亮灯，再有一个灭的灯的情况。最后一个周期可能不满。

然后对方执行最后一次操作，熄灭任意 $k-1$​​ 个灯，我们最终保留了 $\frac {n-1}k \times (k-1)-(k-1)=n-1-\frac{n-1}k-k-1=n-2-(\frac{n-1}k+k)$，根据基本不等式，这坨东西最大值不超过 $n-2-2\sqrt{n-1}$​​，仅当 $\frac {n-1}k=k$ 即 $k=\sqrt{n-1}$。

因为 $\sqrt{n-1}$ 可能开不尽，所以上下取整都代入计算一下，取大者为 $k$ 恒不变进行交互，轮到我们操作时始终保证不存在 $k$ 个连续的亮灯，此时每轮对面最多关 $k-1$ 个灯，每轮可以多亮一盏，也就可以在 $n$ 轮之内达到最优情况。

## Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;

int n,mx,k,a[N],L;

inline int calc(int s){int res=0; for(int i=1;i<n;i++) if(i%s!=0) res++; return res-(s-1);}
inline int chk(){int res=0; for(int i=1;i<=n;i++) res+=a[i]; return res;}

int main(){
	scanf("%d",&n);
	if(n<=3) return puts("0"),fflush(stdout),0;
	int L=sqrt(n-1),R=L+1;
	for(int i=L;i<=R;i++){
		int tmp=calc(i);
		if(tmp>mx) mx=tmp,k=i;
	}
	while(chk()<mx){
		printf("%d",k);
		int cnt=k;
		for(int i=1;i<n;i++){
			if(i%k!=0&&!a[i]) a[i]=1,printf(" %d",i),cnt--;
			if(!cnt) break;
		}
		while(cnt) printf(" 1"),cnt--;
		putchar('\n'),fflush(stdout);
		scanf("%d",&L);
		for(int i=L;i<=L+k-1;i++) a[i>n?i-n:i]=0;
	}
	return puts("0"),fflush(stdout),0;
}
```


---

## 作者：Soulist (赞：3)

## CF1368F

这是一道交互题。

Alice 和 Bob 在玩游戏，有 $n$ 盏灯排成一个圈，顺时针标号为 $1\sim n$，初始所有灯都是关着的。

每轮操作为：

- Alice 选择一个 $k\in [1,n]$ 然后打开任意 $k$ 盏灯（可以重复打开）
- Bob 关闭一段长度为 $k$ 的区间的灯。

设 $R$ 表示经过若干轮后开着的灯的数量的最大值。

你需要在不超过 $10^4$ 次操作达到这个上界。

$n\le 1000$

- 请注意，灯是环形摆放。

### Solution

设 $A$ 表示当前亮着的灯的数量。

假设当前增加了 $k$ 盏灯，里面如果 Bob 无法消去 $k$ 盏灯，那么 $A$ 将会增大。

换而言之，如果操作后不存在连续的 $k$ 盏灯，那么当前操作就可以使得 $A$ 增大。

考虑 $A$ 能够增大的必要条件是什么，即存在一个 $k$ 使得操作后有不存在连续的 $k$ 盏灯。

注意到 $R<n$，所以我们至少有一盏灯是关闭状态。

注意到操作之后的亮着的灯的数量为 $A+k$，此时仍有连续的灯的数量为 $k-1$，从某个灭着的灯处看，我们发现最优情况下每隔 $k$ 个位置就有一盏灯是灭着的，我们有 $A+k\le n-1-\frac{n-1}{k}$

所以 $A\le n-k-1-\frac{n-1}{k}$

于是答案的上界为 $\max_{k} (n-k-1-\frac{n-1}{k})+1$，即 $A$ 到达合法的上界（即可以增长的集合大小）后仍然可以增大 $1$

考虑这样的策略，我们先固定此 $k$，然后维护集合 $A$ 满足 $\{x\in A,x\ne 1\pmod k\}$

不难证明集合中不存在连续的 $k$ 个数（注意到 $1$ 被 ban 掉了）

所以我们每次操作总能够选出 $k$ 个数，同时使答案至少增大 $1$

可以证明当 $k=\sqrt{n}$（下取整）时得到最优解。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 1000 + 5 ; 
int n, R, Z, k, cnt, A[N] ;  
signed main()
{
	fflush(stdout) ; 
	n = gi(), k = sqrt(n) ;
	R = n - k - (n - 1) / k ;
	if( R <= 0 ) { puts("0") ; exit(0) ; }
	while(1) {
		printf("%d ", k ) ; cnt = 0 ;
		rep( i, 1, n ) {
			if(A[i] || i % k == 1) continue ; 
			printf("%d ", i ), A[i] = 1, ++ Z, ++ cnt ; 
			if( cnt == k ) break ; 
		}
		puts("") ; 
		int x ; cin >> x ; 
		rep( i, 0, k - 1 ) {
			if( A[(i + x - 1) % n + 1] ) -- Z ;
			A[(i + x - 1) % n + 1] = 0 ; 
		}
		if( Z == R ) break ; 
	}
	puts("0") ; 
	return 0 ;
}
```

---

## 作者：Graphcity (赞：2)

数据范围很小，完全可以暴力操作。

首先可以来猜一些结论：隔一个开一个能够达到最优解 $\lfloor \dfrac{n}{2}\rfloor -1$。这个貌似是正确的，但是 $n=12$ 时你会发现隔一个开两个可以做到答案为 6。

这个时候便可以猜想：隔一个开 $k$ 个（$k\ge 1$）是最优策略。

首先可以创造隔 $k$ 个开一个的局面，我们尝试在这种局面下进行调整，看能不能找到更优的方案。

我们接下来不能开 $\le k$ 个，因为至少有一段连续段有 $k$ 盏开启的灯，这次操作相当于白做。我们也不能开 $k+1$ 盏灯。根据抽屉原理，我们插入这些灯之后必然会形成至少一个 $k+1$ 的连续段，也相当于白做。

所以这种局面就是最优的。

枚举 $t=k+1$，也就是循环节，找到最大的 $(t-1)\times (\lfloor \dfrac{n}{t}\rfloor-1)+\max(0,(n\bmod t)-1)$，然后暴力操作即可。

时间复杂度 $O(n^2)$。每次操作必然至少多一盏开着的灯，所以操作次数合法。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e3;

int n,a,mx,ans,vis[Maxn+5],chk[Maxn+5];

int main()
{
    cin>>n;
    if(n<=3) {cout<<0<<endl; return 0;}
    For(i,1,n) if((i-1)*(n/i-1)+max(n%i-1,0)>mx)
        mx=(i-1)*(n/i-1)+max(n%i-1,0),a=i;
    for(int i=1;i<=n;i+=a) For(j,1,a-1) vis[i+j-1]=1;
    while(1)
    {
        int cnt=0;
        cout<<a<<' ';
        For(i,1,n) if(vis[i] && !chk[i])
        {
            cout<<i<<' '; chk[i]=1;
            if(++cnt==a) break;
        }
        cout<<endl;
        int x; cin>>x;
        For(i,0,a-1) chk[(x+i-1)%n+1]=0;
        ans=0;
        For(i,1,n) ans+=chk[i];
        if(ans==mx) {cout<<0<<endl; break;}
    }
    return 0;
}
```

---

