# A Student's Dream

## 题目描述

**题目大意：**

有两个人要握手，女孩左手有 $a_l$ 个手指，右手有 $a_r$ 个手指；男孩左手有 $b_l$ 个手指，右手有 $b_r$ 个手指。握手规则为：男孩可以用左手握女孩的右手，也可以用右手握女孩的左手。在女孩的两根手指中间必须有男孩的一根手指，并且男孩的三根手指之间必须有女孩的一根手指。

现在要判断如果可以握手输出 `YES`，不能输出 `NO`。

## 样例 #1

### 输入

```
5 1
10 5
```

### 输出

```
YES```

## 样例 #2

### 输入

```
4 5
3 3
```

### 输出

```
YES```

## 样例 #3

### 输入

```
1 2
11 6
```

### 输出

```
NO```

# 题解

## 作者：monstersqwq (赞：6)

这道题最大的难点就在于题面不好懂，我来简单的解释一下。

#### 题目大意：

两个人要握手，他们不关心谁用左手（即有男左女右和男右女左两种情况）。握手规则：女生两只手指中必须有男生的一只手指（即男生手指数至少是女生的手指数少一）、男生三只手指中必须有男生的一只手指（即女生的手指数的二倍加三要大于男生的手指数）。

题意懂了，就可以直接模拟两种方法，一种可以就输出 YES 即可。

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
	int al,ar,bl,br;
    cin>>al>>ar>>bl>>br;
    if((al*2+3>br&&br>=al-1)||(ar*2+3>bl&&bl>=ar-1))
    {
        cout<<"YES"<<endl;
    }
    else
    {
        cout<<"NO"<<endl;
    }
	return 0;
}
```


---

## 作者：LZT666 (赞：2)

这么简单的题，居然没有几个人发题解？

```
#include<cstdio> //头文件
int main() //主函数
{
    int a,b,c,d; //定义变量
    scanf("%d%d%d%d",&a,&b,&c,&d); //输入
    if((a*2+3>d&&d+1>=a)||(b*2+3>c&&c+1>=b)) //判断 
    { //条件成立 
    	puts("YES");
    	return 0; //不用else，如果条件成立就结束。 
    }
    puts("NO");
    return 0; //结束    
}
/*本人很渣，但还是欢迎大家前来吐槽。*/
```


---

## 作者：Happy_Dream (赞：2)

本人已提交翻译……
***
题意懂了就可以开始做题了，只要按题面规则模拟就可以，只要读懂题就行，没什么可以说的：
***
```cpp
#include <iostream>//头文件
using namespace std;//常规
int main()//主函数
{
	int a,b,c,d;//定义手指
	cin>>a>>b>>c>>d;//输入手指根数
	if((a*2+3>d&&d+1>=a)||(b*2+3>c&&c+1>=b))//判断有两种情况，每种情况里又有两种小情况，只要满足两种小情况就行（题意说了）
        cout<<"YES";//输出
    else//不符合要求
        cout<<"NO";//输出
    return 0;//结束
}
```
***
 _任何一个伟大的思想，都有一个微不足道的开始。_ 
 
 加油！ 加油！ 加油！

---

## 作者：Oscar12345 (赞：2)

作为第1个通过这道题的人，我认为有必要给后来人~~一点点提示~~。
这道题其实有那么一点点~~猥琐~~，
咳咳，废话不说
这道题只要算法就是贪心，嗯。。。外加一点点数学，数学渣请自觉出门。

下面放我那~~优秀~~（chou lou）的代码：
```cpp
#include<iostream>
using namespace std;

int main()
{
	int A,B,C,D;
	cin>>A>>B>>C>>D;
	if((A*2+3>D && D+1>=A) || (B*2+3>C && C+1>=B))
	{
		cout<<"YES"<<endl;
	}
	else
	{
		cout<<"NO"<<endl;
	}
	return 0;
}
```

首次发题解，欢迎各位大佬前来拍砖。。。

---

## 作者：miaohongxuan (赞：1)

[原题链接](https://www.luogu.com.cn/problem/CF62A)

这题其实并不难只需要输入之后if语句判断，再输出即可，但if语句里该写什么条件呢？下面为您揭秘。

先来解决“在女孩的两根手指中间必须有男孩的一根手指”，相当于植树问题，把女孩的手指空隙就是植树的地方，男孩的手指就是树，只要判断女孩的手指空隙是否小于等于男孩的手指数就行了，而手指空隙 $=$ 手指数 $-1$，因此判断“在女孩的两根手指中间必须有男孩的一根手指”的条件就是 $al-1 \leq br$ (以女孩左手握男孩右手为例)。

接下来解决“男孩的三根手指之间必须有女孩的一根手指”，如果男孩手指数是奇数，那么每两个男孩手指空隙中应该有一根女孩手指，只要女孩手指数 $\times 2 + 1 \geq$ 男孩手指空隙数，而当男孩手指数为偶数时空隙数为奇数，有一个空隙(两根手指)不用考虑，所以在奇数基础上还要加 $2$ ，奇数的情况同样适用，所以判断“男孩的三根手指之间必须有女孩的一根手指”的条件是 $al\times2+3 > br$ (以女孩左手握男孩右手为例)。

---

### 具体实现

**1.标准格式与变量、数组定义**

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std; 
int al,ar,bl,br; 
int main(){ 
	cin >> al >> ar >> bl >> br;
	return 0;
}
```
**2.if语句判断部分**

