# The Contest

## 题目描述

A team of three programmers is going to play a contest. The contest consists of $ n $ problems, numbered from $ 1 $ to $ n $ . Each problem is printed on a separate sheet of paper. The participants have decided to divide the problem statements into three parts: the first programmer took some prefix of the statements (some number of first paper sheets), the third contestant took some suffix of the statements (some number of last paper sheets), and the second contestant took all remaining problems. But something went wrong — the statements were printed in the wrong order, so the contestants have received the problems in some random order.

The first contestant has received problems $ a_{1, 1}, a_{1, 2}, \dots, a_{1, k_1} $ . The second one has received problems $ a_{2, 1}, a_{2, 2}, \dots, a_{2, k_2} $ . The third one has received all remaining problems ( $ a_{3, 1}, a_{3, 2}, \dots, a_{3, k_3} $ ).

The contestants don't want to play the contest before they redistribute the statements. They want to redistribute them so that the first contestant receives some prefix of the problemset, the third contestant receives some suffix of the problemset, and the second contestant receives all the remaining problems.

During one move, some contestant may give one of their problems to other contestant. What is the minimum number of moves required to redistribute the problems?

It is possible that after redistribution some participant (or even two of them) will not have any problems.

## 说明/提示

In the first example the third contestant should give the problem $ 2 $ to the first contestant, so the first contestant has $ 3 $ first problems, the third contestant has $ 1 $ last problem, and the second contestant has $ 1 $ remaining problem.

In the second example the distribution of problems is already valid: the first contestant has $ 3 $ first problems, the third contestant has $ 1 $ last problem, and the second contestant has $ 2 $ remaining problems.

The best course of action in the third example is to give all problems to the third contestant.

The best course of action in the fourth example is to give all problems to the second contestant.

## 样例 #1

### 输入

```
2 1 2
3 1
4
2 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2 1
3 2 1
5 4
6
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 1 3
5 6
4
1 2 3
```

### 输出

```
3
```

## 样例 #4

### 输入

```
1 5 1
6
5 1 2 4 7
3
```

### 输出

```
2
```

# 题解

## 作者：_Life_ (赞：12)

### 题意
有三个序列 $a,b,c$，长度分别为 $k_1,k_2,k_3$。设 $n=k_1+k_2+k_3$，将 $a,b,c$ 三个序列拼接后形成的序列是 $1 \sim n$ 的排列。你可以在 $a,b,c$ 间移动元素，使得 $a$ 排序后是 $1 \sim n$ 的前缀，$c$ 排序后是 $1 \sim n$ 的后缀，要求移动次数最少。

### 题解
我们可以把原问题转化一下：有一个只包含 $1,2,3$ 的长度为 $n$ 的序列。将这个序列划分成三段（一段可以为空），使第一段中 $1$ 的数量、第二段中 $2$ 的数量、第三段中 $3$ 的数量之和最大。$n$ 减该问题的答案就是原问题的答案。

我们不如先枚举第二段和第三段的分界点 $i$（第 $i$ 个算入第二段），显然有：
$$ans=\max_{i=0}^n [1,i]\text{中第一二段获得的最大答案}+[i+1,n]\text{中3的数量}$$

第一二段获得的最大答案要如何计算呢？不妨先只考虑序列只有两段时怎么做。还是枚举第一段和第二段的分界点 $i$：

$$ans=\max_{i=0}^n [1,i]\text{中1的数量}+[i+1,n]\text{中2的数量}$$

上面的柿子可以算出区间 $[1,n]$ 的最大答案，区间 $[1,i]$ 的最大答案:

$$\text{区间[1,n]的答案}-\text{[i+1,n]中2的数量}$$

把上面的柿子回代，这道题就做完了！实现细节见代码

