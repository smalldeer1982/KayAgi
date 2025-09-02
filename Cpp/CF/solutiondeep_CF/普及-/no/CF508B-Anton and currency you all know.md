# 题目信息

# Anton and currency you all know

## 题目描述

Berland, 2016. The exchange rate of currency you all know against the burle has increased so much that to simplify the calculations, its fractional part was neglected and the exchange rate is now assumed to be an integer.

Reliable sources have informed the financier Anton of some information about the exchange rate of currency you all know against the burle for tomorrow. Now Anton knows that tomorrow the exchange rate will be an even number, which can be obtained from the present rate by swapping exactly two distinct digits in it. Of all the possible values that meet these conditions, the exchange rate for tomorrow will be the maximum possible. It is guaranteed that today the exchange rate is an odd positive integer $ n $ . Help Anton to determine the exchange rate of currency you all know for tomorrow!

## 样例 #1

### 输入

```
527
```

### 输出

```
572
```

## 样例 #2

### 输入

```
4573
```

### 输出

```
3574
```

## 样例 #3

### 输入

```
1357997531
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 安东和你们都知道的货币

## 题目描述
在伯兰，2016 年。你们都知道的那种货币对伯尔（burle）的汇率上涨了很多，为了简化计算，其小数部分被忽略了，现在汇率被假定为一个整数。

可靠消息来源告诉金融家安东一些关于明天你们都知道的那种货币对伯尔汇率的信息。现在安东知道，明天的汇率将是一个偶数，这个偶数可以通过交换当前汇率中的恰好两个不同数字得到。在所有满足这些条件的可能值中，明天的汇率将是最大可能值。保证今天的汇率是一个奇数正整数 $n$。帮助安东确定明天你们都知道的那种货币的汇率！

## 样例 #1
### 输入
```
527
```
### 输出
```
572
```

## 样例 #2
### 输入
```
4573
```
### 输出
```
3574
```

## 样例 #3
### 输入
```
1357997531
```
### 输出
```
-1
```

### 算法分类
贪心

### 综合分析与结论
- **思路对比**：各位大神的思路基本一致，都是先判断数字中是否有偶数，若没有则直接输出 -1。然后优先寻找最高位且比最后一位小的偶数进行交换，若没有则交换最低位的偶数与最后一位。
- **算法要点**：通过遍历数字的每一位，根据奇偶性和大小关系进行判断和交换操作。
- **解决难点**：解决了直接交换最高位偶数可能不是最优解的问题，采用先找比最后一位小的偶数，再找最低位偶数的策略来保证得到最大的偶数。

### 题解评分
- **bigju**：4星。思路清晰，代码简洁易懂，对关键步骤有详细注释。
- **Franka**：3星。思路正确，但先给出了 TLE 代码，增加了冗余信息，且使用 Pascal 语言，对于习惯 C++ 的人不太友好。
- **Oscar12345**：4星。思路简洁明了，代码规范，使用了常见的 C++ 库函数。
- **zhanghzqwq**：4星。思路清晰，代码结构明确，对关键步骤有提醒。

### 所选题解
- **bigju**：4星。关键亮点在于思路清晰，代码简洁，对关键步骤有详细注释。
- **Oscar12345**：4星。思路简洁明了，代码规范，使用了常见的 C++ 库函数。
- **zhanghzqwq**：4星。思路清晰，代码结构明确，对关键步骤有提醒。

### 重点代码
#### bigju 的代码
```cpp
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
string ch;
bool temp=1;
int fir,las=-1;
int main()
{
    cin>>ch;
    for(int i=0;i<ch.size();i++)
    {
    	if((ch[i]-'0')%2==0&&ch[i]<ch[ch.size()-1]) //如果有比他小的偶数，因为我们是从前往后筛的，直接交换 
		{
			swap(ch[i],ch[ch.size()-1]);
			cout<<ch;
			return 0;
		}
	}
	for(int i=ch.size()-1;i>=0;i--)//如果没有比他小的偶数，那只能尽可能减少损失了 
	{
		if((ch[i]-'0')%2==0) 
		{
			swap(ch[i],ch[ch.size()-1]);
			cout<<ch;
			return 0;
		}
	}
	//此时我们把比最后那个奇数大的偶数和小的偶数都筛完了，发现都没有 
	cout<<-1;//上述两种情况都没发生，说明一个偶数没有 
	return 0;
}
```
核心实现思想：先从前往后遍历，找到比最后一位小的偶数并交换；若没有则从后往前遍历，找到偶数并交换；若都没有则输出 -1。

#### Oscar12345 的代码
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define max(a,b) a>b?a:b
#define min(a,b) a>b?b:a
using namespace std;
char a[100010];
int main()
{
    gets(a);
    bool f=0;
    int l=strlen(a);
    for(int i=0;i<l;i++)
    {
        if((a[i]-'0')%2==0&&a[i]<a[l-1])
        {
            f=1;
            swap(a[i],a[l-1]);
            break;
        }
    }
    if(!f)
    {
        for(int i=l-1;i>=0;i--)
        {
            if((a[i]-'0')%2==0)
            {
                f=1;
                swap(a[i],a[l-1]);
                break;
            }
        }
    }
    if(f)
        puts(a);
    else 
        puts("-1");
    return 0;
}
```
核心实现思想：与 bigju 的思路一致，只是使用字符数组存储数字，通过标记变量 `f` 来判断是否找到合适的交换位置。

#### zhanghzqwq 的代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	string a;
	cin>>a;//输入不解释
	int la=a.size();
	bool found=0;
	for(int i=0;i<la;i++){
		int num=a[i]-'0';
		if(num%2==0){
			found=1;//找到了
			break;//这里不break无所谓，这样快一点
		}
	}
	if(!found){
		cout<<"-1"<<endl;
		return 0;
	}
	int end=a[la-1]-'0';//end是最末尾的奇数
	bool ok=0;
	for(int i=0;i<la;i++){
		int num=a[i]-'0';
		if(num%2==0&&num<end){
			swap(a[i],a[la-1]);
			ok=1;//找到了
			break;//一定要break出去
		}
	}
	if(ok){
		cout<<a<<endl;
		return 0;
	}
	for(int i=la-1;i>=0;i--){//从后往前找
		int num=a[i]-'0';
		if(num%2==0){
			swap(a[i],a[la-1]);
			break;//这里也一定要break出去
		}
	}
	cout<<a<<endl;
	return 0;//完结撒花
}
```
核心实现思想：先判断数字中是否有偶数，若没有则输出 -1。然后从前往后找比最后一位小的偶数并交换，若没有则从后往前找偶数并交换。

### 最优关键思路或技巧
采用贪心策略，优先选择最高位且比最后一位小的偶数进行交换，若没有则选择最低位的偶数进行交换，以保证得到的偶数最大。

### 拓展思路
同类型题可能会有更多的限制条件，如交换次数的限制、数字范围的变化等。类似算法套路可以应用在其他需要通过局部最优解来得到全局最优解的问题中。

### 推荐洛谷题目
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P1090 [NOIP2004 提高组] 合并果子

### 个人心得
- **Franka**：一开始以为是 $105$ 位的字符串，就打了一个无脑模拟，秒送 $TLE$。提醒我们在做题时要仔细分析题目，不能盲目模拟，要寻找更优的算法。

---
处理用时：45.00秒