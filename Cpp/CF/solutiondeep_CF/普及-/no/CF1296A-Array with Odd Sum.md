# 题目信息

# Array with Odd Sum

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

In one move, you can choose two indices $ 1 \le i, j \le n $ such that $ i \ne j $ and set $ a_i := a_j $ . You can perform such moves any number of times (possibly, zero). You can choose different indices in different operations. The operation := is the operation of assignment (i.e. you choose $ i $ and $ j $ and replace $ a_i $ with $ a_j $ ).

Your task is to say if it is possible to obtain an array with an odd (not divisible by $ 2 $ ) sum of elements.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2
2 3
4
2 2 8 8
3
3 3 3
4
5 5 5 5
4
1 1 1 1```

### 输出

```
YES
NO
YES
NO
NO```

# AI分析结果

### 题目内容
# 奇数和数组

## 题目描述
给定一个由 $n$ 个整数组成的数组 $a$。
在一次移动中，你可以选择两个索引 $1 \leq i, j \leq n$ 且 $i \neq j$，并将 $a_i$ 设置为 $a_j$。你可以执行这样的移动任意次数（可能为零次）。在不同操作中你可以选择不同的索引。操作 := 是赋值操作（即你选择 $i$ 和 $j$ 并用 $a_j$ 替换 $a_i$）。
你的任务是判断是否有可能得到一个元素和为奇数（不能被2整除）的数组。
你必须回答 $t$ 个独立的测试用例。

## 样例 #1
### 输入
```
5
2
2 3
4
2 2 8 8
3
3 3 3
4
5 5 5 5
4
1 1 1 1
```
### 输出
```
YES
NO
YES
NO
NO
```
• **算法分类**：数学
• **综合分析与结论**：这几道题解思路本质相同，都是基于对数组中奇数和偶数个数的分析来判断能否得到奇数和。通过对不同情况（全偶数、全奇数、奇偶都有）的讨论得出结论。题解主要区别在于代码实现细节，如统计方式、判断条件写法以及是否使用位运算优化等。
• **所选的题解**
  - **作者：123456zmy (赞：3)  星级：4星  关键亮点**：代码简洁明了，利用位运算 `a&1` 判断奇数，直接统计奇数和偶数个数，通过简洁的逻辑判断输出结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,a1,a2;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		a1=0;a2=0;
		scanf("%d",&n);
		while(n--)
		{
			scanf("%d",&a);
			if(a&1)++a1;
			else ++a2;
		}
		if((a1&1)||(a1&&a2))puts("YES");
		else puts("NO");
	}
	return 0;
}
```
  - **作者：5k_sync_closer (赞：0)  星级：4星  关键亮点**：先列出奇偶运算的基本知识，思路清晰，通过分类讨论三种情况（全偶数、全奇数、奇偶都有），每种情况分别判断输出，逻辑严谨。
```cpp
#include <iostream>
using namespace std;
int n, T, s = 0;
int main()
{
    cin >> T;
    while(T--)
    {
        cin >> n;s = 0;
        for(int i = 1, t;i <= n;++i)
            cin >> t, s += t & 1;
        if(s == 0) 
            cout << "NO" << endl;
        else if(s == n) 
        {
            if(n & 1) cout << "YES" << endl; 
            else cout << "NO" << endl; 
        }
        else cout << "YES" << endl; 
    }
    return 0;
}
```
  - **作者：_0x46EDC (赞：0)  星级：4星  关键亮点**：先进行理论推导，得出能使和为奇数的两种情况，然后给出普通代码和使用位运算优化后的代码，并说明了位运算优先级问题，内容全面。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        int n,odd=0;
        cin>>n;
        for(int i=0;i<n;i++){
            int x;
            cin>>x;
            if(x&1)odd++;
        }
        if((odd&&(n-odd))||(odd&1))cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
```
• **最优关键思路或技巧**：利用奇偶运算性质，通过统计数组中奇数和偶数的个数来判断能否得到奇数和。使用位运算 `x & 1` 判断一个数是否为奇数，能提高代码效率，同时注意位运算优先级。
• **可拓展之处**：此类题目属于基于奇偶性分析的数学类算法题，类似套路是对给定数据进行奇偶分类讨论，分析不同组合下目标结果（如和、积等）的可能性。
• **推荐洛谷题目**：
  - [P1579 哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)
  - [P1246 编码](https://www.luogu.com.cn/problem/P1246)
  - [P2142 高精度减法](https://www.luogu.com.cn/problem/P2142) ，虽然是高精度减法，但也涉及到数字的奇偶性判断等基础数学知识运用。 

---
处理用时：50.80秒