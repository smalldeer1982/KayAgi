# Kill the Monster

## 题目描述

Monocarp is playing a computer game. In this game, his character fights different monsters.

A fight between a character and a monster goes as follows. Suppose the character initially has health $ h_C $ and attack $ d_C $ ; the monster initially has health $ h_M $ and attack $ d_M $ . The fight consists of several steps:

1. the character attacks the monster, decreasing the monster's health by $ d_C $ ;
2. the monster attacks the character, decreasing the character's health by $ d_M $ ;
3. the character attacks the monster, decreasing the monster's health by $ d_C $ ;
4. the monster attacks the character, decreasing the character's health by $ d_M $ ;
5. and so on, until the end of the fight.

The fight ends when someone's health becomes non-positive (i. e. $ 0 $ or less). If the monster's health becomes non-positive, the character wins, otherwise the monster wins.

Monocarp's character currently has health equal to $ h_C $ and attack equal to $ d_C $ . He wants to slay a monster with health equal to $ h_M $ and attack equal to $ d_M $ . Before the fight, Monocarp can spend up to $ k $ coins to upgrade his character's weapon and/or armor; each upgrade costs exactly one coin, each weapon upgrade increases the character's attack by $ w $ , and each armor upgrade increases the character's health by $ a $ .

Can Monocarp's character slay the monster if Monocarp spends coins on upgrades optimally?

## 说明/提示

In the first example, Monocarp can spend one coin to upgrade weapon (damage will be equal to $ 5 $ ), then health during battle will change as follows: $ (h_C, h_M) = (25, 9) \rightarrow (25, 4) \rightarrow (5, 4) \rightarrow (5, -1) $ . The battle ended with Monocarp's victory.

In the second example, Monocarp has no way to defeat the monster.

In the third example, Monocarp has no coins, so he can't buy upgrades. However, the initial characteristics are enough for Monocarp to win.

In the fourth example, Monocarp has $ 4 $ coins. To defeat the monster, he has to spend $ 2 $ coins to upgrade weapon and $ 2 $ coins to upgrade armor.

## 样例 #1

### 输入

```
4
25 4
9 20
1 1 10
25 4
12 20
1 1 10
100 1
45 2
0 4 10
9 2
69 2
4 2 7```

### 输出

```
YES
NO
YES
YES```

# 题解

## 作者：include_BM (赞：9)

玩家死亡需要的攻击次数为 $\left\lceil\frac{hc}{dm}\right\rceil$，对方死亡需要的攻击次数为 $\left\lceil\frac{hm}{dc}\right\rceil$，当 $\left\lceil\frac{hc}{dm}\right\rceil \ge \left\lceil\frac{hm}{dc}\right\rceil$ 时玩家能够获胜。

枚举这 $k$ 次技能中有几次用于增加生命值，几次用于增加攻击力，若有一种情况能够胜利，则输出 `YES`，否则输出 `NO`。

代码：

```cpp
ll hc,dc,hm,dm,k,w,a,f;
signed main(){
    for(int T=read();T;--T){
        hc=read(),dc=read(),hm=read(),dm=read();
        k=read(),w=read(),a=read(),f=0;
        for(int i=0;i<=k;++i)
            if((hc+i*a+dm-1)/dm>=(hm+dc+(k-i)*w-1)/(dc+(k-i)*w)){
                puts("YES");f=1;break;}
        if(!f) puts("NO");
    }
    return 0;
}
```

注：$\left\lceil\frac{n}{m}\right\rceil=\left\lfloor\frac{n+m-1}{m}\right\rfloor$。

---

## 作者：FFTotoro (赞：5)

模拟题。输入各项数据，枚举硬币的分配：将主角的生命值和攻击能力分别加上硬币给予的附加值，然后先求出怪兽杀死主角需要的局数，即 $\left\lceil\dfrac{h_C}{d_M}\right\rceil$，再求主角杀死怪兽需要的局数，即 $\left\lceil\dfrac{h_M}{d_C}\right\rceil$，如果前者大于等于后者，则主角能赢，否则尝试下一种枚举。如果每一种方案都不能行的话，则证明主角不可能赢。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long // 不开 long long 见祖宗
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int a,b,c,d,e,f,g,x,y; cin>>a>>b>>c>>d>>e>>f>>g;
    bool w=true;
    for(int i=0;i<=e;i++){ // 枚举
      int b1=b+i*f,a1=a+(e-i)*g;
      if(!(a1%d))x=a1/d; // 特判能整除的情况
      else x=ceil((double)a1/d);
      if(!(c%b1))y=c/b1;
      else y=ceil((double)c/b1);
      if(x>=y){w=false; cout<<"YES\n"; break;}
    }
    if(w)cout<<"NO\n"; // 每一种方案都不行
  }
  return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：4)

