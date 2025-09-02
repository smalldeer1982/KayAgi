# Maps.

## 题目描述

小 Y 希望得到一幅地图，这份地图有些与众不同。

这份地图是一幅长为 $n$ 个单位，宽为一个单位的网格图，每个网格必须被涂鸦成白色（$0$）或者黑色（$1$）。

你希望满足小 Y 的愿望送给他一幅这样的地图，但是这时小 Y 又提出了两点要求：

- 对于每个不在网格图两端的白色格子，恰好有 $p$ 个满足它的左右两个格子都被涂鸦成黑色。
- 在满足上述所有条件的情况下，这幅地图从左到右的字符构成的字符串的字典序最小。

你心想，这些要求也是小菜一碟，于是开始了你的创作。

## 说明/提示

#### 【样例解释 #1】

对于第一组数据：只有位于第 $4$ 个字符上的数，满足本身是 $0$，不在地图边缘且周围两个都是 $1$，因此符合条件。可以证明这是满足条件的字典序最小的方案。

对于第三组数据：可以证明没有任何一个解满足长度为 $5$ 且有 $3$ 个数本身是 $0$，不在地图边缘且周围两个字符都是 $1$。

#### 【数据范围】

对于所有测试数据，满足 $1 \le T \le 100$，$1 \le n,p \le 10^5$。

**本题开启捆绑测试，所有数据范围均相同的测试点捆绑为一个 $\text{Subtask}$。**

各测试点的附加限制如下表所示。

| 测试点 | $n,p \le$ |
| :-----------: | :-----------: |
| $1 \sim 3$ | $10$ |
| $4 \sim 5$ | $10^3$ |
| $6\sim 10$ | $10^5$ |

## 样例 #1

### 输入

```
5
5 1
3 1
5 3
5 4
5 5```

### 输出

```
00101
101
-1
-1
-1```

# 题解

## 作者：bryce (赞：12)

## 思路
首先是判断 $-1$ 的情况：如果有 $p$ 个 $0$ 要满足条件，那么最少也要 $2\times p + 1$ 个数，判断是否大于 $n$ 即可。

其他的情况：上面已经说过，满足条件最少也需要 $2\times p + 1$ 个数，那么除去这些数，为了字典序最小，前面的全都放 $0$，最后将满足条件的数拼在后面。
## 代码
```cpp
#include<iostream>

using namespace std;

int T;

int main(){
	cin >> T;
	while (T--){
		int n, p, q, k;
		cin >> n >> p;
		if (2 * p + 1 > n){
			cout << -1 << endl;
			continue;
		}
		for (int i = 1; i <= n - (2 * p + 1); i++) cout << 0;
		for (int i = 1; i <= p; i++) cout << 10;
		cout << 1 << endl;
	}
	return 0;
}
```


---

## 作者：Lovely_Elaina (赞：9)

可以看作要求将若干个 `101` 串首尾拼接在一起。

拼接完后如果长度小于 $n$，就在两段填充 `0`。

如果长度大于 $n$，证明无法满足要求。

因为字典序最小，所以左边尽可能多 `0`，那么我们优先往左边填充 `0`。

