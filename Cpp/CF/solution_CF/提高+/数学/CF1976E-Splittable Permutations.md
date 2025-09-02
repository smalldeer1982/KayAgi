# Splittable Permutations

## 题目描述

Initially, we had one array, which was a permutation of size $ n $ (an array of size $ n $ where each integer from $ 1 $ to $ n $ appears exactly once).

We performed $ q $ operations. During the $ i $ -th operation, we did the following:

- choose any array we have with at least $ 2 $ elements;
- split it into two non-empty arrays (prefix and suffix);
- write two integers $ l_i $ and $ r_i $ , where $ l_i $ is the maximum element in the left part which we get after the split, and $ r_i $ is the maximum element in the right part;
- remove the array we've chosen from the pool of arrays we can use, and add the two resulting parts into the pool.

For example, suppose the initial array was $ [6, 3, 4, 1, 2, 5] $ , and we performed the following operations:

1. choose the array $ [6, 3, 4, 1, 2, 5] $ and split it into $ [6, 3] $ and $ [4, 1, 2, 5] $ . Then we write $ l_1 = 6 $ and $ r_1 = 5 $ , and the arrays we have are $ [6, 3] $ and $ [4, 1, 2, 5] $ ;
2. choose the array $ [4, 1, 2, 5] $ and split it into $ [4, 1, 2] $ and $ [5] $ . Then we write $ l_2 = 4 $ and $ r_2 = 5 $ , and the arrays we have are $ [6, 3] $ , $ [4, 1, 2] $ and $ [5] $ ;
3. choose the array $ [4, 1, 2] $ and split it into $ [4] $ and $ [1, 2] $ . Then we write $ l_3 = 4 $ and $ r_3 = 2 $ , and the arrays we have are $ [6, 3] $ , $ [4] $ , $ [1, 2] $ and $ [5] $ .

You are given two integers $ n $ and $ q $ , and two sequences $ [l_1, l_2, \dots, l_q] $ and $ [r_1, r_2, \dots, r_q] $ . A permutation of size $ n $ is called valid if we can perform $ q $ operations and produce the given sequences $ [l_1, l_2, \dots, l_q] $ and $ [r_1, r_2, \dots, r_q] $ .

Calculate the number of valid permutations.

## 样例 #1

### 输入

```
6 3
6 4 4
5 5 2```

### 输出

```
30```

## 样例 #2

### 输入

```
10 1
10
9```

### 输出

```
1814400```

## 样例 #3

### 输入

```
4 1
2
4```

### 输出

```
8```

# 题解

## 作者：DE_aemmprty (赞：5)

## $\textup{Part 1. }$

看题，发现你要对排列计数。我们发现这个操作比较不一般，所以我们可以考虑手玩一下操作，对这个操作有一个基本的概念，并尝试观察性质。

这道题比较简单，我们在手玩操作后，容易发现，操作的含义其实就是：对于一个排列，有若干个区间，每个区间的最大值是固定的。因此，我们在对这个 $l, r$ 算出对应区间的最大值之后，我们就可以完成第一步的转换。

**进展 1：我们将题目转换成计数这样的排列：有若干个区间，每个区间的最大值是固定的。**

## $\textup{Part 2. }$

我们发现，现在这道题感觉可以通过简单的乘法原理解决。但是，我们如果从小到大插入元素，我们发现并不是很好做：在计算后面的元素时，我们不知道可插入的位置个数。

我们思考失败的原因。我们发现，如果将区间大小的 $\max$ 值从小到大排序，那么，每个数 $x$ 可以放置的区间位置为一个后缀，因此，我们从小往大插入显然不太合理。

因此，我们可以考虑从大往小插入。这样的话，我们发现，每次插入数的数量一定是固定的。因此，此题得解。

