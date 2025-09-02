# Vladik and Complicated Book

## 题目描述

Vladik had started reading a complicated book about algorithms containing $ n $ pages. To improve understanding of what is written, his friends advised him to read pages in some order given by permutation $ P=[p_{1},p_{2},...,p_{n}] $ , where $ p_{i} $ denotes the number of page that should be read $ i $ -th in turn.

Sometimes Vladik’s mom sorted some subsegment of permutation $ P $ from position $ l $ to position $ r $ inclusive, because she loves the order. For every of such sorting Vladik knows number $ x $ — what index of page in permutation he should read. He is wondered if the page, which he will read after sorting, has changed. In other words, has $ p_{x} $ changed? After every sorting Vladik return permutation to initial state, so you can assume that each sorting is independent from each other.

## 说明/提示

Explanation of first test case:

1. $ [1,2,3,4,5] $ — permutation after sorting, $ 3 $ -rd element hasn’t changed, so answer is "Yes".
2. $ [3,4,5,2,1] $ — permutation after sorting, $ 1 $ -st element has changed, so answer is "No".
3. $ [5,2,3,4,1] $ — permutation after sorting, $ 3 $ -rd element hasn’t changed, so answer is "Yes".
4. $ [5,4,3,2,1] $ — permutation after sorting, $ 4 $ -th element hasn’t changed, so answer is "Yes".
5. $ [5,1,2,3,4] $ — permutation after sorting, $ 3 $ -rd element has changed, so answer is "No".

## 样例 #1

### 输入

```
5 5
5 4 3 2 1
1 5 3
1 3 1
2 4 3
4 4 4
2 5 3
```

### 输出

```
Yes
No
Yes
Yes
No
```

## 样例 #2

### 输入

```
6 5
1 4 3 2 5 6
2 4 3
1 6 2
4 5 4
1 3 3
2 6 3
```

### 输出

```
Yes
No
Yes
No
Yes
```

# 题解

## 作者：_xbn (赞：4)

不明白楼下两位大佬为什么把问题想得这么复杂，这题不是直接暴力就过了吗?

我来说一下暴力方法。

对于每一个询问，我们可以在询问区间中找所有比它小的数，加上区间左端点

的值就是他在整个区间的排名，跟原始排名比较一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std; 
int n,m,x,y,z,v,a[10002];
int main()
{
   cin>>n>>m;
   for(int i=1; i<=n; i++)cin>>a[i];
   for(int i=1; i<=m; i++)
   {
      cin>>x>>y>>z;
      for(int j=x; j<=y; j++)
      {
          if(a[j]<a[z])v++;
      }
      if(x+v==z)cout<<"Yes"<<endl;
      else cout<<"No"<<endl;
      v=0;
   }
   return 0;
}
```




---

## 作者：Gao_l (赞：3)

## 题意

有一个长度为 $n$ 的排列，每次选一段区间 $[l,r]$ 排序，问位置 $x$ 上的数在排序前后是否发生了改变。

## 思路

暴力枚举 从 `l` 到 `r` 枚举，找比 $a_x$ 小的数。判断是否都在 $a_x$ 的前面。

## C++代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[10005];
int l,r,x;
bool check(){
    int cnt=0;
    for(int i=l;i<=r;i++)
        if(a[i]<a[x])
            cnt++;
    if(cnt==x-l)return true;
    else return false;
}
int main(){
    cin >> n >> q;
    for(int i=1;i<=n;i++)
        cin >> a[i];
    while(q--){
        cin >> l >> r >> x;
        if(check()){ //这里用了一个check()函数，好用来判断
            cout << "Yes\n";
        }else{
            cout << "No\n";
        }
    }
    return 0;
}
```

---

## 作者：foryou_ (赞：1)

我们令题目给出的排列为 $p$，目标位置为 $x$，待排序的区间为 $[l,r]$。

则当且仅当 $\sum_{l \le i \le r \ \text{且} \ p_i < p_x} p_i = x - l$ 时，$p_x$ 在 $p_{l \sim r}$ 排序后位置仍然不变（即比 $p_x$ 小的都在它的左边）。

