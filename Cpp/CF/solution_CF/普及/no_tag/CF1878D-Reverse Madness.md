# Reverse Madness

## 题目描述

You are given a string $ s $ of length $ n $ , containing lowercase Latin letters.

Next you will be given a positive integer $ k $ and two arrays, $ l $ and $ r $ of length $ k $ .

It is guaranteed that the following conditions hold for these 2 arrays:

- $ l_1 = 1 $ ;
- $ r_k = n $ ;
- $ l_i \le r_i $ , for each positive integer $ i $ such that $ 1 \le i \le k $ ;
- $ l_i = r_{i-1}+1 $ , for each positive integer $ i $ such that $ 2 \le i \le k $ ;

Now you will be given a positive integer $ q $ which represents the number of modifications you need to do on $ s $ .

Each modification is defined with one positive integer $ x $ :

- Find an index $ i $ such that $ l_i \le x \le r_i $ (notice that such $ i $ is unique).
- Let $ a=\min(x, r_i+l_i-x) $ and let $ b=\max(x, r_i+l_i-x) $ .
- Reverse the substring of $ s $ from index $ a $ to index $ b $ .

Reversing the substring $ [a, b] $ of a string $ s $ means to make $ s $ equal to $ s_1, s_2, \dots, s_{a-1},\ s_b, s_{b-1}, \dots, s_{a+1}, s_a,\ s_{b+1}, s_{b+2}, \dots, s_{n-1}, s_n $ .

Print $ s $ after the last modification is finished.

## 说明/提示

In the first test case:

The initial string is "abcd". In the first modification, we have $ x=1 $ . Since $ l_1=1\leq x \leq r_1=2 $ , we find the index $ i = 1 $ . We reverse the substring from index $ x=1 $ to $ l_1+r_1-x=1+2-1=2 $ . After this modification, our string is "bacd".

In the second modification (and the last modification), we have $ x=3 $ . Since $ l_2=3\leq x \leq r_2=4 $ , we find the index $ i = 2 $ . We reverse the substring from index $ x=3 $ to $ l_2+r_2-x=3+4-3=4 $ . After this modification, our string is "badc".

In the second test case:

The initial string is "abcde". In the first modification, we have $ x=1 $ . Since $ l_1=1\leq x \leq r_1=1 $ , we find the index $ i = 1 $ . We reverse the substring from index $ x=1 $ to $ l_1+r_1-x=1+1-1=1 $ . After this modification, our string hasn't changed ("abcde").

In the second modification, we have $ x=2 $ . Since $ l_2=2\leq x \leq r_2=2 $ , we find the index $ i = 2 $ . We reverse the substring from index $ x=2 $ to $ l_2+r_2-x=2+2-2=2 $ . After this modification, our string hasn't changed ("abcde").

In the third modification (and the last modification), we have $ x=3 $ . Since $ l_3=3\leq x \leq r_3=5 $ , we find the index $ i = 3 $ . We reverse the substring from index $ x=3 $ to $ l_3+r_3-x=3+5-3=5 $ . After this modification, our string is "abedc".

## 样例 #1

### 输入

```
5
4 2
abcd
1 3
2 4
2
1 3
5 3
abcde
1 2 3
1 2 5
3
1 2 3
3 1
gaf
1
3
2
2 2
10 1
aghcdegdij
1
10
5
1 2 3 4 2
1 1
a
1
1
1
1```

### 输出

```
badc
abedc
gaf
jihgedcdga
a```

# 题解

## 作者：Kedit2007 (赞：22)

## 思路

首先，不难发现原序列被拆分成了 $k$ 段，第 $i$ 段左右边界分别为 $l[i]$ 和 $r[i]$，且在一个区间上的操作不会影响其他区间。

操作过程中，对于每一次操作 $x$，先找到 $x$ 在其所在区间中的对称点，记作 $y$，接着翻转 $x$ 到 $y$ 构成的子串。

注意到操作顺序不影响结果，只需要关注操作次数。考虑对于区间中的某一个点及其对称点，有哪些操作能够使其翻转。对于一个点 $a$，设其对称点为 $b$，为了方便，假设 $a$ 在区间中点左侧。能够影响到 $a$ 的操作都发生在 $a$ 及 $a$ 的左侧与 $b$ 及 $b$ 的右侧，我们只需要统计满足这个条件的操作数即可。

上述统计操作即求若干个区间的和，不难想到用前缀和维护，具体实现细节可参考代码，总体复杂度为 $O(n + q)$。

## 参考代码

```cpp
void work()
{
	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	vector<int> l(m), r(m);
	for (int i = 0; i < m; i++)
	{
		cin >> l[i];
	}
	for (int i = 0; i < m; i++)
	{
		cin >> r[i];
	}
	int q;
	cin >> q;
	vector<int> arr(n + 1);
	for (int i = 0; i < q; i++)
	{
		int t;
		cin >> t;
		arr[t]++;
	}
	for (int i = 1; i <= n; i++)
	{
		arr[i] += arr[i - 1];
	}
	for (int i = 0; i < m; i++)
	{
		int lb = l[i], rb = r[i];
		for (int j = lb - 1, k = rb - 1; j < k; j++, k--)
		{
			int cnt = arr[j + 1] - arr[lb - 1] + arr[rb] - arr[k];
			if (cnt % 2 == 1)
			{
				swap(s[j], s[k]);
			}
		}
	}
	cout << s << '\n';
}
```

---

## 作者：Richard1211 (赞：11)

# 题意简述
给你一个字符串 $s$，且 $|S|=n$，把这个字符串分成 $k$ 个子串 $[l_1,r_1],[l_2,r_2]\dots,[l_k,r_k]$，满足 $l_1=1\And r_k=n\And\forall i∈[1,k],l_i\leq r_i , l_i=r_{i-1}+1$。  
接着给你 $q$ 个询问，每个询问输入一个整数 $x$，需要找到唯一的一个 $i$ 使得 $l_i\leq x\leq r_i$，将 $s$ 的 $[\min(x,r_i+l_i-x),\max(x,r_i+l_i-x)]$ 子串翻转。  
输出所有翻转操作后的字符串 $s$。

# 题目分析
赛时看到这个题的时候，最先想到的思路是，使用 $O(\sum n)$ 的时间预处理出每一个 $x$ 所在的子串编号，用 $belong_i$ 表示 $i$ 所属的子串的编号。  

