# Food on the Plane

## 题目描述

一架新的喷气式飞机有无限行，从驾驶舱到机尾从1开始用正整数编号。每排有六个座位，用字母“a”到“f”表示。座位'a'、'b'、'c'位于过道的左侧（如果有人朝驾驶舱方向看），而座位'd'、'e'、'f'位于右侧。座位'A'和'F'靠近窗户，座位'C'和'D'靠近过道。
    现在是午餐时间，两名乘务员刚开始供应食物。他们从第一排移到最后一排，由于他们中间有食物推车，他们总是保持两排的距离。因此，在开始时，第一个服务员服务第1行，而第二个乘务员服务第3行。当两行都完成服务后，它们向前移动一行(第一个乘务员服务第2行，第二个乘务员服务第4行)。然后他们向前移动三行，第一个乘务员服务第5行，第二个服务员服务第7行。然后他们再向前移动一行，以此类推。
    乘务员以同样的速度工作：服务一名乘客需要1秒钟，向前移动一排需要1秒钟。每位乘务员首先在过道右侧的座位上为乘客服务，然后在过道左侧的座位上为乘客服务（如果有人朝驾驶舱方向看的话）。此外，从窗口到过道，他们总是按顺序为乘客服务。因此，第一个在每排接收食物的乘客位于“F”座，最后一个在“C”座（假设所有座位都有人）。
    Vasya在N排S座，她想知道在她吃午饭前会等多少秒。

## 说明/提示

第一个样例中：第一个乘务员首先为Vasya服务，所以瓦西亚在1秒钟后吃午饭。
    第二个样例中：乘务员花费6s为第1行和第3行中的每个人服务，然后他们将在1s内向前移动一行。当他们第一次提供位于过道右侧的座位时，Vasya必须再等3s。总共6+1+3=10s。

## 样例 #1

### 输入

```
1f
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2d
```

### 输出

```
10
```

## 样例 #3

### 输入

```
4a
```

### 输出

```
11
```

## 样例 #4

### 输入

```
5e
```

### 输出

```
18
```

# 题解

## 作者：tzytttzy (赞：6)

# 本题题解

### （既是本人的第一篇题解，又是本题的第一篇题解，233）

这题不算难，主要是看仔细了就行。


------------

### 1.首先，考虑座位的排数：

第1排和第3排（第2排和第4排一样）的送餐是同步进行的，即顺序也是相同的。

#### 那么事实上第一排和第三排是等价的。

在得到了这个重要条件之后，那么代码可以这样写：


------------


    if((m-1)%4!=0 && (m-1)%2==0) m=m-2;
    if(m%4==0) m=m-2;
    


------------


这就是将他们替换了。

#### 下面我们发现，餐车的运动是以4排为一个循环的 

那就很简单了

每4排，餐车花费的时间是16秒（~~掰掰手指头算一下~~）

所以：


------------

    c=m%4；//处于第几个循环
    t=((m-c)/4)*16;

------------

我们又发现，送一排餐的时间是6s，加上移动一格是1s，则同一循环节内的单双排送餐时间差7s



------------

    if(c==2) t=t+7;

------------

### 2.然后判断座位

根据题设，送餐顺序为F-E-D-A-B-C

------------
    if(n=='a') t+=4;
    if(n=='b') t+=5;
    if(n=='c') t+=6;
    if(n=='d') t+=3;
    if(n=='e') t+=2;
    if(n=='f') t+=1;

------------
于是这道题就完美地结束啦QWQ

------------
最后，附上代码：

C++代码如下：（虽然写的不算最简，但一看就明白了）

    #include<iostream> 
    #include<cstring>
    using namespace std;
    int main(void)
    {
        long long m,c,t=0;
        char n;
        cin>>m>>n;
        if((m-1)%4!=0 && (m-1)%2==0) m=m-2;
        if(m%4==0) m=m-2;
        c=m%4;
        t=((m-c)/4)*16;
        if(c==2) t=t+7;
        if(n=='a') t+=4;
        if(n=='b') t+=5;
        if(n=='c') t+=6;
        if(n=='d') t+=3;
        if(n=='e') t+=2;
        if(n=='f') t+=1;
        cout<<t;
        return 0;
    }

------------

