# 数列分段 Section I

## 题目描述

对于给定的一个长度为 $N$ 的正整数数列 $A_i$，现要将其分成**连续**的若干段，并且每段和不超过 $M$（可以等于$M$），问最少能将其分成多少段使得满足要求。


## 说明/提示

对于$20\%$的数据，有$N≤10$；

对于$40\%$的数据，有$N≤1000$；

对于$100\%$的数据，有$N≤100000,M≤10^9$，$M$大于所有数的最大值，$A_i$之和不超过$10^9$。


将数列如下划分：

$[4][2 4][5 1]$

第一段和为$4$，第$2$段和为$6$，第$3$段和为$6$均满足和不超过$M=6$，并可以证明$3$是最少划分的段数。


## 样例 #1

### 输入

```
5 6
4 2 4 5 1```

### 输出

```
3```

# 题解

## 作者：Dr_殇 (赞：109)

#很简单的一道暴力题这道题有两种方法，一种是边读边做，一种是读完数组再做。这两种方法对新手来说都很简单，不过边读边做相对简单一点。


##注意：ans一开始的初值必须为1，因为最后一段是加不进去的，所以初值一定要为1。


##代码如下：





```cpp
#include <cstdio>//头文件准备
using namespace std;
int n,m,ans=1;//ans的初值要为1
int main(){
    scanf ("%d %d",&n,&m);
    int k=0;
    while (n--){//完全的边读边做
        int a;
        scanf ("%d",&a);//读入a
        if (k+a<=m){//判断k+a是否大于m，如果大于，ans要加1，然后a独立为一段；如果小于等于，k就要加上a
            k+=a;
        }
        else{
            ans++;
            k=a;
        }
    }
    printf ("%d\n",ans);//做完之后输出，结束
    while (1);//反抄袭
}
#珍爱生命，拒绝抄袭！
```

---

## 作者：xun薰 (赞：64)

思路 贪心

对于当前元素只有两种选择 并到其他段上和单独一段。

当前元素能找到和在一起的段就并上，找不到就自己就自己一段。

ans一开始设置为n+1，因为还要并0号元素，没并一次少一个段。

最短c++代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a[100002],ans;
int main(){
    scanf("%d%d",&n,&m);ans=n+1;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i]+a[i-1]<=m)a[i]+=a[i-1],ans--;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：强力人 (赞：14)

**很简单的一道题**

首先读入，不解释；

其次从第一个开始搜索，定义一个sum表示这一段的和，每次搜索先判断sum与a[i]的和是否大于m**(我发现全都用int类型就能过）**，

如果大于，ans++，sum归零，加上a[i]，重复以上。

如果小于等于，sum加上a[i]，重复以上；

最后有一个小坑，如果搜索完后，sum不为零，ans要+1；

输出,AC


```cpp
END;
#include<cstdio>
using namespace std;
int a[100010] ;
int main()
{
    int n,m,i,j,k,ans=0,sum=0;
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++)
    {
        if(a[i]+sum>m)
        {
            sum=0;
            ans++;
        }
        sum=sum+a[i];
    }
    if(sum)
    {
        ans++;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：JimmyF (赞：13)


~~哈哈，小学生又来发题解啦！~~   

好了，废话不多说，让我们进入正题。

这题属于一道比较容易的贪心题。

大体思路就是：

1.每次判断sum+当前数列长度是否<m，如果小于则sum+当前数。sum代表的就是当前段的总长度，这段话则表示当前段还能容纳下这段数列。

2.如果大于等于m，则需要成立一个新的段。则ans++，ans表示总段数。如果sum刚好等于m，则代表上一段没有剩余，如果有剩余的话，就不能将这段数列包含进去，所以sum=ai，就将这段数列作为新段的开头。

3.最后如果sum>0，则代表还有数没有被分段，所以ans++。输出ans。
   
    #include<iostream>  //文件头
    using namespace std;  
    int n,m,a[100010],ans,sum;  //定义变量
    int main()
    {
        cin>>n>>m;   
        for(int i=1; i<=n; i++)
        cin>>a[i];       //输入
        for(int i=1; i<=n; i++)
        {
            if(sum+a[i]<m)sum+=a[i]; //判断是否可以入段
            else
            {
                ans++; //不可入段则总段数++
                if(sum+a[i]>m)sum=a[i]; //判断有剩余的情况，如果有就不能将这段数列包含进去，就将这段数列作为新段的开头。
                  else sum=0; //没有剩余则段的长度归0
            }
        }
        ans+=(sum>0);   //判断一个数还没有被分段的特殊情况
        cout<<ans; //输出总段数
        return 0;  
    }
    
## 希望可以帮助大家，谢谢！
### 欢迎大家指教，评论与点赞。

---

## 作者：LMB_001 (赞：13)

本题并不难，你只要弄一个容器，往里面装，如果>m了就先把计数器加一，再把容器置为当前这个数，主要是数据太水了，

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[100005];
int count(){
    int s=1,t=0;//s就是能装多少个容器，t是模拟容器装的过程
    for (int i=1;i<=n;i++){
        t+=a[i];//往里面装
        if (t>m){
            s++;
            t=a[i];
```
}//如果装过头了，就再加一个容器，注意新容器里应该是a[i]
```cpp
    }
    return s;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];//读入
    cout<<count();//简单明了
}
```

