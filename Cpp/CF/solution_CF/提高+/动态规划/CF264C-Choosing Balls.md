# Choosing Balls

## 题目描述

There are $ n $ balls. They are arranged in a row. Each ball has a color (for convenience an integer) and an integer value. The color of the $ i $ -th ball is $ c_{i} $ and the value of the $ i $ -th ball is $ v_{i} $ .

Squirrel Liss chooses some balls and makes a new sequence without changing the relative order of the balls. She wants to maximize the value of this sequence.

The value of the sequence is defined as the sum of following values for each ball (where $ a $ and $ b $ are given constants):

- If the ball is not in the beginning of the sequence and the color of the ball is same as previous ball's color, add (the value of the ball) $ × $ $ a $ .
- Otherwise, add (the value of the ball) $ × $ $ b $ .

You are given $ q $ queries. Each query contains two integers $ a_{i} $ and $ b_{i} $ . For each query find the maximal value of the sequence she can make when $ a=a_{i} $ and $ b=b_{i} $ .

Note that the new sequence can be empty, and the value of an empty sequence is defined as zero.

## 说明/提示

In the first example, to achieve the maximal value:

- In the first query, you should select 1st, 3rd, and 4th ball.
- In the second query, you should select 3rd, 4th, 5th and 6th ball.
- In the third query, you should select 2nd and 4th ball.

Note that there may be other ways to achieve the maximal value.

## 样例 #1

### 输入

```
6 3
1 -2 3 4 0 -1
1 2 1 2 1 1
5 1
-2 1
1 0
```

### 输出

```
20
9
4
```

## 样例 #2

### 输入

```
4 1
-3 6 -1 2
1 2 3 1
1 -1
```

### 输出

```
5
```

# 题解

## 作者：是个汉子 (赞：4)

~~吐槽一波洛谷中文题面，看了半小时没看懂~~

### Solution

首先明确的是对每一次询问分开处理。

然后因为要求最大价值，可以想到用DP去做。设 $d_{i,j}$ 表示前 $i$ 个元素，以 $j$ 颜色为结尾的最大价值。可以发现，每一个 $i$ 最多只会更新一个 $dp$ ，所以可以将第一维省略掉。

接下来我们思考第 $i$ 个球会从哪些情况继承也就是状态转移：

1.这是子序列第 $1$ 个球： $b\times v_i$ 

2.从上一个和它颜色相同的球的结尾的子序列转移： $dp_{c_i}+a\times v_i$ 

3.从和它颜色不一样的球的结尾的最大价值子序列转移： $\max\limits_{c_i\not=c_j}\{dp_j\}+b\times v_i$ 

但是因为3转移单次复杂度为 $O(n)$ ，所以我们需要 $O(1)$ 找到最优的那个 $j$ 。

因为 $dp$ 数组在转移后是单调不减的，所以可以保留**最大值**的颜色。

但是如果只保留转移前最大值的颜色，那么可能最大值的颜色和 $i$ 一样，所以还要保留**次大值**的颜色，这样就能保证两个中起码有一个是3转移需要的。

然后更新最大值，次大值颜色， $dp_{c_i}$ 的值和 $ans$ 即可。

### 代码

```c++
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int N=1e5+5,INF=1e18;
int n,m,a,b,ans;
int v[N],c[N],dp[N];

signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&v[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
    while(m--){
        ans=0;
        scanf("%lld%lld",&a,&b);
        for(int i=1;i<=n;i++) dp[i]=-INF;
        int t1=0,t2=0,tmp=0;
        for(int i=1;i<=n;i++){
            tmp=max(b*v[i],dp[c[i]]+a*v[i]);
            if(c[i]!=t1) tmp=max(tmp,dp[t1]+b*v[i]);
            else tmp=max(tmp,dp[t2]+b*v[i]);
            if(tmp>dp[t1]){
                if(t1!=c[i]){
                    t2=t1;
                    t1=c[i];
                }
                else t1=c[i];
            }
            else if(tmp>dp[t2]&&c[i]!=t1) t2=c[i];
            dp[c[i]]=max(dp[c[i]],tmp);
            ans=max(ans,tmp);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```



---

## 作者：奇米 (赞：4)

## 题解- CF246C Choosing Balls

* **题目意思**

	说人话就是你可以选若干个物品，若这次选择的物品与上次选的$c_i$相同那么这个的贡献就是$a*v_i$否则是$b*v_i$。要使得利益最大化。
    
* $Sol$

	一开始我以为是什么贪心。后来想想认为还是一个$Dp$。就是要利用其特殊的一个性质**单调性**
    
    我们设$f_i$表示到现在选择的最后一个元素的颜色为$i$的最优解。
    
    显然对于上次颜色相同的只要$f_i=f_i+v_i*a$即可，对于颜色不同的即$f_i=\max{[f_j]+v_i*b}$于是我们只要去求$\max{[f_j(j!=i)]}$即可。此时我们就要去维护最大值以及次大值。而且因为单调性我们可以做到$O(1)$更新最大值与次大值。
    
