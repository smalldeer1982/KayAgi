# [ARC149B] Two LIS Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc149/tasks/arc149_b

数列 $ P\ =\ (P_1,\ \ldots,\ P_N) $ に対し，その最長増加部分列の長さを $ \mathrm{LIS}(P) $ と書くことにします．

$ 1 $ 以上 $ N $ 以下の整数からなる順列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ および $ B\ =\ (B_1,\ \ldots,\ B_N) $ が与えられます．これらの数列に対して，以下の操作を何度でも行うことができます（$ 0 $ 回でもよいです）．

- $ 1\leq\ i\leq\ N-1 $ となる整数 $ i $ をひとつ選ぶ．$ A_i $ と $ A_{i+1} $ をスワップし，$ B_i $ と $ B_{i+1} $ をスワップする．

操作結果の $ \mathrm{LIS}(A)\ +\ \mathrm{LIS}(B) $ としてありうる最大値を答えてください．

 最長増加部分列とは 数列の部分列とは，数列から $ 0 $ 個以上の要素を取り除いた後，残りの要素を元の順序で連結して得られる数列のことをいいます． 例えば，$ (10,30) $ は $ (10,20,30) $ の部分列ですが，$ (20,10) $ は $ (10,20,30) $ の部分列ではありません．

 数列の最長増加部分列とは，数列の狭義単調増加な部分列のうち，長さが最大のもののことをいいます．

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\leq\ A_i\leq\ N $
- $ 1\leq\ B_i\leq\ N $
- $ i\neq\ j $ ならば $ A_i\neq\ A_j $ かつ $ B_i\neq\ B_j $

### Sample Explanation 1

例えば次のように操作を行うことで，$ \mathrm{LIS}(A)\ +\ \mathrm{LIS}(B)\ =\ 8 $ を達成できます． - $ i\ =\ 2 $ として操作を行う．$ A\ =\ (5,1,2,4,3) $, $ B\ =\ (3,2,1,5,4) $ となる． - $ i\ =\ 1 $ として操作を行う．$ A\ =\ (1,5,2,4,3) $, $ B\ =\ (2,3,1,5,4) $ となる． - $ i\ =\ 4 $ として操作を行う．$ A\ =\ (1,5,2,3,4) $, $ B\ =\ (2,3,1,4,5) $ となる． このとき $ A $ は最長増加部分列 $ (1,2,3,4) $ を持ち，$ \mathrm{LIS}(A)=4 $ が成り立ちます．$ B $ は最長増加部分列 $ (2,3,4,5) $ を持ち，$ \mathrm{LIS}(B)=4 $ が成り立ちます．

### Sample Explanation 2

操作を $ 1 $ 度も行わないことにより，$ \mathrm{LIS}(A)\ +\ \mathrm{LIS}(B)\ =\ 10 $ を達成できます．

## 样例 #1

### 输入

```
5
5 2 1 4 3
3 1 2 5 4```

### 输出

```
8```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1 2 3 4 5```

### 输出

```
10```

# 题解

## 作者：_zzzzzzy_ (赞：4)

# 思路
因为我们要求的是一个状态无法通过一个操作让答案变得更优秀的序列，那么考虑构造。

发现当 $a$ 有序的时候无法通过移动一个位置让两个同时增加贡献，那么问题就转化为了把 $a$ 当成第一关键字排序，然后对 $b$ 进行计算 LIS。

然后因为 $a$ 是有序的，所以答案就是 $b$ 的 LIS 加上 $n$。

具体的因为 $a$ 是排列，所以可以直接输入的时候就排好序，然后对 $b$ 跑 LIS，复杂度 $O(n\log n)$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
int n, a[maxn], b[maxn];
int dp[maxn], len = 1;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[a[i]];
    }
    dp[1] = b[1];
    for (int i = 2; i <= n; i++) {
        if (b[i] > dp[len]) {
            dp[++len] = b[i];
        } else {
            dp[lower_bound(dp + 1, dp + len + 1, b[i]) - dp] = b[i];
        }
    }
    cout << len + n << "\n";
    return 0;
}

```

---

## 作者：mlvx (赞：4)

易发现当 $a$ 升序时，答案不会再增加。

故 $a$ 升序时，答案取得最大值。

接下来就变成了求排列的最长上升子序列。

