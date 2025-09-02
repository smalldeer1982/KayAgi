# 【MX-X11-T0】「蓬莱人形 Round 1」糖果曲奇巧克力

## 题目背景

原题链接：<https://oier.team/problems/X11A>。

---

「CANDY CANDY CANDY  COOKIE」

「CANDY CANDY  CHOCOLA...」

「"CANDYCHOCANDYCHOCODY..."」

「CHOCOLATE」


## 题目描述

你有 $a$ 个糖果，$b$ 个曲奇，你可以每次可以执行下面两种操作之一：

- 选择两个糖果**或者**两个曲奇，将它们删掉，花费 $x$。（你需要保证至少有两个糖果或至少有两个曲奇才能进行此操作）

- 选择一个糖果**和**一个曲奇，将它们删掉，花费 $y$。（你需要保证至少有一个糖果和一个曲奇才能进行此操作）

问删光糖果**或**删光曲奇（或两个都删光）的最小花费。

## 说明/提示

**【样例解释 #1】**

对于第一组测试数据，用 $4$ 次二操作即可删光糖果和曲奇，花费 $1 \times 4 = 4$。

对于第二组测试数据，对曲奇用 $2$ 次一操作，再用 $1$ 次二操作即可删光曲奇，花费 $5 \times2 + 3 \times 1 = 13$。

**【数据范围】**

对于所有测试数据，$1 \le T \le 10$，$1 \le a,b,x,y \le 10^5$。

## 样例 #1

### 输入

```
3
4 4 10 1
10 5 5 3
2024 1226 32423 23423```

### 输出

```
4
13
19875299```

# 题解

## 作者：GeorgeDeng (赞：5)

## 题目分析

 $T$ 组数据，每组数据有 $a$ 个糖果和 $b$ 个曲奇。有两种删除操作：

 - 选出 $2$ 个糖果或者 $2$ 个曲奇，代价为 $x$；
 - 选出 $1$ 个糖果和 $1$ 个曲奇，代价为 $y$。

求删完糖果或曲奇的最小代价。

## 思路

一道分类讨论题。

因为有可能 $x>2y$，所以如果出现这种情况的时候，一个一个删除更优，可以直接把 $x$ 赋值为 $2\times y$。

接下来就是计算。我们讨论把糖果删完和把曲奇删完的代价，答案就是删完糖果的代价与删完曲奇的代价中取最小值。糖果或曲奇删除的代价怎么算？因为两个两个删效果更快，而且不用考虑另外一个东西，所以优先两个两个删，代价为数量除以 $2$ 再乘上 $x$。然后把不足以两个两个删的一个一个删就行了，代价是数量对 $2$ 取模再乘上 $y$。综上可以推出式子 $ans=\min(a\div 2 \times x+a \bmod 2 \times y,b\div 2 \times x+b \bmod 2 \times y)$。

注意并不是哪个少优先删哪个，我就是因为这个被卡了 $30min$。

## code:


```cpp
#include <iostream>
#define int long long
using namespace std;

signed main()
{
    int t;
    cin>>t;
    while(t--){
        int a,b,x,y;
        cin>>a>>b>>x>>y;
        if(x>2*y) x = 2*y;//如果两个一起删除还没有一个一个删除代价低，就x=2*y
        cout<<(min(((a/2)*x+(a%2)*y),(b/2)*x+(b%2)*y))<<endl;//直接求答案
    }
    return 0;
}
```

---

## 作者：dendky (赞：3)

## 题意

对于 $a,b$ 堆有两种操作，每次可以执行下面两种操作之一：

1. 选择两个糖果**或者**两个曲奇，将它们删掉，花费 $x$。（需要保证至少有两个糖果或至少有两个曲奇才能进行此操作）
2. 选择一个糖果**和**一个曲奇，将它们删掉，花费 $y$。（需要保证至少有一个糖果和一个曲奇才能进行此操作）

求删光糖果**或**删光曲奇（或两个都删光）的最小花费。
其中，$1 \le T \le 10$，$1 \le a,b,x,y \le 10^5$。

## 思路

