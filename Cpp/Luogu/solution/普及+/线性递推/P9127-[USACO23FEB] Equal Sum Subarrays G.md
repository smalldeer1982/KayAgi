# [USACO23FEB] Equal Sum Subarrays G

## 题目描述

注意：本题的时间限制为 3 秒，为默认时间的 1.5 倍。

FJ 给了 Bessie 一个长度为 $N$ 的数组 $a$（$2 \leq N \leq 500, -10^{15} \leq a_i \leq 10^{15}$），其中所有 $\dfrac{N(N+1)}{2}$ 个连续子数组的和都是不同的。对于每个下标 $i \in [1,N]$，帮助 Bessie 计算最小的改变量，使得数组中存在两个不同的连续子数组的和相等。

## 样例 #1

### 输入

```
2
2 -3```

### 输出

```
2
3```

## 样例 #2

### 输入

```
3
3 -10 4```

### 输出

```
1
6
1```

# 题解

## 作者：zhangchengqi666 (赞：11)

## 说在前面

感觉想了三天才做出来的自己跟个人一样……

小建议：把思路写在代码下面是一种非常好的习惯，容易梳理思路，记得多提问。具体怎么做看后面。

## 题目分析

接下来，我将带领你一步一步，从根开始，找到解题思路。

首先，题目要求改变 $a _ i$ 的值，找到两个不同的连续子序列，它们的和相等。求 $\min \{ |\Delta a _ i|\}$。

其中，$|$ 是绝对值的意思，就是把满足 $a < 0$ 的数变成 $-a$。$\Delta x$ 指的是 $x$ 的改变量，也就是现在的 $x$ 减去原来的 $x$。

现在思考：这两个序列有什么特点？

题目中提到：初始状态下没有两个和相等的连续子序列。所以，如果序列中不包含 $a_i$，那么显然是不行的。因为如果这两个序列与 $a _ i$ 无关，则 $a _ i$ 的变化与对两个序列的和没有影响。那么现在我们得出：两个序列中至少包含 $1$ 个 $a _ i$。

包含两个行不行？也不行。因为如果两个序列都与 $a _ i$ 有关，那么两个序列同时加上或减去一个相同的数，大小关系不变。

得出结论：只有一个序列包含 $a _ i$。

则问题转化为：找到一个包含 $a _ i$ 的序列和一个不包含 $a _ i$ 的序列，他们差值的**绝对值**最小。

那么我们先求出所有子序列的和：

```cpp
for (int i = 1; i <= n; i++) { // 前缀和
    s[i] = s[i - 1] + a[i];
}
for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
        sum[i][j] = s[j] - s[i - 1];
    }
}
```

然后，统计答案。但是直接做时间复杂度大的逆天，光枚举区间就得六重循环。所以，考虑优化。

先把区间信息存进结构体数组：

```cpp
struct arr {
    int l, r, sum;
} b[N];
...
int cnt = 0;
for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
        b[++cnt] = {i, j, s[j] - s[i - 1]};
    }
}
```
随后，我们想一想：最小差值可能出现在什么地方？

是不是很简单？排序后数组相邻的两个数。

所以，按 $sum$ 由小到大排序。

```cpp
struct arr {
    ...
    bool operator < (const arr & x) const {
        return sum < x.sum;
    }
} b[N];
...
sort(b + 1, b + cnt + 1); // 如果不重载小于号要手写比较函数。
```

那么，枚举相邻的两个序列就行了。

这里给出证明：

假设最小产生在 $b _ i$ 和 $b _ {i + 2}$ 之间（不相邻）。那么应有：

$$
b _ {i + 2} - b _ i < b _ {i + 1} - b _ i
$$

即

$$
b _ {i + 2} < b _ {i + 1}
$$

这与 $b _ {i + 1} < b _ {i + 2}$ 矛盾！

所以假设不成立。

那么我们如何得知区间是否包含 $a _ i$ 呢？

这时候，我们在结构体里存的 $l$ 和 $r$ 就有用了。

不用去枚举 $l$ 到 $r$，只需要判断 $l \le i \le r$ 就行了。还是那句话：初始状态下没有两个连续子区间的和相等。

对于每一个 $a _ i$，扫描整个序列数组，如果一个序列和跟它相邻的序列一共只包含一个 $a _ i$，那么将它们的和相减，与答案取最小值。这一轮结束后输出答案。

至此，分析结束，时间复杂度 $O(n ^ 3)$，三次方是因为子序列个数有 $\frac{n \dot (n + 1)}{2}$ 个，乘上枚举 $a _ i$  的 $O(n)$，算下来是 $\Theta (\frac{n ^ 2 \dot (n + 1)}{2})$，差不多 $O (n ^ 3)$。

## 注意事项

$$ ans = \min \{ sum _ {b _ {i + 1}} - sum _ {b _ {i}} \}$$

这里不用加绝对值，因为是从小到大排序。

## 完整代码（最下面就是思路）

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 500 + 5;

int a[N], s[N];

struct arr {
	int l, r, sum;
	
	bool operator < (const arr & x) const {
		return sum < x.sum;
	}
} b[N * N];

int n;

bool check(int l, int r, int x) {
	return l <= x && x <= r;
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			b[++cnt] = {i, j, s[j] - s[i - 1]};
		}
	}
	sort(b + 1, b + cnt + 1);
	for (int i = 1; i <= n; i++) {
		int ans = 0x3f3f3f3f3f3f3f3f;
		for (int j = 1; j < cnt; j++) {
			if (check(b[j].l, b[j].r, i) && !check(b[j + 1].l, b[j + 1].r, i) || !check(b[j].l, b[j].r, i) && check(b[j + 1].l, b[j + 1].r, i)) {
				ans = min(ans, b[j + 1].sum - b[j].sum);
			}
		}
		cout << ans << endl;
	}
	return 0;
}

/*
题目说要求改变 ai 的值，使得有两个不同的连续子序列相等。
那么，这两个子序列有什么特点？
题目说一开始没有两个不同子序列的和相等，说明 ai 的值对序列有影响。
所以两个序列中至少有一个包含 ai？
不对，应该是只有一个。因为两个序列同时加上相同的值，大小关系不变。
所以要求包含 ai 的序列 和 不包含 ai 的序列 的 最小差值。
先求出所有子序列的和：
for (int i = 1; i <= n; i++) {
	for (int j = i; j <= n; j++) {
		for (int k = i; k <= j; k++) {
			sum[i][j] += a[k];
		}
	}
}
时间复杂度是 O(n ^ 3)，会不会炸？
显然不会。题目指出 1 <= N <= 500。
随后来比较。但是直接比较显然会超时。
那我们如何高效的找到不含 ai 和 含 ai 的序列呢？
把序列信息存入结构体中。
struct arr {
	int l, r, sum;
} b[N];
.....
int cnt = 0;
for (int i .....n; i++) 
	for (int j .....n; j++) {
		b[++cnt] = {i, j, sum[i][j]};
	}
}
哦，不用这么麻烦，可以先预处理前缀和。
for (int i = 1; i <= n; i++) {
	sum[i] = sum[i - 1] + a[i];
}
for (i......) 
	for (j.......)
		b[++cnt] = {i, j, sum[i] - sum[j - 1]};
现在怎么做？
可以排个序，这样相邻的差值一定是最小的。
假设 ai 的存在情况如下：

0 1 0 0 1 1 0 0 
怎么找？
看起来只要找相邻的就可以了。
每次枚举相邻两个区间。看如果一边有 ai 一边没有 ai，就计算答案。
如何证明？
可以知道，排序后差值最小一定产生在相邻两个数。假设不产生在 b(i + 1)，产生在 b(i + 2)：
则我们可知
bi < b(i + 1) < b(i + 2);
b(i + 1) - bi < b(i + 2);
证毕。
但怎么判断有没有ai这个数呢？
原始思路：枚举 l ~ r 看有没有 ai。
但是题目说了没有相同的子序列，也就是数互不相同！！！
所以 一旦 l <= i <= r，就说明他在这个区间内！！！
所以判断相邻两段区间是否一个包含一个不包含，如果是则 ans = min(ans, b[i + 1].sum - b[i].sum)；
输出答案即可。
至此，思路完全打开。
*/
```

## 说在后面

若思路、代码讲解有误，欢迎提出！

---

## 作者：封禁用户 (赞：11)

题目意思主要是找到两个区间，使得一个含 $i$ 一个不含 $i$，求所有满足要求的区间的和的最小差值即为 $ans_i$。

我们充分发扬人类智慧：

先把所有的区间和区间和求出来，按照区间和排序，由于需要差值最小，所以依次找下标差为 $1$ 的两个区间（即排序后相邻），差为 $2$ 的，...，直到能找到满足要求的，记录 $flag = 1$，在当前这一轮扫完之后 break 就行。

这样速度快得飞起，在 $n = 500$ 时都可以在 248ms 内卡过。

---

## 作者：DengDuck (赞：10)

这种题都做不出来我是不是退化成弱智了？

首先根据题意不难发现输出的第 $x$ 项 $ans_x$ 等价于找到两个区间，一个包含 $x$，一个不包含 $x$，找到两者的最小差值。

直接做的时间复杂度是 $O(n^3\log n^2)$，我模拟赛打的就是这个思路。

但是其实我们可以考虑逆着维护，也就是根据区间来更新 $ans_x$。

首先提取出所有的区间，从小到大排个序，显然相邻的两个区间除去交集之后的部分就可以拿来更新。

这里其实有几种情况，大家可以根据题目给出的性质讨论讨论，最后发现都是符合的。

所以就可以做了，时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=505;
LL n,a[N],sum[N],ans[N],cnt,b[N];
struct node
{
	LL l,r,x;
}t[N*N];
bool cmp(node x,node y)
{
	return x.x<y.x;
}
LL dkabs(LL x) 
{
	if (x<0)return -x;
	return x;
}
int main()
{
	memset(ans,127,sizeof(ans));
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
		for(int j=1;j<=i;j++)
		{
			t[++cnt]={j,i,sum[i]-sum[j-1]};
		}
	}
	sort(t+1,t+cnt+1,cmp);
	for(int i=2;i<=cnt;i++)
	{
		LL l1=t[i].l,l2=t[i-1].l;
		LL r1=t[i].r,r2=t[i-1].r;
		LL p=dkabs(sum[r2]-sum[l2-1]-sum[r1]+sum[l1-1]);
		memset(b,0,sizeof(b));
		for(int j=l1;j<=r1;j++)b[j]^=1;
		for(int j=l2;j<=r2;j++)b[j]^=1;
		for(int j=1;j<=n;j++)if(b[j])ans[j]=min(ans[j],p);
	}
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：_aa_ (赞：9)

# 思路
找到一个包含 $a_i$ 的区间，和一个不包含 $a_i$ 的区间，对于每个 $a_i$ 最小的两个区间和的差就是答案。

我们可以求出每一个区间的和，再把它们降序排序，这样每一个区间相邻下标的区间一定是与当前区间的区间和差值最小的。

我们枚举两个相邻下标的区间，更新仅在其中一个区间中的点的答案为两个区间和的差。
总时间复杂度为 $O(n^3)$ 。
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
struct node{
	int l,r,s;
	
}brr[180005];
int n,arr[505],tot,ans[505];
bool cmp(node a,node b){
	return a.s>b.s;
}
signed main(){
	memset(ans,0x3f,sizeof ans);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>arr[i];
		
	}
	
	for(int i=1;i<=n;++i){
		int s=0;
		
		for(int j=i;j<=n;++j){
			s+=arr[j];
			brr[++tot]={i,j,s};
			
		}
	}
	
	sort(brr+1,brr+1+tot,cmp);
	for(int i=1;i<=tot-1;++i){
		
		int l1=brr[i].l,r1=brr[i].r,l2=brr[i+1].l,r2=brr[i+1].r;
		for(int j=l1;j<=r1;++j){
			int a=((j>=l1)&&(j<=r1))^((j>=l2)&&(j<=r2));
			
			if(a==1)ans[j]=min(ans[j],brr[i].s-brr[i+1].s);
		}
		for(int j=l2;j<=r2;++j){
			int a=((j>=l1)&&(j<=r1))^((j>=l2)&&(j<=r2));
			
			if(a==1)ans[j]=min(ans[j],brr[i].s-brr[i+1].s);
		}
	}
	for(int i=1;i<=n;++i){
		cout<<ans[i]<<'\n';
	}
	
}
```

