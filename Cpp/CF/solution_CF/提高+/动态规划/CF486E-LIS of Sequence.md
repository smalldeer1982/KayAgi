# LIS of Sequence

## 题目描述

# 题意：
给你一个长度为n的序列a1,a2,...,an，你需要把这n个元素分成三类：1，2，3：

1:所有的最长上升子序列都不包含这个元素

2:有但非所有的最长上升子序列包含这个元素

3:所有的最长上升子序列都包含这个元素

## 说明/提示

1≤n≤10^5

1≤ai≤10^5

## 样例 #1

### 输入

```
1
4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 3 2 5
```

### 输出

```
3223
```

## 样例 #3

### 输入

```
4
1 5 2 3
```

### 输出

```
3133
```

# 题解

## 作者：Xiao_mo (赞：11)

## [题面](https://www.luogu.com.cn/problem/CF486E)

# Step1
设 $f[i]$ 为从前往后第 $i$ 位为结尾的最长上升子序列， $g[i]$ 为从前往后第 $i$ 位为开头的最长上升子序列，$len$ 为最长上升子序列长度， $c[i]$ 为第 $i$ 个数所属的类数。

所以当 $a[i]$ 在某一最长上升子序列里时， $c[i]=1$ 必定满足 $f[i]+g[i]=len+1$ 。

所以当$f[i]+g[i]<len+1$ 时， $c[i]=1$ 。

# Step2
考虑如何区分 $c[i]=2$ 和 $c[i]=3$ 的情况。

首先若存在 $f[i]=f[j],g[i]=g[j](i\not=j)$ ，则 $c[i]=c[j]=2$ 。

因为无论选择第 $i$ 位还是第 $j$ 位都不影响最长上升子序列。

反之，则 $c[i]=3$ 。

```
for(int i=1;i<=n;i++){
	if(f[i]+g[i]<len+1)c[i]=1;
	else m[f[i]][g[i]]++;
}
for(int i=1;i<=n;i++){
	if(f[i]+g[i]<len+1)continue;
	if(m[f[i]][g[i]]>1)c[i]=2;
	else c[i]=3;
}
```
考虑到只用存 $10^5$ 个数，可以使用 $map$ 。

# Step3
关于 $O(nlogn)$ 求 $f[i]$ 和 $g[i]$ ，可以使用树状数组。

# End
贴上代码
```
#include<bits/stdc++.h>
#define ll long long
#define inf 1e8
#define rg register
using namespace std;
const int N=1e5+10;
inline ll read(){
	register ll s=0,f=0;
	register char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
int n,a[N],b[N],c[N],g[N],f[N],len,s[N];
inline int lowbit(int x){
	return x&(-x);
}
inline void update(int x,int y){
	for(int i=x;i<N;i+=lowbit(i)){
		if(s[i]<y)s[i]=y;
	}
}
inline int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)){
		if(ans<s[i])ans=s[i];
	}
	return ans;
}
map<int,int>m[N];
int main() {
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		f[i]=query(a[i]-1)+1;
		update(a[i],f[i]);
		if(len<f[i])len=f[i];
	}
	for(int i=1;i<=n;i++)b[i]=N-a[i];
	memset(s,0,sizeof(s));
	for(int i=n;i;i--){
		g[i]=query(b[i]-1)+1;
		update(b[i],g[i]);
	}
	for(int i=1;i<=n;i++){
		if(f[i]+g[i]<len+1)c[i]=1;
		else m[f[i]][g[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(f[i]+g[i]<len+1)continue;
		if(m[f[i]][g[i]]>1)c[i]=2;
		else c[i]=3;
	}
	for(int i=1;i<=n;i++)printf("%d",c[i]);
	return 0;
}
```


---

## 作者：一架飞机 (赞：11)

设 LIS 为最长上升子序列，总 LIS 为此数组的最长上升子序列（无其他限制条件），$len1_i$ 为以 $a_i$ 结束的 LIS 长度，$len2_i$ 为以 $a_i$ 开始的 LIS 长度。

因为 LIS 满足最优子结构，即 $a_i$ 在一个 LIS 中的位置一定等于 $len1_i$。所以通过 $a_i$ 的 LIS 长度等于 $len1_i+len2_i-1$。又因为“LIS 包含 $a_i$”相当于“通过 $a_i$ 能形成一个 LIS”。所以如果 $len1_i+len2_i-1$ 等于总 LIS 的长度，则总 LIS 可能包含 $a_i$，即输出2。

