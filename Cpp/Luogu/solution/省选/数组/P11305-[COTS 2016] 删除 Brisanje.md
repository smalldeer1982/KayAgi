# [COTS 2016] 删除 Brisanje

## 题目背景


译自 [Izborne Pripreme 2016 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2016/) D1T2。$\texttt{4s,0.5G}$。


为了卡掉理论复杂度较劣的解法，在 Subtask 0 添加了 Hack 数据（#35~#39，感谢 @Hoks 和 @N_z_），同时将时限改为 1.5s。欢迎对数据的加强。


## 题目描述


给定字符串 $s$。

定义 $s(l,r)$ 为 $s$ 第 $l\sim r$ 个字符组成的字符串。

定义 $t(l,r)$ 为 $s$ 删除第 $l\sim r$ 个字符后得到的字符串。

找到最长的区间 $[l,r]$，使得 $s(l,r)$ 在 $t(l,r)$ 中作为子串出现。


## 说明/提示


#### 样例解释

不难注意到 $\texttt{bbcdbcb\underline{bcbad}adda} \to \texttt{bbcd\underline{bcbad}da}$。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le |s| \le 10^5$；
- $s$ 中只有小写字母。


| 子任务编号 | $\vert s\vert \in $ | 得分 |  
| :--: | :--: | :--: | 
| $ 1 $    | $ [1,400] $    |   $ 16 $   |  
| $ 2 $    | $ (400,5000] $   |  $ 24 $   |  
| $ 3 $    | $ (5000,10^5]$ | $ 60 $   |  



## 样例 #1

### 输入

```
abcxyzabc
```

### 输出

```
3```

## 样例 #2

### 输入

```
bbcdbcbbcbadadda```

### 输出

```
5```

# 题解

## 作者：A6n6d6y6 (赞：7)

## 问题描述