**方案一**：对于 $a,b$ 堆中最小的一堆一直进行操作二，直到删完 $a,b$ 堆中最小的一堆。最后的花费即为 $\min(a, b) \times y$。此方案在 $x > {2 \times y}$ 或 $a=1$ 或 $b=1$ 中花费最少。

**方案二**：对于 $b$ 堆尽可能多地进行操作一，此时分类讨论：

1. 当 $b$ 为偶数时，会使用 $\frac{b}{2}$ 次操作一，且正好清空 $b$ 堆，花费为 $\frac{b}{2} \times x$。
2. 当 $b$ 为奇数时，会使用 $\left\lfloor \frac{b}{2} \right\rfloor$ 次操作一，$b$ 堆剩余1个，需再进行一次操作二，花费为 $\left\lfloor \frac{b}{2} \right\rfloor \times x + y$。

此方案在 $x \le {2 \times y}$ 且 $b \le a$ 中花费最少。

**方案三**：对于 $a$ 堆尽可能多地进行操作一，思考过程与方案二同理。此方案在 $x \le {2 \times y}$ 且 $a \le b$ 中花费最少。

最后，只需比较方案一，方案二和方案三中花费最小的输出即可。

注意，因为 `min(a, b)` 和 `y` 最大可以取到 $10^5$，且 ${10^5 \times 10^5} = 10^{10}$，会炸 `int`，故开 `long long`。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t=1, a, b, x, y;//t赋值1是一个好的调试代码习惯，可以方便用于调试自己在场上写的hack数据
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);//快读
    cin>>t;
    while (t--) {
        cin>>a>>b>>x>>y;
        ll cnt1=min(a, b)*y;//一直使用操作二，直到删掉a, b中最小的一堆
        ll cnt2, cnt3;
        cnt2=b/2*x+(b%2)*y;//对b(曲奇堆)一直使用操作1，直到删完
        //   如果b为奇数，b%2==1，那么最后会使用一次操作一；如果为偶数，那么b%2==0，那么最后不会使用操作一
        //压行小技巧：b为奇数：(b%2)*y执行                 b为偶数：(b%2)*y不执行    
        cnt3=a/2*x+(a%2)*y;//对a(糖果堆)同理
        cout<<min({cnt1, cnt2, cnt3})<<"\n";//比较三种方法中花费最少的输出，记得换行
    }
    return 0;
}
``````

---

## 作者：小睿2012 (赞：1)

这题题最后的最小代价等于删掉糖果的最小的代价和删掉曲奇的最小代价中的较小值。

显然当操作一代价小于操作二的代价的 $2$ 倍时，由于我们删完一种即可，所以我们应该尽量先两个两个删，最后如果有剩的就在用操作二。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

long long ans1,ans2,a,b,x,y,c;

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		ans1 = ans2 = 0;
		cin >> a >> b >> x >> y;
		if(x < 2 * y)
		{
			ans1 += ((a / 2) * x);
			ans2 += ((b / 2) * x);
			a %= 2;
			b %= 2;
		}
		if(a > 0) ans1 += a * y;
		if(b > 0) ans2 += b * y;
		cout << min(ans1,ans2) << '\n';
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/213470699)

---

## 作者：LLY_0827 (赞：1)

## P12146 糖果曲奇巧克力