因为 $len1_i$ 等于 $a_i$ 在总 LIS 中的位置，所以“LIS 一定包含 $a_i$”相当于“这个位置只能是 $a_i$”，即“$len1_i$ 唯一（没有其他的 $len1$ 值和它相同）”，即输出3。

代码实现首先要知道 LIS 的 $O(n\log n)$ 求法。所以每次求出的 k 就是 $len1_i$。（k 详见代码）。然后再把数组反转求一次最长下降子序列，就是 $len2_i$。这里求最长下降子序列可以把数都乘以-1，然后求 LIS。最后判断一下。如果 $len1_i+len2_i-1$ 等于总 LIS 的长度，则输出2。如果 $len1_i+len2_i-1$ 等于总 LIS 的长度且 $len1$ 值唯一，则输出3。否则输出1。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define read(x) scanf("%d",&x)
const int M=1e5+5;
int a[M],b[M],dp[M],len1[M],len2[M],ty[M],vis[M];
int main(){
    int n;read(n);
    for(int i=1;i<=n;i++)read(a[i]);
    
    //求len1
    memset(dp,0x3f,sizeof(dp));dp[0]=0;
    for(int i=1;i<=n;i++){
        int k=lower_bound(dp+1,dp+n+1,a[i])-dp;
        dp[k]=a[i];
        len1[i]=k;//以a[i]结尾的LIS长度
    }
    int m=lower_bound(dp+1,dp+n+1,0x3f3f3f3f)-dp-1;//LIS长度
    
    //把数组反转 求len2
    for(int i=1;i<=n;i++)b[i]=-a[n-i+1];//负号：需要求反转后的最长下降子序列，添负号就变为最长上升子序列，然后就和上面一样
    memset(dp,0x3f,sizeof(dp));dp[0]=-1e9;
    for(int i=1;i<=n;i++){
        int k=lower_bound(dp+1,dp+n+1,b[i])-dp;
        dp[k]=b[i];
        len2[i]=k;
    }
    for(int i=1;i<=n;i++)if(len1[i]+len2[i]==m+1)ty[i]=2;else ty[i]=1;
    
    //求len1是否唯一，即ty[i]=3
    for(int i=1;i<=n;i++)if(ty[i]==2)vis[len1[i]]++;
    for(int i=1;i<=n;i++)if(vis[len1[i]]==1&&ty[i]==2)ty[i]=3;
    
    for(int i=1;i<=n;i++)printf("%d",ty[i]);
    return 0;
}
```



---

## 作者：AndyGamma (赞：10)

# 题意：
给你一个长度为n的序列a1,a2,...,an，你需要把这n个元素分成三类：1，2，3：

1:所有的最长上升子序列都不包含这个元素

2:有但非所有的最长上升子序列包含这个元素

3:所有的最长上升子序列都包含这个元素

# 题解：
首先，O(nlogn)求LIS大家应该都会吧……这里就不阐述了。

我们可以通过DP来算出以每个点i结尾的最长上升子序列的长度，记为length[i]，把整个序列的LIS长度记为len。

然后，大家要想明白一个命题：

如果元素i可能出现在LIS中，那么它在LIS中的位置一定刚好等于length[i]。

这个自证不难。

其次，我们可以用一个“分层数组”，其实所谓的“分层数组”就是一个二维数组，只不过我习惯把第一维叫做“层”罢了，第二维因为节省空间，我们开一个vector。

这个“分层数组”相当重要，它是我们解决问题的核心。我们在DP时就已经算出每个元素的length[i]了，因此我们把这个元素的编号添加到层数为length[i]的vector中去，因此“分层数组”中每一层的每个点就和序列中的元素一一对应。

这就是“分层数组”的建立过程，可参见代码注释。

然后呢？

大家又需要想明白两个命题：

在每一层中，随着编号的递增，与点对应的元素的值单调不递增。

每一层（除第一层外）中的每个点一定在前一层中有编号小于它且序列元素值小于它的节点。

考虑我们DP的过程，我们在更新dp数组中下标为length[i]的最小值时，如果已经通过二分查找算出该元素的length[i]，元素可以更新dp[length[i]]的条件是元素的值一定不能比dp[length[i]]大，而dp[length[i]]已经通过前面的元素算出，因此在“分层数组”层数为length[i]的层中，该元素的值一定小于等于在该层中编号比它小的元素的值。

另外，我们在DP时，依据dp数组单调递增的特性可以理解dp[length[i]-1]的值一定比a[i]小，因此在“分层数组”的前一层中，一定有编号小于它且序列元素值小于它的点，这样保证我们在逐层往前推的时候不会出现“一对空”的情况，而是在前一层中是有一个区间（包含编号、序列元素值两方面的限制）与之对应。这个区间中的点就是当前点在前一层中可以扩展到的节点。

大家可能有疑问：为什么要倒着从后往前推呢？

因为倒着推能够保证要扩展的当前点一定有LIS经过它，因此它扩展到的前一层的节点也一定有LIS经过，等到该层所有点扩展完毕后，前一层没有被扩展到的点一定没有LIS经过，打上“1”类标记，下次扩展就不要扩展这些点了。而其他的点都打上“2”类标记，如果只有一个“2”类标记，那么把“2”改成“3”，说明该节点是所有LIS的必经节点。

参考代码如下（若有不理解的参看注释）：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define maxn 100005
using namespace std;
int n,a[maxn];//整个序列
int dp[maxn];//dp[i]代表当前长度为i的上升子序列末尾元素的最小值
int len=0;//整个序列LIS的长度
int sign[maxn];//序列元素所属类别
vector<int>layer[maxn];//分层数组，一共有len层。layer[i]中的点表示这些元素：以这些元素结尾的最长上升子序列长度为i
inline int bins(int i,int val){
    int l=0,r=layer[i].size()-1;
    while(l<r){
        int m=(l+r)>>1;
        if(a[layer[i][m]]>=val)l=m+1;
        else r=m;
    }
    return l;
}
int main(){
    scanf("%d",&n);
    memset(dp,0x3f,sizeof(dp));
    dp[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        int length=lower_bound(dp,dp+n+1,a[i])-dp;//O(nlogn)求LIS
        dp[length]=min(dp[length],a[i]);
        //length表示以该元素结尾的最长上升子序列的长度
        layer[length].push_back(i);//加入到分层数组
        len=max(len,length);//更新整个序列的LIS长度
    }
    for(int i=1;i<=n;i++)sign[i]=1;//初始化全都为第1类，即任何LIS都不经过它们
    if(layer[len].size()==1)sign[layer[len][0]]=3;
    else for(int i=0;i<layer[len].size();i++)sign[layer[len][i]]=2;
    for(int i=len;i>=2;i--){//倒序处理分层数组，一层一层往前推
        for(int j=0;j<layer[i].size();j++){//枚举当前层的所有点
            int bh=layer[i][j];//点的编号
            if(sign[bh]>1){//如果当前节点可以向前扩展（存在LIS经过当前点）
                int l=bins(i-1,a[bh]);//二分查找，扩展的节点在序列中的值必须小于当前节点，才能保证LIS严格递增
                int r=lower_bound(layer[i-1].begin(),layer[i-1].end(),bh)-layer[i-1].begin()-1;//二分查找，扩展的点编号必须小于当前点编号，才能是“序列”
                //当前点可扩展到的前一层的点的范围是区间[l,r]
                for(int k=l;k<=r;k++)sign[layer[i-1][k]]=2;//打上标记，该节点能够被扩展到说明一定在整个序列中有某个LIS包含该点
            }
        }
        //当前层能够扩展到的前一层的点是当前层所有点能扩展到的前一层的节点的并集
        int cnt=0,pos=0;
        for(int j=0;j<layer[i-1].size();j++)if(sign[layer[i-1][j]]==2){
            cnt++;
            pos=j;
        }
        if(cnt==1)sign[layer[i-1][pos]]=3;//如果该层所有可扩展的点只能在前一层中扩展出一个节点，说明这个节点是所有LIS的必经节点。
    }
    for(int i=1;i<=n;i++)printf("%d",sign[i]);//不留空格打印
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：4)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15951459.html)

# 题目大意

给你一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$，你需要把这 $n$ 个元素分成三类：$1,2,3$：

1. 所有的最长上升子序列都不包含这个元素。

2. 有但非所有的最长上升子序列包含这个元素。

3. 所有的最长上升子序列都包含这个元素。

# 题目分析

令 $f_i$ 表示 $\{a_1,a_2,\cdots,a_i\}$ 的 $\rm LIS$ 长度，$g_i$ 表示 $\{a_i,a_{i+1},\cdots,a_n\}$ 的 $\rm LIS$ 长度，$len$ 表示 $\{a_1,a_2,\cdots,a_n\}$ 的 $\rm LIS$ 长度。

对于 $a_i$，若 $f_i+g_i\neq len+1$，说明 $a_i$ 这个点不在整个序列所有的 $\rm LIS$ 方案里。那么 $ans_i\gets 1$。

若 $f_i+g_i=len+1$，判断是否存在 $f_i=f_j$ 且 $g_i=g_j(i\neq j)$，则 $a_i$ 一定属于第二种情况：有但非所有的最长上升子序列包含这个元素。因为其他元素和 $a_i$ 某种意义上来说等价，都在其 $\rm LIS$ 中起到同样的作用。

其他情况为最后一种情况。

$f_i,g_i$ 可以用二分、线段树和树状数组在 $\mathcal{O(n\log n)}$ 的时间内求得，记录是否出现重复可以用桶或 $map$。树状数组码量小，完爆线段树；树状数组容易理解，完爆二分。故此处选择树状数组。

# 代码

```cpp
//2022/2/28 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <map>
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma = 1e5 + 5;
int a[ma],b[ma],f[ma],g[ma],ans[ma];
map<int,int>mp[ma];
int n;
struct BIT {
	int tr[ma];
	#define lowbit(x) (x & -x)
	inline void update(int x,int k) {
		for (;x < ma;x += lowbit(x)) {
			tr[x] = max(tr[x],k);
		}
	}
	inline int query(int x) {
		int res = 0;
		for (;x;x -= lowbit(x)) {
			res = max(res,tr[x]);
		}
		return res;
	}
	inline int getsum(int l,int r) {
		return query(r) - query(l - 1); 
	}
	#undef lowbit
} bita,bitb;
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	for (register int i = 1;i <= n; ++ i) b[i] = ma - a[i];//方便求 g[i]，直接将 a 序列的元素大小关系颠倒过来
	int maxx = 0;
	for (register int i = 1;i <= n; ++ i) {
		f[i] = bita.getsum(1,a[i] - 1) + 1;
		bita.update(a[i],f[i]);
		maxx = max(maxx,f[i]);
	}
	for (register int i = n;i >= 1; -- i) {
		g[i] = bitb.getsum(1,b[i] - 1) + 1;
		bitb.update(b[i],g[i]);
	}
	for (register int i = 1;i <= n; ++ i) {
		if (f[i] + g[i] == maxx + 1) {
			mp[f[i]][g[i]] ++;
		} else {//a[i] 不在任何最长上升子序列
			ans[i] = 1;
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		if (f[i] + g[i] == maxx + 1) {
			if (mp[f[i]][g[i]] >= 2) {
				ans[i] = 2;
			} else {
				ans[i] = 3;
			}
		}
	}
	for (register int i = 1;i <= n; ++ i) printf("%d",ans[i]);
	
	return 0;
}
```

---

## 作者：_Yonder_ (赞：2)

~~我把树状数组求前缀 $\max$ 写成求前缀和也是没谁了，还调了半天。~~

首先用树状数组把以 $i$ 为结尾的最长上升子序列的长度 $A_i$ 求出来，然后再倒过来求类别。

先判断第一类，若是 $\max\limits_{j=i+1}^na_j[A_j=A_i+1]\le a_i$ 那么就是第一类，用个 $F$ 数组来存每种 $A_i$ 的最大 $a_i$ 即可。

然后是第二类和第三类的区别，很明显，只要有两个相同长度的子序列都包含在任意一个最长上升子序列里（包含的子序列可以不同），那这两个子序列都是第二类，否则就是第三类。
# Code
```
#include<bits/stdc++.h>
#define S std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,l,r) for(int i=l;i>=r;i--)
#define ll long long
using namespace std;
const int N=1e5+5,M=5e3+5;
int T,n,a[N],tr[N],b[N],len,Max,ans,A[N],id[N],F[N],cnt[N],head[N];
void add(int x,int c){while(x<N) tr[x]=max(tr[x],c),x+=x&-x;}
int ask(int x){int ans=0;while(x) ans=max(ans,tr[x]),x-=x&-x;return ans;}
int main(){
	S;cin>>n;rep(i,1,n) cin>>a[i],b[++len]=a[i];
	sort(b+1,b+1+len);rep(i,1,n) a[i]=lower_bound(b+1,b+1+len,a[i])-b;
	rep(i,1,n){int c=ask(a[i]-1)+1;add(a[i],c);Max=max(Max,A[i]=c);}len=0;
	per(i,n,1){
		if(A[i]==Max){
			cnt[A[i]]++;
			if(cnt[A[i]]==1) head[A[i]]=i;
			else id[head[A[i]]]=2;
			F[A[i]]=max(F[A[i]],a[i]),id[i]=(cnt[A[i]]==1?3:2);
		}
		else{
			if(F[A[i]+1]<=a[i]){id[i]=1;continue;}
			cnt[A[i]]++;
			if(cnt[A[i]]==1) head[A[i]]=i;
			else id[head[A[i]]]=2;
			F[A[i]]=max(F[A[i]],a[i]);id[i]=(cnt[A[i]]==1?3:2);
		}
	}
	rep(i,1,n) cout<<id[i];
	return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

1. 线段树求出 $f_{i, 0/1}$ 表示以 $i$ 结尾的 LIS 长即其方案数。同理可以求出以 $i$ 开头的长度和方案 $g_{i, 0/1}$。
2. 记 $mx = \max(f_{i, 0}),\ tot = \sum[f_{i, 0} = mx]f_{i, 1}$。
3. 如果 $f_{i, 0} + g_{i, 0} - 1 < mx$，说明不经过任意 LIS。否则如果 $f_{i, 1}\times g_{i, 1} = tot$，说明所有方案都经过 $i$。

方案数是指数级别。类似哈希思想，用两个大质数取模后比对。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int N = 1e5 + 5, V = 1e5, P1 = 998244353, P2 = 1e9 + 7;

struct BigInteger {
	ll v1, v2;
	BigInteger(ll x = 0, ll y = 0)
		: v1(x), v2(y) {}
	BigInteger operator ++ () const {
		return {v1 + 1, v2 + 1};
	}
	bool operator ! () const {
		return !v1 && !v2;
	}
	friend BigInteger operator + (BigInteger a, BigInteger b) {
		return {(a.v1 + b.v1) % P1, (a.v2 + b.v2) % P2};
	}
	friend BigInteger operator * (BigInteger a, BigInteger b) {
		return {(a.v1 * b.v1) % P1, (a.v2 * b.v2) % P2};
	}
	friend bool operator == (BigInteger a, BigInteger b) {
		return a.v1 == b.v1 && a.v2 == b.v2;
	}
};

struct Node {
	int mx; BigInteger num;
	friend Node operator + (Node a, Node b) {
		if(a.mx > b.mx) return a;
		if(a.mx < b.mx) return b;
		return {a.mx, a.num + b.num};
	}
} t[N << 2];

#define ls x << 1
#define rs ls | 1
void init(int x = 1, int l = 1, int r = V) {
	t[x] = {0, 0};
	if(l == r) return;
	int mid = l + r >> 1;
	init(ls, l, mid), init(rs, mid + 1, r);
}
void update(int p, Node v, int x = 1, int l = 1, int r = V) {
	if(l == r) {
		t[x] = t[x] + v;
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) update(p, v, ls, l, mid);
	else update(p, v, rs, mid + 1, r);
	t[x] = t[ls] + t[rs];
}
Node query(int L, int R, int x = 1, int l = 1, int r = V) {
	if(L > R) return {0, 1};
	if(L <= l && r <= R) return t[x];
	int mid = l + r >> 1;
	Node ret = {0, 0};
	if(L <= mid) ret = ret + query(L, R, ls, l, mid);
	if(R > mid) ret = ret + query(L, R, rs, mid + 1, r);
	return ret;
}
Node f[N], g[N];	//	以 i 结尾/开头的LIS长度，方案。
int n, a[N], mx;
BigInteger tot;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for(int i = 1; i <= n; ++ i) {
		cin >> a[i];
		f[i] = query(1, a[i] - 1);
		++ f[i].mx;
		if(!f[i].num) f[i].num = 1;
		update(a[i], f[i]);
		mx = max(mx, f[i].mx);
	}
	init();
	for(int i = n; i >= 1; -- i) {
		g[i] = query(a[i] + 1, V);
		++ g[i].mx;
		if(!g[i].num) g[i].num = 1;
		update(a[i], g[i]);
		if(g[i].mx == mx) tot = tot + g[i].num;
	}
	for(int i = 1; i <= n; ++ i) {
		if(f[i].mx + g[i].mx - 1 != mx) {
			cout << 1;
		}
		else if(f[i].num * g[i].num != tot) {
			cout << 2;
		}
		else cout << 3;
	}
	return 0;
}
```

---

## 作者：include13_fAKe (赞：0)

线段树优化 dp 最板的题，[NOIP2023 天天爱打卡](https://www.luogu.com.cn/problem/P9871) 其实是它的大幅加强版。

考虑求出 $f,g$ 数组。$f_i$ 分别表示 $[1,i]$ 要选第 $i$ 个数的最长上升子序列，$g_i$ 表示子段 $[i,n]$ 要选第 $i$ 个数的最长上升子序列。线段树优化时间复杂度 $O(n\log V)$。实际上 $n$ 和 $V$ 是同阶的。

全序列最长上升子序列即为 $\max\left \{ f_i+g_i-1 \right \} $。以下令其为 $k$。

若 $f_i+g_i-1<k$ 表示不存在一个最长上升子序列包含 $i$ 所以 $i$ 是一类点。以下不再讨论一类点。

若 $(f_i,g_i)$ 的值是唯一的，则这个点是三类点，无法替代。

剩余的为二类点。


```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int num[114514];
int f[114514],g[114514];
struct node{
	int l,r;
	int max_;
	int tag;
}tree[5*114514];
int include13[114514];
map<int,map<int,int> > solve1;
void pushup(int id){
	tree[id].max_=max(tree[id*2].max_,tree[id*2+1].max_);
}
void pushdown(int id){
	tree[id*2].tag=max(tree[id].tag,tree[id*2].tag);
	tree[id*2+1].tag=max(tree[id].tag,tree[id*2+1].tag);
	tree[id*2].max_=max(tree[id*2].max_,tree[id*2].tag);
	tree[id*2+1].max_=max(tree[id*2+1].max_,tree[id*2+1].tag); 
}
void build(int id,int l,int r){
//	cout<<id<<' '<<l<<' '<<r<<endl;
	tree[id].l=l;
	tree[id].r=r;
	tree[id].tag=0;
	if(l==r){
		tree[id].max_=0;
		return;
	}
	int mid=l+r>>1;
	build(id*2,l,mid),build(id*2+1,mid+1,r);
	pushup(id);
}
void modify(int id,int p,int sum){
	int l=tree[id].l,r=tree[id].r;
	pushdown(id);
	if(l==r){
		tree[id].max_=max(tree[id].max_,sum);
		tree[id].tag=max(tree[id].tag,sum);
		return;
	}
	int mid=l+r>>1;
	if(p<=mid)	modify(id*2,p,sum);
	else modify(id*2+1,p,sum);
	pushup(id);
}
int query(int id,int l,int r){
	int l1=tree[id].l,r1=tree[id].r;
//	cout<<id<<' '<<l<<' '<<r<<endl;
	pushdown(id);
	if(l1>=l&&r1<=r){
		return tree[id].max_;
	}
	int mid=l1+r1>>1;
	int ret=0;
	if(l<=mid)	ret=max(ret,query(id*2,l,r));
	if(r>mid)	ret=max(ret,query(id*2+1,l,r));
	pushup(id);
	return ret;
}
int ans1;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>num[i];
	}
	build(1,0,100005);
