# Buy Tickets

## 题目描述

春节期间在中国买火车票很困难，所以我们必须早起并加入长队……  春节即将来临，但不幸的是，小猫仍然有安排要去各地。现在，他必须乘火车前往四川省绵阳，参加信息学奥林匹克国家队的冬令营选拔。  现在是凌晨一点，外面一片漆黑。来自西北的寒风并没有吓退排队的人群。寒冷的夜晚让小猫打了个寒颤。为什么不找个问题来思考呢？这总比冻死要好！  人们不断插队。由于周围太黑，这种行为即使是排在插队者旁边的人也无法发现。「如果队列中的每个人都被分配了一个整数值，并且给出了所有插队者的信息以及他们插队后的站位，我能否找出队列中人们的最终顺序？」小猫想道。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4
0 77
1 51
1 33
2 69
4 
0 20523
1 19243
1 38900
0 31492```

### 输出

```
77 33 69 51
31492 20523 38900 19243```

# 题解

## 作者：BpbjsGreen (赞：12)

树状数组上二分。

---

经过人工模拟，发现正着做对序列的操作是很繁琐的。

不妨**从最后一个人开始往前考虑**。

以样例 #1 为例。

最后一个人 $69$ 插入后其前面有 $2$ 个人，说明他在（现在考虑的）$2$ 个空位之后的空位，即第 $3$ 位。

|空位|空位|$69$|空位|
|:-:|:-:|:-:|:-:|

倒数第二个人 $33$ 插入后其前面有 $1$ 个人，说明他在（现在考虑的）$1$ 个空位之后的空位，即第 $2$ 位。

|空位|$33$|$69$|空位|
|:-:|:-:|:-:|:-:|

倒数第三个人 $51$ 插入后其前面有 $1$ 个人，说明他在（现在考虑的）$1$ 个空位之后的空位，即第 $4$ 位。

|空位|$33$|$69$|$51$|
|:-:|:-:|:-:|:-:|

再对于倒数第四个人 $77$ 这样做，得到答案：

|$77$|$33$|$69$|$51$|
|:-:|:-:|:-:|:-:|

考虑用树状数组维护：每个位置初始化成 $1$ 表示空闲。如果 $P$ 排在 $i$ 个人之后，在树状数组上二分找到前面有 $i$ 个空位的位置，即 $P$ 的位置。标记答案，把 $P$ 的位置 $-1$ 变为 $0$ 即可。

```cpp
// ID: @BpbjsGreen

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int n, c[N], ans[N], t[N], r[N];

int lowbit(int x) { return x & (-x); }
void add(int x, int d)
{
    for (; x <= 2e5; x += lowbit(x))
        c[x] += d;
}
int query(int x) // 树状数组上二分
{
    int pos = 0, sum = 0;
    for (int j = 18; j >= 0; j--)
    {
        if (pos + (1 << j) <= n && sum + c[pos + (1 << j)] <= x)
        {
            pos += (1 << j);
            sum += c[pos];
        }
    }
    return pos;
}

int main()
{
    // freopen("I.in", "r", stdin);
    // freopen("O.out", "w", stdout);

    while (scanf("%d", &n) != EOF) // 读入
    {
        for (int i = 1; i <= n; i++)
            add(i, 1);
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &t[i], &r[i]);
        for (int i = n; i >= 1; i--)
        {
            int pos = query(t[i]);
            pos += 1; // + 1 找到当前人的位置
            ans[pos] = r[i]; // 记录答案
            add(pos, -1); // 空位 - 1
        }
        for (int i = 1; i <= n; i++)
            printf("%d ", ans[i]);
        printf("\n");
    }
}

