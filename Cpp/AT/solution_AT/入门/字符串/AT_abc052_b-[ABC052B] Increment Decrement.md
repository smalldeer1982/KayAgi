# [ABC052B] Increment Decrement

## 题目描述

你有一个整数 $x$。最初，$x=0$。

你得到一个长度为 $N$ 的字符串 $S$，你需要用它进行 $N$ 次操作。在第 $i$ 次操作时，如果 $S_i=$`I`，则将 $x$ 的值加 $1$；如果 $S_i=$`D`，则将 $x$ 的值减 $1$。

请输出在操作过程中（包括第 $1$ 次操作前和第 $N$ 次操作后）$x$ 可能取得的最大值。

## 说明/提示

### 限制条件

- $1 \leq N \leq 100$
- $|S| = N$
- $S$ 只包含 `I` 和 `D` 两种字符

### 样例解释 1

每次操作后 $x$ 的值分别为 $1$、$2$、$1$、$2$、$1$，因此最大值为 $2$。

### 样例解释 2

在初始状态 $x=0$ 时，$x$ 就已经取得最大值，因此输出 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
IIDID```

### 输出

```
2```

## 样例 #2

### 输入

```
7
DDIDDII```

### 输出

```
0```

# 题解

## 作者：BCZSX (赞：3)

~~我看这题就是入门难度的，起码没有被恶意评分到蓝题以上~~

这题很水，所以讲解都看代码吧
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
char s[110];
int n,pos,maxn;//pos存储当前高度，maxn存储最高高度
int main()
{
    scanf("%d%s",&n,s+1);//读入字符串的长度和字符串
    for(int i=1;i<=n;++i)
    {
        if(s[i]=='I') ++pos;//判断如果是‘I’，高度++
        else --pos;//否则高度--
        maxn=max(maxn,pos);//每次选取最大值
    }
    printf("%d\n",maxn);//输出答案
    return 0;//完美结束
}
```

---

## 作者：Cambridge (赞：2)


小学生又来发题解了！