### 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int k1,k2,k3,x[200005],a[200005],b[200005],c[200005],f[200005],g[200005];
int main()
{
	cin>>k1>>k2>>k3;
	for(int i=1,k;i<=k1;i++)cin>>k,x[k]=1;
	for(int i=1,k;i<=k2;i++)cin>>k,x[k]=2;
	for(int i=1,k;i<=k3;i++)cin>>k,x[k]=3;
	int n=k1+k2+k3,ans1=0,ans2=0;
	// for(int i=1;i<=n;i++)cout<<x[i]<<' ';
	// cout<<endl;
	for(int i=0;i<=n;i++)
	{
		a[i]=a[i-1]+(x[i]==1);
		b[i]=b[i-1]+(x[i]==2);
		c[i]=c[i-1]+(x[i]==3);
		f[i]=a[i]+k2-b[i];
		ans1=max(ans1,f[i]);
		g[i]=ans1-(k2-b[i])+(k3-c[i]);
		ans2=max(ans2,g[i]);
	}
	cout<<n-ans2;
}
```

---

## 作者：F_Mu (赞：10)

**题意**

三个人，每个人有一些数字，组合起来是$1$~$n$，每个人可以给另一个人一个拥有的数字，问最小操作数，使得第一个人拥有$1$~$i$的数，第二个人拥有$i+1$~$j$的数，第三个人拥有$j+1$~$n$的数，即第一个人为前缀，第二个人为中间部分，第三个人为后缀。
注意：可以有一个或两个人最后不拥有数字。

**分析**

看到三个人操作，我们先看两个人操作时的情况：

假设到最后，第一个人拥有$1$~$i$，第二个人拥有$i+1$~$n$，那么最小操作数为第二个人$1$~$i$中中拥有的数字加上第一个人$i+1$~$n$中拥有的数字。我们可以采用前缀和，$cnt1[k]$表示第一个人前$k$个数中拥有的个数，$cnt2[k]$表示第二个人前$k$个数中拥有的个数,则表达式为：
$$cnt2[i]+cnt1[n]-cnt1[i]$$
受到启发我们看三个人操作时的情况：

假设到最后，第一个人拥有$1$~$i$，第二个人拥有$i+1$~$j$，第三个人拥有$j+1$~$n$，那么最小操作数为第二个人和第三个人$1$~$i$中拥有的个数加上第一个人和第三个人$i+1$~$j$中拥有的个数加上第一个人和第二个人$j+1$~$n$中拥有的个数。我们可以采用前缀和，$cnt1[k]$表示第一个人前$k$个数中拥有的个数，$cnt2[k]$表示第二个人前$k$个数中拥有的个数，$cnt3[k]$表示第三个人前$k$个数中拥有的个数则表达式为：
$$cnt2[i]+cnt3[i]+cnt1[j]-cnt1[i]+cnt3[j]-cnt3[i]+cnt1[n]-cnt1[j]+cnt2[n]-cnt2[j]$$
化简得到:
$$cnt2[i]-cnt1[i]+cnt3[j]-cnt2[j]+cnt1[n]+cnt2[n]$$
我们从$0$~$n$枚举$i$，接下来我们考虑$j$的取值，我们可以看到对于固定的$i$，只需要找到一个$j$使得该式子最小即可，那么我们可以设置一个后缀$minn[]$数组，$minn[i]$表示当$i\leq j\leq n$时，$cnt3[j]-cnt2[j]$最小的值，那么答案即为：
$$cnt2[i]-cnt1[i]+minn[i]+cnt1[n]+cnt2[n]$$

**代码**
```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define LL long long
using namespace std;
const int maxn = (ll) 2e5 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;
int cnt1[maxn], cnt2[maxn], cnt3[maxn];
int minn[maxn];
vector<int> v1, v2, v3;