---

## 作者：first_fan (赞：8)

## 作为一个突然想~~浪费人生中的美好10分钟~~复习一下贪心的人
### 我点开了```贪心```标签，于是乎就水了这道题……
#### 不多说了，其实这道题就是一个理解贪心正确性然后AC的题，不过这里有几点**小建议**要给大家：
### 1. 有时候在读入一个数据后立即进行处理能够让你的~~main函数变长~~程序更省空间，比如这道题，就不必开存储物品的大数组了，当然，这种水题也不必省空间吧……记住这点，只要是可以边读边操作的，都这样做！所以我的码风经常是这样的?
```
for(int i=1;i<=something1;i++)
{
	something2=read();
    solve();
}
```
### 2.贪心题的正确性判断，比如本题，一个新读入的数你要么放进原有的容器，要么放不进去就~~算了~~再来一个，正确性是显然的。当然，贪心的正确性在较大型的题目中是需要加以反复考虑的!
```
if(bucket+num[i]>lim)
//桶放不下了(在桶排序之后忘不了bucket了QwQ)
{
	cnt++;
    //多加一个桶，为什么只开一个桶？?
    bucket=0;
}
bucket+=num[i];
```
### 3.有时候你的处理就得比较巧妙了:
#### Q:为什么只开一个桶？
#### A:本题并不要求记录咋装的，不问过程就可以~~过河拆桥~~反复利用一个桶
## 又是那个思路，反复用一个不计路径的int数，用完再覆盖着用，都是为了省下空间
好吧，我也不期望你们能够有耐心看我在上面扯，放代码：
```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100010;
int n,lim;
int num[maxn];
ll bucket=0,cnt=1;
int main()
{
　　cin>>n>>lim;
　　//并不需要快读:个数，容量上限
　　for(int i=1; i<=n; i++)
　　{
　　　　cin>>num[i];
 　　  //并不需要快读:大小
　　　　if(bucket+num[i]>lim)
　　　　{
		　　bucket=0;
		　　cnt++;
          　//放不下加个桶重装
　　　　}
　　　　bucket+=num[i];
    　　//比较巧妙的放在外面，两个情况一次满足
　　}
　　cout<<cnt;
  　//一次完美的AC
}
```
### 听我一句劝:别抄我的题解，有毒！(亲测CE)
# 撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：_mzh (赞：5)

# 初学贪心来试试题
这个题根本不需要存储，一边输入一边做就很快。
这个题定义一个sum来存储区间，一个num存储区间内的和，按照贪心的想法，如果一个连续的区间的值如果大于最大值，那么就要开出一个新区间，区间内的和等于最近超出的数。如果没有大于，就把这个输入的数加到区间和中。
弱弱的附上我31ms的码
```
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    int sum=0;
    int p;
    int num=0;
    for(int i = 0;i<n;i++){
        scanf("%d",&p);
        int c=p+num;
        if(c>m){sum++;num=p;}
        else num=c;
    }
    printf("%d",sum+1);
    return 0;
}

---

## 作者：SbasdianJulian (赞：5)

这道题目无论从那个方面来看，都是一道极其之水的题目
###### （~~数据强度更是水出天际~~）
### 先上代码
```
#include<iostream>
using namespace std;
#define N 100010

