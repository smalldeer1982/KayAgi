# 题目信息

# Find B

## 题目描述

An array $ a $ of length $ m $ is considered good if there exists an integer array $ b $ of length $ m $ such that the following conditions hold:

1. $ \sum\limits_{i=1}^{m} a_i = \sum\limits_{i=1}^{m} b_i $ ;
2. $ a_i \neq b_i $ for every index $ i $ from $ 1 $ to $ m $ ;
3. $ b_i > 0 $ for every index $ i $ from $ 1 $ to $ m $ .

You are given an array $ c $ of length $ n $ . Each element of this array is greater than $ 0 $ .

You have to answer $ q $ queries. During the $ i $ -th query, you have to determine whether the subarray $ c_{l_{i}}, c_{l_{i}+1}, \dots, c_{r_{i}} $ is good.

## 样例 #1

### 输入

```
1
5 4
1 2 1 4 5
1 5
4 4
3 4
1 3```

### 输出

```
YES
NO
YES
NO```

# AI分析结果

### 题目内容中文重写
## 寻找数组 B

### 题目描述
如果存在一个长度为 $m$ 的整数数组 $b$ 满足以下条件，则称长度为 $m$ 的数组 $a$ 是“好的”：
1. $\sum\limits_{i = 1}^{m} a_i = \sum\limits_{i = 1}^{m} b_i$；
2. 对于从 $1$ 到 $m$ 的每个索引 $i$，都有 $a_i \neq b_i$；
3. 对于从 $1$ 到 $m$ 的每个索引 $i$，都有 $b_i > 0$。

给定一个长度为 $n$ 的数组 $c$，该数组的每个元素都大于 $0$。

你需要回答 $q$ 个查询。在第 $i$ 个查询中，你需要确定子数组 $c_{l_{i}}, c_{l_{i}+1}, \dots, c_{r_{i}}$ 是否是“好的”。

### 样例 #1
#### 输入
```
1
5 4
1 2 1 4 5
1 5
4 4
3 4
1 3
```

#### 输出
```
YES
NO
YES
NO
```

### 综合分析与结论
这些题解的核心思路都是围绕数组中元素为 $1$ 的情况展开，因为 $1$ 只能增加不能减少，是影响能否构造出满足条件数组 $b$ 的关键因素。大部分题解都采用了前缀和的方法进行预处理，以优化每次查询的时间复杂度。

### 各题解思路、要点及难点对比
|作者|思路|算法要点|解决难点|评分|
|----|----|----|----|----|
|YBaggio|先判断子数组元素是否都大于 $1$，若都大于 $1$ 则是好数组；否则预处理前缀中可补给 $1$ 的值和 $1$ 的数量，根据查询区间判断能否构造出 $b$ 数组|预处理前缀和，根据区间内 $1$ 的数量和可补给值判断|处理数组中存在 $1$ 的情况|4星|
|2huk|先将 $b_i$ 全设为 $1$，分析问题并发现可在 $c_i = 1$ 的位置上加数来解决问题，通过判断能否加完差值来确定是否可行|维护前缀和，判断 $\sum_{i = l}^r c_i - (r - l + 1) \ge x$ 是否成立|同时解决 $c_i = b_i$ 和总和不足的问题|4星|
|ZZZZZZZF|从 $1$ 的数量考虑，若序列和能将 $1$ 全部抬升则是好序列，用前缀和处理求和|定义判断条件 $\operatorname{cnt}(1) \le \sum_{i = l}^{r}a_i - len$，前缀和处理|找出序列为不好序列的条件|4星|
|AKPC|根据 $p_i=[a_i=1]+1$ 的不同情况进行分类讨论，分别给出构造 $b$ 数组的方法|分类讨论，不同情况不同构造方法|针对不同情况构造合适的 $b$ 数组|3星|
|FeiDing|先考虑一次询问，构造 $b$ 数组使 $\Sigma b$ 尽量小，通过比较 $\Sigma b$ 和 $\Sigma c$ 来判断，多次询问用前缀和优化|构造 $b$ 数组，前缀和优化|构造使 $\Sigma b$ 最小的 $b$ 数组|3星|
|I_will_AKIOI|使用贪心算法，最小化 $b_i$，通过比较 $\sum\limits_{i = 1}^{m} b_i$ 和 $\sum\limits_{i = 1}^{m} a_i$ 来判断，用前缀和记录区间和及 $1$ 的个数|贪心算法，前缀和记录|处理 $1$ 的花费比其他数多的问题|3星|
|Luzhuoyuan|考虑构造 $b$ 数组，计算至少要增加的值和至多能减小的值，通过比较判断是否有解，预处理前缀和|计算增加和减小的值，前缀和预处理|判断能否满足总和相等的条件|4星|

