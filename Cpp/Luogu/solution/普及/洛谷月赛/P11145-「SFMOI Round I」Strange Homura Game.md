# 「SFMOI Round I」Strange Homura Game

## 题目背景

> 伝えたいコトバは たったひとつ / 想要传达的言语 唯有一个 \
> キミがいたから 強くなれた / 因有你在 我变坚强了 \
> 2 人ならどんな空も飛べるね / 只要两人一起就能任意飞翔 \
> キミをいつでも 信じてるから / 因为一直都 坚信着你 \
> ずっとずっと夢を見ていよう / 能同做此梦不复醒吧

## 题目描述


**本题和 B1 是不同的问题，请分别仔细阅读两题题面。**

**这是一道交互题。**


**提示**：我们在题目描述的最后提供了一份简要的、形式化描述的题面。

焰和圆在玩游戏。

焰在心中想了一个正整数 $m$，让圆猜出 $m$ 的值。当然，焰不会为难圆，所以 $\textcolor{red}{2}\le m\le 10^{17}$。焰不会作弊，也就是说，**焰不会悄悄更换想好的数字。**

圆可以问焰：对于**非负**整数 $x$，$x\bmod m$ 的值是多少。圆需要用最少的询问次数来猜出 $m$ 的值。（为了得到全部分数，最多只能使用 $2$ 次询问。）

焰一共和圆玩了 $T$ 次游戏。圆的数学很好，在 $\varepsilon $ 秒内就秒了这题，但是她在军训，于是她找来了你，来帮她猜出这 $T$ 次游戏的答案。



**形式化地**：有一个隐藏的正整数 $m\in [\textcolor{red}{2},10^{17}]$。每次询问给定**非负**整数 $x$，回答 $x\bmod m$。用最少的询问次数找出 $m$。共有 $T$ 组测试数据。$m$ 的数值在事先确定，不会根据询问变化，也就是说，**交互库是非适应性的**。

【实现细节】

对于每个测试点，输入一行一个正整数 $T$，表示游戏次数。

对于每组测试数据，你可以用以下的格式发起一次询问：

- $\texttt{? }x$：询问 $x\bmod m$ 的值。你需要保证 $x$ 是**非负**整数，且 $x \in \textcolor{red}{ [0,10^{18}]}$。
	
    从标准输入流读入一个整数表示答案。特别地，若整数是 $\texttt{-1}$，你的程序已经被判定为 $\texttt{Wrong Answer}$，此时你需要立刻终止程序。

你可以用以下的格式回答答案：

- $\texttt{! }m$：回答 $m$ 的值。

在发起询问后，需要刷新缓冲区，否则可能导致 TLE。

- 在 C++ 中，使用 `fflush(stdout)` 或 `cout.flush()`。 特别地，利用 `std::endl` 来换行也会刷新缓冲区。
- 在 Pascal 中，使用 `flush(output)`。  
- 在 Python 中，使用 `stdout.flush()`。  
- 对于其它语言，可自行查阅文档。


## 说明/提示


#### 数据范围

对于 $100\%$ 的数据，保证 $1\le T\le 100$，$m$ 为正整数，$\textcolor{red}{2}\le m\le 10^{17}$。

#### 评分方式

记单个测试点中，你的询问次数的最大值为 $Q$。则得分 $\mathrm{score}$ 如下所示：

$$
\begin{aligned}
\mathrm{score}=\begin{cases}
0, & Q\in [101,+\infty) \\
30, & Q\in [3,101) \\
50, & Q\in [0,3) \\
\end{cases}
\end{aligned}
$$

本题得分为所有测试点得分的最小值。

## 样例 #1

### 输入

```
1

0

1```

### 输出

```

? 5

? 1

! 5```

# 题解

## 作者：Register_int (赞：47)

随便问一个很大的 $x$，你可以得到 $y=x\bmod m$，那么我们有 $m\mid x-y$。

然后你发现 $(x-y-1)\bmod m=m-1$，做完了。

