# [ABC367C] Enumerate Sequences

## 题目描述

给定长度为 $n$ 的正整数序列 $(r_1, \ldots, r_n)$ 和正整数 $k$。

以字典序从小到大的顺序输出所有满足 $1 \le a_i \le r_i$ 且 $a_1 + \cdots + a_n$ 是 $k$ 的倍数的长度为 $n$ 的整数序列 $(a_1, \ldots, a_n)$。

数据范围：$n \le 8$，$1 \le r_i \le 5$，$2 \le k \le 10$。

## 样例 #1

### 输入

```
3 2
2 1 3```

### 输出

```
1 1 2
2 1 1
2 1 3```

## 样例 #2

### 输入

```
1 2
1```

### 输出

```
```

## 样例 #3

### 输入

```
5 5
2 3 2 3 2```

### 输出

```
1 1 1 1 1
1 2 2 3 2
1 3 1 3 2
1 3 2 2 2
1 3 2 3 1
2 1 2 3 2
2 2 1 3 2
2 2 2 2 2
2 2 2 3 1
2 3 1 2 2
2 3 1 3 1
2 3 2 1 2
2 3 2 2 1```

# 题解

## 作者：OGCoder (赞：9)

# 题目大意

按升序排列打印所有满足以下条件的长度为 $N$ 的整数序列。

- 第 $i$ 个元素介于 $1$ 和 $R_i$ 之间。
- 所有元素之和是 $K$ 的倍数。

