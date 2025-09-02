# [ABC360C] Move It

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc360/tasks/abc360_c

$ 1 $ から $ N $ の番号がついた $ N $ 個の箱と $ 1 $ から $ N $ の番号がついた $ N $ 個の荷物があります。荷物 $ i $ $ (1\ \leq\ i\ \leq\ N) $ は箱 $ A_i $ の中にあり、重さは $ W_i $ です。

あなたは荷物を一つ選び、他の箱の中に移動させる操作を $ 0 $ 回以上繰り返し行うことができます。$ 1 $ 回の操作で移動させる荷物の重さが $ w $ であるとき、$ w $ のコストがかかります。

全ての箱に荷物が $ 1 $ つずつ入っている状態にするためにかかるコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{5} $
- $ 1\ \leq\ A_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ W_i\ \leq\ 10^{4} $ $ (1\ \leq\ i\ \leq\ N) $
- 入力はすべて整数
 
### Sample Explanation 1

以下の $ 2 $ 回の荷物の移動で、すべての箱に荷物が $ 1 $ つずつ入っている状態にすることができます。 - 荷物 $ 1 $ を箱 $ 2 $ から箱 $ 1 $ に移す。このとき、コストは $ 33 $ である。 - 荷物 $ 3 $ を箱 $ 3 $ から箱 $ 4 $ に移す。このとき、コストは $ 2 $ である。 この $ 2 $ 回の荷物の移動は合計 $ 35 $ のコストかかります。 $ 35 $ 未満のコストですべての箱に荷物が $ 1 $ つずつ入っている状態にすることはできないため、 $ 35 $ を出力します。

## 样例 #1

### 输入

```
5
2 2 3 3 5
33 40 2 12 16```

### 输出

```
35```

## 样例 #2

### 输入

```
12
3 6 7 4 12 4 8 11 11 1 8 11
3925 9785 9752 3587 4013 1117 3937 7045 6437 6208 3391 6309```

### 输出

```
17254```

# 题解

## 作者：Little_x_starTYJ (赞：8)

### 解题思路
对于每个箱子，都有两种状态，一种是里面装有物品，另一种是里面没有物品。

令 $num_i$ 为第 $i$ 个箱子里面的物品数量。

由于物品与箱子的数量都是 $N$ 个，所以我们必须得从装有多个物品的箱子里面取出 $num_i-1$ 个物品放在未装物品的箱子里。

题目还要求这些物品的重量和最小，因此我们可以尝试贪心。众所周知，对于 $n$ 个满足递增的数字 $a_1,a_2,\cdots,a_n$，取 $n-1$ 个数字使得这些数字的和最小，$\sum_{i=1}^{n-1} a_i$ 总是最小的。