易得拼接后的长度为 $1+2\times p$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,p;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    // freopen("app.in","r",stdin);
    // freopen("app.out","w",stdout);
    
    int T;
    cin >> T;
    while(T--){
        cin >> n >> p;
        int len = 1 + 2 * p;
        if(len > n){
            cout << -1 << endl;
            continue;
        }
        for(int i = n-len; i > 0; i--)
            cout << 0;
        for(int i = 1; i <= p; i++)
            cout << "10";
        cout << 1 << endl;
    }
    return 0;
}
```

---

## 作者：MarsTraveller (赞：6)

# 题意：
构造一个字符串 $S$，长度为 $n$，
- 对于每个字符 $S_i$（$1 \le i \le n-2$），共有 $p$ 个位置满足：
$\begin{cases}
 S_i = 0 \\
 S_{i-1} = 1\\
 S_{i+1} = 1 \\ 
\end{cases}$。

- 在所有满足条件的字符串中，$S$ 的字典序最小。

- 如果构造不出任何 $S$，则输出 `-1`。

# 分析：
既然要求构造，那就从两大方面考虑：
## 1. 无法构造的情况：
构造满足条件的条件子串，用形如 `10101...` 来构造时，需要构造的字符串长度至少为 $2 \times p + 1$。

**所以当构造序列的长度 $n$，满足 $n < 2 \times p + 1$ 时，无法构造出规定字符串。**
## 2. 构造最小的字符串：
既然已经可以构造出字符串了，显然是要让形如 `10101...` 的条件字串越靠后越好，前面的 $n - (2 \times p + 1)$ 个位置要用最小的 $0$ 来补齐，所以最后的字符串一定是形如 `0...0101...101`的字符串，这就是我们要构造的字符串了。

# 代码：
赛时代码：

```cpp
#include <iostream>
#define big long long
using namespace std;
big n,p,T;
int main()
{
    cin >> T;
    while(T--)
    {
        cin >> n >> p;
        if(n < 2*p+1) // 判断能否构造
        {
            printf("-1\n");
            continue;  
        }
        for(big i = 1;i <= n-(2*p+1);i++) // 构造前面补齐的'0'
        {
            cout << 0;
        }
        // 构造最短条件子串
        cout << 1;
        for(big i = 1;i <= p;i++)
        {
            cout << "01";
        }
        cout << '\n'; // 多组数据，不要忘记换行
    }
    return 0;
}
```
 ~~好久没做构造题了，赛时居然 WA 了一回。~~

---

## 作者：York佑佑 (赞：2)

## 题意
输入 $T$ 组数据。对于每组数据，输入 $n$ 和 $p$，并输出一个长度为 $n$ 的字符串（只包含 $0$ 和 $1$），要求里面有 $p$ 个 $a_i$，保证 $a_i$ 为 $0$ 以及 $a_{i-1}$ 和 $a_{i+1}$ 为 $1$。**并且该串从左到右的字符构成的字符串的字典序最小**。如果该串不存在，输出 $-1$。
## 分析
首先，如何构造出有 $p$ 个 $a_i$，保证 $a_i$ 为 $0$ 以及 $a_{i-1}$ 和 $a_{i+1}$ 为 $1$ 的串呢？

- 当 $p$ 为 $1$ 时，不难想到方案为 ```101```。此时 $a_2$ 为 $0$，$a_1$ 和 $a_3$ 为 $1$。

- 当 $p$ 为 $2$ 时，方案为 ```10101```。此时 $a_2$ 和 $a_4$ 为 $0$，$a_1$ 和 $a_3$ 以及 $a_5$ 为 $1$。

列举了一下，也就是说构造的序列长度为 $2p+1$，并且字符串从头到尾为 $0$ 和 $1$ 交替循环即可。

其次，该串从左到右的字符构成的字符串的字典序最小。也就是说，前面的 $0$ 要越多越好。那把刚刚那一段长度为 $2p+1$ 的字符串放在最末尾输出，前面长度为 $n-(2p+1)$ 的串全部输出 $0$ 即可。

最后，时该串是否存在的问题。前文提到，这样有 $p$ 个符合题意的 $0$ 至少要有 $2p+1$ 个。所以当 $n<2p+1$ 时，没有该串。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, p;
		cin >> n >> p;
		if (n < p * 2 + 1)//n<2p+1,没有该串
		{
			cout << "-1\n";
			continue;
		}
		int num = 1;
		for (int i = 1; i <= n - (p * 2 + 1); i++)//先输出n-(2p+1)个0
			cout << 0;
		for (int i = 1; i <= p * 2 + 1; i++)//属于输出1和0交替串
		{
			cout << num;
			num =! num;//1和0交替
		}
		cout << endl;
	}
	return 0;
}
```



---

## 作者：kimidonatsu (赞：2)

# P9687 Maps. 题解

一眼构造题。

考虑 $01$ 串字典序最小的含义：尽可能将 $1$ 往后放。

由于左右端点的 $0$ 都不能算入 $p$  ，那么我们可以这样构造字符串：先补上一个 $1$ ，之后每有一个 $p$ ，我们就输出 $01$ 构造出两个黑块夹一个白块的 $p$ ，即形如 $101$ 的字串。如果最后构造出的长度不等于 $n$ ，我们就在前面的位置用 $0$ 占位补足，容易发现构造出的 $01$ 字符串形式如下：

$$000\dots0101\dots01$$

易证这是满足条件的字典序最小的方案。

显然，无法满足的情况就是无法通过 $\dfrac{n - 1}{2}$ 得到 $p$ 的情况（减去一个占位 $1$ 之后无法构造出满足 $p$ 要求的 $01$ 串）。

可以写出代码：

```cpp
#include <bits/stdc++.h>

void solve() {
	int n, p;
	std::cin >> n >> p;

	if (1 + 2 * p > n) {		// 无法满足，进行特判
		std::cout << "-1\n";
		return;
	}

	for (int i = 1; i <= n - 2 * p - 1; i++)	// 先补 0
		std::cout << "0";
	std::cout << "1";	// 输出 1 和下面的 01 串一起构成题目要求的 101 字串
	while (p--) {		// 按 p 要求输出 01
		std::cout << "01";
	}
	std::cout << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

```


---

## 作者：Lemon_zqp (赞：2)

### 思路
这道题目可以发现规律，如果 $n$ 小于 $2p + 1$ 那么直接输出 $-1$，因为它是说在每个零周围都有一个一，要保证有 $p$ 个零，那么就要 $p + 1$ 个一，加起来就是 $2p + 1$，否则就先输出 $n - (2p + 1)$ 个零，因为要把这个长度为 $2p + 1$ 的字符串放在后面才能保证字典序最小，后面就输出 $p$ 个 `01`，然后在末尾补一个 `1` 即可。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++){
		int n, p;
		cin >> n >> p;
		if(n < (2 * p) + 1){
			cout << -1 << endl;
		}
		else{
			int tt = n - ((2 * p) + 1);
			for(int j = 1; j <= tt; j++){
				cout << 0; 
			}
			for(int j = 1; j <= p; j++){
				cout << 10;
			}
			cout << 1 << endl;
		}
	}
	return 0;
}
```


---

## 作者：ICU152_lowa_IS8 (赞：2)

相对简单的一道题，考了基础构造。

首先考虑无解的情况，显然如果要构成题目的条件，$n$ 不能小于 $2p+1$，否则无解。

随后考虑构造，要达到题目给定的条件，显然字符串中应当包含一个长度为 $2p+1$ 的形如 $101010101\cdots$ 的字符串，剩下的 $n-2p-1$ 个字符都为 $0$，且为 $0$ 的尽量靠前。

将构造出的字符串输出即可，代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,p;
		cin>>n>>p;
		if(n<2*p+1){
			cout<<-1<<endl;
		}
		else{
			for(int i=1;i<=n-2*p-1;i++){
				cout<<0;
			}
			for(int i=1;i<=p;i++){
				cout<<"10";
			}
			cout<<1<<endl;
		}
	}
	return 0;
}

```


