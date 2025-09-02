# YOKOF - Power Calculus

## 题目描述

（略过没有营养的题干）

**题目大意**：
  给出正整数n,若只能使用乘法或除法，输出使x经过运算（自己乘或除自己，以及乘或除运算过程中产生的中间结果）变成x^n的最少步数

## 样例 #1

### 输入

```
1
31
70
91
473
512
811
953
0```

### 输出

```
0
6
8
9
11
9
13
12```

# 题解

## 作者：Doveqise (赞：11)

一道搜索题，搜索需要几步能到达目标预计状态。  
记得搜索×的状态和÷的状态。  
DFS例题赛高！  
emmm细节看代码  
```
#include<bits/stdc++.h>
using namespace std;
int maxn/*步数最大值*/,n/*输入数字*/,S[50]/*存储数组*/;
bool find(int step,int now){//DFS函数
    if(step>maxn||now<=0||now<<(maxn-step)<n) return 0;//判断非法状态
    if(now==n||now<<(maxn-step)==n) return 1;//记录答案
    S[step]=now;//存入数组
    for(int i=0;i<=step;i++){
        if(find(step+1,now+S[i]))return 1;//DFS乘S[i]的情况
        if(find(step+1,now-S[i]))return 1;//DFS除以S[i]的情况
        }
    return 0;
}
signed main(){
    while(scanf("%d",&n)&&n){//读入多组数据
    for(maxn=0;!find(0,1);maxn++);//查找最小需求步数
    printf("%d\n",maxn);//输出答案
    }
}
```

---

## 作者：3200Pheathon (赞：8)