### 题目翻译

在某款电脑游戏里，角色初始生命 $hc$，初始攻击 $dc$。怪物初始生命 $hm$，初始攻击 $dm$。

而你有 $k$ 次机会，将攻击力**永久**提升 $w$ 或者将生命**永久**提升 $a$ 。

每一轮，角色攻击怪物，怪物掉 $dc$ 生命。怪物攻击角色，角色掉 $dm$ 生命。

问若干轮以后，角色能否击杀怪物并且角色存活。

击杀怪物定义为：怪物生命 $\ngtr 0$。

角色存活定义为：角色生命 $>0$。

### 题目思路(不完整)

我们枚举这 $k$ 次机会，分别是加攻击还是加生命。然后判断角色增加这些属性后，能否击败怪物。

而且每一轮的攻击，如果角色击败了怪物，怪物不会攻击角色。也就是说，怪物可以少打一轮伤害。

### 题目代码(不完整)

```cpp
void solve()
{
	long long hc,dc,hm,dm,k,w,a;
	cin>>hc>>dc>>hm>>dm>>k>>w>>a;//输入属性
	for(long long i=0;i<=k;i++)
	{
		long long x=i,y=k-i;//枚举加攻击或加生命
		long long rnd=ceil(hm*1.0/(dc+x*w));//用怪物血量除以角色攻击得到轮数
		if(dm*(rnd-1)<hc+a*y)//如果怪物打出的伤害比角色生命少
		{
			puts("YES");//可以通关
			return;
		}
	}
	puts("NO");
}
```

但是，看似没问题，实则会在第13个数据点错误。

让我们导出看一下。

```
Input
1
1 1
1000000000000000 1000000000
200000 1 10000000000

Output
YES

Answer
NO
```

我们进行调试，分别输出每个循环的结果。

```
1
1 1
1000000000000000 1000000000
200000 1 10000000000
加攻击机会数:0 加生命机会数:200000 总轮数:1000000000000000 怪物打出伤害:2003764204206896640 角色生命:2000000000000001
加攻击机会数:1 加生命机会数:199999 总轮数:500000000000000 怪物打出伤害:1001882101603448320 角色生命:1999990000000001
加攻击机会数:2 加生命机会数:199998 总轮数:333333333333334 怪物打出伤害:667921401402298880 角色生命:1999980000000001
加攻击机会数:3 加生命机会数:199997 总轮数:250000000000000 怪物打出伤害:-8722430986553051648 角色生命:1999970000000001
YES
```

答案竟然爆 ```long long``` 了。

那么我们没办法了吗？错！```__int128``` 了解一下？

我们给总轮数换上 ```__int128``` 即可。

### 总结

思想是对于加攻击还是加生命都考虑一下，找出每种可能。

注意数据范围。

代码不给了，就是改个 ```__int128``` 的事。

---

## 作者：miao5 (赞：0)

### 题目大意

一个人要去杀一个怪物，他们轮流攻击对方，人的血量是 $h_c$，攻击是 $d_c$，怪物的血量是 $h_m$，攻击是 $d_m$，人先攻击，血量小于等于 $0$ 就判定死亡。

人还有 $k$ 次升级的机会，每次可以永久性加 $w$ 点攻击伤害或者是 $a$ 点血量，问人有没有可能击败怪物。

### 大体思路

因为没有问最优解，那么显然人最开始就把 $k$ 次升级的机会全部使用最优，
我们发现 $k$ 的值很小，所以我们可以枚举 $0\leq i\leq k$，表示用 $i$ 次升级的机会来升级攻击力，用 $k-i$ 次升级的机会来升级血量，只要有一次人能击败怪物就判定合法。

判定：因为人是先手，所以只需要满足 $\left\lceil\dfrac{h_c+(k-i)*a}{d_m}\right\rceil\leq \left\lceil\dfrac{h_m}{d_m+i*w}\right\rceil$ 即可。

