# [ARC021B] Your Numbers are XORed...

## 题目描述

有两个序列 $a$ 和 $b$。

已知序列 $b$ 的构造方法：
- 对于 $1 \le i < L$ 的情况，$b_i = a_i \operatorname{xor} a_{i + 1}$，其中 $\operatorname{xor}$ 表示异或；
- $b_L = a_L \operatorname{xor} a_1$。

给定序列 $b$ 的长度 $L$ ，以及序列 $b$，求序列 $a$，如果没有一个满足的序列 $a$，请输出`-1`。

如果你不知道什么是异或，请点[这个链接](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677)。

## 说明/提示

对于 $100\%$ 的数据：
- $2 \le L \le 10^5$；
- $0 \le b_i < 2^{31}$。

## 样例 #1

### 输入

```
2
1
1```

### 输出

```
0
1```

## 样例 #2

### 输入

```
3
1
4
1```

### 输出

```
-1```

## 样例 #3

### 输入

```
3
1
2
3```

### 输出

```
0
1
3```

# 题解

## 作者：Struggle_ong (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT871)

### 题目大意：
有 $ a $,$ b $ 两个序列，已知序列 $b$ 的构造方法：
- 对于 $1 \le i < L$ 的情况，$b_i = a_i \operatorname{xor} a_{i + 1}$，其中 $\operatorname{xor}$ 表示异或；
- $b_L = a_L \operatorname{xor} a_1$。

现给定 $ L $ 及序列 $ b $,求序列 $ a $。

### 关键式子：

$a_{ i+1 } = b_i \operatorname{xor} a_i$

### 证明：

因为 $b_i = a_i \operatorname{xor} a_{i + 1}$。

所以 $b_i \operatorname{xor} a_i = a_i \operatorname{xor} a_{i + 1} \operatorname{xor} a_i $（等式的基本性质）。

所以 $ b_i \operatorname{xor} a_i = a_{ i+1 } $（$ n \operatorname{xor} n = 0 $）。

即 $a_{ i+1 } = b_i \operatorname{xor} a_i$。

#### 根据以上证明，可得以下代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010];
int main()
{
	int l;cin>>l;
	for(int i=1;i<=l;i++)cin>>b[i];
	for(int i=1;i<l;i++)a[i+1]=b[i] xor a[i];//xor 异或，由证明可得，a[i+1]=b[i] xor a[i]
	if((a[l] xor a[1])!=b[l])					
	{cout<<-1<<endl;return 0;}//记得换行
	for(int i=1;i<=l;i++)cout<<a[i]<<endl;
	return 0;
}
```





---

## 作者：AirQwQ (赞：0)

## 入手

- 由题易知，构造出数列然后用 $ b_L=a_L \text{ xor } a_1$ 来检查一遍就好。

## 实现

- 因为 $ b_i=a_i \text{ xor } a_{i+1} $ 等价于 $ a_{i+1}=a_i \text{ xor } b_i $（[证明](https://www.luogu.com.cn/paste/sxjyzm2u)）。

- 题目要求字典序最小（該当する元の数列が複数存在する場合は、辞書順最小な数列を出力します。这一句翻译没给出来）所以令 $ a_0 =0 $ 即可。

## AcCode
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],b[100001];
inline int read(){
   register int s=0,w=1;
   register char ch=getchar(); 
   while(ch<'0'||ch>'9'){
        if(ch=='-'){
            w=-1;
            ch=getchar();
        }
   }
   while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
   }
   return s*w;
}
int main(){
    int l=read();
    for(int i=1;i<=l;i++) 
        b[i]=read();
    for(int i=2;i<=l;i++)
        a[i]=b[i-1]^a[i-1];//代码中异或是^
    if((a[l]^a[1])!=b[l])//记的加括号
        cout<<-1<<endl;
    else 
        for(int i=1;i<=l;i++) 
            cout<<a[i]<<'\n';
    return 0;
}
```

---

## 作者：Defoliation (赞：0)



## 思路
题目所给的构造方法：


