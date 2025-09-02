# Lottery

## 题目描述

$ n $ people indexed with integers from $ 1 $ to $ n $ came to take part in a lottery. Each received a ticket with an integer from $ 0 $ to $ m $ .

In a lottery, one integer called target is drawn uniformly from $ 0 $ to $ m $ . $ k $ tickets (or less, if there are not enough participants) with the closest numbers to the target are declared the winners. In case of a draw, a ticket belonging to the person with a smaller index is declared a winner.

Bytek decided to take part in the lottery. He knows the values on the tickets of all previous participants. He can pick whatever value he wants on his ticket, but unfortunately, as he is the last one to receive it, he is indexed with an integer $ n + 1 $ .

Bytek wants to win the lottery. Thus, he wants to know what he should pick to maximize the chance of winning. He wants to know the smallest integer in case there are many such integers. Your task is to find it and calculate his chance of winning.

## 说明/提示

In the first example, Bytek wins for $ 4 $ target values (namely $ 0, 1, 2, 3 $ ) if he chooses integer $ 2 $ , which is the lowest optimal value. If he chooses $ 3 $ , he also wins in four cases, but it is not the lowest value.

## 样例 #1

### 输入

```
3 6 2
1 4 5```

### 输出

```
4 2```

## 样例 #2

### 输入

```
7 7 1
2 4 7 3 0 1 6```

### 输出

```
1 5```

# 题解

## 作者：IdnadRev (赞：5)

首先注意到我们可以任意打乱编号，因为我们只在意自己有没有获奖而不在意其余获奖者是谁，于是我们不妨令 $a$ 数组有序。

特判掉 $k\geqslant n+1$ 的情况，我们使用双指针枚举获奖的一段长为 $k-1$ 的区间，并使用二分计算出这段区间的人获奖需要 target 在哪段区间内（也可以直接 $O(1)$ 计算）。

对于某个 target 值，很容易计算出能让我们获奖的值区间，我们做区间加以一后全局最大值即为答案。能写出这段暴力代码：

```cpp
for(long long i=xl;i<=xr;i++){
	long long v=min(i-b[l-1],b[r+1]-i);
	add(i-v+1,i+v-1,1);
}
```

我们将 target 区间按照是否满足 `i-b[l-1]<=b[r+1]-i` 分为左右两段，以左边为例，其等价于差分数组某个位置 $+k$，某段区间奇偶性为 $c$ 的所有位置 $-1$。

离散化值域，扫描一遍，每一段奇数位置差分数组相同，偶数位置差分数组相同，因此最值只可能在开头结尾以及其相邻位置取到。

复杂度 $O(n\log n)$，瓶颈在排序。

