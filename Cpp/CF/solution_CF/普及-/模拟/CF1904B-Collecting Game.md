# Collecting Game

## 题目描述

You are given an array $ a $ of $ n $ positive integers and a score. If your score is greater than or equal to $ a_i $ , then you can increase your score by $ a_i $ and remove $ a_i $ from the array.

For each index $ i $ , output the maximum number of additional array elements that you can remove if you remove $ a_i $ and then set your score to $ a_i $ . Note that the removal of $ a_i $ should not be counted in the answer.

## 说明/提示

In the first test case, the answers are as follows:

If we start with $ i=4 $ , our initial score is $ a_4=4 $ and $ a=[20,5,1,2] $ . We can remove $ 3 $ additional elements in the following order:

1. Since $ 4 \ge 1 $ , we can remove $ 1 $ and our score becomes $ 5 $ . After this, $ a=[20,5,2] $ .
2. Since $ 5 \ge 5 $ , we can remove $ 5 $ and our score becomes $ 10 $ . After this, $ a=[20,2] $ .
3. Since $ 10 \ge 2 $ , we can remove $ 2 $ and our score becomes $ 12 $ . After this, $ a=[20] $ .

If we start with $ i=1 $ we can remove all remaining elements in the array, so the answer is $ 4 $ .

If we start with $ i=2 $ , we can remove $ 3 $ additional elements in the following order: $ 1 $ , $ 4 $ , $ 2 $ .

If we start with $ i=3 $ , we can remove no additional elements.

If we start with $ i=5 $ , we can remove $ 1 $ additional element: $ 1 $ .

## 样例 #1

### 输入

```
4
5
20 5 1 4 2
3
1434 7 1442
1
1
5
999999999 999999999 999999999 1000000000 1000000000```

### 输出

```
4 3 0 3 1 
1 0 2 
0 
4 4 4 4 4```

# 题解

## 作者：huangrenheluogu (赞：7)

考虑一个暴力，删去每一个数，每次判断，能加上去就加上去，不能加上任何一个数就退出。这样的复杂度是 $\mathcal{O}(n^3)$。

考虑优秀的暴力，首先先把数组 $a$ 排序，这样可以一遍查找，如果找不到直接返回（因为后面的值更大），复杂度 $\mathcal{O}(n^2)$。

发现 $i$ 到的地方必然不会在 $i-1$ 可以到达的地方之前，所以我们可以用双指针遍历一下数组即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int T, n, now, ans[N], s[N], tot;
struct node{
	int x, id;
}a[N];
inline bool cmp(node x, node y){
	return x.x < y.x;
}
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld", &n);
		for(int i = 1; i <= n; i++){
			a[i].id = i;
			scanf("%lld", &a[i].x);
		}
		now = 1;
		sort(a + 1, a + n + 1, cmp);
		for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i].x;
		for(int i = 1; i <= n; i++){
			now = max(now, i);
			tot = s[now];
			while(now < n && a[now + 1].x <= tot){
				tot += a[now + 1].x;
				now++;
			}
			ans[a[i].id] = now - 1;
		}
		for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
		putchar('\n');
	}
	return 0;
}
/*
1
5
999999999 999999999 999999999 1000000000 1000000000
*/
```

[评测链接](https://codeforces.com/contest/1904/submission/236975040)

---

## 作者：MicroSun (赞：5)

## 题目大意

- 给定一个长度为 $n$ 的数组 $a$

- 对于每一个元素，可以在 $a$ 中删除任意个满足 $p\le a$ 的元素 $p$ 并将自己的值增加 $p$（不会真正改变数组 $a$）

- 求对于每个元素，最多能删除多少个元素，不包含自身

- $\sum{n} \le 10^5$

## 思路

离线所有询问，将 $a$ 按值从小到大排序。

将数组排序后，对于每一个元素 $a_i$，显然所有满足 $j<i$ 的元素 $a_j$ 都可以被删除，$a_i$ 将增加到 $\sum \limits_{j=1}^i a_j$。

考虑预处理出数组 $a$ 的前缀和 $p$。并维护**上次计算中删除的元素中的最大下标** $l$ 来确保 $O(n)$ 的时间复杂度。

计算每一个 $a_i$ 的答案时，如 $l \ge i$，说明在上次的计算中，$a_i$ 已被算入。直接将 $l-1$ 作为答案即可。

否则暴力维护 $l$ ，先令 $l \gets i-1$。如果 $p_l \ge a_{l+1}$，则 $a_{i+1}$ 可以被删除，使 $l \gets l+1$。多次重复这个步骤直到 $p_l < a_{l+1}$。最终，$l-1$ 即为答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0;bool w=0;char ch=getchar();
    while((ch<'0'||ch>'9')&&(ch^45)&&(ch^-1)) ch=getchar();
    (!(ch^45)&&(w=1,(ch=getchar())));
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return w&&(x=-x),x;
}
inline void write(int x,char l='\n'){
    if(!x){putchar('0');putchar(l);return;}
    int cnt=0;
    static char ch[55];
    ((x<0)&&(putchar('-'),(x=-x)));
    while(x) ch[++cnt]=x%10+48,x/=10;
    while(putchar(ch[cnt]),--cnt);
    putchar(l);
}
using ll=long long;
using pii=pair<int,int>;
#define pb push_back
void solve(){
	int n=read();
	vector<pii> a(n+1);
	vector<ll> p(n+1);
	vector<int> ans(n+1);
	int l=0;
	for(int i=1;i<=n;i++) a[i]={read(),i};
	sort(begin(a)+1,end(a));
	p[0]=0;
	for(int i=1;i<=n;i++) p[i]=p[i-1]+a[i].first;
	for(int i=1;i<=n;i++){
		if(l<i){
			l=i;
			while(p[l]>=a[l+1].first&&l<n) l++;
		}
		ans[a[i].second]=l;
	}
	for(int i=1;i<=n;i++) write(ans[i]-1,' ');
	putchar('\n');	
}
int main(){
	int t=1;
	t=read();
	while(t--) solve();
}
```