是不是很简单啊~

只要判断（if）语句

连循环都可以不用呢~

谢谢~（~~纳尼居然有人看完了这么无聊的题解太感动了~~）

---

## 作者：黄文烽 (赞：1)

## CF725B题解
[题目传送门](https://www.luogu.com.cn/problem/CF725B)
### 题意简化
飞机上有两个服务员,他们会按照$F\rightarrow E\rightarrow D\rightarrow A\rightarrow B\rightarrow C$的顺序送餐,并且每服务完一排就会向前移动$1\rightarrow 3$排。

已知服务一个客人需要$1s$,运动一排需要$1s$。求服务到你需要多少时间。
### 模拟
既然服务员前进的排数有规律,那么就可以模拟。

我们设立两个变量$tmp1$和$tmp2$,分别保存第一个服务员的当前位置和第二个服务员的当前位置,然后设立一个变量$ans$,记录当前用时。

所以我们可以知道,当$tmp1\mod 4=2$时,$tmp1+1$,否则$tmp1+3$。$tmp2\mod4=3$时,$tmp2+1$,否则$tmp2+3$。

然后由于服务员是按照$F\rightarrow E\rightarrow D\rightarrow A\rightarrow B\rightarrow C$的顺序送餐,所以我们的答案需要根据不同的字符增加不同的数量,这个操作可以写一个$solve$函数解决。

得代码如下:
### Code1:
```cpp
#include<iostream>

using namespace std;

long long n, ans, tmp1 = 1, tmp2 = 3; //因为题目的数据范围开到了10的18次方,所以要开long long 
char ch;

void solve(){ //代码不是最简的,但适合我这种蒟蒻
	switch(ch){
	    case 'a':{
	    	ans += 4;
			break;
		} 
		case 'b':{
			ans += 5;
			break;
		}
		case 'c':{
			ans += 6;
			break;
		}
		case 'd':{
			ans += 3;
			break;
		}
		case 'e':{
			ans += 2;
			break;
		}
		case 'f':{
			ans += 1;
			break;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); //优化cin 
	
	cin >> n >> ch;
	
	solve();
	
	while(tmp1 != n && tmp2 != n){
		if(tmp1 % 4 == 1){  
			tmp1++, tmp2++; //向前走一排 
			ans += 7; //需要1+6=7秒(需要服务6个乘客) 
		} else {
			tmp1 += 3, tmp2 += 3; //向前走3排 
			ans += 9; //需要3+6=9秒 
		}
	}
	
	cout << ans << endl;
	
	return 0;
} 
```
### 数学
然而,模拟的结果是惨痛的——**[TLE](https://www.luogu.com.cn/record/41491113)**

模拟的时间复杂度是$O(n)$的($n$为排号),数据范围是$1\leq n\leq 10^{18}$,那么要过肯定要用$O(\log n)$的时间复杂度以下。

然而本蒟蒻不会写$O(\log n)$的算法,所以直接使用了数学解法。

我们可以发现服务员的服务是以$4$排为周期的,而每服务$4$列需要$16s$。

设当前位置为第$x$列,第$y$列需要的时间为$t_y$,若$x\mod 4 > 2$或$x\mod 4=0$,则$t_x=t_{x-2}$,所以我们只需要考虑两种情况:

>$x\mod 4=1$

>$x\mod 4=2$

我们可以得出$t_x=\lfloor x/4\rfloor * 16(x\mod 4=1),t_x=\lfloor x*4\rfloor * 16+7(x\mod 4=2)$($\lfloor x\rfloor$表示$x$向下取整)

所以我们就得到了AC代码(时间复杂度$O(1)$)如下:
```cpp
#include<iostream>

using namespace std;

long long n, ans; //因为题目的数据范围开到了10的18次方,所以要开long long 
char ch;

void solve(){ //代码不是最简的,但适合我这种蒟蒻
	switch(ch){
	    case 'a':{
	    	ans += 4;
			break;
		} 
		case 'b':{
			ans += 5;
			break;
		}
		case 'c':{
			ans += 6;
			break;
		}
		case 'd':{
			ans += 3;
			break;
		}
		case 'e':{
			ans += 2;
			break;
		}
		case 'f':{
			ans += 1;
			break;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); //优化cin 
	
	cin >> n >> ch;
	
	solve();
	
	if(n % 4 > 2 || n % 4 == 0) n -= 2; //若x % 4 > 2或x % 4 = 0,则t[x] = t[x-2]$
	
	if(n % 4 == 1){
		ans += (n / 4) * 16;
	} else {
		ans += (n / 4) * 16 + 7;
	}
	
	cout << ans << endl;
	
	return 0;
} 
```
### 结果:[AC](https://www.luogu.com.cn/record/41544478)

---

## 作者：Qianh (赞：1)

# 蒟蒻的第一篇题解
## 1.首先先考虑排的顺序
因为是两人隔着一排送餐，所以送完四排后会集体往后移动一排         
故要判断是否需要减去那一排所需的时间   
故得出if语句
```cpp
if((n + n % 2) % 4 == 0){   
	x = n / 2;   
}   
else{
	x = n - n % 2;
	x = x / 2 + 1;
}
 ```
##  2.然后考虑列的顺序  
题目中说$ $
“每位乘务员首先在过道右侧的座位上为乘客服务，然后在过道左侧的座位上为乘客服务（如果有人朝驾驶舱方向看的话）。此外，从窗口到过道，他们总是按顺序为乘客服务。因此，第一个在每排接收食物的乘客位于“F”座，最后一个在“C”座（假设所有座位都有人）”  
说白了就是列的顺序为：“fedabc”   
故得出判断函数：
```cpp
int ans(char s){
	if(s == 'f')return 1;
	if(s == 'e')return 2;
	if(s == 'd')return 3;
	if(s == 'a')return 4;
	if(s == 'b')return 5;
	if(s == 'c')return 6;
}
  ```
  将代码整合，得到代码
```cpp
  #include <iostream>

using namespace std;
int n;
char s;
int ans(char s){
	if(s == 'f') return 1;
	if(s == 'e') return 2;
	if(s == 'd') return 3;
	if(s == 'a') return 4;
	if(s == 'b') return 5;
	return 6;
}
int main(){
	cin >> n >> s;
	int x;
	if((n + n % 2) % 4 == 0){
		x = n / 2;
	}
	else{
		x = n - n % 2;
		x = x / 2 + 1;
	}
	cout << x * 7 - 7 + (x - 1) / 2 * 2 + ans(s) << endl;
	return 0;
}
 ```
 然后发现
3.考虑数据范围   
蒟蒻写完代码后高高兴兴地将自己的代码交上去，结果
### [WA](https://www.luogu.com.cn/record/41377713)
不是不是吧不会我的思路错了吧   
然后蒟蒻去看了一下题目的数据范围然后发现
### 1 <= n <= 10 ^ 18
这坑人的数据范围   
于是蒟蒻把所有的int都改成了longlong    
代码如下
```cpp
#include <iostream>

using namespace std;
long long n;
char s;
int ans(char s){
	if(s == 'f')return 1;
	if(s == 'e')return 2;
	if(s == 'd')return 3;
	if(s == 'a')return 4;
	if(s == 'b')return 5;
	if(s == 'c')return 6;
}
int main(){
	cin >> n >> s;
	long long x;
	if((n + n % 2) % 4 == 0){
		x = n / 2;
	}
	else{
		x = n - n % 2;
		x = x / 2 + 1;
	}
	cout << (x - 1) * 8 - (x - 1) % 2 + ans(s) << endl;
	return 0;
}
 ```
 然后发现
###  [AC](https://www.luogu.com.cn/record/41377127)
泪流满面啊   
蒟蒻的第一篇题解，请各位大佬多多支持（））

---

## 作者：lelml (赞：0)

## 思路

通过枚举可以发现，每个人发了两排就会往前三排,也就是以四排为一个循环。因此,我们通过判断一个数模四的余数即可算出时间。具体方法见代码。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ll a,t=0;
	char x;
	cin>>a>>x;
	if(a%4==3||a%4==0) a-=2;//如果除以四余0或3，由第一个人送，减二即可把时间点统一到第二个人方便计算
	t=((a-a%4)/4)*16;//计算时间
	if(a%4==2||a%4==0) t+=7;
	if(x=='f') t+=1; 
	if(x=='e') t+=2;
	if(x=='d') t+=3;
	if(x=='a') t+=4;
	if(x=='b') t+=5;
	if(x=='c') t+=6;
	cout<<t;
}
```


---

## 作者：Yydy_RedDust (赞：0)

~~不知道怎么的突然就跳到这道水题了，既然来都来了，那就水篇题解吧。~~


------------
根据题意，我们不难发现服务员的服务顺序是一个循环，且每四排为一个循环，每个循环需要耗费 **16 秒**。  
得到了这个以后，我们还能发现服务员服务完一排需要耗费 **7 秒**。  
由上我们就能求出服务员到当前排的需要等待的时间。  
最后，我们求出服务员在当前座位耗费的时间即可。  
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; //long long 化简，不开 long long 会WA
int read() //快读，这题里貌似没什么用 awa
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
char b;
ll a;
int main()
{
	cin>>a>>b;
	ll ans=(a-1)/4*16; //需要等待的循环数所花的时间
	if(a%2==0)
		ans+=7; //如果在偶数行，需要多等待一排
	if(b=='f')
		ans++;
	else if(b=='e')
		ans+=2;
	else if(b=='d')
		ans+=3;
	else if(b=='a')
		ans+=4;
	else if(b=='b')
		ans+=5;
	else if(b=='c')
		ans+=6; //不同座位需要等待的时间
	cout<<ans;
	return 0; //完美
}
```


---

## 作者：linyinuo2008 (赞：0)

这题上来一看肯定可以通过一些运算和特判直接过啊！

# 1、题目分析

几个要点：

- 强制开 $long$ $long$（数据远超过$2 \times 10^9$）。

- 第一排与第三排同步运行，第二排第四排同理。

- 顺序不为从左向右，每过一个就向前走三步。

- 由此，每四排为一个周期。

# 2、模拟

我们先计算出所在位置在第几个周期，然后根据编号字母进行特判，计算时间。

有一个点是要先把第3排变为第1排，第4排变为第2排。

每个周期需要花16个时间，拿完整周期数乘一下，再根据字符加相应时间即可。

一起来模拟一下：

例： `7f`

由于第二排与第四排同步，处理方便起见，变成 `5f`，同时计算出这是第2个周期，时间为：$1 \times 16$ $+1$ $=$ $17$

PS:这种题最好的方法是拿纸笔模拟。

详见代码注释。

# 3、代码

贴上代码：

```cpp
#include <iostream>
using namespace std;
long long n,time=0;
int main()
{
	char c;
	cin>>n>>c;
	if(n%4==3||n%4==0)//如果在所在周期的第3行或第四行，那么变为第一行或第二行
		n-=2;
	long long num=n%4;//比整周期多出来的排数
	time+=(n-num)/4*16;
	//计算有多少个周期，然后乘每个周期所需时间
	if(num==2)  time+=7;
    //第二排的要先花7秒给第一排的人送饭
    
    //枚举可能所在位置
	if(c=='c')  time+=6;
	else if(c=='b')  time+=5;
	else if(c=='a')  time+=4;
	else if(c=='d')  time+=3;
	else if(c=='e')  time+=2;
	else if(c=='f')  time+=1;
	cout<<time;
	return 0;
} 
```

就这样这题就没了，复杂度$O(1)$，怎么样？

管理员大大求通过！

## 若有错误，欢迎指出！


---

## 作者：Peter0701 (赞：0)

观察题目条件，容易发现乘务员的服务以四排为一个循环，如 $1+3 \rightarrow 2+4 \rightarrow 5+7 \rightarrow 6+8$ 就是两个循环。在每个循环中，乘务员只移动一次。在每个循环中，乘务员共移动两次次。具体来说，从每个循环中 $mod$ $4$ $==$ $1$ 的一排前进到 $mod$ $4$ $==$ $2$ 的一排需要花费 $1$ 秒，而从每个循环中 $mod$ $4$ $==$ $2$ 的一排前进到下一个循环 $mod$ $4$ $==$ $1$ 的一排时需要花费 $3$ 秒。

那么这题就可以通过分类讨论的方式解决，可以按照排数 $n$ 分为以下四类：

情况一： $n$ $mod$ $4$ $==$ $1$ 时，已经经过了 $(n-1)/4$ 个循环，每个循环开始到下一个循环之前共用了 $4×6/2+1+3=16$ 秒，故在第 $n$ 排服务之前总计用了 $(n-1)/4×16=n×4-4$ 秒钟，再对第 $n$ 排每个座位加上相应的服务时间即可。

情况二： $n$ $mod$ $4$ $==$ $2$ 时，已经经过了 $(n-2)/4$ 个循环，每个循环开始到下一个循环之前共用了 $4×6/2+1+3=16$ 秒，又因为在第 $n-1$ 排服务时花费了 $6×1=6$ 秒，从第 $n-1$ 排走到第 $n$ 排花费了 $1$ 秒，故在第 $n$ 排服务之前总计用了 $(n-2)/4×16+6+1=n×4-1$ 秒钟，再对第 $n$ 排每个座位加上相应的服务时间即可。

情况三： $n$ $mod$ $4$ $==$ $3$ 时，已经经过了 $(n-3)/4$ 个循环，每个循环开始到下一个循环之前共用了 $4×6/2+1+3=16$ 秒，故在第 $n$ 排服务之前总计用了 $(n-3)/4×16=n×4-12$ 秒钟，再对第 $n$ 排每个座位加上相应的服务时间即可。

情况四： $n$ $mod$ $4$ $==$ $0$ 时，已经经过了 $(n-4)/4$ 个循环，每个循环开始到下一个循环之前共用了 $4×6/2+1+3=16$ 秒，又因为在第 $n-1$ 排服务时花费了 $6×1=6$ 秒，从第 $n-1$ 排走到第 $n$ 排花费了 $1$ 秒，故在第 $n$ 排服务之前总计用了 $(n-4)/4×16+6+1=n×4-9$ 秒钟，再对第 $n$ 排每个座位加上相应的服务时间即可。

再具体说明一下对第 $n$ 排每个座位加上相应的服务时间的方法：根据题意和题图，服务总是由窗口方向向过道方向进行，又因为题目规定先进行（面向前排方向）右边座位的服务，因此对于每一排来说，服务总是以 $f \rightarrow e \rightarrow d \rightarrow a \rightarrow b \rightarrow c$ 的顺序进行的。因此读入座位号的字母为 $f$ 时，总服务时间要加上 $1$ 秒，读入座位号的字母为 $e$ 时，总服务时间要加上 $2$ 秒，读入座位号的字母为 $d$ 时，总服务时间要加上 $3$ 秒，读入座位号的字母为 $a$ 时，总服务时间要加上 $4$ 秒，读入座位号的字母为 $b$ 时，总服务时间要加上 $5$ 秒，读入座位号的字母为 $c$ 时，总服务时间要加上 $6$ 秒。

那么这题就完美结束了，如有疑问，评论区见！

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,wt;
char s;
int main()
{
    scanf("%lld",&n);
    scanf("%c",&s);
    if(n%4==1)
    {
    	wt=n*4-4;
    	if(s=='f')
    		wt++;
    	else if(s=='e')
    		wt+=2;
    	else if(s=='d')
    		wt+=3;
    	else if(s=='a')
    		wt+=4;
    	else if(s=='b')
    		wt+=5;
    	else if(s=='c')
    		wt+=6;
    }
    else if(n%4==2)
    {
        wt=n*4-1;
        if(s=='f')
    		wt++;
    	else if(s=='e')
    		wt+=2;
    	else if(s=='d')
    		wt+=3;
    	else if(s=='a')
    		wt+=4;
    	else if(s=='b')
    		wt+=5;
    	else if(s=='c')
    		wt+=6;
    }
    else if(n%4==3)
    {
        wt=n*4-12;
        if(s=='f')
    		wt++;
    	else if(s=='e')
    		wt+=2;
    	else if(s=='d')
    		wt+=3;
    	else if(s=='a')
    		wt+=4;
    	else if(s=='b')
    		wt+=5;
    	else if(s=='c')
    		wt+=6;
    }
    else
    {
        wt=n*4-9;
        if(s=='f')
    		wt++;
    	else if(s=='e')
    		wt+=2;
    	else if(s=='d')
    		wt+=3;
    	else if(s=='a')
    		wt+=4;
    	else if(s=='b')
    		wt+=5;
    	else if(s=='c')
    		wt+=6;
    }
    printf("%lld\n",wt);
    return 0;
}
```


---

## 作者：BCZSX (赞：0)

~~这又是一道恶意评分的题目~~

话不多说，讲解看代码吧……
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

#define ll long long

ll n,k,s,ans;
char ch;

int main()
{
	scanf("%lld %c", &n, &ch);//读入
	if (ch == 'a') ans+=4;
	else if (ch == 'b') ans+=5;
	else if (ch == 'c') ans+=6;
	else if (ch == 'd') ans+=3;
	else if (ch == 'e') ans+=2;
	else ans+=1;
    //判断属于哪个座位
	k=(n-1)/4;s=n%4;
	ans+=((s%2)^1)*7;
	if (k != 0) ans+=(k*16);
    //计算需要走到所在排数的时间
	printf("%lld", ans);//输出
	return 0;//完美结束
}
```

---

## 作者：yf最qhhh (赞：0)

~~友情提醒，本题解大部分内容涉及到**三目运算符**，所以不会的请留下来看看下面的内容，会的可以直接跳过这里。~~

首先我们先来看一个 if 语句：
```cpp
if(a>b)a=1;
else a=0;
```
这种简单的 if 语句我们可以简化成：
```cpp
a=a>b?1:0;
```
这就是三目运算符了，看一眼就能明白了吧。

不明白没关系，我们再来看一个栗子：
```cpp
if(a>b)return 1;
else return 0;
```
~~当然了 else 可以直接去掉。~~

用三目运算符怎么写呢？
```cpp
return a>b?1:0;
```
是不是简单多了。

总结一下：三目运算符就是一种能优化比较简单的 if 语句的运算符。

特别注意：cout 里套三目运算符会报错。

（知道这些足以看懂我这篇题解了，剩下更详细的更专业的讲解请移步[度娘](https://baike.so.com/doc/6743674-6958205.html)qwq）

------------

这道题的思路其他题解也说的差不多了，反正就是不能暴力，需要找规律。

所以我呢，主要不是来讲思路的，是来讲代码的优化。

我看很多 dalao 都是 if else 或者 switch case 写了一大堆，但这部分代码可以一行搞定：
```cpp
c1='a'<=c&&c<='c'?c-93:103-c;
```
让我们慢慢来看。

其他题解的打表程序大多长这样：
```cpp
switch(ch){
    case 'a':{
        ans += 4;
        break;
    } 
    case 'b':{
        ans += 5;
        break;
    }
    case 'c':{
        ans += 6;
        break;
    }
    case 'd':{
        ans += 3;
        break;
    }
    case 'e':{
        ans += 2;
        break;
    }
    case 'f':{
        ans += 1;
        break;
    }
}
```
我们把它转移到 $ASCLL$ 码上。（$ASCLL$ 码总不可能有人不懂吧）

找找规律，很轻松的就能得到：
```cpp
if('a'<=c&&c<='c')c1=c-93;
else c1=103-c;
```
三目运算符一优化，就能得到上面那句代码了。

其他的 if 语句同理。

所以这是 AC 代码：
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rll register long long
int main(){
	char c;rll n,c1;
	std::cin>>n>>c;
	n=n%4>2||n%4==0?n-2:n;
	c1='a'<=c&&c<='c'?c-93:103-c;
	printf("%lld",n%4==1?c1+(n/4)*16:c1+(n/4)*16+7);
	return 0;
}
```
可以看到，很多 if 语句用三目运算符一优化，代码简短了很多。

当然了一些有压缩代码癖好的 dalao 可能还是会觉得这代码太长了。

那么，这段代码的终极压缩：
```cpp
#include<bits/stdc++.h>//万能头压缩头文件
char c;long long n,c1;//定义变量
int main(){//主函数，一行
	return std::cin>>n>>c,n=n%4>2||n%4==0?n-2:n,c1='a'<=c&&c<='c'?c-93:103-c,printf("%lld",n%4==1?c1+(n/4)*16:c1+(n/4)*16+7),0;这就是 return 语句的神奇之处。
}//挑战本题最短代码。
```
好了，就到这里吧，谢谢大家！

---

