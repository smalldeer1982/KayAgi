# 「Cfz Round 9」Hope

## 题目描述

她的面前有 $n$ 堆花瓣。其中，第 $i$ 堆花瓣中共有 $a_i$ 片花瓣。

你可以选择若干堆花瓣，并在你选择的每一堆花瓣中拿出任意正整数片花瓣，最后将所有拿出的花瓣组成一堆新的花瓣。你**不能将某一堆花瓣中的所有花瓣都拿走**，但你可以选择 $0$ 堆花瓣，即不进行任何操作。**你只能进行至多一次操作。**

她希望，在你操作结束后，最小的**不等于任意一堆中花瓣的数量**的正整数尽可能大。

你想求出这个正整数的最大值。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组测试数据，你可以选择第 $1$ 堆花瓣并拿走 $2$ 片花瓣。

对于第 $2$ 组测试数据，你可以不进行任何操作。

对于第 $3$ 组测试数据，你可以拿走第 $1$ 堆花瓣中的 $1$ 片花瓣和第 $4$ 堆花瓣中的 $5$ 片花瓣。

#### 「数据范围」

对于所有测试数据，保证：

- $1 \le T \le 10$；
- $1 \le n \le 10^5$；
- $1 \le a_i \le 10^9$。

**本题采用捆绑测试。**

- Subtask 0（10 points）：$n=1$。
- Subtask 1（30 points）：序列 $a$ 中的每一项互不相同。
- Subtask 2（24 points）：$a_i \le 10^4$。
- Subtask 3（36 points）：无特殊限制。

## 样例 #1

### 输入

```
3
3
6 1 3
6
3 1 2 1 1 3
4
3 4 3 6```

### 输出

```
5
4
5```

# 题解

## 作者：kind_Ygg (赞：11)

保姆级题解。
## 题目大意
~~相信你不是外星人。~~
## 思路
最小值最大，一眼二分，三分钟假掉。  
正解似乎只能是贪心，我们通过阅读题目可得，我们要操作成一个以 $1$ 为首项，公差为 $1$ 的等差数列，所以首先排序。然后，分两种情况讨论（咱们设当前答案为 $answer$）：
1. $a_i \ge answer$
2. $a_i < answer$

注：下文 $num$ 是可加可不加的，$sum$ 是必须加的。  
第一种情况：我们就要将 $a_i$ 变为 $answer$（为了填补序列空缺），所以 $sum$ 加上 $a_i-answer$，由于此时的 $answer$ 已经被填好了，因此 $answer$ 加一。

第二种情况：由于 $a_i < answer$，我们也不能去改变 $a_i$ 的值，所以将 $a_i$ 忽略不计，它无论为何值都不会影响答案（前面的数已经构成了从 $1$ 到 $answer-1$ 的等差数列，这就代表 $[1,answer-1]$ 的数都有了，而 $a_i$ 只能比它本身小），但它本身又可以为答案产生贡献，所以 $num$ 加上 $a_i-1$（$-1$ 是因为题目说不能删完）。

