# The Legend of Freya the Frog

## 题目描述

Freya the Frog is traveling on the 2D coordinate plane. She is currently at point $ (0,0) $ and wants to go to point $ (x,y) $ . In one move, she chooses an integer $ d $ such that $ 0 \leq d \leq k $ and jumps $ d $ spots forward in the direction she is facing.

Initially, she is facing the positive $ x $ direction. After every move, she will alternate between facing the positive $ x $ direction and the positive $ y $ direction (i.e., she will face the positive $ y $ direction on her second move, the positive $ x $ direction on her third move, and so on).

What is the minimum amount of moves she must perform to land on point $ (x,y) $ ?

## 说明/提示

In the first sample, one optimal set of moves is if Freya jumps in the following way: ( $ 0,0 $ ) $ \rightarrow $ ( $ 2,0 $ ) $ \rightarrow $ ( $ 2,2 $ ) $ \rightarrow $ ( $ 3,2 $ ) $ \rightarrow $ ( $ 3,5 $ ) $ \rightarrow $ ( $ 6,5 $ ) $ \rightarrow $ ( $ 6,8 $ ) $ \rightarrow $ ( $ 9,8 $ ) $ \rightarrow $ ( $ 9,11 $ ). This takes 8 jumps.

## 样例 #1

### 输入

```
3
9 11 3
0 10 8
1000000 100000 10```

### 输出

```
8
4
199999```

# 题解

## 作者：player_1_Z (赞：5)

### 先来分析题目：
这一题给了终点坐标 $x$，$y$ 和一次跳跃最大距离 $k$ ，求最小跳跃次数。很明显，跳跃次数最小每一步就尽可能跳最大距离 $k$。同时，必须按照 $x$ 轴，$y$ 轴顺序轮流跳，所以就算 $x$ 坐标与终点的 $x$ 坐标相等，也要先向 $x$ 轴跳 $0$ 距离，再向 $y$ 轴跳 $k$ 距离。**那么，我们先算出 $x$ 轴跳几次和 $y$ 轴跳几次，求最大值乘二就行了。**  
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,y,k;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>x>>y>>k;
		int xs=x/k,ys=y/k;
		cout<<2*max(xs,ys)<<endl;
	}
	return 0;
}
```
但是，这样会错，分析一下错因。
### 重点：
首先，我们发现：如果 $y$ 和 $x$ 不是 $k$ 的倍数，那么**最后需要多跳一次了补齐最后的一点距离**。还有，因为跳跃顺序是
先向 $x$ 轴跳，再向 $y$ 轴跳，所以如果是 $x$ 轴方向跳跃次数更多，**输出中乘二后需要减一**，所以在输出时加个判断就行了。
### 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,y,k;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>x>>y>>k;
		int xs=x/k,ys=y/k;
		if(xs*k<x) xs++;if(ys*k<y) ys++;
		if(xs<=ys) cout<<2*ys<<endl;
		else if(xs>ys) cout<<2*xs-1<<endl;
	}
	return 0;
}
```

---

## 作者：Yxy7952 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF2009C)

[翻译](https://www.luogu.com.cn/discuss/984076)

建议评橙。
## 思路

显然，我们每次都尽量跳远一点。

所以可以得到：如果剩余距离大于 $k$，则一次跳 $k
$，否则可以一次跳完。

于是，横向需要跳 $\left \lceil \frac{x}{k}  \right \rceil $ 次，纵向跳 $\left \lceil \frac{y}{k}  \right \rceil $ 次。

如果 $\left \lceil \frac{x}{k}  \right \rceil <\left \lceil \frac{y}{k}  \right \rceil $ 那么我们可以先 $x,y,\dots,x,y$ 交替跳，最后 $y$ 多的部分 $0,y,\dots,0,y$ 这样跳，跳跃次数为 $2\times\left \lceil \frac{y}{k}  \right \rceil $。

如果 $\left \lceil \frac{x}{k}  \right \rceil >\left \lceil \frac{y}{k}  \right \rceil $ 那么我们可以先 $x,y,\dots,x,y$ 交替跳，最后 $x$ 多的部分 $x,0,\dotsx,x$ 这样跳，跳跃次数为 $2\times\left \lceil \frac{x}{k}  \right \rceil -1$，因为最后不用再跳一次 $y$。

如果 $\left \lceil \frac{x}{k}  \right \rceil =\left \lceil \frac{y}{k}  \right \rceil $ 那么我们可以 $x,y,\dots,x,y$ 交替跳，跳跃次数为 $\left \lceil \frac{x}{k}  \right \rceil +\left \lceil \frac{y}{k}  \right \rceil$。

话不多说，直接看代码和注释。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,x,y,k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		cin>>x>>y>>k;
		int a=x/k,b=y/k;
		if(a*k<x) a++;
		if(b*k<y) b++;//如果还剩一点没跳，跳跃次数加1
		if(a<b) cout<<2*b;
		else if(a>b) cout<<2*a-1;
		else cout<<a+b;
		cout<<"\n";
	}
	return 0;
}