---

## 作者：MessageBoxA (赞：7)

*upd 23.10.7：润色文章，修改错别字，补充挂掉的图*

# 写在前面

1. 这题虽然是一道黄题（其实应该评绿的），但这是对于 $O(n^3)$ 的做法而言；这篇博客的做法是 $O(n^2\log n)$，个人觉得大概算蓝。

2. **这个做法细节很多**，我七七八八算下来交了十几发才过，思路和另一个大佬有些像，但是相对于他的博客进行了一些优化，并且更详细地解释了这种 $O(n^2\log n)$ 的做法。

# 题意

[题目链接](https://www.luogu.com.cn/problem/P9127)

给你一个数组 $a$，初始时数组的**所有**区间的区间和互不相同，对于每个 $i\in [1,N]$，将 $a_i$ 改为 $a_i'$ 使得数组会有两个区间的区间和相等，求 $\lvert a_i-a_i'\rvert$ 的最小值。

# 性质

1. 我们很容易想到一个性质：称我们修改的数叫 $i$，最后区间和相等的两个区间一定是**一个区间包含 $i$，一个不包含**。原因很简单，因为对 $i$ 修改过后包含 $i$ 的所有区间的区间和都会变化 $\Delta i$，假设两个区间都包含，那么他们这两个区间的相对大小和修改前一样，而修改前题目保证了没有任何区间和相等，因此同时包含 $i$ 的两个区间修改后不可能区间和相等。

2. 由于题目只让我们输出修改的最小差值，而不用输出具体方案，我们找到一个性质：**两个区间有交的情况一定能归纳为无交的情况**。

   (1). 考虑两个区间交叉的情况

      如图，由于我们修改的 $i$ 由于上述性质不能同时被两个区间包含，那么对于修改后区间和相等的两个红色区间，我们同时减去蓝色虚线括起来的中间部分，就能归纳为两个无交的橙色区间修改后的区间和相等。

      ![](https://cdn.luogu.com.cn/upload/image_hosting/scz4ry0c.png)

   (2). 考虑一个区间包含另一个区间的情况

      如图，对于这两个红色区间，可以归纳为两个橙色区间修改后的区间和互为相反数。

      ![](https://cdn.luogu.com.cn/upload/image_hosting/mn7s294q.png)

3. 两个区间的区间和互为相反数的注意事项 *（注意这里的“区间”概念同样也指一个数，即区间 $[i,i]$）*：如果两个区间，修改后区间和相加为 $0$，它们要对答案产生贡献仅当这两个区间中间还有其他数，或者这两个区间旁边还有其他数。
	
    很显然，如果这两个区间中间有其他数则可归纳为性质二的区间包含的情况；而如果这两个区间是挨在一起的（如下图，红色和绿色代表这两个区间，粉色代表其他数），那么这两个区间可以合并为一个区间和为 $0$ 的区间，加上旁边的数（粉色）就等于这个旁边的数，符合题目要求；而如果没有旁边的数，换句话说就是这两个区间已经占完了整个序列，这时候这两个区间的区间和等于 $0$ 就没用了。

   概括一下就是：**要使得这两个区间的并集的补集非空**。
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/vd5edrst.png)

# 做法

掌握了以上几个性质，我们总结一下最终我们需要干些什么：

> 找出两个不相交的区间，一个包含 $i$，一个不含。要么使得 $i$ 修改后两个区间的区间和相等，要么使得修改后两个区间的区间和互为相反数并且满足性质 3

我们枚举 $l$ 作为分界点，将 $l$ 之前（不包括 $l$）的所有区间都放入一个 `set` 里面，再枚举 $r\in [l,n]$，相当于枚举了所有以 $l$ 开头的区间。此时有两种区间，一种是 $l$ 左边的区间，一种是右边的区间 $[l,r]$。我们用前缀和 $O(1)$ 算出右边区间的区间和，再在 `set` 中 $O(\log n)$ 二分找出与它区间和最接近的区间，求出它们区间和的差值，这个差值意味着：**“$[l,r]$ 的区间和要等于另一个区间的区间和的最小差值”**，注意这个“差值”可以应用于 $[l,r]$ 当中的任意一个数，因为 $[l,r]$ 中的任意一个数加上这个差值都可以使得 $[l,r]$ 的区间和等于另一个区间的区间和，所以所有 $ans_i\ (i\in [l,r])$ 都要被这个差值更新一次。

但我们没有必要因此写数据结构维护 $ans_i$ 的最小值，容易发现当 $l$ 固定的时候，$ans_i$ 会被 $[l,n],[l,n-1],\dots,[l,i]$ 更新一遍，所以我们只需要倒序枚举 $r$ 即可。

> 举例：
>
> $ans_n$ 只会被 $[l,n]$ 更新
>
> $ans_{n-1}$ 会被 $[l,n],[l,n-1]$ 更新
>
> $ans_{n-2}$ 会被 $[l,n],[l,n-1],[l,n-2]$ 更新
>
> $\cdots$
>
> 我们只需要倒序枚举 $r=n\rightarrow l$，维护一个后缀 $\min$ 即可

同理，前面我们找了区间和差值最小的两个区间，我们将 $[l,r]$ 的区间和取相反数，即可找区间和加起来等于 $0$ 的最小修改代价。具体实现代码与上文相同，只是确定了两个区间后碍于性质 3 我们需要判断他们的并集是否覆盖了全部区间。

最后，需要注意一点，最开始的时候 $ans_i$ 需要设为 $num_i$，表示它把自己变为 $0$ 的代价（题目似乎保证了 $N\geq 2$，不用与担心性质 3 冲突）。

# 代码

最后放上代码，小提醒：由于涉及大量区间操作，`for` 的时候注意区间的范围、区间的开闭。

```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void rd(T &x){
	T res=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
	x=res*f;
}
template<class T>inline void wt(T x){
	if(x<0){x=-x;putchar('-');}
	if(x>9) wt(x/10);
	putchar(x%10+'0');
}
typedef long long LL;
const LL LLINF=numeric_limits<LL>::max()-1;
const int MAXN=505;
int n;
struct Node{
    LL val;
    int l,r;
    bool operator < (const Node &y) const{
        return val<y.val;
    }
};
LL a[MAXN],pre[MAXN],ans[MAXN];
set<Node>s;
inline bool is_range_merge_cover_all(int l1,int r1,int l2,int r2){
    if(l1>l2) swap(l1,l2),swap(r1,r2);
    // cout<<l1<<' '<<r1<<' '<<l2<<' '<<r2<<endl;
    if(r1+1<l2) return false;
    if(l1<=1 && max(r1,r2)>=n) return true;
    return false;
}
int main(){
    rd(n);
    if(n==2){//特判n==2
        rd(a[1]);rd(a[2]);
        cout<<min(abs(a[1]),abs(a[2]-a[1]))<<endl<<min(abs(a[2]),abs(a[2]-a[1]));
        return 0;
    }
    pre[0]=0;
    for(int i=1;i<=n;i++){
        rd(a[i]);
        ans[i]=abs(a[i]);//将自己变为0的代价
        pre[i]=pre[i-1]+a[i];
    }
    LL tmp,minx;
    set<Node>::iterator res;
    s.insert({a[1],1,1});
    for(int l=2;l<=n;l++){
        minx=LLINF;
        for(int r=n;r>=l;r--){
            tmp=pre[r]-pre[l-1];
            minx=min(minx,abs(tmp));//这一步的原因是将这个数变为0过后任意相邻区间加它都等于自己
            res=s.lower_bound({tmp,-1,-1});//找后继
            if(res!=s.end()) minx=min(minx,abs(res->val-tmp));
            if(res!=s.begin()){
                res--;//找前驱
                minx=min(minx,abs(res->val-tmp));
            }
            ans[r]=min(ans[r],minx);

            tmp=-tmp;//找与这个区间和的相反数最接近的区间和，使他们抵消成为0的代价最小
            res=s.lower_bound({tmp,-1,-1});//找后继
            if(res!=s.end())
                if(!is_range_merge_cover_all(l,r,res->l,res->r))
                    minx=min(minx,abs(res->val-tmp));//如果这两个区间覆盖了所有数则无法满足题目条件
            if(res!=s.begin()){
                res--;//找前驱
                if(!is_range_merge_cover_all(l,r,res->l,res->r))
                    minx=min(minx,abs(res->val-tmp));
            }
            ans[r]=min(ans[r],minx);
        }
        for(int i=1;i<=l;i++)
            s.insert({pre[l]-pre[i-1],i,l});
    }
    
    s.clear();
    s.insert({a[n],n,n});
    for(int r=n-1;r>=1;r--){
        minx=LLINF;
        for(int l=1;l<=r;l++){
            tmp=pre[r]-pre[l-1];
            minx=min(minx,abs(tmp));
            res=s.lower_bound({tmp,-1,-1});//找后继
            if(res!=s.end()) minx=min(minx,abs(res->val-tmp));
            if(res!=s.begin()){
                res--;//找前驱
                minx=min(minx,abs(res->val-tmp));
            }
            ans[l]=min(ans[l],minx);

            tmp=-tmp;
            res=s.lower_bound({tmp,-1,-1});//找后继
            if(is_range_merge_cover_all(l,r,res->l,res->r)) continue;
            if(res!=s.end())
                if(!is_range_merge_cover_all(l,r,res->l,res->r))
                    minx=min(minx,abs(res->val-tmp));
            if(res!=s.begin()){
                res--;//找前驱
                if(!is_range_merge_cover_all(l,r,res->l,res->r))
                    minx=min(minx,abs(res->val-tmp));
            }
            ans[l]=min(ans[l],minx);
        }
        for(int i=n;i>=r;i--)
            s.insert({pre[i]-pre[r-1],r,i});
    }
    for(int i=1;i<=n;i++) wt(ans[i]),putchar('\n');
    return 0;
}
```

---

## 作者：Glacial_Shine (赞：4)

# 思路

老师拿来打模拟赛，赛时想了一个 $O(n^3\cdot \log n^2)$ 的做法。

就是我们先将 $\frac{N(N+1)}{2}$ 个区间和都求出来，然后排序。

对于每次需要修改的 $a_i$，找出修改 $a_i$ 后会一起修改的区间和，打上标记。

因为区间和互不相同，那么每个区间和的值只会出现一次，所以我们可以用 map 来维护标记。（$\log n^2$ 的来源）

因为打了标记的区间和**永远**不会相等，所以我们只需要考虑没打标记和打了标记之间的差值。

又因为已经排了序，则差值最小的肯定出现在排序后相邻两个标记不同的区间和上，则遍历一遍即可。

结果 TLE 了……

于是我们来考虑如何优化。

发现，map 自带 $\log n^2$ 的时间复杂度，考虑如何消除 $\log n^2$。（$n^3$ 能过）

我们可以记录每个区间和的左端点和右端点，则维护标记就可以用数组解决了。（具体实现可以参考代码）

然后就过了这道题！

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, m, flag[505][505];
LL a[505], sum[500005], ans;
struct node { LL s; int i, j; } p[500005];
bool cmp(node a, node b) { return a.s < b.s; }
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]), sum[i] = sum[i - 1] + a[i];
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            p[++m].s = sum[j] - sum[i - 1], p[m].i = i, p[m].j = j;
    sort(p + 1, p + 1 + m, cmp);
    for (int k = 1; k <= n; k++) {
        ans = 1e18;
        for (int i = 1; i <= k; i++)
            for (int j = k; j <= n; j++)
                flag[i][j] = 1;
        for (int i = 2; i <= m; i++)
            if (flag[p[i].i][p[i].j] != flag[p[i - 1].i][p[i - 1].j])
                ans = min(ans, abs(p[i].s - p[i - 1].s));
        for (int i = 1; i <= k; i++)
            for (int j = k; j <= n; j++)
                flag[i][j] = 0;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：cff_0102 (赞：3)

既然这题能用 $O(n^3)$ 的方法过，为什么评的是绿题啊，感觉不是很难啊。$O(n^2\log n)$ 的做法倒是确实可以评蓝。

不过既然都认为这题可以评绿的话那就绿吧。

---

可以直接将所有 $\frac{n\times(n+1)}{2}$ 个子区间的和全部存下来并排个序。

注意到，如果要通过修改第 $i$ 个元素来让两个子区间的和相等，那么这两个子区间不能都包含 $i$，也不能都不包含 $i$，不然操作 $i$ 有什么用呢？

所以，最终相等的两个子区间一个包含 $i$，一个不包含 $i$。

以序列 $[11,4,5,14]$ 为例，所有子区间加起来并排序后为：

$$[4,5,9,11,14,15,16,19,23,34]$$

假设要更改第 $1$ 个数使得存在两个子区间之和相等，由前面的推导，可以将这些区间是否包含第 $1$ 个数的状态拎出来：

$$[0,0,0,1,0,1,1,0,0,1]$$ 

从里面选出一个 $0$ 和一个 $1$，并求出它们对应的数的差，取最小值，就是答案（在这里为 $15-14=1$）。不难发现，此时只需要取相邻两个数，其中一个状态为 $1$，一个状态为 $0$，作差即可，不需要枚举所有 $1$ 和 $0$，因为如果这两个数不相邻，其间必有一个 $1$ 或 $0$，选这个数，再和另一个状态相反的数作差，显然这样差值更小，为什么还要选不相邻的呢？

对于询问 $i$，每次处理这个序列中相邻的两项，如果满足恰有一个包含 $i$，就更新答案即可。单次复杂度 $O(n^2)$（这个序列的长度），所有询问的复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
struct subarray{
	int s,l,r;
}subs[N*N];
int a[N],s[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];s[i]=s[i-1]+a[i];
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			subs[++cnt]={s[j]-s[i-1],i,j};
		}
	}
	sort(subs+1,subs+1+cnt,[](subarray x,subarray y){
		return make_tuple(x.s,x.l,x.r)<make_tuple(y.s,y.l,y.r);
	});
	for(int i=1;i<=n;i++){
		int ans=1e18;
		for(int j=1;j<cnt;j++){
			int l1=subs[j].l,l2=subs[j+1].l,r1=subs[j].r,r2=subs[j+1].r;
			bool f1=(l1<=i&&i<=r1),f2=(l2<=i&&i<=r2);
			if(f1+f2==1){
				ans=min(ans,abs(subs[j].s-subs[j+1].s));
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

另外，注意到可以直接从头到尾跑一遍相邻的每对子序列，并更新所有只在其中一个序列出现的数的答案。区间修改，单点查询，可以使用线段树维护，最终总复杂度 $O(n^2\log n)$，这里不放代码了~~其实就是我懒得写~~。

---

## 作者：Disjoint_cat (赞：3)

[Link](https://www.luogu.com.cn/problem/P9127)

## P9127 [USACO23FEB] Equal Sum Subarrays G

第一道赛时 AC 的 Gold 题。~~同学们：Gold 不是很水吗~~

### 1. 题意

给你一个长度为 $n$ 的数列 $a$，并保证 $a$ 的所有连续子序列的和不同。

对于每个 $p(1\le p\le n)$，回答下面的问题：

> 最少要把 $a_p$ 变化（增加或减少）多少，才能让 $a$ 中有两个不相同的子序列的和相同。

$n\le500,a_i\le10^{15}$。

### 2. 题解

$n\le500$？$O(n^3)$？但是 USACO 从不卡常啊。。。

---

令 $sum_{i,j}$ 表示原数组中第 $i\sim j$ 个数的和，$ans_p$ 为 $p$ 的答案。

首先，可以发现对于 $i,j(1\le i\le j\le n)$，如果 $i\le p\le j$，则 $sum_{i,j}$ 会被加上 $ans_p$，否则不变。

又因为初始时所有子序列和不同，所以在操作后相等的子序列肯定一个变了，另一个没变。

所以我们可以把会变的和与不会变的和排序，取他们之间差的绝对值最小的即可。

直接双指针。时间复杂度貌似是 $O(n^3)$？

```cpp
const int N=505;
int n;
ll a[N],sum[N];
ll s[N*N],t[N*N],cnt1,cnt2;
void Solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cnt1=cnt2=0;
		for(int j=1;j<i;j++)
			for(int k=j;k<i;k++)
				s[++cnt1]=sum[k]-sum[j-1];
		for(int j=i+1;j<=n;j++)
			for(int k=j;k<=n;k++)
				s[++cnt1]=sum[k]-sum[j-1];
		for(int j=1;j<=i;j++)
			for(int k=i;k<=n;k++)
				t[++cnt2]=sum[k]-sum[j-1];
		sort(s+1,s+cnt1+1);
		sort(t+1,t+cnt2+1);
		t[cnt2+1]=LLONG_MAX;
		ll ans=LLONG_MAX;
		for(int j=1,k=1;j<=cnt1;j++)
		{
			while(k<cnt2&&t[k+1]<=s[j])k++;
			ans=min(ans,min(abs(t[k+1]-s[j]),abs(t[k]-s[j])));
		}
		cout<<ans<<endl;
	}
}
```

然后你发现 TLE 了。

一看，`sort(s+1,s+cnt1+1);` 是给 $O(n^2)$ 个数排序。

所以复杂度实际上是 $O(n^3\log(n^2))$！

所以觉得正解就是把那个 $\log$ 去掉。

最后想出了一种方法：先离散化，这样就能桶排序了。于是只用排一次序了，时间复杂度变成了 $O(n^3)$。

然后又调了半天，终于 AC 了。

最后贴个代码吧：

```cpp
const int N=505;
int n;
ll a[N],sum[N];
int rnk[N][N],ps[N*N],pt[N*N];
#define dat pair<ll,pair<int,int> >
vector<dat>v;
#define mp make_pair
#define F first
#define S second
bool cs[N*N],ct[N*N];
void Solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	v.push_back(mp(LLONG_MIN,mp(0,0)));
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
//			cout<<i<<" "<<j<<" "<<sum[i]-sum[j-1]<<endl;
			v.push_back(mp(sum[j]-sum[i-1],mp(i,j)));
		}
	int len=v.size()-1;
	sort(v.begin(),v.end());
	for(int i=1;i<=len;i++)rnk[v[i].S.F][v[i].S.S]=i;
//	for(int i=1;i<=len;i++)cout<<v[i].S.F<<" "<<v[i].S.S<<" "<<v[i].F<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=len;j++)cs[j]=ct[j]=0;//没写主函数，别ct[j]啊
		for(int j=1;j<i;j++)
			for(int k=j;k<i;k++)
				cs[rnk[j][k]]=1;
		for(int j=i+1;j<=n;j++)
			for(int k=j;k<=n;k++)
				cs[rnk[j][k]]=1;
		for(int j=1;j<=i;j++)
			for(int k=i;k<=n;k++)
				ct[rnk[j][k]]=1;
		int cnt1=0,cnt2=0;
		for(int j=1;j<=len;j++)
		{
			if(cs[j])ps[++cnt1]=j;
			if(ct[j])pt[++cnt2]=j;
		}
		ll ans=LLONG_MAX;
		for(int j=1,k=1;j<=cnt1;j++)
		{
			while(k+1<cnt2&&v[pt[k+1]].F<v[ps[j]].F)k++;
			ans=min(ans,min(abs(v[pt[k+1]].F-v[ps[j]].F),abs(v[pt[k]].F-v[ps[j]].F)));
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：Feyn (赞：3)

[My Blog](https://www.cnblogs.com/feyn)

大概题意是说你有一个长度为 $n$ 的序列 $a$，显然它有 $\frac{n(n+1)}{2}$ 个区间和。对于每个 $x$，你可以把 $a_x$ 改成 $c$，使得修改之后这个序列存在两个区间和相同，输出最小的 $|a_x-c|$。

观察数据范围 $n\le 500$，可以采用 $O(N^3)$ 的算法。思考修改 $a_x$ 会发生什么，所有的区间分成两类，一类是包含 $a_x$ 的，一类是不包含的，修改并不会改变同一类区间之间的差值，于是问题变成了找到两类区间中最接近的一对区间，想到把两类区间按照和排序，然后扫描一遍找最接近的一对即可。

于是问题只剩下了如何快速维护排好序的两类区间，由于区间的值并不会变，所以感觉上可以用链表来维护。每次 $x$ 向后挪动一次，有一些区间会从第二类变成第一类区间，有一些会从第一类变成第二类，容易发现每个区间只会变化 $O(1)$ 次，随便维护一下即可。于是总的复杂度是 $O(N^3)$。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=510;
const int inf=3e18;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,a[N],s[N],n,id[N][N];
struct node{int l,r,data;}c[N*N];
inline bool operator <(node s1,node s2){
	return s1.data<s2.data;
}

struct T{
	int nxt[N*N],pre[N*N];
	void build(bool type){
		if(type){
			for(int i=1;i<=n;i++)pre[i]=i-1,nxt[i]=i+1;
			pre[n+1]=n;nxt[0]=1;
		}
		else nxt[0]=n+1;
	}
	inline void link(int x,int y,int z){nxt[x]=y;nxt[y]=z;pre[y]=x;pre[z]=y;}
	inline void unlink(int x,int y,int z){nxt[x]=z;pre[z]=x;}
	void print(){
		int x=0;
		while(x<=n){
			printf("%lld ",x);
			x=nxt[x];
		}
	}
}A,B;
set<int>sa,sb;

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	for(int i=1;i<=m;i++){
		read(a[i]);s[i]=s[i-1]+a[i];
	}
	for(int i=1;i<=m;i++){
		for(int j=0;j<i;j++){
			c[++n]=(node){j+1,i,s[i]-s[j]};
		}
	}
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++)sa.insert(i);
	sa.insert(0);sa.insert(n+1);
	sb.insert(0);sb.insert(n+1);
	
	c[n+1].data=inf;c[0].data=-inf;
	for(int i=1;i<=n;i++)id[c[i].l][c[i].r]=i;
	A.build(true);
	B.build(false);
	for(int x=1;x<=m;x++){
		for(int i=1;i<x;i++){
			int now=id[i][x-1];
			
			auto R=sa.lower_bound(now);
			auto L=prev(R);
			sa.insert(now);
			A.link(*L,now,*R);
			
			R=sb.upper_bound(now);
			L=prev(prev(R));
			sb.erase(now);
			B.unlink(*L,now,*R);
		}
		for(int i=x;i<=m;i++){
			int now=id[x][i];
			
			auto R=sb.lower_bound(now);
			auto L=prev(R);
			sb.insert(now);
			B.link(*L,now,*R);
			
			R=sa.upper_bound(now);
			L=prev(prev(R));
			sa.erase(now);
			A.unlink(*L,now,*R);
		}
		
		int ans=inf;
		for(int p=B.nxt[0],q=0;p<=n;p=B.nxt[p]){
			while(c[q].data<c[p].data)q=A.nxt[q];
			ans=min(ans,c[q].data-c[p].data);
			ans=min(ans,c[p].data-c[A.pre[q]].data);
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
```

---

## 作者：Moya_Rao (赞：2)

# 题目大意
[原题](https://www.luogu.com.cn/problem/P9127)

给定一个长度为 $n$ 的数组，保证**每个**区间的和**都不相等**。现在要求出每一个如果**只修改**第 $i$ 个值，让两个区间的和变为相等，最少要让这个值加几或减几。

# 思路

考虑先把每个区间的左端点、右端点以及区间和存入一个结构体数组中，按区间和从小到大排个序。

再进行每一个点的遍历。
>初始化这个值的答案 $ans$ 为这个值本身，因为变成 $0$ 了就可以有相同的区间了。 先把标记数组清零，再给包含这个值的数组打上标记，方便判断。接着一个一个区间看，若相邻两个区间的标记不同，说明一个包含这个值，另一个不包含。取出它们俩的差，和 $ans$ 取个 $\min$。全部遍历完了后，输出！

时间复杂度 $O(n^3)$，没问题吧。

交上去看看，[AC](https://www.luogu.com.cn/record/162902638) 喽！

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{long long sum,l,r;}p[500005];
long long n,a[505],s[505],len,ans;
bool v[505][505];
bool cmp(node x,node y){return x.sum<y.sum;}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i];s[i]=s[i-1]+a[i];}
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            len++;
            p[len].sum=s[j]-s[i-1],p[len].l=i,p[len].r=j;
        }
    }
    sort(p+1,p+len+1,cmp);
    for(int k=1;k<=n;k++){
        ans=abs(a[k]);
        memset(v,0,sizeof(v));
        for(int i=1;i<=k;i++)
            for(int j=k;j<=n;j++)v[i][j]=1;
        for(int i=1;i<len;i++)
            if(v[p[i].l][p[i].r]!=v[p[i+1].l][p[i+1].r])ans=min(ans,p[i+1].sum-p[i].sum);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：chenhanzheapple (赞：2)

# [传送门](https://www.luogu.com.cn/problem/P9127)

------------

思路：我们可以对所有区间按区间和排序，然后对于每一个 $i$，枚举所有区间，如果这个编号为 $j$ 的区间包含 $i$，那么对于和 ta 相差最近的两个就有可能是答案（就是编号 $j-1$ 的区间和编号 $j+1$ 的区间）对于所有这样的两个区间的区间和与那个包含 $i$ 的区间作差并取 $\min$ 的值就是答案。注意，这两个区间不能包含 $i$，想一想为什么。

时间复杂度：$O(n^3)$，有一点点常数。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[505],sum[505];
struct node{
    int l,r,x;
};
vector<node> v,p[505];
bool cmp(node x,node y){
    return x.x<y.x;
}
signed main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        sum[i] = sum[i-1]+a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            v.push_back((node){i,j,sum[j]-sum[i-1]});//把每个区间插进vector里，用前缀和来计算区间和（事实上不用应该也没关系）
        }
    }
    sort(v.begin(),v.end(),cmp);//按区间和排序
    for(int i=1;i<=n;i++){
        int minn = LONG_LONG_MAX;
        for(int j=0;j<v.size();j++){//枚举区间
            if(v[j].l<=i && v[j].r>=i){//如果区间包含i，那么处理
                if(j-1>=0 && !(v[j-1].l<=i && v[j-1].r>=i)){//前面的区间
                    minn = min(minn,v[j].x-v[j-1].x);
                }
                if(j+1<v.size() && !(v[j+1].l<=i && v[j+1].r>=i)){//后面的区间
                    minn = min(minn,v[j+1].x-v[j].x);
                }
            }
        }
        cout << minn << endl;
    }
    return 0;
}

