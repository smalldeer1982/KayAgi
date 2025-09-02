# [ABC391F] K-th Largest Triplet

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc391/tasks/abc391_f

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,A_N),\ B=(B_1,B_2,\ldots,B_N),C=(C_1,C_2,\ldots,C_N) $ および整数 $ K $ が与えられます。

$ 1\leq\ i,j,k\leq\ N $ を満たす整数 $ i,j,k $ の選び方 $ N^3 $ 通りそれぞれに対して $ A_iB_j+B_jC_k+C_kA_i $ の値を計算したとき、その中で大きい方から $ K $ 番目の値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ K\leq\ \min(N^3,5\times\ 10^5) $
- $ 1\leq\ A_i,B_i,C_i\leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ N^3=8 $ 個の整数の値は以下の通りです。 - $ (i,j,k)=(1,1,1) $ : $ A_1B_1+B_1C_1+C_1A_1=1\times\ 3+3\times\ 5+5\times\ 1=23 $ - $ (i,j,k)=(1,1,2) $ : $ A_1B_1+B_1C_2+C_2A_1=1\times\ 3+3\times\ 6+6\times\ 1=27 $ - $ (i,j,k)=(1,2,1) $ : $ A_1B_2+B_2C_1+C_1A_1=1\times\ 4+4\times\ 5+5\times\ 1=29 $ - $ (i,j,k)=(1,2,2) $ : $ A_1B_2+B_2C_2+C_2A_1=1\times\ 4+4\times\ 6+6\times\ 1=34 $ - $ (i,j,k)=(2,1,1) $ : $ A_2B_1+B_1C_1+C_1A_2=2\times\ 3+3\times\ 5+5\times\ 2=31 $ - $ (i,j,k)=(2,1,2) $ : $ A_2B_1+B_1C_2+C_2A_2=2\times\ 3+3\times\ 6+6\times\ 2=36 $ - $ (i,j,k)=(2,2,1) $ : $ A_2B_2+B_2C_1+C_1A_2=2\times\ 4+4\times\ 5+5\times\ 2=38 $ - $ (i,j,k)=(2,2,2) $ : $ A_2B_2+B_2C_2+C_2A_2=2\times\ 4+4\times\ 6+6\times\ 2=44 $ これらを値の降順に並べ替えると $ (44,38,36,34,31,29,27,23) $ となるため、 大きい方から $ 5 $ 番目の値は $ 31 $ です。

## 样例 #1

### 输入

```
2 5
1 2
3 4
5 6```

### 输出

```
31```

## 样例 #2

### 输入

```
3 10
100 100 100
100 100 100
100 100 100```

### 输出

```
30000```

## 样例 #3

### 输入

```
5 54
800516877 573289179 26509423 168629803 696409999
656737335 915059758 201458890 931198638 185928366
140174496 254538849 830992027 305186313 322164559```

### 输出

```
689589940713840351```

# 题解

## 作者：abensyl (赞：14)

## 思路

显然，我们应该将 $A$，$B$，$C$ 三个数列从大到小排序。

考虑有哪些元素可能成为前 $K$ 大的，我们把所有 $A_iB_j+B_jC_k+C_kA_i$ 可能是前 $k$ 大的三元组 $(i,j,k)$ 都找出来。

对于三元组 $(i_0,j_0,k_0)$，显然，对于所有三元组 $(i,j,k)$，满足 $i\le i_0$ 且 $j\le j_0$ 且 $k\le k_0$，必然 $A_{i_0}B_{j_0}+B_{j_0}C_{k_0}+C_{k_0}A_{i_0}\le A_iB_j+B_jC_k+C_kA_i$，所以如果 $i_0\times j_0\times k_0>K$，那么该三元组必然不可能是前 $K$ 大的。

我们只需要枚举所有三元组 $(i,j,k)$ 满足 $i\times j\times k\le K$ 即可。

浅算一下时间复杂度，两个调和级数，就是 $O(n\log^2 n)$，可以通过。

## 代码
```cpp
const int N = 5e5+5, M = 5e5+5;
int a[N],b[N],c[N];
bool cmp(int a,int b) { return a>b; }
vector<int> v;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n,k; cin>>n>>k;
    rep(i,1,n) cin>>a[i]; sort(a+1,a+n+1,cmp);
    rep(i,1,n) cin>>b[i]; sort(b+1,b+n+1,cmp);
    rep(i,1,n) cin>>c[i]; sort(c+1,c+n+1,cmp);
    for(int i=1;i<=k&&i<=n;++i) {
        for(int j=1;i*j<=k&&j<=n;++j) {
            for(int l=1;i*j*l<=k&&l<=n;++l) {
                v.push_back(a[i]*b[j]+b[j]*c[l]+c[l]*a[i]);
            }
        }
    }
    nth_element(v.begin(),v.begin()+k-1,v.end(),cmp);
    cout<<v[k-1]<<'\n';
    return 0;
}
```

[完整代码与 AC 记录](https://atcoder.jp/contests/abc391/submissions/62295530)。

---

## 作者：Double_Light (赞：4)

介绍一种更简单的写法。

考虑二分答案，很容易就可以写出 $O(n^3\log\text{ans})$ 的写法，在 `check` 函数中枚举 $i,j,k$。

考虑剪枝优化枚举：首先将 $a,b,c$ 三个数组降序排序，令 $(i,j,k)$ 表示 $a_ib_j+b_jc_k+c_ka_i$。

如果枚举到一个 $i$，若 $(i,1,1)<\text{mid}$，则结束循环；如果枚举到一个 $j$，若 $(i,j,1)<\text{mid}$，则结束循环；如果枚举到一个 $k$，若 $(i,j,k)<\text{mid}$，则结束循环；若已经枚举到 $K$ 个数，则返回 $1$。

容易发现每次进入循环都能找到至少一个解，而找到 $K$ 个解之后就会结束函数，所以枚举的时间复杂度是 $O(K)$。

总时间复杂度 $O(K\log\text{ans})$，答案最大为 $3\times10^{18}$，可以通过本题。

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,k;
int a[200005],b[200005],c[200005];
int ans;
bool check(int x){
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i]*b[1]+b[1]*c[1]+c[1]*a[i]<x)break;
		for(int j=1;j<=n;j++){
			if(a[i]*b[j]+b[j]*c[1]+c[1]*a[i]<x)break;
			for(int l=1;l<=n;l++){
				if(a[i]*b[j]+b[j]*c[l]+c[l]*a[i]>=x)cnt++;
				else break;
				if(cnt>=k)return 1;
			}
		}
	}
	return 0;
}
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+n+1,cmp);
	sort(c+1,c+n+1,cmp);
	int l=1,r=3e18,mid;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：nightwatch.ryan (赞：3)

### Analysis
先将 $A, B, C$ 三个数组降序排序。

下面设 $f(i,j,k) = A_iB_j+B_jC_k+C_kA_i$。

显然一定有：
$$f(i, j, k) \geq f(i+1,j,k),f(i,j+1,k),f(i,j,k)$$。

思考：直接求第 $K$ 大难以实现，怎么办？可以考虑从第一大逐渐拓展到第 $K$ 大。

显然这个过程可以使用 `bfs` 来实现，每一次，将 $(i+1,j,k,f(i+1,j,k)),(i,j+1,k,f(i,j+1,k)),(i,j,k+1,f(i,j,k+1))$ 放入优先队列。注意这个优先队列按照 $f(i,j,k)$ 的值降序排序。

这样，队列顶部一定是最靠近第 $K$ 小的 $f(i,j,k)$。