最后，如果 $ans$ 在 $[sum,sum+num]$ 中，就代表可以填补 $ans$ 这个空缺，所以 $answer+1$。
## Code

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e5+5;
int T,n,a[N];
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1);
		int ans=1;
		int num,sum;
		num=sum=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>=ans) sum+=a[i]-ans,ans++;
			else num+=a[i]-1;
		}
		if(sum<=ans and sum+num>=ans) ans++;
		cout<<ans<<'\n';
	}
	return 0;
}
```
## 后话
这题的贪心策略有些复杂，但只要想到了就秒切。  
祝各位 OIer 们 CSP/NOIP RP++。

---

## 作者：Zskioaert1106 (赞：10)

题目传送门：[P11205 「Cfz Round 9」Hope](https://www.luogu.com.cn/problem/P11205)

> 现实是必须接受的，希望是可有可无的吗？

### 题意分析

我们要将序列 $a$ 经过修改后，变成含有子序列 $1,2,\dots,x$ 的一个序列，同时我们对于每堆只能删除，那么要使最终可能留下的 $x$ 更大，我们必然要让尽量少的花瓣堆去通过删除。

### 做题过程

所以考虑先将序列 $a$ 升序排序。

然后将最小的一堆减去 $1$，得到的差就是我们必须拿出的；第二个与 $2$ 作差，以此类推。

那如果（排序后的）$a_i<i$ 呢？

那这一堆就不能为构成 $i$ 片的花瓣堆所用了。而我们要尝试用 $a_{i+1}$ 去构成 $i$ 片的花瓣堆。

所以我们发现，$a_i$ 的花瓣就处在一种可拿可不拿的状态，我们可以从 $a_i$ 中拿走 $1\sim a_i-1$ 中任意个花瓣。

所以我们设立一个 $flag$ 初始为 $1$，遍历时如果 $a_i\geqslant flag$ 则将 $a_i-flag$ 加入必须拿出的总数 $reality$ 中，并将 $flag\leftarrow flag+1$；否则将 $a_i-1$ 加入可有可无的可腾挪量 $hope$，而 $flag$ 不动。

如果最终的 $reality\leqslant flag$ 并且 $reality+hope \geqslant flag$，那么经过一番腾挪或不腾挪，答案 $\operatorname{mex}(a_1,a_2,\dots,a_n)=flag+1$，否则答案为 $flag$。

### 编写代码

代码的编写还算简单。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
    	int n,a[100005],reality=0,hope=0,flag=1;
    	cin>>n;
    	for(int i=1;i<=n;i++)cin>>a[i];
    	sort(a+1,a+1+n);
    	for(int i=1;i<=n;i++){
    		if(a[i]>=flag){
    			reality+=a[i]-flag;
    			flag++;
			}
			else{
				hope+=a[i]-1;
			}
		}
		if(reality<=flag&&reality+hope>=flag)cout<<flag+1;
		else cout<<flag;
		cout<<endl;
	}
    return 0;
}
```

