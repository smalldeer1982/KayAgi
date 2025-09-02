# 统计问题 The Counting Problem

## 题目描述

给定两个整数 $a$ 和 $b$，求 $a$ 和 $b$ 之间的所有数字中 $0$ ~ $9$ 出现次数。

例如，$a$ = $1024$，$b$ = $1032$，则 $a$ 和 $b$ 之间共有 $9$ 个数如下：

`1024 1025 1026 1027 1028 1029 1030 1031 1032`

其中 `0` 出现 $10$ 次，`1` 出现 $10$ 次，`2` 出现 $7$ 次，`3` 出现 $3$ 次等等……

## 样例 #1

### 输入

```
1 10
44 497
346 542
1199 1748
1496 1403
1004 503
1714 190
1317 854
1976 494
1001 1960
0 0
```

### 输出

```
1 2 1 1 1 1 1 1 1 1
85 185 185 185 190 96 96 96 95 93
40 40 40 93 136 82 40 40 40 40
115 666 215 215 214 205 205 154 105 106
16 113 19 20 114 20 20 19 19 16
107 105 100 101 101 197 200 200 200 200
413 1133 503 503 503 502 502 417 402 412
196 512 186 104 87 93 97 97 142 196
398 1375 398 398 405 499 499 495 488 471
294 1256 296 296 296 296 287 286 286 247```

# 题解

## 作者：LittleMoMol (赞：12)

## UVA 1640 统计问题 The Counting Problem 题解

### 警示后人

题目不允许行末输出多于空格！！

---

### 思路

很明确，是一个数位 $DP$，我们先考虑一些简单的问题。



#### No. 1 如何表示区间的个数

假如有个函数 $\operatorname{count}(a,i)$ 可以返回 $0 \sim a$ 之间数字 $i$ 出现的次数，那么我们要如何表示区间 $l \sim r$ 中相应数字出现的个数？

答案很显然，$\operatorname{count}(r, i) - \operatorname{count}(l-1, i)$，前缀和思想。



#### No. 2 如何将一个十进制数的每一位存入数组中

这个很简单，我就直接上代码了。

```cpp
int get_num(vector<int> num, int l, int r)
{
    int res = 0;
    for (int i = l; i >= r; i -- )
        	res = res * 10 + num[i];
    return res;
}
```

#### No. 3 如何计算 $10$ 的 $n$ 次幂

这个似乎更简单了，可以直接调用库函数，也可以自己手写一个，都不难。

```cpp
int power10(int x)
{
	int res = 1;
	while (x -- ) res *= 10;
	return res;
}
```

#### No. 4 重点：实现 $\operatorname{count}$ 函数

和这个相比，前三个点只是浩瀚星空中的一点灰尘。

举个栗子，令 $n=\overline{abcdefg}$，现在尝试求第 $4$ 位为 $1$ 的个数，可以把 $n$ 写成 $\overline{xxx1yyy}$，我们分类讨论。

-  $xxx=\overline{000} \sim \overline{abc}-1$

  这种情况下，显然后面的 $yyy$ 可以取到 $000 \sim 999$，所以总数量就为 $\overline{abc} \times 1000$ 

-  $xxx=\overline{abc}$ 

  这种情况下，再细分几个情况。
  -  $d < 1$ 

    如果 $n$ 的第 $4$ 位小于 $1$，那么无论 $\overline{yyy}$ 如何取值，都不能改变我们现在枚举的数比 $n$ 大，所以这种情况下答案是 $0$ 

  -  $d = 1$ 

    显然，满足条件的 $yyy=\overline{000} \sim \overline{efg}$，所以答案是 $\overline{efg} + 1$

  -  $d > 1$

    这种情况 $\overline{yyy}$ 无论如何取值都满足要求，所以答案为 $1000$ 

至此，我们将所有情况都不重不漏地讨论完毕了！

#### No. 5 特例

~~易知~~当想要统计的数字为 $1 \sim 9$ 时上述做法毫无问题，但是数字为 $0$ 的时候就得考虑前导零的影响了。

还拿上面的例子来说，如果尝试求第 $4$ 位为 $0$ 的个数，那么 $\overline{0000efg}$ 就不是所求了，所以要减去，这将在代码中有体现。

#### No. 6 Code

  ```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 10;

int get_num(vector<int> num, int l, int r)
{
    int res = 0;
    for (int i = l; i >= r; i -- )
        res = res * 10 + num[i];
    return res;
}

int power10(int x)
{
    int res = 1;
    while (x -- ) res *= 10;
    return res;
}

int count(int n, int x)
{
    if (!n) return 0;
    
    vector<int> num;
    while (n)
    {
        num.push_back(n % 10);
        n /= 10;
    }
    n = num.size();
    
    int res = 0;
    for (int i = n - 1 - !x; i >= 0; i -- ) //注意特例
    {
        if (i < n - 1)
        {
            res += (get_num(num, n - 1, i + 1) - (!x)) * power10(i); //注意特例
        }
        
        if (num[i] == x) res += get_num(num, i - 1, 0) + 1;
        else if (num[i] > x) res += power10(i);
    }
    
    return res;
}

int main()
{
    int a, b;
    while (cin >> a >> b, a)
    {
        if (a > b) swap(a, b);
        
        for (int i = 0; i <= 9; i ++ )
            cout << count(b, i) - count(a - 1, i) << ' '; //前缀和思想
        cout << endl;
    }
    
    return 0;
}
```




本人第一篇题解~

不喜勿喷~ ​

---

## 作者：Ofnoname (赞：7)

这道题不能输出多余空格，可把我害惨了。

我是从多倍经验过来的，正好复习基础的数位DP。

----

### 1. 预处理

我们先允许前导0存在，用$f[i][j][p]$表示“长度为i，以j开头的所有数字里p的次数”。

当我们考虑到第i位时，枚举最高位j和次高位k（从0到9），相同的数字方案都是可以继承的，即$f[i][j][p] = \sum _{p=0} ^ 9 f[i-1][k][p]$。

除了继承以外就是新增的次数，现在的j作为最高位，那么后i-1位共$10^{i-1}$个数字最高位都多了一个j，所以j多了$10^{i-1}$个。

边界情况：$f[1][i][i] = 1$，一位数是没有次高位的，$10^0$也为1，所以这个方程可以直接处理边界。

```cpp
for (int i = 1; i <= 9; i++)
	p10[i] = p10[i-1] * 10;
for (int i = 1; i <= 9; i++)
for (int j = 0; j <= 9; j++)
{
	for (int k = 0; k <= 9; k++)
	for (int p = 0; p <= 9; p++)
		f[i][j][p] += f[i-1][k][p];
	f[i][j][j] += p10[i-1];
}
```

----

### 2. 计算

用$[1,R]$的答案减去$[1,L)$的答案就是正确答案，用一个函数计算即可。答案贡献分为3种。

- 位数小于R的所有数都是可以的，枚举小于`len(R)`的所有i和j，他们都要算入答案。但是首位不能为0，j要从1开始枚举。

