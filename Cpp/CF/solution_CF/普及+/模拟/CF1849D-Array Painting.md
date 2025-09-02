# Array Painting

## 题目描述

You are given an array of $ n $ integers, where each integer is either $ 0 $ , $ 1 $ , or $ 2 $ . Initially, each element of the array is blue.

Your goal is to paint each element of the array red. In order to do so, you can perform operations of two types:

- pay one coin to choose a blue element and paint it red;
- choose a red element which is not equal to $ 0 $ and a blue element adjacent to it, decrease the chosen red element by $ 1 $ , and paint the chosen blue element red.

What is the minimum number of coins you have to spend to achieve your goal?

## 说明/提示

In the first example, you can paint all elements red with having to spend only one coin as follows:

1. paint the $ 2 $ -nd element red by spending one coin;
2. decrease the $ 2 $ -nd element by $ 1 $ and paint the $ 1 $ -st element red;
3. decrease the $ 2 $ -nd element by $ 1 $ and paint the $ 3 $ -rd element red.

In the second example, you can paint all elements red spending only two coins as follows:

1. paint the $ 4 $ -th element red by spending one coin;
2. decrease the $ 4 $ -th element by $ 1 $ and paint the $ 3 $ -rd element red;
3. paint the $ 1 $ -st element red by spending one coin;
4. decrease the $ 3 $ -rd element by $ 1 $ and paint the $ 2 $ -nd element red.

## 样例 #1

### 输入

```
3
0 2 0```

### 输出

```
1```

## 样例 #2

### 输入

```
4
0 0 1 1```

### 输出

```
2```

## 样例 #3

### 输入

```
7
0 1 0 0 1 0 2```

### 输出

```
4```

# 题解

## 作者：Register_int (赞：24)

就一个很显然的 dp。

设 $dp_{i,j}$ 为涂完前 $i$ 格，涂完后最后一格为 $j$ 的最小代价。假设前面都涂完了，那么最后一格只有两种方法涂上，一种是自己花钱涂，一种是找前面的匀一点。那么有转移：

$$dp_{i,a_i}\leftarrow\min(dp_{i-1,0}+1,dp_{i-1,1},dp_{i-1,2})$$

当然还有一种可能，就是先涂完自己这一格，再往前匀一点。在这种情况下，一次涂色最多能影响到的长度为：这个位置往前最长连续正数段的长度 $+1$，你可以理解为一个类似于多米诺骨牌的过程。涂完这一段后，再往前的段与后面都没关系了，因为两边中间隔着一个 $0$，想匀也没法匀。预处理出每个位置 $i$ 前最后出现的 $0$ 的位置，设为 $pre_i$，有转移：

$$dp_{i,a_i-1}\leftarrow\min(dp_{pre_i-1,0},dp_{pre_i-1,1},dp_{pre_i-1,2})+1$$

那么就做完了。时间复杂度 $O(n)$，写法应该是最简洁的。

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
 
int n, a[MAXN], dp[MAXN][3], pre[MAXN];
 
