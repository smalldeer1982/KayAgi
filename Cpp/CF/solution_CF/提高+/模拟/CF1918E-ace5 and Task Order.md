# ace5 and Task Order

## 题目描述

This is an interactive problem!

In the new round, there were $ n $ tasks with difficulties from $ 1 $ to $ n $ . The coordinator, who decided to have the first round with tasks in unsorted order of difficulty, rearranged the tasks, resulting in a permutation of difficulties from $ 1 $ to $ n $ . After that, the coordinator challenged ace5 to guess the permutation in the following way.

Initially, the coordinator chooses a number $ x $ from $ 1 $ to $ n $ .

ace5 can make queries of the form: $ ?\ i $ . The answer will be:

- $ > $ , if $ a_i > x $ , after which $ x $ increases by $ 1 $ .
- $ < $ , if $ a_i < x $ , after which $ x $ decreases by $ 1 $ .
- $ = $ , if $ a_i = x $ , after which $ x $ remains unchanged.

The task for ace5 is to guess the permutation in no more than $ 40n $ queries. Since ace5 is too busy writing the announcement, he has entrusted this task to you.

## 说明/提示

In the first test, the hidden permutation is $ a $ = \[ $ 2,4,1,5,3 $ \], and the initial value of $ x $ is $ 3 $ .

In the second test, the hidden permutation is $ a $ = \[ $ 2,1 $ \], and the initial value of $ x $ is $ 1 $ .

## 样例 #1

### 输入

```
2
5

>

=

<

=

<

<

2

>```

### 输出

```
? 4

? 2

? 1

? 5

? 1

? 3

! 2 4 1 5 3

? 1

! 2 1```

# 题解

## 作者：caibet (赞：5)

调交互题喜欢不写交互程序？

---