---

## 作者：what_can_I_do (赞：8)

[传送门](https://www.luogu.com.cn/problem/P11145)

首先我们先设第一次询问为 $a_1$，回答为 $c_1$，第二次的分别为 $a_2$，$c_2$。

那么显然，$a_1-c_1$ 就是 $m$ 的倍数，设其等于 $k\times m$，此时再减去一个 $c_1$ 就得到 $a_1-2\times c_1=k\times m-c_1$，于是就可以发现 $a_1-2\times c_1$ 对 $m$ 取模得到的余数是 $m-c_1$。

然后我们就可以令 $a_2=a_1-c_1$，$m$ 就等于 $c1+(m-c1)=c1+c2$。

但如果 $a_1$ 是 $m$ 的倍数的话 $c_1$ 就会为 $0$，此时就没法得到正确答案，所以我们就钦定 $a_1$ 为一个大于 $10^{17}$ 的大质数，这样就可以保证 $a_1$ 必定不为 $m$ 的倍数且大于 $m$。

实际上，在赛时没有必要真的去找一个质数，只需要随便找一个大奇数那么它在本题数据中就大概率不是 $m$ 的倍数，如果过不了就再换一个，反正这又不是 CF，不会 fst。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
ll a[3],c[3];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		a[1]=984327128473652833;
		printf("? %lld\n",a[1]),fflush(stdout);
		scanf("%lld",&c[1]);
		a[2]=a[1]-c[1]*2;
		printf("? %lld\n",a[2]),fflush(stdout);
		scanf("%lld",&c[2]);
		printf("! %lld\n",c[1]+c[2]),fflush(stdout);
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：5)

### 思路
推性质题。

考虑如何两步得出答案。

设第一次询问的数为 $a$，第二次询问的数为 $b$，第一次回答的数为 $x$，第二次回答的数为 $y$。

则：
$$
a=im+x
$$
$$
b=jm+y
$$
消去 $m$ 得：
$$
(j-i)\times(a-b)=(j-i)\times(x-y)
$$
所以 $a-b\equiv x-y\pmod m$。

所以一开始输出一个大于等于 $10^{17}$ 的整数 $a$，然后 $b=a-x-1$，答案为 $y+1$。

因为：
$$
a-(a-x-1)=x+1\equiv x-y\pmod m
$$
由于 $1<m$ 且 $y<m$，故 $x+1=m+x-y$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll A=2e17;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		ll x,y;
		cout<<"? "<<A<<endl;
		cin>>x;
		cout<<"? "<<A-x-1<<endl;
		cin>>y;
		cout<<"! "<<y+1<<endl;
	}
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：5)

随便问个 $x$，设拿到了 $r$，那么 $m$ 是 $x-r$ 的因数。于是再问一下 $x-r-1$，余数必然是 $m-1$，然后就结束了。

---

## 作者：include13_fAKe (赞：3)

第一次场切交互题，写篇题解纪念一下。

但考场不会这题，人菜，没救了。
## 做法

### 30 分

因为允许询问 $100$ 次，直接二分法即可。

时间复杂度 $O(T \log m)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

void solve(){
	int l=1,r=1e18;
	int mid=l+r>>1;
	while(l<r){
		cout<<"? "<<mid<<endl;
		int x;
		cin>>x;
		if(x==mid){
			l=mid+1;
		}
		else{
			r=mid;
		}
		mid=l+r>>1;
	}
	cout<<"! "<<l<<endl;
	return;
}
int T;
signed main(){
	cin>>T;
	while(T--)	solve();
	return 0;
}
```
### 正解

只能询问两次，已经够了。

设第一次询问的数为 $x_1$，回答的数为 $y_1$，第二次询问的数为 $x_2$，回答的数为 $y_2$。

当 $x_1$ 足够大时，$x_1-y_1\equiv 0\pmod m$，所以 $x_1-y_1-1\equiv m-1\pmod m$。

然后第二次询问 $x_1-y_1-1$，设得到的答案为 $m'$，有 $m'\equiv m-1\pmod m$ 且 $m'\le m$，故答案为 $m'+1$。

（代码变量命名有些混乱，请谅解）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int T;
signed main(){
	cin>>T;
	while(T--){
		int q=8;
		cout<<"? "<<q<<endl;
		int sum;
		cin>>sum;
		int sum2=q-sum-1;
		cout<<"? "<<sum2<<endl;
		int ans;
		cin>>ans;
		cout<<"! "<<ans+1<<endl;
	}
	return 0;
}
```

