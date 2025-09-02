# Controllers

## 题目描述

You are at your grandparents' house and you are playing an old video game on a strange console. Your controller has only two buttons and each button has a number written on it.

Initially, your score is $ 0 $ . The game is composed of $ n $ rounds. For each $ 1\le i\le n $ , the $ i $ -th round works as follows.

On the screen, a symbol $ s_i $ appears, which is either $ \texttt{+} $ (plus) or $ \texttt{-} $ (minus). Then you must press one of the two buttons on the controller once. Suppose you press a button with the number $ x $ written on it: your score will increase by $ x $ if the symbol was $ \texttt{+} $ and will decrease by $ x $ if the symbol was $ \texttt{-} $ . After you press the button, the round ends.

After you have played all $ n $ rounds, you win if your score is $ 0 $ .

Over the years, your grandparents bought many different controllers, so you have $ q $ of them. The two buttons on the $ j $ -th controller have the numbers $ a_j $ and $ b_j $ written on them. For each controller, you must compute whether you can win the game playing with that controller.

## 说明/提示

In the first sample, one possible way to get score $ 0 $ using the first controller is by pressing the button with numnber $ 1 $ in rounds $ 1 $ , $ 2 $ , $ 4 $ , $ 5 $ , $ 6 $ and $ 8 $ , and pressing the button with number $ 2 $ in rounds $ 3 $ and $ 7 $ . It is possible to show that there is no way to get a score of $ 0 $ using the second controller.

## 样例 #1

### 输入

```
8
+-+---+-
5
2 1
10 3
7 9
10 10
5 3```

### 输出

```
YES
NO
NO
NO
YES```

## 样例 #2

### 输入

```
6
+-++--
2
9 7
1 1```

### 输出

```
YES
YES```

## 样例 #3

### 输入

```
20
+-----+--+--------+-
2
1000000000 99999997
250000000 1000000000```

### 输出

```
NO
YES```

# 题解

## 作者：yingkeqian9217 (赞：5)

## 前言

小学数学题。。。

## 题目描述

给你一个长度为 $n$ 的只包含 + 或 - 的字符串 $s$，共有 $q$ 次询问。每次询问给出两个 $a_j,b_j$，你需要遍历一遍字符串 $s$，到第 $i$ 位时，可以选择 $a_j$ 或者 $b_j$，如果当前字符 $s_i$ 是 +，你的分数加上你选择的数；反之，减去你选择的数。若你的分数初始是 0，问你能否使最终分数为 0。

## 分析

显然，答案与字符串的加减符号个数 $P,M$ 有关，与顺序无关。于是问题变成了，有 $n$ 个数，每个数可以从 $a,b$ 中选择，最终能否使其中 $P$ 个和剩下 $M$ 个和一样。

不难发现，有一部分数可以抵消掉，最终可以使两边都是不同的数，不妨设 $M$ 部分剩下 $M_0$ 个全是 $a$，$P$ 部分剩下 $P_0$ 个全是 $b$，两边和一样当且仅当 $a\times M_0=b\times P_0$，其中 $M-M_0=P-P_0(0\le M_0\le M,0\le P_0\le P)$。

简单的进行转化，即 $\dfrac{a}{b}=\dfrac{P_0}{M_0}$。左边约分，得 $\dfrac{a'}{b'}=\dfrac{P_0}{M_0}(a'=\frac{a}{\gcd(a,b)},b'=\frac{b}{\gcd(a,b)})$。考虑做差，$(a'-b') | (P_0-M_0)$。而 $P_0-M_0=P-M$，所以 $(a'-b') | (P_0-M_0)$ 的**充分条件**是 $(a'-b') | (P-M)$。注意在实现中，要对 $a=b$ 的情况进行特判。

最后，我们还要对 $M_0,P_0$ 进行构造，判断是否满足 $M-M_0=P-P_0(0\le M_0\le M,0\le P_0\le P)$。假设 $P-M=k(a'-b')$，可以发现，$P_0=ka',M_0=kb'$，验证即可。