//	modify(1,0,0);
	for(int i=1;i<=n;i++){
		f[i]=query(1,0,num[i]-1)+1;
//		cout<<query(1,0,num[i]-1)+1<<endl;
		modify(1,num[i],f[i]);
	}
//	for(int i=1;i<=n;i++){
//		cout<<f[i]<<' ';
//	}
//	cout<<endl;
	build(1,0,100005);
	for(int i=n;i>=1;i--){
		g[i]=query(1,num[i]+1,100005)+1;
		modify(1,num[i],g[i]);
	}
//	for(int i=1;i<=n;i++){
//		cout<<g[i]<<' ';
//	}
//	cout<<endl;
	for(int i=1;i<=n;i++){
		ans1=max(ans1,f[i]+g[i]-1);
	}
//	ans1=f[n]+g[n]-1;
	for(int i=1;i<=n;i++){
		if(f[i]+g[i]-1!=ans1){
			include13[i]=1;
		}
		else{
			solve1[f[i]][g[i]]++;
		}
	}
	for(int i=1;i<=n;i++){
		if(include13[i]!=1){
			if(solve1[f[i]][g[i]]>1)	include13[i]=2;
			else	include13[i]=3;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<include13[i];
	}
	cout<<endl;
	return 0;
}//CF486E 
```

---

