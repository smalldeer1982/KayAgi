# Concatenation of Arrays

## 题目描述

You are given $ n $ arrays $ a_1 $ , $ \ldots $ , $ a_n $ . The length of each array is two. Thus, $ a_i = [a_{i, 1}, a_{i, 2}] $ . You need to concatenate the arrays into a single array of length $ 2n $ such that the number of inversions $ ^{\dagger} $ in the resulting array is minimized. Note that you do not need to count the actual number of inversions.

More formally, you need to choose a permutation $ ^{\ddagger} $ $ p $ of length $ n $ , so that the array $ b = [a_{p_1,1}, a_{p_1,2}, a_{p_2, 1}, a_{p_2, 2}, \ldots, a_{p_n,1}, a_{p_n,2}] $ contains as few inversions as possible.

 $ ^{\dagger} $ The number of inversions in an array $ c $ is the number of pairs of indices $ i $ and $ j $ such that $ i < j $ and $ c_i > c_j $ .

 $ ^{\ddagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, we concatenated the arrays in the order $ 2, 1 $ . Let's consider the inversions in the resulting array $ b = [2, 3, 1, 4] $ :

- $ i = 1 $ , $ j = 3 $ , since $ b_1 = 2 > 1 = b_3 $ ;
- $ i = 2 $ , $ j = 3 $ , since $ b_2 = 3 > 1 = b_3 $ .

Thus, the number of inversions is $ 2 $ . It can be proven that this is the minimum possible number of inversions.

In the second test case, we concatenated the arrays in the order $ 3, 1, 2 $ . Let's consider the inversions in the resulting array $ b = [2, 1, 3, 2, 4, 3] $ :

- $ i = 1 $ , $ j = 2 $ , since $ b_1 = 2 > 1 = b_2 $ ;
- $ i = 3 $ , $ j = 4 $ , since $ b_3 = 3 > 2 = b_4 $ ;
- $ i = 5 $ , $ j = 6 $ , since $ b_5 = 4 > 3 = b_6 $ .

Thus, the number of inversions is $ 3 $ . It can be proven that this is the minimum possible number of inversions.

In the third test case, we concatenated the arrays in the order $ 4, 2, 1, 5, 3 $ .

## 样例 #1

### 输入

```
4
2
1 4
2 3
3
3 2
4 3
2 1
5
5 10
2 3
9 6
4 1
8 7
1
10 20```

### 输出

```
2 3 1 4
2 1 3 2 4 3
4 1 2 3 5 10 8 7 9 6
10 20```

# 题解

## 作者：Eddie08012025 (赞：3)

## 思路
考虑排序所有的 $a_i$ 使序列逆序对数量最少。

当 $a_i$ 与 $a_j$ 满足
- $\max(a_{i,1},a_{i,2})=\max(a_{j,1},a_{j,2})$，显然的，$a_{i,1}+a_{i,2}$ 与 $a_{j,1}+a_{j,2}$ 小的一方在前面更优。
- $\max(a_{i,1},a_{i,2})> \max(a_{j,1},a_{j,2})$，$a_j$ 在 $a_i$ 前面更优，证明：假如 $a_{i,1}>a_{i,2}$，无论如何安排都会出现一个逆序对，这是无法改变的。因此我们假设 $a_{i,2}=\max(a_{i,1},a_{i,2})$，考虑 $a_{j,1},a_{j,2}$ 与 $a_{i,1}$ 之间的关系。
  - $a_{j,1},a_{j,2}<a_{i,1}$，显然 $a_j$ 在 $a_i$ 前面更优。
 
  - $a_{j,1}<a_{i,1}<a_{j,2}$ 或 $a_{j,2}<a_{i,1}<a_{j,1}$，$a_i$ 在前面会额外构成 $a_{i,2},a_{j,1}$，$a_{i,2},a_{j,2}$，$a_{i,1},a_{j,2}/a_{j,1}$ 三组逆序对。$a_j$ 在前面会额外构成 $a_{i,1},a_{j,1}/a_{j,2}$ 一组逆序对，所以也是 $a_j$ 在 $a_i$ 前面更优。
 
  - $a_{j,1},a_{j,2}>a_{i,1}$，用同样的方法说明无论如何都会额外出现 $2$ 组逆序对，$a_j$ 在 $a_i$ 前面不劣。
 
- $\max(a_{i,1},a_{i,2})< \max(a_{j,1},a_{j,2})$，得 $a_i$ 在 $a_j$ 前面更优。

借用 sort 排序。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,vis[7],pp[7],ansss,tr[500001],po[500001];
pair<int,int>z[100001],p[300001];
bool cmd(pair<int,int>a,pair<int,int>b){
	int a1=a.first,a2=a.second,b1=b.first,b2=b.second,cnt;
	int maxn=max({a1,a2,b1,b2});
	if((a1==maxn||a2==maxn)&&(b1==maxn||b2==maxn)){
		return (a1+a2)<(b1+b2);
	}else if(a1==maxn||a2==maxn){
		return 0;
	}else if(b1==maxn||b2==maxn){
		return 1;
	}
}signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		ansss=0;
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>z[i].first>>z[i].second;
		}sort(z+1,z+n+1,cmd);
		for(int i=1;i<=n;i++){
			cout<<z[i].first<<" "<<z[i].second<<" ";
		}cout<<"\n";
	}return 0;
}
```

---

## 作者：zengxuheng (赞：2)

# 分析
可以看出，我们有几种排序方式。


---


第一种：比较两个数组之间相互逆序对大小。

例如：

数组 $a1$ 与 $a2$ 有 $cnt1$ 个逆序对。

数组 $a2$ 与 $a1$ 有 $cnt2$ 个逆序对。

比较 $cnt1$ 与 $cnt2$ 大小来排序。


---


第二种：看哪个数组有两个数组最大值，那个数组就排在后面。

例如：

数组 $a1$ 元素为 $[2,3]$，数组 $a2$ 元素为 $[1,5]$。

因为数组 $a2$ 中有两个数组最大值：$5$，因此将 $a2$ 排在 $a1$ 后面。


---

第三种：按和排序。

例如：

数组 $a1$ 元素为 $[2,3]$，和为 $5$；数组 $a2$ 元素为 $[1,5]$，和为 $6$。

因为 $6 > 5$，因此将 $a2$ 排在 $a1$ 后面。


---

证明对错：


---

第一种：

由于比较两个数组之间相互逆序对大小并不能推向全局，贪心思想必须有传递性，于是废除。

例子：

$a1 = (3,3)$，$a2 = (1,5)$，$a1 = (2,2)$。

由于 $a1$ 与 $a2$ 逆序对数量都为 $2$，我们将 $a2$ 排在 $a1$ 后面，$a2$ 与 $a3$ 逆序对数量都为 $2$，我们将 $a3$ 排在 $a2$ 后面。

于是就有了以下一个序列：
$$
(3,3,1,5,2,2)
$$
明显不是最优。


---

第二、三种都具有传递性，所以都可以作为答案。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> a[100010];
inline int read() {
	int x=0,f=1;
	char ch=getchar/*_unlocked*/();
	while (ch<48||ch>57) {
		if (ch=='-') f=-1;
		ch=getchar/*_unlocked*/();
	}
	while (ch>=48&&ch<=57) {
		x=x*10+ch-48;
		ch=getchar/*_unlocked*/();
	}
	return x*f;
}

template<typename T>
inline void write(T x,int f=1) {
	if(x<0) putchar/*_unlocked*/('-'),x=-x;
	if(x>9) write(x/10,0);
	putchar/*_unlocked*/(x%10+'0');
	if(f==1)putchar/*_unlocked*/('\n');
	if(f==2) putchar/*_unlocked*/(' ');
	return;
}

bool cmp(pair<int,int> x,pair<int,int> y) {
	int a=x.first,a1=x.second,b=y.first,b1=y.second;
	int maxn=max({a,a1,b,b1});
	if((a==maxn||a1==maxn)&&(b==maxn||b1==maxn)) return (a+a1)<(b+b1);
	else if(a==maxn||a1==maxn) return 0;
	else if(b==maxn||b1==maxn) return 1;
}
int  main() {
	int t=read();
	while(t--) {
		int n=read();
		int cnt=0;
		for(register int i = 1; i <= n; i++) a[i]= {read(),read()};
		sort(a+1,a+n+1,cmp);
		for(register int i = 1; i <= n; i++) cout<<a[i].first<<' '<<a[i].second<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：2)

考虑两个二元组 $(a_{1,1},a_{1,2})$ 与 $(a_{2,1},a_{2,2})$。由于二元组内部顺序无法改变，可以钦定 $a_{i,1}\le a_{i,2}$，同时为了方便，令 $a_{1,1}\le a_{2,1}$。

分类讨论：

- 形如 $(1,2),(3,4)$ 或 $(1,3),(2,4)$ 或 $(1,2),(1,3)$。此时显然 $(a_{1,1},a_{1,2})$ 在前更优。
- 形如 $(1,4),(2,3)$ 或 $(1,2),(1,2)$，此时无论谁在前都可以。
- 形如 $(1,3),(1,2)$，此时 $(a_{2,1},a_{2,2})$ 在前更优。

可以发现当 $a_{1,1}<a_{2,1}$ 时 $(a_{1,1},a_{1,2})$ 在前一定不劣。当 $a_{1,1}=a_{2,1}$ 时，若 $a_{1,2}\le a_{2,2}$ 则 $(a_{1,1},a_{1,2})$ 在前不劣，否则 $(a_{2,1},a_{2,2})$ 在前不劣。

于是按照二元组最小值为第一关键字，最大值为第二关键字升序排序即可。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef __int128 LL;
const ll maxn=200007,ee=1e18;
ll n,a[maxn][2],mn[maxn],mx[maxn],id[maxn];
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll T=1; cin>>T;
	for(;T--;){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i][0]>>a[i][1],id[i]=i;
			mn[i]=min(a[i][0],a[i][1]),mx[i]=max(a[i][0],a[i][1]);
		}
		sort(id+1,id+1+n,[&](ll x,ll y){
			if(mn[x]==mn[y]) return mx[x]<mx[y];
			else return mn[x]<mn[y];
		});
		for(int i=1;i<=n;i++) cout<<a[id[i]][0]<<" "<<a[id[i]][1]<<" "; cout<<"\n";
	}
	return 0;
}
```