- 对于 $1$ $\leq$ $i$ $<$ $L$ 的情况，$b_i$ $=$ $a_i$ $xor$ $a_{i+1}$。

- $b_L$ $=$ $a_L$ $xor$ $a_1$。

不难想到应根据第一个条件进行构造，根据第二个条件判断构造序列是否合法后输出。






## Solution


观察构造方式一，发现同时存在 $a_i$ 和 $a_{i+1}$，则考虑通过递归的方式进行构造。

将 $b_i$ $=$ $a_i$ $xor$ $a_{i+1}$ 化为 $a_{i+1}$ $=$ $b_i$ $xor$ $a_i$。

#### 证明

 $a$ $xor$ $b$ $xor$ $b$ $=$ $a$。
 
 
原式 


$\Rightarrow$ $b_i$ $=$ $a_i$ $xor$ $a_{i+1}$ 

$\Rightarrow$ $b_i$ $xor$ $a_i$ $=$ $a_{i+1}$ $xor$ $a_i$ $xor$ $a_i$ 


$\Rightarrow$ $b_i$ $xor$ $a_i$ $=$ $a_{i+1}$ 

$QED.$

## 一些小细节

- 如果构造的序列不合法返回 $-1$ 时也要换行。

	~~机房大佬说站外题输出要换行是常识欸(~~
    
- 题意翻译的输出格式部分描述是有误的，输出的 $a$ 序列不仅应该符合要求，而且要保证字典序最小（在原文中有说明），因此 $a_1$ 的值只能赋成 $0$ 。

## $Code:$ 

```cpp

#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int l,a[100001],b[100001];
int main(){
    cin>>l;
    for(int i=1;i<=l;++i) 
        cin>>b[i];
    a[1]=0;
    for(int i=2;i<=l;++i) //构造序列
        a[i]=(b[i-1]^a[i-1]);
    if((a[l]^a[1])!=b[l]){ //判断合法
        cout<<-1<<endl;
        return 0;
    }
    for(int i=1;i<=l;++i) 
        cout<<a[i]<<endl;
}
```









	


---

## 作者：Nygglatho (赞：0)

由于 $b_i = a_i \operatorname{xor} a_{i + 1}$，那么 $b_{i - 1} = a_{i - 1} \operatorname{xor} a_i$。

那么可以得出这样一个结论：$a_i = b_{i - 1} \operatorname{xor} a_{i - 1}$。

原因也是很简单的。

$$
\begin{aligned}
b_{i - 1} &= a_i \operatorname{xor} a_{i - 1} \\
b_{i - 1} \operatorname{xor} a_{i - 1} &= a_i \operatorname{xor} a_{i - 1} \operatorname{xor} a_{i - 1}
\end{aligned}
$$

通过归零律（$a \operatorname{xor} a = 0$）得出：

$$
\begin{aligned}
b_{i - 1} \operatorname{xor} a_{i - 1} &= a_i \operatorname{xor} 0
\end{aligned}
$$

通过恒等律（$a \operatorname{xor} 0 = a$）得出：
$$
\begin{aligned}
b_{i - 1} \operatorname{xor} a_{i - 1} &= a_i \\
a_i &= b_{i - 1} \operatorname{xor} a_{i - 1}
\end{aligned}
$$

所以结论正确，而 $a_1$ 为 $0$ 即可，最后再判断一下，是否是无解，无解输出`-1`。

Code：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int a[100001], b[100001];
int main() {
    int l;
    cin >> l;
    for (int i = 1; i <= l; ++i) cin >> b[i];
    a[1] = 0;
    for (int i = 2; i <= l; ++i) a[i] = (b[i - 1] ^ a[i - 1]);
    for (int i = 1; i < l; ++i)
        if ((a[i] ^ a[i + 1]) != b[i])
            return puts("-1"), 0;
    if ((a[l] ^ a[1]) != b[l]) return puts("-1"), 0;
    for (int i = 1; i <= l; ++i) cout << a[i] << endl;
}
```

---

