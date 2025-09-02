# [CCC 2021 J3] Secret Instructions

## 题目描述

多组数据。

对于每组数据读入 $5$ 个数字字符。

- 如果前两个之和为奇数，输出 `left`；
- 如果前两个之和为非零偶数，输出 `right`；
- 如果前两个之和为零，输出 `left` 或 `right` 取决于上组数据。

然后输出一个空格与后三个数字字符。

## 说明/提示

读入的第三个字符不会为 $0$。

第一组数据不会以 $00$ 开头。

译自 [CCC2021 J3](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/juniorEF.pdf)。

## 样例 #1

### 输入

```
57234
00907
34100
99999
```

### 输出

```
right 234
right 907
left 100
```

# 题解

## 作者：zhang_kevin (赞：4)

# Solution

这题还是很好做的。

我们可以用一个变量记录当前的答案，以便在和为零时输出。

另外建议用 $5$ 个字符输入，避免算位数错误。

最后，判断即可。分别为前两项和为奇数，和为正偶数，和为 $0$。

注意，字符计算的时候记得减去字符零，我就因为这个在测试点 $9$ 错了两次。

# Code

```cpp
// Author: zhang_kevin
// Problem Name: P9022 [CCC2021 J3] Secret Instructions
// URL: https://www.luogu.com.cn/problem/P9022
// Memory Limit: 128 MB
// Time Limit: 500000 ms
// Created: 2023-02-05 13:44:54

#include<bits/stdc++.h>
using namespace std;
int main(){
	string ans = "";
	char c1, c2, c3, c4, c5;
	cin >> c1 >> c2 >> c3 >> c4 >> c5;
	if((c1+c2) & 1) ans = "left";
	else ans = "right";
	while(c1 + c2 + c3 + c4 + c5 - 5 * '0' != 45){
		if((c1-'0'+c2-'0') & 1){
			ans = "left";
			cout << ans << " " << c3 << c4 << c5 << endl;
		}else if(c1 - '0' + c2 - '0' != 0){
			ans = "right";
			cout << ans << " " << c3 << c4 << c5 << endl;
		}else{
			cout << ans << " " << c3 << c4 << c5 << endl;
		}
		cin >> c1 >> c2 >> c3 >> c4 >> c5;
	}
	return 0;
}
```

---

## 作者：ZepX_D (赞：4)

### 题意
输入一个字符串，前两个数字和为奇数时输出 $ \text{left} $，为非零偶数时输出 $ \text{right} $，为 0 时输出上次的答案。
并且每次都输出最后三位数字字符。
### 做法
每次输入后模拟判断，再用一个字符串来记录上次的答案

```cpp
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string s,k;cin >> s;//k用来记录上次的答案
	while(s != "99999")//当读入为99999时跳出
	{
		int sum = s[0]-48+s[1]-48;//将数字字符转换为数字，其实这里不转换也可以，不影响奇偶性，不过判断是否为零要变为判断是否为96
		if (!sum) cout << k;//为零直接输出上次答案
		else if (!(sum&1)) printf("right"),k = "right"; //判断是否为偶数，sum&1相当于sum&2
		else printf("left"),k = "left";
		printf(" %c%c%c\n",s[2],s[3],s[4]);//输出后三个字符
		cin >>s;
	}
}
```


---

