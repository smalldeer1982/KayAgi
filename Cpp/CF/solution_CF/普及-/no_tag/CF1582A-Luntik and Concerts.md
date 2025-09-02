# Luntik and Concerts

## 题目描述

有 $a$ 个 $1$ 分钟的音乐，$b$ 个 $2$ 分钟的音乐，$c$ 个 $3$ 分钟的音乐，将这些音乐分成 $2$ 组，使两组音乐的总时长之差的绝对值尽可能小。

## 说明/提示

$1\le t\le1000,1\le a,b,c\le10^9$。

### 样例解释：
1. 第一组 $1$ 个 $1$ 分钟音乐、$2$ 个 $2$ 分钟音乐，第二组 $1$ 个 $3$ 分钟音乐时两组音乐总时长之差的绝对值最小，为 $0$。
2. 第一组 $2$ 个 $1$ 分钟音乐、$1$ 个 $2$ 分钟音乐$1$ 个 $3$ 分钟音乐，第二组 $2$ 个 $3$ 分钟音乐时两组音乐总时长之差的绝对值最小，为 $1$。
3. 第一组 $5$ 个 $1$ 分钟音乐、$5$ 个 $2$ 分钟音乐，第二组 $5$ 个 $3$ 分钟音乐时两组音乐总时长之差的绝对值最小，为 $0$。
4. 第一组 $1$ 个 $1$ 分钟音乐、$1$ 个 $3$ 分钟音乐，第二组 $1$ 个 $2$ 分钟音乐、$1$ 个 $3$ 分钟音乐时两组音乐总时长之差的绝对值最小，为 $1$。

## 样例 #1

### 输入

```
4
1 1 1
2 1 3
5 5 5
1 1 2```

### 输出

```
0
1
0
1```

# 题解

## 作者：tzl_Dedicatus545 (赞：5)

这道题容易发现，总时长之差的绝对值的最小值只与$a,b,c$的奇偶性相关，枚举8种情况即可：

$$ans=\begin{cases}
0&a = 0 \bmod2,b=0 \bmod 2,c=0\bmod 2\\
1&a = 1 \bmod2,b=0 \bmod 2,c=0\bmod 2 \\
1&a = 1 \bmod2,b=1 \bmod 2,c=0\bmod 2 \\
0&a = 1 \bmod2,b=1 \bmod 2,c=1\bmod 2\\
1&a = 0 \bmod2,b=1 \bmod 2,c=1\bmod 2 \\
0&a = 1 \bmod2,b=0 \bmod 2,c=1\bmod 2 \\
1&a = 0 \bmod2,b=0 \bmod 2,c=1\bmod 2 \\
0&a = 0 \bmod2,b=1 \bmod 2,c=0\bmod 2 \\\end{cases}$$

建议评级：红

**Code:**
```
//By: Luogu@Kamado Tanjirou(308854)
#include <bits/stdc++.h>

using namespace std;

const int INF=0x3f3f3f3f;

signed main()
{
    int t;

    cin>>t;

    while(t--)
    {
        int a,b,c;

        cin>>a>>b>>c;

        if(a%2==0 && b%2==0 && c%2==0)
            cout<<"0\n";
        if(a%2==1 && b%2==0 && c%2==0)
            cout<<"1\n";
        if(a%2==1 && b%2==1 && c%2==0)
            cout<<"1\n";

        if(a%2==1 && b%2==1 && c%2==1)
            cout<<"0\n";
        if(a%2==0 && b%2==1 && c%2==1)
            cout<<"1\n";
        if(a%2==1 && b%2==0 && c%2==1)
            cout<<"0\n";

        if(a%2==0 && b%2==0 && c%2==1)
            cout<<"1\n";
        if(a%2==0 && b%2==1 && c%2==0)
            cout<<"0\n";
    }

	return 0;
}

```



---

## 作者：Cht_master (赞：1)

- 题意简述：给定一个包含 $a$ 个 1，$b$ 个 2，$c$ 个 3 的序列，要求将该序列分成两部分，使得两部分的差的绝对值最小。多组数据，$1\le t\le 10^3$，$1\le a,b,c\le 10^9$。

