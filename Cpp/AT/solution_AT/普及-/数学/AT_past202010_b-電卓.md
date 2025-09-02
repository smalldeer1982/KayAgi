# 電卓

## 题目描述

在你的计算器上输入非负整数 $ X，\ Y $，然后以 $ \frac{X}{Y} $ 为开头，没有多余的 $ 0 $，小数点后第 $3$ 及以下位的数全部舍弃，显示到小数点后第 $2$ 位。例如，当 $ X=4,Y=2$ 时，计算器上显示  `2.00`；当 $ X=2,Y=3$ 时，计算器上显示 ` 0.66`。但是，如果 $Y=0$ 的时候要显示 `ERROR`。

输入 $ X,Y $，请你编写出求计算器显示的程序。

## 说明/提示

- 输入的所有的数都是整数；
- $ 0\ \leq\ X,\ Y\ \leq\ 100 $

样例解释 $1$：

- $ \frac{X}{Y}= 33.33333 \ \cdots $，计算器上显示的是到小数点后第 $ 2 $ 位 `33.33`。

样例解释 $2$：

- 在 $ Y=0 $ 的情况下输出 `ERROR`。

## 样例 #1

### 输入

```
100 3```

### 输出

```
33.33```

## 样例 #2

### 输入

```
42 0```

### 输出

```
ERROR```

# 题解

## 作者：Ggsddu_zzy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202010_b)

#### 题目大意

给定 $x$ 和 $y$，求 $ \dfrac{x}{y}$。

舍弃小数点后第三及以下位。

#### 解题思路

首先判断 $ \dfrac{x}{y}$ 是否可以成立，也就是判断 $y$ 是否等于零，是就输出 `ERROR` 直接 `return 0;`。

因为要舍弃小数点后第三及以下位，输出要用到一点小技巧：[分离数位](https://www.luogu.com.cn/blog/677671/fen-li-shuo-wei-gui-ze)：

- 先将 $ \dfrac{x}{y}$ 的整数部分输出；

- 然后将十分位挪到个位，也就是 $n \times 10$ 再 $\div\ m$，再 $\bmod10$，得到现在的个位，也是就是十分位，将它输出；

- 最后将百分位挪到个位，也就是 $n \times 100$ 再 $\div\ m$，再 $\bmod10$，得到现在的个位，也是就是百分位，将它输出；

注意整数部分后面要有小数点：`.`。

#### 代码

[AC记录](https://www.luogu.com.cn/record/97445309)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main() {
	cin>>n>>m;
	if(m==0) {
		cout << "ERROR\n";  //判断除数是否为0
		return 0;
	} 
    cout<<n/m <<'.';         //整数部分
    cout<<(n*10/m)%10;       //十分位
    cout<<(n*100/m)%10<<'\n';//百分位
    return 0;
}
```



---

## 作者：CEFqwq (赞：1)

这道题看起来就是个计算器，开始我这样写：

```cpp
#include<bits/stdc++.h>
using namespace std;
double x,y;
int main(){
	scanf("%lf%lf",&x,&y);
	if(y==0){
		printf("ERROR\n");
		exit(0);//也可以写作return 0;在main函数中二者等价，其它函数则不同 
	}
	printf("%.2lf",x/y);
}
```

在第六个点 WA 了，所以应该逐位取（具体思路见代码）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
int main(){
	cin>>x>>y;
	if(y==0){//不能除以0
		printf("ERROR\n");
		exit(0);//也可以写作return 0;在main函数中二者等价，其它函数则不同 
	}
	int b=2;//迭代轮数，这样写可以适应更多类似题型，相当于一个模板 
	printf("%d.",x/y);//整数部分先算
	for(int i=1;i<=b;i++)printf("%d",(x*((int)(pow(10,i)+0.5))/y)%10);//小数部分由于浮点数误差，要四舍五入，这个代码就是计算商的第i位
	printf("\n");//十年OI一场空，不加换行见祖宗 
}
```

其他题解基本都是针对本题完成，如果位数更多就比较麻烦，但这个代码可以适应，改迭代轮数即可。正如代码中所说。AT 所有代码要加换行。

---

## 作者：Enoch006 (赞：0)

### 题目大意：

输入两个数 $X$ 和 $Y$，求 $\frac{X}{Y}$ 保留到两位小数。注意，这里的保留两位小数是指直接舍弃第三位小数。

### 题目分析：

- 首先：整数部分直接用整除输出。

- 接着：既然不能直接四舍五入输出小数部分（因为直接舍弃第三位），所以我们得一位一位输出。如何一位一位输出呢？我们只需要将原数 $X$ 乘 $10$ 再除以 $Y$ 再对 $10$ 取模得到 $\frac{X}{Y}$ 的十分位。而百分位就可以用原数 $X$ 乘 $100$ 再除以 $Y$ 再对 $10$ 取模。

### 题目代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,x; 
int main() {
    cin>>a>>x;
    if(x==0){
    	cout<<"ERROR\n";
		return 0; 
	}
	cout<<a/x<<"."<<a*10/x%10<<a*100/x%10;
    return 0;
}    
```


---

## 作者：kiki_123 (赞：0)

[$\color{red}\text{题目传送门}$](https://www.luogu.com.cn/problem/AT_past202010_b)

[$\color{red}\text{更好的阅读体验}$](https://www.luogu.com.cn/blog/Alex-ZJY/solution-at-past202010-b)

## 题意
- 给出两个数 $x,y$，输出 $\frac{x}{y}$。
- 输出结果的整数部分和小数点后两位（**不是保留两位小数**）。
- **例：输入`2 3`，输出`0.66`。**

## 分析
由于不是保留两位小数，所以不能直接输出。

先判断这个式子是否有意义，如果 $y=0$ ，输出`ERROR`。

其他情况的思路：
- 整数部分为 $x\div y$（这里的 $x,y$ 都是`int`类型的，所以 $x \div y$ 是整除运算）。
- 小数部分第一位为 $(x\times10\div y)\bmod10$（意思是把 $x$ 扩大 $10$ 倍再除，这样原来的小数第一位就到了个位）。
- 小数部分的第二位为 $(x\times100\div y)\bmod 10$，原因同上。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x,y;
	cin>>x>>y;
	if(y==0) cout<<"ERROR";
	else cout<<x/y<<'.'<<(x*10/y)%10<<(x*100/y)%10;
	return 0;
}
```

---

