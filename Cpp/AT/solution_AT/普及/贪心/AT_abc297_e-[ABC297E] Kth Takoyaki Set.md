# [ABC297E] Kth Takoyaki Set

## 题目描述

AtCoder 王国出售 $N$ 种类的章鱼烧。第 $i$ 种章鱼烧的价格是 $A_i$ 日元。
高桥一共买了 $1$ 个以上的章鱼烧。这个时候，也允许买多个同样的章鱼烧。
高桥君可以支付的金额中，请从便宜的一方寻求第 $K$ 的金额。但是，如果存在多个支付相同金额的方法，则只计算$ 1 $个。

## 说明/提示

### 约束条件
- $ 1\ \le\ N\ \le\ 10 $
- $ 1\ \le\ K\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
- 所有输入均为整数
### Sample Explanation 1
AtCoder王国出售的4个种类的章鱼烧，分别是$ 20 $日元、$ 25 $日元、$ 30 $日元、$ 100 $日元。高桥君支付的金额可能是，从便宜的一方列举$ 6 $个的话，$ 20 $日元，$ 25 $日元，$ 30 $日元，$ 40 $日元，$ 45 $日元，$ 50 $日元。因此，答案是$ 50 $个日元。请注意总共需要买$ 1 $个以上的章鱼烧。
### Sample Explanation 2
请注意，即使有几种相同金额的购买方法，也不要重复计算。

## 样例 #1

### 输入

```
4 6
20 25 30 100```

### 输出

```
50```

## 样例 #2

### 输入

```
2 10
2 1```

### 输出

```
10```

## 样例 #3

### 输入

```
10 200000
955277671 764071525 871653439 819642859 703677532 515827892 127889502 881462887 330802980 503797872```

### 输出

```
5705443819```

# 题解

## 作者：lottle1212 (赞：12)

# [原题传送门](https://www.luogu.com.cn/problem/AT_abc297_e)
## Part0：
先解读一下题目。

- 给出两个整数 $N$ 和 $K$ $(1 \leq N \leq 10, 1 \leq K \leq 2 \times 10 ^ {5})$。

- 再给出 $N$ 个整数 $A _ {i}$ $(1 \leq A _ {i} \leq 10 ^ {9})$。

- 这些大小为 $A _ {i}$ 的 $N$ 个整数各有无限个，请求出将这些数**任意组合**后所得和的第 $K$ 小值。

输入：

```
4 6
20 25 30 100
```

输出：

```
50
```

前 $6$ 小的和分别为 `20 25 30 40 45 50`，因此输出 `50`。
## Part 1：
当看到 $1 \leq N \leq 10$，便容易想到使用 `set` 的暴力做法。

我们可以建立两个 `set` 容器，用 $s$ 来保存前 $K$ 小的答案，用 $tmp$ 来保存预存的数据。

首先，我们在 $tmp$ 内存入 $N$ 个整数，然后进行宽搜。对于 $tmp$ 内的最小值，将它加入容器 $s$ 中，再对该值枚举接下来可能出现的新答案，存入 $tmp$ 中。

