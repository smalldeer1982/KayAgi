# PermutationForces II

## 题目描述

You are given a permutation $ a $ of length $ n $ . Recall that permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order.

You have a strength of $ s $ and perform $ n $ moves on the permutation $ a $ . The $ i $ -th move consists of the following:

- Pick two integers $ x $ and $ y $ such that $ i \leq x \leq y \leq \min(i+s,n) $ , and swap the positions of the integers $ x $ and $ y $ in the permutation $ a $ . Note that you can select $ x=y $ in the operation, in which case no swap will occur.

You want to turn $ a $ into another permutation $ b $ after $ n $ moves. However, some elements of $ b $ are missing and are replaced with $ -1 $ instead. Count the number of ways to replace each $ -1 $ in $ b $ with some integer from $ 1 $ to $ n $ so that $ b $ is a permutation and it is possible to turn $ a $ into $ b $ with a strength of $ s $ .

Since the answer can be large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, $ a=[2,1,3] $ . There are two possible ways to fill out the $ -1 $ s in $ b $ to make it a permutation: $ [3,1,2] $ or $ [3,2,1] $ . We can make $ a $ into $ [3,1,2] $ with a strength of $ 1 $ as follows: $ $$$[2,1,3] \xrightarrow[x=1,\,y=1]{} [2,1,3] \xrightarrow[x=2,\,y=3]{} [3,1,2] \xrightarrow[x=3,\,y=3]{} [3,1,2]. $ $  It can be proven that it is impossible to make  $ \[2,1,3\] $  into  $ \[3,2,1\] $  with a strength of  $ 1 $ . Thus only one permutation  $ b $  satisfies the constraints, so the answer is  $ 1 $ .</p><p>In the second test case,  $ a $  and  $ b $  the same as the previous test case, but we now have a strength of  $ 2 $ . We can make  $ a $  into  $ \[3,2,1\] $  with a strength of  $ 2 $  as follows:  $ $ [2,1,3] \xrightarrow[x=1,\,y=3]{} [2,3,1] \xrightarrow[x=2,\,y=3]{} [3,2,1] \xrightarrow[x=3,\,y=3]{} [3,2,1]. $ $  We can still make  $ a $  into  $ \[3,1,2\] $  using a strength of  $ 1 $  as shown in the previous test case, so the answer is  $ 2 $ . </p><p>In the third test case, there is only one permutation  $ b $ . It can be shown that it is impossible to turn  $ a $  into  $ b $ , so the answer is  $ 0$$$.

## 样例 #1

### 输入

```
6
3 1
2 1 3
3 -1 -1
3 2
2 1 3
3 -1 -1
4 1
1 4 3 2
4 3 1 2
6 4
4 2 6 3 1 5
6 1 5 -1 3 -1
7 4
1 3 6 2 7 4 5
2 5 -1 -1 -1 4 -1
14 14
1 2 3 4 5 6 7 8 9 10 11 12 13 14
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1```

### 输出

```
1
2
0
2
12
331032489```

# 题解

## 作者：思考人生中 (赞：10)

UPD：修改了一个错误，感谢评论区指出（

---

搞出一个比官方题解更优的 $O(n)$ 解法（？

---

### 题意

给定 $n$ , $s$ ，对给定的 $1\cdots n$ 的排列 $a$ 做 $n$ 次操作，其中第 $i$ 次选定 $x,y\in [i,\min\{i+s,n\}]$ 将序列中**值**为 $x$ 与 $y$ 的数所在位置交换，其中 $x$ 可以等于 $y$。操作后的 $a$ 变为了排列 $b$ 。现在给出 $b$ 并把其中的一些项替换为 $-1$ ，问有多少个不同的可能的排列 $b$ 。

### 题解

我们发现对一定范围内的数进行选择比较麻烦，因此我们考虑把交换数组中的两个数改为交换两个数的下标。我们可以将操作换成在下标数组上进行操作。

具体地说，首先我们构造一个数组 $c_{1\cdots n}$ 其中 $c_i=j$ 意味着 $a_j=i$ 。

类似地我们构造一个数组 $d_{1\cdots n}$ ，其中,

+ 若数 $i$ 在 $b$ 中的下标已经确定为 $j$ ，令 $d_i=j$ ；
+ 若数 $i$ 在 $b$ 中的下标未确定(即被替换为 $-1$ )，令 $d_i=-1$。

那么我们就可以将题目中的操作转化为：

第 $i$ 次操作选取 $x,y\in [i,\min\{i+s,n\}]$ 并交换 $c_x$ 与 $c_y$ 的值。最终 $c$ 在操作后变为 $d$ 。

