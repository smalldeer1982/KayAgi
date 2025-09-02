# [NEERC 2013] Hack Protection

## 题目描述

Pavel 正在给他的朋友 Egor 发送一些非负整数数组。他希望确保在他的朋友收到数组之前，没有人篡改过它。为了解决这个问题，Pavel 需要为他的数组计算某种校验和或摘要。Pavel 有一个创新的头脑，所以他发明了以下算法来计算他的数组的摘要：计算子数组中数字的按位异或等于相同数字的按位与的子数组的数量。

例如，考虑一个由四个二进制数 `01`、`10`、`11` 和 `11` 组成的数组。左下表列出了该数组每个子数组的数字的按位异或结果，右下表列出了该数组每个子数组的数字的按位与结果。表格的行对应于子数组的起始元素，从数组的第 $1$ 个元素到第 $4$ 个元素，而列对应于子数组的结束元素。匹配的值用灰色背景突出显示。

![](/upload/images2/hp.png)

你的任务是帮助 Pavel 计算给定数组的这种摘要。

## 说明/提示

时间限制：1 秒，内存限制：128 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
1 2 3 3
```

### 输出

```
6
```

# 题解

## 作者：Transparent (赞：4)

由于与的性质，固定右端点后，区间与和的每一位都是在一点前全为 $0$，之后全为 $1$。根据这个性质，可以推出使得与和不同的左端点至多有 $62$ 个（每两个反转一位）。于是可以暴力维护这些与和相等的区间，并利用异或前缀和查询异或和等于与和的位置的数量。

与和相等的区间可以直接用 `vector` 维护，每次暴力更新并合并值相同的区间。查询某区间中异或前缀和恰为某值可以用 `map<int,vector<int>>` 记录每个值出现的位置，然后二分。

注意不要把 `vector` 从 `map` 里复制出来。

时间复杂度 $O(n \log n \log V)$。

~~目前最快的~~代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll=long long;

constexpr int MAXN=1e5+10;

map<int,vector<int>> mp;
int n,a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<pair<int,int>> val;
    cin>>n; int pre=0; ll ans=0; mp[0].emplace_back(0);
    for(int i=1;i<=n;++i) {
        cin>>a[i]; pre^=a[i]; mp[pre].emplace_back(i);
        for(auto &[r,v]:val) v&=a[i];
        val.emplace_back(i,a[i]);
        vector<pair<int,int>> tmp; int p=0,cur=-1;
        for(auto &[r,v]:val) {
            if(cur!=v) {
                if(p) tmp.emplace_back(p,cur);
                cur=v;
            }
            p=r;
        }
        tmp.emplace_back(p,cur); swap(tmp,val);
        int lst=0;
        for(auto [r,v]:val) {
            int req=pre^v;
            if(mp.find(req)==mp.end()) {lst=r; continue;}
            auto &vec=mp[req];
            ans+=upper_bound(vec.begin(),vec.end(),r-1)-lower_bound(vec.begin(),vec.end(),lst);
            lst=r;
        }
    }
    cout<<ans<<endl;

    return 0;
}
```

---

## 作者：a___ (赞：2)

考虑对于左端点固定的情况，对于每一位，如果已变为 $0$ 就一定不会变回 $1$，所以向右的与和最多有 $31$ 种（右端点右移与和一定变为原来的子集）。     

我们按位记一个 `nxt` 表示这一位下一个 $0$ 在哪里出现。排序后从左向右扫一遍就可以找到 $31$ 种和的区间（即 $[nxt_{i,j},nxt_{i,j+1})$），然后问题就变为在这 $31$ 个区间内询问一个数（$k\oplus s_{i-1}$（$k$ 表示当前区间与和；$s$ 表示前缀异或和））的出现次数。   

我们用一个 `vector` 记一个数出现的位置，然后在位置序列上二分，就可轻松找到区间一个数的出现次数（具体看代码理解）。    

