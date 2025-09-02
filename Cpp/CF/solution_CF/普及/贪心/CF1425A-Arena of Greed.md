# Arena of Greed

## 题目描述

Lately, Mr. Chanek frequently plays the game Arena of Greed. As the name implies, the game's goal is to find the greediest of them all, who will then be crowned king of Compfestnesia.

The game is played by two people taking turns, where Mr. Chanek takes the first turn. Initially, there is a treasure chest containing $ N $ gold coins. The game ends if there are no more gold coins in the chest. In each turn, the players can make one of the following moves:

- Take one gold coin from the chest.
- Take half of the gold coins on the chest. This move is only available if the number of coins in the chest is even.

Both players will try to maximize the number of coins they have. Mr. Chanek asks your help to find the maximum number of coins he can get at the end of the game if both he and the opponent plays optimally.

## 说明/提示

For the first case, the game is as follows:

1. Mr. Chanek takes one coin.
2. The opponent takes two coins.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

For the second case, the game is as follows:

1. Mr. Chanek takes three coins.
2. The opponent takes one coin.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

## 样例 #1

### 输入

```
2
5
6```

### 输出

```
2
4```

# 题解

## 作者：honey_ (赞：3)

## 题意：
   一堆硬币可以取 $ 1 $ 个也可以取其中一半（硬币个数为偶数才能取），两个人轮流取，两人都采用最佳策略，问先手最多可获得多少硬币。
    
## 分析：
   既然采用最佳策略，那么每次操作一定会让自己取尽量多的，也就是当偶数时取，同时又想让对手尽量少取，那么就是取了一堆后剩下的对手只能取一个，所以贪心很明显。   
   如果有偶数个并且取了偶数个时剩下的硬币个数为奇数，那么就可以取一半，否则就取一个。   
   那么时间复杂度约为 $ O(T \log n) $。   
    
## 注：
   对于有四个硬币的时候先手最多可以取 $ 3 $ 个，上述算法并不能实现，因此特判一下即可。
    
# Code
```cpp
#include <cstdio>
#include <cstdlib>
#define int long long
int solve()
{
	int n,ret=0,now=1;
	scanf("%lld",&n);
	while(n>0)
	{
		int cnt=0;
		if(n%2==0 && n>>1&1)
		    n>>=1,cnt=n;
		else if(n==4)
		    cnt=3,n-=3;
		else
		    cnt=1,n--;
		ret+=cnt*now;
		now^=1;
	}
	return ret;
}
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)
	    printf("%lld\n",solve());
	return 0;
}
```

---

## 作者：kon_tori (赞：2)

### 题意
A 和 B 在进行一种回合制游戏：箱子内共有 $\texttt{n}$ 枚硬币，每次他们有两种选择：

- 只拿走 $\texttt{1}$ 枚硬币。
- 若箱子内有偶数枚硬币，可拿走一半硬币。

A 先拿 B 再拿，直到将所有硬币拿完。

且每次 A 和 B 都执行使自己能拿到**最多硬币**的方案，求最后 A 能拿到的最多硬币数。

共有 $\texttt{T}$ 组数据。

### 思路
刚开始想的最优方案为：

- 优先拿走一半的硬币。
- 如果不能，再拿走 $\texttt{1}$ 枚硬币。

然而按照这种思路， ``WA`` 掉了。

分析之后得出原因：按照这种方案，如果拿走一半硬币后，另一方也能拿走一半硬币，则最后不能拿到最多的硬币。 

真正的最优方案：

- 如果能拿走一半且拿走后另一方不能拿走一半的硬币，才选择拿走一半的硬币。(即 $\texttt{n\%2=0}$ 且 $\texttt{n\%4!=0}$ )
- 否则都只拿走 $\texttt{1}$ 枚硬币。
- 当剩余 $\texttt{4}$ 枚硬币时为特例：此时若拿走一半硬币，则最终 $\texttt{4}$ 枚硬币可以拿走 $\texttt{3}$ 枚。

