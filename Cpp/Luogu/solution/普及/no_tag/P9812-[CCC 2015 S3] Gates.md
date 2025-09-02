# [CCC 2015 S3] Gates

## 题目描述

机场有 $n$ 个登机口，你需要按顺序安排 $m$ 架飞机，第 $i$ 架飞机只能使用 $1 \sim g_{i}$ 号登机口，一个登机口永久只能被一架飞机使用。**当没有登机口可以供某架飞机使用时机场便会关闭，之后的飞机都不能登机。**

请确定一种方案，使得有登机口的飞机数量最多。

## 说明/提示

**【数据范围】：**

对于 $40\%$ 的数据，$1 \leq n,m \leq 2 \times 10^{3}$。

对于 $100\%$ 的数据，$1 \leq n,m \leq 10^{5}$，$1 \leq g_{i} \leq n$。

本题中 Subtask 0 为原题数据，Subtask 1 为 Hack 数据，Hack 数据不计分。

## 样例 #1

### 输入

```
4
3
4
1
1```

### 输出

```
2```

## 样例 #2

### 输入

```
4
6
2
2
3
3
4
4```

### 输出

```
3```

# 题解

## 作者：Loser_Syx (赞：4)

有一个贪心策略：对于 $1 \sim g_i$ 的登机口，一定是选最靠近 $g_i$ 的那个没被使用的登机口。

具体来看看为什么，记刚刚那个数字为 $k$，对于 $g_j < k$ 的 $j$，$j$ 一定去不到那个登机口，对这个无影响，对于 $g_j > k$ 的 $j$，$j$ 的选择一定是比现在的 $i$ 要多的，而因为我们需要停的最多，所以要给 $i$ 留一个位置。

并查集维护最近的 $k$ 即可。

```cpp
const int N=1e5+19;
struct DSU {
	int f[N];
	void init(int n) {
		for (int i=1;i<=n;++i) f[i]=i;
	}
	int find(int x) {
		if (f[x]==x) return x;
		return f[x]=find(f[x]);
	}
	void merge(int x) {
		f[x]=find(x-1);
	}
} dsu;
signed main(){
	int n, m;
	read(n, m);
	dsu.init(n);
	for (int i=1;i<=m;++i) {
		int x=read();
		if (dsu.find(x)==0) return write(i-1,'\n'),0;
		dsu.merge(dsu.f[x]);
	}
	write(m,'\n');
	return 0;
}
```

---

## 作者：chaynflow (赞：4)

## Description

给定 $n$，有一个包含 $1\sim n$ 的集合 $A$，一共 $m$ 次每次给一个参数 $b$，表示需要删掉 $a$ 中一个 $\le b$ 的元素，不能操作后停下，问你最多能操作多少次。

$1 \le n,m \le 10^5, 1 \le b \le n$。

## Solution

显然每次删除满足 $c \le b$ 且最大的 $c \in A$。因为删掉一个小的可能会影响到后面的操作，不如删掉最大的。

set 维护一下即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
set <int> st;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, m, a;
    cin >> n >> m;
    st.insert(0); // 方便判是否不可选择
    for (int i = 1; i <= n; i++) st.insert(i);
    for (int i = 1; i <= m; i++)
    {
        cin >> a;
        set<int>::iterator it = (--st.upper_bound(a)); // 找最大的
        if (!(*it)) return cout << i - 1, 0; // 无法选输出当前个数 - 1
        st.erase(it); //删掉
    }
    cout << m; //所有都能上
	return 0;
}
```

---

## 作者：__Jared__ (赞：2)

温馨提示：本题水分严重超标，撑爆也就黄题，不必惊慌。

### 思路分析
---
首先考虑贪心，由于要求**有登机口的飞机数量最多**，故分配登机口的时候应当以择优为准，即优先选择在 $\in(0,g]$ 范围内最大的，同时用一个桶记录已经被占用的登机口，故有以下 TLE 100pts 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[100010];
int n,m,g,ans;
inline int read() //快读，可忽略
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline int write(int x)
{
    if(x<=9)
	{
        putchar(x+'0');
        return 0;
    }
    write(x/10);
    putchar(x%10+'0');
    return 0;
}
int main()
{
	n=read(),m=read();
	for(int i=0;i<m;i++)
	{
	    bool flag=0;
		g=read();
		for(int j=g;j>0;j--)
		{
			if(!vis[j]) 
			{
				vis[j]++,ans++,flag++;
				break;
			}
		}
		if(!flag) return write(ans);
	}
	return write(ans);
}
```

