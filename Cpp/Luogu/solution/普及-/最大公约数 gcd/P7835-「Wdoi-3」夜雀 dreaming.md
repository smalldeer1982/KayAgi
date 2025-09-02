# 「Wdoi-3」夜雀 dreaming

## 题目背景

作为幻想乡食物链顶端的幽幽子，一直都是老板娘米斯蒂娅的噩梦！

尽管幽幽子一般而言是不会选择吃她的，但奈何日有所思夜有所梦，米斯蒂娅做了一个梦，一个交杂着幻想与现实的梦，或者说，那就是幻想中的现实……

尽管米斯蒂娅不知道这天什么时候会到来，但她不敢放松警惕，于是老板娘向你求助了……

## 题目描述

作为一道签到题，为了能让选手更好的发挥手速，米斯蒂娅决定提供这题的题意简述：[隙间传送](https://www.luogu.com.cn/paste/2dwm3f7z)。

---

在梦中，幽幽子来到了夜雀餐厅。似乎是由于异变的影响，本来就贪吃的幽幽子此刻变得更加可怕。

米斯蒂娅一共会做 $n$ 道菜，用来满足所有顾客的需求，并试图增加自己存活的概率。这些菜的编号为 $0,1,2$ 直到 $n-1$。同时，幽幽子会进行 $k$ 次点餐。

- 本题中，我们记**点菜事件**为 $\operatorname{order}(t,x)$ ，表示顾客向米斯蒂娅发起一份请求，希望她在 $t$ 时刻制作并端上菜品 $x$ 。
- 我们用一个三元组 $(t_i,x_i,y_i)$ 描述幽幽子发起第 $i$ 次点餐。在每次点餐中，幽幽子会发起 $\operatorname{order}(t_i,x_i)$ 。然而幽幽子的欲望是不能被满足的。因此，当幽幽子在 $t_i$ 时刻收到菜品时，会再次发起 $\operatorname{order}(2\cdot t_i,(x_i+y_i)\bmod n)$ ！更加不幸地，此过程会不断累加，接着她会发起 $\operatorname{order}(3\cdot t_i,(x_i+2\cdot y_i)\bmod n)$ 乃至更多……
- 总而言之，幽幽子的第 $i$ 次点餐 $(t_i,x_i,y_i)$ 会执行这样的操作：

$$\operatorname{order}(j\cdot t_i,(x_i+(j-1)\cdot y_i)\bmod n)(j=1,2,3,\cdots)$$

由于幽幽子会发起无数次点餐请求，所以米斯蒂娅是不可能使她满足的。但为了不辜负大家的期望，米斯蒂娅决定竭尽全力拖延时间。作为老板娘，她有着超凡的厨艺：

- 每一个时刻，米斯蒂娅都能做出**无限**份菜，**但菜只能是同一种类**。

如果一个时刻幽幽子点的菜没能被立即做好（幽幽子并不愿意吃上一个时刻做好的菜哦），那么她就会大发雷霆，在这一时刻**立即**摧毁夜雀餐厅。米斯蒂娅想知道她能坚持多久（坚持多久指的是最多能坚持多少个时刻使得这些时刻内幽幽子不会摧毁餐厅，时刻**从 $1$ 开始计数**）。如果她能坚持 $9961^{9961}$ 时刻或以上的话（在此题中，你可以认为 $9961^{9961}$ 是无穷大），请输出 `Mystia will cook forever...`。


## 说明/提示

#### 样例 1 解释

在时刻 $4$，幽幽子同时点了菜品 $3$ 和菜品 $2$，于是夜雀餐厅会被摧毁，答案为 $4-1=3$。

---

#### 数据范围及约定

$$\def\arraystretch{1.5}\begin{array}{|c|c|c|c|c|}\hline
\textbf{Subtask} & \bm{k} & \bm{\max\{t_i\}} & \textbf{特殊性质} & \textbf{分值}\cr\hline
\textsf1 & =1 & \text{无特殊限制} & \text{无} & 10 \cr\hline
\textsf2 & \leq 10 & \leq 10 & \text{无} & 20 \cr\hline
\textsf3 & \text{无特殊限制} & \text{无特殊限制} & \text{A} & 30\cr\hline
\textsf4 & \text{无特殊限制} & \text{无特殊限制}& \text{无}& 40 \cr\hline
\end{array}$$

特殊性质 $\text{A}$ ：保证对于所有的 $i$ ，满足 $y_i = 0$ 。

对于 $100\%$ 的数据，满足：
- $1 \le t_i,n \leq 10 ^ 9$。
- $0 \le x_i,y_i  \leq 10 ^ 9$。
- $1 \le k \leq 1000 $。

## 样例 #1

### 输入

```
4 3
2 1 2
3 1 1
4 2 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
2 1 2
3 0 1```

### 输出

```
Mystia will cook forever...```

# 题解

## 作者：幽云蓝 (赞：13)

这里是八云蓝的官方题解~

$\textbf{Subtask1}$

读题分。直接输出 `Mystia will cook forever...` 即可。

$\textbf{Subtask2}$

猜想答案要么是无解，要么在一个很小的范围内。根据上述性质可以直接枚举时刻然后暴力计算有没有出现不同的菜。

可以证明如果不是无解，答案的理论上界为 $179$。顺带一提，为了更好的送分，蓝没有卡这个上界，所以你设 $100$ 甚至设 $10$ 都能过（不过遇到这种部分分呢，蓝还是建议大家把上界开大一些的）。

$\textbf{Subtask3}$

注：本篇题解称题目中幽幽子的点餐为“点菜方式”，$x_i$ 为初始菜，$\Delta x_i$ 为变化量。

非常接近正解的一档部分分。容易发现，一个时刻只要存在两种菜不同，那么这个时刻餐厅就会被摧毁。由于变化量为 $0$，换句话说，你只需要枚举初始菜不同的两种点菜方式，然后计算出它们出现时刻重合的最小时刻（即设枚举的两个点菜方式为 $x$ 和 $y$，最小时刻即为 $\operatorname{lcm}(t_x,t_y)$），最后将所有计算出的时刻取 $\min$ 然后 $-1$ 即可。无解情况就是没有出现初始菜不同的两种点菜方式，特判即可。

$\textbf{Subtask4}$

注：本篇题解中记“满足两种点菜方式在这一时刻都会点出菜品并且菜品不同的最小时刻”为关键时刻。

依然考虑枚举两个不同（不是初始菜不同哦）的点菜方式 $x$ 和 $y$，如果对于所有的点菜方式都能够计算出它们的关键时刻，那么对计算出的所有时刻取 $\min$ 然后 $-1$ 即可。问题现在变成了对于两个点菜方式 $x$ 和 $y$ 计算它们的关键时刻，首先考虑 $\operatorname{lcm}(t_x,t_y)$ 处，如果相同那么该时刻即为关键时刻，如果两个点菜方式在这个时刻点菜相同的话考虑 $2\times \operatorname{lcm}(t_x,t_y)$ 处，如果仍然相同，那么显然有两个时刻间变化量相同，也就可以得出这两种点菜方式无关键时刻，否则它们的关键时刻即为时刻 $2\times \operatorname{lcm}(t_x,t_y)$。记得特判无解，如果所有点菜方式见均无关键时刻，那么输出 `Mystia will cook forever...`。

---

## 作者：Yukinoshita_Yukino (赞：5)

~~题面看着很乱，实则水得一p~~

咳咳，言归正传，先看一眼题面：

> 有 $k$ 个人在无限多的盒子里放球，第 $i$ 个人只能在 $t_i$ 的倍数编号的盒子里放球，第 $j$ 次放的球的颜色编号是 $[x_i+(j-1) \times y_i]\bmod n$ ， 询问盒子里出现两个不同颜色编号的球的盒子最小编号是多少。

显然，两个人( $x$ 和 $y$ )放的球会在 $t_x$ 和 $t_y$ 的最小公倍数和**最小公倍数的倍数**里相遇,最小公倍数记为 $ \operatorname{lcm}(x,y)$ 。

也就是说我们需要考虑每一个人和其他人之间的 $ \operatorname{lcm}$ 的倍数编号的盒子里球颜色有没有冲突，显然会超时。

能不能优化一下呢？

考虑一个问题，如果对于两个人 $x$ 和 $y$ ，$ \operatorname{lcm}(x,y)$ 编号的盒子里两球颜色不冲突，$2 \times \operatorname{lcm}(x,y)$ 编号的盒子里两球也颜色不冲突，是否后续 $ \operatorname{lcm}$ 编号的盒子也不冲突呢？

答案是肯定的，因为球颜色的变化是周期性的，如果两个周期球的颜色都相同的话，后续周期球的颜色也肯定相同。

所以只需考虑 $ \operatorname{lcm}(x,y)$ 和 $2 \times \operatorname{lcm}(x,y)$ ，时间复杂度 $\operatorname{O}(k^2)$ 。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
int t[1010],x[1010],y[1010],b[1010],ans=0x7fffffffff;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
signed main()
{
	n=read();
	k=read();
	for(register int i=1;i<=k;i++)
	{
		t[i]=read();
		x[i]=read();
		y[i]=read();
	}
	for(register int i=1;i<=k;i++)
	{
		for(register int j=i+1;j<=k;j++)
		{
			int lcm=t[i]*t[j]/__gcd(t[i],t[j]);
			if((x[i]+((lcm/t[i])-1)*y[i]%n)%n!=(x[j]+((lcm/t[j])-1)*y[j]%n)%n) ans=min(ans,lcm);
			if((x[i]+((lcm*2/t[i])-1)*y[i]%n)%n!=(x[j]+((lcm*2/t[j])-1)*y[j]%n)%n) ans=min(ans,lcm*2);
		}
	}
	if(ans==0x7fffffffff) cout<<"Mystia will cook forever...";
	else cout<<ans-1;
    return 0;
}



```


---

## 作者：HerikoDeltana (赞：3)

## [Wdoi R3] 夜雀 dreaming

[洛谷 | P7835 [Wdoi R3] 夜雀 dreaming](https://www.luogu.com.cn/problem/P7835)

这个题是 Wdoi R3 的 A 题，也就是签到题，但是很可惜的我没签上（

### 题意简述

[简化版的题意](https://www.luogu.com.cn/paste/2dwm3f7z)算是很清晰了，因为时间轴的上限是 $9966^{9966}-1$，所以直接求出所有的时间点的倍数再去判断是木大的。

### 思路简述

于是我们考虑同一个时间会在什么情况下出现两个不同的菜。因为放入菜的时间都是每个命令时间的倍数，所以我们考虑对于两个时间点的 $\operatorname{lcm}$，那么根据题意我们最后选取的 $\operatorname{lcm}$ 越小越好，于是我们在枚举之后进行一次排序。（用优先队列也可以）

因为题目中计算每个时间点所点菜的公式已经给出，于是我们就可以每次取出 $\operatorname{lcm}$ 后计算对应的两条命令在这个时间点的菜，若不同那么这个时间点就是答案。

……但是这样还不对，因为假如相同的话，我们再考虑 $2 \times \operatorname{lcm}$ 处，如果再相同就真的没解了。

场上我就因为没考虑 $2 \times \operatorname{lcm}$ 的情况而~~喜提两个 WA~~ 痛失签到机会。

### Code

感谢 @[Fan_Tuan](https://www.luogu.com.cn/user/371178) 大佬帮忙[纠错代码](https://www.luogu.com.cn/discuss/show/342857)。

```cpp
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <map>
#define Heriko return
#define Deltana 0
#define Romanno 1
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false);cin.tie(0)
using namespace std;

