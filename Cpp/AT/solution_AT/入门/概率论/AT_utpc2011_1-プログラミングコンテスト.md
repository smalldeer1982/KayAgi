# プログラミングコンテスト

## 题目描述

[problemUrl]: https://atcoder.jp/contests/utpc2011/tasks/utpc2011_1



# 题解

## 作者：МiсDZ (赞：3)

这应该是一道atcoder的试机题，具体的历史故事我不清楚(看原题翻译好像是什么大赛，了解后我会补充的)，只是知道这题水得应该没人会看题解。
```cpp
#include<bits/stdc++.h>
//#define BL 暴力
using namespace std;
int a[10010][10010],se[10010],maxx=-10234567;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];//BL存储
			if(a[i][j]==1)se[i]++;//BL累加
			if(se[i]>maxx)maxx=se[i];//BL求解
		}
	cout<<maxx<<endl;//BL输出
}
```

---

## 作者：Hzq11_ (赞：1)

## 这题输出要换行!!!
~~否则WA~~  
因此我试了好几次都不行。

### 代码连数组都不用!
送C++代码:
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
int temp,n,m,ans;
int main(){
	int A;
	cin>>n>>m;
	for (int i=0;i<n;i++){
		temp=0;
		for (int j=0;j<m;j++){
			scanf ("%d",&A);  //读入不解释
			if (A)       // 判 断 是 否 等 于 一
				temp++;	
		}
		ans=max (ans,temp);  //更新最大值
	}
	return (cout<<ans<<endl)&&0; //换行保平安
}
```

---

## 作者：TRZ_2007 (赞：0)

发现这题$C$党的同学都没有发题解！  
赶紧发一篇（逃~~  
这道题目，是纯的二维数组,四个$for$，一个$if$就$OK$了  
接下来上代码：
```
#include <stdio.h>
#define max(a,b) a>b?a:b//define宏定义
int main()
{
	int i,j,n,m,ans=0,sum=0;//ans是储存1最多的那一行1的个数，sum是储存当前行1的个数。
	scanf("%d %d",&n,&m);//读入。
	int a[n][m];//省空间大法。
	for(i=0;i<n;i++)//循环读入
		for(j=0;j<m;j++)
			scanf("%d",&a[i][j]);
	for(i=0;i<n;i++)//一列一列慢慢来。
	{
		sum=0;//每一次计数后都得归0。
		for(j=0;j<m;j++)//扫描当前行。
			if(a[i][j]==1) sum++;//如果等于1，sum自加。
		ans=max(sum,ans);//和之前的最大值相比较。
	}
	printf("%d\n",ans);//输出，注意岛国的题目要换行。
}//完美收场2333
```

---

## 作者：Oaklimy (赞：0)

###  本人第一次发题解，请大(shen)佬(ben)多多包涵.
	 这道题很水，AT上的题都如此。




------------
好了，附上代码吧！！！
```cpp
#include <bits/stdc++.h>//无敌头文件
using namespace std;
int main()
{
	int n, m, sum=0, maxv=-1;
	cin >> n>>m;
	int a[n+1][m+1];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];//输入
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]==1)sum++;//判断是否为1.
		}
		maxv=max(maxv,sum);//比较。
		sum=0;
	}
	cout<<maxv<<endl;//输出一最多的一行。
	return 0;//完美撒花。
}
```
还算简单吧！只要熟练操作，人人都会做。


---

## 作者：CZQ_King (赞：0)

# 很简单啊，~~岛国题真水~~
$5$个变量，$3$个$if$，$1$个$for$搞~~腚~~定
```cpp
#include<bits/stdc++.h> //头文件
using namespace std;
int a,b,c,d,e=-1;//就五个变量哦
int main(){
    cin>>a>>b;//输入不多说
    for(int i=1;i<=a*b;i++){//一个a*b循环就行，待会一个mod
        cin>>c;//输入数字（好像是废话）
        if(c==1)d++;//判断是否为1
        if(i%b==0){//与上面的for对应
            if(d>e)e=d;//判断最大值
            d=0;//记得要清零
        }
    }
    cout<<e<<endl;//换行！换行！换行！
    return 0;//完美结束
}
```

---

## 作者：xujian (赞：0)

# 这题的正解是二维数组！

但是本蒟蒻看了这么多题解，觉得是不是还有新解法。

然后一个奇葩的思路就诞生了。

# 一个循环就可以AC！！！

解法也很简单。

首先，矩阵是n*m个数，用一个循环输入就好了，a就是输入的数。

接着，用一个条件判断a是否为1，是则计数器s累加。

再接着，判断一行是否结束（i%m==0）。若果结束则判断是否为最优值。

最后，输出最优值x就可以了，只要弄懂了就不难。

# 所有日本题一定要换行！！！

好了，接下来是代码，谢谢大家。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,s,x;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n*m;i++){
		cin>>a;
		if(a)++s;
		if(i%m==0)x=x>s?x:s,s=0;
	}
	cout<<x<<endl;
	return 0;
}
```

---

## 作者：Soyilieber (赞：0)

# **pascal版本**

十分水的入门知识，ij做循环变量，读入ab，然后循环，每次外循s要清0，forj读数，判断为1则累加，然后对比，大的往ans里塞，最后输出，23个点ac。
### 根本不用数组！！！###
以下为码
```pascal
var
    i,j,a,b,c,s,ans:longint;
begin
    read(a,b);
    for i:=1 to a do
        begin
            s:=0;
            for j:=1 to b do
                begin
                    read(c);
                    if c=1 then inc(s);
                end;
            if s>ans then ans:=s;
        end;
    writeln(ans);
end.
```

---

## 作者：爱晚亭哦 (赞：0)

好久没上洛谷，一上发现日本题库出来了！！！第一题还是水题一题！！！忍不住刷了刷。

回归本题：这题考的只是读入二维数组，其他什么比大小环节就很水了吧（其实读入二维数组已经很水了）。除此之外，就是**输出要换行，否则全WA。**

上代码：
```
#include<cstdio>
int a[10086][12315],b[25041],c=0;//诡异的数组（逃
int main()
{
    int n,m;
	scanf("%d %d",&n,&m);//读入行、列
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
		{
            scanf("%d",&a[i][j]);//读入二维数组
            if(a[i][j]==1)//判断是否为1
				b[i]++;//1的数量+1
            if(b[i]>c)//求数量最多的那一行的个数
				c=b[i];
        }
    printf("%d\n",c);//别忘了换行
}
//蒟蒻题解，大佬勿喷(T~T)
```
~~求管理过qwq~~

---

## 作者：康娜卡姆依 (赞：0)

其他都不想说，但有一点要注意：
#  _ **输出时要换行。。。**_

因此WA得蜜汁尴尬。。。

草率地来一发——
```pascal
uses math; //max调用的数学库
var n,m,i,j,a,zc,maxx:longint;//相信你们都能理解为何不用数组
begin
  read(n,m);
  for i:=1 to n do
  begin 
    for j:=1 to m do
    begin
      read(a);
      if a=1 then inc(zc);
    end;
    maxx:=max(maxx,zc);
    zc:=0;
  end;
  writeln(maxx);
end.
```

---

