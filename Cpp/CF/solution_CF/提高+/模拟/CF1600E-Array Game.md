# Array Game

## 题目描述

Alice 和 Bob 正在玩一个游戏。他们得到了一个长度为 $N$ 由整数组成的数组 $A$。

他们正在一起建立一个序列。在开始的时候，这个序列是空的。  
在一个回合中，玩家可以从数组的左边或右边移出一个数字，并将其添加到序列的右侧。  
规则是：他们所建立的序列必须是单调递增的。赢家就是是做出最后一步的玩家。  
Alice 是第一个玩的。假设他们都以最佳方式进行游戏的情况下，谁能赢得游戏？

## 样例 #1

### 输入

```
1
5```

### 输出

```
Alice```

## 样例 #2

### 输入

```
3
5 4 5```

### 输出

```
Alice```

## 样例 #3

### 输入

```
6
5 8 2 1 10 9```

### 输出

```
Bob```

# 题解

## 作者：Liuxizai (赞：14)

## Description

给定 $\{a_n\}$，Alice 和 Bob 正在构造一个新的序列，轮流从 $\{a_n\}$ 开头或末尾取出一个元素接在新序列的后面，需要保证这个新序列单调递增。

## Solution

我们取出 $\{a_n\}$ 最长的单调递增前缀，记作 $\{p_{c_1}\}$，以及最长的单调递减后缀，记作 $\{q_{c_2}\}$。

将 $\{q_{c_2}\}$ 翻转后，我们可以将原问题转换为，每次从 $\{p_{c_1}\}$ 或 $\{q_{c_2}\}$ 的开头取出元素构造一个新的单调递增序列。

先给出结论，当 $c_1,c_2$ 至少一者为奇数时，Alice 必胜。

下证明这一结论。

1. 若 $c_1,c_2$ 均为奇数，不妨设 $p_1\ge q_1$。

    接下来，Alice 只需在第一步时取走 $p_1$，接下来 $\{q_{c_2}\}$ 中的元素将永远不能被选取，不难发现必然是 Alice 取走最后一个元素。

    此时 Alice 必胜。

2. 若 $c_1,c_2$ 其一为奇数，不妨设 $c_1$ 为奇，$c_2$ 为偶。

    Alice 第一步仍然取走 $p_1$，接下来 Bob 可能能够从 $\{p_{c_1}\}$ 或 $\{q_{c_2}\}$ 的开头选择元素，注意到 $p_1$ 已被取走，此时两序列长度均为偶数，Bob 取数过后，Alice 只需从 Bob 上一步所选择的序列开头取走元素即可，显然 Alice 这一步必然合法。

    Bob 每次取数后，Alice 必然能够进行下一步操作，那么无数可选的局面只能发生在 Bob 取数时，故最后一个元素也由 Alice 取走。

    此时 Alice 必胜。

3. 若 $c_1,c_2$ 均为偶数。

    Alice 第一步无论取走哪个元素，Bob 均可采用 $\mathrm{case\ 2}$ 中的必胜策略，于是 Bob 必胜。
    
    此时 Alice 必败。

## Code

仅给出核心代码。

```cpp
namespace Main{
    int n, a[N];
    void Main(){
        input(n);
        for(ri i = 0; i < n; i++) input(a[i]);
        int i = 0, j = n - 1;
        while(i < n && a[i] < a[i+1]) i++;
        while(j > 0 && a[j] < a[j-1]) j--;
        puts((i+1)&1 || (n-j)&1 ? "Alice" : "Bob");
        return;
    }
} // namespace
```

---

## 作者：404_notfound (赞：3)

一道博弈论诈骗题。

首先对于一个序列，只有左边连续上升段和右边连续上升段是有用的。

然后我们比较序列最左端和最右端的大小，并假定最左端元素更大（毕竟翻转序列不影响答案）

- 如果此时左端上升序列长度为奇数

则先手选择会左端，那么后手根据规则也只能在左端继续选下去。先手会选完最后一个且必胜。

- 如果此时左端上升序列长度为偶数

那么最左端是一个先手必败的状态，也就是说无论谁拿走左边第一个元素，谁就必输  ~~狗都不选~~

所以先手只能选择最右端的元素，后手为了自己赢也不会去选择左边，两个人的胜负取决于右边上升序列长度的奇偶。

- 结论

如果两边上升序列长度有至少一个为奇数，则先手胜。否则后手胜。

code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<cstring>
using namespace std;
const int inf=0x7fffffff;
typedef long long ll;
#define maxn 200009
int a[maxn],n; 
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int len1=0,len2=0;
	a[0]=a[n+1]=-1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>a[i-1])len1++;
		else break;
	}
	for(int i=n;i>=1;i--)
	{
		if(a[i]>a[i+1])len2++;
		else break;
	}
	if(len1&1||len2&1)printf("Alice\n");
	else printf("Bob\n");
	return 0;
}

