# Union of Doubly Linked Lists

## 题目描述

双向链表是一种基本的数据结构。一个双向链表是一串元素序列。链表中每一个元素都链接着它前面和后面的元素。在这个问题中，这个链表是一个线性序列。除了第一个元素外，每个元素都有一个直接前导；除了最后一个元素外，每个元素都有一个直接后继。这个链表不形成一个环。

在这个问题中，你被给予了$n$个单元。这些单元能够形成一个或者多个双向链表。每个单元包含着一些链表元素的信息。这些单元的编号是从$1$至$n$的。

对于每个单元，有两个属性：

$l_i$表示第$i$个单元的前导；

$r_i$表示第$i$个单元的后继。

如果$l_i=0$，表示这个单元没有直接前导。如果$r_i=0$，表示这个单元没有直接后继。


| $i$  | $l_{i}$ | $r_{i}$ |
| ---- | ------- | ------- |
| 1    | 4       | 7       |
| 2    | 5       | 0       |
| 3    | 0       | 0       |
| 4    | 6       | 1       |
| 5    | 0       | 2       |
| 6    | 0       | 4       |
| 7    | 1       | 0       |

你的任务是，给定若干个由如上方式表示的双向链表，链接这些双向链表使得其仅构成一个双向链表。注意：你只能通过链接两个双向链表的首尾单元来链接这两个双向链表。

## 样例 #1

### 输入

```
7
4 7
5 0
0 0
6 1
0 2
0 4
1 0
```

### 输出

```
4 7
5 6
0 5
6 1
3 2
2 4
1 0
```

# 题解

## 作者：_zqh_ (赞：1)

# 思路简述

只需要开两个数组 $\text{Next}$ 和 $\text{Last}$ 分别记录前驱和后继；

然后从 $1$ 到 $n$ 将所有双向链表相连即可。

# Code

```cpp


#include <bits/stdc++.h>
#define ios                  \
	ios::sync_with_stdio(0); \
	cin.tie(0);              \
	cout.tie(0)
// #pragma GCC optimize(2)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define il inline
#define p_q priority_queue 
#define u_m unordered_map 
using namespace std;

int n;

vector<int> Next, Last;

int main() {
	ios;
	cin >> n;
	Next = vector<int>(n + 1);
	Last = vector<int>(n + 1);
	for (int i = 1; i <= n; i++) {
		int x, y;
		cin >> Next[i] >> Last[i];
	}
	int t = 0;
	for (int i = 1; i <= n; i++) {
		if (Next[i] == 0) {
			Next[i] = t;
			Last[t] = i;
			t = i;
			while (Last[t] != 0) {
				t = Last[t];
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << Next[i] << " " << Last[i] << endl;
	}
	return 0;
}
```

---

## 作者：_Execution_ (赞：1)

## 题意

给出一堆双向链表，把这些链表连起来。

## 思路

直接模拟，把链表连到上一个的尾部，输出每个链表的尾元素即可。

## 细节

注意编号是从 $1$ 开始的，循环时注意始末。

## 代码

```cpp
#include <iostream>
using namespace std;
int n, k;
int a[105], b[105];
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  for (int i = 1; i <= n; i++)
    if (!a[i]) {
      b[k] = i;
      a[i] = k;
      k = i;
      while (b[k]) {
        k = b[k];
      }
    }
  for (int i = 1; i <= n; i++) {
    cout << a[i] << " " << b[i] << endl;
  }
  return 0;
}
```




---

## 作者：泠小毒 (赞：1)

# Union of Doubly Linked Lists
给你一堆双向链表，让你把这些双向链表连成一条
## 解法
每次找到一条链表，将头连向上一个尾，将尾存下