```cpp
const int N=100010;
std::vector<int>c[N];
int n,a[N],b[N];std::pair<int,int>nxt[N][35];
long long ans;
int main()
{
    int i,j,k,x;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    scanf("%d",&a[i]),b[i]=b[i-1]^a[i];
    for(i=n+1;i>=1;i--)
    for(j=0;j<31;j++)nxt[i][j+1].second=j,(nxt[i][j+1].first=(a[i]>>j)&1?nxt[i+1][j+1].first:i);
    std::sort(b+1,b+1+n);b[n+1]=-1;
    for(i=1;i<=n;i++)c[std::lower_bound(b+1,b+1+n,a[i]^=a[i-1])-b].push_back(i);
    for(i=1;i<=n;i++)
    {
        std::sort(nxt[i]+1,nxt[i]+32);nxt[i][0].first=i;nxt[i][32].first=n+1;
        for(k=2147483647,j=0;j<32;k^=(1<<nxt[i][++j].second))
        x=std::lower_bound(b+1,b+1+n,k^a[i-1])-b,b[x]==(k^a[i-1])&&(
        ans+=std::lower_bound(c[x].begin(),c[x].end(),nxt[i][j+1].first)
        	-std::lower_bound(c[x].begin(),c[x].end(),nxt[i][j].first));
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：gxy001 (赞：1)

首先，将一个数与上另一个数，这个数 1 的数量不增，所以当左端点固定时，区间的与和最多只有 $\log$ 种取值。

对于与和相同且左端点固定的区间，我们只需要在 $O(\log)$ 的时间内找到其中有多少个区间异或和等于这个固定的与和即可，设区间端点为 $l,r$。

我们求出原数列的异或前缀和，设为数列 $b$，则 $\oplus_{i=l}^ra_i=b_r\oplus b_{l-1}$，设与和为 $x$ 我们求的就是 $\sum\limits_{i=l}^r[b_i\oplus b_{l-1}=x]=\sum\limits_{i=l}^r[b_i=b_{l-1}\oplus x]$，$b_{l-1}\oplus x$ 当区间固定时是定值，所以问题被转化为经典问题，求区间内给定数的出现次数，由于询问次数是 $O(n\log a_i)$ 所以我们要在 $O(\log)$ 内完成查询，使用 vector 里二分或主席树均可。

总复杂度 $O(n\log a_i\log n)$

代码
--
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
std::vector<int> v[100010];
int lg[100010],a[100010][18],b[100010],n,qcnt,c[100010];
long long ans;
int query(int const &l,int const &r){
	int k=lg[r-l+1];
	return a[l][k]&a[r-(1<<k)+1][k];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a[i]),c[i]=b[i]=b[i-1]^a[i][0];
	std::sort(c+1,c+n+1);
	for(int i=1;i<=n;i++)b[i]=std::lower_bound(c+1,c+n+1,b[i])-c,v[b[i]].push_back(i);
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int j=1;j<=lg[n];j++)
		for(int i=1;i+(1<<(j-1))<=n;i++)
			a[i][j]=a[i][j-1]&a[i+(1<<(j-1))][j-1];
	for(int i=1;i<=n;i++){
		int l=i,r=i;
		for(;l<=n;l=r+1){
			int ll=l,rl=n,mid=0,res=query(i,l);
			while(ll<=rl){
				mid=(ll+rl)>>1;
				if(query(i,mid)!=res) rl=mid-1;
				else ll=mid+1,r=mid;
			}
			int ord=res^c[b[i-1]];
			int p=std::lower_bound(c+1,c+n+1,ord)-c;
			if(p<=n&&c[p]==ord)
				ans+=std::upper_bound(v[p].begin(),v[p].end(),r)-std::lower_bound(v[p].begin(),v[p].end(),l);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Star_Cried (赞：1)

## P7003 [NEERC2013]Hack Protection

### 题意

给定一个序列 $a$ ，求有多少个区间满足区间内的数的异或和等于与的和的值。

### 思路

首先我们求一个异或前缀和 $s$，对于每一个区间 $[l,r]$ ，它的贡献为区间内按位与的和等于 $s_r \bigoplus s_{l-1}$ 的段的个数。

设 $x$ 为某个区间的按位与的和，上面的也就是：
$$
s_r \bigoplus s_{l-1}=x\ \Leftrightarrow \ s_r=x \bigoplus s_{l-1}
$$
发现，如果我们固定 $x$ 和 $s_{l-1}$ ，那么 $s_r$ 就是固定的，我们就可以求区间内与 $s_r$ 相等的数的个数来统计答案。

考虑枚举 $l$ ，发现，对于往后按位与的过程，$x$ (与上文定义相同)最多会变化 $\log$ 次，我们就可以将其分为这么多段，然后在 $s$ 中求与 $s_r$ 相等的数的个数就可以了。

求每一段的按位与结果，可以记录变成 0 的那一位是什么，或者直接 st 表查询都行。

对于最后一个问题，我们可以用主席树，或者简单地离散化加 `vector` 上二分即可。

### 实现

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
#include<vector>
#include<utility>
#define int unsigned 
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10;
	int pre[maxn][35],n,a[maxn],b[maxn],s[maxn];
	long long ans;
	vector<int> V[maxn];
	pair<int,int> q[35];
	inline void work(){
		n=read();
		for(int i=1;i<=n;i++) s[i]=read(),a[i]=b[i]=a[i-1]^s[i];
		sort(b+1,b+1+n);
		int cnt=unique(b+1,b+1+n)-b-1;
		for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+cnt,a[i])-b;
		for(int i=1;i<=n;i++) V[a[i]].push_back(i);
		for(int j=0;j<31;j++) pre[n+1][j]=n+1;
		for(int i=n;i;i--)
			for(int j=0;j<31;j++)
				pre[i][j]=((s[i]>>j)&1)?pre[i+1][j]:i;
		for(int l=1;l<=n;l++){
			int tot=0,x=s[l];
			q[0].first=l;
			for(int j=0;j<31;j++)
			if((s[l]>>j)&1) q[++tot]=make_pair(pre[l][j],j);
			q[++tot]=make_pair(n+1,0);
			sort(q+1,q+1+tot);
			for(int i=1;i<=tot;i++){
				int y=lower_bound(b+1,b+1+cnt,x^b[a[l-1]])-b;
				if(y<=n and b[y]==(x^b[a[l-1]]))
				ans+=(lower_bound(V[y].begin(),V[y].end(),q[i].first)-lower_bound(V[y].begin(),V[y].end(),q[i-1].first));
				x^=(1<<q[i].second);
			}
		}
		printf("%lld\n",ans);
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：JZJR_A_0 (赞：0)

# 题解：Hack Protection

## 前置知识

* 位运算
* 数据结构
* 二分

## 思考

注意两个位运算性质：

* $A\oplus B=C,A=B\oplus C$
* $A\otimes B\leq A$

这启示我们区间 $[l,r]$ 的与和至多只有 $\log{a}$ 个不同值，不妨考虑从此入手。

由于与和至多只有 $\log{a}$ 个，那么一段区间就会被分为 $\log{a}$ 段。

不妨设现在在值为 $\otimes_{i=l}^ra_i=x$ 的区间内那么由性质一，区间 $[l,r]$ 的异或和为其前缀数组 $b$ 的 $b_r\oplus b_{l-1}$。

所以若区间有贡献，则有 $b_r\oplus b_{l-1}=\otimes_{i=l}^ra_i$。

那么有 $b_r=(\otimes_{i=l}^ra_i)\oplus b_{l-1}$。

所以当 $b_{l-1}$ 和区间与和 $x$ 为定值时 $b_r$ 也为定值。

那么问题被转换成了求区间内定值个数，爱用什么方法用什么方法。

## 实现

实现相比思考比较麻烦，主要是三个点。

### 如何分段

因为性质二，区间的与和是单调的。考虑二分处理，找到第一个使得区间与改变的数即可完成分段。

### 求区间与和

因为与是没有前缀和差分性质的，所以考虑合并类的数据结构，比如树状数组，ST表，线段树。

当然，ST表肯定是最优的。

### 求区间定值个数

比较闲的可以使用可持久化权值线段树（主席树）或者离线算法。不过我推荐使用 ```vector``` 或者 ```map``` 来二分求解。

### AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
vector<int>mp[N];
int lg[N],a[N][20];
int b[N],n,qcnt,c[N];
long long ans;
struct ST{
	inline void biuld(){
		for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
		for(int j=1;j<=lg[n];j++){
			for(int i=1;i+(1<<(j-1))<=n;i++){
				a[i][j]=a[i][j-1]&a[i+(1<<(j-1))][j-1];
			}		
		}	
	}
	inline int ask(int l,int r){
		int k=lg[r-l+1];
		return a[l][k]&a[r-(1<<k)+1][k];
	}
}ST;
inline void init(){
	for(int i=1;i<=n;i++){
		c[i]=b[i]=b[i-1]^a[i][0];
	}
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++){
		b[i]=lower_bound(c+1,c+n+1,b[i])-c;
		mp[b[i]].push_back(i);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i][0];
	init();ST.biuld();
	for(int i=1;i<=n;i++){
		int l=i,r=i;
		for(;l<=n;l=r+1){
			int L=l,R=n,mid=0;
			int res=ST.ask(i,l);
			while(L<=R){
				mid=(L+R)>>1;
				if(ST.ask(i,mid)!=res)R=mid-1;
				else L=mid+1,r=mid;
			}
			int tik=res^c[b[i-1]];
			int p=lower_bound(c+1,c+n+1,tik)-c;
			if(p<=n&&c[p]==tik){
				ans+=upper_bound(mp[p].begin(),mp[p].end(),r)-lower_bound(mp[p].begin(),mp[p].end(),l);
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

但是由于本题细节奇多，堪比万宁俄罗斯方块，这里提供暴力代码与数据生成帮助对拍。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
const int inf=1e18;
int n,a[N],ans=0;
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int l=1;l<=n;l++){
		int x=0,y=INT_MAX;
		for(int r=l;r<=n;r++){
			x^=a[r];y&=a[r];
			if(x==y)ans++;
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mod=INT_MAX;
inline int rd(){
	return (rand()*rand()+rand()*rand())%mod+1;
}
signed main (){
	srand(0);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n=10000;
	cout<<n<<'\n';
	for(int i=1;i<=n;i++)cout<<rd()<<' ';
	cout<<'\n';
	return 0;
}
```

