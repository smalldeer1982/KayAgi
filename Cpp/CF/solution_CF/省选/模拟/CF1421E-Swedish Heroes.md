# Swedish Heroes

## 题目描述

While playing yet another strategy game, Mans has recruited $ n $ [Swedish heroes](https://www.youtube.com/watch?v=5sGOwFVUU0I), whose powers which can be represented as an array $ a $ .

Unfortunately, not all of those mighty heroes were created as capable as he wanted, so that he decided to do something about it. In order to accomplish his goal, he can pick two consecutive heroes, with powers $ a_i $ and $ a_{i+1} $ , remove them and insert a hero with power $ -(a_i+a_{i+1}) $ back in the same position.

For example if the array contains the elements $ [5, 6, 7, 8] $ , he can pick $ 6 $ and $ 7 $ and get $ [5, -(6+7), 8] = [5, -13, 8] $ .

After he will perform this operation $ n-1 $ times, Mans will end up having only one hero. He wants his power to be as big as possible. What's the largest possible power he can achieve?

## 说明/提示

Suitable list of operations for the first sample:

 $ [5, 6, 7, 8] \rightarrow [-11, 7, 8] \rightarrow [-11, -15] \rightarrow [26] $

## 样例 #1

### 输入

```
4
5 6 7 8```

### 输出

```
26```

## 样例 #2

### 输入

```
5
4 -5 9 -2 1```

### 输出

```
15```

# 题解

## 作者：青君 (赞：7)

## Description 
长度为 $n$ 的数列 $\big<a_i\big>$，一次操作可以把两个相邻的数 $a_i$ 与 $a_{i+1}$ 合并成 $-(a_i+a_{i+1})$，请最大化 $n-1$ 次操作后剩下的数。   
$1\le n\le 200000,-10^9\le a_i \le10^9$  

## Solution  
所有操作相当于给每个数前面分配一个 `+` 或 `-`，然后加起来。  

很容易想到一个 $\Theta(n^3)$ 的区间DP，设 $f_{l,r}$ 表示合并 $[l,r]$ 中的数后能得到的最大值，$g_{l,r}$ 表示合并 $[l,r]$ 中的数后能得到的最小值，有转移
$$f_{l,r}=\max_{l\le i < r}\{-(g_{l,i}+g_{i+1,r})\}$$
$$g_{l,r}=\min_{l\le i < r}\{-(f_{l,i}+f_{i+1,r})\}$$
~~然而这一点儿用都没有~~，没有任何优化余地。

~~凭经验可知~~我们一定少了什么observation ，是否所有合法的分配方案都满足一个简单的性质呢？

观察一下  
$n=1$ ；  
$n=2$ `--`；  
$n=3$ `++-`，`-++`；  
$n=4$ `----`，`+---`，`-+--`，`--+-`,`---+`；  
……

（我也不知道要多敏锐的洞察力才能）发现：  
设 `-` 的个数为 $p$ ，`+` 的个数为 $q$，则  
$$2p+q\equiv1\pmod{3}$$  

证明用归纳法，假设 $n$ 成立，新合并一个数后，$p'=q+1$，$q'=p$，那么
$$2A=2*(2p'+q')\equiv4q+4+2p\pmod{3}$$

因为 $2p+q\equiv1\pmod{3}$
$$2A\equiv3q+5\pmod{3}$$
$$2A\equiv2\pmod{3}$$
$$A\equiv1\pmod{3}$$  
故 $n+1$ 也成立。

但是别高兴得太早，这只是合法方案的必要条件，不是充分条件。事实上有这样一个corner case：类似`+-+-...` 或者 `-+-+...` 这样加减交错的情况一定是不合法的，因为第一次操作的两个数最后符号一定相同。

整理一下，合法的分配方案满足：  
1. $2p+q\equiv1\pmod{3}$；
2. 至少存在一对相邻且符号相同的数。

根据这两点设计一个DP:  
设 $f_{i,j,0/1,0/1}$ 表示考虑了前 $i$ 个数，$2p+q\equiv j\pmod{3}$，第 $i$ 个数的符号为 `-`或`+`，否/是存在至少一对相邻且符号相同的数，的答案。  
转移枚举 $a_i$ 的符号：  
$$f_{i+1,(j+2)\bmod3,0,t|(k==0)}\gets f_{i,j,k,t}-a_{i+1}$$
$$f_{i+1,(j+1)\bmod3,1,t|(k==1)}\gets f_{i,j,k,t}+a_{i+1}$$    
边界 $f_{1,2,0,0}=-a_1,f_{1,1,1,0}=a_1$。  
$\Theta(n)$。

## Comment
为我们提供了一种找规律的方向：**观察模性质**。

## Code

```cpp
#include<bits/stdc++.h> 
#define mk make_pair
#define pk push_back 
using namespace std;
typedef long long LL;
typedef pair<int,int> pi;
template<class T> bool cmax(T &x,T y){return y>x?x=y,1:0;}
template<class T> bool cmin(T &x,T y){return y<x?x=y,1:0;}
const int N=2e5+5;
int n,a[N];
LL f[N][3][2][2];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	if(n==1){
		cout<<a[1]<<endl;
		return 0;
	}
	memset(f,-0x3f,sizeof f);
	f[1][2][0][0]=-a[1];
	f[1][1][1][0]=a[1];
	for(int i=1;i<n;++i)
		for(int j=0;j<3;++j)
			for(int k=0;k<2;++k)
				for(int t=0;t<2;++t)
					cmax(f[i+1][(j+2)%3][0][t|(k==0)],f[i][j][k][t]-a[i+1]),
					cmax(f[i+1][(j+1)%3][1][t|(k==1)],f[i][j][k][t]+a[i+1]);
	cout<<max(f[n][1][0][1],f[n][1][1][1])<<endl;
	return 0;
}
```


---

## 作者：王鲲鹏 (赞：4)

首先可以发现每个数 $x$ 对答案的贡献是 $\pm 1 x$。~~比赛时我就是想不到..想了半天贪心~~

转化成在一定限制下，选出一部分数有正贡献，一部分有负贡献。

记数列长度为 $n$，其中 $a$ 个是负贡献。限制1就是 $n+a \equiv 1 \pmod{3}$。（证明在后面，先说做法

限制2是一种特殊情况. 因为 `+-+-+...+` ，也可以满足限制1，但是没法做出来。因为最开始选的两个数的符号一定是相同的，所以完全的交替是不能出现的。

于是可以简单dp。设 `dp[i][j][0/1]` 表示考虑了前 $i$ 个数，当前 $i+a \equiv j\pmod 3$，现在前缀是否是 `+-+-...+` ，可以取得的最大值。（或类似的设成 $n+a \equiv j \pmod 3$）


##### 证明：
类似归纳法，首先看到对于 $n=1,2,3$ 的情况是显然满足的。
对任意一个 $n \ge 4$，考虑它的最后一步一定是
* 一个合法的状态$(n_1+a_1)$ 和 另外一个合法状态$(n_2+a_2)$ 的组合。
$-[(n_1+a_1)+(n_2+a_2)]\equiv -(1 + 1)\equiv 1 \pmod 3$。



代码：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int n = 0;
int a[200005];
ll f[200005][3][2];
inline void update(ll &x, ll y) { if (y > x) x = y; }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	if (n == 1) {
		printf("%d", a[1]);
		return 0;
	}
	memset(f, -0x3f, sizeof(f));
	f[0][0][1] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= 2; j++) {
			update(f[i + 1][(j + 2) % 3][0], f[i][j][0] - a[i + 1]);
			update(f[i + 1][(j + 1) % 3][0], f[i][j][0] + a[i + 1]);
			update(f[i + 1][(j + 2) % 3][(i & 1)], f[i][j][1] - a[i + 1]);
			update(f[i + 1][(j + 1) % 3][!(i & 1)], f[i][j][1] + a[i + 1]);
		}
	printf("%lld", f[n][1][0]);
	return 0;
}
```


---

## 作者：Crosser (赞：1)

有点观察但是绝对没有 2k7 的题。我觉得这个最多 2k4。

首先真的会想到区间 dp，看到数据范围就摆了。但是我们不难发现符号序列应该满足：

- 存在两个连着的同号。
- 设正号数量为 $p$，则 $n+p-2$ 为 $3$ 的倍数。

然后 $dp[i][p \bmod 3][\text{last}][第一条满足]$ 就可以 $\mathcal O(n)$ 算了。到这里我们就做完了，但是为什么这个结论是对的呢？

注：以下所提深度，满足根节点深度为 $1$。

**必要性：**

首先我们可以把整个操作序列变成一棵二叉苹果树。某个节点深度的奇偶即决定了其最终正负。考虑二叉苹果树的性质，那么一定会存在至少一对相邻节点深度相同，其有同一个父亲。

其次就是 $(n+p)\bmod 3=2$ 的证明。我们考虑对于一个奇深度的节点，如果挂上两个儿子，那么会使得 $n\gets n+1,p\gets p+2$，因此 $(n+p)\bmod 3$ 不变。如果对于一个偶深度的节点挂上两个儿子，那么会使得 $n\gets n+1,p\gets p-1$，因此 $(n+p)\bmod 3$ 还是不变。考虑初始状态 $n=p=1$，所以 $(n+p)\bmod 3=2$。

**充分性：**

即，为什么一定一个满足条件的符号序列一定可以还原成一个操作序列。

依旧是一棵二叉苹果树，这里我们就相当于一棵叶子节点深度奇偶性序列满足要求时一定还原出一棵二叉苹果树。

将所有连着的同号的节点给它们连上父亲。

这样，我们就得到了类似于这样的东西：

![](https://cdn.luogu.com.cn/upload/image_hosting/6jivi8l9.png)

因为我们把能连的都连了，所以不会产生左右两个孤立点的深度奇偶性都和合并过一次的点的深度奇偶性相同，因为这种情况我们可以多合并一次。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kywhuf07.png)

然后就回到了和初始问题一样的规模，并且在这样贪心的合并下，一定可以保证，永远存在两个连着的同号。我们依旧使用类似的处理方式，每次合并两个，根据上面提到的证明就一定不会产生深度冲突。

最后一个问题即，如果还原到根节点的时候深度为 $0$，这种是没有可能的。一旦满足了 $n+p-2$ 为 $3$ 的倍数，如果合并两个奇深度点，$n\gets n-1,p\gets p-2$；如果合并两个偶深度点，$n\gets n-1,p\gets p+1$，所以和模 $3$ 不变，最终留下的一定是 $n=p=1$，满足要求。


最后注意 $n=1$ 特判，因为 $n=1$ 不需要存在相邻两个同号的。

[Code](https://codeforces.com/contest/1421/submission/222547403)

---

## 作者：Unnamed114514 (赞：0)

首先有一个非常简单的区间 dp，因为要取反所以需要同时维护最小值，最大值，所以定义 $f_{l,r}$ 表示 $l,r$ 的产生的最大值，$g_{l,r}$ 表示产生的最小值，有：

$$f_{l,r}\gets\min\limits_{k=l}^{r-1}-(g_{l,k}+g_{k+1,r})$$

$$g_{l,r}\gets\min\limits_{k=l}^{r-1}-(f_{l,k}+f_{k+1,r})$$

这个显然是难以优化的，首先我们来观察几个性质。

第一个性质是原序列取反的数量，测试这个最简单的方法就是搞一个全 $1$ 的序列然后看它取反的位置，这个得到的就是至少的取反数量。

打表出来发现是 $0/2/1$ 进行循环的，更进一步地，手玩可以发现（其实手玩 $4$ 的时候你会发现有 $3$ 个取反，$5$ 个可以全部取反）如果可以出现 $x$ 个取反的，那么出现 $x+3$ 个取反的也是可以的。（前提是 $x+3\le n$）

其实这个时候我们就可以对 $n\bmod3$ 进行讨论然后贪心选剩下的数即可。

这个时候你手玩第二个样例发现它不对，但是其实结论是正确的，只是这是个必要不充分条件。

因为你第一次合并的两个数到最后正负一定相同，所以如果出现正负交替的情况它肯定是不合法的。

所以这样搞的话最后还需要调整，有三种调整方法：

- 再加上三个 `-`。

- 把一个 `-` 调整成 `+`，然后钦定这个 `+` 不会变成 `-` 然后把其它的一个 `+` 调整成 `-`。

- 把三个 `-` 调整成 `+`。

注意到 `+` 调整成 `-` 的过程中，显然是先调整 $<0$ 的，然后调绝对值最小的；然后这个时候 `-` 调成 `+` 的话优先调 $>0$ 的，然后调绝对值最小的。

注意初始的时候先钦定 $\text{}\bmod3$ 个之后三个三个一组调整，如果这组取反之后能造成正收益就直接取反，否则结束操作。

瓶颈在排序，时间复杂度 $O(n\log n)$，因为 $O(n)$ 的 dp 状态太多了，实际上没有这个快。

[code](https://codeforces.com/contest/1421/submission/293350766)

***

补充：dp 做法。

其实这个 $+3$ 已经提示得很明显了，告诉我们最后的结论应该跟 $\text{}\bmod3$ 相关。你令总的为 $n$，`+` 的数量为 $p$，`-` 的数量为 $q$。

那么有：

- $n\bmod3=1,p\bmod3=1,q\bmod3=0$

- $n\bmod3=2,p\bmod3=0,q\bmod3=2$

- $n\bmod3=0,p\bmod3=2,q\bmod3=1$

如果你观察力惊人~~或者贺题解~~你就会发现 $(2p+q)\bmod3=1$ 的结论，然后你就可以 dp 了，定义 $f_{i,0/1/2,0/1,0/1}$ 表示前 $i$ 个，当前 $(2p+q)\bmod3$ 的值，上一个的正负，是否出现连续对，转移是平凡的。

---

## 作者：7KByte (赞：0)

找规律题。

不难想出区间 $\rm DP$ ，但是 $\mathcal{O}(N^3)$ 已经是信息极限了。

观察这道题的特殊性质。

我们只关注最终序列，每一个位置是否取反，所以我们打一个暴搜的代码。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 55
using namespace std;
int n,a[N],v[N];
void solve(int k){
	if(k == n){
		rep(i,1,n){
			if(a[i])putchar('-');
			else putchar('+');
		}
		putchar('\n');
		return;
	}
	int b[N];
	rep(i,1,n)b[i] = a[i];
	rep(i,1,n-1)if(!v[i]){
		v[i] = 1;
		int j = i;
		a[i] ^= 1;a[i + 1] ^= 1;
		while(j > 1 && v[j - 1])a[--j] ^= 1;
		j = i + 1;
		while(j < n && v[j])a[++j] ^= 1;
		solve(k + 1);
		v[i] = 0;
		rep(i,1,n)a[i] = b[i];
	}
}
int main(){
	scanf("%d",&n);
	solve(1);
	return 0;
} 
```