然后发现题目要求的是区间翻转操作，考虑使用文艺平衡树进行维护，这里我选择使用好写且容易理解的 FHQ_Treap。  

考虑如何使用 FHQ_Treap 维护区间翻转，在进行一次翻转操作后，实际上只需要将树的左右儿子全部 swap 一下，然后对树求一遍中序遍历，即可得到正确答案。  

我们在树的每一个点上设置一个懒标记 tag 表示这个点的左右儿子是否需要 swap。一个优化是在交换节点后将这个节点的左右儿子的 tag 都取反，因为只有在奇数的情况下才需要交换，而偶数的情况下就不需要了，然后我们在 Split 和 Merge 前判断是否需要 Pushdown 即可。  

注意由于树需要满足二叉搜索树的性质，所以如果我们按照权值 Split，那么会导致在 swap 节点时不能满足二叉搜索树的性质，所以我们考虑按照子树的 size 进行 Split。  

最后就是 Reverse 了，如果我们要翻转区间 $[l,r]$，可以把整个区间 $[1,n]$ 给 Split 成 $[1,l-1],[l,r],[r+1,n]$，然后我们给 $[l,r]$ 打上 tag，然后再把三个区间 Merge 回去即可。  

实现完 FHQ_Treap 后，我们只需要在每次询问 $x$ 时，进行 
`Reverse(Min(x,q[belong[x]].r+q[belong[x]].l-x,Max(x,q[belong[x]].r+q[belong[x]].l-x)))` 
即可，对于字符串转数字的处理，我们可以 `Insert(s[i]-'a'+1)` ，然后在 中序遍历时输出 `s[i]+'a'-1` 即可。  

由于进行一次区间翻转的时间复杂度为 $O(\log n)$，有 $\sum q$ 次询问，所以算法复杂度为 $O(\sum q\log n)$ 可以通过本题。

具体实现可以参考代码。
# $Code$
```cpp
constexpr long long N=400400;
constexpr long long INF=1000000000;
struct Query{
    long long l,r;
};
long long t,n,k,qry,x;
long long belong[N];
char s[N];
Query q[N];
struct FHQ_Treap{
	struct Tree{
		long long l;
		long long r;
		long long sz;
		long long val;
		long long heap;
		bool tag;
	};
	Tree tr[N];
	long long a[N];
	long long root;
	long long cnt=0;
    inline void Clear(){
        root=cnt=0;
        for(register int i=0;i<=n+1145;++i){
            tr[i].l=tr[i].r=tr[i].sz=tr[i].val=tr[i].heap=tr[i].tag=a[i]=0;
        }
    }
	inline void Pushup(long long x){
		tr[x].sz=tr[tr[x].l].sz+tr[tr[x].r].sz+1;
		return void();
	}
	inline void Pushdown(long long x){
		tr[x].tag=false;
		Swap(tr[x].l,tr[x].r);
		tr[tr[x].l].tag^=1;
		tr[tr[x].r].tag^=1;
		return void();
	}
	inline long long Merge(long long x,long long y){
		if(!x||!y){
			return x+y;
		}
		if(tr[x].heap<tr[y].heap){
			if(tr[x].tag){
				Pushdown(x);
			}
			return tr[x].r=Merge(tr[x].r,y),Pushup(x),x;
		}
		else{
			if(tr[y].tag){
				Pushdown(y);
			}
			return tr[y].l=Merge(x,tr[y].l),Pushup(y),y;
		}
	}
	inline void Split(long long x,long long key,long long &u,long long &v){
		if(!x){
			u=v=0;
			return void();
		}
		if(tr[x].tag){
			Pushdown(x);
		}
		if(tr[tr[x].l].sz<key){
			u=x;
			Split(tr[x].r,key-tr[tr[x].l].sz-1,tr[u].r,v);
		}
		else{
			v=x;
			Split(tr[x].l,key,u,tr[v].l);
		}
		Pushup(x);
		return void();
	}
	inline long long Create(long long key){
		tr[++cnt].val=key;
		tr[cnt].heap=rand();
		tr[cnt].sz=1;
		tr[cnt].tag=false;
		return cnt;
	}
	long long x,y,z;
	inline void Insert(long long key){
		root=Merge(root,Create(key));
		return void();
	}
	inline void Reverse(long long l,long long r){
		Split(root,l-1,x,y);
		Split(y,r-l+1,y,z);
		tr[y].tag^=1;
		root=Merge(x,Merge(y,z));
		return void();
	}
	inline void Dfs(long long x){
		if(!x){
			return void();
		}
		if(tr[x].tag){
			Pushdown(x);
		}
		Dfs(tr[x].l);
        putchar(tr[x].val+'a'-1);
		Dfs(tr[x].r);
		return void();
	}
};
FHQ_Treap FT;
int main(){
//    DEBUG();
    srand(time(0));
    t=read();
    for(register int T=1;T<=t;++T){
        n=read();
        k=read();
        scanf("%s",s+1);
        for(register int i=1;i<=k;++i){
            q[i].l=read();
        }
        for(register int i=1;i<=k;++i){
            q[i].r=read();
        }
        for(register int i=1;i<=k;++i){
            for(register int j=q[i].l;j<=q[i].r;++j){
                belong[j]=i;
            }
        }
        for(register int i=1;i<=n;++i){
            FT.Insert(s[i]-'a'+1);
        }
        qry=read();
        for(register int Q=1,l,r;Q<=qry;++Q){
            x=read();
            l=Min(x,q[belong[x]].r+q[belong[x]].l-x);
            r=Max(x,q[belong[x]].r+q[belong[x]].l-x);
//            Debug(l);
//            Debug(r);
            FT.Reverse(l,r);
        }
        FT.Dfs(FT.root);
        putchar('\n');
        FT.Clear();
        memset(belong,0,sizeof(long long)*(n+114));
    }
    return 0;
}
```

---

## 作者：Bh_hurter (赞：4)

## 题意说明
首先给定一字符串 $s$，和它的长度 $n$。

接着，会给出 $k$ 个 $l$ 以及 $k$ 个 $r$，在这 $k$ 个 $l$ 中，任意  $l_ {i}$ 会比 $r_ {i}$ 小，同时 $l_ {i+1}=r_ {i}+1$。如此这样就把 $s$ 分为了 $k$ 段，并且能保证这 $k$ 段可以完全覆盖 $s$。  