```

---

## 作者：tiantianyang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF2009C)

$ok$，回归正题。
## 题目大意
就是一直想跳到终点的青蛙。
## 思路
这题就是一个非常简单的贪心。~~完了~~

那不可能！~~不然就过不了了~~

首先它是从$（0,0）$出发的，且 $x$ 和 $y$ 皆为非负数。

所以就可以每次都跳最大值 $k$，横向就跳$\lfloor\frac{x}{k}\rfloor$ 次，竖向就跳  $\lfloor\frac{y}{k}\rfloor$ 次。 

紧接着开始判断！

- $\lfloor\frac{x}{k}\rfloor$ < $\lfloor\frac{y}{k}\rfloor$ 刚开始就是 $x$，$y$，$x$，$y$，……，$x$，$y$ 的跳，后面是 $0$，$y$，$0$，$y$，……，$0$，$y$ 的跳，一直到最后。所以就是 $2\times\lfloor\frac{y}{k}\rfloor$！
- $\lfloor\frac{x}{k}\rfloor$ > $\lfloor\frac{y}{k}\rfloor$ 刚开始就 $x$，$y$，$x$，$y$，……，$x$，$y$ 的跳，后面是 $x$，$0$，$x$，$0$，……，$x$，$0$ 的跳，一直到最后。所以就是 $2\times\lfloor\frac{x}{k}\rfloor$！
- $\lfloor\frac{x}{k}\rfloor$ = $\lfloor\frac{y}{k}\rfloor$ 就一直是 $x$，$y$，$x$，$y$，……，$x$，$y$ 的跳，所以就是 $\lfloor\frac{x}{k}\rfloor+\lfloor\frac{y}{k}\rfloor$！

$ok$ 理清楚了吧那就 $3,2,1$ **上代码**：

~~知道你们只想看这个~~ 

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);//这两加不加无所谓 
	int t;cin>>t;//次数 
	while(t--){
		int x,y,k,maxx=0,maxy=0;
		cin>>x>>y>>k;
		maxx=(k+x-1)/k;maxy=(y+k-1)/k;//算到哪一个更远 (被除数+除数-1)/除数：小技巧向上取整 
		if(maxx>maxy) cout<<maxx*2-1<<endl;//到x更远要先乘2再减一 
		else cout<<maxy*2<<endl;//到y更远直接乘2输出 
	}
	return 0;//完美收官 
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

令 $n=\left\lceil\dfrac{x}{k}\right\rceil,m=\left\lceil\dfrac{y}{k}\right\rceil$，表示至少跳 $n$ 次横向与 $m$ 次纵向。因为第一步必须先横跳，所以若 $n>m$，则最少跳 $2n-1$ 次，否则最少跳 $2m$ 次。

---

## 作者：liuli688 (赞：0)

### 思路
比较明显的贪心题。如果剩余距离大于 $k$，则一次跳 $k$，否则可以一次跳完。

于是，横向需要跳 $\lceil \dfrac x k \rceil$ 次，纵向跳 $\lceil \dfrac y k \rceil$ 次。

由于第一次是横向跳跃，因此如果横向跳跃次数大于纵向跳跃次数则输出横向跳跃次数的两倍减一，否则输出纵向跳跃次数的两倍。
### 代码
```cpp
#include <cstdio>
#include <cmath>
 
int T, x, y, k, xx, yy;
 
