# 题目信息

# Unequal Array

## 题目描述

You are given an array $ a $ of length $ n $ . We define the equality of the array as the number of indices $ 1 \le i \le n - 1 $ such that $ a_i = a_{i + 1} $ . We are allowed to do the following operation:

- Select two integers $ i $ and $ x $ such that $ 1 \le i \le n - 1 $ and $ 1 \le x \le 10^9 $ . Then, set $ a_i $ and $ a_{i + 1} $ to be equal to $ x $ .

Find the minimum number of operations needed such that the equality of the array is less than or equal to $ 1 $ .

## 说明/提示

In the first test case, we can select $ i=2 $ and $ x=2 $ to form $ [1, 2, 2, 1, 1] $ . Then, we can select $ i=3 $ and $ x=3 $ to form $ [1, 2, 3, 3, 1] $ .

In the second test case, we can select $ i=3 $ and $ x=100 $ to form $ [2, 1, 100, 100, 2] $ .

## 样例 #1

### 输入

```
4
5
1 1 1 1 1
5
2 1 1 1 2
6
1 1 2 3 3 4
6
1 2 1 4 5 4```

### 输出

```
2
1
2
0```

# AI分析结果

### 题目内容
# 不等数组

## 题目描述
给定一个长度为 $n$ 的数组 $a$ 。我们将数组的相等度定义为满足 $1 \le i \le n - 1$ 且 $a_i = a_{i + 1}$ 的索引 $i$ 的数量 。我们可以进行以下操作：
- 选择两个整数 $i$ 和 $x$ ，使得 $1 \le i \le n - 1$ 且 $1 \le x \le 10^9$ 。然后，将 $a_i$ 和 $a_{i + 1}$ 设置为 $x$ 。
找到使数组的相等度小于或等于 $1$ 所需的最小操作次数。

## 说明/提示
在第一个测试用例中，我们可以选择 $i = 2$ 和 $x = 2$ 来形成 $[1, 2, 2, 1, 1]$ 。然后，我们可以选择 $i = 3$ 和 $x = 3$ 来形成 $[1, 2, 3, 3, 1]$ 。
在第二个测试用例中，我们可以选择 $i = 3$ 和 $x = 100$ 来形成 $[2, 1, 100, 100, 2]$ 。

## 样例 #1
### 输入
```
4
5
1 1 1 1 1
5
2 1 1 1 2
6
1 1 2 3 3 4
6
1 2 1 4 5 4
```
### 输出
```
2
1
2
0
```
### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过找规律来计算最小操作次数。多数题解先统计数组中相邻相等元素对的数量，若数量小于等于1，直接输出0。对于数量大于1的情况，通过模拟操作发现，只需要关注最左边和最右边的相邻相等元素对，设最左边相邻相等元素对中第一个元素位置为 $l$，最右边相邻相等元素对中第二个元素位置为 $r$，一般情况下操作次数为 $r - l - 2$，但长度为3的数组需要特判，操作次数为1。不同题解在细节表述和代码实现上略有差异，但整体思路一致。

### 所选的题解
- **作者：_acat_ (5星)**
    - **关键亮点**：思路清晰，通过具体例子展示操作过程，详细阐述了如何从连续相等和不连续相等的情况归纳出通用公式，代码简洁明了。
    - **核心代码**：
```cpp
void slove()
{
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        int l = n,r = 1;
        int cnt = 0;
        for(int i = 2; i <= n; i++)
        {
            if(a[i] == a[i - 1])
            {
                l = min(l,i - 1);
                r = max(r,i);
                cnt++;
            }
        }
        if(cnt < 2)
            cout << 0 << endl;
        else
        {
            int k = r - l - 1;
            if(k == 1)
                cout << 1 << endl;
            else
                cout << k - 1 << endl;
        }   
}
```
    - **核心实现思想**：遍历数组统计相邻相等元素对数量 `cnt` 以及最左 `l` 和最右 `r` 位置，根据 `cnt` 判断是否需要操作，若需要，根据 `r - l - 1` 的值进行计算，对特殊情况 `r - l - 1 == 1` 特判输出1。

- **作者：__little__Cabbage__ (4星)**
    - **关键亮点**：从简单序列入手分析操作次数规律，清晰阐述了连续与不连续情况实质相同，只关注首尾相邻相等元素对即可，代码简洁易懂。
    - **核心代码**：
```cpp
il void solve()
{
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	int l=-1,r=-1,cnt=0;
	for(int i=1;i<n;++i)
	{
		if(a[i]!=a[i+1]) continue;
		if(l==-1) l=i;
		r=i;
		++cnt;
	}
	if(cnt<=1)
	{
		cout<<0<<'\n';
		return;
	}
	if(r-l+2==3) cout<<1<<'\n';
	else cout<<r-l-1<<'\n';
	return;
}
```
    - **核心实现思想**：遍历数组找到第一个和最后一个相邻相等元素对位置 `l` 和 `r` 并统计数量 `cnt`，`cnt` 小于等于1 时输出0，否则根据 `r - l + 2` 是否为3进行特判输出。

- **作者：_little_Cabbage_ (4星)**
    - **关键亮点**：明确指出是找规律题，通过举例详细说明操作过程，总结出通用公式并对特殊情况进行特判，代码逻辑清晰。
    - **核心代码**：
```cpp
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		int cnt=0,l=1e9,r=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			if(i!=1)
			{
				if(a[i]==a[i-1])
				{
					cnt++;
					l=min(l,i-1);
					r=max(r,i);
				}
			}
		}
		if(cnt<2)
		{
			printf("0\n");
		}
		else
		{
			if(r-l==2)
			{
				printf("1\n");
			}
			else
			{
				printf("%d\n",r-l-2);
			}
		}
	}
}
```
    - **核心实现思想**：输入数据后遍历数组统计相邻相等元素对数量 `cnt` 以及最左 `l` 和最右 `r` 位置，`cnt` 小于2 输出0，否则根据 `r - l` 是否为2进行特判输出。

### 最优关键思路或技巧
通过对不同情况的具体例子模拟操作过程，总结出计算最小操作次数只与最左边和最右边的相邻相等元素对位置有关的规律，简化问题求解过程。

### 可拓展之处
此类找规律计算操作次数的题目，关键在于通过对不同规模数据的模拟操作，挖掘其中的共性与特殊情况，进而总结出通用的计算公式。类似题目可能会改变操作规则或限制条件，如改变每次操作影响的元素范围，或对操作后的数组状态有不同要求等，但解题思路都可从具体例子入手找规律。

### 洛谷相似题目推荐
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析日常生活中的场景找规律计算结果。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：需要通过数学分析找规律来解决连续自然数求和问题。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：利用斐波那契数列性质找规律求解最大公约数。 

---
处理用时：50.46秒