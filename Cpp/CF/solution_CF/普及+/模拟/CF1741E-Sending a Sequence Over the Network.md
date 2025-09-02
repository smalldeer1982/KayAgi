# Sending a Sequence Over the Network

## 题目描述

The sequence $ a $ is sent over the network as follows:

1. sequence $ a $ is split into segments (each element of the sequence belongs to exactly one segment, each segment is a group of consecutive elements of sequence);
2. for each segment, its length is written next to it, either to the left of it or to the right of it;
3. the resulting sequence $ b $ is sent over the network.

For example, we needed to send the sequence $ a = [1, 2, 3, 1, 2, 3] $ . Suppose it was split into segments as follows: $ [\color{red}{1}] + [\color{blue}{2, 3, 1}] + [\color{green}{2, 3}] $ . Then we could have the following sequences:

- $ b = [1, \color{red}{1}, 3, \color{blue}{2, 3, 1}, \color{green}{2, 3}, 2] $ ,
- $ b = [\color{red}{1}, 1, 3, \color{blue}{2, 3, 1}, 2, \color{green}{2, 3}] $ ,
- $ b = [\color{red}{1}, 1, \color{blue}{2, 3, 1}, 3, 2, \color{green}{2, 3}] $ ,
- $ b = [\color{red}{1}, 1,\color{blue}{2, 3, 1}, 3, \color{green}{2, 3}, 2] $ .

If a different segmentation had been used, the sent sequence might have been different.

The sequence $ b $ is given. Could the sequence $ b $ be sent over the network? In other words, is there such a sequence $ a $ that converting $ a $ to send it over the network could result in a sequence $ b $ ?

## 说明/提示

In the first case, the sequence $ b $ could be obtained from the sequence $ a = [1, 2, 3, 1, 2, 3] $ with the following partition: $ [\color{red}{1}] + [\color{blue}{2, 3, 1}] + [\color{green}{2, 3}] $ . The sequence $ b $ : $ [\color{red}{1}, 1, \color{blue}{2, 3, 1}, 3, 2, \color{green}{2, 3}] $ .

In the second case, the sequence $ b $ could be obtained from the sequence $ a = [12, 7, 5] $ with the following partition: $ [\color{red}{12}] + [\color{green}{7, 5}] $ . The sequence $ b $ : $ [\color{red}{12}, 1, 2, \color{green}{7, 5}] $ .

In the third case, the sequence $ b $ could be obtained from the sequence $ a = [7, 8, 9, 10, 3] $ with the following partition: $ [\color{red}{7, 8, 9, 10, 3}] $ . The sequence $ b $ : $ [5, \color{red}{7, 8, 9, 10, 3}] $ .

In the fourth case, there is no sequence $ a $ such that changing $ a $ for transmission over the network could produce a sequence $ b $ .

## 样例 #1

### 输入

```
7
9
1 1 2 3 1 3 2 2 3
5
12 1 2 7 5
6
5 7 8 9 10 3
4
4 8 6 2
2
3 1
10
4 6 2 1 9 4 9 3 4 2
1
1```

### 输出

