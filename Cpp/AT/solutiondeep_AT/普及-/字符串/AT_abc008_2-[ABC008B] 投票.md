# 题目信息

# [ABC008B] 投票

## 题目描述

题目大意
某个组织进行了选拔领导人的选举。组织由n人组成，每个人都写了最领导的人物的名字。投票数最多的人的名字就是领袖。如果有多个得票数最多的人物，输出其中一个即可。

## 说明/提示

1<=名字长度<=50


感谢@Andysun06  提供的翻译

## 样例 #1

### 输入

```
4

taro

jiro

taro

saburo```

### 输出

```
taro```

## 样例 #2

### 输入

```
1

takahashikun```

### 输出

```
takahashikun```

## 样例 #3

### 输入

```
9

a

b

c

c

b

c

b

d

e```

### 输出

```
b```

# AI分析结果

【题目内容】
# [ABC008B] 投票

## 题目描述

题目大意
某个组织进行了选拔领导人的选举。组织由n人组成，每个人都写了最领导的人物的名字。投票数最多的人的名字就是领袖。如果有多个得票数最多的人物，输出其中一个即可。

## 说明/提示

1<=名字长度<=50


感谢@Andysun06  提供的翻译

## 样例 #1

### 输入

```
4

taro

jiro

taro

saburo```

### 输出

```
taro```

## 样例 #2

### 输入

```
1

takahashikun```

### 输出

```
takahashikun```

## 样例 #3

### 输入

```
9

a

b

c

c

b

c

b

d

e```

### 输出

```
b```

【综合分析与结论】
这些题解提供了多种解决“投票”问题的思路，主要可分为以下几类：
1. **使用`map`**：大部分题解采用`map`来统计每个名字的出现次数，利用`map`能方便地将字符串（名字）与整数（票数）关联起来。如翼德天尊、lzqy_、Nt_Tsumiki等的题解。
2. **排序统计**：通过对名字进行排序，然后统计相邻相同名字的数量，找出出现次数最多的名字，如zjyqwq、MarchKid_Joe的题解。
3. **暴力模拟**：使用二重循环枚举每一个字符串和它之后的字符串，比较是否相等来统计票数，如cjZYZtcl的题解。
4. **结构体排序**：定义结构体存储名字和票数，对结构体数组按票数排序，输出票数最多的名字，如A_Plus_Gu的题解。
5. **哈希**：使用双模数哈希来加快比较速度，避免哈希冲突，如1lgorithm的题解。

解决的难点在于如何高效地统计每个名字的出现次数，并找出出现次数最多的名字。`map`的使用能很好地解决这个问题，它可以直接根据名字快速找到对应的票数并进行更新。

【所选的题解】
- 翼德天尊（4星）
  - 关键亮点：思路清晰，详细介绍了`map`的使用，代码简洁且注释详细，适合初学者。
  - 个人心得：无
- lzqy_（4星）
  - 关键亮点：在使用`map`的基础上，提供了去重的思路，提高了效率，同时对`map`的介绍较为详细。
  - 个人心得：作为不太熟悉指针的人，换了不用迭代器的方法来统计票数。
- MarchKid_Joe（4星）
  - 关键亮点：采用排序统计的方法，思路简单直接，代码实现清晰，对边界情况有提示。
  - 个人心得：无

【重点代码】
1. **翼德天尊的代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxn;
string name;
map<string,int> m;
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
    	string a;
    	cin>>a;
    	m[a]++;
    	if (m[a]>maxn){
    		maxn=m[a];
    		name=a;
		}
	}
	cout<<name<<endl;
    return 0;
}
```
核心实现思想：使用`map`统计每个名字的票数，在统计过程中不断更新最大票数和对应的名字。

2. **lzqy_的代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
string a[100000];
int cnt;
map<string,int>m; 
int main()
{
  string s;
  int n;
  cin>>n;
  for(int i=0;i<n;i++)
  {
   cin>>s;
   if(m[s]==0)
   {
   	cnt++;
   	a[cnt]=s;
   }
	m[s]++;
  }
  int Max=-1;
  string ans;
  for(int i=1;i<=cnt;i++)
  if(Max<m[a[i]])
  Max=m[a[i]],ans=a[i];
  cout<<ans<<endl;
  return 0;
}
```
核心实现思想：使用`map`统计票数，同时用数组存储去重后的名字，最后遍历数组找出票数最多的名字。

3. **MarchKid_Joe的代码**
```cpp
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
string s[52] , ansn;
int maxn , t = 1 , n;
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i ++) cin >> s[i];
	sort (s + 1,s + n + 1);
	for (int i = 2;i <= n + 1;i ++)
	{
		if (s[i] != s[i-1])
		{
			if (t > maxn)
			{
				maxn = max (maxn,t);
				ansn = s[i-1];
			}
			t = 1;
		}
		else t ++;
	}
	cout << ansn << endl;
	return 0;
}
```
核心实现思想：先对名字进行排序，然后遍历排序后的数组，统计相邻相同名字的数量，找出出现次数最多的名字。

【最优关键思路或技巧】
- **使用`map`**：`map`是解决此类问题的高效数据结构，它能方便地将字符串与整数关联起来，快速统计每个名字的出现次数。
- **排序统计**：对名字进行排序后，相邻相同名字的数量就是该名字的票数，这种方法简单直接。

【可拓展之处】
同类型题或类似算法套路：
- 统计单词出现频率的问题，可使用`map`统计每个单词的出现次数。
- 统计不同颜色球的数量，同样可以用`map`将颜色与数量关联起来。

【推荐题目】
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)：可使用`map`统计每个数出现的次数，进而解决问题。
2. [P1497 木牛流马](https://www.luogu.com.cn/problem/P1497)：需要统计不同物品的数量，可借助`map`实现。
3. [P1766 液体滴落](https://www.luogu.com.cn/problem/P1766)：可能需要对不同状态进行计数，`map`能发挥作用。

【个人心得摘录与总结】
- lzqy_：作为不太熟悉指针的人，换了不用迭代器的方法来统计票数，提醒我们在遇到不熟悉的知识时，可以寻找其他可行的方法来解决问题。

---
处理用时：45.13秒