```

---

## 作者：yzh_Error404 (赞：2)

比较神秘的一道题。

虽然 $O(n^3)$ 可以过，但是我写了 $O(n^2\log n)$ 的方法。

首先我们把每个子区间的左右端点以及和求出来。

显然对于一个区间，能够和它作为一个位置的答案的区间只有左右两个，所以按照和排序即可。

因为没有两个区间的和是相等的，所以对于一个位置，变得相等的两个区间显然不能同时包含这个位置（同时不包含显然也不行），所以对于两个区间，可以更新的部分就是仅出现一次的部分（区间并去掉区间交），维护更新的最小值即可。

需要支持的操作有区间修改，单点查询，用的是线段树。

对于两个区间中可以修改的部分，我分了三种情况来考虑：相离，包含和相交，看代码应该能看懂。

代码实现：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2005;
const int INF=0x7f7f7f7f7f7f7f7f;
struct node
{
    int l,r,val;
}e[MAXN*MAXN];
int cnt;
inline bool cmp(node a,node b)
{
    return a.val<b.val;
}
int n;
int a[MAXN],sum[MAXN];
inline int get(int l,int r)
{
    return sum[r]-sum[l-1];
}
int t[MAXN*MAXN<<4],tag[MAXN*MAXN<<4];
inline void pushup(int p)
{
    t[p]=min(t[p<<1],t[p<<1|1]);
}
inline void addtag(int p,int k)
{
    t[p]=min(t[p],k);
    if(tag[p]==-INF)tag[p]=k;
    else tag[p]=min(tag[p],k);
}
inline void pushdown(int p,int l,int r)
{
    if(tag[p]!=-INF)
    {
        if(l==r)return;
        addtag(p<<1,tag[p]);
        addtag(p<<1|1,tag[p]);
        tag[p]=-INF;
    }
}
inline void build(int p,int l,int r)
{
    tag[p]=-INF;
    if(l==r)return t[p]=INF,void();
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    pushup(p);
}
inline void change(int p,int l,int r,int a,int b,int k)
{
    if(a>b)return;
    if(r<a||l>b)return;
    if(l>=a&&r<=b)return addtag(p,k),void();
    int mid=(l+r)>>1;
    pushdown(p,l,r);
    change(p<<1,l,mid,a,b,k);
    change(p<<1|1,mid+1,r,a,b,k);
    pushup(p);
}
inline int ask(int p,int l,int r,int k)
{
    if(r<k||l>k)return INF;
    if(l==r)return t[p];
    int mid=(l+r)>>1;
    pushdown(p,l,r);
    return min(ask(p<<1,l,mid,k),ask(p<<1|1,mid+1,r,k));
}
signed main()
{
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
    }
    for(register int i=1;i<=n;i++)
        for(register int j=i;j<=n;j++)
            e[++cnt]=(node){i,j,get(i,j)};
    sort(e+1,e+1+cnt,cmp);
    build(1,1,n);
    for(register int i=1;i<cnt;i++)
    {
        node l=e[i],r=e[i+1];
        int now=r.val-l.val;
        if(l.l>r.l)swap(l,r);
        if(l.r<r.l)//相离
        {
            change(1,1,n,l.l,l.r,now);
            change(1,1,n,r.l,r.r,now);
        }
        else if(l.r>r.r)//包含
        {
            change(1,1,n,l.l,r.l-1,now);
            change(1,1,n,r.r+1,l.r,now);
        }
        else//相交
        {
            change(1,1,n,l.l,r.l-1,now);
            change(1,1,n,l.r+1,r.r,now);
        }
    }
    for(register int i=1;i<=n;i++)
        printf("%lld\n",ask(1,1,n,i));
    return 0;
}
                                                            
```