这下就要用到开头说的方法，写在条件里。

```cpp
if((al-1 <= br && al*2+3 > br)||(ar-1 <= bl && ar*2+3 > bl)){
}
```

**3.输出**

```cpp
if((al-1 <= br && al*2+3 > br)||(ar-1 <= bl && ar*2+3 > bl)){
	cout << "YES";
	return 0;
}
cout << "NO";
```
又完成了一题！ヾ(*>∀＜*)

---

### 完整代码

**请勿抄袭**

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std; 
int al,ar,bl,br; 
int main(){ 
	cin >> al >> ar >> bl >> br;
	if((al-1 <= br && al*2+3 > br)||(ar-1 <= bl && ar*2+3 > bl)){
		cout << "YES";
		return 0;
	}
	cout << "NO";
	return 0;
}
```

---

## 作者：luosw (赞：0)

### 题目描述
看到这道题，我被那~~迷人的外衣~~给~~深深的吸引~~（吓个不轻），首先，我们来分析一下题意：
- 男生有$bl$个左手指，有$br$个右手指
- 女生有$al$个左手指，有$ar$个右手指

题目中还有一件~~非常贴心~~的事：

> The boy and the girl don't really care who goes to the left.

为了防止有些巨犇不会英文（~~巨犇也不会看这种题解的~~），我特地去翻译了一下：

> 男孩和女孩并不会在乎谁走在左边

好，废话说完，开始分析

### 题目分析
分析一下这种题，有两种情况，一种是男左女右，一种是女左男右，为了和其他题解不一样的方法，我们需要编写两个$bool$函数进行分别的判断，简单粗暴地完成这道题目了
```cpp
#include<cstdio>
using namespace std;
int a1,a2,b1,b2;	//用于存放指的数量 
bool abc(){
	if((a1*2+3>b2 and b2+1>=a1)){	//and和&&作用一样 
		return true;
	}
	return false;
}
bool abca(){
	if(a2*2+3>b1 and b1+1>=a2){
		return true;
	}
	return false;
}
bool zzjj(bool a,bool b){
	if(a or b){
		return true;
	}
	return false;
}
int main(){
	scanf("%d%d%d%d",&a1,&a2,&b1,&b2);	//格式化输入
	if(zzjj(abc(),abca())){
		printf("YES");
	}
	else{
		printf("NO");
	}
	return 0;	//最好要写 
} 
```

---

## 作者：半笙、凡尘 (赞：0)

# CF62A 【A Student's Dream】

 ### ~~序：无聊来刷刷水题~~
 
 ----
 - ~~这题过于诡异，属实给我吓一跳啊，手指根数....这题面谁想的，恐怖暴力啊~~
 
 - 按照握手的规则:
 
 
   - 在女孩的两根手指中间必须有男孩的一根手指。
   - 男孩的三根手指之间必须有女孩的一根手指。
   
   
 - 在写代码时，则将条件转换成语句，简单用 $if$ 判断一下条件是否满足即可：
 
   - $a1 \times 2+3>b2 \  \&\& \ b2\geq a1-1$
   - $a2 \times 2+3>b1 \  \&\& \ b1\geq a2-1$
   
 
 - 接下来就是一点也不激动人心的代码了
 
 
```cpp
#include<bits/stdc++.h>
#define RT register
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0)putchar('-'),write(-x);
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}
template<class t> inline void writeln(t x){
	write(x);putchar('\n');
	return;
}
template<class t> inline void write_blank(t x){
	write(x);putchar(' ');
	return;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int a1,a2,b1,b2;
	read(a1);
	read(a2);
	read(b1);
	read(b2);
	if((a1*2+3>b2&&b2>=a1-1)||(a2*2+3>b1&&b1>=a2-1)){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
	return 0;
}
```

---

## 作者：X_Chao_Bai (赞：0)

本题考查分支结构

有两种情况是可以握手的

判断条件题目说的也很清楚了


```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main(){
    cin>>a>>b>>c>>d;
    if(d+1>=a&&a*2+3>d) cout<<"YES";
    //第一个判断，可以握手的第一种情况
	else if(b*2+3>c&&b<=c+1) cout<<"YES";
    //第二个判断，可以握手的第二种情况
    else cout<<"NO";
    //以上两种都不符合，则不可以握手
    return cout<<endl&&0;
}
```

---

