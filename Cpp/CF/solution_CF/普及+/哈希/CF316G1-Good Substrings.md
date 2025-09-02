# Good Substrings

## 题目描述

Smart Beaver recently got interested in a new word game. The point is as follows: count the number of distinct good substrings of some string $ s $ . To determine if a string is good or not the game uses rules. Overall there are $ n $ rules. Each rule is described by a group of three $ (p,l,r) $ , where $ p $ is a string and $ l $ and $ r $ $ (l<=r) $ are integers. We’ll say that string $ t $ complies with rule $ (p,l,r) $ , if the number of occurrences of string $ t $ in string $ p $ lies between $ l $ and $ r $ , inclusive. For example, string "ab", complies with rules ("ab", $ 1 $ , $ 2 $ ) and ("aab", $ 0 $ , $ 1 $ ), but does not comply with rules ("cd", $ 1 $ , $ 2 $ ) and ("abab", $ 0 $ , $ 1 $ ).

A substring $ s[l...\ r] $ $ (1<=l<=r<=|s|) $ of string $ s=s_{1}s_{2}...\ s_{|s|} $ ( $ |s| $ is a length of $ s $ ) is string $ s_{l}s_{l+1}...\ s_{r} $ .

Consider a number of occurrences  of string $ t $ in string $ p $ as a number of pairs of integers $ l,r $ $ (1<=l<=r<=|p|) $ such that $ p[l...\ r]=t $ .

We’ll say that string $ t $ is good if it complies with all $ n $ rules. Smart Beaver asks you to help him to write a program that can calculate the number of distinct good substrings of string $ s $ . Two substrings $ s[x...\ y] $ and $ s[z...\ w] $ are cosidered to be distinct iff $ s[x...\ y]≠s[z...\ w] $ .

## 说明/提示

There are three good substrings in the first sample test: «aab», «ab» and «b».

In the second test only substrings «e» and «t» are good.

## 样例 #1

### 输入

```
aaab
2
aa 0 0
aab 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
ltntlnen
3
n 0 0
ttlneenl 1 4
lelllt 1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
a
0
```

### 输出

```
1
```

# 题解

## 作者：冯老师 (赞：3)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17732656.html)**

