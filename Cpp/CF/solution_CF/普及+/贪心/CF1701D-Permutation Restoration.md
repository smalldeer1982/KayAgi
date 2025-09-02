# Permutation Restoration

## 题目描述

Monocarp 有一个长度为 $n$ ，由 $1$ ~ $n$ 构成的数组  $a$ ，其中每个元素在 $a$ 中出现且仅出现 $1$ 次。

现在 Monocarp 计算一个数组 $b$ ，使得 $b_i=\lfloor\frac{i}{a_i}\rfloor$ 。

现在给出 $b$ 数组，要求求出任意一组 $a$ 。

注意：保证对于所给出的 $b$ 至少有一组 $a$ 与之对应。

## 样例 #1

### 输入

```
4
4
0 2 0 1
2
1 1
5
0 0 1 4 1
3
0 1 3```

### 输出

```
2 1 4 3 
1 2 
3 4 2 1 5 
3 2 1```

# 题解

## 作者：Morax_ (赞：17)

# [CF1701D Permutation Restoration](https://www.luogu.com.cn/problem/CF1701D) 题解

### 题目大意

有一个 $1\sim n$ 的排列 $a$ 数组，现在给定所有的 $b_i=\left\lfloor\frac{i}{a_i}\right\rfloor$，求出对应的 $a$ 数组。

### 分析

根据 $b_i=\left\lfloor\frac{i}{a_i}\right\rfloor$ 这一条件，我们可以容易的得到 $a_i$ 的范围：

* $\because b_i=\left\lfloor\frac{i}{a_i}\right\rfloor,$

  $\therefore b_i\le\frac{i}{a_i},$

  $\therefore a_ib_i\le i,$ 即 $a_i\le\frac{i}{b_i}.$

* $\because b_i=\left\lfloor\frac{i}{a_i}\right\rfloor,$

  $\therefore b_i+1>\frac{i}{a_i},$

  $\therefore a_i(b_i+1)>i,$ 即 $a_i>\frac{i}{b_i+1}.$
  

综合一下，就是 $\frac{i}{b_i+1}<a_i\le\frac{i}{b_i}$。

因此，我们对**左端点排序**，然后贪心地考虑，每次选择右端点最小的线段，这样的话其他线段有更多的选择空间。

从 $1$ 枚举到 $n$，当枚举到 $i$ 时，将每一个以 $i$ 为左端点的线段，加入到一个**以右端点排序的堆中**，每次选择最小的就行了。

### Code

```c++
#include <stdio.h>
#include <utility>
#include <queue>
#include <algorithm>

struct Node {
    int l, i;
} k [500005];
int b [500005], a [500005];
std :: priority_queue <std :: pair <int, int>, std :: vector <std :: pair <int, int> >, std :: greater <> > Q;//以右端点排序的堆（优先队列），第一维是右端点

bool cmp (Node x, Node y) {
    return x.l < y.l;
}//以左端点排序

int main () {
    int t;
    scanf ("%d", &t);
    while (t --) {
        int n;
        scanf ("%d", &n);
        for (int i = 1; i <= n; ++ i) {
            scanf ("%d", &b [i]);
            k [i] = {i / (b [i] + 1) + 1, i};//左端点和下标
        }

        std :: sort (k + 1, k + n + 1, cmp);//排序

        int cnt = 1;
        for (int i = 1; i <= n; ++ i) {
            while (cnt <= n && k [cnt].l == i) {
                int id = k [cnt].i;
                Q.push ({b [id] == 0 ? n : id / b [id], id});//插入右端点和下标
                ++ cnt;
            }
            a [Q.top ().second] = i;//取出最小值（下标）
            Q.pop ();
        }

        for (int i = 1; i <= n; ++ i)
            printf ("%d ", a [i]);//输出
        printf ("\n");
        
        while (! Q.empty ()) Q.pop ();
        for (int i = 1; i <= n; ++ i) {
            b [i] = 0;
            a [i] = 0;
            k [i] = {0, 0};
        }//多测记得清空数组
    }
}
```

---

完！

记得点个赞！


---

## 作者：intel_core (赞：5)

