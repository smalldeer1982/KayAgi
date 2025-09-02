# Minimize Inversions

## 题目描述

You are given two permutations $ a $ and $ b $ of length $ n $ . A permutation is an array of $ n $ elements from $ 1 $ to $ n $ where all elements are distinct. For example, an array \[ $ 2,1,3 $ \] is a permutation, but \[ $ 0,1 $ \] and \[ $ 1,3,1 $ \] aren't.

You can (as many times as you want) choose two indices $ i $ and $ j $ , then swap $ a_i $ with $ a_j $ and $ b_i $ with $ b_j $ simultaneously.

You hate inversions, so you want to minimize the total number of inversions in both permutations.

An inversion in a permutation $ p $ is a pair of indices $ (i, j) $ such that $ i < j $ and $ p_i > p_j $ . For example, if $ p=[3,1,4,2,5] $ then there are $ 3 $ inversions in it (the pairs of indices are $ (1,2) $ , $ (1,4) $ and $ (3,4) $ ).

## 说明/提示

In the first test case, the minimum possible number of inversions is $ 10 $ .

In the second test case, we can sort both permutations at the same time. For this, the following operations can be done:

- Swap the elements in the positions $ 1 $ and $ 3 $ in both permutations. After the operation, $ a = $ \[ $ 2,1,3 $ \], $ b = $ \[ $ 2,1,3 $ \].
- Swap the elements in the positions $ 1 $ and $ 2 $ . After the operations, $ a $ and $ b $ are sorted.

In the third test case, the minimum possible number of inversions is $ 7 $ .

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
5 4 3 2 1
3
3 1 2
3 1 2
6
2 5 6 1 3 4
1 5 3 6 2 4```

### 输出

```
3 2 5 1 4
3 4 1 5 2
1 2 3
1 2 3
2 3 4 6 5 1
1 2 4 3 5 6```

# 题解

## 作者：Lu_xZ (赞：4)

### [B. Minimize Inversions](https://codeforces.com/contest/1918/problem/B)

$A : a \ \ \ \ \ xa,xb \ \ \ \ \ b \ \ \ \ \ ya,yb$

$B : c \ \ \ \ \ xc,xd \ \ \ \ \ d \ \ \ \ \ yc,yd$

xa 为 ab 之间小于 a 的个数，ya 为 b 之后小于 a 的个数。

交换前的逆序对数 $w1 = [(xa + ya) + yb] + [((xc + yc) + yd)]$。

交换前的逆序对数 $w2 = [(xb + yb) + ya] + [((xd + yd) + yc)]$。

若交换后更优，则 $xa + xc > xb + xd$。

按照此规律排序能够做到 $O(n^2\log n)$。

构造一种方案满足 $\forall a,\ b,\ c,\ d \ \ \ \ xa + xc \le xb + xd$。

设 $cnt$ 为 $a, b$ 间元素总个数。

显然有 $\forall x \in [0, cnt]$。

如果 A 有序，则 $xa = 0, xb = cnt$。

此时 $xc \le  cnt + xd$，满足条件。

```
void solve() {
	int n; cin >> n;
	vector<int> a(n);
	vector<int> b(n);
	vector<int> c(n);
	for(int &x : a) cin >> x;
	for(int &x : b) cin >> x;
	iota(All(c), 0);
	sort(All(c), [&](int x, int y){
		return a[x] < a[y];
	});
	for(int x : c) cout << a[x] << ' '; cout << '\n';
	for(int x : c) cout << b[x] << ' '; cout << '\n';
}
```

---

## 作者：ylch (赞：2)

# [CF1918B](https://www.luogu.com.cn/problem/CF1918B) Minimize Inversions 题解

## PART1. 解题思路

可以这么考虑，如果两个数组中都有逆序对，那么找两个数组同时是逆序对的位置交换一定最优。

但出题人不会造这样良心的数据，当两个数列中的逆序对数量交叉时，上述方法就不行了。

找找规律，例如 $A=[1,2],B=[2,1]$，这样不管怎么交换都是无解的，逆序对个数永远都是 $1$。

再看一个，$A=[2,1],B=[2,1]$，这时可以交换位置 $1$、$2$ 的元素，使逆序对数量从 $2$ 个变为 $0$ 个。

列举了上面两个例子，我们可以发现，只有同时满足 $a_i > a_j$ 且 $b_i>b_j$ 时交换逆序对数量才会减少，否则不会有变化。

简化一点，就是把其中一个数组排好序，另一个数组跟着一块移动，但不保证有序。这样一个数组逆序对数量为 $0$，另一个不定，是最优的情况。

## PART2. 代码实现

sort 排序可以过，但是可以用一种更简洁的映射（打表）法，配合哈希。

**重点：** 设 $vis_i$ 表示数组 $a$ 中值为 $i$ 的变量对应的 $b$ 数组中的数为 $vis_i$。

因为题目规定 $a,b$ 数组都是包含 $1 \sim n$ 的所有数，且每个数只出现一次，所以可以先直接输出 $1 \sim n$，就相当于排完序的 $a$ 数组；然后输出 $vis_1 \sim vis_5$，表示 $a$ 数组 $1 \sim 5$ 下标对应的 $b$ 数组元素即可。

复杂度 $O(Tn)$，应该是最好做法了。

## PART3. AC 代码

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int N = 2e5 + 10;

int n, m;
vector <int> a, b;
unordered_map <int, int> vis; 

int main() {
    int T; cin >> T;
    while(T --){
        cin >> n; a.resize(n + 1), b.resize(n + 1); // vector下标从0开始，这里是从1开始，所以要开n+1
	    for(int i = 1; i <= n; i ++){
	        cin >> a[i];
	    }
	    for(int i = 1; i <= n; i ++){
	        cin >> b[i];
	        vis[a[i]] = b[i];
	    }
	    for(int i = 1; i <= n; i ++){
	    	cout << i << " ";
	    }
	    cout << endl;
	    for(int i = 1; i <= n; i ++){
	    	cout << vis[i] << " ";
	    }
	    cout << "\n";
	    // 这里不清空a、b、vis是因为它们的值都会在下一轮输入时被覆盖，自然也就没有清空的必要了
    }
    return 0;
}
```

