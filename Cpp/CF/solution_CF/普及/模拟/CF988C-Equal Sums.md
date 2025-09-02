# Equal Sums

## 题目描述

You are given $ k $ sequences of integers. The length of the $ i $ -th sequence equals to $ n_i $ .

You have to choose exactly two sequences $ i $ and $ j $ ( $ i \ne j $ ) such that you can remove exactly one element in each of them in such a way that the sum of the changed sequence $ i $ (its length will be equal to $ n_i - 1 $ ) equals to the sum of the changed sequence $ j $ (its length will be equal to $ n_j - 1 $ ).

Note that it's required to remove exactly one element in each of the two chosen sequences.

Assume that the sum of the empty (of the length equals $ 0 $ ) sequence is $ 0 $ .

## 说明/提示

In the first example there are two sequences $ [2, 3, 1, 3, 2] $ and $ [1, 1, 2, 2, 2, 1] $ . You can remove the second element from the first sequence to get $ [2, 1, 3, 2] $ and you can remove the sixth element from the second sequence to get $ [1, 1, 2, 2, 2] $ . The sums of the both resulting sequences equal to $ 8 $ , i.e. the sums are equal.

## 样例 #1

### 输入

```
2
5
2 3 1 3 2
6
1 1 2 2 2 1
```

### 输出

```
YES
2 6
1 2
```

## 样例 #2

### 输入

```
3
1
5
5
1 1 1 1 1
2
2 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
6
2 2 2 2 2 2
5
2 2 2 2 2
3
2 2 2
5
2 2 2 2 2
```

### 输出

```
YES
2 2
4 1
```

# 题解

## 作者：泥土笨笨 (赞：25)

## 简述题意

在 `n` 个长度不一定相同的序列中任选两个序列，两个序列都删去他们中的一个数，使得这两个序列的和相同。

## 思路

我们按顺序依次去看每一个序列，对于第 `i` 个序列，因为现在允许我们删掉一个数字，我们可以先把所有数字求和，再依次枚举每个数字，从总和中减掉，这样我们可以得到所有可能的和。

这时候去找一下，前面有没有哪个序列已经产生过这个和，如果之前出现过，它们两个就匹配形成答案。如果没有出现过，那么就把这个和记下来，等着后面有没有来匹配我的。

这里就形成了一个“记录”的需求，需要记录和以及这个和出现在第几个序列里，以及这个和是删掉了哪个数形成的。并且我们需要根据和进行快速的查询。这里正好发现 `map` 是可以满足需求的。

## 具体实现

首先用定义一个结构体和一个 `map` ：

```cpp
struct Node {
    int s, p;
};
map<int, Node> m;
```

其中，结构体中的 `s` 表示目前是第几个序列， `p` 表示这个序列中我们要删掉哪个数字。然后用删掉数字以后的和来当 `map` 的 `key` ，来存储这个和与结构体。

接下来就是遍历每个序列，再遍历每个要被删掉的数，计算出现在的和。用这个和到 `map` 里面去查询，如果之前出现过，则输出答案，否则将这个和记录到 `map` 里。具体可以看代码。


## 完整代码

```cpp
#include <iostream>
#include <map>

using namespace std;
const int MAXN = 200005;
struct Node {
    int s, p;
};
int k, a[MAXN], n, sum;
map<int, Node> m;

int main() {
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        sum = 0;
        cin >> n;
        for (int j = 1; j <= n; ++j) {
            cin >> a[j];
            sum += a[j];
        }
        for (int j = 1; j <= n; ++j) {
            int diff = sum - a[j];
            if (m.count(diff) && m[diff].s != i) {
                cout << "YES" << endl;
                cout << m[diff].s << " " << m[diff].p << endl;
                cout << i << " " << j << endl;
                return 0;
            } else {
                m[diff].s = i;
                m[diff].p = j;
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}
```


---

## 作者：myEnd (赞：2)

## 题目翻译

时间限制 $ 2s $​   |   空间限制 $ 256\text{MB} $​​



#### 题目描述：

