# 题目信息

# [AGC017B] Moderate Differences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc017/tasks/agc017_b

$ N $ 個のマスが一列に並んでいます． 一番左のマスには整数 $ A $ が，一番右のマスには整数 $ B $ が書かれており，他のマスには何も書かれていません．

青橋君は，何も書かれていないマスに整数を書き込み，次の条件を満たすようにしたいです：

- どの隣接する $ 2 $ マスについても，書かれている整数の差は $ C $ 以上 $ D $ 以下である．

青橋君は，この条件を満たす限り，いくらでも大きい整数や小さい整数を書き込むことができます． 青橋君が条件を満たすように整数を書き込むことができるかを判定してください．

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 500000 $
- $ 0\ \leq\ A\ \leq\ 10^9 $
- $ 0\ \leq\ B\ \leq\ 10^9 $
- $ 0\ \leq\ C\ \leq\ D\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

例えば，左のマスから順に $ 1,\ -1,\ 3,\ 7,\ 5 $ となるように整数を書き込めばよいです．

## 样例 #1

### 输入

```
5 1 5 2 4```

### 输出

```
YES```

## 样例 #2

### 输入

```
4 7 6 4 5```

### 输出

```
NO```

## 样例 #3

### 输入

```
48792 105960835 681218449 90629745 90632170```

### 输出

```
NO```

## 样例 #4

### 输入

```
491995 412925347 825318103 59999126 59999339```

### 输出

```
YES```

# AI分析结果

### 题目内容重写

$ N $ 个格子排成一列，最左边的格子写有整数 $ A $，最右边的格子写有整数 $ B $，其他格子为空。青桥君需要在空白的格子中填入整数，使得任意相邻两个格子中的整数差的绝对值在 $ [C, D] $ 之间。青桥君可以填入任意大小的整数，只要满足条件即可。请判断是否存在满足条件的填数方案。

### 说明/提示

#### 约束条件
- $ 3 \leq N \leq 500000 $
- $ 0 \leq A \leq 10^9 $
- $ 0 \leq B \leq 10^9 $
- $ 0 \leq C \leq D \leq 10^9 $
- 输入均为整数

### 样例解释

#### 样例 1
输入：
```
5 1 5 2 4
```
输出：
```
YES
```
解释：例如，从左到右依次填入 $ 1, -1, 3, 7, 5 $，满足条件。

#### 样例 2
输入：
```
4 7 6 4 5
```
输出：
```
NO
```

#### 样例 3
输入：
```
48792 105960835 681218449 90629745 90632170
```
输出：
```
NO
```

#### 样例 4
输入：
```
491995 412925347 825318103 59999126 59999339
```
输出：
```
YES
```

---

### 题解分析与结论

#### 综合分析与结论
本题的核心在于判断是否存在一种填数方案，使得从 $ A $ 到 $ B $ 的路径中，每一步的增量都在 $ [C, D] $ 或 $ [-D, -C] $ 之间。题解主要分为两类：
1. **枚举法**：通过枚举正负增量的数量，计算 $ B $ 是否在可能的范围内。时间复杂度为 $ O(N) $。
2. **数学推导法**：通过数学公式直接判断 $ B $ 是否在某个区间内，时间复杂度为 $ O(1) $。

最优的思路是**数学推导法**，通过将问题转化为区间覆盖问题，直接判断 $ B $ 是否在某个区间内，避免了枚举带来的时间复杂度问题。

---

### 精选题解

#### 题解1：BLUESKY007（评分：5星）
**关键亮点**：
- 通过数学推导，将问题转化为区间覆盖问题，直接判断 $ B $ 是否在某个区间内。
- 时间复杂度为 $ O(1) $，效率极高。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;

int n,a,b,c,d,delta,whole;

double nxt,half=0.5,maxhalf,lft;

int main(){
    scanf("%d%d%d%d%d",&n,&a,&b,&c,&d);
    nxt+=c+d;
    nxt/=2;
    half=nxt-c;
    maxhalf=half*(n-1);
    delta=abs(a-b);
    if(delta>(n-1)*nxt+maxhalf){
        printf("NO\n");
        return 0;
    }
    whole=(int)(delta/nxt);
    lft=delta-nxt*whole;
    if(n&1){
        if(whole&1){
            lft=nxt-lft;
            if(lft<=maxhalf){
                printf("YES\n");
                return 0;
            }
            else{
                printf("NO\n");
                return 0;
            }
        }
        else{
            if(lft<=maxhalf){
                printf("YES\n");
                return 0;
            }
            else{
                printf("NO\n");
                return 0;
            }
        }
    }
    else{
        if(whole&1){
            if(lft<=maxhalf){
                printf("YES\n");
                return 0;
            }
            else{
                printf("NO\n");
                return 0;
            }
        }
        else{
            lft=nxt-lft;
            if(lft<=maxhalf){
                printf("YES\n");
                return 0;
            }
            else{
                printf("NO\n");
                return 0;
            }
        }
    }
    return 0;
}
```

#### 题解2：chl090410（评分：4星）
**关键亮点**：
- 通过枚举正负增量的数量，计算 $ B $ 是否在可能的范围内。
- 时间复杂度为 $ O(N) $，虽然不如 $ O(1) $ 高效，但思路清晰，易于理解。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,e;
signed main(){
	cin>>a>>b>>c>>d>>e;
	if((c%(d+e)+(d+e)-(b+d*(a-1))%(d+e))%(d+e)<=(e-d)*(a-1)&&e*(a-1)+b>=c) cout<<"YES";
	else cout<<"NO";
	return 0;
}
```

#### 题解3：water_tomato（评分：4星）
**关键亮点**：
- 通过枚举正负增量的数量，计算 $ B $ 是否在可能的范围内。
- 时间复杂度为 $ O(N) $，代码简洁，逻辑清晰。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,A,B,C,D,Max,Min;
signed main(){
	scanf("%lld%lld%lld%lld%lld",&n,&A,&B,&C,&D);
	for(int i=0;i<=n-1;i++){
		int tB=B+C*(n-1-2*i);
		int Max=A+i*(D-C);
		int Min=A-(n-1-i)*(D-C);
		if(tB>=Min&&tB<=Max){
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
```

---

### 最优思路总结
最优的思路是通过数学推导，将问题转化为区间覆盖问题，直接判断 $ B $ 是否在某个区间内。这种方法避免了枚举带来的时间复杂度问题，效率极高。

---

### 拓展与举一反三
类似的问题可以通过将问题转化为区间覆盖或数学推导来解决，避免枚举带来的时间复杂度问题。例如，判断是否存在某种路径满足特定条件的问题，都可以考虑类似的思路。

---

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

---

### 个人心得摘录
- **BLUESKY007**：通过数学推导，将问题转化为区间覆盖问题，直接判断 $ B $ 是否在某个区间内，避免了枚举带来的时间复杂度问题。
- **chl090410**：通过枚举正负增量的数量，计算 $ B $ 是否在可能的范围内，虽然时间复杂度较高，但思路清晰，易于理解。

---
处理用时：51.89秒