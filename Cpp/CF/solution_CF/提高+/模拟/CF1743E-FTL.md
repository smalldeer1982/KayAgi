# FTL

## 题目描述

Monocarp is playing a video game. In the game, he controls a spaceship and has to destroy an enemy spaceship.

Monocarp has two lasers installed on his spaceship. Both lasers $ 1 $ and $ 2 $ have two values:

- $ p_i $ — the power of the laser;
- $ t_i $ — the reload time of the laser.

When a laser is fully charged, Monocarp can either shoot it or wait for the other laser to charge and shoot both of them at the same time.

An enemy spaceship has $ h $ durability and $ s $ shield capacity. When Monocarp shoots an enemy spaceship, it receives $ (P - s) $ damage (i. e. $ (P - s) $ gets subtracted from its durability), where $ P $ is the total power of the lasers that Monocarp shoots (i. e. $ p_i $ if he only shoots laser $ i $ and $ p_1 + p_2 $ if he shoots both lasers at the same time). An enemy spaceship is considered destroyed when its durability becomes $ 0 $ or lower.

Initially, both lasers are zero charged.

What's the lowest amount of time it can take Monocarp to destroy an enemy spaceship?

## 说明/提示

In the first example, Monocarp waits for both lasers to charge, then shoots both lasers at $ 10 $ , they deal $ (5 + 4 - 1) = 8 $ damage. Then he waits again and shoots lasers at $ 20 $ , dealing $ 8 $ more damage.

In the second example, Monocarp doesn't wait for the second laser to charge. He just shoots the first laser $ 25 $ times, dealing $ (10 - 9) = 1 $ damage each time.

## 样例 #1

### 输入

```
5 10
4 9
16 1```

### 输出

```
20```

## 样例 #2

### 输入

```
10 1
5000 100000
25 9```

### 输出

```
25```

# 题解

## 作者：Leasier (赞：8)

