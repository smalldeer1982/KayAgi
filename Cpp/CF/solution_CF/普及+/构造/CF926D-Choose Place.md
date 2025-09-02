# Choose Place

## 题目描述

A classroom in a school has six rows with $ 3 $ desks in each row. Two people can use the same desk: one sitting on the left and one sitting on the right.

Some places are already occupied, and some places are vacant. Petya has just entered the class and wants to occupy the most convenient place. The conveniences of the places are shown on the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF926D/a082c4bc1c1ccaad840bb7d19543d2ab2a60cd65.png)Here, the desks in the top row are the closest to the blackboard, while the desks in the bottom row are the furthest from the blackboard.

You are given a plan of the class, where '\*' denotes an occupied place, '.' denotes a vacant place, and the aisles are denoted by '-'.

Find any of the most convenient vacant places for Petya.

## 说明/提示

In the first example the maximum convenience is $ 3 $ .

In the second example the maximum convenience is $ 2 $ .

In the third example the maximum convenience is $ 4 $ .

## 样例 #1

### 输入

```
..-**-..
..-**-..
..-..-..
..-..-..
..-..-..
..-..-..
```

### 输出

```
..-**-..
..-**-..
..-..-..
..-P.-..
..-..-..
..-..-..
```

## 样例 #2

### 输入

```
**-**-**
**-**-**
..-**-.*
**-**-**
..-..-..
..-**-..
```

### 输出

```
**-**-**
**-**-**
..-**-.*
**-**-**
..-P.-..
..-**-..
```

## 样例 #3

### 输入

```
**-**-*.
*.-*.-**
**-**-**
**-**-**
..-..-..
..-**-..
```

### 输出

```
**-**-*.
*.-*P-**
**-**-**
**-**-**
..-..-..
..-**-..
```

# 题解

## 作者：LEle0309 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF926D)

#### 题目大意：

建议撤下原翻译（**教师**？？？）。

有一个 $ 6 \times 8 $ 的教室，其中有 `*` 表示被占用的位置，`.` 表示空位置（只有这个才能选），`-` 表示过道。每个位置方便值如图。现在求方便值值最大的座位。

#### 题目分析：

模拟~~水~~题。

弄一个表，表中记录每一个位置的方便值。

遍历这个教室，枚举所有是 `.` 的座位，并更新最大值即可。

每次更新最大值，就记录一次座位坐标，最后输出答案。

