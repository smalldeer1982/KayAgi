# Sweet Problem

## 题目描述

### 题意简述

有三堆糖果，在同一堆中的糖果颜色相同，但没有两堆糖果的颜色是一样的。

你每天要吃掉两个糖果，但不能吃掉两个颜色相同的糖果。你最多可以吃多少天？

## 样例 #1

### 输入

```
6
1 1 1
1 2 1
4 1 1
7 4 10
8 1 4
8 2 8
```

### 输出

```
1
2
2
10
5
9
```

# 题解

## 作者：Meatherm_test (赞：7)

将三堆糖果的数量升序排序。设排序之后三堆糖果的数量分别为 $a,b,c$，很明显有 $a\leq b \leq c$。

分类讨论：

- $a+b < c$

这种情况下，就算将前两堆糖都吃完也没办法将第三堆糖消耗完。所以这种情况下，答案为 $a+b$。

- $a+b \geq c$

这种情况下一定存在一种方案使得在第三堆吃完之后前两堆糖的数量 **至多** 相差 $1$。

例如 $a=4,b=6,c=8$ 时：

前 $3$ 天选择第一、三堆糖果吃。  
第 $3$ 天结束后，$a=1,b=6,c=5$。  
之后 $5$ 天，选择第二、三堆糖果吃。  
此时 $a=1,b=1,c=0$。  
最后 $1$ 天选择第一、二堆糖果吃。

但要注意，当 $a=5,b=6,c=8$ 时，不存在一种方案使得所有糖果都被吃完。

所以这种情况下，答案为 $\left \lfloor \frac {a+b+c}{2}\right \rfloor$。

代码留给读者编写。相信看了题解之后也不会很难写吧。

---

## 作者：lichenzhen (赞：4)

## 题目大意
有 $3$ 堆颜色不同的糖果，你每天吃掉两个颜色不相同的水果，问吃完这 $3$ 堆糖果你最多可以吃几天。

## 题目解法
一看就是一道贪心题。

还要注意一点，如果这一天剩下的糖果不够两块或者是两块是相同的颜色，那这天不能算。

我们把数据排一下序，三个数分别是 $a_1,a_2,a_3$，我们分情况讨论：

若 $a_1+a_2 \le a_3$，此时我们此时先每天吃 $a_1$ 和 $a_3$，吃到 $a_1=0$，之后每天吃 $a_2$ 和 $a_3$，直到 $a_2=0$，这时候 $a_3$ 还可能有，所以答案为 $a_1+a_2$。

否则，我们可以根据观察得到一个规律，次数就是$(a_1+a_2+a_3) \div 2$。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[5],t;
	cin>>t;
	while(t--)
	{
		cin>>a[1]>>a[2]>>a[3];
		sort(a+1,a+4);
		if(a[1]+a[2]<=a[3]) cout<<a[1]+a[2]<<"\n";
		else cout<<(int)(a[1]+a[2]+a[3])/2<<"\n";
	}
	
 } 
```


---

## 作者：VTloBong (赞：2)

>如果你足够聪明的话，你可以找到如下规律：  
如果三堆糖果数量a,b,c满足三数中任意两数和不大于第三数，那么答案为$\left\lfloor\dfrac{a+b+c}{2}\right\rfloor$；  
否则,答案为较小两数之和。
# 放代码：
```cpp 
#include<stdio.h>
int t; 
int max(int x,int y){return x>y?x:y;}
int main(){
	scanf("%d",&t);
	while(t){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		int m=max(a,max(b,c));//a,b,c中的最大值 
		printf("%d",a+b>=c&&a+c>=b&&b+c>=a?(a+b+c)>>1:a+b+c-m);//判断 
		if(t-1)putchar('\n');
		t--;
	}return 0;
} 

```


---

## 作者：lx_zjk (赞：2)

贪心 卡了我好久 导致我$D$都没做出来 个人感觉$\text{b > a > d > c}$

我的贪心策略是 如果条件要是最优的话 那么必须有两堆$\text{r g b}$是空的 否则显然可以在次进行操作

代码实现比较简单

```cpp
inline int work (int d) {
	if (d == 1) {
		int delta = a[3] - a[2];
		if (a[1] <= delta) return a[1] + a[2];
		if ((a[1] - delta) % 2 == 0) return a[2] - (a[1] - delta) / 2 + a[1];
		return a[2] - (a[1] - delta) / 2 + a[1] - 1;
	}
	if (d == 2) {
		int delta = a[3] - a[1];
		if (a[2] <= delta) return a[1] + a[2];
		if ((a[2] - delta) % 2 == 0) return a[1] - (a[2] - delta) / 2 + a[2];
		return	a[1] - (a[2] - delta) / 2 + a[2] - 1;
	}
	if (d == 3) {
		if (a[1] + a[2] < a[3]) return 0;
		int delta = a[2] - a[1];
		if (a[3] <= delta) return a[1] + a[3];
		if ((a[3] - delta) % 2 == 0) return a[1] - (a[3] - delta) / 2 + a[3];
		return a[1] - (a[3] - delta) / 2 + a[3] - 1;
	}
}
 
