# [AGC058A] Make it Zigzag

## 题目描述

给定一个排列 $ P=(P_1,P_2,\cdots,P_{2N}) $，其中 $ (1,2,\cdots,2N) $。

你可以进行以下操作 $ 0 $ 到 $ N $ 次：

- 选择一个整数 $ x $ ($ 1\ \leq\ x\ \leq\ 2N-1 $)，交换 $ P_x $ 和 $ P_{x+1} $ 的值。

请找出一系列操作，使得操作后的 $ P $ 满足以下条件：

- 对于每个 $ i=1,3,5,\cdots,2N-1 $，$ P_i\ <\ P_{i+1} $。
- 对于每个 $ i=2,4,6,\cdots,2N-2 $，$ P_i\ >\ P_{i+1} $。

请输出满足条件的一系列操作，以以下形式输出：

> $ K $ $ x_1 $ $ x_2 $ $ \cdots $ $ x_K $

其中，$ K $ 表示操作次数 ($ 0\ \leq\ K\ \leq\ N $)，$ x_i $ ($ 1\ \leq\ x_i\ \leq\ 2N-1 $) 表示第 $ i $ 次操作选择的 $ x $ 的值。如果存在多个满足条件的解，任意输出一个即可。

## 说明/提示

### 约束条件

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ (P_1,P_2,\cdots,P_{2N}) $ 是 $ (1,2,\cdots,{2N}) $ 的排列
- 输入的数值均为整数

### 样例解释 1

将 $ P=(4,3,2,1) $ 根据操作后，得到 $ P=(3,4,1,2)$，满足条件。

## 样例 #1

### 输入

```
2
4 3 2 1```

### 输出

```
2
1 3```

## 样例 #2

### 输入

```
1
1 2```

### 输出

```
0```

# 题解

## 作者：yangjinqian (赞：3)

题目很清晰，不用过多阐述。

## 思路

贪心+模拟。枚举 $i$ 从 1 开始到 $2N - 1$ 如果当前 $P_{i} \ge P_{i + 1}$ 那就 swap 一下。同理枚举 2 到 $2N - 2$ 如果当前 $P_{i} \le P_{i + 1}$ 也 swap 。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, t;
int a[N], ans[N];
int main(){
	cin >> n;
	n *= 2;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n - 1; i += 2)
		if (a[i] >= a[i + 1])
			ans[++t] = i, swap(a[i], a[i + 1]);
	for (int i = 2; i <= n - 2; i+= 2)
		if (a[i] <= a[i + 1])
			ans[++t] = i, swap(a[i], a[i + 1]);
	cout << t << endl;
	for (int i = 1; i <= t; i++) cout << ans[i] << " ";
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/191784683)

---

## 作者：Innate_Joker (赞：2)

# [AT_agc058_a [AGC058A] Make it Zigzag](https://www.luogu.com.cn/problem/AT_agc058_a)

## 思路

不知为何，题目标签上写了贪心，个人觉得直接照题意模拟就好。对于 $i = 1,3,5,...,2N - 1,P_i < P_{i + 1}$，就枚举 $1$ 到 $2N - 1$ 之间的奇数，如果 $P_i > P_{i + 1}$，则将两数交换。而$i = 2,4,6,...,2N - 2,P_i > P_{i + 1}$，也是和前面一样。枚举 $2$ 到 $2N - 2$ 之间的偶数，如果 $P_i < P_{i + 1}$，则将两数交换。

## 优化

- 在枚举 $i$ 时，可以让 $i$ 每次加 $2$，来保证每次枚举到的 $i$ 一定是奇数或偶数。
- 因为一共是有 $2N$ 个数，所以可以让 $n$ 在输入后就乘 $2$, 让后面的操作更加方便。
- 这里要养成一个习惯，在打 `AtCoder` 的比赛输出时要记得换行，不然可能会 `Wrong Answer`。

## Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
int p[1000005] {};
int main() {
    int n;
    cin >> n;
    n *= 2;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector <int> answer;
    for (int i = 1; i <= n - 1; i += 2) {
        if (p[i] > p[i + 1]) {
            swap(p[i], p[i + 1]);
            answer.push_back(i);
        }
    }
    for (int i = 2; i <= n - 2; i += 2) {
        if (p[i] < p[i + 1]) {
            swap(p[i], p[i + 1]);
            answer.push_back(i);
        }
    }
    cout << int(answer.size()) << endl;
    if (answer.size() > 0) {
        int len = answer.size();
        for (int i = 0; i < len; i++) {
            cout << answer[i] << ' ';
        }
        cout << endl;//岛国水题要换行捏。
    }
    return 0;
}
```

---

## 作者：FFTotoro (赞：2)

## 前言

赛时 $16$ 分钟过本题，perf 上 $\text{\color{Blue}1862}$，可惜 Unrated，不然可以上大分。

## 解法

这道题我用了与官方题解与众不同的做法。

考察每个连续的 $p_i,p_{i+1},p_{i+2}(1\le i\le 2n-3,i\equiv1\pmod 2)$，容易想到一种贪心：如果 $\max\{p_i,p_{i+2}\}>p_{i+1}$，那么就将 $p_i$ 于 $p_{i+2}$ 中的较大者与 $p_{i+1}$ 交换，那么这三个数肯定是满足题目条件的，并且对后面的操作不会造成影响。

该操作无后效性的证明：

用我们的方法，后面的操作只会用到 $p_{i+2}$，而 $p_{i+2}$ 在本次操作中**只减不增**。同样的 $p_i$ 也只减不增，所以也不会对前面的操作造成影响。

由于操作次数最多为 $\frac{2N}{2}=N$，所以满足要求。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int n; cin>>n;
    vector<int> a(n<<1),b;
    for(auto &i:a)cin>>i;
    for(int i=0;i<n<<1;i+=2){
        if(i+2>=n<<1){if(a[i+1]<a[i])b.emplace_back(i+1); break;}
        if(a[i+1]>max(a[i],a[i+2]))continue;
        if(a[i]>a[i+2])swap(a[i],a[i+1]),b.emplace_back(i+1);
        else swap(a[i+1],a[i+2]),b.emplace_back(i+2); // 判断与交换
    }
    cout<<b.size()<<endl;
    for(auto &i:b)cout<<i<<' ';
    cout<<endl;
    return 0;
}
```

---

## 作者：Like_Amao (赞：2)

**前言**