int main() {
    start;
    int k1, k2, k3;
    cin >> k1 >> k2 >> k3;
    v1.resize(k1 + 5);
    v2.resize(k2 + 5);
    v3.resize(k3 + 5);
    /*输入并标记*/
    for (int i = 1; i <= k1; ++i) {
        cin >> v1[i];
        ++cnt1[v1[i]];
    }
    for (int i = 1; i <= k2; ++i) {
        cin >> v2[i];
        ++cnt2[v2[i]];
    }
    for (int i = 1; i <= k3; ++i) {
        cin >> v3[i];
        ++cnt3[v3[i]];
    }
    int n = k1 + k2 + k3;
    for (int i = 1; i <= n; ++i) {//前缀和
        cnt1[i] = cnt1[i - 1] + cnt1[i];
        cnt2[i] = cnt2[i - 1] + cnt2[i];
        cnt3[i] = cnt3[i - 1] + cnt3[i];
    }
    /*如分析*/
    for (int i = 0; i <= n; ++i)
        minn[i] = cnt3[i] - cnt2[i];
    for (int i = n - 1; i >= 0; --i)
        minn[i] = min(minn[i + 1], minn[i]);
    int ans = inf;
    for (int i = 0; i <= n; ++i) {
        int t = cnt2[i] - cnt1[i] + minn[i] + cnt1[n] + cnt2[n];
        ans = min(ans, t);
    }
    cout << ans;
    return 0;
}
```
本场比赛$D$和$E$惨痛教训：玩后缀一定要注意边界！！！

---

## 作者：Steadywelkin (赞：3)

### 题意

有三个序列 $a_1,a_2,a_3$ ，分别有 $k_1,k_2,k_3$ 个元素，三个序列首尾相接得到一个 $[1,n]$ 的排列，一次操作定义为将其中一个序列中的元素删除并加入到另外一个序列中，要通过最少的操作次数，使得：

* $a_1$ 是 $1$ 到 $n$ 的前缀
* $a_3$ 是 $1$ 到 $n$ 的后缀
* $a_2$ 包含剩下的所有元素

问最小的操作次数。

### 分析

这里提供一个线段树优化的做法。

对于 $a_1$ 这个序列，如果我们要让它的操作次数最少，就是尽可能让操作后的序列与原来的序列有重复元素，同理对于 $a_2,a_3$ 也要尽可能少移动。

由于最终形成的是一个 $1$ 到 $n$ 严格递增的排列，那么我们可以处理出每一个对应位置原来属于哪一个序列中，这样问题就转化成为：

**给你一个长度为 n ，只包含 1,2,3 的序列，将这个序列分成 3 块（每一块可以为空），计第一块的贡献为 1 的数量，第二块的贡献为 2 的数量，第三块的贡献为 3 的数量，使得序列的贡献最大。**

我们考虑怎么处理这个问题，可以考虑先将整个块都分成一个部分，这样答案的贡献就是整个块中 $1$ 的数量。

接下来考虑再将这个部分中分离出来得到第二个部分以及第三个部分，如果暴力枚举，这样的复杂度为 $O(n^2)$ ，显然无法承受。

但可以注意到的是，我们在枚举过程中实际上有很多部分是重复的，这启示我们可以设第二、三块的端点位置为 $pos$ ，那么 $pos$ 后的位置一定是固定的，在每一次加入新的一个数的时候更新中间第二部分的答案后取最大值就是最终的答案。

每一次加入一个数就将后面的每一部分增加贡献，这可以通过线段树进行维护。

**注意：不要忘记可能出现中间第二部分为空的情况。**

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;
typedef long long ll;

inline int read()
{
	int a=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())
		a=(a<<3)+(a<<1)+ch-'0';
	return a*f;
}

const int mod=1e9+7;
const int N=2e5+5;
const int inf=0x3f3f3f3f;

int k1,k2,k3,n,pre[N],ans=inf,cnt;

struct node{
	int val,idx;
	node(int val=0,int idx=0):val(val),idx(idx){}
	inline bool operator<(const node& a)const{
		return val<a.val;
	}
}a[N];

namespace segment_tree
{
	int tr[N<<2],lazy[N<<2];
	
	inline int ls(int pos){return pos<<1;}
	inline int rs(int pos){return pos<<1|1;}
	
	inline void push_up(int pos)
	{tr[pos]=min(tr[ls(pos)],tr[rs(pos)]);}
	
	inline void push_down(int pos)
	{
		lazy[ls(pos)]+=lazy[pos];
		lazy[rs(pos)]+=lazy[pos];
		tr[ls(pos)]+=lazy[pos];
		tr[rs(pos)]+=lazy[pos];
		lazy[pos]=0; return;
	}
	
	void update(int pos,int l,int r,int L,int R,int val)
	{
		if(L<=l&&r<=R){tr[pos]+=val;lazy[pos]+=val;return;}
		int mid=(l+r)>>1;push_down(pos);
		if(L<=mid) update(ls(pos),l,mid,L,R,val);
		if(R>mid)  update(rs(pos),mid+1,r,L,R,val);
		push_up(pos); return; 
	} 
	
	int query(int pos,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return tr[pos];
		int mid=(l+r)>>1,ans=inf;push_down(pos);
		if(L<=mid) ans=min(ans,query(ls(pos),l,mid,L,R));
		if(R>mid)  ans=min(ans,query(rs(pos),mid+1,r,L,R));
		return ans;
	}
}
using namespace segment_tree;

signed main()
{
	k1=read();k2=read();
	k3=read();n=k1+k2+k3;
	
	for(int i=1;i<=k1;i++)
		a[i]=node(read(),1);
	for(int i=1;i<=k2;i++)
		a[i+k1]=node(read(),2);
	for(int i=1;i<=k3;i++)
		a[i+k1+k2]=node(read(),3);
		
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	
	for(int i=1;i<=n;i++)
		pre[i]=pre[i-1]+(a[i].idx==3?0:1);
		
	ans=cnt=k2+k3;
	
	for(int i=1;i<=n;i++)
	{
		update(1,1,n,i,i,pre[i-1]);
		update(1,1,n,1,i,(a[i].idx==2?0:1));
		cnt-=(a[i].idx==1?0:1);
		ans=min(ans,cnt+query(1,1,n,1,i));
		ans=min(ans,cnt+pre[i]);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
```


---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2000}$
---
### 解题思路：

