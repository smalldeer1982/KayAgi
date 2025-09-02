# [JOIGST 2025] 扑克 / Poker

## 题目描述

比太郎有 $N$ 张扑克牌，编号为 $1$ 到 $N$。每张扑克牌都有一个正整数，扑克牌 $i$ 上的正整数为 $A_i$。

将满足以下条件的包含 $K$ 张扑克牌的牌组称为“顺子”：

- 将这些扑克牌按照牌上的正整数从小到大排序后，任意相邻两张牌上的正整数差为 $1$。

判断比太郎是否能从 $N$ 张扑克牌中选出 $K$ 张，使这 $K$ 张牌组成的牌组为一个顺子。

## 说明/提示

#### 【样例解释 #1】

可以选择 $K=2$ 张扑克牌 $1,3$，牌上的正整数分别为 $1,2$，组成了一个顺子。

该样例满足所有子任务的限制。

#### 【样例解释 #2】

没法选出 $K=4$ 张扑克牌使其组成一个顺子。

该样例满足子任务 $2,3$ 的限制。

#### 【数据范围】

- $2 \le N \le 3\times 10^5$；
- $2 \le K \le N$；
- $1 \le A_i \le 10^9(1 \le i \le N)$。

#### 【子任务】

1. （$30$ 分）$K=2$；
2. （$30$ 分）$A_i\le 3\times 10^5(1\le i\le N)$；
3. （$40$ 分）无附加限制。

## 样例 #1

### 输入

```
5 2
1 1 2 4 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
7 4
1 1 2 3 3 5 6```

### 输出

```
No```

# 题解

## 作者：2023z (赞：4)

[link](https://www.luogu.com.cn/problem/P13733)

### 题意

给我们 $ n $ 张牌，问是否能从这 $ n $ 张牌中选出 $ k $ 张组成一个顺子。打过扑克牌的应该都知道顺子是什么东西吧。顺子的定义就是在打出的牌中，每一张都是前一张牌的数字加上一。

### 思路

我提供一个比其他题解麻烦的思路，想看更简便的可以绕路。要组成顺子的牌肯定是从小到大依次递增 $ 1 $ 的，所以我们要对数组进行排序，然后去找每一段顺子，每遇到一个不是前一个数字加一的就截断，然后找下一段顺子。对于一段还没结束的顺子，每次都要判断长度是否等于 $ k $，因为一段顺子也可以从中间断开出牌。

但现在还有一个要注意的点，看这组数据：

```cpp
5 3
1 2 2 3 9
```

在第二个 $ 2 $ 的时候，这段顺子被断开了，又重新开始统计，最后的输出答案是 `No`，实际上 $ 1, 2, 3 $ 可以组成一个长度为 $ 3 $ 的顺子，所以我们还要对数组进行去重，注意 $ a $ 数组的数据范围是 $ 1 \leq a_i \leq 10^9 $。所以去重就出现了两种方法，一种用 map 定义一个桶去重，另一种去重方式用自带去重函数 unique。

使用 map 的代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k, a[300010];
map<int,int> mp;
signed main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    a[0] = a[1] - 1; //第一张可以组成顺子
    int s = 0; //每一段顺子的长度
    for (int i = 1; i <= n; i++) {
        if (mp[a[i]]) continue; //重复的就不要判断
        if (a[i] != a[i - 1] + 1) { //如果这个数不是前一个数加一就断开
            if (s == k) { //记得判断整个顺子长度是不是 k
                cout << "Yes\n";
                return 0;
            }
            s = 0; //断开顺子
        }
        s++; //每一次顺子的长度都要加一
        if (s == k) { //一段顺子也不一定要全部用上
            cout << "Yes\n";
            return 0;
        }
        mp[a[i]] = 1; //这个数已经用过了
    }
    cout << "No\n"; //之前如果可行的话就已经 return 掉了，所以现在一定不行
    return 0;
}
```

用 unique 的代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k, a[300010];
signed main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    int idx = unique(a + 1, a + n + 1) - a - 1; //这个函数可以为数组自动去重，idx 是去重后数组的长度
    a[0] = a[1] - 1;
    int s = 0;
    for (int i = 1; i <= idx; i++) { //注意数组去重后长度变了，所以是到 idx
        if (a[i] != a[i - 1] + 1) { //其他与上份代码相同，不再说明
            if (s == k) {
                cout << "Yes\n";
                return 0;
            }
            s = 0;
        }
        s++;
        if (s == k) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}
```

两个记录

