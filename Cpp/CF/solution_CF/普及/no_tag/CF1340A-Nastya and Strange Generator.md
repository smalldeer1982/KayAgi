# Nastya and Strange Generator

## 题目描述

Denis was very sad after Nastya rejected him. So he decided to walk through the gateways to have some fun. And luck smiled at him! When he entered the first courtyard, he met a strange man who was selling something.

Denis bought a mysterious item and it was... Random permutation generator! Denis could not believed his luck.

When he arrived home, he began to study how his generator works and learned the algorithm. The process of generating a permutation consists of $ n $ steps. At the $ i $ -th step, a place is chosen for the number $ i $ $ (1 \leq i \leq n) $ . The position for the number $ i $ is defined as follows:

- For all $ j $ from $ 1 $ to $ n $ , we calculate $ r_j $ — the minimum index such that $ j \leq r_j \leq         n $ , and the position $ r_j $ is not yet occupied in the permutation. If there are no such positions, then we assume that the value of $ r_j $ is not defined.
- For all $ t $ from $ 1 $ to $ n $ , we calculate $ count_t $ — the number of positions $ 1 \leq j \leq n $ such that $ r_j $ is defined and $ r_j = t $ .
- Consider the positions that are still not occupied by permutation and among those we consider the positions for which the value in the $ count $ array is maximum.
- The generator selects one of these positions for the number $ i $ . The generator can choose any position.

Let's have a look at the operation of the algorithm in the following example:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1340A/b046e416b9d8c9ca15a404e7bc85fa278badc8c3.png)Let $ n = 5 $ and the algorithm has already arranged the numbers $ 1, 2, 3 $ in the permutation. Consider how the generator will choose a position for the number $ 4 $ :

- The values of $ r $ will be $ r = [3, 3, 3, 4,         \times] $ , where $ \times $ means an indefinite value.
- Then the $ count $ values will be $ count = [0, 0, 3, 1,         0] $ .
- There are only two unoccupied positions in the permutation: $ 3 $ and $ 4 $ . The value in the $ count $ array for position $ 3 $ is $ 3 $ , for position $ 4 $ it is $ 1 $ .
- The maximum value is reached only for position $ 3 $ , so the algorithm will uniquely select this position for number $ 4 $ .

Satisfied with his purchase, Denis went home. For several days without a break, he generated permutations. He believes that he can come up with random permutations no worse than a generator. After that, he wrote out the first permutation that came to mind $ p_1, p_2, \ldots, p_n $ and decided to find out if it could be obtained as a result of the generator.

Unfortunately, this task was too difficult for him, and he asked you for help. It is necessary to define whether the written permutation could be obtained using the described algorithm if the generator always selects the position Denis needs.

## 说明/提示

Let's simulate the operation of the generator in the first test.

At the $ 1 $ step, $ r = [1, 2, 3, 4, 5], count = [1, 1, 1, 1,       1] $ . The maximum value is reached in any free position, so the generator can choose a random position from $ 1 $ to $ 5 $ . In our example, it chose $ 5 $ .

At the $ 2 $ step, $ r = [1, 2, 3, 4, \times], count = [1, 1,       1, 1, 0] $ . The maximum value is reached in positions from $ 1 $ to $ 4 $ , so the generator can choose a random position among them. In our example, it chose $ 1 $ .

At the $ 3 $ step, $ r = [2, 2, 3, 4, \times], count = [0, 2,       1, 1, 0] $ . The maximum value is $ 2 $ and is reached only at the $ 2 $ position, so the generator will choose this position.

At the $ 4 $ step, $ r = [3, 3, 3, 4, \times], count = [0, 0,       3, 1, 0] $ . The maximum value is $ 3 $ and is reached only at the $ 3 $ position, so the generator will choose this position.

At the $ 5 $ step, $ r = [4, 4, 4, 4, \times], count = [0, 0,       0, 4, 0] $ . The maximum value is $ 4 $ and is reached only at the $ 4 $ position, so the generator will choose this position.

