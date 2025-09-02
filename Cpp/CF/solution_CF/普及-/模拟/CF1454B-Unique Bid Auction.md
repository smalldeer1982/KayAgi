# Unique Bid Auction

## 题目描述

There is a game called "Unique Bid Auction". You can read more about it here: <a>https://en.wikipedia.org/wiki/Unique\_bid\_auction</a> (though you don't have to do it to solve this problem).

Let's simplify this game a bit. Formally, there are $ n $ participants, the $ i $ -th participant chose the number $ a_i $ . The winner of the game is such a participant that the number he chose is unique (i. e. nobody else chose this number except him) and is minimal (i. e. among all unique values of $ a $ the minimum one is the winning one).

Your task is to find the index of the participant who won the game (or -1 if there is no winner). Indexing is $ 1 $ -based, i. e. the participants are numbered from $ 1 $ to $ n $ .

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
2
1 1
3
2 1 3
4
2 2 2 3
1
1
5
2 3 2 4 2
6
1 1 5 5 4 4```

### 输出

```
-1
2
4
1
2
-1```

# 题解

## 作者：Thomas_Cat (赞：7)

此题比较简单。

只需要找到：

- 有一个的数字

- 这个数字的下标

- 所有数字的最大值

- 所有数字的最小值

---

之后我们对整个数组进行遍历，找到最小值也就是所有符合上述条件的最小值即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
	cin>>t;
	while(t--){
	    int n,a[100005],v[100005]={0},number[100005]={0},MIN=INT_MAX,MAX=0,flag=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			v[a[i]]++,number[a[i]]=i,MIN=min(MIN,a[i]),MAX=max(MAX,a[i]);
		}
		for(int i=MIN;i<=MAX;i++)
			if(v[i]==1) {
				cout<<number[i]<<endl;
				flag=1;
				break;
			}
		if(flag==0) cout<<-1<<endl;
	}
	return 0;
}

```

---

## 作者：dapingguo8 (赞：3)

### 题意

定义一个数组的“独特数”为在该数组中只出现了一次的数。

给定一个长度为$n$的数组$A$，求其最小“独特数”所在下标（若没有独特数，输出`-1`）。

$1\le n \le 2\times10^5$，$1\le A_i \le n$.

### Solution

记录每个数 $x$ 在 $A$ 中出现的次数 $cnt_x$ 。从 $1$ 至 $n$ 枚举 $y$ ，若 $cnt_y=1$ ，则 $y$ 为数组 $A$ 的最小“独特数”。如果不存在 $y$ 使得 $cnt_y=1$ ，代表数组 $A$ 不存在独特数。

但是题目要求求出最小独特数所在下标，所以记录每个数 $x$ 在 $A$ 中最后一次出现的位置 $pos_x$ 。因为所求独特数 $y$ 在 $A$ 中只出现一次，所以 $pos_y$ 便为其在 $A$ 中的位置。

统计元素的数量及位置可以用`map`实现，也可以直接使用数组统计。

时间复杂度 $O(n\log n)$ （使用`map`)或 $O(n)$ （数组统计）

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		map<int,int>cnt,pos;
		int n;
 		cin>>n;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			cnt[x]++;
			pos[x]=i;
		}
		int ans=-1;
		for(auto it:cnt){
			if(it.second==1){
				ans=pos[it.first];
				break;
			}
		}
		cout<<ans<<endl;
	}
}

```

---

## 作者：daiarineko (赞：2)

## 0. 题目概述

每一组数据中，我们要找出与众不同的数据里最小的一个（如果一个数出现的次数为 `1`，就是与众不同的）。

如果没有任何数与众不同，输出 `-1`，否则输出数据的编号（从`1`开始）。

## 1. 解法
### 结构体
这道题我们采用结构体的方式来存储。

结构体怎么写呢？我们首先分析一下题目，发现：如果一个数与众不同，那么这个数必定只有一个人选择 ~~（废话连篇）~~，那么我们就可以直接去存储最后一个选这个数的人的编号，因为如果有多个人选，这个数就会被判断选择次数的部分 pass 掉，不会改变结果；而如果只有一个人选，数据也不会出错。

结构体：
```cpp
struct participant{
	int winner;//选择的人的编号
	int count;//选择次数
}ns[200040];//n in [1,200000]
```

### 输入部分

输入的时候，我们要同时记录选择者编号和选择次数，所以循环内容就是：
```cpp
int c;
cin>>c;
ns[c].winner=i+1;//输出编号从1开始，所以要+1（循环变量从0开始）
ns[c].count++;
```

### 计算 & 输出部分

计算的时候，我们从 `1` 开始检查每个数，如果某个数的选择次数为 `1`，那么就保存一个变量并退出循环；循环结束后输出这个变量（变量初始值为 `-1`，节省一次特判）

代码：
```cpp
int winner=-1;//胜利者编号
for(int i=1;i<=200000;i++){
	if(ns[i].count==1){
		winner=ns[i].winner;
		break;//否则会出错
	}
}
cout<<winner<<endl;
```

## 2. 注意事项

* 每个测试点有多组数据，别忘了先输入数据个数！
* 注意重置结构体数组（memset）！
* 别忘了加 `cstring` 和 `sync_with_stdio` ！
* AC Code 加入了优化（用 `mx` 存储输入的最大值，计算时可以不用遍历至200000）！


## 3. AC Code

```cpp
#include <iostream>
#include <cstring>
using namespace std;