[用 map 的](https://www.luogu.com.cn/record/231463344)

[用 unique 的](https://www.luogu.com.cn/record/231463228)

---

## 作者：little_stickman (赞：3)

# P13733题解
## 主要题意
你有 $n$ 张扑克牌，你要在其中找出 $k$ 张连成一个顺子，问能不能实现。
## 解题思路
我们首先需要将这个数组排序。

然后，再进行判断：

因为你可能会有相同数量的同一张牌，因此如果遇上就可以无视；

如果你现在判断的这张牌的点数是上一张牌加一，那么我们的统计变量就增加一；

否则，就直接将统计变量置为一。（因为无论如何一张牌可以是长度为 $1$ 的顺子）。

在判断过程中，一旦发现统计变量与 $k$ 相等，即代表了可以连成这样的顺子。

这样，我们就完成了这道题目。

主要坑点：

- 统计变量初始置一而不是置零。
- 注意数组减一后下标变为 $0$ 的可能（先将数组下标为 $0$ 的地方置为极大值）。
- 注意重复的扑克牌。
## 上代码！ 
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3 * 1e5 + 10;
int n, k;
int a[MAXN];

int main(void) {
	cin >> n >> k;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	sort(a + 1, a + 1 + n);//重点：排序
	int cnt = 1;
    a[0] = INT_MAX;
	for (int i = 1; i <= n; i ++) {
		a[i] == a[i - 1] + 1 ? cnt ++ : (a[i] == a[i - 1] ? true : cnt = 1);//判断部分
		if (cnt == k) {//与 k 相等了，输出
			cout << "Yes\n";
			exit(0);
		}
	}


	cout << "No\n";
	exit(0);
}
```

---

## 作者：GSQ0829 (赞：2)

### 题目大意：
有一个长度为 $N$ 的序列，分别为 $A_1,A_2,...,A_n$。

选取 $K$ 个数，将这些数按从小到大排序后，任意相邻两数的差为 $1$。

判断该序列是否能够选出 $K$ 个数，满足上述的条件。

---
### 解题思路：
~~这道题的解题思路很简单~~。

首先，要将所有的数都从小到大排序。接下来，从当前的 $A_2$ 开始依次判断：如果这张牌与前一张牌的差为 $1$，说明它满足条件，那么计数器就加一。然后还要判断一下当前的个数是否已经到达了我们的目标个数，那么说明是可以组成条件的，直接输出 `Yes`，结束代码。如果当前的牌不是前一张牌的数加一并且两张牌不相同，那么计数器设回 $1$。如果循环到最后都没有组成答案，那么说明无法成立，就输出 `No`。

这里解释一下为什么两张牌相同就不用设回 $1$：我们先设前一张牌为 $A_1$，当前牌为 $A_2$，下一张牌为 $A_3$。那么如果两张牌相同，$A_1=A_2$，其实有可能 $A_3=A_1+1=A_2+1$，那么此时就满足条件。我们原来选的是 $A_1$ 加入牌堆，此时如果选择了 $A_2$ 加入牌堆，那么还可以带着 $A_3$ 一起加入牌堆，这样个数变得更多了，我们就用 $A_2$ 去代替了 $A_1$，找到了当前的最优解。但是如果不相同，那后面的牌肯定与前一张牌的差距超过 $1$，替换不了它，就得重新改为 $1$。

这样我们就得到了本题的完整思路。这样写下来的复杂度还是不高的，大概在 $O(N \log{N})$，不会超时。

---
### 代码：
接下来给出本题的代码及注释：
```cpp
#include <bits/stdc++.h>
#define int long long // 注意，要开 long long，不然就会超时（不开 long long 见祖宗）
using namespace std;

int a[300001], n, k, ans = 1; // 初始化计数器为 1，默认只有一张牌能组成顺子

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1); // 注意要排序，不然就会有测试点过不了
	for (int i = 2; i <= n; i++) {
		if (a[i] == a[i - 1] + 1) { // 如果当前牌的数是前一张牌的数加一
			ans++; // 那么满足的牌数加一
			if (ans == k) { // 如果这个数量已经等于我们要求的牌数了，那么直接终止循环
				cout << "Yes";
				return 0; // 记得直接结束代码
			}
		} else if (a[i] != a[i - 1]) ans = 1; // 如果不相同，且当前牌的数不是前一张牌的数加一，那么就将计数器重新设为 1
	}
	cout << "No"; 
	return 0;
}
```

---

## 作者：Vct14 (赞：2)

把牌按牌上正整数从小到大排序。用变量 $s$ 存储当前的顺子长度。

遍历每一张牌。若它能与其前面的数组成顺子，那么 $s$ 加一；若它与前一张牌相等，则跳过；否则将 $s$ 赋为 $1$。然后判断此时顺子长度是否达到 $k$，若达到则直接输出 `Yes` 并结束程序。

如果循环完都没有结束程序，那么输出 `No`。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=3e5+2;
int a[N];

int main(){
	int n,k;cin>>n>>k;
	for(int i=1; i<=n; i++) cin>>a[i];
	sort(a+1,a+1+n);int s=1;
	for(int i=2; i<=n; i++){
		if(a[i]==a[i-1]+1) s++;
		else if(a[i]!=a[i-1]) s=1;
		if(s>=k){
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：Doraeman (赞：2)

## 顺子的性质
根据顺子的定义和顺子的组成方式，显然可以得到以下性质：
1. 顺子中所有牌最多使用 $1$ 次；
2. 顺子是有序的。

## 数据处理
根据性质 $1$，我们可以在输入时检查：**如果这个元素出现过，就不必将其加入到 $A$ 序列中**。得到无重复元素的 $A'$ 序列。  
显然这样做不会对结果造成任何影响。

根据性质 $2$，我们可以在将 $A'$ **从小到大排序**，得到有序的无重复元素的 $A''$ 序列。  
这个环节可以**方便我们判断顺子是否存在**。

### 说明解释
事实上，C++ 标准模板库（STL）中有一个容器叫做 ```set```，可以实现以上所有功能。  
但是为了方便接下来的下标处理，我们不使用 ```set```。

## 顺子判断
在有序不重序列 $A''$ 中，如果存在连续的至少 $K$ 个数能满足：
$$
{A''}_i+1={A''}_{i+1}\\
{A''}_{i+1}+1={A''}_{i+2}\\
\dots\ \dots\\ 
{A''}_{i+K-2}+1={A''}_{i+K-1}\\
$$
即**从第二个数开始，每个数等于前一个数加 $1$，一共 $K$ 个数，那么这个子串就是包含 $K$ 个元素的顺子。**

再次观察上式，可以发现，**当 $A$ 序列任意两元素互不相等时，上述判定式可以等价为：** 
$$
{A''}_i+K-1={A''}_{i+K-1}
$$

由此，每次只需要判断下标，就可以判断出是否存在顺子。

## 细节
很有可能遇到 $i+K-1$ 超出 $A''$ 数组下标的情况，会发生数组越界导致 RE，所以需要特殊判断。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;

int n, k, a[N], cnt;
// 判断查重 
map <int, bool> p;

int main(){
    cin >> n >> k;
    for(int i=1; i<=n; i++){
        int x; cin >> x;
        // 如果不重复, 加入x
        if(!p[x]){
            p[x] = 1;
            a[++cnt] = x;
        } 
    }
    // 排序, 到此实现了set的功能 
    sort(a + 1, a + cnt + 1);

    // 检查顺子 
    for(int i=1; i<=cnt; i++)
        // 下标越界, 不检查 
        if(i+k-1 > cnt) continue;
        // 下标判断成功, 是顺子 
        else if(a[i]+k-1 == a[i+k-1]){
            cout << "Yes";
            return 0;
        }
    // 从始至终都没有找到顺子 
    cout << "No";
}
```