### 所选题解
- **YBaggio（4星）**
    - **关键亮点**：思路清晰，代码简洁，通过预处理前缀和有效解决了查询问题。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn = 300010;
int t, n, m, a[maxn];
ll s[maxn], p[maxn];
int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      s[i] = s[i - 1] + (a[i] == 1);
      p[i] = p[i - 1] + (a[i] - 1);
    }
    for (int i = 1; i <= m; i++) {
      int l, r; cin >> l >> r;  
      if (l == r) cout << "NO\n";
      else cout << ((s[r] - s[l - 1] <= p[r] - p[l - 1])? "YES" : "NO") << '\n';
    }
  }
  return 0;
}
```
    - **核心实现思想**：预处理前缀中 $1$ 的数量 $s$ 和可补给 $1$ 的值 $p$，对于每个查询区间 $[l, r]$，判断区间内 $1$ 的数量是否小于等于可补给值，同时特判区间长度为 $1$ 的情况。

- **2huk（4星）**
    - **关键亮点**：从全填 $1$ 的情况出发，分析问题并得出判断条件，代码规范，使用了快速读写模板。
    - **核心代码**：
```cpp
void Luogu_UID_748509() {
	int n, q;
	fin >> n >> q;
	vector<int> a(n + 1), s1(n + 1), de(n + 1);
	for (int i = 1; i <= n; ++ i ) {
		fin >> a[i];
		s1[i] = s1[i - 1] + (a[i] == 1);
		de[i] = de[i - 1] + a[i] - 1;
	}
	
	while (q -- ) {
		int l, r;
		fin >> l >> r;
		if (l == r) puts("NO");
		else if (de[r] - de[l - 1] >= s1[r] - s1[l - 1]) puts("YES");
		else puts("NO");
	}
	
	return;
}
```
    - **核心实现思想**：维护前缀中 $1$ 的数量 $s1$ 和可补给值 $de$，对于每个查询区间 $[l, r]$，判断可补给值是否大于等于 $1$ 的数量，同时特判区间长度为 $1$ 的情况。

- **ZZZZZZZF（4星）**
    - **关键亮点**：从 $1$ 的数量角度分析问题，得出明确的判断条件，代码简洁，提醒了可能导致 TLE 的问题。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300005
long long sum1[N],sum[N];//1的数量 前缀和 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;
        for(int i = 1;i<=n;i++){
            cin>>sum[i];
            sum[i] += sum[i-1];
            sum1[i] = sum1[i-1];
            if(sum[i] - sum[i-1] == 1)
                sum1[i]++;
        }
        while(q--){
            int x,y;
            cin>>x>>y;
            long long len = (y-x+1),s = sum[y]-sum[x-1],n1 = sum1[y]-sum1[x-1];
            if(len == 1){ //特判长度为1
                cout<<"NO\n";
            }
            else if(s-len>=n1) {
                cout<<"YES\n";
            }
            else cout<<"NO\n";
        }
    }
    return 0;
}
```
    - **核心实现思想**：预处理前缀和 $sum$ 和 $1$ 的数量 $sum1$，对于每个查询区间 $[x, y]$，计算区间长度 $len$、区间和 $s$ 和 $1$ 的数量 $n1$，判断 $s - len$ 是否大于等于 $n1$，同时特判区间长度为 $1$ 的情况。

### 最优关键思路或技巧
- **思维方式**：抓住数组中元素为 $1$ 的特殊情况进行分析，因为 $1$ 只能增加不能减少，是影响能否构造出满足条件数组 $b$ 的关键因素。
- **算法优化**：使用前缀和进行预处理，将每次查询的时间复杂度从 $O(n)$ 优化到 $O(1)$。

### 可拓展之处
同类型题可能会改变数组元素的取值范围、增加更多的限制条件或改变构造数组 $b$ 的规则。类似算法套路可以应用于需要根据某些条件构造数组或序列的问题，关键在于找出影响构造的关键因素，并通过预处理来优化查询或计算的时间复杂度。

### 推荐洛谷题目
1. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)：涉及到序列的处理和查询，需要考虑数据的动态变化。
2. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)：需要使用前缀和来优化二维数组的查询。
3. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：需要对序列进行分类讨论和预处理，以优化计算过程。

### 个人心得摘录与总结
- **2huk**：寒假最后一场 CF 没上 Expert 感到生气，体现了竞赛选手对成绩的重视和追求。
- **ZZZZZZZF**：新年之后第一场 cf 惨遭 hack，提醒我们在竞赛中要注意代码的严谨性和边界情况的处理。
- **FeiDing**：有人不开 `long long` 被 Hack，自己不开 `long long` 没过 pretest，强调了在处理大数据时使用合适数据类型的重要性。
- **I_will_AKIOI**：题目比较坑，不开 `long long` 赛时能 A，赛后会被 hack，再次提醒要注意数据类型的选择。 

---
处理用时：49.07秒