[欸？](https://www.luogu.com.cn/record/183296444)

- 不开 long long 你会在最后一个点见祖宗。

- [AC 记录](https://www.luogu.com.cn/record/183296508)。

---

## 作者：pies_0x (赞：6)

# 「Cfz Round 9」Hope 题解
如果我们要让操作后答案为 $k$，则必须要有 $k-1$ 堆花瓣，花瓣个数为 $1,2,\dots,k-1$。

---
我们可以先将花瓣堆排序，然后贪心地进行以下操作：

定义变量 $ans$，为最终答案。

定义变量 $k1$ 和 $k2$，分别为必须拿走多少花瓣和有多少花瓣可以选择拿走。

$ans$ 一开始先为 $1$。

若 $a_i\ge ans$，则 $k1$ 增加 $a_i-ans$，同时 $ans$ 增加 $1$；

反之，则 $k2$ 增加 $a_i-1$。

最终，如果 $k1\leq ans-1\leq k1+k2$，$ans$ 增加 $1$。

---
进一步解释一下：
>若 $a_i\ge ans$，则 $k1$ 增加 $a_i-ans$，同时 $ans$ 增加 $1$

两种情况：
1. $a_i=ans$：显然，存在有 $ans$ 个花瓣的花瓣堆，$ans$ 要增加；
2. $a_i>ans+1$：贪心地将 $a_i$ 减少到 $ans$，以得到情况 $1$，由于后面每一堆的花瓣都比这一堆多，则减少这个花瓣堆的花瓣最优，显然必须减少，否则无法贪心地凑出 $ans$，所以将减少的花瓣统计到 $k1$。
>反之，则 $k2$ 增加 $a_i-1$。

尽量贡献更多的可要可不要的花瓣是这堆花瓣可以做出的唯一贡献。
>最终，如果 $k1\leq ans\leq k1+k2$，$ans$ 增加 $1$

如果 $k1\leq ans\leq k1+k2$，则减少的花瓣可以凑出 $ans$，$ans$ 还要增加 $1$。

## 代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

#define N 100005
#define int long long

int n;
int a[N];

signed main()
{
	int tt;
	scanf("%lld",&tt);
	while(tt--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]);
		sort(a+1,a+n+1);
		int ans=1;
		int k1=0,k2=0;
		for(int i=1;i<=n;++i)
			if(a[i]>=ans)
				k1+=a[i]-ans,
				++ans;
			else
				k2+=a[i]-1;
		if(k1<=ans&&ans<=k1+k2)
			++ans;
		printf("%lld\n",ans);
	}
	return 0;
}
```
[Record](/record/183254137)

---

## 作者：WA_sir (赞：3)

## [题目链接](https://www.luogu.com.cn/problem/P11205)

使“最小的不等于任意一堆中花瓣的数量的正整数”尽可能大，也就是要利用操作造出最长的 $1 \sim k$ 的排列，答案即为 $k+1$。

先将花瓣堆按花瓣数从小到大排序。

接下来 $k$ 从 $1$ 开始尝试。假设当前枚举到 $a_i$.

- 若 $a_i \geq k$，需将 $a_i$ 变为 $k$，此时**必须拿走的花瓣** $mu$ 加上 $a_i-k$。

- 若 $a_i < k$，这堆花瓣已经对答案没有直接贡献。由于不能拿走所有花瓣，**可以拿走的花瓣** $u$ 加上 $a_i-1$。

枚举完后的 $k+1$ 并不一定是最终答案。若 $mu \leq k+1$ 且 $mu+u \geq k+1$，此时必定可以凑出一堆有 $k+1$ 片花瓣的花瓣堆。答案则为 $k+2$。

### 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005],k;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		k=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",a+i);
		sort(a+1,a+n+1);
		long long mu=0,u=0;
		for(int i=1;i<=n;i++)
		{
			while(k>a[i]&&i<=n)u+=a[i++]-1;
			if(i>n)break;
			mu+=a[i]-k;
			k++;
		}
		if(mu<=k&&mu+u>=k)k++;
		printf("%d\n",k);
	}
	return 0;
}
```

祝 cfz 生快。

---

## 作者：jiangyunuo (赞：3)

### 意思：

有 $n$ 堆花瓣，第 $i$ 堆中有 $a_i$ 片花瓣。

接下来我们会从这些花瓣中选出若干堆，从选出的花瓣堆各取一些花瓣，不能取完，把取出的花瓣另外组成一堆，此时我们会得到一个数字，这个数字不等于任何一堆花瓣的数量，且是最小的，求这个数字的最大值。

### 思路：

显然我们要让这些花瓣数量从 $1$ 依次向上排，因此我们需要先来一个 `sort` 排序。

接着我们就可以计算取出的花瓣数量了，如果排序后的第 $i$ 堆花瓣数量为 $b_i$，且 $m$ 表示前面排入序列（即用于排列 $1,2,3,\dots$，除去加入序列的花瓣堆，剩下的是用来控制取出的花瓣新组成的花瓣堆的花瓣数量的）的花瓣堆的数量，那么如果 $b_i > m$ 则取出的数量为 $b_i - m$，且第 $i$ 堆花瓣加入序列，反之这堆取的数量为 $0 \sim b_i-1$。

