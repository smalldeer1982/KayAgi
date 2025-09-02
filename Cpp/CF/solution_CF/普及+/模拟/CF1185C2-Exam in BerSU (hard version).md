# Exam in BerSU (hard version)

## 题目描述

The only difference between easy and hard versions is constraints.

If you write a solution in Python, then prefer to send it in PyPy to speed up execution time.

A session has begun at Beland State University. Many students are taking exams.

Polygraph Poligrafovich is going to examine a group of $ n $ students. Students will take the exam one-by-one in order from $ 1 $ -th to $ n $ -th. Rules of the exam are following:

- The $ i $ -th student randomly chooses a ticket.
- if this ticket is too hard to the student, he doesn't answer and goes home immediately (this process is so fast that it's considered no time elapses). This student fails the exam.
- if the student finds the ticket easy, he spends exactly $ t_i $ minutes to pass the exam. After it, he immediately gets a mark and goes home.

Students take the exam in the fixed order, one-by-one, without any interruption. At any moment of time, Polygraph Poligrafovich takes the answer from one student.

The duration of the whole exam for all students is $ M $ minutes ( $ \max t_i \le M $ ), so students at the end of the list have a greater possibility to run out of time to pass the exam.

For each student $ i $ , you should count the minimum possible number of students who need to fail the exam so the $ i $ -th student has enough time to pass the exam.

For each student $ i $ , find the answer independently. That is, if when finding the answer for the student $ i_1 $ some student $ j $ should leave, then while finding the answer for $ i_2 $ ( $ i_2>i_1 $ ) the student $ j $ student does not have to go home.

## 说明/提示

The explanation for the example 1.

Please note that the sum of the first five exam times does not exceed $ M=15 $ (the sum is $ 1+2+3+4+5=15 $ ). Thus, the first five students can pass the exam even if all the students before them also pass the exam. In other words, the first five numbers in the answer are $ 0 $ .

In order for the $ 6 $ -th student to pass the exam, it is necessary that at least $ 2 $ students must fail it before (for example, the $ 3 $ -rd and $ 4 $ -th, then the $ 6 $ -th will finish its exam in $ 1+2+5+6=14 $ minutes, which does not exceed $ M $ ).

In order for the $ 7 $ -th student to pass the exam, it is necessary that at least $ 3 $ students must fail it before (for example, the $ 2 $ -nd, $ 5 $ -th and $ 6 $ -th, then the $ 7 $ -th will finish its exam in $ 1+3+4+7=15 $ minutes, which does not exceed $ M $ ).

## 样例 #1

### 输入

```
7 15
1 2 3 4 5 6 7
```

### 输出

```
0 0 0 0 0 2 3 ```

## 样例 #2

### 输入

```
5 100
80 40 40 40 60
```

### 输出

```
0 1 1 2 3 ```

# 题解

## 作者：songhn (赞：10)

### 题解：
首先我们可以考虑easy版本里的暴力做法 由贪心思想可得 我们考虑到$i$要删去前$i-1$里面最少的数使得前面的和小于$m-a[i]$那么我们肯定是首先删除最大值 然后次大值 然后次次大值....直到小于 但是这样我们每次都要扫描一遍前面的序列 这样复杂度在hard的情况下就爆炸了 我们观察一下数据范围 会发现$n$,$M$都很大但是$t$却异常小 这就可以想到在$t$上做文章

既然我们是要知道一个大小关系然后不断删去最大的 那么我们可以搞一个桶排 这得益于值域很小 每次我们从100到1挨个枚举删除即可 这样时间复杂度是$O(t\cdot n)$ 