```
YES
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：lenlen (赞：17)

自己做完之后简单的看了一下题解，发现大家都是用 dp 去做的，（看来这有我这个蒟蒻想不到这题是 dp 了qwq），而我是用搜索，也能过，而且跑的还算快 78ms。

### Problem

题目大意：给定一个序列 $b$，问序列 $b$ 有没有可能是任意一个序列 $a$ 通过下列方式得出来的：

1. 将序列 $a$ 分成若干段

2. 将每一段的段长插入到该段的左边或者右边

数据范围： $t \leq 10^4,\sum n \leq 2 \times 10^5$

### Solution

额，CF 上这只是一道 1600 的题，所以常理来说搜索应该是能过的，可能要加一点优化。

我们先把深搜打出来，再考虑如何优化。我们从点 $1$ 开始搜，搜到第 $i$ 个点的时候，显然只有两种情况，第一种是有一段的段长为 $i$，那么我们只需要继续搜索 $i+a_i+1$ 就好；第二种情况是以 $i$ 为开头的一段段长为那一段的结尾的后面一个数，那么我们就遍历 $[i+1,n]$ ，如果 $j-a_j=i$，那么就可以遍历 $j$。

```cpp
void dfs(int x)
{
    if(ans) return ;
    if(x==n+1)
    {
        ans=1;
        return ;
    }
    else if(x>n) return ;
    if(x+a[x]+1<=n+1) dfs(x+a[x]+1);
    for(int i=x+1;i<=n;i++) if(i-x==a[i]) dfs(i+1);
}
```

TLE 了第 18 个点。

然后我们考虑优化，我们可以发现有一个地方非常耗时间，就是第二种情况的时候我们遍历了相当一遍 $n$，而实际需要继续搜索下去的必定比我们遍历的少的多，而我们可以预处理出来，存到 vector 里。

```cpp
for(int i=n;i>1;i--) if(i-a[i]>0) t[i-a[i]].push_back(i);
//
void dfs(int x)
{
    if(ans) return ;
    if(x==n+1)
    {
        ans=1;
        return ;
    }
    else if(x>n) return ;
    if(x+a[x]+1<=n+1) dfs(x+a[x]+1);
    int l=t[x].size();
    for(int i=0;i<l;i++) dfs(t[x][i]+1);
}
```

继续 TLE，TLE 了第 21 个点。

接着优化，我们可以发现我们搜完第 $i$ 个点以后，若没有出答案，那么显然以 $i$ 为开头的这一段后缀是无法被任意一个序列构造出来的，所以再搜 $i$ 就没有意义了，所以我们可以把搜过的点记录一下，不要反复搜。

```cpp
void dfs(int x)
{
    vis[x]=false;
    if(ans) return ;
    if(x==n+1)
    {
        ans=1;
        return ;
    }
    if(x+a[x]+1<=n+1&&vis[x+a[x]+1]) dfs(x+a[x]+1);
    int l=t[x].size();
    for(int i=0;i<l;i++) if(vis[t[x][i]+1]) dfs(t[x][i]+1);
}
```

最后我们可以发现，深搜中每个点只会搜索一次，所以时间复杂度为 $O(n)$，也就可以跑过了。

### Code

完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+32;
int n,T,ans;
int a[N];
bool vis[N];
vector<int> t[N];
void dfs(int x)
{
    vis[x]=false;
    if(ans) return ;
    if(x==n+1)
    {
        ans=1;
        return ;
    }
    if(x+a[x]+1<=n+1&&vis[x+a[x]+1]) dfs(x+a[x]+1);
    int l=t[x].size();
    for(int i=0;i<l;i++) if(vis[t[x][i]+1]) dfs(t[x][i]+1);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);ans=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),t[i].clear(),vis[i]=true;
        vis[n+1]=true;
        for(int i=n;i>1;i--) if(i-a[i]>0) t[i-a[i]].push_back(i);
        dfs(1);
        if(ans) printf("YES\n");
        else printf("NO\n");
    }
}
```


---

## 作者：RuntimeErr (赞：15)

考虑 dp，设 $f_i$ 表示 $[1,i]$ 是否合法。

假设当前 $a_i$ 是表示区间长度的值，通过之前合法的情况递推：

+ 若它在所表示区间的左边，则 $[1,i+a_i]$ 合法的充分条件是 $[1,i-1]$ 合法。

+ 若它在所表示区间的右边，则 $[1,i]$ 合法的充分条件是 $[1,i-a_i-1]$ 合法。 

答案就是 $f_n$ 是否合法。

