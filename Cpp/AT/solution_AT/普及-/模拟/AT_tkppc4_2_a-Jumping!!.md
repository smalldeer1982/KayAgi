# Jumping!!

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tkppc4-2/tasks/tkppc4_2_a

配点 $ 200 $ 点

座標平面上にAliceがいます。彼女のいる座標は $ (0,0) $ です。

彼女は「桂馬飛び」のみで座標 $ (x,y) $ に行けるでしょうか。行ける場合は、最小で何回の桂馬飛びで行けるのかを求めてください。

なお、$ 1 $ 回の「桂馬飛び」とは以下の移動のことを指します。

- 座標 $ (a,b) $ にいる時、座標 $ (a+1,b+2) $ または $ (a-1,b+2) $ に移動する。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_tkppc4_2_a/c3b5225215411ad6fd5647f9473cbc184fa57e89.png)

## 说明/提示

### 制約

- 入力は全て整数である。
- $ -10^5\ \leq\ x,\ y\ \leq\ 10^5 $

### Sample Explanation 1

$ 1 $ 回目で $ (1,2) $ に飛び、$ 2 $ 回目で $ (0,4) $ に飛び、$ 3 $ 回目で $ (1,6) $ に飛ぶことでたどり着けます。 以下の画像のように動きます。 !\[\](https://img.atcoder.jp/tkppc4-2/1a9d0ec0c05411619f92b013a90c95b4.png)

### Sample Explanation 2

どのように動いても、座標 $ (6,\ 1) $ には桂馬飛びだけではたどり着けません。

## 样例 #1

### 输入

```
1 6```

### 输出

```
3```

## 样例 #2

### 输入

```
6 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
869 -120```

### 输出

```
-1```

# 题解

## 作者：Pink_Cut_Tree (赞：6)

### 思路

观察题目，每次可以走到 $(a+1,b+2)$ 或 $(a-1,b+2)$ 的位置。所以以下 $4$ 种情况要输出 `-1`。

1. 当 $y < 0$ 时一定走不到。

1. 当 $y$ 为奇数时一定走不到。

1. 当 $x>\frac{1}{2}y$ 时一定走不到。

1. 当 $x$ 与 $\frac{1}{2}y$ 奇偶性不同时一定走不到。

其余情况均合法，输出 $\frac{1}{2}y$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
int main(){
	cin>>x>>y;
	if(y<0||y%2==1){
		cout<<"-1";
	}
	else if(y<abs(x)*2){
		cout<<"-1";
	} 
	else if((y-abs(x)*2)%4!=0){
		cout<<"-1";
	}
	else{
		cout<<y/2;
	}
return 0;
}
```


---

## 作者：zhujiangyuan (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_tkppc4_2_a)
### 题意
你现在处于 $(0,0)$ 位置，你每次可以走到 $(a+1,b+2)$ 或 $(a-1,b+2)$ 的位置，其中 $a$ 和 $b$ 为你当前的坐标，问你最少走多少步到 $(x,y)$ 的位置。如果无法走到，输出 $-1$。
### 分析
- 因为不管 $a$ 是 $+1$ 还是 $-1$，$b$ 都是要 $+2$，所以 $y<0$ 的情况一定不能到达。
- 纵向每次移动两格，横向每次移动一格，所以最后的纵坐标一定大于等于横坐标的绝对值的 $2$ 倍，所以 $y<\left\vert a\right\vert \times 2$ 的情况一定不能到达。
- 当 $y\geq\left\vert a\right\vert \times 2$ 时，因为 $\frac{1}{2}y-\left\vert a\right\vert$ 一定是 $2$ 的倍数，所以 $y-\left\vert a\right\vert \times 2$ 必须是 $4$ 的倍数，所以 $y-\left\vert a\right\vert \times 2$ 的不是 $4$ 的倍数情况一定不能到达。
- 其他的情况都是可以到达的，因为纵向每次移动两格，所以输出 $y/2$ 即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x,y;
	cin>>x>>y;
	if(y<0) printf("-1\n");
   	else if(y<abs(x)*2) printf("-1\n");
	else if((y-abs(x)*2)%4!=0) printf("-1\n");
	else printf("%d\n",y/2);
	return 0;
}
```


---

## 作者：_7Mr (赞：2)

# 思路
- 因为 $b$ 一直在 $+2$ 所以 $y$ 不能是一个奇数，也不能是一个负数。

- 因为 $a$ 一直在 $+1$ 所以 $y \div 2$ 的奇偶性与 $x$ 的奇偶性一定是一样的。

- 最后如果 $a>b$ 也是不行的 因为 $+1$ 肯定不会大于 $+2$。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
int x,y;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>x>>y;
	if(y%2!=0 || y<0) {//第一种情况
		cout<<-1<<endl;
		return 0;
	}
	x=abs(x);
	y/=2;
	if(x%2!=y%2) {//第二种情况
		cout<<-1<<endl;
		return 0;
	}
	if(x>y) {//第三种情况
		cout<<-1<<endl;
		return 0;
	}
	cout<<y<<endl;
	return 0;
}

