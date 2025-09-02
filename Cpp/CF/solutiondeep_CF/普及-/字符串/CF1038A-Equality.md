# 题目信息

# Equality

## 题目描述

### 题目大意：
给定一个长度为$n$的字符串和$k$，问这个字符串包含字母表前$k$个大写字母并且数量相同的子序列最长是多少

## 样例 #1

### 输入

```
9 3
ACAABCCAB
```

### 输出

```
6```

## 样例 #2

### 输入

```
9 4
ABCABCABC
```

### 输出

```
0```

# AI分析结果

### 题目内容重写
#### 题目描述
给定一个长度为$n$的字符串和$k$，问这个字符串包含字母表前$k$个大写字母并且数量相同的子序列最长是多少。

#### 样例 #1
##### 输入
```
9 3
ACAABCCAB
```
##### 输出
```
6
```

#### 样例 #2
##### 输入
```
9 4
ABCABCABC
```
##### 输出
```
0
```

### 题解分析与结论
#### 综合分析与结论
所有题解的核心思路都是统计字符串中前$k$个大写字母的出现次数，然后取最小值，最后输出最小值乘以$k$。这种思路简单直接，且时间复杂度为$O(n)$，能够高效解决问题。

#### 最优关键思路或技巧
1. **统计字母出现次数**：使用数组或哈希表统计每个字母的出现次数。
2. **取最小值**：在前$k$个字母中取出现次数的最小值。
3. **输出结果**：最小值乘以$k$即为所求的最长子序列长度。

#### 可拓展之处
1. **子序列问题**：类似的问题可以扩展到其他字符集或更复杂的子序列条件。
2. **统计与排序**：统计字母出现次数并进行排序的思路可以应用于其他需要统计和比较的问题。

### 推荐题目
1. [P1038 子序列](https://www.luogu.com.cn/problem/P1038)
2. [P1040 统计字符](https://www.luogu.com.cn/problem/P1040)
3. [P1041 最长公共子序列](https://www.luogu.com.cn/problem/P1041)

### 所选高分题解
#### 题解作者：piggymichael (赞：2)
##### 星级：4星
##### 关键亮点
- 思路清晰，代码简洁。
- 使用数组统计字母出现次数，直接取最小值并输出结果。

##### 核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[30],minn=0x3f3f3f3f;
string s;
int main()
{
	cin>>n>>k>>s;
	for(int i=0;i<s.size();++i)
		a[s[i]-'A'+1]++;
	for(int i=1;i<=k;++i)
		minn=min(minn,a[i]);
	cout<<minn*k<<endl;
	return 0;
}
```

#### 题解作者：togeth1 (赞：0)
##### 星级：4星
##### 关键亮点
- 详细解释了子序列的定义和注意事项。
- 代码结构清晰，易于理解。

##### 核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[10010],ans=0x3f3f3f;
char s[10010];
int main()
{
    cin>>n>>k>>(s+1);
    int n=strlen(s+1);
    for(int i=1; i<=n; i++)a[s[i]-'A'+1]++;
    for(int i=1; i<=k; i++)
    	ans=min(ans,a[i]);
    cout<<ans*k;
    return 0;
}
```

#### 题解作者：Sternenlicht (赞：0)
##### 星级：4星
##### 关键亮点
- 使用桶记录字符出现次数，思路清晰。
- 代码中包含了详细的注释，便于理解。

##### 核心代码
```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

int n,k,ans=INF,tong[30]; 
string s;
int main(){
	n=read(),k=read();cin>>s;
	for (int i=0;i<s.size();i++)
		tong[s[i]-'A'+1]++;
	for (int i=1;i<=k;i++)
		ans=min(ans,tong[i]);
	write(ans*k);
	return 0;
}
```

### 个人心得摘录
- **togeth1**：强调了子序列不一定要连续，提醒了在解题时需要注意的细节。
- **Sternenlicht**：详细解释了为什么最小值乘以$k$是正确答案，增强了理解。

### 通用建议与扩展思路
- **注意细节**：在解决子序列问题时，务必明确子序列的定义，避免误解。
- **优化统计**：使用数组或哈希表统计字符出现次数是常见且高效的策略，可以应用于多种统计问题。

---
处理用时：31.04秒