int n,m,a[N],sum,f;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int j=1;j<=n;j++)
    {
        sum+=a[j];
        if(sum>m)
        {
            j--;f++;sum=0;
        }
    } 
    cout<<f+1;
    return 0;
}
```
我自己都觉得这个代码他不可能AC
只是去试一下数据（然后我就过了。。就过了！）
# 说一下思路

### 1. 读入（不解释）
### 2.  计算区间和
### 3. 如果n次累加之后发现区间和大于m了，那么前面n-1个数就列为一段
### 4. So退回去一位，sum（区间和清空）算下一段

举个例子

输入 #1 

#### 5 6

#### 4 2 4 5 1

区间和最大值为6

第一次循环：sum=4 

第二次循环：sum=6

第三次循环：sum=10
### BOOM！
sum>m了

所以倒回去，记录第一个段（4,2）清空sum

接下来都是如此

最后输出，不要忘了结果加一（植树问题不解释）

后来细细再看了一下代码，虽然AC了但是问题还是很多

至于这些问题，就交给各位大佬去debug啦

~~**（逃）**~~

---

## 作者：Volta (赞：5)

萌新感觉其实还不太简单啊。。。代码不难写但感觉想起来其实还是有点难的。。// dalao们别喷我5555  
直觉得到的思路就是从左到右累加，加到超过m就再分一组，萌新想了很久这个事情的正确性……  
我试着用反证法证明了一下这个的确是最优解……  
证明：  
设k[i]来记录第i个分组的位置，其中k[1]=1，这个数列的第j项为a[j]，通过上面的方法，得到a[k[1]], a[k[1]+1], ...a[k[2]-1]位于第一组，a[k[2]], a[k[2]+1], ...a[k[3]-1]位于第二组，a[k[3]], a[k[3]+1], ...a[k[4]-1]位于第三组，以此类推，最后一个元素可表示为a[k[p]+t]。(即一共被分成了p组)    
则任取i<p，有：   
a[k[i]+1]+a[k[i]+2]+...+a[k[i+1]-1] <= m ①,  
a[k[i]+1]+a[k[i]+2]+...+a[k[i+1]-1]+a[k[i+1]] > m ②。  
假设存在更优的解，即这个解的分组数量比p少，这个解的产生过程一定可以视为合并了至少两个相邻的分组之后移动分组的边界。不妨设只合并了两个分组a[k[i]]~a[k[i+1]+t]。由于②，这个合并的区间一定不能满足题目条件，所以需要移动左侧或右侧分组的边界。  
假设移动右侧的边界，由于②，右侧边界要一直移动到合并前的两个分组的边界处才能符合要求，而这时右侧的分组相当于吞并了一整个分组，由于②，这样操作不能满足要求。  
假设移动左侧的边界，因为②，左侧的边界即使移动1个元素也会超出范围。
所以不存在更优的解，对于这个问题的最优解就是直觉hhh  
可以结合这个图理解一下……  
![示意图233](https://cdn.luogu.com.cn/upload/pic/50916.png)

代码的话就比较简单了，实现思路就可以了……
```c
#include <cstdio>

using namespace std;

// s:sum，题里的m
int n, s;
// 缓存的当前组的数字和
int ts;
// 分组数目
int ans;

int main() {
	scanf("%d%d", &n, &s);
	int t;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &t);
		ts += t;
        // 是否超过s
		if (ts > s) {
        	// 超了，新的数字只能放在新的组里
			ts = t;
			++ans；
		}
	}
	
    // 最后一组不会被计数，所以要+1
	printf("%d", ans + 1);

	return 0;
}
```

---

## 作者：Jimmy000 (赞：3)

由于必须从第一个切起 所以我们就从第一个开始算
### 思路如下
1. 定义n，a输入 z记录前面共有多少个a累加
1. z累加a
1. 当z>m时 ans++需要的数量加一
1. 当z>m时 z赋值a 相当于z赋值0再加a
1. 输出ans+1   因为在开始有一个没加故为ans+1
```
#include<bits/stdc++.h> 
using namespace std;
int ans,k=1,a,z;
int main()
{	int n,m;
	cin>>n>>m; 
	while(n--)//当n=0时跳出循环故输入n次
	{cin>>a;z//累加
	 z=z+a;
	 if(z>m) {ans++;z=a;}//因为最后输出ans+1 所以条件是z>m非 z>=m
	}
	cout<<ans+1;
	return 0;
}

