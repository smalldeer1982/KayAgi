# [ARC020A] 石を滑らせるゲーム

## 题目描述

蚂蚁Ant和Bug在玩一个关于石头的游戏。这个游戏使用一根笔直的细长的冰板和两个小的石头。冰板每1毫米有1000，-1000两种刻度。开始两只游戏蚂蚁玩家有一块石头。两只蚂蚁游戏者交替地从木板边缘滑动石头。然后，最终滑动的石头更接近0度刻度的玩家将成为该游戏的胜者。此外，如果两个石头上的距离为0，则判为平局。为了Ant先生和Bug先生这两只好玩的蚂蚁，请制定出两个棋子位置的刻度分别被给予时判定胜负的程序。

## 样例 #1

### 输入

```
2 3```

### 输出

```
Ant```

## 样例 #2

### 输入

```
1 0```

### 输出

```
Bug```

## 样例 #3

### 输入

```
-100 100```

### 输出

```
Draw```

# 题解

## 作者：da32s1da (赞：4)

平方即可，无需绝对值。
```
#include<cstdio>
int a,b;
int main(){
    scanf("%d%d",&a,&b);
    if(a*a>b*b)puts("Bug");
    else if(a*a==b*b)puts("Draw");
    else puts("Ant");
}
```

---

## 作者：初音Miku (赞：4)

首先更正我的翻译

给定2个在-1000~1000范围的整数 $a$ $b$ ，Miku会把它们比较。

如果 $a$ 的绝对值比 $b$ 的绝对值大，输出`Bug`并换行。

如果 $a$ 的绝对值比 $b$ 的绝对值小，输出`Ant`并换行。

如果 $a$ 的绝对值与 $b$ 的绝对值相等，输出`Draw`并换行。
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>//不需解释的头文件
//#include<Hatsune_Miku>//能让你AK的头文件
using namespace std;//标准
int a,b;//全局变量定义
int main(){
	cin>>a>>b;//读入
	if(abs(a)<abs(b))cout<<"Ant"<<endl;//(比较绝对值记得要cmath
	if(abs(a)>abs(b))cout<<"Bug"<<endl;
	if(abs(a)==abs(b))cout<<"Draw"<<endl;//根据题意判断即可
	return 0;//退出
}
```
![](https://cdn.luogu.com.cn/upload/pic/19396.png)感谢[Irressey](https://www.luogu.org/space/show?uid=79017) 找出我翻译的错误

---

## 作者：林家三少 (赞：2)

$$\small\text{这题我不用平方、abs和加负号}$$ 

$$\small\text{我用了......string!}$$ 

![](http://wx4.sinaimg.cn/large/005XSXmNgy1frvzb0e4suj30h70h7dnt.jpg)

其实比平方、abs和加负号都~~要复杂~~差不多

思路：**先输入那个string,然后利用for来去负号**

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
//优美的小蛮腰文件头qwq
using namespace std;
string a,b;
int aa,bb,k,kk;
int main(){
	cin>>a>>b;
    //这里的a,b都是字符串
	if(a[0]=='-'){
		k=1;
        //我们后面的for其实是把string转成int
        //所以k=1就是跳过负号，从第二个开始
	}
	for(int i=k;i<=a.size()-1;i++){
			aa=aa*10+int(a[i]-48);
            //这个就是用来转int的
	}
	if(b[0]=='-'){
		kk=1;	
        //和上面的一样，b也要转int
	}
	for(int i=kk;i<=b.size()-1;i++){
			bb=bb*10+int(b[i]-48);
	}
    
    //然后接下来就很简单了，直接判断就行
    
	if(aa==bb){
		cout<<"Draw\n";
		return 0;
	}//一样就平局
	if(aa<bb){
		cout<<"Ant\n";
	}//Ant赢
	else{
		cout<<"Bug\n";
	}//Bug赢
	return 0;
}
```



---

## 作者：konglk (赞：1)

终于看到一道写题解的人少的题目了

谁的绝对值越小，谁离0就更近。绝对值在数轴上就是数与0点的距离。这样思路就很清晰了，比较两个的绝对值即可。绝对值用abs~~olute~~函数，表示一个数的绝对值用abs（n）

上代码
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
 int a,b;
 cin>>a>>b;
 int c=abs(a),d=abs(b);
 if(c==d)cout<<"Draw\n";
 else if(c<d)cout<<"Ant\n";
 else cout<<"Bug\n";
 return 0;
}
```
祝大家早日~~AK~~变红！！！

---

## 作者：不到前10不改名 (赞：1)

```
#include<stdio.h>
int a,b;
int main()
{
    scanf("%d%d",&a,&b);
    if(a<0)a=-a;
    //其实abs啊,平方啊都不用...反而直接加负号最快（真的！不信你看最优解里我的在公主殿下前面）
    if(b<0)b=-b;
    if(a>b)
    printf("Bug\n");//回车了解一下？
    else if(a==b)
    printf("Draw\n");
    else 
    printf("Ant\n");
}
```

---

