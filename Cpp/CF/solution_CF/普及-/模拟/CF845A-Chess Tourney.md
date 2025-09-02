# Chess Tourney

## 题目描述

Berland annual chess tournament is coming!

Organizers have gathered $ 2·n $ chess players who should be divided into two teams with $ n $ people each. The first team is sponsored by BerOil and the second team is sponsored by BerMobile. Obviously, organizers should guarantee the win for the team of BerOil.

Thus, organizers should divide all $ 2·n $ players into two teams with $ n $ people each in such a way that the first team always wins.

Every chess player has its rating $ r_{i} $ . It is known that chess player with the greater rating always wins the player with the lower rating. If their ratings are equal then any of the players can win.

After teams assignment there will come a drawing to form $ n $ pairs of opponents: in each pair there is a player from the first team and a player from the second team. Every chess player should be in exactly one pair. Every pair plays once. The drawing is totally random.

Is it possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing?

## 样例 #1

### 输入

```
2
1 3 2 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1
3 3
```

### 输出

```
NO
```

# 题解

## 作者：ShineEternal (赞：7)

~~比楼上简单的代码~~
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[210];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++)//读入2n个数
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+2*n+1);//排序要排到2*n
    if(a[n]<a[n+1])//判断从中间断开能否符合条件（贪心思想）
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}
```

---

## 作者：Nivi (赞：3)

蒟蒻的第一篇题解QWQ

[原题在这里](https://www.luogu.com.cn/problem/CF845A)

------------
稍微讲一下思路吧

看题我们可以知道，将2n个数分成两组，A和B,令B组的每一个数都大于A组

那不就比较A组中最大的和B组中最小的不就完了么！(窃喜

平均分成两组，且一共有2n个数，那一组就是n个数

直接上快排和一个简单的判断语句



------------
代码如下：
```cpp
#include<bits/stdc++.h>//万能头万岁QWQ
using namespace std;
int main(){
    int n,m[201];//定义n和2*n的数组
    cin>>n;//输入n
    for(int i=1;i<=n*2;i++){
        cin>>m[i];
    }//输入m
    sort(m+1,m+2*n+1);//排序
    if(m[n]<m[n+1]){
        cout<<"YES"<<endl;
    }//如果成立
    else{
        cout<<"NO"<<endl;
    }//如果不成立
    return 0;//完美结束
}
```


------------
第一遍提交，很沙雕的，忘记了排序QWQ

望通过

---

## 作者：TLMPEX (赞：1)

思路：先把输入的数从小到大排序，A组的最后一个是第n个数，B组的第1个数是第n+1个数，比较大小，如果第n个数小于第n+1个数，输出``YES``了，否则输出``NO``了。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int k[201];
int main(){
	int n,i;
	cin>>n;
	for(i=1;i<=2*n;i++)
		cin>>k[i];
	sort(k+1,k+2*n+1);//排序
	if(k[n]<k[n+1])cout<<"YES";
	else cout<<"NO";
}
```


---

## 作者：Fat_Fish (赞：0)

这道题我们要找到什么情况下不成立。

一开始，我想:用$sort$排序，分成两组，不就好了吗？怎么会有不成立呢？

后来，冥思苦想，想到了**两数相等**的情况。

这里，我们只要比较**较小组的最大值**，**较大组的最小值**即可。

举个例子，有$1$,$4$,$3$,$4$;排好后就是$1$,$3$,$4$,$4$。

$3<4$符合情况，可见，分在同组内相等时不影响的。

$Code$
```cpp
#include<iostream>
#include<bits/stdc++.h>//头文件
using namespace std;
int main(){
	int n;
	cin>>n;
	int a[n*2+1];//定义数组，我从一开始，所以加一
	for(int i=1;i<=n*2;++i){
		cin>>a[i];//输入
	}
	sort(a+1,a+1+n*2);//按照升序排序，其实降序也可以，就是要手写cmp
	if(a[n]<a[n+1]){//比较临界点的大小
		cout<<"YES\n";
		return 0;//直接结束，剩下的就是不符合的情况
	}
	cout<<"NO\n";
	return 0;
}
```
谢谢观看！

---

## 作者：王炸拆开打 (赞：0)

第一次这么快就做出来，还是有些东西不一样，大家多多指教

第二部分为更加具体的过程，实在没有思路的同学可以转到 **（二）** 进行阅读

# 核心思想：快排+小聪明

### （一）部分内容

大家肯定都想到了排序但是这里有两种不一样的判断方法

1.

```cpp
if(a[n]!=a[n+1]) printf("YES");//如果不一样 
else printf("NO");//一样 
```
2.

```cpp
if(a[n]<a[n+1]) printf("YES");//如果不一样 
else printf("NO");//一样 
```
显然，第一个~~更加凸显我们的小聪明~~


------------
### （二）精细讲解

首先，题目给了我们一个数组$q[2n]$，将其分为两个部分$A$和$B$，并使$A[i]$大于$B[i]$，如果没有其他要求，显然排序的方法就是将数组从大到小排序，前半部分为$B$，后半部分为$A$

