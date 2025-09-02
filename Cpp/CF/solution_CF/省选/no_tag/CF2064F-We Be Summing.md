# We Be Summing

## 题目描述

给定一个长度为 $n$ 的数组 $a$ 和一个整数 $k$。

称一个非空且长度为 $m$ 的数组 $b$ 为史诗子数组（epic subarray），当且仅当存在一个整数 $i$ 满足 $1 \le i < m$ 且 $\min(b_1,\ldots,b_i) + \max(b_{i + 1},\ldots,b_m) = k$。

请计算数组 $a$ 中史诗子数组 $^{\text{∗}}$ 的数量。

 $^{\text{∗}}$ 若数组 $a$ 可以通过从数组 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到，则称 $a$ 是 $b$ 的子数组（subarray）。

## 说明/提示

第一个测试用例中所有史诗子数组如下：
- $[2, 3, 4, 5]$，因为 $\min(2, 3) + \max(4, 5) = 2 + 5 = 7$。
- $[3, 4]$，因为 $\min(3) + \max(4) = 3 + 4 = 7$。

第二个测试用例中，所有包含至少一个 $6$ 和至少一个 $7$ 的子数组均为史诗子数组。

## 样例 #1

### 输入

```
6
5 7
1 2 3 4 5
7 13
6 6 6 6 7 7 7
6 9
4 5 6 6 5 1
5 9
5 5 4 5 5
5 6
3 3 3 3 3
6 8
4 5 4 5 4 5```

### 输出

```
2
12
3
8
10
4```

# 题解

## 作者：w9095 (赞：6)