int main () {
	read (T);
	while (T -- ) {
		read (a[1]); read (a[2]); read (a[3]);
		sort (a + 1, a + 3 + 1);
		ll ans = 0;
		ans = max (work(1), max(work(2), work(3)));
		cout << ans << endl;
	}
	return 0;
}
```


### $\text{UPD just now}$

突然想到如果你要让一个最优 肯定是让最小和次小的为空 那么 我的代码变短了$?$

```cpp
inline int work () {
	int delta = a[3] - a[2];
	if (a[1] <= delta) return a[1] + a[2];
	if ((a[1] - delta) % 2 == 0) return a[2] - (a[1] - delta) / 2 + a[1];
	return a[2] - (a[1] - delta) / 2 + a[1] - 1;
	
}
 
int main () {
	read (T);
	while (T -- ) {
		read (a[1]); read (a[2]); read (a[3]);
		sort (a + 1, a + 3 + 1);
		printf ("%d\n", work());
	}
	return 0;
}
```

---

## 作者：Griseo_nya (赞：1)

一道相对简单的题。

我们可以想到把三个数读进一个数组中，然后从小到大排序。我们设排序好后的三个数分别是 $a[0]$ , $a[1]$ 和 $a[2]$ 。

下面要分情况讨论：

当 $a[0]+a[1]≤a[2]$ 时，这时 $a[2]$ 无论怎么样也填不完（等于时刚好吃完），直接输出  $a[0]+a[1]$ 就好了。
     
当 $a[0]+a[1]<a[2]$ 时，我们先把 $a[2]$ 减到和 $a[1]$ 相同大小，然后 $a[0]$ 中的每颗糖，依次和 $a[1]$ 与 $a[2]$ 中的糖配对，直到 $a[0]$ 中不再有糖为止。此时 $a[1]$ 中剩下的糖可以与 $a[2]$ 中剩余的糖配对。中间我们用 $ans$ 来记录 $a[0]$ 用掉的糖。 但 $a[2]$ 有可能会剩下一颗（因为我们先减 $a[1]$ ），所以我们最后的结果是 $ans+a[1]$ （因为 $a[1]$ 不管怎么样肯定是第二小的）。

一些（可能没什么用的）优化：这样子的话， $a[0]$ 肯定会被用掉，那么我们先存一下 $a[0]$ 的初值，最后的结果不就是原来的 $a[0] $ 加上处理后的 $a[2]$ 吗？而且中间干嘛要一个一个来啊，直接求出 $a[0]$ 的一半就可以愉快的减啦~（但其实都可以过）

那么我们来看看代码☆

（无优化版）
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int a[3],ans=0;
		cin>>a[0]>>a[1]>>a[2];
		sort(a,a+3);
		int delta=a[2]-a[1];						//差值 
		if(a[0]+a[1]<=a[2])cout<<a[1]+a[0]<<endl;	//特判a[0]+a[1]≤a[2]	
		else {
			a[2]=a[1];	
			a[0]-=delta;							//先把 a[2] 减到和 a[1] 相同大小 
			ans+=delta;
			while(a[0]>1){							//用a[0] 中的每颗糖，依次和 a[1] 与 a[2] 中的糖配对
				--a[2];
				--a[1];
				ans+=2;
				a[0]-=2;
			}
			if(a[0]==1)a[1]--,ans++;				//当 a[1] 是奇数时，把那颗糖与 a[1] 中的糖配对 
			cout<<ans+a[1]<<endl;					//输出结果 
		}
	}
	return 0;
}
```

（有优化版）
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int a[3];
		cin>>a[0]>>a[1]>>a[2];
		sort(a,a+3);
		int delta=a[2]-a[1];						//差值 
		if(a[0]+a[1]<=a[2])cout<<a[1]+a[0]<<endl;	//特判a[0]+a[1]≤a[2]	
		else {
			int k=a[0];								//存储原来的 a[0] 
			a[2]=a[1];								//先把 a[2] 减到和 a[1] 相同大小 
			a[0]-=delta;
			if(a[0]%2==1)a[1]--;					//当 a[1] 是奇数时，把多出来的那颗糖与 a[1] 中的糖配对 
			int d=a[0]/2;
			a[1]-=d,a[2]-=d;						//用a[0] 中的每颗糖，依次和 a[1] 与 a[2] 中的糖配对
			cout<<k+a[1]<<endl;						//输出结果 
		}
	}
	return 0;
}
```
        

---