[题目传送门](https://www.luogu.com.cn/problem/AT_agc058_a)

**题目大意**

题意已经很清晰，所以我就不过多赘述，看不懂的多看几遍就好了。

**思路**

看了算法标签，得知这道题要用贪心来做，然后根据题意模拟即可。首先，我们让 $i$ 从 $1$ 循环到 $2N - 1$，每次加上 $2$，如果 $P _ i \ge P _ {i + 1}$，那么就交换，然后，同样地，将 $i$ 从 $2$ 循环到 $2N - 2$，每次加上 $2$，如果 $P _ i \le P _ {i + 1}$，那么也交换。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],ans[200005];
int main()
{
	int n,cnt=0;
	cin>>n;
	n*=2;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=2;i<=n-2;i+=2)
	{
		if(a[i]<=a[i+1])
		{
			int t=a[i];
			a[i]=a[i+1];
			a[i+1]=t;
			ans[++cnt]=i;
		}
	}
	for(int i=1;i<=n-1;i+=2)
	{
		if(a[i]>=a[i+1])
		{
			int t=a[i];
			a[i]=a[i+1];
			a[i+1]=a[i];
			ans[++cnt]=i;
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}
```

---

## 作者：ylch (赞：1)

前情提要：这是我们提高组模拟赛第二题，名字叫“波浪”。

这道题的要求就像它的名字一样：我们要把偶数位置的数视为波浪的高处（浪尖），把奇数位置的数视为波浪的低处。

发现交换两个不符合条件的相邻元素可以使其符合条件，考虑从前到后的每个位置，若不符合交换。

易知这样不会破坏前一个位置的条件。

但这样最多需要 $2n-1$ 次，题目要求操作次数小于等于 $n$，不行。


---


考虑一种更优的交换策略：

对于从前到后第一个不满足条件的位置 $i$，设 $i$ 为偶数：
- 若 $P[i]<P[i+2]$，交换 $P[i],P[i+1]$；
- 否则交换 $P[i+1],P[i+2]$。

这样每次交换都会满足每两个位置的条件，题面保证有解，所以这样的操作可行。且只需最多 $n$ 次。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 7;

int n, a[2 * maxn];
vector<int> ans;

void solve()
{
	cin >> n; n *= 2;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	
	// 特判前两个位置不满足的情况
	if(a[1] > a[2]) swap(a[1], a[2]), ans.push_back(1);
	
	for(int i = 2; i <= n - 2; i += 2){ // 这样每次满足两个位置的条件，for步长设为2
		if(a[i + 1] >= a[i + 2] || a[i] <= a[i + 1]){ // 奇数位不满足条件 或 偶数位不满足条件
			if(a[i] < a[i + 2]) swap(a[i], a[i + 1]), ans.push_back(i);
			else swap(a[i + 1], a[i + 2]), ans.push_back(i + 1);
		}
	}
	cout << ans.size() << '\n';
	for(auto x : ans) cout << x << ' ';
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：lifeiyang1 (赞：1)

~~芜湖！AGC 小水题~~。
# 思路与分析
这道题是一个非常简单的贪心，连贪心都算不上感觉就是一个模拟。他是想让我们把这个序列排成他想要的样子。还告诉我了交换方式，就很简单了，直接按照交换方式去模拟就可以。提醒粗心的大家和我数组要开 $$2\times10 ^ 5$$，不然就像我一样第一次提一次交上去得到了一个大大的紫色。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans[200005],cnt;
int main(){
	scanf("%d",&n);
	n=2*n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	//按照题目给的去模拟 
	for(int i=2;i<=n-2;i+=2){
		if(a[i]<=a[i + 1]){
			swap(a[i],a[i+1]); 
			ans[++cnt]=i;
		}
	}
	for(int i=1;i<=n-1;i+=2){
		if(a[i]>=a[i + 1]){
			swap(a[i],a[i+1]); 
			ans[++cnt]=i;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%d ",ans[i]); 
	return 0;
}
```
顺便建议管理降橙。

---

## 作者：ZHANGyutao123 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_agc058_a)
# 题目描述

给定一个 $1$ 到 $2N$ 的排列 $P=(P_1,P_2,\cdots,P_{2N})$，可以进行若干次操作，每次操作可以将相邻两个位置的元素交换。现在要求进行若干次操作，使得 $P$ 满足以下条件：

对于所有奇数 $i\in[1,2N-1]$，都有 $P_i<P_{i+1}$；

对于所有偶数 $i\in[2,2N-2]$，都有 $P_i>P_{i+1}$。


# 思路分析
题目中说了，必然存在操作方案使得最终序列符合条件，那么我们只需考虑如何跳过中间某一步到达最终符合条件的状态，考虑什么情况下可以快速结束构造。

显然要想得到满足要求的序列必须满足 $P_{2i} > \max\{P_{2i-1}, P_{2i+1}\}$ 或 $P_{2n} < P_{2n-1}$。

依次遍历每个 $2i$，如果它不符合上述条件，就交换 $P_{2i}$ 和 $\max\{P_{2i-1}, P_{2i+1}\}$ 的位置，那么这个位置上的值肯定就满足限制条件了，把操作记录到答案里即可。

对于最后一个位置 $2n$，如果它不符合要求，就交换 $P_{2n}$ 和 $P_{2n-1}$ 的位置即可。

时间复杂度是 $O(n)$，可以通过本题。

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 2;
int n, a[N * 2], cnt; // 定义序列长度n、序列数组a、交换操作次数cnt
vector<int> ans; // 用于存放交换操作的位置
int main() {
	cin >> n;
	for (int i = 1; i <= n * 2; ++i)
		cin >> a[i];
	for (int i = 2; i <= n * 2; i += 2) { // 从第二个位置开始遍历，每次跳两个位置
		if (a[i] < max(a[i - 1], a[i + 1])) { // 如果当前元素不符合题目要求
			if (a[i - 1] > a[i + 1]) // 如果左边的元素比右边的元素大
				swap(a[i], a[i - 1]), ans.push_back(i - 1); // 则将左边的元素交换到当前位置，并记录交换位置
			else
				swap(a[i], a[i + 1]), ans.push_back(i); // 否则将右边的元素交换到当前位置，并记录交换位置
		}
		if (i == n * 2 && a[i] < a[i - 1]) // 如果当前遍历到倒数第二个位置且倒数第二个元素大于最后一个元素
			ans.push_back(i - 1); // 则将倒数第二个位置与最后一个位置交换，并记录交换位置
	}
	cout << ans.size() << '\n'; // 输出交换操作的次数
	for (auto x : ans)
		cout << x << " "; // 逐个输出交换操作的位置
	cout << endl;
	return 0;
}
```


---

## 作者：_JellyFish_ (赞：1)

# 1.题意
给出一个长度为 $2n$ 的排列，要求通过邻项交换的方法，使得这个排列长成“小 大 小 大 小 大”的样子，这里的大小是相对于它的邻项来说的，偶数为大奇数为小，求出所需操作最少次数。
# 2.分析
不难发现，我们只要保证，对于每一个偶数下标 $i$，他都比相邻的两个数要大就可以了。所以我们的 $i$ 只需要枚举偶数，就可以使整个排列都满足要求。而我们也可以发现，对于每一个偶数，它们一定可以通过只和自己的邻项交换来满足整个排列。所以我们使用贪心策略：对于从前往后偶数 $i$，如果相邻的两个数里有比它大的，那就选择最大的那一个和它本身交换。
# 3.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans;
vector<int>v;
int main(){
	cin>>n;
	for(int i=1;i<=n*2;i++)cin>>a[i];
	for(int i=2;i<=n*2;i+=2){
		if(i!=n*2&&a[i]<max(a[i-1],a[i+1])){
			if(a[i-1]>a[i+1])swap(a[i],a[i-1]),v.push_back(i-1);
			else swap(a[i],a[i+1]),v.push_back(i);
		}
		if(i==n*2&&a[i]<a[i-1])v.push_back(i-1);
	}
	cout<<v.size()<<endl;
	for(int i=0;i<v.size();i++)cout<<v[i]<<' ';
	return 0;
}
```


---

## 作者：良心WA题人 (赞：1)

钦定 $a_{2\times n+1}=0,a_0=\infty$，这样会自然满足 $a_1<a_0$ 和 $a_{2\times n}>a_{2\times n+1}$。

假设从 $1$ 到 $2\times k-1$ 均满足条件。一开始 $k=1$，考虑处理 $a_{2\times k-1},a_{2\times k},a_{2\times k+1}$ 这三个数。

令 $t=max\{a_{2\times k-1},a_{2\times k},a_{2\times k+1}\}$：

- 若 $a_{2\times k}=t$ ：不进行操作。
- 若 $a_{2\times k+1}=t$：直接操作一次 $2\times k$​。
- 若 $a_{2\times k-1}=t$：直接操作一次 $2\times k-1$。此时 $a_{2\times k-1}<t<a_{2\times k-2}$，不会对之前的操作造成影响。

此时从 $1$ 到 $2\times k+1$ 均满足条件。可以发现 $k$ 次以内的操作可以让前 $2\times k+1$ 个位置合法，所以操作数 $\le n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
int a[NN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)
		scanf("%d",&a[i]);
	vector<int>ans;
	for(int i=1;i<=2*n;i+=2)
	{
		if(max(a[i],a[i+1])<a[i+2])
		{
			ans.push_back(i+1);
			swap(a[i+1],a[i+2]);
		}
		else if(a[i]>a[i+1])
		{
			ans.push_back(i);
			swap(a[i],a[i+1]);
		}
	}
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

给定一个排列 $P=(P_1,P_2,...,P_{2n})$。

我们可以选择一个 $x$，交换 $P_x$ 和 $P_{x+1}$ 的值 $0 \sim n$ 次。

我们想让 $k$ 满足以下条件：

- 对于每个数 $i=1,3,5,...,2n-1,P_i<P_{i+1}$。
- 对于每个数 $i=2,4,6,...,2n-2,P_i>P_{i+1}$。

还要他变成以下形式输出：

- $K$ $x_1,x_2,x_3,...,x_k$。

铺垫的差不多了，接下来是思路。

思路：

- 枚举偶数下标 $i$。因为每一个偶数下标 $i$，只要大于相邻两个就行。
- 所以对于每一个偶数，它们一定可以通过和自己的相邻的项交换来满足整个排列的答案。

所以我们用贪心：

- 每当相邻两个数有个比他大，就将最大的与他交换。

代码简单就不放了。

---

## 作者：YangXiaopei (赞：0)

## 思路：

很明显，对于每个 $i \in [1, 2N - 2]$，$a_i > a_{i - 1}$ 且 $a_i > a_{i + 1}$。

我们只需枚举每个这样的 $i$，如果不满足，将其替换为 $\max(a_{i - 1}, a_{i + 1})$ 即可。

若 $i$ 与 $i + 1$ 操作，将 $i$ 存入记录答案的数组。

若 $i$ 与 $i - 1$ 操作，将 $i - 1$ 存入记录答案的数组。

详情看代码。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, ans, a[200005];
vector<int> v;
int main() {
	cin >> n;
	for(int i = 1; i <= 2 * n; i++){
		cin >> a[i];
	}
	for(int i = 2; i < 2 * n; i += 2){
		if(a[i] < max(a[i - 1], a[i + 1])){
			if(a[i - 1] > a[i + 1]){
				swap(a[i], a[i - 1]);
				v.push_back(i - 1);
			}
			else{
				swap(a[i], a[i + 1]);
				v.push_back(i);
			}
		}
	}
	if(a[2 * n] < a[2 * n - 1]){
		v.push_back(2 * n - 1);
	}
	cout << v.size() << "\n";
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << ' ';
	}
	return 0;
}
```

---

## 作者：_Memory (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_agc058_a)

### 一、前言

这应该是本蒟蒻的倒数第二或第三篇题解了，会发题解在博客，但是就不提交了，希望能帮到大家。

### 二、思路

阅读题目后不难发现一些规律，我们只需要去比较 $ i $ 所在的数与是否是前中后三个数里面最大的就行。而且我们只需要遍历偶数就可以，那么我们的 $ i $ 就从二开始遍历即可，如果说当前数不是三个数里面最大的，那就继续判断，看看后一个数是不是大于等于前一个数，是的话交换后一个数和当前数的位置，并把 $ i $ 塞进 vector 里。一样的，若前一个数大于后一个数，那就交换当前数和前一个数的位置，压入向量里。最后需要特判一下最后一个偶数就可以，然后把向量里面的所有数给输出来，就完成了本题！

~~更适合我这种蒟蒻体制的水题~~各位请看 AC 代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,p[1919810],ans=0;
vector<int> v;

int main(){
	cin>>n;
	for(int i=1;i<=n*2;i++){
		cin>>p[i]; 
	}
	for(int i=2;i<=n*2;i+=2){
		if(i!=n*2&&p[i]!=max(max(p[i-1],p[i+1]),p[i])){
		
			if(p[i-1]>p[i+1]){ 
				swap(p[i],p[i-1]); 
				v.push_back(i-1);
			}
			
			else if(p[i+1]>=p[i-1]){
				swap(p[i],p[i+1]);
				v.push_back(i);
			}
		}
		else if(i==n*2&&p[i]<p[i-1]){ 
			v.push_back(i-1);
		}
}
	cout<<v.size()<<endl;
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<' ';
	}
	cout<<endl;
	return 0; 
}
```