```cpp
#include<iostream>
using namespace std;
const int maxn=1e1+3;
char a[maxn][maxn];int maxi,maxj,maxx=-1;
int conv[maxn][maxn]=
{
{0},
{0,3,3,0,4,4,0,3,3},
{0,3,3,0,4,4,0,3,3},
{0,2,2,0,3,3,0,2,2},
{0,2,2,0,3,3,0,2,2},
{0,1,1,0,2,2,0,1,1},
{0,1,1,0,2,2,0,1,1},
};//方便值，中间两列0表示过道
int main()
{
	for(int i=1;i<=6;i++)
		for(int j=1;j<=8;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='.'&&conv[i][j]>maxx)//枚举所有是.的座位
			{
				maxi=i;//更新最大值的横坐标
				maxj=j;//更新最大值的横坐标
				maxx=conv[i][j];//更新最大方便值
			}	
		}
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=8;j++)
			if(i==maxi&&j==maxj)cout<<'P';//最大的座位输出P
			else cout<<a[i][j];//否则跟原来一样
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：MarSer020 (赞：1)

怎么这都能评绿，建议评级：普及-。

$\Large\text{Solution}$

一眼丁真，鉴定为：语法练习题。

把位置按收益从大到小枚举即可，由于教室太小了，所以很智障。

$\Large\text{Code}$

由于这个 shaber 不会循环，被 [$\texttt{\color{black}S\color{red}unnyYuan}$](/user/520333) 吊打了。

```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[15][15];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(int i=1;i<=6;i++)
        for(int j=1;j<=8;j++)
            cin>>mp[i][j];
    if(mp[1][4]=='.')
        mp[1][4]='P';
    else if(mp[1][5]=='.')
        mp[1][5]='P';
    else if(mp[2][4]=='.')
        mp[2][4]='P';
    else if(mp[2][5]=='.')
        mp[2][5]='P';
    else if(mp[1][1]=='.')
        mp[1][1]='P';
    else if(mp[1][2]=='.')
        mp[1][2]='P';
    else if(mp[1][7]=='.')
        mp[1][7]='P';
    else if(mp[1][8]=='.')
        mp[1][8]='P';
    else if(mp[2][1]=='.')
        mp[2][1]='P';
    else if(mp[2][2]=='.')
        mp[2][2]='P';
    else if(mp[2][7]=='.')
        mp[2][7]='P';
    else if(mp[2][8]=='.')
        mp[2][8]='P';
    else if(mp[3][4]=='.')
        mp[3][4]='P';
    else if(mp[3][5]=='.')
        mp[3][5]='P';
    else if(mp[4][4]=='.')
        mp[4][4]='P';
    else if(mp[4][5]=='.')
        mp[4][5]='P';
    else if(mp[3][1]=='.')
        mp[3][1]='P';
    else if(mp[3][2]=='.')
        mp[3][2]='P';
    else if(mp[3][7]=='.')
        mp[3][7]='P';
    else if(mp[3][8]=='.')
        mp[3][8]='P';
    else if(mp[4][1]=='.')
        mp[4][1]='P';
    else if(mp[4][2]=='.')
        mp[4][2]='P';
    else if(mp[4][7]=='.')
        mp[4][7]='P';
    else if(mp[4][8]=='.')
        mp[4][8]='P';
    else if(mp[5][4]=='.')
        mp[5][4]='P';
    else if(mp[5][5]=='.')
        mp[5][5]='P';
    else if(mp[6][4]=='.')
        mp[6][4]='P';
    else if(mp[6][5]=='.')
        mp[6][5]='P';
    else if(mp[5][1]=='.')
        mp[5][1]='P';
    else if(mp[5][2]=='.')
        mp[5][2]='P';
    else if(mp[5][7]=='.')
        mp[5][7]='P';
    else if(mp[5][8]=='.')
        mp[5][8]='P';
    else if(mp[6][1]=='.')
        mp[6][1]='P';
    else if(mp[6][2]=='.')
        mp[6][2]='P';
    else if(mp[6][7]=='.')
        mp[6][7]='P';
    else if(mp[6][8]=='.')
        mp[6][8]='P';
    for(int i=1;i<=6;i++){
        for(int j=1;j<=8;j++)
            cout<<mp[i][j];
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：Fur_Zes (赞：0)

这是一道简单的模拟题。

### 题目翻译：
给你一个大小为 $6\times8$ 的网格，由三种字符组成，分别是
```.```，```-```，```*```。这个网格的每个格子还对应着一个权值：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF926D/a082c4bc1c1ccaad840bb7d19543d2ab2a60cd65.png)

现在要你求出网格里字符为```.```中权值最大的那个，并把原位置替换成```P```，最后输出整个网格。

### 题目分析：
我们可以输入一个 char 类型的字符数组 $c$ 来储存网格，定义一个 int 类型的 $a$ 数组来储存权值，定义 $maxs$ 来存储权值的最大值，并用 $maxx,maxy$ 来记录下标。

我们接下来只需要枚举 $c_{i,j}$ 是否为```.```，如果是，我们就将 $a_{i,j}$ 和 $maxs$ 对比大小，并同时更新 $maxx,maxy$。

### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[10][10];
int a[10][10]={	{3,3,0,4,4,0,3,3},
				{3,3,0,4,4,0,3,3},
				{2,2,0,3,3,0,2,2},
				{2,2,0,3,3,0,2,2},
				{1,1,0,2,2,0,1,1},
				{1,1,0,2,2,0,1,1} };
