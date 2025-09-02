# Array Optimization by Deque

## 题目描述

In fact, the problems E1 and E2 do not have much in common. You should probably think of them as two separate problems.

You are given an integer array $ a[1 \ldots n] = [a_1, a_2, \ldots, a_n] $ .

Let us consider an empty [deque](https://tinyurl.com/pfeucbux) (double-ended queue). A deque is a data structure that supports adding elements to both the beginning and the end. So, if there are elements $ [3, 4, 4] $ currently in the deque, adding an element $ 1 $ to the beginning will produce the sequence $ [\color{red}{1}, 3, 4, 4] $ , and adding the same element to the end will produce $ [3, 4, 4, \color{red}{1}] $ .

The elements of the array are sequentially added to the initially empty deque, starting with $ a_1 $ and finishing with $ a_n $ . Before adding each element to the deque, you may choose whether to add it to the beginning or to the end.

For example, if we consider an array $ a = [3, 7, 5, 5] $ , one of the possible sequences of actions looks like this:

 $ \quad $ 1.add $ 3 $ to the beginning of the deque:deque has a sequence $ [\color{red}{3}] $ in it; $ \quad $ 2.add $ 7 $ to the end of the deque:deque has a sequence $ [3, \color{red}{7}] $ in it; $ \quad $ 3.add $ 5 $ to the end of the deque:deque has a sequence $ [3, 7, \color{red}{5}] $ in it; $ \quad $ 4.add $ 5 $ to the beginning of the deque:deque has a sequence $ [\color{red}{5}, 3, 7, 5] $ in it;Find the minimal possible number of inversions in the deque after the whole array is processed.

An inversion in sequence $ d $ is a pair of indices $ (i, j) $ such that $ i < j $ and $ d_i > d_j $ . For example, the array $ d = [5, 3, 7, 5] $ has exactly two inversions — $ (1, 2) $ and $ (3, 4) $ , since $ d_1 = 5 > 3 = d_2 $ and $ d_3 = 7 > 5 = d_4 $ .

## 说明/提示

One of the ways to get the sequence $ [5, 3, 7, 5] $ in the deque, containing only two inversions, from the initial array $ [3, 7, 5, 5] $ (the first sample test case) is described in the problem statement.

Also, in this example, you could get the answer of two inversions by simply putting each element of the original array at the end of the deque. In this case, the original sequence $ [3, 7, 5, 5] $ , also containing exactly two inversions, will be in the deque as-is.

## 样例 #1

### 输入

```
6
4
3 7 5 5
3
3 2 1
3
3 1 2
4
-1 2 2 -1
4
4 5 1 3
5
1 3 1 3 2```

### 输出

```
2
0
1
0
1
2```

# 题解

## 作者：EternalHeart1314 (赞：7)

### [题目传送门](https://www.luogu.com.cn/problem/CF1579E2)

# 思路

手玩样例，可以发现对于即将进入双端队列的一个数 $x$，它只能到队首或到队尾（~~说了等于没说~~）。设队列里大于 $x$ 的数的数量为 $y$，小于 $x$ 的数的数量为 $z$，那么 $x$ 到队尾会产生 $y$ 个逆序对，到队首会产生 $z$ 个逆序对，取 $\min$ 即可。

一个序列，要求查询大于某个数的数的数量，小于某个数的数的数量（~~有点绕~~），还有插入某个数。这——不就是树状数组吗！~~好像~~叫做权值树状数组。

但现在有个问题，就是值域为 $10^9$，那树状数组的下标也有 $10^9$，这……。

离散化！

时间复杂度 $O(tn\log n)$。

# Code
```
#include<bits/stdc++.h>
#define PII pair<int, int>
#define fi first
#define se second
#define int long long
using namespace std;

const int N(2e5 + 7);
int t, n, x, ans, cnt, b[N], c[N];
PII a[N];
map<int, int> mp;

bool cmp(PII x, PII y) {
	return x.se < y.se;
}

void add(int x) {
	while(x <= n + 7) {
		++ c[x];
		x += x & -x;
	}
}

int sum(int x) {
	static int s;
	s = 0;
	while(x) {
		s += c[x];
		x -= x & -x;
	}
	return s;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	a[0].se = 1e18;
	cin >> t;
	while(t --) {
		memset(c, 0, sizeof c);
		cin >> n;
		ans = cnt = 0;
		for(int i(1); i <= n; ++ i) {
			cin >> a[i].fi;
			a[i].se = i;
		}
		sort(a + 1, a + n + 1);
		for(int i(1); i <= n; ++ i) {
			mp[a[i].fi] = ++ cnt;
		}
		sort(a + 1, a + n + 1, cmp);
		for(int i(1); i <= n; ++ i) {
			b[i] = mp[a[i].fi];
		}	//b数组就是离散化过的数组 
		for(int i(1); i <= n; ++ i) {
			ans += min(sum(n) - sum(b[i]), sum(b[i] - 1));
			add(b[i]);
		}	//树状数组 
		cout << ans << '\n';
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：zhaoyp (赞：5)

# Solution
 
考虑每插入一个数对总逆序对数量的影响。

1. 把 $a_i$ 从双端队列的队头入队，则产生逆序对数量为原队列中所有比 $a_i$ 小的数的数量。
2. 把 $a_i$ 从双端队列的队尾入队，则产生逆序对数量为原队列中所有比 $a_i$ 大的数的数量。

不难发现，不管将 $a_i$ 从哪里入队，对之后的决策都不会有影响（所有在 $a$ 序列中排在 $a_{i + 1}$ 前面的数都会在队列中，而 $a_{i + 1}$ 所产生的影响只跟原队列中的数有关）。

于是就可以贪心， $a_i$ 以哪种方式入队所产生的逆序对数量少，就将总逆序对数量加上它。

那么问题就转化成了维护一个序列，支持以下两种操作：
1. 在序列中插入一个数。
2. 查询序列中比某个数大或小的数。

用权值线段树即可，当然也可以离散化加普通线段树。

下面给出离散化加普通线段树的代码。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,ans,anss;
struct node
{
	long long val,x,num;
}a[200005];
struct Tree
{
	long long sum;
}t[200005 << 2];
bool cmp1(node a,node b)
{
	return a.val == b.val ? a.x < b.x : a.val < b.val;
}
bool cmp2(node a,node b)
{
	return a.x < b.x;
}
void input()
{
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++)
		scanf("%lld",&a[i].val),a[i].x = i;	
}
void prefix()
{
	for(int i = 1;i <= n * 4;i++)
		t[i].sum = 0;
	sort(a + 1,a + 1 + n,cmp1);
	for(int i = 1;i <= n;i++)
		if(i - 1&&a[i].val == a[i - 1].val)
			a[i].num = a[i - 1].num;
		else
			a[i].num = i;
	sort(a + 1,a + 1 + n,cmp2);
}
void update(int pos)
{
	t[pos].sum = t[pos << 1].sum + t[pos << 1 | 1].sum;
}
void add(int L,int R,int l,int pos,long long k)
{
	if(L > l||R < l)
		return ;
	if(L == R&&L == l)
	{
		t[pos].sum++;
		return ;
	}
	int mid = (L + R) >> 1;
	add(L,mid,l,pos << 1,k);
	add(mid + 1,R,l,pos << 1 | 1,k);
	update(pos);
}
void query(int L,int R,int l,int r,int pos)
{
	if(L > r||R < l)
		return ;
	if(L >= l&&R <= r)
	{
		anss += t[pos].sum;
		return ;
	}
	int mid = (L + R) >> 1;
	query(L,mid,l,r,pos << 1);
	query(mid + 1,R,l,r,pos << 1 | 1);
}
void work()
{
	ans = 0;
	for(int i = 1;i <= n;i++)
	{
		anss = 0;
		query(1,n,1,a[i].num - 1,1);
		long long p = anss;
		anss = 0;
		query(1,n,a[i].num + 1,n,1);
		ans += min(p,anss);
		add(1,n,a[i].num,1,1);
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		input();
		prefix();
		work();	
	}
	return 0;
}
```

---

## 作者：npqenqpve (赞：3)

### 题意：

顺序操作一个长度为 $n$ 的序列 $a_i$ ，每次可以选择将第 $i$ 个放到一个初始为空的双端队列的最前或最后，希望进行完 $n$ 次操作后逆序对数量最小化。

### 思路：

考虑贪心地放，每次计算放在最前或最后会增加的逆序对数量，选择较小的放置；

这个贪心的正确性显然，如果第 $i+1$ 个放前面，则无论如何第 $i$ 个都在第 $i+1$ 个以后，反之如果第 $i+1$ 个放在最后，则第 $i$ 个一定在其之前，所以前一个的怎么放对后面的贡献都相同，放最好的就行；

求逆序对就数据结构维护一下修改和查询排名，我写的离散化后线段树。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define ld long double
using namespace std;
int n,a[(int)(2e5+10)],t[(int)(1e6+10)],b[(int)(2e5+10)];
void add(int u,int st,int ed,int id,int k)
{
    if(st==ed) 
    {
        t[u]+=k;
        return ;
    }
    int mid=(st+ed)>>1;
    if(mid>=id) add(u*2,st,mid,id,k);
    else add(u*2+1,mid+1,ed,id,k);
    t[u]=t[u*2]+t[u*2+1];
}
int sum(int u,int st,int ed,int l,int r)
{
    if(l<=st&&r>=ed) return t[u];
    if(l>ed||r<st) return 0;
    int mid=(st+ed)>>1;
    return sum(u*2,st,mid,l,r)+sum(u*2+1,mid+1,ed,l,r);
}
signed main()
{
    int q;cin>>q;
    while(q--)
    {
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
        sort(b+1,b+1+n);
        int len=unique(b+1,b+1+n)-b-1;
        for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+len,a[i])-b;
        // for(int i=1;i<=n;i++) cout<<a[i]<<" ";
        // puts("");
        int ans=0;
        memset(t,0,sizeof(t));
        for(int i=1;i<=n;i++)
        {
            int cnt1=sum(1,1,n,a[i]+1,n),cnt2=sum(1,1,n,1,a[i]-1);
            ans+=min(cnt1,cnt2);
            add(1,1,n,a[i],1);
        }
        cout<<ans<<"\n";
    }
}
```


---

## 作者：HMZHMZHMZ (赞：3)

## 题意
给定一个序列 $ a $ 和一个双端队列，按照从 $ 1 $ 到 $ n $ 的顺序把 $ a_i $ 加入双端队列中，可以加到前端也可以加到后端。问双端队列中逆序对个数的最小值。
## 思路
我们考虑对于 $ a_i $ ，把它加到前面和后面所产生的逆序对个数算出来。
1. 将 $ a_i $ 加到前面，所产生的逆序对个数就是下标比 $ i $ 小并且值比 $ a_i $ 小的数的个数。也就是 $ \sum\limits_{j=1}^{i-1}{[a_j < a_i] } $  。

2. 将 $ a_i $ 加到后面，所产生的逆序对个数就是下标比 $ i $ 小并且值比 $ a_i $ 大的数的个数。也就是 $ n-\sum\limits_{j=1}^{i-1}{[a_j < a_i] }+sum_{a_i} $ 。(  $ sum_{a_i} $ 表示 $ a_i $ 出现的次数)

显然对于 $ a_i $ ，它的选择不影响后面的选择，因为 $ \sum\limits_{j=1}^{i-1}{[a_j < a_i]- } $ 的值不变，所以我们就可以考虑贪心，每一次选择产生逆序对数最少的就好了
## 具体做法
我们如果要求这个式子 $ \sum\limits_{j=1}^{i-1}{[a_j < a_i] } $ ，可以用树状数组来维护 $ i $ 之前比 $ a_i $ 小的数的个数。但题目中$ 1\leq a_i \leq 10^9 $,所以需要离散化。总复杂度为 $ O(Tn \log n) $ ，可以通过本题。

tips:本题需要开 `long long` ，不要忘了
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&(-x)
#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
using namespace std;
const int N=2e5+10;
int T,n,a[N],b[N],cnt[N],d[N<<1],ans;
inline void add(int x){for(;x<=n;x+=lowbit(x)) d[x]++;}//树状数组添加操作，都是模板，不细讲
inline int sum(int x){//树状数组求和操作
	int cnt=0;
	for(;x;x-=lowbit(x)) cnt+=d[x];
	return cnt;
}
inline int read(){
	int s=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		s=(s<<3)+(s<<1)+(ch^48);
		ch=getchar();
	}
	return s*f;
}
signed main(){
	T=read();
	while(T--){
		memset(cnt,0,sizeof(cnt));//记得清空！！！
		memset(d,0,sizeof(d));
		ans=0;
		n=read();
		for(register int i=1;i<=n;++i) a[i]=read();
		for(register int i=1;i<=n;++i) b[i]=a[i];//离散化
		sort(b+1,b+n+1);//sort一遍
		for(register int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+n+1,a[i])-b;//用lower_bound求出a[i]在b[i]中的位置，得到一个相对的数
		add(a[1]);//将>=a[1]的数add一遍
		cnt[a[1]]++;
		for(register int i=2;i<=n;++i){
			int s=sum(a[i]);//找之前出现过几个<=a[i]的
			ans+=MIN(s-cnt[a[i]],i-s-1);//s-cnt[a[i]]为1中的情况，i-s-1为2中的情况，ans加上他们之间的最小值
			add(a[i]);//将a[i] add一遍
			cnt[a[i]]++;
		}
		printf("%lld\n",ans);//愉快的输出答案
	}
	return 0;
}
//1322
```