- 位数等于`len(R)`，最高位小于R的最高位，从1开始枚举j，枚举到最高位即可。

- 位数等于`len(R)`，前几位都相等，第i位小于R的第i位。仍然枚举小于R对应位的j即可，但是此时不是最高位，0也要算。还有就是前几位相等的数也要算，把每个数都计算一遍即可。

比如：`23456`，当前枚举到第3位`23???`，那么第三位应该取在$[0,4)$内，2，3各出现了400次。

那么显然这个不能计算出R本身，所以$work(R+1)-work(L)$才是答案。

另外$L>R$时不是输出0，是要把两边交换。

```cpp
void work(int x, int *ans)
{
	int cx[10], len = 0;
	do {
		cx[++len] = x % 10, x /= 10;
	} while(x);//十进制分解这个数
	
	for (int i = 1; i < len; i++)
	for (int j = 1; j <= 9; j++)
	for (int p = 0; p <= 9; p++)
		ans[p] += f[i][j][p];//情况1
	for (int j = 1; j < cx[len]; j++)
	for (int p = 0; p <= 9; p++)
		ans[p] += f[len][j][p];//情况2
	for (int i = len-1; i >= 1; i--)
	{
		for (int j = 0; j < cx[i]; j++)
		for (int p = 0; p <= 9; p++)
			ans[p] += f[i][j][p];//情况3
		for (int p = len; p > i; p--)
			ans[cx[p]] += cx[i] * p10[i-1];//情况3
	}
}
```

---

## 作者：4607wjq (赞：4)

## 核心思想：
 1.分情况讨论。   
 2.不妨记 `f[i][j]` 为 $1 \sim i$ 中数字 $j$ 出现的次数，则 $l \sim r$ 中数字 $j$ 出现的次数等于 $1 \sim r$ 的次数减去 $1 \sim (l-1)$ 的次数，即 `f[r][j] - f[l - 1][j]`。由此，我们只需要求出 $1$ 到 $n$ 中任意数字出现次数即可。
## 分情况讨论：
从数字 $\overline{hijklmn}$ 说起，其中每个字母代表该位的数字，例如，对于 $\overline{ab}$ 来说，当 $a=b=1$ 时，数字就是 $11$。  

我们考察 $0000001$ 到 $\overline{hijklmn}$ 的所有数字中数字 $x$ 出现的次数，我们讨论 $x$ 在每一位上出现的次数，下面以在第 $4$ 位为例。  

我们固定这一位，看看能够构造出 $0000001$ 到 $\overline{hijklmn}$ 中的多少数，那么就有多少数第 $4$ 位有 $x$。不放设当前考察数字为 $\overline{abcdefg}$。
### （一）$\overline{abc} \in [000, \overline{hij})$ 时：
此时无论 $x$ 取何值，由于更高位没有突破 $\overline{hij}$ 的限制，所以都是合法的，即 $1$ 到 $9$ 的任意 $x$ 值，都是可以的（之后解释为什么 $x=0$ 时有限制）。

后三位同理，即 $\overline{efg} \in [000, 999]$。观察到当 $x$ 不为 $0$ 时，$\overline{abc}$ 可以取 $000$ 到 $\overline{hij}-1$ 共 $\overline{hij}$ 种，后三位显然是 $999+1=1000$ 种方式，所以组合可知：
#### 当 $x≠0,\overline{abc} \in [000, \overline{hij})$ 时，有 $\overline{hij} \times 1000$ 个数第 $4$ 位出现了 $x$。

#### 下面对 $0$ 单独考察：
观察到当 $x$ 取 $0$ 时，$\overline{abc}$ 若取 $000$，则这个数字并没有第 $4$ 位（此时第 $4$ 位被算作前导零），但其余情况均可，所以此时 $000$ 不算，是 $(\overline{hij}-1) \times 1000$ 个数。

### （二）$\overline{abc}=\overline{hij}$ 时：
观察到此时 $\overline{abcdefg}$ 的 $d$ 最高取到 $k$，否则整个数大于 $\overline{hijklmn}$。  
我们细分下面三种情况：
#### 1.$k < x$：
当我们尝试将 $x$ 嵌入第 $4$ 位时，由于 $\overline{abc}=\overline{hij}$，所以无论后三位怎么取，都有 $\overline{abcxefg}>\overline{hijklmn}$，故此时是 $0$ 种。
#### 2.$k = x$：
此时由于 $\overline{abcx}=\overline{hijk}$，则 $\overline{efg} \in [000,\overline{lmn}]$，否则构造的数更大。
此时共 $000\sim \overline{lmn}$ 这些方案，即 $\overline{lmn}+1$ 种选法。
#### 3.$k > x$：
由于 $\overline{abcx}<\overline{hijk}$，所以无论后三位怎么取，所构造的整个数都是小于 $\overline{hijklmn}$ 的。所以后三位可以取 $000 \sim 999$，共 $1000$ 种。
#### 综上所述，我们就对一般地数据处理有了思路，下面用注释解释代码。
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define v vector<int>

using namespace std;

int get(int l, int r, v num)  // 获取从第 l 位到第 j 位的数值。
{
    int res = 0;
    for (int i = r; i >= l; i -- )  // vector 储存，和一般表达略有区别。
        res = res * 10 + num[i];
    return res;
}

int power10(int n) // 求 10 的 n 次方，和 get 连用，用于返回数字中特定位置的真实值。
{                         // 例如，234873 中，从第 2 位到第 4 位，get 返回 487，再乘 power10 函数，是 4870。
    int res = 1;
    while (n -- )
        res *= 10;
    return res;
}

int count(int n, int x)
{
    if (!n)
        return 0;
    
    v num; int res = 0;
    
    while (n) // 用 vector 存储数字，便于使用。
    {
        num.push_back(n % 10);
        n /= 10;
    }
    n = num.size();
    
    // 枚举每一位。
    for (int i = n - 1 - !x; i >= 0; i -- )  // 首位不能取 0， 所以 x = 0 时，会从 n - 2 位开始枚举。
    {
        if (i != n - 1)  // 当考察最高位时，不存在第一种情况。
        {
            res += get(i + 1, n - 1, num) * power10(i);  // 由于下标从 0 开始，所以是 power10(i - 1 + 1);
            if (!x)
                res -= power10(i);   // 特殊照顾一下 0，题解中的 (abc - 1) * 1000 中 -1 出来就是一般情况再减去 1000；
        }                            //  一般情况就是减去 power10(i)
        
        if (num[i] == x)
            res += get(0, i - 1, num) + 1;
        if (num[i] > x)
            res += power10(i);
    }
    
    return res;
}