```cpp
//main code:

const int N=2e5+10;
 
int n,a[N];
bool dp[N];
 
void solve(){
    read(n);
    for(int i=1;i<=n;++i)read(a[i]);
    memset(dp,0,sizeof dp);dp[0]=1;
    for(int i=1;i<=n;++i){
        if(i+a[i]<=n)dp[i+a[i]]|=dp[i-1];
        if(i-a[i]-1>=0)dp[i]|=dp[i-a[i]-1];
    }
    if(dp[n])printf("YES\n");
    else printf("NO\n");
}
```

---

## 作者：Hedgehog_210508 (赞：6)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1741E)

**思路**：简单的 dp。

$f_i$ 表示前 $i$ 个是否可以还原。显然，若前 $i$ 个可以还原，那么第 $i$ 个元素只有两种可能性：要么是一块的末尾，要么是块的长度。对于第二种，直接查询前 $i-a[i]-1$ 个是否符合，再加上这一块；对于第一种，在这一块的开头预先处理，若前 $i$ 个符合，那么前 $i+1+a[i+1]$  也符合。

记得初始化。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		ll n,a[200009],f[200009];
		cin>>n;
		for(ll i=1;i<=n;f[i]=0,i++) cin>>a[i];
		f[1]=0;
        f[0]=1;
		for(ll i=0;i<=n;i++){
			if(i-a[i]-1>=0) if(f[i-a[i]-1]) f[i]=1;
			if(f[i]&&i+1+a[i+1]<=n) f[i+1+a[i+1]]=1; 
		}
		if(f[n]) cout<<"yes";
		else cout<<"no";
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：Symbolize (赞：3)

# 思路
动态规划。

## 步骤
### 第一步
定义 $f$ 数组，$f_i$表示截止前 $i$ 个数，是否可以完成变换。能则为 $1$，否则为 $0$.
### 第二步
状态转移方程推导：
因为在变换之前的数组 $a$，要分成若干段，再将长度，加入数组前面或后面，所以有两个状态转移方程。
#### 放前面
我们假设第 $i$ 个数是增加的长度。那么 $i-a_i$ 就是这段变化段的起始位置。那如果说 $i-a_1-1$ 是可以完成变换的，那就说明除了 $i-a_i$ 及以后的数以外，其余都分好了。那截止第 $i$ 个数，不就一定可以完成变换吗？

所以代码表达如下

`if(i-a[i]-1>=0&&f[i-a[i]-1]) f[i]=1; //记得判断下标，不可越界`
#### 放后面
同理，我们假设第 $i$ 个数是增加的长度。那么 $i+a_i$ 就是这段变化段的终止位置。那如果说 $i+a_1+1$ 是可以完成变换的，那就说明除了 $i+a_i$ 及以后、前的数以外，其余都分好了。那截止第 $i$ 个数，不就一定可以完成变换吗？

别急，有个小细节，$i+a_i+1$ 在 $i$ 后面，所以我们可以到过来，目前的 $i$ 若经过第一个状态转移方程后，以可以完成变换，那么我们则将 $i+a_i+1$ 的值附为 $1$。

所以代码表达如下

`if(f[i]) if(i+a[i+1]+1<=n) f[i+a[i+1]+1]=1;//同样需判断下标`

### 第三步
循环遍历后，判断 $f_n$ 输出即可。