### AC代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=200050;
int n,m,a[maxn],mp[maxn],sum[maxn];
inline int read()
{
	int x=0,t=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*t;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++)
	{
		if(sum[i]<=m) printf("0 ");
		else
		{
			int temp=sum[i-1]-m+a[i];
			int res=0;
			for(int j=100;j>=1;j--)
			{
				int t=min(mp[j],(temp+j-1)/j);
				temp-=t*j;
				res+=t;
				if(temp<=0) break;
			}
			printf("%d ",res);
		}
		mp[a[i]]++;
	}
	return 0;
}
```

---

## 作者：lzyqwq (赞：5)

**[题目传送门](https://www.luogu.com.cn/problem/CF1185C2)**

> - 给出一个数组 $\{a_1\sim a_n\}$ 和一个常数 $m$。记 $s_i = \sum\limits_{j=1}^i a_j$。对于 $i\in[1,n]$，询问至少要在区间 $[1,i)$ 中将几个数修改成 $0$，才能使 $s_i\le m$。询问之间相互独立，即**不会真的修改**。
>
> - $n \le 2\times 10^5$，$a_i\le m\le 2\times 10^7$。

对于 $s_i\le m$ 的询问，输出 $0$ 即可。对于 $s_i>m$ 的询问，问题转化成在区间中选取最少的数，使得他们的和大于等于 $s_i-m$。我们肯定贪心地将最大的数变成 $0$，因此考虑找到选取的最小数，然后大于它的都必选，等于它的需要选到刚好使得和大于等于 $s_i-m$。用权值线段树二分支持这个操作，如果右儿子的和够了就在右儿子里面选，否则将右儿子全选，去左儿子选剩下的数。

询问结束后，将 $a_i$ 插入权值线段树。值域甚大，须动态开点。

时间、空间复杂度均为 $\mathcal{O}(n\log m)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5, L = 1, R = 2e7; int n, m, a[N], s[N];
struct SegmentTree {
    int rt, sum[N * 30], tot[N * 30], cnt, ls[N * 30], rs[N * 30];
    void init() {
        memset(sum, 0, sizeof sum), memset(tot, 0, sizeof tot);
        memset(ls, cnt = rt = 0, sizeof ls), memset(rs, 0, sizeof rs);
    }
    SegmentTree() { init(); }
    void modify(int &x, int l, int r, int val) {
        if (!x) x = ++cnt;
        ++tot[x], sum[x] += val; if (l == r) return;
        int mid = (l + r) >> 1;
        if (val <= mid) modify(ls[x], l, mid, val);
        else modify(rs[x], mid + 1, r, val);
    }
    int query(int x, int l, int r, int k) {
        if (l == r) return (k + l - 1) / l;
        int mid = (l + r) >> 1, val = sum[rs[x]];
        if (k <= val) return query(rs[x], mid + 1, r, k);
        return query(ls[x], l, mid, k - val) + tot[rs[x]];
    }
} sgt;
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48;
    x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
signed main() {
    read(n), read(m); 
    for (int i = 1; i <= n; ++i) read(a[i]), s[i] = s[i - 1] + a[i];
    for (int i = 1; i <= n; ++i) {
        if (s[i] <= m) print(0, ' ');
        else print(sgt.query(sgt.rt, L, R, s[i] - m), ' ');
        sgt.modify(sgt.rt, L, R, a[i]);
    }
    return 0;
}
```


---

## 作者：_edge_ (赞：1)

双倍经验，这里只讲 hard 怎么过。

~~这题复杂度过于神奇，如果有 dalao 可以分析出来是对的，欢迎来私信和我交流。~~

简单一点，可以考虑每次都删去最大值，这样就可以保证留下的时间较为多。

然后考虑如何去优化这个过程，我们会发现，删去最大值的过程，可以把它看成扔到另外一个堆，或者 set 里面，然后每次加进去一个数，把那个数和删掉的数里面换一换。

同时如果不够了，那么我们再把当前选手的 set 里面的最大值删掉，如果够的话，把删去 set 里面的最小值看看能不能换过来。

让我们来分析一下这个复杂度，发现其实瓶颈出在两个 set 交换的情况，事实上，这种交换次数不会执行很多次，因为大部分时候他们都是有序的。

