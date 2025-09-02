# Paper Work

## 题目描述

Polycarpus has been working in the analytic department of the "F.R.A.U.D." company for as much as $ n $ days. Right now his task is to make a series of reports about the company's performance for the last $ n $ days. We know that the main information in a day report is value $ a_{i} $ , the company's profit on the $ i $ -th day. If $ a_{i} $ is negative, then the company suffered losses on the $ i $ -th day.

Polycarpus should sort the daily reports into folders. Each folder should include data on the company's performance for several consecutive days. Of course, the information on each of the $ n $ days should be exactly in one folder. Thus, Polycarpus puts information on the first few days in the first folder. The information on the several following days goes to the second folder, and so on.

It is known that the boss reads one daily report folder per day. If one folder has three or more reports for the days in which the company suffered losses $ (a_{i}&lt;0) $ , he loses his temper and his wrath is terrible.

Therefore, Polycarpus wants to prepare the folders so that none of them contains information on three or more days with the loss, and the number of folders is minimal.

Write a program that, given sequence $ a_{i} $ , will print the minimum number of folders.

## 说明/提示

Here goes a way to sort the reports from the first sample into three folders:

 1 2 3 -4 -5 | -6 5 -5 | -6 -7 6In the second sample you can put all five reports in one folder.

## 样例 #1

### 输入

```
11
1 2 3 -4 -5 -6 5 -5 -6 -7 6
```

### 输出

```
3
5 3 3 ```

## 样例 #2

### 输入

```
5
0 -1 100 -1 0
```

### 输出

```
1
5 ```

# 题解

## 作者：帝千秋丶梦尘 (赞：3)

## [题目链接](https://www.luogu.com.cn/problem/CF250A)

这题唯一要看的，就是虽然两个负数就结束，但如果后面是正数，还是可以放的

我们可以来以3个负数为条件，

遇到三个负数就重新计数

并把计负数的和计总数的重新赋值为$1$

CODE：

```cpp
#include<bits/stdc++.h>
#define ri register
using namespace std;
int n,x,ans,temp,sum;
int a[105];
int main(void)
{
	cin>>n;
	for(ri int i(1);i<=n;++i)
	{
		cin>>x;
		ans++;
		if(x<0) sum++;
		if(sum==3)
		{
			a[++temp]=ans-1;
			ans=1;
			sum=1;
		}
	}
	a[++temp]=ans;
	cout<<temp<<endl;
	for(ri int i(1);i<=temp;++i)
	{
		cout<<a[i]<<" ";
	}
	return 0;
}
```


---

## 作者：Eason_AC (赞：2)

## Content
有 $n$ 个数，要分成若干堆，要求每堆中的负数最多只能有两个。试求出分成的堆数最少是多少，并求出每一堆里面的数的个数。

**数据范围：$1\leqslant n\leqslant 100,|a_i|\leqslant100$。**
## Solution
这题目不算太难，我的想法是这样的：一个一个判断是不是负数，如果出现了 $3$ 个负数，那么就把前面的所有数全部划进一堆，就可以保证堆数最少了。
## Code
```cpp
#include <cstdio>
using namespace std;

int n, a[107], s[107], neg;

int main() {
	scanf("%d", &n);
	s[0] = 1;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if(a[i] < 0)	neg++;
		if(neg > 2) {
			++s[0];
			neg -= 2;
		}
		s[s[0]]++;
	}
	printf("%d\n", s[0]);
	for(int i = 1; i <= s[0]; ++i)	printf("%d ", s[i]);
}
```

---

## 作者：nanatsuhi (赞：2)

这道题的题目描述之简洁实为洛谷罕见( •̀ ω •́ )

由于题目中不需要求每组的数，只需要求每组的数的个数，所以可以先明确一点：

### 只要分正负数就行啦

~~这谁都能看出来~~

题目说每堆最多只能有两个负数，为了使堆数尽量少，那就让负数分配得尽量密集，即尽量每组两个。

所以就可以确定一个基本的分类策略了：

- 直接往后遍历整个序列
- 每遍历到一个负数，计数器的值+1
- 当计数器的值达到3时，在下一个前缀和里记录当前遍历的数的数量-1（即不计当前的这个负数）
- 把当前最后一个前缀和的下一个位置里的数设为总数
- 套路输出

~~我这可悲的解释能力~~

