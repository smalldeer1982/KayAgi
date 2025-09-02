# [ABC379D] Home Garden

## 题目描述

高桥有 $10^{100}$ 个花盆。起初花盆都是空的。

你将有 $Q$ 次操作。有三种类型的操作，如下所示：

- `1`：准备一个空花盆，在里面放一颗植物，植物高度为 $0$。
- `2 T`：等待 $T$ 天。在此期间，所有植物的高度增加了 $T$。
- `3 H`：收割所有高度至少为 $H$ 的植物，并输出符合条件的植物数量，将符合条件的植物从花盆中取出。

假定执行 $1$ 和 $3$ 类型的操作花费时间为 $0$。且**一定会有操作 $3$**。

## 说明/提示

对于 $100\%$ 的数据，$1\le Q\le 2\times10^5$，$1\le T,H\le10^9$。操作 $3$ 的次数大于等于 $1$。

## 样例 #1

### 输入

```
6
1
2 15
1
3 10
2 20
3 20```

### 输出

```
1
1```

## 样例 #2

### 输入

```
15
1
1
2 226069413
3 1
1
1
2 214168203
1
3 214168203
1
1
1
2 314506461
2 245642315
3 1```

### 输出

```
2
2
4```

# 题解

## 作者：ikunTLE (赞：14)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc379_d)

### 思路

首先，不难考虑到 $\mathcal{O}(Q^2)$ 的暴力解决方案：每一次操作 2 将所有的植物都增加 $T$；操作 3 挨个统计高度超过 $H$ 的植物数量。

然后，想到操作 2 中可以增加一个变量控制增长的高度 $h$，将操作 2 的时间复杂度降至 $\mathcal{O}(1)$。此后要使操作 1 的初始高度为 $0$，就要将其赋值为 $-h$。

最后，使用**优先队列**降低复杂度。在操作 3 中，每次都删到比 $H$ 低为止。由于所有的植物数量不会超过 $Q$，故总时间复杂度为 $\mathcal{O}(Q\log Q)$，可以通过此题。

**注意事项**

