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
# Chewbacca与数字

## 题目描述
卢克·天行者给了丘巴卡一个整数 $ x $。丘巴卡不擅长处理数字，但他喜欢反转数字中的每一位。反转数字 $ t $ 意味着将其替换为 $ 9 - t $。

帮助丘巴卡通过反转某些（可能为零个）数字，将初始数字 $ x $ 转换为最小的正整数。最终数字的十进制表示形式不能以零开头。

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

### 综合分析与结论
- **思路对比**：各题解核心思路一致，都是遍历数字的每一位，若该位数字大于等于 5 则反转（替换为 9 - 该数字），同时对首位数字进行特判避免出现前导 0。
- **算法要点**：多采用字符串存储数字，方便逐位处理。利用字符与数字的转换，结合 `min` 函数简化判断过程。
- **解决难点**：重点在于处理首位数字，避免反转后出现前导 0；部分题解还需注意字符与数字的转换细节。

### 所选题解
- **引领天下（5星）**
    - **关键亮点**：代码简洁，使用 `min` 函数直接处理每位数字，逻辑清晰。
    - **核心代码**：
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
- **Frank_R_Z（4星）**
    - **关键亮点**：将其他题解方法整合，代码简洁易理解，注释清晰。
    - **核心代码**：
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
- **PC_DOS（4星）**
    - **关键亮点**：思路清晰，对首位数字和其他位数字分别处理，逻辑严谨。
    - **核心代码**：
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

### 最优关键思路或技巧
- 使用字符串存储数字，便于逐位处理。
- 利用 `min` 函数简化判断过程，直接得到每一位的最优值。
- 对首位数字进行特判，避免出现前导 0。

### 拓展思路
同类型题目可能会有不同的数字变换规则，如将数字替换为其他固定值或根据特定公式计算，解题思路依然是逐位处理并考虑边界情况。

### 推荐题目
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：涉及高精度计算，需逐位处理数字。
- [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：同样是高精度问题，考验对数字逐位操作的能力。
- [P1601 A+B Problem（高精）](https://www.luogu.com.cn/problem/P1601)：高精度加法，需要逐位处理并考虑进位。

### 个人心得摘录与总结
- **Star_Wind**：不知道 10 的 18 次方在 `long long` 范围内，发现用字符串处理更简单；在字符与数字转换时遇到问题，需注意 `min` 函数结果为整数，转换为字符要加 `'0'` 并强制类型转换。总结为对于大数处理优先考虑字符串，注意字符与数字转换细节。 

---
处理用时：24.64秒