```
大家AK这道题了吗？？？

---

## 作者：帅到惊动CIA (赞：3)

这题还真是货真价实的入门难度。

我的解法是：“抓”着一个元素，看它与“正在构造中”的段之和是否超出m

@楼下那位，在(lao)下(zi)才是最短c++代码

```cpp
#include<bits/stdc++.h>//头文件不解释
using namespace std;
    int main(){
        int n,m,s=0,ans=0,x;
        cin >>n>>m;
        for(int i=1;i<=n;i++){
                cin >>x;//读入一个元素
                if(s+x<=m)s+=x;//判断它与“正在构造中”的段之和是否超出m，没有就加上去
                else{ans++;s=x;}//超出了就段数加一，重置“正在构造中”的段
        }
        cout <<ans+1;//值得注意的是，由于以上程序是每超出一次段数加一，所以最后一段没算上，故最后加一
        return 0;
}
```

---

## 作者：Operina (赞：2)

 _**蓝**_ 名在刷贪心题时碰到了一道   _**红**_   题,很激动地点进来O(∩_∩)O

作为一只蒟蒻竟然5分钟做出来了当然好开心于是就发了人生首条认真写的题解虽然用的都是英文标点很激动求过谢谢...

啊...正题!



------以上都是扯------


------正文分割线------

这道题是赤裸裸的贪心, 送分题啊同学们!
就一步步地向前走(i++), 看到前面要超了就站住, 画一道分割线(ans++), 继续走, 直到山穷水尽(i == n).

好了. 未压行但做了一点点(真?)小手脚的代码
```cpp
# include <cstdio>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    int a[n + 1];
    int m, ans = 1, num = 0;//由于刚开始是一整段, 画一条变2段, 所以ans初始值为1.
    scanf("%d", &m);
    for(int i = 0; i < n; i++)
    {
        scanf("%c", &a[i]);
        if(num + a[i] <= m)//注意是num!!!
        {
            num += a[i];//累计
        }
        else//要超, 站住划线
        {
            ans++;//划线
            num = a[i];//注意这次a[i]没走, 所以num下一次走之前(a[i + 1])的初值应该为a[i].
        }
    }
    printf("%d\n", &ans);
    return 0;//over~~
}
```
求过谢谢(☆▽☆)


---

## 作者：莫文炜 (赞：2)

这一题比较简单，最主要是比较。一大于M就加组数s1。

重要部分在注释讲，先看AC程序：

```cpp
#include<iostream>
#include<cstdio>//头文件
using namespace std;
int n,m,a[100005],s,s1;//数组记得多定义5个
int main()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
    cin>>a[i];//先输入
    s=a[n];//先把最后一个取出来
    for (int i=n-1;i>=1;i--)
    if (s+a[i]<=m) s+=a[i];//如果小于等于M（题目有讲），就把它加进去
    else//如果不能
    {
        s1++;//组数加1
        s=a[i];//（核心句）不要忘记把本个数取出来
    }
    s1++;//不要忘记再加一，因为最后一个数是没有算到的
    cout<<s1<<endl;
    return 0;
}
```

---

## 作者：szm20060312 (赞：1)

# 直接贪心+暴力
~~本人第一篇题解，多多关照~~

主要思路就是：
k是计算器，最后只要不是0就+1
~~（和小学的植树问题差不多）~~

怕超范围直接上long long

a数组是容器，一边装一边累加，加一次k就减一

上代码：

```cpp
#include<bits/stdc++.h>//万能头文件，复赛能用
using namespace std;
long long n,m,a[100001],k; 
int main(){
	cin>>n>>m;
	k=n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		if(a[i]+a[i-1]<=m){//累加到>m为止
			a[i]+=a[i-1];
			k--;
		}
	}
	if(k!=0){//小学植树问题原理
		k++;
	}
	cout<<k;
	return 0;
}