上述代码合计最坏复杂度在 $\Theta(mg)$ ，由于题目要求 $1\leq g\leq m\leq10^5$ 故 hack 数据超时。

考虑优化；对于第 $i$ 个登机口，始终满足其与前面所有登机口最多只能登 $i-1$ 个飞机，故可以建一个桶 $k$ ，其中 $k_i$ 表示可以登的飞机的最大值，只需要每次做出修改的时候维护桶 $k$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k[100010],g,pos,sasa;
inline int read() //快读 
{
	int a=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') if(ch=='-') f=-f,ch=getchar();
	while(ch>='0'&&ch<='9') a=a*10+ch-'0',ch=getchar();
	return a*f;
}
int get_pos(int g_)
{
	if(to[g_]==g_) return pos;
	return k[g_]=find(k[g_]); //更新桶 
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i) k[i]=i;
	for(int i=1;i<=m;++i)
	{
		g=read();
		pos=get_pos(g); //获取最新下标 
		if(!k[pos])
		{
			cout<<i-1;
			return 0;
		}
		--k[pos];
	}
	cout<<m;
}
```

时间复杂度 $\Theta(m+n)$ ，完美 Accept。

如果想要进一步优化的童鞋可以考虑树状数组和前缀和，这里懒得打了就不贴上来了。

---

## 作者：IkeveLand (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/P9812)

   #### 这道题其实换一个思路想就简单了咩：

- 我们可以倒着想，让每架飞机进入登机口时，除去已经进过飞机的。


- 但这道题的坑点就在于：**当没有登机口可以供某架飞机使用时机场便会关闭，之后的飞机都不能登机。(**~~也就是一棒子打死所有人~~),所以当  $1 \sim gi$   没有一个登机口时，机场也就关闭了




​

- 那么如何实现刚才所说的步骤呢，其实只要用一个自定义函数即可



### 代码如下：



```c
    int fuun (int u){
	if (s[u]==u) return u;
	return s[u]=fuun (s[u]);
    }
```






- 其中 $s[]$ 这个数组就代表 $1 \sim gi$ 中的所有登机口，只要在减去用过的即可，最后将这些整合起来可以了






 ## AC代码：
 
 ```c
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+14;
int n,m,as=0;
int s[N];
int fuun (int u){
	if (s[u]==u) return u;
	return s[u]=fuun (s[u]);
}
signed main ()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++) s[i]=i;
	while (m--){
		int g;
		cin>>g;
		if (fuun (g)!=0) s[s[g]]--;
		else break;//退出循环
		as++;//记录飞机数量
	} 
    
	cout<<as;
	return 0;
} 
```

---

## 作者：unknown_risk (赞：1)

## 题目大意
一架飞机能停 $1$ 到 $g_{i}$ 号登机口，当当前飞机没位置可停时，登机停止，求最多能停多少架飞机。
## 思路
### 50pts
每一遍暴力往前找，知道找到没被标记过的登机口。
### 100pts
我们可以优化这个找的过程，定义 $fa_{i}$ 为 $g_{i}$ 可以停编号最大且空闲的登机口，每次只要去寻找前一个空位即可，并统计编号满足 $[1,g_{i}]$ 停了多少架飞机，如果超出当前编号即输出答案，并退出循环。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,x,vis[N],fa[N];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i-1;
	for(register int i=1;i<=m;i++)
	{
		cin>>x;
		int pos=x;
		while(vis[x])x=fa[x];
		vis[x]++;
		fa[pos]=x-1;
		if(vis[x]>x)
		{
			cout<<i-1;
			return 0;
		}
	}
	cout<<m;
	return 0;
}
```



---

## 作者：ganyu1 (赞：0)