**AC Code：**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mxn = 10;
const ll N = mxn + 10;
set<ll> s, tmp;//定义set
ll n, k, fx, a[N];
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for(ll i = 1; i <= n; ++ i) cin >> a[i];
	for(ll i = 1; i <= n; ++ i) tmp.insert(a[i]);//初始化
	while(s.size() <= k) {
		s.insert(* tmp.begin()); fx = * tmp.begin(); tmp.erase(tmp.begin());//将tmp中的最小值加入s中
		for(register int i = 1; i <= n; ++ i) tmp.insert(fx + a[i]);//枚举答案
	}
	for(ll i = 1; i < k; ++ i) s.erase(s.begin());//删除前k-1个
	cout << *s.begin() ;//输出第k个
	return 0;
}
```


---

## 作者：封禁用户 (赞：5)

# 题目大意

给定 $n$ 个物品，每个物品有一个重量 $a_i$，每一个物品都有无限个。

现在你可以去一些物品，将取出来的重量排序，问你第 $k$ 小的重量是什么。



# 样例解释

样例 ：

```
4 6
20 25 30 100
```

输出:

```
50
```

原因：

取第一个物品，重量为 $20$;

取第二个物品，重量为 $25$;

取第三个物品，重量为 $30$;

取两个第一个物品，重量为 $40$;

取第一个和第三个物品，重量为 $45$;

取第一个和第三物品，重量为 $50$;

因此，第 $6$ 小的重量就是 $50$。

# 思路

首先每种物品可以取很多次，说明普通 $dp$ 会炸。

我们可以考虑第 $k$ 小和第 $k - 1$ 小（假设第 $k - 1$ 重量为 $x$）的关系：

当前第 $k$ 小的就是再取了一个物品，当前第 $k$ 小重量就是 $x + a_i(i \in [1, n])$。

所以我们可以用一个 $\operatorname{set}$ 去维护整个重量，每次取出这个 $\operatorname{set}$ 中最小的数，即第一个数，将这个数加上 $a_i(i\in[1,n])$，在放回 $\operatorname{set}$ 中，我们再把最小的数删除。	

正确性证明：

我们每次我们是取 $\operatorname{set}$ 中最小的数来更新，但是最小的值是不会重复的，所以每次我们都至少能拓展出一个没有出现过的值。

我们将这个操作做 $k$ 次，那么答案一定能拓展出来。

# AC 代码

```cpp
/*****************************************
备注：
******************************************/
#include<queue>
#include<math.h>
#include<stack>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<iomanip>
#include<map>
#include<string.h>
#include<set>	
#include<algorithm>
using namespace std;
#define int long long
const int MAXN = 1e5 + 10;
const int MR = 10 + 5;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
int n, k, a[MAXN];
set<int> s;
signed main()
{
	cin >> n >> k;
	for(int i = 1;i <= n; i++)
	{
		cin >> a[i];
	}
	s.insert(0);
	for(int kkk = 1;kkk <= k; kkk++)
	{
		for(int i = 1;i <= n; i++)
		{
			s.insert(*s.cbegin() + a[i]);
		}
		s.erase(*s.begin());
	}
	cout << *s.cbegin();
	return 0;
}
```

~~我寻思着，我哪里有中文句子和标点符号有空格~~

---

## 作者：2c_s (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc297_e)

# 思路

暴力枚举的思路，最多要排序 $2\times 10^5$ 次，肯定会超时。所以我们采用 STL 中的 **set** 来做此题。

定义一个 set 类型的变量 $st$。读入数组后，循环遍历 $k-1$ 次，每次找 $st$ 中的最小值并和数组中的每个数相加。相加后在 $st$ 中删去原来的数，最后输出 $st$ 的第一个数字即为第 $k$ 小的数。

**证明**：每次在 $st$ 中删去最小的数，删去 $k-1$ 次后 $st$ 的第一个数一定为第 $k$ 小的数。

- 极限情况数据可以达到 $2\times 10^{14}$ 的规模，别忘开 long long。

- 最后别忘输出换行。

# AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=20;
int n,k,a[N];
set<ll>st;
int main(){
	cin>>n>>k;
	k--;
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
		st.insert(a[i]);
	}
	while(k--){
		ll p=*st.begin();//别忘考虑指针。
		st.erase(p);
		for(int i=1;i<=n;++i)st.insert(a[i]+p);
	}
	cout<<*st.begin()<<endl;
	return 0;
}
```

---

## 作者：Fire_flame (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc297_e)

## $\mathtt{Solution}$

不知道为什么大家都用 `set`。

我们可以使用一个小根堆，在广搜的过程中选一个最小的数加上 $a_1,a_2\dots a_n$，然后再放回去。

另外再开一个 `map` 记录放到小根堆里面的数是否被遍历过了，如果有就不放，没有就放进去。

