# [JOI 2024 Final] 室温 / Room Temperature

## 题目描述

K 董事长负责调节高管们的房间的室温，他希望高管们能尽可能舒适地工作。

现在房间里有 $N$ 位高管。每位高管都有一个从 $1$ 到 $N$ 的编号。不穿外套时，高管 $i\ (1 \leq i \leq N)$ 的舒适温度是 $A_{i}$ 度。另外，每位高管每穿一件外套，舒适温度就会降低 $T$ 度。也就是说，高管 $i$ 如果穿了 $k$ 件外套，那么高管 $i$ 的舒适温度就是 $A_{i}-k T$ 度。

如果房间的温度是 $x$ 度，某位高管的舒适温度是 $y$ 度，那么这位高管的不舒适度就是 $|x-y|$。其中，$|t|$ 表示 $t$ 的绝对值。每位高管会根据房间的温度，穿上大于等于 $0$ 件合适的外套，使得不舒适度最小。

K 董事长把高管们的不舒适度的最大值称为房间的不舒适度，并决定要把房间的温度设定为使得房间的不舒适度最小的值。但是，设定的温度必须是整数。

给定高管和舒适温度的信息。编写一个程序，求出房间的不舒适度可能的最小值。

## 说明/提示

对于所有输入数据，满足：

- $2 \leq N \leq 5\times 10^5$
- $1 \leq T \leq 10^{9}$
- $1 \leq A_{i} \leq 10^{9}(1 \leq i \leq N)$

详细子任务附加限制及分值如下表所示。

|子任务|	附加限制|	分值|
|:-:|:-:|:-:|
|1|	$N=2$|	15|
|2|	$N \leq 3000, T=1$|	5|
|3|	$N \leq 3000, T \leq 2$|	30|
|4|	$N \leq 3000, T \leq 3000$|	35|
|5|	无附加限制	|15|

## 样例 #1

### 输入

```
2 4
19 24```

### 输出

```
1```

## 样例 #2

### 输入

```
3 1
21 19 23```

### 输出

```
0```

## 样例 #3

### 输入

```
6 8
24 22 21 25 29 17```

### 输出

```
2```

# 题解

## 作者：红尘万李 (赞：16)

