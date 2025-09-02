# color

## 题目描述

洛谷的名字颜色和咕值直接挂钩，具体细则见 [洛谷咕值系统介绍](https://www.luogu.com.cn/discuss/83952)。

给出某洛谷用户的五项咕值指标的得分，输出该用户的名字颜色。保证该用户不是棕名和紫名。

## 说明/提示

**【样例说明】**

三个样例的咕值分别为 $263,140,0$，名字颜色分别为红、绿、灰。

**【数据范围】**

对于 $20\%$ 的数据，满足五项指标分数均 $\le 10$；

对于另外 $20\%$ 的数据，满足五项指标分数均 $\ge 90$；

对于 $100\%$ 的数据，保证五项指标分数均 $\in [0, 100]$。

## 样例 #1

### 输入

```
100 14 9 55 85```

### 输出

```
Red```

## 样例 #2

### 输入

```
100 10 10 10 10```

### 输出

```
Green```

## 样例 #3

### 输入

```
0 0 0 0 0```

### 输出

```
Gray```

# 题解

## 作者：Yamchip (赞：8)

这道题非常简单，把五个值加起来，再判断一下就可以了，不知道估值的去看洛谷咕值系统介绍。

贴个代码：
```
#include<bits/stdc++.h>
using namespace std;
int a, b, c, d, e, sum;
int main()
{
    cin >> a >> b >> c >> d >> e;
    sum = a + b + c + d + e;
    if(sum <= 99)
        cout << "Gray";
    else if(sum <= 119)
        cout << "Blue";
    else if(sum <= 169)
        cout << "Green";
    else if(sum <= 229)
        cout << "Orange";
    else
        cout << "Red";
    return 0;
}
```

---

## 作者：Hughpig (赞：3)

根据题意，用户的咕值就是五项咕值指标的总和，然后我们就可以通过咕值来判断用户名字颜色了，具体规则：

> 咕值与用户名的颜色直接挂钩，目前，$0\sim 99$ 分为灰名，$100\sim 119$ 分为蓝名，$120\sim 169$ 分为绿名，$170\sim 229$ 分为橙名，$230\sim500$ 分为红名，此标准会根据实际情况进行适当更改。

（摘自[洛谷咕值系统介绍](https://www.luogu.com.cn/discuss/83952)）。

然后依次判断即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e;

int main()
{
    cin>>a>>b>>c>>d>>e;
    int qwq=a+b+c+d+e;//计算所有咕值指标的综合
    //依次判断
    if(qwq<100)cout<<"Gray";
    else if(qwq<120)cout<<"Blue";
    else if(qwq<170)cout<<"Green";
    else if(qwq<230)cout<<"Orange";
    else cout<<"Red";
	return 0;
}
```

---

## 作者：fkcufk (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9516)

这道题就是判断即可，具体详见代码，不做过多解释。

```cpp
#include<iostream>
using namespace std;
int main(){
    
    int a,b,c,d,e;
    cin>>a>>b>>c>>d>>e;
    int sum=a+b+c+d+e;
    if(sum>=230)cout<<"Red";
    else if(sum>=170)cout<<"Orange";
    else if(sum>=120)cout<<"Green";
    else if(sum>=100)cout<<"Blue";
    else cout<<"Gray";
}
```

---

## 作者：Forever_LYD (赞：1)

大水题，其实就是判断，对于新手极其友好。

首先要先算出总估值 $ans$ 再进行判断，其中分界数 $100$ $120$ $170$ $230$ 是用来判断的，代码实现就非常简单了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c,d,e;
  	  int ans=0;
    cin>>a>>b>>c>>d>>e;
    ans=a+b+c+d+e;
    if(ans<100)cout<<"Gray";
    else if(ans>=100&&ans<120)cout<<"Blue";
    else if(ans>=120&&ans<170)cout<<"Green";
    else if(ans>=170&&ans<=230)cout<<"Orange";
    else cout<<"Red";
    return 0;
}
```


---

## 作者：wangyinghao (赞：0)

将输入的数相加就是这个用户的咕值，再进行判断就好了。

### AC Code

```cpp
#include<iostream>
using namespace std;

int main(){
	int a,b,c,d,e,cnt=0;
	cin>>a>>b>>c>>d>>e;
	cnt=a+b+c+d+e;
	if(cnt<100) cout<<"Gray";
	else if(cnt>=100 && cnt<120) cout<<"Blue";
	else if(cnt>=120 && cnt<170) cout<<"Green";
	else if(cnt>=170 && cnt<=230) cout<<"Orange";
	else cout<<"Red";
	return 0;
}
```

---

