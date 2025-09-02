# Letter

## 题目描述

给定一 $N \times M$ 规模的矩阵，输出最小的包含所有 `*` 的矩阵。

## 说明/提示

$1 \leq N,M \leq 50$。

## 样例 #1

### 输入

```
6 7
.......
..***..
..*....
..***..
..*....
..***..
```

### 输出

```
***
*..
***
*..
***
```

## 样例 #2

### 输入

```
3 3
***
*.*
***
```

### 输出

```
***
*.*
***
```

# 题解

## 作者：OdtreePrince (赞：10)

# -模拟-

代码虽长，但缺一不可，先找到*，再找出边界，最后输出。

注意：minx/miny必须初始化为>=n,m的值，否则听取WA声一片。

步骤应该十分清晰了吧，具体代码如下：

~~~
#include<bits/stdc++.h>
using namespace std;
int n,m,maxx,maxy,minx=55,miny=55;
char ch[55][55];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ch[i][j]=getchar();
            while(ch[i][j]!='*'&&ch[i][j]!='.') ch[i][j]=getchar();
            if(ch[i][j]=='*'){
                minx=min(minx,i);
                miny=min(miny,j);
                maxx=max(maxx,i);
                maxy=max(maxy,j);
            } 
        }
    }
    for(int i=minx;i<=maxx;i++){
        for(int j=miny;j<=maxy;j++){
            cout<<ch[i][j];
        }
        cout<<endl;
    }
    return 0;
}
~~~

---

## 作者：无欢 (赞：5)

应该本题最短的题解吧：
```cpp
#include<cstdio>
char a[1001][1001];
int main()
{
	int x,y,i,j,xl=99999,yl=99999,xm=-1,ym=-1;
    //xl和yl表示开始的行数，和开始的列数，所以这里把99999定义为无穷大
    //xm和ym表示结束的行数，和结束的列数，当然，因为没有负数组，所以赋值为-1就好了。
	scanf("%d %d",&x,&y);
	for(i=0;i<=x-1;i++)
	{
		scanf("%s",a[i]);
		for(j=0;j<=y-1;j++)
		{
			if(a[i][j]=='*')
			{
				xl=xl<i? xl:i;//求开始的行数
                //如果当前的行数，比开始的行数小，那开始的行数，就变为当前的行数
                
				yl=j<yl? j:yl;//求开始的列数
                //如果当前的列数，比开始的列数小，那开始的列数，就变为当前的列数
                
				xm=i>xm? i:xm;//求结束的行数
                //如果当前的行数，比结束的行数大，那结束的行数，就变为当前的行数
                
				ym=j>ym? j:ym;//求结束的列数
                //如果当前的列数，比结束的列数小，那结束的列数，就变为当前的列数 
			}
		}
	}
	for(i=xl;i<=xm;i++)//根据开始行、结束行逐行输出
	{
		for(j=yl;j<=ym;j++)//根据每行的开始列、结束列逐列输出
		{
			printf("%c",a[i][j]);
		}
		printf("\n");//记得换行哦~
	}
	return 0;
}
```
程序到这就结束了，我相信我的注释已经够详细了。

---

## 作者：loi_hjh (赞：3)

~~请忽略那些奇奇怪怪的头文件~~