- 题目解析：

  - > Tips：没有认真读题，没看到 $a,b,c\ge 1$ 的条件，就做复杂了。以下按照 $a,b,c\ge 0$ 的条件来做。

  - 发现答案不会超过 3。考虑如果有偶数个 3，则可以用 3 互相抵消；若有奇数个 3，则最多会剩下一个 3。

  - 基于上面那条性质，记 $ave=\dfrac{a+2\cdot b+3\cdot c}{a+b+c}$，由于答案不超过 3 那么就尝试 $sum=ave+i|i\in\{1,2,3\}$ 即可。

  - 最后的问题在于判断用 $a$ 个 1，$b$ 个 2，$c$ 个 3 能否组成 $sum$。根据贪心原理，数越小越容易调整答案，所以先把 3 全部用于组成 $sum$，然后再尝试 2，最后用 1。

- ```cpp
  //答案不会超过3,尝试ave+0/1/2/3即可.
  #include<bits/stdc++.h>
  #define ll long long
  using namespace std;
  ll a,b,c,sm,ave,ans;
  bool Try(ll x){
  	ll cnta(0),cntb(0),cntc(0);//必须把初值赋为0.
  	cntc=min(c,x/3),x-=3*cntc;//尝试3(记得和题目给定上限取min).
  	if(!x)return 1;//除尽了.
  	cntb=min(b,x/2),x-=2*cntb;//尝试2.
  	if(!x)return 1;
  	cnta=min(a,x),x-=cnta;//尝试1.
  	if(!x)return 1;
  	return 0;
  }
  ll Abs(ll x){return ((x>0)?(x):(-x));}
  ll cal(ll x){return Abs(sm-x*2);}//一部分为x,另一部分为sm-x,答案则为|sm-2x|.
  int main(){
  	int T;scanf("%d",&T);
  	while(T--){
  		scanf("%lld%lld%lld",&a,&b,&c),sm=a+2*b+3*c,ave=sm/2,ans=3;
  		for(int i(0);i<=3;++i)if(Try(ave+i))ans=min(ans,cal(ave+i));
  		printf("%lld\n",ans);
  	}
  	return 0;
  }
  ```

  

---

## 作者：do_while_true (赞：1)

结论：答案 $\leq 1$

给出构造：首先尽量 $a,b,c$ 每个都对半分，这样都模下 $2$，假设剩余了 $a'$ 个 $1$，$b'$ 个 $2$，$c'$ 个 $3$．简单分类讨论剩下的所有情况，都可构造出答案 $\leq 1$ 的方案．

例如，仅剩余一个 $3$ 时，撤回两个 $1$，两个 $2$，然后一边分 $2,2$ ，一边分 $1,1,3$．

由于答案 $\leq 1$，判断总和的奇偶性即可得知答案。

---

## 作者：ZBAA_MKC (赞：1)

比赛的时候我是按照样例找规律的：如果所有歌曲的时长总和是偶数，那么就一定可以让两个音乐会的总时长相同。

赛后我想到了类似于 `0 0 1`，`0 1 0` 这样恶心的数据可以 hack 掉我的做法，但我读题后发现数据范围中的 $a,b,c$ 都是大于 $0$ 的，于是我就放心了。目前没有找到可以 hack 掉我的做法的数据，如果有谁找到了可以再评论区告诉我。

代码如下：

```cpp
#include <iostream>
using namespace std;

int main()
{
    int t;
	cin >> t;
	while (t--)
	{
		long long a, b, c;
		cin >> a >> b >> c;
		if ((a + b * 2 + c * 3) % 2 == 0)
		{
			cout << 0 << endl;
		}
		else
		{
			cout << 1 << endl;
		}
	} 
	return 0;
}

```

---

## 作者：gaozitao1 (赞：1)

**题目大意**：有 $a$ 个 $1$ 分钟的音乐，$b$ 个 $2$ 分钟的音乐，$c$ 个 $3$ 分钟的音乐，将这些音乐分成 $2$ 组，使两组音乐的总时长之差的绝对值尽可能小。

在理想状态下，如果音乐的总时长为奇数，那么答案是 $1$ ，如果音乐的总时长为偶数，那么答案是 $0$ 。

那么，能不能达到理想状态呢？

如果音乐的总时长为奇数，那么减去一个一分钟的音乐，就变成了总时长为偶数，所以下面只讨论音乐总时长为偶数。

将每种音乐平均分到两个组，这样分之后，现在两个组的音乐的总时长是相等的，每种音乐要么剩下一组，要么已经分完了。而且剩下的音乐的总时长也是偶数。那么可能有三种情况。

1. 剩下一组两分钟音乐，其他音乐不剩。

	解决方法：将第一组的一个一分钟音乐移到第二组，将剩下的一组两分钟音乐放到第一组。
2. 剩下一组一分钟音乐和一组三分钟音乐。

	解决方法：将第一组一个两分钟音乐移到第二组，将剩下的一组一分钟音乐和一组三分钟音乐放到第一组。
