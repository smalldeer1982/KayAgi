# [CCC 2020] Dog Treats

## 题目背景

本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Junior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/2020CCCJrProblemSet.html) T1 Dog Treats。

## 题目描述

小狗 Barley 喜欢零食。在一天结束时，他的心情取决于他在一天中收到的零食的大小与数量。

零食有三种大小：小、中、大。若这一天它获得小零食 $S$ 份，中零食 $M$ 份，大零食 $L$ 份，则他的快乐值可以用以下公式来衡量：

$1 \times S+2\times M + 3\times L$

如果 Barley 的快乐值大于等于 $10$，那么它是快乐的。否则，他会感到十分伤心。请判断 Barley 在一天结束时心情是快乐的还是伤心的。

## 说明/提示

**本题采用捆绑测试**。

#### 【样例解释】
对于第一组样例，易得快乐值为 $1 \times 3+2\times 1 + 3\times 0=5$，而 $5< 10$，则 Barley 是伤心的。

对于第二组样例，易得快乐值为 $1 \times 3+2\times 2 + 3\times 1=10$，而 $10 \geq 10$，则 Barley 是快乐的。

## 样例 #1

### 输入

```
3
1
0```

### 输出

```
sad```

## 样例 #2

### 输入

```
3
2
1```

### 输出

```
happy```

# 题解

## 作者：niuniudundun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11576)

# 题目大意

计算 $1S+2M+3L$ 是否大于等于 $10$，是则输出 `happy`，否则输出 `sad`。

# 解法

使用题目中的公式计算快乐值 $happy=1S+2M+3L$，使用 `if` 判断 $happy$ 是否大于等于 $10$，是则输出 `happy`，否则输出 `sad`。

代码：

```cpp
#include<iostream>
using namespace std;
int s,m,l,happy;
int main(){
	cin>>s>>m>>l;
	happy=1*s+2*m+3*l;
	if(happy>=10){
		cout<<"happy\n";
	}else{
		cout<<"sad\n";
	}
	return 0;
}
```

---

## 作者：Fish_redflying (赞：1)

依题意模拟即可。

数据范围很小，int 即可胜任。

值得一提的是，三目运算符做到了很好的压行作用，使代码简洁明了。

用法是

`<条件>?<条件真对应的值>:<条件伪对应的值>`

如

```cpp
cout << (3>2 ? 114 : 514) << endl;
```

注意**括号**一定要加，三目运算符的等级比左右位移符号的等级低。

如下即代码。

```cpp
#include<cstdio>
int s,m,l;
int main()
{
    scanf("%d%d%d",&s,&m,&l);
    printf("%s",(s+m*2+l*3)>=10?"happy":"sad");
}
```

---

## 作者：GSQ0829 (赞：1)

### 思路：
超级简单的入门题，就是输入完之后按照公式 $1 \times S+2\times M + 3\times L$ 算出他的快乐值，再判断一下，就可以了。


---
### code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int s, m, l, ans = 0;

int main() {
	cin >> s >> m >> l;
	ans = s + 2 * m + 3 * l;
	if (ans >= 10) cout << "happy";
	else cout << "sad";
	return 0;
}
```

---

## 作者：Mzh2012 (赞：0)

## 题目思路

非常简单的一道水题，先输入所有的数据，再根据题目所给的计算快乐值的公式判断快乐值是否大于 $10$ 即可。

快乐值公式：$1 \times S+2\times M + 3\times L$。

## 代码


```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	int s,m,l;
	cin>>s>>m>>l;
	if(s+2*m+3*l>=10) cout<<"happy";
	else cout<<"sad";

	return 0;
}

```

---

