# [ABC036B] 回転

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc036/tasks/abc036_b



# 题解

## 作者：风之城0 (赞：9)

额,这题虽然说挺水的，完全达不到普及的的难度，但连输入输出样例格式都没有，的确值得吐槽，所以我顺便发个题解加输入输出格式，供大家尽快水过，晚了就被隐藏了。

输入格式：一个数n，然后输入n*n的序列。

输出格式：这个序列顺时针旋转90度后的结果。

样例1：

输入：

3

o x o

x o x

o x o

输出：

o x o

x o x

o x o

样例2：

输入：

3

o o o

x x x

o o o

输出:

o x o

o x o

o x o

以下是代码：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{int n;
 cin>>n;
 char a[100][100];
 for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
       cin>>a[i][j];
 for(int i=0;i<n;i++)
    {for(int j=n-1;j>=0;j--)
       cout<<a[j][i];
    cout<<endl;}
}
```
祝大家尽快水过！

---

## 作者：zr太弱了 (赞：2)

本题还是比较水的，应该没有普及难度，注释放代码里了，还有，本题题面太草率了吧，连样例都没有，请管理员有空修一下
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//顺时针90度，即右转90度，题面描述中"只有X和O"这句话没有用
	long long n,i,j;
	char a[100][100];
	cin>>n;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>a[i][j];
		}
	}//正常输入 
// 	  0 1 2	      0 1 2
//	0 X O X     0 X X X
// 	1 X X X --> 1 O X O
//	2 X O X	    2 X X X
//	观察[1][0]处的"O",它的坐标由[1][0]变成了右图的[2][2]
//  观察[0][2]处的"O",它的坐标由[0][2]变成了右图的[0][0]
//	以此为例，多列举几个例子，我们能容易的知道点在矩阵中的变化规律 
//  所以核心如下：(注意位置) 
	for(i=0;i<n;i++)
	{
		for(j=n-1;j>=0;j--)
		{
			cout<<a[j][i];
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：yazzkl (赞：2)

# 提示
洛谷上没有N的数据范围。。

### 1<=N<=50(来自atcoder官网)
# 正文
### 这道题属于找规律题


因为题目要求顺时针旋转90°

我们可以想到，可能其中有隐藏的规律。

于是我们可以**观察样例**(atcoder上有)

## 实现

可以随便找个点的坐标（最好在中间），看看其旋转90°后的对应点。

发现:任意一个字符串坐标：$[i][j]$旋转90°后，

对应点坐标成了：$[j][n-1-i]$(其中n代表方阵几行几列)

# code
```
#include <stdio.h>
#define N 100
int main(void){            //突然觉得这个好方便
  char s[N][N],ans[N][N]={0}; //定义。s数组为旋转前，ans数组为旋转后
  int i,j,n;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      scanf("%c",&s[i][j]);
      if(s[i][j]!='o' && s[i][j]!='x'){
        scanf("%c",&s[i][j]);     //读入
      }
    }
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      ans[j][n-1-i]=s[i][j]; //规律在此
    }
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      printf("%c",ans[i][j]);//输出旋转后的答案
    }
    printf("\n");
  }
  return 0;
}

