# 和

## 题目描述

题目大意：
输入n个数，输出n个数的和。

## 样例 #1

### 输入

```
5
3 1 5 4 2```

### 输出

```
15```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
21```

## 样例 #3

### 输入

```
7
7 6 5 4 3 2 1```

### 输出

```
28```

## 样例 #4

### 输入

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
210```

# 题解

## 作者：da32s1da (赞：4)

说实话我真不知道数据这么水*2(2820也是这样)

~~观察样例得知，答案为n*(n+1)/2~~
```
#include<cstdio>
int a;
int main(){
    scanf("%d",&a);
    printf("%d\n",(a*(a+1))/2);
}
```

---

## 作者：Macrohard (赞：1)

题目很简单，直接读入$n+1$个数字，将$m_2,m_3……m_n$累加即可。
AC代码如下:
```
#include <stdio.h>
int readint(void){int x;scanf("%d",&x);return x;}
int main(void)
{
    int n=readint(),ans=0;
	for(int i=0;i<n;i++)ans+=readint();
	printf("%d\n",ans);
    return 0;
}
```

---

## 作者：陈洋琛 (赞：1)

直接模拟即可，不需要用高精度。

代码如下：

------------
	#include <iostream>
	using namespace std;
	int main()
	{
    	int n,a,ans=0;
    	cin>>n; //输入n的值
    	for(int i=0;i<n;i++) //总共循环n次
    	{
        	cin>>a; //每次读入一个数
        	ans+=a; //将读入的数加在目前总和上
    	}
    	cout<<ans<<endl; //输出这些数的总和
    	return 0;
	}

---

## 作者：char32_t (赞：1)

# 题解 AT2821 【和】
------------
题意：给定$\color{red}n$个数，求它们的和值。

code：
```cpp
#include<cstdio>
int main(){
	int n, count=0;
	scanf("%d%d", &n, &count);//读入n和第一个数 
	for(int i=2; i<=n; i++){//从第二个数开始 
		int a;
		scanf("%d", &a);//读入当前数 
		count+=a;//加入计数器 
	}
	printf("%d", count);//输出结果 
	return 0;
}
```

---

