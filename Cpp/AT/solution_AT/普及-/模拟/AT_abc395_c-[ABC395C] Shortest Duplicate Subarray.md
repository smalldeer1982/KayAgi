# [ABC395C] Shortest Duplicate Subarray

## 题目描述

给定一个正整数 $N$ 和一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\dots,A_N)$。

请判断 $A$ 中是否存在至少包含两个相同元素的非空连续子数组。若存在，请求出所有满足条件的子数组中最短的长度；若不存在，请输出 `-1`。

## 说明/提示

### 约束条件
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq 10^6$（$1 \leq i \leq N$）
- 输入均为整数

### 样例解释 1
子数组 $(3,9,5,3)$ 和 $(3,9,5,3,1)$ 满足条件。其中最短的子数组长度为 $4$。

### 样例解释 2
不存在符合条件的连续子数组。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 9 5 3 1```

### 输出

```
4```

## 样例 #2

### 输入

```
4
2 5 3 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
10
1 1 2 3 5 8 13 21 34 55```

### 输出

```
2```

# 题解

## 作者：Little_x_starTYJ (赞：14)

## 题目大意
找到一个最小区间 $[l, r]$，存在一个 $a_i(i \in [l, r])$ 能找到一个 $a_j(j \in [l, r])$ 满足 $a_i = a_j,i \neq j$。

如果不存在这个区间，输出 `-1`，否则输出最小区间长度。

## 解题思路
首先我们定义 $lst_k$ 为 $k$ 在 $a$ 中上一次出现位置。那对于每一个数 $a_i$，如果以它作为关键字找到一个最小的区间，一定是 $[lst_{a_i}, i]$，因为它们之间并没有出现任何一个数满足 $a_j = a_i(j \neq i)$。

那么我们就可以遍历数组，每次记录 $a_i$ 的出现位置，计算出区间长度并与答案取 $\min$ 即可。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010], lst[1000010];
int main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		lst[a[i]] = -1145141919;
	}
	int ans = 1e9;
	for (int i = 1; i <= n; i++) {
		if (i - lst[a[i]] + 1 <= ans) {
			ans = i - lst[a[i]] + 1;
		}
		lst[a[i]] = i;
	}
	if (ans > n) {
		cout << -1;
	} else {
		cout << ans;
	}
	return 0;
}
```

---

## 作者：Lovely_yhb (赞：4)

### 题意

求出序列中相隔最近的两个相同数字的距离。

### 思路

发现值域非常小，$A_i\le10^6$。所以可以直接开桶。