直接做的话处理前后关系不是很好处理。不妨将问题转化为确定两个位置，使得这个位置前面的在第一个集合中的数量，中间的在第二个集合中的数量和最后的第三个集合中的数量的和最大。如果这个值为 $x$，显然 $n-x$ 就是原问题的答案。

根据上面的基本转换，可以记录下每一个值初始的时候在哪一个序列上。

设第一个分界位置为 $i$，第二个分界位置为 $j$，$cnt_{i,1/2/3}$ 分别表示在位置 $i$ 之前有多少序列 $1/2/3$ 中的值。则代价可以表示为：$cnt_{i,1}+cnt_{j,2}-cnt_{i,2}+k_3-cnt_{j,3}$，可以发现其实 $i,j$ 两个值比较割裂，所以直接取出其中一个，分开计算即可。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k1,k2,k3,a[200005],x,cnt1,cnt2,cnt3,res,ans;
int main(){
	scanf("%d%d%d",&k1,&k2,&k3);n=k1+k2+k3;
	for(int i=1;i<=k1;i++)scanf("%d",&x),a[x]=1;
	for(int i=1;i<=k2;i++)scanf("%d",&x),a[x]=2;
	for(int i=1;i<=k3;i++)scanf("%d",&x),a[x]=3;
	res=ans=-2147483647;
	for(int i=0;i<=n;i++){
		if(a[i]==1)cnt1++;
		if(a[i]==2)cnt2++;
		if(a[i]==3)cnt3++;
		ans=max(ans,cnt1-cnt2);
		res=max(res,ans+cnt2+k3-cnt3);
	}
	printf("%d\n",n-res);
	return 0;
}
```


---

## 作者：我就是辣鸡 (赞：2)

# 题目分析
只要保证$a_1$和$a_3$满足条件即可,所以我们几乎可以忽略$a_2$.

为了方便下面讲解,简化一下题面.

将每个元素想象成一棵棵带有编号的树,要通过一系列的操作,

将树种在上方($a_1$处),或种在下方($a_3$处),或因生长发育不合格而被扔掉($a_2$处),然后求最少次数使满足题目要求.

(读者看到此处可根据简化题面再独立思考一下如何解题)

# 思路解析

最优答案一类的问题,想到DP.

$F_{i,0/1/2}$表示所有树里到第i课时扔掉/种在上方/种在下方&nbsp;&nbsp;&nbsp;&nbsp;的最少操作次数,接下来要分情况讨论(第i棵树的**原始**状态):

## 1.在上方

$F_{i,0}=min(F_{i-1,1},F_{i-1,0})+ 1$&nbsp;&nbsp;如果这棵树被扔掉,那前面一棵一定不是种在下面

$F_{i,1}=F_{i-1,1}$&nbsp;&nbsp;这棵树不动,对答案没贡献

$F_{i,2}=min$ { $F_{i-1,2},F_{i-1}{1},F_{i-1,0}$} $+1$&nbsp;&nbsp;如果这棵树被种在下面,则前面树的状态无所谓

## 2.在下方

$F_{i,0}=min(F_{i-1,1},F_{i-1,0})+ 1$

$F_{i,1}=F_{i-1,1} + 1$

$F_{i,2}=min$ { $F_{i-1,2},F_{i-1}{1},F_{i-1,0}$}

理解同第一种情况,但要注意是否+1的问题

## 3.在$a_2$~~垃圾箱~~里

方程思路与1,2种情况相同,请读者自行推理

## 4.端点

第一棵树比较特殊,无法从第0棵树转移过来,需要初始化处理一下.

另外说一下时间复杂度,状态转移方程的复杂度是$O(n)$但是所有的树需要按照编号从小到大排序,所以时间复杂度为$O(nlogn)$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int n,m,t,a[200001],b[200001],c[200001],f[200001][3],d[200001],mx,oo;

inline int pd(int x,int y) {
	if(b[x] >= c[y]) return y;
	return x;
}

inline bool cmp(int x,int y) {
	return x < y;
}

int main() {
	scanf("%d%d%d",&n,&m,&t);
	for(int i = 1;i <= n; i++) {
		int u;
		scanf("%d",&u);
		d[++mx] = u;
		a[u] = 1;
		++oo;
	}
	for(int i = 1;i <= m; i++) {//因为a2可以被忽略,所以不做任何处理 
		int x;
		scanf("%d",&x);
	}
	for(int j = 1;j <= t; j++)  {
		int x;
		scanf("%d",&x);
		d[++mx] = x;
		a[x] = 2;
	}
	n = n + m + t;
	sort(d+1,d+mx+1,cmp);
	if(a[1] == 1) f[1][0] = f[1][2] = 1;
	if(a[1] == 0) f[1][1] = f[1][2] = 1;
	if(a[1] == 2) f[1][1] = f[1][0] = 1;
	for(int i = 2;i <= n; i++) {
		if(a[i] == 0) {
			f[i][0] = min(f[i-1][1],f[i-1][0]);
			f[i][1] = f[i-1][1] + 1;
			f[i][2] = min(f[i-1][2],min(f[i-1][0],f[i-1][1])) + 1;
		}
		if(a[i] == 2) {
			f[i][0] = min(f[i-1][1],f[i-1][0]) + 1;
			f[i][1] = f[i-1][1] + 1;
			f[i][2] = min(f[i-1][2],min(f[i-1][1],f[i-1][0]));
		}
		if(a[i] == 1) {
			f[i][0] = min(f[i-1][1],f[i-1][0]) + 1;
			f[i][1] = f[i-1][1];
			f[i][2] = min(f[i-1][2],min(f[i-1][1],f[i-1][0])) + 1;
		}
	}
	printf("%d",min(f[n][1],min(f[n][0],f[n][2])));
	return 0;
}
```

