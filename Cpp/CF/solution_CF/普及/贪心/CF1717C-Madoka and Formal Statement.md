# Madoka and Formal Statement

## 题目描述

给定一个数列 $a_{1…n}$, 如果满足下面条件, 你可以使 $a_i = a_i + 1$:

- $i < n$ 且 $a_i \leq a_{i+1}$
- $i = n$ 且 $a_i \leq a_{1}$

再给定一个数列 $b_{1…n}$, 问 $a$ 是否可以通过上述操作变为 $b$.

## 样例 #1

### 输入

```
5
3
1 2 5
1 2 5
2
2 2
1 3
4
3 4 1 2
6 4 2 5
3
2 4 1
4 5 3
5
1 2 3 4 5
6 5 6 7 6```

### 输出

```
YES
NO
NO
NO
YES```

# 题解

## 作者：xzy090626 (赞：13)

# CF1717C 题解
## 题意
有两个长为 $n(n\le 2\times 10^5)$ 的序列 $a,b$，你可以对 $a$ 进行以下操作：
- 对于 $a_i(i<n)$，如果 $a_i\le a_{i+1}$，那么可以给 $a_i$ 加一；
- 对于 $a_i(i=n)$，如果 $a_n\le a_1$，那么可以给 $a_n$ 加一。

请问是否可以通过若干次操作，使得 $a$ 变为 $b$。
## 分析
对于这种 CF 题目，一看就是贪心。

我们一般通过某些条件判断 $a_i$ 是否合法。

---
首先有一个显然的性质：

当 $a_i>b_i$ 的时候，一定非法（因为所有操作一定是只加不减）。

接着，对于所有的 $a_i$，如果 $a_i=b_i$，那就没有必要考虑了。

那么现在就只剩 $a_i<b_i$ 的情况了。

我们观察样例，注意到如果要使 $a_i$ 变为 $b_i$，那么 $a_{i+1}$ 必须 $\ge b_i-1$，此时的它可以作为一个跳板，帮助 $a_i$ 变为合法。

问题来了：但是 $a_i$ 是由 $a_{i+1}$ 确定的，而 $a_{i+1}$ 是由 $a_{i+2}$ 确定的啊！

这就成了一个循环，似乎没有什么好的办法。

但是不要忘了，我们刚刚的性质：$a_{i+1}$ 仍然是被 $b_{i+1}$ 限制着的。

那就没有问题了：如果 $b_i>b_{i+1}+1$，那么不行，因为此时如果要使得 $a_i$ 合法，$a_{i+1}$ 至少要为 $b_i-1$。但是 $a_{i+1}$ 不可以 $>b_{i+1}$，所以不合法。

结束了。
## 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
int a[N],b[N];
void solve(){
	int n;cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>b[i];
	b[n+1] = b[1];
	for(int i=1;i<=n;++i){
		if(a[i]>b[i]||(b[i]>b[i+1]+1 && a[i]!=b[i])){
			cout<<"NO\n";
			return;
		}
	}
	cout<<"YES\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```
## 总结
- 我们遇到这种一眼贪心题时，要将性质列出来，然后通过性质去判断是否合法。
- 一般来说这种题目 $a_i$ 可以独立判断是否合法，即可以找到一个 $O(1)$ 的方法（条件）判断 $a_i$ 是否合法。
- CSP 2022 rp++！


---

## 作者：ZLRest (赞：2)

不难发现此题是一道分类讨论题。只需要找出不行的情况，其余都是行的情况了,然后直接输出就可以了。

- 我们可以很轻松的得到第一种情况 $a_i>b_i$ 时无论如何 $a_i$ 也不可能等于 $b_i$。
- 然后我们可以发现 $a_i$ 由 $b_i$ 和 $a_{i+1}$ 界定，所以下面该由 $a_{i+1}$ 判断。不难发现如果有解，则 $a_{i+1}$ 一定大于等于 $b_i$，而 $b_{i+1} \ge a_{i+1}$，根据不等式的性质不难得出： $ b_{i+1} \ge b_i-1$,所以无解的情况为 $b_{i+1} <b_i+1$。

其他细节看代码。
### CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int n;
int a[200010],b[200010];
inline int read(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x;
}/////
bool solve(){
	 a[0] = a[n];
	 b[0] = b[n];
	for(int i=0;i<n;i++){
		if(a[i]>b[i]) return 1;
		if(b[i]>b[i+1]+1&&a[i]!=b[i]) return 1;
	}
	return 0;
}
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int j=1;j<=n;j++) b[j]=read();
		if(solve()) puts("NO");
		else puts("YES");
	}
}
```


---

## 作者：XiaoQuQu (赞：1)

显然，要是一直加下去，总得有个时候加不动了。

我们发现，当有任意一个 $a_i>b_i$ 的时候，肯定是无法变为序列 $b$ 的。

如果存在一个 $i$ 使得 $b_i-b_{i-1}>1$，则如果我们想要改动 $a_{i-1}$ 到 $b_{i-1}$，就必须使得 $a_{i}\ge a_{i-1}$，但是我们知道，如果在最后能够让 $a_i\ge a_{i-1}$ 的话，$a_i$ 就必须大于 $b_i$，所以不可能成功。 

```cpp
const int MAXN = 2e5 + 5;
int a[MAXN], b[MAXN];

