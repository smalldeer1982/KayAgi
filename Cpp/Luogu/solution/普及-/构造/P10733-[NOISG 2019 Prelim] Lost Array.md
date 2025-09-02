# [NOISG 2019 Prelim] Lost Array

## 题目背景

翻译自 [NOISG2019 Prelim B.Lost Array](https://github.com/noisg/sg_noi_archive/blob/master/2019_prelim/)。

**本题已启用 Special Judge，满足题目条件的任何答案都将视为正确。**

## 题目描述

给定 $M$ 组形如 $\min (X_{A_i},X_{B_i})=C_i$ 的关系式，请构造一个长度为 $N$ 的数组 $X$，使得数组中的每个数字在 $1$ 到 $10^9$ 之间，并且该数组满足所有的关系式。

题目保证数组存在。

## 说明/提示

### 【样例 #1 解释】
显然，$\min (X_2,X_1) = \min (9,7) =7$，满足题目条件。
### 【样例 #3 解释】
原题的题面没有此样例，但测试数据有。

第一个限制为 $\min (X_1,X_2) =1$，所有的条件实际上和这个限制一样。
### 【样例 #4 解释】
唯一的限制为 $\min (X_1,X_2) =123$，其余的数字可以是介于 $1$ 到 $10^9$ 之间的任何数字。
### 【数据范围】
| $\text{Subtask}$ | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $0$ | $0$ | 样例 |
| $1$ | $5$ | $N=2,M=1$ |
| $2$ | $6$ | $M\leq 3$ |
| $3$ | $20$ | $N,M\leq 1000$ |
| $4$ | $21$ | $C_i \leq 10,N \leq 5$ |
| $5$ | $48$ | 无 |

对于 $100\%$ 的数据：
- $1 \leq N,M \leq 10^5$
- $1 \leq A_i ,B_i \leq N$
- $A_i \neq B_i$
- $1 \leq C_i \leq 10^9$

## 样例 #1

### 输入

```
2 1
2 1 7```

### 输出

```
9 7```

## 样例 #2

### 输入

```
5 6
1 2 1
3 5 4
1 5 3
1 3 3
2 3 1
2 4 1```

### 输出

```
3 1 4 1 5```

## 样例 #3

### 输入

```
2 5
1 2 1
2 1 1
1 2 1
1 2 1
2 1 1```

### 输出

```
1 114514```

## 样例 #4

### 输入

```
5 1
1 2 123```

### 输出

```
123 1000000000 3 4 26311337```

# 题解

## 作者：PR_CYJ (赞：7)

# [题目传送门](https://www.luogu.com.cn/problem/P10733)

# 思路
通过 $\min(X_{A_i},X_{B_i})=C_i$ 可以发现，$X_{A_i}$ 和 $X_{B_i}$ 的最小值都不能低于 $C_i$，所以考虑用 $fr$ 数组来记录每一个 $X_i(1\le i\le n)$ 的下限。同时因为每一个 $X_i$ 都是 $1$ 到 $10^9$ 之间的一个整数，所以要将 $fr_i$ 初始化为 $1$。
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n,m,fr[N];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		fr[i]=1;//要初始化为1
	for(int i=1;i<=m;i++)
	{
		int a,b,pr;
		cin>>a>>b>>pr;
		fr[a]=max(fr[a],pr);
		fr[b]=max(fr[b],pr);
	}
	for(int i=1;i<=n;i++)
		cout<<fr[i]<<" ";
}
```

---

## 作者：zyc0614 (赞：3)

# 前言
~~本蒟蒻来水题解啦~~

[题目传送门](https://www.luogu.com.cn/problem/P10733)
# 题目简述
给你 $M$ 个像 $\min (X_{A_i},X_{B_i})=C_i$ 的关系式，构造一个满足所有的关系式且长度为 $N$ 的数组 $X$。
- $1 \leq N,M \leq 10^5$
- $1 \leq A_i ,B_i \leq N$
- $A_i \neq B_i$
- $1 \leq C_i \leq 10^9$
- **$1 \leq X_1$ ~ $X_N \leq 10^9$** （这条很关键）
# 题目实现
其实这道题目很简单，题目中间接表达每个表达式不冲突，
那我们就可以让 $X_{A_i}$ 和 $X_{B_i}$ 与 $C_i$ 取最大值并赋值即可。

但你以为这就结束了吗！那你就会喜提 [26分的高分](https://www.luogu.com.cn/record/165236739) 。

记得我刚刚说的那条关键句吗，**$1 \leq X_1$ ~ $X_N \leq 10^9$** , 数组中的每个数字在 $1$ 到 $10^9$ 之间，那么 $X_{i}$ 就不能为 $0$ , 所以我们给这些 $X_{i}$ 赋值一个在 $[1,10^9]$ 内的值即可，例如 $233$ 。
# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,M,a,b,c; 


int main(){
	cin>>N>>M;
	int X[N+1]={0};//这里要初始化
	
	
	for(int i=1;i<=M;i++) //或 while(m--) 
	{
		cin>>a>>b>>c;
		X[a]=max(X[a],c);
		X[b]=max(X[b],c);
	}
	
	
	//输出 
	for(int i=1;i<=N;i++) //或 while(n--)
	{
		if(X[i]!=0) cout<<X[i]<<" "; //
		else cout<<"233 "; //其他输出任意值即可,如233; 
	}
	return 0; //完结撒花 
}
```
# 尾声
发题解不仅可以帮助别人，还可以帮自己梳理思路。

