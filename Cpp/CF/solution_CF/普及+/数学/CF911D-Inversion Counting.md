# Inversion Counting

## 题目描述

A permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array. An inversion in a permutation $ p $ is a pair of indices $ (i,j) $ such that $ i>j $ and $ a_{i}<a_{j} $ . For example, a permutation $ [4,1,3,2] $ contains $ 4 $ inversions: $ (2,1) $ , $ (3,1) $ , $ (4,1) $ , $ (4,3) $ .

You are given a permutation $ a $ of size $ n $ and $ m $ queries to it. Each query is represented by two indices $ l $ and $ r $ denoting that you have to reverse the segment $ [l,r] $ of the permutation. For example, if $ a=[1,2,3,4] $ and a query $ l=2 $ , $ r=4 $ is applied, then the resulting permutation is $ [1,4,3,2] $ .

After each query you have to determine whether the number of inversions is odd or even.

## 说明/提示

The first example:

1. after the first query $ a=[2,1,3] $ , inversion: $ (2,1) $ ;
2. after the second query $ a=[2,3,1] $ , inversions: $ (3,1) $ , $ (3,2) $ .

The second example:

1. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
2. $ a=[3,4,2,1] $ , inversions: $ (3,1) $ , $ (4,1) $ , $ (3,2) $ , $ (4,2) $ , $ (4,3) $ ;
3. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
4. $ a=[1,4,2,3] $ , inversions: $ (3,2) $ , $ (4,2) $ .

## 样例 #1

### 输入

```
3
1 2 3
2
1 2
2 3
```

### 输出

```
odd
even
```

## 样例 #2

### 输入

```
4
1 2 4 3
4
1 1
1 4
1 4
2 3
```

### 输出

```
odd
odd
odd
even
```

# 题解

## 作者：Muruski (赞：13)

这道题其实还是挺偏思维题的，我看网上有很多很多的大佬写了超级超级长的并且有点冗杂代码 ~~我是不会告诉你我看不懂的~~ 。

所以我在这放上我自己的代码以及一些思路

首先我们会发现这道题的数据范围是很大的，直接暴力会轻轻松松的T掉~~我T了两发~~再一看这个题目的难度分类，貌似不用打那些平衡树等等高深的算法~~反正我也不会~~，再一想答案只需要输出奇偶性，于是想出了答案。

题意是将一段区间翻转，我们会非常轻易地发现 **原先是正序的翻转后变成了逆序的，并且翻转的部分只对该区间起作用** ，所以翻转后逆序对数量的奇偶性也就是翻转前正序对的数量的奇偶性，但他们两者的奇偶性是不好求的 ~~其实也可以直接判断他们两者的奇偶性，但我不是这么做的~~ ，所以我尝试了另一种方法

我们先设该给定区间的长度为**lenth**，则该区间内所有数对数量为

**lenth(lenth-1)/2** 这里需要注意一下是所有数对数量而不是什么逆序对数量

我们再设翻转后的逆序对数量为**part** 所以翻转前的正序对数量也为part，这个前面提到过了，不懂的往前找，所以翻转前的逆序对数量就为

**lenth(lenth-1)/2-part**

然后现在是最重要的一步：**翻转前的逆序对数量减去翻转前后逆序对数量差就是翻转后逆序对的数量，所以如果要判断翻转后逆序对数量的奇偶性只需要判断反转前后逆序对数量差的奇偶性即可**

这一部感觉还是挺难理解的，各位有不懂的可以私信我

这个数量差可以表示为：

**lenth(lenth-1)/2-part-part**

也就是：

**lenth(lenth-1)/2-part*2**

其中**part*2**一定是偶数，所以我们判断**lenth(lenth-1)/2**就可以了，而这个太简单不过了

