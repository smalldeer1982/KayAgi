# [USACO13NOV] Farmer John has no Large Brown Cow S

## 题目描述

Farmer John likes to collect as many different types of cows as possible. In fact, he has collected almost every conceivable type of cow, except for a few, written on a short list of N lines (1 <= N <= 100).  The list looks like this:

Farmer John has no large brown noisy cow.

Farmer John has no small white silent cow.

Farmer John has no large spotted noisy cow.

Each item in the list describes a missing cow in terms of a short list of adjectives, and each item contains the same number of adjectives (3, in this case).  The number of adjectives per line will be in the range 2..30.

Farmer John has a cow fitting every other possible adjective combination not on his list.  In this example, the first adjective can be large or small, the second can be brown, white, or spotted, and the third can be noisy or silent.  This gives 2 x 3 x 2 = 12 different combinations, and Farmer John has a cow fitting each one, except for those specifically mentioned on his list.  In this example, a large, white, noisy cow is one of his 9 cows.  Farmer John is certain that he has at most 1,000,000,000 cows.

If Farmer John lists his cows in alphabetical order, what is the Kth cow in this list?

Partial credit opportunities: In the 10 test cases for this problem, cases 1..4 involve at most two adjectives per line in Farmer John's list.  In cases 1..6, each adjective will have exactly two possible settings (in all other cases, each adjective will have between 1 and N possible settings).

FJ喜欢收集不同的奶牛，他将未有的N(1 <= N <= 100)头奶牛用如下的形式描述：


Farmer John has no large brown noisy cow.


Farmer John has no small white silent cow.


Farmer John has no large spotted noisy cow.


每一行，描述一头FJ未有的牛。


每一行都含有相同个数的形容词，每行的形容词个数范围为2..30。


在以上给出的列表中，每行共有3个形容词，第一个形容词有两种（large和small），第二个形容词有3种（brown,white和spotted），第三个形容词有2种（noisy和silent）。


所以共可以组成12头不同的奶牛，除了列表给出的3头，他已经拥有了其他9头。FJ最多有1,000,000,000头牛。


若将FJ已经拥有的牛按形容词的字典序排序，请问他已有的第K头牛是哪一头。


## 说明/提示

The input matches the sample given in the problem statement above.  Farmer John would like to know the 7th cow on his farm, when listed in alphabetical order.


Farmer john has cows matching the following descriptions, listed in alphabetical order:

large brown silent

large spotted silent

large white noisy

large white silent

small brown noisy

small brown silent

small spotted noisy

small spotted silent

small white noisy

The 7th cow in this list is described as "small spotted noisy".


## 样例 #1

### 输入

```
3 7 
Farmer John has no large brown noisy cow. 
Farmer John has no small white silent cow. 
Farmer John has no large spotted noisy cow. 
```

### 输出

```
small spotted noisy 
```

# 题解

## 作者：红黑树 (赞：6)

## 题意
有 $L$ 类属性，给定 $N$ 只奶牛在每类属性的取值，令每类属性出现过的值就是该类属性的取值集合。求每类属性所
有可能的取值组合中，按字典序排序后，没有出现在这 $N$ 只奶牛列表里的第 $K$ 个取值组合是什么。
## 思路
每类属性实际上就是进制中的一位，所有属性构成一个混合进制。

首先我们要求出每一位的进率，和每只奶牛在每一位上对应的值，可以对每⼀类属性的值排序，然后去重，按顺序
从 $0$ 开始编号。也可以更加粗暴的先判断每个值是否第一次出现，然后对每个值统计比它小的第一次出现的值的个数，就得到了每个值对应的编号，最大的编号 $+1$ 就是该位的进率。

然后就可以将每只奶牛对应的混合进制数转换成最小单位数量，排序后这些数将数轴分成 $N + 1$ 个区间，我们按顺序处理每个区间，就能找到第 $K$ 个数对应的数值。
最后我们再将数值转换回混合进制，输出每位上的数对应的属性，就是答案。
## 复杂度
令属性类的数量为 $L$。
### 时间
属性值总数 $\mathcal O(NL)$。
* 判断每个属性是否首次出现 $\mathcal O(N)$，注意常数为属性⻓度 $10$。
* 计算属性对应的数值 $\mathcal O(N)$，注意常数为属性⻓度 $10$。
* 计算进制转换对应的值 $\mathcal O(1)$。

奶牛对应的十进制数排序 $\mathcal O(n \log n)$。

寻找第 $K$ 个数 $\mathcal O(N)$。

转换回混合进制 $\mathcal O(L)$。

