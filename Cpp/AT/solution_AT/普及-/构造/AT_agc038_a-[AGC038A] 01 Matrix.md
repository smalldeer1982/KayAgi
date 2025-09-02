# [AGC038A] 01 Matrix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc038/tasks/agc038_a

$ H $ 行 $ W $ 列からなるマス目があります。 すぬけくんは、各マスに $ 0 $ または $ 1 $ を書き込みたいです。 その際、以下の条件を全て満たす必要があります。

- どの行についても、その行に含まれる $ 0 $ の個数と、その行に含まれる $ 1 $ の個数のうち、小さい方が $ A $ である。 （ここで、$ 0,1 $ の個数が同じ場合、小さい方はどちらとしてもよい）。
- どの列についても、その列に含まれる $ 0 $ の個数と、その列に含まれる $ 1 $ の個数のうち、小さい方が $ B $ である。

これらの条件を満たすように各マスに $ 0,1 $ を書き込めるか判定し、 可能な場合は条件を満たす書き込み方を $ 1 $ つ示してください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 1000 $
- $ 0\ \leq\ A $
- $ 2\ \times\ A\ \leq\ W $
- $ 0\ \leq\ B $
- $ 2\ \times\ B\ \leq\ H $
- 入力される値はすべて整数である。

### Sample Explanation 1

どの行についても、その行に含まれる $ 0,1 $ の個数はそれぞれ $ 2,1 $ であり、条件を満たしています。 また、どの列についても、その列に含まれる $ 0,1 $ の個数はそれぞれ $ 2,1 $ であり、条件を満たしています。

## 样例 #1

### 输入

```
3 3 1 1```

### 输出

```
100
010
001```

## 样例 #2

### 输入

```
1 5 2 0```

### 输出

```
01010```

# 题解

## 作者：雨伞CKY (赞：5)

# 题意简述
- 给定 $4$ 个整数 $H,W,A,B$。
- 你需要构造一个由 $0$ 和 $1$ 构成的、$H$ 行 $W$ 列的矩阵，使得其满足：
    1. 每行 $0$ 的个数和 $1$ 的个数中，较小的值为 $A$。
    2. 每列 $0$ 的个数和 $1$ 的个数中，较小的值为 $B$。
- $1\leq H,W\leq 10^{3},0\leq A\leq \frac{W}{2},0\leq B\leq \frac{H}{2}$。

# 题目分析
不难发现，只要在每行中放入 $A$ 个 $0$、$(W-A)$ 个 $1$ 即可满足条件 $1$。例如，当 $H=4,W=3,A=1$ 时，可以构造以下矩阵。

$$
\begin{matrix}
   0 & 1 & 1\\
   0 & 1 & 1\\
   0 & 1 & 1\\
   0 & 1 & 1
\end{matrix}
$$

但是，这个矩阵仅在 $B=0$ 时满足条件 $2$。我们需要进一步修改矩阵。例如，在上方条件下，如果 $B=2$，可将矩阵修 $3,4$ 行的 $0$ 改为 $1$，$1$ 改为 $0$。最终结果如下。

$$
\begin{matrix}
   0 & 1 & 1\\
   0 & 1 & 1\\
   1 & 0 & 0\\
   1 & 0 & 0
\end{matrix}
$$


所以，根据推理过程可得：**满足题意的矩阵的前 $B$ 行中，前 $A$ 列的数为 $0$，其余的数为 $1$；其余行中，前 $A$ 列的数为 $1$，其余的数为 $0$**。在数据规模的限制下，我们**始终可以构造满足题目条件的矩阵**。

