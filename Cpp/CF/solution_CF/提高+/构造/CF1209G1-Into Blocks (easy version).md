# Into Blocks (easy version)

## 题目描述

这是下一个问题的简化版本。在本题中，$q = 0$。

如果一个整数序列的元素被分成若干块排列，如 $[3, 3, 3, 4, 1, 1]$，则称该序列为“优美序列”。形式化地说，如果两个元素相等，则它们之间的所有元素也必须相等。

我们定义一个序列的“难度”为：将其变为优美序列所需最少修改元素的数量。然而，如果你将某个值为 $x$ 的元素改为 $y$，那么你必须将所有值为 $x$ 的元素都改为 $y$。例如，对于 $[3, 3, 1, 3, 2, 1, 2]$，你不能只将第一个 $1$ 改为 $3$，第二个 $1$ 改为 $2$。你要么都不动 $1$，要么把所有 $1$ 都改成同一个值。

给定一个整数序列 $a_1, a_2, \ldots, a_n$ 和 $q$ 次操作。

每次操作为“$i$ $x$”——将 $a_i$ 改为 $x$。操作是累积的（即更改会影响后续操作）。

请输出初始序列和每次操作后序列的难度。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 0
3 7 3 7 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 0
1 2 1 2 3 1 1 1 50 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
6 0
6 6 3 3 4 4
```

### 输出

```
0
```

## 样例 #4

### 输入

```
7 0
3 3 1 3 2 1 2
```

### 输出

```
4
```

# 题解

## 作者：Eddie08012025 (赞：7)

# CF1209G1 Into Blocks (easy version)
## 性质
对于有 $n$ 个数的数组 $a_i$，若无法将其切成两段使左边与右边的颜色完全不相同，为了满足条件，必须把所有颜色都改为同样的一种颜色，最小操作次数是该数组的众数。

简单证明：因为初始颜色一样的，无论如何操作，都还会保持相同的颜色，因为无法将其切成两段使左边与右边的颜色完全不相同，所以可以发现这一性质。

## 做法
将数组分成尽可能多的几段，让这几段中使任意两段的颜色完全不相同。可以先记录每一种颜色出现的最晚的位置，然后用差分就可以完成这一步，代码中进一步说明。

然后分别统计每一段的众数，相加，再用 $n$ 减去其即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,anss,ans,z[200001],p[200001],maxn,l[200001],vis[200001],o;
vector<int>v;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>z[i];
		maxn=max(maxn,z[i]);
		p[z[i]]=i;
		l[z[i]]++;
	}for(int i=1;i<=n;i++){
		//以下是差分的过程，ans统计众数，o表示该点有多少个区间覆盖，这里的区间指颜色第一个出现的位置到颜色最后一个出现的位置构成的区间
        if(!vis[z[i]])vis[z[i]]=1,o++,ans=max(ans,l[z[i]]);
		if(i==p[z[i]])vis[z[i]]=0,o--;
		if(!o){//当o归零时，这就是一段
			anss+=ans;
			ans=0;
		}
	}if(!o){
		anss+=ans;
		ans=0;
	}cout<<n-anss;
	return 0;
}


```

---

## 作者：Eibon (赞：7)

容易发现，在遍历时，如果两种数字相交，必然要消去其中一种。

不妨将每个数出现的最后位置 $pos_{i}$ 与每个数的出现次数 $sum_{i}$ 预处理出来。

