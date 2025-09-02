# [GCJ 2010 #1C] Rope Intranet

## 题目描述

一家公司位于两座非常高的建筑物中。连接这两座建筑的公司内部网由许多电线组成，每根电线连接左侧建筑的一扇窗户和右侧建筑的一扇窗户。

你正从侧面观察这些建筑，因此一座建筑在左边，另一座在右边。左侧建筑的窗户在其右墙上显示为一些点，右侧建筑的窗户在其左墙上显示为一些点。电线是连接左侧建筑窗户和右侧建筑窗户的直线段。

![](https://cdn.luogu.com.cn/upload/image_hosting/c9k75j11.png)

你注意到没有两根电线共用一个端点（换句话说，每个窗户最多只连接一根电线）。然而，从你的视角来看，有些电线在中途相交。你还注意到，每个交点恰好有两根电线相交。

在上图中，交点是黑色圆点，窗户是白色圆点。

你能看到多少个交点？

## 说明/提示

**数据范围**

- $1 \leqslant T \leqslant 15$。
- $1 \leqslant A_i \leqslant 10^4$。
- $1 \leqslant B_i \leqslant 10^4$。
- 每组测试数据中，所有 $A_i$ 互不相同。
- 每组测试数据中，所有 $B_i$ 互不相同。
- 不存在三根电线在同一点相交。

**小数据范围（9 分，测试点 1 - 可见）**

- $1 \leqslant N \leqslant 2$。

**大数据范围（13 分，测试点 2 - 隐藏）**

- $1 \leqslant N \leqslant 1000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3
1 10
5 5
7 7
2
1 1
2 2```

### 输出

```
Case #1: 2
Case #2: 0```

# 题解

## 作者：zhouxiaodong (赞：4)

# 思路
看题模拟就行，大概就是下面这段过程。
- 循环 $t$
  - 读取 $n$ 条电线的左右端点。
  - 找交叉，判断条件：
    - 电线 $j$ 的左端点比电线 $k$ 的左端点低，但右端点比电线 $k$ 高。
    - 电线 $j$ 的左端点比电线 $k$ 的左端点高，但右端点比电线 $k$ 低。
    - 累加交叉数。
  - 输出交叉数。
# AC Code
``````````cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int x;
	int y;
};
int t;
signed main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int n,ans=0;
		cin>>n;
		node a[1010];
		for(int j=1;j<=n;j++)
		{
			cin>>a[j].x>>a[j].y;
		}
		for(int j=1;j<=n;j++)
		{
			for(int k=j+1;k<=n;k++)
			{
				if((a[j].x<a[k].x&&a[j].y>a[k].y)||(a[j].x>a[k].x&&a[j].y<a[k].y))
				{
					ans++;
				}
			}
		}
		cout<<"Case #"<<i<<": "<<ans<<"\n";
	}
	return 0;
}
``````````

---

## 作者：Doraeman (赞：1)

## 交点
如果两条线交叉，那么它们就有交点。

