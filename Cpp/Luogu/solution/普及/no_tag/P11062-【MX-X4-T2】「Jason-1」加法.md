# 【MX-X4-T2】「Jason-1」加法

## 题目背景

原题链接：<https://oier.team/problems/X4C>。

## 题目描述

给定两个整数 $a, b$（可能为负），你可以进行任意多次操作（也可以不操作），每次操作你需要在如下两种形式中进行选择：

- 操作 1：将 $a$ 赋值为 $a$ 与 $b$ 的和，即 $a \gets a + b$。
- 操作 2：将 $b$ 赋值为 $a$ 与 $b$ 的和，即 $b \gets a + b$。

你的目标是最小化 $a$ 与 $b$ 的差的绝对值 $\lvert a-b \rvert$，请输出最小值。

## 说明/提示

**【样例解释 #1】**

对于第 1 组数据，一种可行的操作方案是：不进行任何操作，$\lvert a-b \rvert=0$。

对于第 2 组数据，一种可行的操作方案是：先使用操作 2，$b$ 被赋值为 $10$；再使用操作 1，$a$ 被赋值为 $13$，此时 $\lvert a-b \rvert=3$，可以证明这是能够达到的最小值。

对于第 3 组数据，一种可行的操作方案是：连续使用 $5$ 次操作 1，$a$ 依次被赋值为 $-3,-2,-1,0,1$，此时 $a$ 和 $b$ 相等，$\lvert a-b \rvert=0$。

对于第 4 组数据，一种可行的操作方案是：不进行任何操作，此时 $\lvert a-b \rvert=3$。

对于第 5 组数据，一种可行的操作方案是：使用操作 2，$b$ 被赋值为 $4$，此时 $\lvert a-b \rvert=0$。

**【样例解释 #2】**

对该样例中的两组数据，均可先使用 $1$ 次操作 2，再使用 $3$ 次操作 1，使得差的绝对值为 $0$。

**【数据范围】**

| 测试点编号 | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | A | $27$ |
| 2 | B | $31$ |
| 3 | 无 | $42$ |

- 特殊性质 A：保证 $\lvert a \rvert, \lvert b \rvert \le 10$。
- 特殊性质 B：保证 $a,b \ge 1$。

对于 $100\%$ 的数据，$1 \le T \le 10^5$，$\lvert a \rvert, \lvert b \rvert \le 10^9$。


## 样例 #1

### 输入

```
5
1 1
3 7
-4 1
-5 -8
4 0
```

### 输出

```
0
3
0
3
0
```

## 样例 #2

### 输入

```
2
-6 9
34 -51
```

### 输出

```
0
0
```

# 题解

## 作者：细数繁星 (赞：12)

分讨，比赛的时候想了 20min，感觉黄虚高？

## $\rm 27pts$

$|a|,|b|\le10$。暴力可解。

## $\rm 31pts$

$a,b$ 为正整数。有规律：答案为 $\min\{a,b,|a-b|\}$，这是为什么？

当我们将 $a$ 赋为 $a+b$，答案为 $a$。当我们将 $b$ 赋为 $a+b$，答案为 $b$。显然，差值是轮回的，但单方面不断累加只会离答案越来越远。

那不操作呢？就是 $|a-b|$。

```cpp
cout << min({abs(a), abs(b), abs(a - b)}) << endl;
```

## $\rm 100pts$

### $a,b\ge 1$

上文已提。

### $a,b\le0$

和两数大于 $0$ 的情况几乎一样。

为什么这么说？因为结果终究为正数，两负数相减的绝对值等于两负数的绝对值相减的绝对值。

至于累加，因为是负数，在不考虑正负情况下与情况一一样。

只要注意加绝对值。

### $a\times b<0$

**这个就很神奇了：对于此情况，所有结果都为 $0$.**

其实相当于只要能找到一个数 $k$，保证 $a\mid k$ 且 $b\mid k$，那么就可以归 $0$。因为所有的累加操作最终会使它们的结果一样（补充：rui_er 大佬的结论，此情况下等同于使用辗转相除法，上述提出的也就是最小公倍数，最小公倍数与最大公因数有关，因此产生该结论）。