---

## 作者：fxwqctb (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11145)  
~~题号真臭~~

# 一、大致思路
这道题和前面那道 B1 差别挺大，所以本蒟蒻只 A 了这道 B2。  
首先有个数字 $m$，你需要用两次输出来猜 $m$。  
由于 $m\le10^{17},x\le4\times10^{18}$，输出的是 $x\bmod m$ 的值，我们假设 $x \bmod m=0$，那么显然 $(x-1)\bmod m=m-1$，只要将 $m-1$ 的值增加 $1$ 即可计算出 $m$。  
由于题目告诉你只能猜两次，我们就要在第一次让 $x \bmod m=0$，但这样肯定是不行的，但是 $x-(x\bmod m)$ 肯定是 $m$ 的倍数，这样第二次的 $x$ 肯定为第一次的 $x-(x\bmod m)-1$，这样输出的结果加一就是正确答案。  
我们让第一次的询问为 $x$ 的上限范围 $10^{18}$，再根据第一次的回答算出第二次的 $x$。

# 二、AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long n=0,k=0;
		cout<<"? 1000000000000000000"<<std::endl;//10^18
		cin>>n;
		cout<<"? "<<1000000000000000000-n-1<<std::endl;
		cin>>n;
		cout<<"! "<<n+1<<std::endl;
	}
	return 0;
}
```

---

## 作者：wxzzzz (赞：1)

### 思路

先简化一下式子：

$$\begin{aligned}
&\begin{cases}
x_1=am+b\\
x_2=cm+d
\end{cases}\\
&\begin{cases}
x_1\equiv b\pmod m\\
x_2\equiv d\pmod m
\end{cases}\\
&\begin{cases}
x_1-b\equiv 0\pmod m\\
x_2-d\equiv 0\pmod m
\end{cases}\\
&\begin{cases}
m\mid(x_1-b)\\
m\mid(x_2-d)
\end{cases}
\end{aligned}$$

相当于 $m\mid\gcd(x_1-b,x_2-d)$。

到这里还是无法直接确定 $m$，因为 $\gcd$ 可能有多个因数。

显然 $x_1,x_2$ 必须 $>10^{17}$ 否则可能 $\le m$ 浪费询问机会。

构造 $x_1=10^{17}+3$（大质数），令 $c_1=x_1\bmod m$。

构造 $x_2=2(x_1-c_1)-1$，令 $c_2=x_2\bmod m$。

$m=\gcd(x_1-c1,x_2-c2)$。

证明：数学直觉。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 10
using namespace std;
ll P1 = 100000000000000003, P2;
ll qpow(ll x, ll k, ll MOD) {
    ll ret = 1, base = x;
    while (k) {
        if (k & 1)
            ret = (ret * base) % MOD;
        base = (base * base) % MOD;
        k >>= 1;
    }
    return ret;
}
ll gcd(ll x, ll y) {
    while (x ^= y ^= x ^= y %= x);
    return y;
}
ll T, c1, c2;
int main() {
    scanf("%lld", &T);
    while (T--) {
        printf("? %lld\n", P1);
        fflush(stdout);
        scanf("%lld", &c1);
        P2 = (P1 - c1) * 2 - 1;
        printf("? %lld\n", P2);
        fflush(stdout);
        scanf("%lld", &c2);
        printf("! %lld\n", gcd(P1 - c1, P2 - c2));
        fflush(stdout);
    }
    return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

只能询问两次看似是限制，实际上是个重要的提示：既然机会这么少，那如果我还提问较小的数，那我将难以确定答案。

那么我在第一次提问一个很大的数 $x_{1}$，设得到的输入为 $y_{1}$。根据规则，有：

$$x_{1}\equiv y_{1}\pmod m$$

$$x_{1}-y_{1}-1\equiv m-1\pmod m$$

然后我们再提问 $x_{2}=x_{1}-y_{1}-1$，得到 $y_{2}$。

有

$$y_{2}\equiv x_{2}\equiv m-1\pmod m$$

$$m\equiv y_{2}+1\pmod m$$

$$m=y_{2}+1$$

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,x,y) for(ll i=x;i<=y;i++)

const ll MAX=1e18;
ll q;

int main(){
	cin>>q;
	
	while(q--){
		cout<<"? "<<MAX<<endl;
		ll res;
		cin>>res;
		cout<<"? "<<MAX-res-1<<endl;
		cin>>res;
		cout<<"! "<<res+1<<endl;
	}
}
```