```


---

## 作者：Priori_Incantatem (赞：3)

[CF题目链接](https://codeforces.ml/problemset/problem/1600/E)  
[洛谷链接](https://www.luogu.com.cn/problem/CF1600E)

一道不太正经的博弈论题，可用递归解决

#### 题意
给出一个序列，Alice与 Bob 轮流从序列两端取数，并把取出的数按顺序组成一个序列，需要保持此序列严格递增，最后不能取数的人败，求先手是否有必胜策略

------

定义序列 $a,b$ 分别为原序列 $w$ 的最长递增前缀和最长递减后缀，则第一个被取走的数为 $a$ 或 $b$ 的首元素

- 首先，存在为空的序列，那么如果非空序列长度为奇数**先手必胜**，否则**先手必败**

- 如果首元素较大的序列的长度为奇数，那么**先手必胜**。  
因为先手取了第一个数后，后手就只能在该序列取数。  
同理，如果两个首元素同样大，那么只要其中一个序列长度为奇数，则仍旧**先手必胜**。

- 否则，为了不做必败决策，两人会一直取首元素较小的序列，直到该序列首元素不再是最小

我们发现，接下来需要解决的问题是当前问题的子问题。那么我们只需要处理一下先手的变化情况，并递归求解即可

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<deque>
using namespace std;
const int Maxn=2e5+10;
deque <int> a[2];
int w[Maxn];
int n;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int work()
{
	for(int i=0;i<2;++i)
	if(!a[i].size())return (a[i^1].size() & 1)^1;
	if(a[0][0]==a[1][0])return ((a[0].size()&1)|(a[1].size()&1))^1;
	int p=0;
	if(a[1][0]>a[0][0])p=1;
	if(a[p].size() & 1)return 0;
	int cnt=0;
	while(a[p^1].size() && a[p^1][0]<a[p][0])
	a[p^1].pop_front(),++cnt;
	return work()^(cnt & 1);
}
int main()
{
	// freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;++i)
	w[i]=read();
	for(int i=1;i<=n;++i)
	{
		a[0].push_back(w[i]);
		if(w[i]>=w[i+1])break;
	}
	for(int i=n;i;--i)
	{
		a[1].push_back(w[i]);
		if(w[i]>=w[i-1])break;
	}
	if(!work())puts("Alice");
	else puts("Bob");
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

## 思路

神仙 game 题。

我们发现能取到的数一定要么是以 $a_1$ 开头的最长连续上升的序列，要么是以 $a_n$ 结尾的最长连续下降序列。

我们考虑把这两个序列 $p,q$ 拎出来。我们把 $q$ 翻转。原题可以变成：

给定两个单调上升的序列 $p,q$，每次可以取出序列的头（要求必须大于之前取的），问先手赢还是后手赢。

考虑进行分讨：

1. $p,q$ 均为奇数：直接取走开头较大的那个，这样另外一个序列就永远无法取了，所以只有一个长度为奇数的序列可以取，显然先手必胜。

2. $p$ 或 $q$ 为奇数，另一个为偶数：直接取走奇数的那个的开头，则两个序列都是偶数长度。这样 Bob 无论在哪个序列取完，Alice 一定能在他取的序列里，取走下一个元素。因此 Alice 永远不可能无路可走，一定是 Bob 先没有可以取的。所以先手必胜。

3. $p$ 和 $q$ 都是偶数：先手怎么取，都会转化成 2 的情况，此时后手必胜。

所以，如果 $p,q$ 中只要有一个为奇数，则先手必胜；否则后手必胜。扫一遍，贪心的求出 $p,q$ 这两个序列即可。复杂度 $O(n)$。

代码极其好写就先不给了。

---

## 作者：KAMIYA_KINA (赞：1)

## Tag

贪心，博弈论。

## Description

给定一个长度为 $n$ 的 $\{a_n\}$ 的序列，每一步可以选取序列最右边或者最左边的值，然后放到一个严格递增的新的序列的后面，胜利当且仅当这个人放的是最后一个数。Alice 先手，请问 Alice 和 Bob 谁可以赢。

$\texttt{data range:} n\leq 2\times 10^5$.

## Solution

可能题面有点不清晰，自己看英文理解一下吧……

我们先考虑一个局面下，当前先手的人如何必胜。

我考虑最左边或者最右边更大的那个，然后判断一下如果更大的那个的递增序列如果是奇数的话就直接选，明显可以获胜，否则的话我就选小的那一个，然后继续判断另一个人在下一个局面会不会获胜。

这样的话时间复杂度是 $O(n)$ 的，双指针扫一下就可以了，我用的是 dfs 实现的。

## Code

```cpp
int n, a[N]; 

inline void input() {
    n = rd;
    for(int i = 1; i <= n; i++) a[i] = rd;
    return ;
}


