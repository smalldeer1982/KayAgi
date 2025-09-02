# Missile Defence System

## 题目描述

为了对抗附近恶意国家的威胁，R 国更新了他们的导弹防御系统。

一套防御系统的导弹拦截高度要么一直严格单调上升要么一直严格单调下降。

例如，一套系统先后拦截了高度为 $3$ 和高度为 $4$ 的两发导弹，那么接下来该系统就只能拦截高度大于 $4$ 的导弹。

给定即将袭来的一系列导弹的高度，请你求出至少需要多少套防御系统，就可以将它们全部击落。

## 说明/提示

#### 样例解释
对于样例，需要两套系统。一套击落 $3,4$ 号导弹，另一套击落 $5,2,1$ 号导弹。

#### 数据规模与约定
$1 \leq n \leq 50$。

## 样例 #1

### 输入

```
5 
3 5 2 4 1 
0```

### 输出

```
2```

# 题解

## 作者：Atserckcn (赞：12)

## [P10490 Missile Defence System](https://www.luogu.com.cn/problem/P10490) 题解

### 题目简述：

给定共 $n$ 个导弹，每种拦截系统可以拦截上升或下降的导弹，求共需要几套系统。

### 思路简述：

因为导弹来临是按照顺序，而非高度，所以我们绝对不能用 `sort`（显而易见）。

那么我们不妨将每个导弹分个类：

1、可以用某个上升拦截系统拦截。

2、可以用某个下降拦截系统拦截。

3、需要新建一个上升拦截系统拦截。

4、需要新建一个下降拦截系统拦截。

考虑其中 1 跟 2，3 跟 4 是相互矛盾的，所以我们可以剪枝优化。

剪枝代码：

```cpp
int upsize=up.size();
int downsize=down.size();
if(upsize+downsize>=ans) return;//这种情况已经超过或赶上之前我的最优方案了，我还留你干嘛
if(now>n)//全部拦截后
{
	ans=min(ans,upsize+downsize);//上升下降的总套数
//	printf("over ans:%d\n",ans);
	return;
}
```

### AC  CODE：

思路上文讲述得已经很清楚了，还不懂的可看注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=55;
int n,ans;
int a[MAXN];
vector<int> up,down;//up存上升系统，down存下降系统
void dfs(int now)//现在正在拦截第now个导弹
{
	int upsize=up.size();//注意：千万不要把它俩定义成全局变量！！血泪教训，调了1小时
	int downsize=down.size();//注意：千万不要把它俩定义成全局变量！！血泪教训，调了1小时
	if(upsize+downsize>=ans) return;//上述剪枝
	if(now>n)
	{
		ans=min(ans,upsize+downsize);//上述剪枝
//		printf("over ans:%d\n",ans);
		return;
	}
	for(int i=0;i<upsize;i++)//开始枚举每个上升系统
	{
		if(up[i]<a[now])//可以拦截
		{
			int t=up[i];//t也不可以定义为全局变量！！
            //dfs回溯备份
			up[i]=a[now];
			dfs(now+1);//继续拦截下一个
			up[i]=t;
			break;
		}
	}
	if(upsize==0||up[upsize-1]>=a[now])//判断，是否需要新开一个上升系统
	{
		up.push_back(a[now]);
		dfs(now+1);
		up.pop_back();
	}
    //同上，ctrl C,ctrl V
    //说实话，我因为复制完漏了更改名字而调了半天，太蒻了
	for(int i=0;i<downsize;i++)
	{
		if(down[i]>a[now])
		{
			int t=down[i];
			down[i]=a[now];
			dfs(now+1);
			down[i]=t;
			break;
		}
	}
	if(downsize==0||down[downsize-1]<=a[now])
	{
		down.push_back(a[now]);
		dfs(now+1);
		down.pop_back();
	}
	return;
}
int main(){
	while (true)
	{
		scanf("%d",&n);
		if(n==0) break;//虽然题目没说，但由样例可知，n=0时结束
		up.clear();
		down.clear();
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		ans=0x7fffffff;//无穷大
		dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/162528718)

---

## 作者：Adorable_ (赞：4)

#### [题目传送门。](https://www.luogu.com.cn/problem/P10490)

#### [博客食用更佳。](https://www.luogu.com.cn/article/qzwbhool)

（有任何问题欢迎各位大佬指出交流 %%%。）

非常好的一道练习搜索的题。

### 分析题意 	
首先，这道题很明显是一道深搜加剪枝。

我们根据题意可知，对于一发导弹，我们有四种方案：
1. 新建一个递增拦截装置。
2. 新建一个递减拦截装置。
3. 使用已有的递增拦截装置。
4. 使用已有的递减拦截装置。

所以我们只需在 1 和 3 之间选一种，2 和 4 之间选一种  。

但如果直接爆搜，$n\le50$ 的范围很容易会 ~~boom~~ 挂掉。

所以我们需要优化，对于一个搜索，我们的优化方式大多有这几种：

1.优化搜索顺序（如提前排序/倒置等，如小木棍 P1120，预处理从大到小排序，省好多时间）

2.排除等效冗杂（如小木棍 P1120，同等长度木棍只需判断一次即可）。

3.可行性剪枝（如贪心优化）。

4.最优性剪枝（如若搜索答案已经劣于现已知最优答案，果断回溯）。

5.记忆化搜索（把答案记录下来，避免重复减少时间)。