---

## 作者：CEFqwq (赞：2)

简单题，真的有黄吗。

假设两个相邻的数对为 $(a,b)$ 和 $(c,d)$，我们要讨论它们之间的位置关系。

可以发现，$(a,b)$ 和 $(c,d)$ 交换位置对其余数对贡献不变。

然后来想一下 $(a,b)$ 和 $(c,d)$ 应该怎么排序。

观察样例，可以发现，对于所有数对 $(x,y)$，以 $x+y$ 为关键字排序。

那么假设 $u=a+b$，可以把数对转化为 $(a,u-a),(c,d)$。

现在假设 $u<c+d$，分类讨论 $a$ 和 $c,d$ 的大小关系与 $u-a$ 和 $c,d$ 的大小关系，归纳得出 $(a,u-a)$ 在 $(c,d)$ 前面一定不劣。

如果 $u=c+d$，发现与顺序无关。

然后就说证出来了。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x, y;
	bool operator < (node b){
			return this->x + this->y < b.x + b.y;
	}
}a[1000005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i].x >> a[i].y;
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; i++)
			cout << a[i].x << " " << a[i].y << " ";
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：wangyishan (赞：0)

一种比较自然的做法。

题意是排序这 $n$ 个 `pair` 使得逆序对数最小。

考虑交换一对 `pair` 会产生的逆序对数，这个可以直接暴力跑出来。

