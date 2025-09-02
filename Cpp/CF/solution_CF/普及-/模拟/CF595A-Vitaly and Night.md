# Vitaly and Night

## 题目描述

One day Vitaly was going home late at night and wondering: how many people aren't sleeping at that moment? To estimate, Vitaly decided to look which windows are lit in the house he was passing by at that moment.

Vitaly sees a building of $ n $ floors and $ 2·m $ windows on each floor. On each floor there are $ m $ flats numbered from $ 1 $ to $ m $ , and two consecutive windows correspond to each flat. If we number the windows from $ 1 $ to $ 2·m $ from left to right, then the $ j $ -th flat of the $ i $ -th floor has windows $ 2·j-1 $ and $ 2·j $ in the corresponding row of windows (as usual, floors are enumerated from the bottom). Vitaly thinks that people in the flat aren't sleeping at that moment if at least one of the windows corresponding to this flat has lights on.

Given the information about the windows of the given house, your task is to calculate the number of flats where, according to Vitaly, people aren't sleeping.

## 说明/提示

In the first test case the house has two floors, two flats on each floor. That is, in total there are 4 flats. The light isn't on only on the second floor in the left flat. That is, in both rooms of the flat the light is off.

In the second test case the house has one floor and the first floor has three flats. The light is on in the leftmost flat (in both windows) and in the middle flat (in one window). In the right flat the light is off.

## 样例 #1

### 输入

```
2 2
0 0 0 1
1 0 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 3
1 1 0 1 0 0
```

### 输出

```
2
```

# 题解

## 作者：MZY666 (赞：7)

[原题传送门](https://www.luogu.com.cn/problem/CF595A)。[在我的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-cf595a)。

### 【目录】

- 目录
- 题意概括
- 思路
- 代码实现+注释

### 【题意概括】

输入 $n$，$m$，表示这栋楼有 $n$ 层，每层有 $m$ 户。

每户有两扇窗，$0$ 代表窗没亮着，$1$ 代表窗亮着。

接下来输入**每一扇**窗户的状态。

要求输出有**多少户**的窗是亮着的。

### 【思路】

只要一户人家有一扇窗户是亮着的就行了。也就是判断一下左右两窗户之一有没有亮的，若有则答案$+1$。

可以用以下代码实现上述判断：

```cpp
if(left||right)ans++;
```

注：由于if语句中true的判断是改数是否为非零，因此不需要写成```if(left==1||right==1)```。

是时候上代码了！

~~先吐槽一下：窝评测等了好久（好像到现在都还没好？），果然还是洛谷好。~~

### 【代码实现+注释】

```cpp
#include<bits/stdc++.h>//万能头文件好
using namespace std;
#define ll long long//个人习惯，其实本题用int就够了
int main(){
	ll n,m,i,j,ans=0,left,right;//先全部定义好
	//i,j为循环变量,ans用于储存答案，注意初始化为0
	//left、right是用于输入左右窗的状态，无需用数组
	scanf("%lld%lld",&n,&m);//输入n、m，注意long long要用%lld
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			scanf("%lld%lld",&left,&right);//输入左右窗状态
			if(left||right)ans++;//这一步前面有特别说明
		}
	}
	printf("%lld\n",ans);//输出答案，换行是个好习惯
	return 0;//over!
}
```

完结撒花~（疯狂暗示AWA

---

## 作者：伟大的王夫子 (赞：2)

可以到[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)里食用

题目的意思，有一个一栋楼有$n$层，每层有$m$户，让你统计有那几户至少有一个窗户是亮的。

那么，应该有$n \times m$户人家，依次读入，进行判断即可。
注意一些细节

```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, ans;
int main() {
	int n, m;
	cin >> n >> m;//读入n,m的值 
	for (register int i = 1; i <= n * m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		//有任意一个窗户开着就要算进去 
		ans += x || y;//压行，等价于if (x || y) ++ans; 
	}
	cout << ans;
} 
```

---

## 作者：BotDand (赞：1)

# Problems
一栋楼有$n$层，每层有$m$户，每户有两扇窗，$0$ 代表窗没亮着，$1$ 代表窗亮着，求一共有多少户的窗亮着。
# Answer
因为题目中给出了条件：**每户有两扇窗**。

所以可以看相邻的窗户，如果有一盏及以上的灯是亮着的，说明这户人家是开着灯的。
# Code
Pascal代码，思路已经讲的很清楚了，注释就不加了QAQ。
```pascal
var
  n,m,i,j,a,b,s:longint;
begin
  readln(n,m);//读入n
  for i:=1 to n do
    begin
      for j:=1 to m do
        begin
          read(a,b);
          if (a=1) or (b=1) then inc(s);
        end;
      readln;
    end;
  writeln(s);
end.
```

---

## 作者：k3v1n070828 (赞：1)

### 本题二维数组+模拟即可

需要二维数组$a$来存储灯的开关情况。

∵数据范围是$1≤n,m≤100$

又∵每户有两个窗户

∴数据范围要开到$a[100+10][100×2+10]$(横排200)

然后枚举求解即可

### 思路简单，上代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;//楼层和每层户数
int a[110][210];//存储开关灯情况的数组a
int main(){
	int cnt=0;//答案（计数器），记录开灯的门户总数
	scanf("%d%d",&n,&m);//输入
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m*2;j++)
			scanf("%d",&a[i][j]);//读入数组
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j*2-1]==1||a[i][j*2]==1)//如果相邻两个屋子有开灯情况
				cnt++;//计数器++
	printf("%d\n",cnt);//输出答案
	return 0;//结束程序
}
```

Ps：CF的橙题适合来练习代码熟练度,十分适合普及组选手来做

Bye~~


---

## 作者：Franka (赞：1)

没有Pascal的题解？那我就来水一发。

* 题目大意

一栋楼有**n**层，每层有**m**户，**每户有两扇窗**，**0代表窗没亮着，1代表窗亮着**，让你**求一共有多少户的窗亮着**。

### 首先要知道，亮着一扇或两扇就算这户的窗是亮着的。

那么这题就迎刃而解了

```
var n,m,i,j,x,y,s:integer;//定义
begin
 read(n,m);//读入n和m
  for i:=1 to n do//n层
   begin
    for j:=1 to m do//m户
     begin
      read(x,y);//读入两扇窗的情况
      if(a=1)or(b=1)then s:=s+1;//如果有一个就将s加1
     end;
    readln;
   end;
 write(s);//输出
