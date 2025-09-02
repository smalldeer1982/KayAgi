# Fruits

## 题目描述

The spring is coming and it means that a lot of fruits appear on the counters. One sunny day little boy Valera decided to go shopping. He made a list of $ m $ fruits he wanted to buy. If Valera want to buy more than one fruit of some kind, he includes it into the list several times.

When he came to the fruit stall of Ashot, he saw that the seller hadn't distributed price tags to the goods, but put all price tags on the counter. Later Ashot will attach every price tag to some kind of fruits, and Valera will be able to count the total price of all fruits from his list. But Valera wants to know now what can be the smallest total price (in case of the most «lucky» for him distribution of price tags) and the largest total price (in case of the most «unlucky» for him distribution of price tags).

## 样例 #1

### 输入

```
5 3
4 2 1 10 5
apple
orange
mango
```

### 输出

```
7 19
```

## 样例 #2

### 输入

```
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange
```

### 输出

```
11 30
```

# 题解

## 作者：Fido_Puppy (赞：7)

这道题还是挺简（du）单（liu）的。

首先， 这题就是典型的贪心题。 一看， $N$ 和 $M$ 才 $100$ ， 暴力没问题啊！

思路也是挺简单的， 它要求我们求最小值和最大值。 先看最小值， 那么字符串的数量越多， 给它的值肯定得最小辣！ 那么最大值呢？ ~~（反一反不就行了）~~

相信大家到这一步都是能想通的。 现在问题来了， 怎么保存字符串的个数呢？

~~我会字典树！~~

~~我会二分！~~

其实， 在 $C++$ 的 $STL$ 面前， 都太复杂了！

## Map!!!

还记得小学的时候用过的桶排序吗？ 原理其实是一样的。

但是数组的下标不能用字符串啊！

别慌！

不是还有 MAP 在这儿挡着吗？

可是 MAP 不能排序（就算能排序我也不会啊！）， 怎么办？

MAP 退役了， 数组接上不就行了？

把 MAP 里的值存到数组里， 再排序呀！

#### NOTICE：

1.MAP 其实就是一种下标能定义成任何类型的数组。

2.把 MAP 里的值存到数组里的时候， 要记得不能重复存。

### 代码君：
```cpp
#include<iostream>
#include<algorithm>
#include<map>
#include<cstring>
using namespace std;
int n, m, a[100001], c[100001], len = 0, Min=0, Max=0;
map <string, int> b;
string s[100001];
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) {
		cin >> s[i];
		b[s[i]]++;
	}
	sort(a + 1, a + n + 1, less<int>());
	for(int i = 1; i <= m; i++) {
		if (b[s[i]] != 0) c[++len] = b[s[i]];
		b[s[i]] = 0;
	}
	sort(c + 1, c + len + 1, greater<int>());
	for(int i = 1; i <= len; i++) {
		Min += c[i] * a[i];
		Max += c[i] * a[n - i + 1];
	}
	cout << Min << " " << Max;
	return 0;
}
```
                             
完结撒花！






---

## 作者：_Qer (赞：3)

~~真是一道繁琐的题~~

~~题解有点长看不下去就算了吧~~

这题可以分为两个部分来做，一部分是求最大价值，另一部分是求最小价值。

表述可能不是很清晰，不懂的可以自己先看看代码，理解一下用处，实在有问题就私信我吧，如果看到会第一时间回复的
____
### **先来解决公共的问题：**

#### 首先是变量和函数部分：

```cpp
int n, m, v[110], minv = 0, maxv = 0;
//依次为价格数、水果数、每个价格、最小价值、最大价值
struct fruit{
    string name;
    int num;
}arr[110];
string s;//输入水果名
int top;//水果种类数
//定义一个结构体，表示每个水果，有水果名（仅用于查询）和数量
bool com(fruit a, fruit b) {
    return a.num < b.num;
}
//结构体fruit数组排序需要的函数，升序
bool comn(int a, int b) {
    return a < b;
}
//数组升序排列
```
#### 接下来是输入和简单处理部分：

```cpp
	cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    //上面的输入没什么好讲的，如题
    sort(v, v + n, comn);//将价格升序排序，原因下面讲
    //下面是输入名字及处理
    bool ad;//记录输入的水果名是否是新的
    for (int i = 0; i < m; ++i) {
        cin >> s;//输入名字
        ad = false;//ad为false表示是新水果
        for (int j = 0; j < top; ++j) {//在已有水果中找
            if (arr[j].name == s) {//找到了
                ++arr[j].num;//水果数量+1
                ad = true;//不是新的
                break;
            }
        }
        if (!ad) {//没有找到
            arr[top].name = s;
            arr[top].num = 1;
            ++top;
            //添加新水果
        }
    }
    sort(arr, arr + top, com);//将水果按数量升序排列
```

____
### **最大价值：**

尽量**将更高的单价给有更多数量的水果**，可以得到最大的价值，因此需要按照降序（为了减少代码量，把求最大和最小价值的循环合起来，所以这里按照**从后往前找**，替代降序排列）。

