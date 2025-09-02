# [ABC356C] Keys

## 题目描述

你有 $N$ 个编号为 $1, 2, \dots, N$ 的密钥。  
其中一些是真钥匙，其他都是假钥匙。

有一扇 X 门，你可以插入任意数量的钥匙。只有插入至少 $K$ 把真钥匙，X 门才会打开。

你已经对这些钥匙进行了 $M$ 次测试。第 $i$ 次测试过程如下：

- 您将 $C_i$ 把 $A_{i,1}, A_{i,2}, \dots, A_{i,C_i}$ 把钥匙插入了 X 门。
- 测试结果用一个英文字母 $R_i$ 表示。
    - $R_i =$ o "表示在第 $i$ 次测试中，X 门打开了。
    - $R_i =$ x "表示在第 $i$ 次测试中，X 门没有打开。

有 $2^N$ 种可能的钥匙组合，其中哪些是真钥匙，哪些是假钥匙。在这些组合中，找出与任何测试结果都不矛盾的组合数。  
给定的测试结果有可能是错误的，没有任何组合满足条件。在这种情况下，报告 $0$ 。

## 说明/提示

#### 限制因素

- $N$ 、 $M$ 、 $K$ 、 $C_i$ 和 $A_{i,j}$ 为整数。
- $1 \le K \le N \le 15$
- $1 \le M \le 100$
- $1 \le C_i \le N$
- $1 \le A_{i,j} \le N$
- $A_{i,j} \neq A_{i,k}$ 如果 $j \neq k$ .
- $R_i$ 是 `o` 或 `x`。

#### 样例 $1$ 说明

在此输入中，有三个键，进行了两次测试。  
打开 X 门需要两把正确的钥匙。

- 在第一次测试中，使用了钥匙 $1, 2, 3$ ，X 门打开了。
- 在第二次测试中，使用了钥匙 $2, 3$ ，X 门没有打开。

有两种组合，哪把钥匙是真钥匙，哪把钥匙是假钥匙，测试结果都没有矛盾：

- 钥匙 $1$ 是真的，钥匙 $2$ 是假的，钥匙 $3$ 是真的。
- 密钥 $1$ 是真实的，密钥 $2$ 是真实的，密钥 $3$ 是假的。

#### 样例 $2$ 说明

如问题陈述所述，答案可能是 $0$ 。

## 样例 #1

### 输入

```
3 2 2
3 1 2 3 o
2 2 3 x```

### 输出

```
2```

## 样例 #2

### 输入

```
4 5 3
3 1 2 3 o
3 2 3 4 o
3 3 4 1 o
3 4 1 2 o
4 1 2 3 4 x```

### 输出

```
0```

## 样例 #3

### 输入

```
11 4 9
10 1 2 3 4 5 6 7 8 9 10 o
11 1 2 3 4 5 6 7 8 9 10 11 o
10 11 10 9 8 7 6 5 4 3 2 x
10 11 9 1 4 3 7 5 6 2 10 x```

### 输出

```
8```

# 题解

## 作者：LuukLuuk (赞：5)

# 题解：AT_abc356_c [ABC356C] Keys

#### 题目大意
给你 $N$ 把钥匙，其中有一些是假的。有一扇门，要插至少 $K$ 把真钥匙才能开。现在你进行了 $M$ 次测试，每次在门上插的是编号从 $A_{i,1}$ 到 $A_{i,C_i}$ 的钥匙，若门开了，就是 o，没开就是 x。问你有多少组由 $N$ 把真钥匙和假钥匙组成的可以与上面测试结果相同的组合。

例如样例一，就是告诉你第 $1,2,3$ 把钥匙可以把门打开，第 $2,3$ 把钥匙不能开门，则可能的钥匙组合为以下两种：

- 钥匙一是真的，二是真的，三是假的。
- 钥匙一是真的，二是假的，三是真的。

----------------------------------------------
#### 题解

拿到题，我们先看数据范围：

- $1 \le K \le N \le 15$
- $1 \le M \le 100$

看到那个 $15$ 了吗？没错，这道题就是我们喜闻乐见的暴力题。

显然，直接暴力是会超时的。所以怎么暴力呢？很简单，我们再想一想上面的 $1 \le N \le 15$，我们就会想到状压动规。不过，我们这道题不需要动规，单单状压就可以了（毕竟是第三题）。

