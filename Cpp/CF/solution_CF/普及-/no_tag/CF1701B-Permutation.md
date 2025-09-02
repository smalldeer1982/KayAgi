# Permutation

## 题目描述

Recall that a permutation of length $ n $ is an array where each element from $ 1 $ to $ n $ occurs exactly once.

For a fixed positive integer $ d $ , let's define the cost of the permutation $ p $ of length $ n $ as the number of indices $ i $ $ (1 \le i < n) $ such that $ p_i \cdot d = p_{i + 1} $ .

For example, if $ d = 3 $ and $ p = [5, 2, 6, 7, 1, 3, 4] $ , then the cost of such a permutation is $ 2 $ , because $ p_2 \cdot 3 = p_3 $ and $ p_5 \cdot 3 = p_6 $ .

Your task is the following one: for a given value $ n $ , find the permutation of length $ n $ and the value $ d $ with maximum possible cost (over all ways to choose the permutation and $ d $ ). If there are multiple answers, then print any of them.

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
2
1 2
3
2 1 3```

# 题解

## 作者：Haber (赞：4)

### 题目大意

你需要找到一个排列 $p$,和一个正整数 $d$，使得排列中满足 $p_i \times d=p_{i+1}$ 的 $i$ 的个数最多。在这篇题解中，我们把 $p_i$ 和 $p_{i+1}$ 称为一个满足条件的数对。

输出此时的 $d$ 和 $p$。

### 题目总评

构造题，主要考思维，代码实现并不难。还有SPJ，好评。

### 解题方案

从简单入手。

首先假设有一个 $i$ 满足了 $p_i \times d=p_{i+1}$，还有另外一个 $j$ 并且也可以满足 $p_j\times d=p_{j+1}$。这样我们就有了2个可以满足题目要求的数对。但是我们想，能不能用这两个数对创造出更大的价值？

当 $p_{i+1}\times d=p_j$ 的时候，就会产生3个满足条件的数对！

整理一下，$p_i\times d=p_{i+1}$，$p_{i+1}\times d=p_j$，$p_j\times d=p_{j+1}$。这不就是一个等比数列吗？

此时我们易得一个有 $x$ 项的等比数列，可以产生 $x-1$ 对满足条件的数对，并且这是数字利用率最高的一种构造方法。~~一堆废话~~

当然这个等比数列的公比就是 $d$。因为我们期望这个等比数列的项数越多越好，所以要让这个 $d$ 尽量小。$d$ 为正整数，所以 $d_{min}=2$。

具体构造方法：先以 $1$ 为首项，构造公比为 $2$ 的等比数列，直到快要超过极值 $n$ 时停止。再以 $3$ 为首项($2$ 用过了)构造等比数列，同理构造到极致。再以 $5$ 为首项同理构造。再以 $7$ 为首项……切记**构造的都是公比为 $2$ 的等比数列。**

千万不要认为这里的首项就都是质数。想一下 $9$ 就明白了，在前面的构造中，$9$ 是没有用过的。所以这里的首项都是奇数，因为偶数前面都用过了。

### 代码实现

理论分析完了，看代码吧。

代码真的简单，两个循环。外层控制首项，内层算具体每一项。

**代码:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<2<<endl;
		for(int i=1;i<=n;i+=2)	//首项为奇数
			for(int j=i;j<=n;j*=2)	//公比为2
				cout<<j<<" ";
		cout<<endl;
	}
	return 0;
}
```

亲测能过。~~不会被Hack吧？~~

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1Nf4y1o7Cx)

### 2 思路

设最终成本为 $ans$。

我们可以发现，当 $d=1$ 时，$ans$ 必为 $0$。

并且我们可以发现，如果采用最优的解法，每个小于等于 $\lfloor\dfrac{n}{d}\rfloor$ 的数能够产生 $1$ 个贡献（我们可以让它后面成为它的 $d$ 倍而小于等于 $n$）。也就是说，$ans=\lfloor\dfrac{n}{d}\rfloor$。

那么，当 $d=2$ 时 $ans$ 最大。

我们进行模拟即可。

首先肯定是 $1,2,4,8……$，然后是 $3,6,12,24……$，等等等等。要求所有数字必须小于等于 $n$。

输出即可。

### 3 代码与记录