int main() {
	scanf("%d", &n), memset(dp, 0x3f, sizeof dp), dp[0][0] = dp[0][1] = dp[0][2] = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]); dp[1][a[1]] = 1;
	for (int i = 1; i <= n; i++) pre[i] = a[i] ? pre[i - 1] : i;
	for (int i = 2, j; i <= n; i++) {
		dp[i][a[i]] = min({ dp[i - 1][0] + 1, dp[i - 1][1], dp[i - 1][2] });
		if (a[i]) dp[i][a[i] - 1] = min({ dp[pre[i] - 1][0], dp[pre[i] - 1][1], dp[pre[i] - 1][2] }) + 1;
	}
	printf("%d", min({ dp[n][0], dp[n][1], dp[n][2] }));
}
```

---

## 作者：saixingzhe (赞：7)

# 分析
我们发现，一段连续的非 $0$ 数可以花费一个金币把它们全染成红色，如果这段数里有 $2$ 就可以把两端的 $0$ 也染红，否则只能把一端的 $0$ 染红。

考虑开一个数组存砖块颜色，先染存在 $2$ 的非 $0$ 串 ，再染不存在 $2$ 的非 $0$ 串，最后染 $0$。

坑点： 在染不存在 $2$ 的非 $0$ 串时，若其两边的 $0$ 都未被染过色，优先染与循环方向相反的。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200002],t[200002],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(a[i]==2&&!t[i]){
			ans++;
			t[i]=1;
			int j=i,d=i;
			while(a[(++j)])	t[j]=1;
			while(a[(--d)])	t[d]=1;
			t[d]=1;
			t[j]=1;
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==1&&!t[i]){
			ans++;
			int cun=i-1;
			t[i]=1;
			while(a[(++i)]){
				t[i]=1;
			}
			if(cun<1||t[cun])	t[i]=1;
			else	t[cun]=1; 
		}
	}
	for(int i=1;i<=n;i++) if(!t[i])	ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：__ex (赞：4)

思考性质发现：对于一个连续的非零序列，若全为 $1$，则只用花硬币涂一次，便可以将其全部涂红，且可以多涂一个与其相邻的元素。若存在 $2$，则只用花硬币涂一次，便可以将其全部涂红，且可以将其相邻的两个元素涂红。

例：$n=5$，$a=\{0,1,1,1,0\}$，若花硬币涂红最右边的 $1$，可以将所有的 $1$ 涂红，并把最左边的 $0$ 涂红。若花硬币涂红最左边的 $1$，可以将所有的 $1$ 涂红，并把最右边的 $0$ 涂红。

例：$n=7,a=\{0,2,1,2,1,1,0\}$，花硬币涂任意一个 $2$，都可以同时向左/右扩展，以涂红的 $a_2$ 到 $a_6$，并在左右端点有剩余，涂红 $a_1$ 和 $a_7$。

**一个连续的非零序列是一个单位，其扩展范围只有该序列和其左右相邻元素**

所以就统计每个这样的连续的非零序列 $a_l,a_{l+1},a_{l+2}\cdots a_{r}$，若存在 $2$，则更新 $\forall i\in[l-1,r+1]$，$vis[i]=1$。若不存在 $2$，则贪心地查看，若 $vis[l-1]=0$，就选择扩展到左边，反之扩展到右边。

时间复杂度 $\Theta(n)$。

**code**

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>inline T read(){
	T a=0;bool s=0;
	char ch=getchar();
	while(ch>'9' || ch<'0'){
		if(ch=='-')s^=1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		a=(a<<3)+(a<<1)+(ch^48);
		ch=getchar();
	}
	return s?-a:a;
}
const int mn=2e5+10;
int n,a[mn];bool vis[mn];
int main(){
    n=read<int>();
    for(int i=1;i<=n;i++)
        a[i]=read<int>();
    int cnt=0,f=0,ans=0;n++;
    for(int i=1;i<=n;i++){
        if(!a[i]){
            if(!cnt)continue;
            if(f)vis[i-cnt-1]=1,vis[i]=1;
            else if(i-cnt-1 && !vis[i-cnt-1])vis[i-cnt-1]=1;
            else vis[i]=1;
            for(int j=i-cnt;j<i;j++)
                vis[j]=1;
            cnt=f=0;ans++;
            continue;
        }
        cnt++;if(a[i]==2)f=1;
    }
    for(int i=1;i<n;i++)
        if(!vis[i])ans++;
    printf("%d\n",ans);
    // while(1)getchar();
    return 0;
}
```



---

## 作者：anjack_511 (赞：3)

萌新的第一篇题解

## 题目大意
对于一个初始颜色都为蓝色的数组 $a_1,a_2,\dots,a_n$ 其中 $a_n \in \{0,1,2\}$，现在可以进行两个操作：

1. 花费 $1$ 个金币，将 $a_i$ 涂成红色；
2. 选择一个红色的 $a_i > 0$，将 $a_{i-1}$ 或 $a_{i+1}$ 涂成红色，同时 $a_i$ 减 $1$。

输出金币的最小数目。

## 动态规划

由于操作二只能对其左右的格子产生影响，故而我们考虑动态规划，将其转换为一个 $01$ 背包问题。同时，我们还需要维护格子的数字 $a_i$，故而设计一个三维数组。

$$d[i][j][k] \ \ \ \ (j\in \{0,1\}, \ k \in \{0, 1, 2\}且k \leqslant a_i)$$

转移到 $d[a_i]$ 时，$a_i$ 之前的都被涂过。 

当 $j = 0$ 时说明 $a_i$ 暂时还未被涂过，$j = 1$ 时说明 $a_i$ 已经被涂过了。

