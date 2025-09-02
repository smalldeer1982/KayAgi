# 電子レンジ (Microwave)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2017yo/tasks/joi2017yo_a

JOI 君は食事の準備のため，$ A $ ℃の肉を電子レンジで $ B $ ℃まで温めようとしている．肉は温度が $ 0 $ ℃未満のとき凍っている．また，温度が $ 0 $ ℃より高いとき凍っていない．温度がちょうど $ 0 $ ℃のときの肉の状態は，凍っている場合と，凍っていない場合の両方があり得る．

JOI 君は，肉の加熱にかかる時間は以下のようになると仮定して，肉を温めるのにかかる時間を見積もることにした．

- 肉が凍っていて，その温度が $ 0 $ ℃より小さいとき： $ C $ 秒で $ 1 $ ℃温まる．
- 肉が凍っていて，その温度がちょうど $ 0 $ ℃のとき： $ D $ 秒で肉が解凍され，凍っていない状態になる．
- 肉が凍っていないとき： $ E $ 秒で $ 1 $ ℃温まる．

この見積もりにおいて，肉を $ B $ ℃にするのに何秒かかるかを求めよ．

- - - - - -

## 说明/提示

### Sample Explanation 1

入出力例 $ 1 $ では，もともとの肉は $ -10 $ ℃で凍っている．かかる時間は以下のようになる． - $ -10 $ ℃から $ 0 $ ℃まで温めるのに $ 5\ \times\ 10\ =\ 50 $ 秒． - $ 0 $ ℃の肉を解凍するのに $ 10 $ 秒． - $ 0 $ ℃から $ 20 $ ℃まで温めるのに $ 3\ \times\ 20\ =\ 60 $ 秒． したがって，かかる時間の合計は $ 120 $ 秒である． - - - - - -

### Sample Explanation 2

入出力例 $ 2 $ では，もともとの肉は凍っていない．したがって，肉を $ 35 $ ℃から $ 92 $ ℃まで温めるのにかかる時間は $ 627 $ 秒である．

## 样例 #1

### 输入

```
-10
20
5
10
3```

### 输出

```
120```

## 样例 #2

### 输入

```
35
92
31
50
11```

### 输出

```
627```

# 题解

## 作者：封禁用户 (赞：4)

这道题@AC我最萌 已经给出了可耐的翻译，应该都能懂题意，~~当时我以为b有可能低于0度~~，其实并没有，一遍AC。

你们最喜欢的环节来了，附**AC代码：**
```cpp
#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d,e;
    cin>>a>>b>>c>>d>>e;
    if(a>0)
    {
        cout<<(b-a)*e<<endl;
        return 0;
    }
    else
    {
        cout<<(0-a)*c+d+(b-0)*e<<endl;
        return 0;
    }
    return 0;
 } 
```
如果有锅请私信我。
望管理员通过！！！

---

## 作者：meyi (赞：2)

# 或许是目前最短的代码了吧（笑）
## 这是一道纯模拟题，按照题意模拟即可。
### 上代码：
```cpp
#include<cstdio>
main(){
	int a,b,c,d,e;
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
	printf("%d\n",a<=0?-a*c+d+b*e:(b-a)*e);
    /*若a<=0，则需要在零度以下加热-a次，每次需要c秒，在零度需要d秒，
      在零度以上需要加热b次，每次需要e秒。
      若a>0，则需要加热b-a次，每次需要e秒。
      此处使用三目运算符，省去if语句，所以码量少（笑）*/
}
```

---

## 作者：oimaster (赞：1)

绝对一道很水的黄题！按照题意模拟即可！

注意！当牛排温度为 $0$ 时解冻后温度并不会变成 $1$，所以在写的时候这一步容易出现问题，你的答案应加上 $d+e$！

然后就可以用一点点 `Python` 水过去了！

```python
a=int(input())
b=int(input())
c=int(input())
d=int(input())
e=int(input())
tot=0
while a<b:
    if a<0:
        tot+=c
    elif a==0:
        tot+=d+e
    else:
        tot+=e
    a+=1
print(tot)
```

---