然后这还不够。我们还必须让最小值较小的尽量放在前面，这样会产生更少的逆序对。

然后就做完了。

思想好像叫“邻项交换法”，类似题目：P1080 国王游戏，ABC366F。

代码写得很丑。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define pii pair<int,int>
const int N=200050;
ll m,n,k;
pii a[500050];
int c[5];
int calc(pii x,pii y){
    c[1]=x.first,c[2]=x.second;
    c[3]=y.first,c[4]=y.second;
    int res=0;
    for(int i=1;i<=4;i++){
        for(int j=i+1;j<=4;j++){
            res+=(c[i]>c[j]);
        }
    }
    return res;
}
bool operator<(pii a,pii b){
    return calc(a,b)<calc(b,a);
}
bool operator==(pii a,pii b){
    return calc(a,b)==calc(b,a);
}
bool cmp(pii a,pii b){
    return a<b||(a==b&&(min(a.first,a.second)<min(b.first,b.second)));
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].first>>a[i].second;
    stable_sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)cout<<a[i].first<<" "<<a[i].second<<" ";
    cout<<endl;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：Introl (赞：0)

# CF2024C
## 题意简述
给定 $n$ 个二维数组，每个数组的长度为 $2$，将这 $n$ 个数组连接起来，要使得数组中的逆序对数量尽可能的少。
## 题意分析
题目要求排列数组使得逆序对尽可能少，对于其中一个数组，其可能贡献的逆序对数量为比 $a_{i,1}$ 小的个数 $x$，加上比 $a_{i,2}$ 小的个数 $y$，设 $cnt_i$ 为 $x+y$，之后只需要对数组 $cnt$ 排序输出结果即可。