---

## 作者：hmh100211 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_agc058_a)

## 题意分析：

给定一个整数 $ n $ 和一个元素个数为 $ 2n $ 的排列 $ P=(P_1,P_2, \cdots ,P_{2n}) $，其中 $ 1,2, \cdots ,2n $。

可以进行 $ 0 $ 到 $ n $ 次操作，每次操作可以选择一个整数 $ x(1 \le x \le 2n-1) $，交换 $ P_x $ 和 $ P_{x+1} $ 的值。

需要进行一系列操作，使交换后的 $ P $ 满足：

- 当 $ i $ 为奇数时，$ P_i < P_{i+1} $。

- 当 $ i $ 为偶数时，$ P_i > P_{i+1} $。 

操作完后，输出操作次数 $ k(1 \le k \le N) $ 和 $ k $ 个数 $ x_1,x_2,\cdots ,x_k $。$ x_i $ 表示第 $ i $ 次操作选择的 $ x $ 的值。

###### ~~（如果存在多个满足条件的解，任意输出一个即可）~~。

数据范围为 $ 1 \le n \le 10^5 $，正常开 ` int `。

## 思路：

根据题意可以分析得要让 $ P $ 满足题意，只要让每个**偶数** $ i $ 对应的元素 $ P_i $ 是 $ P_{i-1},P_i,P_{i+1} $ **三个数中最大**的即可，~~直接硬模拟就行~~。

