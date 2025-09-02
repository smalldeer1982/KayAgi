# Circle Game

## 题目描述

Utkarsh is forced to play yet another one of Ashish's games. The game progresses turn by turn and as usual, Ashish moves first.

Consider the 2D plane. There is a token which is initially at  $ (0,0) $ . In one move a player must increase either the $ x $ coordinate or the $ y $ coordinate of the token by exactly $ k $ . In doing so, the player must ensure that the token stays within a (Euclidean) distance $ d $ from $ (0,0) $ .

In other words, if after a move the coordinates of the token are $ (p,q) $ , then $ p^2 + q^2 \leq d^2 $ must hold.

The game ends when a player is unable to make a move. It can be shown that the game will end in a finite number of moves. If both players play optimally, determine who will win.

## 说明/提示

In the first test case, one possible sequence of moves can be

 $ (0, 0) \xrightarrow{\text{Ashish }} (0, 1) \xrightarrow{\text{Utkarsh }} (0, 2) $ .

Ashish has no moves left, so Utkarsh wins.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1451D/00adebe318fd60c39c1fde9564efcda9489c81f2.png)

## 样例 #1

### 输入

```
5
2 1
5 2
10 3
25 4
15441 33```

### 输出

```
Utkarsh
Ashish
Utkarsh
Utkarsh
Ashish```

# 题解

## 作者：Scintilla (赞：10)

相信大家都听过一个游戏：两个人轮流在一张纸牌上放相同的硬币，放不下者输，求谁有必胜策略。

答案是先手。他可以先在牌的正中央放一个硬币，再在后面的每轮中把硬币放在对手所放位置关于纸牌中心的对称位置。

我们可以将这种思想放在这道题上，看看如果后手一直让先手出发的位置位于 $y = x$ 上会发生什么。

不难发现这样最多持续 $s$ 轮，其中 $s$ 是使得 $2s^2k^2 \leq d^2$ 的最大正整数。第 $s + 1$ 轮时，若先手能走出一步，即 $s^2k^2 + (sk + k)^2 \leq d ^ 2$，那么先手必胜，因为

$$(sk + k)^2 + (sk + k)^2 > d ^ 2$$

$$(sk)^2 + (sk + 2k)^2 = 2s^2k^2 + 4sk + 4 =  2(sk + k)^2 + 2> d ^ 2$$

无论后手往哪边走，他都会出界。反之后手必胜。

那么答案已经呼之欲出了：如果 $s^2k^2 + (sk + k)^2 \leq d ^ 2$，那么先手可以让后手的出发点始终在 $y = x + k$ 或 $y = x - k$ 上，那么先手必胜。反之，后手可以让先手的出发点始终在 $y = x$ 上，后手必胜。

```cpp
int tc; ll d, k;
int main() {
    tc = read();
    while (tc--) {
        d = read(), k = read();
        ll tp = sqrt(d * d / 2);
        tp = tp / k * k;
        puts(tp * tp + (tp + k) * (tp + k) <= d * d ? "Ashish" : "Utkarsh");
    } 
    return 0;
}
```

---

## 作者：NashChen (赞：5)

## 题意简述

从 $(0,0)$ 出发，每次只能使横坐标或纵坐标增加 $k$ ，且不能离原点的距离超过 $d$ 。两人交替操作，不能操作者判负。

## 题解

首先，所有的合法点可以简化成半径为 $\frac dk$ 的圆内的**整点**。令 $r=\frac dk$ 。

考虑 $y=x$ 上**最大的合法点**，设为 $(n,n),\sqrt 2n<r$ 。

若 $(n+1,n),(n,n+1)$ 合法，则该两点为必负点。否则 $(n,n)$ 为必负点。

因为若在 $(n+1,n),(n,n+1)$ 仍能移动，则要么 $(n+1,n+1)$ 合法，要么 $(n+2,n),(n,n+2)$ 合法。因为对于曼哈顿距离来说，圆仍然是**凸的**，所以若 $(n+2,n)$ 和 $(n,n+2)$ 合法，则 $(n+1,n+1)$ 也合法。与 $(n,n)$ 的最大性矛盾。

而后手者总可以通过与先手者相反的操作将位置控制在 $y=x$ 上，先手者也可以用相同策略将后手者控制在 $y=x\pm 1$ 上。

所以若 $(n,n+1)$ 在圆内，先手胜，若$(n,n+1)$ 不在圆内，后手胜。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