# code
下面附上 AC 代码！！！
```
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e6+10;
using namespace std;
int t,n,a[N];
bool f[N];
void getans()//处理每组数据
{
	cin>>n;
	memset(f,0,sizeof f);//清空数组
	rep1(i,1,n) cin>>a[i];
	f[0]=1;//递推起点 
	rep1(i,0,n)//循环遍历
	{
		if(i-a[i]-1>=0&&f[i-a[i]-1]) f[i]=1;//第一个状态转移方程 
		if(f[i]) if(i+a[i+1]+1<=n) f[i+a[i+1]+1]=1;//第二个状态转移方程 
	}
	if(f[n]) puts("YES");//如果可以变换
	else puts("NO");//否则
    return;
}
signed main()
{
	cin>>t;
	while(t--) getans();//循环要答案
	return 0;//收场
}
/*
思路：
DP：
f[i]表示截止第i个数，是否能够满足
状态转移方程：
1.如果f[i-a[i]-1]=1,那么f[i]=1
i-a[i]是如果f[i]是加入前a[i]个数后的长度 ，如果i-a[i]前一位可以完成操作，那么一定在f[i]可以完成
2.如果f[i+a[i]+1]=1,那吗f[i]=1
i+a[i]是如果f[i]是加入后a[i]个数前的长度，如果 i+a[i]后一位可以完成操作，那么一定在f[i]可以完成
dp过程：
先判断f[i-a[i]-1]是否OK，若OK，f[i]=1，再由f[i]拓展出f[i+a[i]+1]=1 
*/ 
```


---

## 作者：flying_man (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1741E)

题意：有两个序列，分别记为 $a$ 和 $b$。

将 $a$ 分成若干块，然后将每块的序列个数放在块的左边或右边，得到的新序列为 $b$。

现给定 $b$，让你求出是否存在 $a$ 序列经过上述转换能得到 $b$。

------------
**题解部分：**

我们设 $dp_i$ 为由 $b$ 的前 $i$ 个数字组成的新序列是否存在所对应的 $a$ 序列。

我们有两种途径对当前第 $i$ 个数进行转移：

1. 如果 $b_i$ 不为 $a$ 序列上的数，则第 $i$ 个数前面 $b_i$ 个数均为一个块，由 $dp_{i-b_i-1}$ 转移。
1. 如果 $b_i$ 为 $a$ 序列上的数，则前面需有一个数（下标为 $j$），满足 $j+b_j = i$，用 vector 预处理后一一计算即可。

详细内容请看代码。