**[CF](https://codeforces.com/problemset/problem/316/G1)** **[洛谷](https://www.luogu.com.cn/problem/CF316G1)**

> - 给出字符串 $s$，以及 $n$ 个限制，每个限制形如 $t_i\texttt{ }l_i\texttt{ }r_i$，一个字符串满足该条限制，当且仅当它在字符串 $t_i$ 中的出现次数在 $[l_i,r_i]$ 之间。
>
> - 求 $s$ 有多少个**本质不同**的子串满足所有限制。
>
> - $|s|,\max\limits_{i=1}^n |t_i|\le 200$，$n\le 10$。

记 $s[l,r]$ 为字符串 $s$ 以 $s_l$ 开头，以 $s_r$ 结尾的子串，形式化的，$s[l,r]=\overline{s_l\dots s_r}$。

看到「本质不同子串」，想到后缀数组。先将所有字符串用奇怪字符拼起来（记大串为 $S$）做后缀排序求出 $sa,rk,\text{height}$ 数组并对 $\text{height}$ 数组维护 ST 表。

对于一个字符串 $s$，我们知道排名为 $i$ 的后缀带来的本质不同子串是 $s[sa_i,\text{height}_i+1]\sim  s[sa_i,|s|]$ 这些，然后你会发现这些子串的出现次数随着长度递增**不升**。

因为若有一个长串出现若干次，我的短串也被这个长串包含，至少出现了这么多次。

考虑二分出最短的满足所有限制**上界**的字符串长度 $ans_l$ 以及最长的满足所有限制**下界**的字符串长度 $ans_r$，那么这个后缀就可以带来 $ans_r-ans_l+1$ 个满足所有限制的本质不同子串。

维护一个前缀和数组 $sum_{j,i}$，表示排名为 $1\sim i$ 的后缀中，有多少个后缀是 $t_j$ 带来的。我们又知道对于一个子串，出现它的后缀的排名是一段连续的区间。套路用二分和 ST 表求 $\text{LCP}$ 得到这个区间 $[L,R]$。问题变成了判断区间内某个数 $i$ 出现次数是否（不）超过给定的值。用 $sum_{i,R}-sum_{i,L-1}$ 表示出其出现次数，由于 $n$ 很小，枚举判断即可。这样这题基本就做完了。

还有一个地方需要注意，我们要求的是**原串 $\boldsymbol{s}$** 某个后缀带来的本质不同子串个数，但是现在把所有字符接在一起，$\text{height}$ 数组并是大串 $S$ 中两个排名相邻的后缀的 $\text{LCP}$。所以我们要按排名枚举 $S$ 的后缀，如果它是 $s$ 的后缀就统计答案。然后你对 $S$ 后缀排序，**原串 $\boldsymbol{s}$ 中的所有后缀也是有序的**，不然它们在 $S$ 中也是无序的，相当于你就没排序。 因此直接记录上一个为原串中的某个后缀的位置 $la$，那么我要的 $\text{height}$，原串 $s$ 中排名相邻两个后缀的 $\text{LCP}$，就是 $S$ 中 $S[la,|S|]$ 和当前后缀的 $\text{LCP}$。后面接的东西不影响，因为你接了奇怪字符，在那一位一定失配，不会影响 $\text{LCP}$ 长度。

时间复杂度为 $\mathcal{O}(|S|\log |s| (n+\log|S|))$，空间复杂度为 $\mathcal{O}(|S|\log |S|+n|S|)$。

代码（为啥我写的那么长）：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define P pair
#define fi first 
#define se second 
using namespace std; const int N = 5e5 + 5; ll ans; string s; int n, id[N], a[N];
int ord = 'z', len, ql[N], qr[N], sum[11][N], hd[N], siz[N], k; bool tag[N];
struct SuffixArray {
    int cnt[N], sa[N], rk[N], ht[N], st[20][N], lg[N]; 
    P<P<int, int>, int> p[N], tmp[N];
    void init() {
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= len; ++i) ++cnt[a[i]];
        for (int i = 1; i <= ord; ++i) cnt[i] += cnt[i - 1];
        for (int i = 1; i <= len; ++i) rk[i] = cnt[a[i] - 1] + 1;
    }
    void sort() {
        for (int l = 1, id; l <= len; l <<= 1) {
            for (int i = 1; i <= len; ++i)
                p[i] = {{rk[i], i + l > len ? 0 : rk[i + l]}, i};
            memset(cnt, id = 0, sizeof cnt);
            for (int i = 1; i <= len; ++i) ++cnt[p[i].fi.se];
            for (int i = 1; i <= len; ++i) cnt[i] += cnt[i - 1];
            for (int i = len; i >= 1; --i) tmp[cnt[p[i].fi.se]--] = p[i];
            for (int i = 1; i <= len; ++i) p[i] = tmp[i];
            memset(cnt, 0, sizeof cnt);
            for (int i = 1; i <= len; ++i) ++cnt[p[i].fi.fi];
            for (int i = 1; i <= len; ++i) cnt[i] += cnt[i - 1];
            for (int i = len; i >= 1; --i) tmp[cnt[p[i].fi.fi]--] = p[i];
            for (int i = 1; i <= len; ++i) p[i] = tmp[i];
            for (int i = 1; i <= len; ++i) 
                { if (i == 1 || p[i].fi != p[i - 1].fi) ++id; rk[p[i].se] = id; }
            if (id == len) break;
        }
        for (int i = 1; i <= len; ++i) sa[rk[i]] = i;
    }
    void height() {
        for (int i = 1, k = 0; i <= len; ++i) {
            if (rk[i] == 1) { ht[i] = k = 0; continue; }
            if (k) --k; int j = sa[rk[i] - 1];
            while (i + k <= len && j + k <= len && a[i + k] == a[j + k]) ++k;
            ht[i] = k;
        }
    }
    void ST() {
        for (int i = 1; i <= len; ++i) st[0][i] = ht[sa[i]], lg[i] = __lg(i);
        for (int i = 1; (1 << i) <= len; ++i)
            for (int j = 1; j + (1 << i) - 1 <= len; ++j)
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
    int LCP(int l, int r) {
        if (l == r) return len - sa[l] + 1; ++l;
        int k = lg[r - l + 1]; return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
} SA;
bool check1(int id, int x) {
    int l = 1, r = id, ansl, ansr;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (SA.LCP(mid, id) >= x) ansl = mid, r = mid - 1; else l = mid + 1;
    }
    l = id, r = len;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (SA.LCP(id, mid) >= x) ansr = mid, l = mid + 1; else r = mid - 1;
    }
    for (int i = 1; i <= n; ++i)
        if (sum[i][ansr] - sum[i][ansl - 1] > qr[i]) return 0; 
    return 1;
}
bool check2(int id, int x) {
    int l = 1, r = id, ansl, ansr;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (SA.LCP(mid, id) >= x) ansl = mid, r = mid - 1; else l = mid + 1;
    }
    l = id, r = len;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (SA.LCP(id, mid) >= x) ansr = mid, l = mid + 1; else r = mid - 1;
    }
    for (int i = 1; i <= n; ++i)
        if (sum[i][ansr] - sum[i][ansl - 1] < ql[i]) return 0;
    return 1;
}
signed main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0); 
    cin >> s >> n; len = k = s.size(); 
    for (int i = 1; i <= len; ++i) a[i] = s[i - 1]; a[++len] = ++ord;
    for (int i = 1; i <= n; ++i) {
        cin >> s >> ql[i] >> qr[i]; siz[i] = s.size(); hd[i] = len + 1;
        for (int j = 0; j < siz[i]; ++j) a[++len] = s[j]; 
        for (int j = len; j > len - siz[i]; --j) a[++len] = ++ord;
    }
    SA.init(); SA.sort(); SA.height(); SA.ST();
    for (int i = 1; i <= len; ++i) if (SA.sa[i] <= k) tag[i] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = hd[i]; j < hd[i] + siz[i]; ++j) sum[i][SA.rk[j]] = 1;
    for (int i = 1; i <= len; ++i)
        for (int j = 1; j <= n; ++j) sum[j][i] += sum[j][i - 1];
    for (int i = 1, la = 0; i <= len; ++i) {
        if (!tag[i]) continue;
        int l = (la ? SA.LCP(la, i) : 0) + 1, r = k - SA.sa[i] + 1;
        int ansl = -1, ansr = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check1(i, mid)) ansl = mid, r = mid - 1; else l = mid + 1;
        }
        l = (la ? SA.LCP(la, i) : 0) + 1, r = k - SA.sa[i] + 1; la = i;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check2(i, mid)) ansr = mid, l = mid + 1; else r = mid - 1;
        }
        if (ansl == -1 || ansr == -1) continue;
        if (ansl > ansr) continue; ans += ansr - ansl + 1;
    }    
    cout << ans; return 0;
}
```


---

## 作者：xh39 (赞：3)

## 需要用到算法:

请先学习下列算法再看本题解。

[后缀数组](www.luogu.org/problemnew/show/P3809)(建议还学一下如何求height)

[静态区间最小值(最好是rmq算法)](www.luogu.org/problemnew/show/P3865)

[前缀和](www.luogu.org/problemnew/show/P2879)

二分

注:由于本篇题解过程特别多,所以会讲得很简略。适合基础较好并对上述算法的基本应用及经典题型有一定了解的人看。

另外,如果看不懂,建议看代码,因为我也是看代码看懂的。

神犇可以直接跳过正解部分,直接看总结。(相当于概括)
## 正解
### 求出后缀数组。
首先将所有字符串拼接。为避免两个子串间互相影响,用一个从来没出现过的字符(本篇中用'```^```')如样例#1的结果就是```aaab^aa^aab^ ```

对于这个字符串,将其后缀排序,求出 $rank[]$ 及 $sa[]$\($rank[i]$ 指后缀 $[i,n-1]$ 的排名,$sa$ 是 $rank$ 的逆运算)

然后求出 $height$,其中 $height[i]$ 表示排名为i的子串与排名为 $(i-1)$ 的子串的最长公共前缀。

### 求height
这里简要讲一下如何求height,若看不懂,建议去看其他大佬的博客。

可以先求出 $h[i]$,其中 $h[i]=height[rank[i]]$。

其中h有一个性质,$h[i]>=h[i-1]-1$。关于如何证明,不详细讲~~(我自己都不会)~~,请看其他大佬的博客。

所以我们每次就先将 $h[i]=h[i-1]$,然后再往后看能否再加,就能 $O(1)$ 求出了。

### 求两个后缀的最长公共前缀
$lcp:$最长公共前缀。

排名相邻的lcp就是height。

$lcp[i][j]=min{height[k]}(i<k<=j)$。即任意两个排名相邻串的最小值。

为什么是这个值呢?一个字典序小的后缀一旦一个字母变大,就不可能变回去了。所以最长公共前缀只可能变小,不可能变大,所以是取最小值。

由于串不会改变,所以是静态区间最小值问题,可以用线段树或rmq解决。由于本题查询次数较多,建议使用rmq。
### 如何判断两个子串是否相等
假设我们要查询 $[l0,r0],[l1,r1]$ 是否相等,那么就直接查询 $lcp[l0][l1]是否>=r0=l0+1$ 即可。

即最长公共前缀是子串本身。
### 如何在$log_2$复杂度内查询串出现次数。

在本题中,我们需要查询原串中的子串在限制串中的出现次数。

由于求最长公共前缀是区间最小值,所以一定是递减的。

所以与子串相等的串排名一定是连续的。考虑求出 $[L,R]$

于是我们可以考虑二分查找。二分查找出左端点L及右端点R。

现在我们要做的就是查询这个串的后缀有多少是排名 $[L,R]$内的,可以用前缀和解决。

设 $s[i][j]$ 为第i个限制串,排名为0~j的后缀的个数。然后就可以 $O(n|t|)$ 预处理, $O(1)$ 查询了。

### 如何统计最终的答案
注:指针直接用变量解决,无需用指针。

在左端点相同的情况下,显然右端点越靠左(即串越短),串出现次数就会越多。

理由:设两个端点分别为 $r1$ 和 $r2$,且 $r1<r2$ ,则 $[l,r1]$ 一定出现在 $[l,r2]$ 中,此时如果 $[l,r2]$ 出现了,则它的子串也一定都出现了,所以 $[l,r1]$ 一定会出现。但 $[l,r1]$ 出现了,若区间 $(r1,r2]$ 不匹配,则 $[l,r2]$ 不会出现。

所以.右端点不断往右移,则出现次数一定单调递减(非严格)。由此可推出可行的右端点一定是一个区间[L,R]

那么如何得到结果,可以用与找出现次数类似的二分查找解决,但是复杂度会多乘一个 $log_{2}(n|t|)$,对于本题4s的时间限制,可能没问题,但是这样做可能会对代码的常数要求很大,而且代码也比较难写。

下面介绍一种单调队列优化的方法。

仍然要设右端点的可行区间为[L,R]。

先考虑只有一个限制的情况。

我们发现,如果左端点右移,那么右端点要么右移,要么不变。(请看上5行的解释,与此类似)

(温馨提醒:**下面请注意大小写**,大写LR代表右端点可行区间,小写lr代表原题中的限制出现次数在[l,r]中)

所以我们可以不断将右端点L往右移,直到满足出现次数<=r,也不断将R往右移,直到**不**满足出现次数>=l,注意此时可行区间是**左闭右开**区间[L,R **)**,因为R代表不可行的第一个右端点,此时小于R的都可行。

再考虑多个限制。直接开一个数组设满足第i个限制的可行区间是[L[i],R[i]]\(其它的限制可以不满足)。每次就不需要将L[i],R[i]清空,直接照着上次的枚举即可。
### 如何去重
可参考[SP705](www.luogu.org/problemnew/show/SP705)。

假设一个串的排名为 $i$,那么它与排名为 $(i-1)$ 的串有 $height[i]$ 的最长公共前缀。这部分子串就会与上个串重复,就不能算,那么$[sa[i],sa[i]+height[i]+j](i,j为任意数)$都可行。

(注:这里的 $i$ 与上句**含义不同**)所以左端点为 $i$ 时的右端点的左端点 $L$ 还要与 $sa[i]+height[i]+j$ 取最大值。
## 总结/目录
1.拼接所有字符串,中间用一个奇怪的字符间隔,防止互相影响。

2.求出后缀数组。

3.求出height。

4.求出前缀和。s[i][j]表示i子串中出现了多少rank=[0,j]的后缀。

5.rmq预处理。查询height的最小值。为查询最长公共前缀做铺垫。

6.对子串去重。具体实现可参考[SP705](https://www.luogu.com.cn/problem/SP705)。

7.快速查找出出现次数,可以用二分解决。

8.统计答案。枚举左端点,可行的右端点一定是一个区间。由于左端点向右移动,右端点也肯定向右移动。所以直接用n个指针解决每个限制串的左端点与右端点,最后的可行区间一定是左端点的最大值与右端点的最小值。注意左端点还要与不重复的左端点取最小值。
## 时间复杂度分析
本部分用的步骤序号为总结部分的步骤序号。

设 $N=sum\{\|t\|\}+\|s\|$。

|步骤编号|简述|时间复杂度|备注|
| -----------: | -----------: | -----------: | -----------: |
|1|拼接子串|$O(sum\{\|t\|\})$||  |
|2|后缀数组|$O(N)$或$O(N\times log_2(N))$|可以使用DC3优化到 $O(N)$。|
|3|height|$O(N)$||
|4|前缀和|$O(N \times n)$|需要处理 $n$ 个限制串。所以要乘以 $n$。|
|5|rmq|$O(N\times log_2(N)$|  |
|6|去重|$O(N)$|  |
|7|统计答案,查找出现次数|$O(N\times n\times log_2(N))$|有 $n$ 个指针都要移动。|
|总|  |$O(n^{2}\times \|t\|+n\times \|s\|)$|  |

由于此方法太过麻烦,似乎是全场跑得最慢的,但是还是过了。
## 代码
```cpp
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
struct xyq{ //后缀排序需要用到的桶。链表存储。
	int a,next;
}_[2000005];
int head[1000555],noi=1;
void add(int id,int a){
	_[noi].a=a;
	_[noi].next=head[id];
	head[id]=noi;
	noi++;
}
int sa[1000555],Rank[1000555][2],ran[1000555],a[1000555],tot=0,h[1000555],height[1000555],start[1000555],r_0_j[11][1000555],zyl[1000555],mi[21][1005555],lcp[1000555],log2[1000555]; //start:每个字符串的开始位置。zyl:拼接串每个字符对应哪个限制串。r_0_j:前缀和。lcp:与前一位的最长公共前缀。 
string yuan,limit[15];
int query(int l,int r){
	if(l>r){
		return 2147483647;
	}
	return min(mi[log2[r-l+1]][l],mi[log2[r-l+1]][r-(1<<log2[r-l+1])+1]);
}
int n;
int kmp(int l,int r,int x){ //limit[l]为主串,[l,r]为模式串。进行匹配,返回可以匹配出多少个。
	int lid=0,rid=ran[l],mid,lj=ran[l],rj=ran[l];
	while(lid<=rid){ //确定可行排名区间的左端点。 
		mid=lid+rid>>1;
		if(query(mid+1,ran[l])>r-l){ //如果此位置可以找得到。注意RMQ查询(mid一定要+1),因为lcp(i,j)不需要用到height[i]。
			lj=mid; 
			rid=mid-1;
		}else{
			lid=mid+1;
		}
	}
	lid=ran[l],rid=n-1;
	while(lid<=rid){ //确定可行排名区间的右端点。
		mid=lid+rid>>1;
		if(query(ran[l]+1,mid)>r-l){
			rj=mid;
			lid=mid+1;
		}else{
			rid=mid-1;
		}
	}
	return r_0_j[x][rj]-r_0_j[x][lj-1];
}
int l[1000555],r[1000555],lj[1000555],rj[1000555];
int main(){
	string s;
	cin>>s;
	start[0]=s.size();
	s=s+'^';
	int i,j,k,logn,ykb,last,sum=0,m,now,maxl,minr;
	cin>>m;
	//1.将所有限制字符串拼接,用'^'拼接两个字符串。 
	for(i=0;i<m;i++){
		cin>>limit[i]>>l[i]>>r[i];
		start[i]=s.size()-1;
		if(i==m){
			s=s+limit[i];
		}else{
			s=s+(limit[i]+'^'); //^从未出现。用其拼接两子串以保证不会互相影响。
		}
	}
	//2.求出后缀数组rank及sa。 
	n=s.size();
	start[m]=n-1;
	for(logn=0;(1<<logn)<n;logn++);
	for(i=0;i<n;i++){
		Rank[i][0]=s[i];
	}
	ykb=max(127,n<<1);
	for(i=1;i<=logn;i++){
		for(j=0;j<n;j++){//第一轮按第二关键字排序。
			add(Rank[j+(1<<i-1)][!(i&1)],j);
		}
		tot=0;
		for(j=ykb;j>=0;j--){//取桶,放入a数组。
			for(k=head[j];k;k=_[k].next){
				a[tot++]=_[k].a;
			}
		}
		noi=1;
		memset(head,0,sizeof(head));
		for(j=0;j<n;j++){ //第二轮排序,从a中的数找。
			add(Rank[a[j]][!(i&1)],a[j]);
		}
		tot=0;
		for(j=0;j<ykb;j++){
			last=0;
			for(k=head[j];k;k=_[k].next){
				if(!last||Rank[_[k].a+(1<<i-1)][!(i&1)]!=Rank[_[last].a+(1<<i-1)][!(i&1)]){
					tot++;
				}
				last=k;
				Rank[_[k].a][i&1]=tot;
			}
		}
		noi=1;
		memset(head,0,sizeof(head));
	}
	for(i=0;i<n;i++){
		ran[i]=Rank[i][logn&1]-1;
		sa[ran[i]]=i;
	}
	//-------------------------------------3.求出height。 ---------------------------------------
	j=0;
	for(i=0;i<n;i++){
		if(j){
			j--;
		}
		while(ran[i]&&s[i+j]==s[sa[ran[i]-1]+j]){
			j++;
		}
		h[i]=j;
	}
	for(i=0;i<n;i++){
		height[ran[i]]=h[i];
	}
	now=0;
	//------------------------4.求出s[i][j]表示第i个限制串,排名为0~j的后缀个数。------------------------
	memset(zyl,-1,sizeof(zyl));
	for(i=0;i<m;i++){ //zyl[i]表示后缀i属于哪个限制串。
		for(j=start[i];j<start[i+1];j++){
			zyl[j]=i;
		}
	}
	for(i=0;i<n;i++){ //枚举每个排名。
		if(sa[i]>=start[0]&&s[sa[i]]!='^'){
			r_0_j[zyl[sa[i]]][i]++;
		}
	}
	for(i=0;i<m;i++){ //枚举每个串,求前缀和。 
		for(j=1;j<n;j++){
			r_0_j[i][j]+=r_0_j[i][j-1];
		}
	}
	//-----------------------------5.rmq预处理。mi[i][j]表示j..j+pow(2,i)的最小值。------------------------------- 
	for(i=0;i<n;i++){
		mi[0][i]=height[i];
	}
	for(i=1;i<=logn;i++){
		for(j=0;j<n;j++){
			mi[i][j]=min(mi[i-1][j],mi[i-1][j+(1<<i-1)]);
		}
	}
	log2[1]=0;
	for(i=2;i<=n;i++){
		log2[i]=log2[i>>1]+1;
	}
	//----------------------------------------6.注意去重,求出与上一位的最长公共前缀,若上一位不是原串(即为限制串)中的,继续往前一位,并累计min。---------------------------------------------
	last=2147483647;
	for(i=0;i<n;i++){ //枚举排名。 
		last=min(last,height[i]); //累计min。 
		if(sa[i]<start[0]){
			lcp[i]=last;
			last=2147483647; //重置last。 
		}
	}
	//7.枚举左端点i,求出右端点j的可行区间[lj,rj]。(单调性实现)
	sum=0;
	for(i=0;i<start[0];i++){ //枚举左端点。 
		maxl=i+lcp[ran[i]];
		minr=start[0];
		for(j=0;j<m;j++){ //枚举每个限制。 
			if(lj[j]<i){ //初始化。至少要是i,否则会出问题。
				lj[j]=i;
			}
			if(rj[j]<i){
				rj[j]=i;
			}
			while(kmp(i,lj[j],j)>r[j]&&lj[j]<start[0]){ //若匹配数大于最大性质,说明串暂时不满足要求,还需再往右移。 
				lj[j]++;
			}
			while(kmp(i,rj[j],j)>=l[j]&&rj[j]<start[0]){ //若匹配数还大于最小性质,说明还可以往右移。 
				rj[j]++;
			}
			maxl=max(maxl,lj[j]); //要满足所有串的限制,所以求区间交,l取最大值,r取最小值。
			minr=min(minr,rj[j]);
		}
		if(maxl<minr){ //当L>R时,不可统计负数。
			sum+=minr-maxl; //注意,R存储的是不满足限制的第一个后缀,实际上R是不满足要求的。所以查询的是左闭右开区间,直接减,不需要加一。
		}
	}
	cout<<sum;
	return 0;
}

