# Caisa and Pylons

## 题目描述

Caisa 在玩游戏。

游戏中有从 $0$ 到 $n$ 编号的 $(n+1)$ 个电塔，编号为 $0$ 的电塔高度为 $0$，编号为 $i$ 的电塔高度为$h_i$。

游戏的目标是到达第 $n$ 个电塔，而玩家唯一能做的就是从当前电塔（不妨设编号为 $k$）跳到下一个电塔（编号为 $k+1$）。当玩家这样做时，他的能量值会增加 $h_k-h_{k+1}$（如果该值为负数，则玩家失去能量值）。

玩家必须保证在任何时候他的能量值非负。

Caisa 从 $0$ 号塔开始，问他在一开始最少需要多少能量值才能达到游戏的目标？

## 样例 #1

### 输入

```
5
3 4 3 2 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
4 4 4
```

### 输出

```
4
```

# 题解

## 作者：DiDi123 (赞：2)

# 一、题意

初始时一个人站在编号为 $0$ 的塔上，$h_0=0$，能量为 $E_0$，现在她需要跳 $n$ 个塔，从第 $i$ 个塔跳到第 $i+1$ 个塔能量变化值为 $E_{i+1}-E_i=\Delta E=h_i-h_{i+1}$，求使每个时刻的能量 $E_i\geq 0$ 的最小 $E_0$。

# 二、分析

$$
 
\begin{aligned}
\because\Delta E_{i+1}=&h_i-h_{i+1} \\
\therefore E_i-E_0=&\sum ^i _{j=0}\Delta E_j\\
=&\Delta E_1+\Delta E_2+\dots+\Delta E_i\\
=&(h_0-h_1)+(h_1-h_2)+\dots+(h_{i-1}-h_i)\\
=&h_0-h_i\\
=&-h_i
\end{aligned}
$$
所以保证 $E_i\geq0$ 也就是让 $E_0-h_i\geq0$，所以就找出最大的 $h_i$，让 $E_0=h_i$ 就好了。

回观这道题，其实发现 $\Delta E_i$ 就是一个差分数组（倒着的），而 $E_i$ 就是对差分数组求前缀和，应该就等于原数列。

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int maxx,n,h;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>h;
		maxx=max(maxx,h);
	}
	cout<<maxx;
}
```


---

## 作者：S__X (赞：1)

### 题意：
给定 $n$ 个位置的高度，$0$ 的位置为 $0$，每次移动一步时，需要消耗 $h_k-h_{k+1}$ 的能量，一开始能量为 $0$，过程中能量不能为负，求最少能量值为多少。

### 思路：
分析一下即可发现，题目就是求 $h$ 中的最大值。
这里我们可以用到 `max_element` 函数，`max_element` 是用来来查询最大值所在的第一个位置，所以在代码中我们可以输出其指向的位置。

### code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,h[100001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>h[i];
	cout<<*max_element(h+1,h+n+1);//注意不能endl换行
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析
直接按照题目模拟就行啦。我们在每一次移动到新的塔的时候记录一下现在所需的能量。由于需要满足所有的情况，所以我们还需要取一下这些塔需要的能量最大值。其中，相邻两个塔之间能量的变化量就是 $h_i-h_{i-1}$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
const int N=1e6+10;
int h[N];
int ans,maxx;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>h[i];
	}
	for(int i=1;i<=n;i++){ 
		ans+=h[i]-h[i-1];
		maxx=max(maxx,ans);
	}
	return cout<<maxx,0; 
}
```


---

## 作者：开始新的记忆 (赞：0)

题目大意：给定n个位置的高度，0的位置为0，每次移动一步时，需要消耗hi−hi+1的能量，一开始能量为0，过程中能量不能为负，一美元可以买一点能量，问说最小开销。

求最大值即可

```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<map>
using namespace std;
int main()
{   int a[100010],ans=0,n;
    cin>>n;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        ans=max(a[i],ans);
    cout<<ans;
	return 0;
}
```


---

