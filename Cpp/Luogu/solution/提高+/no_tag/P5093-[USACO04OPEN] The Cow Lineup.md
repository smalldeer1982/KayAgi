# [USACO04OPEN] The Cow Lineup

## 题目描述

约翰的 $ N $（$ 1 \leq N \leq 100000 $）只奶牛站成了一列。每只奶牛都写有一个号牌，表示她的品种，号牌上的号码在 $ 1 \ldots K $（$ 1 \leq K \leq 10000 $ ）范围内。

比如有这样一个队列：1,5,3,2,5,3,4,4,2,5,1,2,3

根据约翰敏锐的数学神经，他发现一些子序列在这个队列里出现，比如"3,4,1,3"，而另一些没有。子序列的各项之间穿插有其他数，也可认为这个子序列存在。现在，他想用 $1 \sim K$ 之间的整数构造一个最短的子序列，使之不在奶牛序列里出现。达个子序列的长度是多少呢？

## 说明/提示

样例解释：

所有长度为 $1$ 和 $2$ 的可能的子序列都出现了，但长度为 $3$ 的子序列"2,2,4"却没有出现。

## 样例 #1

### 输入

```
14 5
1
5
3
2
5
1
3
4
4
2
5
1
2
3```

### 输出

```
3```

# 题解

## 作者：da32s1da (赞：26)

考虑将奶牛分组。

将$1...k$中的每个数字都出现的连续一段分成一组。

例如，样例分成$[1,5,3,2,5,1,3,4],[4,2,5,1,2,3]$两组。

容易发现，每一组的最后一个数字一定是在这一组中**最后**出现且**只出现一次**。

所以！把每个组的最后一个数字取出来，然后剩下的组不成一组的，必然存在没有出现的数字，将其取出。

所以答案是**组数+1**。

```
#include<cstdio>
#include<cstring>
const int N=10050;
int n,k,x;
int vis[N],tot,ans;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(!vis[x])vis[x]=1,tot++;
		if(tot==k){
        	//形成完整的一组，清空vis，累加答案。
			memset(vis,0,sizeof(vis));
			tot=0;
			ans++;
		}
	}
	printf("%d\n",ans+1);//组数+1
}
```

---

## 作者：ZCETHAN (赞：4)

这题是被换了么，为啥感觉题解和题面讲的不是同一个东西？/qd

## 题意简述

给你一个值域为 $k$ 的长度为 $n$ 的序列，求不是这个序列的子序列的最短长度。

## Solution

