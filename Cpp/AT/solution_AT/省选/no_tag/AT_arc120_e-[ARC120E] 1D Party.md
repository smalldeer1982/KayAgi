# [ARC120E] 1D Party

## 题目描述

有 $ N $ 个人打算开派对，他们均分布在数轴上，编号从 $1$ 到 $N$，第 $i$ 个人位于 $ a_i $ 点。初始是他们都位于数轴上不同的点。具体的，所有人所在的点都是偶数点，且有 $ a_1 < a_2 < a_3 <\cdots< a_n$。

派对计划进行 $k$ 秒，每个人每秒钟可以在数轴上向左或者向右移动一个单位长度，也可以不移动。

我们都知道，开派对至少要两个人。所以派对成功举行的条件是，对于任意的某个人 $j (1≤j<N)$，经过一系列移动过程，在派对进行中至少有一瞬间（包括派对结束的那一刻）使得 $a_j = a_{j+1}$（以当前那一秒结束时的位置为准）。

请计算能够使得派对成功举行的最小的 $k$。

能够证明在题目限定条件下答案一定存在。

## 样例 #1

### 输入

```
3
0 6 10```

### 输出

```
5```

## 样例 #2

### 输入

```
5
0 2 4 6 8```

### 输出

```
3```

## 样例 #3

### 输入

```
10
0 2 4 6 8 92 94 96 98 100```

### 输出

```
44```

# 题解

## 作者：PosVII (赞：8)

**前言**

---

小清新 $O(n)$ dp。

**思路**

---

首先考虑在出现第一次相遇之前，一定会有一对相邻的人走的方向相反，原因显然。

我们已知每次相遇后，整个序列就会一分为二，变为子问题。

样例三提示我们同时并非只有一对相邻的人方向相反，相遇是在同时进行的。

当序列长度 $\le 3$ 时，最优策略一定是 $\frac{(a_r - a_l)}{2}$。否则某个序列长度 $\ge 4$ 时，一定存在一种分割使得答案更优秀。

不存在被分割长度为 $1$ 的序列，因为此时它一定在边上或者一定有一个分割是属于某个长度 $\le 3$ 的序列的。

每个长度为 $3$ 或 $4$ 的分割的时间为 $\frac{(a_{r+1}-a_{l-1})}{2}$，使用 dp 求最小时间即可。

**代码**

---

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN=2e5+5;
int n,a[MAXN],f[MAXN];
signed main() {
	#ifndef ONLINE_JUDGE
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	a[0]=a[1],a[n+1]=a[n];
	f[1]=1e9;
	for(int i=2;i<=n;++i) {
		f[i]=max(f[i-2],(a[i+1]-a[i-2])/2);
		if(i>=3) f[i]=min(f[i],max(f[i-3],(a[i+1]-a[i-3])/2));
	}
	printf("%d",f[n]);
	return 0;
}
```

---

## 作者：hgzxwzf (赞：8)

## [ARC120E] 1D Party

### 解题思路：

首先可以想到二分时间 $t$。

发现每个人都是先向右走碰到一个人后一直向左走或者先向左走碰到一个人之后一直向右走。

以先向右走为例，他碰到他右边的那个人后，肯定要用全力去碰左边那个人。

设 $dp_{i,0}$ 表示第 $i$ 个人一开始向左走最后他的位置减去原本他的位置的最大值，$dp_{i,1}$ 表示第 $i$ 个人一开始向左走最后他的位置减去原本他的位置的最大值。

假设第 $i$ 个人为 $A$，第 $i-1$ 个人为 $B$。

1. $A$ 先向右走，$B$ 先向右走：满足 $a_{i-1}+dp_{i-1,0}\ge a_i-dp_{i-1,0}$ 的情况下转移，$dp_{i,0}\leftarrow \max(dp_{i,0},dp_{i-1,0}-\frac{a_i-a_{i-1}}{2})$，当他们都向右时他们的距离不会变，当 $A$ 向左时，他们需要 $\frac{a_i-a_{i-1}}{2}$ 的时间相遇，而且必须在 $B$ 向左之前相遇，所以留给 $A$ 向右的时间只有 $dp_{i-1,0}-\frac{a_i-a_{i-1}}{2}$；
2. $A$ 先向左走，$B$ 先向右走：满足 $a_{i-1}+dp_{i-1,0}\ge a_i-dp_{i-1,0}$ 的情况下转移，$dp_{i,1}\leftarrow\max(dp_{i,1},t-(a_{i}-a_{i-1})$，$A$ 花费 $\frac{a_i-a_{i-1}}{2}$ 的时间和 $B$ 相遇，花费 $\frac{a_i-a_{i-1}}{2}$ 的时间回到原本自己的位置。
3. $A$ 先向右走，$B$ 先向左走：$B$ 最终的位置在 $a_{i-1}+dp_{i-1,1}$，满足 $a_{i-1}+dp_{i-1,1}\ge a_i-t$ 的情况下转移，$dp_{i,0}\leftarrow\max(dp_{i,0},\frac{t-a_i+a_{i-1}+dp_{i-1,1}}{2})$，设 $A$ 最多向右走 $x$，$(a_i+x)-(a_{i-1}+dp_{i-1,1})=t-x$，解得 $x=\frac{t-a_i+a_{i-1}+dp_{i-1,1}}{2}$。
4. $A$ 先向左走，$B$ 先向左走：满足 $a_{i-1}+dp_{i-1,1}\ge a_i-t$ 的情况下转移，$dp_{i,1}\leftarrow\max(dp_{i,1},dp_{i-1}+a_{i-1}-a_i)$，他们相遇后，一起向右走，所以 $A$ 最后的位置和 $B$ 相同，为 $dp_{i-1}+a_{i-1}$。

如果存在 $i$，使得上面四种情况都不满足，那么就说明 $t$ 小了，因为这样 $i-1$ 和 $i$ 不能相遇。

### Code：
```cpp
const int N=2e5+10;
int a[N],dp[N][2],n;

