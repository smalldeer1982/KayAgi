# Choose

## 题目背景

[加强版](https://www.luogu.com.cn/problem/U397746)

对于一个长度为 $n$ 的序列 $a$ ，定义 $a$ 的极差表示 $a$ 中最大值与最小值之差；定义 $C(a,l,r)$ 表示 $a$ 的**连续**子序列 $[a_l,a_{l+1},\dots,a_r]$，其中 $1\le l\le r\le n$。

## 题目描述

给定一个长度为 $n$ 的序列 $a$。

你需要选出 $a$ 的 $k$ 个长度均为 $L$ $(1\le L\le n-k+1)$ 的不同**连续**子序列 
$C(a,l_1,l_1+L-1),C(a,l_2,l_2+L-1),\dots,C(a,l_k,l_k+L-1)$，其中 $1\le l_1<l_2< \dots< l_k\le n-L+1$。

记这 $k$ 个子序列中极差的最小值为 $X$，你需要求出 $X$ 的最大值。同时，你还需要求出，在满足 $X$ 最大的情况下  $L$ 的最小值。

## 说明/提示

**【样例 1 解释】**

- $k=1$ 时，极差最大不超过 $4$，此时满足长度最短的一种方案为 $[1,2,3,4,5]$。
- $k=2$ 时，极差最大不超过 $3$，此时满足长度最短的一种方案为 $[1,2,3,4],[2,3,4,5]$。
- $k=3$ 时，极差最大不超过 $2$，此时满足长度最短的一种方案为 $[1,2,3],[2,3,4],[3,4,5]$。

**【数据规模与约定】**

**本题采用捆绑测试。**

| 子任务 | 分值 | $n\le$ | $k\le$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $10^5$ | $n$ | $a_i$ 均相等 |
| $2$ | $5$ | $10^5$ | $1$ | 数据随机生成 |
| $3$ | $10$ | $100$ | $n$ | 所求的 $X$ 不超过 $10^3$ |
| $4$ | $20$ | $100$ | $n$ | 无 |
| $5$ | $20$ | $10^4$ | $n$ | 无 |
| $6$ | $40$ | $10^5$ | $n$ | 无 |

对于 $100\%$ 的数据，$1\le T\le 10$，$1\le n\le 10^5$，$1\le k\le n$，$-10^9\le a_i\le 10^9$。

## 样例 #1

### 输入

```
3
5 1
1 2 3 4 5
5 2
1 2 3 4 5
5 3
1 2 3 4 5```

### 输出

```
4 5
3 4
2 3```

## 样例 #2

### 输入

```
2
5 1
1 2 2 2 3
5 2
1 2 2 2 3```

### 输出

```
2 5
1 2```

# 题解

## 作者：white_tiger_yyyy (赞：14)

[博客食用更佳。](https://www.luogu.com.cn/blog/546441/p10059-choose)
# 正篇开始
考虑题目中很重要的一句话：
+ 记这 $k$ 个子序列中极差的最小值为 $X$，你需要求出 $X$ 的最大值。

很明显，要求最小值最大，显然二分答案。那么问题来了，二分什么呢？

---
现在有两个选择：二分极差、二分长度。

很明显，前者可以一次性都算出来，但是十分麻烦，无从下手；后者只能算出长度，但是二分思路很简单。这个时候，我们就需要发现一些性质了。
### 性质1：区间 $[l,r]$ 的子区间求出的极差绝对没有该区间大。
### 性质2：所有长度为 $l$ 的区间，都可以被长为 $l+1$ 的区间包含。
根据这两个性质，显而易见就可以推导出结论：
### 结论：区间长度越长，答案或更优，或不变。
这样，一个贪心求极差的方法显然出现：直接枚举所有长度为 $n-k+1$ 的区间，求出这些区间的极差最小值 $X'$，第一个答案即为 $X'$。

既然我们可以求出极差，那么我们就不需要二分极差，因此只能二分长度。但是问题接踵而至：如何快速计算区间极差呢？

---
解决这个问题，我们需要知道一件事情：区间极差=区间最大值-区间最小值。

问题转化为：如何快速求出静态区间最大/最小值？

用线段树自然可以，但是时间复杂度不如 RMQ。现在，我们只需要解决 $\operatorname{check}$ 函数即可。

---
$\operatorname{check}$ 函数的思路其实很普通。

二分长度，当该长度的区间中，有大于等于 $k$ 个大于 $X$，返回 $1$，否则返回 $0$。

现在我们会发现，使用线段树，时间复杂度会多一个 $\log$，而根据分析，原先的时间复杂度为 $O(n\log_2n)$，已经容不得 $n\log^2_2n$ 了。

空间复杂度最大是 RMQ，空间复杂度 $O(n\log_2n)$，最好预处理 $\log$。

---
标程
```cpp
#include<bits/stdc++.h>
#define N 100005
#define M 1000005
using namespace std;
int t,n,k,a[N],mx[M],mn[N],ans1;
int lg[N],f[N][20],dp[N][20];
void build(){
    for(int i=1;i<=100000;i++)
        for(int j=1;j<17;j++) f[i][j]=-1e9-1;
    for(int i=1;i<=100000;i++)
        for(int j=1;j<17;j++) dp[i][j]=1e9+1;
    for(int i=1;i<=n;i++) f[i][0]=dp[i][0]=a[i];
    for(int j=1;j<17;j++)
        for(int i=1;i+(1<<j)-1<=n;i++){
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
        }
}int qmax(int l,int r){
    int zjy=lg[r-l+1];
    return max(f[l][zjy],f[r-(1<<zjy)+1][zjy]);
}int qmin(int l,int r){
    int zjy=lg[r-l+1];
    return min(dp[l][zjy],dp[r-(1<<zjy)+1][zjy]);
}int check(int x){
    int sum=0;
    for(int i=1;i<=n-x+1;i++){
        int lyh=qmax(i,i+x-1);
        int zjy=qmin(i,i+x-1);
        if(lyh-zjy>=ans1) sum++;
    }return sum>=k;
}int main(){
    for(int i=1;i<N;i++) lg[i]=log2(i);
    cin>>t;while(t--){
        cin>>n>>k;ans1=2e9+1;
        for(int i=1;i<=n;i++) cin>>a[i];
        build();
        for(int i=1;i<=k;i++)
            ans1=min(ans1,qmax(i,n-k+i)-qmin(i,n-k+i));
        cout<<ans1<<" ";int l=1,r=n-k+1,ans2;
        while(l<=r){
            int mid=(l+r)/2;
            if(!check(mid)) l=mid+1;
            else r=mid-1,ans2=mid;
        }cout<<ans2<<"\n";
    }return 0;
}
```
---
赛后还有加强版，这会主要卡空间，所以无法支付 RMQ 的空间。

考虑单调队列。由于本题所需要的最大最小值，实际上是滑动窗口板子，所以可以将空间复杂度压缩至 $O(n)$。代码就不写了，留给大家探索。

---

## 作者：_JF_ (赞：9)

by Ecrade_

**结论：** 记长度为 $L$ 时对应的 $X$ 最大值为 $f(L)$，则 $f(L)$ 单调不降。

---
**证明：**

对于任意长度 $2\le L\le n-k+1$，记 $a$ 所有长度为 $L$ 的子序列的极差依次为 $p_1,p_2,\dots,p_{n-L+1}$，记 $p$ 从大到小排序后所的序列为 $p'_1,p'_2,\dots,p'_{n-L+1}$，则 $f(L)=p'_k$；同样地，记 $a$ 所有长度为 $L-1$ 的子序列的极差依次为 $q_1,q_2,\dots,q_{n-L+2}$，记 $q$ 从大到小排序后所的序列为 $q'_1,q'_2,\dots,q'_{n-L+2}$，则 $f(L-1)=q'_k$。

故我们仅需证明 $p'_k\ge q'_k$ 即可。而不难发现，$\forall 1\le i\le n-L+1$，$p_i\ge q_i$ 且 $p_i\ge q_{i+1}$，由此可推出 $p$ 中至少有 $k$ 个数不小于 $q'_k$，进一步推出 $p'_k\ge q'_k$。

故命题 $p'_k\ge q'_k$ 成立，即 $f(L)$ 单调不降。

---
故 $X$ 最大值即为 $f(n-k+1)$，极差可用单调队列求得。$L$ 最小值有两种方法求。

### 法一

直接上二分，具体实现见代码。

时间复杂度 $O(Tn\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[100009];
int qs[100009],qb[100009];
inline int read(){
	int s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
int work(int x,int lim,bool opt){
	int res = 2e9,cnt = 0,hs = 1,ts = 0,hb = 1,tb = 0;
	for (int i = 1;i <= n;i += 1){
		while (ts >= hs && i - qs[hs] + 1 > x) hs += 1;
		while (tb >= hb && i - qb[hb] + 1 > x) hb += 1;
		while (ts >= hs && a[i] < a[qs[ts]]) ts -= 1;
		while (tb >= hb && a[i] > a[qb[tb]]) tb -= 1;
		qs[++ ts] = i,qb[++ tb] = i;
		if (opt == 0 && i >= x) res = min(res,a[qb[hb]] - a[qs[hs]]);
		if (opt == 1 && i >= x && a[qb[hb]] - a[qs[hs]] >= lim) cnt += 1;
		if (opt == 1 && cnt >= k) break;
	}
	if (opt == 0) return res;
	if (cnt < k) return 0;
	return 1;
}
int main(){
	t = read();
	while (t --){
		n = read(),k = read();
		for (int i = 1;i <= n;i += 1) a[i] = read();
		int xans = work(n - k + 1,0,0),lans = n - k + 1,l = 1,r = n - k + 1;
		while (l <= r){
			int mid = (l + r) >> 1;
			if (work(mid,xans,1)) lans = mid,r = mid - 1;
			else l = mid + 1;
		}
		printf("%d %d\n",xans,lans);
	}
	return 0;
}
```

### 法二

考虑对于每个长度 $L$，求出极差不小于 $X$ 最大值的区间个数 $c_L$。

从小到大枚举 $i$，求出以 $i$ 为左端点的极差不小于 $X$ 最大值的**极短**连续区间，记该区间右端点为 $r_i$，则对所有 $r_i-i+1\le L\le n-i+1$ 都执行 $c_L\gets c_L+1$。

具体实现上，由于所有极短连续区间均无包含关系，故可使用单调队列 + 双指针求得；由于每次执行 $c_L\gets c_L+1$ 的 $L$ 都是一段连续区间，故可用前缀和记录。

时间复杂度 $O(Tn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[100009],cnt[100009];
int qs[100009],qb[100009];
inline int read(){
	int s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
int main(){
	t = read();
	while (t --){
		n = read(),k = read();
		for (int i = 1;i <= n;i += 1) a[i] = read(),cnt[i] = 0;
		int xans = 2e9,lans = 0,hs = 1,ts = 0,hb = 1,tb = 0,r = 0,all = 0;
		for (int i = 1;i <= n;i += 1){
			while (ts >= hs && i - qs[hs] > n - k) hs += 1;
			while (tb >= hb && i - qb[hb] > n - k) hb += 1;
			while (ts >= hs && a[i] < a[qs[ts]]) ts -= 1;
			while (tb >= hb && a[i] > a[qb[tb]]) tb -= 1;
			qs[++ ts] = i,qb[++ tb] = i;
			if (i >= n - k + 1) xans = min(xans,a[qb[hb]] - a[qs[hs]]);
		}
		hs = 1,ts = 0,hb = 1,tb = 0;
		for (int i = 1;i <= n;i += 1){
			while (ts >= hs && qs[hs] < i) hs += 1;
			while (tb >= hb && qb[hb] < i) hb += 1;
			while (r < n && (ts < hs || tb < hb || a[qb[hb]] - a[qs[hs]] < xans)){
				r += 1;
				while (ts >= hs && a[r] < a[qs[ts]]) ts -= 1;
				while (tb >= hb && a[r] > a[qb[tb]]) tb -= 1;
				qs[++ ts] = r,qb[++ tb] = r;
			}
			if (a[qb[hb]] - a[qs[hs]] < xans) break;
			cnt[r - i + 1] += 1,cnt[n - i + 2] -= 1;
		}
		for (int i = 1;i <= n;i += 1) cnt[i] += cnt[i - 1];
		while (cnt[lans] < k) lans += 1;
		printf("%d %d\n",xans,lans);
	}
	return 0;
}
```
---
by \_JF_

沿袭上面的做法，其实验题人在二分完 $L$ 后采用数据结构维护区间最值来进行检验是否合法。（可能好像写，好像赛时大部分人也是这么写的）

这样做的复杂度是 $O(Tn\log^2 n)$ 的，没有卡掉，也可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e5+10;
int F[N][20],f[N][20],dis[N],a[N],Log[N],n,k;
inline int read()
{
    register int x=0,f=0;
    register char t=getchar();
    while(t<'0'||t>'9')f^=(t=='-'),t=getchar();
    while(t>='0'&&t<='9')x=(x<<3)+(x<<1)+(t^48),t=getchar();
    return f?-x:x;
}
bool cmp(int a,int b){
	return a>b;
}
int QueryMax(int l,int r){
	int k=Log[r-l+1];
	return max(f[l][k],f[r-(1<<k)+1][k]);
}
int QueryMin(int l,int r){
	int k=Log[r-l+1];
//	cout<<l<<" "<<r<<" "<<k<<" "<<F[l][k]<<endl;
	return min(F[l][k],F[r-(1<<k)+1][k]);
}
void init(){
	memset(f,-0x3f,sizeof(f)),memset(F,0x3f,sizeof(F));
// 	for(int j=0;j<=Log[n];j++)
// 		for(int i=0;i+(1<<j)-1<=n;i++)
// 			F[i][j]=INT_MAX,f[i][j]=-INT_MAX;
	for(int i=1;i<=n;i++)
		F[i][0]=a[i],f[i][0]=a[i];
	for(int j=1;j<=Log[n];j++)
		for(int i=1;i+(1<<j)-1<=n;i++){
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
			F[i][j]=min(F[i][j-1],F[i+(1<<(j-1))][j-1]);
		}	
}
int check(int len){
	int p=0;
	for(int i=1;i+len-1<=n;i++){
		int maxx=QueryMax(i,i+len-1),minn=QueryMin(i,i+len-1);
		dis[++p]=maxx-minn;
//		cout<<i<<" "<<i+len-1<<" "<<maxx<<" "<<minn<<endl;
	}
	if(p<k)	return -1;
	sort(dis+1,dis+p+1,cmp);
	return dis[k];
}
void Find(int pre){
	int l=1,r=n,AnsL=INT_MAX;
	while(l<=r){
		int mid=(l+r)>>1,now=check(mid);
		if(now==-1)	r=mid-1;
		else if(now<pre)	l=mid+1;
		else if(now==pre)	AnsL=min(AnsL,mid),r=mid-1;
//		cout<<Ans<<" "<<AnsL<<endl;
	}
	cout<<pre<<" "<<AnsL<<endl;
} 
int main(){
	for(int i=2;i<=1e5;i++)	Log[i]=Log[i>>1]+1;
	int t;
	t=read();
	while(t--){
		n=read(),k=read();
		for(int i=1;i<=n;i++)	a[i]=read();
		init(); 
//		cout<<check(3)<<endl;
		Find(check(n-k+1));	
	}
	return 0;
}
```


---

## 作者：Targanzqq (赞：8)

## 思路：
**定理 1**：对于其中一个端点确定而另一个端点不确定时，这样的区间极差随区间长度增加单调不下降。

**证明：** 我们定义原极差为 $c_0$，区间新增的数为 $a$，原序列最大和最小值分别为 $maxn$ 和 $minn$，更改后的极差为 $c_1$，则 $c_1=\max(maxn,a)-\min(minn,a)$。显然这个式子的值总大于等于 $c_0$。

知道这个之后，我们就可以直接开始做了。

## 做法：
首先，维护区间极差相当于维护最大值和最小值，所以我们开 两个 st 表，分别维护区间最大和最小值。

首先依据定理 $1$，我们得出：区间长度最大时，$X$ 最大。所以我们需要先求出来这个最大的 $X$，然后通过二分 $L$ 长度求出最小的 $L$。

复杂度 $O(n \log n)$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,k,fin[100001][20],fax[100001][20];

int jc(int l,int r){
	int kk=log2(r-l+1);
	return max(fax[l][kk],fax[r+1-(1<<kk)][kk])-min(fin[l][kk],fin[r+1-(1<<kk)][kk]);
}

int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>fin[i][0];
			fax[i][0]=fin[i][0];
		}
		for(int i=1;i<=20;i++){
			for(int j=1;j<=n;j++){
				if(j+(1<<i)-1<=n){
				fax[j][i]=max(fax[j][i-1],fax[j+(1<<(i-1))][i-1]); 
				fin[j][i]=min(fin[j][i-1],fin[j+(1<<(i-1))][i-1]); 
			    }
			}
		}
		//cout<<"*"<<fax[2][2];
		int ans=2000000001;
		for(int i=1;i<=k;i++){
			ans=min(ans,jc(i,i+n-k));
			//cout<<jc(i,i+n-k)<<" ";
		}
		//cout<<endl;
		//cout<<"&"<<jc(1,3);
		//cout<<"*"<<ans;
		int l=1,r=n-k+1,L=n-k+1;
		while(1){
			if(l>r)break;
			int mid=(l+r)/2;
			int now=0;
			for(int i=1;i<=n-mid+1;i++){
				if(jc(i,i+mid-1)>=ans)now++;
			}
			if(now>=k){
				L=min(L,mid);
				r=mid-1;
			} 
			else{
				l=mid+1;
			}
		}
		cout<<ans<<" "<<L<<endl;
    }
}
```


---

## 作者：cosf (赞：5)

出题人在赛时想到线性做法了。

---

我们先求出 $X$ 的最大值。为了最大，我们先让所有区间尽量长，长度为 $n - k + 1$。用单调队列算出 $1$ 到 $k$  开始的区间的极差，取 $\min$ 即得 $X_{\max}$。

然后我们算出 $1$ 到 $n$ 开始的区间至少要多长才能使它的极差大于等于 $X_{\max}$。

然后我们依次枚举长度，判断一下有多少个区间满足极差 $\ge X_{\max}$ 即可。

注意，区间长度与区间极差 $\min$ 的函数图像不是单调的，需要拿个桶维护一下。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

#define MAXN 100006

using ll = long long;
using pli = pair<ll, int>;

namespace Choose
{
    int n, k;

    // Monotonous Queue
    pli q1[MAXN];
    int s1, e1; // min
    pli q2[MAXN];
    int s2, e2; // max

    ll v[MAXN];

    int st[MAXN];

    pli se[MAXN];

    int e[MAXN];

    int mian()
    {
        memset(e, 0, sizeof(e));
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
        {
            cin >> v[i];
        }
        s1 = s2 = 1;
        e1 = e2 = 0;
        // Calculate the max X
        // The length of section is n - k + 1
        int len = n - k + 1;
        for (int i = 1; i < len; i++)
        {
            while (s1 <= e1 && q1[e1].first >= v[i])
            {
                e1--;
            }
            q1[++e1] = {v[i], i};
            while (s2 <= e2 && q2[e2].first <= v[i])
            {
                e2--;
            }
            q2[++e2] = {v[i], i};
        }
        ll X = 0x3ffff3fff3fff3ff;
        for (int i = len; i <= n; i++)
        {
            while (s1 <= e1 && q1[e1].first >= v[i])
            {
                e1--;
            }
            q1[++e1] = {v[i], i};
            while (s1 <= e1 && q1[s1].second <= i - len)
            {
                s1++;
            }
            while (s2 <= e2 && q2[e2].first <= v[i])
            {
                e2--;
            }
            q2[++e2] = {v[i], i};
            while (s2 <= e2 && q2[s2].second <= i - len)
            {
                s2++;
            }
            X = min(X, q2[s2].first - q1[s1].first);
        }
        cout << X << ' ';
        // Find how long should a section be to have the max difference of X if it starts at i.
        s1 = s2 = 1;
        e1 = e2 = 0;
        memset(st, 0x3f, sizeof(st));
        st[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            while (s1 <= e1 && q1[e1].first >= v[i])
            {
                e1--;
            }
            q1[++e1] = {v[i], i};
            while (s1 <= e1 && q1[s1].second <= i - len)
            {
                s1++;
            }
            while (s2 <= e2 && q2[e2].first <= v[i])
            {
                e2--;
            }
            q2[++e2] = {v[i], i};
            while (s2 <= e2 && q2[s2].second <= i - len)
            {
                s2++;
            }
            int l = lower_bound(q1 + s1, q1 + e1 + 1, pli{v[i] - X, 0x3ffff3ff}) - q1 - 1;
            int r = lower_bound(q2 + s2, q2 + e2 + 1, pli{v[i] + X, 0}, greater<pli>()) - q2 - 1;
            int lef = 0;
            if (l >= s1)
            {
                lef = max(lef, q1[l].second);
            }
            if (r >= s2)
            {
                lef = max(lef, q2[r].second);
            }
            while (st[lef] > i)
            {
                st[lef] = i;
                lef--;
            }
        }
        // Then sort them from short to long
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            if (st[i] - i > -1)
            {
                se[++cnt] = {st[i] - i + 1, i};
            }
        }
        sort(se + 1, se + cnt + 1);
        // Calculate
        int sz = 0, en = n + 1;
        for (int i = 1; i <= cnt; i++)
        {
            sz++;
            e[se[i].second]++;
            for (int j = n + 2 - se[i].first; j < en; j++)
            {
                sz -= e[j];
            }
            en = min((ll)en, n + 2 - se[i].first);
            if (sz >= k)
            {
                cout << se[i].first << endl;
                break;
            }
        }
        return 0;
    }
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        Choose::mian();
    }
    return 0;
}
```


---

## 作者：BIG_CUTE_BUG (赞：3)

[题传](https://www.luogu.com.cn/problem/P10059)

## 思路

最小最大最大最小想到二分。

对某数列增加一个数 $a$，有两种情况：

1. $a$ 是新的极值，极差增大。

2. $a$ 不是新的极值，极差不变。

发现数列中的数越多，极差越大，也即 $L$ 增大 $X$ 单调不减。

所以先取 $L$ 最大值 $L=n-k+1$，把 $X$ 的最大值 $ans$ 算出，然后二分 $L$。

对于 $L_0$，记所有长为 $L_0$ 的区间中极差大于等于 $ans$ 的区间个数为 $cnt$，若 $cnt< k$ 则下收缩，若 $cnt\ge k$ 则上收缩。

## 代码

`check` 中用单调队列维护区间极值来求极差。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N= 1e5+ 5;
int t, n, a[N], k, len, up[N], lw[N], ans= 2e9+ 1;
int get(int x, int now)
{
	int hu= 1, tu= 0, hl= 1, tl= 0, cnt= 0;
	for(int i= 1; i< now; i++)
	{
		while(a[i]>= a[up[tu]] && hu<= tu) tu--; up[++tu]= i;
		while(a[i]<= a[lw[tl]] && hl<= tl) tl--; lw[++tl]= i;
	}
	for(int i= now; i<= n; i++)
	{
		while(a[i]>= a[up[tu]] && hu<= tu) tu--; up[++tu]= i;
		while(a[i]<= a[lw[tl]] && hl<= tl) tl--; lw[++tl]= i;
		if(up[hu]< i- now+ 1) hu++;
		if(lw[hl]< i- now+ 1) hl++;
		if(x== -1) ans= min(ans, a[up[hu]]- a[lw[hl]]);
		else if(a[up[hu]]- a[lw[hl]]>= ans) cnt++;
	}
	return cnt;
}
signed main()
{
	t= input();
	while(t--)
	{
		n= input(); k= input();
		int mx= -1e9, mn= 1e9; ans= 2e9+ 1;
		for(int i= 1; i<= n; i++) a[i]= input(), mx= max(mx, a[i]), mn= min(mn, a[i]);
		int l= 0, r= mx- mn; get(-1, n- k+ 1);
		l= 1, r= n- k+ 1;
		while(l<= r)
		{
			int mid= l+ r>> 1, cnt;
			if(get(ans, mid)>= k) len= mid, r= mid- 1;
			else l= mid+ 1;
		}
		print(ans, ' '), print(len);
	}
	IO:: flush();
	return 0;
}
```

---

## 作者：Double_Light (赞：3)

## P10059 Choose 题解

### 题意简化

给定一个序列 $a$，从其中找到 $k$ 个长度相同的连续子序列，使得它们的极差（最大值与最小值的差）最小的一个尽可能大。求出这个值，并且求出满足条件下的子序列长度的最小值。

### 题目分析

当看到“最小的一个尽可能大”的语句时，很容易联想到二分。

显然，$L$ 的值越大，极差肯定要比较小的 $L$ 要大或相等。那么，求出最大的极差，就只需要让 $L$ 达到最大（即 $n-k+1$，此时一共有 $k$ 个不同的区间），然后取最小的那一个。

对于第二问，考虑二分。前面已经说过，随着 $L$ 的增大，极差肯定是单调不降的，故满足了单调性。每次查询第 $k$ 大的极差，如果与已经算出来的第一问答案相等，则最终答案肯定小于等于当前的 $L$。否则，则将左端点设为 $L+1$。最终当左端点与右端点相等时，最终的答案就是此时的左端点（或右端点）。

每次二分的过程中，都需要查询最大值和最小值来计算极差。于是可以用 ST 表来维护最大值和最小值，降低时间复杂度。

最终代码如下（需加快读）：
### 参考代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
int n,k,t,a[100005],b[100005],maxn=-1e9,minn=1e9,f;
int st[100005][20],st2[100005][20];//st维护最大值，st2维护最小值
int lg[100005];
int query(int l,int r){//查询极差
	int p=lg[r-l+1];
	return max(st[l][p],st[r-(1<<p)+1][p])-min(st2[l][p],st2[r-(1<<p)+1][p]);
}
bool cmp(int p,int q){
	return p>q;
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
signed main(){
	cin>>t;
	lg[1]=0;
	for(int i=2;i<=100000;i++)lg[i]=lg[i>>1]+1;//预处理log
	while(t--){
		n=read();k=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			st[i][0]=st2[i][0]=a[i];
		}
		for(int i=1;(1<<i)<=n;i++){//预处理区间最值
			for(int j=1;j<=n-(1<<i)+1;j++){
				st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
				st2[j][i]=min(st2[j][i-1],st2[j+(1<<(i-1))][i-1]);
			}
		}
		for(int i=1;i<=k;i++)b[i]=query(i,n-k+i);//区间范围[i,n-k+i]
		sort(b+1,b+k+1,cmp);
		f=b[k];
		int l=1,r=n-k+1,mid;
		while(l<r){//l<=r会死循环
			mid=(l+r)/2;
			for(int i=1;i+mid-1<=n;i++)b[i]=query(i,i+mid-1);//区间范围[i,i+mid-1]
			sort(b+1,b+(n-mid+1)+1,cmp);//注意排序的范围
			if(b[k]==f)r=mid;
			else l=mid+1;
		}
		cout<<f<<' '<<r<<'\n';
	}
	return 0;
}
```

---

## 作者：羊羊君的幻想 (赞：3)

B 题比 D 题写的还久，就离谱。



------------


### 题意

在一个序列里选出 $k$ 个长度为 $L$ 且位置不同的区间，要求这 $k$ 个区间的极差的最小值最大，求出这个最大值 $x$，和最小的 $L$。


------------

### 题解

考虑一些特殊性质。

显然，$L$ 具备单调性。简单说来，就是如果 $L$ 可以取到最大值 $x$，那么大于 $L$ 的长度也可以了，当然，要保证可以取 $k$ 个。

证明很简单，如果更大的 $L$ 可以取足 $k$ 个，那么取到的区间中一定包含满足条件的小区间。

所以第一问我们令 $L=n-k+1$ 跑一遍即可。

第二问基于第一问，由于具备单调性，我们考虑二分答案，上界是 $n-k+1$，下界为 $1$，因为单调性已经证明了，所以套用二分模板即可。

具体使用 ST 表维护，我的赛时代码的时间复杂度为 $O(n\log^2n)$，跑得还挺快。


------------
### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
namespace IO{
	inline int read()
	{
		int x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
}
using namespace IO;
using namespace std;
const int N=1e5+10;
int n,k,x;
int lg[N];
int	maxn[N][26],minn[N][26];
int get(int l,int r){
	int mid=lg[r-l+1];
	int MAX=max(maxn[l][mid],maxn[r-(1<<mid)+1][mid]);
	int MIN=min(minn[l][mid],minn[r-(1<<mid)+1][mid]);
	return MAX-MIN;
}
int tmp[N],cnt;
void init(){
	cnt=0;
	memset(tmp,0,sizeof(tmp));
}
bool check(int p){
	init();
	for(int l=1;l<=n-p+1;l++){
		int r=l+p-1;
		tmp[++cnt]=get(l,r);
	}
	sort(tmp+1,tmp+1+cnt,greater<int>());
	return tmp[k]==x;
}
void work(){

	n=read();k=read();
	for(int i=1;i<=n;i++){
		maxn[i][0]=minn[i][0]=read();
	}
	for(int j=1;j<=22;j++){
		for(int i=1;(i+(1<<j))-1<=n;i++){
			maxn[i][j]=max(maxn[i][j-1],maxn[i+(1<<(j-1))][j-1]);
			minn[i][j]=min(minn[i][j-1],minn[i+(1<<(j-1))][j-1]);
		}
	}
	init();
	for(int l=1;l<=k;l++){
		int r=l+n-k;
		tmp[++cnt]=get(l,r);
	}
	sort(tmp+1,tmp+1+cnt,greater<int>());
	x=tmp[k];
	int l=1,r=n-k+1,ans=r;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)){
			r=mid;
			ans=mid;	
		}else l=mid+1;
	}
	cout<<x<<" "<<ans<<"\n";
}
signed main(){
	for(int i=2;i<N;i++){
		lg[i]=lg[i>>1]+1;
	}
	int t=read();
	while(t--){
		work();
	}



return 0;
}
```


---

## 作者：hgckythgcfhk (赞：2)

## subtask $1$

无论怎么选极差都是 $0$，直接输出 $0$ 即可。

## subtask $2$

有很多人得了 $5$ 分，就是这一步粗心了，由于要求极差最大的情况下长度最小，所以不一定是全选，而是以最大值和最小值为端点的一段就够了，想错主要是样例具有误导性。

## subtask $3$&$4$

这是最有用的一档部分分，我们发现，长度大到选不够 $k$ 个的显然不能选，贪心的想，一段中多选一个一定不劣，也就是说，尽可能的选最长的答案最优，但由上面一个部分分可知，长度不一定最优。

从 $n-k+1$ 开始枚举，枚举到第一个不合法的答案 $p$，直接输出 $p+1$。

计算答案的话就是把每一个合法的区间的极差都记下来，求第 $k$ 大，最大值减最小值就是极差。

## subtask $5$

对于上面的过程，我们要优化两个地方。

一个是枚举次数太多，发现答案关于长度单调不降，而这个问题相当于查询一个升序数组第一个为 $x$ 的数，可以二分，具体是叫二分查找还是二分答案我没系统的学过二分所以不是很清楚，但是不影响做题。

然后就是求 RMQ 问题，这档分就是给只会线段树的人设计的。

问：为什么线段树过不了全部数据？

答：本题有多测，全部数据相当于 $10^6$ 而不是 $10^5$。

说不定卡卡常也能过，因为即使不用线段树也必然是双 $\log$，就是常数的问题，但是我懒得卡了，就是用线段树写了一个对拍的暴力。

```cpp
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define void inline void
#define ll long long
using namespace std;constexpr unsigned N=1e5+1;
#define ll long long
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
class Tag{public:signed a,b,c,d;};
class Val{public:signed a,b,c,d;inline Val operator+(const Val e){return Val{a,e.b,max(c,e.c),min(d,e.d)};}};
ll a[N];
class segment_tree{private:Val t[N<<2];unsigned x,y;
	#define ls o<<1
	#define rs ls|1
	#define l t[o].a
	#define r t[o].b
	#define mx(o) t[o].c
	#define mn(o) t[o].d
	#define in x<=l&&y>=r
	#define out y<l||x>r
	void bd(cit o,cit L,cit R){if(L==R){t[o]=Val{L,L,a[L],a[L]};return;}cit m=L+R>>1;bd(ls,L,m);bd(rs,m+1,R);t[o]=t[ls]+t[rs];}
	inline Val qry(cit o){if(in)return t[o];if(out)return Val{0,0,INT_MIN,INT_MAX};return qry(ls)+qry(rs);}
public:
	void build(cit n){bd(1,1,n);}
	inline signed MAX(cit L,cit R){x=L,y=R;return qry(1).c;}
	inline signed MIN(cit L,cit R){x=L,y=R;return qry(1).d;}}t;
unsigned ans,n,k;
inline bool cmp(cit&x,cit&y){return x>y;}
inline unsigned calc(cit len){vector<unsigned>b;
	for(int i=1;i+len-1<=n;++i)b.emplace_back(t.MAX(i,i+len-1)-t.MIN(i,i+len-1));
	sort(b.begin(),b.end(),cmp);return b[k-1];}
inline bool chk(cit x){if(x+k-1>n)return 0;return calc(x)<ans;}
signed main(){open;int T;cin>>T;while(T--){cin>>n>>k;
	for(int i=0;i<n;cin>>a[++i]);t.build(n);ans=calc(n-k+1);cout<<ans<<' ';
	int p=0;for(int i=20;~i;--i)if(chk(p|(1<<i)))p|=(1<<i);cout<<p+1<<'\n';}}
```

## subtask $6$

把线段树换成 ST 表或者单调队列，也可以用 STL 的 nth_element 函数来求第 $k$ 大，这样说不定能过，但时间复杂度的瓶颈不在这里，而且在这个函数是通过分治实现的，所以常数很大，即使手写出来也不会很快，但说不定可以，我没试过。

下面给出 ST 表版本。

```
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define void inline void
#define ll long long
using namespace std;constexpr unsigned N=1e5+1;
#define ll long long
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
ll a[N];
class ST{private:ll mx[20][N],mn[20][N];public:
	void build(cit n){for(int i=1;i<=n;++i)mx[0][i]=mn[0][i]=a[i];
		for(int i=1;i<20;++i)for(int j=1;j+(1<<i)-1<=n;++j)
		mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<i-1)]),
		mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<i-1)]);}
	inline ll MAX(cit l,cit r){cit lg=__lg(r-l+1);return max(mx[lg][l],mx[lg][r-(1<<lg)+1]);}
	inline ll MIN(cit l,cit r){cit lg=__lg(r-l+1);return min(mn[lg][l],mn[lg][r-(1<<lg)+1]);}}t;
unsigned ans,n,k;
inline bool cmp(cit&x,cit&y){return x>y;}
inline unsigned calc(cit len){vector<unsigned>b;
	for(int i=1;i+len-1<=n;++i)b.emplace_back(t.MAX(i,i+len-1)-t.MIN(i,i+len-1));
	sort(b.begin(),b.end(),cmp);return b[k-1];}
inline bool chk(cit x){if(x+k-1>n)return 0;return calc(x)<ans;}
signed main(){open;int T;cin>>T;while(T--){cin>>n>>k;
	for(int i=0;i<n;cin>>a[++i]);t.build(n);ans=calc(n-k+1);cout<<ans<<' ';
	int p=0;for(int i=20;~i;--i)if(chk(p|(1<<i)))p|=(1<<i);cout<<p+1<<'\n';}}

```

加强版：卡空间，实测这个程序需要 30Mb，明显过不了，需要用单调队列，这个就留给大家自己写吧，反正只是打个模板的问题。

---

## 作者：LEE114514 (赞：2)

## 思路：ST 表 + 二分

先考虑第一问，要求取出 $k$ 个区间，使得极差最小值最大。我们发现，假设一个区间 $[l,r]$ 有极差 $x$，那么区间 $[l-1,r]$ 和 $[l,r+1]$ 的极差一定**不小于** $x$。因此，序列长度最大就是最优解。

简证：对于一个区间 $a$，它的极差 $x=a_{max}-a_{min}$，在区间向外扩大时，$a_{max}$ 单调不减，$a_{min}$ 单调不增，因此极差 $x$ 单调不减。

于是转化为：求长度为 $n-k+1$ 的 $k$ 个连续子序列的极差的最小值。

然后是第二问，在已知第一问的基础上，我们发现长度越大越容易满足条件。更进一步的，我们发现这一问的答案具有单调性，可以二分答案。

记第一问答案为 $ans_1$，则二分的条件可以为长度为 $x$ 的所有连续子序列中极差大于等于 $ans_1$ 的个数是否不小于 $k$。因为如果小于 $k$，我们无法构造出满足题意的情况，否则我们只需要任取满足条件的 $k$ 个。

具体实现中，我们可能需要频繁查询区间最值，于是想到可以维护一个 ST 表快速查询。

## Code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,k,T,ans1,ans2,a[maxn];
struct ST{
	int st[20][maxn];
	void build(){
		for(int i=1;i<=n;++i) st[0][i]=a[i];
		for(int j=1;j<20;++j)
		for(int i=1;i+(1<<(j))-1<=n;++i)
			st[j][i]=max(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	}
	int qry(int l,int r){
		int x=log2(r-l+1);
		return max(st[x][l],st[x][r-(1<<x)+1]);
	}
}MAX;
struct ST2{
	int st[20][maxn];
	void build(){
		for(int i=1;i<=n;++i) st[0][i]=a[i];
		for(int j=1;j<20;++j)
		for(int i=1;i+(1<<(j))-1<=n;++i)
			st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	}
	int qry(int l,int r){
		int x=log2(r-l+1);
		return min(st[x][l],st[x][r-(1<<x)+1]);
	}
}MIN;
bool check(int x){
	int res=0;
	for(int i=1;i<=n-x+1;++i)
		res+=(MAX.qry(i,i+x-1)-MIN.qry(i,i+x-1))>=ans1;
	return res>=k;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;++i) cin>>a[i];
		MAX.build();
		MIN.build();
		ans1=2e9+1,ans2=0;
		for(int i=1;i<=k;++i)
			ans1=min(ans1,MAX.qry(i,i+n-k)-MIN.qry(i,i+n-k));
		int L=1,R=n-k+1;
		while(L<=R){
			int mid=(L+R)>>1;
			if(check(mid)) R=mid-1;
			else L=mid+1;
		}
		ans2=L;
		cout<<ans1<<' '<<ans2<<'\n';
	}
}
```

---

## 作者：mayike (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/P10059)
~~就因为这题痛失 AK~~

**结论**：对于此题 $L$，我优先想到二分，因为 $L$ 越大，说明同一区域类 $L$ 长度得到的最大极差一定不小于 $L-1$ 长度得到的，既扩大区间极差只可能增大，而不会减小。因此当 $L=n-k+1$ 是一定可得 $\max(X)$，所以此时不必要二分。

因为题目里还有这样一句话：同时，你还需要求出，在足 $X$ 最大的情况下 $L$ 的最小值。这里，我就采用二分来求 $\min(L)$，因为长度越长时极差是按不递减增大的，所以可以二分。

对于求区间极差，因为长度固定，我用了单调队列做到 $O(n)$。

综合复杂度是 $O(Tn\log^2n)$。

亮出赛时代码，50 分，按注释改即可 AC。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int T, n, k, a[N], Max;
deque<int>q;
struct sb {
	int x, y, sum;
} p[N];
bool cmp(sb x, sb y) {
	return x.sum > y.sum;
}
int dsb(int m) {
	int cnt1 = 0, cnt2 = 0;
	if (!q.empty())q.pop_back();//这里错误，应写成
   //while(!q.empty())q.pop_back();
	for (int i = 1; i <= n; i++) {
		while (!q.empty() && i - m >= q.front())q.pop_front();
		while (!q.empty() && a[i] < a[q.back()])q.pop_back();
		q.push_back(i);
		if (i >= m)p[++cnt1].x = a[q.front()];
	}
	while (!q.empty())q.pop_back();
	for (int i = 1; i <= n; i++) {
		while (!q.empty() && i - m >= q.front())q.pop_front();
		while (!q.empty() && a[i] > a[q.back()])q.pop_back();
		q.push_back(i);
		if (i >= m)p[++cnt2].y = a[q.front()];
	}
	for (int i = 1; i <= cnt1; i++)p[i].sum = p[i].y - p[i].x;
	sort(p + 1, p + 1 + cnt1, cmp);
	return p[k].sum;
}
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++)cin >> a[i];
		int l = 1, r = n - k + 1, mid, ans, anst, Max;
		Max = dsb(n - k + 1);
		while (l <= r) {
			mid = (l + r) >> 1;
			ans = dsb(mid);
			if (ans == Max)anst = mid, r = mid - 1;
			else l = mid + 1;
		}
		cout << Max << ' ' << anst << '\n';
	}
	return 0;
}
```


---

## 作者：_radio_ (赞：1)

# p10059 Choose 题解 
## 思路
首先题目要求我们查询区间极差，想到使用 ST 表。

可以发现，区间越长，极差越大，理由：

设当前区间为 $[l,r]$，变为 $[l,r+1]$，则区间最大值只增不减，区间最小值只减不增，因此极差一定变大。

题目中要求选择 $k$ 个区间，如何证明在区间长度更短时第 $k$ 大的答案一定不会更大？

设当前区间长度为 $L$，变为 $L+1$，我们让新的每个区间都包含一个旧的区间。此时每个答案都只增不减，因此第 $k$ 大答案只增不减。

由于问题具有单调性，我们可以预处理出最长区间的答案，再通过二分查找可以保留这个答案的最短区间的长度。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,k,a[100010],st1[100010][20],st2[100010][20],L[100010],num[100010];
int check(int kuai){
	int cnt=0;
	for(int l=1;l<=n-kuai+1;l++){
		int r=l+kuai-1;
		num[++cnt]=max(st1[l][L[kuai]],st1[r-(1<<L[kuai])+1][L[kuai]])-min(st2[l][L[kuai]],st2[r-(1<<L[kuai])+1][L[kuai]]);
	}
	nth_element(num+1,num+cnt-k+1,num+cnt+1);
	return num[cnt-k+1];
}
signed main(){
	for(int i=2;i<=1e5;i++) L[i]=L[i>>1]+1;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			st1[i][0]=st2[i][0]=a[i];
		}
		for(int i=1;i<=17;i++)
			for(int j=1;j<=n-(1<<i)+1;j++){
				st1[j][i]=max(st1[j][i-1],st1[j+(1<<(i-1))][i-1]);
				st2[j][i]=min(st2[j][i-1],st2[j+(1<<(i-1))][i-1]);
			}
		int kuai=n-k+1,num=check(kuai);
		int l=1,r=kuai;
		while(l<r){
			int mid=(l+r)>>1;
			if(check(mid)==num) r=mid;
			else l=mid+1;
		}
		printf("%lld %lld\n",num,l);
	}
	return 0;
}
```


---

## 作者：ilibilib (赞：1)

## 题目分析：

我们不难发现，当选择序列越长，数越多，极差就越可能更大。

所以我们说 $X$ 随 $L$ 增大而增大。

其次，我们需要在满足 $X$ 最大时 $L$ 最小，

我们肯定需要先知道最大的 $X$ 后，才能确保自己选择 $L$ 可不可行。

根据单调性，我们求出 $L$ 最大时 $X$ 的值即 $X_{max}$，$L$ 最大即 $n-k+1$。

然后进行二分答案，检查不同 $L$ 下，能否选择出 $k$ 个连续子序列使 $X$ 不小于 $X_{max}$。

二分复杂度为 $O(\log X)$。

现在我们就需要一个复杂度差不多为 $O(n)$ 的算法检验 $L$ 的可行性。

为了求极差，我们就要求最大值和最小值。

我可以将数组离散化，然后用双指针选取长度为 $L$ 的序列，维护 

$cnt$ 数组记录每个数的出现次数，进而维护两个 `bitset` 的数组 

$mx$ 和 $mn$，可以用 `_Find_first` 函数求第一个出现的数即最值，

要求最大值则反向维护就行了。故需维护两个 `bitset` 数组。

## code：
```cpp
#include<bits/stdc++.h>
#define sc scanf
#define pt printf
#define gc getchar
#define pc putchar
#define N 114514
using namespace std;
template<typename T>
inline void read(T &x)
{
	int f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=gc();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-48,ch=gc();}
	x*=f;
}
template<typename T>
inline void write(T x)
{
	if(x<0) {x=-x;pc('-');}
	if(x>9) write(x/10);
	pc(x%10^48);
}
bitset<N>mx;bitset<N>mn;
int a[N+10],b[N+10],n,m,cnt[N+10];
inline void del(int i){if(!--cnt[a[i]]) mn.reset(a[i]),mx.reset(n-a[i]+1);}
inline void add(int i){if(!cnt[a[i]]++) mn.set(a[i]),mx.set(n-a[i]+1);}
bool check(int k,int x,int ok)
{
	mx.reset();mn.reset();
	int y=4e9,l=1,r=0,z=0;
	while(r<k) add(++r);
	y=b[n-mx._Find_first()+1]-b[mn._Find_first()];
	if(y>=x) ++z;
	while(r<n)
	{
		del(l++),add(++r);
		y=b[n-mx._Find_first()+1]-b[mn._Find_first()];
		if(y>=x) ++z;
	}
	while(l<=r) del(l++);//不要忘记清空cnt
	if(z>=ok) return true;
	return false;
}
int f(int k)
{
	mx.reset(),mn.reset();
	int y,l=1,r=0;
	while(r<k) add(++r);
	y=b[n-mx._Find_first()+1]-b[mn._Find_first()];
	while(r<n)
	{
		del(l++),add(++r);
		y=min(y,b[n-mx._Find_first()+1]-b[mn._Find_first()]);
	}
	while(l<=r) del(l++);
	return y;
}
int main()
{
	int T;
	read(T);
	while(T--)
	{
		int x,ans=0;
		read(n);read(m);
		for(int i=1;i<=n;++i) read(a[i]),b[i]=a[i];
		sort(b+1,b+n+1);
		for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+n+1,a[i])-b;
		if(b[n]==b[1]){write(0);pc(' ');write(1);pc('\n');continue;}//特判数据1
		x=f(n-m+1);
		int l=1,r=n-m+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(check(mid,x,m)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		write(x);pc(' ');write(ans);pc('\n');
	}
	return 0;
}
```



---

## 作者：xiaoliebao1115 (赞：1)

## 解题思路
###  $40$ 分思路
暴力枚举最大值最小值，硬性求解。
### 考虑优化
由最小值最大很容易想到是二分答案，在暴力枚举完 $n-k+1$ 长度时的极差后，使用二分求解，因为序列满足长度越大极差最小值越大。

但还是会超时。

小心有负数。
#### code 二分优化
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[100001],b[100001],n,k;
bool check(int len,int ans)
{
	int cnt=0;
	for(int i=1;i<=n;i++)
		{
			if(i+len-1<=n)
			{
				int j=i+len-1,minn=INT_MAX,maxn=-INT_MAX;
				for(int k=i;k<=j;k++)
				{
					if(a[k]>maxn) maxn=a[k];
					if(a[k]<minn) minn=a[k];
				} 
				if(maxn-minn>=ans) cnt++;
			}
		}
	if(cnt>=k) return 1;
	return 0;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i],b[i]=0;
		int len=n-k+1;
		int jicha=INT_MAX;
		for(int i=1;i<=n;i++)
		{
			if(i+len-1<=n)
			{
				int j=i+len-1,minn=INT_MAX,maxn=-INT_MAX;
				for(int k=i;k<=j;k++)
				{
					if(a[k]>maxn) maxn=a[k];
					if(a[k]<minn) minn=a[k];
				} 
				if(maxn-minn<jicha) jicha=maxn-minn;
			}
		}
		cout<<jicha<<" ";
		int l=1,r=n-k+1,ans=r;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid,jicha)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<ans<<endl;
	}
	return 0;
 } 
```
### 考虑单调队列
每次求解序列的极差相当于滑动窗口，就变成了单调队列模板。