于是我们直接对于每个询问的区间，朴素地求出 $\sum_{l \le i \le r \ \text{且} \ p_i < p_x} p_i$，若其等于 $x-l$ 则输出 `Yes`，否则输出 `No` 即可。

时间复杂度 $O(nm)$，可以通过。

---

## 作者：Spir1t (赞：1)

### [非常简单的一道题](https://www.luogu.com.cn/problem/CF811B)

#### 先放代码：
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0') {
		if (ch == '-')f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int a[114514],n,m;
signed main(){
	int k;
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	int l,r,x;
	while(m--){
		l=read();r=read();x=read();
		int ans=0;
		for(int i=l;i<=r;i++){
			if(a[i]<a[x]) ans++;
		}
		puts(l+ans==x?"Yes":"No");
	}
	return 0;
}
```

思路楼下大佬已经描述过了，我在这里在更详细地说一下。

整篇代码只有一个地方不好理解，就是这里：
```
puts(l+ans==x?"Yes":"No");

```
其中 $ans$ 代表在区间中比数组中第 $x$ 位置上的数小的数的个数，即可以表示为把这个区间排序后排在数组中第 $x$ 位置上的数前面的数，为什么加上左端点的话表示的就是左端点前的数的个数，如果 $ans+l=x$，那么说明排序后 $x$ 位置上的数没变，输出 Yes 即可，否则输出 No，然后就没有然后了。


---

## 作者：InversionShadow (赞：0)

在区间 $[l,r]$ 中比 $a_x$ 小的数从小到大排序后会排到 $a_x$ 的前面，所以我们统计出 $\sum\limits_{i=1 \& i \neq x}^n[a_i \le a_x]$，如果 $l+\sum\limits_{i=1 \& i \neq x}^b[a_i \le a_x]$ 等于 $x$，输出 `Yes`，否则输出 `No`。

```cpp
#include <bits/stdc++.h>

using namespace std; 

const int MAXN = 1e5 + 100;

int n, m, x, y, z, v, a[MAXN];

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  } 
  while (m --> 0) {
    int l, r, x;
    cin >> l >> r >> x;
    int sum = 0;
    for (int i = l; i <= r; i++) {
      sum += (a[i] < a[x]);
    }
    cout << (l + sum == x ? "Yes\n" : "No\n");
  }
   return 0;
}
```

---

## 作者：ylch (赞：0)

# CF811B Vladik and Complicated Book 题解

[-题目传送门-](https://www.luogu.com.cn/problem/CF811B)

### 题目简述

题目让我们选一个区间 $[l,r]$ 进行排序，然后确认位置 $x$ 上的数位置是否改变了。

### 解法分析

这其实就是一道很简单的暴力模拟题，我来说说自己的见解。

从小到大排序，如果有 $k$ 个数比 $x$ 小，$x$ 排序后就应该在 $l+k$ 位置。那么我们只要数出 $x$ 前面有几个比 $x$ 小的数，再判断位置是否相等就行。

看一下我们算法的复杂度大约是 $\text{O}(nm)$ 左右，$n$ 和 $m$ 最大为 $10^4$，不会超时。

### AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[10005];
int n,m;

signed main()
{
	cin >> n >> m;
	for (int i=1; i<=n; i++)	cin >> a[i];
	for (int l,r,x, _=1; _<=m; _++)
	{
		cin >> l >> r >> x;
		int k = 0;
		for (int i=l; i<=r; i++)
			k += (a[i] < a[x]);
		puts(l+k == x? "Yes" : "No");
	}
	return 0;
}
```

End
-----------

管理员大大辛苦啦~

谢谢大家！我们一起进步，一起 $rp++$！

---

## 作者：Steve_xh (赞：0)

# 题面