因此，我们可以考虑第 $i$ 个箱子里面的物品重量最大的不进行移动，重量较小的就进行移动，最后统计移动了的物品的重量和即可。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct node {
	int a, w;
} a[100010];
int ans;
vector<int> v[100010];
signed main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i].a;
	for (int i = 1; i <= n; i++)
		cin >> a[i].w;
	for (int i = 1; i <= n; i++) {
		v[a[i].a].push_back(a[i].w);
	}
	for (int i = 1; i <= n; i++) {
		if (v[i].size() > 0)
			sort(v[i].begin(), v[i].end());
		if (v[i].size() > 0)
			for (int j = 0; j < v[i].size() - 1; j++)
				ans += v[i][j];
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Hughpig (赞：2)

显然一个箱子里最多只能装一个物品，那么物品数为 $x\ (x>1)$ 的箱子都要移走 $x-1$ 个物品。

贪心的考虑，挑选最轻的 $x-1$ 个物品移走（这样总代价最小），也就是去掉最重的物品，其他都移走。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

constexpr int N=1e5+9;

int n,a[N],w[N],ans;
vector<int> qwq[N];

int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)cin>>w[i],qwq[a[i]].emplace_back(w[i]);
    for(int i=1;i<=n;++i)sort(qwq[i].begin(),qwq[i].end());
    for(int i=1;i<=n;++i){
    	if(qwq[i].size()<2)continue;
    	for(int j=0;j<qwq[i].size()-1;++j)ans+=qwq[i][j];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：toolong114514 (赞：2)

# AT_abc360_c [ABC360C] Move It 题解
## 题面翻译
有 $n$ 个物品，$n$ 个盒子，每个物品用两个属性 $a_i$，$w_i$ 表示。$a_i$ 表示第 $i$ 个物品所在盒子的编号，$w_i$ 表示第 $i$ 个物品的质量。

你可以对任意物品操作任意次，将该物品从当前盒子搬到另一个盒子，代价为这个物品的质量。

求使每个盒子都恰好有一个物品的最小代价。
## 解题思路
简单的贪心，颜色大概在橙到黄之间。

在最优的操作下，每个物品之多被搬运一次。由于对搬运没有限制，那么搬运多次的行为一定可以化为搬运一次，在题面给定 $1\le w_i\le10^4$（$w_i$ 是正整数），所以搬运多次一定不优。

接下来要决定搬运的物品。

容易发现，按质量从小到大选物品是最优的。但是在选择的时候，有一种情况是不能搬运物品的：当前物品所在盒子只有它一个。

那么用一个结构体把物品原来所在的盒子编号及其质量绑起来，然后按质量从小到大排序，并维护一个记录当前盒子剩余物品数的数组，顺序扫描一遍，能取就取即可。
## 参考代码
```cpp
#include<algorithm>
#include<iostream>
using namespace std;
const int N=1e5+10;
struct node{
	int a,w;
}arr[N];
int cnt[N];
bool cmp(node pre,node nxt){
	return pre.w<nxt.w;
}
int n,ans;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i].a;
		cnt[arr[i].a]++;
	}
	for(int i=1;i<=n;i++){
		cin>>arr[i].w;
	}
	sort(arr+1,arr+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(cnt[arr[i].a]>1){
			ans+=arr[i].w;
			cnt[arr[i].a]--;
		}
	}
	cout<<ans;
	return 0;
}
```
[本代码可以通过 AT 的评测。](https://www.luogu.com.cn/record/163539950)

Written by [toolong114514](www.luogu.com/user/477821) on 2024/7/1.

---

## 作者：Redamancy_Lydic (赞：2)

## 背景

机房大佬掉大分了，~~乐~~悲。

## 题意

给你几个箱子和每个箱子里装有的东西 $a$ 和对应的重量 $w$，现在要让每个箱子里都装有一个东西，每次可以移动任意一个箱子中的任意一个东西，代价为它的重量，问最小代价。

## 分析

贪心。首先最终状态里所有箱子一定只有一个东西，那么对于所有装东西的箱子，若装有 $x$ 个东西，那么一定要把它的 $x-1$ 个东西拿走。

由于东西数量和箱子数量相等，那么我们无需考虑每个箱子中的东西该放到那些箱子里，因为空箱子的数量一定是符合的。

那么就把每个箱子中的东西统计出来，从小到大排序，每个箱子的代价就是前 $x-1$ 个东西的重量之和。

## Code

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
using namespace std;
using namespace  __gnu_pbds;
//gp_hash_table<string,int>mp2;
//__gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> q;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
int n;
int a[maxn],w[maxn];
vector<int> v[maxn];
int ans=0;
bool f[maxn];
signed main()
{
//  freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		f[a[i]]=1;
	}
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=n;i++)
	{
		v[a[i]].push_back(w[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i])
		{
			sort(v[i].begin(),v[i].end());
			for(int j=0;j<v[i].size()-1;j++)
			{
				ans+=v[i][j];
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：nightwatch.ryan (赞：1)

### 思路
一个盒子里可以有多个物品，求每个盒子里都有一个物品的最小花费。

显然的，要求最小那么花费最大的物品就得留在原来盒子里，其他的物品再去进行挪动。

那么答案就是 $\sum_{i=1}^{n} W_i - \sum_{i=1}^{n} maxw_i$，其中 $W_i$ 是原来每个物品的花费，$maxw_i$ 是每个盒子里物品的最大花费。
### 代码
```cpp
#include<iostream>
#include<climits>
#define int long long
#define N 100005
int n,a[N],w[N];
int max_w[N],sum_w;
signed main(){
	std::cin>>n;
	for(int i=1;i<=n;i++)std::cin>>a[i];
	for(int i=1;i<=n;i++){
		std::cin>>w[i];
		sum_w+=w[i];
		max_w[a[i]]=std::max(max_w[a[i]],w[i]);
	}
	int sum_maxw=0;
	for(int i=1;i<=n;i++)
		sum_maxw+=max_w[i];
	std::cout<<sum_w-sum_maxw;
} 
```

---

## 作者：Special_Tony (赞：1)

# 思路
要使每个盒子里只有一个物品，则必须只留下一个物品不动，其它都移到空盒子里。显然，我们肯定留下最大的不动，其它全都移走。所以，我们可以把相同盒子里的东西放进一个 vector 排序，最后把除了最大的物品全都加到代价里。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, a[100005], x, sum;
vector <int> v[100005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
		cin >> a[i];
	for (int i = 0; i < n; ++ i)
		cin >> x, v[a[i]].emplace_back (x);
	for (int i = 1; i <= n; ++ i) {
		sort (v[i].begin (), v[i].end ());
		for (int j = 0, m = (int) v[i].size () - 1; j < m; ++ j)
			sum += v[i][j];
	}
	cout << sum;
	return 0;
}
```

---

## 作者：Tracy_Loght (赞：0)

## 思路：

因为要使每一个格子中只有**一个**数，且移动一次的消耗是物品的重量，考虑用 struct 排序，只保留不用移动的，因为肯定想移动尽量**重量少**的，所以**不会移动**的就是每个格子中已有的**最大值**。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[100001],jl,k;
struct op{int a,b;};
op o[100001];
int cmp(op x,op y){return x.a<y.a;}//以箱子编号排序
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>o[i].a;
	for(int i=1;i<=n;i++) cin>>o[i].b,k+=o[i].b;
	std::sort(o+1,o+n+1,cmp);//排序
	for(int i=1;i<=n;i++)f[o[i].a]=max(f[o[i].a],o[i].b);//求值
	for(int i=1;i<=100000;i++) jl=jl+f[i];
	cout<<k-jl;
	return 0;
}
```

---

## 作者：_colin1112_ (赞：0)

## 思路

贪心地想，我们移动物品所需的代价越少越好，所以我们只需对有着大于一个物品的箱子进行排序，依次减去需要代价最小的一个物品，减到每个箱子内只有一个物品即可。

## Code

```c++
#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;
const int E = 1e6 + 5;
ll n;
ll a[E], w[E];
vector<ll> cnt[E];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i <= n; i++)
        cnt[a[i]].push_back(w[i]);
    for (int i = 1; i <= n; i++)
        if (cnt[i].size() > 1)
            sort(cnt[i].begin(), cnt[i].end(), greater<ll>());//对有着大于一个物品的箱子进行排序
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (cnt[i].size() > 1)
            while (1)
            {
                ans += *(cnt[i].end() - 1);//计算代价
                cnt[i].pop_back();//将最小的一个去除
                if (cnt[i].size() == 1)
                    break;//减到箱子内只有一个物品为止
            }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：tzzl3035 (赞：0)

# AT_abc360_c 题解
### 题目大意
有 $N$ 个物品的盒子，第 $i$ 个物品在第 $A_i$ 个盒子中，移动成本为 $W_i$。问使每一个盒子中只有一个物品的最少移动成本。
### 思路——贪心
如果一个盒子中有物品，就留下成本最高的，其余的物品将成本计入答案即可。
### 代码
``` c++
#include <bits/stdc++.h> // 万能头
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
   
	// 输入
	int N, A[100002]={0}, Wi;
	vector<int> box[100002]; // 存储方便且节省空间
	cin >> N;
	for(int i = 0; i < N; i++) cin >> A[i];
	for(int i = 0; i < N; i++) {
		cin >> Wi;
		box[A[i]].push_back(Wi); // 直接插入每一盒中物品的成本
	}
	for(int i = 1; i <= N; i++) {
		sort(box[i].begin(), box[i].end()); // 排序
	}
 	// 将每一个盒子中除成本最高的以外的物品成本加入答案
	int ans = 0;
	for(int i = 1; i <= N; i++) {
		if(box[i].size() == 0) continue;
		for(int j = 0; j < box[i].size()-1; j++) {
			ans = ans + box[i][j];
		}
	}

	cout << ans;
	
	return 0;
}

```
### [RESULT](https://www.luogu.com.cn/record/163567911)

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc360_c)
### 思路
我们可以将这些数字先按 $a$ 从小到大排序，如果相同，再按照 $w$ 从小到大排序，如果在一个框内有 $n$ 个元素，那么我们肯定是移动最小的 $n-1$ 个元素，所以我们枚举每一个位置 $i$，如果 $a_i=a_{i-1}$，那么我们就将答案加上一个 $w_{i-1}$，因为我们肯定是将小的那个元素移除。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct jie
{
	int w;
	long long r;
}a[100005];
bool cmp(jie s1,jie s2)
{
	if (s1.w!=s2.w)
	{
		return s1.w<s2.w;
	}
	else
	{
		return s1.r<s2.r;
	} 
}
int main()
{
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i].w;
	}
	for (int i=1;i<=n;i++)
	{
		cin>>a[i].r;
	}
	a[0].w=-1;
	sort(a+1,a+n+1,cmp);
	long long ans=0;
	for (int i=1;i<=n;i++)
	{
		if (a[i].w==a[i-1].w)
		{
			ans=ans+a[i-1].r;
		}
	}
	cout<<ans<<endl;
} 
```

---

## 作者：Peaky (赞：0)

建议评黄。  
按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/AT_abc360_c)。
### 题目大意
已知有 n 个果篮，每个水果都有一个重量 $w_i$，每搬运一次会消耗 $w_i$ 的体力，我们要做的是在**消耗最小体力**的前提下，使得每一个果篮里都装有一个水果。   
### 思路
很容易想到双指针，就像酱紫：
```cpp
int idx=1;
for(int i=1;i<=n;i++){
	if(t[a[i].y]>1){
		while(t[idx]) idx++;
		t[a[i].y]--;
		t[idx]++;
		ans+=a[i].x;
	}
}
```
$t_i$ 统计的是第 i 个果篮里水果的个数，$a_i$ 是一个 pair 类型的数组，其中第一个参数对应原题目的 $w_i$，第二个参数对应原题目的 $a_i$。  
指针 idx 指向的是没有水果的果篮，i 指向的是第 i 个水果所在的果篮的位置。可以简单的发现，当 $w_i$ 是**单调递增的**，就可以很容易得出最小值，所以我们可以对 $w_i$ 排序。

### 实现
由于两个数组是绑定的，所以可以考虑用 pair 实现。

### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int n,t[N],x,idx=1;
ll ans;
pii a[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x,t[x]++,a[i].y=x;
	for(int j=1;j<=n;j++) cin>>a[j].x;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(t[a[i].y]>1){
			while(t[idx]) idx++;
			t[a[i].y]--;
			t[idx]++;
			ans+=a[i].x;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：int_stl (赞：0)

一道贪心题。

我们发现，题目让我们使每个箱子都有 $1$ 个物品，这就意味着对于每个非空的箱子，要移走的物品数量是箱子装的物品数量减 $1$。

为了让总代价尽量小，我们每次取的时候要取最小值，这个操作用优先队列维护即可。

时间复杂度 $O(n \log n)$，实际表现则更快。

代码如下：

```cpp
priority_queue <int> q[100006];
ll n, a[100005], w[100005];
int main() {
	read(n);
	FORL(i, 1, n, 1) {
		read(a[i]);
	}
	FORL(i, 1, n, 1) {
		read(w[i]), q[a[i]].push(-w[i]);
	}
	ll min_cost = 0;
	FORL(i, 1, n, 1) {
		while (q[i].size() > 1) {
			min_cost += -q[i].top();
			q[i].pop();
		}
	}
	write(min_cost);
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意
给出 $N$ 个箱子和物品，第 $i$ 个物品放在第 $a_i$ 个箱子中，重量为 $w_i$，可以将一个物品移动到另一个箱子中，会花费 $w_i$，现在想通过一些操作让每个箱子只有一个物品，问操作后的花费最小值。

## 解题思路
很明显，如果一个箱子内有 $x$ 个物品，那么有 $x-1$ 个物品都能被移动到其他的箱子中，因为要求的是花费最小值，所以与最终移动到的箱子编号无关。而我们想要求花费最小值，本质上就是求一个有 $x$ 个物品的箱子中 $x-1$ 个 $w_i$ 的和的最小值，也就是除了 $w_{i_{\max}}$ 外其余 $x-1$ 个物品 $w_i$ 之和。

这样，我们只需要输入 $w_i$ 的时候顺便求每个最大值和所有 $w_i$ 的总和，最后用总和减去所有最大值即可。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a[100001],b,mx[100001],sum;

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	
	for(int i=1; i<=n; ++i)
	{
		scanf("%d",&b); sum+=b;
		mx[a[i]]=max(mx[a[i]],b);
	}
	
	for(int i=1; i<=n; ++i) sum-=mx[i];
	printf("%d",sum);
    return 0;
}
```

---

## 作者：jiangruibo (赞：0)

### 思路：
我们可发现，若它们的**编号相同**，我们就只会把**最大的成本**的那个编号留下，其他都会变成另外的编号，我们不用管他到底变成了那几个编号，因为**总的个数**都是一样的，所以答案就是被变过的成本和，这样就能保证最小。

### 代码：
```
#include <bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define int long long
#define endl "\n"
#define ull unsigned long long
#define write(n,x) cout<<setprecision(n)<<fixed<<x
typedef long long LL;
using namespace std;

vector<int> v[100010];
int a[100010];
int b[100010];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=n;i++)
	{
		v[a[i]].push_back(b[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(v[i].size()==0) continue;
		int sum=0;
		int maxn=-1e9;
		for(int j=0;j<v[i].size();j++)
		{
			sum+=v[i][j];
			maxn=max(maxn,v[i][j]);
		}
		ans=ans+(sum-maxn);
	}
	cout<<ans<<endl;
	return 0;
}
/*
 */



```

---

## 作者：wfirstzhang (赞：0)

# ABC360C
## 思路
如果模拟，那么将会移动很多不需要移动的箱子，并且时间复杂度很高。

如果一个位置上只有 $1$ 个箱子，那么不需要移动。而需要把一个位置上有多个的箱子移动到空位置上，这样不需移动其他箱子，没有多余的费用。所以不需要模拟每一步移动，而只需要考虑把一个位置上有多个的箱子移走。

考虑贪心。在一个位置上的多个箱子，移走不会影响以后的箱子移动。而移动同一些箱子，根据加法交换律，也不会影响到全局。符合贪心条件之局部最优解导致全局最优解。

移动同一个位置上的箱子，先移动花费最小的，这就是局部最优解。直到该位置上只有 $1$ 个箱子，就无需再移动。

做法说完了，实现请看代码。

## AC Code
```cpp
#include <algorithm>
#include <iostream>
#include <vector>
struct box{ int index; int weight; };
int compute(std::vector<int>& arr);
int main() {
    using namespace std;
    int n, sum = 0;
    cin >> n;
    vector<box> arr(n); //存储每个箱子的信息
    for(int i = 0; i < n; i++)
        cin >> arr[i].index;
    for(int i = 0; i < n; i++)
        cin >> arr[i].weight;
    vector<vector<int>> bucket(n + 1); //存储每个箱子所在位置上箱子的信息
    for(int i = 0; i < n; i++)
        bucket[arr[i].index].push_back(arr[i].weight); //桶
    for(int i = 1; i <= n; i++)
        sum += compute(bucket[i]);
    cout << sum << endl;
    return 0;
}
int compute(std::vector<int> &arr) {
    if(arr.size() <= 1) //如果只有一个箱子或者没有箱子，不需要考虑
        return 0;
    std::sort(arr.begin(), arr.end(), std::greater<int>()); //从大到小排序
    int sum = 0;
    while(arr.size() > 1) {
        sum += arr.back(); //从后往前找最小值
        arr.pop_back();
    }
    return sum; //该位置移动到最小花费
}
```

---

## 作者：xzz_0611 (赞：0)

[洛谷题目传送门](/problem/AT_abc360_c)  
[AtCoder 传送门](https://atcoder.jp/contests/abc360/tasks/abc360_c)
### 题目大意
有 $N$ 个箱子和 $N$ 件物品，编号均为 $1\sim N$。

第 $i$ 件物品放置在第 $A_i$ 个箱子中，重量为 $W_i$。

你可以将一件物品放置到另一个箱子里，而这件物品的重量就是这次操作的代价。

请问要让每个箱子都有意见物品至少要多少代价。
### 思路
众所周知，想要让代价最少，那么那些能不移动的就都不要移动，所以，如果某个箱子只有一个物品了，那么这个物品就不要移动了。

然后，对于有不止一个物品的箱子，想要达到题目的要求，就要让这个箱子只留下一个物品，剩下的全移走，同时，还要使代价最少。在这个箱子里，要移走的物品数量是不变的，所以要让代价最少，就只能让移走的物品尽可能轻，故要保留这个箱子中最重的一个。

为了方便，可以使用结构体，再进行一边排序，具体的排序方法如下：
- 先按所在箱子编号从小到大排序，若一样，再按重量从小到大排序。

这样就可以使同一个箱子的物品在数组中的位置挨在一起，并且更快找出一个箱子中最重的那一个物品。
### Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct stru{//结构体
	int w,a;
}arr[100000];
bool cmp(stru x,stru y) {//sort排序自定义规则
	if(x.a!=y.a) return x.a<y.a;
	return x.w<y.w;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,ans=0;
	cin>>n;
	for(int i=0;i<n;++i) cin>>arr[i].a;
	for(int i=0;i<n;++i) cin>>arr[i].w;
	sort(arr,arr+n,cmp);//排序
	for(int i=0;i<n;++i) if(i<n-1/*防止数组出界*/&&arr[i].a==arr[i+1].a/*如果下一个也是这个箱子说明这个不是最重的物品*/) ans+=arr[i].w;//累加答案
	cout<<ans;
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

[[ABC360C] Move It](https://www.luogu.com.cn/problem/AT_abc360_c)

简单 C。

记 $cnt_i$ 为第 $i$ 个箱子中现有的物品数量。如果 $cnt_{a_i}>1$，则可以移动第 $i$ 个物品。

那么将物品按照重量从小到大排序。对于第 $i$ 个物品，如果 $cnt_{a_i}>1$，则将 $a_i$ 移走，$ans$ 加上 $w_i$。

最后输出 $ans$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int n, cnt[N], ans;
struct node {
	int id, w;
}a[N];
bool operator < (node x, node y) {
	return x.w < y.w;
}
signed main ()
{
	ios::sync_with_stdio (false);
	cin.tie (0); cout.tie (0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].id, cnt[a[i].id]++;
	for (int i = 1; i <= n; i++) cin >> a[i].w;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		if (!cnt[i]) sum ++;
	}
	sort (a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		if (sum == 0) break;
		if (cnt[a[i].id] > 1) {
			ans += a[i].w;
			sum--;
			cnt[a[i].id]--;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：__PJL__ (赞：0)

### 思路

一眼贪心。

用 vector 存每个物品的重量。

接着看每个箱子，每次移动物品时，一定只能留下一个物品，所以我们留下最重的物品，剩下的物品全部搬走即可。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 1;

long long n, ans, a[MAXN];
vector<long long> c[MAXN];

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1, w; i <= n; i++) {
		cin >> w;
		c[a[i]].push_back(w);
	}
	for(int i = 1; i <= n; i++) {
		c[i].push_back(-1);
		sort(c[i].begin(), c[i].end());
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < c[i].size() - 1; j++) {
			ans += c[i][j];
		}
	}
	cout << ans;
	return 0;
} 
```

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://atcoder.jp/contests/abc360/tasks/abc360_c)

# 思路

一眼贪心，记录 $d_i$ 为当前位置的数量，如果 $d_i \ge 2$ 的话，则可以移动第 $i$ 个物品。

注意:这里 $d_i$ 为 $a_i$ 所在数组。

那么将物品按照重量**从小到大**排序。对于第 $i$ 个物品，只留下一个**最重**的物品，搬走其他即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n,sum,d[maxn];
struct node
{
	int a,w;
}xs[maxn];
inline bool cmp(node x,node y)
{
	if(x.a == y.a) return x.w < y.w;
	else return x.a < y.a;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>xs[i].a;
	}
	for(int i = 1;i <= n;i++)
	{
		cin>>xs[i].w;
	}
	sort(xs + 1,xs + 1 + n,cmp);
	for(int i = 1;i <= n;i++)
	{
		d[xs[i].a]++;
	}
	for(int i = 1;i <= n;i++)
	{
		if(d[xs[i].a] >= 2) sum += xs[i].w,d[xs[i].a]--;
	}
	cout<<sum;
	return 0;
}

```

---

## 作者：Breath_of_the_Wild (赞：0)

有点像某年蓝桥杯的题目：平均。

题意：每个箱子里原本装有一些东西，先要将一些东西拿出来放到别的箱子里。移动每一个物品都有一个代价。求变为每个箱子只装一个物品所需要的最小的代价。

贪心。对于每一个箱子，如果它不够数量（$0$ 个），就等着别的箱子里的的东西移过来，可以不用动；正好 $1$ 个，也不用动；如果大于 $1$ 个，记现在的物品个数为 $a_i$ 个，就取箱子里面最小代价的 $a_i-1$ 个权值累加就可以了。具体这些物品到了哪里我们不用管。

代码较简单，不放这里了。非要看的话，就点[这里](https://atcoder.jp/contests/abc360/submissions/55075101)。

---

## 作者：Size_OIer (赞：0)

如果当前箱子里的物品不止一个，那么就将除了最重物品之外的所有物品移走，然后统计答案。  
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5;
int n,a[maxn],w[maxn];
vector<int> v[maxn];
int ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<=n;i++) v[a[i]].push_back(w[i]);
    for(int i=1;i<=n;i++){
        if(v[i].size()>1){
            sort(v[i].begin(),v[i].end());
            for(int j=0;j<v[i].size()-1;j++) ans+=v[i][j];
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

思路其实比较简单，显然的贪心就行。我们的做法是记录下每个盒子里所有的物品，然后从每个盒子里把除最重物品以外的所有物品都拿出去，不用考虑拿到哪里。答案为所有搬出的物品的重量和。

这里给出两种实现方法：

- 开一个数组 $F$，$F_i$ 表示第 $i$ 个盒子里装的物品重量和。再开一个数组 $M$，$M_i$ 表示第 $i$ 个盒子里装的物品重量的最大值。答案为所有 $F_i-M_i$ 的和。

- 将元素序列按照装的盒子编号为第一关键字、重量为第二关键字排序，然后遍历数组，答案为累加每一个和后边元素装的盒子一样的元素的重量。

这里选用了第二种方法。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct node{
	int a,b;
}f[1000005];
bool cmp(node a,node b){
	if(a.a!=b.a) return a.a<b.a;
	else return a.b<b.b;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>f[i].a;
	for(int i=1;i<=n;i++) cin>>f[i].b;
	sort(f+1,f+1+n,cmp);
	int sum=0;
	for(int i=1;i<=n;i++) if(f[i].a==f[i+1].a) sum+=f[i].b;
	cout<<sum;
	return 0;
}
```

---

