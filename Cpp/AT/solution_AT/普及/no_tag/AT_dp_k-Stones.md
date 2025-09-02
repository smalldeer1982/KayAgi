# Stones

## 题目描述

$N$ 个正整数组成的集合 $A = \{ a _ 1, a _ 2, \ldots, a _ N \}$。太郎君和次郎君将用以下游戏进行对决。

首先，准备一个有 $K$ 个石子的堆。两人依次进行以下操作。太郎君先手。

- 从集合 $A$ 中选择一个元素 $x$，从石堆中恰好移除 $x$ 个石子。

不能进行操作的人输掉游戏。当两人都按照最优策略行动时，判断谁会获胜。

## 样例 #1

### 输入

```
2 4
2 3```

### 输出

```
First```

## 样例 #2

### 输入

```
2 5
2 3```

### 输出

```
Second```

## 样例 #3

### 输入

```
2 7
2 3```

### 输出

```
First```

## 样例 #4

### 输入

```
3 20
1 2 3```

### 输出

```
Second```

## 样例 #5

### 输入

```
3 21
1 2 3```

### 输出

```
First```

## 样例 #6

### 输入

```
1 100000
1```

### 输出

```
Second```

# 题解

## 作者：信守天下 (赞：12)

## [洛谷传送门](https://www.luogu.com.cn/problem/AT4532)
## [AT 传送门](https://atcoder.jp/contests/dp/tasks/dp_k)
## 思路
状态设计为 $f[i]$，表示在剩余 $i$ 块石头时，当前操作者的胜负。

显然，状态 $f[i]$ 可以转移到 $f[i + a[j] (1 \leqslant j \leqslant n)$。

有一个显然的结论：在剩余 $0$ 块石头时，当前操作者必败。

那么，如果一个状态能转移到一个必败状态，那么当前操作者一定必胜。

当前操作者只需要选择转移到那个使对手必败的状态，就可以让自己必胜。

所以我们可以从 $f[1]$ 开始递推求解，最终答案为 $f[k]$。
## code
~~~cpp
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
int n, k;
int a[kMaxN];
bool f[kMaxN];
int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++) {
      f[i] += i - a[j] >= 0&& !f[i - a[j]];
    }
  }
  cout << (f[k] ? "First" : "Second");
  return 0;
}
~~~

---

## 作者：Bpds1110 (赞：8)

### Preface:
[**原题传送门**](https://www.luogu.com.cn/problem/AT_dp_k)

早已写完最后一篇题解了。~~只因这题太水。~~

给出长度为 $N$ 的正整数序列 $a$，和一个整数 $K$，双方每次从 $a$ 中取出一个整数 $a_i$，$1 \le i \le N$，并把 $K - a_i$，当一方无法操作时，另方获胜。求出在最优策略下，哪方可以获胜。
### Solution:
显然是 $dp$。

- **状态**：$dp_i$ 表示取出总和为 $i$ 时，先取的一方是否能获胜。
- **转移方程**：显然，我们设 $1 \le j \le N$，如果对方对于取 $i - a_j$ 的和可以获胜，那么本方对于取 $i$ 一定能获胜，否则一定不能。于是得出方程。

$dp_i = \begin{cases}1,dp_{i - a_j} = 0\\0,dp_{i - a_j} = 1\end{cases}$

- **初值**：先取的一方在取和为 $0$ 时必输，$dp_0 = 0$。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1;
int n, k, dp[N], a[N];
int main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
	dp[0] = 0;
	for(int i = 1; i <= k; i ++) //枚举当前取得的总和 
		for(int j = 1; j <= n; j ++) //枚举dp[i]是否可以通过dp[i-a[j]]所得1 
		{
			if(i - a[j] < 0) continue ; //越界判断 
			dp[i] |= (dp[i - a[j]] == 0); //状态转移方程，满足其一即可 
		}
	cout << (dp[k] ? "First" : "Second");
}

