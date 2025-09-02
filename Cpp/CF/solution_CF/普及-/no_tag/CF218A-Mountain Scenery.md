# Mountain Scenery

## 题目描述

Little Bolek has found a picture with $ n $ mountain peaks painted on it. The $ n $ painted peaks are represented by a non-closed polyline, consisting of $ 2n $ segments. The segments go through $ 2n+1 $ points with coordinates $ (1,y_{1}) $ , $ (2,y_{2}) $ , $ ... $ , $ (2n+1,y_{2n+1}) $ , with the $ i $ -th segment connecting the point $ (i,y_{i}) $ and the point $ (i+1,y_{i+1}) $ . For any even $ i $ $ (2<=i<=2n) $ the following condition holds: $ y_{i-1}&lt;y_{i} $ and $ y_{i}&gt;y_{i+1} $ .

We shall call a vertex of a polyline with an even $ x $ coordinate a mountain peak.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF218A/96f9e39adc23f097d41530b53dba00529f48c7bd.png) The figure to the left shows the initial picture, the figure to the right shows what the picture looks like after Bolek's actions. The affected peaks are marked red, $ k $ = 2. Bolek fancied a little mischief. He chose exactly $ k $ mountain peaks, rubbed out the segments that went through those peaks and increased each peak's height by one (that is, he increased the $ y $ coordinate of the corresponding points). Then he painted the missing segments to get a new picture of mountain peaks. Let us denote the points through which the new polyline passes on Bolek's new picture as $ (1,r_{1}) $ , $ (2,r_{2}) $ , $ ... $ , $ (2n+1,r_{2n+1}) $ .

Given Bolek's final picture, restore the initial one.

## 样例 #1

### 输入

```
3 2
0 5 3 5 1 5 2
```

### 输出

```
0 5 3 4 1 4 2 
```

## 样例 #2

### 输入

```
1 1
0 2 0
```

### 输出

```
0 1 0 
```

# 题解

## 作者：Night_sea_64 (赞：2)

本题是个超级无敌大水题，难度红，主要算法就是模拟。

主要思路就是如果这个数 $-1$ 之后还比左右两边的数大，并且减的个数还不到 $k$ 个就直接把这个数 $-1$。有 spj 所以可以随便弄。

代码如下：

```cpp
#include<iostream>
using namespace std;
int a[210];
int main()
{
    int n,k;
    cin>>n>>k;
    n=2*n+1;
    for(int i=1;i<=n;i++)cin>>a[i];
    int cnt=0;//cnt 记录已经减过的个数。
    for(int i=1;i<=n;i++)
    {
        if(i%2==0)
            if(a[i]-1>a[i-1]&&a[i]-1>a[i+1]&&cnt<k)a[i]--,cnt++;//满足要求就把这个数 -1 然后更新 cnt。
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：OI_AKed_me (赞：1)

# CF218A Mountain Scenery #
[原题链接](https://www.luogu.com.cn/problem/CF218A)
## 思路 ##
因为它只改下标为偶数的数，所以改变一个数不会影响其他的数，那我们就可以贪心：如果一个数可以改就改，改满 $ k $ 个就直接输出。

需要注意的是数组一定要开到 $ 2n+1 $，还有是这题有  spj，所以不用担心过不了样例。
## 代码 ##
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ss stable_sort
#define inf INT_MAX
#define R read()
#define umap unordered_map
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#pragma GCC opitimize(3)
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
inline void StringRead(string &str){
    char s=getchar();
    while(s==' '||s=='\n'||s=='\r'){
        s=getchar();
    }
    while(s!=' '&&s!='\n'&&s!='\r'){
        str+=s;
        s=getchar();
    }
}
inline int read(){
    int X=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch))X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,k,a[505];
int main(){
#ifdef online
	freopen(".in", "r", stdin);
	freopen(".out", "w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	n=R,k=R;
	for(int i=1;i<=2*n+1;i++){
		a[i]=R;
	}
	for(int i=2;i<=2*n;i+=2){
		if(a[i-1]<a[i]-1&&a[i]-1>a[i+1]){
			a[i]--;
			k--;
			if(!k) break;
		}
	}
	for(int i=1;i<=2*n+1;i++){
		write(a[i]);putchar(' ');
	}
//	cout<<endl<<clock();
	return 0;
}

```