开一个数组 $pre_t$，表示 $t$ 这个数上一次出现的位置。如果当前数字出现过，就统计答案。$ans=\min(i-pre_{a_i}+1)$。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int lst[1000006],n,x,ans=0x3f3f3f3f;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		if(lst[x]) ans=min(ans,i-lst[x]+1);
		lst[x]=i;
	}
	cout<<(ans==0x3f3f3f3f?-1:ans);
	return 0;
}
```

---

## 作者：2011hym (赞：4)

## 题意简述

- 我们需要找到一个**最短**的连续子序列，其中至少有一个值出现两次或更多次。
- 如果序列中没有任何重复值，则输出 `-1`。

## 解题思路
### 算法选择：
   - 使用哈希表**记录**每个值最后一次出现的位置。
   - 遍历序列，对于每个元素 $A[i]$，检查它是否已经在哈希表中出现过。
     - 如果出现过，则计算当前子序列的长度 $ i - m_{A_i} + 1 $（$m$ 为**哈希表**），并更新**最短长度**。
     - 更新哈希表中 $A_i$ 的**最后**出现位置。


## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,A[200000];
int main(){
    cin>>N;
    for(int i=0;i<N;i++)cin>>A[i];
    unordered_map<int,int>m;
    int ans=INT_MAX;
    for(int i=0;i<N;i++){
        if(m.find(A[i])!=m.end()){
            ans=min(ans,i-m[A[i]]+1);
        }
        m[A[i]]=i;
    }
    if(ans==INT_MAX)cout<<-1;
    else cout<<ans;
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：$O(N)$，因为只需要遍历序列一次。
- **空间复杂度**：$O(N)$，用于存储哈希表。

---

## 作者：zzhengxi (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc395_c)

## 简化题意

找出给出的数组中的距离最近的两个**相同数**之间的距离。无相同数则输出 $-1$ 。

## 思路

关注数据范围，

> $1 \le A_i \le 10^6(1 \le i \le N) $

可以新建一个标记数组来存这个数**前一次出现的位置**以及这个数**是否出现过**。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[200010];
int v[1000010];//标记数组
int main(){
	int n,mi = INT_MAX;
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
		cin >> a[i];
	for(int i = 1 ; i <= n ; i ++)
		if(!v[a[i]])//如果这个数是之前还没有出现过
			v[a[i]] = i;//把位置记录到标记数组中
		else
			mi = min(mi,i - v[a[i]] + 1),v[a[i]] = i;
		//存储距离，更新标记数组
	if(mi == INT_MAX) cout << -1;
	else cout << mi;
	return 0;
}
``````

---

## 作者：Lyx8058 (赞：1)

## 题目描述：
求区间有重复数的最小区间长度。
## 思路：
写着写着，我们不难想到，这题跟滑动窗口似乎是差不多的。

那差在哪呢？

题目更简单了。

其实若要区间内有数重复，可以将重复的数置于队首和队尾。

我们可以使用一个 deque 来处理，首先将 $a_1$ 入桶，然后在 $a_2$ 至 $a_N$ 中依次枚举，每一次取桶长度与 $ans$ 的最小值，输出 $ans$ 。

大致思路就是这样的，具体实现看代码和注释理解一下。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans=1000000000,dis[1000001];//ans要往大了初始化 。 
deque<int>q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	q.push_back(a[1]);
	dis[a[1]]++;
	for(int i=1;i<=n;i++){
		q.push_back(a[i]);// a[i] 入队 
		dis[a[i]]++;// a[i] 个数 +1 
		if(dis[a[i]]>1){// a[i] 在队中重复了  
			while(q.front()!=a[i]){//队首不是 a[i]  
				dis[q.front()]--;// 队首的次数 -1 
				q.pop_front();// 队首出队  
			}
			ans=min(ans,int(q.size()));//更新、替换最小值  
		}
	}
	if(ans==1000000000) cout<<"-1\n";//不满足重复数字的条件  
	else cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：lee_0730 (赞：1)

# 题意：

给定一个序列 $A$，请你求出这个序列中**最短的**包含至少两个重复数字的区间**长度**，如果没有输出-1。

# 思路：

分析样例，我们不难发现：
最优解区间中必然是有且仅有两个重复数字，并且该区间的左右端点就是这两个数。

故我们可以遍历一遍这个序列，存储下来所有重复的数之间的距离，之后进行比较并选出最小距离，$N$ 范围为 $2 \times 10^5$，考虑用 **map** 实现。

# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
#define fastrd ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
map<int,pii>mp;
map<int,int>vis;
int n;
int main(){
	fastrd
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		if(vis[a]){
			if(mp[a].se-mp[a].fi+1>i-mp[a].se+1||vis[a]==1){//如果当前数字已经存在重复区间，进行比较
				mp[a]={mp[a].se,i};
			}
		}else{
			mp[a]={0,i};//存储当前数字位置，等待重复
		}
		vis[a]++;
	}
    int anss=1<<30;
    for(auto i:mp){
        int a=i.se.fi;
        int b=i.se.se;
        if(a==0){//如果当前数字在原序列中只存在一个，则跳过
            continue;
        }
        anss=min(anss,b-a+1);//比较区间长度
    }
    if(anss==1<<30){//如果ans没有被改变，说明原序列不存在相同元素,输出-1
        cout<<-1;
        return 0;
    }
    cout<<anss;
}
```

## 时间复杂度： $O(N \times \log{N})$

---

## 作者：Perfect_Youth (赞：1)

~~赛时吃三发罚时，我太唐。~~

### 题目思路：

既然题目要求序列最小，我们就可以把上一次 $a_i$ 出现的位置存下来，如果上一次存过，就直接用当前位置减以前位置加一就行。如果没有输出 $-1$。