**注意，只要 $a_{i,1}$ 和 $a_{i,2}$ 不相同，得出的结果应该减去 $1$，这是因为必然会有一个数比另一个数小，所以要排除掉。**

关于求解比当前数小的个数，我们可以使用二分查找函数``lower_bound``来求解。

## Code
```cpp
#pragma GCC optimize(1, 2, 3, "Ofast", "inline")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define ONLINE_JUDGE
#define MULTI_CASES
#define endl '\n'
const int MaxN = 2e5+100;
const int INF = 1e9;
const int mod=212370440130137957ll;
int T=1, N, M;
// int a[MaxN];
struct node{
    int x,y;
    int id;
}a[MaxN];
bool cmp1(node a,node b){
    return min(a.x,a.y)<min(b.x,b.y);
}
bool cmp2(node a,node b){
    return max(a.x,a.y)>max(b.x,b.y);
}
bool cmp(node a,node b){
    return a.id<b.id;
}
int cnt[MaxN];
inline void Solve()
{
	cin>>N;
    for(int i=1;i<=N;i++){
        cin>>a[i].x>>a[i].y;
        a[i].id=i;
    }
    vector<int>b;
    for(int i=1;i<=N;i++){
        b.push_back(a[i].x);
        b.push_back(a[i].y);
    }
    sort(b.begin(),b.end());
    for(int i=1;i<=N;i++){
        if(a[i].x<a[i].y){
            int x=lower_bound(b.begin(),b.end(),a[i].x)-b.begin();
            int y=lower_bound(b.begin(),b.end(),a[i].y)-b.begin()-1;
            cnt[i]=x+y;
        }   
        else{
            if(a[i].x>a[i].y){
                int x=lower_bound(b.begin(),b.end(),a[i].x)-b.begin()-1;
                int y=lower_bound(b.begin(),b.end(),a[i].y)-b.begin();
                cnt[i]=x+y; 
            }
            else{
                int x=lower_bound(b.begin(),b.end(),a[i].x)-b.begin();
                int y=lower_bound(b.begin(),b.end(),a[i].y)-b.begin();
                cnt[i]=x+y; 
            }
        }
    }
    for(int i=1;i<=N;i++){
        a[i].id=cnt[i];
    }
    sort(a+1,a+N+1,cmp);
    for(int i=1;i<=N;i++){
        cout<<a[i].x<<" "<<a[i].y<<" ";
    }
    cout<<endl;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

#ifdef MULTI_CASES
    cin >> T;
    while (T--)
#endif
       Solve();
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}

```

