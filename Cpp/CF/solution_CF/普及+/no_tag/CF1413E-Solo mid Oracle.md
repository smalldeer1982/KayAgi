# Solo mid Oracle

## 题目描述

Meka-Naruto plays a computer game. His character has the following ability: given an enemy hero, deal $ a $ instant damage to him, and then heal that enemy $ b $ health points at the end of every second, for exactly $ c $ seconds, starting one second after the ability is used. That means that if the ability is used at time $ t $ , the enemy's health decreases by $ a $ at time $ t $ , and then increases by $ b $ at time points $ t + 1 $ , $ t + 2 $ , ..., $ t + c $ due to this ability.

The ability has a cooldown of $ d $ seconds, i. e. if Meka-Naruto uses it at time moment $ t $ , next time he can use it is the time $ t + d $ . Please note that he can only use the ability at integer points in time, so all changes to the enemy's health also occur at integer times only.

The effects from different uses of the ability may stack with each other; that is, the enemy which is currently under $ k $ spells gets $ k\cdot b $ amount of heal this time. Also, if several health changes occur at the same moment, they are all counted at once.

Now Meka-Naruto wonders if he can kill the enemy by just using the ability each time he can (that is, every $ d $ seconds). The enemy is killed if their health points become $ 0 $ or less. Assume that the enemy's health is not affected in any way other than by Meka-Naruto's character ability. What is the maximal number of health points the enemy can have so that Meka-Naruto is able to kill them?

## 说明/提示

In the first test case of the example each unit of damage is cancelled in a second, so Meka-Naruto cannot deal more than 1 damage.

In the fourth test case of the example the enemy gets:

- $ 4 $ damage ( $ 1 $ -st spell cast) at time $ 0 $ ;
- $ 4 $ damage ( $ 2 $ -nd spell cast) and $ 3 $ heal ( $ 1 $ -st spell cast) at time $ 1 $ (the total of $ 5 $ damage to the initial health);
- $ 4 $ damage ( $ 3 $ -nd spell cast) and $ 6 $ heal ( $ 1 $ -st and $ 2 $ -nd spell casts) at time $ 2 $ (the total of $ 3 $ damage to the initial health);
- and so on.

One can prove that there is no time where the enemy gets the total of $ 6 $ damage or more, so the answer is $ 5 $ . Please note how the health is recalculated: for example, $ 8 $ -health enemy would not die at time $ 1 $ , as if we first subtracted $ 4 $ damage from his health and then considered him dead, before adding $ 3 $ heal.

In the sixth test case an arbitrarily healthy enemy can be killed in a sufficient amount of time.

In the seventh test case the answer does not fit into a 32-bit integer type.

## 样例 #1

### 输入

```
7
1 1 1 1
2 2 2 2
1 2 3 4
4 3 2 1
228 21 11 3
239 21 11 3
1000000 1 1000000 1```

### 输出

```
1
2
1
5
534
-1
500000500000```

# 题解

## 作者：dead_X (赞：3)

## 1 前言
恶心的数学题（
## 2 题意
一个技能：$a$ 的瞬间伤害，之后 $c$ 秒每秒恢复 $b$ ，冷却 $d$ 秒，问最优情况下能造成的**瞬时最高总伤害**，如果可以是无穷输出 $-1$ 。
## 3 思路
先想怎么样是 $-1$ ，易得条件为 $a>b\times c$ 。

再向不是 $-1$ 会怎么样。

你会发现，一个技能当且仅当前 $\large\frac{a-1}{b}$ 秒会参与答案计算！因为在这个时间之后，这个技能已经对总答案产生了一个非负的贡献，还不如不用这个技能。

然后，因为 $d$ 秒能放一个技能，所以在第 $\large\lfloor\frac{a-1}{b*d}\rfloor$ 次放技能的时候，就能取到最优解。
## 4 代码
```
#include<bits/stdc++.h>
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
long long f(int a,int b,int c,int d,int ll)
{
    return -ll*(ll+1)/2ll*b*d+a*(ll+1);
}
signed main()
{
    int n=read();
    for(int i=1; i<=n; i++) 
    {
        int a=read(),b=read(),c=read(),d=read();
        if(a>b*c) 
        {
            puts("-1");
            continue;
        }
        int t=((a-1)/b)/d;//first t time works
        printf("%lld\n",f(a,b,c,d,t));
    }
    return 0;
}
```

---

## 作者：tommymio (赞：3)

