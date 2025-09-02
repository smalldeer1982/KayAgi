# [NOISG 2017] Best Places / 最佳选址

## 题目背景

译自 [NOISG 2017 A.Best Places](https://github.com/noisg/sg_noi_archive/tree/master/2017/bestplace)。

## 题目描述

IOI 2020 将在新加坡举行！举办这样的国际赛事，选择举办地自然成了十分重要的事。

现在，组委会拿到了一份选手住址名单，共有 $N$ 位选手，他们所在的城市可以看作一个坐标系，第 $i$ 位选手住在 $(X_i,Y_i)$。

为了选手们方便参加比赛，组委会想要选择一个点 $(X,Y)$，使得所有 $|X-X_i|+|Y-Y_i|$ 之和最小。

请你输出这个 $(X,Y)$。如果有多种可能的答案，输出任意一个即可。

**注意：最终答案 $(X,Y)$ 可能与某个 $(X_i,Y_i)$ 相同。一个 $(X_i,Y_i)$ 点上也可能不止一位选手。你应该认为住在同一个点的选手分别单独去赛场，而不是将他们视为同一个人。**

## 说明/提示

### 【样例解释】

对于样例一，不难发现 $(1,0),(2,0),(4,0)$ 也是正确的输出。无论选择 $(1,0),(2,0),(3,0)$ 还是 $(4,0)$，都有 $\sum\limits_{i=1}^N(|X-X_i|+|Y-Y_i|)=3$。可以证明没有 $(X,Y)$ 可以使 $|X-X_i|+|Y-Y_i|$ 之和更小。

对于样例二，$(5,0),(6,0)$ 也是正确的输出。

对于样例三，可以证明这是唯一正确的输出。

### 【数据范围】

**本题采用 $\text{Subtask}$ 捆绑测试。**

|$\text{Subtask}$|分值|$N$|$X_i,Y_i$|
|:-:|:-:|:-:|:-:|
|$1$|$3$|$N=2$|$0\le X_i,Y_i\le10^9$|
|$2$|$20$|$2\le N\le1000$|$0\le X_i\le1000,Y_i=0$
|$3$|$28$|$2\le N\le10^6$|$0 \le X_i\le10^9,Y_i=0$|
|$4$|$13$|$2\le N\le100$|$0\le X_i,Y_i\le100$|
|$5$|$17$|$2\le N\le1000$|$0\le X_i,Y_i\le10^9$|
|$6$|$19$|$2\le N\le10^6$|$0\le X_i,Y_i\le10^9$|

对于 $100\%$ 的数据，$2\le N\le10^6$，$0\le X_i,Y_i\le10^9$。

## 样例 #1

### 输入

```
2
1 0
4 0```

### 输出

```
3 0```

## 样例 #2

### 输入

```
6
1 0
3 0
5 0
7 0
9 0
11 0
```

### 输出

```
7 0```

## 样例 #3

### 输入

```
9
1 16
3 12
5 6
7 10
9 8
11 4
13 14
15 2
17 18
```

### 输出

```
9 10```

# 题解

## 作者：DYYqwq (赞：6)

显然曼哈顿距离之和的 $x$ 和 $y$ 是割裂的，可以分开考虑。

于是问题转化成给你一堆数，让你找一个数使得 $\sum |a[i]-x|$ 最小。

我们注意到，如果只有两个数，那么 $x$ 取两数之间即可；如果有三个数，那么 $x$ 取第二大的数即可；如果有四个数，那么 $x$ 取第二、第三大的数之间即可。

由此注意到，若总数是奇数，必然取在中位数，反之，取中间两数之间，当然，可以取中间两数中的任何一个数。

于是取第 $\lfloor \frac{n-1}{2} \rfloor+1$ 个数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , x[1000010] , y[1000010]; 
int main()
{
    scanf("%d" , &n);
    for(int i = 1 ; i <= n ; i ++) scanf("%d%d" , &x[i] , &y[i]);
    sort(x + 1 , x + n + 1) , sort(y + 1 , y + n + 1);
    printf("%d %d" , x[(n - 1) / 2 + 1] , y[(n - 1) / 2 + 1]);
    return 0;
}
```

---

## 作者：huhengrui2013 (赞：2)

### 题解：P13080 [NOISG 2017] Best Places / 最佳选址

[传送门](https://www.luogu.com.cn/problem/P13080)

### 思路：

对于一维数轴上的坐标，使所有点到该点的距离之和最小的点是该点集的中位数。因此，最优 $X$ 坐标是所有选手 $X_i$ 的中位数，最优 $Y$ 坐标是所有选手 $Y_i$ 的中位数。

求中位数时，排序，再取中间数即可。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int x[N],y[N],n;
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    sort(x+1,x+1+n);//排序求中位数
    sort(y+1,y+1+n);
    cout<<x[n/2+1]<<" "<<y[n/2+1];//下标从一开始，所以要+1
    return 0;
}
```

---

## 作者：Clouds_dream (赞：1)

一道水题。

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13080)

