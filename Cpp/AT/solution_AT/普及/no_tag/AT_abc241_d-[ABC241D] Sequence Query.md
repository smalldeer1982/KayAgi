# [ABC241D] Sequence Query

## 题目描述

# 题意简述
有一个空序列 $A$。给定 $Q$ 次操作，每次询问是以下三种之一：

>`1 x`：向 $A$ 中插入元素 $x$。
>
>`2 x k`：输出 $A$ 中所有 $\le x$ 的元素中的第 $k$ 大值。如果不存在输出 `-1`。
>
>`3 x k`：输出 $A$ 中所有 $\ge x$ 的元素中的第 $k$ 小值。如果不存在输出 `-1`。

## 说明/提示

>$1\le Q\le2\times10^5$。
>
>$1\le x\le10^{18}$。
>
>$1\le k\le5$。
>
>所有输入均为整数。

## 样例 #1

### 输入

```
11
1 20
1 10
1 30
1 20
3 15 1
3 15 2
3 15 3
3 15 4
2 100 5
1 1
2 100 5```

### 输出

```
20
20
30
-1
-1
1```

# 题解

## 作者：wxzzzz (赞：4)

### 思路

#### set

set 是一个 STL 里的关联式容器，其内部是平衡树（红黑树），维护一个有序集合。

下面介绍两种本题需要用到的 set 支持的操作。

1. `s.insert(x)` 在集合 $s$ 中插入一个元素 $x$。
2. `s.lower_bound(x)` 在集合 $s$ 中查找第一个大于等于 $x$ 的元素的地址。

#### 需要注意的几点

- 遍历 set 用的是地址变量，要在前面加指针符号才能得到数值。

- set 自带去重，但本题中是不要去重的，这里要用多重集合 `multiset`。

#### 实现

- $op=1$

  直接插入即可。

  ```cpp
  a.insert(x);
  ```

- $op=2$

  先找到第一个小于等于 $x$ 的位置，然后往后跳 $k$ 位置，一边跳一边判断是否越界。

  ```cpp
  cin >> k;
  auto ans = a.upper_bound(x);
      //auto 表示自动识别变量类型

  while (ans != a.begin() && k)
     k--, ans--;

  if (k)
      cout << "-1\n";
      //如果此时 k 仍然大于 0 ，说明不存在第 k 大的元素

  else
      cout << *ans << '\n';
  ```

- $op=3$

  同理。

  不过，要注意的是，`lower_bound(x)` 这个位置是所有大于等于 $x$ 的元素中的最大值， $ans$ 的初始地址已经包括了一个元素，因此 $k$ 要少往后跳一次。

  ```cpp
  cin >> k;
  auto ans = a.lower_bound(x);

  while (ans != a.end() && k > 1)
      k--, ans++;

  if (ans == a.end())
      cout << "-1\n";
      //如果 ans 已经跳到末尾，说明没有第 k 小的元素

  else
      cout << *ans << '\n';
  ```

### 复杂度证明

由于 set 内部是红黑树，其所有操作复杂度均为 $O(\operatorname{log}n)$ 。

然后每次查询最多往前后查 $k$ 个元素，而 $k≤5$ 。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

long long q , x, k, op;
multiset<long long> a;