$k = a_i$ 说明 $a_i$ 没有通过操作二涂他左侧的那格，此时只能从 $d[a_{i-1}][1]$ 转移过来；$k = a_i - 1$ 说明 $a_i$ 涂了他左边的那格，此时只能从 $d[a_{i-1}][0]$ 转移过来。


$$\begin{aligned}d[i][1][a_i]&=\min
\begin{cases}
d[i-1][1][a_{i-1}] + 1&(a_{i-1}=0)\ \ \  \small{直接涂a_i格，耗费一金币}\\
d[i-1][1][a_{i-1}]&(a_{i-1}>0) \ \ \ \small{让没涂过 a_{i-2} 的 a_{i-1}涂a_i}\\
d[i-1][1][a_{i-1}-1]&(a_{i-1}>1) \ \ \ \small{让涂过 a_{i-2} 的 a_{i-1}涂a_i}
\end{cases}\\
d[i][1][a_i - 1]&=\min
\begin{cases}
d[i-1][0][a_{i-1}] + 1&(a_i>0,a_{i-1}=0)\ \ \  \small{直接涂a_i格，耗费一金币，同时让a_i涂a_{i-1}}\\
d[i-1][0][a_{i-1} - 1] + 1&(a_i>0,a_{i-1}>0)\ \ \  \small{同理，但这里是涂过a_{i-2}的a_{i-1}}
\end{cases}\\
d[i][0][a_i]&=\min
\begin{cases}
d[i-1][1][a_{i-1}]&\ \ \  \small{不涂a_i格，a_{i-1} 没涂 a_{i-2}}\\
d[i-1][1][a_{i-1}-1]&(a_{i-1}>0)\ \ \  \small{不涂a_i格，a_{i-1} 涂过 a_{i-2}}
\end{cases}\\
d[i][0][a_i-1]&=\min
\begin{cases}
d[i-1][0][a_{i-1}]&(a_i>0,a_{i-1}=0)\ \ \  \small{不涂a_i格，之后让a_i 涂 a_{i-1}}\\
d[i-1][0][a_{i-1}-1]&(a_i>0,a_{i-1}>0)\ \ \  \small{同理，但这里涂过 a_{i-2} 的 a_{i-1}}
\end{cases}\end{aligned}$$

进行初始化 

$$
\begin{aligned}
a_0 &= 0,\\
d[0][1][0] &= 0,\\
d[0][0][0] &= INF
\end{aligned}
$$

由于最后一格 $a_n$ 必须要被涂，故

$$ans=\min
\begin{cases}
d[n][1][a_{n}]&(a_{n}=0)\\
d[n][1][a_{n} - 1]&(a_{n}>0) \\
\end{cases}\\
$$

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
#define fr(a, b, i) for (int i = a; i <= b; i++)
#define Fr(a, b, i) for (int i = a; i < b; i++)
#define rf(a, b, i) for (int i = a; i >= b; i--)
#define rF(a, b, i) for (int i = a; i > b; i--)