[题目传送门](https://www.luogu.com.cn/problem/CF811B)

**题目大意：**

给定长度为 $n$ 的序列 $a$，和 $m$ 组询问，每组询问包含下界 $l$ 和上界 $r$，以及一个位置 $x$。问将 $a$ 的 $[l,r]$ 区间升序排序后 $x$ 位置的值是否会改变。

# 思路

纯纯的模拟。不过直接暴力会 $O(nm\log n)$ 而超时，因此需要优化。考虑计算 $a_x$ 在 $[l,r]$ 区间中的排名，再加上 $l$，最后判断是否和在数组中的位置 $x$ 一样即可，复杂度强行降到 $O(nm)$，$(10^4)^2$ 应该还是能过的。

如何计算排名？我们知道升序排序会把所有比当前数小的数都放到这个数前面，因此循环 $[l,r]$ 找所有比 $a_x$ 小的数并统计数量就能知道当前数在区间内的排名。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10005];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1,l,r,x;i<=m;i++){
        cin>>l>>r>>x;
        int t=0;//计数器
        for(int j=l;j<=r;j++)
            if(a[j]<a[x])
                t++;//统计比a[x]小的数
        if(l+t==x)//如果整段排名与在数组中的位置相同
            cout<<"Yes\n";
        else
            cout<<"No\n";
    }
    return 0;
}
```

---

## 作者：Bpds1110 (赞：0)

### Preface:
[原题传送门](https://www.luogu.com.cn/problem/CF811B)

给定长度为 $N$ 的序列 $a$，$M$ 个询问。每次询问 $l$ 到 $r$ 的区间内由小到大排序后，$a_x$ 是否改变。
### Solution:
一道很简单的模拟题，不明白楼下大佬为什么用线段树优化。要询问区间内由小到大排序后，$a_x$ 是否改变，只要枚举 $i$ 从 $l$ 到 $r$。我们设 $cnt$ 为**区间内小于 $a_x$ 的数的个数**，如果满足 $a_i < a_x$，就增加 $cnt$。这样就可以得出区间内小于 $a_x$ 的个数是否与 $x - l$ 的个数相等，$x - l$ 表示从 $l$ 到 $x - 1$ 有多少个数，如果排序后前面数的个数，也就是 $cnt$ 和原本在 $a_x$ 前的数相等，$a_x$ 的值就不会改变。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 1;
int n, m, a[N];
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
	while(m --)
	{
		int l, r, x;
		cin >> l >> r >> x;
		// l到r的区间 
		int cnt = 0;
		//区间内有多少个数比a[x]小，等同于排序后a[x]前有多少个数 
		for(int i = l; i <= r; i ++)
			if(a[i] < a[x]) cnt ++;
			//累加区间内比a[x]小的数的个数 
		if(x - l == cnt) cout << "Yes\n";
		//如果排序前a[x]前的数的个数和排序后a[x]前的数的个数相等，a[x]的值就没变 
		else cout << "No\n";
	}
	return 0;
}

```


---

## 作者：安舒阳 (赞：0)

