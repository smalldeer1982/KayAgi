# Up the hill

## 题目描述

Hiking club "Up the hill" just returned from a walk. Now they are trying to remember which hills they've just walked through.

It is known that there were $ N $ stops, all on different integer heights between $ 1 $ and $ N $ kilometers (inclusive) above the sea level. On the first day they've traveled from the first stop to the second stop, on the second day they've traveled from the second to the third and so on, and on the last day they've traveled from the stop $ N-1 $ to the stop $ N $ and successfully finished their expedition.

They are trying to find out which heights were their stops located at. They have an entry in a travel journal specifying how many days did they travel up the hill, and how many days did they walk down the hill.

Help them by suggesting some possible stop heights satisfying numbers from the travel journal.

## 样例 #1

### 输入

```
0
1
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
2
1```

### 输出

```
1 3 4 2```

# 题解

## 作者：Squirrel_GZQ (赞：5)

## 故事分析
想象有一座山，不算陆地的话，山的高度在  $1$ $\sim$ $N$ ，而每个单位高度都会有一个中转站。这个俱乐部的人记录下了爬山的天数以及下山的天数（显然，他们每天的行程都会结束于一个中转站）。现在他们想知道经过中转站的顺序。
## 思路分析
首先，我们必须输入俱乐部爬山的天数以及下山的天数，这里我用 $up$ 和 $down$ 来表示，更加直观：
```cpp
int up,down;
cin>>up>>down;
```

接着，让我们来将中转站编个号：

显而易见，中转站的编号应为此站所在的单位高度，那么，这个俱乐部所经过的中转站顺序就变成了：他们每天所经过的中转站的编号，于是需要：
```cpp
for(int i=1;i<=up;i++) cout<<i<<" ";//处理上山编号
for(int i=up+down+1;i>=up+1;i--) cout<<i<<" ";//处理下山编号
```

处理上山的过程理解起来很简单，从第一天（此时身处 $1$ 号中转站）开始，一直输出到上山的最后一天（此时身处 $N$ 号中转站）。

那么下山呢？此时已经身处山顶了，于是我们需要倒序输出编号。可是从哪里开始输出呢？

注意，此时**我们已经输出了上山时经过的中转站的编号，共 $up$ 个数**，可是**第一个数是不能算上升的**，因此，下山时输出的的第一个数必定是 $up + down + 1$ ,此时多出来的这个 $1$ 刚好补上了前面的空缺，那么应该在 $up + 1$ 处结束循环。

## 另一种思路
当然，如果觉得以上思路过于冗长，你也可以直接理解为输入两个数 $A$ 与 $B$ ，在 $[1,A+B+1]$ 之间输出一个数列,包含一个上升子序列和一个下降子序列，两个子序列拥有一个公共最大值（山顶）。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int up,down;
int main(){
	cin>>up>>down;
	for(int i=1;i<=up;i++) cout<<i<<" ";
	for(int i=up+down+1;i>=up+1;i--) cout<<i<<" ";
	return 0;
}
```

---

## 作者：XH1111 (赞：4)

## 题意

简单来说，题意的意思是输入两个变量：$a$，$b$。然后通过两个循环，使得第一个输出的 $a$ 个数必须必须保持以下规律：

$a$ 个数比它的下一个数小。

而相反，后来输出的 $b$ 个数又必须保证：

$b$ 个数比它的下一个数大。

## 思路
先是输出 $a$ 个从 $1$ 逐步上升的数，实现代码如下：

```cpp
for(int i=1;i<=a;i++){
    cout<<i<<" ";
}
```

然后就是一个降序，从 $a+b+1$ 到 $a+1$ 输出 $b$ 个数实现代码如下：

```
for(int i=a+b+1;i>a;i--){
   cout<<i<<" ";
}
```

## 最终代码

```
#include<bits/stdc++.h>
using namespace std;
int main() {
    int a,b;
    cin>>a>>b;
    for(int i=1;i<=a;i++){
        cout<<i<<" ";
    }
    for(int i=a+b+1;i>a;i--){
        cout<<i<<" ";
    }
    return 0;
}
```

---

## 作者：yeshubo_qwq (赞：4)

## Description
给你两个整数 $A$ 和 $B$，要你在 $\left[ 1,A+B+1  \right]$ 之间取一个数列，要求有 $A$ 个上升，和 $B$ 个下降。
## Solution
很简单，先升序输出前 $A$ 个数，再降序输出剩余的 $B+1$ 个数即可。

为什么可以这样做？

我们先分析第一个要求：**有 $A$ 个上升**。先升序输出的前 $A$ 个数必然带来 $A-1$ 个上升。而降序输出的 $B+1$ 个数中的第一个数为 $A+B+1$，一定比先升序输出的前 $A$ 个数的最后一个数 $A$ 大，带来了 $1$ 个上升，加起来是 $A-1+1=A$ 个上升，符合要求。

然后我们分析第二个要求：**有 $B$ 个下降**。降序输出剩余的 $B+1$ 个数，带来 $B-1+1=B$ 个下降，也符合要求。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int A,B,i;
int main(){
    scanf("%d%d",&A,&B);
    for(i=1;i<=A;i++)printf("%d ",i);//先升序输出前A个数
    for(i=1+A+B;i>=A+1;i--)printf("%d ",i);//再降序输出剩余的B+1个数
    return 0;
}
```


