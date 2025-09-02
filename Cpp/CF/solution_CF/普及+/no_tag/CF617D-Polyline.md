# Polyline

## 题目描述

在平面直角坐标系上有三个点。我们的目标是画一个没有自交的简单折线，使得这条折线穿过三个点。同时，折线的所有线段都只能与坐标轴平行。求出折线可能包含的最少的线段数。

## 样例 #1

### 输入

```
1 -1
1 1
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
-1 -1
-1 3
4 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 1
2 3
3 2
```

### 输出

```
3
```

# 题解

## 作者：xiaoxiaoxia (赞：4)

# Part 1 题意分析
给你三个点，问最少有几条折线，线只能是横着或者竖着。
# Part 2 思路分析
这题目其实没什么可以说的，直接打一个暴力就可以了。主要有以下几种情况：
- $ans=1$：如果三个 $x$ 都相同，或者三个 $y$ 都相同。
- $ans=2$：如果任意两个 $x$ 相同，并且另一个点的 $y$ 大于等于这两个点 $y$ 的最大值或者小于等于这两个点 $y$ 的最小值。
- $ans=3$：其余情况。
# Part 3 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long x[5],y[5];
    for(int i=0;i<3;i++)
    {
        cin>>x[i]>>y[i];
    }
    int ans=0;
    if((x[0]==x[1]&&x[1]==x[2])||(y[0]==y[1]&&y[1]==y[2]))//第一种情况 
	{
		ans=1;
	}
    else
    {
        for(int i=0;i<3;i++)
        {
            int j=(i+1)%3, k=(i+2)%3;
            if(x[i]==x[j]&&(y[k]>=max(y[i],y[j])||y[k]<=min(y[i],y[j])))//第二种情况 
			{
				ans=2;
			}
            if(y[i]==y[j]&&(x[k]>=max(x[i],x[j])||x[k]<=min(x[i],x[j])))//第三种情况 
			{
				ans = 2;
			}
        }
    }
    if(!ans)
	{
		ans=3;	
	}
    cout<<ans<<endl;//输出 
    return 0;
}
```


---

## 作者：Kotobuki_Tsumugi (赞：2)

首先有一个显然的结论：答案不大于 $3$。

为什么？我们分类讨论。

下文为叙述方便，将平行于横轴的直线成为横线，将平行于竖轴的直线称为竖线。对于任意三个点，我们分别做过他们的横线。

那么会有三种情况。最简单的一种：三条直线重合，答案为 $1$。

第二种情况：有两条重合。如下图所示。

[![pkwMwcQ.png](https://s21.ax1x.com/2024/06/15/pkwMwcQ.png)](https://imgse.com/i/pkwMwcQ)

这时我们可以过点 C 做 AB 的垂线，此时折线 ABEC 答案为 $2$。

[![pkwMs7q.png](https://s21.ax1x.com/2024/06/15/pkwMs7q.png)](https://imgse.com/i/pkwMs7q)

最后一种情况：三条均不重合。如下图所示。

[![pkwMa9S.png](https://s21.ax1x.com/2024/06/15/pkwMa9S.png)](https://imgse.com/i/pkwMa9S)

这时我们可以过 A 点做另外两条的垂线。此时折线 BHAGC 答案为 $3$。

[![pkwMd1g.png](https://s21.ax1x.com/2024/06/15/pkwMd1g.png)](https://imgse.com/i/pkwMd1g)

考虑完横线，同理推出竖线情况。看横线和竖线哪个答案小即可。

最后考虑一个特殊情况：在刚才讨论的第二种情况中，若 C 点被夹在 A 和 B 中间，此时折线 ADCEB 答案为 $3$。可以看图理解。

[![pkwMNh8.png](https://s21.ax1x.com/2024/06/15/pkwMNh8.png)](https://imgse.com/i/pkwMNh8)

[提交记录](https://codeforces.com/contest/617/submission/265479178)。

---

## 作者：kimidonatsu (赞：1)

~~这是 *1700?~~

由于只有三个点，符合题意的过三点的折线段数显然为 1 ~ 3，可以结合图进行分类讨论，这里提供一种更好理解的做法。

如果所有点的 $x$ 坐标或者 $y$ 坐标相同，那么答案为 $1$。

答案为 $2$ 的情况如下：枚举所有点对 $(A, B), (A, C), (B, C)$。假设取出 $(A, B)$，答案为 $2$ 的情况是 $x_A = x_B$ 且 $y_C$ 满足 $y_C \gt \max(y_A, y_B)$ 或 $y_C \lt \min(y_A, y_B)$。$y_A = y_B$ 的情况同理，此时都可以构建出一个直角。

其余情况则为 $3$，这时需要我们可以用第一个点和第二个点作直角，再用第三个点和第二个点作直角，就可以画出折线。

![Image](https://cdn.luogu.com.cn/upload/image_hosting/2stjg7x9.png)

如果有点抽象可以看这张图，$D, B, E$ 为第一种情况，$B, E, C$ 为第二种情况，$A, B, C$ 为第三种情况。

[Submission](https://codeforces.com/contest/617/submission/263128566)

---

## 作者：achjuncool (赞：1)

# 做法

首先是三点在一条与坐标轴平行的直线上，这种情况显然答案是 $1$。

接着是只有其中两点（$A,B$）在一条与坐标轴平行的直线上，第三个点（ $C$）要分两种情况：

- 第一种是这样的，不能自交，所以答案是 $3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/sswtdrkl.png)

- 第二种是这样的，只需把线段 $AB$ 延长一点即可，答案是 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4ityc3n0.png)

如果上面两个条件都不满足，那显然答案就是 $3$ 了。

# Code

~~我写的很麻烦，容易打错~~

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
ll xa, xb, xc, ya, yb, yc;
int main(){
	qwq;
	cin >> xa >> ya >> xb >> yb >> xc >> yc;
	if((xa == xb && xb == xc) || (ya == yb && yb == yc)) cout << 1 << endl;
	else if(ya == yb && (xc >= max(xa, xb) || xc <= min(xa, xb))) cout << 2 << endl;
	else if(ya == yc && (xb >= max(xa, xc) || xb <= min(xa, xc))) cout << 2 << endl;
	else if(yb == yc && (xa >= max(xb, xc) || xa <= min(xb, xc))) cout << 2 << endl;
	else if(xa == xb && (yc >= max(ya, yb) || yc <= min(ya, yb))) cout << 2 << endl;
	else if(xa == xc && (yb >= max(ya, yc) || yb <= min(ya, yc))) cout << 2 << endl;
	else if(xb == xc && (ya >= max(yb, yc) || ya <= min(yb, yc))) cout << 2 << endl;
	else cout << 3 << endl;
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF617D Polyline
## 题意
在二维平面里有三个点，求用一条折线最少拐几次能经过这三个点。这条折线只能由平行于 $x,y$ 轴的线构成。输出最少拐的次数 $+1$。
### 思路分析
首先这道题类似于贪吃蛇游戏，我们知道答案肯定最大就是 $3$。（因为你可以一条线对应一个点，而二维平面里所以横竖的线都是相交的，在交点处拐即可）。\
那么我们就可以探究一下答案为 $1,2$ 的情况。
1. 答案为 $1$ 的情况十分明显，就是三点共线的情况。
2. 答案为 $2$ 的情况要求一定有两个点能被一条线穿过，于是很自然想到有两个点共线。但是仔细思考一下会发现这并不是一个充分条件。
因为如果第三个点在这两个点的中间部分，我们就无法拐一次到达第三个点。于是我们需要把这种情况剔除，而剩下的两点共线我们都可以把共线的其中一点忽略，于是都可以只拐一次经过所有点。
### 简洁的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x_1,x_2,y_1,y_2,x_3,y_3,ans;
signed main(){
    cin>>x_1>>y_1>>x_2>>y_2>>x_3>>y_3;
    if((x_1==x_2&&x_2==x_3)||(y_1==y_2&&y_2==y_3)){
        cout<<1<<'\n';
    }else if(x_1==x_2||y_1==y_2||x_1==x_3||y_1==y_3||x_2==x_3||y_2==y_3){
        if(x_1==x_2&&(y_3>=max(y_1,y_2)||y_3<=min(y_1,y_2)))cout<<2<<'\n';
        else if(y_1==y_2&&(x_3>=max(x_1,x_2)||x_3<=min(x_1,x_2)))cout<<2<<'\n';
        else if(x_1==x_3&&(y_2>=max(y_1,y_3)||y_2<=min(y_1,y_3)))cout<<2<<'\n';
        else if(y_1==y_3&&(x_2>=max(x_1,x_3)||x_2<=min(x_1,x_3)))cout<<2<<'\n';
        else if(x_2==x_3&&(y_1>=max(y_2,y_3)||y_1<=min(y_2,y_3)))cout<<2<<'\n';
        else if(y_2==y_3&&(x_1>=max(x_2,x_3)||x_1<=min(x_2,x_3)))cout<<2<<'\n';
        else cout<<3<<'\n';
    }else{
        cout<<3<<'\n';
    }
    return 0;
}
```

---