[传送门](https://www.luogu.com.cn/problem/P12146)

### 题意理解 (抽象化)

有 $a$ 个糖果，$b$ 个曲奇，每次执行下面两种操作之一：

- 选择两个糖果或者两个曲奇（存在至少两个时），将它们删掉，花费 $x$。

- 选择一个糖果和一个曲奇（存在至少各一个时），将它们删掉，花费 $y$。

问删光糖果，或删光曲奇，或两个都删光的最小花费。

### 思路

按题意分别计算出三种情况的花费，取最小值。

- 尽可能将糖果成对删掉。以 $x$ 的代价成对消除，若有余下的一个，再和另一个曲奇结合，以 $y$ 的代价单个删除。
  - 并不用担心操作无效，因为糖果和曲奇的个数均大于等于 $1$。
```cpp
 ans=min(ans,(a/2)*x+(a%2)*y);
```
- 尽可能将曲奇成对删除。同理。
```cpp
 ans=min(ans,(b/2)*x+(b%2)*y);
```
- 尽可能将曲奇和糖果配对删除，只需要将其中一种删完，便取二者数量最小值作为删除数量。
```cpp
 ans=min(ans,min(a,b)*y）;
```

### 赛时代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main(){
	ll t;
	cin>>t;
	while (t--){
		ll a,b,x,y;
		cin>>a>>b>>x>>y;
		ll ans=1145141919810;
		
		//no 1.
		ans=min(ans,(a/2)*x+(a%2)*y);
		
		//no 2.
		ans=min(ans,(b/2)*x+(b%2)*y);
		
		//no 3.
		ll min3=min(a,b);
		ll pc3=min3*y;
		ans=min(ans,pc3);
	
    cout<<ans<<"\n";
	}
}
```

---

## 作者：da_ke (赞：1)

这道题看上去很像是 DP，其实也确实可以用 DP 优化过来。

注意到 $a,b\leq 10^5$，考虑枚举。

设当前目标是将 $a$ 减为 $0$，设进行了 $i$ 次操作二，则一定要进行 $\frac{a-i}{2}$ 次操作一。总代价为 $y\times i+x\times \frac{a-i}{2}$。

然后讨论将 $b$ 减为 $0$ 的情况。对所有情况取最优。

注意：因为我们枚举操作二，操作二的数目无法改变，因此，操作一剩余的无法用操作二补足。则必须使得 $a-i \equiv 0 \pmod 2$。

读者可自行尝试枚举另外一个量。

---

## 作者：qwqerty (赞：1)

# 解题思路
分情况讨论。  
若 $x\ge 2\times y$，则用 $2$ 次操作二比 $1$ 次操作一更优，则直接选择所有的操作二，此时的结果为 $\min\{a\times y,b\times y\}$。  
否则尽可能多地进行操作一，直到无法操作为止。对于 $a$，需进行 $\lfloor\dfrac{a}{2}\rfloor$ 次操作，最后余下 $a\bmod2$。所以对于 $a$ 需花费 $x\lfloor\dfrac{a}{2}\rfloor+a\bmod2\times y$。最后取最小值，也就是 $\min\{x\lfloor\dfrac{a}{2}\rfloor+a\bmod2\times y,x\lfloor\dfrac{b}{2}\rfloor+b\bmod2\times y\}$。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, a, b, x, y; 
signed main() {
	cin >> t;
	while (t--) {
		cin >> a >> b >> x >> y;
        if (x >= 2 * y) cout << min(a * y, b * y) << "\n";
        else cout << min(a / 2 * x + a % 2 * y, b / 2 * x + b % 2 * y) << "\n";
	}
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

赛时被硬控 20min /qd

---

首先显然有一种方案是全部使用操作二直到数量较小者耗尽。

因为只需要使其中之一耗尽，所以可以用一个操作一顶替两个操作二，然后集火其中之一。如果操作一比两个操作二优秀，我们把每两个操作二全部替换，这是一个新方案。

如果你只思考耗尽数量较小者，那么你会爆零。

因为当前数如果是奇数，这意味着你为了清光它你将不得不使用一次操作二，如果操作二代价极大这是不可接受的。

所以无论曲奇糖果都要试着替一遍。

这三种方案的最小值即为答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
    int a,b,x,y;
    cin>>a>>b>>x>>y;
    if(a>b)swap(a,b);
    cout<<min({a/2*x+a%2*y,a*y,b/2*x+b%2*y})<<'\n';
}
signed main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

注意 `long long`。

---

## 作者：Little_duck_GGG (赞：0)

### 题目意思
现在有两个数 $a$ 和 $b$ 我们要通过两种操作来使得 $a$ 或 $b$ 变为零，问最少要消耗多少能量。

其中，两种操作分别为。
*   选择 $a$ 或 $b$ 减去二，这种情况需要消耗 $x$ 的能量。
*   选择 $a$ 和 $b$ 都减去一。这种情况需要消耗 $y$ 的能量。
### 题目思路
一见到这题，我们可以考虑贪心。我们肯定优先让最小的数变为零。

因为我们只要使得 $a$ 或者 $b$ 变为零就好了，而且两种操作对于 $a$ 和 $b$ 来说都是一样的，所以我们不妨设 $b \ge a$，那么**如果 $a$ 没有变成零，$b$ 肯定也不可能变为零**。

那么如何使用操作使得消耗的能量最少呢。这取决于两种操作各自的代价。

我们可以使得第二种操作变得和第一种操作**类似**，我们通过**操作两次**操作二，拟定一个新的操作，叫做操作三，它的功能是使得 $a$ 和 $b$ 两个数各自减去二，消耗 $2 \times y$ 的能量。

当在 $a \ge b$ 的情况下，我们对 $a$ 进行操作时，我们可以任意调动操作三，只要 $a \ge 0$ 因为如果满足 $a \ge 0$ 则 $b \ge 0$ 时必然的。

那当满足这种条件的时候，我们就可以把原来的两种操作，变成简洁易懂的操作。
*   将较小的数 $a$ 减去二，消耗 $x$ 的能量，命名它为新操作一。
*   将较小的数 $a$ 减去二，消耗 $2 \times y$ 的能量，命名它为新操作二。

那现在我们如何操作是不是就很清楚了。
当 $x \ge 2 \times y$ 的时候，说明我选择新操作二更优，选择新操作二。否则选择新操作一。

那么又有一个问题来了，如何执行新操作一和新操作二。

首先我们明确一个点，不论是新操作一还是新操作二，我们都会**尽力执行到不可行为止**。什么是不可行。就是 $a$ 不够减。

当执行新操作二时，$a$ 不够减，当且仅当 $a = 0$。执行时，因为新操作二其实等同于原来的操作二，所以我们执行此操作时，可以直接用原来的操作二。**$a \times y$ 就是它的能量**。此时的新操作二，其实只是一个**评判进行原操作二是否更优的标尺**。

当执行新操作一时，$a$ 不够减，当且仅当 $a < 2$，但因为 $a$ 必然为正整数，所以 $a \le 1$。则我们可以用 $a$ 去取模二，判断它进行操作后最终会不会**有剩余**，如果有剩余，则我们用**原操作二做完它**。

那么我们就可以打出以下代码了。

```cpp
u2=u3=1e14;
if(a>b) swap(a,b);//假设b>=a 
if(x>2*y)//如果新操作二更优，则选择 
{
	u2=a*y;
}
else//否则用新操作一 
{
  if(a%2==1) u2=(a/2)*x+y;//剩余，则用一次操作二补上
  else u2=(a/2)*x;
}
```
那么这样你就能获得整整十分。

好吧，故事并未结束，还有一个坑点。就是在执行新操作一的时候，如果有剩余，则会多消耗一个 $y$ 对吧。但如果此时的 $b = a + q$，且 $q$ 为奇数，$a$ 也为奇数，那你不是炸了。

所以还要特判这种条件。
给出代码。

```cpp
if(a%2==1&&b%2==0) u3=(b/2)*x;
```
这个不用解释了吧，最后输出 $u2$ 和 $u3$ 的最小值就行了。
给出完整的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long a,b,x,y,u1,u2,u3,u4;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>x>>y;
        u2=u3=1e14;
		if(a>b) swap(a,b);//假设b>=a 
		if(x>2*y)//如果新操作二更优，则选择 
		{
			u2=a*y;
		}
		else//否则用新操作一 
		{
			if(a%2==1) u2=(a/2)*x+y;
			else u2=(a/2)*x;
		}
		if(a%2==1&&b%2==0) u3=(b/2)*x;
		cout<<min(u2,u3)<<endl;//取最小
	}
	return 0;
}
```