---

## 作者：_Lazy_zhr_ (赞：1)

不难发现只要让 $a_1$ 和 $a_3$ 满足条件即可。

令 $x_i$ 表示 $[1,i]$ 中有 $x_i$ 个数不在 $a_1$ 中，$y_i$ 表示 $[i,n]$ 中有 $y_i$ 个数不在 $a_3$ 中，$X_i$ 表示 $[i,n]$ 中有 $X_i$ 个数在 $a_1$ 中，$Y_i$ 表示 $[1,i]$ 中有 $Y_i$ 个数在 $a_3$ 中。特别的，若 $i=0$ 或 $i=n+1$，值为 $0$。

设 $dp_{i,j}$ 表示最终状态为 $a_1$ 包含 $[1,i]$，$a_2$ 包含 $[i+1,j-1]$，$a_3$ 包含 $[j,n]$。

则 $dp_{i,j}=(x_i+((k_1+x_i-i)-X_j))+(y_j+((k_3+y_j-(n-j+1))-Y_i))$。

最终答案为 $\min\limits_{0\le i<j\le n+1}dp_{i,j}$

这里我用了一些括号方便理解。前面一坨表示把 $[1,i]$ 全部加入 $a_1$ 中所要花的次数，后面一坨表示把 $[j,n]$ 全部加入 $a_3$ 中所要花的次数，剩下的请读者自行理解。

接下来把和 $i$ 有关的一坨与和 $j$ 有关的一坨全部预处理出来存到两个数组里，再搞个前（后）缀 $\min$。设这两个前（后）缀 $\min$ 分别为 $A$ 和 $B$。然后枚举一个 $s$，$A_s+B_{s+1}$ 为 $\min\limits_{0\le i\le s<j\le n+1}dp_{i,j}$。

最终答案为 $\min\limits_{0\le s\le n}A_s+B_{s+1}$。

