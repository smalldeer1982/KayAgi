# City Game

## 题目描述

Bob爱上了一个策略游戏（Simcity？）游戏中一个城市由k个地区组成，每个地区都是一块长N×宽M大小的网格矩形,其中可能有些网格已被占用，用R表示;有些则是空地，用F表示。

游戏中可以在空着的空间上建一个矩形的建筑，同时每个建筑按它所占的空地网格数来收租，每占用一个网格可收租金3美元。Bob想知道每个地区中最大面积建筑物能收多少租金。

## 样例 #1

### 输入

```
3
3 3
R R F
F F F
F R F

5 6
R F F F F F
F R F F F F
F F R F F F
F F F R F F
F F F F R R

4 5
R R R R R
R R F R R
R R R R R
R R F R R```

### 输出

```
9
27
3```

# 题解

## 作者：emptysetvvvv (赞：6)

## 背景

>萌新 $\varnothing$ 决心写一篇博客。因为艾教第一次提到这道很经典的题的时候，她还是小小萌新，只会 $O(n^4)$ 的朴素做法。在此后的日子里，艾教不止一次讲到此题，终于有一天，$\varnothing$ 在练习题里见到了他。

## 思路&代码

### Solution1 dp

对于每一个点 $(i, j)$ 表示第 $i$ 行第 $j$ 列，$mp_{i,j}$ 为 $1$ 表示此地有障碍，否则为 $0$。

$h_{i,j}$ 表示他最多向上走距离（就撞墙了），转移方程：

$$h_{i,j}=\begin{cases}h_{i-1,j}+1,& mp_{i,j}=1\\0,&mp_{i,j}=0\end{cases}$$

从 $(i,j)$ 到 $(i-h_{i,j}+1,j)$ 的这根线，向左最远平移到第 $l_{i,j}$ 列，向右最远平移到第 $r_{i,j}$ 列，则该矩形面积为 $(r_{i,j}-l_{i,j}+1)h_{i,j}$。

这个 $l,r$ 显然是按行转移的，我们可以在空间上压掉 $i$ 这一维。

转移的方法也很简单，假设当前 $l_j=k$，若有 $h_{i,k-1}\geqslant h_{i,j}$，则 $k\gets l_{k-1}$。$r$ 的转移同理。

枚举 $i,j$ 复杂度 $O(n^2)$，用 `while` 循环实现的转移看似复杂度 $O(n)$，实际上根本不可能达到，均摊总复杂度 $O(\alpha n^2)$。实测用时 10ms。


```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1005;
int kase, n, m, l[maxn], r[maxn], mp[maxn][maxn], h[maxn][maxn];
int main() {
	scanf("%d", &kase);
	while(kase--) {
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) {
				char c; do c = getchar(); while(c != 'R' and c != 'F');
				if(c == 'R') mp[i][j] = 1;
				else h[i][j] = h[i-1][j] + 1;
			}
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			l[1] = 1;
			for(int j = 2; j <= m; j++) {
				int k = j; while(k > 1 and h[i][k-1] >= h[i][j]) k = l[k-1];
				l[j] = k;
			}
			r[m] = m;
			for(int j = m - 1; j; j--) {
				int k = j; while(k < m and h[i][k+1] >= h[i][j]) k = r[k+1];
				r[j] = k;
			}
			for(int j = 1; j <= m; j++)
				ans = max(h[i][j] * (r[j] - l[j] + 1), ans);
		}
		printf("%d\n", ans * 3);
		if(kase) memset(mp, 0, sizeof mp), memset(h, 0, sizeof h);
	}
	return 0;
}
```

### Solution2 前缀和 二分

对于 dp 中的 $l,r$ 函数，我们思考，从第 $j$ 列往左到第 $l$ 列都畅通无阻，而第 $l$ 列再往左寸步难行，符合二分特性。即若以 $(i-h_{i,j}+1,l)$ 为左上角，$(i,j)$ 为右下角的矩形全是空地，那么这个 $l$ 是合法的。

那么如何快速判断以 $(x_1,y_1)$ 为左上角，以 $(x_2,y_2)$ 为右下角的矩形是否全是空地呢？对 $mp$ 数组求前缀和记为 $s$。若 $s_{x_2,y_2}-s_{x_1-1,y_2}-s_{x_2,y_1-1}+s_{x_1-1,y_1-1}$ 为 $0$，则该矩形全是空地。复杂度$O(n^2\log n)$。实测 80ms。