### 代码实现
$\texttt{code:}$
```cpp
/* light_chaser */
  #include<bits/stdc++.h>
  using namespace std;
  int T;
  long long n;
  long long ans1,ans2;
  
  template<typename T>void read(register T& a){
      T x=0,f=1; 
      register char c=getchar();
      while(!isdigit(c)){
          if(c=='-')f=-1; 
          c=getchar();
      }
      while(isdigit(c))
      x=(x<<1)+(x<<3)+c-'0',c=getchar();
      a=x*f;
  }//快读
  
  int main(){
      /*cin>>T;*/read(T);
      while(T--){//T组数据
          ans1=0;
          //ans2=0;每次清零A，B持有的硬币数
          /*cin>>n;*/read(n);
          while(1){
              if(n==1){
                  ans1++;
                  goto sp;
              }//只剩下1枚硬币可提前结束
              if(n==4){
                  ans1+=3;
                  //ans2++;
                  goto sp;
              }//特判剩下4枚硬币的情况
              if( n%4==0 || n%2==1 ){
                  n--;
                  ans1++;
                  goto sp1;
              }
              if( n%2==0 && n%4!=0 ){
                  n/=2;
                  ans1+=n;
                  goto sp1;
              }//A的回合
              sp1 : ;
              if(n==1){
                  //ans2++;
                  goto sp;
              }//只剩下1枚硬币可提前结束
              if(n==4){
                  ans1++;
                  //ans2+=3;
                  goto sp;
              }//特判剩下4枚硬币的情况
              if( n%4==0 || n%2==1 ){
                  n--;
                  //ans2++;
                  goto sp2;
              }
              if( n%2==0 && n%4!=0 ){
                  n/=2;
                  //ans2+=n;
                  goto sp2;
              }//B的回合
              sp2 : ;
          }
          sp : ;
          cout<<ans1<<"\n";//输出最后A持有的硬币数
      }
      return 0;
  }
```

### 后记
已对排版进行了修复，如仍有不足望指出。

**感谢管理员的辛勤付出！**

蒟蒻的第 $\texttt{12}$ 篇题解，望通过。

---

## 作者：帝千秋丶梦尘 (赞：1)

## [题目链接](https://www.luogu.com.cn/problem/CF1425A)

这题。。。emmm

有坑点。

一开始想着呢，直接能除就除，不然就减，然后$WA$了

然后想着偶数时把先减的算一下，先除的也算一下，取较大值，然后$WA$了

后面仔细思考了一下，发现果然思路不对

举个栗子，假如是$12$

------------

## 开始思路：

小A取$6$，还剩$12-6=6$；小B取$3$，还剩$6-3=3$

小A取$1$，还剩$3-1=2$；小B取$1$，还剩$2-1=1$

小A取到最后的$1$，那么小A取到总值：$6+1+1=8$

但这不是最优解

------------

## 最优解：

小A若先只取$1$，还剩$12-1=11$；小B取$1$，还剩$11-1=10$

这时小A取$5$，还剩$10-5=5$；小B取$1$，还剩$5-1=4$

小A取$2$，还剩$4-2=2$；小B取$1$，还剩$2-1=1$

小A取到了最后的$1$，那么小A取到总值：$1+5+2+1=9$

------------

那这两个的区别在哪呢？

可以发现：偶数最优解中小B不可能取到比1大的数字

而你如果去尝试将奇数代进去时，小A不可能取到比1大的数

那怎么做呢？

可以看到：当12时，小A没有取一半，为什么？

因为取一半后，就会剩6，那小B就能取一半

那我们只要判断下（当前剩余的数/$2$）%$2$是否为$0$

这样就能让另一方一直取$1$了

## 但是4不一样

取到4时，就取一半，这样能取到$3$

如果你跟别的一样判，那么只能取到2了

------------

