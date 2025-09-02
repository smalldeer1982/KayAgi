# [ABC214E] Packing Under Range Regulations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc214/tasks/abc214_e

$ T $ 個のテストケースについて、以下の問題を解いてください。

$ 1,2,\dots,10^9 $ の番号がついた $ 10^9 $ 個の箱と、 $ 1,2,\dots,N $ の番号がついた $ N $ 個のボールがあります。  
 それぞれの箱に入れることのできるボールの個数は多くとも $ 1 $ 個です。  
 以下の条件を満たすように、 $ N $ 個のボールを全て箱に入れることができるか判定してください。

- 全ての $ 1 $ 以上 $ N $ 以下の整数 $ i $ について、番号 $ i $ のボールが $ L_i $ 以上 $ R_i $ 以下の番号がついた箱に入っている。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ L_i\ \le\ R_i\ \le\ 10^9 $
- $ 1 $ つの入力に含まれるテストケースについて、それらの $ N $ の総和は $ 2\ \times\ 10^5 $ を超えない。

### Sample Explanation 1

この入力には $ 2 $ つのテストケースが含まれます。 - $ 1 $ つ目のテストケースについて、以下のようにボールを箱に入れると、問題文中の条件を満たすように $ 3 $ 個のボールを全て箱に入れることができるので、 `Yes` と出力します。 - ボール $ 1 $ を箱 $ 1 $ に入れる。 - ボール $ 2 $ を箱 $ 2 $ に入れる。 - ボール $ 3 $ を箱 $ 3 $ に入れる。 - $ 2 $ つ目のテストケースについて、問題文中の条件を満たすように $ 5 $ 個のボールを全て箱に入れることはできないので、 `No` と出力します。

## 样例 #1

### 输入

```
2
3
1 2
2 3
3 3
5
1 2
2 3
3 3
1 3
999999999 1000000000```

### 输出

```
Yes
No```

# 题解

## 作者：Nahida_Buer (赞：6)

# 题意
给出 $n$ 个小球，第 $i$ 个小球必须放在整数区间 $[L_i,R_i]$ 内。每个位置上只能放置一个小球，问是否有合法的放置方案。多组数据。
# 分析
先从贪心的角度考虑：
容易想到，我们应该先给区间短的小球安排位置，再给区间长的小球安排位置。并且一个小球的区间中一段与其他区间相交得很少，我们应该优先考虑把小球该小球放在这个区间中。

因此我们需要对小球区间从小到大进行排序，左端点为第一关键字，右端点为第二关键字。

然后开始分配每个小球的位置。

从简单的开始考虑，如果所有小球的左端点互异，那么把所有小球都放在其区间的左端点一定是合法的。

那如果有多个小球的左端点相同怎么办？很明显我们应把左端点的位置分配给右端点最小的小球，因为右端点更大的小球有更多的机会在后面找到位置。

# 算法思路
此刻我们就得到了一个朴素的算法：所有小球排序后，依次遍历每个小球，对于每个小球，找到所有与它左端点相同的小球，把左端点的位置让给右端点最小的小球。然后其余小球一律视为左端点向右移一个单位。如果有一个将要被右移的小球的左端点与右端点已经重合了，那么这个小球在最优解中无法找到分配位置，分配失败，输出 No。遍历完所有小球，说明所有小球都能找到相应位置，输出 Yes。

# 实现思路
排序后，用 $i$ 从 $[1,n]$ 遍历每个小球时，对于每个小球找到所有与它左端点相同的小球，设找到一团左端点相同为 $L_i$ 的小球在排序后的数组中对应的下标分别为 $i,i+1...,j-1$，那么第一个左端点大于它们的小球的下标就是 $j$ 设其左端点为 $L_j$。那么区间 $[L_i,L_j)$ 一定是这团小球的可分配区间。

用一个指针 $s$ 指向 $L_i$，然后按照右端点从小到大把这团小球依次分配在位置 $s$ 上（其实也就是按照排序顺序分配），每分配一个小球，就让 `s++`。直到所有小球都被分配完或者 `s==L[j]-1`，然后令 `i=j`，继续下一次遍历。