------------
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005];
bool dp[200005];
void in(int &s){
	char c;s = 0;
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9')
		s=s*10+c-'0',c = getchar();
}
vector<int> p[200005];
int main(){
	in(t);
	while(t--){
		for(int i = 1;i <= n;i++) dp[i] = 0;//初始化切忌使用 memset！
		dp[0] = 1;//初值
		for(int i = 1;i <= n;i++) p[i].clear();
		in(n);
		for(int i = 1;i <= n;i++){
			in(a[i]);
			if(i+a[i] <= n) p[i+a[i]].push_back(i);//预处理
		}
		for(int i = 2;i <= n;i++){//容易得出dp[1]一定为0，所以从2开始
			if(i-a[i] > 0) dp[i] |= dp[i-a[i]-1];//途径1
			for(int j = 0;j < p[i].size();j++){
				dp[i] |= dp[p[i][j]-1];//途径2
			}
		}
		if(dp[n]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：WaterSun (赞：2)

# 思路

考虑 DP。

$dp_i = 1/0$ 表示前 $i$ 位 能/不能 被构造出。

那么我们的状态转移方程就很好想了。

一共可以分为两种情况：

1. 第 $i$ 位作为末尾时，我们只用看第 $i - a_i - 1$ 是否成立即可。

2. 第 $i$ 位作为长度时，我们就可以直接将 $i + a_{i + 1} + 1$ 预先标记出来。（这时候，我们需要判断第 $i$ 位是否成立）

式子如下：

$$dp_i = dp_i \vee dp_{i - a_i - 1}$$

$$dp_{i + 1 + a_{i + 1}} = dp_{i + 1 + a_{i + 1}} \vee dp_i$$

这里为什么可以用或操作呢？

原因是：我们当前的位置，只要成立过或者现在能成立，那么，我们的整个式子就是成立的，因此我们可以用上或运算来简化代码。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10;
int T,n;
int arr[N];
bool dp[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + c - 48;
		c = getchar();
	}
	return r * w;
}

int main(){
	T = read();
	while (T--){
		memset(dp,false,sizeof(dp));
		dp[0] = true;
		n = read();
		for (re int i = 1;i <= n;i++) arr[i] = read();
		for (re int i = 0;i <= n;i++){
			if (i - arr[i] - 1 >= 0) dp[i] |= dp[i - arr[i] - 1];//方程 
			if (i + 1 + arr[i + 1] <= n) dp[i + 1 + arr[i + 1]] |= dp[i];
		}
		if (dp[n]) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：sixrc (赞：2)

都可以 dp 了，这启示我们可以把它转成图论做（）

考虑对于每一个点 $s$ 作为开头，$a_s$ 表示该段长度，那么对应这一段的结尾就是 $t=s+a_s$。注意判断是否 $>n$。

考虑对于每一个点 $t$ 作为结尾，$a_t$ 表示该段长度，那么对应这一段的开头就是 $s=t-a_t$。注意判断是否 $\le 0$。

把每一个 $s \to t$ 连边，从 $1$ 开始 bfs，最后判断能否走到 $n$ 即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, p, a[200010], h[200010], vis[200010];
struct node{
	int x, y, next;
}d[400010];
void add(int x, int y){
	d[++p].y = y, d[p].next = h[x], h[x] = p;
}
int main(){
	scanf ("%d", &t);
	while (t --){
		scanf ("%d", &n);
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			h[i] = vis[i] = p = 0;
		}
		if (n == 1){
			puts ("NO");
			continue;
		}
		for (int i=1; i<=n; i++){
			if (i + a[i] <= n) add(i, i+a[i]);
			if (i - a[i] >= 1) add(i-a[i], i);
		}
		queue <int> q; q.push(1), vis[1] = 1;
		while (!q.empty()){
			int x = q.front(); q.pop();
			for (int i=h[x]; i; i=d[i].next){
				int y = d[i].y;
				if (!vis[y]){
					vis[y] = 1;
					q.push(y+1);
				}
			}
		}
		printf (vis[n] ? "YES\n" : "NO\n");
	}
	return 0;
}

```

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题一看就是一个假的动态规划，只需要用一个标记数组来表示从 $1$ 到 $i$ 是否合法即可，因为长度只能加在此数组两边那么一个数只有可能是长度或数组中的数，那么我们就可以去看 $a_i$ 作为添加在前面的长度与后面的长度所能更新的数即可。那么动态转移方程就是 $\operatorname{if} (i-a_i\geq 1) f_i=\max (f_i,f_{i-a_{i}-1})$ 代表这个数作为长度在后面且开始点在范围内，若在范围能则将起点的状态与此状态的最大值遗传给 $f_i$ 第二个方程就是长度在数组前面的情况 $\operatorname{if}(i+a_{i+1}+1\leq n) f_{i+a_{i+1}+1}=\max (f_i,f_{i+a_{i+1}+1})$ (同理只要在范围内就将此位的状态与原状态中的最大值传给结尾），这样就能保证最后一位一定能更新到因为若合法的话最后一位一定位长度或最后一位。
# AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n,a[200009],f[200009];
signed main(){
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],f[i]=0;
		f[0]=1;
		for(int i=0;i<=n;i++) {
			if(i-a[i]>=1) f[i]=max(f[i],f[i-a[i]-1]);
			if(i+a[i+1]+1<=n) f[i+a[i+1]+1]=max(f[i],f[i+a[i+1]+1]);
		}
		if(f[n]) cout<<"yes\n";
		else puts("no");
	}
	return false;
}
```


---

## 作者：qwq___qaq (赞：1)

容易想到线性 dp。

状态定义：$dp_{i}$ 表示以 $i$ 为最后一个元素是否可行。

对于 $a_{i}$ 作为长度放在右侧，那么有：`dp[i]|=dp[i-a[i]-1]`，因为此时的区间是 $[i-a_i,i-1]$。

对于该区间长度放在右侧，每一个位置都有对应的右端点，我们可以直接用 `vector` 把这些位置存储在里面，这样我们每次就可以直接遍历可行的元素，每个元素一次，可以做到线性。

时空复杂度均为 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int T,n,a[maxn],dp[maxn];
vector<int> t[maxn];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			dp[i]=0;
			t[i].clear();
			t[i].shrink_to_fit();
		}
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			if(i+a[i]<=n)
				t[i+a[i]].push_back(i-1);
		}
		dp[0]=1;
		for(int i=1;i<=n;++i){
			if(i-a[i]>=1)
				dp[i]|=dp[i-a[i]-1];
			for(int j=0,len=t[i].size();j<len;++j)
				dp[i]|=dp[t[i][j]];
		}
		puts(dp[n]?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：Ayano_ (赞：0)

[更好的阅读体验](https://www.luogu.com.cn/blog/aacbe/post-ti-jie-cf1741e)

本蒟蒻的第一篇题解。

这道题我看大家都是用一维 DP 做的，本蒟蒻今天在考场上写了种二维 DP 的做法。我个人认为这种可能理解起来会简单一些（虽说写起来麻烦了点），于是就有了这篇题解。

# 思路
当时（考场上）想了半天没想出来怎么使用一维 DP 解决这道题，便想了一种二维 DP 的做法。

我们定义 $f[0][i]$ 表示以 $i$ 作为一段的头部时是否可行，$f[1][i]$ 表示以 $i$ 作为一段的结尾是否可行。并且在原序列中添加两个点：$0$ 和 $n+1$。

状态转移（以下 $i$ 均指当前考虑的位置）：

- 头的转移  
1. 如果上一个位置可以作为尾，那么这个位置就可以作为头。  
也就是 $f[0][i] = f[1][i-1]$    
2. 如果当前位置作为头，那么下一段的头的位置也可以作为头。  
也就是 $f[0][i+a[i]+1] = f[0][i]$  
- 尾的转移
1. 如果上一段的尾的位置可以做尾，则当前位置可以做尾。  
也就是 $f[1][i] = f[1][i-a[i]-1]$  
2. 如果这一段的头的位置可以做头，那么当前位置也可以做尾。  
也就是 $f[1][i]=f[0][i-a[i]]$  

**注意**：写代码的时候要注意下标不能越界。

根据以上的转移（可能有点乱），我们能知道初始状态为：
$$
f[1][0] = f[0][1] = 1
$$

而最后我们只需要判断第 $n$ 个位置能否做尾或第 $n+1$ 个位置能否做头就好。

# 代码
（供群众批判）
```c++
#include <bits/stdc++.h>
using namespace std;

int n;
int a[200010];
bool f[2][200010];
/*
  0: 作为头
  1: 作为尾
 */

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		memset(f, 0, sizeof f); // 多测不清空，爆零两行泪
		f[1][0] = 1;
		f[0][1] = 1;
		for (int i = 1; i <= n; i++) {
			// i作为头
			// 从上一个是尾转移
			f[0][i] |= f[1][i-1];
			// 隐藏情况：之前有人帮它更新了
			// 更新下一个可能作为头的
			if (f[0][i] && i+a[i]+1 <= n+1) f[0][i+a[i]+1] = 1;
			// i作为尾
			if (i-a[i]-1 >= 0) f[1][i] |= f[1][i-a[i]-1];
			if (i-a[i] >= 0) f[1][i] |= f[0][i-a[i]];
		}
		if (f[1][n] || f[0][n+1]) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}
```

---

## 作者：EnofTeiPeople (赞：0)

有人在 VP，有人在 VP，我没有 VP，秒切后看到了 [lenlen](/user/478885)。

首先，我们将一段序列与其添加在左右两端的数字看做一段，记 $f_r=1/0$ 表示以是否存在以 $r$ 结尾的合法方案，初始化 $f_0=1$。

于是可以考虑一段是左端为长度还是右端为长度，如果 $f_i=1$，那么可以递推到 $f_{b_{i+1}+i+1}=1$，即考虑以 $i+1$ 为左端点长度的新段。

如果是以右端点为长度，那么有 $f_i->f_i|f_{i-a_i-1}$，于是就可以递推后判断 $f_n$ 即可：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a[N];
bitset<N>f;
void add(int p){
    if(p<=n)f[p]=1;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>T;
    int i;
    while(T--){
        cin>>n;
        for(i=1;i<=n;++i)cin>>a[i],f[i]=0;
        add(a[1]+1),f[0]=1;
        for(i=1;i<=n;++i){
            if(i-a[i]-1>=0&&f[i-a[i]-1])f[i]=1;
            if(f[i])add(a[i+1]+i+1);
        }
        puts(f[n]?"YES":"NO");
    }return 0;
}
```

---

## 作者：ningago (赞：0)

简单DP。

设 $dp_i$ 表示 $[i,n]$ 是否珂以被几个区间（连带他们的 _长度_ ）覆盖。

预处理 $n$ 个集合 $v_i$ 表示如果这个点 $i$ 作区间左端点，且 _长度_ 放在区间右边，_长度_ 所在的下标可能有哪些。

显然有 $i\in v_{i - a_i} (i - a_i \in [1,n])$。

则DP有两种转移，分别是：

$$dp_i = dp_{i+a_i+1}$$

$$dp_i = \bigvee_{j\in v_i}dp_{j+1}$$

$\bigvee$ 表示或。

答案显然为 $dp_1$。

时间复杂度显然为 $O(n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <vector>

#define N 200010

int T;
int n;
int a[N];
std::vector <int> v[N];
bool dp[N];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)
			scanf("%d",&a[i]);
		for(int i = 1;i <= n;i++)
			if(i - a[i] >= 1)
				v[i - a[i]].push_back(i);
		dp[n + 1] = 1;
		for(int i = n;i >= 1;i--)
		{
			int sz = v[i].size();
			if(i + a[i] + 1 <= n + 1)
				dp[i] |= dp[i + a[i] + 1];
			for(int j = 0;j < sz;j++)
				dp[i] |= dp[v[i][j] + 1];
		}
		if(dp[1])
			printf("YES\n");
		else
			printf("NO\n");
		for(int i = 1;i <= n + 1;i++)
			dp[i] = 0,v[i].clear();
	}
	return 0;
}
```

---

## 作者：Deft_t (赞：0)

## 思路：
这是一道比较简单的线性 DP。  
使用 $f[i]$ 表示前 $i$ 个数是否能完整组成为一个合法序列。  
然后考虑转移，根据题意分两种情况。
- 把 $b[i]$ 作为下一段合法序列写在左侧的数值，那么下标为 $i+b[i]$ 的就是在当前情况下，下一段合法序列的结尾。需要前提是 $f[i-1]$ 为真，因为 $b[i-1]$ 必须可以作为上一段结尾，这一段才能开始 。
- 把 $b[i]$ 作为当前这段合法序列写在右侧的数值，前提是第 $i-b[i]-1$ 个数必须可以作为上一段的结尾。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
int n;
int b[200005];
bool f[200005];
int main()
{
	ios::sync_with_stdio(NULL);
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i = 1;i <= n;i++) cin>>b[i],f[i] = false;
		if(n==1){
			cout<<"NO"<<endl;
			continue;
		}
		f[0] = true;
		if(b[1]+1 <= n){
			f[b[1]+1] = true;
		}
		for(int i = 2;i <= n;i++){
			if(f[i-1] && b[i]+i<=n) f[b[i]+i] = true;
			
			if(i-b[i]-1 >= 0 && f[i-b[i]-1]) f[i] = true;
			
		}
		if(f[n]) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：aimcf (赞：0)

DP。

设 $f_i$ 为 $1\sim i$ 是否可以分割。

那么如果长度在序列的左边，那么有 $f_{i - 1} \rightarrow f_{i + a_i}$。

如果长度在序列的右边，那么有 $f_{i - a_i - 1} \rightarrow f_i$。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
int a[N], f[N];

signed main()
{
  int T;
  cin >> T;
  while (T --)
  {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++)
      cin >> a[i];
    for (int i = 1; i <= n; i ++)
      f[i] = 0;
    f[0] = 1;
    for (int i = 1; i <= n; i ++)
    {
      if (i + a[i] <= n)
        f[i + a[i]] |= f[i - 1];
      if (i - a[i] >= 1)
        f[i] |= f[i - a[i] - 1];
    }
    if (f[n])
      cout << "Yes\n";
    else
      cout << "No\n";
  }
}

```

[AC](https://www.luogu.com.cn/record/89659503)


---

## 作者：zsseg (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1741E)

### 题意：

定义一个长为 $n$ 的序列 $A$ 是好的，当且仅当 $A_1=n-1$ 或 $A_n=n-1$。给定一个序列 $a$ 求其是否能被划分成若干个好的序列。

### solution:

先考虑暴力做法

```cpp
//dfs(l,i) 为当前扫到第 l 个点，前面有 i 个点没有被划分是否可行，有如下代码：
inline bool dfs(int l,int i){
	if(l>n)return !i;
	if(a[l]==i)if(dfs(l+1,0))return 1;//是右端点
	if(i==0)if(dfs(l+1,-a[l]))return 1;//是左端点
	if(dfs(l+1,i+1))return 1;//不是端点
	return 0;
}
```

可以发现，要想成功划分，$a_n$ 必须是序列的端点。对于一个下标 $i$，若前面都被划分好，则可以将 $i-i+a_i$ 都划分到 $i$ 中，即 $ok_{i-1}\to ok_i,ok_{i+a_i}$，同样，若前面 $a_i$ 个都没被划分，就可以将它们划分到 $i$ 中，即 $ok_{i-a_i-1}\to ok_i$。

由此，我们可以写出朴素代码($ok_i$ 表示 $i$ 是否可以是端点)：

```cpp
inline int slove(){
	bool ok[N]={};
	ok[0]=1;
	f(i,1,n){
		if(a[i]<=i-1)if(ok[i-a[i]-1])ok[i]=1;
		f(j,1,i-1)if(ok[j-1])ok[j+a[j]]=1;
	}
	return ok[n];
}
```

显然，这个代码时间复杂度为 $\varTheta(n^2)$，无法通过。

我们考虑如何维护 $ok_{i-1}=1\to ok_{i+a_i}=1$

显然，扫到一个下标 $i$ 时，我们给 $i+a_i$ 打一个标记 $i-1$，若扫到 $i+a_i$ 时，所有标记有一个为 $1$，则更新为 $1$，防止炸空间，用二维 $\text{vector}$ 维护。

因为标记至多有 $n$ 个，时间复杂度 $\varTheta(n)$，空间复杂度 $\varTheta(n)$。

### Code:

```cpp
#include <bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return f?x:-x;
}
int n,a[200010];
bitset<200010> ok;
inline int slove(){
	ok.reset();
	ok[0]=1;
	vector<vector<int> > oks;
	vector<int> q;
	f(i,1,n+1)oks.push_back(q);//防止 RE
	f(i,1,n){
		for(int j=0;j<oks[i].size();j++){
			if(ok[oks[i][j]])ok[i]=1;//更新标记	
		}
		if(a[i]<=i-1)if(ok[i-a[i]-1])ok[i]=1;//向前更新
		if(i+a[i]<=n)oks[i+a[i]].push_back(i-1);//打标记
	}
	return ok[n];
}
signed main(){
	int T=read();
	while(T--){
		n=read();
		f(i,1,n)a[i]=read();
		puts(slove()?"YES":"NO");
	}
}
```


---