直接上代码，代码里也会有一些解释：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
int n,m;
int lenth,part;
int l,r;
int f;
int a[1550];
int main()
{
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
		scanf("%d",&m);
		lenth=0;
		for(int i=1;i<n;i++)
			for(int j=i+1;j<=n;j++)
				if(a[i]>a[j]) lenth++;//暴力求这个区间的逆序对数量，本人不会更高级的算法了，不过这个也可以过
		if(lenth%2==0) f=1;
		else f=0;//这两行是求原来区间所有数对的数量也就是lenth的奇偶性
		while(m--)
		{
			scanf("%d%d",&l,&r);
			part=r-l+1;
			if((part*(part-1)/2)%2==1)
			    f=!f;
			if(f)
			   printf("even\n");
			else
			    printf("odd\n");//输出答案
		}
	}
	return 0;
}

```
撒个花结束，请管理员大大让我通过，第一篇题解，写得可认真了。

各位大佬要是有不懂得可以私信问我呀

---

## 作者：Arghariza (赞：6)

除去逆序对询问，这个题面很容易让人想到 Splay 翻转区间操作。

~~但 Codeforces 蓝题哪个有用到平衡树的？~~

我们发现逆序对有一个有趣的性质：

- 当前区间所有数对的个数如果是偶数，整个序列逆序对个数就肯定不变；如果是奇数，整个逆序对个数肯定改变。

证明很简单，分类讨论即可。

1. 若当前数对个数为偶数：
- 若正序对个数为**奇数**，逆序对个数就是**奇数**，**翻转后也是奇数**。
- 若正序对个数为**偶数**，逆序对个数就是**偶数**，**翻转后也是偶数**。

2. 若当前数对个数为奇数：
- 若正序对个数为**奇数**，逆序对个数就是**偶数**，**翻转后就是奇数**。
- 若正序对个数为**偶数**，逆序对个数就是**奇数**，**翻转后就是偶数**。

所以判断一下数对个数奇偶性，如果偶数就不变，否则取反。

对于一开始的逆序对个数，归并排序、树状数组什么的套上去就行。

$\color{grey}\mathtt{main\ code:}$

```cpp
int mergesort(int l, int r, int s[], int q[]) {// 归并排序求逆序对
	int res = 0;
	if (l == r) return 0;
	int mid = (l + r) >> 1;
	res += mergesort(l, mid, s, q);
	res += mergesort(mid + 1, r, s, q);
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (s[i] <= s[j]) q[k++] = s[i++];
		else {
			q[k++] = s[j++];
			res += mid - i + 1;
		}
	}
	while (i <= mid) q[k] = s[i], k++, i++;
	while (j <= r) q[k] = s[j], k++, j++;
	for (int i = l; i <= r; i++) s[i] = q[i];
	return res;
}

int main() {
	n = read();
	for (int i = 1; i <= n; i++) s[i] = read();
	cnt = mergesort(1, n, s, q);
	flag = !(cnt % 2);// 初始逆序对奇偶性
	m = read();
	for (int i = 1; i <= m; i++) {
		int l = read(), r = read();
		int t = (r - l + 1) * (r - l) / 2;// 数对个数
		if (t % 2 == 1) flag = !flag;
		if (flag == 0) puts("odd");
		else puts("even");
	}
	return 0;
}
```

---

## 作者：Citnaris (赞：1)

# CF911D Inversion Counting

**题意**

给定一个序列 $a_1......a_n$ ，每个操作将 $a_l......a_r$ 反转，求此时逆序对个数。

**正解**

我们知道，求出一个系列中逆序对的个数的复杂度最好情况下是 $\mathcal{O}(n\log n)$ 的，若每次均反转后计算，那么时间复杂度将是 $\mathcal{O}(mn\log n)$ 的，显然不可过。所以此题正解每次判断将是 $\mathcal{O}(1)$ 的。

我们发现，对于 $i, j\in[l,r], i<j$ ，每个 $a_i, a_j$

* 若再反转前为逆序对，即 $a_i>a_j$ ，那么反转后 $a_i'(a_j)<a_j'(a_i)$ ，即不是逆序对。

* 若再反转前为不是逆序对，即 $a_i<a_j$ ，那么反转后 $a_i'(a_j)>a_j'(a_i)$ ，即是逆序对。

综上所述，每次反转会将原来的逆序对变为非逆序对，原来的非逆序对变成逆序对。

设 $[1,n]$ 中初始有 $s$ 个逆序对。显然，每次反转区间 $[l,r]$ 中选两个数 $a_i, a_j$ 组对（不同顺序算一种）共有 $\frac{(l-r+1)\times (l-r)}{2}$ 种，设该区间中逆序对个数为 $x$ ，则反转后个数变为了 $s-x+(\frac{(l-r+1)\times (l-r)}{2}-x)=s+\frac{(l-r+1)\times (l-r)}{2}-2x$ ，模 $2$ 同余于 $s+\frac{(l-r+1)\times (l-r)}{2}$ ，只需判断这个数的奇偶即可。

预处理 $s$ 可在 $\mathcal{O}(n^2)\ or\ \mathcal{O}(n\log n)$ 中完成，查询可在 $\mathcal{O}(1)\times m=\mathcal{O}(m)$ 中完成，总复杂度 $\mathcal{O}(n\log n+m)\ or\ \mathcal{O}(n^{2}+m)$ 。

**代码 $\mathcal{O}(n^{2}+m)$ 版本**

```cpp
#include <bits/stdc++.h>

