# Data Recovery

## 题目描述

Not so long ago company R2 bought company R1 and consequently, all its developments in the field of multicore processors. Now the R2 laboratory is testing one of the R1 processors.

The testing goes in $ n $ steps, at each step the processor gets some instructions, and then its temperature is measured. The head engineer in R2 is keeping a report record on the work of the processor: he writes down the minimum and the maximum measured temperature in his notebook. His assistant had to write down all temperatures into his notebook, but (for unknown reasons) he recorded only $ m $ .

The next day, the engineer's assistant filed in a report with all the $ m $ temperatures. However, the chief engineer doubts that the assistant wrote down everything correctly (naturally, the chief engineer doesn't doubt his notes). So he asked you to help him. Given numbers $ n $ , $ m $ , $ min $ , $ max $ and the list of $ m $ temperatures determine whether you can upgrade the set of $ m $ temperatures to the set of $ n $ temperatures (that is add $ n-m $ temperatures), so that the minimum temperature was $ min $ and the maximum one was $ max $ .

## 说明/提示

In the first test sample one of the possible initial configurations of temperatures is \[1, 2\].

In the second test sample one of the possible initial configurations of temperatures is \[2, 1, 3\].

In the third test sample it is impossible to add one temperature to obtain the minimum equal to 1 and the maximum equal to 3.

## 样例 #1

### 输入

```
2 1 1 2
1
```

### 输出

```
Correct
```

## 样例 #2

### 输入

```
3 1 1 3
2
```

### 输出

```
Correct
```

## 样例 #3

### 输入

```
2 1 1 3
2
```

### 输出

```
Incorrect
```

# 题解

## 作者：多喝岩浆 (赞：2)

题目给你一堆数字中的部分数字，还给了你一个目标最大值和最小值，让你判断这堆数字能否达到这个最大值和最小值。

这道题直接 $O(N)$ 跑一遍给你的部分数字，找到最大值和最小值。

**如果**最大值大于目标最大值或者最小值小于目标最小值，显然不可能

再写两个判断，判断最大值与目标最大值不同和最小值与目标最小值不相同。**如果**不相同的个数大于 $n - m$ ，那么也显然不可能。

最后如果上面两个**如果**都不符合，那么显然是可能的。

代码如下：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define PP pair <int, int>
using namespace std;
int n, Max, Min = 0x3f3f3f3f, a, b, m;
int main () {
	//freopen (".in", "r", stdin);
	//freopen (".out", "w", stdout);
	ios::sync_with_stdio (false);
	cin.tie (0), cout.tie (0);
	cin >> n >> m >> a >> b;
	for (int i = 1; i <= m; i ++ ) {
		int x;
		cin >> x;
		Max = max (Max, x);
		Min = min (Min, x);
	}
	int res = 0;
	if (a != Min) res ++ ;
	if (b != Max) res ++ ;
	if (Max > b || Min < a) cout << "Incorrect" << endl;
	else if (n - m < res) cout << "Incorrect" << endl;
	else cout << "Correct" << endl;
	return 0;
}
```


---

## 作者：hanyuchen2019 (赞：2)

一道淼题。
## 1.思路

首先，可以扫一遍给的 $m$ 个数，得到这个这几个数中的最小值和最大值。

之后，为了方便起见，
设数据中给出的最大值和最小值为 $\max_1,\min_1$，
序列中求出的最大值和最小值为 $\max_2,\min_2$。

如果 $\min_2<\min_1$ 或者 $\max_2>\max_1$，一定是错的，直接输出 `Incorrect`。

当 $\min_1 \neq \min_2$，那么原序列中一定有一个数是 $\min_1$，以填补这个空缺。

同理，当$\max_1 \neq \max_2$，也会有一个数是 $\max_1$。

在第三组样例中，最大值和最小值都和那个~~可怜~~的 $2$不同，而 $n-m=1$，这一个不确定的数字不可能既是 $\min_1$ 又是 $\max_1$，所以 `Incorrect`。

在 $n-m \geq$ 不同数的情况下，输出 `Correct`。

## 2.Code

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,m,a1,a2,Max=0,Min=114514;
	cin>>n>>m>>a1>>a2;
	for(int i=1,a;i<=m;i++)
	{
		cin>>a;
		Min=min(Min,a);
		Max=max(Max,a);
	}
	if(a1>Min||a2<Max)
	{
		cout<<"Incorrect";
		return 0;
	}
	int flag=0;//记录不同数
	if(Min!=a1)flag++;
	if(Max!=a2)flag++;
	if(n-m<flag)cout<<"Incorrect";
	else cout<<"Correct";
	return 0;
}
```
码字不易，点个赞再走吧~