实现：遍历所有偶数，如果 $ P_i $ 不是最后一个偶数时（当 $ i=2n $ 时只有 $ P_{i-1} $，没有 $ P_{i+1} $)，且不是三个中最大的，再判断 $ P_{i-1} $ 和 $ P_{i+1} $ 哪一个更大，把最大数和 $ P_i $ 交换，再把对应的元素推进 `vector`。如果 $ P_i $ 是**最后一个偶数**，只要特判 $ P_i $ 和 $ P_{i-1} $ 哪个更大。

# AC code：

```c

#include<bits/stdc++.h>

using namespace std;

int n,p[1919810],ans=0;
vector<int> v; //用向量便于储存元素 

int main(){
	cin>>n;
	for(int i=1;i<=n*2;i++){
		cin>>p[i]; //读入，注意下标从1到2*n 
	}
	for(int i=2;i<=n*2;i+=2){ //从2开始，每次+2，遍历所有偶数 
		if(i!=n*2&&p[i]!=max(max(p[i-1],p[i+1]),p[i])){ //如果不是最后一个偶数，而且p[i]不是三个中最大的 
		
			if(p[i-1]>p[i+1]){ //如果p[i-1]更大 
				swap(p[i],p[i-1]); //交换
				v.push_back(i-1); //把i-1推进vector 
			}
			
			else if(p[i+1]>=p[i-1]){ //如果p[i+1]更大 
				swap(p[i],p[i+1]); //交换
				v.push_back(i); //把i推进vector 
			}
		}
		else if(i==n*2&&p[i]<p[i-1]){ //特判最后一个 
			v.push_back(i-1);
		}
	}
	//输出 
	cout<<v.size()<<endl;
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<' ';
	}
	cout<<endl;
    
	return 0; //华丽的结尾
}
```


