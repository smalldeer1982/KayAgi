# Walking in the Rain

## 题目描述

In Berland the opposition is going to arrange mass walking on the boulevard. The boulevard consists of $ n $ tiles that are lain in a row and are numbered from $ 1 $ to $ n $ from right to left. The opposition should start walking on the tile number $ 1 $ and the finish on the tile number $ n $ . During the walk it is allowed to move from right to left between adjacent tiles in a row, and jump over a tile. More formally, if you are standing on the tile number $ i $ $ (i&lt;n-1) $ , you can reach the tiles number $ i+1 $ or the tile number $ i+2 $ from it (if you stand on the tile number $ n-1 $ , you can only reach tile number $ n $ ). We can assume that all the opposition movements occur instantaneously.

In order to thwart an opposition rally, the Berland bloody regime organized the rain. The tiles on the boulevard are of poor quality and they are rapidly destroyed in the rain. We know that the $ i $ -th tile is destroyed after $ a_{i} $ days of rain (on day $ a_{i} $ tile isn't destroyed yet, and on day $ a_{i}+1 $ it is already destroyed). Of course, no one is allowed to walk on the destroyed tiles! So the walk of the opposition is considered thwarted, if either the tile number $ 1 $ is broken, or the tile number $ n $ is broken, or it is impossible to reach the tile number $ n $ from the tile number $ 1 $ if we can walk on undestroyed tiles.

The opposition wants to gather more supporters for their walk. Therefore, the more time they have to pack, the better. Help the opposition to calculate how much time they still have and tell us for how many days the walk from the tile number $ 1 $ to the tile number $ n $ will be possible.

## 说明/提示

In the first sample the second tile gets destroyed after day three, and the only path left is $ 1→3→4 $ . After day five there is a two-tile gap between the first and the last tile, you can't jump over it.

In the second sample path $ 1→3→5 $ is available up to day five, inclusive. On day six the last tile is destroyed and the walk is thwarted.

## 样例 #1

### 输入

```
4
10 3 5 10
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
10 2 8 3 5
```

### 输出

```
5
```

# 题解

## 作者：Lovely_Chtholly (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF192B)

### 【分析】

在第 $2$ 块到第 $n-1$ 块瓦片中，$2$ 块瓦片不能前进的时间是 $\max(a_i,a_{i+1})$，而需要求的就是最小的 $2$ 块瓦片的不能前进的时间。但是这里有一种特殊情况，就是起点和终点提前被毁坏了，若起点先被毁坏就无法出发，若终点先被毁坏就无法到达终点，所以刚才算出的答案需要与 $a_1$ 和 $a_n$ 取最小值。

### 【AC 代码】

```cpp
#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;
const int N=1e3+10,INF=0x3f3f3f3f;
inline int read(char ch=getchar(),int n=0,int m=1)
{
	while(ch<'0' or ch>'9')
	{
		if(ch=='-')m=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();
	return n*m;
}
ostream& operator <<(ostream& o,__uint128_t &a)
{
	__uint128_t x=a;
	stack<int>s;
	while(x)s.push(x%10),x/=10;
	while(!s.empty())o<<s.top(),s.pop();
	return o;
}
int n=read(),a[N],minn=INF;
signed main()
{
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<n;i++)minn=min(minn,max(a[i],a[i+1]));
	cout<<min(minn,min(a[1],a[n]));
	return 0;
}
```

---

## 作者：liuyi0905 (赞：2)

题意想必大家已经看懂了，接下来分析一下。

第 $i$ 块砖的时间为 $t_i$，那么其不能走的时间为 $\max(t_i,t_{i+1})$，但题目中说了，不能走每相邻两块砖中间的最小值。但题目中说了，如果你现在在第 $n-1$ 块砖上，就只能走一步，所以有一个特殊情况：起点或终点很早的时候就损坏了，就得特判一下。

关键代码：
```cpp
for(int i=2;i<n;i++){//从2到n-1遍历一遍
	maxi=max(t[i],t[i+1]);//算出不能走的时间
	mini=min(mini,maxi);//求最短的时间
}
cout<<min(mini,min(t[1],t[n]));//起点和终点做特殊处理
```

---

## 作者：_Kimi_ (赞：2)

### 题意:

有一条从 $1$ 到 $n$ 的路，第 $i$ 块瓦片会在第 $a_i$ 天损坏。

你可以跳一格者跳两格，准确地说，如果你在第 $i$ 格瓦片（$i < n - 1$），你可以到达 $i + 1$ 格或 $i + 2$ 格。

特别地，如果你在 $n - 1$ 格，那么你只可以跳一格。

答案求最晚到达第 $n$ 个瓦片的时间。

### 思路

显然地，如果有连续两个瓦片被破坏掉了，那么就过不去。

枚举从 $2$ 到 $n - 1$，对于每个 $i$，$a_i$ 和 $a_{i+1}$ 必然有其中一个先被损坏（或同时损坏）。

所以说这两块瓦片不能行走的时间是 $\max(a_i,a_{i+1})$。 

只要枚举出最小的两块瓦片不能行走的时间就是答案。

需要特别注意的是，前面之所以从 $2$ 到 $n - 1$ 是因为起点和终点可能先损坏。

如果起点先损坏就走不了了，如果终点先损坏就抵达不了终点。所以最后答案要与 $a_1$ 和 $a_n$ 比较。

### 代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int n, A[maxn], minn = maxn;
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> A[i];
	for(int i = 2; i <= n - 1; i++) {//枚举 
		maxx = max(A[i], A[i + 1]);//这两块瓦片不能行走的时间 
		ans = min(ans, maxx);//最少的时间 
	}
	cout << min(ans, min(A[1], A[n])) << endl;//与a_1 和 a_n 比较 
	return 0;
}
```


---

## 作者：yhylivedream (赞：1)

## 【思路】：

对于每连续两块砖，其不能走的时间为：$\max(t_i,t_{i+1})$，而题目要求的是：连续两块砖不能走的时间中的最小值，但是有一种特殊情况要考虑，那就是起点和终点被提前破坏了，所以我们算答案时还需跟 $a_1$ 和 $a_n$ 求最小值。

## 【代码】：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[1005], maxn = -1e9, ans = 1e9;
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 2; i <= n - 1; i++){
		maxi = max(a[i], a[i + 1]);
		ans = min(ans, maxn);
	}
	cout << min(ans, min(a[1], a[n]));
	return 0;
}
```