不过写题解还是挺累的，别忘了点个赞再走哟~~~~

---

## 作者：shentianxing (赞：3)

把所有 $X_i$ 预设为 $1$。

对于每一条条件，如果 $X_{ai}$ 或 $X_{bi}$ 小于 $C_i$ 就改为 $C_i$，如果都小于 $C_i$，就都改成 $C_i$。

由于一定存在该数组，每一条条件的两个数中至少有一个会被保留，也不会有一个比 $C_i$ 更小。
```cpp
#include <bits/stdc++.h>
using namespace std;
int v[10050];
int main(){
	int n,m;cin>>n>>m;
	while(m--){
		int a,b,c;cin>>a>>b>>c;
		v[a-1]=max(v[a-1],c);
		v[b-1]=max(v[b-1],c); 
	}
	for(int i=0;i<n;i++){
		cout<<v[i]<<" ";
	}
	return 0;
}
```

---

## 作者：RoamingDuck (赞：2)

### 思路
已知 $\min(x_{a_i},x_{b_i}) = c_i$，且题目中说了，保证一定有解，那么取 $\max(x_{a_i},x_{b_i},c_i)$ 即可，剩下的，就输出一个任意数字。

### AC Code
```cpp
#include <iostream>
#define ll long long
using namespace std;
ll n, m;
ll a, b, c, x[100010];
int main()
{
    cin >> n >> m;
    for (ll i = 1; i <= m; i++)
    {
        cin >> a >> b >> c;
        x[a] = max(x[a], c);
        x[b] = max(x[b], c);
    }
    for (ll i = 1; i <= n; i++)
    {
        if (x[i])
        {
        	cout << 114514 << ' ';
        }
        else
        {
        	cout << x[i] << ' ';
        }
    }
    return 0;
}
```

---

## 作者：x1489631649 (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/P10733)
# 输入 
1. 两个整数 $n(1 \le n \le 10^5)$ 代表数组的元素个数和 $m(1 \le m \le 10^5)$ 代表关系式。
2.	接下来 $m$ 行，$a(1 \le a \le n)$，$b(1 \le b \le n)$ 和 $c(1 \le c \le 10^9)$ 
# 输出
输出一个满足条件的数组。
# 分析
需要你找到一个数组 $X_n$，满足题目给出的众多关系式，每个关系式的形式都是为 $X_a$ 和 $X_b$ 的最小值为 $c$。我们要找出一个数组满足条件，那么就只是要让 $X_a$ 和 $X_b$  的最小值都不能低于 $c$，那么我们就取它的最大值即可。
 # Code