根据 $\lfloor \frac{i}{a_i} \rfloor =b_i$ 可以推出 $a_i \in [\lfloor \frac{i}{b_i+1}\rfloor+1,\lfloor \frac{i}{b_i} \rfloor]$。

从 $1$ 到 $n$ 依次填数，把可以填 $i$，填数的上界最小且没有填数的位置填上 $i$。

因为题目保证必须有一个合法的排列，所以这样填一定可以填出一个合法的排列。

但是这样做的复杂度是 $O(n^2)$ 的。

可以用堆优化，在枚举到 $i$ 的时候把以 $i$ 作为填数下界的位置的编号和上界放进堆里。

可以做到 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=5e5+10;
int n,a[NR],b[NR],l[NR],r[NR];
vector<int>v[NR];
#define pb push_back

struct task{
	int x,id;
	bool operator <(const task &T)const{
		return x>T.x;
	}
};
priority_queue<task>q;

int main(){
	int T;cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
			if(!b[i])l[i]=i+1,r[i]=n;
			else l[i]=i/(b[i]+1)+1,r[i]=i/b[i];
			v[l[i]].pb(i);
		}
		while(!q.empty())q.pop();
		for(int i=1;i<=n;i++){
			for(int x:v[i])q.push((task){r[x],x});
			task tmp=q.top();q.pop();
			a[tmp.id]=i; 
		}
		for(int i=1;i<=n;i++)printf("%d ",a[i]),v[i].clear();
		puts("");
	}
	return 0;
}
```

---

## 作者：_Maverick_ (赞：2)

## 题意
Monocarp 有一个长度为 $n$，由 $1$ 到 $n$ 构成的数组 $a$，其中每个元素在 $a$ 中出现且仅出现 $1$ 次。

现在 Monocarp 计算一个数组 $b$ ，使得 $b_i=\lfloor\frac{i}{a_i}\rfloor$。

现在给出 $b$ 数组，要求求出任意一组 $a$。

注意：保证对于所给出的 $b$ 至少有一组 $a$ 与之对应。
## 思路
由于有$b_i=\lfloor\frac{i}{a_i}\rfloor$。可以得到 
 $b_i \le \frac{i}{a_i}<b_i+1$，即 $\frac{i}{b_i+1}<a_i\le\frac{i}{b_i}$。
 
枚举排列 $a$ 中每个数，假设现在枚举到 $x$。对于每个 $x$，存在一些线段 $S_i$，满足 $\frac{i}{b_i+1}<x\le\frac{i}{b_i}$。

从贪心的角度来说，对于这些线段，我们选择右端点最小的线段，为其他空留下更多的选择空间。

考虑类似于尺取的方法，从 $1$ 枚举到 $n$，当枚举到 $x$ 的时候，将所有以 $x$ 为左端点的线段加入到一个以右端点为排序关键字的优先队列中，每次选取最小的即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
template < typename Tp >
void read(Tp &x) {
	x = 0;
	int fh = 1;
	char ch = 1;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') fh = -1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}
const int maxn = 500000 + 7;
int T, n, b[maxn];
void Init(void) {
	read(T);
}
pair <int, pair<int, int> > pr[maxn];
priority_queue < pair<int, int> > Q;
int ans[maxn];
void Work(void) {
	while (T--) {
		for (int i = 1; i <= n; i++) {
			ans[i] = 0;
			pr[i].first = pr[i].second.first = pr[i].second.second = 0;
		}
		read(n);
		for (int i = 1; i <= n; i++) {
			read(b[i]);
			pr[i].first = i / (b[i] + 1) + 1;
			if (b[i] == 0) pr[i].second.first = n;
			else pr[i].second.first = i / b[i];
			pr[i].second.second = i;
		}
		sort(pr + 1, pr + n + 1);
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			while (cnt <= n && pr[cnt + 1].first == i) {
				Q.push(make_pair(-pr[cnt + 1].second.first, pr[cnt + 1].second.second));
				cnt++;
			}
			int id = Q.top().second;
			Q.pop();
			ans[id] = i;
		}
		for (int i = 1; i <= n; i++) {
			printf("%d%c", ans[i], " \n"[i == n]);
		}
	}
}
int main(void) {
	Init();
	Work();
	return 0;
}
```

---

## 作者：览遍千秋 (赞：2)

## 题意简述