令 $dp_{a_i}$ 表示以 $i$ 结尾的最长上升子序列长度。

则 $dp_{a_i}=\max\{dp_j\}+1(1\le j<a_i)$。

问题即带修前缀最大值，线段树或树状数组维护 $dp$ 数组即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pl (p<<1)
#define pr (p<<1|1)
const int N=3e5+10;
int n,ans;
struct node{int a,b;}a[N];
struct SGT{
    int mx[N<<2];
    void pushup(int p){mx[p]=max(mx[pl],mx[pr]);}
    void update(int l,int r,int k,int v,int p){//单点修改
        if(l==r)return mx[p]=v,void();
        int mid=l+r>>1;
        if(k<=mid)update(l,mid,k,v,pl);
        else update(mid+1,r,k,v,pr);
        pushup(p);
    }int query(int l,int r,int le,int ri,int p){//区间最大值
        if(l>=le&&r<=ri)return mx[p];
        int mid=l+r>>1,ret=0;
        if(le<=mid)ret=max(ret,query(l,mid,le,ri,pl));
        if(ri>mid)ret=max(ret,query(mid+1,r,le,ri,pr));
        return ret;
    }
}T;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i].a);
    for(int i=1;i<=n;i++)scanf("%d",&a[i].b);
    sort(a+1,a+n+1,[](node x,node y){return x.a<y.a;});
    for(int i=1;i<=n;i++)T.update(1,n,a[i].b,(a[i].b!=1?T.query(1,n,1,a[i].b-1,1):0)+1,1);//状态转移
    for(int i=1;i<=n;i++)ans=max(ans,T.query(1,n,a[i].b,a[i].b,1));//取dp[i]的最大值
    printf("%d",ans+n);
    return 0;
}
```

---

## 作者：smydahaoren (赞：3)

### 题目大意：

给定两个序列 $A$，$B$。

可以任意的交换 $A_i$ 与 $A_{i+1}$ 但同时要交换 $B_i$ 与 $B_{i+1}$ 交换。

### 解题思路：

首先猜结论，把 $A$ 排成 $1$，$2$，$3$，$\cdots$，$N$，然后求出被改过的的 $B$ 的 $\text{LIS}$。

证明结论，放两张官方题解的图便于理解。


橙色的代表在该数列的 $\text{LIS}$ 里面，白色则代表不在。

![](https://pic1.zhimg.com/80/v2-d4eab1656a80ab3d79395861d7588588_720w.webp)
第一种情况，$A$ 数列在排序时，把一个对应不在 $B$ 数列的 $\text{LIS}$ 序列的数，排序之后，还是不在 $\text{LIS}$ 序列里面，所以这种情况，总 $\text{LIS}$ 长度加一。

![](https://pic4.zhimg.com/80/v2-305cb689700ccd73926e6b8e9342ff4f_720w.webp)

第二种情况，$A$ 数列在排序时，把一个对应在 $B$ 数列的 $\text{LIS}$ 序列的数，排序之后变成不在 $\text{LIS}$ 序列里面，所以这种情况，总 $\text{LIS}$ 长度加零。

第三种情况，$A$ 数列在排序时，把一个对应不在 $B$ 数列的 $\text{LIS}$ 序列的数，排序之后变成在 $\text{LIS}$ 序列里面，所以这种情况，总 $\text{LIS}$ 长度加二。

第四种情况，$A$ 数列在排序时，把一个对应在 $B$ 数列的 $\text{LIS}$ 序列的数，排序之后还是在 $\text{LIS}$ 序列里面，所以这种情况，总 $\text{LIS}$ 长度加一。

可以看到，在每次操作中，$\text{LIS}$ 总和至少不会减小，在 $A$ 所消除的逆序数对肯定大于 $B$ 数列的减小个数，所以即使是最坏情况 $\text{LIS}$ 也会是 $A$ 数列所产生的 $n$。

### Code:

因为 $A_i$ 和 $B_i$ 是对应的，所以在把 $A$ 排成有序数对后，相应的 $B$ 数列就确定了。


所以定义一个结构体储存。

```
struct f{
     int x,y;
}a[N];
```

然后因为需要排序 $A$ 数列，所以定义比较规则。

```
bool cmp(const f& a,const f& b){
	return a.x<b.x;
}
```

排序。

```
sort(a+1,a+n+1,cmp);
```


在排序完之后，确定了了 $B$ 序列，直接求 $B$ 的 $\text{LIS}$ 就可以了。

```
dp[++lis]=a[1].y;
for(int i=1;i<=n;i++){
	if (a[i].y>dp[lis]) dp[++lis]=a[i].y;
	else *lower_bound(dp+1,dp+n+1,a[i].y)=a[i].y;
}
```

最后输出。

```
cout<<n+lis;
```


结束。

---

## 作者：CReatiQ (赞：2)

### 题意概述

给定长为 $n$ 的两排列 $A,B$，允许进行操作：将 $A_i,B_i$ 同时与 $A_{i+1},B_{i+1}$ 交换，求二者 $\text{LIS}$ 最大和。

---

### 思路一

有一个在反悔贪心中常用的技巧：将序列按照某一关键字排序，之后考虑每次交换对答案产生的贡献。这个技巧在这里也能使用。

我们将序列交换至 $A$ 单调递增，此时若进行交换操作，$A$ 中 $\text{LIS}$ 必然减小，$B$ 中 $\text{LIS}$ 可能增大，增大值小于等于减小值（当且仅当 $A$ 与 $B$ 只有被操作的两位不同时，增大值等于减小值）。

$A$ 中之前被拆断的一段递增序列不会经过操作后重新连起来，否则这个操作就是冗余的，所以如此经过若干次操作之后答案小于等于 $A$ 单调递增时的答案。

---

### 思路二

考虑把序列拆成 $(A_i,B_i)$ 这样的 $n$ 个二元组，然后一个一个往序列里插入。

如果插入后有一个位置的二元组在 $A,B$ 中都不对 $\text{LIS}$ 产生贡献，我们可以将它移位使它至少在 $A,B$ 一者中对 $\text{LIS}$ 产生贡献，所以有：最优解的每个二元组一定对答案产生了贡献。

对于一个最优解，如果有二元组只对 $B$ 的 $\text{LIS}$ 产生贡献，我们可以通过移位使它仅对 $A$ 产生贡献（因为已经是最优解，不可能通过移位使它同时对两者产生贡献）。

所以使 $A$ 单调递增的序列一定是最优解之一。

---

### Code

以 $A$ 为关键字排序后写一个 $\mathcal{O}(n \log n)$ 的 $\text{LIS}$ 即可。

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
#define MAXN (int)(3e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)

int n,top,f[MAXN];
pair<int,int> A[MAXN];

inline int read()
{
	int x=0,f=1;char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f*x;
}

inline int crq_max(int x,int y) { return x>y?x:y; }

int main()
{
	n=read();
	rep(i,1,n) A[i].first=read();
	rep(i,1,n) A[i].second=read();
	sort(A+1,A+n+1);
	rep(i,1,n)
		if (A[i].second>f[top]) f[++top]=A[i].second;
		else *lower_bound(f+1,f+top+1,A[i].second)=A[i].second;
	printf("%d",n+top);
	return 0;
}
```