这样我们每次都是操作的范围是连续的一段区间，显然舒服的多。

**现在我们再来分析被转化后的操作。**

我们可以发现下面几点：

+ $\forall i$ ，还原后的 $d_i$ 的值必然是 $c_1,c_2\cdots c_{\min\{i+s,n\}}$ 中的一个；
+ 第 $i$ 步的操作对后续操作的可选下标对应数值的范围的影响仅仅为不能选择第 $i$ 步操作后的 $c_i$ ；
+ 若第 $i$ 步选择的 $x,y$ 均不等于 $i$ ，那么这对序列后续操作的影响和 $x=y=i$ 时等价，因为此时的 $x,y$ 的选择对后续每个位置可选的数的范围没有影响。

因此我们不妨令第 $i$ 次操作中 $x=i$ ，从而我们可以认为第 $i$ 次操作确定还原后的 $d_i$ 的值。

**进一步地，我们还可以将“操作”转化为：**

第 $i$ 次操作选取 $c_1,\cdots ,c_{\min\{i+s,n\}}$ 中一个**不存在于** $c'_1,c'_2,\cdots,c'_{i-1}$ 的数 $c_k$ , 然后 $c'_i \leftarrow c_k$ 。 

最终， $c'$ 变为 $d$ 。

这样，我们就会发现每一个未确定的 $d_i$ 的可选值的个数就是 $c_1,\cdots ,c_{\min\{i+s,n\}}$ 中**在所有操作前未确定 $d$ 中下标的数的个数**减去**在 $d_1\cdots d_{i-1}$ 中 $-1$ 的个数（即未确定数值的个数）**。

此外，我们判断是否存在解的方式就是看是否存在 $d_i$ 使得其在 $c$ 中的下标 $j$ 满足 $i+s<j$ 。若有说明无论如何 $d_i$ 所在位置无论什么情况下都不可能取到 $d_i$ ，无解 ；若没有则显然可以做到。

判断是否有解之后，将 $d_i$ 每一位可选值的个数乘起来就是答案了。代码中是若干次线性扫描，因此时间复杂度为 $O(n)$ 。

如果还有不懂的地方就看看代码吧~

### 代码