## 判断交叉
怎么判断交叉呢？
![](https://cdn.luogu.com.cn/upload/image_hosting/niqjru05.png)  
在这幅图中，可以清晰看出判断方法：如果 $A_i>A_j,B_i<B_j$，那么这两条线就必然会存在交点。

反之，如果不满足上述条件，就肯定不会有交点（可以自行画图验证）。

又因为 $i,j$ 等价，所以满足 $A_i<A_j,B_i>B_j$ 时也会有交点。

## 细节
刚才已经提到，$i,j$ 等价，所以如果直接进行 $2$ 层循环遍历符合上述两种条件之一的 $(i,j)$ 组合，就会同时将 $(j,i)$ 组合计入，会存在**重复计算**。

为了避免重复计算，可以都算好之后将答案除以 $2$，也可以**加入限制条件**，如 $i>j$，此时就不会存在重复计算了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+5;

int a[N], b[N];

int main(){
    int T; cin >> T;
    for(int _=1; _<=T; _++){
        int n; cin >> n;
        int ans = 0;
        for(int i=1; i<=n; i++){
            cin >> a[i] >> b[i];
            for(int j=1; j<i; j++)
                // 遍历之前的所有电线, i>j 避免存在重复计算  
                if(a[i] < a[j] && b[i] > b[j]) ans++;
                else if(a[i] > a[j] && b[i] < b[j]) ans++;
        }
        printf("Case #%d: %d\n",_,ans);
    }
}
```

---

## 作者：LiHen_Yan (赞：1)

## P13396 [GCJ 2010 #1C] Rope Intranet 题解

### Problem
给你 $n$ 条线段的左右端点编号，求这 $n$ 条线段有几个交点，$n \leq 1000$。

### Solution
注意到数据保证 $a_i$ 互异，$b_i$ 互异，不存在三根电线在同一点相交。

那么在这种情况下，对于两条线段 $i,j$，出现交点的充要条件就只有两种。

第一种就是 $i$ 这条直线相对于 $j$ 来说，左面在上面，右面在下面，也就是 $a_i > a_j$ 且 $b_i < b_j$。

第二种就是 $i$ 这条直线相对于 $j$ 来说，左面在下面，右面在上面，也就是 $a_i < a_j$ 且 $b_i > b_j$。

暴力枚举无序直线对 $i,j$ 即可，时间复杂度 $O(n^2)$。

### Code

```cpp
#include <bits/stdc++.h>

#define int long long
constexpr int maxn = 1010;
int a[maxn], b[maxn], n, T;
inline void solve(int ca){
	int ans = 0;
	std::cin >> n;
	for(int i = 1; i <= n; i++) std::cin >> a[i] >> b[i];
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			if(a[i] > a[j] && b[i] < b[j]){
				ans++;
				continue;
			}
			if(a[i] < a[j] && b[i] > b[j]){
				ans++;
			}
		}
	}
	std::cout << "Case #" << ca << ": " << ans << '\n'; 
}
int32_t main(){
	std::cin.tie(nullptr) -> std::ios::sync_with_stdio(false);
	std::cin >> T;
	for(int i = 1; i <= T; i++){
		solve(i);
	}
	
	return 0;
} 
```

---

## 作者：AFO_Lzx (赞：1)

要解决本题，我们可以观察到：两根电线会交叉，**当且仅当它们的连接方式会交叉**。

具体地，对于第 $i$ 根和第 $j$ 根电线，有如下结论：

- 若 $a_i<a_j$ 且 $b_i>b_j$，这两根电线会交叉。
- 若 $a_i>a_j$ 且 $b_i<b_j$，这两根电线会交叉。

本质上这就是在计算**逆序对**的数量。

我们可以通过一下几步解决这个问题：

- 首先先按左侧建筑物的窗户高度 $a_i$ 对电线进行排序。这是保证了对于所有 $i<j$，有 $a_i<a_j$。
- 接下来我们根据窗户的新排序就得到了一个新的 $b$ 序列，这里可以通过结构体排序实现。
- 根据前面的结论，我们只需要计算满足 $i < j$ 且 $b_i > b_j$ 的数对 $(i,j)$ 的数量，也就是 $b$ 序列中逆序对的数量。

其中，由于数据范围很小、时限大，所以逆序对的计算只需要 $O(n^2)$ 循环枚举计算即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using ll = long long;
using namespace std;

const int N = 1e5 + 5;

struct node {
	int a, b;
} c[N];

bool cmp(const node &x, const node &y) {
	return x.a < y.a;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int q;
	cin >> q;
	
	for (int i = 1; i <= q; i++) {
		int n;
		cin >> n;
		
		for (int i = 1; i <= n; i++) {
			cin >> c[i].a >> c[i].b;
		}
		sort(c + 1, c + n + 1, cmp);
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (c[i].b > c[j].b) cnt++;
			}
		}
		cout << "Case #" << i << ": " << cnt << '\n';
	}
	return 0;
}
```