此时将一个数赋为 $a+b$，与将一个数赋为 $|a-b|$ 效果相同，所以有这个结论。

## 满分代码

```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void solve() {
  ll a, b;
  cin >> a >> b;
  if (a < b) swap(a, b);
  if (a * b >= 0) cout << min({abs(a), abs(b), abs(a - b)}) << endl;
  else {
    cout << 0 << endl;
  }
} 


main() {
	int t; cin >> t; while (t--) solve();
	return 0;
}

```

[AC 记录。](https://www.luogu.com.cn/record/177187632)

---

## 作者：qcf2010 (赞：8)

## 题意
给出整数 $a$ 和 $b$，进行若干次 `a+=b` 或 `b+=a` 的操作，使得 $\lvert a-b \rvert$ 最小。

## 思路
为了讨论方便，我们可以先令 $a \le b$。接下来，分几种情况讨论。

### 当 $a$ 和 $b$ 均为正数时
当不做任何操作时，$\lvert a-b \rvert = b - a$；若进行一次操作 1，则 $\lvert a-b \rvert =\lvert (a+b) - b \rvert= a$；若进行一次操作 2，则 $\lvert a-b \rvert = \lvert a - (a+b) \rvert = b$。很容易发现，若再进行几次操作，$\lvert a-b \rvert$ 只会变得越来越大，又因为 $a \le b$，所以 $\lvert a-b \rvert$ 的最小值就是 $\min(b-a,a)$。

### 当 $a$ 和 $b$ 均为负数时
论述方法同上，会发现 $\lvert a-b \rvert = \min(b-a,\lvert b \rvert)$。

### 当 $a$ 和 $b$ 其中一个为 $0$ 时
若 $a=0$，则进行操作 1；若 $b=0$，则进行操作 2。易得此时 $\lvert a-b \rvert = 0$。

### 当 $a$ 为负数，$b$ 为正数时
这是最难讨论的情况，但存在一种操作方法可以使 $\lvert a-b \rvert = 0$，如下：

1. 比较 $a$ 与 $b$ 的绝对值。
2. 若 $a$ 的绝对值更大，则不断进行操作 1，当且仅当 $a < 0$ 时。
3. 若 $b$ 的绝对值更大，不断进行操作 2，当且仅当 $b > 0$ 时。
4. 若 $\lvert a \rvert \ne \lvert b \rvert$，则跳回至第 1 点。
5. 如上述若干次操作后，必有 $\lvert a \rvert = \lvert b \rvert$，进行两次操作 1 后，$\lvert a-b \rvert = 0$。求得最终结果。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, a, b, c;
int main() {
	cin>>t;
	while(t--){
		cin>>a>>b;
		if(a>b) swap(a,b);
		if(a==b) cout<<"0\n";
		else if(a<0&&b==0||a==0&&0<b) cout<<"0\n";
		else if(a>0&&b>0) cout<<min(a,b-a)<<"\n";
		else if(a<0&&b<0) cout<<min(abs(b),b-a)<<"\n";
		else cout<<"0\n";
	}
	return 0;
}
```
希望能给大家一些帮助。

---

## 作者：K_J_M (赞：8)

## 题目描述
给定两个整数 $a, b$（可能为负），你可以进行任意多次操作（也可以不操作），每次操作你需要在如下两种形式中进行选择：

- 操作 1：将 $a$ 赋值为 $a$ 与 $b$ 的和，即 $a \gets a + b$。
- 操作 2：将 $b$ 赋值为 $a$ 与 $b$ 的和，即 $b \gets a + b$。

你的目标是最小化 $a$ 与 $b$ 的差的绝对值 $\lvert a-b \rvert$，请输出最小值。
## 分类讨论
当 $a,b≥1$ 时，显然答案为
$$\begin{cases}
\min(a-b,b) & a>b\\
\min(b-a,a) & \text{otherwise}
\end{cases}
$$
当 $[a=0]+[b=0]>0$ 时，答案为 $0$。\
当 $a,b<0$ 时，如果执行任意操作，可以证明答案永远不会更小，此时答案为 $\min (|a-b|,\min(-a,-b))$。\
当 $a\times b<0$ 时，手模几组样例会发现每次让绝对值大的加上绝对值小的，其过程类似于辗转相除法，最后必然得到 $0$。\
[Ac Code](https://www.luogu.com.cn/paste/cyvvgxvm)

---

## 作者：wenhaoran11 (赞：7)

本蒟蒻的第一篇题解，望通过qwq...

---

正文开始：考虑分类讨论

1. $a$ 与 $b$ 都大于零或小于零，不论进行操作一还是操作二，其中的一个值都会越来越大，导致差值变大，所以一种情况为 `abs(a[i]-b[i])`，然后还有一种情况，在此写一下：对于第一种情况：`a=a+b,b=b` 则差值为 $b$ 同理对于第二种情况差值为 $a$ 所以主要代码为 `cout<<min(abs(a[i]),min(abs(b[i]),abs(a[i]-b[i])));`。

2. 接下来就是 $a$ 和 $b$ 异号的情况了（如 $a=1,b=-8$），如果在正数上相加正数会变小 ，如果在负数上相加负数会变大，双方的差值会越来越小，直到变成 $0$。

接下来代码就非常好写了，$O(n)$ 的复杂度就能过。

正文结束

---

接下来介绍些函数

`abs()`：求绝对值

`min()`：求最小值

---

```cpp

代码copy不上

``````

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1000005];
int b[1000005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		if((a[i]>0&&b[i]>0)||(a[i]<0&&b[i]<0)){
			cout<<min(abs(a[i]),min(abs(b[i]),abs(a[i]-b[i])))<<endl;
		}else if(a==0||b==0){
			cout<<0<<endl;
		}else{
			cout<<0<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Charged_Charge (赞：2)

# 洛谷 P11062
## 题目大意：
总共 $t$ 组数据，每组两个数 $a$ 与 $b$，可以进行若干次操作，操作分为两个类型。操作一：使 $a$ 变为 $a+b$；操作二：使 $b$ 变为 $a+b$。输出若干次操作后 $a$ 与 $b$ 的差的绝对值最小是多少。
## 解题思路：
1. 如果两个数异号，那么答案就是 $0$，因为可以通过若干次操作把 $a$ 和 $b$ 变成相等的两个数。
- 当 $\left|a\right|\le\left|b\right|$ 时，进行操作二，直到 $\left|a\right|\ge\left|b\right|$。
- 当 $\left|a\right|\ge\left|b\right|$ 时，进行操作一，直到 $\left|a\right|\le\left|b\right|$。
- 当 $\left|a\right|=\left|b\right|$ 时结束操作。
2. 如果两个数同号，那么答案就是 $\min(\min(\left|a\right|,\left|-b\right|),\left|a-b\right|)$。因为在同号的情况下进行过多的操作只会增加两数的差，所以答案只会是不操作或操作一次的情况，分别为以下三种。最后对这三种情况的答案取最小值即可。
- $\left|\left(a+b\right)-b\right|=\left|a\right|$
- $\left|a-\left(a+b\right)\right|=\left|-b\right|$
- $\left|a-b\right|$
# AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main() {
	cin >> t;

	while (t--) {
		int a, b;
		cin >> a >> b;

		if ((a <= 0 && b >= 0) || (b <= 0 && a >= 0)) {
			cout << 0 << endl;
			continue;
		}

		cout << min(min(abs(a), abs(-b)), abs(a - b)) << endl;
	}

	return 0;
}
```

---

## 作者：nbhs23a28 (赞：2)

## 题目分析
本题是个不折不扣的思维题。在获得灵感之前，让我们先枚举一些情况找找规律。不妨用 $(x,y)$ 形式表示若干次操作后的 $a$ 和 $b$。

则一次操作后可得 $(a,a+b)$ 及 $(b,a+b)$，此时差的绝对值为 $a$ 或 $b$；二次操作后可得 $(a,2a+b)$，$(2a+b,a+b)$，$(b,a+2b)$ 及 $(a+2b,a+b)$，差的绝对值依次为 $a+b$，$a$，$a+b$ 及 $b$；……

## 解题思路
以此类推，我们可以发现，除不进行操作时差的绝对值为 $\lvert a-b \rvert$，其余情况下均可表示为 $\lvert k_1a+k_2b \rvert (k_1,k_2 \in \mathbb{N}$ 且 $k_1,k_2$ 不同时为 $0)$。当 $a$，$b$ 异号或有一数为 $0$ 时，易知此时所求最小值为 $0$（总能构造出一组合法的 $k_1$，$k_2$ 使其值为 $0$），而当二者同号时则要使 $k_1$，$k_2$ 尽可能小，不难发现我们只需取 $\min (\lvert a \rvert,\lvert b \rvert,\lvert a-b \rvert)$ 即可。

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{int t;cin>>t;   
 while(t--)
 {long long a,b;
  cin>>a>>b;
  if(a==0||b==0)
  cout<<"0\n";
  else if(a*b>0)//判断是否同号
  cout<<min(abs(a-b),min(abs(a),abs(b)))<<'\n';
  else
  cout<<"0\n";
 }
}
```

---

## 作者：abc1234shi (赞：1)

一道结论题，分两种情况讨论。

第一种情况，$a$ 和 $b$ 同为非负数或同为负数（同号）：其实很简单，只要先比较 $a$ 与 $b$ 哪个绝对值更小，再将小的绝对值与 $a$ 与 $b$ 差的绝对值进行比较，小者即是答案。

为什么呢？因为若该项与另一项相加，其和与相加的那一项的差值为该项，（相当于 $a+b−b=a$ 这样）因为后来变化的值必定比前面两项大，（注意：在变化前 $a−b$ 的值也可能为差值的最小值）故最小差为 $\min\{a,b,|a-b|\}$。

第二种情况，$a$ 和 $b$ 一正一负（不同号）：这个比较难想，直接模拟会超时。

由第一点推理可得，差值为 $|n×a+m×b|$，其中 $n,m≥0$。则必定可以找出 $n,m≥0$，使得 $n×a+m×b=0$ 成立，（例如：若 $a<0，b>0$ ，设 $n=b，m=−a$ 则 $b×a+(−a)×b=0$ 可成立）故最小差值为 $0$。

我们再引用 @rui_er 的话进行解释，可能比较好理解一些：$(a,b)$ 执行欧几里得算法可以将一个变为 $0$，另一个变为 $\gcd(a,b)$（忽略正负号）。再将 $0$ 变成两个数之和即可，所以我们在不同号是直接输出 $0$ 即可。

时间复杂度 $O(t)$，完全可过。

本题重点部分仅需一个判断语句即可解决，难点在找结论。
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
signed main () {
	cin >> t;
	
	while (t--) {
		int a, b;
		cin >> a >> b;
		if ((a >= 0 && b >= 0) || (a < 0 && b < 0)) {
			int s = min(abs(a), abs(b));
			cout << min(abs(a - b), s) << endl;
		}
    else {
		cout<<0<<endl;
		}
	}
	 return 0;
}
```

---

## 作者：Didncan_yu (赞：1)

本题可分为以下两种情况：

### $a \times b > 0$

对于所给的两种操作，本质上 $a \gets a + b$ 会使 $\lvert a - b \rvert$ 变为操作前的 $\lvert a \rvert$，$b \gets a + b$ 会使 $\lvert a - b \rvert$ 变为操作前的 $\lvert b \rvert$。而当 $a,b$ 同为正或同为负时，绝对值是单调递增的。

所以我们至多只会进行一次操作，对于原 $\lvert a \rvert,\lvert b \rvert,\lvert a - b \rvert$ 取最小值即可。

### $a \times b \le 0$

当 $a,b$ 中有一个 $0$ 时，显而易见得答案为 $0$。

当 $a,b$ 为一正一负时，我们对于绝对值较大的数，将其赋值为 $a + b$，进行完操作后，可得操作完后 $a,b$ 要么一正一负，要么其中一个为 $0$，对于前者继续重复上述操作，通过这种类似辗转相除法的操作，最后一定会出现 $0$。

```cpp
void solve(){
	cin>>a>>b;
	if(1ll*a*b>0)cout<<min({abs(a),abs(b),abs(a-b)})<<endl;
	else cout<<"0\n";
}
```

---

## 作者：ylzpl (赞：0)

这题有点那啥。  
解题思路：首先我们可以考虑将 $a=a+b,b=a+b$。那么，现在有两个数 $a,b$。如果我将 $a=a+b$，那么 $|a-b|$ 就相当于 $|a+b-b|$，也就是 $|a|$。如果我将 $b=a+b$，那么 $|a-b|$ 就是 $|a-a+b|$，也就是 $|b|$。那么，除此之外，我们还可以不变，答案就是 $|a-b|$。所以，我们的答案就是上述过程结果的最小值。那么，这种思路还是有问题滴。比如我取任意一个正数和一个负数，就可以把这种情况给卡掉。所以，我们对于异号的两个数，需要特殊处理。因为求 $|a-b|$ 的最小值，所以我们不妨设 $a=\min(a,b),b=\max(a,b)$，则有 $a=a+b$ 这个操作和 $b=b+a$ 这个操作。为啥有 $b=b+a$ 这个操作捏，因为当 $b$ 很大时，比如 $-114514,1000000$ 这种数据，你加上 $b$ 不就废了，永远不会使值变小。所以，我们需要干的就是在 $a+b>b$ 的情况下将 $b$ 减小，在 $a+b<b$ 的情况下将 $a$ 增大，最后 $|a-b|$ 的值终将是 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
signed main(){
	int T;
	cin>>T;
	while(T--){
		int a,b;
		cin>>a>>b;
		if(a<0&&b>0){
			cout<<0<<"\n"; 
		}
		if(a>0&&b<0){
			cout<<0<<"\n";
		}
		else{
			cout<<min(abs(a),min(abs(b),abs(a-b)))<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：LG086 (赞：0)

分情况讨论 $a,b$ 同号和 $a,b$ 异号时的答案。

当 $a,b$ 同号时，发现 $|a-b|$ 的最小值是 $\min(\min(|a|,|b|),|a-b|)$。  
因为每次操作最好的选择就是选取 $a,b$ 中较小的数加上较大的数。  
默认初始时 $a\le b$，那么此时 $|a-b|=|(a+b)-b|=|a|$，且操作次数越多答案越大。所以操作次数应不超过一次。所以答案就是 $\min(\min(|a|,|b|),|a-b|)$。

当 $a,b$ 异号时，答案为 $0$。  
假设 $a\lt b$。
重复执行如下操作直到 $|a|=|b|$：
- 若 $|a|\lt|b|$，那么进行若干次操作二，直到 $|a|\ge|b|$。    
- 若 $|a|\gt|b|$，那么进行若干次操作一，直到 $|a|\le|b|$。

若此时 $|a|=|b|$ 那么重复执行两次相同的操作即可使 $a=b$。

这很容易让我们联想到更相减损法。  
以较大的数减较小的数，把所得的差与较小的数比较，再以大数减小数，直到所得的较小的数和差相等为止。  
由于 $a=|a|,b=|b|$，所以无视符号，上述对 $a$ 和 $b$ 操作就是在求 $\gcd(a,b)$。求得最大公约数时 $|a|=|b|$，所以重复执行两次相同的操作即可使 $a=b$。  
所以最终答案 $|a-b|=0$。

---
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll n;
ll a,b;
int main(){
    cin>>n;
    while(n--){
        cin>>a>>b;
        if((a<0&&b>0)||(a>0&&b<0))
        cout<<0<<endl;
        else
        cout<<min(min(abs(a),abs(b)),abs(a-b))<<endl;
    }
}
```

---