```

---

## 作者：Haphyxlos (赞：7)

# AT4532
[题目传送门](https://www.luogu.com.cn/problem/AT4532)

很显然，这是道博弈论的题目，这里有以下几个结论：

 1. 剩余$0$块石头时，当前操作者必败。 
 
 2. 如果可以使得对手必败，那么当前操作者必胜。
 
 3. 反之，如果不论进行何种操作对手都将必胜，那么当前玩家只能认输。
 
**那么我们设$dp[i]$表示还剩$i$块石头时，当前操作者是否必胜，那么 $dp[i]$为必 胜当且仅当存在$i≥a_j$且$dp[i$-$a_j]$为必败。**

**ACcode如下：**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
bool dp[maxn];	
int n,k,a[maxn];
int main(int argc,char const *argv[]){
	std::ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>a[i];
	dp[0]=false;	//终局必败 
	for(int i=1;i<=k;++i){
		dp[i]=false;//默认必败 
		for(int j=1;j<=n;++j){
			//结论2 
			if(i>=a[j]&&dp[i-a[j]]==false)dp[i]=true;
		}
	}
	puts(dp[k]?"First":"Second");
	return 0;
}
```

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：YCSluogu (赞：5)

貌似没有人用记忆化搜索来写这道题……而且没有把跟博弈论相关的东西讲的很清楚。
(等会这样和DP有区别吗)

首先我们要明确一个事情：他们所做的一切决策都是最优策略。也就是说，
只要由当前状态所转移出的状态中，有取胜的情况，那么就一定会胜利。  
好比走迷宫，如果走这条路会到终点，那么一定会走下去。

对于当前状态 $(now, win)$，可以有 $(now + a_j, win')$。如果 win' = false，
由于双方采用最优策略，那么 win 一定为 true。假如当前为 A 出手，收走 $a_j$ 个石子后 B 可能会输，那么 A 就一定会赢

然后再写个记忆化：AC到手

AC代码：
``` cpp
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1e6;

int p[MAXN];
int a[MAXN], n;
int Sum;

bool dfs(int now) {
    if (~p[now]) {
        return p[now] % 2;
    }
    for (int i = 1; i <= n; i++) {
        if (now - a[i] >= 0 && !dfs(now - a[i])) {
            return (p[now] = 1) % 2;
        }
    }
    return (p[now] = 2) % 2;
}

int main() {
    memset(p, -1, sizeof(p));
    cin >> n >> Sum;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << (dfs(Sum) ? "First" : "Second");
    return 0;
}
```


---

## 作者：Gloaming (赞：3)

## 分析

这道题是一道博弈论的题目，但是那个东西太难了，本蒟蒻不会，所以就用一个类似DP的东西做这道题。

我们先考虑一个极限的情况：当前一块石头都没有，所以我们的先手必败，进一步推广后，如果第$i$颗棋子先手必败，那么第$i+a_j(1\leq j\leq n)$颗棋子先手必胜，这就类似于一个DP

换一种写法就是$dp_i=!dp_{i-a_j}$，代码就可以轻松地写出来了。

## Code
```c++
#include <bits/stdc++.h>
using namespace std;
const int MAXK = 100000 + 10;
int n, k, dp[MAXK], a[100 + 10];
int main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i ++)
	{
		cin >> a[i];
	}
	dp[0] = 0;
	for(int i = 1; i <= k; i ++)
	{
		for(int j = 1; j <= n; j ++)
		{
			if(i - a[j] < 0) continue;
			if(dp[i - a[j]] == 0) dp[i] = 1;
		}
	}
	if(!dp[k]) cout << "Second";
	else cout << "First";
	return 0;
}
```

---

## 作者：_JF_ (赞：3)

# **AT4532 Stones**

这个题实际上还是DP

## 大体思路

设 $dp[i]$ 表示当前的人是输还是赢 对从$1-k$的东西进行处理 最后输出我们要的 $dp[k]$ 即可

如果 $dp[i-a[j]]$ 为 $false$ （就是取了）的话，证明取了这一步对手必败 所以对于当前的 $i$ 来说，他就有必胜策略，所以他就 $100%$ 赢了 这时的 $dp[i]$ 就是 $true$ 了

所以整合思路，可以得到最重要的东西

 $dp[i]=true(i\geq a[j]\quad and\quad dp[i-a[j]]=false)$
 
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int a[N];
bool dp[N];
int main()
{
	long long  n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	dp[0]=false;// 初始化为失败
	for(int i=1;i<=k;i++)
	{
		dp[i]=false;//一开始默认失败
		for(int j=1;j<=n;j++)
		{
			if(i>=a[j]&&dp[i-a[j]]==false) dp[i]=true;
		}
	}
	if(dp[k]==true)
		cout<<"First";
	else
		cout<<"Second";
	return 0;
}
```


---

## 作者：kimi0705 (赞：2)

# Description
如果当前玩家没有石头可以取的话，那么他的对手获胜。
如样例 1：
```
2 4
2 3
```
四个石头，可以拿 $2,3$。
先手拿了 $3$ 后手只能拿 $2,3$，但只剩下 $1$，什么也拿不了，所以先手 win。
如样例 2：
```
2 5
2 3
```
四个石头，可以拿 $2,3$。
先手拿了 $3$ 后手只能拿 $2,3$，但只剩下 $2$，可以拿 $3$，先手就不能拿了，所以后手 win。
# Solution
## 构造
因为题目问的是有 $k$ 个石头时，谁赢。
所以很自然得想到设 $dp_i$ 为石头个数为 $k$ 时的答案，$dp_i = 0$ 时后手赢。
## 初值
$dp_0 = 0$。
## 终值
$dp_n$。
## 动态转移方程
因为**双方都以最优策略行动**，所以只要有一个方案能让他赢，他一定能赢。

那是什么时候能赢呢，在他拿了 $arr_x$ 个石头后，后手赢的时候，因为他拿完他就变成了“后手”了。
## code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
bool f[100005];
int arr[100005];
int main() {
	cin >>  n >> k;
	for (int i = 1; i <= n ; i++) cin >> arr[i];
	for (int i = 1; i <= k; i++) { // 枚举每个石头数的方案
		for (int j = 1; j <= n; j++) {
			if (arr[j] <= i) {
				if (!f[i - arr[j]]) {
					f[i] = 1;
					break;
				}
			}
		}
	}
	if(f[k]) cout << "First";
	else cout << "Second";
}
```

---

## 作者：diqiuyi (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT4532)

**题意**

正如题目所说的那样。

但要注意一下胜利条件，如果当前玩家没有石头可以取的话，那么他的对手获胜。

**思路1**

这题还是有些递推式的。设一个布尔型变量 $f_i$ 表示剩下 $i$ 个石头的时候先手能否取胜。显然，如果能取到一个**对方处于必败**的局面，那么当前局面就是必胜的。也就是说，如果有某个 $a_j$ 使得 $f_{i-a_j}=0$，那么显然有 $f_i=1$。复杂度为 $O(nk)$。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
bool f[100010];
int a[105],k,n;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++)
			if((a[j]<=i&&!f[i-a[j]])){
           			//防止越界
				f[i]=1;
				break;
			}
	cout<< (f[k]?"First":"Second") <<endl;
	return 0;
}
```

**思路2**

既然递推式有了，那么搜索也可以做。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105],k,n;
bool dfs(int x){
    if(!x)
        return 0;
    for(int i=1;i<=n;i++)
        if(x>=a[i]&&!dfs(x-a[i]))
            return 1;
    return 0;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cout<< (dfs(k)?"First":"Second") <<endl;
	return 0;
}
```
喜获 TLE。

