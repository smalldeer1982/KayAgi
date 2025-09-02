# [ICPC 2020 Nanjing R] Baby's First Suffix Array Problem

## 题目描述

对于长度为 $n$ 的字符串 $s$ ，它的后缀数组是一个由 $1$ 到 $n$ 的整数组成的排列 $sa$ ，使得 $s[sa_1.. n], s[sa_2..n], \dots, s[sa_n..n]$ 是按照字典序排序的 $s$ 的非空后缀列表。字符串 $s$ 的后缀的排名表是一个由 $1$ 到 $n$ 的整数组成的排列 $rank$ ，使得 $rank_{sa_i} = i$ 。

小鸟 Kotori 有一个字符串 $s = s_1s_2\dots s_n$ 。她想要进行 $m$ 次询问。在第 $i$ 次询问中，会给出 $s$ 的一个子串 $x = s[l_i..r_i]$ ，Kotori 想要知道 $x$ 的后缀 $s[k_i..r_i]$ 的排名。

注意，$s[l..r]$ 表示 $s$ 的从第 $l$ 个位置开始到第 $r$ 个位置结束的子串（包括第 $l$ 个和第 $r$ 个位置）。

## 说明/提示

### 注意

题面翻译由 Doubao 提供。

## 样例 #1

### 输入

```
2
10 4
baaabbabba
2 8 3
1 1 1
2 3 2
2 5 4
20 3
cccbccbadaacbbbcccab
14 17 16
3 20 17
17 20 18
```

### 输出

```
2
1
2
3
4
15
3
```

# 题解

## 作者：lzyqwq (赞：13)