```

---

## 作者：yuzhechuan (赞：1)

广义后缀自动机经典题型吧

---

### 题解：

注意到$n$非常小，我们可以考虑用模式串中的所有串来一个个检验看看是否合法

考虑用广义后缀自动机进行优化

将模式串和询问串放在一起建出广义后缀自动机，然后用后缀树上的经典操作遍历一遍，累加得到每种子串在每个原串中的出现次数，然后就可以大胆地将每个节点的出现次数暴力与给出的限制比较一下看看是否合法，若合法，就加上这个节点代表的串的种类数就好啦

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=1e6+5;
int noden=1,ch[N][30],len[N],f[N],n,L[N],R[N],sz[N][15],du[N];
queue<int> q;
long long ans;
char s[N];

int insert(int k,int last){
	if(ch[last][k]&&len[last]+1==len[ch[last][k]]) return ch[last][k];
	int x=++noden,p=last,flag=0,q,copy;
	len[x]=len[last]+1;
	while(p&&!ch[p][k]) ch[p][k]=x,p=f[p];
	if(!p) f[x]=1;
	else{
		q=ch[p][k];
		if(len[p]+1==len[q]) f[x]=q;
		else{
			if(len[p]+1==len[x]) flag=1;
			copy=++noden;
			len[copy]=len[p]+1;
			for(int i=0;i<26;i++) ch[copy][i]=ch[q][i];
			f[copy]=f[q];
			f[q]=f[x]=copy;
			for(;ch[p][k]==q;p=f[p]) ch[p][k]=copy;
		}
	}
	return flag?copy:x;
}

bool check(int x){ //暴力检验
	for(int i=1;i<=n;i++) if(sz[x][i]<L[i]||sz[x][i]>R[i]) return 0;
	return 1;
}

signed main(){
	scanf("%s",s);
	for(int i=0,last=1;s[i];i++) last=insert(s[i]-'a',last),sz[last][0]=1;
	read(n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		for(int j=0,last=1;s[j];j++) last=insert(s[j]-'a',last),sz[last][i]=1;
		read(L[i]);read(R[i]);
	}
	for(int i=2;i<=noden;i++) du[f[i]]++; //我用的是拓扑来遍历一遍后缀树
	for(int i=1;i<=noden;i++) if(!du[i]) q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<=n;i++) sz[f[x]][i]+=sz[x][i]; //累加
		if(!--du[f[x]]) q.push(f[x]);
	}
	for(int i=2;i<=noden;i++) if(sz[i][0]&&check(i)) ans+=len[i]-len[f[i]]; //合法就累加该节点所代表的不同的串的种类数
	write(ans);
}
```

