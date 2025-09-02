# Range Sorting (Hard Version)

## 题目描述

The only difference between this problem and the easy version is the constraints on $ t $ and $ n $ .

You are given an array $ a $ , consisting of $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ .

Define the beauty of an array $ p_1, p_2, \ldots p_k $ as the minimum amount of time needed to sort this array using an arbitrary number of range-sort operations. In each range-sort operation, you will do the following:

- Choose two integers $ l $ and $ r $ ( $ 1 \le l < r \le k $ ).
- Sort the subarray $ p_l, p_{l + 1}, \ldots, p_r $ in $ r - l $ seconds.

Please calculate the sum of beauty over all subarrays of array $ a $ .

A subarray of an array is defined as a sequence of consecutive elements of the array.

## 说明/提示

In the first test case:

- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [4] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [6, 4] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 1 = 1 $ .In the second test case:

- The subarray $ [3] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [10] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [3, 10] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [10, 6] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 2 - 1 = 1 $ .
- You can sort the subarray $ [3, 10, 6] $ in one operation by choosing $ l = 2 $ and $ r = 3 $ . Its beauty is equal to $ 3 - 2 = 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 0 + 0 + 1 + 1 = 2 $ .

## 样例 #1

### 输入

```
5
2
6 4
3
3 10 6
4
4 8 7 2
5
9 8 2 4 6
12
2 6 13 3 15 5 10 8 16 9 11 18```

### 输出

```
1
2
8
16
232```

# 题解

## 作者：Mikefeng (赞：26)

## 题意

对 $l,r$ 排序的花费是 $r-l$，问对于每个子区间排序的花费和是多少。

## 做法

首先可以证明，一定不会有两次排序相交，否则一次更大的排序一定不劣。

容斥，最大花费显然是 $\sum_{i=2}^n (i-1)\times(n-i+1)$，考虑对于 $\forall l\le i<r$ 来说，什么时候 $l,i$ 和 $i+1,r$ 可以分别排序。

发现不好计数，因为与前半段的最大值和后半段的最小值都有关系。

转化一下，枚举前半段的最大值 $x$，位置为 $b$，要求后半段的最小值比 $x$ 大。

可以通过 set 找到前一个比 $x$ 大的数的位置 $a$，后一个比 $x$ 大的数的位置 $c$，$c$ 后面第一个比 $x$ 小的数的位置 $d$。

那么前半段的左端点可以在 $(a,b]$ 中选，右端点一定是 $c-1$，后半段的左端点一定是 $c$，右端点可以在 $[c,d)$ 中选，贡献为 $(b-a)\times(d-c)$。

时间复杂度 $O(n\log n)$。


## 代码
```cpp
const int N=3e5+5;
int T,n;
int a[N],id[N];
set<int> s1,s2;
bool M2;
int main(){
	int Time=clock();
	look_memory;
	T=read();
	while(T--){
		n=read();
		F(i,1,n) a[i]=read();
		ll sum=0;
		F(i,2,n) sum+=1ll*(i-1)*(n-i+1);
		F(i,0,n+1) s1.emplace(i);
		s2.emplace(0);s2.emplace(n+1);
		F(i,1,n) id[i]=i;
		sort(id+1,id+n+1,[&](int i,int j){return a[i]<a[j];});
		F(i,1,n){
			int b=id[i];
			int a=*(--s1.lower_bound(b));
			int c=*s1.upper_bound(b);
			if(c!=n+1){
				int d=*s2.lower_bound(c);
				sum-=1ll*(b-a)*(d-c);
			}
			s1.erase(b);s2.emplace(b);
		}
		cout<<sum<<'\n';
		s1.clear();s2.clear();
	}
	look_time;
	return 0;
}

```

---

## 作者：Alex_Wei (赞：22)

### *[CF1827B2 Range Sorting (Hard Version)](https://www.luogu.com.cn/problem/CF1827B2)

先求一个序列的权值：将贡献拆到每个间隔 $i - 1\sim i$ 处。间隔 $i - 1\sim i$ 产生贡献当且仅当 $a_1\sim a_{i - 1}$ 的最大值大于 $a_i\sim a_n$ 的最小值，因为无论如何都要有间隔后的元素换到间隔前。

枚举间隔 $i - 1\sim i$ 和区间左端点 $j < i$。设 $v = \max a_{j\sim i - 1}$。

- 若 $v \geq a_i$，则 $i\sim n$ 作为右端点均合法。
- 若 $v < a_i$，则 $p\sim n$ 作为右端点合法，其中 $p$ 为 $i$ 之后第一个小于 $v$ 的位置，若不存在则为 $n + 1$。

暴力的时间复杂度为 $\mathcal{O}(n ^ 3)$。

两个优化：

- 维护递增单调栈（只有单调栈内的元素可能成为最大值），若栈顶 $j_1$ 满足 $a_{j_1} < a_i$ 则弹出。

  设弹出前栈顶下方的元素为 $j_2$，则 $j_2 + 1\sim j_1$ 每个位置作为左端点时，与 $i - 1$ 之间的最大值均为 $a_{j_1}$，即 $\max a_{j\in [j_2 + 1\sim j_1]\sim i - 1} = a_{j_1}$。

  不断弹出直到 $a_{j_1} > a_i$，此时答案加上 $j_1 (n - i + 1)$，因为 $i\sim i + 1$ 在左端点属于 $[1, j_1]$，右端点属于 $[i, n]$ 的区间中产生贡献。