signed main()
{
    for (scanf("%d", &T); T--; )
    {
        scanf("%d%d%d", &x, &y, &k);
        xx = ceil(x * 1.0 / k);
        yy = ceil(y * 1.0 / k);
        if (xx > yy)
            printf("%d\n", xx + xx - 1);
        else
            printf("%d\n", yy + yy);
    }
    return 0;
}
```

---

## 作者：huanglihuan (赞：0)

### 思路

记 $x_1$ 为 $x\div k$ 向上取整的值，$y_1$ 为 $y\div k$ 向上取整的值。

则，若 $x_1=y_1$，答案为 $x_1+y_1$，因为两边都需要跳。

如果 $x_1\le y_1$，则第二个左标到 $y$ 时需要 $2\times y_1$，反之，如果 $x_1\ge y_1$，则需要 $2\times x_1-1$ 次，因为最后一次不用跳。

代码：

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 988444333
#define MOD 1000000007
using namespace std;
const int N = 1e5 + 5;
inline int read ()
{
	int x = 0;
	bool f = 1;
	char c = getchar ();
	while (c < '0' || c > '9') f = (c == '-' ? !f : f),c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return (f ? x : -x);
}
inline void write (int x)
{
	if (x < 0) putchar ('-'),x = -x;
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
void solve ()
{
	int x = read (),y = read (),k = read ();
	int x_1 = (x - 1) / k + 1,y_1 = (y - 1) / k + 1;
	if (x_1 == y_1) write (x_1 + y_1);
	if (x_1 < y_1) write (2 * y_1);
	if (x_1 > y_1) write (2 * x_1 - 1);
	putchar ('\n');
}
signed main ()
{
	int T = read ();
	while (T --) solve ();
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

要从 $(0,0)\to (x,y)$，显然每次尽量跳 $d$ 步，也就是 $x,y$ 方向分别要 $\lceil\frac{x}{d}\rceil,\lceil\frac{y}{d}\rceil$ 次，下面记为 $s_x,s_y$。

如果 $s_x<s_y$，答案是 $2\times s_y$。

如果 $s_x>s_y$，答案是 $2\times s_x-1$，显然最后一步不用跳。

如果两者相等，答案是 $s_x+s_y$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,x,y,k;
signed main(){
    for(cin>>T;T;--T){
        cin>>x>>y>>k;
        x=(x/k)+(bool)(x%k),y=(y/k)+(bool)(y%k);
        if(x>y)
            cout<<2*x-1<<'\n';
        else if(x==y)
            cout<<2*x<<'\n';
        else
            cout<<2*y<<'\n';
    }
    return 0;
}
```

---

## 作者：ybc2026lhy (赞：0)

[博客食用效果更佳](https://www.luogu.com.cn/article/00lmbl0y)

##### 分析：
这道题是一道数学题，不难发现，当 $x/k$ 向上取整后等于 $y/k$ 向上取整时，答案就是它们的和。又根据样例可以得到，当 $x/k$ 向上取整后小于 $y/k$ 向上取整时，答案是 $2$ 倍的 $y/k$ 向上取整，而当 $x/k$ 向上取整后大于 $y/k$ 向上取整时，答案为 $2$ 倍的 $x/k$ 向上取整减去一。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>T;
	while(T--){
		int x,y,k;
		cin>>x>>y>>k;
		int ans=(x+k-1)/k,cnt=(y+k-1)/k;//向上取整
		if(ans==cnt){
			cout<<ans+cnt<<"\n";
		} else if(ans<cnt){
			cout<<cnt*2<<"\n";
		} else {
			cout<<ans*2-1<<"\n";
		}
	}
	return 0;
}

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://codeforces.com/contest/2009/problem/C)

## 分析

考虑 $x$ 和 $y$ 两个方向，发现在 $x$ 方向上所需的跳跃次数为 $\lceil \frac{x}{k} \rceil$。那么同样，在 $y$ 方向上所需的跳跃次数为 $\lceil \frac{y}{k} \rceil$。试着组合一下，便发现两种情况。

- $\lceil \frac{x}{k} \rceil \le \lceil \frac{y}{k} \rceil$。在这种情况下，需要在 $y$ 方向上进行 $\lceil \frac{y}{k} \rceil - \lceil \frac{x}{k} \rceil$ 次额外跳跃。所以当选择 $x$ 方向上的 $d = 0$ 时，所需跳跃次数最小，需要 $2 \times \lceil \frac{y}{k} \rceil$ 次跳跃。

- $\lceil \frac{x}{k} \rceil > \lceil \frac{y}{k} \rceil$。使用与前一种情况相同的推理方法，但是一开始是朝向 $x$ 方向的，所以在最后一跳时，不需要朝向 $y$ 方向跳。总共需要 $2 \times \lceil \frac{x}{k} \rceil - 1$ 次跳跃。

时间复杂度：$O(t)$。

## Code

```cpp
/*
Codeforces CF2009C The Legend of Freya the Frog  
*/
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a;i <= b;i++)
#define per(i,a,b) for(int i = a;i >= b;i--)
#define pb push_back
#define PII pair<int,int>
using namespace std;
typedef long long ll;
int t;
ll x,y,k;
inline void solve()
{
	cin>>x>>y>>k;
	ll pos = (x + k - 1) / k;//向上取整
	ll res = (y + k - 1) / k;
	if(pos <= res)
	{
		cout<<res * 2<<"\n";
	}
	else
	{
		cout<<pos * 2 - 1<<"\n";
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

[AC submissions](https://codeforces.com/contest/2009/submission/279874806)

---

## 作者：coderJerry (赞：0)

小花絮：~~这个人交了 6 次才过~~。

和官解一样的思路。很直接的想法，如果只考虑 $x$ ，那么纵坐标走到 $x$ 处需要 $2\lceil x/k \rceil-1$ 步（乘 $2$ 是因为每走两步才有 $1$ 步是改变 $x$ 坐标，减 $1$ 是因为第一步就是改变 $x$ 坐标）。同理横坐标走到 $y$ 处需要 $2\lceil y/k \rceil$ 步，两者取个最大值就是答案。

赛时代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t,x,y,k;
    cin>>t;
    while(t--){
        cin>>x>>y>>k;
        cout<<max(2*((x+k-1)/k)-1,2*((y+k-1)/k))<<endl;
    }
    return 0;
}
```