那么如果有剩下的小球怎么办？当然是当做与 $j$ 小球同左端点，继续下一次分配，因为这些小球的区间中，在 $j$ 小球左端点前面的位置已经全部被分配完了。

但是发现之前遍历遗留的小球与当次遍历的小球并不满足按照右端点从小到大排序。因此我们需要一个数据结构支持单点插入，最小值查询，以及最小值删除，这正是优先队列，也就是堆。

那么每次遍历将所有左端点相同的小球的右端点放入优先队列中，然后每次取出堆顶元素仍然按照上面的规则分配位置，分配结束条件是位置分完或者堆为空，而失败条件是堆顶元素小于要分配的位置 $s$。

综上，每个点最多入队并出队一次，加上最开始的排序，总时间复杂度就是$O(n\log n)$。

### 实现细节
用 C++ 自带的数对 `pair<int,int>` 排序，刚好满足按第一个元素为第一关键字，第二个元素为第二关键字从小到大排序。所以直接让左端点为第一个元素，右端点为第二个元素就好。比自建结构体，自己写比较函数方便多了。

C++ 默认优先队列为大根堆，也就是大的元素在堆顶，所以我们每次只要让相反数入队，取出时也取相反数就可以实现小根堆啦！

在排序后的数组最后加上一个左右端点均为无穷大的区间作为哨兵，可以免去很多特判。

最后送上本人最优解（现在变次优解了）的 AC 代码：