在 $n$ 个长度不一定相同的序列中任选两个序列，两个序列都删去他们中的一个数，使得这两个序列的和相同。



#### 输入格式：

第一行一个整数 $k$ ( $2 \le k \le 2 \cdot 10^5$​​ )。

接下来有 $k$ 组数据。

对于第 $i$​​ 组数据第一行是一个整数 $n_i$​​ （ $1 \le n_i \le 2 \cdot 10^5$​​ ），表示这个序列有 $n_i$​​ 个数。第二行则是 $n_i$​​ 个数 $a_{i,1}, a_{i,2}, \dots, a_{i,n_i}$​ ，表示这个序列。对于每一个 $a$​ 保证其都在闭区间 $[-10^4, 10^4]$​ 内，并且每个序列的和都不超过 $2\cdot 10^5$​​ ，$n_1, n_2, n_3, \dots, n_k \le 2\cdot 10^5$​ 。

#### 输出格式：

第一行输出 `YES` 或 `NO` 表示 **有解** / **无解** 。

对于 `YES` 的情况，接下来两行分别输出 **序列号  位置** ，位置从1开始，表示要删除的数。

对于 `NO` 的情况，输出文件无其余内容。




#### 样例解释：

样例一：

选取 $[2,3,1,3,2]$​ （序列 **1** ） 和 $[1,1,2,2,2,1]$​ （序列 **2**）。 可以通过删除第一个序列的第 **二** 个元素得到 $[2,1,3,2]$​ 并且通过删除第二个序列的第 **六** 个元素得到 $[1,1,2,2,2]$​ . 这样两个序列的和就都变为 $8$​​​ 了，符合题意​。

样例二：

无解。

样例三：

选取 $[2,2,2,2,2]$​​​​ （序列 **2**）和 $[2,2,2,2,2]$​​​​ （序列 **4**）。 可以通过删除第二个序列的第 **二** 个元素得到 $[2,2,2,2]$​​​​ 并且通过删除第四个序列的第 **一** 个元素得到 $[2,2,2,2]$​​​​ . 这样两个序列的和就都变为 $8$​​​​​ 了，符合题意。

## 题解

#### 解题思路：

可以在输入时就对每个序列进行求和并记录，读入完之后就拿到了这个序列的 **初始和** 了。之后进行暴力枚举删除每个数，并记录在一个键值对应的映射表 `map` 中。其中因为枚举出来的是和，所以令和是键，要输出的数据是值，可以定义一个结构体 `Node_t` 来存储。

#### 参考代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

struct Node_t
{
    //序列
    __int64 sequences;

    //对应下标
    __int64 index;
};

__int64 k/*数据组数*/, a[200005]/*当前序列*/, n/*元素数*/, nowsum/*当前的和*/;

map<__int64, Node_t> mp;

inline void quick_cppio(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return ;
}

inline void init(void)
{
    nowsum = 0;
}