省流：我是 Luogu 第 $2$ 个 AC 此题的入。

---

## 作者：signed_long_long (赞：1)

# 题目解法

注意到不存在三根电线在同一点相交，$N\le 1000$，$T\le 15$，所以可以放心用 $O(N^2)$ 的方法。

枚举任意两条电线 $i$ 和 $j$，判断这两条电线是否相交的方法就是看它们是不是交错了，即 $a_i<a_j$ 且 $b_i>b_j$，或者 $a_i>a_j$ 且 $b_i<b_j$。

时间复杂度 $O(TN^2)$，足以通过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
const int N=1005;
int a[N],b[N];
void work(int qwert){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){//避免重复
			if(a[i]<a[j] and b[i]>b[j]) ans++;
			if(a[i]>a[j] and b[j]>b[i]) ans++;
		}
	}
	printf("Case #%d: %d\n",qwert,ans);
}
signed main(){
	cin>>T;
	for(int __=1;__<=T;__++) work(__);
	return 0;
}
```

---

## 作者：L_T_L (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13396) 

我们需要计算所有电线之间的交点数量。关键在于理解两条电线在什么情况下会相交。从侧面观察时，两条电线 $(A_1,B_1)$ 和 $(A_2,B_2)$ 会相交的条件是：它们在左建筑和右建筑中的相对顺序相反。具体来说，如果 $A_1<A_2$ 且 $B_1>B_2$，或者 $A_1>A_2$ 且 $B_1<B_2$，那么这两条电线就会相交。

因此，问题转化为统计所有满足 $A_i<A_j$ 且 $B_i>B_j$ 或者 $A_i>A_j$ 且 $B_i<B_j$ 的电线对 $(i,j)$ 的数量，其中 $i<j$。这类似于计算序列中的逆序对数量，可以使用归并排序的方法高效计算逆序对数目。

首先将所有电线按照左建筑的高度 $A_i$ 进行排序。然后，统计右建筑的高度 $B_i$ 中的逆序对数目。每个逆序对即对应一个交点。

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
struct nd{
    int a;
    int b;
};
bool cmp(const nd &w1,const nd &w2){return w1.a<w2.a;}
int T;
int main(){
    cin>>T;
    for(int t=1;t<=T;t++){
        int n;
        cin>>n;
        nd wires[N];
        for(int i=0;i<n;i++)
            cin>>wires[i].a>>wires[i].b;
        sort(wires,wires+n,cmp);
        int ans=0;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                if(wires[i].b>wires[j].b)
                    ans++;
        cout<<"Case #"<<t<<": "<<ans<<endl;
    }
    return 0;
}
```
其实对于 $3$ 秒的时间限制，可以使用复杂度更高的排序算法。

---

## 作者：stardusts (赞：1)

# 题意

给定两条竖线之间的连线，求这些线条的交点个数。

# 思路

我们先思考：什么条件下线段 $x,y$ 会相交？那肯定就是 $x$ 的一端在 $y$ 的上方，而另一端在 $y$ 的下面，即端点的相对位置不同。

再看本题的数据：$1 \leqslant N \leqslant 1000$，于是我们便可以愉快地打暴力，两层循环枚举两条线段，判断线段两端点相对位置是否不同。

判相对位置不同有几种方法，我用的方法是这个：`(a[i].x - a[j].x) * (a[i].y - a[j].y) < 0`，意思就是如果端点的相对位置不同，那么 `a[i].x - a[j].x` 和 `a[i].y - a[j].y` 必然有一个为负数而另一个不是，所以如果线段两端点相对位置是否不同，则两者相乘结果必然小于 0。

# 注意事项