```

---

## 作者：_s_z_y_ (赞：0)

## 思路
根据题意，你每次可以走到 $(a+1,b+2)$ 或 $(a-1,b+2)$ 的位置，所以 $y\geq0$ 且 $y$ 不为奇数。又因为 $a$ 一直在 $+1$ 或 $-1$，$b$ 一直在 $+2$ 所以 $\dfrac{y}{2}\geq|x|$ 且  $\dfrac{y}{2}$ 的奇偶性与 $|x|$ 的奇偶性一定是一样的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
int main()
{
	cin>>x>>y;
	if(y<0||y%2==1||y/2<abs(x)||(y/2)%2!=abs(x)%2)
		cout<<-1;
	else
		cout<<y/2;
}
```

---

## 作者：shenbairui (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_tkppc4_2_a)


## 题目描述

你现在处于 $(0,0)$ 位置，你每次可以走到 $(a+1,b+2)$ 或 $(a-1,b+2)$ 的位置，其中 $a$ 和 $b$ 为你当前的坐标，问你最少走多少步到 $(x,y)$ 的位置。如果无法走到，输出 $-1$。

## 题目分析

我们可以筛出四种不可能

$1.$ $y<0$ 时一定不合法。

$2.$ $y$ 为奇数时一定不合法。

$3.$ $x>\dfrac{1}{2}y$ 时一定不合法。

$4.$ $x$ 与 $\dfrac{1}{2}y$ 奇偶性不同时一定不合法。

如果条件均合法，输出 $\dfrac{1}{2}y$。
## 上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int x,y;
	cin>>x>>y;
	if(y<0 || y%2) cout<<"-1";
	else if(y<abs(x)*2) cout<<"-1";
	else if((y-abs(x)*2)%4) cout<<"-1";
	else cout<<y/2;
	return 0;
}
```


拜拜！下期见！

---

## 作者：Vct14 (赞：0)

### 题意翻译

你现在在一个坐标系的原点（也就是 $(0,0)$ 处）。

对于每一步，你需要先选择向左或向右走 $1$ 步，再向上走 $2$ 步。即假如你在 $(a,b)$，你就可以到达 $(a-1,b+2)$ 或 $(a+1,b+2)$ 的位置（如下图）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_tkppc4_2_a/c3b5225215411ad6fd5647f9473cbc184fa57e89.png)

问：给定 $x,y$，你能否到达 $(x,y)$ 的位置。

- 如果能，输出最少的步数；

- 如果不能，输出 $-1$。

### 思路

先来筛几种明显不可能的 $(x,y)$。

- 由于每一步都要向上 $2$ 步，所以如果 $y<0$ 或 $y$ 是一个奇数，则一定不可能。

```c++
if(y<0 || y%2) cout<<"-1";
```

- 假设一种极端情况：你一直朝左（或朝右）移动，则必须有 $b=\left|a\right|\times 2$。但是如果不全朝左（或朝右）移动，则 $b\ge\left|a\right|\times 2$。所以如果 $y<\left|x\right|\times 2$，则一定不可能。

```c++
else if(y<abs(x)*2) cout<<"-1";
```

那么筛到这里，必有 $y\ge\left|x\right|\times 2$ 且 $y$ 为偶数，即 $\dfrac{y}{2}\ge \left|x\right|$。

再来分析一下：

每走 $2$ 步，横向移动就有 $3$ 种情况：

1. $2$ 步均向左，$a\leftarrow a-2$；
2. $1$ 步向左，$1$ 步向右，$a$ 不变；
3. $2$ 步均向右，$a\leftarrow a+2$。

可以发现，如果走偶数步，则 $\left|a\right|$ 奇偶性不变；否则就会改变。

更进一步地，因为 $a$ 初始为 $0$，为偶数，所以：如果走偶数步，则 $\left|a\right|$ 为偶数；否则为奇数。

所以步数与 $\left|a\right|$ 奇偶性相同。

若当前点为 $(a,b)$，则一定走了 $\dfrac{b}{2}$ 步。因此 $\dfrac{b}{2}$ 与 $\left|a\right|$ 奇偶性相同。则有 $\dfrac{b}{2}-\left|a\right|$ 为偶数。则 $b-\left|a\right|\times 2$ 为 $4$ 的倍数。

所以，若 $y-\left|x\right|\times 2$ 不为 $4$ 的倍数，则也不可能。

```c++
else if((y-abs(x)*2)%4) cout<<"-1";
```

最后，便一定可以到达了，输出 $\dfrac{y}{2}$ 即可。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int x,y;
	cin>>x>>y;
	if(y<0 || y%2) cout<<"-1";
	else if(y<abs(x)*2) cout<<"-1";
	else if((y-abs(x)*2)%4) cout<<"-1";
	else cout<<y/2;
	return 0;
}
```