```cpp
void solve() {
    n = read(), q = read();
    for (int i = 1; i <= q; i ++)
        l[i] = read(), tmp[i] = l[i];
    for (int i = 1; i <= q; i ++)
        r[i] = read(), tmp[i + q] = r[i];
    sort(tmp + 1, tmp + 2 * q + 1);
    m = unique(tmp + 1, tmp + 2 * q + 1) - tmp - 1;
    pos[l[1]] = ++ tot;
    t[tot].v = l[1];
    for (int i = 1; i <= q; i ++) {
        int now = pos[l[i]] + pos[r[i]];
        // printf("now = %d\n", now);
        if (!pos[l[i]]) {
            pos[l[i]] = ++ tot;
            t[tot].v = l[i];
            t[tot].l = t[now].l;
            t[tot].r = now;
            t[t[now].l].r = tot;
            t[now].l = tot;
        } else {
            pos[r[i]] = ++ tot;
            t[tot].v = r[i];
            t[tot].l = now;
            t[tot].r = t[now].r;
            t[t[now].r].l = tot;
            t[now].r = tot;
        }
    }
    int now = 1, id = 1;
    while (t[now].l) now = t[now].l;
    while (now) {
        b[id] = t[now].v;
        pos[t[now].v] = id;
        now = t[now].r;
        id ++;
    }
    // for (int i = 1; i <= tot; i ++)
    //     cout << b[i] << ' ';
    // cout << '\n';
    long long ans = 1;
    init();
    for (int i = n, j = m; i >= 1; i --) {
        while (j >= 1 && i < tmp[j]) {
            siz ++;
            if (pos[tmp[j]] > 1 && b[pos[tmp[j]] - 1] > tmp[j])
                siz --;
            if (pos[tmp[j]] < m && b[pos[tmp[j]] + 1] > tmp[j])
                siz --;
            j --;
        }
        if (tmp[j] == i) continue;
        (ans *= (n - i + siz)) %= mod;
    }
    cout << ans << '\n';
}
```

---

## 作者：yshpdyt (赞：5)

## 题意
对于一个数组，每次遵守以下规则将其分成两个数组：
- 大小至少为 $2$。
- 从某个位置分开，左边的最大值记作 $l_i$，右边最大值记作 $r_i$ 。

给定你操作次数 $q$ ，以及 $l,r$ 数组，求满足题意的初始长度为 $n$ 的排列数量。
## Sol
模拟切割操作，发现可以确定出现元素的相对顺序，具体来说就是 $l_i$ 出现在 $r_i$ 左边，根据题目的分割的性质，若 $i<j$，满足 $r_i=r_j$，一定有 $l_i$ 在 $l_i$ 左边，可以考虑用链表维护其相对顺序。

接下来考虑插入未确定的元素，由于每次切割有最大值的限制，插入 $x$ 必须插入在比它大的元素旁边，这样才能保证切割后，不会影响到另一边的最大值。

由于随着 $x$ 的减小，比它大的元素的增多，具有单调性，更具体来说，满足前缀和。

不妨设 $f_x$ 表示 $x$ 能放的缝隙数量，考虑每个缝隙，让其贡献放到较大的位置上，这是因为当 $a_{i+1}<x<a_i$，这个缝隙已经可以放元素了，记 $g_x$ 表示放完 $x$ 后增加的可以多放位置数。

对于在链表中的 $a_i$，$g_{a_i}=[a_i>a_{i-1}]+[a_i>a_{i+1}]$。

对于不在链表中的 $x$，$g_x=1$，因为 $x$ 必须放在 $y>x$ 的旁边，$y$ 旁边的位置统计过了，增加的位置在 $x$ 右边。

答案就是：
$$f_x=f_{x+1}+g_{x+1}$$
$$res=\prod_{x\notin a}f_x$$

时间复杂度 $O(n)$ 。

