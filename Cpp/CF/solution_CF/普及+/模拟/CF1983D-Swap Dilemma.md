# Swap Dilemma

## 题目描述

Given two arrays of distinct positive integers $ a $ and $ b $ of length $ n $ , we would like to make both the arrays the same. Two arrays $ x $ and $ y $ of length $ k $ are said to be the same when for all $ 1 \le i \le k $ , $ x_i = y_i $ .

Now in one move, you can choose some index $ l $ and $ r $ in $ a $ ( $ l \le r $ ) and swap $ a_l $ and $ a_r $ , then choose some $ p $ and $ q $ ( $ p \le q $ ) in $ b $ such that $ r-l=q-p $ and swap $ b_p $ and $ b_q $ .

Is it possible to make both arrays the same?

## 说明/提示

In the first testcase, you don't need to perform any operations since the arrays are same.

In the second testcase, it can be proven there exists no way to make the arrays same.

In the third testcase, one of the ways to make the arrays same is to first choose $ l=1 $ , $ r=3 $ , $ p=1 $ , $ q=3 $ then choose $ l=1 $ , $ r=2 $ , $ p=3 $ , $ q=4 $ .

## 样例 #1

### 输入

```
6
4
1 2 3 4
1 2 3 4
5
1 3 4 2 5
7 1 2 5 4
4
1 2 3 4
4 3 2 1
3
1 2 3
1 3 2
5
1 5 7 1000 4
4 1 7 5 1000
3
1 4 2
1 3 2```

### 输出

```
YES
NO
YES
NO
NO
NO```

# 题解

## 作者：TTpandaS (赞：14)

操作可以拆分为每次交换 $r=l+1,q=p+1$。那么每次交换将分别改变两个数组的一组逆序对或者都不变。也就是说两个数组的逆序对数量奇偶性不会变。所以当两个数组不同或者逆序对奇偶性不同时输出 `NO`。

考虑奇偶性相同时为何一定是 `YES`。每次交换 $a_1,a_2$，而对于数组 $b$ 就相当于是在进行冒泡排序，所以一定能相等。

---

## 作者：Diaоsi (赞：7)

