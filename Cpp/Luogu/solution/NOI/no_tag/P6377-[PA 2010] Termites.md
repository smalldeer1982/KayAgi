# [PA 2010] Termites

## 题目描述

有一个长度为 $n$ 的数列 $a$，两名玩家轮流行动，每次可以选择一个与 $0$ 相邻的数字，得到数字大小的得分，并将它变为 $0$。求如果两个人都采取最优策略，两个人的得分。

## 说明/提示

#### 数据规模与约定
对于全部的测试点，保证 $1\leq n\leq 10^6$，且对于任何一个 $a$ 中的元素 $x$，都保证 $0\leq x\leq 10^6$ 且至少存在一个 $0$。

## 样例 #1

### 输入

```
8
1 2 0 3 7 4 0 9
```

### 输出

```
17 9```

# 题解

## 作者：251Sec (赞：5)

先考虑只有 deque 的情况，注意到若存在 $a_i\le a_{i+1} \ge a_{i+2}$ 这样的结构，那么先手若取了 $a_i$ 后手一定取 $a_{i+1}$，然后先手一定取 $a_{i+2}$，于是把它们合成一个数 $a_i+a_{i+2}-a_{i+1}$。于是所有 deque 都是单谷的，此时最优策略就是取最大的可取的数。然后有两个栈的情况，只需要把它们拼起来并在中间加上一个 $-\infty$ 即可。