#### 核心部分：
```cpp
	for (int i = 0; i < top; ++i)//每个水果都要有价值
		maxv += v[n - i - 1] * arr[top - i - 1].num;
        //最大价值加上数量与单价的积
```
____
### **最小价值：**

与最大价值相反，尽量**把更低的单价给更多的水果**，获得最少收益，因此按照升序排列，按顺序取每种水果的收益。

#### 核心部分：

```cpp
	for (int i = 0; i < top; ++i)//每个水果都要有价值
		minv += v[i] * arr[top - i - 1].num;
        //这里arr数组是按数量多到少排列，所以用top - i - 1从数量多到少取
        //最小价值加上数量与单价的积
```
____
大家也看到了，上面我求最大价值的时候也是按升序排列，只是从后往前数的，可以知道，我是要合并的，而且细心的同学也能发现，两个循环的步骤都是一样的，所以就把这两个和起来，如下：

```cpp
	for (int i = 0; i < top; ++i) {
        minv += v[i] * arr[top - i - 1].num;//最小价值
        maxv += v[n - i - 1] * arr[top - i - 1].num;//最大价值
    }
    //这样就可以同时求两个啦
```
____
### **完整代码：**
（已经看懂上面解释的同学可以不用看完整代码了，这里的代码没有注释）
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, v[110], minv = 0, maxv = 0;
struct fruit{
    string name;
    int num;
}arr[110];
bool com(fruit a, fruit b) {
    return a.num < b.num;
}
bool comn(int a, int b) {
    return a < b;
}
string s;
int top;
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    sort(v, v + n, comn);
    bool ad;
    for (int i = 0; i < m; ++i) {
        cin >> s;
        ad = false;
        for (int j = 0; j < top; ++j) {
            if (arr[j].name == s) {
                ++arr[j].num;
                ad = true;
                break;
            }
        }
        if (!ad) {
            arr[top].name = s;
            arr[top].num = 1;
            ++top;
        }
    }
    sort(arr, arr + top, com);
    for (int i = 0; i < top; ++i) {
        minv += v[i] * arr[top - i - 1].num;
        maxv += v[n - i - 1] * arr[top - i - 1].num;
    }
    cout << minv << " " << maxv << endl;
    cout << "拒绝抄袭，共建和谐洛谷" << endl;
    return 0;
}
```

---

## 作者：fls233666 (赞：2)

首先让我指出一个翻译中的缺漏：

如果会出现不同字符串的数量比 $n$ 大的情况，那么岂不是要分类讨论...但是这题貌似没有到达那样的难度...

我仔细翻看原题面，找到了一句话：

It is guaranteed that the number of distinct fruits from the list is less of equal to $n$

简单翻译一下：**保证不同的字符串数量小于** $n$ 。

于是这题就简单很多了。

------------

考虑怎么分配价格。我们可以马上得出一个贪心策略：**对于总价格最大，优先把大的价格分配给数量最多的字符串；对于总价格最小，优先把最小的价格分配给数量最多的字符串** 。

简单来说，就是要**统计每种字符串的数量，然后按照数量的多少进行分配**。

具体的实现流程是：
1. 把 $n$ 个价格从小到大排序；
2. 把 $m$ 个字符串去重，统计每种字符串的个数；
3. 把每种字符串的个数排序；
4. 分别计算最小总价格和最大总价格。

那么，下面来实现代码：

```cpp
#include<iostream>
#include<cstdio> 
#include<string>
#include<algorithm>
#define rgt register int
#define ll long long
#define MX 111
using namespace std;

int cost[MX],cnt[MX];
/* cost[]为读入的n个价格
  cnt[]为每种字符串的数量*/
string fruits[MX];    //fruits为去重后的字符串
int n,m,len,minans,maxans;
//len为字符串的种类的数量
  
int main()
{
	string str;
	bool fd;
  
	cin>>n>>m;
	for(rgt i=0;i<n;i++)
		cin>>cost[i];
	sort(cost,cost+n);
    //读入价格并排序
  
	for(rgt i=0;i<m;i++){
		cin>>str;  //读入一个字符串
		fd=false;
		for(rgt j=0;j<len;j++){
			if(str==fruits[j]){  //如果重复
				fd=true;  //标记
				cnt[j]++;  //计数
			}
		}
		if(!fd){   //没有重复
			fruits[len]=str;
			cnt[len]++;
			len++;
            //加一个种类
		}
	}
	sort(cnt,cnt+len);   //数量排序
                                
	for(rgt j=0,i=len-1;i>=0;i--,j++){
		minans+=cnt[i]*cost[j];
	} //计算最小价格
  
	for(rgt j=n-1,i=len-1;i>=0;i--,j--){
		maxans+=cnt[i]*cost[j];
	} //计算最大价格
  
	cout<<minans<<" "<<maxans;   //输出答案
	
    return 0;
}
```


---