代码如下：
```cpp
#include <bits/stdc++.h>
#define getchar()(p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1 , 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

using namespace std;

inline
int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ '0');
		ch = getchar();
	}
	return x * f;
}

const int N = 1e6 + 7;

int n, ans = 2e9, s[N];

int main() {
	n = read();
	for (int i = 1, x; i <= n; i++) {
		x = read();
		if (s[x]) ans = min(ans, i - s[x] + 1);
		s[x] = i;
	}
	if (ans == 2e9) ans = -1;
	printf ("%d", ans);
	return 0;
}
```

---

## 作者：ryf2011 (赞：1)

# 题目思路
由于 $A_i \le 10^6$，所以我们用一个结构体，存储每个数出现的次数。

顺序遍历数组，当一个数第一次出现时，记录它的位置。当一个数第二次出现时，由于我们记录了它第一次出现的位置，所以我们此时直接把当前位置减第一次出现的位置再加 $1$ 即可。

别忘了答案取最小值。

# 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int max_n=2e5+5;
const int max_v=1e6+5;
int n,a[max_n];
struct node{
	int cnt; //出现次数 
	int l; //第一次出现的位置 
} t[max_v]; 
int ans=max_n; //设初值 
int main(){
	//输入 
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	} 
	//计算 
	for(int i=1;i<=n;i++){
		t[a[i]].cnt++;
		if(t[a[i]].cnt>=2){ //出现 2 次，说明之前已出现过，且一定记录过第一次出现位置，相减即可 
			ans=min(ans,i-t[a[i]].l+1); //取最小值 
		}
		else{
			t[a[i]].l=i; //如果第一次出现，记录位置 
		}
	}
	if(ans==max_n){ //如果 ans 没有变化，说明没有数字出现过 2 次，即数字各不相同，输出 -1 
		printf("-1\n");
	}
	else{ //否则，输出最小值 
		printf("%d\n",ans);
	}
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：天使宝贝 (赞：1)

### 题目大意

有一个正整数 $n$ 和一个长度为 $n$ 的整数序列 $a = (a_1,a_2,\dots,a_n)$ 。

请判断 $a$ 是否存在一个非空的连续子数组，该子数组中的某个数在 $a$ 中多次重复出现。如果存在这样的子数组，求最短的子数组的长度。

### 思路&分析
观察到值域不大，我们直接开个桶记录每个数在数组 $a$ 中出现的位置，当一个数已经出现过时，我们不难发现，如果选后面该数出现的位置肯定不优，所以我们就先把它和上一次出现的位置之间的长度算出来，然后更新该数的最新位置，所有的答案中取个最小的就是答案。

### CODE
```cpp
#include <bits/stdc++.h>
#define ll long long
#define il inline
#define IOS ios::sync_with_stdio(false), cin.tie(0)
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define dep(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
constexpr int MAXN = 1e6 + 5;
int n, x, ans = 1e9, t[MAXN];
signed main() {
	IOS;
	cin >> n;
    rep(i, 1, n) {
        cin >> x;
        if (t[x]) ans = min(ans, i - t[x] + 1);
        t[x] = i;
    }
    cout << ((ans == 1e9) ? -1 : ans) << endl;
	return 0;
}
```

---

## 作者：cjx_AK (赞：1)

#### 题目
题目给你一个数组 $a$，让你求最小长度的连续子数组使得有数字至少出现过两次。

#### 思路
我们可以记录每个数字出现的位置，然后若这数字出现过，就记录一次答案，然后在这些答案中取最小值即可。（注意记录答案后记录的位置要更新）

#### code


```
#include<bits/stdc++.h>
using namespace std;
int T,a[500005],b[90000004],k[90000004],ans=1e9;
char s[501][501];
void solve(){
int n;
cin>>n;
for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(b[a[i]]){
			ans=min(ans,i-k[a[i]]+1);
			k[a[i]]=i;
		}else{
			k[a[i]]=i;
			b[a[i]]=1;
		}
	}
	if(ans==1e9){
		cout<<-1;
	}else cout<<ans<<endl;
}
signed main(){
	//cin>>T;
	T=1;
	while(T--){
solve();
	}
	return 0;
}

,
```

---

## 作者：_Star_Universe_ (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc395_c)
### 题目大意
给定一个正整数 $n$ 和一个长度为 $n$ 的整数序列 $a=\{a_1,a_2,\dots,a_N\}$，确定是否存在包含多次出现相同值的非空连续子序列 $a$。如果存在这样的子序列，则找到最短的子序列的长度。