所以为什么大家都在写链表？

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1e13;
int n;
ll a[1000005];
vector<ll> Comp(vector<ll> a) {
	vector<ll> b;
	for (ll x : a) {
		b.push_back(x);
		while (b.size() >= 3) {
			ll x = b[b.size() - 1], y = b[b.size() - 2], z = b[b.size() - 3];
			if (y >= x && y >= z) {
				for (int i = 0; i < 3; i++) b.pop_back();
				b.push_back(x + z - y);
			}
			else break;
		}
	}
	return b;
}
vector<ll> f;
void Add(vector<ll> a) {
	int i = 0, j = a.size() - 1;
	while (i <= j) {
		if (a[i] >= a[j]) f.push_back(a[i++]);
		else f.push_back(a[j--]);
	}
}
ll s;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), s += a[i];
	for (int i = 1, j; i <= n; ) {
		if (a[i]) { i++; continue; }
		j = i + 1;
		while (j <= n && a[j]) j++;
		if (j <= n) {
			vector<ll> b;
			for (int p = i + 1; p < j; p++) b.push_back(a[p]);
			Add(Comp(b));
		}
		i = j;
	}
	vector<ll> t;
	for (int i = n; i; i--) {
		if (!a[i]) break;
		t.push_back(a[i]);
	}
	reverse(t.begin(), t.end());
	t.push_back(-inf);
	for (int i = 1; i <= n; i++) {
		if (!a[i]) break;
		t.push_back(a[i]);
	}
	Add(Comp(t));
	sort(f.begin(), f.end(), greater<ll>());
	ll res = 0;
	for (int i = 0; i < f.size(); i++) res += ((i & 1) ? -1 : 1) * f[i];
	if (res < 0) res += inf;
	else res -= inf;
	printf("%lld %lld\n", (s + res) / 2, (s - res) / 2);
	return 0;
}
```

---

## 作者：chlchl (赞：2)

停课第一天，喵喵喵。

## Solution
由于得分之和是定值，且双方都想让自己分数最大，那么令 $res$ 为**先手得分与后手得分的差**，那么先手的目的是让这个数尽可能大，后手则是尽可能小。

显然原序列可以拆分成若干个区间，其中开头和结尾的区间可以看做栈，每次从栈顶取；中间的区间则可以看成若干个双端队列，每次从两边取。

这个题给部分分可能会好做一些，考虑一个区间的单调性。

对于中间的区间，如果是**单调的**，那么先手直接从最大的一侧取，显然不劣。

开头的区间如果是单调递**增**、结尾的区间如果是单调递**减**的也同理，贪心做就行。

现在讨论不单调的情况。如果 $\exist i\in(1,n),a_{i-1}<a_i,a_i>a_{i+1}$，那么可以证明的是，如果 $a_{i-1}$ 或 $a_{i+1}$ 是可取的值中最大的，先手一定会取 $a_{i-1}$ 和 $a_{i+1}$，后手则一定会取 $a_i$。

考虑反证：若先手取完 $a_{i-1}$ 之后，后手取了一个 $a_j,j\ne i$，那么会有 $a_{i-1}<a_i<a_j$，且 $a_j$ 在取 $a_{i-1}$ 前就已经可被取（因为取走 $a_{i-1}$ 后只有 $a_i$ 是新增加的可取数）。

那先手取 $a_j$ 一定更优，矛盾，证毕。

至于取完 $a_i$ 后为什么会马上再取 $a_{i-1}$ 是类似的。

那么对于这样连续三个数的“山峰”，就可以缩点，权值为 $a_{i-1}+a_{i+1}-a_i$，采用**链表**维护。并且这样缩点，每次取完一个数后先后手是**一定发生变化的**，不用担心最后的统计。

缩完点后，剩下的区间就只剩三种情况：单调递减、单调递增、先减后增，这个时候贪心是可做的。将所有数扔进堆里，**每次取最大**就行。

剩下几种特殊情况：第一个区间单调递减、先减后增，最后一个区间单调递增、先减后增。

其中先减后增的情况，可以把靠近 $0$ 的那一段也放进堆里（这一段显然是可以直接贪心的）。那么就剩下第一个区间单调递减、最后一个区间单调递增的情况。这里以第一个区间单调递减作为例子（最后一个区间是类似的）。

若区间长度是偶数，由于只能从一端取，先手每取一个，后手必然可以取一个比先手更大的，先手是亏的。

所以策略就是先跑完上面贪心的点，把这部分的点留到最后（因为希望把先手挪到别人身上）。

而且这部分取完**先后手是不变的**，因此不可以在中间某个时间段做，一做后面就会全亏。

若区间长度是奇数，最靠近 $0$ 的那个数先手是可以马上取的，这个数可以扔进堆里，剩下的数就变成偶数的情况了。

这部分实现的时候可以把两个相邻的数作差缩点。

最后利用一个和式一个差式可以求出双方的分数。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 10;
int n, sum, res, len, a[N], b[N], op[N];
int l[N], r[N];

#define l(i) (l[i])
#define ll(i) (l[l[i]])
#define lll(i) (l[l[l[i]]])

bool cmp(int a, int b){
	return a > b;
}

main(){
	scanf("%lld", &n);
	r[0] = 1, l[n + 1] = n;
	for(int i=1;i<=n;i++){
		scanf("%lld", &a[i]), op[i] = (a[i] != 0);
		sum += a[i], l[i] = i - 1, r[i] = i + 1;
	}
	for(int i=3;i<=n;i=r[i]){
		while(op[ll(i)] && op[l(i)] && op[i] && a[l(i)] >= a[ll(i)] && a[l(i)] >= a[i])
			a[i] = a[ll(i)] + a[i] - a[l(i)], r[lll(i)] = i, l[i] = lll(i);
	}
	int val = 0, hd = r[0], tl = l[n + 1];
	while(a[hd] >= a[r[hd]] && op[hd] && op[r[hd]])
		val += a[r[hd]] - a[hd], hd = r[r[hd]];
	while(a[tl] >= a[l[tl]] && op[tl] && op[l[tl]])
		val += a[l[tl]] - a[tl], tl = l[l[tl]];//处理那些需要最后取的 
	for(int i=hd;i<=tl;i=r[i]){
		if(op[i])
			a[++len] = a[i];
	}
	sort(a + 1, a + 1 + len, cmp);
	a[++len] = val;//不能取的那些部分留到最后
	for(int i=1;i<=len;i++){
		if(i & 1)
			res += a[i];
		else
			res -= a[i]; 
	}
	printf("%lld %lld\n", (sum + res) / 2, (sum - res) / 2);
	return 0;
}
```

---

## 作者：Drind (赞：2)

唉，调了一个早上也没发现我最初始的代码哪里错了，伤心啊。

回到题目上，首先我们可以把序列分成若干段，中间的段都可以两边取，头尾的段只能从一个方向取。

如果所有序列均存在单调性，那么变得可做，具体怎么做下面再说，但是这题不保证存在单调性，麻烦了。

我们尝试去寻找类似于山峰的结构，就是 $a_{i-1}\le a_i,a_{i+1}\le a_i$ 的结构，无论从哪里开始取，只要先手取了 $i-1$ 或者 $i+1$，后手就应该把 $i$ 拿走（因为这么选，肯定比先手多赚一笔，而且还不改变其他的局面）。那么先手肯定会继续把剩下的另一个拿走（如果拿别的，不如一开始就不要拿这个山峰）。

所以我们可以把山峰缩成一个能让先手和后手的分数差增加 $a_{i-1}+a_{i+1}-a_i$ 的点，现在所有序列都会变成以下三种情况。

1. 单调递增
2. 单调递减
3. 单谷

