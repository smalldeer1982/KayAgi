# [ROI 2018]  Decryption

## 题目背景

译自 [ROI 2018 Day2](https://neerc.ifmo.ru/school/archive/2017-2018.html) T1. [Расшифровка](https://neerc.ifmo.ru/school/archive/2017-2018/ru-olymp-roi-2018-day2.pdf) ([Decryption](https://codeforces.com/gym/102154/problem/B))。 

## 题目描述

研究表明，汉字的顺序并不一定能影响阅读。科学家们对数列进行了类似的研究。

给一个正整数数列，若数列首项为数列中所有数的最小值，末项为数列中的最大值，则我们称这是个正确的数列。例如，序列 $[1, 3, 2, 4]$ 和 $[1, 2, 1, 2]$ 是正确的，但序列 
$[1, 3, 2]$ 不是。

给出长度为 n 的序列 $[a_1, a_2, \ldots, a_n]$。对于该序列的某个片段 $[a_l, a_{l+1}, \ldots, a_r]$, 若该片段的首项为该片段中的最小值，末项为该片段中的最大值，则我们称这是个正确的片段。

对于给定的序列，请求出该序列至少需要被分成多少段，才能使得每个片段均为正确的片段。序列 $[2, 3, 1, 1, 5, 1]$ 可以分为三个正确的段：$[2, 3]$ 和 $[1, 1, 5]$ 和 $[1]$。

需要编写一个程序，该程序按给定的顺序确定可以划分的最小正确段数。

## 说明/提示

对于 $30\%$ 的数据，$1 \leq n \leq 500$。

对于 $60\%$ 的数据，$1 \leq n \leq 5000$。

对于所有数据，$1 \leq n \leq3 \times 10^5$，$1\leq a_i \leq 10^9$。

## 样例 #1

### 输入

```
5
5 4 3 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
4
1 3 2 4```

### 输出

```
1```

## 样例 #3

### 输入

```
6
2 3 1 1 5 1```

### 输出

```
3```

# 题解

## 作者：flangeborg (赞：26)

### 前言
修改题解太痛苦了，还是麻烦审核大大了。

一道特别痛苦的单调栈 + dp 的问题、500ms 的时间限制真的赛神仙。本人也用了挺长时间，也去参考了其他 AC 大佬的做法，最后才把这道题 A 过了。

## 题目大意
给定一个长度为 $n$ 的数组 $a$，一个合法序列的定义是：对于任意一个区间 $[l,r]$，区间的最小值为 $a_l$，最大值为 $a_r$。现在将这个长度为 $n$ 的数组 $a$ 分成 $k$ 段，使得其中每一段都是合法序列，试求 $k$ 最小值。

## 解题方法
- 看到“最小”、“最大”两个对于序列的限制，我们能够想到使用单调栈来维护数组。对于这道题我们需要用两个栈来维护。**一个是严格单调递减的栈（$stk1[n]$），还有一个是单调递增的栈（$stk2[n]$）**（关于为何使用这两种单调栈的问题建议配合后面的 AC 代码食用）。

- 其次，这道题还需要使用 dp 来求解。定义一个一维数组 $dp[n]$，**对于任意一个数组下标 $i$，$dp_i$ 表示到 $i$ 坐标处，分割出来的序列全为合法序列的最小分割次数。**

- 然后我们来构思状态转移方程，试想，如果当前坐标 $i$ 后（**注意是 $i$ 坐标后，否则状态转移会出问题**）需要进行分割以构成合法序列，上一次开始分割的坐标 $j$ 需要尽可能地小才能保证转移出的结果是最小的。

- 有了这样的想法，这时候就应该与前面提到的单调栈来配合了。由于这道题对数组内的顺序有严格要求，所以**这道题使用单调栈的时候，栈中存储的不是数组变量的值，而是数组变量的下标**。

## 两个重要的结论及其证明：
1. 在严格单调递减栈中，在当前循环到第 $i$ 次时，$i$ 入栈，由于栈中的严格递减性，栈顶 $i$ 所对应的 $a_i$ 一定会小于栈中 $i$ 下方（记为 $j$）所对应的 $a_j$ ，并且通过单调性也可以得出 $(j,i]$ 这个区间一定是合法的。

   **证明：使用反证法，假设 $(j,i]$ 区间为非法，则会至少有一个坐标 $l$ 使得 $a_l > a_i$，则会使得当前递减栈除栈顶外第一个元素不是 $j$，出现矛盾，说明结论正确。**
   
2. 在上一结论所描述的情况下，使用 STL 库中的 lower_bound 函数（[意义及用法](http://c.biancheng.net/view/7521.html)），以 $j$ 为目标（即作为函数中的第三个参数）在单调递增栈中二分查找到的结果（即一个小于等于 $j$ 的坐标，记为 $p$）在数组 $a$ 中所对应的值 $a_p$ 一定小于 $a_j$。

   **证明：同样使用反证法，假设存在一个坐标 $p$ 使得 $a_p > a_j$，因为 $p < j$，所以当 $j$ 进入单调递增栈时，$p$ 会被弹出栈，出现矛盾，说明结论正确。**

## 状态转移方程
- 通过这些结论以及先前的构思推导，我们终于可以把这道题目中最重要的状态转移方程给列出来了，代码如下：


	`dp[i]=dp[lower_bound(stk2+1,stk2+top2+1,stk1[top1-1])-1]+1;`

- 经过如此长的思维历程才推出来的状态转移方程竟然如此简单，接下来上代码。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300005],dp[300005],top1,top2,stk1[300005],stk2[300005];
//stk1：严格单调递减栈 stk2：单调递增栈（使用手写栈的原因是时间过于紧张） 
int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
	for(int i = 1; i <= n; i++)
	{
		while(top1 && a[stk1[top1]] <= a[i]) top1--;
		stk1[++top1] = i;
		while(top2 && a[stk2[top2]] > a[i]) top2--;
		stk2[++top2] = i;
		//维护两个单调栈 
		dp[i] = dp[*lower_bound(stk2 + 1,stk2 + top2 + 1,stk1[top1 - 1]) - 1] + 1;
		//千辛万苦得出的状态转移方程 
	}
	printf("%d",dp[n]);
	return 0;
} 
```
代码就到这了，希望能够对大家有所帮助。

---

## 作者：Loser_Syx (赞：13)

来一发题解。

## 思路

考虑维护两个单调栈，并用两个数组 $Max$ 和 $Min$ 依次存储当前递增的栈顶元素和当前递减的栈顶元素值**的下标**，这样预处理可以清楚地看到下标 $i$ 前面的较大值和较小值（由于是单调栈，存储递增的是维护的当前节点以它来说的前一个大于他的元素的下标，存储递减的是维护的前一个小于他元素的下标）。

如此一来，我们便可以从末尾开始枚举，因为末尾元素一定是其中某一段合法的区间的末尾，假如我们设当前的末尾元素下标为 $i$，暂定的开头元素下标为 $j$，如果存储的 $Max_i < Min_j$ 的话，说明 $j$ 前面的 $Min_j$ 一定符合条件，此处可以将开头调为 $Min_j$，当 $Max_i \geq Min_j$ 时，此时已经不能扩展，则将 $i$ 改为 $j-1$，统计答案。

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n + 1), mn(n + 1), mx(n + 1), mns, mxs;
	mns.emplace_back(0);
	mxs.emplace_back(0);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		while (mns.size() > 1 && a[i] < a[mns.back()]) {
			mns.pop_back();
		}
		while (mxs.size() > 1 && a[i] >= a[mxs.back()]) {
			mxs.pop_back();
		}
		mn[i] = mns.back();
		mx[i] = mxs.back();
		mns.emplace_back(i);
		mxs.emplace_back(i);
	}
	int res = 0;
	for (int i = n; i; ++res) {
		int j = i;
		for (; mx[i] < mn[j]; j = mn[j]);
		i = j - 1;
	}
	cout << res << '\n';
	return 0;
}
```

