# [ARC016B] 音楽ゲーム

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc016/tasks/arc016_2

楽器を演奏できない高橋君は、音楽ゲームが大好きです。  
 このゲームでは $ 9 $ 個のボタンが存在し、曲に合わせてボタンをタイミングよく押したり、押しっぱなしにすることによって楽器を演奏してしている気分になります。  
 あなたには高橋くんがプレイした楽曲の譜面が与えられます。  
 ボタンを押す場所は`x`、押しっぱなしにする部分は`o` で与えられます。他は`.`です。  
 高橋くんが譜面をミスなくプレイしたとき、ボタンを押した回数を出力してください。  
 入力は以下の形式で標準入力から与えられる。

> $ N $ $ x_{11} $$ x_{12} $$ ... $$ x_{18} $$ x_{19} $ $ x_{21} $$ x_{22} $$ ... $$ x_{28} $$ x_{29} $ : $ x_{N1} $$ x_{N2} $$ ... $$ x_{N8} $$ x_{N9} $

1. $ 1 $ 行目に、譜面の行数を表す整数 $ N\ (1≦N≦100) $ が与えられる。

- 譜面は常に $ 9 $ 列であることが保証されている。

5. $ 2 $ 行目からの $ N $ 行で、高橋くんが遊ぶ譜面が与えられる。 
  - 譜面の種類は `x` `o` `.` の $ 3 $ 種類である。
  - 譜面が `x` のとき、高橋くんはボタンを押す。
  - 譜面が `o` のとき、高橋くんはボタンを押し、同じ列で `o` が続く限り押しっぱなしにする。
  - 譜面が `.` のとき、高橋くんは何もしない。
 高橋くんが譜面をミスなくプレイしたとき、ボタンを押した回数を出力せよ。  
 なお、出力の最後には改行をいれること。  
```
<pre class="prettyprint linenums">
15
.........
.x.......
.........
...x.....
.........
.......o.
.......o.
.......o.
.........
..x.....o
........o
........o
....x...o
.x......o
........o
```

 ```
<pre class="prettyprint linenums">
7
```

- 一瞬だけ押す必要がある部分は $ 5 $ つあります。
- 長押しは $ 2 $ つです。
- 合わせて $ 7 $ が答えです。
 
```
<pre class="prettyprint linenums">
6
..o..x.o.
..o..x.o.
..x..o.o.
..o..o.o.
..o..x.o.
..o..x.o.
```

 ```
<pre class="prettyprint linenums">
9
```

- 一瞬だけ押す必要がある部分は $ 5 $ つあります。
- `x` が連続している場合、何度もボタンを押す必要があることに注意してください。
- 長押しは $ 4 $ つです。
- 合わせて $ 9 $ が答えです。
 
```
<pre class="prettyprint linenums">
2
.........
.........
```

 ```
<pre class="prettyprint linenums">
0
```

# 题解

## 作者：zcl1024 (赞：4)

这道题非常水，不过我觉得题意翻译的不是很清楚  
题意应为：给定一个N行9列的二维数组，求出x的个数和o且上面一个数不是o都数的和  
如果没有理解我的意思，那么详情见代码  
下面献上cpp&&pascal的代码  