# P10205 [JOI 2024 Final] 室温 题解
[题面传送门](https://www.luogu.com.cn/problem/P10205)

------------
## 题意概括
题目让我们求的是，对于一个内部任意某些元素可以减少正定值的数组 $a$，满足 $k=|a_i-t|(1≤i≤n)$ 的最大值最小，并输出这个最小的 $k$。$t$ 即为题目中的室温，可以根据需要任意修改。

------------
## 题目分析
由于每一位高管的舒适温度可以通过穿外套的方式减少，我们不妨对他们进行统一：让每位高管的舒适温度都处于 $[0,t]$ 之间。这里我们可以直接通过对 $a_i$ 取模来实现，很好理解。

接下来，我们要考虑把室温 $t$ 调到哪里才能使 $k$ 最小。首先，我们将统一好的舒适温度由小到大**排序**。接下来，**找到相邻两个高管间舒适温度相差的最大值**。注意，舒适温度最低的高管和舒适温度最高的高管也要进行比较，具体方法为将最低的舒适温度 $a_1$ 加上 $t$ 后再与 $a_n$ 相减，形成一个闭环。千万不能漏掉这里。

这时候肯定就有人要问了，为什么要算这么一个最大值呢？我们可以这样理解：如果我们要调整室温使房间的不舒适度最小，那我们肯定是去成全两个相邻舒适温度相差最大的，这样才能降低最大的 $k$，从而使得房间的 $k$ 最小。

那么，上述的效果如何实现呢？我们假设已经找到两个相差最大的舒适温度，分别为 $x$ 和 $y(x<y)$，那么差的最大值即为 $maxd=y-x$。因为高管们每次改变舒适温度的值是相同的，所以最终，房间内高管舒适温度的极差的最小值，就是 $x+t-y$。

最后，我们只需要把室温调到 $[y,x+t]$ 的中间就可以了。这时的 $k$ 是 $\frac{x+t-y}{2}$，即 $\frac{t-maxd}{2}$，**有可能是一个小数**，但题目中要我们调至整数。此时，不管是向上取整还是向下取整，我们不舒适度的最大值都是**前者**。原因是，如果调整室温偏向两个高管中的一个，使其不舒适度减小，那么室温离另一个高管的舒适温度就会更远，其不舒适度就会增大。而我们取的是不舒适度的最大值，所以对于有小数的情况，不舒适度的最大值都是向上取整，具体实现可参考下面的代码。

------------
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500002],t,maxd,k;//变量名如题意
int main()
{
    scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]%=t;//边输入边取模
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		maxd=max(maxd,a[i+1]-a[i]);
	maxd=max(maxd,a[1]+t-a[n]);//如题目分析，这里千万不能漏
	k=ceil((double(t-maxd))/2.0);//向上取整的函数，如果它本来就是整数就不变
	printf("%d",k);
	return 0;
}
```
记得，顶一下！

---

## 作者：Perta (赞：5)

考虑在房间温度为 $x$ 度时第 $i$ 位高管的最小不舒适度 $f_i(x)$。不难发现，当 $x>A_i$ 时，$f_i(x)=x-A_i$；否则 $f_i(x)=\min((A_i-x)\bmod T,T-(A_i-x)\bmod T)$。

由于 $\lvert x-A_i\rvert\geq\min(\lvert x-A_i\rvert\bmod T,T-\lvert x-A_i\rvert\bmod T)$，我们不妨将 $x$ 设为一个极小值。设 $y=\lvert x\rvert\bmod T$，则 $f_i(x)=\min(\lvert y-A_i\rvert\bmod T,T-\lvert y-A_i\rvert\bmod T)$（$x$ 足够小）。

$f_i(x)$ 可以看成在一个长为 $T$ 的环上，位置 $y$ 与位置 $A_i\bmod T$ 的距离。

将所有 $A_i\bmod T$ 的位置标记。设分界点 $mid=(y+\lfloor\frac{T}{2}\rfloor)\bmod T$，与其相邻的两个（也许只有一个）**标记位置**分别为 $t_1,t_2$，则 $\max f_i(x)=\max(dis(y,t_1),dis(y,t_2))$，其中 $dis(u,v)$ 表示环上 $u$ 与 $v$ 的距离。

给个图方便理解（蓝色的点为标记位置，即 $A_i\bmod T$）：

![](https://pic.imgdb.cn/item/65f994ef9f345e8d037aa4da.png)

可以发现，当 $mid$ 在圆弧 $t_1t_2$ 上时，取中点可以使 $\max f_i(x)$ 有最小值 $\lceil\frac{T-\mathop{t_1t_2}\limits^{\frown}}{2}\rceil$。所以直接找 $\max \mathop{t_1t_2}\limits^{\frown}$ 即可，注意要算优弧。

时间复杂度 $O(n\log n)$。

[Code](https://www.luogu.com.cn/paste/vbzvfl9k)

---

## 作者：feizhu_QWQ (赞：2)

这道题第一眼看上去十分的像二分，可找来找去都找不到单调性，所以放弃了二分。  
所以我们来分析一下这道题。  
首先，高管们可以通过换衣服降温，所以我们一开始就把高管们的适合温度对 $t$ 取余。  
接着我们可以画这么一张图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/l1f90e1u.png)  

那么此时的答案就是 $(a[5]-a[1]+1)/2$。   
你以为这道水黄就到此结束了，可还有更优答案！  

我们可以继续给温度最高的穿衣服，然后他就会变成适应度最低的，这样是有概率得到最佳答案的。  
所以我们可以给每个主管（除了最后一个外）轮流穿衣服，然后计算答案，就出来啦！  
代码：  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,minn=1e18;
int a[1000005];
int pre[1000005];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>t;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]%=t;//对温度进行取余
	sort(a+1,a+1+n);//排序
	int minn=(a[n]-a[1]+1)/2;//计算不额外穿衣服的答案
	for(int i=1;i<n;i++)//这里是从1到n-1哦
	{
		minn=min(minn,(a[i]+t-a[i+1]+1)/2);//计算答案
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：wangzhechun (赞：2)

### (づ｡◕‿‿◕｡)づP10205 [JOI 2024 Final] 室温 题解

[题目传送门](https://www.luogu.com.cn/problem/P10205)

[博客查看更佳](https://www.luogu.com.cn/article/11rs720c)

由题意可知，通过穿外套，高管的舒适温度就可以变为 $[0,1,\ldots,T-1]$ 范围内，即 $A_i = A_i \bmod T$。

然后对 $A$ 数组排序，根据题目中要求，设定一个温度，使得最大差值最小，取余之后 $A_i \in [0,1,\ldots,T-1]$。

通过观察样例3，答案并不是 $\frac{A_n-A_1+1}{2}$（向上取整，所以加 $1$ ），因为如果将 $[A_1,\ldots,A_i]$ 区间内的温度都加 $T$，即原数组变为 $[A_{i+1},\ldots,A_n,A_1+T,\ldots,A_i+T]$ 时，可能 $A_{i+1}$ 与 $A_i+T$ 差值更小。

那么我们就可以枚举 $i$，保留答案最小值，即 $ans=\min(\frac{A_i+T-A_{i+1}+1}{2})$，输出答案即可。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 1;
int n, t, ans, a[maxn];
int main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n >> t;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= t;                                     //读入并取模
    }

    sort(a + 1, a + n + 1);                            //对 a 数组排序
    ans = (a[n] - a[1] + 1) / 2;                       //向上取整

    for (int i = 1; i < n; i++)
        ans = min(ans, (a[i] + t - a[i + 1] + 1) / 2); //取答案最小值

    cout << ans;
    return 0;
}   //code by wangzhechun
```
然后我们就可以完美的AC这道题啦~\(≧▽≦)/~。