然后是 $q$ 次询问，每次给出一个 $x$。先从 $k$ 段中找出 $x$ 在那一段，再将这一段中下标从 $\min(x,l+r-x)$ 到 $\max(x,r+l-x)$ 的子段进行翻转。  

最后输出翻转后的 $s$。（别忘了一共有 $t$ 组数据）  
## 题目简解  
首先不难发现，每次对某一段子串是独立的，一个子串翻转不会影响其他子串，所以可以一段一段的来看。

其实，任意一个对于字符串 $s$ 合法下标 $a$，与下标 $l+r-x$ 在 $a$ 所在的子段中是对应的，也就是说，下标为 $a$ 的字符，都只会和下标 $l+r-a$ 的字符交换，下为证明过程。  

设当前 $x$ 所在 $s$ 的子段起始位置为 $l$，终止位置为 $r$。  

|l|u|o|......|g|u|
|:-:|:-:|:-:|:-:|:-:|:-:|      
|l|l+1|l+2|......|r-1|r| 

若输入为 $x$，则其从前往后数应是第 $|x-l+1|$ 个，而 $l+r-x$ 恰好是从后往前第 $|x-l+1|$ 个，所以 $x$ 与 $l+r-x$ 相对应。
  
那么我们只用统计每个位置被翻转的次数（毕竟一个位置只会和固定的某一个位置交换），最后看这个位置 $a$ 被翻转的次数是奇数还是偶数，是奇数则与 $l+r-a$ 交换，偶数则不动。  

不难想到，既然每次会对一个区间进行操作计数，于是便可用差分数组优化，这样操作计数的时间复杂度就降为了 $O(1)$，具体请参考代码。   

### AC code 

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e5;
int l[N+5],r[N+5],c[N+5];
int main(){
	int t;
	cin>>t;
	while(t--){//t组数据 
		string s;
		int n,k;
		cin>>n>>k>>s;
		for(int i=1;i<=k;i++){
			cin>>l[i];
		}
		for(int i=1;i<=k;i++){
			cin>>r[i];
		}//输入 
		memset(c,0,sizeof c);//差分数组初始化 
		int q;
		cin>>q;
		while(q--){
			int x;
			cin>>x;
			int i=lower_bound(r+1,r+k+1,x)-r;//二分查找x所在的子段（如果按l找会有问题） 
			int a=min(x,l[i]+r[i]-x);
			int b=max(x,l[i]+r[i]-x);
			c[a]++;
			c[b+1]--;//差分数组计数 
		}
		int sum=0;
		string ans=s;//尽量不要在原字符串上操作 
		for(int i=1;i<=k;i++){
			for(int j=l[i];j<=r[i];j++){
				sum+=c[j];
				if(sum%2!=0){//说明这里翻转了奇数次 
					ans[j-1]=s[l[i]+r[i]-j-1];//把当前位置交换 
				}
			}
		}
		cout<<ans<<'\n';//别忘换行 
	}
	return 0;
} 
```

（蒟蒻的第一篇题解，请管理员放过）

---

## 作者：LCat90 (赞：3)

一种暴力的做法是平衡树无脑翻转。

但是我们考虑巧妙的做法。题目中 $x$ 对应了一个连续的区间，并且这些区间一定没有交叉，要么就是包含。

根据这个性质，对于一个点 $i$，我们记录它被翻转了几次。如果是奇数次，就将它和另一个元素翻转；如果偶数次则保留。区间加我们可以维护差分序列，最后求和。

如果预处理出 $x$ 对应的区间的话时间复杂度就是 $O(n+q)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int t, n, q, a[N], k, ans, pre[N];
int read(); char c[N]; bool vis[N];
struct node {
	int l, r;
	friend bool operator < (node a, node b) {
		return a.l < b.l;
	}
} p[N];
signed main() {
	cin >> t;
	while(t--) { 
		cin >> n >> k; 
		scanf("%s", c + 1);
		for(int i = 1;i <= k; ++i) scanf("%d", &p[i].l);
		for(int i = 1;i <= k; ++i) scanf("%d", &p[i].r);
		for(int i = 1;i <= n; ++i) vis[i] = a[i] = pre[i] = 0;
		sort(p + 1, p + k + 1);
		cin >> q;
		while(q--) { int x;
			scanf("%d", &x);
			int l = 1, r = k;
			while(l < r) {
				int mid = l + r >> 1;
				if(p[mid].r >= x) r = mid;
				else l = mid + 1;
			}
			
			int L = min(x, p[l].r + p[l].l - x), R = max(x, p[l].r + p[l].l - x);
//			cout << "\n" << l << " " << L << " " << R << "\n\n";
			pre[L] ++; pre[R + 1] --;
		}
		for(int i = 1;i <= n; ++i) a[i] = a[i - 1] + pre[i]; int cnt = 1;
//		for(int i = 1;i <= n; ++i) cout << a[i] << " "; puts("");
		for(int i = 1;i <= n; ++i) {
			if(i > p[cnt].r) cnt ++;
			if(a[i] & 1) {
				if(vis[i]) continue ;
				vis[i] = vis[p[cnt].r - i + p[cnt].l] = 1;
				swap(c[i], c[p[cnt].r - i + p[cnt].l]);
			}
		}
		for(int i = 1;i <= n; ++i) cout << c[i];
		puts("");
	}  
	return 0;
}

/*

*/

int read() {
	char c; int sum = 0; while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') sum = (sum << 3) + (sum << 1) + (c ^ 48), c = getchar();
	return sum;	
}
```

---

## 作者：AbsMatt (赞：3)

### [题目传送器](https://www.luogu.com.cn/problem/CF1878D)

### [更爽的阅读体验](https://www.luogu.com.cn/blog/yaohaoyou/solution-cf1878d)

## 题意
给定 $n$ 个区间，其中两两相邻，且能覆盖 $[1,n]$，给定 $q$ 次修改，每次将包含 $x$ 的区间进行一次翻转，翻转 $[\min(x,r+l-x),\max(x,r+l-x)]$，求最后的字符串。

## 做法
题解区用的貌似都是本蒟蒻不会的 Splay（或其他平衡树） 和奇怪的模拟，这里给大家讲一种好想也好写的方法。

首先，$x$ 所在的区间非常好求，只需要先对区间排序后二分即可，难点在于如何进行翻转。