mps 大牛提供了一种简短有力的二分写法，借鉴倍增的思路。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 1005;
int kase, n, m, l, r, mid, h[maxn][maxn], mp[maxn][maxn], s[maxn][maxn];
bool judge(int xi, int yi, int xj, int yj) {
	return !(s[xj][yj] - s[xi-1][yj] - s[xj][yi-1] + s[xi-1][yi-1]);
}
int main() {
	scanf("%d", &kase);
	while(kase--) {
		scanf("%d %d", &n, &m);
		char c[2];
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) {
				scanf("%s", c);
				if(c[0] == 'R') mp[i][j] = 1;
				else h[i][j] = h[i-1][j] + 1;
				s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + mp[i][j];
			}
		int ans = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) {
				if(mp[i][j]) continue;
				//二分开始
				int l = j;
				for(int k = 1 << 10; k; k >>= 1)
					if(l - k >= 1 and judge(i-h[i][j]+1, l-k, i, j)) l -= k;
				int r = j;
				for(int k = 1 << 10; k; k >>= 1)
					if(r + k <= m and judge(i-h[i][j]+1, j, i, r+k)) r += k;
				//二分结束
				ans = max(h[i][j] * (r - l + 1), ans);
			}
		printf("%d\n", ans * 3);
		if(kase) memset(mp, 0, sizeof mp), memset(s, 0, sizeof s), memset(h, 0, sizeof h);
	}
	return 0;
}
```

若不喜欢，用平常的二分写法亦可，速度相近。

```cpp
//二分开始
l = 1, r = j;
while(l <= r)
	if(judge(i-h[i][j]+1, mid=(l+r)>>1, i, j)) r = mid - 1;
	else l = mid + 1;
int lef = l;
l = j, r = m;
while(l <= r)
	if(judge(i-h[i][j]+1, j, i, mid=(l+r)>>1)) l = mid + 1;
	else r = mid - 1; 
int rig = r;
//二分结束
```

### Solution3 单调栈

单调栈是复杂度最低的做法。维护一个 $h$ 值递增的单调栈。单调栈用 `pair` 即可，存高度 $h$ `first` 和宽度 $w$ `second`。

弹出时再计算该元素能向左走多少，被弹出时，说明栈顶元素已经不可能再向右走，栈顶元素的高度 $h$ 记为储存的 `first`，宽度 $w$ 为 **这一轮中** **此前所有（包括自身）** 出栈元素的 `second` 之和。

入栈元素 $w_{i}=\sum w_{j} + 1$，$j$ 为 $i$ 入栈时弹出的每个元素。

复杂度 $O(n^2)$，实测 10ms。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1005;
typedef int array[maxn][maxn];
array map, h;
int CASE, n, m, top;
pair<int, int> s[maxn];
int main() {
	scanf("%d", &CASE);
	while(CASE--) {
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) {
				char c; do c = getchar(); while(c != 'R' and c != 'F');
				if(c == 'F') map[i][j] = 1;
			}
		int ans = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(map[i][j]) h[i][j] = h[i-1][j] + 1;
		for(int i = 1; i <= n; i++) {
			s[top = 1] = make_pair(h[i][1], 1);
			for(int j = 2; j <= m; j++) {
				int w = 0;
				while(top and h[i][j] <= s[top].first)
					ans = max(s[top].first * (w += s[top--].second), ans);
				s[++top] = make_pair(h[i][j], w + 1);
			}
			int w = 0;
			while(top) ans = max(s[top].first * (w += s[top--].second), ans);
		}
		printf("%d\n", ans * 3);
		if(CASE) memset(map, 0, sizeof map), memset(h, 0, sizeof h);
	}
	return 0;
}
```

---

## 作者：LG_kemeng (赞：4)

# 没学过单调栈，也不想写dp的看过来
这边给出一个不需要前缀知识的方法。

首先，题目求的是矩形，数据范围 $n \leq 10^3$ ，复杂度 $O(n^2)$ 即可通过，那考虑对矩阵暴力遍历，每个节点保存 $l$， $r$， $h$ 三个数据。 $l$ 表示同行内该节点左侧离该节点最远的非 $R$ 节点， $r$ 同理。 $h$ 表示该节点的最高高度。那么对于每个节点，可以如下更新：
```cpp
l[i][j] = max(nearl+1,l[i-1][j]);
r[i][j] = min(r[i-1][j],nearr-1);
h[i][j] = h[i-1][j] + 1;
```
然后再暴力遍历一遍，跑一个 `h[i][j]*(r[i][j]-l[i][j]+1)` 的最大值就行了。坑点： $ans$ 要 $\times$ 3 。

AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T> inline void read(T &x){x=0;register int f=1;register char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}x*=f;}
template<typename T,typename ...Args> inline void read(T &x,Args &... y){read(x);read(y...);}
int h[1005][1005],l[1005][1005],r[1005][1005],a[1005][1005];
signed main(void)
{
	register int _;read(_);
	while(_--)
	{
		memset(a,0,sizeof a);
		register int n,m;read(n,m);
		register char c;
		for(register int i=1;i^(n+1);i++)
		{
			for(register int j=1;j^(m+1);j++)
			{
				c=getchar(); while(c!='F'&&c!='R') c=getchar();
				a[i][j]=c=='F'?1:0;
			}
		}
		register int ans=0;
		for(register int i=1;i^(m+1);i++) r[0][i]=0x3f3f3f3f;
		for(register int i=1;i^(n+1);i++)
		{
			register int cl=0,cr=m+1;
			for(register int j=1;j^(m+1);j++)
			{
				if(a[i][j])
				{
					h[i][j]=h[i-1][j]+1;
					l[i][j]=max(cl+1,l[i-1][j]);
				}
				else
				{
					h[i][j]=l[i][j]=0;
					cl=j;
				}
			}
			for(register int j=m;j^0;j--)
			{
				if(a[i][j])
				{
					r[i][j]=min(r[i-1][j],cr-1);
					ans=max(ans,h[i][j]*(r[i][j]-l[i][j]+1));
				}
				else
				{
					r[i][j]=n+1;
					cr=j;
				}
			}
		}
		printf("%d\n",ans*3);
	}
	return 0;
}
/*
　　　　　／＞　 フ
　　　　　| 　_　 _|
　 　　　／`ミ _x 彡
　　 　 /　　　 　 |
　　　 /　  ヽ　　 ?
　／￣|　　 |　|　|
　| (￣ヽ＿_ヽ_)_)
　＼二つ
*/
```

---

## 作者：Doubeecat (赞：2)

> [UVA1330 City Game](https://www.luogu.com.cn/problem/UVA1330)
> 
> 有 $k$ 片土地，每片土地被分成 $n \times m$ 个格子，每个格子里写着 `R` 或者 `F`.
> 
> 对于每片土地，找一块矩形土地，要求这片土地都标着 `F` 并且面积最大。
> 
> $n,m \leq 10^3$

## 解题思路

单调栈/悬线法

类似这类有障碍点找最大矩形的题显然可以用悬线法来做，不过这题里是大材小用。

其实这题是[这题](https://www.luogu.com.cn/problem/SP1805)的变式，一时没有思路可以看下上面那题。

考虑怎么构成一个极大矩形，发现一个矩形实际上可以按照行拆分成一条一条的，比如这样。

```
FFF    F F F
FFF => F F F
FFF    F F F
       1 2 3
