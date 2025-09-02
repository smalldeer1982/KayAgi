# [ABC397C] Variety Split Easy

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc397/tasks/abc397_c

> 本题是 F 题的简易版本。

给定一个长度为 $N$ 的整数列 $A=(A_1, A_2, \ldots, A_N)$。

当在 $A$ 的某一位置将其分割为 $2$ 个非空的连续子序列时，求这两个子序列中不同整数的种类数之和的最大可能值。

更严格地说，对于满足 $1 \leq i \leq N-1$ 的整数 $i$，分别计算子序列 $(A_1, A_2, \ldots, A_i)$ 和 $(A_{i+1}, A_{i+2}, \ldots, A_N)$ 中不同整数的种类数之和，并求这些和的最大值。

## 说明/提示

### 约束条件

- $2 \leq N \leq 3 \times 10^5$
- $1 \leq A_i \leq N$ ($1 \leq i \leq N$)
- 输入均为整数

### 样例解释 1

- 当 $i=1$ 时，子序列 $(3)$ 和 $(1,4,1,5)$ 各自包含的整数种类数分别为 $1$ 和 $3$，和为 $4$。
- 当 $i=2$ 时，子序列 $(3,1)$ 和 $(4,1,5)$ 各自包含的整数种类数分别为 $2$ 和 $3$，和为 $5$。
- 当 $i=3$ 时，子序列 $(3,1,4)$ 和 $(1,5)$ 各自包含的整数种类数分别为 $3$ 和 $2$，和为 $5$。
- 当 $i=4$ 时，子序列 $(3,1,4,1)$ 和 $(5)$ 各自包含的整数种类数分别为 $3$ 和 $1$，和为 $4$。

因此，当 $i=2$ 或 $i=3$ 时，取到最大值 $5$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 1 4 1 5```

### 输出

```
5```

## 样例 #2

### 输入

```
10
2 5 6 5 2 1 7 9 7 2```

### 输出

```
8```

# 题解

## 作者：CSP_SAKME (赞：5)

# 题目大意

给你一个长度为 $N$ 的整数序列：$A = (A_1, A_2, \ldots, A_N)$。

当把一个位置上的 $A$ 分割成两个非空（连续）子数组时，求这两个子数组中不同整数个数之和的最大值。

更具体地说，求整数 $i$ 在 $1 \leq i \leq N-1$ 中的以下两个值的最大和：$(A_1, A_2, \ldots, A_i)$ 中的不同整数计数，以及 $(A_{i+1}, A_{i+2}, \ldots, A_N)$ 中的不同整数计数。

# 题目思路

如果直接枚举分割点，那么肯定爆炸，所以考虑其他方法。

我们需要抓住不变的量，例如现在 $i=2$，下一个分割点是 $3$。

那么不变量是什么？

显然是第一个子数组的 $A_1, A_2$，第二个子数组的 $A_4, A_5$。

$A_3$ 从第二个子数组移到第一个子数组，很明显只要改这一个数。

这里再搞两个优化用的数组，用来存储数的出现次数。

如果第一次出现就加一，如果是最后一个就减一。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300001],b[300001],n,k[300001],ansa,ansb,maxn;
int main(){
	cin >> n;
	for(int i=1;i<=n;i++) cin >> k[i];
	a[k[1]]++;
	ansa=1;
	for(int i=2;i<=n;i++){
		b[k[i]]++;
		if(b[k[i]]==1) ansb++;
	}
  //前面预处理出i=1的情况，其实不处理也行
	maxn=ansa+ansb;
	for(int i=2;i<n;i++){
		a[k[i]]++;
		if(a[k[i]]==1) ansa++;//a数组加一个数
		b[k[i]]--;
		if(b[k[i]]==0) ansb--;//b数组减一个数
		maxn=max(ansa+ansb,maxn);
	}
	cout << maxn;
	return 0;
}
```

---

## 作者：JCT_addyi (赞：2)

### 题意：
给你 $n$ 个数，把它分成两段，求每段不同数字的和，问怎么分和最大，最大值为多少。

### 思路：
开两个数组，一个从前往后搜，一个从后往前搜，再来一个标记数组看这个数重复没有，最后求两个数组相对应的数的和的最大值就行了。