注意第二层循环的 $j$ 要从 `i + 1` 开始，这样可以避免重复计算。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
struct NONE{
    int x, y;
}a[N];
int t, n, ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // 以上两行是快读快写 
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
    	ans = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> a[i].x >> a[i].y;
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                if ((a[i].x - a[j].x) * (a[i].y - a[j].y) < 0)
                    ans++;
        cout << "Case #" << _ << ": " << ans << '\n';
    }
    return 0;
}
```

---

## 作者：SXY83296647 (赞：0)

## 思路
这题让我们求出每组数据中电线的交点总和，首先可以求出两根电线 $(a_i,b_i)$ 和 $(a_j,b_j)$ 相交的条件是 $(a_i - a_j) \times (b_i - b_j) < 0$，接着就可以判断并计数了，以下给出代码：
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,N;
int main()
{
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin>>T;
    for (int t=1;t<=T;t++){
        cin>>N;
        vector<int> a(N,0);
        vector<int> b(N,0);
        for (int i=0;i<N;i++){
            cin>>a[i]>>b[i];
        }
        int ans=0;
        for (int i=0;i<N;i++){
            for (int j=i+1;j<N;j++){
                if((a[i]-a[j])*(b[i]-b[j])<0){
                    ans++;
                }//(a[i]-a[j])*(b[i]-b[j])<0的本质是判断两根电线的高度顺序是否相反
            }
        }
        cout<<"Case #"<<t<<": "<<ans<<"\n";
    }
    return 0;
}
```
时间复杂度：$O(N^2)$

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13396)

# 题目分析

本题最重要的一点是找到两条电线相交的充要条件。结论：设两条电线相交，当且仅当 $(A_1-A_2)\times(B_1-B_2)<0$。证明：

首先给出一个定理。介值定理：若连续函数满足 $\operatorname{f}(x_1)=a$，$\operatorname{f}(a_2)=b$，则对于任意 $a \le c \le b$，都存在 $x_1 \le x \le x_2$，使得 $\operatorname{f}(x)=c$。特别地，对于连续函数，若 $c=0$，则定理变成若 $x_1$，$x_2$ 满足其对应的函数值分别位于 $x$ 轴的两侧，则 $x_1$，$x_2$ 间必然存在零点。

若 $(A_1-A_2)\times(B_1-B_2)<0$，假设左右窗户间距足够大。将 $A_1B_1$ 线段看作 $x$ 轴，线段 $A_2B_2$ 为函数 $\operatorname{f}(x)$。设$A_2$ 对应的横坐标为 $0$，$B_2$ 对应的横坐标为 $1$，易证 $\operatorname{f}(0)<0$，$\operatorname{f}(1)>0$。则 $0$ 到 $1$ 间必然存在零点，即与 $x$ 轴相交的点，这里就是与 $A_1B_1$ 相交的点。

若 $A_1B_1$ 与 $A_2B_2$ 有交点。假设 $(A_1-A_2)\times(B_1-B_2)>0$，则 $\operatorname{f}(0)$ 与 $\operatorname{f}(1)$ 位于 $x$ 轴的同侧，设交点为 $(p,0)$，则从 $0$ 到 $p$ 这一段 $\operatorname{f}(x)$ 的增减性与 $p$ 到 $1$ 这一段不同，显然这不符合直线的性质，因此假设不成立，即 $(A_1-A_2)\times(B_1-B_2)<0$。

有了这一点就好办了。由于 $n$ 的范围很小，可以枚举。建议对所有电线按照 $A_i$ 从小到大排序以去重。

# 代码


```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
struct str{
	int x,y;
}s[N];
int cmp(str a,str b){
	if(a.x!=b.x){
		return a.x<b.x;
	}
	return a.y<b.y;
}
int main(){
	int t;
	cin>>t;
	for(int o=1;o<=t;o++){
		cout<<"Case #"<<o<<": ";
		int n,ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>s[i].x>>s[i].y;
		}
		sort(s+1,s+1+n,cmp);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i-1;j++){
				if(s[j].y>s[i].y){
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：DFs_YYDS (赞：0)

# 题目大意
两条平行线，在这两条线上有 $n$ 条线段，以及这些线的端点坐标（分别在这两条平行线上），问这些线段有多少个交点（没有三个线段交于一点）。
# 具体思路
先把框架写好


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans;
struct o{
	int x,y;
}a[1000005];//使用结构体方便后续操作 
int main(){
	cin>>t;
	for(int w=1;w<=t;w++){//由于这里需要输出是第几组数据，所以需要用一个变量来统计 
		cin>>n,ans=0;
    	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    	
    	//计算 
    	
    	cout<<"Case #"<<w<<": "<<ans<<"\n";
	}
    return 0;
}
```


