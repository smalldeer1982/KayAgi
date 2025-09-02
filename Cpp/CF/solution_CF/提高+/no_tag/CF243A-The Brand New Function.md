# The Brand New Function

## 题目描述

Polycarpus has a sequence, consisting of $ n $ non-negative integers: $ a_{1},a_{2},...,a_{n} $ .

Let's define function $ f(l,r) $ ( $ l,r $ are integer, $ 1<=l<=r<=n $ ) for sequence $ a $ as an operation of bitwise OR of all the sequence elements with indexes from $ l $ to $ r $ . Formally: $ f(l,r)=a_{l} | a_{l+1} | ...\  | a_{r} $ .

Polycarpus took a piece of paper and wrote out the values of function $ f(l,r) $ for all $ l,r $ ( $ l,r $ are integer, $ 1<=l<=r<=n $ ). Now he wants to know, how many distinct values he's got in the end.

Help Polycarpus, count the number of distinct values of function $ f(l,r) $ for the given sequence $ a $ .

Expression $ x | y $ means applying the operation of bitwise OR to numbers $ x $ and $ y $ . This operation exists in all modern programming languages, for example, in language C++ and Java it is marked as "|", in Pascal — as "or".

## 说明/提示

In the first test case Polycarpus will have 6 numbers written on the paper: $ f(1,1)=1 $ , $ f(1,2)=3 $ , $ f(1,3)=3 $ , $ f(2,2)=2 $ , $ f(2,3)=2 $ , $ f(3,3)=0 $ . There are exactly $ 4 $ distinct numbers among them: $ 0,1,2,3 $ .

## 样例 #1

### 输入

```
3
1 2 0
```

### 输出

```
4```

## 样例 #2

### 输入

```
10
1 2 3 4 5 6 1 2 9 10
```

### 输出

```
11```

# 题解

## 作者：275307894a (赞：6)

[题面传送门](https://www.luogu.com.cn/problem/CF243A)

[可能更好的阅读体验](https://www.cnblogs.com/275307894a/p/14223780.html)

题解里居然没有对这个东西复杂度严格证明的，我来补一发。

首先暴力$O(n^2)$不再赘述。

可以加上一些剪枝，如果我们对于每个$i$倒序枚举每个$j$，那么如果$a_j|a_{j+1}|⋯|a_i=a_j|a_{j+1}|⋯|a_{i-1}$，那么就不用往下枚举，因为接下来的一定与前一个所枚举的相同。

然后，就过了。

代码实现:
```cpp
#include<cstdio>
using namespace std;
int n,m,k,x,y,z,a[100039],f[2000039],ans;
int main(){
	//freopen("1.in","r",stdin);
	register int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<=n;i++){
		if(!f[a[i]]) ans++,f[a[i]]=1;
		for(j=i-1;j;j--){
			if(a[j]==(a[i]|a[j])) break;
			a[j]|=a[i];
			if(!f[a[j]]) ans++,f[a[j]]=1;
		}
	}
	printf("%d\n",ans);
}
```
那么为什么这样子复杂度是对的呢?这样子看上去就是$O(n^2)$的。

观察`a[j]|=a[i];`这条语句，即如果进入这条语句，$a_j$至少有一个二进制位由$0$变成$1$，则对于每个$a_j$，最多只会被操作$loga_j$次，则总复杂度为$O(nloga_i)$，可以通过本题。

---

## 作者：DPair (赞：3)

似乎所有题解都没有给出关于复杂度的说明，这里简单说明一下。

## 【思路】

首先我们考虑一个 $O(n^2)$ 的做法。

显然我们可以考虑在 $r$ 处计算贡献，即 **暴力枚举** $r$ ，然后 **暴力向左扩展** $l$。

这样就可以算出所有区间的值。

但由于本题数据范围 $10^5$ ，考虑优化。

首先区间很容易让我们想到前缀和或者后缀和（本题中为或），显然我们在枚举 $r$ 的时候，算出的是 $[1,r]$ 区间的一段后缀或。

那么我们假设 $s[i]$ 表示 $a[i]~|~a[i+1]~|~\dots~|~a[r]$ 。

那么显然在更新 $r$ 为 $r+1$ 时，所有 $s[i]$ 都会发生 $s[i] \leftarrow s[i]~|~ a[r]$ 。

然后我们就可以从后往前暴力扫直到 $s[i]~|~a[r]=s[i]$ ，然后就可以直接 `break` 跳出了。

首先说明这是正确的。

一种解释是，我们显然在任意时候都要保证 $s[i-1]=s[i]~|~a[i-1]$ ，这里这个式子是与 $r$ 无关的。

那么若 $s[i]$ 不改变，显然 $\forall j \le i$ ，$s[j]$ 也不需要改变。

另一种解释是，我们假设 $S(x)$ 为 $x$ 在 **二进制** 下所有为 $1$ 的 **位置** 的集合，即设 $x=2^{k_1}+2^{k_2}+\dots+2^{k_{|S(x)|}}$ ，那么 $S(x)=\{k_1,k_2,k_3,\dots,k_{|S(x)|}\}$

不难发现一个性质： $S(s[i])\subseteq S(s[i-1])$ 。

而 $S(x) \subseteq S(y)$ 等价于 $x~|~y=y$ 。

所以当 $s[i]~|~a[r]=s[i]$ 时，$S(a[r])\subseteq S(s[i])$ ，故 $\forall j\le i$ ，$S(a[r])\subseteq S(s[j])$ ，故有 $s[j]~|~a[r]=s[j]$ ，不需要改变。

然后说明这复杂度是正确的。

显然若 $s[i]~|~a[r]\ne s[i]$ 时， $s[i]$ 会变为 $s[i]~|~a[r]$ ，这种情况下 $|S(s[i])|\le |S(s[i]~|~a[r])|$ 显然成立，可以理解为 $s[i]$ 的二进制位上多了一个 $1$ 。

而由于 $a_i \le 10^6$ ，那么每一个数最多被修改 $\log 10^6$ 即 $20$ 次，并且在无法修改之后不会被继续修改，故复杂度正确。

## 【代码】
只放关键部分。
```cpp
int n;
bool vis[1 << 20 | 5];
int a[100005], ans;
int main(){
    read(n);
    for (register int i = 1;i <= n;i ++){
        read(a[i]);
        if(!vis[a[i]]) {
            vis[a[i]] = 1;
            ++ ans;
        }
        for (register int j = i - 1;j;-- j){
            if((a[j] | a[i]) == a[j]) break;
            a[j] |= a[i];
            if(!vis[a[j]]) {
                vis[a[j]] = 1;
                ++ ans;
            }
        }
    }
    fprint(ans, 10);
}
```

---

## 作者：xyf007 (赞：2)

## 暴力+剪枝
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
std::set<int>s;
int n,a[100001];
int main(int argc, char const *argv[])
{
	scanf("%d",&n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&a[i]);
		s.insert(a[i]);
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = i-1; j >=0; --j)
		{
			if (a[j]==(a[j]|a[i]))
			{
				break;
			}
			a[j]|=a[i];
			s.insert(a[j]);
		}
	}
	printf("%lld\n", (long long)s.size());
	return 0;
}
```

---

## 作者：Transparent (赞：2)

### 暴力枚举 减一下枝就好了
真不知道这题怎么会是
$\color{#9d3dd2}\text{省选/NOI-}$

用一个set来存储函数结果

当一个数在二进制下全为1时，无论和什么数取或都是原来的数，这时候减掉就可以了

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005],n;
set<int>sett;
int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d",a+i);
	for(int i=1; i<=n; i++)
	{
		int x=a[i],y=0;
		sett.insert(x);
		for(int j=i+1; j<=n; j++)
		{
			x|=a[j];
			y|=a[j];
			sett.insert(x);
			if(x==y) //剪枝
				break;
		}
	}
	printf("%d\n",sett.size());
	return 0;
}
```
### 强烈建议更正难度！！！

