# Unfair Game

## 题目描述

Alice and Bob gathered in the evening to play an exciting game on a sequence of $ n $ integers, each integer of the sequence doesn't exceed $ 4 $ . The rules of the game are too complex to describe, so let's just describe the winning condition — Alice wins if the [bitwise XOR](http://tiny.cc/xor_wiki_eng) of all the numbers in the sequence is non-zero; otherwise, Bob wins.

The guys invited Eve to act as a judge. Initially, Alice and Bob play with $ n $ numbers. After one game, Eve removes one of the numbers from the sequence, then Alice and Bob play with $ n-1 $ numbers. Eve removes one number again, after which Alice and Bob play with $ n - 2 $ numbers. This continues until the sequence of numbers is empty.

Eve seems to think that in such a game, Alice almost always wins, so she wants Bob to win as many times as possible. Determine the maximum number of times Bob can win against Alice if Eve removes the numbers optimally.

## 说明/提示

In the first example, Bob wins when Eve has not removed any numbers yet.

In the second example, Bob wins if Eve removes one one and one three.

## 样例 #1

### 输入

```
5
1 1 1 0
1 0 1 2
2 2 2 0
3 3 2 0
0 9 9 9```

### 输出

```
1
1
3
3
12```

# 题解

## 作者：菲斯斯夫斯基 (赞：10)

## CF1955F Unfair Game 题解

upd：刚通过就发现答案的式子打错了。/kk

### 前言

讲个笑话，打 vp 时同学说要去吃饭了，然后突然发现自己打的大分讨假了，于是就在 $1$ 分钟内想出了这个神奇的做法，不明不白地 AC 了。

做的时候看着 $p_i\le200$ 傻了，为啥不开到 $10^{18}$？但我确信有 $\mathcal{O}(1)$ 回答每一次查询的做法，于是有了这篇题解。

### 思路

首先 $(1)_{10}=(001)_2$，$(2)_{10}=(010)_2$，$(3)_{10}=(011)_2$，$(4)_{10}=(100)_2$。显然 $4$ 是没有什么用的，只有在个数为偶数的时候异或和才能为 $0$，单独考虑贡献为 $\lfloor\frac{p_4}{2}\rfloor$ 就行了。同时也不难发现只有当 $p_1,p_2,p_3$ 同奇或同偶才符合条件。

于是开始分类讨论（以下默认三个数经过若干次操作后有合法状态）：

+ 三个数同奇或同偶，现在是合法状态。那么下一次合法状态为三个数同时减 $1$，需要操作 $3$ 次；或者其中一个数减 $2$，需要操作 $2$ 次。故后者更优。每个数减 $2$ 都能有一次贡献，答案不难计算为 $\lfloor\frac{p_1}{2}\rfloor+\lfloor\frac{p_2}{2}\rfloor+\lfloor\frac{p_3}{2}\rfloor$，注意同奇时要加上三个数最后都为 $1$ 的贡献。

+ 否则，有一个数的奇偶性与其它两个不同，不是合法状态。如果这个数不为 $0$，直接将这个数减 $1$ 即可，和上面相同；否则，要将另外两个数都减 $1$，又回到了上面的情况。

事实上，把上面讨论的式子整理一下，你会惊奇地发现其实都是一样的。当然你按照分类打一遍也行。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int a,b,c,d;
int main()
{
	cin>>t;
	while(t--)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%d\n",a/2+b/2+c/2+d/2+(a%2&&b%2&&c%2));
	}
	return 0;
}