## End

管理员大大辛苦啦~

这里是 [YLCHUP](https://www.luogu.com.cn/blog/YLCHUP/)，谢谢大家！祝大家 AC！

---

## 作者：zhuxiangrui_2010 (赞：2)

# CF1918B Minimize Inversions 题解

## 题意
给定两个排列 $a$ 和 $b$，可以进行任意次操作，每次操作可以同时交换两个排列的相同两个位置，求两个排列的逆序对数量和最小是多少。

## 思路
让逆序最少，也就是让升序更多。易发现当 $a_i < a_j $ 时交换就一定不会增加逆序个数，那么我们只用把每个元素按照 $a_i$ 的值从小到大来排序即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
struct xvlie{
    int x,y;
}q[200010];
bool cmp(xvlie p,xvlie q){
    return p.x<q.x;
}
int main(){
   cin>>t;
   for(int i=1;i<=t;i++){
        int n;
    	cin>>n;
        for(int j=1;j<=n;j++){
            cin>>q[j].x;
        }
        for(int j=1;j<=n;j++){
            cin>>q[j].y;
        }
        sort(q+1,q+n+1,cmp);
        for(int j=1;j<=n;j++){
            cout<<q[j].x<<" ";
        }
        cout<<endl;
        for(int j=1;j<=n;j++){
            cout<<q[j].y<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：yyrwlj (赞：2)

## 题意简述

给定两个排列 $a$ 和 $b$，每次操作可以同时交换两个排列的相同两个位置。

可以操作任意次，求两个排列的逆序对数量和最小是多少。

## 思路

消除掉 $a$ 的一个逆序对**最多**会让 $b$ 产生 $1$ 个逆序对，所以将 $a$ 升序排序，这个过程中逆序对总数是不会增多的。

$a$ 排好序后，若再消除 $b$ 的 $1$ 个逆序对，则必然会使 $a$ 产生 $1$ 个逆序对。所以就不用再交换了。

总而言之，将 $a$ 升序排序，$b$ 跟着 $a$ 变化。

---

## 作者：All_Unluck_Beginning (赞：1)

# CF1918B Minimize Inversions

## 思路

### 暴力
一个一个的算，复杂度巨大。

### 数学规律
让逆序最少，也就是让升序更多。我们可以通过多组数据实验，最终我们会发现，将数列 $A$ 减少一个逆序对，让数列 $B$ 随着 $A$ 变化，最多会只会增加一个逆序对。而让 $A$ 相邻两个数保持升序，$B$ 相邻两个数保持降序再排序，$A$ 数列就会增加一个逆序，$B$ 数列就会减少一个数列，导致不变，所以排序是最好的办法。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int t,n;
struct node{
    int a,b;
}q[200005];
bool cmp(node x,node y){
    return x.a<y.a;
}
int main(){
	cin>>t;
    while(t--){
    	cin>>n;
        for(int i=1;i<=n;i++)cin>>q[i].a;
        for(int i=1;i<=n;i++)cin>>q[i].b;
        sort(q+1,q+n+1,cmp);
        for(int i=1;i<=n;i++)cout<<q[i].a<<" ";
        puts("");
        for(int i=1;i<=n;i++)cout<<q[i].b<<" ";
        puts("");
    }
    return 0;
}
```

---

## 作者：Mashu77 (赞：0)

大致题意：给你两个序列 
 $\{a\},\{b\}$ 满足 $[1,n]$ 
这 $n$
 个数的一个全排序，你可以做任意次操作，每次选择两个下标 $i,j\in[1,n]$
 并同时交换 $a_i$ 与 $a_j$
，$b_i$ 与 $b_j$，使得最终两个序列的逆序对数量之和最小，然后你打印出这两个序列。

先说如何实现：只需要用结构体或者 ```pair<int,int>``` 把两个序列绑定起来，然后按照任意一个序列由小到大排序，得到的就是最优解，实现的时间复杂度是 $O(n\log n)$。当然，我们考虑数据的特殊性，也可以直接使用桶排序，这样时间复杂度是 $O(n)$。 

接下来证明这样是最优解。

对于任意一次交换操作，我们可以视为交换若干次相邻元素的结果。例如将 
$[1,2,3]$ 交换 $1$
 和 $3$
 的位置，结果是 $3,2,1$；我们可以将这个过程视为 $[1,2,3]\rightarrow[2,1,3]\rightarrow[2,3,1]\rightarrow[3,2,1]$。因此，我们只需要考虑每次交换相邻的两个元素对于逆序对之和的影响。

我们假设当前考虑的两个相邻元素分别为 $[a_i,a_{i+1}],[b_i,b_{i+1}]$，因为这两个元素的位置相邻，我们无需考虑交换这两个元素对于其他元素的影响。如果 $a_i<a_{i+1}$
 并且 $b_i<b_{i+1}$，那么我们显然不用交换；如果 
$a_i>a_{i+1}$ 并且 $b_i>b_{i+1}$，那么我们显然要交换；如果 
$a_i<a_{i+1}$ 或者 $a_i>a_{i+1},b_i<b_{i+1}$，交换对于逆序对无影响。但是这样我们无法找到普遍的规律，如果对于 $a_i>a_{i+1},b_i<b_{i+1}$，我们选择交换，这样以上四种情况最终的结果都是 $a_{i+1}$
 。因此我们只需要按照 $a_i$
 从小到大排序就可以了

---

## 作者：Fubaogege (赞：0)

看题可得：  
经过任意次操作交换两个排列相同的位置，求两个排列逆序对数量和最少是多少。

思路：  
~~这么简单的题不用多说吧。~~  
逆序最少等于升序最多。我们只用把每个元素按照 $a_i$ 的值从小到大排序就行。

代码：
```c
   while(cin>>n){
    	t--;if(t==0)return 0;
        for(int i=1;i<=n;i++)cin>>a[j].x;
        for(int i=1;i<=n;i++)cin>>a[j].y;
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=n;i++)cout<<a[j].x<<" ";
        cout<<endl;
        for(int i=1;i<=n;i++)cout<<a[j].y<<" ";
        cout<<endl;
    }
```

---

## 作者：QoQ_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1918B)

本蒟蒻的第二篇题解，望过 QAQ~

好了废话不多说，步入正题：

---

### 题意

输入两个长度为 $n$ 的数列，交换 $A_i$ 和 $A_j$，再交换 $B_i$ 和 $B_j$，使数列的逆序对的个数的和最小。

### 思路

这一题如果你直接一个一个交换判断的话，未免也太麻烦了，所以我是先从规律入手：使逆序最少，也就是让升序更多，那么我们就可以用从小到大排序的方式来减少逆序个数。经测试，将数列 $A$ 减少一个逆序对，让数列 $B$ 随着 $A$ 变化，**最多**会增加一个逆序对。而让 $A$ 相邻两个数保持升序，$B$ 相邻两个数保持降序再排序，$A$ 数列就会增加一个逆序，$B$ 数列就会减少一个数列，导致不变，所以排序是最好的办法。

### code 参考
```
#include<bits/stdc++.h>
using namespace std;
int T,n;
struct some{
    int A;
    int B;
}arr[200005];
bool cmp(some x,some y){
    return x.A<y.A;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&arr[i].A);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&arr[i].B);
        }
        sort(arr+1,arr+n+1,cmp);
        for(int i=1;i<=n;i++){
            printf("%d ",arr[i].A);
        }
        printf("\n");
        for(int i=1;i<=n;i++){
            printf("%d ",arr[i].B);
        }
        printf("\n");
    }
    return 0;
}
```
完结撒花~

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/1918/B)|[链接](https://www.luogu.com.cn/problem/CF1918B)

### 题目分析

只需用操作将任意一个数组按升序排序即可。

当每次交换相邻两个数时可以对数组排序且不增加逆序对。证明：

1. $a$ 数组相邻两数与 $b$ 数组相邻两数均升序，此时排序不会改变其升序。

1. $a$ 数组相邻两数与 $b$ 数组相邻两数均降序，此时排序会使两数组均减少 $1$ 逆序对。

1. $a$（$b$）数组相邻两数升序，$b$（$a$）数组相邻两数均降序，此时排序会使两数组一个减少 $1$ 逆序对，一个增加 $1$ 逆序对，最终不变。

故排序后逆序对最少。

### 参考代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
struct node{
	int a,b;
}e[200005];
int t,n;
bool cmp(node na,node nb)
{
	return na.a<nb.a;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&e[i].a);
		for(int i=1;i<=n;i++)scanf("%d",&e[i].b);
		sort(e+1,e+n+1,cmp);
		for(int i=1;i<=n;i++)printf("%d ",e[i].a);
		putchar('\n');
		for(int i=1;i<=n;i++)printf("%d ",e[i].b);
		putchar('\n');
	}
	return 0;
}
```
感谢阅读。

