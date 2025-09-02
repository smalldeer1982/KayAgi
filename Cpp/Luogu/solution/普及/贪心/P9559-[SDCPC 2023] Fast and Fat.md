# [SDCPC 2023] Fast and Fat

## 题目描述

您正在参加一场团体越野比赛。您的队伍共有 $n$ 名队员，其中第 $i$ 名队员的速度为 $v_i$，体重为 $w_i$。

比赛允许每名队员独立行动，也允许一名队员背着另一名队员一起行动。当队员 $i$ 背着队员 $j$ 时，如果队员 $i$ 的体重大于等于队员 $j$，则队员 $i$ 的移动速度不会变化，仍然为 $v_i$；如果队员 $i$ 的体重小于队员 $j$，则队员 $i$ 的移动速度会减去两者的体重差值，即变为 $v_i - (w_j - w_i)$。如果队员 $i$ 的移动速度将变为负数，则队员 $i$ 无法背起队员 $j$。每名队员最多只能背负另一名队员，被背负的队员无法同时背负其他队员。

所有未被背负的队员中，最慢的队员的速度，即为整个队伍的速度。求整个队伍能达到的最大速度。

## 样例 #1

### 输入

```
2
5
10 5
1 102
10 100
7 4
9 50
2
1 100
10 1```

### 输出

```
8
1```

# 题解

## 作者：SXqwq (赞：9)

## Analysis

首先我们注意到**如果一个期望最大速度无论如何都无法满足，则比它大的速度也无法满足**，符合**局部答案舍弃性**，也可以说单调性。考虑二分。

每次二分期望最大值，然后 check 一下该期望最大值是否满足即可。

具体如何写 check 呢？

首先，如果一个人的速度小于期望最大速度，我们肯定希望他能够被一个人背起来，并且这个人背起他之后速度仍然大于等于期望最大速度。

但是注意，**一个人最多只能背起一个人**。这里我们就遇到了一个问题，如果一个人跑的很快，体重又很大，可以背起一个跑的很慢而且很重的人。我们却让他背一个很轻而且跑的不算慢的人。导致后面很重而且跑的很慢的人无法背起来。实际上他可以被背起来，这就会导致答案错误。

我们显然希望一个能背很重的人去背一个很重的人。（保证他自身速度大于等于期望最大值的前提下）考虑贪心。

首先，对于每个二分出来的期望最大值，我们先预处理一下如果一个人可以背人（他的速度大于等于期望最大值），他最大可以背多重的人。形式化地，若 $v_i$ 表示这个人的速度， $w_i$ 表示这个人的重量， $x$ 表示当前期望最大值。则他能在满足自身速度大于等于期望最大值的前提下，能背动的最大重量是 $a_i=v_i+w_i-x$ 。也就是把自身速度降到 $x$ 的时候。

然后，我们对 $a_i$ 进行从大到小排序，对速度小于等于期望最大值的人的重量进行从大到小排序。记为 $q_i$ 。显然如果 $a_i < q_i$ 则直接返回 false 即可。因为我们已经从大到小排序，如果当前人能背动的最大重量小于当前人的重量则后面也一定背不动。

