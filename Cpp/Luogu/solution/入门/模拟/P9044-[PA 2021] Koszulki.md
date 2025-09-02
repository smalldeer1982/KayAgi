# [PA 2021] Koszulki

## 题目描述

$n$ 个人参加一场比赛，其中第 $i$ 个人的得分为 $a_i$。

主办方决定至少颁发 $k$ 件礼物。

但是，若 $\exist 1 \leq x, y \leq n, a_x \geq a_y$ 且 $x$ 未拿到礼物但 $y$ 拿到礼物，$x$ 会不满意。

主办方希望每个人都满意，求颁发的礼物数量的最小值。

## 说明/提示

#### 样例 #1 解释
最优方案为除了最后一人以外全部送礼物。
#### 数据范围
对于 $100\%$ 的数据，$1 \leq k \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 120$。

## 样例 #1

### 输入

```
5 3
75 90 120 75 40```

### 输出

```
4```

# 题解

## 作者：small_john (赞：3)

## 分析

简单的**贪心**题。

总体思路：从分数高的人开始发礼物。

## 具体做法

用桶存储每个分数对应的人数。

接下来 $i$ 从满分 $120$ 开始向 $0$ 循环，$ans$ 加上分数为 $i$ 的人的个数。当 $ans$ 大于等于 $k$ 时，退出循环，输出 $ans$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int x,n,k,ans,ton[122];
int main()
{
	cin>>n>>k;
	for(int i = 1;i<=n;i++) 
	    cin>>x,ton[x]++;//在线操作 
	for(int i = 120;i>0;i--)
	{ 
	    ans+=ton[i];
	    if(ans>=k)
			break;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ice_fish01 (赞：3)

## $\text{P9044 [PA2021] Koszulki}$ 题解

### 本题算法：贪心。

### 思路分析

如果不考虑“至少颁发 $k$ 件礼物”这一条件，我们可以直接选择**不发**。

那么加上这个条件，我们先发分数高的，再发分数低的，每一批发完后发的总数 $\ge k$ 时结束就一定能满足条件。

所以我们可以通过**计数排序**来实现。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,t[114+5+14],k,n,ans;
signed main()
{
	cin >> n >> k;
	for(int i = 1;i <= n;i++)
	{
		cin >> a;
		t[a]++;
	}
	for(int j = 120;j >= 0;j--)
	{
		ans += t[j];
		if(ans >= k) // 不要再浪费礼物了 
			break;
	}
	cout << ans;
	return 0;
}

```


---

## 作者：Light_Star_RPmax_AFO (赞：2)

## 前言

[题目传送](https://www.luogu.com.cn/problem/P9044)

### 题目

# [PA2021] Koszulki

## 题目描述

$n$ 个人参加一场比赛，其中第 $i$ 个人的得分为 $a_i$。

主办方决定至少颁发 $k$ 件礼物。

但是，若 $\exist 1 \leq x < y \leq n, a_x \geq a_y$ 且 $x$ 未拿到礼物但 $y$ 拿到礼物，$x$ 会不满意。

主办方希望每个人都满意，求颁发的礼物数量的最小值。

# 贪心

一道红题

这题肯定要先满足高分先发，所以我们就用 **桶排序** ，这样我们就可以记录每个分数有多少人。

为了让礼物数最少，我们就在比 $k$ 高的时候直接输出就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>a;//桶。
int main(){
	int a[10010],x;
	int n,ans=0,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>x,a[x]++;
	for(int i=120;i>=0;i--){
		ans+=a[i];
		if(ans>=k){cout<<ans;return 0;}
	}
}
```


---

## 作者：BlackPanda (赞：1)

**[Problem](https://www.luogu.com.cn/problem/P9044)**

------------
## Description

有 $n$ 个人，其中第 $i$ 个人的分数是 $a_i$，主办方希望至少颁发 $k$ 个礼物，如果 $\forall 1 \le x < y \le n,a_x \ge a_y$ 且 $x$ 没领到礼物 $y$ 领到了，那么 $x$ 会不满意。

主办方希望每个人都满意，求颁发的礼物数量的最小值。

------------
## Solution

简单贪心。

由于 $1 \le a_i \le 120$，所以可以开一个桶将所有数排序，然后从大到小颁发礼物，当领到礼物的人数大于等于 $k$ 的时候就退出。

------------
## Code


```cpp
#include <iostream>
using namespace std;

int n, k;
int a, c[2005];
int res;

int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i ++ )
	{
		cin >> a;
		c[a] ++ ;
	}
	for (int i = 120; i >= 1; i -- )
	{
		res += c[i];
		if (res >= k)
		{
			cout << res << endl;
			break;
		}
	}
	return 0;
}


```

---

## 作者：ImNot6Dora (赞：1)

大蒟蒻——我，终于来主题库发题解啦 WOW！
### 正文
一道比较普通的贪心题，属于很水的红题类型。

由于 $a_i$ 可能相同，而最高分数是 $120$，所以这题明显是让我们用桶排序做。

为了让所有人都满意，所以如果发现目前记录的礼品数量加上下一个分数的所有人超过了 $k$，那就加上这些人数并立即跳出循环。而这道题必须从大到小遍历。

代码思路自认为非常清晰，就不放注释了。
# AC C++ CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[121],n,k,c,ans=0,maxx=-1,minn=121;
int main(){
	cin>>n>>k;
	while(n--){
		cin>>c;
		a[c]++;
		maxx=max(maxx,c);
		minn=min(minn,c);
	} 
	for(int i=maxx;i>=minn;i--){
		if(ans+a[i]>=k){
			cout<<ans+a[i];
			return 0;
		}
		ans+=a[i];
	}
	cout<<ans;
	return 0;
}
```
By ImNot6Dora

---

## 作者：Loser_Syx (赞：0)

## 思路

贪心思路，很好理解，要发出最少的奖品，肯定要优先发给分数最高的人，那么我们就可以用一个计数桶来存储每个分数的的人数（分数最高 $120$，最低 $1$），一直相加，直到发的总人数 $\geq k$。

## 代码

```cpp
#include <cstdio>
int a[114514], ans, n, k;
main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		a[x]++;
	}
	for(int i = 120; i >= 0; i--){
		ans += a[i];
		if(ans >= k) break;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：E5pe7ance_ (赞：0)

简单贪心题，有点像[直播获奖](https://www.luogu.com.cn/problem/P7072)削弱版，建议评红。

为了防止有人不满意的情况出现，我们从分数最高的人开始颁发礼物。

用一个桶存储每人的分数即可，再从满分 $ 120 $ 开始加每个分数的人数。当总人数大于等于 $ k $ 时，结束。

```cpp
#include <iostream>
using namespace std;
int n, k, ans = 0, a[2005], tong[122];
int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++) 
	{
	    cin >> a[i];
	    tong[a[i]]++;
	}
	for (int i = 120; i > 0; i--) 
	{
	    ans += tong[i];
	    if (ans >= k) break;
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：CuteMurasame (赞：0)

### 前言

一眼贪心，大水题！

### 分析

因为 $a_i\leq 120$，明显可以用桶记录，贪心从后**往前累加**（否则会有人不满意）。当累加的人数超过**或等于**题目中的 $k$ 时，退出，输出答案。

### 代码

```cpp
#include<bits/stdc++.h>
#define N 121
using namespace std;
inline int read() //快读
{
    int x=0; bool f=1; char ch=getchar();
    while(!isdigit(ch)) f=ch=='-'?0:1,ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?x:-x;
}
inline void write(int x) //快写
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
}
int n,k,ans,t[N]; //t[N] 为桶
int main()
{
	n=read(),k=read();
	for(int i=1;i<=n;++i) ++t[read()]; // 用桶记录每个分数有多少人
	for(int i=N-1;i>=1;--i)
        if((ans+=t[i])>=k) break; //相当于 {ans+=t[i]; if(ans>=k) break;}
	write(ans); //输出结果
	return 0;
}
```

---