总时间复杂度为 $\mathcal O(N^2L)$。
### 空间
记录属性 $\mathcal O(NL)$，注意常数为属性长度 $10$。
## 代码
```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 102, kMaxL = 31;

struct P {          // 属性种类
  int r, w;         // 位权、进率
  string s[kMaxN];  // 位上的数对应的属性值
} p[kMaxL];
string s[kMaxN][kMaxL], str;
int b[kMaxN][kMaxL], v[kMaxN], n, k, l, x;

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> str >> str >> str >> str;
    for (l = 0;; l++) {  // 读入属性
      cin >> str;
      if (str == "cow.") {  // 属性结束
        break;
      }
      s[i][l] = str, b[i][l] = 1;       // 记录属性、初始化首次出现标记
      for (int j = 1; j < i; j++) {     // 枚举之前的同类属性
        b[i][l] &= s[j][l] != s[i][l];  // 判重标记是否首次出现
      }
    }
  }
  for (int k = l - 1; k >= 0; k--) {                    // 权重由低到高枚举属性类型
    p[k].w = k == l - 1 ? 1 : p[k + 1].w * p[k + 1].r;  // 计算当前属性的位权
    for (int i = 1; i <= n; i++) {                      // 枚举每只奶牛
      int c = 0;                                        // 初始化位上的值
      for (int j = 1; j <= n; j++) {                    // 枚举其他奶牛
        c += b[j][k] && s[j][k] < s[i][k];              // 计算较小同类属性数量
      }
      p[k].r = max(p[k].r, c + 1);  // 更新进率
      p[k].s[c] = s[i][k];          // 记录值对应的属性
      v[i] += c * p[k].w;           // 累加位对应的值
    }
  }
  sort(v + 1, v + 1 + n);             // 将拥有的奶牛按值排序
  v[0] = -1, v[n + 1] = 1e9 + 1;      // 初始化边界
  for (int i = 1; i <= n + 1; i++) {  // 枚举缝隙寻找第k只
    if (k <= v[i] - v[i - 1] - 1) {   // 在当前缝隙中
      x = v[i - 1] + k;
      break;
    } else {
      k -= v[i] - v[i - 1] - 1;  // 减去当前缝隙长度
    }
  }
  for (int i = 0; i < l; i++) {   // 值转混合进制
    int y = x / p[i].w % p[i].r;  // 计算位上的值
    cout << (i ? " " : "") << p[i].s[y];
  }
  return 0;
}
```

---

## 作者：tzyt (赞：5)

update：2022/4/17 更正了博客地址

