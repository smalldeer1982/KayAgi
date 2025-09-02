# 题目信息

# Party

## 题目描述

 $ n $ people came to a party. Then those, who had no friends among people at the party, left. Then those, who had exactly 1 friend among those who stayed, left as well. Then those, who had exactly $ 2,3,...,n-1 $ friends among those who stayed by the moment of their leaving, did the same.

What is the maximum amount of people that could stay at the party in the end?

## 样例 #1

### 输入

```
1
3
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# Party

## 题目描述
n个人来到一个派对。然后，那些在派对中没有朋友的人离开了。接着，那些在留下的人中恰好有1个朋友的人也离开了。随后，那些在当时留下的人中恰好有2、3、……、n - 1个朋友的人也依次离开了。

最后留在派对中的人数最多能是多少？

## 样例 #1
### 输入
```
1
3
```
### 输出
```
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过找规律或构造朋友关系来确定最终留下的最多人数。多数题解发现当 \(n \geq 2\) 时，最多留下 \(n - 2\) 人， \(n < 2\) 时为0人。各题解的不同在于找规律的方式，有的通过画图枚举，有的从朋友关系构造角度分析。

### 所选的题解
 - **作者：C_Cong (5星)**
    - **关键亮点**：通过画图模拟不同人数情况下朋友关系的变化来找规律，思路清晰直观，易于理解。
    - **个人心得**：提到题目翻译可能误导人，强调了理解题意的重要性。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int T,n;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		(n<2)?printf("0\n"):printf("%d\n",n-2);
	}
	return 0;
} 
```
核心实现思想：根据推导出的规律，对输入的 \(n\) 进行判断，若 \(n < 2\) 输出0，否则输出 \(n - 2\) 。
 - **作者：xxzjbd (4星)**
    - **关键亮点**：从整体的朋友关系构造角度出发，通过分析删除边对朋友数量的影响得出结论，方法简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		if(n<2)cout<<0<<endl;
		else cout<<n-2<<endl;
	}
	return 0;
}
```
核心实现思想：同样根据规律，对输入的 \(n\) 进行判断，输出相应结果。
 - **作者：rayluo (4星)**
    - **关键亮点**：从朋友离开条件出发，分析出要牺牲尽量少的人且其朋友数小于剩下的人，进而构造出一种可行的朋友关系图，逻辑严谨。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define in inline
#define ll long long

in int read()
{
	int w=0,r=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')r=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		w=(w<<1)+(w<<3)+(ch^48);
		ch=getchar();
	}
	return w*r;
}

int T,n;

int main()
{
	T=read();
	while(T--)
	{
		n=read();
		if(n<=2)
		{
			puts("0");
		}
		else
		{
			cout<<n-2<<endl;
		}
	}
	return 0;
} 
```
核心实现思想：通过自定义的快速读入函数读取数据，根据规律判断 \(n\) 的情况并输出结果。

### 最优关键思路或技巧
通过画图、构造朋友关系等方式找规律，发现当 \(n \geq 2\) 时，牺牲两个朋友数相对较少的人（如构造让两人与其余人都为朋友但两人之间不是朋友的关系），可使剩下 \(n - 2\) 人。这种从简单情况入手找规律以及合理构造关系的思维方式是解决本题的关键。

### 可拓展之处
此类题目属于根据特定规则找规律的数学类题目，类似套路是从简单情形开始枚举，分析变化规律并推广到一般情况。对于涉及关系构造的题目，要从满足条件的角度出发去设计合理的结构。

### 推荐洛谷题目
 - [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：通过找规律或动态规划解决棋盘上棋子移动的问题，与本题找规律的思路类似。
 - [P1464 Function](https://www.luogu.com.cn/problem/P1464)：需要根据给定的函数定义找规律来计算结果，锻炼从规则中挖掘规律的能力。
 - [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过对数字计算规则的分析找规律，与本题在思维方式上有相似之处。 

---
处理用时：40.93秒