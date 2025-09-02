# [CCC 2023 J1] Deliv-e-droid

## 题目描述

在游戏 Deliv-e-droid 中，一个机器人需要在避开障碍物的同时递送包裹。

在游戏结束时，最终得分根据以下积分系统计算：
- 每递送一个包裹获得 50 分。
- 每次与障碍物碰撞扣除 10 分。
- 如果递送的包裹数量大于与障碍物碰撞的次数，则获得额外的 500 分奖励。

你的任务是确定游戏结束时的最终得分。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
2```

### 输出

```
730```

## 样例 #2

### 输入

```
0
10```

### 输出

```
-100```

# 题解

## 作者：maomao233 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9299)

### 分析

计算 Deliv-e-droid 获得的钱，总共分两步：

1. 送达的**奖励的钱**和未送达的**扣除的钱**；
2. 判断是否有 $500$ 元奖励。

先计算第一步，按照小学乘法计算公式：

份数（送达的快递的数量）$\times$ 一份量（奖励的 $50$ 元钱）$=$ 奖励的钱。

份数（未送达的快递的数量）$\times$ 一份量（扣除的 $10$ 元钱）$=$ 扣除的钱。

那么获得的钱就是**奖励的钱**与**扣除的钱之差**，即 $50p-10c$。

第二步，直接用分支语句判断：

```cpp
if(p>c)
{
	获得的钱 +500。
}
```

加上第一步，再用[三目运算符](https://baike.baidu.com/item/%E6%9D%A1%E4%BB%B6%E8%BF%90%E7%AE%97%E7%AC%A6/6180633)优化一下，公式为：

```cpp
(50*p-10*c)+((p>c)?500:0)
```

代码就出来了。

---

## 作者：Jasoncwx (赞：2)

## 题目思路
按照题意模拟，定义变量 $ans$ 表示答案。$ans$ 则为送达的快递总数 $\times50-$ 未送达的快递总数 $\times10$。


如果 $P>C$，$ans+500$。

最后输出 $ans$ 即可。

## 代码
```cpp
//By Jasoncwx
#include<bits/stdc++.h>
using namespace std;

int main(){
	int p,c;
	cin>>p>>c;
	int ans=p*50-c*10;
	if(p>c)ans+=500;
	cout<<ans;
    return 0;
}
```

---

## 作者：Sun_Email (赞：1)

这题题意说的非常明确，计算钱的公式也非常简单。不过要注意的是：如果 $p>c$，钱数要 $+500$。（不要漏掉！）

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int p,c,ans=0;
int main(){
	scanf("%d%d",&p,&c);
	ans=p*50-c*10;
	if(p>c){
		ans+=500;
	}
	printf("%d",ans);
	return 0;
}
```
完结撒花

---

## 作者：Leaves_xw (赞：1)

**思路：**

首先一个判断，若 $P > C$，则 $ans$ 累加 $500$，随后再输出 $ans + 50 \times P-10 \times C$ 就行了。

**代码：**

```
#include<bits/stdc++.h>
using namespace std;
int ans=0;
int main()
{
    int p,c;
    cin>>p>>c;
    if(p>c)ans+=500;
    ans=p*50-c*10;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：ruruo (赞：0)

# 分析

- 分支结构练习题，我们利用问号表达式一行即可搞定。

# 代码

```cpp
#include<iostream>
using namespace std;

long long a, b;

int main() {
    cin >> a >> b;
    cout << (a > b ? 50 * a - 10 * b + 500 : 50 * a - 10 * b);
    return 0;
}
```


---