[CF2064F We Be Summing](https://www.luogu.com.cn/problem/CF2064F)

计数问题通常需要对计数对象找到一个独一无二的特征进行计数，否则只能进行容斥。注意到一个子区间中 $i$ 从左到右的过程中，前一部分 $\min$ 单降，后一部分 $\max$ 也单降，所以一个区间对应的前一部分 $\min$ 和后一部分 $\max$ 组成的有序数对 $(x,y)$ 是唯一的，于是我们对 $(x,y)$ 进行计数。

显然 $x+y=k$，考虑枚举 $x$，对这种情况下的子区间进行计数。

和 $\min,\max$ 有关的问题通常考虑每个位置的数的贡献区间，以 $\min$ 为例，位置 $a_i$ 能作为 $\min$ 贡献的区间就是左右第一个比 $a_i$ 小的数之间的区间。设 $a_i$ 的贡献区间为 $[l_i,r_i]$，则所有满足 $l_i\le l\le i\le r\le r_i$ 的区间 $[l,r]$ 区间 $\min$ 均为 $a_i$。我们可以利用单调栈求出每个位置的贡献区间。

考虑如何进行计数。假设现在正在计数的数对为 $(x,y)$，首先把序列中所有等于 $x,y$ 的数都找出来。设第 $a$ 个等于 $x$ 的位置为 $x_a$，第 $b$ 个等于 $y$ 的位置为 $y_b$，则产生贡献首先要满足 $x_a\lt y_b$。其次，考虑 $x_a$ 的 $\min$ 贡献区间和 $y_b$ 的 $\max$ 贡献区间的关系。如果 $r_{x_a}\ge l_{y_b}-1$，则所有满足 $l_{x_a}\le l\le x_a$ 且 $y_b\le r\le r_{y_b}$ 的区间 $[l,r]$ 都可以在 $i=l_{y_b}-1$ 处取到有序数对 $(x,y)$。否则如果 $r_{x_a}\lt l_{y_b}-1$，则不存在 $i$ 可以得到出 $(x,y)$。对于第一个限制，我们可以双指针维护插入时机满足。对于第二个限制，是一个二维偏序问题，使用树状数组维护。

还有一个问题就是我们的计数需要不重不漏。也就是说，以最大值为例，考虑上述流程中每次 $l$ 的取值，对于每一个出现了 $m$ 次的数 $a$，有 $\bigcup\limits_{i=1}^m[l_{a_i},a_i]=[1,n]$ 且 $\forall x,y\in[1,m]$，有 $[l_{a_x},a_x]\cap[l_{a_y},a_y]=\varnothing$。这是好处理的，我们只需要在计算 $l$ 的时候改为找左边第一个小于等于这个元素的数即可。同理，考虑最小值，对 $r$ 也有这个限制。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,k,a[500000],c[500000],l1[500000],r1[500000],l2[500000],r2[500000],st[500000],top=0;
vector<long long>p[500000];
long long lowbit(long long x)
{
	return x&(-x);
}

void add(long long x,long long k)
{
	while(x<=n)c[x]+=k,x+=lowbit(x);
}

long long getsum(long long x)
{
	long long ans=0;
	while(x>0)ans+=c[x],x-=lowbit(x);
	return ans;
}

int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld%lld",&n,&k);
	   	for(int i=1;i<=k;i++)p[i].clear(),c[i]=0;
	   	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),p[a[i]].push_back(i);
	   	for(int i=1;i<=n;i++)
	   	    {
	   	    while(top>0&&a[i]<a[st[top]])top--;
	   	    l1[i]=st[top]+1,st[++top]=i;
			}
		top=0;
		for(int i=1;i<=n;i++)
	   	    {
	   	    while(top>0&&a[i]<a[st[top]])r1[st[top]]=i-1,top--;
	   	    st[++top]=i;
			}
		while(top>0)r1[st[top]]=n,top--;
		for(int i=1;i<=n;i++)
	   	    {
	   	    while(top>0&&a[i]>=a[st[top]])top--;
	   	    l2[i]=st[top]+1,st[++top]=i;
			}
		top=0;
		for(int i=1;i<=n;i++)
	   	    {
	   	    while(top>0&&a[i]>=a[st[top]])r2[st[top]]=i-1,top--;
	   	    st[++top]=i;
			}
		while(top>0)r2[st[top]]=n,top--;
		long long ans=0;
		for(int i=k-n;i<k;i++)
		    {
		    	long long j=k-i,r=0;
		    	if(p[i].size()==0||p[j].size()==0)continue;
		    	for(int l=0;l<(int)p[i].size();l++)
		    	    {
		    	    	while(p[j][r]<p[i][l]&&r<(int)p[j].size())add(r1[p[j][r]],p[j][r]-l1[p[j][r]]+1),r++;
		    	    	ans+=(r2[p[i][l]]-p[i][l]+1)*(getsum(n)-getsum(l2[p[i][l]]-2));
					}
				r--;
				while(r>=0)add(r1[p[j][r]],l1[p[j][r]]-p[j][r]-1),r--;
			}
		printf("%lld\n",ans);
	   }
	return 0;
}
```

---

## 作者：SICKO (赞：5)

## 前言

看完[日麻新生はるか](https://space.bilibili.com/3546700731910221)的[光速AK](https://www.bilibili.com/video/BV17jwSeAEiE/?spm_id_from=333.1391.0.0&vd_source=0501e6cd609de41b6038e410d710ffa5)，我大为震撼，于是写一篇题解加深对这题的印象。

## 正文

首先我们分析一下题目，题目要我们找序列 $a$ 长度为 $m$ 的子串 $b$，要求字串具有性质：

$$\min(b_1, b_2, \dots, b_i) + \max(b_{i+1}, b_{i+2}, \dots, b_m) = k$$

我们很快发现，对于一个任意的子串 $b$，随着 $i$ 的增大，前面前缀求取最小值的部分单调不增，后面后缀求取最大值的部分也是单调不增，所以 $b$ 的合法切分一定是 $b$ 上连续的一段。

我们考虑一个数什么时候能成为最大值或者最小值，也就是一个数在什么时候会对和产生贡献。这个贡献一定是一个区间，也就是说，在这个区间内，这个数一定是最大/最小的。如果一个数最小值的贡献区间与另一个数的最大贡献区间有重合，那么重合部分就是合法的切分。

![](https://cdn.luogu.com.cn/upload/image_hosting/o61v1l3y.png)

上述部分需要我们快速处理出贡献位置，这部分可以用单调栈 $O(n)$ 处理。接下来就只剩下如何快速计算合法方案的数量了。我们分析一下上面的图片，我们只需要选上了 $a_1$ 与 $a_2$ 及其内的子串，那么就一定是合法的，所以答案就是 $a_1$ 合法贡献区间左边的元素数量乘以 $a_2$ 合法贡献区间右边的元素。这个过程可以用树状数组加速。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+6;
int n, k;
int a[N];
int l1[N], l2[N], r1[N], r2[N];
int stk[N], tp;
vector<int> vec[N];
int cnt[N];
void solve() {
    int res = 0;
    cin>>n>>k;
    for(int i=1; i<=n; i++) cin>>a[i];
    stk[tp=0] = 0;
    for(int i=1; i<=n; i++) {
        while(tp && a[stk[tp]] > a[i]) --tp;
        l1[i] = stk[tp] + 1;
        stk[++tp] = i;
    }
    stk[tp=0] = 0;
    for(int i=1; i<=n; i++) {
        while(tp && a[stk[tp]] <= a[i]) --tp;
        l2[i] = stk[tp] + 1;
        stk[++tp] = i;
    }
    stk[tp=0] = n+1;
    for(int i=n; i; i--) {
        while(tp && a[stk[tp]] >= a[i]) --tp;
        r1[i] = stk[tp] - 1;
        stk[++tp] = i;
    }
    stk[tp=0] = n+1;
    for(int i=n; i; i--) {
        while(tp && a[stk[tp]] < a[i]) --tp;
        r2[i] = stk[tp] - 1;
        stk[++tp] = i;
    }
    for(int i=1; i<=n; i++) vec[a[i]].push_back(i);
    for(int l = k-n, r=n; l<=n; ++l, --r) {
        auto A = vec[l], B = vec[r];
        while(!A.empty()) {
            while(!B.empty() && B.back() > A.back()) {
                int val = r2[B.back()]-B.back()+1;
                for(int i = l2[B.back()];i<=n;i+=i&-i) cnt[i] += val;
                B.pop_back();
            }
            int x = A.back(); A.pop_back();
            int v = 0;
            for(int i=min(r1[x]+1, n); i; i-=i&-i) v += cnt[i];
            res += v*(x-l1[x]+1);
        }
        int m = (int)B.size(); B = vec[r];
        while(B.size() > m) {
            for(int i = l2[B.back()];i<=n;i+=i&-i) cnt[i] = 0;
            B.pop_back();
        }
    }
    for(int i=1; i<=n; i++) vec[i].clear();
    cout<<res<<"\n";
}

signed main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    int T = 1;
    cin>>T;
    for(int i=1; i<=T; i++) solve();
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

## 思路

其实可以直接线性。

同样考虑枚举 $x,y$ 表示最小值和最大值，要求 $x+y=k$。

不难发现不同的 $(x,y)$ 不会计算到同一种方案。

然后考虑枚举具体位置，也就是枚举 $i,j$ 满足 $a_i=x,a_j=y$。

设 $l1_i/r1_i$ 表示 $i$ 左/右边第一个比 $i$ 小的数，$l0_i/r0_i$ 是 $i$ 左/右边第一个比 $i$ 大的数。

那么只需满足 $j>i$ 且 $l0_j<r1_i$ 就会产生贡献，这个贡献是让左端点在 $(l1_i,i]$ 右端点在 $[j,r0_j)$ 的区间变得合法。

进一步地，对于一个固定的 $i$，会产生贡献的 $j$ 是一个区间，容易用双指针维护。

同时根据区间的优秀性质（区间 $(l1_i,r1_i)$ 要么不交，要么包含，区间 $(l0_i,r0_i)$ 也一样），我们可以用一些简单的方法快速维护新增区间个数（例如前缀和）。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) (x).begin(),(x).end()
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
int const N=2e5+10;
int n,m,a[N],qz[N],Qz[N],l0[N],r0[N],l1[N],r1[N];
vector<int>vec[N];
inline void solve(){
	cin>>n>>m;rep(i,1,n) vec[i].clear();
	rep(i,1,n) cin>>a[i],r0[i]=r1[i]=n+1,l0[i]=l1[i]=0,vec[a[i]].push_back(i);
	{
		stack<int>S;
		rep(i,1,n){
			while (!S.empty() && a[i]>a[S.top()]) r0[S.top()]=i,S.pop();
			S.push(i);
		}
	}
	{
		stack<int>S;
		per(i,n,1){
			while (!S.empty() && a[i]>a[S.top()]) l0[S.top()]=i,S.pop();
			S.push(i);
		}
	}
	{
		stack<int>S;
		rep(i,1,n){
			while (!S.empty() && a[i]<a[S.top()]) r1[S.top()]=i,S.pop();
			S.push(i);
		}
	}
	{
		stack<int>S;
		per(i,n,1){
			while (!S.empty() && a[i]<a[S.top()]) l1[S.top()]=i,S.pop();
			S.push(i);
		}
	}
	int ans=0;
	rep(i,1,n){
		if (i>=m || m-i>n) continue;
		int j0=0,j1=0,las=0,sg=0;
		rep(j,0,(int)vec[m-i].size()-2) sg+=max(vec[m-i][j+1],r0[vec[m-i][j]]),qz[j]=sg;
		sg=0;
		rep(j,0,(int)vec[m-i].size()-1) sg+=r0[vec[m-i][j]],Qz[j]=sg;
		for (auto x:vec[i]){
			while (j0<(int)vec[m-i].size() && vec[m-i][j0]<=x) ++j0;
			while (j1<(int)vec[m-i].size() && l0[vec[m-i][j1]]<r1[x]) ++j1;
			if (j0>=j1) continue;
			las=max(las,l1[x]+1);
			int sm=-vec[m-i][j0]-qz[j1-2]+Qz[j1-1];
			if (j0) sm+=qz[j0-1]-Qz[j0-1];
			ans+=(x-las+1)*sm,las=x+1;
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

自然的想法是枚举左侧 $\min$ 为 $x$，然后对包含 $(x,k-x)$ 的合法区间计数。这看起来会算重，但手玩一下就会发现每个区间都只会有唯一的 $(x,k-x)$。

接下来考虑计数，预处理 $L_{i,0/1},R_{i,0/1}$ 分别表示左侧第一个不大于 $i$ 的位置、左侧第一个大于 $i$ 的位置、右侧第一个小于 $i$ 的位置和右侧第一个不小于 $i$ 的位置。如果一对 $(x,k-x)$ 位置分别在 $i,j$，那么若 $L_{j,1}<R_{i,0}$，这对数字就可以产生 $(R_{j,1}-j)\times(i-L_{i,0})$ 的贡献。双指针扫一遍即可简单计算。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18;
bool M1;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N=4e5+5;
int n,k,a[N];
int L[N][2],R[N][2];
void init(){
	stack<int>st;
	for(int i=1;i<=n;i++){
		while(!st.empty()&&a[st.top()]>a[i])st.pop();
		if(!st.empty())L[i][0]=st.top()+1;
		else L[i][0]=1;
		st.push(i);
	}
	while(!st.empty())st.pop();
	for(int i=1;i<=n;i++){
		while(!st.empty()&&a[st.top()]<=a[i])st.pop();
		if(!st.empty())L[i][1]=st.top();
		else L[i][1]=1;
		st.push(i);
	}
	while(!st.empty())st.pop();
	for(int i=n;i>=1;i--){
		while(!st.empty()&&a[st.top()]>=a[i])st.pop();
		if(!st.empty())R[i][0]=st.top();
		else R[i][0]=n;
		st.push(i); 
	}
	while(!st.empty())st.pop();
	for(int i=n;i>=1;i--){
		while(!st.empty()&&a[st.top()]<a[i])st.pop();
		if(!st.empty())R[i][1]=st.top()-1;
		else R[i][1]=n;
		st.push(i);
	}
}
vector<int>g[N];
int c[N];
void add(int x,int w){
	for(x;x<=n;x+=(x&-x))c[x]+=w;
}
int ask(int x){
	int aaa=0;for(x;x>0;x-=(x&-x))aaa+=c[x];
	return aaa;
}
void solve(){
	n=read();k=read();
	for(int i=1;i<=k;i++)g[i].clear();
	for(int i=1;i<=n;i++)a[i]=read(),g[a[i]].push_back(i);
	init();int ans=0;
	//for(int i=1;i<=n;i++)cerr<<L[i][0]<<" "<<R[i][0]<<" "<<L[i][1]<<" "<<R[i][1]<<'\n';
	for(int x=1;x<k;x++){int y=k-x;
		int l=g[y].size()-1;
		for(int j=g[x].size()-1;j>=0;j--){
			int pos=g[x][j];
			while(l>=0&&g[y][l]>pos){
				int pos2=g[y][l];
				add(L[pos2][1],R[pos2][1]-pos2+1);
				l--;
			}
			ans+=(pos-L[pos][0]+1)*ask(R[pos][0]-1);
			//cerr<<x<<" "<<pos<<" "<<L[pos][0]<<" "<<R[pos][0]<<" "<<ask(R[pos][0]-1)<<'\n';
		}
		for(int i=l+1;i<g[y].size();i++){
			int pos2=g[y][i];
			add(L[pos2][1],-(R[pos2][1]-pos2+1));
		}
	}
	cout<<ans<<'\n';
}
bool M2;
signed main(){
    //freopen("data.in","r",stdin);
    int T;T=read();while(T--)solve();
    cerr<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC<<"s"<<endl;
    cerr<<"Memory:"<<(&M1-&M2)/1024/1024<<"MB"<<endl;
    return 0;
}

```