---

## 作者：Austin0116 (赞：0)

# 分析
决策性问题，DP 不好设计状态，考虑贪心。

一开始有两种贪心思路：一是比较 $(p_{1,1},p_{1,2})$ 与 $(p_{2,1},p_{2,1})$ 在前后的逆序对数量，少的排前面。二是直接比较两者较小的数，再比较两者较大的数，小的排前面。这两种贪心方法一是错的，二是对的。虽然二者都是考虑局部最优，但一方法没有传递性。反例在最后会给。

最后只需要按照上述方法排序即可。时间复杂度为 $O(n \log n)$。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
long long sum;
struct ha{
	int x,y;
	inline bool operator < (const ha &o) const{//按照上述规则排序
		if(min(x,y)!=min(o.x,o.y)) return min(x,y)<min(o.x,o.y);
		return max(x,y)<max(o.x,o.y);
	}
};
ha a[100005];
char ch;
inline void read(int &x){
	x=0;
	while(ch<48||ch>57) ch=getchar();
	while(ch>=48&&ch<=57){
		x=x*10+(ch^48);
		ch=getchar(); 
	}
}
void write(long long x){
	if(x>9) write(x/10);
	putchar((x%10)^48);
}
int main(){
	read(t);
	while(t--){
		read(n);
		for(int i=1;i<=n;i++) read(a[i].x),read(a[i].y);
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++) write(a[i].x),putchar(' '),write(a[i].y),putchar(' ');
		putchar('\n');
	}
	return 0;
}
```

# 反例

当有 $(2,2)(3,3)(1,5)$ 这三对时，由于 $(1,5)$ 与其余两者逆序对数量均相同，所以就有可能出现这样的情况：$(3,3)(1,5)(2,2)$。$(3,3)$ 在 $(1,5)$ 前面和 $(2,2)$ 在 $(1,5)$ 后面都可以。但 $(3,3)$ 却不能在 $(2,2)$ 前面，所以这个贪心算法是错误的。

---

## 作者：Louis_lxy (赞：0)

换一种理解方式，容易发现逆序对可以由两个方面构成，要么是二元组内的，要么是两个二元组之间的，二元组内的很好维护，考虑维护二元组之间的。

观察样例，容易发现如果将每一个为逆序对的二元组都反转，这样得到了若干区间，这些区间如果完全被包含（这里包含不包括端点重合的包含），造成 $2$ 的贡献，非常好理解，无论怎么排都是有一个大于后面两个或者一个小于前面两个，如果相交（这里不包括端点重合的相交，包括端点重合的包含），那么造成 $1$ 的贡献，也非常好理解，自己造几个样例手玩一下就知道了（非常抽象的是题目没给这类样例），如果都不满足上述两种情况，那么不造成贡献，这个自己玩一下就知道了。

然后上面只讨论了两个二元组的情况，注意到只要我们将相交（这里的定义与上文一致）的区间按左端点从小到大决定顺序即可，当然不交的也要按照左端点从小到大决定顺序，于是将所有区间按左端点排序，然后遍历，计算前面有多少个区间与这个区间相交和重合（这里的定义与上文相同），当然如果左端点相同就要按照右端点从小到大排序。

具体方法就是拿个树状数组维护右端点。然后就没了。

---