---

## 作者：Sorato_ (赞：7)

## 题目大意

给定一个长度为 $\large n$ 的序列 $\large a$，对于 $\large a$ 的一个子段 $\large[a_l,a_{l+1},...,a_r]$，若 $\large a_l=\min\limits_{i=l}^{r}(a_i), a_r=\max\limits_{i=l}^{r}(a_i)$，则这个子段是合法的，问如何划分才能使合法的子段数最小，输出最小子段数。

## 思路

首先，我们预处理出 $\large a_i$ 右侧第一个小于它的数的位置 $mn_i$，和 $a_i$ 右侧第一个大于等于它的数 $mx_i$，可以用单调栈预处理出来。

对于一个子段 $[l,r]$，若 $mx_r<mn_l$，则使 $r=mx_r$，直到不满足此条件。

这么做的道理很简单。要想使合法子段数最小，显然要使子段长度最长。对于一个左端点 $l$，它所对应的能使子段长度最长的右端点 $l$ 一定是在区间 $[l,mn_l)$ 中的最大值的位置，如果最大值在这段区间中出现了多次，则取最靠右的位置。

## Code

```c++
#include<bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#define reg register
#define int long long
using namespace std;
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	{x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,a[300010],mx[300010],mn[300010],ans,nxt[300010],pre[300010];
stack<int>maxx,minn;
signed main()
{
	n=read();
	for(reg int i=1;i<=n;i=-~i)	a[i]=read();
	maxx.push(1);minn.push(1);
	for(reg int i=2;i<=n;i=-~i)
	{
		while(!maxx.empty()&&a[i]>=/*大于等于，因为会有相同的值，赛时没写等号挂了*/a[maxx.top()])	mx[maxx.top()]=i,maxx.pop();
		while(!minn.empty()&&a[i]<a[minn.top()])	mn[minn.top()]=i,minn.pop();
		maxx.push(i);minn.push(i);
	}
	while(!maxx.empty())	mx[maxx.top()]=n+1,maxx.pop();
	while(!minn.empty())	mn[minn.top()]=n+1,minn.pop();
	for(reg int l=1,r=1;r<=n;r=-~r)
	{
		while(mx[r]<mn[l]&&r!=mx[r]&&r<=n)	r=mx[r];
		ans=-~ans;l=-~r;
	}
	return printf("%lld",ans),0;
}
```