最后，优先队列第 $K$ 次弹出元素时，弹出的这个元素的 $f(i,j,k)$ 的值即为答案。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N], b[N], c[N];
int calc(int i, int j, int k){ return a[i] * b[j] + b[j] * c[k] + c[k] * a[i]; }
struct Node{ 
    int i, j, k, val;
    bool operator < (const Node &node) const {
        if(val != node.val) return val < node.val;
        if(i != node.i) return i < node.i;
        if(j != node.j) return j < node.j;
        return k < node.k;
    } 
};
map<Node, int> vis;
priority_queue<Node> q;
signed main(){
    cin.tie(0) -> sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for(int i = 1; i <= n; i ++) cin >> a[i];
    sort(a + 1, a + 1 + n, greater<int>());
    for(int i = 1; i <= n; i ++) cin >> b[i];
    sort(b + 1, b + 1 + n, greater<int>());
    for(int i = 1; i <= n; i ++) cin >> c[i];
    sort(c + 1, c + 1 + n, greater<int>());
    q.push({1, 1, 1, calc(1, 1, 1)});
    int cnt = 0;
    while(cnt < k){
        Node cur = q.top(); q.pop();
        if(!vis[cur]){
            vis[cur] = 1; cnt ++;
            if(cnt == k) return cout << cur.val << endl, 0;
            if(cur.i < n) q.push({cur.i + 1, cur.j, cur.k, calc(cur.i + 1, cur.j, cur.k)});
            if(cur.j < n) q.push({cur.i, cur.j + 1, cur.k, calc(cur.i, cur.j + 1, cur.k)});
            if(cur.k < n) q.push({cur.i, cur.j, cur.k + 1, calc(cur.i, cur.j, cur.k + 1)});
        }
    }
}
```

---

## 作者：littlebug (赞：3)

## Solution

优先队列板子题。

为了方便，设 $f(i,j,k) = a_i b_j + b_j c_k + c_k a_i$，就是题面中那个式子。

显然，对于一组 $(i,j,k)$，在所有的可能组合中比 $f(i,j,k)$ 小的最大的数，一定是 $f(i-1,j,k) , f(i,j-1,k) , f(i,j,k-1)$ 中的一个。

所以我们先把 $a,b,c$ 从大到小排序，然后先把 $f(1,1,1)$ 丢进优先队列（大根堆）里。每次取队头 $f(i,j,k)$，然后把 $f(i-1,j,k) , f(i,j-1,k) , f(i,j,k-1)$ 丢进优先队列里即可，这样重复 $K$ 次（题面中的那个 $K$），最后一次的结果就是答案。

注意判断一个状态是否访问过，因为某只唐诗忘记判这个而被硬控 2min，最后在赛后 43s 过掉了这道题。

![](https://s21.ax1x.com/2025/02/01/pEZQh34.png)

## Code

```cpp
const int A=1e12,B=1e6;

int n,k,a[MAXN],b[MAXN],c[MAXN];
priority_queue <pii> q;
set <int> vis;