---

## 作者：lfxxx (赞：0)

看到本质不同子串，全部丢到广义 SAM 上。

然后你发现所有限制等价于 $endpos$ 集合中文本串的出现次数大于 $0$ 且其他串的出现次数在一个区间内。

考虑对于每个 parent 树上的等价类设计状态 $dp_{u,i}$ 表示其 $endpos$ 集合中给出的串的出现次数，那么直接在 parent 树上 dp 就可以求解，对于一个等价类再暴力判断是否满足所有要求，将其的代表的所有子串加入答案。

复杂度是 $O(len \times n)$ 这里 $len$ 是字符串长度和，字符集是为常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 4e5+114;;
struct SAM{
	int len,fa;
	int son[26];
}nd[maxn];
int tot,lst;
int dp[maxn][11];
void ins(char c){
    if(nd[lst].son[c-'a']!=0){
    	int q=nd[lst].son[c-'a'],v=lst;
        if(nd[q].len==nd[v].len+1){
        	lst=q;
        	return ;
		}
        int nq=++tot;
        lst=nq;
        nd[nq]=nd[q];
        nd[nq].len=nd[v].len+1;
        nd[q].fa=nq;
        while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
        return ;
    }
    int u=++tot,v=lst;
	nd[u].len=nd[lst].len+1;
  	lst=u;
	while(v!=0&&nd[v].son[c-'a']==0) nd[v].son[c-'a']=u,v=nd[v].fa;
	if(v==0){
        nd[u].fa=1;
        return ;
    }else{
        int q=nd[v].son[c-'a'];
        if(nd[v].len+1==nd[q].len){
            nd[u].fa=q;
            return ;
        }else{
            int nq=++tot;
            nd[nq]=nd[q];
            nd[nq].len=nd[v].len+1;
            nd[u].fa=nq;
            nd[q].fa=nq;
            while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
            return ;
        }
    }
    return ;
}
vector<int> E[maxn];
int n;
void init(){
    for(int i=2;i<=tot;i++) E[nd[i].fa].push_back(i);
    return ;
}
int ans;
int L[11],R[11];
void dfs(int u){
    for(int v:E[u]){
        dfs(v);
        for(int i=0;i<=n;i++) dp[u][i]+=dp[v][i];
    }
    for(int i=1;i<=n;i++){
        if(dp[u][i]<L[i]||dp[u][i]>R[i]||dp[u][0]==0) return ;
    }
    ans+=(nd[u].len-nd[nd[u].fa].len);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    string s;
    cin>>s;
    lst=++tot;
    for(char x:s) ins(x),dp[lst][0]++;
    cin>>n;
    for(int i=1;i<=n;i++){
        lst=1;
        string t;
        cin>>t>>L[i]>>R[i];
        for(char x:t) ins(x),dp[lst][i]++;
    }
    init();
    dfs(1);
    cout<<ans<<'\n';
    return 0;
}

