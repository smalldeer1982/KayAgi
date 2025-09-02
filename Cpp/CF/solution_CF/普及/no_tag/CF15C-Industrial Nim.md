# Industrial Nim

## 题目描述

There are $ n $ stone quarries in Petrograd.

Each quarry owns $ m_{i} $ dumpers ( $ 1<=i<=n $ ). It is known that the first dumper of the $ i $ -th quarry has $ x_{i} $ stones in it, the second dumper has $ x_{i}+1 $ stones in it, the third has $ x_{i}+2 $ , and the $ m_{i} $ -th dumper (the last for the $ i $ -th quarry) has $ x_{i}+m_{i}-1 $ stones in it.

Two oligarchs play a well-known game Nim. Players take turns removing stones from dumpers. On each turn, a player can select any dumper and remove any non-zero amount of stones from it. The player who cannot take a stone loses.

Your task is to find out which oligarch will win, provided that both of them play optimally. The oligarchs asked you not to reveal their names. So, let's call the one who takes the first stone «tolik» and the other one «bolik».

## 样例 #1

### 输入

```
2
2 1
3 2
```

### 输出

```
tolik
```

## 样例 #2

### 输入

```
4
1 1
1 1
1 1
1 1
```

### 输出

```
bolik
```

# 题解

## 作者：午夜飘雪 (赞：13)

~~趁没人抢占前排☆！~~

### 简单博弈论题

容易发现每辆车是一个独立的nim游戏，于是只需要求出所有的车的石头数量的异或和即可。

但是数据范围是1e16，暴力对所有车求异或和肯定不行，于是问题就在于如何快速求一段连续自然数的异或和。

这里用到了一个性质：一个偶数和它的下一个奇数的异或和为1。正确性还是很显然的。

于是对于每段连续自然数只需要特判一下头尾即可，最后异或和非零则先手必胜

```
#include<iostream>
#include<cstdio>
using namespace std;
int n;
long long ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        long long a,len;
        scanf("%lld%lld",&a,&len);
        if(a%2){ans^=a,++a,--len;}//特判头
        if(len&&len%2){ans^=a+len-1,--len;}//特判尾
        if(len&&(len/2)%2)ans^=1;//中间
    }
    if(ans)printf("tolik\n");
    else printf("bolik\n");
    return 0;
}  
```

~~以及一开始忘记开long long然而依然AC是什么操作∑(°口°)~~

---

## 作者：Heartlessly (赞：7)

## Description

现在有很多石子，可以分为 $n$ 个区。第 $i$ 个区中有 $m_i$ 堆石子，且这个区的第 $j$ 堆石子共有 $x_i + j - 1$ 个石子。现两个人每次从任意一堆石子中取正整数个石子，取完石子的人获胜，他们都会做出最优的选择。若先手赢输出 **"tolik"**，后手赢输出 **"bolik"**（不包含引号）。$(1 \leq n \leq 10^5,1 \leq m_i,x_i \leq 10^{16})$

## Source