暴力翻转很明显是 $O(n \times q)$，于是想如何优化。可以发现会有很多区间会多次反转导致很多次操作，但其实每个区间只有两种可能，翻转和没翻转，考虑通过这种性质优化。可以发现 $[\min(x,r+l-x),\max(x,r+l-x)]$ 其实就是将 $x$ 所在的区间的第 $x-l+1$ 个到第 $r-(x-l+1)+1$ 个进行翻转，所以对于每个位置，一旦进行了翻转，区间都可以直接求出。

用线段树维护那些位置进行了翻转，需要区间修改和单点查询，tag 记录整个区间是否都要翻转，最后输出时单点查询判断每个点是否需要翻转即可。

### 总结
时间复杂度为 $O(n\log_2n)$，瓶颈在线段树和 lower_bound。记得要将输入的区间排序（貌似输入不保证单调递增）和初始化线段树。
### AC Code

```cpp
#include<bits/stdc++.h>  // 开始了
using namespace std;
const int maxn=2e5+10;
int n,m;
int l[maxn],r[maxn];
namespace SegmentTree{  // 线段树
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    bool tag[maxn<<2];
    void pushdown(int p){  // 传递 tag
        if(tag[p]){
            tag[ls]^=1;
            tag[rs]^=1;
            tag[p]=0;
        }
    }
    void update(int p,int l,int r,int pl,int pr){  // 区间修改
        if(l>=pl&&r<=pr){
            tag[p]^=1;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(pl<=mid) update(lson,pl,pr);
        if(pr>mid)  update(rson,pl,pr);
    }
    bool query(int p,int l,int r,int x){  // 单点查询
        if(l==r){
            return tag[p];
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(x<=mid)  return query(lson,x);
        return query(rson,x);
    }
}
void solve(){
    cin>>n>>m;
    string s;
    cin>>s;
    for(int i=1;i<=m;i++)   cin>>l[i];
    for(int i=1;i<=m;i++)   cin>>r[i];
    sort(l+1,l+m+1);// 记得排序
    sort(r+1,r+m+1);
    int q;
    cin>>q;
    for(int i=1;i<=n<<2;i++)    SegmentTree::tag[i]=0;  // 记得初始化
    while(q--){
        int x;
        cin>>x;
        int k=lower_bound(r+1,r+m+1,x)-r,a=min(x,r[k]+l[k]-x),b=max(x,r[k]+l[k]-x);
        // printf("%d %d\n",a,b);
        // printf("%d\n",k);
        SegmentTree::update(1,1,n,a,b);
    }
    for(int i=1;i<=m;i++){
        for(int j=l[i];j<=r[i];j++){
            if(SegmentTree::query(1,1,n,j)) cout<<s[r[i]-(j-l[i]+1)];  // 要交换
            else    cout<<s[j-1];  // 不交换
            // printf("%d",SegmentTree::query(1,1,n,j));
        }
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--)  solve();  // 多测
    return 0;  // 再见
}
```


---

## 作者：homo_snow (赞：2)

# 题意

给出一长度为 $n$ 的字符串 $s$，将其分成 $k$ 个子串 $[l_{1},r_{1}]$，$[l_{2},r_{2}]...[l_{k},r_{k}]$，保证 $l_{1}=1,r_{k}=n$。

再给出 $q$ 个询问，每次一个整数 $x$，要求找出 $i$ 使得 $l_{i}\le x \le r_{i}$，并反转区间 $[\min(x,r_{i}+l_{i}-x),\max(x,r_{i}+l_{i}-x)]$。

求最后的字符串 $s$。

# 思路

首先，对于查找 $x$ 所在区间，其实直接使用数组映射就行。

通过观察式子可以发现，由 $x$ 得到的反转区间 $[a,b]$ 的对称轴为题中 $[l_{i},r_{i}]$ 的对称轴。

由此，我们可以把每一个同轴对称的区间归为一个，一起翻转。

显然，最简单的办法就是将区间标记 $+1$，对此可以用差分进行优化。

如果当前位置被奇数个区间所覆盖，那么将其与其对称位置进行交换。

$Code$:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7;

int t, n , k,q,l[N],r[N],pos[N],dif[N];
string s;