[Submission](https://codeforces.com/contest/1257/submission/324769569)

Code：

```cpp
int N,n[5],a[5][MAXN],b[MAXN],x[MAXN],y[MAXN],X[MAXN],Y[MAXN];
void solve(){
	for(int i=1;i<=3;i++) cin>>n[i],N+=n[i];
	for(int i=1;i<=3;i++) for(int j=1;j<=n[i];j++){
		cin>>a[i][j];
		b[a[i][j]]=i;
	} for(int i=1;i<=N;i++) x[i]=x[i-1]+(b[i]!=1),Y[i]=Y[i-1]+(b[i]==3);
	for(int i=N;i;i--) y[i]=y[i+1]+(b[i]!=3),X[i]=X[i+1]+(b[i]==1);
	for(int i=1;i<=N;i++) x[i]=(x[i]<<1)-i-Y[i];
	for(int i=N;i;i--) y[i]=(y[i]<<1)-(N-i+1)-X[i];
	for(int i=2;i<=N;i++) Remin(x[i],x[i-1]);
	for(int i=N-1;i;i--) Remin(y[i],y[i+1]);
	int ans=INT_MAX;
	for(int i=0;i<=N;i++) Remin(ans,x[i]+y[i+1]+n[1]+n[3]);
	cout<<min(ans,n[1]+n[3])<<"\n";
}
```

---

## 作者：511017802yrb (赞：1)

提供一种不同于评论区的 ~~Guess~~ 解法：

## 题目描述

给定三个序列 $A$, $B$, $C$，长度分别为 $k_1$, $k_2$, $k_3$，将 $A$, $B$, $C$ 拼接后会形成一个长度为  
$$
n = k_1 + k_2 + k_3
$$  
的排列。

你可以在 $A$, $B$, $C$ 之间移动元素，使得 $A$ 排序后是 $1\sim n$ 的前缀，$C$ 排序后是 $1\sim n$ 的后缀，求最少移动次数。

---

## 题解

观察题目，$A$ 数组内选择的数字是从 $1$ 开始的排列前缀，$C$ 数组中选择的排列是从某个数字开始一直到 $n$ 的排列。我们先对三个数组 $A$, $B$, $C$ 各自排序，再进行进一步观察。

以样例 1 为例：  
排序后：

- $A$: $1\ 3$  
- $B$: $4$  
- $C$: $2\ 5$  

将它们拼接，得到新数组  
$$
b = [1,\,3,\,4,\,2,\,5]
$$  

那么，将此数组通过最少次数的移动变为升序，就是原问题的答案。

例如把元素 $2$ 移动到 $1$ 和 $3$ 之间后，  
$$
b = [1,\,2,\,3,\,4,\,5]
$$  
此时对应：

- $A$: $1\ 2\ 3$  
- $B$: $4$  
- $C$: $5$  

朋友们也可以尝试更多样例，发现这一规律！

- 本质上，问题转化为：将一个乱序排列，通过最少次数的移动，变为严格升序排列。  

想到 **最长递增子序列（LIS）**：  
> 最少移动次数 = $n - \mathrm{LIS}(b)$。  

下面给出 1A 记录：  
[E. The Contest](https://codeforces.com/contest/1257/submission/317428232)

```cpp
#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

int LIS(const vector<int>& a) {
    vector<int> d;
    for (int x : a) {
        auto it = lower_bound(d.begin(), d.end(), x);
        if (it == d.end()) {
            d.push_back(x);
        } else {
            *it = x;
        }
    }
    return d.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k1, k2, k3;
    cin >> k1 >> k2 >> k3;

    int n = k1 + k2 + k3;
    vector<vector<int>> a(4);
    for (int i = 1; i <= k1; i++){
        int x;
        cin >> x;
        a[1].push_back(x);
    }
    for (int i = 1; i <= k2; i++){
        int x;
        cin >> x;
        a[2].push_back(x);
    }
    for (int i = 1; i <= k3; i++){
        int x;
        cin >> x;
        a[3].push_back(x);
    }

    ranges::sort(a[1]);
    ranges::sort(a[3]);
    ranges::sort(a[2]);

    vector<int> b;
    for (auto x : a[1]) {
        b.push_back(x);
    }
    for (auto x : a[2]) {
        b.push_back(x);
    }
    for (auto x : a[3]) {
        b.push_back(x);
    }

    int h = LIS(b);
    cout << n - h << '\n';

    return 0;
}
```

---

## 作者：Jur_Cai (赞：1)

[如果 LaTeX 炸了可到博客来看 QwQ](https://www.luogu.com.cn/blog/JuruoCai/solution-cf1257e)

先考虑暴力枚举序列 $a_1$ 和 $a_3$ 的长度 $l_1$ 和 $l_3$。

则操作次数为 

- $[1,l_1]$ 不在 $a_1$ 中的数量，和 $a_1$ 中剩下的数量。

- $[n-l_3+1,n]$ 不在 $a_3$ 中的数量，和 $a_3$ 中剩下的数量。

- 同时 $a_1$ 中剩下的数可能在 $[n-l_3+1,n]$ 范围中，$a_3$ 中剩下的同理，贡献会被多算一遍，要减掉。

设 $Sum1_{x}$ 为原序列 $a_1$ 中小于等于 $x$ 的数量，$Sum3_{x}$ 为原序列 $a_3$ 中大于等于 $x$ 的数量。

写成式子为

$$
(l_1-Sum1_{l_1}+k_1-Sum1_{l_1})+(l_3-Sum3_{n-l_3+1}+k_3-Sum3_{n-l_3+1})-(k_1-Sum1_{n-l_3})-(k_3-Sum2_{l_1+1})
$$

发现 $Sum$ 可以用树状数组进行维护，就得到了 $O(n^2\log n)$ 的做法。

把上面的式子关于 $l_1$ 和 $l_3$ 的分开整理，可以发现都是能单独算的，那只要两边都取最小值再求和即可，时间复杂度 $O(n\log n)$。

Update：$Sum$ 数组可以直接维护，那就是 $O(n)$ 的了。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&-x
using namespace std;
int k1,k2,k3,n,mn[500005];
int tree1[500005],tree2[500005];
inline void add1(int x,int k) {
    for(; x<=n; x+=lowbit(x)) tree1[x]+=k;
}
inline void add2(int x,int k) {
    for(; x<=n; x+=lowbit(x)) tree2[x]+=k;
}
inline int query1(int x) {
    int res=0;
        for(; x; x-=lowbit(x)) res+=tree1[x];
    return res;
}
inline int query2(int x) {
    int res=0;
    for(x--; x; x-=lowbit(x)) res+=tree2[x];
    return k3-res;
}
int main() {
    scanf("%d%d%d",&k1,&k2,&k3),n=k1+k2+k3;
    for(int i=1,x; i<=k1; i++) {
        scanf("%d",&x);
        add1(x,1);
     }
     for(int i=1,x; i<=k2; i++) scanf("%d",&x);
     for(int i=1,x; i<=k3; i++) {
        scanf("%d",&x);
        add2(x,1);
    }
    //这里用一个mn数组存前缀最小值是防止结果出现l1+l3>n的情况
    memset(mn,0x3f,sizeof(mn));
    mn[0]=query2(1);
    for(int l=1; l<=n; l++)
        mn[l]=min(mn[l-1],l+query2(l+1)-query1(l)*2);
    int ans=n;
    for(int l=0; l<=n; l++)
        ans=min(ans,l+query1(n-l)-query2(n-l+1)*2+mn[n-l]);
    cout<<ans;
    return 0;
}
```

---

## 作者：龙水流深 (赞：0)

## 思路

看到这题，明显可以把题目转化为：给你一个长度为 $n$，只包含 1,2,3 的序列，将这个序列分成 3 段（每一段可以为空），给你一个长度为 $n$，只包含 1,2,3 的序列，将这个序列分成 3 块（每一块可以为空），计第一块的贡献为 1 的数量，第二块的贡献为 2 的数量，第三块的贡献为 3 的数量，使得序列的贡献最大，答案为 $n$ 减去块数。

以样例为例：

``2 1 2``

``3 1``

``4``

``2 5``

![](https://cdn.luogu.com.cn/upload/image_hosting/7uygnqfs.png)

## 做法

### 做法一

暴力枚举三块的分界点，用前缀和差分维护，时间复杂度 $O(n^2)$，无法通过。[测评记录](https://www.luogu.com.cn/record/70265981)

核心代码如下。
```cpp
//a1,a2,a3为题目中a1,a2,a3的前缀和
for(int i=0;i<=n;i++)
	for(int j=i;j<=n;j++)
		ans=max(ans,a1[i]+a2[j]-a2[i]+a3[n]-a3[j]);
```

### 做法二

可以注意到，暴力做法中，如果先枚举二，三两段的分界线，第三段可以 $O(1)$ 求出，然后前面的东西其实是可以用线段树维护最值的。每次转移复杂度为 $O(\log n)$，总复杂度 $O(n\log n)$，可以通过此题。

以下为核心代码。
```cpp
for(int i=1;i<=n;i++)
{
	update(1,1,n,i,i,pre[i-1]);
	update(1,1,n,1,i,(a[i].idx==2?0:1));
	cnt-=(a[i].idx==1?0:1);
	ans=min(ans,cnt+query(1,1,n,1,i));
	ans=min(ans,cnt+pre[i]);
}
```
### 做法三

注意到在做法二中，枚举分界线后，前面的答案为一段前缀，一段后缀，只要预处理出前缀和，即可求出前缀最大值，每次转移 $O(1)$，总之间复杂度 $O(n)$。

核心代码
```cpp
for(int i=0;i<=n;i++)
{
	s=max(s,a1[i]+k2-a2[i]);
	ans=max(ans,s-(k2-a2[i])+(k3-a3[i]));
}
```

## 代码

### 线段树

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;
typedef long long ll;

inline int read()
{
	int a=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())
		a=(a<<3)+(a<<1)+ch-'0';
	return a*f;
}

const int mod=1e9+7;
const int N=5e5+5;
const int inf=0x3f3f3f3f;

int k1,k2,k3,n,pre[N],ans=inf,cnt;

struct node{
	int val,idx;
	node(int val=0,int idx=0):val(val),idx(idx){}
	inline bool operator<(const node& a)const{
		return val<a.val;
	}
}a[N];

namespace segment_tree
{
	int tr[N<<2],lazy[N<<2];
	
	inline int ls(int pos){return pos<<1;}
	inline int rs(int pos){return pos<<1|1;}
	
	inline void push_up(int pos)
	{tr[pos]=min(tr[ls(pos)],tr[rs(pos)]);}
	
	inline void push_down(int pos)
	{
		lazy[ls(pos)]+=lazy[pos];
		lazy[rs(pos)]+=lazy[pos];
		tr[ls(pos)]+=lazy[pos];
		tr[rs(pos)]+=lazy[pos];
		lazy[pos]=0; return;
	}
	
	void update(int pos,int l,int r,int L,int R,int val)
	{
		if(L<=l&&r<=R){tr[pos]+=val;lazy[pos]+=val;return;}
		int mid=(l+r)>>1;push_down(pos);
		if(L<=mid) update(ls(pos),l,mid,L,R,val);
		if(R>mid)  update(rs(pos),mid+1,r,L,R,val);
		push_up(pos); return; 
	} 
	
	int query(int pos,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return tr[pos];
		int mid=(l+r)>>1,ans=inf;push_down(pos);
		if(L<=mid) ans=min(ans,query(ls(pos),l,mid,L,R));
		if(R>mid)  ans=min(ans,query(rs(pos),mid+1,r,L,R));
		return ans;
	}
}
using namespace segment_tree;

signed main()
{
	k1=read();k2=read();
	k3=read();n=k1+k2+k3;
	
	for(int i=1;i<=k1;i++)
		a[i]=node(read(),1);
	for(int i=1;i<=k2;i++)
		a[i+k1]=node(read(),2);
	for(int i=1;i<=k3;i++)
		a[i+k1+k2]=node(read(),3);
		
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	
	for(int i=1;i<=n;i++)
		pre[i]=pre[i-1]+(a[i].idx==3?0:1);
		
	ans=cnt=k2+k3;
	
	for(int i=1;i<=n;i++)
	{
		update(1,1,n,i,i,pre[i-1]);
		update(1,1,n,1,i,(a[i].idx==2?0:1));
		cnt-=(a[i].idx==1?0:1);
		ans=min(ans,cnt+query(1,1,n,1,i));
		ans=min(ans,cnt+pre[i]);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
```

### 前缀数组

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,s,ans,k1,k2,k3,a1[200005],a2[200005],a3[200005];
int main()
{
	cin>>k1>>k2>>k3;
	for(int i=1,k;i<=k1;i++) cin>>k,a1[k]=1;
	for(int i=1,k;i<=k2;i++) cin>>k,a2[k]=1;
	for(int i=1,k;i<=k3;i++) cin>>k,a3[k]=1;
	n=k1+k2+k3;
	for(int i=0;i<=n;i++)
	{
		if(i)
		{
			a1[i]+=a1[i-1];
			a2[i]+=a2[i-1];
			a3[i]+=a3[i-1];
		}
		s=max(s,a1[i]+k2-a2[i]);
		ans=max(ans,s-(k2-a2[i])+(k3-a3[i]));
	}
	cout<<n-ans;
	return 0; 
}
```

---

## 作者：ljfty (赞：0)

做一遍前缀和，令 $b_{x,y}$ 表示序列 $x$ 包含 $1\sim y$ 的数字有几个。考虑枚举第一个序列保留哪个前缀 $1\sim i$，对于第三个序列，如果保留了后缀 $j\sim n(i<j)$。

考虑哪些数需要被移掉，这样恰好能不重不漏。那么答案就是：

$$b_{1,n}-b_{1,i}+b_{2,n}-(b_{2,j-1}-b_{2,i})+b_{3,j-1}$$

可以发现只要维护 $-b_{2,j-1}+b_{3,j-1}$ 的后缀 $\min$ 就好了，剩下的都是定值。时间复杂度 $O(n)$，头尾稍微注意一下。

***code:***

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define Min(x,y)((x)<(y)?x:y)
#define For(i,x,y)for(i=x;i<=(y);i++)
#define Down(i,x,y)for(i=x;i>=(y);i--)
int a1[N],a2[N],a3[N],suf[N];
int read()
{
	int A;
	bool K;
	char C;
	C=A=K=0;
	while(C<'0'||C>'9')K|=C=='-',C=getchar();
	while(C>'/'&&C<':')A=(A<<3)+(A<<1)+(C^48),C=getchar();
	return(K?-A:A);
}
int main()
{
	int k1,k2,k3,n,i,ans=INT_MAX;
	k1=read(),k2=read(),k3=read();
	n=k1+k2+k3;
	For(i,1,k1)a1[read()]=1;
	For(i,1,k2)a2[read()]=1;
	For(i,1,k3)a3[read()]=1;
	For(i,2,n)
	{
		a1[i]+=a1[i-1];
		a2[i]+=a2[i-1];
		a3[i]+=a3[i-1];
	}
	suf[n]=-a2[n]+a3[n];
	Down(i,n-1,0)suf[i]=Min(suf[i+1],-a2[i]+a3[i]);
	For(i,0,n)ans=Min(ans,suf[i]+a1[n]-a1[i]+a2[n]+a2[i]);
	cout<<ans;
	return 0;
}
```

---