接下来在遍历中遇见一个新数字，就将这个数字全部加入到区间中，统计出众数并让计数器 $ans$ 加上，最后的答案即操作次数就是 $n-ans$。因为显然在一段操作中留下区间众数是为最优的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int n,q,cnt,now,num,ans;
int a[maxn],sum[maxn],pos[maxn];
signed main()
{
    scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		pos[a[i]]=i;
		sum[a[i]]++;
	}
	for(int i=1;i<=n;){
		now=i;num=0;
		while(now>=i){
			now=max(now,pos[a[i]]);
			num=max(num,sum[a[i]]);
			i++;
		}
		ans+=num;
	}
	printf("%lld\n",n-ans);
    return 0;
}
//dyyyyds
```

---

## 作者：_soul_ (赞：4)

你对于每一个元素处理处一个l一个r，显然如果两个元素lr所代表的区间有交点，那么必然这两个元素在最后不能共存。

那么你只要用set维护一个元素的个数从小到大，每次将一个出现次数最小的元素，并且他们lr有交，把小的并 上去就行了，并完之后同时更新set。

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,q,dis[N],m,ans=0;
int a[N];
struct zero {
	int l,r,x;
	bool operator < (const zero& a) const {
		return l<a.l;
	}
} lib[N];
set<int> st[N];
set<int>::iterator it;
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; i++) {
		scanf("%d",a+i);
		dis[++m]=a[i];
	}
	sort(dis+1,dis+m+1);
	m=unique(dis+1,dis+m+1)-dis-1;
	for(int i=1; i<=n; i++) {
		a[i]=lower_bound(dis+1,dis+m+1,a[i])-dis;
		st[a[i]].insert(i);
	}
	for(int i=1; i<=m; i++) {
		lib[i].l=*st[i].begin();
		it=st[i].end();
		--it;
		lib[i].r=*it,lib[i].x=st[i].size();
	}
	sort(lib+1,lib+m+1);
	int maxn=0,pos=0;
	for(int i=1; i<=m; i++) {
		maxn=max(maxn,lib[i].r);
		if(i==m||lib[i+1].l>maxn) {
			int tmp=0;
			for(int r=pos+1; r<=i; r++) {
				tmp=max(tmp,lib[r].x);
				ans+=lib[r].x;
			}
			ans-=tmp,pos=i,maxn=0;
		}
	}
	printf("%d\n",ans);
}

```


---

## 作者：皎月半洒花 (赞：3)

感觉这个 G1 还是比较 naive 的？找个性质这题就没了。

大概做题时有这么几个 Observation，当时拿笔写了下来，感觉应该是比较正常思路：

1、答案上界一定是 $n-\max \{col{\rm num}\}$ .

2、如果一个颜色存在不相邻，那么要么会被全部涂成别的颜色，要么会被保留。

3、根据 $2$ 不难发现，一段交错排布的元素最后必然只会保留一种颜色。

4、根据 $3$ 可以得到一个贪心：将所有颜色按照出现次数从大到小排序。一开始预处理出所有颜色第一次出现的位置 $s_i$ 和最后一次出现的位置 $t_i$，那么不难看出要把 $[s_i,t_i]$ 之间的元素都涂成当前颜色。不难知道这样是最优的。

然后实现上遇上了一点小阻碍。大概就是说随着不停地染色，可能会有一些别的颜色被染成当前颜色，这样就要动态更新当前颜色的 $s_i$ 和 $t_i$ 。然后就因为觉得这个不好维护就摸了一会儿…结果发现其实是很好维护的。具体来说，从大到小做一定可以让每个点至多被染一次色，复杂度可以保证；同时发现 $[s_i,t_i]$ 分别满足单调性，就可以暴力 `while` 做了。

最后复杂度显然排序外线性。

```cpp
 
int ans ;
int cnt ;
int n, q ;
int buc[N] ;
int fst[N] ;
int lst[N] ;
int vis[N] ;
int base[N] ;
pint ord[N] ;
vint pos[N] ;
 
#define m_k make_pair
 
bool comp(pint a, pint b){
    return a.fr == b.fr ? a.sc < b.sc : a.fr > b.fr ;
}
 
int main(){
    cin >> n >> q ; int x, y ;
    for (int i = 1 ; i <= n ; ++ i)
        base[i] = qr(), buc[base[i]] ++ ;
    for (int i = 1 ; i <= n ; ++ i)
        pos[base[i]].push_back(i) ;
    for (int i = 1 ; i <= n ; ++ i)
        if (!fst[base[i]]) fst[base[i]] = i ;
    for (int i = n ; i >= 1 ; -- i)
        if (!lst[base[i]]) lst[base[i]] = i ;
    for (int i = 1 ; i <= 200000 ; ++ i)
        if (buc[i]) ord[++ cnt] = m_k(buc[i], i) ;
    sort(ord + 1, ord + cnt + 1, comp) ;
    for (int i = 1 ; i <= cnt ; ++ i){
        x = ord[i].fr ; y = ord[i].sc ;
        if (vis[y]) continue ; vis[y] = 1 ;
        if (x == lst[y] - fst[y] + 1) continue ;
        int l = fst[y], r = lst[y] ;
        for (int p = fst[y] ; p <= lst[y] ; ++ p){
//            printf("%d ", p) ;
            if (base[p] != y && !vis[base[p]]){
                vis[base[p]] = 1 ;
//                printf("%d ", base[p]) ;
                for (auto k : pos[base[p]]){
                    chkmin(l, k) ;
                    chkmax(r, k) ;
                    base[k] = y, ++ ans ;
                }
            }
//            puts("") ;
        }
//        printf("%d %d\n", l, r) ;
        while (1){
            int tl, tr ;
//            printf("%d %d\n", l, r) ;
            tl = fst[y], tr = lst[y] ;
            if (l == fst[y] && r == lst[y]) break ;
            fst[y] = l, lst[y] = r ;
            for (int p = tl - 1 ; p >= l ; -- p){
//                printf("(%d %d %d)", p, base[p], vis[base[p]]) ;
                if (base[p] != y && !vis[base[p]]){
                    vis[base[p]] = 1 ;
//                    printf("%d ", base[p]) ;
                    for (auto k : pos[base[p]]){
                        chkmin(l, k) ;
                        chkmax(r, k) ;
                        base[k] = y, ++ ans ;
                    }
                }
//                puts("") ;
            }
            for (int p = tr + 1 ; p <= r ; ++ p){
                if (base[p] != y && !vis[base[p]]){
                    vis[base[p]] = 1 ;
                    for (auto k : pos[base[p]]){
                        chkmin(l, k) ;
                        chkmax(r, k) ;
                        base[k] = y, ++ ans ;
                    }
                }
            }
        }
//        debug(base, 1, n) ;
//        printf("%d %d %d %d %d\n", x, y, fst[y], lst[y], ans) ;
    }
    printf("%d\n", ans) ;
    return 0 ;
}
```

