# Zabuton

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf17-final/tasks/cf17_final_d

ある年のCODE FESTIVALの本戦には $ N $ 人の参加者が集まりました。 参加者 $ i $ は身長が $ H_i $ で力が $ P_i $ です。

りんごさんは参加者に座布団を積むゲームをしてもらおうとしています。

参加者は好きな順番で並び、$ 1 $ 人ずつ座布団を $ 1 $ 箇所に積んでいきます。 はじめ、座布団は $ 1 $ 枚も積まれていません。 参加者 $ i $ は、自分の番が回ってきた時にすでに積まれた座布団が $ H_i $ 枚以下の場合はちょうど $ P_i $ 枚の座布団を積みます。そうでない場合は諦めて $ 1 $ 枚も積みません。

りんごさんはできるだけ多くの参加者に座布団を積んで欲しいと思っています。 参加者の並び順を工夫することによって、最大で何人の参加者に座布団を積んでもらうことができるでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 0\ \leq\ H_i\ \leq\ 10^9 $
- $ 1\ \leq\ P_i\ \leq\ 10^9 $

### Sample Explanation 1

入力の通りの順に参加者が並ぶと、$ 1,3 $ 番目の参加者が座布団を積むことができます。 また、$ 3 $ 人全員が座布団を積めるような並び順は存在しないため、答えは $ 2 $ 人となります。

### Sample Explanation 2

$ 2 $ 番、$ 3 $ 番、$ 1 $ 番の順で参加者が並ぶと、全員が座布団を積むことができます。

## 样例 #1

### 输入

```
3
0 2
1 3
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3
2 4
3 1
4 1```

### 输出

```
3```

## 样例 #3

### 输入

```
10
1 3
8 4
8 3
9 1
6 4
2 3
4 2
9 2
8 3
0 1```

### 输出

```
5```

# 题解

## 作者：无名之雾 (赞：4)

