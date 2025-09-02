# Painting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/keyence2020/tasks/keyence2020_a

$ H $ 行 $ W $ 列の マス目があり、最初すべてのマスは白色です。

あなたは、このマス目に何回かペイント操作を施すことにしました。 $ 1 $ 回のペイント操作では、以下の $ 2 $ 種類の作業のうちいずれか $ 1 $ つが行えます。

- 行をひとつ選び、その行に含まれるマスをすべて黒く塗る。
- 列をひとつ選び、その列に含まれるマスをすべて黒く塗る。

黒く塗られているマスの個数が $ N $ 個以上となるようにするためには、最小で何回のペイント操作が必要ですか。 なお、制約の項で記述される条件のもとで、何回かペイント操作を行うことで 黒く塗られているマスの個数が $ N $ 個以上となるようにできることが保証されます。

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 100 $
- $ 1\ \leq\ W\ \leq\ 100 $
- $ 1\ \leq\ N\ \leq\ H\ \times\ W $
- 入力値はすべて整数である。

### Sample Explanation 1

「行をひとつ選び、その行に含まれるマスをすべて黒く塗る」という操作を異なる行に対して $ 1 $ 回ずつ、 合計 $ 2 $ 回行うことで、黒く塗られているマスの個数を $ 14 $ にできます。

## 样例 #1

### 输入

```
3
7
10```

### 输出

```
2```

## 样例 #2

### 输入

```
14
12
112```

### 输出

```
8```

## 样例 #3

### 输入

```
2
100
200```

### 输出

```
2```

# 题解

## 作者：A_Đark_Horcrux (赞：5)

首先比较出h和w哪个更大。既然需要最少的次数涂到n个格子，那肯定是挑行和列中比较大的哪那一个去涂咯qwq

如果涂了几行/列以后，刚好能涂到n，那次数就是n/行数（或列数）

如果涂了几行/列以后，离n还差一丢丢，那就再涂一次咯qwq

```cpp
#include<cstdio>
int main(){
	int a,b,n; scanf("%d %d %d",&a,&b,&n),printf("%d",n/(a>b?a:b)+(n%(a>b?a:b)!=0));//如果整除直接输出，如果不整除就加1
	return 0;
}
```


---

## 作者：梦游的小雪球 (赞：2)

题外话：emmm这道题竟然是橙题。

## 梦雪的思路：

**这道题其实很简单吧，具体做法其他题解中都有详细解说，那我就来强调一下注意事项吧。**

1. $3$个数必须都用$double$，不然你在除法时系统会自动向下取整。

1. 向上取整：$ceil$。

1. AT题库记得最后要换行。

## AC代码

```
#include<bits/stdc++.h>
using namespace std;
double n,m,k;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	cout<<ceil(k/max(n,m))<<endl;
	return 0;
}

```

结尾废话：冲社贡ing，希望能早日回红。

---

## 作者：帝千秋丶梦尘 (赞：1)

