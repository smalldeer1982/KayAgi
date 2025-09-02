# Deletion of Repeats

## 题目描述

Once Bob saw a string. It contained so many different letters, that the letters were marked by numbers, but at the same time each letter could be met in the string at most 10 times. Bob didn't like that string, because it contained repeats: a repeat of length $ x $ is such a substring of length $ 2x $ , that its first half coincides character by character with its second half. Bob started deleting all the repeats from the string. He does it as follows: while it's possible, Bob takes the shortest repeat, if it is not unique, he takes the leftmost one, and deletes its left half and everything that is to the left of this repeat.

You're given the string seen by Bob. Find out, what it will look like after Bob deletes all the repeats in the way described above.

## 样例 #1

### 输入

```
6
1 2 3 1 2 3
```

### 输出

```
3
1 2 3 
```

## 样例 #2

### 输入

```
7
4 5 6 5 6 7 7
```

### 输出

```
1
7 
```

# 题解

## 作者：jdsb (赞：7)

## 题意
给定一个长度为$n$的数列（其实是字符串），其中的每个数字表示一个字母要进行若干次删除操作，每次把字符串中的相邻连续子串形如 $XX$ 删除前一个 $X$ 及其前面的所有字符。

## 分析
我们可以从小到大枚举长度为 $L$ 的子串，然后用哈希加二分来判断相邻的子串是否相同，如果相同，则将前一个子串以及前面的所有部分删除。这个做法时间复杂度为 $O(N^2 log N)$，显然是会超时。我们来考虑另一种操作，每隔 $L$ 设置一个观察点，对相邻的两个观察点，分别以这两个点为起点和终点求一遍最长公共前缀(LCP)与最长公共后缀(LCS)，设前一个观察点的位置为 $x$，如果这最长公共前缀和最长公共后缀加起来大于等于当前的长度 $L$，则说明 $x-LCP+1$ 到 $x-LCP+L+1$ 为我们所要求的前一个 $X$。我就配个图来简单证明一下。
![](https://cdn.luogu.com.cn/upload/image_hosting/otmhh9id.png)

红点为观察点，橙线表示LCP，绿线表示LCS，则可以发现前一段橙线加绿线和后一段橙线加绿线是完全相同的，所以以两条橙线的左端点为起始点的子串只要不超过这个长度也是相同的，而 $lCP+LCS≥L$，所以也就存在两个连续子串的长度是相同的。

根据上面的证明，我们就可以在 $\dfrac{|S|}{L}log L$ 的时间内求出相邻的相同子串，而删除操作因为是这之前的字符都要删除，所以我们就可以用一个指针来指向当前没被删除的位置，然后移动指针即可。因为枚举观察点的时间复杂度为调和级数求和是 $O(NlogN)$，而用哈希求LCP和LCS为 $O(logN)$，所以总的时间复杂度为 $O(NlogN *logN)=O(N{log}^2N)$。

一些细节在代码里有讲。

## 代码
```cpp
#include<bits/stdc++.h>
#define fre(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
using namespace std;
#define ll long long
const int N=1e5+5,p=1e5+7,mod=1e9+7;
int n;
ll Hash[N],bit[N];
int get(int l,int r)
{
	return ((Hash[r]-Hash[l-1]*bit[r-l+1])%mod+mod)%mod;
}
int b[N],a[N];
void init()
{
	bit[0]=1;
	for(int i=1;i<=n;i++)
	{
		Hash[i]=(Hash[i-1]*p+a[i])%mod;
		bit[i]=bit[i-1]*p%mod;
	}
}
//二分加最长公共前缀和最长公共后缀 
int LCP(int x,int y)
{
	int l=0,r=y-x;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(get(x-mid+1,x)==get(y-mid+1,y)) l=mid;
		else r=mid-1;
	}
	return l;
}
int LCS(int x,int y)
{
	int l=0,r=n-y+1;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(get(x,x+mid-1)==get(y,y+mid-1)) l=mid;
		else r=mid-1;
	}
	return l;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init();//初始化处理哈希 
	int first=1;//指向没被删除的字符串位置 
	for(int l=1;l<=n;l++)
	{
		int j=l+first-1,k=2*l+first-1;
		if(k>n) break;
		while(k<=n)
		{
			int lcp=LCP(j,k),lcs=LCS(j,k);
			if(lcp+lcs>l)
				first=max(first,k-lcp+1);
			j+=l;k+=l;
		}
	}
	printf("%d\n",n-first+1);//最后要减去之前被删除的部分 
	for(int i=first;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```


---

## 作者：封禁用户 (赞：5)

本蒟蒻来水一发题解

题目中“字母”的范围是0-1e9，而n<=1e5，因此，先对“字符串”进行离散化

因为每个字母出现的次数不超过10次，所以我们开1e5个vector记录每个“字母”出现的位置，如果有2个字符串是重复的，那么他们的第一个字母一定相同。枚举每个字母，以及重复字符串的两个开始位置，使用**哈希**###### 来判断是否相等。

时间复杂度：枚举字符1e5，枚举两个位置10*10=100,哈希判相等1总共1e7

注意:长度小的会被先删掉，然后就不会跟后面重复

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
const int P=20040911;
int a[N],h[N],p[N],rmp[N],n,cnt,ans;
vector<int>v[N];
vector<pair<int,int>>del;
map<int,int>mp; 
bool same(int x,int y)
{
	int xe=y-1,ye=2*y-x-1;
	if(ye>n)
		return false;
	int hx=h[xe]-h[x-1]*p[y-x],hy=h[ye]-h[y-1]*p[y-x];	
	return hx==hy;		
}
int main()
{
	p[0]=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if(mp.find(x)!=mp.end())
			a[i]=mp[x];
		else
		{
			mp[x]=++cnt;
			a[i]=cnt;
			rmp[cnt]=x;
		}
		p[i]=p[i-1]*P;
		v[a[i]].push_back(i);
		h[i]=h[i-1]*P+a[i];
	} 
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<v[i].size();j++)
			for(int k=j+1;k<v[i].size();k++)
				if(same(v[i][j],v[i][k]))
					del.push_back(make_pair(v[i][k]-v[i][j],v[i][j]));
	sort(del.begin(),del.end());
	for(int i=0;i<del.size();i++)
		if(del[i].second>ans)
			ans=del[i].second+del[i].first-1;
	printf("%d\n",n-ans);
	for(int i=ans+1;i<=n;i++)
		printf("%d ",rmp[a[i]]);
	printf("\n");
	return 0;
}