~~感觉描述的好抽象。~~
##  Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=998244353;
const ll inf=1e18;
const double eps=1e-6; 
ll n,m,l[N],r[N];
ll a[N],x[N],y[N],cnt[N];
vector<ll>v;
void sol(){
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>x[i];
    for(int i=1;i<=m;i++)cin>>y[i];
    l[x[1]]=0;
    r[0]=x[1];
    a[x[1]]=x[1];
    for(int i=1;i<=m;i++){
        if(a[x[i]]){
            a[y[i]]=y[i];
            r[y[i]]=r[x[i]];
            l[y[i]]=x[i];
            l[r[x[i]]]=y[i];
            r[x[i]]=y[i];
        }else{
            a[x[i]]=x[i];
            r[x[i]]=y[i];
            l[x[i]]=l[y[i]];
            r[l[y[i]]]=x[i];
            l[y[i]]=x[i];
        }
    }
    for(int j=r[0];j;j=r[j])v.push_back(j);
    cnt[v[0]]=1,cnt[v.back()]=1;
    for(int i=1;i<v.size();i++)cnt[max(v[i],v[i-1])]++;
    ll res=1,ans=0;
    for(int i=n;i>=1;i--){
        if(!a[i]){
            res=res*ans%mod;
            ans=(ans+1)%mod;
        }
        ans=(ans+cnt[i])%mod;
    }
    cout<<res<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt=1;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：CCPSDCGK (赞：4)

既然题目给出了 $l_i,r_i$，那么相当于 $l_i,r_i$ 在排列中的顺序一定是 $l_i$ 先于 $r_i$。

我们称一个在 $\{l_i\},\{r_i\}$ 中出现过的数称为“固定数”，否则为“自由数”。

容易根据这 $q$ 个条件能推出固定数的相对顺序或判断无解。

具体做法是倒序合并，每次选择两个数所在的子段然后按序合并。这其实就是链表合并，需要额外用并查集维护。

求出相对顺序后，接下来需要往里面插“自由数”，其实我们可以规定“自由数”自始至终跟着那个“固定数”
一起走下去，具体的，对于两个相邻的“固定数” $x,y$，若 $z$ 能插入到这两个数之间，那只需要满足 $z<\max(x,y)$ 即可，这样让 $z$ 只需要跟着最大值一路闯天涯即可。

所以只需要大往小插，可插的空永远只多不少，答案就是所有可插缝隙数量相乘。

时间复杂度：$O(n)$

```cpp
int fa[300005],l[300005],r[300005],vl[300005],vr[300005],pre[300005],nxt[300005],cnt[300005];
bool vis[300005];
int find(int x){
	if(fa[x]==x) return x;
	int t=find(fa[x]);
	fa[x]=t,vl[x]=vl[t],vr[x]=vr[t];
}
int main(){
	int n,q;cin>>n>>q;
	vis[n]=1;
	for(int i=1;i<=q;i++) cin>>l[i];
	for(int i=1;i<=q;i++) cin>>r[i];
	for(int i=1;i<=q;i++){
		if(vis[min(l[i],r[i])]||!vis[max(l[i],r[i])]) return cout<<0,0;
		vis[min(l[i],r[i])]=1;
	}
	for(int i=1;i<=n;i++) fa[i]=vl[i]=vr[i]=i;
	for(int i=q;i;i--){
		int x=find(l[i]),y=find(r[i]);
		fa[x]=y,nxt[vr[x]]=vl[y],pre[vl[y]]=vr[x],vl[y]=vl[x],vr[x]=vr[y];
	}
	int x=vl[find(n)];cnt[x]++;
	while(x) cnt[max(nxt[x],x)]++,x=nxt[x];
	int ans=1,mul=0;
	for(int i=n;i;i--){
		mul+=cnt[i];
		if(!vis[i]) ans=(ll)ans*mul%mod,mul++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

有一个长度为 $n$ 的排列 $p$，初始为一段，对其进行 $m$ 次操作：

- 选择一段，从中间切开变成两段。

给出每次操作后左右两段的最大值，求可能的初始排列数量。

## 题目分析

显然可以根据每次的操作模拟出最后从左到右每一段的最大值。这里我采用建树的方法，叶子节点为当前的段的最大值，然后操作就在对应位置新建两个儿子，最后叶子的 dfs 序就代表了从左往右的顺序。

然后就很简单，考虑一个序列，元素依次为这些最大值，然后把没出现的元素插入，插入一个空的前提是小于相邻的最大值中最大的一个，直接模拟可以插的空即可，复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repm(x) rep(x,1,m)
#define pb push_back
#define E(x) for(auto y:p[x])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=1e6+5,mod=998244353;
inline void Mul(int &a,int b){a=1LL*a*b%mod;}
int n,m,a[N],b[N],tot,Id[N],ps[N],s[N],tp,c[N],ct[N],Sum,ans=1;
vector<int>p[N];
bool v[N];
inline void dfs(int x){
	if(!p[x].size())s[++tp]=Id[x],v[Id[x]]=1;
	E(x)dfs(y);
}
signed main(){
	n=read(),m=read(),ps[n]=++tot,Id[tot]=n;
	repm(i)a[i]=read();
	repm(i)b[i]=read();
	repm(i){
		int x=a[i]>b[i]?ps[a[i]]:ps[b[i]];
		ps[a[i]]=++tot,p[x].pb(tot),Id[tot]=a[i];
		ps[b[i]]=++tot,p[x].pb(tot),Id[tot]=b[i];
	}
	dfs(1);
	rep(i,0,tp)ct[max(s[i],s[i+1])]++;
	per(i,n,1){
		Sum+=ct[i];
		if(!v[i])Mul(ans,Sum),Sum++;
	}
	cout <<ans<<'\n';
	return 0;
}
```

---

## 作者：__Louis__ (赞：1)

## 题解：CF1976E Splittable Permutations

### 题目描述

定义一次操作是把一个序列分成两个非空子序列，然后把他放到整个序列的集合之中。

这次操作的 $l_i$ 是左边序列的最大值，$r_i$ 是右边序列的最大值。

现在给定你 $l_i$ 和 $r_i$，求有多少种 $1 \sim n$ 的排列可以找到一种操作方式满足给定的条件。

### 思路

首先可以发现，我们可以确定最终整个序列中每一个序列的最大值。

如果要把一个序列分成两份，就可以插入一个新的节点，最终会形成一个双端队列。

然后考虑如何把剩下的数加进来。

对于一个没有加进来的数，它可以插入的地方当且仅当旁边两个数有一个比他大，这样就可以跟着一个“大哥”一直走下去。

插入每个数的时候把答案相乘，利用乘法原理，但是如何使得答案更大？

再发现一点，如果 $x$ 越小，那么其可以插入的缝隙就越多，所以我们考虑从大往小插入即可。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int maxn=3e5+10;
int nxt[maxn],pre[maxn];
bool b[maxn];
struct node{
	int x,y;
}arr[maxn];
int da[maxn];
signed main(){
	int n,q;
	scanf("%lld%lld",&n,&q);
	b[n]=true;
	nxt[n]=n+1;
	pre[n+1]=n;
	nxt[0]=n;
	pre[n]=0;
	for(int i=1;i<=q;i++){
		scanf("%lld",&arr[i].x);
	}	
	for(int i=1;i<=q;i++){
		scanf("%lld",&arr[i].y); 
	}
	for(int i=1;i<=q;i++){
		if(b[arr[i].x]){
			b[arr[i].y]=true;
			int k=nxt[arr[i].x];
			nxt[arr[i].y]=k;
			pre[k]=arr[i].y;
			nxt[arr[i].x]=arr[i].y;
			pre[arr[i].y]=arr[i].x;
		}else{
			b[arr[i].x]=true;
			int k=pre[arr[i].y];
			nxt[k]=arr[i].x;
			pre[arr[i].x]=k;
			nxt[arr[i].x]=arr[i].y;
			pre[arr[i].y]=arr[i].x;
		}
	}
	int p=nxt[0];
	da[p]++;
	while(nxt[p]!=n+1){
		int k=nxt[p];
		da[max(k,p)]++;
		p=nxt[p];
	}
	p=pre[n+1];
	da[p]++;
	int res=0,ans=1;
	for(int i=n;i>=1;i--){
		res+=da[i];
		if(!b[i]){
			ans=ans*res%mod;
			res++;
		}
	}
	printf("%lld",ans);
} 
```

---

## 作者：Alex_Wei (赞：0)

### [CF1976E Splittable Permutations](https://www.luogu.com.cn/problem/CF1976E)

通过链表实时维护每个序列的最大值。初始链表仅有一个元素 $1$。对于一次操作 $l, r$，因为题目保证合法，所以较大值一定在序列里。若 $l > r$，则在 $l$ 后面插入 $r$，否则在 $r$ 前面插入 $l$。这给出了所有涉及到的元素的相对顺序。

目前，操作涉及到的元素单独形成一个序列，且一定是这个序列的最大值。对于其它元素 $x$，按限制从严格到不严格考虑，即按值从大到小考虑。设最大值大于 $x$ 的序列个数为 $c$，则 $x$ 共有 $(n - x) + c$ 个插入方案：$n - x$ 表示插在某个 $x + 1\sim n$ 左边，$c$ 表示插在某个最大值大于 $x$ 的序列的最右边。

但如果两个最大值大于 $x$ 的序列相邻，那么插在左侧序列的最右边和插在某个 $x + 1\sim n$ 左边是相同的方案，因此实际方案数为 $(n - x) + d$，其中 $d$ 表示最大值大于 $x$ 的序列形成的极长段个数。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1976/submission/265705046)。

---

