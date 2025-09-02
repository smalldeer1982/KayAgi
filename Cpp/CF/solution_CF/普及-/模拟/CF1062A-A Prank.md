# A Prank

## 题目描述

JATC and his friend Giraffe are currently in their room, solving some problems. Giraffe has written on the board an array $ a_1 $ , $ a_2 $ , ..., $ a_n $ of integers, such that $ 1 \le a_1 < a_2 < \ldots < a_n \le 10^3 $ , and then went to the bathroom.

JATC decided to prank his friend by erasing some consecutive elements in the array. Since he doesn't want for the prank to go too far, he will only erase in a way, such that Giraffe can still restore the array using the information from the remaining elements. Because Giraffe has created the array, he's also aware that it's an increasing array and all the elements are integers in the range $ [1, 10^3] $ .

JATC wonders what is the greatest number of elements he can erase?

## 说明/提示

In the first example, JATC can erase the third and fourth elements, leaving the array $ [1, 3, \_, \_, 6, 9] $ . As you can see, there is only one way to fill in the blanks.

In the second example, JATC can erase the second and the third elements. The array will become $ [998, \_, \_] $ . Because all the elements are less than or equal to $ 1000 $ , the array is still can be restored. Note, that he can't erase the first $ 2 $ elements.

In the third example, JATC can erase the first $ 4 $ elements. Since all the elements are greater than or equal to $ 1 $ , Giraffe can still restore the array. Note, that he can't erase the last $ 4 $ elements.

## 样例 #1

### 输入

```
6
1 3 4 5 6 9
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
998 999 1000
```

### 输出

```
2```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
4```

# 题解

## 作者：恨穹不是妹 (赞：1)

###### 题目翻译：
###### JATC和他的朋友长颈鹿正在他们的房间里，为了解决一些问题。长颈鹿在黑板上写了一个数组a[i] 然后去了洗手间。
 
###### JATC决定通过删除数组中的一些连续元素来恶作剧他的朋友。因为他不希望恶作剧太过分，他只会在某种程度上擦除，这样长颈鹿仍然可以使用来自其他元素的信息来恢复数组。因为长颈鹿创建了数组，他也知道到它是一个递增的数组，所有元素都是范围内的整数 【1，10……3】

###### JATC想知道他能擦除的元素的最大数量是多少？
          
#### emm，这道题比较简单啦，但是还是一道不错的模拟题，应为它加了一个隐藏条件就是说它还有一个边界限制不大于1000和不小于1，所以说即使没有下界或上界也是有可能算得出的
比如说这组数据

**输入:**

**3**

**998 999 1000**

**输出：2**

为什么是答案2呢，因为所有的数都不超过1000，所以擦去第1，2个数，还是可以倒推出原来的数组

还有这组

**输入:**

**5**

**1 2 3 4 5**

**输出：4**

是因为下界是1，擦去1，2，3，4个后还可以推回来

所以，我们要在数组头加多一个0，在数组末加一个1001

### 下面我们看代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[101],ans=0,k=-1;
int main()
{
	cin>>n;
	a[1]=0;//队头加一个0
	a[n+2]=1001;//队尾加一个1001
	for(int i=2;i<=n+1;i++)
	{
	cin>>a[i];
	}
	for(int i=2;i<=n+2;i++)
	
	{
	if(a[i]==a[i-1]+1)//算最长的连续序列
	k++;
	else
	{
		if(k>ans)
		ans=k;
		k=-1;
	}
	}
		if(k>ans)
		ans=k;
	cout<<ans;
}
```


---

## 作者：FJ·不觉·莫笑 (赞：1)

### **读题：**  
  给你一个大小为$n$的单调上升序列，保证元素范围在$[$$1$,$10^3$$]$范围内，求最多可以删除多少个连续的元素，使得这个序列还原后唯一.   
  

------------
### **思路：**  
不就是最长上升序列吗？连数组都不用，一边读入一边处理，若这一个比前一个大，计数器加一，否则计数器清零。  


