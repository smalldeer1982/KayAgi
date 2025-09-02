# [ABC190F] Shift and Inversions

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc190/tasks/abc190_f

$ 0,\ 1,\ 2,\ \dots,\ N\ -\ 1 $ を並び替えた数列 $ A\ =\ [a_0,\ a_1,\ a_2,\ \dots,\ a_{N-1}] $ が与えられます。  
 $ k\ =\ 0,\ 1,\ 2,\ \dots,\ N\ -\ 1 $ のそれぞれについて、$ b_i\ =\ a_{i+k\ \bmod\ N} $ で定義される数列 $ B\ =\ [b_0,\ b_1,\ b_2,\ \dots,\ b_{N-1}] $ の転倒数を求めてください。

 転倒数とは 数列 $ A\ =\ [a_0,\ a_1,\ a_2,\ \dots,\ a_{N-1}] $ の転倒数とは、$ i\ かつ\ a_i\ >\ a_j $ を満たす添字の組 $ (i,\ j) $ の個数のことです。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ <\ =\ N\ <\ =\ 3\ \times\ 10^5 $
- $ a_0,\ a_1,\ a_2,\ \dots,\ a_{N-1} $ は $ 0,\ 1,\ 2,\ \dots,\ N\ -\ 1 $ の並び替えである

### Sample Explanation 1

$ A\ =\ [0,\ 1,\ 2,\ 3] $ です。 $ k\ =\ 0 $ のとき、$ B\ =\ [0,\ 1,\ 2,\ 3] $ の転倒数は $ 0 $ です。 $ k\ =\ 1 $ のとき、$ B\ =\ [1,\ 2,\ 3,\ 0] $ の転倒数は $ 3 $ です。 $ k\ =\ 2 $ のとき、$ B\ =\ [2,\ 3,\ 0,\ 1] $ の転倒数は $ 4 $ です。 $ k\ =\ 3 $ のとき、$ B\ =\ [3,\ 0,\ 1,\ 2] $ の転倒数は $ 3 $ です。

## 样例 #1

### 输入

```
4
0 1 2 3```

### 输出

```
0
3
4
3```

## 样例 #2

### 输入

```
10
0 3 1 5 4 2 9 6 8 7```

### 输出

```
9
18
21
28
27
28
33
24
21
14```

# 题解

## 作者：briquette (赞：2)

