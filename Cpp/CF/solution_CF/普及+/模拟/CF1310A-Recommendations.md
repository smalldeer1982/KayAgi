# Recommendations

## 题目描述

VK news recommendation system daily selects interesting publications of one of $ n $ disjoint categories for each user. Each publication belongs to exactly one category. For each category $ i $ batch algorithm selects $ a_i $ publications.

The latest A/B test suggests that users are reading recommended publications more actively if each category has a different number of publications within daily recommendations. The targeted algorithm can find a single interesting publication of $ i $ -th category within $ t_i $ seconds.

What is the minimum total time necessary to add publications to the result of batch algorithm execution, so all categories have a different number of publications? You can't remove publications recommended by the batch algorithm.

## 说明/提示

In the first example, it is possible to find three publications of the second type, which will take 6 seconds.

In the second example, all news categories contain a different number of publications.

## 样例 #1

### 输入

```
5
3 7 9 7 8
5 2 5 7 5```

### 输出

```
6```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1 1 1 1 1```

### 输出

```
0```

# 题解

## 作者：灵茶山艾府 (赞：7)

按 $a[i]$ 从小到大遍历，把 $a[i]$ 相同的元素分为一组。

比如 $a=[1,1,1,2,9,9]$，那么一开始把等于 $1$ 的元素的**花费**丢到一个大根堆中，其中有一个 $1$ 是不需要增大的，把最大的花费弹出，表示对应的那个 $1$ 不需要增大。

然后把等于 $2$ 的元素的花费丢到大根堆中，同样把最大的花费弹出，表示对应的那个元素不需要继续增大。

然后把等于 $3$ 的元素的花费丢到大根堆中，由于此时没有等于 $3$ 的元素，直接从堆中弹出一个最大的花费。

模拟上述过程，同时用一个变量 $\textit{costSum}$ 表示堆中的花费之和，每次弹出最大花费后，累加 $\textit{costSum}$，即为答案。

AC 代码（Golang）：

```go
package main
import("bufio";"container/heap";."fmt";"os";"sort")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n int
	Fscan(in, &n)
	a := make([]struct{ v, t int }, n)
	for i := range a { Fscan(in, &a[i].v) }
	for i := range a { Fscan(in, &a[i].t) }
	sort.Slice(a, func(i, j int) bool { return a[i].v < a[j].v })

	ans := int64(0)
	h := hp{}
	for i, cur, costSum := 0, 0, int64(0); i < n || h.Len() > 0; cur++ {
		if h.Len() == 0 { cur = a[i].v }
		for ; i < n && a[i].v == cur; i++ { // 所有等于 cur 的元素的花费入堆
			heap.Push(&h, a[i].t)
			costSum += int64(a[i].t)
		}
		costSum -= int64(heap.Pop(&h).(int)) // 弹出一个最大花费，表示这个元素不需要继续增大
		ans += costSum
	}
	Print(ans)
}

type hp struct{ sort.IntSlice }
func (h hp) Less(i, j int) bool  { return h.IntSlice[i] > h.IntSlice[j] }
func (h *hp) Push(v interface{}) { h.IntSlice = append(h.IntSlice, v.(int)) }
func (h *hp) Pop() interface{}   { a := h.IntSlice; v := a[len(a)-1]; h.IntSlice = a[:len(a)-1]; return v }

```


---

## 作者：fanminghao000 (赞：2)

偶然在以前的模拟赛里翻到了这道题，写篇题解记录一下。

考虑这样一个贪心：为了让修改数字的代价尽量小，应该让代价大的尽量保持不变。也就是说，在 $x$ 个 $a_i$ 相同时，应该保留 $t_i$ 最大的那个，剩余的 $x-1$ 个全部修改。正确性十分显然，因为这 $x$ 个元素修改后的序列是固定的，也就是说修改次数是固定的，那当然是每次修改的代价越小越好啦

具体实现代码时，可以按 $a_i$ 升序排列后遍历，并用一个堆来维护实时最大值。用 $now$ 记录现在放到了哪一个数，判断这个位置上本来有没有东西，有的话丢进堆里一起操作。然后继续选最大的 $t$ 保留就好了


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
/*
思路：有相同就保留t最大的那个。可以把所有相同元素的t都丢进一个堆里面，每次取出堆顶即最大值保留，剩下的都视为a值+1。
*/ 
int n;
struct node{
	int a,t;
	friend bool operator <(node x,node y){
		return x.a<y.a;
	}
}a[200010];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].a;
	for(int i=1;i<=n;i++) cin>>a[i].t;
	sort(a+1,a+n+1);
	priority_queue<int> q;
	int now=0,sum=0,ans=0;
	for(int i=1;i<=n;i++){
		if(q.empty()){//这个位置现在是空的
			now=a[i].a;
			q.push(a[i].t);
			sum+=a[i].t;
		}
		else{
			if(a[i].a==now){//相同，放进堆里等待+1
				q.push(a[i].t);
				sum+=a[i].t;
			}
			else if(a[i].a>now){
				while(a[i].a>now&&!q.empty()){//不同，执行+1操作
					sum-=q.top();
					q.pop();
					ans+=sum;
					now++;
					//printf("ans=%d a_i=%d\n",ans,a[i].a);
				}
				if(a[i].a==now){//又相同了，再往里放 
					q.push(a[i].t);
					sum+=a[i].t;
				}
				else if(q.empty()){//前面的都执行完了，上一个位置和这个位置没有重叠
					q.push(a[i].t);
					sum+=a[i].t;
					now=a[i].a;
				}
			}
		}
	}
	while(!q.empty()){//剩下的也要放完
		sum-=q.top();
		q.pop();
		ans+=sum;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：tmp_get_zip_diff (赞：2)

**思路：**

1.如果直接贪心的话会发现情况很复杂。我们可以先求出所有数修改之后的数量应该是多少。如果两个数相同，那么其中一个数如果和其他数相同就得加到一个没有出现的数为止，不过有个更好的办法，对于这种情况，那么这几个数一定是连续的，所以可以先按 $a$ 从小到大排序，如果之前的数字修改后，当前的数比他前一个数小，就让当前的数加1，设求出的数组为数组 $c$ 。

2.在得到数组 $c$ 后，考虑如何用数组 $a$ 转移到最后的数组 $b$ 。设大于等于 $a_i$ 和 $a_j$ 的最小的整数是 $c_k$ ，且 $b_i>b_j$，如果让 $a_j$ 修改成 $b_k$ ，那么 $a_i$ 就得修改成一个比 $x$ 大的数，显然这样是不优的。所以需要优先使用 $b$ 大的数字来修改。

**代码：**
```
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e5+10; 
const int maxm = 1e6+10; //注意2e5、1e6得出来是小数，不能int arr[2e5+10]

