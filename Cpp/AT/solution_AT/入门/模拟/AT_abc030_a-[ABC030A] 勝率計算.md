# [ABC030A] 勝率計算

## 题目描述

野球 AtCoder 联赛的赛季已经结束。高桥队在 $A$ 场比赛中赢了 $B$ 场，青木队在 $C$ 场比赛中赢了 $D$ 场。在 AtCoder 联赛中，胜率越高的队伍排名越高。请编写一个程序，判断高桥队和青木队哪一队的胜率更高。

## 说明/提示

### 样例解释 1

高桥队的胜率为 $2/5=0.4$，青木队的胜率为 $3/6=0.5$，所以青木队的胜率更高。另外，两队的比赛场数可能不同。

### 样例解释 2

当比赛场数相同时，胜场数更多的队伍胜率更高。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2 6 3```

### 输出

```
AOKI```

## 样例 #2

### 输入

```
100 80 100 73```

### 输出

```
TAKAHASHI```

## 样例 #3

### 输入

```
66 30 55 25```

### 输出

```
DRAW```

# 题解

## 作者：Bilibili乾杯Ω (赞：7)

望采纳，谢谢

~~其实这题比较煎蛋~~~

## 但是，

有一个十分十分重要的东西，那就是：

### 空行!!!
（之前就是因为没有空行WA了）

思路：分别算出高桥君与青木君的胜率再来三个比较就OK了。

话不多说，上代码~~
```cpp
#include<bits/stdc++.h>  //万能头
using namespace std;
double a,b,c,d,gao,qing;  //一定要用double！！
int main(){
    cin>>a>>b>>c>>d;
    gao=b/a;
    qing=d/c;
    if(gao==qing) cout<<"DRAW"<<endl;  //判断两人胜率是否一样
    if(gao>qing) cout<<"TAKAHASHI"<<endl;  //判断高桥君的胜率是否更高
    if(gao<qing) cout<<"AOKI"<<endl;  //判断青木君的胜率是否更高
    return 0;  //结束~~
}
```

---

## 作者：有限光阴 (赞：3)

# ~~一道大水题~~
上代码
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
	double a,b,c,d,f,t;
	cin>>a>>b>>c>>d;
	f=b/a;//高桥君的胜率
	t=d/c;//青木君的胜率
	if(f==t)cout<<"DRAW"<<endl;  //判断两人胜率是否一样
	if(f>t)cout<<"TAKAHASHI"<<endl;  //判断高桥君的胜率是否更高
	if(f<t)cout<<"AOKI"<<endl;  //判断青木君的胜率是否更高
	return 0;好习惯
}
```
~~不喜勿喷~~

~~dalao勿喷~~


------------
这里告诉一些不怎么做AT题的朋友

AT题都需要--**换行**


---

## 作者：Kazdale (赞：2)

对于一些对double不是特别熟悉的人来说，我们这道题可以采取一种特殊的做法。


先想一想小数的比较方式：从高位到低位依次比较



再想一想整数的呢？一样


------------

## 关键就在于如何让计算机把 _小数变成整数_ 


举个例子：

87 / 100 = 0.87 = 87%

下面是重点

### 87 * 100 = 8700

### 8700 / 100 = 87

也就是说可以把被除数乘以10的n次方，再除以除数，把商转换成整数再比较

上代码
------------
```cpp
#include <iostream>
using namespace std;
int main(){
    long long a,b,c,d;//开long long是怕数据过大（时间充足）
    cin >> a >> b >> c >> d;
    b *= 10000000;
    d *= 10000000;//乘数稍微大一些，提高一下精度
    b /= a;
    d /= c;//算胜率
    if(b > d){
        cout << "TAKAHASHI\n";
    }
    if(b == d){
        cout << "DRAW\n";
    }
    if(b < d){
        cout << "AOKI\n";
    }//比较（AT题结果需要换行）
	return 0;//好习惯
}
```




---

## 作者：_Andy_Lin_ (赞：1)