```
#include<bits/stdc++.h>
using namespace std;
int ans[100005];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
	{
        int a,b,c;
        cin>>a>>b>>c;
    	ans[a]=max(ans[a],c);//将当前输入的数与原先数组存的数进行比较。
        ans[b]=max(ans[b],c);
    }
    for(int i=1;i<=n;i++)
	{
        if(ans[i]!=0)
            cout<<ans[i]<<" ";
        else cout<<1<<" ";//如果是这个数组是零，代表没有对这个数字的限制，可以取任意数。
    }
    return 0;
}
```
# 时间复杂度
本代码仅使用一重循环，显然可以通过。

---

## 作者：Arthur_Douglas (赞：1)

## 思路

只需要在输入时记录 $X$ 数组，然后取最大，最后所得的值便是答案。但注意**将未用的** $X$ 赋值为极大值即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int X[100001];
const int Maxn = 1e9;
signed main()
{
	int n , m;
	cin >> n >> m;
	for(int i = 1;i <= m;++ i)
	{
		int a , b , c;
		cin >> a >> b >> c;
		X[a] = max(X[a] , c);
		X[b] = max(X[b] , c);
	}
	for(int i = 1;i <= n;++ i)
	if(!X[i])
	cout << Maxn << ' ';
	else
	cout << X[i] << ' '; 
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

由 $\min (X_{A_i},X_{B_i})=C_i$ 可以得到 $X_{A_i}\geqslant C_i$ 且 $X_{B_i}\geqslant C_i$，并且它们俩中必有一个等于 $C_i$。我们考虑直接让 $X_{A_i}=X_{B_i}=C_i$，但是如果前面的关系式对要求其中某一个数等于一个更大的 $C_i$，那么我们就不更新。

由题目保证数组存在，不会存在两个数都不更新的情况。

```c++
#include<bits/stdc++.h>
using namespace std;

int x[100002];

int main(){
	int n,m;cin>>n>>m;
	while(m--){
		int a,b,c;cin>>a>>b>>c;
		if(x[a]<c) x[a]=c; 
		if(x[b]<c) x[b]=c; 
	}
	for(int i=1; i<=n; i++){
		if(x[i]) cout<<x[i]<<" ";
		else cout<<"1 ";
	}
    return 0;
}
```

---

## 作者：brbrbread (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10733)
### 题目要求
题目要求我们输出一个长度为 $n$ 的 $X$ 数组 且 满足
 $\min(X_A,X_B) = C$  。
###  思路
那么思路就相当明确了，先输入 $NM$  再输入 $a b c$  。 
那我们转念一想：如果 $X_A$ $X_B$  都等于 $C$ 那 $\min(X_A,X_B) = C$  是不是就一定会成立？
抱着这样的想法我们来试一试:
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int N,M;
int a,b,c;
int x[114514];
int main(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++){
		scanf("%d%d%d",&a,&b,&c); 
		x[a]=c;
		x[b]=c;
		
	}
	for(int i=1;i<=N;i++){
		if(x[i]==0) printf("1 ");
		else printf("%d ",x[i]);
	}
	return 0;
}

```


结果......
[WA了](https://www.luogu.com.cn/record/165169023) 。

这样是没有办法照顾到全局的 所以我们可以用 $\max$ 取最大值 来给 $X$ 数组赋值然后输出。注意 $X$ 数组的空位要填上 $1$   ~ $10^9$ 的数不能是 0 啊！
### AC code 1
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int N,M;
int a,b,c;
int x[114514];//数据范围是 1^5 四舍五入114514（bushi
int main(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++){
		scanf("%d%d%d",&a,&b,&c); 
		x[a]=max(x[a],c);//赋值
		x[b]=max(x[b],c);
	}
	for(int i=1;i<=N;i++){
		if(x[i]==0) printf("114514 ");//判断是不是空位
		else printf("%d ",x[i]);
	}
	return 0;//朴实无华的结尾
}

```
当然，也可以使用动态数组。
###  AC code 2
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int N,M;
int a,b,c;
vector<int> x[114514];
int main(){
	ios::sync_with_stdio(0);//解除cin 与  cout 的绑定 
	cin.tie(0),cout.tie(0);//时间设为 0 
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++){//输入要求 
		scanf("%d%d%d",&a,&b,&c); 
		x[a].push_back(c);//存入限制 
		x[b].push_back(c);
		
	}
	for(int i=1;i<=N;i++){
		if(x[i].empty()) cout<<"1 ";
		else{
			sort(x[i].begin(),x[i].end());//对最小值限制排序 
			int l=x[i].size();//获取长度 
			cout<<x[i][l-1]<<" ";
		}
		
	}
	return 0;
}