----------------------------
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
string a[1010];
int main(){
    int n;
    cin>>n;
    int i,j;
    int ans=0;//不要忘记清0
    for(i=1;i<=n;i++){
        cin>>a[i];//输入字符串
        for(j=0;j<9;j++){//字符串从0开始
            if (a[i][j]=='x'||(a[i][j]=='o'&&a[i-1][j]!='o')) ans++;//根据题意可得
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
-----------
```pas
var n,i,j,ans:longint;
    a:array[0..2000,1..20] of char;//数组定义一定要从0开始
begin
  readln(n);
  for i:=1 to n do
  begin
    for j:=1 to 9 do
    begin
      read(a[i][j]);
      if (a[i][j]='x')or((a[i][j]='o')and(a[i-1][j]<>'o')) then inc(ans);//边读入边判断
    end;
    readln;//不要忘记哦
  end;
  writeln(ans);
end.
```

---

## 作者：朱屹帆 (赞：3)

### 题目：[AT769 音楽ゲーム](https://www.luogu.com.cn/problem/AT769)
### 题意：这一题翻译讲的不是很清楚，我来翻译一下：
一种演奏乐曲的谱子上有三种符号：$ x $，$ o $和 $ .$。

这张谱子格式为n行9列，编写一个程序，求出答案。

答案为：谱子中$ x $的个数和$ o $的连续数列的个数的和。

### 思路：
- 显然，求$ x $的个数很简单，在输入时标记一下就可以了。
- 但求$ o $的连续数列的个数就需要数组来记录了。

  我们只需要计两个数组$last[n]$和$now[n]$就可以了。
  
  $last[i]$表示上一行$o$的位置；
  
  $now[i]$表示这一行$o$的位置。
  
  如果$last[i]$不是$o$且$now[i]$是$o$，则cnt++。
  
  如果$last[i]$是$o$且$now[i]$也是$o$，则cnt不变。
  
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long q=0,w=1;
	char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')q=q*10+ch-'0',ch=getchar();
	return q*w;
} //快读
void write(long long out){
	if(out<0){puts("-");out=abs(out);}
	if(out>9)write(out/10);
	cout<<out%10;
} //快写
const long long N = 1e3+5;
char input; //输入字符
long long n,i,j,cnt;
bool last[N],now[N]; //两个数组记录状态
int main(){
	n=read();
	for(i=1;i<=n;i++){
		for(j=1;j<=9;j++){
			input=getchar();
			if(input=='.')now[j]=false;
			if(input=='x')now[j]=false,cnt++; //关于x，cnt++;
			if(input=='o'){ //判断o
				if(last[j]==false)
					cnt++;
				now[j]=true;
			}
		}
		input=getchar();
		for(j=1;j<=9;j++)last[j]=now[j];
	}
	write(cnt),cout<<endl;
	return 0; //完美结束
}
```
### 注：
这是一道被恶意评分的题目，实际是一道水题！

---

## 作者：RioBlu (赞：1)

我用字符串+不用字符串数组

只要一个last字符串和a(代表now)字符串
```
#pragma GCC optimize(2)//O(2)优化
#include<bits/stdc++.h>
using namespace std;
string a,last;
long long b,ans;
int main()
{
	cin>>b;
	for(int s=0;s<b;s++)
	{
	    cin>>a;
	    for(int v=0;v<9;v++)
	    {
	        if(a[v]=='o'&&last[v]!='o')ans++;//使用last的判断
	        if(a[v]=='x')ans++;//判断
	    }
	    last=a;//last的赋值部分
	}
	cout<<ans<<endl;
}
```

---

## 作者：CZQ_King (赞：1)

这道题还算水，就是判断$x$的个数和一排$o$的个数。~~（感觉真像节奏大师）~~

------------
思路：在输入的时候判断$x$的个数，如果是$o$，再判断它上面那个是不是$o$，不是的话，个数$++$。

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,ans;
char music[1000][9];//对于AT那么水的题1000够了
int main(){
	cin>>a;
	for(int i=0;i<a;i++){
		for(int j=0;j<9;j++){
			cin>>music[i][j];//输入相应的按键
			if(music[i][j]=='x')ans++;//如果是x，个数++
		}
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<a;j++){
			if(music[j][i]=='o'&&music[j-1][i]!='o')//判断是不是o且上面那个是否不是o
			ans++;//个数++
		}
	}
	cout<<ans<<endl;//最后输出个数
	return 0;//结束
}
```

---

## 作者：monstersqwq (赞：0)

~~原来紫题的难度估计全在题意理解上了~~

#### 题目大意：

给出一个 $a$ 行 $9$ 列的矩阵，由“o”、“x”、“.”三种字符组成，问“x”的个数与“o”的列数之和（注意，一个“o”也算一列）

“o”的列数可以转化为：正上方不是“o”且当前位置是“o”的位置数量，这样一列“o”只会在开头的一个计数。

至于开头的“o”在第一行的情况，因为用 string 吞换行可能会出现一些玄学错误，特判一下就好了。

直接模拟即可。

这道题中还有一些小小的细节，代码里都有写。

tips：AT 题中不换行，听取 WA 声一片。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int main()
{
    string a[1005];
    int n,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        for(int j=0;j<9;j++)//string从0开始
        {
            if(a[i][j]=='x') ans++;
            else if(a[i][j]=='o'&&i==1) ans++;
            else if(a[i][j]=='o'&&a[i-1][j]!='o') ans++;//为了防止可能出现的一切玄学错误，我写成了else if的形式
        }
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Mr_WA的大号 (赞：0)

桃花潭水深千尺，不及管理员送我情。小学生又来发题解了！

题号：AT769

算法：暴力

难度：★

## 开课了！

这一题非常的容易，模拟就能AC这一题。以下为这一题的解答方式：

第一步：输入。因为是要统计x的个数，所以可以在输入的时候就开始统计x的个数。

第二步：统计连续o的个数。o的个数是指竖排连续，并不是横行。所以用一个双重循环来枚举。外层循环枚举列，内层循环枚举行。如果
```cpp
music[j][i]=='o'&&mucis[j][i]!='o'
```
，就加1。

第三步：输出。

课讲完了，上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<iomanip>
using namespace std;
int n,ans;
char music[1010][30];
int main()
{
	cin>>n;//输入
	for(int i=1; i<=n; i++)
		for(int j=1; j<=9; j++)
		{
			cin>>music[i][j];//输入乐谱
			if(music[i][j]=='x')ans++;//如果是x，加1
		}
	for(int i=1; i<=9; i++)
		for(int j=1; j<=n; j++)//双重循环枚举
			if(music[j][i]=='o'&&music[j-1][i]!='o')ans++;//如果条件成立，加1
	cout<<ans;//输出
	return 0;
}
```
祝大家能AC！

---

## 作者：谷民 (赞：0)

## AT769 【音楽ゲーム】

本题题意不太清晰，以我的理解是求“x”的个数和满足上方不是“o”的字符“o”的个数。

举样例2为例
>
6  
..o..x.o.  
..o..x.o.  
..x..o.o.  
..o..o.o.   
..o..x.o.  
..o..x.o.

计数的为红色字符
>
6  
..$\color{red}{\text{o}}$..$\color{red}{\text{x}}$.$\color{red}{\text{o}}$.  
.. o ..$\color{red}{\text{x}}$. o .  
..$\color{red}{\text{x}}$..$\color{red}{\text{o}}$. o .  
..$\color{red}{\text{o}}$.. o . o .   
.. o ..$\color{red}{\text{x}}$. o .  
.. o ..$\color{red}{\text{x}}$. o .

共9个

思路：读入字符矩阵，若为“x”直接累加，若为“o”，判断上方不为“o”累加

代码：

```
#include<bits/stdc++.h>
using namespace std;
int n;
char x[305][15];//字符矩阵
int ans;//累加和答案
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=10;j++){//循环读入
			scanf("%c",&x[i][j]);
			if(x[i][j]=='x'){//判断x直接累加
				ans++;
			}
			if(x[i-1][j]!='o'&&x[i][j]=='o'){//若为o判断上方后累加
				ans++;
			}
		}
	}
	printf("%d\n",ans);//输出，注意AT需要换行
	return 0;
}