---

## 作者：cly312 (赞：0)

比较一眼的题目，场切了。

分别考虑 $x$ 和 $y$。在 $x$ 方向上我们需要的跳跃次数是 $\lceil \frac{x}{k} \rceil$，在 $y$ 方向上我们需要的跳跃次数是 $\lceil \frac{y}{k} \rceil$。考虑下面的两种情况：

- $\lceil \frac{y}{k} \rceil \geq \lceil \frac{x}{k} \rceil$。在这种情况下，需要在 $y$ 方向上有 $\lceil \frac{y}{k} \rceil - \lceil \frac{x}{k} \rceil$ 额外的跳跃。当青蛙跳跃时，它将选择 $x$ 方向的 $d = 0$。所以总共需要 $2 \cdot \lceil \frac{y}{k} \rceil$ 个跳跃。

- $\lceil \frac{y}{k} \rceil < \lceil \frac{x}{k} \rceil$。同理，但是由于青蛙最初面向 $x$ 方向，所以最后一次跳跃不需要向 $y$ 方向。总共需要 $2 \cdot \lceil \frac{x}{k} \rceil - 1$ 个跳跃。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	int t;
	cin>>t;
	while(t--){
		ll x,y,k;
		cin>>x>>y>>k;
		ll a=(x+k-1)/k;
		ll b=(y+k-1)/k;
		ll m;
		if(a>b)
			m=2*a-1;
		else
			m=2*b;
		cout<<m<<"\n";
	}
}
```

---

## 作者：wawatime1 (赞：0)

### 思路
显而易见的结论。

横向至少要跳 $⌈\displaystyle \frac{x}{k}⌉$ 次，记为 $a$。纵向至少跳 $⌈\displaystyle \frac{y}{k}⌉$，记为  $b$。

- 如果 $a = b$ 输出 $a + b$。
- 如果 $a < b$ 输出 $b \times 2$。
- 如果 $a > b$ 输出 $a \times 2 - 1$，为什么要减一？因为第一次是先跳的横向。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, x, y, k, a, b;
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &x, &y, &k);
		a = ceil(x * 1.0 / k);
		b = ceil(y * 1.0 / k);
		if (a == b)
			printf ("%d\n", a + b);
		else if (a > b)
			printf("%d\n", 2 * a - 1);
		else
			printf("%d\n", 2 * b);
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

一道贪心题。

横向需要跳 $⌈\frac{x}{k}⌉$ 次，纵向跳 $⌈\frac{y}{k}⌉$ 次。

由于第一次是横向跳跃，因此如果横向跳跃次数大于纵向跳跃次数则输出横向跳跃次数的两倍减一，否则输出纵向跳跃次数的两倍。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
ll T, x, y, k, xx, yy;
void read () {
	cin >> x >> y >> k;
    xx = ceil (x * 1.0 / k); yy = ceil (y * 1.0 / k);
    if (xx > yy) cout << xx + xx - 1 << endl;
    else cout << yy + yy << endl;
}
int main () {
	cin >> T;
	while (T --) read ();
    return 0;
}
```

---

## 作者：Badans (赞：0)

# 思路
## 跳跃次数分解

假设青蛙需要 $a$ 次跳跃完成 $x$ 方向的移动，$b$ 次跳跃完成 $y$ 方向的移动：

$a = \lceil \frac{x}{k} \rceil \quad b = \lceil \frac{y}{k} \rceil$
## 跳跃方向交替规则
总跳跃次数 $n=a+b$，但需要满足“交替规则”：

**奇数**次跳跃只能先移动 $x$ 方向再移动 $y$ 方向；

**偶数**次跳跃可以完美交替。

当 $a≠b$ 时：选择**较大**的方向（$a$ 或 $b$）进行多次跳跃，补足另一个方向。

当 $a=b$ 时：$a+b$ 正好满足交替规则。

## 特殊情况

$x=0$ 或 $y=0$：只需计算一个方向上的跳跃次数，结果为**偶数**即可。

$x=y=0$：不需要任何跳跃，结果为 $0$。

# 代码：
```python
import math

T = int(input()) 
for _ in range(T):
    x, y, k = map(int, input().split())  
    xx = math.ceil(x / k) 
    yy = math.ceil(y / k) 
    if xx > yy:
        print(xx + xx - 1)
    else:
        print(yy + yy)

```

---