```
~~本人第一篇题解，多多关照~~

---

## 作者：2007qqc_LiverpoolFC (赞：1)

## 这道题十分简单
# 可是
### 我把本身十几行的代码写成了三十多行
# 是不是很惊奇
## 主要思路：
#### 1. 从头到尾扫一遍；
#### 2. s标记本分段的和，s每次加上扫到的数字。若s加上扫到的的数字大于要求的最大和，将s归零以后再加，同时计数器u++；
#### 3. 最后输出u+1（因为最后一组数据不能在循环中计数）
### 闲话少说，先看代码 ~~虽说这不算是先看~~
```cpp~~
#include <bits/stdc++.h>//万能头文件
using namespace std;
int n,m,a[100010],ans;//定义 变量与题目一样（虽然我这里大小写不同）
bool g(int k){ //关键 其实这个循环中的u就是所求 但为了搞事情 在主函数中打了一段二分
	int t=1,s=0,u=0;//t:记录扫描到第几位 s:本段的总和 u:到此为止的段数（若此处u=1,最后应return u<=k;
	while(t<=n)//也可以用for循环
	{
		if(s+a[t]>m)
		{
			s=0;
			u++;
		}
		s+=a[t];
		t++;
	}
	return u<k;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);//请原谅我输入输出不统一的问题
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(g(mid))
		{
			ans=mid;//记录满足条件的mid
			r=mid-1;
		}
		else l=mid+1;
	}//二分（没有必要）
	cout<<ans<<endl;
	return 0;
}
```
### 另外，蒟蒻第一次写题解，请各位dalao多多指教

---

## 作者：circlegg (赞：1)

样例：

3 2\4\5 1 贪心法（超了就隔开）

3\2 4\5 1 dp（找空间利用最大的）

若 [i]和[i+1]能够合并

则 [i+1]<=m-[i]

若[i]独立存在的解更优,则后面一定可以合并

所以[i+2]<=m-(m-[i])

即[i+2]<=[i]

(1)所以[i]独立存在[i+1]与[i+2]合并产生的解必不差于

[i]与[i+1]一起,[i+2]独立存在的解(>=)

同理
若 [i+2]和[i+1]能够合并

则 [i+1]<=m-[i+2]

若[i]独立存在的解更优,则后面一定可以合并

所以[i]<=m-(m-[i+2])

即[i]<=[i+2]

(2)所以[i+2]独立存在[i]与[i+1]合并产生的解必不差于

   [i+2]与[i+1]一起,[i]独立存在的解(>=)

因为在样例中，(1)是dp解,(2)是贪心解

所以任何一种方式进行划分解都相同

所以贪心成立

···
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,t,cur,ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&t);
        cur+=t;
        if(cur>m){
            ans++;
            cur=t;
        }
    }
    ans++;
    printf("%d",ans);
    return 0;
}
···
```

---

## 作者：wangjinbo (赞：0)

刚看到这道题，以为是动归......一看难度，放心了，然后意识到是贪心

分析：因为每一段不大于大于m，所以就一直加，超过m就分段
代码：
```cpp
#include<bits/stdc++.h>//万能头，比赛慎用
using nmaespace std;
int a[100001];
int main()
{
    int n,m,tot=0,ans=1;//因为开始就有一段，所以ans初始化为1
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        tot+=a[i];
        if(tot>m){
            ans++;tot=a[i];//分段，a[i]是下一段第一个
        }
    }
    cout<<ans
    while(1);//这个不解释自己理解
    return 0;
}
```



---

## 作者：兄主的仙人掌 (赞：0)

### 代码

# 年少不知账号贵，抄袭封号两行泪

```cpp
#include <iostream>
using namespace std;
int sum,ans,a[100002];
int main() {
    int n,m;
    cin >> n >> m;
    for (int i=1;i<=n;i++)
        cin >> a[i];
    for (int i=1;i<=n;i++) {
        ans+=a[i];
        if(ans>m) {
            sum++;
            ans=0;
            i--;
        } else if (ans==m) {
            sum++;
            ans=0;
        }
    }
    if (ans!=0)
        sum++;
    cout << sum;
    return 0;
}
```

### 分析

题目很简单，没学过OI的人应该也能想出来，说的放肆点，就连~~驴~~阿米娅也能做出来