# 题意
给你一个数列，每一次循环左移一次，持续 $n-1$ 次，求每一次有多少个逆序对。
# 思路
想到逆序对的做法有分治和树状数组，但都多余了，因为我们很明显和可以从上一次的答案推到这一次的，因为如果除了从开头放到结尾的数之外，都不会造成贡献，所以我们假设那个从开头放到结尾的数为 $k$，这样的话，放在开头的时候，只有 $k$ 个数字比他小，所以贡献要减去 $k$，然后挪到后面了，有 $n-k-1$ 个数字比他大，那么贡献加上这个数字即可，第一次求答案可以用分治。
# Code
```cpp
#include<bits/stdc++.h>

#define endl '\n'
#define ll long long
using namespace std;

ll n,num1[300009],num2[300009],num3[300009],ans;

inline void Sort(ll l,ll r)
{
	ll mid=(l+r)/2,lt=l,rt=mid+1,cnt=l;

	if(l==r) 
    {
        return;
    }
	else 
    {
        Sort(l,mid);
        Sort(mid+1,r);
    }

	while(lt<=mid && rt<=r)
    {
		if(num1[lt]>num1[rt])
        {
            num3[cnt]=num1[rt];
            ans=ans+mid-lt+1;
            cnt++;rt++;
        }
		else 
        {
            num3[cnt]=num1[lt];
            cnt++;
            lt++;
        }
    }
	while(lt<=mid)
    {
        num3[cnt]=num1[lt];
        cnt++;
        lt++;
    }
	while(rt<=r)
    {
        num3[cnt]=num1[rt];
        cnt++;
        rt++;
    }
	for(int i=l;i<=r;i++)
    {
        num1[i]=num3[i];
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>num1[i];
        num2[i]=num1[i];
    }

    Sort(1,n);
    for(int i=1;i<=n;i++)
    {
        num1[i]=num2[i];
    }
    cout<<ans<<endl;
    
    for(int i=1;i<n;i++)
    {
        ans=ans-num1[i];
        ans=ans+n-num1[i]-1;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：abensyl (赞：1)

原题：[[ABC190F] Shift and Inversions](https://www.luogu.com.cn/problem/AT_abc190_f)。

## 思路

一道关于逆序对的模板题。

首先求出在不变换之前的逆序对数量，再考虑每次将第一个元素移到最后的时候对答案的改变值。

对于每次改变对于答案的改变值是多少呢？

考虑逆序对的定义为，$i<j$ 且 $a_i>a_j$，当一个数在第一个位置的时候，对于所有其他元素，都满足 $i<j$ 这个条件（$i$ 在这里就是第一个元素的下标 $1$，而 $j$ 就是 $[1,n]$ 中的下标），而因为这是一个排列，所以后面的数字比它小的个数就是 $i$（因为是 $[0,n)$ 的排列），它所产生的逆序对就是 $a_i$，而一到后面以后。

同样的思路，可以得到它将产生的逆序对为 $n-a_i-1$。

树状数组求逆序对为 $O(n\log n)$，计算每次改变 $O(1)$，共计算 $n$ 次，所以为总共为 $O(n)$，总时间复杂度为 $O(n\log n)$，可过。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&-i)
using namespace std;
const int N = 5e5 + 5;
int a[N],tr[N];
void update(int u,int x) {
	for(int i=u;i<N;i+=lowbit(i))
		tr[i]+=x;
}
int query(int u) {
	int res=0;
	for(int i=u;i;i-=lowbit(i)) 
		res+=tr[i];
	return res;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),
	cout.tie(nullptr);
	int n,res=0;
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i],a[i]++;
    //在这里，对每个 a[i] 都加上了 1，因为树状数组下表是从 1 开始的
	for(int i=1;i<=n;++i) {
		res+=i-1-query(a[i]);
		update(a[i],1);
	} cout<<res<<'\n';
	for(int i=1;i<n;++i) {
		res=res+(n-a[i])-a[i]+1;
        //由于每个 a[i] 都被加了 1，所以调整操作与前文的描述有所不同，不过大体思路一致，很容易理解
		cout<<res<<'\n';
	}
	return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[[ABC190F] Shift and Inversions](https://atcoder.jp/contests/abc190/tasks/abc190_f)

Atcoder Problems 评分：$\color{Cyan}1321$

考虑当数列的第一个数变为最后一个数时逆序对数量的变化。

假设当前数列为 $a_1,a_2,\ldots,a_n$，设 $a_1$ 为 $x$。则与 $x$ 构成逆序对的数是**大于 $x$ 的数**，即 $1 \sim x-1$ 这些数与 $x$ 构成逆序对，所以与 $x$ 构成逆序对的数共有 $x-1$ 个。

那么当 $x$ 变为序列中最后一个数时，与之构成的逆序对数又有什么变化呢？很显然，当 $a_1$ 变为 $a_n$ 时（原 $a_2 \sim a_n$ 变为 $a_1 \sim a_{n-1}$），与 $x$ 构成逆序对的为 $x+1\sim n$ 这些数，总共有 $n-x$ 个。

所以，每一次数组左移，整个数列的逆序对数量减少 $a_1-1$，增加 $n-a_1$。

那么这道题就解决了。

最初的逆序对数可以用树状数组求出。

[代码](https://atcoder.jp/contests/abc190/submissions/46984336)，时间复杂度 $O(n\log n)$。

---

## 作者：huyangmu (赞：1)

水题，根本没有绿。

注意到 $n$ 的范围较大，直接模拟肯定不行，考虑每次循环左移会让逆序对减少或增加多少个。

设上一次操作的答案是 $ans$，当前要从第一个移到最后一个的数在原数组中是第 $i$ 个，根据逆序对的定义，把第 $i$ 个移到最后一个，会减少序列中比 $a_{i}$ 小的数的个数，加上序列中比 $a_{i}$ 大的数的个数。又因为序列是一个 $0$ 到 $n-1$ 的全排列，所以当前询问的答案为 $ans+n-1-2 \times a_{i}$。

用树状数组可以快速求出第一次的答案，然后递推求出下一次的答案并输出。


```cpp