int maxs,maxx,maxy;
int main()
{
	for(int i=0;i<6;i++)
	for(int j=0;j<8;j++)
	{
		cin>>c[i][j];
		if(c[i][j]=='.')
		{
			if(a[i][j]>maxs)
			maxs=a[i][j],maxx=i,maxy=j;
		}
	}
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(i==maxx&&j==maxy) cout<<"P";
			else cout<<c[i][j];
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
比较小型的模拟和循环，甚至就是一个查询最大值的过程，而每一个位置的贡献都已经算好了且不变。
## 分析。
一个只有 $6\times8$ 的网格，显然只要遍历一遍整个网格，去掉坐上人的，在去掉过道，剩下的空位置中，找到贡献值最大的坐上去就行了。

具体来说，我们输入整个网格，然后把那张题目中的座位贡献值表存到一个不变量中，遍历整个网格，找到既不是过道 ```-``` 也不是坐人 ```*``` 的地方，然后查询在当前合法位置 $a_{i,j}$ 对应在前面的座位贡献值表中的对应贡献，找到最大的，在把它修改成 ```P``` 表示坐在这里，然后其它的位置直接自行输出即可。显然这道题的答案位置可能不仅仅只有一个。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int ans;
int ans_i,ans_j,sum;
char ch[10][10];
int wokl=0;
int val[6][8]={
	3,3,0,4,4,0,3,3,
	3,3,0,4,4,0,3,3,
	2,2,0,3,3,0,2,2,
	2,2,0,3,3,0,2,2,
	1,1,0,2,2,0,1,1,
	1,1,0,2,2,0,1,1,
};//那个座位贡献值表存下来，0表示过道。 
int main(){
	for(int i=0;i<6;i++){
		for (int j=0;j<8;j++){
		    cin>>ch[i][j];
		}
	}
	for(int i=0;i<6;i++){
	    for(int j=0;j<8;j++){
			if(ch[i][j]=='.'){//可以坐人。 
				if(val[i][j]>sum){
				    ans_i=i;
				    ans_j=j;
				    sum=val[i][j];
				}
				//如果当前的位置贡献更大，那么更新坐标。 
			}
		}
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<8;j++){
			if(ans_i==i&&ans_j==j){
				cout<<"P";
			}//找到位置并修改。 
			else{
				cout<<ch[i][j];
			}
		}
		cout<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：wenlebo (赞：0)

题目大意：给出一间 $6\times 8$ 的教室且 `*` 表示被占用的位置，`.` 表示空位置，`-` 表示过道，求出有这最大方便度的空位置并按样例输出，其中方便度与位置的关系如下图（建议修改翻译，将该图放到下方，更容易看见）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF926D/a082c4bc1c1ccaad840bb7d19543d2ab2a60cd65.png)

由于教室十分的小，所以没有超时的可能！只需枚举每一个位置查看能否坐下且更方便即可。

上代码：

```
#include <bits/stdc++.h>
using namespace std;
int ans,ansi,ansj;
string o[6];
string q[6]{	//用这种方式可以方便的存储方便度
	"33044033",//修改：上一次少打了一个字符
	"33044033",
	"22033022",
	"22033022",
	"11022011",
	"11022011"
};
int main(){
	for(int i=0;i<6;i++){
		cin>>o[i];
	}
	for(int i=0;i<6;i++){    //枚举位置
		for(int j=0;j<8;j++){
			if(o[i][j]=='.'&&(q[i][j]-'0'>ans)){ //过道和已经坐人的不可以坐
				ans=q[i][j]-'0';
				ansi=i;
				ansj=j;
			}
		}
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<8;j++){
			if(ansi==i&&ansj==j){//输出
				cout<<"P";
			}else{
				cout<<o[i][j];
			}
		}
		cout<<"\n";
	}
	return 0;
}

```


---

## 作者：　　　吾皇 (赞：0)

~~虽然使用语言不能重复，但还是用C语言水了过去~~ 发一波c++的题解
### 题目分析
```
教室是6*8的，每个位置对应一个数字，要使petya坐在一个数字最大的位置（输出一种解即可），那么我们就可以定义一个maxx表示当前能量的最大值，用二维数组a存下每个点的能量，再暴力扫过去，如果该点能量小于maxx改变maxx的值，在输出时只要判断该点能不能坐人，能量值是否为maxx，是否输出过P即可
```
### 代码
```
#include<iostream>
using namespace std;
string mp[6];//这里可以用字符串也可以用char二维数组
int p=1,maxx,a[6][8]={{3,3,0,4,4,0,3,3},{3,3,0,4,4,0,3,3},{2,2,0,3,3,0,2,2},{2,2,0,3,3,0,2,2},{1,1,0,2,2,0,1,1},{1,1,0,2,2,0,1,1}};//p=1代表一开始没有输出过'P',用a直接存入各点能量
int main() {
	for (int i=0;i<6;i++)	cin>>mp[i];//读入教室
	for (int i=0;i< 6;i++)
		for (int j=0;j<8;j++)
			if (mp[i][j]=='.')
				maxx=max(maxx,a[i][j]);//如果当地有空位那么就比较
	for (int i=0;i<6;i++){
		for (int j=0;j<8;j++){
		    if (mp[i][j]=='.'&&a[i][j]==maxx){//见上述分析所说
				if(p){
					p=0;//p=0代表已经输出过了，不必在输出
					cout<<'P';
					continue;//避免以下的操作直接跳到下一步
				}
		    }
		    cout<<mp[i][j];//如果一切正常输出该点即可
		}
		cout<<endl;//每行输完要换行
	}
	return 0;
}
```
### 改进
- 由于前面比后面大，中间比两边大，所以可以用类似二分的方式从最前面的中间往两边搜，只要搜到一个就肯定是最大值，再输出即可

---