---

## 作者：H_Kaguya (赞：2)

这里提供一个 $O(N^2 \log N)$ 的解法。  

先考虑一个暴力的思路。  

对于位置 $i$ 的修改，所有包含 $i$ 位置的子区间都会变，所以最后一定是一个包含 $i$ 的子区间和一个不包含 $i$ 的子区间相等。  
我们把每个子区间的和都放到一个 `set` 里面。  
查询一个点的答案，就把这个点所在的子区间从 `set` 里面 `erase()` 掉，然后枚举这个点所在的子区间，在 `set` 里面查找前驱后继，选差值的最小值作为答案。  
每个点所在的子区间是 $O(N^2)$ 级别的，所以总复杂度 $O(N^3 \log N)$。  

有点差，接着优化。  

我们按照相等的子区间的位置关系进行分类。  
首先考虑有交而不包含的情况。  
如果修改之后 $[a, b]$ 和 $[c, d]$ 的和相等，并且 $[a, b], [c, d]$ 有交（设 $a \le c \le b \le d$ ），那么我们把中间的交集去掉，剩下的两部分依然相等（即 $[a, c)$ 和 $(b, d]$ ）。  
因此，所有有交而不包含的情况都可以归纳到无交的情况。  

接下来考虑包含的情况。  
如果 $[a, b]$ 和 $[c, d]$ 的和相等，且 $a \le c \le d \le b$，则我们发现 $[a, c), (b, d]$ 的和互为相反数。  
同样可以归纳到无交的情况。  