---

## 作者：Stars_visitor_tyw (赞：0)

## CF192B Walking in the Rain 题解
### 思路：
当两块相邻的瓦片都碎了就过不去了，所以在 $\max(a_i,a_{i+1})$ 时就不能走了。但题目中提到，如果在第 $n-1$ 块瓦片上则只能跳一步（毕竟不能超过终点），所以出现了一个特殊情况，那就是起点或终点早就碎了，所以还需要跟起点和终点取最小值。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n, a[200005], maxi, mini=1e9;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=2;i<=n-1;i++)
    {
        maxi=max(a[i],a[i+1]);
        mini=min(mini,maxi);
    }
    cout<<min(mini,min(a[1],a[n]));
    return 0;
}

---

## 作者：live_cxy110122 (赞：0)

# 题意：

有一条从 $1$ 到 $n$ 的路，第 $i$ 块瓦片会在第 $a_{i}$ 天结束时损坏，也就是可以存在 $a_{i}$ 天。

你可以跳一格或跳两格，准确地说，如果你在第 $i$ 格瓦片，你可以到达 $i+1$ 格或 $i+2$ 格。

特别情况，如果你在 $n−1$ 格，那么你只可以跳一格。

求最晚的可以从 $1$ 到达 $n$ 的天数。

------------

# 思路：
- 我们要从 $2$ 到 $n-1$ 枚举出一个最小值，也就是答案。

- 第 $i$ 块瓦片可以存在 $a_{i}$ 天，如果两个相邻的瓦片同时破碎，那就肯定过不去了，所以你必须站在在 $\max(a_i,a_{i+1})$ 的上面。

- 但是起点和终点可能很早就损坏了，所以我们算答案时还需要： $\min(a_1, a_n)$ 求最小值。

最后就可以开始写代码了

------------

# 代码：

```cpp
#include<bits/stdc++.h>		//万能头 
using namespace std;
const int N = 1e3+5;		//定义常量存储数据范围（个人习惯） 
int n, a[N], maxx = -1e9, minn = 1e9; //定义变量 
signed main()				//signed等于int（个人习惯） 
{
	cin>>n;
	for(int i = 1; i <= n; i++) 
		cin>>a[i];				 //输入 
	for(int i = 2; i <= n-1; i++)//枚举 
	{
		maxx = max(a[i], a[i+1]);//必须站在剩余时间更长的瓦片上 
		minn = min(minn, maxx);  //求时间 
	}
	cout<<min(minn, min(a[1], a[n]));//起点a[1]和终点a[n]需要求最小值 
	return 0;
}
```


---

## 作者：shengheng (赞：0)

注意是要求**最晚**可以从 $1$ 到达 $n$ 的天数。

## 思路

可以赖在 $\max a_i,a_{i+1}$ 上不走，除非起点终点被提前浇烂。这样一来，求出 $\max a_i,a_{i+1}$ 中的最小值，再与 $a_1$ 和 $a_n$ 比较即可。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
int n,a[1001],cnt=1e3+1,wal=-1e3-1;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<n;i++){
    	wal=max(a[i],a[i+1]);
    	cnt=min(cnt,wal);
	}cout<<min(cnt,min(a[1],a[n]));
	return 0;
}

```


---

## 作者：ruanshaochuan______ (赞：0)

设第 $i$ 块砖损坏的时间为 $t_i$，那么这块砖不能走的的时间就是 $\max(t_i,t_{i+1})$ 我们只要从 $2$ 到 $n-1$ 枚举出一个最小值即可，注意最后要和起点与终点取一个最小值，以防它们在很早的时候就损坏了。     
code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[1005],mini;
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
  	mini=min(a[1],a[n]);
	for(int i = 2; i <= n - 1; i++)mini=min(mini,max(a[i],a[i+1]));
        cout<<mini;
	return 0;
}
```


---

## 作者：coritom (赞：0)

## 思路
只要有两个相邻的瓦片同时破碎，那就肯定过不去了。所以你必须站在在 $\max(a_i, a_{i + 1})$ 的上面，而且要保证终点的瓦片没有破碎，否则就过不去了，所以要判断起点和终点的最小值。
## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[1005], maxi = -1e9, sum = 1e9;
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for(int i = 2; i <= n - 1; i++){
		maxi = max(a[i], a[i + 1]);
		sum = min(sum, maxi);
	}
	cout << min(sum, min(a[1], a[n]));
	return 0;
}
```


---

