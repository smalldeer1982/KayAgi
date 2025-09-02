# Wardrobe

## 题目描述

Olya wants to buy a custom wardrobe. It should have $ n $ boxes with heights $ a_{1},a_{2},...,a_{n} $ , stacked one on another in some order. In other words, we can represent each box as a vertical segment of length $ a_{i} $ , and all these segments should form a single segment from $ 0 $ to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924E/5093cd7c115b544583c5d55ccc379a13fe72e866.png) without any overlaps.

Some of the boxes are important (in this case $ b_{i}=1 $ ), others are not (then $ b_{i}=0 $ ). Olya defines the convenience of the wardrobe as the number of important boxes such that their bottom edge is located between the heights $ l $ and $ r $ , inclusive.

You are given information about heights of the boxes and their importance. Compute the maximum possible convenience of the wardrobe if you can reorder the boxes arbitrarily.

## 说明/提示

In the first example you can, for example, first put an unimportant box of height $ 2 $ , then put an important boxes of sizes $ 1 $ , $ 3 $ and $ 2 $ , in this order, and then the remaining unimportant boxes. The convenience is equal to $ 2 $ , because the bottom edges of important boxes of sizes $ 3 $ and $ 2 $ fall into the range $ [3,6] $ .

In the second example you have to put the short box under the tall box.

## 样例 #1

### 输入

```
5 3 6
3 2 5 1 2
1 1 0 1 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 2 5
3 6
1 1
```

### 输出

```
1
```

# 题解

## 作者：cwfxlh (赞：1)

# [CF924E](https://www.luogu.com.cn/problem/CF924E)    

儿简送。     

箱子底端不太好处理，于是将 $[l,r]$ 变为 $[\sum h_i-r,\sum h_i -r]$，就可以只考虑箱子顶端了。    

显然的，放置箱子一定是先来一堆不重要的垫底，再拿重要的箱子往上堆，直到堆过 $[l,r]$ 后再用剩下的箱子封顶，原因是显然的。      

另外，在 $r$ 下面的重要箱子，必定是从大到小往上堆的，因为这堆重要箱子的顶部是确定的，所以必定是从上往下尽量放小箱子，才能最大化在区间内的箱子顶部个数。     

于是跑两个背包，第一个背包是跑出用不重要的箱子能堆到的高度，第二个背包在第一个背包基础上，按从大到小的顺序跑重要箱子的背包，记录在区间内的箱子顶部个数最多是多少。复杂度 $O(n\sum h_i)$。     

代码：    

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,h[500003],b[500003],dp[200003],k1,k2,k3;
int stk1[500003],stk2[500003],tot1,tot2,ans;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++)cin>>h[i];
    for(int i=1;i<=n;i++){
        cin>>b[i];
        if(b[i])stk2[++tot2]=h[i];
        else stk1[++tot1]=h[i];
    }
    for(int i=1;i<=n;i++)k1+=h[i];
    l=k1-l;
    r=k1-r;
    swap(l,r);
    sort(stk1+1,stk1+tot1+1);
    sort(stk2+1,stk2+tot2+1);
    for(int i=0;i<=10000;i++)dp[i]=-1000000;
    dp[0]=0;
    for(int i=1;i<=tot1;i++){
        for(int j=k1;j>=stk1[i];j--){
            if(dp[j-stk1[i]]==0)dp[j]=0;
        }
    }
    for(int i=tot2;i;i--){
        for(int j=k1;j>=stk2[i];j--){
            dp[j]=max(dp[j],dp[j-stk2[i]]+((j>=l)&&(j<=r)));
        }
    }
    ans=0;
    l=max(l,0);
    r=min(r,k1);
    for(int i=l;i<=r;i++)ans=max(ans,dp[i]);
    cout<<ans;
    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
题意简述：有 $n$ 个箱子，对于每一个箱子都有一个固定的高度 $h_i$ 并且部分箱子定义为重要的。要把它们堆成一摞，请问最多有多少个重要的箱子**底部的高度**位于 $l$ 和 $r$ 之间。

