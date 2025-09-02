# 题目信息

# Chewbaсca and Number

## 题目描述

Luke Skywalker gave Chewbacca an integer number $ x $ . Chewbacca isn't good at numbers but he loves inverting digits in them. Inverting digit $ t $ means replacing it with digit $ 9-t $ .

Help Chewbacca to transform the initial number $ x $ to the minimum possible positive number by inverting some (possibly, zero) digits. The decimal representation of the final number shouldn't start with a zero.

## 样例 #1

### 输入

```
27
```

### 输出

```
22
```

## 样例 #2

### 输入

```
4545
```

### 输出

```
4444
```

# AI分析结果

### 题目翻译
卢克·天行者给了丘巴卡一个整数 $ x $。丘巴卡不擅长处理数字，但他喜欢反转数字中的每一位。反转数字 $ t $ 意味着将其替换为 $ 9 - t $。

帮助丘巴卡通过反转某些（可能为零个）数字，将初始数字 $ x $ 转换为最小的正整数。最终数字的十进制表示不能以零开头。

### 综合分析与结论
这些题解的核心思路都是模拟数字转换过程，将数字按位处理，若某一位数字大于等于 5 则将其反转（替换为 9 减去该数字），同时要特判首位不能为 0。
- **思路**：大多题解都是用字符串存储数字，遍历字符串按规则处理每一位。
- **算法要点**：按位判断数字大小，大于等于 5 则反转；特判首位避免为 0。
- **解决难点**：处理首位为 0 的情况，确保结果是正整数。

### 题解评分与选择
- **珂爱甲贺忍蛙**：3 星。思路较清晰，但代码中直接列举数字替换，不够简洁灵活。
- **引领天下**：4 星。思路清晰，代码简洁，使用 `min` 函数处理数字转换。
- **Frank_R_Z**：4 星。代码简洁，解释清晰，同样使用 `min` 函数。
- **yuzhechuan**：3 星。使用输入输出加速，边读边处理，但代码中存在拼写错误（`return 0；`）。
- **PC_DOS**：4 星。思路清晰，对首位和其他位分别处理，逻辑明确。
- **Star_Wind**：3 星。思路正确，但代码中循环范围存在问题（`xh(i,1,st.size())` 应改为 `xh(i,1,st.size()-1)`）。

选择评分较高的题解：
- **引领天下**：4 星。关键亮点是代码简洁，使用 `min` 函数处理数字转换，能有效避免复杂的判断。
- **Frank_R_Z**：4 星。代码简洁易懂，同样使用 `min` 函数，且对 `48` 是 `'0'` 的 ASCII 码有解释。
- **PC_DOS**：4 星。思路清晰，对首位和其他位分别处理，逻辑明确，还使用了输入输出加速。

### 重点代码
#### 引领天下
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[20];
int main(void){
    scanf ("%s",a);
    for (int i=0;a[i];i++)a[i]=min(a[i],char(9+'0'-a[i]+'0'));
    if (a[0]=='0')a[0]='9';
    printf ("%s",a);
}
```
核心思想：使用 `min` 函数比较原数字和反转后的数字，取较小值，最后特判首位是否为 0。

#### Frank_R_Z
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;
	cin>>a;
	for(int i=0;i<a.size();i++)
	{
		a[i]=min(a[i],char(9+48-a[i]+48));
	} 
	if(a[0]=='0')a[0]='9';
	cout<<a<<endl;
	return 0;
}
```
核心思想：同样使用 `min` 函数处理每一位数字，最后处理首位为 0 的情况。

#### PC_DOS
```cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	string sNum;
	int iLength;
	register int i;
	cin >> sNum;
	iLength = sNum.length();
	if (sNum[0] >= '5' && sNum[0] <= '8'){
		sNum[0] = '9' - sNum[0] + '0';
	}
	for (i = 1; i < iLength; ++i){
		if (sNum[i] >= '5' && sNum[i] <= '9'){
			sNum[i] = '9' - sNum[i] + '0';
		}
	}
	cout << sNum;
	return 0;
}
```
核心思想：分别处理首位和其他位，首位在 5 到 8 之间时反转，其他位大于等于 5 时反转。

### 最优关键思路或技巧
- 使用字符串存储大数字，方便按位处理。
- 利用 `min` 函数简化数字比较和转换过程。
- 特判首位避免结果为 0 开头的数字。

### 拓展思路
同类型题可能涉及对数字的其他变换操作，如交换相邻位、按特定规则替换数字等，解题思路都是按位处理数字，注意边界条件和特殊情况。

### 推荐洛谷题目
- P1009 [阶乘之和](https://www.luogu.com.cn/problem/P1009)：处理大数字的计算，需要按位处理。
- P1601 [A+B Problem（高精）](https://www.luogu.com.cn/problem/P1601)：高精度加法，按位处理数字相加。
- P2142 [高精度减法](https://www.luogu.com.cn/problem/P2142)：高精度减法，按位处理数字相减。

### 个人心得摘录与总结
- **Star_Wind**：为将 `min` 之后的整数转换为字符，调了半天，总结出要强制转换 `char(...+'0')`。提醒我们在字符和数字转换时要注意类型的处理。

---
处理用时：42.41秒