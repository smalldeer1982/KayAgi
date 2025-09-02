# Color Game

## 题目描述

$n$ 个白色石头以相等的间隔排列。相邻石头之间的距离为 $1$。两个玩家用这块石头玩游戏。每个玩家轮流选择白色石头并将其变为黑色。但是，不能从前一回合变黑的石头中选择距离在 $k$ 内的石头。不能选择白色石头的玩家输了。在这个游戏中，双方采用最优策略，询问先手必胜或者后手必胜。

## 样例 #1

### 输入

```
2 1```

### 输出

```
first```

## 样例 #2

### 输入

```
3 0```

### 输出

```
first```

# 题解

## 作者：wangyi_c (赞：1)

## 0.前言

[题目传送门](https://www.luogu.com.cn/problem/AT1074)

## 1.题目大意

$n$ 个白色石头以相等的间隔排列。相邻石头之间的距离为  $1$。两个玩家用这块石头玩游戏。每个玩家轮流选择白色石头并将其变为黑色。但是，不能从前一回合变黑的石头中选择距离在 $k$ 内的石头。不能选择白色石头的玩家输了。在这个游戏中，双方采用最优策略，询问先手必胜或者后手必胜。

## 2.思路讲解

这道题我们要分类讨论：

- 当 $n÷2$ $\le$ $k$ 时，只要先手方涂黑中间的那个石子，后手必输。

- 当 $n$ 为奇数时，那么最后一个石子是先手方涂黑的，后手必输。

- 当 $n$ 为偶数时，那么最后一个石子是后手方涂黑的，先手必输。

这样我们就可以简简单单的得出代码了。

## 3.AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
signed main(){
	cin>>n>>k;
	if(k>=n/2){//第一种情况
		cout<<"first"<<"\n";
	}
	else if(n%2==1){//第二种情况
		cout<<"first"<<"\n";
	}
	else{//第三种情况
		cout<<"second"<<"\n";
	}
	return 0;
}
```
_THE END_

谢谢观看

By wangyi

---

## 作者：_Hero_ (赞：1)

# 题目大意
有两个人在长度为 $n$ 的 等距白色石头列中做游戏，规则是轮流选择白色石头并把它涂成黑色，但是不能涂离前一回涂成的石头距离 $k$ 内的石头。问如果两人都采取最优策略，是先手赢还是后手赢。

# 分析
三种情况：

1. $k$ 比 $n$ 的一半大或与它相等，直接把中间涂掉，那先手就赢了。
2. 如果 $n$ 是奇数，那对方最后会没地方下，所以先手赢。
3. 如果 $n$ 是偶数，那先手自己会无处可下，所以后手赢。

最后注意要换行。

# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
   cin>>n>>k;
   if(k>=n/2||n%2==1)
   cout<<"first"<<endl;
   else
   cout<<"second"<<endl;
   return 0;
}

```


---

## 作者：guozhetao (赞：1)

## 题目大意

$n$ 个白色石头以相等的间隔排列。相邻石头之间的距离为 $1$。两个玩家用这块石头玩游戏。每个玩家轮流选择白色石头并将其变为黑色。但是，不能从前一回合变黑的石头中选择距离在 $k$ 内的石头。不能选择白色石头的玩家输了。在这个游戏中，双方采用最优策略，询问先手必胜或者后手必胜。
## 思路
首先，如果 $k$ $\geq$ $\dfrac{2}{n}$，那么第一步先手下最中间的位置就赢了（$k$ $\geq$ $\dfrac{2}{n}$，所以最中间的位置往左和往右都放不了）。

如果 $k$ $<$ $\dfrac{2}{n}$，那么就相当于每一个位置都能放置。这样如果 $n \bmod 2 = 1$,那么先手赢，否则后手赢。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main() {
	scanf("%d%d",&n,&k);
	if(k >= n / 2 or n % 2) printf("first\n");
	else printf("second\n");
}
```


---

## 作者：alex_liu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT1074)

## 思路：

先手必胜的两种情况：

1. $n \leq k\times 2$ 则先手必胜（直接放中间）

2. $n \bmod 2$ 为奇数时 则先手必胜（所以石头都会被选）

除了这两种情况外，先手必输

话不多说上~~压行~~代码吧！

## AC CODE ：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
    cin>>n>>k;
    puts((k<<1)>=n||(n&1)?"first":"second");
    return 0;
}
```


---

## 作者：DPseud (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT1074)

## 题意

翻译貌似有一点问题，纠正一下：

有 $n$ 个距离相等的白色石头，有两人用这些石头做游戏。

规则就是每个玩家轮流选择白色石头并将其变为黑色，但是不能从前一回合变黑的石头中选择距离在 $k$ 内的石头。

无法选择白色石头的玩家失败。

在这个游戏中，双方采用最优策略，询问先涂必胜或者后涂必胜。

## 思路

这是一道较为简单的思维题，我们可以画图分析：

当 $n=7$，$k=5$ 时，只需要涂黑中间的石头：

![](https://cdn.luogu.com.cn/upload/image_hosting/kx5653vk.png)

当 $n=15$，$k=3$ 时，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kghj5geu.png)

注：涂灰的是对手的，涂黑的是自己的。

能看到自己有 4 块涂黑的，对手有 3 块涂黑的，最后一块可涂黑的石头是自己涂的，因此也可以先出手必胜。

我们能总结出这些结论：

1. 如果 $k\geq n/2$，先出手必胜。

2. 如果 $k<n/2$ 但是 $n\bmod2=1$，先出手必胜。

3. 如果 $k<n/2$ 并且 $n\bmod2=0$ ，后出手必胜。

最后是你们都喜欢的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    register short n,k;//数据很小，我们可以用register short 
    cin>>n>>k;
    if(k>=n/2)cout<<"first";
    else if(n%2==1)cout<<"first";
    else cout<<"second";
    cout<<endl;//岛国题要输出回车结尾 
    return 0;
} 
```

---

## 作者：lky1433223 (赞：1)

本来想找一个线段染色的题结果搜到了这个

一看是日语的还挺开心就写了顺带提交了翻译

~~这题水~~

题意

Z大佬和W大佬玩~~球~~石头,一共有n个石头，可以选择任意一个石头把它变成另一个颜色，但是下一轮对手不可以选择距离这个石头k以内的石头。两个人都选择最优策略。

两种情况：

⑴如果k >= n /2，放在中间对手就没得选了。

⑵如果k < n 所有的石头肯定都会被选。所以就是n%2。

并没有必要放的代码

```cpp
//忽略以下懒得删的翻译
/*
n个白色石头以相等的间隔排列。 相邻石头之间的距离为1。
两个玩家用这块石头玩游戏。 每个玩家轮流选择白色石头并将其变为黑色。但是，不能选择上一回合被变黑的石头距离k以内的石头。
不能选择白色石头的玩家输了。
在这个游戏中，双方采用最优策略，询问先手必胜或者后手必胜。
输入：
    n表示石头的数量k表示不可选择的距离。(1 <= n <= 50, 0 <= k <= n)
输出：
    先手first 后手 second
*/
#include <bits/stdc++.h>
using namespace std;
int n, k;
int main()
{
    scanf("%d %d", &n, &k);
    cout << (n % 2 || k >= n / 2 ? "first" : "second") << endl;
    return 0;
}
```


---

## 作者：_easy_ (赞：0)

# 思路
1. 当 $k>\frac{2}{n}$ 时，先手只要涂中间的一个（奇数）或者两个中的一个（偶数），后手就涂不了了。

2. 当 $k<\frac{2}{n}$ 且 $n \bmod 2 = 1$ 时，最后一个涂黑石子的一定是先手，所以先手必胜。

3. 当 $k<\frac{2}{n}$ 且 $n \bmod 2 = 0$ 时，最后一个涂黑石子的一定是后手，所以后手必胜。


坑点：日本题目不管是不是多组数据末尾都要换行。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k; 
int main(){
	cin>>n>>k;
	if(k*2<n&&n%2==0){
		cout<<"second"<<endl;//  满足情况3
	}else{
		cout<<"first"<<endl;//  满足情况1或2
	}
	return 0;
}

```