总结：本题考察二分答案应用。在写 check 函数的时候应用了贪心的思想。整体难度不大。考察基础算法熟练度。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 100010;
const int INF = 1e9;
int T;
int n;
struct Node
{
    int v,w;
}A[N],B[N];
bool check(int x)
{
    vector <int> p,q;
    for(int i=1;i<=n;i++) if(A[i].v >= x) p.push_back(A[i].v+A[i].w-x);
    for(int i=1;i<=n;i++) if(B[i].v < x) q.push_back(B[i].w);
    if(p.size() < q.size()) return false;
    for(int i=0;i<q.size();i++)
    {
        if(p[i] < q[i]) return false;
    }
    return true;
}
bool cmp(Node a,Node b) 
{
    return a.w > b.w;
}
bool cmp1(Node a,Node b)
{
    return (a.v+a.w) > (b.v+b.w);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--)
    {   
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>A[i].v>>A[i].w;
            B[i].v = A[i].v;
            B[i].w = A[i].w;
        }
        sort(A+1,A+n+1,cmp1);
        sort(B+1,B+n+1,cmp);
        int l = 0,r = INF;
        while(l < r)
        {
            int mid = (l+r+1) / 2;
            if(check(mid)) l = mid;
            else r = mid-1;
        }
        cout<<l<<endl;
    }
}
```


---

## 作者：Coffee_zzz (赞：4)

发现有单调性，一眼丁真，鉴定为二分答案。

对值域二分，每次检查当前的答案 $ans$ 是否合法。

首先把人分成两波：$v_i \lt ans$ 的和 $v_i \ge ans$ 的。

对于 $v_i \ge ans$ 的人，他的背上能背一个体重小于等于 $v_i+w_i-ans$ 的人；

对于 $v_i \lt ans$ 的人，他一定要被背着。

接下来我们贪心地匹配。

对于 $v_i \gt ans$ 的人，按照 $v_i+w_i- ans$ 的值从小到大排序；

对于 $v_i \lt ans$ 的人，按照 $w_i$ 的值从小到大排序。

那么我们依次考虑每一个要被背的人 $i$，给他分配一个最小的满足 $v_p+w_p-ans \ge w_i$ 且背上没有人的人 $p$，让这个人背上他。

如果每一个要被背的人都能被背上，则合法，否则不合法。正确性显然。

---

## 作者：One_JuRuo (赞：4)

## 思路

直接做比较难，考虑二分答案，所以我们需要想出一种时间复杂度还行的方法检查答案是否合格。

假设目前二分的答案是 $x$，那么速度低于 $x$ 必然需要别人背。

那么，自然而然地想到将所有人分成两部分，那么速度低于 $x$ 中的所有人应当优先满足较重的，如果优先满足较轻的，就可能导致较重的无法被满足。

同时，速度低于 $x$ 的人中，最重的，应该用速度和体重之和最大的人来满足，如果满足不了，这个答案就肯定无法满足，如果能满足就可以继续看下一组人。

具体实现可以用优先队列排序，每次取最大的。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int v,w;}t[100005];
inline bool cmp(node a,node b){return a.v<b.v;}
int T,n,l,r,mid,ans;
inline bool check(int x)
{
	priority_queue<int>l,r;
	for(int i=1;i<=n;++i)
	{
		if(t[i].v>=x) r.push(t[i].w+t[i].v);//分成两个部分，速度满足条件的要看速度和体重之和
		else l.push(t[i].w);//速度不满足的只看体重
	}
	while(!l.empty()&&!r.empty())
		if(r.top()-l.top()>=x) l.pop(),r.pop();//每次看最大的一组人是否满足条件
		else return 0;
	return (l.empty());//如果最后剩的是速度低的人也不满足条件
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d%d",&t[i].v,&t[i].w);
		sort(t+1,t+n+1,cmp),l=0,r=1000000000,ans=0;
		while(l<=r)//二分答案
		{
			mid=l+r>>1;
			if(check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}	
}
```

---

## 作者：Auto_Accepted (赞：1)

首先这个问题它是有单调性的，整体队伍速度大的满足的话整体队伍速度小的一定也满足，所以一眼二分答案。

然后不难想到二分整体的速度，只有大于这个速度的才能背人。

然后就变为了一个经典的贪心问题，速度越大的背越重的即可。

然后做完了。

## 代码：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair <int , int>
vector < PII > a;
inline bool check(int mid){
    priority_queue <int> l , r;
    for(auto [x , y] : a){
        if(x < mid){
            l.push(y);
        }
        else{
            r.push(x + y - mid);
        }
    }
    while((!l.empty()) && (!(r.empty()))){
        int w1 = l.top() , w2 = r.top();
        if(w2 < w1) return 0;
        l.pop();
        r.pop();
    }
    return l.empty();
}
signed main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        a.resize(n);
        for(int i = 0;i < n;i++){
            cin >> a[i].first >> a[i].second;
        }
        sort(a.begin() , a.end());
        int l = 0 , r = INT_MAX , ans;
        while(l <= r){
            int mid = l + r + 1 >> 1;
            if(check(mid)){
                ans = mid;
                l = mid + 1;
            }
            else{
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }
}
```


---

## 作者：LIUYC_C (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P9559)

### 大体思路：
挺显然的，观察到要最慢的队员最快，即要求最小值的最大值，一眼二分最慢的速度。

考虑怎么 check 答案，即判断在最慢速度的限制下，所有的队员的速度是否都大于这个值，若大于，返回 true，否则返回 false。

观察到还有背起操作，只有速度小于二分的速度的才要被背起，那么大于二分速度的人数小于小于二分速度的人数的话，肯定就背不了那么多人，返回 false 就好，此时考虑贪心，拆完括号后，得到一个队员被背起后的速度变为了 $v_{i}+w_{i}-w_{j}$，那么我们肯定让速度和体重之和最大的去背体重最大的，排个序就好。

### 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int N=1e5+10;

struct node{
  int v;
  int w;
}tr[N],h[N];

int w[N];
int m[N];

bool cmp(int a,int b){
  return a>b;
}  

int n;

bool check(int x){
  int ans=0;
  int idx1=0,idx2=0;
  for(int i=1;i<=n;i++){
    if(tr[i].v>=x){
      ans++;
      w[++idx1]=tr[i].w+tr[i].v;
    }
    else{
      m[++idx2]=tr[i].w;
    }
  }
  if(idx1<idx2)return false;
  sort(w+1,w+idx1+1,cmp);
  sort(m+1,m+idx2+1,cmp);
  for(int i=1;i<=idx2;i++){
    if(w[i]-m[i]<x){
      return false;
    }
  }
  return true;
}

void solve(){
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>tr[i].v>>tr[i].w;
  }

  int l=1,r=1e9;
  while(l<r){
    int mid=l+r+1>>1;
    if(!check(mid))r=mid-1;
    else l=mid;
  }
  cout<<l<<endl;
}

signed main(){
  ios::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--){
    solve();
  }
  return 0;
}
```