signed main()
{
    read(n,k),_::r(a,n),_::r(b,n),_::r(c,n);
    sort(a+1,a+n+1,greater<int>()),sort(b+1,b+n+1,greater<int>()),sort(c+1,c+n+1,greater<int>());

    auto calc=[](int i,int j,int k){return a[i]*b[j]+b[j]*c[k]+c[k]*a[i];};
    auto c2=[](int i,int j,int k){return i*A+j*B+k;};
    
    q.emplace(calc(1,1,1),c2(1,1,1));
    --k;
    pii ck; int x,y,z;
    while(k--)
    {
        ck=q.top(),q.pop();
        x=ck.nd/A,y=ck.nd%A/B,z=ck.nd%B;
        if(x+1<=n && vis.find(c2(x+1,y,z))==vis.end()) q.emplace(calc(x+1,y,z),c2(x+1,y,z)),vis.emplace(c2(x+1,y,z));
        if(y+1<=n && vis.find(c2(x,y+1,z))==vis.end()) q.emplace(calc(x,y+1,z),c2(x,y+1,z)),vis.emplace(c2(x,y+1,z));
        if(z+1<=n && vis.find(c2(x,y,z+1))==vis.end()) q.emplace(calc(x,y,z+1),c2(x,y,z+1)),vis.emplace(c2(x,y,z+1));
    }
    
    write(q.top().st,'\n');

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：sh1kong (赞：2)

[In Luogu](https://www.luogu.com.cn/problem/AT_abc391_f)

妙妙题。可惜之前没做过弱化版。

[弱化版](https://www.luogu.com.cn/problem/P1631)

与弱化版类似。将 $A,B,C$ 从大到小排序。一开始把 $(1,1,1)$ 塞入大根堆里。然后对每个堆顶 $(i,j,k)$，扩展 $(i+1,j,k)$，$(i,j+1,k)$，$(i,j,k+1)$ 塞入堆里。那么就做完了。注意需要去重，具体可以哈希一下用 map 维护。由于 $K$ 只有 $5 \times 10^5$，时间复杂度可以接受。

[AC 记录](https://atcoder.jp/contests/abc391/submissions/62333291)

---

## 作者：lkjzyd20 (赞：1)

## 简要题意

给你 $A,B,C$ 三个序列，求第 $K$ 大 $A_iB_j + B_jC_k + C_kA_i$ 。
## 思路
我们可以考虑堆优化（利用大根堆维护前 $K$ 大元素）来减少时间复杂度。

由于最大值一般由较大的数相乘产生，我们可以固定某一维度，减少搜索空间，所以先对 $A,B,C$ 进行排序（降序），然后使用大根堆（优先队列），只枚举最有可能的最大值组合，避免无效计算，每一次的堆顶进行扩展时进行判重，这里我使用 set 数据结构来维护。

时间复杂度为 $O(n\log n+K\log K) $
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
using namespace std;
const int N=5e5+10;
int n,K,a[N],b[N],c[N];
struct Node {
    int sum,i,j,k;
    bool operator<(const Node& x)const{
        return sum<x.sum;
    }
};
priority_queue<Node> q;
set<tuple<int,int,int> >s;
int Ans(int i,int j,int k){return a[i]*b[j]+b[j]*c[k]+c[k]*a[i];}
void check(int i,int j,int k)
{
    if(s.count({i,j,k}))return;
    q.push({Ans(i,j,k),i,j,k});
    s.insert({i,j,k});
}
main() 
{
    cin>>n>>K;
    rep(i,1,n)cin>>a[i];
    rep(i,1,n)cin>>b[i];
    rep(i,1,n)cin>>c[i];
    sort(a+1,a+n+1,greater<int>());
    sort(b+1,b+n+1,greater<int>());
    sort(c+1,c+n+1,greater<int>());
    q.push({Ans(1,1,1),1,1,1});
    s.insert({1,1,1});
    rep(cnt,1,K-1)
    {
        Node x=q.top();
        q.pop();
        int i=x.i,j=x.j,k=x.k;
        if(i<n) check(i+1,j,k);
        if(j<n) check(i,j+1,k);
        if(k<n) check(i,j,k+1);
    }
    cout<<q.top().sum;
    return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

## 思路
发现 $K$ 较小，可以遍历所有前 $K$ 小的值。\
先给三个数组排序，令 $(i,j,k)$ 表示 $A_iB_j+B_jC_k+C_kA_i$，显然 $(i,j,k)$ 不小于 $(i-1,j,k)$、$(i,j-1,k)$ 和 $(i,j,k-1)$，换句话说只有 $(i,j,k)$ 被遍历后才会考虑后三者。

依此开一个优先队列，排序后初始推入 $(N,N,N)$，然后重复 $K-1$ 次每次取出最大的元素 $(i,j,k)$，并尝试推入 $(i-1,j,k)$、$(i,j-1,k)$ 和 $(i,j,k-1)$（注意去重），最后队顶就是第 $K$ 大值。

时间复杂度 $O(N\log N+K\log K)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,z;
	long long num;
	bool friend operator < (const node &a,const node &b){
		return a.num != b.num ? a.num < b.num : (a.x != b.x ? a.x < b.x : (a.y != b.y ? a.y < b.y : a.z < b.z));
	}//这一个判断会被用在优先队列和 map 中，注意 map 中关键字不同必须保证可以有序排序，否则可能会混淆键值
};
int n,k,a[300000],b[300000],c[300000],ans,x,y,z;
priority_queue<node>q;
node tmp;
map<node,bool>m;
inline node f(int x,int y,int z){
	return {x,y,z,(long long)a[x] * (b[y] + c[z]) + (long long)b[y] * c[z]};//把 (x,y,z) 转换成结构体
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
	for(int i = 1;i <= n;i ++) scanf("%d",&b[i]);
	for(int i = 1;i <= n;i ++) scanf("%d",&c[i]);
	sort(a + 1,a + n + 1),sort(b + 1,b + n + 1),sort(c + 1,c + n + 1);
	q.push(f(n,n,n));
	for(int i = 1;i < k;i ++){
		tmp = q.top();//取出队顶
		q.pop();
		x = tmp.x,y = tmp.y,z = tmp.z;
		if(x > 1 && !m[f(x - 1,y,z)]) q.push(f(x - 1,y,z)),m[f(x - 1,y,z)] = true;//边界判断与 map 防重
		if(y > 1 && !m[f(x,y - 1,z)]) q.push(f(x,y - 1,z)),m[f(x,y - 1,z)] = true;
		if(z > 1 && !m[f(x,y,z - 1)]) q.push(f(x,y,z - 1)),m[f(x,y,z - 1)] = true;
	}
	printf("%lld",q.top().num);
	return 0;
}
```

---

## 作者：ljy05 (赞：1)

不难发现如果将 $A,B,C$ 从大到小排序，那么选 $(i,j,k)$ 得到的值一定大于等于选 $(i+1,j,k),(i,j+1,k),(i,j,k+1)$ 所得到的值。

所以，如果我们从大到小枚举每个可能的值，那么 $(i,j,k)$ 必然出现在 $(i+1,j,k),(i,j+1,k),(i,j,k+1)$ 之前。那么，我们在枚举到 $(i,j,k)$ 之前，就不用考虑枚举 $(i+1,j,k),(i,j+1,k),(i,j,k+1)$。

可以用一个堆来快速的解决这个问题。一开始将 $(1,1,1)$ 加入堆，每次从堆中取出值最大的 $(i,j,k)$ ，再将 $(i+1,j,k),(i,j+1,k),(i,j,k+1)$ 加入堆中。第 $K$ 次取出的就是答案。由于这种方式可能会重复枚举同一个三元组，所以需要一个 set 来去重。

时间复杂度 $O(n \log n)$。[AC 记录](https://atcoder.jp/contests/abc391/submissions/62282004)。

---

## 作者：__FL__ (赞：1)

很暴力的题。

## 题意

给定三个长度为 $N$ 的序列 $A,B,C$，对于所有的  $A_iB_j + B_jC_k + C_kA_i\ (1\leq i,j,k\leq N)$，求其中第 $K$ 大的值。

## 思路

考虑暴力枚举所有可能的值，发现复杂度达到了 $N^3$ 量级，显然不可做。发现 $K$ 的值并不大，考虑通过某种方式直接从大到小枚举可能的值。

首先将 $A,B,C$ 都从大到小排序，这是显然的。考虑一个显然的贪心，设三元组 $(i,j,k)$，我们称 $(i+1,j,k),(i,j+1,k),(i,j,k+1)$ 是它的延伸，则第 $u$ 大的三元组一定是前 $u-1$ 大的某个三元组的延伸（我们定义此类三元组的“大小”为其套入式子中的大小）。更直观地，假设第 $1$ 大和第 $2$ 大的三元组分别为 $(1,1,1)$ 和 $(2,1,1)$，第 $3$ 大的三元组一定会是 $(1,2,1),(1,1,2),(3,1,1),(2,2,1),(2,1,2)$ 中的一个，其中前两个是 $(1,1,1)$ 的延伸，后三个是 $(2,1,1)$ 的延伸。

这非常符合广度优先搜索的做法，从 $(1,1,1)$ 开始，记录所有未出现过的延伸，在其中选择最小的继续拓展，直到拓展到第 $K$ 个。这一过程可以用堆实现。

## 复杂度分析

排序复杂度 $O(n\log{n})$；搜索每次拓展最多会出现 $3$ 个新的延伸，总共最多 $3K$ 个延伸，时间复杂度 $O(K)$，总时间复杂度 $O(n\log{n}+K)$.

## 代码

这里我懒得写重载运算符，用奇怪的方式处理了一下，但是应该看得懂。

```cpp
#include<bits/stdc++.h>
#define int long long
#define PIIII pair<pair<long long,long long>,pair<long long,long long>>
using namespace std;
int n,k,a[200005],b[200005],c[200005],l,p,num;
priority_queue<PIIII>q;
unordered_map<int,bool>mp;
inline int getid(int a,int b,int c) {return a*(n+1)*(n+1)+b*(n+1)+c;}
inline int getnum(int x,int y,int z) {return a[x]*b[y]+a[x]*c[z]+b[y]*c[z];}
bool cmp(int a,int b) {return a > b;}
void bfs()
{
	int o1,o2,o3;
	q.push({{getnum(1,1,1),1},{1,1}});
	mp[getid(1,1,1)] = 1;
	while (l < k)
	{
		PIIII now = q.top();
		num = now.first.first;
		o1 = now.first.second;
		o2 = now.second.first;
		o3 = now.second.second;
		l++;
		q.pop();
		if (o1 < n && !mp[getid(o1+1,o2,o3)]) q.push({{getnum(o1+1,o2,o3),o1+1},{o2,o3}}),mp[getid(o1+1,o2,o3)]=1;
		if (o2 < n && !mp[getid(o1,o2+1,o3)]) q.push({{getnum(o1,o2+1,o3),o1},{o2+1,o3}}),mp[getid(o1,o2+1,o3)]=1;
		if (o3 < n && !mp[getid(o1,o2,o3+1)]) q.push({{getnum(o1,o2,o3+1),o1},{o2,o3+1}}),mp[getid(o1,o2,o3+1)]=1;
	}
}
signed main()
{
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	for (int i = 1; i <= n; i++)
		cin >> c[i];
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+n+1,cmp);
	sort(c+1,c+n+1,cmp);
	bfs();
	cout << num;
    return 0;
}
```

---

## 作者：superLouis (赞：1)

## 题解： AT_abc391_f [ABC391F] K-th Largest Triplet

水题一道，只是有点思维难度而已了。

----------
### 1. 解题思路
将 $A$、$B$、$C$ 分别按降序排序。同时，定义函数 $f(i, j, k) = A_i \times B_j + B_j \times C_k + C_k \times A_i$。

我们需要尝试枚举前 $K$ 个最大的值，其中 $K$ 的范围较小，$K \le 2 \times 10^5$。重要的是：

- $f(i, j, k) \ge f(i + 1, j, k)$
- $f(i, j, k) \ge f(i, j + 1, k)$
- $f(i, j, k) \ge f(i, j, k + 1)$

这意味着如果我们按降序枚举，$f(i, j, k)$ 总是先于 $f(i+1, j, k)$、$f(i, j+1, k)$ 和 $f(i, j, k+1)$。

因此，可以通过以下算法解决该问题：

1. 准备一个二叉堆 $Q$，将 $\{f(0,0,0), 0, 0, 0\}$ 插入二叉堆中（这里我们可以用 `vector` 容器从 $0$ 号下标开始存储）。
2. 重复以下步骤 $K$ 次：

   - 取出 $Q$ 中的最大元素 $\{val, i, j, k\}$。
   - 移除 $\{val, i, j, k\}$，并把 $\{f(i+1, j, k), i+1, j, k\}$、$\{f(i, j+1, k), i, j+1, k\}$ 和 $\{f(i, j, k+1), i, j, k+1\}$ 插入到二叉堆中（如果他们尚未在 $Q$ 内）。
3. 时间复杂度为 $O(N \log N + K \log K)$。

----------
### 2. 代码实现
就知道你们想要这个。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Sum {
    int value;
    int i, j, k;
    Sum(int v, int x, int y, int z) : value(v), i(x), j(y), k(z) {}
    bool operator < (const Sum &other) const {
        return value < other.value;
    }
};
int find_kth(int N, int K, vector<int> &a, vector<int> &b, vector<int> &c) {
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    sort(c.rbegin(), c.rend());
    priority_queue<Sum> pq;
    pq.push(Sum((int)a[0] * b[0] + (int)b[0] * c[0] + (int)c[0] * a[0], 0, 0, 0));
    set<tuple<int, int, int>> st;
    st.insert(make_tuple(0, 0, 0));
    int count = 0;
    while (!pq.empty()) {
        Sum cur = pq.top();
        pq.pop();
        count++;
        if (count == K) return cur.value; 
        if (cur.i + 1 < N && st.find(make_tuple(cur.i + 1, cur.j, cur.k)) == st.end()) {
            st.insert(make_tuple(cur.i + 1, cur.j, cur.k));
            pq.push(Sum((int)a[cur.i + 1] * b[cur.j] + (int)b[cur.j] * c[cur.k] + (int)c[cur.k] * a[cur.i + 1], cur.i + 1, cur.j, cur.k));
        }
        if (cur.j + 1 < N && st.find(make_tuple(cur.i, cur.j + 1, cur.k)) == st.end()) {
            st.insert(make_tuple(cur.i, cur.j + 1, cur.k));
            pq.push(Sum((int)a[cur.i] * b[cur.j + 1] + (int)b[cur.j + 1] * c[cur.k] + (int)c[cur.k] * a[cur.i], cur.i, cur.j + 1, cur.k));
        }
        if (cur.k + 1 < N && st.find(make_tuple(cur.i, cur.j, cur.k + 1)) == st.end()) {
            st.insert(make_tuple(cur.i, cur.j, cur.k + 1));
            pq.push(Sum((int)a[cur.i] * b[cur.j] + (int)b[cur.j] * c[cur.k + 1] + (int)c[cur.k + 1] * a[cur.i], cur.i, cur.j, cur.k + 1));
        }
    }
    return -1;
}
signed main() {
    int N, K; cin >> N >> K;
    vector<int> a(N), b(N), c(N);
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        a[i - 1] = x;
    }
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        b[i - 1] = x;
    }
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        c[i - 1] = x;
    }
    cout << find_kth(N, K, a, b, c) << endl;
    return 0;
}
```
其中，我使用了 `set` 容器来判断是否已经在二叉堆 $Q$ 中。

[测评记录](https://atcoder.jp/contests/abc391/submissions/62289756)

---

## 作者：abc1856896 (赞：1)

挺暴力的题。

# Solution

首先三重循环枚举加优先队列必然会爆，时间复杂度 $O(n^3 \log K)$。

我们注意到 $K$ 不是很大，所以我们可以在三重循环里判断该循环前面所生成的数量是否比 $K$ 大，如果大了直接结束，否则加入队列。类似于剪枝。

这样乱搞后枚举的次数理论上来说是 $K \log ^2 K$，实际上可能跑得多两三倍。经实测，当 $N$ 和 $K$ 均取上界时，最多跑 $46894156$ 次，可以通过。

# Code


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],b[200005],c[200005],k;
bool cmp(int t1,int t2){
	return t1>t2;
}
priority_queue<int> q;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+n,cmp);
	sort(c+1,c+1+n,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k/i&&j<=n;j++){
			for(int l=1;l<=k/(i*j)&&l<=n;l++){
				q.push(a[i]*b[j]+b[j]*c[l]+a[i]*c[l]);
			}
		}
	}
	k--;
	while(k--) q.pop();
	cout<<q.top();
	return 0;
}
```

---

## 作者：zhangbo1000 (赞：0)

首先我们把 $A,B,C$ 本身分别按照从大到小排序显然不会影响答案。

然后我们观察 $A_iB_j+B_jC_k+C_kA_i$，显然我们把 $A_i,B_j,C_k$ 中任意一个减小（对于排序后的 $A,B,C$，这等价于将 $i,j,k$ 中任意一个增大），答案都会减小，所以最终的所有 $A_iB_j+B_jC_k+C_kA_i$ 假如先按照大小排序，再按照 $ijk$ 排序（这不会影响答案，因为这一步排的是相等的数），则 $A_iB_j+B_jC_k+C_kA_i$ 至少是第 $ijk$ 大的。

所以我们可以根据这一点枚举，总枚举量为：

$$\sum_{i=1}^n\sum_{j=1}^{\frac{n}{i}}\sum_{k=1}^{\frac{n}{ij}}O(1)$$

（取整问题不影响复杂度分析），后面两层是一个调和级数的形式，上式等于：

$$\sum_{i=1}^nO(\frac{n}{i}\log \frac{n}{i})$$

$\log \frac{n}{i}$ 有宽松的上界 $\log n$，$\sum_{i=1}^n\frac{n}{i}$ 又是调和级数，等于 $O(n\log n)$，所以上述算法的时间复杂度为 $O(n\log^2n)$。

然后找 $O(n\log^2n)$ 个数中第 $K$ 大就完了，这是个[很经典的问题](https://www.luogu.com.cn/problem/P1923)，可以 $O(n\log^2n)$ 完成。

[代码及评测记录。](https://atcoder.jp/contests/abc391/submissions/62291444)

---

## 作者：Lele_Programmer (赞：0)

# AT_abc391_f 题解

提供一种比较新奇的二分套二分的做法。

## 思路

先将序列 $A,B,C$ 降序排序，假设 $A,B$ 选的元素位置已确定，那么 $C$ 选的元素位置依次递增的话，$A_iB_j+B_jC_k+C_kA_i$ 的值也是单调递减的。

于是可以确定第一层二分，将最终答案进行二分，如果比当前值小的方案大于等于 $K$ 种，那么左指针更新为中点，如果小于 $K$ 种，则右指针更新为中点左侧的点。

接下来考虑如何确定大于等于一个已知值的方案数。

设 $i,j,k$ 分别是指向 $A,B,C$ 的索引，最外层枚举 $i$，第二层枚举 $j$，然后 $k$ 进行二分，如果某个 $i,j$ 产生的贡献为 $0$，则对于 $j \le j' \le n$ 的所有 $j'$ 都不会产生贡献了，令 $i \leftarrow i+1, j \leftarrow 1$，开始新一轮 $j$ 的枚举。

虽然 $i,j$ 是暴力枚举，但是对于无贡献的 $k$ 直接退出，可以保证每一次枚举 $i,j$ 都至少有 $1$ 的贡献，所以这一部分的时间复杂度是 $\mathcal{O}(K \log N)$。

那么总的时间复杂度是 $\mathcal{O}(K \log N \log M)$，这里 $M$ 是答案值域，最大为 $3 \times 10^{18}$，理论上极限数据可能得跑到 $5 \times 10^8$，但是它 $3$ 秒内过了。


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string& x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string& x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string& x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

const int N=200005;

int n,k;
int a[N],b[N],c[N];

bool cmp(const int& a,const int& b) {
    return a>b;
}

i64 calc(int i,int j,int k) {
    return (i64)a[i]*b[j]+(i64)b[j]*c[k]+(i64)c[k]*a[i];
}

bool check(i64 mid) { // >=mid <k
    int cnt=0;
    _rep(i,1,n) {
        _rep(j,1,n) {
            int l=0,r=n;
            while (l<r) {
                int d=(l+r>>1)+1;
                if (calc(i,j,d)>=mid) l=d;
                else r=d-1;
            }
            if (!l) break;
            cnt+=l;
            if (cnt>=k) return false;
        }
    }
    return true;
}

int main() {
    read(n),read(k);
    _rep(i,1,n) read(a[i]);
    _rep(i,1,n) read(b[i]);
    _rep(i,1,n) read(c[i]);
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+n,cmp);
    sort(c+1,c+1+n,cmp);
    i64 l=0,r=3e18;
    while (l<r) {
        i64 mid=(l+r>>1)+1;
        if (!check(mid)) l=mid;
        else r=mid-1;
    }
    write(l);
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

我们不妨把 $a,b,c$ 都按从大到小排序，这时会对于 $1\le i,j,k<n$，有 $a_ib_j+b_jc_k+c_ka_i\ge a_{i+1}b_j+b_jc_k+c_ka_{i+1}$，其余同理。所以可以开一个 set 维护一个状态 $val,i,j,k$，其中 $val=a_ib_j+b_jc_k+c_ka_i$，每次把一个状态移除后加入它的后继状态（前提是这个后继状态未被加入过，即使它被删除了也不能继续加入），即 $f(i+1,j,k),i+1,j,k$，$f(i,j+1,k),i,j+1,k$ 和 $f(i,j,k+1),i,j,k+1$，这里 $f(x,y,z)=a_xb_y+b_yc_z+c_za_x$，这样每次我们找到的 $val$ 最大的状态必定一次比一次小并且在某一次的 $val$ 和上一次之间不可能再有其他的 $val$，因此找 $k$ 次便可以得到答案。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
#define piiii pair<pair<int,int>,pair<int,int>>
int a[N],b[N],c[N];
set<piiii,greater<piiii>> st,st2;
inline int f(int x,int y,int z)
{
	return a[x]*b[y]+b[y]*c[z]+c[z]*a[x];
}
signed main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	sort(a+1,a+n+1,greater<int>());
	sort(b+1,b+n+1,greater<int>());
	sort(c+1,c+n+1,greater<int>());
	st.insert({{f(1,1,1),1},{1,1}});
	st2.insert({{f(1,1,1),1},{1,1}});
	k--;
	while(k)
	{
		auto p=*st.begin();
		st.erase(st.begin());
		auto p1=p.first,p2=p.second;
		int x=p1.second,y=p2.first,z=p2.second;
		if(x<n&&!st2.count({{f(x+1,y,z),x+1},{y,z}}))
		st.insert({{f(x+1,y,z),x+1},{y,z}}),st2.insert({{f(x+1,y,z),x+1},{y,z}});
		if(y<n&&!st2.count({{f(x,y+1,z),x},{y+1,z}}))
		st.insert({{f(x,y+1,z),x},{y+1,z}}),st2.insert({{f(x,y+1,z),x},{y+1,z}});
		if(z<n&&!st2.count({{f(x,y,z+1),x},{y,z+1}}))
		st.insert({{f(x,y,z+1),x},{y,z+1}}),st2.insert({{f(x,y,z+1),x},{y,z+1}});
		k--;
	}
	cout<<st.begin()->first.first;
}

---

## 作者：Your_Name (赞：0)

## 题意

找到一组 $(i,j,k)$ 使得其权值为所有 $N^3$ 种选择中第 $K$ 大的。

定义一组 $(i,j,k)$ 的权值为 $A_iB_j + B_jC_k + C_kA_i$。

## 题解

发现 $K$ 最大是 $5\times 10^5$，感觉复杂度可能和 $K$ 有关。

再观察，发现 $A,B,C$ 全部为正整数，所以把他们全部从大到小排序后，$(i,j,k)$ 的权值显然会大于等于 $(i+1,j,k)$，$(i,j+1,k)$，$(i,j,k+1)$。

所以，三种情况一定是排名比他后的组。

由此递推，发现我们可以直接暴力找出前 $K$ 大，用大根堆维护，再用 map 防止重复即可。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e5 + 10;
LL n, k, a[N], b[N], c[N];
struct node{
    LL val, i, j, k;
    friend bool operator < (node a, node b){
        return a.val < b.val;
    }
}ans;
priority_queue<node>q;
LL get(LL i, LL j, LL k){
    return a[i] * b[j] + b[j] * c[k] + c[k] * a[i];
}
map<pair<int, pair<int, int>>, bool> ma;//注意结构体不能直接用 map
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for(LL i = 1; i <= n; i ++)cin >> a[i];
    for(LL i = 1; i <= n; i ++)cin >> b[i];
    for(LL i = 1; i <= n; i ++)cin >> c[i];
    sort(a + 1, a + 1 + n, greater<LL>());
    sort(b + 1, b + 1 + n, greater<LL>());
    sort(c + 1, c + 1 + n, greater<LL>());
    q.push({get(1, 1, 1), 1, 1, 1});
    ma[{1, {1, 1}}] = 1;//最大的
    while(k --){
        ans = q.top();
        q.pop();
        int a = ans.i, b = ans.j, c = ans.k;
        if(a < n && ma.count({a + 1, {b, c}}) == 0){
            ma[{a + 1, {b, c}}] = 1;
            q.push({get(a + 1, b, c), a + 1, b, c});
        }
        if(b < n && ma.count({a, {b + 1, c}}) == 0){
            ma[{a, {b + 1, c}}] = 1;
            q.push({get(a, b + 1, c), a, b + 1, c});
        }
        if(c < n && ma.count({a, {b, c + 1}}) == 0){
            ma[{a, {b, c + 1}}] = 1;
            q.push({get(a, b, c + 1), a, b, c + 1});
        }//往后拓展
    }
    cout << ans.val;
    return 0;
}
```
 _完结撒花。_