end.
```


---

## 作者：ZJKAW (赞：1)

这题的 n 和 m 其实没有用，只要两个两个读入就可以了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,a,b;
	 ios::sync_with_stdio(0);cin.tie(0);//输入加快 
	 cin>>n>>m;
    int ans=0;
      while(cin>>a>>b)
      	if(a==1||b==1)ans++;
      	   cout<<ans<<endl;
      	return 0; 
}
```


---

## 作者：MrFish (赞：1)

题目描述：
有一个n层，每层m户的公寓，每户有两扇窗户，请你统计有几户至少有一个窗户是亮的。



```cpp
#include<iostream>

using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	int a,b;
	int ans=0;
	for(int i=0;i<n*m;i++)
	{
		cin>>a>>b;
		if((a==1&&b==1)||(a==1&&b==0)||(a==0&&b==1))
		{
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：sinsop90 (赞：0)

看了某些大佬的各式解法,我感觉我太蒟蒻了

总而言之就是每家每户去判断,每家有2个窗,一个窗开着就行了

所以......
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,ans=0;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		int x,y;
		for(int j=1;j<=m;j++){
			scanf("%d %d",&x,&y);
			if(x==1 || y==1){//一个窗开着就ans++
				ans++;
			}
		}
	}
	printf("%d",ans);
}
```


---

## 作者：C171517 (赞：0)

例如：

$1$ $0$ $1$ $1$


我们看，每户左右两个窗子，那么我们可以用一个变量检测每户一边的窗子。我们设$i$检测每户左边的窗子，那么它将遇到的是$1$和$1$ ；设$j$检测每户右边的窗子，同理，它将遇到的是$0$和$1$ 。这样，$i$和$j$分工协作，每次共同检测一户。每次只要有一个检测到为$1$，储存总和的变量就可以加$1$。

这道题我是按照输入、解析、输出的步骤来的，没想过把输入和解析放在一块，因此有了这样的思路。（以前没用过二维数组，这道题想用一下。）代码如下。
```cpp
#include<bits/stdc++.h>            //万能头文件
using namespace std;               
int main(){
    int n,m,i=0,j=1,e,sum=0,b,c;   //定义变量，i检测左边窗户，j检测右边窗户
    cin>>n>>m;                     //输入n和m
    int a[n][2*m];                 //定义装窗户数据的二维数组
    for(c=0;c<=n-1;++c)            //循环输入数组
    {
        for(b=0;b<=2*m-1;b++)
        {
            cin>>a[c][b];
        }
    }
    for(e=0;e<n;++e)               //在每一层楼中分析
    {              
        while(j<=2*m-1)            //j检测完最后一个窗户时结束
        {
            if(a[e][i]==1||a[e][j]==1)sum++;//利用数组检测
            i+=2;                  //准备进入下一户
            j+=2;
        }
        i=0;                       //一层楼检测完后复位
        j=1;
    }
    cout<<sum;                     //输出结果
    return 0;                      //结束咯
}
```

第一次写题解，有误请包涵。

---

