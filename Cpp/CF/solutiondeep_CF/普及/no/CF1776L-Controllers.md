# 题目信息

# Controllers

## 题目描述

You are at your grandparents' house and you are playing an old video game on a strange console. Your controller has only two buttons and each button has a number written on it.

Initially, your score is $ 0 $ . The game is composed of $ n $ rounds. For each $ 1\le i\le n $ , the $ i $ -th round works as follows.

On the screen, a symbol $ s_i $ appears, which is either $ \texttt{+} $ (plus) or $ \texttt{-} $ (minus). Then you must press one of the two buttons on the controller once. Suppose you press a button with the number $ x $ written on it: your score will increase by $ x $ if the symbol was $ \texttt{+} $ and will decrease by $ x $ if the symbol was $ \texttt{-} $ . After you press the button, the round ends.

After you have played all $ n $ rounds, you win if your score is $ 0 $ .

Over the years, your grandparents bought many different controllers, so you have $ q $ of them. The two buttons on the $ j $ -th controller have the numbers $ a_j $ and $ b_j $ written on them. For each controller, you must compute whether you can win the game playing with that controller.

## 说明/提示

In the first sample, one possible way to get score $ 0 $ using the first controller is by pressing the button with numnber $ 1 $ in rounds $ 1 $ , $ 2 $ , $ 4 $ , $ 5 $ , $ 6 $ and $ 8 $ , and pressing the button with number $ 2 $ in rounds $ 3 $ and $ 7 $ . It is possible to show that there is no way to get a score of $ 0 $ using the second controller.

## 样例 #1

### 输入

```
8
+-+---+-
5
2 1
10 3
7 9
10 10
5 3```

### 输出

```
YES
NO
NO
NO
YES```

## 样例 #2

### 输入

```
6
+-++--
2
9 7
1 1```

### 输出

```
YES
YES```

## 样例 #3

### 输入

```
20
+-----+--+--------+-
2
1000000000 99999997
250000000 1000000000```

### 输出

```
NO
YES```

# AI分析结果

### 题目内容重写

你正在祖父母家玩一款古老的视频游戏，使用一个奇怪的游戏机。你的控制器只有两个按钮，每个按钮上写有一个数字。

初始时，你的得分为 $0$。游戏由 $n$ 轮组成。对于每一轮 $1\le i\le n$，第 $i$ 轮的操作如下：

屏幕上会出现一个符号 $s_i$，可能是 $+$（加号）或 $-$（减号）。然后你必须按下控制器上的两个按钮之一。假设你按下了一个写有数字 $x$ 的按钮：如果符号是 $+$，你的得分将增加 $x$；如果符号是 $-$，你的得分将减少 $x$。按下按钮后，该轮结束。

当你完成所有 $n$ 轮后，如果你的得分为 $0$，你就赢了。

多年来，你的祖父母购买了许多不同的控制器，因此你有 $q$ 个控制器。第 $j$ 个控制器上的两个按钮分别写有数字 $a_j$ 和 $b_j$。对于每个控制器，你需要计算是否可以使用该控制器赢得游戏。

### 算法分类
数学

### 题解分析与结论

这道题的核心是通过数学分析来判断是否可以通过选择按钮的数字来使得最终得分为0。题解主要集中在如何通过统计加号和减号的数量，并结合按钮的数字关系来判断是否存在解。

### 所选高分题解

#### 题解1：作者：yingkeqian9217 (5星)
**关键亮点：**
- 通过统计加号和减号的数量，简化问题。
- 使用数学公式推导出解的条件，避免复杂的遍历。
- 代码简洁且高效，处理了边界情况。

**核心代码：**
```cpp
#include<bits/stdc++.h>
#define P (n+sum>>1)
#define M (n-sum>>1)
#define K (abs(sum)/abs(x-y)) 
#define Nsw (P<M&&x>y||P>M&&x<y)
#define judge(x,y) (x*K<=y)
using namespace std;
typedef long long ll;
ll n,q,sum;
char ch;
signed main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		cin>>ch;
		sum+=(ch=='+'?1:-1);//记录P-M
	}
	scanf("%lld",&q);
	while(q--){
		ll x,y,g;
		scanf("%lld%lld",&x,&y);
		if(Nsw) swap(x,y);//注意P,M与a,b的对应关系
		if(x==y){//特判
			printf(sum?"NO\n":"YES\n");
			continue;
		}
		g=__gcd(x,y),x/=g,y/=g;
		if(!(sum%(x-y))&&judge(x,P)&&judge(y,M))
     		 printf("YES\n");//构造合法解
		else printf("NO\n");
	}
	return 0;
}
```

#### 题解2：作者：Night_fall (4星)
**关键亮点：**
- 通过数学推导，简化了问题的复杂度。
- 使用最小公倍数和最大公约数来优化计算。
- 代码逻辑清晰，处理了多种边界情况。

**核心代码：**
```cpp
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long

int u,d;

signed main(){
    int n,T;
    cin>>n;
    for(int i=1;i<=n;i++){
        char ch;
        cin>>ch;
        if(ch=='+') u++; //统计个数
        else d++;
    }
    cin>>T;
    int cha=abs(u-d);//作差
    if(u<d) swap(u,d);//固定大小关系，简化问题
    if(cha==0){
    	while(T--) cout<<"YES\n";//加号个数等于减号个数，全部抵消
    	exit(0); //相当于 return 0;
    }
    while(T--){
        int a,b;
        cin>>a>>b;
        int gcd=__gcd(a,b);//求最小公倍数中的一个过程。
        a/=gcd,b/=g; //把a,b当做x,y，下同
        int ct=abs(a-b);//作差
        if(ct==0||cha/ct!=cha*1.0/ct){ //a=b或者不是整数倍
            cout<<"NO\n";
            continue;
        }
        if(a<b) swap(a,b);//固定大小关系
        if(cha/ct*a<=u&&cha/ct*b<=d) cout<<"YES\n"; //x,y < n,m，同时a,u都是大的，b,d都是小的，一一对应
        else cout<<"NO\n";
    }
    return 0;
}
```

### 最优关键思路与技巧
1. **统计符号数量**：通过统计加号和减号的数量，简化问题。
2. **数学推导**：利用最大公约数和最小公倍数来优化计算，判断是否存在解。
3. **边界处理**：处理了按钮数字相同和符号数量相等的情况。

### 可拓展之处
- 类似的问题可以通过统计和数学推导来简化复杂度，例如在组合数学中常见的问题。
- 可以扩展到更多按钮或更多符号的情况，但需要更复杂的数学推导。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)

### 个人心得总结
- **调试经历**：在处理边界情况时，容易忽略符号数量相等或按钮数字相同的情况，需要特别注意。
- **顿悟感想**：通过数学推导，可以将看似复杂的问题简化为简单的公式判断，大大提高了效率。

---
处理用时：38.50秒