# [SEERC 2020] Reverse Game

## 题目描述

Alice 和 Bob 在玩一个游戏，规则如下：

- 游戏开始前给定一个字符串 $s$。

- 每次行动，选择 $s$ 的一个子串 $t$，$t$ 只能是 `10`、`100`、`110`、`1010` 中的一个，反转 $t$ 的每个字符，例如 `100` 翻转为 `001`。

- 不能操作者输掉游戏。

Alice 先手，问双方同时采取最优策略的情况下，谁能赢。

## 说明/提示

对于样例 $1$，选择子串 `10` 进行反转后 Bob 无法操作。

## 样例 #1

### 输入

```
010```

### 输出

```
Alice```

## 样例 #2

### 输入

```
1111```

### 输出

```
Bob```

## 样例 #3

### 输入

```
1010```

### 输出

```
Bob```

## 样例 #4

### 输入

```
1010001011001```

### 输出

```
Alice```

# 题解

## 作者：xiangxiyu (赞：3)

## 思路
$10$ 可以走一步，$100$，$110$，$1010$ 可以走两步，所以只要最后留一步或两步，就赢了，所以 $\texttt{Alice}$ 要保证她走完后要留三步或四步，所以只要 $\texttt{Alice}$ 每次都走到 $3k+1$，$3k+2$ 的位置就可以保证能赢，我们会发现总步数是开始序列中逆序对的个数。
## 举例证明
$100$ 反转后为 $001$，$100$ 有两个逆序对，反转就相当于走了两步，$10$ 有一个逆序对，反转后就为 $01$ 相当于走了一步，最后时答案肯定是连续的 $0$ 连着连续的 $1$，逆序对个数为 $0$，我们只需要统计一下原序列中逆序对的个数，看一下能不能被 $3$ 整除就好了。
#### 提示
逆序对个数最大为长度的平方，要开 long long。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans = 0,k = 0;
signed main() {
    string a;
    cin >> a;
    int n = a.size();
    for (int i=0;i<n;i++){
        if (a[i] == '1')  k++;
	else ans += k;//统计逆序对个数
    }
    if(ans%3!=0) cout<<"Alice";//不能整除 Alice赢
    else cout<<"Bob";//整除 Bob赢
    return 0;
}
```

---

## 作者：xiezheyuan (赞：3)

## 思路

首先我们考虑怎样的局面是无法操作的，也就是找不到 `10`，等价于假如将字符串看成一个序列的话，就是没有逆序对。这引导我们往逆序对考虑。

假设当前逆序对的数量为 $X$，则 `10` 可以减少一个逆序对，其他方法可以减少两个逆序对。

是否对于每一个有至少两个逆序对的字符串，都可以用题面中的方法减少两个逆序对呢？答案是肯定的。假如我们有一个没有逆序对的字符串 $00000\cdots11111\cdots$，然后我们需要让它出现一个逆序对，那么只能交换 $0,1$ 分界线旁的两个元素。然后我们需要出现两个逆序对，那么只有三种决策：

- 将刚刚交换的 $1$ 往前交换，对应 `100`。
- 再交换一个 $1$ 过来，对应 `110`。
- 从有序字符串开始，交换分界线开始第二个元素。对应 `1010`。

这样子就证明了每次操作可以消去一个或两个逆序对。

然后发现这就等价于一个简单的游戏：有 $X$ 个石子，每个人可以拿一个或两个，拿不了的判负。

SG 函数，令 $f(X)$ 表示有 $X$ 个石子的局面的 SG 函数。

然后就有 $f(X)=\operatorname{mex}(f(X-1),f(X-2))$。发现 $f(0)=0,f(1)=1,f(2)=2$，到了 $f(3)$ 时归 $0$，以后是一个循环。

所以 $f(X)=X\bmod 3$。我们就做完了。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

int a1[2], n;
long long ans;
string s;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> s;
    n = s.size(); s = " " + s;
    for(int i=1;i<=n;i++){
        a1[s[i] - '0']++;
        if(s[i] == '0') ans += a1[1];
    }
    cout << (ans % 3 ? "Alice" : "Bob");
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Miracle_1024 (赞：2)

## 思路：
  对于所有操作，都是在把 $1$ 往后移动，使逆序对数量减少。当 $s$ 没有逆序对的时候，游戏结束。

  对于四个操作（$101101001010$ 变为 $010110010101$），分别可以使原串减少 $1$、$1$、$2$、$2$ 个逆序对

  并且对于一个 $01$串，可以转化为只包含：$10$、$110$、$100$、$1010$ 四种情况，其余字符串都可以被转化为只包含 $10$、$110$、$100$、$1010$ 的字符串。

  那我们只需要统计字符串中逆序对的数量，我们发现，对于逆序对的数量 $n$，若 $n \bmod 3 \ne 0$，那么先手都可以利用操作使当前逆序对数量变为 $n \bmod 3 = 0$ 的状态，为必胜态，反之则必败。

## 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll cnt,ans;
string s;
int main(){
    cin>>s;
    for (int i=0;i<s.size();i++){
        if (s[i]=='1')cnt++;
        else ans+=cnt;
    }
    if(ans%3) cout<<"Alice";
    else cout<<"Bob";
}
```