[题目链接](https://www.luogu.com.cn/problem/CF1918E)

简单分析这个询问：获得 $x$ 与某个数的大小关系，并使 $x$ 向这个数逼近。因此不难想到询问次数平方级别的做法：对于一个数，反复对其进行询问，直到结果为相等，根据询问次数可以得到这个数和 $x$ 的差值。对于所有数都如此，便能求出整个排列。

如何优化？考虑对于每个值求其位置，进行分治。类似快速排序，在值域区间 $[l,r]$ 中找出哪个位置值为 $mid=\lfloor{l+r\over 2}\rfloor$，将 $mid$ 值所在的位置设为它。之后将值小于 $mid$ 的位置放在左区间，大于 $mid$ 的位置放在右区间，再对于两个子区间递归求解。

首先看如何求 $mid$ 值所在的位置。在不知道 $x$ 的时候似乎不好求，假如能使 $x=mid$，并且能够随意让其增减（用于还原 $x$ 为 $mid$），就能对于区间内每个数询问，结果是相等时就得到了这个位置。

考虑找到原序列的最小，最大值，较为好想。以最大值为例，需要尽量使 $x$ 增大，可以对于每个数询问，如果结果为大于则一直询问直到结果为等于为止；如果结果为等于则暂定当前为最大位置；如果结果为小于且当前存在暂定的最大位置则询问一次最大位置用来还原 $x$（如果不存在，则最大值一定在当前位置之后，以后 $x$ 也会增大）。最小值同理。

求出最大位置之后，$x=n$；求出最小位置之后，$x=1$。询问一次最大位置 $x\leftarrow \min(n,x+1)$；询问一次最小位置，$x\leftarrow\max(1,x-1)$。这样我们就掌控了 $x$。

然后看如何比较 区间内的位置 在原序列上的数 和 $mid$ 的大小关系。显然对于每个位置询问一下再用最大最小值还原一下即可。

结合起来就做完了。可以参考代码理解：

```cpp
namespace{
	int T;
	const int N=2e3+3;
	int n,p[N],ans[N];
	int query(int i){
		cout<<"? "<<i<<endl;
		char c;
		cin>>c;
		return c=='>'?1:c=='='?0:-1;
	}
	int mn,mx,x;
	void find(int l,int r){
		if(l>=r) return;
		int mid=l+r>>1;
		// 将 x 移动到 mid 
		while(x<mid) query(mx),++x;
		while(x>mid) query(mn),--x;
		vector<int> vl,vr;
		int pmid=0;
		// 找到值为 mid 的位置，顺便求出每个位置在原数列中的数和 mid 的大小关系 
		F(i,l,<=r){
			int ret=query(p[i]);
			if(ret==1) vr.pb(p[i]),query(mn);
			else if(ret==-1) vl.pb(p[i]),query(mx);
			else pmid=i;
		}
		swap(p[pmid],p[mid]);
		F(i,0,<vl.size()) p[l+i]=vl[i];
		F(i,0,<vr.size()) p[mid+1+i]=vr[i];
		find(l,mid-1);
		find(mid+1,r);
	}
	void solve(){
		cin>>n;
		mn=mx=0;
		F(i,1,<=n){
			int ret=query(i);
			if(ret>=0){
				mx=i;
				while(ret==1) ret=query(i);
			}else if(mx) query(mx);
		}
		F(i,1,<=n){
			int ret=query(i);
			if(ret<=0){
				mn=i;
				while(ret==-1) ret=query(i);
			}else if(mn) query(mn);
		}
		p[1]=mn;p[n]=mx;
		x=1;// 求出最小位置后，x 一定为 1 
		int tmp=1;
		F(i,1,<=n){
			if(i==mn||i==mx) continue;
			p[++tmp]=i;
		}
		find(2,n-1);
		F(i,1,<=n) ans[p[i]]=i;
		cout<<"! ";
		F(i,1,<=n) cout<<ans[i]<<' ';
		cout<<endl;
	}
	void work(){
		cin>>T;
		while(T--) solve();
	}
}
```

这个算法的询问次数如何？

稍微写了一下，有非常不紧凑的上界 $(3\lfloor\log_2 n\rfloor+6)n$，实际上应该比这小得多。

---

## 作者：ax_by_c (赞：3)

# 题目大意

有一个 $n$ 个数的排列 $a$ 和一个数 $x$，每次你可以询问 $x$ 与其中某一个数的关系。

若该数大于 $x$ 则回答大于，$x$ 增加一。

若该数小于 $x$ 则回答小于，$x$ 减去一。

若该数等于 $x$ 则回答等于，$x$ 不变。

要求你在 $40n$ 次操作内确定出 $a$。

# 解题思路

可以发现用 $n$ 次操作可以把 $x$ 变为某个指定的数。

而当 $x$ 等于某个数时，我们对另一个数进行询问，即可知道该数与另一个数的大小关系。

然后再对原数问一次把 $x$ 变回来，这样比较需要两次操作。

那么此时把一个数和其他所有数比较就需要 $3n$ 次操作了。

既然我们可以用 $3n$ 次操作把小于和大于分开，所以考虑快速排序。

每次选取集合内一个数并比较其他数，分成小于和大于两个集合，再分别处理。

但如果你选取确定的一个数，以 codeforces 的风格是肯定不让你过的，所以要随机选取。

平均要跑 $\log_2 n$ 次比较，我们把 $40n$ 除以 $3n$，发现是十三多一点，而两千的 log 只有十一，脸不是太黑即可通过。

# 示例代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
const int N=2005;
mt19937 Brnd(time(0));
int n;
int a[N];
void BE(int pos){
	char gt;
	while(1){
		cout<<"? "<<pos<<endl;cout.flush();
		cin>>gt;
		if(gt=='='){
			break;
		}
	}
}
void srt(int l,int r,vi v){
	if(v.empty()){
		return ;
	}
	if(l>r){
		return ;
	}
	if(l==r){
		for(auto x:v){
			a[x]=l;
		}
		return ;
	}
	vi A,B;
	int piv=v[Brnd()%v.size()];
	BE(piv);
	char gt;
	for(auto x:v){
		if(x==piv){
			continue;
		}
		cout<<"? "<<x<<endl;cout.flush();
		cin>>gt;
		if(gt=='>'){
			B.push_back(x);
		}
		else{
			A.push_back(x);
		}
		cout<<"? "<<piv<<endl;cout.flush();
		cin>>gt;
	}
	int rp=piv;
	piv=r-B.size();
	a[rp]=piv;
	srt(l,piv-1,A);
	srt(piv+1,r,B);
}
void slove(){
	cin>>n;
	for(int i=1;i<=n;i++){
		a[i]=0;
	}
	vi v;
	for(int i=1;i<=n;i++){
		v.push_back(i);
	}
	srt(1,n,v);
	cout<<"! ";
	for(int i=1;i<=n;i++){
		cout<<a[i]<<' ';
	}
	cout<<endl;cout.flush();
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)slove();
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

世纪难题。

首先我们考虑先固定 $x$，比如让 $x = a_1$（重复问 $1$ 直到回答为 `=`），那么此时我们可以知道任意一个 $a_i$ 和 $a_1$ 的大小关系（问一次 $i$ 再问一次 $1$），并且可以知道 $a_i$ 的具体值。

那么剩下的数被分成了两个集合，一个 $< a_1$ 一个 $> a_1$。发现我们可以对这两个集合递归地做上面的过程。递归时传需要求的位置集合和值域 $[l, r]$ 即可。

问题在于询问次数没有保障。考虑每次递归时从当前集合中随机一个数作为分界点。期望询问次数 $O(n \log n)$。$40n$ 的次数限制很宽松所以能过。

[code](https://codeforces.com/problemset/submission/1918/244661758)

---

## 作者：ZMQ_Ink6556 (赞：1)

## 题解：CF1918E ace5 and Task Order

### 解题思路

要求找到整个排列所有位置的值，考虑**排序**。

则我们可以**模拟快排**，首先随机出一个中心点，对中心点持续询问直到返回 `=`。

然后就可以将这个点和整个序列内部的所有点比较，比较后还要重新询问一次这个点来消除增减造成的影响。

若有 $x$ 个数比它小，则它的值就是 $x + 1$。

其余点**分治处理**即可（断句不是“其余/点分治/处理”不要读错了）。

随机出中心点并使 $x$ 对齐的期望次数是每次对齐 $\log n$ 下 $\times n$ 个位置。

判断大小的次数期望是 $n \log n$ 次，具体参照快排复杂度分析。每次判断后要复原所以要乘以 $2$。 

总期望次数为 $3 \times n \lceil \log n \rceil$，大约 $33n$，小于题目要求的 $40n$。卡的比较紧，如果实在是运气太差一遍没过可以多交几遍。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t , n , ans[2005];
vector<int> p;
char cc;
inline void qsort(int l , vector<int> a)
{
	int x = rand() % a.size();
	cout << "? " << a[x] << endl;
	cin >> cc;
	while(cc != '=')
	{
		cout << "? " << a[x] << endl;
		cin >> cc;
	}
	vector<int> b , c;
	b.clear();
	c.clear();
	for(int i = 0 ; i < a.size() ; i++)
	{
		if(i == x)
		{
			continue;
		}
		cout << "? " << a[i] << endl;
		cin >> cc;
		if(cc == '<')
		{
			b.push_back(a[i]);
		}
		else
		{
			c.push_back(a[i]);
		}
		cout << "? " << a[x] << endl;
		cin >> cc;
	}
	ans[a[x]] = l + b.size();
	if(b.size())
	{
		qsort(l , b);
	}
	if(c.size())
	{
		qsort(l + b.size() + 1 , c);
	}
	return;
}
int main()
{
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto t = ms.time_since_epoch().count();
	srand(t);
	cin >> t;
	while(t--)
	{
		cin >> n;
		p.clear();
		for(int i = 1 ; i <= n ; i++)
		{
			p.push_back(i);
		}
		qsort(1 , p);
		cout << "! ";
		for(int i = 1 ; i <= n ; i++)
		{
			cout << ans[i] << ' ';
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：wosile (赞：1)

下午 WC 的课全是黑题不太想听于是 vp 了一场 div.2。然而 vp 的时候 [censored] 在医院所以大部分时间在和 [censored] 聊天（好像如果我去听课大部分时间也会在和 [censored] 聊天）。赛时有一点小 bug 没调完。

其实这就是个简单 *2200。

首先一个 $O(n^2)$ 次询问的解很显然：对每个位置 $i$ 不断查询直到返回 `=`，然后就可以通过大小关系直接给这 $n$ 个数排序从而得到答案。

既然排序可以得到答案，我们考虑那些 $O(n\log n)$ 的排序，比如借鉴快速排序的思路。

快速排序的过程中，我们需要对值域分治。要在控制 $x$ 的值不变的情况下查询若干个位置的答案，从而把这些位置分成“$>x$”和“$<x$”两组（$=x$ 可以直接得到答案），递归下去就可以得到答案。这看似不好办到，因为我们没法直接控制 $x$ 的值。

不过其实这个问题很容易就能解决，我们只要找到 $1$ 和 $n$ 在哪里，就能随意控制 $x$ 的值了。查询一次 $1$ 可以让 $x$ 减小 $1$，$n$ 同理。

具体来讲，我们只要扫一遍 $1\sim n $，对于每个位置，如果询问返回 `<` 就继续查直到不是 `<` 为止，否则直接不管。显然这样最多查询 $O(n)$ 次（因为 $x$ 最多增大 $n$ 次），并且在 $a_i=1$ 的地方一定可以取到 $x=1$。我们只要看 $x$ 在哪里取到最小值即可。找 $a_i=n$ 同理。

找 $1$ 和 $n$ 需要 $O(n)$ 次询问。

快速排序部分，询问次数是 $T(n)=2T(\dfrac{n}{2})+O(n)=O(n\log n)$

在对一个值域区间的询问开始前，我们需要把 $x$ 的值调整为这个区间的分割点 $mid$，这需要 $|x-mid|$ 次询问。直接先序遍历就可以让这部分的总询问次数为 $O(n\log n)$。

常数是足够小的。

讲的可能不是很清楚，但是代码很清楚，详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int p1,pn;
int ans[2005];
int query(int x){
	cout<<"? "<<x<<endl;
	cout.flush();
	string s;
	cin>>s;
	if(s[0]=='=')return 0;
	if(s[0]=='<')return -1;
	if(s[0]=='>')return 1;
	return 0114507537;
}
int cur;
void solve(int l,int r,vector<int>&v){
	// v 是值在 [l,r] 中的下标集合 
	if(l>r)return;
	if(l==r){
		ans[v[0]]=l;
		return;
	}
	int mid=(l+r)/2;
	while(cur>mid){
		query(p1);
		cur--;
	}
	while(cur<mid){
		query(pn);
		cur++;
	}
	vector<int>vl,vr;
	vl.clear();
	vr.clear();
	// 分成 [l,mid-1] 和 [mid+1,r] 
	for(int x:v){
		int tmp=query(x);
		if(tmp==0)ans[x]=mid;
		if(tmp==-1){
			vl.push_back(x);
			query(pn);
		}
		if(tmp==1){
			vr.push_back(x);
			query(p1);
		}
	}
	solve(l,mid-1,vl);
	solve(mid+1,r,vr);
} 
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		//find 1&n
		p1=pn=1;
		int md=0x3f3f3f3f,d=0;
		for(int i=1;i<=n;i++){
			int tmp=query(i);
			d+=tmp;
			while(tmp==-1){
				tmp=query(i);
				d+=tmp;
			}
			if(d<md)p1=i,md=d;
		}
		md=-0x3f3f3f3f,d=0;
		for(int i=1;i<=n;i++){
			int tmp=query(i);
			d+=tmp;
			while(tmp==1){
				tmp=query(i);
				d+=tmp;
			}
			if(d>md)pn=i,md=d;
		}
		ans[p1]=1,ans[pn]=n;
		
		vector<int>tmp;
		tmp.clear();
		for(int i=1;i<=n;i++)if(i!=p1 && i!=pn)tmp.push_back(i);
		int val=query(pn);
		while(val==1)val=query(pn);
		cur=n;
		solve(2,n-1,tmp);
		cout<<"! ";
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		cout<<endl;
		cout.flush();
	}
	return 0;
	// quod erat demonstrandum
}

```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF1918E%20ace5%20and%20Task%20Order)

# 思路

首先，你显然可以用 $3n$ 次操作求出 $a_1$ 和 $x$。同时整个序列可以按照值分为小于 $a_1$ 和大于 $a_1$ 两部分。

考虑分别处理这两个部分。你希望还可以通过分治的方法，将一个部分再分为一个部分。

但是，由于数据的不随机性，我们不能单纯的选取一个部分的第一个当作分界点，因为容易构造一个有单调性的序列，每次分治都只会被分出来一个数。

既然数据不随机，我们就选得随机。每一次随机选取一个数当作一个数，这样我们每一次分治期望情况下是能将序列平均分的。因此询问次数是 $(3 \times \log n) \times n$ 次的。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

mt19937 rnd(random_device{}());
const int N = 2010;
int n,x,arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void dfs(vector<int> v,int l,int r){
    if (l == r) return arr[v.back()] = l,void();
    int len = v.size(); int id = abs((int)rnd()) % len;
    vector<int> a,b;
    while (1){
        printf("? %d\n",v[id]); fflush(stdout);
        char op[10]; scanf("%s",op);
        if (op[0] == '<') x--;
        else if (op[0] == '>') x++;
        else break;
    }
    arr[v[id]] = x;
    for (auto p:v){
        if (p == v[id]) continue;
        printf("? %d\n",p); fflush(stdout);
        char op[10]; scanf("%s",op);
        if (op[0] == '<') a.push_back(p);
        else b.push_back(p);
        printf("? %d\n",v[id]); fflush(stdout);
        scanf("%s",op);
    }
    if (!a.empty()) dfs(a,l,x - 1);
    if (!b.empty()) dfs(b,x + 1,r);
}

inline void solve(){
    vector<int> a,b;
    int num = 1;
    n = read();
    while (1){
        puts("? 1"); fflush(stdout);
        char op[10]; scanf("%s",op);
        if (op[0] == '=') break;
    }
    for (re int i = 2;i <= n;i++){
        printf("? %d\n",i); fflush(stdout);
        char op[10]; scanf("%s",op);
        if (op[0] == '<'){
            num++; a.push_back(i);
        }
        else b.push_back(i);
        puts("? 1"); fflush(stdout);
        scanf("%s",op);
    }
    arr[1] = x = num;
    if (!a.empty()) dfs(a,1,num - 1);
    if (!b.empty()) dfs(b,num + 1,n);
    printf("! ");
    for (re int i = 1;i <= n;i++) printf("%d ",arr[i]);
    puts(""); fflush(stdout);
}

int main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：hcywoi (赞：0)

考虑将该序列排序。

使用快速排序，随机一个数 $m$，一直询问下标 $m$，直到返回 `=`。

我们发现，当前 $x$ 就等于 $a_m$（$a$ 表示排列）。

遍历序列，记当前下标为 $i$，询问下标 $i$，如果满足了询问前 $x$ 的值等于 $a_m$，那么返回 `<`，说明 $a_i<a_m$；返回 `>`，说明 $a_i>a_m$。显然，每次操作完后询问 $m$，即可满足以上限制。

显然，期望询问次数是小于 $40n$。

---

### 代码
```cpp
#include <bits/stdc++.h>

using i64 = long long;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    std::cin >> n;

    auto ask = [&](int x) {
        std::cout << "? " << x + 1 << std::endl;
        char c;
        std::cin >> c;
        return c;
    };

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    auto quick_sort = [&](auto self, std::vector<int> p) -> std::vector<int> {
        if (!p.size()) {
            return {};
        }

        int sz = p.size();
        int m = rnd() % sz;
        while (ask(p[m]) != '=');
        std::vector<int> l, r;
        for (int i = 0; i < sz; i ++ ) {
            if (i != m) {
                if (ask(p[i]) == '<') {
                    l.push_back(p[i]);
                } else {
                    r.push_back(p[i]);
                }
                ask(p[m]);
            }
        }

        auto ql = self(self, l);
        auto qr = self(self, r);
        std::vector<int> q;
        for (auto x: ql) {
            q.push_back(x);
        }
        q.push_back(p[m]);
        for (auto x: qr) {
            q.push_back(x);
        }
        return q;
    };
    auto q = quick_sort(quick_sort, p);

    std::vector<int> ans(n);
    for (int i = 0; i < n; i ++ ) {
        ans[q[i]] = i + 1;
    }
    std::cout << "! ";
    for (int i = 0; i < n; i ++ ) {
        std::cout << ans[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t -- ) {
        solve();
    }

    return 0;
}
```

---

## 作者：Remarks (赞：0)

提供一个时间复杂度同快速排序的随机化做法。

首先关注到我们可以不断地询问一个位置直至返回量为 `=` 来使得 $x$ 与询问的位置的值相等。

其次关注到，若一个时刻 $x$ 与位置 $k$ 上的数相等，我们询问任意一个位置再询问 $k$，$x$ 的值不变。（因为如果 $x$ 加一，询问 $k$ 会使其减一，反之则减一加一）。

因为 $x$ 是未知量，我们考虑先随机一个位置，假定其为 $pos$，然后不断进行上文的操作使 $x$ 等于该位置的值，即为 $A_{pos}$。这部分的代价为 $n$。

然后我们要确定这个位置的值，观察到原序列为一个排序，所以小于一个值的数的个数加一即为该值。我们询问所有非 $pos$ 的位置，再询问 $pos$。第一步可以得到该位置与 $A_{pos}$ 的大小关系，第二步可以修正 $x$ 使其再次等于 $A_{pos}$。由此得到有多少数小于 $A_{pos}$，即可得到 $A_{pos}$ 的值。此部分的代价为 $2\times n$。并且将原来的序列中所有位置分为了两个集合，一集合中对应原序列的值为 $[A_{pos}+1,n]$，另一集合为 $[1,A_{pos}-1]$。

然后我们考虑分治解决问题。对于一部分数，假如我们知道了其值域为 $[l,r]$，位置的集合为 $S$，那么我们可以仿照上一步，在 $S$ 中任选一个位置 $p$，然后使 $x$ 变为这个数，然后再询问整个集合中的所有位置，根据值域得到 $A_p$，并且确定了这个集合中那些位置的数大于 $A_p$，哪些位置小于 $A_P$。大于 $A_p$ 的部分的值域显然为 $[A_p+1,r]$，小于的部分为 $[l,A_p-1]$，再次分治即可。



随机算法，期望的代价为 $n\log n$，足以通过此题。本人一发过了。

代码：（仅供参考） https://codeforces.com/contest/1918/submission/244199336

---

## 作者：dark_moon (赞：0)

**[更好的阅读体验](https://www.cnblogs.com/cndarkmoon/articles/17998636)**

做法：基于整体二分的排序

$x$ 的值配合上评测机的回答可以提供很多信息，所以我们考虑将这个值尽量掌控在自己手里。

首先，我们可以找到最小值和最大值，这样子就可以自己操作 $x$ 的值。

假设我们要找到最大值。我们可以从 $1$ 到 $n$ 依次询问，如果回答大于号，就继续询问，如果是小于号，就及时止损，询问下一个数，如果是等于号，就可以考虑更新答案。但是到底要不要更新答案呢？我们注意到，虽然我们不能知道 $x$ 的值，但是可以知道他的变化量，也便是说，可以记录一个 $now$ 表示变化量，如果收到了大于号，就增加，否则就减小，等到收到了等于号，就判断这个变化量是个正数还是负数，如果是正数，那么当前询问的数就有可能是最大值，否则就不可能。如果是正数，不仅要更新答案，还要更新 $now$ 为 $0$，因为我们本质是要比较当前这个等于号对应的数字是否比上一个答案大。

找最小值则反过来即可。

现在我们拿到了最大值和最小值，我们就拿到了随意操控 $x$ 的权力。由于答案序列是一个排列，所以我们可以考虑排序以获得答案。根据题意易得，我们可以做到将一个数与 $x$ 值作比较，并且这个 $x$ 值可以由我们操控，所以可以整体二分，确定 $x$ 值后将比 $x$ 小的放在左面，大的放在右面，然后递归处理。

这样共会进行 $n\log{n}$ 次比较，每次比较需要一次操作比较一次操作还原 $x$（比较后 $x$ 的值会改变），而按照先左再右的递归，$x$ 的值最多改变 $n\log{n}$ 次，再加上刚开始寻找最小值和最大值，均是最坏均摊 $2n$ 次，可以顺利在限定次数内完成任务。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2005;
int t, n, now, a1[N], a2[N], ma, mi, a[N], sum;
char c;
void print(int x){
	cout << "? " << x << "\n";
	cout.flush();
	assert(sum <= 40 * n);
	return;
}
int makeMin(){
	int ans = 0, now = 0, la = 1;
	for(int i = 1; i <= n; i ++){
		while(1){
			print(i);
			cin >> c;
			if(c == '<')
			now --;
			else if(c == '>'){
				now ++;
				break;
			}
			else if(c == '='){
				if(now < la)
				ans = i, la = now;
				break;
			}
		}
	}
	return ans;
}
int makeMax(){
	int ans = 0, now = 0, la = -1;
	for(int i = 1; i <= n; i ++){
		while(1){
			print(i);
			cin >> c;
			if(c == '>')
			now ++;
			else if(c == '<'){
				now --;
				break;
			}
			else if(c == '='){
				if(now > la)
				ans = i, la = now;
				break;
			}
		}
	}
	return ans;
}
void dfs(int l, int r){
	if(l == r)
	return;
	int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
	while(now < mid){
		print(ma);
		cin >> c;
		now ++;
	}
	while(now > mid){
		print(mi);
		cin >> c;
		now --;
	}
	for(int i = l; i <= r; i ++){
		print(a[i]);
		cin >> c;
		if(c == '<'){
			a1[++cnt1] = a[i];
			print(ma);
			cin >> c;
		}
		else if(c == '=')
		a1[++cnt1] = a[i];
		else{
			a2[++cnt2] = a[i];
			print(mi);
			cin >> c;
		}
	}
	for(int i = l; i <= l + cnt1 - 1; i ++)
	a[i] = a1[i - l + 1];
	for(int i = l + cnt1; i <= r; i ++)
	a[i] = a2[i - l - cnt1 + 1];
	dfs(l, mid);
	dfs(mid + 1, r);
	return;
}
signed main(){
	cin >> t;
	while(t --){
		sum = 0;
		cin >> n;
		ma = makeMax();
		mi = makeMin();
		for(int i = 1; i <= n; i ++) 
		a[i] = i;
		while(1){
			print(mi);
			cin >> c;
			if(c == '=')
			break;
		}
		now = 1;
		dfs(1, n);
		int ans[n + 5] = {0};
		for(int i = 1; i <= n; i ++)
		ans[a[i]] = i;
		cout << "! ";
		for(int i = 1; i <= n; i ++)
		cout << ans[i] << " ";
		cout << "\n";
		cout.flush();
	}
	return 0;
}
```

---

## 作者：言琢დ (赞：0)

可能是土著人没玩过现代玩具，所以这里有一只老东西觉得这道交互题很好玩。

题意很简单，就是给你一个排列 $\{a_n\}$ 和一个未知数 $x$，每次询问会告诉你 $a_i$ 和 $x$ 的大小关系，并让 $x$ 向 $a_i$ 方向移动 $1$ 个单位（想象成数轴）若 $x=a_i$ 则不移动。

然后就有了一个随机化做法，对于每次询问队列 $A$，每次利用随机函数找到一个哨兵 $who$，然后暴力询问直到 $x=A[who]$ 之后，用这个哨兵再对 $A$ 中的询问进行分类。

由于这个东西是随机的，所以期望的复杂度在 $\log$ 级别，又因为 $\sum n\le2000$，所以 $O(n^2\log n)$ 可以跑得过去。

```cpp
char getch(){
  char x; std::cin >> x; return x;
}
int init(){
  int x; std::cin >> x; return x;
}
char Query(int id){
  std::cout << '?' << ' ' << id << std::endl;
  return getch();
}
int Rand(int L, int R){
  return L + rand() % (R-L+1);
}
void go(std::vector<int>&A, std::vector<int>&ans){
  /* 尝试询问 A 中的下标*/
  int who = Rand(0, A.size() - 1); // 选定哨兵
  while (Query(A[who]) != '=') ;
  std::vector<int>L, R;
  for (std::vector<int>::iterator it = A.begin(); it != A.end(); ++it) {
    int val = *it;
    char now = Query(val);
    if (now == '<') L.push_back(val); // 小于 who 的分为一类
    else if (now == '>') R.push_back(val); // 大于 who 的分为一类
    Query(A[who]);
  }
  if (!L.empty()) { // 对小于 who 的一类排序
    std::vector<int>ansL;
    go(L, ansL);
    for (std::vector<int>::iterator it = ansL.begin(); it != ansL.end(); ++it)
      ans.push_back(*it);
  }
  ans.push_back(A[who]);
  if (!R.empty()) { // 对大于 who 的一类排序
    std::vector<int>ansR;
    go(R, ansR);
    for (std::vector<int>::iterator it = ansR.begin(); it != ansR.end(); ++it)
      ans.push_back(*it);
  }
}
int main(){
  std::ios::sync_with_stdio(false);
  srand(time(NULL));
  int T = init();
  while (T--) {
    int n = init();
    std::vector<int>A, ans;
    for (int i = 1; i <= n; ++i)
      A.push_back(i);
    go(A, ans);
    std::cout << "! ";
    for (int i = 1; i <= n; ++i)
      for (int j = 0; j < n; ++j)
        if (ans[j] == i) std::cout << j+1 << ' '; // 这个下标的对应关系要注意
    std::cout << std::endl;
  }
}
```

---

## 作者：MaxBlazeResFire (赞：0)

有个简单的构造，设我们现在要求得位置集合 $S$ 的答案，我们不断询问其第一个元素 $z_0$，直到得到一个 `=`，把 $x$ 调整到 $p_{z_0}$；然后依次问 $S$ 中的每个元素，这样可以把 $S$ 中的所有元素按照关于 $p_{z_0}$ 的大小分成两份，可以递归。

但是这样的总询问次数是多少呢？我们发现，每次递归时询问第 $1$ 个元素花的总步数是 $O(n)$ 的，可以通过分治树归纳证明。但是第二部分询问每个元素的总步数，实际上是分治树所有节点的深度之和，如果我们每次取第一个元素询问，而排列原来就是有序的话，它就会形成一条链也就是 $O(n^2)$ 级别。更本质地，这其实是一个快速排序的过程。

怎么办呢？`random_shuffle` 一下就行。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 2005

inline void ff(){ fflush( stdout ); }

int n;
char s[3];

vector<int> anseq;

inline void modix( int target ){
	printf("? %d\n",target); ff(); scanf("%s",s + 1);
	while( s[1] != '=' ) printf("? %d\n",target),ff(),scanf("%s",s + 1);
}

void divide_conquer( vector<int> numbers ){
	int siz = numbers.size();
	if( siz <= 1 ){ for( int ele : numbers ) anseq.emplace_back( ele ); return; }
	random_shuffle( numbers.begin() , numbers.end() );
	int z0 = numbers[0]; modix( z0 );
	vector<int> less,grea;
	for( int i = 1 ; i < siz ; i ++ ){
		printf("? %d\n",numbers[i]); ff(); scanf("%s",s + 1);
		if( s[1] == '<' ) less.emplace_back( numbers[i] );
		else grea.emplace_back( numbers[i] );
		printf("? %d\n",z0),ff(),scanf("%s",s + 1);
	}
	divide_conquer( less );
	anseq.emplace_back( z0 );
	divide_conquer( grea );
}

int Ans[MAXN];
inline void solve(){
	scanf("%d",&n);
	vector<int> Ns; for( int i = 1 ; i <= n ; i ++ ) Ns.emplace_back( i );
	anseq.clear(); divide_conquer( Ns );
	for( int i = 1 ; i <= n ; i ++ ) Ans[anseq[i - 1]] = i;
	printf("!");
	for( int i = 1 ; i <= n ; i ++ ) printf(" %d",Ans[i]); puts(""); ff();
}

signed main(){
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