---

## 作者：OoXiao_QioO (赞：0)

# 题目描述

$n$ 个白色石头以相等的间隔排列。相邻石头之间的距离为 $1$。两个玩家用这块石头玩游戏。每个玩家轮流选择白色石头并将其变为黑色。但是，不能从前一回合变黑的石头中选择距离在 $k$ 内的石头。不能选择白色石头的玩家输了。在这个游戏中，双方采用最优策略，询问先手必胜或者后手必胜。

# 思路

这道题一看就是博弈题，通常只需要判断几个条件即可，通过研究发现此题我们只需要判断三种情况即可。

- 如果 $k\ge n\div 2$，先手直接把最中间的石头涂黑，那么后手无论如何都是败局已定，所以输出 $\verb!first!$。

- 如果 $n$ 为奇数，那么最后一定会先手方涂黑一个石子后对方无处可下，故而败北，输出 $\verb!first!$。

- 如果 $n$ 为偶数，那么最后一定会后手方涂黑一个石子后对方无处可下，故而败北，输出 $\verb!second!$，后手终于赢了一局。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k;
	cin>>n>>k;
	//分情况判断即可 
	if(k>=n/2)
		return printf("first\n"),0;
	else if(n%2)
		return printf("first\n"),0;
	else
		return printf("second\n"),0;
	return 0;
}
```


---

## 作者：xmkevin (赞：0)

## 题目分析：

1、如果 $k ≤ n / 2$，那么先手下中间，就赢了。

2、否则如果 $n$ 为奇数，那么两个两个涂黑完后，先手涂黑最后一个，后手无处涂黑，则先手赢。

3、如果 $n$ 为偶数，则后手赢。

## 代码：

```cpp
#include<iostream>
using namespace std;
int main() {
	int n,k;
	cin>>n>>k; 
	if(k >= n / 2) cout<<"first\n";
	else if(n % 2 == 1) cout<<"first\n";
	else cout<<"second\n";
}
```

P.S.AT题目后面要加换行。

---

## 作者：Deamer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT1074)

# 思路：

我们分三种情况考虑：

- 如果 $k≥n/2$ ，先手方直接把中间的石子涂黑，对方就输了。

- 如果 $n$ 是奇数，那么最后一定会先手方涂黑一个石子后对方无处可下，故而败北。

- 如果 $n$ 是偶数，那么最后一定会后手方涂黑一个石子后对方无处可下，故而败北。

建议大家画图理解。

#  _Code_ 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
	scanf("%d%d",&n,&k);
	if(k>=n/2) printf("first\n");
	else if(n&1) printf("first\n");
	else printf("second\n");
	return 0;
}
```