**[我永远喜欢数据结构](https://www.luogu.com.cn/blog/juruo-lzy/IloveDS)**

很神仙的串串题，第一次见这种做法。在 CF 上应该能评个 $\ge \color{maroon}{*3300}$。~~当时场上想假了直接对着这玩意冲成小丑了~~。百度上只搜到了后缀树的题解，你谷的一篇后缀数组题解可能是因为作者太神仙了所以讲的比较简略，这里来一篇详细一点的后缀数组题解。

长文码字不易，有笔误还请耐心指出 /bx。

**[题目传送门](https://www.luogu.com.cn/problem/P9623)**

> - 给出长度为 $n$ 的字符串 $s$，$m$ 组询问对 $s[l,r]$ 这个子串进行后缀排序后，（这个子串的）后缀 $s[k,r]$ 的排名。排名定义为比它小的后缀的个数 $+1$。
>
> - 多组数据，记 $N=\sum n$，$M=\sum m$，$N,M\le 5\times 10^4$。
>
> - $\text{5.00 s / 256.00 MB}$。

这个 $N\le 5\times 10^4$ 和 $\text{5.00\,s}$ 时限是不是为了放时间复杂度 $\mathcal{O}((N+M)\log^3 N)$ 的做法过啊，是的话就太不牛了 /qd。

先对原串进行后缀排序。

考虑从排名的定义入手，求出子串中有多少个后缀比询问的后缀小。对于这些子串中的后缀，考虑找到它们在原串中的后缀，尝试寻找充要条件。

设有（子串的）后缀 $s[i,r]$，其中 $i\in[l,k)\bigcup \,(k,r]$。按两类情况考虑。

- $rk_i<rk_k$

  此时 $s[i,r]<s[k,r]$，**当且仅当 $\boldsymbol{i<k}$ 且 $\bold{|LCP}\boldsymbol{(s[i,n],s[k,n])|\le r-k}$，或 $\boldsymbol{i>k}$**。

  - 充分性
  
      当 $i<k$ 且 $|\text{LCP}(s[i,n],s[k,n])|\le r-k$ 时，两个后缀第一个不同的位置一定均在 $s[i,r]$ 和 $s[k,r]$ 中出现，此时比较两个串也是比较这两位，因为 $rk_i<rk_k$，故 $s[i,r]<s[k,r]$。
  
      当 $i>k$ 时，若两个后缀第一个不同的位置均在 $[l,r]$ 中出现则与上一种情况合理，否则 $s[i,r]$ 是 $s[k,r]$ 的前缀，故 $s[i,r]<s[k,r]$。
  
  - 必要性
  
      考虑 $s[i,r]<s[k,r]$ 时，若 $i<k$，则一定有 $|\text{LCP}(s[i,n],s[k,n])|\le r-k$，否则 $s[k,r]$ 为 $s[i,r]$ 前缀，此时 $s[k,r]<s[i,r]$。若 $i>k$，则已经满足条件。
  
  - 做法
  
      分 $i<k$ 和 $i>k$ 讨论。
    
      若 $i<k$，则需要统计有多少个后缀 $s[i,n]$ 满足 $i\in[l,k)$，$rk_i<rk_k$ 且 $\text{|LCP}(s[i,n],s[k,n])|\le r-k$。降第三个限制转化为 $\text{height}$ 数组的限制，其等价于 $\min\limits_{j=rk_i+1}^{rk_k}\text{height}_j\le  r-k$。容易发现此时满足条件的 $i$ 的 $rk_i$ 在一个前缀 $[1,x]$ 中，其中 $x<rk_k$。二分 + RMQ 求出这个 $x$，问题转化成统计有多少个点对满足 $i\in[l,k)$ 且 $rk_i\in[1,x]$，主席树维护即可。
    
      若 $i>k$，则需要统计有多少个后缀 $s[i,n]$ 满足 $i\in(k,r]$ 且 $rk_i<rk_k$，同样主席树维护。

  

- $rk_i>rk_k$

  此时 $s[i,r]<s[k,r]$，**当且仅当 $\boldsymbol{i>k}$ 且 $\bold{|LCP}\boldsymbol{(s[i,n],s[k,n])|\ge r-i+1}$**。
  
  - 充分性
  
      容易发现此时 $s[i,r]$ 为 $s[k,r]$ 前缀，故 $s[i,r]<s[k,r]$。
    
  - 必要性
  
      考虑证明不满足上述条件则 $s[i,r]>s[k,r]$。
    
      若 $i<k$，如果两个串第一个不同的位置均在 $[l,r]$ 中出现，因为 $rk_k<rk_i$，所以 $s[i,r]>s[k,r]$。否则，$s[k,r]$ 为 $s[i,r]$ 前缀，此时 $s[i,r]>s[k,r]$。
    
      若 $i>k$ 且 $\text{|LCP}(s[i,n],s[k,n])|\le r-i$，则两个串第一个不同的位置一定均在 $[l,r]$ 中出现，因为 $rk_k<rk_i$，所以 $s[i,r]>s[k,r]$。
    
  - 做法（本题解最核心部分）
  
      以排名为下标做一遍序列分治，将询问挂在 $rk_k$ 上，每层分治考虑右半边对左半边的贡献（很像 cdq 分治）并左右递归下去统计，则对于任意一个合法的后缀，根据分治树的形态，一定存在且仅存在一层分治，使得询问在左半边，后缀在右半边，此时它被统计到。并且，在每层分治中我们统计合法的贡献，可以做到不重不漏。
    
      设分治区间为 $[L,R]$，中点 $mid=\left\lfloor\dfrac{L+R}{2}\right\rfloor$。
    
      对于左半边的一个询问 $(l,r,k)$，我们要统计右半边有多少个 $i$，满足：
    
      - $sa_i\in(k,r]$
    
      - $\text{|LCP}(s[k,n],s[sa_i,n])|\ge r-sa_i+1\Leftrightarrow \min\limits_{j=rk_k+1}^i \text{height}_j\ge r-sa_i+1$
    
      采用序列分治的一般套路，从 $mid\rightarrow L$ 扫描询问。设当前扫到的排名为 $K$。维护变量 $mn=\min\limits_{j=K+1}^{mid}\text{height}_j$。对于右半区间维护前缀 $\text{height}$ 最小值，即 $pmn_i=\min\limits_{j=mid+1}^{i}\text{height}_j$。则对于当前扫到的排名上的询问，条件中的 $\min\limits_{j=rk_k+1}^i \text{height}_j\ge r-i+1$ 可以转化为 $\min\{mn,pmn_i\}$。
    
      容易发现 $pmn_i$ 具有单调（不升）性。可以找到一个分界点 $p$，使得当 $i\in[mid+1,p)$ 时，$\min\{mn,pmn_i\}=mn$；当 $i\in[p,R]$ 时，$\min\{mn,pmn_i\}=pmn_i$。
    
      对于分界点左边的情况，就是统计有多少 $i$ 满足：
      
      - $sa_i\in(k,r]$
      
      - $mn \ge r-sa_i+1\Leftrightarrow sa_i\ge r-mn+1$
      
      - $i\in[mid+1,p)$
      
      整理一下就是：
      
      - $sa_i\in[\max\{r-mn,k\}+1,r]$
      
      - $i\in[mid+1,p)$
      
      容易主席树维护。
      
      对于分界点右边的情况，就是统计有多少 $i$ 满足：
      
      - $sa_i\in(k,r]$
      
      - $pmn_i\ge r-sa_i+1\Leftrightarrow sa_i+pmn_i\ge r+1$
      
      - $i\in [p,R]$
      
      你发现这是个三维数点，好像行不通啊！
      
      然后就是一个很妙的转化了。考虑正难则反。你发现对于分界点右边的情况，$sa_i+pmn_i\ge r+1\Rightarrow sa_i+mn\ge r+1$，因为在分界点右边 $pmn_i=\min\{pmn_i,mn\}$。所以可以先统计满足以下条件的 $i$ 的个数：
      
      - $sa_i\in[\max\{r-mn,k\}+1,r]$
      
      - $i\in [p,R]$
      
      算上分界点左边的统计，相当于要统计右半边满足 $sa_i\in[\max\{r-mn,k\}+1,r]$ 的 $i$ 个数。可以 `vector` + 二分统计。考虑哪些不合法的被统计了，显然它满足：
      
      - $sa_i\in[\max\{r-mn,k\}+1,r]$
      
      - $sa_i+pmn_i\le r$
      
      - $i\in[p,R]$
      
      于是就要减去这样的 $i$ 的个数。实际上这还是个三维数点，不过你发现，$\boldsymbol{\nexists\,i\in[mid+1,p),sa_i\in[\max\{r-mn,k\}+1,r]\land sa_i+pmn_i\le r}$。即分界点左边不存在满足前两个条件的 $i$。
      
      为什么呢？首先 $sa_i\in[\max\{r-mn,k\}+1,r]$ 的必要条件是 $sa_i\ge r-mn+1$。你考虑分界点左边 $mn\le pmn_i$，若 $sa_i\ge r-mn+1$ 即 $sa_i+mn\ge r+1$，则一定有 $sa_i+pmn_i\ge r+1$。反之，若 $sa_i+pmn_i\le r$，则一定有 $sa_i+mn \le r$ 即 $sa_i\le r-mn$。因此**两个条件不能被同时满足**。
      
      所以我们直接大胆忽略 $i\in[p,R]$ 这个条件，统计全局（当前分治区间） $sa_i\in[\max\{r-mn,k\}+1,r]$ 且 $sa_i+pmn_i\le r$ 的 $i$ 的个数。同样是二维数点，主席树维护即可。
      
至此两类统计都解决了。接下来算复杂度。因为有主席树和 ST 表，所以空间复杂度显然为 $\mathcal{O}(N\log N)$。

至于时间复杂度（只说每个部分的瓶颈），后缀排序是 $\mathcal{O}(N\log^2 N)$ 的（因为不是瓶颈所以没用基数排序优化）。$rk_i<rk_k$ 的统计需要往主席树中插入 $\mathcal{O}(N)$ 个点对，并且每次询问要进行一次 $\mathcal{O}(1)$ 检查（ST 表）的二分以及 $\mathcal{O}(\log N)$ 的主席树查询，时间复杂度为 $\mathcal{O}((N+M)\log N)$。

对于分治部分，每个询问会在 $\mathcal{O}(\log N)$ 层分治中被扫到，每次扫到要做一次主席树查询和 `vector` 二分，单次是 $\mathcal{O}(\log N)$。每个点对会在 $\mathcal{O}(\log N)$ 层分治中被插入主席树，单次也是 $\mathcal{O}(\log N)$。这部分的时间复杂度为 $\mathcal{O}((N+M)\log^2 N)$。为了维护主席树，每层分治需要将点对进行排序，由于每层分治的区间总长度为 $N$，因此任意一层排序的 $\log$ 不超过 $\mathcal{O}(\log N)$。容易通过乘法分配律得到是 $\mathcal{O}(N\log^2 N)$ 的。因此，分治部分的总时间复杂度为 $\mathcal{O}((N+M)\log ^2 N)$。

综上，本做法时间复杂度为 $\mathcal{O}((N+M)\log^2 N)$，空间复杂度为 $\mathcal{O}(N\log N)$，可以接受。

**[代码](https://www.luogu.com.cn/paste/tfdo14g3)**

**[AC 记录](https://www.luogu.com.cn/record/140264543)**

完结撒花！
      
     

---

## 作者：yspm (赞：8)

按照题目名称，从 SA 角度入手思考这个问题。

对于 $t\in[l,r]\ \cap \mathbb{Z}$，如果有 $rk_t<rk_k$ 并且 $\rm LCP(t,k)\le r-k+1$，那么后缀 $s[t\dots r]$ 肯定比 $s[k\dots r]$ 排名靠前。

对于那些 $rk_t>rk_k$ 的 $t$，如果 $\rm LCP(t,k)\ge r-t+1$ 那么也可以满足从 $t$ 开始的后缀排名小于从 $k$ 开始的后缀排名。不难发现这时候我们需要满足 $t>k$

先说 $rk_t< rk_k$ 的部分，我们的限制中包含了 $\rm LCP$ 的长度，所以可以放到 $\rm height$ 数组上处理。找到 $\rm height$ 数组的一个前缀 $[1,p]$ 满足区间 $[p+1,rk_k]$ 的最小值小于 $r-k+1$（使用二分配合 ST 表做到单 $\log$ 复杂度）然后对这段进行数点，注意应该数前缀有多少 $s$ 满足 $sa_s\in [l,k-1]$

对于那些 $s>k$ 的且 $rk_s<rk_k$ 的部分，只要 $rk$ 小就行了，即使 $\rm LCP\ge r-s+1$ 也没关系，因为字符串长度本来就小。

剩下一个部分就是对于 $rk_t>rk_k$ 但是 $t>k,\rm LCP(s[t\dots r],s[k\dots r])\ge r-t+1$ 的 $t$ 的统计。考虑对 $rk$ 数列分治，询问放到 $rk_k$ 的位置,统计 $[mid+1,r]$ 中的后缀 $[l,mid]$ 中的询问的贡献。这其实是一个带限制的数点，即 $sa_t+\min\limits_{i=rk_k+1}^t{h[i]}+1\ge r$

既然有分治，那么把 $\rm LCP$ 中的区间 $h_i$ 最小值  拆开成左边一段 $h_i$ 的最小值 $minl_i$ 和右边一段 $h_i$ 的最小值 $minr_i$ 取较小者。

取较小者拆成对数点位置的限制，即如果 $sa_t+minr_t-1<r$ 的肯定不考虑，满足 $t>k,s[t\dots r]<s[k\dots r]$ 的 $t$ 肯定也满足 $t\ge r-minl_k+1$

对于所有 $[l,mid]$ 中的询问按照 $(l,r,k)$ 中的 $r$ 从大到小排序。把 $[mid+1,r]$ 中的 $t$ 按照 $sa_t+minr_t$ 从大到小排序，树状数组统计答案。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N=5e4+10;
int n,Q,ans[N];
char s[N];
int sa[N],rk[N],ton[N],sec[N],h[N],st[N][16];
inline int query(int l,int r){
	int t=log2(r-l+1);
	return min(st[l][t],st[r-(1<<t)+1][t]);
}
struct Fenwick_Tree{
	int c[N];
	inline int query(int x){
		int res=0;
		for(;x;x-=x&(-x)) res+=c[x];
		return res;
	}
	inline void insert(int x,int k){
		for(;x<=n;x+=x&(-x)) c[x]+=k;
		return ;
	}
}T;
inline void get_SA(){
    int m=26;
    auto qsort=[&](){
		rep(i,1,n) ton[rk[i]]++;
        rep(i,1,m) ton[i]+=ton[i-1];
        for(int i=n;i>=1;--i) sa[ton[rk[sec[i]]]--]=sec[i];
        for(int i=1;i<=m;++i) ton[i]=0;
        return ;
    };
	for(int i=1;i<=n;++i) rk[i]=s[i]-'a'+1,sec[i]=i;
    qsort();
	for(int w=1,p=0;p<n;m=p,w<<=1){
		p=0; 
        for(int i=n;i>=n-w+1;--i) sec[++p]=i;
        for(int i=1;i<=n;++i) if(sa[i]>w) sec[++p]=sa[i]-w;
        qsort();
        swap(sec,rk);
        rk[sa[1]]=p=1;
        for(int i=2;i<=n;++i){
            if(sec[sa[i]]==sec[sa[i-1]]&&sec[sa[i]+w]==sec[sa[i-1]+w]) rk[sa[i]]=p;
            else rk[sa[i]]=++p;
        }
    }
	int k=0;
	for(int i=1;i<=n;++i){
		k=max(k-1,0);
		if(rk[i]==1) continue;
		int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]) ++k;
		h[rk[i]]=k;
	}
	for(int i=1;i<=n;++i) st[i][0]=h[i];
	for(int j=1;j<16;++j){
		for(int i=1;i+(1<<j)-1<=n;++i) st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}
    return ;
}
vector<tuple<int,int,int,int> > q1[N];//l,r,k,id
vector<tuple<int,int,int> >q2[N];//l,r,id

int minl[N],minr[N],id[N];

inline void conquer(int l,int r){
	if(l==r) return ;
	int mid=(l+r)>>1;
	conquer(l,mid); conquer(mid+1,r);
	vector<tuple<int,int,int,int> > S;
	for(int i=l;i<=mid;++i) for(auto t:q1[i]) S.push_back(t);
	if(!S.size()) return ;
	minr[mid]=minl[mid+1]=n+1;
	for(int i=mid+1;i<=r;++i) minr[i]=min(minr[i-1],h[i]);
	for(int i=mid;i>=l;--i) minl[i]=min(h[i+1],minl[i+1]);
	sort(S.begin(),S.end(),[&](tuple<int,int,int,int> a,tuple<int,int,int,int> b){return get<1>(a)>get<1>(b);});
	int cnt=0;
	for(int i=mid+1;i<=r;++i) id[++cnt]=i;
	sort(id+1,id+cnt+1,[&](const int x,const int y){return sa[x]+minr[x]>sa[y]+minr[y];});
	int iter=0;
	for(auto [l,r,k,qid]:S){
		while(iter<cnt&&sa[id[iter+1]]+minr[id[iter+1]]-1>=r){
			++iter;
			T.insert(sa[id[iter]],1);
		}
		if(max(r-minl[rk[k]]+1,k+1)<=r){
			ans[qid]+=T.query(r)-T.query(max(r-minl[rk[k]]+1,k+1)-1);
		}
	}
	for(int i=1;i<=iter;++i) T.insert(sa[id[i]],-1);
	return ;	
}

int main(){
    int test; scanf("%d",&test);
    while(test--){
        scanf("%d%d",&n,&Q);
        scanf("%s",s+1);
		get_SA();
		for(int i=1;i<=Q;++i){
			int l,r,k; scanf("%d%d%d",&l,&r,&k);
			q1[rk[k]].emplace_back(l,r,k,i);
			if(k!=r) q2[rk[k]].emplace_back(k+1,r,i);
			if(l!=k){
				int pos=rk[k];
				for(int i=15;i>=0;--i) if(pos>(1<<i)){
					if(query(pos-(1<<i)+1,rk[k])>=r-k+1) pos-=(1<<i);
				}
				--pos;
				q2[pos].emplace_back(l,k-1,i);
			}
		}
		conquer(1,n);
		for(int i=1;i<=n;++i){
			T.insert(sa[i],1);
			for(auto [l,r,id]:q2[i]) ans[id]+=T.query(r)-T.query(l-1);
		}
		for(int i=1;i<=n;++i) T.insert(sa[i],-1);
		for(int i=1;i<=Q;++i) printf("%d\n",ans[i]+1),ans[i]=0;
		for(int i=1;i<=n;++i){
			q1[i].clear();
			q2[i].clear();
			rk[i]=sa[i]=ton[i]=sec[i]=0;
		}
	}
    return 0;
}
```



---

## 作者：Nt_Tsumiki (赞：6)

提供一个常数巨小且非常简单的 2log SA 做法。

基于 zltqwq 的[这篇题解](https://www.luogu.com.cn/article/eggc13n7)。

简单模拟一下两个字符串比大小的过程，即，求出 LCP 比较 LCP 后一位的字符大小。

对于后一位的字符大小我们可以通过原串上的 rk 求得。

因为有二维限制所以较为显然的对于 sa 数组上个分治，令 $pre_i=\min_{j=i}^{mid} h_j,suf_i=\min_{j=mid-1}^i h_j$。

那么跨过 $mid$ 的区间 $[l,r]$ LCP 可以表示为 $\min\{pre_{rk_l+1},suf_{rk_r}\}$。

那我们现在就可以按照 rk 和原串中的位置关系去分讨了。

1. $rk_i<rk_k\land i<k$，因为 $rk_i<rk_k$ 的缘故且后缀 $i$ 还比后缀 $k$ 长，所以我们要想使 $i$ 对答案有贡献只能让 $\min\{pre_{i+1},suf_{rk_k}\}<r-k+1$，反之 $k$ 的下一位就为空了一定小于 $i$，对于实现上我们要分两种情况计数。
   - $suf_{rk_k}<r-k+1$，这时候 LCP 一定小于 $r-k+1$，所以直接统计 $[l,k-1]$ 范围内的点数就行了。
   - $suf_{rk_k}\ge r-k+1$，这时候我们要统计的实际就是 $pre_{i}<r-k+1$ 的 $i$ 的数量，直接和 $sa_i\in[l,k-1]$ 一起做就是一个二维数点，扫描线即可。
2. $rk_i>rk_k\land i<k$，因为 $i$ 不仅 rk 比 $k$ 大，而且串还比 $k$ 长，所以一定不被计数。
3. $rk_i<rk_k\land i>k$，和上面同理，只不过是一定被统计。
4. $rk_i>rk_k\land i>k$，和 1 差不多，只不过限制是 $\min\{pre_{rk_p+1},suf_i\}\ge r-sa_i+1$ 也就是 $pre_{rk_p+1}\ge r-sa_i+1\land suf_i\ge r-sa_i+1$。对于第一个式子化简一下有 $sa_i\ge r-pre_{rk_p+1}+1$，也就是对于 $sa_i$ 的范围为 $[\max\{k+1,r-pre_{rk_p+1}+1\},r]$；对于第二个式子化简一下有 $sa_i+suf_i\ge r+1$，两个限制一起做就是一个二维数点。

综上，我们得到了一个 cdq 分治套二维数点的两个 log 小常熟做法。

[submission](https://www.luogu.com.cn/record/195887905)

---

## 作者：zhouhuanyi (赞：3)

提供一个 $O(n \log n)$ 的做法。

考虑先认为 $S[x,r]<S[k,r]$ 的充要条件为 $rk_{x}<rk_{k}$，再修正算错的部分，可以发现算错的部分有两种：

$1.$ $x<k$ 的部分，此时要满足 $S[k,r]$ 是 $S[x,r]$ 的一个 $\text{border}$ 且 $S[x,n]<S[k,n]$，即 $lcp(S[x,n],S[k,n])\geqslant n-k+1$，$rk_{x}<rk_{k}$，这个在 $\text{rk}$ 数组上对应一段连续的区间，可以直接二维数点解决。

$2.$ $x>k$ 的部分，此时要满足 $S[x,r]$ 是 $S[k,r]$ 的一个 $\text{border}$ 且 $S[k,n]<S[x,n]$，即对于 $S[k,r]$ 的所有真 $\text{border}$，长度为 $len$ 的贡献为 $[rk_{r}<rk_{r-len+1}]$，求所有 $\text{border}$ 的贡献和。由于一个串的 $\text{border}$ 形成 $\text{log}$ 段等差数列，每一段等差数列都形如 $(ST)^tS$ 的形式，对于同一个等差数列约束形如 $(TS)^tA>B$，$t$ 对应的是一段前缀或一段后缀，二分分界点即可，令等差序列长度为 $l$，这部分要 $\log_{2} l$ 的代价，而 $\prod_{i=1}^{m}(l+1)\leqslant n$，所以 $\sum_{i=1}^{m}\log_2(l+1)\leqslant \log_{2}n$。加上用基本子串字典求解 $\text{border}$ 等差数列的复杂度，于是这部分可以做到 $O(n \log n)$。

综上我们在 $O(n\log n)$ 的复杂度内解决了该问题，但实际上跑得比一部分 $O(n\log^2n)$ 的分治做法还要慢，原因可能是基本子串字典常数太大了。

---

## 作者：MaxBlazeResFire (赞：2)

对原串求后缀数组。下面考察区间 $\rm SA$ 和原串 $\rm SA$ 的关系。

对于区间 $[l,r]$ 与内部的两个位置 $i<j$，考察区间内部 $i$ 后缀与 $j$ 后缀的大小关系。

如果原串 $j$ 的排名小于 $i$ 的排名，那么区间内 $j$ 的排名也小于 $i$ 的排名；如果原串 $j$ 的排名大于 $i$ 的排名，当 $[j,n]$ 和 $[i,n]$ 的 $\rm LCP$ 小于等于 $r-j$ 时，区间内存在使得 $j$ 的字典序大于 $i$ 字典序的判据，$j$ 的排名仍然大于 $i$ 的排名；否则 $j$ 的排名小于 $i$ 的排名。

把所有询问离线下来，在原串排名序列上做 $\rm CDQ$ 分治。具体来说，我们把 $k$ 处的询问挂在下标 $rk_k$ 上，每次统计右半部分对左半部分的贡献。具体来说，我们求出对于左侧的每个询问，右侧有几个位置为它贡献。考虑两侧的两个位置 $i,j$，与 $i$ 上的询问 $[l,r]$，由上面的讨论，$j$ 为 $i$ 做贡献（$j$ 在区间内的字典序小于 $i$）的条件是：

$sa_j\in[l,r]$；$sa_j>sa_i$ 且 ${\rm LCP}(i,j)>r-sa_j$。考虑套路地用一个指针 $i$ 从 $mid$ 向左扫，维护变量 $e=[i+1,mid]$ 区间 $\rm height$ 的 $\min$，再记静态序列 $c_j=[mid+1,j]$ 的区间 $\rm height$ 的 $\min$，枚举 $i$ 上询问 $[l,r]$，转化为统计有多少个 $j$ 满足 $sa_j\in[\max\{sa_i+1,l\},r]$ 且 $sa_j>r-\min\{e,c_j\}$，再分讨一步，分别求有多少个 $j$ 同时满足 $sa_j\in[l,r],c_j\leq e,sa_j+c_j>r$ 或同时满足 $sa_j\in[l,r],c_j>e,sa_j>r-e$。

把 $(sa_j,c_j)$ 放到二维平面上去，右侧的问题是朴素的；前者则是让我们求出一个直角梯形内或是三角形内的点数。注意到这个直角梯形或三角形的角一定在 $x$ 轴上，差分成一个贴着 $x$ 轴的矩形和一个贴着 $x$ 轴的等腰直角三角形，对于这个等腰直角三角形，考虑从一侧扫描线，就只用维护一维偏序，分别用两个 $\rm BIT$ 就好，另一边也可以类似地做。

然后再考虑左到右的贡献，两个排名，$i<j$，$i$ 为 $j$ 做贡献的条件是 $sa_i\in[l,r],sa_i>sa_j$ 或 $sa_i\in[l,r],sa_i<sa_j$ 且 ${\rm LCP}(i,j)\leq r-sa_j$，转化成 $sa_i\in[\max\{sa_j+1,l\},r]$ 与 $sa_i\in[l,\min\{r,sa_j-1\}]$ 与 $\min\{e,c_i\}\leq r-sa_j$ 可以类似地处理。

复杂度 $O(n\log^2n)$。

[参考代码。](https://www.luogu.com.cn/paste/7b5qaein)

---

## 作者：Otomachi_Una_ (赞：0)

首先建出后缀数组。假设 $hi_i=\operatorname{lcp}(s[rk_i,n],s[rk_{i+1},n])$。

考虑计算 $s[l,r]$ 中 $s[k,r]$ 的 $sa$，即我们需要计算 $s[i,r]$（$i\in [l,r]$）中有多少个字典序小于 $s[k,r]$ 的。

首先我们计算 $i\in [l,k-1]$ 的部分。这部分比较容易。

首先 $s[i,r]<s[k,r]$ 表明了 $s[i,n]<s[k,n]$。即 $rk_i<rk_k$。其次我们需要 $\operatorname{lcp}(s[i,n],s[k,n])<r-k+1$。这是因为其第一个不同的字符应当出现在 $[k,r]$ 之中。

由于 $\operatorname{lcp}(s[i,n],s[j,n])=rmq(rk_i,rk_j-1)$。其中 $rmq(l,r)$ 表示 $\min_{i=l}^r h_i$。

我们通过 $hi$ 数组容易算出 $sa_i$ 应当在一个前缀当中。就变成了一个二位数点。

然后计算 $i\in [k+1,r]$。首先如果 $rk_i<rk_k$ 那么显然 $s[i,r]<s[k,r]$。有变成一个二位数点。

然后剩下的部分就比较复杂了。我们想要计算 $i\in [k+1,r]$ 的个数，使得其是 $s[k,r]$ 的一个前缀且 $rk$ 值比其大。更加具体的：

- $i\in [k+1,r]$；
- $rk_k<rk_i$；
- $rmq(rk_k,rk_i-1)\geq r-i+1$。

条件 $2$ 不好处理。我们不要枚举 $i$，我们来枚举 $j=sa_i$。可以改写成：

- $rk_k<j$；
- $sa_j\in [k+1,r]$；
- $rmq(rk_k,j-1)\geq r-sa_j+1$.

我们写一个 $O(nq)$ 的暴力来算这部分，竟然直接过了！！！这也太好笑了。

我们来考虑一点正经一点的做法。记 $l_0=rk_k$，形式化地写成：

- $l_0<j$；
- $sa_j\in[l_1,r_1]$；
- $rmq(l_0,j-1)+sa_j\geq l_2$；

对 $l_0$ 和 $j$ cdq 分治。假设分治中心是 $M$。我们需要计算所有 $[l_0,j]$ 跨跨过 $M$ 的贡献。

假设 $A_i=rmq(i,M-1)$，$B_i=rmq(M,i)$。那么改写成：

- $sa_j\in [l_1,r_1]$；
- $\min(A_{l_0},B_{j-1})+sa_j\geq l_2$；

那么实际上由于大于号那边是 $\min$，所以我们能拆成两个条件：

- $A_{l_0}+sa_j\geq l_2$；
- $B_{j-1}+sa_j\geq l_2$。

第一个条件是关于 $sa_j$ 本身的一个约束。和 $[l_1,r_1]$ 求个交就行。

 第二个条件是关于 $B_{j-1}+sa_j$ 的一个约束。我们把这个也看作一个变量，就变成了经典的二位数点问题。扫描线即可。

时间复杂度 $O(n\log^2n)$。

---