交换次数最多最多出现的地方就是新加进去一个元素，这样数量级也是 $n$ 的级别。

因此，复杂度是 $O(n \log n)$。

代码写的稍微比较复杂。

```cpp
#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
const int INF=2e5+5;
int n,m,a[INF],sum;
multiset<int> s,s1;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	cout<<"0 ";sum+=a[1];
	for (int i=2;i<=n;i++) {
		s.insert(a[i-1]);sum+=a[i];
		while (s.size() && s1.size()) {
			int kk=*(s1.begin()),kk1=*(--s.end());
			if (kk1>kk) swap(kk,kk1);
			else break;
			sum-=kk;sum+=kk1;
			s1.erase(s1.find(kk1));
			s.erase(s.find(kk));
			s1.insert(kk);s.insert(kk1);
		}
		while (sum>m && s.size()) {
			int kk=*(--s.end());sum-=kk;
			s1.insert(kk);s.erase(s.find(kk));
		}
		while (sum<m && s1.size()) {
			int kk=*(s1.begin());
			if (sum+kk>m) break;
			sum+=kk;
			s1.erase(s1.find(kk));
			s.insert(kk);
		}
		cout<<s1.size()<<" ";
	}
	return 0;
}
```


---

## 作者：Cesare (赞：1)

## $Solution$

可撤销的贪心。

首先有一种很假的做法，维护一个堆，每次加入一个元素，如果当前值 $\leq m$ 就直接输出当前所用次数，否则用堆每次把最大的弹出，直到满足为止。

但这样是错的，因为当前这次加入的 $t_i$ 可能可以影响后面的答案。

那么考虑记录这个影响，每次比较这个 $t_i$ 与先前堆中弹出元素的关系，考虑把这个弹掉优势是什么，如果这个弹掉把先前的加回去可以满足 $s \leq m$ 就加回去。

## $Code:$

```cpp
#include <bits/stdc++.h>
#define For(i, j, k) for(int i = (j), ED = (k); i <= ED; ++i)
using namespace std;
typedef long long ll;
const ll N = 200011;
const ll INF = 5e16;

#define dd ch = getchar()
inline ll read() {
	ll x = 0; int f = 0; char dd;
	for (; !isdigit(ch); dd) f ^= (ch == '-');
	for (; isdigit(ch); dd)  x = x * 10 + (ch ^ 48);
	return f? -x: x;
}
#undef dd

inline void write ( ll x ) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10); 
	putchar(x % 10 | 48);
}

inline void wrn ( ll x ) { write(x), putchar(' '); }

inline void wln ( ll x ) { write(x), putchar('\n'); }

namespace Cesare {

	ll res = 0;
	ll n, m, s, t[N], Need[N];

	priority_queue <ll> Q;

	int main() {
		n = read(), m = read();
		For ( i, 1, n ) t[i] = read();
		For ( i, 1, n ) {
			s += t[i];
			if (s <= m) {
				wrn(res); 
				Q.push(t[i]);
				continue;
			}
			ll cc = 0, Mn = INF;
			while (!Q.empty()) {
				ll now = Q.top(); Q.pop();
				s -= now, ++res;
				Mn = min(Mn, now);
				Need[++cc] = now;
				if (s <= m) break;
			}
			wrn(res);
			if (t[i] > Mn) {
				s = s + Mn - t[i], Q.push(Mn);
				Rep ( j, cc - 1, 1 ) if (s + Need[j] <= m) 
					s += Need[j], --res, Q.push(Need[j]);
			} else Q.push(t[i]);
		} return 0;
	}

}

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	return Cesare :: main();
}

/*

*/


```