---

## 作者：VelvetChords (赞：0)

# P11145 「SFMOI Round I」Strange Homura Game
## 0.前言
第一次做的交互题，还做对了，发题解以纪念。
## 1.思路
### 第一次询问

先选择一个很大的数 $x$（例如 $10^{18}$），并进行第一次询问，得到 $a=x \mod m$。

从这一结果，我们可以得出关系式：

$k\times m + a = x$ 

然后转化成：

$k\times m = x − a$

在这里，$k$ 是某个整数（表示 $m$ 在 $x$ 中可以整除的倍数）。

### 第二次询问
在第二次询问中，想要通过 $k\times m$ 来进一步确认 $m$ 的值，但直接询问 $k\times m$ 会得到 0，因为 $k\times m \mod m$ 肯定是 0。而我们询问 $k\times m−1$，则会得到：

$(k\times m−1) \mod m=m−1$

### 计算最终答案

第二次询问得到的回复是 $m−1$。

根据计算，原本的公式中 $m$ 的关系可以用以下方式表达：

$ans+1=(m−1)+1=m$

所以最终的答案即为 $ans+1$。

然后，这道题就这么结束了。

---

## 作者：lihl (赞：0)

很难不发现，我们询问 $x_1$ 需要充分大，回答的 $y_1$ 因为 $y_1=x_1\bmod m$ 显然 $m\mid x_1-y_1$。注意到其一定满足 $x_1-y_1 \equiv 0\pmod m$，显然 $x_1-y_1-1\equiv m-1\pmod m$。

第二次询问 $x_2=x_1-y_1-1$，根据推论，一定返回的是 $y_2=m-1$，故输出 $y_2+1$ 即可。

---

## 作者：cff_0102 (赞：0)

注意到题目最后的评分方式中，只允许最多询问两次，所以肯定要有技巧的询问。

假设第一次询问的数为 $x$，那么我们可以得到 $x\bmod m$，设其为 $a$，则满足 $km+a=x$，即 $km=x-a$。由此，我们可以得到一个 $m$ 的倍数。第二次询问肯定要以这个数为基础询问。

那么应该询问什么呢？如果询问计算得到的 $km$，回复必定是 $0$，好，白问了。但是不难发现如果询问 $km-1$，交互库必定会回复 $m-1$。