---

## 作者：Floating_Trees (赞：0)

### 题意
给定两个长度为 $n$ 的序列 $a$ 和 $b$ ，定义一次操作为：
+ 选择两个正整数 $i,j \in [1,n]$，交换 $a_i,a_j$ 和 $b_i,b_j$。

你可以进行任意次操作，请最小化两个序列逆序对个数之和，输出操作后的序列。
### 思路
先上思路：将其中一个序列按升序排序，另一个随之变动。可问题是要怎么证明这样的是最优？果能证明交换过后第一个序列增多的逆序对的个数 $\le$ 第二个序列减少的逆序对的个数，那么这样就是最优的。比如说序列 $\{1,2,3,4,5\}$ 和 $\{5,4,3,2,1\}$，交换 $a_1,a_5,b_1,b_5$，第二个序列减少的逆序对的个数是最大的，但仍然大于等于的一个序列增加的逆序对的个数。也就是说，再第二个序列减少的逆序对的个数最多时，还是大于等于第一个序列增加的逆序对的个数，是最优的，那么其他情况下，也一定是最优的。
### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = (int)2e5 + 10;
int T, n;
struct node {
	int a,b;
} u[N];
bool cmp(node x, node y)
{
	return x.a < y.a;
}

int main()
{
	scanf ("%d",&T);
	while  (T--)
	{
		scanf ("%d",&n);
		for (int i = 1;i <= n;i++) scanf ("%d",&u[i].a);
		for (int i = 1;i <= n;i++) scanf ("%d",&u[i].b);
		sort(u + 1, u + 1 + n, cmp);
		for (int i = 1;i <= n;i++) printf ("%d ",u[i].a);
		printf ("\n");
		for (int i = 1;i <= n;i++) printf ("%d ",u[i].b);
		printf ("\n");
	}
	
	return 0;
}
```


---

## 作者：梦应归于何处 (赞：0)

### 思路

我们考虑 $a_i$、$a_j$、$b_i$、$b_j$。

这里面可能有 $0,1,2$，三种逆序对的情况。

若有 $0$ 个逆序对则交换后会有 $2$ 个逆序对，若有 $1$ 个逆序对则交换后会有 $1$ 个逆序对，若有 $2$ 个逆序对则交换后会有 $0$ 个逆序对。

因此我们发现如果按照 $a$ 数组从小到大排序后 $a_i$、$a_j$、$b_i$、$b_j$ 中最多有 $1$ 个逆序对，交换后不会更优，所以我们就可以按照 $a$ 数组从小到大排序。
 
### 代码

~~~cpp
#include <bits/stdc++.h>
#define ll long long
#define ex exit(0)
#define _endl_ puts("");
#define inl inline
#define null NULL
#define pll pair<ll,ll>
#define mkp make_pair
using namespace std;
struct node {
	ll l, r;
} a[200005];
bool cmp(node x, node y) {
	return x.l < y.l;
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll t;
	cin >> t;
	while (t--) {
		ll n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i].l;
		}
		for (int j = 1; j <= n; j++) {
			cin >> a[j].r;
		}
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1; i <= n; i++) {
			cout << a[i].l << " ";
		}
		cout << endl;
		for (int i = 1; i <= n; i++) {
			cout << a[i].r << " ";
		}
		cout << endl;
	}
	return 0;
}
~~~

---

## 作者：w9095 (赞：0)

[CF1918B Minimize Inversions](https://www.luogu.com.cn/problem/CF1918B)

诈骗题，点破一文不值。

交换元素 $i,j$ 时可能有以下四种情况：

情况一：$a_i\lt a_j,b_i\lt b_j$，此时总逆序对数加 $1$。

情况二：$a_i\gt a_j,b_i\lt b_j$，此时总逆序对数不变。

情况三：$a_i\lt a_j,b_i\gt b_j$，此时总逆序对数不变。

情况四：$a_i\gt a_j,b_i\gt b_j$，此时总逆序对数减 $1$。

分析上面四种情况，发现只要 $a_i\lt a_j$ 时交换就是不劣的，那么我们只用把每个元素按照 $a$ 从小到大来排序即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct val
{
	long long a,b;
}a[300000];
long long t,n;
bool cmp(struct val a,struct val b)
{
	return a.a<b.a;
}
 
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld",&n);
	   	for(int i=1;i<=n;i++)scanf("%lld",&a[i].a);
	   	for(int i=1;i<=n;i++)scanf("%lld",&a[i].b);
	   	sort(a+1,a+n+1,cmp);
	   	for(int i=1;i<=n;i++)printf("%lld ",a[i].a);
	   	printf("\n");
	   	for(int i=1;i<=n;i++)printf("%lld ",a[i].b);
	   	printf("\n");
	   }
	return 0;
} 
```

