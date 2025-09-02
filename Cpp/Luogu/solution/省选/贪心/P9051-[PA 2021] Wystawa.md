# [PA 2021] Wystawa

## 题目描述

给定长度为 $n$ 的序列 $a, b$。

你需要构造一个序列 $c$，构造方法为：

- 选择 $k$ 个 $i$，令 $c_i \leftarrow a_i$。
- 对于其他 $i$，令 $c_i \leftarrow b_i$。

求序列 $c$ 的最大子段和的最小值，并给出一种方案。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq k \leq n$，$-10^9 \leq a_i, b_i \leq 10^9$。

## 样例 #1

### 输入

```
6 2
-1 7 0 2 -5 0
3 1 4 -3 -3 12```

### 输出

```
4
BBABBA```

## 样例 #2

### 输入

```
3 2
-1 -4 -1
-4 -2 -1```

### 输出

```
0
AAB```

# 题解

## 作者：Usada_Pekora (赞：11)

题意：给定两个长度为 $n$ 的序列 $a,b$，试构造一个同样长 $n$ 的序列 $c$，满足有恰好 $k$ 个位置，$c_i\leftarrow a_i$，其它位置 $c_i\leftarrow b_i$，请输出所有合法的 $c$ 里最大子段和最小的一个，如果有多个，输出任意一个即可。

直接构造一个最小的不是很好做，但是可以构造一个不超过 $x$ 的出来，即可以判定一个值是否合法，所以考虑二分。

对于 `check`，考虑这样一点：当 $a_i<b_i$ 时，我们选 A 肯定是更好的，假设有 $k^{'}$ 个点满足这个条件，那么我们只需要把这些位置填 A，然后替换 $k^{'}-k$ 个点。

怎么替换呢？显然是替换代价最小的那些点。当出现前缀的最大子段和 $g \leq 0$ 的时候考虑替换，注意：若换了以后最大子段和会变成一个正数，那么不应该进行这次替换，同时把这个 A 换掉的代价应该加上 $g$（原因显然）。在求完整个序列的最大子段和后，我们再考虑替换剩下的数，只要选出最小的一些加到 $g$ 上就好了。

我们还需要维护一个数应不应该被替换，显然，如果一个位置应该被替换，则代价比它小的位置应该被替换；那么，维护另一个最大子段和 $h$，对应的选数策略是能选 B 就选 B，如果这个 $h$ 超过了 $x$，那么此时替换代价最大的位置就不应该被换掉，让 $h$ 减去它的代价，然后删掉它。

需要维护每个位置的代价，然后支持单点赋值（或插入删除），全局最值。随便搞一个数据结构都行。