储存最大最小值。
## 正解 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[100001],b[100001],n,k,p[100001],q[100001],xx[100001],mm[100001];
void work_min(int k) {
    int head = 1, tail = 0,cnt=0;
    for(int i = 1; i <= n; i++) {
        while(head <= tail && q[tail] >= a[i]) tail--;
        q[++tail] = a[i];
        p[tail] = i;
        while(p[head] <= i-k) head++;
        if(i >= k) cnt++,mm[cnt]=q[head];
    }
}
void work_max(int k) {
    int head = 1, tail = 0,cnt=0;
    for(int i = 1; i <= n; i++) {
        while(head <= tail && a[i] >= q[tail]) tail--;
        q[++tail] = a[i];
        p[tail] = i;
        while(p[head] <= i-k) head++;
        if(i >= k) cnt++,xx[cnt]=q[head];
    }
}
bool check(int len,int ans)
{
	work_min(len);
	work_max(len);
	int cnt=0;
	for(int i=1;i<=n;i++)
		{
			if(i+len-1<=n)
			{
				int maxn=xx[i];
				int minn=mm[i];
				if(maxn-minn>=ans) cnt++;
			}
		}
	if(cnt>=k) return 1;
	return 0;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i],b[i]=0;
		int len=n-k+1;
		int jicha=INT_MAX;
		work_min(n-k+1);
    	work_max(n-k+1);
		for(int i=1;i<=n;i++)
		{
			if(i+len-1<=n)
			{
				int maxn=xx[i];
				int minn=mm[i];
				if(maxn-minn<jicha) jicha=maxn-minn;
			}
		}
		cout<<jicha<<" ";
		int l=1,r=n-k+1,ans;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid,jicha)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<ans<<endl;
	}
	return 0;
 } //注意a[i]有负数
 //好坑！！！！！！ 