附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,p,q,x,y;
char gg,a[101][101];
int main(){
	scanf("%d%d",&n,&m);
	p=0x3f,x=0x3f;//无穷大 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>gg;
			a[i][j]=gg;
			if(gg=='*'){
				if(i<=p) p=i;//最左上角的* 
				if(j<=x) x=j;//最右上角的* 
				if(i>=q) q=i;//最左下角的 
				if(j>=y) y=j;//最右下角的 
			}
		}
	for(int i=p;i<=q;i++){
		for(int j=x;j<=y;j++)
			printf("%c",a[i][j]);
		putchar('\n');
	}
	return ~~(0-0);
}
```

---

## 作者：hinatakaho (赞：2)

这是一道字符串的模拟题，按照题意去写就好了qwq
```cpp
  #include< bits/stdc++.h > // 万能头文件
  using namespace std; // by hinatakaho
  char a[51][51];
  #define REG register
  int main(){
   	REG int n,m,h1=-1,z1=-1,h2=-1,z2=-1;//h1，z1,h2,z2分别是用来寻找最上，最左，最下，最右的“*”的，全部初始化为-1；
	scanf("%d%d",&n,&m);//可以用cin，但还是用scanf更好，如果有读入优化最好
	for(REG int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf(" %c",&a[i][j]);//占位符前要有空格，跳过换行符；
		}
	} 
    //以下是四个顶点的寻找
	for(REG int i=1;i<=n;i++){
		for(REG int j=1;j<=m;j++){
			if(a[i][j]=='*'){
				h1=i;
				break;
			}
		}
		if(h1==i){
			break;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='*'){
				h2=i;
				break;
			}
		}
			if(h2==i){
			break;
		}
	}
	for(REG int i=1;i<=m;i++){
		for(REG int j=1;j<=n;j++){
			if(a[j][i]=='*'){
				z1=i;
				break;
			}
		}
		if(z1==i){
			break;
		}
	}
	for(REG int i=m;i>=1;i--){
		for(REG int j=1;j<=n;j++){
			if(a[j][i]=='*'){
				z2=i;
				break;
			}
		}
			if(z2==i){
			break;
		}
	}
	for(REG int i=h1;i<=h2;i++){
		for(REG int j=z1;j<=z2;j++){
			printf("%c",a[i][j]);
		}
			printf("\n");//注意换行；
		}
	return 0;//结束qwq，祝大家编程开心
 }
```

---

## 作者：PC_DOS (赞：2)

这是一道字符串模拟题，事实上只需要从输入的字符串里找到以下内容即可:

1. iStartY-第一个有星号的行的编号；

2. iEndY-最后一个有星号的行的编号；

3. iStartX-所有有星号的行中，星号第一次出现的列号的最小值；

4. iEndX-所有有星号的行中，星号最后一次出现的列号的最大值；

因此就可以得到代码了:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInput; //暂存输入的字符串
	vector<int> arrLineHaveStar, arrColStart, arrColEnd; //arrLineHaveStar-存放所有有星号的行的编号，arrColStart-存放所有有星号的行中，星号第一次出现的列号，arrColEnd-存放所有有星号的行中，星号最后一次出现的列号
	vector<string> arrDraw; //存放所有输入的字符串
	int iWidth, iLength, i, j, iStartX, iEndX, iStartY, iEndY; //iWidth-行数，iLength-列数，i、j-循环计数器，iStartY-第一个有星号的行的编号，iEndY-最后一个有星号的行的编号，iStartX-所有有星号的行中，星号第一次出现的列号的最小值，iEndX-所有有星号的行中，星号最后一次出现的列号的最大值
	cin >> iWidth >> iLength; //输入行数和列数
	for (i = 1; i <= iWidth; ++i){ //逐行读入
		cin >> sInput; //读入字符串
		if (count(sInput.begin(), sInput.end(), '*')!=0){ //如果这个串有星号(这里用到了STL的count()函数)
			arrLineHaveStar.push_back(i - 1); //保存这一行的行号
			for (j = 0; j <= iLength - 1; ++j){ //记录星号第一次出现的列号
				if (sInput[j] == '*'){
					arrColStart.push_back(j);
					break;
				}
			}
			for (j = iLength - 1; j >= 0; --j){ //记录星号最后一次出现的列号
				if (sInput[j] == '*'){
					arrColEnd.push_back(j);
					break;
				}
			}
		}
		arrDraw.push_back(sInput); //保存输入的字符串
	}
	if (arrLineHaveStar.size() == 0){ //特判，如果一个星号都没有
		goto endapp; //直接结束
	}
	iStartY = arrLineHaveStar[0]; //记录第一个有星号的行的编号，由于arrLineHaveStar肯定是升序的，因此第一项一定最小
	iEndY = arrLineHaveStar[arrLineHaveStar.size() - 1]; //记录最后一个有星号的行的编号，由于arrLineHaveStar肯定是升序的，因此最后一项一定最小
	iStartX = *min_element(arrColStart.begin(), arrColStart.end()); //计算星号第一次出现的列号的最小值
	iEndX = *max_element(arrColEnd.begin(), arrColEnd.end()); //计算号最后一次出现的列号的最大值
	for (i = iStartY; i <= iEndY; ++i){ //从第一个有星号的行循环到最后一个有星号的行
		for (j = iStartX; j <= iEndX; ++j){ //从星号第一次出现的列号的最小值循环到星号最后一次出现的列号的最大值
			cout << arrDraw[i][j]; //输出对应字符
		}
		cout << endl; //一行输出完毕，别忘了换行哦
	}
endapp:
	return 0; //结束
}
```

---