signed main(){
	scanf("%lld",&t);
	while(t--){
		memset(pos,0,sizeof(pos));
		memset(dif,0,sizeof(pos));
		scanf("%lld%lld",&n,&k);
		cin >> s;
		for(int i = 1; i <= k; i++) scanf("%lld",&l[i]);
		for(int i = 1; i <= k; i++){
			scanf("%lld",&r[i]);
			for(int j = l[i] ; j <= r[i]; j++) pos[j] = i;
		}
		scanf("%lld",&q);
		while(q--){
			int x;
			scanf("%lld",&x);
			dif[min(x , r[pos[x]] + l[pos[x]] - x)]++;
			dif[max(x , r[pos[x]] + l[pos[x]] - x) + 1]--;
		}
		for(int i = 1; i <= n; i++)
			dif[i] += dif[i-1];
		for(int i = 1; i <= k; i++)
			for(int j = l[i]; j <= (l[i] + r[i]) / 2; j++)
				if(dif[j] & 1)
					swap(s[j-1],s[r[i] + l[i] - j - 1]);
		printf("%s\n",s.c_str());
	}
	return 0;
}
```


---

## 作者：lfxxx (赞：2)

你说得对，虽然平衡树和珂朵莉树写起来麻烦，但是思维难度为 $0$。

考虑线用珂朵莉树维护每个 $x$ 所对应的 $l_i,r_i$，然后每次暴力找出反转的区间，直接用文艺平衡树的做法，在 FHQtreap 上维护一个反转标记即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e6+114;
int tot,root;
struct FHQTreap{
	int val,sz,ls,rs,tag;
	char data;//这个节点存储的数据 
}treap[maxn];
int clone(char data){
	int New=++tot;
	treap[New].data=data;
	treap[New].val=rand();
	treap[New].sz=1;
	treap[New].tag=1;
	treap[New].ls=0;
	treap[New].rs=0;
	return New;
}
inline void pushup(int cur){
	treap[cur].sz=treap[treap[cur].ls].sz+treap[treap[cur].rs].sz+1;
}
inline void rot(int cur){
	treap[cur].tag^=1;
}
inline void pushdown(int cur){
	if(treap[cur].tag==1){
		swap(treap[cur].ls,treap[cur].rs);
		if(treap[cur].ls!=0) treap[treap[cur].ls].tag^=1;
		if(treap[cur].rs!=0) treap[treap[cur].rs].tag^=1;
		treap[cur].tag=0;
	}
}
int merge(int x,int y){
	pushdown(x);
	pushdown(y);
    if (!x||!y) return x+y;
    if (treap[x].val<treap[y].val)
    {
        treap[x].rs=merge(treap[x].rs,y);
        pushup(x);
        return x;
    }
    else
    {
        treap[y].ls=merge(x,treap[y].ls);
        pushup(y);
        return y;
    }
}
void split(int cur,int x,int &l,int &r) {
	pushdown(cur);
	if(cur==0){
		l=r=0;
		return ;
	}
	if(treap[treap[cur].ls].sz>=x){
		r=cur;
		split(treap[cur].ls,x,l,treap[cur].ls);
	}
	else{
		l=cur;
		split(treap[cur].rs,x-treap[treap[cur].ls].sz-1,treap[cur].rs,r);
	}
	pushup(cur);
}
void write(int cur){
	pushdown(cur);
    if (cur == 0)
    return ;
    write(treap[cur].ls);
    cout << treap[cur].data;
    write(treap[cur].rs);
}
int kth(int cur,int k){
    while(1){
    	pushdown(cur);
        if (k<=treap[treap[cur].ls].sz)
            cur=treap[cur].ls;
        else
        if (k==treap[treap[cur].ls].sz+1)
            return treap[cur].data;
        else
            k-=treap[treap[cur].ls].sz+1,cur=treap[cur].rs;
    }
}
int cursor;
inline void Move(int k){
	cursor=k;
}
inline void Insert(char c){
	int x=0,y=0,z=0;
	split(root,cursor,x,z);
	y=clone(c);
	root=merge(x,merge(y,z));
}
inline void Delete(int len){
	int x=0,y=0,z=0;
	split(root,cursor,x,y);
	split(y,len,y,z);
	root=merge(x,z);
}
inline void Rotate(int len){
	int x=0,y=0,z=0;
	split(root,cursor,x,y);
	split(y,len,y,z);
	rot(y);
	root=merge(x,merge(y,z));
}
inline void Get(){
	int x=0,y=0,z=0;
	split(root,cursor,x,y);
	split(y,1,y,z);
	write(y);
	root=merge(x,merge(y,z));
}
inline void Prev(){
	cursor--;
}
inline void Next(){
	cursor++;
}
struct Node{
    int l,r,v;
    Node(int l,int r = 0,int v = 0) : l(l), r(r), v(v){}
    bool operator<(const Node &a) const {
        return l < a.l;
    }
};
set<Node> s;
set<Node>::iterator Split(int pos) {
    set<Node>::iterator it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) {
        return it;
    }
    it--;
    if (it->r < pos) return s.end();
    int l = it->l;
    int r = it->r;
    int v = it->v;
    s.erase(it);
    s.insert(Node(l, pos - 1, v));
    return s.insert(Node(pos, r, v)).first;
}
int found(int pos){
	set<Node>::iterator it = Split(pos);
	return (it->v);
}
int n,q,k;
int L[maxn],R[maxn];
void work(){
	tot=root=cursor=0;
	s.clear();
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		Insert(c);
		Next();
	}
	for(int i=1;i<=k;i++){
		cin>>L[i];
	}
	for(int i=1;i<=k;i++){
		cin>>R[i];
	}
	for(int i=1;i<=k;i++){
		s.insert(Node(L[i],R[i],i));
	}
	cin>>q;
	while(q--){
		int x;
		cin>>x;
		int p=found(x);
		int lt=min(x,L[p]+R[p]-x),rt=max(x,L[p]+R[p]-x);
		Move(lt-1);
		Rotate(rt-lt+1);
	}
	Move(0);
	for(int i=1;i<=n;i++){
		Get();
		Next();
	}
	cout<<'\n';
}
int T;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--) work();
}
```


---

## 作者：NanNanzi_QvQ (赞：2)

思维题，赛时没用特殊的数据结构完成了这道题。

理解题意，题目给了一个字符串和 $k$ 个区间，这 $k$ 个区间是 $[1,n]$ 的一个划分。随后，给出 $q$ 次操作，每次给定一个 $x$，设 $x \in [l_i,r_i]$，则将 $\min(l_i+r_i+x,x),\max(l_i+r_i+x,x)$ 之间的字符串翻转，输出翻转后的结果。

手玩之后发现，每次翻转的一定是每个区间中中心对称的一个小区间。例如，当 $l=2,r=5$ 时，若 $x=3$，则翻转 $[3,4]$，若 $x=2$, 则翻转 $[2,5]$。于是，考虑记录每个字符所在的区间被翻转了多少次，如果是奇数次，就将这个字符和其在这个区间中对称的字符交换为止，如果是偶数次，则为止不变。

于是可以开一个数组 $num[i]$，用于记录操作中数字 $i$ 出现的次数，我们设 $x\in [l,r]$，并且设 $x\leq \frac{l+r}{2}$，则字符 $x$“被翻转的次数”，即为 $num_l+num_r+num_{l+1}+num_{r-1}\dots +num_x+num_{r-(x-l)}$。

注意到对称性，对每个区间 $[l,r]$，我们只需要考虑小于等于 $\frac{l+r}{2}$ 的字符的翻转即可。

