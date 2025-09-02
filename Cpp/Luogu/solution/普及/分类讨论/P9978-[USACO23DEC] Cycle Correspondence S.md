# [USACO23DEC] Cycle Correspondence S

## 题目描述

Farmer John 有 $N$（$3 \le N \le 5\cdot 10^5$）座谷仓，其中 $K$ 对不同的谷仓连接在一起。

一开始，Annabelle 为每座谷仓分配了一个 $[1,N]$ 范围内的整数编号，并发现编号为 $a_1,\dots,a_K$ 的谷仓按照顺序形成了一个环形连接。换句话说，对于所有的 $1 \le i < K$，谷仓 $a_i$ 和 $a_{i+1}$ 相连，谷仓 $a_K$ 与 $a_1$ 亦相连。所有的 $a_i$ 不相同。

然后，Bessie 也为每个谷仓分配了一个 $[1,N]$ 范围内的整数编号，并发现编号为 $b_1,\dots,b_K$ 也按照顺序形成了一个环形链接。所有的 $b_i$ 不相同。

一些（可能没有或全部）谷仓被 Annabelle 和 Bessie 分配了相同的编号。计算最多有多少个这样的谷仓。

## 说明/提示

### 样例解释 1

Annabelle 和 Bessie 可以为每个谷仓分配相同的编号。

### 样例解释 2

Annabelle 和 Bessie 无法为任何谷仓分配相同的编号。

### 样例解释 3

Annabelle 和 Bessie 可以分配编号 $2,3,4,6$ 给相同的谷仓。

### 测试点性质

- 测试点 $4-5$ 满足 $N \le 8$。
- 测试点 $6-8$ 满足 $N \le 5000$。
- 测试点 $9-15$ 没有额外限制。

## 样例 #1

### 输入

```
6 3
1 2 3
2 3 1```

### 输出

```
6```

## 样例 #2

### 输入

```
6 3
1 2 3
4 5 6```

### 输出

```
0```

## 样例 #3

### 输入

```
6 4
1 2 3 4
4 3 2 5```

### 输出

```
4```

# 题解

## 作者：strcmp (赞：8)

赛时差点没切。

------------

这个题目描述很屎，要手模一下我才发现两个结论：

1. $a,\,b$ 序列里都没有出现的数，一定能全部互相匹配上，因此答案要加上 $a,\,b$ 里都没有出现过的数的个数。

2. $a,\,b$ 序列里出现过的数的贡献，本质上是对 $b$ 及 **$b$ 的翻转**做 $k - 1$ 次向右循环移位，然后取最多的 $a_i = b_i$ 的 $i$ 数量。为什么要翻转因为环是无向的。

举例来说，样例三：

```
6 4
1 2 3 4
4 3 2 5
```

我们令 $b$ 翻转，循环移位 $0$ 次可以得到最优答案。

第一类的贡献非常好算，因为值域是 $[1,\,n]$，开个桶统计就行了。

第二类贡献，考虑令 $s_i$ 为 $b_i$ 循环移位多少次之后会产生贡献，因为 $a,\,b$ 各自的数互不重复，所以是对的。具体的，令 $d_i$ 为 $a_i$ 的出现位置，分讨 $b$ 的循环移位次数，可得到 $s_i$ 的值，答案即为 $\max_{0 \le i \le k} s_i$。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long int ll;
using pll = pair<ll, ll>;
const int maxn = 5e5 + 10;
const ll mod = 998244353LL;
const ll inf = 1145141919810LL;
int n, k; ll a[maxn], b[maxn], cnt[maxn], sum[maxn]; int d[maxn]; pll c[maxn];
int main() {
	scanf("%d%d", &n, &k); ll ans = 0;
	for (int i = 1; i <= k; i++) scanf("%lld", &a[i]), ++cnt[a[i]], d[a[i]] = i;
	for (int i = 1; i <= k; i++) scanf("%lld", &b[i]), ++cnt[b[i]];
	for (int i = 1; i <= k; i++) {
		int u = d[b[i]];
		if (!u) continue;
		if (u >= i) ++sum[u - i];
		else ++sum[k - i + u];
	}
	for (int i = 0; i <= k; i++) ans = max(ans, sum[i]);
	reverse(a + 1, a + k + 1); memset(d, 0, sizeof(d)); memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= k; i++) d[a[i]] = i;
	for (int i = 1; i <= k; i++) {
		int u = d[b[i]];
		if (!u) continue;
		if (u >= i) ++sum[u - i];
		else ++sum[k - i + u];
	}
	for (int i = 0; i <= k; i++) ans = max(ans, sum[i]);
	for (int i = 1; i <= n; i++) ans += !cnt[i];
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：tanghg (赞：6)