---

## 作者：qingyun111 (赞：0)

[洛谷CF1918B Minimize Inversions](https://www.luogu.com.cn/problem/CF1918B)

[CF1918B Minimize Inversions](https://codeforces.com/contest/1918/problem/B)

## 读懂题目意思：

给了两个数组，分别都是从 $1$ 到 $n$ 的数字，只不过排序是混乱的。现在，你可以任选 $i$ 和 $j$ 两个位置进行交换。而这里的交换，是两个数组同时交换，而不是单一个数组进行交换。

## 我们需要做什么？

我们需要减少两个数组中逆序对的个数（就是同数组中，前边的数字大于后边数字的个数）。

关于这题，因为只有从 $1$ 到 $n$ 的数字，逆序对可以直接认为 $a_{i} \neq i$，那我们要减少，不就是要让不在位置上的数字尽量回到原本的位置吗？

### 我们该如何减少呢？

换个方向想：怎样才可以减少？

因为进行交换的时候，都是两个数组同时进行交换。当 $a_{i}$ 与 $a_{j}$ 形成逆序对的时候，而 $b_{i}$ 与 $b_{j}$ 并没有形成逆序对，那么这两个位置不论怎么换，都始终会有一边形成逆序对，这种情况是无解的。

**那我们只需要找两个数组同位置，也同时形成了逆序对的地方，将它们进行交换。**

再简洁一些的解法，那就是让其中一个数组变成有序的，另外一个数组跟着它进行更改。

## 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;
namespace fastio{
    struct reader{
        template<typename T>reader&operator>>(T&x){
            char c=getchar();short f=1;
            while(c<'0'||c>'9'){if(c=='-')f*=-1;c=getchar();}
            x=0;while(c>='0'&&c<='9'){
                x=(x<<1)+(x<<3)+(c^48);
                c=getchar();
            }x*=f;return *this;
        }
    }cin;
    struct writer{
        template<typename T>writer&operator<<(T x){
            if(x==0)return putchar('0'),*this;
            if(x<0)putchar('-'),x=-x;
            static int sta[45];int top=0;
            while(x)sta[++top]=x%10,x/=10;
            while(top)putchar(sta[top]+'0'),--top;
            return*this;
        }
    }cout;
};
#define vll vector<ll>
#define pll pair<ll,ll>
#define pii pair<int,int>
#define vpll vector<pll>
#define endl '\n'
#define yes cout<<"Yes"<<endl;
#define no cout<<"No"<<endl;
#define N 3000010
ll num[N];
ll v1[N];
void solve() {
    ll  n,k,ans,m,a,b,c,d,e,q,boll,tem,val,x,y,z,sum,sum1,sum2,maxx,minn,temp1,temp2;
    ans=sum=tem=val=sum1=sum2=temp1=temp2=0,maxx=-1e18,minn=1e18;
    a=b=c=d=0;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>v1[i];
    }
    vpll v(n);
    for(int i=0;i<n;i++){
        cin>>x;
        v[i]={v1[i],x};
    }
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++){
        cout<<v[i].first<<" ";
    }
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<v[i].second<<" ";
    }

    return;
}
int main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int t=1;
    cin>>t;
    while(t--) {
        solve();
    }
    
    return 0;
}
```



---

## 作者：FinderHT (赞：0)

### 题意简述

给你两个排列 $a,b$，你要进行若干次操作，每次操作要求找两个下标 $i,j$ 并同时交换 $a_i,a_j$ 和 $b_i,b_j$，要求进行完所有操作后使两个排列中逆序对的总数最小，输出操作完的序列（答案不唯一）。

### 思路

乍一看像是归并排序之类的算法，但实际上就是个简单的结论：即将 $a,b$ 两数组中任意一个数组排序，另一个数组按照被排序数组的顺序修改即可。

证明：不难发现对于任意两对元素 $a_i,a_j$ 和 $b_i,b_j$，每一对中逆序对数量都为 $0$ 或 $1$，那么在这两对元素中逆序对的总数只可能是 $0,1,2$ 中的任意一个。我们将任意一个排列排序后，这个排列中就不存在逆序对；那么对于任意满足条件的 $i,j$，$a_i,a_j$ 和 $b_i,b_j$ 中逆序对的总数最多是 $1$，从而保证两个排列逆序对的总数最小。

### 代码

```cpp
#include<bits/stdc++.h>
#define gt getchar
#define pt putchar
#define int long long
#define ull unsigned long long
#define fst first
#define snd second
#define mkp(x,y) make_pair(x,y)
#define L(x) x<<1
#define R(x) x<<1|1
using namespace std;
typedef pair<int,int> pii;
const double eps=1e-6;
inline bool pts(char ch){return ch>=48&&ch<=57;}
inline int read(){
	bool f=0;int x=0;char ch;
	ch=gt();
	while(!pts(ch)&&ch!=EOF){if(ch=='-')f=1;ch=gt();}
	while(pts(ch)){x*=10;x+=(ch-48);ch=gt();}
	if(f)return -x;
	else return x;
}
template<class T>
inline void print(T x){
	char s[114];
	int top=0;
	if(x<0)pt('-');
	do{
		top++;
		if(x>=0)s[top]=(x%10)+48;
		else s[top]=(-(x%10)+48);
		x/=10;
	}while(x);
	while(top){pt(s[top]);top--;}
}
const int MAXN=2e5+10;
struct node{
    int val,pos;//val为输入的数值，pos为val在输入数组中的位置
}a[MAXN];
int b[MAXN],bb[MAXN];//bb的作用是记录b数组的初始状态，方便修改
bool cmp(node a,node b){
    return a.val<b.val;
}
void solve(){
    int n=read();
    for(int i=1;i<=n;i++){
        a[i].val=read();
        a[i].pos=i;
    }
    sort(a+1,a+n+1,cmp);//a数组从小到大排序
    for(int i=1;i<=n;i++){
        b[i]=read();
        bb[i]=b[i];
    }
    for(int i=1;i<=n;i++)
        b[i]=bb[a[i].pos];//给b数组进行操作
    for(int i=1;i<=n;i++)cout<<a[i].val<<' ';
    cout<<'\n';
    for(int i=1;i<=n;i++)cout<<b[i]<<' ';
    cout<<'\n';
}
signed main(){
    int T=read();
    while(T--)solve();
    return 0;
}
```



---

## 作者：TheShuMo (赞：0)

## 题意

给定两个长度为 $n$ 的序列 $a$ 和 $b$，你可以进行如下操作任意次，选择一组 $(i,j)$ 交换 $a_i$ 与 $a_j$，和 $b_i$ 与 $b_j$。最小化两个序列的逆序对数量之和。

## 分析

先给结论：将任意一个序列变成升序排列，这样的结果一定最优。

给一个不算太严谨的证明：

对于 $(i,i+1)$ 若 $a_i > a_{i+1}$，那么交换 $(i,i+1)$ 一定不劣。这时，如果有 $b_i > b_{i+1}$ 那么逆序对总数减少 $2$。否则不变。

那么扩展开来，使得对于任意 $i$ 有 $a_i < a_{i+1}$ 即 $a$ 序列升序，那么从原序列到该序列逆序对数量一定不升。下证该没有比该方法更优的方法。

此时，如果交换 $(i,j)$，那么 $a$ 序列的逆序对会多 $2j-2i+1$ 个，原因是 $i + 1$ 到 $j-1$ 的都比 $a_i$ 大，$i+1 $ 到 $j - 1$ 都比 $a_j$ 小，加上 $a_i$ 一个，总共即 $2j-2i+1$ 个。此时 $[i+1,j-1]$ 内的数全都与 $a_i,a_j$ 产生了逆序对。

$b$ 序列的逆序对至多多 $2j - 2i + 1$ 个，当且仅当 $b$ 序列在 $[i,j]$ 降序。若 $b$ 序列在 $[i,j]$ 不降序，在 $j$ 后面的数的数与在 $i$ 前面的数形成逆序对数都不会改变。存在 $k \in [i,j]$ 使得 $a_k < a_i$ 或 $a_k > a_j$。交换后会减少逆序对数量，因此此时交换逆序对总数一定会升高。

所以只要结构体排序一遍输出就好了。

[code](https://www.luogu.com.cn/paste/ffxr7nxb)

---

## 作者：CheZiHe929 (赞：0)

# CF1918B 题解

## 题目链接

[Codeforces](https://codeforces.com/contest/1918/problem/B)

## 简要题意

有两个从 $1$ 到 $n$ 的排列 $a,b$，你可以选择任意的两个索引 $i,j$，同时交换 $a_i$ 和 $a_j$ 及 $b_i$ 和 $b_j$，要求最小化逆序对数量总和。

多测。

## 简要思路

有两种做法都可以过掉此题。

### 按照 $a$ 数组从小到大进行排序（当然 $b$ 数组也可以）

考虑两对元素 $a_i$ 与 $a_j$ 和 $b_i$ 与 $b_j$（$i < j$），其中每一对元素都存在着 $0$ 或 $1$ 个逆序对，因此在两对元素中，可能存在 $0$ 或 $1$ 或 $2$ 个逆序对。

当有 $0$ 个逆序对时，交换后则会出现 $2$ 个逆序对；当有 $1$ 个逆序对时，交换后仍为 $1$ 个逆序对；当有 $2$ 个逆序对时，交换后为 $0$ 个逆序对。

考虑对 $a$ 数组进行从小到大的排序，那么对于每一组元素 $a_i$ 与 $a_j$ 和 $b_i$ 与 $b_j$（$i < j$），只会存在 $0$ 或 $1$ 组逆序对，交换后则会出现 $1$ 或 $2$ 组逆序对，不会更优。

因此我们在对 $a$ 数组进行排序后，任何一对索引的逆序对数量都不会多于交换后的逆序对数量。因为每对索引中的逆序对数量是可能的最小值，因此总共的逆序对的数量也一定是最小值。

代码如下。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=2e5+5;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

std::pair<int,int> a[MAXN];

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

    int T=read();
    while(T--){
		int n=read();
		for(int i=1;i<=n;i++)a[i].first=read();
		for(int i=1;i<=n;i++)a[i].second=read();
		
		std::sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)put(a[i].first,i,n);
		for(int i=1;i<=n;i++)put(a[i].second,i,n);
	}

	return 0;
}
```