### 解题思路
因为本题要求我们输出最小长度，所以定义一个 $ans$ 等于一个很大的值 `0x3f3f3f`。

理解了题意后我们不难发现符合条件的子序列首尾必定相同，用 $ind_{a_i}$ 表示 $a_i$ 的位置，如果遍历数组时出现记录过的值，在 $ans$ 和 $i-ind_{a_i}+1$ 中取最小值，结束时判断 $ans$ 是否改变，是则输出新值，否则输出 `-1`。

观察到 [这篇博客园题解](https://www.cnblogs.com/Sinktank/p/18745531) 中提供了针对上述思路进行简化的代码，不需要定义 $a$ 数组以及判断当前数字 $a_i$ 是否出现过，直接在 for 循环中输入 $a$，然后比较 $ans$ 和 $i-ind_a+1$ 取更小值，此做法明显降低了代码的空间复杂度。

我个人认为两种做法的本质是相同的，只是输入和判断略有差异，我们应选择自己理解的方式。[代码](https://www.luogu.me/paste/xxi41qev#)。

---

## 作者：linch (赞：0)

## Problem
求出最小的连续子序列长度，使得其中含有相同的整数。无解输出 `-1`。

## Solution
对于序列中每个数字 $x$，记录其最后一次出现的位置 $a_x$，若的序列中**在此之后**的数 $A_i=x(i>a_x)$，那么$[a_x,i]$ 一定是符合要求的序列，长度为 $i-a_x+1$。取所有合法序列长度的最小值即可。

时间复杂度 $O(n)$，可以通过本题。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
int n,a[maxn],ans=maxn;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(a[x]) ans=min(ans,i-a[x]+1);
		a[x]=i;
	}
	if(ans==maxn) cout<<"-1\n";
	else cout<<ans<<"\n";
	return 0;
}
```
[AC record](https://atcoder.jp/contests/abc395/submissions/63324108)

---

## 作者：Jayfeather2012 (赞：0)

比都比了，就写一发吧。
## 思路
双指针~~  
~~这题很像双指针，所以用双指针~~  
观察题目，可以发现：当一个以 $l$ 为开头的有重复值的最短连续子序列的结尾为 $r$，则以 $l+1$ 为开头的有重复值的最短连续子序列的结尾至少为 $r$。由此很容易看出此题可以用双指针。  
我们从 $1$ 至 $n$ 枚举所有 $l$，对于每个 $l$，寻找以 $l$ 为开头的有重复值的最短连续子序列的结尾 $r$，并将所有序列的长度取最小值输出。如果不存在以 $l$ 为开头的有重复值的连续子序列，就不参与取最小值。  
具体细节看代码吧！
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pp pair<int,int>
using namespace std;
int n,ans,a[2000005],b[2000005];//b数组标记每个数是否出现过 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	ans=n+1;//ans设最大值 
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int l=1,r=2;l<=n;++l){
		b[a[l]]=1;//标记a[l]这个数 
		while(!b[a[r]]&&r<=n||r<=l){
			b[a[r]]=1;//标记a[r] 
			++r;
		}
		//寻找以l为开头的有重复值的最短连续子序列的结尾r
		if(b[a[r]])ans=min(r-l+1,ans);
		//如果存在以l为开头的有重复值的最短连续子序列，就取最小值 
		b[a[l]]=0;//去掉a[l]这个数 
	}
	if(ans==n+1)cout<<-1<<"\n";
	//如果不存在有重复值的连续子序列，输出-1 
	else cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：ny_ShuaiQideWo (赞：0)

## 题目大意
找到长度最短且包含重复的子数组

## 分析
可以看到 $A_i$ 的范围是小于等于 $10^6$ 的，考虑开一个数组 $t$ 存 $i$ 上一次出现的位置。具体思路看代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1e9;//ans初始化要大一点
int t[1000005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL),cout.tie(NULL);
    cin>>n;
    for(int i=1;i<=n;i++){
    	int x;
    	cin>>x;
    	if(t[x]) ans=min(ans,i-t[x]+1);//用这个位置减上一个得到以x开头x结尾的长度
    	t[x]=i;//更新t[i]
	}
    if(ans==1e9) cout<<"-1\n";//可能没有重复
    else cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Manchester_City_FC (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc395_c)

[AtCoder 题目传送门](https://atcoder.jp/contests/abc395/tasks/abc395_c)

### 题目大意
给你一个正整数 $N$ 和一个长度为 $N$ 的整数序列 $A = (A_1,A_2,\dots,A_N)$。

确定是否存在一个非空且连续的子数组，满足其中有重复的值，并且该值在数组 $A$ 中出现多次。如果这样的子数组存在，找出最短的子数组长度。

数据范围 $1 \le N \le 2 \times 10^5$。

### 解题思路
由于我们找到的子数组中必须包含两个相同的数，所以我们只需要找到数组中任意两个相同数值的最短距离。

可以通过遍历数组并记录每个数最后一次出现的位置，计算相同数字出现的区间长度，从而得到最短满足“存在重复值”的连续子数组的长度。如果没有重复的数字，则输出 `-1`。

时间复杂度 $\mathcal O(n)$，可以通过本题。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1,inf=INT_MAX;
int n,a[N],l[N],k=inf;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    memset(l,-1,sizeof(l));
    for(int i=1;i<=n;i++) {
        int t=a[i];
        if(l[t]!=-1) k=min(k,i-l[t]+1);
        l[t]=i;
    }
    if(k==inf) cout<<-1;
    else cout<<k;
}
```

