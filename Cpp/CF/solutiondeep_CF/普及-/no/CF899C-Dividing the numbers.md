# 题目信息

# Dividing the numbers

## 题目描述

Petya has $ n $ integers: $ 1,2,3,...,n $ . He wants to split these integers in two non-empty groups in such a way that the absolute difference of sums of integers in each group is as small as possible.

Help Petya to split the integers. Each of $ n $ integers should be exactly in one group.

## 说明/提示

In the first example you have to put integers $ 1 $ and $ 4 $ in the first group, and $ 2 $ and $ 3 $ in the second. This way the sum in each group is $ 5 $ , and the absolute difference is $ 0 $ .

In the second example there are only two integers, and since both groups should be non-empty, you have to put one integer in the first group and one in the second. This way the absolute difference of sums of integers in each group is $ 1 $ .

## 样例 #1

### 输入

```
4
```

### 输出

```
0
2 1 4 
```

## 样例 #2

### 输入

```
2
```

### 输出

```
1
1 1 
```

# AI分析结果

### 题目翻译
# 数字分组

## 题目描述
Petya 有 $n$ 个整数：$1, 2, 3, \cdots, n$。他想把这些整数分成两个非空组，使得每个组中整数之和的绝对差尽可能小。

请帮助 Petya 对这些整数进行分组。$n$ 个整数中的每一个都必须恰好属于一个组。

## 说明/提示
在第一个样例中，你需要把整数 $1$ 和 $4$ 放在第一组，把 $2$ 和 $3$ 放在第二组。这样，每个组的和都是 $5$，绝对差为 $0$。

在第二个样例中，只有两个整数，由于两个组都必须是非空的，你必须把一个整数放在第一组，另一个整数放在第二组。这样，每个组中整数之和的绝对差为 $1$。

## 样例 #1
### 输入
```
4
```
### 输出
```
0
2 1 4 
```

## 样例 #2
### 输入
```
2
```
### 输出
```
1
1 1 
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用数学规律来解决问题。通过观察发现，对于长度为 $4$ 的序列，其可以分成和相等的两组，差值为 $0$。当 $n$ 大于 $4$ 时，可以不断减去 $4$ 进行简化，最后根据 $n$ 对 $4$ 取模的结果进行分类讨论。

各题解的思路和算法要点基本一致，但在代码实现和细节处理上有所不同。有的题解使用数组记录分组元素，有的直接输出；有的题解在处理余数情况时更加详细，有的则相对简洁。

### 题解列表
- **Light_az（4星）**
    - **关键亮点**：思路清晰，对余数情况的讨论详细，代码有一定的注释，可读性较好。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,cnt=0,t=0,k,x,y;
const int N=1e5+10;
int a[N];
char b[N]={' ','1','1','3'};//n取模后的特判 
string s;
void print(int n){//余数规律 
	if(n%4==0||n%4==3){
		cout<<0<<endl;
	}
	else{
		cout<<1<<endl;
	}
}
int main(){
	cin>>n;
	print(n);//输出余数 
	while(n>=4){//对n取模并记录数字 
		cnt+=2;
		a[++t]=n;//第一个数 
		a[++t]=n-3;//第二个数 
		n-=4;
	}
	if(n){//取模剩下的数的特判 
		cnt++;
		a[++t]=b[n]-'0';
	}
	cout<<cnt<<" ";//输出总数 
	for(int i=1;i<=t;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```
核心实现思想：先根据 $n$ 对 $4$ 取模的结果输出最小差值，然后不断减去 $4$ 并记录分组元素，最后处理余数情况，输出分组元素个数和具体元素。

- **yzy041616（4星）**
    - **关键亮点**：思路阐述详细，对题目和解题步骤的解释清晰，代码简洁。
    - **重点代码**：
```cpp
#include<iostream>
using namespace std;
int diff[4]={0,1,1,0};
string start[4]={" "," "," 1 "," 3 "};
int main(){
	int n;cin>>n;
	cout<<diff[n%4]<<endl;
	cout<<n/2<<start[n%4];
	for(;n>3;n-=4)cout<<n<<" "<<n-3<<" ";//改成n-1和n-2也行
}
```
核心实现思想：使用数组存储不同余数情况下的最小差值和初始分组元素，根据 $n$ 对 $4$ 取模的结果输出最小差值和分组元素。

- **HuZHUNZHUN（4星）**
    - **关键亮点**：使用函数 $f(x)$ 来表示问题的答案，逻辑清晰，代码结构简洁。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	if(n%4==0)
	{
		cout<<"0\n"<<n/2<<" ";
		for(int i=0;i<n/4;i++) cout<<4*i+1<<" "<<4*i+4<<" ";
	}
	else if(n%4==1)
	{
		cout<<"1\n"<<n/2<<" ";
		for(int i=0;i<n/4;i++) cout<<4*i+2<<" "<<4*i+5<<" "; 
	}
	else if(n%4==2)
	{
		cout<<"1\n"<<n/2<<" 1 ";
		for(int i=0;i<n/4;i++) cout<<4*i+3<<" "<<4*i+6<<" ";
	}
	else
	{
		cout<<"0\n"<<n/2<<" 3 ";
		for(int i=0;i<n/4;i++) cout<<4*i+4<<" "<<4*i+7<<" ";
	}
	return 0;
}
```
核心实现思想：根据 $n$ 对 $4$ 取模的结果进行分类讨论，输出最小差值和分组元素。

### 最优关键思路或技巧
- 观察到长度为 $4$ 的序列可以分成和相等的两组，利用这个规律将 $n$ 个数的问题转化为 $n\%4$ 个数的问题，大大简化了问题。
- 根据 $n$ 对 $4$ 取模的结果进行分类讨论，确定最小差值和分组方案。

### 可拓展之处
同类型题或类似算法套路：对于一些需要对整数进行分组并求差值的问题，可以先观察数字的规律，尝试找到一些特殊的组合使得差值最小，然后通过取模等方式简化问题。

### 推荐洛谷题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

### 个人心得
本题解中没有包含个人心得。

---
处理用时：44.72秒