template<typename J>
I void fr(J &x)
{/*快读略*/}

template<typename J>
I void fw(J x,bool k)
{/*快写略*/}

CI MXX=1005,NXX=8e7+5;

I LL Gcd(LL x,LL y){Heriko !y?x:Gcd(y,x%y);}

I LL Lcm(LL x,LL y){Heriko (x*y)/Gcd(x,y);}

LL n,k;

struct Order
{
    LL t,x,y;
}

co[MXX];

struct List
{
    LL val,a,b;
}

ko[NXX];

LL cnt;

I bool Cmp(const List &x,const List &y) {Heriko x.val<y.val;}

S main()
{
    fr(n),fr(k);
    for(R int i(1);i<=k;++i) fr(co[i].t),fr(co[i].x),fr(co[i].y);
    for(R int i(1);i<=k;++i)
        for(R int j(i+1);j<=k;++j)
                ko[++cnt]=(List){Lcm(co[i].t,co[j].t),i,j};
    sort(ko+1,ko+1+cnt,Cmp);
    for(R LL i(1);i<=cnt;++i)
    {
        if(ko[i].val<=0) continue;
        LL a(ko[i].a),b(ko[i].b);
        LL va((n+co[a].x+((ko[i].val/co[a].t)-1)*co[a].y)%n);
        LL vb((n+co[b].x+((ko[i].val/co[b].t)-1)*co[b].y)%n);
        LL vx((n+co[a].x+(((ko[i].val/co[a].t)<<1)-1)*co[a].y)%n);
        LL vy((n+co[b].x+(((ko[i].val/co[b].t)<<1)-1)*co[b].y)%n);
        if(va!=vb)
        {
            fw(ko[i].val-1,1);
            Heriko Deltana;
        }
        else if(vx!=vy)
        {
            fw(((ko[i].val)<<1)-1,1);
            Heriko Deltana;
        }
    }
    puts("Mystia will cook forever...");
    Heriko Deltana;
}
```

---

## 作者：一只小H (赞：2)

## 题意简述

有 $k$ 个人依次在盒子里放球。第 $i$ 个人会选择**所有**编号为 $t_i$ 的倍数的盒子，对第 $j$ 小的放入一个颜色为 $(x_i+(j-1)y_i)\bmod n$ 的球。

输入：

* 颜色数量 $n$，人数 $k$。
* $k$ 行，每行三个整数 $t_i$、$x_i$、$y_i$。

输出：

* 输出编号最小的放置了不止一种**颜色**的球的盒子编号**减一**。如果不存在这样的盒子输出 `Mystia will cook forever...`。

## 题目分析

观察数据范围发现 $k \le 1000$，可以从这里找突破口，发现每两个人之间判断一次不会超时。

要想某个盒子不止一种颜色，首先得有不止一个人在盒子里放球，可以通过求公倍数来找出两人都放了球的盒子，然后再判断颜色。

从最小公倍数开始，当颜色不相等时记录 $ans$ 取最小值，颜色相等则选第二小的公倍数，如果再相等那么往后就没有不相等的了，因为每次颜色变化的值取模后都是一样的，原来的颜色加上这个值也是一样的。

详情请见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k;
long long t[1001], x[1001], y[1001];
long long ans = LONG_LONG_MAX;
int main()
{
    cin >> n >> k;

    for (int i = 1; i <= k; ++i)
    {
        cin >> t[i] >> x[i] >> y[i];

        //每两个人之间都要进行判断
        for (int j = 1; j < i; ++j)
        {
            long long gcd = __gcd(t[j], t[i]);

            /*
            lcm(t[j],t[i]) = t[j] * t[i] / gcd(t[j],t[i])
            a 表示两数最小公倍数是 t[i] 的几倍
            a = lcm(t[j],t[i])/t[i] = t[j] / gcd(t[j],t[i])
            b 同理
            */

            long long a = t[j] / gcd, b = t[i] / gcd;
            for (int k = 1; k <= 2; ++k)
            {
                //题中给的式子
                int aa = (y[i] * (a * k - 1) % n + x[i]) % n;
                int bb = (y[j] * (b * k - 1) % n + x[j]) % n;

                if (aa != bb)
                {
                    ans = min(ans, t[i] * (t[j] / gcd) * k);
                    break;
                }
            }
        }
    }
    if (ans == LONG_LONG_MAX)
        cout << "Mystia will cook forever..." << endl;
    else
        cout << ans - 1 << endl;
    return 0;
}
```