---

## 作者：SakurajiamaMai (赞：0)

## 思路:

通过题意可以知道，最终要求的结果是一个最大的最小值，也就是最小值最大。考虑二分，左端点为最慢的速度，右端点为最长速度。接下来是如何写判断函数。

首先遍历所有人，只要有人不符合当前的速度，就需要找人来背他，**那么背他的人至少要具备这样一个性质，就是当前的体重加上自己的速度与当前速度的差值大于等于被背的人的体重**，将这样一个数值存入数组中，然后排序，一旦有不符合的就返回。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
string s;
int n,t,a[N],f[N],res,m,k;
bool vis[N];
struct node
{
    int v,w;
    bool operator<(const node&W)const
    {
        if(v==W.v) return w>W.w;
        else return v<W.v;
    }
}p[N];
bool check(int u)
{
    int num=0,cnt=0;
    for(int i=1;i<=n;i++){
        if(p[i].v<u) f[i]=-p[i].w,num++;
        else f[i]=p[i].w+p[i].v-u,cnt++;
    }
    if(num>cnt) return false;
    sort(f+1,f+1+n);
    for(int i=1,j=n;i<=j;i++,j--)
        if(f[i]+f[j]<0) return false;
    return true;
}
void solve()
{
    cin>>n;
    int l=0x3f3f3f3f,r=-0x3f3f3f3f;
    for(int i=1;i<=n;i++) cin>>p[i].v>>p[i].w,r=max(r,p[i].v),l=min(l,p[i].v);
    sort(p+1,p+1+n);
    while(l<r){
        int mid=l+r+1>>1;
        if(check(mid)) l=mid;
        else r=mid-1;
    }
    cout<<l<<endl;
}
signed main()
{
    std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}

```


---

## 作者：zzbzwjx (赞：0)

## 题意
[自己看题](https://www.luogu.com.cn/problem/P9559)

## 思路
根据题目可以看出整个队伍的速度满足单调性，速度大的满足条件，速度小的一定也会满足条件，因此我们只需找到一个时间复杂度可以的方法就行。可以观察到，对于一个确定的速度 $V$ ，会存在两种情况。

- 小于 $V$ 的一定要被大速度的背才可以
- 大于等于 $V$ 的人才可以背人

再观察可得，大于 $V$ 的人可以背起重量最大值为 $w_i+V-v_i$ ，因此用两个优先队列存储，最后小于 $V$ 的被全部背起就可以满足条件。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
bool f(int v, vector<pair<int, int> > a){
	priority_queue<int> l, r;
	for (auto [x, y] : a) {
		if (x >= v) {
			r.push(y + x - v);
		} else {
			l.push(y);
		}
	}
	while (r.size() && l.size()) {
		if (r.top() >= l.top()) {
			r.pop();l.pop();
		} else {
			return 0;
		}
	}
	if (l.empty()) return 1;
	return 0;
}
void do_() {
	cin >> n;
	vector<pair<int, int> > a(n);
	for (auto &[x, y] : a) {cin >> x >> y;}
	sort(a.begin(), a.end());
	int l = 0, r = 1e9;
	while (l < r){
		int mid = (l + r + 1) >> 1;
		if (f(mid, a)) {l = mid;}
		else {r = mid - 1;}
	}
	cout << l << '\n';
}
int main() {
	cin>>t;
	while(t--){
		do_();
	}
	return 0; //好习惯
}
```

