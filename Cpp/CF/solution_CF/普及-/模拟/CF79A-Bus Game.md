# Bus Game

## 题目描述

在狐狸Ciel赢得一场编程现场赛之后，她乘坐公共汽车返回她的城堡。 公共汽车的车费是220日元。 她在巴士上遇到了兔子Hanako。 因为他们在公车上感到无聊，所以她们决定玩下面这个游戏。 起初，有一堆硬币，里面包含了x枚100日元硬币和y枚10日元硬币。 他们轮流从中取硬币。 Ciel先手拿。 在每个回合里，她们每次必须从堆中拿出刚好220日元。 在轮到Ciel时，如果她有多种方式可以从中取出220日元，她会选择包含最大数量的100日元硬币的方式。 轮到Hanako时，如果有多种方式可以取出220日元，她会选择包含最多10日元硬币的方式。如果轮到了Ciel或Hanako不能从堆中拿出220日元，那么她就会失败。 请确定这场游戏的胜利者。

## 样例 #1

### 输入

```
2 2
```

### 输出

```
Ciel
```

## 样例 #2

### 输入

```
3 22
```

### 输出

```
Hanako
```

# 题解

## 作者：kon_tori (赞：5)


### 题意
共有 ``x`` 张面值为``100``元的纸币， ``y`` 张面值为``10``元的纸币。
``Ciel``, ``Hanako`` 两人用这些纸币进行一种回合制游戏： ``Ciel`` 每次取出``220`` 元，优先选择 ``100`` 元纸币；
然后 ``Hanako`` 每次取出 ``220`` 元，优先选择 ``10`` 元纸币，由此算一个回合。
直到其中一人不能取出  ``220`` 元的时候，游戏结束，另一方获胜。

### 思路
游戏结束有两种情况：
- 1.当剩余的钱不足 ``220`` 元时；
- 2.当剩余的钱大于 ``220`` 元但无法刚好凑出 ``220`` 元时。

``Ciel`` 优先选择 ``100`` 元纸币，则他有 ``3``
种方案：
- 1.优先选择 ``2`` 张 ``100`` 元的纸币和 ``2`` 张 ``10`` 元的纸币；
- 2.若不能则选择 ``1`` 张 ``100`` 元的纸币和 ``12`` 张 ``10`` 元的纸币； 
- 3.若也不能，则选择 ``22`` 张 ``10`` 元纸币。 

``Hanako`` 优先选择 ``10`` 元纸币，则他有 ``3``
种方案：
- 1.优先选择 ``22`` 张 ``10`` 元的纸币；
- 2.若不能则选择 ``12`` 张 ``10`` 元的纸币和 ``1`` 张 ``100`` 元的纸币； 
- 3.若也不能，则选择 ``2`` 张 ``10`` 元纸币和 ``2`` 张 ``100`` 元的纸币 。 

我们可以根据题意直接模拟求出最后获胜的人。
### 代码实现
```cpp
/* light_chaser */
  #include<bits/stdc++.h>
  using namespace std;
  int c2,c1;//100元纸币的数量和10元纸币的数量
  int main(){
      cin>>c2>>c1;
      while(1){//一直循环直到游戏结束
          if(c2*100+c1*10<220){
              puts("Hanako");
              return 0;
          }//Ciel拿不出220元,直接结束，Hanako获胜
          if( c2>=2 && c1>=2 ){
              c2-=2;
              c1-=2;
          }//Ciel的方案1
          else if( c2>=1 && c1>=12 ){
              c2--;
              c1-=12;
          }//Ciel的方案2
          else if(c1>=22){
              c1-=22;
          }//Ciel的方案3
          else if( (c2>=2 && c1<2) || (c2==1 && c1<12) || (c2==0 && c1<22) ){ 
              puts("Hanako");
              return 0;
          }//Ciel不能刚好凑出220，结束，Hanako获胜
          if(c2*100+c1*10<220){
              puts("Ciel");
              return 0;
          }//Hanako拿不出220元,直接结束，Ciel获胜
          if(c1>=22){
              c1-=22;
          }//Hanako的方案1
          else if( c1>=12 && c2>=1 ){
              c1-=12;
              c2-=1;
          }//Hanako的方案2
          else if( c1>=2 && c2>=2 ){
              c1-=2;
              c2-=2;
          }//Hanako的方案3
          else if( (c2==0 && c1<22) || (c2==1 && c1<12) || (c2>=2 && c1<2) ){
              puts("Ciel");
              return 0;
          }//Hanako不能刚好凑出220，结束，Ciel获胜
      }
  }
 ```