int n, a[200010], d[200010][2][3];
int main()
{
    cin >> n;
    fr(1, n, i) cin >> a[i];
    d[0][1][0] = 0;
    d[0][0][0] = 9999999;
    fr(1, n, i){
        d[i][1][a[i]] = d[i - 1][1][a[i - 1]] + 1; 
        if(a[i - 1] > 0) 
            d[i][1][a[i]] = min(d[i - 1][1][a[i - 1]], d[i][1][a[i]]);
        if(a[i - 1] > 1) 
            d[i][1][a[i]] = min(d[i - 1][1][a[i - 1] - 1], d[i][1][a[i]]);
        
        if(a[i] > 0) {
            d[i][1][a[i] - 1] = d[i - 1][0][a[i - 1]] + 1;
            if(a[i - 1] > 0) 
                d[i][1][a[i] - 1] = min(d[i - 1][0][a[i - 1] - 1] + 1, d[i][1][a[i] - 1]);
        }
        
        d[i][0][a[i]] = d[i - 1][1][a[i - 1]];
        if(a[i - 1] > 0)    
            d[i][0][a[i]] = min(d[i - 1][1][a[i - 1] - 1], d[i][1][a[i]]);
        
        if(a[i] > 0){
            d[i][0][a[i] - 1] = d[i - 1][0][a[i - 1]];
            if(a[i - 1] > 0) 
                d[i][0][a[i] - 1] = min(d[i][0][a[i] - 1], d[i - 1][0][a[i - 1] - 1]);
        }

    }
    cout << min(d[n][1][a[n]], (a[n] > 0) ? d[n][1][a[n] - 1] : 999999);
    return 0;
}
```

---

## 作者：Wf_yjqd (赞：2)

比赛的时候最后几分钟 WA 了，然后重构一遍就过了，然后就不知道为啥当时错了。

------------

考虑所有不含 $0$ 的序列，一定可以花费 $1$ 的代价全部染色。

如果序列中不含 $2$，可以选择向左或向右染一格。

否则两边都可以染一格。

记录过程中的代价，剩下的 $0$ 每个花费 $1$。

真的好水，复杂度 $\operatorname{O}(n)$。

------------

注意处理边界和多次染同一个的问题。

可以选择统一都优先染左边。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int n,a[maxn],nxt0[maxn],cnt2[maxn],ans,lst,bulst;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        cnt2[i]=cnt2[i-1]+(a[i]==2);
    }
    for(int i=n+1;i>=1;i--)
        nxt0[i]=(!a[i])?i:nxt0[i+1];
    for(int i=1;i<=n;i++){
        if(!a[i])
            continue;
        ans+=nxt0[i]-i-1;
        bulst=lst;
        lst=nxt0[i]-1;
        if(bulst<i-1)
            ans++;
        if((bulst>=i-1||cnt2[lst]-cnt2[i-1])&&lst<n){
            ans++;
            lst++;
        }
        i=lst;
    }
    printf("%d",n-ans);
    return 0;
}
```


---

## 作者：船酱魔王 (赞：1)

# CF1849D Array Painting 题解

## 题意回顾

长度为 $ n $ 的序列 $ a $ 初始时全是蓝色的，你可以耗费 $ 1 $ 代价将一个蓝色位染红，你也可以不耗费代价，命令一个已经染红的非 $ 0 $ 位耗费自己的 $ 1 $ 个数值将相邻的一个数染红。求你染红整个数组的最小代价。

$ n \le 2 \times 10^5 $，$ 0 \le a_i \le 2 $。

## 分析

可以发现，如果两个数之间有 $ 0 $ 的话，则这两个数之间的颜色不能相互传导；而两个数之间无 $ 0 $ 的话，这两个数的颜色可以互相传导，且非 $ 0 $ 连续段可以一次染完。

因此我们把序列分成若干个段，即**单** $ 0 $ 段和连续非 $ 0 $ 段。每个段最多影响到相邻段。

可以发现，一个非 $ 0 $ 段如果有 $ 2 $ 的话可以顺便染掉 $ 2 $ 个相邻段，全 $ 1 $ 只能染 $ 1 $ 个，因此我们还要关心每个非 $ 0 $ 段是否存在 $ 2 $。

我们从左往右扫描每个段，如果这个段是全 $ 1 $ 段的话左面有未染的 $ 0 $ 段则染左面，否则染右面，因为左面如果不染的话之后就没机会染了，右面还可以被更右面的染。有 $ 2 $ 段的话可以染两边。