---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1185C2) & [CF 传送门](//codeforces.com/problemset/problem/1185/C2)
# 思路
第一反应是准备一个大根堆 $q$ 和一个记录当前堆里数总和的变量 $now$，然后在输入的同时先把总和 $now$ 加上 $a_i$，然后把 $q$ 里的数弹到 $now\le m$ 为止，最后再把 $a_i$ 插到 $q$ 里去。**这里注意**，要先弹数再插 $a_i$！！！因为规定 $a_i$ 自身不能弹掉！代码如下：
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, m, x, now, tot;
priority_queue <int> q;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	while (n --) {
		cin >> x;
		now += x;
		while (now > m && ! q.empty ())
			now -= q.top (), q.pop (), ++ tot; //tot 用于记录目前删掉的数个数
		q.push (x);
		cout << tot << ' ';
	}
	return 0;
}
```
然后，你会发现 WA 在了第 $13$ 个点。这里蒟蒻提供一组自制 Hack 数据：
```
3 10
5 6 5
```
我们来分析一下这个方法的漏洞。这个方法的错误原因就在于题目规定了 $a_i$ 自身不能弹掉，这就导致了先前弹掉的数在后面不一定也要弹，即可能出现之前弹掉的数甚至比 $a_i$ 自身还小的情况。这对处理 $a_i$ 自身没任何问题，但是对后续就有问题了。不明白的读者可以手动模拟上面的 Hack 数据。

于是，我们要弥补这个漏洞的突破口就在于我们只需要把操作回退到加 $x$ 之前就行，别的数弹不弹掉已经无所谓了。至于回滚操作，我们可以准备一个小根堆 $poper$ 用于存储已经被弹掉了的数。这时候，我们就不用急着将 $a_i$ 插进 $q$ 里，因为 $a_i$ 插不插对输出答案是没有影响的。

当 $poper$ 为空或 $poper$ 的堆顶（也就是弹出的数中最小的那个数）比 $a_i$ 还大时，这是我们不用回滚，我们也只能乖乖把 $a_i$ 插进 $q$ 里。否则，我们要在输出完毕后回滚一次操作，即我们把先前加上 $a_i$ 的 $now$ 再减去 $a_i$ 还，这时我们的 $now$ 肯定远远小于 $m$ 了，我们要把 $now$ 加到不能再加（再加就要 $now>m$ 了）为止。我们要尽量把小的换回去，这样换回去的个数才能尽量多，这也就是我们选择使用小根堆的原因。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, m, x, now, tot;
priority_queue <int> q;
priority_queue <int, vector <int>, greater <int>> poper;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	while (n --) {
		cin >> x;
		now += x;
		while (! q.empty () && now > m)
			now -= q.top (), poper.push (q.top ()), q.pop (), ++ tot;
		cout << tot << ' ';
		if (poper.empty () || poper.top () >= x) { //不用换
			q.push (x);
			continue;
		}
		now -= x;
		++ tot; //x 也是个数啊，所以要把删掉的数 +1
		while (! poper.empty () && now + poper.top () <= m)
			now += poper.top (), q.push (poper.top ()), poper.pop (), -- tot;
		poper.push (x);
	}
	return 0;
}
```

---

## 作者：linakrbcs (赞：0)

这里是一篇**权值树状数组 + 倍增**的题解！

## 题意简述

给出 $n$ 个数 $a _ 1 \sim a _ n$ 和常数 $M$。

对每个 $i = 1 , 2 , \cdots , n$，要求在 $a _ 1 \sim a _ i$ 中选数，使得选出数的总和不超过 $M$，且按照以下优先级选数：

1. 先选择 $a _ i$；
2. 若 $a _ i < M$，则在选择 $a _ i$ 后，在 $a _ 1 \sim a _ {i - 1}$ 中按数值从小到大的顺序选数。

求第 $i$ 次选数时在 $a _ 1 \sim a _ i$ 中未被选出数的个数。

$1 \le n \le 2 \times 10 ^ 5$，$1 \le a _ i \le M \le 2 \times 10 ^ 7$。

## 算法分析

从 $a _ 1$ 到 $a _ n$ 依次考虑每个 $a _ i$。由于选数时优先选择 $a _ i$，因此只需考虑在 $a _ 1 \sim a _ {i - 1}$ 中选出数之和不超过 $M - a _ i$ 时选数的个数。