signed work() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    a[0] = a[n]; b[0] = b[n];
    for (int i = 1; i <= n; ++i) if (a[i] > b[i]) return puts("NO");
    for (int i = 1; i <= n; ++i) if (b[i - 1] - b[i] > 1 && a[i - 1] != b[i - 1]) return puts("NO");
    return puts("YES");
}

signed main(void) {
    ios::sync_with_stdio(false), cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) work();
    return 0;
}
```

---

## 作者：流水行船CCD (赞：1)

### 题目分析

这道题看题意很明显是要分类找状况的题。

首先题目说了我们只能使 $a_i=a_i+1$ ，如果有一个位置上的 $a_i>b_i$ 时，序列 $a_{1\ldots n}$ 肯定不能变成序列 $b_{1 \ldots n}$ ，这就是第一个判断条件；

接着思考，由于 $a_i$ 只能增加，如果要使数列 $a$  有机会转变为 $b$ ，我们的 $a_i$ 最大值只能取 $b_i$ ，又因为只有 $a_i \le a_{i+1}$ 时才能改变 $a_i$ 的值，所以 $a_{i-1}$ 最大值只能为 $b_i+1$ 。（注意，这里的最大值不是 $b_i$ ）所以当 $b_{i-1} > b_i+1$ 的时候，也是不可以转化成功的。

同时，不要忘了 $a_i=b_i$ 的时候直接可以，不用判断上述条件。（~~本蒟蒻忘过~~）

最后，我为了方便，直接把数组的第一项赋值到最后一项~~这样可以省略一个取模~~。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool k;
int t,n,maxx;
int a[200005],b[200005]; 
signed main(){
	scanf("%lld",&t);
	while(t--){
		maxx=0;k=true;
		scanf("%lld",&n);
		for(register int i=1;i<=n;i++){scanf("%lld",&a[i]);}
		for(register int i=1;i<=n;i++){scanf("%lld",&b[i]);}
		a[n+1]=a[1];b[n+1]=b[1];
		for(register int i=1;i<=n;i++){
			if(a[i]==b[i]){continue;}
			if(a[i]>b[i]){k=false;break;}
			if(b[i]>(b[i+1]+1)){k=false;break;}
		}
		if(k){printf("YES\n");}
		else{printf("NO\n");}
	}
	return 0;
}
```

完结撒花

---

## 作者：Comentropy (赞：1)

## 分析

因为这道题只让判断是否可能，故可寻找使其不可能成立的性质。

如上，我们只需要寻找数列 $a$ 一定不可能达到 $b$ 的一些特征。

- 显然因为 $a_i$ 只能增加，故若出现 $ a_i > b_i $ 一定不可能。
- 当 $a_i \leq a_{i+1} $ 时，只有 $a_i=a_i +1$，故无论如何增加都不可能使得 $ b_i > b_{i+1} +1 $ 成立（证明见 ```ps``` ）。


```ps``` : 此处若 $ a_{i+1} + k ( k\in \mathbb{N} ) = b_{i+1}$，则 $a_i$ 最多能加到 $ a_{i+1} + k + 1$，即 $b_{i+1} +1 $，故得性质。

只需如上判断即可。

## Code

实现部分代码如下：

```cpp

bool check(){
    b[n+1]=b[1];
    for(int i=1;i<=n;i++)
        if(a[i]>b[i] || a[i]<b[i]&&b[i]>b[i+1]+1)
            return false;
    return true;
}

```




---

## 作者：NotTogawaButSakiko (赞：1)