int main() {
	cin >> q;
	
    while (q--) {
        op, x;
        cin >> op >> x; 
        if (op == 1)
            a.insert(x);
        else if (op == 2) {
            cin >> k;
            auto ans = a.upper_bound(x);

            while (ans != a.begin() && k)
                k--, ans--;

            if (k)
                cout << "-1\n";
            else
                cout << *ans << '\n';
        } else {
            cin >> k;
            auto ans = a.lower_bound(x);

            while (ans != a.end() && k > 1)
                k--, ans++;

            if (ans == a.end())
                cout << "-1\n";
            else
                cout << *ans << '\n';
        }
    }

    return 0;
}
```

---

## 作者：tbdsh (赞：2)

# 题意
[题目传送门](/problem/AT_abc241_d)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-abc241-d)

进行 $Q$ 次对空序列 $A$ 的操作，操作如下：

>`1 x`：向 $A$ 中插入元素 $x$。
>
>`2 x k`：输出 $A$ 中所有 $\le x$ 的元素中的第 $k$ 大值。如果不存在输出 `-1`。
>
>`3 x k`：输出 $A$ 中所有 $\ge x$ 的元素中的第 $k$ 小值。如果不存在输出 `-1`。

对于每次的操作 $2,3$ 输出一个数表示答案。

# 分析
本题可以使用 `STL` 中的 `multiset`。

`multiset` 是一个是有序多重集合，会自动对里面的元素进行排序。

对于每次操作 $1$，直接用 `.insert(x)` 插入即可。

时间复杂度：$O(\log n)$。

对于每次操作 $2$，用 `.upper_bound(x)` 查找到第一个 $> x$ 的数再暴力枚举答案即可。**注意**，如果在枚举中得到的迭代器是 `.begin()`，应该退出循环，输出 `-1`。

时间复杂度：$O(\log n)$。

对于每次操作 $3$，用 `.lower_bound(x)` 查找到第一个 $\ge x$ 的数再暴力枚举答案即可。**注意**，如果在枚举中得到的迭代器是 `prev(.end())`，或未查找到 $\ge x$ 的数，应该退出循环，输出 `-1`。

时间复杂度：$O(\log n)$。

总时间复杂度：$O(Q\times \log n)$。

# Code
```cpp
//Code provided by @tianbiandeshenghuo11
#include<bits/stdc++.h>

using namespace std;
long long t;
multiset<long long> m;
int main(){
  cin >> t;
  while (t--){
    long long a, x, k;
    cin >> a >> x;
    if (a == 1){
      m.insert(x);
    }else if (a == 2){
      cin >> k;
      auto it = m.upper_bound(x);
      bool flag = 1;
      for (int i = 1; i <= k && flag; i++){
        if (it == m.begin()){
          flag = 0;
          break;
        }
        it--;
      }
      if (flag){
        cout << *it << "\n";
      }else {
        cout << "-1\n";
      }
    }else {
      cin >> k;
      auto it = m.lower_bound(x);
      bool flag = it != m.end();
      for (int i = 1; i < k && flag; i++){
        if (it == prev(m.end())){
          flag = 0;
          break;
        }
        it++;
      }
      if (flag){
        cout << *it << "\n";
      }else {
        cout << "-1\n";
      }
    }
  }
  return 0;
}


---

## 作者：hz20210123 (赞：1)

## [传送门](https://www.luogu.com.cn/problem/AT_abc241_d)


## 题目大意

一共有三种操作，分别是：

- 向序列中插入数 $x$。

- 输出序列中所有 $\le x$ 的元素中的第 $k$ 大值。如果不存在输出 $-1$。

- 输出序列中所有 $\ge x$ 的元素中的第 $k$ 小值。如果不存在输出 $-1$。


## 知识简介 & 题意分析

本题可以使用 `set` 以及二分查找函数。

- `set` 属于 C++ 标准模板库 （STL），意为集合。`set` 中的元素自动去重且由小到大自然有序。不过由于本题要求输出所有满足条件的元素，因此不需要去重，可使用多重集合 `multiset`。

- `lower_bound` 和 `upper_bound` 使用于已经有序的序列中，返回地址指针。`lower_bound(x)` 返回 $\ge x$ 的最小位置，`upper_bound(x)` 返回 $> x$ 的最小位置。


## 注意事项

数值较大，要开 `long long`!