---

## 作者：_anll_ (赞：4)

博客内观赏效果更佳哦！
## 题目大意
给你一个长度为 $n$ 的序列 $a$，如果你当前的分数 $s \ge a_i$，$1\le i\le n$，你就可以删除 $a_i$ 并将 $s$ 增加 $a_i$。

问你对于每一个 $i$，删除 $a_i$ 并将你的分数设为 $a_i$。你**还能**删除多少个数。（最开始删除的 $a_i$ 不算）

## 大体思路
~~不是为什么我老被橙题卡的痛不欲生啊~~

不难发现最优的策略是从最小的开始吃，直到吃不动。显然易见，需要将数组从小到大排序。

但这样显然不够，我们还需要在这个基础上进行一些小优化。

令排序后的序列为 $p$，考虑预处理出该序列的前缀和 $q$，简单模拟一下可得 $p_{i-1}$ 可以删除的数 $p_i$ 一定能删除。所以我们只需要记录一下 $p_{i-1}$ 删除的最大数的位置。

然后从这往后暴力维护。比较 $q_{j-1}$ 和 $p_j$ 的大小，如果 $p_j > q_{i-1}$ 就终止循环。

## 代码演示
思路大概就上面那些，场切代码没有美化，有一些变量和题解里代码不同的变量名和一些小细节，那就结合注释理解吧。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
struct Num{
	int id,val;
}num[100005];
int t,n,qzh[100005],anu[100005];
bool cmp(Num a,Num b){
	return a.val<b.val;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>num[i].val;
			num[i].id=i;
		}
		sort(num+1,num+1+n,cmp);
		for(int i=1;i<=n;i++) qzh[i]=qzh[i-1]+num[i].val;
		int las=0,j,now=num[1].val;
		for(int i=1;i<=n;i++){
			las=max(las,i);//可能会出现i和i-1断层的情况
			anu[num[i].id]=las;
			for(j=las+1;j<=n;j++){
				if(qzh[j-1]<num[j].val) break;
			}
			las=j-1;
			anu[num[i].id]=las-1;
		}
		for(int i=1;i<=n;i++) cout<<anu[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：P_VICVIC_R (赞：1)

~~竟然有老师强制要求学僧题解，所以我找出了这场老早以前的比赛题。~~

-----

#### 题意：

定义一个操作：有一个序列，对于任意的一个值，都可以将比它小的另一个值加到它自身里，并将那个小的值从序列里删掉（下文管这个叫吞并）。

现在每组测试给你一个序列，问题对于序列中的每一个元素，各自可以~~吞并~~多少个其他元素。

#### 范围：

$ 1≤a_i≤10^9 , 1≤T≤5000 , ∑n≤10^5$ （多测）。

#### solution

看到 $∑n≤10^5$ ，说明 $O(∑n)$ 或 $O(∑n\log n)$ 都可做。

首先，我们肯定是要先排序，因为如果一个数本来就比另一个数小，那么小数一定会被大数吞并。

所以排序后，每一个数的下标减一就是它至少能吞并的数的数量，（~~那么不难想到最大的数字就能吞并剩余其他的数~~）。

所以每个数吞并完本来就比他小的数字的大小，就是排序后的前缀和。

（下文中的下标默认为排序后的下标）。

当第 $i$ 位前缀和大于第 $i+1$ 个数时，第 $i$ 个数便能吞并第 $i+1$ 个数，所以当有连续的一段都有第 $i$ 个数便能吞并第 $i+1$ 个数时，这一段数的答案便是一样的，所以想到双指针：

```c++
while(l<=n&&r<=n){
	while(l<n&&r<n&&pre[r-1]>=a[r])
		r++;
	for(int i=l;i<r;i++) 
		ans[a[i]]=r-1;//因为有排序嘛,所以注意一下统计答案的方法
	l=r;r++;
}
```

~~最后注意清数组，我死这上面三回。~~

如有错误的，欢迎私信指正。

---

## 作者：mouseboy (赞：1)

# 题意
> 你的分数为你吃掉元素的分数的总和
>
> 你可以吃掉不大于你当前分数的元素
>
> 求对于每一个 $i(1 \le i \le n)$ 为起始分数可以吃掉最大的元素个数

# 思路
> - 考虑到 $\sum n\le10^5$ 很容易想到 $nlog(n)$
>
> - 然后发现这个元素处理时一定有单调性 想到二分
>
> - 我们每次二分求出不比当前分数大的最大值
>
> - 更新答案,直到改变不了答案为止

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mk make_pair
using namespace std;

const int Maxn = 1e5 + 5;
ll t, n, x, y, cnt, a[Maxn], vis[Maxn], sum[Maxn];

struct node {
  ll a, id;// a为元素值,id为原数组下表
} b[Maxn];

bool cmp(node x, node y) {
  return x.a < y.a;// 排序
}
s
ll h(ll x, ll y) {// 二分找到不比当前分数大的最大值
  ll mid, l = x, r = n;
  while (l < r) {
    mid = l + r >> 1;
    mid++;
    if (b[mid].a <= y) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;// 因为直接覆盖可不清空
    for (int i = 1; i <= n; i++) {
      cin >> a[i], b[i].a = a[i], b[i].id = i;// 读入,并处理
    }
    sort(b + 1, b + 1 + n, cmp);// 排序
    for (int i = 1; i <= n; i++) {
      vis[b[i].id] = i;
      sum[i] = sum[i - 1] + b[i].a;// 处理
    }
    for (int i = 1; i <= n; i++) {
      x = sum[vis[i]], cnt = vis[i];// x为当前分数,cnt为答案
      while (1) {
        y = h(cnt, x);// 二分求出不比当前分数大的最大值
        if (y == cnt) {// 如果不能更新就退出
          break;
        }
        cnt = y;
        x = sum[cnt];// 更新答案
      }
      cout << --cnt << " ";// 要除去自己
    }
    cout << "\n";
  }
  return 0;// 华丽的结束
}

```

---

## 作者：kczw (赞：1)

# 题意
共有 $t$ 组数据

对于每组数据，给定一个长度为 $n$ 的数列。有一个基础为 $0$ 的变量 $s$。如果这个数值大于等于数列中的一个数，删去这个数，数值加上这个数。输出 $n$ 个结果，如果把 $s$ 加上 $n$ 数列中的 $i$ 个数并且删去这个数。问这个基础数值最多能到多少。
# 思路
首先，对于一个长度为 $n\le10^5$ 的数列我们不可能去两两比较大小，所以我们肯定要排序，同时对于大小同样的数，可以合并到一起，所以我们可以离散，算对于某个值所能达到的 $s$ 的最大值。

所以直接用 map。

离散排序过后，就可以保证一边的数全部都可以加到 $s$ 中，我们可以直接前缀和预处理好最后的值。

然后易证对于每个数列里的数，其 $s$ 所能够达到的最大值一定是某一位的前缀和。如果有一个数最后可以让 $s$ 达到第 $i$ 位前缀和，那么对于最小的比这个数大的数最后至少可以到达 $i$ 位前缀和，然后我们再继续递推，看从这个数最多可以到达第多少位前缀和，再传递给下一位。

举个例子，如果有一个排列过后的数列：
```
2 2 2 4 4 5 5 14 1145……
```
那如果 $2$ 可以使 $s$ 到第 $8$ 位的前缀和，那么 $4$ 可以直接从第 $8$ 位开始推导。
# 实现
```cpp
#include<iostream>
#include<map>
#define int long long
#define N 100005
using namespace std;
int t,n,a[N],id[N];
signed main(){
	scanf("%lld",&t);
	while(t--){
		map<int,int> num,vist;
		int ID=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),num[a[i]]++;
		int pre=0,number=0;
		for(auto v:num){
			id[++ID]=v.first;
			number+=v.second;
			pre+=v.first*v.second;
			vist[v.first]=number;
			num[v.first]=pre;
		}for(int i=ID-1;i>=1;i--)
		if(num[id[i]]>=id[i+1])
			vist[id[i]]=vist[id[i+1]];
		for(int i=1;i<=n;i++)printf("%lld ",vist[a[i]]-1);printf("\n");
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF1904B Collecting Game](https://www.luogu.com.cn/problem/CF1904B)

# 题意简述

给你一个由 $n$ 个正整数组成的序列 $a$ 和一个分数。如果你的分数大于或等于 $a_i$，那么你可以将分数增加 $a_i$，并从序列中删除 $a_i$，你需要求出对于每一个 $a_i$ 为你的分数时你可以从这个序列中删除数的最大数量。

# 解题思路

我们可以考虑将询问离线并将数字从小到大排序，然后维护一个指针 $l$，代表当前数字能到达的数，因为这样维护的话我们会发现，当一个数字比另一个数字大时，那么它所能到达的数字是不可能比比它小的数字小的，因此这样贪心是正确的。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,sum,l,ans[100010];
struct node{
	long long x,id;
}a[100010];
bool cmp(node x,node y){
	return x.x<y.x;
}
#define forl(i,a,b) for(int i=a;i<=b;i++)
#define forr(i,a,b) for(int i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		cin>>n;
		bool vis[n+1]={0};
		forl(i,1,n)
			cin>>a[i].x,a[i].id=i;
		sort(a+1,a+1+n,cmp);
		sum=0,l=1;
		forl(i,1,n)
		{
			while(l<=i)
			{
				if(!vis[l])
					vis[l]=1,sum+=a[l].x;
				l++;
			}
			if(sum>=a[l].x)
				while(sum>=a[l].x)
				{
					//cout<<l<<endl;
					if(!vis[l])
						vis[l]=1,sum+=a[l].x;
					if(sum<a[l+1].x || l>=n)
					{
						ans[a[i].id]=l-1;
						break;
					}
					l++;
				}
			else
				ans[a[i].id]=l-2;
		}
		forl(i,1,n)
		{
			if(ans[i]==n)
				ans[i]--;
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
	QwQ;
}
/*
Hack:
5
1 2 3 7 10
*/
```

---

## 作者：Star_F (赞：0)

一道贪心橙题。

## 题目大意：
给定一个序列，对于每一个元素，都可以将比它小的另一个元素加到它自身里，并将那个小的值从序列里删掉。

求每个元素能删除的最大数量。

## 题目分析：

考虑贪心，肯定是从最小的开始删除，因为这样能保证最优，所以我们对原数组进行排序。

这样做的时间复杂度是 $\mathcal{O}(n^2)$ 的，考虑优化。

因为我们已经排完序，所以从 $1$ 到 $n$ 遍历时答案一定是单调不降的，因为后面的数更大，能删除的数就更多，所以每次就不用从 $1$ 开始枚举是否能删除，而是从上一次的答案开始枚举。

我们还需要维护一个原数组的前缀和，用于快速求出能删到哪个元素。

时间复杂度 $\mathcal{O}(n \log n) $。

具体看代码实现。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Node
{
    int i, v;
} n[100005];

int T, N, Q[100005], A[100005];

bool cmp(Node x, Node y)
{
    return x.v < y.v;
}

signed main()
{
    cin >> T;
    while (T--)
    {
        cin >> N;
        for (int i = 1; i <= N; i++)
        {
            cin >> n[i].v;
            n[i].i = i;
        }
        sort(n + 1, n + 1 + N, cmp);
        for (int i = 1; i <= N; i++)
            Q[i] = Q[i - 1] + n[i].v;
        int L = 0, J, C = n[1].v;
        for (int i = 1; i <= N; i++)
        {
            L = max(L, i);
            A[n[i].i] = L;
            for (J = L + 1; J <= N; J++)
            {
                if (Q[J - 1] < n[J].v)
                    break;
            }
            L = J - 1;
            A[n[i].i] = L - 1;
        }
        for (int i = 1; i <= N; i++)
            cout << A[i] << " ";
        cout << endl;
    }
    return 0;
}
```

[提交记录](https://codeforces.com/contest/1904/submission/275956264)

---

## 作者：Miracle_1024 (赞：0)

## 思路：
  先选中判断值，任何比它小的数都可以直接被移除并加入你的分数。然后再根据加上这些数依次判断比判断值大的数（一旦有数比判断值加上之前所有数都要大，那么这个数和所有比它大的数就无需再去判断了）。这里可以使用 pair 来为原始数组加上序号来输出。
  
## 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
const int INF=0x3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
bool cmp(pair<ll,ll> x,pair<ll,ll> y){
	return x.first<y.first;
}
ll t,n,ans[N],idx,q;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		pair<ll,ll> a[n+5];
		memset(ans,0,sizeof ans);
		for(int i=1;i<=n;i++){
			cin>>a[i].first;
			a[i].second=i;	
		}
		sort(a+1,a+n+1,cmp);	
		idx=1,q=0;
		for(int i=1;i<=n;i++){
			while(idx<=i){
				q+=a[idx].first;
				idx++;
			}
			while(idx<=n&&q>=a[idx].first){
				q+=a[idx].first;
				idx++;
			}
			ans[a[i].second]=max(0ll,idx-2);
		}
		for(int i=1;i<=n;i++){
			cout<<ans[i];
			if(i!=n)cout<<" ";
			else cout<<endl;
		}
	}
}
```

---

## 作者：__JiCanDuck__ (赞：0)

# 题面翻译

长为 $n$ 的序列，可以进行下面的操作。

- 如果你的分数 $s\ge a_i,1\le i\le n$，你就可以删去 $a_i$ 并且将 $s$ 增加 $a_i$。

问：对于每一个 $i$，删除 $a_i$ 并将你的分数设为 $a_i$，你**还**可以删除多少个数（注意开始删除的数不算）。

$T$ 组数据，多测。

# 思路

不难发现，如果你分数大于 $i$，那么你删 $i$ 还是等会再删 $i$ 在不删其他元素的情况下是一样的，所以排序对答案没有影响。

排序后，不难看出，如果已经删了 $i$，那么之前的所有元素都可以删掉。

于是，可以考虑一个指针，记录已经删到了哪里，对于 $i$，计算继续删可以删多少。

# 时间复杂度

指针扫一遍，复杂度 $O(n)$，排序复杂度 $O(n \log n)$，可以优雅的跑过去。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1e5 + 5;

int n, Ans[kMaxN];
struct H {
	int a, b;
	friend bool operator<(const H &A, const H &B) {return A.a < B.a;} //重载运算符。
} a[kMaxN];

signed main() {
  ios ::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i].a;
			a[i].b = i; //排序后顺序被打乱，所以记下编号
		}
		sort(a + 1, a + n + 1); //排序
		int r = 1, s = 0;
		for (int i = 1; i <= n; i++) {
			s += a[i].a * (r <= i);  //如果没有计算过才计算
			(r == i) && (r++);     //如果指针正在判定 i 是否删除，那么指针往后移
			for (; r <= n && a[r].a <= s; r++) { //不断往后移
				s += a[r].a;
			}
			Ans[a[i].b] = r - 2; // 计算答案，由于不算自己且正在判定的需要减去
		}
		for (int i = 1; i<= n; i++) cout << Ans[i] << ' ';
		cout << '\n';
  }

  return 0;
}
```

---

## 作者：jr_inf (赞：0)

每次在数组中找大于 $s$ 的数太麻烦了，将数组排序后，每次能删去的数一定是一个前缀，就只需要对于每个 $i$，考虑它能删去的数的右端点在哪。设 $r_i$ 为初始删除 $i$ 能删到的数的右端点的编号，那么有：

$$
r_i=
\begin{cases}
n & \text{ if } i=n \\
i & \text{ if } \sum_{j=1}^{i}a_i<a_{i+1} \\
r_{i+1} & \text{ if } \sum_{j=1}^{i}a_i \geq a_{i+1}
\end{cases}
$$

倒序求 $r_i$ 即可，每个点的答案就是 $r_i-1$。

code：
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e5+10;
int t,n,r[N],b[N],ans[N];
struct node{int id,x;}a[N];
bool cmp(node x,node y){return x.x<y.x;}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i].x),a[i].id=i;
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)b[i]=b[i-1]+a[i].x;
		r[n]=n;
		for(int i=n-1;i>=1;i--)r[i]=(b[i]<a[i+1].x?i:r[i+1]);
		for(int i=1;i<=n;i++)ans[a[i].id]=r[i]-1;
		for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
		printf("\n");
	}
}