---

## 作者：3Luby3 (赞：2)

## 题意分析
给定 $n$ 张牌，判断是否能组成长度为 $k$ 的顺子。

顺子是指两张牌之间的差值为 $1$，且严格递增。

## 思路
顺子既然是有着**严格递增**条件的，那我们不妨给整个数组从小到大排序，满足递增的条件。

然后我们用一个变量 $cnt$ 记录下目前严格递增且差值为 $1$ 的顺子的长度，如果当前的牌与上一张牌的数值一样，这张牌就不需要记录了，或者上一张牌与这一张牌的差值大于 $1$，则 $cnt$ 就要重新赋值为 $1$ 来计算，同时我们也要计算 $cnt$ 的最大值，最终判断 $cnt$ 是否大于等于 $k$。

最后有一个细节问题需要注意，就是 $cnt$ 数组我们应赋初始值为 $1$。因为最初总有一张牌（在下标为 $1$ 的位置）并没有递增（因为它是第一张牌，没有可以对比的），所以 $cnt$ 需要提前记录。

## 代码

::::success[正确代码]
```cpp line-numbers
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[300010],n,k;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    int cnt=1,maxx=-1e18;
    for(int i=2;i<=n;i++){
        if(a[i]==a[i-1]) continue;
        else if(a[i]==a[i-1]+1){
            cnt++;
            maxx=max(maxx,cnt);
        }
        else{
            cnt=1;
        }
    }
    if(maxx>=k) cout<<"Yes";
    else cout<<"No";
    return 0;
}
```
::::