```
### AC code 3 (与2相似)
```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
int N,M;
int a,b,c;
set<int> x[114514];
int main(){
	ios::sync_with_stdio(0);//解除cin 与  cout 的绑定 
	cin.tie(0),cout.tie(0);//时间设为 0 
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++){//输入要求 
		scanf("%d%d%d",&a,&b,&c); 
		x[a].insert(c);//存入限制 
		x[b].insert(c);
		
	}
	for(int i=1;i<=N;i++){
		if(x[i].empty()) cout<<"1 ";
		else{

			int l=x[i].size();//获取长度 
			set<int>::iterator it=x[i].end();
			it--;
			cout<<*it<<" ";
		}
		
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10733)

很简单的构造题。

既然要使 $\min(X_{A_i},X_{B_i})=C_i$，那我们可以使 $X_{A_i}=\max(X_{A_i},C_i)$，$X_{B_i}=\max(X_{B_i},C_i)$，其余取 $C_i$ 的上限 $10^9$，就可以满足要求。

```cpp
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
const int Max = 1e9;

int p[N];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        p[a] = max(p[a], c);
        p[b] = max(p[b], c);
    }
    for (int i = 1; i <= n; i++)
        cout << (p[i] == 0 ? Max : p[i]) << " ";
    return 0;
}
```

---

## 作者：_xdd_ (赞：1)

要想 $\min(X_{a_i},X_{b_i})=c$，只需要把 $X_{a_i}$ 和 $X_{b_i}$ 与 $c$ 取 $\max$，不清楚的可以照着样例算。

其他值取任意值即可。

```cpp
#include<iostream>
using namespace std;
int arr[100005];
int main(){
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin >> a >> b >> c;
        arr[a]=max(arr[a],c);//取 max
        arr[b]=max(arr[b],c);
    }
    for(int i=1;i<=n;i++){
        if(arr[i])
            cout << arr[i] << ' ';
        else cout << 1 << ' ';
    }
    return 0;
}
```

---

## 作者：LG086 (赞：0)

### 分析


给定 $M$ 组形如 $\min (X_{A_i},X_{B_i})=C_i$ 的关系式，构造一个长度为 $N$ 的数组 $X$。  
因为每个 $X_i$ 都介于 $1$ 和 $10^9$ 之间，所以初始化数组，全为 $1$。  
对于每个 $A_i,B_i,C_i$，一种可行的方案是：
$$
\begin{cases}
  X_{A_i}=X_{B_i}=C_i & X_{A_i} \le C_i ,X_{B_i}\le C_i \\
  X_{A_i}=C_i & X_{A_i} \le C_i \\
  X_{B_i} = C_i & X_{B_i} \le C_i
\end{cases}
$$

用文字来说，就是当 $X_{A_i} \le C_i$ 且 $X_{B_i}\le C_i$，$X_{A_i}=X_{B_i}=C_i$；当只有 $X_{A_i} \le C_i$，那么 $X_{A_i} = C_i$；当只有 $X_{B_i} \le C_i$ 时，那 $X_{B_i}=C_i$。

可以证明这样构造符合题意。

------------
### 代码

```cpp
#include<iostream>
using namespace std;
int n,m,a,b,c,dp[114514];
int main(){
    cin>>n>>m;
    for(int i(1);i<=n;i++)
    dp[i]=1;
    while(m--){
        cin>>a>>b>>c;
        if(dp[a]<=c&&dp[b]<=c)dp[a]=c,dp[b]=c;
        else if(dp[a]<=c)dp[a]=c;else dp[b]=c;
    }
    for(int i(1);i<=n;i++)
    cout<<dp[i]<<" ";
}
```

---

## 作者：dvsfanjo (赞：0)