就相当于是暴力，但暴力是分成了两段是双层循环，这个也是分两段，只有一层循环。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+6;
int n,ans,a[N],x[N],y[N];
bool k[N];//标记数组 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		x[i]=x[i-1];//求不同数的个数 
		if(k[a[i]]==0) x[i]++,k[a[i]]=1;//是第一次标记没重复 
	}
	for(int i=1;i<=n;i++) k[i]=0;//清空 
	for(int i=n;i>=1;i--){
		y[i]=y[i+1];//倒着求 
		if(k[a[i]]==0) y[i]++,k[a[i]]=1;//标记 
	}
	for(int i=1;i<n;i++) ans=max(yly,x[i]+y[i+1]);//求每个搭配的最大值 
    return 0;
}

```

谢谢大家！

---

## 作者：KobeBeanBryantCox (赞：1)

# AT_abc397_c [ABC397C] Variety Split Easy 题解

---------------

[题目传送门](https://www.luogu.com.cn/problem/AT_abc397_c)。

---------------

## 题意

给一个序列 $A$，把 $A$ 分成两个部分，求每一个部分的不同数字的个数和最大。

---------------

## 思路

看到不同数字，直接使用 set 去重即可。

所以维护两个 set，第一个空的，第二个刚开始满的。

考虑顺便在第二个 set 记每个数字出现次数。

然后从左往右扫，每次把当前的加入第一个 set，在第二个 set 中删除（删除时要判断出现次数是否是 $1$ 再删，否则不能删）。

然后每一次扫记一次答案，求最大即可。

时间复杂度 $O(n\log n)$。

不使用 set，用类似[合唱队形](https://www.luogu.com.cn/problem/P1091)的 trick 能做到 $O(n)$，具体的看[官解](https://atcoder.jp/contests/abc397/editorial/12466)。

----------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
int in()
{
	int k=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=3e5+10;
int f[N],a[N];
set<int>aa,bb;
int main()
{
	int n=in();
	for(int i=1;i<=n;i++)a[i]=in(),bb.insert(a[i]),f[a[i]]++;
	int maxx=0;
	for(int i=1;i<n;i++)
	{
		aa.insert(a[i]);
		if(f[a[i]]==1)bb.erase(bb.find(a[i]));
		f[a[i]]--;
		maxx=max(maxx,(int)(aa.size()+bb.size()));
	}
	out(maxx);
	return 0;
}
```

---------------

## 后记

若不清楚或错误，欢迎评论或私信。

---

## 作者：Bai_R_X (赞：1)

## 思路
类似一个滑动窗口。