struct INFO {
	int x, y;
} info[maxn];
int n, arr[maxn];
int main() {
	cin >> n;
	for (int i = 1; i<=n; ++i) cin >> info[i].x, arr[i] = info[i].x;
	for (int i = 1; i<=n; ++i) cin >> info[i].y;
	sort(info+1, info+n+1, [](INFO a, INFO b) {return a.x<b.x;});
	for (int i = 1; i<=n; ++i) arr[i] = max(arr[i-1]+1, info[i].x);
	set<int> st; //set
	for (int i = 1; i<=n; ++i) st.insert(arr[i]);
	ll ans = 0;
	sort(info+1, info+n+1, [](INFO a, INFO b) {return a.y>b.y;});
	for (int i = 1; i<=n; ++i) {
		auto it = st.lower_bound(info[i].x);
		ans += 1LL*(*it-info[i].x)*info[i].y;
		st.erase(it);
	}
	cout << ans << endl;
	return 0;
}
```
希望各位看懂，谢谢管理员，求过

---

## 作者：ix35 (赞：2)

为啥我比赛时 FST，交到洛谷上 AC 了啊？

这题感觉不太难，贪心即可。

如果有 $k$ 个数都是 $x$，那么当然选择其中价值较小的 $k-1$ 个数增加 $1$，再做比较。

但是直接暴力复杂度是 $O(n^2)$，不能通过此题。

考虑优化，由价值从大到小插入每一个数，如果当前位置上已经有一个数，那么一定是把当前的数后移（因为当前数是目前价值最小的数），求出当前位置之后的第一个空位即可。

用动态开点的线段树优化一下即可，时间复杂度 $O(n\log a_i)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=200010;
struct P {
	int a,t;
}p[MAXN];
bool cmp (P a,P b) {return a.t>b.t;}
int n,tot,rt,ch[MAXN<<5][2],val[MAXN<<5];
long long ans;
void modify (int &p,int l,int r,int pos,int v) {
	if (!p) {p=++tot;}
	val[p]+=v;
	if (l==r) {return;}
	int mid=(l+r)>>1;
	if (pos<=mid) {modify(ch[p][0],l,mid,pos,v);}
	else {modify(ch[p][1],mid+1,r,pos,v);}
	return;
}
int query (int p,int l,int r,int xl,int xr) {
	if (xr<l||r<xl) {return 0;}
	if (xl<=l&&r<=xr) {return val[p];}
	int mid=(l+r)>>1;
	return query(ch[p][0],l,mid,xl,xr)+query(ch[p][1],mid+1,r,xl,xr);
}
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {scanf("%d",&p[i].a);}
	for (int i=1;i<=n;i++) {scanf("%d",&p[i].t);}
	sort(p+1,p+n+1,cmp);
	for (int i=1;i<=n;i++) {
		int l=p[i].a,r=1e9+1e6;
		while (l<r) {
			int mid=(l+r)>>1;
			if (query(rt,1,1e9+1e6,l,mid)==mid-l+1) {l=mid+1;}
			else {r=mid;}
		}
		ans+=1ll*p[i].t*(l-p[i].a);
		modify(rt,1,1e9+1e6,l,1);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：wasa855 (赞：2)

感觉这是一道不难的题目。   


---

显然，如果有 2 个相同的数，一定是把花费较小的那个数 +1 ，如果有 3 个相同的数，一定是把花费较小的那 2 个数 +1。   
   
那么可以得出操作的方法，假设目前在处理 $x$，那么对于所有满足 $a_i=x$ 的 $i$ ，把除了 $b_i$ 最小的全部 +1，这样可以保证花费最少。   
   
实现的时候不需要什么高级的数据结构（还不会被卡常），每次把要操作的数放进一个堆里，每轮弹掉最大的数即可。   

Code：
```cpp
#define N 200005
struct Node
{
	int x,y;
};
Node a[N];
int n;
bool cmp(Node x,Node y)
{
	return x.x<y.x;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) a[i].x=read();
	for(int i=1;i<=n;i++) a[i].y=read();
	sort(a+1,a+n+1,cmp);
	priority_queue<int> q;
	int cur=0,cnt=0,ans=0,tmp=0;
	while(!q.empty()||cur<n)
	{
		cnt++;
		if(q.empty())
		{
			cnt=a[cur+1].x;
			while(cnt==a[cur+1].x&&cur<n)
			{
				cur++;
				tmp+=a[cur].y;
				q.push(a[cur].y);
			}
		}
		else
		{
			while(cnt==a[cur+1].x&&cur<n)
			{
				cur++;
				tmp+=a[cur].y;
				q.push(a[cur].y);
			}
		}
		tmp-=q.top(); q.pop();
		ans+=tmp;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

