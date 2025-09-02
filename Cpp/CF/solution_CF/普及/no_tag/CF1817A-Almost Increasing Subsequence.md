# Almost Increasing Subsequence

## 题目描述

A sequence is almost-increasing if it does not contain three consecutive elements $ x, y, z $ such that $ x\ge y\ge z $ .

You are given an array $ a_1, a_2, \dots, a_n $ and $ q $ queries.

Each query consists of two integers $ 1\le l\le r\le n $ . For each query, find the length of the longest almost-increasing subsequence of the subarray $ a_l, a_{l+1}, \dots, a_r $ .

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

## 说明/提示

In the first query, the subarray is $ a_1, a_2, a_3 = [1,2,4] $ . The whole subarray is almost-increasing, so the answer is $ 3 $ .

In the second query, the subarray is $ a_1, a_2, a_3,a_4 = [1,2,4,3] $ . The whole subarray is a almost-increasing, because there are no three consecutive elements such that $ x \geq y \geq z $ . So the answer is $ 4 $ .

In the third query, the subarray is $ a_2, a_3, a_4, a_5 = [2, 4, 3, 3] $ . The whole subarray is not almost-increasing, because the last three elements satisfy $ 4 \geq 3 \geq 3 $ . An almost-increasing subsequence of length $ 3 $ can be found (for example taking $ a_2,a_3,a_5 = [2,4,3] $ ). So the answer is $ 3 $ .

## 样例 #1

### 输入

```
9 8
1 2 4 3 3 5 6 2 1
1 3
1 4
2 5
6 6
3 7
7 8
1 8
8 8```

### 输出

```
3
4
3
1
4
2
7
1```

# 题解

## 作者：2021sunzishan (赞：8)

一道不错的前缀和题，细节较多。

## 题目大意：

给定一个有 $n$ 个数的序列，且给出 $m$ 个询问，每次询问区间 $[l,r]$，问此区间内最长的几乎递增子序列长度是多少。

所谓几乎递增子序列是指，若该序列中不存在连续的三个数 $x$，$y$，$z$，使得 $x\ge y\ge\ z$，那么此序列为几乎递增子序列。

**看到这里，果断使用前缀和思想。**
## 思路：

定义前缀和数组 $s[i]$，表示以 $i$ 结尾的，在这之前共有多少个元素满足 $x \ge y \ge \ z$。

询问时，只需要用区间的长度减去区间当中有多少满足条件的元素即可。

但需要注意的是，$s[l]$ 由 $a[l-1]$ 和 $a[l-2]$ 决定，$s[l+1]$ 由 $a[l]$ 和 $a[l-1]$ 决定，含有不在区间内的元素，所以算的时候应该从 $s[l+2]$ 开始算，当然还要减 $1$。所以满足要求的元素个数为 $s[r]-s[(l+2)-1]$，即 $s[r]-s[l+1]$。

注意还要特判区间长度不足 $3$ 的情况。

以上就是本题的思路了，如果还没有看懂，就看代码吧！

