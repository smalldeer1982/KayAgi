# 题目信息

# Epic Novel

## 题目描述

Alex has bought a new novel that was published in $ n $ volumes. He has read these volumes one by one, and each volume has taken him several (maybe one) full days to read. So, on the first day, he was reading the first volume, and on each of the following days, he was reading either the same volume he had been reading on the previous day, or the next volume.

Let $ v_i $ be the number of the volume Alex was reading on the $ i $ -th day. Here are some examples:

- one of the possible situations is $ v_1 = 1 $ , $ v_2 = 1 $ , $ v_3 = 2 $ , $ v_4 = 3 $ , $ v_5 = 3 $ — this situation means that Alex has spent two days ( $ 1 $ -st and $ 2 $ -nd) on the first volume, one day ( $ 3 $ -rd) on the second volume, and two days ( $ 4 $ -th and $ 5 $ -th) on the third volume;
- a situation $ v_1 = 2 $ , $ v_2 = 2 $ , $ v_3 = 3 $ is impossible, since Alex started with the first volume (so $ v_1 $ cannot be anything but $ 1 $ );
- a situation $ v_1 = 1 $ , $ v_2 = 2 $ , $ v_3 = 3 $ , $ v_4 = 1 $ is impossible, since Alex won't return to the first volume after reading the third one;
- a situation $ v_1 = 1 $ , $ v_2 = 3 $ is impossible, since Alex doesn't skip volumes.

You know that Alex was reading the volume $ v_a $ on the day $ a $ , and the volume $ v_c $ on the day $ c $ . Now you want to guess which volume was he reading on the day $ b $ , which is between the days $ a $ and $ c $ (so $ a < b < c $ ). There may be some ambiguity, so you want to make any valid guess (i. e. choose some volume number $ v_b $ so it's possible that Alex was reading volume $ v_a $ on day $ a $ , volume $ v_b $ on day $ b $ , and volume $ v_c $ on day $ c $ ).

## 说明/提示

In the first test case, since Alex was reading volume $ 1 $ both at day $ 1 $ and at day $ 100 $ then he was reading volume $ 1 $ at any day between them.

In the second test case, Alex could read any volume from $ 1 $ to $ 4 $ at day $ 16 $ . For example, he could read volume $ 1 $ from day $ 1 $ to day $ 15 $ , volume $ 2 $ at days $ 16 $ and $ 17 $ , volume $ 3 $ at day $ 18 $ and volume $ 4 $ at days $ 19 $ and $ 20 $ .

In the third test case, there is only one possible situation: Alex read one volume per day, so at day $ 42 $ he read volume $ 42 $ .

## 样例 #1

### 输入

```
4
1
1 1
100 1
99
4
10 1
20 4
16
100
1 1
100 100
42
100
1 1
100 2
99```

### 输出

```
1
2
42
1```

# AI分析结果

### 题目内容翻译

Alex 买了一本新小说，这本小说共有 $n$ 卷。他逐卷阅读，每卷可能需要花费几天时间（可能是一天）来读完。因此，在第一天，他阅读了第一卷，接下来的每一天，他要么继续阅读前一天的那卷，要么阅读下一卷。

设 $v_i$ 为 Alex 在第 $i$ 天阅读的卷号。以下是一些例子：

- 一种可能的情况是 $v_1 = 1$，$v_2 = 1$，$v_3 = 2$，$v_4 = 3$，$v_5 = 3$ —— 这种情况意味着 Alex 花费了两天（第 1 天和第 2 天）阅读第一卷，一天（第 3 天）阅读第二卷，两天（第 4 天和第 5 天）阅读第三卷；
- 情况 $v_1 = 2$，$v_2 = 2$，$v_3 = 3$ 是不可能的，因为 Alex 从第一卷开始阅读（因此 $v_1$ 不能是除 $1$ 以外的任何值）；
- 情况 $v_1 = 1$，$v_2 = 2$，$v_3 = 3$，$v_4 = 1$ 是不可能的，因为 Alex 在阅读了第三卷后不会回到第一卷；
- 情况 $v_1 = 1$，$v_2 = 3$ 是不可能的，因为 Alex 不会跳过卷。

已知 Alex 在第 $a$ 天阅读了卷 $v_a$，在第 $c$ 天阅读了卷 $v_c$。现在你想猜测他在第 $b$ 天（$a < b < c$）阅读了哪一卷。由于可能存在多种可能性，你只需要输出任意一个合法的猜测（即选择一个卷号 $v_b$，使得 Alex 在第 $a$ 天阅读卷 $v_a$，在第 $b$ 天阅读卷 $v_b$，在第 $c$ 天阅读卷 $v_c$ 是可能的）。

### 算法分类
模拟

### 题解分析与结论

该题的核心思路是通过分类讨论来确定 Alex 在第 $b$ 天阅读的卷号。大多数题解都采用了类似的思路，即根据 $b - a$ 和 $v_c - v_a$ 的关系来判断 Alex 在第 $b$ 天阅读的卷号。具体来说：

1. 如果 $b - a \ge v_c - v_a$，说明 Alex 在第 $b$ 天及之前已经阅读到了第 $v_c$ 卷，因此输出 $v_c$。
2. 如果 $b - a < v_c - v_a$，说明 Alex 在第 $b$ 天阅读的卷号为 $v_a + (b - a)$。

这种思路简洁且高效，能够快速得出答案。

### 评分较高的题解

#### 题解作者：ikunTLE (赞：6)
**星级：4.5**
**关键亮点：**
- 思路清晰，直接通过分类讨论得出答案。
- 代码简洁，易于理解。

**核心代码：**
```cpp
#include<stdio.h>
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
int main(){
	int t=read();
	while(t--){
		int n=read(),a=read(),va=read(),c=read(),vc=read(),b=read();
		printf("%d\n",(b-a>vc-va)?(va+b-a):vc);
	}
	return 0;
}
```

#### 题解作者：Arefa (赞：3)
**星级：4**
**关键亮点：**
- 通过极端情况的分析，确保方案的合法性。
- 代码简洁，逻辑清晰。

**核心代码：**
```kotlin
import java.util.Scanner
fun main() {
    val read = Scanner(System.`in`)
    var n = read.nextInt()
    while(n>0){
        n--
        var z=read.nextInt()
        var d1=read.nextInt()
        var v1=read.nextInt()
        var d2=read.nextInt()
        var v2=read.nextInt()
        var b=read.nextInt()
        if(b-d1>=v2-v1) println(v2)
        else println(v1+b-d1)
    }
}
```

#### 题解作者：nightwatch.ryan (赞：3)
**星级：4**
**关键亮点：**
- 思路明确，通过简单的条件判断得出答案。
- 代码简洁，易于理解。

**核心代码：**
```cpp
#include<iostream>
int t,n,a,va,c,vc,b,vb;
int main(){
	std::cin>>t;
	for(;t;t--){
		std::cin>>n>>a>>va>>c>>vc>>b;
		if(b-a>=vc-va) std::cout<<vc;
		else std::cout<<va+(b-a); 
		std::cout<<'\n';
	}
}
```

### 最优关键思路或技巧
- **分类讨论**：通过比较 $b - a$ 和 $v_c - v_a$ 的关系，快速确定 Alex 在第 $b$ 天阅读的卷号。
- **极端情况分析**：考虑 Alex 每天只阅读一章的情况，确保方案的合法性。

### 可拓展之处
- 类似的问题可以扩展到其他需要根据时间或步骤推断状态的场景，例如任务调度、资源分配等。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：39.97秒