```cpp
//Luogu submission
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
bool vis[max_n+2];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1701B_1.in","r",stdin);
	freopen("CF1701B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)vis[i]=false;
		printf("%d\n",2);
		for(int i=1;i<=n;++i){
			if(vis[i])continue;
			for(int j=i;j<=n;j<<=1){
				printf("%d ",j);
				vis[j]=true;
			}
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/78922239)

By **dengziyue**

---

## 作者：BetaCutS (赞：1)

因为 $p$ 为排列，所以 $d=1$ 时成本为 $0$。所以 $d\ge2$。

设成本为 $c$，因为只有小于等于 $\left\lfloor\dfrac{n}{d}\right\rfloor$  的数才有一个小于等于 $n$ 的数与它配对，而每个小于等于 $\left\lfloor\dfrac{n}{d}\right\rfloor$ 的数对 $c$ 产生 $1$ 的贡献，所以 $c=\left\lfloor\dfrac{n}{d}\right\rfloor$。

之前已经说了，$d\ge2$，所以 $d$ 取 $2$ 必定是最优解之一。

所以可以第一个数是 $1$，接着如果上一个数小于等于 $\left\lfloor\dfrac{n}{2}\right\rfloor$，这个数就是上一个数乘 $2$；否则是最小的前面没有出现过的数。

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=2e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T,n,vis[N],a[N],cnt;
//vis记录每个数是否用过
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		memset(vis,0,sizeof vis);
		cnt=0;
		for(int i=1;i<=n;i++)
			if(!vis[i])
			{
				int x=i;
				while(x<=n)
					a[++cnt]=x,vis[x]=1,x*=2;
			}
		puts("2");
		for(int i=1;i<=n;i++)
			printf("%d ",a[i]);
		puts("");
	}
	return 0;
}

```


---

## 作者：Qerucy (赞：1)

这是一道构造题。

如何构造？首先我们要算出 $d$。

因为我们要让代价尽可能的大，所以 $ p_{i + 1} $ 就要尽可能的小。因为如果 $ p_{i + 1} $ 变小的话，排列选择的方案就变多，代价也变得更大。

而 $ p_{i + 1} $ 是由 $ p_i \cdot d $ 得来的，所以如果要 $ p_{i + 1} $ 尽可能的小的话，$d$ 就要尽可能的小。

因为 $p$ 是排列，所以在 $p$ 中没有重复的数字，所以 $d$ 不为 $1$。

所以 $d$ 最小为 $2$。

然后我们以 $ d = 2 $ 来构造即可。

代码：

```cpp
#include<cstdio>
#include<cstring>

using namespace std;

bool vis[1000010];
int t;
int n;
int now;

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		puts("2");//先输出d
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++){
			if(vis[i]) continue;//如果这个数已经出现在排列中了，就跳过
			now=i;
			while(now<=n){//如果这个数没有出现在排列中，就从这个数开始构造
				printf("%d ",now);
				vis[now]=1;
				now*=2;
			}
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：hanzhang666 (赞：0)

# 分析
典型的贪心。 

首先算出 $d$。

我们要让代价最大，即 $d$ 尽可能小。由于排列中没有相同的数，所以 $d\not=1$。

综上知 $d=2$。

以 $d=2$ 为条件构造即可。此题得解。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int flag[200005]; 
signed main(){
	int T=read();
	while(T--){
		int n=read();
		puts("2");
		for(int z=1;z<=n;z++){
			flag[z]=0;
		}
		for(int z=1;z<=n;z++){
			for(int i=z;i<=n;i*=2){
				if(!flag[i]){
					cout<<i<<" ";
					flag[i]=1;
				}
				else break;
			}
		}
		puts("");
	}
}
```


---

## 作者：xzy090626 (赞：0)

## 题意
构造一个长为 $n$ 的排列 $p$ 以及一个常数 $d$，使得 $p$ 中满足 $p_i \cdot d = p_{i+1}(1 \le i < n)$ 的 $p_i$ 数量最多。

本题多测，共有 $t$ 组数据。

数据范围：$1 \le t \le 500$，$1 \le n \le 2 \times 10^5$，所有 $n$ 的总和不大于 $2 \times 10^5$。
## 分析
考虑贪心。

先分析 $d$ 的大小。

我们可以发现，所有满足条件的 $p_i$ 的数量一定不大于 $\log_d n$。又由于当 $d \le 1$ 时无法满足条件，所以我们直接让 $d=2$ 就行了。

---
接下来就是 $p$ 的构造了。

由于 $d=2$，我们不妨先设 $p_1 = 1$，使得 $p$ 尽可能最优。

接着，为了使满足条件的 $p_i$ 最多，我们要让后面的 $p_i$ 的值都为 $p_{i-1} \times 2$，直到 $p_i > n$ 为止。

