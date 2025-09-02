# The Doors

## 题目描述

Three years have passes and nothing changed. It is still raining in London, and Mr. Black has to close all the doors in his home in order to not be flooded. Once, however, Mr. Black became so nervous that he opened one door, then another, then one more and so on until he opened all the doors in his house.

There are exactly two exits from Mr. Black's house, let's name them left and right exits. There are several doors in each of the exits, so each door in Mr. Black's house is located either in the left or in the right exit. You know where each door is located. Initially all the doors are closed. Mr. Black can exit the house if and only if all doors in at least one of the exits is open. You are given a sequence in which Mr. Black opened the doors, please find the smallest index $ k $ such that Mr. Black can exit the house after opening the first $ k $ doors.

We have to note that Mr. Black opened each door at most once, and in the end all doors became open.

## 说明/提示

In the first example the first two doors are from the left exit, so when Mr. Black opened both of them only, there were two more closed door in the left exit and one closed door in the right exit. So Mr. Black wasn't able to exit at that moment.

When he opened the third door, all doors from the right exit became open, so Mr. Black was able to exit the house.

In the second example when the first two doors were opened, there was open closed door in each of the exit.

With three doors opened Mr. Black was able to use the left exit.

## 样例 #1

### 输入

```
5
0 0 1 0 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 0 0 1
```

### 输出

```
3
```

# 题解

## 作者：Creator_157 (赞：3)

### 题目大意：
有一个长度为 $n$ 的 $0$ $1$ 串（$2≤n≤200000$），求 **最后一个** $0$ 和 **最后一个** $1$ 的 位置的最小值。


------------
### 思路：
模拟布莱克先生开门的过程，将 **最后一个** $0$ 和 **最后一个** $1$ 的 位置 求出来比较大小即可。


------------
### code：
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a,l1,l2;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(a==0)l1=i;//找到0最后的位置
        else if(a==1)l2=i;//找到1最后的位置
    }
    cout<<min(l1,l2);//得出答案
    return 0;
}
```

---

## 作者：Chtholly_L (赞：2)

### 题意：

在一个房子的左右两边各有一些们，现在要依次打开这些门，问哪边的会先被全部打开。

输入 $0$ 代表打开左边的一扇门，输入 $1$ 代表打开右边的一扇门。

---


### 分析：

根据输入进行判断，找到最后一个 $0$ 和最后一个 $1$ 出现的位置，就是左边的和右边的最后一个门各是什么时候打开的，再将两个位置进行比较，位置较小的就是先全都打开的。

---


### 代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

bool a[200005];

int main(){
    int n;
    cin>>n;
    int len1,len2;  //标记最后一次出现的位置位置
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x==1){
            len1=i;  //更新位置
        }
        else{
            len2=i;  //更新位置
        }
    }
    cout<<(len1<len2?len1:len2);
    return 0;
}
```

---

## 作者：LeTu_Jun (赞：1)

------------
这题题意理解很难，但真不用从前往后一个一个模拟。

简略一下题意：

**寻找一个由 01 组成的字符串中 0/1 最后的位置，之后两者再求最小值。**
    
为什么可以这么理解？

因为既然是开门，那么不管开了多少门，只有开了最后一个门之后，通道才会开启。

那么我们只要寻找最后一个门所在的位置即可。

*~~你看这题理解题意后多简单呀~~*

$code$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
char s[N];
int n;
int min_1,min_0;
/*min_1—1 的最后位置*/ 
/*min_0—0 的最后位置*/ 
int main ()
{
	scanf("%d",&n);
	scanf("%s",s);
	/*字符串加速读入*/ 
	for(int i=n,j=1;i>=1;i--,j++){
		/*从后往前数*/ 
        if(s[i]=='1' && min_1==0)
		/*因为是从后往前数的,需要判断这个字符*/ 
		/*是不是第一个遇到的*/ 
        {
        	min_1=n-j+1;
		}
		if(s[i]=='0' && min_0==0)
		/*同上*/ 
		{
			min_0=n-j+1;
		}
		if(min_1 && min_0)
		/*都找到了就跳出*/ 
		{
			break;
		}
    }
    printf("%d",min(min_1,min_0));
    /*求最小*/ 
    return 0;
 } 
```


---

## 作者：LLGZ (赞：1)

**题意**

其实题意并不好读懂，让人不知所云

这里我解释一下：

输入$n$及$n$个数（数只为0和1），0表示左面的门，1表示右边的门，门是从左到右依次打开的，问最少打开几个门才可以出来。

其中隐含的条件是左右两边的门，有任意一面的门全部打开，就可以离开。

从左向右找最后一个0或1

>比如：找到最后一个0，说明之后再也没有0，也就是打开最后一个0后，就可以从左面出去

最后输出最后一个0或1的位置，找最前面的，也就是最少的

code
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n;
bool s[200001];
int le,ri;
int main()
{
    
    cin >> n;
    
    for(int i=1;i<=n;i++)
    cin >> s[i];
    	
    for(int i=1;i<=n;i++)
    {
    	if(s[i]==1)
    	le=i;
    	
    	if(s[i]==0)
    	ri=i;
    }
    
    cout << min(le,ri);
	return 0;
}
```


---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/31/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces1143A%20The%20Doors/)

### Solution

题目很简单，实际上就是让我们从$n - 1$倒着枚举，求最后一个与数列最后的一个数字不同的是哪一个，输出它的编号就可以了。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
 
using namespace std;
 
const int MAXN = 200005;
int n, x, a[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int x = a[n];//记录最后一个数字
    for (int i = n - 1; i >= 1; i--)
        if (a[i] != x) {//找出与数列最后一个数字的数
            printf("%d\n", i);
            return 0;
        }
    return 0;
}
```

---

## 作者：世末OIer (赞：0)

题目大意:求一个数组中min{最后一个0的位置，最后一个1的位置}

题解:

水题一道,不用数组也可以AC
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,n;
int main(){
    cin>>n;
    int i,j;
    int l1,l2;
    for(i=0;i<n;++i){
        cin>>a;              //读入
        if(a==0) l1=i;         //更新
        else l2=i;
    }
    cout<<min(l1,l2)+1<<endl;     //输出+1（从0开始的下标）
    return 0;
} 
```

---

## 作者：codemap (赞：0)

这道题挺简单的,没有什么要注意的地方,简单说一下做法

一边输入一边记一下左边的门和右边的门的个数

然后再遍历一遍,记一下当前已经有多少左面的门和右边的门,只要左边或右边全被打开就输出当前是第几扇门,并结束循环

上代码
```cpp
#include<iostream>
using namespace std;
bool a[200001];//数组用bool就行
int main()
{
    int n,i,l=0,r=0,l1=0,r1=0;//l,r是左右门总个数,l1,r1是左右门当前个数
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        if(!a[i])//如果是0
            l++;//左边门++
        else//如果是1
            r++;//右边门++
    }
    for(i=1;i<=n;i++)
    {
        if(!a[i])//如果是0
            l1++;//左边门++
        else//如果是1
            r1++;//右边门
        if(l1==l||r1==r)//如果有一次全被打开
        {
            cout<<i;//输出当前门数
            break;//结束循环
        }
    }
    return 0;//完美结束
}
```
# 拒绝抄袭

---