答案即为第二次询问的结果 $+1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;while(t--){
		long long x=1e18;
		cout<<"? "<<x<<endl;
		long long a;cin>>a;
		long long km=x-a;
		cout<<"? "<<km-1<<endl;
		long long ans;cin>>ans;
		cout<<"! "<<ans+1<<endl;
	} 
	return 0;
}
```

---

## 作者：NTT__int128 (赞：0)

# P11145 Strange Homura Game题解
首先，询问 $10^{18}\bmod m$ 的值，设为 $x$。因为 $10^{18}\equiv x\pmod m$，所以 $m|10^{18}-x$，发现此时 $10^{18}-x-1\equiv m-1\pmod m$，因此再询问 $10^{18}-x-1\bmod m$ 的值，设为 $y$，则答案为 $y+1$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,x,y;
signed main(){
	cin>>t;
	while(t--){
		cout<<"? 1000000000000000000"<<endl;
		cin>>x;
		if(x==-1)return 0;
		x=1000000000000000000-x;
		cout<<"? "<<x-1<<endl;
		cin>>y;
		if(y==-1)return 0;
		cout<<"! "<<y+1<<endl;
	}
	return 0;
}
```

---

## 作者：coderJerry (赞：0)

取个大于 $10^{17}$（$m$ 的最大值）的数 $d$ 进行一次询问，得到 $d \bmod m=a$。于是再询问一次 $(d-a-1)$，得到 $(d-a-1) \bmod= m-1$。然后把这次询问得到的结果加一输出就好了。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int d=1e18;
signed main(){
    int t,a,b;
    cin>>t;
    while(t--){
        cout<<"? "<<d<<endl;
        cin>>a;
        cout<<"? "<<d-a-1<<endl;
        cin>>b;
        cout<<"! "<<b+1<<endl;
    }
    return 0;
}
```

---

## 作者：lcfollower (赞：0)

首先询问一个大整数 $x_1$（$x\in \{(10^{17} ,10^{18}]\}$），得到 $x_1\bmod m = y$，则有 $m \mid \left(x_1  - y\right)$。

然后询问 $x_2 = x_1 - y - 1$，则有 $ x_2 \bmod m = m - 1$，将这个值加 $1$ 即可。

```cpp
# include <cstdio>
# include <iostream>

# define int long long

using namespace std;

int x = 1e18 ,y ,T;

signed main(){
std::cin >> T;
while(T --){
  x = 1e18;
  std::cout << "? " << x << std::endl;
  std::cin >> y;
  x -= y + 1;
  std::cout << "? " << x << std::endl;
  std::cin >> y;
  std::cout << "! " << y + 1 << std::endl;
}
  return 0;
} //B2
```

---

## 作者：lichenxi111 (赞：0)

一道很有趣的题目。

## 思路

首先需要问一个保证大于 $m$ 的数，遂选择 $x = 10 ^ {17} + 3$，对于 $x$ $\bmod$ $m$ 的值 $a$，设 $y = x - a$，发现 $y$ 一定是 $m$ 的倍数。

又因为 $m \ge 2$，所以 $y - 1$ 一定不是 $m$ 的倍数，遂 $(y - 1)$ $\bmod$ $m$，所得值 $b$ 就一定是 $m - 1$，$b + 1$ 即为答案。

有点懵？看下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ali224dw.png)

其中 $k$ 为整数，也就是说，可以把 $(k-1)m$ 以前的数都忽略掉，即假设 $k = 1$，只观察最后一个长度为 $m$ 的区间，$y - 1$ 肯定不在 $y$ 或 $(k - 1)m$ 的点上，所以区间长 $m = b + 1$。

哦，对了，忘了一个重要的点。

## 交互

你先按照他要求的格式，把你想要询问的数告诉他。

在此题，例如 ```cout << "?" << " " << 114514```

在交互库中，有一个数 $m$，例如 $m = 114515$，交互库就会返回 $114514$ $\bmod$ $114515$，即返回 $114514$，不会有人理解为会返回那个算式吧？返回的数用 ```cin``` 之类的读入即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve()
{
	int a,b;
	int x = 100000000000000003;
	cout << "? " << x << endl;
	cin >> a;
	if(a == -1)
	{
		exit(0);
	}
	x -= a;
	cout << "? " << x - 1 << endl;
	cin >> b;
	if(b == -1)
	{
		exit(0);
	}
	cout << "! " << b + 1 << endl;
}
signed main()
{
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}
```

---