---

## 作者：Exp10re (赞：6)

居然没人写题解，这下不得不抢沙发了。

## 简要题意

将长度为 $N$ 的数列 $[a_1,a_2,\cdots,a_n]$ 分为尽量少的若干段，使得每一段的首位为该段最小值，末位为该段最大值。（称其为合法段）

## 解题思路

显然，朴素的思想是枚举 $1,2,\cdots,n$ 之中的每一个 $i$，然后贪心往后寻找位置最靠后的 $p$ 使得 $[a_i,a_{i+1},\cdots,a_p]$ 是一个合法段。

但是朴素算法仅能获得 [85分的好成绩](https://www.luogu.com.cn/record/118733878)，考虑优化。

考虑使用 ST 表离线维护区间最小值和最大值。

容易得知，如果一个区间从第 $i$ 位开始，第 $k$ 位结束，那么显然 $[a_i,a_{i+1},\cdots,a_k]$ 中必定没有任何一个数小于 $a_i$。

枚举 $1,2,\cdots,n$ 之中的每一个 $i$，然后二分查找出 $i$ 之后第一个满足 $a_k \lt a_i$ 的最小的 $k$。

容易得知，使得 $[a_i,a_{i+1},\cdots,a_p]$ 是一个合法段的 $p$ 必定满足 $p \lt k$，于是先找到 $[a_i,a_{i+1},\cdots,a_{k-1}]$ 中最大的值（容易得知 $a_p$ 一定等于最大的值），然后考虑二分查找出使得 $[a_i,a_{i+1},\cdots,a_p]$ 是一个合法段且 $a_p$ 等于最大值的，位置最靠后的 $p$，那么这个 $p$ 一定是使得 $[a_i,a_{i+1},\cdots,a_p]$ 是一个合法段的最大的 $p$。

相较于朴素算法，时间复杂度从 $O(n^2)$ 降到了 $O(n\log n)$，可以接受。

大致思路就是这样，实现具体细节见代码吧。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=300110;
int log2(int t)
{
	return (int)(log(t)/log(2));
}
int a[MAXN],posl[31][MAXN],posg[31][MAXN],tpow[33];
int queryl(int l,int r)
{
	int t=log2(r-l+1);
	return min(posl[t][l],posl[t][r-tpow[t]+1]);
}
int queryg(int l,int r)
{
	int t=log2(r-l+1);
	return max(posg[t][l],posg[t][r-tpow[t]+1]);
}
int binsg(int l,int R,int num)//二分最大值 
{
	int m,r=R,ans=0,t;
	while(l<=r)
	{
		m=(l+r)/2;
		t=queryg(m,R);
		if(t<num)
		{
			r=m-1;
		}
		else
		{
			l=m+1;
			ans=m;
		}
	}
	return ans;
}
int binsl(int L,int r,int num)//二分最小值 
{
	int m,l=L,ans=0,t;
	while(l<=r)
	{
		m=(l+r)/2;
		t=queryl(L,m);
		if(t>=num)
		{
			l=m+1;
			ans=m;
		}
		else
		{
			r=m-1;
		}
	}
	return ans;
}
int main()
{
	int n,i,j,lgt,r,cnt=0;
	scanf("%d",&n);
	tpow[0]=1;
	for(i=1;i<=25;i++)
	{
		tpow[i]=tpow[i-1]*2;
	}
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		posl[0][i]=a[i];
		posg[0][i]=a[i];
	}
	for(i=1;i<=25;i++)//ST表 
	{
		for(j=1;j<=n;j++)
		{
			if(i+tpow[i-1]<=n)
			{
				posl[i][j]=min(posl[i-1][j],posl[i-1][j+tpow[i-1]]);
				posg[i][j]=max(posg[i-1][j],posg[i-1][j+tpow[i-1]]);
			}
			else
			{
				posl[i][j]=posl[i-1][j];
				posg[i][j]=posg[i-1][j];
			}
		}
	}
	for(i=1;i<=n;)
	{
		lgt=queryl(i,n);//判断i是否为[i,n]中的最大值，如果是，那么相对应的p取值范围为 [i,n]
		if(lgt==a[i])
		{
			r=n;
		}
		else
		{
			r=binsl(i,n,a[i]);
		}
		lgt=queryg(i,r);//寻找取值范围内最大值 
		r=binsg(i,r,lgt);//寻找最大值最靠后的位置 
		cnt++;//统计 
		i=r+1;//优化，直接跳到下一个不在段内的位置 
	}
	printf("%d",cnt);
	return 0;
}
```

---

## 作者：JJerry (赞：5)

# 题意

对于数列 $a_l,a_{l+1},a_{l+2},...,a_r$，规定当 $a_l$ 为其中的最小值，$a_r$ 为其中的最大值时，该数列为一个正确片段。求数组 $a$ 可以最少划分成多少个正确片段。

# 思路

对于数组中的第 $i$ 个数 $a_i$，由这个数为左端点的区间，其右端点只能在 $a_i$ 右侧，且离它最近的比他小的数的左边。如数组 $a=\{2,3,4,1,0\}$，以 $a_0$ 为左端点的区间，右端点只能在 $a_3$ 左侧的元素中取得。设数组 $mmin$ 用于存储每个数右侧离它最近的比他小的数的位置，如，$mmin[0]=3$，$mmin[3]=4$。形式化地，对于满足条件的区间 $[l,r]$，应符合 $r<mmin[l]$。其中的 $mmin$ 数组可以通过单调递增栈获得，具体实现参考代码。

但对于每一个区间而言，我们如何获得具体的 $r$ 呢？考虑到每个区间的右端点必须要比左端点的数小，所以我们仿照上述的 $mmin$ 数组，可以构造出一个 $mmax$ 数组，用于记录每个数右侧离它最近的比他大的数的位置，如，$mmax[0]=1$，$mmax[1]=2$。同时，为了满足题目中分割的区间尽可能多的要求，每个区间应尽可能的大。为了达成这个条件，在求取以 $l$ 为左端点区间的右端点 $l$ 时，可以从 $l$ 起跳，即令 $r=l$，每次跳到下一个离它最近，但比他大的数的位置上 $mmax[r]$，但只跳一次显然不能够获得最长区间，所以需要继续往下跳，直到跳出 $mmin[l]$，即 $mmax[r]>mmin[l]$ 时停止。如此一来，即可获得以 $l$ 为左端点的最长区间。在求取下一个区间时，我们只需要让 $l=r+1,r=l$，并再次重复上述操作即可。代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n, a[300005], mmax[300005]={}, mmin[300005]={}; cin >> n;
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
    }
    stack<int> stk1, stk2;
    for(int i = 1 ; i <= n ; i++){
        while(!stk1.empty() && a[stk1.top()] > a[i]){
            mmin[stk1.top()] = i;
            stk1.pop();
        }
        stk1.push(i);
    }
    while(!stk1.empty()) mmin[stk1.top()] = n+1, stk1.pop();
    for(int i = 1 ; i <= n ; i++){
        while(!stk2.empty() && a[stk2.top()] <= a[i]){
            mmax[stk2.top()] = i;
            stk2.pop();
        }
        stk2.push(i);
    }
    while(!stk2.empty()) mmax[stk2.top()] = n+1, stk2.pop();
    int l = 1, r = 1, ans = 0;
    while(r <= n){
        while(mmin[l] > mmax[r]) r = mmax[r];
        ans++, r = l = r+1;
    }
    cout << ans << endl;
}
```