本题的时限有两秒，但是全部排序的解法是[过不了的](https://www.luogu.com.cn/record/87458972)。所以就需要思考如何简化排序步骤。

根据排序的性质我们可以发现：对于排序序列中的数 $a_i$，排在他前面的数一定比它小，反过来也可以说是 $a_i$ 的位置取决于排在他前面的数。

这样我们只需要遍历要排序的数列找出比 $a_i$ 小的数的个数就能确定 $a_i$ 的位置进而判断数是否改变。

这里我们使用一个计数器来记录小于的数的个数，如果 $cnt$ 刚好到 $k-1$，也就是小于它的数刚好有 $cnt$ 个，那么他就在第 $cnt+1$ 位，也就是它的位置没有发生改变

还有一个细节：作为**一个排列，当中的每个数是不相同的**，所以我们只需要考虑位置有没有发生改变即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	int data[10005];
	int ttmp[10005];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&data[i]);
	}//按照要求输入，data从1输入不要给自己挖坑
	
	for(int i=0;i<m;i++){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		
		const int should=data[k];//排序后k位置上需要的数
		int cnt=0;
		for(int j=l;j<=r;j++){
			if(data[j]<should){//只考虑小于的
				cnt++;
			}
		}
		if(cnt==k-l){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
	return 0;
}
```


---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF811B)

# 题意简述

有一个长度为 $n$ 的排列，每次选一段区间 $[l,r]$ 排序，问位置 $x$ 上的数在排序前后是否发生了改变。保证 $x \in [l,r]$。

# Solution

此题暴力枚举即可。

因为是求位置 $x$ 的数排名有没有改变，所以我们要先求出它的原始排名。我们可以遍历整个排序的范围，即 $l$ 到 $r$，判断当前元素是否小于位置 $x$ 的数，如果是，进行累加。代码：

```cpp
for(int j=l; j<=r; j++)
	if(a[j]<a[x])
		ans++;
```

然后用上一步求得的 $ans$，即区间内小于位置 $x$ 的数的数量，加上区间的左端点 $l$，如果结果等于 $x$，证明它的位置没有改变，输出 `Yes`，否则输出 `No`。代码：

```cpp
if(l+ans==x) {
	printf("Yes\n");
} else {
	printf("No\n");
}
```

最后放下完整代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m, a[10005];
	scanf("%d%d", &n, &m);
	for(int i=0; i<n; i++) scanf("%d", &a[i]);
	for(int i=0; i<m; i++) {
		int l, r, x, ans=0;
		scanf("%d%d%d", &l, &r, &x);
		for(int j=l; j<=r; j++)
			if(a[j]<a[x])
				ans++;//统计个数
		if(l+ans==x) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}
```

By 2022.7.22 蒟蒻的第二十五篇题解

---

## 作者：空清虚 (赞：0)

# 背景

1.2，元旦回校 day1。（为什么人家正常都是 1.3 下午回校啊）

教练在 vjudge 开模拟赛，于是出了这套本来在 cf 的题目。

# 思路

首先，我要说明，我的做法是没有算法的。（蒟蒻水平不够高，没学到算法）

这道题的给的数据是 $n,m\le 10^4$。

(大概)上限 $10^8$ 的时间复杂度，也就是说双重循环 stl 快排暴力是绝对不可行的，TLE 在第 35 个点。（亲测）

接下来的 50 分钟，我的思路逐渐向前缀和优化方向发展。（错）

首先

如何确定区间里面我们需要的数的位置？

首先有个大前提，就是数列中只是数字乱序。即只有可能出现大小在 $[1,n]$ 区间内的数。

那么，每个数的值便是它在区间中的位置信息。

在一个区间里面有上下界，我们可以通过上下界来确定，并且最劣时间复杂度是区间长度的一半，也就是在内部循环我们可以杀掉一半的时间复杂度，只需要加一个 `if`。

 具体实现

当给出 $[l,r]$ 区间小于（或者可以加等于，只要判断两个分支包括等于就可以，不要重复运算）$n$ 的一半时，从 $[l,r]$ 中枚举位置信息。

反之，从 $[1,n]$ 区间外枚举位置信息。

枚举方式多样，包括计算小于或大于其值的个数等。

代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,nu[10003],l,r,p;
int main()
{
	scanf("%d%d",&n,&m);
	for (register int i=1;i<=n;i++)
		scanf("%d",&nu[i]);
	for (register int i=1;i<=m;i++)//主要关注点
	{
		int sum;
		scanf("%d%d%d",&l,&r,&p);
		if (r-l+1>n/2)
		{
			sum=nu[p]-1;
			for (register int j=1;j<l;j++)
				if (nu[p]>nu[j]) sum--;
			for (register int j=r+1;j<=n;j++)
				if (nu[p]>nu[j]) sum--;
		}
		else
		{
			sum=0;
			for (register int j=l;j<=r;j++)
				if (nu[p]>nu[j]) sum++;
		}
		if (l+sum==p) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：xzggzh1 (赞：0)

题意：

有一个长度为 $n$ 的排列，每次选一段区间 $[l,r]$ 排序，问位置 $x$ 上的数在排序前后是否发生了改变。保证 $x∈[l,r]$ 。

---

由于 $n,m \leq 10^4$ 所以 $O(n\times m)$ 的暴力可以过。

每次循问的时候遍历区间，查找在区间中比位置 $x$ 的数小的数，然后计算排名是否与原来在区间里的位置相同即可。

当然，若数据范围增大也可以用主席树来搞。

代码：（主席树）

```cpp
int n,m,cnt=0,a[100001];
int root[100001],t[2500001],lt[2500001],rt[2500001];
inline void build(int l,int r,int& nod){
    nod=++cnt;t[nod]=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(l,mid,lt[nod]);
    build(mid+1,r,rt[nod]);
}
inline void xg(int l,int r,int& nod,int la,int p){
    nod=++cnt;t[nod]=t[la]+1;lt[nod]=lt[la];rt[nod]=rt[la];
    if(l==r)return;
    int mid=(l+r)>>1;
    if(p<=mid)xg(l,mid,lt[nod],lt[la],p);
    else xg(mid+1,r,rt[nod],rt[la],p);
}
inline int s(int l,int r,int x,int y,int k){
    if(l==r)return l;
    int mid=(l+r)>>1,cmp=t[lt[y]]-t[lt[x]];
    if(k<=cmp)return s(l,mid,lt[x],lt[y],k);
    else return s(mid+1,r,rt[x],rt[y],k-cmp);
}
int main()
{
    n=read();m=read();int sum=n;
    for(int i=1;i<=n;i++)a[i]=read();
    build(1,sum,root[0]);
    for(int i=1;i<=n;i++)xg(1,sum,root[i],root[i-1],a[i]);
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),z=read();
        int k=s(1,sum,root[x-1],root[y],z-x+1);
        if(k==a[z])puts("Yes");
        else puts("No");
    }
}
```

---

## 作者：IkunTeddy (赞：0)

# 做法分析
这个题看起来暴力会超时，但实际上暴力就是最好的方法，暴力就完事了。

直接枚举 $l$ 到 $r$ 这个区间，只要所有比 $a[x]$ 小的数都能够刚好排列到 $ a[x] $ 前面，那么 $ a[x] $ 就不会变。
# Code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn=10000+10;
int a[maxn];
int b[maxn];

int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int k=1;k<=m;k++){
		int l,r,x;
		cin>>l>>r>>x;
		int c=a[x];
		int tmp=0;
		for(int i=l;i<=r;i++){
			if(a[i]<c) tmp++;
		}
		if(tmp==x-l) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}

	return 0;
}

```


---

## 作者：xudiyao (赞：0)

# 洛谷CF811B题解
## 题目大意

在一个长度为 $n$ 的排列里，每次选一段区间 $[l,r]$ 排序，问位置 $x$ 上的数在排序前后是否发生了改变。

## 思路引导

数据范围较小，可以直接暴力搜索。

在区间 $[l,r]$ 里，如果有一个数比位置 $x$ 上的数要小，则位置 $x$ 上的数前面有多少个数，若与排序前的个数一致，则输出 ```Yes```，否则输出 ```No```。

## 示范代码
~~~cpp
#include <bits/stdc++.h>//万能头文件yyds。 
using namespace std;
int f[10100],k[10100];
int main()
{
  int n,m,a,b,c,s;
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>f[i];
	for(int i=1;i<=m;i++)
	{
	  s=0;
		cin>>a>>b>>c;;
		for(int j=a;j<=b;j++)  if(f[j]<f[c]) s++;//有几个数比位于x这个位置上的数要大。 
		if(s+a==c) k[i]=1;//若与排序前相同。 
	}
	for(int i=1;i<=m;i++)//输出 。 
	{
	  if(k[i]==1) cout<<"Yes\n";
	  else cout<<"No\n"; 
  }
	return 0;
}//AC撒花。
//禁止抄题解！！！
~~~

---

