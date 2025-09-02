# 「NnOI R2-T1」Khronostasis Katharsis

## 题目描述

$n$ 个气球被栓在水平地面上，初始高度均为 $0$ 米，初始时刻记为第 $0$ 秒。

每个气球被剪断栓绳后会匀速上升，第 $i$ 个气球每秒上升 $v_i$ 米。

现在已知第 $i$ 个气球会在第 $t_i$ 秒时被剪断栓绳，问第 $T$ 秒时最高的气球中编号最小的一个的编号。

## 说明/提示

**【样例 1 解释】**

第 10 秒时，五个气球的高度分别为 9,14,9,30,21 米。

**【数据范围】**

对于 $100\%$ 的数据，保证 $1\le n,v_i\le 10^5$，$0\le t_i\le T\le 10^4$。

**提示：本题开启捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c}
\textbf{Subtask} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& n \le 1000 & 33 \r
\textsf2& v_i\ 相等 & 10 \r
\textsf3& t_i \ 相等 & 10 \r
\textsf4& 无特殊限制 & 47 \r
\end{array}
$$

### 题目来源

|项目|人员|
|:-:|:-:|
|idea|EstasTonne|
|data|EstasTonne|
|check|船酱魔王|
|solution|EstasTonne|

## 样例 #1

### 输入

```
5 10
1 1
2 3
3 7
5 4
3 3```

### 输出

```
4```

## 样例 #2

### 输入

```
20 131
872 127
228 17
273 66
306 78
636 107
878 110
1141 122
835 10
247 28
248 48
65 4
664 109
267 96
1103 87
725 83
231 119
671 58
825 52
391 47
573 100```

### 输出

```
8```

# 题解

## 作者：Fkxxx (赞：7)

### 思路

只需求出每一个气球在 $m$ 时刻的高度，再取最大值即可。

这里有一个坑点，那就是如果在 $x$ 时放飞气球，那么它在 $x$ 时高度是已经达到了 $v_i$ 的，易得高度计算式：

$$( T - t_i + 1 ) \times v_i$$

## ACCODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m , p , ans ;
signed main(){
    cin >> n >> m ;
    for( int i = 1 ; i <= n ; i ++ ){
        int u , v ;
        cin >> u >> v ;
        int e = ( m - v + 1 ) * u ;
        if( e > p ){
            p = e ;
            ans = i ;
        }
    }
    cout << ans;
    return 0 ;
}
```

---

## 作者：ivyjiao (赞：2)

依题意可得，第 $T$ 秒时第 $i$ 个气球的高度是 $v_i\times(T-t_i)$。

然后把这个值取最小值并记录其编号即可。

因为极端数据 $10^5\times(10^4-0)\leq2^{31}-1$，所以不需要开 long long。

```
#include<iostream>
using namespace std;
int n,T,minn=-1,minni,x,y;
int main(){
    cin>>n>>T;
    for(int i=1;i<=n;i++){
        cin>>x>>y;
        if(x*(T-y)>minn) minn=x*(T-y),minni=i;
    }
    cout<<minni;
}
```

---

## 作者：coderJerry (赞：2)

$\operatorname{Update}$ $ {2023/09/23}$ ：完善了题目分析，调整码风。
### 题目大意
给出 $n$ 个气球的起飞时间和速度，问 $T$ 秒之后飞的最高的气球的编号。
### 题目分析
我们用结构体存放每个气球的飞行高度和编号，其中每个气球的飞行高度在输入时就计算好。计算方法如下：速度（即  $v_i$）$\times$ 时间（即 $T-t_i$）。接着按照题目意思排序后输出飞的最高的气球的编号即可。排序方法如下：按照飞行高度从大到小排序，如飞行高度相等，则序号较小的气球排在前。
### AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,T,v[100010],t[100010];
struct node{
    int num,id;
}ans[100010];
bool cmp(node x,node y){
    if(x.num!=y.num) return x.num>y.num;
    else return x.id<y.id;
}
int main(){
    cin>>n>>T;
    for(int i=1;i<=n;i++){
        cin>>v[i]>>t[i];
        ans[i].num=v[i]*(T-t[i]);//计算飞行时间
        ans[i].id=i;
    }
    sort(ans+1,ans+n+1,cmp);//排序
    cout<<ans[1].id<<endl;
    return 0;
}
```

---

## 作者：Morishima_zj_zhy (赞：1)