当然，我们上面的假设基于 $k^{'}\geq k$，否则，考虑交换 AB，然后填 $n-k$ 个新的 A 即可，注意 $a_i=b_i$ 的处理，我们之前的做法是只在 $a_i\lt b_i$ 时才选择 $a_i$，即相等时选择 $b_i$，交换后也应该保持这个方案。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
struct node {
	int pos;
	ll val;
	node(int _pos = -1, ll _val = -2e14) {
		val = _val, pos = _pos;
	}
	bool operator < (const node &o) const {
		return (val ^ o.val) ? (val < o.val) : (pos < o.pos);
	}
};
int n, k, kk, a[N], b[N], swi;
char ans[N];
inline bool check(ll x) {
	ll g = 0, h = 0;
	int rest = kk - k;
	set<node> S;
	for (int i = 1; i <= n; i++) {
		if (a[i] < b[i] + swi)
			g += a[i], ans[i] = 'A', S.insert(node(i, b[i] - a[i]));
		else
			g += b[i], ans[i] = 'B';
		if (g > x)
			return false;
		while (rest && g <= 0ll && !S.empty()) {
			auto it = S.begin();
			if (g + it->val <= 0ll) 
				ans[it->pos] = 'B', g += it->val, rest--, S.erase(it);
			else {
				S.erase(it), S.insert(node(it->pos, g + it->val));
				break;
			}
		}
		g = max(g, 0ll), h = max(h + b[i], 0ll);
		while (h > x && !S.empty()) {
			auto it = --S.end();
			h -= it->val, S.erase(it);
		}
	}
	while (rest && !S.empty()) {
		auto it = S.begin();
		ans[it->pos] = 'B', g += it->val, rest--, S.erase(it);
	}
	return rest == 0 && g <= x;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	for (int i = 1; i <= n; i++)
		if (a[i] < b[i])
			kk++;
	swi = 0;
	ll l = 0, r = 2e14, ans_val = -1;
	if (kk < k) {
		kk = n - kk, k = n - k, swi = 1;
		for (int i = 1; i <= n; i++)
			swap(a[i], b[i]);
	}
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (check(mid))
			ans_val = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	assert(check(ans_val));
	cout << ans_val << '\n';
	for (int i = 1; i <= n; i++)
		ans[i] = (!swi ? "AB" : "BA")[ans[i] - 'A'];
	for (int i = 1; i <= n; i++)
		cout << ans[i];
	cout << endl;
	return 0;
}
```

---

## 作者：pref_ctrl27 (赞：11)

### [PA2021] Wystawa

#### Description

给定两个长度为 $n$ 的序列 $a,b$，要求构造一个序列 $c$，$c_i$ 等于 $a_i$ 或者 $b_i$，并且恰好有 $k$ 个位置等于 $a_i$，其余位置等于 $b_i$。最小化 $c$ 的最大子段和。

$n\leq 2\times 10^5,-10^9 \leq V\leq 10^9$。

#### Analysis

为了方便处理，我们希望让选数的过程变得具有单调性，即答案随 $k$ 的变大而变大。

因此，我们先让 $a_i\leq b_i$ 的位置选 A，其它选 B，设此时选 A 的个数为 $k'$。对于 $k'<k$ 的情况，我们让 AB 反转即可。可以证明，如果我们让选 B 的位置对应的 $a_i \gets b_i$，答案不变。此时 $a_i\leq b_i$。

考虑二分答案 $x$。

设 $f_{i,j}$ 表示前 $i$ 个位置选 $j$ 个 B，任意子段和 $\leq x$ 时最小化最大后缀和。
转移形如 $f_{i,j}\gets f_{i-1,j}+a_i$ 和 $f_{i,j}\gets f_{i-1, j-1}+b_i$，同时对 $0$ 取 $\max$，删去末尾 $>x$ 的位置，合法等价于 $f_{n,n-k}$ 存在。

考虑优化 DP 转移。
画出 $(j,f_{i,j})$ 的图像，可以发现转移相当于先向上平移 $a_i$，然后从后往前依次尝试将斜率替换为 $b_i-a_i$ 然后将后面的斜率加上一个当前斜率的减少量，然后删去后面一段并将一段前缀变为 $0$。
可以发现，$f$ 是凸的，因此可以直接看成将斜率 $b_i-a_i$ 插入凸包。
对于前缀变为 $0$ 操作，相当于前缀斜率变为 $0$ 并改变交界处的斜率。

这些操作可以用一个 `set` 维护。
复杂度 $\mathcal O(n\log n\log V)$。

---

## 作者：是青白呀 (赞：6)

首先，我们显然有一个 $O(n)$ 求固定序列最大子段和的方案。于是可以二分答案 $x$，check 的部分套上一个 dp 解决：设 $dp_{i,j}$ 表示考虑到 $i$，从 $b$ 中选了 $j$ 个数，目前的最大子段和不超过 $x$ 的最大后缀和的最小值。转移有 $dp_{i,j}=\max(\min(dp_{i-1,j}+a_i,dp_{i-1,j-1}+b_i),0)$。

这个 dp 状态数爆炸了，贪心对最大字段和问题显然没有出路，考虑**整体 dp 优化**。将 $(j,dp_{i,j})$ 作为点刻画在平面直角坐标系上，第一个转移是整体抬升 $a_i$ 的高度，但第二个转移，由于我们不知道点之间的大小关系，是不好实现的。同时，最后抬平到 $0$ 和抹掉大于 $x$ 的操作也不好做。

于是考虑找一个办法让点变得有序，这样抬平和抹除操作就会好实现一些。若想使得点单调递增，那么就需要满足一个单调性：每多选一个 $b$，花费就增加一点。

此时可以先考虑一个没有 $k$ 的限制的最优状态，假设有 $v$ 个 $i$ 满足 $a_i\leq b_i$，则这 $v$ 个位置选 $a$ 更优，其它的位置选 $b$ 更优。不妨设 $v\geq k$，对于 $v<k$ 的情况可以通过交换 $a$ 和 $b$，且令 $k\gets n-k$ 达成。那么此时，在原本选 $b$ 的位置不变的情况下，还需要选择 $v-k$ 个 $a_i\leq b_i$ 的点选成 $b$，而这样的点越多，显然越劣。

为了方便刻画整个问题，我们交换 $a_i>b_i$ 的 $a_i$ 和 $b_i$，并钦定该位置只能选 $a_i$，同时给 $k\gets k+1$。显然这样处理不会改变答案。此时满足 $b$ 选得越多，答案越劣。最终目标变为对新的 $a$、$b$ 序列，从 $b$ 中选 $n-k$ 个，最小化最大后缀和。你会发现此时 $(j,dp_{i,j})$ 形成了一个下凸壳。

考虑当前情况下的维护方式。我们考虑在 set 中维护每个点相对于前一个点的斜率，这个斜率显然是不降的。同时，我们在外部维护初始点的点值和总的抬升高度。考虑每个操作如何实现：

- 对于全局抬升 $a_i$ 的第一个更新，我们直接修改初始点的点值即可。复杂度 $O(1)$。
- 对于第二个更新，实际上是增加了一个 $b$ 的选择，所有含有贡献大于 $b_i-a_i$ 的 $j$ 都会更新决策，扔掉一个贡献最大的，并选上 $b_i-a_i$，反映在图像中就是插入了一段斜率为 $b_i-a_i$ 的线段，将这个斜率直接插入 set，并更新抬升高度即可。复杂度 $O(\log n)$。
- 对于对 $0$ 取 $\max$ 的操作，实际上是取出所有值小于 $0$ 的点，修改成 $0$，并调整下一个点对应的斜率。可以考虑每次暴力取出最靠前的线段，并更新初始点值和抬升高度，直到初始点值不小于 $0$ 即可。你发现一个线段改为 $0$ 之后，所有的更新都和维护的起始点同步了，于是直接把它取出来单独维护**值位于起始点位置**的个数即可。你发现这样操作的话，一个线段只会被取出来一次，故复杂度均摊到每一次操作是 $O(\log n)$。
- 对于抹去值大于 $x$ 的点的操作，每次暴力取出最靠后的线段，并更新初始点值和抬升高度，直到初始点值加上抬升高度的值不超过 $x$ 即可。复杂度仍然是均摊 $O(\log n)$。

最终只需要判断 set 中所有点数和是否不小于 $n-k+1$ 即可。总复杂度 $O(n\log V\log n)$。

最后构造方案是容易的。我们发现每一个点的斜率都是由一个 $b_i-a_i$ 贡献的。我们找到最后 set 中及外部单独维护的前 $n-k$ 个点，它们对应的 $n-k$ 个 $i$ 就是选成 $b$ 的 $n-k$ 个位置。

代码比较好写。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) lson[x]
#define rs(x) rson[x]
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=1e5+5,M=105,inf=1e18+7,mo=1e9+7;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,k;
int a[N],b[N];
vector<int>posb,posn;
void addz(int pos){
	posn.push_back(pos);
}
struct slope{
	set<pii>s;
	set<pii>::iterator it;
	int stp=0,ht=0;
	void init(){
		stp=0,ht=0;
		s.clear();
	}
	void insert(int del,int x){
		s.insert(mp(del,x)),ht+=del;
	}
	void del_front(){
		while(!s.empty()&&stp+(s.begin()->fir)<0){
			int ndel=s.begin()->fir;
			addz(s.begin()->sec);
			stp+=ndel,ht-=ndel;
			s.erase(s.begin());
		}
		if(!s.empty()&&stp<0){
			int ndel=s.begin()->fir,nid=s.begin()->sec;
			s.erase(s.begin());
			ndel+=stp,ht+=stp,stp=0;
			s.insert(mp(ndel,nid));
		}
		else if(stp<0)stp=0;
	}
	void del_back(int x){
		while(!s.empty()&&stp+ht>x){
			ht-=s.rbegin()->fir;
			it=s.end(),it--;
			s.erase(it);
		}
	}
}S;
bool fix[N];
bool sit[N];
bool check(int x){
	S.init();
	rep(i,1,n){
		S.stp+=a[i];
		if(!fix[i])S.insert(b[i]-a[i],i);
		S.del_front(),S.del_back(x);
		if(S.stp>x)return 0;
	}
	while(!S.s.empty())
	    addz(S.s.begin()->sec),S.s.erase(S.s.begin());
	return (int)posn.size()>=n-k;
}
signed main(){
	read(n),read(k);
	rep(i,1,n)
	    read(a[i]);
	rep(i,1,n)
	    read(b[i]);
	int cntk=0;
	rep(i,1,n)
	    if(a[i]<=b[i])cntk++;
    bool swp=0;
	if(cntk<k){
		swp=1;
		rep(i,1,n)
		    swap(a[i],b[i]);
		k=n-k;
	}
	rep(i,1,n)
	    if(a[i]>b[i])a[i]=b[i],fix[i]=1,k++;
	int le=0,ri=inf,ans=inf;
	while(le<=ri){
		int mid=(le+ri)>>1;
		if(check(mid)){
			posb.clear();
			rep(j,0,n-k-1)
			    posb.push_back(posn[j]);
			ans=mid,ri=mid-1;
		}
		else le=mid+1;
		posn.clear();
	}
	for(auto j:posb)
	    sit[j]=1;
	printf("%lld\n",ans);
	rep(i,1,n){
		if(swp^(sit[i]|fix[i]))printf("B");
		else printf("A");
	}
	return 0;
}
```

---

## 作者：Officer_Xia_ZhuRen (赞：1)

对 [Usada_Pekora 大神的题解](https://www.luogu.com.cn/article/3lnz5h8n) 做一些更多的解释。

能想出这个解法的也是神仙了，先膜拜一下。

二分和预处理部分不做赘述。

考虑先取小的尝试加。

一个增加量 $_\Delta x=a_{i}-b_{i}$（当且仅当 $b_{i}\le a_{i}$）何时会对当前的最大后缀和产生变化？

我们记录当前的最大后缀为和 $g$。

容易发现这些累加都只会发生在当前累加的最大后缀和 $g+_\Delta x>0$ 时，也就是对于这些 $g+_\Delta x<0$ 时的东西，我们把它累加上，不会对当前的 $g$ 在转移时造成任何影响（$g$ 需要与 $0$ 取 $\max$）。

这个不是充分条件，而是必要条件，考虑以当前数字结尾的一段最大后缀，当前数 $c_{i}<0$，而它之前的一段存在 $>0$ 的部分，不能对于其他的数也这么做。

这个时候不能盲目地把 $g$ 贪心掉。

再维护一个贪心的后缀和 $h$，处理那些增量是否合法：具体就是把 $h=\max(h+a_{i},0)$，（注意这里是 $0$，意味着 $h$ 并非一定是包含当前 $c_{i}$ 的后缀和）其中我们尝试检查那些对后缀和 $>0$ 部分有影响的数是否合法。

对于当前的所有数来说：

首先我们注意到那些 $g$ 加上后仍然为 $0$ 的数对于后缀和必定没有影响，它们不应当加到 $h$ 上（也就是与 $0$ 取 $\max$ 的过程中被赋值为 $0$ 了）。

其他的数都一定会对 $h$ 产生影响。

所以当 $h$ 超过限制 $lim$ 的时候，我们贪心地，选择最大的那些 $_\Delta x$ 使它不合法。

最后的判断只要保证剩下的未分配的 $k$ 都有位置接就好，实际上这里的 $g$ 一定都是合法的。

更多细节见注释。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void in(T &n){
	n=0;char c=getchar();bool flag=0;
	for(;c<'0'||c>'9';c=getchar()) if (c=='-') flag=1;
	for(;c>='0'&&c<='9';c=getchar()) (n*=10)+=(c^48);
	if (flag) n=-n;
}
int wlsk[45];int wltp;
template<typename T>
void out(T n,char c=0){
	if (n==0){putchar('0');if (c)putchar(c);return ;}
	if (n<0) putchar('-'),n=-n;
	while(n) wlsk[++wltp]=(n%10),n/=10;
	while(wltp) putchar(wlsk[wltp--]^48);
	if (c) putchar(c);
}
const int N=2e5+5;
typedef long long ll1;
const ll1 inf=1e9+7;
int n,K;
ll1 a[N],b[N];
bool chose[N];
bool C[N];
bool FLAG=0;
void init(){
	in(n),in(K);
	for(int i=1;i<=n;i++)in(a[i]);
	for(int i=1;i<=n;i++)in(b[i]);
	int ca=0;
	for(int i=1;i<=n;i++){
		if(a[i]<=b[i])ca++,chose[i]=0;
		else chose[i]=1;
	}
	//我们假设要选的都是A。 
	if(ca>K){
		FLAG=1;
		//A多了，这个时候转化一下，多选K个B 
		for(int i=1;i<=n;i++){
			swap(a[i],b[i]),chose[i]^=1;
		}
		K=n-K,ca=n-ca;
	}
	K-=ca;//还要选多少个更少的A 
	//让我们把选B的一部分转换成更多的A 
}
struct Node{
	int pos;
	ll1 mx;
	bool operator <(const Node&o)const{
		return mx!=o.mx?mx<o.mx:pos<o.pos;
	}
};
set<Node>S;
set<Node>::iterator iter;
Node tmp;
bool check(ll1 lim){
	int rest=K;
	ll1 g=0,h=0;
	S.clear();
	for(int i=1;i<=n;i++){
		C[i]=chose[i];
		if(!chose[i]){//A更小 
		    g+=a[i];
		}else{//这里当前选的是B，可替换为更大的A。
			g+=b[i],
			S.insert((Node){i,a[i]-b[i]});//等待替换，这里加的是差值
		}
		if(g>lim)return 0;
		//最小限制不满足
		//g本身就是累加形式，所以之前的g<=现在的g,可以直接判
		while(rest&&g<=0&&!S.empty()){
			iter=S.begin();
			if(g+iter->mx<=0){
				rest--;
				g+=iter->mx;
				C[iter->pos]^=1;
				S.erase(iter);
			}else{
				tmp=*iter;S.erase(iter);
				S.insert((Node){tmp.pos,tmp.mx+g});
				break;
			}
		}//注意：这一部分的任何操作不会实质性影响答案
		//因为保持了g<0再判
		g=max(0ll,g),h=max(0ll,h+a[i]);
		//h作为一直累加的，排除了g的贡献，实际上是不断地挑战极限
		//但是如果达到了限制则必然需要替换掉最大的数，
		//使得它加不上去。（不能全部满足，必然舍弃最劣的）
		//由于g已经帮h填平了，所以h只是用来判断哪些能要的
		//h保证了选定的数的累加合法性
		while(h>lim&&!S.empty()){
			iter=S.end();iter--;
			h-=iter->mx;S.erase(iter);
		}
	}
	while(rest&&!S.empty()){
		iter=S.begin();
		C[iter->pos]^=1;
		rest--;S.erase(iter);
	}
	return !rest;//用完了 
}
ll1 ans=-1;
void work(){
	ll1 l=0,r=1e15+6,md;
	while(l<=r){
		md=(l+r)>>1;
		if(check(md)){
			ans=md,r=md-1;
		}else l=md+1;
	}
	check(ans);
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++)C[i]^=FLAG;
	for(int i=1;i<=n;i++){
		C[i]?printf("B"):printf("A");
	}
}
int main(){
	init();
	work();
	return 0;
}
```

---