还是代码比较能说明解法吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
int as[110],cnt=1,k;//k是计数器，cnt是堆数,as是前缀和数组
int main()
{
	int n,x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(x<0) k++;
		if(k==3) as[cnt++]=i-1,k=1;
	}
	as[cnt]=n;
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",as[i]-as[i-1]);
	return 0;
}
```

---

## 作者：xiaomuyun (赞：1)

# CF250A Paper Work 题解
[题目传送门](https://www.luogu.com.cn/problem/CF250A)

~~蒟蒻来写详细的题解辣~~
## 题意简述
给出一个长度为 $n$ 的序列，分成 $m$ 堆，每堆最多只能有 $2$ 个负数，求最小的堆数，并输出每堆的个数。（$1\leq n,|a_i|\leq100$）
## 题目分析
题目没有讲清楚一个东西，我来给大家分析一下。大家看下面的例子：

$$\{1,2,3,-4,-5,6,5,-5,-6,-7,6\}$$

我们可以这样分：

$$\color{black}\{\color{red}\underline{1,2,3,-4,-5,6,5}\color{black},\color{blue}\underline{-5,-6}\color{black},\color{green}\underline{-7,6}\color{black}\}$$

也可以这样分：

$$\color{black}\{\color{red}\underline{1,2,3,-4,-5}\color{black},\color{blue}\underline{6,5,-5,-6}\color{black},\color{green}\underline{-7,6}\color{black}\}$$

但实际上答案是第一种。这说明什么？**尽管可能这一堆已经有了 $2$ 个负数，但是它依然能再继续往后加正数。**
## 具体解法
这题甚至不需要多重循环，$O(n)$ 遍历一次 $1\sim n$ 就行了。

需要一个 $tot$ ，一个 $cnt$ 数组和一个 $ans$ 数组。具体用处如下：

- $tot$ 表示当前堆的数量；
- $cnt_i$ 表示第 $i$ 堆中有几个负数；
- $ans_i$ 表示第 $i$ 堆中一共有几个数。

在遍历的时候，我们需要分类讨论。如果当前遍历到第 $i$ 个数（即 $a_i$），则有以下操作：

- 如果 $a_i$ 是负数，则如果当前堆中的负数数量还没满，就能将 $a_i$ 加入进去；否则就要开一个新堆，并且新堆中的负数数量已经为 $1$；
- 如果 $a_i$ 不是负数，则直接将当前堆中的元素数量 $+1$ 即可。

## 代码实现
```cpp
#include<cstdio>
using namespace std;
int n,a[101],ans[101],cnt[101];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	int tot=1;
	for(int i=1;i<=n;++i){
		if(a[i]<0){//对应第一种情况
			if(cnt[tot]<2) ++cnt[tot],++ans[tot];//加入当前堆
			else ++cnt[++tot],++ans[tot];//开一个新堆
		} else {//对应第二种情况
			++ans[tot];
		}
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i){
		printf("%d ",ans[i]);
	}
	putchar('\n');//不要复制题解，对着代码手打一遍都比这么做好
	return 0;
}
```
## 总结
感谢阅读！希望大家能点个赞，管理员求过！

---

## 作者：wkjwkj (赞：1)

[更好的阅读体验]( http://mywkj.github.io/2020/06/20/cf250a-paper-work-ti-jie/)



题目是很简单的，但我却被坑了好几次~~可能是我太蒟蒻了~~

- 首先分析一下思路，在满足每一组内至多有2个负数时，我们肯定要尽可能使每一组内的元素尽可能多。那么策略就出来了。
- 然而我们要注意一下，翻译中并没有提到**每一组内的元素必须连续**，但根据题意，我们要满足**每一组内的元素必须连续**，~~我就是因为这个错了一次，但估计大佬们都没有这种错误~~

核心代码如下:

```cpp
scanf("%d",&a[i]);
if(a[i]<0)fu++;
else zheng++;
if(fu==3){
ans[++m]=zheng+2;
fu=1;
zheng=0;
}
```

但还是要注意一些特殊情况，如

```php
input:
1
0
output:
1
1
```

完整代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
int zheng,fu;
int a[105];
int ans[105];
int m;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]<0)fu++;
		else zheng++;
		if(fu==3){
			ans[++m]=zheng+2;
			fu=1;
			zheng=0;
		}
	}
	if(fu==1||fu==2||zheng>0)ans[++m]=fu+zheng;
	printf("%d\n",m);
	for(int i=1;i<=m;i++)printf("%d ",ans[i]);
	return 0;
 } 
```



---

## 作者：_Kouki_ (赞：0)