最后输出即可
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,lst,a[110],b[110];
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i] >> b[i];
	for(int i=1;i<=n;i++)if(a[i]==0)
	{
		b[lst]=i,a[i]=lst,lst=i;
		while(b[lst])lst=b[lst];
	}
	for(int i=1;i<=n;i++)
		cout << a[i] << " " << b[i] << endl;
	return 0;
}
```

---

## 作者：Rookie_t (赞：0)

题目上说要用双向链表，可以用手打链表的方法解决。

就是让这些链表头尾相接形成一个环，然后用数组模拟构造双向链表和将链表首尾相接的过程。

具体看代码： 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l[105],r[105],n,Next;
signed main(){
	ios::sync_with_stdio(false);
    cin>>n;
    for(int i = 1;i <= n;i++){
    	cin>>l[i]>>r[i];
	}    
    for(int i = 1;i <= n;i++){
        if(!l[i]){
            r[Next] = i;
            l[i] = Next;
            Next = i;
            while(r[Next]){
                Next = r[Next];
            }
        }
    }
    for(int i = 1;i<=n;i++){
    	cout<<l[i]<<" "<<r[i]<<endl;
	}
    return 0;
}
```

---

## 作者：gaoleng_luogu_name (赞：0)

### 简要题意
~~话很多~~，其实只要看这一句就行了。

“你的任务是，给定若干个由如上方式表示的双向链表，链接这些双向链表使得其仅构成一个双向链表。注意：你只能通过链接两个双向链表的首尾单元来链接这两个双向链表。”

说白了，就是给你若干个双向链表，你只要将它们首尾相接后输出就行了。

### 思路
看懂题目后就简单了。让每一条链表的头连向上一个尾，再将尾更新。这里用数组模拟即可，不需要链表

### 代码
个人认为挺容易理解，不放注释了。~~码风丑陋，勿怪。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[105],w[105],n,Next;
void print()
{
	for(int i=1;i<=n;i++)
		printf("%d %d\n",t[i],w[i]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&t[i],&w[i]);
	for(int i=1;i<=n;i++)
	{
		if(!t[i])
		{
			w[Next]=i;
			t[i]=Next;
			Next=i;
			while(w[Next])
			{
				Next=w[Next];
			}
		}
	}
	print();
	return 0;
}
```
### 记录
[洛谷](https://www.luogu.com.cn/record/141589339)

[CF](https://codeforces.com/contest/847/submission/239776394)

---

## 作者：eric0928 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF847A)

## 题意
给你一些双向链表，让你把这些双向链表连起来。

## 思路
模拟即可，只需把上一条链表的尾巴和下一条链表的头连在一起，再把尾巴的值存下来就好了。链表实现其实可以用数组模拟。

## 代码
~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=105; 
int a[maxn],b[maxn];
int n,cnt;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;i++){
		if(!a[i]){
			b[cnt]=i,a[i]=cnt,cnt=i;
			while(b[cnt]) cnt=b[cnt];
		}
	}	
	for(int i=1;i<=n;i++) printf("%d %d\n",a[i],b[i]);
	return 0;
}
~~~

---

## 作者：Davis_xu (赞：0)

# **题意**
题面看着挺长的，有点复杂。但翻译一下即为：给你一些双向链表，把他们首尾相连，最后输出。
# **思路**
每次将这个链表头与上一次的尾连起来，再将尾更新为当前的尾（事实上，只需要用数组模拟即可，无需链表）。
# **代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e2+10;
int n,f,a[N],b[N];
int main(){
    ios::sync_with_stdio(false);//去同步
    cin.tie(0);cout.tie(0);
    cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    //输入
	for(int i=1;i<=n;i++){
        if(a[i]==0){
		    b[f]=i;
            a[i]=f;
            f=i;
		    while(b[f]) f=b[f];//连接
	    }
    }
	for(int i=1;i<=n;i++) cout<<a[i]<<" "<<b[i]<<endl;//输出
    return 0;
}
```


---

## 作者：NaOHqwq (赞：0)

## 题意

题面有一点点长，但其实就是给出几个双向链表，让我们把这些链表连成一条，且只能通过链接两个双向链表的首尾单元来链接这两个双向链表。

## 思路