时间复杂度 $O(kn\log k)$，可以通过此题。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define int long long
using namespace std;
const int MAXN = 15;
int n, m, ans, a[MAXN];
map<int, bool>mp;
int bfs(){
	priority_queue<int, vector<int>, greater<int> >pq;
	for(int i = 1;i <= n;i ++){
		if(mp[a[i]])continue;
		pq.push(a[i]);
		mp[a[i]] = 1;
	}
	while(!pq.empty()){
		ans ++;
		int t = pq.top();
		if(ans == m)return t;
		pq.pop();
		for(int i = 1;i <= n;i ++){
			if(mp[t + a[i]])continue;
			mp[t + a[i]] = 1;
			pq.push(t + a[i]);
		}
	}
	return 0;
}
signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i = 1;i <= n;i ++)scanf("%lld", &a[i]);
	printf("%lld", bfs());
	return 0;
}
```


---

## 作者：Butterfly_qwq (赞：1)

首先要用一个 set。

第一步，把 $0$ 加入 set。

第二步，循环 $k$ 次，把队首 $l$ 弹出，循环每一个价格（$A_1,A_2\dots A_n$），把 $l+A_i$ 插入 set。

循环完成之后此时的队首就是答案。

Code:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[11];
set<int> s;
signed main()
{
	int n,k;
	cin>>n>>k;
	for(int i=0;i<n;i++)cin>>a[i];
	s.insert(0);
	for(int i=0;i<k;i++)
	{
		int w=*(s.begin());
		s.erase(s.begin());
		for(int j=0;j<n;j++)s.insert(w+a[j]);
	}
	cout<<*(s.begin());
	return 0;
}
```

---

## 作者：2huk (赞：1)

## 题目描述

有 $N$ 种物品，第 $i$ 种物品的价格为 $A_i$，每种物品有无限个。

现在要选择一些物品，每种物品可以不选或选若干个。问如果这样选择总价格第 $K$ 小是多少。

## 样例输入输出

```input1
4 6
20 25 30 100
```

```output1
50
```

前 $6$ 小的价格分别是 $20,\ 25,\ 30,\ 40,\ 45,\ 50$。

## 数据范围

$1 \le N \le 10,\ 1 \le K \le 2 \times 10^5,\ 1 \le A_i \le 10^9$

## 分析

从样例入手。

最开始每种物品的价格分别是 $20\ 25\ 30\ 100$。

加下来我们会在这个序列中每次取出最小值删掉，并在数列中加上这个最小值与所有原价格的搭配。那么取得第 $K$ 次就是最终答案。

首先取出最小值 $20$，再在数列中加入 $20+20\ ,25+20,\ 30+20\ ,100+20$，那么此时这个数列就变成：$25,\ 30,\ 100,\ 40,\ 45,\ 50,\ 120$。

继续操作，再次取出最小值 $25$，并在数列中加入 $20+25,\ 25+25,\ 30+25,\ 100+25$，那么此时这个数列就变成：$30,\ 100,\ 40,\ 45,\ 50,\ 120,\ 45,\ 50,\ 55,\ 125$。由于题目要求重复只计算一次，所以要把重复元素去掉。即 $30,\ 100,\ 40,\ 45,\ 50,\ 120,\ 55,\ 125$

这样重复 $K$ 次，第 $K$ 次取出的元素就是答案。

推广到一般情况，这个问题该如何实现呢？

由于上述操作中存在 `取最小值` 和 `去重` 的操作，那么我们可以直接定义集合 `set` 存储数据，每次取出集合最小值并依次插入，根据上述操作执行即可。

## 代码

```cpp
#include <iostream>
#include <set>

using namespace std;

typedef long long LL;

int n, k, a[12];
LL t;			// t 表示当前集合中的最小值 
set<LL> s;		// 存储价格的集合 

int main()
{
	// 读入 
	cin >> n >> k;
	
	for (int i = 1; i <= n; i ++ )
	{
		cin >> a[i];
		s.insert(a[i]);		// 初始化集合，将所有价格加入 
	}
	
	while (k -- )		// k 次操作，第 k 次得到的最小值就是最终答案 
	{
		t = *s.begin();		// 取当前最小值 
		s.erase(t);			// 删除 
		// 插入 t 与所有原价格的搭配
		for (int i = 1; i <= n; i ++ )
		{
			s.insert(t + a[i]);
		}
	}
	
	cout << t;		// 输出答案 
	
	return 0;
}
```

