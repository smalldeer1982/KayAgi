# TCMCF+++

## 题目描述

Vasya has gotten interested in programming contests in TCMCF+++ rules. On the contest $ n $ problems were suggested and every problem had a cost — a certain integral number of points (perhaps, negative or even equal to zero). According to TCMCF+++ rules, only accepted problems can earn points and the overall number of points of a contestant was equal to the product of the costs of all the problems he/she had completed. If a person didn't solve anything, then he/she didn't even appear in final standings and wasn't considered as participant. Vasya understood that to get the maximal number of points it is not always useful to solve all the problems. Unfortunately, he understood it only after the contest was finished. Now he asks you to help him: find out what problems he had to solve to earn the maximal number of points.

## 样例 #1

### 输入

```
5
1 2 -3 3 3
```

### 输出

```
3 1 2 3 
```

## 样例 #2

### 输入

```
13
100 100 100 100 100 100 100 100 100 100 100 100 100
```

### 输出

```
100 100 100 100 100 100 100 100 100 100 100 100 100 
```

## 样例 #3

### 输入

```
4
-2 -2 -2 -2
```

### 输出

```
-2 -2 -2 -2 
```

# 题解

## 作者：ADivT (赞：9)

### 首先
对于任意$a,x>0$有$ax>x($~~小学结论~~) 所以看到正数就直接输出

由于**负负得正**(~~双倍小学知识~~)我们读入绝对值最大的偶数即可；

**but**,接下来才是本题的重点：
## **特判**
- 若只有一个负数 输出它（坑了我好几次）;
- 若只有一个负数,n-1个0 或者全是0 输出0;

由以上,可得AC代码:
```cpp
#include<bits/stdc++.h>

#define rep(i,o,p) for(register int i=o;i<=p;++i)

using namespace std;

int n,a[110],ze=0,ne=0,x,l=0;

int main() {
	scanf("%d",&n);
	rep(i,1,n) {
		scanf("%d",&x);
		if(x>0) {
			printf("%d ",x);
			continue;
		}
		a[++l]=x;
		if(a[l]<0) ++ne;
		else ++ze;
	}
	if(n==1&&ne==1) {
		printf("%d ",a[1]);
		return 0;
	}
	if(ze==n||(ne==1&&ze==n-1)) {
		printf("0\n");
		return 0;
	}
	sort(a+1,a+l+1);
	rep(i,1,ne/2*2) printf("%d ",a[i]);
	return 0;
}
```
到此，即可AC，不留个赞再走吗


---

## 作者：Binary_Lee (赞：2)

### 题目描述
有 $n$ 个数 $a_i$ 请你从中至少选出一个数，使它们的乘积最大

### 解决思路
1. 对于正数，对答案一定有贡献（正数越乘越大），所以输入正数时直接输出即可。

2. 对于负数，如果负数的个数 $f$ 是偶数，负负得正，可以全部输出。如果负数的个数 $f$ 为奇数，那么就输出绝对值较大的 $f-1$ 个。

3. 有一种特殊情况，那就是 $n = 1$ ，且唯一的数是负数，那就直接输出这个负数。

4. 对于 $0$ 也要特殊讨论。如果全部是 $0$ 或者除 $0$ 外只有一个负数，那么只能输出 $0$。

代码十分简短。

~~感觉思路和其他大佬都很像~~

### AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,f,l,ans[105],t; //ans数组存储负数，f为负数个数，l为零的个数 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a);
    	if(a>0) printf("%d ",a); //如果是正数就直接输出 
    	else a==0?l++:ans[++f]=a; //三目运算，如果是零l++，否则存到负数数组里 
	}
	if(f==1&&n==1) printf("%d",ans[1]); //只有一个负数 
	else if(l==n||(f==1&&l==n-1)) printf("0"); //0的特殊情况 
	else{
		sort(ans+1,ans+f+1); //对负数排序 
		if(f%2==0) for(int i=1;i<=f;i++) printf("%d ",ans[i]); //偶数个就全部输出 
		else for(int i=1;i<f;i++) printf("%d ",ans[i]); //奇数个就输出绝对值大的f-1个 
	}
    return 0;
}

```
~~望过~~

---

## 作者：BYWYR (赞：1)

## Problem

有 $n$ 个数 $a_i$
 ，请你从中**至少**选出一个数，使它们的乘积**最大**。
 
## Soulution

分 $3$ 种情况讨论：

- 正数不会让乘积变成负数，只会让乘积越来越大。所以，遇到正数，就直接选择。

- 负数可能会让乘积变成负数，但是两个负数相乘，又可以变为正数。所以，在这里我们需要选择偶数个绝对值尽可能大的负数。
  
  举个例子：
  ```
  -7 -5 -3
  ```
  显然选择 $-7$，$-5$ 是最优的，结果为 $35$。
- $0$，乘一下它会让整个式子变为 $0$。但是在只有 $1$ 个负数且剩余的数全是 $0$ 时，选择 $0$ 就可以让式子的结果尽可能的大，从而舍弃掉那个负数。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],fu,zero,x,cnt;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(x>0) { //正数直接选择
			printf("%d ",x);
			continue;
		}
		a[++cnt]=x;
		if(a[cnt]<0) ++fu;
		else ++zero;//非正数的情况
	}
	if(n==1&&fu==1) {//只有一个负数
		printf("%d ",a[1]);
		return 0;
	}
	if(zero==n||(fu==1&&zero==n-1)) {//只有1个负数且剩余的数全是0 
		printf("0\n");
		return 0;
	}
	sort(a+1,a+cnt+1);
	for(int i=1;i<=fu/2*2;i++)
		printf("%d ",a[i]);//两个绝对值越大的负数乘起来结果更大
	return 0;
}
```