#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 3e5 + 5;
int n, a[N], tree[N], ans;
struct Node{
	int x, id;
}b[N];
int lowbit (int x){
	return x & -x;
}
int query (int x){
	int sum = 0;
	while (x){
		sum += tree[x];
		x -= lowbit(x);
	}
	return sum;
}
void update (int x, int val){
	while (x <= n){
		tree[x] += val;
		x += lowbit(x);
	}
	return ;
}
bool cmp (Node x, Node y){
	return x.x > y.x;
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i){
		cin >> a[i];
		b[i].x = a[i];
		b[i].id = i;
	}
	sort(b + 1, b + n + 1, cmp);
	for (int i = 1; i <= n; ++i){
		ans += query(b[i].id - 1);
		update(b[i].id, 1);
	}
	cout << ans << '\n';
	for (int i = 1; i < n; ++i){
		ans = ans + n - 1 - 2 * a[i];
		cout << ans << '\n';
	}
	return 0;
}

---

## 作者：Happy_mouse (赞：0)

# [Shift and Inversions](https://www.luogu.com.cn/problem/AT_abc190_f) 题解
[AC 证明](https://www.luogu.com.cn/record/173650362)
## 分析与解答
挺板的一道题。

因为知道数字的总数，并且数字两两不同，介于 $0$ 到 $n-1$ 之间，则每次轮换可以由轮换前的情况 $O(1)$ 导出。轮换 $n$ 次，总共 $O(n)$，毫无问题。

现在的问题就在于如何求初始逆序对数了。

$n\le 3\times 10^5$，$O(n^2)$ 肯定过不了。

这个数据范围得用差不多 $O(n\log n)$ 过。

emm……树状数组 ~~，就决定是你了~~ ！

这边给没学过的加个餐，会用树状数组求前缀和的直接划走。

-----

前置芝士：[树状数组](https://blog.csdn.net/TheWayForDream/article/details/118436732)。

知道树状数组可以**单点修改，区间查询**；同时联想到逆序对求的是满足 $i<j$ 并且 $a_i>a+j$ 的一对数。那么不难想到把之前的所有数存下来，求出前面有多少个数比当前数大即可。

问题就来了：如何使用树状数组查询比当前数大的数字？

~~聪明的小朋友可能已经发现了，~~ 树状数组可以求区间和。而“比当前数大的数”就处于“当前数”到“无限”的区间内。不过，这个区间太大了，显然是不好求的。

**正难则反。**

求出 $0$ 到“当前数”区间内的数，用总数减去该值，就是比“当前数”大的数的个数了。

不过为什么这种算法的复杂度比较低，有时却要用其他 $O(n^2)$ 的算法来算呢？

注意到前面提到要求出 $0$ 到“当前数”区间内的数，而**树状数组的空间大小是跟所存信息的范围直接挂钩的**。有时数据较大（数组内 $a_i\le 10^9$），数组也就得开到那么多，显然会炸。这题较为特殊，恰好是 $0$ 到 $n-1$，才能使用这种算法。

---

代码实现中有个小坑，需要避开一下：题目给出 $a_i$ 大小为 $0$ 到 $n-1$，但我们惊讶地发现，`lowbit(0)=0`（`lowbit(i)` 表示 `i&-i`，求最低位的 $1$），在加入过程中会直接死循环（我被同样的问题坑过好几次，血与泪的教训啊），因此**输入时** $a_i$ **要加一**。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[300005],s[300005],n;
//a 数组为输入，s 数组为树状数组

//树状数组插入操作
void add(int x){
	for(int i=x;i<=n;i+=i&-i) s[i]++;
}
//树状数组查询操作
int sum(int x){
	int cnt=0;
	for(;x;x-=x&-x) cnt+=s[x];
	return cnt;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	int nxd=0;//求初始逆序对
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]++;//这是刚刚提到的那个坑
		nxd+=i-1-sum(a[i]);
		//i-1 为前面的数字总数
		//sum(a[i]) 算的是前面比 a[i] 小的个数
		add(a[i]);
		//插入 a[i]
	}
	cout<<nxd<<'\n';//输出初始情况
	for(int i=1;i<n;i++){
		nxd=nxd+(n-a[i])-(a[i]-1);
		//n-a[i] 为增加逆序对的个数（比该数大的到该数前面，形成逆序对）
		//a[i]-1 为减少逆序对的个数（比该数到该数小的后面，拆散逆序对）
		cout<<nxd<<'\n';//输出该改变后的情况
	}
	return 0;
}
```
在这里浅浅吐槽一句，怎么有的 dalao 又是莫队又是离散化的，130 多行，反正我是真没看懂……

写题解辛苦，路过/认真看过的大佬们都给个赞呗。

---

## 作者：DerrickLo (赞：0)

先处理出原序列的逆序对。

然后发现如果将第一个数放到最后面，那么逆序对的数量就会加上大于它的数的个数，减去小于他的数的个数。

然后就能动态维护逆序对数了。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&-x
#define int long long
using namespace std;
int n,a[300005],ans;
int tr[300005];
void add(int u,int v){
	for(;u<=300000;u+=lowbit(u))tr[u]+=v;
}
int query(int u){
	int res=0;
	for(;u;u-=lowbit(u))res+=tr[u];
	return res;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]++;
	for(int i=n;i;i--)ans+=query(a[i]),add(a[i],1);
	cout<<ans<<"\n";
	for(int i=1;i<n;i++){
		ans+=n-a[i],ans-=a[i]-1;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：cosf (赞：0)

## [ABC190F](https://www.luogu.com.cn/problem/AT_abc190_f)

首先，如果我们仅仅是求没左移时逆序对的个数，那么可以出门左转，做做 [P1908](https://www.luogu.com.cn/problem/P1908)。

那么，左移一位意味着什么？

相当于，原本第一位所在的所有逆序对都消失了，并且第一位放到了最后后又产生了一些新的逆序对。

这显然可以用树状数组来维护。具体就维护一个比该值大的树状数组和一个比该值小的树状数组，分别统计每个点作为逆序对前面的那一个和后面那一个的个数。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXN 300005
#define lowbit(x) ((x) & -(x))

#define int long long

int n;

int t1[MAXN];

void a1(int p, int v)
{
    while (p <= n)
    {
        t1[p] += v;
        p += lowbit(p);
    }
}

int q1(int p)
{
    int res = 0;
    while (p)
    {
        res += t1[p];
        p -= lowbit(p);
    }
    return res;
}

int t2[MAXN];

void a2(int p, int v)
{
    while (p <= n)
    {
        t2[p] += v;
        p += lowbit(p);
    }
}

int q2(int p)
{
    int res = 0;
    while (p)
    {
        res += t2[p];
        p -= lowbit(p);
    }
    return res;
}

int a[MAXN];

int r[MAXN];

signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        res += q1(n - a[i]);
        a1(n - a[i], 1);
        a2(a[i] + 1, 1);
    }
    r[0] = res;
    for (int i = 1; i < n; i++)
    {
        a2(a[i] + 1, -1); // 先删再算
        a1(n - a[i], -1);
        res -= q2(a[i] + 1);
        res += q1(n - a[i]);
        a1(n - a[i], 1);
        a2(a[i] + 1, 1);
        r[i] = res;
    }
    for (int i = 0; i < n; i++)
    {
        cout << r[i] << endl;
    }
    return 0;
}

```