接下来，我们设现在的 $p_i$ 为 $3$，则 $p_{i+1} = 6$，以此类推。

这样就能得出最优解了。

写的时候记得判 $p_i$ 的大小就行。

---

## 作者：yanhao40340 (赞：0)

### 题意
给定正整数 $n$，求一个 $1 \sim n$ 的排列 $p$ 和一个正整数 $d$，使得满足 $p_{i+1}=p_i \times d$，$1 \le i < n$ 的数量最多。

若有多种答案，输出任意一种即可。
### 确定 $d$
因为要使满足题意的数量最多，所以要让每一个数的贡献都尽量大。

考虑排列中的一个数 $x$。若要让 $x$ 的贡献最大，那么就把 $\dfrac{x}{d}$ 放在 $x$ 的左边（$d \mid x$），把 $dx$ 放在 $x$ 的右边（$x \le \dfrac{n}{d}$），这样贡献最大。

为了使尽量多的 $x$ 的贡献都达到最大值，我们就要选择一个 $d$，使得满足

$$\begin{cases} x=dk&1\le k \le \dfrac{n}{d}, k \in \mathbb{Z} \\ x \le \dfrac{n}{d}\end{cases}$$

的 $x$ 最多。显然，

$$x \in \{dk \mid k,1 \le k \le \dfrac{n}{d^2}\}$$

时贡献最大，即 $\dfrac{n}{d^2}$ 要最大。所以 $d=2$ 时，可以找到排列 $p$，使得符合题意的数量最大。
### 构造 $p$
根据 $x$ 贡献最大值的取法可知，公比为 $2$ 的等比数列贡献最大。

所以我们可以由一些等比数列来组成 $p$。取排列中还没有出现的最小数作首项，以 $2$ 作公比，构造等比数列。

最后把构造出的等比数列连起来，就是一个满足条件的排列 $p$。
### 代码
实现的有些麻烦，不喜勿喷。
```cpp
#include <iostream> 
#include <set>
#include <vector>
using namespace std;
set<int> s;//判断是否未出现
vector<int> v;//存答案
int main(){
	int t,n;scanf("%d",&t);
	while (t--){
		scanf("%d",&n);s.clear();v.clear();puts("2");
		for (int i=1;i<=n;++i) s.insert(i);
		while (!s.empty()){
			for (int i=*(s.begin());i<=n;i<<=1)
				v.push_back(i),s.erase(i);
		}
		for (int it:v) printf("%d ",it);
		putchar('\n');
	}
	return 0;
}
```
### 注记
思考：既然 $d$ 要尽量小，为什么 $d$ 不取 $1$？

---

## 作者：Night_sea_64 (赞：0)

大家好，本蒟蒻又来写题解了~~~

