# Points and Minimum Distance

## 题目描述

You are given a sequence of integers $ a $ of length $ 2n $ . You have to split these $ 2n $ integers into $ n $ pairs; each pair will represent the coordinates of a point on a plane. Each number from the sequence $ a $ should become the $ x $ or $ y $ coordinate of exactly one point. Note that some points can be equal.

After the points are formed, you have to choose a path $ s $ that starts from one of these points, ends at one of these points, and visits all $ n $ points at least once.

The length of path $ s $ is the sum of distances between all adjacent points on the path. In this problem, the distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is defined as $ |x_1-x_2| + |y_1-y_2| $ .

Your task is to form $ n $ points and choose a path $ s $ in such a way that the length of path $ s $ is minimized.

## 说明/提示

In the first testcase, for instance, you can form points $ (10, 1) $ and $ (15, 5) $ and start the path $ s $ from the first point and end it at the second point. Then the length of the path will be $ |10 - 15| + |1 - 5| = 5 + 4 = 9 $ .

In the second testcase, you can form points $ (20, 20) $ , $ (10, 30) $ , and $ (10, 30) $ , and visit them in that exact order. Then the length of the path will be $ |20 - 10| + |20 - 30| + |10 - 10| + |30 - 30| = 10 + 10 + 0 + 0 = 20 $ .

## 样例 #1

### 输入

```
2
2
15 1 10 5
3
10 30 20 20 30 10```

### 输出

```
9
10 1
15 5
20
20 20
10 30
10 30```

# 题解

## 作者：DFbd (赞：3)

## 思路

要让总路程最小，就要让路径上相邻两点的距离小。而本题中，两点的距离是曼哈顿距离，所以问题就变成了：把 $2n$ 个点分成两组，每组的相邻两数的差最小。

这时就能想到排序，前 $n$ 个分一组，后 $n$ 个分一组，把相邻两数之差都加起来，就是最小总路程了。

路径就是两组中的第一个数为第一个点，第二个数为第二个点，以此类推。

## 代码
```
#include <bits/stdc++.h>
using namespace std;
int t, n, a[205], ans;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= 2 * n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + 2 * n + 1);//排序
    ans = 0;
    for (int i = 1; i < n; i++) {
      ans += a[i + 1] - a[i];//求前一部分的相邻两数之差
    }
    for (int i = n + 1; i < 2 * n; i++) {
      ans += a[i + 1] - a[i];//求后一部分的相邻两数之差
    }
    cout << ans << "\n";
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " " << a[i + n] << "\n";//输出路径
    }
  }
  return 0;
}
```

---

## 作者：xinruian (赞：2)

### **题意简述**

给你 $2n$ 个正整数，你需要将其两两配对，组合成 $n$ 个点的坐标  $(x,y)$ ,使得从某一点出发遍历所有点所经过的距离最短

### **解析**

- 在坐标系里从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ 时，当 $x$ 的变化量是沿着 $\overrightarrow{x2-x1}$ 方向，$y$ 的变化量是沿着 $\overrightarrow{y2-y1}$ 方向时走的距离最小（比如说从 $(1,2)$ 走到 $(3,4)$，那么每一步的 $\Delta x >= 0, \Delta y >= 0$），值为 $ \left| x_1 - x_2 \right| + \left| y_1 - y_2 \right|$ 。

- 若 $x_1,x_2,...,x_n$ 和 $y_1,y_2,...,y_n$ 都是单调序列，此时距离为 $ \left| x_1 - x_n \right| + \left| y_1 - y_n \right|$。那么问题就转换为把 $2n$ 个正整数转换为两组单调的序列 $x_1,x_2,...,x_n$ 和 $y_1,y_2,...,y_n$，使得 $ \left| x_1 - x_n \right| + \left| y_1 - y_n \right|$ 最小。
- 把所有整数排序，前n个数作为横坐标，后n个作为纵坐标，这样答案最小

(第一次独立写题解，希望大家多多提建议)

### **代码**