Monocarp 有一个由 $n$ 个数字 $1, 2, \cdots, n$ 组成的排列 $a$。

然后 Monocarp 计算出了一个由 $n$ 个数字组成的数列 $b$，满足 $b_i = \lfloor \dfrac{i}{a_i} \rfloor$。

现在 Monocarp 丢掉了排列 $a$，他希望你可以通过数列 $b$ 倒推出排列 $a$，如果有多个答案，给出任意一个即可，数据保证有解。

多测，$1 \le T \le 10^5, \sum{n} \le 5 \times 10^5$

## 问题分析

由于有 $b_i = \lfloor \dfrac{i}{a_i} \rfloor$，可以得到 $b_i \le \dfrac{i}{a_i} < b_i+1$，即 $\dfrac{i}{b_i+1} < a_i \le \dfrac{i}{b_i}$。

枚举排列 $a$ 中每个数，假设现在枚举到 $x$。对于每个 $x$，存在一些线段 $S_i$，满足 $\dfrac{i}{b_i+1} < x \le \dfrac{i}{b_i}$。

从贪心的角度来说，对于这些线段，我们选择右端点最小的线段，为其他空留下更多的选择空间。

考虑类似于尺取的方法，从 $1$ 枚举到 $n$，当枚举到 $x$ 的时候，将所有以 $x$ 为左端点的线段加入到一个以右端点为排序关键字的优先队列中，每次选取最小的即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