**[[Luogu]CF15C](https://www.luogu.org/problemnew/show/CF15C)**

**[[Codeforces]15C](http://codeforces.com/problemset/problem/15/C)**

## Solution

很显然这是一个 **Nim 游戏**，也就是说只要把每一堆中的石子个数异或起来，不为 $0$ 则先手必胜（$\rm SG$ 定理）。

但石子最多可能有 $\sum\limits_{i = 1}^n m_i$ 堆，直接异或会超时，所以要结合每一个区中石子个数的特性。

对于第 $i$ 个区，我们设 $l = x_i,r = x_i + m_i - 1,pre_i = 0 \oplus 1 \oplus 2 \oplus \cdots \oplus i$，那么这个区中每一堆石子个数的异或和为 $pre_r \oplus pre_{l - 1}$ 。

$x_i$ 和 $m_i$ 很大，所以考虑找规律。

首先易证 $a \oplus (a + 1) = 1$，其中 $a \in \{ x  \mid x \in {\rm N},x = 2k \}$（因为二进制下 $a$ 的右起第一位为 $0$，而 $a + 1$ 为 $1$，其余二进制位都相同）。

假如我们现在要求 $pre_x$，可以分成 $4$ 种情况：

1. $x \bmod 4 = 0$，$0 \oplus 1 \oplus 2 \oplus \cdots \oplus (x - 1)$ 可以变为 $\frac{x}{2}$ 个 $1$ 的异或和，且 $\frac{x}{2}$ 一定是一个偶数，所以前 $x - 1$ 个数的异或和为 $0$，$0 \oplus x = x$，此时 $pre_x = x$ 。
2. $x \bmod 4 = 1$，$0 \oplus 1 \oplus 2 \oplus \cdots \oplus x$ 可以变为 $\frac{x+1}{2}$ 个 $1$ 的异或和，且 $\frac{x+1}{2}$ 一定是一个奇数，所以此时 $pre_x = 1$ 。
3. $x \bmod 4 = 2$，$0 \oplus 1 \oplus 2 \oplus \cdots \oplus (x - 1)$ 可以变为 $\frac{x}{2}$ 个 $1$ 的异或和，且 $\frac{x}{2}$ 一定是一个奇数，所以前 $x - 1$ 个数的异或和为 $0$，而 $x$ 是偶数，$1 \oplus x = x + 1$，此时 $pre_x = x + 1$ 。
4. $x \bmod 4 = 3$，$0 \oplus 1 \oplus 2 \oplus \cdots \oplus x$ 可以变为 $\frac{x+1}{2}$ 个 $1$ 的异或和，且 $\frac{x+1}{2}$ 一定是一个偶数，所以此时 $pre_x = 0$ 。

这样就可以在 $O(1)$ 的时间内求出 $pre_x$，总时间复杂度为 $O(n)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

int n;
LL ans;

inline LL solve(LL x) {//求 0 xor 1 xor 2 xor ... xor x 的值 
    LL res = 0;
    switch (x % 4) {//分四种情况 
        case 0 : { res = x; break; }
        case 1 : { res = 1; break; }
        case 2 : { res = x + 1; break; }
        case 3 : { res = 0; break; }
    }
    return res;
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        LL x, m, l, r;
        read(x), read(m);
        l = x, r = x + m - 1;
        ans ^= solve(r) ^ solve(l - 1);//求异或和 
    }
    puts(ans ? "tolik" : "bolik");
    return 0;
}
```



---

## 作者：Rachel_in (赞：7)

本题的暴力的话，就是裸的NIM游戏，将每堆石子的数量异或一下，判断如果异或和不为零的话，先手必胜，否则后手必胜。但我们发现这个算法的瓶颈在于$m$的值非常大，我们试想一下是否可以快速求一段区间的异或和。

对于区间$[l,r]$的异或值,等价于$[1,l-1] Xor [1,r]$,因为异或两遍$[1,l-1]$区间相当于没异或。我们的目标就是求出$[1,x]$

我们可以打表找规律，我们打出$[1,x]$,$x$小于等于20的表:

![](https://cdn.luogu.com.cn/upload/pic/59146.png)

我们可以发现：

当$i\%4=0$时，异或和为$i$。

当$i\%4=1$时，异或和为$1$。

当$i\%4=2$时，异或和为$i+1$。

当$i\%4=3$时，异或和为$0$。

**代码**：

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
inline ll read(){
	ll res=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
	return res*f;
}
int n;
ll x,m,k;
inline ll work(ll a){
	if(a==0) return 0;
	if(a%4==1) return 1ll;
	if(a%4==2) return a+1;
	if(a%4==3) return (ll)0;
	if(a%4==0) return a;
}
int main(){
	n=read();
	k=0;
	for(int i=1;i<=n;i++){
		x=read();m=read();
		ll l=x,r=x+m-1;
		k^=work(r)^work(l-1);
	}		
	if(k) puts("tolik");
	else puts("bolik");
	return 0;
}
```


---

## 作者：Cutler (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF15C)

看题目也知道是个 $\texttt{Nim}$ 游戏了，关于 $\texttt{Nim}$ 游戏，有一个众所周知的性质

> 如果所有的值异或起来为 $\texttt 0$，则后手赢，否则先手赢。

那么暴力的话就是把所有的值异或起来，显然会超时，那么我们考虑优化。

关于异或还有一个性质，一个偶数和这个数接下来的奇数异或为 $\texttt 1$ ，因为两者二进制的最后一位刚好相反，其余的位全部相当。

读题面我们发现，对于每个采石场，它的值是一段连续的序列。

所以我们可以给每个采石场的值分组，把偶数和它接下来的奇数分为一组，我们只需要考虑开头单独成组，末尾单独成组以及总共完整组的个数的奇偶性即可。

不懂的看代码：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int n, x, m, ans;

signed main(){
	
	scanf("%lld",& n);
	while(n --){
		scanf("%lld%lld", & x,& m);
		if(x & 1) ans ^= x,++ x,-- m;//判断开头是否单独成组
		if(m & 1) ans ^= x + m - 1,-- m;//判断末尾是否单独成组
		ans ^= (m >> 1) & 1;//判断组数奇偶性
	}
	
	if(ans) puts("tolik");//先手赢
	else puts("bolik");
	return 0;
}
```

优雅结束。

---

## 作者：OldVagrant (赞：2)

## 题意简述
有 $n$ 个采石场，每个采石场里有 $m_i$ 辆车,每个采石场第 $1$ 辆车里有 $x_i$ 块石头，第 $j$ （$0<j \leq m_i$）辆车中有 $x_i+j-1$ 块石头。有两个人每次从任意一辆车中取任意数量的石头（不能不取），最后一个取完所有石头的胜利，两人都以最优策略去取，问结果是先手胜利还是后手胜利。
## Solution
     
读完题之后，我们很快地可以发现这就是一个**Nim游戏**，而Nim游戏的后手必胜条件是每一堆的石子数异或起来**结果为 $0$** ，否则先手必胜。   
然后....~~直接暴力异或？~~  

看一下数据范围，$n<=10^5 $, $x_i,m_i<=10^{16} $ ,采石场数量不多，但是车的数量和每堆石子的数量是一个很大的数，这告诉我们~~暴力会TLE~~要用一个 $O(n)$ 的算法。   

观察一下这道题给出的条件，每个采石场的第一辆车的石头数是给定了的，而后面每辆车的石头数都是前一辆车的石头数+1，所以每个采石场可以看成一个连续的自然数序列，这个序列里每一个数都异或起来的结果肯定是有规律的，不妨推导一下这个规律。 

先观察一下**从 $0$ 开始**的自然数序列的异或和有什么规律：   

| 序列长度 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 异或和 | 1 | 3 | 0 | 4 | 1 | 7 | 0 | 8 | 1 | 11 | 0 | 12 |
可以发现，异或和似乎有某种规律，这个规律看起来和序列长度有关,令序列长为 $l$ 。        
先从 $l=0$ 看起，此时序列异或和为 $0$ 。      
然后 $l=1$ ，序列里新添加了一个 $1$ ，原来的异或和为 $0$ ，那么这个序列现在的异或和就为 $1$ 。    
接着 $l=2$ , 序列里又多了一个 $2$ ，原来的异或和为 $1$ ，再和 $2$ 异或一下得到 $3$ 。  
再看 $l=3$ , 新来的这个 $3$ 和原来的异或和相等，所以异或和又回到了 $0$ 。     
$l=4$ 时，$4$ 异或上 $0$ 还是 $4$； $l=5$ 时，$5$ 和 $4$ 只有最后一位不一样，所以异或和变成了 $1$ ；$l=6$ 时，$6$ 是个偶数，所以 $6$ 异或上   $1$ 就相当于给 $6$ 加上 $1$ 也就是 $7$ ； $l=7$ 时，跟 $l=3$ 的情况一样，$l=8$ 时和 $l=4$ 时的结果一样......以此类推，推完之后发现了下面的这些规律：  
1. 如果 $l\bmod 4=1$ ,那么异或和为 $1$ 。  
2. 如果 $l\bmod 4=2$ ,那么异或和一定为 $l+1$ (在 $1$ 的基础上多异或了一个 $l$ ,$l$ 为偶数所以二进制下最低位为 $0$ ，和 $1$ 异或刚好得到 $l+1$ )。   
3. 如果 $l\bmod 4=3$ ,那么异或和一定为 $0$ (以刚刚的 $l$ 为准,在异或和已经为 $l+1$ 的基础上多异或了一个 $l+1$ ，两个相同的数的异或值为 $0$ )。 
4. 如果 $l\bmod 4=0$ ,那么异或和一定为 $l$ (任何数异或上一个 $0$ 都不变)。   
在规律4的基础上再来解释规律1，以规律4的 $l$ 为准，$l$ 和 $l+1$ 的异或结果一定为 $1$，因为 $l\bmod 4=0$ ,所以 $l$ 和 $l+1$ 只有最低位不同，所以异或结果为 $1$ 。   

~~恭喜你完成了一大半的推导。~~   

但是，$1\leq x_i\leq 10^{16}$ ,也就是说序列一定不从0开始，so....如何解决？

异或运算的逆运算是它本身，就是 $a \oplus  b \oplus b=a$ ，这个序列是从 $x_i$ 开始的，我们可以算出来 $0\sim x_i+m_i-1$ 的异或和，再求出 $0\sim x_i-1$ 的异或和，两者异或一下就得到了 $x_i\sim x_i+m_i-1$ 的异或和，根据上面推导得出的结论，可以 $O(1)$ 求出一个采石场中石头数量的异或和，$O(n)$ 求出总的异或和，然后判断一下即可。
## Code
~~结论题的代码一般都很简单，推出结论的话几行就出来了。~~
```c
#include <bits/stdc++.h>
using namespace std;
#define ll long long//记得开longlong
#define rint register int
#define pc(x) putchar(x)
#define gc getchar
ll n,a,m,sum,ps;
inline ll read(){
	ll x=0;
	char ch=gc();
	while(!isdigit(ch)) ch=gc();
	while(isdigit(ch)) x=x*10+ch-'0',ch=gc();
	return x;
}
ll work(ll x){//根据推导出的规律来快速求出异或和
	if(x%4==0) return x;
	if(x%4==1) return 1;
	if(x%4==2) return x+1;
	else return 0;
}
int main(){
	n=read();
	for(rint i=1;i<=n;i++) a=read(),m=read(),sum^=(work(a+m-1)^work(a-1));
	(sum)?printf("tolik"):printf("bolik");//总异或和不为0则先手胜，否则后手胜
	return 0;
}	
```


---

## 作者：漠寒 (赞：2)

## 分析

对于 $nim$ 游戏的话，可以去看[P2197](https://www.luogu.com.cn/problem/P2197)进行博弈论相关知识的学习。

在得到结论之后，我们就是要求，所有车辆石头的异或和，是否为零，是则后手赢，反之先手赢。

我们考虑每一位来单独处理，计算这些车石头数在每一位有多少个 $1$，对于第 $i$ 位而言，若以函数的角度理解，它的周期是 $2^{i+1}$，每一周期里，有 $2^i$ 个数字该位为 $1$。

因此对于每一位，我们就可以先找出 $x$ 当前所处的连续 $1$ 或连续 $0$ 的片段最远延伸到了多少，然后再找出多少个满周期，最后再加上剩余的数里有多少个该位为 $1$。

具体的实现可以详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int cnt[60];
int cf[60];
int mx=57;
int n,x,mm;
signed main()
{
	cf[0]=1;
	for(int i=1;i<=mx;i++)cf[i]=cf[i-1]*2;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>mm;
		for(int j=0;j<=mx;j++){
			int m=mm;//这个东西导致我错了很久 
			int sum=x/cf[j]+1;//找出当前连续段的末端位置
			//每一连续段大小都是2^j，所以直接除后加一，乘上2^j减1就是所求 
			if(x&cf[j]){//x是从1开始，后面取完周期就是从0开始 
				sum=sum*cf[j]-1;
				if(sum-x+1>m)cnt[j]+=m;//特判 
				else {
					cnt[j]+=sum-x+1;
					m-=sum-x+1;
					sum=m/(cf[j]*2);//周期数 
					m-=cf[j]*2*sum;
					cnt[j]+=sum*cf[j];//一半0，一半1 
					m-=cf[j];//先有2^j个0 
					if(m>0)cnt[j]+=m;
				}
			}
			else {
				sum=sum*cf[j]-1;
				if((sum-x+1)>m)cnt[j]+=0;
				else {
					m-=sum-x+1;
					sum=m/(cf[j]*2);
					m-=cf[j]*2*sum;
					cnt[j]+=sum*cf[j];//前面同理 
					if(m>0)cnt[j]+=min(m,cf[j]);//前面就是1了 
				}
			}
			cnt[j]%=2;//因为是异或，直接模2即可 
		}
	}
	for(int i=0;i<=mx;i++){
		if(cnt[i]){//异或和不为0，先手必胜 
			puts("tolik");
			return 0;
		}
	}
	puts("bolik");
	return 0;
}
```


---

## 作者：IceKylin (赞：1)

# CF15C Industrial Nim 题解
### [原题链接（in luogu）](https://www.luogu.com.cn/problem/CF15C)
### [原题链接（in CodeForces）](https://codeforces.com/problemset/problem/15/C)
### [更好的阅读体验？](https://www.luogu.com.cn/blog/std-IK/cf15c-ti-xie)

一道显而易见的 **博弈论** 题目。

考虑对每辆车建立 **Nim 游戏** 的模型。根据结论，可以得出答案即为所有车的石子数量的异或和，如果为 $0$ 那么先手必胜，否则后手必胜。

接下来思考如何在 **常数阶** 的时间复杂度内求出从 $1$ 开始的连续整数异或和。

对于异或和，有一些简单的性质：

- ${(2k)\oplus(2k+1)=1\quad(k\in N)}$

- ${(2k)\oplus(2k+1)\oplus(2k+2)\oplus(2k+3)=0\quad(k\in N)}$

- ${(2k)\oplus1=2k+1\quad(k\in N)}$

运用这些性质，就可以有如下操作：

设 ${f(x)=1\oplus2\oplus3\oplus\cdot\cdot\cdot\oplus(x-1)\oplus x}$

易得 ${f(x)=\begin{cases}
		x\quad(x\bmod 4=0)\\
     1\quad(x\bmod 4=1)\\
     x+1\quad(x\bmod 4=2)\\
     0\quad(x\bmod 4=3)
		\end{cases}}$
       
然后简单模拟即可， **时间复杂度** 为 $O(n)$。

P.S. 此题数据范围建议开 **long long** 。

## AC 代码
```cpp
//By IceKylin
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
ll n,ans;


il ll f(ll x){
	if(x%4==0)return x;
	if(x%4==1)return 1;
	if(x%4==2)return x+1;
	return 0;
}


int main(){
	ios::sync_with_stdio(false);
	cin>>n;
    for(int i=1;i<=n;++i){
    	ll x,m;
    	cin>>x>>m;
    	ans^=f(x-1);
		ans^=f(x+m-1);
    }
    if(ans==0)cout<<"bolik";
    else cout<<"tolik";
    return 0;
} 
```

---

## 作者：jijidawang (赞：1)

~~此题是 P2197 与 P3908 二合一~~

***

根据 Nim 游戏的经典结论，有当
$$\bigoplus_{i=1}^n\bigoplus_{j=X_i}^{X_i+M_i-1}j=0$$
时先手必胜，否则后手必胜 .

关于算这个式子等号左边，如果能快速计算 $1$ 到 $k$ 的异或和就行了 .

这个结论是 $\displaystyle f(k)=\bigoplus_{i=1}^ki$ 当 $k$ 是四的倍数时为 $0$ .

因为对于每个 $c$ 都有 
$$\begin{aligned}(4c)\oplus(4c+1)\oplus(4c+2)\oplus(4c+3)&=((4c)\oplus(4c+1))\oplus((4c+2)\oplus(4c+3))\\&=1\oplus 1\\&= 0\end{aligned}$$
（根据异或的定义，相邻两数的异或肯定是 $1$）

于是不是四的倍数的情况只需要找最近的四的倍数然后异或几个即可，于是可以得到
$$f(k)=\bigoplus_{i=1}^ki=\begin{cases}k&k\equiv0\pmod4\\1&k\equiv1\pmod4\\k+1&k\equiv2\pmod4\\0&k\equiv3\pmod4\end{cases}$$
于是这个 $f(k)$ 就可以 $O(1)$ 算了，返回原式，就有 $O(n)$ 的做法了 .

（可能有点意识流，见谅）

CF Submission: [161629341](https://codeforces.com/contest/15/submission/161629341) .

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$

---
应该是实现比较简单的一种方式。

---
### 解题思路：

说到底就是考了一个小 $\text{trick}$。

规则和一般的 $\text{NIM}$ 是一样的，这里不赘述。有所变动的是，题目给出的 $m_i$ 很大，不能直接通过枚举进行异或，考虑对这个过程进行优化。

注意到大多数的数都是连续的，而对于任意的一个偶数 $x$ 有 $x\oplus (x+1)=1$，因为在增加一之后，除了最后一位都没有变化。稍微拓展一下就有 $x\oplus(x+1)\oplus(x+2)\oplus(x+3)=0$，其中 $x\bmod2=0$。

这时候就能想到利用这个性质跳过中间的一大段数，不妨令从 $4k_1$ 开始到 $4k_2+3$ 中间的所有的数全都跳过，那么从前往后和从后往前各扫一次就好了。

注意有可能区间长度比较短，导致出现在同一个块中，这时候就需要记录下从前往后的最后的位置，防止重复计算。

---
### 代码：
```cpp
#include<iostream>
using namespace std;
long long n,m,x,ans,le,j,i;
signed main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>x>>m;le=0;
		for(j=x;j%4!=0&&j<=x+m-1;j++)ans^=j,le=j;
		for(j=x+m-1;j%4!=3&&j>le;j--)ans^=j;
	}
	if(ans)cout<<"tolik";
	else cout<<"bolik";
	return 0;
}
```

---

## 作者：king_xbz (赞：0)

之前排版没排好，重发一次。

很显然，**对于每辆车而言就是一个Nim游戏**，但是有很多辆车，分别异或取模需要耗费的时间大约是$O(n^2)$。

这显然是不彳亍的。

但是，我们可以发现，相邻两车的石子差值为1.

所以，我们可以考虑从这里入手。

假如$x$^$(x+1)$。那么有几种情况：

$10101010xor10101011=00000001$

$10101011xor10101100=00000111$

这两种情况中肯定是第一种情况更好考虑。

所以，我们截取整个序列如果第一个数为奇数，最后一个数为偶数，那么答案就是$last$^$first$.

如果第一个为奇数，最后一个为奇数，那么答案就是$first$

如果第一个为偶数，最后一个为偶数，答案就是$last$

接下来，考虑中间有几个偶异或奇：假如我们有偶数组偶异或奇，那么异或0，否则就异或1.

为了防止中间序列为长度0的情况，我们**特判让$m[i]<=4$的情况暴力异或解决**。

代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 5001
#define N 3759844
#define int long long
using namespace std;
int x[N],m[N];
signed main()
{
	int n;
	cin>>n;
	for(fint i=1;i<=n;i++)
	cin>>x[i]>>m[i];
	int ans=0;
	for(fint i=1;i<=n;i++)	
	if(m[i]<=4)
	{
		for(fint j=0;j<m[i];j++)
		ans^=(x[i]+j);
	}
	else
	{
		if(x[i]%2==1&&(x[i]+m[i]-1)%2==0)
		ans^=x[i]^(x[i]+m[i]-1),m[i]-=2;
		else
		if(x[i]%2==1&&(x[i]+m[i]-1)%2==1)
		ans^=x[i],m[i]--;
		else
		if(x[i]%2==0&&(x[i]+m[i]-1)%2==0)
		ans^=(x[i]+m[i]-1),m[i]--;
		if((m[i]/2)%2==1)
		ans^=1LL;
		else
		ans^=0LL;
	} 
	if(ans==0)
	puts("bolik");
	else
	puts("tolik");
	return 0;
}
```

最后，不开$longlong$见祖宗！祝大家AC愉快

---

## 作者：PosVII (赞：0)

**前言**

------------

本题考查博弈论以及一些异或的知识。

**思路**

------------

一段 $f(l,r)$ 的异或显然可转化为 $f(1,l-1) \mathbin{\mathrm{xor}}  f(1,r)$， 而我们只需要找规律就能发现：

对于 $f(1,x)$ 的异或，

- 当 $x\bmod 4 = 1$ 时 $f(1,x)=1$。
- 当 $x\bmod 4 = 2$ 时 $f(1,x)=x+1$。
- 当 $x\bmod 4 = 3$ 时 $f(1,x)=x$。
- 当 $x\bmod 4 = 0$ 时 $f(1,x)=0$。

而将其转化后就可以进行正常博弈即可。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
template<typename G>inline void read(G&x){x=0;G f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();x*=f;}
int n;
long long _xor(long long x) {
	long long p=x%4;
	if(p==1) return 1;
	if(p==2) return x+1;
	if(p==3) return 0;
	if(p==0) return x;
}
long long x,y,ans;
int main() {
	read(n);
	while(n--) {
		read(x),read(y);
		ans^=_xor(x+y-1)^_xor(x-1);
	}
	if(ans==0) puts("bolik");
	else puts("tolik");
	return 0;
}
```

---