```

所以这就启发我们，对于每一个格子，可以先将其上边连续的 `F` 数量处理出来，记作 $h_{i,j}$，这里可以采用递推。

若 $a_{i,j}$  $=$ `F`，则 $h_{i,j} = h_{i-1,j} + 1$ 

否则 $h_{i,j} = 0$ 

我们在读入时预处理就能做到。

```cpp
cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        for (int j = 1;j <= m;++j) {
            cin >> g[i][j];
            if (g[i][j] == 'F') h[i][j] = h[i-1][j] + 1;
        }
    }
```

这样，我们就把问题拆分成了每一行上单独的[这题](https://www.luogu.com.cn/problem/SP1805)，我们对于每一行跑一遍单调栈就解决了。

具体地说，我们现在对于一堆矩形，要求出其最大面积。我们建立两个栈，一个用来表示高度，一个用来表示宽度。从左到右扫描每个矩形：
- 若当前矩形比栈顶矩形的高度高，直接进栈。
- 反之，不断取出栈顶直到当前矩形比栈顶矩形的高度大。注意在出栈过程中，这些矩形也是有用的。我们考虑取他们的公共部分，也就是累加他们的宽度之和，并且用每个矩形的高度乘上累计宽度取更新答案。在这个过程结束后，我们就把当前高度与累计宽度的矩形再进栈。

整个过程结束之后，我们要将栈排空，这里我们可以直接添加一个高度为 $0$ 的矩形方便实现，写成代码也就是

```cpp
stack <int> s1,s2;

int work(int x) {
    int ans = 0;
    while (!s1.empty()) s1.pop();//清空两个栈
    while (!s2.empty()) s2.pop();
    s1.push(0);s2.push(0);//保证不访问空栈
    for (int i = 1;i <= m + 1;++i) {
        int now = h[x][i];//当前位置最大的 F 连续高度
        if (now > s1.top()) {s1.push(now),s2.push(1);}//直接进栈的情况
        else {
            int wid = 0;
            while (!s1.empty() && now < s1.top()) {
                wid += s2.top();//累加高度
                ans = max(ans,wid * s1.top();//更新答案
                s1.pop(),s2.pop();
            }
            s1.push(now),s2.push(wid+1);//最后入栈
        }
    }
    return ans;
}
```

对于每一行，我们都执行一个这样的过程

```cpp
int ans = 0;
for (int i = 1;i <= n;++i) ans = max(ans,work(i));    
```

时间复杂度 $O(nm)$

## 代码

```cpp
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
#define ll long long
#define ri register int

char buf[1 << 20], *p1, *p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)?EOF: *p1++)
inline int read() {
	ri v = getchar();int f = 1,t = 0;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {t = t * 10 + v - 48;v = getchar();}
	return t *= f;
}

const int N = 1e3+10;

int n,m,h[N][N];

char g[N][N];

stack <int> s1,s2;

int work(int x) {
    int ans = 0;
    while (!s1.empty()) s1.pop();
    while (!s2.empty()) s2.pop();
    s1.push(0);s2.push(0);
    for (int i = 1;i <= m + 1;++i) {
        int now = h[x][i];
        if (now > s1.top()) {s1.push(now),s2.push(1);}
        else {
            int wid = 0;
            while (!s1.empty() && now < s1.top()) {
                wid += s2.top();
                ans = max(ans,wid * s1.top());
                s1.pop(),s2.pop();
            }
            s1.push(now),s2.push(wid+1);
        }
    }
    return ans;
}

void solve() {
    memset(h,0,sizeof h);
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        for (int j = 1;j <= m;++j) {
            cin >> g[i][j];
            if (g[i][j] == 'F') h[i][j] = h[i-1][j] + 1;
        }
    }
    int ans = 0;
    for (int i = 1;i <= n;++i) ans = max(ans,work(i));
    printf("%d\n",ans * 3);
}