[题目链接](https://www.luogu.com.cn/problem/P3087)

[博客中观看体验更好](https://ttzytt.com/2021/09/P3087/)

前言：这篇题解写的可能比较啰嗦，主要时是因为我把所有思考的过程都写下来了，所以如果你已经有了基本的思路，或者是希望找一篇简洁的题解，就可以跳过这篇题解了。

# 1：理解题意

总共有 $cow$ 头牛，$type$ 类形容词，有 $num_i$ 个第 $i$ 类形容词，第 $i$ 类的第 $j$ 种形容词是 $adj_{i,j}$ ，每头牛都需要有这 $type$ 类形容词按照顺序来修饰。现在告诉你要删除这 $cow$ 头牛中的 $n$ 头，问你在这剩下的 $cow-n$ 头牛中，按照字典序排序，排在第 $k$ 位的牛是哪一头?

# 2：分析和转化问题

## 2.1：和数字系统的关联
单看这样的描述可能有些抽象，现在我们来看一下样例是怎么样的，再在样例的基础上思考应该怎么解决这道题。

在样例中 $n=3$，$k = 7$。$adj_{i,j}$的值如下

| $adj_{i,j}$           | $j=1$   | $j=2$    | $j=3$     |
| :-------------------- | :------ | :------- | :-------- |
| $i=1$（第一类形容词） | "large" | "small"  | N/A       |
| $i=2$（第二类形容词） | "brown" | "white"  | "spotted" |
| $i=3$（第三类形容词） | "noisy" | "silent" | N/A       |

因为样例中让我们求的是按照字典序排在第7的牛，我们可以思考一下以字典序为关键字进行排序的过程是什么样的。

举个例子：有两个字符串"abc"和字符串"cde"需要进行字典序排序，首先我们应该比较在第一位的字符"a"和"c"的字典序，再比较第二位"b"和"c"的字典序，最后才是第三位的字符。

从这个过程中我们可以发现每一位字符对于字符串整体字典序的影响是不一样的，其中第一位的影响最大，最后一位最小。因此我们就可以说他们对于整个字符串的字典序的影响的“权值”不同。如果我们按照字典序给不同的字符串从小到大排序，对于一个字符串，不管从第二个字符到最后一个字符的字典序有多小，如果第一个字符的字典序很大，那么它也会排在很后面

再观察这道题目中让我们求解的问题，我们可以发现，第1类形容词比如"large"对于整串字符的影响是最大的，其次是第二类，比如"brown"，最后才是第三类。

分析到这里，相信你已经体会到这个问题和数字系统的相关性了。

那就是我们在比较数字时，采用的方法也是从高位到低位进行比较

比如有这样一个 $10$ 进制数字 $(123456789)_{10}$

数字 $1$ 代表的值是 $100000000$ 它代表的值是所有数字中最大的（1是第一位）

数字 $2$ 代表的值是 $20000000$  它代表的值是第二大的（2是第二位）

数字 $x$ 在第 $i$ 位代表的值就是 $10^{i-1}\times x$，整个 $10$ 进制数代表的值就每一位数字代表的值的累加

把整个规则推广到 $k$ 进制，那么数字 $x$ 在第 $i$ 位代表的值就是 $k^{i-1}\times x$

## 2.2：解决简化过的问题

那么问题就来了，不管是我们刚刚讨论的 $10$ 进制还是 $k$ 进制，它们的机制都是 “逢 $k$ 就进 $1$”，因此第 $i+1$ 位的 “数字 $1$” 在十进制中代表的值一定是第 $i$ 位的 “数字 $1$” 代表的值的 $k$ 倍。而在我们这个问题中，每一类形容词的数量是不一定的。

我们可以先尝试解决每类形容词数量一定的情况，设每类形容词的数量都是 $k$ ，首先我们要对每类形容词进行字典序排序，把结果存在 `rank[i][j]`中，其中 $i$ 代表形容词类型，$j$ 代表排名。

这一步的目的是把字符串转化成数字，方便后续的计算。（把每个形容词映射到数字系统中的 “第 $i$ 位的数字 $j$ ”，但是需要注意的一点是，形容词的类数越小，对整体字典序影响越大，数字的位数越小，对整体的值的影响越小）

因为我们已经完成了形容词到数字的映射，所以下面要做的就等于“把 $10$ 进制转换到 $k$ 进制”，再把得到的数字转换回对应的字符串

这样的例子可能有些抽象，下面我们来模拟一遍这个过程

我们规定第一类形容词有以下两个 {"a","b"}, 第二类形容词也有以下两个{"c","d"}, 第三类是{"e","f"}。

那么我们可以求出以下的`rank`数组

（因为方便计算，所以排名从0开始）

| $rank_{i,j}$          | $j=0$ | $j=1$ |
| :-------------------- | :---- | :---- |
| $i=1$（第一类形容词） | "a"   | "b"   |
| $i=2$（第二类形容词） | "c"   | "d"   |
| $i=3$（第三类形容词） | "e"   | "f"   |

如果我们想求字典序排在第 $3$ 位的牛，那么我们需要先求出 $3$ 的二进制数，也就是 $(011)_2$。然后把这个数字倒过来，变成 $(110)_{2反}$（形容词的类数越小，对整体字典序影响越大，数字的位数越小，对整体的值的影响越小），最后再把 $(110)_{2反}$ 映射回对应的字符串（第几位对应第几类），最后的答案也就是 "a, d, f"

## 2.3：解决原问题
在解决刚刚简化过的问题的过程中，我们把每类形容词的类映射到了数字系统的 “第几位数”，把它们的排名 $j$ 映射到了数字系统中的数字 $j$，而每类形容词的数量就成了这个数字系统的进制数。

我们可以发现，解决原问题的关键就在于进制，在刚刚简化过的问题中，数字系统中每一位的进制是一样的，并且每一类形容词的数量也是一定的，那么再解决当前问题时，每一类的形容词数量是不一定的，所以相应的，每一位的进制也要有所改变。

回到题目给的样例，每类形容词的数量是 $num_1 = 2$, $num_2 = 3$, $num_3 = 2$ 

而第三类的形容词被我们映射到了数字系统中的第一位数字，第二类是第二位，同样的，第一类就是第三位

因此我们可以规定，在第一位的时候，这个数字系统是二进制的，在第二位的时候，这个数字系统是三进制的，第三位也是二进制。

虽然我们可以做到用这样的 "$2,3,2$" 进制来描述每一种牛，但是在解决这道题的时候，我们还需要把十进制转换成这样的 "$2,3,2$" 进制。

大家肯定对十进制转二进制这样的问题非常熟悉，比如要把一个十进制数 $a$ 转换成 $x$ 位的二进制数 $b$ ，要做的就是从 $b$ 的最高位 $x$ 开始，每次都进行 $\lfloor a \div （b的这一位在十进制中代表的值） \rfloor$ 的操作，然后再计算 $a = a \bmod （b的这一位在十进制中代表的值）$

写成程序的话，就是这样的
~~~cpp
    //k是十进制数
    //weight_in_pos[i]是第i位（从最高位开始计，和我们平常用的方法相反）在十进制中代表的值
    //i是当前位（从最高位开始计，和我们平常用的方法相反）
    for (int i = 1; i <= adj_num; i++)
    {
        cout << adj_by_pos[i][(k) / weight_in_pos[i]] << " ";
        k %= weight_in_pos[i];
    }
~~~

所以呢，对于 "$2,3,2$" 这样的进制，我们只需要提前计算好他们每一位在十进制中代表的值就可以把十进制转换成这样的进制了。

（每一位在十进制中代表的值的意思就是 在原进制系统中，如果这一位是 $1$ ，其他位都是 $0$ ，转换成 $10$ 进制之后的值）

那么这样的进制的每一位在十进制中代表的值如何计算呢？

不管是在几进制的系统里，只要两个数的进制系统相同，那么一个 位数更多的数 所代表的值一定比位数更少的那个要大。

所以我们可以这样计算第 $i$ 位在十进制中所代表的值，就是第 $i-1$ 位数字在十进制中代表的值再乘上第 $i-1$ 位上能表示的最大的数字 $+ 1$（确保位数更多的数一定比位数更少的大），并且我们可以发现最大的数字 $+ 1$ 刚好就是这一位的进制。（比如 $2$ 进制最大的数是 $1$ ）

有了这个结论就可以递推的求解每一位在十进制中代表的值，我们可以把答案存在 `weight_in_pos[i]` 数组中（第 $i$ 位代表的值），并且把第一位代表的值初始化为 $1$

在样例的 "$2,3,2$" 进制中，第一位在十进制中代表的值被初始化为 $1$，第二位的 weight_in_pos 值就是 $1\times 2 = 2$，第三位就是 $2\times 3 = 6$，

至此，我们已经能计算出所有牛中排在第 $k$ 个的牛了，但是题目问的是在这剩下的 $cow-n$ 头牛中，按照字典序排序，排在第 $k$ 位的牛是哪一头。

这个小问题的求解就比较简单了，我们可以把 $k$ 转化成在所有牛中的排名，而不是剩下的牛的排名，我们可以先计算出要删除的那 $n$ 头牛在所有牛中的排名，如果这 $n$ 头牛中有牛的排名比 $k$ 小，或是等于 $k$ ，那么就需要把 $k$ 加 $1$。（相当于排名前 $k$ 的这些牛中有一些是不能选取的，而我们要选出 $k$ 头，所以要加上删去的 $n$ 头牛中排名比 $k$ 小的）

# 代码和细节
细节都有注释
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, k;
int adj_num = 0;
vector<string> str[105];          //str[i]表示用于修饰第i头牛的形容词
vector<string> adj_by_pos[35];    //adj_by_pos[i]表示所有在位置i出现的形容词
set<string> is_appear[35];        //is_appear[i]用于判断在位置i上，某个形容词是否出现
int weight_in_pos[35];            //每一位代表的值（按照字典序排在第几）
map<string, int> rank_in_pos[35]; //rank_in_pos[i][j]代表在位置i上，字符串j按照字典序排序，排在第几
int cow_rank[105];                //fj没有的牛的排名
bool debug = false;               //调试开关，可以打开去体会一下解题的过程
void mapping()                    //对每类形容词进行字典序排序，把结果存在 rank[i][j]中，其中 i 代表形容词类型，j 代表排名
{                                 //注意这里的排名从0开始（这是把单词映射到数字上，数字是从0开始的）
    for (int i = 1; i <= adj_num; i++)
    {
        int rank = 0;
        for (auto j : adj_by_pos[i]) //c++11的新特性，意思是用j遍历所有adj_by_pos[i]的元素
        {
            rank_in_pos[i][j] = rank;
            if (debug)
                cout << j << " rank = " << rank << " i = " << i << endl;
            rank++;
        }
    }
}

int get_pos(int cow_id)
{
    int ans = 0;
    for (int i = 1; i <= adj_num; i++)
    {
        ans += weight_in_pos[i] * (rank_in_pos[i][str[cow_id][i - 1]]);
    }
    return ans + 1; //答案可能是0，但是排位应该从1开始
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> k;
    string temp_str;
    for (int i = 1; i <= n; i++)
    {
        cin >> temp_str;
        while (temp_str != "no")
        {
            cin >> temp_str;
        }
        int adj_pos = 1;

        while (1)
        {
            cin >> temp_str;
            if (temp_str == "cow.")
            {
                break;
            }
            str[i].push_back(temp_str);
            if (!is_appear[adj_pos].count(temp_str)) //还没有出现过，这里是去重操作
            {
                adj_by_pos[adj_pos].push_back(temp_str);
                is_appear[adj_pos].insert(temp_str);
            }
            if (i == 1)
            {
                adj_num++; //计算形容词的种类数
            }
            adj_pos++;
        }
    }
    for (int i = 1; i <= adj_num; i++)
    {
        sort(adj_by_pos[i].begin(), adj_by_pos[i].end()); //对每个类型的形容词进行排序
    }

    weight_in_pos[adj_num + 1] = 1;            //第一位代表的数字应该是1
    adj_by_pos[adj_num + 1].push_back("temp"); //1和1相乘是1，所以要push一个元素进去，这样子size就是1

    for (int i = adj_num; i >= 1; i--) //计算每一位在十进制中代表的值（这里的位的计算方法和平时的方法是反的）
    {                                  //这是因为本题中的形容词类型和数字系统的 “位” 是相反的
        if (debug)
            cout << "i" << i << endl;
        weight_in_pos[i] = weight_in_pos[i + 1] * adj_by_pos[i + 1].size();
    }
    mapping();
    for (int i = 1; i <= n; i++)
    {
        cow_rank[i] = get_pos(i); //计算出要删除的n头牛的整体排名
        if (debug)
            cout << "cowrkw " << i << " = " << cow_rank[i] << endl;
    }
    sort(cow_rank + 1, cow_rank + n + 1); //按照每种牛的排名进行排序
    for (int i = 1; i <= n; i++)
    {
        if (cow_rank[i] <= k)
        {
            k++;
        }
        else
        {
            break;
        }
    }
    k--; //k原本代表的是排在第几的牛，但是我们已经把牛的排名转化成数字了，
        //排名最小的牛的数字是0而不是1，所以这里要减1
    if (debug)
        cout << "new k" << k << endl;
    for (int i = 1; i <= adj_num; i++)
    {
        cout << adj_by_pos[i][(k) / weight_in_pos[i]] << " ";
        if (debug)
            cout << "i " << i << " (k) / weight_in_pos[i] " << (k) / weight_in_pos[i] << endl;
        k %= weight_in_pos[i];
    }
    system("pause");
}
```

题解就到这里了，如果你发现题解有问题，或是有看不懂的地方，都欢迎私信我或者是在评论区里讲，如果你觉得对你有帮助就点个赞吧，谢谢。

---

## 作者：CR_Raphael (赞：4)

感觉这是一道代码题

组合计数+乱搞

把原题中单词变为进制即可

注意：FJ没有的牛不算在数量内（我是把他已有的第K头牛变成所有牛中的第P头牛，但是代码里一律用的是P，请见谅）

```c++
#include<iostream>
#include<cstdio>
#include<map>
#include<algorithm>
#include<cmath>
#define elc every_lost_cow
using namespace std;

const int maxp=35;
const int maxn=105;
int every_lost_cow[maxn];
int n, p, adj, k[maxp], w[maxp];
string s[maxp][maxn];
string c[maxn][maxp];

int findd(int x, string y) {
	int j;
	for(j=1; j <= k[x]; j++){
		if(s[x][j]==y)return j;
	}
	return 0;	
}

int tmp(string a, string b) {
	int i;
	
	for(i=0; i < min(a.size(),b.size()); i++) {
		if(a[i] != b[i])return a[i] < b[i];
	}
	
	return a.size() < b.size();
}

int turn(int x) {
	int t=0,i;
	
	for(i=1; i <= adj; i++) {
		t=t+ w[i]*(findd(i,c[x][i])-1);
	}
	
	return t+1;
}

int main() {
	cin>>n>>p;
	
	int ti, i, j;
	string t;
	
	for(i=1; i <= n; i++) {
		ti=0;
		
		cin>>t;
		while(t != "no")
			cin>>t;
		
		ti++;
		cin>>c[i][ti];
		while(c[i][ti] != "cow.") {
			if(!findd(ti, c[i][ti])) {
				k[ti]++;
				s[ti][k[ti]]=c[i][ti];
			}
			ti++;
			cin>>c[i][ti];
		}
		
		adj=ti-1;
	}
	
	for(i=1; i <= adj; i++){
		sort(s[i]+1,s[i]+1+k[i],tmp);
	}
	
	w[adj+1]=1;
	k[adj+1]=1;
	for(i=adj; i >= 1; i--)
		w[i]=w[i+1]*k[i+1];
	
//for(i=1; i <= n; i++) {
//	for(int j=1; j <= k[i]; j++)
//		cout<<s[i][j]<<' ';
//	cout<<endl;
//}
	
	for(i=1; i <= n; i++) 
		elc[i]=turn(i);
	
	sort(elc+1,elc+1+n);
	
	for(i=1; i <= n; i++) {
		if(elc[i] <= p) p++;
		else break;
	}
	
//cout<<p<<endl;
	
	p--;
	for(i=1; i <= adj; i++) {
		ti=p/w[i]+1;
		cout<<s[i][ti]<<' ';
		p=p%w[i];
	}
	
	return 0;
}
```

---

## 作者：zzxLLL (赞：3)

正解像是康托展开之类的？但是蒟蒻不会，所以用了一堆 STL。

---

对于每一列的字符串，按照字典序给它们编号。这样每一行的形容词串就变成了一堆数字。

设共有 $s$ 列，第 $i$ 列共有 $b_i$ 个不同的形容词，那么实际上每一行就是一个“第 $i$ 位是 $b_i$ 进制”的数。设第 $j$ 行的第 $k$ 个形容词再该列的排名为 $a_{j,k}$，然后这一行的形容词就可以用数字 $\sum\limits_{k=1}^{s}(a_{j,k} \times \prod\limits_{p=k+1}^{s}b_p)$ 表示。

例如样例，``large brown noisy``转化为``0 0 0``，``small white silent``转化为``1 2 1``。然后按照进制转化的方法，前者转化为 $0$，后者转化为 $1 \times 6 + 2 \times 2 + 1 \times 1 = 11$。

然后对于每一行的形容词都可以转化为一个数字，我们将这些数字称为“关键数字”。将关键数字排序后得到数组 $key$。我们要求的其实是第 $k$ 个"非关键数字"，而“非关键数字”个数是 $O(\prod b_i)$ 级别的，直接枚举妥妥的 T 飞。而“关键数字”只有 100 个，所以考虑计算答案在哪两个“关键数字”之间。

这个是简单的。从小到大找区间 $(key_i , key_{i+1})$，若 $k \leq key_{i+1} - key_i$ 说明答案为 $ans = key_i + k - 1$，直接输出 $ans$ 对应的形容词串即可。否则 $k \gets k-(key_{i+1}-key_i)$，然后进入下一个区间。

---

具体的复杂度懒得算了。这题的数据范围极小，$n \leq 100$，形容词个数 $\leq 30$，所以不论怎么玩 STL 都炸不了。事实上最大点仅 4ms。

我的代码里面使用了大量的 STL，而且还是修修补补才写出来的。做这种毒瘤前还是先思考完整再写，不然不知道写出来一坨什么玩意（

```cpp
#include<map>
#include<set>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

int n,k,sz;
map<string,int>adj[110];	// 每一列形容词的编号
map<int,string>rev[110];	// adj[rev[S]] = S
set<string>qwq[110];		// 每一列形容词
vector<string>awa[110];		// 每一行形容词
long long bit[110];			// 每一列进率
vector<long long>key;		// 关键数字 

long long encode(vector<string>v){
	long long ret=0;
	for(int i=0;i<sz;i++) ret=ret*bit[i+1]+(adj[i+1][v[i]]-1);
	return ret;
}
vector<string>decode(long long v){
	vector<string>ret;
	for(int i=sz;i>=1;i--)
		ret.push_back(rev[i][v%bit[i]]),v/=bit[i];
	reverse(ret.begin(),ret.end());
	return ret;
}

int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		string tmp;
		cin>>tmp; cin>>tmp; cin>>tmp; cin>>tmp;
	//   Farmer     John       has       no
		for(int j=1;;j++){
			cin>>tmp;
			if(tmp=="cow.") break;
			qwq[j].insert(tmp),sz=j;
			awa[i].push_back(tmp);
		}
	}
	
	long long R=1;
	bit[0]=1;
	for(int i=1;i<=sz;i++){
		int cnt=0;
		auto it=qwq[i].begin();
		for(;it!=qwq[i].end();it++) adj[i][*it]=++cnt,rev[i][cnt-1]=*it;
		R*=cnt,bit[i]=cnt;
	}
	
	for(int i=1;i<=n;i++) key.push_back(encode(awa[i]));
	sort(key.begin(),key.end()),key.push_back(R);
	
	long long cur=0,res=k;
	for(auto it=key.begin();it!=key.end();it++){
		long long now=*it;
		if(res<=now-cur){
			vector<string>ans=decode(res+cur-1);
			for(auto it0=ans.begin();it0!=ans.end();it0++) cout<<*it0<<' ';
			break;
		}else
			res-=(now-cur),cur=now+1;
	}
	return 0;
}
```

---

## 作者：phoebuszhu (赞：2)

## 题意简述

现在给你了 $n$ 个 FJ 没有的牛的一些形容词连句，问你 FJ 有的牛中的第 $m$ 个的形容词属性连句是什么？

## 思路简述

步骤 $1$：转化法

首先，发现 $n$ 很小。~~所以可以乱搞(bushi~~

而且，每一个字符串的形容词个数是一样的。

可以想到什么呢？

进制！！

我们可以把每一个形容词看成一个进制位，那么其实答案就是一个转进制后的数。

在输入的时候，我们把每一个形容词用数字存下来。

就比如，样例中：


```
Farmer John has no large brown noisy cow.