In total, we got a permutation of $ 2, 3, 4, 5, 1 $ , that is, a generator could generate it.

## 样例 #1

### 输入

```
5
5
2 3 4 5 1
1
1
3
1 3 2
4
4 2 3 1
5
1 5 2 4 3```

### 输出

```
Yes
Yes
No
Yes
No```

# 题解

## 作者：随情英 (赞：8)

个人认为，本题最难懂的是题意

#### 题目简述：

给定一个数据生成器，给出一个输出序列，问是否由该生成器生成。

#### 简要思路：
考虑倒序考虑，我们从前往后处理输出序列，每次判断当前数字 $x$ 的 $count_x$ 是否是最大的。如果不是，直接退出。否则，标记 $x$，找到 $x$ 后面未被标记的第一个数 $y$ 。使 $count_y = count_y + count_x$， $count_x = 0$。
据此，容易写出以下暴力代码

[bf code](https://www.luogu.com.cn/paste/v9c0xjos)

容易发现，这样写法,复杂度是显然 $O(n^2)$ 的，可以被一个排好序的数据卡掉。

考虑数据结构优化。

可以看到，两次内层循坏，一个是找当前最大值，另一个是找当前位置后第一个未标记的位置。区间最大值可以容易地用线段树优化。我们把标记的点用 $1$ 表示，未标记用 $0$。那么第二次内层循环即转化为找 $01$ 序列中一位置后第一个 $1$ 的位置，依然使用线段树。复杂度 $O(nlogn)$

```cpp
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-')
		{
			f = -1;
		}
		c = getchar();
	}
	while (isdigit(c))
	{
		x = x * 10 + c - 48;
		c = getchar();
	}
	return x * f;
}
const int maxn = 200010;
int p[maxn], cnt[maxn];
struct SegmentTree
{
	int l, r;
	int dat, dat2;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define dat(x) tree[x].dat
#define dat2(x) tree[x].dat2
} tree[maxn << 2];
void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r)
	{
		dat(p) = 1, dat2(p) = l;
		return;
	}
	int mid = l + r >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	dat(p) = max(dat(p << 1), dat(p << 1 | 1));
	dat2(p) = l;
}
void change(int p, int x, int d)
{
	if (l(p) == r(p) && x == l(p))
	{
		dat(p) += d;
		if (dat(p) == 0)
		{
			dat2(p) = 1 << 30;
		}
		return;
	}
	int mid = l(p) + r(p) >> 1;
	if (x <= mid)
		change(p << 1, x, d);
	else
		change(p << 1 | 1, x, d);
	dat(p) = max(dat(p << 1), dat(p << 1 | 1));
	dat2(p) = min(dat2(p << 1), dat2(p << 1 | 1));
}
int ask(int p, int l, int r)
{
	if (l <= l(p) && r >= r(p))
		return dat(p);
	int mid = l(p) + r(p) >> 1;
	int val = 0;
	if (l <= mid)
		val = max(val, ask(p << 1, l, r));
	if (r > mid)
		val = max(val, ask(p << 1 | 1, l, r));
	return val;
}
int ask2(int p, int l, int r)
{
	if (l <= l(p) && r >= r(p))
		return dat2(p);
	int mid = l(p) + r(p) >> 1;
	int val = 1 << 30;
	if (l <= mid)
		val = min(val, ask2(p << 1, l, r));
	if (r > mid)
		val = min(val, ask2(p << 1 | 1, l, r));
	return val;
}
void solve()
{
	int n = read();
	for (int i = 1; i <= n; ++i)
	{
		p[read()] = i;
		cnt[i] = 1;
	}
	build(1, 1, n);
	for (int i = 1; i <= n; ++i)
	{
		int w = ask(1, 1, n);
		if (w != cnt[p[i]])
		{
			puts("NO");
			return;
		}
		else
		{
			if (p[i] + 1 <= n)
			{
				int k = ask2(1, p[i] + 1, n);
				if (k != 1 << 30)
				{
					cnt[k] += cnt[p[i]];
					change(1, k, cnt[p[i]]);
				}
			}
			change(1, p[i], -cnt[p[i]]);
			cnt[p[i]] = 0;
		}
	}
	puts("YES");
}
int main()
{
	int T = read();
	while (T--)
	{
		solve();
	}
	return 0;
}
```
注：本题其实是道结论题，但考场上很难轻易想到。既然数据范围允许，写稍劣些的算法又何乐而不为。

---

## 作者：KellyFrog (赞：5)

翻译者来写篇题解。

对于一次标记，假设标记了$k$，那么显然

`count[k右边（不含k）第一个没有标记的位置]+=count[k]`。因为$k$没有了，原来$r_j=k$的$j$都会再找到$k$后面一个没有标记的位置。

首先证明如果$k$被标记了$c$，$k,k+1,...$都被标记了$c,c+1,...$。

证明：

显然对$k=n$成立。

假设：$k$到$n$都成立，$k-q$到$k-1$都没有被标记过；

证明：若$k-q$标记为$c'$，则后面仍然是$c',c'+1,...$的形式。

选中了$k-q$，说明`count[k-q]`是最大的，那么`count[k-q+1]+=count[k-q]`仍然是最大的，并且是惟一最大的，则$k-q+1$一定被标记为$c'+1$，如此往复得证。



------------


故原来的输入序列如果是生成器生成，应该从后往前拆分成若干个公差为1的等差数列。

```cpp
#include <iostream>

using namespace std;

const int MAXN = 1e5 + 5;

int a[MAXN];

void Solve() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i < n; i++) {
		if(a[i + 1] - a[i] > 1) {
			cout << "No" << endl;
			return;
		}
	}
	cout << "Yes" << endl;
}

int main() {
	int t, n;
	cin >> t;
	while(t--) {
		Solve();
	}
}
```

---

## 作者：流绪 (赞：3)

读了半小时题才读懂.......

首先如果数字的数量小于等于 $2$ 个，那么怎么填都一定可以。

我们考虑普遍情况，如果在数组中间一个位置填了一个数 $p$，那么下一个数怎么填呢？显然此时 $r$ 数组为：$[1,2,3,...,p+1,p+1,p+2,p+3,...]$。所以我们必须在 $p$ 的下一个位置填 $p+1$一直填到数组尾部，然后重复上述操作。

因此我们得到一个结论：若序列 $p$ 可以分为多个小段，每个小段都是以 $1$ 为公差的递增等差数列，则可以成功构造。

下面是 $AC$ 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f7f7f7f7f 
#define maxn 1000010
#define ri register int
#define il inline
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define mod 998244353
#define db(x) cout << x << endl; 
#define eps 0.0001
using namespace std;
int a[maxn],v[maxn];
char s[maxn]; 
signed main()
{
	ios::sync_with_stdio(0);
	int t=1;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		int flag = 1;
		for(int i=1;i<=n;i++)
			cin >> a[i];
		if(n<=2)
		{
			cout << "Yes\n";
			continue;
		}
		for(int i=1;i<=n;i++)
			v[i] = 0;
		v[1] = 1;
		a[0] = inf;
		for(int i=1;i<=n;i++)
		{
		//	cout << i << endl;
			if(a[i] >a[i-1])
				flag = 0;
			while(a[i+1] == a[i]+1&&i+1<=n)
				v[i] = 1,i++;
			v[i] = 1;
		}
		for(int i=1;i<=n;i++)
			if(!v[i])
				flag = 0;
		if(flag)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
	return 0;
}
```


---

## 作者：朝夕 (赞：2)

## 题目大意

一个数字排序生成器[1~n的数字都只出现一次]，遵循以下规则：

1）生成一个数组$r$，$r_i$表示从位置$i$往后（包括$i$），第一个还没塞入数字的位置下标。

譬如要生成5个数字，目前生成结果为：$[1,x,x,2,x]$，则r数组为$[2,2,3,5,5]$。

2）生成一个count数组，$count_i$=r数组中等于i的元素个数。

以上面例子的r数组为例，$count=[0,2,1,0,2]$。

3）找到count数组里值最大的元素下标。若有多个则任取一个，然后将本次要放入的数字放入该下标中。

4）直到所有数字全部放入。

现在给你一个数字的排序，问你可不可能通过上面这种方式生成这种排序。

## 解题思路

我们很快可以发现，若本轮生成数字时，将数字放在了下标i上，则下一轮生成数字时，必须放在下标i+1上。

为什么？我们来模拟一遍。

第一轮生成数字，$r=[1,2,3,4,5],count=[1,1,1,1,1]$。可以随便放，假如我们放在3的位置。

第二轮生成数字，由于位置3已有数字，所以$r=[1,2,4,4,5],count=[1,1,0,2,1]$。

则此时只能放在位置4.

注意还要特判：若本轮放在了空数组的最后一位，则下一轮可以随便放。


## 参考代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int p[100005];
int vis[1000005];
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>p[i];
        for(int i=1;i<=n;i++) vis[p[i]]=i;//每个数字生成的下标
        int last=n,f=1;
        p[0]=1e8;
        for(int i=1;i<=n;i++)
        {
            while(p[last]<i) last--;//确定目前最后一位在哪里
            if(vis[i]==last)//如果这个数字放在最后一位，则满足算法
            {
                last--;
                continue;
            }
            else//否则
            {
                if(vis[i+1]==vis[i]+1)//如果下一轮生成位置在本轮后面，则满足
                {
                    continue;
                }
                else//否则不满足
                {
                    f=0;
                    break;
                }
            }
        }
        if(f) puts("Yes");
        else puts("No");
    }
    return 0;
}
```





---

## 作者：ZigZagKmp (赞：0)

本文同步发表于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13749280.html)