signed main() {
    int T;cin >> T;
    while (T--) solve();
	return 0;
}
```

---

## 作者：saixingzhe (赞：1)

# 分析

我们枚举横着每条边，提出所有的 `F`，把他们合起来，会发现形成了一个类似柱形图的东西，我们枚举每个柱左右第一个比它矮的柱，然后记录这个矩阵大小即可。

还有一道和这题一样但没有多测的题 [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1002][1002],f[1002],L[1002],R[1002],ans,T;
char c;
int main(){
	cin>>T;
	while(T--){
		ans=0;
		memset(f,0,sizeof(f));
		memset(L,0,sizeof(L));
		memset(R,0,sizeof(R));
		scanf("%d%d",&n,&m); 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>c;
				if(c=='F')	a[i][j]=1; 
				else	a[i][j]=0;
			}
		} 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j])	f[j]++;
				else	f[j]=0;
			}
			stack <int> s;
			for(int j=1;j<=m;j++){
				while(!s.empty()&&f[s.top()]>=f[j])	s.pop();
				if(s.empty())	L[j]=0;
				else	L[j]=s.top();
				s.push(j);
			}
			while(!s.empty())	s.pop();
			for(int j=m;j>=1;j--){
				while(!s.empty()&&f[s.top()]>=f[j])	s.pop();
				if(s.empty())	R[j]=m+1;
				else	R[j]=s.top();
				s.push(j);
			}	
			for(int j=1;j<=m;j++)	ans=max(ans,f[j]*(R[j]-L[j]-1));
		} 
		printf("%d\n",ans*3); 
	}
	return 0;
}
```
**多测一定清干净！**

---

## 作者：Jeremiahy (赞：1)

## 分析

如果采用暴力枚举，时间复杂度是 $O(m^3n^3)$，考虑使用扫描线。

我们把每个格子向上延伸的连续空格看成一条悬线，并且用 $up_{i,j}$、$left_{i,j}$、$right_{i,j}$ 表示格子 $(i,j)$ 的悬线长度以及该悬线向左、向右运动的运动极限。

![](https://cdn.luogu.com.cn/upload/image_hosting/1nfghjmi.png)

如图所示。列 $3$ 的悬线长度为 $3$，向左、向右各能运动一列，因此向左、向右的运动极限分别为列 $2$ 和列 $4$。

这样，每个格子 $(i,j)$ 对应着一个以第 $i$ 行为下边界、高度为 $up_{i,j}$，左右边界分别为 $left_{i,j}$ 和 $right_{i,j}$ 的矩形。不难发现，所有这些矩形中面积最大的就是题目所求。

下面考虑如何快速求出以上 $3$ 种信息。当第 $i$ 行第 $j$ 列不是空格时，$3$ 个数组的值均为 $0$，否则 $up_{i,j}=up_{i-1,j}+1$。那么，$left$ 和 $right$ 呢？深入思考后，可以发现 $left_{i,j}=\max\{left_{i-1,j},lo+1\}$其中，$lo$ 是第 $i$ 行中，第 $j$ 列左边的最近障碍格的列编号。如果从左到右计算 $left_{i,j}$，则很容易维护 $lo$。$right$也可以同理计算，但需要从右往左计算，因为要维护第 $j$ 列右边最近的障碍格的列编号 $ro$。

为了节约空间，我们的程序用 $up_j$，$left_j$ 和 $right_j$ 来保存当前扫描行上的信息。

#### 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int mat[1003][1003], up[1003][1003], left[1003][1003], right[1003][1003], T, m, n;
signed main () {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &m, &n);
		for (register int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				int ch = getchar();
				while (ch != 'F' && ch != 'R') ch = getchar();
				mat[i][j] = ch == 'F' ? 0 : 1; //记录地图
			}
		int ans = 0;
		for (register int i = 0; i < m; i++) {
			int lo = -1, ro = n;//初始化
			for (int j = 0; j < n; j++)
				if (mat[i][j] == 1)//不是空地
					up[i][j] = left[i][j] = 0, lo = j;
				else 
					up[i][j] = i == 0 ? 1 : up[i - 1][j] + 1, left[i][j] = i == 0 ? lo + 1 : max(left[i - 1][j], lo + 1); //计算up，left
			for (register int j = n - 1; j >= 0; j--)
				if (mat[i][j] == 1)
					right[i][j] = n, ro = j;
				else
					right[i][j] = i == 0 ? ro - 1 : min(right[i - 1][j], ro - 1), ans = max(ans, up[i][j] * (right[i][j] - left[i][j] + 1));//计算right，ans
		}
		printf("%d\n", ans * 3);
	}
	return 0;
}
```

注：本博客借用蓝书中的思路进行讲解。


---

## 作者：风羽跃 (赞：1)

### 题意简述：

给你一个 RF 矩阵，求只含 F 的最大子矩阵。

#### [题目传送门](https://www.luogu.com.cn/problem/UVA1330)

### 题目分析：

啥叫 RF 矩阵？不就是 $01$ 矩阵嘛。

找一个最大的 $0$ 子矩阵不就行了。

这道题限制条件很少，导致做法多种多样：单调栈、二分、扫描线、最大子矩阵……

我这里介绍一种 DP 的做法（比较经典）。

时间复杂度：$O(n\times m)$。

总体思路：求出每个点 $(i,j)$ 上的最大子矩阵,然后取最大值。

具体做法：

想象一下现在我们找到了一个值为 $0$ 的点，然后有一条线从该点出发,一直向上延伸，直至撞到 $1$ 为止，我们就得到了一条纵向的线段。

设该点 $(i,j)$，线段长度 $up(i,j)$，线段不断向左右两边扫，撞到1停止的左端点和右端点分别为 $lmx(i,j)$，$rmx(i,j)$，这个子矩阵大小就是 $up(i,j)\times(rmx(i,j)-lmx(i,j)+1)$。

关键在于如何求出 $lmx(i,j)$ 和 $rmx(i,j)$。

$O(n\times m)$ 地预处理出每个单点最远能到达的左右端点，在自上而下 DP 时用每个点上面的点的左右端点去更新它自己的左右端点（此时这个点的所谓“左右端点”就变成了它所代表线段所能到达的左右边界），如果是 $lmx$ 就取 $\max$，$rmx$ 就取 $\min$，这样就能在二维时间复杂度内求出线段的左右端点了。

### AC代码（含注释）：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>

#define maxn 1005

using namespace std;

int n,m,lmx[maxn][maxn],rmx[maxn][maxn],up[maxn][maxn];
int ans;
char mp[maxn][maxn];

int main()
{
	int T;
	cin>>T;
	while(T--){
		ans=0;
		cin>>n>>m;
		memset(lmx,0,sizeof(lmx));
		memset(rmx,0,sizeof(rmx));
		memset(up,0,sizeof(up));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>mp[i][j];
				if(mp[i][j]=='F'){
					lmx[i][j]=rmx[i][j]=j;//初值就是它自己
					up[i][j]=1;//同上
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=2;j<=m;j++){//别忘了j要从2开始 
				if(mp[i][j-1]=='F'&&mp[i][j]=='F')
                	lmx[i][j]=lmx[i][j-1];//预处理出单点的左右端点 
			}
			for(int j=m-1;j>=1;j--){
				if(mp[i][j+1]=='F'&&mp[i][j]=='F')
					rmx[i][j]=rmx[i][j+1];
			}
		}
		for(int i=2;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(mp[i-1][j]=='F'&&mp[i][j]=='F'){//如果上面的点能过来 
					lmx[i][j]=max(lmx[i][j],lmx[i-1][j]);//更新当前线段左边界 
					rmx[i][j]=min(rmx[i][j],rmx[i-1][j]);//更新当前线段右边界 
					up[i][j]=up[i-1][j]+1;//更新线段长 
				}
				ans=max(ans,up[i][j]*(rmx[i][j]-lmx[i][j]+1));
				//不管能不能顺下来都要更新答案
			}
		}
		cout<<ans*3<<endl;//别忘了乘3!!! 
	}
	return 0;
}
```


