# Laura and Operations

## 题目描述

Laura is a girl who does not like combinatorics. Nemanja will try to convince her otherwise.

Nemanja wrote some digits on the board. All of them are either $ 1 $ , $ 2 $ , or $ 3 $ . The number of digits $ 1 $ is $ a $ . The number of digits $ 2 $ is $ b $ and the number of digits $ 3 $ is $ c $ . He told Laura that in one operation she can do the following:

- Select two different digits and erase them from the board. After that, write the digit ( $ 1 $ , $ 2 $ , or $ 3 $ ) different from both erased digits.

For example, let the digits be $ 1 $ , $ 1 $ , $ 1 $ , $ 2 $ , $ 3 $ , $ 3 $ . She can choose digits $ 1 $ and $ 3 $ and erase them. Then the board will look like this $ 1 $ , $ 1 $ , $ 2 $ , $ 3 $ . After that, she has to write another digit $ 2 $ , so at the end of the operation, the board will look like $ 1 $ , $ 1 $ , $ 2 $ , $ 3 $ , $ 2 $ .

Nemanja asked her whether it was possible for only digits of one type to remain written on the board after some operations. If so, which digits can they be?

Laura was unable to solve this problem and asked you for help. As an award for helping her, she will convince Nemanja to give you some points.

## 说明/提示

In the first test case, Laura can remove digits $ 2 $ and $ 3 $ and write digit $ 1 $ . After that, the board will have $ 2 $ digits $ 1 $ . She can make it have only digits $ 2 $ or $ 3 $ left by performing a similar operation.

In the second test case, she can remove digits $ 1 $ and $ 3 $ and write a digit $ 2 $ . After performing that operation $ 2 $ times, the board will have only digits $ 2 $ left. It can be proven that there is no way to have only digits $ 1 $ or only digits $ 3 $ left.

In the third test case, there is a sequence of operations that leaves only digits $ 1 $ on the board. It can be proven that there is no way to have only digits $ 2 $ or only digits $ 3 $ left.

## 样例 #1

### 输入

```
3
1 1 1
2 3 2
82 47 59```

### 输出

```
1 1 1
0 1 0
1 0 0```

# 题解

## 作者：wwwidk1234 (赞：3)

