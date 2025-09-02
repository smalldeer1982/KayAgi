# 题目信息

# The Fair Nut and String

## 题目描述

The Fair Nut found a string $ s $ . The string consists of lowercase Latin letters. The Nut is a curious guy, so he wants to find the number of strictly increasing sequences $ p_1, p_2, \ldots, p_k $ , such that:

1. For each $ i $ ( $ 1 \leq i \leq k $ ), $ s_{p_i} = $ 'a'.
2. For each $ i $ ( $ 1 \leq i < k $ ), there is such $ j $ that $ p_i < j < p_{i + 1} $ and $ s_j = $ 'b'.

The Nut is upset because he doesn't know how to find the number. Help him.

This number should be calculated modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, there are $ 5 $ possible sequences. $ [1] $ , $ [4] $ , $ [5] $ , $ [1, 4] $ , $ [1, 5] $ .

In the second example, there are $ 4 $ possible sequences. $ [2] $ , $ [3] $ , $ [4] $ , $ [5] $ .

In the third example, there are $ 3 $ possible sequences. $ [1] $ , $ [3] $ , $ [4] $ .

## 样例 #1

### 输入

```
abbaa
```

### 输出

```
5```

## 样例 #2

### 输入

```
baaaa
```

### 输出

```
4```

## 样例 #3

### 输入

```
agaa
```

### 输出

```
3```

# AI分析结果

### 题目内容重写

#### The Fair Nut and String

**题目描述**

The Fair Nut 找到了一个字符串 $s$。该字符串由小写拉丁字母组成。Nut 是一个好奇的家伙，因此他想找到严格递增的序列 $p_1, p_2, \ldots, p_k$ 的数量，满足以下条件：

1. 对于每个 $i$（$1 \leq i \leq k$），$s_{p_i} = $ 'a'。
2. 对于每个 $i$（$1 \leq i < k$），存在一个 $j$ 使得 $p_i < j < p_{i + 1}$ 且 $s_j = $ 'b'。

Nut 很沮丧，因为他不知道如何找到这个数量。请帮助他。

这个数量应该对 $10^9 + 7$ 取模。

**说明/提示**

在第一个样例中，有 $5$ 个可能的序列：$[1]$，$[4]$，$[5]$，$[1, 4]$，$[1, 5]$。

在第二个样例中，有 $4$ 个可能的序列：$[2]$，$[3]$，$[4]$，$[5]$。

在第三个样例中，有 $3$ 个可能的序列：$[1]$，$[3]$，$[4]$。

**样例 #1**

**输入**

```
abbaa
```

**输出**

```
5
```

**样例 #2**

**输入**

```
baaaa
```

**输出**

```
4
```

**样例 #3**

**输入**

```
agaa
```

**输出**

```
3
```

### 算法分类

**动态规划**

### 题解分析与结论

本题的核心在于统计满足条件的子序列数量，特别是形如 $"a"$ 或 $"aba \ldots aba"$ 的子序列。大多数题解都采用了动态规划的思路，通过维护一个变量来记录当前能够形成的子序列数量，并在遇到字符 'a' 或 'b' 时进行相应的更新。

### 所选高分题解

#### 题解1：Super_Cube (5星)

**关键亮点**

- 思路清晰，直接通过维护变量 `ans` 和 `x` 来记录当前能够形成的子序列数量。
- 代码简洁，逻辑明了，易于理解。
- 通过遇到 'a' 和 'b' 时的不同处理，巧妙地实现了动态规划的思路。

**核心代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int ans,x;
int main(){
	cin>>a;
	for(int i=0;i<a.size();i++){
		if(a[i]=='a')ans=(ans+x+1)%1000000007;
		if(a[i]=='b')x=ans;
	}cout<<ans;
	return 0;
}
```

#### 题解2：cqbztz2 (4星)

**关键亮点**

- 使用了乘法原理和加法原理，将问题分解为多个区间的子问题。
- 通过维护 `sum` 和 `ans` 变量，实现了对子序列数量的统计。
- 代码逻辑清晰，但相比 Super_Cube 的题解稍显复杂。

**核心代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,sum,mod=1e9+7;
string s;
int main(){
    cin>>s;
    s[s.length()]='b';
    for(int i=0;i<=s.length();i++){
        if(s[i]=='a'){
            sum++;
        }
        else if(s[i]=='b'&&sum!=0){
            ans=((ans+ans*sum+sum)%mod+mod)%mod;
            sum=0;
        }
    }
    cout<<ans;
    return 0;
}
```

#### 题解3：liaoz123 (4星)

**关键亮点**

- 通过维护 `pre` 变量来记录最近的 'b' 之前的合法子序列数量，思路清晰。
- 代码简洁，逻辑明了，易于理解。
- 通过遇到 'a' 和 'b' 时的不同处理，巧妙地实现了动态规划的思路。

**核心代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
typedef long long ll;
ll ans,pre;
const ll mod=1e9+7;
int main(){
	cin>>a;
	int len=a.length();
	for(int i=0;i<len;i++){
		if(a[i]=='a')
		ans=(ans+pre+1)%mod;
		if(a[i]=='b')
		pre=ans;
	}
	cout<<ans<<endl;
	return 0;
}
```

### 最优关键思路或技巧

1. **动态规划维护变量**：通过维护一个变量来记录当前能够形成的子序列数量，并在遇到 'a' 和 'b' 时进行相应的更新。
2. **取模运算**：在每次更新答案时，都要对 $10^9 + 7$ 取模，防止数值溢出。
3. **分情况讨论**：遇到 'a' 时，考虑单独形成子序列和与之前的子序列结合形成新子序列的情况；遇到 'b' 时，更新记录变量。

### 可拓展之处

类似的问题可以通过动态规划的思路来解决，特别是涉及到子序列计数的问题。可以通过维护变量来记录当前状态，并根据不同情况进行更新。

### 推荐题目

1. [P1045 子串计数](https://www.luogu.com.cn/problem/P1045)
2. [P1046 最长公共子序列](https://www.luogu.com.cn/problem/P1046)
3. [P1047 最长上升子序列](https://www.luogu.com.cn/problem/P1047)

---
处理用时：40.83秒