---

## 作者：maomao233 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF413A)

做法很简单。可以先从已知的这 $m$ 个数中找出最小值和最大值，再从下面两个条件来判断：

- 如果 已知的这 $m$ 个数中的最小值 比 给定的最小值 还小（最大值同理），则肯定不可能；
- 判断 已知的这 $m$ 个数中的最小值 与 给定的最小值 是否不同（最大值同理），如果 不同的个数 比 剩下的数的个数 还多（比 $n-m$ 还多），则肯定不可能。

两者条件都不满足则可能。给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,mn,mx;
	cin>>n>>m>>mn>>mx;
	int minn=101,maxn=0;
	for(int i=1;i<=m;i++)
	{
		int x;
		cin>>x;
		minn=min(minn,x),maxn=max(maxn,x);
	}
	if(minn<mn||maxn>mx||n-m<(mn!=minn)+(mx!=maxn))
	{
		puts("Incorrect"); 
	}
	else
	{
		puts("Correct");
	}
	return 0;
}
```


---

## 作者：小杨小小杨 (赞：1)

## 题意
不用我说了吧，太简单了。
## 思路
依题意得
-  如果给出的数中最小值小于了规定值，或给出的数中最大值大于了规定值，那么就绝对不可能存在解。应为无论再大再小再符合，最大的和最小的永远不会等于规定值。
-  在不违反第一条的情况下，如果给出的数的数量和总数的差大于等于二，说明至少还有两个数没给出，就算给出的数中没有一个等于规定值，也可以通过那几个数保证成立，比如差两个，差的两个可以是一个是最大规定值，一个是最小规定值。故一定存在解。
- 在不违反第一条的情况下，如果给出的数的数量和总数的差等于一，除非给出的数中的最大数等于最大规定值，或最小数等于最小规定值，就存在解，不然就不会存在解。应为只有一个拓展空间，若两个都不同，那么就一定不可能相同，最多只有一个会相同。
-  在不违反第一条的情况下，如果给出的数的数量等于总数，且最大值和最小值全部符合要求，那么存在解，否则不存在解。
- 可证，其余情况均无解  

综上所述，可得代码。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mi,ma,i,mi1,ma1,x;
int main(){
	scanf("%d%d%d%d",&n,&m,&mi,&ma);//读入
	mi1=2e9;ma1=-2e9;//初始化
	for (i=1;i<=m;i++) scanf("%d",&x),mi1=min(mi1,x),ma1=max(ma1,x);//保存当前最大和最小
	if (mi1<mi||ma1>ma){//符合第一条
		printf("Incorrect\n");
		return 0;
	}
	if (n-m>=2||mi==mi1&&ma==ma1||n-m==1&&(mi==mi1||ma==ma1)){//符合第二、三、四条
		printf("Correct\n");
		return 0;
	}
	printf("Incorrect\n");//其余都无解。
	return 0;
}

```


---

## 作者：szh_AK_all (赞：0)

## 题意
已知一个长度为 $n$ 的数组的一部分，这部分的长度为 $m$。再给出两个数 $min$ 和 $max$，让我们判断，这个数组的最大数和最小数有没有可能分别是 $max$ 和 $min$。
## 分析
首先，要判断这个数组的最大数和最小数有没有可能分别是 $max$ 和 $min$，那我们得先求出这一部分数的最大值和最小值。如果这一部分数的最大值超过了 $max$，那么肯定不符合。因为，这一部分数的最大值肯定是小于等于整个数组的最大值。同理，如果这一部分数的最小值小于 $min$，那么整个数组的最小值肯定也小于 $min$，同样不符合。