long long T,N,M;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&N,&M);
		long long k= (long double)N/M*sqrt(0.5);
		if(N*N< M*M*(2*k*k+2*k+1)) puts("Utkarsh");
		else puts("Ashish");
	}
	return 0;
}
```

---

## 作者：VinstaG173 (赞：4)

是一个在数学课上被同学拿来讲的题（

首先我们发现这是一个典型的博弈论问题。于是我们可以先用那两条定理推一下胜负状态:

1. 必败状态的所有后继状态都是必胜状态

2. 必胜状态的至少一个后继状态是必败状态

以 $d=7,k=2$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/ra44b3k0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在这个图上我们用红色点标记必胜点，蓝色点标记必败点得：

![](https://cdn.luogu.com.cn/upload/image_hosting/p235bmt2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

此时我们发现一个规律：对角线上的胜负状态相同，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kmr7zuj2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

由此我们得到一个解法：直接判断直线 $y=x$ 上最远的可达的点是否必败，具体只要看这个点的右边或上面的点是否可达就行了。

那么为什么这样是对的呢？

首先必败状态会造成其左和其下都是必胜状态，于是显然其左下为必败状态。

然后必胜状态需满足其上或其右为必败状态，于是其左或其下为必败状态，显然其左下为必胜状态。

所以这是一道代码极短思维难度又不高的~~可以当 Div2A 的 Div2D~~ 题（

Code:
```cpp
#include<cstdio>
#define ll long long
int t,d,k,x;
int main()
{
    scanf(" %d",&t);
    while(t--)
    {
        scanf(" %d %d",&d,&k);
        x=0.70710678*d/k;//(x,x)为 y=x 上最远可达的点
        if((ll)k*k*(x*(x+1ll)<<1|1)<=(ll)d*d)puts("Ashish");//即 (kx)^2+(k(x+1))^2<=d^2，故 (kx,k(x+1)) 可达，先手必胜
        else puts("Utkarsh");
    }
    return 0;
}
```

---

## 作者：Konnyaku_LXZ (赞：2)

首先我们发现，不管是先手还是后手，都可以**控制对方的行动**。先手可以控制对方在直线 $y=x±k$ 上运动，后手则可以控制对方在直线 $y=x$ 上运动。而这两条直线所对应的**获胜方也会不同**。

对于直线 $y=x$，总共可以走 $\lfloor \sqrt{ \frac{d \times d}{2}}$ $/k \rfloor$ 轮。如果下一轮**先手还可以走**的话，那么**后手一定没得走**（因为最后一轮已经走完了，所以后手不可能再走到直线 $y=x$ 上，而往另一个方向走，距离显然会更大），这种情况下先手胜；反之如果先手没发走了，则后手胜。

即若 $x \times x + (x+k) \times (x+k) \le d \times d$（其中 $x=\lfloor \sqrt{ \frac{d \times d}{2}}$ $/k \rfloor \times k$，即最后一轮结束后的横纵坐标值)，则先手胜，反之后手胜。

最后还有一个需要特别注意的地方：**sqrt 的返回值不是整数，所以要先转换成整数之后再除以 $k$，否则等于没除。**

具体见代码。

Code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<vector>
using namespace std;

const int MAXN=205;
typedef long long LL;

LL d,k;
bool flag;

void Init(){
	cin>>d>>k;
}

void Solve(){
	LL x=LL(sqrt(d*d/2))/k*k;
	if(x*x+(x+k)*(x+k)<=d*d) flag=true;
	else flag=false;
}

void Print(){
	puts(flag?"Ashish":"Utkarsh");
}

int main()
{
	int T;
	cin>>T;
	while(T--){
		Init();
		Solve();
		Print();
	}
	return 0;
}
```

---

## 作者：TEoS (赞：2)

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/14029814.html)


------------


**题意分析**

给出一个半径为 $d$ 的圆，以 $(0,0)$ 为起点，每次可以向上或向右移动 $k$ 个单位，先移出圆的为败，求先手还是后手能赢。

**思路分析**

经过分析可以发现，无论对方怎么走，先手可以保证在直线 $y=x+k$ 或 $y=x-k$ 上行走，后手可以保证在直线 $y=x$ 上行走。因此，当存在一个必胜点（即下一步必定出圆） $(x,y)$ 满足 $|y-x|=k$ 且 $k|x$ ，则先手可以走到这里保证必胜；同理，当存在一个必胜点 $(x,y)$ 满足 $x=y$ 且 $k|x$ ，则后手可以走到这里保证必胜。

**具体实现**

显然我们应该首先在直线 $y=x$ 上走得尽量远，然后判断最远的点是否为必胜点，如果是则后手胜，否则先手胜。具体判断即看下一步是否会超出圆。显然最远即半径长 $d$ ，而每走 $2$ 步走的距离即为 $\sqrt{2}k$ ，因此能走的最大步数为 $2\left \lfloor \frac{d}{\sqrt{2}k} \right \rfloor$ ，此时的坐标为 $(k\left \lfloor \frac{d}{\sqrt{2}k} \right \rfloor,k\left \lfloor \frac{d}{\sqrt{2}k} \right \rfloor)$ 。下一步往上走和往右走都一样，即走到 $(k\left \lfloor \frac{d}{\sqrt{2}k} \right \rfloor,k(\left \lfloor \frac{d}{\sqrt{2}k} \right \rfloor+1))$ ，用两点间的距离公式判断是否出圆即可，即最终只需要判断 $(k\left \lfloor \frac{d}{\sqrt{2}k} \right \rfloor)^2+(k(\left \lfloor \frac{d}{\sqrt{2}k} \right \rfloor+1))^2>d^2$ ，若成立，则会超出，后手胜；否则先手胜。向下取整可以直接强制类型转换为整型。