---

## 作者：lzyqwq (赞：0)

小丑做法。属于是超级钢琴做魔怔了。

> - 给出长度为 $n$ 的序列 $a,b,c$，求 $a_ib_j+a_ic_k+b_jc_k$ 的第 $K$ 大值。
> - $K\le 5\times 10^5$，$n\le 2\times 10^5$。

假设我们有一个三元组集合 $S$，初始包含所有 $1\le i,j,k\le n$ 的 $(i,j,k)$。定义上面那个式子为一个三元组的权值。我们可以重复 $K-1$ 次下面过程：

> 取出 $S$ 中权值最大的三元组，将其从 $S$ 中删除。

最后 $S$ 中三元组的最大权值即为答案。

考虑将全部三元组压缩成若干个子集，每个子集形如 $\{[l,r],[x,y],[u,v]\}$，包含 $i\in[l,r],j\in[x,y],k\in[u,v]$ 的三元组。

那么初始的 $S$ 就可以表示成 $\{[1,n],[1,n],[1,n]\}$。

考虑取出当前的最大值，就是在所有子集的最大值中取。而对于某个子集的最大值，就是 $a,b,c$ 均在对应区间中取最大值。这个过程可以通过用 ST 表维护最大值的位置来 $\mathcal{O}(1)$ 完成。对于所有子集的最大值可以开一个大根堆维护。