### 按照 $a,b$ 数组的和排序

其实和上面一种算法本质上是差不多的。

考虑按照总和排序后的两对元素 $a_i$ 与 $a_j$ 和 $b_i$ 与 $b_j$（$i < j$），因为 $i < j$，所以 $a_i + b_i \le a_j + b_j$，因此我们进行分类讨论：

- 当 $a_i \le a_j,b_i \le b_j$ 时

	逆序对数量为 $0$，交换后数量会变成 $2$，因此当前即为最优状态。
    
- 当 $a_i \le a_j,b_i > b_j$ 时

	$a$ 数组中这对元素存在 $0$ 个逆序对，$b$ 数组中这对元素存在 $1$ 个逆序对，因此总共有 $1$ 个逆序对，同第一种做法，交换后仍为 $1$ 个逆序对，不会更优。
    
- 当 $a_i > a_j,b_i \le b_j$ 时

	同上。

（因为 $a_i + b_i \le a_j + b_j$，所以不存在 $a_i > a_j,b_i > b_j$ 的情况，因为我们是按照总和从小到大来进行排序的。）

代码如下。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=2e5+5;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

struct node{
	int a,b;
	int sum;
}m[MAXN];

bool cmp(node x,node y){return x.sum<y.sum;}//按照总和进行排序

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	int T=read();
	while(T--){
		int n=read();
		for(int i=1;i<=n;i++)m[i].a=read();
		for(int i=1;i<=n;i++){
			m[i].b=read();
			m[i].sum=m[i].a+m[i].b;
		}
		
		std::sort(m+1,m+n+1,cmp);
		for(int i=1;i<=n;i++)put(m[i].a,i,n);
		for(int i=1;i<=n;i++)put(m[i].b,i,n);
	}

	return 0;
}
```

**THE END.**

**THANK YOU.**

---

## 作者：Zhuluoan (赞：0)

## 题意简述

给定两个长度均为 $n$ 的序列 $a$ 和 $b$。你可以进行任意次如下操作：

- 选择两个正整数 $i,j \in [1,n]$，交换 $a_i$ 和 $a_j$，再交换 $b_i$ 和 $b_j$。

请最小化两个序列中逆序对的个数的和。请输出经过操作后的序列。

## 题目分析

将 $a$ 数组排序，就可以最小化两个序列中逆序对的个数的和了，证明如下：

> 当 $a$ 排序了之后，对于任意一对 $i$ 和 $j$，两数组中逆序对之和数量 $x$ 最大为 $1$，当 $x=0$ 时，交换后 $x$ 为 $2$，当 $x=1$ 时，交换后 $x$ 为 $1$，所以再怎么交换都不可能更优了，故现在的序列即为最优解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10; 
int t,n;
pair<int,int> a[N];
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].first;
	for(int i=1;i<=n;i++) cin>>a[i].second;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++) cout<<a[i].first<<" ";
	cout<<"\n";
	for(int i=1;i<=n;i++) cout<<a[i].second<<" ";
	cout<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>t;
    while(t--)
    {
    	solve();
	}
	return 0;
}
```