- 不开 `long long` 见祖宗。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
priority_queue<int/*,vector<int>,greater<int>*/>pq;
signed main(){
	int q=read(),h=0;
	while(q--){
		int op=read();
		if(op==1)
			pq.push(-h);
		else if(op==2)
			h+=read();
		else{
			int x=read(),ans=0;
			while(!pq.empty()){
				int temp=pq.top();
				if(temp+h>=x)
					++ans,pq.pop();
				else break;
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：Nagato__Yuki (赞：13)

# Solution

题目要我们支持三种操作：

- 在最前面插入一个数
- 全局加
- 查询大于等于 $h$ 的数的数量并删除

对于全局加，直接维护一个`lazytag`，加的时候直接加在`lazytag`上。

然后对于插入，在插入新的数时直接初始化为`-lazytag`。

我们发现这个数列单调不降，所以查询的时候可以直接`lower_bound`，找到大于等于`h-lazytag`的数就行了。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mxn 200010
ll q,a[mxn],head=200000,tail=200000,lazy;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>q;
    while(q--){
        int opt;cin>>opt;
        if(opt==1)a[--head]=-lazy;//插入
        else if(opt==2){//全局加
            ll t;cin>>t,lazy+=t;
        }
        else{
            ll h;cin>>h;
            ll pos=lower_bound(a+head,a+tail,h-lazy)-(a+head);
            cout<<tail-head-pos<<'\n',tail=head+pos;//查找并删除
        } 
    }
    return 0;
}
```

---

## 作者：adsd45666 (赞：4)

## 题目大意：

实现一个数据结构，使其支持以下三个操作：

`1` 向这个数据结构中插入一个数值为 $0$ 的节点。

`2 T` 将这个数据结构中的所有元素加 $T$ 。

`3 H` 将这个数据结构中大于等与 $H$ 的元素删除并输出删除的元素数。

## 思路分析：

由于不存在使此结构中的元素变小的手段，所以集合中的元素按加入时间来排序，其的值是单调不减的。因为存在单调性，则 $3$ 操作简化为二分查找第一个小于 $H$ 的元素。

那么如何解决 $2$ 操作与删除操作呢？

对于操作 $2$ ，维护一个现时间 $nt$ ，对于每一个新加入的节点，维护其时间戳 $t_i$ ，则其的大小为 $nt-t_i$ 。

删除操作，由于区间具有单调性，在删除时一定是从左往右删除，则实际不用真的删除，只需维护已经删除的点数量 $nl$ ，每次二分查找时，使区间左端点等于 $nl$ 即可。

## 代码详解：

```cpp
#include <bits/stdc++.h>
#define seq(q, w, e) for (int q = w; q <= e; q++)
#define int long long
using namespace std;
const int maxn = 2e5+10,inf=0x7fffffff;
int t[maxn];
int nt,sum,nl,h;
int q,op,tot;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>q;
    while(q--){
        cin>>op;
        if(op==1){
            tot++;
            t[tot]=nt;
        }
        if(op==2){
            cin>>sum;
            nt+=sum;
        }
        if(op==3){
            cin>>h;
            int l=nl,r=tot+1,mid;
            while(l+1<r){
                mid=(l+r)>>1;
                if((nt-t[mid])>=h){
                    l=mid;
                }
                else{
                    r=mid;
                }
            }
            cout<<l-nl<<"\n";
            nl=l;
        }
    }
    return 0;
}
```

---

## 作者：I_Love_DS (赞：3)

## 闲话

第一眼：什么？$10^{100}$？

第二眼：哦，吓人的。

其实这题根本不需要任何高级的数据结构。$O(q)$ ~~玄学~~搞定了。

## 思路

又是一个小模拟。

我们记当前已经等待了 $tot$ 天。一开始，$tot=0$。

那么对所有的第 $2$ 种操作，把 $tot$ 加上 $t$ 即可。

第 $1$ 种操作稍微有点棘手。我们记 $r$ 为最后种上的花的编号。那么把 $r$ 加一即可。

是吗？其实不是，因为我们这样会认为这朵花高度也是 $tot$。

所以我们记个 $a$ 数组，每次加 $r$ 的同时将 $a_r$ 设为 $-tot$，也就是把以前不存在这朵花时等待的时间减掉。此时，每朵花的高度就是 $a_i+tot$。

这下第 $3$ 操作就简单多了。

可以记 $l$ 为舍弃的花的数量。因为舍弃一朵花，意味着这朵花再也不会回来。又因为花的高度是单调不增的，所以可以利用类似双指针的思想，每次将高度大于 $h$ 的花扔掉，$l$ 就加一。

至此，本题结束了。

时间复杂度 $O(q)$，每次操作都是常数或 $O(q)$。

## 代码

```cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int N = 2e5 + 50;

int q, l = 0, r = 0;

ll sum = 0, a[N];

int main() {
	scanf("%d", &q);
	while (q--) {
		int op;
		ll x;
		scanf("%d", &op);
		if (op == 1) {
			a[++r] = -sum; // 把之前的时间减掉
		} else if (op == 2) {
			scanf("%lld", &x);
			sum += x; // 时间加上 x
		} else {
			int cnt = 0;
			scanf("%lld", &x);
			while (sum + a[l + 1] >= x && l < r) ++l, ++cnt;
            // 类似双指针的思想
			printf("%d\n", cnt);
		}
	}
	return 0;
}
```

---

## 作者：PineappleSummer (赞：3)

[D - Home Garden](https://atcoder.jp/contests/abc379/tasks/abc379_d)

很套路吧。

记一个 $tag$ 为当前天数，开一个大根堆记当前存在的植物。

加入一株植物时在大根堆里加入 $-tag$。

天数增加时让 $tag\gets tag+T$。

查询时对于当前大根堆里所有的植物，设其在大根堆里的值为 $p$，则其生长天数为 $p+tag$。由于 $tag$ 相同，所以 $p$ 越大，其生长天数越大。每次取堆顶 $p$，如果 $p+tag$ 小于 $H$，说明剩下的植物都不满足条件，退出循环，否则弹出堆顶，让 $ans$ 加 $1$。对于每次查询输出 $ans$ 即可。

时间复杂度 $\mathcal O(q\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int Q;
priority_queue <int> q;
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> Q;
    int opt, x, tag = 0;
    while (Q--) {
        cin >> opt;
        if (opt == 1) {
            q.push (-tag);
        }
        else if (opt == 2) {
            cin >> x;
            tag += x;
        }
        else {
            cin >> x;
            int ans = 0;
            while (!q.empty ()) {
                if (q.top () + tag >= x)
                    q.pop (), ans ++;
                else break;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
```

---

## 作者：Moya_Rao (赞：2)

# 题目大意
高桥有 $10^{100}$ 个花盆，一开始什么花都没有种。  
现在有 $Q$ 次操作，每次操作有如下三种类型：
- 输入为 `1`：新开一个空花盆，放上一株高度为 $0$ 的新植物。
- 输入为 `2 T`：每珠现有的花都长高 $T$ 单位。
- 输入为 `3 H`：摘掉所有高度不小于 $H$ 的花，并输出能够摘掉的花的个数。

假设执行操作 $1$ 和操作 $3$ 所需时间为 $0$。  
现在请你处理这 $Q$ 次操作，并对于每次操作 $3$ 输出对应的答案，数据保证至少存在一组操作 $3$。

# 思路
~~考场上看到这题为啥就莫名其妙想到了 [P2827 蚯蚓](https://www.luogu.com.cn/problem/P2827) 呢？~~

考虑拿一个数组存下当前所有种植的花的高度。仔细看题后不难发现，这个数组一定是单调不升的。  
但是操作 $2$ 不好解决，你没办法在 $2$ 秒的时间限制内让每次操作 $2$ 都去给每珠花增加高度。不过嘛，有一个很巧妙的方法，其实也来自于 [P2827 蚯蚓](https://www.luogu.com.cn/problem/P2827) ，就是新建一个变量叫做 $up$，花要长高，在这里长高就可以了，而它的实际高度是一开始存储的高度再加上 $up$。但新加的花的初始高度得设为 $-up$，要不然前面长高的那些就也算进去了，那就不对啦！

是不是就解决了呢？当然没有，还有操作 $3$ 呢！别担心，前面不是说了这个数组一定是单调不升的吗？多了一个 $up$ 后肯定也一样嘛。那不就可以二分了？二分一下可以摘走多少珠花就可以啦。但是也不能直接去真的移动数组来摘花呀，没关系，由于 $Q$ 最大只有 $2 \times 10^5$，完全可以开一个数组把所有用过的花盆的情况都存着，不过用两个变量 $st$ 和 $ed$，表示这个数组下标为 $st \sim ed$ 的这一段才是现在真正存在的花盆就行啦！好啦，这不就解决了么？

最后献上考场时一字未改的[提交记录](https://atcoder.jp/contests/abc379/submissions/59603410)，可以在里边查看 AC 代码哟~

如果你觉得这篇题解对你有帮助的话，请点一个赞，谢谢！

---

## 作者：hjyowl (赞：2)

### 题目大意

你需要维护一个数据结构，支持以下操作：

```1``` 增加一个新的数，初始为 $0$。

```2 x``` 对于所有数，增加 $x$。

```3 x``` 求出大于等于 $x$ 的数的个数并且删除掉。

### 思路

暴力肯定是不行的。

考虑使用一个可重集维护。

但是对于集体修改时间复杂度还是会很高。

于是我们思考一下，定义一个时间戳变量 $T$，每次增加一个新的数时不插入 $0$ 而插入 $-T$，对于每一次查询，我们只需要查询大于等于 $x$ 减当前的时间戳 $T$，这个操作直接通过二分即可。然后二分得到了迭代器再删除即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	multiset<long long>s;
	long long q;
	cin >> q;
	long long TIME = 0;
	while (q -- ){
		long long op;
		cin >> op;
		if (op == 1){
			s.insert(-TIME);
		}
		else if (op == 2){
			long long T;
			cin >> T;
			TIME += T;
		}
		else{
			long long H;
			cin >> H;
			auto t = s.lower_bound(H - TIME);
			long long res = 0;
			auto cc = t;
			for (; cc != s.end(); cc ++ ){
				res ++ ;
			}
			cout << res << endl;
			s.erase(t,s.end());
			
		}
	}
	return 0;
}
```

---

## 作者：sh1kong (赞：2)

[In Luogu](https://www.luogu.com.cn/problem/AT_abc379_d)

D < C。建议橙。

这种套路的题还是挺多的。

考虑维护一个小根堆，里面存每个盆栽栽入的时间。

再维护一个全局时间 $t$。

那么操作 $1,2$ 直接按照上面维护就好了。

对于操作 $3$，不断取出那些满足当前时间 $t$ 减去堆顶栽入时间 $tp \ge H$ 的堆顶。答案即为取出的次数。这样均摊是 $\mathcal{O(Q \log Q)}$ 的。那么就做完了。

赛时码风良好代码：[Link](https://atcoder.jp/contests/abc379/submissions/59598230)

---

## 作者：xiaozhangawa (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc379_d) | [原题传送门](https://atcoder.jp/contests/abc379/tasks/abc379_d)

## 题目大意

有一个长度为 $10^{100}$ 的容器、 $q$ 次操作（$q\leq 2\times 10^5$），每次操作可能为以下 $3$ 种：

- `1` 往容器里丢一个数，初始值为 $0$。
- `2 T` 将容器里所有的数增加 $T$。
- `3 H` 将容器里所有 $\geq H$ 的数取出，并输出取出数的个数。

## 思路

首先大家不要被题目中的 $10^{100}$ 吓到，因为 $q\leq2\times10^5$，并且每次操作至多增加 $1$ 个数，所以总共至多有 $q$ 个数。

然后我们从问题入手，先分析操作 $3$。注意到 $\geq H$ 的数一定是这个数列中最大的若干个数，因此我们需要一个能够维护有序序列的数据结构，自然就能想到优先队列。

操作 $1$ 我相信大家都会，那么我们开始分析操作 $2$。操作 $2$ 需要把每个数都增加 $T$，如果暴力的话，单次时间复杂度为 $\mathcal O(n\log n)$（$n$ 为目前优先队列中的元素数），显然太慢了。但是这个操作是对**每个数**进行增加，很自然的就能想到使用一个变量 $t$ 来记录增量，每次操作 $2$ 就把 $t$ 增加 $T$ 就好了。那么如果要取到数列中的真实值，就应该用该数 $+t$。

此时，我们的操作 $1$ 也应该修改一下，并不是插入 $0$，而是插入 $0-t=-t$。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
priority_queue<ll> q;//优先队列
int main(){
	int Q;
	ll T=0;//增量
	cin>>Q;
	while(Q--){
		int op;
		cin>>op;
		if(op == 1) q.push(-T);//操作1
		else if(op == 2){//操作2
			int t;
			cin>>t;
			T+=t;
		}else if(op == 3){//操作3
			int ans = 0,h;
			cin>>h;
			while(!q.empty() && q.top()+T >= h){//一定要判空，不然会RE
				ans++;
				q.pop();
			}
			cout<<ans<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Anins (赞：2)

## [[ABC379D] Home Garden](https://www.luogu.com.cn/problem/AT_abc379_d)

### 题意：

开始有一个空集，有 $Q$ 次操作，每次有标识数 $op$：

1. 若 $op$ 为 $1$：为集合添加一个元素 $0$。
2. 若 $op$ 为 $2$：输入 $T$，为集合内所有元素增加 $T$。
3. 若 $op$ 为 $3$：输入 $H$，删除集合内不小于 $H$ 的元素，并输出删除元素个数。

#### 数据范围：$1 \leq Q \leq 2 \times 10^{5}$，$1 \leq T,H \leq 10^{9}$

### 思路：

因为题中有多元素修改操作，所以我使用线段树统计区间加来实现。

设变量 $l$ 和 $r$ 表示未被删除的元素集合的在线段树内的位置。

我们发现 $1 \leq Q \leq 2 \times 10^{5}$，直接用线段树根节点表示 $1$ 到 $2 \times 10^{5}$ 这个区间。

- 对于操作 $1$：直接令 $r$ 加一即可。
- 对于操作 $2$：线段树对区间 $l$ 和 $r$ 加 $T$。
- 对于操作 $3$：我们发现未删集合在在 $l$ 到 $r$ 内内单调不增，那么考虑二分找出在 $l$ 到 $r$ 内第一个小于 $H$ 的元素位置，设它为 $L$，那么答案就是 $L-l$，输出后将 $l$ 赋值为 $L$ 即可更新未删集合。

### 代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct tree {
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	#define mid ((l+r)>>1)
	ll add[800005];
	void push_down(ll k) {
		if(!add[k]) return;
		add[ls]+=add[k];
		add[rs]+=add[k];
		add[k]=0;
	}
	void solve(ll k, ll l, ll r, ll L, ll R, ll op) {
		if(L<=l&&r<=R) {
			add[k]+=op;
			return;
		}
		push_down(k);
		if(L<=mid) solve(ls, l, mid, L, R, op);
		if(R>mid) solve(rs, mid+1, r, L, R, op);
	}
	ll query(ll k, ll l, ll r, ll op) {
		if(l==r) return add[k];
		push_down(k);
		if(op<=mid) return query(ls, l, mid, op);
		else return query(rs, mid+1, r, op);
	}
}sg;
int main() {
	ll Q, T, H, l=1, r=0, op;
	cin >> Q;
	while(Q--) {
		cin >> op;
		if(op==1) r++;
		else if(op==2) {
			cin >> T;
			if(l<=r) sg.solve(1, 1, 200000, l, r, T); //注意判断是否是空集 
		} else if(op==3) {
			cin >> H;
			//使用二分找出l-r内第一个小于H的元素位置，若都不小于H那么l将会更新为r+1合题意 
			ll L=l, R=r, Mid;
			while(L<=R) {
				Mid=(L+R)/2;
				if(sg.query(1, 1, 200000, Mid)>=H) L=Mid+1;
				else R=Mid-1;
			}
			cout << L-l << endl;
			l=L; //更新未删集合 
		}
	}
	return 0;
}
```

---

## 作者：zhangjiting (赞：2)

## 思路

虽然花盆数很大，但并没有用，因为 $q$ 很小。

记录 $l$ 和 $r$，表示数组上 $l$ 到 $r$ 这一段是种了花的，且 $l$ 上的花最先种下。

对于操作一，令 $r$ 等于 $r+1$；

对于操作二，在 $l$ 到 $r$ 上区间加。

对于操作三，由于下标越小的位置高度越大，所以可以二分。

区间加和单点查询使用树状数组就可以实现，时间复杂度为 $O(q\log^2q)$。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cerr<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6+5;
int q;
int t[N];
int lowbit(int x){
	return x&(-x);
}
void add(int x,int v){
	for(;x<=2e5;x+=lowbit(x)) t[x]+=v;
}
int ask(int x){
	int res=0;
	for(;x;x-=lowbit(x)) res+=t[x];
	return res;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	IOS;
	cin>>q;
	int tl=1,tr=0;
	while(q--){
		int op,x;
		cin>>op;
		if(op==1) tr++;
		if(op==2){
			cin>>x;
			add(tl,x);
			add(tr+1,-x);
		}
		if(op==3){
			cin>>x;
			int l=tl,r=tr,res=tl-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(ask(mid)>=x) res=mid,l=mid+1;
				else r=mid-1;
			}
			cout<<res-tl+1<<endl;
			tl=res+1;
		}
	}
	return 0;
}

```

---

## 作者：crz_qwq (赞：1)

明显的平衡树题，于是用平衡树水过去了。

我们维护一个增量 $t$，则树中元素真正的值皆为 $x_i+t$，其中 $x_i$ 是树中存的数 遇到 $1$ 操作时，我们对平衡树插入 $-t$，遇到第 $2$ 种操作时，$t$ 加上 $T$，遇到第 $3$ 种操作时，删去 $x_i \ge H-t-1$ 的所有 $i$ 并且统计。

时间复杂度 $O(Q\log Q)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
mt19937 rng(time(0));
int root,tot;
struct node{
	int val,pri,ls,rs,sz;
}tr[N];
int New(int x)
{
	++tot;
	tr[tot].val=x;
	tr[tot].pri=rng();
	tr[tot].ls=tr[tot].rs=0;
	tr[tot].sz=1;
	return tot;
}
void pushup(int p){tr[p].sz=tr[tr[p].ls].sz+tr[tr[p].rs].sz+1;}
void split(int p,int x,int &L,int &R)
{
	if(!p)
	{
		L=R=0;
		return ;
	}
	if(tr[p].val<=x)
	{
		L=p;
		split(tr[p].rs,x,tr[p].rs,R);
	}
	else
	{
		R=p;
		split(tr[p].ls,x,L,tr[p].ls);
	}
	pushup(p);
}
int merge(int L,int R)
{
	if(!L||!R)
		return L|R;
	if(tr[L].pri<=tr[R].pri)
	{
		tr[L].rs=merge(tr[L].rs,R);
		pushup(L);
		return L;
	}
	tr[R].ls=merge(L,tr[R].ls);
	pushup(R);
	return R;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int q,t=0;
	cin>>q;
	while(q--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int L,R;
			split(root,-t,L,R);
			root=merge(merge(L,New(-t)),R);
		}
		if(op==2)
		{
			int x;
			cin>>x;
			t+=x;
		}
		if(op==3)
		{
			int x,L,R;
			cin>>x;
			split(root,x-t-1,L,R);
			cout<<tr[R].sz<<'\n';
			root=L;
		}
	}
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

考虑使用 `set` 维护所有的植物高度，令 $sum$ 为全局加的标记。

则操作 $1$ 时，应该插入 $-sum$；操作二令 $sum \gets sum + T$。

由于总插入数量是 $O(q)$ 级别的，那么有效删除数量也是 $O(q)$ 级别的，直接暴力从大到小遍历 `set`，若 $v + sum \ge H$ 就删除。

时间复杂度为 $O(q \log q)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll q, op, x, sum, ans;
multiset<ll> S;
bool End;
int main(){
	q = read();
	while(q--){
		op = read();
		if(op == 1)
		  S.insert(-sum);
		else if(op == 2){
			x = read();
			sum += x;
		}
		else{
			ans = 0;
			x = read();
			while(!S.empty()){
				auto it = S.end();
				--it;
				if((*it) + sum >= x){
					S.erase(it);
					++ans;
				}
				else
				  break;
			}
			write(ans);
			putchar('\n');
		}
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Tairitempest (赞：1)

## 题意简析
给出三种操作，操作 1 是在添加一个高度为 $0$ 的植物，操作 2 是让所有植物生长相同的高度 $T$，操作 3 是移除所有高度大于等于 $H$ 的植物，统计被移除的植物的数量并输出。
## 解法说明
注意到操作 2 中会让所有植物生长相同的高度，因此可以取一个变量 $tag$ 来维护目前等待的总天数，而非暴力修改高度值。那么后来要添加植物了怎么办？对于后来种下的植物，其高度就是后来等待的天数，等价于目前 $tag$ 的值减去它被种下时 $tag$ 的值。

同时，我们也可以发现后面的植物的高度是永远不会比前面的植物的高度要高的，因为前面的植物会比它多生长一段时间，也就是说，植物的高度有单调递减性，一个植物的高度如果不高于 $H$，那么后面所有的元素都不会高于 $H$。

因此该题可以使用以下解决方法：用队列维护这个植物被种下的植物时的 $tag_i$，每个植物的高度就是当前的 $tag$ 减去记录时的 $tag_i$。种下植物时将当时的 $tag$ 入队，等待则将 $tag$ 加上 $T$。这样的话，每个植物种下和变高都可以 $O(1)$ 实现。每出现操作 3 的时候，就检查队首元素并移除该元素直到队首植物的高度小于 $H$ 或者队列为空，同时统计被移除的元素的数量并输出。这样的话就可以 $O(Q)$ 解决该题。

以下是本人代码，写的不是很好看，但是可以参考一下。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll Q,T,H,type,tag;
queue<ll> q;
int main(){
	cin>>Q;
	while(Q--){
		cin>>type;
		if(type==1){
			q.push(tag);
		}else if(type==2){
			cin>>T;
			tag+=T;
		}else{
			ll ans=0;
			cin>>H;
			while(tag-q.front()>=H&&not q.empty()){
				ans++;
				q.pop();
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Ad_lqz_ht (赞：1)

## 前言
线段树二分！
## 题意
有 $q$ 次操作。
1. 新建一个空节点。
2. 将所有节点权值加 $t$。
3. 查询有多少权值大于或等于 $h$ 的节点，并删除这些节点。

对于样例
```
6
1
2 15
1
3 10
2 20
3 20
```
第一步，我们新建一个节点，权值为 $0$。
![](https://www.luogu.com.cn/api/team/downloadFile/jfqs8tmb)  
第二步，将所有节点权值加上 $15$。
![](https://www.luogu.com.cn/api/team/downloadFile/g5je4bzu)  
第三步，再新建一个权值为 $0$ 的节点。
![](https://www.luogu.com.cn/api/team/downloadFile/jeot17ub)  
第四步，一共只有一个节点的权值大于或等于 $10$，删除节点 $1$，输出 $1$。
![](https://www.luogu.com.cn/api/team/downloadFile/ncj3thd7)  
第五步，将所有节点权值加上 $20$。
![](https://www.luogu.com.cn/api/team/downloadFile/lx1c1uq1)  
第六步，有一个节点的权值大于或等于 $20$，删除这个节点，输出 $1$。
![](https://www.luogu.com.cn/api/team/downloadFile/g5a82qx7)  
## 思路
显然，我们可以使用一个队列来维护这个，因为操作二保证了队列里的点的单调性，所以每个点只会进出队列一次，每次操作均摊下来的时间复杂度是 $\Omicron(1)$，总时间复杂度是 $\Omicron(n)$，可以通过，可以参考[官方题解](https://atcoder.jp/contests/abc379/editorial/11330)。

但是，如果这道题就这么结束了，那也未免太过无趣了一些。因此，受数据结构的熏陶，在看到了操作二后，我们可以想到使用线段树进行区间加，对于操作三，我们可以进行线段树二分。

但是这个时候你发现了一个问题，普通的线段树不好维护删除点的操作，但是好在删除的点不会影响后面的操作，所以我们可以不管他。但是不管他的话也会出现一个问题，我们在进行线段树二分的时候区间就不满足单调性了，所以我们可以对所有点一块进行区间加，但是在统计答案的时候去除掉这部分被删除的点。

这样，第五步就变成了这样。
![](https://www.luogu.com.cn/api/team/downloadFile/bnu49hdy)

而之所以这样保证了单调性是因为旧的点加的次数一定大于或等于新来的点，加给新来的点的值也给了旧的点，但是旧的点的值没有给新来的点，因此，点的权值是单调不升的。

还有一个问题就是在进行操作一的时候怎么去新建一个空的节点，这对线段树来说十分困难。但是显然我们新节点的个数不可能超过操作数 $q$，所以我们可以直接在建树和计算的过程中将区间范围设为 $1 \sim q$，对于一操作，让节点数加一，用来进行二操作的加法。

解决了线段树维护操作一和二的问题，还有一个操作三。
对于操作三来说，操作二已经保证了区间单调，可以进行线段树二分。

线段树二分适用于少部分满足区间单调性的问题上。具体的来说，如果我想要知道权值大于或等于 $h$ 的点有多少个，我们可以先求出最小的大于或等于 $h$ 的点的位置，然后再用位置减去删除的点的数量，剩下的就是答案。

我们可以发现，如果某个节点的右孩子的最大值要大于这个权值，那么第一个大于等于 $h$ 的点一定在右孩子那边，否则在左孩子那边。

操作一的时间复杂度是 $\Omicron(1)$ 的，操作二和三的时间复杂度都是 $\Omicron(\log n)$ 的，$n$ 是节点数。因此，总时间复杂度为 $\Omicron(q \log n)$ 的，可以通过。
## 代码
大体思路就是这个样子，一个区间加和维护区间最大值的线段树。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//一定要开long long
const int N = 200005;
int n, tot = 1, cnt, las;
//cnt是节点数量，las是有多少被删除。
struct tree
{
    int ls, rs;
    int val, tag;
} tr[N << 1];//线段树
inline void newnode(int &x) { x = ++tot; return; };//动态开点
inline void pushup(int rt)
{
    tr[rt].val = 0;
    if (tr[rt].ls) tr[rt].val = max(tr[rt].val, tr[tr[rt].ls].val);
    if (tr[rt].rs) tr[rt].val = max(tr[rt].val, tr[tr[rt].rs].val);
    return;
}//区间最大值
inline void pushdown(int rt)
{
    if (!tr[rt].tag) return;
    if (!tr[rt].ls) newnode(tr[rt].ls);
    if (!tr[rt].rs) newnode(tr[rt].rs);
    tr[tr[rt].ls].val += tr[rt].tag;
    tr[tr[rt].rs].val += tr[rt].tag;
    tr[tr[rt].ls].tag += tr[rt].tag;
    tr[tr[rt].rs].tag += tr[rt].tag;
    tr[rt].tag = 0; return;
}//下传懒标记
void update(int rt, int nl, int nr, int ql, int qr, int k)
{
    if (ql <= nl && nr <= qr)
    {
        tr[rt].val += k;
        tr[rt].tag += k;
        return;
    }
    pushdown(rt); int mid = (nl + nr) >> 1;
    if (!tr[rt].ls) newnode(tr[rt].ls);
    if (!tr[rt].rs) newnode(tr[rt].rs);
    if (ql <= mid) update(tr[rt].ls, nl, mid, ql, qr, k);
    if (qr > mid) update(tr[rt].rs, mid + 1, nr, ql, qr, k);
    return pushup(rt);
}//区间加
int query(int rt, int nl, int nr, int val)
{
    if (nl == nr) return tr[rt].val >= val ? nl : las;//走到叶子节点，判断是否符合条件
    pushdown(rt); int mid = (nl + nr) >> 1, res = las;
    if (tr[rt].rs && tr[tr[rt].rs].val >= val)
		res = max(res, query(tr[rt].rs, mid + 1, nr, val));//右孩子的最大值大于val
    else if (tr[rt].ls && tr[tr[rt].ls].val >= val)
		res = max(res, query(tr[rt].ls, nl, mid, val));//否则从左孩子走
    return res;
}//线段树二分
signed main()
{
    cin.tie(0) -> ios::sync_with_stdio(false);
    int opt, x;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> opt;
        if (opt == 1) ++cnt;//节点数加一
        else cin >> x;
        if (opt == 2 && cnt) update(1, 1, n, 1, cnt, x);//有节点再更新，防止越界，每次操作要给1到cnt每个节点加。
        if (opt == 3)
        {
            int tmp = query(1, 1, n, x);//第一个大于或等于x的位置。
            cout << max(0ll, tmp - las) << '\n';//减去被删除的。
            las = max(las, tmp);//到第一个大于等于的位置全部被删除。
        }
    }
    return 0;
}
```
## 写在后面
线段树二分比较偏向模板的题还有[这个](https://www.luogu.com.cn/problem/P11217)，大家可以自己写一写试一试。

---

## 作者：CaoSheng_zzz (赞：1)

假设每个花都有种植时间节点，那么时间节点越小的花的高度一定大于时间节点大的高度。

那么我们需要维护每朵花的时间节点和高度，不难发现有很多时间节点相同的花，由于相同时间节点的花高度相同所以我们可以维护当前时间节点有多少花和当前时间节点花的高度。

因为二操作是区间加法，而三操作由于我们通过时间储存可以二分去做所以不难想到用线段树解决我们需要维护的东西。

**总结：线段树板子** 。

Code：
```cpp
#define ls k << 1
#define rs k << 1 | 1
#define int long long

const int maxn = 2e5 + 1;
struct SegTree {
    int l, r ;
    int val ;
    int num ;
    int lazy ;
} tree[maxn << 2] ;
int id = 1, cnt = 0, ct ;
bool flag = false ;

void push_up(int k) { tree[k].num = tree[ls].num + tree[rs].num ; tree[k].val = max(tree[ls].val, tree[rs].val) ;}
void push_down(int k) { 
    if(! tree[k].lazy) return ;
    tree[ls].lazy += tree[k].lazy ;
    tree[rs].lazy += tree[k].lazy ;
    tree[ls].val += tree[k].lazy ;
    tree[rs].val += tree[k].lazy ;
    tree[k].lazy = 0 ;
    return ;
}

void build(int k, int l, int r) {
    tree[k].l = l, tree[k].r = r ;
    if(l == r) return ;
    int mid = l + r >> 1 ;
    build(ls, l, mid), build(rs, mid + 1, r) ;
    push_up(k) ;
}

void Add(int k, int l, int r, int num) {
    if(tree[k].l > r || tree[k].r < l) return ;
    if(tree[k].l == tree[k].r) {
        tree[k].num = num ;
        return ;
    }
    Add(ls, l, r, num), Add(rs, l, r, num) ;
    push_up(k) ;
}

void Change(int k, int l, int r, int val) {
    if(tree[k].l > r || tree[k].r < l) return ;
    if(l <= tree[k].l && tree[k].r <= r) {
        tree[k].lazy += val ;
        tree[k].val += val ;
        return ;
    }
    push_down(k) ;
    Change(ls, l, r, val), Change(rs, l, r, val) ;
    push_up(k) ;
}

std::pair<int, int> Ask(int k, int num) {
    push_down(k) ;
    if(tree[k].val < num) return {0, 0} ;
    if(tree[k].r < id) return {0, 0} ;
    if(tree[k].l == tree[k].r) return {tree[k].num, tree[k].r} ;
    std::pair<int, int> l = Ask(ls, num), r = Ask(rs, num) ;
    return {l.first + r.first, max(l.second, r.second)} ;
}

signed main() {
    int n = read() ;
    build(1, 1, n) ;
    while(n --) {
        int opt = read() ;
        if(opt == 1) {
            if(! flag) flag = true, ++ cnt, ++ ct ;
            else ++ ct ;
        }
        else {
            if(flag) flag = false, Add(1, cnt, cnt, ct), ct = 0 ;
            if(opt == 2) {
                int val = read() ;
                Change(1, id, cnt, val) ;
            }
            else {
                int num = read() ;
                auto x = Ask(1, num) ;
                output(x.first), ent ;
                id = max(x.second + 1, id) ;
            }
        }
    }
    return 0 ;
}
```

---

## 作者：Cosine_Func (赞：1)

赛时调了四十分钟的水题。

简化版题面：
有 $Q$ 个查询，请按顺序处理。
查询有以下三种类型。

- `1`：在数列末尾添加一个 $0$。
- `2 T`：将数列中的所有数加上 $T$。
- `3 H`：删除数列中所有大于或等于 $H$ 的数，并输出删除的数的个数。

显然，这个数列具有单调不升的性质，因此在执行操作三时，可以二分找到删除的位置。至于操作二，显然是区间修改单点查询，因此可以使用树状数组维护。时间复杂度 $O(Q\times \log ^2 Q)$，我的赛时代码因为某些细节问题理论上可以被卡到 $O(Q^2)$，但由于本题的特殊性，很难构造出 hack 数据。

参考代码：

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define endl '\n'
#define itn int
#define pi pair<int,int>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define int ll
using namespace std;
const int MOD1=1e9+7;
const int MOD2=998244353;
const int N=2e5+5;
int q,op,t,h,head,tail,a[N],tree[N];
int lowbit(itn x){
	return x&(-x);
}
void add(itn x,itn k){
	for(int i=x;i<=2e5;i+=lowbit(i))
		tree[i]+=k;
}
int ask(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=tree[i];
	return res;
}
inline void Solve(){
	cin>>q;
	head=1,tail=0;
	while(q--){
		cin>>op;
		if(op==1){
			tail++;
		}
		if(op==2){
			cin>>t;
			add(head,t);
			add(tail+1,-t);
		}
		if(op==3){
			cin>>h;
			int l=head,r=tail;
			while(l<=r){
				int mid=l+(r-l)/2;
				if(ask(mid)>=h)l=mid+1;
				else r=mid-1;
			}
			while(ask(r+1)>=h and r<tail)r++;
			cout<<r-head+1<<endl;
			head=r+1;
		}
	}
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int T=1;
    //cin>>T;
    while(T--)
    	Solve();
    return 0;
}


```

---

## 作者：Hacker_Cracker (赞：0)

## [ABC379D] Home Garden 题解
### Solution
首先 $O(Q^2)$ 的暴力模拟解法是很容易实现出的。这里的瓶颈主要在于操作 $3$ 中的删除操作。这里我们需要输出所有 $\ge x$ 的植物高度。那什么可以快速维护一个从大到小的，长度不定的序列呢？

**优先队列**。

于是整个操作过程就明了了：

- 首先维护一个变量 $h$，来记录当前所有花的最高高度。
- 对于操作一：由于当前的最高高度为 $h$，目前植物高度为 $0$，那么我们就往优先队列里放进去一个高度为 $-h$ 的植物。
- 对于操作二：直接使 $h \gets h+T$ 即可。
- 对于操作三：一直向外弹出队首元素 $X$，统计个数，直到 $h+X<H$ 即可。

这样就完成了。

### 注意事项
- 不开 long long 见祖宗。
- 优先队列是大根堆。

### [AC](https://www.luogu.com.cn/record/187840468) Code
```cpp
#include<iostream>
#include<queue>
#define ll long long
using namespace std;
priority_queue<ll>q;
int Q,op;
ll t,h,tot_h,tp,ans;
int main(){
	cin>>Q;
	for(;Q;Q--){
		cin>>op;
		if(op==1){
			q.push(-tot_h);
		}else if(op==2){
			cin>>t;
			tot_h+=t;
		}else{
			cin>>h;
			ans=0;
			while(!q.empty()){
				tp=q.top();
				if(tot_h+tp>=h){
					ans++;
					q.pop();
				}else{
					break;
				}
			}
			cout<<ans<<endl; 
		}
	}
	return 0;
}
```

---

## 作者：Dtw_ (赞：0)

# 题意
* $1$ 新建一个节点。
* $2,x$ 将已有的所有节点全加上 $x$。
* $3,x$ 求目前节点值 $\ge x$ 的点的数量，然后将这些点都删掉。
# Solution

首先考虑对于第 $i$ 个询问，我们可以把之前的 $2$ 单独拿出来，然后就是求一段区间使得他的和 $\ge x$，假设这段区间为 $[l, r]$ 那么在 $l$ 之前的 $1$ 操作都是符合要求的。所以我们用前缀和维护所有的 $2$ 操作，然后直接二分一个 $mid$ 使得 $[mid, i]$ 这一段的和 $\ge x$，那 $mid$ 之前的 $1$ 操作就全符合要求，此时我们可以继续向后尝试。

我写的可能比较麻烦，就是把 $2$ 单独存起来，然后在单独存的数组上进行二分。同时因为每次询问完后满足要求的点全会删掉，所以记录一个 $l$，表示 $l$ 往上的都不行了。

然后就做完了。
# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n' 

#define int long long

#define pii pair<int, int>

#define fi first
#define se second

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int inf = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n, m;

int cnt[N];

pii s[N];

int f(int x) // 找第一个 >= x 的 2 操作在单独存的数组中的下标
{
    int l = 1, r = m, res = m + 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (s[mid].se >= x)
        {
            r = mid - 1;
            res = mid;
        }
        else l = mid + 1;
    }
    return res;
}

signed main()
{
    fst
    cin >> n;
    int l = 1;
    for (int i = 1; i <= n; i++)
    {
        cnt[i] = cnt[i - 1]; // 1 的个数
        int op, x;
        cin >> op;
        if (op != 1) cin >> x;
        if (op == 1) cnt[i]++;
        if (op == 2) s[m + 1].fi = s[m].fi + x, s[m + 1].se = i, m++; // fi 表示值，se 表示在真正数组上的下标
        if (op == 3)
        {
            int ll = f(l), r = m, res = 0;
            // cout << "ll : " << ll << endl;
            while (ll <= r)
            {
                int mid = (ll + r) / 2;
                if (s[m].fi - s[mid - 1].fi >= x)
                {
                    res = s[mid].se;
                    ll = mid + 1;
                }
                else r = mid - 1;
            }
            // cout << "we find " << res << endl;
            if (res < l) cout << 0 << endl;
            else cout << cnt[res] - cnt[l - 1] << endl, l = res + 1;
        }
    }
    return 0;
}
```

---

## 作者：OIer_Tan (赞：0)

简单小做法，当乐子看看得了。

## 题意

高桥有 $10^{100}$ 个花盆。最初，他没有种植任何植物。

给您 $Q$ 个查询，请按顺序处理。

查询有以下三种类型。

- `1`：准备一个空花盆并放入一株植物。这里，植物的高度是 $0$。
- `2 T`：等待 $T$ 天。在此期间，现有植物的高度会增加 $T$。
- `3 H`：收获所有高度至少达到 $H$ 的植株，并输出收获植株的数量。收获的植物会从花盆中移出。

假设执行第一类和第三类查询所需的时间为零。

## 思路

由于我懒，并不想维护全局加还带删除的数据结构（指树套树），所以我考虑直接记录当前的时间 $t$，并用 `multiset` 维护当前拥有的花盆，加入的时候就将种植的时间丢进去，收获的时候就二分 $t-H$ 的位置然后删除，输出前后大小之差即可。

复杂度保证是因为每个花最多只会被加入然后删掉一次，所以复杂度是 $O(Q\log Q)$ 的。

不用 `set` 的原因是同一时间可能种多盆花。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll q ;

multiset <ll> s ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> q ;
	ll now = 0 ;
	while ( q -- )
	{
		ll opt ;
		cin >> opt ;
		if ( opt == 1 )
		{
			s.insert ( now ) ;
		}
		else if ( opt == 2 )
		{
			ll t ;
			cin >> t ;
			now += t ;
		}
		else 
		{
			ll h ;
			cin >> h ;
			ll tmp = now - h ;
			auto it = s.upper_bound ( tmp ) ;
			ll siz = s.size () ;
			s.erase ( s.begin () , it ) ;
			siz -= s.size () ;
			cout << siz << endl ;
		}
//		cout << now << "#" ;
//		for ( auto x : s )
//		{
//			cout << x << " " ;
//		}
//		cout << endl ;
	}
	return 0 ;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

## 赛时思路

我们想象一下，操作 $2$ 可以暴力把所有的植物都升高 $T$，最后输出时把所有植物搜一遍。这样的最坏复杂度为：$O(4\times10^{10})$。最后 TLE 了三个点。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=2e5+5;
struct node{
	long long time;
	bool flag;
};
vector<node>v;
int main(){
	int Q;
	cin>>Q;
	while(Q--){
		int op;
		cin>>op;
		if(op==1){
			v.push_back({0,0});
		}
		else if(op==2){
			int t;
			cin>>t;
			for(auto i=v.begin();i!=v.end();i++){
				i->time+=t;
			}
		}
		else{
			int q;
			cin>>q;
			int cnt=0;
			for(auto i=v.begin();i!=v.end();i++){
				if(i->time>=q&&i->flag==0){
					i->flag=1;
					cnt++;
				}
			}
			cout<<cnt<<endl;
		}
	}
	return 0;
} 
```

### 优化

这个代码最大的缺点就是每一次操作 $2$ 和 $3$ 都要全部搜索一遍，浪费时间复杂度，我们为何不把操作 $2$ 变成累计的计数器，并在最开始的操作 $1$ 记录这盆花放入花盆的时间。这样可以去掉一个循环，复杂度大概为 $O(Q)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  	int Q;
  	cin >> Q;
  	ll s = 0;
  	queue<ll> que;
  	while(Q--) {
    	int t;
	    cin >> t;
    	if(t == 1) {
    	 	que.push(s);//输入时别的植物已经长多高了
    	}else if(t == 2) {
      		ll T; cin >> T;
      		s += T;
    	}else {
      		int ans = 0;
      		ll H; cin >> H;
      		while(!que.empty() && s - que.front() >= H) ans++, que.pop();//优化重点！
      		cout << ans << endl;
    	}
  	}
}
```

---