[评测记录](https://www.luogu.com.cn/record/200454497)

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
int read(){
	int x=0;char c=getchar();
	while(c>'9' || c<'0')c=getchar();
	while(c<='9' && c>='0'){x=(x<<3)+(x<<1)+c-48;c=getchar();}
	return x;
}
int T;
void solve(){
	int n=read();
	pair<int,int>p[n+5];
	for(int i=1;i<=n;i++){
		p[i].fi=read();
		p[i].se=read();
	}
	p[n+1].se=2e9;
	p[n+1].fi=2e9;
	sort(p+1,p+1+n);
	priority_queue<int>q;
	int i=1;
	while(i<=n){
		q.push(-p[i].se);
		int j=i+1,s=p[i].fi;
		while(p[j].fi==p[i].fi){
			q.push(-p[j].se);
			j++;
		}
		while(s<p[j].fi && !q.empty()){
			int v=-q.top();
			q.pop();
			if(s>v){
				puts("No");
				return ;
			}
			s++;
		}
		i=j;
	}
	puts("Yes");
	return ;
}
int main(){
	T=read();
	while(T--)solve();
}
```

---

## 作者：Rannio (赞：5)

提供一个非常好想也非常好写，但跑的贼慢的做法。

### 思路

先把每个能放球的区间看作线段，那我们的目的就是按顺序放球，同时给还未放的球留出尽可能多的位置。

那我们就可以按右端点升序排，右端点相同就按左端点降序排，然后对于每条线段，都尽量选择靠左的位置放球。这样既可以使还未放的球有尽量多的空间，又可以使可选位置较少的球先放，完美达成目的。

那如何找到最左侧的空位呢？我们可以使用一个树状数组维护一个位置上有没有放球，然后迭代寻找空位。

由于值域最大到达了 $10^9$，所以我们使用 `unordered_map` 代替数组来实现树状数组，时间复杂度为 $O(n \log^2 V \log n)$，其中 $V$ 为值域。

```C++
#include<bits/stdc++.h>
#define lb(x) x&-x
using namespace std;
#define typeOfReadAndWrite int
inline typeOfReadAndWrite read()
{
	typeOfReadAndWrite x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')f*=(ch=='-'?-1:1),ch=getchar();
	while(ch>=48&&ch<=57)x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
int T,n,k;
struct node{
    int x,y;
}a[200005];
unordered_map<int,int> tree;
void change(int x,int kk){for(int i=x;i<=k;i+=lb(i)) tree[i]+=kk;}
int query(int x){
    if(x==0) return 0;
    int res=0;
    for(int i=x;i;i-=lb(i)) res+=tree[i];
    return res;
}
bool cmp(node x,node y){
    return x.y==y.y?x.x>y.x:x.y<y.y;
}
bool check(int x,int l,int num){
    return query(x)-num<x-l+1;
}
signed main(){
    scanf("%d",&T);
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            a[i].x=read();
            a[i].y=read();
            k=max(k,a[i].y);
        }
        sort(a+1,a+n+1,cmp);
        bool fl=0;
        for(int i=1;i<=n;i++){
            int r=a[i].y,ll=query(a[i].x-1);
            if(query(r)-ll==r-a[i].x+1){
                fl=1;
                __builtin_printf("No\n");
                break;
            }
            while(1){
                int num=query(r)-ll;
                if(num==r-a[i].x+1) break;
                r=a[i].x+num-1; 
            }
            change(r+1,1);
        }
        if(!fl) __builtin_printf("Yes\n");
        tree.clear();
        k=0;
    }
    return 0;
}
```

---

## 作者：Katyusha_01 (赞：4)

鲁迅：*“一见到二分图匹配，立刻想到 hall 定理”*。

由 hall 定理可知：有合法方案的充要条件是

> 对于任意一个小球集合 $S$，对应的区间的并 $T$ 的大小 $|T|$ 必须大于等于集合 $S$ 的大小 $|S|$。

还可以注意到一点：

> 如果 $S_1,T_1$ 与 $S_2,T_2$ 均满足条件，且 $T_1,T_2$ 互不相交，那么 $S_1\cup S_2,T_1\cup T_2$ 一定满足条件(读者自证不难)。
> 
> 由此可知：对于一个不满足条件的 $S,T$，如果 $T$ 不是一段连续的区间，那么一定存在一个 $S,T$ 的子集不满足条件。
> 
所以我们只需要找到一个不满足条件的连续区间即可。

考虑扫描线，维护区间长度减区间小球个数的最小值，只要在过程中最小值始终不为负数即存在合法方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef struct{
	int mn,tag;
}Tree;
Tree t[1600011];
void push_up(int p)
{
	t[p].mn = min(t[p << 1].mn,t[p << 1 | 1].mn);
}
void Add(int p,int k)
{
	t[p].mn += k,t[p].tag += k; 
}
void push_down(int p)
{
	Add(p << 1,t[p].tag),Add(p << 1 | 1,t[p].tag),t[p].tag = 0;
}
void add(int p,int l,int r,int ll,int rr,int k)
{
	if(l <= ll && rr <= r)
		return Add(p,k);
	push_down(p);
	int mid = ll + rr >> 1;
	if(l <= mid)
		add(p << 1,l,r,ll,mid,k);
	if(mid < r)
		add(p << 1 | 1,l,r,mid + 1,rr,k);
	push_up(p);
}
struct{
	int l,r,k;
}a[200011];
int T;
int n;
map<int,int> d;
vector<pair<int,int> > v[400011];
int h[400011];
int b[400011];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> T;
	while(T--)
	{
		cin >> n;
		int id = 0;
		for(int i = 1;i <= n;i++)
		{
			cin >> a[i].l >> a[i].r,a[i].k = 1;
			b[++id] = a[i].l,b[++id] = a[i].r;
		}
		sort(b + 1,b + id + 1);
		int m = 0;
		for(int i = 1;i <= id;i++)
		{
			if(b[i] != b[i - 1])
				h[++m] = b[i];
			d[b[i]] = m;
		}
		for(int i = 1;i <= m;i++)
			v[i].clear();
		for(int i = 1;i <= n;i++)
			v[d[a[i].r]].push_back({d[a[i].l],a[i].k});
		for(int i = 1;i <= 4 * m;i++) t[i] = {0,0};
		bool flag = 1;
		for(int i = 1,x = 0;i <= m;i++)
		{
			if(i > 1)
				add(1,1,i - 1,1,m,h[i] - x);
			x = h[i];
			add(1,i,i,1,m,1);
			for(auto l:v[i])
				add(1,1,l.first,1,m,-l.second);
			if(t[1].mn < 0)
				flag = 0;
		}
		cout << (flag ? "Yes\n" : "No\n");
	}
	return 0;
}
```

