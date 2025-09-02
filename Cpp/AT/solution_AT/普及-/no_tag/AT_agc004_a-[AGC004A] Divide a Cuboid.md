# [AGC004A] Divide a Cuboid

## 题目描述

用若干个 $ 1 \times 1 \times 1 $ 的小方块（立方体）组成一个 $ A \times B \times C $ 的大长方体，每个小方块可以涂成红色或蓝色，但要满足以下要求：

① 至少有 $1$ 个红色方块与 $1$ 个蓝色方块。

② 所有的红色方块必须组成一个长方体。

③ 所有的蓝色方块必须组成一个长方体。

求所有满足要求的染色方案中，红色方块数与蓝色方块数相差个数的最小值。

## 说明/提示

$ 2 ≤ A, B, C ≤ 10^9 $

感谢@刷题永动机 提供的翻译

## 样例 #1

### 输入

```
3 3 3```

### 输出

```
9```

## 样例 #2

### 输入

```
2 2 4```

### 输出

```
0```

## 样例 #3

### 输入

```
5 3 5```

### 输出

```
15```

# 题解

## 作者：CZQ_King (赞：1)

这道题简化之后就是：

```
在一个立方体切一刀，使切出的两部分的体积的差最小。
```

那么分类讨论：

- 当有一条边是偶数的时候，直接从那条边的正中间切过去，那么差就为$0$。

- 当每条边都是奇数时，因为我们不能从正中间切过，但我们要接近于正中间，所以要在$\lfloor\frac a2\rfloor$或$\lceil\frac a2\rceil$处切一刀,此时差的面积为$1\times a\times b$，为了让体积最小，所以我们选取最短的两条边相乘得到体积。

![](https://s2.ax1x.com/2019/08/10/eL8gE9.png)

**注意！因为边长最长会有$10^9$，相乘会达到$10^{18}$，所以要开$long\ long$**

------------
代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a[3];//一定要开long long
int main(){
    cin>>a[0]>>a[1]>>a[2];
    sort(a,a+3);//排序获得最小的两边长
    cout<<((a[0]&1&a[1]&1&a[2]&1)?a[0]*a[1]:0)<<endl;//分类讨论
}
```

---

## 作者：Vocanda (赞：0)

# 题目
[题目链接](https://www.luogu.com.cn/problem/AT2041)

# 分析
题目的意思是让把一个长方体分成两部分，要求每一部分都是长方体，所以容易得到，只有当两部分是由一个长方体劈开时，才满足要求。

所以我们把题目简化成了如下：\
把一个大长方体分成两个小长方体使得两部分的体积之差最小。

要想使体积之差最小，那么肯定是劈的越靠中间，越平均越好。

所以只要有一条边是偶数长度，那么这个大长方体就可以被平均分开，输出 $0$ 即可。

如果没有一条边的长度是偶数，我们在分的时候肯定有一个长方体比另一个多一层，那么我们之需要找最小的这一层的面积就行了，所以答案就是三条边长两两相乘中取最小值。

注意要开 $long\ long$
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int a,b,c;scanf("%lld%lld%lld",&a,&b,&c);
	if(!(a & 1) || !(b & 1) || !(c & 1))return puts("0"),0;
	else{
		printf("%lld\n",min(min(a*b,b*c),a*c));
	}
	return 0;
}

```

---

## 作者：Snow_Dreams (赞：0)

这道题就是去求一个立方体切一刀后两体积差最小的值

1. 如果所有边中有偶数边：直接输出0，并终结程序

2. 如果所有边只有奇数边，则必定差最小是一个面的面积，求的方式就是去取 ab, bc, ac 的最小值，然后输出最小值

即可

然后注意一下那个long long的问题

因为10^9^2爆int了，所有要开long long

建议：直接宏替换

```cpp
#define int long long
```
注意要将main函数设成signed

---

## 作者：Victorique (赞：0)

水题。
我们可以YY出，如果长宽高有一个是偶数，那没差，绝对是0。如果倒霉催的全是奇数，那么一定会差一个面的大小，那么输出面积最小的一面。
```cpp
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#define re register
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define ms(arr) memset(arr, 0, sizeof(arr))
const int inf = 0x3f3f3f3f;
ll a,b,c;
int main() 
{
	cin>>a>>b>>c;
	if(a%2==0||b%2==0||c%2==0) {
		cout<<0;
		return 0;
	}
	cout<<min(min(a*b,a*c),b*c);
    return 0;
}
```

---