- 将所有形如 “$i$ 之后第一个小于 $a_j$ 的位置” 的查询 $(j, i)$ 离线下来倒着扫描线。维护权值线段树 $T$ 表示值 $p$ 对应的下标，查询相当于前缀 $\min$。单点 $\min$ 前缀求 $\min$ 也可以用树状数组维护。

加任意一个优化可通过 B1，加两个优化可通过 B2。

时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1827/submission/205930118)。

注意到 **$i$ 是 $j$ 后第一个大于 $a_j$ 的位置**，考虑在扫描线的过程中维护一个从栈顶到栈底下标递增且值递减的单调栈。$i + 1\to i$ 时，将 $a_{i + 1}$ 加入单调栈，然后按 $j$ 从小到大的顺序（$a_j$ 递减）考虑询问 $(j, i)$。弹出单调栈栈顶直到栈顶对应权值小于 $a_j$，则栈顶即为查询答案。

若某个询问 $(j, i)$ 弹出了元素 $a_p$，则 $(j' > j, i)$ 答案显然不为 $p$。只需证明不存在 $(j', i' < i)$ 的答案为 $p$。

> 若 $i' < j$，则因为 $a_j < a_p$，所以 $p$ 一定不会是 $(j', i')$ 的答案（$j$ 可以作为答案）。
>
> 若 $i' = j$，则因为 $a_{j'} < a_{i'} = a_j < a_p$，所以 $p$ 一定不会是 $(j', i')$ 的答案。
>
> 若 $j < i' < i$，那么 $a_{i'} < a_j$，否则 $j$ 后第一个大于 $a_j$ 的位置不可能是 $i$。所以 $a_{j'} < a_{i'} < a_j < a_p$，$p$ 一定不会是 $(j', i')$ 的答案。$\square$

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1827/submission/205972579)。

---

## 作者：chlchl (赞：6)

好题，费解题。

## Solution
正难则反，我们考虑将所有区间都“暴力”排序，代价是 $\sum\limits_{i=2}^{n} (i-1)\times(n-i+1)$。

然后，我们考虑一个区间 $[l,r]$。如果存在 $x\in(l,r]$，使得 $[l,x-1]$ 和 $[x,r]$ 分别排序后即可有序，那么代价会比直接排序的代价少 $1$。

所以，我们的目标就是找到所有这样的区间。容易发现，如果想要存在这样的情况，必须满足 $\max\limits_{k=l}^{x-1}a_k<\min\limits_{k=x+1}^{r}a_k$，即前半段最大值小于后半段最小值。

这样的东西不好统计，我们转成对每个位置单独考虑贡献。

对于每个位置 $i$，我们假设 $a_i$ 为某个**右半**区间 $[x,r]$ 的最小值（$x\le i\le r$），那么 $[l,x-1]$ 的最大值要小于 $a_i$。

现在需要统计有多少个区间 $[l,r]$ 可以拆成 $[l,x-1]$ 和 $[x,r]$ 分别排序，并且知道 $i$ 在 $x$ 和 $r$ 之间。

找到 $i$ 后面第一个比 $a_i$ 小的数 $a_{rr}$，那么 $r$ 在 $[i,rr)$ 间都是可以的（保证右半段最小值一定是 $a_i$）。

然后从 $i$ 往前找到前一个比 $a_i$ 小的位置 $a_{rl}$，如果 $rl$ 在右半边，那么最小值就是 $a_{rl}$ 了，所以一定在左半边。也就是说，$rl$ 一定**可以作为**前后两段的分界点，即上文的 $x-1$。

**请注意，其他题解所说的，$rl$ 一定是分界点的说法，并不意味着 $rl$ 是唯一的，请不要混淆。我们所找的只是“可以拆”，并不是找“怎么拆”。**

最后，再从 $rl$ 往前找到前一个比 $a_i$ 大的数 $a_{ll}$。因为要求左半边最大值小于右半边最小值（$a_i$），所以 $l$ 只能在 $(ll,rl]$ 之间。

区间个数就是 $(rr-i)\times (rl-ll)$。

实现方式颇多，可以单调栈、倍增、二分、`set` 等。因为本人偏好，故采用二分实现。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int T, n, a[N], f1[N][20], f2[N][20];