本场题解见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1340-solution)
## CF1340A
### 题意简述
有一个随机数生成器。
- 定义 $r_j$ ​表示 $j$ 右边（包括 $j$ ）第一个没有标记的位置。
- 定义 $count_j$ ​表示满足 $r_i=j$ 的 $i$ 的个数。
- 刚开始所有位置都没有被标记。

它的工作方法如下：
- 找到当前 $count$ 值最大且没有被标记的位置 $i$ ，如有多个 $i$ ，则随机选取一个。
- 标记 $i$ 的位置，并将输出序列的第 $i$ 项设为已经被标记的位置的数量。
- 如果还有数没有被标记，重复执行第一步。

判断一个排列是否有可能是这个生成器生成的。

多测，$t\le 10^5,1\le n\le 10^5,\sum n\le 10^5$。
### 算法标签
并查集，可修改堆/线段树/其他数据结构。
### 算法分析
分析 $r_j$ 的修改过程，发现其与并查集类似，且$count_j$对应并查集集合大小。

我们只需要判断当前输出的数是否是 $count$ 值最大且没有被标记即可，这个最大值可以通过堆或者线段树等数据结构求得。

### 代码实现
写的比较丑……
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp>void read(Tp &x){
	x=0;int fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=fh;
}
int n,m;
int a[maxn];
int fa[maxn],siz[maxn];
int fid(int x){
	return fa[x]==x?fa[x]:fa[x]=fid(fa[x]);
}
void merge(int x,int y){//x->y
	int xx=fid(x),yy=fid(y);
	if(xx==yy)return;
	fa[xx]=yy;siz[yy]+=siz[xx];
}
int mx;
set<int>st;