```

---

## 作者：yangduan_ (赞：3)

# 思路
本题其实只要知道两个式子：
#### $a⨁a=0$
#### $a⨁0=a$
因此我们就可以先判断偶数出现的次数。


------------

# 注意
#### $1⨁2⨁3=0$
所以再加一个特判即可。


------------
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c,d,ans;
int main(){
	int i,j;
	cin>>t;
	while(t--){
		cin>>a>>b>>c>>d;
		ans=a/2+b/2+c/2+d/2;
		if((a%2==1)&&(b%2==1)&&(c%2==1)) ans++;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：yshpdyt (赞：3)

## 题意
$n=a_1+a_2+a_3+a_4$ 场比赛，初始有 $a_1$ 枚面值为 $1$ 的硬币，$a_2$ 枚面值为 $2$ 的硬币，$a_3$ 枚面值为 $3$ 的硬币，$a_4$ 枚面值为 $4$ 的硬币，每场比赛结束后移去一枚银币，直到没有硬币。如果所有银币面值异或起来为 $0$ 就获胜，你可以改变每场移去硬币的顺序，求最大的获胜场数。

## Sol
本题的关键在于凑偶数。

注意到面值为 $4$ 的银币比较特殊，其异或其他面额的硬币任意枚的结果都不为 $0$，所以我们可以先让 $4$ 的数量为偶数，把其他三类移空后再移去 $4$，这样会对答案贡献：

$$\left\lfloor \frac{a_4}{2}\right\rfloor$$

然后默认 $4$ 不存在，考虑其它三类，由于 $1\bigoplus2 \bigoplus 3=0$ ，如果 $a_1,a_2,a_3$ 均是奇数，那么可以算一次贡献。然后让他们全部变成偶数，也就是除了全奇数的情况需要加一次贡献，其余直接舍弃掉减一。接下来可以让三个位置都减一，三场比赛赢一场，或者让其中一个位置减二，两场比赛赢一场，显然后面的更优也更可持续发展，因为我们无法保证三个位置的数相同，总会有一个位置先减完，不如挨个减，然后就和 $4$ 的情况类似，所以答案为：

$$res=\left\lfloor \frac{a_1}{2}\right\rfloor+\left\lfloor \frac{a_2}{2}\right\rfloor+\left\lfloor \frac{a_3}{2}\right\rfloor+\left\lfloor \frac{a_4}{2}\right\rfloor+\left[a_1\bmod2+a_2\bmod2+a_3\bmod2==3\right]$$
## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 800005
#define endl "\n" 
#define fi fisrt
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll a[7];
void sol(){
    cin>>a[1]>>a[2]>>a[3]>>a[4];
    ll res=a[4]/2;
    res+=a[1]/2+a[2]/2+a[3]/2;
    if((a[1]&1)&&(a[2]&1)&&(a[3]&1))res++;
    cout<<res<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout); 
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();

    return 0;
}
```

---

## 作者：FiraCode (赞：2)

先找性质。

由于 $1,2,3$ 无论怎么 $\oplus$ 都凑不出来 $4$，所以要合法，必须让 $4$ 的个数为偶数。

然后又 $1 \oplus 2 = 3$，所以一个 $1$ 和一个 $2$ 可以和一个 $3$ 抵消，所以 $1,2,3$ 的个数奇偶性相同。

然后考虑预处理，由于 $1,2,3$ 的次数贡献跟 $4$ 无关，所以预处理的时候不用考虑 $4$。

那么设 $f_{i,j,k}$ 表示 $i$ 个 $1$，$j$ 个 $2$，$k$ 个 $3$ 的最大赢得次数，并且 $i, j, k$ 奇偶性相同，那么我们要么选出两个相同的数，然后异或抵消，要么选择 $1,2,3$ 并抵消，即 $f_{i,j,k} = \min\{ f_{i-2,j,k},f_{i,j-2,k}, f_{i,j,k-2},f_{i-1,j-1,k-1} \} + 1$。

然后询问的时候分别将 $a,b,c$ 变为同奇或同偶然后取最大即可。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
int T;
int f[210][210][210];
 
