# Good Subarrays (Easy Version)

## 题目描述

This is the easy version of this problem. In this version, we do not have queries. Note that we have multiple test cases in this version. You can make hacks only if both versions of the problem are solved.

An array $ b $ of length $ m $ is good if for all $ i $ the $ i $ -th element is greater than or equal to $ i $ . In other words, $ b $ is good if and only if $ b_i \geq i $ for all $ i $ ( $ 1 \leq i \leq m $ ).

You are given an array $ a $ consisting of $ n $ positive integers. Find the number of pairs of indices $ (l, r) $ , where $ 1 \le l \le r \le n $ , such that the array $ [a_l, a_{l+1}, \ldots, a_r] $ is good.

## 说明/提示

In the first test case, all subarrays of $ a $ are good, so all pairs are suitable.

In the second test case, the pairs $ (1, 1) $ , $ (2, 2) $ , and $ (3, 3) $ are suitable. For example, when $ (l, r) = (1, 2) $ , the array $ b=[1,1] $ is not good because $ b_2 < 2 $ .

## 样例 #1

### 输入

```
3
3
1 2 3
3
1 1 1
4
2 1 4 3```

### 输出

```
6
3
7```

# 题解

## 作者：lenlen (赞：10)

### Problem

题目大意：给你一个数组，定义一个序列是好的为在序列 $[l,r]$ 中，满足 $\forall i,a_i \geq i-l+1$，求原序列有多少个子序列是好的。

数据范围： $t \leq 2 \times 10^5,\sum n \leq 2 \times 10^5$。

### Solution

我们可以对 $a_i \geq i-l+1$ 进行化简：

$$ a_i \geq i-l+1 \Rightarrow l \geq i+1-a_i$$

这样的话，我们可以对于每个 $i$ 求出 $b_i=i+1-a_i$。

因为 $l$ 的单调递增，那么这个题显然就变成了对于每个 $i$ 找到一个最小的 $l$，满足 $l \geq \max\limits_{k=l}^i b_k$。

维护 $\max$ 我们可以用倍增或者线段树去维护，而我们可以发现，在查找最小的 $l$ 时，若 $p$ 满足条件，那么 $p+1$ 也肯定满足条件，所以容易发现 $l$ 具有单调性，可以用二分来查找。

时间复杂度 $O(n \log n)$。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7232,inf=1e9+7;
int T,n;
long long ans,a[N],f[N][32],lg[N];
int mx(int x,int y)
{
    return x<y?y:x;
}
void init()
{
    int ln=log2(n);
    for(int i=1;i<=ln;i++)
    for(int j=1;j+(1<<i-1)<=n;j++) f[j][i]=mx(f[j][i-1],f[j+(1<<i-1)][i-1]);
}
int main()
{
    scanf("%d",&T);
    for(int i=2;i<=2e5;i++) lg[i]=lg[i>>1]+1;
    while(T--)
    {
        scanf("%d",&n);
        ans=0;
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]=i+1-a[i],f[i][0]=a[i];
        init();//倍增
        for(int i=1;i<=n;i++)
        {
            int l=1,r=i,num=-1;
            while(l<=r) 
            {
                int mid=l+r>>1;
                int tmp=lg[i-mid+1];
                if(mx(f[mid][tmp],f[i-(1<<tmp)+1][tmp])<=mid) r=mid-1,num=mid;
                else l=mid+1;
            }
            if(num!=-1) ans+=i-num+1;
        }
        printf("%lld\n",ans);
    }
}
```


---

## 作者：with_no_signal (赞：8)

# 题目大意

求出给定序列中有多少子序列为“好的”。

定义一个子序列为“好的”，当且仅当该序列第 $i$ 个元素的值大于等于 $i$。

## 思路

我们可以发现：若序列 $[l,r]$ 是满足条件的序列，那么序列 $[l+1,r]$ 必然满足条件。

定义变量 $nw$ 表示在输入 $a_i$ 时满足 $[l,i]$ 是好的序列的最小的值，用 $i+1-a_i$ 和 $nw$ 中的较大值更新 $nw$ 即可。

如果有什么不明白的可以结合代码理解一下。



```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n;
int a[200005];
int cnt[200005];
int nw;
int sum=0;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		nw=1;
		sum=0;
		for(int i=1;i<=n;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			nw=max(nw,i+1-a[i]);
			sum=sum+i-nw+1;
		}
		cout<<sum<<"\n";
	}
	return 0;
}
```


---

## 作者：loser_seele (赞：2)

不会二分，于是写了题解里没有的人类智慧双指针。

一个奇怪的思路：注意到 $ a_i \geq i-l+1 $ 等价于 $ -a_i \leq l-i-1 $ ，而后面这个东西随着 $ l $ 的增加满足条件的区间右端点一定单调不减，因为原本符合条件的数字现在一定还是符合条件。

于是直接用双指针维护符合条件的数，左端点右移的时候不断增加符合条件的右指针即可。

因为两个指针都单调不减，所以时间复杂度为 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
int l=1,r=1,a[maxn];
bool check(int x)
{
return -a[x]<=-x+l-1;
}
signed main()
{
int T;
cin>>T;
while(T--)
{
int n;
cin>>n;
for(int i=1;i<=n;i++)
cin>>a[i];
l=1,r=1;
int ans=0;
while(l<=n)
{
while(!check(l)&&l<=n)
l++;
if(l>n)
break;
while(check(r)&&r<=n)
r++;
r--;
ans+=r-l+1;
l++;
}
cout<<ans<<'\n';
}
}
```