### 后续
 感谢管理员的辛勤付出！
 
蒟蒻的第$5$篇题解，望通过。

~~求赞~~

---

## 作者：WCG2025 (赞：4)

~~一道水模拟~~

看题意
ciel尽可能拿多的100元，当一百不足时就用二十元去补

Hanako则反之，尽可能多的拿十元，不够时就才用一百元去补

就模拟他们拿钱的过程，当钱不够220元或者十元不够两个时，就退出判断一下就好了

```cpp
#include <cstdio>
#include <string>
#include <cstring> 
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long;
int x,y,turn=1;	//一开始是ciel
int main()
{
    cin>>x>>y;
    while(turn)//turn 1代表ciel，turn 2代表Hanako
    {
        if(y<2||100*x+10*y<220) break;//钱不够或者十元不足
        if(turn==1)
        {
            if(x>=2)x-=2,y-=2;
            else if(x==1)x-=1,y-=12;
            else if(x==0)y-=22;
        }
        else if(turn==2)
        {
            if(y>=22)
            y-=22;
            else if(y>=12)
            y-=12,x-=1;
            else if(y>=2)
            y-=2,x-=2;
        }
        turn=3-turn;//ciel完了就是Hanako，反之Hanako完了就是ciel
    }//谁先退出谁就输了
    if(turn==1)
    printf("Hanako");
    else 
    printf("Ciel");
    return 0;
} 

```

---

## 作者：李至擎 (赞：1)