[Swap Dilemma](https://codeforces.com/contest/1983/problem/D)

考场上猜了个结论把它过了。

首先两个数组排序后得相等，否则一定无解，特判掉这种情况后可以将两个数组是为长度相同的排列。

有一个观察是，交换两个任意位置的数可以看成多次相邻交换。在一个排列中，交换相邻两项后排列的逆序对数会变化 $\pm1$ 个。

当两个排列的逆序对奇偶性相同时，一定可以通过适当地操作使得两个排列相等，下面给出一个简易的证明：

令 $a_i=i$，不难发现可以通过若干次操作使得原 $a$ 序列变成这样的顺序排列。在排序的过程中对序列 $b$ 实施同样的操作，注意到操作之后 $b$ 的逆序对一定是偶数。

此时令 $l=1,r=2$，对序列 $b$ 做冒泡排序。由于逆序对数是偶数，所以 $b$ 排序完后 $(l,r)$ 会交换偶数次，等于没有交换，于是 $a=b$。$\ \Box$

有了这个结论，判断的条件就很显然了，即 $a$ 和 $b$ 的逆序对数奇偶性相同。

[提交记录](https://codeforces.com/contest/1983/submission/269287720)

你以为这就结束了？

其实这道题还有更深刻的观察，就是在置换的角度下，逆序对数与环数的奇偶性是同步变化的。换句话说，逆序对的奇偶性 $=$ 排列长度 $+$ 环数的奇偶性。

具体地说，对于一个排列，将 $i$ 与 $p_i$ 连边，整个图就会构成一个**简单环森林**。考虑对排列进行邻项交换，根据之前的结论我们知道逆序对个数一定变化 $1$，接下来讨论环数的变化。

- 若这相邻的两项在同一个环中，则邻项交换等价于分裂这个环，环数加一。
- 若这相邻的两个项不在同一个环中，则邻项交换等价于合并两个环，环数减一。

所以对于任何邻项交换操作，环数的奇偶性都会改变。$\ \Box$

由于本题中排列长度一定相同，所以只需要比较环数的奇偶性。时间复杂度 $\mathcal{O}(n\log n)$，瓶颈在排序离散化。

[提交记录](https://codeforces.com/contest/1983/submission/269509074)

---

## 作者：Xy_top (赞：5)

赛时写了一个爆标的做法，巨久，导致没上分。

思路是模拟：$i$ 从 $1$ 扫到 $n$，使 $a
_i=b_i$。

从 $1$ 开始，假设 $a_1=a$，$b_1=b$。$a=b$ 不用处理；$a\not=b$ 时假设 $b$ 中下一个数字 $a$ 出现的位置为 $b_p$，$a$ 中下一个数字 $b$ 出现的位置为 $a_q$（如果找不到输出 ``NO``）。

当 $p\not= n$ 时，可以在 $b$ 中交换 $b_1$ 和 $b_p$，$a$ 中交换 $a_2$ 和 $a_{p+1}$，这样 $a_1$ 就等于 $b_1$ 了。$q\not= n$ 时也同理。当 $p$ 和 $q$ 都等于 $n$ 时先在 $a$ $b$ 中分别交换 $a_2$ $a_n$，$b_2$ $b_n$，再交换 $b_1$ $b_2$，$a_2$ $a_3$ 即可。

为了存储每个数字出现的位置，需要离散化再开 ``vector``，交换位置后还要再刷新位置，还要再开懒标记队列，写到最后都崩溃了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, cnt;
int a[100005], b[100005];
vector <int> v1[200005], v2[200005];//存储数字出现位置
map <int, int> m;//离散化
queue <pair <int, int> > st1[200005], st2[200005];//懒标记队列
void reloada (int x) {//更新懒标记
	while (!st1[x].empty () && !v1[x].empty () && v1[x].back () == st1[x].front ().first) {
		v1[x].back () = st1[x].front ().second;
		st1[x].pop ();
	}
}
void reloadb (int x) {//更新懒标记
	while (!st2[x].empty () && !v2[x].empty () && v2[x].back () == st2[x].front ().first) {
		v2[x].back () = st2[x].front ().second;
		st2[x].pop ();
	}
}
void swapa (int x, int y) {
	st1[a[x] ].push (make_pair (x, y) );
	st1[a[y] ].push (make_pair (y, x) );
	swap (a[x], a[y]);
}
void swapb (int x, int y) {
	st2[b[x] ].push (make_pair (x, y) );
	st2[b[y] ].push (make_pair (y, x) );
	swap (b[x], b[y]);
}
void solve () {
	cnt = 0;
	m.clear ();
	cin >> n;
	For (i, 1, 2 * n) v1[i].clear ();
	For (i, 1, 2 * n) v2[i].clear ();
	For (i, 1, 2 * n) {
		while (!st1[i].empty () ) st1[i].pop ();
	}
	For (i, 1, 2 * n) {
		while (!st2[i].empty () ) st2[i].pop ();
	}
	For (i, 1, n) {
		cin >> a[i];
		if (!m[a[i] ]) m[a[i] ] = ++ cnt;
		a[i] = m[a[i] ];
	}
	For (i, 1, n) {
		cin >> b[i];
		if (!m[b[i] ]) m[b[i] ] = ++ cnt;
		b[i] = m[b[i] ];
	}
	foR (i, n, 1) {
		v1[a[i] ].push_back (i);
		v2[b[i] ].push_back (i);
	}
	if (n == 1) {
		if (a[1] == b[1]) cout << "YES";
		else cout << "NO";
		return;
	}
	For (i, 1, n - 2) {
		if (a[i] == b[i]) continue;
		reloadb (a[i]);
		reloada (b[i]);
		while (!v2[a[i] ].empty () && v2[a[i] ].back () < i) v2[a[i] ].pop_back ();
		while (!v1[b[i] ].empty () && v1[b[i] ].back () < i) v1[b[i] ].pop_back ();
		if (v2[a[i] ].empty () || v1[b[i] ].empty () ) {
			cout << "NO";
			return;
		}
		if (v1[b[i] ].back () != n) {
			int l = v1[b[i] ].back ();
			swapa (i, l);
			swapb (i + 1, l + 1);
		} else if (v2[a[i] ].back () != n) {
			int l = v2[a[i] ].back ();
			swapb (i, l);
			swapa (i + 1, l + 1);
		} else {
			swapa (i + 1, n);
			swapb (i + 1, n);
			swapb (i, i + 1);
			swapa (i + 1, i + 2);
		}
	}
	if (a[n - 1] != b[n - 1] || a[n] != b[n]) cout << "NO";
	else cout << "YES";
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：gan1234 (赞：3)

### 分析

考虑如果 $a$ 和 $b$ 能通过若干次这样的操作后相同，那么同样可以若干次操作后 $a,b$ 序列变得有序。

考虑到交换不相邻的两个数的操作，可以由若干次交换相邻的数的操作完成。我们不妨操作时只交换相邻的数，这样要求 $r-l=q-p$ 的限制就被我们弄没了。发现如果排序 $a$ 和 $b$ 所需交换数相同，那么我们就能将对 $a$ 的操作与对 $b$ 的操作两两匹配构造方案，而且由于我们能反复交换两个数，因此只要交换次数的奇偶性相同即可。

这样我们就把问题转化为了排序一个序列需要交换相邻的数多少次，这个东西可以随便做，随便找一种排序方式算一下就行。我用的是用树状数组维护插入排序的过程，计算交换数。

这里需要特判一个东西，我们发现如果序列中存在两个数相同，那么交换这两个相同的数可以使奇偶性改变，此时一定有解。

### 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
int n;
int a[MAXN],b[MAXN],cnt[MAXN];
int A[MAXN],pos[MAXN];
int bit[MAXN];
void add(int x,int z){while(x<=n){bit[x]+=z;x+=x&-x;}}
int sum(int x){int res=0;while(x){res+=bit[x];x-=x&-x;}return res;}
int get(){
	int res=0;
	for(int i=1;n>=i;i++)bit[i]=0;
	for(int i=1;n>=i;i++)pos[A[i]]=i,add(i,1);
	for(int i=1;n>=i;i++){
		res+=sum(pos[i])-i;
		add(1,1);add(pos[i],-1);
	}
	return res;
}

void work(){
	cin>>n;
	for(int i=1;n>=i;i++)cin>>a[i];
	for(int i=1;n>=i;i++)cin>>b[i];
	int flg=0;
	for(int i=1;n>=i;i++)cnt[a[i]]=0;
	for(int i=1;n>=i;i++){
		cnt[a[i]]++;
		if(cnt[a[i]]==2)flg=1;
	}
	for(int i=1;n>=i;i++)cnt[b[i]]--;
	for(int i=1;n>=i;i++)
		if(cnt[a[i]]){
			puts("NO");
			return ;
		}
	if(flg){
		puts("YES");
		return ;
	}
	vector<int>v;
	map<int,int>ma;
	for(int i=1;n>=i;i++)v.push_back(a[i]);
	sort(v.begin(),v.end());
	for(int i=0;n>i;i++)ma[v[i]]=i+1;
	for(int i=1;n>=i;i++)a[i]=ma[a[i]];
	for(int i=1;n>=i;i++)b[i]=ma[b[i]];
	for(int i=1;n>=i;i++)A[i]=a[i];
	int t1=get();
	for(int i=1;n>=i;i++)A[i]=b[i];
	int t2=get();
	if(t1%2==t2%2){
		puts("YES");
	}else puts("NO");
}
int main(){
	int _T;
	cin>>_T;
	while(_T--)work();
	return 0;
}
```

---

## 作者：Kolkas (赞：2)

这是本蒻蒻的第一篇题解，如果有些解释不清楚的地方，请各位佬们一定一定一定要补充一下。

正篇开始：

解题的思路是结合数学的分析对数组进行暴力的维护（说白了其实就是找规律然后根据性质对结果进行推导）。

------------
我们先来证明两个性质（顺带分析一下题目）：

1）任意长度的交换都可以由若干个长度为 $2$ 的交换进行等效替代。

证明：

我们将数组中交换的两个数的下标的差值 $+1$（我们不妨叫做 $k+1$）定义为长度为 $k+1$ 的交换。

举个例子，就比如 $[13,14,5,2,0]$ 经过交换变为 $[13,14,0,2,5]$（将 $5$ 和 $0$ 进行交换）就是一个长度为 $3$ 的交换。

假设现有数组 $a[5,2,3,4,1]$，我们可以用一个长度为 $5$ 的交换将 $1$ 和 $5$ 进行交换变成 $[1,2,3,4,5]$，显然除此之外，我们还可以先通过 $4$ 次长度为 $2$ 的交换将 $1$ 移到 $5$ 的左边（可以将长度为 $2$ 的交换理解为前进一个位置，如下所示：


初态：$5,2,3,4,1$

中间态 $1$：$5,2,3,1,4$（相当于 $1$ 前进一次插到 $3$ 和 $4$ 中间）

中间态 $2$：$5,2,1,3,4$（同上前进一次）

中间态 $3$：$5,1,2,3,4$（同上）

末态：$1,5,2,3,4$（同上）

这样我们就通过 $4$ 次长度为 $2$ 的交换让 $1$ 来到了 $5$ 的左边，同理可知，我们可以再通过 $3$ 次长度为 $2$ 的交换将 $5$ 移到 $4$ 的右边，形成最终的 $[1,2,3,4,5]$ 一共进行了 $3+4=7$ 次长度为 $2$ 的交换，不难发现，其中 $4$ 是初态中 $1$ 和 $5$ 的下标的差值，$3$ 是下标的差值再减去 $1$。显然，该随机样例具有通性。

可得结论：任意长度为 $k+1$ 的交换可以由 $2k-1$ 个长度为 $2$ 的交换进行等效替代（可以在纸上手动模拟一下，很快能得出结论）。

2）最终 $a,b$ 数组所通过相同个数的长度为 $k+1$ 的交换所形成的相同的结果有很多个，数量是 $n!$（$n$ 为数组 $a,b$ 的长度）。

证明：

比如 $a[1,2,5,4,3],b[3,2,1,4,5]$ 都可以通过一个长度为 $3$ 的交换变成末态 $[1,2,3,4,5]$，到这里本就应该结束了，但是我们还是可以继续对数组 $a,b$ 的相同两个位置进行长度相等的交换，即这个末态并不只有 [1,2,3,4,5] 这一种情形，应该是 $5$ 的全排列（$120$ 种）。换言之，只要是 $a,b$ 通过相同的努力（等次等长度的交换）最终走在了一起（变成同一种结果）就可以啦，至于这个末态长什么样子我们是完全不关心的。

那我们不妨把这种“双向奔赴”变为数组 $b$ 一个人的“单向奔赴”，即将末态就当作 $a$ 数组最开始的样子，让数组 $b$ 想方设法变成 $a$ 即可（因为这种末态有 $n!$ 种样子，一定有其中一种是数组 $a$ 现在的样子）。

性质 $2$ 结合性质 $1$ 我们就可以得出，数组 $b$ 通过若干个（不妨记作 $x$）长度为 $2$ 的交换一定可以变成数组 $a$ 的样子，（因为由性质 $1$ 可知，就算长度不为 $2$ 的交换也可以等价为多个长度为 $2$ 的交换，无非就是多一些长度为 $2$ 的交换，累加在一起就好了）。

好的，数组 $b$ 终于通过了 $x$ 个长度为 $2$ 的交换变成了数组 $a$ 的样子，只要数组 $a$ 还保持不变，我们就可以输出 YES 了。

这么久了，数组 $a$ 还能是原来的样子吗？显然，因为是长度为 $2$ 的交换，所以数组 $a$ 中任意挑选两个元素并一直把它们换来换去就好了，所以只要 x 是偶数就是 YES，奇数就是 NO。


------------
附上AC代码：
```cpp
#include <iostream>
#include <algorithm>//swap函数在这里面
using namespace std;

const int N=1e5+10;
int a[N],b[N];

int main()
{
    int t; scanf("%d",&t);//时间限制比较严格，所以用scanf和printf
    while(t--)
    {
        int x = 0;
        int n; scanf("%d",&n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        for(int i = 0; i < n; i++) scanf("%d", &b[i]);
        
        int next = 1;//用来判断是否能执行for循环的后续操作
        for(int i = 0; i < n; i++)
        {
            int flag = 0, first = 0;
            
            if(a[i] != b[i])
            {
                first++;
                for(int j = i + 1; j < n; j++)
                {
                    if(b[j] == a[i])
                    {
                        flag++;
                        swap(b[i], b[j]);
                        int k = j - i;
                        x += 2 * k - 1;
                        x %= 2;//x不开longlong累加在一起并最终去判断奇偶性是因为容易超时
                        break; // 提前退出内层循环,记得要写,不然会超时
                    }
                }
            }
            
            if(flag == 0 && first == 1)//如果数组b中有a中没有的数(flag就会一直等于0)，直接返回
            {
                next--;
                printf("NO\n");
                break;
            }
        }
        if(next)
        {
            if(x == 0) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
```


------------
~~终于~~结束咯，仍需指出的是算法的时间复杂度大概是 $O(n^2)$ 的，题目的 $n$ 给到了 $100000$，写的时候还是要多注意。

---

## 作者：Special_Tony (赞：2)

# 思路
显然，如果数组排序后不完全相同，那肯定无解（不用解释吧）。显然，因为 $a,b$ 数组内的元素分别不相同，所以交换两个数会使各自的逆序对 $+1$ 或 $-1$，但两个数组的逆序对之差的奇偶性不变，而相同的数组的逆序对之差是 $0$ 即一个偶数，所以，我们只要看两个数组的逆序对之差是否为偶数就行啦。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, a[100005], b[100005], c[100005];
ll sum1, sum2;
void mergesort (int l, int r, int a[], ll& ans) {
	if (l >= r)
		return ;
	int mid = (l + r) / 2, i = l, j = mid + 1, k = l;
	mergesort (l, mid, a, ans), mergesort (mid + 1, r, a, ans);
	while (i <= mid && j <= r)
		if (a[i] > a[j])
			c[k ++] = a[j ++], ans += mid - i + 1;
		else
			c[k ++] = a[i ++];
	while (i <= mid)
		c[k ++] = a[i ++];
	while (j <= r)
		c[k ++] = a[j ++];
	for (int i = l; i <= r; i ++)
		a[i] = c[i];
	return ;
}
bool cmp () {
	for (int i = 0; i < n; ++ i)
		if (a[i] != b[i])
			return 1;
	return 0;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		for (int i = 0; i < n; ++ i)
			cin >> b[i];
		sum1 = sum2 = 0;
		mergesort (0, n - 1, a, sum1), mergesort (0, n - 1, b, sum2); //归并排序顺便求出逆序对
		if (cmp ())
			cout << "No\n";
		else if ((sum1 ^ sum2) & 1)
			cout << "No\n";
		else
			cout << "Yes\n";
	}
	return 0;
}
```

---

## 作者：ben090302 (赞：0)

妙妙题。

先考虑一个结论：

若答案为是，当且仅当两个数列一定在相同奇偶性的冒泡后可以变成相同的有序数列。

首先我们可以发现，大的换和相邻的冒泡换没有本质区别，因为我们可以让两个数来回换。

奇偶相同就是要求两个来回换的数最后相对位置正确。

粗略分析我们就能大概想到这个结论是对的。

考虑到冒泡次数等于逆序对个数，树状数组维护以下就行了。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lb(x) (x&(-x))
const int N=3e5+5;
int T,n;
int a[N],b[N];
int B[N];
int t[N];
void add(int x,int k){
    for(int i=x;i<=200000;i+=lb(i)){
        t[i]+=k;
    }
}

int query(int x){
    int res=0;
    for(int i=x;i;i-=lb(i)){
        res+=t[i];
    }
    return res;
}

void work(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    int n1=0,n2=0;
    for(int i=1;i<=n;i++){
        n1+=query(a[i]);
        add(a[i],1);
    }   
    for(int i=1;i<=n;i++) add(a[i],-1);
    for(int i=1;i<=n;i++){
        n2+=query(b[i]);
        add(b[i],1);
    }
    for(int i=1;i<=n;i++) add(b[i],-1);
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        if(a[i]!=b[i]){
            cout<<"NO\n";
            return ;
        }
    }
    if((n1%2)==(n2%2)){
        cout<<"YES\n";
    }
    else{
        cout<<"NO\n";
    }
}
signed main(){
    cin>>T;
    while(T--){
        work();
    }
}
```

---

## 作者：白鲟 (赞：0)

一次远距离交换可以替换为多次相邻交换，仅考虑相邻交换显然不劣。两个数列各交换一次又等价于一个数列交换两次。因此只需判断从一个数列相邻交换到另一个数列的次数是否为偶数，即将第二个数列根据第一个数列的顺序重标号后，求逆序对数的奇偶性。

```cpp
#include <cstdio>
const int maxn = 1e5, maxv = 2e5;
int T, n, x, loc[maxv + 1], a[maxn + 1], b[maxn + 1], t[maxn + 1];
int calc(int l, int r) {
    if(l == r) {
        return 0;
    }
    int mid = (l + r) >> 1, res = calc(l, mid) ^ calc(mid + 1, r), i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if(b[i] > b[j]) {
            t[++k] = b[j++];
            res ^= ((mid - i + 1) & 1);
        }
        else {
            t[++k] = b[i++];
        }
    }
    while (i <= mid) {
        t[++k] = b[i++];
    }
    while (j <= r) {
        t[++k] = b[j++];
    }
    for (int p = l; p <= r; ++p) {
        b[p] = t[p - l + 1];
    }
    return res;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        bool flag = true;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            loc[a[i]] = i;
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &b[i]);
            b[i] = loc[b[i]];
            if (!b[i]) {
                flag = false;
            }
        }
        if (!flag) {
            puts("NO");
        }
        else {
            puts((calc(1, n) & 1) ? "NO" : "YES");
        }
        for (int i = 1; i <= n; ++i) {
            loc[a[i]] = 0;
        }
    }
    return 0;
}
```

---

## 作者：DrAlfred (赞：0)

摘要：数据结构，逆序对

[传送门：https://www.luogu.com.cn/problem/CF1983D](https://www.luogu.com.cn/problem/CF1983D)

## 题意

给定两个长度为 $n$ 的，由互不相同的数组成的数列 $a_n, b_n$。每次操作你能选择满足 $r - l = q - p, 1 \leq l \leq r \leq n, 1 \le p \le q \le n$ 的四个下标 $l, r, p, q$，交换 $a_l$ 和 $a_r$，$b_p$ 和 $b_q$。问是否能经过若干次操作使得 $a = b$？若可以，输出 `YES`，否则输出 `NO`。

## 分析思路

$23 \min$ 切这题，上大分。

若 $a$ 和 $b$ 的元素不同，直接输出 `NO`。

否则，我们可以构造出一个长度为 $n$ 的排列 $p_n$，使得 $a_{p_i} = b_i$。我们最终的目的是使得 $p_i = i$。注意到每次操作，我们都能减少（或增加） $p_i$ 中的两个（或零个）逆序对。所以如果一开始 $p_n$ 的逆序对个数为奇数，则一定为 `NO`。否则使用类似冒泡排序的方法我们总能找到一种使得 $p_n$ 有序的操作方案。

使用树状数组求出逆序对。时间复杂度 $O\left(n\log n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
using i64 = long long;
template <class T>
struct Fenwick {
    std::vector<T> c;
    inline int lowbit(int x) { return x & -x; }
    inline void merge(T &x, T &y) { x = x + y; }
    inline T subtract(T x, T y) { return x - y; }
    inline void update(size_t pos, T x) {
        for (pos++; pos < c.size(); pos += lowbit(pos)) merge(c[pos], x);
    }
    inline void clear(void) {
        for (auto &x : c) x = T();
    }
    inline T query(size_t pos) {
        T ans = T();
        for (pos++; pos; pos ^= lowbit(pos)) merge(ans, c[pos]);
        return ans;
    }
    inline T query(size_t l, size_t r) {
        return subtract(query(r), query(l - 1));
    }
    Fenwick(size_t len) : c(len + 2) {}
};
Fenwick<i64> C(N);
int n, a[N], b[N];
inline void YES(void) { cout << "YES\n"; }
inline void Yes(void) { cout << "Yes\n"; }
inline void NO(void) { cout << "NO\n"; }
inline void No(void) { cout << "No\n"; }
inline void YES_NO(bool cond) { cond ? YES() : NO(); }
inline void Yes_No(bool cond) { cond ? Yes() : No(); }
inline void solve(void) {
    std::cin >> n;
    std::map<int, int> pos;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i], pos[a[i]] = i;
    }
    std::vector<int> vec = {0};
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) {
        if (!pos.count(b[i])) return NO();
        vec.push_back(pos[b[i]]);
    }
    i64 inv = 0;
    Fenwick<int> C(2 * n);
    for (int i = 1; i <= n; i++) {
        inv += i - 1 - C.query(vec[i]);
        C.update(vec[i], 1);
    }
    YES_NO(inv % 2 == 0);
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    int t = 1;
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：GoldenCreeper (赞：0)

首先发现对于任何一个操作满足 $l-r=q-p$，都可以通过 $\mathrm{swap}(l,l+1),\mathrm{swap}(l+1,r),\mathrm{swap}(p,p+1),\mathrm{swap}(p+1,q)$ 来完成，所以我们只需要判断两个序列能不能通过相同数量的交换两个相邻的元素而转换成相同的数组即可。

显然 $a$ 和 $b$ 的元素必须相等。不妨设转换后的数组为排序后的 $a$，记为 $s$，因为重复两次交换相邻元素可以使数组不变，所以只需统计 $a$ 转变到 $s$ 所需的操作次数和 $b$ 转变到 $s$ 所需的操作次数，并判断奇偶性是否相同即可。

参考实现：

```cpp
/*

 @Author: CreeperOI
 @Problem: D
 @Start Time: 2024-07-07 23:58
 @Finish Time: 2024-07-07

*/
#include <bits/stdc++.h>
// #define int long long
using namespace std;

int const N = 2e5 + 10, mod = 1e9 + 7;
int n, m, k, a[N], b[N], sa[N], sb[N];
pair<int,int> ta[N], tb[N];

void Main(){
    cin >> n;
    for (int i = 1;i <= n;++i) cin >> a[i];
    for (int i = 1;i <= n;++i) cin >> b[i];
    
    // 离散化
    for (int i = 1;i <= n;++i) {
        ta[i] = {a[i], i};
        tb[i] = {b[i], i};
    }

    sort(ta + 1, ta + 1 + n, [](pair<int,int> x, pair<int,int> y){
        return x.first < y.first;
    }), sort(tb + 1, tb + n + 1, [](pair<int,int> x, pair<int,int> y){
        return x.first < y.first;
    });
    int fl = 0;
    for (int i = 1;i <= n;++i){
        if (ta[i].first != tb[i].first) {
            fl = 1;
            break;
        }
    }
    if (fl == 1){
        puts("NO");
        return;
    }
    for (int i = 1;i <= n;++i) {
        a[ta[i].second] = i; 
        b[tb[i].second] = i;
    }

    for (int i = 1;i <= n;++i) {
        sa[a[i]] = i;
        sb[b[i]] = i;
    }
    int ta = 0, tb = 0;
    for (int i = 1;i <= n;++i) {
        if (a[i] == i) continue;
        swap(a[i], a[sa[i]]);
        swap(sa[a[i]], sa[a[sa[i]]]);
        ta ++;
    }
    for (int i = 1;i <= n;++i) {
        if (b[i] == i) continue;
        swap(b[i], b[sb[i]]);
        swap(sb[b[i]], sb[b[sb[i]]]);
        tb ++;
    }
    puts(ta % 2 == tb % 2 ? "YES" : "NO");
}
signed main() {
    // freopen("cpp.in", "r", stdin);
    // freopen("cpp.out", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--) Main();
    // cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
    return 0;
}
```

---