---

## 作者：luminouris (赞：1)

这道题相当于求出F构成最大矩阵的面积，分析数据规模可得最多用时间复杂度为
O(n²)，可用单调栈或扫描线方法。
我们这里尝试扫描线；
  首先用d数组记录矩形高度读入字符串若为F则高度+1；
  若为R则高度为0；
  注意需将d全部赋值为0否则会出边界；
  

```c++
		for(int i=1;i<=n;i++)
		 { 
		 	for(int j=1;j<=m;j++)
		 	{
		 		cin>>c;
		 		if(c=='F')
		 			d[i][j]=d[i-1][j]+1; 
		 		else d[i][j]=0; 	
		 	}
			
		 }
```
第一步输入并从上往下递推求出高。
```c++
        for(int i=1;i<=n;i++)
        {
            d[i][0]=d[i][m+1]=-1;
            l[1]=1;
            r[m]=m;
            for(int j=2;j<=m;j++)
            {
                l[j]=j;
                while(d[i][j]<=d[i][l[j]-1])
                l[j]=l[l[j]-1];
         }
            for(int j=m-1;j>=1;j--)
            {
                r[j]=j;
                while(d[i][j]<=d[i][r[j]+1])
                r[j]=r[r[j]+1];
             }
```
第二步
从左往右求出左值； 
左值用于记录左端点的位置；
如果该点数值比左边一个点的
数值小则该值左端点和左边那个点相同；
同理
从右往左求出右值
右值用于记录右端点的值
如果该点数值比左边一个点的数值小
则该值右值与右边那个端点相同；
```c++
for(int j=1;j<=m;j++)
 ans=max(ans,d[i][j]*(r[j]-l[j]+1));
```
第三步不离开i的循环，
左值减去右值乘以高即是该端点所在的高最大矩形
的面积从左往右遍历每一个点即可求出该行的最大
矩形面积。
完整代码如下：
```c++
#include<bits/stdc++.h>
using namespace std;
int l[1005],r[1005];
int d[1005][1005];
int main()
{

	char c;
	int T,ans=0;
	cin>>T;
	while(T--)
	{
		memset(l,0,sizeof(l));
		memset(r,0,sizeof(r));
		memset(d,0,sizeof(d));
		int m,n;
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		 { 
		 	for(int j=1;j<=m;j++)
		 	{
		 		cin>>c;
		 		if(c=='F')
		 			d[i][j]=d[i-1][j]+1; 
		 		else d[i][j]=0; 	
		 	}
			
		 }
	    for(int i=1;i<=n;i++)
        {
            d[i][0]=d[i][m+1]=-1;
            l[1]=1;
            r[m]=m;
            for(int j=2;j<=m;j++)
            {
                l[j]=j;
                while(d[i][j]<=d[i][l[j]-1])
                l[j]=l[l[j]-1];
            } 
            for(int j=m-1;j>=1;j--)
            {
                r[j]=j;
                while(d[i][j]<=d[i][r[j]+1])
                r[j]=r[r[j]+1];
            }
			for(int j=1;j<=m;j++)
 			ans=max(ans,d[i][j]*(r[j]-l[j]+1));	
		}
		cout<<ans*3<<endl;
	}
	return 0;
}```