先考虑在中间的序列（也就是两边都可以取的），发现先手一定会取最大的（因为接下来就没有这么大的给后手取，先手肯定优），所以对于这一部分，我们直接把所有点全塞进一个优先队列里，然后先手后手来回分即可。

然后考虑在边上的序列，如果是越向外越小的序列（如果在开头，那就是单增，如果在结尾，就是单减）的话，依然可以采用刚才的贪心策略（因为先手一下就把最大的拿走了，今后再也没有人能拿到更大的），塞到同一个优先队列即可。

如果是越向外越大的序列，就有点复杂，因为这个时候先手可能是劣的。如果长度是偶数，那么先手一定是劣的，所以没有人会想拿这个序列的任何一个数，我们留到最后，看哪个人最后是先手，就塞给他就行了。如果长度是奇数，处理方法也比较简单，就是把这个序列的开头拿出来，塞到前面的单调队列里，剩下的当偶数来做，为什么呢？如果某个人拿走了序列开头的数，今后这个序列长度就是偶数，而长度是偶数的序列，先手必然是劣的，所以没人想取。所以一个长度是奇数的序列，对于先手来说肯定是优的，那么取了开头的数也无所谓。

如果是单谷的序列，那么结合上述两点，分成两段考虑即可。

实现上有一些小细节，在缩点的时候一定要往搜索方向相反的方向去缩点，不然无法多次合并（就是如果你是从左往右搜索，那么要尝试 $i-2,i-1,i$ 能否缩在一起）。

缩点的过程可以用链表实现。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
inline int _abs(int x){if(x>0) return x;return -x;}

int a[N];
int val[N],tag[N],l[N],r[N];
int b[N],btag[N];
priority_queue<int>q;

void fake_main(){
	int n; cin>>n; int sum=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]; sum+=a[i];
		if(a[i]==0) tag[i]=0; else tag[i]=1;
		val[i]=a[i]; l[i]=i-1; r[i]=i+1;
	}
	r[0]=1; l[n+1]=n;//记一下开头和结尾
	for(int i=3;i<=n;i++){
		while(tag[i]&&tag[l[i]]&&tag[l[l[i]]]&&val[i]<=val[l[i]]&&val[l[i]]>=val[l[l[i]]]){//这个就是我说的往反方向缩点
			val[i]=val[i]-val[l[i]]+val[l[l[i]]];
			l[i]=l[l[l[i]]];//链表连删俩数
			r[l[i]]=i;
		}
	}
	int lv=0,rv=0;
	int L=r[0],R=l[n+1];
	int ts=0;
	
	for(;val[L]>val[r[L]]&&tag[L]&&tag[r[L]];){
		ts+=val[r[L]]-val[L];
		L=r[r[L]];
	}//最前面的序列，先模拟最后俩人来回取的过程，把对两人分数差的贡献记到变量里，最后看谁先手就加给谁
	for(;val[R]>val[l[R]]&&tag[R]&&tag[l[R]];){
		ts+=val[l[R]]-val[R];
		R=l[l[R]];
	}//最后面的序列，处理方法类似
	for(int i=L;i<=R;i=r[i]){//剩下夹在中间的东西，一股脑全塞到优先队列里
		if(tag[i]!=0) q.push(val[i]);
	}
	int delt=0,p=1;
	while(!q.empty()){//一个一个取，如果是先手取的就会给两人差带来正贡献，所以乘1，否则乘-1
		delt+=p*q.top(); q.pop();
		p=-p;
	}
	delt+=p*ts;//别忘记靠边的序列带来的贡献
	
	cout<<(sum+delt)/2<<" "<<(sum-delt)/2<<"\n";
	
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：Felix72 (赞：1)

先把题目转化成这样：

> 有一个变量 $s$，两人按照题设中的规则取数，先手取得 $x$ 会使得 $s \larr s + x$，后手取得会使 $s \larr s - x$，先手要使 $s$ 最大，后手要使 $s$ 最小，求 $s$。

可以发现这个题和原题本质相同，并且两人的利益有了直接冲突，这样更好分析一些。

我们分析题目的形式，是若干个双端队列加上（至多）两个栈。

先考虑一个单谷双端队列的情况（先单调不升，后单调不降），我们声称最优策略是每次取左右两边的较大值。

证明：假设一个人不这么做，那么如果另一个人不吃这套，还是坚持取最大值，你会发现结果还不如取最大值。

这样就解决了单谷的问题。继续考虑一个不是单谷的情况：$a_{i - 1} < a_i > a_{i + 1}$。我们声称这三个数完全等价于 $a_{i - 1} + a_{i + 1} - a_i$，即把这三个数替换成这一个新的数，答案不会变化。