其次，当判断完以上条件后，若果程序还未终止，那么开始判断这一步。如果这一部分数的最大值不等于 $max$，那么代表：如果要符合要求，那么在完整的数组里，肯定有一个数是等于 $max$的。同理，如果这一部分数的最小值不等于 $min$，那么代表：如果要符合要求，那么在完整的数组里，肯定有一个数是等于 $min$的。如果这一部分的最大值或最小值不等于 $max$ 或 $min$，那么在完整的数组里，肯定要腾出 $1$ 个或 $2$ 个位置，让这个位置的数等于 $max$ 或 $min$。所以，我们要判断，除开这 $m$ 个数外，完整的数组所剩余的空间是否能腾出 $1$ 个或 $2$ 个位置来满足要求。

## Code
```c
#include<iostream>
using namespace std;
int main()
{
	int n,m,a1,a2,max=0,min=10000000;
	cin>>n>>m>>a1>>a2;
	for(int i=1;i<=m;i++)
	{
	    int a;
		cin>>a;
        if(a<min)
        min=a;
		if(a>max)
		max=a;
	}
	if(a1>min||a2<max)
	{
		cout<<"Incorrect";
		return 0;
	}
	int p=0;
	if(min!=a1)p++;
	if(max!=a2)p++;
	if(n-m<p)cout<<"Incorrect";
	else cout<<"Correct";
	return 0;
}
```


---

## 作者：zsh_haha (赞：0)

水题一道！

### 解题思路

首先，我们先把给定的 $m$ 个数从小到大排序，如果 $minn>t_1$ 或 $maxn<t_m$，那么这时候无论我们怎么加数字也不会正确了，直接输出 `Incorrect`。

接下来考虑 $minn=t_1$ 且 $maxn=t_m$ 的情况，这时候无论还能不能放数字都可以成立，所以这种情况直接输出 `Correct`。

然后考虑 $minn=t_1$ 且 $maxn>t_m$ 的情况，这时候想要正确，必须在 $t_m$ 后放一个与 $maxn$ 一样大的数字，所以这时候只有 $n>m$ 时才能成立。$minn<t_1$ 且 $maxn=t_m$ 时也是如此。

最后考虑 $minn<t_1$ 且 $maxn>t_m$ 的情况，这时需要在 $t_1$ 前放一个与 $minn$ 一样大的数字，在 $t_m$ 后放一个与 $maxn$ 一样大的数字才能成立，所以这时 $n-m\ge2$ 才能成立。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101];
int main(){
	int n,m,maxn,minn;
	cin>>n>>m>>minn>>maxn;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	sort(a+1,a+m+1);
	if(minn>a[1]||maxn<a[m]){
		cout<<"Incorrect";
		return 0;
	}
	if(minn==a[1]){
		if(maxn==a[m]){
			cout<<"Correct";
			return 0;
		}else if(n>m){
			cout<<"Correct"; 
			return 0; 
		}else{
			cout<<"Incorrect";
			return 0;
		}
	}
	if(maxn==a[m]){
		if(minn==a[1]){
			cout<<"Correct";
			return 0;
		}else if(n>m){
			cout<<"Correct"; 
			return 0; 
		}else{
			cout<<"Incorrect";
			return 0;
		}
	}
	if(n-m>=2){
		cout<<"Correct";
		return 0;
	}else{
		cout<<"Incorrect";
		return 0;
	}
	return 0;
}
```

### [AC 记录](https://www.luogu.com.cn/record/117761300)

---

## 作者：MOwansui (赞：0)

水题一道。

根据题目信息，我们需要判断是否可以在给定的 $ m $ 个温度的基础上添加 $ n-m $ 个温度，使得最小温度为 $ min $ ，最大温度为 $ max $ 。首先，我们需要判断给定的温度范围是否符合要求，即 $ min $ 不大于记录的最小温度， $ max $ 不小于记录的最大温度。如果不符合该条件，则输出 "Incorrect"。

其次，我们需要判断是否可以通过添加温度来满足最小和最大值的要求。首先计算最小温度和最大温度与给定最小值和最大值之间的差异个数。如果 $ n-m $ 小于差异个数，则说明无法通过添加温度来满足要求，输出 "Incorrect"。否则，输出 "Correct"。

Python代码，可AC
```Python
n, m, a1, a2 = map(int, input().split())
temperatures = list(map(int, input().split()))