---

## 作者：李尧 (赞：1)

本蒟蒻带来一个鬼畜的做法

什么单调栈啊，我不会【你还好意思说】

所以我带来一种耗时但是AC没问题的简单算法

emm，有没有觉得这题很眼熟呢

寻找最大的F矩阵的数目，然后乘三

其实我们可以把它看成是求最大子矩阵啊！！！

为了防止R影响，我们把有R的格子权值赋成负无穷【其实就是整型范围内最小值】，有F的格子赋成1，最后求得的子矩阵面积不就是我们要的最大F矩阵面积吗？？

以下代码

~~~
#include <bits/stdc++.h>
using namespace std;
long long int T,n,m,ans;
int a[1007][1007];
long long s[1007][1007];//注意要开long long 
char c;
int main(){
	scanf("%lld",&T);
	while(T--){
		memset(a,-127,sizeof(a));//清成负无穷
		memset(s,0,sizeof(s));
		ans=0;
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				scanf(" %c",&c);
				if(c=='F') a[i][j]=1;
				s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];//矩形前缀和
			}
		for(int i=1;i<=n;i++)//O（n^3）求最大子矩阵
			for(int j=i;j<=n;j++){
				long long int mn=0;
				for(int k=1;k<=m;k++){
					mn=min(mn,s[j][k]-s[i-1][k]);
					ans=max(ans,s[j][k]-s[i-1][k]-mn);
				}		
			}
		printf("%lld\n",3*ans);//输出乘三
	}
	return 0;
}
~~~
不要复制代码哦，本蒟蒻祝各位大佬AC

---

## 作者：Lyccrius (赞：0)

把每个格子向上延伸的连续空格看成一条悬线，并用 $\text{up} (i, j)$、$\text{left} (i, j)$、$\text{right} (i, j)$ 表示格子 $(i, j)$ 的悬线长度以及该选线向左、向右运动的 “运动极限”。

每个格子 $(i, j)$ 对应着一个以 $i$ 行为下界、高度为 $\text{up} (i, j)$，左右边界分别为 $\text{left} (i, j)$ 和 $\text{right} (i, j)$ 的矩形。这些矩形中面积最大的就是题目所求。

当第 $i$ 行第 $j$ 列不是空格时，$3$ 个数组的值均为 $0$，否则 $\text{up} (i, j) = \text{up} (i - 1, j) + 1$，$\text{left} (i, j) = \max \{ \text{left} (i - 1, j), \text{lo} + 1 \}$。其中 $\text{lo}$ 是第 $i$ 行中，第 $j$ 列左边的最近障碍格的编号。$\text{right}$ 也可以同理计算，但需要从右往左计算，因为要维护第 $j$ 列右边最近的障碍格的列编号 $\text{ro}$。

时空复杂度均为 $\mathcal{O} (m n)$。

