# 题目信息

# Increase and Copy

## 题目描述

Initially, you have the array $ a $ consisting of one element $ 1 $ ( $ a = [1] $ ).

In one move, you can do one of the following things:

- Increase some (single) element of $ a $ by $ 1 $ (choose some $ i $ from $ 1 $ to the current length of $ a $ and increase $ a_i $ by one);
- Append the copy of some (single) element of $ a $ to the end of the array (choose some $ i $ from $ 1 $ to the current length of $ a $ and append $ a_i $ to the end of the array).

For example, consider the sequence of five moves:

1. You take the first element $ a_1 $ , append its copy to the end of the array and get $ a = [1, 1] $ .
2. You take the first element $ a_1 $ , increase it by $ 1 $ and get $ a = [2, 1] $ .
3. You take the second element $ a_2 $ , append its copy to the end of the array and get $ a = [2, 1, 1] $ .
4. You take the first element $ a_1 $ , append its copy to the end of the array and get $ a = [2, 1, 1, 2] $ .
5. You take the fourth element $ a_4 $ , increase it by $ 1 $ and get $ a = [2, 1, 1, 3] $ .

Your task is to find the minimum number of moves required to obtain the array with the sum at least $ n $ .

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
1
5
42
1337
1000000000```

### 输出

```
0
3
11
72
63244```

# AI分析结果

### 题目内容
# 增加与复制

## 题目描述
最初，你有一个数组 $a$，它仅包含一个元素 $1$（即 $a = [1]$）。

在一次移动中，你可以执行以下操作之一：
- 增加数组 $a$ 中某个（单个）元素的值 $1$（从 $1$ 到数组当前长度中选择某个 $i$，并将 $a_i$ 增加 $1$）；
- 将数组 $a$ 中某个（单个）元素的副本追加到数组末尾（从 $1$ 到数组当前长度中选择某个 $i$，并将 $a_i$ 追加到数组末尾）。

例如，考虑一个包含五步的操作序列：
1. 取第一个元素 $a_1$，将其副本追加到数组末尾，得到 $a = [1, 1]$。
2. 取第一个元素 $a_1$，将其增加 $1$，得到 $a = [2, 1]$。
3. 取第二个元素 $a_2$，将其副本追加到数组末尾，得到 $a = [2, 1, 1]$。
4. 取第一个元素 $a_1$，将其副本追加到数组末尾，得到 $a = [2, 1, 1, 2]$。
5. 取第四个元素 $a_4$，将其增加 $1$，得到 $a = [2, 1, 1, 3]$。

你的任务是找出获得总和至少为 $n$ 的数组所需的最少移动次数。

你需要回答 $t$ 个独立的测试用例。

## 样例 #1
### 输入
```
5
1
5
42
1337
1000000000
```
### 输出
```
0
3
11
72
63244
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是基于数学分析，尝试找到一种最优的操作方式来达到数组和至少为 $n$ 的目标。
- **思路方面**：多数题解都意识到先将初始元素增加到某个值 $x$，再通过复制操作来达到目标和是较优的方式。并且都发现 $x$ 取接近 $\sqrt{n}$ 时能使操作次数最少。
- **算法要点**：关键在于如何根据 $n$ 确定具体的操作次数。有的通过枚举接近 $\sqrt{n}$ 的值来精确计算，有的通过对 $\sqrt{n}$ 取整后进行简单特判来计算。
- **解决难点**：难点在于证明为何先增加到接近 $\sqrt{n}$ 再复制是最优策略，部分题解通过基本不等式或对勾函数性质进行了解释。

### 所选的题解
- **作者：tommymio (5星)**
  - **关键亮点**：思路清晰，通过将 $n$ 分解为 $xy + b(0\leq b<x\leq y)$ 的形式，详细分析每种分解下的操作次数，并且指出 $x,y$ 尽可能接近时答案最优，采用 $O(\sqrt n)$ 的枚举保证了正确性，代码实现简洁明了。
  - **重点代码**：
```cpp
#include<cstdio>
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;} 
int main() {
	int T=read();
	while(T--) {
		int n=read(),ans=n+10;
		for(register int i=1;1ll*i*i<=n;++i) {
			ans=min(ans,n/i+i-2+(n%i>0));
		}
		printf("%d\n",ans);
	}
	return 0; 
}
```
  - **核心实现思想**：通过循环枚举 $i$（$1\leq i\leq\sqrt{n}$），计算 $n/i + i - 2 + (n\%i>0)$ 的值并取最小值，其中 $n/i + i - 2$ 是 $n$ 能被 $i$ 整除时的操作次数，$n\%i>0$ 时再加 $1$ 是处理余数的情况。
- **作者：shzaiz (4星)**
  - **关键亮点**：先阐述了两条重要性质，即应复制大于1的元素以及先增加到 $\sqrt{n}$ 再复制是最优的，通过基本不等式证明了 $x+\lceil\frac{n}{x}\rceil - 2$ 在 $\sqrt{n}$ 处取极小值，思路具有逻辑性，代码简洁。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int n;cin>>n;
	int s = sqrt(n);
	int ans = (s+(n/s)-2);
	if(n%s!=0) ans++;
	cout<<ans<<"\n";
}
int main(){
	int T;cin>>T;while(T--)solve();return 0;
}
```
  - **核心实现思想**：先对 $n$ 取平方根得到 $s$，计算 $s + (n/s) - 2$ 作为初始操作次数，若 $n$ 除以 $s$ 有余数，则操作次数加 $1$。
- **作者：dead_X (4星)**
  - **关键亮点**：将问题转化为求 $x\times y\geq n,x\in Z^+,y\in Z^+$ 中 $x + y - 1$ 的最小值，明确指出 $y=\lceil\frac{n}{x}\rceil$ ，进而得到 $Ans=x+\lceil\frac{n}{x}\rceil - 1$ ，虽然代码简单，但思路清晰，数学转化能力强。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
    int num=0;
    char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num*=10,num+=ch-48,ch=getchar();
    return num;
}
int n;
void Main(){
	scanf("%lld",&n);
	int t=sqrt(n-1);++t;
	printf("%lld\n",t+(n-1)/t-1);
}
signed main(){
	for(int T=read();T;--T)Main();
}
```
  - **核心实现思想**：先对 $n - 1$ 取平方根并加 $1$ 得到 $t$，然后计算 $t + (n - 1)/t - 1$ 作为操作次数。

### 最优关键思路或技巧
通过数学分析，将问题转化为寻找合适的 $x$ 和 $y$ 使得操作次数最少，利用基本不等式或对勾函数性质确定 $x$ 接近 $\sqrt{n}$ 时最优，并且通过不同方式精确计算操作次数，如枚举、简单特判等。

### 可拓展之处
同类型题可涉及更多对操作规则和目标的变化，类似算法套路是对操作结果进行数学建模，分析最优情况，利用数学性质来简化计算。

### 洛谷相似题目
- P1028 [NOIP2001 普及组] 数的计算：通过给定的规则对数字进行操作并统计方案数，涉及对操作规则的数学分析。
- P1147 连续自然数和：给定一个数，求其能表示为哪些连续自然数之和，需要通过数学推导找到满足条件的解。
- P2669 金币：按照一定规律获取金币，计算给定天数内获得的金币总数，需要分析规律并通过数学方法计算。 

---
处理用时：57.00秒