模拟，只需要让每一条链表的头连向上一个尾，在把尾的值存下来就可以让这些链表连成一条了。

这里笔者就直接用数组模拟了，因为会比较简单。（也是因为笔者比较菜）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100+5; 
int a[maxn], b[maxn];
int n, nxt;//nxt是存尾的变量
int main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i] >> b[i];
	}
	for(int i = 1;i <= n;i++){
		if(a[i] == 0){
			b[nxt] = i;
			a[i] = nxt;
			nxt = i;
			while(b[nxt]){
				nxt = b[nxt];
			}//链接两个链表的头尾
		}
	}	
	for(int i = 1;i <= n;i++){
		cout << a[i] << " " << b[i] << endl;
	}
	return 0;
}
```

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/847/A)|[链接](https://www.luogu.com.cn/problem/CF847A)

### 题目大意

给出一些双向链表，其中有一些链表已经连接在了一起。现在把这些链表连成一条，求原来每条链表现在的前驱后继。

### 题目分析

对于链表前驱后继的记录，可以使用 ```pair``` 数组。```<pair(数据类型),(数据类型)>``` 相当于一个结构体，如下：

```cpp
struct pair{
	(数据类型) first,second;
};
```

而其中的 ```first``` 为第一个元素，```second``` 为第二个元素。

其余模拟即可，只需要每次找出一个无前驱的链表接在现在链表的末尾即可。

### 参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
pair<int,int>a[105];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].first,&a[i].second);
	for(int i=1;i<=n;i++)
		if(!a[i].first)
		{
			a[q].second=i;
			a[i].first=q;
			q=i;
			while(a[q].second)q=a[q].second;
		}
	for(int i=1;i<=n;i++)printf("%d %d\n",a[i].first,a[i].second);
	return 0;
}
```
感谢你的阅读！

---

## 作者：MuLinnnnn (赞：0)