---

## 作者：qzmoot (赞：3)

# 题面
[题目传送门](https://www.luogu.com.cn/problem/P9290)
# 方法分析
## 1.暴力
这道题一看暴力就能做，直接 $n^2$ 枚举，拿到了分，睡觉去。
## 2.RMQ
这道题目这么明显的一个序列中的最大值与最小值，直接考虑 RMQ，用 ST 表来维护。最后再寻找每个子区间就行了。

注意寻找时，我们不能找到空区间，遇到空区间我们直接跳过就行了。
### 一点点小优化
1. 对于一个已经合法的区间，我们将剩余的左边，和剩余的右边入队。

1. 对于以上三个序列都不合法，我们就要把合法区间的左半，右半，后面的区间入队。

# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;    // 定义常量N为300005
struct node{
	int l,r;    // 定义区间的左右边界
	node() {}    // 默认构造函数
	node(int l,int r)    // 构造函数，初始化左右边界
	{
		this->l=l;
		this->r=r;
	}
};
queue<node> q;    // 使用队列存储区间
int n,k,a[N],lg[N],max_[N][25],min_[N][25],minn,maxx,cnt;
// max_和min_用于存储区间的最大值和最小值
// minn和maxx用于记录当前处理的区间的最小值和最大值
int get_max(int x,int y)
{
	return a[x]<=a[y] ?y :x;    // 获取两个值中较大的值
}
int get_min(int x,int y)
{
	return a[x]<=a[y] ?x :y;   // 获取两个值中较小的值
}
int main()
{
	scanf("%d",&n);    // 输入序列的长度
	lg[0]=-1;   // 初始化lg数组
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		lg[i]=lg[i>>1]+1;
		max_[i][0]=min_[i][0]=i;    // 初始化区间的最大值和最小值
	}

	for(int j=1;j<=lg[n];j++)
		for(int i=1;i<=n;i++)
			if(i+(1<<(j))-1<=n)
			{
				max_[i][j]=get_max(max_[i][j-1],max_[i+(1<<(j-1))][j-1]);    // 计算区间的最大值
				min_[i][j]=get_min(min_[i][j-1],min_[i+(1<<(j-1))][j-1]);    // 计算区间的最小值
			}

	q.push(node(1,n));    // 将整个序列表示的区间入队
	while(!q.empty())
	{
		node tmp=q.front();
     q.pop();
		if(tmp.l>tmp.r)
			continue;
		k=lg[tmp.r-tmp.l+1];    
		maxx=get_max(max_[tmp.l][k],max_[tmp.r-(1<<k)+1][k]);   
		minn=get_min(min_[tmp.l][k],min_[tmp.r-(1<<k)+1][k]);   

		if(minn<=maxx)    // 分类1
		{
			cnt++;    // 计数加1
			q.push(node(tmp.l,minn-1));
			q.push(node(maxx+1,tmp.r));
		}
		else    //分类2
		{
			q.push(node(tmp.l,maxx)); 
			q.push(node(maxx+1,minn-1));
			q.push(node(minn,tmp.r));
		}
	}
	cout<<cnt;
	return 0;
}
```

给个小赞吧！

---

## 作者：WsW_ (赞：2)

### 更新
- $2023.11.17$ 改了一处写错的式子。  

感谢管理的仔细审核！

---
学数据结构学傻了，分享一个 ST 表加分讨递归的解法。   

---
### 思路
在一段区间中，必定存在一个**位置最靠前**的最小值和一个**位置最靠后**的最大值。而这两个决定了这个区间如何划分。  

假设 $f(l,r)$ 表示区间 $[l,r]$ 最少分成几段，区间中**位置最靠前**的最小值和**位置最靠后**的最大值的位置分别为 $pmin,pmax$。  
1. $l=pmin,r=pmax$ 时，这整个区间都是正确的。  
$f(l,r)=1$。  

2. $l=pmin,r<pmax$ 时，可以拆成 $[l,pmax],[pmax+1,r]$ 两个区间。  
其中，区间 $[l,pmax]$ 是正确的，我们只需要求出区间 $[pmax+1,r]$ 这个区间要分几段就行。  
$f(l,r)=1+f(pmax+1,r)$。  

3. $l<pmin,pmax=r$ 时，与上面一个分讨类似。  
$f(l,r)=f(l,pmin-1)+1$。  

4. $pmin=pmax+1$ 时，分成两个区间求。  
$f(l,r)=f(l,pmax)+f(pmin,r)$。  

5. $l<pmin\le pmax<r$ 时，分成三个区间，中间的那个区间是正确的。  
$f(l,r)=f(l,pmin-1)+1+f(pmax+1,r)$。

6. $l<pmax<pmin<r$ 时，分成三个区间。  
$f(l,r)=f(l,pmax)+f(pmax+1,pmin-1)+f(pmin,r)$。  

用 ST 表来存和查询最小值和最大值所在的位置。

时间复杂度 $O(n\log n)$。

---
### 思路
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[300003];
int smax[300003][20],smin[300003][20];
int lg2[300003];
int cnt;

void dfs(int l,int r){
	int x,y;
	int len=r-l+1;
	int pmin,pmax;
	
	x=a[smin[l][lg2[len]]],y=a[smin[r-(1<<lg2[len])+1][lg2[len]]];
	if(x<=y)pmin=smin[l][lg2[len]];
	else pmin=smin[r-(1<<lg2[len])+1][lg2[len]];
	
	x=a[smax[l][lg2[len]]],y=a[smax[r-(1<<lg2[len])+1][lg2[len]]];
	if(x<=y)pmax=smax[r-(1<<lg2[len])+1][lg2[len]];
	else pmax=smax[l][lg2[len]];
	if(pmin==l&&pmax==r){
		cnt++;
	}
	else if(pmin==l){
		cnt++;
		dfs(pmax+1,r);
	}
	else if(pmax==r){
		cnt++;
		dfs(l,pmin-1);
	}
	else if(pmin==pmax+1){
		dfs(l,pmax);
		dfs(pmin,r);
	}
	else if(pmin<=pmax){
		cnt++;
		dfs(l,pmin-1);
		dfs(pmax+1,r);
	}
	else{
		dfs(l,pmax);
		dfs(pmax+1,pmin-1);
		dfs(pmin,r);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	lg2[0]=-1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		smax[i][0]=smin[i][0]=i;
		lg2[i]=lg2[i>>1]+1;
	}
	for(int i=1;i<=lg2[n];i++){
		int len=1<<i;
		for(int l=1;l+len-1<=n;l++){
			int x,y;
			
			x=a[smin[l][i-1]],y=a[smin[l+(1<<i-1)][i-1]];
			if(x<=y)smin[l][i]=smin[l][i-1];
			else smin[l][i]=smin[l+(1<<i-1)][i-1];
			
			x=a[smax[l][i-1]],y=a[smax[l+(1<<i-1)][i-1]];
			if(x<=y)smax[l][i]=smax[l+(1<<i-1)][i-1];
			else smax[l][i]=smax[l][i-1];
		}
	}
	dfs(1,n);
	cout<<cnt;
	return 0;
}
```