[双倍经验](https://www.luogu.com.cn/problem/AT2698)

输出方案是简单的，考虑这两题的差别就是数据范围。

先大概来康康当值域小的时候的做法。也就是上面那题。考虑 dp。

我们令 $dp_i$ 表示 $[i,n]$ 中没有出现的子序列的最短长度。那么如果当前后缀中有某一个值没有出现过，那么 $dp_i=1$；否则，我们枚举这个没有出现过的子序列的第一个数，令它在后缀中从前往后第一次出现的位置为 $j$，那么就相当于从 $dp_{j+1}$ 转移过来，即：$dp_i=dp_{j+1}+1$。在值域小的情况下，可以预处理一个数组 $nxt_{i,j}$ 表示后缀 $[i,n]$ 中 $j$ 从前往后第一次出现的位置。然后直接从后往前做，这样复杂度是 $O(nk)$ 的。

这题能获得 92pts。

现在我们考虑优化这个东西。实际上，这个 $dp_i$ 转移的时候，只不过是从后面某些点转移过来，我们不妨开一个堆来存储这些值。然后滚动掉 $nxt$，即令 $nxt_i$ 表示当前 $i$ 第一次出现的位置，然后当 $nxt_i$ 更新的时候，在堆中删去 $dp_{nxt_i+1}+1$，然后修改后重新加入。这样复杂度就变成了 $O(n\log k)$。

一个小问题就是我们希望这个堆能够删除某个特定的值，那就开两个堆，然后要删除一个元素就将其加入到第二个堆中，查询的时候，如果两个堆对顶相同就同时弹出即可。

## Code

```cpp
#include<bits/stdc++.h>
#define inf (1<<30)
#define INF (1ll<<60)
#define pb emplace_back
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define pt(a) cerr<<#a<<'='<<a<<' '
#define pts(a) cerr<<#a<<'='<<a<<'\n'
#define int long long
using namespace std;
struct Heap{
	priority_queue<int,vector<int>,greater<int>> q,del;
	void push(int v){q.push(v);}
	void pop(int v){del.push(v);}
	int top(){
		while(!q.empty()&&!del.empty()&&q.top()==del.top())
			q.pop(),del.pop();
		return q.top();
	}
}q;
const int MAXN=1e5+10;
int dp[MAXN],nxt[MAXN],c[MAXN];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,k;cin>>n>>k;
	rep(i,1,n) cin>>c[i];
	rep(j,1,k) nxt[j]=-1;
	memset(dp,0x3f,sizeof(dp));
	int cnt=0;
	per(i,n,1){
		if(nxt[c[i]]==-1) cnt++;
		else q.pop(dp[nxt[c[i]]+1]+1);
		nxt[c[i]]=i;
		q.push(dp[nxt[c[i]]+1]+1);
		dp[i]=(cnt==k?q.top():1);
	}cout<<dp[1];
	return 0;
}
```

---

## 作者：Gaode_Sean (赞：3)

这题的题意可以转化为：将序列划分成若干段，每一段都包含 $1 \sim K $ 的数，求最多能分成几段。

照这样做，就能保证有 $K^m$ 种排列（m 表示最多能分成的段数）。

最后的答案是 $m+1$ 。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+1;
int n,k,ans,cnt,a[maxn];
int main()
{
	scanf("%d%d",&n,&k);
	while(n--){
		int x;
		scanf("%d",&x);
		if(a[x]==ans) a[x]++,cnt++;
		if(cnt==k) cnt=0,ans++;
	}
	printf("%d",ans+1);
	return 0;
}
```

---

## 作者：Mysterious_Cat (赞：2)

### 题目思路：
将 $a_1 \cdot \cdot \cdot a_n$ 划分成尽量多的 $x$ 个区间，满足每个区间都包含 $1 \cdot \cdot \cdot k$ 所有元素，答案即为 $x+1$ 。

设答案为 $ans$ ，所选的数分别为 $b_1 \cdot \cdot \cdot b_{ans}$ ，$t_0\cdot\cdot\cdot t_{ans-1}$ 将 $A$ 划分为 $ans-1$ 个区间，第 $i$ 个区间为 $[t_{i-1},t_i)$ ，则 $\forall{i},i\in[1,ans-1]$ 必然满足$b_i\in[\min\limits_{t_{i-1} \le j < t_i}\{a_j\},\max\limits_{t_{i-1} \le j < t_i}\{a_j\}](1=t_0\le{t_1}\le{t_2} \cdot\cdot\cdot \le{t_{ans-1}}={n})$ 且 $b_i$ 任取 $1\cdot\cdot\cdot k$ ，否则 $\exists{b_1\cdot\cdot\cdot{b_{ans-1}}}$ 不为$A$的子序列，此时显然 $ans-1$ 更优 。 

简化上述推论，得：  

将 $A$ 分为若干段区间与 $B$ 的每一个元素一一对应，则 $b_i$ 只能取对应区间内的元素，仅当区间包含 $1\cdot\cdot\cdot k$ 所有元素时该长度下 $\forall B$ 为 $A$ 的子序列。

当答案 $ans$ 满足题目要求时，$ans-1$必然不满足题目要求，否则 $ans-1$ 更优，故 $ans$ 为最大区间数 $+1$ 。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    int x = 0;
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
    return x;
}

bool flag[100005];

int main()
{
    int a, n, k, cnt = 1, tmp = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
    {
        cin >> a;
        if(!flag[a]) flag[a] = true, tmp++;
        if(tmp == k) memset(flag, 0, sizeof(flag)), tmp = 0, cnt++;
    }
    cout << cnt;
    
    return 0;
}
```


---

## 作者：JAMES__KING (赞：1)

思路：我们首先考虑进行分组：将$1...k$中每个数字都出现的连续一段分为一组，例如样例，我们可以这样分组：

$[1,5,3,2,5,1,3,4]$为第一组，$[4,2,5,1,2,3]$为第二组，接着寻找两组数据中相同的规律。

我们很容易发现每一组的最后一个数字在整组中其它没有出现。

所以注意！标记了本组中的最后一个之后，剩下的不成一组，所有变量也要清零，重新计算。

最后的答案便是**组数+1**。

最后贴上代码：

```cpp
#include<bits/stdc++.h>
#define gets(S) fgets(S,sizeof(S),stdin)
using namespace std;
int n,k,ans,sum,f[10005],x;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(f[x]==0) f[x]=1,ans++;//还未出现
		if(ans==k)//形成一组
		{
			memset(f,0,sizeof f);ans=0;//清零
			sum++;//计数器增加
		}
	}
	printf("%d",sum+1);//组数千万记得要+1
	return 0;
}
```


---

## 作者：Bulyly (赞：1)


### 题意简述
在值域为 $ 1 $ 到 $ k $ 的序列中，求非该序列子序列序列的最短长度。
### 思路
这道题的思路还是非常好想的 很快就能够想到了用划分区间。此言怎讲，将该序列划分为若干子区间，满足子区间中的数恰满足 $ 1 $ 到   $ k $ 的数都出现，这样我们能发现每个区间的最后一个值一定是只出现过一次的，这里我就简单地来证明一下。

如果该数出现了不止一次，那么该区间是不是应该早结束了（至少是在前一位就结束了是吧） 好了，证明完毕。

接着，既然该数是该区间中最后出现的数且仅出现了一次，那么再提醒你一点，再该数后任意接一个数构成的子序列是不是一定不会在该区间内出现且是最短的，以此类推在多个区间的情况下，将每个区间最后一个值取出再任意添加一个数是不是就是最短的非原序列的子序列的序列——即为所求。
所以,我们只需要将分的组数加 $ 1 $ 即是答案！！！


------------

AC code：
```cpp
#include<bits/stdc++.h>//OvO~
#define N 10010
using namespace std;
bool sg[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int k(0),tot(0);//初始化
	for(int i=1;i<=n;i++)
	{
		int tp;
		cin>>tp;
		if(!sg[tp])  sg[tp]=1,k++;//记录
		if(k==m)  tot++,k-=k,memset(sg,0,sizeof sg);//重置
	}
	printf("%d",tot+1);
	return 0;//perfect ending!!!
 
}
```

---

## 作者：Zhou_Wingay (赞：1)

### 思路：我们将整个数组进行分割，使每个子数组都包含1$\cdots$k至少一次，例：
```cpp
15325134|425123
```
此时可以发现，我们每个子数组最后纪录的那个数一定只在这个子数组中出现一次，所以，我们选取每个子数组最后一个数，再加上任意一个数即可组成最短不存在子序列。

#### 所以，最短不存在子序列的长度为组数加一。

最后就是代码了：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,k,t,sum=1,v[10005]={0};
int main(){
	int i;
	cin>>n>>k;
	for(i=1;i<=n;i++){
		cin>>a;
		if(v[a]==0){v[a]=1;t++;}
		if(k==t){sum++;t=0;memset(v,0,sizeof(v));}
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：人间凡人 (赞：1)

这是一道**贪心**的题目。

问题是要求最短的不出现序列的长度。但是看着感觉很麻烦，无从下手。

因此，我们将问题转化一下，可以先求出最长的在序列中出现过的长度，只要将长度$+1$输出，这样问题就迎刃可解了。

思路：我们将输入的序列分为若干段，每一段都要包含$1$到$k$中的数，记录最多可分为的段数,同样$+1$就可以了。

证明：大家知道这是为什么吗?因为如果每一段都含有$1$到$k$中的数，这样只要在每段中任选一个数组合，就可以拼成所有相同位数的数。所以只用将最多可分为的段数$+1$输出即可。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,tot,x,ans,f[100005];
int main() {
	scanf("%d%d",&n,&k);tot=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(!f[x]){
			f[x]=true;
			tot++;
		}
		if(tot==k){
			ans++;
			tot=0;
			for(int j=1;j<=k;j++)f[j]=false;
		}
	}
	printf("%d\n",ans+1);
	return 0;
}

```


---

## 作者：L2_sheep (赞：1)

这题用一下贪心的策略。
- 用head｛k｝数组记录数字k第一次出现的位置。

- 用next｛i｝数组记录位置i的数下一次出现的位置。

- 用mp记录所有数head的最大值。

- 每个数的head的位置通过next数组后移，直到超过了mp。如果不存在这样的位置，直接输出答案。更新一下mp。 重复这个步骤，直到找到答案。
 
以下是代码：
```cpp
#include <stdio.h>
#define N 100001
#define M 10001

int a[N], head[M] = {0}, next[N];
 
int main() 
{
	int i, n, k, ans, mp, p, tmp;
	
	scanf("%d%d", &n, &k);
	for(i = 1; i <= n; i++) scanf("%d", a + i);
	for(i = n; i; i--){
		next[i] = head[a[i]];
		head[a[i]] = i;
	}
	
	ans = 1, mp = 0;
	while(1){
		tmp = mp;
		for(i = 1; i <= k; i++){
			while(head[i] && head[i] <= mp) head[i] = next[head[i]];
			if(!head[i]){
				printf("%d\n", ans);
				return 0;
			}
			if(head[i] > tmp) tmp = head[i];
		}
		mp = tmp;
		ans++;
	}
    
    return 0;
}
```

---