* $Code$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e5+5;

int n,m,a[N],c[N],f[N],las,ans,ret;

signed main()
{
	scanf("%lld%lld",&n,&m);
	for ( int i=1;i<=n;i++ ) scanf("%lld",&a[i]);
	for ( int i=1;i<=n;i++ ) scanf("%lld",&c[i]);
	for (;m--;)
	{
		int A,B;
		scanf("%lld%lld",&A,&B);
		memset(f,-63,sizeof(f));
		ans=0;
		int lp=0,lb=0;
		for ( int i=1;i<=n;i++ ) 
		{
			ans=max(B*a[i],f[c[i]]+A*a[i]);
			if(c[i]!=lp) ans=max(ans,f[lp]+B*a[i]);
			else ans=max(ans,f[lb]+B*a[i]);
			if(ans>f[lp])
			{
				if(lp!=c[i]) lb=lp,lp=c[i];
				else lp=c[i];
			}
			else 
				if(ans>f[lb]&&c[i]!=lp) lb=c[i];
			f[c[i]]=max(f[c[i]],ans);
			ret=max(ret,ans);
		}
		printf("%lld\n",ret);
		ret=0;
	}
	return 0;
}
					
				
			
			
```


---

## 作者：Lily_White (赞：2)

***先吐槽一下这个翻译是错的啊！***

下面是正确的翻译：

> 有一个序列，每个元素有一个颜色$c_i$和权值$v_i$，你需要从中选出一些元素，不改变相对顺序的组成一个新序列，使得整个序列的总分最高。

> 新序列的分数是这样计算的：  
> 对于每个你选出的元素：
> - 如果这个元素和新序列中上一个元素颜色相同，就在总分里加上$v_i \cdot a$
> - 否则加上$v_i \cdot b$  

> 其中$a,b$是每个询问都会给你的常数，回答不超过$500$个询问。

---
第一眼看上去：

欸这不就是个维护区间最值的题吗看我写个线段树切了它。

看到数据范围，~~qwq~~ ~~笑容逐渐僵硬~~。

$nq=10^5\times 500=5\times 10^7$。对于本题实际上只有$2.5$s的时限来说刚好，但是复杂度再带一个$\log$便会很难通过，但是线段树的复杂度是$O(nq\log n)$的。

所以我们需要一个$O(nq)$级别的算法，对于每个询问我们需要线性求解。

定义$dp[c]$为**最后一个元素是$c$的所有序列中分数的最大值。**

我们应当从两个方向进行转移。

- 从相同颜色的序列转移而来，用$dp[c_i] + v_i \cdot a$来更新$dp[c_i]$；
- 从不同颜色的序列转移来，用$\max_{c_j \neq c_i}dp[c_j] + v_i \cdot b$来更新$dp[c_i]$。

那么我们只需要维护数列中最大的和第二大的就可以了。因为这其中一定$\exists j \Rightarrow c_i \neq c_j$。

在更新最大值与第二大值的时候，因为**转移后$dp$数组的值单调不减**，所以珂以直接$O(1)$更新，这样就解决了本题。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
#define until(x) while (!x)
#define fail(s) assert(!s)
const int INF = 0x3f3f3f3f;
const LL INFLL = lshll(60);
const long double EPS = 1e-6;
const int MAXN = 100010;
LL dp[MAXN];
LL c[MAXN], v[MAXN];
int n, q, a, b;
int main() {
	ios::sync_with_stdio(false);
	cin >> n >> q;
	for (int i = 1; i <= n; i++)cin >> v[i];
	for (int i = 1; i <= n; i++)cin >> c[i];
	while (q--) {
		cin >> a >> b;
		LL mx = 0, mxx = 0, plc = 0;
		for (int i = 1; i <= n; i++)dp[i] = -INFLL;
		for (int i = 1; i <= n; i++) {
			LL col = c[i], val = v[i];
			dp[col] = max(dp[col], 
			          max(dp[col] +``` val * a, 
					     ((plc == col) ? mxx : mx) + val * b));
			if (plc == col)mx = dp[col];
			else if (dp[col] > mx) {
				mxx = mx;
				mx = dp[col];
				plc = col;
			}
			else if (dp[col] > mxx) {
				mxx = dp[col];
			}
		}
		cout << mx << endl;

	}
	return 0;
}
```

---

## 作者：qiqing (赞：1)

## Choosing Balls 
> **题意**：by 木木！
>
>给定一个长度为$n$的球的序列，每个球有 颜色$c_i$和价值$v_i$
>
> ​			现在可以在序列中任意选出一个可能不连续的子序列（可能为空）
>
> ​			假设第$i$个选中的球的编号为$d_i$，则其对该子序列价值的贡献为： 
> $$
> \begin{cases} a\times v_{d_i}&i\neq 1\text{且}c_{d_i}=c_{d_{i-1}}\\ b\times v_{d_i}&\text{otherwise} \end{cases}
> $$
> ​			定义空序列的价值为0
> ​			有$q$次询问，每次询问指定一组新的$a$和$b$，求价值最大的子序列的价值

### 题解

设$\texttt {dp[c[i]]}$表示最后一个球是$\texttt {c[i]}$的最大价值

设$\texttt {c[j]}$表示上一个球

1. 上一个球颜色相同

$$
\texttt {dp[c[i]] = dp[c[j]] + a * v[i]}
$$


2. 上一个球颜色不同

$$
\texttt {dp[c[i]] = dp[c[j]] + b * v[i]}
$$

3. 上一个没有球

$$
\texttt {dp[c[i]] = v * a[i]}
$$



1、3两个情况都可以$O(1)$转移

而这种情况需要找到$\texttt {Max\{dp[c[j]]|c[i]!=c[j]\}}$

只记录**历史最大值**肯定是不行的

所以，同时记录最大值$\texttt {dp[now]}$和次大值$\texttt {dp[pre]}$且$\texttt {pre!=now}$

就可以保证2情况可以$O(1)$转移了

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给定一个有 $n$ 个元素的序列，序列的每一个元素是个球，第 $i$ 个球具有 $v_i$ 的值，颜色为 $c_i$。

一个序列的价值为每一个球价值和。在一个序列中，第 $i$ 个球的价值为：

当 $c_i=c_{i-1}$，$value=a \times v_i$。

否则，$value=b \times v_i$。

接下来有 $q$ 组询问，每组询问给定 $a$ 和 $b$，问在当前给定的 $a$ 和 $b$ 下，原序列所有子序列（不一定要连续）的价值中的最大值。
## 分析
首先我们考虑动态规划。用 $dp_{i,j}$ 表示前 $i$ 个元素中子序列以颜色 $j$ 结尾的最大价值。

首先我们考虑每一个 $i$ 所代表的新球只会更新一个 $dp_{i,j}$，所以我们可以把 $i$ 这一维省掉。

接下来我们考虑第 $i$ 个球的结果可能会从哪些情况继承：

当前球为子序列第一个：$b \times v_i$。

从上一个和他颜色相同的球结尾的子序列继承：$dp_{c_i}+a \times v_i$。

从和他颜色不同的球结尾的最大价值子序列继承：$dp_{x}+b \times v_i$。

现在找第 $3$ 种情况中的 $x$：

我们记录当前情况下 $dp$ 值最大和次大的颜色。这两个中一定有一个是第三种情况需要的，所以就可以完成第三种情况了。最后然后再拿当前球的结果更新数组的相应值即可。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=100005;
const LL INF=1LL<<56;
LL read(){
    int x;
    scanf("%d",&x);
    return 1LL*x;
}
int n,q,c[N];
LL v[N],dp[N];
int main(){
    scanf("%d%d",&n,&q);
    for (int i=1;i<=n;i++)
        v[i]=read();
    for (int i=1;i<=n;i++)
        scanf("%d",&c[i]);
    while (q--){
        LL a=read(),b=read();
        LL ans=0;
        int Max=0,Nxt=0;
        for (int i=0;i<=n;i++)
            dp[i]=-INF;
        for (int i=1;i<=n;i++){
            int color=c[i];
            LL now=max(dp[color]+a*v[i],b*v[i]);
            if (color!=Max)
                now=max(now,dp[Max]+b*v[i]);
            else/* if (color!=Nxt)*/
                now=max(now,dp[Nxt]+b*v[i]);
            if (now>dp[Max]){
                if (Max!=color)
                    Nxt=Max,Max=color;
            }
            else if (now>dp[Nxt]&&color!=Max)
                Nxt=color;
            dp[color]=max(dp[color],now);
            ans=max(ans,now);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

## solution
### 前言
第一眼看上去 $O(qn)$ 好像不太可行，感觉是线段树？

再看一眼，颜色只有 $n$ 个，发现可以 $O(qn)$。
### DP
这种题是典型的 `dp`。

状态：$dp_{i,col}$ 表示考虑到第 $i$ 个数，最后一个取颜色 $col$ 的最大值。

转移方程：$dp_{i,col}=\max(dp_{i-1,col}+a\times v_i,other+b\times v_i)$。

其中 $other=\max_{j=1}^{j\ne col,j\le n}dp_{i-1,j}$。

发现这样做会超时，而且 $other$ 的做法很朴素，考虑优化。

如果只记录上一次转移的最大值，发现只有一次转移会有问题，就是 $other$ 去到最大值的 $j$。

记录上一次转移的次大值 $other'$ 和 $other$ 取最大值的位置 $k$。

如果冲突，此时次大值一定不会冲突，而且是当前最优的策略。

转移方程：

$dp_{i,col}=\left\{\begin{matrix} 
  max(dp_{i-1,col}+a\times v_i,other'+b\times v_i) &j=k\\  
  max(dp_{i-1,col}+a\times v_i,other+b\times v_i) &j\ne k 
\end{matrix}\right.$

在转移过程中更新最大值和次大值即可。

再次观察更新时没有用到其他的 $dp_{i-1}$，可以把第一维压掉。

复杂度 $O(qn)$。

---