int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        if (!a && !b)
            return 0;
        if (a > b)
            swap(a, b);
        
        for (int i = 0; i < 9; i ++ )
            cout << count(b, i) - count(a - 1, i) << ' ';
        cout << count(b, 9) - count(a - 1, 9);
        puts("");
    }
}
```

---

## 作者：初音Miku (赞：4)

```cpp
#include <stdio.h>
#include <math.h>//两个打酱油的头文件
#include<Hatsune_Miku>真正能AC的头文件
#include<bits/stdc++.h>//真正发挥作用的大哥
using namespace std;
__int64 ans[10], cal[10];
int tre[10], arrx[9] = {0, 1, 20, 300, 4000, 50000, 600000, 7000000, 80000000};
int arrz[9] = {0, 1, 10, 190, 2890, 38890, 488890, 5888890, 68888890};//根据题意可得
//根据题意定义，大家可以去原OJ看下题
void deter (int a)
{
    memset(tre, 0, sizeof(tre));//清空
    if (a == 0) tre[0] = 1;
    while (a)
    {
          tre[a % 10]++;
          a /= 10;
    } return;
}
//不解释的定义
int pwr10[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
int absorb (int a, int s)
{
    a /= pwr10[s - 1];
    return a % 10;
}//神奇的东西

void calc (int ed)//计算函数
{
    int digi = (int)(log10(ed) + 1), i, j, k, er, nsa = 0;
    memset(cal, 0, sizeof(cal));
    if (ed == 0) { cal[0] = 1; return; }
    for (i = digi; i >= 1; i--)
    {
        nsa *= 10;
        er = absorb(ed, i);
        for (j = 0; j < er; j++)
        {
            if (nsa + j != 0 || i == 1)
            {
               deter(nsa + j);
               for (k = 0; k < 10; k++)
                   cal[k] += (__int64)tre[k] * pwr10[i - 1];
            }
            for (k = 1; k < 10; k++)
                cal[k] += arrx[i - 1];
            if (nsa + j == 0) cal[0] += arrz[i - 1];
            else cal[0] += arrx[i - 1];
        }
        nsa += er;
    }
    deter(ed);//看不懂得就跟我一起看吧....
    for (k = 0; k < 10; k++)
        cal[k] += tre[k];
    return;//这过程让我无法解释，我只是个弱弱弱的OIer
}
//中间过程不解释，因为我也不怎么会，迷迷糊糊算是看着还可以.......
int main ()
{
    int x, y, t, i;
    while (初音殿下赛高~)//防作弊true or 1即可
    {
          scanf("%d %d", &x, &y);
          if (x == 0 && y == 0) break;
          if (x > y) { t = x; x = y; y = t; }
          calc(y);
          for (i = 0; i < 10; i++)
              ans[i] = cal[i];
          calc(x - 1);
          for (i = 0; i < 10; i++)
              ans[i] -= cal[i];
          for (i = 0; i < 10; i++)
              printf("%I64d ", ans[i]);//这个地方要修改O(∩_∩)O哈，根据原作者意愿，我没修改。
          printf("\n");//记得换行，不然会哭一辈子。。
    }
    return 0;//再见喽，完美AC
}

```
特别鸣谢
# 《算法竞赛进阶指南》 
## 李煜东著作
看到这个题没题解我就搬过来了，大家看不懂得继续看书哦

---

## 作者：ekatsim (赞：3)

蒟蒻不会数位 DP，所以来一篇暴力吧 QAQ。

# 思路
看到数据范围 $10^8$，而且是多次询问，所以直接暴力模拟是显然不行的。考虑优化一下，我们只要预处理出 $10^8$ 范围内的答案，将答案分块，然后依照询问查询相应的块就可以了。（~~就是一个正常的分块~~）

本来觉得可能常数比较大，可能过不了,没想到 UVA 神机居然给过了。

# 代码
```cpp
#include <bits/stdc++.h>
#define inf 2147483647
#define mod 998244353
#define lowbit(x) x&-x
const int maxn=2e5+5;
using namespace std;
struct node
{
    int cnt[10];
}all[10005];
int ans[10];
int main()
{
    for(int i=1;i<=1e8;i++)//预处理分块，块长10000
    {
        int id=i/10000;
        int split=i;
        while(split)
        {
            all[id].cnt[split%10]++;
            split/=10;
        }
    }
    int a,b;
    while(scanf("%d %d",&a,&b),a)
    {
        if(a>b)
            swap(a,b);//注意！！不保证a<b！！
        memset(ans,0,sizeof(ans));
        int lef=a/10000+1,rig=b/10000-1;
        for(int i=lef;i<=rig;i++)
            for(int j=0;j<=9;j++)
                ans[j]+=all[i].cnt[j];
        for(;a<10000*lef&&a<=b;a++)//处理"零散"部分
        {
            int split=a;
            while(split)
            {
                ans[split%10]++;
                split/=10;
            }
        }
        for(;b>=10000*(rig+1)&&a<=b;b--)
        {
            int split=b;
            while(split)
            {
                ans[split%10]++;
                split/=10;
            }
        }
        for(int i=0;i<9;i++)
            printf("%d ",ans[i]);
        printf("%d\n",ans[9]);
    }
    return 0;
}
```


---

## 作者：蒟蒻溴化氢 (赞：2)

UVA卡输出 实在是不知道哪里错了 POJ上能过

~~我感觉另一篇题解什么也没有说~~

首先 我们要求$[L,R]$ 的出现次数

等效于求$[1,R]$的方案数减去 $[1,L-1]$的方案数

我们来考虑数位dp 在允许先导0存在的情况下 

我们设 $dp[i][j][k]$ 表示:

最低位是第一位 在第i位填j,从这一位填j的最小值到这一位填j的最大值 k出现的次数

那么就有方程$dp[i][j][k]=\sum dp[i-1][l][k] ~~~~~l \in[0,9] $  

但是我们需要的个数是不能有先导0存在的 因此我把没有先导0的方案数单独拿出来考虑 

$zero[i]$表示在第i位填0的最小值到第i为填0的最大值的方案数
有方程:

$$
zero[i]=(\sum dp[i-1][j][0])+zero[i-1];~~~j \in [1,9]
$$

最后 就是如何拼凑出答案
对于我们要求$[1,x]$的答案
1. 先从高位到低位枚举

2. 枚举这一位要填的数 枚举的上界是不能超过当前x的位

3. 累加每一种数字出现次数

最后要注意的是 因为没有先导0的存在 所以我们在最高位填0的时候累加的应该是zero答案而不是dp中的答案


```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define il inline
#define res register int
using namespace std;
const int N=11;
il int read()
{
	int x=0,f=0,c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return f?-x:x;
}
int a,b;
int dp[N][N][N];
int ans[2][N];
int mi[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
int zero[N];
void clean()
{
	memset(ans,0,sizeof ans);
}
int wk[15],tot;

void work(int x,int id)
{
	 if(x==0||x==-1) { ans[id][0]=1; return;}
	 int t=x; tot=0;
	 while(x) 
	 	wk[++tot]=x%10,x=x/10; x=t; int tmp=0;
	 for(res p=tot;p>=1;p--)
	 {
		 int cur=wk[p];
		 for(res i=0;i<cur;i++) 
		 	for(res j=0;j<10;j++)
		 	{
		 		if(p==tot&&i==0&&j==0) ans[id][j]+=zero[p];
				else ans[id][j]+=dp[p][i][j];
		 	}
		tmp+=cur*mi[p-1];
		ans[id][cur]+=x-tmp+1;
	 }
}

void pre()
{
	for(res i=0;i<=9;i++) dp[1][i][i]=1;
	for(res i=2;i<=9;i++)
		for(res j=0;j<10;j++)
			for(res k=0;k<10;k++)
			{
				for(res l=0;l<10;l++)
					dp[i][j][k]+=dp[i-1][l][k];
				if(j==k) dp[i][j][k]+=mi[i-1];
			}
	zero[1]=zero[2]=1;
	for(res i=3;i<=9;i++)
	{ 
		for(res j=1;j<10;j++)
			zero[i]+=dp[i-1][j][0];
		zero[i]+=zero[i-1];
	}
}


int main()
{
	pre();
	while(1)
	{
		clean();
		a=read(); b=read(); if(a>b) swap(a,b);
		if(!a&&!b) break;
		for(res i=0;i<10;i++) dp[1][i][i]=1;
		work(b,1);
		work(a-1,0);	
		for(res i=0;i<10;i++)
		{
			printf("%d ",ans[1][i]-ans[0][i]);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：火箭升空 (赞：2)

**- 这道题作为数位DP的典型题，还是很有必要仔细研究吃透的~**

这道数位DP难就难在找到递推公式，乍一看似乎没有什么规律，因为每个数的位数可能不一样...那怎么办呢？我们可以在每个数前面补上**前导零**！这样一看，似乎就可以写一写递推公式了！

我们设f[i]为i位数字，每个数字的个数。。（很容易，我们可以证得，不考虑前导零的情况下，每个数字的个数是相同的）
 
### 于是就有了f[i]=f[i-1]*10+10^(i-1)。

接下来，实现起来就很容易啦。举个例子：

对于三位数ABC，我们首先看A00，那么从0到A00每位数字出现的个数都是A*f[2]次（不考虑第一位），再考虑首位，则0~A-1 又分别出现了100次。现在，就差首位的A没有处理了！！怎么处理呢？首位的A其实出现了BC+1次！很简单对不对！然后只需对BC，C进行相同操作。

这样，我们就基本处理完了！但是，别忘了减去前导零...~~（千万别忘记，别问我是咋知道的...）~~

OK！现在！上代码喽！

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
long long cnt1[15], cnt2[15], f[15], mi[15], num[15];
long long a, b;
void solve(long long x, long long *cnt) {
  long long len = 0;
  memset(num, 0, sizeof(num));
  while (x) {
    num[++len] = x % 10;
    x /= 10;
  }
  for (int i = len; i >= 1; i--) {
    for (int j = 0; j <= 9; j++) {
      cnt[j] += f[i - 1] * num[i];
    }
    for (int j = 0; j < num[i]; j++) {
      cnt[j] += mi[i - 1];
    }
    long long res = 0;
    for (int j = i - 1; j >= 1; j--) {
      res *= 10;
      res += num[j];
    }
    cnt[num[i]] += res + 1;
    cnt[0] -= mi[i - 1];
  }
}
void init() {
  memset(cnt1, 0, sizeof(cnt1));
  memset(cnt2, 0 ,sizeof(cnt2));
}
int main() {
  while (cin >> a >> b) {
    if (a == 0 && b == 0) return 0;
    if (a > b) swap(a, b);
    init();
    mi[0] = 1;
    for (int i = 1; i <= 13; i++) {
      f[i] = f[i - 1] * 10 + mi[i - 1];
      mi[i] = 10 * mi[i - 1];
    }
    solve(a - 1, cnt1); solve(b, cnt2);
    for (int i = 0; i <= 8; i++) {
      cout << cnt2[i] - cnt1[i] << ' ';
    }
    cout << cnt2[9] - cnt1[9];
    cout << endl;
  }

  return 0;
}
```

额，，，别忘了别多输出空格...

~~好啦，看完别忘给个赞~~~

求求管理员给过吧www

---

## 作者：cherubim (赞：1)

### 千万不要输出多余的空格！！！

~~可把孩子提交惨了QAQ~~

分析题目：第一眼看到思维那当然就是暴力，直接枚举并写函数来分解每一个数，然后用一个数组乘起来统计最后输出。思路当然是简单的，可是一看这数据范围就给吓傻了QAQ

暴力不行，那就必须得用其他思路来写了

可是蒟蒻不会数位DP啊QAQ，这可怎么办呢

~~这时候就应该用数位DP的思想来混子了~~

数位dp其实就是两个部分。初始化、求解。那我们可以大致了解一下思路后，用一种稍微高一点的时间复杂度的方式按照数位dp的思路来枚举。

求 $a$ 到 $b$ ，那么就用 $solve(b + 1) - solve(a）$ 来计算。

我们不妨可以设 $f[i][j][k]$ 表示第i位，最高位为j，k有多少个。
那么我们就可以用f数组来表示我们的每一个数位。

稍微分析一下就可以知道，第i位上k出现的次数为 $\sum\limits_{l=0}^ f[i-1][l][k] $ +这个数在i位上出现的次数 。 i-1 来继承上一位统计的这个数字出现的次数。那么，怎么计算这个数在这个数位出现了多少次呢?

简单分析一下：如果 $j < k$ 或 $j > k$ ，那就没有。

当 j==k时， 举个栗子，比如说 $[100,199]$ , 可以看出数字1肯定出现了100次，那么就可以推出：$f[i][j][j]+=10^{i-1}$。

那么接下来只要注意处理前导0的情况，按照位数依次统计就行了。


### CODE
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000010
#define INF 1<<30
#define mod 100000007

using namespace std;

int a,b;
int f[110][110][110]; 

int solve(int x,int num){
	int kkk[1000];
	int ans=0,len=0;
	memset(kkk,0,sizeof(kkk));
	while(x!=0){
		kkk[++len]=x%10;
		x/=10;
	}
	for(int i=1;i<len;i++){
		for(int j=1;j<=9;j++){
			ans+=f[i][j][num];
		}
	}
	
	for(int i=1;i<kkk[len];i++)  //统计位数与原数一样，但最高位较小的数，不能有前导零；
		ans+=f[len][i][num];
    for(int i=len-1;i>=1;i--){
    	int x_x=kkk[i];
    	for(int j=0;j<x_x;j++)
    		ans+=f[i][j][num];
		for(int j=len;j>i;j--)
			if(kkk[j]==num) ans+=kkk[i]*pow(10,i-1);
	}
	return ans;
}
signed main()
{
	//初始化
	for(int i=0;i<=9;i++) f[1][i][i]=1;
	for(int i=2;i<=100;i++){//总共的位数 
		for(int j=0;j<=9;j++){ //此位数 
			for(int l=0;l<=9;l++){//上位数 
				for(int r=0;r<=9;r++){ //统计 
					f[i][j][r]+=f[i-1][l][r]; 
				}
			}
			f[i][j][j]+=pow(10,i-1);
		}
	}
	 
	int T;
	cin>>T;
	while(T--){
		scanf("%lld %lld",&a,&b);
		int ans=0;
		for(int i=0;i<=9;i++)
			ans+=(solve(b+1,i)-solve(a,i))*i;	
		printf("%lld\n",ans);
	}
	
	return 0;
}
```



---

## 作者：_Scaley (赞：1)

## 题意

给出两个整数 $a$ 和 $b$ ，统计在区间 $[a,b]$ 的整数中，数码 $0$ 到 $9$ 各出现了几次并依次输出 。

## 解法

由于是数位 dp 的模板题，所以理所当然用最好记的记忆化搜索来做啦 。

#### 下面放上模板来解释一下：

|变量名|意义|
|:----:|:----:|
|pos|现在搜索到的位数|
|Qd1|判断有无前导零|
|Qd2|判断是否到了边界|
|top|边界|
|ans|统计答案|
|sum|统计到的数字的数目|
|f[pos][sum]|记忆化数组|
|a[pos]|记录边界的数组|

```c++
int dp(int pos, bool Qd1, bool Qd2, int sum) {
	if (!pos) return sum; // 如果已经搜到第零位数了（不存在），那么这个数是合法的，返回值
	if (!Qd1 && !Qd2 && f[pos][sum] != -1) return f[pos][sum]; // 如果没有前导零，没到达边界而且记忆化数组已统计，返回记忆数值
	int top = Qd2 ? a[pos] : 9, ans = 0; // 确认需要枚举到的边界
	for (int i = 0; i <= top; ++i) // 枚举数字
		ans += dp(pos - 1, !(i || !Qd1), Qd2 && i == a[pos], sum + ((i == shu) && (i || !Qd1))); // 统计答案
	if (!Qd1 && !Qd2) f[pos][sum] = ans; // 记忆化
	return ans; // 返回答案
}
```

#### 一些小地方：

我们可以想象，$f[i][j]$ 数组记录的是第 $i$ 位数，前一个数为 $j$ 的数的方案数，

如果这个数组已经在还未到达边界，还未有前导零的时候已经被更新过了，这时候递归到边界，$f[i][j]$ 记录的是后面的数从 $[0,9]$ 的方案数，

但这时候边界不一定能取到 $[0,9]$，所以不判边界和前导零显然是不对的。

## 完整代码

```c++
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#define MAXN 23
#define int long long // 这个是个保险
//-------------定义结构体-----------

//--------------定义变量------------
int shu;
int f[MAXN][MAXN], a[MAXN];
//--------------定义函数------------
inline int read() { // 快读
	int x = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void swap(int &l, int &r) {
	l ^= r ^= l ^= r;
}
int dp(int pos, bool Qd1, bool Qd2, int sum) { // 这个前面解释了
	if (!pos) return sum;
	if (!Qd1 && !Qd2 && f[pos][sum] != -1) return f[pos][sum];
	int top = Qd2 ? a[pos] : 9, ans = 0;
	for (int i = 0; i <= top; ++i)
		ans += dp(pos - 1, !(i || !Qd1), Qd2 && i == a[pos], sum + ((i == shu) && (i || !Qd1)));
	if (!Qd1 && !Qd2) f[pos][sum] = ans;
	return ans;
}
int pre(int i) { // 把数字的每一位拆分，以便判断每一数位的边界
	int cnt = 0;
	memset(f, -1, sizeof f); // 记的清空记忆数组
	while (i != 0)
		a[++cnt] = i % 10, i /= 10;
	return dp(cnt, 1, 1, 0);
}
//---------------主函数-------------
signed main() {
	int l, r;
	while (1) {
		l = read(), r = read();
		if (l > r) swap(l, r); // l 可能大于 r（保险）
		if (l == 0 && r == 0) break;
		for (int i = 0; i <= 9; ++i) {
			shu = i;
			if (i == 9) printf("%lld", pre(r) - pre(l - 1)); // 防止多输出空格
			else printf("%lld ", pre(r) - pre(l - 1));
		}
		printf("\n"); // 记得换行
	}
	return 0;
}
```

---

## 作者：TempestMiku (赞：0)

数位 dp 经典题。我们需要对一个数的每一位都进行考虑得出答案。

[windy数（另一个经典题）](https://www.luogu.com.cn/problem/P2657) 

[双倍经验](https://www.luogu.com.cn/problem/P2602) 

假设一个数为 $\overline{abcdefg}$，要求第 $4$ 位是 $2$ 的个数，我们可以这样考虑。

当前三位属于 $\overline{000} \sim \overline{abc}-1$ 时，后面四位可以随便取得，所以第四位可以为 $2$ 的共有 $\overline{2000} \sim \overline{2999}$ 共 $1000$ 个，即 $abc\times 10^{\text{位数}-1}$ 个。

注意 $0$ 的特判，当 $\overline{abc}=\overline{000}$ 时他没有第四位，故 $(abc-1)\times 10^{\text{位数}-1}$ 个。

当前三位是 $\overline{abc}$ 时：

- 如果第四位的 $\overline{d}=2$ 时，后面只能选择 $\overline{000}\sim \overline{efg}$  共 $efg+1$ 个数。

- 如果第四位的 $\overline{d}>2$ 时，后面可以选 $\overline{000}\sim \overline{999}$
 共 $10^{\text{位数}-1}$ 个。

注意 $0$ 的特判，如果是 $0$ 的话，因为第一位不能是 $0$，所以要从倒数第 $2$ 位开始取。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar(' ');
    }
}
using namespace Testify;
int n,m;
inline int qpow(int b){
    int a=10;
    int res=1;
    while(b){
        if(b&1) res=res*a;
        b>>=1;
        a*=a;
    }
    return res;
}
inline int howmany(vector<int> Spasmodic,int l,int r){
    int Igallta=0;
    for(register int i=l;i>=r;i--){
        Igallta=Igallta*10+Spasmodic[i];
    }
    return Igallta;
}
inline int SATELLITE(int n,int num){
    vector<int> q;
    int op=n;
    while(op){
        q.push_back(op%10);
        op/=10;
    }
    int TERABYTE=0;
    bool flag;
    if(!num){
        flag=true;
    }
    else{
        flag=false;
    }
    for(register int i=q.size()-1-flag;i>=0;i--){
        if(i==q.size()-1) goto IZANA;
        TERABYTE+=(howmany(q,q.size()-1,i+1)-(flag))*qpow(i);
        IZANA:
        if(q[i]==num) {
            TERABYTE+=(howmany(q,i-1,0))+1;
        }
        else if(q[i]>num){
            TERABYTE+=(qpow(i));
        }
    }
    return TERABYTE;
}
signed main(void){
    while(1){
        n=read(),m=read();
        if((!n)&&(!m)) return 0;
        if(n>m) swap(n,m);
        for(register int i=0;i<9;i++){
            write(SATELLITE(m,i)-SATELLITE(n-1,i));
        }
        printf("%lld\n",(SATELLITE(m,9)-SATELLITE(n-1,9)));
    }
    puts("THE INTERNET ANGEL Be INVOKED 天使飞跃那无尽宇宙");
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

数位 dp 复健中。

我们发现对于每个数字 $0\sim 9$ 其实是互相独立。

那么就是 $10$ 个几乎相同子问题并列。只需要解决其中一个即可。

设 $f_{i,j,k}$ 表示处理前 $i$ 个数位，已经有 $j$ 个数位上的数与 $k$ 相等。

那么接下来枚举第 $i+1$ 个数位，如果前面的数位都“顶格”，这个数位只能枚举到限制，否则可以从 $0$ 枚举到 $9$。

如果 $k\not = 0$ 或者这个数位之前已经有非零的数位，那么当枚举出来的下一位和 $k$ 相同则 $j$ 可以加一，即 $f_{i,j,k}\gets f_{i,j,k}+f_{i+1,j+1,k}$。

反之，则这一位枚举对 $j$ 没有贡献。$f_{i,j,k}\gets f_{i+1,j,k}$。

这个过程中，我们需要记录前面是不是都“顶格”、前面有没有非零（也就是这一位会不会成为前导零）、及 $i,j,k$ 三个值。

接下来使用记忆化搜索实现就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
int f[15][15],lg[15];
int ret;
inline int dp(bool limit,bool lzero,int dep,int fl,int sum)
{
//	printf("%d %d %d %d %d\n",limit,lzero,dep,fl,sum);
	if(dep==0)
		return sum;
	if(!limit && !lzero && f[dep][sum]!=-1)return f[dep][sum];
	int ret=0,i,nxt=limit?lg[dep]:9;
	rep(i,0,nxt)ret+=dp(limit&&(i==lg[dep]),lzero&&(i==0),dep-1,fl,sum+(!(lzero&&(i==0))&&i==fl));//,printf("%d\n",i);//,printf("%d\n",ret);
	if(!limit && !lzero)f[dep][sum]=ret;
	return ret;
}
inline int solve(int v,int fl)
{int cnt,i,j;
	rep(i,0,12)rep(j,0,12)f[i][j]=-1;
	cnt=0;while(v)
	{
		lg[++cnt]=v%10;
		v/=10;
	}
	return dp(1,1,cnt,fl,0);
}
int main()
{int i,j,l,r;
//	printf("%d\n",solve(10,2));
	while(cin>>l>>r && (l||r))
	{if(l>r)swap(l,r);
		rep(i,0,8)printf("%d ",solve(r,i)-solve(l-1,i));
		printf("%d\n",solve(r,9)-solve(l-1,9));
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

一道模板题。

## 分析

**【总体思路】**

题目是让我们求在 $l$ 到 $r$ 中每个数字出现的次数，我们不妨将 $f[i][j][k]$ 定义为：在第 $i$ 位，前一个数字为 $j$，且目前已经出现了 $k$ 个指定数字时，最终的答案。不难发现，这是一种只能查找某一个指定数字在区间内出现的次数的数组。所以，我们在写记忆化搜索的时候，需要把 $0$ 到 $9$ 都找一遍。

**【记忆化搜索】**

首先，在搜索函数中，我们需要定义以下几个变量：目前寻找的是第几位；上一位选定的值； 是否有前导零； 能选择的数是否有上界； 目前找到的指定数字的数量； 指定数字的值。

函数如：
```
int dfs(int now,int last,bool if_z,bool if_l,int ans,int x)
```

其次，在特判一些情况时，我们直接套模板就行了，只需注意在最后一位时，我们返回的值是目前找到的指定数字的数量，而不是零或一。

最后，在枚举这一位选择的所有情况时，我们不仅要判断是否含有前导零，还要判断一下这一位目前选择的数是不是指定数字。

最终函数如下：

```cpp
int dfs(int now,int last,bool if_z,bool if_l,int ans,int x)
{
	if(!now) return ans;
	else
	{
		if(!if_z&&!if_l&&f[now][last][ans]!=-1) return f[now][last][ans];//已经找过了 
		else
		{
			int ans_s=0,up=if_l?a[now]:9;
			for(int i=0;i<=up;i++)
				if(if_z&&!i) ans_s+=dfs(now-1,i,1,if_l&&i==up,ans,x);//有前导零 
				else ans_s+=dfs(now-1,i,0,if_l&&i==up,ans+(i==x?1:0),x);//i=x，即这一位选定的正好是指定数字 
			return if_l?ans_s:(if_z?ans_s:f[now][last][ans]=ans_s);
		}
	}
}
```

**【主函数】**

在找每一位的时候，我们也是按照前缀和的思想进行寻找。注意的是，题目给定的 $l$ 和 $r$ 顺序不一定，我们需要判断一下谁是 $l$ 谁是 $r$。同时，在输出的时候，我们不能输出多余的空格，不然就会判错。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=15;
int a[N],f[N][N][N];
int l,r;
int dfs(int now,int last,bool if_z,bool if_l,int ans,int x)
{
	if(!now) return ans;
	else
	{
		if(!if_z&&!if_l&&f[now][last][ans]!=-1) return f[now][last][ans]; 
		else
		{
			int ans_s=0,up=if_l?a[now]:9;
			for(int i=0;i<=up;i++)
				if(if_z&&!i) ans_s+=dfs(now-1,i,1,if_l&&i==up,ans,x);
				else ans_s+=dfs(now-1,i,0,if_l&&i==up,ans+(i==x?1:0),x);
			return if_l?ans_s:(if_z?ans_s:f[now][last][ans]=ans_s);
		}
	}
}
int check(int x,int y)
{
	memset(f,-1,sizeof(f));
	int len=0;
	while(x) a[++len]=x%10,x/=10;
	return dfs(len,0,1,1,0,y);
}
signed main()
{
	while(cin>>l>>r&&l&&r)
	{
		if(l>r) swap(l,r);
		for(int i=0;i<=9;i++)
			cout<<check(r,i)-check(l-1,i)<<(i!=9?" ":"\n");		
	}
	return 0;
}
```


---

## 作者：sunkuangzheng (赞：0)

**【题目分析】**

从多倍经验看过来的，~~惊讶的发现可以水题解。~~

这道题是数位 dp 模板题之一，我们边看代码边讲。

首先确定总体思路：一次性统计出十个数字的出现频率较难，因此我们分开处理每一个数字的出现次数。

- 第一部分 搜索

采取搜索的方式，`pos` 代表搜到了哪一位，`numi` 代表这一次选定的数字（参数 `k`）出现的次数，`lim` 表示当前位是否有限制（$1$ 表示有限制），`pre` 表示当前位是否为前导零（$1$ 表示是）。

```cpp
int dfs(int pos,int numi,bool lim,bool pre,int k){
	if(pos == 1) return numi;
	int up = lim ? num[pos-1]:9;
	int ans = 0;
	for(int i = 0;i <= up;i ++){
		ans += dfs(pos-1,numi + (k == 0?(!pre && i == k):(i == k)),(lim && i == up),(pre && i == 0),k);
	}
	return ans;
}
```
`up` 的含义是**当前枚举位的最高限制**，是为了让枚举的数字不超过给定数字。

`numi + (k == 0?(!pre && i == k):(i == k))` 的意思是如果我们在统计 $0$ 的数量，那么如果是前导零计数器就不能增加；否则只要这一位与统计的数字相等，计数器自增。

`(lim && i == up)` 是指如果之前有限制，并且这一位还与上界相等，那么限制依然存在。为什么用与运算而不用或运算？举个例子，我们的枚举上限是 $114514$，目前枚举到的是 $1045$，此时虽然 $5$ 这一位相等，但是不论以后怎么枚举，我们枚举的数字一定小于 $114514$。

`(pre && i == 0)` 是指如果这一位是前导零，并且枚举的还是 $0$，那么前导零状态就要延续。

至此本题的重点——搜索部分就写完了。

但是纯暴力搜索复杂度是不优的，因此我们需要采用**记忆化搜索**。

- 第二部分 记忆化搜索

我们直接选取 `dfs` 函数的参数当作状态，设 `f[pos][numi][lim][pre]` 表示艘至第 `pos` 位，当前数字出现了 `numi` 次，限制和前导零状态分别为 `lim` 和 `pre` 时的答案，初始化为 `-1`。在搜索函数中添加判断语句，如果当前状态下 $f \ne -1$，则直接返回该值。每次搜索完毕后，将答案赋给 $f$ 数组。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int f[15][15][2][2],num[15],n,l,r;
int dfs(int pos,int numi,bool lim,bool pre,int k){
	if(f[pos][numi][lim][pre] != -1) return f[pos][numi][lim][pre];
	if(pos == 1) return numi;
	int up = lim ? num[pos-1]:9;
	int ans = 0;
	for(int i = 0;i <= up;i ++){
		ans += dfs(pos-1,numi + (k == 0?(!pre && i == k):(i == k)),(lim && i == up),(pre && i == 0),k);
	}
	return f[pos][numi][lim][pre] = ans;
}
int work(int x,int k){
	memset(f,-1,sizeof(f));
	int u = 0;
	while(x){
		num[++u] = x % 10;
		x /= 10;
	}
	n = u;
	return dfs(n+1,0,1,1,k);
}

```

输出时，枚举 $0\sim 9$ 的数字，每一次询问运用前缀和思想，输出 `work(r)-work(l-1)` 即可。



---

## 作者：Endt (赞：0)

# The Counting Problem-题解
##### 考察算法：数位 DP
### 题意
计算给定范围内 $0\sim9$ 出现的次数。
### 分析
数据范围很大，且与位上的数有关，考虑数位 DP。
#### 状态定义
$dp_{i,j,k}$ 表示小于 $i$ 位的数中 $j$ 的出现次数，有前导 $0$（$k=0$）/ 没有前导零（$k=1$)。
#### 状态转移
枚举 $i$ 和 $j$，如果 $j\not=0$，在 $i-1$ 位的数前面加一个 $0$ 就有前导 $0$ 了，不增加 $j$ 的数量，$dp_{i,j,0}=dp_{i-1,j,0}+dp_{i-1,j,1}$；在 $i-1$ 位的数前面加 $1\sim9$ 就没有前导零，同时如果加的是 $j$ 还会多出 $10^{i-1}$ 个 $j$，$dp_{i,j,1}=9(dp_{i-1,j,0}+dp_{i-1,j,1})+10^{i-1}$。$j=0$ 同理分析，$dp_{i,0,0}=dp_{i-1,0,1}+dp_{i-1,0,0}+10^{i-1}$，$dp_{i,0,1}=9(dp_{i-1,0,1}+dp_{i-1,0,0})$。
### 计算
先算小于 $a$ 的答案，再算小于等于 $b$ 的答案，用后者减前者。
### 代码
```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Tem  template
#define  Pub  public:
#define  Pri  private:
#define  Pro  protact:

#define  Max(a,b)  ((a)>(b)?(a):(b))
#define  Min(a,b)  ((a)<(b)?(a):(b))
#define  Abs(a)  ((a)>0?(a):-(a))

int dp[10][10][2];

std::vector<int> solve(int a){
    int numa[10]={},w=0;
    std::vector<int> A(10);
    while(a)numa[++w]=a%10,a/=10;
    
    for(int i=0;i<w;++i){
        for(int j=0;j<=9;++j){
            A[j]+=dp[i][j][1];
        }
    }
    for(int i=1;i<numa[w];++i){
        for(int j=0;j<=9;++j){
            A[j]+=dp[w-1][j][0]+dp[w-1][j][1];
        }
        A[i]+=pow(10,w-1);
    }
    for(int i=w-1;i>=1;--i){
        for(int j=0;j<numa[i];++j){
            for(int k=0;k<=9;++k){
                A[k]+=dp[i-1][k][0]+dp[i-1][k][1];
            }
            for(int k=w;k>i;--k)A[numa[k]]+=pow(10,i-1);
            A[j]+=pow(10,i-1);
        }
    }
    return A;
}

int main(){
    for(int i=1;i<=9;++i){
        for(int k=1;k<=9;++k){
            dp[i][k][1]=dp[i-1][k][0]*9+dp[i-1][k][1]*9+pow(10,i-1);
            dp[i][k][0]=dp[i-1][k][0]+dp[i-1][k][1];
        }
        dp[i][0][1]=dp[i-1][0][1]*9+dp[i-1][0][0]*9;
        dp[i][0][0]=dp[i-1][0][1]+dp[i-1][0][0]+pow(10,i-1);
    }
    
    for(int a,b;scanf("%d%d",&a,&b);){
        if(a+b==0)break;
        if(a>b)std::swap(a,b);
        std::vector<int> A=solve(a),B=solve(b+1);
        for(int i=0;i<=9;++i){
            printf("%d",B[i]-A[i]);
            putchar(i<9?' ':'\n');
        }
    }
    
    return 0;
}
```

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/UVA1640)

## 题意

统计正整数 $a\sim b$ 中 $0\sim9$ 每个数码出现的次数。

## 分析

其实就是计算两次 $1\sim x$ 中每个数码 $num$ 出现的次数，前缀和相减就是答案。

我们设 $\text{ask}(x,num)$ 表示 $1\sim x$ 中数码 $num$ 出现的次数，先把数 $x$ 按位拆分，设共有 $n$ 位，个位到第 $n$ 位分别存在 $a_{1\sim n}$ 中，为了方便后面的计算，再求出 $b_i$ 表示 $x$ 的第 $i$ 位到个位组成的数。

然后开始求答案 $ans$，众所周知，$0$ 比较特殊，于是我们把 $0$ 单独提出来处理，先解决当 $num=1\sim9$ 时怎么做。

设 $\text{dfs}(p,num)$ 表示 $x$ 的第 $p$ 位之前全部填 $a_{p+1\sim n}$ 时第 $1\sim p$ 位的可能的数码 $num$ 的个数，特别的，当 $p=n$ 时，也认为有一个虚拟的第 $n+1$ 位填了最大的限制。

因此当 $num=1\sim 9$ 时，$\text{ask}(x,num)$ 为 $\text{dfs}(n,num)$。

然后写 $\text{dfs}(p,num)$。我们把统计第 $1\sim p$ 位分成第 $p$ 位和第 $1\sim p-1$ 位来算：

- 求第 $p$ 位填 $num$ 时的数的个数：若 $num<a_p$，这一位填 $num$ 时前面的位已经固定，后面的则可以为 $0\sim 10^{p-1}-1$ 共 $10^{p-1}$ 种数；若 $num=a_p$，则 $p\sim n$ 位都填了最大值，剩下的位可以填 $b_{p-1}+1$ 种数；若 $num>a_p$，则不可能填。

- 求第 $1\sim p-1$ 位填 $num$ 时的数的个数：若第 $p$ 位填 $a_p$，则后面的位子填的 $num$ 的个数就是 $\text{dfs}(p-1,num)$；若第 $p$ 位填 $0\sim a_p-1$，则此时后面的填法时没有限制的，设 $dp_{i,j}$ 表示 $0\sim 10^i-1$ 中的所有数的数码 $j$ 的个数的总和，则答案为 $dp_{p-1,num}\times a_p$。

对于 $num=0$ 的情况，最高位不能填 $num$，只要求出第 $n$ 位填 $1\sim a_n$ 时的答案和所有 $1\sim n-1$ 位数中 $num$ 的个数再相加就是答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=10;
ll dp[N][N],m10[N]={1},a[N],b[N];
ll dfs(int p,int num){
	if(p==0)
		return 0;
	ll ans=0;
	if(num<a[p])
		ans+=m10[p-1];
	else if(num==a[p])
		ans+=b[p-1]+1;
	ans+=dp[p-1][num]*a[p];
	ans+=dfs(p-1,num);
	return ans;
}
ll ask(ll x,int num){
	if(x<10)
		return num<=x;
	int n=0;
	while(x){
		a[++n]=x%10;
		x/=10;
		b[n]=a[n]*m10[n-1]+b[n-1];
	}
	ll ans=0;
	if(num==0){
		ans=dp[n-1][num]*(a[n]-1);
		ans+=dfs(n-1,num);
		ans+=ask(m10[n-1]-1,num);
	}
	else
		ans=dfs(n,num);
	return ans;
}
int main(){
	for(int i=0;i<=9;i++)
		dp[1][i]=1;
	for(int i=1;i<=9;i++)
		m10[i]=m10[i-1]*10;
	for(int i=2;i<=9;i++)
		for(int j=0;j<=9;j++)
			dp[i][j]=m10[i-1]+dp[i-1][j]*10;
	ll x,y;
	while(cin>>x>>y&&x&&y){
		if(x<y)
			swap(x,y);
		for(int i=0;i<9;i++)
			cout<<ask(x,i)-ask(y-1,i)<<" ";
		cout<<ask(x,9)-ask(y-1,9)<<endl;
	}
	return 0;
}
```

**注意输出不能多行末空格。**

---

## 作者：dingshengyang (赞：0)



下面是 AT1483 我的题解。这两题大体相同，不同的地方我会说明。

---

其实……这道题……就是数位 DP 板子题之一（求区间内某一数码（所有数码）出现的个数，板子题：P2602。）

---

好，开始。定义数组 $f_{i,j,k}$ 为前 $i$ 位，这一位填的 $j$，$k$ 出现了几次。

- 状态边界：第 $1$ 位，填的 $i$，那么除了 $i$ 填了一次之后，其他都是 $0$。因此 $f_{1,i,i}=1$。

- 状态转移：上一位填的什么鬼数都可以：$f_{i,j,k} = \sum^{9}_{t=0} f_{i-1,t,k}$。但是，注意 $f_{i,j,j}$ 需要特判，加上 $10^{i-1}$。因为如果现在填 $12$（求 $f_{2,2,2}$），填了个 $2$，转移到 $f_{1,t,2}=1(t=2)$ 和 $f_{1,t,2}=0(t\not = 2)$，但是只管了 $2$，$12,22,32,42,...,92$，你不去管他了？当然要加上。

+ dp 过程：先分解数位，用 `vector<int>`存下来。倒着枚举。在当前位以下的，都是整块的，直接加上。同时，之前高位可能也有 $1$，那么还需要加上 $10^{i-1}$，但是因为数组下标从 $0$ 开始，就不用减一了。如果已经是最后一位（$i=0$），那么查一下自己的数位，有 $1$ 就加上。我们之前讨论的都是 $10^{\lfloor \log_{10}^{x} \rfloor}$ 及其以上的。那么之前的直接加上。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL f[40][10][10];
void init(){
	for(int i = 0;i <= 9;i ++)f[1][i][i] = 1;//状态边界
	for(int i = 2;i <= 13;i ++){
		for(int j = 0;j <= 9;j ++){
			for(int k = 0;k <= 9;k ++){
				for(int t = 0;t <= 9;t ++){
					f[i][j][k] += f[i-1][t][k];//状态转移
				}
			}
			f[i][j][j] += pow(10,i-1);//特殊判断
		}
	}
}
LL dp(LL n,LL k){//1 到 n 当中，k 出现了多少次。
	vector<int> nums;
	while(n) nums.push_back(n%10),n/=10;//分解数位
	LL res = 0;//答案
	for(int i = nums.size()-1;i >= 0;i --){
		if(nums[i]){
			for(int j = (i == nums.size()-1);j < nums[i];j ++)res += f[i+1][j][k];//整块加上
			for(int j = nums.size()-1;j > i;j --){
				if(nums[j] == k)res += pow(10,i)*nums[i];//遍历高位
			} 
		}
		if(i == 0){//检查自己
			for(int j = 0;j < nums.size();j ++){
				res += nums[j] == k;
			}
		}
	}
	for(int i = nums.size()-1;i >= 1;i --){//不足 10 的那几次幂，直接加上。
		for(int j = 1;j <= 9;j ++){
			res += f[i][j][k];
		}
	}
	return res;
}
int main(){
	init();
	LL l = 1,r;
	cin>> r;
	cout << dp(r,1) - dp(l-1,1) << endl;
	return 0;
}

```

这题复杂一点。第一，如果 $l > r$，则应该交换两者；
第二，结尾不能有多余空格。

就这样吧，主函数代码如下：

```cpp
int main(){
	init();
	LL l,r;
	while(1){
	    cin >> l >> r;
	    if(l == r && r == 0)break;
	    if(l > r)swap(l,r);
	    for(int i = 0;i < 9;i ++){
		    cout << dp(r,i)-dp(l-1,i) << " ";
	    }
	    cout << dp(r,9) -dp(l-1,9) << endl;
	}
	return 0;
}
```

---