我们枚举每个分割点，用 `map` 维护每个点出现的次数（为 $0$ 时删除，不过我用的变量维护的大小）即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,i,a[300005],maxn,cnt;
map<int,int> mp1,mp2;
signed main()
{
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	mp1[a[1]]++;
	for(i=2;i<=n;i++)mp2[a[i]]++;
	maxn=mp2.size()+1;
	cnt=mp2.size();
	for(i=2;i<=n;i++)
	{
		mp2[a[i]]--;
		if(mp2[a[i]]==0)cnt--;
		mp1[a[i]]++;
		if(mp1.size()+cnt>maxn)maxn=mp1.size()+cnt;
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：boluo2014 (赞：1)

哎呀，一道非常水的题目。

### 思路

首先，看一下数据，一看就不能用暴力，否则会开心地 TLE。

为了后面叙述的方便，我们定义在 $i$ 处截断表示在 $a_i$ 后面截断。

但是，我们发现在 $i$ 处截断和在第 $i+1$ 处截断，它们的差距很少。具体少在哪里呢？如果已经知道了在 $i$ 处截断，那么在前面一段的数中 $a_{i+1}$ 多了 $1$ 个。而在后面的那一段中，$a_{i+1}$ 减少了 $1$ 个。而 $a_{i+1}$ 我们是知道的，故可以迅速求出并操作。

### 实现

所以，我们只需要维护两个计数器数组，不停地维护它们的变化。初始，答案的值就是里面不同数的个数。变化后有以下情况：

- 前面一段多了一个以后，那一个的数量为 $1$，说明是新增的，答案 $+1$。
- 后面一段少了一个以后，那一个的数量为 $0$，说明去掉以后就没有了，答案 $-1$。

我们在每次操作以后，都取更大的答案，最终输出便是。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n,a[maxn],c1[maxn],c2[maxn];
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	int i,ans=0,mx=0;
	for(i=1;i<=n;i++){
		cin>>a[i];
		c2[a[i]]++;
	}
	for(i=1;i<=n;i++){
		if(c2[i]){
			ans++;//初始的个数 
		}
	}
	for(i=1;i<=n;i++){
		c1[a[i]]++;
		c2[a[i]]--;
		if(c2[a[i]]==0){//后面的少成0了 
			ans--;
		}
		if(c1[a[i]]==1){//前面的多了一个新的 
			ans++;
		}
		mx=max(mx,ans);//每次取最大 
	}
	cout<<mx<<endl;
	return 0;
}
```
注：提交后有可能会 UKE，建议直接在 ATCODER 提交。

你会了吗？

---

## 作者：Ray_yi (赞：1)

### 思路：

题目要求的是使贡献最大的切分点 $i$。数据范围是不允许暴力的，肯定会超时，那怎么办呢？

我们很容易可以想到先预处理出对于每个位置他的前面有多少重复的，与后面有多少重复的。也就是预处理出前缀和后缀，然后枚举 $i$，计算出结果再求最大值。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxi=-1,t[300005],a[300005];
int l[300005],r[300005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		l[i]+=l[i-1];
		if(t[a[i]]==1) l[i]++;
		t[a[i]]=1;
	}
	for(int i=1;i<=n;i++) t[i]=0;
	for(int i=n;i>=1;i--){
		r[i]+=r[i+1];
		if(t[a[i]]==1) r[i]++;
		t[a[i]]=1;
	}
	for(int i=1;i<=n;i++){
		int ans=0;
		ans+=i-l[i]+(n-i-r[i+1]);
		maxi=max(maxi,ans);
	}
	cout<<maxi;
	return 0;
}
```

---

## 作者：xyx404 (赞：1)

## 题意：
将数组分割成两个非空连续子数组，使得两个子数组中不同元素的数量之和最大。

## 思路：

定义数组 $pre$，其中 $pre_i$ 表示前 $i$ 个元素中不同元素的数量。  
定义数组 $suf$，其中 $suf_i$ 表示从位置 $i$ 到末尾的不同元素数量。

将两个数字预处理完成后，对于所有满足 $1 \le i < n$ 的 $pre_i+suf_{i+1}$ 中取最大值就是答案。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
const int N=3e5+5;
int n,a[N],pre[N],suf[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	unordered_set<int>spre;
	pre[0]=0;
	for(int i=1;i<=n;i++){
		spre.insert(a[i]);
		pre[i]=spre.size();
	}
	unordered_set<int>ssuf;
	suf[n+1]=0;
	for(int i=n;i>=1;i--){
		ssuf.insert(a[i]);
		suf[i]=ssuf.size();
	}
	int maxx=0;
	for(int i=1;i<n;i++){
		maxx=max(maxx,pre[i]+suf[i+1]);
	}
	cout<<maxx;
	
	return 0;
}

```
[提交记录](https://atcoder.jp/contests/abc397/submissions/63852658)。

---

## 作者：wrh316 (赞：1)

### 思路

首先，使用前缀数组记录从 $a _{1}$ 到 $a _{i}$ 的不同整数个数，再使用后缀数组记录从 $a _{i}$ 到 $a _{n}$ 的不同整数个数。

然后，使用哈希集合来统计不同整数的个数。从左到右遍历数组，统计前缀的不同整数个数。从右到左遍历数组，统计后缀的不同整数个数。

最后对于每个分割点 $i$，计算最大值。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[300005];
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	vector<int> pre(n), sum(n);
	unordered_set<int> spre, ssum;
	for (int i = 0; i < n; i++) {
		spre.insert(a[i]);
		pre[i] = spre.size();
	}
	for (int i = n - 1; i >= 0; i--) {
		ssum.insert(a[i]);
		sum[i] = ssum.size();
	}
	int ans = 0;
	for (int i = 0; i < n - 1; i++) ans = max(ans, pre[i] + sum[i + 1]);
	cout << ans;
	return 0;
}
```

---

## 作者：Tjaweiof (赞：0)

# AT_abc397_c 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc397_c)

赛时为了之后方便写 F，使用了树状数组求区间不同数字个数，结果最后调 D 调到没写 F。

树状数组求区间不同数字个数的方法见 [P1972](https://www.luogu.com.cn/problem/P1972)。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n, a[3000001], c[3000001], last[3000001], ans[3000001], res;
int lowbit(int x){
	return x & -x;
}
void change(int x, int v){
	while (x <= n){
		c[x] += v;
		x += lowbit(x);
	}
	return;
}
int query(int x){
	int res = 0;
	while (x){
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		if (last[a[i]]){
			change(last[a[i]], -1);
		}
		change(i, 1);
		last[a[i]] = i;
		ans[i] += query(i);
	}
	for (int i = 1; i <= n; i++){
		ans[i] += query(n) - query(i);
		res = max(res, ans[i]);
	}
	cout << res;
	return 0;
}
```

---

## 作者：da_ke (赞：0)

宏观的思考这道题的思路：

设 $(A_1,A_2,\dots,A_i),(A_{i+1},A_{i+2},\dots,A_{N})$。

设左半部分的数 $x$ 的出现次数 $C_{1,x},$，右半部分的数 $x$ 的出现次数 $C_{2,x}$。

初始的，所有数都被划分为右半部分，即 $i=0$。依照 $i=0$ 的标准，初始化 $C_{1},C_{2}$。

将 $i$ 从 $1$ 枚举到 $N-1$：

- 考虑 $C_1,C_2$ 的转移方式：
  - 从 $C_2$ 中剔除 $A_i$，在 $C_1$ 中加入 $A_i$。
  - 具体的，$C_{2,A_i}\leftarrow C_{2,A_i}-1,C_{1,A_i}\leftarrow C_{1,A_i}+1$
- 考虑答案的统计方式：
  - 如果转移完毕 $C_{1,A_i}=1$ 证明左半部分之前没有过 $A_i$，左半部分不同数的个数加 $1$。
  - 同理完成右半部分转移，请读者自己思考！

代码：<https://atcoder.jp/contests/abc397/submissions/63791860>

```cpp
int main()
{
    int N;
    cin>>N;
    vector<int> A(N+2);
    vector<int> cnt1(N+2,0),cnt2(N+2,0);
    int ans=0,ans1=0,ans2=0;
    rep(i,1,N) 
    {
        cin>>A[i],cnt2[A[i]]++;
        if(cnt2[A[i]]==1) ans2++;
    }
    rep(i,1,N-1) // 逐步将每个数从 cnt2 中删除
    {
        cnt2[A[i]]--;
        if(cnt2[A[i]]==0) ans2--;
        cnt1[A[i]]++; if(cnt1[A[i]]==1) ans1++;
        ans=max(ans,ans1+ans2);
    }
    cout<<ans<<endl;
}

// 路虽远行则将至，事虽难做则必成。
```

終。

---

## 作者：Hacker_Cracker (赞：0)

## [ABC397C] Variety Split Easy 题解
### Solution
简单题。

由于子序列是连续的，所以我们从 $1$ 到 $N$ 枚举一遍即可。开两个 map，分别维护 $i$ 左边的子序列不同元素的个数和右边的。每次只需要比较两个 map 的大小的加和与当前答案的最大值即可。

### [AC Code](https://atcoder.jp/contests/abc397/submissions/63862641)
```cpp
#include<iostream>
#include<map>
using namespace std;
const int N=3e5+10;
map<int,int>lt,rt;
int a[N],n,ans=-1e9;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],rt[a[i]]++;
	for(int i=1;i<=n;i++){
		lt[a[i]]++;
		rt[a[i]]--;
		if(!rt[a[i]]) rt.erase(a[i]);
		ans=max(ans,(int)lt.size()+(int)rt.size());
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：Tairitempest (赞：0)

## [ABC397C] Variety Split Easy

开两个桶，获得从 $1$ 到 $N$ 的左侧不重复数字数量前缀，和从 $N$ 到 $1$ 的右侧不重复数字数量后缀。

统计时把对应的前后缀拼接起来即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a[300010],l[300010],r[300010];
ll t1[300010],t2[300010],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		l[i]=l[i-1];
		if(t1[a[i]]==0) l[i]++;
		t1[a[i]]++;
	}
	for(int i=n;i>=1;i--){
		r[i]=r[i+1];
		if(t2[a[i]]==0) r[i]++;
		t2[a[i]]++;
	}
	for(int i=1;i<n;i++){
		ans=max(ans,l[i]+r[i+1]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：MergeSort (赞：0)

## 更新记录

$\texttt{upd.2025.3.20}$ 修改了一些表述。

## 快速访问

[传送门（查看题目）](https://www.luogu.com.cn/problem/AT_abc397_c)

[查看其它题解](https://www.luogu.com.cn/problem/solution/AT_abc397_c)

## 题目大意

给定整数 $n \in \left[1,3\times 10^5\right]$ 和整数数列 $a(|a|=n)$，你需要求出 $\displaystyle \max_{i=1}^{n-1} \left(\left|\bigcup_{j=1}^{i} a_j \right| + \left|\bigcup_{j=i+1}^{n} a_j \right|\right)$。

## 思路分析

如果枚举分割点，暴力去重计算，把计算的结果取最大值输出，速度会很慢；而如果开两个数组，第一个数组的第 $i$ 项表示原数组 $a$ 前 $i$ 项去重后有多少个数，第二个数组第 $j$ 项表示 $a_j \sim a_n$ 去重后有多少个数，中途用 `map` 顺着计算，速度会快很多。题目保证 $a$ 的每一项都在 $1\sim n$ 之间，所以 `map` 其实可以改成更快的“布尔”数组（本题没卡 `unordered_map`）。知道了这些，题目也就切掉了。

## 参考程序（AC 于 atcoder，非完整程序）

```
//语言：C++ 20。
//开头省略一些代码。
//N 表示 max n。
int a[N],lnum[N],rnum[N],lset[N],rset[N];//用 int 代替 bool，可能会加快速度。 
int n,ans,lsize,rsize;
int main()
{
	//这三行代码是用于加速输入输出的。
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (int i = 1;i <= n;i++)
		cin >> a[i];
	for (int i = 1;i <= n;i++)
	{
		if (!lset[a[i]])//如果不在“集合”中，放入集合要把大小加一。
			lsize++,lset[a[i]] = 1;
		lnum[i] = lsize;//按照预处理数组的定义更新。
	}
	for (int i = n;i;i--)
	{
		if (!rset[a[i]])//同上。 
			rsize++,rset[a[i]] = 1;
		rnum[i] = rsize;//同上。
	}
	for (int i = 1;i < n;i++)
		ans = max(ans,lnum[i] + rnum[i + 1]);//按照预处理数组的定义，循环求最大值即可。
  	//结尾省略一些代码。
}
```

时间复杂度是 $\mathcal{O}(n)$，可以通过。

## 后记

这道题告诉我们，我们要在合适的条件下预处理、空间换时间，并且在数值规模较小的去重中将 `set/map` 替换为 `bool/int` 数组。

提示：如果 `define` 了 `int` 成 `long long`，`bool` 用 `int` 代替时要用 `signed`，用 `long long` 会拉低速度。

## 附录

[AC 记录（atcoder）](https://atcoder.jp/contests/abc397/submissions/63863841)

---

## 作者：LionBlaze (赞：0)

我们注意到，我们可以直接枚举隔开两个子串的下标 $i$。

那么我们维护两个序列，一个是 $(A_1,A_2,\dots,A_i)$，下面称为“左侧序列”，另一个是 $(A_{i+1},A_{i+2},\dots,A_N)$，称为“右侧序列”。另外，还需要维护“左侧序列”和“右侧序列”中各种元素的个数，和不同元素个数。

维护方法：如果在一个序列中添加一个元素，那么如果这个序列中原本没有这个元素（即对应元素数量为 $0$），则把不同元素个数增加 $1$。然后，不管序列中有没有这个元素，都把对应元素数量增加 $1$。删除同理，先把数量减少 $1$，如果减少之后变成了 $0$，则把不同元素个数也减少 $1$。

首先我们扫一遍求出当 $i=N$ 时的两个序列以及权值数组（实际上左侧序列并不需要维护，因为是空的）。注意此时不可以统计答案，因为序列为空并不满足题目要求（统计了也没事，可以证明此时的答案要么不是最优解，要么不是唯一的最优解）。

然后，从小到大枚举下标 $i$，把第 $i$ 个元素从右侧序列中删除，从左侧序列中加入。处理完成之后，统计答案即可。

[Code](https://atcoder.jp/contests/abc397/submissions/63782461)。当时代码写得比较混乱，实际上 `k1` 是右侧序列，`k2` 是左侧序列。

---