```

---

## 作者：Hopeful_Hunter (赞：1)

先读题，此题有一个明显的性质：

对于固定了左端点的区间，区间长度越大，极差也会越来越大。

此时先不考虑 $L$ 取什么值。

我们先考虑如何计算出固定了 $L$ 后，$X$ 的最大值，由于选择的 $l_i$ 都是不重复的，我们可以计算出 $\max_{j=i}^{j=i+ L-1} \{ a_j\} - \max_{j=i}^{j=i+ L-1} \{ a_j\}$，其中 $1 \le i \le n - L + 1$，我们贪心地考虑 $l_i$ 的选择，为了让 $X$ 尽可能大，那么我们尽量的选择极差较大的位置。

当 $L$ 取最大值时（区间越长时），显然 $X$ 的值最大。（先不关注 $L$ 最小）

令 $X$ 的最大取值为 $Max$。

那么求出 $X$ 的最大之后，现在问题就变成了给定最大极差要求求出合法的 $L$ 的最小值。

令 $f(i)$ 表示当题目中的 $L = i$ 时 $X$ 的最大值是否等于最优的 $Max$，那么显然 $f(i) = 1$ 时 $f(i + 1) = 1$，所以使用二分。

但时还不够，如果暴力求极差，时间复杂度：$O(n ^2\log_2 n)$。

极差的变化如同一个滑动窗口，所以使用单调队列优化，时间复杂度：$O(n \log_2 n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int T, n, k, a[N], s[N], head[2], tail[2], f[N][2];

int Calc(int len){
	int sum = 0, ans = INT_MAX;
	head[0] = head[1] = 1, tail[0] = tail[1] = 0;
	for(int i = 1; i < len; i++){
		for(; head[0] <= tail[0] && a[i] <= a[f[tail[0]][0]]; tail[0]--);
		for(; head[1] <= tail[1] && a[i] >= a[f[tail[1]][1]]; tail[1]--);
		f[++tail[0]][0] = i;
		f[++tail[1]][1] = i;
	}
	for(int i = len; i <= n; i++){
		for(; head[0] <= tail[0] && a[i] <= a[f[tail[0]][0]]; tail[0]--);
		for(; head[1] <= tail[1] && a[i] >= a[f[tail[1]][1]]; tail[1]--);
		f[++tail[0]][0] = i, f[++tail[1]][1] = i;
		for(; f[head[0]][0] <= i - len; head[0]++);
		for(; f[head[1]][1] <= i - len; head[1]++);
		s[++sum] = a[f[head[1]][1]] - a[f[head[0]][0]];
	}
	sort(s + 1, s + sum + 1);
	return s[sum - k + 1];
}

void Solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	int tmp = Calc(n - k + 1);
	int l = 1, r = n - k + 2;
	while(l < r){
		int mid = (l + r) >> 1;
		Calc(mid) == tmp ? r = mid : l = mid + 1;
	}
	cout << tmp << ' ' << l << '\n';
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	for(cin >> T; T--; Solve()){
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

## 分析

2024 第一场 AK 的比赛，祭。

我们首先很容易发现一点，当子段长度为 $L_0$ 时，必定不比长度小于 $L_0$ 时的最小极差小，因此如果我们想最大化这个最小极差 $X$，我们需要找到最大子段长度 $L_0$，由于有子段数量限制 $k$，因此 $L_0=n+1-k$。所以，取每一个长度为 $L_0$ 的子段的极差的最小值，就是我们要求的最大 $X$。实现的话，可以使用 $O(1)$ 查询的 ST 表。

下一步考虑如何求 $L$。由于求的是最小的 $L$，且没有什么好的线性求法（至少我没想到），所以应该是二分。二分（不加 check）的复杂度为 $O(\log n)$（最大的长度仅有 $L_0=n+1-k$），因此 $O(n)$ 的 check 是可以的。枚举所有长为 $L$ 的子段，判断是否有 $k$ 个子段的极差大于等于 $X$ 即可。

赛时代码比较乱，加点注释。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int lg[100010],st[100010][22],st2[100010][22],n,k,x;
int check(int len,int jc)
{
	int tp=0;
	for(int i=1;i+len-1<=n;i++)
	{
		if(max(st[i][lg[len]],st[i+len-1-(1<<lg[len])+1][lg[len]])-min(st2[i][lg[len]],st2[i+len-1-(1<<lg[len])+1][lg[len]])>=jc) tp++;
        	//ST表求出最大值减去最小值，tp是极差大于X的子段数量
	}
	if(tp>=k) return 1;
	return 0;
}
void solve()
{
	mp.clear();
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>st[i][0],st2[i][0]=st[i][0];
	for(int j=1;j<=21;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	for(int j=1;j<=21;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st2[i][j]=min(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
        //ST表预处理
	x=2e9;
	for(int i=1;i<=k;i++) x=min(x,max(st[i][lg[n-k+1]],st[i+n-k-(1<<lg[n-k+1])+1][lg[n-k+1]])-min(st2[i][lg[n-k+1]],st2[i+n-k-(1<<lg[n-k+1])+1][lg[n-k+1]]));
    	//X为每个长度为L0=n-k+1的子段的极差最小值
	cout<<x<<' ';
	int l=1,r=n+1-k,mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(check(mid,x))
		{
			r=mid;
		}
		else l=mid+1;
	}//二分
	cout<<l<<endl;
}
signed main()
{
	lg[1]=0;lg[2]=1;
	for(int i=3;i<=1e5;i++) lg[i]=lg[i/2]+1;
    	//ST表预处理
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}

---

## 作者：i_love_xqh (赞：0)

# 题目链接

[P10059 Choose](https://www.luogu.com.cn/problem/P10059)。

# 分析

## 题目大意

给出一个长度为 $n$ 的序列，定义一个子区间的极差为这个区间的最大值与最小值之差。

现给出 $k$，求最小的 $L$ 满足选出 $k$ 个不同的长度为 $L$ 的子区间，使选出子区间的极值中的最小值最大，$1\le L\le n-k+1$。

## 题目分析

由极差定义可知，对于一个子区间 $l\sim r$，固定 $l$，随着 $r$ 的扩大极值是肯定会单调不降的，因为新加入的元素要么比当前最大值大，要么比当前最小值小，或在两者之间，前两种情况都使极值增大，后者不变；反过来，固定 $r$，随着 $l$ 的缩小极值也是单调不降的。所以就可以先将极值的最大值给求出来，即当长度取最大，也就是 $n-k+1$ 时，此时选出来的 $k$ 个子区间的极值的最小值就是最大值。

然后考虑求出最小的 $L$。因为发现随着 $L$ 的增大极值单调不降，所以具有单调性，于是就想到二分求出 $L$。

对于二分到的一个 $L$，判断是否可行，只用看 $n-L+1$ 个不同的子区间的极值中，第 $k$ 大的那个是否为之前求出来的最大值，如果可行则将区间收缩，否则扩大。

因为此题是未加强版，所以我用了 $O(n\log^2n)$ 的做法，即把所有 $n-L+1$ 个极值排序，这样排序带个 $O(n\log n)$，二分又有 $O(\log n)$，但验证也可以用单调队列维护，实现总时间复杂度 $O(n\log n)$。

Code：
```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T,n,d,k,ans;
ll st[100010][20],ts[100010][20],mxk[100010];//这里获取区间最大值和最小值我用了st表，预处理有个O(nlogn)，当然也可以用单调队列
ll lg[100010];
bool check(ll l) {
    ll res=1e18,p=lg[l],cnt=0;
    for(ll i=1;i<=n-l+1;i++){
        ll j=i+l-1;
		mxk[++cnt]=max(st[i][p],st[j-(1<<p)+1][p])-min(ts[i][p],ts[j-(1<<p)+1][p]);//将结果存入
    }
	sort(mxk+1,mxk+cnt+1);//排序
    if(mxk[cnt-k+1]==ans)return true;
    return false;//验证第k大是否满足
}
int main() {
    lg[1]=0;
    for(ll i=2;i<=100000;i++)lg[i]=lg[i/2]+1;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		for(ll i=1;i<=n;i++)scanf("%lld",&st[i][0]),ts[i][0]=st[i][0];
		for(ll j=1;j<=lg[n];j++){
			for(ll i=1;i+(1<<j)-1<=n;i++){
				st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);//区间最大值
				ts[i][j]=min(ts[i][j-1],ts[i+(1<<j-1)][j-1]);//区间最小值
			}
		}
		ans=1e18;
		ll p=lg[n-k+1];
		for(ll i=1;i<=k;i++){
			ll j=n-k+i;
			ans=min(ans,max(st[i][p],st[j-(1<<p)+1][p])-min(ts[i][p],ts[j-(1<<p)+1][p]));//先求出极值最大值
		}
        ll l=1,r=n-k+1;
        while(l<r){
            ll mid=(l+r)/2;
            if(check(mid))r=mid;
            else l=mid+1;
        }//二分答案
        printf("%lld %lld\n",ans,l);
	}
    return 0;
}
```

---

## 作者：we_are_the_chuibing (赞：0)

### 思路

要求“最小的一个尽可能大”，直接想到二分。

显然，$L$ 的值越大，极差肯定要比较小的 $L$ 要大或相等。那么，求出最大的极差，就只需要让 $L$ 达到最大（即 $n - k + 1$，此时一共有 $k$ 个不同的区间），取最小的那一个。

对于第二问，考虑二分。前面已经说过，随着 $L$ 的增大，极差肯定是单调不降的，故满足了单调性。每次查询第 $k$ 大的极差，如果与已经算出来的第一问答案相等，则最终答案肯定小于等于当前的 $L$。否则，则将左端点设为 $L + 1$。最终当左端点与右端点相等时，最终的答案就是此时的左端点（或右端点）。

每次二分的过程中，都需要查询最大值和最小值来计算极差。于是可以用ST表来维护最大值和最小值，降低时间复杂度。

不加快读会T。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define guan_li_yuan_da_da_qiu_guo return 0;
using namespace std;
ll n,k,t,a[100005],b[100005],maxn=-1145141919,minn=1145141919,f,st[100005][20],st2[100005][20],lg[100005];
ll sc(ll l,ll r){
	ll p=lg[r-l+1];
	return max(st[l][p],st[r-(1<<p)+1][p])-min(st2[l][p],st2[r-(1<<p)+1][p]);
}
bool cmp(ll p,ll q){return p>q;}
ll read(){
	ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;
}
int main(){
	cin>>t;
	lg[1]=0;
	for(ll i=2;i<=100000;i++)lg[i]=lg[i>>1]+1;
	while(t--){
		n=read();k=read();
		for(ll i=1;i<=n;i++){
			a[i]=read();
			st[i][0]=st2[i][0]=a[i];
		}
		for(ll i=1;(1<<i)<=n;i++){
			for(ll j=1;j<=n-(1<<i)+1;j++){
				st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
				st2[j][i]=min(st2[j][i-1],st2[j+(1<<(i-1))][i-1]);
			}
		}
		for(ll i=1;i<=k;i++)b[i]=sc(i,n-k+i);
		sort(b+1,b+k+1,cmp);
		f=b[k];
		ll l=1,r=n-k+1,mid;
		while(l<r){
			mid=(l+r)/2;
			for(ll i=1;i+mid-1<=n;i++)b[i]=sc(i,i+mid-1);
			sort(b+1,b+(n-mid+1)+1,cmp);
			if(b[k]==f)r=mid;
			else l=mid+1;
		}
		cout<<f<<' '<<r<<endl;
	}
	guan_li_yuan_da_da_qiu_guo
}
```


