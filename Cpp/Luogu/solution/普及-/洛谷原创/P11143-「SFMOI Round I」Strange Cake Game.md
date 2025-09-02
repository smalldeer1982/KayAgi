# 「SFMOI Round I」Strange Cake Game

## 题目背景

小 $\mathcal{W}$ 和 小 $\mathcal{M}$ 在 CF 庄园里分蛋糕。


## 题目描述


有一块面积为 $n\times m$ 的矩形蛋糕。记其左上角顶点为 $(0,0)$，右下角顶点为 $(n,m)$，右上角顶点为 $(0,m)$。

蛋糕上分布着 $k$ 块巧克力，第 $i$ 块的位置为 $(x_i-0.5,y_i-0.5)$。**一个点上可能有不止一块巧克力。**

小 M 和 小 W 要切蛋糕。蛋糕刀起初在 $(0,0)$，小 W 先手，轮流移动蛋糕刀。设蛋糕刀在 $(x,y)$，则它可以被移动到 $(x,y+1)$ 或 $(x+1,y)$。

在若干步后，蛋糕会被切割轨迹完全分成两个部分——右上角的部分归小 W，左下角的部分归小 M。小 W 和小 M 都想吃到最多的巧克力，请帮他们计算：如果双方都按照最优策略行动，小 W 能分到几块巧克力。

如下是蛋糕的示例和一种可能的切蛋糕的方式。