---

## 作者：liuyi0905 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P10737)
首先我们会发现，每次反转 $t$ 中的字符，都是将 $t$ 的逆序对数量减少，当 $s$ 的逆序对数量为 $0$（$s=000\dots111$）时无法操作，因此题意转化为每次将 $s$ 的逆序对数量减少 $1$ 或 $2$，无法操作者失败。

设 $s$ 的逆序对数量为 $r$，
+ 如果 $r$ 不是 $3$ 的倍数，第一次 Alice 减去 $r \bmod3$，之后若`Bob 减 $x$ 个，则 Alice 减 $3-x$ 个，此方案 Alice 必胜。
+ 如果 $r$ 是 $3$ 的倍数，若 Alice 减 $x$ 个，则 Bob 减 $3-x$ 个，此方案 Bob 必胜。

结论：若 $s$ 的逆序对数量是 $3$ 的倍数，则 Bob 胜，否则 Alice 胜。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
string s;
int main(){
	cin>>s;
	LL c=0,r=0;
	for(auto o:s)
		o=='0'?r+=c:c++;
	cout<<(r%3?"Alice":"Bob");
	return 0;
}
```

---

## 作者：will1111 (赞：0)

# P10737 题解

### 思路

显然是博弈论。

我们发现所有可以翻转的子串 $t$ 都是将 $\texttt{1}$ 右移，所有翻转操作都是在减少 $S$ 中的**逆序对**。

当不能操作时，$S$ 中所有 $\texttt{0}$ 都在 $\texttt{1}$ 的左边，此时 $S$ 中不存在逆序对。

进一步发现翻转 $\texttt{10}$ 减少 $1$ 个逆序对，其余都减少 $2$ 个逆序对。

于是问题就转化为，每次减少 $1$ 或 $2$ 个逆序对，没有逆序对时输掉，谁赢的问题。

只需要统计逆序对的数量，若逆序的数量为 $3$ 的倍数，则 $\texttt{Bob}$ 赢，否则 $\texttt{Alice}$ 赢。

统计逆序对的数量时，由于 $S$ 中只包含 $\texttt{0}$ 和 $\texttt{1}$，只需要在读取到 $\texttt{0}$ 时将逆序对总数加上该位之前 $\texttt{1}$ 的数量就可以了。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<string>

using namespace std;


int main()
{
	long long cnt=0,ans=0; // 不开 long lnog 见祖宗。
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='1')
		{
			cnt++; // 统计 1 的数量。
		}
		else
		{
			ans+=cnt; // 统计逆序对的总数。
		}
	}
	if(ans%3!=0)
	{
		printf("Alice\n"); // 若逆序对总数不为 3 的倍数，Alice 赢。
	}
	else
	{
		printf("Bob\n"); // 否则 Bob 赢。
	}
	return 0;
}
```

---

## 作者：__Sky__Dream__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P10737)

## 题目大意
给出一段 $01$ 序列，Alice 和 Bob 可以依次轮流对 `10`，`110`，`100`，`1010` 进行反转，使其变成 `01`，`011`，`001`，`0101`。Alice 先开始操作，谁先无法操作则对手赢得游戏。

## 解题思路
**博弈论。**

我们注意到，所有 $4$ 种可以反转的字串，都是将 $1$ 向串的**右侧**移动，所以结束时，所有的 $0$ 都在 $1$ 的**左侧**。继续观察操作序列，发现每一次操作，都可以使整个串的 $01$ 逆序对（我们将 $0$ 在 $1$ 左侧定义为正序）数量减少 $1$ 或 $2$。所以我们统计所有的逆序对，这道题就变成了一个**巴什博弈**，将逆序对 $\bmod 3$ 即可得到答案。

## AC Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void dfs()
{
	string s;
	cin>>s;
	int n=s.length();
	s=" "+s;
	ll sum=0;
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='1') ans++;
		else sum+=ans;
	}
	if(sum%3==0) cout<<"Bob";
	else cout<<"Alice";
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0); 
	dfs();
	return 0;
}
```