**思路3**

记忆化搜索。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
int F[1000005];
int a[105],k,n;
int dfs(int x){
    if(F[x]!=-1)
        return F[x];
    if(!x)
        return 0;
    for(int i=1;i<=n;i++)
        if(a[i]<x&&!dfs(x-a[i]))
            return F[x]=1;
    return F[x]=0;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i],F[a[i]]=1;
    memset(F,-1,sizeof(F));
	cout<< (dfs(k)?"First":"Second") <<endl;
	return 0;
}
```
~~然后又挂掉了。~~

**思路4**

看着思路 $1$ 的解法，我想到了一个小优化。就是因为数组 $a$ 是有序的，所以如果 $a_j > i$ 可以提前退出循环。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
bool f[100010];
int a[105],k,n;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++){
        		if(a[j]>i)
                		break;
			if(!f[i-a[j]]){
				f[i]=1;
				break;
			}
          	}
	cout<< (f[k]?"First":"Second") <<endl;
	return 0;
}
```
~~然而似乎并没有变快多少。~~

总的来说这题方法很多，感觉难度给高了。

---

## 作者：Phartial (赞：2)

定理 $1$：当石子数量为 $0$ 时先手必败。

显然。

定理 $2$：若当前局势**能**转到任何一个先手必败的局势则先手必胜。

此时先手可以通过转到先手必败的局势来获胜。

定理 $3$：若当前局势**无法**转到任何一个先手必败的局势则先手必败。

此时先手无论转到哪个状态都会使对手必胜。