---

## 作者：guanyf (赞：0)

### 题意
- 有个人有 $N$ 种不同面值的货币 $A_i$，每种货币可以用无限次。现在求出他能凑出的第 $K$ 小的金额。

- $1 \le K \le 2  \times 10^5$

### 导入
可以想到一个非常暴力的思路：用 `set` 记录当前的金额，然后暴搜找到所有状态，虽然每个货币可以用无限次，但是实际上只有 $\le K$ 才对答案有影响。因此是可以计算出答案的。

由于上一个算法并不好优化，因此需要找到题目的突破点。

### 分析、思路
由于 $K \le 2 \times 10^5$，因此可以从 $K$ 入手。由于 `set` 自带去重排序功能，因此我们只需要重复 $K-1$ 此操作就可以找到答案。对于当前第 $i$ 小的数 $x$ 来说，显然可以把所有把 $x+A_i(1 \le i \le N)$ 都放进 `set` 中。很容易就会想到证明正确性的方法：由于每次取出的都是当前第 $i$ 小的，因此它加上所有 $A_i$ 中最小的一定就会因为 `set` 的特性变成不会使答案变劣的数。以此类推，都是这样。

时间复杂度：$\operatorname{O}(NK)$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
set<int> st;
int n, k, a[100];
signed main() {
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    st.insert(a[i]);
  }
  for (auto i : st) {
    if (!(--k)) {
      cout << i, exit(0);
    }
    for (int j = 1; j <= n; j++) {
      st.insert(i + a[j]);
    }
  }
  return 0;
}
```


---

## 作者：zajasi (赞：0)

## 题意
给定 $n$ 个数。你可以去若干个数，每个数无限次取。问所凑出来的所有数中第 $k$ 小的是谁？重复的算一个。
## 解题思路
这道题其实就是丑数的加法版本。跟丑数一样，我们维护 set。对于每一个数，我们将其取出，删掉该数，然后将该数分别加上所有原先的数扔进去。刚开始，set 里有一个 $0$。
## AC 代码
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
int n,k,c,x;
int a[11];
multiset<int> s;
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    s.insert(0);//刚开始是 0
    for(int i=1;i<=k+1;i++){
        x=*s.begin();
        s.erase(x);//删
        for(int j=1;j<=n;j++){
            s.insert(x+a[j]);//加
        }
    }
    cout<<x;
    return 0;
}

```

---

## 作者：FL_sleake (赞：0)

## 题意简述

给定 $ n $ 件商品，第 $ i $ 件商品的价格为 $ A_i $，选一些商品可以组成一些价格，同一件商品可被重复选择任意多次。问这些价格中第 $ k $ 大的是多少。

## Solution

注意一个细节，题目注重的仅仅是价格，而非方案，因此 **多种不同的选择方案得到的同一个价格只算一次。** 基于这个性质，使用 set 自带的去重功能来解决此题。

考虑到 $ n $ 很小，只有 $ 10 $，因此可以每次把最小的价格取出来，依次加上每个 $ A_i $ 再放回去，重复 $ k-1 $ 次后 set 内的第一个元素即为答案。初始化将每个 $ A_i $ 都放入 set 内，保证不漏算价格。总复杂度为 $ O(NK) $。

## 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//注意long long
ll n,k,a[200010];
set<ll> s;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],s.insert(a[i]);
	//set中此时已有第1小的价格，因此重复k-1次可得到第k小的价格
   	for(int i=1;i<=k-1;i++){
		ll num=*s.begin();
		s.erase(num);
		for(int j=1;j<=n;j++) s.insert(num+a[j]);
	}
	cout<<(*s.begin())<<endl;
	return 0;
}
```

---