Farmer John has no small white silent cow.

Farmer John has no large spotted noisy cow.
```
*注：在此句话之后，所有的 $(a)_{cow}$ 作为一个字符串所对应的 cow 进制数使用，其中 $a$ 是一个整数。

我们可以把第一位的 `large` 当作 $0$，`small` 当作 $1$。第二位的`brown` 当作 $0$，`white` 当作 $1$，`spotted` 当作 $2$。

以此类推。

那么我们查询一个字符串其实就是查询一个进制数。

比如 `small spotted noisy` 就对应 $(120)_{cow}$。

接下来就是 cow 进制转为 $10$ 进制了。

$(120)_{cow}=0+2\times 2+1\times 2\times 3=6+4=10$。

读者可以自己按照样例和**我给出的定义**推导后可以发现， `small spotted noisy` 真的对应 $(120)_{cow}$。

那如果我给你一个数 $10$，那你能不能推导到 `small spotted noisy` 呢？

当然可以。

我们用小学学过的短除法，$10$ 是可以对应到 $(120)_{cow}$ 的。

$10\div 2=5$ 余 $0$；

$5\div 3=1$ 余 $2$；

$1\div 2=0$ 余 $1$；

请注意，先除以后面的那个数，然后从后向前连起余数即可。

然后就可以通过 $120$ 对应到 `small spotted noisy` 了。

当然，对应关系其实是按照**字典序排序**得到的，所以我们需要排序。

----

步骤 $2$：解决问题

接下来的问题是，有一些牛是 FJ 没有的，那怎么办呢？

我们现在知道这个牛的 $id'$，那么我们如何补到 $id$ 呢？

我们只需要把这些缺掉的牛补上后，$id$ 就是对的了！

缺掉的牛的 $id$ 可以直接算出，我们可以把这些数存入一个数组。

先把这个数组排好序，随后我们只需要从小到大和 $id'$ 比较。

- 如果 $x_i\le id'$，那么 $id'$ 应该在这头牛补上后向后一个顺位，那就是 $id'+1$ 了。
- 如果 $x_i> id'$，那么已经结束了，因为后面的 $x$ 一定 $>id'$，$id=id'$；

这样做为什么是对的呢？

排好序后，第一个数就一定是第一个缺的，第二个数就一定是第二个缺的，以此类推。

补上后直接用步骤 $1$ 中的做法做就行了。

----

步骤 $3$：思路整理

先通过 cow 进制转 $10$ 进制把所有的形容词连句转为数字；

然后通过步骤 $2$ 中的模拟算法把 $id'$ 转化为 $id$；

随后通过 $10$ 进制转 cow 进制把 $id$ 转为正常的形容词连句即可。

时间复杂度是 $O(n\log n+n|S|)$ 的。

---

## 作者：Liyunze123 (赞：0)

相信题意大家都明白了吧。

这道题呢，可以把所有的形容词都提取出来（一行的第五个单词开始，到倒数第二个单词都是形容词），再把它们分为第 $1$ 个、第 $2$ 个……直到第 $M$ 个（$M$ 是未知数，要自己去求）。

题目说了要按照形容词的字典序排序，这一步大家别忘了。

接下来就是重点了。

算法思考：暴力枚举所有的可能，枚举到第 $K$ 头牛。

时间复杂度 $O(K)$，会超时。

优化：就拿样例来说，答案是 small spotted noisy，那么形容词是 large 的就可以跳过。那么问题来了，怎么知道答案的形容词不是 large 呢？形容词是 large 的应该有 $6$ 头，但两头 FJ 没有，所以只有 $4$ 头牛带 large。但是：$K=7$，large 的最大编号才是 $4$，所以答案肯定不带 large。继续看 small。

FJ有 $2×3-1=5$ 头，再算上前面的 large，small 的最大编号应该是 $9$。$9>7$，所以第 $K$ 头牛的第一个形容词是 small。照这样的方法，继续确认第 $2$ 个、第 $3$ 个……第 $M$ 个形容词。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t[32],j,b[32],m,h[32];//b[i]表示第i位选第b[i]个形容词，t[i]表示总共有多少种第i个形容词 ，m用来累加，h数组每个数据的值最后都会一样，h[i]表示第i句形容词的个数（不管形容词之前是否出现） 
char ans[32][102][13],a[32],ans2[32][102][13];//a用来输入，ans和ans2的作用待会儿会讲到的 
int find(int i){//find函数用来找输入的形容词a是否已经出现 
	for(int w=1;w<=t[i];w++)if(strcmp(ans[i][w],a)==0)return 1;
	return 0;
}
void s(int i){//给ans[i]按照字典序排序，使用选择排序 
	for(int w=1,m=w;w<t[i];w++,m=w){
		for(int x=w+1;x<=t[i];x++)if(strcmp(ans[i][m],ans[i][x])>0)m=x;
		swap(ans[i][m],ans[i][w]);
	}
}
int f(int i,int j){
	b[i]=j;//假设第i位选第j个形容词 
	int num=1;//因为要做乘法，初始化成1 
	for(int w=i+1;t[w];w++)num*=t[w];//应有多少头牛 
	for(int w=1,x=1;w<=n;w++,x=1){
		for(x=1;x<=i;x++)if(strcmp(ans2[x][w],ans[x][b[x]])!=0)break;//切记是ans2[x][w],表示第w句话中第x个形容词 
		if(x==i+1)num--;//如果输入中某头没有的牛复合函数的计算条件，数量-1 
	}
	b[i]=0;//第i位不一定选第j个形容词，所以计算结束还要变回0 
	return num;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int w=1,y=4;w<=n;w++,y=4){
		for(int x=1;x<=5;x++)scanf("%s",a);
		while(strcmp(a,"cow.")){//不是 cow.，就说明还没读完整个句子 
			if(!find(++y-4))t[y-4]++,strcpy(ans[y-4][t[y-4]],a);//判断形容词是否已经出现了 ，如果没出现就加入ans1数组，该数组存不重复的所有形容词 ，y表示是句子的第几个单词 
			strcpy(ans2[y-4][++h[y-4]],a);//但ans2数组就是直接截取句子的所有形容词，不管有没有出现过 
			scanf("%s",a);
		}
	}
	for(int w=1;t[w];w++)s(w);//s函数是排序的，因为我用char数组所以就写了选择排序，当然也可以用string写sort 
	for(int w=1;t[w];w++)//枚举要确认的位数，w表示要确认第w位的形容词 
		for(int x=1;x<=t[w];x++){//枚举第w位所有的形容词 
			int y=f(w,x);//f(w,x)表示已经确认好w-1位，第w位的形容词选第x个，牛的数目 
			if(m+y<k)m+=y;//如果第w位的形容词到了第x个牛的总数还不到K就继续累加 
			else{b[w]=x;break;}//否则第w位的形容词就选第x个 
		}
	for(int w=1;t[w];w++)printf("%s ",ans[w][b[w]]);//最后输出，这么写因为第w位选第b[w]个形容词 
	return 0;
}
```