最后：

## 为什么 C++ 不能自带一个 ```#define int long long```！

---

## 作者：tanyichen_space (赞：0)

好像还没有 $O(n \log{n})$ 的做法，来写一篇。
### 性质 1
记 $\bigoplus _l ^r a_i$ 为 $[l,r]$ 的异或和，$\bigotimes _l ^r a_i$ 为 $[l,r]$ 的与和，$pre_i=\bigoplus _l ^r a_i$，则对于一段区间 $[l,r]$，它能产生贡献，当且仅当
$$ \bigoplus _l ^r a_i= \bigotimes _l ^r a_i$$
即
$$pre_{l-1} \oplus pre_r= \bigotimes _l ^r a_i$$
即
$$pre_{l-1}= \bigotimes _l ^r a_i \oplus pre_r$$
### 性质 2
记 $W=\max{a_i}$
右端点 $r$ 固定，$\bigotimes _l ^r a_i$ 随 $l$ 的递减单调不增，且最多出现 $\log{w}$ 次。
### Solution
我们先预处理出每个右端点对应与值，记 $f_{i,j,fi}$ 为以 $i$ 为右端点，第 $j$ 大的与值，$f_{i,j,se}$ 为其对应最大的左端点。由与运算的结合律，$f_{i,j,fi}$ 可由 $f_{i-1,j,fi}$ 与 $a_i$转移得。具体实现见代码。