bool pd(int t)
{
	memset(dp,0xcf,sizeof(dp));
	dp[1][0]=dp[1][1]=t;
	rep(i,2,n)
	{
		bool f=0;
		if(a[i-1]+dp[i-1][0]>=a[i]-dp[i-1][0])
		{
			dp[i][0]=max(dp[i][0],dp[i-1][0]-(a[i]-a[i-1])/2);
			dp[i][1]=max(dp[i][1],t-(a[i]-a[i-1]));
			f=1;
		}
		if(a[i-1]+dp[i-1][1]>=a[i]-t)
		{
			dp[i][0]=max(dp[i][0],(t-(a[i]-(a[i-1]+dp[i-1][1])))/2);
			dp[i][1]=max(dp[i][1],dp[i-1][1]+a[i-1]-a[i]);
			f=1;
		}
		if(!f) return 0;
	}
	return 1;
}

int main()
{
	cin>>n;
	rep(i,1,n) cin>>a[i];
	int l=1,r=(a[n]-a[1])/2,ans;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(pd(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：0x3F (赞：5)

都在二分些啥。

我们首先注意到，如果我们钦定两个人先相遇，就相当于先把答案和这两个人距离的一半 chkmax，然后把这两个人交换，然后这两个人不用再相遇，区间拆成了两个独立的子区间。

如图所示。

![](https://s21.ax1x.com/2024/05/30/pk8SBqS.png)

我们考虑差分数组的变化：若一开始相邻两个人之间的距离依次为 $a,b,c$，则操作以后变为 $a+b$ 和 $b+c$，中间被隔开分成两个区间。

这就相当于把 $[1,n-1]$ 拆分成 $[1,p_1],[p_1,p_2],\cdots,[p_k,n-1]$（相邻两个区间恰好有一个公共元素），要求所有区间的和的最大值最小。

同时，除了第一个区间和最后一个区间可以只有 $2$ 个元素以外，其他区间都至少要有 $3$ 个元素。我们可以在前后补 $0$ ，这样所有区间都至少要有 $3$ 个元素。

同时，区间长度 $\ge5$ 可以拆分，所以一定不优。所以我们可以 DP，每次只需要考虑下一个区间的长度是 $3$ 还是 $4$。

时间复杂度为 $\mathcal{O}(n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 2e5 + 10;
int n, arr[_], brr[_], dp[_];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i < n; i++) {
        brr[i] = arr[i+1] - arr[i];
    }
    memset(dp, 0x3F, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (i >= 2) {
            dp[i] = min(dp[i], max(dp[i-2], brr[i-2] + brr[i-1] + brr[i]));
            if (i >= 3) {
                dp[i] = min(dp[i], max(dp[i-3], brr[i-3] + brr[i-2] + brr[i-1] + brr[i]));
            }
        }
    }
    cout << dp[n] / 2 << endl;
    return 0;
}
```

---

## 作者：allenchoi (赞：0)

### 科技：
二分，DP  
### 思路：  
首先二分答案 $x$。单调性显然，因为可以站着不动。  
考虑如何检验合法性。    
易想到每个人肯定都只有两种走法：  
1.先向右走直到和右边一个人相遇，在尽量向左走；  
2.先向左走直到和左边一个人相遇，在尽量向右走。  
设 $f_{i,0}$ 表示第 $i$ 个人在第一种情况下能先向右走多远，$f_{i,1}$ 表示第 $i$ 个人在第二种情况下最后能往右走多远。注意，$f_{i,0}$ 和 $f_{i,1}$ 都可能是负数。  
显然，$f_{1,0}=f_{1,1}=x$。  
接着，$i>1$ 时分类讨论转移：  
>#### 1.$f_{i-1,0}$ 转移到 $f_{i,0}$   
>条件：$f_{i-1,0}$ 可用且 $a_{i-1}+f_{i-1,0}\ge a_i-f_{i-1,0}$  
让 $i$ 与 $i-1$ 在 $i-1$ 要向左时再相遇，则相遇位置为 $a_i+f_{i-1,0}$，$i$ 向左的时间比 $i-1$ 向右的时间少 $f_{i-1,0}-(a_i-a_{i-1}-f_{i-1,0})=2f_{i-1,0}-a_i+a_{i-1}$。这些时间可以用来向右走一段距离再走回 $a_i$，所以 $f_{i,0}=\frac{2f_{i-1,0}-a_i+a_{i-1}}{2}$。 

>#### 2.$f_{i-1,1}$ 转移到 $f_{i,0}$   
>条件：$f_{i-1,1}$ 可用且 $a_{i-1}+f_{i-1,1}\ge a_i-x$  
让 $i$ 与 $i-1$ 在最后一刻，则相遇位置为 $a_i+f_{i-1,1}$，$i$ 要向左走 $a_i-a_{i-1}-f_{i-1,1}$，剩下 $x-a_i+a_{i-1}+f_{i-1,1}$ 的时间。这些时间可以用来向右走一段距离再走回 $a_i$，所以 $f_{i,0}=\frac{x-a_i+a_{i-1}+f_{i-1,1}}{2}$。  

>#### 3.$f_{i-1,0}$ 转移到 $f_{i,1}$   
>条件：$f_{i-1,0}$ 可用且 $a_{i-1}+f_{i-1,0}\ge a_i-f_{i-1,0}$  
让 $i$ 与 $i-1$ 相遇后马上向右，则相遇后再回到 $a_i$ 所需时间为 $2\times\frac{a_i-a_{i-1}}{2}=a_i-a_{i-1}$ ，剩下的时间 $x-a_i+a_{i-1}$ 都向右走，所以 $f_{i,1}=x-a_i+a_{i-1}$。  

>#### 4.$f_{i-1,1}$ 转移到 $f_{i,1}$   
>条件：$f_{i-1,1}$ 可用且 $a_{i-1}+f_{i-1,1}\ge a_i-x$  
让 $i$ 与 $i-1$ 相遇后马上向右，此时 $i$ 与 $i-1$ 应该一起向右，所以二者最后的位置应该是一样的，即 $a_{i-1}+f_{i-1,1}$，所以 $f_{i,1}=a_{i-1}+f_{i-1,1}-a_i$ 。  

如果存在某一个 $i(2\le i \le n)$ 使得四种情况都不能从 $i-1$ 转移到，那么就是 $x$ 太小了，非法；如果能顺利转移到 $n$，$x$ 就是合法的。  
### 代码：  
~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5,INF = -2122219135;
int n,a[N],f[N][2];
void upd(int x,int y,int v){f[x][y] = max(f[x][y],v);}
bool check(int x)
{
	memset(f,-127,sizeof(f));
	f[1][0] = f[1][1] = x;
	for(int i = 2;i <= n;i++)
	{
		if(f[i - 1][0] != INF && a[i - 1] + f[i - 1][0] >= a[i] - f[i - 1][0])
			upd(i,0,(2 * f[i - 1][0] - a[i] + a[i - 1]) / 2);
		if(f[i - 1][1] != INF && a[i - 1] + f[i - 1][1] >= a[i] - x)
			upd(i,0,(x - a[i] + a[i - 1] + f[i - 1][1]) / 2);
		if(f[i - 1][0] != INF && a[i - 1] + f[i - 1][0] >= a[i] - f[i - 1][0])
			upd(i,1,x - a[i] + a[i - 1]);
		if(f[i - 1][1] != INF && a[i - 1] + f[i - 1][1] >= a[i] - x)
			upd(i,1,f[i - 1][1] - a[i] + a[i - 1]);
		if(f[i][0] == INF && f[i][1] == INF) return false;
	}
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	int l = 0,r = a[n] - a[1],mid;
	while(r - l > 1)
	{
		mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%d\n",r);
	return 0;
}
~~~

---

## 作者：WerChange (赞：0)

提供二分与 DP 做法。

# Solution

## 题意

给出 $n (\le 2\times 10^5)$ 个单调递增偶整数 $a_i$，求最小的 $k$ 满足每一个 $i$ 都可以在 $k$ 时刻之前（含）与相邻的数相遇。每个单位时间可以移动一个单位距离。

## 思路

### 启发式思考

在想到正解之前，我们可以想想类正解。

显然，在时间一单位一单位过去的时候，一个元素如果愣着不动，肯定不是最优的策略——因为无论它去追随相邻的、或是去相遇相邻的，时间都可以尽可能更优。

所以我们看做元素是不断运动的。

如果它乱走，没有遇到任意一个相邻的元素的情况下，随便改变方向，好像也不优。所以我们也规定一个元素就只有两个阶段：第一、第二阶段——要么先左再右，要么先右再左。

想到这里，对我们有了些许启发。来看看下面这个能拿 80pts 的错解：

> 就考虑两种情况：
>
> 1. 奇（ji）左偶右：黑色表示第一阶段、红色表示第二阶段
>
> ![img](https://cdn.luogu.com.cn/upload/image_hosting/zf9ejjtt.png)
>
> 2. 奇（ji）右偶左：同上
>
> ![img](https://cdn.luogu.com.cn/upload/image_hosting/a1mwt3iq.png)
>
> 当然 $n$ 的奇偶也要考虑。

像这样，是不是以为可以直接 $O(n)$ 直接跑就解决了？

显然，这太天真了~~（像我一样）~~，提供一组 hack 数据：

#### input

```plaintext
10
12 12 24 26 56 70 98 124 124 178 
```

#### answer

```plaintext
34
```

#### output

```plaintext
36
```

至于模拟过程自己模拟吧，这是我能对出来的最小数据了。

[贴一个错误代码](https://www.luogu.com.cn/paste/088znuit)，可以自己对拍对数据。

### 正解

我们可以直接二分答案 $k$。

接下来考虑怎么扩缩范围。

设 $f(i,0)$ 表示元素 $i$ 先左走，调头后最多还可走多少步。

设 $f(i,1)$ 表示元素 $i$ 先右走，最多可以走多少步再掉头。

然后就是小学学过的相遇问题，自己在纸上画画就出来了，这里不做赘述。要是不会的话，可以私信。

方程不好整理，自己看代码吧。挺具象的。

### 代码

马蜂抽象就随便看看吧，溜了。

code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 2e5 + 5;

int n;
int a[MAXN];
int d[MAXN];
int f[MAXN][2];

bool check(int md) {
    memset(f, -1, sizeof(f));
    f[1][1] = md;
    for (int i = 2; i <= n; i++) {
        if (f[i - 1][1] != -1) {
            int k = f[i - 1][1];
            if (k - d[i] / 2 >= 0) {
                f[i][0] = max(f[i][0], md - d[i] / 2);
                f[i][1] = max(f[i][1], k - d[i] / 2);
            }
        }
        if (f[i - 1][0] != -1) {
            int k = f[i - 1][0];
            if (k - d[i] / 2 >= 0) {
                f[i][0] = max(f[i][0], k - d[i] / 2);
                f[i][1] = max(f[i][1], k - d[i] / 2);
            }
        }
    }
    return f[n][0] != -1 || f[n][1] != -1;
}

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 2; i <= n; i++) d[i] = a[i] - a[i - 1];
    int l = 1, r = 1e9, mid, ans = -1;
    while (l <= r) {
        mid = l + r >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