```

---

## 作者：__stick (赞：2)

# 题意

首先题目非常的复杂，简化一下就是每次找到最靠左且长度最短的可以从中间分成两个相同部分的子串，删除它的前半部分**及以前的部分**问最后会剩下什么。


# 分析

首先，题目一个不太寻常的限制很快就能引起注意，每个字符出现次数不超过 $10$ ，这是个常数，可以忽略的那种，这样也就启示我们枚举每一个出现过的的字符，然后枚举他所有出现过的位置，因为一个子串要想从中间分开，这所分开的两部分的首字母肯定是相同的，这样就让我们大大减小了枚举量，这样最多只会枚举 $O(10n)$ 对子串，这时我们在一个可接受的时间内求出它们后面的位置是否相等即可。

这很容易使用 hash 做到 $O(1)$ 复杂度，假设枚举到位置 $i,j(i<j)$  则我们要判断的就是 $s[i \cdots j-1]$ 是否等于 $s[j\cdots j+j-i]$ ，把这两个子串的hash值提取出来作比较即可。鉴于CF卡 hash 的优良传统，要不就老老实实双模数 hash 要么就另寻他法。其实这玩意也等价于两个后缀 $i,j$ 的 lcp 长度大于等于 $j-i$ ，这玩意可以用后缀数组+rmq 做到 $O(1)$ 询问，于是将所有找到的串拎出来按题目要求排个序，模拟一下删除的操作即可。

# 代码

用的后缀数组，具体如何用后缀数组求 lcp就不证明了，结论是 ：
$$\operatorname{lcp}(s[i\cdots n],s[j\cdots n])=\min_{k=rk[i]+1}^{rk[j]}\{height[k]\}$$

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<ll,ll> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
#define mp make_pair
const int mod=998244353;
const int MAXN=1e5+10;
int id[MAXN];
int cnt[MAXN],x[MAXN],y[MAXN];
int a[MAXN];
int sa[MAXN];
void get_sa(int n,int m)
{
	for(int i=1;i<=n;i++)cnt[x[i]=a[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0; 
		for(int i=n-k+1;i<=n;i++)y[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]>k)y[++p]=sa[i]-k;
		for(int i=1;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[x[i]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i;i--)sa[cnt[x[y[i]]]--]=y[i],y[i]=0;
		swap(x,y);
		p=x[sa[1]]=1;
		for(int i=2;i<=n;i++)x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		if(p==n)break;
		m=p;
	}
}
int rk[MAXN],hi[MAXN];
void get_hi(int n)
{
	for(int i=1;i<=n;i++)rk[sa[i]]=i;
	for(int i=1,k=0;i<=n;i++)
	{
		if(rk[i]==1)continue;
		if(k)k--;int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++;
		hi[rk[i]]=k;
	}
}
int F[MAXN][24];
inline int lcp(int l,int r)
{
	l=rk[l],r=rk[r];
	if(l>r)swap(l,r);
	l++;
	int k=log2(r-l+1);
	return min(F[l][k],F[r-(1<<k)+1][k]);
}
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int n;cin>>n;
	int tt=0;
	unordered_map<int,int>mp(n<<1|1);
	auto lsh=[&](int& x)
	{
		if(mp.count(x))
		{
			x=mp[x];
		}	
		else
		{
			id[++tt]=x;
			mp[x]=tt,x=tt;
		}
	};
	vii v(n+1);
	for(int i=1;i<=n;i++)cin>>a[i],lsh(a[i]),v[a[i]].push_back(i);
	get_sa(n,n);
	get_hi(n);
	for(int i=1;i<=n;i++)F[i][0]=hi[i];
	for(int j=1;1<<j<n;j++)
		for(int i=1;i<=n;i++)
			F[i][j]=min(F[i][j-1],F[i+(1<<(j-1))][j-1]);
	vector<pii>res;
	for(int i=1;i<=tt;i++)
	{
		for(int j=0;j<v[i].size();j++)
			for(int k=j+1;k<v[i].size();k++)
			{
				int x=v[i][j],y=v[i][k];
				if(lcp(x,y)>=y-x) res.push_back({y-x,x});
			}
	}	
	sort(res.begin(),res.end());
	int ans=1;
	for(pii p:res)if(p.Y>=ans)ans=p.X+p.Y;
	cout<<n-ans+1<<'\n';
	for(int i=ans;i<=n;i++)cout<<id[a[i]]<<' ';
	return 0;
}
```