统计答案时，因为非 $ 0 $ 段相邻的一定是 $ 0 $ 段，因此非 $ 0 $ 段都要消耗一个代价，$ 0 $ 段如果不能被相邻的染的话也要消耗一个代价。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int n;
int a[N];
int ct = 0;
int d[N];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	int th = -1;
	for(int i = 1; i <= n; i++) {
		if((th == a[i] && a[i] != 0) || (th == 2 && a[i] == 1)) {
			continue;
		} else if(th == 1 && a[i] == 2) {
			th = 2;
		} else {
			d[ct] = th;
			th = a[i];
			ct++;
		}
	}
	d[ct] = th;
	int sta = 0;
	int ans = 0;
	for(int i = 1; i <= ct; i++) {
		if(d[i] == 0) {
			if(sta == 1) {
				ans++;
			} else if(sta == -1) {
				sta = 0;
			} else if(sta == 0) {
				sta = 1;
			}
		} else if(d[i] == 1) {
			ans++;
			if(sta == 1) {
				sta = 0;
			} else {
				sta = -1;
			}
		} else if(d[i] == 2) {
			ans++;
			sta = -1;
		}
	}
	if(sta == 1) {
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：CarroT5656 (赞：1)

**题目大意**

给定一个长度为 $n$ 的序列 $a$。一开始，所有位置都是蓝色的。可以执行下列操作若干次：

* 选择一个位置并将其染成红色，代价为 $1$。

* 选择一个红色的位置 $i$，$a_i>0$，将 $a_i$ 减 $1$，并选择一个相邻的蓝色方块染成红色。

问你将所有方块都染成红色的最小代价。

**解法分析**

不难得到，对于一个区间 $[l,r]$，如果满足 $\forall i(l\le i\le r)\ a_i>0$，在处理的时候可以把整个区间看作是一个元素 $\max\{a_l,a_{l+1},\cdots a_r\}$。

那么就是一个很明显的 dp。

设 $f_i$ 表示已经处理好前 $i$ 个的最小代价是多少。

最基本的转移式是 $f_i=\min(f_{i-1}+1,f_i)$

剩下的就是对着后面的 $1$ 或 $2$，考虑每一种情况，进行转移。情况有点多，详见代码。

时间复杂度为 $O(n)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
void Min(ll &x,ll y){if(y<x) x=y;}
ll n,m,a[N],b[N],dp[N];
int main(){
	memset(dp,0x3f,sizeof dp);
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(ll i=1;i<=n;i++){
		ll j=i,mx=a[i];
		while(mx>0&&j<=n&&a[j+1]>0) Max(mx,a[++j]);
		b[++m]=mx,i=j;
	}
	n=m;
	dp[0]=0;
	for(ll i=0;i<n;i++){
		Min(dp[i+1],dp[i]+1);
		if(b[i+1]==1) Min(dp[i+2],dp[i]+1);
		if(b[i+2]==1) Min(dp[i+2],dp[i]+1);
		if(b[i+1]==1) Min(dp[i+1],dp[i]+1);
		if(b[i+1]==2) Min(dp[i+2],dp[i]+1); 
		if(b[i+2]==2) Min(dp[i+3],dp[i]+1);
	}
	printf("%lld\n",min(dp[n],dp[n+1]));
	return 0;
}
```

---

## 作者：hanjinghao (赞：1)

# 题意

有 $ n $ 个格子，第 $ i $ 个格子上的数字为 $ a_i $。一开始，所有格子都是蓝色的。你可以进行以下两种操作若干次：

一、花费一枚硬币，把一个蓝色的格子染成红色。

二、选择一个红色的且数字不为 $ 0 $ 的格子以及其旁边的一个蓝色的格子，把红色格子上面的数字减一，并把蓝色格子染成红色。

求至少要花费多少枚硬币，使得所有格子都被染成红色？

# 思路

找出所有极长的数字非零连续段。对于每一段，因为两边的数字都是 $ 0 $，所以这一段无法从外面染过来，只能从段内某个点开始染色。贪心地考虑：如果这一段中有 $ 2 $，那么就直接从 $ 2 $ 开始往左右两边染色，最后可以把段内所有的点以及这一段左右两边的两个点染成红色。如果这一段全是 $ 1 $，那么可以从最左边的 $ 1 $ 开始往右染色，把段内所有的点以及这一段右边的一个点染成红色；或者从最右边的 $ 1 $ 开始往左染色，把段内所有的点以及这一段左边的一个点染成红色。

先把有 $ 2 $ 的连续段处理好，这一定不劣。

然后，如果某个蓝色的 $ 0 $ 的左右两边都是 $ 0 $，那么这个 $ 0 $ 就无法从其他点染过来，只能直接通过操作一染成红色。

对于剩下的蓝色的 $ 0 $，考虑以下情况：

如果其左边有全 $ 1 $ 连续段并且没有被标记，那么直接从左边染过来，并且把左边的全 $ 1 $ 连续段打上标记。

否则，如果其右边有全 $ 1 $ 连续段并且没有被标记，那么直接从右边染过来，并且把右边的全 $ 1 $ 连续段打上标记。

对于剩下的情况，通过操作一染成红色。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline const void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline const void writesp(const T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline const void writeln(const T x)
{
	write(x);
	putchar(10);
}

const int N = 2e5 + 5;
int n, ans, a[N], b[N];
bool ok[N], vis[N];

int main()
{
	read(n);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	for (int i = 1; i <= n; ++i)
		if (a[i])
		{
			int r = i;
			while (r < n && a[r + 1])
				++r;
			++ans;
			for (int j = i; j <= r; ++j)
				ok[j] = 1;
			bool two = 0;
			for (int j = i; j <= r; ++j)
				if (a[j] == 2)
				{
					two = 1;
					break;
				}
			if (two)
			{
				if (i != 1) ok[i - 1] = 1;
				if (r != n) ok[r + 1] = 1;
			}
			i = r;
		}
	int len = 0;
	for (int i = 1; i <= n; ++i)
		if (!ok[i] && (i == 1 || !ok[i - 1]) && (i == n || !ok[i + 1])) b[++len] = i;
	ans += len;
	for (int i = 1; i <= len; ++i)
		ok[b[i]] = 1;
	for (int i = 1; i <= n; ++i)
		if (!a[i]) vis[i] = 1;
	for (int i = 1; i <= n; ++i)
		if (!ok[i])
		{
			if (i != 1 && !vis[i - 1])
			{
				ok[i] = 1;
				continue;
			}
			if (i != n && !vis[i + 1])
			{
				ok[i] = 1;
				for (int j = i + 1; j <= n && a[j]; ++j)
					vis[j] = 1;
				continue;
			}
			++ans;
			ok[i] = 1;
		}
	writeln(ans);
	return 0;
}

```

---

## 作者：Crazyouth (赞：1)

**翻译**

你有一个蓝色数列 $a$，共 $n$ 个数，且 $0\le a_i\le2$，你可以进行以下两个操作：

1. 花费一枚硬币把一个 $a_i$ 变成红色的。
2. 选择一个红色的 $a_i$，把它旁边的一个蓝色数变成红色的，且选择的 $a_i$ 减一。

求你最少花费多少硬币把整个数列变成红色的。

**分析**

不难得到，对于一个 $a_i$，它表示的就是它变成红色后能执行的操作 $2$ 的个数。所以只要给它旁边 $a_i$ 个数打上标记即可，最后看哪些没有标记即可。

思路有了，现在考虑实现。我们创建数组 `tag[]`，用 `tag[i]` 表示第 $i$ 个数有没有标记，并令 `tag[0]=1`。假如 $a_i=1$，我们先考虑执行 `tag[i-1]=1`，但假如 `tag[i-1]` 已经是 $1$，考虑执行 `tag[i+1]=1`；假如 $a_i=2$，直接两个都执行即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/424h8y2g.png?x)