题意：给定一个数列 $a_{1…n}$, 如果满足下面条件, 你可以使 $a_i = a_i + 1$:

-  $i \le n$ 且 $a_i \le a_{i+1}$
- $i = n$ 且 $a_i \le a_1$

再给定一个数列 $b_{1…n}$, 问 $a$ 是否可以通过上述操作变为 $b$.

Sol：分类讨论

- $a_i > b_i$，显然不能通过操作变为 $b_i$；
- $a_i = b_i$，不用考虑；
- $a_i < b_i$，我们考虑对 $a_i$ 进行操作的限制。$a_i$ 只受 $a_{i+1}$ 和 $b_i$ 的限制，要使得 $a_i$ 能通过操作变为 $b_i$， 当且仅当 $b_i$ 小于等于 $a_{i+1}$ 最终取值 $+1$，也就是$b_{i+1}+1$。

所以当存在 $i$ 使得 $a_i > b_i$ 或 $b_i > b_{i+1} + 1$ 时不能通过操作使 $a$ 变为 $b$，其余情况可以。


---

## 作者：Acerkaio (赞：1)

### 题目？

[Link](https://www.luogu.com.cn/problem/CF1717C)

### 思路？

因为操作中，只会有 $a_i = a_i + 1$，所以当 $a_i > b_i$ 时候显然是无解的，我们还发现因为当 $a_{i+1} > a_i$ 时候 $a_i = a_i + 1$，所以当 $b_i > b_{i+1} + 1, a_i < b_i$时是无解的，因为如果要满足 $a_i = b_i$，那么要求 $a_{i+1} \ge b_{i} - 1$，则无法满足了 $a_{i + 1} = b_{i+1}$。

### CODE

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1000001], b[1000001];
signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		bool flag = 1;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		for (int i = 1; i <= n; i++)
			cin >> b[i];
		b[n + 1] = b[1];
		for (int i = 1; i <= n; i++) {
			if (a[i] > b[i] || (a[i] < b[i] && b[i] > b[i + 1] + 1)) {
				cout << "NO\n";
				flag = 0;
				break;
			}
		}
		if (flag)
			cout << "YES\n";
	}
	return 0;
}
```


---

## 作者：chatoudp (赞：0)

# CF1717C 题解


把 $a$ 序列变成 $b$ 序列，有一点是显然不行的：

$n$ 为序列长度。

### $b_i>a_i$，$i\in\{1,2,3\dots,n\}$ 
 
当然，也不是满足下面条件就可以了。

每个数只有当后一个数大于等于它的时候，他才能加一。

而，第 $i$ 个数加到 $b_i$ 时就不会再加了，所以他的前一项只能加到 $b_i+1$。

还有一种情况，那就是根本不用加，不管它的后一项的限制是几，他都可以满足要求。

## 总结一~~哈~~下

### 条件一：

$b_i \le a_i$，$i\in\{1,2,3\dots,n\}$

### 条件二：

$b_i \le b_{i+1}+1$ 或 $b_i = a_i$。（若 $i+1 = n+1$ 那么 $i+1$ 为 $1$）

#### AC Time ！！！（~~请乱~~禁止抄袭）

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,a[200005],b[200005],c[200005]; 
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) scanf("%d",&b[i]);
		bool f=1;
		int minn=2147483647;
		int maxn=0,maxid;
		for(int i=1;i<=n;i++)
			if(b[i]<a[i])
			{
				printf("NO\n");
				goto F;
			}
		for(int i=1;i<=n;i++)
			if(b[i]>b[i+1==n+1?1:i+1]+1&&b[i]!=a[i]){
				printf("NO\n");
				goto F;
			}
		printf("YES\n");
		F:
			;
	}
	return 0;
}

```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/solution/CF1717C)

## 题目意思
给你两个长为 $n$ 的序列 $a,b$，当以下条件成立时，可以让 $a_i \gets a_i+1$:
- $i<n$ 且 $a_i \le a_{i+1}$；
- $i=n$ 且 $a_i \le a_1$。

问 $a$ 是否可以通过上述操作变为 $b$。

## 解题步骤
首先一看到题目，就知道它是贪心题。