### 题目大意：
给你 $ n $ 个数，然你分成若干个堆，要求每个堆之多有 2 个负数。
### 题目思路：
边读边做，一旦有三个负数立马换到下一组。   
堆数加一，个数加一。    
现在我们就来实现吧！
### 题目代码：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
/*
快读，虽然没用到
*/
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int n;//
int a[110];//每堆的个数
int l=1;//堆数
int fs;//统计负数
int main()
{
    scanf("%d",&n);//输入 n
    for(int i=1;i<=n;++i){//循环
        int x;//定义
        scanf("%d",&x);//输入数
        if(x<0) ++fs;//统计负数
        if(fs>2){//如果负数大于二
            ++l;//堆数+1
            fs=1;//负数为1
        } 
        a[l]++;//这一堆的个数+1
    }
    printf("%d\n",l);//输出堆数
    for(int i=1;i<=l;++i){//循环每个堆
        printf("%d ",a[i]);//输出每个堆的个数
        /*nb的我把i -> l*/
    }
    // cin>>n;
    return 0;//完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。
}
```

---

## 作者：Daniel_yao (赞：0)

## 题目大意

给出 $n$ 个数，分成 $m$ 堆，每堆最多只能有两个负数，求最小的堆数，并输出每堆的个数。

### 具体思路

如果把这些数放进一个无序堆里，就有很多种放法，但题目要求是求出最小的堆。所以，我们就有了这三种决策。

- 当一个数为负数时，计数器加 1；

- 当计数器为三时，计数器归零，把这些数放入堆；

- 其余的数全部放进堆；

由于题目要求，求最小的堆数，所以当堆尾为负数时，此时的堆肯定是最小的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N], s, num;
int n, x;
int main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> x;
		if(x < 0){
		  num++;
                }
		if(num == 3){
     		 a[++s] = i - 1;
     		 num= 1;
		}
	}
	a[++s] = n;
	cout << s << endl;
	for(int i = 1;i <= s;i++){
   	 cout << a[i] - a[i - 1] << " ";
	}
	return 0;
}

```

完结撒花！！


---

## 作者：chlchl (赞：0)

## 题意
题意即题目翻译，本题言简意赅，故不提供简述题意。

## 做法
先提供一个**错误做法**（题目翻译中没有说**同一堆元素要连续**，但是题解中有人提到）。

如果没有括号内的内容，直接统计负数个数 $cnt$，堆数肯定就是 $\lceil \frac{cnt}{2}\rceil$。**将所有正数放在一堆中，其余输出 $2$ 即可**（再判断一下**是否有 $1$ 个负数）**。

代码就不放了，有兴趣的自己打打吧。
### 正解
~~看到 $n\leq 100$，其实什么沙雕做法都可以了~~。

直接在线处理，一旦 $cnt > 2$ 了，就一定要新开一堆了，将 $2$ 个负数和正数个数加起来作为一堆，并且负数个数改为 $1$**（不是 $0$）**，正数改为 $0$（全部被放进去了）。

最后还要**判断一下是否还有剩余的数**没有被放进来，如果有就新开一堆。

剩下的就是输出了。

## 代码
以下是 AC 代码。珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100 + 10;
int n, m, cnt, cnt1, x, ans[N];

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%d", &x);
		if(x < 0)	cnt++;
		else	cnt1++;
		if(cnt == 3){
			ans[++m] = cnt1 + 2;
			cnt = 1, cnt1 = 0; 
		}
	}
	if(cnt || cnt1)	ans[++m] = cnt + cnt1;
	printf("%d\n", m);
	for(int i=1;i<=m;i++)	printf("%d ", ans[i]);
	return 0;
}
```


---

## 作者：Allanljx (赞：0)

## 题意
有 $n$ 个数，分成 $m$ 堆，每堆最多只能有 $2$ 个负数，问最少能分成多少堆，并求每堆的个数。
## 思路
一开始我理解错了题意，以为只需要求出负数的个数，再把所有正数分给其中一组就行，结果连第一个点都过不去，后来才发现必须要按顺序排。

所以我们可以用 $f$ 记录当前负数出现的次数，如果为 $3$，就将前面的个数输出来。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101],f,d=1,n,f1;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]<0) f1++;//统计负数个数
	}
	if(f1>0) if(f1%2==0)cout<<f1/2<<endl;else cout<<f1/2+1<<endl;//输出组数
	else cout<<1<<endl;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<0) f++;//统计负数
		if(f==3)
		{
			f=1;
			cout<<i-d<<' ';
			d=i;
		}
	}
	if(n-d+1!=0) cout<<n-d+1;
	return 0;
}
```


---

## 作者：·糯· (赞：0)

## 题目分析
这题我们可以按顺序扫过去，扫到第三个负数时就用一个数组存下前面的数的数量，最后输出总堆数和每堆的数的数量即可。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],ans[110],tot;
int main(){
	cin>>n;
	int sum=0,minus=0,cnt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<0)
			minus++;
		if(minus>2){//负数超过要求了
			ans[++cnt]=sum;//用数组记录答案
			sum=1;
			minus=1;
		}
		else
			sum++;
	}
	ans[++cnt]=sum;
	printf("%d\n",cnt);//堆数
	for(int i=1;i<cnt;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[cnt]);
	return 0;
}
```


---