---

## 作者：_EternalRegrets_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/P10205)

### 题意描述：
>有 $n$ 个人，每个人都有一个喜欢的温度。同时，他们也可以穿外套使他们希望的温度发生变化。（每多穿一件，喜欢的温度降低 $t$ ）求所有人喜欢的温度与一个定值的差的最大值的最小值。

### Solution:
发现题目的温度可以在模 $t$ 的情况下解决。

显然，对于排序之后的序列，最佳温度是最小值和最大值的平均。

所以我们可以考虑将每个相邻两人组构造到最小值和最大值处（加 $t$ 即可）。

具体见代码。

### code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[500005];
signed main(){
    //freopen("temperature.in","r",stdin);
    //freopen("temperature.out","w",stdout);

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n,t; cin>>n>>t;

    for(register int i=1;i<=n;i++){
        cin>>a[i];
        a[i]%=t;
    }

    sort(a+1,a+1+n);

    int ans; ans=(a[n]-a[1]+1)/2;

    for(register int i=1;i<=n;i++){
        ans=min(ans,(a[i]+t-a[i+1]+1)/2);
    }

    cout<<ans;
    return 0;
}
```

---

## 作者：王逸辰 (赞：1)

# P10205 [JOI 2024 Final] 室温 题解
## 思路
首先，我们可以从题目中发现，每位高管都可无限叠加外套。

而且，题目中要求的是最小的不舒适度，而不是温度的具体值。

所以，我们可以不用管温度的具体大小，只需将各个高管的舒适度无限接近即可。

易知，这个最小的不舒适度的范围及在 $1$ 至 $T$ 间。

综上，结果便出来了。

我们可以在输入时直接模 $T$，然后在已经是最小的不舒适度的前提下，从小到大找出最大的不舒适度，即比较相邻相邻两数的最大值，即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,ans,a[500001];
int main(){
    cin>>n>>t;
    for(int i=1; i<=n; i++)
        cin>>a[i],a[i]%=t;
    sort(a+1,a+n+1);
	ans=a[1]+t-a[n];
    for(int i=2; i<=n; i++) {
        ans=max(ans,a[i]-a[i-1]);
    }
    if(t==ans)
        puts("0");
    else
        cout<<(t-ans-1)/2+1;
    return 0;
}
```