# [AC](https://www.luogu.com.cn/record/116701926)

---

## 作者：MurataHimeko (赞：0)

冷静分析一下。

题目所说的相当于要求对于每个偶数位置 $i$，都满足 $a_i = \max{(a_{i-1},a_i, a_{i+1})}$。那么就好做了，如果 $a_i$ 不是最大值，那么和最大值的位置交换即可。

交换次数最多为 $n$ 次。

代码：

```cpp

const int N = 1e5 + 5;
int n, a[N<<1];
int ans, b[N];

int main () {
	io >> n;
	re(i, n*2) io >> a[i]; 
	for(int i(2); i <= 2*n; i += 2) {
		int id = a[i-1] > a[i+1] ? i-1 : i+1;
		if(a[id] > a[i]) {
			b[++ans] = min(id, i);
			swap(a[id], a[i]);
		}
	}
	io << ans << "\n";
	re(i, ans) io << b[i] << " ";
}
```


---

## 作者：exploration (赞：0)

这道AGC的题普通思路很容易想到，但需要一点点**思维的改进**。

容易想到做法：遍历整个数列，找到不符合波浪数列条件的那个数进行交换，但问题在于，这个操作能在 $N$ 次以内完成吗？

因为 $P=(P_1,P_2,\cdots,P_{2N})$ ，所以排列 $P$ 是一共有 $2N$ 个的。如果是**最坏情况**，即**每相邻两个都要交换一次**，那么肯定无法在 $N$ 次以内完成。

这时候就**选相邻的两个**地判断，每次**结合左右两个数**一起判断，如果右边的数比左边的大，则交换这个数和它左边的，反之交换这个数和它右边的。操作次数肯定**比 $N$ 次少或一样**。

# Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[200001];
vector<ll>f;
main()
{
	scanf("%lld",&n);
	for (ll i=1;i<=2*n;i++) scanf("%lld",&a[i]);
	for (ll i=2;i<=2*n;i+=2)
	{
		if (a[i]<max(a[i-1],a[i+1]))
		{
			if (a[i-1]>a[i+1])
			{
				swap(a[i],a[i-1]);
				f.push_back(i-1);
			}
			else
			{
				swap(a[i],a[i+1]);
				f.push_back(i);
			}
		}
		if(i==2*n&&a[i]<a[i-1]) f.push_back(i-1);
	}
    printf("%lld\n",f.size());
	for (ll i=0;i<f.size();i++) printf("%lld ",f[i]);
}
```

---