---

## 作者：zqh123b (赞：1)

[luogu 传送门](https://www.luogu.com.cn/problem/CF1579E2)

[CF 传送门](https://codeforces.com/problemset/problem/1579/E2)

---

### 题意分析

~~对不起，没有~~

---

### 解题思路
1. 双端队列？！  
不就两种情况吗？即左和右。
2. 逆序对？！  
插左边不就是比该数小的数字个数，右边相反吗？
3. 最小值？！  
完全不带怕的，直接取 `min` 好吧。
4. $a_i$ 范围过大？！  
上离散化！
5. 查询太慢？！  
树状数组解决一切!
6. 没了  
乖乖写代码吧。。。

---

### 代码展示
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int t,n,a[N],b[N],c[N];
int last_one(int n){
	return n&(-n);
}
void change(int x,int k){
	while(x<=n){
		c[x]+=k;
		x+=last_one(x);
	}
}
int query(int r){
	int ans=0;
	while(r>0){
		ans+=c[r];
		r-=last_one(r);
	}
	return ans;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=a[i];
			c[i]=0;
		}
		sort(b+1,b+n+1);
		int m=unique(b+1,b+n+1)-b-1;
		for(int i=1;i<=n;i++){
			a[i]=lower_bound(b+1,b+m+1,a[i])-b;
		}
		change(a[1],1);
		int ans=0;
		for(int i=2;i<=n;i++){
			ans+=min(query(n)-query(a[i]),query(a[i]-1));
			change(a[i],1);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

### 避坑指南
1. $n \le 2 \times 10^5$ 而非 $n \le 10^5$。
2. 十年 `OI` 一场空，不开 `long long` 见祖宗。
3. $-10^9 \le a_i \le 10^9$！

---

## 作者：happybob (赞：1)

## 题意

一个 $n$ 个元素的序列和一个双端队列，按顺序每次在前或后面插入每个 $a_i$，求出插入完成后最小逆序对数量。

## 解法

比较容易的贪心。

贪心，就是局部最优导致全局最优。显然，每次插入 $a_i$，计算在前面和后面插入造成的逆序对数量，取较小的累加即可。

手玩一下样例，发现是对的。那么如何证明呢？

显然，在前面插入和后面插入，对逆序对数量有影响的总是整个队列的元素，也就是说，插入 $a_i$ 时，无论插在前面还是后面，对插入 $a_{i+1}$ 是没有影响的，显然结论成立。

至于逆序对，提供一个新的方法。计算逆序对可以平衡树维护，因为插入 $a_i$ 在前面，其实就是求队列有多少个数比 $a_i$ 小，插入后面就是大，可以转化为求排名。

单次复杂度 $O(n \log n)$，最慢的测试点 $468$ 毫秒。

还有一个问题，多测如何清空平衡树。显然，每次都 `memset` 复杂度是 $O(N t)$ 的，其中 $N$ 是数据范围，就是 $2 \cdot 10^5$。尽管 `memset` 常数很小，但是清空一个 $n$ 个元素的数组，复杂度仍然是 $O(n)$ 的，这时，循环更快。英文题面有这样一句话：

```
It is guaranteed that the sum of n over all test cases does not exceed 2 \cdot 10^5
```

翻译过来，所有测试的 $n$ 的和不超过 $2 \cdot 10^5$，那么每次只清空上次的 $n$ 的个数，总循环次数不超过 $2 \cdot 10^5$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <unordered_map>
#include <climits>
using namespace std;

#define int long long

const int N = 2e5 + 5, INF = INT_MAX;
unordered_map<int, int> mp;

int t, n;

int idx, root;

class Treap
{
public:
	struct Node
	{
		int l, r, val, cnt, sz, key;
	}tr[N];
	void pushup(int u)
	{
		tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + tr[u].cnt;
	}
	void zig(int& x)
	{
		int q = tr[x].l;
		tr[x].l = tr[q].r, tr[q].r = x, x = q;
		pushup(tr[x].r), pushup(x);
	}
	void zag(int& x)
	{
		int q = tr[x].r;
		tr[x].r = tr[q].l, tr[q].l = x, x = q;
		pushup(tr[x].l), pushup(x);
	}
	int get_node(int key)
	{
		tr[++idx].key = key;
		tr[idx].sz = tr[idx].cnt = 1;
		tr[idx].val = rand();
		return idx;
	}
	void build()
	{
		for (register int i(1); i <= idx; ++i) tr[i] = { 0, 0, 0, 0, 0, 0 };
		idx = 0;
		get_node(-INF), get_node(INF);
		root = 1;
		tr[1].r = 2;
		pushup(root);
		if (tr[1].val < tr[2].val) zag(root);
	}
	void insert(int& x, int key)
	{
		if (!x) x = get_node(key);
		else if (tr[x].key == key) tr[x].cnt++;
		else if (tr[x].key > key)
		{
			insert(tr[x].l, key);
			if (tr[tr[x].l].val > tr[x].val) zig(x);
		}
		else
		{
			insert(tr[x].r, key);
			if (tr[tr[x].r].val > tr[x].val) zag(x);
		}
		pushup(x);
	}
	int get_rank(int x, int key)
	{
		if (!x) return 0;
		if (tr[x].key == key) return tr[tr[x].l].sz + 1;
		if (tr[x].key > key) return get_rank(tr[x].l, key);
		return tr[tr[x].l].sz + tr[x].cnt + get_rank(tr[x].r, key);
	}
};

Treap tp;

signed main()
{
	scanf("%lld", &t);
	while (t--)
	{
		tp.build();
		mp.clear();
		int ans = 0, now = 0;
		scanf("%lld", &n);
		while (n--)
		{
			now++;
			int x;
			scanf("%lld", &x);
			mp[x]++;
			tp.insert(root, x);
			int k = tp.get_rank(root, x) - 1;
			ans += min(max(0ll, k - 1), max(0ll, now - (k - 1) - mp[x]));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```



---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1579E2)
## 思路
这题非常水，简单地贪心一下就好了。

$a_i$ 插入队头的贡献为原先队列中小于 $a_i$ 的数的个数，插入队尾的贡献为原先队列中大于 $a_i$ 的数的个数。

然后我们取个 $\min$，因为 $a_i$ 很大，所以还要离散化，因为 $n$ 有 $2 \times 10^5$，所以我们用树状数组求逆序对。
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=1e6+10;
int a[N],n,b[N];
struct Tree_Array{
    int c[N<<2];
    inline void clear(int n){for (int i=1;i<=n;++i) c[i]=0;}
    inline int lowbit(int x){return x&-x;}
    inline void update(int x,int v){while (x<=n) c[x]+=v,x+=lowbit(x);}
    inline int query(int x){int ans=0;while (x) ans+=c[x],x-=lowbit(x);return ans;}
}T;//树状数组模板内容
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int t;cin>>t;
    while (t--){
        cin>>n;
        for (int i=1;i<=n;++i) cin>>a[i],b[i]=a[i];
        T.clear(n<<2);//清空一下，其实清空到 n 就可以了，我清空到 4*n
        sort(b+1,b+n+1);
        int len=unique(b+1,b+n+1)-b-1;
        for (int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+len+1,a[i])-b;//离散化
        int ans=0;T.update(a[1],1);
        for (int i=2;i<=n;++i){
            ans+=min(T.query(n)-T.query(a[i]),T.query(a[i]-1));//取个 min
            T.update(a[i],1);//插入 a[i]
        }
        cout<<ans<<'\n';
    }
    return 0;
}

```


---

## 作者：苏联小渣 (赞：0)

这题被搬到了校内考试。当时发现了结论一下子忘了怎么求逆序对，打了个 $O(n^2)$ 的暴力，然后考完路上想了想就推出来了……

引以为憾。

---

首先有一个结论：对于每次操作的 $a_i$，设将其放到队头产生的逆序对数量为 $x$，放到队尾产生的逆序对数量为 $y$，那么如果 $x<y$ 就放队头，否则放队尾。

其实很好证明，因为每次只能把数放到边缘位置（就是第一个或最后一个），这个边缘位置要么在原队列中所有数的左边，要么在原队列中所有数的右边，而逆序对只关心相对位置和数字的大小关系，换句话来说，每一次操作（放队头或队尾）是**无后效性**的，所以取产生逆序对最少的位置即可。

根据逆序对的定义，$i<j,a_i>a_j$ 的 $(i,j)$，那么对于每一个 $a_i$：

放到队头，产生的逆序对数量为原队列中 $<a_i$ 的数的个数；

放到队尾，产生的逆序对数量为原队列中 $>a_i$ 的数的个数。

用权值树状数组维护即可。将每一次的最小逆序对相加就是最后的答案。注意要先离散化。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, maxn, cnt, n, s, s1, s2, a[200010], d[200010];
map <int, int> mp;
void add(int p, int x){
	for (; p<=n; p+=p&-p) d[p] += x;
}
int query(int p){
	int ret = 0;
	for (; p; p-=p&-p) ret += d[p];
	return ret;
}
signed main(){
	scanf ("%lld", &t);
	while (t --){
		memset(a, cnt=s=0, sizeof(a));
		memset(d, 0, sizeof(d));
		mp.clear();
		scanf ("%lld", &n);
		for (int i=1; i<=n; i++){
			scanf ("%lld", &a[i]);
			mp[a[i]] = 1;
		}
		map <int, int> :: iterator p;
		for (p=mp.begin(); p!=mp.end(); p++){
			mp[p->first] = ++cnt;
		}
		for (int i=1; i<=n; i++){
			add(mp[a[i]], 1);
			if (i == 1) continue;
			s1 = query(n) - query(mp[a[i]]);
			s2 = query(mp[a[i]] - 1);
			s += min(s1, s2);
		}
		printf ("%lld\n", s);
	}
	return 0;
}
```

后记：所以说考场上一定要多想啊……

---

## 作者：一铭君一 (赞：0)

# CF1579 E2

## 题目描述

给定你一个序列 $a$，要求按照顺序把 $a$ 中所有元素从队头或者队尾插入一个双端队列中，要求插入完 $a$ 中所有元素之后，双端队列中产生的逆序对数最小。

每个测试点中所有测试用例包含的 $a$ 的元素个数总和不超过 $2\times 10^5$。

## Solution

考虑安排一个数 $a_i$ 可能对答案产生的影响。

无非分两种情况，把 $a_i$ 插入到队头或者队尾：

1. 把 $a_i$ 安排到队头。此时双端队列中所有比 $a_i$ **小**的数会与 $a_i$ 产生一个逆序对。

2. 把 $a_i$ 安排到队尾。此时双端队列中所有比 $a_i$ **大**的数会与 $a_i$ 产生一个逆序对。

题目要求我们求出最少产生的逆序对，一个容易想到的贪心策略就是在上面两种方案中选择一个产生逆序对更少的执行。

现在我们用归纳法来证明这个贪心：

安排 $a_1$ 时，双端队列里没有任何元素，此时一定产生 0 的逆序对，这是最优的。

考虑安排 $a_i$ 的情况，此时 $a_1 \dots a_{i-1}$ 一定已经被安排完了。

假设我们对 $a_1 \dots a_{i-1}$ 的安排是最优的，那么我们贪心的安排 $a_i$ 得到的就是对 $a_1 \dots a_i$ 的最优安排策略。

显然我们可以把这个结论利用于 $i=2$ 的情况，因为我们已经保证了对 $a_1$ 的安排是最优的。这样，我们得到了对 $a_1,a_2$ 的最优安排策略。

然后发现，它可以继续从 $i=2$ 推广到 $i=3,4,5\dots n$ 的情况。

即：对于每一个 $i$，贪心的选取两种安排方式中产生逆序对数更小的一种就可以得到 $a_1\dots a_n$ 的最优安排策略，贪心策略正确。

剩下的问题就是搞点数据结构维护双端队列中的元素了，这个很简单，使用权值线段树/树状数组/分块/平衡树等等都可以。

## Notes

写代码的时候要注意：

* 注意值域： $-10^9 \leq a_i\leq 10^9$，这意味着我们需要进行离散化。

* 注意到 $n\leq 2\times 10^5$，而一个序列产生的逆序对数可以达到 $n^2=4\times 10^{10}$ 级别，这显然爆掉了 `int`，需要开 `long long`。

* 多测不清空，爆零两行泪。

## $\text{Talk is cheap,show you the code}$

因为我喜欢暴力数据结构，所以我写了分块来维护双端队列中的元素。

~~不会真的有人闲到去写线段树或者平衡树吧，不会吧不会吧。。。~~

```cpp
#define int long long//这句很重要
const int maxn=200005;

int T;
int n,ans;
int A[maxn],B[maxn];

int bel[maxn],L[1005],R[1005],len,tot,it;
int num[1005],cnt[maxn];
//分块数组

void init(){
  memset(num,0,sizeof num);
  memset(cnt,0,sizeof cnt);
  memset(bel,0,sizeof bel);
  memset(L,0,sizeof L);
  memset(R,0,sizeof R);
  memset(A,0,sizeof A);
  memset(B,0,sizeof B);
  ans=n=len=tot=it=0;
  read(n);
  for(int i=1;i<=n;++i) B[i]=read(A[i]);
  
  std::sort(B+1,B+1+n);
  it=std::unique(B+1,B+1+n)-B-1;
  for(int i=1;i<=n;++i)
    A[i]=std::lower_bound(B+1,B+it+1,A[i])-B;
  //读入+离散化
  len=sqrt(it);
  tot=it/len;
  for(int i=1;i<=it;++i) bel[i]=(i-1)/len+1;
  for(int i=1;i<=tot;++i){
    if(i*len>it) break;
    L[i]=(i-1)*len+1;
    R[i]=i*len;
  }
  if(R[tot]<it) tot++,L[tot]=R[tot-1]+1,R[tot]=it;
  //初始化值域分块
}

int check_less(const int k){
  int sum=0,i;
  for(i=1;i<bel[k];++i)
    sum+=num[i];
  for(int j=L[i];j<k;++j)
    sum+=cnt[j];
  return sum;
}
int check_more(const int k){
  int sum=0,i;
  for(i=tot;i>bel[k];--i)
    sum+=num[i];
  for(int j=R[i];j>k;--j)
    sum+=cnt[j];
  return sum;
}

signed main(){
  read(T);
  while(T--){
    init();
    for(int i=1;i<=n;++i){
      int a=check_less(A[i]),b=check_more(A[i]);
      if(a>b) ans+=b;
      else ans+=a;
      cnt[A[i]]++,num[bel[A[i]]]++;
    }
    write(ans),putchar('\n');
  }
  return 0;
}
//write(x),read(x)是输出/读入一个整数，为了简便，省略了
```

---

## 作者：Jairon314 (赞：0)

$ Solution $

----------

// 不敢再乱用 latex 了...

可以发现，这道题每次往 deque 中放入一个数字，都会对当前全局所有的数字产生可能的贡献，与此时 deque 中原有数字的顺序无关。所以可以贪心，考虑从前面放入数字和后面放入数字对当前全局产生了多少逆序对，然后模拟即可。逆序对用树状数组求就行了，别忘了离散化呦~

注意：每次往 deque 前面放入一个数字 val ，对逆序对数产生的贡献为此时 deque 中比 val 小的数字个数；每次往 deque 后面放入一个数字 val ，对逆序对数产生的贡献为此时 deque 中比 val 大的数字个数。贪心比较即可，树状数组维护。


```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;
 
#define int long long
 
/***** Fast_IO *****/
 
using std::cin;
using std::cout;
using vii = std::vector<int> ;
using pii = std::pair<int,int> ;
 
namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;
 
	inline char gc (){
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<21),stdin),p1==p2)?EOF:*p1++;
	}
 
	#define gc getchar
	#define pc putchar
	#define ONLINE_JUDGE OJ
 
	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}
 
	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
 
	void _FILE(){
		#ifndef ONLINE_JUDGE
			freopen("text.in","r",stdin);
			freopen("text.out","w",stdout);
		#endif
	}
 
	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define each(i,v) for(auto &i:v)
	#define all(v) v.begin(),v.end()
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
}using namespace IO;
 
/***** Fast_IO *****/
 
#define maxn 1000010
#define SIZE 5010
 
int T,n;
long long a[maxn];
 
// ::deque<int> de;
 
class TA{
	#define lowbit(k) ((k)&(-k))
 
	private:
		long long tree[maxn];
 
	public:
		void clear(){
			memset(tree,0,sizeof tree);
		}
 
		void add(int x,long long val){
			for(;x<=n;x+=lowbit(x)){ tree[x]+=val; }
			return;
		}
 
		long long query(int x){
			long long res=0;
			for(;x>0;x-=lowbit(x)){ res+=tree[x]; }
			return res;
		}
}ta;
 
long long cnt[maxn];
int b[maxn];
 
signed main(){
	_FILE();
	read(T);
	while(T--){
		long long ans=0;
		memset(cnt,0,sizeof cnt);
		ta.clear();
		read(n);
		FOR(i,1,n){ read(a[i]); b[i]=a[i]; }
		::sort(b+1,b+n+1);
		int size_b=::unique(b+1,b+n+1)-(b+1);
		FOR(i,1,n){
			a[i]=::lower_bound(b+1,b+size_b+1,a[i])-(b);
		}
		FOR(i,1,n){
			int val=a[i];
			if(i==1){
				ta.add(val,1);
				// de.pb(val);
				++cnt[val];
				continue;
			} else{
				long long res=ta.query(val-1);
				// outn(val),outn(res);
				++cnt[val];
				if(res<=i-res-cnt[val]){
				// 	de.push_front(val);
					ans+=res;
				} else{
					ans+=i-res-cnt[val];
				// 	de.pb(val);
				}
				ta.add(val,1);
			}
			// ++cnt[val];
		}
		outn(ans);
	}
	return 0;
}
```


---