先考虑环外情况。显然如果有一个编号两人均没有使用，那么它可以在外围使用。那么让答案加一。之后考虑环上的答案即可。

我们发现，其实就是我们考虑假设旋转一个环几下和另一个环最多能有几个位置相同。那么因为编号不重复，那么一个编号在另一个环中最多只有一个位置出现，所以在这个位置需要偏移的量上的结果加一即可，最后取一个最大值与原答案相加。

然后因为可以翻转这个环来看所以可以考虑把序列翻转之后再做一遍上述操作。然后就愉快地做完了。
```cpp
#include<iostream>
#include <cstring>
#define endl "\n"
#define int long long
using namespace std;
typedef long long ll;
const ll MAXN=5e5+5;
ll n,k;
ll a[MAXN*2],b[MAXN*2];
bool visa[MAXN],visb[MAXN];
ll d[MAXN],loc[MAXN];
ll ans;
void Do(){
    memset(d,0,sizeof(d));
    for(int i=1;i<=k;++i){
        loc[b[i]]=i;
    }
    for(int i=1;i<=k;++i){
        ll nxt=loc[a[i]];
        if(nxt==0){
            continue;
        }
        if(nxt>i){
            d[nxt-i]++;
        }else{
            d[nxt-i+k]++;
        }
    }
    for(int i=1;i<=k;++i){
        ans=max(ans,d[i]);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= k; ++i) {
        cin >> a[i];
        visa[a[i]] = true;
    }
    for (int i = 1; i <= k; ++i) {
        cin >> b[i];
        visa[b[i]] = true;
    }
    Do();
    ll l=1,r=k;
    while(l<=r){
        swap(a[l],a[r]);
        l++;
        r--;
    }
    Do();
    for (int i = 1; i <= n; ++i) {
        if (!(visa[i] || visb[i])) {
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：听取MLE声一片 (赞：5)

首先没有出现过的编号是一定可以分配相同的，这一部分要先记上。

之后问题转化为一个环可以移动若干位，求和另一个环对应位置相同的最多个数。

直接枚举环移动的位数暴力判断是 $O(n^2)$ 的，考虑优化这个过程。

编号是一个排列，所以环内元素两两不同，则第一个环内一个数至多对应第二个环中的一个数。求出第一个环的每个数要向右平移多少位才能和第二个环对应相同，取最大值即可。

要正反做一遍，因为可以翻转方向。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#include<random>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=5e5+10;
int n,m,ans,a[N],b[N],pos[N],vis[N];
int solve(){
	int res=0;
	map<int,int>mp;
	for(int i=1;i<=m;i++)
		if(pos[b[i]]){
			int x=i-pos[b[i]];
			if(x<0)x+=m;
			mp[x]++;
		}
	for(int i=-n;i<=m;i++)
		res=max(res,mp[i]);
	return res;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		a[i]=read();
		pos[a[i]]=i;
		vis[a[i]]=1;
	}
	for(int i=1;i<=m;i++){
		b[i]=read();
		vis[b[i]]=1;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])ans++;
	int s1=solve();
	reverse(b+1,b+m+1);
	int s2=solve();
	ans+=max(s1,s2);
	cout<<ans;
	return 0;
}

```

---

## 作者：Night_sea_64 (赞：3)

银组的送分题。

这里先解释一下奇怪的题意。就是有 $n$ 个谷仓，其中有一个包含 $k$ 个谷仓的环。有两种编号方式，第一种编号方式下 $a_1,a_2,\dots,a_k$ 这些不同编号的谷仓按顺序连接形成环，第二种编号方式下 $b_1,b_2,\dots,b_k$ 这些不同编号的谷仓按顺序连接形成环。问你最多有多少个谷仓的编号相同。

谷仓的编号分为 3 类。第一类是均不在两个环里的，第二类是只在一个环里的，第三类是在两个环里的。

第一类的所有编号显然都算上，因为在环外的点可以随便编号。第二类的显然都不能算上，因为这两种编号方式下，一个谷仓在环内，另一个谷仓在环外，这两个谷仓就一定不是同一个。