---

## 作者：cjx_AK (赞：0)

有两种选择，直接分类讨论。

取糖果就比较哪一种操作更优，若第一种更优则剩下可能还有一颗需要执行操作二。

若操作二更优，则需要考虑曲奇的个数。

取曲奇同理，将变量反一下即可。

code：

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,a,b,x,y;
int cad(int a,int b){
	int res=0;
	if(x/2<y){
	//	cout<<'x';
		res+=a/2*x;
		if(a%2){
			res+=y;
		}
	}else{
		res+=y*min(a,b);
		a=max(a-b,0ll);
		if(a==0)return res;
		if(a%2){
			res-=y;
			a++;
		}
		res+=a/2*x;
	}
return res;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>a>>b>>x>>y;
	//	cout<<cad(a,b)<<endl;
	cout<<min(cad(a,b),cad(b,a))<<endl;
	}
}
```

---

## 作者：LRRabcd (赞：0)

# $\tt solution$

分两种情况：

- 删光糖果&#x20;
  - $b<a$，答案是 $\lfloor\frac{ax}{2}\rfloor+y(a\bmod 2)$。
  - $b\geq a$，答案是 $\min\{\lfloor\frac{ax}{2}\rfloor+y(a\bmod 2),ay\}$。
- 删光曲奇&#x20;
  - $a<b$，答案是 $\lfloor\frac{bx}{2}\rfloor+y(b\bmod 2)$。
  - $a\geq b$，答案是 $\min\{\lfloor\frac{bx}{2}\rfloor+y(b\bmod 2),by\}$。

最终的答案就是**删光糖果**和**删光曲奇**两个答案的较小值。

## $\tt Code$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int T;
	cin>>T;
	while(T--){
		int a,b,x,y;
		cin>>a>>b>>x>>y;
		int cnt1=0,cnt2=0;
		cnt1=min(x*(a/2)+y*(a%2),y*a);
		if(b<a){
			cnt1=x*(a/2)+y*(a%2);
		}
		cnt2=min(x*(b/2)+y*(b%2),y*b);
		if(a<b){
			cnt2=x*(b/2)+y*(b%2);
		}
		cout<<min(cnt1,cnt2)<<"\n";
	}
	return 0;
}
```