代码有点长，放[剪贴板](https://www.luogu.com.cn/paste/idzyck7l)里了，实现时要格外注意相同坐标人的处理。

---

## 作者：王熙文 (赞：4)

## 思路

考虑如果确定了 $x,c$，$|v_i-c| \le |x-c|$ 的 $v_i$ 在哪里。假设 $c\le x$，那么满足要求的 $v_i$ 一定在 $x$ 左边。进一步可以发现 $2c-x \le v_i \le x$。

那么对于一个 $c$，需要满足：当 $c\le x$ 时， $2c-x$ 大于从 $x$ 向左的第 $k$ 个 $v_i$；当 $c>x$ 时，$2c-x$ 小于从 $x$ 向右的第 $k$ 个 $v_i$。

对于一个 $x$，可以求出从 $x$ 向左、向右的第 $k$ 个 $v_i$，设其为 $l,r$，那么 $c$ 的个数就可以求出来了。当 $x$ 向左、向右不存在第 $k$ 个数，则 $c$ 的左或右端点为 $0$，否则 $c$ 的左或右大概在 $l,r$ 与 $x$ 的平均数左右。

可以发现每个 $x$ 不同的 $(l,r)$ 只有 $\mathcal O(n)$ 个，对于每一个 $(l,r)$ 相同的区间，只需要求区间最左、右的两个即可。

这是因为：当存在 $l$ 时，如果存在 $r$，则区间答案的变化量为 $1$（因为除以 $2$ 会有奇偶的问题），检查最左的两个即可。如果不存在 $r$，则区间的答案单调递减，也检查最左的两个。当不存在 $l$ 时，如果不存在 $r$，与都存在同理。如果存在 $r$，则区间答案单调递增，需要检查最右的两个。

具体实现中，先检查 $0,1,m-1,m$，再对于每个 $v_i$ 检查 $v_i-2,v_i-1,v_i,v_i+1,v_i+2$，这样一定包含了所有区间的左端点和右端点。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k;
int a[1000010];
int ax=-1,wz;
void get_min(int x)
{
	int wz1=upper_bound(a+1,a+n+1,x)-a-1;
	int wz2=lower_bound(a+1,a+n+1,x)-a;
	int l,r;
	if(wz1-k+1<=0) l=0;
	else l=(a[wz1-k+1]+1+x+1)/2;
	if(wz2+k-1>n) r=m;
	else r=(a[wz2+k-1]-1+x)/2;
	int nowans=max(r-l+1,0ll);
	if(ax<nowans || (ax==nowans && wz>x)) ax=nowans,wz=x;
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n>>m>>k;
	for(int i=1; i<=n; ++i) cin>>a[i];
	sort(a+1,a+n+1);
	get_min(0),get_min(m);
	if(m!=0) get_min(1),get_min(m-1);
	for(int i=1; i<=n; ++i)
	{
		for(int j=-2; j<=2; ++j)
		{
			if(0<=a[i]+j && a[i]+j<=m) get_min(a[i]+j);
		}
	}
	cout<<ax<<' '<<wz;
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

先来考虑下，给定一个 $x$ 如何算式子的值。

当 $c=0$ 时，显然所有 $a_i \leq x$ 的 $i$ 都在 $x$ 前面，然后你发现当 $c$ 扫过 $\frac{x+a_i}{2}$ 时会导致 $x,a_i$ 的相对位置关系发生变化，于是一个 $x$ 保证其前面只有少于 $k$ 个数的 $c$ 一定是一个区间，也就是 $x$ 前面 $k$ 个数和后面 $k$ 个数的反转区间内部，故可以利用二分 $O(\log n)$ 求出一个 $x$ 的答案。

然后观察下贡献答案和什么有关，你发现只和 $x$ 在 $a$ 数组中的排名以及奇偶性有关，但是存在一种特殊情况，当前面 $k$ 个数或者后面 $k$ 个数超出数组时，就会和这个 $x$ 本身的大小呈现正比或者反比，所以对每个相邻 $a_i$ 构成的区间和 $a_i$ 本身构成的区间最左边两个数和最右边两个数拎出来计算答案即可，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6+114;
int a[maxn];
int n,m,k;
int L(int x){
    //c 最少多少可以反转 x 前面的数的劣势
    if(x<a[1]) return 0;
    int l=1,r=n+1;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(a[mid]<=x) l=mid;
        else r=mid;
    }
    //a[1,l]<=x
    if(l<k) return 0;
    else{
        return (x+a[l-k+1])/2+1;
    }
}
int R(int x){
    //c 最少多少可以不让 x 后面的反转
    if(x>a[n]) return m;
    int l=0,r=n;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(a[mid]>=x) r=mid;
        else l=mid;
    }
    //a[r,n]>=x
    if(n-r+1<k) return m;
    else{
        return (x+a[r+k-1]+1)/2-1;
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    int ans=0,w=0;
    for(int i=1;i<=n;i++){
        if(a[i]>0){
            int x=a[i]+1;
            if(x<=m){
                int l=L(x),r=R(x);
                if(r-l+1>ans||(r-l+1==ans&&x<w)){
                    ans=r-l+1;
                    w=x;
                }
            }
            x=a[i]+2;
            if(x<=m){
                int l=L(x),r=R(x);
                if(r-l+1>ans||(r-l+1==ans&&x<w)){
                    ans=r-l+1;
                    w=x;
                }
            }
            x=a[i]-1;
            if(x>=0){
                int l=L(x),r=R(x);
                if(r-l+1>ans||(r-l+1==ans&&x<w)){
                    ans=r-l+1;
                    w=x;
                }
            }
            x=a[i]-2;
            if(x>=0){
                int l=L(x),r=R(x);
                if(r-l+1>ans||(r-l+1==ans&&x<w)){
                    ans=r-l+1;
                    w=x;
                }
            }
        }
        int x=a[i];
        int l=L(x),r=R(x);
        if(r-l+1>ans||(r-l+1==ans&&x<w)){
            ans=r-l+1;
            w=x;
        }
    }
    int l=L(0),r=R(0);
    if(r-l+1>ans||(r-l+1==ans&&0<w)){
        ans=r-l+1;
        w=0;
    }
    if(1<=m){
        l=L(1),r=R(1);
        if(r-l+1>ans||(r-l+1==ans&&1<w)){
            ans=r-l+1;
            w=1;
        }
    }
    if(m>=0){
        l=L(m),r=R(m);
        if(r-l+1>ans||(r-l+1==ans&&m<w)){
            ans=r-l+1;
            w=m;
        }
    }
    if(m-1>=0){
        l=L(m-1),r=R(m-1);
        if(r-l+1>ans||(r-l+1==ans&&m-1<w)){
            ans=r-l+1;
            w=m-1;
        }
    }
    cout<<ans<<" "<<w<<"\n";
    return 0;
}
```

---

## 作者：N1K_J (赞：0)

写 vjudge 题目找错题了，误打误撞写了这一题。

首先这个关于权值的答辩式子的意思就是数轴上到 $c$ 距离小于 $x$ 到 $c$ 距离的 $v_i$ 个数少于 $k$。

假设 $c \le x$，也就是说 $[2c-x,x]$ 区间内 $v_i$ 的个数少于 $k$。

也就是说数轴上 $x$ 的左起第 $k$ 个 $v_i=v_l$ 满足 $|c-x| < |c-v_l|$，同理，数轴上 $x$ 的又起第 $k$ 个 $v_i=v_r$ 满足 $|c-x| < |c-v_r|$。

这样就能直接求出给定 $x$ 的情况下 $c$ 的范围。

考虑 $[0,m]$ 所有的 $x$ 肯定是不行的。

但是可以考虑 $x$ 的权值构成的函数（假设直接把证书之间的部分连起来）。

需要注意到权值的最大值是非常靠近某一个 $v_i$ 或者 $0,m$ 的，这是因为这样子会尽可能的增大取左右第 $k$ 个时 $c$ 可行区间的长度，所以说最后的结果可以考虑求所有 $x$ 为形如 $[v_i-B,v_i+B],[0,B],[m-B,m]$ 区间内的解。

代码里 $B=10$，可以没有问题的通过，题解区还有 dalao 给出了 $B \le 2$ 的详细证明，可以参考一下。

[Code](https://codeforces.com/contest/1835/submission/249905572)

---

