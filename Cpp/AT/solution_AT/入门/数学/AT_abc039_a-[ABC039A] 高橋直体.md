# [ABC039A] 高橋直体

## 题目描述

高桥君有一个高为 $A\ \mathrm{cm}$，宽为 $B\ \mathrm{cm}$，深为 $C\ \mathrm{cm}$ 的长方体。请问这个长方体的表面积是多少 $cm^2$？

## 说明/提示

### 限制

- $1 \leq A, B, C \leq 100$
- 输入的所有数均为整数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 3 4```

### 输出

```
52```

## 样例 #2

### 输入

```
3 4 2```

### 输出

```
52```

## 样例 #3

### 输入

```
100 100 100```

### 输出

```
60000```

## 样例 #4

### 输入

```
1 1 1```

### 输出

```
6```

# 题解

## 作者：Ofnoname (赞：3)

抢占题解制高点。

简单模拟，看了翻译就会做。

表面积公式：$S=2(ab+bc+ca)$，能上洛谷的人应该都知道。

C++ Code:
```
#include <iostream>
using namespace std;

int a,b,c;

int main()
{
    cin>>a>>b>>c;
    cout<<2*(a*b+b*c+a*c);
    return 0;
}
```

---

## 作者：Phecda (赞：1)

此题很难！此题很难！此题很难！

我一开始看的一脸懵逼（因为不相信这么“难”！）

题目大意：给定一个长方形的长宽高，求其表面积

哇！~~是一道很难的计算几何哎！~~

根据题意，我们直接算出长方形的每一个面的面积然后累加就好了

但是——我们有小学数学老师教的公式哎~！

那就是——

$s=((a*b)+(b*c)+(a*c))*2$

于是套上公式，别写错就好了！

（此处需注意，如果一开始ans（答案）要参与乘法运算，请赋值成1，否则....（不可描述））

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define ll long long

using namespace std;

ll ans=1;
ll a,b,c;

int main(){
	scanf("%lld%lld%lld",&a,&b,&c);
	ans=a*b;
	ans+=a*c;
	ans+=b*c;
	ans*=2;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：loserchen (赞：0)

# 题意
可以看到，题目就是给了我们一个立方体的长，宽，高，求出它的表面积。

根据小学老师给的公式，可求出：
 $$ S=2(ab+ac+bc) $$
 所以，可以通过公式，得出代码：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c;
	cin>>a>>b>>c;
	cout<<(a*b+a*c+b*c)*2;
	return 0;
}

```

~~此题结束~~

---

## 作者：Xxzxx (赞：0)

这题————红题都算不上，那些大佬们把它提到了 

# 普及/提高-！！！

这根本就是看你手不手残……

```
#include<iostream>//呵呵呵
using namespace std;
int a,b,c,ans;
int main()
{
    cin>>a>>b>>c;//输入
    ans+=a*b*2;//求两个面的面积
    ans+=a*c*2;//求两个面的面积
    ans+=c*b*2;//求两个面的面积
    cout<<ans<<endl;//输出
    return 0;///你懂的……
}
```

---

## 作者：goodlearndaydayup (赞：0)

其实这是一道水题，唯一难度在于~~日文~~。
题意：给你三个数a,b,c;求出这个长方体的表面积。
上代码
```
#include<iostream>
#include<fstream>
#include<algorithm>//头文件

using namespace std;
int main()
{
     int a,b,c;//长宽高
	 cin>>a>>b>>c;//输入
	 cout<<(a*b+a*c+b*c)*2;//小学五年级数学公式

    return 0;
}
```

---