解题步骤如下：
1. 输入 $n$ 和 $a,b$；
2. 既然是要让每个 $a_i$ 增加，从而使 $a$ 变为 $b$，那么每个 $a_i$ 就不能大于 $b_i$，如果是这样直接输出 `NO`；
3. 如果 $b_i>b_{i+1}+1$，也要输出 `NO`，但是万一 $a_i=b_i$，就不能输出了；
4. 如果上面的条件不成立，这时输出 `YES`。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200010],b[200010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	BREAK:
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		for(int i=1;i<=n;i++)
			if(a[i]>b[i]||b[i]>b[i%n+1]+1&&a[i]!=b[i])
			/*为了方便，我写成了i%n+1，意思就是绕成一个环*/
			{
				cout<<"NO\n";
				goto BREAK;//退出本次循环
			}
		cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：ZLRest (赞：0)

### 前置芝士
并查集

如果不会并查集请先做这道题 [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367) 。
### 分析
很明显此题是一道 01 背包题，此题要求一些物品捆绑，那我们可以将这些物品合并成一个物品再跑 01 背包板子。

### 处理
合并操作可以用并查集实现，把捆绑的物品的价值和重量分别加到它祖先的价值和重量上就可以实现了。

然后我们来分析 01 背包的部分：

因为每种物品只有一个，所以我们对每个物品只有两种选择：取或不取。最优解一定存在于这两种选择之中。而可以证明，取第 $i$ 种物品时得到的最优解一定比第 $i-1$ 得到的最优解不劣：
- 因为若取第 $i$ 件物品，则取第 $i$ 种物品时得到的最优解优于取第 $i_1$ 件物品得到的最优解；
- 若不取第 $i$ 件物品，则取第 $i$ 种物品时得到的最优解等于取第 $i_1$ 件物品得到的最优解。

那么现在问题就转化成了求第 $i$ 件物品时的最优解，对于第 $i$ 件物品，我们还是有两种选择：
- 取，就相当于求用 $W-w_i$ 取前 $i-1$ 件物品的最优解，那么当前的最优解就是用 $W-w_i$ 取前 $i-1$ 件物品的最优解加上 $v_i$；
- 不取，就相当于求用 $W$ 取前 $i-1$ 件物品的最大值。

那么状态转移方程就出来了,我们用 $i$ 表示第几件物品，$j$ 表示还剩多少重量，就是： 
$dp[i][j] = max(dp[i - 1][W], dp[i - 1][W - w[i]] + v[i])$。

然后我们发现可以优化：观察状态转移方程，我们发现只用到了 $i$ 和 $i-1$,考虑滚动数组优化，那么状态转移方程就变成了： $dp[j]=max(dp[j],dp[j-w[i]]+v[i])$。

然后就可以完美通过此题了。

其他细节看代码。
### CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,W;
int w[10010],v[10010];
int f[10010];
int dp[10010];
inline int read(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9'){c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x;
}
int find(int x){
	return (f[x]==x)?x : find(f[x]);
}
int main(){
	n=read();
	m=read();
	W=read();
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=n;i++){
		int x,y;
		x=read();
		y=read();
		w[i]=x;
		v[i]=y;
	}
	for(int i=1;i<=m;i++){
		int x,y;
		x=read();
		y=read();
		int fx=find(x),fy=find(y);
		f[fy]=fx;
		
	}
	for(int i=1;i<=n;i++){
		if(f[i]!=i){
		w[find(i)]+=w[i];
		w[i]=0;
		v[find(i)]+=v[i];
		v[i]=0;	
		}
		
	}
	for(int i=1;i<=n;i++)
	{	
		for(int j=W;j>=w[i];j--){
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
		}
	}
	cout<<dp[W];
	return 0;
}
```


---

## 作者：Ferm_Tawn (赞：0)

这道题所需知识点为：**贪心**。

思路：

分两种情况讨论：

- 若 $a_i > b_i$，题目中没说能使用减法，故这种情况的输出为 ```NO```。

- 否则如果 $b_i > b_{(i + 1) \bmod n}$，这也是不行的。从题目上来看，想使前面的数增加，后面的数就要小于前面的数。而本情况不满足，也输出 ```NO```。

- 上述情况不满足，输出 ```YES``` 。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool flag;
int t , n;
int a[1000005] , b[1000005];
signed main(){
	cin >> t;
	while(t--){
		flag = true;
		cin >> n;
		for(int i = 0 ; i < n ; i++) cin >> a[i];
		for(int i = 0 ; i < n ; i++) cin >> b[i];
		for(int i = 0 ; i < n ; i++){
			if(a[i] > b[i]){
				flag = false;
				break;
			}
			else{
				if(a[i] < b[i] && b[i] > b[(i + 1) % n] + 1){
					flag = false;
					break;
				}
			}
		}
		if(flag == true) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}
```