---

## 作者：da_ke (赞：0)

对于以第 $i$ 个结尾的子序列，其开头必然在「与 $A_i$ 相同的最后一个数」之前。故以第 $i$ 个结尾最优情况必然是开头就是「与 $A_i$ 相同的最后一个数」。对所有情况取最优。

对于「与 $A_i$ 相同的最后一个数」可以使用离散化维护。

如果直接使用数组离散化，时间复杂度 $O(N)$。

[示范代码](https://atcoder.jp/contests/abc395/submissions/63284358)

```cpp
#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;

int main()
{
    int N;
    cin>>N;
    map<int,int> mp;
    int ans=N+1;
    rep(i,1,N)
    {
        int t; cin>>t;
        if(mp[t]) ans=min(ans,i-mp[t]+1);
        mp[t]=i;
    }
    cout<<((ans==N+1)?-1:ans)<<endl;
}
```

建议评上位红或下位橙（请不要在评论区辱骂）。

---

## 作者：fanjiayu666 (赞：0)

### 评价
灰常简单。
### 方法

主要意思就是从 $A$ 中截一个最短的连续字串，使得这个段最短。

那分析完题目，发现极其简单，只需使一个段内只有两个重复的，一定是以目前开头时的最短的，所以只要记录每个数字上一次的位置，再维护最小值即可。

即对于 $A_i$，他的最小答案是：$i-mp_{A_i}+1$ （$mp$ 记录的是上一次出现的位置。）。

code:

(主代码)
```cpp
for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!mp[a[i]]){
            mp[a[i]]=i;
            continue;
        }
        ans=min(ans,i-mp[a[i]]+1);//维护答案。
        mp[a[i]]=i;//更新上次出现位置。
    }
```

### 总结

没什么好说的。

---

## 作者：zaolong (赞：0)

## 题目大意

给定一个正整数 $n$ 和一个长度为 $n$ 的整数数列 $a$。

是否存在一个 $a$ 的非空子数组，使得该数组存在重复值。如果存在这样的子数组，则查找此类子数组中最短的子数组的长度。

## 思路

显然满足条件的最短的子数组，首尾元素必须相同。如果存在首尾不同但满足条件的子数组可以通过删除首尾两边的元素使得它成为首尾元素相同的且更短的子数组。\
因此需要一个数组 $bj$ 来记录 $a_i$ 前一次出现的位置。如果找到相同的就取 $ans=\min(ans,i-bj_{a_i}+1)$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1e9,a[1000005],bj[1000005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(bj[a[i]]!=0){
			ans=min(ans,i-bj[a[i]]+1);
		}
		bj[a[i]]=i;
	}
	if(ans!=1e9) cout<<ans;
	else cout<<-1;
	return 0;
}
```

---

## 作者：Jerry_zpl (赞：0)

这题很水。
#### 问题陈述
给你一个正整数 $N$ 和一个长度为 $N$ 的整数序列 $A$。请判断 $A$ 是否存在一个非空（连续）子数组，它有一个重复值，在 $A$ 中出现多次。如果存在这样的子数组，求最短的子数组的长度。
#### 思路：
- 我们可以定义一个数组 $vis$，用来标记 $a_i$ 的位置。
- 当循环到 $i$ 时，若 $vis_{a_i}=1$ 则 $a_i$ 之前出现过，符合题目中所说的数组，用变量 $mini$ 求最短长度。
- 为啥 $a_i$ 出现了两次就比较长度呢？因为题目让我们求最短的子数组的长度。所以出现了两次就符合条件了，没必要再看第三次出现的位置。
- 如果 $vis_{a_i}=0$，那么标记一下 $a_i$ 出现的位置 $i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int a[maxn];
int vis[maxn];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int mini=INT_MAX;
	for(int i=1;i<=n;i++){
		if(vis[a[i]]){
			mini=min(mini,i-vis[a[i]]+1);
		}
		vis[a[i]]=i;
	}
	if(mini==INT_MAX) mini=-1;
	cout<<mini<<"\n";
	return 0;
}
```