但是这个实现会 `WA on test 4`，我们发现了一组 hack，即全都是 $1$ 的时候，理论上只需要一枚硬币，但输出会多很多，这是因为第一个 $1$ 染了后面的数，而第二个 $1$ 发现 $a_1$ 没有标记，于是它去染第一个数了，但实际上这时候 $a_1$ 已经是红的了，这就导致 $a_3$ 还是蓝的。因此加一组特判，若 $a_i$ 是由 $a_{i-1}$ 染的，就不能染 $a_{i-1}$。

P.S. 感谢 @happybob 巨佬帮我找到的 hack。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int tag[int(2e5+10)],a[int(2e5+10)],p[int(2e5+10)];//标记，原数组，被谁染的
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	tag[0]=1;
	for(int i=1;i<=n;i++)
	{
		if(!a[i]) continue;
		else if(a[i]==1)
		{
			if(!tag[i-1]&&p[i]!=i-1)//没染过且不是被i-1染的
			{
				tag[i-1]=1;
				p[i-1]=i;
			}
			else//染后面的
			{
				tag[i+1]=1;
				p[i+1]=i;
			}
		}
		else
		{
			if(!tag[i-1]&&p[i]!=i-1)//没染过且不是被i-1染的
			{
				tag[i-1]=1;
				p[i-1]=i;
			}
			if(!tag[i+1])//没染过，染后面的
			{
				tag[i+1]=1;
				p[i+1]=i;
			}
		}
	}
	for(int i=1;i<=n;i++) if(!tag[i]) ans++;//统计没有标记的
	cout<<ans;
	return 0;
}

---

## 作者：Halberd_Cease (赞：0)

考虑化简给出的序列。

对于一段非 ```0``` 的区间，显然只需要花费 $1$ 就可以让整段区间被染色：从两端染色即可。

具体来说，对于区间 $[l,r]$ 有：

- 如果这段区间全部由 ```1``` 组成，那么我们从左边开始染色，可以把 $[l,r+1]$ 染色，同理，从右边开始染色可以染完 $[l-1,r]$；

- 如果这段区间中有 ```2```，那么我们从任意一个 ```2``` 开始染色，往左边和往右边染，可以染完 $[l-1,r+1]$。


