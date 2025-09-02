# 题目信息

# Blocks

## 题目描述

There are $ n $ blocks arranged in a row and numbered from left to right, starting from one. Each block is either black or white.

You may perform the following operation zero or more times: choose two adjacent blocks and invert their colors (white block becomes black, and vice versa).

You want to find a sequence of operations, such that they make all the blocks having the same color. You don't have to minimize the number of operations, but it should not exceed $ 3 \cdot n $ . If it is impossible to find such a sequence of operations, you need to report it.

## 说明/提示

In the first example, it is possible to make all blocks black in $ 3 $ operations. Start with changing blocks $ 6 $ and $ 7 $ , so the sequence is "BWWWWBBB". Then change blocks $ 2 $ and $ 3 $ , so the sequence is "BBBWWBB". And finally, change blocks $ 4 $ and $ 5 $ , so all blocks are black.

It is impossible to make all colors equal in the second example.

All blocks are already white in the third example.

In the fourth example it is possible to make all blocks white in two operations: first operation is to change blocks $ 2 $ and $ 3 $ (so the sequence is "BBW"), and then change blocks $ 1 $ and $ 2 $ (so all blocks are white).

## 样例 #1

### 输入

```
8
BWWWWWWB
```

### 输出

```
3
6 2 4
```

## 样例 #2

### 输入

```
4
BWBB
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
WWWWW
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3
BWB
```

### 输出

```
2
2 1 
```

# AI分析结果

### 题目内容重写

#### 题目描述

有 $n$ 个方块排成一行，从左到右编号为 1 到 $n$。每个方块要么是黑色，要么是白色。

你可以进行以下操作零次或多次：选择两个相邻的方块，并将它们的颜色反转（白色变为黑色，黑色变为白色）。

你希望找到一系列操作，使得所有方块的颜色相同。你不需要最小化操作次数，但操作次数不应超过 $3 \cdot n$。如果无法找到这样的操作序列，你需要报告。

#### 说明/提示

在第一个样例中，可以通过 3 次操作将所有方块变为黑色。首先反转方块 6 和 7，序列变为 "BWWWWBBB"。然后反转方块 2 和 3，序列变为 "BBBWWBB"。最后反转方块 4 和 5，所有方块变为黑色。

在第二个样例中，无法将所有方块变为同一种颜色。

在第三个样例中，所有方块已经是白色。

在第四个样例中，可以通过两次操作将所有方块变为白色：首先反转方块 2 和 3，序列变为 "BBW"。然后反转方块 1 和 2，所有方块变为白色。

#### 样例 #1

##### 输入

```
8
BWWWWWWB
```

##### 输出

```
3
6 2 4
```

#### 样例 #2

##### 输入

```
4
BWBB
```

##### 输出

```
-1
```

#### 样例 #3

##### 输入

```
5
WWWWW
```

##### 输出

```
0
```

#### 样例 #4

##### 输入

```
3
BWB
```

##### 输出

```
2
2 1 
```

### 算法分类
模拟

### 题解分析与结论

#### 题解对比

1. **破壁人五号**：
   - **思路**：从左到右遍历方块，遇到黑色方块就反转它和下一个方块。如果最后一个方块是黑色且 $n$ 是奇数，则可以通过反转前 $n-1$ 个方块使其变为黑色；否则无解。
   - **难点**：处理最后一个方块的特殊情况，特别是当 $n$ 为偶数时无解的证明。
   - **评分**：4星
   - **关键亮点**：通过奇偶性判断无解情况，思路清晰，代码简洁。

2. **过氧化氢_syq0057**：
   - **思路**：从左到右遍历方块，遇到黑色方块就反转它和下一个方块。如果最后一个方块是黑色且 $n-1$ 是偶数，则可以通过反转前 $n-1$ 个方块使其变为黑色；否则无解。
   - **难点**：处理最后一个方块的特殊情况，特别是当 $n-1$ 为奇数时无解的证明。
   - **评分**：4星
   - **关键亮点**：通过奇偶性判断无解情况，思路清晰，代码简洁。