---

## 作者：HappyJaPhy (赞：0)

## 题目（重现赛打的第二道题）
[在我的博客里查看题解](https://www.luogu.com.cn/blog/ImDustSans/solution-p9559)
- 求最小值最大，一眼答案二分（主要是最近被答案二分快折磨没了，比较敏感）
- 一个人可以进行可能有损的帮助，使整体速度变大

## 思路
这道题是对预计的速度进行二分查找，但是 check(v) 这个函数该如何写呢？

1. 首先，如果队伍速度的中位数都比要查找的 $v$ 还小的话，那么一定不能成功

------------
**小证明**

如果有速度小于 $v$ 的人，那他一定是要被背起的。若需要被背起的人数过半，那么这个速度一定不可能达到。

------------

2. 我们将输入复制一份，分别按照重量 $w_i$ 以及重量与速度之和 $w_i+v_i$ 排序。
- 为什么要这么做呢？观察题目里“背起”后速度的式子，打开括号可以得到：
$$v_i+w_i-w_j$$
- 也就是说，最终的速度只与 $v_i+w_i$ 以及 $w_j$ 有关。这里利用贪心思想，我们让需要背起的最重的人 $j$，与自身“容量”也即 $v_i+w_i$ 最大的人 $i$ 匹配起来。如果这样都不能匹配上，那么就一定无法达到要求的速度了。
3. 因为在第一点里还需要速度 $v$ 的中位数，所以还需要复制一份以 $v_i$ 排序，方便查询。

## AC 代码
```cpp
#include <bits/stdc++.h>
#define N 1005
using namespace std;
int n;

struct node {
	int v, w, id;
	bool operator <(const node &x)const {
		return v + w < x.v + x.w;
	}
} a[N], b[N], c[N];

inline bool cmdw(node a, node b) {
	return a.w < a.w;
}

inline bool cmdv(node a, node b) {
	return a.v < a.v;
}

inline void read(int &x) {
	char ch = x = 0;
	while (ch < '0' || ch > '9') {
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	return ;
}

inline void print(int x) {
	static int stk[50];
	int top = 0;
	do {
		stk[top++] = x % 10;
		x /= 10;
	} while (x);
	while (top) {
		putchar(stk[--top] + 48);
	}
	putchar('\n');
	return ;
}

bool vis[N];
bool check(int x) {
	if (c[n >> 1].v < x) { //如果中位数（偶数个时取更大的那个）都不够，就直接返回
		return 0;
	}
	memset(vis, 0, sizeof vis);
	int l = n;
	for (int i = n; i; i--) {
		while ((b[l].v >= x || vis[b[l].id]) && l) { //找重量最大的需要背起的人
			l--;
		}
		while ((a[i].v < x || vis[a[i].id]) && i) { //找“容量”最大的可以背别人的人
			i--;
		}
		if (!i || !l) { //找完了就退出
			break;
		}
		if (a[i].v + a[i].w - b[l].w < x) { //如果“容量”最大的人都无法胜任，那就一定不行了
			return 0;
		}
		vis[a[i].id] = vis[b[l].id] = 1; //记得标记有人了
	}
	return 1;
}

int main() {
	int T, l, r, mid, res;
	read(T);
	while (T--) {
		read(n);
		for (int i = 1; i <= n; i++) {
			read(a[i].v), read(a[i].w);
			b[i].v = a[i].v, b[i].w = a[i].w; //读入时复制两份出来
			c[i].v = a[i].v, c[i].w = a[i].w;
			a[i].id = b[i].id = c[i].id = i;
		}
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + n, cmdw);
		sort(c + 1, c + 1 + n, cmdv); //分别按照 w、v 和 w + v 来排序
		res = l = c[1].v, r = c[n].v;
		while (l <= r) { //答案二分
			mid = (l + r) >> 1;
			if (check(mid)) {
				l = mid + 1;
				res = mid;
			} else {
				r = mid - 1;
			}
		}
		print(res);
	}
	return 0;
}
```
- 我自己都没想到能一次过，这可能才是我第 $3$ 次打正解是答案二分的题目，可以说是受益良多。
- 感觉代码挺复杂的，有优化或错误请大佬指正！
- 改了点细节的东西，直接交是过不了滴~

---