借用一下 @Dead_X 的一句话题意，就是求采取最优策略时，敌人**在某个时刻受到的最大伤害总和**。

一开始还看错题目了，这里提醒一下治疗是会叠加的（

先考虑最大伤害总和为 $\infty$ 的情况，显然有 $a>b\times c$，即对于一次回复，即使进行完毕，还是会受到伤害。这样的情况下如果进行无限轮，造成的伤害是无限大的。

那么，对于最大伤害总和不为 $\infty$ 的情况，则是 $a\leq b\times c$ 了。这提醒我们，如果在 $0$ 时刻发动攻击后，在 $\lceil\frac{a}{b}\rceil$ 时刻时 $0$ 时刻攻击造成的贡献就会变成一个非负数。那么这样还不如不打。所以最大伤害总和一定出现在 $0\sim\lfloor\frac{a-1}{b}\rfloor$ 时刻。

继续考虑，如果最后这段时刻中，某一段时刻只是在回血而没有被攻击，还不如取最后一次攻击时造成的伤害总和更优。所以，最大伤害总和一定会出现在第 $\left\lfloor\frac{\lfloor\frac{a-1}{b}\rfloor}{d}\right\rfloor=\lfloor\frac{a-1}{bd}\rfloor$ 次攻击时（注意，此处攻击次数计数不包括 $0$ 时刻发动的攻击）。

计算一下包括第 $\lfloor\frac{a-1}{bd}\rfloor$ 次攻击在内，造成的最大伤害即可。答案为：

$$
(\lfloor\frac{a-1}{bd}\rfloor+1)\times a- \sum_{i=1}^{\lfloor\frac{a-1}{bd}\rfloor} i\times d\times b 
$$

可以使用等差数列求和化为封闭形式。时间复杂度为 $O(T)$。

```cpp
#include<cstdio>
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
int main() {
    int T=read();
    while(T--) {
        int a=read(),b=read(),c=read(),d=read();
        int n=(a-1)/b/d;
        if(a>b*1ll*c) printf("-1\n");
        else printf("%lld\n",(n+1)*1ll*a-d*(1+n)*1ll*n/2*b);
    }
    return 0;
}
```

---

## 作者：lyhqwq (赞：2)

# Solution

逆天数学题。

当 $a>b\times c$ 时答案为 $-1$。

考虑不是 $-1$ 的情况，我们将求最大生命转化为求最大伤害。

对于 $a\leq b \times c$ 的情况，一次攻击会在 $\lceil \dfrac{a}{b} \rceil$ 时变为非负数，对总的伤害没有贡献，所以最大伤害一定在 $[0,\lfloor \dfrac{a-1}{b} \rfloor]$ 取到。

这中间会攻击 $\dfrac{a-1}{b\times d} +1$ 次。

答案为 
$(\lfloor\dfrac{a-1}{b\times d}\rfloor+1)\times a-\sum\limits_{i=1}^{\lfloor\frac{a-1}{b\times d}\rfloor} i \times b\times d$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int _;
signed main(){
    scanf("%lld",&_);
    while(_--){
        int a,b,c,d;
        scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        if(a>b*c) puts("-1");
        else{
            int t=(a-1)/(b*d);
            printf("%lld\n",(t+1)*a-b*d*t*(t+1)/2);
        }
    }
    return 0;
}

