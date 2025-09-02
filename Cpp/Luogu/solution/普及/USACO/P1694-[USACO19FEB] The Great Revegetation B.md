# [USACO19FEB] The Great Revegetation B

## 题目描述

长时间的干旱使得 Farmer John 的 $N$ 块草地上牧草匮乏。随着雨季即将到来，现在应当是重新种植的时候了。

在 Farmer John 的储物棚里有四个桶，每个桶里装着一种不同的草种。他想要在每块草地上播种其中一种草。作为一名奶农，Farmer John 想要确保他的每头奶牛都能得到丰富的食谱。他的 $M$ 头奶牛每一头都有两块喜爱的草地，他想要确保这两块草地种植不同种类的草，从而每头奶牛都可以有两种草可供选择。Farmer John 知道没有一块草地受到多于 $3$ 头奶牛的喜爱。

请帮助 Farmer John 选择每块草地所种的草的种类，使得所有奶牛的营养需求都得到满足。 

## 样例 #1

### 输入

```
5 6
4 1
4 2
4 3
2 5
1 2
1 5```

### 输出

```
12133```

# 题解

## 作者：Licis_Subway (赞：4)

本题解主要使用贪心算法。

# 1. 思路
本题我们看到“Farmer John 知道没有一块草地受到多于 $3$ 头奶牛的喜爱。”这句话后，就可以明白一定可以使用贪心。

为了保证答案为字典序最小的答案，我们可以进行逐位进行求解。求完第一块草地的解后，我们再求后面的草地的解。

# 2. 做法
这样的话，我们就可以遍历每一个草地并进行枚举：

- 如果当前草地有牛喜欢……
	- 那头牛喜欢的另一个草地和当前草地一样？
    	- 枚举下一种草（当前草不能使用）。
    - 否则……
    	- 将当前草地匹配当前草类型。
 
就像这样：

```cpp
for(int i=1;i<=m;i++)
  scanf("%d%d",&a[i].first,&a[i].second);
```

接下来，枚举每一个草：

```cpp
for(int i=1;i<=n;i++)//每一个草地
{
    int grasstype=1;
    for(;grasstype<=4;grasstype++)//枚举四种草哪种可以
        if(check(i,grasstype))//如果可以
        {
            ans[i]=grasstype;//设置答案
            break;
        }
}
```

接下来，是重点部分（`check` 子函数）

```cpp
bool check(int grass,int x)
{
    set<int> cows=findcow(grass);//有哪些牛喜欢这片草地
    set<int>::iterator it=cows.begin();
    for(;it!=cows.end();it++)//枚举这些牛
    {
        if(a[*it].first==grass)//如果第一个存储的是当前草地（第二个为目标草地）
        {
            if(a[*it].second>=grass) continue;//检查目标草地是否还未存储答案
            if(ans[a[*it].second]==x) return false;//如果相等，则当前答案错误。
            else continue;
        }
        else//同理
        {
            if(a[*it].first>=grass) continue;
            if(ans[a[*it].first]==x) return false;
            else continue;
        }
    }
    return true;
}
```

`findcow` 子函数用来找出所有喜欢当前草地的牛，大概这样写：
```cpp
set<int> findcow(int grass)
{
    set<int> ans;
    for(int i=1;i<=m;i++)
        if(a[i].first==grass||a[i].second==grass) ans.insert(i);
    return ans;
}
```

到这里，本题就结束了。