![](https://cdn.luogu.com.cn/upload/pic/73150.png)

说的简单，但是不好好做绝对会WA，~~比如我~~

瞧瞧我第一次提交的代码，看上去还OK，一交上去全WA：

```cpp
#include <iostream>
using namespace std;
int sum,ans,a[100002];
int main() {
    int n,m;
    cin >> n >> m;
    for (int i=1;i<=n;i++)
        cin >> a[i];
    for (int i=1;i<=n;i++) {
        ans+=a[i];
        if(ans+a[i]>=m) {
            sum++;
            ans=0;
        }
    }
    cout << sum;
    return 0;
}
```

总结一些这里的注意事项：

#### `ans>m`和`ans==m`是两种情况！

当`ans>m`时，`a[i]`其实是不能算在前一个分段里的，所以i需要回退1

#### 当`ans!=0`时，`ans`存储的其实是最后一个分段

当`ans!=0`时，`ans`存储的其实是最后一个分段，所以`sum`还需要+1

~~没了~~

---

## 作者：Islauso (赞：0)

本题主要思路是模拟，贪心什么的不存在的

有两种做法，读数组，读完再做，或是边读边做，因为前面的数据对后面没有影响

但有些地方还是要注意一下，不然要被坑（~~第一次全是Wonderful Answer~~）

上代码
```cpp
#include<cstdio>
using namespace std;
int n,m,p,ans,a;//p用来存当前这一组总数，ans存数量 
int main()
{
	scanf("%d%d",&n,&m);//个人比较喜欢scanf，这样不容易超时 
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		p+=a;//累加当前数据 
		if(p>m)//如果大于限额，说明在上一个数据时就已经不能装了，因此将这一次的数据存到新一组里。 
		{
			p=a;//存入这一组 
			ans++;//组数加一 
		}
		if(p==m)//如果等于限额，说明装完这一个就不能装了，因此组内总数清零， 组数加一。 
		{
			p=0;
			ans++;
		}
	}
	if(p) ans++;//因为超出时组数加的总是前一组，而不是这一组， 所以如果最后超出，还要加一 。 
	printf("%d",ans);
	return 0;//（完美结束） 
}
```
蒟蒻第二篇题解，如果有什么地方不对，希望dalao们在评论中指出，感谢感谢。

---

## 作者：zhaowangji (赞：0)

可以边读边做，可以全读完在做（写法都是一样的），但既然边读边做省时间，那就边读边做了

用sum记录当前的和，ans记录分的段数


外面套一个循环读入新数

sum先加上去，看看与规定的每段的和比较怎么样

1.大于规定的和

说明新数和之前的数要分段了，sum记为新数（因为要继续操作啊），段数ans++

2.等于规定的和

说明新数与之后的数要分段了，sum记为0（重新记段了），段数ans++

3.小于规定的和

继续做呗，这里可以不用写continue

```cpp
#include<iostream>
using namespace std;
int n,m,a[100007],ans,sum;//一开始没看见数据范围RE了
//sum是计算当前每一段的和，ans是分的段数
int main()
{
    cin>>n>>m;//直接读入，边读边做
    for(int i=1;i<=n;i++)//也可以是while循环
    {
        cin>>a[i];//每次读入一个新的数
        sum+=a[i];//加上试试
        if(sum>m)sum=a[i],ans++;//比限制的数大了，要分一段，记住此时总和是新的一段，所以sum等于这个数
        else if(sum==m)sum=0,ans++; 
        //如果刚刚好，要分一段，此时总和就是0了
    }
    if(sum)ans++;//如果还有剩余的，记住要再分一段
    cout<<ans;//输出
    return 0;//记得要写
}
```
~~竟然嫌我说明少~~

---

## 作者：木守球 (赞：0)

## 为什么贪心是对的？
这道问题是典型的贪心问题。大部分人看到贪心就直接按贪心做了，却没有想过为什么贪心是对的，这也是公开算法标签的坏处。对于很多新手来说，不明白为什么贪心。其他题解都没有很好的阐述贪心，所以本题解的重点在于**证明贪心的正确性。**
### 证明思路来源于算法导论
贪心和动态规划有异曲同工之妙，关键都在于问题划分为子问题，那么本题的子问题是什么呢？

我们从头开始先分出一段的数字，并设这第一段数字的长度为A，那么子问题就是：A+1到N的剩余序列的划分。

那么A怎么选呢？对于贪心来说A肯定要选到最大，也就说是这个A的最大取值就是贪心的选法，那么运用剪枝法决策树里减掉贪心的选择，剩下的选择就是1到A-1，子问题变成了X（2到A-1）到N的序列划分。

显而易见非贪心的子问题的序列长度要大于贪心的选择，对于这两个序列如果用同一种分法，贪心的短序列的结果不可能会劣于长序列，之后把这个子问题再做选择，又分出贪心和非贪心两种情况。

讲到这里相信大家都已经明白了吧！贪心选择不可能会劣于其他选择。
代码部分：：
```cpp
#include<iostream>
using namespace std;
int main()
{
	int N, M, temp=0,cnt=0,data;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		cin >> data;
		temp += data;
		if (temp > M)
		{
		    cnt++;
			temp = data;   //开始新的一段
		}
	}
	cout << cnt+1; //最后temp肯定小于M，加入最后一段
	return 0;
}
```



---

## 作者：wzl2003 (赞：0)

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int main()
{
    int a=0,n,m,d,s=0,ans=1;//从第一组的ans开始，如果ans不记为0，则第一组数计数器无记录。
    cin>>n>>m;
    for(int i=0;i<n;i++)
    { cin>>d;
      if(d+a<=m){  a+=d;}//将a的值加d
      else {
      a=d;//从d开始，如果为0，则此次循环的d不能进入统计
      ans++;}
    }
    cout<<ans;
return 0;}
```

---

## 作者：voilin (赞：0)

```cpp
//贪心问题
// 由于是分成连续的段，所以不考虑当前这一段可不可以恰好被后面的数填上
//直接分 
// 如果当前这一段没有填满，就继续加数，填满则分段
#include <bits/stdc++.h> 
using namespace std;
int n,a[100001],s;
long long m,sum;
int main(){
    cin>>n>>m; 
    for(int i=0;i<n;i++)
    cin>>a[i];
    //输入数据 
    for(int i=0;i<n;i++)
    {
        if(sum+a[i]>m)//如果这一段累加起来大于m 
        {s++;//分段 
        sum=0;//清零重新开始计算，这一点注意 
        i--;//返回上一步，因为这一步超过m了 
        }
        else {sum+=a[i];}//累加 
    }
    cout<<s+1;//因为如果分了s次段，会产生s+1段数据，所以加1 
    return 0;
}
```

---

## 作者：Dark_Kotori (赞：0)

很简单的小贪心，其实都不用开数组的

循环一次所有数据，直到加到再加一个数就会爆M

```cpp
#include<iostream>
using namespace std;
int data[100010];
int main(){
    int n,m,s=0,solve=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)    cin>>data[i];
    for(int i=1;i<=n;i++){
        s+=data[i];
        if(s>m){
            solve++;
            s=0;
            i--;
        }
    }
    if(s!=0)    solve++;
    cout<<solve;
}
```

---

## 作者：charles_typ (赞：0)

这道题其实思考的难度挺大的，不能做题光想着通过就行了。我相信不会做的人都能猜出来答案是这样的。

那么为什么答案会是这样的呢？

首先主观感觉上是这样的，如果前面的没有填满（就是某个分段没有充分的利用），那么就会造成资源浪费。

其实证明也就一句话的事，应该使得每一段尽量的长，所以其实与顺序无太大关系，不信你可以造几个极端数据试试（然而其实并不能造出来）。

```cpp
#include <iostream>
using namespace std;
int sum,n;
int main()
{
    int num=1;
    int count=0;
    cin>>n>>sum;
    for(int i=0;i<n;i++)
    {
        int temp;
        cin>>temp;
        if(count+temp<=sum)
            count+=temp;
        else
        {
            num++;
            count=temp;
        }
    }
    cout<<num<<endl;
    return 0;
}
```

---

## 作者：guobaipeng0 (赞：0)

题外话：这个pascal+C++题解应该是很简洁的。

分析：此题为纯模拟，只需循环一遍，

判断加上第i个数会不会超过m，



if (s+a[i]<=m)

不会就累加



s+=a[i];

否则，段数sum累加，把段数和s赋值为第i个数。


C++代码：


```cpp
#include<iostream>
using namespace std;
int n,m,i,a[100005],s,sum;
int main()
{
    cin>>n>>m;
    for (i=1; i<=n; i++) cin>>a[i];
    for (i=n; i>=1; i--)
    {
        if (s+a[i]<=m)s+=a[i];
        else
        {
            sum++;
            s=a[i];
        }
    }
    sum++;
    cout<<sum;
    return 0;
}
```
Pascal代码：
```cpp
var n,m,i,s,sum:longint;
 array a[1..100005] of longint;