不处理，直接对这些杂乱无章的数据进行计算，非常麻烦。所以我们先按照第一个点从小到大排个序。

接着我们一个一个计算，在遍历到第 $i$ 条线的时候，前面有多少条线和它相交呢？

由于我们已经排序过了，所以前面的线段的起点一定比这条要小，所以我们应该利用终点的关系进行计算。

遍历之前的每一条线，遍历到线 $j$ 时，如果 $j$ 的终点小于 $i$ 终点，则不会相交（如图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/iiot5i73.png)

反之，如果 $j$ 的终点大于 $i$ 终点，则不会相交（如图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/e0arf9p6.png)

所以我们只需要对于每条线遍历 $i$，$i$ 之前的所有线，若其终点比 $i$ 的终点大，则答案增加 $1$，否则不变。


```cpp
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++){
    for(int j=1;j<i;j++){
        if(a[j].y>a[i].y)ans++;
    }
}
```

# 完整代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans;
struct o{
	int x,y;
}a[1000005];
bool cmp(o x,o y){
	return x.x<y.x;
}
int main(){
	cin>>t;
	for(int w=1;w<=t;w++){
		cin>>n,ans=0;
    	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
		sort(a+1,a+n+1,cmp);
    	for(int i=1;i<=n;i++){
    		for(int j=1;j<i;j++){
    			if(a[j].y>a[i].y)ans++;
    		}
    	}
    	cout<<"Case #"<<w<<": "<<ans<<"\n";
	}
    return 0;
}
```

完结撒花！

---

## 作者：chenzhuole1 (赞：0)

## 题解：P13396 [GCJ 2010 #1C] Rope Intranet

[题目链接](https://www.luogu.com.cn/problem/P13396)

### 思路

考虑暴力枚举所有可能的电线对，判断它们在左侧建筑的高度顺序与右侧建筑的高度顺序相反，统计满足条件的对数即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t;
    for(int k=1;k<=t;k++)
	{
        s=0;
        cin>>n;
        vector<pair<int,int>> wires(n);
        for(auto& w:wires) cin>>w.first>>w.second;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                if((wires[i].first<wires[j].first)^(wires[i].second<wires[j].second))
                    s++;
        cout<<"Case #"<<k<<": "<<s<<'\n';
    }
    return 0;
}
```

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13396)

### 思路

暴力大水题。

这道题我们只要找到形成交点的条件即可。我们容易通过观察发现，若有两扇窗户 $i$ 与 $j$，则条件为 $a_i<a_j$ 且 $b_i>b_j$ 或 $a_i>a_j$ 且 $b_i<b_j$，那么由于数据很小，可以直接暴力枚举 $i$ 和 $j$，看是否符合条件，符合条件交点数就加 $1$。