---

## 作者：zt17 (赞：0)

[查看题目](https://www.luogu.com.cn/problem/CF1717C)
## 思路

我们想想看这样的数组有什么特征？

 - $a_{i} > b_{i}$ 时，没得谈，因为 $a_{i}$ 没办法缩小。
 
 - $a_{i} = b_{i}$ 时，不用变化。

那就只剩下 $a_{i} < b_{i}$ 的情况了。~~（我感觉我啥也没说）~~

那我们就重点思考一下这种想法。

首先我们要明白，如果 $a_i \to b_i$ （注：这里的箭头表示转换）成立，则 $a_{i+1} \ge b_i$ 必须成立。那我们就可以把这一点当成一个判断其是否能进行变换的条件。

当我偶然在看样例发现这个规律后，哇，当时那个兴奋劲直接冲上我的脑阔，直接开始写代码。

写着写着，发现，不对啊？虽然 $a_i$ 可以由 $a_{i+1}$ 来确定，但是 $a_{i+1}$ 是由 $a_{i+2}$ 决定的啊？而我们要去判断 $a_{i+2}$ 时，我们又得去考虑 $a_{i+3}$……这样看，我们似乎陷入了一场 $\lceil$ 循环 $\rfloor$ 当中……

我们只能从头开始想。我们可以确定的是，之前算出来的结论肯定有用，但是不是这么用的。

等等，从头?

还记得我之前说了什么吗？

>  - $a_{i} > b_{i}$ 时，没得谈，因为 $a_{i}$ 没办法缩小。

> ……那就只剩下 $a_{i} < b_{i}$ 的情况了。~~（我感觉我啥也没说）~~

不！这一点很重要！

如果 $b_{i} > b_{i+1} + 1$ 的时候合法，那么 $a_{i+1} \ge b_{i}$。但是 $a_{i} > b_{i}$ 时违反了最开始的第一条件 ,所以说如果 $b_{i} > b_{i+1} + 1$ ，则至少在 $a_{i}$ 这里，不合法。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[20002],b[20002];
int main()
{
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int m;
        cin >> m;
        for(int j=1;j<=m;j++)
            cin >> a[j];
        a[m+1] = a[1];  
        for(int j=1;j<=m;j++)
            cin >> b[j];
        b[m+1] = b[1];
        bool qwq=false;
        for(int j=1;j<=m;++j)
        {
            if(a[i]>b[i]||(b[i]>b[i+1]+1 && a[i]!=b[i])){qwq = true;break;}
        }
        if(qwq) {cout << "NO" << endl;continue;}
        cout << "YES" << endl;
    }
    return 0;
}
```


---

## 作者：Microchip2333 (赞：0)

[题目传送门 (洛谷)](https://www.luogu.com.cn/problem/CF1717C)


[题目传送门 (CF)](https://codeforces.com/problemset/problem/1717/C)

------

**题意简述**

你有两个长度为 $n$ 的数组 $a, b$. 你可以进行以下操作：

- 选择一个下标 $i$ $(1\leq i< n)$，若 $a_i\leq a_{i + 1}$，那么你可以让 $a_i$ 自增 $1$.

- 特别地，若 $a_n\leq a_1$, 你可以让 $a_n$ 自增 $1$.

现在请你判断，经过若干次操作后 $a$ 数组是否可以变成 $b$ 数组。

---

**思路整理**

一般 CF 上判断 Yes 或 No 的题目，大部分都是判断无解情况，所以我们仅需要思考在什么情况下会无解。


第一种很容易就想到，当 $a_i > b_i$ 时，无论如何操作 $a$ 只会增加而不会减少，所以 $a_i$ 永远不可能等于 $b_i$. 故此情况无解。

第二种情况，当 $a_i = b_i$ 时，这个 $a_i$ 无需考虑，那么当 $a_i<b_i$ 时，如果想使 $a_i$ 与 $b_i$ 相等，我们需要使 $a_{i+1}>a_i$，即 $a_i\leq a_{i+1} - 1$。

但是因为 $a_{i}$ 的上限是 $b_{i}$，
所以这就可以得出另一个式子： 

$$ a_{i+1}\geq b_i-1 $$

又因为 $a_{i + 1}$ 的上限是 $b_{i + 1}$，所以我们可以得到：

$$ b_{i + 1}\geq b_i-1 $$

简单变形，可以得到：

$$ b_i\leq b_{i + 1} + 1 $$

因此可以得到：当 $b_i > b_{i + 1} + 1$ 时，无解。

这时我们就可以用时间复杂度 $\Theta (\sum n)$ 的算法来求解了。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 10;
 
int n, a[N], b[N];
 
void solve(){
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i]; a[n + 1] = a[1];
	for (int i = 1; i <= n; i ++ ) cin >> b[i]; b[n + 1] = b[1];
	for (int i = 1; i <= n; i ++ ){
		if (a[i] > b[i] || b[i] - b[i + 1] > 1 && a[i] < b[i]){
			cout << "No" << endl;
			return;
		}
	}
	cout << "Yes" << endl;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	int tt; cin >> tt;
	while (tt -- ) solve();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1717C 题解

这题有更简单的做法，参看官方题解，但是这里只讲自己考场上的心路历程和解题思路。

## 思路分析

为了方便表述，以下讨论的数组 $a,b$ 均已翻转，操作条件变为 $a_{i-1}\le a_i$ 时 $a_i\gets a_i+1$,且 $a_0$ 和 $a_n$ 是同一个元素。

首先考虑简单暴力，对于每个 $a_i$，如果有 $a_{i-1}\le a_i$，贪心地操作使 $a_i\gets \min(b_i,a_{i-1}+1)$，简单模拟样例后发现，这样的操作至多进行 $2$ 轮之后，数组 $a$ 就不会变了，我们称这样的数组 $a$ 为收敛状态，那么此时如果依然有 $b_i>a_i$ 则无解。

显然这个做法是错误的，考虑以下数据：

```
3
1 1 1
8 8 8
```

这个数据的答案是 "`YES`"，但是至少要 $3$ 轮才能得到状态收敛，因此我们应该思考一个问题： 当 $a$ 和 $b$ 存在什么样的关系时，再一轮操作 $a$ 就达到收敛状态，显然，答案是存在至少一个 $i$ 满足 $a_i=b_i$，且新一轮的操作从 $i+1$ 开始执行，证明略去，我们称这样的数组 $a$ 为次收敛状态。

那么我们现在再来思考，如果经过一轮操作之后，如果 $a$ 没有达到次收敛状态怎么办，此时我们引进一个新发现，如果不存在 $b_i$ 的限制，数组 $a$ 可以得到任意的相同值 $w$，具体的操作如下：

>1. 让所有的 $a_i$ 都与 $a$ 中的最大值 $a_m$ 相等（从 $a_m$ 开始往后按顺序把每个数都变成 $a_m$ 即可）。
>2. 如果此时 $a_m=w$ 结束操作。
>3. 因为 $a_m=a_{m-1}$，那么可以操作 $a_m\gets a_m+1$。
>4. 重复第一步直到结束。

有了这个操作方式之后就很简单了，只需要把 $a$ 都变成 $\min\{b_i\}$ 即可，此时 $a$ 就达到了次收敛状态，再操作一轮即可判定答案。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define f puts("come here");
using namespace std;
const int MAXN=2e5+1;
int a[MAXN],b[MAXN];
inline void solve() {
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d",&a[i]);
	for(int i=0;i<n;++i) scanf("%d",&b[i]);
	reverse(a,a+n),reverse(b,b+n);
	for(int i=0;i<n;++i) if(b[i]<a[i]) return (void)(puts("NO"));
	for(int i=1;i<n;++i) if(a[i-1]>=a[i]) a[i]=min(b[i],a[i-1]+1);
	if(a[n-1]>=a[0]) a[0]=min(b[0],a[n-1]+1);
	int p=-1;
	for(int i=0;i<n;++i) {
		if(a[i]==b[i]) p=i;
	}
	if(p==-1) {
		for(int i=0;i<n;++i) {
			if(p==-1||b[i]<b[p]) p=i;
		}
		for(int i=0;i<n;++i) a[i]=b[p];
	}
	for(int i=(p+1)%n;i!=p;i=(i+1)%n) {
		if(a[(i+n-1)%n]>=a[i]) a[i]=min(b[i],a[(i+n-1)%n]+1);
	}
	for(int i=0;i<n;++i) if(a[i]<b[i]) return (void)(puts("NO"));
	puts("YES");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