```cpp
#include<cstdio>
#include<iostream>
#define MAXN 200000
#define MOD 998244353
using namespace std;

int a[MAXN+5],b[MAXN+5],c[MAXN+5],d[MAXN+5];
bool vis[MAXN+5];

int main() {
    ios::sync_with_stdio(0);
    int t,n,s,cnt,p;
    bool flag;
    long long ans;
    cin>>t;
    while (t--) {
        ans=1;cnt=0;flag=0;p=0;
        cin>>n>>s;
        for (int i=1;i<=n;++i) d[i]=-1,vis[i]=0;
        for (int i=1;i<=n;++i) cin>>a[i],c[a[i]]=i;
        for (int i=1;i<=n;++i) cin>>b[i];
        for (int i=1;i<=n;++i) if (b[i]!=-1) d[b[i]]=i,vis[i]=1;
        for (int i=1;i<=n;++i) if (a[d[i]]-i>s) flag=1;
        if (flag==1) {
            cout<<"0\n";
            continue;
        }
        for (int i=1;i<=n;++i) {
            while (p<i+s&&p<n) {++p;if (!vis[c[p]]) ++cnt;}
            if (d[i]==-1) {
                ans=(ans*cnt)%MOD;
                --cnt;
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：老莽莽穿一切 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16459625.html)

---

[**CF link**](http://codeforces.com/problemset/problem/1698/E)

[**你谷 link**](https://www.luogu.com.cn/problem/CF1698E)

与官方题解一样的解法，姑且发一篇题解，个人感觉思路非常自然，不需要什么思维上的火花。

首先考虑从题面入手来分析这道题目的做法，操作 $n$ 次，每次选取**值**在 $[i,i+s]$ 区间内的两个点进行交换，最后使得 $a$ 数组变为 $b$ 数组，然后 $b$ 数组中有一些位置待定，求可行解个数。

首先这种经典的计数题套路就是从判定入手，如果给定一个 $b$ 数组，如何用一种**通用**的方法构造一组解或判定无解，注意到交换的方式有一些特殊，一个很直观的点就是值为 $1$ 的点从始至终只能操作一次，这提醒我们在最劣情况下到第 $i$ 次操作时前 $i-1$ 个值应该已经归位，现在要解决值 $i$ 的问题。

接下来就是解决本题的关键，以一个非常顺畅的思路，我们来到了判定是否有解的关键点——对于每个第 $i$ 次交换能否使 $i$ 回归原处，我们同样可以从 $1$ 开始考虑。

首先我们可以将 $b$ 数组排序，让 $a$ 数组**随着 $b$ 数组**排序，此时就变成把 $a$ 数组变成一个顺序排列，即 $1,2,\cdots,n$，这样的话我们第一次交换就是 $a_1$ 和 $1$，那么要求就是 $a_1\le1+s$ 我们可以将这个特例大胆地普遍化成 $a_i\le i+s$，我们可以试图证明这个东西：

首先这里的所有 $a_i$ 是**没交换前**的 $a_i$，且 $a$ 数组已经随着 $b$ 数组排序，那么我们分两种情况讨论：

1. $a_i>i$，当我们在做 $i$ 时，$a_i$ 还在原本的位置，则交换 $i$ 与 $a_i$，此时情况如上述所说，满足 $a_i\le i+s$。
2. $a_i<i$，此时 $a_i$ 应该已经被交换过了，我们考虑 $a_i$ 被交换成了 $a_j$，那么应该满足 $j<i$，那么上一次操作时的情况所需要满足的要求为 $a_i\le j+s$，这两个不等式的交显然比 $a_i\le i+s$ 更紧，所以满足要求。

上面证明了必要性，而充分性则是通过此要求构造解的过程，那么我们回到原问题，原问题就得到了转化，若 $b$ 数组不排序，约束条件就为 $a_i\le b_i+s$，因为我们是要构造 $b_i$，所以进一步转化为 $b_i\ge a_i-s$。

那这个式子就非常好解决了，无解情况就是已经确定的 $b$ 中有点不满足上述要求，否则我们将所有 $a_i-s$ 取出，即将所有约束取出，再从紧到松排序，即先求出满足要求的情况数，再将情况数从小到大排序，再略加处理乘起来就好了。

实现上时间复杂度瓶颈是 `sort` 的 $\mathcal O\left(n\log n\right)$，如果有闲心可以写计数排序优化到 $\mathcal O\left(n\right)$，这里的[代码](https://codeforces.com/contest/1698/submission/163201275)是一切从简。

---

## 作者：I_am_Accepted (赞：3)

提供一种线性复杂度的方法。

### Analysis

首先，我们发现**每个数在序列中的绝对位置无用**，所以我们将 $\{a\},\{b\}$ 都进行如下变换（$\{b\}$ 中 $-1$ 的那些不用管）：

设原序列为 $\{A\}$，新序列为 $\{B\}$，$B_{A_i}=i$。

（也就是置换的逆）

对于 $\{b\}$ 的新序列，没有被赋值的设为 $-1$。

接下来 $\{a\},\{b\}$ 均指新序列。

那我们的操作就转化为：

$i:1\to n$，每次选择两个**下标** $i \leq x \leq y \leq \min(i+s,n)$ 然后交换两个位置上的元素。

* * *

**结论：** $\{a\}$ 能变成 $\{b\}$ 当且仅当对于任意元素 $x$，设在 $a,b$ 中的下标为 $i,j$，有 $j\ge i-m$。

这里就不证明了，不代表不会……

* * *

然后就转化成：

有 $k$ 个小朋友和 $k$ 颗糖果（$k$ 为 $\{b\}$ 中 $-1$ 的个数），每个小朋友都喜欢糖果序列的一个后缀，问有几种分配方案使得小朋友都拿到喜欢的糖果。

这是一个很经典且简单的 $O(k)$ 问题，不再赘述。

### Code

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ll long long
#define N 200000
const ll mod=998244353;
ll ans;
int n,m,a[N],b[N],c[N],pos[N],tot,x;
void work(){
	cin>>n>>m;
	For(i,0,n-1) cin>>x,a[x-1]=i;
	For(i,0,n-1) b[i]=-1;
	For(i,0,n-1){
		cin>>x;
		if(x!=-1) b[x-1]=i;
	}
	For(i,0,n-1) pos[i]=-1;
	For(i,0,n-1) if(b[i]!=-1) pos[b[i]]=i;
	For(i,0,n-1) b[i]=(b[i]==-1);
	Rof(i,n-2,0) b[i]+=b[i+1];
	tot=0;
	For(i,0,n-1)
		if(pos[a[i]]==-1) c[tot++]=b[max(0,i-m)];
		else if(i-pos[a[i]]>m){
			cout<<0<<endl;
			return ;
		}
	ans=1;
	For(i,0,tot-1) (ans*=c[i]-(tot-1-i))%=mod; 
	cout<<ans<<endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;cin>>T; 
	while(T--)work();
return 0;}
```

---