剩下的就是一些特殊情况，比如将一个数修改为 $0$，或者将一个子区间修改为 $0$。  
特判一下即可。  

因此直接进行类似于扫描线的操作。  
顺序枚举端点 $i$，将 $i$ 之前的不包含 $i$ 的子区间全都扔到一个 `set` 里面，然后枚举端点 $j$，在 `set` 里面查询 $[i, j]$ 的前驱后继，并将答案更新到 $[i, j]$ 的每一个位置上。  
正反各跑一遍即可。  
可以倒着枚举 $j$ 直接更新答案，然后本蒟蒻脑抽了，跑了一个线段树 ~~（不过至少不影响复杂度）~~。  

每个区间只会进入 `set` 一次，`lower_bound()` 一次，所以总复杂度是 $O(N^2 \log N)$。  

贴一个大常数的赛时代码~  

```cpp
//..........
//wa da shi, ba ka
#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define sz 505
typedef long long ll;
const ll inf = 1e18;
int n;
ll num[sz], ans[sz << 1 | 1];
set<ll> st;
ll read();
void renew(ll, int, int);
void rew(ll, ll, int, int);
void build(int, int, int);
void fix(int, int, int, int, int, ll);
void dfs(int, int, int, ll);
int main()
{
	ll y;
	n = read(); build(0, 1, n);
	for (int i = 1; i <= n; ++i)
		num[i] = read();
	for (int i = 1; i <= n; ++i)
		ans[i] = inf;
	for (int i = 1; i <= n; ++i)
		fix(0, 1, n, i, i, abs(num[i]));
	if (n != 2)
	{
		for (int i = 1; i <= n; ++i)
			st.insert(num[i]);
		for (int i = 1; i <= n; ++i)
			renew(-num[i], i, i);
		st.clear();
	}
	st.insert(num[1]);
	ll c = num[1];
	for (int i = 2; i <= n; ++i)
	{
		y = 0LL;
		for (int j = i; j <= n; ++j)
		{
			y += num[j];
			renew(y, i, j);
			fix(0, 1, n, i, j, abs(y));
			if (j == n)
				rew(-y, c, i, j);
			else
				renew(-y, i, j);
		}
		y = 0LL;
		for (int j = i; j; --j)
		{
			y += num[j];
			st.insert(y);
		}
		c += num[i];
	}
	st.clear();
	st.insert(num[n]);
	c = num[n];
	for (int i = n - 1; i; --i)
	{
		y = 0LL;
		for (int j = i; j; --j)
		{
			y += num[j];
			renew(y, j, i);
			fix(0, 1, n, j, i, abs(y));
			if (j == 1)
				rew(-y, c, j, i);
			else
				renew(-y, j, i);
		}
		y = 0LL;
		for (int j = i; j <= n; ++j)
		{
			y += num[j];
			st.insert(y);
		}
		c += num[i];
	}
	dfs(0, 1, n, inf);
	return 0;
}

ll read()
{
	ll x = 0LL;
	char c = getchar(), f = 0;
	while (c < '0')
	{
		f = (c == '-');
		c = getchar();
	}
	do {
		x = x * 10LL + (c & 15);
		c = getchar();
	}while (c >= '0');
	return f ? -x : x;
}

void renew(ll a, int lf, int rt)
{
	auto x = st.lower_bound(a);
	if (x != st.end())
	{
		fix(0, 1, n, lf, rt, abs(a - *x));
	}
	if (x != st.begin())
	{
		--x;
		fix(0, 1, n, lf, rt, abs(a - *x));
	}
}

void rew(ll a, ll b, int lf, int rt)
{
	auto x = st.lower_bound(a);
	if (x != st.end())
	{
		if (*x == b)
		{
			++x;
			if (x != st.end())
				fix(0, 1, n, lf, rt, abs(a - *x));
			--x;
		}else
			fix(0, 1, n, lf, rt, abs(a - *x));
	}
	if (x != st.begin())
	{
		--x;
		if (*x == b)
		{
			if (x != st.begin())
			{
				--x;
				fix(0, 1, n, lf, rt, abs(a - *x));
			}
		}else
			fix(0, 1, n, lf, rt, abs(a - *x));
	}
}

void build(int a, int lf, int rt)
{
	ans[a] = inf;
	if (lf == rt)
		return;
	int mid = lf + rt >> 1;
	build(mid << 1, lf, mid);
	build(mid << 1 | 1, mid + 1, rt);
}

void fix(int a, int lf, int rt, int wa, int wb, ll b)
{
	if (ans[a] <= b)
		return;
	if (lf == wa && rt == wb)
	{
		ans[a] = b;
		return;
	}
	int mid = lf + rt >> 1;
	if (wb <= mid)
		fix(mid << 1, lf, mid, wa, wb, b);
	else if (wa > mid)
		fix(mid << 1 | 1, mid + 1, rt, wa, wb, b);
	else
	{
		fix(mid << 1, lf, mid, wa, mid, b);
		fix(mid << 1 | 1, mid + 1, rt, mid + 1, wb, b);
	}
}

void dfs(int a, int lf, int rt, ll b)
{
	b = min(b, ans[a]);
	if (lf == rt)
	{
		printf ("%lld\n", b);
		return;
	}
	int mid = lf + rt >> 1;
	dfs(mid << 1, lf, mid, b);
	dfs(mid << 1 | 1, mid + 1, rt, b);
}

```


---

## 作者：hanjinghao (赞：2)

# 题意：

给定一个长度为 $ n $ 的序列，保证任意两个连续子序列的元素和不相等。对于每一个元素，你需要回答这个问题：如果只修改这个元素，使得存在两个连续子序列的元素和相等，那么这个元素的改变量最少是多少？

# 思路：

对于一个元素，要修改它的值，使得存在两个连续子序列的元素和相等，实际上就是要使得某个包含它的子序列的元素和等于某个不包含它的子序列的元素和。原因很显然：如果两个子序列都不包含这个元素，那么这个元素的修改和两个子序列都没有关系。如果两个子序列都包含这个元素，那么不管这个元素怎么修改，两个子序列的元素和之差都不会改变，一开始不相等，改了以后也不会相等。因此，满足条件的只有一个包含、一个不包含。