if a1 > min(temperatures) or a2 < max(temperatures):
    print("Incorrect")
else:
    differences = 0
    if a1 not in temperatures:
        differences += 1
    if a2 not in temperatures:
        differences += 1

    if n - m < differences:
        print("Incorrect")
    else:
        print("Correct")
```

---

## 作者：Chronomaly_Atlandis (赞：0)

没什么好说的，只要考虑数组是否不合法就行。

不合法的三种条件：

1. 输入的 $min$ 比输入的 $max$ 大时。

1. 数组中任意元素值比输入的 $min$ 小或比输入的 $max$ 大时。

1. 剩余的空间无法存进输入的 $min$ 小和比输入的 $max$时。

如果数组满足以上任意一点，那么一定是不满足要求的，否则就是可以满足的。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	cin.tie(NULL);
	int n,up,down,m,sum=0;
	cin >> n >> m >> down >> up;
	if(down>up){
		cout << "Incorrect";
		return 0;
	}
	for(int i=1;i<=m;i++){
		int tmp;
		cin >> tmp;
		if(tmp<down||tmp>up){
		cout << "Incorrect";
		return 0;
		}
		if(tmp==down)sum++;	
        if(tmp==up)sum++;	
}
cout << ((2-sum>n-m)?"Incorrect":"Correct");
	return 0;
}
```



---

## 作者：Rhapsodia (赞：0)

可以先计算给定数组中的最大和最小值，如果最大值大于给定最大值或最小值小于给定最小值，则输出 `Incorrect` 。

其次，当剩下的元素数量不足以同时存在最大值和最小值时，也输出 `Incorrect` 。

其余情况都输出 `Correct` 即可。

Python 代码

```python
n, m, mn, mx = map(int, input().split())
p = list(map(int, input().split()))
s = n - m
 
if max(p) > mx or min(p) < mn:
    print("Incorrect")
elif mn in p and mx in p:
    print("Correct")
elif mn in p:
    if s >= 1:
        print("Correct")
elif mx in p:
    if s >= 1:
        print("Correct")
elif s >= 2:
    print("Correct")
else:
    print("Incorrect")
```

---

## 作者：Firstly (赞：0)

## **解题思路：**

因为满足题目的数组没有特定的要求，所以不妨判定该数组是否一定不满足要求。

设要求的最大值为 $x$，最小值为 $y$，则一定不满足要求的情况如下：

- 当 $y>x$ 时。
- 对于数组中的任意值 $a$，$a>x$ 或 $a<y$ 时。
- 当剩余的元素数量不足以满足兼有 $x$ 和 $y$ 时。

如果一个数列满足以上任意一点，那么一定没有数组可以满足要求。否则就是可能的。

## **Code：**
```cpp
#include<iostream>
#include<algorithm>
#define ok return 0
#define no cout<<"Incorrect";
#define yes cout<<"Correct";
using namespace std;
int n,m,maxn,minn,tmp;
bool f[2];//f[0]表示是否含有最小值，f[1]表示是否含有最大值
int main(){
    cin>>n>>m>>minn>>maxn;
    if(minn>maxn){no;ok;}
    for(int i=1;i<=m;i++){
        cin>>tmp;
        if(tmp<minn||tmp>maxn){no;ok;}
        if(tmp==minn)f[0]=tmp;
        if(tmp==maxn)f[1]=tmp;
    }int ans=0;
    for(int i=0;i<2;i++)
        if(f[i])ans++;
    if(2-ans>n-m){no;ok;}
    yes;ok;
}
```


---

## 作者：封禁用户 (赞：0)

