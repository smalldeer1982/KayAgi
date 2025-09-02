# Little Elephant and Chess

## 题目描述

The Little Elephant loves chess very much.

One day the Little Elephant and his friend decided to play chess. They've got the chess pieces but the board is a problem. They've got an $ 8×8 $ checkered board, each square is painted either black or white. The Little Elephant and his friend know that a proper chessboard doesn't have any side-adjacent cells with the same color and the upper left cell is white. To play chess, they want to make the board they have a proper chessboard. For that the friends can choose any row of the board and cyclically shift the cells of the chosen row, that is, put the last (rightmost) square on the first place in the row and shift the others one position to the right. You can run the described operation multiple times (or not run it at all).

For example, if the first line of the board looks like that "BBBBBBWW" (the white cells of the line are marked with character "W", the black cells are marked with character "B"), then after one cyclic shift it will look like that "WBBBBBBW".

Help the Little Elephant and his friend to find out whether they can use any number of the described operations to turn the board they have into a proper chessboard.

## 说明/提示

In the first sample you should shift the following lines one position to the right: the 3-rd, the 6-th, the 7-th and the 8-th.

In the second sample there is no way you can achieve the goal.

## 样例 #1

### 输入

```
WBWBWBWB
BWBWBWBW
BWBWBWBW
BWBWBWBW
WBWBWBWB
WBWBWBWB
BWBWBWBW
WBWBWBWB
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
WBWBWBWB
WBWBWBWB
BBWBWWWB
BWBWBWBW
BWBWBWBW
BWBWBWWW
BWBWBWBW
BWBWBWBW
```

### 输出

```
NO
```

# 题解

## 作者：LongDouble (赞：2)

##### **题目大意：**

棋盘的每个格子有两种颜色：`B`（黑）和 `W`（白）。

输入一个 $8\times 8$ 的棋盘。

可以将这个棋盘的任意一行的最后一个格子放在该行的第一个位置，其他格子往右移一个位置。

如：`BBBBBBWW` 可以变成 `WBBBBBBW`。

求输入的棋盘能否变成：

```
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
```
如果能，输出 `YES`，否则输出 `NO`。

##### **解题思路：**

我们仔细观察，不难发现，目标棋盘的每一行只有 `WBWBWBWB` 和 `BWBWBWBW`。

再分析：

能变成 `WBWBWBWB` 的只有 `BWBWBWBW`；

能变成 `BWBWBWBW` 的只有 `WBWBWBWB`。

也就是说，如果这个棋盘能变成目标棋盘，那么这个棋盘的每一行必须得是`WBWBWBWB` 或 `BWBWBWBW`。

所以，直接判断每一行是不是 `WBWBWBWB` 或 `BWBWBWBW` 即可。

##### **代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
string a[10];

