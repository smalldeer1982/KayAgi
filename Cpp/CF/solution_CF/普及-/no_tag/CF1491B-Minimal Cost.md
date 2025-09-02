# Minimal Cost

## 题目描述

给你一个 $n$ 行 $10^6+2$ 列的图，行从 $1$ 到 $n$ 标号，列从 $0$ 到 $10^6+1$ 标号。

为简便，下面用 $(i,j)$ 表示第 $i$ 行第 $j$ 列的节点。

一开始每一行 $i$ 都恰好有一个障碍物 $(i,a_i)$。你可以将障碍物移动到四周空的节点（不能移出图的范围），上下移动一个单位花费 $u$，左右移动一个单位花费 $v$。（可参照上图）

你需要使得 $(1,0)$ 到 $(n,10^6+1)$ 之间有一条路径（只能上下左右移动，不能越过障碍物），求移动障碍物的最小花费。

## 样例 #1

### 输入

```
3
2 3 4
2 2
2 3 4
3 2
2 4 3
3 2```

### 输出

```
7
3
3```

# 题解

## 作者：Priori_Incantatem (赞：5)

[原题链接](https://codeforces.ml/problemset/problem/1491/B)  
[洛谷链接](https://www.luogu.com.cn/problem/CF1491B)

本题分为三种情况：
1. 这 $n$ 个障碍物没有组成一堵墙：也就是说如果 $\max\limits_{i=2}^n\{|a_i-a_{i-1}|\}>1$，那么则不需要花费任何费用，因为可以直接绕过障碍物。
2. 这 $n$ 个障碍物组成了一堵普通的墙：也就是 $\max\limits_{i=2}^n\{|a_i-a_{i-1}|\}=1$。那么，我们有两种选择：横向挪动一个障碍物，使其转化为情况 $1$；或者纵向挪动一个障碍物，使得某一行没有障碍物。那么，所需要的费用就是 $\min(u,v)$
3. 这 $n$ 个障碍物组成了一堵完美的墙：也就是所有的 $a_i$ 都相等。那么，我们只需要横向挪动任意一个障碍物，就把问题转化为了情况 $2$，所以情况三的所需费用就是 $v+\min(u,v)$。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=110;
int n,u,v;
int a[Maxn];
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
bool check1()
{
    for(int i=2;i<=n;++i)
    if(abs(a[i]-a[i-1])>1)return 1;
    return 0;
}
bool check2()
{
    for(int i=2;i<=n;++i)
    if(a[i]!=a[i-1])return 1;
    return 0;
}
int main()
{
    // freopen("in.txt","r",stdin);
    int T=read();
    while(T--)
    {
        n=read(),u=read(),v=read();
        for(int i=1;i<=n;++i)
        a[i]=read();
        if(check1())puts("0");
        else if(check2())printf("%d\n",min(u,v));
        else printf("%d\n",v+min(u,v));
    }
    return 0;
}
```

---

## 作者：serverkiller (赞：4)

这里是官方题解。

分类讨论：

如果所有 $a_i$ 均相同，答案为 $v+\min(u,v)$ 。

如果存在 $|a_i-a_{i+1}| > 1$ ，答案为 $0$ 。

否则，答案为 $\min(u,v)$ 。

---

## 作者：cute_overmind (赞：3)

### 题目大意
[题意](https://www.luogu.com.cn/problem/CF1491B)
### 题目分析
分别记两点间纵坐标距离为 
$dis_1,dis_2,\dots dis_{n-1}$。
其中，$dis_1=|y_2-y_1|,dis_2=|y_3-y_2|,\dots dis_{n-1}=|y_n-y_{n-1}| $。

为方便表达，再记一个时间 $t$ 作为题目答案。

在任意相邻两点中的 $dis_x(1\le x \le n)$ 中存在：
- 当 $dis_x >1$ 时，必定存在满足题意的路径可走，即 $t = 0$。
- 当 $dis_x \le 1$ 时，那么说明两点之间有障碍物，此时我们要推开它，即花费 $t =\min(u,v)$。
- 当 $dis_1 = dis_2 = \dots = dis_{x-1} = dis_x = dis_{x+1} = \dots = dis_{n-1}$ 时，那么两点间完全被墙所分隔。为题目有解，我们须连续推开两个点上的墙，即 $t=v+\min(u,v)$。

### [代码](https://www.luogu.com.cn/record/162608490)
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n , u , v , ans , a[N];
int solve()
{
	for(int i = 2 ;i <= n;i++) ans = max(ans , abs(a[i] - a[i - 1]));
	if(ans == 0) return min(v * 2 , v + u);
	if(ans == 1) return min(u , v);
	return 0;
}
int main()
{
	int t;
	cin >> t;
	while(t--){
		cin >> n >> u >> v;
		for(int i = 1;i <= n;i++) cin >> a[i];
		ans = 0;
		cout << solve() << '\n';
	}
	return 0;
}
```

---

## 作者：_Michael0727_ (赞：2)

# 题解：CF1491B Minimal Cost

[文章食用效果更佳](https://www.luogu.com.cn/article/t3eykpcb)

---

## 审题

[题目传送门](https://www.luogu.com.cn/problem/CF1491B)

---

## 思路

总共可以分三种情况进行讨论

- 如果障碍物没有形成一堵墙，即相邻两个障碍物的 $a$ 值之差大于 $1$ ，则可以直接绕开，花费为 $0$。
- 如果障碍物形成了一堵普通的墙，即相邻两个障碍物的 $a$ 值之差都小于等于 $1$ ，则仅需向上或向下推一次即可，花费 $\min (u,v)$。
- 如果障碍物组成了一堵完美的墙，即每个障碍物的 $a$ 值都相等，则需要向左或右推一次，变为情况 $2$ ，总花费 $v+ \min (u,v)$。

---

**AC 代码**

```cpp
# include <bits/stdc++.h>
using namespace std ;
long long a [114514] ;
int main ( )
{
	long long q ;
	cin >> q ;
	while ( q -- )
	{
		long long n , u , v , dis ;
		cin >> n >> u >> v ;
		for ( long long i = 1 ; i <= n ; i ++ )
		{
			cin >> a [i] ;
			dis = ( i - 1 ? max ( dis , abs ( a [i] - a [i - 1] ) ) : 0 ) ;
		}
		if ( dis == 0 )
		{
			cout << v + min ( u , v ) << endl ;
		}
		else if ( dis == 1 )
		{
			cout << min ( u , v ) << endl ;
		}
		else
		{
			cout << 0 << endl ;
		}
	}
	return 0 ;
}
```

---

[AC 记录](https://www.luogu.com.cn/record/162203604)

---

## 作者：Tulip_ (赞：1)

### 题意

给你一个 $n$ 行 $10^6+2$ 列的图。

你需要移动障碍物，从起点 $(1,0)$ 走到终点 $(n,10^6+1)$。

每上下移动障碍物一个单位花费 $u$，每左右移动障碍物一个单位花费 $v$。

求移动障碍物的最小花费。

### 思路

其实这道题很简单，只需要**分类讨论三次**。

第一种：

![](https://cdn.luogu.com.cn/upload/image_hosting/juxbw0q4.png)

这种就是两个障碍物的距离 $\ge 2$，我们可以**直接通过**，花费就为 $0$。

第二种：

![](https://cdn.luogu.com.cn/upload/image_hosting/j9hx3zbt.png)

这种就是两个障碍物的距离 $=1$，需要移动其中**一个一个单位长度**，但为了**花费小**，所以花费就为 $\min (ans, \min (u,v))$。

第三种：

![](https://cdn.luogu.com.cn/upload/image_hosting/wa43rh2c.png)

这种就是两个障碍物的距离 $=0$，也就是**相等**，需要移动其中**一个两个单位长度**，也要为了**花费小**，所以花费就为 $\min (ans,v+ \min (u,v))$。

### 代码

在思路中我们分了**三次讨论**，所以代码中就有三个 `if` 判断，来判断花费数量。

代码，如下。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005];
int n,m,t,u,v,ans=2e9;
signed main(){
	cin>>t;
	while (t--){
		cin>>n>>u>>v;
		for (int i=1;i<=n;i++)scanf("%d",a+i);
		for (int i=2;i<=n;i++){
			if (abs(a[i]-a[i-1])>=2)ans=0;
			if (abs(a[i]-a[i-1])==1)ans=min(ans,min(u,v));
			if (a[i]==a[i-1])ans=min(ans,v+min(u,v));
		}
		cout<<a+i;
	}
	return 0;
}
```

---

## 作者：Dreamer_Boy (赞：1)

调了两个多小时终于过了，交一发题解。


### 题目分析
如果你认真读题就会发现，这道题看似有很多种情况，但障碍的移动方式其实只有几种。

如果当所有障碍物都在一列时，可以将某一个障碍水平移动一格，再垂直移动一格或者水平移动两格，那么答案就是 $v + \min(u,v)$。

当有通路时，则无需移动，答案就是 $0$。

其余情况都可以通过将其中一个障碍水平移动一格或垂直移动一格来达成目标，答案是 $\min(u, v)$。

然后按题意模拟即可。

### AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>
T read(T x)
{
    T opt = 1, sum = 0;
    char ch = getchar();
    while(!isdigit(ch)) opt = (sum == '-') ? -1 : 1, ch = getchar();
    while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48);
    return opt * sum;
}
#define read read(0)
const int N = 1005;
int a[N];
 
int main()
{
	int T;
	cin >> T;
	while(T -- )
	{
		int n, v, u;
		cin >> n >>u >> v;
		for(int i = 1;i <= n;i ++ ) cin >> a[i];
		bool xt = 1,ne = 0;
		for(int i = 2;i <= n;i++) {
		    if(abs(a[i] - a[i - 1]) >= 2) {
		        ne = 1; 
		    }
		}
		if(ne) {
		    puts("0");
		    continue;
		}
		for(int i = 2;i <= n;i ++ ) {
		    if(a[i] != a[1]) {
		        xt = 0;
		    }
		}
		int ans;
		if(xt) ans = min(u + v,v * 2);
		else ans = min(u, v);
		cout << ans << endl;
	}
	
	return 0;
}
```
### 结语
[洛谷 AC 记录](https://www.luogu.com.cn/record/115028248)。

[CF AC 记录](https://codeforces.com/contest/1491/submission/213444660)。

---

## 作者：FutaRimeWoawaSete (赞：1)

显然，我们记录下来两两之间纵坐标之差的绝对值 $res$ 。           

- $2 \leq res$ 时，我们已经存在合法路径；             

- $res = 1$ 时，我们只要考虑推一次上下/左右；            

- $res = 0$ 时，我们考虑推两次，且不能两次都上下推；           

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Len = 1e6 + 5;
int n,m,a[Len],u,v,Y = 1e6 + 1;
int calc()
{
	int res = 0;
	for(int i = 2 ; i <= n ; i ++) res = max(res , abs(a[i] - a[i - 1]));
	if(!res) return min(v * 2 , v + u);
	if(res == 1) return min(u , v);
	return 0;
}
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d %d %d",&n,&u,&v);
		for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
		printf("%d\n",calc());
	}
	return 0;
}
```

---

## 作者：LRL65 (赞：1)

思路：
1. 如果障碍物之间有缺口，也就是说有 $|a_{i+1}-a_i|>1$ ，那么直接输出 `0` 即可。
1. 如果障碍物已经形成了墙，而且这个墙是有突出来的部分的，不是笔直向下的（各位想象一下），也就是说 ：对于任意的 $i$，都有 $|a_{i+1}-a_i|<=1$ 且至少有一个 $i$ ，可以满足 $|a_{i+1}-a_i|=1$ 。那么此时应该选择任意一个突出的部分，将这个障碍物随意移动（不能移到障碍物上），所以应输出 $\min(u,v)$ 。
1. 还有一种是最特殊的，障碍物形成一堵笔直向下的墙，也就是说：对于任意的 $i$ ，都满足 $a_{i+1}=a_i$ 。那么此时应将任意一个地方向左或向右平移，然后再随意移动（不能移回去），所以应输出 $v+\min(u,v)$ 。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,u,v,a[105];
int main() {
	cin>>t;
	while(t--) {
		cin>>n>>u>>v;
		for(int i=1;i<=n;i++)cin>>a[i];
		bool flag=true;
		for(int i=2;i<=n;i++)
			if(a[i]!=a[i-1])flag=false;
		if(flag)cout<<v+min(u,v)<<endl;
		else {
			bool flag=true;
			for(int i=2;i<=n;i++)
				if(abs(a[i]-a[i-1])>1)flag=false;
			if(flag)cout<<min(u,v)<<endl;
            else cout<<0<<endl;
		}
	}
}
```


---

## 作者：Storm_Lightning (赞：0)

# CF1491B Minimal Cost

## 题目大意

给你一张地图，每一行都有一个障碍点，求 $(1,0)$ 到 $(n,10^6+1)$ 这个点的最小花费。

## 思路分析

我们可以考虑设 $a_k$ 和 $a_{k+l}$ 之间的纵坐标之差为 $now$。

那么就可以分如下三种情况。

- $now\ge2$ 时，则此路线可通过，已经存在合法路线了。

- $now=1$ 时，则此时就考虑左右或者上下走一个。

- $now=0$ 时，则此时就可以左右移动两次或者上下移动一次并且左右移动一次。

## 代码

由于代码太简单，作者就不放了。

---

## 作者：GoodLuckCat (赞：0)

闲话：第一次用专栏写题解。

---

先挂个 [原题链接](https://www.luogu.com.cn/problem/CF1491B)。

其实题目中所说的障碍物的分布，一共就三种情况。

设 $m$ 为障碍物之间的距离。下面的图中，`W` 代表墙。

第一种：$m=0$。

```
|  W  |
|  W  |
```

大概就长这样。此时需要 $\min(u,v)+v$ 的花费才能移动完成。

第二种：

```
|  W  |
|   W |
```

此时移动一次即可，上下左右都可以，所以花费为 $\min(u,v)$。

第三种：

```
| W   |
|   W |
```

此时可以明显地看出不用移动，花费为 $0$。

所以三种情况来讨论就行了。注意多测，还有 **`switch` 要写 `break`**。我被坑了一次（）

放代码：（~~这才是我正常的码风~~）

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,u,v,a,b,m=-1;
        cin>>n>>u>>v>>a;
        for(int i=2;i<=n;i++)
        {
            cin>>b;
            if(m<abs(a-b))m=abs(a-b);
            a=b;
        }
        switch(m)
        {
            case 0:cout<<min(u,v)+v<<endl;break;
            case 1:cout<<min(u,v)<<endl;break;
            default:cout<<"0\n";break;
        }
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

我们废话不讲，直接切入正题。

这道题其实并不复杂，只需分类讨论即可。我们将设每两墙纵坐标距离为 $d$，接着分类讨论：

仔细一想我们发现，这题看似情况很多，实际只有 $3$ 种而已。
1. 当 $d\ge 2$ 时，说明有道路，则无需移动，直接输出 $0$ 即可。
2. 当 $d=1$ 时，我们只要考虑推一次上下或者左右，答案就是 $\min (u,v)$。
3. 当 $d=0$ 时，也就是说所有障碍物都在一列，那么将某个障碍水平移动一格，再垂直移动一格或水平移动两格，那么答案就是 $v+\min (u,v)$。

讨论完这 $3$ 种情况，本题大致没有问题了。

代码：
```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
ll a[1000010],x,n,u,v;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>x;
	while(x--){
		cin>>n>>u>>v; 
		for (int i=1;i<=n;i++) cin>>a+i; 
		ll ans=0;//最终答案 
		for (int i=2;i<=n;i++) {//分类讨论 
			if (abs(a[i]-a[i-1])>=2) ans=0;//第一种情况：有通路 
			if (abs(a[i]-a[i-1])==1) ans=min(ans,min(u,v));//第二种情况：推一次上下或者左右 
			if (a[i]==a[i-1]) ans=min(ans,v+min(u,v));//第三种情况：将某个障碍水平移动一格，再垂直移动一格或水平移动两格 
		}
		cout<<ans<<endl; 
	}
	return 0;
}
```
本人打字还是挺累的，希望审核能通过！

---

## 作者：Berd__ (赞：0)

## 分析
此题看似有很多种情况，实际上经过仔细观察可以发现，当有道路时，则无需移动，答案就是 $0$。

而如果所有障碍物都在一列，将某个障碍水平移动一格，再垂直移动一格或水平移动两格，那么答案就是 $v+\min(u,v)$。

其余情况通过将其中一个障碍水平移动或垂直移动来达成，最小花费是 $\min(u,v)$。

分类讨论即可，按题意模拟。

此题太水，只需判断情况模拟即可，代码不放了，参考 @Priori_Incantatem 大佬的。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int a[105],n,u,v,T;
bool aknoi()
{
    for(int i=2;i<=n;++i)
    if(abs(a[i]-a[i-1])>1)return 1;
    return 0;
}
bool akioi()
{
    for(int i=2;i<=n;++i)
    if(a[i]!=a[i-1])return 1;
    return 0;
}
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>u>>v;
        for(int i=1;i<=n;++i)
        cin>>a[i];
        if(aknoi()) printf("0\n");
        else if(akioi()) cout<<min(u,v)<<endl;
        else cout<<v+min(u,v)<<endl;
    }
    return 0;
}
```

---

## 作者：rain_dew (赞：0)

原题链接：[CF1491B Minimal Cost](https://www.luogu.com.cn/problem/CF1491B)

一道简单的数学题。

## 思路：

我们将设每两墙间距离（纵坐标距离）$dis$，这需要分三种情况：

1. 散墙（即 $dis \ge 2$）：如下图蓝线所示，即可不需要任何的花费，直接输出 $0$ 即可；
![第一种情况](https://cdn.luogu.com.cn/upload/image_hosting/cfgfoswv.png)
2. 半墙（即 $dis=1$）：如下图红线所示，一定会有一面墙移动后腾出移动位置，也就是纵向移动与横向移动均可，可见此时最小花费为纵向移动与横向移动花费的最小值；
![第二种情况](https://cdn.luogu.com.cn/upload/image_hosting/x73pk0n8.png)
3. 全墙（即 $dis=0$）：先如下图紫线所示，一定会有一面墙往横向移动（实线与虚线均可）后，转移至第二种情况（如上图红线所示），此时记录横向花费和第二种情况最小值的和。
![第三种情况](https://cdn.luogu.com.cn/upload/image_hosting/tcc6exgy.png)

最后比较最小值输出，同时注意本题多测。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000005];
int n,m,t,u,v;

int main()
{
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d%d",&n,&u,&v);
		for (int i=1;i<=n;i++)
			scanf("%d",a+i);
		int ans=2e9;
		for (int i=2;i<=n;i++)
		{
			if (abs(a[i]-a[i-1])>=2)//1
				ans=0;
			if (abs(a[i]-a[i-1])==1)//2
				ans=min(ans,min(u,v));
			if (a[i]==a[i-1])//3
				ans=min(ans,v+min(u,v));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：szkzyc (赞：0)

此题的思路个人觉得比较好理解，是在 $B$ 题中比较简单的一类。

此题的思路就是分类讨论，第一类为：

障碍排成整齐的一列，说明必须得将任意一个左右平移一次后再选择上下还是左右（这个时候选择最小值就行了）。所以第一类的公式为：

### $v + min(u, v) $

第二类就是任意两个相邻障碍相差的绝对值不大于 $1$，此类的就必须得上下或左右移动一格，也就是：

### $min(u, v)$

第三类就是但凡有两个相邻障碍相差的绝对值大于等于 $2$ 时，就一定能一口气走到终点，也就是 $0$。

由于此题太水了，就不放代码了。剩下的就是判断是第几种情况辣！这也非常好判断啊，每个暴力枚举也是可以稳过的。

---