```


---

## 作者：Aiopr_2378 (赞：0)

Solution of CF316G1 Good Substrings

标签：后缀数组、二分

## 题目大意

给出 $n$ 个限制，每个限制包含 $3$ 个参数 $T,l,r$, 一个字符串满足当前限制，当且仅当这个字符串在 $T$ 中的出现次数在 $[l,r]$ 之间。
    
现在给一个字符串 $S$,问 $S$ 的所有**本质不同**的子串中，有多少个满足所有限制。

两个子串本质不同，定义为两个字符串不相等。

## 解题思路

看到处理子串问题，考虑使用后缀数组。

### P1. &emsp; 进行拼合
    
一次性处理多个字符串的关系，考虑把所有串合并在一个串里，每个串中间用奇怪的字符隔开，以保证后缀排序高度数组的正确性。并记 $s$ 为原模式串，$t$ 为合并后的字符串（下面称为合并串）。

为方便表示，记 $s_{l,r}$ 表示字符串 $s$ 中第 $l$ 位开始，第 $r$ 位结束的子串。

### P2. &emsp; 关于“本质不同”

因为要找本质不同的子串，考虑后缀排序后，排名为 $i$ 的 $s$ 的后缀串，所贡献的本质不同子串为 $s_{sa_i,height_i+1},\cdots,s_{sa_i,|s|}$（均以 $sa_i$ 为开始位置）。

需要说明的是，因为对组合串进行后缀排序，事实上，排名为 $p$ 的以 $s$ 贡献来的后缀串，记它的前面最近的一个以 $s$ 贡献来的后缀串位置为 $last$。排名 $p$ 串贡献来的本质不同子串应为 $s_{sa_p,\text{LCP}(last,p)+1},\cdots,s_{sa_p,|s|}$，这是好求的。

### P3. &emsp; 发现单调性

当 $s$ 的子串的起始位置固定是，终止位置向后移动。形式化地，$s_{l,r}$ 和 $s_{l,r'}(r'>r)$ 相比，前者在所有匹配串的出现次数一定**不少于**后者(因为能和后者匹配的，一定可以和前者匹配)，也就是说，随着子串长度的不断增长，其在任意一个匹配串的出现次数**非增**。

接下来利用单调性进行二分决策。对于每个 $s$ 的排名为 $i$ 的后缀串，决策出：“最短的满足所有最大限制的子串长度”（即出现次数不大于每个限制的 $r$ 参数），记为 $L$；“最长的满足所有最大限制的子串长度”（即出现次数不少于每个限制的 $l$ 参数），记为 $R$。对答案的贡献就是 $R-L+1$。

但需要注意，每个后缀串贡献的“本质不同子串”是有限制的（上一页提到的 $s_{sa_i,height_i+1},\cdots,s_{sa_i,|s|}$），需要在二分的边界上判断并予以制约。

### P4. &emsp; 计算重复次数

枚举到排名为 $p$ 的 $s$ 的后缀串时，二分到一个值 $x$，表示：现在判断以 $sa_p$ 为起始，长度为 $x$ 的子串，是否满足所有要求。

判断其在所有限制串中出现的次数，可以利用高度数组，在其上进行二分或倍增，分别从位置 $p$ 向前和后找到最远的 $l,r$ 位置，使得 $\text{LCP}(l,r)\ge x$。这样可以求出组合串 $t$ 中所有和当前串有至少 $x$ 长度的公共前缀串。现在需要从排名为 $[l,r]$ 这些串中找到限制 $t_j$ 串的出现次数。可以记 $sum_{i,j}$ 表示排名为 $[1,j]$ 的串中，有多少个后缀串是 $t_i$ 限制带来的。利用这个前缀和，枚举 $j\in [1,n]$，计算出出现次数 $sum_{j,r}-sum_{j,l-1}$，进行判断即可。

### P5. &emsp; 复杂度分析

进行一个二分的时间复杂度为 $O(n+\log |t|)$，对于每个 $t$ 中以 $s$ 带来的后缀串，都要进行一次二分，故时间复杂度为 $O(|t|\log |t|+|s|\log |s|(n+\log |t|))$。

## 参考代码

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
#define MAXN 500005
int sa[MAXN],k,n,m,bel[MAXN],x[MAXN],y[MAXN],lstx[MAXN],c[MAXN],len;
int rnk[MAXN],height[MAXN],sum[15][MAXN];
int lim,f[35][MAXN];
long long ans;
string s,t;
struct tsk{
    int l,r;
}a[15];
void getsa(){
    m=125;
    for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
    for(int i=2;i<=m;i++) c[i]+=c[i-1];
    for(int i=n;i;i--) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1){
        int num=0;
        for(int i=n-k+1;i<=n;i++) y[++num]=i;
        for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
        for(int i=1;i<=m;i++) c[i]=0;
        for(int i=1;i<=n;i++) c[x[i]]++;
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i];
        memcpy(lstx,x,sizeof(x));
        memset(x,0,sizeof(x));
        num=1;
        x[sa[1]]=1;
        for(int i=2;i<=n;i++){
            if(lstx[sa[i]]==lstx[sa[i-1]]&&lstx[sa[i]+k]==lstx[sa[i-1]+k]) x[sa[i]]=num;
            else x[sa[i]]=++num;
        }
        m=num;
        if(m==n) break;
    }
}
void geth(){
    for(int i=1;i<=n;i++) rnk[sa[i]]=i;
    for(int j=0,i=1;i<=n;i++){
        if(rnk[i]==1) continue;
        if(j) j--;
        while(i+j<=n&&sa[rnk[i]-1]+j<=n&&s[i+j]==s[sa[rnk[i]-1]+j]) j++;
        height[rnk[i]]=j;
    }
}
bool check(int x,int p,int op){
    int up,down,l=1,r=p-1;
	if(height[p]<x) up=p;
	else{
		while(l<r){
			int mid=(l+r)>>1;
			int tg=log2(p-mid);
			if(min(f[tg][mid+1],f[tg][p-(1<<tg)+1])>=x) r=mid;
			else l=mid+1;
		}
		up=l;
	}
    l=p+1,r=n;
    if(height[p+1]<x) down=p;
    else{
        while(l<r){
            int mid=(l+r+1)>>1;
            int tg=log2(mid-p);
            if(min(f[tg][p+1],f[tg][mid-(1<<tg)+1])>=x) l=mid;
            else r=mid-1;
        }
		down=l;
    }
    for(int i=1;i<=k;i++){
        int cnt=sum[i][down]-sum[i][up-1];
        if(op==0&&cnt>a[i].r) return 0;
        if(op==1&&cnt<a[i].l) return 0;
    }
    return 1;
}
int bs_l(int l,int r,int p){
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid,p,0)) r=mid;
        else l=mid+1;
    }
    return l;
}
int bs_r(int l,int r,int p){
    while(l<r){
        int mid=(l+r+1)>>1;
        if(check(mid,p,1)) l=mid;
        else r=mid-1;
    }
    return l;
}
int main(){
	ios::sync_with_stdio(0);
    cin>>s>>k;
    len=s.length();
    for(int i=1;i<=k;i++){
        cin>>t>>a[i].l>>a[i].r;
        s+="*"+t;
    }
    n=s.length();
    s=" "+s;
    for(int now=0,i=1;i<=n;i++){
        if(s[i]=='*') now++,bel[i]=-1;
        else bel[i]=now;
    }
    getsa();
    geth();
    lim=log2(n);
    for(int i=1;i<=n;i++) f[0][i]=height[i];
    for(int i=1;i<=lim;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++) sum[j][i]=sum[j][i-1];
        if(bel[sa[i]]!=-1) sum[bel[sa[i]]][i]++;
    }
    for(int minn=0x3f3f3f3f,i=1;i<=n;i++){
        minn=min(minn,height[i]);
        if(bel[sa[i]]!=0) continue;
        int l=bs_l(minn+1,len-sa[i]+2,i);
        int r=bs_r(minn+1,len-sa[i]+1,i);
		minn=0x3f3f3f3f;
		if(!check(l,i,0)||!check(r,i,1)) continue;
        if(l>r) continue;
        ans+=r-l+1;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Paracelestia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF316G1)

## $\texttt{Solution}$

$|S| \leq 200$，看到这个数据范围，直接上哈希乱搞。

存下每个限制串中每个子串的出现次数，再枚举文本串子串累计答案，详见代码。

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;

#define fi first
#define se second

const int N = 1e4 + 10;
const int M = 1e6 + 10;

template<typename T> inline T read() {
    T x = 0, f = 1; char ch = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch - '0');
    return x * f;
}

template<typename T> inline void write(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T> inline void print(T x, char ed = '\n') {
    write(x), putchar(ed);
}

const int p = 1145141;

string s;
int n, l[N], r[N], ans;
ull hsh[N], pn[N];
unordered_map<ull, int> hst[11];
unordered_map<ull, bool> vis;

signed main() {
    cin >> s >> n;
    for(int i = pn[0] = 1; i < N; ++ i) pn[i] = pn[i - 1] * p;
    // 存限制串子串
    for(int k = 1; k <= n; ++ k) {
        string t; cin >> t >> l[k] >> r[k];
        int m = t.length(); t = ' ' + t;
        for(int i = 1; i <= m; ++ i) hsh[i] = hsh[i - 1] * p + t[i];
        for(int len = 1; len <= m; ++ len) {
            for(int i = 1; i + len - 1 <= m; ++ i) {
                ull x = hsh[i + len - 1] - hsh[i - 1] * pn[len];
                hst[k][x] ++;
            }
        }
    }
    // 枚举文本串子串
    int m = s.length(); s = ' ' + s;
    for(int i = 1; i <= m; ++ i) hsh[i] = hsh[i - 1] * p + s[i];
    for(int len = 1; len <= m; ++ len) {
        for(int i = 1; i + len - 1 <= m; ++ i) {
            ull x = hsh[i + len - 1] - hsh[i - 1] * pn[len];
            if(vis[x]) continue;
            vis[x] = 1; // 记得是本质不同！
            bool f = 0;
            for(int j = 1; j <= n; ++ j) 
                if(hst[j][x] < l[j] || hst[j][x] > r[j]) 
                	{ f = 1; break; }
            if(!f) ans ++;
        }
    }
    print(ans);
    return 0;
}
```

## $\texttt{Appendix}$

~~本人 G2 卡了很久始终 MLE on #15，望有识之士能够教教怎么卡过~~

---