---

## 作者：aaalys (赞：0)

# P12146 糖果曲奇巧克力 题解

[题目传送门](https://www.luogu.com.cn/problem/P12146)

这题有很多细节，作者在赛时交了 3 遍才过。

## 思路

首先可以证明：删糖果的过程中用操作一删曲奇，肯定不优于一直删糖果。

删曲奇也同理，所以最优策略是只删一种物品。

先考虑删光糖果的最小花费，曲奇也同理，花费取一下最小就行。

设 $cost_i$ 为有 $i$ 个曲奇（或糖果），删完的最小花费。

由于操作一一次删两个，所以 $cost_i$ 要按照 $i$ 的奇偶性分类讨论。

假设 $i$ 为偶数，只有两种可能的最优策略：都用操作一，都用操作二。如果操作一二混着用，可以把操作一或两次操作二替换成更优的操作。最终答案 $cost_i= \min (iy,\frac{ix}{2})$。

如果 $i$ 为奇数，由于操作一一次删两个，所以必须最后使用一次操作二，前面的偶数个用上面的方法做。

综上所述，在 $a$ 为偶数时，$cost_a= \min (iy,\frac{ix}{2})$。在 $a$ 为偶数时，$cost_a=cost_{i-1} + y$。

最终答案就是 $\min(cost_a,cost_b)$。

## Code

最后就是愉快的代码时间。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a, b, x, y;							// 注意开long long
ll cost(ll i) {							// 求cost(i)
	if (i & 1) return cost(i - 1) + y;	// i为奇数
	return min(i * y, i * x / 2);		// i为偶数
}
void run() {
	cin >> a >> b >> x >> y;
	cout << min(cost(a), cost(b)) << endl;	// 输出答案
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int _;	// 多组数据
	cin >> _;
	while (_--) run();
	return 0;
}
```

---

## 作者：Jerry_zpl (赞：0)

难度：红。  
这题可以分三种情况：
- 我们可以求 $\min(a,b)$，再把 $\min(a,b)$ 每次减少 $1$，那么答案就是 $\min(a,b) \times y$。
- 还可以考虑把 $a$ 消掉，要使次数最少，当然是每次除以 $2$，当然，余数也要注意，所以答案是 $[\frac{a}{2} \times x+(a \bmod 2) \times y]$。注意，后面的 $a \bmod 2$ 是余数，只能一个一个的减少。
- 最后，还可以消 $b$，跟消 $a$ 同理，这里就不讲了。

最后取最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,x,y;
		cin>>a>>b>>x>>y;
		cout<<min(min(a,b)*y,min((a/2)*x+(a%2)*y,(b/2)*x+(b%2)*y))<<endl;
	}
	return 0;
}
```

---