[传送门](https://www.luogu.com.cn/problem/P11305)。见原题题目描述。

## 思路

你说得对，但是只用哈希、二分、线段树可以轻松通过。

分为两种情况：

1. $s(l,r)$ 在原串中不重叠地出现了两次；
  
2. $s(l,r)$ 形如 $AB$，如果原串中出现了 $AABB$，那么就可以将两边的 $AB$ 拼接起来。
  

对于第一种情况，二分一个长度 $x$，对于所有哈希值相同的子串，记录**最后一次**出现的**左端点**，判断**其他右端点**是否在它的**左边**，就可以处理不重叠的要求了，用了一个 `std::map`，时间复杂度 $\mathcal{O}(n\log^2n)$。

对于第二种情况，类似于 [\[NOI2016\] 优秀的拆分](https://www.luogu.com.cn/problem/P1117)，先考虑形如 $AA$ 的串。不妨设 $l_i$ 为以 $i$ 为**右端点**最长 $AA$ 串的一半长度，不妨设 $r_i$ 为以 $i$ 为**左端点**最长 $AA$ 串的一半长度，答案即为：

$$
\max\limits_{i=1}^{n-1}l_i+r_{i+1}
$$

好，现在考虑如何描述所有 $AA$ 串，对于长度为 $2i$ 的 $AA$ 串：

如果我们在字符串上每隔 $i$ 设置一个观察点，那么所有 $AA$ 串**必然包含两个观察点**。

**相邻观察点**的 LCP（最长公共前缀） 与 LCS（最长公共后缀） 拼起来的字符串即为经过的两点上的**最长** $AA$ 串。若 LCP 与 LCS 的和大于 $i$，说明它们相交，可以有让**一段区间**多出长度为 $i$ 的选择。例如 $\texttt{ABC(AB)CAB}$，其中括号是**重叠**的部分，那么出现了三个 $AA$ 串：$\texttt{ABCABC},\texttt{BCABCA},\texttt{CABCAB}$。

可以分析，这样的一段区间**不会超过** $n\log n$ 个，如果用哈希求 LCP 和 LCS，时间复杂度是 $\mathcal{O}(n\log^2n)$ 的。

现在只需要对于每个**左端点**和**右端点**，当作一个操作，取一个最大值，有 $n\log n$ 次修改，最后统一查询，可以**离线**下来对于长度 $i$ **排序**，**从小到大**处理，就成了**区间赋值**，用**线段树**处理，时间复杂度也是 $\mathcal{O}(n\log^2n)$ 的。

最后将两种答案**取最大值**，得到最终答案，总时间复杂度 $\mathcal{O}(n\log^2n)$。

综上，我们在 $\mathcal{O}(n\log^2n)$ 的时间复杂度下解决这道缝合问题。

## 细节

**自然溢出**？被卡了。**单哈希**？也被卡了。所以只能写**双模哈希**。

注意多个二分的**最大边界条件**。

## 代码

[AC记录](https://www.luogu.com.cn/record/220313629)。代码轻微压行、卡常。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10,mod1=1e9+7,mod2=1e9+9,base1=19491001,base2=19370707;
struct SegmentTree{
    struct node{int l,r,w;}t[maxn<<2];
    int ls(int u){return u<<1;}
    int rs(int u){return u<<1|1;}
    void pushdown(int u){
        if(!t[u].w)return;
        t[ls(u)].w=t[u].w;
        t[rs(u)].w=t[u].w;
        t[u].w=0;
    }
    void build(int u,int l,int r){
        t[u]={l,r,0};
        if(l==r)return;
        int mid=(l+r)>>1;
        build(ls(u),l,mid);
        build(rs(u),mid+1,r);
    }
    void modify(int u,int l,int r,int w){
        if(r<t[u].l||t[u].r<l)return;
        if(l<=t[u].l&&t[u].r<=r){t[u].w=w;return;}
        pushdown(u);
        modify(ls(u),l,r,w);
        modify(rs(u),l,r,w);
    }
    int query(int u,int x){
        if(x<t[u].l||t[u].r<x)return 0;
        if(x<=t[u].l&&t[u].r<=x)return t[u].w;
        pushdown(u);
        return query(ls(u),x)^query(rs(u),x);
    }
}Tl,Tr;//区间赋值线段树
struct num{
    int h1,h2;num(int a=0,int b=0){h1=a;h2=b;}
    friend bool operator<(const num &a,const num &b){
        if(a.h1!=b.h1)return a.h1<b.h1;
        return a.h2<b.h2;
    }
    friend bool operator ==(const num &a,const num &b){return a.h1==b.h1&&a.h2==b.h2;}
    friend num operator + (const num &a,const num& b){return num((a.h1+b.h1)%mod1,(a.h2+b.h2)%mod2);}
    friend num operator - (const num &a,const num& b){return num((a.h1-b.h1+mod1)%mod1,(a.h2-b.h2+mod2)%mod2);}
    friend num operator * (const num &a,const num& b){return num((a.h1*b.h1)%mod1,(a.h2*b.h2)%mod2);}
}h[maxn],p[maxn],base(base1,base2);//双哈希结构体
int n;
num get(int l,int r){return h[r]-h[l-1]*p[r-l+1];}
int lcp(int x,int y){
    int l=0,r=x,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(get(x-mid+1,x)==get(y-mid+1,y))l=mid+1,ans=mid;
        else r=mid-1;
    }
    return ans;
}//哈希求LCP
int lcs(int x,int y){
    int l=0,r=n-y+1,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(get(x,x+mid-1)==get(y,y+mid-1))l=mid+1,ans=mid;
        else r=mid-1;
    }
    return ans;
}//哈希求LCS
struct node{int l,r,w;};vector<node>Vr,Vl;
bool cmp(const node& a,const node& b){
    if(a.w!=b.w)return a.w<b.w;
    if(a.l!=b.l)return a.l<b.l;
    return a.r<b.r;
}//排序线段
map<num,int>st;
bool check(int mid){
    st.clear();
    for(int i=n-mid+1;i>=1;i--){
        const num&& h=get(i,i+mid-1);
        if(!st.count(h))st[h]=i;
        else if(st[h]>=i+mid)return 1;
    }
    return 0;
}//第一种情况
signed main(){
    // freopen("str.in","r",stdin);
    // freopen("str.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    string s;cin>>s;s=' '+s;
    n=s.size()-1;p[0]={1,1};
    for(int i=1;i<=n;i++){
        h[i]=h[i-1]*base+num{s[i],s[i]};
        p[i]=p[i-1]*base;
    }//哈希初始化
    Vl.clear();Vr.clear();
    for(int i=1;i<=n;i++){
        for(int j=i,k=i+i;k<=n;j+=i,k+=i){
            int l=max(k-lcp(j,k)+i,k),r=min(k+lcs(j,k)-1,k+i-1);
            if(l>r)continue;
            Vl.push_back({l,r,i});
            Vr.push_back({l-i*2+1,r-i*2+1,i});
        }
    }//求线段
    sort(Vl.begin(),Vl.end(),cmp);
    sort(Vr.begin(),Vr.end(),cmp);
    Tl.build(1,1,n);Tr.build(1,1,n);
    for(auto [l,r,w]:Vl)Tl.modify(1,l,r,w);
    for(auto [l,r,w]:Vr)Tr.modify(1,l,r,w);//离线赋值
    int l=0,r=n/2,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))l=mid+1,ans=mid;
        else r=mid-1;
    }//第一种情况
    for(int i=1;i<n;i++)
        ans=max(ans,Tl.query(1,i)+Tr.query(1,i+1));//第二种情况
    cout<<ans;
    return 0;
}
```

---

## 作者：Twlight！ (赞：5)

注：本文展示的是 $O(n^2)$ 的暴力哈希做法，在提交本文（2024/11/26）前，暂无能卡掉我们代码的数据。如果您有好的 Hack 思路，请联系 @andychen_2012。

## 前情提要
[![image.png](https://i.postimg.cc/Dy7Kp4Fx/image.png)](https://www.luogu.com.cn/discuss/1004856)

见上图或[此贴](https://www.luogu.com.cn/discuss/1004856)。

在我原哈希做法被卡后，@andychen_2012 只说了一句话：$O(n^2)$ 连 $10^5$ 都过不去，菜。

于是他以惊人的速度，结合我们想出来的 Trick 通过了本题目前 [2024/11/25 13:30] 所有的 Hack，见[提交记录](https://www.luogu.com.cn/record/191025558)。

由于暴力哈希的天然优势，本篇题解将专门介绍 $O(n^2)$ 乱搞做法和 Trick。

## 思路
设最长的子串为 $\text{A}$，显然原问题可以拆成两种情况：
1. 子串以 ```..A..A..``` 的形式出现在原串中。
2. 子串以 ```...A...``` 的形式出现在原串中，删除 $\text{A}$ 后，拼起来的字符串才能再找到 $\text{A}$。

不妨以另一种角度看情况 2：拼起来能得到 $\text{A}$，说明新的 $\text{A}$ 在原串中被老的 $\text{A}$ 拆成两段了，比如 ```abc abcdefg defg```，```abcdefg``` 被自己拆成了 ```abc、defg```。我们想要找到最长的 $\text{A}$ 也很简单，只需要找最长的形如 $\text{SSTT}$ 的子串即可。

第一问可以直接二分枚举长度为 $\text{mid}$ 的串，把它们哈希值丢到一个 $\text{map}$ 里，直接扫一遍 $\text{map}$ 判断是否存在不相交的串。

第二问可以直接暴力枚举，对于每个位置 $i$ 找出他往前最长的 $\text{SS}$、往后最长的 $\text{TT}$，如果你担心卡常，长度可从大到小枚举进行剪枝，统计答案可参考廊桥分配。

最后对两个问的答案求个 $\max$ 即可。

时间复杂度：$O(n \log n + n^2)$，经过一天的测试，我们暂时找不到能 hack 掉我们做法的数据（已知最慢点 624ms），当然这是在洛谷上测的。

下面分享几种在代码不断被 Hack 时，我们做出的优化技巧：
- Trick1: 使用大模数哈希，从大到小枚举答案。
- Trick2: 使用自然溢出哈希 && 大模数哈希以达到断路。
- Trick3: 给每个字母设置一个权值，哈希查询时直接做减法，先判断两个区间内每种字符数量是否相同；随机哈希 && 自然溢出哈希 && 大模数哈希的超级断路。
- Trick4: 记录每种字母的位置，查询时直接从最远的与当前字母相同的位置开始遍历，这样每次遍历都保证了他们中第一位相同，套上超级断路即可。
- Trick5: 在 Trick4 的基础上，添加剪枝，判断当前位置是否一定不能造成贡献。

不难发现，我们只需要不断增加必要条件的判定，Hack 就会越来越难造。

## 参考代码
每种 Trick 代码见 [云剪贴板](https://www.luogu.com.cn/paste/v0n0pbkr)。

「魔法和奇迹，都是存在的。」

---

## 作者：Reunite (赞：4)

无聊缝合题。

我们称删去的 $s$ 在剩下的串中的出现为 $s'$。 分两种情况讨论，$s'$ 跨过断点，$s'$ 未跨过断点，因为是取 $\max$，所以算重无所谓。

先考虑简单的未跨过断点的情况，此时 $s'$ 一定完整出现在断点前或断点后，且具有单调性，直接二分长度 $len$，前后缀双哈希判断即可，复杂度 $O(n\log n)$。

再考虑跨过断点的情况，不难发现我们一定可以划分为 $aabb$ 的形式，然后就转化为了 [P1117 [NOI2016] 优秀的拆分 ](https://www.luogu.com.cn/problem/P1117)，稍微修改一下，把统计答案的差分改到线段树上区间取 $\max$，维护前端点和后端点两个线段树即可。最后拍下来所有的值，只需要枚举 $aabb$ 的 $ab$ 分割点再左右相加即可，复杂度 $O(n\ln n\log n)$。

写下上面那段话的人是啥被，注意到我们仅需要支持区间取 $\max$，且值域为 $O(n)$，仅需要把这 $n\ln n$ 条带权线段插到 vector 里面，按照权值从大到小扫，每次仅需赋值给未被赋值的点即可，用并查集维护即可做到 $O(\alpha n\ln n)$。

但是很烦，这题卡单哈希，map 常数极大，还要写一个哈希表，复杂度 $O(\alpha n\ln n)$，目前最优解。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int n;
char c[100005];

namespace CaseA{
	#define mod 998244353
	#define md 1000000009
	#define M 999983
	#define ll long long

	int b1[100005];
	int b2[100005];
	int hs1[100005];
	int hs2[100005];

	struct Hash{
		int cnt;
		int h[999982];
		struct node{ll x;int v,nxt;}e[200005];
		inline int Find(ll x){
			for(int i=h[x%M];i;i=e[i].nxt)
				if(e[i].x==x) return e[i].v;
			return 0;
		}
		inline void add(ll x,int v){e[++cnt]={x,v,h[x%M]},h[x%M]=cnt;return ;}
		inline void clear(){
			for(int i=1;i<=cnt;i++) h[e[i].x%M]=0;
			cnt=0;
			return ;
		}
	}L,R;

	inline int get1(int l,int r){return (hs1[r]-1ll*hs1[l-1]*b1[r-l+1]%mod+mod)%mod;}
	inline int get2(int l,int r){return (hs2[r]-1ll*hs2[l-1]*b2[r-l+1]%md+md)%md;}
	inline ll get(int l,int r){return 1ll*get1(l,r)*M+get2(l,r);}
	
	inline bool check(int len){
		L.clear(),R.clear();
		for(int i=n-len+1;i>=1;i--) if(!R.Find(get(i,i+len-1))) R.add(get(i,i+len-1),i);
		for(int i=len;i<=n;i++) if(!L.Find(get(i-len+1,i))) L.add(get(i-len+1,i),i);
		for(int i=1;i<=n-len+1;i++){
			ll hs=get(i,i+len-1);
			if(L.Find(hs)>=i&&R.Find(hs)<=i+len-1) continue;
			return 1;
		}
		return 0;
	}

	inline int solve(){
		b1[0]=b2[0]=1;
		for(int i=1;i<=n;i++) b1[i]=1ll*b1[i-1]*137%mod,hs1[i]=(1ll*hs1[i-1]*137+c[i])%mod;
		for(int i=1;i<=n;i++) b2[i]=1ll*b2[i-1]*2333%md,hs2[i]=(1ll*hs2[i-1]*2333+c[i])%md;
		int l=1,r=n/2,mid,ans=0;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		return ans;
	}
}

namespace CaseB{

	char s[100005];
	char t[100005];
	int lg[100005];
	int sa1[100005];
	int rk1[100005];
	int ht1[100005];
	int sa2[100005];
	int rk2[100005];
	int ht2[100005];
	int mn1[18][100005];
	int mn2[18][100005];

	inline void SA(char s[],int sa[]){
		int m=122;
		int x[100005]={0};
		int y[100005]={0};
		int c[100005]={0};
		for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
		for(int i=2;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i;i--) sa[c[x[i]]--]=i;
		for(int k=1;k<=n;k*=2){
			int cnt=0;
			for(int i=n-k+1;i<=n;i++) y[++cnt]=i;
			for(int i=1;i<=n;i++) if(sa[i]>k) y[++cnt]=sa[i]-k;
			for(int i=1;i<=m;i++) c[i]=0;
			for(int i=1;i<=n;i++) c[x[i]]++;
			for(int i=2;i<=m;i++) c[i]+=c[i-1];
			for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
			swap(x,y);
			x[sa[1]]=cnt=1;
			for(int i=2;i<=n;i++)
				x[sa[i]]=cnt+=!(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]);
			if(cnt==n) break;
			m=cnt;
		}
		return ;
	}
	
	inline void initlcp(char s[],int sa[],int rk[],int ht[]){
		int k=0;
		for(int i=1;i<=n;i++) rk[sa[i]]=i;
		for(int i=1;i<=n;i++){
			if(rk[i]==1) continue;
			if(k) k--;
			int j=sa[rk[i]-1];
			while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]) k++;
			ht[rk[i]]=k;
		}
		return ;
	}
	
	inline int get1(int l,int r){
		int len=lg[r-l+1];
		return min(mn1[len][l],mn1[len][r-(1<<len)+1]);
	}
	
	inline int get2(int l,int r){
		int len=lg[r-l+1];
		return min(mn2[len][l],mn2[len][r-(1<<len)+1]);
	}

	struct node{
		int a[100005];
		int fa[100005];
		int vl[100005];
		int sz[100005];
		vector <pair <int,int> > g[100005];
		inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
		inline void work(){
			for(int i=1;i<=n+1;i++) fa[i]=vl[i]=i,sz[i]=1;
			for(int i=n;i>=1;i--){
				int s=g[i].size()-1;
				for(int j=0;j<=s;j++){
					int u=Find(g[i][j].first),l=vl[u],r=g[i][j].second;
					while(l<=r){
						a[l]=i;
						int v=Find(l+1),rr=vl[v];
						if(sz[v]>sz[l]) fa[u]=v,sz[v]+=sz[l];
						else fa[v]=u,sz[u]+=sz[v],vl[u]=rr;
						u=Find(l),l=vl[u];
					}
				}
			}
			return ;
		}
	}t1,t2;

	inline int solve(){
		memcpy(s,c,sizeof(c));
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++) t[i]=s[n-i+1];
		SA(s,sa1);
		SA(t,sa2);
		initlcp(s,sa1,rk1,ht1);
		initlcp(t,sa2,rk2,ht2);
		for(int i=1;i<=n;i++) mn1[0][i]=ht1[i],mn2[0][i]=ht2[i];
		for(int j=1;j<=lg[n];j++){
			for(int i=1;i+(1<<j)-1<=n;i++)
				mn1[j][i]=min(mn1[j-1][i],mn1[j-1][i+(1<<(j-1))]),
				mn2[j][i]=min(mn2[j-1][i],mn2[j-1][i+(1<<(j-1))]);
		}
		for(int len=1;len<=n;len++){
			for(int i=len;i<=n;i+=len){
				if(i+len>n) continue;
				int j=i+len;
				int s1=get1(min(rk1[i],rk1[j])+1,max(rk1[i],rk1[j]));
				int s2=get2(min(rk2[n-i+1],rk2[n-j+1])+1,max(rk2[n-i+1],rk2[n-j+1]));
				if(s1+s2<=len) continue;
				int l=max(j-s2,i);
				int r=min(i+s1-1,j-1);
				t1.g[len].push_back({l-len+1,r-len+1});
				t2.g[len].push_back({l+len,r+len});
			}
		}
		t1.work(),t2.work();
		int mx=0;
		for(int i=1;i<n;i++) mx=max(mx,t2.a[i]+t1.a[i+1]);

		return mx;
	}
}

signed main(){
	scanf("%s",c+1);
	n=strlen(c+1);
	printf("%d\n",max(CaseA::solve(),CaseB::solve()));

	return 0;
}
```