---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/P10059)
### 题解
首先，能得到一个结论，那就是 $L$ 越大，满足极差大于某一个数的连续子序列数量越多。

那么我们考虑二分套二分，第一个二分的值域是最小极差，第二个二分的值域是 $L$。然后发现求最值可以用 ST 表来维护。

check 中用满足条件的数量（长度为 $L$ 且极差大于 check 的连续子序列数）是否大于等于 $k$ 即可。

但是这是不行的，$O(n \log^2 n)$ 稳稳地超时，考虑优化。

回顾题解开头的结论，如果一个极差存在方案，那么这个极差在子序列长度为 $n - k+1$（即 $L_{max}$） 时 check 的结果必然是 true，于是我们得出了优化方案：

- check 时直接考虑长度为 $n-k+1$ 的连续子序列中极差大于要检查的数的数量是否大于 $k$。 

好像就 ST 表超纲了（
### 代码
```
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 100010,MAX_LOG = 20;
int n,k;
int a[N];
int f[N][MAX_LOG],g[N][MAX_LOG],lg[N];
int query_max (int l,int r) {
	int k = lg[r - l + 1];
	return max (f[l][k],f[r - (1 << k) + 1][k]);
}
int query_min (int l,int r) {
	int k = lg[r - l + 1];
	return min (g[l][k],g[r - (1 << k) + 1][k]);
}
int get (int len,int res) {
	int ans = 0;
	for (int i = 1;i <= n - len + 1;i++) ans += query_max (i,i + len - 1) - query_min (i,i + len - 1) >= res;
	return ans;
}
int get_ans (int res) {
	int l = 1,r = n - k + 1;
	while (l < r) {
		int mid = l + r >> 1;
		if (get (mid,res) >= k) r = mid;
		else l = mid + 1;
	}
	if (get (l,res) >= k) return l;
	return -1;
}
int main () {
	lg[1] = 0,lg[2] = 1;
	for (int i = 3;i < N;i++) lg[i] = lg[i / 2] + 1;
	int T;
	scanf ("%d",&T);
	while (T--) {
		scanf ("%d%d",&n,&k);
		set <int> s;
		for (int i = 1;i <= n;i++) scanf ("%d",&a[i]),f[i][0] = g[i][0] = a[i],s.insert (a[i]);
		for (int j = 1;j < MAX_LOG;j++) {
			for (int i = 1;i + (1 << j - 1) <= n;i++) {
				f[i][j] = max (f[i][j - 1],f[i + (1 << j - 1)][j - 1]);
				g[i][j] = min (g[i][j - 1],g[i + (1 << j - 1)][j - 1]);
			}
		}
		if (s.size () == 1) {
			puts ("0 1");
			continue;
		}
		if (k == 1) {
			int tmp = query_max (1,n) - query_min (1,n);
			cout << tmp << ' ' << get_ans (tmp) << endl;
			continue;
		}
		int l = 0,r = 2e9;
		while (l < r) {
			int mid = (LL)l + r + 1 >> 1;
			if (get (n - k + 1,mid) >= k) l = mid;
			else r = mid - 1;
		}
		printf ("%d %d\n",l,get_ans (l));
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

场切本题，AK 基础赛，必须写个题解纪念一下。

#### 题目大意

在数组 $a$ 中选出 $k$ 个长度为 $L$ 的**连续**子序列，最大化这些子序列的极差的最小值，并且求出最小的 $L$。

首先对于每个 $L$，他极差的最小值肯定是单调递增的。假定两个序列，他们是包含关系，更长的序列的极差肯定不会小于短的序列。所以考虑二分。


接下来就是求出极差了。由于 $L$ 一直在变化，所以我们需要选择单调队列来维护区间最大值和最小值，然后相减，就求出了每个序列的极差。

为了使极差最小值尽可能大，我们也需要选极差尽可能大的子序列，也就是将所有序列的极差排序，选择最大的 $k$ 个。当然，我们只要这 $k$ 个的最小值，也就是第 $k$ 大的数，所以可以使用 ```nth_element``` 来解决，但是我用了会寄，只能用排序了。复杂度 $O(n\log^2 n)$，对于 $\sum n$ 最大有 $10^6$ 的数据来说，应该算[勉强卡过](https://www.luogu.com.cn/record/142847094)。

我们前面说过序列是单调递增的，所以最右边的是最大值，二分时可以判断当前的极差是否是最大值，不是就排除掉这个区间。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[100005],b[100005],m[100005];
vector<int>v;
int check(int L)
{
  int l=1,r=0,len=0;
  for(int i=1;i<=n;i++)
  {
  	while(l<=r&&a[m[r]]<=a[i]) r--;
  	m[++r]=i;
  	if(i-m[l]>=L) l++;
  	if(i>=L) v.push_back(a[m[l]]);
  }
  l=1,r=0;
  for(int i=1;i<=n;i++)
  {
  	while(l<=r&&a[m[r]]>=a[i]) r--;
  	m[++r]=i;
  	if(i-m[l]>=L) l++;
  	if(i>=L) b[++len]=v[i-L]-a[m[l]];
  }//单调队列求极差，b表示极差
  sort(b+1,b+len+1);
  int res=b[len-k+1];
  v.clear();
  memset(b,0,sizeof(b));//多测不清空，爆零两行泪
  return res;
}
int main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
  	cin>>n>>k;
  	for(int i=1;i<=n;i++) cin>>a[i];
  	int l=1,r=n-k+1,mid,ans=check(n-k+1);//ans表示最大值
  	while(l<r)
  	{
  	  mid=l+r>>1;
  	  int now=check(mid);
  	  if(now<ans) l=mid+1;//不是最大值，跳过
  	  else r=mid;
	}
	cout<<ans<<" "<<r<<"\n";
  }
  return 0;
}
```

---