---

## 作者：yhylivedream (赞：4)

提供一个时间较慢但不用脑子的并查集做法。

一个显然的贪心是将区间按右端点排序，对于每个区间找到区间内最左边的空位填球，这样才能使之后局面最优。

然后就转化成了并查集模板题，注意到值域有 $10^9$，开 map 即可。

时间复杂度 $n\log\log n$，一个来自 map，一个来自并查集路径压缩。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using Pii = pair<LL, LL>;

const LL kMaxN = 2e5 + 5;

LL T, n;
Pii a[kMaxN];
map<LL, LL> fa;

LL F(LL x) {
  !fa.count(x) && (fa[x] = x);//若没出现过就将父亲初始化为自己
  return fa[x] == x ? x : fa[x] = F(fa[x]);
}

signed main() {
  for (cin >> T; T--;) {
    cin >> n, fa.clear();
    for (LL i = 1; i <= n; i++) {
      cin >> a[i].second >> a[i].first;
    }
    bool fl = 1;
    sort(a + 1, a + n + 1);
    for (LL i = 1; i <= n; i++) {
      LL p = F(a[i].second);
      if (p > a[i].first) {
        fl = 0; break;
      }
      fa[p] = p + 1;
    }
    cout << (fl ? "Yes" : "No") << '\n';
  }
}
```

---

## 作者：GeorgeAAAADHD (赞：3)

## 题目大意：

有 $n$ 个球和 $10^9$ 个盒子，每次要在 $[l_i,r_i]$ 中的盒子放入一个球。每个盒子最多放一个球。求是否可以满足这些要求。多测。

## 算法分析：

容易发现贪心的思路。每次将一个球放入最左边能放入的位置，因此需要先按左端点进行升序排序。

然后我们维护指针 $l$，表示左端点的位置。并依次将 $r_i$ 入小根堆。其中我们还要判断最小的 $r_i$ 是否比 $l$ 还小。

之后再将堆清空。其中我们再判断最小的 $r_i$ 是否比 $l$ 还小。若堆空后还没有发生上面的情况则表示这种方案是可行的。

至此我们就完成了这道题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
struct node{
	int l,r;
	bool operator < (const node &a) const{
		return l<a.l;
	}
}a[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
		sort(a+1,a+n+1);
		priority_queue<int,vector<int>,greater<int>> p;
		int l=0,r=0,f=0;
		while(r<n){
			if(p.empty()){//初始时则先将第一个区间压入
				l=a[++r].l;
				p.push(a[r].r);
			}
			while(r<n&&a[r+1].l<=l)p.push(a[++r].r);
			if(p.top()<l){//若出现了右端点小于左端点的情况则退出循环
				f=1;p.pop();
				break;
			}
			l++;
			p.pop();
		} 
		if(f){
			cout<<"No\n";
			continue;
		}
		while(!p.empty()){
			if(p.top()<l){//同上
				f=1;
				break;
			}
			l++;
			p.pop();
		}
		if(f){
			cout<<"No\n";
			continue;
		}
		cout<<"Yes\n";
	}
	return 0;
} 
```

---

## 作者：lovely_qiqi (赞：2)

## 问题陈述
给你一些球以及它们应该在的区间，每个点只能放一个球，问能否放完。**（多测）**
## 思路

这题首先想到**贪心**：合理放法，放左边比放右边更好，因为这样可以给后面的留下更多位置。

但一个一个遍历肯定超时。

所以我们需要一个数据结构来维护，它需要满足以下特点：

- 能高效的找出最值（这样才能判断会不会无解）

- 能高效的加入数值（每个元素都要尝试加进来）

这就是**堆**！