---

### 1.考虑可行性剪枝
再考虑可行性剪枝，可以用**贪心**的思想，（楼下 [luobotianle 大佬](https://www.luogu.com.cn/user/1245780) 解释的非常好，简单易理解，这里就直接引用了。）
```
如果对于一个导弹，我们有两个递增装置都能够拦截它，那么基于贪心，我们一定会选择目前高度最高的一个去拦截它（因为低的那一个“更有潜力”）

如现在有两个递增装置，第一个依次拦截了高度为 2 5 8 的三枚导弹，第二个拦截了 6 7 的两枚导弹，那么如果又来了一发高度为 9 的导弹，那么用第一个拦截一定会比第二个更优。
```

**递减装置同理。**

### 2.考虑最优性剪枝

当目前答案已经大于已知最优答案时，直接回溯即可。

---
综上，AC_code 如下，要注意一些细节问题。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
int n,a[60],ans = 0x7fffffff;
vector<int> up,down; //分别记录递增序列的最大值和递减序列的最小值 

void dfs(int now)
{
	int x = up.size(),y = down.size();
	if(x+y>=ans) return; //最优性剪枝，解释参见上文 
	if(now>n) //搜索结束
	{
		ans = min(ans,x+y); 
		return;
	}
	for(int i = 0;i<x;i++)
	{
		if(up[i]<a[now]) 
		{
			int tmp = up[i]; 
			up[i] = a[now]; 
			dfs(now+1);
			up[i] = tmp; 
			break; //显然每次只会更新第一个值，第一个找到的值一定是可行的最大值  
		}
	}
	if(!x or (up[x-1]>=a[now])) //新建一个递增装置 
	{
		up.push_back(a[now]); 
		dfs(now+1); 
		up.pop_back();  
	}
	for(int i = 0;i<y;i++) //遍历每一个递减序列 
	{
		if(down[i]>a[now])
		{
			int tmp = down[i]; 
			down[i] = a[now];
			dfs(now+1);
			down[i] = tmp;
			break;
		}
	}
	if(!y or (down[y-1]<=a[now])) //新建一个递减装置 
	{
		down.push_back(a[now]);
		dfs(now+1);
		down.pop_back();
	}
} 

signed main()
{
	while(cin>>n && n) 
	{
		if(n==0) break; 
		ans = 0x7fffffff;
		for(int i = 1;i<=n;i++) cin>>a[i]; 
		up.clear(), down.clear(); //多测一定要记得初始化！！！ 
		dfs(1); 
		cout<<ans<<endl;
	}
	return 0;
}
```
第一次写题解，有问题的地方还请指出，多多包涵。

---

## 作者：BK小鹿 (赞：2)

## 思路分析

首先看到这个 $n = 55$ 的超小范围，一眼丁真，鉴定为爆搜。考虑一下如何搜索。

对于当前的这个导弹，我们有四种选择：

- 用某个已有下降系统拦截。

- 用已有的上升系统拦截。

- 新开一个上升系统。

- 新开一个下降系统。

然后就可以写出这样的一个朴素[代码](https://www.luogu.com.cn/paste/0dk29w34)。

很遗憾，他会全部超时，因为只有一个测试点。此时考虑优化。

下面介绍几个常用的优化方法：

- 优化搜索顺序：优先搜索分支较少的节点，可以想一下为什么。

- 可行性剪枝，都不可行了还搜什么。

- 最优性剪枝，如名字。

- 排除等效冗余。

接下来全部用上就行了。首先我们发现第一种与第二种，第三种与第四种都是互相矛盾的，可以剪枝，这是第一个剪枝。

然后，还可以使用最优性剪枝，如果当前使用的系统已经大于等于当前答案，同样没必要搜索了。

然后，我们就可以愉快的切掉此题了，送上你们最爱的代码。

## AC Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<20+5];
inline int read(){
unsigned int x=0;
char c=gc();
while(!isdigit(c)){
c=gc();
}while(isdigit(c)){
x=x*10+(c^48);
c=gc();
}return x;
}

const int N = 55;

int n;
int h[N], up[N], down[N], cnt1, cnt2;
int res;

void init()
{
    res = 0x3f3f3f3f;
    cnt1 = cnt2 = 0;
    memset(up, 0, sizeof(up));
    memset(down, 0, sizeof(down));
}

void dfs(int u)
{
    if (cnt1 + cnt2 >= res) return;
    if (u > n)
    {
        res = min(res, cnt1 + cnt2); 
        return;
    }

    // 尝试放入上升序列
    int i;
    for (i = 0; i < cnt1; i++)
    {
        if (up[i] < h[u])
        {
            int t = up[i];
            up[i] = h[u];
            dfs(u + 1);
            up[i] = t;
            break;
        }
    }
    if (i == cnt1) // 新开一个系统来处理
    {
        up[cnt1++] = h[u];
        dfs(u + 1);
        cnt1--;
    }

    // 尝试放入下降序列
    for (i = 0; i < cnt2; i++)
    {
        if (down[i] > h[u])
        {
            int t = down[i];
            down[i] = h[u];
            dfs(u + 1);
            down[i] = t;
            break;
        }
    }
    if (i == cnt2) // 新开一个系统来处理
    {
        down[cnt2++] = h[u];
        dfs(u + 1);
        cnt2--;
    }
}

int main()
{
    while (n = read(), n)
    {
        init();
        for (int i = 1; i <= n; i++) h[i] = read();
        dfs(1);
        printf("%d\n", res);
    }
    return 0;
}


```

---

## 作者：Montpelier (赞：2)

~~放眼望去，整个题解区都是 up 和 down 两种反导系统分开存的，其实没必要啊。~~



---

## 思路：爆搜+剪枝

### 首先是无脑爆搜：

不考虑任何剪枝，可以按照导弹来袭的时间顺序，逐个安排，对于每个导弹，分别尝试升序拦、降序拦、开新的升序、开新的降序四种方法。

[喜提 TLE](https://www.luogu.com.cn/record/170297281)，而且理论上超时了不止一点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=59;
struct sys{int h,f;}s[N]; //升序，f=1；降序，f=-1
int n,ans,a[N];
void dfs(int p,int t) { //正在安排第p个导弹,已经有t个系统
	if (p==n+1) {
		ans=min(ans,t);
		return;
	}
	int th=a[p];
	for (int i=1;i<=t;++i) {
		if (s[i].f*s[i].h<s[i].f*th) { //可用
			int k=s[i].h;
			s[i].h=th;
			dfs(p+1,t);
			s[i].h=k;
		}
	}
	t++;
	s[t]=(sys){th,1};
	dfs(p+1,t);
	s[t].f=-1;
	dfs(p+1,t);
	t--;
}
int main() {
	while (1) {
		while (ans--) s[ans].h=s[ans].f=0;
		ans=INT_MAX;
		cin>>n;
		if (n==0) break;
		for (int i=1;i<=n;++i) cin>>a[i];
		dfs(1,0);
		cout<<ans<<endl;
	}
	return 0;
}

//你抄了吗
```


### 考虑优化

本题剪枝思路：**（针对降序情况，升序同理）**

1. 如果当前已经花费的系统数 $\geq$ 已知最优方案，那么**直接退出**即可。

2. **如果已经存在能够拦截的系统**，那么打死**不新建**。例子：四枚导弹高度为 $10000, 1, 999, 888$，既然 $1$ 这个位置肯定要拦截，那么一定要牺牲一个系统。需要考虑的就是到底是牺牲 $10000$ 的系统，还是新建一个来拦截 $1$。这个例子中，答案是一样的。但是事实上我们并无法确定 $10000$ 这个系统就算不牺牲，是否能拦截后面的 $999$ 和 $888$ 这两枚导弹。（e.g. $2, 1, 999, 888$），那么显然将来来到了第三个位置再新建系统更加有主动权（这个剪枝优化最大）。

3. 这个剪枝是建立在上一个剪枝的前提下的。假设存在两个系统，他们都能拦截当前这个导弹，那么根据剪枝 2 的理论，必须使用这两个系统中的一个来拦。不说什么数学证明（蒟蒻不懂呐），根据常识就可以知道：因为无论这个系统最初高度值是多少，拦截后他都会变成当前导弹的高度，而另外一个未使用的系统则会保持不变。因为对于一个降序的系统，他可以拦截比系统高度值低的任何导弹，却无法拦截更高的导弹，因此对于降序系统而言系统高度越高代表越“优”，因此最优情况就是**拿原本高度低的系统去拦截**。（其实是一大堆废话，常识哪有这么复杂 qq）

### 其他一些细节

  1. 升序情况的剪枝和上述本质同理，甚至都不需要复制黏贴重新写，因为**所有 `if` 语句判断符号完全相反**的情况下，不妨把每个系统设成 `struct` 结构，包含 $h$ 和 $f$ 两个参数，分别表示高度和升降方向。升序，$f=1$；降序，$f=-1$。这样的话，在所有剪枝 `if` 语句判断的时候（比大小）条件里乘上一个 $f$，就可以一次完成两种情况的判断了。

2. 虽说剪枝判断的时候升降序可以一起搞，但是真正进一步递归必须分开。用 `nxt[]` 数组中 $nxt_1$ 和 $nxt_3$ **分别**记录的是降序和升序中最没潜力的那套系统。每次 $O(n)$ 扫过所有可能系统，记录 $nxt$，分别递归**一次即可**。


3. 代码里 $nxt$ 数组看似不太高深，实际上也只是为了压缩代码长度方便而设。本身 $f=1$ 或 $f=-1$ 代表了升降两种情况，那么不妨调用 $nxt_{f+2}$ 来替代 $nxt_f$，使其变成正数。所以，`nxt[]` 数组真正有用的只有 $[1]$ 和 $[3]$ 两个位置，其他位置你填什么都行。（虽说如此，但是为避免出错，还是建议别用数组，老老实实 `int nxt1,nxt2;` 分开存）







---



看代码罢。

[AC 记录](https://www.luogu.com.cn/record/170376708)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=59;
struct sys{int h,f;}s[N]; //升序，f=1；降序，f=-1
int n,ans,a[N];
void dfs(int p,int t) { //正在安排第p个导弹,已经有t个系统
	if (p==n+1) {
		ans=min(ans,t);
		return;
	}
	if (t>=ans) return;	
	int th=a[p];
	int nxt[5]; //nxt[3]存升序最没潜力的系统，nxt[1]存降序最没潜力的系统
	memset(nxt,0,sizeof nxt);
	for (int i=1;i<=t;++i)
		if (s[i].f*s[i].h<s[i].f*th) { //可用
			int f=s[i].f;
			if (!nxt[f+2]) nxt[f+2]=i;
			else if (s[i].h*f>s[nxt[f+2]].h) nxt[f+2]=i;
		}
	int nx=1;
	while(nx<=3) {
		if (nxt[nx]) {
			int k=s[nxt[nx]].h;
			s[nxt[nx]].h=th;
			dfs(p+1,t);
			s[nxt[nx]].h=k;
		}
		nx+=2;
	}
	//须得新建
	t++;
	if (!nxt[3]) {
		s[t]=(sys){th,1};
		dfs(p+1,t);
	}
	if (!nxt[1]) {
		s[t]=(sys){th,-1};
		dfs(p+1,t);
	}
	t--;
}
int main() {
	while (1) {
		while (ans--) s[ans].h=s[ans].f=0;
		ans=INT_MAX;
		cin>>n;
		if (n==0) break;
		for (int i=1;i<=n;++i) cin>>a[i];
		dfs(1,0);
		cout<<ans<<endl;
	}
	return 0;
}
```

不懂私我~

---

## 作者：luobotianle (赞：2)

第一眼看上去好像是个线性 DP，然而由于导弹既可以是递增也可以是递减，所以不能 DP；然后发现此题的 $n$ 只有 $50$，考虑直接 DFS。

显然，对于一个导弹，我们有四种情况来拦截它：

1. 用一个已经建立好的递增拦截装置拦截；

2. 用一个已经建立好的递减拦截装置拦截；

3. 新建一个递增拦截装置；

4. 新建一个递减拦截装置。

爆搜的复杂度显然是撑不住的，考虑优化。

首先，当我们能够用已经建好的拦截装置拦截时，我们一定不会新建一个；所以上面的1和3只需选一个，2和4只需选一个即可。

然后考虑最优性剪枝。如果目前使用的拦截装置数量已经比 $ans$ 多了，直接返回即可。

这两个剪枝下来还是会 T，怎么办？
我们发现，如果对于一个导弹，我们有两个递增装置都能够拦截它，那么基于**贪心**，我们一定会选择**目前高度最高的一个**去拦截它（因为低的那一个“更有潜力”）；

如现在有两个递增装置，第一个依次拦截了高度为 `2 5 8` 的三枚导弹，第二个拦截了 `6 7` 的两枚导弹，那么如果又来了一发高度为 `9` 的导弹，那么用第一个拦截一定会比第二个更优。

递减装置同理。

所以，我们在向下更新时，对于用之前的装置的情况，我们只需递归一次即可，大大降低了复杂度，可以通过本题。

其他细节代码中有展示。

```cpp
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
const int N=55;
int n,a[N];
vector<int> up,down;//分别记录递增序列的最大值和递减序列的最小值 
int ans;
void dfs(int now){
	int x=up.size(),y=down.size();
	if(x+y>=ans)return;//最优性剪枝 
	if(now>n){//全部拦截，更新答案 
		ans=min(ans,x+y);
		return;
	}
	for(int i=0;i<x;i++){//遍历每一个递增序列 
		if(up[i]<a[now]){
			int tmp=up[i];
			up[i]=a[now];
			dfs(now+1);
			up[i]=tmp;
			break;//显然我们每次只会更新第一个值，第一个找到的值一定是可行的最大值 
		}
	}
	if(x==0||up[x-1]>=a[now]){//新建一个递增装置 
		up.push_back(a[now]);
		dfs(now+1);
		up.pop_back();
	}
	//下面为递减分支，和上面一样 
	for(int i=0;i<y;i++){
		if(down[i]>a[now]){
			int tmp=down[i];
			down[i]=a[now];
			dfs(now+1);
			down[i]=tmp;
			break;
		}
	}
	if(y==0||down[y-1]<=a[now]){
		down.push_back(a[now]);
		dfs(now+1);
		down.pop_back();
	}
}
int main(){
	while(cin>>n){
		if(n==0)break;//题目中没说，但 n=0 是多测的结束标志 
		ans=0x7fffffff;
		up.clear();down.clear();//多测清空 
		for(int i=1;i<=n;i++)cin>>a[i];
		dfs(1);
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：yaoshuen (赞：1)

### 简单搜索+剪枝


---

思路：用一个数组 ${s_{n}}$ 记录上升的拦截系统，对于每个 $s_{i}$，表示的是该系统拦截的最后一个（即最高的）导弹，那么判断一个导弹能否被该系统拦截只需判断这个导弹的高度是否大于 $s_{i}$ 即可。

下降的系统也是同理。

判断对于一个导弹是否需要新开一个系统只要记录有没有系统能够拦截它，若没有就新开一个。


---

#### 剪枝

1.每次在调用深搜函数时先判断当前所用系统数是否大于或等于当前最小值。若是，则返回。

理由：我们知道，在向后处理过程中，所用拦截系统数必然只增不减（要么把导弹加入已知系统，要么新开一个系统），所以一旦现在所用系统数大于或等于目前答案，那么现在的状态得到的答案最少也只会和目前答案相等，对其没有任何贡献。

2.一个导弹若能加入不止一个拦截系统，那么仅搜索他加入第一个系统的情形。

理由：根据循环的顺序，第一个可加入的拦截系统必然是高度最高的，加入最高的拦截系统显然对答案最有益。

AC_CODE 如下


```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	int f=1,s=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
int n;
int a[60];
vector<int>s,j;
int ans=60;
void dfs(int dep){
	int ss=s.size(),jj=j.size();
	if(ss+jj>=ans) return;
	if(dep>n){
		ans=min(ans,(int)(ss+jj));
		return;
	}
	bool f1=0,f2=0;
	for(int i=0;i<ss;i++){
		if(a[dep]>s[i]){
			int tmp=s[i];
			s[i]=a[dep];
			f1=1;
			dfs(dep+1);
			s[i]=tmp;
			break;
		}
	}
	for(int i=0;i<jj;i++){
		if(a[dep]<j[i]){
			int tmp=j[i];
			j[i]=a[dep];
			f2=1;
			dfs(dep+1);
			j[i]=tmp;
			break;
		}
	}
	if(f1==0){
		s.push_back(a[dep]);
		dfs(dep+1);
		s.pop_back();
	}
	if(f2==0){
		j.push_back(a[dep]);
		dfs(dep+1);
		j.pop_back();
	}
}
void doit(){
	ans=60;
	s.clear();
	j.clear();
	dfs(1);
	printf("%d\n",ans);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	while(1){
		n=read();
		if(n==0) break;
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		doit();
	}
	return 0;
}

```

---

## 作者：GXZJQ (赞：0)

# P10490 Missile Defence System 题解

[题目链接](https://www.luogu.com.cn/problem/P10490)

## 思路分析

本题考查深度优先搜索 DFS。

对于本题，首先要弄明白它的搜索顺序：

- 从前往后枚举每颗导弹属于上升子序列还是下降子序列；
- 如果这颗导弹属于上升子序列，枚举这颗导弹属于哪一个上升子序列，反之同理。

那么我们就只需要借鉴一下最长上升子序列中的贪心优化方式，记 $U_i$ 表示第 $i$ 个上升子序列的末尾元素，$D_i$ 表示第 $i$ 个下降子序列的末尾元素，然后直接枚举每种情况即可。其余细节部分请参见代码注释：

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 50 + 5;
int n, h[N], U[N], D[N], ans = 0x3f3f3f3f;
bool flag = false;

/**
 * @brief 深度优先搜索函数
 *
 * @param su 当前拦截上升导弹序列的防空系统数
 * @param sd 当前拦截下降导弹序列的防空系统数
 * @param cnt 当前正在考虑划分哪个导弹
 **/
void DFS(int su, int sd, int cnt) {
	if (su + sd >= ans) return; //最优性剪枝：结果已经不可能比最优解更优了，就不用继续枚举了，直接返回
	if (cnt == n + 1) { //已经枚举了所有导弹，考虑更新答案
		ans = min(su + sd, ans);
		return;
	}

	//考虑将当前导弹划分到上升系统中
	flag = false;
	for (int i = 1; i <= su; i++) {
		if (U[i] < h[cnt]) {
			int tmp = U[i];
			U[i] = h[cnt];
			DFS(su, sd, cnt + 1);
			U[i] = tmp; //深度优先搜索还原现场
			flag = true;
			break;
		}
	}
	if (!flag) { //新建一个上升系统
		U[su + 1] = h[cnt];
		DFS(su + 1, sd, cnt + 1);
	}

	//考虑将当前导弹划分到下降系统中
	flag = false;
	for (int i = 1; i <= sd; i++) {
		if (D[i] > h[cnt]) {
			int tmp = D[i];
			D[i] = h[cnt];
			DFS(su, sd, cnt + 1);
			D[i] = tmp; //深度优先搜索还原现场
			flag = true;
			break;
		}
	}
	if (!flag) { //新建一个下降系统
		D[sd + 1] = h[cnt];
		DFS(su, sd + 1, cnt + 1);
	}
}

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	while (cin >> n, n) {
		ans = 0x3f3f3f3f;
		for (int i = 1; i <= n; i++) cin >> h[i];
		DFS(0, 0, 1);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Zhl2010 (赞：0)

## 题目概括
题目给定一个长度为 $n$ 的数组 $w_n$，要求我们用最少的上升子序列和下降子序列完全覆盖该数组。

求该方案的上升子序列和下降子序列的总个数。
## 思路
**贪心思想**：在末尾添加最接近当前数量的元素的递增或递减序列（其中最后一个元素小于 $q_u$，最大或大于 $q_u$，最小的序列）。


因此，两个表 $up_i$ 和 $down_i$ 可分别用于表示第i个递增序列和递减序列的结束元素。在研究过程中，根据上述原理，将尽可能多的序列添加到数量最多的序列中，是满足上述想法的解决方案。

`DFS` 迭代：指定当前可搜索导弹拦截系统的最大最大数量 $cnt$ （即答案是 $cnt$）。从 $0$ 开始，每次运行 `DFS` 一次。如果当前 $cnt$ 无法拦截所有导弹，则执行 `cnt++` （即 `+1` 搜索步骤）和 `DFS`，直到它们合法（这是一个迭代深化过程）。则此时的 $cnt$ 即为答案。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q[110],up[110],down[110],ans;
void dfs(int s,int su,int sd){
	if(su+sd>=ans)return;
	if(s==n){
		ans=su+sd;
		return;
	}
	
	//1(上升)
	int k=0;
	while(k<su&&up[k]>=q[s])k++;
	int t=up[k];
	up[k]=q[s];
	if(k<su)dfs(s+1,su,sd);
	else dfs(s+1,su+1,sd);
	up[k]=t;
	
	//2(下降)
	k=0;
	while(k<sd&&down[k]<=q[s])k++;
	t=down[k];
	down[k]=q[s];
	if(k<sd)dfs(s+1,su,sd);
	else dfs(s+1,su,sd+1);
	down[k]=t;
	return;
}
int main(){
	while(cin>>n&&n){
		for(int z=0;z<n;z++){
			scanf("%d",&q[z]);
		}
		ans=n;
		dfs(0,0,0);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：yx666 (赞：0)

# 题解：P10490 Missile Defence System
## Part 1：题目描述
国家 R 更新了他们的导弹防御系统。新型系统可以击落一系列导弹，只要它们按高度升序或按高度降序到来。

给定一系列到来导弹的高度，将军想知道需要多少套新型系统才能将它们全部击落。

输入包含多个测试用例。每个测试用例的第一行包含一个整数 $n (1\le n\le 50)$。接下来的一行包含 $n$ 个不同的整数，表示高度。

特别的，当 $n=0$ 时，表示输入数据结束。

对于每个测试用例，输出一行，包含所需系统的数量。

## Part 2：题解
### Part 2.1：确定算法
最开始，认为是线性 DP，最长上升子序列和最长下降子序列。

但是经过推敲，一个导弹可能被上升的覆盖，也可能被下降的覆盖，具有后效性，不能用 DP。

注意到 $1\le n\le 50$ 这极小的数据，考虑 dfs 爆搜。

### Part 2.2：搜索策略
对于一个导弹，我们有四个方法来拦截它：

1. 新建递增拦截装置；

2. 新建递减拦截装置。

3. 已经建好的递增拦截装置；

4. 已经建好的递减拦截装置；


如果这样爆搜，时间复杂度十分炸裂（需要新建、以及遍历每一个拦截装置），考虑剪枝。

### Part 2.3：剪枝策略
记 $up_i$ 表示第 $i$ 套递增拦截装置**最后拦截高度**，$dn_i$ 表示第 $i$ 套递减拦截装置**最后拦截高度**。

$a_i$ 表示第 $i$ 枚导弹高度，当前搜索到第 $x$ 枚。

$|up|$ 表示递增拦截装置个数，$|dn|$ 同理。

可以证明，**$up$ 单调递增，$dn$ 单调递减**（证明在后文）。

#### Part 2.3.1：策略 1
记 $ans$ 表示某一次 dfs 后的答案。

如果当前已经建立的拦截装置大于 $ans$，回溯（最优性剪枝）。

#### Part 2.3.2：策略 2
我们发现，对于方法 1、2，我们只有在没有拦截装置可用时才会使用。

而我们判断有没有拦截装置可用，只需判断：

1. $up_{back}\ge a_x$（所有递增都太高）或 $dn_{back}\le a_x$（所有递减都太矮）

2. $|up|=0$ 或 $|dn|=0$（压根没有拦截装置）。

只有这些时候才会新建。

#### Part 2.3.3：策略 3
对于方法 3、4，我们贪心地想到，对于导弹 $x$，有：

1. 使用递增装置 $i$，最优时是 $up_i$ 恰好是**小于 $a_x$ 的最大值**。

2. 使用递减装置 $i$，最优时是 $dn_i$ 恰好是**大于 $a_x$ 的最大值**。

例子：

递增装置 1 依次拦截了高度为 $2,3,8$ 的三枚导弹（$up_1=8$），递增装置 2 依次拦截了高度为 $1,6$ 的两枚导弹（$up_2=6$）。

如果又来了一枚高度为 $11$ 的导弹，那么用装置 1 拦截一定会比装置 2 更优（如果不理解为什么最优，再想想如果来袭的下一个导弹是 $10$ 呢）。

这样我们就完成了所有的剪枝策略。

贴一下代码：

``` cpp
int n,ans,a[N];

vector<int>up,dn;
// up_i 表示第 i 套递增拦截装置**最后拦截高度**
// dn_i 表示第 i 套递减拦截装置**最后拦截高度**。

void dfs(int x){
	int l_up=up.size(),l_dn=dn.size();
	
	// 可行性剪枝（策略 1）
	if(l_up+l_dn>=ans) return ;
	if(x>n){
		ans=min(ans,l_up+l_dn);
		return ;
	}
	
	if(l_up==0||up.back()>=a[x]){	// 策略 2
		up.push_back(a[x]);
		dfs(x+1);
		up.pop_back();				// 回溯
	}else{							// 策略 3
		for(int i=0;i<l_up;++i){
			if(up[i]<a[x]){
				int tp=up[i];
				up[i]=a[x];
				dfs(x+1);
				up[i]=tp;			// 回溯		
				break;				// 每个导弹由已建立的拦截的最优解只有一个，不需要去尝试其他的。
			}
		}
	}
	
	if(l_dn==0||dn.back()<=a[x]){	// 策略 2
		dn.push_back(a[x]);
		dfs(x+1);
		dn.pop_back();				// 回溯
	}else{							// 策略 3
		for(int i=0;i<l_dn;++i){
			if(dn[i]>a[x]){
				int tp=dn[i];
				dn[i]=a[x];
				dfs(x+1);
				dn[i]=tp;			// 回溯
				break;
			}
		}
	}
}
```

### Part 2.4：可行性证明
很多题解都没有证明，$up$ 单调递增，$dn$ 单调递减，这里证明一下（数学归纳法）。

首先，$|up|=0,|dn|=0$ 时，是单调序列。

有以下修改情形（记 $t$ 表示新的拦截高度，$dn$ 同理，下标从 $1$ 开始），对于单调递增的 $up$：

1. 增加（新建系统）：此时 $up_{back}<t$， 即 $\forall i\in[1,|up|],up_i<t$，不影响单调性。

2. 修改：记修改的位置为 $p$，则 $\forall i\in[1,p-1],up_i>t$，且 $\forall i\in[p+1,|up|],t>up_p>up_i$，同样不影响单调性。

证明毕。

## Part 3：代码
1. 多组数据，注意清空。

2. 题目没说，当 $n=0$ 时，表示输入数据结束。

3. 篇幅原因，没贴快读上去

``` cpp
#include<bits/stdc++.h>
using namespace std;

int read();
void write(int x);

const int inf=2147483647;

#define N 55

int n,ans,a[N];

vector<int>up,dn;
// up_i 表示第 i 套递增拦截装置**最后拦截高度**
// dn_i 表示第 i 套递减拦截装置**最后拦截高度**。


void dfs(int x){
	int l_up=up.size(),l_dn=dn.size();
	
	// 可行性剪枝（策略 1）
	if(l_up+l_dn>=ans) return ;
	if(x>n){
		ans=min(ans,l_up+l_dn);
		return ;
	}
	
	if(l_up==0||up.back()>=a[x]){	// 策略 2
		up.push_back(a[x]);
		dfs(x+1);
		up.pop_back();				// 回溯
	}else{							// 策略 3
		for(int i=0;i<l_up;++i){
			if(up[i]<a[x]){
				int tp=up[i];
				up[i]=a[x];
				dfs(x+1);
				up[i]=tp;			// 回溯		
				break;				// 每个导弹由已建立的拦截的最优解只有一个，不需要去尝试其他的。
			}
		}
	}
	
	if(l_dn==0||dn.back()<=a[x]){	// 策略 2
		dn.push_back(a[x]);
		dfs(x+1);
		dn.pop_back();				// 回溯
	}else{							// 策略 3
		for(int i=0;i<l_dn;++i){
			if(dn[i]>a[x]){
				int tp=dn[i];
				dn[i]=a[x];
				dfs(x+1);
				dn[i]=tp;			// 回溯
				break;
			}
		}
	}
}

signed main(){
	for(;;){
		n=read();
		if(n==0) break;
		for(int i=1;i<=n;++i)
			a[i]=read();
		
		// 注意清空
		ans=inf;up.clear();dn.clear();
		
		dfs(1);
		
		// 注意输出换行
		write(ans),putchar('\n');
	}
	return 0;
}
```

---

## 作者：abc1856896 (赞：0)

导弹防御系统很自然的想到最长上升子序列算法，不过这里的条件是一套防御系统的导弹拦截高度要么一直上升要么一直下降，所以用最长上升子序列算法是不正确的。

考虑直接爆搜。

每次爆搜这个数是存在上升子序列还是在下降子序列，然后进行一个爆搜即可。

# 爆搜代码

```cpp
int n,up[55],down[55];
int a[55];
void dfs(int u,int up_len,int down_len){ 
	if(up_len+down_len>=ans) return;
	if(u==n){
		ans=min(ans,up_len+down_len);
		return;
	}
	int tt=0;
	while(t<up_len && up[tt]>a[u]) tt++;
	if(kk<up_len){
		int kk=up[tt];
		up[tt]=a[u];
		dfs(u+1,up_len,down_len);
		up[tt]=kk;
	}
	else{
		int kk=up[tt];
		up[tt]=a[u];
		dfs(u+1,up_len+1,down_len);
		up[tt]=kk;
	} 
	tt=0;
	while(tt<down_len && down[tt]<a[u]) tt++;
	if(tt<down_len){
		int kk=down[tt];
		down[tt]=a[u];
		dfs(u+1,up_len,down_len+1);
		down[tt]=kk;
	}
}
```

---

## 作者：wwwidk1234 (赞：0)

## 解析

给定一些导弹，要求用“上升拦截系统”或“下降拦截系统”拦截导弹，其中，**上升拦截系统**只能**拦截上升序列**，**下降拦截系统**只能**拦截下降序列**。问最多要用多少套系统才能拦截所有的导弹。

看到 $n \le 50$ 可以想到 dfs。用 `dfs(u,d,dep)` 表示当前在看第 $dep$ 个数，已经设置了 $u$ 个上升拦截系统，$d$ 个下降拦截系统。设 $up_i$ 和 $down_i$ 表示第 $i$ 套上升（下降）系统最后一次拦截的导弹高度。

做法：一次 dfs 有三种方案，分别是：

1. 用第 $i$ 套上升系统拦截；
2. 用第 $i$ 套下降系统拦截；
3. 新开一个上升（下降）拦截系统；

但是，这种做法每次都要枚举 $i$，显然会 TLE。

考虑优化，假设要用上升拦截系统拦截一个导弹，那么可以**用最后一次拦截高度最大的系统拦截**。举个例子，我们要拦截高度 $h=10$ 的导弹，有 $4$ 个系统：

$$
\text{甲}\left\{1,2,3,4,5\right\} \\
\text{乙}\left\{1,3,4,5,7\right\} \\
\text{丙}\left\{1,4,5,6,8\right\} \\
\text{丁}\left\{1,2,5,7,9\right\} \\
$$

显然，用丁系统拦截该导弹最适合。下降拦截系统也同理。

## 代码
```cpp
int n,a[N];
int up[N],down[N];
//up[k],down[k]表示第[k]个上升/下降系统中最后一个拦截的元素是什么
int ans=300948787;  //it just a number,it didn't mean anything else
inline int find_up(int x,int u)
{
    for(int i=1;i<u;i++)
    	if(x>up[i]) return i;
    return u;
}
inline int find_down(int x,int d)
{
    for(int i=1;i<d;i++)
    	if(x<down[i]) return i;
    return d;
}
void dfs(int u,int d,int dep)  //当前在看第dep个数,已经有u个上升,d个下降
{
    if(u+d>=ans) return; //最优性剪枝
    if(dep>n)
    {
        ans=u+d;
        return;
    }
    //上升
    int x=find_up(a[dep],u+1);  //这个数应该放在up[x]上
    const int k=up[x];
    up[x]=a[dep];
    dfs(max(x,u),d,dep+1);
    up[x]=k;   //回溯
    //下降
    x=find_down(a[dep],d+1);  //这个数应该放在up[x]上
    const int kk=down[x];
    down[x]=a[dep];
    dfs(u,max(x,d),dep+1);
    down[x]=kk;   //回溯
}
```

本题与 [P10483 小猫爬山](https://www.luogu.com.cn/problem/P10483) 相类似，推荐 AC 本题后完成这道题。

---