using namespace std;

const int NR = 1500 + 5;
int cnt, a[NR], n, m, l, r;

inline void Init()
{
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (a[j] < a[i])
                cnt += 1;
    return;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    Init();
    scanf("%d\n", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &l, &r);
        cnt += (r - l + 1) * (r - l) / 2;
        cnt %= 2;
        cnt == 0 ? printf("even\n") : printf("odd\n");
    }
    return 0;
}
```

---

## 作者：⚡current⚡ (赞：1)

蒟蒻的第一篇题解，对大佬来说可能有点啰嗦

首先我们要仔细看题，要求的是[L, R]翻转后整个序列中逆序对的奇偶性，不是[L, R]中逆序对的奇偶性，也不是逆序对的总数

接着我们就可以思考[L, R]中的逆序对与整个序列逆序对的关系，我们会惊奇地发现，由于[L, R]中的数翻转之后与[L, R]区间之外的数的相对位置并不会发生改变，所以除了$a$, $b$两个数都属于[L, R]的数对$(a, b)$，其他的数对都不会发生变化，所以只要知道区间[L, R]中逆序对奇偶性的变化，就可以知道整个序列中奇偶性的变化

那如何求出这个变化呢? 思考一下逆序对的定义: 

> 对于给定的一段正整数序列，逆序对就是序列中$a_i>a_j$且$i<j$的有序对 ——[P1908 逆序对](https://www.luogu.org/problem/P1908)

接下来是本道题的主要难点:

对于任意数对$(a_i, a_j)\, (i<j)$，只存在以下三种情况:

$a_i>a_j$(逆序对)，$a_i =b_j$(相等的数对)，$a_i<a_j$(顺序对?)(洛谷的$LaTeX$怎么打大括号啊QWQ)

显然我们可以得到以下等式: 逆序对数量 + 相等的数对的数量 + 顺序对数量 = 数对总数

其中逆序对在区间翻转后会变成顺序对，顺序对会变成逆序对，而相等的数对还是相等的数对

设$m =  $ 逆序对数 + 翻转之后的逆序对数 = 数对总数 - 相等的数对数量，那么如果$m\&1 == 1$，奇偶性改变；如果$m\&1 == 0$，奇偶性不变

数对总数用很容易就可以算出$ = \frac {n(n-1)}{2} \;\; (n = R - L + 1)$，那么相等的数对个数怎么求呢？

答案是不用求~~，这是我经过对人生和社会的大思考后得出的结论~~，其实这是翻译的锅，仔细看一眼英文题面，说的是：

> A permutation of size $n$ is an array of size $n$ such that each integer from $1$ to $n$ occurs exactly once in this array

对，permutation就是`next_permutation();`里的那个permutation，排列的意思，也就是说$1$~$n$都各出现一次，互不重复，那么只要求出初始逆序对个数，然后对于每一个询问，我们$O(1)$地求出[L, R]内数对总数的奇偶性就可以了

代码$\downarrow$

```c++
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int m, x, y, num;