创建和谐洛谷，拒绝代码抄袭！

---

## 作者：sangshang (赞：0)

# Preface

纯思维题，完全不需要代码能力。

# Solution

观察所给的可以翻转的字符串，发现其大致呈显 1 后面跟着些 0；翻转后变成 0 后跟着些 1。

再仔细观察，注意到因为 $\texttt{10}$ 可以翻转的，所以字符串翻转到最后，一定是前缀一堆 0，后缀一堆 1 这种模式。因此，我们可以感性地把将字符串翻转到不能再翻转理解为将所有 1 搬运到字符串尾部。把翻转 $\texttt{10}$ 理解为将单独的 1 向后搬一格，定义为一步，此时所需的步数是确定的。

再观察 $\texttt{110,100,1010}$ 与 $\texttt{10}$ 之间的关系，发现翻转 $\texttt{110,100,1010}$ 都可以转化为两次翻转 $\texttt{10}$，也可以理解为一次走两步。

假设除了步数只剩一步，一定可以一次走一步或一次走两步，设总步数是 $x$，定义倒数第 $k$ 步是再走 $k$ 步将字符串翻转到不能再翻转，步数定义同上。

1. Alice 希望自己走最后一步，Bob 则希望不要让 Alice 走最后一步。

2. 从 Alice 的角度出发。如果 Alice 走了倒数第二步，然后换 Bob，那 Bob 一定会走最后一步，所以 Alice 不希望自己走到倒数第二步。

3. 如果 Alice 走到倒数第三步，Bob 只需一次走两步就可以走最后一步。所以，Alice 也不希望自己走到倒数第三步。

4. 如果 Alice 走到倒数第四步，让 Bob 从第三步走，那 Alice 就必胜。所以 Alice 同样希望自己走到第四步。

想到这里，重复上述思路，我们就知道了。只要 Alice 能让 Bob 从倒数第 $3k(k\in \mathbb N)$ 步走，Alice 就能让自己每次都走到 $3k+1$ 步，获得胜利。 

因此若 $x\ \bmod\ 3=1\ \text{or}\ 2$，Alice 就能通过一次走一步或两步，让 Bob 从倒数第 $3k$ 步走。否则当 $x\ \bmod\ 3=0$，Alice 不论一次走一步或两步，Bob 都能走到倒数第 $3k+1$ 步，让 Alice 从倒数第 $3k$ 步走，Bob 就必胜。

证明除了步数只剩一步，一定可以一次走一步或两步。

>将所有去掉后缀一堆 1 和前缀一堆 0 字符串概括为  
>111...($u_1$ 个 1)000...($v_1$ 个 0)............(一堆 1 和一堆 0)111...($u_n$ 个 1)000...($v_n$ 个 0)
>
>容易发现，只要 $\max_{1\le i\le n}\{u_i,v_i\}>1$，就一定有一个位置可以用 $\texttt{100,110}$ 之一翻转，也就是一次走两步。
>
>否则 $\max_{1\le i\le n}\{u_i,v_i\}=\min_{1\le i\le n}\{u_i,v_i\}=1$，此时若 $n>1$，那一定可以用 $\texttt{1010}$ 翻转，也是一次走两步。
>
>综上所述，只有 $n=1,u_1=v_1=1$ 是不可以用 $\texttt{100,110,1010}$ 之一翻转，此种情况对应只剩一步可以走。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
char str[maxn];

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> (str + 1);
	int len = strlen(str + 1), cnt = 0;
	long long sum = 0;
	for (int i = len; i >= 1; --i) {
		if (str[i] == '1') {
			sum += len - i - cnt, ++cnt;
		}
	}
	if (!(sum % 3)) {
		cout << "Bob";
	} else {
		cout << "Alice";
	}
	return 0;
}
```

代码很短很简单，就是注意 $sum$ 是 $O(len^2)$ 级别的，要开 `long long`。

---

## 作者：gh_AC (赞：0)

## 思路：

经过观察我们可以发现能翻转的数都是以 $1$ 开头的，在 $0$ 都在前面，$1$ 都在后面时就不能再反转了，下一步操作的人就输了。

我们就可以算出将所有 $1$ 都转移到最右边的步数，然后再判断谁赢了就很容易了。

## 代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string a;
long long sum,s;
int main(){
	cin>>a;
	for(int i=0;i<a.length();i++){
		if(a[i]=='1') s++;
		else sum+=s;
	}
	if(sum%3==0) cout<<"Bob";
	else cout<<"Alice";
	return 0;
}
```