![](https://cdn.luogu.com.cn/upload/image_hosting/bbtczspo.png)

# 代码
```cpp
#include <iostream>
using namespace std;

int H,W,A,B;

int main(){
    cin >> H >> W >> A >> B;
    for (int i = 1;i <= H;i++){
        for (int j = 1;j <= W;j++){
            if ((i <= B && j <= A) || (i > B && j > A)) cout << 0;
            else cout << 1;
        }
        cout << endl;
    }
    return 0;
}
```

[AC 记录：Submission #24954479 - AtCoder](https://atcoder.jp/contests/agc038/submissions/24954479)

---

## 作者：FreedomKing (赞：2)

# 简单构造
[注：blog 食用更佳](https://www.luogu.com.cn/blog/zhugeminhao/SP3394)

------------
### 题目大意
给定 $h,w,a,b$，要你构造一个 $h$ 行 $w$ 列的01矩阵使得：

- 对于每一行，$\min${$0的个数,1,1的个数$}$=a$
- 对于每一列，$\min${$0的个数,1,1的个数$}$=b$

无解输出 $-1$；如果有多解，任意输出一组即可。
### 思路
在前 $b$ 行中的前 $a$ 列填 $1$，后面填 $0$。

在后 $h-b$ 行中的前 $a$ 列填 $0$，后面填 $1$。

那么思路清晰，开干！

------------
[AT5198 [AGC038A] 01 Matrix](https://www.luogu.com.cn/problem/AT5198)
### AC Code:
```cpp
#include<bits/stdc++.h>//不用万能头也可以，但个人觉得万能头方便
using namespace std;//可以不加（雾
int h,w,a,b;
int main(){
	scanf("%d%d%d%d",&h,&w,&a,&b);//输入h,w,a,b
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if((i<=b&&j<=a)||(i>b&&j>a)) putchar('0');//判断是否输出0
			else putchar('1');//反之输出1
		}
		putchar('\n');//换行
	}
	return 0;//好习惯
}
```

~~蒟蒻的第 6 篇题解，但还是求过 QwQ~~

---

## 作者：Trump__Biden (赞：0)

### [传送门](https://www.luogu.com.cn/problem/AT5198)

## 思路：

根据题意，考虑将整个矩形分为四个部分，去构造这个矩形。

在前 $ b $ 行的前 $ a $ 列中填 $ 0 $，后几列填 $ 1 $。

后几行中的前 $ a $ 列中填 $ 1 $，后几列中填 $ 0 $。

说白了上边的两个是相反的，于是蒟蒻便根据上面的思路写出如下代码。

## 代码：
```
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int h,w,a,b,s[1005][1005];
int main() {
	scanf("%d%d%d%d",&h,&w,&a,&b);
	for(int i = 1; i <= h; ++ i) {
		for(int j = 1; j <= w; ++ j) {
			if((i <= b && j <= a)||(i > b && j > a)) {
				printf("0");
			}
			else {
				printf("1");
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：ztntonny (赞：0)

## 题意
给定 $h,w,a,b$，请你构造 $h$ 行 $w$ 列的 $01$ 矩阵使得：
- 对于每一行，$\min\{0$的个数$,1$的个数$\}=a$
- 对于每一列，$\min\{0$的个数$,1$的个数$\}=b$
无解请输出 $-1$；如果有多解，任意输出一组即可。
## 思路
为了方便，构造的时候肯定让同样的字符挨着，所以不难想象会形成一个如下图的方阵：![](https://cdn.luogu.com.cn/upload/image_hosting/ox8mmd8n.png)
为了构造的如题意，长度分别是这样的：![](https://cdn.luogu.com.cn/upload/image_hosting/20i5cfp4.png)
这样在前 $b$ 行中，保证有 $a$ 个 $1$，在后 $m-b$ 行中有 $a$ 个$0$；在前 $a$ 列中有 $b$ 个 $1$，在后 $n-a$ 列中有 $b$ 个 $0$。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	long long a , b , m , n;
	cin >> m >> n >> a >> b;
	for ( int mi = 0; mi < b; mi++ )//前b行
	{
		for ( int ai = 0; ai < a; ai++ )//1部分
			cout << 1;
		for ( int ai = a; ai < n; ai++ )//0部分
			cout << 0;
		cout << endl;
	}
	for ( int ni = b; ni < m; ni++ )//后m-b行
	{
		for ( int ai = 0; ai < a; ai++ )//1部分
			cout << 0;
		for ( int ai = a; ai < n; ai++ )//0部分
			cout << 1;
		cout << endl;
	}
	return 0;
}
```


---

## 作者：EthanOI (赞：0)

## 前言
非常有意思的题目。

[题目传送门](https://www.luogu.com.cn/problem/AT5198)与[不一定更好的阅读体验](https://www.luogu.com.cn/blogAdmin/article/edit/446603)
## 做法
第一眼看到这道题时，可能会被吓到，至少形式是非常吓人的。但事实上，我们只需要找到一种满足条件的构造，输出即可，现在的问题在于如何找到这个构造
## 构造
由于是自己构造，当然是考虑最简单的情况，方便起见，设每一行都有 $a$ 个 $0$，$w-a$ 个 $1$。下面就是一种这样的构造（满足条件 $1$）：

| $0$ | $1$ | $1$ | $1$ |
| -----------: | -----------: | -----------: | -----------: |
| $0$ | $1$ | $1$ | $1$ |
| $0$ | $1$ | $1$ | $1$ |
| $0$ | $1$ | $1$ | $1$ |

（注：此时 $h=w=4$，$a=1$）、

这样行的约束条件就没有了（全部满足了）。因此，只需要考虑在此情况下列如何构造。

同样的，为了尽可能将构造简化，假设每一列刚好是前 $b$ 个相同，后 $h-b$ 个相同。经过一小会儿的思考，就能得到非常简单的一种构造了。设 $i$ 行 $j$ 列的数为 $a[i][j]$，取 
$a[i][j]=\begin{cases}0&i\leqslant a,j\leqslant b  \\0 &i>a,j>b\\1&\text{其他情况}\end{cases}$

是不是非常巧妙？其实自己操作下来并没有那么困难。

后面代码就简单了
## [$\mathcal{AC\text{ }CODE}$](https://www.luogu.com.cn/record/77909352)
```cpp
#include <bits/stdc++.h>
using namespace std;
int h, w, a, b;
int main()
{
    cin >> h >> w >> a >> b;
    for (int i = 1; i <= h; i++)
	{
        for (int j = 1; j <= w; j++)
            if ((i <= b && j <= a) || (i > b && j > a)) cout << 0;
            else cout << 1;
        cout << endl;
    }
    return 0;
}
```
珍惜生命，远离抄袭

---

## 作者：yinhy09 (赞：0)

## 解题思路：
此题只是找一个可行解，所以思路就是**化简并找规律**。

所谓化简并找规律就是将所有可行解概括为一种特殊的规律，就是寻找一个通用寻找符合条件的解的方法，楼上的题解（ By 雨伞CKY）已经说了解法，所以我这里重点说一下我是如何想的（思路非常重要，尤其是这种找一组可行解的方法，是一种组合构造思路）。

## 思路分析：

首先我们先随机找一个方阵，并将其转化，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/x8sdqc33.png)

所以经过转化，规律可以概括为：

![](https://cdn.luogu.com.cn/upload/image_hosting/dxtge1hy.png)

所以只需要用一个数组 `a` 来存下图像（①或②均可），本人采用了②。所以 `for` 循环遍历每一个格子 $a_{i,j}$ 的下标在那个区域中，然后标成对应的数。(先 `memset(a,0,sizeof(a))` 将数组复位为零，然后将需要为1的存成1，最后输出数组 `a` 即可)。

既然已经有了思路，就赶快上代码~

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int h,w,a,b;
	cin>>h>>w>>a>>b;
	const int maxn=1000+5;//实现确定好数据范围
	bool q[maxn][maxn];
	memset(q,0,sizeof(q));//先数组清零
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			if(j<=a&&i>b) q[i][j]=1;//右上角置1
			else if(j>a&&i<=b) q[i][j]=1;//左下角置1
		}
	}
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++) cout<<q[i][j];
		cout<<endl;
	}
	return 0;
}
```

谢谢大家的观看~

---

## 作者：hyc1026 (赞：0)

本题化简题意总是可构造如下方阵：

在前 $b$ 行中的前 $a$ 列填 $0$，后面填 $1$。

在后 $h-b$ 行中的前 $a$ 列填 $1$，后面填 $0$。

这样总满足要求。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int Q[5001][5001];

int main()
{
    int h,w,a,b;
    cin >> h >> w >> a >> b; 
    for(int i=1; i<=h; i++)
    {
        for(int j=1; j<=w; j++) Q[i][j] = (i<=b&&j<=a) || (i>b&&j>a); //判断所在位置应该填什么
    }
    for(int i=1; i<=h; i++)
    {
        for(int j=1; j<=w; j++) cout << Q[i][j];
        cout << endl;
    }
    return 0;
}
```