这样，本题可以转化为以下两种操作：

- 修改：在集合中插入一个数；
- 查询：求集合中数从小到大前缀和不超过某个值的最大位置。

由于 $a _ i$ 并不在查询集合中，因此先查询，再修改。

查询操作的形式启发我们用**权值树状数组**维护。

注意到 $a _ i$ 范围较大，因此首先进行离散化。但这里要求每个元素离散化后的值不同（原因详见下文）。

然后，维护树状数组 $C$ 统计集合中小于等于某个值的**元素个数**，树状数组 $S$ 统计集合中小于等于某个值的**元素和**。

考虑到树状数组维护了**倍增**的信息（即 $C _ x$ 对应原数组区间为 $\left[ x - \operatorname {lowbit} \left( x \right) + 1 , x \right]$），我们有以下算法：

- 维护区间右端点 $p$，选择的元素个数 $rc$，选择的元素之和 $rs$。
- 按顺序枚举 $k = 2 ^ {\left\lfloor \log _ 2 n \right\rfloor} , 2 ^ {\left\lfloor \log _ 2 n \right\rfloor - 1} , \cdots , 2 ^ 1 , 2 ^ 0$，考虑是否选择权值树状数组中下标为 $\left[ p + 1 , p + k \right]$ 的区间。
  - 如果 $p + k \le n$（即选择 $\left[ p + 1 , p + k \right]$ **不会越界**），且 $rs + S _ {p + k} \le M - a _ i$（即选择 $\left[ p + 1 , p + k \right]$ 后**元素和不超过** $M - a _ i$），则令 $rc$ 加上 $C _ {p + k}$，$rs$ 加上 $S _ {p + k}$（表示选择了 $\left[ p + 1 , p + k \right]$），再令 $p$ 加上 $k$（为考虑下一区间做准备）。
  - 否则，不将 $\left[ p + 1 , p + k \right]$ 作为完整的区间选择。
- 上述过程结束后，$rc$ 的值即为 $a _ 1 \sim a _ {i - 1}$ 中选数的个数。故答案（$a _ 1 \sim a _ i$ 未被选出数的个数）为 $i - rc - 1$。

注意，若权值树状数组中存在两个值对应下标相同，则以上倍增过程无法区分这两个数。因此，若 $a _ i$ 中存在元素相同，离散化时，可以添加第二关键字加以区分（代码中直接使用了排序后得到的随机顺序）。

最后进行修改。设 $a _ i$ 离散化后的值为 $val \left( i \right)$，则对树状数组 $C$ 进行在 $val \left( i \right)$ 位置的加 $1$ 操作，对树状数组 $S$ 进行在 $val \left( i \right)$ 位置的加 $a _ i$ 操作（原始数值）即可。

时间复杂度 $O \left( n \log n \right)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long llint;

const int N=200005, L=20;

int n, a[N], v[N];

struct node{
    int w, i;
    
    bool operator <(const node x) const{
        return w<x.w;
    }
}w[N];

class bit{
    int c[N];
    llint s[N];
    
    public:

    void upd(int p, int w){
        for(int i=p; i<=n; i+=i&-i) ++c[i], s[i]+=w;
    }
    
    int qry(int w){
        int p=0, rc=0;
        llint rs=0;
        for(int i=L; ~i; --i){
            if((p|1<<i)<=n && rs+s[p|1<<i]<=w) p|=1<<i, rc+=c[p], rs+=s[p];
        }
        return rc;
    }
}s;

int main(){
    int m;
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; ++i){
        scanf("%d", a+i);
        w[i]={a[i], i};
    }
    
    sort(w+1, w+n+1);
    for(int i=1; i<=n; ++i) v[w[i].i]=i;
    
    for(int i=1; i<=n; ++i){
        printf("%d ", i-s.qry(m-a[i])-1);
        s.upd(v[i], a[i]);
    }
}

```


---