**切勿抄袭！！！**
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[200005],s[200005];
inline int read() {//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
int main() {
//	freopen("1.in","r",stdin);
//	freopen(".out","w",stdout);
	n=read(),m=read();
	for(int i=1; i<=n; i++) {
		a[i]=read();
		if(i<3)continue;
		if(a[i]<=a[i-1]&&a[i-1]<=a[i-2])//如果满足要求
			s[i]=s[i-1]+1;//前缀和累加
		else
			s[i]=s[i-1];
	}
	while(m--) {
		int l=read(),r=read();
		int ls=r-l+1;//区间长度
		if(ls<=2)//特判
			printf("%d\n",ls);
		else
			printf("%d\n",ls-(s[r]-s[l+1]));//求答案
	}
	return 0;
}


```
完结~


---

## 作者：Withershine (赞：8)

# 2023.5.18 修正关于前缀和数组的说法，与代码适配的思路。

## 题意
给定长度为 $n$ 一个序列 $a$ 以及 $q$ 次询问，每次询问给出 $l$ 和 $r$，要求找出序列 $a$ 在 $[l,r]$ 内最长的**几乎递增**子序列。

对于几乎递增的定义：如果一个序列中不存在**连续的**三个数 $x$，$y$，$z$，使得 $x \ge y \ge \ z$，则这个序列是几乎递增的。

## 思路
用一个前缀和数组 $s$ 记录，其中 $s_i$ 表示从 $a_3$ 到 $a_i$ 中满足 $a_{i-2} \ge a_{i-1} \ge a_{i}$ 的 $i$ 的数量。对于每次询问，输出 $r-l+1-(s_r-s_{l+1})$ 即可。

简单做个解释，对于每个 $a_{i-2} \ge a_{i-1} \ge a_{i}$，只有 $a_i$ 会决定是否满足当前式子，所以不选择 $a_i$。举个例子:

5 4 3 2 1 2 3 4 5 1

在上面的序列中，子序列 ${5,4,3}$，${4,3,2}$ 和 ${3,2,1}$ 都是不满足题目要求的，当输入 $l=1$，$r=10$ 时，输出答案为 $7$。可以想到，选中的 $7$ 个数可以是这样的：

_5 4_（**3 2 1**） _2 3 4 5 1_

也可以是这样的：

（**5 4 3**） _2 1 2 3 4 5 1_

为了区分选择与未被选择，这里用斜体与粗体区分开，选择方法不止两种，上面的第一种选法，与给出的解释一致。

### 证明
当序列中存在 $a_i \ge \dots \ge a_{j-2} \ge a_{j-1} \ge a_j$，$j-i+1 \ge 3$ 时，对于这一部分，一定有 $j-i-1$ 个连续的三个数 $x$，$y$，$z$，使得 $x \ge y \ge \ z$。

从第 $j$ 项开始，每不选择一个 $a_j$，相对应序列 $a_{j-2},a_{j-1},a_j$ 的规律就会被破坏，要破坏掉整个从 $a_i$ 到 $a_j$ 的序列的规律，至少要破坏到 $a_{i+2}$ 的位置（也包括 $a_{i+2}$ 这个位置）。故最多只能选择 $2$ 个数。

当 $j-i+1=3$，即最短满足 $x \ge y \ge \ z$ 的序列时，最多只能选择 $2$ 个，也就是至少要不选一个。（这里其实不选哪一个都是一样的）

### 前缀数组（2023.5.18 新增）
对于每一个 $s_i$，记录的是从 $a_3$ 到 $a_i$ 中满足 $a_{i-2} \ge a_{i-1} \ge a_{i}$ 的 $i$ 的数量。而对于区间 $[l,r]$ 来说，第 $a_l$ 项对应的序列（上面说的三元组）从 $a_{l-2}$ 就开始了，第 $a_{l+1}$ 项对应的序列从 $a_{l-1}$ 就开始了，因此不能将第 $a_{l}$ 与第 $a_{l+1}$ 项对应的序列算入这个区间内。所以最后的答案应该是从第 $s_{l+2}$ 项算起，结论就是 $r-l+1-(s_r-s_{(l+2)-1})$，即 $r-l+1-(s_r-s_{l+1})$。

## 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n , q , a[200005];
ll l , r;
ll f[200005] , now;
inline ll answer(ll L , ll R)
{
    ll ans = f[R] - f[L + 1];
    if(R - L + 1 <= 2)//特判，区间长度为2或1
    {
        ans = 0;
    }
    return R - L + 1 - ans;
}
signed main()
{
    n = read();
    q = read();
    fr(i , 1 , n)
    {
        a[i] = read();
        if(i >= 3)
        {
            now = 0;
            if(a[i - 2] >= a[i - 1] && a[i - 1] >= a[i])
            {
                now = 1;
            }
            f[i] = f[i - 1] + now;
        }
    }
    while(q--)
    {
        l = read();
        r = read();
        printf("%lld\n" , answer(l , r));
    }
    system("pause");
    return 0;
}
```


---

## 作者：沉石鱼惊旋 (赞：4)

[更好的阅读体验](http://blog.cyx2009.top/archives/167/)

# 题目翻译

> 我们定义“几乎递增”序列表示这个序列没有 $3$ 个连续的元素 $x,y,z$ 使得 $x\ge y\ge z$。
> 
> 现在有一个长度为 $n$ 的序列，有 $q$ 次询问，每次问一个区间 $[l,r]$，你回答 $[l,r]$ 中最长的“几乎递增”子序列长度。
> 
> 一行 $2$ 个正整数 $n,q$ 表示长度和查询个数。
> 
> $q$ 行每行 $1$ 个整数，表示最长的“几乎递增”子序列长度。
> 
> $1\leq n,q\leq 2\times 10^5,a_i\leq 10^9$。

# 题目思路

这里讲一下莫队算法。

因为莫队算法是基于分块的，也就是说每个询问，莫队算法的时间复杂度为 $\mathcal O(\sqrt n)$，总时间复杂度 $\mathcal O(q\sqrt n)$，可以接受。

很显然，这题在进行莫队的时候，我们只需对于新进的数字判断一下三个数关系即可实现莫队精华部分。

接着我们按照莫队常规操作记录编号输出即可。

# 完整代码


```cpp
#include<bits/stdc++.h>
usingnamespacestd;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
char buf[1000000],*p1=buf,*p2=buf;
inline int read()
{
    registerchar c=getchar();registerint x=0;
    while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}
int len,n,q;
int a[200020];
int ans[200020];
struct node
{
	int l,r,id;
}b[2000020];
bool cmp(node x,node y)
{
    int fx=(x.l-1)/len,fy=(y.l-1)/len;
    if(fx^fy)return fx<fy;
    if(fx&1)return x.r>y.r;
    return x.r<y.r;
}
int main()
{
    n=read();q=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
    }
    len=sqrt(n);
    for(int i=1;i<=q;i++)
    {
        int l,r;
        l=read();r=read();
        b[i]={l,r,i};
    }
    sort(b+1,b+q+1,cmp);
    int l=1,r=0,ANS=0;
    for(int i=1;i<=q;i++)
	{
		while(r<b[i].r)
		{
			r++;ANS++;
			if(r-l+1<3)continue;
			if(a[r-2]>=a[r-1]&&a[r-1]>=a[r])ANS--;
		}
		while(r>b[i].r)
		{
			if(r-l+1<3)
			{
				r--;ANS--;
				continue;
			}
			if(a[r-2]<a[r-1]||a[r-1]<a[r])ANS--;
			r--;
		}
		while(l<b[i].l)
		{
			if(r-l+1<3)
			{
				l++;ANS--;
				continue;
			}
			if(a[l]<a[l+1]||a[l+1]<a[l+2])ANS--;
			l++;
		}
		while(l>b[i].l)
		{
			l--;ANS++;
			if(r-l+1<3)continue;
			if(a[l]>=a[l+1]&&a[l+1]>=a[l+2])ANS--;
		}
		ans[b[i].id]=ANS;
	}
	for(int i=1;i<=q;i++)
    {
        printf("%d\n",ans[i]);
    }
    return0;
}
```



---

## 作者：Shunpower (赞：3)

### 题意

定义一个序列是**几乎上升的**，当且仅当它不包含三个连续的元素 $x,y,z$ 满足 $x\geq y\geq z$。

有一个长度为 $n$ 的序列，给出 $q$ 个询问，每次询问 $l,r$，表示询问 $a_l,a_{l+1},a_{l+2},\cdots a_r$ 组成的序列中**最长的几乎上升子序列长度**。

### 思路

下文令 $a_l,a_{l+1},a_{l+2},\cdots a_r$ 组成的序列为 $b$。

下文说长度大于等于 $3$ 的极长的单调不递增子段为**坏子段**。

我们不妨先考虑如何在 $O(n)$ 时间内得到一个序列 $b$ 的答案。要算出最长上升子序列长度，就意味着需要删除最少的元素数量。我们可以把 $b$ 序列中所有坏子段拿出来，这些子段都妨碍了我们将 $b$ 变为一个几乎上升的序列。

能够发现因为我们拿出来的这些子段都是极长的，所以这些子段互不相交。

那么我们考虑每一个子段，对于一个子段，很显然其中只能留下两个元素，否则仍然无法满足约束。虽然删去一些元素后很多原本不相邻的元素会变得相邻，但是可以发现，只要对于某一个子段留且仅留下首尾两个元素就不会在删完之后再次出现反例。因为首元素的前一个元素必然小于它，而尾元素的后一个元素必然大于它，无论如何都不可能存在一个包含这两个元素其中之一的反例。

那么如何加快速度呢？

首先我们可以先求出原本 $a$ 序列中的坏子段。然后可以发现，在 $[l,r]$ 区间中，包含若干完整的坏子段。很显然，我们可以前缀和每个坏子段的长度减掉 $2$，然后在查询中快速得到所有完整坏子段中需要删去的元素数量。

而 $l,r$ 可能也归属于一个坏子段，因此要对两边进行统计，如果两边也存在于坏字段中，并且这个坏子段在 $[l,r]$ 内的部分的长度大于等于 $3$，就也需要删去其在 $[l,r]$ 内的部分的长度减去 $2$ 个元素。

加在一起就可以得到最少要删去的元素个数，用区间长度减掉就可以得到最长几乎上升子序列长度。

### 代码

在代码实现中为了方便，我们可以将所有元素先分成一堆极长的单调不递增子段，但注意在统计答案时，只有长度大于等于 $3$ 的这样的子段才能贡献。

```
int n,q;
int a[N];
int sum[N];
vector <pii> seq;
int lst=1;
int now=1;
int bel[N];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    fr1(i,1,n){
        cin>>a[i];
    }
    seq.pb(0,0);
    fr1(i,1,n-1){
        if(a[i]>=a[i+1]){
            now++;
        }
        else{
            fr1(j,lst,now){
                bel[j]=seq.size();//记录下每个元素归属于哪个极长的单调不递增子段
            }
            seq.pb(mp(lst,now));
            lst=now=i+1;
        }
    }
    fr1(j,lst,now){
        bel[j]=seq.size();
    }
    seq.pb(mp(lst,now));
    fr1(i,1,seq.size()-1){
        sum[i]=sum[i-1]+(seq[i].se-seq[i].fi+1>=3?seq[i].se-seq[i].fi-1:0);
    }//对坏子段中需要删去的元素数量垒前缀和，如果不坏则记为0
    while(q--){
        int l,r;
        cin>>l>>r;
        if(bel[l]==bel[r]){//归属于同个极长单调不递增子段
            cout<<min(2,r-l+1)<<endl;
            continue;
        }
        int lef=seq[bel[l]].se-l+1;//拿出包含l的极长的单调不递增子段在[l,r]内的部分的长度
        if(lef<3){
            lef=0;
        }
        else{
            lef-=2;
        }//算出要删掉多少元素
        int rig=r-seq[bel[r]].fi+1;//拿出包含r的极长的单调不递增子段在[l,r]内的部分的长度
        if(rig<3){
            rig=0;
        }
        else{
            rig-=2;
        }//同理
        cout<<r-l+1-(sum[bel[r]-1]-sum[bel[l]]+lef+rig)<<endl;//前缀和相减得到完整坏子段的贡献，加上两边的贡献得到删去元素的最小数量，再用区间长度减掉
    }
    ET;
}
```

[AC 记录](https://codeforc.es/contest/1818/submission/203929990)

---

## 作者：Jerry_heng (赞：2)

（一）

先找出符合 $a_i \ge a_{i+1} \ge a_{i+2}$ 的所有 $i$。

将问题按左端点（或右端点）排序。

对于每一个问题，找出最左的符合条件的 $l$ 和最右的符合条件的 $r$。

由于时间会超，$r$ 用二分搜。

然后一般的 $ans$ 就是给定区间长度减去 $r$ 和 $l$ 间距离。

特殊情况见代码。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,l,a[200011],k,ans[200011],be[200011];
struct node{
	int x,y;
}dis[200011];
struct nodd{
	int x,y,sit;
}ask[200011];
bool cmp(nodd p1,nodd p2){
	return p1.x<p2.x||p1.x==p2.x&&p1.y<p2.y;
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n-2;i++)if(a[i]>=a[i+1]&&a[i+1]>=a[i+2])be[++k]=i;
	be[k+1]=1000000;
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&ask[i].x,&ask[i].y);
		ask[i].sit=i;
	}
	sort(ask+1,ask+q+1,cmp);
	for(int i=1;i<=q;i++){
		while(be[l]<ask[i].x&&l<k)l++;
		int ll=l,rr=k,r;
		while(ll<=rr){
			int mid=(ll+rr)>>1;
			if(be[mid]+2<=ask[i].y)r=mid,ll=mid+1;
			else rr=mid-1;
		}
		if(be[l]+2>ask[i].y||be[l]<ask[i].x)ans[ask[i].sit]=ask[i].y-ask[i].x+1;
		else ans[ask[i].sit]=ask[i].y-ask[i].x+1-(r-l+1);
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：AfterFullStop (赞：1)

虽然 *1500，但似乎我又有不同做法了（？），于是发一下。

考虑把序列分成若干不上升段（即在上升处划一刀）。首先每一段里面一定不可能选三个。不妨设询问的为整个序列，考虑取每个段的左右端点（如果一段只有一个元素那么就只选他一个），显然是满足的。于是设长度不等于 $1$ 的段数为 $a$，等于 $1$ 的段数为 $b$，则答案为 $2a+b$。

对于左右两段，特判即可。

实现时可以考虑分成两个 set 存两种段，当然更优美的实现方式是考虑在每个段的端点处各对差分数组加上 $1$。

```cpp
#include<bits/stdc++.h>
#define ri int
#define ll long long
#define mkp make_pair
#define mkt make_tuple
#define ld long double
using namespace std;
const int maxn=4e5+7;
const int inf=2e9;
const int mod=998244353;
const ld eps=1e-9;
int n,q;
int a[maxn];
int cf[maxn];
void solve(){
	cin>>n>>q;
	for(ri i=1;i<=n;i++)cin>>a[i];
	for(ri i=1;i<=n;i++)cf[i]=0;a[n+1]=inf;
	for(ri i=1,j=0;i<=n;i=j+1){
		j++;
		while(j+1<=n&&a[j+1]<=a[j])j++;
		if(i==j)cf[j]++;
		else cf[i]++,cf[j]++;
	}
	for(ri i=1;i<=n;i++)cf[i]+=cf[i-1];
	for(ri i=1;i<=q;i++){
		int l,r;cin>>l>>r;
		int ans=cf[r]-cf[l-1];
		if(ans==0){
			ans=min(r-l+1,2);
		}
		else{
			if(a[r]<=a[r-1]&&a[r]>=a[r+1])ans++;
			if(a[l]>=a[l+1]&&a[l]<=a[l-1])ans++;	
		}
		cout<<ans<<'\n';
	}
}
signed main(){
	ios::sync_with_stdio(0);
	int T=1;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Red_river (赞：1)

### 题目大意
给你一些数，定义不能有**连续三个数**使得后两个数**小于等于**前一个数。求一段区间内最大符合条件的子序列有多长。
### 题意分析
其实我们不难发现，这道题如此巨大的数据范围，时间复杂度肯定是 $O(n)$ 的。这就容易想到了前缀和。我们需要预处理出当前位置比前一个位置大的**连续**区间的长度，接着求出大于二的长度的前缀和。因为存的时候漏了个一。之后你想使其符合条件，就需要将除了两个之外的所有字符都删掉。具体可参考代码理解。
### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 250005
#define NO printf("No\n")
#define YES printf("Yes\n")

using namespace std;

int n, m, k, jk, ans, sum, num, cnt, tot;
int head[N], dis[N], vis[N], wis[N], f[N];

// 读取函数
void read(int &x)
{
	x = 0;
	int ff = 1;
	char ty;
	ty = getchar();
	while(!(ty >= '0' && ty <= '9'))
	{
		if(ty == '-') ff = -1;
		ty = getchar();
	}
	while(ty >= '0' && ty <= '9')
		x = (x << 3) + (x << 1) + ty - '0', ty = getchar();
	x *= ff;
	return;
}

// 写入函数
void write(int x){
	if(x == 0){
		putchar('0');
		return;
	}
	if(x < 0){
		x = -x;
		putchar('-');
	}
	char asd[201];
	int ip = 0;
	while(x) asd[++ip] = x % 10 + '0', x /= 10;
	for(int i = ip; i >= 1; i--) putchar(asd[i]);
	return;
}

signed main()
{
	// 读取序列长度n和查询次数m
	read(n), read(m);

	// 读取序列的元素并计算vis和f数组
	for(int i = 1; i <= n; i++){
		read(dis[i]);
		if(i != 1 && dis[i - 1] >= dis[i]) vis[i] = vis[i - 1] + 1;  // 记录递减区间的长度
		else vis[i] = 0;  // 否则为0
		f[i] = f[i - 1] + (vis[i] >= 2);  // 更新f数组，记录递减子序列的长度
	}

	// 处理每个查询
	int x, y;
	while(m--){
		read(x), read(y);
		wh(y - x + 1 - (f[y] - f[min(x + 1, y)]));  // 由于要大于二的才算，所以要让其位置加一的值与右区间取最小值。
	}

	return 0;
}
```

---

## 作者：Guizy (赞：1)

### Almost Increasing Subsequence 题解

看到区间，想到前缀和。设 $s_i$ 表示的是到 $i$ 为止有多少 $x,y,z$ 满足 $x \geq y \geq z$。

所以很快我们就可以计算出 $s_i$。

```cpp
for (int i = 1; i <= n; i++)
{
    cin >> a[i];
    if (i >= 3 && a[i] <= a[i - 1] && a[i - 1] <= a[i - 2])
        s[i] = s[i - 1] + 1;
    else
        s[i] = s[i - 1];
}
```

然后对于一个区间，每个 $x \geq y \geq z$ 都必须至少删掉一个，所以答案为区间长度减去区间的 $x \geq y \geq z$ 的 $(x,y,z)$ 的个数。注意这个个数是 $s_r-s_{l+1}$ 而不是 $s_r-s_{l-1}$。

注意特判 $l=r$ 的情况。

```cpp
#include <bits/stdc++.h>
#define int long long
#define r(x) for (int i = 1; i <= x; i++)
using namespace std;

const int N = 5e5 + 10;
int n, q, a[N], s[N], l, r;

signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    r(n)
    {
        cin >> a[i];
        if (i >= 3 && a[i] <= a[i - 1] && a[i - 1] <= a[i - 2])
            s[i] = s[i - 1] + 1;
        else
            s[i] = s[i - 1];
    }
    r(q)
    {
        cin >> l >> r;
        cout << (r - l + 1) - (s[r] - s[min(r, l + 1)]) << "\n";//特判 l=r，直接取 min 即可。
    }

    return 0;
}
```

---