```
#include <cstdio>
#include <algorithm>

const int maxN = 1000 + 10;

int K;
int M, N;
int city[maxN][maxN];

int up[maxN][maxN];
int left[maxN][maxN];
int right[maxN][maxN];

int main() {
    scanf("%d", &K);
    for (int kase = 1; kase <= K; kase++) {
        scanf("%d%d", &M, &N);
        for (int i = 1; i <= M; i++) for (int j = 1; j <= N; j++) {
            char ch;
            scanf(" %c", &ch);
            while (ch != 'F' && ch != 'R') scanf(" %c", &ch);
            if (ch == 'F') city[i][j] = 0;
            else city[i][j] = 1;
        }
        int ans = 0;
        for (int i = 1; i <= M; i++) {
            int lo = 0;
            int ro = N + 1;
            for (int j = 1; j <= N; j++) if (city[i][j]) {
                up[i][j] = 0;
                left[i][j] = 0;
                lo = j;
            } else if (i == 1) {
                up[i][j] = 1;
                left[i][j] = lo + 1;
            } else {
                up[i][j] = up[i - 1][j] + 1;
                left[i][j] = std::max(left[i - 1][j], lo + 1);
            }
            for (int j = N; j >= 1; j--) if (city[i][j]) {
                right[i][j] = N;
                ro = j;
            } else if (i == 1) {
                right[i][j] = ro - 1;
                ans = std::max(ans, up[i][j] * (right[i][j] - left[i][j] + 1));
            } else {
                right[i][j] = std::min(right[i - 1][j], ro - 1);
                ans = std::max(ans, up[i][j] * (right[i][j] - left[i][j] + 1));
            }
        }
        printf("%d\n", ans * 3);
    }
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

### 前置知识
[单调栈](https://oi-wiki.org/ds/monotonous-stack/)，是一种线性的数据结构，通常用栈或数组模拟实现。顾名思义，就是保持单调性的栈，通常使用的是单调递增以及单调递减的单调栈，递增和递减都是指从栈底到栈顶的顺序，它的模板有如下：视野总和、求最大区间、直方图中最大的矩形等。因为每个元素入队一次，出队一次，所以总的复杂度为 $O(n)$。所以本题单调栈是可行的，复杂度为 $O(nm)$。
***
首先，存储前缀和为 $sum_{i,j}$ 表示到达第 $(i,j)$ 个位置的连续的 `F` 的个数，然后我们构建一个单调递增栈，以 `sum` 升序排列，求出最左边可以影响的点 $l_i$，以及最右边可以影响的点 $r_i$。从贪心的角度，我们肯定要去到我们可以取到的最左和最右。由此，该矩阵长为 $r_i-l_i+1$，宽为 $sum_{i,j}$。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,sum[1005][1005],ans,l[1005],r[1005],t;
stack<int> stk;
signed main(){
	scanf("%lld",&t);
	for(int i=1;i<=t;i++){//多组测试数据
		scanf("%lld%lld",&n,&m);
		ans=-2e9;//初始化为极小值
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				l[j]=r[j]=0;
				char s;
				cin>>s;
				if(s=='F')
					sum[i][j]=sum[i-1][j]+1;//前缀和
				else
					sum[i][j]=0;			
			}
			stk.push(1);
			for(int j=2;j<=m;j++){
				int x=stk.top();
				while(sum[i][x]>sum[i][j]&&!stk.empty()){
					stk.pop();
					r[x]=j-1;
					if(stk.empty())
						break;
					x=stk.top();
				}
				stk.push(j);
			}
			while(!stk.empty()){
				int x=stk.top();
				stk.pop();
				r[x]=m;
			}
			stk.push(m);
			for(int j=m-1;j>=1;j--){
				int x=stk.top();
				while(sum[i][x]>sum[i][j]&&!stk.empty()){
					stk.pop();
					l[x]=j+1;
					if(stk.empty())
						break;
					x=stk.top();
				}
				stk.push(j);
			}	
			while(!stk.empty()){
				int x=stk.top();
				stk.pop();
				l[x]=1;
			}//单调栈的模板
			for(int j=1;j<=m;j++)
				ans=max(ans,(r[j]-l[j]+1)*sum[i][j]);//求最大
		}
		printf("%lld\n",ans*3);//注意乘3
	}
	return 0;
}
```

---

## 作者：rhyyy1 (赞：0)

一道思维好题。

可以用前缀和+二分的做法，复杂度 $(n^2logn)$。

这里推荐一种复杂度更小的算法——单调栈。