---

## 作者：L_zaa_L (赞：1)

给出一种比较好想的 SA 算法。

就是我们发现满足条件的答案，要么是两个不相交但是字符串相同的两个区间，要么是删掉一个区间后两边合并出现了一个新的串和删掉的那个串相等。

对于前面那一个我们是非常容易进行维护的，我们可以二分，如果一个答案为 $i$，那么 $i-1$ 也一定是合法的，然后用 hash 加 map 判断这个长度有没有重复出现过，注意要处理一下两个串不能相交。

对于第二种情况，我们需要考虑一下。我们发现只有 $AABB$ 这种才合法，那么这就是一个经典的问题，我们可以仿照[P1117 [NOI2016] 优秀的拆分](https://www.luogu.com.cn/problem/P1117)的方法，先把这个东西拆成 $AA$，我们可以枚举这个区间的长度 $x$，然后从 $x$ 开始每 $x$ 设立一个关键点，然后可以得知 $AA$（$A$ 的长度是我们枚举的那个长度 $x$）中两个 $A$ 都一定有一个关键点，于是我们可以通过看关键点 $i,i+x$ 来看有哪些合法的位置，往前找两个相邻的关键点有最长的相同的位置 $lcp$，往后找两个关键点最长往后相同的位置 $lcs$，然后我们就可以判断有哪些长度为 $x$ 的区间符合条件了，就是 $[i-lcs+1,i+lcp-x]$ 以这些为开头的长度为 $2*x$ 的串都是 $AA$ 形式的串，相似的，我们也可以得出 $[i-lcp+x\times 2,i+lcp-1+2\times 2]$ 结尾的是 $AA$ 串，所以我们就可以用线段树进行维护以某个位置为开头或结尾的 $AA$ 串最长的长度，然后就可以记录答案了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e6+5;
const int base=29,Mod=1e9+7;
const int base1=37,Mod1=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
inline void Add(int &x,int y){(x=x+y+Mod)%=Mod;}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n%10+'0');
}
int n,m,t,lg[N];
struct SuffixArray {
	char s[N];
	int rak[N],tp[N],tag[N],sa[N];
	int height[N];
	int minsum[N][21];
	inline int log(int pp){
		int xx=0;
		while(pp!=0){
			pp>>=1;
			xx++;
		} 
		return xx;
	}
	inline void init(){
		memset(minsum,0,sizeof(minsum));
		memset(tp,0,sizeof(tp));
		memset(rak,0,sizeof(rak));
		memset(tag,0,sizeof(tag));
		memset(sa,0,sizeof(sa));
		memset(height,0,sizeof(height));
	}
	inline void Radix_sort(){
		for(register int i=1;i<=m;++i) tag[i]=0;
		for(register int i=1;i<=n;++i) ++tag[rak[i]];
		for(register int i=1;i<=m;++i) tag[i]+=tag[i-1];
		for(register int i=n;i>=1;--i) sa[tag[rak[tp[i]]]--]=tp[i],tp[i]=0;
	}
	inline void SA(){
		m=150;int p=0;
	    For(i,0,m) tag[i]=0;
		For(i,1,n) rak[i]=(int)s[i];
		For(i,1,n)++tag[rak[i]];
		For(i,1,m) tag[i]+=tag[i-1];
		Rof(i,n,1) sa[tag[rak[i]]--]=i;
		for(int k=1;k<=n;k<<=1){
			p=0;
	        For(i,0,m) tag[i]=tp[i]=0;
			For(i,n-k+1,n) tp[++p]=i;
			For(i,1,n)if(sa[i]>k)tp[++p]=sa[i]-k;
			For(i,1,m) tag[i]=0;
			For(i,1,n)tag[rak[i]]++;
			For(i,1,m) tag[i]+=tag[i-1];
			Rof(i,n,1) sa[tag[rak[tp[i]]]--]=tp[i],tp[i]=0;
			swap(rak,tp);
			rak[sa[1]]=1;
			p=1;
			For(i,2,n)
				rak[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+k]==tp[sa[i]+k])?p:++p;
			m=p;
		}
	}
	inline void GetHeight(){
		int k=0;
	    For(i,1,n){
	        if(k) k--;
	        while(s[i+k]==s[sa[rak[i]-1]+k]) ++k;
	        height[rak[i]]=k;
	    }
	}
	inline void RMQ(int num){ 
		For(i,1,n) minsum[i][0]=height[i]; 
	    For(j,1,19)
	        For(i,1,num-(1<<j)+1){ 
                minsum[i][j]=min(minsum[i][j-1], minsum[i+(1<<(j-1))][j-1]);
            }
	}
    inline int rmq(int l,int r){
        int x=rak[l],y=rak[r];
		if(x>y) swap(x,y);x++;
		int k=lg[y-x+1];
		return min(minsum[x][k],minsum[y-(1<<k)+1][k]);
    }    
}A,B;
struct Segment_Tree{
int tr[N],lz[N];
inline void down(int x,int k){tr[x]=max(tr[x],k),lz[x]=max(lz[x],k);}
inline void pushdown(int x){
	if(!lz[x]) return;
	down(ls(x),lz[x]);down(rs(x),lz[x]);
	return;
}
void updata(int x,int l,int r,int L,int R,int k){
	if(L<=l&&r<=R){down(x,k);return ;}
	pushdown(x);int mid=(l+r)>>1;
	if(L<=mid) updata(ls(x),l,mid,L,R,k);
	if(R>mid) updata(rs(x),mid+1,r,L,R,k);
}
int qry(int x,int l,int r,int p){
	if(l==r)return tr[x];
	pushdown(x);int mid=(l+r)>>1;
	if(p<=mid) return qry(ls(x),l,mid,p);
	return qry(rs(x),mid+1,r,p);
}
}t1,t2;
inline void solve(){
	For(i,1,n){
		for(int j=i;j+i<=n;j+=i){
			int lcp=A.rmq(j,j+i),lcs=B.rmq(n-j+1,n-j-i+1);
			lcs=min(lcs,i);lcp=min(lcp,i); 
			int len=lcp+lcs-i;
			if(lcp+lcs-1>=i){
				t2.updata(1,1,2*n,j-lcs+1,j-lcs+len,i);
				t1.updata(1,1,2*n,j-lcs+(i<<1),j-lcs+(i<<1)+len-1,i);

			}
		}
	}
}
int hsh[N],mi[N],hsh1[N],mi1[N];
unordered_map<int,bool>mp,mp1;
inline int gethsh(int l,int r){
	return (hsh[r]-hsh[l-1]*mi[r-l+1]%Mod+Mod)%Mod;
}
inline int gethsh1(int l,int r){
	return (hsh1[r]-hsh1[l-1]*mi1[r-l+1]%Mod1+Mod1)%Mod1;
}
inline bool check(int x){mp.clear();mp1.clear();
	For(i,x,n){
		if(i-2*x+1>0){
			mp[gethsh(i-2*x+1,i-x)]=1;
			mp1[gethsh1(i-2*x+1,i-x)]=1;
		}
		int f=gethsh(i-x+1,i),f1=gethsh1(i-x+1,i);
		if(mp[f]==1&&mp1[f1]==1){
			return 1;
		}
	}
	return 0;
}
char ss[N];
signed main(){
//	freopen("brisanje.in.3a","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	lg[0]=-1;mi[0]=1;mi1[0]=1;
	For(i,1,N-5) lg[i]=lg[i>>1]+1;
	For(i,1,N-5)mi[i]=mi[i-1]*base%Mod;
	For(i,1,N-5)mi1[i]=mi1[i-1]*base1%Mod1;
	scanf("%s",ss+1);
	n=strlen(ss+1);
	For(i,1,n) hsh[i]=(hsh[i-1]*base+ss[i]-'a'+1)%Mod;
	For(i,1,n) hsh1[i]=(hsh1[i-1]*base1+ss[i]-'a'+1)%Mod1;
	memcpy(A.s,ss,sizeof(ss));
	reverse(ss+1,ss+n+1);
	memcpy(B.s,ss,sizeof(ss));
	A.SA();A.GetHeight();A.RMQ(n);
	B.SA();B.GetHeight();B.RMQ(n);
	solve(); 
	int ans=0;
	For(i,1,n-1){
		ans=max(ans,t1.qry(1,1,2*n,i)+t2.qry(1,1,2*n,i+1));
	}
	int l=ans+1,r=n;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			ans=max(ans,mid);
			l=mid+1;
		}else r=mid-1;
	}
	printf("%lld\n",ans);
	
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}

