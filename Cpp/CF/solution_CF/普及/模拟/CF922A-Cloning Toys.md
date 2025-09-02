# Cloning Toys

## 题目描述

Imp非常喜欢他的毛绒玩具。

![](https://cdn.luogu.org/upload/vjudge_pic/CF922A/62fe36f6fbde65681f909b9b7cc85dddda4799f7.png)

最近，他发现了一个可以克隆毛绒玩具的机器。Imp知道如果他将一个玩具本体进行克隆，他将会得到两个本体（新增一个）和一个克隆体；而如果将一个克隆体进行克隆，他将会得到三个克隆体（新增两个）。

一开始，Imp只有一个毛绒玩具本体。他想要知道他能否使用这个机器得到恰好$x$ 个克隆体和$y$ 个本体。他不能把玩具扔掉，也不能在没有克隆体的时候对一个克隆体进行克隆。

## 说明/提示

在样例一中，Imp可以对本体进行两次克隆，再对克隆体进行两次克隆。
翻译贡献者：浮尘ii

## 样例 #1

### 输入

```
6 3
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
1000 1001
```

### 输出

```
Yes
```

# 题解

## 作者：mwhxiaopy (赞：6)

这道题可以直接打表，但是有一个坑。

我先写一下坑在哪里：
**输入y和x！！** **先输入克隆体数量！！**

好了，写完这个坑，就可以开始了。

首先，我们知道需要$x$个主体。

每次操作可以获得$1$个主体。

在过程中，会得到$x-1$个克隆体。

所以：第一个判断：如果需要克隆体$<x-1$
则无法实现，输出$no$。

如果克隆体$>=x-1$,判断克隆体数量$-(x-1)$是否为偶数。如果是，则可以。如果不是，不可以。这是最主要的判断。

最后写$3$个特判：
1.本体为0。

2.本体为1且克隆体不为$0$。

3.本体$-1<$克隆体。

于是就完成了。

最后，别忘了```return 0```。

代码：
```
#include<iostream>
using namespace std;
int main()
{
    int a,b,x,y;
    cin>>b>>a;
    if(a-1==0&&b!=0)//特判本体=1
        cout<<"No";
    else if(a-1>b)//特判是否需要克隆体小于需要本体-1
        cout<<"No";
    else if(a==0)//特判a=0
        cout<<"No";
    else if((a+b)%2==1)//主要判断
        cout<<"Yes";
    else if((a-b)%2==0)
        cout<<"No";
    return 0;
}
```
谢谢大家。

别忘了点个赞（^_^）

求过

---

## 作者：star_magic_young (赞：3)


------------

~~jr来水一发~~

------------


## 思路

首先,我们知道如果将一个玩具本体进行克隆,将会*新增一个本体和一个克隆体*;而如果将一个克隆体进行克隆,将会*新增两个克隆体*

所以,我们可以求出把本体克隆完后的克隆体数目,即本体数量-1

然后把需要的克隆体数目减去刚才那个数字,如果得到一个偶数,说明方法是可行的

这个做法需要特判:把本体克隆完后的克隆体数目要为正数才可行;还有 0 1的情况要输出Yes

------------


#### code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define il inline
#define sta static
#define re register
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
#define swap(a,b) a^=b^=a^=b
const int mod=19650827,_=2010;
using namespace std;
il bool issz(char ch){return ch>='0'&&ch<='9';}
il long long rd()
{
  char ch;long long x=0,w=1;
  while(!issz(ch)){if(ch=='-') w=-1;ch=getchar();}
  while(issz(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
  return x*w;
}
long long a,b,c;	//a 需要的克隆体 b 需要的本体 c 克隆完本体后的克隆体数目
int main()
{
  a=rd();b=rd();
  c=b-1;
  printf("%s\n",((c>0||(a==0&&c==0))&&a-c>=0&&(a-c)%2==0)?"Yes":"No");
  return 0;
}
```

---

## 作者：long_long (赞：0)

## 思路：

这道题可以用诸葛排除法。
第一个判断问的是克隆体是否为0。因为如果克隆体为0，意味着操作了0次，所以本体也应该为0。第二个判断问克隆体如果为1，并且本体大于0。

如果过了这两个判断，那么让本体减克隆体减1。
然后如果本体可以被2整除，则输出Yes。

见代码：
```
#include<iostream>
using namespace std;
int x,y;
int main(){
    int x,y;    
    cin>>x>>y;
    if(x==0){
        cout<<"No"<<endl;
        return 0;
    }
    if(x==1&&y>0){
        cout<<"No"<<endl;
        return 0;
    }
    y-=(x-1);
    if(y>=0&&y%2==0) cout<<"Yes"<<endl; else cout<<"No"<<endl;
    return 0;
}
```


---

## 作者：durex_com (赞：0)

题很简单，因为真品数满足的方法只有一种，看赝品的剩余数判断就是了。

但是题目有很多坑，我也是wa了很多次才过的（vjudge）。

贴代码
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
int x,y,xnum=0,ynum=0;
int main()
{
	
	scanf("%d%d",&y,&x);
	if(x==1&&y>0||x==0)
    {
        printf("No");
        return 0;
    }
    int z=x-1;
    y-=z;
    if(y>=0&&y%2==0) printf("Yes");
           else  printf("No");
    return 0;
}
```

---

## 作者：PC_DOS (赞：0)

这道题总体不难，但是有两个小小的坑点。

首先说一下总体思路:

要得到nOrig个本体和nClone个克隆体，必须对本体进行nOrig-1次克隆，此时一并得到nOrig-1个克隆体，由于剩下的nClone-nOrig+1个克隆体只能由克隆体克隆得到，因此，显然当且仅当nClone-nOrig+1为偶数时才可以正好得到这么多的克隆体和本体。

但是需要注意:

1. 由于已经有了1个本体，因此nOrig不可能为0。

2. nOrig为1时，不能进行克隆，因此所需克隆体的个数只可能为0。

加上特判之后，就可以得到代码了:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nClone, nOrig, nTimesOrig; //nClone-所需克隆体个数，nOrig-所需本体个数，nTimesOrig-需对本体克隆的次数
	cin >> nClone >> nOrig; //输入需求量
	if (nOrig == 0){ //如果本体需求量为0
		cout << "No"; //不可能
		goto endapp; //结束
	}
	if (nOrig == 1 && nClone != 0){ //如果本体需求量为1且克隆体需求量非0
		cout << "No"; //不可能
		goto endapp; //结束
	}
	nTimesOrig = nOrig - 1; //计算克隆本体的次数
	nClone -= nTimesOrig; //计算需要克隆克隆体的次数
	if (nClone < 0){ //显然不可能出现负数
		cout << "No"; //不可能
		goto endapp; //结束
	}
	if (nClone % 2 != 0) //如果nClone-nOrig+1不为偶数
		cout << "No"; //不能
	else //如果nClone-nOrig+1为偶数
		cout << "Yes"; //能
endapp:
	return 0; //结束
}
```

---