赛时代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k, q, x, now, sum;
string s;
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> k >> s;
        vector<int> l(k + 2), r(k + 2), num(n + 1);
        for (int i = 1; i <= k; i++) cin >> l[i];
        for (int i = 1; i <= k; i++) cin >> r[i];
        cin >> q;
        for (int i = 1; i <= q; i++) cin >> x, num[x]++;
        now = 1, sum = 0;;
        for (int i = 1; i <= n; i++) {
            if (i > r[now]) now++;
            int x = min(l[now] + r[now] - i, i), y = max(l[now] + r[now] - i, i);
            sum += num[x] + num[y];
            if (i > x) continue;
            if (sum % 2 == 1) swap(s[x - 1], s[y - 1]);
        }
        cout << s << endl;
    }
    return 0;
}
```


---

## 作者：hikariyo_ (赞：2)

虽然平衡树写起来麻烦，但是思维含量几乎为零。

首先查询 $x$ 在哪个区间中，这个用 `upper_bound` 就行。找到了 $a,b$ 后就是文艺平衡树反转区间的模板了。

由于边界处理起来比较麻烦，这里使用建立 `dummy head, tail` 的方法来简化，每次翻转区间 $[a,b]$ 时，原来需要找到 $L=kth(a-1),R=kth(b+1)$，现在就是 $L=kth(a),R=kth(b+2)$。


复杂度 $O(n\log n)$，可过。

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 200010;
int n, k;
int l[N], r[N];
char s[N];

struct Node {
	int s[2], p, size;
	char v;
	int flip;
	
	void init(char v_, int p_) {
		s[0] = s[1] = 0, v = v_, p = p_;
		flip = 0; 
	}
	
	void spread() {
		swap(s[0], s[1]);
		flip ^= 1;
	}
} tr[N];
int idx, root;

void pushup(int u) {
	tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1;
}

void pushdown(int u) {
	if (!tr[u].flip) return;
	
	tr[tr[u].s[0]].spread();
	tr[tr[u].s[1]].spread();
	tr[u].flip = 0;
}

void rotate(int x) {
	int y = tr[x].p, z = tr[y].p;
	int k = tr[y].s[1] == x;
	tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
	tr[y].s[k] = tr[x].s[k^1], tr[tr[x].s[k^1]].p = y;
	tr[x].s[k^1] = y, tr[y].p = x;
	pushup(y), pushup(x);
}

void splay(int x, int k) {
	while (tr[x].p != k) {
		int y = tr[x].p, z = tr[y].p;
		if (z != k) {
			if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if (!k) root = x;
}

int build(int l, int r, int p) {
	int mid = l+r >> 1;
	int u = ++idx;
	tr[u].init(s[mid], p);
	if (l <= mid-1) tr[u].s[0] = build(l, mid-1, u);
	if (mid+1 <= r) tr[u].s[1] = build(mid+1, r, u);
	pushup(u);
	return u;
}

int getk(int k) {
	int u = root;
	while (u) {
		pushdown(u);
		if (k <= tr[tr[u].s[0]].size) u = tr[u].s[0];
		else if (k == tr[tr[u].s[0]].size + 1) {
			splay(u, 0);
			return u;
		}
		else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
	}
	
	return -1;
}

void output(int u) {
	pushdown(u);
	if (tr[u].s[0]) output(tr[u].s[0]);
	if (tr[u].v != '@') cout << tr[u].v;
	if (tr[u].s[1]) output(tr[u].s[1]);
}

void solve() {
	idx = root = 0;
	cin >> n >> k >> s+1;
	s[0] = s[n+1] = '@';
	root = build(0, n+1, 0);
	
	for (int i = 0; i < k; i++) cin >> l[i];
	for (int i = 0; i < k; i++) cin >> r[i];
	int q, x; cin >> q;
	while (q--) {
		cin >> x;
		int t = upper_bound(l, l+k, x) - l - 1;
		int y = r[t] + l[t] - x;
		int a = min(x, y), b = max(x, y);
		int L = getk(a), R = getk(b+2);
		splay(R, 0), splay(L, R);
		tr[tr[L].s[1]].spread();
	}
	output(root);
	cout << '\n';
}

int main() {
	int T; cin >> T;
	while (T--) solve();
	return 0;
}

```

---

## 作者：AK_400 (赞：1)

# [ CF1878D](https://codeforces.com/problemset/problem/1878/D) 题解
## 题面
给定长度为 $n$ 字符串 $s$ 和长度为 $k$ 的数组 $l,r$。

有 $q$ 次询问，每次询问给定一个整数 $x$，存在唯一的 $i$，使得 $l_i\le x\le r_i$，翻转区间 $(\min(x,r_i+l_i-x),\max(x,r_i+l_i-x))$。
## solution
区间翻转，显然是文艺平衡树板子。

$a,b$ 二分求一下就行了。

# CODE 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,q,x;int l,r,mid;
string s;
int L[200005],R[200005];
int fnd(int x){//二分找区间
    l=1,r=k;
    while(l<r){
        mid=(l+r)/2;
        if(L[mid]>x)r=mid-1;
        if(R[mid]<x)l=mid+1;
        if(L[mid]<=x&&x<=R[mid])return mid;
    }
    return l;
}
struct splaytree{
    int sz[200005],ch[200005][2],fa[200005],rt,tot;char vl[200005];
    bool lz[200005];
    void init(){
        for(int i=0;i<=n+1;i++){
            vl[i]=ch[i][0]=ch[i][1]=lz[i]=fa[i]=rt=tot=sz[i]=0;
        }
    }
    void mt(int x){
        sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
        return;
    }
    int get(int x){
        return x==ch[fa[x]][1];
    }
    void cl(int x){
        sz[x]=ch[x][0]=ch[x][1]=fa[x]=vl[x]=lz[x]=0;
    }
    void rot(int x){
        int y=fa[x],z=fa[y],c=get(x);
        if(!y)return;
        ch[y][c]=ch[x][c^1];
        if(ch[x][c^1])fa[ch[x][c^1]]=y;
        fa[y]=x;
        ch[x][c^1]=y;
        fa[x]=z;
        if(z)ch[z][y==ch[z][1]]=x;
        mt(y);
        mt(x);
        return;
    }
    void splay(int x,int g=0){
        if(g==0)rt=x;
        for(int f=fa[x];(f=fa[x])!=g;rot(x)){
            if(fa[f]!=g)rot((get(x)==get(f)?f:x));   
        }
        return;
    }
    int bd(int l,int r,int f){
        if(l>r)return 0;
        int mid=l+r>>1,cur=++tot;
        vl[cur]=s[mid];
        fa[cur]=f;
        ch[cur][0]=bd(l,mid-1,cur);
        ch[cur][1]=bd(mid+1,r,cur);
        mt(cur);
        return cur;
    }
    void tr(int x){
        swap(ch[x][0],ch[x][1]);
        lz[x]^=1;
        return;
    }
    void pd(int x){
        if(!lz[x])return;
        tr(ch[x][0]);
        tr(ch[x][1]);
        lz[x]=0;
        return;
    }
    int kth(int k){
        int cur=rt;
        while(1){
            pd(cur);
            if(ch[cur][0]&&k<=sz[ch[cur][0]]){
                cur=ch[cur][0];
            }
            else {
                k-=1+sz[ch[cur][0]];
                if(k<=0){
                    splay(cur);
                    return cur;
                }
                cur=ch[cur][1];
            }
        }
        return -1;
    }
    void rev(int l,int r){
        int L=kth(l),R=kth(r+2);
        splay(L),splay(R,L);
        tr(ch[ch[L][1]][0]);
        return ;
    }
    void prt(int p){
        pd(p);
        if(ch[p][0])prt(ch[p][0]);
        if(vl[p]>='a'&&vl[p]<='z')cout<<vl[p];
        if(ch[p][1])prt(ch[p][1]);
        return;
    }
}T;
signed main(){
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--){
        cin>>n>>k;
        mxn=max(mxn,n);
        T.init();
        cin>>s;
        s=' '+s+' ';
        T.rt=T.bd(0,1+n,0);
        for(int i=1;i<=k;i++){
            cin>>L[i];
        }
        for(int i=1;i<=k;i++){
            cin>>R[i];
        }
        cin>>q;
        while(q--){
            cin>>x;
            int p=fnd(x);
            int fl=min(x,R[p]+L[p]-x),fr=max(x,R[p]+L[p]-x);
            T.rev(fl,fr);
        }
        T.prt(T.rt);
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1878D)
## 思路
首先注意序列 $l, r$ 满足的条件，可以发现每一对 $l_{i}, r_{i}$ 都把 $[1, k]$ 这个区间分成了互不重叠的区间，且这个 $[1, k]$ 中的所有整数都包含在这些区间内。而通过操作的说明并画图可以发现每次操作相当于选取了一个区间内一个居中的区间并将这个区间对应的字符串 $s$ 翻转。