---

## 作者：yvbf (赞：0)

https://www.bilibili.com/video/BV19cAaeVEme?p=2

(视频讲解，由于目前 luogu 内嵌 b 站视频分 p 的参数不生效，所以直接贴链接)

---

## 作者：Judgelight (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF2064F)

---

这种题不太需要考虑去重的问题，如果能把所有合法的区间都表示为矩阵，那么就变成了矩阵加、数有多少个点大于 $0$，可以排序扫描线，用树状数组维护。

那么我们考虑如何把所有合法区间都表示为矩阵加的形式。首先我们可以去找每个子序列 $b[l,r]$ 的左右两个端点 $i,j$ 满足 $\min(a_l\sim a_i)+\max(a_{i+1}\sim a_r)=k,\min(a_l\sim a_{i-1})+\max(a_i\sim a_r)\neq k,\min(a_l\sim a_{j-1})+\max(a_j\sim a_r)=k,\min(a_l\sim a_j)+\max(a_{j+1}\sim a_r)\neq k$，然后我们可以去找到所有的 $[l,i]$，对于它们去找一个区间 $[l',r']$ 满足 $\forall t\in[l',r'],\min(a_l\sim a_i)+\max(a_{i+1}\sim a_t)=k$，那么矩阵 $[l,i][l',r']$ 就刻画了一堆合法的 $b$，关于 $j$ 的刻画是同理的。关于这个的实现，首先找 $[l,i]$ 我们可以按照 $a$ 从大到小加入所有位置，不妨设当前的值为 $x$，则我们找到每个 $x$ 结尾的最长区间使得这个区间的所有元素都 $\ge x$，就找到所有 $[l,i]$ 了。然后 $[l',r']$ 可以二分找，check 只需要一个静态的区间最值，用 st 表即可。总时间为 $O(n\log n)$。

---

