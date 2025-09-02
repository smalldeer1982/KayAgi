# [NWRRC 2022] Absolutely Flat

## 题目描述

Alice 是一位拥有一张四条腿桌子的自豪主人，她希望她的桌子保持平稳。Alice 认为桌子平稳的条件是四条腿的长度都相等。

Alice 测量了桌子当前四条腿的长度，分别为 $a_1, a_2, a_3, a_4$。她还有一个长度为 $b$ 的垫片。Alice 可以将这个垫片加在任意一条腿上，这样该腿的长度会增加 $b$。她也可以选择不使用垫片，这样四条腿的长度保持不变。注意，Alice 只有一个垫片，不能对同一条腿使用两次，也不能同时用在两条腿上。

请你判断 Alice 是否能够让她的桌子变得平稳。

## 说明/提示

在第一个样例测试中，桌子已经平稳，无需使用垫片。

在第二个样例测试中，Alice 可以将垫片加在第三条腿上，使桌子平稳。

在第三和第四个样例测试中，Alice 无法让桌子平稳。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10
10
10
10
5```

### 输出

```
1```

## 样例 #2

### 输入

```
13
13
5
13
8```

### 输出

```
1```

## 样例 #3

### 输入

```
50
42
42
50
8```

### 输出

```
0```

## 样例 #4

### 输入

```
20
40
10
30
2```

### 输出

```
0```

# 题解

## 作者：___AaAa_bBcCd___ (赞：3)

题目传送门：[P13598 [NWRRC 2022] Absolutely Flat](https://www.luogu.com.cn/problem/P13598)

发现能做到平稳首先得至少有三条腿相等，然后剩下那条要么是也相等要么是正好短 $b$。

所以假设四条腿已经升序排序，判断：

1. 第 $2$ 条腿的长度等于第 $4$ 条腿。

2. 第 $1$ 条腿的长度等于第 $2$ 条腿（不放垫片）。

3. 第 $1$ 条腿的长度等于第 $2$ 条腿的长度减 $b$（放垫片）。

其中第一条必须满足，后两条要满足一个。

于是就解决了。先排序，然后判断输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],b;
int main(){
    cin>>a[0]>>a[1]>>a[2]>>a[3]>>b;
    sort(a,a+4);
    cout<<(a[1]==a[3]&&(a[0]==a[1]||a[0]+b==a[1]));
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/229472085)。

---

## 作者：b_donk (赞：2)

### 题目大意
判断是否可以通过在最多一条桌腿上添加长度为 $b$ 的垫片，使得四条桌腿的长度相等。

### 题目思路

遍历每条腿，尝试给每一条腿加上 $b$，然后检查是否四条腿可以相等（如果已经相等，就不用再添加）。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
main() {
	int a1, a2, a3, a4, b;
	cin >> a1 >> a2 >> a3 >> a4 >> b;
	if (a1 == a2 && a2 == a3 && a3 == a4) {// 如果本来就是平坦的话就直接输出1
		cout << 1;
		return 0;
	} 
	
	// 检查是否能让四条腿相等
	if (a2 == a3 && a3 == a4 && a1 + b == a2) {
		cout << 1;
		return 0;
	}
	if (a1 == a3 && a3 == a4 && a2 + b == a1) {
		cout << 1;
		return 0;
	}
	if (a1 == a2 && a2 == a4 && a3 + b == a1) {
		cout << 1;
		return 0;
	}
	if (a1 == a2 && a2 == a3 && a4 + b == a1) {
		cout << 1;
		return 0;
	}
	cout << 0; // 如果怎么都平坦不了的话就直接输出0
	return 0;
}
```
希望这篇题解能够帮到你。

---

## 作者：ryf2011 (赞：2)

# 1.题目思路
本题**前置知识**：分支结构、数组。

我们来分析一下可行和不可行的情况。

先来看可行的情况：

1. 数列 $a$ 最小值与最大值相等（即数列 $a$ 的值都相等），可行；
2. 数列 $a$ 是最小值的只有一个数，且这个数与 $b$ 相加等于数列最大值，可行。

