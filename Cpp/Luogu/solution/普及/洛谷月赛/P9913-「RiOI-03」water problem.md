# 「RiOI-03」water problem

## 题目描述

给定一个正整数 $n$，问一个正方形能否被分割为 $n$ 个小正方形（**不要求大小相等**），输出 `Yes` 或 `No`。多组数据。

分割的不严格定义可以理解为切一刀。但是切出的这一刀必须是线段，且其端点必须在正方形的边界上或先前切出的线段上。

## 说明/提示

### 样例解释 1

显然，正方形无法分割为 $3$ 个小正方形；\
由于 $4 = 2^2$，$256 = 16^2$，则它们均能被分割成若干个全等的小正方形。

### 数据规模与约定

+ Subtask 0（10 pts）：$n$ 是偶数。
+ Subtask 1（35 pts）：$n \leq 8$。
+ Subtask 2（55 pts）：无特殊限制。

对于所有数据，$1 \leq T \leq 10^5$，$1 \leq n \leq 10^9$。

## 样例 #1

### 输入

```
3
4
3
256```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：小粉兔 (赞：105)

倒着阅读本题解，即可知道在 2023 激励计划中我给这题评分 10 的原因。

---

**注意到**

![](https://cdn.luogu.com.cn/upload/image_hosting/6c3yk0e0.png)  
（此图片来自[《怎样把一个立方体分成 54 个小立方体？》](http://www.matrix67.com/blog/archives/6513)，作者为顾森（Matrix67），此图片以 CC BY-NC-SA 协议进行许可）

由于通过将 $1$ 个小正方形分割为更小的 $4$ 个小正方形可以**增加 $\bm 3$ 个小正方形数量**，更大的 $n$ 均可被满足，例如：

- $n = 9$ 可由 $n = 6$ 的方案分割得到。
- $n = 10$ 可由 $n = 7$ 的方案分割得到。
- $n = 11$ 可由 $n = 8$ 的方案分割得到。
- ……

所以除了 $n \in \{ 2, 3, 5 \}$ 以外的 $n$ 均有方案。

通过**瞪眼法**不难发现 $n \in \{ 2, 3, 5 \}$ 时没有方案。

参考代码（Python）：

```python3
#这回只花了45min就打完了。
#真好。记得多手造几组。最好有暴力对拍。 
coach = 'water235'
for _ in range(int(input())):
  print('No' if input() in [*coach] else 'Yes')
```

参考代码（Python）：

题目背景中的小 H 昨天生日吗？也太巧了吧！今天是 CPhO 2019 报道日，昨天也是[我的生日](https://www.zhihu.com/question/353626585/answer/880220243)，祝我和小 H 昨天生日快乐！

比赛结束后听说这题是原题……？哎，water's problem，原来是教练出的题，[怪不得嘛](https://www.zhihu.com/question/531201223/answer/2468824563)。

不过，这样就直接 AC 了也太快了，所以最好要等个 [45 分钟](https://www.zhihu.com/question/527361777/answer/2472274087)左右再提交。

再联想教练的网名，正解呼之欲出：当 $n$ 被教练的网名中的数码包含时无解，否则有解。

通过样例可知，$n = 4$ 时答案是 `Yes` 而 $n = 3$ 时答案是 `No`。

注意到题目名：**water problem**。由于你的教练的网名就叫 **water**_235_，这一定是某种暗示。

泉州七中学生快速 AC 方法。

---

## 作者：cff_0102 (赞：19)

假设一个正方形能被分成 $n$ 份，则在这个正方形外面拼上 $3$ 个大小相同的正方形，得到一个大正方形，这个大正方形中一共有 $n+3$ 个小正方形，故一个正方形也能被分成 $n+3$ 份。

![](https://cdn.luogu.com.cn/upload/image_hosting/nup5axjz.png)

而我们知道一个正方形可以被分成 $1,4,6,7,8$ 份。

![](https://cdn.luogu.com.cn/upload/image_hosting/3lkmidsm.png)

所以一个正方形也能被分成 $6+3=9$ 份，$7+3=10$ 份，$8+3=11$ 份，$9+3=12$ 份，以此类推。所以只要 $n\ge6$，一个正方形就必然能被分成 $n$ 块。

因此，只要 $n\ge6$，直接输出 `Yes`，如果 $n=1$ 或 $4$，也输出 `Yes`，否则输出 `No`。别忘了输出要换行。

C++ 赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		if(n>=6)cout<<"Yes\n";
		else if(n==1||n==4)cout<<"Yes\n";
		else cout<<"No\n";
	} 
	return 0;
}
```

---

## 作者：FFTotoro (赞：12)

## 前言

[~~这是我 $12$ 月 $9$ 日 $14$ 点多一点在官网洛谷提交的记录，时间是 $12$ 月 $9$ 日下午，这个时间我根本没确定题目只需特判 $2,3,5$。~~](https://www.luogu.com.cn/problem/solution/P8423)

## 解法

显然对于 $n=2,3,5$ 无解；考虑其他情况如何构造。

$n=1,6,8$ 是容易构造的。具体地，$n=1$ 不需要任何操作，$n=6$ 只需将一个 $3\times 3$ 的网格的其中 $4$ 个小正方形合并成一个大正方形即可构造，$n=8$ 类似 $n=6$ 的情况，只需把 $3\times 3$ 的网格改为 $4\times 4$ 的网格，将 $9$ 个小正方形合并成一个大正方形即可。

就是构造如下的图形（盗一下 OEIS 上面的图）：

```
n = 6
+---+---+---+
|...|...|...|
+---+---+---+
|.......|...|
|.......+---+
|.......|...|
+-------+---+
n = 8
+---+---+---+---+
|...|...|...|...|
+---+---+---+---+
|...........|...|
|...........+---+
|...........|...|
|...........+---+
|...........|...|
|-----------+---+
```

又因为在构造出的图形的任意一个小正方形上将其分为 $4$ 个更小的正方形可以将总的个数增加 $3$。故对于所有 $n\not\in\{2,3,5\}$ 都是合法的。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n; cin>>n;
    cout<<(n==2||n==3||n==5?"No\n":"Yes\n");
  }
  return 0;
}
```

---

## 作者：FurippuWRY (赞：9)

我们可以从 $n=1$ 开始枚举，找规律。

| $n=$ | 分割情况 |
| :----------: | :----------: |
| $1$ | 不用分割。 |
| $2$ | 很明显，没法分割。 |
| $3$ | 无法分割。 |
| $4$ | 可以四等分。 |
| $5$ | 无法分割。 |
| $6$ | ![](https://cdn.luogu.com.cn/upload/image_hosting/9k0v9d5c.png) |
| $7$ | 四等分 $n=4$ 的任意一个小正方形。 |
| $8$ | 类似于 $n=6$，不算右下角的小正方形，底部和侧面分别各有三个小正方形。 |
| $9$ | 四等分 $n=6$ 的任意一个小正方形。 |
| $10$ | 四等分 $n=7$ 的任意一个小正方形。 |
| $11$ | 四等分 $n=8$ 的任意一个小正方形。 |
| $12$ | 四等分 $n=9$ 的任意一个小正方形。 |
| $13$ | 四等分 $n=10$ 的任意一个小正方形。 |
| $14$ | 四等分 $n=11$ 的任意一个小正方形。 |

由表可以推测，只要 $n \notin \{2,3,5\}$，那么就可以分割。

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, a;

int main() {

    cin >> n;
    while (n--) {
        cin >> a;
        if (a != 2 && a != 3 && a != 5) cout << "Yes" << '\n';
        else cout << "No" << '\n';
    }

    return 0;
}
```

---

## 作者：I_Am_Busy (赞：4)

这是一个比较经典的问题，结论大家都知道了，蒟蒻想从头分析一遍。

- 完全平方数

看到这个题目很多人就会直接想：将正方形分割成正方形，那数量不就是完全平方数吗？没错，所以完全平方数当然可以。

- 分割

但是递交上去之后很多人就爆零了，原因是正方形大小不一定相同，那我们就可以将一个正方形分成几个小正方形，或者将几个小正方形合并成一个。

我们可以首先将一个小正方形分割成 $4$ 个。照这样，$1$ 个小正方形就可以分割成 $4$ 个，$4$ 个小正方形中的一个再分割就可以分割成 $7$ 个……以此类推，所有满足 $n$ 为自然数的 $3n + 1$ 都满足题目要求。

我们继续向下尝试，然后就是 $9$ 个。照这样，$1$ 个小正方形就可以分割成 $9$ 个，$9$ 个小正方形中的一个再分割就可以分割成 $17$ 个……以此类推，所有满足 $n$ 为自然数的 $8n + 1$ 都满足题目要求。

如果是 $16$ 个呢？照这样，$1$ 个小正方形就可以分割成 $16$ 个，$16$ 个小正方形中的一个再分割就可以分割成 $31$ 个……以此类推，所有满足 $n$ 为自然数的 $15n + 1$ 都满足题目要求，但很显然这些数构成的集合包含于 $3n + 1$，所以我们不单独列出来算。

再往后，$25$ 个，$36$ 个……我们会发现最后其实只有 $3n + 1$ 和 $8n + 1$ 两种数满足题目要求，于是分割这一块就结束了。

- 合并

上面已经提到了合并，我们现在就来尝试一下。

我们要合并，那么我们最好选择一个初始的方阵，不能太小，但也不要太大，比如我们可以从 $16$ 个小正方形开始合并。

我们可以首先将 $4$ 个小正方形合并成一个。照这样，$16$ 个小正方形就可以合并成 $13$ 个，$10$ 个，$7$ 个或 $4$ 个。

我们也可以选择 $9$ 个。照这样，$16$ 个小正方形就可以合并成 $8$ 个。

选择再多的小正方形合并与分割同理，没有必要列举。

- 基础图形

我们已经推算出来，$7$ 个，$8$ 个或 $9$ 个小正方形都是满足条件的，于是之后的正方形数量至少都可以通过分裂来得到（每次分裂加三个小正方形）。那么 $7$ 个以下的呢？

显而易见，$6$ 个小正方形可以是 $9$ 个小正方形进行一次合并得到，$4$ 个小正方形可以通过分裂得到，而 $1$ 个就更不用说了，而 $2$ 个，$3$ 个或 $5$ 个小正方形却无论如何得不出来。因为 $6$ 个小正方形不能再合并，$8$ 个小正方形也不能。

（最后我们发现，其实完全平方数完全可以不单拎出来，直接作为分裂的一种。）

所以最后只需要判断一下数字是不是 $2$，$3$，$5$ 以外的数即可。

---

## 作者：fxwqctb (赞：3)

# 一、思路

把正方形切成 $n$ 个小正方形，我们最先考虑的应该是平方数的情况 ，如果 $n$ 为平方数，那么就可以把它切成 $n$ 个一模一样的小正方形。

我们也可以考虑一下当 $n\le8$ 的情况，当 $n=1$ 或 $n=4$ 时，$n$ 为平方数，所以 $1$ 与 $4$ 是可以的。

最后发现，当 $n=6$、$n=7$ 和 $n=8$ 也是可以的。  

$n=6$：  
![](https://cdn.luogu.com.cn/upload/image_hosting/znbrfuyw.png)

$n=7$：  
![](https://cdn.luogu.com.cn/upload/image_hosting/gnzyw3zj.png)

此时你可以根据以上思路编好代码，就可以骗到 35 分。

我们可以发现，正确的概率会比错误的概率大，我们可以尝试一下当 $n>8$ 的情况都输出 `Yes`，交上去时发现对了。

其实，当我们证明 $6$、$7$、$8$ 都是可以的时候，如果我们把图形中的任意一块正方形切割成 $4$ 个更小的正方形，就等于增加了 $3$ 个小正方形。

那么 $9$ 块就可以变为 $6$ 块加 $3$ 块。  
那么 $10$ 块就可以变为 $7$ 块加 $3$ 块。  
那么 $11$ 块就可以变为 $8$ 块加 $3$ 块。  
以此类推。

推出结论：除了 $n=2$、$n=3$ 和 $n=5$ 以外，其余都为正确。

# 二、AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool pf(int n)//是否为平方数
{
	if(int(sqrt(n))*int(sqrt(n))==n)return 1;
	else return 0;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		if(n==2||n==3||n==5)cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```

---

## 作者：JimmyDong (赞：2)

## 思路
由于 $n,t$ 很大，考虑每次询问直接出结果。由于一个正方形可以被分为四个小正方形，所以只要 $k$ 是满足要求的，$k+3$ 必然满足要求。

当 $n=1$ 显然满足，所以只要 $n$ 满足 $n\equiv1\pmod{3}$ 必然满足要求。继续枚举，发现 $n=2,3,5$ 不可以。又因 $n=6,8$ 可以按照如下图方式满足条件，所以 $n(n\geq 6)$ 满足 $n\equiv0\pmod{3}$ 和 $n\equiv2\pmod{3}$ 都必然满足要求。

![ ](https://cdn.luogu.com.cn/upload/image_hosting/mohog8db.png)

综上，只有 $n=2,3,5$ 不满足要求。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        if(n!=2&&n!=3&&n!=5) cout<<"Yes\n";
        else cout<<"No\n";
    } 
    return 0;
}
```


---

## 作者：_zqh_ (赞：1)

本题题如其名，确实比较水。

# 思路简述

首先，我们先枚举出 $1,2,\dots,8$ 中可以拼成正方形的数，分别是：

$$
1,4,6,7,8
$$

接下来我们来证明一下所有 $6$ 以后的数字都可行。

下图是大正方形的一部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/a14hn3sm.png)

易知，我们可以将这个正方形分成四份：

![](https://cdn.luogu.com.cn/upload/image_hosting/xjqykbuu.png)

而相当于分割份数加了 $3$，

那么以 $6$ 为标准，可以衍生出：

$$
9,12,15,\dots
$$

也满足条件。

同理以 $7,8$ 为标准，可以衍生出剩下大于 $6$ 的数。

**得证**。

**思路部分完结**。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
ios::sync_with_stdio(0); \
cin.tie(0);              \
cout.tie(0)
// #pragma GCC optimize(2)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define il inline
#define p_q priority_queue 
#define u_m unordered_map 
using namespace std;

int T;
int n;
bool pd[100] = {0, 1, 0, 0, 1, 0, 1, 1, 1};

int main() {
	ios;
	cin >> T;
	while (T--) {
		cin >> n;
		if (n <= 8) {
			if (pd[n]) {
				cout << "Yes\n";
			} else cout << "No\n";
			continue;
		}
		if (n >= 4) {
			cout << "Yes\n";
		}
		else cout << "No\n";
	}
	return 0;
}
```

这个代码有点冗余，我们换一个：

```cpp
#include <bits/stdc++.h>
#define ios                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)
// #pragma GCC optimize(2)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
using namespace std;

int T;
int n;

int main() {
    ios;
    cin >> T;
    while (T--) {
        cin >> n;
        if (n >= 6) {
            cout << "Yes\n";
        } else if (n == 1 || n == 4) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
```

---

## 作者：Aveiro7 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9913)
## 题意：

给定一个正整数 $n$，问一个正方形能否被分割为 $n$ 个小正方形（**不要求大小相等**），输出 `Yes` 或 `No`。多组数据。

分割的不严格定义可以理解为切一刀。但是切出的这一刀必须是线段，且其端点必须在正方形的边界上或先前切出的线段上。

## 思路：

这道题是一个结论题，~~但绝对远没有黄题的难度~~，看完这篇题解，你会觉得它就是红题的难度。

先下结论：**当 $n=4$ 或 $n=1$（一定要判断 $n=1$ 的情况！）以及 $n$ 是大于等于 $6$ 的整数，就都符合题意**。

这题可以采用**数学归纳法**。显然一个正方形很容易等分为四个小正方形（所以当 $n=4$ 时成立），因此要将小正方形的数目增加三个时很容易做到的，所以我们计算时的跨度为 $3$。

当 $n=6,7,8$ 时，可按下图的所示方式进行分割。

![](https://cdn.luogu.com.cn/upload/image_hosting/zk0vc2qo.png)

假设对某个 $n=k\ge6$，已将正方形分为 $k$ 个小正方形，那么只要再将其中一个小正方形等分为 $4$ 个更小的正方形，即可得到 $n=k+3$ 个小正方形，所以命题对一切自然数 $n\ge6$ 都成立。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int main()
{
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		cin>>n;
		if(n==1 or n==4 or n>=6) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```



---

## 作者：coderJerry (赞：1)

### 题目大意
给出 $n$ ，判断能否把一个正方形分成 $n$ 个小正方形。
### 题目分析
小学奥数题。一种可行的方案是，我们可以把大正方形分成两部分，中间和边缘。中间我们可以将其分成 $k$ 个正方形（$k$ 是平方数），接着剩余的 “$L$” 字部分，只需要用大于 $1$ 的奇数个正方形填满即可。换句话说，只要 $n$ 可以表示为一个平方数加一个大于 $1$ 奇数的和，那么他就符合题意。

上面的表述有些抽象，下面举 $2$ 个具体的例子帮助大家理解。
- $n = 10$ 的时候：

![](https://cdn.luogu.com.cn/upload/image_hosting/e6wja8rh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
- $n = 11$ 的时候：

![](https://cdn.luogu.com.cn/upload/image_hosting/mgdslp4b.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

经过检验，我们发现只有 $n=2,3,5$ 的时候无法构造。
### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        if(n==2||n==3||n==5) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
    return 0;
}
```


---

## 作者：linjunye (赞：1)

[题目连接](https://www.luogu.com.cn/problem/P9913?contestId=147237)

此题题解可以参考此链接：[点这里](https://mp.weixin.qq.com/s?__biz=MzA4OTAwNDA3Mg==&mid=2650159576&idx=6&sn=05a00134783e213edc608bab91eb57f4&chksm=8823189fbf5491894408667f01bd8610cbcfd9b7931cef79c89e5e6c026fd974f578b037d26d&scene=27)

首先，我们可以针对是否能分割 $n$ 个正方形进行推导 （$n\le10$）

![](https://cdn.luogu.com.cn/upload/image_hosting/f3fvmy5i.png)

我们可以发现一件事情：
##### $n=7$ 时的分割图不就是 $n=4$ 时的分割图，然后把左上角的正方形一分为四吗！

可以看出，如果把其中一个正方形一分为四，那也就是增加了三个正方形，所以我们能推导出如下结论（ $a_i$ 代表能否分割成 $i$ 个正方形）：

$a_{x+3}=a_x$

根据一下结论，我们可以分割 $11$ 个正方形 （$a_{11}=a_{11-3}$），也可以分割 $12$ 个（$a_{12}=a_{12-3}$）……

所以，除了不能分割成 $2$，$3$，$5$ 个正方形，其余均可以分割成功。

附代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n;
int main(){
	cin>>q;
	while(q--){
		cin>>n;
		if(n==2||n==3||n==5)cout<<"No\n";
		else cout<<"Yes\n";
	}
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

规律题，但是我玩画图玩了一个小时。

题目不要求正方形大小相等，所以我们打开万能的画图软件进行绘制。

例如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ea2elgcb.png)

我们可以发现，按这种方法绘制，每次将边上的正方形个数增加 $1$，总共增加 $2$，说明一定可以分割成大于 $2$ 的**偶数**个正方形。$10pts$ 就轻松到手了，注意，不可能被分割成 $2$ 个正方形。

同理，每个正方形都能继续分成四个小正方形。也就是增加了 $3$ 个小正方形，小正方形可以继续分割。

也就是说，如果分割数能被拆成一个大于 $2$ 的偶数加 $k$ 个 $3$，就能分割成功。翻译成符号语言就是 $x=y+3k$。其中，$x$ 为分割数，$y$ 为一个大于 $2$ 的偶数，$k$ 为正整数。

然后枚举到底是哪个偶数就行了，易证这个偶数必然存在。

赛时写的代码，比较乱，凑合着看吧。

```
#include<bits/stdc++.h>
using namespace std;
int t,n;
bool check()
{
  for(int i=4;i<=n;i+=2) if((n-i)%3==0) return 1;
  //找到一个偶数使得k为整数
  return 0;
}
int main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
  	cin>>n;
  	if(n==2) cout<<"No\n";
  	else if(n==1) cout<<"Yes\n";//前两个特判
  	else if(n%2==0) cout<<"Yes\n";//偶数必然成立
  	else if(check()) cout<<"Yes\n";
  	else cout<<"No\n";
  }
  return 0;
}
```

---

## 作者：suyi1111 (赞：0)

**Update at 2024.10.17 20:27**  
将完整代码给出了，因为写个函数让人补充完整有点傻，且这题是结论题。

本人一看这题，心里就乐了。

刚好最近午休时闲的没事干推过这个东西。

首先，将大正方形分割为 $n$ 个大正方形可以理解为用 $n$ 个正方形拼出大正方形

其次，如果 $n$ 个正方形能拼出一个大正方形，那么 $n+3$ 个正方形一定能拼出一个大正方形。

证明如下：

如果 $n$ 个正方形拼出一个边长为 $m$ 的大正方形，那么我们在这个正方形的左、上、左上三个方向加上三个边长为 $m$ 的大正方形。则必定能拼出一个边长为 $2m$ 的更大的正方形。

接下来就是手模了

$1$ 个正方形能拼出大正方形（比 $1$ 大的 ${}\bmod3=1$ 的正方形都能拼出大正方形）  
$8$ 个正方形能拼出大正方形（比 $8$ 大的 ${}\bmod3=2$ 的正方形都能拼出大正方形）  
$6$ 个正方形能拼出大正方形（比 $6$ 大的 ${}\bmod3=0$ 的正方形都能拼出大正方形）  

所以只有 $2$ 个正方形，$3$ 个正方形和 $5$ 个正方形拼不出大正方形。

### Code：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,t;
    cin>>t;
    while(t--){
        cin>>a;
        cout<<(a!=2&&a!=3&&a!=5?"Yes":"No")<<endl;
    }
    return 0;
}
```

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9913)

很好的思维题，不过百度可以搜到（）

首先我们能一眼观察到一个结论，那就是：  
对于每个正方形，可以在里面画一个十字架，这样使得正方形数加 $3$。

然后我们进行分类讨论。  
我们设初始的大正方形边长被分为了 $x$ 个等分，且大正方形的两条边中的每条边上都摆有 $x$ 个正方形。  
于是我们得出当 $x$ 为定值时，正方形共有 $2x-1+1=2x(\text{个})$。  
其中第一个 $1$ 为两条边长共有的 $1$ 个小正方形，第二个 $1$ 为除了两条边以外剩余的一个大正方形。

当 $x=1$ 时：  

则可以从中选择 $k(k\in\mathbb{N})$ 个正方形画上十字架。  
得：所有满足 $2\times1-1+3k=1+3k=n(k\in\mathbb{N})$ 的 $n$ 均有解。  
注意这里要减一，因为只有一个正方形，小正方形与大正方形重复了。

当 $x=2$ 时：  
则可以从中选择 $k(k\in\mathbb{N})$ 个正方形画上十字架。  
得：所有满足 $2\times2+3k=4+3k=n(k\in\mathbb{N})$ 的 $n$ 均有解。

当 $x=3$ 时：  
则可以从中选择 $k(k\in\mathbb{N})$ 个正方形画上十字架。  
得：所有满足 $2\times3+3k=6+3k=n(k\in\mathbb{N})$ 的 $n$ 均有解。  

当 $x=4$ 时：  
则可以从中选择 $k(k\in\mathbb{N})$ 个正方形画上十字架。  
得：所有满足 $2\times4+3k=8+3k=n(k\in\mathbb{N})$ 的 $n$ 均有解。

从中可以看出，若 $n(n\ge1)\equiv1\pmod3$ 或 $n(n\ge6)\equiv0\pmod3$ 或 $n(n\ge8)\equiv2\pmod3$ 则一定有解。  
不难看出此时仅有 $2,3,5$ 未满足条件。
但是此时无需再进行分类讨论了，因为 $k\in\mathbb{N}$，所以我们得出结论：

当 $n=2,3,5$ 时，无解，否则有解。  
得代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
inline string its(int x){stringstream ss;string s;ss<<x;ss>>s;return s;}
inline int sti(string s){stringstream ss;int x;ss<<s;ss>>x;return x;}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
#define lb(x) x&-x
signed main()
{
	int t;
	rd(t);
	while(t--)
	{
		int n;
		rd(n);
		puts(n!=2&&n!=3&&n!=5?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

water problem 果然 water。

首先讲 $35$ 分做法。

手动画图后得到 $n=\{1,4,6,7,8\}$ 时能分割，否则不行。


------------

我们发现当一个正方形横竖各割一刀时正方形数量会 $+3$，再切又能 $+3$，所以发现，只要一个 $n$ 满足要求，所有和 $n\bmod 3$ 余数相同的数都可以满足要求。

而在 $35$ 分做法中 $n=\{6,7,8\}$ 时都行，而它们 $\bmod\ 3$ 分别等于 $0,1,2$ 刚好是 $\bmod\ 3$ 时出现的所有余数，故得出结论：$n\le 6$ 时总是可以。

而在 $n\le 6$ 的数中，只有 $n=\{2,3,5\}$ 时才不可以，故只有这三个数不行，否则可以。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int T,n;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n;
		if(n==2||n==3||n==5) puts("No");
		else puts("Yes");
	}
	return 0;
}
```


---

## 作者：CarlosLiu (赞：0)

## 题目大意
把一个正方形分为 $n$ 个小正方形是否可行？
## 解题思路
结论题。

参照一下后面的图。图中把正方形分为 $2n+1$ 个小正方形和一个大正方形。但大正方形还能继续分！所以，如果某数可行，此数加上至少为 $3$ 的奇数也可行。

按照这点，不难发现，除了 $2,3,5$ 都可以。

![](https://cdn.luogu.com.cn/upload/image_hosting/5cryzpwj.png)

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main() {
	cin>>t;
    for(int i=1;i<=t;i++) {
        cin>>n;
        if(n==2||n==3||n==5) cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
    return 0;
}
```

---

## 作者：SunsetVoice (赞：0)

被队爷的第一题吊打了，不知道自己在干什么。

观察发现 $n$ 为偶数且不为 $2$ 时：

可以通过构造一个边长为 $ \frac{n-2}{2}a$ 的正方形，然后用边长为 $a$ 的正方形补剩余部分来构造。很明显 $2-2=0$，不可能有边长为 $0$ 的正方形。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xz2d6sta.png)

然后推一个引理：

如果可以分为 $n$ 个正方形，则可以分为 $n+3$ 个正方形。

证明：

可以将任意一个正方形分成相等的 $4$ 格（显而易见），于是此时个数变为 $n-1+4$。

而 $n=4,6,8$ 的时候均可，而 $4\bmod 3=1$，$6\bmod 3=0$，$8\bmod 3=1$。这样就覆盖了所有 $6$ 以上的数字。

所以只有 $n=2,3,5$ 时没有方案。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T,n;
	cin>>T;
	while(T--){
		cin>>n;
        if(n==3 or n==5 or n==2)cout<<"No"<<endl; 
		else cout<<"Yes"<<endl;
	} 
	system ("pause");
}

```


---

## 作者：ys_kylin__ (赞：0)

其实很容易看出是一道数学题，但是，我用了一种奇怪的思路去解。

首先，不难发现，由于不一定正方形的大小要相等，可以对一个小正方形无限切割成四块，就是多出了三块。也就是说，只要找到一种方案，那这种方案加三，加六，加九等等都可以。

那问题就变成了：分别找到除以三余零到二的数，要求可行且最小，而比他们大且除以三同余的数都可行。

除以三余一的，自然是 $1$ 了。除以三余二的，是 $8$，整除三的是 $6$。而 $2,3,5$ 不行，根据之前的理论，其它的都可以。

得出结论：只有 $2,3,5$ 不行（挺意外的）。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int n;
		scanf("%d",&n);
		if(n==2 || n==3 || n==5)
			printf("No\n");
		else printf("Yes\n");
	}
	
	return 0;
} 
```
[记录](https://www.luogu.com.cn/record/139180442)

---

## 作者：TainityAnle (赞：0)

### 题意

问一个正方形能否被分成 $n$ 个小正方形。

### 思路

1. 我们发现，想把一个正方形分成小正方形，至少是 4 个。即如“田”字型。所以当 $n<4$ 时，显然不行，当然 $n=1$（即不分割）是可以的。

2. 当 $n\ge4$ 时，当 $n$ 为偶数时，完全可以按照留左上一个大正方形，右下半圈小正方形，如图。此时，如果最下面一排有 $k$ 个，则小正方形数是 $2k-1$，再加上大的，满足每个 $n\ge4$ 的偶数。

![](https://cdn.luogu.com.cn/upload/image_hosting/5n26sdx2.png)

3. 当 $n\ge4$ 时，当 $n$ 为奇数时，我们再偶数情况的基础上，将大正方形切成“田”字状。此时，如果最下面一排有 $k$ 个，则正方形总个数是 $2k+3$，因为 $2\le k$，所以 $n=5$ 不成立。

综上，当 $n=2$ 或 $n=3$ 或 $n=5$ 时，输出 `No`。否则输出 `Yes`。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T,x;
    cin>>T;
    while(T--){
        cin>>x;
        if(x==2||x==3||x==5) cout<<"No\n";
        else cout<<"Yes\n";
    }
    return 0;
}
```

---

## 作者：Jasonshan10 (赞：0)

## 题意

- 给定一个正整数 $n$，问一个正方形能否被分割为 $n$ 个小正方形（不要求大小相等）。

## 思路

- 分析：由正方形的分割图，我们发现**任何一个正方形**都可在原来的基础上**增加** $3k$ 个正方形，所以可以将自然数分为 $3$ 类，$3k$，$3k+1$，$3k+2$ 分别进行考虑能够做到。

- 当 $n=4$，$n=6$，$n=8$时分别有符合要求的解。

![](https://cdn.luogu.com.cn/upload/image_hosting/n3of9l41.png)


- 因为 $n=4$ 有解，所以任何 $4+3k(k\ge 0)$ 的都有解。

- 因为 $n=6$ 有解，所以任何 $6+3k(k\ge 0)$ 的都有解。

- 因为 $n=8$ 有解，所以任何 $8+3k(k\ge 0)$ 的都有解。

- 很明显，在 $n=1$ 的情况下也是有解的。

- 综上所述，只有当 $n=2$，$n=3$，$n=5$ 时，无解。

- 所以当 $n=2$，$n=3$，$n=5$ 时，输出 `NO`，否则输出 `YES`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int n;
        scanf("%d",&n);
        if (n==2||n==3||n==5){
            printf("No\n");
        }
        else{
            printf("Yes\n");
        }
    }
    return 0;
}
```

---

## 作者：wangzelin (赞：0)

# P9913 题解


## 题目解析

我们可以先找规律。

首先对于 $n=6$，$7$，$8$  可证一定可以分。

又因为任意一个正方形都可以平分为 $4$ 个同样大小的小正方形，

因此如果有 $n=k$ 的分法，就能得到 $n=k+3$ 时的一种分法，

所以可以得到 $n=9$，$10$，$11$  的分法，

进而可以知道对于所有 $n \ge 6$，都是可以分的。

接着考虑 $n \le 5$ 的情况，

$ n=1 $，$4$ 由上可得是肯定可以的，$n=2$，$3$ 证不可行也比较简单。

对于 $ n=5 $，~~比赛时我画了许多图都无法分~~，是不可行的。

由此我们得出当 $n=2$，$3$，$5$ 是不可以分，其他值皆可以分。

## 代码


~~代码应该就不用多说了~~。

```cpp
#include<bits/stdc++.h>
using namespace std;

int x;

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>x;
		if(x==2||x==3||x==5) cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```

~~这是我第一次提交题解，希望能通过审核~~。

---

