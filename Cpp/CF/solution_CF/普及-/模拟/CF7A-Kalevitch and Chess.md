# Kalevitch and Chess

## 题目描述

A famous Berland's painter Kalevitch likes to shock the public. One of his last obsessions is chess. For more than a thousand years people have been playing this old game on uninteresting, monotonous boards. Kalevitch decided to put an end to this tradition and to introduce a new attitude to chessboards.

As before, the chessboard is a square-checkered board with the squares arranged in a $ 8×8 $ grid, each square is painted black or white. Kalevitch suggests that chessboards should be painted in the following manner: there should be chosen a horizontal or a vertical line of 8 squares (i.e. a row or a column), and painted black. Initially the whole chessboard is white, and it can be painted in the above described way one or more times. It is allowed to paint a square many times, but after the first time it does not change its colour any more and remains black. Kalevitch paints chessboards neatly, and it is impossible to judge by an individual square if it was painted with a vertical or a horizontal stroke.

Kalevitch hopes that such chessboards will gain popularity, and he will be commissioned to paint chessboards, which will help him ensure a comfortable old age. The clients will inform him what chessboard they want to have, and the painter will paint a white chessboard meeting the client's requirements.

It goes without saying that in such business one should economize on everything — for each commission he wants to know the minimum amount of strokes that he has to paint to fulfill the client's needs. You are asked to help Kalevitch with this task.

## 样例 #1

### 输入

```
WWWBWWBW
BBBBBBBB
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
```

### 输出

```
3
```

## 样例 #2

### 输入

```
WWWWWWWW
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
```

### 输出

```
1
```

# 题解

## 作者：Tune_ (赞：19)

数据不大，直接暴力~

看看哪行哪列全是B，就染哪行哪列。

但当全是B时要特判，8次

```
#include<bits/stdc++.h>
using namespace std;
char a[8][8];
int main()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            cin>>a[i][j];
    int ans=0;
    for(int i=0;i<8;i++)//行
    {
        bool f=1;
        for(int j=0;j<8;j++)
        {
            if(a[i][j]!='B')
                f=0;
        }
        if(f)
            ans++;
    }
    for(int i=0;i<8;i++)//列
    {
        bool f=1;
        for(int j=0;j<8;j++)
        {
            if(a[j][i]!='B')
                f=0;
        }
        if(f)
            ans++;
    }
    if(ans==16)//特判
        ans=8;
    cout<<ans;
    return 0;//搞定~~~
}
```

求点赞~

---

## 作者：char32_t (赞：5)

# 题解 CF7A 【Kalevitch and Chess】
------------
统计最少需要的操作的行或者列的个数，按照贪心的思想，如果某行全部为B，肯定会操作这一行，因为如果将一行的B涂为W的收益最大（即涂同时包含B和W的选择比涂全为B的选择劣）
Code：
```cpp
#include<cstdio>
#include<iostream>
int main() {
	char s[10];//模拟棋盘 
	int a=0, b=10;
	for(int i=0; i<8; i++) {
		scanf("%s", s);//输入棋盘的每一行 
		int count=0;//计数器 
		for(int j=0; j<8; j++)
			if(s[j]=='B') count++;
		if(count==8) a++;//如果全为B，就涂 
		b=std::min(b, count);
	}
	int ans=a+b;
	if(a==8) ans=8;//如果全为B，则只需涂8次 
	printf("%d", ans);//输出结果 
	return 0;
}
```

---

## 作者：呵呵侠 (赞：2)

经典贪心题目，如果某行全为B，那么必然要操作此行，列同理

我是用字符类型二维数组做的题：
```cpp
#include <iostream>
using namespace std;
char a[8][8];
int main()
{
    for(int i = 0; i <= 7; i++)
        for(int j = 0; j <= 7; j++)
            cin >> a[i][j];//输入
    int ans = 0;
    for(int i = 0; i <= 7; i++)//判断行
    {
        bool flag = true;//判断一行是不是都是B的判断器，赋值为true
        for(int j = 0; j <= 7; j++)
        {
            if(a[i][j] != 'B')//如果不是B
                flag = false;//判断器值为false
        }
        if(flag == true)//如果这一行都是B
            ans++;//染色次数增加1
    }
    for(int i = 0; i <= 7; i++)//判断列
    {
        bool flag = true;//判断一列是不是都是B的判断器，赋值为true
        for(int j = 0; j <= 7; j++)
        {
            if(a[j][i] != 'B')//如果不是B
                flag = false;//判断器值为false
        }
        if(flag == true)//如果这一列都是B
            ans++;//染色次数增加1
    }
    if(ans == 16) //特判，如果8行8列都是B，那么其实只要8次操作就够了
        ans = 8;
    cout << ans;
    return 0;
}
```

---

## 作者：_Legacy (赞：1)

#### 分析
1. 根据题意只能一整行或一整列地涂黑，所以只要判断是否一整行/列都是B，若符合条件 ```ans++``` 。
1. 特判：若全部都是B可能出现 ```(ans==16)``` 的情况，但其实只要8次就可以了。
#### 上代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	char a[9][9],b[9];
	int t,ans=0;
	for(int i=0;i<8;i++){
		cin >> b;
		//因为它中间没有空格，所以是一整行输入的
		for(int j=0;j<8;j++){
			a[i][j]=b[j];
		}
	}
   //输入
	for(int i=0;i<8;i++){
		t=1;
		for(int j=0;j<8;j++){
			if(a[i][j]!='B'){
				t=0;
				break;
			}
		}
		if(t){
			ans++;
		} 
	}
   //一行行看
	for(int i=0;i<8;i++){
		t=1;
		for(int j=0;j<8;j++){
			if(a[j][i]!='B'){
				t=0;
				break;
			}
		}
		if(t){
			ans++;
		} 
	}
   //一列列看
	if(ans==16) ans=8;
	cout << ans;
   //特判
} 
//CF7A
```

---