```
**此题告诉我们，遇到一道题，研究样例也很重要**

---

## 作者：Lithium_Chestnut (赞：1)

显然一道找规律题。

既然顺时针旋转九十度，所以双重循环中，$i$ 不用变化，重点在 $j$ 上，九十度旋转就是倒序输出，那么结果就显而易见了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[101][101];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) cin>>a[i][j];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=n;j>=1;j--) cout<<a[j][i];
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：A_Plus_Gu (赞：1)

考察内容：字符串、模拟

输入样例#1：
```
2
ox
ox
```

输出样例#1：
```
oo
xx
```

输入样例#2：
```
4
oooo
oxox
xoox
ooxo
```

输出样例#2：
```
oxoo
ooxo
xooo
oxxo
```


代码：
```
#include<iostream>
using namespace std;
char s[10001][10001];
long n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>s[i][j];
			
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=n;j>=1;j--){
			cout<<s[j][i];
			
		}
		cout<<endl;
	}
	return 0;
} 
```


---

## 作者：star_looker (赞：1)

这道题说实话还是蛮水的。

其实只要在输出上做点手脚，下标换一下就好了。

为啥？我们来分析一下：

假设输入了：

```latex
1 2 3 4
2 3 4 5
3 4 5 6
4 5 6 7
```

首先第一个数字“1”的下标：$arr[0][0]$，那么把下标交换后位置不变，翻转后的“1”还是在这个位置吗？我们可以先尝试将“1”翻转试试：

```latex
1 ? ? ?
? ? ? ?
? ? ? ?
? ? ? ?
```

我们再反转一下$arr[0][1]$：

```latex
1 ? ? ?
2 ? ? ?
? ? ? ?
? ? ? ?
```

接着翻转这一行：

```latex
1 ? ? ?
2 ? ? ?
3 ? ? ?
4 ? ? ?
```

我们最后反转一下$arr[0-3][0]$这一列：

```latex
1 2 3 4
2 ? ? ?
3 ? ? ?
4 ? ? ?
```

这确实实现了翻转的功能。那我们就方便了，只要在输出中将：

```cpp
for(int i=0;i<m;i++){
	for(int j=0;j<n;j++){
		printf("%d ",arr[i][j]); 
	}
	printf("\n"); 
} 
```

下标交换后这样：

```cpp
for(int i=0;i<m;i++){
	for(int j=0;j<n;j++){
		printf("%d ",arr[j][i]); 
	}
	printf("\n"); 
} 
```

中间不做任何处理就AK了。

CODE（现打的）：
```cpp
#include<bits/stdc++.h>//万能头文件  
using namespace std;//命名空间  
int n,m,arr[100][100];//生成长和宽  数组 
int main(){//主函数 —程序的开始  
    scanf("%d%d",&n,&m);//输入  
    for(int i=0;i<n;i++)//循环输入行  
        for(int j=0;j<m;j++)//循环输入列 
            scanf("%d",&arr[i][j]);                       
    for(int i=0;i<m;i++){//循环 
        for(int j=0;j<n;j++){
		    printf("%d ",arr[j][i]);//输出  
	      }
		printf("\n");//输出换行不要忘  
	 }                  
	 return 0;//return 0 —程序的消逝 
}
```
请看懂了后抄袭（

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

额······其实这道题出的有点草率啊，不仅样例没有，连n的范围都没有。但其实这道题难度的确不难，我们自己列数据，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/8q8xtnua.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们在找一找规律，就不难发现，代码这样敲：

```cpp
for(int i=1; i<=n; i++)
	for(int j=n; j>=1; j--)
  		cout<<a[j][i];
```

当然，上面的代码还要再加上换行，我只是说明如何将矩阵“旋转”90度。完整代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
int n;
char a[100][100];
int main()
{
cin>>n;
for(int i=1; i<=n; i++)
	for(int j=1; j<=n; j++)
		cin>>a[i][j];
for(int i=1; i<=n; i++)
{
	for(int j=n; j>=1; j--)cout<<a[j][i];//输出
	cout<<endl;//记得换行
}
    return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：wushuang0828 (赞：0)

因为没有样例，我就用AC代码测了的几个样例

样例输入1：

5

xoxxx

oooox

xxoox

ooxoo

oxoxx

样例输出1：

ooxox

xoxoo

oxoox

xooox

xoxxx

样例输入2：

3

oox

xox

oxx

样例输出2:

oxo

xoo

xxx

下面是AC代码：
```pascal
var
 n,i,j:longint;
 a:array[0..101,0..101] of char;
begin
 readln(n);//输入n
 for i:=1 to n do
  begin
   for j:=1 to n do
    read(a[i,j]);//输入n*n的矩阵
   readln;
  end;
 for i:=1 to n do
  begin
   for j:=n downto 1 do//规律
    write(a[j,i]);//输出
   writeln;//记得换行
  end;
end.
```

---