注意输出的格式。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[1005],b[1005],s;
signed main(){
    cin>>t;
    for(int k=1;k<=t;k++)
    {
    	scanf("%lld",&n);
    	for(int i=1;i<=n;i++)
    	{
    		scanf("%lld%lld",&a[i],&b[i]);
    	}
    	s=0;
    	for(int i=1;i<=n;i++)
    	{
    		for(int j=i+1;j<=n;j++)
    		{
    			if(a[i]<a[j]&&b[i]>b[j]||a[i]>a[j]&&b[i]<b[j])  s++;
    		}
    	}
    	printf("Case #%lld: %lld\n",k,s);
    }
    return 0;
}
```

---

## 作者：abc1234shi (赞：0)

# 题意
求出题目中有多少线段相交，一道数学模拟题。
# 思路
两条线段如何满足相交呢？如图所示，黑线代表高楼，蓝线是电线，红色的点是电线的交点，左边数字代表左端点高度，右边数字是右端点高度（可能不太准确）。
![](https://cdn.luogu.com.cn/upload/image_hosting/0rm8m2b6.png)
答案很简单，其实就是两条线段左端点上下分布，而这两条线段的右端点刚好反过来，这两条线段就相交。


题目中又说，不存在两条线段共端点的情况，所以就不存在两条线段相交于端点的情况。

那么我们就可以将所有线段以左端点大小进行排序，然后开始枚举。因为进行排序过，所以在左端点中后面的项肯定是大于前面的项的。所以我们就判断右端点，如果前面的项的右端点大于后面的项的右端点，则这两条直线相交，就会存在交点，就将答案变量增加一。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct a{
	int x,y;
}b[111000];
int cmp(a i,a j){
	return i.x<j.x;
} 
int main(){
	int t;
	cin>>t;
	for(int c=1;c<=t;c++){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>b[i].x>>b[i].y;
		int cnt=0;
		sort(b+1,b+n+1,cmp);
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				if(b[i].y>b[j].y)cnt++;
			}
		}
		cout<<"Case #"<<c<<": "<<cnt<<endl;
	}
	return 0;
}
```

---

## 作者：YuTinMin (赞：0)

## 思路

又有题解可以写了。

求交点？那不就是给左边的楼的高度弄一个排序，然后一个双重循环然后判断有没有比上一个低吗？

我说着有一些模糊，举个例子吧。左边的房子 $1$、$2$ 和 $3$ 分别连接右边的窗户 $2$、$3$ 和 $1$。直接画一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ekdhaays.png)

一个十分帅气的图。然后我们继续看，我们先看左边的，从高到低看，左 $3$ 连接的右 $1$ 比左 $2$ 连接的右 $3$ 低，这说明什么了，说明它们之间肯定就有一个交点的，就可以发现规律，如果下一个的连接对象比上一个的连接对象低，那就是一个交点，或者说是一个低的点的连接对象比一个高的点的连接对象高，就会出现一个交点，那就 `ans` 加一，那答案不就出来了嘛，直接看代码，更好理解。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

struct node
{
    int x, y; //x是左边，y是右边
}a[10005];

bool cmp(node a, node b)
{
    return a.x < b.x; //左边从小到大排序
}

int main()
{

    int T;
    cin >> T;
    for(int t = 1;t <= T;t++)
    {
        int n, ans = 0; //ans是答案的数量
        cin >> n;
        for(int i = 1;i <= n;i++)
            cin >> a[i].x >> a[i].y;
        sort(a + 1,a + n + 1, cmp);
        for(int i = 1;i <= n;i++)
        {
            for(int j = i + 1;j <= n;j++)
            {
                if(a[i].y > a[j].y) //交点出现的条件
                    ans++;
            }
        }
        printf("Case #%d: %d \n", t, ans); //输出
    }

    system("pause");
    return 0;
}
```

---

## 作者：tujiaqi12 (赞：0)

## 思路
对于每个 $1 \leqslant i < j \leqslant n$，若满足以下的一种情况就会产生交点。

第一种，$a_i < a_j$ 且 $b_i > b_j$。

第二种，$a_i > a_j$ 且 $b_i < b_j$。

双层遍历遍历每一个符合条件的 $i$ 和 $j$，统计交点数量即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n;
ll a[1005],b[1005],ans;
int main(){
	scanf("%lld",&t);
	for(ll i = 1;i <= t;i++){
		scanf("%lld",&n); 
		for(ll j = 1;j <= n;j++){
			scanf("%lld%lld",&a[j],&b[j]);
		} 
		ans = 0;
		for(ll j = 1;j < n;j++){
			for(ll k = j + 1;k <= n;k++){
				if(a[j] > a[k] && b[j] < b[k]){
					ans++;
				}
				if(a[j] < a[k] && b[j] > b[k]){
					ans++;
				}
			}
		}
		printf("Case #%lld: %lld\n",i,ans);
	}
	return 0;
}
```

