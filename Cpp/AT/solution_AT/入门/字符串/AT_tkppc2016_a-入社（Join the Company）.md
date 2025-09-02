# 入社（Join the Company）

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tkppc2/tasks/tkppc2016_a

joisinoお姉ちゃんは、AtJump社というゲーム会社に就職した。  
 joisinoお姉ちゃんは極めて優秀なプログラマーなので、ゲームプログラミングだけでなく、社内のいろいろな問題を解決するプログラムの作成も仕事として任されている。  
 joisinoお姉ちゃんの最初の仕事は、二つの文字列に分割されてしまった文字列を元に戻すプログラムを作成することである。

## 说明/提示

### Sample Explanation 1

"at"と"jump"をつなげると、"atjump"になります

## 样例 #1

### 输入

```
at
jump```

### 输出

```
atjump```

## 样例 #2

### 输入

```
joi
shino```

### 输出

```
joishino```

# 题解

## 作者：Catcats (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_tkppc2016_a)

## 题目大意

合并输入的 $2$ 个字符串，并输出。

## 题目解法

提供 $2$ 种解法：

### 1. 分别读入与输出

把两个字符串分开输出。代码如下：

```cpp
cin>>a>>b;
cout<<a<<b<<endl;
```

### 2. 运用 `string` 的 `+` 运算符

`string` 类有重载 `operator+`，可以合并 $2$ 个字符串。

我们可以用 `a+b` 合并输入的两个字符串。代码如下：

```cpp
cin>>a>>b;
cout<<a+b<<endl;
```

当然也可以使用 `char*` 的分别输出，以及 `strcat()` 完成本题。

---

## 作者：TRZ_2007 (赞：0)

嗯……~~C党的同学们都这么懒吗？~~  
今天本蒟蒻~~就要为C党的同学们出头！~~  
此题大概的题意，根据本蒟蒻的理解，就是：输入两个字符串，把它们连接起来。那么此题就是考察字符串的输入输出   
下面给出我们的蒟蒻代码  
```
#include <stdio.h>//C党万岁！
int main()
{
	char a[51],b[51];
	gets(a);gets(b);//gets字符串读入，也可以换成scanf("%s",a);scanf("%s",b);
	printf("%s",a);//注意输出不能用puts，要不然自动换行！
	printf("%s",b);
}
```

---

## 作者：LCuter (赞：0)

本题利用string的‘+’直接拼接在一起输出即可~

~~string版a+b~~

```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
    string a,b;
    cin>>a>>b;
    cout<<a+b;
    return 0;
}
```

---