这里推荐先做一下[SP1805](https://www.luogu.com.cn/problem/SP1805)。

有了对单调栈的基础了解，开始解决这道题。

分别以前 $i$ 排为操作对象，处理出每列上的最大高度，注意排是横向的，并且每次最大高度的前提是与第 $i$ 排相接。

然后就用[SP1805](https://www.luogu.com.cn/problem/SP1805)的办法解决每个子问题就可以了。复杂度 $O(n^2)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+50;
char c[N][N];
int a[N][N];
struct node{
	int id,h;
}sta[N];
void solve(){
	int n,m,ans=0; cin>>n>>m;
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
		    cin>>c[i][j];
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
	        if(c[i][j]=='R') a[i][j]=0;
	          else a[i][j]=a[i-1][j]+1;
	for(int i=1;i<=n;i++){
		int top=0;
		for(int j=1;j<=m;j++){
			if(sta[top].h<=a[i][j]||top==0){
			    sta[++top].id=j; sta[top].h=a[i][j];
			}else{
				int now=0;
			    while(sta[top].h>a[i][j]){
			        ans=max(ans,sta[top].h*(j-sta[top].id));
			        now=sta[top].id;
					top--;
				}
			    sta[++top].id=now; sta[top].h=a[i][j];
			}
		}
		while(top>0){
			ans=max(ans,sta[top].h*(m+1-sta[top].id));
			top--;
		}
	}
	printf("%d\n",ans*3);
}
int main(){
	ios::sync_with_stdio(false); 
	cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--) solve();
}
```


---

## 作者：Gorenstein (赞：0)

## 题目大意

- [PDF链接](https://onlinejudge.org/external/13/p1330.pdf)
- [洛谷题面链接](https://www.luogu.com.cn/problem/UVA1330)

多组测试数据，每组测试数据给出一个 $n\times m$ 的矩形，其中有些位置标上了`F`。求一个最大面积的矩形，使覆盖到的位置中不含`F`。$n,m\leqslant 10^3$。

## 解题思路

说白了就是在一个矩形里面找到一个不覆盖含`F`格子最大的矩形。

我们发现，对于左边的一条边处在同一列的所有不包含`F`矩形，其右边处在的列是能够求出来的。因此我们可以求出任意一列，在从上往下每一个位置中能够到达的最右边位置。

然后对于左边同处于这一列的这些矩形，我们要求出其最大的覆盖面积。于是对于同一列，问题简化为了每一个位置往右都有限制，找到面积最大的矩形。然后发现这就是一个[SP1805](https://www.luogu.com.cn/problem/SP1805)。这个是可以直接用单调栈维护的。

然后当我们求出了以每一列为左边的那条边的矩形的最大面积之后，将这些列各自的答案取个 $\max$ 即可。

这样做法的正确性在于，我们计算每一列的时候，将所有的以这一列为左边的矩形都算了进去。因此是不会遗漏的。

单列用单调栈维护，每个位置最多进栈出栈一次，时间复杂度为 $O(n)$；总共 $m$ 列，时间复杂度为 $O(nm)$。

```cpp
while(t--){
	memset(a,0,sizeof(a));
	ans=0,n=read(),m=read();
	for(int i=1;i<=n;i++){
		int R=0;
		for(int j=1;j<=m;j++){
			char c[5],ch;
			cin>>c;ch=c[0];
		    if(ch=='R'){
				for(int k=R+1;k<j;k++)
					a[i][k]=j-k;
				R=j;
			}
			else if(j==m)
			    for(int k=R+1;k<=j;k++)
					a[i][k]=j-k+1;
		}
	}
	int now=0;
	for(int i=1;i<=m;i++){
		memset(s,0,sizeof(s));
		memset(w,0,sizeof(w));
		a[n+1][i]=p=0;
		for(int j=1;j<=n+1;j++)
			if(a[j][i]>s[p])
				s[++p]=a[j][i],w[p]=1;
			else{
				int width=0;
				while(s[p]>a[j][i])
					width+=w[p],now=max(now,width*s[p]),p--;
				s[++p]=a[j][i],w[p]=width+1;
			}
		ans=max(ans,now);
	}
	printf("%d\n",ans*3);
}
```

---

## 作者：Rye_Catcher (赞：0)

- 题目链接：https://www.luogu.org/problemnew/show/UVA1330

- 思路：

  ### 单调栈
  
  如果不知道这是什么可以先做[这道题](https://www.luogu.org/problemnew/show/SP1805)和看看本蒟蒻的博客：
  
  https://www.luogu.org/blog/Rye-Catcher/solution-sp1805
  
  或者到网上搜其他dalao的博客
  
  如果你知道单调栈的思路，那么就不难想了。
  
  刚刚链接里的那道题是在一根数轴上单调栈，那么在这道题中我的思路就是把每纵行看做一个数轴，以向右为正方向，数轴上每个横行对应每个点记录从这开始向右最多有几块空地（就好比是链接中矩形高度），用单调栈思路一根一根数轴的处理，不断更新最大值。
  
  单调栈具体实现跟链接中那道题几乎一样，唯一难题就是怎样预处理向右拓展的最多空地数，好吧其实这也不是最难之处。
  
  我们对于每一横行输入搞一个last记录上一个R的位置，先初始last=0,然后如果接下来在j处读到了一个R，就遍历last+1到j-1的空地，把下标为k（从1开始数第k个）的空地数赋值为j-k(在纸上画一画其实很容易理解),再把last设为j。注意，我们还要在越界处进行一次操作。
  
  如果上面看不懂就看代码吧，如果弄清链接那道题其实代码很好懂。
  
- Tips:

  ### 毒瘤输入  毒瘤输入  毒瘤输入
  搞这输入跟我从想题到打完代码时间一样长。
  
  POJ discuss区中甚至有人反映数据输出可能不严格按照要求（例如：两个字符间有多个空格）建议用cin读入。
  
- 代码：

```
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <algorithm>
#define ri register int 
using namespace std;
int n,m,t,anss=0;
int city[1010][1010];
template <class T>inline void read(T &x){
	x=0;char c;int neg=0;
	while(!isdigit(c=getchar()))neg=c=='-';
	x=c-48;
	while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
	x=neg?-x:x;
}
inline int solve(int r){  //单调栈
	int w[1005],s[1005],p,ans=0;
	city[n+1][r]=p=0;
	for(ri i=1;i<=n+1;i++){
		if(city[i][r]>s[p]){
			s[++p]=city[i][r];
			w[p]=1;
		}
		else {
			int wid=0;
			while(s[p]>city[i][r]){
				wid+=w[p];
				ans=max(ans,wid*s[p]);
				p--;
			}
			if(city[i][r])s[++p]=city[i][r],w[p]=wid+1;
		}
	}
	return ans;
}
int main()
{
	char ch;string sp;
	cin>>t;
	while(t--){
	    anss=0;
		read(n),read(m);
		for(ri i=1;i<=n;i++){
			int last=0;     
			for(ri j=1;j<=m;j++){
			    cin>>sp;ch=sp[0]; //毒瘤输入
			     if(ch=='R'){ 
					for(ri k=last+1;k<j;k++){//预处理
						city[i][k]=j-k;
					}
					last=j;
				}
				else if(j==m){//注意这个操作必不可少
				    for(ri k=last+1;k<=j;k++){
						city[i][k]=j-k+1;
					}
				}
			}
		//	putchar('\n');
		}
		for(ri i=1;i<=m;i++){//注意n,m的区别
			anss=max(anss,solve(i));
		}
		memset(city,0,sizeof(city));
		cout<<anss*3<<endl;
	}
	return 0;
}
```

代码效率较高，不过我很佩服10ms，POJ0ms的大佬们

---