------------
### **坑点：**  
保证元素范围在$[$$1$,$10^3$$]$之间，不仅仅是数据范围，还暗含了一个条件：  
**如果 999 之后还有一个数，那么就肯定是 1000；如果 92 之前还有一个数，那么就肯定是 1**  


------------
### **解决方法：**  
 可将数列看成从$0$到$1001$,多出两位，即可。  
 

------------
### **上代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,x=0,y,ans=0,len=0;
    cin>>n;  
	for(int i=0;i<=n;i++)   
	{
		if(i==n)   
			y=1001;   
		else
			cin>>y;    
		if(y==x+1)     
			len++;
		else
		{
			if(len-1>ans)
				ans=len-1;
			len=0;
		}
		x=y;
	}
	if(len-1>ans)
		ans=len-1;
	cout<<ans;
    return 0;
}
```


---

## 作者：joy2010WonderMaker (赞：0)

喜提最优解。

### 题目分析

这道题本质上就是求最长连续上升1的序列，但有两个坑点。

+ 一是当删掉了一些数后，最后一项是1000，它可能可以被去掉。

+ 二是当删掉了一些数后，第一项是1，它也可能被去掉。

对于第一个坑点，可以将数枚举完后，再枚举一次，将1001加进序列，判断是否是连续上升1的数列。

对于第二个坑点，可以在第一次枚举前，先枚举一次，将0加进序列，判断是否满足连续上升1的条件。

### 题目解法

用两个变量模拟，输入第二个变量，判断第一个变量是否是第二个变量减一。

### 代码

```cpp
#include<cstdio>
int a,b,ans,temp;//a初始值为0，方便解决第二个坑点
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<=n;i++){//多枚举一次，避免第一个坑点
        if(i==n){
            b=1001;
        }else{
            scanf("%d",&b);
        }
        if(b==a+1){
            temp++;   
        }else{
            if(temp-1>ans){
                ans=temp-1;//去掉头尾
            }
            temp=0;
        }
        a=b;
    }
    if(temp-1>ans){//再来一次，防止出现错误
        ans=temp-1;
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：Maxmilite (赞：0)

本题解与其他题解思路不同

## Explanation


对于某个序列，找出一个最大的子序列，保证该子序列位置不存在其他可能序列。

坑点来了:

> 序列需要满足如下要求：
> - 序列必须是**连续**的**一个**子序列
> - 序列中的元素 $x$ 满足 **$x \in [1,10 ^ 3]$**

~~这个题意搞了半天没读懂什么意思..去了趟厕所回来才醒悟~~

![血泪史 (大哭)](https://cdn.luogu.com.cn/upload/image_hosting/luigiegs.png)
血泪史 (大哭)

## Solution

实际上我们不难发现，如果一段序列 $a_l \sim a_r$ 是可以删除的话，那么我们只要保证 $a_{l - 1}$ 和 $a_{r + 1}$ 的差值为 $(r + 1) - (l - 1) + 1$ 即可

所以不难找出方法：

**对于 $i \in [1 , n]$，找出每个 $a_i$ 所能删除的最大子区间**

所以我们只要对每个 $a_r, r \in [1 , n]$ 枚举左端点就可以了

对于可行的左端点 $a_l$ 满足区间长度为 $r - l - 1$

注意特判两个边界 $1$ 和 $1000$
> 序列中的元素 $x$ 满足 **$x \in [1,10 ^ 3]$**

用 $f_i$ 记录 $a_i$ 的区间长度，最后取最大值就可以了

## AC Code _(C language)_

```cpp
#include <stdio.h>
int a[105], ans, n, f[105];
inline void solve()
{
	
	a[n + 1] = 1001;
	for(int i = 1; i <= n + 1; ++i)
	{
		for(int j = 0; j < i; ++j)
			if(a[i] - a[j] == i - j)
				f[i] = i - j - 1 > f[i] ? i - j - 1 : f[i];
	}
	for(int i = 1;i <= n + 1; ++i)
		ans = f[i] > ans ? f[i] : ans;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1;i <= n;++i)
		scanf("%d", &a[i]);
	solve();
	printf("%d\n", ans);
	return 0;
}
```

---