---

## 作者：xuan_gong_dong (赞：0)

## 题目
[[ABC190F] Shift and Inversions](https://www.luogu.com.cn/problem/AT_abc190_f)
## 分析

首先我们考虑暴力，每次暴力修改，然后重新查询逆序对数的和，时间复杂度为 $O(n^2)$，显然过不了。

但是手玩一下样例可以发现其实只需得出初始状态的逆序对数就好了，每次修改其实就是减去开头数所配对的逆序对数，再加上将它放在末尾所新增的逆序对数，容易发现这两个数分别为 $x$ 和 $n-x+1$。

这样复杂度就是求逆序对的 $O(n \log n)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int b[600010],c[600010];
long long sum=0;
int lowbit(int x) {
	return (-x)&x;
}
void updata(int k,int x) {
	for(int i=k; i<=n; i+=lowbit(i)) {
		c[i]+=x;
	}
}
long long  getsum(int x)
{
	long long sum=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		sum+=c[i];
	}
	return sum;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%d",&b[i]);
		b[i]++;
		b[i+n]=b[i];
	}
	for(int i=1;i<=n;i++)
	{
		updata(b[i],1);
		sum+=i-getsum(b[i]);
	}
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",sum);
		sum-=(b[i]-1);
		sum+=(n-b[i]);
	}
	return 0;
}
```


---

## 作者：Erica_N_Contina (赞：0)

# [ABC190F] Shift and Inversions



## 思路

暴力写法很容易想到也很容易想到时间复杂度过高，所以我们考虑以下内容：**每次我们将数组的第一个数移动到最后一个时，逆序对的数量发生了什么变化？**
 
我们将数组的第一个数移动到最后一个时，对数组的第 $2\sim n$ 个数是没有影响的，只对被移动的数有影响。我们知道当我们把一个数字 $a$ 从开头移动到最后一个时，会有一些与 $a$ 相关的逆序对消失，且逆序对减少的数量等于序列中 $<a$ 的数的数量。同时，也会有一些与 $a$ 相关的逆序对出现，且逆序对增加的数量等于序列中 $>a$ 的数的数量。

那么我们怎么样求出序列中 $>a$（或者 $<a$）的数的数量呢？本来我考虑写线段树啊做映射啊，后来一恍惚，发现数组是个**全排列**呀！那太好办了，序列中 $>a$（或者 $<a$）的数的数量不就是 $n-a$（或者 $a-1$）嘛！

## 代码实现

我们先求出初始状态下的逆序对数量（这边就直接**归并排序**了），然后对于每一次操作，$O(1)$ 更新答案即可。假设第 $i$ 次操作将数字 $a_i$ 从开头调至结尾，那么逆序对数量 $sum$ 就应该变成 $sum+(n-a_i)-(a_i-1) $。

**注意：** 这里我们讨论的序列是 $1\sim n$ 的序列。题目中是 $0\sim n-1$ 的，所以在输入时要 $+1$。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=1e6+5;
const int M=1e3;
const int MOD=903250223;
const int INF=1e9;
//变量
int n,c,sum,res,tmp,cnt,m;
int t[N],b[N],a[N];

void gbsort(int l,int r){//归并排序 
	if(l==r)return ;
	int mid=l+r>>1;
	gbsort(l,mid);gbsort(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid||j<=r){
		if(i>mid)t[k++]=b[j++];
		else if(j>r||b[i]<b[j])t[k++]=b[i++];
		else t[k++]=b[j++],sum+=mid-i+1;//ans存逆序对个数
	}
	for(int i=l;i<=r;i++)b[i]=t[i];
}


signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int t;
		cin>>t;
		b[i]=a[i]=t+1;
	}
	gbsort(1,n);
	cout<<sum<<endl;
//	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
	for(int i=1;i<n;i++){
		sum=sum+(n-a[i])-(a[i]-1);
		cout<<sum<<endl;
	}
	return 0;
}
```