那么目前的关键点就是$B$中最大的元素（$q[n]$）$A$中最小的元素（即$q[n+1]$)是否符合题目即可（参考 **（一）** 部分）

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int q[1001],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n+n;i++) scanf("%d",&q[i]);//注意数组长度
	sort(q+1,q+n+n+1);//快速排序 
	if(q[n]!=q[n+1]) printf("YES");//如果不一样 
	else printf("NO");//一样 
	return 0;
}
```



---

## 作者：Soshine_溯闪 (赞：0)

我 **第五次** 传题解。     
这题是**排序**加**贪心**加**模拟**。    
唯一的坑点是 $A$ 和 $B$ 两组个数要相等。     
# 整体思路
1. 将 $a$ 数组从小到大排序。    
2. 将 $a$ 数组对半劈开，看 $A$ 组的最大数是否小于 $B$ 组的最小数，由于$a$ 数组已经排过序，所以如果分的 $A$ 的最大值还小于 $B$ 的最小值，那么 $A$ 的其他数肯定都是小于 $B$ 的任何数的，那么就可以直接输出 $YES$ 。
3. 否则，因为贪心思路是 $A$ 越小越好，并且 $a$ 数组已经排过序， $A$ 分的是最小的一半，所以如果 $A$ 分最小都不行的话，那么答案就是 $NO$ 。     
# 思考亿下，就可以看程序了
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
const int maxn=220;
int a[maxn],n;		//定义 
int main(){
	cin>>n;
	for(int i=1;i<=n*2;i++) cin>>a[i];		//输入 
	sort(a+1,a+1+n+n);		//排序 
	if(a[n]<a[n+1]) cout<<"YES"<<endl;		//满足条件就输出YES 
	else cout<<"NO"<<endl;		//否则输出NO 
	return 0;
}
```
跪求管理员给过。     

---

## 作者：Contemptuous (赞：0)

既然 $A$ 组都要比 $B$组小，那么我们可以将它们先从小到大排个序，然后判断中间的两个数中，第一个数一定要比第二个数小。

举个例子。

我们有一组数：$6,1,23,4$，我们先把他们从小到大排序，变成$1,4,6,23$，然后判断中间的两个数即$4$和$6$，$4$比$6$小，那么这组数就成立。我们可以把它分成：$1,4$和$6,23$。

上代码。

```cpp
#include <iostream>
#include <bits/stdc++.h>

using namespace std;


int main()
{
	
	int n, s[10001];
	
	cin >> n;
	
	for (int i = 1; i <= n*2; ++i)
	{
		cin >> s[i];
	}
	
	sort (s+1, s+2*n+1);
	
	if (s[n] < s[n+1])
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
	
	return 0;
} 
```

---

## 作者：Elma_ (赞：0)

## Descreption
给出$n\times2$个人的成绩，问能否依据成绩把这些人平均分成两组$A$,$B$，使得从$A$,$B$两组中各自任选一个人出来，$A$组中选出来的人的成绩都小于$B$组。

## Solution

贪心思想。

可以对每个人的成绩进行从小到大的排序，然后从中间分成两组，较小的一组为$A$组，另一组为$B$组，则第$n$个数就是$A$组中最大的数，第$n+1$个数就是$B$组中最小的数。

易证若$B$组中最小的数大于$A$组中最大的数，则题目成立。又因为成绩已经从小到大排过序，则第$n+1$个数大于等于第$n$个数。所以当且权当第$n$个数和第$n+1$个数相等时，应输出NO。

## Code
```
#include <iostream>
#include <algorithm>
using namespace std;

int n, a[205];

int main(void)
{
	cin>>n;
	for(int i=1;i<=2*n;i++)//注意人数是n的两倍
		cin>>a[i];
		
	sort(a+1, a+2*n+1);//从小到大排序
	
	if(a[n] == a[n+1])//若相等
		cout<<"NO"<<endl;
	else
		cout<<"YES"<<endl;
	return 0;
}
```


---

## 作者：hensier (赞：0)

这道题可用快排大法。我们将这$2\times n$个数排列之后$(a[0]-a[2\times n-1])$，再比较$a[n],a[n-1]$即可。

$AC$代码：

```cpp
#include<bits/stdc++.h>//万能头文件
int n,a[200];
char s[][4]={"NO","YES"};
int main()
{
    scanf("%d",&n);//输入n
    for(int i=0;i<2*n;i++)scanf("%d",&a[i]);//输入
    std::sort(a,a+2*n);//快排
    printf("%s",s[a[n-1]<a[n]]);//输出
}
```

---

## 作者：PC_DOS (赞：0)

这是一道模拟题，只需要对输入的2n个数据从小到大排序，并判断第n项(即第一组最大项)是否比第n+1项(即第二组最小项)小即可。如果第n项是否比第n+1项小，那么可以分出，否则不能分出符合要求的组。

~~谁能告诉我为什么我一提交C++11代码就出错QAQ~~

代码:
```
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std; //头文件和命名空间
int main(){
    ios::sync_with_stdio(false); //输入输出加速
    int iTemp,i,nCount; //iTemp-暂存输入；i-循环计数器；nCount-组大小
    vector<int> arrVal; //存放数据的动态数组
    cin >> nCount; //读入大小
    for (i = 1; i <= 2 * nCount; ++i){ //循环读入，注意有2*nCount个数据
        cin >> iTemp; //读入
        arrVal.push_back(iTemp); //压入动态数组
    }
    sort(arrVal.begin(), arrVal.end()); //排序
    if (arrVal[nCount - 1] < arrVal[nCount]) //判断第n项(即第一组最大项)是否比第n+1项(即第二组最小项)小，注意vector索引从0开始因此改为判断第n-1项(即第一组最大项)是否比第n项(即第二组最小项)小
        cout << "YES"; //是
    else //否则不能分出符合题意的两组
        cout << "NO"; //否
    return 0; //结束
}
```

---

