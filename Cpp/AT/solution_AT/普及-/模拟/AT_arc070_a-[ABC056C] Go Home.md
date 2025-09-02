# [ABC056C] Go Home

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc056/tasks/arc070_a

無限に左右に伸びている数直線上の $ 0 $ の地点に時刻 $ 0 $ にカンガルーがいます。 カンガルーは時刻 $ i-1 $ から $ i $ にかけて、なにもしないか、もしくは長さがちょうど $ i $ のジャンプを、左右どちらかの方向を選んで行えます。 つまり、時刻 $ i-1 $ に座標 $ x $ にいたとすると、時刻 $ i $ には $ x-i $, $ x $, $ x+i $ のどれかに存在することが出来ます。 カンガルーの家は座標 $ X $ にあります。カンガルーはできるだけ早く座標 $ X $ まで移動しようとしています。 カンガルーが座標 $ X $ に到着する時刻の最小値を求めてください。

## 说明/提示

### 制約

- $ X $ は整数
- $ 1≦X≦10^9 $

### Sample Explanation 1

$ 3 $ 回右にジャンプすると時刻 $ 3 $ に家にたどり着けて、これが最小です。

### Sample Explanation 2

時刻 $ 0 $ にはなにもせず、時刻 $ 1 $ に右にジャンプすることで時刻 $ 2 $ に家にたどり着けます。

## 样例 #1

### 输入

```
6```

### 输出

```
3```

## 样例 #2

### 输入

```
2```

### 输出

```
2```

## 样例 #3

### 输入

```
11```

### 输出

```
5```

# 题解

## 作者：DLDZD (赞：1)

## 思路：
运用高斯的等差数列

### $\frac{n(n+1)}{2} $ 公式
从一开始，依次套公式，直到那个数套进去的值大于小于目标数，输出套到公式的那个数。
## code：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,ans=0;
	cin>>n;
	for(int i=0;i<n;i++){
		i+=ans++;//套公式
	}
	cout<<ans;//输出那个数
	return 0;
}
```


---

## 作者：simonG (赞：1)

### 前言
题意：袋鼠一次可以跳$\dfrac{n\times(n+1)}{2}$，问袋鼠怎么回家。
### 详解
>* 在数轴上，前后一样，所以取绝对值。
>* 若$\dfrac{n\times(n+1)}{2}>X$，那显而易见，每次只能走$n$，就无法回到$X$。
>* （$n$非定值，而是变化着的答案。）
>* 对于$\dfrac{n\times(n+1)}{2}$, 一定存在     
$$\dfrac{n\times(n+1)}{2}-2\times i=X$$

#### 法1

>* 可以暴力证明

```cpp
int sum=0,flag=0;
for(int i=1; i<=100; i++)  	//X位置
{
	for(int j=1; j<=100; j++) { //1+到n
		sum+=j;
		for(int k=1; k<=100; k++)//i多少
			if(sum-2*k==i) {
				cout<<i<<"YES\n";
				flag=1;
				break;
			}
		if(flag) {
			flag=0;
			break;
		}
	}
}
```

结果都是$"YES"$，故证。

#### 法2

>* 具体证：  
>* $\dfrac{n\times(n+1)}{2}=1+2+3+...+n$，而等于
$$1+2+3+...+(i-1)-i+(i+1)....+n$$
$$=\dfrac{n\times(n+1)}{2}-2\times i=X$$
>* 只要在袋鼠跳的过程中，又一次往回跳，既满足
>* 这里$i$的意思是当$i$秒时，袋鼠位置非$+i$而$-i$。所以本道题的答案就是$n$。
>* 即求$\dfrac{n\times(n+1)}{2}\geqslant X$时，$n$最小是几。  

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,ans,a;//ans,即n，a，是求袋鼠走到哪儿的
int main()
{
	scanf("%d",&x);
	x=abs(x);//输入，取绝对值
	while(a<x)
		ans++,a+=ans;//看n的结果
	printf("%d",ans);//输出
	return 0;
}
```

代码实现非常简单，重要看理解题意。

### 后记
#### 管理辛苦了！

---

## 作者：Cambridge (赞：1)


蒟蒻又来发题解了!

不知道为啥远程OJ尚未返回编译信息然后就CE了，但是本蒟蒻觉得我的做法是对的，于是就先来发一篇题解。所以我在这里声明：本题解代码1%的几率会WA！本题解代码1%的几率会WA！本题解代码1%的几率会WA！（重要的事情说三遍。）

这道题刚开始我看完题目的时候，第一反应：DFS或者BFS啊！但是当我看到X小于等于1000000000的时候······（你懂的。）那么这道题我们就只能用玄学了。首先，我们先求X的绝对值，毕竟往左往右走是一样的，这样可以简单一点。然后，反正袋鼠都是最终要到达家的，所以就走啊。当如果这一步走到的地方超过了X，那么，当前位置-X的那一步不走就行了。

思路如上，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
int x,time,place;
int main()
{
	cin>>x;
	x=abs(x);//取绝对值
	while(place<x)time++,place+=time;//具体原因看上方解释。
	cout<<time<<endl;//记得换行
    return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