struct participant{
	int winner;//选择的人的编号
	int count;//选择次数
}ns[200040];//n in [1,200000]
int main(){
	ios::sync_with_stdio(false);
	int t,n;
	cin>>t;
	for(int i=0;i<t;i++){
		int mx=0;
		cin>>n;
		memset(ns,0,sizeof(ns));//重置数组
		for(int i=0;i<n;i++){
			int c;
			cin>>c;
			ns[c].winner=i+1;//输出编号从1开始，所以要+1（循环变量从0开始）
			ns[c].count++;
			mx=max(mx,c);//优化
		}
		int winner=-1;//胜利者编号
		for(int i=0;i<=mx;i++){
			if(ns[i].count==1){
				winner=ns[i].winner;
				break;//否则会出错
			}
		}
		cout<<winner<<endl;
	}
	return 0;
}


```

---

## 作者：PLDIS (赞：1)

这道题有一个点比较坑人：**每次询问这些唯一的元素中最小的元素的下标**。

我们可以开几个桶，让他们存两个数：**这个数出现的次数和这个数最后一次出现的下标（反正我们只要找出现次数为 $1$ 的数的下标）。**

最后，我们从小到大遍历每个桶，只要遇到一个只出现一次的数，就输出它的下标，因为它是要输出唯一的元素中最小的元素的下标。（注意，它的第一个数的下标是 $1$）

最后的最后，我们要看我们在之前有没有找到符合要求的数，如果没有，就输出 $-1$。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int bucket[n + 10][2] = {0}; //开桶
        for(int i = 0;i < n;i++){
            int b;
            cin >> b;
            bucket[b][0]++;
            bucket[b][1] = i;
        }
        bool flag = false;
        for(int i = 1;i <= n;i++){
            if(bucket[i][0] == 1){
                cout << bucket[i][1] + 1 << endl;
                flag = true;        //标记已经找到了这样的数
                break;
            }
        }
        if(!flag){
            cout << -1 << endl;
        }
    }
    return 0;
}
```

---

## 作者：Fan_Tuan (赞：1)

# 题意
给定一个长度为$n$ 的序列$a$,对于序列中的每一个元素， 如果它在序列中只出现过一次， 那么我们称它为唯一的， 询问在这些唯一的元素中最小的元素的下标。

# 思路
用一个$pair$类型的优队存储每一个元素的值与下标， $vis$数组记录当前$a_i$是否在队列中， 如果不在， 则放入队列中，否则$vis_{a_i}$++。处理完序列$a$后，我们只需要寻找当前队列中第一个$vis$=1的元素的下标即可。

# 代码
```
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue>
// #define d lld
// #define int long long
using namespace std;

const int maxn = 2e5 + 10;
int t, n, vis[maxn];
 
signed main () {
    scanf ("%d", &t);
    while (t--) {
        memset(vis, 0, sizeof vis);
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
        scanf ("%d", &n);
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            if (vis[x] == 0) vis[x] = 1, q.push(make_pair(x, i));
            else vis[x]++;
        }
        int flag = 0;
        while (!q.empty()) {
            int p = q.top().first;
            int id = q.top().second;
            q.pop();
            if (vis[p] != 1) continue;
            else {
                printf ("%d\n", id);
                flag = 1;
                break;
            }
        }
        if (flag == 0) puts("-1");
    }
    return 0;
}
```


---

## 作者：yzy1 (赞：1)

题目大意
---

共 $t (t\le2\times10^4)$ 组数据,
对于每组数据输入一个整数 $n (1 \le n \le 10^5)$
和一个长度为 $n$ 的数组 $a(1\le a_i \le n)$.
请找到数组中只出现过一次且最小的数**的下标** (从 $1$ 开始),
如果找不到这样的数则输出 $-1$.

对于所有测试点满足 $\sum_n \le 10^5$.

做法
--