## 作者：Zenith_Yeh (赞：1)

这道题只要分四种情况讨论即可。

- 当 $(a<0,b<0)$ 时，我们只需要算 $(b-a)*c$ 即可。
- 当 $(a<0,b\geq 0)$ 时，我们只需要算 $\operatorname{abs}(a)*c+d+b*e$ 即可。 （ $\operatorname{abs}(a)$ 就是 $a$ 到 $0$ 度的距离 ）
- 当 $(a=0)$ 时，我们只需要算 $d+b*e$ 即可。
- 当 $(a=0)$ 时，我们只需要算 $(b-a)*e$ 即可。

**上菜:**
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{   int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c))f|=(c=='-'),c=getchar();
    while(isdigit(c))x=x*10+(c&15),c=getchar();
    return f?-x:x;
}
int main()
{   int a=read(),b=read(),c=read(),d=read(),e=read(),ans;
    if(a<0)//四种情况。
    {   if(b<=0)ans=(b-a)*c;
        else ans=abs(a)*c+d+b*e;
    }
    else 
    {   if(a==0)ans=d+b*e;
        else ans=(b-a)*e;
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：wushuang0828 (赞：1)

Pascal题解一篇，可能跟其他大佬比起来我的方法麻烦了一些，但这也是一种方法……

思路：for循环判断如果i<0就加上c，如果i=0就加上d，如果i>0就加上e，特判也必须加，如果a<0那么s就要加上e

具体看代码：
```pascal
var
 a,b,c,d,e,i,s:longint;
begin
 readln(a);//最初牛排为a度
 readln(b);//最终要烤成b度
 readln(c);//如果温度低于0度，就加上的c度
 readln(d);//如果温度等于0度，就加上的d度
 readln(e);//如果温度大于0度，就加上的e度
 for i:=a to b-1 do//循环从a度到b度过程
  begin
   if i<0 then s:=s+c;//如果牛排小于0度每加热一度需要c秒
   if i=0 then s:=s+d;//如果温度等于0度时需要d秒解冻
   if i>0 then s:=s+e;//如果温度高于0度时每加热一度要e秒
  end;
 if a<0 then s:=s+e;//如果a<0那么s就要加上e
 writeln(s);//输出
end.
```

---

## 作者：tommychen (赞：0)

### 题面
[洛谷题面](https://www.luogu.com.cn/problem/AT2447) 
[AT题面](https://atcoder.jp/contests/joi2017yo/tasks/joi2017yo_a)

我们[AC我最萌](https://www.luogu.com.cn/user/80358)的翻译已经足够直白了吧,在这儿我就不再做解释了。
### 思路
看到题我们就会想到分情况讨论。

当 $a$ $\lt$ $0$时,

答案为$(b-a)$ $\times$ $e$。其中$b-a$为需要加热多少度，$(b-a) $ $\times$ $e$表示总共需要的秒数。

当 $a$ $\geq$ $0$时,

答案为$fabs(a)$ $\times$ $c+d+b$ $\times$ $e$。其中$fabs(a)$ $\times$ $c$表示0度以下需要多少秒，$b$ $\times$ $e$表示0度以上需要多少秒。
    
我们按照上面的情况进行模拟即可。
### 注意点
**统计总秒数的变量一定要清0！！！**

**AT的题目一定要打换行！！！**
(我可是被这坑过的/kk)
### 代码
上菜咯！
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
	int a,b,c,d,e;
	cin>>a>>b>>c>>d>>e;//按照题目条件输入
	int sum=0;//统计总秒数
	if(a>0){//第一种情况
		sum=(b-a)*e;
	}else{//第二种情况，这里用else是因为所有的情况除了第一种就是第二种
		sum=fabs(a)*c+d+b*e;
	}
	cout<<sum<<endl;//输出结果
	return 0;//结束啦(*^▽^*)
}
```


---

## 作者：梦游的小雪球 (赞：0)

这道题的翻译其实已经很直白了，没有什么干扰信息，所以我们直接上代码（思路都在注释里）
## AC代码
### 请认真仔细的读完每一个注释
```
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,s;//与翻译中的一一对应
int main( ){
	cin>>a>>b>>c>>d>>e;//输入
	if(a<0)//将牛排烤到0度
		s=s+abs(a)*c;//时间一次性增加
	if(a==0)
		s=s+d;//总时间加上解冻的时间
	s=s+(b-a)*e;//剩下的：将牛排从0到烤b度
	cout<<s<<endl;//输出
	return 0;//完美结束
}
```


---

## 作者：rui_er (赞：0)

根据题意，我们可以把数据分成三类：

- $a<0, b<0$
- $a<0, b>0$
- $a>0, b>0$

根据题意列出公式计算即可。

C++：

```cpp
#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d, e;
    cin>>a>>b>>c>>d>>e;
    int ans;
    if(a < 0)
    {
        if(b < 0) ans = (b - a) * c;
        else ans = (-a) * c + d + b * e;
    }
    else
    {
        ans = (b - a) * e;
    }
    cout<<ans<<endl;
    return 0;
}
```

Python：

```python
a, b, c, d, e = int(input()), int(input()), int(input()), int(input()), int(input())
if a<0:
	if b<0:
    	print((b-a)*c)
    else:
    	print((-a)*c+d+b*e)
else:
	print((b-a)*e)
```

---

## 作者：政凯 (赞：0)

一个人，要把一块为a度的肉加热到b度（b肯定大于等于a），把小于0度的肉加热到0度，每加热一度要c秒；把0度的肉加热到1度，每加热一度要d秒；把大于0度的肉加热到1度以上，每加热一度要e秒。

因此，
1、如果a小于0，加热到0度需要(0-a）*c秒
2、如果a<=0并且0<b，从0度到加热到1度需要d秒
3、如果b>0，从1度到加热到b度需要b-max(0,a)*e秒
      

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long a,b,c,d,e,h,bb;
int main()
{
	cin>>a>>b>>c>>d>>e;
	if (a<0) h+=(min(b,bb)-a)*c;//是按第一步操作
	if (a<=0&&0<b) h+=d; //是按第二步操作
	if (b>0) h+=(b-max(bb,a))*e; //是按第三步操作
	cout<<h<<endl;
	return 0;
}
```


---

## 作者：xujian (赞：0)

既然有一道这么水的黄题挡在面前，~~当然是先秒了啦~~~

标准的C语言，9行代码AC。

### [评测记录](https://www.luogu.org/recordnew/show/15918944)

## 思路：分3种情况模拟：

### 第一种：要先加热再解冻再加热

这里主要要注意的是解冻前加热的时间，因为a是负数，所以直接取a会导致加热时间也是负数，所以可以用abs取绝对值或直接写（0-a）。

### 顺便提一下：abs头文件<math.h>，浮点数绝对值要用fabs。

### 第二种：直接解冻再加热

不知道有没有这种情况，这中情况是很好求的，因为初温就是0度，所以加热时间就是b。

### 第三种：直接加热

这里的话只要用到abe三个数，因为都是正数，所以加热时间就是（b-a），就不多解释了。

好了，该上代码了。

~~求管理大大给过。。。~~

```c
#include<stdio.h>
int a,b,c,d,e;
int main(){
    scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
    if(a<0)printf("%d\n",abs(a)*c+d+b*e);
    else if(a==0)printf("%d\n",d+b*e);
    else printf("%d\n",(b-a)*e);
    return 0;
}
```

---

## 作者：CZQ_King (赞：0)

一道模拟题~~（放在任务计划好久了QWQ）~~

------------

做法：一个$while$循环模拟，记得判断$a$是否小于$0$，如果小于，加上一个$e$

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,ans,i;
int main(){
    cin>>a>>b>>c>>d>>e;
    i=a;//用i来模拟温度
    while(i!=b){//让i直到指定温度b
        if(i<0)ans+=c;//如果被冷冻
        if(i==0)ans+=d;//解冻
        if(i>0)ans+=e;//加热
        i++;//温度++
    }
    cout<<ans+((a<0)?1:0)*e<<endl;//如果a<0，最加上一个e
    return 0;
}
```

---

