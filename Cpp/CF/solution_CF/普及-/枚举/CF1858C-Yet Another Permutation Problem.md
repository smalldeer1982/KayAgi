# Yet Another Permutation Problem

## 题目描述

# 又一个排列问题


Alex 收到了一个名为 "GCD 排列" 的游戏作为生日礼物。这个游戏的每一轮进行如下操作：

- 首先，Alex 选择一个整数序列 $ ^{\dagger} $ $ a_1, a_2, \ldots, a_n $ ，其中整数范围从 $ 1 $ 到 $ n $ 。
- 然后，对于每个 $ i $ 从 $ 1 $ 到 $ n $ ，计算整数 $ d_i = \gcd(a_i, a_{(i \bmod n) + 1}) $ 。
- 本轮的得分是 $ d_1, d_2, \ldots, d_n $ 中不同数字的数量。

Alex 已经玩了几轮游戏，所以他决定找一个整数序列 $ a_1, a_2, \ldots, a_n $ ，使得它的得分尽可能地大。

回顾一下，$ \gcd(x, y) $ 表示 $ x $ 和 $ y $ 的 [最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor)，而 $ x \bmod y $ 表示将 $ x $ 除以 $ y $ 的余数。

 $ ^{\dagger} $ 长度为 $ n $ 的排列是一个由 $ n $ 个不同整数组成的数组，整数范围从 $ 1 $ 到 $ n $ 且顺序任意。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是排列（数组中有重复的 $ 2 $），$ [1,3,4] $ 也不是排列（虽然 $ n=3 $，但数组中有 $ 4 $）。

## 说明/提示

在第一个测试用例中，Alex 想要找一个由整数 $ 1 $ 到 $ 5 $ 组成的排列。对于排列 $ a=[1,2,4,3,5] $，数组 $ d $ 等于 $ [1,2,1,1,1] $。它包含 $ 2 $ 个不同的整数。可以证明，长度为 $ 5 $ 的排列中没有比这个得分更高的。

在第二个测试用例中，Alex 想要找一个由整数 $ 1 $ 到 $ 2 $ 组成的排列。只有两种这样的排列：$ a=[1,2] $ 和 $ a=[2,1] $。在这两种情况下，数组 $ d $ 都等于 $ [1,1] $，所以这两种排列都是正确的。

在第三个测试用例中，Alex 想要找一个由整数 $ 1 $ 到 $ 7 $ 组成的排列。对于排列 $ a=[1,2,3,6,4,5,7] $，数组 $ d $ 等于 $ [1,1,3,2,1,1,1] $。它包含 $ 3 $ 个不同的整数，所以得分等于 $ 3 $。可以证明，由整数 $ 1 $ 到 $ 7 $ 组成的排列中没有得分更高的。

## 样例 #1

### 输入

```
4
5
2
7
10```

### 输出

```
1 2 4 3 5 
1 2 
1 2 3 6 4 5 7 
1 2 3 4 8 5 10 6 9 7```

# 题解

## 作者：fuxuantong123 (赞：9)

# CF1858C Yet Another Permutation Problem 题解
## 题意
构造一个 $1$ 到 $n$ 的摆列，首尾相接，把相邻两数的最大公因数存起来，使其中不同的数字的个数尽可能大。
## 思路
一个简单的贪心：

> **尽可能的使所有数都作出贡献，序列的价值才是最大的。**

对于每个 $a_i$，要使其对答案做出贡献，则 $a_{i+1}$ 应是 $a_i$ 的倍数。

所以，可以先升序枚举 $a_i$，判断 $a_i \times 2$ 是否在 $1$ 到 $n$ 的范围以内。如果在，将其排在 $a_i$ 之后，即为 $a_{i+1}$。