再来看不可行的情况：

1. 如果数列 $a$ 中不同的数的个数大于 $2$，那么无论如何也不能使所有数都相等，不可行。
2. 除上述可行与不可行情况的其他情况都不可行。

分析完成。我们用一个计数数组记录每个数出现的次数，再用一个计数变量记录不同数的个数，以及数列最大值、最小值变量便可以完成上述判断。

# 2.代码
注：本代码仅供参考。

:::info[代码]{open}
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int max_v=105; //a[i] 的最大值
int a[5],b,cnt,mina=2147483647,maxa;
int times[max_v]; //记录每个数出现的次数
int main(){
    for(int i=1;i<=4;i++){
        scanf("%d",&a[i]);
        if(!times[a[i]]){ //如果之前都没出现过，那么这是第一次出现，不同数的个数 +1
            cnt++;
        }
        times[a[i]]++;
        if(cnt>2){ //不同数个数多于 2，那么一定不可行
            puts("0");
            return 0;
        }
        mina=min(mina,a[i]); //最小值
        maxa=max(maxa,a[i]); //最大值
    }
    scanf("%d",&b);
    if(mina==maxa){ //数列所有数都相等
        puts("1");
    }
    else if(mina+b==maxa&&times[mina]==1){ //只有一个数与其他数不同，且满足条件
        puts("1");
    }
    else{ //其他情况都不可行
        puts("0");
    }
    return 0;
}
```
:::

# 3.后记
更多内容，请移步至：

1. [$\color{red}\texttt{Luogu ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")；
2. [$\color{orange}\texttt{cnblogs（博客园） cnblogs2011ryf}$](https://www.cnblogs.com/cnblogs2011ryf)。

---

## 作者：Doraeman (赞：2)

~~我看到另外两位大佬的代码好长长长长啊。~~
## 思路
不妨设 $a_1\le a_2\le a_3\le a_4$（对 $a$ 数组排序实现）。

此时，分情况讨论。

- 如果 $a_1=a_4$，根据不等式，说明 $a_1=a_2=a_3=a_4$。  
  不需要使用垫子，直接输出 ```1```，结束。
- 反之，$a_1\not=a_4$，根据不等式说明 $a_1<a_4$。  
  这时为了使四条桌子腿齐平，必须要给 $a_1$ 使用垫子，$a_1$ 的长度变成 $a_1+b$。  
- 若 $a_1+b=a_2=a_4$，根据不等式可以推出 $a_2=a_3=a_4$，所以得到此时 $4$ 条腿长度相等，可以把桌面弄平。输出 ```1```，结束。
- 反之，$a_1+b\not=a_2$ 或 $a_2\not=a_4$，那么即使给 $a_1$ 使用垫子也没有用。输出 ```0```，结束。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a[5], b;
    for(int i=1; i<=4; i++)
        cin >> a[i];
    cin >> b;
    // 排序 
    sort(a + 1, a + 5);

    // 不用垫子 
    if(a[1] == a[4]) cout << 1;
    // 用垫子, 效果很好 
    else if(a[1] + b == a[2] && a[2] == a[4]) cout << 1;
    // 用垫子, 效果不好 
    else cout << 0;
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 P13598 [NWRRC 2022] Absolutely Flat](https://www.luogu.com.cn/problem/P13598)

## 题意简述

给定四条桌腿长度和一个垫片，判断是否能通过贴在一条腿上（或不贴）使四条腿长度相等。

## 解题思路

只有一个垫片，肯定只能贴在最短的腿上；只要另外三条腿长度相等，再判断最短的是否贴垫片后也能相等即可。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int a[4],b;
	cin>>a[0]>>a[1]>>a[2]>>a[3]>>b;
	sort(a,a+4);
	cout<<((a[0]==a[1]||a[0]+b==a[1])&&a[1]==a[3])<<'\n';
	return 0;
}
```

---