# 题解：P10733 [NOISG2019 Prelim] Lost Array

## 思路

对于每一次操作，我们可已让：

$$X_{a_i}=\max(X_{a_i},c)$$

$$X_{b_i}=\max(X_{b_i},c)$$

这样就满足了条件。

## 注意

其他没有被动过的数组元素，改成 $1$ 就好了，如果手贱改成 $1145141919810$ 的后果是：

$$100pt \to 26pt$$

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
ll a[N], u, v, k, n, m;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> k;
		a[u] = max(a[u], k);
		a[v] = max(a[v], k);
	}
	for (int i = 1; i <= n; i++)
		if (a[i])
			cout << a[i] << ' ';
		else
			cout << 1 << ' ';
	return 0;
}
```

---

## 作者：qfy123 (赞：0)

# P10733
[传送门](https://www.luogu.com.cn/problem/P10733)
## 思路
简单构造题。

手玩样例，不难得出构造方式：对于 $\forall i \in [1,M]$，将 $X_{A_i}$ 和 $X_{B_i}$ 分别赋值为 $\max (X_{A_i},C_i)$ 和 $\max (X_{B_i},C_i)$。对于那些没有给出限制的，随便输出一个在 $[1,10^9]$ 内的整数即可。

还是简要说明一下正确性：我们每次都对数组的两个元素与 $C_i$ 取最大值，由于题目保证有解，按照这种方法构造结束后，**这两个元素的值至少有一个等于 $C_i$**，并且对于这两个元素的而言，**它们的值最少取到 $C_i$**，那么对这两个元素取最小值一定等于 $C_i$。综上，用这种构造方式构造出来的数列一定能满足题目的 $M$ 个限制。

如果实在不清楚，可以照着样例，用上述方法构造一遍。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N],n,m;
mt19937 rnd(time(0));
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		a[x] = max(a[x],c);
		a[y] = max(a[y],c);
	}
	for(int i=1;i<=n;i++) printf("%d ",a[i]?a[i]:(rnd()%(int)1e9)+1);
	return 0;
}

```
[AC记录](https://www.luogu.com.cn/record/165248984)

---

## 作者：xxseven (赞：0)

作为除出题人外的首A，来写一篇题解~~庆祝一下~~

注意到 $\min(x_a,x_b)=c$ 等价于一组较好处理的条件，即$x_a \ge c, x_b \ge c,x_a=c$ 或 $x_b=c$。为了方便地满足这组条件，不妨直接令 $x_a \gets c,x_b \gets c$。

但是这样会出现一个问题：假如 $x_a$ 已经赋值为 $c_0$，又出现了一组限制条件为 $x_a,x_b,c_1$ 且 $c_1 \lt c_0$，那么 $x_a$ 会被更小的值覆盖掉从而不满足先前的条件。解决方法也很简单，在赋值时取 $\max$ 即可。

总时间复杂度 $O(m)$，可以通过此题。

下面是完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+6;
int n,m,a[N];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int x,y,v,i=1;i<=m;++i){
		cin>>x>>y>>v;
		a[x]=max(a[x],v); a[y]=max(a[y],v);
	}
	for(int i=1;i<=n;++i)
		cout<<(a[i]?a[i]:1)<<' ';
	return 0;
}

```

希望这篇题解能够帮到你！

---

## 作者：hard_learn (赞：0)

# 简要题意
构造长度为 $N$ 的数组 $X$，满足给定的 $M$ 个最小值约束条件。
# 思路
因为数组中每个位置的值满足约束条件中的最大值要求，所以遍历每一个约束条件 $a$ 和 $b$ 是数组索引位置，$c$ 是约束的最大值。即取 $X$ 数组与 $c$ 的最大值。
# 注意
当 $X_i$ 为 $0$ 时，不能输出 $0$ 可以随便输出一个自己喜欢的数。
# 代码 
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int x[100005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();cout.tie();
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		x[a]=max(x[a],c);
		x[b]=max(x[b],c);
	}
	for(int i=1;i<=n;i++){
		if(x[i]==0){
			cout<<"114514"<<endl;
			continue;
		}
		cout<<x[i]<<" ";
	}	
	cout<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 题解：P10733 [NOISG2019 Prelim] Lost Array

## 思路

对于任意 $\min(X_{A_{i}},X_{B_{i}})=C_{i}$。

只要让 $X_{A_{i}}$ 与 $C_{i}$ 取 $\max$ 值。

$X_{B_{i}}$ 与 $C_{i}$ 取 $\max$ 值。

这样可以让 $\min(X_{A_{i}},X_{B_{i}})$ 绝对是 $C_{i}$。

对于为赋值的数，初始化时都初始化为 $1$ 即可。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long n,m,f[10000000],a,b,c;
signed main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)f[i]=1;
	for(int i=1; i<=m; i++) {
		cin>>a>>b>>c;
		f[a]=max(f[a],c);
		f[b]=max(f[b],c);
	}
	for(int i=1; i<=n; i++)cout<<f[i]<<" ";
	return 0;
}
```