```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int a[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= 2 * n; i ++)
        cin >> a[i];
    sort(a + 1, a + 1 + 2 * n);
    int tmp = n;
    int ans = 0;
    for (int i = 2; i <= n; i ++)
        ans += a[i] - a[i-1] + a[tmp + i] - a[tmp+i-1];
    cout << ans << endl;

    for (int i = 1; i <= n; i ++)
        cout << a[i] << ' ' << a[tmp + i] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t --)
        solve();

    return 0;
}
```





---

## 作者：Mo默Sh笙 (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF1895B)

------------

首先注意到最终求的是曼哈顿距离，所以让点的横纵坐标分别单调可以使路程，此时的总路程等于 $ \lvert x_{1}-x_{n} \rvert + \lvert y_{1}-y_{n} \rvert $。

考虑如何让这个值最小，将这个问题转变为将序列分成长度相同的两组使得极值和最小。很显然，按排序后的中点作划分即可得到。

所以将序列排序一下，前一半作为横坐标，后一半作为纵坐标即可。

------------

$ \texttt{Code}$：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define db double
#define il inline
#define re register
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
//#define int ll
#define pii pair<int,int>
#define mp make_pair
#define F(i,a,b) for(re int (i)=(a);(i)<=(b);(i)++)
#define DF(i,a,b) for(re int (i)=(a);(i)>=(b);(i)--)
#define G(i,u) for(re int (i)=head[u];(i);(i)=nxt[(i)])
inline ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}return x*f;}
const int N=210;
int n;
int a[N];
signed main()
{
	int T=read();
	while(T--)
	{
		n=read();
		F(i,1,n+n) a[i]=read();
		sort(a+1,a+n+n+1);
		printf("%d\n",abs(a[1]-a[n])+abs(a[n+1]-a[n+n]));
		F(i,1,n) printf("%d %d\n",a[i],a[i+n]);
	}
	return 0;
}
```



---

## 作者：wuyin331 (赞：1)

# 题解

因为 $ (x_1, y_1) $ 之间 $ (x_2, y_2) $ 的距离被定义为 $ |x_1-x_2| + |y_1-y_2|$。我们假设先对 $x$ 坐标考虑，将数组 $a$ 排序，假设数组  $a$ 的元素有 $\{1,2,4,6,8,10\}$，我们则需要选择 $3$ 个元素，假设我们选择 $x$ 坐标分别为 $\{1,2,6\}$，那么 $y$ 坐标为 $\{4,8,10\}$，发现有重复的区间 $[4,6]$ 被计算，可以想到如果能分为两个不重复的区间，没有额外的答案被计算，结果为最小的。

那么如何将分成两个不重复的区间呢，明显可以想到只要分别选择排序后的数组 $a$ 的前 $n$ 个为 $x$ 坐标，则剩下的为 $y$ 坐标，没有重复的区间，为最优的答案。

# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<climits>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<cstring>
#include<unordered_map>
#include<unordered_set>
#include<cmath>
#include<numeric>
#define int long long
using namespace std;
int t,n,m,k,q,num,nums[205];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=2*n;i++) cin>>nums[i];
		sort(nums+1,nums+1+2*n);
		vector<int>x,y;
		int ans=0;
		for(int i=2;i<=n;i++) ans+=nums[i]-nums[i-1];
		for(int i=n+2;i<=2*n;i++) ans+=nums[i]-nums[i-1];
		for(int i=1;i<=n;i++) x.emplace_back(nums[i]);
		for(int i=n+1;i<=2*n;i++) y.emplace_back(nums[i]);
		cout<<ans<<"\n";
		for(int i=0;i<n;i++){
			cout<<x[i]<<" "<<y[i]<<'\n';
		}
	}
	return 0;
}
```



---

## 作者：UncleSam_Died (赞：1)

### 题目大意
已知有 $2n$ 个数，第 $i$ 个为 $a_i$，请你把这 $2n$ 个数划分成两组，每组 $n$ 个数，分别作为 $n$ 个点的横纵坐标，已知两个点 $(x_1,y_1)$ 和 $(x_2,y_2)$ 之间的距离为 $\left | x_1-x_2 \right|+\left| y_1-y_2 \right|$，请你找到一条路径经过所有的点，并最小化路径的长度。

### 解题思路
首先，我们对 $a$ 数组从小到大排序，把前 $n$ 个数作为 $x$、后 $n$ 个数作为 $y$，然后计算输出即可。