正如上面所说的，我们定义 $i$ 为判断真假钥匙的状态，其中真钥匙所属的位为 $1$，假钥匙为 $0$；$b_x$ 为第 $x$ 次尝试时的状态，其状态的表示与 $i$ 同理，用了的为 $1$，没用的为 $0$。我们对每个 $i$ 进行 $m$ 次循环来枚举每个 $b_j$ 以对 $i$ 的合法性进行判断。具体地，我们定义一个初值为 $ 0$ 变量 `flag`，表示初始状态下 $i$ 一定合法，然后在 $m$ 次循环中做下列操作来判断 $i$ 是否不合法：

```
flag = flag || ((count(b[j] & i) >= k) != r[j]);
```

其中，函数 `count(x)` 表示 $x$ 在二进制下 $1$ 的个数；$b_j$ 按位与 $i$ 是为了筛选出既是真的又被插上的钥匙；$r_j$ 表示门的状态，$1$ 为开，$0$ 为关；`!=` 是为了判断是否当前状态在插第 $j$ 次时门的状态是否和输入一致，因为 `flag` 初值为 $0$，所以取反。

完整代码如下：
```c
#include <cstdio>
using namespace std;

int c[110], a[110][110], r[110];
int b[110];
char s[110];
int n, m, k;
int ans;

int count(int x) {
	int cnt = 0;
	while (x) {
		x = x & (x - 1);
		cnt++;
	}
	return cnt;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &c[i]);
		for (int j = 1; j <= c[i]; ++j) {
			scanf("%d", &a[i][j]);
			b[i] += (1 << (a[i][j] - 1));
		}
		scanf("%s", s + 1);
		if (s[1] == 'o') {
			r[i] = 1;
		} else {
			r[i] = 0;
		}
	}
	
	for (int i = 0; i < (1 << n); ++i) {
		int flag = 0;
		for (int j = 1; j <= m; ++j) {
			flag = flag || ((count(b[j] & i) >= k) != r[j]);
		}
		if (!flag) {
			ans++;
		}
	}
	
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：4)

这题其实就是暴力。

我们可以暴力枚举哪一些钥匙是真的，然后判断每个条件是否能满足输入即可。

代码如下。

```cpp
#include <iostream>
using namespace std;

int n, m, k;

int a[105][20], c[105], pd[105], ans;
bool vis[20];

void dfs(int step, int now) {
	int ttttt = 1;
	for(int i = 1; i <= m; i++) {
		int ttt = 0;
		for(int j = 1; j <= c[i]; j++) {
			if(vis[a[i][j]]) ttt++;
		}
		if(ttt >= k && !pd[i]) ttttt = 0;
		if(ttt < k && pd[i]) ttttt = 0;
	}
	if(ttttt) ans++;
	for(int i = now + 1; i <= n; i++) {
		if(!vis[i]) {
			vis[i] = 1;
			dfs(step + 1, i);
			vis[i] = 0;
		}
	}
}