---

## 作者：pioneer2000 (赞：2)

前言：感谢  [Fa_Nanf1204](https://www.luogu.com.cn/user/1054528)  的帮助，树状数组维护写挂了自己没发现（太弱了。


我看题解里都是用二分写的，那我就来发一篇用树状数组维护的题解吧。

不难发现若 $a$ 数组升序排列，则 LIS 的最大值不会再改变（因为当 $a$ 数组升序排列后，再改变 $a$ 的顺序，最多只能使 $b$ 的 LIS 加一，其 LIS 的总和不变）。

所以只要将 $a$ 数组升序排列，再计算 $b$ 数组的 LIS 即可，这里我们可以用树状数组维护以当前点为末尾的前 $i$ 项的最长子序列，最后统计 $ans$ 取最大值即可。


## code

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=3e5+5;
ll n,maxn,b[N],ans=0,dp[N];
struct node{
    ll x,y;
}a[N];
bool cmp(node b,node c){
    return b.x<c.x;
}
ll lowbit(ll x){
    return x&-x;
}
void update(ll x,ll k){
    for(int i=x;i<=n;i+=lowbit(i)){
        b[i]=max(b[i],k);
    }
}
ll query(ll x){
    ll ret=0;
    for(int i=x;i;i-=lowbit(i)){
        ret=max(ret,b[i]);
    }
    return ret;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x;
        dp[i]=1;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i].y;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        dp[i]=max(dp[i],query(a[i].y)+1);
        update(a[i].y,dp[i]);
        ans=max(ans,dp[i]);
    }
    cout<<ans+n;
    return 0;
}