```

---

## 作者：aCssen (赞：3)

### Solution

vector 的插入不是 $\mathcal O(n)$ 的吗。

插入考虑使用平衡树。具体地，使用 fhq treap 实现文艺平衡树，每次分裂出前 $P_i$ 个数再合并起来即可。

平衡树的中序遍历就是原顺序。

### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int maxn=2e5+5;
struct node{
	int ls,rs,siz,val,dat;
}t[maxn];
int root,seed=19260817,tot;
int rnd(){
	int ret=seed;
	seed=(seed*7+13)%1000000007;
	return ret;
}
int Random(int N){
	return 1ll*rnd()*rnd()%N+1;
}
int New(int val){
	t[++tot]=(node){0,0,1,val,Random(998244353)};
	return tot;
}
void pushup(int p){
	t[p].siz=t[t[p].ls].siz+t[t[p].rs].siz+1;
}
void split(int x,int S,int &p,int &q){
	if(!x) return p=q=0,void();
	if(t[t[x].ls].siz+1<=S){
		p=x;
		split(t[x].rs,S-t[t[x].ls].siz-1,t[x].rs,q);
	}
	else{
		q=x;
		split(t[x].ls,S,p,t[x].ls);
	}
	pushup(x);
}
int merge(int x,int y){
	if(!x||!y) return x|y;
	if(t[x].dat<t[y].dat){
		t[x].rs=merge(t[x].rs,y);
		pushup(x);
		return x;
	}
	t[y].ls=merge(x,t[y].ls);
	pushup(y);
	return y;
}
void out(int p){
	if(!p) return;
	out(t[p].ls);
	Write(t[p].val,' ');
	out(t[p].rs);
}
int main(){
	int n;
	while(~scanf("%d",&n)){
		tot=root=0;
		for(int i=1;i<=n;i++){
			int p=read(),v=read(),x,y;
			split(root,p,x,y);
			root=merge(x,merge(New(v),y));
		}
		out(root);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：TangyixiaoQAQ (赞：2)

# 题意简述

要求做 $n$ 次的插队操作，得出最终的序列。

# 思路解析

## vector 做法解析（理论不可行）

第一眼看出这是一道模拟题，首要且唯一的难点就是如何实现插入操作。

STL库中，在 `vector` 中有 `insert` 操作可以实现插入，但它的时间复杂度是 $O(n)$ 的，理论上，总体时间复杂度 $O(n^2)$，总体最大消耗时间约为 $4 \times 10^{10}$，不足以通过此题（但因为其 `vector` 在国内外程序开发的常用性，经过来自五湖四海的人士各种优化，加上编译器的优化，免去了 C++ 传统 STL 的常数极大的特性， `vector` 的 `insert` 操作常数极小，卡常或不卡常依旧可以通过此题）。

### vector 做法代码实现
```cpp
#pragma G++ optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")
#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> a;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n) {
        a.clear();
        while (n--) {
            int x, y;
            cin >> x >> y;
            a.insert(a.begin() + x, y);
        }
        for (auto i : a) {
            cout << i << " ";
        }
        cout << '\n';
    }
    return 0;
}
```

![vector的提交记录](https://discourse.xinyoudui.com/uploads/default/original/3X/5/0/50f011d4696e6c6112d5b2e265b990114ea07ce8.png)

## 块状链表做法解析

注意到这题并不需要查询，那么我们想到可以使用链表数据结构。然而，对于本题，我们需要在特定位置中插入元素，虽然链表的插入时间复杂度为 $O(1)$，但是它的访问时间是 $O(n)$ 的。如何解决呢？

尺有所短，寸有所长。常规的数组用的多了，也要尝试其他的数据结构。我们可以使用[**块状链表**](https://oi-wiki.org/ds/block-list/)。

插队的人的数字插入每个节点的数组，按题意模拟，并在适当的时候进行分裂等操作即可。

因为其运用了分块的思想，总体时间复杂度为 $O(n \sqrt {n})$ 或 $O(n^{\frac{3}{2}})$。因为本题 $n \le 2 \times 10^5$，理论总体最大消耗时间约为 $9 \times 10^7$，注意下常数可以通过此题。

你可以手动模拟，但是你也可以使用 `pd_ds` 库中的 `rope` 来实现该功能（下文会阐述时间复杂度）。

### rope 做法代码实现

```cpp
#pragma G++ optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")
#include <bits/stdc++.h>
using namespace std;
#include <ext/rope>         //引入rope库
using namespace __gnu_cxx;  // rope所在的命名空间
int n;
list<vector<int>> a;  // 手动模拟块状链表
rope<int> l;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n) {
        l.clear();
        while (n--) {
            int x, y;
            cin >> x >> y;
            l.insert(x, y);
        }
        for (int i : l) {
            cout << i << " ";
        }
        cout << "\n";
    }
    return 0;
}
```

![rope的提交记录](https://discourse.xinyoudui.com/uploads/default/original/3X/5/c/5c27a633d1859180457738b4aa68109ab1eaedbb.png)

~~反而实际上更慢了~~。

## 平衡树做法解析（杀鸡焉用牛刀）

然而，很多人并不知道块状链表这一个数据结构，有没有什么其他的做法呢？

再看一眼，其实就是平衡树的模板题，你可以手动模拟，但在`pd_ds` 库中，有很多平衡树类型供你挑选，推荐还是 Splay 树（详见 [OI Wiki 上的平衡树](https://oi-wiki.org/lang/pb-ds/tree/)）。

当然了，你也可以用上文提到的 `rope` 来实现，因为它采用了可持久化平衡树实现，实际上每次是 $O(\log n)$ 的。

### 平衡树代码实现

见上文块状链表 rope 做法代码实现。

## 线段树做法解析

从前往后的操作不利用以上的做法很难实现，那么我们可不可以使用逆向思维，从后往前操作呢？

明显地，能想到后插队的人是要比先排队的人的优先级要高的，这种做法是可行的。可以先行记下空白的位置（或说是区间），那么当插入的时候，就插入第几个空白的位置就可以了。

根据上面做法的经验，我们仅需一个能进行单点插入，和随机访问比较数据结构即可。对于区间，线段树在这里起到一个前缀和的查询的作用，可以满足我们的需求。

## 树状数组&二分做法解析

能用到线段树的题，很多也都可以用树状数组。在这里，树状数组做法和线段树做法是类似的，但是，注意到可以优化查询的过程，所以可以用二分的思想来查询第几个空白的位置。

# 后记

关于是否能使用这些简单好用的 STL 容器或函数，详见[《关于NOI系列活动中编程语言使用限制的补充说明》](https://www.noi.cn/xw/2021-09-01/735729.shtml)。

由于机房的网上不了 [POJ](http://poj.org/)，对于原题数据的检测无法进行（待补）。

其实这几种思想是相似的，如果有其他更好的想法或做法可以在评论区指出。

---

## 作者：qcf2010 (赞：1)

# 前置知识  

- [树状数组](https://oi-wiki.org/ds/fenwick/)
- [二分](https://oi-wiki.org/basic/binary/)

# 思路

如果按照正常顺序从前向后模拟，问题会变得很复杂。但是反过来，我们从最后一个人开始从后向前模拟，整个问题就会变得非常简单。

为什么呢？考虑一个简单的例子：首先来了一个人，站在第 $1$ 个人后面。接着又来了若干个人，都~~没有素质~~插在第 $1$ 个人的后面。最后一个人来了，他也~~没有素质~~插在了第 $1$ 个人后面。诶，此时，最后一个人就是第 $1$ 个人后面的第一个人。

发现了什么？最后一个插队的人是离他所排的人最近的，而第一个插队的人是离他所排的人最远的。

所以，从后往前模拟，就可以顺利解决此题。扫描每一个人，若他排在第 $x$ 个人后面，那么查找队伍中哪一个位置前面有 $x$ 个空位，然后把这个人放在这里。

如何快速获取从队头到某一处之间有多少个空位？使用树状数组，维护每一个位置上有没有人（有人为 $0$，没人为 $1$）。利用树状数组能快速求出区间和的性质，即可求出从队头到某一处之间有多少个空位。那如何查找到这个位置？很自然地可以想到二分查找。

至此，问题解决。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[200010],v[200010];
int ans[200010];

int c[200010];

void Add(int x,int y){
	for(;x<=n;x+=x&-x) c[x]+=y;
}

int Query(int x){
	int ans=0;
	for(;x;x-=x&-x) ans+=c[x];
	return ans;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	while(cin>>n){
		for(int i=1;i<=n;++i) c[i]=0;
		for(int i=1;i<=n;++i) Add(i,1);
		for(int i=1;i<=n;++i) cin>>a[i]>>v[i];
		for(int i=n;i>=1;--i){
			int l=1,r=n;
			while(l<r){
				int mid=(l+r)>>1;
				if(Query(mid)>=a[i]+1) r=mid;
				else l=mid+1;
			}
			ans[l]=v[i];
			Add(l,-1);
		}
		for(int i=1;i<=n;++i) cout<<ans[i]<<" ";
		cout<<"\n";
	}

	return 0;
}

```