## 代码实现

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,x,pos,cnt;
multiset<int> a;
multiset<int> ::iterator it;//注意类型 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	while(n--){
		cin>>cnt>>x;
		if (cnt==1) a.insert(x);
		else if (cnt==2){
			cin>>pos;
			multiset<int> ::iterator it=a.upper_bound(x);
			while (it!=a.begin()&&pos)
				pos--,it--;
			if (pos!=0)
				cout<<"-1"<<endl;
			else
				cout<<*it<<endl;//注意是指针 
		}
		else{//基本同上 
			cin>>pos;
			multiset<int> ::iterator it=a.lower_bound(x);
			while (it!=a.end()&&pos>1)
				pos--,it++;
			if (it==a.end())
				cout<<"-1"<<endl;
			else
				cout<<*it<<endl;
		}
	}
	return 0;//好习惯 
}
```

到此为止啦。

---

## 作者：loser_seele (赞：1)

题意：给定一个序列，支持插入，查询 $ x $ 及以下第 $ k $ 大的数，查询 $ x $ 及以上第 $ k $ 小的数，$ k \leq 5 $。

去年场上不会 STL，寄了。

因为 $ k $ 很小，启发我们可以使用类似暴力的做法。

在 STL 里有一个自带的容器 multiset，支持对可重集合的 upper_bound，lower_bound，insert 等操作，对于本题是够用的。

对于插入，直接 insert 即可。

对于查询，可以直接 upper_bound 或者 lower_bound 出当前位置，然后暴力减少 $ k $ 并移动下标，如果 $ k $ 到达集合边界的时候仍不为 $ 0 $ 则证明集合内满足条件的数不够 $ k $ 个，无解。否则输出当前 $ k $ 指向的值即可。

时间复杂度 $ \mathcal{O}(m \times (\log{n}+k)) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
multiset<int> st;
signed main() 
{
	int q;
	cin >> q;
	while (q--) 
	{
		int t, x;
		scanf("%lld%lld", &t, &x);
		if (t == 1) 
		st.insert(x);
		else if (t == 2) 
		{
			int k;
			scanf("%lld", &k);
			auto it = st.upper_bound(x);
			while (it != st.begin() && k) 
			{
				k--;
				it--;
			}
			if(k)
			printf("-1\n");
			else
			printf("%lld\n", *it);
		}
		else 
		{
			int k;
			cin >> k;
			auto it = st.lower_bound(x);
			while (it != st.end() && k >= 2) 
			{
				k--;
				it++;
			}
			if (it == st.end())
			printf("-1\n");
			else 
			printf("%lld\n", *it);
		}
	}
}
```


---

## 作者：FurippuWRY (赞：0)

用 `multiset` 以及 `upper_bound()` 和 `lower_bound()` 做此题。

------------

定义一个 `multiset`，命名为 `a`;

- 操作 1：用 `a.insert(x)` 插入元素 $x$； 

- 操作 2：用 `upper_bound()` 查找，然后向前 $k$ 个数，同时判断 $k$ 是否等于 `a.begin()`，若等于，退出循环并且输出 `-1`，否则输出 `a` 中所有小于等于 $x$ 的元素中的第 $k$ 大值。  

- 操作 3：与操作 2 类似，用 `lower_bound()` 查找，然后向后 $k$ 个数，同时判断 $k$ 是否等于 `a.end()`，若等于，退出循环并且输出 `-1`，否则输出 `a` 中所有大于等于 $x$ 的元素中的第 $k$ 小值。  

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

multiset<int> a;

int q, p, x, k;