int main() {
	f[1][1][1] = 1;
	for (int i = 0; i <= 200; ++i) {
		for (int j = (i & 1); j <= 200; j += 2) {
			for(int k = (j & 1); k <= 200; k += 2) {
				if (i == 1 && j == 1 && k == 1) continue;
				if (i == 0 && j == 0 && k == 0) continue;
				if (i >= 2) f[i][j][k] = max(f[i][j][k], f[i - 2][j][k] + 1);
				if (j >= 2) f[i][j][k] = max(f[i][j][k], f[i][j - 2][k] + 1);
				if (k >= 2) f[i][j][k] = max(f[i][j][k], f[i][j][k - 2] + 1);
				if (i >= 1 && j >= 1 && k >= 1) f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - 1] + 1);
			}
		}
	}
 
	scanf("%d", &T);
	while (T--) {
		int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
 
		int ans = 0;
		if (a - (a & 1) >= 0 && b - (b & 1) >= 0 && c - (c & 1) >= 0) ans = f[a - (a & 1)][b - (b & 1)][c - (c & 1)];
		if (a - (!(a & 1)) >= 0 && b - (!(b & 1)) >= 0 && (c - (!(c & 1))) >= 0) ans = max(ans, f[a - (!(a & 1))][b - (!(b & 1))][(c - (!(c & 1)))]);
 
		printf("%d\n", d / 2 + ans);
	}
	return 0;
}
```

---

## 作者：Lee_OIer (赞：1)

学 OI 以来做过的最水的 $\color{#52C41A} 普及+/提高 $ 题。

(以前——打表 AC 水蓝，徒手硬算水紫)

---

### 题意
给定一个数字 $n$ 和 $n$ 个序列中数字 $1$，$2$，$3$，$4$ 的个数，每个序列以最佳方式（保证下文总和尽可能大）每次取出序列中的 $1$ 个数字直至该序列为空，每个序列求每次取出后所有数字的异或不为 $0$ 的次数总和。

---

### $\color{#F1C40F} 芝士 $

[OIwiki 异或](https://oiwiki.org/math/bit/)：数学符号表示 $\oplus$，只有两个对应位不同时才为 $1$。

$1 \oplus 1 = 0$

$1 \oplus 0 = 1$

以上是异或的基本性质，也体现了异或的自反性——

$a \oplus b = c$

$c \oplus b = a$

---

### 思路
由上述 $\color{#F1C40F} 芝士 $ 可知：$1 \oplus 2 = 3$

由于 $1$，$2$，$3$ 无法通过异或凑出 $4$，所以 $4$ 的个数必须为偶数；由于 $1$，$2$，$3$ 本身可以相互抵消，所以 $1$，$2$，$3$ 的奇偶性需要相同。

答案为 $\lfloor \displaystyle \frac{a_1}{2} \rfloor + \lfloor \displaystyle \frac{a_2}{2} \rfloor + \lfloor \displaystyle \frac{a_3}{2} \rfloor + \lfloor \displaystyle \frac{a_4}{2} \rfloor$，若 $1$，$2$，$3$ 同奇时需再加 $1$。

此题标签中虽有 $\colorbox{#2949B4}{\color{#FFFFFF}动态规划,dp}$，但由于此题数据范围较小，所以可以直接使用数学知识解题，在此就先不对本题 dp 做法进行讲解，如果数据范围较大还是需要使用 dp

---

### Code
```cpp
#include<iostream>
using namespace std;
int t, a, b, c, d, ans;
signed main() {
	cin >> t;
	while(t--) {
		cin >> a >> b >> c >> d;
		ans = (a / 2) + (b / 2) + (c / 2) + (d / 2) + (a % 2 == 1 && b % 2 == 1 && c % 2 == 1);
		cout << ans << '\n';
	}
}
```

---

## 作者：tanzexiaodezhonghao (赞：1)

## 思路
一开始看到 Alice 和 Bob 我还以为是博弈论，一看标签是动态规划和数学。经过思考，我发现这好像不需要动态规划吧，数组都不用。

这题主要是要凑偶数。经过几次尝试，你可以发现 $1$，$2$ 和 $3$ 无法异或得出 $4$，所以 $4$ 的个数一定是偶数，单独考虑 $\lfloor \dfrac{num_4}{2} \rfloor$ 的情况。然后你可以发现 $1 \oplus 2 \oplus 3 = 0$，我们把 $num_1$ 和 $num_2$ 以及 $num_3$ 都变成偶数，可以让他们都减一，贡献三，但其中一个减二，贡献二会更优，接下来可以推出答案为：$\lfloor \dfrac{num_1}{2} \rfloor + \lfloor \dfrac{num_2}{2} \rfloor + \lfloor \dfrac{num_3}{2} \rfloor + \lfloor \dfrac{num_4}{2} \rfloor$ 加上 $num_1$ 和 $num_2$ 以及 $num_3$ 中的奇数个数。
## 代码
公式有点绕，但写起来很简单。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,b,c,d;
int work(){
    return a/2+b/2+c/2+d/2+(a%2==1&&b%2==1&&c%2==1);
}
int main(){
    cin>>T;
    while(T--){cin>>a>>b>>c>>d;cout<<work()<<endl;}
    return 0;
}
```

---