同时可以看出 $\left\lceil\dfrac{x}{y}\right\rceil=\left\lfloor\dfrac{x+y-1}{y}\right\rfloor$，因为 C++ 运行除法操作的时候自动向下取整，所以在枚举 $i$ 时暴力带入上面的式子判断即可。

时间复杂度 $O(\sum k)$，可以通过本题。

```cpp
#include<iostream>
#define int long long
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		int x,y,z;
		cin>>x>>y>>z;
		bool flag=0;
		for(int i=0;i<=x;i++){
			if((a+(x-i)*z+d-1)/d>=(c+b+i*y-1)/(b+i*y)){
				cout<<"YES"<<endl;
				flag=1;
				break;
			}
		}
		if(!flag) cout<<"NO"<<endl;
	}
}
```

---

## 作者：__vector__ (赞：0)

### 题目意思：  
一个角色与怪物决斗。  
角色有以下两个属性：  
1.$hc$：生命值  
2.$dc$：攻击力  
怪物有以下两个属性：  
1.$hm$：生命值  
2.$dm$：攻击力  

决斗方式：  
1.角色向怪物发动攻击，怪物生命值掉了 $dc$。  
2.怪物向角色发动攻击，角色生命值掉了 $dm$。  
如此循环，直到其中一方的生命值小于等于 $0$，另一方获胜。  

决斗开始之前，角色可以购买装备，角色有 $k$ 枚硬币，一个硬币可以使生命值增加 $a$，也可以使攻击力增加 $w$。  
求如果以最优的方式购买装备，角色是否能打败怪物。  

有 $t$ 组数据，$1 \le t \le 5 \cdot 10^4$。   

### 题目分析：  
看到这道题，可以发现测试数据组数很多，可能需要 $O(1)$ 回答每组询问，但是，既然是要求最优方案，难以做到 $O(1)$ 回答询问。  
此时可以发现，题目里面说了，所有测试数据的 $k$ 之和不超过 $2 \cdot 10^5$。所以直接枚举分配给生命值和角色的硬币数量，对于枚举到的每组方案显然可以 $O(1)$ 判断角色是否可以胜利，如果可以胜利输出 ```YES```，如果所有方案都不可行输出 ```NO```。~~（我到比赛结束前十几分钟才发现这个最后没时间写了）~~ 这道题就做出来了。  
### 注意事项：  
如果就这样写，将会在第 $13$ 个测试点 WA 掉，原因是神仙 hacker 造的数据会爆掉 ``` long long```，所以在 C++20 下开 ```__int128```
 即可。  
