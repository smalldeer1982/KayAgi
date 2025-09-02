# Monsters (easy version)

## 题目描述

This is the easy version of the problem. In this version, you only need to find the answer once. In this version, hacks are not allowed.

In a computer game, you are fighting against $ n $ monsters. Monster number $ i $ has $ a_i $ health points, all $ a_i $ are integers. A monster is alive while it has at least $ 1 $ health point.

You can cast spells of two types:

1. Deal $ 1 $ damage to any single alive monster of your choice.
2. Deal $ 1 $ damage to all alive monsters. If at least one monster dies (ends up with $ 0 $ health points) as a result of this action, then repeat it (and keep repeating while at least one monster dies every time).

Dealing $ 1 $ damage to a monster reduces its health by $ 1 $ .

Spells of type 1 can be cast any number of times, while a spell of type 2 can be cast at most once during the game.

What is the smallest number of times you need to cast spells of type 1 to kill all monsters?

## 说明/提示

In the first test case, the initial health points of the monsters are $ [3, 1, 2] $ . It is enough to cast a spell of type 2:

- Monsters' health points change to $ [2, 0, 1] $ . Since monster number $ 2 $ dies, the spell is repeated.
- Monsters' health points change to $ [1, 0, 0] $ . Since monster number $ 3 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ .

Since it is possible to use no spells of type 1 at all, the answer is $ 0 $ .

In the second test case, the initial health points of the monsters are $ [4, 1, 5, 4, 1, 1] $ . Here is one of the optimal action sequences:

- Using a spell of type 1, deal $ 1 $ damage to monster number $ 1 $ . Monsters' health points change to $ [3, 1, 5, 4, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ . Monsters' health points change to $ [3, 1, 5, 3, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ again. Monsters' health points change to $ [3, 1, 5, 2, 1, 1] $ .
- Use a spell of type 2:
  - Monsters' health points change to $ [2, 0, 4, 1, 0, 0] $ . Since monsters number $ 2 $ , $ 5 $ , and $ 6 $ die, the spell is repeated.
  - Monsters' health points change to $ [1, 0, 3, 0, 0, 0] $ . Since monster number $ 4 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 2, 0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 1, 0, 0, 0] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 3 $ . Monsters' health points change to $ [0, 0, 0, 0, 0, 0] $ .

Spells of type 1 are cast $ 4 $ times in total. It can be shown that this is the smallest possible number.

## 样例 #1

### 输入

```
2
3
3 1 2
6
4 1 5 4 1 1```

### 输出

```
0
4```

# 题解

## 作者：Blikewsr (赞：2)

- [题目传送门](https://www.luogu.com.cn/problem/CF1784A)

- 题目大意             
  有一个序列 $a_1, a_2 \ldots a_{n-1}, a_{n}$ 且所有元素皆为正整数，共有两种操作，使得进行若干次操作后的序列的所有元素皆不大于零，求第一种操作的最小操作次数。
  
  操作如下：   
  1. 选择序列中的任意一个正整数元素，将其减一；
  2. 将序列中所有的正整数元素都将其减一，如有元素因此操作小于等于零，则再次进行一次此操作；
  
- 注意              
  第一种操作可以执行无数次，第二种操作只可以执行一次。
  
- 思路                              
  很明显，如果序列中的所有元素皆满足 $a_i(1
  \le i < n) + 1 = a_{i + 1}$ 的话，那么我们只需要进行一次操作二即可将序列清零。
  
  所以，我们便可以先使用操作一将序列有序化（如上），然后在进行一次操作二即可。
  
  但是，为了最小化第一种操作，为了避免不需要的操作，我们先将序列排序一遍。
  
- 代码实现
```
#include <bits/stdc++.h>
#define int long long
namespace S_T_D {
	inline int Read() {
		int f = 0, n = 1;
		char ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') n *= -1;
			ch = getchar();	
		}
		while (isdigit(ch)) {
			f = (f << 1) + (f << 3) + ch - '0';
			ch = getchar();	
		}
		return f * n;
	}
	inline void write(int x) {
		if (x < 0) x = -x, putchar('-');
		if (x > 9) write(x / 10);
		putchar(x % 10 ^ 48);
		return;		
	}
	inline int min(int x, int y) {
	    return x < y ? x : y;
    }
    inline int max(int x, int y) {
    	return x > y ? x : y;
    }
	#define read Read()
}
using namespace std;
using namespace S_T_D;
const int N = 2e5 + 1;
int T, n, tot, num, a[N];
signed main() {
	T = read;              // 多组数据 
	while (T --) {
		n = read;
		tot = 0, num = 0;  
		/*
			tot : 操作一次数 
			num : 序列有序化基准值
		*/ 
		for (int i = 1; i <= n; ++ i) a[i] = read;
		sort(a + 1, a + n + 1);       // 先从小到大排序一遍 
		for (int i = 1; i <= n; ++ i) {
			if (a[i] == num) continue;   // 如果等于基准值，无需操作，跳过 
			else ++ num, tot += a[i] - num;	   // 否则将基准值 + 1，再进行操作一 
		}
		write(tot), puts("");    // 输出答案 
	}
	return 0;
}	
```

- 此题解仅供参考，谢谢！

---

## 作者：听取MLE声一片 (赞：2)

简单题。

不难看出最终答案要化为类似 $1,2,3,4,5,6$ 这样的形式，当然可以出现重复。

为什么呢？因为这样从小到大相邻数差不大于 1 的形式，可以直接第二个操作一带一路推完的。如果中间有相邻数差大于 1，就要把前面消去后再一个一个的减，还不如先减到相邻差为 1 然后一次删除。

首先对序列进行排序。

记录 $cnt=1$。从小到大枚举序列，当前值为 $a_i$。如果 $a_i<cnt$，那么这个值可以被之前的消去，可以不用管。反之则此值是必须处理的，答案增加 $cnt-a_i$，$cnt$ 加一。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
int n,a[N];
signed main()
{
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		sort(a+1,a+n+1);
		int ans=0,cnt=1;
		for(int i=1;i<=n;i++){
			if(a[i]<cnt)
				continue;
			ans+=a[i]-cnt;
			cnt++;
		}
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：Alex_Wei (赞：1)

考虑操作 2 结束后仍有怪物未被杀死，则将剩余的操作 1 提到操作 2 之前，答案不会变劣。因此，执行操作 2 后所有怪物一定被杀死。

进一步地，执行操作 1 前后怪物血量的相对大小不变（交换法可证）。

考虑到满足条件的血量集合形如 $1, \cdots, 1, 2, \cdots, 2, \cdots$，所以我们将 $a$ 从小到大排序，记 $c$ 表示上一只怪物的血量。若 $a_i = c$ 则不变，否则 $c$ 加上 $1$，答案再加上 $a_i - c$。

时间复杂度 $\mathcal{O}(n\log n)$ 或 $\mathcal{O}(n)$（桶排）。[代码](https://codeforces.com/contest/1785/submission/192284245)。

---

## 作者：hellolin (赞：1)


[题面(洛谷)](https://www.luogu.com.cn/problem/CF1784A)

[题面(Codeforces)](https://codeforces.com/problemset/problem/1784/A)

## 思路

我们肯定希望技能 2 用在最划算的地方，也就是使用一次技能 2 「杀死」更多的怪物，直接结束游戏 ~~（毕竟这么牛波一的技能每局只能用一次）。~~

如何保证使用技能 2 能秒杀全场呢？

很简单，只要保证血量序列里有若干血量为 $1$ 的怪物，有若干血量为 $2$ 的怪物，还有 $3,\ 4,\ 5,\ ...$，这样每扣一次血必定有至少一只怪物被「杀死」，技能继续扣血，还有至少一只怪物被「杀死」，技能继续，循环到结束游戏。经过若干次技能 1 之后，怪物血量序列排序后如下：

$$\overbrace{1,\ ...}^{\texttt{若干个}1},\ \overbrace{2,\ ...}^{\texttt{若干个}2},\ \overbrace{3,\ ...}^{\texttt{若干个}3},\ \overbrace{4,\ ...}^{\texttt{若干个}4},\ ...$$

简单地来说，我们只需要使用技能 1 直到怪物血量满足：

- 排序后相邻血量相差不超过 $1$。

就行了。

## 代码

代码也很好写啦，排序一遍检查相邻血量之差有没有大于 $1$ 的，给它降下来。

``` cpp
// Coder          : Hellolin
// Time           : 2023-02-06 10:25:33
// Problem        : Monsters (easy version)
// Contest        : Luogu
// URL            : https://www.luogu.com.cn/problem/CF1784A
// Time Limit     : 4000 ms
// Memory Limit   : 500 MiB

#include <iostream>
#include <algorithm>

#define ll long long
const int MAX = 200205;

int t;
ll n, a[MAX], ans; // 记得开 long long
int main()
{
    // 加速输入输出
    std::ios::sync_with_stdio(false);

    // 多组测试数据
    std::cin>>t;
    while(t--)
    {
        std::cin>>n;
        for (int i=1; i<=n; i++) std::cin>>a[i];

        // 排序
        std::sort(a+1, a+1+n);

        // 计算答案，输出，记得 ans=0
        ans=0;
        for (int i=1; i<=n; i++) // 注意这里 i 要从 1 开始，万一怪物序列里没有 1 需要弄出来一个 1
        {
            if (a[i]-a[i-1]>1) // 相邻的两个血量相差大于 1
            {
                ans += a[i]-a[i-1]-1; // 需要使用技能 1
                a[i] = a[i-1]+1;
            }
        }
        std::cout<<ans<<std::endl;
    }

    return 0;
}
```


---

## 作者：Supernova_empire (赞：0)

乍一看这一题便懵了，详细看看后发现：
本题思维很难，但代码很简单。
### 基本思路：
看一组样例：
$$1\medspace2\medspace3\medspace4\medspace5  $$
很明显，使用技能 $2$ ，连锁反应。
$1$ 没了，再发动， $2$ 就没了，再发动。。。   
所以我们**需要使用技能$1$让怪物血量变为这样的数列** 。　  
先排个序，然后，先用技能 $1$ 把怪物的血量扣到形成我们需要的数列。
```cpp
for(int i=1;i<=n;i++){
    if(monster[i]>i) used+=(monster[i]-i);
}
```


------------

但是，有个东西叫做**极端样例**！  
全输入 “$1$” ，再输入 $2$ ？  
所以，我们需要标记一下，第 $i$ 个怪兽需要扣到多少血量，再进行技能 $2$ 的使用。  
代码主题：
```cpp
int act=0;
for(int i=1;i<=n;i++){
	if(monster[i]>monster[i-1]) act++;
	if(monster[i]>act){
		use+=(monster[i]-act);
		monster[i]-=(monster[i]-act);//因为第3行有判断，所以需要修改数组里的数据
	}
}
```

---

## 作者：yinhy09 (赞：0)

## 题目分析：

我们有一个巨大的大招，肯定要在最好的时刻来用。最好的用法莫过于一下秒杀全局。这样一次干掉的血量最大，肯定最值。那么我们就可以一个一个把所有怪物打成血量连续递增，然后一招剿灭。

## AC Code : 

```cpp
/*******************************
| Author:  yinhy09
| Problem: C. Monsters (easy version)
| Contest: Codeforces Round #850 (Div. 2, based on VK Cup 2022 - Final Round)
| URL:     https://codeforces.com/contest/1786/problem/C
| When:    2023-02-05 20:06:06
| 
| Memory:  512 MB
| Time:    4000 ms
*******************************/
 
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define multicase() ll T;scanf("%lld",&T);while(T--)
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll n;
const int maxn=2e5+10;
ll a[maxn];
ll b[maxn];
ll qwq=0;
int main()
{
	multicase()
	{
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)b[i]=min(b[i-1]+1,a[i]);
		qwq=0;
		for(int i=1;i<=n;i++)qwq+=a[i],qwq-=b[i];
		printf("%lld\n",qwq);
	}
	return 0;
}
```

谢谢观看喵~

---

## 作者：_zzzzzzy_ (赞：0)

## 题意
给出整数 $N$ 和 $N$ 个整数，表示有 $N$ 只怪物和每只怪物的血量。

给你 $2$ 种攻击技能：

- 技能 1 ：指定某一只怪物，然后对它造成 $1$ 的伤害。
- 技能 2 ：对群体造成 $1$ 的伤害，如果在这次伤害中让每一只怪物的血量变成 $0$ ，就可以再次使用，直到没有怪物因为攻击让血量为 $0$ 。

问需要用多少次技能 1 ， $1$ 次技能 2 才能打败 $N$ 只怪兽。
## 思路

要先把这个怪兽的血量有序化，我们很容易可以想到一种贪心思路，先用技能 1 把怪物的血量打成阶梯状，然后技能 2 的连击次数可以达到最高，也就是每次都要杀死一只怪兽，最后答案呈现出 $1\dots2\dots\ \dots x\dots$ 的格式， $x$ 的大小就是技能 2 的连击次数。

## 赛时代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200050;
int a[maxn];
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+n);
		int ans=0;
		for(int i=0;i<n;i++){
			if(a[i]==a[i+1]||a[i]==a[i+1]-1);//此处写的既不美观
			else{
				ans+=a[i+1]-(a[i]+1);
				a[i+1]=a[i]+1;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

## 赛后代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200050;
int a[maxn];
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,ans=0;
		cin>>n;
		int cnt=1;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);
		ans+=a[1]-cnt;//此处处理的比赛时更加巧妙一点
		for(int i=2;i<=n;i++){
			if(a[i]!=cnt){
				cnt++;
				ans+=a[i]-cnt;
			}
		}
		cout<<ans<<'\n';
	}
}
```

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1784A)

[codeforces div1](https://codeforc.es/contest/1784/problem/A)

[codeforces div2](https://codeforc.es/contest/1786/problem/C)

### 题目大意

你正在玩一个游戏。

现在有 $n$ 个怪物，第 $i$ 个怪物的血量为 $a_i$。

你要杀死它们。你有两种方法来攻击。
1. 选取任何一个怪物并将其血量减少 $1$。这种攻击方法可以无限次使用。
2. 所有未被“杀死”的怪物的血量都减少 $1$，如果任何怪物被这种攻击方法“杀死”，你可以立即重复一次。**注意，这种攻击每局只能使用一次。**

要“杀死”一个怪物，你需要让它的血量小于或等于 $0$。被“杀死”的怪物立即退出游戏。

问“杀死”所有怪物所需第一种攻击方法的最少次数。

多组数据，$1\le \sum n \le 2 \times 10^5$。

### 思路

既然需要最小化使用方法一的次数，就需要让只能使用一次的方法二所造成的伤害最大。

> 声明：以下的序列 $a$ 均是经过升序排序的。

> 证明：
>
> 先说为什么要求尽可能延续方法二以获得最大伤害。
>
> 将其转化成另一个问题：一个长度为 $n$ 的序列 $b$，满足：
>
> + $b_i \le a_i$；（攻击不超过血量）
>
> + $0 \le b_i - b_{i-1} \le 1(2 \le i \le n)$。（**要使方法二连续攻击。其实还可以 $b_i=0$，但是在这之后的 $b$ 都等于 $0$，肯定不优。**）
>
> 求 $\sum_{i=1}^{n}{b_i}$ 的最大值。这个值就是最大的伤害。答案可以通过 $\sum_{i=1}^{n}{a_i}-\sum_{i=1}^{n}{b_i}$ 求出。
>

> ……这里需要感性理解一下，直接证明可能不清楚……

那么求解时有以下两种情况：

1. $a_i-a_{i-1}>1$。则将 $a_i$ 更新成 $a_{i-1}+1$，让方法二延续下去；

2. $a_{i-1}-a_i \le 1$。此时 $a_i$ 可以满足延续方法二，跳过。

所以先对原血量序列排序，再在序列最前面加一个 $0$，如果相邻元素之差大于 $1$，则更新答案和序列元素。

时间复杂度 $O(n\log{n})$。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,a[200010];
void solve(){
	cin>>n;ll ans=0;
	for(int i=1;i<=n;++i)cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;++i)if(a[i]-a[i-1]>1)ans+=a[i]-a[i-1]-1,a[i]=a[i-1]+1;
	cout<<ans<<'\n';
	return;
}
int main(){
	int t=1;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

设第 $i$ 个怪物的血量为 $m_i$。

对于每组数据，我们先把读入进来的 $m$ 从小到大排序。

我们可以先把 $m_1$ 打到 $1$，这样可以保证二技能使用**第一次有怪物死亡**，能接着使用第二次。

然后从第 $m_2$ 枚举，如果能把 $m_i$ 打到 $m_{i-1}+1$，那么就把 $m_i$ 打到 $m_{i-1}+1$（因为要保证**每次二技能后都有怪物死亡**，且一技能使用次数最少），否则不对 $m_i$ 进行操作。

最后 $m$ 一定是单调不减且相邻两项的差最大为 $1$ 的，即对于 $i>1$，一定有 $0\leq m_i-m_{i-1}\leq 1$，其中 $m_1=1$。

在这种状态下，一个二技能即可解决所有怪物。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,a[200001];
long long ans;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        int c=1,d=0;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);
        ans+=a[1]-c;
        for(int i=2;i<=n;i++){
            if(a[i]==c)continue;
            else c++,ans+=a[i]-c;
        }
        cout<<ans<<endl;
        ans=0;
    }
}
```


---