---

## 作者：hy233 (赞：1)

写一个没人写的双指针做法。

我们形象到图上，如果一个连续子序列 $ [l,r] $ 是好的，相当于对于所有 $i \in[l,r]$ ， $a_i$ 的点在从 $l$ 开始，斜率为 $1$ 的直线上。
![](https://cdn.luogu.com.cn/upload/image_hosting/4lj1w77c.png)

如果我们将 $l$ 右移一格，相当于将直线右移一单位，而点显然不变。于是若 $[l,r]$ 合法，则 $[l+1,r]$ 当然也合法。
![](https://cdn.luogu.com.cn/upload/image_hosting/i0oeqdgy.png)

这样我们就可以双指针做了，每次将 $l$ 右移一单位时直接暴力往右更新 $r$ ，当前答案即为 $r-l+1$ ，累加即可。

---

## 作者：qwq___qaq (赞：0)

### 警钟长鸣

由于 C1 思路过于复杂，导致 C2 无法解出。

### 正文

CF 上的标签写的是 `two points`，意思是双指针，不过我的做法不同。

首先注意到每个店都会有一个最远的可以选择的左端点，记作 $p_i$。考虑到一个区间 $[l,r]$ 是否可以选择，就必须保证 $\forall i\in[l,r],p_i\le l$，可以转化为 $\max\limits_{i=l}^ra_i\le l$。于是，可以自然地想到使用 ST 表维护 $p_i$ 的静态区间最大值。

我们可以考虑 $O(n)$ 地固定左端点，然后求出右端点可以取的值的数量。容易发现此处具有单调性：对于同一个 $l$，如果一个 $r$ 可行，那么 对于所有 $r'<r$，都是可行的。

于是考虑二分，找到每个 $l$ 对应的最大的 $r$，答案就是 $\sum\limits_{l=1}^nr-l+1$。

时空复杂度均为 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int T,n,a[maxn],Log[maxn],dp[maxn][20];
inline int Qmax(int l,int r){
	int k=Log[r-l+1];
	return max(dp[l][k],dp[r-(1<<k)+1][k]);
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;++i){
			scanf("%lld",&a[i]);
			dp[i][0]=i-a[i]+1;
		}
		for(int i=2;i<=n;++i)
			Log[i]=Log[i>>1]+1;
		for(int j=1;(1<<j)<=n;++j)
			for(int i=1;i+(1<<j)-1<=n;++i)
				dp[i][j]=max(dp[i][j-1],dp[i+(1<<j-1)][j-1]);
		int ans=0;
		for(int i=1;i<=n;++i){
			int l=i,r=n;
			while(l<r){
				int mid=l+r+1>>1;
				if(Qmax(i,mid)>i)
					r=mid-1;
				else
					l=mid;
			}
			ans+=(r-i+1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：GI录像机 (赞：0)

## 思路：

考虑建立一个数组 $v_i$，表示以 $i$ 为左端点的区间个数有多少个。

枚举右端点 $r$，考虑此端点能作为几个区间的右端点。容易发现 $[l,r]$ 作为左端点都是能够满足条件的，其中 $l$ 是第一个满足题设的左端点。因为 $l$ 必定不降，可以采用双指针维护 $l$。维护时只需判断当前 $r$ 是否满足 $a_r\ge r-l+1$，若不满足，考虑使用下一位作为 $l$。每次枚举将满足 $l\le i\le r$ 的 $v_i$ 加一，可使用差分，时间复杂度为 $O(n)$。但我喜欢用线段树，就用了线段树。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int t = read(), n, a[N], v[N << 2], lazy[N << 2];
void pushup(int pos) {
	v[pos] = v[pos << 1] + v[pos << 1 | 1];
}
void pushdown(int pos, int l, int r) {
	int mid = (l + r) >> 1;
	lazy[pos << 1] += lazy[pos];
	lazy[pos << 1 | 1] += lazy[pos];
	v[pos << 1] += (mid - l + 1) * lazy[pos];
	v[pos << 1 | 1] += (r - mid) * lazy[pos];
	lazy[pos] = 0;
}
void build(int pos, int l, int r) {
	lazy[pos] = v[pos] = 0;
	if (l == r)return;
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
}
void add(int pos, int l, int r, int L, int R, int k) {
	if (L <= l && r <= R) {
		v[pos] += (r - l + 1) * k;
		lazy[pos] += k;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(pos, l, r);
	if (L <= mid)add(pos << 1, l, mid, L, R, k);
	if (mid + 1 <= R)add(pos << 1 | 1, mid + 1, r, L, R, k);
	pushup(pos);
}
int query(int pos, int l, int r, int L, int R) {
	if (L <= l && r <= R)return v[pos];
	int mid = (l + r) >> 1, ans = 0;
	pushdown(pos, l, r);
	if (L <= mid)ans += query(pos << 1, l, mid, L, R);
	if (mid + 1 <= R)ans += query(pos << 1 | 1, mid + 1, r, L, R);
	return ans;
}
signed main() {
	while (t--) {
		n = read();
		build(1, 1, n + 1);
		int l = 1, ans = 0;
		for (int i = 1; i <= n; i++) {
			a[i] = read();
			while (i - l + 1 > a[i])l++;
			add(1, 1, n, l, i, 1);
		}
		write(query(1, 1, n, 1, n));
		putchar('\n');
	}
	return 1919810 - 1919810;
}
```


---

## 作者：Masna_Kimoyo (赞：0)

给个没脑子直接草过去的做法。

可以先预处理出所有数能到的位置。钦定一个点，看这个点的左端点最远能到哪。

很显然是有单调性的，越远可能性越小，所以搞个二分。

如果当前位置是可以的，那它一定大于在这段区间中所有点能到的最远位置。

所以 `check` 很简单，看下区间里最近的最远位置是不是包含了当前点就可以了。

维护“最近”用一个线段树，求最大值。

```cpp
#include<bits/stdc++.h>
#define int long long
#define printlf(x) print(x),putchar('\n')
#define printsp(x) print(x),putchar(' ')
using namespace std;
inline int read(){
    int x=0;
    bool w=0;
    char c=getchar();
    while(!isdigit(c))  w|=c=='-',c=getchar();
    while(isdigit(c))   x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void print(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) print(x/10);
    putchar('0'+x%10);
}
const int N=2e5+5;
int a[N],pos[N];
int tree[N*3];
int n;
#define ls(x) x<<1
#define rs(x) x<<1|1
inline void push_up(int p){
    tree[p]=max(tree[ls(p)],tree[rs(p)]);
}
inline void Build(int p,int l,int r){
    if(l==r){
        tree[p]=pos[l];
        return ;
    }
    int mid=l+r>>1;
    Build(ls(p),l,mid);
    Build(rs(p),mid+1,r);
    push_up(p);
}
inline int query(int p,int l,int r,int pl,int pr){
    //cout<<pl<<' '<<pr<<' '<<l<<' '<<r<<" edededede\n";
    if(l>=pl && r<=pr)  return tree[p];
    int mid=l+r>>1,res=0;
    if(pl<=mid) res=max(res,query(ls(p),l,mid,pl,pr));
    if(pr>mid)  res=max(res,query(rs(p),mid+1,r,pl,pr));
    return res;
}
inline int Solve(){
    n=read();
    int ans=0;
    for(register int i=1;i<=n;++i)  a[i]=read();
    for(register int i=1;i<=n;++i)  pos[i]=max(1ll,i-a[i]+1);
    //for(register int i=1;i<=n;++i)  cout<<pos[i]<<' ';cout<<" pos\n";
    Build(1,1,n);
    //cout<<" buildok\n";
    for(register int i=1;i<=n;++i){
        int l=pos[i],r=i,res=0;
        //cout<<l<<' '<<r<<" startlr\n";
        while(l<=r){
            int mid=l+r>>1;
            if(query(1,1,n,mid,i)<=mid)  r=mid-1,res=mid;
            else    l=mid+1;
        }
        ans+=i-res+1;
    }
    return ans;
}
signed main(){
    int T=read();
    while(T--){
        printlf(Solve());
    }
    return 0;
}

```

---

## 作者：Tx_Lcy (赞：0)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16799023.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1736C1)
## 思路
给出一种不需要脑子的做法。

首先我们把每个 $a_i$ 都减去 $i$，这样原问题就转化为对于每一个左端点 $i$，寻找一段连续的区间，使得这段区间的最小值加上 $i-1$ 后 $\ge 0$。

容易发现这个东西具有单调性，显然可以双指针维护，因为~~我懒~~没有什么优化的必要，所以可以简单地用二分水过。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
int a[N],f[N][20],lg[N];
inline int query(int l,int r){
    int p=lg[r-l+1];
    return min(f[l][p],f[r-(1<<p)+1][p]);
}
signed main(){
    int t;cin>>t;
    while (t--){
        int n;cin>>n;
        for (int i=1;i<=n;++i) io.read(a[i]),a[i]-=i,f[i][0]=a[i];
        for (int j=1;j<=19;++j)
            for (int i=1;i+(1<<(j-1))<=n;++i)
                f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        lg[0]=lg[1]=0;
        for (int i=2;i<=n;++i) lg[i]=lg[i>>1]+1;
        int ans=0;
        for (int i=1;i<=n;++i){
            int l=i,r=n;
            while (l<r){
                if (l+1==r){if (query(i,r)+i-1>=0) l=r;break;}
                int mid=(l+r)>>1;
                if (query(i,mid)+i-1>=0) l=mid;
                else r=mid-1;
            }
            ans+=(l-i+1);
        }
        cout<<ans<<'\n';
    }
    return 0;
}

```


---