```

---

## 作者：262620zzj (赞：0)

# 思路

超级二合一题。思维难度很低。

分类讨论 $t(l,r)$ 在原串中的出现。

第一种情况，原来 $s$ 中只含有一个 $t$，删除了之后左右两段拼成了一个 $t$。那么相当于 $t$ 是形如 `AABB` 串的中间的 `AB`，要寻找最长的 `AABB` 串，这就纯和优秀的拆分一样了。计算 $f_i,g_i$ 表示以 $i$ 结尾/开头，最长的形如 `AA` 的串，答案就是 $\max f_i+g_{i+1}$。计算时枚举一个 $len$ 表示 `AA` 的一个 `A` 的长度，然后我们把 $len,2\times len,3\times len \dots$ 这些位置设为关键点位置。这样每个长为 $2\times len$ 的 `AA` 串必然恰好包含两个关键位置。然后每两个关键点之间用 SA 计算两侧最长扩展的距离。这样我们有 $n\log n$ 个区间赋值操作。这里方法超级多，说一下我的。我们再弄个 multiset 维护，一个区间操作拆成在 $L$ 加入一个 $len$，在 $R+1$ 删除一个 $len$，更新完之后查询最大值作为这个位置的 $f/g$ 即可。复杂度 $O(n\log^2 n)$。

否则相当于查询 $s$ 中出现多次的字符串的长度最大值，又是个板子。跟洛谷上的 SAM 板子是雷同的问题。SAM $O(n)$ 可以直接做完。但是由于我想写个哈希练练手，于是想了个哈希做法。二分答案后，每次把所有长度为 $len$ 的子串插入一个 set，里面存 pair，一维哈希值，一维是串的出现位置。查询是否有相同且位置相差大于等于 $len$ 的串即可。复杂度 $O(n\log^2 n)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e5+5;
typedef long long ll;
int n;
string s;
namespace type1{
    constexpr ll base=20081023,MOD1=1e9+7,MOD2=1e9+9;
    struct num{
        ll val1,val2;
        inline num(ll a=0,ll b=0){val1=a,val2=b;}
        inline bool operator < (const num &b)const{
            if(val1!=b.val1)return val1<b.val1;
            else return val2<b.val2;
        }
    }h[N],pw[N];
    inline num operator + (num a,num b){return num((a.val1+b.val1)%MOD1,(a.val2+b.val2)%MOD2);}
    inline num operator - (num a,num b){return num((a.val1-b.val1+MOD1)%MOD1,(a.val2-b.val2+MOD2)%MOD2);}
    inline num operator * (num a,num b){return num((a.val1*b.val1)%MOD1,(a.val2*b.val2)%MOD2);}
    set<pair<num,int> > ss;
    inline bool check(int mid){
        ss.clear();
        for(int i=n-mid+1;i>=1;i--){
            num Hash=h[i+mid-1]-h[i-1]*pw[mid];
            auto it=ss.upper_bound({Hash,i});
            if(it!=ss.end()&&it->first.val1==Hash.val1&&it->first.val2==Hash.val2&&it->second>=i+mid)return 1;
            ss.insert({Hash,i});
        }
        return 0;
    }
    inline ll calc(){
        pw[0]=num(1,1);
        num unit(base,base);
        for(int i=1;i<=n;i++)pw[i]=pw[i-1]*unit;
        for(int i=1;i<=n;i++)h[i]=(h[i-1]*unit)+num(s[i],s[i]);
        int l=0,r=n/2,mid,ans=0;
        while(l<=r){
            mid=l+r>>1;
            if(check(mid))ans=mid,l=mid+1;
            else r=mid-1;
        }
        return ans;
    }
}
namespace type2{
    struct SA{
        int sa[N],rk[N],sa2[N],rk2[N],h[N],buc[N],lg2[N],st[20][N];
        inline void figure(string s){
            memset(buc,0,sizeof(buc));
            int V=127;
            for(int i=1;i<=n;i++)buc[rk2[i]=s[i]]++;
            for(int i=1;i<=V;i++)buc[i]+=buc[i-1];
            for(int i=n;i>=1;i--)sa[buc[rk2[i]]--]=i;
            V=0;
            for(int i=1;i<=n;i++){
                if(rk2[sa[i]]!=rk2[sa[i-1]])V++;
                rk[sa[i]]=V;
            }
            for(int h=1;h<n;h<<=1){
                int tmp=0;
                for(int i=n-h+1;i<=n;i++)sa2[++tmp]=i;
                for(int i=1;i<=n;i++)if(sa[i]-h>0)sa2[++tmp]=sa[i]-h;
                fill(buc,buc+V+3,0);
                for(int i=1;i<=n;i++)buc[rk[i]]++;
                for(int i=1;i<=V;i++)buc[i]+=buc[i-1];
                for(int i=n;i>=1;i--)sa[buc[rk[sa2[i]]]--]=sa2[i];
                memcpy(rk2,rk,(n+3)*sizeof(int));
                V=0;
                for(int i=1;i<=n;i++){
                    if(rk2[sa[i]]!=rk2[sa[i-1]]||rk2[sa[i]+h]!=rk2[sa[i-1]+h])V++;
                    rk[sa[i]]=V;
                }
                if(V==n)break;
            }
            h[1]=0;
            int tmp=0;
            for(int i=1;i<=n;i++){
                if(rk[i]==1)continue;
                if(tmp>0)tmp--;
                while(i+tmp<=n&&sa[rk[i]-1]+tmp<=n&&s[i+tmp]==s[sa[rk[i]-1]+tmp])tmp++;
                h[rk[i]]=tmp;
            }
            lg2[0]=-1;
            for(int i=1;i<=n;i++)lg2[i]=lg2[i>>1]+1;
            for(int i=1;i<=n;i++)st[0][i]=h[i];
            for(int p=1;p<=19;p++)
                for(int i=1;i+(1<<p)-1<=n;i++)
                    st[p][i]=min(st[p-1][i],st[p-1][i+(1<<p-1)]);
        }
        inline int lcp(int x,int y){
            if(x==y)return n-x+1;
            int l=rk[x],r=rk[y];
            if(l>r)swap(l,r);
            l++;
            int p=lg2[r-l+1];
            return min(st[p][l],st[p][r-(1<<p)+1]);
        }
    }pre,suf;
    ll f[N],g[N];
    multiset<int> ss;
    typedef pair<int,int> pii;
    #define fi first
    #define se second
    vector<pii> opf[N],opg[N];
    inline ll calc(){
        pre.figure(s);
        for(int i=1;i<=n/2;i++)swap(s[i],s[n-i+1]);
        suf.figure(s);
        for(int len=1;len<=n/2;len++){
            for(int i=len;i+len<=n;i+=len){
                int j=i+len;
                int s1=suf.lcp(n-i+1,n-j+1),s2=pre.lcp(i,j);
                if(s1+s2-1>=len){
                    int L=i-s1+1,R=j+s2-2*len;
                    L=max(L,i-len+1),R=min(R,i);
                    if(L<=R)opg[L].push_back({len,1}),opg[R+1].push_back({len,-1});
                    L=i-s1+2*len,R=j+s2-1;
                    L=max(L,j),R=min(R,j+len-1);
                    if(L<=R)opf[L].push_back({len,1}),opf[R+1].push_back({len,-1});
                }
            }
        }
        ss.insert(0);
        for(int i=1;i<=n;i++){
            for(pii pr:opf[i]){
                if(pr.se==1)ss.insert(pr.fi);
                else{
                    auto iter=ss.find(pr.fi);
                    ss.erase(iter);
                }
            }
            f[i]=*prev(ss.end());
        }
        ss.clear();
        ss.insert(0);
        for(int i=1;i<=n;i++){
            for(pii pr:opg[i]){
                if(pr.se==1)ss.insert(pr.fi);
                else{
                    auto iter=ss.find(pr.fi);
                    ss.erase(iter);
                }
            }
            g[i]=*prev(ss.end());
        }
        ll ans=0;
        for(int i=1;i<n;i++)ans=max(ans,f[i]+g[i+1]);
        return ans;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>s;
    n=s.size();
    s="$"+s;
    ll ans1=type1::calc(),ans2=type2::calc();
    cout<<max(ans1,ans2);
    return 0;
}
```

