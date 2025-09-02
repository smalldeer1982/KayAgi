# [AGC010A] Addition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc010/tasks/agc010_a

黒板に $ N $ 個の整数が書かれています。$ i $ 番目の整数は $ A_i $ です。

これらの数に対して、高橋君は以下の操作を繰り返します。

- 偶奇が等しい $ 2 $ つの数 $ A_i,A_j $ を一組選び、それらを黒板から消す。
- その後、二つの数の和 $ A_i+A_j $ を黒板に書く。

最終的に黒板に数が $ 1 $ つだけ残るようにできるかどうか判定して下さい。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ A_i\ ≦\ 10^9 $
- $ A_i $ は整数

### Sample Explanation 1

以下のようにすれば、数を $ 1 $ つだけ残すことができます。 - 黒板から $ 1 $ と $ 3 $ を消し、$ 4 $ を書く。このとき、残る数は $ (2,4) $ である。 - 黒板から $ 2 $ と $ 4 $ を消し、$ 6 $ を書く。このとき、残る数は $ 6 $ だけである。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
NO```

# 题解

## 作者：__polar_ice (赞：4)

这道题只是一道判断**奇偶性**的题~~有点水~~

求一串数字的和的**奇偶性**，可得：这串数字的奇数个数的奇偶性就是这一串数字的奇偶性

**证明：**

假设$A$∈{$2n,2n+1$}，A中偶数出现了$X$次，奇数出现了$Y$次，则总和为$X·2n+Y(2n+1)=2n(X+Y)+Y$。

$\because2n(X+Y)$能被2整除，是偶数

$\therefore$这串数字的总和的**奇偶性**取决于Y，即奇数的个数。

$P.S.$我用`while(cin)`形式代替了`for`循环

**代码** $code$

```cpp
#include<iostream>
using namespace std;
int main()
{
    int x,cnt=0;
    cin>>x;//直接忽略n
    while(cin>>x)cnt+=x%2;//判断奇数出现的次数
    cout<<(cnt%2?"NO":"YES")<<endl;//最后再判断奇数的总个数的奇偶性
    return 0;
}
```

**共**10**行**~

---

## 作者：初音Miku (赞：2)

题意我觉得我已经说明的很清楚了吧。
```cpp
#include<iostream>//C++头文件
#include<algorithm>//标准头文件
#include<Hatsune_Miku>//AC头文件
using namespace std;
int n,a[100001],ans=0;//根据题意定义，都在int范围内，ans用来记录和。
int main(){
    cin>>n;//读入n
    for(int i=1;i<=n;i++){
        cin>>a[i];
         ans+=a[i];//记录总数值
    }
    if(ans%2==0)cout<<"YES"<<endl;//满足题意，输出YES换行。
    else cout<<"NO"<<endl;//不行就输出NO
    //大写！大写！大写！
    return 0;//结束
}
```

---

## 作者：ZolaWatle (赞：1)

## AT2302题解

题目大意：给定很长一串数，问这串数的**总和**是奇数还是偶数。

我的思路：统计这串数中奇数和偶数**分别有多少个**，再进行判断。

因为凡是上过小学的，都懂这个道理：

-  很多很多个偶数加起来还是偶数，即：

$$ 2\cdot k_{1}+2\cdot k_{2}+2\cdot k_{3}+...+2\cdot k_{n}=2\cdot(k_1+k_2+k_3+...+k_n) $$

- 偶数个奇数的总和也是偶数，举个例子吧：

假设有$n$（$n$为偶数）个奇数相加，可以列出以下式子：

$$ (2\cdot k_1 -1)+...+(2\cdot k_n-1) $$

$$ 2\cdot(k_1+k_2+k_3+...+k_n)-1\cdot n $$

因为$ n $是偶数，所以上式也为偶。

一个数的奇偶很好判断，**对$ 2 $取模**即可。开两个变量，$ even $和$ odd $，分别存奇数和偶数的个数。

在程序末，统计完奇偶，加一句判断就行了。

### 代码（奇丑）：

```cpp
#include <iostream>
#include <cstdio>
#define re register int  //玄学优化 
using namespace std;

int n,tmp,even,odd;

int main()
{
	std::cin>>n;
	
	for(re i=1;i<=n;i++)
	{
		std::cin>>tmp;  //不需要开数组 
		if(tmp%2==0)  //如果是偶数 
			even++;
		else
			odd++;
	}
	
	if((even==n)/*这一句其实可以不需要，因为全是偶数即奇数个数为0，而0也是偶数*/||(odd%2==0)) 
	//如果这一串数都是偶数或者奇数的数量为偶数 
		std::cout<<"YES";
	else
		std::cout<<"NO";  //按照题意输出即可 
		
	return 0;
}
```

**3Q~**

原题链接：[AT2302 [AGC010A] Addition](https://www.luogu.com.cn/problem/AT2302)

---

## 作者：asasas (赞：0)

~~这题又是恶评~~

# 切入正题

### 题意：给定$N$个数，求它们和的奇偶性

照题意模拟即可。

code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
     int n;
     long long a[100005];//注意要开long long!
     cin >> n;
     long long ans=0;//同样要开long long
     for (int i=1;i<=n;i++){
     	cin >> a[i];
     	ans+=a[i];
     }
     if (ans%2==0) cout << "YES\n";
     else cout << "NO\n";//AT要换行哦
}
```



---

## 作者：LCuter (赞：0)

直奔主题……

四种情况：

1.偶数加偶数等于偶数

2.偶数加奇数等于奇数

3.奇数加偶数等于奇数

4.奇数加奇数等于偶数

研究发现，加上一个偶数，奇偶性不变；加上一个奇数，奇偶性变

又因为刚开始的和为0，是偶数，所以初始值为true

之后每读入一个数做一次奇偶判断并作相应变化即可

```cpp
#include<cstdio>
int main(){
    int n,tmp;
    bool book=true;
    scanf("%d",&n);
    for(register int i=1;i<=n;i++){
        scanf("%d",&tmp);
        if(tmp%2!=0){
            book=!book;
        }
    }
    if(book){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
}
```

---

## 作者：OdtreePrince (赞：0)

# -取余出奇迹-

> 取余能出奇迹，但是数据太水，最原始的方法都过了

分析一下数据

每次对输入的数取模 %

用sum统计和，每次再对sum取模，sum为零是偶数，or和为奇数

应该不难理解，(a+b)%2=((a%2)+(b%2))%2

这样数据再大也能过  -^ ^-

注：模运算以%表示。
~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k,sum=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&k);
        sum+=k%2;
        sum%=2;
    }
    if(sum) cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
    return 0;
}~~~

---