---

## 作者：fanfansann (赞：0)

简单构造。
我们直接把矩阵依据 $j= a$ 和 $i= b$ 这两条线横竖切开两刀，分成四份，这样左上角全填 $1$ 和右下角全填 $1$，剩下的全填 $0$ ，因为要求最小值为$a/b$，那么这种方法就**一定可以构造成功**，因为另一半要么大于 $a$ ，答案就是最小值 $a$ ，要么小于 $a$ ，答案会更小，同样满足要求。
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>

using namespace std;
const int N = 5007;
int n, m, a, b;
int ans[N][N];
int main()
{
    cin >> n >> m >> a >> b;

    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j)
            ans[i][j] = 0 + ((i <= b && j <= a) || (i > b && j > a));
    for(int i = 1; i <= n; ++ i)
    {
        for(int j = 1; j <= m; ++ j)
        printf("%d", ans[i][j]);
        puts("");
    }
    return 0;
}

```


---

## 作者：JustinXiaoJunyang (赞：0)

思路分析：

给定 $h,w,a,b$，请你构造 $h$ 行 $w$ 列的 `01` 矩阵使得：

- 对于每一行，$\min\{0$ 的个数 $,1$ 的个数$\}=a$
- 对于每一列，$\min\{0$ 的个数 $,1$ 的个数$\}=b$

无解请输出 $-1$；如果有多解，任意输出一组即可。

本题总是可构造如下方阵：

前 $b$ 行中的前 $a$ 列填 $0$，后面填 $1$。

在后 $h-b$ 行中的前 $a$ 列填 $1$，后面填 $0$。

这种方案总是成立，所以不用考虑 $-1$。

想练习更多构造题，可以去看看 [CF1436B](https://www.luogu.com.cn/problem/CF1436B)。

参考代码：

```cpp
#include <iostream>
using namespace std;

int f[5005][5005];

int main()
{
    int h, w, a, b;
    cin >> h >> w >> a >> b; 
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++)
    {
        if (j <= a && i > b) f[i][j] = 1;
		else if(j > a && i <= b) f[i][j] = 1;
    }
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++) cout << f[i][j];
        cout << endl;
    }
    return 0;
}
```

---

## 作者：力巴尔 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT5198)

### 思路：

在前 $b$ 行的前 $a$ 列输出 $1$，后面输出 $0$。

在后 $(h - b)$ 行相反，前 $a$ 列输出 $0$，后面输出 $1$。

这样就能满足题意。

拿样例举例：

输入：3 3 1 1

根据上述思路，输出：
```
1 0 0
0 1 1
0 1 1
```

即可满足题意。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int h, w, a, b;
    cin>>h>>w>>a>>b;
    for (int i = 1;i <= h;i++)
    {
        for (int j = 1;j <= w;j++)
        {
            if (i <= b)
                if (j <= a)
                    cout<<1;
                else
                    cout<<0;
            else
                if (j <= a)
                    cout<<0;
                else
                    cout<<1;
        }
        puts("");
    }
}
```


---