---

## 作者：LEE114514 (赞：0)

## 思路

这里，我们提供一个乱搞解法。

答案 $T$ 只可能由两种情况产生：

- $S$ 中 $T$ 不交的出现两次。
- $S$ 形如 $C+A+A+B+B+D$，且 $T=A+B$，其中 $+$ 表示字符串拼接，且 $A,B$ 不可为空（为空了会被上一种情况统计到）。

对于第一种情况，我们二分答案长度 $L$，检查是否有某个串不交的出现过至少两次。具体的，维护每个长度为 $L$ 的子串哈希值第一次出现的位置。当后面再次遇到这个哈希值时，检查它与第一次出现是否有交。

对于第二种情况，我们暴力处理对于每个点 $i$，其开始或结束的最长 $A+A$ 串长度。具体的，我们暴力收缩边界，直至满足 $A+A$ 的性质，最后一次 $O(n)$ 扫描计算最大答案。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int maxn=1e5+5;
int n;
ull hs[maxn],base[maxn];
char str[maxn];
int res;
int L,R,MID;
inline ull gethash(int l,int r){
	return hs[r]-1ll*hs[l-1]*base[r-l+1];
}
bool check(int x){
	map<ull,int> mp;
	for(int i=MID;i<=n;++i){
		if(mp.count(gethash(i-MID+1,i))){
			if(mp[gethash(i-MID+1,i)]<i-MID+1) return 1;
		}else mp[gethash(i-MID+1,i)]=i;
	}
	return 0;
}
int pre[maxn],suf[maxn];
int main(){
	base[0]=1;
	for(int i=1;i<=100000;++i) base[i]=base[i-1]*13331ull;
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;++i) hs[i]=hs[i-1]*13331ull+str[i];	
	L=0,R=n;
	while(L<R){
		MID=(L+R+1)>>1;
		if(check(MID)) L=MID;
		else R=MID-1;
	}
	res=L;
	for(int i=1;i<=n;++i){
		pre[i]=(n+1-i)>>1;
		suf[i]=(i+1)>>1;
		if(n>10000){//乱搞：期望答案不会很大
			pre[i]>>=1;
			suf[i]>>=1;
		}
		while(gethash(i,i+pre[i]-1)!=gethash(i+pre[i],i+pre[i]+pre[i]-1)) --pre[i];
		while(gethash(i-suf[i]+1,i)!=gethash(i-suf[i]-suf[i]+1,i-suf[i])) --suf[i];
	}
	for(int i=1;i<=n;++i) res=max(res,pre[i+1]+suf[i]);
	printf("%d",res);
}
```

---

## 作者：251Sec (赞：0)

口胡题解。

按照内部串在外部串里的出现位置，在原串里是否跨越 $[l,r]$ 分类讨论。

如果不跨越，就是找最长的满足不交地出现了两次的子串。直接 SAM 上找到第一个和最后一个 endpos。

如果跨越，对每个位置 $i$ 求出以它结尾的最长平方串 $f_i$ 和以它开头的最长平方串 $g_i$。那么答案为 $\max \{f_i+g_{i+1}\}$。求这个东西是简单的，直接优秀的拆分。

复杂度 $O(n \log n)$。

---