使用 `std::vector` 开桶, 统计每个数字在数组中出现的位置, 然后 $\mathcal O(n)$
扫一遍, 找到最小的符合要求的数即可.

Code
---

```cpp
int t, n;
std::vector<int> sum[N];
int main() {
  scanf("%d", &t);
  while (t--) {
    bool fl = false;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      int x;
      scanf("%d", &x);
      sum[x].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
      if (sum[i].size() == 1) {
        printf("%d\n", sum[i][0]);
        fl = true;
        break;
      }
    }
    if (!fl) puts("-1");
    for (int i = 1; i <= n; i++) {
      sum[i].clear();
    }
  }
  return 0;
}
```

---

## 作者：happybob (赞：0)

没有用 `STL`的吗？

我用的是自动排序的 `set` 与 当作桶的 `unordered_map`，然后枚举一遍原来的数组，最终输出下标。

这里介绍了一个不太好但是很有用的东西：`goto`，是无条件跳转语句，虽然功能强大，但有点……反正用得比较少，通常用 `bool` 判断是否执行接下来的而不是用 `goto` 直接调到语句后面。

其使用方法：

```cpp
goto S;
cout << "not AKIOI\n";
S:
cout << "AKIOI\n";
```
输出： `AKIOI`

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;

unordered_map<int, int> mp;

int a[200005];

int main()
{
    ios::sync_with_stdio(false);
    register int T;
    cin >> T;
    while(T--)
    {
        mp.clear();
        set<int> st;
        int n;
        cin >> n;
        for(register int i = 1; i <= n; i++)
        {
            cin >> a[i];
            mp[a[i]]++;
        }
        unordered_map<int, int>::iterator last = mp.end();
        for(register unordered_map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
        {
            if(it -> second == 1) st.insert(it -> first);
        }
        int value = *(st.begin());
        for(register int i = 1; i <= n; i++)
        {
            if(a[i] == value) {cout << i << endl; goto G;}
        }
        cout << "-1\n";
        G:{} //这里一定要加花括号，不然会CE
    }
    return 0;
}
```

这里使用到了一个 `register`，其意思为寄存器，这种类型修饰的变量访问更快，但已经在 `c++17` 中移除了……

---

## 作者：gonghw (赞：0)

~~作为蒟蒻stl啥的我也不会用~~
来一发简单桶，用题目条件数据做优化。
```cpp
#include<bits/stdc++.h>
#define int ll
#define ll long long
#define fp for(int i=1;i<=n;i++)
const ll N = 2e6;
using namespace std;

ll t;
ll n;
ll a[N],b[N];

void solve()
{
	cin>>n;
	fp b[i]=0;
	ll max=0;
	fp
	{
		cin>>a[i];
		if(a[i]>max) max=a[i];
		b[a[i]]++;
	}
	ll num=0;
	for(int i=1;i<=max;i++)   //max卡一下时间
	{
		if(b[i]==1)
		{
			num=i;
			break;
		}
	}
	if(!num) cout<<-1<<endl;
	else
	{
		fp
		{
			if(a[i]==num)
			{
				cout<<i<<endl;
				break;
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin>>t;
	while(t--) solve();
	return 0;
}
```
桶来找不是重复的数，再遍历一遍数列找到该数的下标输出即可


---

## 作者：Eason_AC (赞：0)

## Content
给定一个长度为 $n$ 的数列 $\{a_i\}_{i=1}^n$，请找出在数列中仅出现一次的最小的数的位置。

**数据范围：$t$ 组询问，$1\leqslant t\leqslant 10^4,1\leqslant a_i\leqslant n\leqslant 2\times 10^5,\sum n\leqslant 2\times10^5$。**
## Solution
边输入边统计这些信息：

- 这个数出现的次数。
- 这个数出现的位置。
- 所有数的最小值。
- 所有数的最大值。

然后从所有数的最小值到最大值直接遍历一遍，找到的第一个只出现一遍的数的位置就是我们当前这组询问的答案了。如果都不符合要求直接输出 $-1$ 就好。
## Code
```cpp
int t, n, a[200007];

int main() {
	t = Rint;
	while(t--) {
		int vis[200007] = {0}, id[200007] = {0}, minx = 0x3f3f3f3f, maxx = 0, flag = 0;
		n = Rint;
		F(i, 1, n) {
			a[i] = Rint;
			vis[a[i]]++, id[a[i]] = i, minx = min(minx, a[i]), maxx = max(maxx, a[i]);
		}
		F(i, minx, maxx)
			if(vis[i] == 1) {
				printf("%d\n", id[i]);
				flag = 1;
				break;
			}
		if(!flag) puts("-1");
	}
	return 0;
}

```

---