---

## 作者：danb123 (赞：1)

## 题目大意
求一个数，这个数对给定数组的每一个数的绝对值之和最小，并且数组中的每一个数可以减去若干个固定值。
## 题目思路
在这道题目里，我们不管他穿多少件外套，它的最小值是它模上固定值，这样每个数的范围就在零到固定值之间。然后我们再把它们排序，求最大的每两个数之间的差，然后输出固定值减去刚才求的最大值减一再除以二再加一。
## 正确代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,t,a[1000001];
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>t;
	for(ll i=1;i<=n;i++)cin>>a[i],a[i]%=t;
	sort(a+1,a+n+1);
	for(ll i=1;i<n;i++)m=max(ma,a[i+1]-a[i]);
	m=max(m,a[1]+t-a[n]);
	t==m?cout<<0<<endl:cout<<(t-m-1)/2+1<<endl;
	return 0;
}
```

---

## 作者：dinghongsen (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P10205)

### 解题思路

依题意，第 $i$ 位高管的舒适温度是 $a_{i} \bmod t$，然后排序，一头一尾即为最值，再依次遍历 $t + a_{i-1} - a_{i}$ 最小值，即房间的不舒适度的最小值，最后输出。
### code
```cpp
# include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, t, a[N];
int main() {
    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= t;
    }
    sort(a + 1, a + 1 + n);
    int ret = ceil(1.0 * (a[n] - a[1]) / 2);
    for (int i = 1; i <= n; i++) {
        ret = min(ret, (int) ceil(1.0 * (a[i - 1] - a[i] + t) / 2));
    }
    cout << ret;
    return 0;
}
```

---

## 作者：JYX0924 (赞：0)

通过观察可以发现，对于两个数 $k_{1}t+b$ 和 $k_{2}t+b$。它们对于答案的贡献是一样的，因为它们都可以通过减去若干个 $t$ 变成一样的数。

所以，我们可以对于每一个 $a_{i}$ 先让它对 $t$ 取模，然后把它从小到大进行排序。最后，枚举每一个断点计算答案。即：$ans=\min\{ans,(a_{i+1}-a_{i}+t+1)\div2\}$。

下面是我的 AC 代码。


```c
#include<bits/stdc++.h>
#define ll long long 
#define maxn 500005
using namespace std;
ll n,t,a[maxn],ans;
vector<ll> q;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>t; for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) q.push_back(a[i]%t);
	sort(q.begin(),q.end(),greater<ll>()); ll zx=q.back(),len=q.size();
	ans=(q[0]-q[len-1])/2+(q[0]-q[len-1])%2;
	for(int i=0;i<len-1;i++)
	{
		q[i]-=t; ans=min(ans,(q[i+1]-q[i]+1)/2);
	}
	cout<<ans;
	return 0;
}
```
谢谢大家！！！

---

## 作者：ac_lxy (赞：0)

### 题解思路
为了求出房间的不舒适度可能的最小值，我们可以先将每位高管的舒适温度计算出来，并按照从小到大的顺序进行排序。然后，我们找到相邻两位高管的舒适温度之差的最大值，并考虑首尾两位高管的情况，选择其中的最大值作为房间的不舒适度。最后，我们通过将房间的不舒适度减去 $1$ 后除以 $2$ 并加上 $1$，得到房间的不舒适度可能的最小值。

### 代码实现
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 5e5 + 10;

int n, T, answer;
int a[MAX_N];

int readInt() {
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}

void maximize(int &x, int y) {
    x = max(x, y);
}

int distance(int x, int y) {
    return min(abs(x - y), T - abs(x - y));
}

int main() {
    n = readInt();
    T = readInt();
    for (int i = 1; i <= n; i++)
        a[i] = readInt(), a[i] %= T;
    sort(a + 1, a + n + 1);
    for (int i = 1; i < n; i++) 
        maximize(answer, a[i + 1] - a[i]);
    maximize(answer, a[1] + T - a[n]);
    if (T == answer)
        cout << "0" << endl;
    else
        cout << (T - answer - 1) / 2 + 1 << endl;
    return 0;
}
```

---