---

## 作者：曹老师 (赞：0)

## Sol ##
[blog食用](http://www.caolaoshi.men/index.php/archives/usaco13nov-fjhnlbc.html)

~~哇哇哇，昨晚调了一个小时没调出来，今天早上调了一会就出来了~~坑点不算很多，只是我比较粗心……

拿到题，一眼肯定想到和排列组合有关的知识，其实用到的也不是太多，首先对于单词的存储，我们想方设法的把每一行和每一列的单词都分别存下来，以后都会调用到的。然后预处理出第$i$列第$j$行后面有多少种可能性放到$qc$数组中，递推公式：

$$qc_{i,j} = qc_{i+1,j} ×  cnt[i+1]$$

在预处理之前呢，我们求出每一列不同的单词数量，存到$cnt$数组中，可以排好序之后用类似栈的做法做，不多解释了，截止到现在，排列组合的知识已经全部用完~

然后，我们求**如果没有删除(在所有的牛中去掉没有的牛)操作，我们要查询的$K$所对应的位置。**什么叫对应的位置呢？就是开始我们的状压了：**对于每一列，每一个单词都标记一下，该单词是这一列的第几个单词。**那么我们第一次求$K$的位置的时候，就能把求得的这些位置存到$Knum$数组中。

接下来就是删除操作，所谓删除，其实我们可以理解为：**如果有比$K$的位置小的数，我们就把$K$往后移。**~~应该很容易理解吧。~~于是我们就枚举每一行，把每一行的几个单词对应的位置处理出来，存到$Pnum$数组中，用$sol$函数进行比较，如果比$K$的位置要小，$K$就后移。最后$Knum$中的数就是我们答案在他所在列的位置，输出就好了。

再说说把单词转化为位置的做法，刚才我们维护了第$i$行第$j$列后面的可能性。我们每一列每一列的求，对于每一列，枚举他的每一行，如果从枚举到的这一行向上，所有可能性的总和比我们要查的位置要大，我们就取这一行，更新我们要查的位置，**更新的时候一定要记得乘上行数减一！**

**几个易错的地方：**

1.最后比较每一行与$K$所对应的位置的时候，一位一位的比较，发现小的，立即停止，注意，不是$break$，是$return$，因为题目中可能会有比较的两个字符串每一个位置对应相等的情况，因此在最后打上标记就行。

2.把每一个单词转化为每一列的第几个单词的时候，注意两个地方，第一个就是相等的情况，如果相等，后面的直接取最后一行；第二种是最后一列的时候，直接就可以赋值。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct Letr {
	int group;
	string adj;
	bool operator < (const Letr &a) const {
		return adj < a.adj;
	}
};
Letr adj[30005];
vector<string>str[350];
int n , k , num , top = 0 , cnt[350] , qc[350][1050], knum[350] , pnum[350], flag;
string gro[350][1050];

int jud(string s) {
	if(s != "Farmer" && s != "John" && s != "has" && s != "no" && s != "cow.")
		return 1;
	return 0;
}

void update(int t) {
	for(int i=1; i<num; i++) {
		int sum = 0;
		for(int j=1; j<=cnt[i]; j++) {
			sum += qc[i][j];
			if(sum == t) {
				knum[i] = j;
				for(int l=i+1; l<=num; l++)
					knum[l] = cnt[i];
				return ;
			}
			if(sum > t) {
				knum[i] = (j-1<1)?1:j;
				t -= (qc[i][(j-1<1)?1:(j-1)]*(j-1));
				break;		
			}
		}
	}
	knum[num] = t;
} 

void sol(int x[] , int y[]) {
	for(int i=1; i<=num; i++) {
		if(x[i] > y[i])
			return;
		if(x[i] < y[i]) {
			flag = 1;
			return;		
		}
	}
	flag = 1;
}

int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++) {
		string s;
		num = 0;
		while(1) {
			cin>>s;
			if(jud(s)) {
				num++;
				str[i].push_back(s);
				adj[++top].adj = s;
				adj[top].group = num;
			}
			if(s == "cow.")
				break;
		}
	}
	sort(adj , adj+top+1);
	for(int i=1; i<=top; i++) {
		if(adj[i].adj == adj[i-1].adj && adj[i].group == adj[i-1].group)
			continue;
		gro[adj[i].group][++cnt[adj[i].group]] = adj[i].adj;
	}
	for(int i=1; i<=n; i++)
		qc[num][i] = 1;
	for(int i=num-1; i>=1; i--)
		for(int j=1; j<=n; j++)
			qc[i][j] = qc[i+1][j]*cnt[i+1];
	update(k);
	for(int i=1; i<=n; i++) {
		flag = 0;
		for(int j=0; j<str[i].size(); j++) {
			for(int l=1; l<=cnt[j+1]; l++) {
				if(str[i][j] == gro[j+1][l]) {
					pnum[j+1] = l;
					break;
				}
			}		
		}
		sol(pnum , knum);
		if(flag) {
			k++;
			update(k);
		}
	}
	for(int i=1; i<=num; i++)
		cout<<gro[i][knum[i]]<<" ";
	return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3087

---