---

## 作者：Loyal_Soldier (赞：2)

### 思路

由于题目不要求连续的牌组成顺子，所以可以将 $a$ 数组从大到小排序并去重。

然后，用一个变量 $now$ 维护上一张选的牌，再用一个变量 $ans$ 维护当前取了多少牌，如果当前的牌不能和上一次选的牌组成顺子（即 $a_i\ne now + 1$），则将 $ans$ 重置 $1$，否则增加 $ans$，表示选择了当前牌。当 $ans\ge k$ 时，输出 `Yes`，如果中途 $ans$ 没有一次满足条件，则输出 `No`。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N = 3e5 + 10;
int n, k, a[N], now, ans;//now 是上一次取的牌，ans 是当前取的牌的数量
bool flag = false;//flag 标记是否找到了 k 张牌的顺子
signed main()
{
	cin >> n >> k;
	for(int i = 1;i <= n;i ++) cin >> a[i];
	sort(a + 1, a + n + 1);//排序
	n = unique(a + 1, a + n + 1) - a - 1;//去重
	ans = 1, now = a[1];//初始化，最开始取了 a[1]
	for(int i = 2;i <= n;i ++)
	{	
		if(a[i] != now + 1) ans = 1;
		else ans ++;
		if(ans >= k)
		{
			cout << "Yes";
			flag = true;//输出并标记
			break;
		}
		now = a[i];//选了 a[i] 这张牌
	}
	if(flag == false) cout << "No";//如果不能组成顺子，输出 No
	return 0;
}
```

---

## 作者：queenbee (赞：1)

# P13733 [JOIGST 2025] 扑克 / Poker 题解
## 思路
[题目传送门](https://www.luogu.com.cn/problem/P13733)，考虑到顺子是公差为 $1$ 的升序等差数列，所以先对数组进行排序并对数组进行去重，递推求出每以每种牌为结尾的最大顺子。有递推式：

$dp_i=\begin{cases}dp_{i-1}+1 &\text{if } a_i-a_{i-1}=1 \\ 1 &\text{if } a_i-a_{i-1} \ne 1
\end{cases}$

最后对答案进行查找。

## 程序
```cpp
#include<bits/stdc++.h>	//我爱万能头 
using namespace std;
#define int long long
const int N=3e5+10;
int n,k;
int a[N];
int dp[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);	//先序排序 
	n=unique(a+1,a+n+1)-a;	//去重 
	for(int i=1;i<=n;i++){	//递推 
		if(a[i]-a[i-1]==1){
			dp[i]=dp[i-1]+1;
		}
		else{
			dp[i]=1;
		}
	}
	for(int i=1;i<=n;i++){
		if(dp[i]>=k){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0; //完结撒花 
} 
```

---

## 作者：zhujianheng (赞：1)

观察到一个性质，这个牌组为顺子当且仅当它在排完序的数组里面正好是公差为 $1$，项数为 $K$ 的等差数列，很容易证明。

然后只要询问这样的等差数列存不存在就可以了。

对于这样的询问，我们考虑排序后的数组 $a$。

假设我们当前遍历到第 $i$ 个数。

如果 $a_i=a_{i-1}+1$，那么最长的顺子的长度就加 1。如果加后，这个最长的顺子的长度达到 $K$，那么就存在这样一个数列。

如果 $a_i=a_{i-1}$，那么最长的顺子的长度不会增加，因为我们可以选 $a_{p_1},a_{p_2},\cdots,a_{p_{cnt-1}},a_i$，也可以选 $a_{p_1},a_{p_2},\cdots,a_{p_{cnt-1}},a_{i-1}$，其中 $cnt$ 是当前的顺子的长度，$p_i$ 是第 $i$ 个选出的数的编号。所以这种情况没有变化。

如果 $a_i>a_{i-1}+1$，那么最长的顺子的长度就会到此终止，需要重新从 $i$ 开始计算最长顺子长度。

这样，如果最后还没有找到顺子长度等于 $K$ 的一种，那么就不存在，注意我们从 $2$ 开始遍历，因为 $a_1$ 不一定等于 $1$。

Code:

```
#include<bits/stdc++.h>
using namespace std;
const int N=300009;
int a[N];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	int cnt=1;
	for(int i=2;i<=n;i++)
		if(a[i]==a[i-1]+1){
			cnt++;
			if(cnt==k){
				cout<<"Yes"<<endl;
				return 0;
			}
		}
		else if(a[i]==a[i-1]) continue;
		else cnt=1;
	cout<<"No"<<endl;
	return 0;
}
```

---