[我的博客](https://wwwidk1234.github.io/)
## 题意
黑板上有 $a$ 个 $1$，$b$ 个 $2$，$c$ 个 $3$，要求操作后只留下一种数字。

以黑板上只保留 $1$ 为例，假设 $b>c$，我们可以通过重复消除 $2,3$，添加 $1$ 来使黑板上只剩下 $1,2$，然后重复执行以下步骤消除剩余的 $2$：
- 消除 $1,2$ 并写下 $3$。
- 消除 $2,3$ 并写下 $1$。

以数列 $\left\{1,2,2,2,2,3,3\right\}$ 为例，可以用以下操作来使数列中只有 $1$（用蓝色表示添加，用灰色表示删除）：
1. $\left\{1,{\color{blue}{1,1}},2,2,{\color{#C0C0C0}{2,2,3,3}}\right\}$
2. $\left\{1,1,{\color{#C0C0C0}1,2},2,{\color{blue}3}\right\}$
3. $\left\{1,1,{\color{blue}1},{\color{#C0C0C0}2,3}\right\}$

此时数列里只有 $1$，问题已解决。

## 代码
```python
T=(int)(input())
for test in range(T):
    s=input().split()
    a=int(s[0])
    b=int(s[1])
    c=int(s[2])
    print(0 if (b+c)%2 else 1,
          0 if (a+c)%2 else 1,
          0 if (a+b)%2 else 1)
```

---

## 作者：__Floze3__ (赞：2)

## 思路

略微思考不难得到，三个数字的数量之差的奇偶性是不会变的。因为一个数的数量减少了 $1$，另一个数无论是增加 $1$ 或是减少 $1$，两者的差要么不变，要么增加 / 减少 $2$，对奇偶性无影响。  
同时，如果另外两个数的数量变为 $0$，它们数目的差一定是 $0$。那么，我们只需要判断另外两个数的奇偶性是否相同即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int T, a, b, c;

int main(){
    cin >> T;
    while (T--){
        cin >> a >> b >> c;
        cout << (b % 2 == c % 2) << ' ' << (a % 2 == c % 2) << ' ' << (a % 2 == b % 2) << '\n';
    }
    return 0;
}
```

---

## 作者：feiji_code (赞：1)

# 题意：
有 $a$ 个 $1$，$b$ 个 $2$，$c$ 个 $3$。

可以删除 $2$ 个不同的数字再加上 $1$ 个与删除的不同的数字，进行若干次操作，能否剩下一种数字。

## 思路：
拿 $1$ 来举例，如果 $2$、$3$ 的数量和是偶数，那么可以一直删除 $2$ 和 $3$，就能只留下 $1$ 了。

例如：```1、2、3、3、3```

第一次操作改为 ```1、1、3、3```（$2$ 和 $3$ 得 $1$）

第二次操作改为 ```1、2、3```（$1$ 和 $3$ 得 $2$）

第三次操作改为 ```1、1```（$2$ 和 $3$ 得 $1$）

这样，就只剩下 $1$ 了，其他数同理。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//主函数↓
int main(){
	ios::sync_with_stdio(0),cin.tie(NULL),cout.tie(NULL);//关闭输入输出流的同步
    int t;
    cin>>t;
	for(int i=1,a,b,c;i<=t;++i){
		cin>>a>>b>>c;
		if((b+c)%2==0) cout<<1<<' ';//判断奇偶性
		else cout<<0<<' ';
		if((a+c)%2==0) cout<<1<<' ';
		else cout<<0<<' ';
		if((a+b)%2==0) cout<<1<<'\n';
		else cout<<0<<'\n';
	}
	return 0;
}

```


---

## 作者：IOI_AK_TLR (赞：1)

# 题意

你有 $a$ 个 1、$b$ 个 2 和 $c$ 个 3。

每次操作你可以删除两个不同的数字，并把与这两个数字都不同的那一个数字添加进来，问若干次操作后可不可能**只剩下** 1 或者 2 或者 3。


------------

# 思路

显然，当某个数字的数量改变的时候，另外的两个数字的数量也会随之改变，“改变”要么是数量加一，要么是数量减一，从而可以发现如果一开始两个数的奇偶性不同，则无论怎么操作都不会变得相同，反之亦然。

而如果最后只剩下同一种数字，那么另外两个数字的数量就都是 $0$ ，也就是它们的奇偶性相同，如果一开始它们的奇偶性不同，则无法把它们的数量都归零，因此直接检验另外两个数字的奇偶性是否相同即可。


------------

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,a,b,c; 
int ta,tb,tc;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>c;
		ta=a,tb=b,tc=c;
		if(tb<tc)
			swap(tb,tc);
		if(tb%2!=tc%2)
			cout<<"0 ";
		else
			cout<<"1 ";
		ta=b,tb=a,tc=c;
		if(tb<tc)
			swap(tb,tc);
		if(tb%2!=tc%2)
			cout<<"0 ";
		else
			cout<<"1 ";
		ta=c,tb=a,tc=b;
		if(tb<tc)
			swap(tb,tc);
		if(tb%2!=tc%2)
			cout<<"0\n";
		else
			cout<<"1\n";
	}
	return 0;
}

```


---

## 作者：_txb_ (赞：0)

[CF1900B Laura and Operations](https://www.luogu.com.cn/problem/CF1900B)

## 题意
可以删除 $2$ 个不同的数字再加上 $1$ 个与删除的不同的数字，进行若干次操作，能否剩下一种数字。

## 思路
只有可能有三种选法，我们来看一看 $1$ 的，如果其他两数的数量和是偶数，就可以一直把其他两数给减掉，所以可以留下 $1$，但不是偶数就不可以全部消除，就算消到最少也会留下一个非 $1$ 的数。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
	while(t--)
	{
		int a,b,c;
		cin>>a>>b>>c;
		if((b+c)%2==0) cout<<1<<" ";
		else cout<<0<<" ";
		if((a+c)%2==0) cout<<1<<" ";
		else cout<<0<<" ";
		if((a+b)%2==0) cout<<1<<endl;
		else cout<<0<<endl;
	}
	return 0;
}
```


---

## 作者：FlyPancake (赞：0)

# [CF 1900B Laura and Operations](https://www.luogu.com.cn/problem/CF1900B) 题解

小清新结论题。

## Ideas

假设有 $a$ 个 $1$，$b$ 个 $2$，$c$ 个 $3$：

讨论剩 $1$ 的情况，$2$ 与 $3$ 同理：

若 $b$ 与 $c$ 相等，那么只要同时不断擦除 1 个 $2$ 与 1 个 $3$，即可符合条件。

若 $b$ 大于 $c$（$b$ 小于 $c$ 同理），先同时擦除 $c$ 个 $2$ 和 $c$ 个 $3$，那么有：

$$\displaystyle a\leftarrow a+c,b\leftarrow b-c,c\leftarrow 0.$$

如果现在的 $b$ 为偶数，那么可重复经过以下步骤使得剩下数字均为 $1$：

- 擦除 $1$ 和 $2$，变为 $3$。
- 擦除 $2$ 和 $3$，变为 $1$。

如果现在的 $b$ 为奇数，那么无法重复经过以上步骤或其它步骤（可考虑 $b$ 为 3 的特殊情况）使得剩下数字均为 $1$。

所以只要判断一开始的 $b-c$ 的奇偶性即可。

## Code

```
#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--){
		int a, b, c; cin>>a>>b>>c;
		cout<<((b-c)%2==0)<<" "<<((a-c)%2==0)<<" "<<((a-b)%2==0)<<"\n";
	}
	return 0;
}
```


---

## 作者：__HHX__ (赞：0)

# 思路
根据题意可得一次操作分别可使 $a,b,c$ 变为：
1. 操作一，若 $b \geq 0,c \geq 0$ 则可以使 $a \Leftarrow a + 1,b \Leftarrow b - 1,c \Leftarrow c - 1$。
2. 操作二，若 $a \geq 0,c \geq 0$ 则可以使 $a \Leftarrow a - 1,b \Leftarrow b + 1,c \Leftarrow c - 1$。
3. 操作三，若 $a \geq 0,b \geq 0$ 则可以使 $a \Leftarrow a - 1,b \Leftarrow b - 1,c \Leftarrow c + 1$。

若 $b + c = k$，代入所有操作：
1. 操作一，$(b - 1) + (c - 1) = b - c - 2 = k - 2$。
2. 操作二，$(b - 1) + (c + 1) = b - c = k$。
2. 操作二，$(b + 1) + (c - 1) = b - c = k$。

因为当 $k = 0$ 时，会。

所以 $k = 2n(n \in \mathbb{N})$ 即 $k \bmod 2 = 0$ 时，一定可以只剩数字 $1$。

$a,b,c$ 可以互相轮换我就不写了。
# 结论
1. 当 $(b + c) \bmod 2 = 0$ 时，一定可以只剩数字 $1$。

2. 当 $(a + c) \bmod 2 = 0$ 时，一定可以只剩数字 $2$。

3. 当 $(a + b) \bmod 2 = 0$ 时，一定可以只剩数字 $3$。

---

## 作者：silent_ST (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1900B)

## 题意

给定 $a$ 个 $1$，$b$ 个 $2$，$c$ 个 $3$。

在每次操作中，你可以删除其中两个不同的数，然后添加一个与删除的两个数均不同的数（添加和删除的数均为 $1$、$2$ 或 $3$）。例如：删除 $1$、$2$，添加 $3$。

问：若干次操作后是否能**只剩下** $1$ 或者 $2$ 或者 $3$。

## 思路

找规律。

令 $a = 2$，$b = 3$，$c = 4$。

考虑构造出的如下数列是否能通过操作变为只有 $2$ 的数列：

![](https://cdn.luogu.com.cn/upload/image_hosting/dwlgwmh6.png)

经过操作后，数列变为：

![](https://cdn.luogu.com.cn/upload/image_hosting/kfobijfb.png)
 
此时数列中只有 $2$。

回顾一下删除过程：先将 $a$ 个 $1$、$a$ 个 $3$ 成对删除并产生 $a$ 个 $2$。

此时还剩下 $2$ 个 $3$，于是将其中 $1$ 个 $3$ 与 $1$ 个 $2$ 配对删除，产生 $1$ 个 $1$，再使用这 $1$ 个 $1$ 与剩余的 $1$ 个 $3$ 进行配对删除。

所以，在将原有的 $1$ 全部与 $3$ 配对删除之后，剩余的 $3$ 需要分成两组，一半用于与 $2$ 配对删除产生 $1$，另一半用于消除产生的 $1$ 和它本身。

那么就要保证剩余的 $3$ 能够被分成两组且无剩余，即 $(c - a)$ 为偶数。

结论：当 $(c - a) \bmod 2 = 0$ 时，数列中能够只剩下 $2$。

$1$、$3$ 同理。

## 代码

```cpp
#include <iostream>
using namespace std;
int t, a, b, c;
int main(){
    cin >> t;
    for(int i = 1; i <= t; i++){
        cin >> a >> b >> c;
        int ans_one = 0, ans_two = 0, ans_three = 0;
        if((b - c) % 2 == 0) ans_one = 1;
        if((a - c) % 2 == 0) ans_two = 1;
        if((b - a) % 2 == 0) ans_three = 1;
        cout << ans_one << " " << ans_two << " " << ans_three << endl;
    }
    return 0;
}
```

---

## 作者：zhangshuhang2011 (赞：0)

## 思路

首先我们注意到如果最后只剩 $x$，那么另外两个数的数量最后必然都为 $0$，奇偶性相同。而在每一次操作中某个数的数量要么增加 $1$ 要么减少 $1$，原来奇偶性相同的现在还是相同；原来不同的现在还是不同，所以一开始另外 $2$ 个数的数量的奇偶性必须相同才可以。

而如果有两个数，设为 $y$ 和 $z$，个数奇偶性相同，则剩下的那个数，设为 $x$，最后一定可以满足要求，方法如下：

> 1. 如果 $y$ 和 $z$ 的数量均为奇数，那么擦除一个 $y$ 和一个 $z$，并写入一个 $x$。
> 2. 如果黑板上有 $y$ 则擦除一个 $x$ 和一个 $y$，并写入一个 $z$；再擦除一个 $y$ 和一个 $z$，并写入一个 $x$。这时 $x$ 和 $z$ 的数量没变，但 $y$ 少了 $2$ 个。
> 3. 不断重复第二步直到黑板上没有 $y$ ，然后对 $z$ 如法炮制。

这样就一定能只留下 $x$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5];
inline bool isok(int n){
    return (a[1]+a[2]+a[3]-a[n])%2==0;
}
void solve(){
    cin >> a[1] >> a[2] >> a[3];
    if(isok(1)) cout << "1 "; else cout << "0 ";
    if(isok(2)) cout << "1 "; else cout << "0 ";
    if(isok(3)) cout << "1 "; else cout << "0 ";
    cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}

```
## 注意事项

- 此题较为简单，没有注意事项

---

## 作者：__infinity (赞：0)

## Laura and Operations 题解

一共有 $3$ 种操作：删除 $1,2$ 添加 $3$ ,删除 $1,3$ 添加 $2$ ,删除 $2,3$ 添加 $1$ 。

对于 $1$ 来说，显然无论如何操作 $2$ 和 $3$ 的奇偶性都不改变。$2,3$ 同理。

所以只需判断三数之间奇偶性关系即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int a,b,c;
		cin>>a>>b>>c;
		cout<<!((b+c)%2)<<" "<<!((a+c)%2)<<" "<<!((a+b)%2)<<endl;
	}
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 思路

我们怎么判断某一个数可不可能全部出现呢？

我们看另外两个数的个数之差，如果是偶数就输出 $1$ 否则就输出 $0$。

那为什么呢，如果为奇数则它无论怎么操作最终还会剩下一个数没有人跟他匹配。如果是偶数则一个数都不会剩下。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define pb(a) push_back(a)
using namespace std;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		ll a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		ll t = abs(b - c);
		if (t % 2 == 0) {
			cout << "1 ";
		} else {
			cout << "0 ";
		}
		t = abs(a - c);
		if (t % 2 == 0) {
			cout << "1 ";
		} else {
			cout << "0 ";
		}
		t = abs(a - b);
		if (t % 2 == 0) {
			cout << "1\n";
		} else {
			cout << "0\n";
		}
	}
	return 0;
}
~~~

---

## 作者：Phartial (赞：0)

以下只讨论第一个数的计算方法，其他数同理。

高妙做法是注意到无论怎么操作，$b,c$ 的奇偶性总是相同，于是猜测 $b,c$ 可以变为 $0$ 当且仅当 $b$ 和 $c$ 奇偶性相同。可以通过简单的构造来证明这一点。于是你就做完了。

笨蛋做法是考虑 dp，设 $f_{a,b,c}$ 表示现在还剩 $a$ 个 $1$，$b$ 个 $2$，$c$ 个 $3$，是否能通过一系列操作变成形如 $(n,0,0)$ 的状态。转移是简单的，但该状态拓扑序并不明显，所以我们使用记忆化搜索进行处理。

高妙做法：

```cpp
#include <iostream>

using namespace std;

int t, a, b, c;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--; ) {
    cin >> a >> b >> c;
    cout << !(b + c & 1) << ' ' << !(a + c & 1) << ' ' << !(a + b & 1) << '\n';
  }
  return 0;
}
```

笨蛋做法：

```cpp
#include <iostream>

using namespace std;

const int kN = 201;

int t, a, b, c;
bool f[3][kN][kN][kN], v[3][kN][kN][kN];

bool G(int o, int a, int b, int c) {
  if (a < 0 || b < 0 || c < 0) {
    return 0;
  }
  if ((o == 0 || !a) && (o == 1 || !b) && (o == 2 || !c)) {
    return 1;
  }
  if (v[o][a][b][c]) {
    return f[o][a][b][c];
  }
  v[o][a][b][c] = 1;
  return f[o][a][b][c] = G(o, a - 1, b - 1, c + 1) || G(o, a - 1, b + 1, c - 1) || G(o, a + 1, b - 1, c - 1);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--; ) {
    cin >> a >> b >> c;
    for (int o = 0; o < 3; ++o) {
      cout << G(o, a, b, c) << ' ';
    }
    cout << '\n';
  }
  return 0;
}
```


---

## 作者：codwarm (赞：0)

小学奥数题，可以猜结论加证明。

## 题目分析

黑板上有 $a$ 个 $1$，$b$ 个 $2$，$c$ 个 $3$。

两个数每次要么同加要么一加一减，任意两数之差奇偶性不变，因此猜结论：两数之差为偶数，可以只剩下第三个数。

## 证明

假设要求只剩下 $3$，不妨设 $a<b$，可以分为下面几步搞定：

1. 擦掉 $a$ 个 $1,2$，变为：$0,b-a,c+a$。
2. 擦掉 $1$ 个 $2,3$，变为：$1,b-a-1,c+a-1$。
3. 擦掉 $1$ 个 $1,2$，变为：$0,b-a-2,c+a$。
4. 重复 $2,3$。

可以发现每次都会减少两个 $2$，因此只有 $(b-a) \bmod 2 = 0 $ 时，可以只剩下 $3$。

## 代码
```cpp
// Problem: B. Laura and Operations
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c;
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> a >> b >> c;
		cout<<!((b-c) % 2)<<" "<<!((a-c)%2)<<" "<<!((a-b)%2)<<endl;
	}
	
	return 0;
}
```



---

## 作者：yuyc (赞：0)

### 题意

在黑板上写 $a$ 个 $1$、$b$ 个 $2$ 和 $c$ 个 $3$，每次可以进行一种操作：

- 擦去黑板上两个不同的数，在黑板上写下与擦去的两个数不同的数（如：擦去 $1$ 、$2$，写下 $3$）。

问是否可以通过上述操作，使得最后黑板上只剩下一种数。

### 解析
以 $1$ 为例，如果想要使得黑板上只剩下 $1$，就得消耗掉黑板上所有的 $2$ 和 $3$。

有三种操作：

1. 消耗 $2$ 和 $3$ ，增加 $1$。
2. 消耗 $1$ 和 $2$ ，增加 $3$。
3. 消耗 $1$ 和 $3$ ，增加 $2$。

不难发现当 $b=c$ 时，只需一直进行操作 $1$ 即可将所有的 $2$ 和 $3$ 变成 $1$。

如果 $b\not= c$，则可以通过执行操作 $2$、$3$ 来使得 $2$ 的个数与 $3$ 的个数相等，当且仅当 $b$、$c$ 奇偶性相同。

那么会不会出现 $b$、$c$ 相差过大导致 $1$ 不够用的情况呢？

其实不会。

尝试构造一组数据: `1 99 1`。

这组数据满足 $b\not= c$，且 $b>c$ ,故执行操作 $2$，执行一次后变为 `0 98 2`。

此时无法执行操作 $2$，但是可以执行操作 $1$，我们要让 $2$ 的个数与 $3$ 的个数相同，就是为了一直执行操作 $1$ 来消耗掉所有的 $2$ 和 $3$，在数字数量足够时顺序不影响。

执行一次操作 $1$ 后就变成 `1 97 1`，这其实就相当于初始的状态，故交替执行操作 $1$、$2$ 即可消耗掉所有的 $2$ 和 $3$。

判断是否能使黑板上只剩下 $2$、$3$ 的过程同理。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		int a,b,c;
		cin>>a>>b>>c;
		if((c & 1) == (b & 1)) cout<<1;
		else cout<<0;
		cout<<' ';
		if((a & 1) == (c & 1)) cout<<1;
		else cout<<0;
		cout<<' ';
		if((a & 1) == (b & 1)) cout<<1;
		else cout<<0;
		cout<<'\n';
	}	
	return 0;
}
```


---