---

## 作者：wht_1218 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10733)。


------------

这是一道构造题。  
我们可以观察到：要使 $\min (X_{A_i},X_{B_i})=C_i$，就要让 $X_{A_i},X_{B_i}$ **至少**为 $C_i$。    
所以对于每一个关系式，让 $X_{A_i}=\max (X_{A_i},C_i),X_{B_i}=\max (X_{B_i},C_i)$，因为 $X_{A_i}$ 或 $X_{B_i}$ 可能大于 $C_i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100007],n,m;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)a[i]=1;
	while(m--){
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		a[x]=max(a[x],z);
		a[y]=max(a[y],z);
	}for(int i=1;i<=n;++i)printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：TheForgotten (赞：0)

# P10733 [NOISG2019 Prelim] Lost Array

[题目传送门](https://www.luogu.com.cn/problem/P10733)

## 题目描述
构造一个长度为 $N$ 的数组 $X$，使得数组中的每个数字在 $1$ 到 $10^9$ 之间，并且该数组满足所有的关系式

## 思路
因为题目保证数组存在，所以只要根据给出的关系式来确定数字，令 $\min (X_{A_i},X_{B_i})=C_i$，只需让 $X_{A_i}$ 和 $X_{B_i}$ 在大于 $C$ 时等于自己，在小于 $C$ 时等于 $C$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a,b,c,x[100005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a>>b>>c;
		x[a]=max(x[a],c);
		x[b]=max(x[b],c);
	}
	for(int i=1;i<=n;i++){
		if(x[i]==0) cout<<1<<"\n";
		else cout<<x[i]<<"\n";
	}
	return 0;
}
 
```

---

## 作者：pengzy (赞：0)

### 思路
构造限制是 $\min(X_{A_{i}},X_{B_{i}})=C_{i}$，翻译一下就是对于每个限制条件，要求 $X_{A_{i}} \ge C_{i},X_{B_{i}} \ge C_{i}$。所以每次输入限制条件时，我们要让 $X_{A_{i}}$ 和 $X_{B_{i}}$ 都取两数最大值。

没有限制条件就输出 $1$。

代码：
```cpp
int n,m,a,b,c,ans[Max];
int main()
{
	n=read(),m=read();
	while(m--) {
		a=read(),b=read(),c=read();
		ans[a]=max(ans[a],c);
		ans[b]=max(ans[b],c);
	}
	for(int i=1;i<=n;i++) {
		if(ans[i])write(ans[i]),putchar(' ');
		else puts("1");
	}
	return 0;
}
```

---

## 作者：JYX0924 (赞：0)

因为题目保证有解，所以直接对于每一次询问，令 $X_{a}=\max\{X_{a},c\}$，$X_{b}=\max\{X_{b},c\}$。

在输出时，若 $X_{i}=0$，就随意给它赋大于 $0$ 的值即可。

下面是我的 AC 代码。

```c
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int n,m,x,y,z,a[100005];
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>z; a[x]=max(a[x],z); a[y]=max(a[y],z);
	}
	for(int i=1;i<=n;i++) {if(a[i]==0) a[i]=1; cout<<a[i]<<" ";}
	return 0;
}
```
谢谢大家！！！

---

## 作者：zhanghy123 (赞：0)

想要满足 $\min(X_{A_i},X_{B_i})=c$，就可以在 $X_{A_i}$ 和 $X_{B_i}$ 的位置上取 $\max(X_{A_i},c)$ 和 $\max(X_{B_i},c)$，这样这两个位置上的数就满足条件。其他位置上的数随便给就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,n,m,x[100001];
int main()
{
	cin>>n>>m;
	for(int i=1; i<=m;i++)
	{
		cin>>a>>b>>c;
		x[a]=max(x[a],c);
		x[b]=max(x[b],c);
	}
	for(int i=1; i<=n; i++)
	{
		if(x[i])
			cout<<x[i]<<' ';
		else
			cout<<"99999 ";//随便给
	}
	return 0;
}

```

