# 题目信息

# Game 23

## 题目描述

Polycarp plays "Game 23". Initially he has a number $ n $ and his goal is to transform it to $ m $ . In one move, he can multiply $ n $ by $ 2 $ or multiply $ n $ by $ 3 $ . He can perform any number of moves.

Print the number of moves needed to transform $ n $ to $ m $ . Print -1 if it is impossible to do so.

It is easy to prove that any way to transform $ n $ to $ m $ contains the same number of moves (i.e. number of moves doesn't depend on the way of transformation).

## 说明/提示

In the first example, the possible sequence of moves is: $ 120 \rightarrow 240 \rightarrow 720 \rightarrow 1440 \rightarrow 4320 \rightarrow 12960 \rightarrow 25920 \rightarrow 51840. $ The are $ 7 $ steps in total.

In the second example, no moves are needed. Thus, the answer is $ 0 $ .

In the third example, it is impossible to transform $ 48 $ to $ 72 $ .

## 样例 #1

### 输入

```
120 51840
```

### 输出

```
7
```

## 样例 #2

### 输入

```
42 42
```

### 输出

```
0
```

## 样例 #3

### 输入

```
48 72
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写
# Game 23

## 题目描述

Polycarp 玩“Game 23”。初始时他有一个数字 $n$，目标是通过若干次操作将其转换为 $m$。每次操作，他可以将 $n$ 乘以 $2$ 或乘以 $3$。他可以执行任意次数的操作。

输出将 $n$ 转换为 $m$ 所需的操作次数。如果无法完成，则输出 -1。

可以证明，任何将 $n$ 转换为 $m$ 的方式都包含相同次数的操作（即操作次数不依赖于转换方式）。

## 说明/提示

在第一个例子中，可能的操作序列是：$120 \rightarrow 240 \rightarrow 720 \rightarrow 1440 \rightarrow 4320 \rightarrow 12960 \rightarrow 25920 \rightarrow 51840$。总共有 $7$ 步。

在第二个例子中，不需要任何操作。因此，答案是 $0$。

在第三个例子中，无法将 $48$ 转换为 $72$。

## 样例 #1

### 输入

```
120 51840
```

### 输出

```
7
```

## 样例 #2

### 输入

```
42 42
```

### 输出

```
0
```

## 样例 #3

### 输入

```
48 72
```

### 输出

```
-1
```

### 算法分类
数学

### 题解分析与结论
本题的核心逻辑是通过数学方法判断 $m$ 是否能通过 $n$ 乘以若干次 $2$ 或 $3$ 得到，并计算所需的操作次数。大多数题解都采用了类似的方法：首先判断 $m$ 是否能被 $n$ 整除，然后通过不断除以 $2$ 和 $3$ 来统计操作次数，最后检查剩余的数是否为 $1$。

### 所选高星题解
#### 题解1：yuzhechuan (4星)
**关键亮点**：代码简洁，逻辑清晰，直接通过数学方法解决问题，避免了复杂的递归或搜索。
**核心代码**：
```cpp
int a,b;
int main(){
	scanf("%d%d",&a,&b);
	if(b%a!=0){
		printf("-1");
		return 0;
	}
	b/=a;
	a=0;
	while(b%2==0) b/=2,a++;
	while(b%3==0) b/=3,a++;
	if(b!=1) a=-1;
	printf("%d",a);
}
```

#### 题解2：zhy12138 (4星)
**关键亮点**：代码结构清晰，使用了快速读取函数，适合处理较大数据。
**核心代码**：
```cpp
int n,m;
int main()
{
    n=read(),m=read();
    if(m%n!=0)
    {
        puts("-1");
        return 0;
    }
    int t=m/n,ans=0;
    while(t%2==0)
        t/=2,++ans;
    while(t%3==0)
        t/=3,++ans;
    if(t==1)
        printf("%d\n",ans);
    else
        puts("-1");
    return 0;
}
```

#### 题解3：FP·荷兰猪 (4星)
**关键亮点**：使用了浮点数判断是否能整除，代码逻辑清晰，适合初学者理解。
**核心代码**：
```cpp
ll n,m;
cin>>n>>m;
double shang;
shang=m*1.0/n;
if (shang!=int(shang))
{
    cout<<"-1"<<endl;
    return 0;
}
else
{
    ll t;
    t=m/n;
    ll ans;
    ans=0;
    while (t%3==0)
    {
        t/=3;
        ans++; 
    }
    while (t%2==0)
    {
        t/=2;
        ans++;
    }
    if (t!=1)
    {
        cout<<"-1"<<endl;
        return 0;
    }
    else
    {
        cout<<ans<<endl;
        return 0;
    }
}
```

### 最优关键思路
通过数学方法，首先判断 $m$ 是否能被 $n$ 整除，然后通过不断除以 $2$ 和 $3$ 来统计操作次数，最后检查剩余的数是否为 $1$。这种方法避免了复杂的递归或搜索，效率高且易于理解。

### 可拓展之处
类似的问题可以通过分解质因数的方法来解决，例如判断一个数是否能通过乘以某些特定的数得到另一个数。这类问题通常可以通过数学方法高效解决。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1069 分解质因数](https://www.luogu.com.cn/problem/P1069)

### 个人心得总结
在解决这类问题时，数学方法往往比递归或搜索更高效。通过分解质因数，可以快速判断是否能够通过特定的操作得到目标数，并且可以统计所需的操作次数。这种方法不仅代码简洁，而且易于理解和实现。

---
处理用时：31.66秒