[童鞋们看题目先](https://www.luogu.com.cn/problem/AT5747)

看完题目，你应该就懂了，所以：

# 终

（是不可能的。

这题，感觉没什么需要特别讲的。

就是让你按他的方法涂格子嘛，而且不是必须n个，而是≥n个。

那肯定行和列中哪个大涂哪个嘛。

so，up代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,x,ans;
int main(void)
{
    scanf("%d%d%d",&n,&m,&x);
    ans=x/max(n,m);
    if(x%max(n,m)!=0)
        ans++;
    printf("%d",ans);
	return 0;
}
```
# 各位看官慢走吖，掰掰

---

## 作者：μηδσ (赞：1)

## Solution
这道题就是看你要进行至少几次操作才能使得有至少$n$个方块是黑色，所以只要判断一下染一行还是染一列比较划算。

判断一下是行的方块比较多还是列的方块比较多（行列的方块数对应着其的价值

以样例$1$为例，在一个$3\times7$的网格中进行$x$次操作使得其中至少含有10个黑色的方块。

![GSP5_Uhfgd8KSml.png](https://i.loli.net/2020/10/28/QBNl69jIarih5uS.png)

不难发现，把任意的两行染成黑色是最划算的。

此处顺便介绍一个非常不错的函数$--$ceil()

ceil函数可以取不小于自变量的最大整数（~~这样就可以避免不必要的if和问号表达式了~~

## Code
~~~cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

double h, k, n; //定义基本的变量，注意要用double，否则系统可能会直接向下取整

int main(){
	cin >> h >> k >> n;		//十分正常的输入
	cout << ceil(n / max(h, k));	//引用ceil函数向上取整
	return 0;
} 
~~~

---

## 作者：xgwpp6710 (赞：0)

思路很简单。（这题没降红差评

就是比较 $h$ 和 $l$ 哪个大，然后拿 $n$ 去除这个较大值向上取整。

这是为什么呢？显然我们应该让每一次尽量多涂几个格子。那么就看行和列哪个格子多了。

不妨设 $h$ 更大，那么显然最好方法就是每次涂一列 $h$ 格，格子多还不会重复。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int h,l,n;
	cin>>h>>l>>n;
	int t=max(h,l);
	cout<<(n-1)/t+1;
	return 0;
}
```
update：应管理员要求给变量加了 $\LaTeX$

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

#### 题意理解：

已知一行可涂多少个黑色格子、一列可涂多少个黑色格子和一共至少需要多少个黑色格子，求至少涂多少行或多少列可以涂满题目要求的格子。

#### 题目思路：

挺简单的，我们看看行和列哪个一次涂的格子多，然后用需要涂的格子数除以行和列的最大值，如果有余数的话商加一。

题意和思路如上，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<fstream>
#include<algorithm>//文件头不解释
using namespace std;
int n,m,a,ans;//定义变量
int main()
{
    cin>>n>>m>>a;//读入
    ans=a/max(n,m);//看上方解释
    if(a%max(n,m)!=0)ans++;//如果有余数
    cout<<ans<<endl;//记得换行
	return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：WHJ___ (赞：0)

这是很简单的贪心思想预备题。

我们要在最少的步数里使涂的格子大于等于  $N $，那么我们只需要选择单次可以涂更多格子的涂法，那很显然，我们只需要在长和宽中取最大值，然后一行一行(或一列一列)涂，这样可以直接一个除法实现。


```cpp
#include<bits/stdc++.h>
#define I long long
#define RI register int
#define il inline
#define INF 0x7fffffff
using namespace std;
const int N=1e+7;

il I Max(I a,I b){//手写max加速,自带的max速度较慢 
	if(a>b)return a;
	else return b;
}

il I read(){//快速读入 
	I x=0,f=1;
	char c=0;
	while(!isdigit(c=getchar()))f-=(c=='-')*2;
	while(isdigit(c)){x=(x<<1)+(x<<3)+f*(c-48);c=getchar();}
	return x;
}

signed main()
{
	RI i,j;
	I paint=Max(read(),read());//取长宽中的最大值 
	cout<<ceil(read()*1.0/paint);//直接得出答案，注意乘*1.0，否则会变成整除 
	return 0;
}

```


---

## 作者：所有人袛旳 (赞：0)

**这是我的第二篇题解** 

 [佛系安利我的博客](https://www.luogu.com.cn/paste/p9a8xgwd)

# 1. 输入输出
小蒟蒻在做这道题的时候遇到最恶心的问题就是，没看懂输入格式，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/e8ew1zk2.png)
实际上，它在告诉你，按照标准输入，输入H、W、N（就是题目的意思）。
# 2. 思考过程
（1）. 怎么涂才能使用的次数最少
题意很简单，用最少的次数，涂上要求的颜色块数（多涂不算），既然是每一次操作选择一行或者一列，并且多操作没有任何影响，那肯定操作长（我指的是较长的边），所以有最少操作次数的情况是每一次都选长。![](https://cdn.luogu.com.cn/upload/image_hosting/newbc8wf.png)
能选择红色的方法涂，就不要用黄色的方法涂。


------------
（2）. 如何求需要多少次才能达到题目要求
在上一个问题中，我们知道了每一次都涂长， _但是需要多少次呢？_ 为了方便，我们设长为ma（即max），我们会自然地想到用n除以ma，**but**我们发现出问题了，比方说， ma=10 ， n=55 ，根据整型变量的规则， 55 / 10=5 ，再往回代， 5 * 10=50 ，依然不够，需要在加一次，所以我们应该判断一下 n%ma 是否为 0 ，若不是就加 1 ，若是就不做任何操作。

# 代码实现

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;

int h,w,n;//根据制约，int够用了 

int pan(int a,int b){//返回最大值 
	if(a>=b) return a;//小蒟蒻不会用三目，凑合着看 
	return b;
}

int main() {
	cin>>h>>w>>n;//我不建议用快读，毕竟这题不至于 
	h=pan(h,w);//返回其最大值 
	w=n/h;
	if(n%h!=0) w++;//如2.（2） 
	cout<<w;
	return 0;//完美地结束 
}
```

# 写在最后
因为这是一道外国题，读题可能不方便（即使管理员写的有翻译，但是输入输出没有写），所以我建议用谷歌浏览器，单击右键，就有一个翻译成中文的按钮，用谷歌的翻译看，比较快。在强调一遍，ATCode的题目输入格式用了两个$包了起来，中间的就是需要输入的。

制作不易，给个赞吧！

---

## 作者：xh39 (赞：0)

题目意思:输入$h,w,n$,给你一个$h$行$w$列的长方形,每次可以给一行或者一列上色,问要上几次才可以有n个上了色的。

显然,要让上色次数最少,每次要尽量上得多。我们可以给长方形的长(即最长的那一条边。)上色,一次就上的多。设长为$d$

要有n个上了色的,一次可以上$d$个,至少要上$ceil(n÷d)$次。其中ceil表示上取整。

下面讲如何向上取整,会的可以跳过,直接看代码。

怎么向上取整呢?这里不推荐用cmath库函数,建议自己写。$ceil(a÷b)$有2中情况。a除以b余0,$ceil(a÷b)=a/b$,a不可以整除b。$ceil(a÷b)=a/b+1$,其中/运算相当于c++的/,表示除完向下取整。

可是又要用if语句。很麻烦,所以就把它整体加上$(b-1)$,即$ceil(a÷b)=(a+b-1)/b$。这样我们发现,第一种情况,还是$a/b$(加上$b-1$不足b,舍去小数,不变),第二种情况还是$a/b+1$(加上$b-1$,整数部分就相当于多加了1)。

AC代码
```cpp
#include<iostream>
using namespace std;
int main(){
    int a,b,c,d; //a,b为h,w。c为n。
    cin>>a>>b>>c;
    d=max(a,b); //最大边为长。
    cout<<(c+d-1)/d; //向上取整。
    return 0;
}
```

---