数据范围都是 $10^4$ 那么我们考虑一些 $O\left(n^2\right)$ 的算法。
## 分析。
既然是一个区间，那么我们不难想到，这些箱子的摆放必定是一堆不重要的箱子垫底，然后是重要的箱子，最后再用不重要的箱子封顶。那么我们只要最大化中间的这些箱子即可。但是我们发现如果处理箱子的底部，我们仍然要判断上端，所以我们不妨将这一摞箱子反过来，区间随之修改，则整个求解区间不变，而上下端点改变，此时的问题就变成了：

令 $k=\sum h_i$ 则请问有多少个箱子的**顶部**位于区间 $\left[k-r,k-l\right]$。此时就便于处理了。

此时分别处理一下重要的和不重要的箱子。显然对于相同种类的箱子，高度较小的箱子位于上面会更优，因为这样会使得整个塔的高度不变且两个端点更加接近。那么现在的算法就很显然了，背包和动态规划。事实上，这个的时间复杂度为 $O\left(n\times\sum h_i\right)$ 即 $O\left(n^2\right)$ 的样子。正正好。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,l,r;
int k,sum,ans;
int dp[100005];
struct node{
	int x,y;
}h[100005];
bool cmp(node first,node second){
	return first.y<second.y||first.y==second.y&&first.x>second.x;
}
int main(){
	cin>>n>>l>>r;
	for (int i=1;i<=n;i++){
		cin>>h[i].x;
		k+=h[i].x;
	}
	for (int i=1;i<=n;i++){
		cin>>h[i].y;
	}
	sort(h+1,h+n+1,cmp);
	dp[0]=1;
	for (int i=1;i<=n;i++){
		for (int j=k;j>=h[i].x;j--){
			if(dp[j-h[i].x]){
				if(j>=k-r&&j<=k-l){
					sum=1;
				}
				else sum=0;
				dp[j]=max(dp[j],dp[j-h[i].x]+h[i].y*sum);
			}
		}
	}
	for (int i=0;i<=k;i++){
		ans=max(ans,dp[i]);
	}
	cout<<ans-1<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：SIGSEGV (赞：0)

令$H=\sum_{i=1}^na_i$,将重要盒子的底端在$[l,r]$内转换为重要盒子的顶端在$[L,R]$内，其中$L=H-r,R=H-l$。

同时可得出最佳答案的至少一种方案中所有重要的盒子一定会连在一起。

然后考虑背包。背包中选中的物品代表从下往上放，未被选中的物品代表它们最后放，这样算出来的值不会比实际情况少。这样背包是正确的，因为最佳答案肯定会被统计到。

显然不重要盒子必须先做背包且它们的做背包顺序对答案没有影响，然而重要的盒子要按照$a_i$从大到小的顺序做背包，因为在所有选中的重要盒子内把低的放在高的上面一定更优。（有些选中的盒子因为**高度不够**不能统计入答案，这些高度不够的显然用$a_i$大的去垫更好）

算法时间复杂度为$O(nH)$。但是CF的题解中说珂以优化到$O(H\sqrt{H})$，这个菜鸡不会，知道怎么优化的珂以发评论qwq

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int n,dp[N],l,r;
struct Box {int v,tp;} a[N];
int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> l >> r;int sum = 0;
    for (int i = 1;i <= n;i++) cin >> a[i].v,sum += a[i].v;
    for (int i = 1;i <= n;i++) cin >> a[i].tp;
    sort(a + 1,a + n + 1,
    [](Box a,Box b) {return a.tp < b.tp || (a.tp == b.tp && a.v > b.v);});
    int tmp = l;l = sum - r;r = sum - tmp;
    for (int i = 1;i <= sum;i++) dp[i] = INT_MIN >> 2;
    dp[0] = 0;
    for (int i = 1;i <= n;i++)
        for (int j = sum;j >= a[i].v;--j)
            dp[j] = max(dp[j],dp[j - a[i].v] + a[i].tp * (l <= j && j <= r));
    cout << *max_element(dp + 1,dp + sum + 1) << endl;
    return 0;
}

```

---