接着统计答案，考虑区间集合 $\{[f_{i,j+1,se}+1,i],[f_{i,j+1,se}+2,i],...,[f_{i,j,se}-1,i],[f_{i,j,se},i]\}$ 对答案的贡献，它们与值都是  $f_{i,j,fi}$，由性质2，它们对答案的贡献等于 $、\{pre_{f_{i,j+1,se}},pre_{f_{i,j+1,se}+1},...pre_{f_{i,j,se}-1}\}$ 中 $f_{i,j,fi} \oplus pre_r$ 的个数。

现在问题转化为，给定若干对 $(A,B,C)$，求 $[A,B]$ 中 $C$ 的个数。

我们可以通过容斥原理，用 $[0,B]$ 中 $A$ 的个数减去 $[0,A-1]$ 中的个数。

现在问题转化为，给定若干对 $(B,C)$，求 $[0,B]$ 中 $C$ 的个数。

用桶排序对 $B$ 进行排序，从 $1$ 扫到 $N$，用哈希记录 $pre_B$ 的出现次数，对于每个 $B$ 枚举 $C$ 即可。
### 时间复杂度
对于 $f$ 数组的处理，由性质 1，$f$ 数组最大 $n\log{W}$ 故复杂度也是 $O(n\log{W})$ 的。