本题目的严格加强版被伟大的 [rprp](https://www.luogu.com.cn/user/139012) 出在了进阶计划后期的专题考试中。

就此我在考场上想出了一种 $O(n\log n)$ 的爆标算法。

## 思路

我们考虑两个人向砖堆里面加砖的过程。

设当前砖堆块数为 $W$，以及 $(H_1,P_1)$ 和 $(H_2,P_2)$。

- 对于 $H_1$ 在前，接完这俩任务，$W\le H_2-P_1$。
- 对于 $H_2$ 在前，接完这俩任务，$W\le H_1-P_2$。

如果要求 $H_2$ 在前更优秀，有 $H_1+P_1\le H_2+P_2$。

所以不难想到把按照 $H_i+P_i$ 排序。

然后按照反悔贪心做即可。

维护一个堆，不断按顺序向堆里压入元素，如果无法操作就替换做了任务里面 $P_i$ 最大的。

## 证明

1. 如果所得贡献相同，那么所花时间越少一定不劣。

2. 若已确定所有人都往砖堆里加砖，那按 $H_i+P_i$ 从小到大排序一定不劣。


因为按 $H_i+P_i$ 从小到大排序来扔砖头一定不劣。

考虑 $i$ 的时候，若现在他不扔，以后就都不能扔了，但如果现在他扔了，以后可以将他取消，所以若扔，相较于之前的决策不劣的话就可以直接扔。

如果此时扔了，根据上一段可以知道直接扔了一定是比之前的决策优的。

如果此时之扔不了，由于每次扔砖头的贡献一样。

如果可以选择之前的一个取消来扔这个，那贡献相同，我们就看有没有时间更长的来取消，

这样就可以使总时间更短，所以更优。

## 代码

```cpp
// LUOGU_RID: 174239124
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void write(int x){
    if(x==0){putchar('0');return;}
	int len=0,k1=x,c[10005];
	if(k1<0)k1=-k1,putchar('-');
	while(k1)c[len++]=k1%10+'0',k1/=10;
	while(len--)putchar(c[len]);
}
const int N=2e5+5;
struct node{
    int v1,v2;
}a[N];
bool cmp(node a,node b){
    return a.v2<b.v2;
}
priority_queue<int>q; 
signed main(){
//	freopen("big_gift.in","r",stdin);
    int n=read(),ans=0,sum=0;
    for(int i=1;i<=n;i++)a[i].v2=read(),a[i].v1=read(),a[i].v2+=a[i].v1;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        sum+=a[i].v1,q.push(a[i].v1);
        if(sum<=a[i].v2)ans++;
        else sum-=q.top(),q.pop();
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：wangziyue_AK (赞：3)

## 提供一些关于排序方式和反悔贪心的证明
### 性质及证明：
对于可行的一个答案序列，使此序列中的每一个人都可以加砖头，可以将其按照 $H_i+P_i$ 排序，其一定合法。考虑证明：假设答案序列中的一组 $i<j$ 若满足 $H_i+P_i>H_j+P_j$，则按照此排序方式需要交换，其交换后必定合法：把 $i$ 以前加入的石子数计为 $K$，则必有 $K+P_i\leq H_j$ 和 $K\leq H_i$，交换后 $K\leq H_j$ 显然成立，而因为 $H_i+P_i>H_j+P_j$ 所以 $H_i-P_j>H_j-P_i$,那么 $K\leq H_i-P_j$ 即 $K+P_j\leq H_i$。综上，交换 $i$ 和 $j$ 后 $i$ 和 $j$ 仍然可以加砖头，此时交换 $i$ 和 $j$ 合法。
### $O(n^2)$ 做法
先按照 $H_i+P_i$ 排序，然后简单 DP 一下，$f_{i,j}$ 表示选到第 $i$ 个人，加砖头了 $j$ 人次的最小总砖数。
### $O(n\log n)$ 做法
我在模拟赛中见到的此题数据 $n\leq 100000$，上述做法无法通过，需要使用反悔贪心。
可以发现，这可以用反悔贪心维护一个答案序列，此序列中的每一个人都可以加砖头，且序列长度时刻为当前答案。当遍历到一个 $i$ 时，若可以加砖则必定加砖，否则删去 $P$ 最大的人(包括 $i$)，可以证明此时一定能把 $i$ 加入，因为考虑答案序列的最后一位 $j$，它之前加入的不超过 $H_j$，则到 $i$ 时只要 $H_j+P_j\leq H_i$ 即可，若不满足，减去 $P_{max}$ 相当于右边变为 $H_i+P_{max}$,此时有 $H_j+P_j\leq H_i+P_i\leq H_i+P_{max}$，所以删去一个后一定能把 $i$ 加入，则反悔成立。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
int n,ans;
ll sum=0;
struct xx{
	ll x;int y;
}a[N];
inline bool cmp(xx ax,xx ay){
	return ax.x+ax.y<ay.x+ay.y;
}
priority_queue<int> q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%d",&a[i].x,&a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		q.push(a[i].y);
		if(sum<=a[i].x) ans++;
		else sum-=q.top(),q.pop();
		sum+=a[i].y;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：star_fish (赞：2)

## 前言

反悔贪心板子题，数据比[P4053 [JSOI2007] 建筑抢修](https://www.luogu.com.cn/problem/P4053)还要弱。这类题什么时候定一个标准难度。


---


本题与道路抢修的的思路以及解法基本一致。先按照所有人的限制，也就本题中的 $h_i+l_i$ 进行从小到大的排序，然后遍历数组，尽量往砖堆里加砖，若无法继续无脑加砖，则弹出砖堆代价最大的砖。

进行贪心正确性的证明。遇到无法继续加砖的情况时，考虑能否用这块砖平替之前的砖，可以使得答案不变的情况下目前的砖头总数更小，以尽量满足后面工人的需求。

我们使用一个大根堆维护砖堆中价值最大的那坨砖。进行能否平替的判断时，将当前砖的价值与堆顶进行比较。若价值比堆顶更小，则弹出堆顶，插入当前砖。

可以证明在上述情况下，弹出后一定可以插入当前砖。变化之前，$sum$ 值不严格小于上一个插入的砖的限制。平替之后，$sum$ 值一定是减少了的。而因为我们对每一坨砖进行了限制从小到的排序，因此显然平替后的 $sum$ 值小于当前砖的限制，可以插入当前砖。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 5050
struct node{int x,y;}a[N];
bool cmp(node a,node b){return a.x+a.y<b.x+b.y;}
priority_queue<int> q;
int n,sum=0,ans,t;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	while(q.size()) q.pop();
	sum=0,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(sum<=a[i].x) q.push(a[i].y),sum+=a[i].y,ans++;
		else if(a[i].y<q.top()) sum+=a[i].y-q.top(),q.pop(),q.push(a[i].y);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Reunite (赞：2)

好吧我来补一个有一些道理的题解。

如果我们拥有一个顺序 $p_i$，使得按照 $p_i$ 顺序决策每一个任是否加入，且能保证最优，那么是有一个容易的 $nV$ 背包 dp 的。这里的顺序决策指的是前面任何一个人调到后面决策不可能导致更优。

关键在确定顺序 $p_i$，考虑任意两个人 $i,j$ 的顺序，如果在任意 $h$ 的情况下，先 $i$ 后 $j$ 或先 $j$ 后 $i$ 都不会更优，则两人之间不存在强制偏序关系，不管，这两个人的顺序无所谓。剩下的就是有强制偏序关系的了。不妨设 $j$ 在前更优，则偏序的形成是因为：存在一个 $h$，使得先 $j$ 后 $i$ 能够加入两个人，但是先 $i$ 后 $j$ 只能加入一个人。剩下无论如何都加不了或都加的了两个人的 $h$ 显然与两人之间的顺序无关了。因此只需要关注上面的唯一情况。写成式子就是：

- $h\le H_j,h+P_j\le H_i$

- $h\le H_i,h+P_i> H_j$

合并，有：$H_j-P_i<h\le H_i-P_j$，若存在这样的 $h$，则有：$H_j+P_j\le H_i+P_i$。注意到不等式变形的时候有一些截断和边界点调整，因为都是整数，且误差不影响，可以近似这样处理。

那我们就把顺序关系和考虑的两个人独立分开了啊，只需要按照 $H_i+P_i$ 升序排序，这样的顺序决策一定不会劣，那就做完了，设 $f_{i,j}$ 为前 $i$ 个人，目前高度为 $j$ 的最多人数，转移是简单的。复杂度 $O(nV)$。但这样显然过不了，然后就上经典的值域定义域转换，重新设计为考虑前 $i$ 个人，保证选 $j$ 个人到目前的最小高度即可。这样就优化到 $O(n^2)$ 了。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

int n;
ll f[5005];
struct node{int a,b,c;}a[5005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int main(){
    in(n);
    for(int i=1;i<=n;i++) in(a[i].a),in(a[i].b),a[i].c=a[i].a+a[i].b;
    sort(a+1,a+1+n,[](node p,node q){return p.c<q.c;});
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=i;j;j--)
            if(f[j-1]<=a[i].a) f[j]=min(f[j],f[j-1]+a[i].b);
    for(int i=n;i>=1;i--)
        if(f[i]<=1e14){printf("%d\n",i);return 0;}

	return 0;
}

```

---

## 作者：Super_Cube (赞：1)

# Solution

现有两个相邻的人 $i,j$，设前面累计砖块量为 $s$，那么 $i$ 在前面比 $j$ 在前面优的条件为 $s+p_i\le h_j$ 且 $s+p_j>h_i$，结合出 $h_i-p_j\le h_j-p_i$，即 $h_i+p_i\le h_j+p_j$。所以先对所有人按 $h_i+p_i$ 从小到大排序。

一个很自然的想法是设 $dp_{i,j}$ 表示前 $i$ 个人累计砖块量为 $j$ 的最多人数，转移为 $dp_{i,j}=\max(dp_{i-1,j},[p_i\le j\le p_i+h_i](dp_{i-1,j-p_i}+1))$，最后在 $dp_n$ 中扫一遍取最大值。0/1 背包，时间复杂度 $O(nV)$，无法通过。

技巧：对调答案与状态。改写状态定义：$dp_{i,j}$ 为前 $i$ 个人选了 $j$ 个人的最小砖块数。转移：$dp_{i,j}=\min(dp_{i-1,j},[dp_{i-1,j-1}\le h_i](dp_{i-1,j-1}+p_i))$，最后在 $dp_n$ 中扫一遍找到 $dp_{n,i}$ 有意义中最大的 $i$ 即为答案。时间复杂度：$O(n^2)$，可以通过。

# Code
```cpp
#include<bits/stdc++.h>
struct node{
	int h,p;
	inline bool operator<(const node&_)const{
		return h+p<_.h+_.p;
	}
}a[5005];
long long dp[5005];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].h,&a[i].p);
	std::stable_sort(a+1,a+n+1);
	memset(dp+1,63,n<<3);
	for(int i=1;i<=n;++i)
		for(int j=i;j;--j)
			if(dp[j-1]<=a[i].h)dp[j]=std::min(dp[j],dp[j-1]+a[i].p);
	for(int i=n;~i;--i)
		if(dp[i]!=0x3f3f3f3f3f3f3f3f)printf("%d",i),i=0;
	return 0;
}
```

---