---

设 $f_i$ 表示还剩下 $i$ 颗石子时先手是否必胜。

显然 $f_0=0$，而由上可知 $f_i=1$ 当且仅当 $i\ge a_j$ 且 $f_{i-a_j}=0$。

由 $1$ 开始往后递推即可，最终答案为 $f_k$。

```cpp
#include <iostream>

using namespace std;

const int kN = 101;
const int kK = 1e5 + 1;

int n, k, a[kN];
bool f[kK];

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= n; ++j) {
      f[i] |= i >= a[j] && !f[i - a[j]];
    }
  }
  cout << (f[k] ? "First" : "Second");
  return 0;
}

```


---

## 作者：Doqin07 (赞：2)

我们可以非常显然的知道：

1. 剩余 0 块石头时，当前操作者必败  

2. 如果可以使得对手必败，那么当前操作者必胜  

3. 反之，如果不论进行何种操作对手都将必胜，那么当前玩家只能认输

那么我们可以设 $dp[i]$ 表示还剩 $i$ 块石头时，当前操作者是否必胜，那么 $dp[i]$ 为**必胜**当且仅当存在 $i \ge a_j$ ，且 $dp[i-a_j]$ 为**必败**

-----

代码：
```cpp
/*Coder:DongYinuo*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7;
#define F(i, l, r) for (int i = l; i <= r; ++i)
#define REP(i, r, l) for (int i = r; i >= l; --i)
#define mem(a,b) memset(a, b, sizeof(a));
#define MP make_pair
#define PB push_back
#define PII pair<int, int>
#define PLL pair<ll, ll>
#define all(a) begin(a), end(a)
#define sz(a) ((int)a.size())
#define lson ind * 2 
#define rson ind * 2 + 1

namespace IO{
    int I(){
        char c; int x = 0, f = 1;
        while (c = getchar()){ if (c == '-') f = -1;if (isdigit(c)) break;}
        while (isdigit(c)){ x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();}
        return x * f;
    }
    template <typename T>
    void Rd(T& arg){
        arg = I();
    }
    template <typename T, typename...Types>
    void Rd(T& arg, Types&...args){
        arg = I();
        Rd(args...);
    }

    ll L(){
        char c; int x = 0, f = 1;
        while (c = getchar()){ if (c == '-') f = -1;if (isdigit(c)) break;}
        while (isdigit(c)){ x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();}
        return x * f;
    }
    template <typename T>
    void RLd(T& arg){
        arg = L();
    }
    template <typename T, typename...Types>
    void RLd(T& arg, Types&...args){
        arg = L();
        Rd(args...);
    }

    void test(int x){
        cout << x << " ";
    }
    template <typename T>
    void debug(T& arg){
        test(arg);
    }
    template <typename T, typename...Types>
    void debug(T& arg, Types&...args){
        test(arg);
        debug(args...);
    }
}
using namespace IO;

#define test 
const int N = 1e6 + 6;

namespace SOLVE{
    int n, k, a[N], dp[N];

    void main(){
        Rd(n, k);
        F (i, 1, n){
            Rd(a[i]);
        }
        dp[0] = 0;
        F (i, 1, k){
            dp[i] = 0;
            F (j, 1, n){
                if (i >= a[j] && dp[i - a[j]] == 0){
                    dp[i] = 1;
                }
            }
        }
        puts(dp[k] == 1 ? "First" : "Second");
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while (t--){
        SOLVE::main();
    }
    return 0;
}
```


---

## 作者：nitianyi (赞：1)

# 题目大意
有 $K$ 个石子，双方轮流取石子，每一次取的石子数必须是集合 $A$ 中的一个数，双方都以最优策略行动，判断先手必胜还是后手必胜。

当一名玩家无法操作时，另一名玩家获胜。