---

## 作者：lzdll (赞：1)

依次插入每个人非常困难，所以我们正难则反，从最后一个人开始考虑，这样每个人的位置就可以固定下来了。所以我们再插第 $i$ 个人时就不用管 $i$ 之后的人了，也就是插入的**空位置** $u$ 要满足 $u$ **之前的空位置**有 $p_i$ 个，这样就不会受后边的人的干扰，还保证了**当 $i$ 插队的时候**是插在了第 $p_i$ 个人之后。

这样说可能比较抽象，我们看这样一组样例

```
3
0 10
1 20
1 30
```

我们从后往前模拟，$30$ 在插队时，插在了**当时的第一**的后面，所以他是第二。$20$ 在插队时，插在了**当时的第一**的后面，找到前面空位置为 $1$ 的位置，所以最终就是第三。这是因为在 $20$ 插队时还没有 $30$，且前面需要有 $1$ 个人，所以放在了第三个。

所以，我们只需要二分这个位置即可，每次查询后需要单点修改，二分时需要用到区间查询，使用树状数组即可，复杂度 $\Theta(n\log^2n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define R(x) x=read()
using namespace std;
inline int read() {
	int x=0,y=1;
	char e=getchar();
	while(e<'0'||e>'9') {
		if(e=='-')y=-1;
		e=getchar();
	}
	while(e>='0'&&e<='9') {
		x=(x<<1)+(x<<3)+(e^'0');
		e=getchar();
	}
	return x*y;
}
#define lb(i) (i&(-i))
const int N=200005;
int n,p[N],v[N],t[N];
int ans[N];
void add(int x,int k){
	while(x<=n){
		t[x]+=k;
		x+=lb(x);
	}
}
int ask(int x){
	int sum=0;
	while(x){
		sum+=t[x];
		x-=lb(x);
	}
	return sum;
}
signed main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	while(cin>>n){
		memset(t,0,sizeof t);
		for(int i=1;i<=n;++i){
			R(p[i]),R(v[i]);
		}
		for(int i=n;i>=1;--i){
			int l=1,r=n,mid,u=1;
			while(l<=r){
				mid=(l+r)>>1;
				if(mid-ask(mid)>=p[i]+1){
					r=mid-1;
					u=mid;
				}else{
					l=mid+1;
				}
			}
			add(u,1);
			ans[u]=v[i];
		}
		for(int i=1;i<=n;++i){
			cout<<ans[i]<<" ";
		}
		cout<<"\n";
		
	}
	return 0;
}