最后如果用取出的花瓣组成的花瓣堆判断一下，$sum$ 表示加入序列的那些花瓣堆取出的花瓣数量，$top$ 表示剩余花瓣堆的最大可取出的花瓣数量，判断方法：如果 $sum \le m+1 \le top+sum$ 那么就可以得到的数字最大是 $m+2$（因为满足上述条件可以让新组成的花瓣堆也加入序列） 反之就是 $m+1$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int n,m;
	long long sum,top;
    int a[100000];
    for(int i=1;i<=t;i++){
        cin>>n;
        m=0;
        sum=0;
        top=0;
        for(int j=1;j<=n;j++)cin>>a[j];
        sort(a+1,a+n+1);
        for(int j=1;j<=n;j++){
		    if(a[j]>m){m++;sum+=(a[j]-m);}
		    else top+=(a[j]-1);
		}
        if(sum<=m+1&&sum+top>=m+1)cout<<m+2<<endl;
        else cout<<m+1<<endl;
    }
	return 0;
}
```
### 原因：
对于为什么要这样做，再次解释一下，由于我们想让结果更大，我们需要让花瓣的个数将从 $1$ 开始一直往上的数，尽量多占点，我们有两种方法，第一种就是将已有序（从小到大）的花瓣数量分别去占从 $1$ 开始一直往上的数，第二种就是将取走的花瓣在占掉下一个数（当然，不一定能占掉，所以我们就需要判断）。

---

## 作者：signed_long_long (赞：2)

# 题目解法
先从小到大排序，然后再拿花瓣，先拿到 $1$，再一个一个往上加。定义 $x$ 为现在要拿到的花瓣数，$s$ 为一定要拿的花瓣数，$k$ 为可以拿也可以不拿的花瓣数，如果 $x\le a_i$，就用 $s$ 加上 $a_i-x$，答案增加一，否则就把 $k$ 增加 $a_i$。

最后，如果 $s\le x\le s+k$，就把答案增加一（拿走的花瓣数刚好能填一个数），最后输出答案即可。

代码：
```cpp
#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int a[100500];
void w(){
	int n,aa=0,bb=0;//aa对应s，bb对应k
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",a+i);
	}
	sort(a+1,a+n+1);
	int q=1;
	for(int i=1;i<=n;i++){
		if(a[i]>=q) aa+=a[i]-(q++);
		else bb+=a[i]-1;
	}
	if(aa<=q and aa+bb>=q) q++;
	printf("%lld\n",q);
}
signed main() {
	scanf("%lld",&T);
	for(int i=1;i<=T;i++){
		w();
	}
    return 0;
}
```

---

## 作者：Hy13_xsm (赞：1)

## 题意概述
有一个长度为 $n$ 的数列 $a$，可以进行如下操作：

选取若干个数，将它们分别减去一个数 $x$，也就是说每一个数对应的减数 $x$ **不一定**相等，且对于第 $i$ 个选定的数，$a_i-x\ge 1$，简单来讲就是不能减完。然后在数列中插入一个新的数，它的数值为 $\sum x$，可以发现操作过后数列中所有数的和与操作前相等。需要注意的是，可以不进行任何修改。

现在需要进行最多 $1$ 次操作，求数列 $a$ 的 $\text{mex}$ 最大的可能值。

## 题目分析

稍微想一想就能发现，想要 $\text{mex}$ 变大，就至少要让数列中由 $1$ 开始的自然数序列最长。而达到这样的目的，可以对数列进行排序，定义一个变量 $k=1$，然后依次找不大于 $k$ 的数，找到了的话 $k$ 就自增，最后的 $k$ 就是不把 $\sum x$ 插入时的 $\text{mex}$。（此时的减法操作已经执行完毕）

然后考虑插入 $1$ 个数。需要注意的是，操作时选中的数所减去的值在后面必须加回去，至于没有被选中的数，可以随意支配。（但是至少要将值留在 $1$ 及以上，这样才满足题目要求）

当必须插入的值已经大于 $k$，就不能与之前选中的数列合并为一个自然数序列。或者必须和不必须的总和加起来不到 $k$，也不能合并。这种情况下 $\text{mex}$ 为 $k$。而如果恰恰与前面的情况相反，那么 $\text{mex}$ 为 $k+1$。到这里问题就迎刃而解。这道题用了贪心的思想和分类讨论，很锻炼思维，是一道好题。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define N 100005
#define int long long
using namespace std;
int t,k,m,s,n,a[N];//s,m分别代表非必要值和必要值 
signed main()
{
	cin>>t;
	while(t--)
	{
		k=1;m=0;s=0;
		cin>>n;
		for(int i=1	;i<=n;i++)
		cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
		{
			if(a[i]>=k)
			{
				m+=a[i]-k;
				k++;
			}else s+=a[i]-1;
		}
		if(m<=k&&m+s>=k)cout<<k+1<<endl;
		else cout<<k<<endl;
	}
	return 0;
}//不要抄袭谢谢 
```