我们一开始先把所有连续子序列按照元素和从小到大排序。接下来枚举 $ i $，对于每一个包含 $ i $ 的子序列，求出元素和小于它并且不包含 $ i $ 的子序列中，元素和最大是多少，以及元素和大于它并且不包含 $ i $ 的子序列中，元素和最小是多少。用打擂法即可求出答案。

时间复杂度为 $ O(n ^ 3) $

# 核心代码：

```cpp
const int N = 505;
long long n, a[N], s[N], ans[N], lft[N * N], rgh[N * N];
pair < long long, pair < int, int > > b[N * N];

int main()
{
	read(n);
	for (int i = 1; i <= n; ++i)
		read(a[i]), s[i] = s[i - 1] + a[i];
	int len = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j)
			b[++len] = make_pair(s[j] - s[i - 1], make_pair(i, j));
	sort(b + 1, b + len + 1);
	memset(ans, 0x3f, sizeof(ans));
	for (int i = 1; i <= n; ++i)
	{
		lft[1] = 0;
		for (int j = 2; j <= len; ++j)
			if (b[j].second.first <= i && b[j].second.second >= i)
			{
				if (b[j - 1].second.first <= i && b[j - 1].second.second >= i) lft[j] = lft[j - 1];
				else lft[j] = j - 1;
			}
			else lft[j] = 0;
		rgh[len] = 0;
		for (int j = len - 1; j; --j)
			if (b[j].second.first <= i && b[j].second.second >= i)
			{
				if (b[j + 1].second.first <= i && b[j + 1].second.second >= i) rgh[j] = rgh[j + 1];
				else rgh[j] = j + 1;
			}
			else rgh[j] = 0;
		for (int j = 1; j <= len; ++j)
		{
			if (lft[j]) ans[i] = min(ans[i], llabs(b[j].first - b[lft[j]].first));
			if (rgh[j]) ans[i] = min(ans[i], llabs(b[j].first - b[rgh[j]].first));
		}
	}
	for (int i = 1; i <= n; ++i)
		writeln(ans[i]);
	return 0;
}
```

---

## 作者：Hell0_W0rld (赞：2)

# [Equal Sum Subarrays G](https://www.luogu.com.cn/problem/P9127) 题解
## 题目大意
给定一个序列 $A=(a_1,a_2,\dots,a_n)$，满足子段和两两不相同。有 $n$ 个问询，第 $i$ 个问询要求求最小的 $d$，使得将 $a_i$ 加 $d$ 或减 $d$，序列 $A$ 中有子段和相同的两个不同子段？
## Solution
感觉不需要什么部分分啊。

我们发现，对于**任意两个不相同子段**，例如 $[l_1,r_1]$ 和 $[l_2,r_2]$，我们用 $s_1$ 和 $s_2$ 表示这两个子段的总和。并且我们认为两个区间并集为 $S$，交集为 $T$。

这样的话，我们发现：

对于所有满足 $i \in \complement_{S}T$ 的 $i$，$a_i$ 可以通过 $\pm \lvert s_1-s_2\rvert$ 得到相等的两个子段：$s_1=s_2$，满足条件。注意对于满足 $i\in T$ 的 $i$ 是不满足条件的，因为它的加减会使 $s_1,s_2$ 同时变化。

于是我们可以得出算法：
+ 我们可以枚举任意两个子段。
+ 更新答案。设子段编号 $a,b$，执行 `tag(a,b)`。

如何更新答案（我把它封装在 `tag(a,b)` 里）：
+ 我们用一个数组，标记 $C_k$ 表示 $k$ 号被覆盖了几次。对于 $C_k$ 为 $1$ 的点，我们用 $s_a-s_b$ 更新 $k$ 号点的答案。
+ $s_i$ 表示第 $i$ 个子段的子段和。
+ 记得清空数组。

但是复杂度 $O(n^5)$，无法接受。

注意到我们可以把子段和按从大到小排序，这样只需要考虑相邻的子段即可。证明显然，其他都是不必要更新。

这样算法变成这样：
+ 我们提取所有子段和，放在数组里并排序。
+ 对于相邻子段 $i,i+1$，执行 `tag(i,i+1)`。

这样这题就做完啦？是的。复杂度：$O(N^2\log N^2+N^3)$,前面是排序后面是更新答案。