取出最大值对应的三元组 $(i,j,k)$ 后，需要删除她。只需要从其取出来的子集中删掉她再把子集放回大根堆即可。

假设她原来所在子集为 $\{[l,r],[x,y],[u,v]\}$，删掉她后可以表示成 $\{[l,i-1],[x,y],[u,v]\},\{\{i\},[x,j-1],[u,v]\},\{\{i\},\{j\},[u,k-1]\},\{\{i\},\{j\},[k+1,v]\},\{\{i\},[j+1,y],[u,v]\},\{[i+1,r],[x,y],[u,v]\}$ 的并。那么相当于删掉原来子集再往大根堆中插入 $\mathcal{O}(1)$ 个子集。

时间复杂度为 $\mathcal{O}(K\log n)$，空间复杂度为 $\mathcal{O}(n\log n)$。

Code：https://atcoder.jp/contests/abc391/submissions/62285800

但是你注意到排序之后，每次 $a,b,c$ 均会从对应区间的头部取。于是不需要 ST 表了。。。

---

## 作者：imljw (赞：0)

仔细读完题目，我们可以发现，直接硬求显然不可取，我们可以考虑换一种方式，首先把 $a$ $b$ $c$ 数组从大到小排序。最大值很明显是三元组 $(1, 1, 1)$，次大值肯定是 $(1, 1, 2)$ 和 $(1, 2, 1)$ 以及 $(2, 1, 1)$ 中的一个，其余的都一定比上面三个小，一定不是次大值，那么我们可以将其扩展一下，对于当前最大值 $(i, j, k)$，可能成为新的最大值的只有 $(i + 1, j, k)$ 和 $(i, j + 1, k)$ 以及 $(i, j, k + 1)$ 加上之前算出来的可能为新的最大值的三元组，丢进最大堆维护并用数据结构维护即可，每个三元组只会贡献最多三个新的，只会找出 $k$ 个三元组（只求前 $k$ 大），所以只有不到 $3 \times k$ 个三元组进入堆，时间复杂度铁定够了。

赛时代码，~~请勿抄袭~~。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[200005], b[200005], c[200005], n, k, an;
struct nodw
{
    long long x, y, z;
} h;
bool operator<(nodw x, nodw y)
{
    return a[x.x] * b[x.y] + (a[x.x] + b[x.y]) * c[x.z] < a[y.x] * b[y.y] + (a[y.x] + b[y.y]) * c[y.z];
}
bool cmp(long long a, long long b)
{
    return a > b;
}
priority_queue<nodw> q;
map<pair<pair<long long, long long>, long long>, bool> mp;
int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &b[i]);
    sort(b + 1, b + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &c[i]);
    sort(c + 1, c + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        q.push((nodw){1, 1, i});
    while (k--)
    {
        h = q.top();
        q.pop();
        an = a[h.x] * b[h.y] + (a[h.x] + b[h.y]) * c[h.z];
        if (h.x < n && !mp.count(make_pair(make_pair(h.x + 1, h.y), h.z)))
            q.push((nodw){h.x + 1, h.y, h.z}), mp[make_pair(make_pair(h.x + 1, h.y), h.z)] = 1;
        if (h.y < n && !mp.count(make_pair(make_pair(h.x, h.y + 1), h.z)))
            q.push((nodw){h.x, h.y + 1, h.z}), mp[make_pair(make_pair(h.x, h.y + 1), h.z)] = 1;
    }
    printf("%lld", an);
    return 0;
}
```

---

## 作者：Ivan422 (赞：0)

一个唐诗解法。

我们考虑把这些数枚举一次。

但是超时。

因为我是唐诗，根本不会二分，所以写了个优先队列。

我们发现，可以先将 $a,b,c$ 从大到小排序。

然后我们找找贪心方法，每一次都不会错过。

设当前枚举到 $i,j,k$。

我们尽量少枚举一点。

我们发现，$i+1,j,k$ 是比 $i+2,j,k$ 更大，也比 $i+1,j+1,k$ 什么的更大。

所以我们考虑每一次在优先队列中插入 $i+1,j,k$、$i,j+1,k$ 与 $i,j,k+1$ 才可以保证每一次不会错过。

当然这里我炸了一次，因为重复访问了。

那么，我们搞一个 `set`，不要让 $i,j,k$ 枚举有重复。

最后我们就可以做到 $\mathcal O(k \log k)$ 左右的优秀复杂度了。

~~竟然不输二分？~~

~~代码比思路更唐。~~


```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
//using namespace __gnu_pbds;
#define int long long
#define ai3 array<int,3>
#define ai4 array<int,4>
//#define pb push_back
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,m,a[N],b[N],c[N];
set<ai3>st;
priority_queue<ai4>pq;
void iist(int i,int j,int k){
	if(!st.count(ai3{i,j,k})){
		st.insert(ai3{i,j,k});
		pq.push(ai4{a[i]*b[j]+b[j]*c[k]+a[i]*c[k],i,j,k});
	}			
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	sort(a+1,a+n+1,greater<int>());
	sort(b+1,b+n+1,greater<int>());
	sort(c+1,c+n+1,greater<int>());
	iist(1,1,1);
	for(int _=1;_<=m;_++){
		ai4 front=pq.top();pq.pop();
		auto [v,i,j,k]=front;
		if(_==m)return cout<<v,0;
		else{
			if(i<n)iist(i+1,j,k);
			if(j<n)iist(i,j+1,k);
			if(k<n)iist(i,j,k+1);		
		}
	}
    return 0;
}
//note:

```

---

## 作者：Inv_day_in_R (赞：0)

简单搜索。

首先给三个数组都排个序。不难想到，值最大的三元组显然是 $(n,n,n)$。那么第二大的呢？肯定是 $(n-1,n,n)$、$(n,n-1,n)$ 或 $(n,n,n-1)$。这时，可以想到用一个优先队列维护，每次选出最大值 $(i,j,k)$，然后将比这个最大值略小一点的三个值进队列，也就是 $(i-1,j,k)$、$(i,j-1,k)$ 和 $(i,j,k-1)$。当然要记得判重，用一个 `map` 即可。由于找到第 $k$ 大就停止，每次最多三个新的组入队，那么队列中最多 $3k$ 个元素，加上排序，时间复杂度稳定 $O(n\log n+k\log k)$。

代码：

```cpp
int calc(array<int,3>a){
	return a[0]*a[1]+a[1]*a[2]+a[2]*a[0];
}
void solve(){
	int n,K;
	cin>>n>>K;
	vector<int>a(n),b(n),c(n);
	cin>>a>>b>>c;
	sort(all(a));
	sort(all(b));
	sort(all(c));
	priority_queue<array<int,4>>pq;//默认大根堆
	map<array<int,3>,bool>mp;
	pq.push({calc({a[n-1],b[n-1],c[n-1]}),n-1,n-1,n-1});
	mp[{n-1,n-1,n-1}]=1;
	for(int x=1;x<=K;x++){
		auto[_,i,j,k]=pq.top();
		pq.pop();
		if(x==K){
			cout<<_<<endl;//输出第K大的值
			return;
		}
		if(i&&!mp[{i-1,j,k}]){//i>=1且i-1,j,k未被访问过
			pq.push({calc({a[i-1],b[j],c[k]}),i-1,j,k});
			mp[{i-1,j,k}]=1;
		}
		if(j&&!mp[{i,j-1,k}]){//j>=1且i,j-1,k未被访问过
			pq.push({calc({a[i],b[j-1],c[k]}),i,j-1,k});
			mp[{i,j-1,k}]=1;
		}
		if(k&&!mp[{i,j,k-1}]){//k>=1且i,j,k-1未被访问过
			pq.push({calc({a[i],b[j],c[k-1]}),i,j,k-1});
			mp[{i,j,k-1}]=1;
		}
	}
}
```

---

## 作者：linjinkun (赞：0)

>[不加火车头（不吸氧）不开快读全部 `long long` 提交记录。](https://www.luogu.com.cn/record/201060670)

>[使用了我所知的三种优化后的提交记录（最慢点还是没有在一秒内跑过啊）。](https://www.luogu.com.cn/record/201065391)

做法非常的妙，我们先将 $A,B,C$ 这三个数组降序排序，我们设 $f(i,j,k) = A_iB_j+B_jC_k+C_kA_i$，由于 $f(i,j,k) \ge f(i+1,j,k),f(i,j,k) \ge f(i,j+1,k),f(i,j,k) \ge f(i,j,k+1)$，我们想到了一种类似 `bfs` 的做法，因为 `bfs` 的正确性就在于每次取出的点一定是在某种意义上最小或最大的（根据题目决定大还是小），而我们这道题无法保证这一点，但是可以使用优先队列 `priority_queue` 来解决，同时它也满足 `bfs` 的一个性质：每次取出一个点，放入的点一定在某种意义上比它小或大（根据题目决定大还是小），所以我们可以使用 `bfs` 的做法，只需要把队列 `queue` 换成优先队列 `priority_queue` 即可。

时间复杂度：$O(N \log N+K \log K)$。$O(N \log N)$ 是排序部分，$O(K \log K)$ 指的是优先队列 `priority_queue` 中最多会出现 $O(K)$ 个元素，然后优先队列 `priority_queue` 中插入删除复杂度为 $O(\log K)$。当然，此题还有不可忽视的 `STL` 常数，导致实际跑出来的结果时间方面没有那么理想，不过也因为我没有开火车头（不吸氧），粗暴地全开 `long long`，这样会导致程序常数增加，所以没法在一秒内跑过。

代码一号（优化前）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 2e5+5;
struct node
{
	int v;
	int x;
	int y;
	int z;
	int operator<(const node&a)const
	{
		return v<a.v;
	}
};
priority_queue<node>q;
int a[N];
int b[N];
int c[N];
map<pair<pair<int,int>,int>,int>mp;
signed main()
{
	int n,k;
	scanf("%lld %lld",&n,&k);
	for(int i = 1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i = 1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
	}
	for(int i = 1;i<=n;i++)
	{
		scanf("%lld",&c[i]);
	}
	sort(a+1,a+n+1,greater<int>());
	sort(b+1,b+n+1,greater<int>());
	sort(c+1,c+n+1,greater<int>());
	q.push({a[1]*b[1]+a[1]*c[1]+b[1]*c[1],1,1,1});
	mp[{{1,1},1}] = 1;
	for(int i = 1;i<=k;i++)
	{
		int x = q.top().x,y = q.top().y,z = q.top().z,v = q.top().v;
		q.pop();
		if(i == k)
		{
			printf("%lld",v);
			return 0;
		}
		int ax = x+1,ay = y,az = z;
		int bx = x,by = y+1,bz = z;
		int cx = x,cy = y,cz = z+1; 
		if(ax<=n&&mp.find({{ax,ay},az}) == mp.end())
		{
			mp[{{ax,ay},az}] = 1;
			q.push({a[ax]*b[ay]+a[ax]*c[az]+b[ay]*c[az],ax,ay,az});
		}
		if(by<=n&&mp.find({{bx,by},bz}) == mp.end())
		{
			mp[{{bx,by},bz}] = 1;
			q.push({a[bx]*b[by]+a[bx]*c[bz]+b[by]*c[bz],bx,by,bz});
		}
		if(cz<=n&&mp.find({{cx,cy},cz}) == mp.end())
		{
			mp[{{cx,cy},cz}] = 1;
			q.push({a[cx]*b[cy]+a[cx]*c[cz]+b[cy]*c[cz],cx,cy,cz});
		}
	}
    return 0;
}
```
代码二号（优化后）：
```cpp
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO {
#define FASTIO
#define IOSIZE 100000
	char ibuf[IOSIZE], obuf[IOSIZE];
	char *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#ifdef ONLINE_JUDGE
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#endif//fread in OJ, stdio in local
	
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() {
		T s = 0;
		int w = 1;
		char ch;
		while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1;
		if (ch == EOF) return false;
		while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
		return s * w;
	}
	template<typename T> inline bool read(T &s) {
		s = 0;
		int w = 1;
		char ch;
		while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1;
		if (ch == EOF) return false;
		while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
		return s *= w, true;
	}
	inline bool read(char &s) {
		while (s = getchar(), isspace(s));
		return true;
	}
	inline bool read(char *s) {
		char ch;
		while (ch = getchar(), isspace(ch));
		if (ch == EOF) return false;
		while (!isspace(ch)) *s++ = ch, ch = getchar();
		*s = '\000';
		return true;
	}
	template<typename T> inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x > 9) print(x / 10);
		putchar(x % 10 + 48);
	}
	inline void print(char x) {
		putchar(x);
	}
	inline void print(char *x) {
		while (*x) putchar(*x++);
	}
	inline void print(const char *x) {
		for (int i = 0; x[i]; ++i) putchar(x[i]);
	}
#ifdef _GLIBCXX_STRING
	inline bool read(std::string& s) {
		s = "";
		char ch;
		while (ch = getchar(), isspace(ch));
		if (ch == EOF) return false;
		while (!isspace(ch)) s += ch, ch = getchar();
		return true;
	}
	inline void print(std::string x) {
		for (int i = 0, n = x.size(); i < n; ++i)
			putchar(x[i]);
	}
#endif//string
	template<typename T, typename... T1> inline int read(T& a, T1&... other) {
		return read(a) + read(other...);
	}
	template<typename T, typename... T1> inline void print(T a, T1... other) {
		print(a);
		print(other...);
	}
	
	struct Fast_IO {
		~Fast_IO() {
			fwrite(obuf, p3 - obuf, 1, stdout);
		}
	} io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) {
		return read(b), io;
	}
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) {
		return print(b), io;
	}
#define cout io
#define cin io
#define endl '\n'
}
using namespace fast_IO;
const int N = 2e5+5;
struct node
{
	long long v;
	int x;
	int y;
	int z;
	int operator<(const node&a)const
	{
		return v<a.v;
	}
};
priority_queue<node>q;
long long a[N];
long long b[N];
long long c[N];
map<pair<pair<int,int>,int>,int>mp;
signed main()
{
	int n,k;
	cin >> n >> k;
	for(int i = 1;i<=n;i++)
	{
		cin >> a[i];
	}
	for(int i = 1;i<=n;i++)
	{
		cin >> b[i];
	}
	for(int i = 1;i<=n;i++)
	{
		cin >> c[i];
	}
	sort(a+1,a+n+1,greater<int>());
	sort(b+1,b+n+1,greater<int>());
	sort(c+1,c+n+1,greater<int>());
	q.push({a[1]*b[1]+a[1]*c[1]+b[1]*c[1],1,1,1});
	mp[{{1,1},1}] = 1;
	for(int i = 1;i<=k;i++)
	{
		int x = q.top().x,y = q.top().y,z = q.top().z;
		long long v = q.top().v;
		q.pop();
		if(i == k)
		{
			cout << v;
			return 0;
		}
		int ax = x+1,ay = y,az = z;
		int bx = x,by = y+1,bz = z;
		int cx = x,cy = y,cz = z+1; 
		if(ax<=n&&mp.find({{ax,ay},az}) == mp.end())
		{
			mp[{{ax,ay},az}] = 1;
			q.push({a[ax]*b[ay]+a[ax]*c[az]+b[ay]*c[az],ax,ay,az});
		}
		if(by<=n&&mp.find({{bx,by},bz}) == mp.end())
		{
			mp[{{bx,by},bz}] = 1;
			q.push({a[bx]*b[by]+a[bx]*c[bz]+b[by]*c[bz],bx,by,bz});
		}
		if(cz<=n&&mp.find({{cx,cy},cz}) == mp.end())
		{
			mp[{{cx,cy},cz}] = 1;
			q.push({a[cx]*b[cy]+a[cx]*c[cz]+b[cy]*c[cz],cx,cy,cz});
		}
	}
    return 0;
}
```
~~当然我相信再加上一些毒瘤优化后应该是能在一秒内跑过的。~~