这道题真心很简单，~~最近掉蓝了，赶紧刷AT题刷回去~~，言归正传，这道题本蒟蒻看一眼就知道是基本字符串的应用，我们只需求一求每个位置的最大值即可，真心是红题。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int n,da,dq;
    char st[10000];//定义
    int main()
    {
    cin>>n;//读入有多少个位置
    for(int i=1; i<=n; i++)
    {
        cin>>st[i];
        if(st[i]=='I')dq++;//如果往上爬，当前海拔+1
        else dq--;//如果往下走，当前海拔-1
        if(dq>da)da=dq;//每个位置每个位置都与最大值比较
    }
    cout<<da<<endl;//输出最大值并换行
    return 0;
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

## 作者：Eason6 (赞：1)



------------
祖国的花朵，最蒟的是我。大家好。我就是大蒟蒻

------------
俗话说得好：洛谷水题千千万，AT水题占一半。没错，本蒟蒻又来刷水题了。

------------
吭吭，进入正题，首先看题，猛然发现：不就是一道简单的模拟题吗？只要一个循环再判断就行了，话不多说，上代码(注释在代码里):
```
#include<bits/stdc++.h>//万能头文件 
using namespace std;//命名空间 
long long int n;//定义海拔 
char s;//定义输入 
long long int ans=0;//输出 
long long int ansn=0;//用来存储小答案
int main(){//主函数 
	cin>>n;//输入不解释 
	for(int i=1;i<=n;i++){
		cin>>s;//输入I或D 
		if(s=='I'){
			ansn++;//如果为I，ansn++ 
		}
		else if(s=='D'){
			ansn--;//如果为D，ansn-- 
		}
		ans=max(ans,ansn);//求ans与ansn两个之间的大值 
	}
	cout<<ans;//输出答案 
	return 0;//结束程序 
} //真好 
```


---

## 作者：Kaedeuim (赞：1)

题记：第三次吃日本题解

![](https://cdn.luogu.com.cn/upload/pic/60836.png)

好，不闹。

这道题要求输入一个长度为n的大写字符串，然后判断

它：如果是‘I’当前高度加一，如果是‘D’当前高度

减一。

好，那么来看一下，我的算法是这样：

```
先定义一个cmp（最大值（置0））
一个jsq(当前高度（置0）)。
判读：如果是‘I’，jsq++。
满足当前条件下，判断：
如果当前高度jsq>cmp,那么把当前的cmp变成jsq
判读：如果是‘D’，jsq--。
return 0;结束战斗。
```
Q：为什么jsq--的情况下不用将它与cmp比较呢？

A：因为它只要jsq--，就不会比当前cmp大，所以不用

比较。



# AC Code

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int n;
	cin>>n;
	string s;
	cin>>s;
	int cmp=0;
	int jsq=0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='I')
		{
			jsq++;
			if(jsq>cmp)cmp=jsq;
		}
		if(s[i]=='D')jsq--;
	}
	cout<<cmp<<endl;
	return 0;
}
```

#### 看我写得这么辛苦，点个赞再走吧！


---

## 作者：林家三少 (赞：1)

又是一道$\color{red}\text{红题}$，不过我有一个疑惑，为什么楼上和楼下的dadlao的思路都一样，为什么还能多过4篇呢！QAQ

我用的是记数的方法，具体如下：

先判断，如果输入字符是"I"

	shu[j]++;
    
意思就是把他攀登的高度++，j是我的一个临时变量，为了防止加错地方(因为i是会变的)

$\color{blue}\text{重点是输入字符不是"I"}$

	j++;    shu[j]=shu[j-1]-1;
    
大家记住"shu[j]=shu[j-1]-1;"这条语句很重要，如果不加就会WA几个点，因为我们不是重新开始在0这个点爬得，我们只是再退一步，这个很重要

最后就是判断了，就是和max比较一下

AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
string st;  //定义字符串
int n,j=1,maxx;  
int shu[100+50];  //定义负责记数的数组
int main()
{
	cin>>n;  //输入个数
	cin>>st;  //再输入字符串
	for(int i=0;i<=st.size()-1;i++)  //循环要从0开始，到字符串长度-1
		if(int(st[i])==73) shu[j]++;  //我是判断"I"的ASCLL码来的
		else
		{
			j++;
			shu[j]=shu[j-1]-1;  //这里就是我上面讲的处理不等于"I"的语句了
		}
	for(int i=1;i<=j;i++)
		if(shu[i]>maxx)
			maxx=shu[i];  //和比较max
	cout<<maxx<<"\n";  //输出max，记得换行
	return 0;  //完美结束
}
```


---

## 作者：向日葵小班 (赞：1)

**又是一道岛国大水题啊啊，~~不顾它那红红的标题所望~~**

**由于太~~水~~，不放思路了，直接在程序里讲**

# 接下来是放代码时间！！
```cpp
#include<iostream>//一坨头文件
#include<fstream>
#include<algorithm>
using namespace std;
int n,h,d=-100;//n存字符长度，h存当前高度，d存最大高度
char a[110];//a数组存字符串
int main()
{
     cin>>n;//读入字符串的长度
     for(int i=1;i<=n;i++)
     {
     	cin>>a[i];//读入字符串
     	if(a[i]=='I')h++;//如果字符是I，高度++
     	if(h>d)d=h;//每次选取最大值
     	if(a[i]=='D')h--;//如果字符是D，高度--
     	if(h>d)d=h;//每次选取最大值
     }
     cout<<d<<endl;//输出最大值,记得换行
    return 0;//完美结束
}
```


---

## 作者：PrefixAMS (赞：0)

~~今天到来了快乐的刷红题时间~~

纯模拟

for一遍

每次取一下max