---

## 作者：queenbee (赞：0)

# P10737 Reverse Game题解
## 思路
[题目传送门](https://www.luogu.com.cn/problem/P10737)，已知有四种子串可以反转，分别为 `10`、`100`、`110`、`1010`，观察到每个字符串中均含有子串 `10`，所以先对 `10` 进行分析，得出只要有 `0` 在 `1` 后即可进行操作，所以最后不可操作的字符串形式一定为 `0000……1111……`。获胜条件即为优先将全部 `0` 移动到字符串左方。

再对其他字符串进行分析，`10`、`1010` 转化均是将 `0` 向左移动一格，`100`、`110`则是将 `0` 向左移动两格，这四种字符串包含了将 `0` 向左移动 1 或 2 格的所有情况。而后手则可以保证每次向左移动 3 格，所以如果所有 `0` **需要移动的距离**为 3 的倍数，则后手必胜，否则先手必胜。

`0` 需要移动的距离：距离字符串左方最近的 `0` 最终会移动到字符串的第一位，第二近的则会移动到第二位，以此类推。其与目标位置的距离即为 `0` 需要移动的距离。

## 程序
```
#include<bits/stdc++.h>	//我爱万能头 
using namespace std;
string s;
long long cnt,sum;	//记得开long long 
int main(){
	cin>>s;
	for(int i=0;i<s.length();i++){	
		if(s[i]=='0'){
			sum+=i-cnt;	//计算0需要移动的距离 
			cnt++;	//计算0的数量 
		}
	}
	if(sum%3!=0){	//判断输出结果 
		puts("Alice");
	}
	else{
		puts("Bob");
	}
	return 0;	//完结撒花 
} 
```

---

## 作者：封禁用户 (赞：0)

#### 大致题意
给出一段 01 序列，Alice 和 Bob 可以依次轮流对 `10`，`110`，`100`，`1010` 进行反转，使其变成 `01`，`011`，`001`，`0101`。Alice 先开始操作，谁先无法操作则对手赢得游戏。
#### 思路
设逆序对数为 $X$，每次操作可以减少一个或两个逆序对。具体来说，交换 `10` 可以减少一个逆序对，其他方法可以减少两个逆序对。

我们可以定义 SG 函数 $f(X)$ 表示有 $X$ 个逆序对，而 SG 函数的递推关系是 $f(X)=\text{mex}(f(X-1),f(X-2))$，其中 $\text{mex}$ 表示最小排除值。

又通过计算，发现 $f(0)=0$，$f(1)=1$，$f(2)=2$，$f(3)=0$，此后为循环。也就是说，$f(X)=X\ \text{mod}\ 3$。且根据 SG 函数的性质，如果 $f(X)=0$
，则当前局面为必败局面，反之亦然。

于是我们可以计算逆序对数量并 $\text{mod}\ 3$ 得出结果。

#### 代码
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    long long ans = 0;
    int count_1 = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            count_1++;
        } else {
            ans += count_1;
        }
    }//计算逆序对数
    cout << (ans % 3 ? "Alice" : "Bob") << endl;
    return 0;
}
```
#### Updated：计算逆序对数的小寄巧
一般的计算逆序对数：$O(n^2)$
```cpp
for (int i = 0; i < s.size(); ++i) {
	for (int j = i + 1; j < s.size(); ++j) {
		if (s[i] > s[j]) {
			++count;
		}
	}
}
```
$\texttt{42}$ 分，考虑优化。

我们可以先遍历字符串 $s$ 的每一个字符，如果当前字符是 `1`，则将计数器加一；如果当前字符是 `0`，则将计数器的值加入 `ans` 中，这是因为当前的 `0` 与之前出现的所有 `1` 构成了逆序对。

按照上述思路便有了 $O(n)$ 算法：
```cpp
for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
        count_1++;
    } else {
        ans += count_1;
    }
}

```

---