3. **IYSY2009I**：
   - **思路**：从左到右遍历方块，遇到需要改变的方块就反转它和下一个方块。通过统计黑色和白色方块的奇偶性来判断是否有解。
   - **难点**：处理最后一个方块的特殊情况，特别是当两种颜色的方块都为奇数时无解的证明。
   - **评分**：4星
   - **关键亮点**：通过奇偶性判断无解情况，思路清晰，代码简洁。

#### 最优关键思路

- **奇偶性判断**：通过统计黑色和白色方块的奇偶性来判断是否有解。如果两种颜色的方块都为奇数，则无解。
- **模拟操作**：从左到右遍历方块，遇到需要改变的方块就反转它和下一个方块。

#### 可拓展之处

- **类似题目**：翻硬币问题、开关问题等，都可以通过模拟操作和奇偶性判断来解决。
- **优化思路**：可以通过预处理或动态规划来优化操作次数，但在此题中由于操作次数限制较宽松，模拟操作已经足够。

#### 推荐题目

1. [P8597 翻硬币](https://www.luogu.com.cn/problem/P8597)
2. [P2004 费解的开关](https://www.luogu.com.cn/problem/P2004)
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

### 精选题解

#### 破壁人五号

**星级**：4星  
**关键亮点**：通过奇偶性判断无解情况，思路清晰，代码简洁。

```cpp
#include<bits/stdc++.h>
using namespace std;
int getint(){
    int ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
	}
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}
 
int a[1000];
vector<int>sol;
int main(){
    int n=getint();
    for(int i=1;i<=n;i++){
        char c=' ';
        cin>>c;
        a[i]=(c=='W'?0:1);
    }
    for(int i=1;i<n;i++){
        if(a[i]){
            sol.push_back(i);
            a[i]=1-a[i];
            a[i+1]=1-a[i+1];
        }
    }
    if(a[n]){
        if(n&1){
            for(int i=1;i<n;i+=2){
                sol.push_back(i);
            }
        }else{
            puts("-1");
            return 0;
        }
    }
    cout<<sol.size()<<endl;
    for(int i=0;i<sol.size();i++){
        cout<<sol[i]<<" ";
    }
    return 0;
}
```

#### 过氧化氢_syq0057

**星级**：4星  
**关键亮点**：通过奇偶性判断无解情况，思路清晰，代码简洁。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
using namespace std;
const int N = 205;
const int M = 605;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int n;
char s[N];
int ans[M], op;
int main() {
	scanf("%d%s", &n, s);
	for (int i=0; i<n-1; i++) {//不能到最后一个
		if (s[i] == 'B') {
			s[i] = 'W';
			ans[++op] = i;
			if (s[i + 1] == 'B') s[i + 1] = 'W';
			else s[i + 1] = 'B';
		}
	}
	if (s[n - 1] != 'W') {
		if (n & 1) {
			for (int i=0; i<n-1; i+=2)
				ans[++op] = i;
		}
		else {
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n", op);
	for (int i=1; i<=op; i++)
		printf("%d ", ans[i] + 1);//程序中字符串下标从0开始，题目要求从1
	return 0;
}
```

#### IYSY2009I

**星级**：4星  
**关键亮点**：通过奇偶性判断无解情况，思路清晰，代码简洁。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
int op[605];
int main(){
	int n=read();
	string s;
	cin>>s;
	int b=0,w=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='B') b++;
		else w++;
	}
	if(b%2&&w%2){
		printf("-1");
		return 0;
	}
	int cnt=0;
	if(b%2==0){
		for(int i=0;i<s.size();i++)
			if(s[i]=='B'){
				cnt++;
				op[cnt]=i+1;
				s[i]='W';
				if(s[i+1]=='W') s[i+1]='B';
				else s[i+1]='W';				
			}
		printf("%d\n",cnt);
		for(int i=1;i<=cnt;i++)
			printf("%d ",op[i]);
		return 0;
	}
	for(int i=0;i<s.size();i++)
		if(s[i]=='W'){
			cnt++;
			op[cnt]=i+1;
			s[i]='B';
			if(s[i+1]=='W') s[i+1]='B';
			else s[i+1]='W';				
		}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",op[i]);
	return 0;
}
```

---
处理用时：63.32秒