int main() {
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++) {
		cin >> c[i];
		for(int j = 1; j <= c[i]; j++) {
			cin >> a[i][j];
		}
		char x;
		cin >> x;
		if(x == 'o') pd[i] = 1;
		else pd[i] = 0;
	}
	dfs(1, 0);
	cout << ans;
}
```

---

## 作者：ToastBread (赞：0)

# ABC356 C 题解
## 思路
关注数据范围：

-   $1 \le K \le N \le 15$
-   $1 \le M \le 100$
-   $1 \le C_i \le N$
-   $1 \le A_{i,j} \le N$

很明显可以发现，数据范围还是很小的，自然想到**枚举**。可以发现，题目中明确说到有 $2^N$ 种可能的答案，每种答案要花 $\mathcal O(NM)$ 的时间枚举，那么时间复杂度就是 $\mathcal O(2^N \times NM)$，最坏情况下大约执行 $5 \times 10^7$ 次运算，绰绰有余。

所以思路出来了：暴力枚举所有可行的答案，对于每一种可行的答案，判断是否满足条件。

这里提供一种搜索的方案（$26$ 毫秒）和一种枚举与拆分的方案（$40$ 毫秒），按需取用。

具体的实现思路可以看我的代码。


## AC 代码
### DFS 搜索
```cpp
#include<iostream>
using namespace std;
int n,m,k,c,x,ans,nowp[20],inp[105][20];//ans答案，nowp现在的枚举，inp输入，这里为了简单，并没有使用传统的存答案方法
bool isok[105];//门开了吗 
char ch;
void dfs(int step)
{
	if(step>n)//检查 
	{
		bool now=1;
		for(int i = 1; i <= m; i++)
		{
			int nowclac=0;//现在能开门的钥匙数量 
			for(int j = 1; j <= n; j++)
			{
				nowclac+=(inp[i][j]*nowp[j]);//等效于(inp[i][j]?nowp[j]:0) 
			}
			if((nowclac>=k)!=isok[i])//不成立 
			{
				now=0;
				break;
			}
		}
		if(now) ans++;//成立 
		return;
	}
	nowp[step]=1;
	dfs(step+1);//dfs 
	nowp[step]=0;
	dfs(step+1);
}
int main()
{
	cin>>n>>m>>k;
	for(int i = 1; i <= m; i++)
	{
		cin>>c;
		for(int j = 1; j <= c; j++)
		{
			cin>>x;
			inp[i][x]++;//这里为了判断做铺垫，没有直接存，转而统计“这个钥匙在这个方案中出现了吗”。 
		}
		cin>>ch;
		isok[i]=(ch=='o');//判断能开门吗 
	}
	dfs(1);//dfs 
	cout<<ans;
	return 0;
}
```
### for 循环拆分
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,k,c,x,ans,nowp[20],inp[105][20];//ans答案，nowp现在的枚举，inp输入，这里为了简单，并没有使用传统的存答案方法
bool isok[105];//门开了吗 
char ch;
void cf(int x)//拆分 
{
	for(int j = 1; j <= n; j++)
	{
		nowp[j]=x&1;
		x/=2;
	}
}
void check()//与dfs的check一样 
{
	bool now=1;
	for(int i = 1; i <= m; i++)
	{
		int nowclac=0;//现在能开门的钥匙数量 
		for(int j = 1; j <= n; j++)
		{
			nowclac+=(inp[i][j]?nowp[j]:0);//等效于(inp[i][j]?nowp[j]:0) 
		}
		if((nowclac>=k)!=isok[i])//不成立 
		{
			now=0;
			break;
		}
	}
	if(now) ans++;//成立 
	return;
}
int main()
{
	cin>>n>>m>>k;
	for(int i = 1; i <= m; i++)
	{
		cin>>c;
		for(int j = 1; j <= c; j++)
		{
			cin>>x;
			inp[i][x]++;
		}
		cin>>ch;
		isok[i]=(ch=='o');
	}
	for(int i = 0; i < pow(2,n); i++)
	{
		cf(i);//拆分
		check();//判断 
	}
	cout<<ans;
	return 0;
}

```

结束了。

---

## 作者：OPEC (赞：0)

# [[ABC356C] Keys](https://www.luogu.com.cn/problem/AT_abc356_c)

这道题 $n\le 15$ 是一道暴力题，只需 DFS 每一个钥匙选不选，然后对每种方法进行查验，最后统计总数。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e2+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int n,m,k,ans;
int c[N];
char r[N];
int a[N][N];
int b[N];
bool check()
{
	for(int i=1;i<=m;i++)
	{
		int sum=0;
		for(int j=1;j<=c[i];j++)
		{
			if(b[a[i][j]])
				sum++;
		}
		if(r[i]=='o')
		{
			if(sum<k)
				return 0;
		}
		else
		{
			if(sum>=k)
				return 0;
		}
	}
	return 1;
}
void dfs(int x,int s)
{
	b[s]=x;
	if(s==n)
	{
		if(check())
			ans++;
		return;
	}
	for(int i=0;i<=1;i++)
	{
		dfs(i,s+1);
	}
}
signed main()
{
	fst
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		cin>>c[i];
		for(int j=1;j<=c[i];j++)
		{
			cin>>a[i][j]; 
		}
		cin>>r[i];
	}
	dfs(0,0);
	cout<<ans;
	return 0;
}
```

---