int read() {
	int x = 0; char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x;
}

#define lowbit(x) x&-x

int n, a[600000], b[600000], c[600000];

void add(int x) {
	for(int i = x; i <= n; i += lowbit(i)) ++c[i];
} 

long long sum(int x) {
	long long ans = 0;
	for(int i = x; i; i -= lowbit(i)) ans += c[i];
	return ans;
}

int main(void) {
	long long ans = 0;
	cin >> n;
	for(int i = 1; i <= n; ++i) a[i] = b[i] = read();
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; ++i) a[i] = n - (lower_bound(b + 1, b + n + 1, a[i]) - b) + 1; 
	for(int i = 1; i <= n; ++i) {
		ans += sum(a[i] - 1);
		add(a[i]);
	}
    //上面是树状数组求逆序对个数，这题归并甚至暴力求逆序对因该也是可以的
	ans &= 1;
    m = read();
    while(m--)
    {
        x = read();
        y = read();
        num = y-x+1;
        num = num*(num-1)/2;//求数对总数
        if((num)&1) ans = (ans+1)&1;//判断奇偶性是否改变
        if(ans) puts("odd");
        else puts("even");
    }
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

首先，在询问之前，我们要求出整个序列的逆序对数。

为了保证时间复杂度不过高，我们可以使用归并排序来求逆序对。

这是归并排序的代码：

```
void work(int l,int mid,int r){
	int i=l;
	int j=mid+1;
	int k=l;
	while(i<=mid&&j<=r){
		if(a[i]<=a[j])b[k++]=a[i++];
		else{
			b[k++]=a[j++];
			cnt+=mid-i+1;
		}
	}
	while(i<=mid)b[k++]=a[i++];
	while(j<=r)b[k++]=a[j++];
	for(i=l;i<=r;++i)a[i]=b[i];
}
void ask(int l,int r){
	if(l>=r)return;
	int mid=(l+r)>>1;
	ask(l,mid);
	ask(mid+1,r);
	work(l,mid,r);
}
```

其中调用 `ask(1,n)` 后，`cnt` 表示整个数列的逆序对数。

然后，我们可以发现，无论怎么翻转，都有一个性质：

对于任何一个原来的逆序对，如果它的两个数有一个不在翻转范围内，则这个逆序对依然存在，只是改了一点位置。

比如说，有个数列是 $4,3,2,1$，翻转从 $4$ 到 $2$ 的范围，那么 $4$ 和 $1$ 组成的逆序对不会改变。

但是，在翻转范围内，翻转后逆序对的数量等于原来正序对的数量。为什么呢？

很明显，对于一个有 $m$ 个数的子串，里面一共有 $\dfrac{m\times(m-1)}{2}$ 个数对。因为这些数两两不同，所以，设有 $k$ 个逆序对，则有 $\dfrac{m\times(m-1)}{2}-k$ 个正序对。

翻转过后，正序对和逆序对对调，就有了上面的性质。

也就是说，我们首先求出数列没有翻转之前的逆序对数量的奇偶性。如果翻转时，翻转范围内的数对数量（就是 $\dfrac{(r-l+1)\times(r-l)}{2}$）是奇数的，那么奇偶性总逆序对数量的奇偶性就会被改变，无论翻转范围内有多少逆序对；否则不会改变。