```


---

## 作者：yyrwlj (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1904B)

## 思路

首先，显然从小到大删除数字是最优的，所以我们再准备一个将原序列 $t$ 升序排序后的 $a$ 序列。

### 先来看接下来的朴素做法。

所有小于等于当前数的都可以直接删除，所以把 $a$ 序列从前往后扫，一直扫到 $a_j > t_i$ 为止，此时的分数为 $\sum_{k=1}^{j}a_k$。

然后 $k$ 继续从 $j+1$ 到 $n$ 扫，直到当前的分数小于 $a_k$ 为止。时间复杂度 $O(n^2)$。

### 接下来考虑优化

由于 $a$ 序列是单调不减的，所以找到最大的 $j$ 使得 $a_j \le t_i$ 可以使用二分。计算 $\sum_{k=1}^{j}a_k$ 可以预处理前缀和。

然后要找到最小的 $k$，使得 $j \le k \le n$ 且  $\sum_{i=1}^{k}a_k < a_{k+1}$。

我们发现不能直接使用二分，因为不满足二段性。

但是可以将所有满足 $\sum_{j=1}^{i}a_j < a_{j+1}$ 的 $i$ 存进一个序列 $d$ 中，我们会发现 $d$ 是单调递增的。

于是问题就转化成了找到一个最小的 $k$，使得 $d_k \ge j$，可以使用二分解决，时间复杂度优化成了 $O(n \log n)$。

注意，因为有可能出现可以删除所有数的情况，所以要把 $n$ 放到 $d$ 的末尾。

## Code

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100005;
int a[N], t[N];
long long s[N];
int d[N];
void work()
{
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d", &t[i]);
        a[i] = t[i];
    }
    sort(a + 1, a + n + 1);
    int m = 0;
    for (int i=1;i<=n;i++)
    {
        s[i] = s[i - 1] + a[i];
        if (s[i] < a[i + 1])
            d[++m] = i;
    }
    d[++m] = n;
    for (int i=1;i<=n;i++)
    {
        int l = 1, r = n, ans;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (a[mid] <= t[i])
                l = mid + 1, ans = mid;
            else
                r = mid - 1;
        }
        if (ans == 1)
        {
            printf("0 ");
            continue;
        }
        l = 1, r = m;
        int ans2 = m;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (d[mid] >= ans)
                r = mid - 1, ans2 = mid;
            else
                l = mid + 1;
        }
        printf("%d ", d[ans2] - 1); //减一是因为要排除自己
    }
    putchar('\n');
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```

---

