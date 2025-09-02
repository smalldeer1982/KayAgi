# 题目信息

# Vasilije in Cacak

## 题目描述

Aca and Milovan, two fellow competitive programmers, decided to give Vasilije a problem to test his skills.

Vasilije is given three positive integers: $ n $ , $ k $ , and $ x $ , and he has to determine if he can choose $ k $ distinct integers between $ 1 $ and $ n $ , such that their sum is equal to $ x $ .

Since Vasilije is now in the weirdest city in Serbia where Aca and Milovan live, Cacak, the problem seems weird to him. So he needs your help with this problem.

## 说明/提示

In the first test case $ n = 5,\ k=3,\ x=10 $ , so we can choose the numbers: $ 2 $ , $ 3 $ , $ 5 $ , whose sum is $ 10 $ , so the answer is "YES".

In the second test case $ n = 5, \ k=3, \ x=3 $ , there is no three numbers which satisfies the condition, so the answer is "NO". It can be shown that there are no three numbers whose sum is $ 3 $ .

## 样例 #1

### 输入

```
12
5 3 10
5 3 3
10 10 55
6 5 20
2 1 26
187856 87856 2609202300
200000 190000 19000000000
28 5 2004
2 2 2006
9 6 40
47202 32455 613407217
185977 145541 15770805980```

### 输出

```
YES
NO
YES
YES
NO
NO
YES
NO
NO
NO
YES
YES```

# AI分析结果

### 题目翻译
Aca和Milovan，两位同为竞技程序员的伙伴，决定给Vasilije出一道题来测试他的技能。

Vasilije会得到三个正整数：$n$、$k$和$x$，他必须判断是否能在$1$到$n$之间选择$k$个不同的整数，使得它们的和等于$x$。

由于Vasilije现在身处塞尔维亚一座奇特的城市——Aca和Milovan居住的恰卡克（Cacak），这道题对他来说显得有些奇怪。所以他需要你的帮助来解决这个问题。

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路一致，均是先确定从$1$到$n$中选$k$个不同整数的和的取值范围，即最小值为前$k$个正整数的和，最大值为后$k$个正整数的和，再使用高斯等差数列求和公式计算这两个值，最后判断$x$是否在该范围内，若在则输出`YES`，否则输出`NO`。

在证明取值范围中的值都能取到时，部分题解使用了数学归纳法，部分题解采用了感性理解的方式。

### 所选题解
- **作者：Richard1211 (赞：12)，4星**
    - **关键亮点**：思路清晰，不仅给出了结论，还使用数学归纳法进行了证明，代码简洁。
    - **个人心得**：赛时通过观察样例发现不合法情况的条件，然后大胆猜测除不合法条件外其他情况都合法并通过了题目。
- **作者：cherry2010 (赞：6)，4星**
    - **关键亮点**：思路直观，对`NO`的情况分析清晰，代码简洁易懂。
- **作者：InversionShadow (赞：2)，4星**
    - **关键亮点**：对取值范围的推导有详细的感性理解过程，代码规范。

### 重点代码
```cpp
// Richard1211的代码
#define YES printf("YES\n")
#define Yes printf("Yes\n")
#define yes printf("yes\n")
#define NO printf("NO\n")
#define No printf("No\n")
#define no printf("no\n")
constexpr long long N=1000100;
long long t,n,k,x;
int main(){
    t=read();
    for(register int T=1;T<=t;++T){
        n=read();
        k=read();
        x=read();
        if(x<k*(k+1)/2||x>k*(n+n-k+1)/2){
            No;
        }
        else{
            Yes;
        }
    }
    return 0;
}

// cherry2010的代码
#include <bits/stdc++.h>
using namespace std;
long long t,n,k,x;
int main() {
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%lld",&n,&k,&x);
		if(k*(1+k)/2>x)		//情况 1
		{
			printf("NO\n");
		}
		else if(k*(n-k+1+n)/2<x)	//情况 2
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
	return 0;
}

// InversionShadow的代码
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, k, x;

void solve() {
	cin >> n >> k >> x;
	int sum = 0;
	// (末项 + 首项) * 项数 / 2
	sum = (long long)((n + n - k + 1) * k) / 2;
	int ans = 0;
	ans = (long long)((1 + k) * k) / 2;
	if (ans > x || sum < x) {
		cout << "NO\n";
		return ;
	}
	cout << "YES\n";
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;	
}
```
**核心实现思想**：先读取多组数据，对于每组数据，计算前$k$个正整数的和（最小值）与后$k$个正整数的和（最大值），然后判断$x$是否在这个范围内，根据判断结果输出`YES`或`NO`。

### 扩展思路
同类型题目通常会考察对数学规律的发现和运用，例如在一定范围内选择若干个数满足特定条件的问题。解题的关键在于找出取值范围，并证明范围内的值都能取到。

### 推荐题目
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：考察数学运算和高精度计算。
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：简单的数学模拟题。
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过数学计算解决实际问题。

---
处理用时：31.91秒