```




---

## 作者：Ciyang (赞：0)

#### 这题是学习滚动数组思想的水题。

找遍了题面，仍然找不到 N 的范围，但是我们已知列数为 9 。其他题解可能是尽可能往大里开吧，我们就选择滚动数组的思路了，当然也可以像有一篇题解一样开两个变量，但是没那么方便。

题意大概是数'x'的个数和'o'的排数（有几排不连续的'o'），因此思路很简单，数'x'就不必说了，然后数上方不是'o'的'o'。

所以就开一个char数组tmp\[2\]\[10\]，然后开一个变量 m 用来滚动。

打个广告，[**My blog**](https://xciyang.github.io/)。

#### 代码:

```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
int n, m, ans;
char tmp[2][10];
int main() {
// 主程序
	cin >> n;
	while(n--) {
		cin >> tmp[m];
		for(int i= 0; i < 9; i++) ans+= (tmp[m][i] == 'x' || (tmp[m][i] == 'o' && tmp[m ^ 1][i] != 'o'));
        // 模拟即可
		m^= 1;
        // 滚动思路
	}
    cout << ans << endl;
	return 0;
}
```


---

## 作者：xujian (赞：0)

这是一道被恶意评分的题目。

虽然是一道紫题，但是真的很水，不像楼下几位大佬的代码那样复杂。

## 题意：给定一个n行8列的矩阵，求其中x字符的个数与o字符且上面字符不是o字符的个数的和（有点绕）

方法：按题意模拟即可。

代码如下↓：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[1010];
int n,sum;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=0;i<=n;i++)
		for(int j=0;j<9;j++)
			if(s[i][j]=='x'||(s[i][j]=='o'&&s[i-1][j]!='o'))sum++;
	cout<<sum<<endl;
	return 0;
}
```

人生中第一道紫题题解，管理大大给过吧。

---