[题目](https://www.luogu.com.cn/problem/CF1701B)

主要知识点是贪心。

---

### 题目大意：

#### 题目描述

对于一个数 $n$ 以及这个数的的全排列 $p$ 和一个正整数常量 $d$，定义这个全排列的价值为 $p_i\times d=p_{i+1}$ 的个数 $(1≤i<n)$。

现给定 $n$，求出价值最大的 $p$ 以及该情况下的 $d$。

#### 输入格式

第一行，一个正整数 $t$，表示数据组数。

对于每组测试数据，输入一个正整数 $n$。

#### 输出格式

对于每组测试数据，第一行输出正整数 $d$，第二行输出 $n$ 个正整数用空格隔开，表示 $p$。如果有多种答案，输出任何一个都可以。

---

### 题解

先确定 $d$。$d=2$ 情况下当然会出来更多的倍数，所以都让 $d=2$ 就可以了。

接下来全排列怎么构造呢？尽可能让后一个数都是前一个数的两倍，不难想到，我们可以选一个数，然后做这个数开头，公比为 $2$ 的等比数列，直到下一个数大于 $n$。

但是选哪个数作为开头呢？不能选偶数作为开头，因为偶数可以让一个奇数不断 $\times\text{ }2$ 得到。所以只能选奇数作为开头。而奇数是没有在之前的等比数列里出现过的，所以它 $\times\text{ }2,\times\text{ }4,\dots$ 都不会在前面的等比数列里出现过。

这样这道题就做完了，以下是 AC 代码（短的可怜）：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        cout<<2<<endl;
        for(int i=1;i<=n;i+=2)
            for(int j=i;j<=n;j<<=1)
                cout<<j<<" ";
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：ZhanPJ (赞：0)

题目传送门：[CF1701B](https://www.luogu.com.cn/problem/CF1701B)

---

**题目大意：**

你需要用数字 $1 \sim n$（每个数字不重复使用）构造出一个序列 $p$，并确定一个正整数 $d$。使得在序列 $p$ 中，$p_i \times d = p_{i+1}$ 的次数最多。

如果有多个解，输出任意一组即可，不要求 $d$ 最大。

---

**解题思路：**

~~这场比赛我跟着打的，然后这题害得我只做出来了两道题。~~

- 所需性质及其证明：

性质 $1$：$p_i$ 所乘的 $d$ 越小，$p_i < p_i \times d \leq n$ 的可能性越大。

设有一个新的正整数 $c$，且保证 $d < c$。由于要保证 $p_i < p_i \times d$，所以 $d$ 的取值范围为 $d > 1$。

那么我们可以由此得出 $p_i < d \times p_i < c \times p_i$。

那么在 $c \times p_i > n$ 时，$d \times p_i$ 是**有可能**小于等于 $n$ 的。（如 $p_i = 19,n=198,d=10,c=11$ 时，$p_i < p_i \times d \leq n < c_i \times c$）

那么通过这个式子，我们可以了解到在任何情况下，我们求的序列 $p$ 中的值 $p_i$ 所乘的 $d$ 越小，$p_i < p_i \times d \leq n$ 成立的可能性越大。

性质 $2$：$d$ 的**固定取值**为 $d=2$。

因为 $1$ 乘任何数结果为原数，所以 $d \not = 1$。

因为性质 $1$ 的存在，且题目已经说明 $d > 0$。根据上面所说 $d \not =1$ 可以推导出 $d > 1$。那么可得 $d = 2$ 是不等式 $d > 1$ 的最小整数解。

- 解题：

我们通过上述的性质 $2$，我们已经确定了 $d=2$ 那么接下来的步骤就是建立序列。

建立序列的时候考虑数字遍历的重复。因为我们枚举 $p_i \times 2$ 的时候已经用掉了一些数字。那么在第一层大循环中，用掉的数字需要跳过，即建议一个数组储存数字的使用情况。

---

**通过代码：**

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
bool vis[200005];
int main(){
	int T,n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(vis,0,sizeof(vis));
		printf("2\n");
		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			for(int j=i;j<=n;j*=2){
				printf("%d ",j);
				vis[j]=1;
			}
		}
		printf("\n");
	}
	
	return 0;
}
```

---

**修改**：

2022 年 8 月 4 日：修改了性质 $1$ 的证明过程和性质 $2$ 的描述。

---

## 作者：郑朝曦zzx (赞：0)

# 解题思路
本题贪心，比较好想的一个思路是把 $d$ 取最小然后构造。

构造方法：

先输出所有 $2$ 的次幂，然后输出 $3$ 乘上 $2$ 的次幂，以此类推。

比如当 $n$ 为 $10$ 的时候，我们是这样构造的：
```cpp
1 2 4 8 3 6 5 10 7 9
```
贪心的证明：

结论比较显然，以二为底的 $\log(n)$ 一定比以其他为底的值更大。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
bool use[200010];
int main()
{
	scanf("%d", &t);
	while (t--)
	{
		memset(use, 0, sizeof(use)); 
		scanf("%d", &n);
		printf("2\n");
		for (int i = 1; i <= n; ++i)
		{
			int tmp = i;
			if (use[i] == 0)
			{
				while (true)
				{
					printf("%d ", tmp);
					tmp *= 2;
					if (tmp > n || use[tmp]) break;
					use[tmp] = 1;
				}
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：osfly (赞：0)

简单构造题。

很明显的，当 $d=2$ 的时候代价最大。

---

证明：

$\because p_i\cdot d=p_{i+1}$

当 $d$ 减小时，$p_i\cdot d$ 也在减小，$p_{i+1}$ 也在减小，

那么 $p_{i+1}$ 减小时，$p_{i+1}$ 可供选择的数就越多，代价也随即越大，

那么 $d$ 在取最小值时，代价最大，

因为 $p$ 是个排列，所以没有重复数字，所以 $d$ 最小值为 $1$。

---

所以我们对于 $d=2$ 来构造即可

```cpp
#include<cstdio>
#include<cstring>
int t;
int n;
int a[200010];
bool vis[200010];
int tot;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		tot=0;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			if(!vis[i])//如果这个数已经出现在排列中，由于排列的不重复性，所以不能选择该数
				for(int j=i;j<=n;j*=2)
				{
					a[++tot]=j;
					vis[j]=1;//标记，代表此数已出现在排列中
				}
		printf("2\n");
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
	}
	return 0;
}
```

---