因为我们要求的答案是最小的花费，因此将上面的区间看作一个点，花费都是 $1$，所以对最终的答案没有影响。

第一种区间可以看作点 ```1```，第二种可以看作点 ```2```。

操作过后我们可以发现所有的 ```1``` 和 ```2``` 之间都隔了有至少一个 ```0```。

我们在操作过后的序列上顺序寻找 ```1``` 和 ```2```，如果这一位是 ```1``` 的话，就默认把左边的 ```0``` 染色，如果左边的染过色就染右边的。

如果是 ```2``` 就无脑把左右都染色。

上面步骤的花费是操作后序列中 ```1``` 和 ```2``` 的数量。

然后再次遍历寻找没有被染色的 ```0``` 手动进行染色并累加答案。

得到的就是最终的答案了。

核心代码：

```cpp
for (int i = 1; i <= m; i++)
{
	if (b[i] == 2)
	{
		ans++;
		vis[i - 1] = vis[i] = vis[i + 1] = 1;
	}
	if (b[i] == 1)
	{
		ans++;
		vis[i] = 1;
		if (vis[i - 1])
			vis[i + 1] = 1;
		else
			vis[i - 1] = 1;
	}
}
for (int i = 1; i <= m; i++)
{
	if (!vis[i])
		ans++;
}
```

---

## 作者：快乐的大童 (赞：0)

### 题目大意
一个长度为 $n$ 的序列为 $a$，值域为 $0,1,2$。你可以花费 $1$ 直接涂黑一个 格子，也可以将一个已经涂黑的格子旁边的 $a_i$ 个格子全部涂黑。求将序列所有 $n$ 个格子全部涂黑的最小花费。

$n\le 2\times 10^5$。
### 思路

虽然这道题非常的 dp，但我们考虑贪心。

发现优先涂 $2$ 一定是比优先涂 $1$ 是要优的，所以我们考虑先花钱将 $2$ 涂黑，将两边的点涂黑，再选择没涂过的 $1$，花钱涂黑它，再随便选一边没涂过的涂黑，最后花钱将剩下还是白色的格子涂黑。

这个策略很显然是假的。考虑数据 `0 2 1 2 0`，先涂黑位置 $2$，标记位置 $1,3$，再涂黑位置 $4$，标记位置 $5$，理应花费为 $2$。但现实是，只需要涂黑位置 $2$，剩下的都会通过一些连续的 $1,2$ 向左或向右传播。

这启发我们将一段连续的非 $0$ 的 $a_i$ 合并（注意不要合并 $0$），发现在这个块内任意花钱涂一个数都会使整个块都被涂黑，那么我们只需要沿用开头提到的贪心策略，对于每个块，如果其中有 $2$，涂掉任意一个 $2$，并且与块相邻的两个格子均能被涂黑；如果其中只有 $1$，涂掉任意一个 $1$，与块相邻的两个格子只能被涂黑一个，随意选一个之前没标记过的即可，推荐选靠前的格子，因为这样不会影响后面块的决策。
### 代码
```cpp
#include<bits/stdc++.h>
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
inline int rd(){
	int x=0,f=1;int ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x,char ch='\0'){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[40];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);if(ch!='\0')putchar(ch);
}
const int maxn=2e5+5,maxm=4e5+5;
int n,m,a[maxn],b[maxn];
bool vis[maxn];
void solve_the_problem(){
	n=rd();rep(i,1,n)a[i]=rd();
	int pos=1;
	while(pos<=n){
		b[++m]=a[pos];
		while(a[pos]&&a[pos+1])pos++,b[m]=max(b[m],a[pos]);
		pos++;
	}
	vis[0]=vis[m+1]=1; 
	int ans=0;
	rep(i,1,m){
		if(b[i]==2){
			if(!vis[i]) ans++;
			vis[i-1]=vis[i]=vis[i+1]=1;
		}
	}
	rep(i,1,m){
		if(b[i]==1){
			if(!vis[i]) ans++,vis[i]=1;
			if(vis[i-1]+vis[i+1]==0) vis[i-1]=1;
			else vis[i-1]=vis[i+1]=1;
		}
	}
	rep(i,1,m){
		if(!vis[i]) ans++;
	}
	write(ans,10);
}
signed main(){int _=1;while(_--)solve_the_problem();}
/*

*/

```


---