[博客传送门](https://www.luogu.com.cn/blog/linguosheng/)

------------
我不用什么实数，直接用分数来处理，还不用担心精度问题。

------------
方法是：高桥君的胜率是b/a,青木的胜率是d/c。先来通个分，让b乘上c，让d乘上a，分母就一样了。然后就直接比较b与d即可。

------------
AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main()
{
	scanf("%d%d%d%d",&a,&b,&c,&d);
	d*=a,b*=c;
	if(d>b){
		puts("AOKI");
	}
	else if(d<b){
		puts("TAKAHASHI");
	}
	else{
		puts("DRAW");
	}
	return 0;
}
```

---

## 作者：CZQ_King (赞：1)

来一波$Python3$代码

题目原意：
> 输入A,B,C,D

> A：高橘君参赛数，B:高橘君胜利数，C:青木参赛数，D:青木胜利数

> 如果胜率一样输出"DRAW"

> 如果高橘君胜率高输出"TAKAHASHI"

> 如果青木胜率高输出"AOKI"

模拟就可以过。

公式：$\Large\text{胜率}=\frac{\text{胜利数}}{\text{总参赛数}}$

通过上面这个公式算出俩人的胜率，再比较一下就可以了

代码：
```
a,b,c,d=map(int,input().split())
e=b/a
f=d/c# 算出两人的胜率
if e>f: # 如果TAKAHASHI的胜率比AOKI的高
    print ("TAKAHASHI")
elif e<f: # 如果比他低
    print ("AOKI")
else: # 如果一样
    print ("DRAW") # 平手
```
注意：
1. 输入要用``map(int,input().split())``，否则$RE$
2. 除号``'/'``不要写成整除``'//'``
3. 你会发现有一个长得很像``else``又长得很像``if``的``elif``，其实它就是``if else``的缩写。

---

## 作者：李之恒 (赞：0)

题目意思很明确，就是比较2个人的胜率，而求胜率的公式为：

**胜率=获胜场次÷ 总比赛场次x100%**

有人会问，100%不就是1吗？加上去有什么用。

这你就大错特错了。

**如图：**
输入1和2，分别计算1/2和1* 1.0/2的值，结果截然不同。

![](https://cdn.luogu.com.cn/upload/image_hosting/ebcty3bp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

但请各位注意，**这里的乘1.0不是起到转换百分比的作用**，因为它有更加光荣的任务：
#### 我们考虑C/C++对于有关浮点数(long double,double,float)除法的规定：当除数或被除数至少一个为浮点数时，先将除数和被除数都强制转换成浮点型，再做除法，返回值为一个浮点型。所以我们只要将被除数强制转换成浮点数即可。一种优美的写法是 1.0 * a / b。根据乘法的规定，浮点型和整形做乘法，返回值为浮点型，而 1.0是一个浮点型，于是被除数 1.0 * a 变成了一个浮点型，根据上面的分析，上式的结果就是一个正常的浮点数了。
具体请见 [感谢](https://www.luogu.com.cn/blog/fusu2333/solution-p5006)

知道了这个，本题也就解得很流畅了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c,d;
	double x,y;
	cin>>a>>b>>c>>d;
	x=b*1.0/a;
	y=d*1.0/c;
	if(x>y)
	{
		printf("TAKAHASHI\n");
		return 0;
	}
	if(x<y)
	{
		printf("AOKI\n");
		return 0;
	}
	printf("DRAW\n");
	return 0;
}
```
最后提醒一句：**注意换行**

P.S:**感谢管理员对我问题的指正**。

---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题我要吐槽一下标签，这完全就是恶意评分。哪里需要高精？？？哪里需要哈希？？？言归正传，开始讲题。读入4个数，分别是高橘君参赛数，高橘君胜利数，青木参赛数，青木胜利数，再用两个变量存储b/a和d/c的值，也就是胜率。再比较一下，对应输出即可。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    double a,b,c,d;
    double s1,s2;//注意要用double
    int main()
    {
    cin>>a>>b>>c>>d;//读入数据
    s1=b/a;//求高橘君胜率
    s2=d/c;//求青木君胜率
    if(s1>s2)cout<<"TAKAHASHI";//如果高橘君胜率高，输出TAKAHASHI
    if(s1<s2)cout<<"AOKI";//如果青木君胜率高，输出AOKI
    if(s1==s2)cout<<"DRAW";//如果平局，输出DRAW
    cout<<endl;//AT题记得换行
    return 0;
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：Eric_lerk (赞：0)

**一个简单易懂的代码**

------------
**关于吐槽**:有些不懂精度的可以看看[这篇文章](https://www.luogu.org/blog/ybuffcoding/solution-at1515)。

------------
**上代码**
------------

```cpp
#include<bits/stdc++.h>//万能头，联赛必备
using namespace std;//没有它输入输出是不存在的
int main()//定义主函数
{
	double a,b,c,d;//看题意不解释
	double s,k;//用精度
	cin>>a>>b>>c>>d;//输入
	s=b/1.0/a;//储存高桥君的胜率
	k=d/1.0/c;//储存青木的胜率
	if(s==k){//如果胜率一样
		cout<<"DRAW"<<endl;//输出DRAW
	}
else	if(s>k){//如果高桥胜率大于青木
		cout<<"TAKAHASHI"<<endl;//输出！@#￥%……&
	}
else	if(s<k){//如果青木胜率高
		cout<<"AOKI"<<endl;//输出AOKI(话说有点像AKIOI)
	}
	return 0;//完美~结束
	 
}

```

------------
**警惕后人！！！要注意输入顺序！！！**



---

## 作者：K2sen (赞：0)

# 题很~~煎蛋~~（希望我不会被人锤）

可是他就是很煎蛋啊

当然是要帮帮萌新们啦

赶脚萌新们也不会刷这种题，也就像我一样颓在机房里的人才会刷吧..

上代码楼

开double的变量，然后直接判断就好了啊

还有胜率的算法是：获胜的场次除以比赛的场次..

表忘记换行（不知道岛国咋想的）
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
double c1,c2,s1,s2;
int main() {
	cin>>c1>>s1>>c2>>s2;
	if(s1/c1>s2/c2)
		cout<<"TAKAHASHI"<<endl;
	else if(s1/c1<s2/c2)
		cout<<"AOKI"<<endl;
	else
		cout<<"DRAW"<<endl;
	return 0;
}
```


---

## 作者：Zirnc (赞：0)

这道题很简单，先算出两个人各自的胜率然后比较就行了。

要注意的地方就是要用双精度浮点数类型 `double`。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    double a, b, c, d;
    cin >> a >> b >> c >> d;
    double ab = b/a;
    double cd = d/c;
    if (ab == cd) cout << "DRAW" << endl;
    if (ab > cd) cout << "TAKAHASHI" << endl;
    if (ab < cd) cout << "AOKI" << endl;
    return 0;
}







```

---

## 作者：tgs9311 (赞：0)

蒟蒻的第一篇题解，大佬轻喷……

# 题意很简单：
请你比较两个人的胜率并输出胜率高的那个人，如果一样就输出DRAW。

 ****但是**** ，有一点我们不能忽视：如果**除不尽**，double类型很可能会对两个相等的分数（例如3/7和21/49）判不相同（第一次就是这么WA的）。

于是我们应该写模拟手动比较分数：


------------

```
#include<iostream>//头文件
using namespace std;
int main()
{
    int a,b,c,d;//题目有，不解释
    cin>>a>>b>>c>>d;
    //下面手写比较分数：
    //按照题目的输入，应该比较b/a和d/c
    //因此将它们通分比较，比较cb/ca和da/ca
    //所以只要比较c*b和d*a就行了！
    if(b*c==a*d)
    {
        cout<<"DRAW"<<endl;//如果相同，则胜率一样，输出"DRAW"
    }
    if(b*c>a*d)
    {
        cout<<"TAKAHASHI"<<endl;//如果大于，高橘君胜率高，输出"TAKAHASHI"
    }
    if(b*c<a*d)
    {
        cout<<"AOKI"<<endl;//如果小于，青木胜率高输出"AOKI"
    }
}
```

---

## 作者：zzhhf (赞：0)

# 来发个用函数解题的
#### 分析：这道题只是单独的模拟题。我们只需要根据题目所要求的来编写代码，这道题就可以AC了。
这道题奇怪了。0分代码：

    #include<bits/stdc++.h>   //注释在满分代码。
    using namespace std;
    int a[10];
    double s1,s2;
    void fun(int,int,int,int);
    int main()
    {
    	int a1,a2,b1,b2;
    	cin>>a1>>a2>>b1>>b2;
    	fun(a1,a2,b1,b2);
    }
    
    void fun(int a,int b,int c,int d)
    {
    	s1=b*1.0/a;
    	s2=d*1.0/c;
    	if(s1>s2)cout<<"TAKAHASHI";else
    	if(s1==s2)cout<<"DRAW";else
	if(s1<s2)cout<<"AOKI";
	cout<<endl;
    }
满分代码：

    #include<bits/stdc++.h>   //万能头文件。
    using namespace std;
    int a[10];
    double s1,s2;          //一定要开double。
    void fun(int,int,int,int);  //定义函数。
    int main()             //主程序。
    {
    	int a1,a2,b1,b2;
    	cin>>a1>>a2>>b1>>b2;
    	fun(a1,a2,b1,b2);     //调用函数。
    }

    void fun(int a,int b,int c,int d)
    {
	s1=b*1.0/a;         //这里一定要*1.0不然就变成整除了。
	s2=d*1.0/c;
	if(s1>s2)cout<<"TAKAHASHI";else
	if(s1==s2)cout<<"DRAW";else
	if(s1<s2)cout<<"AOKI";           //输出。
	cout<<endl;
    }

---

## 作者：Jinyeke (赞：0)

#### 题目：输入A,B,C,D，A：高橘君参赛数，B:高橘君胜利数，C:青木参赛数，D:青木胜利数，如果胜率一样输出"DRAW"，如果高橘君胜率高输出"TAKAHASHI"，如果青木胜率高输出"AOKI"
### 大致思路：先求出两个人的胜率（即胜利数除以参赛数），再进行比较
#### 代码如下（pascal):
```pascal
var
 a,b,c,d:longint;
 s1,s2:double;
begin
 read(a,b,c,d);//输入
 s1:=b/a; //s1为高橘君胜率
 s2:=d/c; //s2为青木胜率
 if s1=s2 then writeln('DRAW')//依据题目相等输出DRWM
  else if s1>s2 then writeln('TAKAHASHI')//高桥君赢输出TAKAHASHI
  else if s1<s2 then writeln('AOKI');//青木赢输出AOKI
end.
```
### 共建文明洛谷，请勿Ctrl+C!

---

## 作者：不到前10不改名 (赞：0)

```
#include<stdio.h>
double mzy,zjq,lhy,lgx,srx,sry;//这里用一下数据格式，卡一个精度
int main()
{
    scanf("%lf%lf%lf%lf",&mzy,&zjq,&lhy,&lgx);
    srx=zjq/mzy;//这个zjq和mzy如果是int就会强制转换，srx就会不保留小数了
    //但是这题吃10的-7次方的精度，所以还是老实点double好好做吧！QAQ~
    sry=lgx/lhy；//这个和上面数据同理
    if(srx<sry)//这种低级if语句也没什么好说的呢~
    printf("AOKI\n");//大写+回车
    if(srx==sry)//这地方是两个=（废话！）
    printf("DRAW\n");
    if(srx>sry)
    printf("TAKAHASHI\n");
    return 0;
}
```

---

## 作者：wjmqwq (赞：0)

## 这题实在有点~~简单~~————我这题不过就当场把这个面包吃掉吧唧吧唧......
### 完全可以用if语句我最擅长的就是if语句了
###### **~~好像我也只会做有关if语句的题目了~~**
我这里用单精度————怕通不过

**代码如下**
```
#include<iostream>
using namespace std;
int main()
{
	float a,b,c,d;
	cin>>a>>b>>c>>d;// 输入a,b,c,d;
	if(b/a>d/c) // 比较谁的胜率高，b/a表示高橘君 
	cout<<"TAKAHASHI"<<endl;
	if(b/a==d/c)   // d/c表示青木 
	cout<<"DRAW"<<endl;
	if(b/a<d/c) 
	cout<<"AOKI"<<endl;
	return 0;
}
```
希望过已经被拒绝~~好几次~~了
## 记得输出换行

## [if语句的意思以及作用](https://www.runoob.com/cplusplus/cpp-if-else.html)

---