思路
---
这里令给定的最小值和最大值是 $min$ 和 $max$，序列中的最小值和最大值是 $mn$ 和 $mx$ 。

不存在的情况如下：
- $mn<min$ 或 $mx>max$ 。
- 如果数量和总数的差等于 $0$ ，且给出的序列中不含最大**或**最小值，那么就没有一个剩余的数可以成为最大值或最小值。
- 如果数量和总数的差等于 $1$ ，且给出的序列中不含最大**和**最小值，那么剩余的那个数也不可以同时成为最大值或最小值。
- 如果不是以上情况，则能满足在剩余及当前的串中找出最大值和最小值，即成立。
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n,m,mn,mn;
    cin>>n>>m>>mn>>mx;
    int kx=0,kn=577577577;
    for(int i=0;i<m;i++)
    {
      int a;
      cin>>a;
      kx=max(ta,a);//数据中给出的最大值
      kn=min(ti,a);//数据中给出的最小值
    }
    if(kx>mn||kn<mx)
    {
      cout<<"Incorrect"<<endl;
    }//数据中给出的最大值和最小值和序列中求出的最大值和最小值不匹配
    else
    {
	    if(mn==kn&&kx!=kx) m++;
	    else if(mx==kx&&mn!=kn) m++;//给出的数的数量和总数的差等于一
	    else if(ma!=kx&&mn!=kn) m+=2;//
	    if(m>n) cout<<"Incorrect"<<endl;//最大值小于最小值
	    else cout<<"Correct"<<endl;
    }
    return 0;
}
```



---

## 作者：RainFestival (赞：0)

我们对于每个数考虑，设现在考虑 $a_i$：

+ 如果 $a_i>max$ 或者 $a_i<min$，则无解。

+ 如果 $a_i=max$，$opt_1=1$。

+ 如果 $a_i<min$，$opt_2=1$。

最后比较 $n$ 和 $m+2-opt_1-opt_2$ 即可。

```cpp
#include<cstdio>
int n,m,x,y,cnt=0;
int main()
{
	scanf("%d%d%d%d",&n,&m,&x,&y);
	for (int i=1;i<=m;i++)
	{
		int t;
		scanf("%d",&t);
		if (t<x||t>y) return puts("Incorrect"),0;
		if (t==x) cnt=cnt bitor 1;
		if (t==y) cnt=cnt bitor 2;
	}
	if (cnt==0) return n-m>=2?puts("Correct"):puts("Incorrect"),0;
	if (cnt==1||cnt==2) return n-m>=1?puts("Correct"):puts("Incorrect"),0;
	puts("Correct");
	return 0;
}
```

谢谢观看！

---

## 作者：N_z_ (赞：0)

## 思路
考虑如果最大值是要求的值的话，那么一定没有已给出的值大于要求的值。

否则，对于当前最大值非要求的值，我们可以加入一个值，即要求的最大值。

最小值同理。

即：
* 设要求的最大值是$x$，最小值是$y$。
* 若$\max(a_1,a_2,...,a_m)≥x$或$\min(a_1,a_2,...,a_m)≤y$，则不存在解。
* 不然，若$\max(a_1,a_2,...,a_m)=x$且$\min(a_1,a_2,...,a_m)=y$，则存在解。
* 不然，若$\max(a_1,a_2,...,a_m)=x$或$\min(a_1,a_2,...,a_m)=y$且$n-m≥1$ ，则存在解。
* 不然，若$n-m≥2$ ，则存在解。
* 不然，则不存在解。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,mi,ma;
    cin>>n>>m>>mi>>ma;
    int nmi=1000000,nma=0;
    for(int x=1,y;x<=m;x++)
    cin>>y,nmi=min(nmi,y),nma=max(nma,y);
    if(nmi<mi||nma>ma)cout<<"Incorrect";
    else if(nmi==mi&&nma==ma)cout<<"Correct";
    else if((nmi==mi||nma==ma)&&(n-m>=1))cout<<"Correct";
    else if(n-m>=2)cout<<"Correct";
    else cout<<"Incorrect";
}
```

---