```

---

## 作者：Brute_Force (赞：0)

### 题意
有一个技能：会有 $a$ 的瞬间伤害，之后 $b$ 秒每秒恢复 $c$，冷却 $d$ 秒，试求最优情况下能造成的瞬时最高总伤害，如果可以是无穷输出 $-1$。（注意一点，恢复会叠加）（引用自 @[dead_X](/user/111055) 的题意）
### 思路
这是一道数学题，考虑到以下两种情况：

1. 结果为 $-1$ 的情况，即 $ a > b \times c$。输出 $-1$。

2. 其他情况，则需要进行数学计算，输出最高的伤害。

由于恢复可以叠加，所以解答的过程中可能会更复杂一点。我们可以分析一下：

先说明一下 $-1$ 的情况，它代表着如果能每一轮都恢复自身的血量小于伤害，那么结果肯定是无限大。

除特判条件外，如果最后这段时刻中，只是在恢复自身血量而没有攻击，程序得立即停下，不然回血后就不是攻击的最大值了。由上述分析可得知，伤害的最大值往往是在第 $\large\lfloor\frac{a-1}{b \times d}\rfloor$ 的时候产生。

### 代码
核心代码：
```cpp
if(a>b*c) cout<<-1<<endl;
else long long j=(a-1)/b/d;
cout<<(j+1)*a-d*(1+j)*j/2*b<<endl;
```

---

## 作者：Halberd_Cease (赞：0)


与众不同的三分做法。

首先明确这个奶量是要叠加的。

然后题目要求的最大的初始血量，就是你从最初开始的某一个时间点造成伤害减去怪奶回来的血量的最大值。

如果总共奶的没有一刀砍的多就是无穷大的伤害。

然后考虑奶的没有砍的快的情况。

将攻击和奶按周期考虑，因为奶的总量比攻击的多，所以在完整周期结束后，怪的血会比原来不低，因此最优的策略应该是一刀接一刀地砍，然后在某一个瞬间达到最大的伤害总量。

设函数 $f(k)$ 表示在砍第 $k$ 次时达到的伤害。

函数明显单峰，可以三分。

首先，如果是第一次砍就没有奶，第 $k$ 次砍就有 $k-1$ 轮奶，其中最近的一次奶已经奶了 $d$ 次，次近的已经奶了 $2d$ 次,以此类推，如果没有就算没有。

然后可以等差数列在 $O(1)$ 的时间内求出。

然后就没有了。

给出 $f(k)$ 的代码：
```cpp
int f(int k)
{
    int atk=k*a;
    int bw=c/d;
    if(bw>k-1)
    {
        k--;
        int mo=b*k*d;
        //cout<<b*d<<' '<<mo<<'\n';
        return (b*d+mo)*k/2-atk;
    }
    int mo=b*d*bw;
    //cout<<b*d<<' '<<mo<<'\n';
    return (k-1-bw)*c*b+(b*d+mo)*bw/2-atk;
}
```



---

## 作者：Composite_Function (赞：0)

$$\text{思路}$$

- 注意 恢复是可以叠加的，就是如果 $c < d$，它的恢复不会被打断。

因为攻击和恢复存在一周期，我们想到会分两种情况：

1. 攻击大于恢复值，即 $a > b \times d$，无论有多少血量，在不断重复下一定可以成功击败。
2. 攻击小与等于恢复值，即 $a \le b \times d$，这样正常的攻击贡献是小于等于 $0$ 的。这说明，会在 $[0,\lfloor\dfrac{a-1}{b} \rfloor]$ 间的一个时刻会有最大伤害，因为此时怪物来不及回满血。算上攻击间隔，最大伤害会在第 $\lfloor\dfrac{\lfloor\dfrac{a-1}{b} \rfloor}{d}\rfloor=\lfloor\dfrac{a-1}{b\times d} \rfloor$ 伤害是打出。然后用打出的伤害减去恢复值就是答案。

------------

核心代码如下：

```
if (a > b * c) cout << -1 << endl;
else {
	int e = (a - 1) / b / d;
	int f = (e + 1) * a;
	int g = d * ((e + 1) * e / 2) * b;
	cout << f - g << endl;
}
```

------------


---

## 作者：BFqwq (赞：0)

首先先考虑在一个周期中敌人的最大回血。

显然就是尽可能多的回血周期叠在一起，然后可能最后会有一个部分周期。如果这个最大回血值小于一刀的伤害，那么无论对方血量多高都可以砍死（即每个周期伤害都高于回血）。

然后如果无法砍死无数血量，则必然在某刀之后对方死亡。如果这一刀之后对方在下一个周期的回血量无法赶上下一刀的伤害，则我可以继续拖延再砍一刀。否则我就只能到此为止，不然总伤害就会降低。

而如果有 $g$ 个周期叠加，则对方下一个周期的回血量为 $g\times b\times d$，而我们要求这个值必须小于等于 $a$，于是 $g=a\div(b\times d)$（此处表示整除）。

然后我们只要计算出前面 $g$ 个周期的总伤害和总回血就行。注意因为在 $0$ 时刻砍了一刀，所以一共是 $g+1$ 刀。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200],str[200];int tt;
inline void print(int x,char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=120005;
int t;
signed main(){
	t=read();
	while(t--){
		int a=read(),b=read(),c=read(),d=read();
		int tim=c/d;
		int mx=tim*b*d+(c-d*tim)*b;
		if(a>mx){
			print(-1);
			continue;
		}
		int g=a/(b*d);
		int sh=(g+1)*a;
		int hf=(b*d)*(g+1)*g/2;
		print(sh-hf);
	}
	return 0;
}
```


---

