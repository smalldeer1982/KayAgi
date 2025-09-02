# Permutations

## 题目描述

You are given a permutation $ p $ of numbers $ 1,2,...,n $ . Let's define $ f(p) $ as the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513B2/01b3997850b3844bd3627bf7c28ebf2176a4c489.png)Find the lexicographically $ m $ -th permutation of length $ n $ in the set of permutations having the maximum possible value of $ f(p) $ .

## 说明/提示

In the first example, both permutations of numbers {1, 2} yield maximum possible $ f(p) $ which is equal to 4. Among them, $ (2,1) $ comes second in lexicographical order.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 3 2 
```

# 题解

## 作者：Wf_yjqd (赞：1)

一篇题解没有，必须得写一下。

------------
做这题前，先做 [CF513B1](https://www.luogu.com.cn/problem/CF513B1)，也就是此题的暴力。

然后我们可以打个表,举个例子。
```cpp
1 2 3 4 5 6 
1 2 3 4 6 5 
1 2 3 5 6 4 
1 2 3 6 5 4 
1 2 4 5 6 3 
1 2 4 6 5 3 
1 2 5 6 4 3 
1 2 6 5 4 3 
1 3 4 5 6 2 
1 3 4 6 5 2 
1 3 5 6 4 2 
1 3 6 5 4 2 
1 4 5 6 3 2 
1 4 6 5 3 2 
1 5 6 4 3 2 
1 6 5 4 3 2 
2 3 4 5 6 1 
2 3 4 6 5 1 
2 3 5 6 4 1 
2 3 6 5 4 1 
2 4 5 6 3 1 
2 4 6 5 3 1 
2 5 6 4 3 1 
2 6 5 4 3 1 
3 4 5 6 2 1 
3 4 6 5 2 1 
3 5 6 4 2 1 
3 6 5 4 2 1 
4 5 6 3 2 1 
4 6 5 3 2 1 
5 6 4 3 2 1 
6 5 4 3 2 1 
32
```
多试几个后，发现两点：


1、$\operatorname{f}(p)$ 最大的排列共 $2^{n-1}$ 个。

2、当 $\operatorname{f}(p)$ 最大时，1 放在最左或最右边，2 放在剩下位置扥最左或最右边，以此类推。

证明：

若有一排列 $p$，原有 $n$ 个数，将当前最小值 $b$ 放在第 $x$ 个，后面的数整体后挪一位时，$\operatorname{f}(p)=(\sum_{i=1}^{n}\sum_{j=i}^{n}\min(p_i,...,p_j))-(\sum_{i=1}^{x-1}\sum_{j=x}^{n}\min(p_i,...,p_j))+(\sum_{i=1}^{x-1}\sum_{j=x}^{n}\min(b,p_i,...,p_j))+n\times b$。

又因 $b$ 是当前最小值，$\operatorname{f}(p)=(\sum_{i=1}^{n}\sum_{j=i}^{n}\min(p_i,...,p_j))+n\times b+(\sum_{i=1}^{x-1}\sum_{j=x}^{n}b-\min(p_i,...,p_j))$。

当 $x$ 取 $1$ 或 $n+1$ 时，$\sum_{i=1}^{x-1}\sum_{j=x}^{n}b-\min(p_i,...,p_j)$ 取 $0$。

由于 $b<\min(p_i,...,p_j)$，所以当 $(x-1)\times (n-x+1)\ne0$ 即 $x\ne1$ 且 $x\ne n+1$ 时，$\sum_{i=1}^{x-1}\sum_{j=x}^{n}b-\min(p_i,...,p_j)<0$。

综上，$x$ 取 $1$ 或 $n+1$，即当前最小值放在最左或最右边时，$\operatorname{f}(p)$ 最大。

每个数放最左或最右边有 $2$ 种情况，而最后一个数只有一个位置可以放，最大的排列共 $2^{n-1}$ 个。

之后，我们用 $2$ 的幂次求每个区间可能的方案数，与 $m$ 作对比，确定 $i$ 放在左还是右能使 $\operatorname{f}(p)$ 最大，直到求出整个排列。

code：
```cpp
/*B1暴力
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,cnt,cntt,ans[50000],ansa[50000][10],maxn,a[10],vis[10];
ll q(){
    ll anss=0,minn;
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=n;j++){
            minn=0x3f3f3f3f;
            for(ll k=i;k<=j;k++)
                minn=min(minn,a[k]);
            anss+=minn;
        }
    return anss;
}
void dfs(ll x){
    if(x==n){
        ans[++cnt]=q();
        for(ll i=1;i<=n;i++)
            ansa[cnt][i]=a[i];
        // printf("%lld\n",ans[cnt]);
        maxn=max(maxn,ans[cnt]);
        return ;
    }
    for(ll i=1;i<=n;i++)
        if(!vis[i]){
            vis[i]=1;
            a[x+1]=i;
            dfs(x+1);
            vis[i]=0;
        }
    return ;
}
int main(){
    scanf("%lld%lld",&n,&m);
    dfs(0);
    for(ll i=1;i<=cnt;i++)
        if(ans[i]==maxn){
            cntt++;
            if(cntt==m){
                for(ll j=1;j<=n;j++)
                    printf("%lld ",ansa[i][j]);
                return 0;
            }
        }
    return 0;
}
B2
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,poww[84],ans[84];
void dfs(ll now,ll l,ll r,ll th){
    if(l==r){//边界
        ans[l]=now;
        return ;
    }
    if(th<=poww[r-l-1]){//左
        ans[l]=now;
        dfs(now+1,l+1,r,th);
        return ;
    }
    ans[r]=now;//右
    dfs(now+1,l,r-1,th-poww[r-l-1]);
    return ;
}
int main(){
    scanf("%lld%lld",&n,&m);//输入
    poww[0]=1;
    for(int i=1;i<=52;i++)
        poww[i]=poww[i-1]*2;//求幂次
    dfs(1,1,n,m);//构造
    for(int i=1;i<=n;i++)
        printf("%lld ",ans[i]);//输出
    return 0;
}
```


---

## 作者：enyyyyyyy (赞：0)

很简单！不就是将 $m$ $2$ 进制的结果存起来。遍历 $1$ 至 $n$，是 $0$，就输出 $i$；遍历 $n$ 至 $1$，是 $1$，就输出 $i$；

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll n,m,k,a[55];
int main() {
	n=read(),m=read()-1;
	while(m) {
		a[++k]=m%2;
		m>>=1;
	}
	for(ll i=1;i<=n;i++)
		if(!a[n-i]) print(i),printf(" ");
	for(ll i=n;i>=1;i--)
		if(a[n-i]) print(i),printf(" ");
	return 0;
}

```

---