```

---

## 作者：thh_loser (赞：1)

# P10688 Buy Tickets 题解

[题目链接](https://www.luogu.com.cn/problem/P10688)

## 题意

有 $n$ 个人想要插队，求插完队的顺序。

## 思路

其实这道题是 [P4309 [TJOI2013] 最长上升子序列](https://www.luogu.com.cn/problem/P4309) 的第一步，我们发现`std::vector` 可以轻松实现这个功能，然而它的复杂度是假的。

手写平衡树复杂度是正确的，但不好（懒得）写，于是我们使用了伟大的 `__gnu_cxx::rope`（一棵可持久化平衡树），它同样能够实现该功能。

如果不会可以看 [OIwiki](https://oi-wiki.org/ds/block-list/)。

## code

```c++
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace __gnu_cxx;//rope 所在的命名空间
int t(1),n;
rope<int>rop;
signed main(){
	while(-1!=scanf("%d",&n)){
		rop.clear();
		for(int i=1,ui,vi;i<=n;++i){
			scanf("%d%d",&ui,&vi);
			rop.insert(ui,vi);//类似于vector的insert
		}
		for(int i : rop) std::cout << i << " ";
		std::cout<<"\n";
	}
	return 0;
}
```

---

## 作者：myxRUC (赞：0)

## 转化利用树状数组！！！

由于是排队问题，所以后进入队列的人拥有站在哪里的决定权，因此我们倒序处理进入队列的人。

因此每个人进入队列的时候，如果他的理想位置是 $x$ 的话,他显然没有任意挑选位置的自主权，必须在剩下的位置里面挑选一个最满意的。

由此可知我们整道题所要做的就是维护一个数组，来存储第 $k$ 个点以前剩余的座位个数，比如 $find(5)=4$，就说明前五个座位里面还剩下四个，那么如果此时进入队列的人想坐在第四个位置，就要看 $find(4)$ 是不是等于 $4$，如果是，就要坐在第四个位置；否则，说明第五个位置没人坐，就坐在第五个位置。**这也就是二分的思想**。

```cpp
int l = 1, r = n;
while (l < r) {
	int mid = (l + r) / 2;
	int t = find(mid);
	if (t < p[i]) {
		l = mid + 1;
	}
	else {
		r = mid;
	}
}
```
显然 $find(i)$ 有前缀和的思想，而又要进行单点修改，所以就要借助树状数组。

```cpp
inline int lowbit(int x) {
	return x & -x;
}