3. 每种音乐各剩下一组

	解决方法：将一分钟音乐和两分钟音乐放到第一组，将三分钟音乐放到第二组。
    
通过这些证明，说明了最后结果只和音乐总时长有关。所以只需要求出总时长的奇偶性就行了。

注意可能爆 int 。

代码：
```cpp
#include<cstdio>
#include<iostream>
int main()
{
	int a,b,c,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&a,&b,&c);
		printf("%d\n",(1ll*c*3+a+b*2)%2);
	}
	return 0;
}
```

---

## 作者：qwq___qaq (赞：1)

### 题意简述
一个人有 $a$ 一分钟的歌，$b$ 张两分钟的歌，$c$ 张三分钟的歌。他想把所有的歌曲分发给两场音乐会，这样每一首歌都应该包含在一场音乐会中。目标尽可能缩小音乐会持续时间的差。
### 算法思路
易得总用时为 $t=a+2b+3c$。首先，从样例分析，应该是一个东西模 $2$ 的余数，猜测为 $t \bmod 2$ 的值，但是缺少证明。
### 正确性证明
首先提交代码，发现它应该是可以 $A$ 的，接下来是一个 **小小**的证明。

（1）首先，我们以最贪心的思想，选 $3$，若 $c\bmod2=1$，那么进入操作（2），否则进入操作（3）。

（2）若 $b\bmod2=1$，那么放一个选到少的那组去，可以保证差为 $1$；防止则放两个到少的那组去，差为 $1$，进入操作 （4）。

（3）此时差为 $0$，如果 $b\bmod2=1$，那么随便多放一个，差为 $2$，进入操作（5）；否则差为 $0$，进入操作（6）。

（4）此时，我们已经保证了差为 $1$，若 $a\bmod 2=1$，那么先补一个到少的那里去，剩下的平均分配，答案为 $0$；否则直接平均分配，答案为 $1$。

（5）此时差为 $2$，先补两个到少的那里，差为 $0$，奇偶性不变，尽量平均分配，答案为 $a\bmod2$。

（6）此时差为 $0$，直接平均分配，答案为 $a\bmod2$。
****
综上，答案为 $t\bmod2$，得证。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
signed main(){
    scanf("%lld",&t);
    for(int i=1,a,b,c;i<=t;i++){//多组数据
        scanf("%lld%lld%lld",&a,&b,&c);
        printf("%lld\n",(a+2*b+3*c)%2);//可能爆 int
    }
    return 0;
}
```

---

## 作者：_easy_ (赞：0)

# 思路
观察样例的输入输出不难发现输出的总是 $0$ 或者 $1$。然后再结合题目意思可以发现时间的奇偶性和答案有关系。下面给出证明：
- 贪心，先把 $3$ 分钟的选了。如果 $c$ 是奇数，就把 $3$ 和 $1$ 配对，$2$ 两两分组，最后要么剩下 $1$,要么剩下 $0$，即根据总时间的奇偶性来判断。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,a,b,c;//一定要开long long哦
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b>>c;
		cout<<(a+b*2+c*3)%2<<endl;
	}
	return 0;
}
````

---

## 作者：Cat_shao (赞：0)

本题难度红题（感觉有做法比我的要简单）。


## 题目大意

一共 $t$ $(1 \le t \le 1000)$ 组数据，对于每一组数据输入三个数 $a, b, c$ $(1 \le a, b, c \le 10^9)$，表示有 $a$ 个 1， $b$ 个 2， $c$ 个 3。现在要将这些数分成两堆，使这两堆的差最小。

## 解法

~~第一眼看成背包~~，因为 $1 \le a, b, c \le 10^9$ ，所以对于每一组数据一定是 $O(1)$ 求出来的。

考虑到 1, 2, 3 三个数相差不大，我们可以先将这些数分成两堆：
1. 第一堆有 $\left \lfloor \frac{a}{2}  \right \rfloor$ 个 1，$\left \lfloor \frac{b}{2}  \right \rfloor$ 个 2，$\left \lfloor \frac{c}{2}  \right \rfloor$ 个 3 。（ $\lfloor \rfloor$ 表示向下取整 ）
2. 第二堆有 $a - \left \lfloor \frac{a}{2}  \right \rfloor$ 个 1，$b - \left \lfloor \frac{b}{2}  \right \rfloor$ 个 2，$c - \left \lfloor \frac{c}{2}  \right \rfloor$ 个 3 。

第一堆的和 $\le$ 第二堆的和，而且两者差不会超过 6，相比这是毋庸置疑的。（差为 6 的情况就是第二堆的 $a, b, c$ 各比第一堆多一个 ）

这个时候我们就可以写一个 01背包，容量为 6，用于计算在 $a - \left \lfloor \frac{a}{2}  \right \rfloor$ 个 1，$b - \left \lfloor \frac{b}{2}  \right \rfloor$ 个 2，$c - \left \lfloor \frac{c}{2}  \right \rfloor$ 个 3 的情况下能否凑出每一个数。

如果第二堆数能凑出来 $k$ 这个数，那么把第一堆的和加上 $k$ ，第二堆的和减去 $k$ 后做一个差 叫 $res$，我们可以枚举每一个 $k$ $(0 \le k \le 6)$ 然后求得最小的 $res$ ，这个 $res$ 也是最终的答案。

其实说了这么多就是枚举每一种靠谱的分配情况，由于靠谱的分配情况并不多，所以可以直接枚举。

```cpp
//
// Created by Cat-shao on 2021/10/24.
//
 