void init(){
	for(int j=1;j<=19;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			f1[i][j] = max(f1[i][j - 1], f1[i + (1 << (j - 1))][j - 1]);
			f2[i][j] = min(f2[i][j - 1], f2[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int query_max(int l, int r){
	int k = log2(r - l + 1);
	return max(f1[l][k], f1[r - (1 << k) + 1][k]);
}

int query_min(int l, int r){
	int k = log2(r - l + 1);
	return min(f2[l][k], f2[r - (1 << k) + 1][k]);
}

int main(){
	scanf("%d", &T);
	while(T--){
		for(int j=1;j<=19;j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				f1[i][j] = f2[i][j] = 0;
		scanf("%d", &n);
		for(int i=1;i<=n;i++)
			scanf("%d", &a[i]), f1[i][0] = f2[i][0] = a[i];
		init();
		long long ans = 0;
		for(int i=1;i<=n;i++)
			ans += 1ll * (i - 1) * (n - i + 1);
		for(int i=1;i<=n;i++){
			int ll = 0, rl = 0, rr = n + 1;
			int l = i + 1, r = n;
			while(l <= r){
				int mid = (l + r) >> 1;
				if(query_min(i + 1, mid) < a[i])
					r = mid - 1, rr = mid;
				else
					l = mid + 1; 
			}
			l = 1, r = i - 1;
			while(l <= r){
				int mid = (l + r) >> 1;
				if(query_min(mid, i - 1) < a[i])
					l = mid + 1, rl = mid;
				else
					r = mid - 1; 
			}
			l = 1, r = rl - 1;
			while(l <= r){
				int mid = (l + r) >> 1;
				if(query_max(mid, rl - 1) > a[i])
					l = mid + 1, ll = mid;
				else
					r = mid - 1; 
			}
			ans -= 1ll * (rr - i) * (rl - ll);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```



---

## 作者：spider_oyster (赞：6)

赛时想复杂了。当时只是想做出 B1，于是考虑 $n^2$ 枚举区间。

实际上这种题一般都是单个位置算贡献的。

先令答案为对所有区间“硬”排序的总贡献。

考虑位置为 $x$，如果只用对 $[l,x]$ 和 $[x+1,r]$ 分别排序。当前区间排序的贡献就会 $-1$。

那么 $\max\limits_{j=l}^{x}a_j<\min\limits_{j=x+1}^{r} a_j$。

发现直接枚举不好算，我们可以钦定每个 $a_i$ 为 $[x+1,r]$ 的最小值。（钦定为最大值也可以）。然后求当前满足要求的区间个数。

>- 实际是寻找满足上述式子的 $l_{min}$ 和 $r_{max}$，那么区间数量就是 $(r_{max}-i+1)\times(x-l_{min}+1)$。
>- 可以发现，$x$ 是从 $i$ 往前第一个值小于 $a_i$ 的位置，否则 $a_i$ 一定不是 $[x+1,r]$ 的最小值。
>- 根据 $\max\limits_{j=l}^{x}a_j<a_i$，从 $x$ 往前找 $l_{min}$ 即可。
>- 根据 $a_i$ 是 $[x+1,r]$ 的最小值，$r_{max}$ 是从 $i$ 往后第一个值小于 $a_i$ 的往前一个位置，否则 $a_i$ 一定不是 $[x+1,r]$ 的最小值。

由于 $a_i$ 两两不同，最小值也不同，故不会重复计算。

所以这道题难就难在想到用钦定最小值的方法来计算。

对于形如“第一个大于/小于”，可以用单调栈求。

对于 $l_{min}$，可以通过跳 ST 表的方式求，每次跳表时如果最大值小于 $a_i$，那么就可以跳。

时间复杂度 $O(n\log n)$。 

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,t,a[N],f[20][N],r[N];
long long ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)
    {
        ans=0;
        cin>>n;
        a[0]=a[n+1]=0;
        for(int i=1;i<=n;i++) cin>>a[i],f[0][i]=a[i],ans+=1ll*i*(i-1)/2;
        for(int j=1;j<20;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                f[j][i]=max(f[j-1][i],f[j-1][i+(1<<j-1)]);
        stack<int> st;
        st.push(n+1);
        for(int i=n;i;i--)
        {
            //这里求的实际是 r_min+1，从后往前第一个小于 a[i] 的位置
            while(a[st.top()]>a[i]) st.pop();
            r[i]=st.top();
            st.push(i);
        }
        while(!st.empty()) st.pop();
        st.push(0);
        for(int i=1;i<=n;i++)
        {
            //这里求的是 x
            while(a[st.top()]>a[i]) st.pop();
            int j=st.top();
            //跳表求 l_min
            for(int k=19;~k;k--)
                if(j>(1<<k)&&f[k][j-(1<<k)]<a[i]) j-=1<<k;
            if(st.top()>0) ans-=1ll*(r[i]-i)*(st.top()-j+1);
            st.push(i);
        }
        cout<<ans<<'\n';
    }
}
```


---

## 作者：I_am_Accepted (赞：4)

子串中一个 gap 有 $1$ 的贡献当且仅当子串中 gap 之前的值 $\max>$ 子串中 gap 之后的值 $\min$。

然后枚举子串 gap 之前的最大值位置，狂暴推式子，发现只要求得

* 每个位置 $i$ 左侧第一个大于其的位置 $L_i$（没有 $L_i=0$）。

* 每个位置 $i$ 右侧第一个大于其的位置 $R_i$（没有 $R_i=n+1$）。

* 每个位置 $i$ 的 $[R_i,n]$ 中最左侧的位置 $X_i$ 使得 $a_{X_i}<a_i$。

答案就可以线性算了。

$L_i,R_i$ 可以用单调栈求。重点在 $X_i$ 如何求，我们先将 $R_i$ 全求出来。

按 $a_i$ 从大往小删位置，维护剩下位置形成的双向链表，扫到值 $a_i$ 时查询一下位置 $R_i-1$ 在链表中的后继即可。

值离散化后复杂度线性。

[代码](https://codeforces.com/contest/1827/submission/206855325)

当然有严格线性的做法。

考虑每个位置 $i$ 的询问挂在节点 $R_i$ 上。倒序扫下标，维护如下图的单调栈。

![](https://cdn.luogu.com.cn/upload/image_hosting/3sn1ay0r.png)

在单调栈插入位置 $i$ 之前处理所有挂在 $i$ 点的询问下标集合 $S$。

从小到大遍历所有 $S$ 内的元素，设当前为 $j$。将目前单调栈中值 $>a_j$ 的栈顶依次弹出（这些位置必然不再会作为别人的 $X_i$ 了），然后将 $X_j$ 设为栈顶。

复杂度线性。

[代码](https://codeforces.com/contest/1827/submission/206894850)

---

## 作者：xs_siqi (赞：3)

思路比较难想的权值线段树做法。

考虑对每一个点算贡献。往右边找到第一个比你小的值，你们之间的距离，与你找到的比你小的点，离 $n$ 号点的距离，这两个东西的乘积就是贡献。

假如说，你找到一个比你小的点，然后后面还有另一个比你小的点，那就更新掉。把这个你刚找到的比你小的点换成距离乘积即可。

然后我们就得到了一个 $O(n^2)$ 的暴力做法，是不是很好想呢。

但是这个算法其实是很难优化的。因为你想要进一步优化，你就得在 $\log$ 的复杂度内求出右边所有比你小的点的坐标。这很难做。

不妨退一步想，先把之前找到的贡献结论退化一下。

不难发现我们是基于这一个性质构建的这个算法：

如果有 $\max\{a,i-1\}>\min\{i,b\}$，则必然 $[a,b]$ 这个区间是需要进行操作的。因为你后面有最小的东西都比前面大，说明这个区间必然是不符合前小后大的规则的。

然后我们就可以得到一个 $O(n^3)$ 的退化算法。暴力枚举 $a,i,b$ 三个数值即可。

然后我们会发现一个对我们后续没什么帮助的优化，不过还是讲一下：

对于 $\max\{a,i-1\}$ 必然满足单调递增，所以使用尺取法就可以做到 $O(n^2)$ 的复杂度。

然后我们考虑优化。一般做法就是你要去剪枝状态数。

不妨换个思路，将枚举状态数换为用组合数学计算状态。

不难想到，可以枚举一个点下标为 $x$，值为 $a_x$，然后你去找它的左边第一大。左边第一大显然就是区间 $[a,b]$ 的 $a$。因为你再往左边走一步，你对于每个区间 $[a,i-1]$ 的最大值就会变。

那么如何找到合适的 $i$ 点成了难点。不妨将这个式子容斥一下。总方案数很有规律不难推出就是 $\sum{ i\times (n-i)}$。

然后上面的式子大于号就变成了小于号。这个时候 $i$ 点就成了对于 $x$ 的右边第一大。

所以单调栈两遍，分别找左边第一大，右边第一大即可。

然后你现在要考虑的事情就是如何得到 $b$ 点。

显然，$b$ 点需要满足的性质是：在 $x$ 右边，且比 $a_x$ 小。

不难想到我们可以权值线段树以具体值为下标，记录 $x$ 的最小值即可。

这其实还是有一个漏洞的：考虑这样一个样例：

```
1 4 2 3 5
```

显然此时你枚举 $4$ 时会枚举到 $5$ 号，但是你的 $3$ 已经插进权值线段树里去了。

所以我们按每个枚举点的右边第一大去从大到小排个序然后插到权值线段树里去就行了。

组合一下，每个点对答案的贡献是 $-(b-i)(x-a)$。因为你左边可以在 $[a,x]$ 任意一个点上，右边在 $[i,b]$ 任意一个点上。

记得离散化。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const int maxn=3e5+5;
int T,t,n,sum,lb[maxn],rb[maxn],q[maxn],b[maxn];
struct edge{int id,x;}a[maxn];
struct tree{int p;}tr[maxn*4];
bool cmp1(edge x,edge y){return x.x<y.x;}
bool cmp2(edge x,edge y){return x.id<y.id;}
bool cmp3(edge x,edge y){return rb[x.id]>rb[y.id];}
inline void pushup(int rt){tr[rt].p=min(tr[ls].p,tr[rs].p);}
inline void build(int rt,int l,int r){
	if(l==r){tr[rt].p=1e9;return ;}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(rt);}
inline void add(int rt,int l,int r,int p,int z){
	if(l==r&&l==p){
		tr[rt].p=z;
		return ;}
	int mid=(l+r)>>1;
	if(p<=mid)add(ls,l,mid,p,z);
	if(mid<p)add(rs,mid+1,r,p,z);
	pushup(rt);}
inline int query(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[rt].p;
	int ans=1e9,mid=(l+r)>>1;
	if(ql<=mid)ans=query(ls,l,mid,ql,qr);
	if(mid<qr)ans=min(ans,query(rs,mid+1,r,ql,qr));
	return ans;}
signed main(){
	scanf("%lld",&T);
	while(T--){
		sum=0;
		scanf("%lld",&n);
		build(1,1,n);
		for(int i=1;i<=n;i++)lb[i]=rb[i]=a[i].x=a[i].id=0;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i].x),a[i].id=i;
		sort(a+1,a+n+1,cmp1);
		for(int lst=0,now,i=1;i<=n;i++){
			now=a[i].x;
			a[i].x=a[i-1].x+(now!=lst);
			lst=now;}
		sort(a+1,a+n+1,cmp2);
		t=0,q[t]=0;
		for(int i=1;i<=n;i++){
			while(t&&a[i].x>=a[q[t]].x)t--;
			lb[i]=q[t];
			q[++t]=i;}
		t=0,a[n+1].x=0,q[t]=n+1;
		for(int i=n;i>=1;i--){
			while(t&&a[i].x>=a[q[t]].x)t--;
			rb[i]=q[t];
			q[++t]=i;}
		for(int i=1;i<n;i++)sum+=i*(n-i);
		for(int i=1;i<=n;i++)b[i]=a[i].x;
		sort(a+1,a+n+1,cmp3);
		for(int lst=n+1,i=1;i<=n;i++){
			int a1=lb[a[i].id],a2=a[i].id,b1=rb[a[i].id];
			if(b1>n)continue;
			for(int j=b1;j<lst;j++)add(1,1,n,b[j],j);
			lst=b1;
			int b2=query(1,1,n,1,a[i].x);
			if(b2==1e9)b2=n+1;
			sum-=(a2-a1)*(b2-b1);}
		printf("%lld\n",sum);}
	return 0;}
```


---

## 作者：sanaka87 (赞：2)

首先我们手玩，可以发现如果左边有大的右边有小的，那肯定至少需要对这个区间（当然可以包含它）做一次操作。这个启示我们对每一个小区间 $[i,i+1]$ 算贡献。

考虑 $[i,i+1]$ 什么时候需要被计入答案。那一定是 $[1,i]$ 存在一个数大于 $[i+1,n]$ 的一个数，形式化的讲，就是左边最大值要大于右边最小值（不加等于号是因为保证了两两不同）。这样好像有点不好看，**补集转换一下**，我们考虑什么时候不计入答案，那就是就是左边最大值要小于右边最小值。那么我们可以做出 B1 了：先枚举 $[i,i+1]$，求出后缀最小值数组后枚举左端点，双指针即可。时间复杂度 $O(n^2)$。

B2 怎么做呢？想了半天发现只会这样一个暴力：先枚举 $[i,i+1]$，然后枚举左边的最大值（这个可以用单调栈来维护），这样最坏是 $O(n)$ 的，然后对于一个枚举出来左边的最大值，我们用 ST 表 + 二分可以算出右边最远可以扩展到哪里。这样复杂度肯定爆炸了，我们考虑一个很显然的剪枝：如果 $\max_{j=l}^{i}a_j>a_{i+1}$（**注意之前做了一个补集转换**），那么就直接 break。

事实上这样的复杂度就是 $O(n\log n)$ 了。怎么证明，又是怎么想到的呢？

考虑在笛卡尔树上处理这个问题。建出一个大根的笛卡尔树，我们发现 $i$ 必须没有右儿子，才有可能**不被计入答案**。为什么？如果有右儿子，那么显然 $a_i>a_{i+1}$，一定是要被计入的。

于是我们可以枚举没有右儿子的点，然后枚举左边的最大值，这可以通过记录一个数前面第一个比他大的数实现，当然如果跳的时候发现当前点权值大于 $a_{i+1}$，那肯定不行了，直接退出（可以想想为什么）。那么整个暴力跳的复杂度其实是一个链剖分的过程（把重儿子设为右儿子），时间复杂度是对的。

这题就做完了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define gc getchar
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=gc();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=gc();}
	while (isdigit(ch)){x=x*10ll+ch-'0';ch=gc();}
	return x*f;
}
int n,fa[500005],sta[500005],top,a[500005],ma[500005][21],mi[500005][21],lg2[500050];
int queryma(int l,int r){
	int k=lg2[r-l+1];
	return max(ma[l][k],ma[r-(1<<k)+1][k]);
}
int querymi(int l,int r){
	int k=lg2[r-l+1];
	return min(mi[l][k],mi[r-(1<<k)+1][k]);
}
int main(){
	int T=read();
	while (T--){
		n=read();
		ll _=0;
		for (int i=1;i<=n;i++) a[i]=read(),mi[i][0]=ma[i][0]=a[i],lg2[i]=log2(i);
		for (int j=1;j<=20;j++){
			for (int i=1;i+(1<<j)-1<=n;i++){
				mi[i][j]=min(mi[i][j-1],mi[i+(1<<j-1)][j-1]);
				ma[i][j]=max(ma[i][j-1],ma[i+(1<<j-1)][j-1]);
			}
		}
		top=0;
		for (int i=1;i<=n;i++) sta[i]=fa[i]=0;
		for (int j=1;j<=n;j++){
			while (top&&a[sta[top]]<a[j]) top--;
			fa[j]=sta[top];
			sta[++top]=j;
		}
		for (ll j=1;j<n;j++){
			_+=1ll*j*(n-j);
			ll las1=j,las2=j+1;
			if (a[j]>a[j+1]) continue;
			for (int k=j;k&&a[k]<a[j+1];k=fa[k]){
				ll ans2=-1,ans1=-1,lb=1,rb=j;
				while (lb<=rb){
					int mid=(lb+rb)/2;
					if (queryma(mid,j)<=a[k]){
						ans1=mid;rb=mid-1;
					}else lb=mid+1;
				}
				lb=j+1,rb=n;
				while (lb<=rb){
					int mid=(lb+rb)/2;
					if (querymi(j+1,mid)>=a[k]){
						ans2=mid;lb=mid+1;
					}else rb=mid-1;
				}
				_+=-1ll*(las1-ans1+1)*1ll*(ans2-j);
				las1=ans1-1;
			}
		}	
		cout<<_<<endl;
	}
	return 0;
}
/*
1
12
2 6 13 3 15 5 10 8 16 9 11 18
*/


```


---

## 作者：Hisaishi_Kanade (赞：1)

存在一个比较显然的结论，对于任意一个序列进行操作，最小化价值后必然不存在操作区间相交的情况。

那么我们可以这样理解，将每个数所在位置与其应在的位置作为左右端点，得到 $n$ 个区间，这些区间取并后得到若干个无交的区间就是我们最后需要操作的区间。

直接算区间长度和太难，不如容斥。考虑怎么样计算相邻区间之间距离之和。我们观察一下，假设 $[l, i],[i+1,r]$ 是可以分开排的点会怎么样？显然不存在跨过 $i,i+1$ 点的区间。

有了这个结论，代入原序列考虑每个点作为区间直接断点的点的次数，即其每次贡献 $-1$。

当 $l\le i \le r$ 时，若 $[l,i],[i+1,r]$ 可以分开排序，则 $\max\limits_{j=l}^{i}a_j<\min\limits_{j=i+1} ^ra_j$ 。

问题转化为统计满足条件的 $l,r$ 的对数。再转换一下，枚举左边区间最大值位置 $a$，然后 $a$ 左边最靠右的比 $a$ 大的数的位置 $b$；然后找到右侧第一个比 $a$ 大的数 $c$，以及 $c$ 右侧第一个比 $a$ 小的数的位置 $d$。

此时满足条件的 $l_1\in(b,a],r_1=c-1,l_2=c,r_2\in[c,d)$。所以对数是 $(a-b)(d-c)$。

如何求 $b,c,d$ 呢？最大值最小值都是有单调性的，可以二分。二分三次求出即可。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
const int N=3e5+5, lgN=20, inf=2e9;
int g[N][lgN], f[N][lgN], lg[N]; ll ret;
int t, n, i, j, l, r, ans, mid, k, a, b, c, d;
inline int qmax(int l, int r)
{
	k=lg[r-l+1];
	return max(g[l][k], g[r-(1<<k)+1][k]);
}
inline int qmin(int l, int r)
{
	k=lg[r-l+1];
	return min(f[l][k], f[r-(1<<k)+1][k]);
}
int main()
{
	rep(i, 2, N-1) lg[i]=lg[i>>1]+1;
	scanf("%d", &t); while(t--)
	{	ret=0;
		scanf("%d", &n); rep(i, 1, n) scanf("%d", f[i]), g[i][0]=f[i][0]; ret=1ll*n*(n-1)*(n+1)/6ll;
		rep(i, 1, lg[n]) rep(j, 1, n-(1<<i)+1) f[j][i]=min(f[j][i-1], f[j+(1<<i-1)][i-1]);
		rep(i, 1, lg[n]) rep(j, 1, n-(1<<i)+1) g[j][i]=max(g[j][i-1], g[j+(1<<i-1)][i-1]);
		rep(i, 1, n)
		{
			l=1; r=i; b=i-1;
			while(l<=r)
			{
				mid=l+r>>1;
				if(qmax(mid, i)==f[i][0]) b=r=mid-1;
				else l=mid+1;
			}
			l=i; r=n; c=i+1;
			while(l<=r)
			{
				mid=l+r>>1;
				if(qmax(i, mid)==f[i][0]) c=l=mid+1;
				else r=mid-1;
			}
			if(c>n) continue;
			l=c; r=n; d=c;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(qmin(c, mid)>f[i][0]) d=l=mid+1;
				else r=mid-1;
			}
			ret-=1ll*(d-c)*(i-b);
		}
//		rep(i, 1, n) printf("%d %d %d\n", i, findl(i), findr(i));
		printf("%lld\n", ret);
	}
	return 0;
}
```

---

## 作者：MiniLong (赞：1)

好题。

正着死搞很难，那就考虑反着来。

如果全部子段直接一次排序的话那么总答案为 $\sum\limits_{i=1}^{n-1} i \times (n-i)$，即 $\dfrac{n \cdot (n-1) \cdot (n+1)}{6}$ 。

先考虑一个区间怎样减少排序次数。

那么肯定是要把一个区间从某几个位置分开然后分治地搞。

那么这样分开排序后还是有序的条件是什么？

就是两个子段 **互不影响**。

问题又来了，怎样才算互不影响。

假设把一个区间 $[l,r]$ 分成 $[l,p],[p+1,r]$ 两段，互不影响的条件就是对于每个 $i$ 在 $[l,p]$ 和 $[p+1,r]$ 之间的，将这个区间 $[l,r]$ 排序后原来 $i$ 对应的值还在原来 $i$ 对应的那个子区间里。

举个例子 $[3,1,2,5,4]$，假设 $p=3,i=2$。

将原区间排序 $[1,2,3,4,5]$，原来第 $i$ 位的数 $i$ 还在 $[1,3]$ 里面，这样子就对右边一点影响都没有。

所以总结一下，一个区间能分成两个子区间当且仅当两个子区间互不影响，也就是说这两个子区间的 **值域区间不相交**。
(**注意：每个大区间不止能分成两个，可以分成多个，也可以理解为分开的两个子区间还能自我分解**)

如上面那个例子,$[1,3]$ 与 $[4,5]$ 显然不相交。

知道这个东西就好算了。

先假设从小到大排序，那么上面那个条件就可以转化为区间 $[l,r]$ 能分割成 $[l,p],[p+1,r]$ 当且仅当 $\max\limits_{i=l}^p a_i < \min\limits_{j=p+1}^r a_i$。

然后就是统计答案。

因为要算所有子区间的答案和，所以可以顺序枚举每个分割点 $p$，看看以 $p,p+1$ 为端点的区间之间的贡献。

先用个单调栈，从右往左扫一遍，对于每个位置 $p$， 记录一下每个值 $x$ 在区间 $[p,r_j]$ 为最小值，每次 $p$ 左移的时候记录一下哪些 $r_j$ 被当前新加入的给删掉了，然后加上新加入的 $p$ 位置的贡献区间 $[p,r]$。

再从左往右扫，一样地用个单调栈，记录 $y$ 在区间 $[l_k,p-1]$ 为最大值，然后遍历刚刚记录的部分，用树状数组更新一下贡献即可。具体详见代码吧~

```cpp
#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; ++i)
#define _req(i, x, y) for(int i = x; i >= y; --i)
#define _rev(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define pb push_back
#define fi first
#define se second
#define mst(f, i) memset(f, i, sizeof f)
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
namespace fastio{
    char ibuf[50007],*p1 = ibuf, *p2 = ibuf;
    #ifdef ONLINE_JUDGE
    #define get() p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 50007, stdin), p1 == p2) ? EOF : *p1++
    #else
    #define get() getchar()
    #endif
    template<typename T> inline void read(T &t){
        T x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T, typename ... Args> void write(T t, Args... args){
        write(t), putchar(' '), write(args...);
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
    template<typename T> void writes(T t){
        write(t), putchar(' ');
    }
    #undef get
};
using namespace fastio;
#define multitest() int T; read(T); _rep(tCase, 1, T)
typedef long long ll;
typedef pair<int, int> PII;
const int N = 6e5 + 5;
int n, len, a[N], lsh[N];
struct Tree{
    int c[N];
    void add(int x, int v){for(; x <= len; x += x & -x) c[x] += v;}
    int sum(int x){int res = 0; for(; x; x -= x & -x) res += c[x]; return res;}
}tl, tr;
struct node{
    int x, l, r;
};
vector<node> in[N], out[N];
int main(){
	multitest(){
        read(n); _rep(i, 1, n) read(a[i]), lsh[++len] = a[i];
        sort(lsh + 1, lsh + 1 + len);
        len = unique(lsh + 1, lsh + 1 + n) - lsh - 1;
        _rep(i, 1, n) a[i] = lower_bound(lsh + 1, lsh + 1 + n, a[i]) - lsh;
        ll ans = 1ll * n * (n - 1) * (n + 1) / 6ll;
        stack<node> st;
        _req(i, n, 1){
            int curl = i, curr = i;
            while(st.size() && a[i] < st.top().x){
                in[i].pb(st.top());
                curr = st.top().r, st.pop();
            }
            node t = {a[i], curl, curr};
            st.push(t);
            out[i].pb(t);
        }
        ll cur = 0;
        while(st.size()){
            node u = st.top(); st.pop();
            tr.add(u.x, u.r - u.l + 1);
        }
        _rep(i, 1, n - 1){
            for(auto &j : out[i]){
                cur -= 1ll * tl.sum(j.x - 1) * (j.r - j.l + 1);
                tr.add(j.x, -(j.r - j.l + 1));
            }
            for(auto &j : in[i]){
                cur += 1ll * tl.sum(j.x - 1) * (j.r - j.l + 1);
                tr.add(j.x, j.r - j.l + 1);
            }
            int tot = n - i, curl = i, curr = i;
            while(st.size() && a[i] > st.top().x){
                node u = st.top(); st.pop();
                cur -= 1ll * (tot - tr.sum(u.x)) * (u.r - u.l + 1), curl = u.l;
                tl.add(u.x, -(u.r - u.l + 1));
            }
            cur += 1ll * (tot - tr.sum(a[i])) * (curr - curl + 1);
            tl.add(a[i], curr - curl + 1);
            st.push({a[i], curl, curr});
            ans -= cur;
        }
        writeln(ans);
        _rep(i, 1, n) in[i].clear(), out[i].clear();
        _rep(i, 1, len) tl.c[i] = tr.c[i] = 0;
        len = 0;
    }
    return 0;
}

```

---

## 作者：orz_z (赞：1)

发现选择的区间不包含且不相交，于是区间的形式为选一段空一段。

考虑到 $r-l$ 即为每个区间 $[i,i+1]$ 的贡献。

于是考虑 $[i,i+1]$ 什么时候不选，发现当左段的最大值小于右端的最大值时，$[i,i+1]$ 不选更优。

于是枚举左段的最大值 $x$，位置为 $b$，要求右段的最小值比 $x$ 大。

维护 `set` 找到前一个比 $x$ 大的数的位置 $a$，后一个比 $x$ 大的数的位置 $c$，$c$ 后面第一个比 $x$ 小的数的位置 $d$。

那么左段的左端点可以在 $(a,b]$ 中选，右端点为 $c-1$，右段的左端点是 $c$，右端点在 $(c,d]$ 中选，贡献为 $(b-a)\times (d-c)$。

时间复杂度 $\mathcal O(n\log n)$。

---

## 作者：MurataHimeko (赞：0)

考虑容斥。

然后拆贡献。考虑当 $\max(a_l, a_{l+1},...,a_{i}) \leq \min(a_{i+1}, a_{i+2},...,a_r)$ 时，那么 $i$ 和 $i+1$ 之间是不需要交换的，有 $-1$ 的贡献。

至此我们可以得出一个 $O(n^2)$ 的做法：

枚举分界点 $i$，从 $i \sim 1$ 枚举左端点 $l$，求出对于当前左端点 $l$ 在 $i$ 之后第一个满足 $ a_r < \max(a_l, a_{l+1},...,a_i)$ 的 $r$，记为 $f_l$。 那么 $i+1 \sim r-1$ 都是合法的右端点。注意到 $\max(a_l, a_{l+1}, ..., a_i)$ 单调不降，所以可以双指针解决。

考虑优化。

枚举前半段的最大值的位置 $x$，通过单调栈求出 $x$ 前第一个比 $a_x$ 大的位置 $pre_x$，$x$ 后第一个比 $a_x$ 大的位置 $suf_x$。所以前半段的左端点的范围是 $pre_x + 1 \sim x$。这时发现，当右端点取 $x+1 \sim suf_x-2$ 时，后半段对应的 $f_l=x+1$。那么此时 $x$ 是没有贡献的。所以前半段的分界点必然是 $suf_x-1$。那么右半段的右端点就应该是 $suf_x \sim f_x - 1$。所以总的贡献为 $(x - pre_x)\times (f_x - suf_x)$。

$f_x$ 可以通过线段树简单求得。

复杂度 $O(n\log n)$。

---

## 作者：2018ljw (赞：0)

把 $(i,i+1)$ 看成一段线段，一次操作的贡献就可以摊到区间内的所有线段上。

关注到两次操作若线段有交必定不如对并集操作一次，因此每个线段对每个区间贡献不超过 $1$。

考虑 $(i,i+1)$ 对 $[l,r]$ 无贡献（$l\le i<r$），当且仅当 $\max\{a_{l\dots i}\}\le \min\{a_{i+1\dots r}\}$，此时左右两半可视为独立。

考虑统计线段总共有多少次无贡献，容斥减一下就好。

记 $pre_i$ 表示 $i$ 左侧第一个 $a_x>a_i$ 的位置（没有记 $0$），$nxt_i$ 表示 $i$ 右侧第一个 $a_x>a_i$ 的位置（没有记 $n+1$）。

枚举左半最大值 $a_x$，那么可选区间左端点为 $[pre_x+1,x]$。由于无贡献线段必须满足右半 $\min$ 大于等于左半 $\max$，因此对于一个 $x$，其能讨论到的线段有且仅有 $(las_x-1,las_x)$。此时右端点可以在 $las_x$ 所在，由 $>a_x$ 的元素构成的连续区间中任选。

因此我们从大到小插入每个数。用 $0/1$ 表示某个数是否被插入，问题变为找每个位置前后第一个 $1$ 位置、维护每个 $1$ 连通块大小。

关注到插入顺序的特殊性，第一个问题可以单调栈预处理。关注到询问的特殊性，第二个问题只需要维护连通块两个端点的信息。

由于需要离散化，复杂度 $O(n\log n)$。[record](https://codeforces.com/contest/1827/submission/208579526)。

---