第三类的编号需要考虑环的顺序。设 $m$ 表示第一种编号方式下给定的环的输入顺序的第一个谷仓，在第二种编号方式下输入顺序是第 $m$ 个。然后扫描一下所有第三类的编号，计算出如果这个编号在两种编号方式下对应的两个谷仓如果相同，那么 $m$ 应该是多少，加到桶里，最后取个数最多的 $m$ 即可。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,k,a[500010],b[500010],b2[500010];
int c[500010],ans,pos[500010];
int cnt[500010],maxn;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>a[i];
		c[a[i]]++;
	}
	for(int i=1;i<=k;i++)
	{
		cin>>b[i];
		c[b[i]]++,b2[k-i+1]=b[i];
	}
	for(int i=1;i<=n;i++)
		if(!c[i])ans++;
	for(int i=1;i<=k;i++)
		if(c[a[i]]==2)pos[a[i]]=i;
	for(int i=1;i<=k;i++)
		if(c[b[i]]==2)cnt[(pos[b[i]]+k-i)%k]++;
	for(int i=0;i<k;i++)maxn=max(maxn,cnt[i]);
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=k;i++)
		if(c[b2[i]]==2)cnt[(pos[b2[i]]+k-i)%k]++;
    for(int i=0;i<k;i++)maxn=max(maxn,cnt[i]);
	cout<<ans+maxn<<endl;
	return 0;
}
```

---

## 作者：Mirasycle (赞：2)

如果在 $A$ 和 $B$ 里面都没有出现的数字就可以直接累加到答案里了。然后对于 $A$ 和 $B$ 的处理其实就是找一个 $A_i$ 找一个 $B_j$。两个数组分别从两个下标开始循环一圈，看看有几个相同的。

如果固定 $A$ 数组，枚举 $B$ 数组的话时间复杂度过高，可以看看 $B$ 数组每个数平移几个单位长度可以正好匹配到 $A$ 数组，最多的平移长度加上未出现数字个数就是答案。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=5e5+10;
bool vis[maxn];
int a[maxn],b[maxn],c[maxn],d[maxn];
int ans1=0,cnt=0,n,k;
int calc(){
	memset(d,0,sizeof(d));
	for(int i=1;i<=k;i++){
		if(b[i]==0) continue; 
		if(b[i]==i) d[0]++;
		else if(b[i]<i) d[i-b[i]]++;
		else if(b[i]>i) d[k+i-b[i]]++;
	}
	int Max=0;
	for(int i=0;i<k;i++) Max=max(Max,d[i]);
	return Max;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i]; vis[a[i]]=1;
		c[a[i]]=i; 
	}
	for(int i=1;i<=k;i++){
		cin>>b[i]; vis[b[i]]=1;
		b[i]=c[b[i]];
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]) ans1++;
	int ans2=calc();
	reverse(b+1,b+1+k);
	ans2=max(ans2,calc());
	cout<<ans1+ans2;
	return 0;
}
```

---

## 作者：UncleSam_Died (赞：1)

### 题目大意
两个环呈包含关系，每个环上的元素都不相同，两个环可以自由旋转，问怎么使得重合部分最多。

### 解题思路
显然，我们对于环 $b$ 记录它的每一个元素最少需要转多少圈才会和 $a$ 中的某一元素重合。然后依次枚举每一个可能旋转的位置，看一下有多少个 $b_i$ 可以重合。

### AC 代码
```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 1000005
int n,k,a[N],b[N];
int tong[N],ans;
int cnt1[N],cnt2[N];
int pa[N],pb[N],pf[N];
int fb[N];
namespace Case1{
	inline void Main(){
		for(register int i=k+1;i<=2*k;++i)
			b[i]=b[i-k];
		for(register int i=1;i<=k;++i){
			int cnt=0;
			for(register int j=i;j<k+i;++j)
				if(b[j]==a[j-i+1]) ++cnt;
			ans=std::max(ans,cnt);
		}
		for(register int i=1;i<=k;++i)
			std::swap(b[i],b[k*2-i+1]);
		for(register int i=1;i<=k;++i){
			int cnt=0;
			for(register int j=i;j<k+i;++j)
				if(b[j]==a[j-i+1]) ++cnt;
			ans=std::max(ans,cnt);
		}	
	}
}
namespace Case2{
	inline void Main(){
		for(register int i=1;i<=k;++i)
			fb[k-i+1]=b[i];
		for(register int i=1;i<=k;++i)
			pa[a[i]]=i,pb[b[i]]=i,pf[fb[i]]=i;
		for(register int i=1;i<=k;++i){
			if(pa[b[i]])
				++cnt1[(pa[b[i]]-pb[b[i]]+k)%k];
			if(pa[fb[i]])
				++cnt2[(pa[fb[i]]-pf[fb[i]]+k)%k];
		}
		for(register int i=0;i<k;++i)
			ans=std::max({ans,cnt1[i],cnt2[i]});
	}
}
inline void work(){
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=k;++i)
		scanf("%d",&a[i]);
	for(register int i=1;i<=k;++i)
		scanf("%d",&b[i]);
	for(register int i=1;i<=k;++i)
		tong[a[i]]=tong[b[i]]=1;
	int res=0;
	for(register int i=1;i<=n;++i)
		if(tong[i]==0) ++res;
	if(k<=10000) Case1::Main();
	else Case2::Main();
	ans=ans+res;printf("%d",ans);
}signed main(){
	srand(114514);
	srand(rand());
	srand(time(0));
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	work();return 0;
}



```

---