代码看不懂或思路看不懂欢迎私信！

---

## 作者：Colinxu2020 (赞：0)

优先队列调整法板子，鉴定为 F<E<D。

先将 $a,b,c$ 三个数组升序排序，记 $f(i,j,k)=a_{i}\times b_{j}+b_{j} \times c_{k}+a_{i} \times c_{k}$，求出 $\Delta$，$f(i+1,j,k)-f(i,j,k)=(a_{i+1}-a_i) \times (b_{j}+c_{k})$，因为 $b_j,c_k \gt 0$，而我们已经排序，所以 $f(i+1,j,k) \gt f(i,j,k)$，同理可得 $f(i,j+1,k) \gt f(i,j,k),f(i,j,k+1) \gt f(i,j,k)$。

不妨维护一个优先队列 $p$，初始插入 $(n,n,n)$，对于每一个元素，我们按 $f(i,j,k)$ 为其优先级，重复 $k-1$ 次，每次从 $p$ 中弹出堆顶，并插入 $f(i-1,j,k),f(i,j-1,k),f(i,j,k-1)$，注意不要越界，并对优先队列中的元素去重。最后答案为堆顶元素的 $f(i,j,k)$。

正确性证明：若答案为 $f(i-2,j,k)$，由上面的引理可得 $f(i-1,j,k) \gt f(i-2,j,k)$，而因为答案为 $f(i-2,j,k)$，我们必然已经弹出 $f(i-1,j,k)$，并加入 $f(i-2,j,k)$，同理可得，所有可能的答案都会被考虑到。

复杂度：$\Theta(K \log_2 K)$。

---

## 作者：tian720 (赞：0)

题目传送门：[[ABC391F] K-th Largest Triplet](https://www.luogu.com.cn/problem/AT_abc391_f)。
## Solution：
考虑将最大数对 $(1,1,1)$ 逐步扩展到第 $K$ 大数对。

将三个数组降序排列后，设 $f(i,j,k)=A_iB_j+B_jC_k+C_kA_i$。可以发现 $f(i,j,k)$ 总排在 $f(i+1,j,k),f(i,j+1,k),f(i,j,k+1)$ 的前面，于是我们可以借助这个单调性减少枚举范围。

那么本题就可以解决了，我们维护一个大根堆，循环 $K$ 次，每次取出堆顶 $(i,j,k)$，删除后加入新的 $(i+1,j,k),(i,j+1,k),(i,j,k+1)$，$K$ 次后直接输出。

注意使用 map 判重，更要注意 map 不能直接映射结构体，需要自定义排序规则。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
ll a[N],b[N],c[N];
int n,k;
ll get(int p1,int p2,int p3){
	return a[p1]*b[p2]+b[p2]*c[p3]+c[p3]*a[p1];
}
struct node{
	int p1,p2,p3;
	bool operator < (const node &xx)const{
		ll w1=get(xx.p1,xx.p2,xx.p3);
		ll w2=get(p1,p2,p3);
		return w1>w2;
	}
};
priority_queue<node> q;
int dx[]={0,0,1},dy[]={0,1,0},dz[]={1,0,0};
struct node2{
	int p1,p2,p3;
	bool operator < (const node2 &xx)const{
		if(xx.p1!=p1) return xx.p1>p1;
		if(xx.p2!=p2) return xx.p2>p2;
		return xx.p3>p3; 
	}
};
map<node2,bool> mp;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
	sort(a+1,a+1+n),sort(b+1,b+1+n),sort(c+1,c+1+n);
	reverse(a+1,a+1+n),reverse(b+1,b+1+n),reverse(c+1,c+1+n);
	q.push({1,1,1});
	node aa;
	for(int t=1;t<=k;t++){
		aa=q.top();
		q.pop();
		for(int i=0;i<3;i++){
			int xp1=aa.p1+dx[i],xp2=aa.p2+dy[i],xp3=aa.p3+dz[i];
			if(xp1>n||xp2>n||xp3>n||mp.count({xp1,xp2,xp3})) continue;
			q.push({xp1,xp2,xp3});
			mp[{xp1,xp2,xp3}]=1;
		}
	}
	cout<<get(aa.p1,aa.p2,aa.p3);
	return 0;
}
```

---

## 作者：Thomas0702 (赞：0)

先将 $a,b,c$ 从大到小排序。

# 赛时思路 #
第 $K$ 大问题，立即想到二分。

考虑怎么 check 有多少 $(i,j,k)$ 满足 $a_ib_j+b_jc_k+a_ic_k\geq mid$，如果只枚举其中的一维 $i$，不太能做。尝试枚举两维 $i,j$，那么 $c_k\geq\frac{mid-a_ib_j}{a_i+b_j}$，这样要确定有多少 $k$ 符合条件只需要二分一下。很明显暴力枚举要二分 $O(N^2)$ 次。但是注意到 $K$ 很小，考虑通过这个性质剪枝。

1. 假如我们枚举到 $(i_0,j_0)$，且此时不存在 $k$ 符合条件，那么 $(i_0,j_0+1),\dots,(i_0,N)$ 也一定不存在 $k$ 符合条件，可以直接枚举下一个 $i$ 了。

2. 设当前满足条件的 $k$ 的总数为 $s$，若 $s\geq mid$，那么继续 check 下去不会改变 $s$ 与 $mid$ 的相对大小关系，可以直接 return 了。

对于每个 $i$，都至多有一次二分没找到符合条件的 $k$，剩下的每次二分都至少找到一个符合条件的 $k$。也就是说，有效的二分最多进行 $K$ 次，无效的二分最多进行 $N$ 次。

这样总状态数就是 $O(N+K)$ 了！于是时间复杂度 $O((N+K)\log N\log V)$，常数较小，能跑过去。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void rd(){}
template<typename T,typename... U> void rd(T &x,U&... arg){
	x=0;int f=1,c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
	x*=f;rd(arg...);
}
const int maxn=2e5+5;
int N,K;
ll a[maxn],b[maxn],c[maxn];
inline bool cmp(ll i,ll j){return i>j;};
ll check(ll x){
	ll s=0;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			ll __x=x-a[i]*b[j];
			ll k=upper_bound(c+1,c+N+1,(__x+a[i]+b[j]-1)/(a[i]+b[j]),cmp)-c-1;
			s+=k;
			if(!k||s>K) break;
		}
		if(s>K) break;
	}
	return s;
}
int main(){
	rd(N,K);
	for(int i=1;i<=N;i++) rd(a[i]);
	for(int i=1;i<=N;i++) rd(b[i]);
	for(int i=1;i<=N;i++) rd(c[i]);
	sort(a+1,a+N+1,cmp);
	sort(b+1,b+N+1,cmp);
	sort(c+1,c+N+1,cmp);
	ll l=0,r=3e18;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid)<K) r=mid-1;
		else l=mid+1;
	}
	printf("%lld",r);
	return 0;
}
```

# 赛后 #
看了最优解的代码，发现我傻了。

直接枚举 $i,j,k$，能省掉二分的一个 $\log$，剪枝还是一样，能做到 $O(K\log V)$ 的复杂度。