设数列长度为 $n$，操作次数为 $q$，则我们的程序的时间复杂度为 $O(n\operatorname{log}n+q)$，顶多 $20$ 万左右。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
#define max_n 1500
int n;
int a[max_n+2];
int b[max_n+2];
int cnt=0;
int q;
bool ans;
void work(int l,int mid,int r){
	int i=l;
	int j=mid+1;
	int k=l;
	while(i<=mid&&j<=r){
		if(a[i]<=a[j])b[k++]=a[i++];
		else{
			b[k++]=a[j++];
			cnt+=mid-i+1;
		}
	}
	while(i<=mid)b[k++]=a[i++];
	while(j<=r)b[k++]=a[j++];
	for(i=l;i<=r;++i)a[i]=b[i];
}
void ask(int l,int r){
	if(l>=r)return;
	int mid=(l+r)>>1;
	ask(l,mid);
	ask(mid+1,r);
	work(l,mid,r);
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF0911D_1.in","r",stdin);
	freopen("CF0911D_1.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
	}
	ask(1,n);
	if(cnt&1)ans=false;
	else ans=true;
	scanf("%d",&q);
	for(int i=1,l,r,x;i<=q;++i){
		scanf("%d%d",&l,&r);
		x=r-l+1;
		if((x*(x-1)/2)&1)ans^=1;
		if(!ans)puts("odd");
		else puts("even");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/61991686)

By **dengziyue**

---

## 作者：zythonc (赞：0)

## 【题意】
给定一个序列

每次操作翻转一个区间 $[l,r]$

求**每次**翻转后**整个序列**逆序对的奇偶性

## 【思路分析】

首先看到翻转区间我们可以想到Splay可以胜任

看到逆序对可以想到归并排序

但是根据 ~~（CF的题目都是思维题）~~ **时间复杂度**可以很轻易地判断出这显然是不行的

**考虑这道题目让我们求什么**

显然，我们并不需要求出逆序对的数目，而只需要求它的**奇偶性**

对于一个要被翻转的区间 $[l,r]$

显然长度 $len=r-l+1$

其**全部数对**的数目是：$num=\frac{len(len-1)}{2}$

**对于这个区间：**

- **其全部的正序对在翻转后会变成逆序对**

- **其全部的逆序对在翻转后会变成正序对**

### 重点来了

如果 $num$ 是一个偶数，分类讨论其逆序对的奇偶性的两种情况

- **奇数**，那么其正序对的数目也是**奇数**，翻转后奇偶性**不变**

- 偶数，显然翻转后奇偶性不变

如果 $num$ 是一个奇数，其逆序对的奇偶性也有两种情况

- **奇数**，那么其正序对的数目是**偶数**，翻转后奇偶性**改变**

- **偶数**，那么其正序对的数目是**奇数**，翻转后奇偶性**改变**

## 【总结】
**如果 $num$ 是偶数，那么不管怎样奇偶性都不变，如果是奇数，那么不管怎么样奇偶性都会改变**

## 【代码实现】

```
#include<iostream>
#include<algorithm>
using namespace std;
int a[500001],r[500001],len,ans,e,L,R,t,num;
void msort(int s,int e){
	if(s==e) return;
	long long int mid=(s+e)/2;
	msort(s,mid);msort(mid+1,e);
	int i=s,j=mid+1,k=s;
	while(i<=mid&&j<=e){
		if(a[i]<=a[j]){
			r[k]=a[i];
			k+=1;i+=1;
		}
		else{
			r[k]=a[j];
			k+=1;j+=1;
			ans+=mid-i+1;
		}
	}
	while(i<=mid){
		r[k]=a[i];
		k+=1;i+=1;
	}
	while(j<=e){
		r[k]=a[j];
		k+=1;j+=1;
	}
	for(int i=s;i<=e;i++)
		a[i]=r[i];
}
int main(){
	cin>>num;
	for(int i=1;i<=num;i++){
		cin>>a[i];
	}
	msort(1,num);
	if(ans%2==0) e=1;
	cin>>t;
	while(t--){
		cin>>L>>R;
		len=R-L+1;
		if(len*(len-1)/2%2){
			e=!e;
		}
		cout<<(e?"even\n":"odd\n");
	}
}
```

~~**为什么我的归并排序时间复杂度假了QAQ**~~

---

## 作者：Nero_Claudius (赞：0)

这是一道看似复杂其实也不简单的思维题。

------------

其实思路很明显。

因为这道题的数据范围比较大，有1e5的询问，如果暴力（像我考场上那样打平衡树）的话可以做到mnlogn。

但那样也是稳T。

经过思考之后我们可以发现，这道题必定要使用m的解法，也就是对于每一个询问O1求解。（总不可能mlogn求解）

那么怎么O1呢？

------------

众所周知，O1算法自古以来就和数学脱不开关系。

而本题中有哪些量可以扯上来搞一搞呢？

具体的值？肯定不现实。

那也就只剩下区间长度了。

------------

针对区间长度进行考察之后，我们可以发现这样的一件事：

如果区间中数对个数为偶数，那么翻转之后答案不变。

否则变化。

这是为什么呢？

很显然，翻转操作是具有封闭性的。换言之，不会影响到外面的元素。

而根据我们的手动模拟，翻转后逆序对个数=数对数-翻转前逆序对个数。

于是乎正解就出来了。

------------


我们先用树状数组搞一搞原数组的逆序对。

然后对于每一组询问，异或一下判奇偶即可。

------------


AC代码如下：

`797ms 24kb`

```cpp
// By Ilverene

#include<bits/stdc++.h>

using namespace std;

namespace StandardIO{

	template<typename T>inline void read(T &x){
		x=0;T f=1;char c=getchar();
		for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
		x*=f;
	}

	template<typename T>inline void write(T x){
		if(x<0)putchar('-'),x*=-1;
		if(x>=10)write(x/10);
		putchar(x%10+'0');
	}

}

using namespace StandardIO;

namespace Solve{

	// Define your constants here.
	const int N=1515;

	// Define your global variables here.
	int n,m,s=0,a[N],b[N];
	// Define your main functions here.
	template<typename _Tp>inline _Tp query(_Tp x){
	    int res=0;
	    for(int i=x;i;i-=i&-i)res+=b[i];
	    return res;
	}
	void update(int x){
		for(int i=x;i<=n;i+=i&-i)++b[i];
	}
	
	inline void solve(){
		// Write your main logic here.
		read(n);
	    for(int i=1;i<=n;++i)read(a[i]);
	    for(int i=n;i>=1;--i){
	        s=(s+query(a[i]-1))&1;
	        update(a[i]);
	    }
	    read(m);
	    while(m--){
	    	int l,r;
	    	read(l),read(r);
	        if(((r-l+1)*(r-l)/2)&1)s^=1,printf(s?"odd":"even");
	        else printf(s?"odd":"even");
	        putchar('\n');
	    }		
	}
}

using namespace Solve;

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	solve();
}

//
```

---

## 作者：noble_ (赞：0)

思维要求比较高。

首先我们要把原图的逆序对q算出来。

这个树状数组或归并排序都ok（树状数组不用离散化好评）

那么翻转$[l,r]$中的数怎么做呢？

暴力过不了，我试过了。

设$ t=r-l+1 $即为区间长度

那么区间数对数量（看好是所有数对，不是逆序对）的数量就是$  k =\frac{n\times(n-1)}{2}$

方法是我们判断一下数量k的奇偶性，如果是奇数的，那么就把$ q $的奇偶性变一变。

然后判断q的奇偶性输出就行。

为什么这样是对的呢？

首先翻转区间只影响到了两个数都在这个区间里面的逆序对，不干涉其他的数对。 **翻转区间后，逆序对变成了正序对，正序对变成了逆序对。** 

那么如果k是偶数，那么无论区间里面的逆序对的奇偶性如何，翻转后奇偶性都不变。比如k=8,区间里面的逆序对数量p=3，翻转后逆序对数量p=5，不改变奇偶性。p为偶数时也同理。

那么如果k是奇数呢？比如k=9, p=3，翻转后p=6，奇偶性改变了。而p为偶数时也同理。

综上，只要区间数对数量k为奇数，原序列的逆序对数量奇偶性就改变，否则则不改变。

代码挺丑，就不放在这里了，如果想看来[我的博客](https://www.cnblogs.com/noblex/p/9510814.html)看吧。

---