_[description】给定n，问最少使用多少次乘法和除法，就可以通过x得到x^n，可以使用中间结果。
 _
 

------------
**显然**爆搜会t（2^15谁受的住啊）。

于是用IDDFS加上剪枝（若最大次幂在规定次数自乘都无法到达n，则return false）
 
引一段lh学长关于IDDFS的介绍（大佬就不用看了）

```
从小到大枚举答案所需步数，
然后在搜索时一旦超出这个步数就不再搜索。

根据搜索空间的一般规律，搜索的状态空间随着步数指数级增长。

这样我们的时间主要取决于最后一次搜索的时间，
DFS的缺点得到了一定程度的弥补。

```

然后就可以~~愉快地~~水题了

```
#include<bits/stdc++.h>

int n,dep,num[15];//根据样例可以看出15步足够了
using namespace std;
bool dfs(int cnt,int x)
{
    if(num[cnt]==n) return true;
    if(cnt>=dep) return false;//IDDFS
    x=max(x,num[cnt]);
    if(x*(1<<(dep-cnt))<n)
    return false;//可行性剪枝
    for(int i=0;i<=cnt;i++)
    {
        num[cnt+1]=num[cnt]+num[i];
        if(dfs(cnt+1,x)) return true;
        if(num[cnt]>num[i])      num[cnt+1]=num[cnt]-num[i];
        else num[cnt+1]=num[i]-num[cnt];
        if(dfs(cnt+1,x)) return true;
    }

    return false;
}

int main()
{
	std::ios::sync_with_stdio(false);
    while(cin>>n&&n)
    {
        if(n==1) cout<<"0"<<endl;
        else
        {
            num[0]=1;
            for(dep=1;;dep++)
            if(dfs(0,1)) break;
            cout<<dep<<endl;
        }
    }
    return 0;
}


```

---

## 作者：设计涉及社稷 (赞：3)

```
#include<bits/stdc++.h>
using namespace std;

int n,maxh;
int a[1010];

bool dfs(int x,int cur)
{
    if(x<<(maxh-cur)<n) 
		return false; //乐观估计剪枝，当前深度到限制深度指数最多增长2^(maxh-cur)倍 
    
	if(cur>maxh) 
		return false; //达到限制深度 
    
	a[cur]=x;
    
	if(x==n) 
		return true;
    
	for(int i=0;i<=cur;i++)
	{
        if(dfs(x+a[i],cur+1)) 
			return true;
        if(dfs(x>a[i]?x-a[i]:a[i]-x,cur+1)) 
			return true;
    }
    return false;
}

int main()
{
    while(scanf("%d",&n)&&n)
	{
		maxh=0;
		memset(a,0,sizeof(a));
		while(!dfs(1,0))//只要没找到答案就一直继续 
		{
			memset(a,0,sizeof(a));
			maxh++;
		}
		printf("%d\n",maxh);
	}
    return 0;
}
```

---

## 作者：huyangmu (赞：3)

这道题答案不会太大，所以考虑迭代加深。

我们从 $0$ 开始枚举每一个深度，每个深度都用搜索判断能否变成 $n$，如果可以就直接输出枚举到的深度，并退出循环。

但直接搜索明显会超时，所以可以用两个剪枝优化，如果当前的值小于 $0$ 了，就肯定到不了 $n$，直接退出搜索，如果后面全是加法操作也比 $n$ 小，也直接退出搜索。

### AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e3 + 5;
int n, ans, dep[N], i;
bool dfs (int x, int sum){
	if(x == i) return sum == n;
	dep[x] = sum;
	if (sum < 0) return 0;
	if ((sum << (i - x)) < n) return 0;
	if ((sum << (i - x)) == n) return 1;
	for (int i = 0; i <= x; ++i){
		if(dfs(x + 1, (sum + dep[i])) || dfs(x + 1, (sum - dep[i]))) return 1;
	} 
	return 0;
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	while (1){
		cin >> n;
		if (n == 0) return 0;
		for (i = 0; ; ++i){			
			if (dfs(0, 1) == 1){
				ans = i;
				break;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}


---

## 作者：紊莫 (赞：1)

清纯的小搜索加轻微剪枝。  

## Part 1 思路  

每一步，对于每一个中间结果（包括自己），可以乘和除，自然联想到使用搜索。

具体的，我们只关心指数是多少，可以以此为搜索的状态，然后对于每一个中间结果，可以用一个数组记录。此时问题在我们并不知道要搜索几次。如果直接搜索很有可能找不到答案，这里引进一个名为“迭代加深”的操作，可以简单看作广搜版的深搜，即每次限定搜索深度。  
对于一些浅层的节点，会在搜索中被多次搜索到，但是这种浪费和搜索树每一层指数级别的增长来说，可以忽略不计。  

对此，不难写出如下暴力：  
```cpp
int dfs(int p,int sum){
	if(p>m) return sum==n;
	s[p]=sum;
	for(int i=1;i<=p;i++)
		if(dfs(p+1,sum-s[i])||dfs(p+1,sum+s[i])) return 1;
	return 0;
}
```

可是这一种写法仍然会超时。  

引进一个剪枝，当从这一步开始，`sum` 每一步都加上最大的值，也就是每次乘 $2$，这是当前能达到的最大值，如果这都不能到目标，可以直接返回。  

```cpp
if(sum<<(m-p+1)<n) return 0;
```
至此即可优雅通过。

## Part 2 参考代码  

仅供参考。  

```cpp
//Author: Velvet on Luogu(uid=443675)
#include <bits/stdc++.h>
using namespace std;
int n,m,s[100];
int dfs(int p,int sum){
	if(p>m) return sum==n;
	if(sum<<(m-p+1)<n) return 0;
	s[p]=sum;
	for(int i=1;i<=p;i++)
		if(dfs(p+1,sum-s[i])||dfs(p+1,sum+s[i])) return 1;
	return 0;
}
int main(){
	while(cin>>n&&n){
		for(m=0;!dfs(1,1);m++);
		cout<<m<<endl;
	}
}
```



---

## 作者：D2T1 (赞：1)

# 题解 [SP7579] YOKOF - Power Calculus

[Luogu Link](https://www.luogu.com.cn/problem/SP7579)

题目显然可以转化为：

>  给出正整数 $n$,若只能使用加法或减法，输出使 $1$ 经过运算（自己加或减自己，以及加或减运算过程中产生的中间结果）变成 $n$ 的最少步数。

使用 IDDFS 求解。

IDDFS，即迭代加深的 DFS，就是在 DFS 过程中添加一个“最大深度值”，每次 DFS 时如果递归深度大于这个值就强制结束递归。如果没搜到目标，就令最大深度值 $+1$，继续搜一遍。这样虽然会重复搜搜索树上浅层节点，但是浅层节点数相对于深层节点数可以忽略不计（搜索树上，大部分情况 $1\sim n$ 层的节点数远小于 $n+1$ 层节点）。

那 IDDFS 有什么好处呢？它既可以防止 DFS 陷入错误的搜索分支耗费时间，又不像 BFS 一样占用大空间。如果搜索树分支很多，且目标在浅层节点上，可以考虑 IDDFS。

IDDFS 的过程可以大致分为四部分：

1. 枚举“最大深度值”，从 $1$ 开始，每次进行 DFS，成功搜到就退出，失败就 $+1$ 继续搜。
2. DFS 中，如果递归层数大于最大深度值，判断答案是否正确。
3. 进行可行性剪枝（如果当前的答案怎么都达不到目标，直接剪枝）。
4. 枚举分支，继续递归。

本题的可行性剪枝为：记录当前搜到的所有数的最大值，设为 $mx$，当前层数设为 $i$，最大深度为 $md$，则如果递归到 $md$ 层，那么最大只可能搜到 $mx\times 2^{md-i}$，这个值如果小于目标直接剪枝。

```cpp
//SP7579
#include <bits/stdc++.h>
using namespace std;

int n, a[20], md;

bool dfs(int dep, int mx){
	if(a[dep] == n) return true;
	if(dep >= md) return false;
	if(mx*(1<<(md-dep))<n) return false;
	for(int i = 0; i <= dep; ++ i){
		a[dep+1] = a[dep] + a[i];
		if(dfs(dep+1, max(mx, a[dep+1]))) return true;
		a[dep+1] = abs(a[dep]-a[i]);
		if(dfs(dep+1, max(mx, a[dep+1]))) return true;
	}
	return false;
}

int main(){
	while(true){
		scanf("%d", &n);
		if(n == 0) return 0;
		if(n == 1){ puts("0"); continue; }
		a[0] = 1;
		for(md = 1; ; ++ md)
			if(dfs(0, 1)){ printf("%d\n", md); break; }
	}
}
```

---

## 作者：Randolph、 (赞：1)

## [SP7579 YOKOF - Power Calculus](https://www.luogu.org/problem/SP7579)

## 迭代加深搜索

- DFS每次选定一个分支，不断深入，直至到达递归边界才回溯。这种策略带有一定的缺陷。试想以下情况：**搜索树每个节点的分支数目非常多，并且问题的答案在某个较浅的节点上。如果深搜在一开始选错了分支，就很可能在不包含答案的深层子树上浪费许多时间**

- 此时，我们可以**从小到大限制搜索的深度**，如果在当前深度限制下搜不到答案，就把深度限制增加，重新进行一次搜索，这就是迭代加深思想。

- 虽然该过程在深度限制为d时，会重复搜索第1~d-1层的节点，但是当搜索树节点分支数目较多时，随着层数的深入，每层节点数会呈指数级增长（这样时间主要取决于最后一次搜索的时间），这点重复搜素与深层子树的规模相比，实在是小巫见大巫了。

- 总而言之，**当搜索树规模随着层次的深入增长很快，并且我们能够确保答案在一个较浅层的节点时**，就可以采用迭代加深的深度优先搜索算法来解决问题。

## 分析

显然有解，连续乘n次x总是能得到x^n的，只是可能不是最优解。

操作次数最小时有搜索深度最小，而理论上搜索深度可以是无穷的，这种情况下就可以使用迭代加深了。

（以上by Chelly）

```cpp
#include<cstdio>
using namespace std;
int n,ans,a[15];
inline bool dfs(int step,int x) {//x为当前构造的指数
	if (step>ans || x<=0 || x<<(ans-step)<n) return 0;
    //当step超过限定步数，指数为非正数，或者x自乘（ans-step）次仍小于n（可行性剪枝），则直接返回
	if (x==n || x<<(ans-step)==n) return 1;
	a[step]=x;
	for (register int i=0; i<=step; i++)
		if (dfs(step+1,x+a[i]) || dfs(step+1,x-a[i]))//乘或除以一个构造过的数
			return 1;
	return 0;
}
int main() {
	while(scanf("%d",&n) && n) {
        //用x乘除构造x^n，相当于从1加减构造出指数n
		for (ans=0; !dfs(0,1); ans++);//迭代加深搜索
		printf("%d\n",ans);
	}
}
```

（以下by ZAGER）

## 迭代加深搜索使用范围:

1.在有一定的限制条件时使用（例如本题中“如果能在1515步以内（包括1515步）到达目标状态，则输出步数，否则输出-1−1。“）。

2.题目中说输出所以解中的任何一组解。

为什么能够降低时间复杂度：

我们可能会在一个没有解（或解很深的地方无限递归然而题目中要求输出任何的一组解），所以我们限制一个深度，让它去遍历更多的分支，去更广泛地求解，(其实和BFSBFS有异曲同工之妙)。

---

## 作者：Hisaishi_Kanade (赞：0)

迭代加深的基本思想就是说，由于搜索树的深度特别大，直接深搜可能会陷入一个很深的地方“无法自拔”，那么结合一下 bfs 的思想，每次枚举我这次**搜到多深**，这样搜索树的大小是得以控制的。

搜索树每层的节点数指数级增长，所以运行的效率基本上就取决于最后一层多少个节点。那么我们考虑这一题的搜索树深度。

~~小学奥数可知~~ $a^x\times a^y=a^{x+y}$，然后有 $a^x\div a^y=a^{x-y}(a\not =0)$。

显然的一种可能的构造方案就是我一路跳到 $2^{\lceil\log n\rceil}$，然后依次减掉多余的二进制位数。一路跳的步数显然是 $\log n$ 级别，一共就 $\log n$ 级别个位，所以依次减掉的个数也是 $\log n$ 级别。

所以可以知道最后的结果是一定不会大于 $2\log n$，我这种构造很显然不是最优的，甚至劣不少。也就是最后的复杂度大致介于 $O(tn)$ 到 $O(tn^2)$ 小得多。

`assert` 一下知道 $t<150$，跑这个是稳稳地了。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
const int N=20;
int rem[N];
int n,m;
inline const bool check(int dep,int now)
{
	if(dep>m)return now==n;
	if((now<<m-dep+1)<n)return false;
	rem[dep]=now;
	int i;rep(i,1,dep)if(check(dep+1,now-rem[i])||check(dep+1,now+rem[i]))return true;
	return false;
}
int main()
{
	while(cin>>n && n)
	{
		rep(m,0,20)if(check(1,1))break;
		cout<<m<<endl;
	}
	return 0;
}
```

---

## 作者：朝夕晨曦_L (赞：0)

来一发简单做法

题目链接：[SP7579 YOKOF - Power Calculus](https://www.luogu.com.cn/problem/SP7579) 

题目大意：如何用最少的步数凑出一个次数。

思考一个问题：题干提到的相乘，实际上可以看做同底数幂相乘，底数不变，指数相加，我们只需要维护一个变量指数就可以了。

那么难点就来了，怎么有效的利用中间产物？开个数组 $num$ 储存，下标就可以是当前用的步数。

我们可以使用迭代加深搜索，每次规定一个步数，能到达目标，就返回一，输出该步数。考虑剪枝，如果从当前局面开始，每次都用最大的两个数相乘，也就是最大的两个指数相加，都不能达到目标的话，就直接返回不可以。

记得处理边界，搜到最后一步，或者一波操作也没能返回可以，就只好返回不可以了！

见代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int num[100001], n, dep;

bool dfs(int step,int now){
    if(now <= 0 || step > dep || now << (dep - step) < n) return 0;
    if(now << (dep - now) == n) return 1;
    if(now == n) return 1;
    num[step] = now;//储存当前步骤的指数
    for(int i = 0;i <= step; i++){
        if(dfs(step + 1,now + num[i])) return 1;
        if(dfs(step + 1,now - num[i])) return 1;

    }
    return 0;
}

int main(){
    while(1){
        cin >> n;
        if(n == 0) break;
        for(dep = 0; ; dep++){
            if(dfs(0,1)) break;
        }
        cout << dep << endl;
    }
    return 0;
}
```

---

## 作者：so_cool (赞：0)

先来确定算法。

这道题先来思考用什么算法？似乎没什么特殊的算法，那么就只能搜索了。

是深搜呢？还是广搜呢？广搜没前途，状态不好记录，深搜又控制不住，一条路走到黑。

其实这道题直接迭代加深搜索就可以了。

什么是迭代加深搜索？就是深搜设定上一个搜索的边界，逐步加深这个边界，这样每次会限制其搜索的深度，就不会一条路走到黑了。　　

但是这是依旧**相当的暴力**啊！！！

我试了一下，连样例数据都卡到爆了，所以必须进一步优化，这里使用剪枝优化。

如果当前的指数自乘剩下的次数之后仍然比 $n$ 小，那么我们就一定会果断舍弃，这就是剪枝的内容。

具体代码如下：
```
 #include<iostream>
 using namespace std;
 int num[],n,idt;//用num来存储已经创造过的可以用于计算的数，idt是限制的深度
 bool dfs(int step,int now)//step是当前用了多少次运算，now是当前指数
 {
     if(now<=||step>idt||now<<(idt-step)<n) return false;//判断一定不能成功的条件和剪枝
     if(now<<(idt-step)==n) return true;//剪枝
     if(now==n) return true;//如果正确，那么就返回
     num[step]=now;//存储一下这个指数
     for(int i=;i<=step;i++)
     {
         if(dfs(step+,now+num[i])) return true;//乘
         if(dfs(step+,now-num[i])) return true;//除
     }
     return false;//不成功一定要最后返回false
 }
 int main()
 {
     while()
     {
         cin>>n;
         if(n==) break;
         for(idt=;;idt++)//从0开始枚举深度
         if(dfs(,)==true) break;//发现可以就结束循环
         cout<<idt<<endl;
     }
     return ;
 }
```

---

## 作者：会打沙包的猫 (赞：0)

迭代加深搜索的关键就是枚举边界，
虽然可能造成重复，
但实际上寻找最优解的时候，
可以规避一些很深的支路，来优化dfs的效率
.一句话总结：获得了**bfs特性**的**dfs**

**下面直接贴代码（注释）**

~~~cpp
#pragma GCC optimize(2)
//手动开氧气，是我最后的倔强
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int stt[100],floor;
//stt是存步骤，floor存限制步数
int n;
int dfs(int step,int now)
{
	if(step>floor)return false;
    //关键语句
	if(!(now>0))return false;
    //可行性剪枝
	if((now<<(floor-step))<n)return false;
    //可行性剪枝
    if((now<<(floor-step))==n)return true;
    //估计答案
	if(now==n)return true;
    //找到答案
	stt[step]=now;
    //存储路径
	for(int i=0;i<=step;i++)
	{
		if(dfs(step+1,now+stt[i]))
		  return true;
          //深搜的下一步是乘法
		if(dfs(step+1,now-stt[i]))
		  return true;
          //深搜的下一步是除法
	}
	return 0;
}
int main()
{
	while(1)
	{
		floor=0;
		scanf("%d",&n);
		if(n==1)
		  {
		  	puts("0");
		    continue;
          //如果x^1，那么不需要操作
		  }
		if(n==0)
		  return 0;
          //结束
		for(floor=0;1;floor++)//关键语句：枚举边界
		  {
		  	if(dfs(0,1))
		  	{
		  		printf("%d\n",floor);
				break;
		  	}
		  }
	}
}
~~~

---