### 题目传送门

[P9569 Khronostasis Katharsis](https://www.luogu.com.cn/problem/P9569)

### 思路

由题面可知，我们求的是第 $T$ 秒时**最高**的气球中**编号最小**的一个的编号。

**大概分这样两个步骤：**

1. 算出每个气球在第 $T$ 秒时的高度。

1. 求出在第 $T$ 秒时最高的气球中编号最小的那个。

以样例一为例：

| 每秒上升的米数 | 剪断栓绳的时间 | 第 $10$ 秒的高度 |
| :----------: | :----------: | :----------: |
| $1$ | $1$ | $(10-1)\times1=9$ |
| $2$ | $3$ | $(10-3)\times2=14$ |
| $3$ | $7$ | $(10-7)\times3=9$ |
| $5$ | $4$ | $(10-4)\times5=30$ |
| $3$ | $3$ | $(10-3)\times3=21$ |

我们设第 $T$ 秒的高度为 $h$，可以得出公式：

$$h=(T-t_{i})\times v_{i}$$

求出公式之后，将公式代入代码，这题就通过了。

### AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int v[maxn], t[maxn];
int h[maxn]; // 记录每个气球在第 T 秒的高度

int main() {
	memset(h, 0, sizeof(h));
	int n, T;
	cin >> n >> T;
	for (int i = 1; i <= n; i++) {
		cin >> v[i] >> t[i];
	}
	for (int i = 1; i <= n; i++) {
		h[i] = (T - t[i]) * v[i];
	}
	int maxx = -0x3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		if (h[i] > maxx) maxx = h[i];
	}
	for (int i = 1; i <= n; i++) {
		if (h[i] == maxx) { // 因为我们是按照编号从小到大枚举，所以存在和最大值相同的高度时，这个气球的编号一定是最高的气球中编号最小的。
			cout << i;
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：zzx114514 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P9569)
# 题目大意
$n$ 个气球被栓在水平地面上，初始高度均为 $0$ 米，初始时刻记为第 $0$ 秒。

每个气球被剪断栓绳后会匀速上升，第 $i$ 个气球每秒上升 $v_i$ 米。

现在已知第 $i$ 个气球会在第 $t_i$ 秒时被剪断栓绳，问第 $T$ 秒时最高的气球中编号最小的一个的编号。
# 解题思路
先判断哪些气球在第 $T$ 秒已经升空，计算它们当前的高度，按照高度和编号排序，高度从大到小，编号从小到大，数组中第一个气球的编号就是答案。
# 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,T,v,t;
struct Node
{
	int h,id;//存储已升空气球的高度和编号 
} a[100005];
bool cmp(Node a,Node b)
{
	if (a.h==b.h) return a.id<b.id;
	return a.h>b.h; 
}//按照高度和编号排序，高度从大到小，编号从小到大 
int main()
{
	cin>>n>>T;
	for (int i=1;i<=n;i++)
	{
		cin>>v>>t;
		if (t<=T) a[i].h=(T-t)*v;//如果气球已升空，则计算高度 
		a[i].id=i;//存储编号 
	}
	sort(a+1,a+n+1,cmp);//排序 
	cout<<a[1].id;//第一个气球的编号就是答案 
	return 0;//华丽的结尾 
}
```


---

## 作者：zhang_Jimmy (赞：1)

赛时思路：

容易发现，第 $i$ 个气球在第 $T$ 秒时的高度为：

$$(T - t_i + 2) \cdot v_i$$

我们定义 $maxn$ 是到第 $i$ 个气球上升高度的最大值，$ans$ 是到第 $i$ 个气球的上升高度的最大值的气球的编号。

那么 $maxn$ 的值每次就会变为 $\max(maxn,(T - t_i + 1 + 1) \cdot v_i)$。

如果 $maxn$ 有变化，那么就将 $ans$ 变为当前气球的编号。

最后输出 $ans$ 就可以了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, T, u, t, ans, maxn;
int main(){
// 	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> n >> T;
	for(int i = 1; i <= n; i ++){
		cin >> u >> t;
		int tmp = maxn;
		maxn = max(maxn, (T - t + 2) * u);
		if(maxn != tmp) ans = i;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：FurippuWRY (赞：0)

题意：计算气球的运动高度 $h$，输出在 $T$ 秒时，位于最高点的气球的编号，如果有多个气球位于最高点，则输出最小的编号。

众所周知，物体运动距离的公式为 $s=vt$。依据题意，因为气球一开始都被栓在地上不动，在 $t_i$ 秒被剪断栓绳，即在 $t_i$ 秒开始运动，所以气球运动时间为 $T-t_i$，公式变为 $h=v_i(T-t_i)$，代入计算即可。

## AC CODE
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 9;

int n, T, v, t[N], maxn = 0, num[N], cnt = 0;

int main() {
	cin >> n >> T;
	for (int i = 1; i <= n; ++i) {
		cin >> v >> t[i];
		t[i] = T - t[i];
		t[i] = t[i] * v;
		if (t[i] > maxn) {
			maxn = t[i];
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (t[i] == maxn) {
			num[++cnt] = i;
		}
	}
	sort(num, num + cnt);
	cout << num[1];
	return 0;
}
```

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9569)

观察题面，我们可以得知：第 $i$ 个气球在当时间到达第 $T$ 秒时，飞行的总高度为 $v_i\times(T-t_i)$ 米。于是我们便将此设定为比较飞行高度的参数，每次打擂台比较大小即可。

但是特别地，本题要求输出的是编号。所以我们在比较飞行高度（满足“打下擂台”条件）时，将编号 $i$ 记录即可完成本题。于是得代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define wtl(x) wt(x),putchar('\n')
#define kg putchar(' ')
#define hh putchar('\n')
signed main()
{
	int n,T;
	rd(n,T);
	int mx=-1,xb=-1;
	for(int i=1;i<=n;i++)
	{
		int v,t;
		rd(v,t);
		if(v*(T-t)>mx)
		{
			mx=v*(T-t);
			xb=i;
		}
	}
	wtl(xb);
	return 0;
}
```

---

## 作者：xiaoyang111 (赞：0)

# P9569 Kronostasis Katharsis 题解

## 前言

[题目传送门。](https://www.luogu.com.cn/problem/P9569)

[可能更好的阅读体验。](https://www.luogu.com.cn/blog/xiaoyang111/solution-p9569)

## 讲解

### 思路

这个题是本场比赛的签到题，很简单，仅仅是考察模拟，具体解题步骤见下。

1. 输入各种数据。

2. 算出第 $i$ 个气球在第 $T$ 秒的时候的高度，计算第 $T$ 秒时候气球的高度是多少的计算方法见后面。

3. 在所有气球升上的高度里面取最大值，输出。

气球在第 $T$ 秒的时候的高度是多少呢？看题，题目说“每个气球被剪断栓绳后会匀速上升”我们获得了气球上升的速度和剪短绳子的时间，先算出气球总共上升了多久时间，乘上上升的速度就行了，形象化的说，就是第 $i$ 个气球上升高度就是 $(T - t_i) × v_i$。

### 代码

思路出来了，代码很简单。

代码风格可能有些不好看，请见谅。

```cpp
#include <iostream>
using namespace std;
int main(){
	int n,t;
	cin >> n >> t;//输入 
	int ans1=-1,ans2=-1;//第一个是最大数第二个是下标 
	for (int i=1;i<=n;++i){//遍历输入 
		int v,temp;//第一个是上升速度第二个是多久放 
		cin >> v >> temp;//输入 
		int time=t-temp;//放开一共上升了多久 
		int sm=time*v;//上升了多少 
		if (ans1<sm){//如果比之前的最大值还要高 
			ans1=sm;//改变之前的最大值 
			ans2=i;//改变之前的下标 
		}
	}
	cout<<ans2<<endl;//输入 
	return 0;//结束 
}
```

---

## 作者：__zfy__ (赞：0)

### 思路
基础问题。

对于每个气球，就是用 $T - t_i \times u_i$ 这个公式求，下面是推导：
- 首先要求出剪短绳子后有多少时间飞，就是 $T - t_i $。
- 最后 $\times u_i$ 得出最终高度。

找到最大的 $ans$ 和最小的 $id$ 输出。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[100005];
//快读
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
//  变量名=read();
//  n=read();
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(0);
	ll n,T,ans=-1,id=10000000000;
	cin>>n>>T;
	for(ll i=1;i<=n;i++)
	{
		ll u,t;
		cin>>u>>t;
		t=T-t;
		if(ans<u*t)
		{
			ans=u*t;
			id=i;
		}
	}
	cout<<id<<endl;
	return 0;
}
```


---