### 正确性证明
由路径长度的计算方式，易得当一条路径 $x$ 和 $y$ 均具有单调性时，路径长度最短。对于 $x$ 中最小的数 $x_{min}$ 和最大的数 $x_{max}$，显然，不管怎样，必然存在路径上的某一段横向长度为 $x_{max}-x_{min}$，显然此时直接从 $x_{min}$ 走到 $x_{max}$ 是最优的，纵向同理。综上，使得所有点的 $x$ 和 $y$ 坐标具有单调性的解法是最优的。那么，接下来需要考虑如何分配 $x$ 和 $y$。因为此时 $x$ 和 $y$ 需要具有单调性，那么总的路径长度为 $x_{max}-x_{min}+y_{max}-y_{min}$。设 $A$ 和 $B$ 为可能的 $x_{max}$ 和 $y_{min}$ 的值，其中 $A<B$。

当 $x_{max}=A$ 且 $y_{min}=B$ 时，总路径长度 $s_1=A-x_{min}+y_{max}-B$；当 $x_{max}=B$ 且 $y_{min}=A$ 时，总路径长度 $s_2=B-x_{min}+y_{max}-A$。此时有 $s_2-s_1=B-A+B-A=2(B-A)$，由 $B>A$ 知，$B-A>0$，所以 $s_2>s_1$，因此 $s_1$ 为更优解。综上，$x_{max}<y_{min}$ 时为最优解，即按照上面所讲的方式分配。

### AC 代码
```cpp
#include<stdio.h>
#include<math.h>
#include<algorithm>
#define N 205
int n,a[N];
int x[N],y[N];
inline void work(){
	scanf("%d",&n);
	for(register int i=1;i<=n<<1;++i)
		scanf("%d",&a[i]);
	std::sort(a+1,a+2*n+1);int ans=0;
	for(register int i=1;i<=n;++i)
		x[i]=a[i],y[i]=a[i+n];
	for(register int i=1;i<n;++i)
		ans+=x[i+1]-x[i]+y[i+1]-y[i];
	printf("%d\n",ans);
	for(register int i=1;i<=n;++i)
		printf("%d %d\n",x[i],y[i]);
}
signed main(){
	int T;scanf("%d",&T);
	while(T--) work();
} 
```


---

## 作者：wanghaoran00 (赞：1)

### 思路
贪心，题中需求出曼哈顿距离（即 $ \lvert x1-x2 \rvert + \lvert y1-y2\rvert$）最短，设 $a_{1} \le a_{2} \le a_{3} \le a_{4} $，其中曼哈顿距离为其中两数之和减去其他两数，易证 $a_{1}+a_{4}-a_{2}-a_{3} $ 时最小，此时即满足排序后分为两个长度为 $n$ 的递增序列依次相减。

ACcode
```
#include<bits/stdc++.h>
using namespace std;
void read(int &p){
    p=0;
    int k=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-'){
            k=-1;
        }
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        p=p*10+c-'0';
        c=getchar();
    }
    p*=k;
    return;
}
int T,n,a[205],b[205],ans;
signed main(){
    read(T);
    while(T--){
        read(n);
        ans=0;
        for(int i=1;i<=n*2;i++){
            read(a[i]);
        }
        sort(a+1,a+1+n*2);
        for(int i=2;i<=n;i++){
            ans+=abs(a[i]-a[i-1]);
        }
        for(int i=n+2;i<=n*2;i++){
            ans+=abs(a[i]-a[i-1]);
        }
        printf("%d\n",ans);
        for(int i=1;i<=2*n;i++){
            if(i>n){
                b[i-n]=a[i];
            }
        }
        for(int i=1;i<=n;i++){
            printf("%d %d\n",a[i],b[i]);
        }
    }
    return 0;
}

```

---

## 作者：Leeb (赞：0)

### 题意简述

给定一个长度为 $2n$ 的序列 $a$，你需要将 $a$ 中的数组成 $n$ 个坐标 $(x_i,y_i)$，并使这些坐标点之间的曼哈顿距离之和最小。

### 解题思路