### 题目分析
我们需要找到一个点，使得所有选手到这个点的曼哈顿距离之和最小。为了最小化这个总和，$x$ 和 $y$ 应该分别取所有 $x_i$ 和 $y_i$ 的中位数，这是因为中位数在绝对偏差最小化问题中是最优解。

### 注意
- 当 $n$ 为偶数时，选择中间两个数中的任意一个都可以。
- 由于奇数被整除时会向下取整，所以要加 1。

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e6+10, M = 1e8 + 10;

int n;
int xz[N],yz[N];//每个点的坐标

signed main()
{
	fst
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>xz[i]>>yz[i];
	}
	sort(xz+1,xz+n+1);//排序方便找中位数
	sort(yz+1,yz+n+1);
	int mx,my;
	if(n%2==0)mx=xz[n/2],my=yz[n/2];
	else mx=xz[n/2+1],my=yz[n/2+1];
	cout<<mx<<' '<<my;
	return 0;
}
```

---

## 作者：M1__ (赞：0)

# 题解：P13080 [NOISG 2017] Best Places / 最佳选址

[Link](https://www.luogu.com.cn/problem/P13080)

## 形式化题意

给出 $N$ 个选手的坐标，要求找到一个坐标 $(X,Y)$，使其能最小化 $\sum|X-X_i|$ 和 $\sum|Y-Y_i|$。也就是使所有选手到该点的曼哈顿距离之和最小。

## 题目思路
因为曼哈顿距离在 $X$ 和 $Y$ 方向上是独立的，所以可以分别处理横坐标和纵坐标。

因此问题转化为：在一组数据中，找到一个数使得这个数与其他数的绝对差之和最小。显然这个数是中位数。所以只需求 $N$ 个 $X$ 的中位数与 $N$ 个 $Y$ 的中位数即可。

让我们回忆一下如何求中位数：

- $M=X_{\frac{N+1}{2}}$，此时 $N \bmod 2 \neq 0$。
- $M=\frac{X_{\frac{N}{2}}+X_{\frac{N}{2}+1}}{2}$，此时 $N \bmod 2 = 0$。

## 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10;
ll n,x[N],y[N],ansx,ansy; 
int main() {
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    sort(x+1,x+n+1);
    sort(y+1,y+n+1);
    if (n%2==1){
        ansx=x[(n+1)/2];
        ansy=y[(n+1)/2];
    } 
    else{
        ansx=(x[n/2]+x[n/2+1]+1)/2;
        ansy=(y[n/2]+y[n/2+1]+1)/2;
    }
    cout<<ansx<<" "<<ansy;
    return 0;
}
```

---

## 作者：goIdie (赞：0)

## 思路

要使 $\sum_{i=1}^{n} \lvert X-X_i\rvert+\lvert Y-Y_i\rvert$ 最小，只需分别使 $\sum_{i=1}^{n} \lvert X-X_i\rvert$ 和 $\sum_{i=1}^{n} \lvert Y-Y_i\rvert$ 最小。