---

## 作者：Bulyly (赞：0)

### 题目大意
给你 $n$ 个 $0$ 到 $n-1$ 全排列的数组，然后这个数组会循环左移 $n-1$
问你这个过程中数组的逆序数对是多少？


------------
### 解析
- 首先考虑先求原始序列的逆序对个数，一定得是 $O(n\log n)$ 的算法，所以可以用归并排序和树状数组来做。这里介绍的是树状数组的做法。

- 考虑先用树状数组的朴素做法求原始序列的逆序对个数，接着如果每一次都像这样跑一遍的是会超时的，所以我们可以考虑找规律，题目的提示性很强。

- 首先每次我们会把当前序列的一个数移到结尾，此时所有比第一个数小的数都在它的后面，逆序对个数应为 $val[i]-1$，所以应该减去。当他插到最后一个位置时，所有比它大的数都在他的前面所以应该加上 $n-val[i]$。整理得，转移时 $ans=ans-a[i]\times2+n+1$。

- 注意：逆序对个数可能会爆 int 范围，$val[i]$ 可能为 $0$。

AC code:
```cpp
#include <cstdio>
#include <cstring>
#include <iostream> 
#include <algorithm>
#define rs register
#define int long long
using namespace std;
const int N=300005;
int a[N],tr[N];
int n,ans;
void add(int x,int v){for(;x<=n;x+=x&-x) tr[x]+=v;}
int ask(int x)
{
	int res(0);
	for(;x;x-=x&-x)  res+=tr[x];
	return res;
}
signed main()
{
	memset(tr,0,sizeof tr);
	scanf("%lld",&n);
	for(rs int i=1;i<=n;i++)  scanf("%lld",&a[i]),a[i]++;
	for(rs int i=n;i>=1;i--)
	{
		ans+=ask(a[i]-1);
		add(a[i],1);
	}
	for(rs int i=1;i<n;i++)
	{
		printf("%lld\n",ans);
		ans+=a[i]*(-2)+n+1;
	}
	printf("%lld\n",ans);
	
	
	return 0;
}
```