### AC代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int t;
signed main()
{
    scanf("%lld",&t);
    int hc,dc,hm,dm,k,w,a;
    while(t--)
    {
        scanf("%lld%lld",&hc,&dc);//角色的生命和攻击力
        scanf("%lld%lld",&hm,&dm);//怪物的生命和攻击力
        scanf("%lld%lld%lld",&k,&w,&a);
        bool flag=0;
        for(int i=0;i<=k;i++)
        {
            int gjl=(k-i)*w+dc;//新的攻击力
            int sd=hm/gjl-1;//杀死怪物时受到伤害的次数
            if(hm%gjl>0)sd++;
            if((__int128)hc+(__int128)i*(__int128)a>(__int128)sd*(__int128)dm)
            {
                printf("YES\n");
                flag=1;
                break;
            }
        }
        if(!flag)printf("NO\n");
    }
    #ifndef ONLINE_JUDGE
    system("pause");
    #endif
    return 0;
}
```


---

## 作者：Arctic_1010 (赞：0)

### 题目翻译

Monocarp 有 $h_C$ 滴血和 $d_C$ 点攻击力，而敌人有 $h_M$ 滴血和 $d_M$ 点攻击力。

他们轮流按照以下步骤攻击对面：

+ Monocarp 攻击敌人，让敌人的血量减少 $d_C$。
+ 敌人攻击 Monocarp，让 Monocarp 的血量减少 $d_M$。
+ 如此循环，直到一个人的血量降为 $0$ 或以下，则对面胜利。

Monocarp 可以每次花 $1$ 个金币买护甲升级或者武器升级，每份护甲升级可以让他的初始血量增加 $a$，每份武器升级可以让他的初始攻击力增加 $w$。

Monocarp 有 $k$ 个金币，请判断他能否打败敌人。

多组数据，$\sum k\le 2\cdot 10^5$。其他范围见原题面。

### 思路

#### 流程

题面很长，变量很多，不妨先考虑判定问题。

血量和攻击力范围很大，不适合枚举。

容易发现，Monocarp 和敌人能抗住对面伤害的次数比较好计算，分别为 $\lceil \dfrac{h_C}{d_M}\rceil$  和 $\lceil \dfrac{d_C}{h_M}\rceil$。

Monocarp 能取胜当且仅当敌人能抗住对面伤害的次数小于 Monocarp 能抗住对面伤害的次数。

然后我们就可以通过这两个变量来 $O(1)$ 算出是否能取胜。

解决了判定问题，我们再来看整个题面：

首先贪心。因为 $a,w>0$，所以花金币买升级比不买升级一定不会更劣，所以我们~~豪横一把~~直接全用。

注意到 $k$ 的范围允许我们去枚举，所以直接枚举即可。

枚举 $i$ 表示用 $i$ 个金币升级武器，$k-i$ 个金币升级护甲，然后用上述判定方法是否满足能打败对面即可。

时间复杂度为 $O(\sum k)$ ，可以通过本题。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
signed main()
{
	cin>>t;
	while(t--)
	{
		ll hc,dc,hm,dm,k,w,a;//有些变量很大，记得开long long，我这里为了方便就全开了。
		cin>>hc>>dc>>hm>>dm>>k>>w>>a;
		bool flag=false;
		for(ll i=0;i<=k;i++)//注意从0开始！
		{
			dc+=i*w,hc+=(k-i)*a;//花金币买升级。
			if((hc+dm-1)/dm>=(hm+dc-1)/dc)//这里是两个上取整操作。
			{
				flag=true;
				puts("YES");
				break;
			}
			dc-=i*w,hc-=(k-i)*a;//判定完后记得把对应变量恢复默认值！（我就在这里卡了30min）
		}
		if(!flag) puts("NO");
	}
    return 0;
}

```

### Bonus

Q：`ceil` 那么好用，为什么不用 `ceil`？

A：因为浮点数误差。在这道题中用了 `ceil` 需要把 `int` 强制转成浮点数，而常用操作是使用 `1.0*`。但是由于本题数据范围比较大，存在浮点数误差使得精确度下降，而我们要求的是准确值，就可能会造成悲剧。

Q：我就想用 `ceil` ！

A：也不是不行，你可以强制类型转换成 `long double`，这样应该就能应付大多数的题目了。

~~ps：在本题中，`ceil` 不强制类型转换亲测可过，但是为了保险还是加上吧。~~ 

---

## 作者：YangHHao (赞：0)

## 题意简述

一名英雄对战一个怪物，英雄先攻击，从怪物 $h_m$ 的血量中扣除 $d_c$，之后怪物从英雄 $h_c$ 的血量中扣除 $d_m$，以此轮换，hp 掉光就输

每组数据中，英雄有 $k (k \le  2 \times 10^5\text{且}\sum k \le 2 \times 10^5)$ 块钱，每块钱可以帮他增加 $w$ 的攻击或 $a$ 的血量

求英雄有没有机会获胜

## 分析

显然在 **开始打架前** **花完金币** 最优，而因为英雄先手，所以只需英雄杀怪物所需次数小于等于怪物杀英雄的次数即可
	
即 $ \left \lceil {\dfrac{h_m}{d_c} }  \right \rceil \le \left \lceil {\dfrac{h_c}{d_m} }  \right \rceil $

考虑到 $k$ 的总和很小，暴力枚举增加的攻击和血量即可

## 代码实现

```cpp
#include<iostream>
using namespace std;
#define int long long
int divi(int a,int b){
	return (a+b-1)/b;
}
int t,hc,dc,hm,dm,k,w,a;
signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>hc>>dc;
		cin>>hm>>dm;
		cin>>k>>w>>a;
		bool f=0;
		for(int i=0;!f&&i<=k;i++){
			if(divi(hc+a*i,dm)>=divi(hm,dc+w*(k-i)))puts("YES"),f=1;
		}
		if(!f)puts("NO");
	}
}

```


---

## 作者：rsg26 (赞：0)

**题外话**

第一次 fst 祭

**正题**

