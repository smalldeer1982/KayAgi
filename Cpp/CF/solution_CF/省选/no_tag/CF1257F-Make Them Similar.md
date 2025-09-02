# Make Them Similar

## 题目描述

给定一个长度为 $n$ $(2\leq n\leq100)$ 的正整数数组 $a_i$ $(0\leq a_i \leq 2^{30}-1)$

求是否存在 $x$ $(0\leq x \leq 2^{30}-1)$ ，使得对于数组 $b_i$，其中 $b_i=a_i \text{ xor } x$，$b_i$ 中所有元素两两的 $\text{popcount}(b_i)$ 相同。

其中 $\text{ xor }$是按位异或，$\text{popcount}(x)$是 $x$ 的二进制表示中 $1$ 的个数

请输出任意满足条件的 $x$ ，若不存在输出 $-1$

## 样例 #1

### 输入

```
2
7 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
3 17 6 0
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3
1 2 3
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3
43 12 12
```

### 输出

```
1073709057
```

# 题解

## 作者：LittleMoMol (赞：7)

## 前言
本题解采用**折半搜索**算法完成，对于不打算用这种方法的同学，这篇题解可能会浪费你人生中宝贵的十几分钟。

[有益于锻炼专注力的阅读体验](https://www.cnblogs.com/LittleMoMol-kawayi/p/LuoGu_solution_CF1257F.html)

## 思路
此题似乎找不出什么好的性质，那么考虑暴力。

发现 $x,a$ 都在 $2^{30}$ 内，直接枚举必然无法承受，怎么办？折半！

我们把 $x,a_i$ 劈成两半，一半为前 $15$ 位，一半为后 $15$ 位，分别暴力计算。

令 $c_i$ 表示 $a_i \oplus x$ 得到的数的前 $15$ 位的 $1$ 的个数（前 $15$ 位，指：从高往低数前 $15$ 位）；

令 $d_i$ 表示 $a_i \oplus x$ 得到的数的后 $15$ 位的 $1$ 的个数（后 $15$ 位，指：从低往高数前 $15$ 位）。

那么 $c_i + d_i$ 就表示 $a_i \oplus x$ 得到的数在二进制表示下 $1$ 的个数，题目要求所有的 $c_i + d_i$ 必须相等，那么我们可以列出必须满足的式子：$c_i + d_i = c_{i-1} + d_{i-1},\ 2 \le i \le n$。

你会发现这个式子没有简单的判定方法，那考虑把式子换一种形式，既然要保证所有的 $c_i + d_i$ 相等，那么只要满足 $c_i + d_i = c_1 + d_1$ 就可以了。

貌似有一些思路，但是还没有复杂度较低的判定方法，那就再把式子换一种形式：$c_i - c_1 = d_1 - d_i$，这样就可做了。

## 实现

我们求 $c$ 数组的时候把每一个 $x$ 所对应的所有 $c_i - c_1$ 存下来。求 $d$ 数组的时候，把所有 $d_1 - d_i$ 存下来。

如果某一个 $x$，与其对应的 $c_i - c_1$ 和 $d_1 - d_1$ 每一项都相等，那么就满足条件了，输出即可。

## 插曲

如何快速地求一个数在二进制下的 $1$ 的个数？先上代码~

```cpp
int get_cnt(int val)
{
	int res = 0;
	while (val) val &= val - 1, res ++ ;
	return res;
}
```

我们举个例子来看一看

![](https://cdn.luogu.com.cn/upload/image_hosting/44arzcr3.png)

总的来说 $x-1$ 相当于是把 $x$ 在二进制表示下最靠后的 $1$ 以及这个 $1$ 后面的所有 $0$ 按位取反，得到的数再与上 $x$ 相当于把最靠后的 $1$ 消去了。

## Code

```cpp
#include <iostream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

const int N = 110;
const int Mo = (1 << 15) - 1;

int n;
int a[N];
map<vector<int>, int> mp;

int get_cnt(int val)
{
	int res = 0;
	while (val) val &= val - 1, res ++ ;
	return res;
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	for (int x = 0; x < (1 << 15); x ++ )
	{
		int c1 = get_cnt((a[1] >> 15) ^ x);
		vector<int> vec;
		for (int i = 2; i <= n; i ++ ) vec.push_back(get_cnt((a[i] >> 15) ^ x) - c1);
		mp[vec] = x;
	}
	for (int x = 0; x < (1 << 15); x ++ )
	{
		int d1 = get_cnt((a[1] & Mo) ^ x);
		vector<int> nw;
		for (int i = 2; i <= n; i ++ ) nw.push_back(d1 - get_cnt((a[i] & Mo) ^ x));
		if (mp.count(nw))
		{
			cout << (mp[nw] << 15) + x << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}

```

## 完结撒花

这是我折半搜索第一次学明白的题了，也是我第一道灰题！收~

---

## 作者：柳易辰 (赞：5)

## $\text{Start}$
看到异或，联想到了许多算法：$\text{Trie}$，线性基......

再看 $n$ 和 $a_i$ 的范围，这好像与别的处理异或的算法时间复杂度对不上啊。

但是题目的要求是构造一个满足条件的 $x$。构造？$0\leqslant x<2^{30}$？这不就是**折半搜索**（Meet in the Middle）最擅长的事情吗？

如果不会的话，可以先做一下这道模板 [P4799 [CEOI2015 Day2] 世界冰球锦标赛](https://www.luogu.com.cn/problem/P4799)。

（关于 $0\leqslant x<2^{30}$，题目中虽然没有说 $x$ 的范围，但是易证：当 $0\leqslant x<2^{30}$ 都没有答案时，一定无解。）  
&nbsp;
## $\text{Solution}$

做折半搜索的题，一定要对 $30,40$ 这些数字敏感，因为折半搜索的时间复杂度往往就是 $O(3^{15}\log_23^{15})$ 或者 $O(2^{20}\log_22^{20})$ 之类的。

题目中，我们发现需要构造的 $x$ 拆成二进制位后正好是 $30$ 位，所以由此出发进行思考。折半就是把 $30$ 折成 $15$ 和 $15$ 两半，即把 $x$ 拆成前 $15$ 位和后 $15$ 位分开构造，最后整理答案。

相似地，我们把 $a_1\sim a_n$ 也拆成二进制位，前 $15$ 位和后 $15$ 位分开构造。

$(a_1\bigoplus x)\sim (a_n\bigoplus x)$ 前十五位的 $\text{popcount}$ 分别为 $c_1\sim c_n$，后十五位的为 $d_1\sim d_n$。那么只要满足 $\forall 2\leqslant i\leqslant n,c_i+d_i=c_1+d_1$ 即可。

如果我们用 $\text {map}$ 记录对于每一种 $x$ 前十五位情况对应的 $c$ 数组，那么在枚举 $x$ 的后十五位时，需要大量时间判断这个 $x$ 是否是一个解。因为我们无法确定 $c_1+d_1$ 的取值，就算确定了 $d$ 数组，也很难找到对应的 $c$ 数组。

于是我们将上述式子转化成折半搜索更加通用的形式，$c_i-c_1=d_1-d_i$。这样的话一旦确定了 $c$ 和 $d$ 数组中的一个，另一个也随着确定。  
&nbsp;
## $\text{Process}$
1. 枚举前半段：$x:0\rightarrow 2^{15}-1$：
	1. 求出 $c_1(\text{popcount}(a_1>>15\bigoplus x))$。
    
   2. 循环求出 $c$ 数组（记录 $c_i-c_1$）。
   
   3. 用 `map<vector<int>, int>` 类型存储。其中 $\text{vector}$ 类型存的是 $c$ 数组，$\text{int}$ 类型存的是 $x$ 的前十五位。  

2. 枚举后半段：$x:0\rightarrow 2^{15}-1$：
	1. 求出 $d_1(\text{popcount}(a_1 \&(2^{15}-1)\bigoplus x))$。
    
   2. 循环求出 $d$ 数组（记录 $d_1-d_i$）。
   
   3. 查询 $\text {map}$ 中是否有以 $d$ 数组为键的键值对，若有，输出其值，结束程序。  

3. $x$ 无解，输出 `-1`。

&nbsp;
## $\text{Code}$
时间复杂度为 $O(2^{15}15n)$ 的[代码](https://www.luogu.com.cn/paste/tkh7s82m)。
  
注意点：
1. 位运算的运算优先级。
  
2. $c_i-c_1,d_1-d_i$ 两次枚举时，$c_1,d_1$ 一次是减数，一次是被减数。
  
3. 不要将 $c_1$ 或 $d_1$ 放入记录 $c$ 或 $d$ 的 $\text{vector}$ 中。

&nbsp;
## $\text{End}$
做完这道题，相信你对折半搜索的理解已经有一些深入了。~~于是你可以给我点一个赞！~~
  
一般的折半搜索对于前面部分或者后面一部分都是分两种情况讨论的。如本题中 $x$ 的每一位分 $0/1$ 讨论。这样的折半搜索时间复杂度往往是 $2^{\frac{n}{2}}$ 乘以一些常数。
  
但是也有一些例外：

[CF585D Lizard Era: Beginning](https://www.luogu.com.cn/problem/CF585D)
  
[USACO 12 OPEN Balanced Cow Subsets G](https://www.luogu.com.cn/problem/P3067)
  
这是两道独树一帜的折半搜索好题，送给大家！

---

## 作者：YLWang (赞：4)

一个简单的思路是预处理出每个 $a_i$ 的 popcount，之后枚举 $x$。显然过不去。 

考虑 $x$ 对于每一位的贡献是相对独立的，即 $x$ 每位的取值不会影响到其他位。再发现最后要求相等，满足拼合性，于是考虑折半搜索。

把前 $15$ 位的所有方案都记录出来丢进一个 $map$ 里头。后 $15$ 枚举的时候可以方便地找出有没有方案符合。

这玩意的实现挺有技巧的，放一份代码链接。https://www.luogu.com.cn/paste/vf9j2wud

但事实上你在发现每一维是独立的时候就可以想列一堆方程高斯消元。

实现也挺有技巧的，为了避免小数可以整点辗转消元或者分数类之类的玩意。这个代码非主流就不放了。


---

## 作者：orpg (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1257F)
### 思路分析
由于数据较大，所以直接搜索是不可行的。这个时候我们考虑折半搜索。我们把 $x$，$a$ 的二进制拆分为前 $15$ 位和后 $15$ 位。

设一个 $b_i$ 为 $x$ 前 $15$ 位和 $a_i$ 前 $15$ 位的异或值中 $1$ 的个数。

设一个 $c_i$ 为 $x$ 后 $15$ 位和 $a_i$ 后 $15$ 位的异或值中 $1$ 的个数。

我们发现只要 $b_1=c_1,b_2=c_2,···,b_i=c_i$ 时，这个 $x$ 就可行。对于式子 $b_1+c_1=b_i+c_i$ 而言，变一下式，就是 $b_i-b_1=c_1-c_i$。所以我们使用两个数组维护每一个 $b_i-b_1$ 和 $c_1-c_i$。最后判断即可。
### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n;
int a[maxn];
map<vector<int>, int> mp;
int count(int val){
    return __builtin_popcount(val);//此函数可以判断一个数转二进制中1的个数
}
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int x=0;x<(1<<15);x++){//前十五位
        int b1=count((a[1]>>15)^x);
        vector<int> vec;
        for(int i=2;i<=n;i++){
            int b2=count((a[i]>>15)^x);
            vec.push_back(b2-b1);
        }
        mp[vec]=x;
    }
    for(int x=0;x<(1<<15);x++){
        int c1=count((a[1]&((1<<15)-1))^x);
        vector<int> vis;
        for(int i=2;i<=n;i++){
            int c2=count((a[i]&((1<<15)-1))^x);
            vis.push_back(c1-c2);
        }
        if(mp.count(vis)){
            int ans=(mp[vis]<<15)+x;
            cout<<ans;
            goto End;
        }
    }
    cout<<-1;
    goto End;
    End:;
}
```

---

## 作者：brealid (赞：2)

所以，这篇题解是一个非常规做法。（然而拿到了 $\color{white}\colorbox{#52C41A}{AC}$）

让我们一起认识：模(%)拟(你)退火

## 1 模拟退火本尊

由于篇幅，~~及作者太懒~~等原因，本文不会介绍模拟退火的具体流程。  
所以放一篇作者觉得不错的文章 https://www.cnblogs.com/flashhu/p/8884132.html

## 2 估值函数设计

这道题不像别的题目，要求的是一个**最优化答案**，有明确的估值函数。   
这道题要求的是**一个可行解**。   
所以，不像别的题目可以直接开始敲**随机搜索**部分，这道题需要先设计**估值函数**

### 2.1 何为"估值函数"

这是我从 A* 算法中搬过来的一个概念，其作用在于判断一个解的优劣

### 2.2 设计“估值函数”

应该有更好的估值函数，但笔者很懒，就选用了 $S^2$ ——方差

这个不了解的自行右转百度

## 3 算法流程设计

由于我们这个“估值函数”的特殊性，所以当 $S^2=0$ 时，此时的 $x$ 就是一个可行解。

伪代码如下：

>    double best = $S^2(0)$, now;      
>    for (温度逐渐降低)         
> $\ \ \ \ \ \ $ 随机改变 x 的某一位   
> $\ \ \ \ \ \ $ if ($S^2 (x_{new}) < S (x)$) then 存解;  
> $\ \ \ \ \ \ $ else 以一个概率接受这个较次解  
>
>    if ($S^2 (x_{new}) =0$)   
> $\ \ \ \ \ \ $  输出这个解  
> $\ \ \ \ \ \ $ return 1;   
>    return 0;  

## 4 各参数设计

通过本地二分即可获得合适的参数

（本题共 $100$ 个测试点, 其中 $data\#25$ 及以后容易 $TLE$ ） 

## 5 无解判断

易发现，$x$改变某一位后，设$count(x)$ 为$x$二进制中$1$的个数，则所有的 $count(b_i)$均改变$1$($+1$或$-1$)。所以当任意$count(a_i)$与$count(a_j)$奇偶性不同时一定无解。

另外，**当模拟退火运行时间超过 $3.9s$时大概率无解，直接输出$-1$并返回（蛤?）** （如$data\#92$，任意$count(a_i)$与$count(a_j)$奇偶性相同却无解）

## 6 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef signed char          int8;
typedef unsigned char       uint8;
typedef short                int16;
typedef unsigned short      uint16;
typedef int                  int32;
typedef unsigned            uint32;
typedef long long            int64;
typedef unsigned long long  uint64;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline Int read(char &c)       
{
    Int flag = 1;
    c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}
// 以上：fastio模板

#define randR(x) (rand() % (x)) // 随机一个[0,x)之间的整数
#define double_rand_0_to_1() ((double)rand() / RAND_MAX + ((double)rand() / RAND_MAX / RAND_MAX))
#define inline // 随机一个0~1的double值
inline int count(int x) // 含义如上，求x二进制中1的个数
{
    int res = 0;
    while (x) {
        if (x & 1) res++;
        x >>= 1;
    }
    return res;
}

int n;
int a[107], cnt[107];

inline double check(int x)
{
	// 计算 S²
    int tot = 0;
    for (int i = 1; i <= n; i++) tot += (cnt[i] = count(a[i] ^ x));
    double average = tot / n, ans = 0;
    for (int i = 1; i <= n; i++) ans += (cnt[i] - average) * (cnt[i] - average);
    return ans;
}

#define startT 5000 
#define deltaT 0.999  
#define endT 0.0013  
#define acceptK 1  
#define eps 0.0003

inline bool SA() // 核心函数
{
    double best = check(0), now;
    int x = 0, op;
    for (int t = startT; t > endT && best >= eps; t *= deltaT) {
        op = 1 << randR(30);
        now = check(x ^ op);
        if (now < best) {
            best = now;
            x ^= op;
        } else if (exp((best - now) / t) < acceptK * double_rand_0_to_1()) {
            best = now;
            x ^= op;
        }
    }
    if (best < eps) {
        write(x);
        return 1;
    } 
    return 0;
}

int main()
{
    srand(20170933 ^ 201709 ^ 2017); // 为什么是这个数：信仰优化
    n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        cnt[i] = count(a[i]);
    }
    for (int i = 1; i < n; i++) { // 无解判断
        if ((cnt[i] & 1) != (cnt[i + 1] & 1)) {
            puts("-1");
            return 0;
        }
    }
    while (!SA()) if (clock() > 3.9 * CLOCKS_PER_SEC) { // 时间控制
        puts("-1");
        return 0;
    }
    return 0;
}
```

~~写完洗把脸没准就过了~~

---

## 作者：GFyyx (赞：1)

## 解题思路
$\log_{2}{a_i} < 30$ 爆搜 $\Theta(a_i)$ 的时间复杂度会超时。

但是使用折半搜索就可以通过。

### 位运算
对于十进制数 $x$，若想取二进制下 $x$ 的低 $15$ 位，代码如下：

```x&(1<<15)-1```

若想取二进制下 $x$ 的高 $15$ 位，代码如下：

```x>>15```

### 折半搜索

设 $b_i=\left\lfloor\dfrac{a_i \oplus x}{2^{15}}\right\rfloor$，$c_i=a_i \oplus (x \& (2^{15}-1))$。

由题意得，$b_1+c_1=b_i+c_i(i \in [2,n])$。

即 $b_i-b_1=c_1-c_i(i \in [2,n])$。

### 优化
求解 $b$ 数组时把每个 $x$ 对应的 $b_i-b_1$ 记录下来，与接下来的 $c_1-c_i$ 比对，每一项都相等则 $x$ 合法。

判断数组是否相等，需要花费 $\Theta(n)$ 的时间复杂度，如果常数不好程序有超时的风险且不易处理。

考虑试用 map 将数组映射成一个数字作比较，问题就迎刃而解了，总时间复杂度为 $\Theta(2^{\frac{n}{2}}n\log_{2}{n})$。

## AC 代码（附有注释）
本人码风较毒瘤，本题属于码量较小的紫题，强烈建议自己先写一下。
```cpp
#include <iostream>
#include <vector>
#include <map>
#define F for(register int i=0; i<(1<<15); i++)
#define pct __builtin_popcount
//题目中的popcount()函数 
using namespace std;
int n,a[101];
map<vector<int>,int> mp;//将数组映射成int 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	cin >> n;
	for(register int i=1; i<=n; i++)
		cin >> a[i];
	F{//高15位
		int b1=pct((a[1]>>15)^i);
		vector<int> boki;
		for(register int j=2; j<=n; j++){
			int bj=pct(i^(a[j]>>15))-b1; 
			boki.push_back(bj);
		}
		mp[boki]=i;
	}
	F{//低15位
		int c1=pct(i^(a[1]&(1<<15)-1));
		vector<int> cao;
		for(register int j=2; j<=n; j++){
			int cj=c1-pct(i^(a[j]&(1<<15)-1));
			cao.push_back(cj);
		}
		if(mp.count(cao)){
			cout << (mp[cao]<<15)+i << endl;
			return 0;
		}//发现一个x,满足bi-b1=c1-ci,找到解
	}
	cout << "-1\n";
	return 0;
}
```


---

## 作者：junxis (赞：0)

meet-in-the-middle 一下。

我们先枚举 $x$ 的后 $15$ 位，记为 $q$。并算出仅考虑 $a_i$ 的后 $15$ 位与 $q$ 异或后的 popcount，记为 $c_i$。

类似地，再枚举 $x$ 的前 $15$ 位，记为 $p$。并算出仅考虑 $a_i$ 的前 $15$ 位与 $p$ 异或后的 popcount，记为 $d_i$。

那么 $x$ 合法，当且仅当 $\forall i < n$，$c_i+d_i=c_{i+1}+d_{i+1}$。

移项，等价于 $c_i-c_{i+1}=-(d_i-d_{i+1})$。

即两个数组的差分数组每一项都互为相反数。

我们使用 rolling-hash。

在第一次枚举中使用一个 $\text{std::map}$，记录下每个差分数组的哈希值对应的任意一个 $x$ 的后 $15$ 位。

在第二次枚举中直接算出每个差分数组取相反数后对应的哈希值，检查 $\text{map}$ 中是否有这个哈希值。若有，算出 $x$，输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using hashv = pair<ll, ll>;
const ll M1 = 1e9 + 7, M2 = 1e9 + 9;

hashv operator+(hashv a, hashv b) {
	return hashv((a.first + b.first) % M1, (a.second + b.second) % M2);
}

hashv operator*(hashv a, hashv b) {
	return hashv(a.first * b.first % M1, a.second * b.second % M2); 
}

const int N = 110;
int n, a[N];
map<hashv, int> mp;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int half = 1 << 15;

	hashv base(13331, 23333);

	for (int x = 0; x < half; x++) {
		hashv hs(0, 0);
		int lst = 0;
		for (int i = 0; i < n; i++) {
			int p = a[i] & (half - 1);
			int c = __builtin_popcount(p ^ x);
			if (i) {
				hs = hs * base + hashv((c - lst + M1) % M1, (c - lst + M2) % M2);
			}
			lst = c;
		}
		mp[hs] = x;
	}

	for (int x = 0; x < half; x++) {
		hashv need(0, 0);
		int lst = 0;
		for (int i = 0; i < n; i++) {
			int p = a[i] >> 15;
			int c = __builtin_popcount(p ^ x);
			if (i) {
				need = need * base + hashv((lst - c + M1) % M1, (lst - c + M2) % M2);
			}
			lst = c;
		}
		if (mp.count(need)) {
			int ans = (x << 15) + mp[need];
			cout << ans << "\n";
			return 0;
		}
	}
	cout << "-1\n";
}
```

---

## 作者：Yansuan_HCl (赞：0)

高位和低位之间 `popcount` 互不影响，考虑折半搜索。

条件是每一位的 `popcount` 相同。先枚举低 $15$ 位 $x$ 的值，计算出低位的 `popcount` 数组；再从高 $15$ 位的值搜索。为了避免不同的和造成的影响，可以对数组差分。

需要扔到 `set` 中。大力 `set<vector<int>>` 会爆掉，可以哈希。代码需要判断哈希冲突。

```cpp
const int N = 105, S = (1 << 15);
int n, a[N];

set<pair<int, int>> st;

int hsh(const vector<int> &s) {
    const ll BASE = 3389, P = 1000000007;
    int v = 0;
    for (int i : s) 
        v = (ll(v) * BASE + (i % BASE + BASE) % BASE) % P;
    return v;
}

vector<int> gen(int x) {
    vector<int> v(n + 1);
    U (i, 1, n) v[i] = __builtin_popcount((a[i] & (S - 1)) ^ x);
    U (i, 0, n - 2) v[i] = v[i + 2] - v[i + 1];
    v.resize(n - 1); v.shrink_to_fit();
    return v;
}

int main() {
    rd(n);
    U (i, 1, n) rd(a[i]);

    U (x, 0, S - 1) 
        st.insert({hsh(gen(x)), x});
    U (x, 0, S - 1) {
        vector<int> v(n + 1);
        U (i, 1, n) v[i] = __builtin_popcount((a[i] >> 15) ^ x);
        U (i, 0, n - 2) v[i] = -(v[i + 2] - v[i + 1]);
        v.resize(n - 1); v.shrink_to_fit();
        int h = hsh(v);

        auto p = st.lower_bound({h, 0});
        while (p->first == h && gen(p->second) != v) ++p; // 防止哈希碰撞
        if (p->first != h) continue; // 写在前面会错。
        
        int ans = (x << 15) + p->second;
        exit(printf("%d", ans) & 0);
    }
    puts("-1");
}
```

~~目前（2022.9.14）是最优解。~~

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1257F)

# 题解

考虑先将每一位上单独异或一个 $1$ 所有数会使 $a[i]$ 发生什么变化，可以这样预处理出来：

```cpp
inline void Getcnt(){
    rep(i,0,MAXK){
        rep(j,1,n)if((a[j]^(1<<i))<a[j])cnt[i][j]=-1;
        else cnt[i][j]=1;
    }
}
```

并且，我们可以得到 $a[i]$ 的 $1$ 的个数，这样：

```cpp
inline void Getbitcnt(){
    rep(i,1,n){
        rep(j,0,MAXK)if((a[i]>>j)&1)
            ++bitcnt[i];
    }
}
```

而我们的目标就是，尝试将一些 $cnt[i]$ 影响在 $a$ 数组上，最后使得每一个 $a[j]$ 都一样

如果我们直接暴力，时间复杂度无疑是 $\mathcal O(2^{30}n)$ 会超时，想到一个优化——折半搜索

尝试以 $[0,14]$ 和 $[15,29]$ 分开组合 $cnt[i]$，最后我们枚举答案中所有数的 $1$ 的个数为 $k$，再枚举第一个暴力部分的组合，在第二个部分中用 `map` 或者其他数据结构找到是否存在这样的组合即可

可以有一个小优化，省掉 $30$ 的常数：

由于我们最后的数的 $1$ 个数相同，那么我们可以维护差分数组，那么最后的差分数组一定全为 $0$，然后用相同方法去找即可

时间复杂度 $\mathcal O(2^{15}\times 2+2^{15}\times 15)$

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13343252.html
```



---

## 作者：灵茶山艾府 (赞：0)

根据异或的定义可以知道：一个数若某个位上是 $0$，该位异或 $1$ 之后，该数二进制中 $1$ 的个数会 $+1$；若某个位上是 $1$，该位异或 $1$ 之后，该数二进制中 $1$ 的个数会 $-1$

故原题可以转化成如下问题：

有 $n$ 个数 $base\_ones$（原数据二进制 $1$ 的个数）和 $30$ 个操作 $ops$，其中 $ops[i]$ 是将这 $n$ 个数中的某些数 $+1$，某些数 $-1$。问能否从这 $30$ 个操作中选取若干操作，使得这 $n$ 个数都相同。

由于数据量很小，考虑暴力枚举：

1. 从 $0$ 到 $30$，枚举目标值 $ones$，对每个目标值，进行步骤 $2$ - $4$
2. 将这 $30$ 个操作拆分成相等的两部分 $ops_0$ 和 $ops_1$
3. 枚举 $ops_0$ 集合，计算操作累加的结果集合 $sum\_op_0$，将其存入一 $map$
4. 枚举 $ops_1$ 集合，计算操作累加的结果集合 $sum\_op_1$，基于等式 $base\_ones+sum\_op_0'+sum\_op_1=ones$（集合中对应元素相加）可以计算出 $sum\_op_0'$，若其在 $map$ 中存在，则上述问题的操作选取是存在的。
5. 若枚举结束仍未找到，则上述问题的操作选取不存在。

AC 代码如下（Golang）

```go
package main

import (
	. "fmt"
	"math/bits"
)

func main() {
	var n int
	Scan(&n)
	ops := [30][100]int8{}
	baseOnes := [100]int8{}
	for j := 0; j < n; j++ {
		var v uint
		Scan(&v)
		for i := range ops {
			if v>>uint(i)&1 == 0 {
				ops[i][j] = 1
			} else {
				ops[i][j] = -1
			}
		}
		baseOnes[j] = int8(bits.OnesCount(v))
	}

	for ones := int8(0); ones <= 30; ones++ {
		mp := map[[100]int8]uint{}
		for i := uint(0); i < 1<<15; i++ {
			sumOp0 := [100]int8{}
			for j := uint(0); j < 15; j++ {
				if i>>j&1 == 1 {
					for k, v := range ops[j] {
						sumOp0[k] += v
					}
				}
			}
			mp[sumOp0] = i
		}
		curOnes := [100]int8{}
		for i := 0; i < n; i++ {
			curOnes[i] = ones - baseOnes[i]
		}
		for i := uint(0); i < 1<<15; i++ {
			targetSumOp0 := [100]int8{}
			for j, v := range curOnes {
				targetSumOp0[j] = v
			}
			for j := uint(0); j < 15; j++ {
				if i>>j&1 == 1 {
					for k, v := range ops[j+15] {
						targetSumOp0[k] -= v
					}
				}
			}
			if v, ok := mp[targetSumOp0]; ok {
				Print(i<<15 | v)
				return
			}
		}
	}
	Print(-1)
}
```


---

## 作者：chenxia25 (赞：0)

这是个挺巧妙的思维题。考虑折半枚举，左右边 $2^{15}$ 种，每种处理出 $a_{2\sim n}\oplus x$ 依次与 $a_1\oplus x$ 的 popcount 的差值的 `vector`。然后两边的 `vector` 互补就是个合法情况。考虑用 `set` 存 `vector`，这样复杂度是 $\mathrm O\!\left(2^{15}n\log\right)$，换成排序 + 二分常数似乎小一点，但还是过不去（我人傻常数大/kk）。于是可以对 `vector` 哈希把 $\log$ 去掉。

---