begin
    readln(n,m);
    for i:=1 to n do readln(a[i]);
    for i:=n downto 1 do
    begin
        if s+a[i]<=m s:=s+a[i] else
        begin
            sum:=sum+1;
            s:=a[i];
        end;
    end;
    writeln(sum+1);
end.
```

---

## 作者：antiquality (赞：0)

##看到有些题解要开数组

##其实一边读一边看要省空间点，因为题目要求的是

#连续

好了，不多废话，代码见下

```pas
 var
  n,m:longint;
  i,j,k,max,ans,next:longint;
 begin
  readln(n,m);
  ans:=1; max:=0; next:=0;
  for i:=1 to n do
   begin
    read(k);
    inc(max,k+next);
    next:=0;
    if max>m then begin max:=0; next:=k; inc(ans); end
     else if max=m then begin max:=0; inc(ans); end;
   end;
  writeln(ans);
 end.
```
几个要注意的点：

1.ans要注1，不多讲了

2.分下一组的话要记得分下去

3.审题！审题！审题！（重要的事情说三遍

第一次没看见“连续”

第二次没分组

第三次没注0

###就损了三次提交[黑线


---

## 作者：新建文本文档 (赞：0)

```cpp
#include<cstdio>
int n,m,x=0,y,tot=1,a[100000];
int main(void){
  scanf("%d%d",&n,&m);
  for(int i=0;i<n;i+=1){
      scanf("%d",&y); x+=y; //现在组的总和
      if(x>m) x=y,tot+=1;//如果超过m，则组+1，最后一个分到下一组
  }
  printf("%d",tot);
}
```

---

## 作者：hfctf0210 (赞：0)

这题简直是弱智题！

连数组都不用开，直接边读边加，能分多大就多大。

核心代码：

```cpp
for(int i=1;i<=n;i++)
{
cin>>x;
s+=x;
if(s>m)
{
ans++;
s=x;
}
}
cout<<ans+1<<endl;//一定要+1，还有最后一段
```

---

## 作者：野菜汤 (赞：0)

题解：

其实这题很容易啦，只要一个循环过去，然后将数字相加，如果超过界限就分组，然后只要数组开的够大，基本通过就不是问题啦！以下是个人的源程序代码，仅供参考。

```delphi
var i,m,n,ans,sum:longint;
    a:array[1..100000] of longint;
