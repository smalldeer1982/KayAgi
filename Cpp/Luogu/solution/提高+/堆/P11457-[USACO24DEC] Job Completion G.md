# [USACO24DEC] Job Completion G

## 题目描述

奶牛 Bessie 有 $N$（$1\le N\le 2\cdot 10^5$）个工作需要你去完成。第 $i$ 个工作，如果你选择完成它，必须在时刻 $s_i$ 或之前开始，花费 $t_i$ 时间才能完成（$0\le s_i\le 10^{18}, 1\le t_i\le 10^{18}$）。

你可以完成的工作的最大数量是多少？时间从时刻 $0$ 开始，并且一旦你开始一个工作，你必须一直工作直到完成，而不能在此期间开始完成其他工作。

## 说明/提示

对于第一个测试用例，你只能完成其中一个工作。在完成一个工作后，将会是时刻 $2$ 或更晚，因此已经太晚，无法开始另一个工作，必须要在时刻 $1$ 或更早才能开始。

对于第二个测试用例，你可以在时刻 $0$ 开始第二个工作并于时刻 $2$ 完成，然后在时刻 $2$ 开始第一个工作并于时刻 $5$ 完成。

- 测试点 $2$：同一个测试用例中的所有 $t_i$ 均相等。
- 测试点 $3\sim 4$：$N\le 2000$，$s_i, t_i\le 2000$。
- 测试点 $5\sim 8$：$N\le 2000$。
- 测试点 $9\sim 16$：没有额外限制。

## 样例 #1

### 输入

```
3
2
1 4
1 2
2
2 3
1 2
3
1 4
2 3
1 2```

### 输出

```
1
2
2```

# 题解

## 作者：Mr_Az (赞：8)

# P11457 [USACO24DEC] Job Completion G

### Algorithm:

反悔贪心。

### Solution:

如果不会的可以先去做 [[JSOI2007] 建筑抢修](https://www.luogu.com.cn/problem/P4053)。

考虑两个工作选择哪一个更优。设当前时刻为 $t$，当前有两个工作 $i,j$，且完成了 $i$ 不能完成 $j$，而完成了 $j$ 还可以完成 $i$。此时显然有先做 $j$ 再做 $i$ 更优。对应这种情况，变为表达式则有：

1. $t+t_i>s_j$。
2. $t+t_j \le s_i$。

解得此时 $s_i+t_i > s_j+t_j$。

所以我们只需要先将所有的工作按照 $s_i+t_i$ 从小到大进行排序，那么最终的操作顺序一定是这里的一段子序列。我们用反悔贪心去选择，记当前时间为 $now$：

1. 直接选择这个工作 $now \le s$，$now=t+s$;
2. 无法选择这个工作 $now > s$，如果之前完成的工作最长用时大于当前任务的 $t$，直接替换掉。

所有完成的工作只需要用大根堆存 $t$。

### Code:

```cpp
int T,n;	
pii a[N];
signed main(){
	read(T);
	while(T--){
		read(n);
		for(rint i=0;i<n;++i) read(a[i].first,a[i].second);
		sort(a,a+n,[](pii& a,pii& b){return (a.first+a.second)<(b.first+b.second);});
		priority_queue<int> q;
		int now=0,cnt=0;
		for(rint i=0;i<n;i++){
			auto [s,t]=a[i];
			if(now<=s){
				q.push(t);
				now+=t;
				cnt++;
			}//直接选择这工作
            else if(!q.empty()&&q.top()>t){
				now-=q.top();
				q.pop();
				q.push(t);
				now+=t;
			}//与之前的最长用时工作替换
		}
		cout<<cnt<<"\n";
	}
	return 0;
}
```

---

## 作者：zhuangzhihe (赞：4)

非常好的一道反悔自动机练习题。

 与这题十分类似：[P4053 建筑抢修](https://www.luogu.com.cn/problem/P4053)，感兴趣可以先去做一下。

第一眼观看时，可以看出，这道题应该与每项工作的紧急程度有关。因为显而易见的，如果一项工作完成后还可以完成其他的工作，但其它工作完成后就不能再完成这项工作了，我们应当先完成这项工作。

举个例子，假设我们现在已经耗费了 $100000$ 的时间，工作 $a$ 的截止开始时间为 $114514$，工作所需时间为 $2$，工作 $b$ 的截止开始时间为 $123456$，工作所需时间为 $20000$，此时如果先完成 $b$，时间就变成 $120000$，此时无法再完成 $a$。但如果先完成 $a$，此时时间变为 $100002$，我们仍有充足的时间去完成 $b$。所以可以得出结论，我们一般应当先完成最紧急的任务。

然而“紧急”是如何定义的呢？我们可以先猜想，截止开始时间越早，这项工作就越紧急。然而很快可以给出反例。

假设我们现在已经耗费了 $100000$ 的时间，工作 $a$ 的截止开始时间为 $114514$，工作所需时间为 $2$，工作 $b$ 的截止开始时间为 $114513$，工作所需时间为 $20000$，此时如果先完成 $b$，时间就变成 $120000$，此时无法再完成 $a$。但如果先完成 $a$，此时时间变为 $100002$，我们仍有充足的时间去完成 $b$。

上面这个例子仅仅是在开头的例子上将 $b$ 的截止开始时间修改为了 $114513$，此时会发现，我们仍然是先完成 $a$ 更划算，但此时 $b$ 的截止开始时间显然比 $a$ 更早，因此我们的猜想被推翻了。

然而再观察这个例子，我们可以发现它的截止结束时间就是他的截止开始时间加上它的所需完成时间，也就是说，在这个截止结束时间之前，你必须要完成这项工作，而不是开始你的工作。

我们继续猜想，会不会一项工作的紧急程度是由截止结束时间决定的呢？观看上面两个例子，会发现该结论在上述例子中均成立。那么我们再使用数学证明。

设两个工作截止开始时间为 $s_i$ 与 $s_j$，完成所需时间为 $t_i$ 与 $t_j$，当前已耗费的时间为 $time$，如果我们的最优选择方式为先完成工作 $i$ 再完成工作 $j$，也就是说先完成工作 $i$ 能完成工作 $j$，反之则不行，那么显然有两个不等式，分别是 $time+t_i\le s_j$ 与 $time+t_j>s_i$。

将第一个式子两边各加上 $t_j$，第二个式子两边同加上 $t_i$，可以得到 $time+t_i+t_j\le s_j+t_j$ 与 $time+t_j+t_i>s_i+t_i$，发现此时两个式子的左边相同，利用不等式的传递性可得 $s_j+t_j>s_i+t_i$，显然，我们可以将之理解为，如果先完成工作 $i$ 能完成工作 $j$，反之不行，那么工作 $i$ 的截止结束时间一定早于工作 $j$，也就是一般来说，我们应当先完成截止结束时间较早的工作。

所以，我们可以给每项工作按照截止结束时间升序排序，然后依次处理，确认是否完成这项工作。

然而，这个结论在面对一大堆工作时会出问题。我们的结论仅适用于先完成 $i$ 时能完成 $j$，反之不行的情况。如果两个工作一定冲突，我们该选谁呢？很显然，我们应当选择消耗时间较少的而非截止结束时间较早的。

有时也许由于我们的贪心，在前面选择了一个截止结束时间较早但耗时大于当前工作的，并且此时时间不够我们完成这项工作了，那么这就是前面所说的两个工作一定冲突的情况了。我们应当舍弃前面那个耗时较大的而选择现在这个。但如果前面耗时反而更小，那么我们就不用管，就当无事发生。

这样一种思路我们当然可以用大根堆来维护。我们先处理最紧急的，并依次往越来越不紧急的顺序去处理，每次处理时先将这次工作的耗时放进大根堆，如果时间充足就先完成这项工作，否则我们弹出之前耗时最长的工作，也就是大根堆的堆顶，然后再来完成这项工作。当然，如果这项工作本身就是耗时最长的，由于前面我们已经将它放入大根堆中，所以会直接将它自己弹出。然后再修改当前工作时间。

这时也许有同学要问，如果这项工作的耗时会导致工作时间不够怎么办？这种情况我们其实完全不用担心。因为我们是按照紧急程度升序排序后再处理的。凡是放入大根堆的，都一定是我们已经完成的工作。已完成的工作显然在此次工作之前处理，也就是说它的截止结束时间较早，在截止结束时间较早，且它的耗时大于我们当前工作的耗时的情况下，显然如果这项工作能完成，那么放弃这项工作去完成当前工作也是没有问题的。

都讲到这里了，思路已经十分清晰，接下来代码也很好实现了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 200005
int n,ans,t,m;
pair<int,int> a[N];
priority_queue<int> q;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>m;
	while(m--){
		cin>>n;
		for(int i=1;i<=n;i++){cin>>a[i].first>>a[i].second;a[i].first+=a[i].second;}
		sort(a+1,a+n+1);//排序
		while(q.size()) q.pop();//清空
		t=0;ans=0;
		for(int i=1;i<=n;i++){
			q.push(a[i].second);//放入大根堆
			if(t+a[i].second<=a[i].first){//能完成就完成
				ans++;
				t+=a[i].second;
			}else{
				t+=(a[i].second-q.top());//不能完成就放弃耗时最长的
				q.pop();
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：4)

考虑如果确定了待完成的任务集合 $S$，并且要求 $S$ 中的任务必须全部完成。那么对于 $S$，最优的顺序就是按照 $s_i+t_i$ 从大到小倒序完成。

证明考虑将时光从无穷远处倒流回到时刻 $0$，一个任务需要在 $s_i+t_i$ 之前完成，完成后时光将会跳到 $t_i$ 时刻前，此时倒序完成一定最优。

将所有任务按照 $s_i+t_i$ 从大到小排序后，完成任务的顺序已经确定。

依序枚举每个任务。贪心地，如果能选就选，不能选可以选择反悔，从之前完成的任务中选择花费的时间 $t_i$ 最大的一个扔掉。复杂度 $O(n\log n)$。

---

## 作者：Chenyichen0420 (赞：3)

## 思路分析

贪心，按照 $s+t$ 的值从小到大排序，这是最后期限。然后每个任务依次放入，超时了就优先抛弃用时长的，优先队列解决。

好吧，管理说这样并没有阐释清楚，那我再补充一下：

对于一个任务而言，如果我们能在不影响后面的任务的前提下尽可能的向后拖延一定更优，因此我们按照 $s+t$ 的值排序。

但是这样不一定能够达到最优，因为一个在前面的任务可能占用的时间过于长，导致后面更多任务无法正确的计入贡献。

因此我们使用反悔贪心的方式，让后面的任务来维护“不影响后面的任务”这一性质。当超限的时候，显然删去用时用时最长的能尽可能地给后面留下更多的时间。

所以本质上，我们就是在尽可能拖延的基础上用反悔贪心来保证不影响后面的任务。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, tim;
struct node {
	int l, r;
	inline bool operator<(const node& v) {
		return l < v.l;
	}
}q[200005];
priority_queue<int>pq;
signed main() {
	ios::sync_with_stdio(0);
	for (cin >> t; t; t--) {
		cin >> n; tim = 0;
		for (int i = 1; i <= n; ++i)
			cin >> q[i].l >> q[i].r, q[i].l += q[i].r;
		sort(q + 1, q + n + 1);
		while (pq.size()) pq.pop();
		for (int i = 1; i <= n; ++i) {
			tim += q[i].r;
			pq.emplace(q[i].r);
			while (tim > q[i].l)
				tim -= pq.top(), pq.pop();
		}
		cout << pq.size() << endl;
	}
}
```

---

## 作者：XCDRF_ (赞：2)

# P11457 \[USACO24DEC] Job Completion G 题解

[原题传送门](https://www.luogu.com.cn/problem/P11457)

[更好的阅读体验](https://www.luogu.com.cn/article/eno4erh7)

## 解题思路

~~看到这个题，第一眼想到了 DP，但是怎么推都推不出转移方程，遂放弃……~~

考虑贪心。设当前有 $i$ 和 $j$ 两个工作，其中 $i<j$，在做这两个工作之前花费的时间为 $sum$。则 $i$ 工作在 $j$ 工作前完成更优的充要条件是：$i$ 工作完成后可以做 $j$ 工作，但 $j$ 工作完成后不能做 $i$ 工作。写成式子就是：$sum+t_i\le s_j\wedge sum+t_j>s_i$。两式相加可得 $s_i+t_i<s_j+t_j$。所以将工作按 $s_i+t_i$ 升序排序，每次选最后期限最早的工作一定在当前为止最优。

当然，一直贪心肯定不能保证正确性。如果答案队列中有一个耗时特别大的工作，完成这个工作后，时间已经超过了下一个工作的开始时间，就放不进去了，可能因为这一个工作错过了下面的许多工作。这时可以考虑反悔贪心，用新工作把这个耗时特别大的工作替换掉。

再思考一下，做这个操作的条件是什么？

1. 需要有耗时最大的工作，也就是答案队列不空。
2. 新工作耗时要比最大工作耗时小，不然还不如不换。
3. 将耗时最大的工作取出来后，当前时间要比新工作的最晚开始时间要小，不然取出来了新工作也放不进去。

耗时最大的工作用一个大根堆维护即可。

## 注意事项

1. 记得开 long long。
2. 多测清空。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=3e5+5;
int t,n;
pii a[N];
bool cmp(pii a,pii b){
	return a.fi+a.se<b.fi+b.se;//按照 s+t 升序排序
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i].fi>>a[i].se;
		sort(a+1,a+n+1,cmp);
		priority_queue<int> q;
		int now=0,cnt=0;
		for(int i=1;i<=n;i++){
			pii t=a[i];
			if(now<=t.fi){//能放就直接放
				now+=t.se;
				q.push(t.se);
				cnt++;
			}
			else if(!q.empty()&&q.top()>t.se&&now-q.top()<=t.fi){//分别对应上述的三个条件
				now+=t.se-q.top();
				q.pop();
				q.push(t.se);
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
} 
```

[AC 记录](https://www.luogu.com.cn/record/196036099)

---

## 作者：xiaoliebao1115 (赞：2)

感觉题解区很多都没有证明清楚，自己来一篇题解。
## sol
假设有两个工作 $i$ 先完成劣于 $i+1$ 先完成，设 $sum$ 表示 $i$ 之前的工作已经花费的总时间。可能的情况只有 $i$ 先完成会使得 $i+1$ 无法完成，但反过来可以。

那么有 $sum+t_i>s_{i+1}$，但 $sum+t_{i+1}\le s_i$，有 $s_{i+1}-t_i<sum\le s_i-t_{i+1}$，整理得 $s_{i+1}+t_{i+1}<s_i+t_i$，所以显然可以对 $s_i+t_i$ 排序，按照这样的顺序遍历进行反悔贪心。

- 如果 $sum<=s_i$ 的话，$sum$ 加上 $t_i$ 即可。
- 否则，找到前面已经完成的 $t_i$ 最短的工作记作 $k$，将他的时间与当前比较，如果当前 $t$ 较小则将那个踢掉，当前加入，否则不变。

这样很对，但需要证明将那个踢掉之后一定能加入当前 $i$。假设 $i$ 上一个做的工作是 $j$，那么显然有 $sum-t_j\le s_j$，我们需要证明的是 $sum-t_k\le s_i$，也就是 $sum-t_j+(t_j-t_k)\le s_j+(-s_j+s_i)$，括号外的部分已经成立，考虑括号中的增量，也就是需要证明 $t_j-t_k\le -s_j+s_i$，由于排序可知 $s_j+t_j\le s_i+t_i<s_i+t_k$，那么 $t_j-t_k\le-s_j+s_i$ 成立，命题成立。

## code
使用优先队列维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int nn=3e5+5;
int t,n;
struct node{
	int s,t;
};
node x[nn];
inline bool cmp(node l1,node l2){
	return l1.s+l1.t<l2.s+l2.t;
}
priority_queue<int> q;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>x[i].s>>x[i].t;
		sort(x+1,x+n+1,cmp);
		int sum=0,ans=0;
		for(int i=1;i<=n;i++){
			if(sum<=x[i].s){
				sum+=x[i].t;
				q.push(x[i].t);
				ans++;
			}
			else{
				int tmax=q.top();
				if(tmax>x[i].t){
					q.pop();
					sum=sum-tmax+x[i].t;
					q.push(x[i].t);
				}
			}
		}
		while(!q.empty()) q.pop();
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：K_yuxiang_rose (赞：2)

这题和 [P11328 [NOISG 2022 Finals] Gym Badges](https://www.luogu.com.cn/problem/P11328) 几乎一模一样。

先考虑排序，考虑两个下标 $i$ 和 $j$，其中 $i<j$，设 $sum$ 为在 $i$ 之前总共使用的时间，则工作 $j$ 在工作 $i$ 之前完成更优，当且仅当：完成工作 $i$ 后不能完成工作 $j$，并且完成工作 $j$ 后能完成工作 $i$。也就是：

$sum+t_i>s_j$ 并且 $sum+t_j\le s_i$。

化简后得：$s_i+t_i>s_j+t_j$。所以我们按照这个式子排序即可。

接下来是贪心部分。先将工作时间存进大根堆，也就是优先队列中反悔用，默认这个工作能参加，将答案加一。对于能参加的工作就参加。对于不能参加的工作，就把现在最耗时间的工作弹出，将答案减一。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int> q;
struct node
{
	int t,s;
}a[300005];
bool cmp(node i,node j)
{
	return i.s+i.t<j.s+j.t;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		while(!q.empty()) q.pop();//多测记得清空
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i].s>>a[i].t;
		int sum=0,ans=0;
		sort(a+1,a+n+1,cmp); 
		for(int i=1;i<=n;i++)
		{ 
			q.push(a[i].t);
			ans++;
			if(sum<=a[i].s) sum+=a[i].t;
			else sum+=a[i].t-q.top(),q.pop(),ans--;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：fish_love_cat (赞：1)

五倍经验：P12916，P11457，P11328，P4053，AT_cf17_final_d

---

每个任务有一个截止时间 $s_i+t_i$，于是有贪心思路，让截止时间急的优先完成。

但这是错的，有一个完不成了，那么无论如何都会少一个任务，于是不一定舍弃当前任务，可以贪心的找一个前面很长的任务扔掉节约时间。

于是套一个优先队列，做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct fish{
    int fix,ed;
    bool operator <(const fish &x)const{
        return fix<x.fix;
    }
}a[200005];
bool cmp(fish x,fish y){
    return x.ed<y.ed;
}
priority_queue<fish>q;
int sum;
void solve(){
    sum=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i].ed>>a[i].fix,a[i].ed+=a[i].fix;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        sum+=a[i].fix;
        q.push(a[i]);
        while(sum>a[i].ed)
        sum-=q.top().fix,q.pop();
    }
    cout<<q.size()<<'\n';
    while(!q.empty())q.pop();
}
signed main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Delete_error (赞：0)

### 前话：
[Link](https://www.luogu.com.cn/problem/P11457)。
### 完成顺序：
对于一个工作，我们发现 $s+t$ 等价于工作的最久完成时间，我们下文将 $s$ 写为 $T_1$，$s+t$ 写为 $T_2$。

我们先考虑如何确定完成顺序，用邻项交换法思考，设当前时间为 $now$，当 $a$ 和 $b$ 先做 $a$ 更优时，当且仅当先做完 $a$ 后仍然可以做完 $b$，同时当先做完 $b$ 后做不完 $a$，可以用两个不等式表示：
$$now+a_{T_1}+b_{T_1}\le b_{T_2}$$
$$now+b_{T_1}+a_{T_1}>a_{T_2}$$
合并为：
$$a_{T_2}<now+a_{T_1}+b_{T_1}\le b_{T_2}$$
即：
$$a_{T_2}<b_{T_2}$$
那么就按这个排序，则答案方案一定是总序列的子序列，即完成顺序固定。
### 反悔贪心：
设当前时间为 $now$，当前要做的是 $c$，如果能做完就先做且答案加一；不能做完则一定当前加入了 $c$ 的方案有一个工作做不完，又因为 $now$ 越小后面的工作做完的可能越大，则踢掉当前方案中 $T_1$ 最久的工作，由于加入 $c$ 踢掉最久的，则答案不变。因为答案方案一定是总序列的子序列，则这样反悔贪心是正确的，不会改变先后顺序。
### code:
排序和大根堆维护都为 $O(n\log n)$。

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int  MAXN=2e5+5;
ll t,n;
struct Node{
	ll s,t;
}stu[MAXN];
bool cmp(Node a,Node b){
	return a.s+a.t<b.s+b.t;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		priority_queue<ll> q;
		ll sum=0,ans=0;
		for(int i=1;i<=n;i++) cin>>stu[i].s>>stu[i].t;
		sort(stu+1,stu+n+1,cmp);
		for(int i=1;i<=n;i++){
			q.push(stu[i].t);
			if(sum<=stu[i].s){
				sum+=stu[i].t;
				ans++;
			}
			else{
				sum+=stu[i].t;
				sum-=q.top();
				q.pop();
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

有问题私信,中考不一定会在，但看到一定会回复。

---

## 作者：StayAlone (赞：0)

较为经典的贪心。

首先假设已经钦定好了要完成的任务以及完成顺序（且合法），显然就是一个接一个地完成任务。完成第 $i$ 个任务后，总共花费 $\sum\limits_{j=1}^i t_j$。

考虑邻项交换。设已经耗费 $sum$ 的时间，此后任务 $i$ 比任务 $j$ 优，当且仅当完成 $i$ 后仍可完成 $j$，且完成 $j$ 后无法完成 $i$。即：$sum+t_i\le s_j$，$sum+t_j>s_i$。

相加得 $s_i+t_i\le s_j+t_j$。于是排序后，问题转化为选择一个最优的子序列，依次完成任务。

该问题可以反悔贪心。回到最开头的贪心策略，耗费的时间就是已选择任务集 $t$ 的和。维护这个和，若能加入第 $i$ 个任务就加入，否则考虑堆内最大的 $t$ 反悔即可。

[AC record](https://www.luogu.com.cn/record/219408630)

```cpp
int n;

struct node {
    ll s, t;

    il bool operator < (const node &p) const {
        return s + t != p.s + p.t ? s + t < p.s + p.t : t < p.t;
    }
} a[MAXN];

il void solve() {
    read(n);
    rep1(i, 1, n) read(a[i].s, a[i].t);
    sort(a + 1, a + 1 + n);
    priority_queue <ll> q; ll sum = 0; int cnt = 0;
    rep1(i, 1, n) {
        if (sum <= a[i].s) ++cnt, sum += a[i].t, q.emplace(a[i].t);
        else if (q.top() > a[i].t) sum -= q.top() - a[i].t, q.pop(), q.emplace(a[i].t);
    } printf("%d\n", cnt);
}

int main() {
    for (int T = read(); T--; ) solve();
    return 0;
}
```

---

## 作者：无名之雾 (赞：0)

赛时被这题搞笑到了。板的不能再板的反悔贪心。

更加搞笑的是赛后才意识到本题除了 [P4053](https://www.luogu.com.cn/problem/P4053) 和 [P11328](https://www.luogu.com.cn/problem/P11328) 这两道需要略微修改代码的原题外。

还有 [AT_cf17_final_d](https://www.luogu.com.cn/problem/AT_cf17_final_d) 这道我之前写过 [题解](https://www.luogu.com.cn/article/mxa2f5ef) 并且被出在进阶计划模拟赛里，代码只需要加一个多测就能通过的超级原题。

## 思路

我们考虑只有两项工作时如何去选择。

设当前砖堆块数为 $T$，以及 $(s_1,t_1)$ 和 $(s_2,t_2)$。

- 对于 $s_1$ 在前，接完这俩任务，$T\le s_2-t_1$。
- 对于 $s_2$ 在前，接完这俩任务，$T\le s_1-t_2$。

如果要求 $s_2$ 在前更优秀，有 $s_1+t_1\le s_2+t_2$。

所以不难想到把按照 $s_i+t_i$ 排序。

然后按照反悔贪心做即可。

## 证明

1. 如果所得贡献相同，那么所花时间越少一定不劣。

2. 若已确定所有工作都做，那按 $s_i+t_i$ 从小到大排序一定不劣。


因为按 $s_i+t_i$ 从小到大排序来做一定不劣。

考虑 $i$ 的时候，若现在他不做，以后就都不能做了，但如果现在他做了，以后可以将他取消，所以若做，相较于之前的决策不劣的话就可以直接做。

如果此时做了，根据上一段可以知道直接做了一定是比之前的决策优的。

如果此时之做不了，由于每次做砖头的贡献一样。

如果可以选择之前的一个取消来做这个，那贡献相同，我们就看有没有时间更长的来取消，

这样就可以使总时间更短，所以更优。

维护一个堆，不断按顺序向堆里压入元素，如果无法操作就替换做了任务里面 $t_i$ 最大的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void write(int x){
    if(x==0){putchar('0');return;}
	int len=0,k1=x,c[10005];
	if(k1<0)k1=-k1,putchar('-');
	while(k1)c[len++]=k1%10+'0',k1/=10;
	while(len--)putchar(c[len]);
}
const int N=5e5+5;
struct node{
    int v1,v2;
}a[N];
bool cmp(node a,node b){
    return a.v2<b.v2;
}
priority_queue<int>q; 
void solve(){
//	freopen("big_gift.in","r",stdin);
    while(!q.empty())q.pop();
    int n=read(),ans=0,sum=0;
    for(int i=1;i<=n;i++)a[i].v2=read(),a[i].v1=read(),a[i].v2+=a[i].v1;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        sum+=a[i].v1,q.push(a[i].v1);
        if(sum<=a[i].v2)ans++;
        else sum-=q.top(),q.pop();
    }
    cout<<ans<<"\n";
}
signed main(){
    int t=read();
    while(t--)solve();
    return 0;
}
```

---