CODE：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,x,ans,flag;
signed main(void)
{
	std::ios::sync_with_stdio(false);
	cin>>T;
	while(T--)
	{
		cin>>x;
		ans=0,flag=0;
		while(x)
		{
			if(!flag)
			{
				flag=1;
				if(x%2==1)
				{
					ans++;
					x--;
				}
				else{
					if((x/2)%2==0&&x!=4)
					{
						ans++;
						x--;
					}
					else{
						ans+=x/2;
						x-=x/2;
					}
				}
			}
			else{
				flag=0;
				if(x%2==1)
				{
					x--;
				}
				else{
					if((x/2)%2==0&&x!=4)
					{
						x--;
					}
					else{
						x-=x/2;
					}
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Strelitzia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1425A)

---

有点挫败感吧，只是一道 $\mathfrak{1400}$ 的题$\ldots$

一开始的想法是如果是偶数，直接取一半，这当然是错的。

我们考虑一个数：

如果是奇数，只能取一个，不用管。

如果是偶数

a.它的二进制后几位如果是 $\mathrm{1001}\dots\mathrm{11110}$，我们可以直接取一半，

这样对手就只能取一个。

b.如果是 $\mathrm{1011}\dots\mathrm{1000}$，我们可以先取一个一，变成 $0111$ 就转换成了情况 $\operatorname a$

注意 $\operatorname a$ 等于 $\mathrm4$ 时要特判。


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

const int N = 1e5 + 5;

int T;
long long  a,ans;

int main () {
	read(T);
	while (T --) {
		read(a);
		ans = 0;
		int turn = 0;
		long long tmp = 0;
		while (a) {
			turn ++;
			if (a & 1) tmp = 1;
			else {
				if (!(((a >> 1)) & 1) && a > 4) ans ++,a -= 2;
				tmp = a >> 1;
			}
			if (turn & 1) ans += tmp;
			a -= tmp;
		}
		print(ans),putchar('\n');
	}
	return 0;
}
```

---

## 作者：icefake (赞：0)

## 关于题意
Mr. Chanek 正在玩一种游戏，最开始箱子里面有 $n$ 个金币，双方轮流从中拿取金币，在一个回合中，可以选择进行以下两种操作之一的操作：

> 拿走一个金币
> 
> 拿走当前箱子里剩余金币的一半（箱子里面的剩余金币数必须为偶数）

由 Mr. Chanek 开始第一回合，双方都会选择让自己的利益最大化，求 Mr. Chanek 所能拿到的最多金币数。

有 $T$ 组 $n$

## 关于做法
首先对于这道题，因为操作一只能拿走一个金币，所以操作二拿走的金币总是大于等于操作一拿走的金币，因此，我们每回合优先考虑操作二，然后进行暴力模拟，得到最后的最大金币数。

## 至于复杂度
因为每一次都拿走一半的金币，并且如果本回合无法进行操作二，那么进行一次操作一后必定能继续进行操作二，所以我们可以得到该暴力模拟的复杂度约为 $O(T \times long\ n)$，对于 $n \leq 10^{18}, T \leq 10^5$ 的数据完全没问题。

---

## 作者：Qing_喵乖乖喵 (赞：0)

[原题链接](https://codeforces.ml/contest/1425/problem/A)  
简要翻译:  
Mr.Chanek与另一个人玩一个取硬币游戏,他先手。玩家在自己的回合内可以取走硬币堆中的一个。如果硬币堆里有偶数个硬币，玩家也可以选择取走硬币总数的一半。两名玩家都是绝对聪明的，他们都希望拿到手中的硬币尽可能多。    
这道题的坑点在于**游戏人的目的是最大化手上的硬币数量，而不是比对手多来赢得比赛**。  
在可以取 $n/2$ 时马上取确实能保证比对手多，但是这不一定能使手上的硬币最大化。  
也就是说，我们希望取走 $n/2$ ，但不一定现在。  
我们需要再单独取走1个逼迫对手取走下一个，使我在取走 $n/2$ 后**留下的还是一个奇数**。  
这里需要注意的是 $n=4$ 时，直接取走2要更优。  
~~目测每次n为偶数就直接取 $n/2$ 的不是TLE就是WA，至于为什么会T，我也很好奇~~  
```cpp
#include <cstdio>
typedef long long ll;
#define REG register
inline char getc(){
    static char buf[1<<14],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<14,stdin),p1==p2)?EOF:*p1++;
}
inline ll scan(){
    REG ll a=0; REG char ch=0;
    while(ch<48) ch=getc();
    while(ch>=48) a=a*10+ch-48,ch=getc();
    return a;
}
inline void print(ll x){
    if(x>9){
        print(x/10); putchar(x%10+48);
    }else{
        putchar(x+48);
    }
}
ll t,x;
int main(){
    t=scan();
    while(t--){
        x=scan();
        REG ll c=1,d,ans=0;
        while(x){
            if(x&1) d=1;
            else{
                if((x>>1)&1) d=x>>1;
                else{
                    if(x>4) x-=2,ans++;
                    d=x>>1;
                }
            }
            if((c++)&1) ans+=d;
            x-=d;
        }
        print(ans); putchar('\n');
    }
    return 0;
}
```  

---