原题目链接：[Luogu](https://www.luogu.com.cn/problem/CF847A) & [CodeForces](https://codeforces.com/contest/847/problem/A)

**题目大意**

给出一些双向链表，让你将这些链表连成一条。

我们只需要一个变量 $nxt$ 标注**后继**，找到可连接的地方枚举 $nxt$ 的位置。

**AC Code:**
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int l[103],r[103];

int main(){
    int n;
    scanf("%d",&n);
    int nxt = 0; // 后继初始值为0
    for(int i = 1; i <= n; ++i)
    	scanf("%d%d",&l[i],&r[i]); //input
    for(int i = 1; i <= n; ++i){
    	if(l[i] == 0){ //找到
    		r[nxt] = i;
    		l[i] = nxt;
    		nxt = i;
    		while(r[nxt]){ // 寻找下一个nxt
    			nxt = r[nxt];
			}
		}
	}
    for(int i = 1; i <= n; ++i)
    	printf("%d %d\n",l[i],r[i]); //output
	return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/111712453)

---

## 作者：mqxmm (赞：0)

# 小兔的话
欢迎大家在评论区留言哦 $\sim$  

## 简单题意
给出 $n(n \leq 100)$ 个数的前驱和后继，每个数会与前驱和后继相连接，这些数会连接成一些旧链表  
每条旧链表的起点都是前驱为 $0$（没有前驱）的数，终点都是后继为 $0$ （没有后继） 的数  
请你把这些旧链表连接成 $1$ 条新链表，并输出每个数在这条新链表中的前驱和后继（如果有多种连接方案，输出任意一种即可）  

## 题目解析
题目已经给出了每个数的前驱和后继，并且每条链表的起点 都是前驱为 $0$ 的数  
我们先可以预处理出每条旧链表的起点和终点，就是从每一个前驱为 $0$ 的数开始向后继搜索，一直搜索到没有后继为止，搜索中的第一个数为起点、最后一个数为终点  
再把每条链表的终点和下一条链表的起点连接起来，最后就可以得到 $1$ 条新链表了  

## 样例分析

```cpp
样例输入：
4 7
5 0
0 0
6 1
0 2
0 4
1 0
```

把旧链表预处理出来：$3$、$5-2$、$6-4-1-7$  
把旧链表连接起来：$3 \to 5-2 \to 6-4-1-7$  
连接之后，得出新链表：$3-5-2-6-4-1-7$  

```cpp
样例输出:
4 7
5 6
0 5
6 1
3 2
2 4
1 0
```

## 代码（纯数组）
```cpp
#include <cstdio>

int rint()
{
	int x = 0, fx = 1; char c = getchar();
	while (c < '0' || c > '9') { fx ^= (c == '-'); c = getchar(); }
	while ('0' <= c && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	if (!fx) return -x;
	return x;
}

const int MAX_n = 100;
int n, now;
int u[MAX_n + 5]; // 前驱 
int v[MAX_n + 5]; // 后继 

int main()
{
	n = rint();
	for (int i = 1; i <= n; i++)
		u[i] = rint(), v[i] = rint();
	for (int i = 1; i <= n; i++)
	{
		if (u[i] == 0) // 没有前驱的肯定是一条子链表的起点 
		{
			v[now] = i; u[i] = now; now = i;
			// 与上一条子链表相连 
			while (v[now]) now = v[now]; // 向后搜索 
			// 循环结束, 找到当前子链表的终点 
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d %d\n", u[i], v[i]);
	return 0;
}

```

## 代码（vector）
```cpp
#include <cstdio>
#include <vector>
using namespace std;

int rint()
{
	int x = 0, fx = 1; char c = getchar();
	while (c < '0' || c > '9') { fx ^= (c == '-'); c = getchar(); }
	while ('0' <= c && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	if (!fx) return -x;
	return x;
}

const int MAX_n = 100;
int n;
int u[MAX_n + 5]; // 前驱 
int v[MAX_n + 5]; // 后继 
vector<pair<int, int> > e; // pair 记录每条子链表的头和尾 

int DFS(int now)
{
	if (v[now] == 0) return now; // 返回终点 
	return DFS(v[now]); // 向后搜索 
}

int main()
{
	n = rint();
	for (int i = 1; i <= n; i++)
	{
		u[i] = rint();
		v[i] = rint();
	}
	for (int i = 1; i <= n; i++)
		if (u[i] == 0) e.push_back(make_pair(i, DFS(i))); // 插入当前子链表 (简化版, 只留头和尾, 中间的没有影响) 
	int siz = e.size();
	for (int i = 1; i < siz; i++)
	{
		v[e[i - 1].second] = e[i].first;
		u[e[i].first] = e[i - 1].second;
		// 每条子链表与前一个子链表相连 
	}
	for (int i = 1; i <= n; i++)
		printf("%d %d\n", u[i], v[i]);
	return 0;
}

```


---

## 作者：rui_er (赞：0)

模拟题。

根据题目给的若干个双向链表的信息，我们可以枚举一个点，向左搜该链表的左端点，向右搜该链表的右端点，标记 $vis$ 表示是否搜到过。这样我们就获得了每个链表的信息，然后按顺序把链表串联起来即可。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
using namespace std;
typedef long long ll;
const int N = 105; 

int n, l[N], r[N], lm[N], rm[N], tot, vis[N];
int* L[N];
int* R[N];
template<typename T> void chkmin(T &x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T &x, T y) {if(x < y) x = y;}

int main() {
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d%d", &l[i], &r[i]);
	rep(i, 1, n) if(!vis[i]) {
		vis[i] = 1;
		int u = i;
		while(l[u]) vis[u=l[u]] = 1;
		L[++tot] = &l[u];
		lm[tot] = u;
		u = i;
		while(r[u]) vis[u=r[u]] = 1;
		R[tot] = &r[u];
		rm[tot] = u;
	}
	rep(i, 2, tot) {
		*R[i-1] = lm[i];
		*L[i] = rm[i-1];
	}
	rep(i, 1, n) printf("%d %d\n", l[i], r[i]);
	return 0;
}
```

---