---

## 作者：Focalors (赞：2)

构造题一道。

为了使字典序最小，应从后往前依次用 $1, 0$ 染色，因此恰好有 $p$ 个白色格子左右两边均为黑色格子的字符串长度为 $2 \times p + 1$（首尾均为 $1$，如 $p=3$ 时所成的字符串为 $1010101$）。

若 $2 \times p + 1 > n$，则无法完成，输出 $-1$；否则，在该字符串前方还有 $n - 2 \times p - 1$ 个 $0$，依次输出即可。

AC 代码：
```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read() {
	ll x = 0, y = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') y = -1;
		c = getchar();
	}
	while (c >= '0' && c <='9') x = (x << 3) + (x << 1) + (c & 15), c = getchar();
	return x * y;
}
int t, n, p;
int main() {
	t = read();
	while (t--) {
		n = read();
		p = read();
		if (2 * p + 1 > n) {
			puts("-1");
			continue;
		}
		for (int i = 1; i <= n - 2 * p - 1; i++)
		    putchar('0');
		for (int i = 1; i <= p + 1; i++)
			if(i == p + 1) putchar('1'), putchar('\n');
			else putchar('1'), putchar('0');
	}
	return 0;
}
```

---

## 作者：WBH_xh_0709 (赞：1)

一.原题链接：[原题链接](https://www.luogu.com.cn/problem/P9687)  
二.思路：  
它就是让你输入 $T$，并输入 $T$ 组数据，每组数据输入 $n$ 和 $p$，让你构造一个 01 字符串，使它的字典序最小，并且让它有正好 $p$ 个 1 的左右两边都是 0。  
我们首先想到它要有 $p$ 个 1 的左右两边是 0，那么只要 $p$ 大于等于 $(n+1)/2$，这个字符串就构造不成。特判完，我们就想如何构造了。我们要保证他的字典序最小，所以我们就把 1 尽量往后放。所以，我们最后一个就是 1，然后 01 相间着存到 $a$ 数组中，1 存够 $p$ 个后，就退出循环。  
注意：因为多测要清空，$a$ 数组在每次都要清空，每一项都设为 0。此处枚举是从 $n$ 到 $1$ 枚举，具体请看代码。  
三.代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int t;
int n,p;
int a[1000010];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>p;
		if(p>=(n+1)/2){
			cout<<"-1\n";
			continue;
		}
		memset(a,0,sizeof(a));
		int k=0;
		for(int i=n;i>=1;i--){
			if(k<=p){
				if((n-i)%2==0)
					a[i]=1;
				if((n-i)%2==1){
					a[i]=0;
					k++;
				}
			}
			else
				break;
		}
		for(int i=1;i<=n;i++)
			cout<<a[i];
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：CNS_5t0_0r2 (赞：1)

因为 $1$ 要每 $2$ 位填充一个，不难发现，当 $n \leq 2p$ 时无解。

否则，从头开始填充，每 $2$ 位填充一个 $1$，直到填满 $p$ 个，最后反向输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int t,n,p;
int ans[N];
int main(){
	scanf("%d", &t);
	for(;t;t--){
		memset(ans,0,sizeof ans);
		scanf("%d%d", &n, &p);
		if(n <= p * 2)
			printf("-1");
		else{
			int i = 2;
			for(i = 2;(i / 2) <= p;i += 2)
				ans[i - 1] = 1;	
			ans[i - 1] = 1;
			for(int i = n;i >= 1;i--)
				printf("%d",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：FurippuWRY (赞：1)

题意：构造一个长度为 $n$ 的 01 字符串 $S$，此字符串有以下两点要求：  
1.  对于字符串中所有的 $p$ 个不在字符串两端的 $0$，它们左边和右边的一个字符为 $1$。  
2.  使构造出的字符串的字典序最小。  

先设 $S$ 完全由 $0$ 构成。  
对于点 1，设一变量 $j$，为 $S$ 中的字符序号。$j$ 赋初始值为 $1$（因为“不在字符串两端”）。将 $S$ 中的字符 $S_j$ 左边和右边的元素改为 $1$，（即 $S_{j-1}\leftarrow 1,S_{j+1}\leftarrow 1$），然后将 $j$ 的值加上 $2$，继续修改 $S_{j+2}$ 左右两个元素，如此循环 $p$ 次，此时所构造的 $S$ 中，每两个 $1$ 之间都由一个 $0$ 隔开。

对于点 2，仅需倒序输出所构造的 $S$ 即可。因为 $S$ 是从开头开始构造的，所以 $S_{0}$ 一定为 $1$，若 $p$ 远小于 $n$，则 $S$ 的后半段大部分都是 $0$，此时倒序字符串的字典序是小于原字符串的，而且符合以上两点要求。也就是说，倒序字符串的字典序小于等于原字符串，且符合要求，所以倒序输出即可。

那如何判断输出 $-1$ 呢？若 $2p\ge n$，则输出 $-1$，否则输出所构造的 $S$。因为每两个 $1$ 之间都由一个 $0$ 隔开，所以从第一个 $1$ 到最后一个 $1$ 的长度就为 $2p+1$，如果 $2p\ge n$，则 $2p+1$ 是一定大于 $n$ 的，构造出的 $S$ 长度须小于等于 $n$ 才合法，所以此时就输出 $-1$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 114514;

int t, n, p, s[N];

int main() {
	cin >> t;
	while (t--) {
		int j = 1;
		cin >> n >> p;
		if (2 * p >= n) {
			cout << -1 << '\n';
			continue;
		}
		else {
			for (int i = 0; i < n; ++i) s[i] = 0;
			for (int i = 0; i < p; ++i) {
					s[j + 1] = 1;
					s[j - 1] = 1;
					j += 2;
			}
			for (int i = n - 1; ~i; --i) {
				cout << s[i];
			}
			cout << '\n';
		}
	}
    return 0;
}
```

---

## 作者：Failure_Terminator (赞：1)

## Solution

简单构造。

考虑一种形如 `10101...` 的构造形式，这种形式可满足最多 $\left \lfloor \frac{n - 1}{2}  \right \rfloor$ 个 $0$ 的条件。

若超过这个数量就无法完成，输出 $-1$。

题目要求所求字串字典序最小，因此将尽可能多的 $0$ 放在字串前部。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int now=0,nev=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
    while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar(); }
    return now*nev;
}

int n, k;

void solve(){
	n = read(), k = read();
	int t = (n - 1) / 2;
	string s;
	if (k <= t){
		for (int i = 1; i <= k; i ++)
			s += "10";
		s += "1";
		for (int i = k * 2 + 2; i <= n; i ++) s += "0";
		reverse(s.begin(), s.end());
	}
	else s = "-1";
	cout << s << "\n";
}

signed main()
{
	int t = read();
	while (t --) solve();
    return 0;
}
```

---

## 作者：Big_Dinosaur (赞：1)

构造题。

当 $2p+1\le n$ 时，有解。字典序最小的解，是当序列倒转，前 $p+1$ 个奇数位位 $1$，其他位是 $0$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x;string s;
signed main(){
int t;cin>>t;while(t--){
cin>>n>>x;s="";
if(x*2+1>n)puts("-1");else{
for(int i=1;i<=n;++i)if((i&1)&&(i<=x*2+1))s+="1";else s+="0";
for(int i=n-1;i>=0;--i)cout<<s[i];puts("");
}
}
}
```

---

## 作者：InversionShadow (赞：1)

因为要字典序最小，所以肯定前面是若干个 $\texttt{0}$。

那么如何构造后面的形如 $\texttt{10101...01}$ 呢？发现 $p=1$ 时是 $\texttt{101}$，$p=2$ 时是 $\texttt{10101}$，所以是若干个 $\texttt{01}$ 加上一个 $\texttt{1}$，长度也就是 $2 \times p + 1$。

所以 $\texttt{0}$ 的数量就是 $n - (2 \times p + 1)$。

那什么时候无解呢？如果 $2 \times p + 1 > n$ 就输出 `-1`。

```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, p;

void solve() {
	cin >> n >> p;
	if (p * 2 + 1 > n) {
		cout << "-1\n";
		return ;
	}	
	for (int i = 1; i <= n - 2 * p - 1; i++) {
		cout << 0;
	}
	for (int i = n - 2 * p - 1; i <= n; ) {
		if (i == n - 3) {
			cout << "101";
			i += 3;
			break;
		} else {
			cout << "10";
			i += 2;
		}
	}
	cout << "\n";
}

int main() {
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

/*
10101
*/
```

---

## 作者：Miyamizu_Mitsuha (赞：1)

考虑贪心。$p$ 个 $0$ 旁边有 $2$ 个 $1$，所以自然考虑形如这样的序列：`1010101...`要求字典序最小，把这一坨东西放在后面，前面填充 $0$ 就好了。

补一下无解判断：$p$ 个最少需要 $2\times p+1$ 个位置（$p$ 个 `10`，最后再补一个 `1`），所以如果 $p\times 2 \geq n$ 显然无解。

```
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin>>T;

    while(T--) {
        int n,p;
        cin>>n>>p;

        if(p*2>=n){
            cout<<"-1"<<endl;
        } else {
            int k=n-1-2*p;
            string zeros(k,'0');
            cout<<zeros;
            while(p--)cout<<"10";
            cout<<1<<endl;
        }
    }

    return 0;
}
```


---

## 作者：__Octhyccc__ (赞：0)

考虑构造。

先思考这样一个问题，在输出结果一定没有 $-1$（即都可以构造出来）的时候，$p$ 最大可以是多少？

很明显，字符串是 `101010...1`，由于最后有一个 `1`，所以 $p$ 的最大值是 $\lfloor\frac{n-1}{2}\rfloor$，所以 $p > \lfloor\frac{n-1}{2}\rfloor$ 时，输出 $-1$ 即可。

因为需要字符串字典序尽可能小，字符串最后一位只能是 `1`。那么前面我们输出多少个 `0` 呢？

最后一位只能是 `1`，那么有效位数就是 $n-1$。又因为制造 $p$ 个 `101` 串至少需要 $p$ 个 `10`（放在字符串尾），那我们就要输出 $n-1-2p$ 个 `0`，再输出 $p$ 个 `10`，最后放一个 `1`，就完成了构造。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;int T;
int main(){
	scanf("%d",&T);
	while(T--){
		int n,p;
		scanf("%d%d",&n,&p);
		if((n-1)/2<p){
			puts("-1");continue;
		}
		for(int i=0;i<n-2*p-1;i++)putchar('0');
		for(int i=0;i<p;i++)printf("10");
		puts("1");
	}
	return 0;
}
```

---

## 作者：May_Cry_ (赞：0)

一道构造题

## 思路
题目说构造出一个字符串使的左右都是黑色的方块的白块数量**正好**为 $p$，并要求字典序最小，显然，染黑两个距离为 $1$ 的块会产生一个满足要求的白块，又要求字典序最小，所以我们可以倒序来染黑块，记录一个变量 ``cnt``，初始值一定要赋为 ``-1``，因为染黑 $2$ 个只能产生一个满足条件的白块，当循环中的 $i$ 小于 $1$ 时，证明根本无法满足条件，直接输出 $-1$。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
int T;
int n ,p;
int ans[1000001];
void solve() {
    memset(ans , 0 ,sizeof ans);
    bool flag = 0;int cnt = -1;
    for (int i = n;;i -= 2) {
        ans[i] = 1; cnt ++;
        if (i < 1) {
            cout << "-1\n";flag = 1;break;
        }
        if (cnt == p) break;
    }
    // cout << cnt << endl;
    if (flag) return;
    if (cnt < p) {
        cout << "-1";return;
    }
    for (int i = 1;i <= n;i ++) {
        cout << ans[i];
    }
    cout << endl;
}
inline int read();
int main(){
	T = read();
    while (T --) {
        n = read() ,p = read();
        // cin >> n >> p;
        solve();
    }
	return 0;
}
inline int read(){
	int x = 0 ,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑贪心。

对于一组有解的输入 $n,p$，字典序最小的答案一定是形如：$00\dots01010\dots101$ 的。这里面满足条件的 $0$ 的数量等于 $1$ 的数量减 $1$。可以推出 $1$ 的数量为 $p+1$，满足条件的 $0$ 的数量为 $p$。

那么，对于无解的情况，一定就是 $n \le 2 \times p$。有解的情况先输出 $n-2\times p-1$ 个 $0$，再按照上面的样子输出 $p$ 个 $10$ 与 $1$ 个 $1$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p;
string s;
void solve(){
	cin>>n>>p;
	if(n<=2*p){cout<<"-1\n";return ;}
	for(int i=1;i<=n-2*p-1;++i) cout<<0;
	for(int i=1;i<=p;++i) cout<<"10";
	cout<<"1\n";return ;
}
int main(){
	int t;cin>>t;
	while(t--) solve();
	return 0;
}
```


---

## 作者：SunsetVoice (赞：0)

算法：贪心。

既然是字典序最小，那么我们就要让 $1$ 尽量靠后，这就是贪心。

注意首先判断无解。

时间复杂度为线性，可以通过。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,p;
	int T;
	bool a[100001] = {0};
	cin>>T;
	while(T--){
		int j;
		cin>>n>>p;
		for(int i = 1;i<=n;i++)a[i] = 0;
		if(n%2==1)j = n/2;
		else j = n/2-1;
		if(p>j)cout<<-1<<endl;
		else{
			j = n-1;
			while(p>0){
				p--;
				a[j] = 1;
				j-=2;
			}
			for(int i = 1;i<=n;i++){
				if(a[i+1]==1 or a[i-1]==1)cout<<1;
				else cout<<0;
			}
			cout<<endl;
		}
	}
	system ("pause");
}

```


---

## 作者：Submerge_TA (赞：0)

易知，一个满足条件的网格图的长度至少为 $2 \times p + 1$，所以如果 $n$ 小于 $2 \times p + 1$，一定没有满足条件的网格图，输出 `-1`，否则输出互相交错的 $p+1$ 个 `1` 和 $p$ 个 `0`，因为长度必须为 $n$ 且字典序最小，所以在前面输出 $n - 2 \times p - 1$ 个 `0`，再输出互相交错的 $p+1$ 个 `1` 和 $p$ 个 `0`，就是满足条件的网格图。

AC 代码：

```
#include<iostream>
using namespace std;
int t,n,p;
int main() {
	cin>>t;
    for(int i=0;i<t;i++) {
        cin>>n>>p;
        if(n<2*p+1) {
        	cout<<-1<<endl;
			continue;
		}
		for(int j=2*p+1;j<n;j++) cout<<0;
		for(int j=0;j<p;j++) cout<<10;
		cout<<1<<endl;
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

首先，答案中一定有一个串 `101010...01010101`，而这个串本身需要 $2\times p+1$ 个位置，所以 若 $n<2\times p+1$ 则无解。

然后我们可以把这个串放到最后面，然后前面都放 $0$，这样可以保证字典序最小。

```
#include<iostream>
using namespace std;
int t,a,b,x;
int main(){
    cin>>t;
    while(t--){
        cin>>a>>b;
        x=-1;
        if(2*b+1>a){
            puts("-1");
            continue;
        }
        for(int i=1;i<=a;i++){
            if(i<=a-2*b-1) cout<<0;
            else{
                x=i;
                break;
            }
        }
        if(x>=0){
            for(int i=x;i<=a;i++){
                if((i-x)%2==0) cout<<1;
                else cout<<0;
            }
        }
        cout<<endl;
    }
}
```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/P9687)

## 题意

构造题，给你一个长度为 $n$ 的 $01$ 序列，初始全部为 $0$，你需要将一些项改成 $1$，而且满足以下要求：

- 对于每个不在序列两端的 $0$，恰好有 $p$ 个满足它的左右两个格子都被改成 $1$。

如果无法构造出来，输出 $-1$，否则输出字典序最小的序列。

## 思路

贪心。因为要字典序最小，所以 $0$ 要尽可能的集中在前面，而为了满足条件，后面的序列要是 $1010 \cdots 01$ 的形式，这一段的长度应为 $2 \times p + 1$，其中有 $p$ 个 $0$ 和 $p + 1$ 个 $1$。自然前面的 $0$ 的个数就为 $n - (2 \times p + 1)$，然后直接输出即可。

## 代码

```cpp
// J2023 | BLuemoon_
#include <bits/stdc++.h>

using namespace std;

int t, n, p;

int main() {
  for (cin >> t; t; t--) {
    cin >> n >> p;
    if (((p << 1) + 1) > n) {
      cout << "-1\n";
    } else {
      string s;
      for (int i = 1; i <= (n - ((p << 1) + 1)); i++) {
        cout << "0";
      }
      for (int i = 1; i <= p; i++) {
        cout << "10";
      }
      cout << "1\n";
    }
  }
  return 0;
}
```

---

## 作者：Lavande (赞：0)

我的思路来源于[这里](https://www.luogu.com.cn/blog/674469/lgr-161-div3-luo-gu-ji-chu-sai-4-ti-xie)，感谢官方提供思路！

# 题目

小Y希望有一幅长为 $n$ 个单位，宽为一个单位的网格图，每个网格必须被涂鸦成白色或者黑色。

当然还有两个条件：

- 对于每个不在网格图两端的白色格子，恰好有 $p$ 个满足它的左右两个格子都被涂鸦成黑色。

- 在满足上述所有条件的情况下，这幅地图从左到右的字符构成的字符串的字典序最小。

# 思路

事实上由于这道题的贪心性，其实最后一个数字总是为 $1$。我们可以发现，字典序越小，要求这个字符串第一个为 $1$ 的元素一定尽量靠后，那么我们可以从 $1$ 枚举到 $n$，判断这个 $1$ 放在哪里。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,p,i,j;//一定要开long long！
long long f(long long x){
    return (x-1)/2;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n>>p;
        if(f(n)<p){
            cout<<"-1"<<endl;
            continue;
        }
        for(i=1;i<=n;i++){
            if(f(i)==p){
            	break;
			}
        }
        for(j=1;j<=n-i;j++){
        	cout<<0;
		}
        for(j=1;j<=i;j++){
            if(j%2) cout<<1;
            else cout<<0;
        }
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：IcyFoxer_XZY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9687)

一道思维题。

首先考虑输出 $-1$ 的情况。由于有 $p$ 个不在首尾的白色网格两边都是黑色，所以一个长为 $n$ 的网格图最多有 $(n-1)\div 2$（向下取整）个满足要求的白色网格。当题目给出的 $p$ 大于此数时输出 $-1$。

接下来就好做了。由于字典序最小，所以网格图中的黑点尽量往后放，那从后往前遍历，依次把每个网格涂成黑、白、黑......直到有 $p$ 个满足要求的点，剩余的就全部涂白。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,p;
signed main(){
	cin>>t;
    while(t--){
    	cin>>n>>p;
    	if(p>(n-1)/2)puts("-1");
    	else{
    		for(int i=1;i<=n-(p*2+1);++i)printf("0");
    		for(int i=1;i<=p;++i)printf("10");
    		puts("1");
		}
	}
    return 0;
}
```
Bye！

---

## 作者：蟋蟀喵～～ (赞：0)

## 简述题意

给出 $0,1$ 序列的长度 $n$，数字 $1$ 的个数 $p$，使除了序列开头与序列结尾的每个数 $1$ 的两边都是 $0$，并使字典序最小。

## 算法分析

一般地，带有 `字典序最小` 的题目一般是贪心。

拿到贪心题，我们就要想贪心方法了。

> ### 贪心分析：
> 1. 既然只有 $0$ 和 $1$，字典序又要最小，我们就要让最前面几位尽量是 $0$。
> 1. $1$ 的两边都是 $0$，所以该序列肯定有 $p$ 个 `101` 子串。
> 1. 由于一开始都是 $0$，字典序最小，所以最后应该是连续的 `101`。
> 1. 连续 $2$ 个 `101` 子串应该是 `10101` 而不是 `101101`。
> 1. 所以最后应有 $1$ 个 `101` 与 $p - 1$ 个 `01`。
> 1. 也就是说 $n < 2 \times p + 1$ 时，无解，其余情况有解。
> 1. 最开始应有 $n - 2 \times p + 1$ 个 $0$。

## 代码（为了您的名誉，请不要抄袭题解）

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,p;
int main(){
	cin >> t;
	while(t--){
		cin >> n >> p;
		int temp = p * 2 + 1;                      //101 子串开始的位置。
		if(temp > n){
			cout << "-1\n";
		}else{
			for(int i = 1; i <= n - temp; i++){         //n - temp : 0 的个数。
				cout << "0";
			}
			cout << 101;                        //第一个是 101。
			for(int i = 1; i < p - 1; i++){           //剩下 p - 1 个 01。
				cout << "01";
			}
			cout << "\n";
		}
	}
	return 0;
}
```

---

## 作者：xiaoyang111 (赞：0)

# P9687 Maps. 题解

## 前言

[题面传送门。](https://www.luogu.com.cn/problem/P9687)

[可能更好的阅读体验。](https://www.luogu.com.cn/blog/xiaoyang111/p9687-maps-ti-xie)

求过。

## 讲解

### 思路

我们约定一下：下面讲解为了方便并没有说多测的事情，请读者注意。

这一题主要考察构造思路。

下面是这个题的简化题面。

> 构造一个长度 $n$ 的 $\texttt{01}$ 串，需要满足恰好 $p$ 个 $\texttt{0}$ 左右两边都是 $\texttt{1}$，且字典序最小的字符串，如果构造不出来就输出 $\texttt{-1}$。

我们想，可以把最终构造出的字符串分成前面和后面两个部分，第一个部分是用来凑数的，第二个部分就是算 $\texttt{0}$ 两边都是 $\texttt{1}$ 的部分。

为了让字典序最小，让第一个部分全是 $\texttt{0}$，第二个部分是 $p$ 个 $\texttt{0}$ 间接穿插在 $p + 1$ 个 1 的，即 $\texttt{1010101...101}$ 形式。那么第二个部分长度就是 $p + p + 1$，即 $2 p + 1$ ，第一部分长度就是 $n - (2 p + 1)$。

构造第二部分的时候需要注意，是 $\texttt{0}$ 穿插在 $\texttt{1}$ 中间的，先 $\texttt{1}$ 再 $\texttt{0}$，最后应该多一个 $\texttt{1}$，所以 $\texttt{0}$ 的数量大于 $\texttt{1}$ 的数量。穿插 $\texttt{0}$ 的时候可以这样做（这里下标从 $0$ 开始枚举）：当下标是 $2$ 的倍数是，该位置就应该是 $\texttt{1}$，否则就应该是 $\texttt{0}$。

怎么判断能否构造呢？我们想，如果第二部分应该的长度和总长一样，意味着刚好塞下，所以这时第一部分长度没有，即 $n - (2 p + 1) = 0$；如果如果第二部分应该的长度比总长长，意味着塞不下，构造失败，所以这时第一部分长度最后算出来是负数，即 $n - (2 p + 1) < 0$，那么我们拿这个式子判断一下就可以了。

### 代码

思路出来了，代码就不会很难。风格可能有些难看，敬请谅解。

```cpp
#include <iostream>//头文件
using namespace std;
int main(){
	int t;//多组数据。
	cin >> t;
	for (int _=0;_<t;++_){
		int n,p;
		cin >> n >> p;//输入。
		if (n-(2*p+1)<0){//根据讲解中的式子判断一下。
			cout<<-1;//构造失败。
		}else{
			for (int i=0;i<n-(2*p+1);++i){//第一部分。
				cout<<"0";
			}
			for (int i=0;i<2*p+1;++i){//第二部分。
				if (i%2==0){
					cout<<"1";
				}else{
					cout<<"0";
				}
			}
		}
		cout<<endl;//记住要换行。
	}
	return 0;
} 
```

---

## 作者：XRRRRcode (赞：0)

## 题解
本题在基础赛中还是比较简单的，理解题意后解题就变得异常方便。在 $n\le 2p$ 时，显然是无解的（因为字符串无法装下足够的黑色块），特判输出 $-1$。因为要求输出的字符串字典序最小，所以要在构造的字符串的尽可能前的位置放置尽可能多的 $0$。

综上所述，我们可以先构造一个倒序字符串。为了使最终得到的字符串字典序最小，所以就得到了一个以 $1$ 开头的字符串。接着循环构造，因为要在倒序字符串前面放置最少数量的 $1$，我们得到可以在 $1$ 后面放置 $p$ 个 $01$ 串，用 $0$ 填补剩余的字符，最后将倒序字符串还原输出。

一共 $T$ 组数据，处理每组数据时花费 $O(p)$ 的时间复杂度构造以 $1$ 开头的 $01$ 串，再花费共计 $O(n)$ 的时间复杂度输出补位用的 $0$ 和还原后倒序串。根据特判后的 $2p<n$ 不难得出总时间复杂度为 $O(Tp)$，对于 $T<100$ 并且 $n,p<10^5$ 的数据范围可以稳过了。
## 代码
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
    int t,i,j,n,p,k;
    string s;
    cin>>t;
    for(i=0;i<t;i++)
    {
        cin>>n>>p;
        if(2*p>=n)
        {
            cout<<-1<<endl;
            continue;
        }//特判
        s="1";
        for(j=1;j<=p;j++)
        {
            s+='0';
            s+='1';
        }//构造倒序串
        k=s.size();
        for(j=n-k;j>0;j--)
            cout<<'0';//输出补位0
        for(j=k-1;j>=0;j--)
            cout<<s[j];
        cout<<endl;
    }
    return 0;
}
/*
ID:R127047330
Length:517B
Time:78ms
Memory:812KB
*/
```


---

## 作者：G__G (赞：0)

先简化一下题意：按照几条规则构造长度为 $n$ 的字典序最小的字符串,构造不出输出 $-1$。

- 字符串里只有 $0$ 和 $1$。
- 有 $p$ 个不在边缘的 $0$ 的两边都是 $1$。

如果没有字典序最小，构造方法可能很多。但就是这个条件，让一种构造方法脱颖而出。

$$....1010101$$

而满足条件的字符串长度是：

$$2p+1$$

所以能构造字符串的必要条件就是：

$$2p+1 \le n$$

讲的都讲完了，下面就是代码实现。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		if(m*2+1>n){
			cout<<-1<<endl;
			continue;
		}
		string s="1";
		for(int i=1;i<=m;i++){
			s="10"+s;
		}
		for(int i=n;i>s.size();i--){
			cout<<"0";
		}
		cout<<s<<endl;
	}
	return 0;
}
```


---

## 作者：_colin1112_ (赞：0)

+ 一道比较水的构造题。

## 思路

首先判断是否有可行方案。

先看规则：

+ 对于每个不在网格图两端的白色格子，恰好有 $p$ 个满足它的左右两个格子都被涂鸦成黑色。

既然要恰好有 $p$ 个满足它的左右两个格子都被涂鸦成黑色，那么就要判断他满足条件后是否在 $n$ 这个长度内。

判断代码：

```c++
if(p*2+1>n){// p*2+1 是满足条件最少的长度。
	cout <<-1<<endl;// 如果超出 n 的长度，则输出 -1。
}
```

如果没有超出长度，那么说明是可行的，就要构造一个字典序最小的序列来。

既然要最小，那么在满足条件的字符串基础上，在其前面补 $0$ 即可。

## AC Code

```c++
#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define IO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;
const int E=1e6+5;
ll t;
int main() {
	IO;
	cin >>t;
	while(t--){
		ll n,p;
		cin >>n>>p;
		if(p*2+1>n){
			cout <<-1<<endl;
		}
		else{
			bool flag=false;
			for(int i=0;i<n-(p*2+1);i++){
				cout <<0;// 在字符串前面补 0。
			}
			for(int i=0;i<p*2+1;i++){
				if(flag==false){
					cout <<1;
					flag=true;
				}
				else if(flag==true){
					cout <<0;
					flag=false;
				}
			}// 其他的直接输出满足条件的字符串即可。
			cout <<endl;
		}
	}
	return 0;
}
```

---

## 作者：FwbAway (赞：0)

考虑到字典序最小，所以我们要尽可能的把 $1$ 放在字符串的右侧，可以从 $n-1$ 处每次向回跳，一次跳两个，每一次把当前位置标记为 $0$，左右标记为 $1$ 即可：

```c++
for (int i = n-1; i >= 1; i -= 2) {
	if (!q) break;
	q--;
	ans[i] = 0;
	ans[i + 1] = 1;
	ans[i - 1] = 1;
}
```
推算之后可以发现要占用的空间为 $q \times 2 + 1$，所以如果 $n$ 大于这个值，就直接输出 $-1$ 即可。

输出的时候最好用数组输出，标记起来方便一些，记得没有空格。

完整代码：

```c++
#include <bits/stdc++.h>
using namespace std;
int T;
int n, q, ans[110000];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &q);
		if (n < q * 2 + 1) {
			printf("-1\n");
			continue;
		}
		for (int i = 1; i <= n; i++)ans[i]=0;
		for (int i = n-1; i >= 1; i -= 2) {
			if (!q) break;
			q--;
			ans[i] = 0;
			ans[i + 1] = 1;
			ans[i - 1] = 1;
		}
		for (int i = 1; i <= n; i++) {
			printf("%d", ans[i]);
		}printf("\n");
	}
	return 0;
}
```

---