证明：可以看出两人都想要取得更大的数 $a_i$。如果先手取了 $a_{i - 1}$ 或 $a_{i + 1}$，相当于把取 $a_i$ 的机会让给了后手，那么这只有可能是先手想同时取得 $a_{i - 1}$ 和 $a_{i + 1}$，否则如果先手去别的地方取数，那么相当于他还是先手，但是刚刚白白亏了 $a_i - a_{i - 1}/a_{i + 1}$ 的权值，还不如不取。

最后考虑一下前后两个栈的问题。我们把这两个栈拼成一个双端队列，中间加一个 $-\infin$，那么 $-\infin$ 一定是全局最后一个被取走的，这样就和双端队列等价了。算完后把这个 $-\infin$ 的贡献去掉即可。

---

## 作者：qiyichen12 (赞：0)

# 分析
看样例
```
8
1 2 0 3 7 4 0 9
```
首先可以看出，$0$ 必然将序列分成好几块，可以单独讨论。对于单谷的块最优一定是两端选最大。比如对于 ```1 2``` 应先选 ```2```。再比如对于 ```6 4 3 1 5 7 9``` 顺序应该是 ```9 7 6 5 4 3 1```。（可以理解为对于单谷的块两端选最大可以获得一个下降序列）。

## 证明
如果是单谷的块，其形式为 $a_1 > a_2 > a_3 > \dots > a_k < a_{k+1} < a_{k+2} < \dots < a_n$。

而当先手选数时，因为 $\max(a_1,a_n) > a_2,a_{n-1} > a_3,a_{n-2} > \dots > a_k$ 所以两段最大就是单块最大。同时先手无论选什么都无法阻止后手选第二大，故两端选最大一定最优。
```cpp
void Psh(vector<long long> v)
{
	for (int i = 0,j = int(v.size())-1;i <= j;)
	{
		if (v[i] >= v[j]) r.push_back(v[i++]);
		else r.push_back(v[j--]);
	}
}
```

对于非单谷的块，可以对于顶峰的 $a_i,a_{i+1},a_{i+2}$（$a_i < a_{i+1} > a_{i+2}$）考虑转化。通过记录 $res = ans_1-ans_2$ 使得顶峰的 $a_i,a_{i+1},a_{i+2}$ 等价于 $a_i+a_{i+2}-a_{i+1}$。
## 证明
当 $res = ans_1-ans_2$ 时，先手选的数为正，后手为负。

当先手先选到 $a_{i,i+1,i+2}$ 时，他只能选 $a_i$ 或 $a_{i+2}$，而后手一定会选 $a_{i+1}$ 因为 $a_i < a_{i+1} > a_{i+2}$，这是先手无论如何都只能选另一个。即为 $a_i+a_{i+2}-a_{i+1}$。

当后手选时情况反了过来，变成 $a_{i+1}-a_i-a_{i+2}$，但因为他是后手，所以后手在 $res$ 里的贡献还是 $a_i+a_{i+2}-a_{i+1}$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<long long> r;
long long a[1000005];
long long inf = 1e13;
void Psh(vector<long long> v)
{
	for (int i = 0,j = int(v.size())-1;i <= j;)
	{
		if (v[i] >= v[j]) r.push_back(v[i++]);
		else r.push_back(v[j--]);
	}
}
vector<long long> Chg(vector<long long> v)
{
	vector<long long> res;
	for (long long x : v)
	{
		res.push_back(x);
		while ((int)res.size() >= 3)
		{
			int i = res.size()-1;
			if (res[i] <= res[i-1]&&res[i-1] >= res[i-2]) 
			{
				long long t = res[i]+res[i-2]-res[i-1];
				for (int i = 1;i <= 3;i++) res.pop_back();
				res.push_back(t);
			}
			else break;
		}
	}
	return res;
}
int main()
{
	vector<long long> h;
	long long sum = 0,res = 0;
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i],sum += a[i];
	for (int i = 1,j;i <= n;) 
	{
		if(a[i]) 
		{
			i++;
			continue;
		}
		j = i+1;
		while (j <= n&&a[j]) j++;
		if (j <= n)
		{
			for (int k = i+1;k < j;k++) h.push_back(a[k]);
			Psh(Chg(h)),h.clear();
		}
        i = j;
	}
	for (int i = n;i > 0;i--) 
	{
		if (!a[i]) break;
		h.push_back(a[i]);
	}
	reverse(h.begin(),h.end());
	h.push_back(-inf);
	for (int i = 1;i <= n;i++) 
	{
		if (!a[i]) break;
		h.push_back(a[i]);
	}
	Psh(Chg(h));
	sort(r.begin(),r.end(),greater<long long>());
    for (int i = 0;i < int(r.size());i++) res += ((i & 1)?(-1):(1))*r[i];
	if (res < 0) res += inf;
	else res -= inf;
	printf("%lld %lld\n",(sum+res)/2,(sum-res)/2);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P6377)