[点我看题](https://www.luogu.com.cn/problem/CF79A)

思路：显然是模拟题，没什么好说的。

方法（以取一次硬币为例）：

- $1.$ 判断钱够不够取；

- $2.$ 如果够取，根据当前取硬币的人进行模拟；

- $3.$ 如果不够取，退出循环，输出答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,w;//n、m是原来的100元和10元的硬币个数，w是当前取硬币的人（0为Ciel取，1为Hanako取） 
int main()
{
	cin>>n>>m;//输入原来的硬币个数 
	while(n*100+m*10>=220&&m>=2)//总钱数不够或者10元不足（至少要有2枚10元硬币才能凑出220元） 
	{
		if(!w)//如果现在轮到Ciel取 
		{
			if(n==0)m-=22;//没有100元的硬币，只能取22枚10元的 
			else if(n==1)n-=1,m-=12;//有1枚100元的硬币，就取1枚100元的和12枚10元的 
			else n-=2,m-=2;//有2枚及以上的100元的硬币，就各取2枚 
		}
		else//如果现在轮到Hanako取 
		{
			if(m<12)n-=2,m-=2;//10元的硬币不足12枚，只能各取2枚 
			else if(m<22)n-=1,m-=12;//10元的硬币不小于12枚但小于22枚，就1枚100元的和12枚10元的  
			else m-=22;//有22枚及以上的10元的硬币，就各取22枚10元的			
		}
		w=!w;//变成下一个人取硬币 
	}
	if(w)cout<<"Ciel";//如果轮到Hanako取时不能再取了，Ciel就获胜了 
	else cout<<"Hanako";//反之，Hanako就获胜了 
	return 0;//结束程序 
}
```

---

## 作者：SqrtSecond (赞：1)

一个回合中，要想用$100$元和$10$元取出$220$元，充其量只有三种情况：

$1.$取$2$张$100$元，$2$张$10$元；

$2.$取$1$张$100$元，$12$张$10$元；

$3.$不取$100$元，$22$张$10$元。

题目中说$\text{Ciel}$优先取$100$元，$\text{Hanako}$优先取$10$元，

**也就是说$\text{Ciel}$优先取第$1$种情况，其次再取第$2$种，最后再取第$3$种，$\text{Hanako}$恰好相反。**

只要有一个回合三种都不能取，那么那个人就输了。

上代码：

```
#include<bits/stdc++.h>
using namespace std;
int x,y;
int main()
{
	cin>>x>>y;
	while(true)
	{
		//Ciel的回合
		if(x>=2&&y>=2)//取2张100元，2张10元
		{
			x-=2;y-=2;
		}
		else if(x>=1&&y>=12)//取1张100元，12张100元 
		{
			x-=1;y-=12;
		} 
		else if(y>=22)//不取100元，取22张10元
		{
			y-=22;
		}
		else//都不行，Ciel输，Hanako赢
		{
			puts("Hanako");
			return 0;
		}
		//Hanako的回合 
		if(y>=22)//不取100元，取22张10元
		{
			y-=22;
		}
		else if(x>=1&&y>=12)//取1张100元，12张100元
		{
			x-=1;y-=12;
		} 
		else if(x>=2&&y>=2)//取2张100元，2张10元
		{
			x-=2;y-=2;
		}
		else//都不行，Hanako输，Ciel赢
		{
			puts("Ciel");
			return 0;
		}
	}
}
```


---

## 作者：LucasXu80 (赞：1)

Python 题解！

这道题的思路就是纯模拟。

那么退出的条件是什么呢？

### 1.留下的总钱数不足220（显然）

### 2.留下的10元张数小于2

这个也很好理解，小于2的话最后的那个20就不可能出来了。

所以就上代码了！

```python
import sys #结束程序用
n,m=map(int, input().split()) #输入
while True: #模拟，一直进行下去直到有人获胜为止
    #Ciel的一轮
    if n*10+m<22 or m<2: #Ciel无法取到220
        print("Hanako") #注意，这个时候Ciel输了，是Hanako赢了！
        sys.exit() #结束程序（如果不结束就会一直运行下去）
    #下面的情况一定保证能取到220
    if n>=2: #100元超过2张，优先取
        n-=2
        m-=2 #2张100，2张10
    elif n==1: #只有1张100
        n-=1
        m-=12 #1张100，12张10
    else: #只剩下n==0的情况
        m-=22 #22张10
    #Hanako的一轮
    if n*10+m<22 or m<2: #无法取到
        print("Ciel") #Hanako输了，Ciel赢了
        sys.exit()
    if m>=22: #有超过22张10，优先
        m-=22
    elif m>=12: #elif去掉了m≥22的情况，这里只有12≤m<22
        n-=1
        m-=12
    else: #最后只剩下m<12
        n-=2
        m-=2
    #循环一轮后又会进入下一轮，所以就又回到Ciel的一轮了
```
CF的题一般不卡时间（都是2s），所以用代码较短的Python打，其实是省时间的。

（虽然慢，但是也不会被卡到TLE）

希望大家喜欢，求过求赞！

---

## 作者：Allanljx (赞：0)

## 思路
模拟，什么时候该这两个人的取220，需要注意他们两个开始取得顺序。具体情况见注释。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b;
	cin>>a>>b;
	for(int i=1;;i++)
	{
		if(i%2==1)//该Ciel了
		{
			if(a>=2)
			{
				if(b>=2)//两张100元和两张10元
				{
					a=a-2;
					b=b-2;
				}
				else//10元不足两张时不可能刚好取出220元
				{
					cout<<"Hanako\n";return 0;
				}
			}
			else if(a==1)
			{
				if(b>=12)//当有一张100元和十二张及以上10元时
				{
					a=a-1;
					b=b-12;
				}
				else
				{
					cout<<"Hanako\n";return 0;
				}
			}
			else if(b>=22)//当10元的超过22张时
			{
				if(b>=22)
				{
					b-=22;
				}
				else {cout<<"Hanako\n";return 0;}
			}
			else//凑不出来
			{
				cout<<"Hanako\n";return 0;
			}
		}
		if(i%2==0)//该Hanako时
		{
			if(b>=22)//10元超过22张时
			{
				b-=22;
				continue;
			}
			if(a>=1)//100元够1张时
			{
				if(b>=12)//10元够十二张时
				{
					a=a-1;
					b=b-12;
					continue;
				}
			}
			if(a>=2)//100元够2张时
			{
				if(b>=2)//10元够2张时
				{
					a=a-2;
					b=b-2;
					continue;
				}
			}
			cout<<"Ciel\n";return 0;//凑不出来
		}
	}
	return 0;
}
```


---

## 作者：stry (赞：0)

今天的我又来刷水题了。

~~其实我认为这道题不配有橙题的称号~~

这道题和普通noip的第一题差不多，就是 
#### 纯模拟

这道题判断是否输的条件有两个：

### 剩下的钱没够220元或剩下十元的钱不够两张。

假如轮到Ciel取时有3种情况
|10元  |100元  |
| -----------: | -----------: |
|2张  |2张  |
|12张 |1张  |
|22张 |0张  |

**注意：从上往下依次判断，如果可执行就执行前面的**

同样假如轮到Hanako取时也有3种情况
|10元  |100元  |
| -----------: | -----------: |
|22张|0张  |
|12张|1张  |
|2张 |2张  |

**同样注意：从上往下依次判断，如果可执行就执行前面的**

说了那么久，直接上程序吧
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int main()
{
    int a,b;cin>>a>>b;
    for(int i=0;;i++)
    {
        if(a*100+b*10<220&&b<2){if(i%2==0){cout<<"Ciel";return 0;}else{cout<<"Hanako";return 0;}}//判断是否满足退出条件
        if(i%2==1)//判断是否是Ciel取钱
        {
        if(a>=2){a=a-2;b=b-2;} 
        else{if(i>1){a--;b=b-12;}else{b=b-22;}}
        //取钱过程判断
        }
        else
        {
        if(b>=22){b=b-22;}
        else{if(b>=12){a--;b=b-12;} else{b=b-2;a=a-2;}} 
        //取钱过程判断
        }
    }
}
```
**注意：全文共有三处错误，误抄！！**

完美撒花。

---

## 作者：Daidly (赞：0)

[更好的阅读体验](https://www.luogu.com.cn/blog/271736/solution-cf79a)

原题：[CF79A Bus Game](https://www.luogu.com.cn/problem/CF79A)

建议标签为：模拟，注意几个点就出来了：

- Ciel为先手，且$100$元要的最多；Hanako为后手，且$10$元要的最多。

- 不仅要关心所需最多的，还要关心另一个的个数与总价值。

- 因为最重要的是十元（因为无论是谁，$200$元可以用$10$元代替，但那个$20$可不能用$100$元代替），所以要同时判断十元个数与总数。

- 当$100$元要的最多时，注意$100$元的个数，看是否能取满，不能的话用十元代替；十元也是，不能的话，退一步用一个$100$元代替十个$10$元。

这样，代码就应运而出了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,ans=1;//先手为1=>Ciel
int t[2]={0,1};//我这里用了一个数组储存，其他方式也行
//0为Hanako，1为Ciel
int main(){
	cin>>x>>y;
	for(int i=1;;++i){
		if(y<2||100*x+10*y<220){//判断y值和总值，正如第二点所说
			break;
		}
		if(i%2==1){//如果为Ciel
			if(x>=2){//判断最多能去多少个x，不同的范围，不同的减值
				x-=2;
				y-=2;
			}else{
				if(x==1){
					x-=1;
					y-=12;
				}else{
					y-=22;
				}
			}
		}else{//如果为Hanako
			if(y>=22){//判断最多能去多少个y
				y-=22;
			}else{
				if(y>=12){
					x-=1;
					y-=12;
				}else{
					x-=2;
					y-=2;
				}
			}
		}
		ans=t[1-ans];//注意这里统计的是将要输的人的名字
	}
	if(ans==0){//如果输的人是Hanako，那么Ciel就赢
		cout<<"Ciel";
	}else{//反之
	    cout<<"Hanako";
	}
    return 0;
}
```
希望通过，谢谢！

---

## 作者：chenkaiwen (赞：0)

这个是一道比较明显的模拟题，我们可以总结出以下规律：

对于狐狸有三种情况可以选择(狐狸优先选择100元，)：

1. x>=2&&y>=2
2. x>=1&&y>=12
3. y>=22

对于兔子有三种情况可以选择(兔子优先选择10元，)：

1. y>=22
2. x>=1&&y>=12
3. x>=2&&y>=2

那么我们只需要用一个无限循环就可以了，其他的细节我会在代码的注释中写出这里就不多说了，代码如下：

[![](https://cdn.luogu.com.cn/upload/image_hosting/bhfc7ota.png)证明](https://www.luogu.com.cn/record/32116072)

```cpp
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
long long read() {//快读，加快输入 
	long long f=1,w=0;
	char c=getchar();
	while(c>'9'||c<'0') {
		c=getchar();
		if(c=='-')f=-1;
	}
	while(c<='9'&&c>='0') {
		w=(w<<3)+(w<<1)+c-'0';
		c=getchar();
	}
	return w*f;
}
int x,y;
bool Ciel() {
	if(x>=2) {
		if(y>=2) {
			x-=2,y-=2;
			return 1;
		} else {
			cout<<"Hanako"<<endl;//如果狐狸输了，则输出兔子 
			return 0;
		}
	} else if(x>=1) {
		if(y>=12) {
			x-=1,y-=12;
			return 1;
		} else {
			cout<<"Hanako"<<endl;
			return 0;
		}
	} else {
		if(y>=22) {
			y-=22;
			return 1;
		} else {
			cout<<"Hanako"<<endl;
			return 0;
		}
	}
}
bool Hanako() {
	if(y>=22) {
		y-=22;
		return 1;
	} else if(y>=12) {
		if(x>=1) {
			x-=1,y-=12;
			return 1;
		} else {
			cout<<"Ciel"<<endl;//如果兔子输了，则输出狐狸 
			return 0;
		}
	} else if(y>=2) {
		if(x>=2) {
			x-=2,y-=2;
			return 1;
		} else {
			cout<<"Ciel"<<endl;
			return 0;
		}
	} else {
		cout<<"Ciel"<<endl;
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	x=read(),y=read();//输入 
	bool Ans=1;//是否需要继续判断 
	while(1) {
		if(Ans==1) {
			Ans=Ciel();//如果返回值是0，那么下面就不用继续了 
		} else {
			return 0;//弹出循环 
		}
		if(Ans==1) {
			Ans=Hanako();
		} else {
			return 0;//弹出循环 
		}
	}
	return 0;
}
```
### 谢谢观赏

---

## 作者：monstersqwq (赞：0)

一道模拟题。

思路：无限循环，用 a 记录100元的数量，用 b 记录10元的数量。每次如果 $a \times 100+b \times 10<220$ 或 $b<2$就直接输出不是此回合取的人然后结束程序，其它如果该 Ciel 拿就用 $a$ 从大往小分别枚举（即 $a \ge 2,a=1,a=0$ 三种情况），如果该 Hanako 拿就从 $b$ 从大往小枚举（即 $a \ge 22,12\le a < 22,a<12$ 三种情况），每次更改取的人。（bool 类型为取反，即!）

~~丑陋~~的代码：
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
	int a,b;//a存储100元的数量，b存储10元的数量
	bool s=false;//s=false表示该Ciel取，true表示该Hanako取
	cin>>a>>b;
	while(1)
	{
		if(s==false)//表示该Ciel取 
		{
			if(100*a+10*b<220||b<2)
			{
				cout<<"Hanako"<<endl;
				break;
			}
			if(a>=2)
			{
				a-=2;
				b-=2;
			}
			else if(a==1)
			{
				a-=1;
				b-=12;
			}
			else if(a==0)
			{
				b-=22;
			}
		}
		else//表示该Hanako 
		{
			if(100*a+10*b<220||b<2)
			{
				cout<<"Ciel"<<endl;
				break;
			}
			if(b>=22)
			{
				b-=22;
			}
			else if(b>=12)
			{
				b-=12;
				a-=1;
			}
			else if(b>=2)
			{
				a-=2;
				b-=2;
			}
		}
		s=!s;
	}
	return 0;
}
```


---

## 作者：hensier (赞：0)

这道题可以使用暴力算法。暴力的原因很简单，因为题目中说每次要凑齐$220$元，而不是$10x$元。

我们知道，这道题目可以一直循环地做——当然肯定要有出口。出口就是当任意一种钱币为负。

我们可以用$while(1)$或者$for(;;)$来实现循环，并设置一个$bool$变量记录是谁取硬币。然后模拟即可。

$AC$代码：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int x,y,a,b;//x，y表示初始的100、10硬币各有多少
bool f;//记录轮到谁
int main()
{
    cin>>x>>y;
    while(1)
    {
        f=!f;//每次都取反
        if(f)//这代表轮到了Ciel
        {
            a=min(2,x);//Ciel尽量取100的，所以最大是2
            if(a==2)//下面进行逐一判断，注意顺序不能反
            {
                if(y<2)//不够就输了
                {
                    printf("Hanako");
                    break;
                }
                x-=2;
                y-=2;//减掉
            }
            if(a==1)//同上
            {
                if(y<12)
                {
                    printf("Hanako");
                    break;
                }
                x--;
                y-=12;
            }
            if(!a)
            {
                if(y<22)
                {
                    printf("Hanako");
                    break;
                }
                y-=22;
            }
        }
        else
        {
            if(y>21)b=22;//剩余数量大于等于22就取22
            else if(y>11)b=12;//否则大于等于12就取12
            else if(y>1)b=2;//如果大于等于2就取2
            else//不够2就输了
            {
                printf("Ciel");
                break;
            }
            if(b==22)y-=22;//是22就减掉22个10的硬币
            if(b==12)//是12就判断是否有100硬币
            {
                if(!x)//没有就输了
                {
                    printf("Ciel");
                    break;
                }
                y-=12;
                x--;
            }
            if(b==2)//同上
            {
                if(x<2)
                {
                    printf("Ciel");
                    break;
                }
                y-=2;
                x-=2;
            }
        }
    }
    return 0;
}
```

---