signed main() {
	cin >> q;
	while (q--) {
		cin >> p >> x;
		if (p == 1) a.insert(x);
		if (p == 2) {
			cin >> k;
			multiset<int>::iterator n = a.upper_bound(x);
			while (n != a.begin() && k) {
				k--;
				n--;
			}
			if (k) cout << -1 << '\n';
			else cout << *n << '\n';
		}
		if (p == 3) {
			cin >> k;
			multiset<int>::iterator n = a.lower_bound(x);
			while (n != a.end() && k > 1) {
				k--;
				++n;
			}
			if (n == a.end()) cout << -1 << '\n';
			else cout << *n << '\n';
		}
	}
	return 0;
}
```

---

## 作者：Soul_Seeker (赞：0)

# AT_abc241_d 题解

前言：STL yyds！

[题~目~传~送~门~](https://www.luogu.com.cn/problem/AT_abc241_d)

## 思路详解

这题可以运用STL中的 `multiset` 来解

简单介绍一下 `multiset`：它可以维护一个多重有序集合（就是它会自动帮你把输入的数排序）

简述一下这题需要知道的函数：

1. `s.insert(a)` 他可以将 $a$ 插入进集合 $s$ 中

2. `s.lower_bound(a)` 他会返回集合 $s$ 中第一个大于等于 $a$ 的 **地址**

3. `s.upper_bound(a)` 他会返回集合 $s$ 中第一个小于等于 $a$ 的 **地址**

就这么多，没了。

知道了这几个函数，这题目就好写多了。

**注：不开 long long 见祖宗**

## 代码展示

```cpp
#include <bits/stdc++.h>
using namespace std;
long long q, x, k, temp;
multiset<long long> a;
int main() {
	cin >> q;
	while (q--) {
		cin >> temp >> x;
		if (temp == 1) a.insert(x);//插入
		else if (temp == 2) {
			cin >> k;
			auto sum = a.upper_bound(x);//查找
			while (sum != a.begin() && k)k--, sum--;//因为已经有序，所以直接移动即可
			if (k)cout << "-1" << endl;
			else cout << *sum << endl;//由于是地址，所以要转换
		} else {
			cin >> k;
			auto sum = a.lower_bound(x);//查找
			while (sum != a.end() && k > 1)k--, sum++;//和上面的一样
			if (sum == a.end())cout << "-1" << endl;
			else cout << *sum << endl;
		}
	}
	return 0;//完结撒花~
}
```

---

## 作者：Crasole (赞：0)

## 思路

使用 STL 中的 multiset 来做。

### 操作 $1$：

直接将 $x$ 插入即可。

### 操作 $2$：

先用 `upper_bound(x)` 到指定位置，接着再往前数 $k$ 个数，注意要判断位置如果在 `s.begin()` 那就不能往前了。输出时判断有没有 $k$ 个数即可，如果没有输出 `-1`。

### 操作 $3$：

先用 `lower_bound(x)` 到指定位置，接着往后扫，**注意：`lower_bound(x)` 时得到元素是所有大于等于 $x$ 的元素中的最大值，因此要少往后扫一次**，注意要判断位置如果在 `s.end()` 那就不能往后了。输出时判断当前位置是不是 `s.end()` 即可，如果是输出 `-1`。

$x \le 10^{18}$，要开 `long long`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
multiset <int> s;
int Q, opt, k, x;
signed main(){
	cin >> Q;
	while(Q--) {
		cin >> opt >> x;
		if(opt == 1)
			s.insert(x);
		else if(opt == 2) {
			cin >> k;
			multiset <int>::iterator now = s.upper_bound(x);//找到位置
			while(now != s.begin() && k)//往后k个数
				k--, now--;
			cout << (k ? -1 : *now) << endl;//如果k>0说明前面没有k个数
		}
		else {
			cin >> k;
			multiset <int>::iterator now = s.lower_bound(x);
			while(now != s.end() & k > 1)//注意少一次
				k--, now++;
			cout << (now == s.end() ? -1 : *now) << endl;//now == s.end()说明后面没有没有了
		}
	}
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc241_d)

## 思路

用 STL 里 multiset 和其自带的二分函数来做此题。

读入数据后，分类讨论操作的种类。

**对于操作 $1$**：直接在集合中加入即可。

**对于操作 $2$**： 用 ``upper_bound`` 函数，二分查找到第一个**比它大的数**的位置，然后往前枚举 $k$ 个数，输出即可。当现在的位置等于 ``begin()`` 的时候，说明前面**没有** $k$ 个，退出循环输出 ``-1``。

**对于操作 $3$**：用 ``lower_bound`` 函数，二分查找它的位置，然后往后枚举 $k$ 个数，输出即可。当找到现在的位置是 ``end()``，说明后面**没有** $k-1$ 个（因为 ``end()`` 是**没有**值的），退出循环输出 ``-1``。

- $1\le x\le 10^{18}$，记得开 long long。

这里不放代码了，对照上面的逻辑一步步写即可。

---