```

---

## 作者：Fa_Nanf1204 (赞：2)

### 分析：
首先容易观察到，如果当 $a$ 数组有序时，此时是最佳状态。

给出证明：因为 $a$ 数组有序时，此时再进行交换的话，$a$ 数组的贡献一定减 $1$，而 $b$ 数组的贡献最大才加 $1$，所以此时的状态是最优的。

那么将 $a$ 数组排序，计算对应的 $b$ 数组的最长上升子序列长度即可。

因为序列是个排列，所以可以 $O(n \log n)$ 的时间复杂度做最长上升子序列。相信大家都会，笔者这里采用了树状数组维护前缀最大值的方法维护最长上升子序列，就不过多讲述了。
### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define N 300005
#define lowbit(i) (i&-i)
using namespace std; 
int n;
struct node{
	int a,b;
}e[N];
bool cmp(node x,node y){
	return x.a<y.a;
}
int dp[N];
int tr[N];
void update(int x,int v){
	for(int i=x;i<=n;i+=lowbit(i)){
		tr[i]=max(tr[i],v);
	}
}
int query(int x){
	int sum=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		sum=max(sum,tr[i]);
	}
	return sum;
}
int ans=0;
int main(){
	cin.tie(),cout.tie(),ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>e[i].a;
		dp[i]=1;
	}
	for(int i=1;i<=n;i++){
		cin>>e[i].b;
	}
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++){
		dp[i]=max(dp[i],query(e[i].b)+1);
		//cout<<query(e[i].b)<<'\n';
		update(e[i].b,dp[i]);
		ans=max(ans,dp[i]);
	}
	cout<<ans+n;
	return 0;
}
```

---

## 作者：Register_int (赞：1)

首先用冒泡排序以 $A$ 为关键字排序。容易发现，每一次在 $A$ 中的交换都会至少消除 $1$ 个逆序对，那么 $A$ 的 $\text{LIS}$ 增加的次数必然大于等于 $B$ 中 $\text{LIS}$ 的减小次数。排序后求个 $\text{LIS}$ 即可。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;

int n, a[MAXN], b[MAXN];

int dp[MAXN], len;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[a[i]]);
	dp[++len] = b[1];
	for (int i = 2; i <= n; i++) {
		if (b[i] > dp[len]) dp[++len] = b[i];
		else *lower_bound(dp + 1, dp + len + 1, b[i]) = b[i];
	}
	printf("%d", len + n);
}

```

---

## 作者：Naganorhara_Yoimiya (赞：0)

## 题解：AT_arc149_b [ARC149B] Two LIS Sum
人类智慧题。

前置知识：$O(n \log n)$ 求最长上升子序列。

容易发现一个性质：在 $A$ 数组有序的时候（即此时最长上升子序列长度和至少为 $n+1$），两数组最长上升子序列长度最长。

打之前是口胡的，下面给出证明：

因为在相同位置上 $A$ 和 $B$ 对应的数字一定不会变，因此一次交换 $A$ 和 $B$ 相同的元素会减少一组逆序对或者不减少逆序对，因此以 $A$ 为关键字排序之后对 $B$ 做 LIS 一定不劣。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
const int maxn = 3e5+100;
struct node{int a,b;} p[maxn+100];
bool cmp(node A,node B){
	if(A.a == B.a) return A.b < B.b;
	return A.a < B.a; 
}
int dp[maxn+100],l[maxn+100];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> p[i].a;
	for(int i = 1;i <= n;i++) cin >> p[i].b;
	sort(p+1,p+1+n,cmp);
	for(int i = 1;i <= n;i++) l[i] = p[i].b;
	int cnt = 0;
	dp[++cnt] = l[1];
	for(int i = 2;i <= n;i++){
		int t = lower_bound(dp+1,dp+1+cnt,l[i]) - dp;
		if(t == cnt + 1) dp[++cnt] = l[i];
		else dp[t] = l[i];
	}
	cout << n + cnt;
	return 0;
}
```

---