---

## 作者：feicheng (赞：1)

一道细节很多的题  ~~（本蒟蒻提交了7次才过）~~
## 题意简述
有 $n$ 个数，**求至少选择一个数**，使选择的数相乘能达到最大乘积的一种方案。

$1 \le n\le100,1\le a_i \le 100$
## 思路讲解
首先我们知道，如果负数只有一个，那么选它是肯定不划算的。所以我们可以把负数进行配对，只要有两个负数就可以选择。

但是这样的话就有一个坑：**如果数只有一个且是负数**，这个程序就不会选这个数，不满足至少选择一个的要求。所以对于这种情况要特判

然后提交上去你会发现你又 WA 了，原因是形如下面的这种数据：
```
5
-1 0 0 0 0 
```
所以我们还要特判：如果负数只有一个且其余的都是0，输出0。

然后我们将数组排序，因为优先选择绝对值大的负数相乘是最佳方案。就可以 AC 本题了
## 核心代码

```cpp

constexpr int iN = 110;
int a[N],vis[N],n,pos,Znum,Fnum;//Znum是0的个数，Fnum是负数的个数
int main(int argc,const char *argv[]){
	std::ios::sync_with_stdio(false);
   std::cin >> n;
   for(ri i = 1;i <= n;++i) std::cin >> a[i],Znum += a[i] == 0,Fnum += a[i] < 0;
   if(n == 1) return std::cout << a[n] << '\n',0;//特判只有一个数的情况
   if(Znum == n || Znum == n - 1 && Fnum == 1) return std::cout << 0,0;//特判全是0和n-1个0＋一个负数的情况
   std::sort(a+1,a+1+n);
   for(ri i = 1;i <= n;++i) {
      if(a[i] < 0) {
         if(!pos) pos = i;//pos表示上个未配对负数的位置
         else vis[pos] = vis[i] = 1,pos = 0;
      }
      else if(a[i] > 0) vis[i] = 1;
   }
   for(ri i = 1;i <= n;++i) if(vis[i]) std::cout << a[i] << ' ';
	return 0;
}


```

---

## 作者：yizhiming (赞：1)

# 贪心题