---

## 作者：Red_Alert_star (赞：2)

# 洛谷 P9290

[题目传送门](https://www.luogu.com.cn/problem/P9290)

## 题意

对于序列 $[a_l, a_{l+1}, \ldots, a_r]$，若 $a_l$ 是该序列的最小值，$a_r$ 是该序列的最大值，则该序列是合法序列。已知长度为 $n$ 的序列 $[a_1, a_2, \ldots, a_n]$，试将该序列分成若干段合法序列，求最小分割段数。
## 分析
由题目可知，若区间 $[a_l, a_{l+1}, \ldots, a_r]$ 是合法序列，则其最小元素 $a_l$ 一定在该序列的首位，最大元素 $a_r$ 一定在末位。

### 第一种思路

暴力枚举：枚举 $i=1\ldots n$，对于每个 $i$，贪心选取大于等于 $i$ 的数直至第一个大于 $i$ 的数。但俗话说得好，暴力不一定能出奇迹。此算法的时间复杂度为 $O(n^2)$，无法通过所有数据。

### 另一种思路
直接求解效率较低，我们可以考虑进行逆向求解。我们可以运用**分治思想**，将序列 $[a_1, a_2, \ldots, a_n]$ 分成若干个子序列：
![](https://cdn.luogu.com.cn/upload/image_hosting/otmfqob6.png)
由题意得，一个合法序列的区间最小值在首位，区间最大值在末位。那对于区间 $[a_l, a_{l+1}, \ldots, a_r]$，我们不妨以其区间最大值和区间最小值的位置分割这个序列，从而将此序列分割成三个子序列，不断分割，进行求解。此处有两种情况：

（此处令区间最大值为 $max$，最小值为 $min$）

① $min$ 的位置在 $max$ 之前：
![](https://cdn.luogu.com.cn/upload/image_hosting/vy8b5593.png)
不难看出，此时区间 $2$ 是一个合法序列，且该序列**无法再向左右延伸**（自行理解一下），计数器 $ans = ans + 1$。那么此时我们只需继续以同样方式分割区间 $1$、$3$ 即可。

② $min$ 的位置在 $max$ 之后
![](https://cdn.luogu.com.cn/upload/image_hosting/8k7cx0fh.png)
此时，区间 $2$ 并不是合法序列，我们需要继续分割区间 $1$、$2$、$3$。

## 具体实现
①边界：由于一个合法序列最少有 $1$ 个元素，所以分割的边界为 $l$ $=$ $r$。

②由于需要调用区间最大值、最小值（[RMQ 问题](https://baike.baidu.com/item/rmq/1797559?fr=ge_ala)），考虑用 $\operatorname{ST}$ 表离线维护区间最小值和最大值。

③用 $\operatorname{BFS}$ 搜索每个子区间寻找合法序列。建立一个队列以存储每个符合要求的序列。

### 分割时的注意事项：

1. 对于情况①，区间 $[a_{min},a_{min+1}, \ldots, a_{max}]$ 已经是合法序列，只需搜索区间 $[a_l,a_{l+1}, \ldots,a_{min-1}]$ 和 $[a_{max+1}, \ldots,a_{r-1},a_r]$。

2. 对于情况②，三个区间皆非合法序列。由于 $min$， $max$ 是区间 $[a_l, a_{l+1}, \ldots, a_r]$ 的最大值、最小值，故 $min$ 也是区间 $[a_{min}, \ldots,a_{r-1},a_r]$ 的最小值，放在首位； $max$ 也是区间 $[a_l,a_{l+1}, \ldots,a_{max}]$ 的最大值，放在末位。所以须搜索区间 $[a_l,a_{l+1}, \ldots,a_{max}]$、 $[a_{max+1},a_{max+2}, \ldots,a_{min-1}]$ 和 $[a_l,a_{l+1}, \ldots,a_{max}]$。

3. 若 $min$ 与 $max$ 相同，则应返回**位置较前**的一个（即情况①），否则无法将区间分割成三个部分。

该方法的时间复杂度为 $O(n\log{n})$，符合本题要求。
## AC代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct node{
	int l;
	int r;
};
queue<node> q;
int a[300005],lg[300005],d1[300005][30]/*最大值*/,d2[300005][30]/*最小值*/,n,k,minn,maxx,ans=0;
//lg[]数组：预处理log2(x) 
int mx(int x,int y)
{
	if(a[x]<=a[y]) return y;
	else return x;
}
int mn(int x,int y)
{
	if(a[x]<=a[y]) return x;
	else return y;
}
//最大值最小值相同则返回位置靠前的那个 
int main()
{
	cin>>n;
	lg[0]=-1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		lg[i]=lg[i>>1]+1;
		d1[i][0]=d2[i][0]=i;//初始化 
	 }
	for(int j=1;j<=lg[n];j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(i+(1<<(j))-1<=n)
			{
				d1[i][j]=mx(d1[i][j-1],d1[i+(1<<(j-1))][j-1]);
				d2[i][j]=mn(d2[i][j-1],d2[i+(1<<(j-1))][j-1]);
			}
		}
	}
	//预处理(建立ST表) 
	q.push(node{1,n});
	while(!q.empty())
	{
		node t=q.front();
		q.pop();
		if(t.l>t.r) continue;
		k=lg[t.r-t.l+1];
		maxx=mx(d1[t.l][k],d1[t.r-(1<<k)+1][k]);
		minn=mn(d2[t.l][k],d2[t.r-(1<<k)+1][k]);//ST表查询 
		if(minn<=maxx)//情况① 
		{
			ans++;//找到一个合法队列就累加 
			q.push(node{t.l,minn-1});
			q.push(node{maxx+1,t.r});
		}
		else//情况② 
		{
			q.push(node{t.l,maxx});
			q.push(node{maxx+1,minn-1});
			q.push(node{minn,t.r});
		}
	}
	cout<<ans;
	return 0;//好习惯 
}

```


---

## 作者：sunzz3183 (赞：2)

# P9290 [ROI 2018] Decryption 题解

## 题意 

[见题面](https://www.luogu.com.cn/problem/P9290)

## 分析

~~作者模拟赛没想到单调栈，数据结构学傻了，只会线段树，这里写一篇线段树题解。~~

考虑贪心。

显然，对于一个左端点，尽量向右选是最优的，而不能向右选的一个条件就是遇见比左端点小的数字了，所以右端点的取值范围就是 $[i,j)$ 其中 $j$ 是第一个满足 $a_j<a_i$ 的数字。

然后对于第二个条件要满足左端点是最大值，那如果有多个最大值呢？那就取最靠右的最大值。

查小于某个数的第一个值，和查询区间最大值，这不明显线段树吗！

所以我们考虑维护

```cpp
struct Tree{
    int l,r,mn;
    pair<int,int>mx;
}tree[N<<2];
```

$mn$ 是区间最小值，$mx$ 设置一个 $pair$ 第一维是原值，第二位是左端点，方便比较。

找区间最大值比较简单，略。

找小于某个数的第一个值，我们可以考虑线段树上二分：

```cpp
inline int findmin(int k,int q,int x){
    if(q<=tree[k].l){
        if(tree[k].mn>=x)return 0;//如果都大于等于就不二分
        while(tree[k].l<tree[k].r)
            if(tree[k<<1].mn<x)k<<=1;
            else (k<<=1)|=1;
        return tree[k].l;
    }
    int mid=(tree[k].l+tree[k].r)>>1;
    if(q<=mid){
        int t=findmin(k<<1,q,x);
        if(t)return t;
        else return findmin(k<<1|1,q,x);
    }
    else return findmin(k<<1|1,q,x);
}
```

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=3e5+3;
int n,a[N],ans;
struct Tree{
    int l,r,mn;
    pair<int,int>mx;
}tree[N<<2];
void build(int l,int r,int k){
    tree[k].l=l,tree[k].r=r;
    if(l==r){
        tree[k].mx={a[l],l};
        tree[k].mn=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,k<<1);
    build(mid+1,r,k<<1|1);
    tree[k].mx=max(tree[k<<1].mx,tree[k<<1|1].mx);
    tree[k].mn=min(tree[k<<1].mn,tree[k<<1|1].mn);
    return;
}
inline int findmin(int k,int q,int x){
    if(q<=tree[k].l){
        if(tree[k].mn>=x)return 0;//如果都大于等于就不二分
        while(tree[k].l<tree[k].r)
            if(tree[k<<1].mn<x)k<<=1;
            else (k<<=1)|=1;
        return tree[k].l;
    }
    int mid=(tree[k].l+tree[k].r)>>1;
    if(q<=mid){
        int t=findmin(k<<1,q,x);
        if(t)return t;
        else return findmin(k<<1|1,q,x);
    }
    else return findmin(k<<1|1,q,x);
}
inline pair<int,int> findmax(int k,int l,int r){
    if(l<=tree[k].l&&tree[k].r<=r)return tree[k].mx;
    int mid=(tree[k].l+tree[k].r)>>1;
    if(r<=mid)return findmax(k<<1,l,r);
    else if(l>mid)return findmax(k<<1|1,l,r);
    else return max(findmax(k<<1,l,r),findmax(k<<1|1,l,r));
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    build(1,n+1,1);
    for(int i=1;i<=n;i++){
        int r=findmin(1,i+1,a[i]);
        i=findmax(1,i,r-1).second;
        ans++;
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：xiaomuyun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9290)

昨天晚上刚复习了一遍手写数据结构，今天模拟赛就用上了。

## 题意理解

你需要将序列划分为尽可能少的区间，且对于任何一个区间 $[l,r]$，需要保证 $a_l=\min\limits_{i=l}^{r}$ 并且 $a_r=\max\limits_{i=l}^{r}$。

请求出这个最少的区间数。

## 思路分析

### 抽象思路

贪心会很奇怪，所以在打模拟赛的时候我在想 dp。

设 $f_i$ 表示区间 $[1,i]$ 的最小划分区间数。

考虑 $f_i$ 可以从哪些位置转移。

因为 $i$ 肯定会作为 $[1,i]$ 这个区间的划分中最后一个区间的末尾，也就是最后一个区间的最大值。并且题目想要让划分的区间数量最少，所以综上所述，$f_i$ 的值应该为 $\min\limits_{j=1}^{i}f_{j-1}+1$，其中 $[j,i]$ 必须是一个正确的数列。

有一个性质：对于任意 $1 \le i < j \le n$，$f_i \le f_j$。一个区间的划分数量是不可能小于其前缀的划分数量的。

因此我们只需要找出最小的满足 $[j,i]$ 是正确数列的 $j$，$f_{j-1}$ 就是最小的。

那么对于每个 $i$，如何在 $\mathcal{O}(\log_2 n)$ 或 $\mathcal{O}(\sqrt{n})$ 的时间复杂度内求出 $j$ 呢？

### 实现思路

考虑维护一个严格单调递减的单调栈。在插入 $i$ 之后，我们会发现一个性质：此时这个栈的栈顶，也就是 $a_i$，和这个栈的次栈顶，设其为 $a_j$，区间 $(j,i]$（即 $[j+1,i]$）的最大值一定是 $a_i$。运用 **反证法**：如果这个区间中还有比 $a_i$ 大的数，这个栈的次栈顶就不会是 $a_j$ 了。

这个时候我们就只需要在 $[j,i]$ 中找到一个最小的左端点 $k$ 满足 $a_k=\min\limits_{x=k}^ia_x$ 即可。怎么做呢？

答案是再维护一个单调栈（~~鹅鹅鹅~~），但是这个单调栈是不严格单调递增的，我们可以用它来求出上文抽象思路中提到的需要求的 $j$。在插入 $i$ 之后，我们又会发现一个性质：栈中的任意一个数，若其在 $a$ 数组中的编号为 $k$，则 $[k,i]$ 的最小值一定是 $a_k$。同样，反证法易证，大家可以跟着我上面的思路去想，实在不会可以评论我。

综上所述，维护两个栈并分别插入 $i$ 之后，我们就只需要在不严格单调递增栈中，二分查找出第一个大于等于严格单调递减栈的次栈顶的位置即可。这个位置就是抽象思路中提到的要找的 $j$。

代码就不提供了，非常好写。

---

