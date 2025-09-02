# 题目信息

# Timofey and cubes

## 题目描述

Young Timofey has a birthday today! He got kit of $ n $ cubes as a birthday present from his parents. Every cube has a number $ a_{i} $ , which is written on it. Timofey put all the cubes in a row and went to unpack other presents.

In this time, Timofey's elder brother, Dima reordered the cubes using the following rule. Suppose the cubes are numbered from $ 1 $ to $ n $ in their order. Dima performs several steps, on step $ i $ he reverses the segment of cubes from $ i $ -th to $ (n-i+1) $ -th. He does this while $ i<=n-i+1 $ .

After performing the operations Dima went away, being very proud of himself. When Timofey returned to his cubes, he understood that their order was changed. Help Timofey as fast as you can and save the holiday — restore the initial order of the cubes using information of their current location.

## 说明/提示

Consider the first sample.

1. At the begining row was \[ $ 2 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 4 $ \].
2. After first operation row was \[ $ 4 $ , $ 1 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 3 $ , $ 2 $ \].
3. After second operation row was \[ $ 4 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 2 $ \].
4. After third operation row was \[ $ 4 $ , $ 3 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 1 $ , $ 2 $ \].
5. At fourth operation we reverse just middle element, so nothing has changed. The final row is \[ $ 4 $ , $ 3 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 1 $ , $ 2 $ \]. So the answer for this case is row \[ $ 2 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 4 $ \].

## 样例 #1

### 输入

```
7
4 3 7 6 9 1 2
```

### 输出

```
2 3 9 6 7 1 4```

## 样例 #2

### 输入

```
8
6 1 4 2 5 6 9 2
```

### 输出

```
2 1 6 2 5 4 9 6```

# AI分析结果

### 题目翻译
# 季莫费和立方体

## 题目描述
小季莫费今天过生日！他从父母那里收到了一套由 $n$ 个立方体组成的礼物。每个立方体上都写有一个数字 $a_{i}$。季莫费把所有的立方体排成一排，然后去拆其他礼物了。

在这段时间里，季莫费的哥哥迪玛按照以下规则重新排列了这些立方体。假设这些立方体按顺序从 $1$ 到 $n$ 编号。迪玛进行了几个步骤，在第 $i$ 步，他将从第 $i$ 个到第 $(n - i + 1)$ 个的立方体段进行反转。只要 $i <= n - i + 1$，他就会一直这样做。

完成这些操作后，迪玛得意地离开了。当季莫费回到他的立方体旁时，他发现立方体的顺序变了。请尽快帮助季莫费，挽救这个节日——根据立方体当前的位置信息恢复它们原来的顺序。

## 说明/提示
考虑第一个样例。
1. 开始时序列是 \[ $2$ , $3$ , $9$ , $6$ , $7$ , $1$ , $4$ \]。
2. 第一次操作后序列是 \[ $4$ , $1$ , $7$ , $6$ , $9$ , $3$ , $2$ \]。
3. 第二次操作后序列是 \[ $4$ , $3$ , $9$ , $6$ , $7$ , $1$ , $2$ \]。
4. 第三次操作后序列是 \[ $4$ , $3$ , $7$ , $6$ , $9$ , $1$ , $2$ \]。
5. 在第四次操作中，我们只反转中间的元素，所以没有任何变化。最终的序列是 \[ $4$ , $3$ , $7$ , $6$ , $9$ , $1$ , $2$ \]。所以这个样例的答案是序列 \[ $2$ , $3$ , $9$ , $6$ , $7$ , $1$ , $4$ \]。

## 样例 #1
### 输入
```
7
4 3 7 6 9 1 2
```
### 输出
```
2 3 9 6 7 1 4
```

## 样例 #2
### 输入
```
8
6 1 4 2 5 6 9 2
```
### 输出
```
2 1 6 2 5 4 9 6
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过寻找数字交换的规律来恢复原序列。通过对样例的观察和分析，发现当 $i$ 为奇数时，$a_i$ 与 $a_{n - i + 1}$ 交换位置，而 $i$ 为偶数时，数字位置不变。各题解的区别主要在于实现细节和代码风格。

### 题解评分与选择
- **老彩笔**：4星。思路清晰，详细解释了规律的发现过程，代码中使用了快读优化输入，同时对 $n$ 为奇数的情况进行了特判，代码可读性较高。
- **Noby_Glds**：4星。思路巧妙，在输入时就生成答案数列，减少了额外的数组使用，代码简洁。
- **joy2010WonderMaker**：4星。思路简洁明了，直接根据规律进行交换操作，代码简洁易懂。

### 重点代码
#### 老彩笔
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//快读 
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10-48+ch;ch=getchar();}
	return x*f;
}
int n;
int a[200005];
int ans[200005],cnt;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n/2;i++)
	{
		if(i%2==1)
		{
			ans[i]=a[n-i+1];
			ans[n-i+1]=a[i];
		}
		else
		{
			ans[i]=a[i];
			ans[n-i+1]=a[n-i+1];
		}
	}
	if(n%2==1)
		ans[n/2+1]=a[n/2+1];
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<' ';
	return 0;
}
```
**核心思想**：先读取输入，然后根据 $i$ 的奇偶性交换或保持元素位置，最后处理 $n$ 为奇数的情况并输出结果。

#### Noby_Glds
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		if(min(i,n-i+1)%2==1) cin>>a[n-i+1];
		else cin>>a[i];
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
    return 0;
}
```
**核心思想**：在输入时，根据 $i$ 和 $n - i + 1$ 中较小值的奇偶性，将输入直接放到对应的位置上。

#### joy2010WonderMaker
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[200005];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n/2;i=i+2)swap(a[i],a[n-i+1]);
    for(int i=1;i<=n;i++)printf("%d ",a[i]);
    return 0;
}
```
**核心思想**：读取输入后，只枚举奇数位置的 $i$，交换 $a[i]$ 和 $a[n - i + 1]$，最后输出结果。

### 最优关键思路或技巧
- 通过观察样例，找出数字交换的规律，即奇数位置的数字会交换，偶数位置的数字不变。
- 利用 $i$ 和 $n - i + 1$ 的关系，减少不必要的枚举，将时间复杂度优化到 $O(n)$。

### 拓展思路
同类型题可能会有不同的序列变换规则，解题关键依然是找出变换规律。类似的算法套路包括通过对样例的分析和模拟，找出元素之间的位置关系变化规律，然后根据规律进行相应的操作。

### 推荐洛谷题目
- P1047 [NOIP2005 普及组] 校门外的树
- P1097 [NOIP2007 提高组] 统计数字
- P1161 开灯

### 个人心得摘录与总结
- **oneman233**：提到每个数字的交换次数是确定的，且“交换”是可逆的，即交换（原序列）=现序列，那么交换（现序列）=原序列。这提示我们在处理这类可逆变换问题时，可以利用可逆性来简化问题。 

---
处理用时：44.08秒