---

## 作者：TonyYin (赞：1)

考场解法，比其他题解复杂，但好像顺便说明了其他题解的结论？

## 题意

[剪贴板](https://www.luogu.com.cn/paste/2dwm3f7z) 里的题目描述比较友好。

有无限个盒子，从 $1$ 开始编号，有 $n$ 个球，从 $0$ 开始编号。有 $k$ 个人。

$k$  个人往盒子里放球，第 $i$ 个人只能在编号为 $t_i$ 的倍数的盒子放球，第 $j$ 次放球的颜色编号为 $[x_i+(j-1)\times y_i]\bmod n$.

求：编号最小的盒子，满足盒子里存在两球颜色不同。

$n\leq 10^9$，$k\leq 10^3$.

## 分析

注意到 $k\leq 10^3$，容易想到暴力枚举两个人，设这两人为 $(u, v)$.

$u$ 和 $v$ 会在一些盒子里同时放球，这些盒子的编号为 $c\times \operatorname{lcm}(t_u, t_v)$，$c$ 是正整数。

对于第 $c\times \operatorname{lcm}(t_u, t_v)$ 个盒子，是 $u$ 第 $\dfrac{\operatorname{lcm}(t_u, t_v)}{t_u}\times c$  次放球，是 $v$ 第 $\dfrac{\operatorname{lcm}(t_u, t_v)}{t_v}\times c$ 次放球。

对于某个 $c$，假设第 $c\times \operatorname{lcm}(t_u, t_v)$ 个盒子中，$u$ 和 $v$ 所放球的颜色相同，那么有同余方程：
$$
x_u+(c\times \frac{\operatorname{lcm}(t_u, t_v)}{t_u}-1)\cdot y_u
\equiv
x_v+(c\times \frac{\operatorname{lcm}(t_u, t_v)}{t_v}-1)\cdot y_v
\pmod{n}
$$
其中只有 $c$ 是未知量，整理一下式子，即可用 $\rm{ExGcd}$ 求出 $c$ 的最小正整数解 $c_{min}$.

若 $c_{min}\geq 2$，说明第 $\operatorname{lcm}(t_u, t_v)$ 个盒子满足条件，用 $\operatorname{lcm}(t_u, t_v)$ 更新答案。

若 $c_{min}=1$，继续判断 $c=2$ 是否为可行解。若 $c\neq 2$，则用 $2\times \operatorname{lcm}(t_u, t_v)$ 更新答案。否则  $(u, v)$ 这种情况无解，对答案无贡献。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1008;
const int inf = 0x3f3f3f3f3f3f3f3f;
int n, k;
inline int exgcd(int a, int b, int &x, int &y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	int r = exgcd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return r;
}
inline int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
int t[MAXN], x[MAXN], y[MAXN];
signed main() {
	scanf("%lld%lld", &n, &k);
	for(int i = 1; i <= k; i++) {
		scanf("%lld%lld%lld", &t[i], &x[i], &y[i]);
	}
	int ans = inf;
	for(int i = 1; i <= k; i++) {
		for(int j = 1; j <= k; j++) {
			if(i == j) continue;
			int xx, yy;
			int Lcm = t[i] / gcd(t[i], t[j]) * t[j];
			int a = Lcm / t[i] * y[i] - Lcm / t[j] * y[j];
			int b = x[j] - x[i] + y[i] - y[j];
			if(a < 0 && b < 0) continue;
			int d = gcd(a, n);
			if(b % d != 0) {
				ans = min(ans, Lcm);
				continue;
			} else {
				exgcd(a, n, xx, yy);
				int tmp = ((b/d*xx) % (n/d) + (n/d)) % (n/d);
				if(tmp >= 2) ans = min(ans, Lcm);
				if(tmp == 1 && (n/d) != 1) {
					ans = min(ans, 2 * Lcm);
				}
			}
		}
	}
	if(ans == inf) cout << "Mystia will cook forever...\n";
	else cout << ans - 1 << endl;
	return 0;
}
```



---

## 作者：MuYC (赞：0)

(补一发关于答案是 $2 \times \operatorname{lcm}$ 或者是 $\operatorname{lcm}$ 的证明)

枚举一对 $i,j$， $k_it_i = k_jt_j = \operatorname{lcm}(t_i,t_j)$。

题目要求我们找一个最小的 $s$ 使得 $x_i + y_i(sk_i - 1) \equiv x_j + y_j(sk_j - 1)$ 不成立。

因为 $a + b \equiv c + d\mod p$ 等价于：$a - d \equiv c - b \mod p$

（可以移项）

那么 $y_i(sk_i - 1) - y_j(sk_j - 1) \equiv x_j - x_i$。

则 $sy_ik_i - sy_jk_j \equiv (x_j - y_j) - (x_i - y_i)$

左右都是一个常数，可以解方程， $s$ 与得到的结果同余的时候这个式子成立，不成立就是 s 与结果不同余的情况。

当 $(y_ik_i - y_jk_j) \equiv 0 \mod p$，并且 $(x_j - y_j) - (x_i - y_i) = 0$，本式对于任意 $s$ 成立，那么就意味着无解。

否则我们暴力循环这个 $s$ 即可（因为式子只在同余的情况下成立，只用循环两次）。

所以答案只可能是无解或者是某两个 $t$ 的最小公倍数或者是这个最小公倍数的两倍。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 50;
#define int long long
int Mod, K;
int t[MAXN], x[MAXN], y[MAXN], ans = 2e18;

signed main() {
    cin >> Mod >> K;
    for(int i = 1 ; i <= K ; i ++) 
        cin >> t[i] >> x[i] >> y[i];
    for(int i = 1 ; i <= K ; i ++) {
        for(int j = i + 1 ; j <= K ; j ++) {
            int G = __gcd(t[i], t[j]), lcm = t[i] / G * t[j];
            int Ki = lcm / t[i], Kj = lcm / t[j], f = x[j] - y[j] - x[i] + y[i];
            f %= Mod, f += Mod, f %= Mod;
            if((y[i] * Ki - y[j] * Kj % Mod + Mod) % Mod == 0 && !f) continue;
            for(int s = 1 ; ; s ++) {
                if(s * (y[i] * Ki - y[j] * Kj % Mod + Mod) % Mod == f) continue;
                ans = min(ans, s * lcm);
                break;
            }
        }
    }
    if(ans == 2e18) cout << "Mystia will cook forever...";
    else cout << ans - 1;
    return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

## 题目简述

你有无限个盒子，盒子编号从 $1$ 到正无穷。同时你有 $n$ 种颜色的球，颜色用 $0\sim n-1$ 的整数来表示。

有 $k$ 个人依次在盒子里放球。第 $i$ 个人会选择**所有**编号为 $t_i$ 的倍数的盒子，对选中的盒子中编号最小的的放入一个颜色为 $x_i$ 的球，第二小的放入一个 $(x_i+y_i)\bmod n$ 颜色的球，第三小的放入一个颜色为 $(x_i+2y_i)\bmod n$ 颜色的球……第 $j$ 小的放入一个颜色为 $(x_i+(j-1)y_i)\bmod n$ 的球。

在所有人都放完球后，请输出编号最小的放置了两种或两种以上**颜色**的球的盒子编号减一。如果不存在这样的盒子输出 `Mystia will cook forever...`。

## 解题思路

看到数据范围，$k\leq 10^3$，很容易想到对任意两人共同放的盒子进行枚举。

对于两人组 $i,j$ 来说，同时放到的盒子的编号必为 $t_i,t_j$ 的倍数。

所以最小的编号为 $\operatorname{lcm}(t_i,t_j)$ 如果这时在该盒子内两球的编号不同，就更新答案，否则考虑编号为 $2\times \operatorname{lcm}(t_i,t_j) $ 处，若该盒子内两球的编号也相同就说明等编号变化内两球的颜色变化相同，后面的也肯定相同，就不用枚举下去了。

## 部分分

#### Subtask 1

$k=1$ 肯定没有所求盒子，输出 `Mystia will cook forever...`。

#### Subtask 2

所求的时刻必然比较小，使用数组枚举或者暴力枚举都可以。

#### Subtask 3

$y_i=0$，这对启发正解有帮助。思路与正解相同。

#### Subtask 4

正解。

## 参考代码

```cpp
#include<iostream>
using namespace std;
#define ll long long
const int MAXN=1e3+5;
ll n,k;
ll ans=1e18;
struct order{
	ll t,x,y;
}a[MAXN];
ll gcd(ll p,ll q){
	return ((p%q==0)?q:gcd(q,p%q));
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++)
		cin>>a[i].t>>a[i].x>>a[i].y;//输入
	for(int i=1;i<=k;i++)
		for(int j=i+1;j<=k;j++){
			int G=gcd(a[i].t,a[j].t);
			ll T1=a[i].t/G,T2=a[j].t/G;
			if((a[i].x+(T2-1)*a[i].y-a[j].x-(T1-1)*a[j].y)%n!=0)
				ans=min(ans,T1*T2*G);
			else if((T1*a[j].y-T2*a[i].y)%n!=0)//偷了个懒，这与题解描述的式子是等价的。
				ans=min(ans,2*T1*T2*G);
		}
	if(ans==1e18)
		cout<<"Mystia will cook forever...";
	else
		cout<<ans-1;
} 
```


---

