# Playing Cubes

## 题目描述

Petya and Vasya decided to play a little. They found $ n $ red cubes and $ m $ blue cubes. The game goes like that: the players take turns to choose a cube of some color (red or blue) and put it in a line from left to right (overall the line will have $ n+m $ cubes). Petya moves first. Petya's task is to get as many pairs of neighbouring cubes of the same color as possible. Vasya's task is to get as many pairs of neighbouring cubes of different colors as possible.

The number of Petya's points in the game is the number of pairs of neighboring cubes of the same color in the line, the number of Vasya's points in the game is the number of neighbouring cubes of the different color in the line. Your task is to calculate the score at the end of the game (Petya's and Vasya's points, correspondingly), if both boys are playing optimally well. To "play optimally well" first of all means to maximize the number of one's points, and second — to minimize the number of the opponent's points.

## 说明/提示

In the first test sample the optimal strategy for Petya is to put the blue cube in the line. After that there will be only red cubes left, so by the end of the game the line of cubes from left to right will look as \[blue, red, red, red\]. So, Petya gets 2 points and Vasya gets 1 point.

If Petya would choose the red cube during his first move, then, provided that both boys play optimally well, Petya would get 1 point and Vasya would get 2 points.

## 样例 #1

### 输入

```
3 1
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
3 2
```

# 题解

## 作者：cff_0102 (赞：4)

这道题是比较简单的，没有那么麻烦。

### 翻译：

有 $n$ 个红方块和 $m$ 个蓝方块 $(n,m \le 10^5)$，现在 Petya 先 Vasya 后二人轮流搭方块，如果上下两个方块颜色相同，则 Petya 得一分，否则 Vasya 得一分。问 Petya , Vasya 的最大可能得分分别是多少。

### 题解：

这里把 Petya 和 Vasya 简写为 P 和 V 。

一共 $n+m$ 个方块，就会有 $n+m-1$ 对相邻的方块，又因为相邻两个方块只有相同和不同两种情况，所以 P 和 V 的最高得分之和必然为 $n+m-1$。

因为 $n,m$ 个方块最多只有 $\min{(n,m)}$ 处不同，所以 V 最高得分为 $\min{(n,m)}$。

所以 P 的最高得分之和就是 $n+m-1-\min{(n,m)}=\max{(n,m)}-1$。

这道题就瞬间变为入门题目了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int n,m;//题目中的变量
	cin>>n>>m;//输入
	cout<<max(n,m)-1<<' '<<min(n,m)//上面推理过了
	return 0;
}
```
望管理能过这篇题解。

---

## 作者：Leaves_xw (赞：1)

~~看到只有两个人写我就过来了~~

### 题目大意：

有 $n$ 个红方块和 $m$ 个蓝方块 $(n,m \le 10^5)$ ，现在 Petya 先 Vasya 后二人轮流搭方块，如果上下两个方块颜色相同，则 Petya 得一分，否则 Vasya 得一分。问 Petya ,Vasya 的最大可能得分分别是多少。

### 思路分析：

若要使 Petya 得得分数得到最大，就是让 Petya 和 Vasya 选取相同的颜色，但是 $n,m$ 可能会不同，所以找出最大值即可，也就是 $max(n,m)$，由此可得出 Petya 能得到的最大分值为 $max(n,m)-1$。

若要使 Vasya 得得分数得到最大，就是让 Petya 和 Vasya 选取相同的颜色，同上可得出 Vasya 的最大得分为 $min(n,m)$。

### AC代码：

```
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;//定义n和m
    cin>>n>>m;//输入n，m
    cout<<max(n,m)-1<<' '<<min(n,m)<<endl;//输出公式
    return 0;
}
```

点个赞再走吧！

---

## 作者：H6_6Q (赞：1)

### 题目翻译：
有  $n$ 个红方块和 $m$ 个蓝方块 $(n,m \le 10^5)$，现在$A$ 和 $B$ 两个人轮流搭方块  $(A$ 先手 $)$，如果上下两个方块颜色相同，则 $A$ 得一分，否则 $B$ 得一分。问 $A$ , $B$ 的最大可能得分分别是多少。       
### 思路：
很显然：       
对于 $A$，放与上次相同颜色的方块一定更优。  
对于 $B$，放与上次不同颜色的方块一定更优。 
       
综合上述结论，我们开始分析。      
       
对于 $A$，一直到选了 $\min(n,m) \times 2$ 个方块时，每次 $A$ 都只有自己的放置能得一分，所以此时 $A$ 的得分为 $\min(n,m)$。       
在这之后，由于只剩下一种颜色，所以不论谁放都是 $A$ 得分，所以此时 $A$ 的得分为          
$\min(n,m) + ((n+m)-\min(n,m) \times 2)$       
化简后就是 $\max(n,m)$       
又因为 $A$ 是先手，所以首次放置一定不得分，所以还要减一，即 $\max(n,m) -1$。         

对于 $B$，由于最多也就 $\min(n,m)$ 种不同颜色的可能，而且只要每次放与上次不同的颜色，这所有的可能都一定会出现，所以 $B$ 的最大的分就是 $\min(n,m)$。         

综上所述：       
对于 $A$，答案为 $\max(n,m) -1$ 。  
对于 $B$，答案为 $\min(n,m) $。 

### Code:
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<cmath>
#include<queue>
#include<map>
#include<set>

using namespace std;

int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

int n,m; 

int main()
{
	n=read();m=read();
	printf("%d %d",max(n,m)-1,min(n,m));
    //分析了那么久，核心代码就这一行
	return 0;
}
```


---

## 作者：Loser_Syx (赞：0)

## 思路

由于 Petya 的得分方式是上下两个方块颜色相同才得分，所以 Petya 拿的方块永远都是与上一个方块颜色相同的，而 Vasya 的得分方式是上下两个方块颜色不同才得分的，所以 Vasya 拿的方块永远都是与前一个方块颜色不同的，然而 Petya 是先手，他得优先拿掉数量最少的方块中的一块，再是 Vasya 拿……以此类推，我们可以得出这么一个计算得分的公式：

Petya = $\max(n, m)- 1$

Vasya = $\min(n, m)$

这个时候，有人就会说：“为什么 Petya 的得分要减 $1$？”减去一是因为第一块拿走的方块不算分，而这一块是 Petya 拿的，Petya 的得分多算了 $1$，所以要减去。

## 代码：

```cpp
#include <bits/stdc++.h>
int main(){
    int a, b;
    std::cin >> a >> b;
    std::cout << std::max(a, b) - 1 << " " << std::min(a, b);
}
```

---