template < typename Tp >
void read(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

const int maxn = 500000 + 7;
int T, n, b[maxn];

void Init(void) {
	read(T);
}

pair <int, pair<int, int> > pr[maxn];
priority_queue < pair<int, int> > Q;
int ans[maxn];

void Work(void) {
	while(T--) {
		for(int i = 1; i <= n; i++) {
			ans[i] = 0; pr[i].first = pr[i].second.first = pr[i].second.second = 0;
		}
		read(n);
//		memset(ans, 0, sizeof(ans));
//		while(!Q.empty()) Q.pop();
//		memset(pr, 0, sizeof(pr));
		for(int i = 1; i <= n; i++) {
			read(b[i]);
			pr[i].first = i / (b[i] + 1) + 1;
			if(b[i] == 0) pr[i].second.first = n;
			else pr[i].second.first = i / b[i];
			pr[i].second.second = i;
		}
		sort(pr + 1, pr + n + 1);
		int cnt = 0;
		for(int i = 1; i <= n; i++) {
			while(cnt <= n && pr[cnt + 1].first == i) {
				Q.push(make_pair(-pr[cnt + 1].second.first, pr[cnt + 1].second.second));
				cnt++;
			}
			int id = Q.top().second; Q.pop();
			ans[id] = i;
		}
		for(int i = 1; i <= n; i++) {
			printf("%d%c", ans[i], " \n"[i == n]);
		}
	}
}

int main(void) {
	Init();
	Work();
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：2)

### 1 视频题解

![](bilibili:BV1Nf4y1o7Cx)

### 2 思路

首先，我们求出 $a[i]$ 的取值范围。设 $l[i]\le a[i]\le r[i]$。

我们可以发现，当 $b[i]=0$ 时 $a[i]\le n$，否则 $a[i]\le\lfloor\dfrac{i}{b[i]}\rfloor$。

根据上式，我们可以发现，$\lfloor\dfrac{i}{l[i]-1}\rfloor=b[i]+1$，并且 $l[i]-1$ 也是满足 $\lfloor\dfrac{i}{a[i]}\rfloor=b[i]+1$ 中 $a[i]$ 的最大值。

那么 $l[i]=\lfloor\dfrac{i}{b[i]+1}\rfloor+1$。但要注意的是，当 $i=n$ 且 $b[i]=0$ 时 $l[i]=n$ 而非 $n+1$。

然后，我们求出 $l[i]$ 和 $r[i]$ 之后，问题就变成了，将 $1$ 到 $n$ 之间的整数分配给 $n$ 个空，第 $i$ 个空被分配到了 $a[i]$，那么要求 $l[i]\le a[i]\le r[i]$。

我们将这 $n$ 个空，以 $r$ 为第一关键字 $l$ 为第二关键字升序排序。

依次枚举，取出 $x$，并且要求 $l[i]\le x\le r[i]$，$x$ 之前没被取出，在上述条件下 $x$ 还要最小。我们可以证明必定存在这个 $x$。

我们可以使用线段树维护每个数字是否被取出。

然后，当取数字的时候，我们使用二分判断哪个数字满足要求还尽可能小。

输出答案即可。

### 代码与记录

```cpp
//Luogu submission
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 500000
int t;
int n;
int a[max_n+2];
int b[max_n+2];
struct S{
	int id,l,r;
}s[max_n+2];
int tr[max_n<<2];
int askl(int i,int x){
	if(i==n&&!x)return n;
	return i/(x+1)+1;
}
int askr(int i,int x){
	if(!x)return n;
	return i/x;
}
bool cmp(S a,S b){
	if(a.r^b.r)return a.r<b.r;
	return a.l<b.l;
}
void build(int o,int l,int r){
	tr[o]=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build((o<<1)|1,mid+1,r);
}
int query(int o,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[o];
	int mid=(l+r)>>1;
	int res=0;
	if(ql<=mid)res+=query(o<<1,l,mid,ql,qr);
	if(qr>mid)res+=query((o<<1)|1,mid+1,r,ql,qr);
	return res;
}
void upd(int o,int l,int r,int x,int v){
	if(l==r){
		tr[o]=v;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)upd(o<<1,l,mid,x,v);
	else upd((o<<1)|1,mid+1,r,x,v);
	tr[o]=tr[o<<1]+tr[(o<<1)|1];
}
int askans(int l,int r){
	int mid,res=l;
	while(l<=r){
		mid=(l+r)>>1;
		if(query(1,1,n,mid,mid)==0)res=mid;
		if(query(1,1,n,l,mid)<mid-l+1)r=mid-1;
		else l=mid+1;
	}
	upd(1,1,n,res,1);
	return res;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1701D_1.in","r",stdin);
	freopen("CF1701D_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",b+i);
		for(int i=1;i<=n;++i){
			s[i].id=i;
			s[i].l=askl(i,b[i]);
			s[i].r=askr(i,b[i]);
		}
		sort(s+1,s+n+1,cmp);
		build(1,1,n);
		for(int i=1;i<=n;++i)a[s[i].id]=askans(s[i].l,s[i].r);
		for(int i=1;i<=n;++i)printf("%d ",a[i]);printf("\n");
	}
}
```

[记录传送门](https://www.luogu.com.cn/record/78922247)

By **dengziyue**

---

## 作者：roumeideclown (赞：1)

感觉其他题解的代码写得不是很易懂，我来一发。

# 题解：CF1701D Permutation Restoration

建议先了解：[堆](https://oi-wiki.org/ds/heap/) 以及 [优先队列](https://oi-wiki.org/lang/csl/container-adapter/#%E4%BC%98%E5%85%88%E9%98%9F%E5%88%97)。

## 题意简述

题面已经很简洁了，略过。

## 解法分析

先浅浅推一下式子：

$$ \because b_i = \lfloor \frac{i}{a_i} \rfloor $$

$$ \therefore \frac{i}{a_i} - 1 < b_i \le \frac{i}{a_i} $$

$$ \therefore \frac{i}{b_i + 1} < a_i \le \frac{i}{b_i} $$

所以对于每个 $ b_i = \lfloor \frac{i}{a_i} \rfloor $，$ a_i $ 可取的最小值为 $ \frac{i}{b_i + 1} +1 $，最大值为 $ \frac{i}{b_i} $。

因为数列 $ a $ 是一个 $1$ 到 $n$ 的排列，所以我们不妨贪心。

先按左端点（即最小值）排序，然后每次应取右端点（即最大值）最小的线段，这样可以尽量给剩下的线段更大的选择范围。

于是从 $1$ 到 $n$ 枚举变量 $i$，若存在线段的左端点为 $i$，则把它放进一个按右端点单调不降排序的优先队列中，每次取队首，令它的答案为 $i$。

注意：经实践，这里不能简单地排序之后赋答案，不论以什么为关键字排序。（这里应有一张我 WA 了 $10$ 发的截图，但是机房电脑没法截图）

## 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+5;
int b[N],ans[N]; //ans 数组为（按输入顺序）的第 i 条线段对应的答案
struct line {
	int l,r; //该线段的左、右端点
	int id; //由于需要排序，因此我们要记录下输入时对应的 i，记录在 id 中
	bool operator > (const line &t) const { //重载运算符，由于是大根堆，因此重载大于号
		return r>t.r;
	}
} a[N];
bool cmp(line x,line y) { //按左端点排序
	return x.l<y.l;
}
priority_queue<line,vector<line>,greater<line>> q; //按右端点排序的大根堆
void solve() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>b[i];
		a[i].id=i; //记 i，在上面已说过
		a[i].l=i/(b[i]+1)+1; //根据我们推出来的式子求最小值和最大值
		a[i].r=b[i]==0?n:i/b[i]; //求最大值时要特判，因为 b[i] 可能为 0，此时 a[i] 的最大值为 n
	}
	sort(a+1,a+1+n,cmp); //排序
	//这里应有一行清空队列，但是我们不难发现每组数据队中队列里的线段都会被 pop 出来赋答案，因此不用清
	int j=1; //j 表示下一个进队列的应为 a[j]
	for(int i=1;i<=n;i++) {
		while(a[j].l<i&&j<=n) j++; //找到左端点等于 i 的线段
		while(a[j].l==i&&j<=n) {
			q.push(a[j]); //当线段左端点等于 i 时，push 进队列
			j++;
		}
		line p=q.top(); //搞出队首，赋答案
		q.pop();
		ans[p.id]=i;
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	cout<<'\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
//多测
	int t;cin>>t;
	while(t--) solve();
	return 0;
}

```

---

## 作者：Purslane (赞：1)

## Solution

对于每一个 $i$ , 我们可以很容易知道 $a_i$ 的取值范围 $[l_i,r_i]$ .

现在变成了一个任务规划问题 : 

给每个数分配不同的权值 , 使得每个权值都在特定的范围内 .

这是经典的贪心 . 考虑按 $l$ 为第一关键字排序 . 维护一个优先队列 ( 或者平衡树 ) , 扫描一下 . 每个位置 , 我们都可以分配给这个数据结构内的元素 , 然后把它删掉 . 但是给谁呢 ? 贪心的考虑 , 应该给 $r$ 最小的 , 这是当务之急 , 其它的可以缓一缓 .

PS : 这种题都想用高级的知识点而不断 RE , 可以退役矣 .

code :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int T,n,a[MAXN],b[MAXN];
vector<pair<int,int>> lst[MAXN];
void work(void) {
	cin>>n;
	ffor(i,1,n) cin>>b[i];
	ffor(i,1,n) lst[i].clear();
	ffor(i,1,n) {
		int l,r;
		if(b[i]==0) l=i+1,r=n;
		else l=i/(b[i]+1)+1,r=i/b[i];
		lst[l].push_back({r,i});
	}
	set<pair<int,int>>st;
	ffor(i,1,n) {
		for(auto v:lst[i]) st.insert(v);
		auto it=*st.begin();
		a[it.second]=i;
		st.erase(st.begin());
	}
	ffor(i,1,n) cout<<a[i]<<' ';
	cout<<'\n';
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) work();
	return 0;
}
```



---

## 作者：SUNCHAOYI (赞：1)

$\forall b_i = \lfloor \dfrac{i}{a_i} \rfloor$，等价于 $a_ib_i \le i <  a_i(b_i + 1)$，所以有 $\dfrac{i}{b_i + 1} < a_i \le \dfrac{i}{b_i}$。也就是说，每一个 $b_i$ 都会对应一段 $a_i$ 的区间。由于左端点是开区间无法取到 $\dfrac{i}{b_i + 1}$，因此就是就比 $\dfrac{i}{b_i + 1}$ 大的最小整数，也就是 `i / (b[i] + 1) + 1`；右端点是闭区间，求出不大于 $\dfrac{i}{b_i + 1}$ 的最大整数，也就是 `i / b[i]`（当然，$b_i$ 为 $0$ 时显然应该是 $n$）。

便于处理，**以左端点为关键字进行排序**。考虑到随着 $i$ 的变化，每段区间的右端点都会被最先舍去。因此我们对于每一段区间，用贪心的思想取出每段中的右端点构成的集合中的最小的数作为答案。不难想到可以利用优先队列（小根堆）去维护最小值。由于数据经过了排序，所以还需要记录原来的编号，得到的最小值的编号便是原来 $a$ 数组的下标。

于是有了最终代码，加了一些注释便于理解：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 5e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,a[MAX],ans[MAX]; 
struct node
{
	int x,id;
} num[MAX];
priority_queue <pair <int,int>,vector <pair <int,int> >,greater <pair <int,int> > > q;
bool cmp (node xx,node yy)
{
	return xx.x < yy.x;
}
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);  
	t = read ();
	while (t--)
	{
		n = read ();
		for (int i = 1;i <= n;++i)
		{
			a[i] = read ();
			num[i] = {i / (a[i] + 1) + 1,i};//最后加 +1 是因为开区间无法取到
		}
		sort (num + 1,num + 1 + n,cmp);//左端点排序
		while (!q.empty ()) q.pop ();//多测的初始化不能忘记！！
		int j = 1;
		for (int i = 1;i <= n;++i)
		{
			while (j <= n && num[j].x == i)//找到符合左端点为 i 的就加入到优先队列中
			{
				int k = num[j].id;
				if (!a[k]) q.push ({n,k});
				else q.push ({k / a[k],k});
				++j;
			}
			ans[q.top ().second] = i;//取最小的右端点的编号，进行答案的更新
			q.pop ();
		}
		for (int i = 1;i <= n;++i) printf ("%d ",ans[i]);
		puts ("");
	} 
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}