---

## 作者：yyycj (赞：0)

## [题目传送门](https://atcoder.jp/contests/abc395/tasks/abc395_c)

## 题目简述
给你一个数列 $A$，求这个序列中长度最小的连续的一段子序列，且这个子序列至少包含一个重复元素；如果没有这样的子序列，输出 $-1$。

## 主要思路
要求长度最小，那么只需要将重复元素放在子序列的两端，求出每个这种序列的长度，取最小值即为长度最小。

所以可以创建一个长度为 $10^{6}$ 的一维数组 $idx$，表示在 $A_{1} \sim A_{i}$ 中，对于每个 $j \in [1,n]$，第一次出现 $A_{j}$ 的下标。当 $idx_{A_{i}}$ 已经记录过了下标，就说明此时满足了重复元素为子序列两端的条件，答案与 $A_{i} - idx_{A_{i}} + 1$ 取最小值。

一开始可以将答案设定为一个大于 $10^{6}$ 的值，就可以保证不会与真实答案混淆。最后输出答案时，如果答案还为这个值，则输出 $-1$。

## AC Code
```cpp
#include<map>
#include<set>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;

namespace IO {
	#ifdef ONLINE_JUDGE
	#define getchar getchar_unlocked
	#endif
	#define pc putchar
	#define gc getchar
	template<typename T> void read(T &x) { int f = 1; x = 0; char ch = gc(); while (!isdigit(ch)) { if (ch == '-')f = -1; ch = gc(); }while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = gc(); }x *= f; }
	template<typename T, typename ...Args> void read(T &x, Args &...args) { read(x); read(args...); }
	template<typename T> void print(T x) { if (x < 0) { pc('-'); x = -x; }if (x > 9) { print(x / 10); }pc(char(x % 10 + 48)); }
	template<typename T, typename ...Args> void print(T &x, Args &...args) { print(x); pc(' '); print(args...); }
	inline void readstr(string& x) { x.clear(); char ch = gc(); while (isspace(ch)) ch = gc(); while (!isspace(ch) && ch != EOF) { x.push_back(ch); ch = gc(); } }
	inline void printstr(char* x) { for (int i = 0; i < (int)strlen(x); i++) pc(x[i]); }
	inline void printstr(string& x) { for (auto i = x.begin(); i != x.end(); i++) pc(*i); }
};
using namespace IO;

#define OUT 0
#define MAMBA return
typedef long long ll;
typedef long double db;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
int man();int main(){MAMBA man();}
inline int _abs(int a) { if (a < 0) return -a; return a; }
inline int _pow(int a, int b) { int x = 1, y = a; while(b > 0) {if (b & 1) x *= y; y *= y; b >>= 1; } return x; }
// ----------------------------

// ----------------------------
int nums[N];
// ----------------------------


int man() {
	int n, a, ans = INF;
	read(n);
	// ----------------------------
	for (int i = 1; i <= n; i++) {
		read(a);
		if (nums[a] == 0) nums[a] = i;
		else ans = min(ans, i - nums[a] + 1);
	}
	// ----------------------------
	if (ans == INF) print(-1);
	else print(ans);
	MAMBA OUT;
}
/*
				 .-~~~~~~~~~-._       _.-~~~~~~~~~-.
			 __.'              ~.   .~              `.__
		   .'//   A    C    之   \./  之    真    理  \`.
		 .'//                     |                     \`.
	   .'// .-~"""""""~~~~-._     |     _,-~~~~"""""""~-. \`.
	 .'//.-"                 `-.  |  .-'                 "-.\`.
   .'//______.============-..   \ | /   ..-============.______\`.
 .'______________________________\|/______________________________`.