**题目大意**

> 给定 $a_1\sim a_n$，两个人轮流操作，每次选择一个 $a_i$ 满足 $a_{i-1}=0$ 或 $a_{i+1}=0$，然后将 $a_i$ 加入自己的得分，并令 $a_i\gets 0$。
>
> 求两个人都在最大化自己得分的策略下最终得分。
>
> 数据范围：$n\le 10^6$。

**思路分析**

原题相当于给出若干个双端队列，每次取开头或结尾。

注意到如果 $a_{i-1}<a_i>a_{i+1}$，那么先手取走 $i-1$ 后后手必定取走 $i$，如果在后手其他位置操作，则先手也在这里操作更优秀。

并且先手取走 $a_{i-1}$ 肯定是为了获得 $a_{i+1}$ 的收益，否则在其他位置操作更优。

那么这三个元素可以合并为 $a_{i-1}+a_{i+1}-a_i$，操作后每个双端队列都是单谷的，每次取最大值显然是最优解。

但对于序列两端的队列，只能从一侧取数。

如果 $a_1>a_2$，很显然会最后取走 $a_2$，那么不断操作开头和结尾都会变成单调序列，这样就能排序贪心了。

用链表维护序列。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e6+5;
ll a[MAXN],S,w,b[MAXN];
int n,m,l[MAXN],r[MAXN];
bool o[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,r[0]=1,l[n+1]=n;
	for(int i=1;i<=n;++i) cin>>a[i],o[i]=!!a[i],S+=a[i],l[i]=i-1,r[i]=i+1;
	for(int i=3;i<=n;++i) {
		while(true) {
			int x=l[i],y=l[x],z=l[y];
			if(o[y]&&o[x]&&o[i]&&a[x]>=a[i]&&a[x]>=a[y]) {
				a[i]+=a[y]-a[x],r[z]=i,l[i]=z;
			} else break;
		}
	}
	int s=r[0],t=l[n+1]; ll z=0;
	for(;o[s]&&o[r[s]]&&a[r[s]]<=a[s];s=r[r[s]]) z+=a[r[s]]-a[s];
	for(;o[t]&&o[l[t]]&&a[t]>=a[l[t]];t=l[l[t]]) z+=a[l[t]]-a[t];
	for(int i=s;i<=t;i=r[i]) if(o[i]) b[++m]=a[i];
	sort(b+1,b+m+1,greater<>()),b[++m]=z;
	for(int i=1;i<=m;++i) w+=(i&1?1:-1)*b[i];
	cout<<(S+w)/2<<" "<<(S-w)/2<<"\n";
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

首先考虑一个弱化的问题：如果 $a$ 单调怎么做？

这个问题是易于解决的，每个人都只需要从大往小取即可。

但是问题在于，原序列并没有单调性，我们考虑让它具有单调性。

不妨考虑每一个峰，即 $a_i\ge\max\{a_{i-1},a_{i+1}\}$，此时先手取 $a_{i-1}/a_{i+1}$ 后，后手必须取 $a_i$，然后先手再取另一个。如果取的是其它更优的值，先手显然不会取 $a_{i-1}/a_{i+1}$。

考虑这个博弈问题，其实就是先手要最大化两个的差，后手要最小化两个的差，那么此时先手造成的收益其实就是 $a_{i-1}+a_{i+1}-a_{i}$，我们就可以合并这三个。

容易发现，此时合并之后就只剩下三种情况：

- 单增

- 单减

- 单谷

但是注意到无论哪种情况，极值都一定在两端，所以我们只需要把它们全部塞堆里每次取最大值即可。

此时有些问题，因为边上可能存在取不了极值的情况，因为有一边取不了，不妨以左边为例。

如果左边是个单增序列的话，正常取即可。

如果左边是单减序列的话，长度为偶数是先手后手轮流取，后手一定比先手收益更大，所以先手一定不会取，单独算即可；如果长度为奇数，那么最后一个是可以取的，因为这样对方不会取，把它塞进堆里面即可。

如果左边是单谷的话，就分单增和单减部分分别处理即可。

---