最后输出 ans即可

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cc cin>>
#define st strlen
#define ch char
#define out cout<<
#define rrr return 0;
ch as[10010000];
ll ans,now,o;
int main()
{
	cc o;//这个变量其实是用不到的
	cc as;
	for(int i=0;i<st(as);i++)//因为strlen能完美解决
	{
		if(as[i]=='I') now++;
		else now--;
		ans=max(ans,now);//其实这里可以稍稍剪一下枝 就是当上升的时候我才比较，其实也没太大用
	}
	out ans;
	rrr
}
```


---

## 作者：封禁用户 (赞：0)

~~又是AT题，不想讲了啊~~

错误代码展示：
```
#include<bits/stdc++.h>
using namespace std;
int n,ans,ma=-10;
char m;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>m;
		if(m=='I') ans++;
		else ans--;
		if(ans>ma) ma=ans;
	}
	cout<<ma<<endl;
	return 0;
}
```
这道题说了初始海拔是0，那么它全是D咋办
```
#include<bits/stdc++.h>
using namespace std;
int n,ans,ma;
char m;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>m;
		if(m=='I') ans++;
		else ans--;
		if(ans>ma) ma=ans;
	}
	cout<<ma;
	return 0;
}
```
这就不说了···

有的就是输入输出出错了，或者判断写写错了。

### 还有一种就是极品，请读读题再写代码
```
#include<bits/stdc++.h>
using namespace std;
int n,ans,ma;
char m;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>m;
		if(m=='I') ans++;//是I就+1
		else ans--;//如果不是I，就肯定是D，-1
		if(ans>ma) ma=ans;//找出最大的
	}
	cout<<ma<<endl;//输出
	return 0;
}
```

---

## 作者：yzx4188 (赞：0)

这就是一题~~纯~~模拟加字符串嘛！

为什么大家的题解都那么长呢？？？

这题有一个小小的坑：

# 它要输出的是最高的高度

而题目又说要加上0，~~让人一脸懵~~

上代码辣

```cpp
#include<iostream>
#include<string>
using namespace std;
int n,thn,tmh;//thn:当前海拔，tmh:最高海拔
int main(){
	string s;//定义字符串
	cin>>n>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='I')//如果是I就++
		    thn++;
		else
		    thn--;//和上面相反
		if(thn>tmh)//如果当前海拔破纪录了，就更新记录
		    tmh++;
	}
	cout<<tmh<<endl;//输出记录
	return 0;//撒花！！！
}
```


---

## 作者：I_will (赞：0)

这道题我运用的是山峰原理。

* 当s[i]是I时，x++。
* 当s[i]是D是，第一次就判断x和d的大小，然后x--。
* 到最后一定要记得再判断一次x和d的大小，再输出。

----
英文：

I apply the principle of mountain peak to this problem.

* When s[i] Is I is，x++.
* When s[i] Is D is, the first time to judge the size of X and D, and then X --.
* At the end, you must remember to judge the size of X and D again and output it again.

----
This is order（程序）:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,z;
string s;
int d,x;
int main()
{
	cin>>n;
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(z==0&&s[i]=='I')z=1;
		if(s[i]=='I')x++;
		if(z==1&&s[i]=='D')
		{
		z=0;
		if(x>d)d=x;
		}
		if(s[i]=='D')x--;
	}
	if(x>d)d=x;
	cout<<d<<endl;
	return 0;
}
```

---

## 作者：CZQ_King (赞：0)

一道水题，只需要按照题意模拟。

------------
做法：逐个判断字符串的第$n$个为$I$还是$D$。然后，判断最大值。

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a;
int ans,l,maxx=-1*0x7fffffff;//maxx为int的最小值
int main(){
	cin>>l>>a;//输入长度和字符串
	for(int i=0;i<l;i++){//循环l次，a.length()次也行
		ans+=(a[i]=='I')?1:-1;//I为上，D为下
		maxx=max(ans,maxx);//看现在是不是最高
	}
	if(maxx==-1)maxx=0;//要特判是不是-1
	cout<<maxx<<endl;//输出最大值
	return 0;
}
```

---

## 作者：RioBlu (赞：0)

很水的一题

如果是$s[i]=I$ 海拔++

如果是$s[i]=D$ 海拔--

然后看看海拔是否大于ans，如果大于ans=now即可（注意ans初始赋值为0）
```
#include<bits/stdc++.h>
using namespace std;
int a,now,ans;
char u;
int main()
{
	cin>>a;
	for(int s=0;s<a;s++)
	{
		cin>>u;
		if(u=='I')now++;
		else
		now--;
		ans=max(ans,now);
	}
	cout<<ans<<endl;//输出
	return 0;
}
```

---