输入 $n$ ，得到所有可能的序列，然后我们发现这些序列的加号个数有一定的规律。

下面是表，$S$ 表示加号个数的集合。

```
n   S
1   1
2   0
3   2
4   1,4
5   0,3
6   2,5
7   1,4,7
```

不难发现 $(n+sum_{+})\bmod 3=2$。同时序列中必定有两个相邻的位置符号相同。

不得不说这题的样例非常良心，指出了必须存在邻项符号相同的情况。

所以我们设计状态 $f[i][0/1/2][0/1][0/1]$ 表示前 $i$ 个数，当前和 $\bmod 3$ 后的值，上一个位置是 $+/-$，是否已经有邻项相同的位置。

时间复杂度 $\mathcal{O}(N)$，转移时有 $24$ 倍常数。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,a[N];long long f[N][3][2][2];
inline void ck(long long &x,long long y){if(y > x)x = y;}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	if(n==1){printf("%d\n",a[1]);return 0;}
	memset(f,0xcf,sizeof(f));
	f[1][n % 3][0][0] = -a[1];
	f[1][(n + 1) % 3][1][0] = a[1];
	rep(i, 2, n)rep(j, 0, 2)rep(k, 0, 1)rep(p, 0, 1)rep(w, 0, 1)
		ck(f[i][(j + k) % 3][k][w | (k == p)], f[i - 1][j][p][w] + (k * 2 - 1) * a[i]);
	printf("%lld\n",max(f[n][2][0][1], f[n][2][1][1]));
	return 0;
}
```

---

## 作者：happybob (赞：0)

我是不会猜结论的人。

先判掉 $n=1$。

考虑问题其实等价于一棵二叉树合并，直接想法是区间 DP，$f_{i,j}$ 表示将区间 $[i,j]$ 合并成一棵二叉树的答案。转移枚举根的两部分子树对应的前后缀是什么。复杂度 $O(n^3)$。

如果继续往这个区间 DP 上面想可能就做不出来了。这个 DP 状态数很大，没有什么前途。

但是接下来并没有什么很显然的优化方法。不过可以考虑从另一个思路来想。最终每个点的贡献都是 $1$ 或 $-1$。不妨对最终的贡献序列考虑。什么样的贡献序列是合法的？

对小数据打打表，发现了一个神秘规律，记贡献序列中有 $c$ 个 $1$。那么当 $c+n \equiv 2 \pmod 3$ 时总有二叉树构造。不过观察样例 $2$ 发现不太对，事实上有一个额外限制是必须有相邻两个数的贡献相同。多打点表发现这个规律非常的对啊！

于是考虑一个针对最终贡献序列的 DP。记 $f_{i,0/1/2,0/1,0/1}$ 表示目前考虑了前 $i$ 个数，选 $1$ 的数的个数加上 $n$ 模 $3$ 的结果，$i$ 选的是 $-1$ 还是 $1$，以及目前是否有相邻的两个贡献相同。转移是 $O(1)$ 的。总复杂度 $O(n)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <print>
#include <vector>
#include <queue>
using namespace std;

using ll = long long;

const int N = 2e5 + 5;

int n, a[N];
ll f[N][3][2][2];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	if (n == 1)
	{
		cout << a[1] << "\n";
		return 0;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				f[i][j][k][0] = f[i][j][k][1] = (ll)-1e16;
			}
		}
	}
	f[0][n % 3][0][0] = 0ll;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				for (int h = 0; h < 2; h++)
				{
					int nh = h | ((i != 0 && k == 1));
					f[i + 1][(j + 1) % 3][1][nh] = max(f[i + 1][(j + 1) % 3][1][nh], f[i][j][k][h] + a[i + 1]);
					nh = h | ((i != 0 && k == 0));
					f[i + 1][j][0][nh] = max(f[i + 1][j][0][nh], f[i][j][k][h] - a[i + 1]);
				}
			}
		}
	}
	ll ans = max({ f[n][2][0][1], f[n][2][1][1] });
	println("{}", ans);
	return 0;
}
```

---

## 作者：orz_z (赞：0)


考虑到所有合法的分配方案都满足一个简单的性质：$2 \times p+q \equiv 1 \pmod 3$（其中 $p$ 为 `-` 的个数，$q$ 为 `+` 的个数）和至少存在一对相邻且符号相同的数。数学归纳易证。

由此，设 $f_{i,j,0/1,0/1}$ 表示考虑了前 $i$ 个数，$2 \times p+q\equiv j \pmod 3$，第 $i$ 个数的符号为 `-` 或 `+`，否/是存在至少一对相邻且符号相同的数，的答案。

边界 $f_{1,2,0,0}=-a_1$，$f_{1,1,1,0}=a_1$。

转移方程：
$$
f_{i+1,(j+2)\pmod 3,0,t|(k==0)} \leftarrow f_{i,j,k,t}-a_{i+1}\\
f_{i+1,(j+2)\pmod 3,1,t|(k==1)} \leftarrow f_{i,j,k,t}+a_{i+1}
$$
时间复杂度 $\mathcal O(n)$。

---