这里还有一点：

因为 $\left|x\right|\times 2\ge 0$ ，所以当 $y<0$ 时，肯定满足 $y<\left|x\right|\times 2$。所以 $y<0$ 的判断可以省略。

又因为 $y$ 为奇数时，$y-\left|x\right|\times 2$ 必为奇数，满足 $y-\left|x\right|\times 2$ 不为 $4$ 的倍数，所以 $y$ 是否为奇数的判断也可以省略。

综上，可以将代码优化为：

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int x,y;
	cin>>x>>y;
	if(y<abs(x)*2 || (y-abs(x)*2)%4) cout<<"-1";
	else cout<<y/2;
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

[传送门。](https://www.luogu.com.cn/problem/AT_tkppc4_2_a)

# 思路：

从题目中可以知道，$y$ 坐标是一直在 2 点 2 点的增加着，所以如果目标点的 $y$ 坐标比 0 小或者不是 2 的倍数，都是无法达到的。因为 $y$ 坐标无法倒退，所以如果能走到，步数一定是目标点 $y$ 坐标的一半。对应的步数如果小于 $x$ 坐标的绝对值，那么必然是没有办法抵达目的地的。可步数比 $x$ 坐标大就能走到吗？同样不见得。因为你不可能让 $x$ 坐标停留在某个数字上不动，会一直加一减一的上下浮动，需要 2 次才能够回位。所以在步数大于或等于 $x$ 坐标的同时，两者间的差必须得是 2 的倍数才能成功抵达目的地。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long x,y;
    cin>>x>>y;
    if(y<0||y%2!=0||(x-y/2)>0||abs(x-y/2)%2!=0) cout<<-1;
    else cout<<y/2;
    cout<<endl;
    return 0;
}
```

---

## 作者：Versed_sine (赞：0)

# [AT_tkppc4_2_a Jumping!!](https://www.luogu.com.cn/problem/AT_tkppc4_2_a)题解

### 分析

观察题目，可以发现有以下四种的点到不了：

> $y<0$ 的点（因为只能往上走）。
>
> $y$ 为奇数的点（因为每次 $y$ 增加 $2$）。
>
> $|x|>\frac{y}{2}$ 的点（因为最边上的点落在 $y=\pm2x$ 的两条直线上，$\frac{y}{|x|}>2$ 的点不符题意）。
>
> $|x|$ 与 $\frac{y}{2}$ 奇偶性不同的点（由找规律得出）。

除上述点外的点均符合要求，到达该点的步数即为 $\frac{y}{2}$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int x,y;

int main(){
	scanf("%d %d",&x,&y);
	if((y<0)||(y&1)||(abs(x)>y/2)||((abs(x)&1)!=(y/2&1))) printf("-1\n");
	else printf("%d",y/2);
	
	return 0;
}
```