#define lson ((x<<1))
#define rson ((x<<1)|1)
#define mid ((l+r)>>1)
int str[maxn<<2];
void pushup(int x){
	str[x]=max(str[lson],str[rson]);
}
void chg(int x,int l,int r,int p,int v){
	if(l==r){
		str[x]=v;
		return;
	}
	if(p<=mid)chg(lson,l,mid,p,v);
	else chg(rson,mid+1,r,p,v);
	pushup(x);
}
int get_max(){
	return str[1];
}
void upd(int p,int v){
	chg(1,1,n,p,v);
}

signed main(){
	int T;
	read(T);
	while(T--){
		read(n);mx=1;
		for(int i=1,x;i<=n;++i)read(x),a[x]=i;
		for(int i=1;i<=n;++i)fa[i]=i,siz[i]=1;
		int fl=1;st.clear();
		for(int i=1;i<=n;i++)st.insert(i),upd(i,1);
		for(int i=1;i<=n;++i){
			int cur=a[i];
			int mx=get_max();
			if(siz[cur]!=mx){
				fl=0;break;
			}
			st.erase(cur);
			set<int>::iterator nxt=st.lower_bound(cur);
			if(nxt!=st.end()){
				int y=(*nxt);
				merge(cur,y);
				upd(y,siz[y]);
				upd(cur,0);
			}
			else{
				fa[cur]=siz[cur]=0;
				upd(cur,0);
			}
		}
		puts(fl?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：juicyyou (赞：0)

# CF1340A Nastya and Strange Generator
## 解法：
据说这题是结论题，可是考场上没有推出结论，那怎么办呢？这里给出一个不用结论的方法。

首先考虑如何维护 $r_j$，其实这也是个套路，我们开一个并查集，对于每次操作，直接把要放入的位置 $i$ 所在的集合与 $i + 1$ 所在的集合合并，这样，一个位置 $i$ 所在的集合的根节点就是 $r_i$。( 注意，如果根节点是 $n + 1$，那么就说明了这个位置已经没有 $r_i$，了 ) 那怎么统计次数 $count_i$ 呢？只需要给每一个集合开一个附加值 $size$ ，然后用 set 和 map 去维护所有 $size$ 就行了。

下面是我的 Code :
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<set>
#include<cstdlib>
#include<cctype>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e5 + 5;
const ll maxm = 1e3 + 5;
template<class T>
inline T qread(T &IEE){
	register T x = 0, f = 1;
	register char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -f;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return IEE = x * f;
}
template<class T>
inline void qwrite(T a){
	if(!a){
		putchar('0');
		return ;
	}
 	if(a < 0){
		putchar('-');
		a = -a;
	}
	if(a > 9) qwrite(a / 10);
	putchar(a % 10 + 48);
	return ;
}
ll ma, n, t;
ll siz[maxn], c[maxn], fa[maxn], a[maxn];
bool f;
void init(){
	for(int i = 1;i <= n + 1;i++){
		fa[i] = i;
		siz[i] = 1;
	}
	return ;
}
ll find(ll x){
	if(fa[x] == x){
		return x;
	}
	return fa[x] = find(fa[x]);
}
int main(){
	qread(t);
	while(t--){ // 多测
		multiset<ll> ms;
		map<ll, ll> mp;
		qread(n);
		init();
		f = 0;
		for(int i = 1;i <= n;i++){
			qread(a[i]);
			c[a[i]] = i;
			ms.insert(-1);
		}
		mp[1] = n;
		for(int i = 1;i <= n;i++){
			ll tmp = c[i];
			if(ms.empty()){
				f = 1;
				break;
			}
			multiset<ll>::iterator it = ms.begin();
			ma = -(*it);
			if(siz[tmp] == ma){
				--mp[ma];
				if(mp[ma] == 0){
					ms.erase(-ma);
				}
				ll rx = find(tmp), ry = find(tmp + 1); // 并查集
				siz[ry] += siz[rx];
				fa[rx] = ry;
				if(ry != n + 1){
					if(++mp[siz[ry]] == 1){
						ms.insert(-siz[ry]);
					}
				}
			} else {
				f = 1;
				break;
			}
		}
		if(!f){
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}


```

上述算法的单次复杂度为 $\mathcal O(n \log n\, + n\, \alpha(n))$ 可以直接算为 $\mathcal O(n \log n)$，那么算上多组数据后，总的时间复杂度即为 $\mathcal O(\sum n \log n)$ 可以通过此题。

---