首先，两个点 $(x1,y1)$ 和 $(x2, y2)$ 之间的曼哈顿距离为 $|x1-x2|+|y1-y2|$。

很容易想到，先将 $a$ 序列升序排序，然后将其分成长度为 $n$ 的两段，前一段作为每个点的横坐标，后一段作为每个点的纵坐标。

然后直接按照曼哈顿距离公式计算即可。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long
using namespace std;
int n, x, a[N];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline void init() {
    n = x = in();
    n <<= 1;
    for (int i = 1; i <= n; ++i) a[i] = in();
    sort(a + 1, a + 1 + n);
}
inline void work() {
    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        if (i == x + 1) continue;
        ans += a[i] - a[i - 1];
    }
    printf("%d\n", ans);
    for (int i = 1; i <= x; ++i)
        printf("%d %d\n", a[i], a[x + i]);
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = in();
    while (t--) {
        init();
        work();
    }
    return 0;
}
```



---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1895B)

设序列 $a$ 经过某一安排后所有在 $x$ 坐标上的元素排序列 $b$ 的前 $n$ 个，在 $y$ 上的排 $b$ 的后 $n$ 个。

那么安排点的坐标产生的最小的路径就是先将 $b$ 的前 $n$ 个单独从小到大排一次序，后 $n$ 个从小到大排一次序，然后计算 $\sum_{i=2}^{n} b_i-b_{i-1}+\sum_{i=n+2}^{2\times n} b_i-b_{i-1}$ 就行了。

因为最小的路径 $x$ 轴和 $y$ 轴一定有序，才不会绕路导致路径增长，那么就让所有安排在 $x$ 上的和安排在 $y$ 上的排序，并将排序后相同位置的组成一个坐标，这样就保证有序了。

接下来考虑将 $\sum_{i=2}^{n} b_i-b_{i-1}+\sum_{i=n+2}^{2\times n} b_i-b_{i-1}$ 最小化。最小化的方法是让 $b$ 数组为 $a$ 数组从小到大排列后的序列。那么此时我们可以保证 $b_1\le b_2\le ......\le b_{2\times n}$。但是如果这个序列不是从头到尾都有序的，那么就一定会在该序列中存在两个 $x$ 之间的差值和两个 $y$ 之间的差值与从头到尾有序的序列差得更多，因为从头到尾都有序的序列不管取任意一个元素这个元素和该元素的前一个元素在序列中都是大小相邻的两数，大小相邻的两数之间差值一定小。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int n,a[210],ans=0;
		scanf("%d",&n);
		for(register int i=1;i<=2*n;i++) scanf("%d",&a[i]);
		sort(a+1,a+2*n+1);
		for(register int i=2;i<=n;i++) ans+=a[i]-a[i-1];
		for(register int i=n+2;i<=2*n;i++) ans+=a[i]-a[i-1];
		printf("%d\n",ans);
		for(register int i=1;i<=n;i++) printf("%d %d\n",a[i],a[i+n]);
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：0)

最优的情况是，横坐标和纵坐标都不下降或不上升并且相邻两数之差尽量小，这样就不会走“回头路”且距离下一个点更近。

把 $a$ 数组排序，取前 $n$ 个数为横坐标，后 $n$ 个数为纵坐标最优。

```c++
#include<bits/stdc++.h>
using namespace std;

int a[202];