## 赛场代码
赛时脑残跑了 `tag(i-1,i)` 和 `tag(i,i+1)`，仅做参考。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define repD(i,u,E) for(register ll i=hd[u];i;i=E[i].nxt)
#define all(x) x.begin(),x.end()
using namespace std;
void upd_s(ll&x,ll v){x=min(x,v);}
void upd_b(ll&x,ll v){x=max(x,v);}
const ll N=509,INF=8e18;
ll n,a[N],ans[N],sum[N];
struct Node{
	ll l,r,x;
	bool operator<(const Node&a)const{
		return x<a.x;
	}
}xx[N*N];
vector<ll> ADD[N],RMV[N];
bool bj[N];
void tag(ll a,ll b,ll v){
	memset(bj,0,sizeof(bj));
	ll l=xx[a].l,r=xx[a].r;
	rep(i,l,r)bj[i]^=1;
	l=xx[b].l,r=xx[b].r;
	rep(j,l,r)bj[j]^=1;
	rep(i,1,n)if(bj[i])ans[i]=min(ans[i],v);
}
int main(){
	cin>>n;
	rep(i,1,n)cin>>a[i],sum[i]=sum[i-1]+a[i];
	ll cnt=0;
	rep(i,1,n)rep(j,i,n){
		ll x=sum[j]-sum[i-1];
		xx[++cnt]=(Node){i,j,x};
	}
	sort(xx+1,xx+1+cnt);
	fill(ans,ans+1+n,INF);
	rep(i,1,cnt){
		ll nw=INF,id=0;
		if(i!=1){
			ll cost=xx[i].x-xx[i-1].x;
			tag(i-1,i,cost);
		}
		if(i!=cnt){
			ll cost=xx[i+1].x-xx[i].x;
			tag(i,i+1,cost);
		}
	}
	rep(i,1,n)cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：ztrztr (赞：1)

## 题意概括
由于简化版的翻译已经很明显了，就不再多加说明了。
## 思路
### $24$ pts
这里提供一种虽然时间复杂度是 $O(n^5)$，但是常数比较小的方法。
我们从 $1$ 到 $n$ 遍历每个 $i$，然后对于每个 $i$ 可以枚举两个区间，要求其中一个区间含有 $i$，一个没有。

第一个区间为 $[l1, r1]$，那么我们对于 $l1$ 可以只枚举 $[1, i]$，$l2$ 枚举 $[i, n]$。

第二个区间为 $[l2, r2]$，那么我们只用枚举 $[1, i)$ 和 $[l2, i)$ 或者 $(i, n]$ 和 $[l2, n)$。
### $100$ pts
由于 $n$ 最大为 $500$，那么 $O(n^3)$ 的复杂度可以过。我们可以把所有的区间之和都全存下来，然后按区间和的大小从小到大或者从大到小进行排序。因为排序后可以得出有着最小的区间和之差的两个区间肯定是在排序后是相邻的。

我们可以遍历每个 $i$，然后对于每两个相邻的合法区间对取差的最小值。一对合法的区间定义为一个区间含有 $i$，而另一个没有 $i$。因为只有这样才能保证一个改了后另一个没改，使得区间和之差改变。不然如果两个区间都含有 $i$ 或者都没有 $i$，那么两个区间和都增加相同的量或者都不变，就没有意义了。

## 代码
### $24$ pts
```cpp
#include <bits/stdc++.h>

using namespace std;
/*
*/
#define int long long
int n, a[1000005], s[100005], ss[505][505];
signed main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    // if (n > 80) return 0;
    for (int i = 1; i <= n; i ++) cin >> a[i], s[i] = s[i - 1] + a[i];
    for (int i = 1; i <= n; i ++) {
        int minn = 1e18;
        for (int j = 1; j <= i; j ++) {
            for (int k = i; k <= n; k ++) {
                for (int J = 1; J < i; J ++) {
                    for (int K = J; K < i; K ++) {
                        int sum1 = s[k] - s[j - 1];
                        int sum2 = s[K] - s[J - 1];
                        // cout << j << " " << k << " " << J << " " << K << " " << sum1 << " " << sum2 << "\n";
                        minn = min(minn, abs(sum2 - sum1));
                    }
                }
                for (int J = i + 1; J <= n; J ++) {
                    for (int K = J; K <= n; K ++) {
                        int sum1 = s[k] - s[j - 1];
                        int sum2 = s[K] - s[J - 1];
                        // cout << j << " " << k << " " << J << " " << K << " " << sum1 << " " << sum2 << "\n";
                        minn = min(minn, abs(sum2 - sum1));
                    }
                }
            }
        }
        cout << minn << "\n";
    }
    return 0;
}
```
### $100$ pts
```cpp
#include <bits/stdc++.h>

using namespace std;
/*
*/
#define int long long
int n, a[100005], s[100005];
struct node{
    int x, y, v;
    bool operator <(node nn) const {
        return v < nn.v;
    }
} ss[250005];
int tot = 0;
bool cmp(node x, node y) {return x.v < y.v;}
signed main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    freopen("out2.out", "w", stdout);
    cin >> n;
    // if (n > 80) return 0;
    for (int i = 1; i <= n; i ++) cin >> a[i], s[i] = s[i - 1] + a[i];
    for (int i = 1; i <= n; i ++) {
        for (int j = i; j <= n; j ++) {
            ss[++ tot] = (node){i, j, s[j] - s[i - 1]};
        }
    }
    
    sort(ss + 1, ss + tot + 1, cmp);
//    for (int i = 1; i <= tot; i ++) cout << ss[i].v << "\n";
    for (int i = 1; i <= n; i ++) {
        int minn = 1e18;
        for (int j = 2; j <= tot; j ++) {
            int l1 = ss[j].x, r1 = ss[j].y, l2 = ss[j - 1].x, r2 = ss[j - 1].y;
            bool b1 = (l1 <= i && i <= r1), b2 = (l2 <= i && i <= r2);
            if (b1 == !b2) minn = min(minn, abs(ss[j].v - ss[j - 1].v));

        }
        cout << minn << "\n";
    }
    return 0;
}
```

---

## 作者：学委 (赞：1)

这里提供一种代码简单且效率较高的做法。

- 题意：问修改 $a_i$ 绝对值至少多少可以让数列中两个连续子串和不同。

考虑所有连续子串，按和从小到大排序。

![](https://cdn.luogu.com.cn/upload/image_hosting/h0sd3pew.png)

上图每一个竖线表示一个子段和，对于 $i$，红色线表示包含 $i$ 的子段，绿色线表示不包含 $i$ 的子段。

题意转换为移动红线到绿线所需的最小代价。因此只需要考虑移动大小排序相邻的子段。

从上面思路重新思考题目，先按和的大小排序所有子段。从小到大考虑两个相邻子段：对于那些 **只被其中一个子段包含** 的 $i$ 可以更新其答案，代价为这两个相邻子段的差的绝对值。（对于被两个子段同时包含的 $a_i$，修改 $a_i$ 并不能改变两个子段的差。 

复杂度 $O(n ^ 2 log (n ^ 2))$.

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 510;
const int M = N * N / 2;
int n;
ll a[N], sum[N], ans[N];
struct Seg {
    int l, r;
    ll sum;
    Seg() {}
    Seg(int l, int r, ll sum): l(l), r(r), sum(sum) {}
    bool operator<(const Seg& rhs) const {
        return sum < rhs.sum;
    }
} seg[M];
int cnt = 0;
const ll inf = 1e18;

bool bet(ll x, ll l, ll r) {
    return x >= l && x <= r;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
        ans[i] = inf;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j++) {
            seg[++cnt] = Seg(i, j, sum[j] - sum[i - 1]);
        }
    }
    // 先按和的大小排序所有子段。
    sort(seg + 1, seg + cnt + 1);
    for (int i = 1; i <= cnt - 1; i++) {
        // 只需要考虑相邻子段
        Seg seg1 = seg[i], seg2 = seg[i + 1];
        ll del = abs(seg2.sum - seg1.sum);
        for (int j = min(seg1.l, seg2.l); j <= max(seg1.r, seg2.r); ++j) {
            // 对于那些 **只被其中一个子段包含** 的 $i$ 可以更新其答案，代价为这两个相邻子段的差的绝对值。（对于被两个子段同时包含的 $a_i$，修改 $a_i$ 并不能改变两个子段的差。
            if (bet(j, seg1.l, seg1.r) && bet(j, seg2.l, seg2.r))
                continue;
            if (!bet(j, seg1.l, seg1.r) && !bet(j, seg2.l, seg2.r))
                continue;
            ans[j] = min(ans[j], del);
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
```


---

## 作者：lsj2009 (赞：1)

## Solution

看了眼 Luogu 题解区，大多是 $\Theta(n^3)$ 的做法，这里给出一个 $\Theta(n^2\log{n^2})$ 的做法。

- 结论：对于两个连续子序列 $a_{l_1\cdots r_1}$ 和 $a_{l_2\cdots r_2}$ 如果要通过改变 $a_k$ 可以使两者和相等，那么当且仅当 $[k\in[l_1,r_1]]\neq [k\in[l_2,r_2]]$。
- 证明：将两者作差得 $d=(\sum\limits_{i=l_1}^{r_1} a_i)-(\sum\limits_{i=l_2}^{r_2} a_i)$。然后分类讨论：
- 当 $k\notin[l_1,r_1]$ 且 $k\notin[l_2,r_2]$，$a_k$ 的改变并不影响 $d$ 的改变。
- 当 $k\in[l_1,r_1]$ 且 $k\notin[l_2,r_2]$，令 $a_k\gets a_k-d$ 即可。
- 当 $k\notin[l_1,r_2]$ 且 $k\in[l_2,r_2]$，令 $a_k\gets a_k+d$ 即可。
- 当 $k\in[l_1,r_2]$ 且 $k\in[l_2,r_2]$，$a_k$ 的改变使减号两边同时产生了一个相等偏移量，所以 $d$ 不变。

那么对于每个 $i$ 我们可以考虑开两个数组，一个存含 $i$ 的区间的值，一个存不含 $i$ 的区间的值，那么两个数组最小的两个元素之差的绝对值即为所求。这样直接暴力去做、统计复杂度应为 $\Theta(n\times n^2\times n^4)$，非常之大。考虑优化：

- 容易发现从节点 $i$ 到节点 $i+1$ 的过程中，所包含或不包含他们的区间是有一部分重合的；具体而言，是 $\{[l,i]\mid 1\le l\le i\}$ 和 $\{[i+1,r]\mid i+1\le r\le n\}$。则我们可以开两个集合，一个保存包含 $i$ 的区间，一个保存不包含的，那么对于每一次转移的过程中只需在原有的保存包含和不包含的区间的集合中加减即可。这样复杂度也就优化到了 $\Theta(n\times n\times n^4)$。
- 可以发现，时间复杂度主要花费在了后面 $\Theta(n^4)$ 的计算最小值当中。我们先考虑这么一个问题：将两个集合变成同一个集合，求该集合两两元素之间的最小的差？
- 容易发现，当我们将所有元素按从小到大排序后，我们只需要计算两两相邻元素之差即可，正确性显然。然后我们把他加上一个在线修改、查询操作，也就是 CF1418D，这里不再赘述。
- 回到原题目，和 CF1418D 的差距也就是要区分两个集合，那么我们只需要再加上一个参数表示属于哪个集合即可，修改判断与他相邻的数是否和它属于相同集合，正确性同样显然。这样复杂度就是 $\Theta(n^2\log{n^2})$。

然后就做完了。

## Code

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define int long long
#define PII pair<int,int>
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=5e2+5;
multiset<int> s1;
multiset<PII> s2;
int sum[N],a[N];
void delone(multiset<int>& s,int x) {
	auto it=s.find(x); s.erase(*it);
}
void del(PII x) {
	auto it=s2.lower_bound(x);
	auto a=++it; --it;
	if(a!=s2.end()) {
		if((*a).second!=(*it).second)
			delone(s1,(*a).first-(*it).first);
	}
	if(it!=s2.begin()) {
		auto b=--it; ++it;
		if((*b).second!=(*it).second)
			delone(s1,(*it).first-(*b).first);
		if(a!=s2.end()) {
			if((*a).second!=(*b).second)
				s1.insert((*a).first-(*b).first);
		}
	}
	s2.erase(it);
}
void ins(PII x) {
	auto it=s2.lower_bound(x); 
	if(it!=s2.end()) {
		if((*it).second!=x.second)
			s1.insert((*it).first-x.first);
	}
	if(it!=s2.begin()) {
		auto a=--it; ++it;
		if((*a).second!=x.second)
			s1.insert(x.first-(*a).first);
		if(it!=s2.end()) {
			if((*a).second!=(*it).second)
				delone(s1,(*it).first-(*a).first);
		}
	}
	s2.insert(x);
}
signed main() {
	int n;
	scanf("%lld",&n);
	rep(i,1,n)
		scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
	rep(i,1,n) {
		rep(j,i,n)
			ins({sum[j]-sum[i-1],0});
	}
	rep(i,1,n) {
		ins({sum[i],1}); del({sum[i],0});
	}
	rep(k,1,n) {
		printf("%lld\n",*s1.begin());
		rep(i,1,k) {
			del({sum[k]-sum[i-1],1}); ins({sum[k]-sum[i-1],0});
		}
		rep(i,k+1,n) {
			del({sum[i]-sum[k],0}); ins({sum[i]-sum[k],1});
		}
	}
	return 0;
}
```

---

## 作者：MrPython (赞：0)

我来教大家如何打暴力。

首先，根据题面，假设我们当前要修改第 $i$ 个数。如果两个区间都包含 $i$，此时无论做何修改差都不变，都不包含同理。因此，我们找的两个区间应为：其中一个包含第 $i$ 项，而另一个不含。

由于 $n$ 非常小，我想到将所有符合条件的区间和都存下来，这个过程预处理出来或者套个前缀和都可以。之后，就是在两个数组中找绝对值差最小。排个序然后双指针搞一下就可以。

使用 `std::sort` 的时间复杂度为 $O(n^3\log n)$，还是很难通过。我经过简单的卡常拿到了 3.07s 的好成绩。于是我一怒之下换成基数排序就过了。

```cpp
#include <bits/extc++.h>
using namespace std;
namespace pbds = __gnu_pbds;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
template <typename T> class PrefixSum {
  vector<T> sum;

 public:
  template <typename InputIterator, typename = _RequireInputIter<InputIterator>>
  PrefixSum(InputIterator begin, size_t n): sum(n + 1) {
    typename vector<T>::iterator it = next(sum.begin());
    *(it++) = *begin;
    for (size_t i = 1; i < n; ++i, ++it) *it = *prev(it) + *++begin;
  }
  T get_sum(size_t m, size_t n) { return sum[n] - sum[m]; }
  T get_val(size_t m) { return get_sum(m, m + 1); }
  T operator[](size_t m) { return get_val(m); }
  size_t size(void) { return sum.size(); }
};
// 我的基数排序模板仅支持无符号整数，因此有全部加一个偏移量到正数
template <typename ForwardIterator,
          typename = is_unsigned<typename ForwardIterator::value_type>>
void radixSort(ForwardIterator first, ForwardIterator last) {
  constexpr ui P = 8;
  constexpr size_t T =
      numeric_limits<typename ForwardIterator::value_type>::digits / P;
  size_t n = distance(first, last);
  ui W = 0;
  auto* dat = new typename ForwardIterator::value_type[n];
  for (size_t i = 0; i < T; ++i, W += P) {
    array<size_t, 1u << P> cnt{};
    for_each(first, last, [&](typename ForwardIterator::reference const x) {
      ++cnt[(x >> W) & ((1u << P) - 1)];
    });
    partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    rotate(cnt.begin(), prev(cnt.end()), cnt.end()), cnt[0] = 0;
    for_each(first, last, [&](typename ForwardIterator::reference const x) {
      dat[cnt[(x >> W) & ((1u << P) - 1)]++] = x;
    });
    copy(dat, dat + n, first);
  }
  delete[] dat;
}
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n;
  fin >> n;
  vector<li> a(n);
  for (li& i : a) fin >> i;
  PrefixSum<li> p(a.begin(), n);
  for (size_t i = 0; i < n; ++i) {
    vector<uli> s, t;
    for (size_t j = 0; j < i; ++j)
      for (size_t k = j; k < i; ++k)
        s.emplace_back((uli)p.get_sum(j, k + 1) - numeric_limits<li>::min());
    for (size_t j = i + 1; j < n; ++j)
      for (size_t k = j; k < n; ++k)
        s.emplace_back((uli)p.get_sum(j, k + 1) - numeric_limits<li>::min());
    uli ans = numeric_limits<uli>::max();
    for (size_t j = 0; j <= i; ++j)
      for (size_t k = i; k < n; ++k)
        t.emplace_back((uli)p.get_sum(j, k + 1) - numeric_limits<li>::min());
    radixSort(s.begin(), s.end()), radixSort(t.begin(), t.end());
    vector<uli>::iterator it = s.begin();
    for (uli i : t) {
      while (it != s.end() && *it < i) ++it;
      if (it != s.end()) ans = min(ans, *it - i);
      if (it != s.begin()) ans = min(ans, i - *prev(it));
    }
    fout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：WisNourx_ (赞：0)

和楼上邓鸭子的做法很像。

## 题目分析
非常明显的性质是任意两个区间之间的和总会不相同。

题目要求求出对于每个数的最小修改值，可以想到排序之后对于每个数找到一个包含这个数的区间和一个不包含这个数的区间，计算答案。

可这样做是会超时的，于是考虑优化。

根据性质不难发现，排序后相邻两个区间的和总会不相同。

由此我们想到一种做法：求出所有区间和后排序，计算相邻两个只出现一次的数的最小修改值（也就是对两区间内不交的数计算答案）。

总共有 $\frac{n(n+1)}{2}$ 个区间，所以总共计算了 $\frac{n^2+2n-2}{2}$ 次。要求每个数至少被计算一次，而 $\frac{n^2+2n-2}{2} - n =\frac{n^2+2n-2}{2} - \frac{2n}{2} = \frac{n^2-2}{2}$ 且 $2 \leq n \leq 500$，因此原式始终大于 $0$，即 $\frac{{n^2+2n-2}}{2} > n$，每个数至少会被计算一次。

时间复杂度为 $\mathcal O(n^3)$，可以通过。代码如下。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<cmath>
#include<unordered_map>
#define int long long
using namespace std;

char buf[1<<20], *p1=buf, *p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf, 1, 1<<20, stdin), p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x)
{
	x=0;int f=1;char c=getchar();
	while (!isdigit(c)) f=(c=='-')?-1:1, c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+c-'0', c=getchar();
	x*=f;
}

typedef long long LL;
const int N=510;
int n, a[N], sum[N], len, v[N], ans[N];
struct node{int l, r, v;}q[N*N];
bool cmp(node n1, node n2) {return n1.v<n2.v;}

signed main()
{
	read(n);
	memset(ans, 0x3f, sizeof ans);
	for (int i=1;i<=n;i++) 
	{
		read(a[i]);
		sum[i]+=sum[i-1]+a[i];
		for (int j=1;j<=i;j++) q[++len]={j, i, sum[i]-sum[j-1]};
	}
	sort(q+1, q+len+1, cmp);
	for (int i=2;i<=len;i++)
	{
		for (int j=q[i].l;j<=q[i].r;j++) v[j]^=1;
		for (int j=q[i-1].l;j<=q[i-1].r;j++) v[j]^=1;
		for (int j=1;j<=n;j++) if (v[j]) ans[j]=min(ans[j], abs(q[i].v-q[i-1].v)), v[j]=0;
	}
	for (int i=1;i<=n;i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：DengStar (赞：0)

> [题目链接](https://www.luogu.com.cn/problem/P9127)

## $O(n^5)$ 暴力

显然，如果修改 $a_i$ 的值，只会影响包含 $a_i$ 的区间的区间和。于是对于每个 $a_i$，可以将所有区间分成两类，即包含 $a_i$ 的区间和不包含 $a_i$ 的区间。这两种区间的区间和中最小的差值即为答案。

对于每个 $a_i$，暴力枚举所有的区间和是 $O(n^2)$ 的（这里可以用前缀和快速求出区间和）；枚举两类区间的差值是 $O(n^4)$ 的——注意区间的个数是 $O(n^2)$ 量级的，双层的遍历就是 $O(n^4)$。乘上外层枚举 $a_i$ 的循环，总的时间复杂度为 $O(n^5)$。

部分代码如下：

```cpp
// s1[]：包含 a[i] 的区间和，s2[]：不包含 a[i] 的区间和
// top1 和 top2 分别表示 s1[] 和 s2[] 当前的元素个数
for(int i = 1; i <= n; i++)
{
    top1 = top2 = 0, ans = INF;
    for(int j = 1; j <= n; j++)
    {
        for(int k = j; k <= n; k++) // 枚举 [j, k] 区间
        {
            ll s = sum[k] - sum[j-1];
            if(j <= i && k >= i) s1[++top1] = s; // 判断该区间是否包含 a[i]
            else s2[++top2] = s;
        }
    }
    for(int i = 1; i <= top1; i++) // O(n^4) 暴力枚举差值
        for(int j = 1; j <= top2; j++) ans = min(ans, abs(s1[i] - s2[j]));
    printf("%lld\n", ans);
}
```

## $O(n^3 \log (n^2))$

上面这种做法中用 $O(n^4)$ 暴力枚举差值实在太过愚蠢了。考虑优化这一步。

先将 ```s1[],s2[]``` 排序，然后使用双指针法，这样只要遍历一遍，时间复杂度降低到 $O(n^2)$。

这部分代码如下：

```cpp
sort(s1 + 1, s1 + top1 + 1), sort(s2 + 1, s2 + top2 + 1);
int p1 = 1, p2 = 1; // p1 和 p2 分别是 s1[] 和 s2[] 的指针
s2[top2+1] = INF; // 由于双指针法可能取到 s2[top2+1]，需要先将其设为无穷大
for(p1; p1 <= top1; p1++)
{
    while(s2[p2+1] <= s1[p1] && p2 < top2) p2++;
    ans = min({ans, abs(s2[p2] - s1[p1]), abs(s2[p2+1] - s1[p1])});
    // s2[p2] 是 s2[] 中小于等于 s1[p1] 的最大的数，s2[p2+1] 是 s2[] 中大于 s1[p1] 的最小的数
    // 由于 s1[] 和 s2[] 都是升序的，所以与 s1[p1] 差值最小的数一定在这两者之中 
}
```

给 $n^2$ 个数排序是 $O(n^2 \log (n^2))$ 的，双指针法是 $O(n^2)$，总的时间复杂度为 $O(n^3 \log (n^2))$。

## $O(n^3)$

上面的做法的时间瓶颈来自给 $n^2$ 个数排序。如何优化呢？

我们发现 $n$ 的范围很小，这启示我们可以把 $O(n^2)$ 个区间和预处理，将其离散化和排序，之后每次排序 ```s1[],s2[]``` 时就可以用桶排，时间复杂度降到 $O(n^2)$。

具体做法详见代码：

```cpp
// P9127 [USACO23FEB] Equal Sum Subarrays G
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 510;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, top0, top1, top2;
bool vis1[MAXN * MAXN], vis2[MAXN * MAXN];
ll a[MAXN], sum[MAXN], s1[MAXN * MAXN], s2[MAXN * MAXN];
ll q[MAXN * MAXN], tot, rnk[MAXN][MAXN];

void pre()
{
	// 预处理，离散化，排序 
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j <= n; j++) q[++tot] = sum[j] - sum[i-1];
	}
	sort(q + 1, q + 1 + tot);
	top0 = unique(q + 1, q + 1 + tot) - q - 1;
	// q 是离散化后的数组 
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			ll s = sum[j] - sum[i-1];
			rnk[i][j] = (lower_bound(q + 1, q + 1 + top0, s) - q);
			// rnk[i][j] 表示 [i,j] 的区间和的排名，即新的下标
			// q[rnk[i][j]] 即为 [i,j] 的区间和 
		}
	}	
}