# 思路
用 $f[i]$ 表示还剩 $i$ 块石头时正在操作的人的胜负情况（$1$ 表示必胜，$0$ 表示必输），显然 $f[0]=0$，且若 $f[i-a[j]]=0$ 则 $f[i]=1$, 若 $f[i-a[j]]=1$ 则 $f[i]=0$。通过以上分析，可以以 $f[0]=0$ 为起始，再双重循环对 $f[i]$ 赋值，最后输出 $f[k]$ 对应的胜负情况即可。
# 代码
```c
#include<bits/stdc++.h>
using namespace std;
int n,k,a[110];
bool f[100010];  //f[i]表示还剩i块石头时正在操作的人的胜负情况
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	f[0]=0;  //从f[0]开始赋值
	for(int i=1;i<=k;++i){
		for(int j=1;j<=n;++j){
			if(i-a[j]<0)continue; //若i-a[j]<0则跳过
			if(f[i-a[j]]==0){
				f[i]=1;  //若f[i-a[j]]=0则f[i]=1
				break;  //找到必胜策略就退出当前循环
			}
			else f[i]=0; //若f[i-a[j]]=1则f[i]=0,继续寻找必胜策略
		}
	}
	if(f[k]==1)printf("First");  //f[k]=1说明先手必胜
	else printf("Second");  //f[k]=0说明后手必胜
	return 0;
}
```












---

## 作者：luogu_gza (赞：0)

我们考虑先手是有**优先权**的，所以我们定义状态为 $f_i$，表示还剩 $i$ 块石头的时候当前操作的人是否必胜。

那么，考虑一次取石头，就可以转化胜负，那么转移方程就呼之欲出了。

$$f_{j+a_i}=f_{a_i}\oplus 1$$

但是，如果有多种情况导向一种剩余石子个数，那么其实因为先手是有**优先权**的，所以其中如果有一种是先手必胜的，那么这个状态就是先手必胜的。

早期代码，不喜勿喷。

[code](https://www.luogu.com.cn/record/94555569)

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_dp_k)

## 思路

由题目可以推导出如下几条结论：

- 当剩余的石头为数为 $0$，当前操作者必败。
- 如果对手必败，或**可以**转化为对手必败的转移方程，则当前操作者必胜。
- 如果对手必胜，或**不可以**转化为对手必败的转移方程，则当前操作者必败。

于是想到我们可以用 bool 类型定义 dp 数组，并把它转化为背包问题求解。

定义一个 bool 类型数组 $dp$，$dp_i$ 表示当在剩余 $i$ 块石头时当前操作者胜负。从 $1$ 到 $n$ 二重循环判断拿去不同数量石子后能否转化为对手必败的转移方程，如果能就跳出循环并把 $dp_i$ 赋值为“对手必败”的值；如果不能就把 $dp_i$ 赋值为“对手不败”的值。当循环完成后 $dp_m$ 不为“对手必败”，即无法转化为对手必败的转移方程，则当前操作者（先手）必败，输出 ``Second``，反之输出 ``First``。

- 在剩余石子数不够要拿去的数量时，跳过。
- 别忘最后输出换行。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,a[N];
bool flag,dp[N];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(int i=1;i<=m;++i){
        flag=0;//别忘归零。
        for(int j=1;j<=n;++j){
            if(i<a[j])continue;//不够就跳过。
            if(dp[i-a[j]]==0){
                flag=1;
                break;
            }
        }
        dp[i]=flag;
    }
    if(dp[m])cout<<"First\n";
    else cout<<"Second\n";
    return 0;
}

~~~

---

## 作者：xcrr (赞：0)

经典博弈论 DP。设 $sg_i= \left \{1/0  \right \} $，$sg_i=0$ 表示剩余 $i$ 块石头，当前决策者必败；$sg_i=1$ 表示剩余 $i$ 块石头，当前决策者必胜。我们要求的就是 $sg_k$。

考虑一个状态：当前状态能通过一步操作到必败状态，那这个状态就是必胜态；当前状态不能通过任何一步操作到任何必败状态，那么它就是必败态。

实际也不难理解，当你决策时，你肯定将当前石子取走一部分，将剩下的石子给对方时，让对方必败；如果取走任何一种数量的石子，对方都必胜，那么你就必败了。

为了清晰好写，可以用记忆化搜索的方式。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;
int a[105],_sg[100005];//0先手必败 1先手必胜

bool sg(int x)
{
	if(_sg[x]!=-1)return _sg[x];
	for(int i=1;i<=n;i++)
	{
		if(x-a[i]<0)continue;
		if(sg(x-a[i])==0)
			return _sg[x]=1;
	}
	return _sg[x]=0;
}

int main()
{
	cin>>n>>k;
	

	memset(_sg,-1,sizeof _sg);
	for(int i=1;i<=n;i++) cin>>a[i];
	_sg[0]=0;

	
	if(sg(k))cout<<"First";
	else cout<<"Second";

	return 0;
}
```

---