---

## 作者：Hoks (赞：1)

## 前言
duel 到的，也是没想到学 SA 也一段时间了，第一次切用上关键点调和级数是在这。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
题目条件中有**每个字母最多出现10次**，所以可以存下每个字母重复出现的位置枚举做。

复杂度是 $O(nm^2)$ 的，其中 $m$ 为一个字母最多出现的次数。

但其实还有一种 $O(n\log^2 n)$ 的做法，如果使用 SA 的话可以达到 $O(n\log n)$。

因为题目要求是找到两个最短相同的字符串，所以很自然的想到枚举长度 $len$。

接着找直接暴力枚举一遍，hash+二分，复杂度 $O(n^2\log n)$。

接着考虑来优化这个暴力枚举的过程。

考虑类似于 SA 的做法，也就是[优秀的拆分](https://www.luogu.com.cn/problem/P1117)中的做法。

每隔长度 $len$ 设置一个关键点。

对于两个相邻关键点 $x,y$，求一遍 LCS 和 LCP。

也就相当于是以 $x,y$ 为断点一起像左/右扩展。

只需这个扩展的总长度大于 $len$ 即是匹配上了。

实现也就非常简单了，$O(n\log^2n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define int unsigned long long
using namespace std;
const int N=1e5+10,V=1e5,INF=0x3f3f3f3f3f3f3f3f,mod=998244353,p=1145141;
int n,l=1,op[N],h[N],a[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int get(int l,int r){return h[r]-h[l-1]*op[r-l+1];}
inline int LCP(int x,int y)
{
    int l=1,r=y-x,res=0;
    while(l<=r)
        if(get(x-mid+1,x)==get(y-mid+1,y)) res=mid,l=mid+1;
        else r=mid-1;
    return res;
}
inline int LCS(int x,int y)
{
    int l=1,r=n-y+1,res=0;
    while(l<=r)
        if(get(x,x+mid-1)==get(y,y+mid-1)) res=mid,l=mid+1;
        else r=mid-1;
    return res;
}
signed main()
{
    n=read();for(int i=op[0]=1;i<=n;i++) op[i]=op[i-1]*p,h[i]=h[i-1]*p+(a[i]=read());
    for(int len=1,L,R;len<=n;len++)
    {
        L=len+l-1,R=2*len+l-1;if(R>n) break;
        while(R<=n)
        {
            int lcp=LCP(L,R),lcs=LCS(L,R);
            if(lcp+lcs>len) l=max(l,R-lcp+1);
            L+=len;R+=len;
        }
    }
    print(n-l+1);put('\n');
    for(int i=l;i<=n;i++) print(a[i]),put(' ');
    genshin:;flush();return 0;
}
```

---

## 作者：_edge_ (赞：1)

这题目还是挺有意思的。

首先是题目，题目大概就是让你删除从左到右并重复的子串的左半部分，什么意思呢，就是比如对于 `6 1 5 5 1 5 5`，`1 5 5 1 5 5 ` 这边是一个重复的子串，但是题目仅仅要求删除前半段重复的，以及左边的所有部分，也就是说 `6 1 5 5` 都要被删除。

这种题目其实很容易想到方法，考虑到每一个数字出现次数不会超过 $10$，我们可以枚举第一个数字来确定要删除的一个子串，那么我们找到之后可以用 hash 轻松的判断是否重复。

想到这里题目已经解决了一半了，但是还存在很棘手的一个问题，就是说它一开始删的是长度小的，从左到右的，也就是说存在一些情况它重复的可能会交叉，~~(虽然说我没找到小数据反例，但我的的确确是 WA 了)~~。

那么这种情况下考虑前一个区间删除，如果说当前区间左端点在那个区间下，直接不考虑。

注意这边还要排个序，不然不是有序的了。

~~虽然说我自己试了一下，不排序也能 A，我也不知道为什么。~~

另外，这题目 hash 模数好像没有特意地卡。。。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int INF=1e5+5;
const int Mod=1e9+7;
const int base=233;
int n,tot,a[INF],ax[INF],num[INF][15],kk[INF],ba[INF],hash1[INF],tota;
struct _node_data {
        int len,id;
} aa[INF<<4];
bool gethash(int l,int r) {
        // cout<<r<<" "<<l<<"\n";
        int len=r-l; int ll=l,rr=l+len-1;
        int xx=hash1[rr]-hash1[ll-1]*ba[rr-ll+1]%Mod+Mod; xx%=Mod;
        // cout<<rr<<" "<<ll<<"\n";
        ll=r,rr=r+len-1;
        int yy=hash1[rr]-hash1[ll-1]*ba[rr-ll+1]%Mod+Mod; yy%=Mod;
        // cout<<l<<" "<<r<<" "<<xx<<" "<<yy<<"\n";
        return xx==yy;
}
bool cmp(_node_data xx,_node_data yy) {
        if (xx.len!=yy.len) return xx.len<yy.len;
        else return xx.id<yy.id;
}
signed main()
{
        scanf("%lld",&n);
        for (int i=1; i<=n; i++)
                scanf("%lld",&a[i]),ax[i]=a[i];
        sort(ax+1,ax+1+n);
        tot=unique(ax+1,ax+1+n)-ax-1;
        for (int i=1; i<=n; i++) {
                a[i]=lower_bound(ax+1,ax+1+tot,a[i])-ax;
                num[a[i]][++kk[a[i]]]=i;
        }
        ba[0]=1; for (int i=1; i<=n; i++) ba[i]=ba[i-1]*base%Mod;
        for (int i=1; i<=n; i++)
                hash1[i]=(hash1[i-1]*base%Mod+a[i])%Mod;
        for (int i=1; i<=tot; i++)
                for (int j=1; j<=kk[i]; j++)
                        for (int k=j+1; k<=kk[i]; k++)
                                if (gethash(num[i][j],num[i][k]))
                                        aa[++tota].len=num[i][k]-num[i][j]+1,aa[tota].id=num[i][j];
        sort(aa+1,aa+1+tota,cmp);
        int ans=0;
        for (int i=1; i<=tota; i++)
                if (aa[i].id>ans)
                        ans=aa[i].id+aa[i].len-2;
        cout<<n-ans<<"\n";
        for (int i=ans+1; i<=n; i++)
                cout<<ax[a[i]]<<" ";
        return 0;
}

```

如果还有不懂的可以来私聊我哦！！！

---