*/
```

---

## 作者：YBJ1006 (赞：0)

开一个桶记录之前离自己最近的且和自己相同的位置，更新答案即可。

**赛时代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int N = 1e6 + 10;

int a[N], t[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int ans = 1e9;
    for (int i = 1; i <= n; i++)
    {
        if (t[a[i]] != 0)
        {
            ans = min(ans, i - t[a[i]] + 1);
        }
        t[a[i]] = i;
    }
    if (ans == 1e9)
    {
        cout << -1; return 0;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

这题还是挺好写的。但不知道为什么我挂了两发。

记 $n$ 为数组长度，另开一个数组记录找到的最小值。

首先考虑什么情况无解。就是当我循环下来，最小的数组没有更新的情况下，这就是无解，所以返回 $-1$。这种情况好写：

```cpp
return minn == INT_MAX ? -1 : minn;
```

然后考虑使用 `unordered_map` 记录每一次最后出现的位置。循环遍历从 $0 \sim n - 1$，当每一次情况出现时，更新最小。

每一次操作完之后，记录最后一次出现的位置即可。

### 代码实现

```cpp
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>

#define unmap unordered_map
#define unset unordered_set
#define muset multiset
#define ll long long
#define unint unsigned int
#define ull unsigned ll
#define please return
#define AC 0
#define il inline
#define cst const
#define db double
#define ld long db
#define pii pair<int,int>
#define pll pair<ll,ll>

#define str string


#define int long long

using namespace std;

cst ll INF = 9223372036854775807;
cst int inf = 2147483647;
cst int xinf = 0x3f3f3f3f;
cst ll XINF = 0x3f3f3f3f3f3f3f3fll;
cst db pi = acos (-1.0), eps = 1e-12;

cst int MAXN = 50 + 10;
cst int mod = 11;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define repr(i, a, b) for (int i = a; i >= b; i--)

il int _abs (int a) { if (a < 0) return -a; return a; }
il int _pow (int a, int b) { int x = 1, y = a; while(b > 0) {if (b & 1) x *= y; y *= y; b >>= 1; } return x; }

int read () { int sum = 0, f = 1; char ch; ch = getchar (); while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar ();} while (ch >= '0' && ch <= '9') {  sum = sum * 10 + ch - '0'; ch = getchar ();} return sum * f;}
void print (int x) { if (x < 0) { putchar ('-'); x = -x;} if (x > 9) print (x / 10); putchar (x % 10 + '0'); return ;}

int todo (vector <int>& A) {
    int n = A.size(), minn = INT_MAX;
    unordered_map <int, int> L;

    rep(i, 0, n - 1) {
        if (L.find (A[i]) != L.end ()) {
            
            minn = min (minn, i - L[A[i]] + 1);
        }
        L[A[i]] = i;
    }

    return minn == INT_MAX ? -1 : minn;
}

// ------------------------------
signed main () {
    int N;
    cin >> N;
    vector <int> A (N);
    rep(i, 0, N - 1) cin >> A[i];
    
    
    cout << todo (A) << endl;
    
	please AC;
}
```

---

## 作者：hjyowl (赞：0)

### 简化题意

给定一个序列，求以两个相同的数为端点的序列最长能有多长。

### 思路

我们可以统计每个数 $x$ 的第一次出现，然后我们用当前的 $i$ 减掉 $x$ 上一次出现的位置加一得到区间长度，然后求出最大值即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2000010;
int n,m;
int a[N];
map<int,int>lst;
string s;
bool debug = 0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	int res = 1e9;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
		if (lst[a[i]] == 0){
			lst[a[i]] = i;
		}
		else{
			res = min(res,i - lst[a[i]]);
		}
	}
	if (res == 1e9){
		cout << -1;
		return 0;
	}
	cout << res + 1;
	return 0;
}
```

---