int main()
{
    quick_cppio();
    cin >> k;
    for (__int64 i = 1; i <= k; ++i)
    {
        init();
        cin >> n;
        for (__int64 j = 1; j <= n; ++j)
        {
            cin >> a[j];
            nowsum += a[j];
        }
        for (__int64 j = 1; j <= n; ++j)
        {
            //枚举删掉的数
            __int64 now = nowsum - a[j];//删掉这个数之后的和
            if (mp.count(now) && mp[now].sequences != i)
            {
                cout << "YES" << endl << mp[now].sequences << " " << mp[now].index << endl << i << " " << j << endl;
                goto end;
            }
            else
            {
                Node_t tmp;
                tmp.index = j;
                tmp.sequences = i;
                mp[now] = tmp;
            }
        }
    }
    cout << "NO" << endl;
    end:
    return 0;
}
```



---

## 作者：Alexxu2024 (赞：2)

------------
~~终于发布了第一篇题解~~
# CF988C 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF988C)



题目要求删除一个数，那么，我们可以在每次输入新序列时删除一个数进行求和，再查询以前有没有这个数值，如果有，直接输出结果并结束程序。

考虑“查询”，可以维护一个 ```map``` ：


------------

```cpp
map<int,pair<int,int> > mp;
```


------------

代表：


------------

```
map<得到的值,pair<第几个数列，删除的第几个数> >
```


------------

那么求和怎么办呢？

可以先算出总和，再减去要删除的数。

# 代码：
```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
long long a[200010];//貌似可以用int
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    map<int,pair<int,int> > mp;
    int k;
    cin >> k;
    for(int i=1;i<=k;i++){
        int n;
        cin >> n;
        long long sum=0;
        for(int j=1;j<=n;j++){
            cin >> a[j];
            sum+=a[j];//求总和
        }
        //cout << sum << " ";
        for(int j=1;j<=n;j++){
            long long presum=sum-a[j];//求删除数后的总和

            //cout << presum << " ";
            if(mp.count(presum)&&mp[presum].first!=i){//如果已经保存过这个和且不是同一个数列
                cout << "YES" << endl;
                cout << mp[presum].first << " " << mp[presum].second << endl;
                cout << i << " " << j;
                return 0;//直接结束程序
            }
            else{//向map中添加新的结果
                mp[presum]={i,j};
            }
        }
        //cout << endl;
    }
    cout << "NO";//如果一直没有判断到，就不会结束程序，无解
    return 0;
}
```


------------

# [通过记录](https://www.luogu.com.cn/record/155754839)

---

## 作者：ACtheQ (赞：1)

## CF988C Equal Sums

本题比较水为 ```STL``` 大水题！

前置知识：[map](https://www.cnblogs.com/fnlingnzb-learner/p/5833051.html)。

一个正常人会想到的操作，先将每个序列求和，在挨个枚举每个数去删除，然后判断。

很明显，这样的时间复杂度为 $O(T^N)$。

~~(不超时才怪呢）~~！

于是我翻出来我的 ```STL``` ~~(家箱底)~~：```MAP```。

```MAP``` 定义为 ```map<int,Node>```。

其中 ```Node``` 有两个参数，一个代表当前是第几个数列，另一个代表删除哪一个数。

对于每一个序列，枚举每一项，同时将一个数列的总和减去当前项。

再判断这个差放进 ```map``` 中查询，如果出现相同，且不是本身的话，输出答案，结束程序。

最终，如果没有结果输出 ```NO```。

时间复杂度为：$O(TN)$。

---

## 作者：xyta (赞：1)

### 这道题其实难度不大，具体做法可以采用 map 或者数组。
先来看一下题目的大概意思。
## 题目
题目给出 $k$ 个序列，请找出两个序列 $a$ 和 $b$ 以及分别从两个序列中找出两个数 $a_{i}$ 和 $b_{j}$。使得 $a$ 序列的和减去 $a_{i}$ 等于 $b$ 序列的和减去 $b_{j}$。

有解输出  YES，无解输出 NO。

如果有解输出任意一组 $a$ 在所有序列中的编号 $n$ 和从 $a$ 序列中找到的数在 $a$ 序列中的编号 $i$，以及 $b$ 在所有序列中的编号 $m$ 和从 $b$ 序列中找到的数在 $b$ 序列中的编号 $j$。

## 思路

由于题目的时间限制 $2s$, 空间限制 $256\text{MB}$。而且 $ 2 \le k \le 2 \cdot 10^5 $,$ 1 \le n_{i} \le 2 \cdot 10^5 $。所以我们我法去记录所有输入的值而在所有输入结束后统一判断，但是我们的时间足够，可以采用 $O(nk)$ 的边输入便判断的方法。由于每个序列的总和都在 $-10^4$ 到 $10^4$ 之间，所以可以理解为所有可能的总和数量不超过 $2\times10^4$，再减去一个数，可能数量没有太大的差异，而数组在符合题意的情况下至少能开 $10^7$。所以我们可以用一个数组来记录每一种可能结果，但设计到负数结果，我们可以直接采用 map 进行存储，当然数组经过处理也是可以存储的。

在每次输入完序列后进行遍历所有本序列肯能的值（值代表着此序列的和减去任意此序列的一个数）。然后在 map 中查询这个值是否存在，如果存在并且不是本序列出来的值，那么可以直接进行配对，得出一个答案并输出，后续的输入可以不用管了。但如果没有就将这个值得到的信息存储到 map 中对应得地方，方便后续其它数组得出的其它值进行配对。

我们可以用一个布尔类型的变量去存储答案是否存在，初始值设为假。当找出答案后将答案直接输出或者用变量进行存储，布尔类型变量改为真。所有判断结束后如果值为真则有解，否则无解。

在 map 中我们只需要存储这个值得出的序列编号以及此序列的和减去的数在此序列中的编号，因为每次从新输入新序列，前面输入的序列不会保留，所以我们需要将需要存储的值的信息存全方便之后配对的查询以及输出。

当然，你得出答案后可以直接结束程序，这样就不需要布尔类型的变量去存储状态，但为了保险起见，我选择让他把所有数据都输完。

具体执行内容看代码。

## 代码

```cpp
#include<iostream>
#include<map>//重要头文件 
#include<algorithm>
using namespace std;
int a[200010];//这里是每次输入暂时存储输入序列的地方 
map<int,int> x;//这个map用来存储这个值对应的序列的编号 
map<int,int> y;//这个map用来存储这个值对应的序列中减去的数在此序列中的编号
map<int,bool> z;//这个map用来存储这个值在以前是否出现过
//当然，写了这么多的map也可以用结构体将其化为一个map,具体写法如下
/*
struct node{
	int x,y;
	bool z;
};
map<int,node> m;
*/
//查询时用m[n].x这种形式查询 
int main()
{
	bool cmp=false;//用来存储现在的状态是否有解 
	int ans1,ans2,ans3,ans4;//分别对应题目简介中的：a序列在所有序列的数在a中的编号，这个值减去的数在a中的编号，b序列在所有序列中的编号，这个值减去的数在b中的编号。  
	int k;//序列数量 
	cin>>k;
	for(int i=1;i<=k;i++)//可以改为while(k--)，因为我最开始以为要在循环后找出答案，所以没敢损坏k的值，一样的作用 
	{
		int sum=0;//为了方便后续每个值的枚举，我们先用sum存储整个序列的和然后在遍历减去每一个数，值就可以o(1)得到了 
		int n;//此序列的长度 
		cin>>n;
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];//输入序列 
			sum+=a[j];//加和 
		}
		if(cmp) continue;//如果已经有解，后续就不需要进行查找，可以直接跳过 
		for(int j=1;j<=n;j++)//开始用o(n)枚举所有此序列可能的值 
		{
			if(!z[sum-a[j]])//如果此值从未出现 
			{
				z[sum-a[j]]=1;//出现了 
				x[sum-a[j]]=i;//存储此序列的编号 
				y[sum-a[j]]=j;//存储减去此值在此序列中的编号 
			}
			else if(x[sum-a[j]]!=i)//如果出现并且不是此序列中出的值，就代表找到解了 
			{
				cmp=1;//将状态改为真，代表找到解了 
				ans1=x[sum-a[j]];//存储答案，如上文 
				ans2=y[sum-a[j]];//存储答案，如上文 
				ans3=i;//存储答案，如上文 
				ans4=j;//存储答案，如上文 
				//break; 
			}
		}
	}
	if(cmp)//有解 
	{
		cout<<"YES"<<endl<<ans1<<" "<<ans2<<endl<<ans3<<" "<<ans4<<endl;//输出答案 
	}
	else cout<<"NO";//无解 
	return 0;
}//简简单单60行，问题全部解决，stl爆率真的高！ 
```

## 总结

这道题不难想，可以锻炼使用 map 或者经过处理后使用数组，时间也很宽松。

但注意事项是，加入在查询中找到已经出现过此值，不要直接得出答案，记得判断不要是从此序列中出来的值，不然就是相同的序列，不符合题意了。(~~本蒟蒻就因此哇了一次 qwq~~)

---