由于每次操作都是选取区间中居中的一个区间，所以操作顺序没有不同，而且如果一个位置被翻转了偶数次则相当于没有翻转。

## 具体过程
对于每次操作给出的 $x$，计算出其对应的 $a, b$，使用差分数组记录下这片区间的对应字符串被翻转了一次。

所有操作结束后通过查分数组计算出所有位置被翻转的次数，如果是偶数则不翻转，否则将其与其对应的位置 $r_{i} + l_{i} - x$ 交换（注意不要重复交换）。

## AC Code

```
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) ((x >= y) ?(x) :(y))
#define MIN(x, y) ((x <= y) ?(x) :(y))
#define FOR(st, ed, i, stp) for (int i = st; i <= ed; i += stp)
#define FORR(st, ed, i, stp) for (int i = ed; i >= st; i -= stp)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double dou;
typedef pair<int, int> pii;

const int maxn = 2e5 + 10;
const int maxk = maxn;

int t;
int n, k;
string s;
int l[maxn];
int r[maxn];
int q;
int x;
int revidx (int x, int i) {
	return r[i] - x + l[i];
}

int idx[maxn], sum[maxn];
string ans;

void work () {
	ans.clear();
	
	scanf("%i%i", &n, &k);
	
	FOR (1, n, i, 1) {
		sum[i] = 0;
		ans += '\0';
	}
	
	cin >> s;
	FOR (1, k, i, 1) {
		scanf("%i", &l[i]);
	}
	FOR (1, k, i, 1) {
		scanf("%i", &r[i]);
		
		FOR (l[i], r[i], j, 1) {
			idx[j] = i;
		}
	}
	scanf("%i", &q);
	while (q--) {
		scanf("%i", &x);
		
		int a = MIN(x, revidx(x, idx[x])), b = MAX(x, revidx(x, idx[x]));
		++sum[a];
		--sum[b + 1];
	}
	
	FOR (1, n, i, 1) {
		sum[i] += sum[i - 1];
		ans[((sum[i]%2 == 0) ?(i) :(revidx(i, idx[i]))) - 1] = s[i - 1];
	}
	
	cout << ans << '\n';
}
int main () {
	scanf("%i", &t);
	while (t--) {
		work();
	}
	return 0;
}

```

---

## 作者：BHDwuyulun (赞：0)