bool dfs(const int op, int lef ,int rig, int x, int y) {
    if(lef == rig) return op;
    if(a[lef] >= a[rig] && (x & 1)) return op;
    if(a[rig] >= a[lef] && (y & 1)) return op;
    if(a[lef] < a[rig]) return dfs(op ^ 1, lef + 1, rig, x - 1, y);
    if(a[rig] < a[lef]) return dfs(op ^ 1, lef, rig - 1, x, y - 1);
    if(a[lef] == a[rig]) return op ^ 1;
}


inline void work() {
    int lef = 1, rig = n, lt = 1, rt = 1;
    while(a[lef] < a[lef + 1] && lef < n) lt++, lef++;
    while(a[rig] < a[rig - 1] && rig > 1) rt++, rig--;
    puts(dfs(0, 1, n, lt, rt) ? "Bob" : "Alice");
    return ;
}


inline void solve() {
    input();
    work();
    return ;
}
```



---

## 作者：Jerrlee✅ (赞：0)

## 提示
既然有两个情况，就分类看吧。
## 思路
我们有两个情况：

- 移动中的玩家可以从阵列的左端或右端获取数字。

- 移动中的玩家只能从阵列的一端获取数字。

让我们首先解决情况 $2$：

由于只能获取数组一端的数字，因此数组的另一端是永久的此路不通。这意味着直到游戏结束，玩家只能从游戏的一端取数字阵列。我们可以预先计算增加序列的长度（从左到右）以根据每个数字的奇偶性和递增序列的长度，我们可以确定是谁赢得比赛。

情况 $1$：

假设数组是 `A, C, …… , D, B`，再假设 $A \leq B$。如果正在移动的玩家以 `B` 为例，这意味着数组的左侧现在被阻塞，然后我们剩下的是情况 $2$。如果发生这种情况，我们已经知道结果。如果结果对现在上场的玩家有利，他赢了。否则，他应该采取行动，因为那样他至少有机会获胜。现在我们只剩下数组 `C, ……  ,D,B `，我们可以递归解决这个问题。

时间复杂度 $O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
void fun(int start,int end,vector <int> &a,int fst,int scd){
  if(start==end){
    if(fst==1) cout<<"Alice"; //fst 是 first 啊，不是 failed system tests(
    else cout<<"Bob";
    return;
  }
  if(a[start]==a[end]){
    int cnt=1,cnt1=1,i;
    for(i=start+1;i<=end;i++)
    if(a[i]>a[i-1]) cnt++;
    else break;
    for(i=end-1;i>=start;i--)
    if(a[i]>a[i+1]) cnt1++;
    else break;
    if(cnt%2==1||cnt1%2==1){
      if(fst==1) cout<<"Alice";
      else cout<<"Bob";
    }
    else{
      if(scd==1) cout<<"Alice";
      else cout<<"Bob";
    }
    return;
  }
  if(a[end]>a[start]){
    int cnt=1,i;
    for(i=end-1;i>=start;i--)
    if(a[i]>a[i+1]) cnt++;
    else break;
    if(cnt%2){
      if(fst==1) cout<<"Alice";
      else cout<<"Bob";
      return;
    }
    cnt=1;
    for(i=start+1;i<end;i++)
    if(a[i]<a[end]&&a[i]>a[i-1]) cnt++;
    else break;
    if(a[i]>=a[end]){
      if(cnt%2) fun(i,end,a,scd,fst);
      else fun(i,end,a,fst,scd);
      return;
    }
    else{
      if(cnt%2){
        if(fst==1) cout<<"Alice";
        else cout<<"Bob";
      }
      else{
        if(scd==1) cout<<"Alice";
        else cout<<"Bob";
      }
      return;
    }
  }
  int cnt=1;
  for(i=start+1;i<=end;i++)
  if(a[i]>a[i-1]) cnt++;
  else break;
  if(cnt%2){
    if(fst==1) cout<<"Alice";
    else cout<<"Bob";
    return;
  }
  cnt=1;
  for(i=end-1;i>start;i--)
  if(a[i]<a[start]&&a[i]>a[i+1]) cnt++;
  else break;
  if(a[i]>=a[start]){
    if(cnt%2) fun(start,i,a,scd,fst);
    else fun(start,i,a,fst,scd);
    return;
  }
  else{
    if(cnt%2){
      if(fst==1) cout<<"Alice";
      else cout<<"Bob";
    }
    else{
      if(scd==1) cout<<"Alice";
      else cout<<"Bob";
    }
    return;
  }
}
int main(){
  cin>>n;
  vector<int>a(n);
  for(int i=0;i<n;i++) cin>>a[i];
  fun(0,n-1,a,1,0); // 递归解决，比起别的有些复杂……
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/59666440)

[AC记录（CF）](http://codeforces.com/contest/1600/submission/131561066)

---