对于统计答案，$(A,B,C)$ 最多有 $n\log{W}$ 组，故复杂度也是 $O(n\log{W})$ 的。
### 代码
用 `vector` 存的，常数比较大，追求更高效率可以考虑链式前向星。
```cpp,
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
#define pr pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace __gnu_pbds;
using namespace std;
template<typename T>inline void read(T &x){
    T f=1;char ch=getchar();x=0;
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
    x*=f;
}
template<typename T>inline void write(T x){
    if(x<0){putchar('-');x=-x;}
    if(x<=9){putchar(x^48);return;}
    write(x/10);
    putchar(x%10^48);
}
const int N=209626;
int a[N],pre[N];
cc_hash_table<int,int>h;
vector<pr>f[N],e[N],g[N];
int n,ans=0;
signed main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        pre[i]=pre[i-1]^a[i];
    }
  //预处理f数组
    for(int i=1;i<=n;i++){
        int lst=a[i];
        f[i].push_back(mp(a[i],i));
        for(int j=0;j<f[i-1].size();j++){
            if((a[i]&f[i-1][j].fi)!=lst){
                lst=(a[i]&f[i-1][j].fi);
                f[i].push_back(mp(lst,f[i-1][j].se));
            }
        }
    }
 	//桶排
    for(int i=1;i<=n;i++){
        for(int j=0;j<f[i].size();j++){
            e[f[i][j].se].push_back(mp(f[i][j].fi,i));
        }
    }
  //用哈希统计答案
    for(int i=1;i<=n;i++){
        h[pre[i-1]]++;
        for(int j=0;j<e[i].size();j++){
            ans+=h[pre[e[i][j].se]^e[i][j].fi];
        }
    }
  //去重
    h.clear();
    for(int i=1;i<=n;i++){
        for(int j=0;j<f[i].size()-1;j++){
            g[f[i][j+1].se].push_back(mp(f[i][j].fi,i));
        }
    }
    for(int i=1;i<=n;i++){
        h[pre[i-1]]++;
        for(int j=0;j<g[i].size();j++){
            ans-=h[pre[g[i][j].se]^g[i][j].fi];
        }
    }
    write(ans);putchar('\n');
    return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[P7003 [NEERC2013] Hack Protection](https://www.luogu.com.cn/problem/P7003)。

容易想到前缀异或和，以及按位拆分等操作。

定义符号 $\bigoplus^r_{i=l}$ 表示区间 $[l,r]$ 的异或和，符号 ${\large{\&}}^r_{i=l}$ 区间 $[l,r]$ 中所有数按位与的结果，$a\oplus b$ 表示 $a$ 与 $b$ 做异或运算。

对于一个区间 $\bigoplus^r_{i=l} a_i=\bigoplus^r_{i=1} a_i\oplus\bigoplus^{l-1}_{i=1} a_i$，如果 $\bigoplus^r_{i=l} a_i={\large{\&}}^r_{i=l}$，那么等量代换，得 $\bigoplus^r_{i=1}a_i\oplus\bigoplus^{l-1}_{i=1}a_i={\large{\&}}^r_{i=l}$，$a=b\iff a\oplus b=0$，所以上式可写为 $\bigoplus^r_{i=1}a_i\oplus\bigoplus^{l-1}_{i=1}a_i\oplus {\large{\&}}^r_{i=l}=0$。

考虑拆贡献，对于一个固定的 $l$，有 $\bigoplus^r_{i=1}a_i=\bigoplus^{l-1}_{i=1}a_i\oplus {\large{\&}}^r_{i=l}$，仅需要找到满足条件的 $r$ 的数量即可，如果 $\bigoplus^{l-1}_{i=1}a_i$ 和 ${\large{\&}}^r_{i=l}$ 一定，就可以推出 $\bigoplus^{l-1}_{i=1}a_i$，很容易知道，由于与运算不可逆的性质（就是说一位一旦变为 $0$ 了以后再和任何数按位与都不可能再次变为 $1$ 了），所以在确定了 $l$ 以后，对于不同的 $r$，${\large{\&}}^r_{i=l}$ 只可能最多变化 $31$ 次，考虑把这 $31$ 个位置全部枚举出来，记算有多少 $\bigoplus^r_{i=1}a_i=\bigoplus^{l-1}_{i=1}a_i\oplus {\large{\&}}^r_{i=l}$ 即可。

计算方法可以把所有异或前缀和预处理出来，处理时会出现不方便的情况，可以考虑离线每次询问，存到 vector 里二分一下即可。

时间复杂度为 $O(n\log a_i \log n)$，代码容易。

---

## 作者：Starlight237 (赞：0)

一个使用主席树的实现。

> (**2021集训队作业 P7003 【[NEERC2013]Hack Protection】**)给定一个序列，求多少个区间的按位异或值等于按位与的值。

**Lemma 0** 一个序列的前缀按位与最多有 $O(\log v)$ 种，且每一种值对应的前缀出现的位置都是一个连续段。其中 $v$ 为值域。  
证明：考虑到只有 $\lceil\log_2v\rceil$ 位，而每一位最多改变一次（由 1 改变为 0 之后永远是 0，由 0 不可能改变为 1），因此得证。同理，一个序列的前缀按位或也满足这个结论。

上面的结论用的非常多，曾经某 Ag 学长来我校讲课时就说了雅礼集训中遇到的某道题，也是这个套路，~~由于比本题更裸就不多提及了~~。

我们枚举区间的左端点 $i$，然后 $[i,n]$ 就可以划分为 $O(\log v)$ 个前缀按位与相同的连续段（这里前缀按位与是指从 $i$ 开始而不是从 $1$ 开始的前缀），这一划分可以**多次二分 + ST 表**来完成。设当前找到的前缀按位与相同的连续段为 $[l,r]$，并设该相同值为 $t$（换言之，$\forall j\in[l,r],st.\ a_i\ \text{and}\ a_{i+1}\ \text{and}\ ...\ \text{and}\ a_j=t$），为了使 $[i,j](j\in[l,r])$ 的按位异或等于按位与，令 $s_i$ 表示**整个序列**的前缀异或值，应当有 $s_j\oplus s_{i-1}=t$，也就是 $s_j=s_{i-1}\oplus t(j\in[l,r])$。问题转化为统计一个区间 $s[l..r]$ 内定值 $s_{i-1}\oplus t$ 出现的次数。

直接开个 `INT_MAX` 的大主席树显然会 `MLE`，考虑离散化。需要注意在主席树中查询时要先判断一下 $s_{i-1}\oplus t$ 是否在序列中出现了，如果根本没出现过，应当直接 `continue` 掉，而不是依然求其排名并用主席树查询，否则会多算许多答案。

```cpp
#define ll long long
const int N = 100010;
int n, a[N], st[N][20], lg[N], buc[N];
inline int query(int l, int r) {
	int _lg = lg[r - l + 1];
	return st[l][_lg] & st[r - (1 << _lg) + 1][_lg];
}
int ptr, root[N];
struct Node {
	int siz, ls, rs;
} seg[N << 5];
inline void pushup(int k) {
	seg[k].siz = seg[k << 1].siz + seg[k << 1 | 1].siz;
}
void add(int lst, int&k, int l, int r, int p) {
	k = ++ptr;
	seg[k] = seg[lst];
	if (l == r) {++seg[k].siz; return ;}
	int mid = l + r >> 1;
	p <= mid ? add(seg[lst].ls, seg[k].ls, l, mid, p) : add(seg[lst].rs, seg[k].rs, mid + 1, r, p);
	pushup(k);
}
int qry(int lst, int k, int l, int r, int p) {
	if (l == r) return seg[k].siz - seg[lst].siz;
	int mid = l + r >> 1;
	return p <= mid ? qry(seg[lst].ls, seg[k].ls, l, mid, p) : qry(seg[lst].rs, seg[k].rs, mid + 1, r, p);
}
int main() {
	n = rd();
	for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
	ll ans = 0;
	for (int i = 1; i <= n; ++i) st[i][0] = rd(), a[i] = a[i - 1] ^ st[i][0], buc[i] = a[i];
	for (int j = 1; j <= lg[n]; ++j)
		for (int i = 1; i + (1 << j) - 1 <= n; ++i)
			st[i][j] = st[i][j - 1] & st[i + (1 << j - 1)][j - 1];
	sort(buc + 1, buc + n + 1);
	int tt = unique(buc + 1, buc + n + 1) - buc - 1;
	for (int i = 1; i <= n; ++i) add(root[i - 1], root[i], 0, n, lower_bound(buc + 1, buc + tt + 1, a[i]) - buc);
	for (int i = 1; i <= n; ++i) {
		int l = i, r = i;
		for (; l <= n; l = r + 1) {
			int _l = l, _r = n, mid, tmp = query(i, l);
			while (_l <= _r)
				mid = _l + _r >> 1, query(i, mid) == tmp ? r = mid, _l = mid + 1 : _r = mid - 1;
			int val = lower_bound(buc + 1, buc + tt + 1, tmp ^ a[i - 1]) - buc;
			if (buc[val] != (tmp ^ a[i - 1])) continue;
			ans += qry(root[l - 1], root[r], 0, n, val);
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

