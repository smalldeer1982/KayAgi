# Ravioli Sort

## 题目描述

众所周知，有一种叫做[意大利面排序](https://en.wikipedia.org/wiki/Spaghetti_sort)的算法。你决定自己实现一个类似的排序算法，但是当你检查你的储藏室时，你意识到你没有意大利面了！你唯一有的是意大利饺子，但你不会因此而放弃…

你构思了以下算法。对于数组中的每个数字 $a_i$，构建一个由 $a_i$ 个意大利饺子组成的堆栈。下面的图片展示了当 $ai = 4$ 时的堆栈。

[![](https://espresso.codeforces.com/04041f95b0a3e1dee7d8b24fa163e68861737411.png)](https://espresso.codeforces.com/04041f95b0a3e1dee7d8b24fa163e68861737411.png)

将这些堆栈按照输入数组中对应数字的顺序排列在一行中。找到最高的堆栈（如果有多个最高的堆栈，选择最左边的一个）。移除这个堆栈，并将其高度添加到输出数组的末尾。将行中的堆栈向左移动，使它们之间没有间隙。重复这个过程，直到所有的堆栈都被移除。

起初，你对自己的算法感到非常满意，但是当你尝试对更多的输入进行排序时，你意识到它并不总是能产生正确的排序数组。事实证明，当两个相邻的意大利饺子堆栈（在过程的任何步骤中）在高度上相差两个或更多时，较高堆栈的顶部意大利饺子会滑落到较低的堆栈上面。

给定一个输入数组，判断描述的算法是否能正确排序它。

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
3 1 2
```

### 输出

```
NO
```

# 题解

## 作者：mamingxiao (赞：5)

第一次写题解有点激动，（^_^）,这道题的意思就是输入一个序列如果有连两个数差大于1就输出“NO”，否则输出“YES”，只要明白意思就非常简单了，废话不多说直接看代码：
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int abs(int a,int b)//求绝对值 
{
	return max(a-b,b-a);//输出大的，就是绝对值，负绝对值就把max改为min 
}
int main()
{
	int n;
	cin>>n;
	int a[n]={};//序列 
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if(i>0)
		{
			if(abs(a[i]-a[i-1])>1)//和前一个求差 
			{
				cout<<"NO"<<endl;//如果大于1就输出“NO” 
				return 0;
			}
		}
	}
	cout<<"YES"<<endl;//如果差都小于1就输出“YES” 
    return 0;//完美结束 
}
```


------------

就是这么简单（~~记得关注加三连~~）
掰掰。

---

## 作者：lzqy_ (赞：3)

## 题意

**由于题面暂时没有很好的翻译，所以这里明确一下翻译**

**单纯翻译的话，题面如下**：

```

按相应数字在输入数组中出现的顺序将数字堆排成一行（数字越大数字堆越高）。
找到最高的一个（如果有几堆最高的，用最左边的一个）。
将其移动到输出数组的末尾。
重复此过程，直到所有数字堆都已排序。

一开始你对你的算法很满意，但是当你在更多的输入上尝试时，
你意识到它并不总是产生正确的排序数组。
结果发现，当两堆相邻的数字堆高度相差两个或两个以上时，
高一堆的顶部就会滑到低一堆的顶部。

给定一个输入数组，找出所描述的算法是否能正确排序
```

首先，第一段很明显就是选择排序，可以忽略不看；

可是第三段中的 ```是否能正确排序``` 是什么意思呢？选择排序难道无法正确排序？显然不是的。

然后我们来看第二段：

>结果发现，当两堆相邻的数字堆高度相差两个或两个以上时，高一堆的顶部就会滑到低一堆的顶部。

这时我们应该就明了了——如果有相邻两堆高度差大于 $1$ 时，数字堆会被打破，就无法排序成功了。

**分析了那么多，重新总结一下题意**：

```
如果给定的数列里，有相邻数字的差大于1，
输出‘NO’，否则输出‘YES’。
```

## 实现

**这道题难就难在分析题意，题意明了了，实现自然就不难了。**

我们只需要将数组从头到尾扫一遍，对于每一个 $i$，只要$|a_i-a_{i-1}|>1$ 的情况出现，则输出 NO，否则输出 YES。

具体实现看代码：

```
#include <bits/stdc++.h>
using namespace std;
int a[100001],n;
int main()
{
  cin>>n;
  for(int i=1; i<=n; i++)
    cin>>a[i];
  //读入
  for(int i=2; i<=n; i++)
  {
    if(abs(a[i]-a[i-1])>1)
    //abs函数即取绝对值
    {
      cout<<"NO\n";
      return 0;//输出NO后可直接结束程序
    }
  }
  //若没有程序没有结束，
  //那么就说明任意相邻两数差不大于2，可直接输出YES
  cout<<"YES\n";
  return 0;
}

```

## Tipes：

- 第二个循环从2开始。（原因：由于是$a_i$与$a_{i-1}$比，所以要从 $2$ 开始）。

- abs函数当然也可以自己写，这里为了方便，就直接调用了。

- 两个循环其实可以合并起来，因为数据不大，为了好理解，我便分开写了。

# 祝大家AC愉快！

---

## 作者：REAL_曼巴 (赞：1)

此题模拟就行。题意如下：

给你一个序列，如果序列相邻两个数的差大于一，就输出 $YES$ ,否则输出 $NO$

此题做法如下:

先输入序列，如果本项与上一项的差的绝对值大于等于二，即可输出不合法，反之再循环后输出合法。（可以用数组也可不用，但我写了不用的）

这里说一下为什么要用绝对值，因为两数得出的差可能会出现负数，这样取绝对值可以把负数转正。

```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long n,b,a;
int main(){
    cin>>n>>a;
    n--;
    while(n--){
        cin>>b;
        if(abs(b-a)>1){//绝对值判断
            cout<<"NO";
            return 0;
        }
        a=b;//这步是不用数组方法的精髓，就是纪录上个数，可节省空间
    }
    cout<<"YES";
    return 0;
}

```


---

## 作者：happybob (赞：1)

这题其实不需要真得按照题意模拟，经过研究，其实我们发现，如果两个数之间绝对值大于等于2，就不行，否则可以

代码，不用数组：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n, a, b;
    cin >> n >> a;
    for(int i = 2; i <= n; i++)
    {
        cin >> b;
        if(abs(b - a) >= 2)
        {
            cout << "NO\n";
            return 0;
        }
        a = b;
    }
    cout << "YES\n";
    return 0;
}
```


---

## 作者：Contemptuous (赞：1)

这道题我们为了排序成功，必须使任意两项的差小于等于$1$，只要有一组差大于$1$，那么就输出$NO$，结束程序。

如果每一组差都小于等于$1$，则输出$YES$。

我们可以先定义一个数组，在循环外输入数组的第一个元素，然后从$2-n$循环，每输入一个数就与前一个数相比较，如果差大于$1$，就输出$NO$，结束程序。最后在末尾输出$YES$。

题目大意就在这里了，代码我就不放了。

---

## 作者：零殇 (赞：0)

### 题意

给你$n$个数，如果出现相邻两个数的差值大于等于$2$，那么这个数列就是不合法的。

判断数列合不合法，如果合法输出$YES$,否则输出$NO$。

### 思路

我们可以定义一个$bool$变量$k$，每一次输入时和上一个输入进行对比，如果两数绝对值大于等于$2$，则记录下来。

最后在输入结束的时候判断，如果合法输出$YES$，否则输出$NO$。

### 注意

#### 第一个输入时需要特判。
#### 因为第一个已经特判，所以循环时要从2开始


上代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
	int n,a[100];
	bool k=0;
	cin>>n;
	cin>>a[1];//特判
	for(int i=2;i<=n;i++)//因为之前特判过，从2开始循环
	{
		cin>>a[i];
		if(abs(a[i]-a[i-1])>=2)//如果不合法
			k=1;//记录
	}
	if(k==0)//判断是否合法
	{
		cout<<"YES";
		return 0;
	}
	cout<<"NO";
	return 0;
}
```

完结撒花~

---

## 作者：wshcl (赞：0)

# 题意

给你一组长度为$n$的数列，

如果其中有相邻的两数差大于1，输出"NO"

否则输出"YES"

# 思路

本题可以先一次输入全部数列（输入量也不大）。

之后再开个for循环，一个个判断即可，如果
$\lvert a_{i}-a_{i-1} \rvert >1$
输出"NO"，结束。

否则输出"YES"

# AC Code
```cpp
#include<cstdio>
#include<cmath>//求绝对值要用到的头文件
using namespace std;
int n,a[11];//n<=10，数组开11就行
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);//输入数据
	for(int i=2;i<=n;i++)
		if(abs(a[i]-a[i-1])>1)//判断相邻的两个数的差是否大于1
		{
			printf("NO");//如果大于1输出"NO"
			return 0;//及时结束程序防止误输出"YES"
		}
	printf("YES");//如果全部判断完了还没有输出"NO"那么输出"YES"
 	return 0;
}
```


---

## 作者：_cmh (赞：0)

解法 @栾竹清影 大佬已经讲的很清楚了，这里介绍一种不用数组实现的方法。

我们读入 $last$ ，再读入 $now$ 。判断 $abs(now-last)$ 是否大于 $1$ ，如果是，输出 $NO$，结束程序。然后把 $last$ 替换成 $now$ 即可。最后输出 $YES$ 。

代码：

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int n,last,now;
int main(){
	cin>>n>>last;
	for(int i=2;i<=n;i++){
		cin>>now;
		if(abs(now-last)>1){
			cout<<"NO";
			return 0;
		}
		last=now;
	}
	cout<<"YES";
 	return 0;
}
```

求赞

---

## 作者：Daidly (赞：0)

这个题其实只需要判断两个数之差是否大于一就可以了，如果大于一的话，就是$NO$，如果小于一的话，就是$YES$。
```
#include<bits/stdc++.h>//火车头
using namespace std;
int n,a[105];
int main(){   
   ios::sync_with_stdio(false);//加速黑科技
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){//数组输入
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		if(abs(a[i]-a[i+1])>1){//判断两相之差的绝对值是否大于一
		    cout<<"NO"<<endl;
			return 0;
		}
	} 
	cout<<"YES"<<endl;
	return 0;
}
```


---

## 作者：　　　吾皇 (赞：0)

~~太水了~~
### 题目分析
```
如果序列中任意相邻两元素的差值大于1输出"NO",否则输出"YES"，所以只要O(n)查找整个序列比较相邻两元素的差的绝对值是否大于1即可
```
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[1001];
int main(){
	cin>>n;
    cin>>a[1];//为了减少代码量把比较和读入一起做，所以先读入第一个
	for (int i=2;i<=n;i++){//从第二个开始，进行读入和比较操作
		cin>>a[i];
		if (abs(a[i]-a[i-1])>1) {//只要任何两相邻元素的差值大于1就输出NO并停止程序
            cout<<"NO";
            return 0;
        }
    }
	cout<<"YES";//如果程序没有被终止代表这个序列满足条件输出YES
}
```


---

## 作者：Creator_157 (赞：0)

### 题目大意：

给你一个序列，如果序列**相邻两个数的差**大于 $1$ ，就输出 Y$E$S , 否则输出 $N$O。

------------
### 思路：

其实很简单，再读入第二个数时就与前一个数比较**差的绝对值**即可。

求绝对值可以用 $C$++ 的 **abs函数**。

------------

### code：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
long long n,b,a;
int main()
{
    cin>>n；
    cin>>a;
    for(int i=1;i<=n-1;i++)
    {
        cin>>b;
        if(abs(a-b)>1)
        {
            cout<<"NO";
            return 0;
        }
        a=b;
    }
    cout<<"YES";
    return 0;
}
```


---