---

## 作者：iyka (赞：0)

本蒟蒻又来~~水~~写题解啦！

细看本题，题目中无处不在告诉你这道题是一道构造，但问题就在于怎么构造呢？

首先题目说一定有解，那就说明不可能出现几个关系式互相冲突的情况，那此时我们直接把 $x_a$ 和 $x_b$ 赋值成为 $\max(x_a,c)$ 和 $\max(x_b,c)$ 就可以保证对于关系式肯定是成立的，那 $x$ 中剩下的其它元素就可以随意赋值为任何大于等于 $1$ 且小于等于 $10^9$ 的数，最终 $x$ 数组就为本题答案。

### 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,mod=1e9;
int x[N],n,m;
int main()
{
	cin>>n>>m;
	for(int i=1,a,b,c;i<=m;++i)
		cin>>a>>b>>c, x[a]=max(x[a],c), x[b]=max(x[b],c);
	for(int i=1;i<=n;++i)
		cout<<((x[i]==0)?rand()%mod+1:x[i])<<" "; //"随意赋值"
	return 0;
}
```

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10733)

既然题目保证数组 $X$ 存在，所以这道题我们在每次输入时将 $X_a,X_b$ 与 $c$ 取最大值并赋值即可，无需考虑无解情况。

注意到有些 $X_i$ 没有被赋值，此时 $X_i$ 仍为初值 $0$。由于题目要求 $1\le X_i\le10^9$，所以我们给这些 $X_i$ 赋值一个位于 $[1,10^9]$ 内的数值即可，例如 $114514$。

```cpp
int x[100010];
signed main()
{
	int n,m;
	rd(n,m);
	while(m--)
	{
		int a,b,c;
		rd(a,b,c);
		x[a]=max(x[a],c),x[b]=max(x[b],c);
	}
	for(int i=1;i<=n;i++)
	{
		wt(x[i]?x[i]:114514),kg;
	}
	hh;
	return 0;
}
```

---

## 作者：donnieguo (赞：0)

## 题意简述

给定 $n$ 个数和 $m$ 条记录，每条记录有三个正整数 $a,b,c$，表示 $\min(X_a,X_b) = c$，其中 $X$ 为你构造的数组。

## 思路

其实这道题目很简单，对于每一组 $a,b,c$，我们只需要将 $X_a,X_b$ 的值都与 $c$ 取 $\max$，这样就可以保证所有的 $X_a$ 和 $X_b$ 的值都是 $c$，也就是 $\min(X_a,X_b)$ 的值一定是 $c$。最后输出即可。

- 最后要输出 $n$ 个数，对于一些没有赋值的数，输出任意值即可。因为如果某个 $X_i$ 没有被赋值，那么所有的 $a,b$ 一定不会等于 $i$，这里的任意值我就都取了 $1$。

- 任意值不能小于等于 $0$，因为题目中有一句话——

>
>数组中的每个数字在 $1$ 到 $10^9$ 之间。
>

~~本蒟蒻因为没看到这句话 WA 了两次~~

## AC代码

```cpp
#include <iostream>
using namespace std;

int n, m;
int a, b, c, x[100010];
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b >> c;
		x[a] = max(x[a], c);
		x[b] = max(x[b], c);
	}
	for (int i = 1; i <= n; i++)
		!x[i] ? cout << 1 << ' ' : cout << x[i] << ' ';
	return 0;
}
```

---