# P9812题解
## [题目传送门](https://www.luogu.com.cn/problem/P9812)
## 题意
每架飞机只能选择 $[1,g[i]]$ 中的登机口，登机口也只能匹配一架飞机，双向奔赴了属于是。直到有一架飞机没有空闲登机口可以匹配或者所有飞机都能匹配，输出能匹配登机口的最大飞机数量。不难看出，选择登机口的最优解是选择编号更大的空闲登机口。
## 第一次

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100001
using namespace std;
int n,m,g[N],d[N],ans;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>g[i];
	for(int i=1;i<=m;i++){
		while(d[g[i]]&&g[i]) g[i]--; 
		if(!g[i]) break;
		d[g[i]]=1;
		ans++;
	}
	cout<<ans;
	return 0;
}
```

纯暴力，原题数据都可以过，但最后一个 hack 点 TLE 了，显然需要优化。
## 第二次
定义数组 $fa$ 存储 $[1,g[i]]$ 中编号最大且空闲的登机口，若不存在则退出循环，此时的结果就是拥有停机口的最大飞机数量。
### AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100001
using namespace std;
int n,m,g[N],check[N],fa[N],ans;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) fa[i]=i-1;
	for(int i=1;i<=m;i++){
		cin>>g[i];
		int h=g[i];
		while(check[h]) h=fa[h];
		if(!h) break;
		fa[g[i]]=h-1;
		check[h]=1;
		ans++;
		
	}
	cout<<ans;
	return 0;
}
```
完结撒花

---

## 作者：COsm0s (赞：0)

感觉评绿高了。

每一架飞机的机场范围是 $1\sim g_i$，那么如果我们选择 $g_i$ 这一机场，对于后面的飞机影响是最小的。

但是问题是 $g_i$ 可能已经被用过了怎么办。

我们采用 set 维护还可以用的飞机场。在可以用的飞机场里选择一个最大的即可。

复杂度 $\Theta(m\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
set <int> st;
int n, m, x;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	st.insert(0);
	for (int i = 1; i <= n; i ++) st.insert(i);
	for (int i = 1; i <= m; i ++) {
		cin >> x;
		auto it = (-- st.upper_bound(x));
		if (!(*it)) return cout << i - 1, 0;
		st.erase(it);
	}
	cout << m << '\n';
	return 0;
}
```




---

## 作者：cosf (赞：0)

## [P9812](https://www.luogu.com.cn/problem/P9812)

题目中有一个限制：**当没有登机口可以供某架飞机使用时机场便会关闭，之后的飞机都不能登机**。

这个条件比较烦，我们来考虑如果没有这个条件答案会是多少。

我们可以用贪心。先对 $g$ 进行排序，然后从大到小依次对应登机口。具体来讲，一开始全部（$n$ 个）登机口都是可以用的，假设对于当前的 $g_i$，对应了该飞机之后最大号能放的登机口 $m$ 就等于 $\min\{m, g_i\} - 1$。

那么，加上这个条件又该如何呢？我们可以**二分答案**。二分一个答案 $mid$ 之后，只对前 $mid$ 个 $g$ 排一下序，然后跑一遍上面的模拟即可。放不完就说明这个 $mid$ 是不行的，否则即可行。

时间复杂度为 $O(n\log^2 n)$，虽然不是最优，但实现非常简单。~~毕竟数据范围就这么大，就是给我们用对数平方的方法做的。~~

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXM 100005

int n, m;
int g[MAXM];
int v[MAXM];

bool check(int x)
{
	copy(g + 1, g + x + 1, v + 1);
	sort(v + 1, v + x + 1); // 需要复制再排
	int j = n;
	for (int i = x; i; i--)
	{
		if (!j)
		{
			return false;
		}
		j = min(j, v[i]) - 1;
	}
	return true;
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> g[i];
	}
	int l = 1, r = m + 1; // 这个最大值理论上来说到 n + 2 就可以了，但不知道为什么这样会 wa
	while (l < r - 1)
	{
		int mid = (l + r) >> 1;
		if (check(mid))
		{
			l = mid;
		}
		else
		{
			r = mid;
		}
	}
	cout << l << endl;
	return 0;
}

```


---