### 前言
题目链接：[$Link$](https://www.luogu.com.cn/problem/CF45I)

~~第一次发题解的蒟蒻求刷咕值~~
### 题目大意
~~这道题一堆巴拉巴拉的，英语渣滓哭泣~~，总之就是说你要输入 $n$ 个数字，然后输出最大乘积用到的数字，最少输出1个数，上限自然是 $n$ 个这题看似很水，实际~~好细啊~~，好多细节。
### 题目解析
这道题的话，我个人是选择先用数组存入数据，用变量存储 $0$，正数和负数的数量，然后通过判断这些变量来进行操作。
具体解释放在代码注释里:
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int a[110],l,zh,fu,minn =1010,minfu = 1010,ans;
bool shu = 0;//这个地方拿来记录是否输出，因为我个蒟蒻不知道该怎么解决运行完一种方式后，直接退出。
int main(){
	int n;
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];//读入，不做解释。
		if(minfu>abs(a[i])&&a[i]<0){
			minfu = abs(a[i]);
			ans = i;//ans拿来存储绝对值最小的负数的位置。
		}//这里用abs来获取绝对值，用minfu来记录绝对值最小的负数，后面用得到。
		if(minn>a[i]){
			minn = a[i];
		}//这里是存储最小值，不多做解释。
		if(a[i]>0){
			zh++;
		}else if(a[i]<0){
			fu++;
		}else {
			l++;
		}//记录0,正数，负数的出现次数。
	}
	if(fu%2==0){//判断，当负数的个数为偶数时，所有的负数相乘为正数，因为负数乘负数为正数，这种情况时，所有数字都输出，0除外。
		for(int i=1;i<=n;i++){
			if(a[i]!=0){//判断是否是0
				cout<<a[i]<<" ";
				shu=1;//表示已经输出过了。
			}
		}
	}else{
		for(int i=1;i<=n;i++){
			if(a[i]!=0&&i!=ans){//如果目前数字不是0，而且不是绝对值最小的负数，就进行输出，以保证绝对值较大的负数和正数能够被输出。
				cout<<a[i]<<" ";
				shu =1;//同上。
			}
		}
	}
	if(zh==0&&(fu%2!=0||fu == 0)&&shu==0){//进行判断，如果正数数量为0才可能输出0，判断负数数量是否是偶数，或者是否为零，并且没有输出其他的数字，才会运行，以保证不会重复输出。
		if(l>0){//当输入内有0时，则输出0。
			for (int i=1;i<=l;i++){
				cout<<0<<" ";
			}
		}else {//当没有0时则会输出绝对值最小的负数，即最大的负数。
			cout<<a[ans];//ans在这里用到了，输出最大负数。
		}
	}
	return 0;
}
```
### 后记
蒟蒻哪里写错了还请大佬给指导，祈祷过审，代码很多地方比较麻烦，大佬自行修改吧。
## 完结撒花


---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF45I)

这道题要非常细心才能做出来，注意特判 （这道题应该是普及 -               吧）
# 思路与特判条件：

既然要求已知数中的最大积且至少要有一个数，那么：
1. 遇到正数直接输出（因为它不会使最后的积变小，类似于贪心）
2. 遇到负数时统计数量并记录它的数值，最后从小到大排序（因为负负得正，越小的两个负数相乘的值会越大，如果有奇数个负数则只能输出奇数 $-1$ 个）
3. 遇到 $0$ 时统计个数，如果 $0$ 的个数刚好为 $n$ 或者为 $n-1$ 且其余的那一个数为负数，则输出 $0$（特判条件）
4. 只有一个数且那个数是负数时，输出那个数（因为不能不选）

知道了思路与特判条件，就来贴代码吧

# AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,x,cntb=0,cntc=0,b[105]={0};//n 为 题目的数量；x 为输入的数；cntb ，cntc 分别存储负数与 0 的个数 ，b[]数组存储负数的数值 
	cin>>n;//输入 
	for(int i=1;i<=n;i++){//循环输入 
		cin>>x;//输入 
		if(x>0){//如果它是正数 
			cout<<x<<" ";//直接输出 
		}
		else if(x<0){//如果它是负数 
			cntb++;//负数计数器 +1 
			b[cntb]=x;//记录当前值 
		}else{//如果它是 0 
			cntc++;//0 的计数器 +1 
		}
	}
	if(n==1&&cntb==1){//只有一个数且这个数是负数 
		cout<<b[1]<<endl;//输出这个数 
		return 0;//结束程序 
	}
	if(cntc==n-1&&cntb==1||cntc==n){//一个负数其余都是 0 或全部都是 0 的情况 
		cout<<0<<endl;//输出 0 
		return 0;//结束程序 
	}
	sort(b+1,b+cntb+1);//将负数排序（默认从小到大） 
	if(cntb%2==1)cntb--;//当只有奇数个负数，则只能选奇数 -1 个 
	for(int i=1;i<=cntb;i++)cout<<b[i]<<" ";//输出最小的 cntb 个 
	return 0;//结束程序 
}
```



---

## 作者：WKAHPM (赞：0)

题目大意：给你$N$个整数，让你从中选$r$个数($0<r \leq N$)，使得它们的乘积最大。输出任意一组解

思路：（~~大佬勿喷~~）

- 1 我们知道几个正整数的乘积总是正数，所以遇到正整数直接输出就好啦

- 2 遇到负数就不同了，我们知道“奇负偶正”，于是就有两种情况：

    - 1 如果有偶数个负数，因为“偶正”，所以全部输出
    
    - 2 如果有奇数个负数，我们只能输出个数-1个负数，并且这些负数的绝对值最大

- 3 接下来还需要三个特判

    - 特判1：如果$N=1$并且这个数小于等于0，输出这个数

    - 特判2：如果$N$（$N>1$）个整数全是0，输出0
    
    - 特判3：如果$N$（$N>1$）个整数中全是非正数（只有0和负数），如果只有1个负数并且0的个数不为0，输出0（因为0比负数大）
    
- 4 然后。。。你就[AC](https://www.luogu.org/recordnew/show/15426590)了

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],sum1=0,sum2=0;//sum1统计0的个数，sum2统计负数的个数
int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&a[i]);
		if(a[i]<0) sum2++;//a[i]是负数，sum2++
		else
          if(a[i]==0) sum1++;//a[i]是0，sum1++
          else
			printf("%d ",a[i]);//a[i]是正数，输出！
	}
	sort(a+1,a+n+1);//因为要取绝对值最大的负数，所以先排序
	if(sum2%2==0)//偶数个负数全部输出
	{
		for(int i=1; i<=sum2; i++)
		{
			printf("%d ",a[i]);
		}
	}
	else//奇数个负数输出个数-1个
	{
		for(int i=1;i<=sum2-1;i++)
	    {
	    	printf("%d ",a[i]);
		}
	}
    if(n==1&&a[1]<=0) 
    {
       cout<<a[1];
       return 0;
    }
	if(sum1==n) cout<<0;//全是0
	if(sum1+sum2==n&&sum2==1) cout<<0;//全是负数和0且负数只有一个
	return 0;
}

```

---