---

## 作者：Islauso (赞：1)

## 题目大意

给出一个序列 $a$，设 $f(l,r)$ 表示 $a_l|a_{l+1}|a_{l+2}|\cdots|a_r$，求 $f(l,r)$ 有多少不同的值。

## 思路

显然，对于任意 $l$，$f(l,r)\le f(l,r+1)$，也就是说，对于从同一个数开始的所有区间，它们的值一定是随长度增加而增加的，所以，我们假设有一个变量 $t$，它从 $a_l$ 开始不停地与下一个数相或，这个 $t$ 的值增加的次数就是所有以 $a_l$ 为左端点的区间中不同的 $f(l,r)$ 的值的数量，因为 $t$ 只会增大，不会变小。

那么我们怎么知道这个 $t$ 变大了多少次呢？考虑 $t$ 在什么情况下会变大，显然，$t$ 会变大，当且仅当原来 $t$ 为 $0$ 的位变成了 $1$，而且每一位最多会变一次，所以，我们维护一个 $nxt$ 数组，用 $nxt_{i,j}$ 表示 $a_i$ 到 $a_n$ 这些数中第 $j$ 位为 $1$ 的第一个数的下标，由于有些位可能同时变成 $1$，所以我们还需要对下标进行去重。

最终时间复杂度 $O(n\log M)$，常数稍大。

## 参考代码

对于 $nxt$ 数组，这里采用的是滚动数组的方法，减小了一点空间复杂度。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+10;
struct QwQ
{
	int val;
	int id;
	bool operator < (const QwQ &a) const
	{
		return val == a.val ? id < a.id : val < a.val;
	}
};
QwQ t[30];
int n, mx, a[N], b[N*15], nxt[30];
ll ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = n; i >= 1; i--)
	{
		int x = a[i];
		for(int j = 0; j <= 20; j++)
		{
			t[j] = (QwQ){nxt[j], j};
			if((a[i]>>j)&1)
				nxt[j] = i;
		}
		sort(t, t+21);//排个序方便去重
		for(int j = 0; j <= 20; j++)
			if(t[j].val)
			{
				if(!b[x] && (j == 0 || t[j].val != t[j-1].val))
				{
					ans++;
					b[x] = 1;
				}
				x |= (1<<t[j].id);
			}
		if(!b[x])//上面那样循环会漏掉最后一个，得额外加上。
		{
			ans++;
			b[x] = 1;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：GaryH (赞：1)

看了一眼题解，发现好像都用的$STL$存答案,那我就来一发桶存储。

首先,桶排的常数肯定比$STL$小，就算$STL$时间复杂度低一些，桶排也大概率比$STL$快。

我们只要用桶来统计每个数的出现情况，最后遍历整个桶即可。

放上代码(目前最优解第2)：

```
#include<iostream>
#include<cstdio>
#include<map>
#define R register
using namespace std;
typedef int ll;
const int maxn=125000;
int n;
ll cnt;
int ans;
ll a[maxn];
ll tot[maxn*12];
inline int read(void){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(R int i=1;i<=n;i++){
		cnt=0;tot[a[i]]++;
		for(int j=i+1;j<=n;j++){
			cnt|=a[j];tot[cnt|a[i]]++;
			if((cnt|a[i])==cnt)break;
		}
	}
	for(R int i=0;i<maxn*10;i++){
		if(tot[i])ans++;
		
	}
	printf("%d",ans);
	return 0;
}
```

---