## 数据范围
-   $1 \le N \le 8$
-   $2 \le K \le 10$
-   $1 \le R_i \le 5$
# 思路解析
因为题目中的$N$和 $R_i$ 都很小，直接暴力搜索$1$~$N$就好了。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,r[100010],b[1000010];
void dfs(int u,int sum=0){//u表示填第几个数 sum 表示所有数的总和
	if(u==n+1){//所有数都填好了
		if(sum%k!=0) return; //如果所有数的和不是 k 的倍数那么就不输出
		for(int i=1;i<u;i++) cout<<b[i]<<' ';//输出答案
		cout<<endl;
		return;
	}
	for(int i=1;i<=r[u];i++){
		b[u]=i;//记录答案
		dfs(u+1,sum+i);//继续搜下一个
		b[u]=0;//还原
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>r[i];
	dfs(1);//从第一个数开始搜索
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：7)

## 题意

题目中让我们按字典序输出满足第 $i$ 个数在 $R_i$ 中的所有长度为 $N$ 的整数序列，使得这些数的和是 $K$ 的倍数。乍一看，这道题把我这个蒟蒻难倒了，但是一看数据范围，想必大家有了一点清晰的思路。
## 分析思路

看到数据范围很小，$N$ 和 $R$ 的大小都在 10 以内，一定能想到方法了吧？没错，就是使用 DFS 操作进行暴力枚举。具体地说，就是对于每一位都把能填的所有数试一遍，只要答案是 $K$ 的倍数，就直接输出，记得要返回，不然就死循环了。这个方式的正确性是显然的，因为我们第一次达到个数要求的一定就是字典序排在更前面的，代码也非常简单，其实就是一个全排列的变式，还没掌握全排列的同学可以看看[这道题](https://www.luogu.com.cn/problem/P1706)。
## 代码+注释

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,sum;
int r[10],ans[10];
void dfs(int ns){ //ns表示当前到了哪一位 
	if(ns>n){ //到达个数就判断并返回 
		if(sum%k==0){ //符合要求 
			for(int i=1;i<=n;i++)
				cout<<ans[i]<<' ';
			cout<<endl;
		}
		return; //无论符不符合要求都要记得返回哦 
	}
	for(int i=1;i<=r[ns];i++){ //枚举当前这一位可以填的所有书 
		ans[ns]=i; //先记录答案 
		sum+=i; //总和加上当前枚举到的数 
		dfs(ns+1); //搜索下一位 
		sum-=i; //回溯回去才能答案正确 
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>r[i];
	}
	dfs(1); //从第一位开始依次枚举 
	return 0;
}
```

---

## 作者：linch (赞：2)

## 题意
给定 $N$ 个整数 $R_i$，求出长度为 $N$ 的正整数列，满足第 $i(1\le i \le n)$ 个数不超过 $R_i$ 且数列的和是 $K$ 的倍数，按照字典序升序输出。

## 思路
由于此题，$N$ 和 $R_i$ 都比较小，我们可以暴力枚举每一个符合第一条要求的数列，判断其和是否为 $K$ 的倍数。若满足，则直接输出。

由于要求升序输出，我们可以使用 DFS，每一位都从 $1$ 开始选择，直到 $R_i$，$N$ 个数全部选好后判断其和，并回溯。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10;
int n,k,r[maxn],a[maxn];
void dfs(int dep,int sum){//dep 记录当前枚举到第几位，sum 记录和。
	if(dep>n){//已完成枚举。
		if(sum%k==0){
			for(int i=1;i<=n;i++){
				cout<<a[i]<<" ";
			}
			cout<<"\n";//满足条件则输出。
		}
		return;//注意无论是否满足，都需要返回。
	}
	for(int i=1;i<=r[dep];i++){
		a[dep]=i;
		dfs(dep+1,sum+i);
	}//从 1 开始枚举。
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>r[i];
	}//输入。
	dfs(1,0);//暴力枚举。
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/173362545)

---

## 作者：SunSkydp (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/sunskydp/p/18365611/abc367c_solution)  
## 简要题意  
给定 $n,k$ 和 $R_i$，你需要输出所有满足下列条件的整数序列：

- 长度为 $n$。
- 第 $i$ 个元素的范围为 $[1,R_i]$。
- 一个序列的所有元素的总和为 $k$ 的倍数。

输出请按照按照从左至右按位从小到大的顺序输出。

## 题解
注意到数据范围很小，我们可以直接爆搜，这里用的是 dfs，搜索过程中记录和，在数组上做标记，记得回溯清空标记，找到符合题意的方案就输出。

```cpp
#include <bits/stdc++.h>
#define _for(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 10;
int n, k, r[N], a[N];
void dfs(int x, int sum) {
	if(x == n + 1) {
		if(sum % k == 0) {
			_for(i, 1, n) cout << a[i], putchar(' ');
			putchar('\n');
		} return ;
	}
	_for(i, 1, r[x]) {
		a[x] = i;
		dfs(x + 1, sum + i);
		a[x] = 0;
	}
	return ;
}
signed main() {
    cin >> n >> k;
    _for(i, 1, n) cin >> r[i];
    dfs(1, 0);
    //cerr << clock() << "ms\n";
    return 0;
}
```

---

## 作者：zhlzt (赞：1)

### 题解

dfs 暴力搜索，参数设一个 $dep$ 和一个 $sum$ 即可。

时间复杂度为 $O\left(n\prod\limits_{i=1}^n R_i\right)$，但由于有 $k$ 的倍数的限制，根本跑不满。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[15],r[15],n,k;
void dfs(int dep,int sum){
	if(dep>n){
		if(sum%k) return;
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<" ";
		}
		cout<<"\n"; return;
	}
	for(int i=1;i<=r[dep];i++){
		ans[dep]=i; 
		dfs(dep+1,sum+i);
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>r[i];
	dfs(1,0); 
	return 0;
}
```

---

## 作者：under_the_time (赞：1)

## 题意

> 给定长度为 $n$ 的正整数数组 $r$ 和正整数 $k$，输出所有长度为 $n$ 的序列，要求序列中第 $i$ 项值域在 $[1,r_i]$ 中，且满足序列各项之和为 $k$ 的倍数。按照字典序从小到大输出。
>
> - 对于两个序列 $a,b$，$a$ 的字典序小于 $b$ 当且仅当存在一个 $i$ 使得 $a$ 和 $b$ 中 $[1,i-1]$ 的部分相同且 $a_i<b_i$。

## 解法

考虑暴搜加剪枝。搜索过程中从前往后填数，总是优先选择较小的数放入当前位置，这样可以满足后得到的合法解的字典序一定大于先得到的合法解。剪枝方面可以考虑两种情况：**和太小或者和太大**，即：（令当前位置为 $i$，还没有填入；之前的总和为 $sum$）

- 我们求出一个最大不超过 $\sum r_i$ 的 $k$ 的倍数 $K$，若 $sum+(n-i+1)>K$，即后面的所有位全部填 $1$ 答案也太大，则说明当前的和不可能合法，可以剪枝；
- 若 $sum+\sum_{j\in[i,n]}r_j<k$，即后面的所有位全部拉满了填答案也太小，则说明当前的和不可能合法，也可以剪枝。

## 代码

```cpp
// Problem: C - Enumerate Sequences
// Contest: AtCoder - AtCoder Beginner Contest 367
// URL: https://atcoder.jp/contests/abc367/tasks/abc367_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Good luck to the code >w<
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn = 10;
int s[maxn], r[maxn], tmp[maxn], n, K, k;
void dfs(int now, int sum) {
	if (now > n) {
		if (sum % k == 0)
			for (int i = 1; i <= n; i ++)
				printf("%d%c", tmp[i], "\n "[i < n]); // 这里将字符串视为数组即可理解。
		return ;
	}
	if (sum + n - now + 1 > K) return ; // 剪枝1
	if (sum + s[n] - s[now - 1] < k) return ; // 剪枝2
	for (int i = 1; i <= r[now]; i ++) // 从小往大枚举填入
		dfs(now + 1, sum + (tmp[now] = i));
}
int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &r[i]), s[i] = s[i - 1] + r[i];
	for (K = 0; K + k <= s[n]; K += k); // 算出 K
	dfs(1, 0);
	return 0;
}
```

- 其实上述剪枝优化的并不多，~~或许不剪枝也能过？~~

评测记录：https://www.luogu.com.cn/record/173356152

---

## 作者：JXR_Kalcium (赞：1)

## 题目大意

要按照字典序从小到大依次输出一个长度为 $N$ 的满足条件的序列 $A$，当且仅当对于每个 $1\le i\le N$ 都有 $1\le A_i\le R_i$ 且 $\sum_{i=1}^{N} A_i\bmod K=0$ 时 $A$ 满足条件。

## 解题思路

首先看到 $N\le 8$ 就知道这一题肯定是**搜索**，我们可以先枚举满足 “对于每个 $1\le i\le N$ 都有 $1\le A_i\le R_i$” 这个条件的全排列，顺便记录一下每个数的和，最后检查和是否是 $K$ 的倍数，如果是的话输出即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl;
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,k,r[11],a[11];

void dfs(ll x, ll y)
{
    if(x==n+1)
    {
        if(!(y%k))
        {
            for(int i=1; i<=n; ++i)
            write(a[i]), spc; endl;
        }

        return;
    }

    for(int i=1; i<=r[x]; ++i)
    {
        a[x]=i; dfs(x+1,y+i);
        a[x]=0;
    }
}

int main()
{
    n=read(); k=read();
    for(int i=1; i<=n; ++i) r[i]=read();
    dfs(1,0);
    return 0;
}
```

---

## 作者：Happy_mouse (赞：0)

# [Enumerate Sequences](https://www.luogu.com.cn/problem/AT_abc367_c) 题解
[AC证明](https://www.luogu.com.cn/record/173357877)
## 题目大意
求满足下面要求的整数序列。

- 第 $i$ 个元素介于 $1$ 和 $R_i$ 之间（含）。
- 所有元素之和是 $K$ 的倍数。
## 分析与解答
这个数据范围……
-   $1 \le N \le 8$
-   $2 \le K \le 10$
-   $1 \le R_i \le 5$

反手再看看题目。嗯，直接爆搜！

DFS 模板题。对每个位置 $i$ 从 $1$ 到 $R_i$ 统统遍历并进行递归。

Nice!

每层递归复杂度 $O(R_i)$，输出的复杂度 $O(N)$，总时间复杂度 $O(N\times \prod_{i=1}^N R_i)$，大概 $4\times 10^6$，毫无压力。

## 代码
话不多说，上代码。

大家应该都看得懂，代码中就不打注释了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[10],n,m,now[10],cnt;
void dfs(int step){
	if(step>n&&cnt%m==0){
		for(int i=1;i<=n;i++) cout<<now[i]<<' ';
		cout<<'\n';
		return ;
	}
	for(int i=1;i<=a[step];i++){
		now[step]=i;
		cnt+=i;
		dfs(step+1);
		cnt-=i;
		now[step]=0;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs(1);
	return 0;
}
```

---

## 作者：lcy0506 (赞：0)

# 题解：AT_abc367_c [ABC367C] Enumerate Sequences

这道题数据这么小，再仔细看一下题面，很容易发现这是一道 dfs 较为简单的题目。

题目中说要按照字典序排列，这个只要我们枚举时按从小到大，就无需考虑这个问题，等搜完 $n$ 个数后，看是否是 $m$ 的倍数，如果是，打印出来，否则继续搜。

## 代码如下

```
#include <bits/stdc++.h>
using namespace std;
int a[100001],n,m,flag[1000001];//flag[i]指第i位的数
void dfs(int now,int sum)//now指当前搜到第几位，sum指累加和
{
	for(int i=1;i<=a[now];i++)//从小到大枚举
	{
		if(now==n)//已经搜到n
		{
			if((sum+i)%m==0)//判断是否为m的倍数
			{
				for(int j=1;j<=n-1;j++)//打印
				{
					printf("%d ",flag[j]);
				}
				printf("%d\n",i);//最后一个单独打印
			}
			continue;
		}
		else
		{
			flag[now]=i;//做标记
			dfs(now+1,sum+i);//继续搜
			flag[now]=0;
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	dfs(1,0);
}
```

---

## 作者：Redamancy_Lydic (赞：0)

## 大致题意

让你按照字典序输出一些长 $n$ 的序列，序列中的数字有范围，且序列和需要为 $k$。

## 分析

直接深搜。搜索的时候对从第一个元素开始，每个元素从小到大枚举所有可能的值，这样就保证答案按照字典序升序排列。

用一个 `vector` 存储序列，到达边界之后计算一遍和，判断是否满足条件，然后直接输出 `vector` 中的元素即可。

按照题目的数据范围完全可以过。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int maxn=1e6+10;
const int mod=1e9+7;
int n,k;
int a[maxn];
void dfs(int x,vector<int> ans)
{
	if(x>n)
	{
		int sum=0;
		for(auto i : ans)sum+=i;
		if(sum%k)return ;
		for(auto i : ans)cout<<i<<' ';
		cout<<'\n';
		return ;
	}
	for(int i=1;i<=a[x];i++)
	{
		ans.push_back(i);
		dfs(x+1,ans);
		ans.pop_back();
	}
}
signed main()
{
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	vector<int> v;
	dfs(1,v);
	return 0;
}

```

---

## 作者：D0000 (赞：0)

考虑到 $n$ 和 $r_i$ 都较小，直接枚举所有序列，一个较为直观的方法就是 dfs，由于最后按字典序输出，而 dfs 遍历序列的顺序恰好就是字典序，所以只需要判断一下是不是 $k$ 的倍数输出就行了。时间复杂度 $n\times r^n$ 其中 $r=\max\{r_i\}$。事实上，这就是本题最好的方法，因为不是求有多少种方案，而是把所有合法方案输出，当 $k=1$ 时，就有 $r^n$ 种合法方案。

---

## 作者：HeYilin (赞：0)

### 题意

给定两个正整数 $n$、$k$ 和一个长为 $n$ 的序列 $R$ ，要求你构造出所有可行的序列 $A$ ，使其满足： $1 \leq A_i \leq R_i$，$\forall i \in [1,n]$ ，且 $k | \sum_{i=1}^n a_i$ 。按照字典序输出所有可行序列。

### 做法

爆搜解决一切！

用 `dfs(now,x,sum,ans[])` 表示搜索状态，四个参数分别表示当前搜到了第 $now$ 个位置，当前位置上填充的数是 $x$ ，总和是 $sum$ ，以及填充到的数组 $ans[]$ 。

对于每个位置我们从 $1$ 到 $R_i$ 枚举填充的数，每次层数到达 $n$ 后表示当前序列已填充完成，判断一下总和是否能被 $k$ 整除。如果可以就输出。

由于我们枚举的顺序是从小到大的，所以可以保证求出的顺序一定是字典序。

### 代码

```cpp
#include<bits/stdc++.h>
typedef long long int ll;
using namespace std;
const int maxn=15;
int n,k,limit[maxn];
int ans[maxn];
void dfs(int now,int x,int sum,int ans[]){
//	for(int i=1;i<=n;i++)cout<<"---> "<<ans[i]<<" ";
//	cout<<"\n sum : "<<sum<<"\n";
	if(now==n){
		if(sum%k==0){
			for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
			cout<<"\n";
		}
		
		return;
	}
	for(int i=1;i<=limit[now+1];i++){
		ans[now+1]=i;
		dfs(now+1,i,sum+i,ans);
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>limit[i];
	for(int i=1;i<=limit[1];i++){
		ans[1]=i;
		dfs(1,i,i,ans);
	}
	return 0;
}
```

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路

  初看好像是什么递推，但是看一眼数据范围，全都是小于 $10$ 的，直接考虑深搜，搜每个位上放什么数字，搜完判断是否合法，合法再输出，从 $1$ 到 $N$ 搜，数字从小到大搜，可保证字典序升序，时间复杂度可过。

- ### 具体实现

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,k,r[10];
  int ans[10];
  void dfs(int x,int sum)
  {
  	if(x>n)
  	{
  		if(sum%k!=0) return;
  		for(int i=1;i<=n;i++)
  		{
  			printf("%d ",ans[i]);
  		}
  		printf("\n");
  		return;
  	}
  	for(int i=1;i<=r[x];i++)
  	{
  		ans[x]=i;
  		dfs(x+1,sum+i);
  	}
  }
  int main()
  {
  	scanf("%d%d",&n,&k);
  	for(int i=1;i<=n;i++) scanf("%d",&r[i]);
  	dfs(1,0);
  }
  ```

---

## 作者：__O_v_O__ (赞：0)

我们发现，$n\le 10,r_i\le 5$，所以这题一定是搜索。

我们通过搜索，枚举数列中每个数的取值。确定了数列后，再判断它的和是否为 $k$ 的倍数，是则输出即可。

但是题目中还有一个要求：输出的数列字典序从小到大。其实，这个问题不需要考虑，因为我们在搜索时，本来就是从小到大枚举的每个数，字典序一定满足要求。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,r[10001],a[10001];
void dfs(int x){
	if(x==n+1){
		int su=0;
		for(int i=1;i<=n;i++)su+=a[i];
		if(su%k==0){
			for(int i=1;i<=n;i++)cout<<a[i]<<' ';
			cout<<'\n';
		}
		return;
	}
	for(int i=1;i<=r[x];i++){
		a[x]=i,dfs(x+1),a[x]=0;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>r[i];
	dfs(1);
	return 0;
}
```

---

## 作者：donnieguo (赞：0)

## 题意简述

给定 $N$ 和 $K$，以及 $N$ 个整数 $R_1,R_2,\ldots R_n$，要求按字典序输出满足以下要求的序列 $a$：

- $\forall i\in [1, n],a_i\leq R_i$

- $\large\sum\limits_{i=1}^n \normalsize a_i \bmod K=0$

$1\leq N \leq 8$，$2\leq K \leq 10$，$1\leq R_i\leq 5$。

## 思路

看到这个数据范围就知道要用 dfs 了。

枚举到第 $i$ 个数的时候，上界为 $R_i$，最后加总判断一下是否为 $K$ 的倍数即可。

## AC code

```cpp
#include <iostream>
using namespace std;

int n, k;
int r[10], a[10];

void dfs(int pos)
{
	if (pos == n + 1)
	{
		int sum = 0;
		for (int i = 1; i <= n; i++) sum += a[i];
		if (sum % k == 0) {
			for (int i = 1; i <= n; i++) cout << a[i] << ' ';
			cout << '\n';			
		}
		return;
	}
	for (int i = 1; i <= r[pos]; i++)
	{
		a[pos] = i;
		dfs(pos + 1);
	}
}

int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> r[i];
	dfs(1);
	return 0;
}
```

---

## 作者：xiaoke2021 (赞：0)

一眼丁真鉴定为：深搜。

---

题目要我们做些什么呢？其实就是给你 $n,k$ 和一个长度为 $n$ 的数组 $r$，输出所有长度为 $n$ 的序列 $a$，满足对于所有的整数 $1 \le i \le n$，都有 $a_i \le r_i$，且序列 $a$ 所有元素之和为 $k$ 的非负整数倍。按字典序输出。

发现数据很小，可以直接暴力，枚举每一种情况，统计合法答案即可。

由于深搜是按顺序枚举的，所以不用考虑字典序的问题。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int r[10+5];
int ans[10+5];
void dfs(int step){ // 处理到了答案的哪一位
//	cout<<step<<endl;
	if(step>n){
		int sum=0;
		for(int i=1;i<=n;i++) sum+=ans[i];
		if(sum%k==0){
			for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
			puts("");
		}
		return ;
	}for(int i=1;i<=r[step];i++){ //从 1 开始枚举，所以自然是按字典序枚举的
		ans[step]=i;
		dfs(step+1);
		ans[step]=0;
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>r[i];
	dfs(1);
	return 0;
}
```

---

## 作者：lcfollower (赞：0)

观察到数据范围很小，$1\le N\le 8$，$1\le R_i\le 5$，所以考虑 dfs。

每次搜索 $[1,R_i]$ 之间的数，然后搜索即可。

时间复杂度为 $\mathcal O(R_i^N)$，能在时限内通过。

[代码](https://atcoder.jp/contests/abc367/submissions/56785084)。

---

## 作者：Breath_of_the_Wild (赞：0)

题意：给定 $n,k,\{a_n\}$，请求出若干个 $\{b_n\}$ 使得这些 $\{b_n\}$ 按照字典序排列，$1\le b_i\le a_i$，且它们的和为 $k$ 的倍数。

注意到 $n\le 8$ 且 $a_i\le 5$，爆搜完全可以通过本题，于是可以对于每一位 $i$，枚举填的数（$1$ 至 $a_i$），最后判断是否满足和为 $k$ 倍数即可。

对于字典序的问题，不需要特殊处理，因为 DFS 的输出顺序正好就满足字典序的要求。
```cpp
void DFS(int x){
	if(x==n+1){
		int ans=0;
		for(int i=1;i<=n;i++) ans+=box[i];
		if(ans%k==0){
			for(int i=1;i<=n;i++)cout<<box[i]<<" ";
			cout<<'\n';
		}
		return;
	}
	for(int i=1;i<=a[x];i++){
		box[x]=i;
		DFS(x+1);
		box[x]=0;
	}
}
```

---

## 作者：xuduang (赞：0)

### 题意

你需要构造一个长为 $n$ 的序列 $A$，使得 $1 \le A_i \le R_i$，且 $\displaystyle\sum_{i=1}^{n}A_i$ 能被 $k$ 整除，输出所有的方案。

### 分析

看到 $n \le 8$ 和输出所有方案，自然的考虑爆搜。

记 `dfs(u,sum)` 表示当前到了第 $u$ 项，当前的和为 $sum$。当 $u=n+1$ 时判断 $sum$ 是否整除 $k$ 即可。

代码不难实现，细节很少。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int n, k;
int r[N];
int a[N];//当前的数组
void dfs(int u, int sum)
{
    if(u == n + 1 && sum % k == 0)//满足条件了
    {
        for(int i = 1; i <= n; i++) cout << a[i] << " ";
        puts("");
        return ;
    }
    for(int i = 1; i <= r[u]; i++) a[u] = i, dfs(u + 1, sum + i);
    //爆搜
}
signed main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> r[i];
    dfs(1, 0);
    return 0;
}
```

---

## 作者：Your_Name (赞：0)

## 题意
按字典序输出所有满足以下条件的序列 $A$。
* 长度为 $n$
* $A_i\in[1,R_i]$
* $K \mid S_A$ (所有元素之和是 $K$ 的倍数)
## 思路
因为 $R_i \le 5$ 且 $n\le 8$，所以可以暴力枚举每个数是多少，然后最后判断和是否满足条件即可。

注意枚举时从小到大，这样一定可以保证输出顺序为字典序。因为在上一位相同的情况下，当前位更小的（即字典序更小的）一定先被枚举。

复杂度为 $O(\prod_{i = 1}^{n} R_i)$，最大为 $5^8$，能过。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, r[11], res[11], sum;
void dfs(int k){
    if(k == n + 1){//枚举完了
        if(sum % m)return;//判断合法
        for(int i = 1; i <= n;i++){
            cout << res[i] <<' ';
        }
        cout << endl;//输出
        return ;
    }
    for(int i = 1; i <= r[k]; i++){
        sum += i;//累计选出来的和
        res[k] = i;//加入答案
        dfs(k + 1);//继续选下一个
        sum -= i;//回溯
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> r[i];
    }
    dfs(1);
    return 0;
}
```
 _完结撒花。_

---

## 作者：liruixiong0101 (赞：0)

# C - Enumerate Sequences
## 题意：
给定 $n,k$（$1\le n\le 8, 2\le k\le 10$） 和一个长度为 $n$ 的数组 $r_i$（$1\le r_i\le 5$），请你按照字典序从小到大输出满足以下条件的序列：
- 序列长度为 $n$。
- 序列中的每一个元素 $a_i$，都要满足 $a_i\le r_i$。
- 序列中数的总和是 $k$ 的倍数。

## 思路：
观察到 $n$ 和 $r_i$ 都很小，考虑爆搜，枚举每一个元素该选什么，累加总和，如果元素大小是从 $1$ 枚举到 $r_i$，那么直接输出序列，字典序一定从小到大。

## 代码：
<https://atcoder.jp/contests/abc367/submissions/56788422>

---

## 作者：wang_freedom (赞：0)

### 思路：
观察到 $r$ 很小，所以考虑枚举，计算当前 $A$ 数组的和，如果是 $k$ 的倍数就输出。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define rop(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'
using namespace std;
int n,k,r[10],res=1,a[10],sum,now; 
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	rep(i,1,n){
		cin>>r[i];
		res*=r[i];
		a[i]=1;
	}
	if(n%k==0){
		rep(i,1,n)
			cout<<a[i]<<' ';
		cout<<endl;
	}
	rop(i,1,res){
		sum=0;
		a[n]++;
		now=n;
		while(a[now]>r[now]){
			a[now]=1;
			a[--now]++;
		}
		rep(j,1,n)
			sum+=a[j];
		if(sum%k==0){
			rep(j,1,n)
				cout<<a[j]<<' ';
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

## 题目思路：
搜索题，暴力搜索即可。从 $1 \sim R_i$ 枚举每个空，用 $num$ 求和判断，用 $a$ 数组存答案即可。
## CODE:

```cpp
#include <iostream>
using namespace std;
int n, k, r[9], a[9];
void print()
{
  for (int i = 1; i <= n; i++)
    cout << a[i] << ' ';
  puts("");
}
void dfs(int x, int num)
{
  if (x > n)
  {
    if (num % k == 0) print();
    return;
  }
  for (int i = 1; i <= r[x]; i++)
  {
    a[x] = i;
    dfs(x + 1, num + i);
    a[x] = 0;//可无
  }
}
int main()
{
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> r[i];
  dfs(1, 0);
  return 0;
}
```

---

## 作者：EricWan (赞：0)

暴力 DFS，如果每一个位置都填充完了，就判断是否合法，之后输出。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, p[100], a[100];
void dfs(int id, int s) {
	if (id > n) {
		if (s == 0) {
			for (int i = 1; i <= n; i++) {
				cout << a[i] << " ";
			}
			cout << endl;
		}
		return;
	}
	for (int i = 1; i <= p[id]; i++) {
		a[id] = i;
		dfs(id + 1, (s + i) % k);
	}
}
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	dfs(1, 0);
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

既然 $n$ 很小，考虑暴力搜索。

参数记录当前选择第几个数，以及和对 $k$ 取余的值，最后判断每种情况的和是否为 $0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=11;
int n,k,a[N],b[N];
void output(){
    for(int i=1;i<=n;i++)
        cout<<b[i]<<" \n"[i==n];
    return;
}
void dfs(int step,int sum){
    if(step>n){
        if(!sum)
            output();
        return;
    }
    for(int i=1;i<=a[step];i++){
        b[step]=i;
        dfs(step+1,(sum+i)%k);
    }
    return;
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    dfs(1,0);
    return 0;
}
```

---

