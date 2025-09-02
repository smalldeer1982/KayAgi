# [NERC 2021] Interactive Treasure Hunt

## 题目描述

**这是一道交互题。**

有一个 $n \times m$ 的网格。两个宝箱被埋藏在网格的两个不同单元格中。你的任务是找到这两个宝箱。你可以进行两种操作：

1. **DIG** $r$ $c$：尝试在单元格 $(r, c)$ 挖掘宝藏。交互器会告诉你是否找到了宝藏。
2. **SCAN** $r$ $c$：从单元格 $(r, c)$ 进行扫描。该操作的结果是从 $(r, c)$ 到两个宝藏所在单元格的曼哈顿距离之和。曼哈顿距离的计算公式为 $|r_1 - r_2| + |c_1 - c_2|$。

你需要在最多 7 次操作内找到两个宝藏（包括 **DIG** 和 **SCAN** 操作）。为了通过测试，你必须在两个藏有宝藏的单元格中各调用至少一次 **DIG** 操作。

### 交互协议

你的程序需要在一轮运行中处理多个测试用例。首先，测试系统会给出 $t$ —— 测试用例的数量（$1 \le t \le 100$）。然后，依次处理 $t$ 个测试用例。

在每个测试用例中，你的程序首先需要读取两个整数 $n$ 和 $m$（$2 \le n, m \le 16$）。

然后，你的程序可以发起以下两种查询：

1. **DIG** $r$ $c$（$1 \le r \le n$；$1 \le c \le m$）。交互器会返回整数 $1$（如果找到了宝藏）或 $0$（如果未找到）。如果你多次在同一个单元格挖掘，由于宝藏已被取走，结果将始终为 $0$。
2. **SCAN** $r$ $c$（$1 \le r \le n$；$1 \le c \le m$）。交互器会返回一个整数，表示从 $(r, c)$ 到两个宝藏所在单元格的曼哈顿距离之和。即使你已经找到一个宝藏，该操作仍然会计算两个宝藏的距离之和。

当你找到两个宝藏（即通过 **DIG** 操作两次获得 $1$ 的响应）后，你的程序应继续处理下一个测试用例，或者如果是最后一个测试用例则退出。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1
2 3

1

1

3

0

1```

### 输出

```


SCAN 1 2

DIG 1 2

SCAN 2 2

DIG 1 1

DIG 1 3```

# 题解

## 作者：_O_v_O_ (赞：1)

[双倍经验](/problem/CF1666I)。

不懂 $n,m$ 为啥才 $16$。似乎是拿来诈骗 $2^4=16$ 从而想到二分的人。

注意到要挖两次答案，而两个点是轮换对称的，所以还要挖一次，那么只剩 $4$ 次。

我们不妨令 $x_1\le x_2,y_1\le y_2$

为了消除掉绝对值的影响，先用 SCAN 询问 $(1,1),(1,m)$，设答案为 $a,b$。

那么就能得出一组方程：

$$\begin{cases}x_1-1+y_1-1+x_2-1+y_2-1=a \\ x_1-1+m-y_1+x_2-1+m-y_2=b\end{cases}$$

化简可得：

$$\begin{cases}x_1+y_1+x_2+y_2=a+4 \\ x_1-y_1+x_2-y_2=b+2-2\times m\end{cases}$$

那么能算出 $x_1+x_2=\frac{a+b+6-2\times m}2=\frac{a+b}2+3-m,y_1+y_2=\frac{a-b+2+2\times m}2=\frac{a-b}2+1+m$。

继续消除绝对值的影响，询问外面是不现实的，那么我们不妨询问里面，不妨询问 $(1,\frac{y_1+y_2}2),(\frac{x_1+x_2}2,1)$，设答案为 $c,d$。

那么就有：

$$\begin{cases}x_1-1+x_2-1+|y_1-y_2|=c \\ y_1-1+y_2-1+|x_1-x_2|=d\end{cases}$$

由于我们先前令 $x_1\le x_2,y_1\le y_2$，那么就能得出 $x_1+x_2,x_2-x_1$，容易解出 $x_1,x_2$，同理可以解出 $y_1,y_2$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define y1 qwqawa
#define y2 awaqwq

int n,m;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>n>>m;
		cout<<"SCAN "<<1<<' '<<1<<endl;
		int a;cin>>a;
		cout<<"SCAN "<<1<<' '<<m<<endl;
		int b;cin>>b;
		int sumx=(a+b)/2+3-m;
		int sumy=(a-b)/2+1+m;
		cout<<"SCAN "<<1<<' '<<sumy/2<<endl;
		int c;cin>>c;c+=2,c-=sumx;
		cout<<"SCAN "<<sumx/2<<' '<<1<<endl;
		int d;cin>>d;d+=2,d-=sumy;
		int x1=(d+sumx)/2,x2=sumx-x1;
		int y1=(c+sumy)/2,y2=sumy-y1;
		cout<<"DIG "<<x1<<' '<<y1<<endl;
		int nailong;cin>>nailong;
		if(nailong){
			cout<<"DIG "<<x2<<' '<<y2<<endl;
			cin>>nailong;
		}
		else{
			cout<<"DIG "<<x1<<' '<<y2<<endl;
			cin>>nailong;
			cout<<"DIG "<<x2<<' '<<y1<<endl;
			cin>>nailong;
		}
	}
	return 0;
}
```

---