```

---

## 作者：Rayman (赞：1)


给出一个数组 $b$ 其中每个元素 $b_i=\frac{i}{a_i}$
，通过数组 $b$ 求出相应的排列 $a$。

---

因为 $b_i=\frac{i}{a_i}$ 所以我们可以求出每个 $a_i$ 的取值范围。 

$\frac{i+1}{b_i+1}+1<=a_i$

当$b_i{=}\mathllap{/\,}0$时 $a_i<=\frac{i+1}{b_i}$

当$b_i=0$ 时 $a_i<=n$

所以就是在 $n$ 条线段中每条都取一个数字。 可以用贪心的方法来选择数字 $1$ 到 $n$ 的位置。建立数组 $l$ 和 $r$ 存储左范围和右范围，从数字 $1$ 到 $n$ 依次将可取该数字的位置的右范围放入最小堆维护，每次选择的时候，选择右范围最小的位置将该数字放入。

---
```cpp
// Problem: D. Permutation Restoration
// Contest: Codeforces - Educational Codeforces Round 131 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1701/problem/D
// Memory Limit: 256 MB
// Time Limit: 4000 ms

#include<bits/stdc++.h>
#define endl '\n'
#define fi first
#define se second
#define ll long long
#define m_p(a,b) make_pair(a,b)
using namespace std;
typedef vector<int> vint;
typedef pair<int,int> pii;





int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int times; cin>>times;
	while(times--) {
		int n; cin>>n;
		vint a(n);
		for(int i=0;i<n;i++) cin>>a[i];
		vint r(n);
		vint ans(n); 
		vector<vint> tt(n+1);
		for(int i=0;i<n;i++) {
			r[i]=(a[i]==0?n:(i+1)/a[i]);
			tt[(i+1)/(a[i]+1)+1].push_back(i);
		}
		set<pii> t; 
		for(int i=1;i<=n;i++) {
			for(auto j:tt[i]) t.emplace(r[j],j); 
			//将左范围为i的右范围全部放入最小堆
			ans[t.begin()->se]=i; 
			t.erase(t.begin());
		}
		for(int i=0;i<n;i++) cout<<ans[i]<<' ';
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：qwq___qaq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1701D)

首先，求出每个位置的最小可取值 $l$、最大可取值 $r$。

然后按照 $r$ 排序，确定一个选择 $a$ 的顺序（这里选择从小到大），然后，把右端点可以覆盖的，暂时放在一起。

因为左端点最大的会最先废掉，所以我们可以考虑把那些左端点最小的先得到 $a$，这一步可以用优先队列维护。

每一个都只会赋一个 $a$，时间复杂度 $O(n\log n)$。

---