### 1 题目
[传送门](https://www.luogu.com.cn/problem/CF1878D)
### 2 思路
~~虽然平衡树简单无脑，但本人没学过……~~

考虑一种巧妙的做法：发现字符串反转时两两对应，因此只有该字符串翻转奇数次时，才真正被翻转。而每次翻转时打标记太慢，因此考虑在每次输入 $x$ 时，根据 $x$ 就可以计算出需要翻转的区间。
为了方便，在输入 $r$ 数组时采用映射（map）。
```cpp
map<int,int> mp;
for(int i=1;i<=k;i++){
	cin>>r[i];
	for(int j=l[i];j<=r[i];j++){
		mp[j]=i;
	}
}
```
所以 $x$ 属于 $mp_{x}$ 区间内。将开头和末尾打标记，最后模拟时传递即可。
```cpp
d[min(x,l[mp[x]]+r[mp[x]]-x)]++;  //左端点 ++
d[max(x,l[mp[x]]+r[mp[x]]-x)+1]--;//右端点+1 --
```
### 3 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define bug printf("---OK---")
#define pa printf("A: ")
#define pr printf("\n")
#define pi acos(-1.0)
#define TIE ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)//懒得用printf和scanf~~~
using namespace std;
const ll N=2e5+5;
int l[N],r[N];
map<int,int> mp;
int d[N];
void solve(){
	memset(l,0,sizeof l);
	memset(r,0,sizeof r);
	memset(d,0,sizeof d);
	mp.clear();
	int n,k,q,x;
	string s;
	cin>>n>>k;
	cin>>s;
	for(int i=1;i<=k;i++){
		cin>>l[i];
	}
	for(int i=1;i<=k;i++){
		cin>>r[i];
		for(int j=l[i];j<=r[i];j++){
			mp[j]=i;
		}
	}
	cin>>q;
	while(q--){
		cin>>x;
		d[min(x,l[mp[x]]+r[mp[x]]-x)]++;
		d[max(x,l[mp[x]]+r[mp[x]]-x)+1]--;
	}
	for(int i=1;i<=n;i++){
		d[i]+=d[i-1];
	}
	for(int i=1;i<=k;i++){
		for(int j=l[i];j<=l[i]+r[i]>>1;j++){
			if(d[j]%2==1){
				swap(s[j-1],s[l[i]+r[i]-j-1]);
			}
		}
	}
	cout<<s<<endl;
}
int main(){
	TIE;
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
看到好多大佬用线段树和 Splay 做，实际很简单。

意思大概是给你一个的字符串，分成 $k$ 个区间。给你一个 $x$，让你求出 $a$ 和 $b$，$a$ 的值为 $\min(x,r_i+l_i-x)$，$b$ 的值为 $\max(x,r_i+l_i-x)$，然后把 $a$ 和 $b$ 翻转。考虑使用差分，维护前缀和。经过尝试，可以发现翻转 $2$ 次等于没翻。不难发现，可以影响 $a$ 的点都在 $a$ 的左侧和 $b$ 的右侧，统计即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;const int N=2e5+5;
#define genshin_start ios::sync_with_stdio(false);cin.tie(0);
int T,n,m;string s;int dp[N],a[N],b[N],Q,x;
int main(){genshin_start;
cin>>T;
    while(T--){
        memset(dp,0,sizeof(dp));memset(a,0,sizeof(a));memset(b,0,sizeof(b));
        cin>>n>>m;cin>>s;
        for(int i=0;i<m;i++) cin>>a[i];for(int i=0;i<m;i++) cin>>b[i];
        cin>>Q;
        while(Q--){//
            cin>>x;
            dp[x]++;
        }
        for(int i=1;i<=n;i++) dp[i]+=dp[i-1];
        for(int i=0;i<m;i++){
            int l=a[i]-1,r=b[i]-1;
            while(l<r){
                int temp=dp[l+1]+dp[b[i]]-dp[a[i]-1]-dp[r];
                if(temp%2==1){
                    char tem=s[r];
                    s[r]=s[l];
                    s[l]=tem;
                }l++;r--;
            }
        }
        cout<<s<<endl;//
    }
    return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析 

因为对于每次操作，保证满足条件的 $(l_i,r_i)$ 只有一组，而 $r$ 序列是按照升序排列的，所以我们可以先通过二分找到每次操作的 $(l_i,r_i)$。

根据题目意思，我们能够通过 $x,l_i+r_i-x$ 找到该次操作翻转的字符串对应的左右下标。现在差的就是对区间内的字符串进行翻转了。很显然的是，我们可以把字符串看成由若干个字符组成的数组排列出来的结果，那么对于翻转 $[l,r]$ 区间内的子串，就是把下标为 $l$ 到 $r$ 的数组翻转。这不就是模板的[文艺平衡树](https://www.luogu.com.cn/problem/P3391)吗。所以套个模板就能过了。


代码可以自己写，不会的建议先去看模板的题解，这里就不加以解释了。

**【精简分析】**：

按照题意找到需要翻转的子串，一眼看出翻转区间是文艺平衡树，套模板。

---

## 作者：phigy (赞：0)

我们发现字符串中的字符永远是两两对应的，因此只有当一对字符串被翻转了奇数次，它们才会翻转。

然后我们发现对于每次翻转的区间的标记数组 $+1$ 的时间复杂度是 $O(n)$ 的这是不可行的。

所以我们又看到翻转的区间具有包含的关系，所以我们可以只对翻转的区间的开头末尾打上标记，然后最终模拟的时候向后传递即可。

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>

#define int long long

using namespace std;

int T;
int n,m,q;
int a[1000005];
int l[1000005];
int r[1000005];
char c[1000005];
int an[1000005];
int sum[1000005];
signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        for(i=1;i<=n;i++)
        {
            cin>>c[i];
            sum[i]=0;
        }
        for(i=1;i<=m;i++)
        {
            cin>>l[i];
        }
        for(i=1;i<=m;i++)
        {
            cin>>r[i];
        }
        cin>>q;
        for(i=1;i<=q;i++)
        {
            cin>>a[i];
        }
        sort(a+1,a+q+1);
        for(i=1,j=1;i<=n;i++)
        {
            if(r[j]<i)j++;
            an[i]=l[j]+r[j]-i;
        }
        for(i=1,j=1;i<=q;i++)
        {
            while(r[j]<a[i])j++;
            sum[min(a[i],l[j]+r[j]-a[i])]++;
            sum[max(a[i],l[j]+r[j]-a[i])]--;
        }
        int res=0;
        for(i=1;i<=n;i++)
        {
            res+=sum[i];
            ///cout<<sum[i]<<' ';
            if((res&1)&&i<an[i])swap(c[i],c[an[i]]);
            cout<<c[i];
        }
        cout<<endl;
    }
    return 0;
}


```


---

## 作者：ttq012 (赞：0)

对于每一次给定的翻转参数 $x$，翻转的区间则是 $[x,l_i+r_i-x]$ 且满足 $l_i\le x\le r_i$。

容易发现 $l_i+r_i-x$ 求的是 $x$ 在 $[l_i,r_i]$ 区间对称得到的点。

也就是说，在这段区间内的所有翻转操作都是以一个中心虚轴为中心，往两边各走一段距离得到的。

例如区间的字符串 $s’$ 为 $\texttt{abcdefg}$，则：

+ 如果 $x=3$ 那么翻转 $[3,5]$ 区间，得到 $\texttt{ab{\color{red}{edc}}fg}$。
+ 如果 $x=2$ 那么翻转 $[2,6]$ 区间，得到 $\texttt{a{\color{red}f}cde{\color{red}b}g}$。
+ 容易发现，如果 $x$ 位置在翻转区间内奇数次，那么 $x$ 和其对应位置就做了一次交换操作。
+ 否则抵消掉，没有做任何的交换操作。

所以就不需要使用 Splay 或者 FHQ-Treap 了。单组时间复杂度 $O(n\log n)$，瓶颈在于二分查找询问区间。

考虑优化。

发现可以直接记录第 $i$ 个位置所在区间的编号，这样就不用二分查找区间了。

单组询问时间复杂度 $O(n)$。

[Code](https://www.luogu.com.cn/paste/7qfb0nq4)

---

## 作者：Imken (赞：0)

因为平时做思维题不多就只会暴力。

看到区间翻转不难想到文艺平衡树。

那么只用在做的时候二分出对应的 $l_i, r_i$ 然后进行区间翻转就行。

赛时 `r[i] + l[i] - x` 写错挂了五发，气死了！

[Code](https://codeforces.com/contest/1878/submission/225384822)


---