学过中位数的应该都知道，中位数有一个性质：所有数与中位数的绝对差之和最小。也就是上面的式子。[证明在这里](https://zhuanlan.zhihu.com/p/73139689)

所以，我们只需将 $X$ 数组和 $Y$ 数组排序后分别输出中位数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[1000001],y[1000001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
    sort(x+1,x+1+n);
    sort(y+1,y+1+n);
	cout<<x[n/2+1]<<" "<<y[n/2+1];//因为我的循环下标起始为1，所以中位数下标为 n/2+1
}
```

---

## 作者：Vct14 (赞：0)

由于求的是曼哈顿距离，而且没有要求必须选择某个选手的住址，因此本题实际上可以拆成两个[货仓选址](https://www.luogu.com.cn/problem/P10452)。答案是所有横坐标的中位数和所有纵坐标的中位数。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+2;
int x[N],y[N];

int main(){
	int n;cin>>n;
	for(int i=0; i<n; i++) cin>>x[i]>>y[i];
	sort(x,x+n);sort(y,y+n);
	cout<<x[n/2]<<" "<<y[n/2];
	return 0;
}
```

---

## 作者：Doraeman (赞：0)

## 结论
当所有点排序后，中位数位置能保证两侧点数量平衡，从而使得移动选址点时总距离变化最小。

即：当数轴上有 $N$ 个点时，第 $\lfloor\frac{N+1}{2}\rfloor$ 个点到这 $N$ 个点的距离最小。

## 证明
设数轴上有 $N$ 个点，坐标为 $x_1\leq x_2\leq\dots \leq x_n$，需证明选择第 $\lfloor\frac{n+1}{2}\rfloor$ 个点（即中位数点）时，到所有点的距离之和最小。  
记选中的点为 $x_m$，距离和为 $S(m)=\sum_{i=1}^n |x_i - x_m|$，目标是证明当 $m=\lfloor\frac{n+1}{2} \rfloor$ 时，$S(m)$ 取得最小值。
### 分类讨论
#### $N$ 为奇数
设 $N=2k-1(m\in\mathbb{N}^*)$。  
此时中位数为第 $m$ 个点 $x_m$，需证明对任意 $k\neq m$，有 $S(m) < S(k)$。  
- 若 $k<m$，取 $k = m-t(t\geq1)$，则：  
  $$S(m-t) - S(m) = \sum_{i=1}^{m-t} (x_m - x_i) - \sum_{i=m-t+1}^{m} (x_m - x_i) + \sum_{i=m+1}^{2m-1} (x_i - x_m) - \sum_{i=m+1}^{2m-1} (x_i - x_{m-t})
  $$
  化简后，前两项对应左侧 $m-t$ 个点到 $ x_m $ 和 $ x_{m-t} $ 的距离差，后两项对应右侧 $ m-1 $ 个点的距离差。由于左侧有 $ m-t $ 个点，右侧有 $ m-1 $ 个点，且 $ m-t < m-1 $（因 $ t \geq 1 $），则：  
  $$
  S(m-t) - S(m) = t \cdot (x_m - x_{m-t}) + (m-1 - (m-t)) \cdot (x_{m-t} - x_m) = t \cdot \Delta - (t-1) \cdot \Delta = \Delta > 0
  $$  
  其中 $ \Delta = x_m - x_{m-t} \geq 0 $，故 $ S(m-t) > S(m) $。  
- 若 $ k > m $，同理可证 $ S(m+t) > S(m) $，即中位数点 $ x_m $ 使距离和最小。

#### $N$ 为偶数
设 $N = 2m(m \in \mathbb{N}^* )$  
此时中位数可以是第 $ m $ 或 $ m+1 $ 个点，需证明这两个点的距离和相等且为最小值。  
- 取 $ k = m $ 和 $ k = m+1 $，计算距离和：  
  $$
  S(m) = \sum_{i=1}^m (x_m - x_i) + \sum_{i=m+1}^{2m} (x_i - x_m)
  $$  
  $$
  S(m+1) = \sum_{i=1}^m (x_{m+1} - x_i) + \sum_{i=m+1}^{2m} (x_i - x_{m+1})
  $$  
  两式相减：  
  $$
  S(m+1) - S(m) = m \cdot (x_{m+1} - x_m) - m \cdot (x_{m+1} - x_m) = 0
  $$  
  故 $ S(m) = S(m+1) $。  
- 对任意 $ k < m $ 或 $ k > m+1 $，类似奇数情况可证 $ S(k) > S(m) $，即中间两个点的距离和均为最小值。


### 数据验证
- **数据：$ N=5 $（奇数）**  
  点坐标为 $ \{1, 2, 4, 5, 7\} $，中位数为第 $3$ 个点 $ x_3=4 $，距离和为：  
  $$
  |1-4| + |2-4| + |4-4| + |5-4| + |7-4| = 3+2+0+1+3=9
  $$  
  若选 $ x_2=2 $，距离和为 $ 1+0+2+3+5=11 > 9 $，同理验证其它点，可得中位数最优。  
- **数据：$ N=4 $（偶数）**  
  点坐标为 $ \{1, 3, 5, 7\} $，中位数为第 2、3 个点 $ x_2=3 $ 和 $ x_3=5 $，距离和分别为：  
  $$
  S(2)=|1-3|+|3-3|+|5-3|+|7-3|=2+0+2+4=8
  $$  
  $$
  S(3)=|1-5|+|3-5|+|5-5|+|7-5|=4+2+0+2=8
  $$  
  均为最小值，且选其他点时距离和更大（如选 $ x_1=1 $ 时和为 $12$）。
  
## 结论应用
无妨将每个点的 $x$ 坐标和 $y$ 坐标分开计算。

考虑 $x$ 坐标时，认为所有点都在同一条数轴上，只是 $x$ 坐标不同，取其中位数 $x_{ans}$。  
同理，考虑 $y$ 坐标时，认为所有点都在同一条数轴上，只是 $y$ 坐标不同，取其中位数 $y_{ans}$。

最后直接输出坐标 $(x_{ans},y_{ans})$ 就是答案了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+5;

int n, x[N], y[N];

int main(){
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> x[i] >> y[i];

    sort(x + 1, x + n + 1);
    sort(y + 1, y + n + 1);

    int mid = (n + 1) / 2;
    printf("%d %d",x[mid],y[mid]);
}
```

---

## 作者：Lagrange_NoAria (赞：0)

## 题目部分

### 题意简化

给你多个点的坐标，找出一个点，这个点到其他点的曼哈顿距离之和最小。

### 小小的分析

曼哈顿距离具有独分性，即在 $x$ 与 $y$ 方向独立。所以 $X_{med}$ 和 $Y_{med}$ 可最小化 $\sum |X-X_i|+|Y-Y_i|$。

#### 算法实现

这道题目仅需求这个点的坐标，所以我们可以建两个数组，分别输出这两个数组的中位数。

## 代码区

总结：输入、排序、取中位数。


```cpp
#include<bits/stdc++.h>
using namespace std;
int x[1000005],y[1000005];
int main(){
    int n;
    cin>>n;
    for(int i = 1; i <= n; i++){
        cin>>x[i]>>y[i];
    }
    sort(x+1,x+n+1);sort(y+1,y+n+1);
    if(n % 2 == 1) cout<<x[(n+1)/2]<<" "<<y[(n+1)/2];
    else cout<<x[n/2]<<" "<<y[n/2];
    return 0;
}
```

---

## 作者：_fallen_leaves_ (赞：0)

[P13080 [NOISG 2017] Best Places / 最佳选址](https://www.luogu.com.cn/problem/P13080)

## 题意
给出 $n$ 个人的坐标，记作标为 $(X_i,Y_i)$ ，选择一个点，记坐标为 $(X,Y)$，使所有人的 $|X-X_i|+|Y-Y_i|$ 和最小。

## 思路
分别考虑 $x$ 轴与 $y$ 轴，我们分别把 $x$ 轴与 $y$ 轴从小到大排序，取 $x$ 轴与 $y$ 轴最中间的数，也就是我们的答案，这样可以使所有人的路程和最短。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000005],b[1000005],s,s2;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	cout<<a[n/2+1]<<" "<<b[n/2+1];
	return 0;
}

```

---