int main(){
	int t;cin>>t;
	while(t--){
		int n;scanf("%d",&n);
		int l=2*n;
		for(int i=0; i<l; i++) cin>>a[i];
		sort(a,a+l);
		int dis=0;
		for(int i=1; i<n; i++) dis+=(a[i]-a[i-1])+(a[i+n]-a[i+n-1]); // 两点间距离
		printf("%d\n",dis);
		for(int i=0; i<n; i++) printf("%d %d\n",a[i],a[i+n]);
	}
	return 0;
}
```

---

## 作者：carp_oier (赞：0)

## advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/CF1895B.html)看看呢。

## analysis

我们的目标是让曼哈顿距离最小。考虑贪心。

我们通过手玩几组数据就能发现，这个距离最小的形成是有规律的：对数组从小到大排序，前 $n$ 小的数作为一维，剩下的数作为另一维。

简单证明（~~不是反正法~~）：

假设一维存在这么三个数字 $a_1$，$a_2$，$a_3$，其中 $a_1 < a_2, a_2 > a_3$，记这三个数字排完序后得到的数字是 $b_1$，$b_2$，$b_3$，有 $b_1 < b_2 < b_3$。

计算这三个点这一维的距离：$|a_2 - a_1| + |a_3 - a_2| = 2 \times a_2 - a _ 1 - a _ 3$，等价于 $|b_2 - b_1| - |b_3 - b_2| = 2 \times b_3 - b_1 - b_2$。

所以我们进行排序之后得到最小序列的构造是等价的。


```cpp
    read(n);

    sum = 0;

    fos(i, 1, n * 2) read(a[i]);

    sort(a + 1, a + n * 2 + 1);

    fos(i, 2, n) sum += a[i] - a[i - 1];
    fos(i, n + 2, n * 2) sum += a[i] - a[i - 1];

    ww(sum), wl;
    fos(i, 1, n) ww(a[i]), ws, ww(a[2 * n - i + 1]), wl;
```

---

## 作者：BugGod (赞：0)

考虑贪心。首先我们将 $a$ 数组从小到大排序，然后将 $a_1\sim a_n$ 作为 $x$ 坐标，$a_{n+1}\sim a_{2n}$ 作为 $y$ 坐标，求差值就是答案。

证明：设点为 $(a_1,a_{n+1}),(a_2,a_{n+2}),\cdots,(a_n,a_{2n})$，如果我们交换 $a_i,a_j$，那么现在计算差时就会有“重复的部分”，因为 $a$ 是按从小到大排序的，那么交换后距离由 $a_i-a_{i-1}+a_{j+1}-a_j$ 变为 $a_j-a_{i-1}+a_{j+1}-a_i$。

$$\because a_i\le a_j$$

$$\therefore a_i-a_j\le a_j-a_i$$

$$\therefore a_i-a_{i-1}+a_{j+1}-a_j\le a_j-a_{i-1}+a_{j+1}-a_i$$

所以交换后距离会变大，所以不交换值更小。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[210],ans;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		memset(a,0,sizeof a);
		ans=0;
		for(int i=1;i<=2*n;i++)cin>>a[i];
		sort(a+1,a+1+2*n);
		for(int i=1;i<n;i++)ans+=a[i+1]-a[i];
		for(int i=n+1;i<2*n;i++)ans+=a[i+1]-a[i];
		cout<<ans<<'\n';
		for(int i=1;i<=n;i++)cout<<a[i]<<" "<<a[i+n]<<'\n';
	}
	return 0;
}
```

---

## 作者：yuyc (赞：0)

### 题意简述
给定 $2n$ 个正整数，将其组成 $n$ 个点的坐标，使得从某一点出发遍历所有点所经过的距离最短，对于两个点 $(x_1,y_1),(x_2,y_2)$ 其距离为 $\lvert x_1 - x_2 \rvert + \lvert y_1 - y_2\rvert$ 
### 解析
由求距离的公式可知：两点距离大小跟其横坐标差值的绝对值与纵坐标差值绝对值有关，故两点横纵坐标之间相差越少，距离越短。

所以，可以用排序的方法来使相邻数的差值尽可能小，在排序好的数中，只要使得所有的 $x$ 全部相邻，所有的 $y$ 全部相邻，（即前一半全是 横坐标 ，后一半全是 纵坐标，或者反过来），就能求得最短距离
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 205;
int a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,anss = 0;
		cin>>n;
		vector<pair<int,int> > ansp;
		for(int i=0;i<2 * n;i++){
			cin>>a[i];
		}	
		sort(a,a + 2 * n);
		int lx = a[0],ly = a[n];
		for(int i=0;i<n;i++){
			anss += abs(a[i] - lx) + abs(a[n + i] - ly);
			lx = a[i],ly = a[n + i]; 
			ansp.push_back({a[i],a[n + i]});
		}
		cout<<anss<<endl;
		for(int i=0;i<ansp.size();i++) cout<<ansp[i].first<<' '<<ansp[i].second<<endl;
	}
	return 0;
}
```



---

