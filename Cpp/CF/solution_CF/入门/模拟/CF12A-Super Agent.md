# Super Agent

## 题目描述

在 Potatoland 有一个非常秘密的基地，那里按照特殊的配方制作土豆泥。邻国 Porridgia 决定窃取这个配方并将其卖给 Pilauland。为此任务，他们多年来一直在培养特工 Pearlo。最终，Pearlo 学会了所有间谍的秘密，潜入了 Potatoland 的领土，并到达了秘密基地。

现在他正站在入口处，但要进入基地，他需要通过一个组合锁。一分钟前，一名工人在终端上输入了密码并打开了门。该终端是一个 $3 \times 3$ 的数字键盘，数字从 $1$ 到 $9$。

Pearlo 知道密码由不同的数字组成，并且很可能关于终端的中心按钮对称。他有一个热感应器，可以检测到工人按下了哪些数字。现在他想检查工人输入的密码是否关于终端的中心按钮对称。如果是这样，这将帮助 Pearlo 减少可能的密码组合数量。

## 说明/提示

如果你不熟悉「中心对称」这个术语，可以参考 http://en.wikipedia.org/wiki/Central\_symmetry。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
XX.
...
.XX
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
X.X
X..
...
```

### 输出

```
NO
```

# 题解

## 作者：Anguei (赞：16)

此题最简短题解。

首先要注意，题目说的是中心对称。

而且限制了矩阵大小为 $3 \times 3$.这就很简单了。

**读入三行，拼接在一个字符串中，把判断中心对称转化为判断线性对称。**

附上一分钟即可写出的 Python2 代码（0.13KB)。

```python
s = raw_input() + raw_input() + raw_input()
for i in range(5):
    if s[i] != s[8 - i]:
        print 'NO'
        exit()
print 'YES'
```

---

## 作者：ByGones (赞：7)

这题我看前面的大佬大多用的都是一位数组，但我个人认为用二维数组更好理解。

这里的对称指的是 _左上_ 和 _右下_ 对称， _左下_ 和 _右上对_ 称。

**建议根据样例自己琢磨，而不是复制题解。**

上 AC 代码

```
#include<bits/stdc++.h>
using namespace std;
char a[3][3];
int main()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			cin>>a[i][j];//输入
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(a[i][j]!=a[3-i-1][3-j-1])//看每个点和它对应的点一不一样。
			{
				cout<<"NO";
				return 0;//有一处不同就输出“NO”，结束程序。
			}
	cout<<"YES";//没有不同就输出“YES”。
    return 0;//华丽结束
}
```


---

## 作者：呵呵侠 (赞：5)

# 注意：题里面说是中心对称！
## 其实轴对称也是有做法的
### 但此处不予列举
先看一张表：

|a[0]|a[1]|a[2]|
| :----------- | :----------- | :----------- |
|a[3]|a[4]|a[5]|
|a[6]|a[7]|a[8]|
如果要它中心对称，必定要满足：

a[0]=a[8]，

a[1]=a[7]，

a[2]=a[6]，

a[3]=a[5]

这样四个条件

那么，答案就出来了

AC代码：
```
#include <iostream>
using namespace std;
int main()
{
    char a[9];
    for(int i=0;i<9;i++)
        cin>>a[i];
    if(a[0]==a[8]&&a[1]==a[7]&&a[2]==a[6]&&a[3]==a[5])
        cout<<"YES";
    else
        cout<<"NO";
    return 0;
}
```
当然，如果你觉得if一大串看起来太不顺眼，不妨看看我下面的思路

有没有发现：相加等于8的两个格子都相等，才是中心对称图形

所以，另一份AC代码：
```
#include <iostream>
using namespace std;
int main()
{
    char a[9];
    for(int i=0;i<9;i++)
        cin>>a[i];
    for(int i=0;i<9;i++)
        if(a[i]!=a[8-i]){
            cout<<"NO";
            return 0;
        }
    cout<<"YES";
    return 0;
}
```

---

## 作者：Level_Down (赞：2)

这题好水啊

直接if判断

上（~~美丽简单易懂的~~）代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[4][4];
int main()
{
	for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
				{
					cin >> a[i][j];
				}
		}
	if(a[1][1] == a[3][3] && a[2][1] == a[2][3] && a[3][1] == a[1][3] && a[1][2] == a[3][2])
		{
			cout << "YES";
			}	
			else
				{
					cout << "NO";
				}
	return 0;			
 } 
```
这样就行了啊，简单还好理解

---

## 作者：览遍千秋 (赞：2)

日常水题解


----

既然给定了3\*3，那就枚举吧。


----

可得到代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
char a[4][4];
int main()
{
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            cin>>a[i][j];
    if(a[1][1]==a[3][3]&&a[1][2]==a[3][2]&&a[1][3]==a[3][1]&&a[2][1]==a[2][3])
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
    return 0;
}
```

---

## 作者：洪荒太初 (赞：1)

# 水题
## 风某欣慰的笑了
![](https://p3.ssl.qhimgs1.com/sdr/400__/t018d1eff5452de6e1d.jpg)

没人发c++我就来发一下，
这还是我第一次发题解
。。。。
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10];//首先先定义
int main()
{
	
	for(int i=1;i<=9;i++)
	{
		cin>>s[i];//输入 
	}
	/*
      	        X s[1]X s[2]. s[3]
		. s[4]. s[5]. s[6]
		. s[7]X s[8]X s[9]
		然后找到规律 
		发现f[5]没人跟它对，所以可以直接跳过 
    */
    for(int i=1,j=9;i<=4,j>=6;i++,j--)//循环开始 
    {
    	
        if(s[i]!=s[j])//判断 
        {
        	cout<<"NO";//不一样就输出NO 
        	return 0;//跳过下面的YES 
		}
    }
    cout<<"YES";//如果是的话就输出YES 
    return 0;
}
```


---

## 作者：OdtreePrince (赞：0)

# -模拟-

三个词，$\color{blue}\texttt{输入 模拟 输出}$。

关于原点ch[2][2]对称，只需用循环解决判断，nicer!

代码来喽，DALAO勿喷！

~~~
#include<bits/stdc++.h>
using namespace std;
char ch[3][3];
int main(){
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            ch[i][j]=getchar();
            while(ch[i][j]!='X'&&ch[i][j]!='.'){
                ch[i][j]=getchar();
            }
        }
    }
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            if(ch[i][j]!=ch[4-i][4-j]){
                cout<<"NO";
                return 0;
            }
        }
    }
    cout<<"YES";
    return 0;
}~~~

---

## 作者：AntaresQAQ (赞：0)

题目给了3\*3的矩阵，要求判断是否中心对称。


因为矩阵是由“.”和“x”组成的字符串，所以读取时一次读一整行。


然后判断每个点和它中心对称的点是否相同，如果不匹配则不是中心对称图形，检查完全部匹配即为中心对称图形。


```cpp
#include<bits/stdc++.h>
using namespace std;

char graph[4][5];//注意多开一个给换行符 

int main()
{
    for(int i=1;i<=3;i++)
        cin>>graph[i]+1;//读入字符串，字符串从第1位开始用 
    for(int i=1;i<=3;i++)//循环检查 
        for(int j=1;j<=3;j++)
            if(graph[i][j]!=graph[4-i][4-j])//判断当前点和以[2][2]中心对称点是否相同 
            {
                puts("NO");//找到不符后退出程序 
                return 0;
            }
    puts("YES");//未找到不符 
    return 0;
}
```

---