Update on 2022.10.26：感谢 [T_E_I_O_](https://www.luogu.com.cn/user/140694)。

Update on 2024.11.8：感谢 [Ebola](https://www.luogu.com.cn/user/20158) 和 [w9095](https://www.luogu.com.cn/user/569235)。

首先你可以不进行任何一次双炮连发。

现在假定我们要进行双炮连发，注意到每进行完一次就相当于回到了初始状态（即两个炮都未装上）。

考虑 dp，设 $f_i$ 表示通过若干单发 + 最后恰好一次双炮连发使敌方耐久度减少 $i$ 的最小时间，$g_i$ 表示通过若干次若干单发 + 双炮连发的连续组合使敌方耐久度减少 $i$ 的最小时间。

初值：$f_0 = g_0 = 0$。

转移：

- 对于 $g_i$：$g_i = \displaystyle\min_{j = 0}^{i - 1} (g_j + f_{i - j})$。

- 对于 $f_i$：考虑枚举连发前第一种炮弹发射了 $j$ 发，其中 $j \geq 0$ 且 $j(p1 - s) + (p1 + p2 - s) \leq i$，则第二种炮弹至少发射了 $\lceil \frac{i - (j(p1 - s) + (p1 + p2 - s))}{p2 - s} \rceil$ 发，则此时我们令 $f_i \leftarrow \min(f_i, \max(t_1(j + 1), t_2(\lceil \frac{i - (j(p1 - s) + (p1 + p2 - s))}{p2 - s} \rceil + 1)))$ 即可。

答案：$\displaystyle\min_{i = h} g_i$。

时间复杂度为 $O(h^2)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

ll dp1[10007], dp2[10007]; 

inline int max(int a, int b){
	return a > b ? a : b;
}

inline ll min(ll a, ll b){
	return a < b ? a : b;
}

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

int main(){
	int p1, p2, h, s, n;
	ll t1, t2, ans;
	scanf("%d %lld", &p1, &t1);
	scanf("%d %lld", &p2, &t2);
	scanf("%d %d", &h, &s);
	n = h + max(p1, p2);
	ans = min(t1 * ((h - 1) / (p1 - s) + 1), t2 * ((h - 1) / (p2 - s) + 1));
	for (int i = 1; i <= n; i++){
		dp1[i] = dp2[i] = 4e18;
		for (int j = 0; j * (p1 - s) + (p1 + p2 - s) <= i; j++){
			ll x = i - (j * (p1 - s) + (p1 + p2 - s));
			dp1[i] = min(dp1[i], max(t1 * (j + 1), t2 * ((x == 0 ? 0 : (x - 1) / (p2 - s) + 1) + 1)));
		}
		for (int j = 0; j < i; j++){
			dp2[i] = min(dp2[i], dp2[j] + dp1[i - j]);
		}
		if (i >= h) ans = min(ans, dp2[i]);
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

[CF1743E FTL](https://www.luogu.com.cn/problem/CF1743E)

考虑到任意时刻若两激光同时发射，则递归变为 $h$ 更小的子问题。因此，设 $f_i$ 表示初始两激光均没有充能时，打出 $i$ 伤害的最少时间。

假设在同时发射前两激光均有空闲时间，则同时减小空闲时间可得伤害相同且时间更少的方案。因此，在同时发射激光前，至少一个激光没有空闲时间。

直接枚举其发射次数即可得到 $\mathcal{O}(h ^ 2)$ 解法，因为每个激光的发射次数显然不会超过 $h$。设时间为 $t = kt_1$ 或 $t = kt_2$，$c_i = \lfloor \frac t {t_i}\rfloor$，则当 $c_1, c_2 > 0$ 时才会同时发射。因此伤害为 $c_1p_1 + c_2p_2 - (c_1 + c_2 - [c_1, c_2 > 0]) s$。

[代码](https://codeforces.com/contest/1743/submission/183795573) 和题解稍有不同。

---

## 作者：Lgx_Q (赞：2)

**数据范围：1≤p[1,2],h≤5000**

显然，这题应在攻击力方面暴力。

首先感觉这题像是 DP，但是却有着充能时间的限制。但是如果两个激光炮一起攻击，那么两个激光炮的充能时间都会变成 $0$。容易想到，记状态 $f[i]$ 表示对敌方攻击了 $i$ 点攻击力，并且最后一次攻击为两个激光炮一同攻击，的最少时间。由于在最后一次，两个激光炮同时攻击，因此充能都为 $0$。

不难想到转移：$f[i]=\min_{j=0}^{i-1}\{f[j]+cost(i-j)\}$，其中 $cost(attack)$ 为至少造成 $attack$ 点伤害，并且最后一次是两个激光炮同时攻击，的最少时间。

计算 $cost$ 似乎很困难。可以设计一个函数 $Find(usedTime1,usedTime2,attack)$ 表示第一个激光炮已使用 $usedTime1$ 点时间，第二个激光炮已使用 $usedTime2$ 点时间，总共要造成 $attack$ 点伤害的最小时间。显然，$Find$ 函数可以通过二分的方式得出。于是 $cost(attack)=Find(t_1,t_2,attack)$。

计算答案？在打败敌方前的最后一次攻击如果不是两个激光炮一起攻击呢？我们当然可以枚举在打败前的最后一次两个激光炮同时攻击后，敌方的血量 $i$ 。然后利用 $Find(0,0,i)$ 计算答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=15010;
int p1,t1,p2,t2,h,s,f[maxn],ans,cost[maxn];
int Find(int ted1,int ted2,int n)
{
	int lo=max(ted1,ted2),hi=1e16;
	while(lo<=hi)
	{
		int mid=lo+hi>>1;
		int c1=(mid-ted1)/t1,c2=(mid-ted2)/t2;
		if(c1*(p1-s)+c2*(p2-s)>=n) hi=mid-1;
		else lo=mid+1;
	}
	return lo;
}
signed main()
{
	scanf("%lld%lld%lld%lld%lld%lld",&p1,&t1,&p2,&t2,&h,&s);
	f[0]=0;
	for(int i=p1+p2-s;i<=h+p1+p2-s;i++)
	{
		cost[i]=Find(t1,t2,i-p1-p2+s);
	}
	for(int i=1;i<=h+p1+p2-s;i++)
	{
		f[i]=0x3f3f3f3f3f3f3f3f;
		for(int j=0;i-j>=p1+p2-s;j++)
		{
			int tmp=i-j;
			if(tmp<p1+p2-s) continue;
			f[i]=min(f[i],f[j]+cost[tmp]);
		}
	}
	ans=f[h];
	for(int i=h+1;i<=h+p1+p2-s;i++) ans=min(ans,f[i]); 
	for(int i=0;i<h;i++)
	{
		ans=min(ans,f[i]+Find(0,0,h-i));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：红黑树 (赞：1)

## [题目](https://codeforces.com/problemset/problem/1743/E)

## 题解

考虑 DP，$t_1$ 和 $t_2$ 都是 $10^{12}$，不能放进状态里，那么状态就确定了，$f_i$ 表示造成 $i$ 点伤害所需的最少时间。

首先考虑只用一种武器的转移：
$$f_{i + p - s} = f_i + t_i$$

两种武器一起用：
枚举武器 $k$ 的使用次数 $j$，则前 $j - 1$ 次都使用 $k$ 武器，第 $j$ 次两种一起用，则
武器 $k$ 创造的伤害是 $\left(j - 1\right) \cdot \left(p_k - s\right)$
另一把武器也不能闲着，可以趁武器 $k$ 冷却的时间继续攻击，则另一把武器创造的伤害是 $\lvert \dfrac{j \cdot t_k - t_{3 - k}}{t_{3 - k}} \rvert \cdot \left(p_{3 - k} - s\right)$
最后的两把武器一起攻击的伤害是 $p_1 + p_2 - s$

那么，设这三个伤害加起来的总伤害是 $u$，则
$$f_{i + u} = f_i + j \cdot t_k$$
## 代码
```cpp
// Please submit with C++14! It's best to use C++20 or higher version.
constexpr bool __MTCS__ = 0;  // Spectre (n@rbtr.ee)
#ifndef LOCAL                 // By rbtree (https://rbtr.ee)
#pragma region HEAD           // DO OR DIE
#endif
#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#ifdef ___RB_DEBUG___
#include "rb_debug.h"
#else
#define dbg(...)
#endif
#define ra (scanf("%lld", &la), la)
#define se(exp) begin(exp), end(exp)
#define LIKELY(exp) __builtin_expect(bool(exp), 1)
#define UNLIKELY(exp) __builtin_expect(bool(exp), 0)
#define qmx(exp1, exp2, exp3) exp1 = exp3(exp1, exp2)

typedef long long tp;
using namespace std;
void __Cored__(tp);
tp la;

signed main(/* >_< */) {
for (static tp __TCS__ = __MTCS__ ? ra : 1, __NOW__ = 0; __NOW__ < __TCS__;
     __Cored__(++__NOW__)) {
}
return 0;
}

#ifndef LOCAL
#pragma endregion HEAD
#endif

////////////////////////////////////////////////////////////////////////////////

constexpr tp Hat_H = 5003;

tp f[Hat_H];

void __Cored__([[maybe_unused]] tp __TID__) {
tp p1 = ra, t1 = ra, p2 = ra, t2 = ra, h = ra, s = ra;
memset(f, 0x3f, sizeof f);
f[0] = 0;
for (tp i = 0; i < h; ++i) {
  qmx(f[min(i + p1 - s, h)], f[i] + t1, min);
  qmx(f[min(i + p2 - s, h)], f[i] + t2, min);
  for (tp j = 1; j <= h; ++j) {
    if (j * t1 >= t2) {
      qmx(f[min(i + (j - 1) * (p1 - s) + (j * t1 - t2) / t2 * (p2 - s) + p1 +
                    p2 - s,
                h)],
          f[i] + j * t1, min);
    }
    if (j * t2 >= t1) {
      qmx(f[min(i + (j - 1) * (p2 - s) + (j * t2 - t1) / t1 * (p1 - s) + p2 +
                    p1 - s,
                h)],
          f[i] + j * t2, min);
    }
  }
}
printf("%lld\n", f[h]);
}

//*/
```

---

## 作者：CENRUIYANG (赞：1)

考虑dp，需要考虑的状态有：
1. 造成伤害
2. 充能状态
3. 时间

充能状态/时间这两维值域太大了，难以设进数组中，所以我们考虑将造成伤害作为数组下标，时间作为数组的值。一个简单的想法就是设 $f_i$ 表示造成 $i$ 的伤害所需的最少时间，但是会发现这样做难以转移，因为我们无法知道充能状态。所以考虑把状态定义的复杂一些使得充能状态可以知道。

设 $f_i$ 表示造成 $i$ 的伤害，两个炮正好同时打了一次所需的最少时间，这样定义状态之后，每个状态所对应的都是完全未充能，方便我们转移。

初始化 $f_0=0$，其余均为 $+\infty$，$0$ 时刻实际上也可以看作是正好同时打完。

考虑转移，我们一定是能打就打，然后到要同时打之前，其中一个停止等另外一个充能完毕一起打出。所以我们发现，其中一个炮一定是一直打的，“关键时间”只有 $k \times t_0,k \times t_1(k \in [1,h])$，只需拿这些“关键时间”来更新即可。

需要注意的是，最后一次不一定是同时打的，所以我们需要在原有的状态上尝试能打就打，更新最终的答案，但也别忘了与最后一次是同时打的取 $\max$。

[代码](https://codeforces.com/contest/1743/submission/180153078)

---

## 作者：pioneer2000 (赞：0)

### 思路：

首先这一题长得就很像动态规划，本想以时间为状态去转移 $t$ 时间内伤害最大值，当时我们看数据范围就可以发现 $t=10^{12}$，所以转换一下思路，将伤害作为动态规划的对象，这时候题目的状态就确定下来了：$f_i$ 表示造成 $i$ 点伤害所需的最小时间。

但这还是比较难写转移（太蒟蒻了），于是跑去看了下题解-----好，我们可以将状态在简化一下，将 $f_i$ 表示造成 $i$ 点伤害且**最后一发是双炮连发**所需的最小时间。

那么万一最后一发不是双炮连发怎么办，别急，先往后看。

那么现在我们在来考虑转移：这其实不难想，我们可以用两层循环，外层循环枚举伤害值，而内层伤害枚举前伤害值加上至少的伤害值所需的最短时间。

那么转移式即为 $f_i=\min_{j=0}{f_j^{i-1}\operatorname{+}w_{i-j}}$。此时我们只要处理 $w_{i-j}$ 的问题就行了。

此时不妨去预处理，去二分时间得出打出 $x$ 伤害所需的最短时间（******我们算的是打出双炮连发后造成伤害的最短时间******）。

最后还有一种最后一发不是双炮连发的可能没有解决，此时我们可以枚举最后一次使用双炮连发后的飞船血量，将其时间与最后的 $w_j$ 加起来，与双炮连发的情况一起取最小值即可。

注意：最后不是双炮连发的情况取得是剩余血量的最大时间。

代码较为简单，不给出了。

---

## 作者：Imiya (赞：0)

发现每一次同时攻击后，两艘飞船都会回到初始状态，所以可以尝试 dp 找什么时候同时攻击。

设 $f_i$ 表示血量减到 $i$ 所需的最短时间。

设 $g_i$ 表示从初始状态先使用若干次单独攻击，最后使用一次共同攻击总共打出 $i$ 点伤害所需的最短时间。

那么有 $f_i=\min\limits_{j\in(i,h]}(f_j+g_{j-i})$。

然后考虑如何算 $g$。

设单独打出了 $x$ 个一号和 $y$ 个二号。

$$harm=x\cdot(p_1-s)+y\cdot(p_2-s)+p_1+p_2-s$$
$$T=\max((x+1)t_1,(y+1)t_2)$$

可以直接枚举 $i$ 和 $j$ 更新对应的 $g$，复杂度是 $O(h^2)$ 的。注意 $harm$ 的上界应当是 $h+\max(p_1,p_2)$，因为要考虑到溢出的伤害。

发现最后可能还会来一坨单独伤害。所以还要记录一个 $g'_i$，表示从初始状态只用单独攻击，打出 $i$ 点伤害的最短时间。计算方式和 $g$ 类似。

$$harm=x\cdot(p_1-s)+y\cdot(p_2-s)$$
$$T=\max(xt_1,yt_2)$$

枚举即可。

最后 $ans=\max\limits_{i\in[0,h]}(f_i+\max\limits_{j\in[i,h+\max(p_1,p_2)]}(\max(g_j,g'_j)))$。

#### code

```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int N=10110,inf=0x3f3f3f3f3f3f3f3f;
int p1,t1;
int p2,t2;
int h,s;
int g[N][2],f[N];
void init(){
    cin>>p1>>t1>>p2>>t2>>h>>s;
    memset(g,0x3f,sizeof(g));
    g[0][0]=g[0][1]=0;
    for(int i=0;i*(p1-s)<=h+max(p1,p2);i++){
        for(int j=0;j*(p2-s)+i*(p1-s)+p1+p2-s<=h+max(p1,p2);j++){
            int harm=j*(p2-s)+i*(p1-s)+p1+p2-s;
            g[harm][0]=min(g[harm][0],max((i+1)*t1,(j+1)*t2));
        }
    }
    for(int i=0;i*(p1-s)<=h+max(p1,p2);i++){
        for(int j=0;j*(p2-s)+i*(p1-s)<=h+max(p1,p2);j++){
            int harm=j*(p2-s)+i*(p1-s);
            g[harm][1]=min(g[harm][1],max(i*t1,j*t2));
        }
    }
}
signed main(){
    // freopen("read.in","r",stdin);
    init();
    memset(f,0x3f,sizeof(f));
    f[h]=0;
    for(int i=h-1;i>=0;i--){
        for(int k=h;k>i;k--){
            f[i]=min(f[i],f[k]+g[k-i][0]);
        }
    }
    int ans=inf;
    if(p1-s>=h)ans=min(ans,t1);
    if(p2-s>=h)ans=min(ans,t2);
    for(int i=0;i<=h;i++){
        for(int j=i;j<=h+max(p1,p2);j++){
            ans=min(ans,f[i]+min(g[j][0],g[j][1]));
        }
    }
    cout<<ans;
    return 0;
}
```


---