check 函数：
```cpp
inline ll f(int i,int j,int k){return a[i]*b[j]+b[j]*c[k]+c[k]*a[i];}
ll check(ll x){
	ll s=0;
	for(int i=1;i<=N;i++){
		if(f(i,1,1)<x) break;
		for(int j=1;j<=N;j++){
			if(f(i,j,1)<x) break;
			for(int k=1;k<=N;k++)
				if(f(i,j,k)<x) break;
				else if(++s>=K) return s;
		}
	}
	return s;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

要求的那个东西我简记为 $f_{i,j,k}$，读过题的应该知道是啥。

将三个数组从大到小排序后，我们不难发现 $f_{i,j,k}\ge f_{i+1,j,k},f_{i,j+1,k},f_{i,j,k+1}$。用这个进行类推，不难发现 $i^\prime>i,j^\prime>j,k^\prime>k$ 时恒有 $f_{i,j,k}\ge f_{i^\prime,j^\prime,k^\prime}$。

因此，$i\times j\times k>m$ 的时候（这里的 $m$ 是原题中的 $K$，防重名），所有的 $f_{i^\prime,j^\prime,k^\prime}(i^\prime\le i,j^\prime\le j,k^\prime\le k,不同时满足)\le f_{i,j,k}$。而显然，$f_{i^\prime,j^\prime,k^\prime}$ 的个数 $\ge m$。

所以我们只需要把满足 $i\times j\times k\le m$ 的所有值存下来，再调用一遍 `nth_element` 就行了。

实践出真知，极限数据下这样的 $i,j,k$ 只有 $16782730$ 组，而 `nth_element` 是线性的。三秒时限吸口氧随便跑。实测 $666ms$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[200005],b[200005],c[200005];vector<int>v;
inline int calc(int x,int y,int z){
	return a[x]*b[y]+b[y]*c[z]+c[z]*a[x];
}
signed main(){
	ios::sync_with_stdio(0); 
//	m=2e5; n=2e5; int cnt=0;
//	for(int i=1;i<=m&&i<=n;++i)
//		for(int j=1;i*j<=m&&j<=n;++j)
//			for(int k=1;i*j*k<=m&&k<=n;++k)
//				cnt++;
//	return cout<<cnt<<endl,0;
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>b[i];
	for(int i=1;i<=n;++i) cin>>c[i];
	sort(a+1,a+n+1,greater<int>());
	sort(b+1,b+n+1,greater<int>());
	sort(c+1,c+n+1,greater<int>());
	for(int i=1;i<=m&&i<=n;++i)
		for(int j=1;i*j<=m&&j<=n;++j)
			for(int k=1;i*j*k<=m&&k<=n;++k)
				v.emplace_back(calc(i,j,k));
	nth_element(v.begin(),v.begin()+m-1,v.end(),greater<int>());
	cout<<v[m-1]<<endl; return 0; 
}
```

---

## 作者：stripe_python (赞：0)

赛后 10min 过 F。

看到这个题就想起 [S 组初赛考题](https://www.luogu.com.cn/article/og3zj63g)，所以考虑对值域二分，判断满足 $a_ib_j+a_ic_k+b_jc_k \ge mid$ 的 $(i,j,k)$ 对数是否 $\ge K$。

直接枚举显然 $O(n^3)$，考虑对 $a,b,c$ 排序。这样在枚举的时候就是从大到小，如果 $a_ib_1+a_ic_1+b_1c_1 < mid$，那么后面也不可能满足，直接 `break`。另两重循环同理。注意到，虽然看上去是三重循环，但 $cnt \ge K$ 时即结束判断，也就意味着最多执行 $K$ 次。这也是一个[经典 trick](https://www.luogu.com.cn/problem/P1631)。于是复杂度为 $O(n\log n + K \log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#ifdef SPN_LOCAL
#define debug(x) (cerr << "On Line " << __LINE__ << ": " << #x << " = " << x << endl)
#else
#define debug(x)
#endif

const int N = 2e5 + 5;
#define int long long

int n, K, a[N], b[N], c[N];

int f(int i, int j, int k) {return a[i] * b[j] + a[i] * c[k] + b[j] * c[k];}

bool check(int x) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (f(i, 1, 1) < x) break;
		for (int j = 1; j <= n; j++) {
			if (f(i, j, 1) < x) break;
			for (int k = 1; k <= n; k++) {
				if (f(i, j, k) < x) break;
				if (++cnt >= K) return true;
			}
		}
	} 
	return cnt >= K;
}

void _main() {
	cin >> n >> K;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	sort(a + 1, a + n + 1, greater<int>()), sort(b + 1, b + n + 1, greater<int>()), sort(c + 1, c + n + 1, greater<int>());
	long long l = 0, r = 3e18, res = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1, res = mid;
		else r = mid - 1;
	}
	cout << res;
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr), cerr.tie(nullptr);
	
	int t = 1; for (/*cin >> t*/; t--; ) _main();
	return 0;
}
```

---

## 作者：Aegleseeker_ (赞：0)

最水的一集。难度远小于 [D](https://www.luogu.com.cn/article/jtuoij9t) 和 [E](https://www.luogu.com.cn/article/4tim8n7t)。

如果你做过 [这道题](https://www.luogu.com.cn/problem/P1631) 的话，那么你就会发现本题所用的思想完全一致。

优先队列调整法固然是一种很经典的 trick，不过这里我们考虑更为巧妙的东西。

如果我们将 $a_i,b_i,c_i$ 按降序排序，令 $f(i,j,k)=a_i\times b_j+b_j\times c_k+c_k\times a_i$，则显然 $f(i,j,k)\le f(i,j,k+b)$。同理，我们可以得出这样一条结论：

若 $i\times j\times k>n$，则必存在至少 $n$ 个三元组的 $f$ 大于等于 $f(i,j,k)$，既 $f(i,j,k)$ 不可能在第 $n$ 大内。

该结论比较显然，读者不妨尝试一下证明。

容易发现将上式的 $n$ 替换成 $K$，我们同样能保证所有 $i\times j\times k$ 满足要求的三元组都一定在前 $K$ 大内。于是我们枚举 $i,j,k$ 只需枚举到乘积大于 $K$ 即可。然后就可以随便做了，比如放进优先队列里或二分。

代码大概长这样：

```cpp
for(int i=1;i<=n;i++){
		for(int j=1;j<=n&&1ll*i*j<=K;j++){
			for(int k=1;k<=n&&1ll*i*j*k<=K;k++){
				q.push(1ll*a[i]*b[j]+1ll*b[j]*c[k]+1ll*c[k]*a[i]);
			}
		}
	}
```

我们不妨分析一下复杂度，$\sum\limits_{i=1}^n \sum\limits_{j\le \frac{n}{i}} \frac{n}{ij}$，这个东西一眼 $O(n\ln^2 n)$ 左右吧，显然能过。

当然注意到如果如果值域小的话可以二分答案套 3sum（好像是有基于值域的多项式做法？我不会 qwq）但是我并不会。

submission：https://atcoder.jp/contests/abc391/submissions/62280753

---

## 作者：light_searcher (赞：0)

赛时被 `map` 里套结构体恶心到了，导致没场切，长记性了。

令 $f(i,j,k)=a_ib_j+a_ic_k+b_jc_k$。首先将三个序列从小到大排序，那么 $f(n,n,n)$ 无疑就是最大值，那么接下来 $f(n-1,n,n),f(n,n-1,n),f(n,n,n-1)$ 都可能成为次大值，这启示我们用大根堆，每次取出最大的一个值，设它是 $f(i,j,k)$，然后把 $f(i-1,j,k),f(i,j-1,k),f(i,j,k-1)$ 中没入过队的入队，然后重复 $k$ 次即可，可以用 `map` 去重。

这样做的时间复杂度是 $\mathcal O(n \log n+k \log k)$。

Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,k,a[N],b[N],c[N];
struct node{
	int v,idxa,idxb,idxc;
	bool operator<(node k)const{
		if(v!=k.v) return v<k.v;
		if(idxa!=k.idxa) return idxa<k.idxa;
		if(idxb!=k.idxb) return idxb<k.idxb;
		return idxc<k.idxc;
	}
};
priority_queue<node>q;
map<node,bool>mp;
int f(int i,int j,int k){
	return a[i]*b[j]+a[i]*c[k]+b[j]*c[k];
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	sort(c+1,c+n+1);
	q.push({f(n,n,n),n,n,n});
	mp[{f(n,n,n),n,n,n}]=1;
	for(int i=1;i<k;i++){
		int idxa=q.top().idxa,idxb=q.top().idxb,idxc=q.top().idxc,A=f(idxa-1,idxb,idxc),B=f(idxa,idxb-1,idxc),C=f(idxa,idxb,idxc-1);
		q.pop();
		if(idxa>1&&!mp[{A,idxa-1,idxb,idxc}]){
			mp[{A,idxa-1,idxb,idxc}]=1;
			q.push({A,idxa-1,idxb,idxc});
		}
		if(idxb>1&&!mp[{B,idxa,idxb-1,idxc}]){
			mp[{B,idxa,idxb-1,idxc}]=1;
			q.push({B,idxa,idxb-1,idxc});
		}
		if(idxc>1&&!mp[{C,idxa,idxb,idxc-1}]){
			mp[{C,idxa,idxb,idxc-1}]=1;
			q.push({C,idxa,idxb,idxc-1});
		}
	}
	printf("%lld",q.top().v);
	return 0;
}

---

## 作者：Milky_Cat (赞：0)

我菜炸了，这个 trick 我会，结果这题做了半个多小时。

令 $f(i,j,k)$ 表示 $A_iB_j+B_jC_k+C_kA_i$。

若数组 $A,B,C$ 均单调不减。

显然有：

+ $f(i-1,j,k)\leq f(i,j,k)$。

+ $f(i,j-1,k)\leq f(i,j,k)$。

+ $f(i,j,k-1)\leq f(i,j,k)$。

然后直接开个堆从 $f(n,n,n)$ 开始广搜，不断 $-1$，hash 判重就好了。

[评测链接](https://atcoder.jp/contests/abc391/submissions/62298414)

---