---

## 作者：MA_tian (赞：0)

# 题目大意
给你两个数组 $ a $ 和 $ b $，可以在数组内交换 $ a_i $，$ a_j $ 和 $ b_i $，$ b_j $，必须同时交换，求两个数组中逆序对总和最少，有 $ T $ 组数据。
# 做法
逆序对的定义：$ i<j $ 并且 $ a_i>a_j $。

观察可知，当升序最多时逆序对最少。所以当 $ a_i<a_j $ 时交换一定不会添加逆序对。

加入 $ b $ 数组再看会发现，每消掉一个 $ a $ 中的逆序对最多在 $ b $ 中添加一个逆序对，所以将 $ a $ 升序排序怎么看都不会使答案变大。

若此时再排b数组，则会增加 $ a $ 数组的逆序对，所以不用再进行操作了。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int l1,l2;
}a[200005];
bool cmp(node u1,node u2){
    return u1.l1<u2.l1;
}
int main(){
	int T,n;
   	cin>>T;
   	while(T--){
    	cin>>n;
        for(int i=0;i<n;i++){
            cin>>a[i].l1;
        }
        for(int i=0;i<n;i++){
            cin>>a[i].l2;
        }
        sort(a,a+n,cmp);
        for(int i=0;i<n;i++){
            cout<<a[i].l1<<" ";
        }
        cout<<endl;
        for(int i=0;i<n;i++){
            cout<<a[i].l2<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```

---

