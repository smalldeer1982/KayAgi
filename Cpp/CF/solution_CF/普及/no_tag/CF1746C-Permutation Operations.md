# Permutation Operations

## 题目描述

You are given a permutation $ a $ of size $ n $ and you should perform $ n $ operations on it. In the $ i $ -th operation, you can choose a non-empty suffix of $ a $ and increase all of its elements by $ i $ . How can we perform the operations to minimize the number of inversions in the final array?

Note that you can perform operations on the same suffix any number of times you want.

A permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array. A suffix is several consecutive elements of an array that include the last element of the array. An inversion in an array $ a $ is a pair of indices $ (i, j) $ such that $ i > j $ and $ a_{i} < a_{j} $ .

## 说明/提示

In the first test case one of the optimal solutions is to increase the whole array on each operation (that is, choose the suffix starting at index $ 1 $ ). The final array $ [11, 12, 13, 14] $ contains $ 0 $ inversions.

In the second test case, $ a $ will be equal to $ [2, 4, 3, 5, 6] $ , $ [2, 4, 3, 7, 8] $ , $ [2, 4, 6, 10, 11] $ , $ [2, 8, 10, 14, 15] $ and $ [7, 13, 15, 19, 20] $ after the first, second, third, fourth, and fifth operations, respectively. So the final array $ a $ has zero inversions.

## 样例 #1

### 输入

```
4
4
1 2 3 4
5
1 3 2 4 5
3
2 3 1
1
1```

### 输出

```
1 1 1 1
1 4 3 2 1
1 3 3
1```

# 题解

## 作者：lenlen (赞：13)

### Problem

题目大意：给你一个 n 的排列，第 i 次操作是使序列的一个后缀加上 i，操作 n 次，使得序列严格递增。

数据范围： $t \leq 10^4,\sum n \leq 2 \times 10^5$。

### Solution

这个题运用了点差分的思想吧，不过也仅仅是思想而已。

一个后缀加上一个数，并不会影响这个后缀本身的单调性，只会影响后缀的第一个数与前一个数的大小关系，也就是只会影响后缀的第一个数的差分。

所以我们寻找 $a_i \leq a_{i-1}$ 的位置，然后给 $a_i$ 后缀加上一个 $a_{i-1}$ 就可以了。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7232;
int t,n;
int a[N],s[N],ans[N];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),s[i]=a[i]-a[i-1],ans[i]=0;
        for(int i=1;i<=n;i++)
        {
            if(s[i]>0) continue;
            ans[a[i-1]]=i;
        }
        for(int i=1;i<=n;i++) if(!ans[i]) ans[i]=1;//这个地方你想填什么都可以，已经不影响单调性了
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        printf("\n");
    }
}
```


---

## 作者：晴空一鹤 (赞：8)

[题面传送门](https://www.luogu.com.cn/problem/CF1746C)

# Solution

先大体翻译一下：你有一个长度为 $n$ 的排列，同时你可以进行 $n$ 次操作，在第 $i$ 次操作时你可以选择该排列的一个后缀，让他们加上 $i$ ，最终目的是让这个排列变成一个严格单调递增的数组。

构造题。个人认为是比赛中最简单的题。

首先观察，给一个后缀整体加某个数其实对相对大小有影响的只有该后缀最前面一个数和以及这个数前面的那个数。而有 $n$ 次操作，该数组的长度也只有 $n$ ,于是我们可以考虑对原排列的每一个后缀都进行一次加法。

又由于是排列，$1$ ~ $n$ 每个数将恰好出现一次。

于是构造方法出来了：我们每次找到数字 $i$ 在排列中出现的位置，再把他后面的每个数加上 $i$ ,由于排列中不可能有负数，后面的每个数都将大于 $i$ ！

就这样操作 $n$ 轮，由于是排列，刚好会对每个数后面的后缀进行一次加法，于是便保证了对于任意一个位置，它后面的数都会严格大于他！

于是这道题就做完了。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200001],b[200001];
int main()
{
	cin>>t;
	while(t--){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
	cin>>a[i];b[a[i]]=i+1;}
	for(int i=1;i<=n;i++)cout<<min(b[i],n)<<" ";
	cout<<"\n";
}
}
```


---

## 作者：GalwayGirl (赞：5)

给个不要脑子好想的做法。

## Problem

题目大意：你有一个长度为 $n$ 的排列，同时你可以进行 $n$ 次操作，在第 $i$ 次操作时你可以选择该排列的一个后缀，让它们加上 $i$，最终目的是让这个序列变成严格单调递增。

数据范围： $t \leq 10^4, \sum n \leq 10^5$。

## Solution

分析一下，我们可以发现要让这个序列满足单调递增，那么显然要使所有的差分都大于 $0$，而我们的每一次更改，可以发现只会更改我们更改的后缀的第一位数的差分，并不会影响这个后缀本身的单调性，所以做法也就很显然了：

记下差分数组，我们目标是把所有负数变为正数。那我们把它们放进小根堆，因为每次操作都可以加上 $i$，我们肯定会让最小的加上最大的，所以就从小根堆把值提出来，倒序加上 $i$，再放回堆里去，这样可以满足操作正确，时间复杂度 $O(n \log n)$。