#include <bits/stdc++.h>
using namespace std;
 
int T, a, b, c, halfA, halfB, halfC, l, r;
bool able[20];
 
int main()
{
    cin >> T;
    while (T--) {
        memset(able, 0, sizeof(able));
        cin >> a >> b >> c;
        halfA = a / 2;
        halfB = b / 2;
        halfC = c / 2;
        able[0] = true;
        for (int j = 1; j <= min(a - halfA, 6); ++j) {
            for (int i = 5; i >= 0; --i) {
                if (able[i]) {
                    able[i + 1] = true;
                }
            }
        }
        for (int j = 1; j <= min(b - halfB, 3); ++j) {
            for (int i = 5; i >= 0; --i) {
                if (able[i]) {
                    able[i + 2] = true;
                }
            }
        }
        for (int j = 1; j <= min(c - halfC, 2); ++j) {
            for (int i = 5; i >= 0; --i) {
                if (able[i]) {
                    able[i + 3] = true;
                }
            }
        }
        l = halfA + 2 * halfB + 3 * halfC;
        r = a - halfA + 2 * (b - halfB) + 3 * (c - halfC);
        int res = abs(r - l);
        for (int i = 0; i <= 6; ++i) {
            if (able[i]) {
                res = min(res, abs((l + i) - (r - i)));
            }
        }
        cout << res << endl;
    }
    return 0;
}
```

---

## 作者：Alex_Wei (赞：0)

### 1582A. [Luntik and Concerts](https://codeforces.com/contest/1582/problem/A)

注意到 $a,b,c$ 下界均为 $1$，因此可以这样构造：首先依次考虑 $a$ 个 $1$ 和 $c$ 个 $3$，哪个音乐会时间更少就放到里面，若相等则任意放。我们就得到了一个两个时长相差不超过 $3$ 的演唱会，且相差是奇数还是偶数由 $a+3c$ 即 $a+c$ 的奇偶性决定。由于至少有一个 $2$ 因此我们一定能将时长差从 $3$ 缩减到 $1$。

对于剩下的 $2$，若相差为 $1$ 则放到时长较少的那个音乐会里面从而保证时长差为 $1$。相差为 $2$ 同理。若相差为 $0$，那么我们将有 $1$ 的那个音乐会的 $1$ 挪到另一个里面去，再放上一个 $2$ 即可保证相差恒为 $0$。

综上，我们只需输出 $a+c$ 对 $2$ 取模后的结果即可。时间复杂度 $\mathcal{O}(T)$。

```cpp
int main() {
	int T, a, b, c; cin >> T;
	while(T--) cin >> a >> b >> c, cout << (a + c & 1) << endl;
	return 0;
}
```

---

## 作者：int1 (赞：0)

**答案：$a + 2b + 3c$ 除以 $2$ 的余数。**

**引理：一定存在一种构造方案，使得两组之差的绝对值 $\le 1$。**

证明：因为 $a, b, c > 0$，考虑先放 $3$，再放 $2$，最后放 $1$。每次往两组中和较小的那一组中放，放完 $3$ 之后，两组之差的绝对值只能是 $0$ 或 $3$；放完 $2$ 后只能是 $0$ 或 $1$ 或 $2$，再放 $1$ 即可得到 $0$ 或 $1$。

**事实：当两组之差的绝对值为 $1$ 的时侯和为奇数，否则和为偶数。**

由该引理和该事实得证。

---