用堆维护右端点最小值即可，详情见代码。
```
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
struct node{
	int l;
	int r;
}a[200010];
bool cmp(node t1,node t2){return t1.l<t2.l;}
priority_queue<int,vector<int>,greater<int>> h;
int t,n,al,now;
bool flag;
int main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		flag=false;//标记
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i].l>>a[i].r;
		sort(a+1,a+1+n,cmp);//按左端点升序排序，贪心
		al=0,now=0;//L
		while(h.size()) h.pop();////多测不清空，亲人两行泪
		while(now<n){//遍历
			if(h.empty()){//如果是空的就压进来，不然就是空的，无法进行之后的操作。
				al=a[++now].l;
				h.push(a[now].r);
			}
			while(now<n&&a[now+1].l<=al){//如果下一个在al之前，那无需更新，直接加入即可，但是最后可能将al遍历了，所以要+1
				h.push(a[++now].r);
			}
			if(h.top()<al){/如果当前右端点小于左端点，无解
				cout<<"No"<<endl;
				flag=true;
				break;
			}
			al++;
			h.pop();
		}
		if(flag==true) continue;
		while(!h.empty()){////如果里面还有没被处理的区间，那就按之前的方法处理即可。
			if(h.top()<al){
				cout<<"No"<<endl;
				flag=true;
				break;
			}
			al++;
			h.pop();//当前的处理完了，pop掉，不然可能干扰后续操作
		}
		if(flag==false) cout<<"Yes"<<endl;
	}
    return 0;
}
```

---

## 作者：_lfxxx_ (赞：2)

### 题目大意

有 $n$ 个球和 $10^9$ 个盒子，每个盒子最多一个球，接下有 $n$ 个 $l_i,r_i$，表示第 $i$ 个球要在 $[l_i,r_i]$ 的盒子中，问是否有合法方案。$T$ 组数据。

$1\le T,n,\sum n \le 2 \times 10^5,1 \le l_i \le r_i \le 10^9$。

### 思路

贪心。维护每个球目前能放到最左边哪个位置，每次把最小的拿出来（若相同，选右边小的）。感性理解一下，就是先把自己独特的位置占了，然后还要先满足严格条件。

首先按左端点排序，用 $l,r$ 指针维护哪些的区间左端点较小可以考虑放到最左边的位置，每次找到最小的右端点所在的区间放在位置 $l$，之后更新 $r$。

需要维护最小值，可以用小根堆维护这个过程，插入一个元素，弹出一个元素，很好写，时间复杂度 $O(n \log n)$。

### 代码
```cpp
    	for(int i=1;i<=n;++i)
    		cin>>a[i].l>>a[i].r;
    	sort(a+1,a+1+n,[](const seg&a,const seg&b){return a.l<b.l;});
    	r=0;
    	priority_queue<int,vector<int>,greater<int>>q;
    	while(r<n){
    		if(q.empty()){
    			l=a[++r].l;
    			q.emplace(a[r].r);
			}
   	 		while(r+1<=n&&a[r+1].l<=l)
   	 			q.emplace(a[++r].r);
   	 		if(q.top()<l++){
				cout<<"No\n";
				goto here;
			}
			q.pop();
		}
		while(!q.empty()){
			if(q.top()<l++){
				cout<<"No\n";
				goto here;
			}
			q.pop();
		}
		cout<<"Yes\n";
	here:;
```

---

## 作者：Federico2903 (赞：1)