```c++
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
#define ld long double
using namespace std;
int T;
ll d,k;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&d,&k);
		puts(pow(k*(ll)((ld)d/sqrt((ld)2)/k),2)+pow(k*(ll)((ld)d/sqrt((ld)2)/k+1),2)>d*d?"Utkarsh":"Ashish");
	}
	return 0;
}
```



---

## 作者：H6_6Q (赞：2)

## [1451D - Circle Game](https://codeforces.com/contest/1451/problem/D)

### 题目大意

两个人轮流操作，从原点开始，每次操作使 $x$ 坐标或 $y$ 坐标加 $k$，如果操作后与源点的欧几里得距离大于 $d$ ，那么操作的这个人就输了。

两人都以最优策略，问谁会赢

### 解题思路
博弈论小白表示这么简单的博弈论也不会/kk

对于一个 $(x,y)$ ，如果它是必败点，那么 $(x-k,y),(x,y-k)$ 就是必胜点。

因此 $(x-k,y-k)$ 同是必败点。

所以如果 $(0,0)$ 是必败点，那么一定有 $(p \times x,p \times y)$ 是必败点。

随便枚举判断下就行了。

### Code
```cpp
int t,d,k,s1,s2,fl;

signed main()
{
	t=read();
	while(t--)
	{
		d=read();k=read();
		s1=0,s2=0,fl=0;
		for(int i=0;i*i*2<=d*d;i+=k)
		{
			if((i+k)*(i+k)+i*i>d*d)
				fl=1;
		}
		if(fl) printf("Utkarsh\n");
		else printf("Ashish\n");
	}                     
	return 0;
}
```

---

## 作者：pomelo_nene (赞：1)

这种题第一步就是手模拟。不如尝试一下？

我们发现，设 $x=\dfrac{d}{k}$，当：

- $x<\sqrt{1^2+0^2}$ 时，先手必败；   
- $\sqrt{1^2+0^2} \leq x < \sqrt{1^2+1^2}$ 时，先手必胜；   
- $\sqrt{1^2+1^2} \leq x < \sqrt{1^2+2^2}$ 时，先手必败；
- ……


显然这是有规律的。映射到游戏来，会发生什么？

注意到根号内的第二个数（没有平方）是最优情况下先手可以走的步数，第一个数同理是后手可以走的步数。

于是可以猜测，先手一直往上，后手一直往右一定是整个游戏的最优状态。如果先手必胜，当后手往上的时候，先手可以往右调整这个状态，后手仍然是必败态；当先手是必败态的时候，后手可以同样用这个方法去调整状态。

综上完事儿。少用 `sqrt()`。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL st[200010];
int main(){
	int T;
	scanf("%d",&T);
	for(LL i=1;i<=200009;++i)
	{
		if(i&1)
		{
			LL sr=(i+1)>>1;
			st[i]=sr*sr+(sr-1)*(sr-1);
		}
		else	st[i]=i*i/2;
	}
	while(T-->0)
	{
		LL d,k;
		scanf("%lld %lld",&d,&k);
		for(LL i=1;i<=200009;++i)
		{
			if(st[i]*k*k>d*d)
			{
				puts(i&1?"Utkarsh":"Ashish");
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：寒冰大大 (赞：1)

从 $(0,0)$ 开始，第 $2i$ 轮绝对可以走到 $(di,di)$这个位置（除非已经超出了这个圆）

如果 $(di,di+d)$ （ 等价于$(di+d,d)$ ） 还可以走，那么先手还可以再走一步后手输定了，否则就是先手输定了（因为一定可以走这样的路径）

代码只有这么点
```cpp
inline void solve()
{	
	mstd::qread(r);
	mstd::qread(d);
	int lk=(int)sqrt(1ll*r*r/2.0);
	if((int)ceil(sqrt(1ll*(lk/d*d)*(lk/d*d)+1ll*(lk/d*d+d)*(lk/d*d+d)))<=r) printf("Ashish\n");
	else printf("Utkarsh\n");
} 
 
```


---

## 作者：k2saki (赞：0)

由于都采用最优策略，所以行走的路线一定是一上，一右，一上，一右的。因为他们都可以把各自的行动控制在一定的范围之内。

然后暴力模拟即可，题解区很多人都是 O1 的。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m;

signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        int x = 0, y = 0, ans = 0;
        while (1)
        {
            if (ans % 2 == 0)
                x += m;
            else
                y += m;
            ++ans;
            if (x * x + y * y > n * n)
            {

                ans--;
                break;
            }
        }
        if (ans % 2 == 0)
            puts("Utkarsh");
        else
            puts("Ashish");
    }
}
```


---