还有一点值得注意，我们刚才是假设加号个数 $M$ 对应 $a$。显然我们要保证 $\min(P,M)$ 对应 $\max(a,b)$，为了方便，我们可以使 $P,M$ 的顺序与 $a,b$ 的顺序相同。当然，这样的话，就是 $P$ 对应 $a$ 了。

## Code
```cpp
#include<bits/stdc++.h>
#define P (n+sum>>1)
#define M (n-sum>>1)
#define K (abs(sum)/abs(x-y)) 
#define Nsw (P<M&&x>y||P>M&&x<y)
#define judge(x,y) (x*K<=y)
using namespace std;
typedef long long ll;
ll n,q,sum;
char ch;
signed main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		cin>>ch;
		sum+=(ch=='+'?1:-1);//记录P-M
	}
	scanf("%lld",&q);
	while(q--){
		ll x,y,g;
		scanf("%lld%lld",&x,&y);
		if(Nsw) swap(x,y);//注意P,M与a,b的对应关系
		if(x==y){//特判
			printf(sum?"NO\n":"YES\n");
			continue;
		}
		g=__gcd(x,y),x/=g,y/=g;
		if(!(sum%(x-y))&&judge(x,P)&&judge(y,M))
     		 printf("YES\n");//构造合法解
		else printf("NO\n");
	}
	return 0;
}
```
蒟蒻无能，有错误可以在评论区提出捏~

---

## 作者：Night_fall (赞：3)

这题貌似只需要最简单的语法知识，完全是一道 ~~乱搞的~~ 构造题。

但是需要 ~~强大的~~ 数学能力。

言归正传：

#### 1.

首先想一个最简单的思路：dfs。

就是在每次询问时把两个数用 dfs 填到每个符号里去，再判断 $\verb!YES!$ 或 $\verb!NO!$。

但很明显，$O(2^nT)$，这是过不去的。

#### 2.

首先可以分析给定的 $n$ 个符号。

又根据加减法的交换律和结合律得知，符号的顺序可以任意调换，那么就可以直接**统计加号与减号的个数**。

那么就可以把 dfs 变成简单的遍历，

分别求出 $a,b$ 分别与加减配对的个数，遍历其中两个，另外两个就可以求得。

很明显，$O(n^2T)$，还是过不去。

#### 3.

再看一眼数据范围，得知只有 $O(T)$ 才能过。

简单来说，就是不能用遍历，要把每次询问压成 $O(1)$。

现在就需要数学才能了。

------------