![蛋糕示例](https://cdn.luogu.com.cn/upload/image_hosting/er9wuv91.png?x-oss-process=image/resize,m_lfit,h_500)
![切蛋糕示例](https://cdn.luogu.com.cn/upload/image_hosting/9o6ntvlb.png?x-oss-process=image/resize,m_lfit,h_500)

## 说明/提示

### 数据范围

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$n=m=1$；
- Subtask 2（10 pts）：$1 \le n \times m \le 60$；
- Subtask 3（15 pts）：$1 \le n \times m \le 10^5$；
- Subtask 4（20 pts）：$k=1$；
- Subtask 5（50 pts）：无特殊限制。


对于 $100\%$ 的数据，保证：

- $0 \le k \le 2 \times 10^5$；
- $1 \le n,m \le 10^{18}$；
- $1 \le x_i \le n$，$1 \le y_i \le m$。


## 样例 #1

### 输入

```
3 3
1
1 3```

### 输出

```
1```

# 题解

## 作者：_Punainen_ (赞：9)

## 题目大意

有一家蛋糕店被 $\mathcal W$ 帮和 $\mathcal M$ 帮俩群土匪抢劫了，但是蛋糕只有一个，于是他们决定瓜分这块蛋糕。

已知在蛋糕大小为 $n \times m$，上方有 $k$ 块巧克力，它们分别位于 $( x_i - 0.5 , y_i - 0.5 )$, 并且同一个位置可以有两块巧克力，因为这些巧克力太美味了，所以双方都想要分到尽可能多的巧克力。

蛋糕刀起初在坐标 $( 0 , 0 )$ 的位置，由双方轮流移动，经过猜拳，由 $\mathcal W$ 帮先手，每次可以使刀移动到 $(x+1,y)$ 或 $(x,y+1)$ 处，并且右上角部分分给 $\mathcal W$ 帮，左下角部分分给 $\mathcal M$ 帮，双方都采用最优策略，求 $\mathcal W$ 帮最多可分到多少巧克力？

---

## 思路

容易发现，$\mathcal W$ 帮为了获得更多的巧克力会尽量向下移动，而 $\mathcal M$ 帮会尽力向右方移动，就像下图，而题面的图是来扰乱我们思路的。

![](https://cdn.luogu.com.cn/upload/image_hosting/8kqcnwk7.png)因为 $( n , m \leq 10^{18})$，所以我们不能够进行暴力判断，只得寻找规律。

用一眼发现 $(1,1)$,$(2,2)$ 等点上的巧克力属于 $\mathcal W$ 方，则发现 $x_i$ 和 $y_i$ 可以取等号。而当 $x_i > y_i$ 时，属于倒霉蛋 $\mathcal M$ 帮，便可得出通解，当 $x_i \leq y_i$ 时，属于 $\mathcal W$。

---

## 代码

我马蜂有点难看，别介意。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int x[200111],y[200111],k,w,n,m;
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		cin>>x[i]>>y[i];
		if(x[i]<=y[i])w++;
	}
	cout<<w;
	return 0;
}
```

---

## 作者：M1__ (赞：2)

## 题目思路
考虑贪心算法。               
根据题意，我们可以猜出结论，在最优状态下，小 W 将一直向下移动，小 M 一定向右移动。             
又因为小 W 是先手，所以当这块巧克力的横坐标小于等于纵坐标，即 $x \le y$ 时，这块巧克力才可能归小 W 所有。        
另外，本题还有某些神秘做法可得 $20-25$ 分。                
要特别注意的是，此题的最后两个子任务是卡 long long 的。
## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	long long m,n,k,x,y,ans=0;//一定注意开long long
	cin>>m>>n;
	cin>>k;
	while(k--){
		cin>>x>>y;
		if(x<=y)ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：liyunhe (赞：1)

### 分析
显然，这道题两人的做法符合贪心策略。

![](https://cdn.luogu.com.cn/upload/image_hosting/847x41xl.png)

红蓝线的意思同题目
所以在直线 y=x （含）右上方的都为小 W 的范围。  
即 $y_i-x_i\ge 0$ 时第 $i$ 块归小 W 。
### 代码：
```cpp
#include<iostream>
#define int long long
using namespace std;
signed main(){
	int n,m,k,ans=0;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		if(y-x>=0)ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：jiangyunuo (赞：1)

### 题目大意：
有一个 $n \times m$ 的矩阵蛋糕，上面放了一些巧克力，巧克力放在由这一条条线中的格子里，$x_i$ 和 $y_i$ 表示巧克力放在 $(x_i-0.5,y_i-0.5)$ 上，即由 $(x_i-1,y_i)$、$(x_i,y_i-1)$、$(x_i,y_i)$、$(x_i-1,y_i-1)$ 四个点组成的矩形，小 W 与小 M 轮流切蛋糕，小 W 先，他们从 $(0,0)$ 开始，如果现在到了 $(x,y)$，那么他们下步必须走到 $(x+1,y)$ 或 $(x,y+1)$，他们都想得到最多的巧克力，，如果他俩都用最优策略，问小 W 最多可得多少块巧克力。
### 大体思路：
问个问题，最优策略是什么呢？  
绘制一幅图可以令我们更好的理解：  
![图](https://cdn.luogu.com.cn/upload/image_hosting/5ciwoaqj.png)  
现在我们要站在小 W 的角度去思考问题，怎样才是最优的呢？  
![图](https://cdn.luogu.com.cn/upload/image_hosting/5l9ndqzs.png)  
显然，当我们来到 $(1,0)$ 最好的选择，这是我们又要站到小 M 的角度思考。  
![图](https://cdn.luogu.com.cn/upload/image_hosting/msnro9rt.png)  
显然，当我们来到 $(1,1)$ 最好的选择。  
所以，这是怎么得来的呢？可以发现当我们想去获得最多的巧克力时，我们应该单单向下或右，我们会发现，假设我们在 $(x,y)$，那么当我们走到 $(x+1,y)$ 时，那么第 $x$ 行（指格子的第 $x$ 行）除了前 $y-1$ 格（同前）的巧克力，其他都归小 W；如果我们走到 $(x+1,y)$ 时，那么第 $y$ 列除了前 $x$ 格的巧克力，其他都归小 M。  
因此，我们可得：
![](https://cdn.luogu.com.cn/upload/image_hosting/z88ivtuo.png)  
小 W 一定会从 $(x,y)$ 走到 $(x+1,y)$，小 M 正好相反。  
那么我们已经知道规律了，那该如何如何判断呢？  
前面我们说过：  

>假设我们在 $(x,y)$，那么当我们走到 $(x+1,y)$ 时，那么第 $x$ 行（指格子的第 $x$ 行）除了前 $y-1$ 格（同前）的巧克力，其他都归小 W。

那么我们可以知道 $x_i$ 和 $y_i$ 表示的格是第 $x_i$ 行、第 $y_i$ 列的格子，那么当 $y_i \ge x_i$，时，那么这块巧克力就归小 W 了（当小 W 切的时候，$x=y$）。  
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m;
    cin>>n>>m;
    int k;
    cin>>k;
    double x,y;
    int a=0;       //记录小 W 可以获得的最多的巧克力。
    for(int i=1;i<=k;i++){
        cin>>x>>y;
        if(y>=x)a++;    //判断巧克力是否可以让小 W 得到。
    }
    cout<<a<<endl;
    return 0;
}
```

---

## 作者：zhang_Jimmy (赞：1)

首先，不难发现：如果想获得最优策略，先手小 W 一定会往下切，后手小 M 一定会往右切。

证明一下：

首先，如果想要让双方得到的巧克力尽量多，双方每人一定会朝同一个方向切，且双方的方向不同，因为这样能使他们分到的区域的大小之差尽量最小化。

然后分类讨论（均使用题目中的图片，红色代表小 W 的移动轨迹，蓝色代表小 M 的移动轨迹）：

1. 小 W 往下切，小 M 往右切，如图：

 ![](https://cdn.luogu.com.cn/upload/image_hosting/006b7k2l.png)

2. 小 W 往右切，小 M 往下切，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/21g56wh4.png)

很显然，第一种切法更优。故小 W 往下切，小 M 往右切的策略最优。

于是，我们只用统计 $x \le y$ 的巧克力数量并输出即可。时间复杂度 $O(k)$。注意要开 `long long`。

代码如下：

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ll k, n, m, x, y, ans = 0;
	cin >> n >> m >> k;
	for(int i = 1; i <= k; i ++)
		cin >> x >> y, ans += (x <= y ? 1 : 0);
	cout << ans;
	return 0;
}
```

---

## 作者：Hootime (赞：0)

_预防电信诈骗，从你我做起。——[yuruilin2026](https://www.luogu.com.cn/user/1294410)_ 
## 题意
有一块面积为 $n\times m$ 的矩形蛋糕，蛋糕上分布着 $k$ 块巧克力，第 $i$ 块的位置为 $(x_i-0.5,y_i-0.5)$。**一个点上可能有不止一块巧克力。**

小 M 和 小 W 要切蛋糕。刀起初在 $(0,0)$，小 W 先手，轮流移动刀。设刀在 $(x,y)$，则它可以被移动到 $(x,y+1)$ 或 $(x+1,y)$。

最后蛋糕会被切割成两个部分，小 W 得到右上部分。小 W 和小 M 都想吃到最多的巧克力，求如果双方都按照最优策略行动，小 W 能分到几块巧克力。

## 思路
我们将蛋糕视为一个方格状的地图，在 $(x_i-0.5,y_i-0.5)$ 的巧克力在方格 $(x_i,y_i)$ 内部。

我们需要明确两人的最优策略。设刀在 $(x,y)$，对于小 W，显然向下移动比向右移动好，因为他能多获得一个方格和方格内部的巧克力。对于小 M 则反之。然后我们能得到这样一个操作序列：下，左，下，左，……直到触碰边界。

所以对于一个巧克力 $(x_i,y_i)$，只需要判断 $x_i \le y_i$，满足条件就 `cnt++` 即可。

## 代码
### 注释版
```cpp
#include <bits/stdc++.h>
#define int long long // 不开 long long 见祖宗 
int n, m, k, cnt;
signed main(){
    scanf("%lld %lld\n%lld", &n, &m, &k);
    while(k--){ // 对于每块巧克力 
        int x, y;
        scanf("%lld %lld", &x, &y); // 输入 
        if(x <= y) cnt++; // 满足条件 
    }
    printf("%lld", cnt); // 输出 
}

```

### 无注释版
 _请不要直接提交我的代码。_ 
```
#include <bits/stdc++.h>
#define int long long 
int n, m, k, cnt;
signed main(){
    scanf("%lld %lld\n%lld", &n, &m, &k);
    while(k--){  
        int x, y;
        scanf("%lld %lld", &x, &y);  
        if(x <= y) cnt++; 
    }
    printf("%lld", cnt); 
}

```

---