inline void add(int v, int x) {//单点修改
	for (int i = x; i <= n; i += lowbit(i)) {
		a[i] += v;
	}
}

inline int find(int x) {//求前缀和
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		ans += a[i];
	}
	return ans;
}
```
因此在第 $i$ 座位被占用以后，使用 $add(-1,i)$ 这个操作就行了，这样就很高效的完成树状数组的维护。

## 完整代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
const int N = 200005;

int a[N], num[N], c[N], p[N];
int cnt, n;

inline int lowbit(int x) {
	return x & -x;
}

inline void add(int v, int x) {
	for (int i = x; i <= n; i += lowbit(i)) {
		a[i] += v;
	}
}

inline int find(int x) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		ans += a[i];
	}
	return ans;
}

int main(void) {
	while (cin >> n) {

		memset(a, 0, sizeof a);
		memset(c, 0, sizeof c);

		for (int i = 1; i <= n; i++) {
			cin >> p[i] >> num[i];
			p[i]++;
			add(1, i);
		}

		for (int i = n; i >= 1; i--) {
			int l = 1, r = n;
			while (l < r) {
				int mid = (l + r) / 2;
				int t = find(mid);
				if (t < p[i]) {
					l = mid + 1;
				}
				else {
					r = mid;
				}
			}
			c[r] = num[i];
			add(-1, r);
		}

		for (int i = 1; i <= n; i++) {
			cout << c[i] << ' ';
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Toorean (赞：0)

建议升绿。

$n$ 个人有编号，给出插入是顺序，求最终序列。

可以直接用平衡树暴力做，但杀鸡焉用牛刀，这里介绍二分方法。

考虑将插入序列翻转，那么翻转后的第一行可以确定其位置。那么第二行的插入，如果插入的位置在第一次插入之前，那么说明最后一次插入不会影响到这一次插入。我们直接将其插入对应位置。反之，如若在后，那么要将其向后移动一个位置。

如此反复的，对于当前插入于 $p$ 之后的操作，我们首先计算 $1$ 到 $p$ 中已经确定答案的数量 $c$，在 $p+1$ 开始的第 $c$ 个空位插入当前数即可。

可以用树状数组维护这个操作。寻找空位时用二分。总复杂度 $\mathcal O(n\log^2n)$。

```cpp
for (int i = 1; i <= n; i ++) scanf ("%d%d", pos + i, val + i);
for (int i = n; i >= 1; i --) {
    int left = t.query (pos[i]);
    int p = pos[i] + 1;
    int l = p, r = n;
    int ls = t.query (pos[i]);
    while (l <= r) {
        int mid = l + r >> 1;
        if (t.query (mid) - ls + left <= mid - pos[i] - 1) p = mid, r = mid - 1;
        else                                               l = mid + 1; 
    }
    t.add (p, 1);
    ans[p] = val[i];
}
for (int i = 1; i <= n; i ++) printf ("%d ", ans[i]);
puts ("");
```

---