(下面为了讲述方便，把加号个数记为 $n$，减号个数记为 $m$）

最简单的就是可以把 $a$ 全填一个符号，$b$ 同理，使正负能互相抵销，直接:

```if(n==m){cout<<"YES";continue;}```

那么假如 $a,b$ 有正有负呢？

$-a,+a$ 会抵消，同理，$-b,+b$ 也会。

来看看抵消过程。

不难发现：抵销去的加号个数等于减号个数。

那么最后就一定会有 $±ax±by$（$x$，$y$ 为常数）。

换而言之，就是指 $n-x=m-y$。

因为 $1<=a,b<=10^9$，所以排除 $ax$ 与 $by$ 同号的情况，具体证明如下：

- 因为 $a,b>0$ 且 $x,y>0$
- 所以 $ax+by>0$ 且 $-ax-by<0$
- 所以排除同号情况

那么接下来的问题就是如何求 $x,y$ 了。

显而易见的，有 $±ax±by=0$。

后面为了简化问题，可以使一个大小关系固定，那么就只需要考虑一种情况了。

可以考虑 $ax-by=0$。

即 $ax=by$。

因为 $x,y$ 必须符合 $ax=by$,

所以如果存在合法的 $x,y$，那么它们一定是由 $ax=by$ 中最小的 $x,y$ 乘倍得来的。

把“最小的 $x,y$”翻译一下，就是 $a,b$ 的最小公倍数。

遍历一遍所有可能的乘倍是可行的，但是时间应该不够。

可以再优化一下，直接把 $x,y$ 作差，把 $n,m$ 作差，比较两者所差的倍数，就可以知道要乘多少倍了。

最后是输出：

1. 如果加号个数等于减号个数，全为 $\verb!YES!$。 （直接全部填一个数抵销掉）
2. 如果 $a=b$，那么在1不成立时，全为 $\verb!NO!$。 （相当于只有一个数，肯定不行）
3. 如果 $(n-m)/(x-y)$ 不为整数，即乘倍不为整数时，输出 $\verb!NO!$。 （不是整数倍，如果还想抵消的话，$x,y$ 就会变成小数）
4. 如果最后需要的 $x,y$ 比 $n,m$ 多，输出 $\verb!NO!$。

------------

### code

感觉前面讲的不是很清楚，多加了一些注释。

还有就是讲解的变量名和代码里的不太一样，代码是以前写的，懒得改了，多看看注释。

```cpp
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long

int u,d;

signed main(){
    int n,T;
    cin>>n;
    for(int i=1;i<=n;i++){
        char ch;
        cin>>ch;
        if(ch=='+') u++; //统计个数
        else d++;
    }
    cin>>T;
    int cha=abs(u-d);//作差
    if(u<d) swap(u,d);//固定大小关系，简化问题
    if(cha==0){
    	while(T--) cout<<"YES\n";//加号个数等于减号个数，全部抵消
    	exit(0); //相当于 return 0;
    }
    while(T--){
        int a,b;
        cin>>a>>b;
        int gcd=__gcd(a,b);//求最小公倍数中的一个过程。
        //最小公倍数其实是 a*b/gcd，但那只是为了求x,y所经历的过程，不用写
        a/=gcd,b/=gcd; //把a,b当做x,y，下同
        int ct=abs(a-b);//作差
        if(ct==0||cha/ct!=cha*1.0/ct){ //a=b或者不是整数倍
            cout<<"NO\n";
            continue;
        }
        if(a<b) swap(a,b);//固定大小关系
        //为什么到这里才固定呢？因为前面没有用到x,y，即使用到也加了绝对值，所以其实前面固定也是可以的
        if(cha/ct*a<=u&&cha/ct*b<=d) cout<<"YES\n"; //x,y < n,m，同时a,u都是大的，b,d都是小的，一一对应
        else cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：2)

# CF1776L Controllers 题解
## 分析
先把题目形式化。设 $n$ 次加减中有 $x$ 个加，$y$ 个减，其中 $a$ 加了 $u$ 次，减了 $v$ 次，显然 $b$ 加了 $x-u$ 次，减了 $y-v$ 次。题目则要求 $u\cdot a-v\cdot a+(x-u)\cdot b-(y-v)\cdot b=0$，转换一下得 $(u-v)\cdot a=-(x-y)\cdot b+(u-v)\cdot b$，把右边的 $(u-v)\cdot b$ 拎到左边，得 $(u-v)\cdot (a-b)=-(x-y)\cdot b$。

接下来就是要解这个式子，分两种情况：

- 当 $a-b$ 为 $0$ 时，$x-y$ 必为 $0$，否则无解。
- 当 $a-b$ 不为 $0$ 时，显然 $u-v= \dfrac {-(x-y)\cdot b }{a-b}$。很明显，$0 \le u \le x$，$0 \le v \le y$，通过这两个不等式解得 $-y \le u-v \le x$，

代码内判断这两种情况即可。

## 示例代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace Raiden
{
    int n;
    signed work()
    {
        cin >> n;
        int x = 0, y = 0;
        for (int i = 1; i <= n; i++)
        {
            char c;
            cin >> c;
            if (c == '+')
            {
                x++;
            }
            else
            {
                y++;
            }
        }
        int T;
        cin >> T;
        while (T--)
        {
            int a, b;
            cin >> a >> b;
            if (a == b)
            {
                if (x == y)
                {
                    cout << "YES" << endl;
                }
                else
                {
                    cout << "NO" << endl;
                }
                continue;
            }
            int m = x - y;
            if (b * m % (b - a))
            {
                cout << "NO" << endl;
                continue;
            }
            long long k = b * m / (b - a);
            if (-y <= k && k <= x)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