---

## 作者：篮网总冠军 (赞：1)

一眼题。

因为我们要这个正整数尽量大，所以我们要把花瓣变成从 $1$ 开始的连续正整数，且长度尽量大。

接着，我们要利用剩余的花瓣。

首先，如果这些选中的堆拿出花瓣的和已经超过了需要的个数，显然是不行的。

其次，如果选中的堆拿出花瓣的和加上未选堆花瓣的和还不够组成新堆，那也不行。

最后，都是可以的情况，加 $1$ 即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
long long a[100005];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);
		int cnt1=0,cnt=0,v=1;
		for(int i=1;i<=n;i++){
			if (a[i]<v){
				cnt1=cnt1+(a[i]-1);
				continue;
			}
			cnt+=(a[i]-v);
			v++;
		}
		if (cnt>v) cout<<v<<endl;
		else if (cnt+cnt1>=v) cout<<v+1<<endl;
		else cout<<v<<endl;
	}
}
```

---

## 作者：Drifty (赞：0)

### Solution

显然，贪心地去想，我们肯定会考虑先把序列弄成形如 $1,1,\dots,1,2,2,\dots, 2, 3, 3, \dots, k$ 的形式。

因为取出来的花只有一堆，最多对答案的影响也只有 $1$，因此先尽可能的从一开始堆积的方案一定不劣。

我们把原数组从小到大排序统计一个序列 $b$，$b_i$ 即为 $1,1,\dots,1,2,2,\dots, 2, 3, 3, \dots, k$ 对于每一个 $i$ 最大可能的值。那么在这个情况下，取出来的那一堆花的数量即为 $\sum_{i = 1} ^ n(a_i-b_i)$。我们注意到我们只要保证 $b_k$ 不变且 $b_{i+1} - b_{i} <2$，那么原来花堆产生的贡献不变，但是又可以取出更多的花。具体的，我们发现最少可以取成 $1, 1, 1, \dots, 1, 2, 3, \dots,b_k$ 的形式，我们记为 $c$。取出来的那堆花的数量我们记为 $p$。那么有 $\sum_{i = 1} ^ n(a_i-b_i)\le p\le \sum_{i = 1}^n(b_i-c_i)$。我们发现如果 $\exist p=b_k+1$ 那么答案为 $b_k + 2$，否则即为 $b_k + 1$。


### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int N = 1e5 + 3;
int T;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> T;
	for (int n; T --;) {
		cin >> n;
		i64 p = 0, e = 0;
		int l = 1, f = 0;
		vector <int> a(n), b(n);
		for (int i = 0; i < n; i ++) cin >> a[i];
		sort (a.begin(), a.end());
		for (int i = 0; i < n; i ++) {
			if (a[i] >= l) p += (a[i] - l), l ++;
			b[i] = l - 1;
		}
		for (int i = 0; i + 1 < n; i ++) {
			if (b[i] == b[i + 1] && b[i] > 1) {
				b[i] --, e ++;
				if (b[i] == b[i - 1] && b[i] > 1) b[i - 1] --, e ++;
			}
		}
		if (l >= p && l <= p + e) cout << l + 1 << '\n';
		else cout << l << '\n';
	}
	return 0;
}
```

---