重复此操作直到无法继续进行。此时，选择剩余能选择的数中最小的数排在 $a_i$ 后。


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100010];
int mp[100010];
inline int read(){//废物快读
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main(){
	int t=read();
	while(t--){
		int n=read();
		for(int i=1;i<=n;i++){
			mp[i]=0;
		}
		a[1]=1;
		int cnt=1;
		for(int i=2;i<=n;i++){
			int sum=i;
			if(mp[sum]==0){
				while(sum<=n){
					a[++cnt]=sum;
					mp[sum]=1;
					sum*=2;
				}
			} 
		}
		for(int i=1;i<=cnt;i++){
			printf("%d ",a[i]);
		}
		printf("\n");
	}
return 0;
}
```

---

## 作者：Siegerkranz_2735 (赞：3)

#### 简化题意

在这个问题中，给定一个正整数 $n$，你需要找到一个排列 $a$，其中 $a_i$ 是从 $1$ 到 $n$ 的不同整数，使得对于每个 $i$（$1 \leq i \leq n$），$d_i = \gcd(a_i, a_{(i \bmod n) + 1})$ 的值尽可能多。这里 $d_i$ 是排列中相邻两个数的最大公约数。

你的任务是找到这样的排列 $a$。

*（顺便推荐一下我的翻译）

#### 解决方案

如果 $d_i$ 的种类有 $k$ 个，显然 $2×k \leq n$ 时才有解。

这是因为一 $[\frac{n}{2}+1,n]$ 之间的数不可能是两个 $[1,n]$ 内的不同的数的 $\gcd$ ,所以 $k$ 最多只能取 $\lfloor \frac{n}{2}\rfloor$。

构造也非常简单，我们让序列 $\{ d_n\}$ 中有 $[1, \frac{n}{2}]$ 中的每个正整数就可以。

暴力即可：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define M 300005
int T,n,ans[M],f[M];
int main(){
    for(scanf("%d",&T);T--;){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)f[i]=0;
        for(int i=1;i<=n/2;++i){
            if(!f[i]){
                int now=i;
                for(;now<=n/2;printf("%d ",now),f[now]=1,now*=2);
                printf("%d ",now);
                f[now]=1;
            }
        }
        for(int i=n/2+1;i<=n;++i)if(!f[i])printf("%d ",i);
        printf("\n");
    }
    return 0;
}
```


---

## 作者：Iniaugoty (赞：2)

大意：求出一个 $n$ 的排列，使相邻两个数的最大公因数中不同的数最多。

使不同的数最多，就要尽可能地使每个数都成为一个 GCD。可以把每个数的倍数（如果范围内有的话）都放在旁边。因为越大的数在范围内的倍数就越少，把最小的倍数（除自身外）即 $2$ 倍数放在旁边一定是最优的。

实现很简单：

```cpp
ans[cnt = 1] = 1;
F(i, 2, n) vis[i] = 0;
F(i, 2, n) {
	if (vis[i]) continue;
	for (int j = i; j <= n; j <<= 1)
		vis[j] = 1, ans[++cnt] = j;
}
```

---

## 作者：Jie_Xu_Sheng (赞：2)

### 题意

让你输出一个排列，使得相邻两数的 $\gcd$ 构成的集合的 $size$ 最大（第 $n$ 个和第 $1$ 个也算相邻）。

### 思路

在 $1$ 到 $n$ 之中两数能产生的 $\gcd$ 为 $1,2,…,n$。

所以如果我们能够造一个使得相邻两数的 $\gcd$ 构成的集合包含 $1,2,…,n$ ，那么肯定是最大的。

如果每一个数后面放他的二倍，那么 $\gcd$ 集合就包含了这个数。

所以构造就很容易了。从 $1$ 依次遍历到 $n$ ，如果$i$ 还没有出现过，那么就在序列中依次放 $i,2i,4i,8i,…$。

这样，每一个 $1$ 到 $n/2$ 的数后面都是它的二倍，这两数的 $\gcd$ 就是这个数，一定是最优的。

 ### Code
 
 [CF1858C Yet Another Permutation Problem](https://codeforces.com/contest/1858/submission/218962302)

---

## 作者：信息向阳花木 (赞：2)

~~虽然但是这场 C 不是比 B 简单吗？~~

赛时推的奇葩结论。

想让一个序列两两最大公约数不同的数最多，我们可以在一个数后面摆上它的倍数，这样最大公约数就是这个数本身。由于这是一个排列，可以证明，这样摆不同的最大公约数最多。

举个例子，当 $n = 9$ 时：
* $a_1 = 1, a_2 = 2, a_3 = 4, a_4 = 8$。
* $3$ 是此时最小的还没用过的数字，因此 $a_5 = 3, a_6 = 6$。
* $5$ 是此时最小的还没用过的数字，因此 $a_7 = 5$。
* $a_8 = 7,a_9=9$

这样构造，$a = \{1, 2, 4, 8, 3, 6, 5, 7\}$，两两最大公约数分别为 $1,2,4,8,1,3,1,1,1$，不同数的个数最大。

时间复杂度 $O(n)$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010;

int t, n, m;
int a[N];
bool st[N];

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		memset(st, 0, sizeof st);
		
		scanf("%d", &n);
		for (int i = 1; i <= n; i ++ )
		{
			if(!st[i])
			{
				st[i] = 1;
				printf("%d ", i);
				for (int j = i * 2; j <= n; j *= 2 )
				{
					if(!st[j])
					{
						printf("%d ", j);
						st[j] = 1;
					}
				}
			}
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Q3284489219 (赞：1)

# CF1858C Yet Another Permutation Problem 题解

#### 题目大意

构造一个 $n$ 的排列 $p$,使得相邻两数的 $\gcd$ 集合去重后大小最大。

#### 题目分析

首先我们考虑，如果我们想得到两个数的 $\gcd$ 为 $x$ 且这两个数最小，应如何选择这两个数？

显然，当这两个数分别为 $x,2x$ 时，这两个数最小。

于是，我们得到一个性质：我们最后的 $\gcd$ 集合中一定存在所有小于等于 $\frac n 2$ 的数，因为我们必然可以将这些数与其二倍相邻，而 大于 $\frac n 2$ 的数，根据上述分析，则必然不会出现在 $\gcd$ 集合中。

那么，构造数组就十分简单了，对于一个最小的还未被选择的数，首先输出它本身，然后将其一直 $\times 2$ 输出，直到其大于 $n$。

#### 证明

现在，我们来证明为何 最后的 $\gcd$ 集合中一定存在所有小于等于 $\frac n 2$ 的数。

考虑反证法，假设存在一个 $x \leq \frac n 2$ 不在 $\gcd$ 集合中 , 设 $x$ 与 $y$ 相邻，易得 $y$ 不是 $x$ 的倍数。若 $\gcd(x,y)=r$，因为 $r$ 可以与 $2r$ 相邻，所以这样做并不会增加集合中的数，所以不如 $x$ 与 $2x$ 相邻优，证毕。

#### 代码

```c++
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double

using namespace std;

int n;
bool vis[100005];

void init(){
	memset(vis,0,sizeof(vis));
	cin>>n;
	cout<<1<<" ";
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			cout<<i<<" ";
			vis[i]=1;
			for(int j=2;j*i<=n;j*=2){
				cout<<j*i<<" ";
				vis[j*i]=1;
			}
		}
	}
	cout<<endl;
}

int main(){
	int t;
	cin>>t;
	while(t--)
	    init();
	return 0;
}
```

萌新第一篇题解，求通过。

---

## 作者：Bad_Luck_No_Fun (赞：1)

一道超级简单的题目。

~~话说 cf 的 C 题这么简单。~~

我们发现这是一个构造题。

我们先找能够构造出来理论最大值。

易得，这个理论最大值就是最大数除以二的下取整。

如何构造呢。

我们可以把每个偶数和他的二分之一的那个数放在一起。

则一个数最多和两个数在一起，放在一左一右即可。

剩下的奇数直接原封不动放在后面。

容易证明这种构造方法可以构造出理论上的最大值。

最后直接上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)
# define maxn 100005
typedef long long ll;
template<typename T> void read(T &x){
	x=0;int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
	x*=f;
}
bool vis[maxn];
int ans[maxn];
int T, n, tot;
int main()
{
	read(T);
	while(T--){
		read(n);
		tot = 0;
		for(int i = 1; i <= n; i++) vis[i] = 0;
		for(int i = 1; i <= n; i++)
			if(!vis[i])
				for(int j = i; j <= n; j *= 2)
					ans[++tot] = j, vis[j] = 1;
		for(int i = 1; i <= n; i++) cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}

```


---

## 作者：SamHJD (赞：1)

## [CF1858C Yet Another Permutation Problem](https://www.luogu.com.cn/problem/CF1858C)

**题意**

你需要构造一种 $1\dots n$ 的排列，并围成一个环，使每一个数和下一个数的最大公约数组成的数组中不同的数最多。

**解法**

我们的贪心策略是让每一个数都尽可能成为最大公约数数组的一项，也就是找一个他的倍数放在他后面。

我们从 $1\dots n$ 枚举，每次 $\text{while()}$ 找当前数的二倍，若还没被取则放入答案数组，被取则跳出循环进入下一个数。

设当前数为 $x$，若循环中 $x^m$ 被取，设取走这个数的数为 $y$，则 $y^{m+p}=x^m,p>0$，那么 $y^p=x$，$y$ 一定会把 $x$ 取走。因此可以直接跳出。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T,n,vis[N],ans[N],k;
int main(){
	scanf("%d",&T);
	while(T--){
		memset(vis,0,sizeof(vis));
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			if(vis[i]) continue;
			for(int x=i;x<=n&&!vis[x];x*=2) vis[x]=1,ans[++k]=x;
		}
		for(int i=1;i<=n;++i) printf("%d ",ans[i]);puts(""); 
	}
	return 0;
}
```

---

## 作者：Gao_yc (赞：1)

# Solution：

首先讲构造：从小到大枚举还没加入答案数组的数 $i$，将 $i\times 2^j \le n$ 加入答案数组（$j$ 从 $0$ 开始枚举）

### 证明：

容易发现，对于任意 $2i \le n$，$2i$ 必定紧跟着 $i$ 后被加入答案数组，因此 $\gcd(i,2i)=i$ 一定能对答案产生贡献。

而对于 $2i \gt n$，显然不存在两个不超过 $n$ 的数，满足他们的最大公因数为 $i$。

因此，这样构造出来的答案必定是最优的。

复杂度 $\mathcal{O}(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],ans[N],cnt;
bool vis[N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
        for(int i=1;i<=n;++i) vis[i]=0;
        cnt=0;
		for(int i=1;i<=n;++i){
            if(vis[i]) continue;
            for(int j=i;j<=n;j<<=1) ans[++cnt]=j,vis[j]=1;
        }
        for(int i=1;i<=n;++i) printf("%d ",ans[i]);puts("");
	}
    return 0;
}
```


---

## 作者：Microchip2333 (赞：0)

**题意简述**

一个长度为 $n$ 的排列 $a$ 构成一个环，定义数组 $d$ 中的元素为 $a$ 中所有任意两个相邻的元素的最大公约数，现在请你构造一个排列 $a$，使得 $d$ 中不同元素的个数最大。

数据范围： $2\leq n, \sum n \leq 10^5$。

**解法**

首先可以证明，$d$ 中的最大元素 $d_{max}$ 不会超过 $\lfloor\frac{n}{2}\rfloor$，证明如下：

假设存在一个元素 $d' >d_{max}$，由于排列不会出现两个相同的元素，故此排列中一定有 $t\times n$，其中 $t \geq 2$，且 $t$ 是整数。那么当 $t$ 取最小值 $2$ 时，$d$ 数组中必须存在 $2d'$，其值一定 $>n$，与这是个长度为 $n$ 的排列矛盾，故 $d$ 中的最大元素 $d_{max} \leq \lfloor\frac{n}{2}\rfloor$。

接下来，我们对于每一个 $1\leq x\leq d$，尝试使 $x$ 的倍数与 $x$ 相邻，不难看出使 $2x$ 与 $x$ 相邻最优。 

在此构造方案中，任意一个整数 $x$ 最多只会与一个其他的数相邻，如果把每个数看成一个结点，在两个相邻的数之间从较小的向较大的连一条有向边，那么整个图将会由若干条链组成。

例如：$n = 10$ 时，由刚才的构造方案连边，得：$1\rightarrow2 ,2\rightarrow4, 3\rightarrow6, 4\rightarrow8, 5\rightarrow10$。

那么最终图为：

链 1：$1\rightarrow2\rightarrow4\rightarrow8$

链 2：$3\rightarrow6$

链 3：$5\rightarrow10$

链 4：$7$

链 5：$9$

由于链与链之间并无特殊限制，故将这些链按任意顺序输出即可。

时间复杂度：$O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int n, a[N], e[N], ne[N], h[N], idx;

bool used[N];

void add(int a, int b){
	e[idx] = b; ne[idx] = h[a]; h[a] = idx ++ ;
}

void dfs(int u){
	cout << u << " "; used[u] = true; 
	for (int i = h[u]; ~i; i = ne[i])
		dfs(e[i]); 
}

void solve(){
	cin >> n; int cnt = 2; idx = 0;
   // 初始化，记住切勿 memset, 因为时间复杂度 O(n) 会在多测下超时
	for (int i = 1; i <= n; i ++ ) h[i] = -1;
	for (int i = 1; i <= n; i ++ ) used[i] = false ;
    
	int t = 1; // 注意从 1 ~ 1*2 开始枚举，这样最大公因数就可以由 1 一直枚举到 n / 2, 是最优方案
	for (int i = 1; i <= n; i ++ ){
		if (t * 2 > n) break ;
		else add(t, t * 2);  // 加边
		t ++ ;
	}
	
   // 从 1 开始输出每条链
	for (int i = 1; i <= n; i ++ )
		if (!used[i]){
			dfs(i); 
            
	cout << endl; 
}

int main(){
	int tt = 1; cin >> tt;
	while (tt -- ) solve();
	return 0;
}

```

---

## 作者：mahaoming (赞：0)

# CF1858C Yet Another Permutation Problem 题解

### 思路

我们先找能够构造出来理论最大值。

显然，这个理论最大值就是最大数除以二的下取整。

考虑如何构造。

首先把 $1$ 放在前面，然后枚举 $i$（$i$ 为 $2$ 到 $n$），对于每个 $i$，一直乘二，直到大于 $n$ 为止。对于乘出来的每一个数，只要没有被标记过，就输出，然后标记上。这样输出的一定是最优的。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read(){
	long long s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')w=-1;
		c=getchar();
	}
	while('0'<=c&&c<='9')s=s*10+c-'0',c=getchar();
	return s*w;
}
long long t,n,v[100005];
int main(){
	t=read();
	while(t--){
		n=read();
		for(long long i=1;i<=n;i++)v[i]=0;
		v[1]=1;
		cout<<"1 ";
		for(long long i=2;i<=n;i++)
			if(!v[i]){
				long long j=i;
				while(j<=n){
					if(!v[j])cout<<j<<" ";
					v[j]=1,j*=2;
				}
			}
		cout<<endl;
	}
	return 0;
}


```


---

## 作者：Drind (赞：0)

显然 $(i \bmod n) +1$ 就等于 $i+1$。并且数组 $d$ 的数字最多也只会有 $\left\lfloor\frac{n}{2}\right\rfloor$ 个，因为最多就是 $\left\lfloor\frac{n}{2}\right\rfloor$ 和 $2 \times \left\lfloor\frac{n}{2}\right\rfloor$ 两个数的最大公约数了。

所以我们大体上可以得到一个策略，把每个小于等于 $\left\lfloor\frac{n}{2}\right\rfloor$ 的数和他的两倍放在一起。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

int vis[N],vk[N];
void fake_main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++) vis[i]=vk[i]=0;
	for(int i=1;i<=n/2;i++){
		if(vk[i]) continue;
		vk[i]=1;//vk是统计有哪个数字还没在d数组出现过
		cout<<i<<" "<<i*2<<" ";
		vis[i]=vis[i*2]=1;
		int tmp=i;
		while(tmp*2<=n/2){//一直乘2直到大于n为止
			tmp*=2;
			vk[tmp]=1;
			cout<<tmp*2<<" ";
			vis[tmp*2]=1;
		}
	}
	for(int i=1;i<=n;i++) if(vis[i]==0) cout<<i<<" ";//输出剩下的数字
	cout<<endl;
}

signed main(){
	int t;
	cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：SunnyYuan (赞：0)

## 思路

这个题是一个简单的构造题。~~竟然比 T2 简单，也是少见~~

我们可以首先从 $1$ 开始不断乘以 $2$，像这样：$1, 2, 4, 8, 16\cdots,2^x$，直到什么时候超过 $n$ 就停止。

这样相邻两个数字的 $\gcd$ 就可以凑出 $1, 2, 4, 8, \cdots,2^{x- 1}$。

$2$ 已经出现在刚刚的序列中，我们可以选择忽略。

然后我们可以从 $3$ 开始不断乘以 $2$，像这样：$3, 6, 12, 24, \dots, 3 \times 2^x$，直到什么时候超过 $n$ 就停止。

这样相邻的连个数字就可以凑出 $3, 9, 18,  \cdots, 3\times 2^{x - 1}$。

剩下的，您应该也明白了，从 $5$ 开始继续造，然后是 $7$，因为 $9$ 已经在 $3$ 的序列里了，所以 $7$ 后面的是 $11$，直到 $x > n$ 就停止。

最后把剩下的按任意顺序输出就可以了。

可以证明这是最优解。

~~1 分钟出思路系列~~

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n;
	cin >> n;
	vector<bool> a(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (a[i]) continue;
		int j = i;
		while (j <= n) {
			cout << j << ' ';
			a[j] = 1;
			j <<= 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (a[i]) continue;
		cout << i << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T;
	cin >> T;
	while (T--) solve();
	
	return 0;
}
```

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

构造题，但据说重了。

~~You're wrong,here's why.~~

## 题面大意

给定一个数 $n$，要将 $1$ 到 $n$ 的排列排成一个环，使得相邻两个数的最大公约数互异的数量最多。

## 解题思路

我们发现如下性质：$\gcd(x,kx)=x$。

那我们考虑构造多条链，链上每个值都是上一个值的倍数。

在每个点打标记，暴力找倍数就行。

```cpp
#include <stdio.h>

typedef long long i64;
const i64 mod = 1, maxn = 100007;

int T, n, li[maxn];

void find(int index)
{
    if (li[index])
        return;
    printf("%d ", index);
    li[index] = 1;
    for (int k = 2; k * index <= n; k++)
        if (li[k * index] == 0)
        {
            find(k * index);
            return;
        }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        if (n <= 2)
        {
            for (int i = 1; i <= n; i++)
                printf("%d ", i);
            puts("");
            continue;
        }
        else
        {
            for (int i = 1; i <= n; i++)
                li[i] = 0;
            printf("%d ", 1);
            for (int i = 2; i <= n; i++)
                find(i);
            puts("");
            continue;
        }
    }

    return 0;
}
```

---

## 作者：qwerasdasd1 (赞：0)

## 杂言
赛时想到做法，结果调 code 把自己心态调炸了，所以来写一篇题解（恼）。

另：此题与 [P9345 夕阳西下几时回](https://www.luogu.com.cn/problem/P9345) 几乎相同，可以此练手。

另另：本题多测，多测不清空，爆零两行泪。
## 题意翻译
$a_1,a_2, \dots ,a_n$ 是 $1$ 至 $n$ 的一个排列，记 $d_i=\gcd(a_i,a_{i\bmod n+1})$。构造一个 $\{a\}$，使 $\{d\}$ 中不同元素的个数最大。

## 知识点
数论，贪心，构造。

## 做法
显然，首先显然有 $\max\{d_i\}=\frac{n}{2}$，因为如果 $d_i > n/2 $，则必有另一个 $d_i > n$，而这是不可能的。

所以我们可以尝试构造出一个 $\{d\}$，使其中不同元素个数为 $\frac{n}{2}$，这样就能使 $\{d\}$ 中不同元素的个数最大。

贪心地想，我们从小到大枚举，对于每一个未插入的数 $a_i$ 且 $a_i \le \frac{n}{2}$，直接把 $2a_i$ 插入 $a_i$ 的后面，直到 $2a_i > n$,。接着继续枚举。

通过此方式枚举，显然对于每个 $a_i \le \frac{n}{2}$ 都能成为 $\{d\}$ 中的某个数，这么做就是最优的。

时间复杂度 $O(n)=\sum n$。

## Code
```cpp
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t;
int vis[N],ans[N];//vis数组为标记数组，ans数组即为答案序列
int main(){
	t=read();
	while(t--){
		int n=read(),cnt=0;
		memset(vis,0,sizeof(vis));
		memset(ans,0,sizeof(ans));
		for(int i=1;i<=n/2;i++){//只枚到 n/2
			int j=i;
			if(vis[j]) continue;
			while(j<=n){
				ans[++cnt]=j;
				vis[j]=1;//标记，防止重复枚举
				j*=2;
			}
			
		}
		for(int i=n/2+1;i<=n;i++){//剩下的没标记过的直接填上去即可
			if(!vis[i]) ans[++cnt]=i;
		}
		for(int i=1;i<=n;i++) printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Dawn_cx (赞：0)

## 题意

给定一个 $n$ ，要求构造一个 $1$ 到 $n$ 的排列，使得 $\gcd(a_i,a_{i\bmod n})$ 的不同的值最多。

## 思路
对于一个数 $x$ ，若想让 $x$ 对答案有贡献，至少要保证 $x$ 的最小的倍数 $2x\le n$ ，并且 $2x$ 与 $x$ 相邻，因此不同的最大公约数最多有 $\lfloor\frac{n}{2}\rfloor$ 种。

因此我们构造时只需要满：对于 $x\le\lfloor\frac{n}{2}\rfloor$ ， $2x$ 与其相邻即可。


```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int mod = 998244353;
inline void read(int &x){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch&15);ch=getchar();}
	x=s*w;
}
int T,n;
bool vis[maxn];
int main(){
	read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++)vis[i]=0;
		for(int i=n;i;i--){
			if(!vis[i]&&i%2==0){
				int now=i;
				while(now%2==0){
					vis[now]=true;
					printf("%d ",now);
					now/=2;
				}
				vis[now]=true;
				printf("%d ",now);
				now/=2;
			}
		}
		for(int i=1;i<=n;i++)if(!vis[i])printf("%d ",i);
		puts("");
	}
}
```


---