假设某时刻人的体力为 $A$ ，攻击力为 $B$ ，而怪物的体力为 $a$ ，攻击力为 $b$ ，那么人杀掉怪需要 $\left \lceil  \frac aB\right \rceil$ 轮进攻，所以人需要抗住怪物的 $\left \lceil  \frac aB\right \rceil + 1$ 轮进攻，所以需要 $A > b\times (\left \lceil  \frac aB\right \rceil + 1)$ ，注意这里不能取等，否则人会在最后一轮攻击前体力降到 $0$ 。

这道体中，我们枚举每个金币花在哪里，由于多花总比不花强，而且每个金币有一样的效果，所以直接 `for` 一遍即可。

时间复杂度 $\mathcal{O}(\sum k)$ 。

**代码**

很简单

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define int long long

using namespace std;

int T, a, b, A, B, k, w1, w2, judge;

inline int upe(int x, int y) { // 除法上取整
    if (!(x % y)) return x / y;
    return x / y + 1;
}

signed main() {
    scanf("%lld", &T);
    while (T --) {
        scanf("%lld %lld %lld %lld %lld %lld %lld", &A, &B, &a, &b, &k, &w1, &w2), judge = 0;
        for (int i = 0; i <= k; ++i) // 枚举每一个金币花在哪里
            if (b * (upe(a, B + (k - i) * w1) - 1) < A + i * w2) judge |= 1; // 判断
        puts(judge == 1 ? "YES" : "NO");
    }
    return 0;
}
```

然后就 fst 了，为什么呢，因为我们分析，发现 $b\times (\left \lceil  \frac aB\right \rceil + 1)\le 10 ^ 9\times (10 ^ {15} + 1)$ 会爆 `long long` ，所以改成 `__int128` 就可以了。

正确代码（重复的就不给了）

```cpp
if ((__int128)b * (upe(a, B + (k - i) * w1) - 1) < (__int128)A + i * w2) judge |= 1;
```

**最后**

CF 的赛制和现在的 OI 赛制存在很大的差别，一个数据溢出便会造就 $4000$ 名左右的差别，所以建议大家写代码时细心再细心（深有感触.jpg

---

## 作者：Eason_AC (赞：0)

## Content
你要在游戏中打一个怪物。已知你现在的血量为 $h_C$，攻击一次对怪物造成的伤害为 $d_C$；怪物现在的血量为 $h_M$，攻击一次对你造成的伤害为 $d_M$。你手头有 $k$ 个硬币，每次你可以花费一个硬币升级你的血量或者伤害。具体地，每花费一个硬币，要么你的伤害提升 $w$，要么你的血量提升 $a$。判断你是否可以通过若干次升级打败怪物。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 5\times 10^4$，$1\leqslant h_C,h_M\leqslant 10^{15}$，$1\leqslant d_C,d_M\leqslant 10^9$，$0\leqslant k,\sum k\leqslant 2\times 10^5$，$0\leqslant w\leqslant 10^4$，$0\leqslant a\leqslant 10^{10}$。**
## Solution
首先我们不难发现一点：要想在升级之后打败怪物，需要保证**你需要攻击的次数小于等于怪物需要攻击的次数**，即，设升级后你的血量为 $h_C'$，伤害为 $d_C'$，则你需要保证 $\lceil\dfrac{h_M}{d_C'}\rceil\leqslant\lceil\dfrac{h_C'}{d_M}\rceil$。

由于我们只需要判断能否打败怪物，因此，把 $k$ 个硬币全部花完一定不劣。而每次升级的东西是从两个中选一个，因此，我们直接枚举花费在血量/伤害上的硬币个数 $x$，则花费在另一方面上的硬币个数是 $k-x$，然后按照上面的条件判断，不断枚举直到某种情况能够打败怪物。如果所有情况都不能打败怪物，输出 `NO` 即可。
## Code
```cpp
namespace Solution {
	ll hc, dc, hm, dm, k, w, a;
	
	iv Main() {
		MT {
			read(hc, dc, hm, dm, k, w, a);
			int fl = 0;
			F(ll, i, 0, k) {
				ll hc0 = hc + i * a, dc0 = dc + (k - i) * w;
				if((ll)ceil(hm * 1. / dc0) <= (ll)ceil(hc0 * 1. / dm)) {fl = 1; break;}
			}
			fl ? YES : NO;
		}
		return;
	}
}
```

---