[完结撒花！！！](https://www.luogu.com.cn/record/76952990)

---

## 作者：AEddy (赞：0)

### 题意：
有两个玩家玩石头，一共有 $n$ 个石头，可以选择任意一个石头把它变成黑色，但是下一轮对手不可以选择距离这个石头 $k$ 以内的石头。两个人都选择最优策略，询问先手必胜或者后手必胜。

### 思路：
先手赢一共分两种情况：

- 如果 $k\ge n\div2$，放在中间，后手就没得选了。

- 如果 $k<n\div2=1$ 且 $n\mod2=1$，后手也选不了了。

所以我们用三目运算符判断一下满足哪个情况直接输出答案。

```cpp
n%2||k>=n/2?"first":"second"
```

### 代码：
到此为止，这道题就[完结](https://www.luogu.com.cn/record/76942947)了。

下面是完整代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
    cin>>n>>k;
    cout<<(n%2||k>=n/2?"first":"second")<<endl;
    return 0;
}
```

---

## 作者：_acat_ (赞：0)

题目难度：$\color{#FE4C61} \text{入门}$

算法标签：$\color{#0E90D2} \text{模拟}$

## 题目大意：

有 $n$ 个距离相等的白色格子，有两人用这些格子做游戏。

规则就是每个玩家轮流选择白色格子并将其涂成黑色，但是不能从前一回合变黑的格子中选择距离在 $k$ 内的格子。

无法选择白色格子的玩家失败。

在这个游戏中，双方采用最优策略，询问先涂必胜或者后涂必胜。

## Sol

分 $3$ 种情况讨论。

1. 当 $n \div 2 \leq k$ 时，把最中间的棋子涂成黑色，这样周围棋子就都不能图了，所以输出 `first`。

2. 当 $k<n \div 2$ 但是 $n \mod 2=1$ 时，我们可以举个栗子：

假设 $n=11$，$k=2$。

（红色是 `first`，黄色是 `second`。）

![](https://cdn.luogu.com.cn/upload/image_hosting/rk51c048.png)

那么涂到最后，黄色就涂不了了，所以输出 `first`。

3. 当 $k<n \div 2$ 并且 $n \mod 2=0$ 时，红色无法再涂色了，所以输出 `second`。

## AC 代码

- **注意：AT 的题目输出要加 `\n`。**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,k;
    cin>>n>>k;
    if(k<n/2&&n%2==0)
    {
    	cout<<"second"<<endl;
        return 0;
    }
    cout<<"first"<<endl;
    return 0;
} 
```

---

## 作者：lrmlrm_ (赞：0)

# 题意
有 $ n $ 个距离相等的白色石头，有两个人用这些石头做游戏。规则就是每个玩家轮流选择白色石头并将其变为黑色，但是不能从前一回合变黑的石头中选择距离在 $ k $ 内的石头。无法选择白色石头的玩家失败。假设在这个游戏中，双方采用最优策略，问先涂必胜还是后涂必胜。

# 思路

不难发现规律如下 :

$ \ \ $ 1.如果 $ k \geq n \div 2 $ , 就是先手胜利 。

$ \ \ $ 2.如果 $ k \leq n \div 2 $ , 就要判断 $ n \mod 2 $ , 如果是 $ 1 $ , 先手胜利 ， 否则后手必胜 。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
int main(){
	scanf("%d%d",&n,&k);
	if(k>=n/2)printf("first\n");
	else if(n%2==1)printf("first\n");
	else printf("second\n");
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 题意简述
$n$ 个白色石头以相等的间隔排列。 相邻石头之间的距离为 $1$。 两个玩家用这块石头玩游戏。 每个玩家轮流选择白色石头并将其变为黑色。但是，不能从前一回合变黑的石头中选择距离在 $k$ 内的石头。 不能选择白色石头的玩家输了。 在这个游戏中，双方采用最优策略，询问先手必胜或者后手必胜。

### 题目分析
我们可以分情况分析：

1. 如果 $k>=n/2$，先手只要放在中间就必胜。
2. 如果 $k<n/2$，就判断 $n\bmod2$ 是多少。如果是 $1$，先手必胜；如果是 $0$，后手必胜。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
int main()
{
	cin>>n>>k;
	if(k>=n/2)cout<<"first\n";
	else if(n%2==1)cout<<"first\n";
	else cout<<"second\n";
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

[AT1074题目](https://www.luogu.com.cn/problem/AT1074)

#  题意

$n$ 个白色石头以相等的间隔排列。 相邻石头之间的距离为 $1$ 。 两个玩家用这块石头玩游戏。 每个玩家轮流选择白色石头并将其变为黑色。但是，不能从前一回合变黑的石头中选择距离在 $k$ 内的石头。 不能选择白色石头的玩家输了。 在这个游戏中，双方采用最优策略，询问先手必胜或者后手必胜。

# 思路

这是一道简单的题目（**考思维**）

其实输出 `first` 只有两种情况：

情况 $1$ : 如果 $k$ 大于 $n$ $\div$ $2$ ，输出 `first` 。

情况 $2$ : 如果 $k$ 小于 $n$ $\div$ $2$ 且 $n$ $\%$ $2$ 等于 $1$ ，输出 `first` 。

其它情况输出 `second`。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
int main()
{
	cin>>n>>m;//m代表k
	if(m>=n/2||(m<n/2&&n%2==1))cout<<"first"<<endl;
   else cout<<"second"<<endl;//注意在做AT题时，要加换行
	return 0;
} 
```

---