# 3.完整代码
[这里](https://www.luogu.com.cn/paste/gw6asee8)
## 关于本题一定有解

这里为大家证明一下为什么本题一定有解。

[证明本题一定有解](https://www.luogu.com.cn/paste/f9sexaci)

---

## 作者：lflby (赞：3)

# 题意

有 $N$ 块草地和 $M$ 头奶牛，还有四种种子，每头奶牛喜欢两块草地，Farmer John 想要让奶牛吃不同的草，让我们构造出一种字典序最小的种草方法。

# 思路

我们可以把这道题当成一个图，对于每条边的两个端点种子不同。

题目说要字典序最小，所以我们从第一块草地开始，每次从 $1$ 开始到 $4$ 判断和他发射出去的端点是否有一样的。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<int>a[105];
int d[105];
int main()
{
	cin>>n>>m;
	for (int i = 1; i <= m; i++)
	{
		int x,y;
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			bool flag = true;
			for (int k = 0; k < a[i].size(); k++)
			{
				if (j==d[a[i][k]])
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				d[i]=j;
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cout<<d[i];
	}
	return 0;
}
```

---

## 作者：1234567890sjx (赞：3)

因为 Farmer John 知道没有一块草地受到多于 $3$ 头奶牛的喜爱，所以可以直接贪心。

枚举当前的第 $i$ 块土地，枚举种上了第 $1/2/3/4$ 种草，直接暴力枚举每一头奶牛判断是否可以满足需求即可。

时间复杂度 $O(nm)$。

---

## 作者：MarsNotFound (赞：2)

# P1694 题解

[题目传送门](https://www.luogu.com.cn/problem/P1694)

# 题意
输出一个长度为 $n$ 的由 $1$ 到 $4$ 构成的数列，且要求 $a_i$ 和 $b_i$ 的数字不同。

# 思路
看到范围第一时间想到爆搜，但这题可以用贪心来做。思路也不难，枚举 $1$ 到 $n$ 个田，$1$ 到 $4$ 的不同品种的草，再枚举 $1$ 到 $m$ 个要求，不符合要求就跳出循环换一种草，具体含义请看注释。时间复杂度为 $O(nm)$。

代码双手奉上。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005],b[1005],s[1005];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{	
		cin>>a[i]>>b[i];
		if(a[i]>b[i])swap(a[i],b[i]);
	}
	for(int i=1;i<=n;i++)
	{
		int j;
		for(j=1;j<=4;j++)
		{
			int flag=0;
			for	(int k=1;k<=m;k++)
			{
				if(b[k]==i && s[a[k]]==j)//当b[k]为当前选中的田但a[k]已经种植了相同类型的草时 
				{
					flag=1;//不成立，直接退出换下一种草 
					break;
				}
			}
			if(!flag)break;//没标记就是有成立的，直接退出
		}
		cout<<j;
		s[i]=j;
	}
	return 0;
}
```
由于是从小到大爆搜，所以可以保证字典序最小。

感谢管理员审核。

---

## 作者：JOKER_chu (赞：2)

## 题意

形式化的来说，需要你构造一个长度为 $N$，每一位为 $[1, 4]$ 之间的数字，最终的字符串要保证对于每一对输入的 $A_i$ $B_i$，满足 $A_i$ $B_i$ 的位置上的数字不同。

## 思路

输入时将不能相同的塞进 `vector` 里，然后枚举每个位置上的数字，检验是否可行，由于深搜具有字典序顺序，所以第一次搜出来的一定是所有解中最小的。

## 代码

模拟赛代码懒得改了，有 `freopen`。

```cpp
#include <iostream>

#include <cmath>

#include <algorithm>

#include <vector>

#define endl '\n'

using namespace std;

const int hutao = 1e2 + 5;

int n, m;
vector<int>end1[hutao];
bool v[hutao][15];

void s(int x, string sum){
  if(x > n){
    cout << sum; // 第一次搜出来的字典序最小
    exit(0); // 直接跳出程序，但据说不太稳定
  }
  for(int first = 1; first <= 4; ++first){ // 枚举这个位置能放的
    if(v[x][first] == 0){
      v[x][first] = 1;
      for(int second = 0; second < end1[x].size(); ++second){ // 检查是否能放
        v[end1[x][second]][first] = 1;
      }
      s(x + 1, sum + char(first + '0'));
      v[x][first] = 0;
      for(int second = 0; second < end1[x].size(); ++second){ // 回溯
        v[end1[x][second]][first] = 0;
      }
    }
  }
}

int main(){
  freopen("revegetate.in", "r", stdin);
  freopen("revegetate.out", "w", stdout);
  ios :: sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for(int first = 1, x, y; first <= m; ++first){
    cin >> x >> y;
    end1[x].push_back(y); // 将每对不能在一起的标记
    end1[y].push_back(x);
  }
  s(1, "");
  return 0;
}
```

---

## 作者：Mason123456 (赞：1)

## [P1694](https://www.luogu.com.cn/problem/P1694)

### 前言 & 思考方式

由于此题较基础，我们来学习一下在考场上如何快速找到思路。

先看数据范围，$N$ 的数据非常小，我们现在有理由怀疑这是**搜索**、**枚举**或 **DP**。然后在画个图，发现只需满足两个点不在输入的两个数 $a,b$ 中即可。

### 思路 & 解法

**贪心**，或者说**贪心** + **枚举**。只需**枚举** $1 \sim N$ 中**贪心**每个位置的最小值即可。注意一定要从左往右搜答案，这样可以满足答案最小。

### 代码 [#](https://www.luogu.com.cn/record/153258381)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 155;
int n, m;
int G[N][N], v[N];
int main(){
	cin>>n>>m;
	for(int i = 1;i <= m;i++){
		int a,b;
		cin>>a>>b;
		G[a][b] = 1;
		G[b][a] = 1;
     /*
     对于G[a][b]，表示a与b不同
     */
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= 4;j++){
			
			bool flag = 0;
			for(int k = 1;k <= m;k++){
				if(G[i][k] == 1 && v[k] == j){// 如果i要和j不同并且它们相同
					flag = 1;
					break;
					
				}
			}
			if(flag)	continue;
			v[i] = j;
			break;
			
		}
	}
	
	for(int i = 1;i <= n;i++){
		cout<<v[i];
	}
	return 0;
}

```

---

## 作者：carbon_monoxide (赞：1)

形式化题意：构造一个长度为 $n$ 的字符串，每一位取值范围为 1 到 4，输入的 $a_i$ 和 $b_i$ 保证两者位置的数不同。

看数据范围。真好！可以爆搜了。

直接暴力枚举每一位的数值来构造字符串。由于是从小到大枚举，所以可保证字典序最小。

个人觉得挺简单~~所以光明正大没加注释~~。

时间复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[160],b[160],c[110],k;
int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>a[i]>>b[i];
        if(a[i]>b[i]) swap(a[i],b[i]);
    }
    for(int i=1;i<=n;i++){
        for(k=1;k<=4;k++){
            int flag=0;
            for(int j=0;j<m;j++){
                if(b[j]==i&&c[a[j]]==k){
                    flag=1;
                    break;
                }
            }
            if(!flag) break;
        }
        cout<<k;
        c[i]=k;
    }
    return 0;
}
```

---

## 作者：pengzy (赞：0)

### 题意
给定 $n$ 和 $m$，求构造一个只包含数字 `1234` 的长度为 $n$ 的数列，使得 $m_{i}$ 的两个数不相同。

### 思路
一开始没有想法，不知道怎么贪心。后来发现数据范围小，可以暴力。

第一层循环暴力枚举 $n$ 片草地，第二层循环枚举这篇草地可以种哪种草。第三层循环枚举 $m$ 头牛，如果当前枚举的草地正好是牛喜欢的草地之一，我们分两种情况：

为方便表示，用 $a_{i}$，$b_{i}$ 分别表示第 $i$ 头牛喜欢的两片草地。

1. 枚举的草地正好和 $a_{i}$ 一样

此时不必去考虑 $b_{i}$ 如何，只要保证 $a_{i}$ 尽量小，且需要 $a_{i}$ 的草种满足其他牛的需求。

因为循环时草种从 $1$ 到 $4$，所以最后的数肯定字典序最小。

2. 枚举的草地正好和 $b_{i}$ 一样

此时需要 $b_{i}$ 的草种和 $a_{i}$ 不同。其他与第一种情况相同。

```cpp
const int Max=160;
int n,m,f[Max];
vector<int> ans;
struct cow{
	int a,b;//记录每头牛喜欢的两片草地 
}a[Max];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++) {
		a[i].a=read(),a[i].b=read();
		if(a[i].a>a[i].b)swap(a[i].a,a[i].b);
		//喜欢的两片草地先枚举小的 
	}
	for(int i=1;i<=n;i++) {//枚举草地 
		int j;
		for(j=1;j<=4;j++) {//枚举每片草地的草种 
			bool g=0;
			for(int k=1;k<=m;k++) {
				//对于第k只牛，喜欢的a草地之前已经种了
				//如果喜欢的a草地和现在枚举的草地草种一样 
				if(a[k].b==i&&f[a[k].a]==j) {
					g=1;
					break;
				}
			}
			if(g==0) {
				//如果当前草种合法，立即记录 
				f[i]=j;
				ans.push_back(j);
				break;
			}
		}
	}
	for(auto i:ans)write(i);
	return 0;
}
```

---

## 作者：Tjl0427 (赞：0)

## 题解：P1694 [USACO19FEB] The Great Revegetation B
### 题意
输出一个 $N$ 位在区间 $[ 1,4 ]$ 的的整数构成的，第 $a_i,b_i$ 位满足：$a_i \ne b_i$。
### 思路
通过二重循环暴力枚举每一格种的种类，并判断这个方案是否可行。要从左往右枚举，这样就可以保证答案最小。
### 代码
```c
#include<bits/stdc++.h>
using namespace std;
int n,m,x[200],y[200],z[200],k;
int main()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		cin>>x[i]>>y[i];
	    if(x[i]>y[i])
		{
			swap(x[i],y[i]);
		}
	}
    for(int i=1;i<=n;i++)
	{
		for(k=1;k<=4;k++)
		{
			int flag=0;
			for(int j=0;j<m;j++)
			{
			    if(y[j]==i&&z[x[j]]==k)
				{
					flag=1;
					break;
				}
			}
			if(!flag){
				break;
			}
		}
		cout<<k;
		z[i]=k;
	}
	return 0;
}
```

---

## 作者：卷王 (赞：0)

这题还是很简单的。

提供两种写法。

## 枚举

思路：通过二重循环暴力枚举每一格种的种类，在二重循环内判断这个方案是否可行。

实现：枚举第 $i(1\le i\le n)$ 格，种第 $j(1\le j\le 4)$ 种草，枚举第 $k(1\le k\le m)$ 个要求，判断是否可行，可行就输出 $j$。

## 递归

思路：使用 $c$ 数组记录每一个要求，然后从第 $1$ 格开始爆搜，对于每一格只放满足要求的草种。

实现：见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
bool flag = 0;
int c[107][107], cnt[107];
int t[107];
bool vis[7];

inline void dfs(int x) {
	if(x > n) {
		for(int i = 1; i <= n; i++) cout << t[i];
		exit(0);
	}
	for(int i = 1; i <= 4; i++) vis[i] = 0;
	for(int i = 1; i <= cnt[x]; i++) vis[t[c[x][i]]] = 1;
	for(int i = 1; i <= 4; i++) {
		if(vis[i]) continue;
		t[x] = i; dfs(x + 1); t[x] = 0;
	}
}

signed main() {
	n = read(), m = read();
	for(int i = 1; i <= m; i++) {
		int x = read(), y = read();
		if(x < y) swap(x, y);
		c[x][++cnt[x]] = y;
	}
	dfs(1);
	return 0;
}
```

---

## 作者：___QAQ__ (赞：0)

## 题意
简单来说，这题需要构造一个长度为 $N$，每一位为 $[1,4]$ 之间的数字的字符串, 保证最终字符串 $a_i,b_i$ 位上字符不相同，输出字典序最小的答案。
## 思路
枚举每一块草，模拟种草，若当前草地可种植，则按输入的 $a_i,b_i$ 暴力将之后的草块标记为不可种植。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e2 + 1, MAXM = 15e1 + 1;

struct Node{
  int a, b;
}pos[MAXM];

int n, m, ans;
bool su[MAXN][5];

bool cmp(const Node &x, const Node &y){
  return x.a != y.a ? x.a < y.a : x.b < y.b;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for(int i = 1; i <= m; i++){
    cin >> pos[i].a >> pos[i].b;
  }
  for(int i = 1; i <= n; i++){ //枚举每一块草
    for(int x = 1; x <= 4; x++){ //模拟种植4个种类的草
      if(!su[i][x]){ //当前位置可以种植
        cout << x;
        for(int j = 1; j <= m; j++){ //标记为不可种植
          if(pos[j].a == i){
            su[pos[j].b][x] = 1;
          }else if(pos[j].b == i){
            su[pos[j].a][x] = 1;
          }
        }
        break;
      }
    }
  }
  return 0;
}
```

时间 $O(nm)$。

---