int main()
{
	for (int i = 1; i <= 8; i++)
	{
		cin >> a[i];
		if (a[i] != "WBWBWBWB" && a[i] != "BWBWBWBW")
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}
```


---

## 作者：ruruo (赞：0)

# CF259A 题解

题意：给你一个 $8 × 8$ 的棋盘，每个格子为黑（ $B$ ）或白（ $W$ ），问你能否将棋盘变成黑白相间的，可以输出 "YES", 否则输出 "NO"。

因为 WBWBWBWB 经过一次变形变成 BWBWBWBW。

BWBWBWBW 经过一次变形变成 WBWBWBWB。

所以只有 BWBWBWBW 和 WBWBWBWB 两种情况符合要求。

------------------------------

AC code:

```cpp
#include<iostream>
using namespace std;

string s; //用来记录每一行的棋盘颜色

int main() {
    for(int i = 1; i <= 8; i++) { //一共8行
        getline(cin, s); //输入
        if(s != "WBWBWBWB" && s != "BWBWBWBW") { 
            cout << "NO" << endl; //如果不满足，直接输出 "NO" 并 return 0
            return 0;
        }
    }
    cout << "YES" << endl; //如果能成功跳出循环那说明符合要求 输出 "YES"
    return 0;
}
```


最后祝各位 CSP-S/J rp++ !

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF259A)

# 思路：

既然要把整个棋盘变成这个样子：

```
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
```

那么你会发现：

B 与 W 是互相嵌套的

所以不管你怎么移动每一行棋盘，只要不是以下两种情况，那就不能组成需要的棋盘

```
BWBWBWBW 或 WBWBWBWB
```

所以只要每一行逐个判断是否与两种字符串的其中一个相同就可以了

# AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
string a[9];//棋盘的 8 行 
int main(){
	for(int i=1;i<=8;i++){//逐行输入，更加方便 
		cin>>a[i];//输入 
		if(a[i]!="WBWBWBWB"&&a[i]!="BWBWBWBW"){//如果当前行与需要的两个字符串都不相同 
			puts("NO");//输出 
			return 0;//直接结束程序 
		}
	}
	puts("YES");//每一行都判断完，没有结束程序则合法，输出 
	return 0;
}
```


---

## 作者：hensier (赞：0)

这道题可以用$STL$之$queue$（队列）进行操作。

用$STL$ $queue$的好处是在于它便于操作，而且容量极大。本次需要用到的$queue$操作：

|函数名称|类型|意义|示例|
|-|-|-|-|-|
|$q.push()$|$void$|把元素入队|$q.push(1)$就是把$1$这个元素入队|
|$q.pop()$|$void$|把顶部元素弹出|如果现在$q$顶部元素$8$（就是最先入队的）弹出，那么$8$就出队，不再是队列的元素|
|$q.empty()$|$bool$|判断队列是否为空（没有元素）|如果队列为空就返回$1$，否则返回$0$|
|$q.front()$|队列类型|返回队列顶部元素|假设现在队列为$\{1,3,5,13\}$（$1$是最先进入队列的），则返回$1$|

这个了解了，我们就可以开始模拟。

$WWBBWBBW$假设这个是初始的字符串。

开始右移：

|当前字符串|操作次数|
|-|-|
|$WWBBWBBW$|$0$|
|$WWWBBWBB$|$1$|
|$BWWWBBWB$|$2$|
|$BBWWWBBW$|$3$|
|$WBBWWWBB$|$4$|
|$BWBBWWWB$|$5$|
|$BBWBBWWW$|$6$|
|$WBBWBBWW$|$7$|
|$WWBBWBBW$|$8$|

我们发现，无论如何都无法满足条件，因此返回$0$。

根据上述的模拟方式，我们得到代码：

```cpp
/*耗时:906ms,内存:8.00kb,长度:794b*/
#include<bits/stdc++.h>//万能头文件
#define f()for(int i=0;i<8;i++)
#define F()for(int j=0;j<8;j++)//宏定义两个循环
using namespace std;
char c[8][8];//处理输入
queue<char>q;//定义char队列
string s[]={"WBWBWBWB","BWBWBWBW"},t[]={"NO","YES"};//"WBWBWBWB"和"BWBWBWBW"是唯一的两种情况
bool check(queue<char>a,string s)//判断队列里的内容排列起来是否合适
{
    string x="";
    while(!a.empty())
    {
        x+=a.front();
        a.pop();
    }
    return x==s;
}
void clear(queue<char>&a)//清空队列
{
    while(!a.empty())a.pop();
}
bool func(string a[],bool b)
{
    f()//(0,8)循环
    {
        clear(q);//清空队列
        F()q.push(c[i][j]);//把元素推入
        int k=0;//最多可以右移8次，然后再右移就循环了，所以定义一个k=0
        while(!check(q,a[b]))//如果队列内容不合适就继续右移
        {
            q.push(q.front());//右移操作——先推入顶部元素，再弹出顶部
            q.pop();
            k++;//计数器加1
            if(k==8)break;//到了8就直接跳出循环
        }
        if(!check(q,a[b]))return 0;//只要有一个不同就返回0
        b=!b;//每一次更换
    }
    return 1;
}
int main()
{
    f()F()cin>>c[i][j];
    cout<<t[func(s,0)||func(s,1)];//直接输出YES或NO
}
```

然而，这道题目还有一道更直接、更简单的方法。

```cpp
/*耗时:964ms,内存:8.00kb,长度:240b*/
#include<iostream>
using namespace std;
string s;//字符串保存8个字符
int n=8;//循环次数
int main()
{
    while(n--)//while(n--){}等同于循环8次
    {
        cin>>s;//输入字符串
        if(s!="WBWBWBWB"&&s!="BWBWBWBW")//只要这行的棋格不是相邻不同的话，就直接输出NO并结束程序
        {
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES";//输出YES
}
```

通过这道题，我们可以发现，有的时候直接的方法的效率不一定是最高的——虽然容易理解。~~暴力非常容易看懂~~

对于同一道题，我们不妨用多种方法去芜存菁。

---