---

## 作者：maomao233 (赞：0)

### 题意
你现在处于 $(0,0)$ 位置，你每次可以走到 $(a+1,b+2)$ 或 $(a-1,b+2)$ 的位置，其中 $a$ 和 $b$ 为你当前的坐标，问你最少走多少步到 $(x,y)$ 的位置。如果无法走到，输出 $-1$。
### 分析
- 因为不管是 $(a+1,b+2)$ 还是 $(a-1,b+2)$ ，$b$ 始终都要 $+2$ ，不可能为负数。所以 $y<0$ 的情况**一定不能到达**。
- 横向坐标每次增加 $1$ ，纵向坐标每次增加 $2$ ，因此要到达的 $y$ 坐标一定会大于等于 $\lvert x\rvert$ $\times$ $2$ ，否则**一定不能到达**。
- 当满足 $y\geq\lvert x\rvert\times$ $2$ 时，因为 $\dfrac{1}{2}y-\lvert x\rvert$ 一定是 $2$ 的倍数，所以 $y-\lvert x\rvert\times$ $2$ 必须是 $4$ 的倍数，否则不是 $4$ 的倍数的情况**一定不能到达**。
- 如果满足了以上 $3$ 点，那么**其他情况一定都是可行的**，最后输出 $y\div2$ 即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x,y,t;
	cin>>x>>y;
	if(y<0)//y坐标是负数，不满足条件1 
	{
		cout<<-1<<endl;
		return 0;
	}
	t=abs(x);
	if(t*2>y||(y-t*2)%4!=0)//判断如果 y<|a|×2 或者 y-|a|×2不是4的倍数，则输出-1 
    {
        cout<<-1<<endl;
    }
	else//输出 y÷2 
    {
    	cout<<y/2<<endl;
    }
	return 0;
}
```


---

## 作者：S__X (赞：0)

又来水题解了！

## 题意：
你现在处于 $(0,0)$ 位置，你每次可以走到 $(a+1,b+2)$ 或 $(a-1,b+2)$ 的位置，其中 $a$ 和 $b$ 为你当前的坐标，问你最少走多少步到 $(x,y)$ 的位置。如果无法走到，输出 $-1$。

## 分析:
由于只能向上走，所以 $y\geq 0$。

每次 $x$ 移动一格，$y$ 移动两格，所以 $y\geq x\times 2$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	a=abs(a);
	if(a*2>b||(b-a*2)%4!=0) cout<<-1<<endl;
	else cout<<b/2<<endl;
	return 0;
}
```

---

## 作者：jsisonx (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_tkppc4_2_a)
# 题目思路
这道题，如果直接硬模拟，会费时费空间而且没必要。
正确的做法是找规律。

- 首先，如果 $y<0$，那么一定到不了，直接输出 $-1$。
- 然后，如果 $y$ 是奇数，那么由于 $y$ 每次增加 $2$，所以也到不了，输出 $-1$。
- 如果上面两条都不满足呢？我们设向左跳为 $-1$，向右跳为 $1$，那么如果 $|x|$ 与 $\frac{y}{2}$ 的奇偶性不同，那么一定无法通过 $\frac{y}{2}$ 个 $1$ 与 $-1$ 求和的方法得到 $x$，输出 $-1$。
- 如果 $|x|>\frac{y}{2}$，那么一定到不了，因为第 $i$ 行最多可以跳到第 $i$ 个位置。
- 如果以上所有情况均不满足，那么输出 $\frac{y}{2}$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;
    if(b<0||b%2==1){
        cout<<-1<<endl;
        return 0;
    }
    if((b/2)%2!=abs(a)%2){
        cout<<-1<<endl;
        return 0;
    }
    if(abs(a)>b/2){
        cout<<-1<<endl;
        return 0;
    }
    cout<<b/2<<endl;
    return 0;
}
```


---