---

## 作者：York佑佑 (赞：3)

## 题意
给出两个数 $a,b$。要你用 $1$ 到 $a+b+1$ 中的所有数字组成一个排列，使得其中有 $a$ 个数比它的下一个数小，且有 $b$ 个数比它的下一个数大。
## 分析
先分析第一种情况：有 $a$ 个数比它的下一个数小，也就是有 $a$ 个上升。升序输出的前 $a$ 个数必然带来 $a-1$ 个上升。而降序输出的 $b+1$ 个数又带来了一个上升，将两结果相加既是 $a-1+1=a$ 个上升，符合题目的要求。

再分析第二种情况：有 $b$ 个数比它的下一个数大，也就是有 $b$ 个下降。降序输出剩余的 $b+1$ 个数时与上文相同，带来了 $b-1+1=b$ 个下降，符合题目的要求。
## 结论
只要将 $a+1$ 个数字按升序输出，剩下 $b$ 个数字按降序输出即可。

注：本题答案不唯一。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b;
int main()
{
	scanf("%d%d",&a,&b);//读入 
	for(int i=1;i<=a;i++)	
    	printf("%d ",i);//将a+1个数字按升序输出
	for(int i=a+b+1;i>=a+1;i--)	
    	printf("%d ",i);//剩下b个数字按降序输出
	return 0;
}
```

---

## 作者：_xxxxx_ (赞：2)

### 题意

给出两个数 $a$，$b$。要你用 $1$ 到 $a+b+1$ 中的所有数字组成一个排列，使得其中有 $a$ 个数比它的下一个数小，且有 $b$ 个数比它的下一个数大。

------------

### 分析

我们可以将这个数列看成两段，第一段满足 $a$ 个数比它的下一个数小，第二段满足 $b$ 个数比它的下一个数大。

分为两段后，我们就要考虑如何将这两段拼起来。很容易发现，如果第一段中含有 $a+1$ 的话，那么另一段就一定会有一个比 $a+1$ 小的，会导致它小于它的上一个数。所以第一段就是 $[ 1,a ]$。第二段就是 $[ a+b+1,a+1 ]$。 

举个例子，当 $a=2,b=2$ 时，就要将 $5$ 个数排列为

$$1,2,5,4,3$$

此时，$1<2$，$2<5$，$5>4$，$4>3$。满足条件。

整理一下，代码就很容易了。

------------

### $code$

```cpp
#include <iostream>
using namespace std;
int a, b;
signed main()
{
	cin >> a >> b;
	for(int i = 1; i <= a; i++)//从1到a 
	{
		cout << i << " ";
	}
	for(int i = a + b + 1; i >= a + 1; i--)//从a+b+1到a+1 
	{
		cout << i << " ";
	}
	return 0;
}

```


---

## 作者：小杨小小杨 (赞：1)

## 题意
给你两个数 $A$ 和 $B$，问你在 $[ 1 , A+B+1 ]$ 之间取长度为 $A$ 的上升序列的和一个长度为 $B$ 的下降序列，要求下降序列中的每一个数都要比上升序列的每一个数都要小。
## 思路
这题意没谁了。   
很简单，要求下降序列中的每一个数都要比上升序列的每一个数都要小，那么就把最大的 $A+1$ 个数字按升序输出，再把剩下的 $B$ 个数字按降序输出即可。这样就可以保证要求了。   
注：此题有答案不唯一性。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,i;
int main(){
	scanf("%d%d",&a,&b);//读入
	for (i=b+1;i<=a+b+1;i++) printf("%d ",i);//把最大的 A+1 个按升序输出
	for (i=b;i>=1;i--) printf("%d ",i);//把其余的 B 个按降序输出
	return 0;
}

```


---

## 作者：luohaoyu1011 (赞：0)

## 题意
给出两个数 $a$，$b$，要你用 $1$ 到 $a+b+1$ 中的所有数字取一个排列，要求其中有 $a$ 个数比下个数小，而且有 $b$ 个数比下个数大。


------------

## 分析
有两个要求。第一个要求：有 $a$ 个上升。首先升序输出的前 $a$ 个数一定会 $a-1$ 个上升。而后降序输出的带来 $b+1$ 个数中的第一个数 $a+b+1$，一定比首先升序输出的前 $a$ 个数的最后一个数 $a$ 大，带来了 $1$ 个上升，加起来是 $a-1+1=a$ 个上升，符合本题要求。        

------------

第二个要求：有 $b$ 个下降。降序输出余下的的 $b+1$ 个数，带来 $b-1+1=b$ 个下降，也符合本题要求。


------------
## 结论
首先将 $a+1$ 个数字按升序输出，再将剩余下的 $b$ 个数字按降序输出。


------------
## code
```
#include <bits/stdc++.h> 
using namespace std;
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);//读入 。 
    for(int i=1;i<=a;i++)   printf("%d ",i);
    //将a+1个数字升序输出。 
    for(int i=a+b+1;i>=a+1;i--) printf("%d ",i);
    //再将剩下b个数字按降序输出。 
    return 0;//养成好习惯。 
}
```

---

