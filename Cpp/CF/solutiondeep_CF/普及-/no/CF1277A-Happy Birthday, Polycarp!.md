# 题目信息

# Happy Birthday, Polycarp!

## 题目描述

Hooray! Polycarp turned $ n $ years old! The Technocup Team sincerely congratulates Polycarp!

Polycarp celebrated all of his $ n $ birthdays: from the $ 1 $ -th to the $ n $ -th. At the moment, he is wondering: how many times he turned beautiful number of years?

According to Polycarp, a positive integer is beautiful if it consists of only one digit repeated one or more times. For example, the following numbers are beautiful: $ 1 $ , $ 77 $ , $ 777 $ , $ 44 $ and $ 999999 $ . The following numbers are not beautiful: $ 12 $ , $ 11110 $ , $ 6969 $ and $ 987654321 $ .

Of course, Polycarpus uses the decimal numeral system (i.e. radix is 10).

Help Polycarpus to find the number of numbers from $ 1 $ to $ n $ (inclusive) that are beautiful.

## 说明/提示

In the first test case of the example beautiful years are $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 8 $ , $ 9 $ and $ 11 $ .

## 样例 #1

### 输入

```
6
18
1
9
100500
33
1000000000
```

### 输出

```
10
1
9
45
12
81
```

# AI分析结果

### 题目内容
# 生日快乐，波利亚克！

## 题目描述
万岁！波利亚克已经 $n$ 岁啦！Technocup团队衷心祝贺波利亚克！

波利亚克庆祝了他所有的 $n$ 个生日：从第 $1$ 个到第 $n$ 个。此刻，他在想：他有多少次年满美丽的数字岁呢？

按照波利亚克的定义，一个正整数如果仅由一个数字重复一次或多次组成，那么它就是美丽的。例如，以下数字是美丽的：$1$、$77$、$777$、$44$ 和 $999999$。以下数字不是美丽的：$12$、$11110$、$6969$ 和 $987654321$。

当然，波利亚克使用的是十进制记数系统（即基数为10）。

帮助波利亚克找出从 $1$ 到 $n$（含）中有多少个美丽的数字。

## 说明/提示
在示例的第一个测试用例中，美丽的年份是 $1$、$2$、$3$、$4$、$5$、$6$、$7$、$8$、$9$ 和 $11$。

## 样例 #1
### 输入
```
6
18
1
9
100500
33
1000000000
```
### 输出
```
10
1
9
45
12
81
```

### 算法分类
枚举

### 题解综合分析与结论
这些题解主要分为打表法和直接计算法。打表法思路简单直接，由于美丽数数量有限（共81个），通过预先列举出所有美丽数，再统计小于等于给定 $n$ 的美丽数个数。直接计算法则通过对数字的十进制拆分，根据不同位数的美丽数规律，结合给定数字 $n$ 的具体情况进行计算。打表法代码实现简单，代码可读性高，但需要预先确定所有美丽数；直接计算法代码相对复杂，但无需预先枚举所有美丽数，在理论上更具通用性。

### 所选的题解
- **作者：Sayori（5星）**
    - **关键亮点**：思路清晰，直接打表，代码简洁明了，可读性高。
    - **个人心得**：无
    - **重点代码核心实现思想**：预先定义包含所有美丽数的数组 `beau_num`，对每个输入的 $n$，遍历该数组统计小于等于 $n$ 的美丽数个数。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, ans[10010];
int beau_num[81] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 
                    11, 22, 33, 44, 55, 66, 77, 88, 99, 
                    111, 222, 333, 444, 555, 666, 777, 888, 999, 
                    1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999, 
                    11111, 22222, 33333, 44444, 55555, 66666, 77777, 88888, 99999, 
                    111111, 222222, 333333, 444444, 555555, 666666, 777777, 888888, 999999, 
                    1111111, 2222222, 3333333, 4444444, 5555555, 6666666, 7777777, 8888888, 9999999, 
                    11111111, 22222222, 33333333, 44444444, 55555555, 66666666, 77777777, 88888888, 99999999, 
                    111111111, 222222222, 333333333, 444444444, 555555555, 666666666, 777777777, 888888888, 999999999};
int main(){
    scanf("%d", &t);
    for(int i = 1; i <= t; ++i){
        register int x, sum = 0;
        scanf("%d", &x);
        for(int i = 0; i <= 80; ++i)
            if(beau_num[i] <= x) ++sum;
            else break;
        ans[i] = sum;
    }
    for(int i = 1; i <= t; ++i)
        printf("%d\n", ans[i]);
}
```
- **作者：gyh20（4星）**
    - **关键亮点**：通过循环枚举1 - 9每个数，动态生成由其组成的美丽数并统计小于等于 $n$ 的个数，代码简洁高效。
    - **个人心得**：无
    - **重点代码核心实现思想**：对1 - 9的每个数 `i`，通过 `tmp = tmp * 10 + i` 不断生成新的美丽数并判断是否小于等于 $n$，统计符合条件的个数。
    - **核心代码片段**：
```cpp
#include<cstdio>
using namespace std;
int main(){
	long long t,n;
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		long long ans=0;
		for(long long i=1;i<=9;++i){
			long long tmp=i;
			while(tmp<=n){
				++ans;
				tmp=tmp*10+i;
			}
		}
		printf("%lld\n",ans);
	}
}
```
- **作者：AlanSP（4星）**
    - **关键亮点**：采用直接计算的方式，对数字进行十进制拆分，考虑不同位数美丽数情况，逻辑严谨。
    - **个人心得**：无
    - **重点代码核心实现思想**：先计算小于当前数字 $n$ 位数的美丽数个数，再针对 $n$ 所在位数的美丽数，通过与 $n$ 的逐位比较确定是否符合条件并统计。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int t,n,ans,cnt;
 
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=0;
		cnt=0;
		int bn=n;
		while(bn) cnt++,bn/=10;
		if(n<10)
		{
			cout<<n<<endl;
			continue;
		}
		ans+=9*(cnt-1);
		int tem=pow(10,cnt-1);
		if(tem%10==9) tem++;
		int f=n/tem;
		int b=f;
		n%=tem;
		ans+=f-1;
		tem/=10;
		
		while(tem!=0)
		{
			if(n/tem<f) break;
			else if(n/tem>f)
			{
				ans++;
				break;
			}
			
			n%=tem;
			tem/=10;
			if(tem==0) ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

### 最优关键思路或技巧
打表法简单直观，利用美丽数数量有限的特点，预先枚举所有美丽数，通过遍历统计解决问题，代码实现难度低。而像gyh20的动态生成美丽数并统计的方法，避免了预先打表，通过循环动态生成并判断，代码简洁高效，在一定程度上优化了空间，同时保持了较低的时间复杂度。

### 拓展
此类题目属于数字规律枚举类问题，类似套路是先分析数字规律，若可能的结果集有限，可考虑打表法；若结果集虽有规律但难以穷举，可像gyh20的方法，通过循环动态生成并判断。

### 洛谷相似题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举不同数字组合判断是否为质数，考察枚举技巧。
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：要求按特定格式输出组合，锻炼对枚举和组合的理解。
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)：根据给定函数规则，通过枚举不同参数取值范围求解，强化枚举与条件判断结合能力。 

---
处理用时：87.29秒