begin
  read(m,n);
  sum:=1;{因为从第一个开始就算是一组了，但是一次划分之后就算有了两组，所以初始化值为1}
  for i:=1 to m do read(a[i]);
  for i:=1 to m do begin
    ans:=ans+a[i];
    if ans>n then begin inc(sum);ans:=a[i];end;//如果ans超过标准，那么总数sum加1，ans就直接等于那个数（也就是分组了）
  end;
  write(sum);
end.
```
这是一道比较经典的贪心练手题，很简单，却包含了贪心的精华，贪心并不是一种固定模式的算法，而是需要技巧的求其最优解，所以对个人的思考有着较深的要求。


---

## 作者：TURX (赞：0)

>一些东西已经在代码里面说明，这道题入门暴力还是可以的
```cpp
#include<iostream>
using namespace std;
int n,now,temp=0; // n≤100000，now与temp都为临时变量
unsigned long long m; // m≤10^9
int ans=1; // 就是全是0也至少有一段
int main() {
    ios::sync_with_stdio(false); // 提高iostream效率
    cin>>n>>m; // 输入
    for(int t=0;t<n;t++) {
        cin>>now; // 输入当前数
        if((temp+=now)>m) { // 如果比m大，就要分段
            temp=0; // temp清零（重算新的一段）
            ans++; // 段数++
            temp+=now; // 从0开始算temp的值
        }
    }
    cout<<ans<<endl; // 输出段数
}
```

---

## 作者：LiuLinlong (赞：0)

#贪心算法·入门难度

首先需要建数组，存储整个数列，然后用sum记录这前几项的和，如果超过了m，就代表这一段结束了，这一项属于下一段；

代码如下：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int a[100005];
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int sum=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        sum+=a[i];
        if(sum>m){
            ans++;
            sum=0;
            i--;//加上a[i]时超出m，所以a[i]是下一段的
        }
        if(i==n) ans++;//代表到最后了，因为定义ans初值为0，而即使不分ans也至少为1
    }
    printf("%d",ans);
    return 0;
}
```

---