## 思路
一个贪心，我们设 $i$ 为最靠前的能放球的位置，不断模拟即可。  
我们把原数列排序（这里是 `set`），并把这些区间的**右端点**依次压入优先队列，如果队头（最小的右端点）比 $i$ 小了，那么说明至少有一个球无法满足情况，输出 `No`，如果队列是空的，直接把 $i$ 跳到下一个左端点即可，用 `lower_bound`，最后如果队列没有完全清空，说明放不完，输出 `No`，否则就输出 `Yes`。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main() {
	cin >> t;
	for(int __=0;__<t;__++){
		int n;
		cin >> n;
		map<int,vector<int> > g;
		set<int> s;
		priority_queue<int, vector<int>, greater<int> > q;
		for (int i = 0; i < n; i++) {
			int u,v;
			cin >> u >> v;
			g[u].push_back(v);
			s.insert(u);
		}
		s.insert(INT_MAX);
		int i=*s.begin();
		bool flg=1;
		while(i<=1000000000){
			vector<int> temp=g[i];
			for(int j=0;j<temp.size();j++) q.push(temp[j]);
			q.pop();
			if(q.empty()) i=*s.lower_bound(i+1);
			else{
				if(q.top()<=i) {
					flg=0;break;
				}
				i++;
			}
		}
		if(flg && q.empty()) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}

```

---

## 作者：cjh_trailblazer (赞：0)

[原题面](https://www.luogu.com.cn/problem/AT_abc214_e)
## 题目分析：
注意到题目要求每一个球放在对应区间内，所以可以直观看出贪心策略：每个球尽量往左放，而右区间越小的越先往左放。  
所以需要动态判断每个球是否可放，需要动态维护放入球的右端点最小值，因此可以考虑对左端点排序后使用**优先队列**进行维护。

代码有注释。
## 代码如下：

```cpp
#include<bits/stdc++.h>
#define mihoyo freopen
#define starrail main
#define int long long
#define lowbit(x)  (x&(-x))
using namespace std;
inline int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T,n,now,ll;
bool f;
struct mm{
	int l,r;
	friend bool operator<(mm a,mm b){
		return a.l<b.l;//用于排序 
	}
} m[200010];
signed starrail()
{
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) m[i].l=read(),m[i].r=read();
		sort(m+1,m+1+n);//以左端点排序 
		priority_queue<int,vector<int>,greater<int>>q;//小根堆，优先队列 
		f=0,now=0,ll=0;
		while(now<n){//now 代表第几个球 
			if(q.empty()){//当前球处理完，再放入新球 
				ll=m[++now].l;//区间占到哪了 
				q.push(m[now].r);//每个球右端点进队 维护最小值 
			}
			while(now<n/*没放完*/&&m[now+1].l<=ll) q.push(m[++now].r);//假设可以放 
			if(q.top()<ll){//放不了 
				f=1;
				q.pop();
				break;
			}
			ll++;//当前球放好了，边界右移 
			q.pop();
			if(f){
				printf("No\n");
				break;
			}
		}
		while(!q.empty()){//已放入的球没处理完 
			if(q.top()<ll)	f=1;
			ll++;
			q.pop();
		}
		if(f){
			printf("No\n");
			continue;
		}
		printf("Yes\n");
	}
	return 0;
}
```

---

## 作者：StevenLiTheOIer (赞：0)

## 思路：
众所周知，把球放得越靠近左边，留给右边的空间就越多，所以越划算。维护左端点的位置 $l$ 并依次把右端点加入优先队列，然后开始出队。如果 $l>r_i$，那么 $i$ 明显是放不下的；反之，如果所有球都能顺利出队，就是有解的。

最后反复强调：注意多测，多测不清空，亲人两行泪。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200006;
struct node
{
	int l, r;
	bool operator < (const node &rhs) const
	{
		return l < rhs.l;
	}
};
node a[maxn];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i].l >> a[i].r;
		sort(a + 1, a + n + 1);
		priority_queue <int, vector <int>, greater <int> > q;
		int l = 0, r = 0;
		bool Exit = false;
		while (r < n)
		{
			if (q.empty())
			{
				l = a[++r].l;
				q.push(a[r].r);
			}
			while (r + 1 <= n && a[r + 1].l <= l) q.push(a[++r].r);
			if (q.top() < l++)
			{
				cout << "No" << endl;
				Exit = true;
			}
			q.pop();
			if (Exit) break;
		}
		if (Exit) continue;
		while (!q.empty())
		{
			if (q.top() < l++)
			{
				cout << "No" << endl;
				Exit = true;
			}
			q.pop();
			if (Exit) break;
		}
		if (Exit) continue;
		cout << "Yes" << endl;
	}
	return 0;
}
```

---

