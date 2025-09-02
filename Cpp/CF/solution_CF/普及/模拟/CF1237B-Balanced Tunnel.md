# Balanced Tunnel

## 题目描述

Consider a tunnel on a one-way road. During a particular day, $ n $ cars numbered from $ 1 $ to $ n $ entered and exited the tunnel exactly once. All the cars passed through the tunnel at constant speeds.

A traffic enforcement camera is mounted at the tunnel entrance. Another traffic enforcement camera is mounted at the tunnel exit. Perfectly balanced.

Thanks to the cameras, the order in which the cars entered and exited the tunnel is known. No two cars entered or exited at the same time.

Traffic regulations prohibit overtaking inside the tunnel. If car $ i $ overtakes any other car $ j $ inside the tunnel, car $ i $ must be fined. However, each car can be fined at most once.

Formally, let's say that car $ i $ definitely overtook car $ j $ if car $ i $ entered the tunnel later than car $ j $ and exited the tunnel earlier than car $ j $ . Then, car $ i $ must be fined if and only if it definitely overtook at least one other car.

Find the number of cars that must be fined.

## 说明/提示

The first example is depicted below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237B/7d2f6b4d3eea560d8fb835871b9aa0fd74a81766.png)

Car $ 2 $ definitely overtook car $ 5 $ , while car $ 4 $ definitely overtook cars $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ . Cars $ 2 $ and $ 4 $ must be fined.

In the second example car $ 5 $ was definitely overtaken by all other cars.

In the third example no car must be fined.

## 样例 #1

### 输入

```
5
3 5 2 1 4
4 3 2 5 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
5 2 3 6 7 1 4
2 3 6 7 1 4 5
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2
1 2
1 2
```

### 输出

```
0
```

# 题解

## 作者：HHYQ_07 (赞：5)

# 题解

## 前言

这道题我们老师在暑假期末测评上出的第一题，考试时 $20$ 分钟直接暴切一遍过，现在来写一写考场上我的思路。

## 思路

看之前的题解大多都是 $O(n \log n)$ 的复杂度，但其实这里 $O(n)$ 就够了。我们先让数组 $a$ 倒序记录 $b$ 序列的每一个数在 $a$ 序列出现的顺序（请读者这里自行想一想为什么要倒序储存）。然后遍历一遍，维护一个最小值，每次和前面的最小值比较，如果最小值比它小，就说明此位前面至少有一个比它小的，就让答案加一，每次更新最小值。其实本质上就是求逆序对，只不过这里不是总数。

## ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n,a[N],b[N],x,ans,sum;
signed main()
{
//	freopen("car.in","r",stdin);
//	freopen("car.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		b[x]=i;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		a[n-i+1]=b[x];
	}	
	sum=a[1];
	for(int i=2;i<=n;i++)
	{
		if(sum<a[i])ans++;
		sum=min(sum,a[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：WsW_ (赞：4)

### 更新：
1. 2023/7/5根据要求删除了数字与汉字间的空格。  
2. 2023/7/9根据要求在数字和汉字间添加半角空格，完善内容，标题改为三级标题并在标题行前添加回车。

感谢指出错误！

### 思路  
先观察 样例 #1：  
如果没有一辆车超车，那么我们可以这样看：  
进去一个 $3$ 出来一个 $3$，进去一个 $5$ 出来一个 $5$。  
但实际情况是：  
进去一个 $3$ 出来一个 $4$，显然 $4$ 超车了。  
进去一个 $5$ 出来一个 $3$，但显然 $3$ 没有超车，因为它已经进去过了。  
我们可以发现，如果一辆车没有进去过，却出来了，那么它就超车了。  
于是，按顺序一个一个进，一个一个出，记录没有进去却出来的车的数量，就是答案。  
具体实现见代码注释。  

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int en[100005],ex[100005];//enter进入;exit出去
int t[100005];//统计谁已经出去了但没进来，后面它进来就不用管他，直接跳过
int sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&en[i]);
	int j=1;//j代表已经进到哪一个了
	for(int i=1;i<=n;i++){
		scanf("%d",&ex[i]);
		while(t[en[j]])j++;//如果一个车已经出去过了，那么后来进来的时候就跳过它
		if(ex[i]!=en[j]){//如果出来的不是进来的，出来的就超车了
			sum++;
			t[ex[i]]=1;//因为没进来直接出去了，所以之后这辆车会进来，统计一下，之后他进来跳过就好。
		}//如果进来的不是出来的，一直找到进来的出去为止，比它提前出去的都是超车，所以j不变
		else j++;//如果进来的是出来的，那就找下一个进来的
        //因为进来的的是出来的，所以不用统计，它之后不会再进来
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Awdrgysxc (赞：4)

## 【Analysis】

### 算法一
>先把车的先后顺序转化成进出的时间,问题就转化成了有多少个线段被其他线段完全覆盖,这就可以用主席树维护,时间复杂度$O(N\times log_2 \times N)$

### 算法二
>预处理出每辆车的出站顺序，再按入站顺序枚举车，当第$i$辆车的出站时间小于$1$~$i-1$辆车出站时间的最大值时,++ans,这个$Max$可以线性维护，总复杂度$O(N)$

## 【Code】
```cpp
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>
 
namespace IO
{
    inline char gc()
    {
        static char s[1<<20|1]={0},*p1=s,*p2=s;
        return (p1==p2)&&(p2=(p1=s)+fread(s,1,1<<20,stdin),p1==p2)?EOF:*(p1++);
    }
//	inline char gc() { return getchar(); }
	inline long long read()
	{
		long long ret=0;bool flag=0;char c=gc();
		while ((c<'0')|(c>'9')) flag ^= !(c^'-'),c=gc();
		while ((c>='0')&(c<='9')) ret=(ret<<1)+(ret<<3)+(c^'0'),c=gc();
		return flag?-ret:ret;
 	}
 	char OutputAns[1<<20|1],*OutputCur = OutputAns;
 	inline void output()
 	{
 		OutputCur -= fwrite(OutputAns,1,OutputCur - OutputAns,stdout);
	}
	inline void print(long long ans)
	{
		char s[20]={0};
		if (OutputCur - OutputAns + sprintf(s,"%I64d",ans) >> 20) output();
		OutputCur += sprintf(OutputCur,"%I64d",ans);
	}
	inline void printc(char c)
	{
		if (OutputCur - OutputAns + 1 >> 20) output();
		*(OutputCur++) = c;
	}
}
 
using IO::read;
using IO::print;
using IO::printc;
using IO::output;
 
typedef long long int64;
 
const int M = 2e5 + 11;
 
struct Tree { int ls, rs, sum; } T[M * 25];
 
struct Node { int l, r; bool operator < (const Node& x) const{ if (l != x.l) return l < x.l; return r < x.r; } } E[M];
 
int n, ans, tot;
 
int Rt[M];
 
inline void Build(int o = 1, int l = 1, int r = n + n)
{
	if (l == r) return ; int mid = l + r >> 1; T[o].ls = ++tot, T[o].rs = ++tot;
	Build(T[o].ls, l, mid), Build(T[o].rs, mid + 1, r);
}
 
inline void Insert(int pre, int now, int p, int l = 1, int r = n + n)
{
	if (l == r) { T[now].sum = T[pre].sum + 1; return ; } int mid = l + r >> 1;
	if (p <= mid)  T[now].ls = ++tot, T[now].rs = T[pre].rs, Insert(T[pre].ls, T[now].ls, p, l, mid);
	else T[now].ls = T[pre].ls, T[now].rs = ++tot, Insert(T[pre].rs, T[now].rs, p, mid + 1, r);
	T[now].sum = T[T[now].ls].sum + T[T[now].rs].sum;
}
 
inline int Qu(int pre, int now, int x, int y, int l = 1, int r = n + n)
{
	if (x <= l && y >= r) return T[now].sum - T[pre].sum; int mid = l + r >> 1, res = 0;
	if (x <= mid) res = Qu(T[pre].ls, T[now].ls, x, y, l, mid);
	if (y > mid) res += Qu(T[pre].rs, T[now].rs, x, y, mid + 1, r); return res;
}
 
inline void Input()
{
	n = read();
	for (int i = 1;i <= n; ++i) { int x = read(); E[x].l = i; } 
	for (int i = 1;i <= n; ++i) { int x = read(); E[x].r = n + i; }std::sort(E + 1, E + 1 + n);
}
 
inline void Solve()
{
	int now = 2, limr = 1, pos = 1; Rt[0] = ++tot; Build(); Rt[1] = ++tot; Insert(Rt[0], Rt[1], E[1].r);
	for (int i = 1;i <= n; ++i)
	{
		for (;now <= n; ++now)
		{
			if (E[now].l > E[now].r) break; Rt[now] = ++tot;
			Insert(Rt[now - 1], Rt[now], E[now].r);
		} if (limr > E[i].r) continue;
		ans += Qu(Rt[pos - 1], Rt[now - 1], limr + 1, E[i].r) - 1; limr = E[i].r; pos = i;
	} printf("%d\n", ans);
}
 
int main(void)
{
	Input();
	Solve();
}
```

---

## 作者：littleseven (赞：1)

### 安利博客 [链接地址](http://littleseven.top)

由于最开始给出的进入隧道顺序固定，并且如果没有超车的话出隧道的顺序也应该和进入隧道一样。那么我们不妨开一个**队列**维护这个进入隧道的顺序。

之后对于离开隧道的每一辆车，我们比对当前输入值$b[i]$和队首元素$now$，如果$b[i] \neq now$证明在隧道中$b[i]$超过了$now$，之后统计答案$ans++$，并且标记$vis[b[i]] = 1$。便于处理每一辆车最多被罚款一次。

那么如果一个车已经被罚款（应该提前出队列），之后却出现在了队首，这样怎么办？？？

由于记录了$vis[i]$，我们可以理解成如果$vis[i] = 1$，则编号为$i$的汽车已经离开隧道，所以每次循环判断队首是否还在隧道内即可。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
queue <int> q;
 
int n, x, ans, vis[110000];
 
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) {
        scanf("%d", &x);
        q.push(x);
    }
    
    for (int i = 1; i <= n; i ++ ) {
        while (vis[q.front()]) {
            q.pop();
        }
        scanf("%d", &x);
        vis[x] = 1;
        int now = q.front();
        if (x != now) {
            ans ++ ;
            // cout << "now:" << x << endl;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：fighter (赞：1)

~~一开始看错读入顺序，导致最后强行倒序读入~~

读完题目就可以发现，车辆的具体编号并没有什么用，我们只需要知道进入隧道时的相对顺序就好了。所以我们根据进入隧道的顺序重新编号。

那么我们就可以发现，如果一辆车出隧道时，至少有一辆编号比他大的（即进入隧道比他晚的）车已经出隧道，那么说明他一定超车了。

所以我们遍历出隧道序列，并且维护已经出隧道的所有车辆组成的有序序列。这里可以使用一个set(或树状数组)维护。然后对于当前点，查找编号比他大的车辆，如果存在则需要标记，否则不需要。然后把当前点加入set（或树状数组）即可。

```cpp
#include <bits/stdc++.h>
#define MAX 500005
using namespace std;

int n;
int a[MAX], b[MAX], id[MAX];
set<int> s;
set<int>::iterator it;

int main()
{
    cin >> n;
    for(int i = n; i >= 1; i--){
        scanf("%d", &a[i]);
        id[a[i]] = i;
    }
    for(int i = n; i >= 1; i--){
        scanf("%d", &b[i]);
        b[i] = id[b[i]];
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        it = s.lower_bound(b[i]);
        if(it != s.end()) ans++;
        s.insert(b[i]);
    }
    cout << ans << endl;

    return 0;
}
```

---

## 作者：kexinluo (赞：0)

## 朴素想法
分别用 $A,B$ 两个数组表示入列和出列。  
对于 $B$ 中的每个元素 $B_i$，若有这辆车后面出来的车 $B_j(i < j \leq n)$ 原先进入隧道时（即在 $A$ 中）的位置在 $B_i$ 的前面，说明 $B_i$ 一定是超车了。

为了方便判断，我们把 $A$ 中的元素一一映射成一个从 $1$ 到 $n$ 的上升序列，并且把 $B$ 中的元素按照 $A$ 的映射规则映射。这样，进入时一定是号码小的先进去。  
这样的话，我们只用在 $B$ 中判断车号码的大小（因为号码小的比号码大的先进入），就可以判断那辆车超车了。

**总结：** 把出来的车按进的顺序编号，若对于 $i$，存在 $j>i$ 使得 $B_i>B_j$，则 $i$ 有超车行为。

**就拿样例来说吧：**
```
A: 3 5 2 1 4
B: 4 3 2 5 1
```
映射：$3\to``1",5\to``2",2\to``3",1\to``4",4\to``5"$，就变成了：
```
A: 1 2 3 4 5
B: 5 1 3 2 4
```
然后看
- $5$ 比后面的 $1,3,2,4$ 都大，说明 $5$（即原本的 $4$）超车。
- $1$ 后面的每一个数都大于 $1$，说明他没有超车。
- $3$ 比后面的 $2$ 大，说明 $3$（即原本的 $2$）超车。
- $2$ 后面的每一个数都大于 $2$，说明他没有超车。

得到答案为 $2$。

## 优化 $O(n^2) \to O(n)$
显然，这个算法复杂度为 $O(n^2)$ 级别的，超时，所以要想个办法快点比较。  
我们可以看到，只要 $B_i$ 后所有的 $B_j$ 都小于 $B_i$，则 $i$ 超车，反之不超。  
所以只需要把 $B_i$ 和其后最小的数，即 $\min_{i<j\leq n}\{B_j\}$ 作比较。令 $f_i$ 表示从 $i$ 到 $n$ 中最小的数，即 $f_i=\min_{i<j\leq n}\{B_j\}$。则如果 $B_i > f_{i+1}$ 就说明 $i$ 超车了。  
显然，$f_i=\min\{f_{i+1},b_i\}$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
#define ll long long
#define us unsigned

int n;
int a[N], b[N], c[N];  // c 用于映射
int f[N];  // i~n 中最小的数 

int main()
{
	scanf("%d", &n);
	for (int i=1; i<=n; i++)
	{
		scanf("%d", &a[i]);
		c[a[i]] = i;  // 建立映射关系
	}
	for (int i=1; i<=n; i++)
	{
		scanf("%d", &b[i]);
		b[i] = c[b[i]];  // 映射
	}
	f[n] = b[n];  // 初始状态
	for (int i=n-1; i>=1; i--)
	{
		f[i] = min(f[i+1], b[i]);  // 递推
	}
	int ans = 0;
	for (int i=1; i<n; i++)
	{
		if (b[i] > f[i+1]) ans ++;  // 统计超车数
	}
	printf("%d\n", ans);
	return 0;
}
```
---
[AC](https://www.luogu.com.cn/record/79175648)

---