把最后一个 for 里 if 的 `y` 写成了 `x` 导致 `Wa On 7` 呜呜呜。

# 

---

## 作者：PosVII (赞：2)

**前言**

------------

hard 不错。

这个题相当于是对你 G2 做法的一个极大提示和对思路正确性的确定，所以还是很重要的。

**思路**

------------

考虑一个极其显然的思路，答案在最终一定会转化成如下形式：

```1 1 1 2 2 3 3 3```

形如一段段连续的数字拼起来。考虑如下数列：

```1 2 1 1 2 3```

于是我们先从 $1$ 开始往右找，我们发现当把一取完时，我们取到了这一段：

```1 2 1 1```

但是 $2$ 没取完，于是继续取直到把 $2$ 取完：

```1 2 1 1 2```

此时这个段就已经可以在修改后作为答案加入答案里了，而且直接这么做是一定最优的，考虑证明：


如果该段要加入答案，那么实际上的代价是该段数字总数减去该段众数的出现次数，这个不难证。

那么我们发现两段的众数数量显然是比一整段的众数数量更大的，于是可以贪心地嗯（硬）取。

暴力模拟即可。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
template<typename G> inline void read(G &x) {x=0;G f=1;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') {x=x*10+(ch^48);ch=getchar();}x*=f;}
const int MAXN=2e5+5;
int n,q;
int a[MAXN],R[MAXN],sum[MAXN];
signed main() {
	read(n),read(q);
	for(int i=1;i<=n;++i) read(a[i]),R[a[i]]=i,++sum[a[i]];
	int i=1,ans=0;
	while(i<=n) {
		int mxr=i,mxs=0;
		while(i<=mxr) {
			mxs=max(mxs,sum[a[i]]);
			mxr=max(mxr,R[a[i]]);
			++i;
		}
		ans+=mxs;
	}
	printf("%d",n-ans);
	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

首先两个相同的元素无论怎么操作都是相同的。假设 $a_l=a_r$，那么 $[l,r]$ 区间都得是 $a_l$ 这个数才是合法的。

这意味着出现区间（即第一次出现到最后一次出现）存在交集的数一定会合并。其他的就不合并。

合并一次会加上当前数的个数。除了最终变成的数不会操作，其他的数都得操作一遍，贪心考虑就不要让次数最多的合并，其余的合并上去即可，也就是 $\sum c_i-\max c_i$。

按左端点排序一下，遍历一遍维护一堆要合并的数即可。

```cpp
sort(f + 1, f + 1 + c);
for (int i = 1; i <= c; i++) {
	if (f[i].l < r) {
		m = max(m, f[i].c);
		s += f[i].c;
		r = max(r, f[i].r);
	} else {
		ans += s - m;
		l = f[i].l, r = f[i].r;
		m = s = f[i].c;
	}
}
ans += s - m;
 ```

---

## 作者：maxyzfj (赞：0)

### 题目分析

首先，我们发现了一个结论，在原序列中，如果存在 $1\le l<r\le n$ 使得 $a_l=a_r$，那么在最终的序列中，区间 $[l,r]$ 里面所有元素的值必然相等。这是因为无论怎么修改，都有 $a_l=a_r$，而由题意，我们要让等于 $a_l$ 的元素在序列中出现的位置连续，因此只能让 $[l,r]$ 中的元素都相等。

这样，我们就可以得到若干个区间，满足其内部的元素都相等，于是我们可以自然地想到可以用并查集维护相等关系（即若两个元素在最终的序列中相等，则将其所在的集合合并）。

接下来考虑统计答案：对于每个集合，它包含的数应当对应序列上一段连续的区间，它包含的数在操作之后需两两相等，那么为了让代价最小，只需使此数等于最初序列中这个集合中元素的众数即可。那么此区间的代价就是区间长度减去区间众数个数，而区间众数个数用桶统计即可。

### 算法优化

上述做法如果暴力合并，则可能会被卡成 $O(n^2)$（这是因为两区间包含或相交时，可能会发生不必要的合并，即合并两个本已在同一集合的元素）。因此我们需要一些优化：

1. 将需要合并的区间按照长度从大到小排序，这样如果出现了相互包含的区间，可以减少不必要的合并。

1. 合并时记录每个集合对应区间的左端点和右端点，这样在合并某个区间内的元素时，可以直接从当前未合并的位置开始合并。

进行完上述的两个优化，那么每两个相邻的元素最多只会合并 $1$ 次，时间复杂度为排序所需的 $O(n\log n)$，足以通过此题。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define mp(x,y) make_pair(x,y)
#define lb(x) (x&(-x))
#define fi first
#define se second
int read(){
	int x=0,f=1;
    char ch=getchar();
	while (ch<'0'||ch>'9'){
    	if (ch=='-') f=-1;ch=getchar();
    }
	while (ch>='0'&&ch<='9'){
    	x=x*10+ch-48;ch=getchar();
    }
	return x*f;
}
void writ(int x){
    if(x<0){
		putchar('-'),x=-x;
	}
    if(x>9){
		writ(x/10);
	}
    putchar(x%10 +'0');
}
void write(int x,char p=' '){
    writ(x);
    putchar(p);
}
string sread(){
    string t="";
    char c=getchar();
    while(c==' '||c=='\t'||c=='\r'||c=='\n'||c==0||c==EOF){
        c=getchar();
    }
    while(!(c==' '||c=='\t'||c=='\r'||c=='\n'||c==0||c==EOF)){
        t+=c,c=getchar();
    }
    return t;
}
const int MOD=1000000007,mod=998244353,inf=2e18+31,N=2e5+5;
int fa[N],siz[N],n,q,a[N],cnt[N];
int get(int x){
	if(x==fa[x]){
		return x;
	}
	return fa[x]=get(fa[x]);
}
void merge(int x,int y){
	x=get(x);
	y=get(y);
	if(x==y){
		return;
	}
	if(siz[x]<siz[y]){
		swap(x,y);
	}
	fa[y]=x;
	siz[x]+=siz[y];
}
struct node{
	int l,r;
}b[N];
int L[N],R[N];
bool operator<(const node a,const node b){
	if(a.r-a.l==b.r-b.l){
		return a.l>b.l;
	}
	return a.r-a.l>b.r-b.l;
}
int work(int l,int r){
	int ret=0;
	for(int i=l;i<=r;i++){
		cnt[a[i]]++;
		ret=max(ret,cnt[a[i]]);
	}
	for(int i=l;i<=r;i++){
		cnt[a[i]]=0;
	}
	return ret;
} 
int getans(){
	int mx=a[1];
	for(int i=1;i<=n;i++){
		if(b[a[i]].l==0){
			b[a[i]].l=i;
			b[a[i]].r=i;
		}
		else{
			b[a[i]].r=i;
		}
		mx=max(mx,a[i]);
	}
	sort(b+1,b+mx+1);
	for(int i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
		L[i]=R[i]=i;
	}
	for(int i=1;i<=mx;i++){
		if(b[i].r==0){
			break;
		}
		if(get(b[i].l)==get(b[i].r)){
			continue;
		}
		for(int j=R[get(b[i].l)];j<L[get(b[i].r)];j++){
			merge(j,j+1);
		}
		L[get(b[i].l)]=min(b[i].l,L[get(b[i].l)]);
		R[get(b[i].l)]=max(R[get(b[i].l)],b[i].l);
	}
	int ans=n;
	int l=1;
	for(int i=1;i<=n+1;i++){
		if(get(i)!=get(l)){
			ans-=work(l,i-1);
			l=i;
		}
	}
	for(int i=1;i<=mx;i++){
		b[i].l=b[i].r=0;
	}
	return ans;
}
signed main(){
    n=read(),q=read();
    for(int i=1;i<=n;i++){
    	a[i]=read();
	}
	write(getans(),'\n');
	return 0;
}
```

---

