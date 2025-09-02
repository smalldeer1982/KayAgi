# 题目信息

# Unnatural Conditions

## 题目描述

Let $ s(x) $ be sum of digits in decimal representation of positive integer $ x $ . Given two integers $ n $ and $ m $ , find some positive integers $ a $ and $ b $ such that

- $ s(a) \ge n $ ,
- $ s(b) \ge n $ ,
- $ s(a + b) \le m $ .

## 说明/提示

In the first sample, we have $ n = 6 $ and $ m = 5 $ . One valid solution is $ a = 6 $ , $ b = 7 $ . Indeed, we have $ s(a) = 6 \ge n $ and $ s(b) = 7 \ge n $ , and also $ s(a + b) = s(13) = 4 \le m $ .

## 样例 #1

### 输入

```
6 5
```

### 输出

```
6 
7
```

## 样例 #2

### 输入

```
8 16
```

### 输出

```
35 
53
```

# AI分析结果

### 题目内容
# 非自然条件

## 题目描述
设\(s(x)\)为正整数\(x\)十进制表示下各位数字之和。给定两个整数\(n\)和\(m\)，找出一些正整数\(a\)和\(b\)，使得：
- \(s(a) \geq n\)，
- \(s(b) \geq n\)，
- \(s(a + b) \leq m\)。

## 说明/提示
在第一个样例中，我们有\(n = 6\)且\(m = 5\)。一个有效的解决方案是\(a = 6\)，\(b = 7\)。实际上，我们有\(s(a) = 6 \geq n\)且\(s(b) = 7 \geq n\)，同时\(s(a + b) = s(13) = 4 \leq m\)。

## 样例 #1
### 输入
```
6 5
```
### 输出
```
6 
7
```

## 样例 #2
### 输入
```
8 16
```
### 输出
```
35 
53
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过构造满足条件的\(a\)和\(b\)来解决问题。大部分题解利用了数字相加进位会使数位和减小这一特性，通过构造特定形式的\(a\)和\(b\)，让它们的数位和满足\(s(a) \geq n\)，\(s(b) \geq n\)，同时让\(a + b\)通过进位得到一个数位和较小的数，满足\(s(a + b) \leq m\)。不同题解在具体构造方式上有所差异，有的构造通用解，有的根据输入动态构造。

### 所选的题解
 - **作者：Anguei（5星）**
    - **关键亮点**：思路清晰简洁，直接给出最短AC代码，并详细证明了正确性，通过固定构造的数字形式，确保满足题目所有可能输入条件。
    - **个人心得**：感慨比赛时构造方式过于复杂。
```python
print '4' * 300
print '5' * 299 + '6'
```
核心实现思想：输出固定长度的由\(4\)组成的数作为\(a\)，由\(299\)个\(5\)和\(1\)个\(6\)组成的数作为\(b\)，利用相同长度的\(4\)和\(5\)相加得\(9\)，最后一位相加进位得到\(10\)的幂，满足数位和条件。
 - **作者：—维尼—（4星）**
    - **关键亮点**：解题思路阐述详细，从理解题意出发，分析如何构造满足条件的数，代码实现清晰易懂。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	for(int i=1;i<=300;i++){
		cout<<"4";
	}
	cout<<endl;
	for(int i=1;i<=299;i++){
		cout<<"5";
	}
	cout<<6<<endl;
	return 0;
}
```
核心实现思想：与Anguei类似，通过循环输出固定数量的\(4\)和\(5\)、\(6\)构造\(a\)和\(b\)，利用进位使\(a + b\)数位和满足条件。
 - **作者：small_moon（4星）**
    - **关键亮点**：详细解释了使\(a + b\)数位和减小的原理是进位，并给出一种通过双端队列动态构造\(a\)和\(b\)的方法，使\(a\)、\(b\)同一数位和为\(9\)且最后一位和为\(10\)。
```cpp
#include<bits/stdc++.h>
using namespace std;
int na,nb,n,m;
deque <int> a,b; 
void pa() {
	int tmp=0;
	if(a.front()==4) tmp=5;
	else tmp=4;
	a.push_front(tmp); na+=tmp;
}
void pb() {
	int tmp=0;
	if(b.front()==5) tmp=4;
	else tmp=5;
	b.push_front(tmp); nb+=tmp;
}
int main()
{
	a.push_front(5);
	b.push_front(5);
	a.push_front(4);
	b.push_front(5);
	cin>>n>>m;
	na=9; nb=9; 
	while(na<n) pa();
	while(nb<n) pb();
	while(a.size()<b.size()) pa();
	while(b.size()<a.size()) pb();
	while(!a.empty())
	{
		printf("%d",a.front());
		a.pop_front();
	}
	cout<<endl;
	while(!b.empty())
	{
		printf("%d",b.front());
		b.pop_front();
	}
	return 0;
}
```
核心实现思想：先初始化\(a\)、\(b\)的前几位，然后通过自定义函数在\(a\)、\(b\)前面添加数字，保证数位和满足\(s(a) \geq n\)，\(s(b) \geq n\)，且利用\(a\)、\(b\)对应数位和为\(9\)（除最后一位和为\(10\)）保证\(a + b\)进位后数位和满足条件。

### 最优关键思路或技巧
利用数字相加进位使数位和减小这一特性来构造数字。构造通用解时，选择合适的数字组合（如多个\(4\)与多个\(5\)、\(6\)组合），确保在满足\(s(a) \geq n\)，\(s(b) \geq n\)的同时，能通过进位让\(s(a + b)\)达到较小值以满足\(s(a + b) \leq m\)。

### 可拓展之处
同类型题通常围绕数字的数位特性、数字运算（加、乘等）后的数位变化进行构造。类似算法套路是先分析题目对数字的要求，找到能改变数位和的关键操作（如进位、借位等），然后根据数据范围构造满足条件的数字。

### 推荐题目
 - [P1108 低价购买](https://www.luogu.com.cn/problem/P1108)：涉及数字序列的构造与分析，与本题类似需根据特定条件构造满足要求的序列。
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过组合数字满足特定条件，锻炼构造满足条件数字组合的能力。
 - [P1464 Function](https://www.luogu.com.cn/problem/P1464)：根据函数特性构造满足条件的输入值，与本题构造满足条件数字思路类似。 

---
处理用时：83.50秒