---

## 作者：LotleTos (赞：0)

组成每个交点的两条线叠在一起都是 `X` 的变形。

所以，对于两条有交点的线 $x$ 和 $y$：

- 要么 $x$ 的左端点比 $y$ 的左端点高，且 $x$ 的右端点比 $y$ 的右端点低。

 - 要么 $x$ 的左端点比 $y$ 的左端点低，且 $x$ 的右端点比 $y$ 的右端点高。

枚举所有的 $x$ 和 $y$，通过这个性质判断是否有交点，累加答案即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010];
int b[1010];
int f(){
	int n;
	cin>>n;
	int sum=0;
	for(int i=0;i<n;i++){
		cin>>a[i]>>b[i];
		for(int j=0;j<i;j++){
			if(a[i]>a[j]&&b[i]<b[j]){
				sum++;
			}
			if(a[i]<a[j]&&b[i]>b[j]){
				sum++;
			}
		}
	}
	cout<<sum;
	return 0;
}
int main(){
	int T;
	cin>>T;
	for(int i=1;i<=T;i++){
		cout<<"Case #"<<i<<": ";//冒号后面有空格！很坑！
		f();
		cout<<endl;
	}
}
```

---

## 作者：god_std (赞：0)

### Part 1 主要思路

怎么说呢？基本没有思维含量，枚举两条线段是否相交即可

### Part 2 部分代码实现

  我们需要一个定理（[介值定理](https://baike.baidu.com/item/%E4%BB%8B%E5%80%BC%E5%AE%9A%E7%90%86/10818809)）：存在连续函数 $f(x),g(x)$ 和两个整数 $x_1,x_2(x_1\neq x_2)$，满足 $f(x_1)<g(x_1),f(x_2)>g(x_2)$，则必有一个实数 $x_3 \in (x_1,x_2)$，满足 $f(x_3)=g(x_3)$。

  先看看两条线段相交的函数 `J(int m,int n)` 表示第 $m$ 条电线与第 $n$ 条电线是否相交，有两种情况相交（假设 $l_m,l_n$ 为电线的左端点，$r_m,r_n$ 为右端点）：
  
1. `l[m]>l[n]&&r[m]<r[n]`，此时两直线不平行，且由介值定理，两直线有交点。
2. `l[m]<l[n]&&r[m]>r[n]`，同上，两直线有交点。

那么有了以下函数（标准版）：
```cpp
//46ms
bool J(int m,int n)
{
	if(l[m]>l[n]&&r[m]<r[n])
		return true;
	if(l[m]<l[n]&&r[m]>r[n])
		return true;
	return false;
}
```
经过修改可降低复杂度（我也不知道怎么降低的）
```cpp
//30ms
bool J(int m,int n)
{
	return ((l[m]-l[n])*(r[m]-r[n])<0);
}
```

剩下的暴力就可以啦！

### Part 3 AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0')
	{
		int num=ch-'0';
		x=x*10+num;
		ch=getchar();
	}
	return f*x;
} 
int T=read();
int l[1000001];
int r[1000001];
bool J(int m,int n)
{
	return ((l[m]-l[n])*(r[m]-r[n])<0);
}
int solve()
{
	memset(l,0,sizeof(l));
	memset(r,0,sizeof(r));
	int n=read(),ans=0;
	for(int i=1;i<=n;i++)
		l[i]=read(),
		r[i]=read();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(J(i,j))
				ans++;
	return ans;
}
int main()
{
	int it=1;
	while(T--)
	{
		int ans=solve();
		cout<<"Case #"<<it++<<": "<<ans<<endl;
	}
	return 0;
}
```

---