ll solve(int pos)
{
	ll ans = INF;
	memset(vis1, 0, sizeof(vis1)), memset(vis2, 0, sizeof(vis2));
	top1 = top2 = 0, ans = INF;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j <= n; j++) // [i, j]
		{
			if(i <= pos && j >= pos) vis1[rnk[i][j]] = true;
			else vis2[rnk[i][j]] = true;
		}
	}
	for(int i = 1; i < MAXN * MAXN; i++) // 桶排序
	{
		if(vis1[i]) s1[++top1] = q[i];
		else if(vis2[i]) s2[++top2] = q[i];
	}
	int p1 = 1, p2 = 1; // p1 和 p2 分别是 s1[] 和 s2[] 的指针
	s2[top2+1] = INF; // 由于双指针法可能取到 s2[top2+1]，需要先将其设为无穷大
	for(p1; p1 <= top1; p1++)
	{
	    while(s2[p2+1] <= s1[p1] && p2 < top2) p2++;
	    ans = min({ans, abs(s2[p2] - s1[p1]), abs(s2[p2+1] - s1[p1])});
	    // s2[p2] 是 s2[] 中小于等于 s1[p1] 的最大的数，s2[p2+1] 是 s2[] 中大于 s1[p1] 的最小的数
	    // 由于 s1[] 和 s2[] 都是升序的，所以与 s1[p1] 差值最小的数一定在这两者之中 
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum[i] = sum[i-1] + a[i];
	pre();
	for(int i = 1; i <= n; i++) printf("%lld\n", solve(i));
	return 0;
}
```



## 总结

这道题中，我们先思考了最暴力的做法，然后用双指针法和离散化两个技巧优化了时间复杂度。其中离散化的技巧是具有启发性的，它启示我们在数据规模较小的情况下可以先离散化，然后就可以使用一些时间复杂度更小的算法（如这道题中的桶排序）。

---