完结撒花~

---

## 作者：loser_seele (赞：0)

虽然这题我不会做，但是考虑一个更普通的问题：区间逆序对的计算。这题实际上只是区间逆序对的特殊情况。

显然，区间 $ [l,r] $ 向左右端扩展的贡献都是可以直接用树状数组计算的。

于是可以直接上莫队板子，首先离散化压缩值域，然后离线所有询问之后跑莫队即可，在更新左右扩展的贡献时用树状数组更新答案。

时间复杂度 $ \mathcal{O}(n\sqrt{n}\log{n}) $，不是很优雅的暴力做法，但可以通过。注意数组要开双倍不然会越界。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=600005;
int n,m;ll a[N];
inline int lowbit(int x){return x&-x;}
ll c[N],sizei=0;
int p[N];bool cmp(int x,int y){return a[x]<a[y];}
inline void add(int x,ll k){sizei+=k;for(;x<=n;x+=lowbit(x))c[x]+=k;}
inline ll getsum(int x){ll ans=0;for(;x;x-=lowbit(x))ans+=c[x];return ans;}
ll L[N],R[N];
const int block=800;
struct ASK
{
    int l,r,p;
}ask[N];
inline bool mmp(ASK n1,ASK n2)
{
    if(n1.l/block!=n2.l/block)
  return n1.l<n2.l;
    if((n1.l/block)&1)
                    return n2.r<n1.r;
    return n1.r<n2.r;
}
struct node{int l,r,p,op;};
vector<node>ls[N],rs[N];
int B,bl[N/block+5],br[N/block+5],w[N];
int s[N/block+5],C[N];
ll ret[N],ans[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        p[i]=i;
    }
    for(int i=n+1;i<=2*n;i++)
    {
        a[i]=a[i-n];
        p[i]=i;
    }
    n*=2;
    sort(p+1,p+n+1,cmp);
    ll tmp=a[p[1]];a[p[1]]=1;
    for(int i=2,t=1;i<=n;i++)
    {
        if(a[p[i]]!=tmp)
        t++;
        tmp=a[p[i]];a[p[i]]=t;
    }
    for(int i=1;i<=n;i++)
    {
        L[i]=L[i-1]+sizei-getsum(a[i]);
        add(a[i],1);
    }
    memset(c,0,sizeof(c));
    for(int i=n;i>=1;i--)
    {
        R[i]=R[i+1]+getsum(a[i]-1);
        add(a[i],1);
    }
    m=n/2;
    for(int i=1;i<=m;i++)
    {
        ask[i].l=i,ask[i].r=i+n/2-1;
        if(ask[i].l>ask[i].r)
        swap(ask[i].l,ask[i].r);
        ask[i].p=i;
    }
    sort(ask+1,ask+m+1,mmp);
    ask[0]=(ASK){1,0,0};
    for(int i=1;i<=m;i++)
    { 
        ret[i]=L[ask[i].r]-L[ask[i-1].r]+R[ask[i].l]-R[ask[i-1].l];
             if(ask[i].r>ask[i-1].r)
             rs[ask[i-1].l-1].push_back((node){ask[i-1].r+1,ask[i].r,i,-1});
        else if(ask[i].r<ask[i-1].r)
        rs[ask[i-1].l-1].push_back((node){ask[i].r+1,ask[i-1].r,i, 1});
             if(ask[i].l<ask[i-1].l)
             ls[ask[i  ].r+1].push_back((node){ask[i].l,ask[i-1].l-1,i,-1});
        else if(ask[i].l>ask[i-1].l)
        ls[ask[i  ].r+1].push_back((node){ask[i-1].l,ask[i].l-1,i, 1});
    }
    B=(n-1)/block+1;
    for(int i=1;i<=B;i++) 
    {
        bl[i]=br[i-1]+1;
        br[i]=br[i-1]+block;
    }
    br[B]=n;
    for(int i=1;i<=B;i++)
    for(int j=bl[i];j<=br[i];j++)
    w[j]=i;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<w[a[i]];j++)
        s[j]++;
        for(int j=bl[w[a[i]]];j<=a[i];j++)
        C[j]++;
        for(int j=0;j<rs[i].size();j++)
        {
            node t=rs[i][j];
            int l=t.l,r=t.r;
            tmp=0;
            for(int k=l;k<=r;k++)
            tmp+=s[w[a[k]+1]]+C[a[k]+1];
            ret[t.p]+=t.op*tmp;
        }
    }
    memset(C,0,sizeof(C));
    memset(s,0,sizeof(s));
    for(int i=n;i>=1;i--)
    {
        for(int j=w[a[i]]+1;j<=B;j++)
        s[j]++;
        for(int j=a[i];j<=br[w[a[i]]];j++)
        C[j]++;
        for(int j=0;j<ls[i].size();j++)
        {
            node t=ls[i][j];
            int l=t.l,r=t.r;
            tmp=0;
            for(int k=l;k<=r;k++)
            tmp+=s[w[a[k]-1]]+C[a[k]-1];
            ret[t.p]+=t.op*tmp;
        }
    }
    for(int i=1;i<=m;i++)
    {
        ret[i]+=ret[i-1];
        ans[ask[i].p]=ret[i];
    }
    for(int i=1;i<=m;i++)
    printf("%lld\n",ans[i]);
}
```


---

## 作者：FReQuenter (赞：0)

## 思路

对一个序列求逆序对可以用归并排序或树状数组 $O(n\log n)$ 解决，但如果对每一个 $b$ 求逆序对，则时间复杂度为 $O(n^2\log n)$。我们考虑优化：能不能从上一个状态推算出下一个 $b_i$ 有多少逆序对呢？

我们设 $b$ 是一个 $1$ 至 $n$ 的排列：

- 当 $b_1$ 被去除时，因为 $b_i$ 贡献了 $b_i-1$ 个逆序对，所以从上一轮的答案中减去 $b_i-1$。

- 当 $b$ 的末尾加入 $b_n$ 时，因为会和前面的 $n-b_i$ 个数产生逆序对，所以上一轮的答案累加上 $n-b_i$。

```cpp
#include<iostream>
#include<vector>
using namespace std;
#define int long long
#define lowbit(x) ((x)&(-x))
int c[300005],a[300005],n;
void update(int x,int v){for(int i=x;i<=n;i+=lowbit(i)) c[i]+=v;}
int getsum(int x){int ans=0;for(int i=x;i>=1;i-=lowbit(i)) ans+=c[i];return ans;}
main(){
    int ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]++;
    }
    for(int i=n;i>=1;i--){
        update(a[i],1);
        ans+=getsum(a[i]-1);
    }
    //逆序对个人推荐使用树状数组，常数1/2（当然要离散化的话另说）
    cout<<ans<<'\n';
    for(int i=1;i<n;i++){
        ans+=n-1-(a[i]-1)-(a[i]-1);
        //更新答案
        cout<<ans<<'\n';
    }
}
```

---