---

## 作者：xiaomuyun (赞：1)

# CF218A Mountain Scenery 题解
[题目传送门](https://www.luogu.com.cn/problem/CF218A)

~~详细的解法来了~~
## 题意分析
给定一个长度为 $2\times n+1$ 的序列，且这个序列满足：对于每个 $i$（$1\leq i\leq 2\times n+1$），如果 $i$ 是偶数，则一定满足 $a_{i-1}<a_i$ 且 $a_i>a_{i+1}$。你需要求出一个序列，其中有 $k$ 个下标为偶数的数相比输入的序列被减了 $1$，但是这个序列依然满足上面的条件。
## 题目分析
我们可以发现，对于每个是偶数的 $i$，如果 $a_i-1>\max\begin{cases}a_{i-1}\\a_{i+1}\end{cases}$，则这个数是可以 $-1$ 的，然后 $ans_i$ 设为 $a_i-1$ 即可；否则就不对这个数做任何操作。

要注意：**每个是偶数的 $i$ 只能减一次 $1$！** 我这个蒟蒻就是因为一开始觉得一个 $i$ 可以减很多次 $1$，[然后错了](https://codeforces.com/problemset/submission/218/137076348)。
## 代码实现
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
int n,k,a[210],ans[210];
int main(){
	scanf("%d%d",&n,&k);
	n=(n<<1)|1;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) ans[i]=a[i];
	for(int i=2;i<=n;i+=2){
		if(!k) break;//如果已经将k个偶数的i减一了，就可以直接退出循环输出即可
		if(a[i]-1>a[i-1]&&a[i]-1>a[i+1]) --k,--ans[i];//如果它-1之后依然比两边的都大，就可以减一
	}
	for(int i=1;i<=n;++i) printf("%d ",ans[i]);
	putchar('\n');//你真的不点个赞吗
	return 0;
}
```
## 总结
应该算是一道挺简单的入门题。希望大家能点个赞，管理员求过！

---

## 作者：Transparent (赞：1)

### 题目大意：

有一个画了 $n$ 个山峰的图片，
由不闭合折线表示，
共有 $2n$ 个段。
对于任何偶数 $i$ （$2≤i≤2n$），
以下条件成立：$y_i-1 <y_i$ 和$ y_i> y_i + 1$
（ $y_i$ 表示第 $i$ 个点的y坐标）
Little Bolek 对图片做了恶作剧，
他选择了其中的 $k$ 个山峰，
并将这 $k$ 个山峰的高度增加 $1$ ，
即将这 $k$ 个点的y坐标加 $1$ 。
给你恶作剧后的图片
（输入这 $2n+1$ 个点的y坐标），
请你还原。
若有多种可能，
输出任意一种。

---------------

从头到尾遍历每一个编号位偶数的点，
若它的高度减1（即若这个点还原后的高度）
比它上一个点的高度高，
也比它下一个点的高度高，
就还原这个点，
即使它的高度减1。

判断高度是因为，
如果当前点高度减1后，
不比它上一个点的高度高，
或不比它下一个点的高度高，
就不满足 $y_i-1 <y_i$ 和$ y_i> y_i + 1$ 。

最后：数组需要开到 $2n+1$ 

------------

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[202],ans[202];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n*2+1;i++)
	{
		scanf("%d",a+i);
	}
	for(int i=1;i<=n*2+1;i++)
	{
		if(i%2==0&&a[i-1]<(a[i]-1)&&a[i+1]<(a[i]-1)&&k>0)//判断高度条件 
		{
			k--;//用k来计数 
			ans[i]=a[i]-1;//还原 
		}
		else
		{
			ans[i]=a[i];
		}
	}
	for(int i=1;i<=n*2;i++)
	{
		printf("%d ",ans[i]);
	}
	printf("%d\n",ans[n*2+1]);
	return 0;
}
```
~~别试样例了，输出不一样（有Special Judge）~~

---

## 作者：KK_lang (赞：0)

## 思路

如果这个数是偶数下标，并且 $-1$ 之后还比左右两边的数大，并且减的个数还不到 $k$ 个，就直接把这个数 $-1$。

## AC Code

直接按照思路开搞！

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, k;
int a[210];

int main()
{
    cin >> n >> k;
    n = 2 * n + 1; // 依题意，长度不为 n，为 2 * n + 1
    for (int i = 1; i <= n; i++) cin >> a[i];
    int cnt = 0; // 记录减的个数
    for (int i = 1; i <= n; i++) // 遍历
    {    //偶数下标     减一后比左边大         减一后比右边大    没到 k 个
        if (i % 2 == 0 && a[i] - 1 > a[i - 1] && a[i] - 1 > a[i + 1] && cnt < k)
            a[i]--, cnt++; // 符合条件就操作，并且累加个数
        cout << a[i] << " "; // 输出序列
    }
    return 0;
}
```

红题水平，都可以 AC 吧！

---

## 作者：Qiancy1427 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF218A)

~~简简单单的签到题~~

### 题意

给定一个长为 $2 \times n+1$ 的数列 $a$。如果 $i$ 是偶数，那么 $a_i>a_{i-1}$ 且 $a_i<a_{i+1}$。其中有 $k$ 个下标为偶数的数比原来减 $1$ 后依然满足上述规则，输出任意一个满足要求的数列。保证有满足要求的答案（这句是在英文里的）。

### 理解

简单的遍历思路，检验每一个下标为偶数的数是否可以减 $1$，如果可以就执行操作。操作 $k$ 次后，直接全部输出，结束程序。

其中，在检验操作后是否小于前后两个数时，既可以用两个条件判断，也可以用最大值来判断。

注意，每一个数只能减一次（执行一次操作）。	

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[300];	//数组要开到2n+1 
int main(){
	cin>>n>>k;
	for(int i=1;i<=n*2+1;i++)	cin>>a[i];
	for(int i=2;i<=n*2;i+=2){
		if(!k)	break;	//如果k小于0，跳出循环 
		if(a[i]-1>max(a[i-1],a[i+1])){	//检查是否小于前后两个数 
			a[i]--;
			k--;
		}
	}
	for(int i=1;i<=n*2+1;i++)	cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：Fr0sTy (赞：0)

### 题意简述
------------

给定两个整数 $n,k$。

再给定一个长度为 $2 \times n +1$ 的数列，这个数列的第偶数项 $a_i$ 满足 $a_i > a_{i-1}, a_i > a_{i+1}$。

想在将这个数列的 $k$ 个偶数项删去 $1$（不能重复）且这个数列仍然满足原数列的条件，输出这个数列。

### 解题思路
------------

我们可以从 $1$ 到 $2 \times n + 1$ 扫一遍，如果遇到偶数项且这个偶数项 $a_i$ 满足 $a_i > a_{i-1} + 1 , a_i>a_{i+1}+1$，就将 $k$ 减 $1$，直到 $k=0$。

之所以要满足 $a_i > a_{i-1} + 1 , a_i>a_{i+1}+1$ 而不是 $a_i > a_{i-1}, a_i > a_{i+1}$，是因为这个偶数项将要减 $1$，就有可能出现 $a_i = a_{i-1}$ 或 $a_i > a_{i+1}$ 的情况，这样就不满足题意了。

本题有 spj。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1000005];
int main() {
	scanf("%d%d",&n,&k); n=2*n+1;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=2;i<=n;i+=2) {
		if(k==0) break;
		if(a[i]>a[i-1]+1&&a[i]>a[i+1]+1) a[i]--,k--;
	}
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
//code by TheCedar
```

---

## 作者：hanyuchen2019 (赞：0)

简单模拟。

依次判断偶数位上的“山峰”，如果其高度 $-1$ 后仍然比左右两边高（即仍然是山峰），就将高度 $-1$，直到一共减了 $k$ 次。

Tips:
1. 整个序列真正的长度为 $2n+1$ ，数组也要开大！！！
2. 本题有 `Special Judge` ，不用担心你的代码过不了样例。

```cpp
#include<iostream>
using namespace std;
int a[205];
int main()
{
    int n,k;
    cin>>n>>k;
    n=n*2+1;//现在的n是序列的真正长度了
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=2;i<n;i+=2)
    {
        if(a[i-1]<a[i]-1&&a[i+1]<a[i]-1)//判断是否比两边高
            k--,a[i]--;
        if(!k)break;//减够k次就退出
    }
    for(int i=1;i<=n;i++)
        cout<<a[i]<<" ";
    return 0;
}

```

---