虽然时间长，码量较大，但是在打 CF 前面几题时尽量写比较直观思维难度小的代码以节省时间。

最后贴上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
int t,n,a[N],cha[N],ans[N];
struct hh{
    int id,val;
    bool operator <(const hh&a)const {
        return a.val<val;
    }
};
int main(){
    scanf("%d",&t);
    while(t--){
        priority_queue<hh> q;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            cha[i]=a[i]-a[i-1];
            q.push({i,cha[i]});
        }
        for(int i=n;i>=1;i--){
            ans[i]=q.top().id;
            int w=q.top().val;
            q.pop();
            w+=i;
            q.push({ans[i],w});
        }
        for(int i=1;i<=n;i++)printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
```


---

## 作者：Scorilon (赞：3)

一道简单的构造题，然而赛场上写的太急时间复杂度没控制好导致超时。

对于每个操作，我们可以发现，改变其大小关系的只有在 $i$ 和 $i+1$ 这个位置，对于 $1\sim i$ 及 $i+1 \sim n$ 是不改变其大小关系的。

因此，我们只要找到每一个非严格单调递增的地方，改变其关系即可。

而要怎么更改呢？对于两个数 $x_1$ 与 $x_2$，已知 $x_1 \ge x_2$，只要将 $x_1$ 加上 $x_2$，将 $x_2$ 加上 $x_1$ 就可以保证 $x_1 < x_2$。同时因为这是一个排列，可以保证不会有冲突，此做法可行。时间复杂度 $O(n)$。

```cpp
#include <cstdio>
#include <iostream>
 
using namespace std;
 
int t;
int n;
int a[100005];
int p[100005];
 
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),p[i]=0;
		for(int i=1;i<=n;i++) {
			if(i>1&&a[i]<a[i-1]) p[a[i]]=i-1,p[a[i-1]]=i;
		}
		for(int i=1;i<=n;i++) {
			if(!p[i]) printf("1 ");
			else printf("%d ",p[i]);
		}
		puts("");
	}
	return 0;
} 
```


---

## 作者：aCssen (赞：0)

### Solution
考虑差分。

我们设 $c_i=a_{i}-a_{i-1}$，则题目的要求就变为了 $\forall 1 \le i \le n,c_i > 0$，而第 $i$ 次操作则可以转化为取一个 $1 \le p \le n$，令 $c_p=c_p+i$。

又因为 $a$ 是一个排列，所以 $|c_i|$ 一定小于 $n$，同时最大的 $|c_i|$ 最多只有 $1$个。而我们的操作最后一步可以加 $n$，所以一定有解。

这组解应该这样构造：先将 $c$ 从小到大排序，对于所有 $c_i <0$，依次使用第 $n,n-1,\dots,1$ 个操作，因为小于零的数，越小其绝对值越大。

如果遇到了一个 $c_i > 0$，直接跳出循环即可，此时没有更新到的答案可全部设为 $1$，因为全局加不影响相对大小关系。
### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e5+5;
struct node{int c,id;}t[maxn];
int a[maxn],ans[maxn],n;
bool cmp(node a,node b){
	return a.c<b.c;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		t[i]=(node){a[i]-a[i-1],i};
	sort(t+1,t+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(t[i].c>=0) break;
		ans[n-i+1]=t[i].id;
	}
	for(int i=1;i<=n;i++){
		if(ans[i]>0) printf("%d ",ans[i]);
		else printf("1 ");
		ans[i]=0;
	}
	printf("\n");
} 
int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：Light_Cone (赞：0)

# Problem
- 题意：给定一个 $n$ 的排列，共有 $n$ 次操作，第 $i$ 次操作使得排列的非空后缀的元素分别增加 $i$，使得序列中的逆序对数量最少。
 
- 数据范围 $1\le n \le {10}^5,1 \le a_i \le n,\sum n\le 2 \times{10}^5$

# Solution
 不妨考虑逆序对的定义： $i>j$ 且 $a_i<a_j$。

 进一步思考选择一个后缀加上 $i$ 的影响，不难想到对于所选择的后缀内部，其逆序对贡献不变，而未被选择的部分则会改变其贡献，且对后缀进行操作逆序对数量一定不大于操作前的数量。
 
 我们不妨差分的去想，若使第 $i$ 位的元素所贡献的逆序对数量最少，则我们需要使 $a_j\le a_i(1 \le j<i)$。也就是说，第 $k$ 次操作在对 $a_i$ 为起始位置的后缀，会使得 $\max {a_j}-a_i\leftarrow\max a_j-a_i-k(1\le j<i)$。对于 $a_i$，其 $\max {a_j}-a_i\le n-a_i$，故我们只需将第 $n-a_i+1$ 次操作选在下标为 $i$ 的位置即可。
 
 时间复杂度 $O(n)$。
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define fori(i,n) for(int i=1;i<=n;i++)
using namespace std;
using ll = long long;
int t;
void solve()
{
    int n;
    cin>>n;
    vector <int> a(n+1),ans(n+1);
    fori(i,n) cin>>a[i],ans[n-a[i]+1]=i;
    fori(i,n) cout<<ans[i]<<" \n"[i==n];
}
int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>t;
    while(t--)
        solve();
    return 0;
}
```



---

