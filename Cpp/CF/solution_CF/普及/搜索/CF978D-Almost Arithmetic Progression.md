# Almost Arithmetic Progression

## 题目描述

Polycarp 喜欢等差数列，对于一个数列 $ [a_1,a_2,a_3,\dots,a_n] $，如果对于每个 $ i\,(1\le i < n) $，$ a_{i+1}-a_i $ 的值均相同，那么这个数列就是一个等差数列。例如，$ [42] $ ，$ [5,5,5] $ ，$ [2,11,20,29] $ 和 $ [3,2,1,0] $ 是等差数列，但是 $ [1,0,1] $，$ [1,3,9] $ 和 $ [2,3,1] $ 不是。

根据定义，任何长度为 $ 1 $ 或 $ 2 $ 的数列都是等差数列。

Polycarp 找到了一个只包含正整数的数列 $ [b_1,b_2,b_3,\dots,b_n] $ 。他只想最多将每个元素改变一次。换句话说，对于每个元素，有三种选项：自增 $ 1 $，自减 $ 1 $ 或者不变。

你需要找到对 $ b $ 中元素操作（每个只能操作一次）的最小次数，使 $ b $ 变成一个等差数列。

操作完成后的数列可以含有 $ 0 $ 。

## 说明/提示

在样例 $ 1 $ 中，Polycarp 应该将第 $ 1 $ 个元素加 $ 1 $ ，将第 $ 2 $ 个元素加 $ 1 $ ，将第 $ 3 $ 个元素加 $ 1 $ ，并且不改变第 $ 4 $ 个元素。所以，Polycarp 操作之后的数列为 $ [25,20,15,10] $ 。

在样例 $ 2 $ 中，Polycarp 不应进行操作，因为他的数列已经是等差数列了。

在样例 $ 3 $ 中，不可能通过上述的操作将数列变为等差数列。

在样例 $ 4 $ 中，Polycarp 应该只将第 $ 1 $ 个元素加 $ 1 $ 。操作之后的数列为 $ [0,3,6,9,12] $ 。

## 样例 #1

### 输入

```
4
24 21 14 10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
500 500
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
14 5 1
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
5
1 3 6 9 12
```

### 输出

```
1
```

# 题解

## 作者：feicheng (赞：6)

### 题意简述：
有一个数列，可以对数列的值 $+1$ 或 $-1$，修改若干次，使得数列为等差数列，最小化修改次数,无解输出 $-1$。

### 思路讲解：
这道题其实所需要的算法知识并不多，更多的是对等差数列的认识。

我们知道一个等差数列由首项 $a_1$ 和公差 $d$ 所决定，而只要确定了等差数列中的两项，公差 $d$ 就确定了。

因而我们可以思考枚举等差数列前两项的可能性，来检验整个数列能否成为一个等差数列。

具体地，设公差为 $d$，如果数列 $a$ 的某两项 $a_i$ 和 $a_{i-1}$ 满足如下其中一个条件时，不能通过修改数列使其构成一个等差数列。

$$
\left\{
      \begin{array}{lr}
      a_i-a_{i-1} > d+1\\
      a_i - a_{i-1}<d-1
      \end{array}
\right.
$$
这样只需枚举等差数列前两项的可能性，再进行检验即可。
                        
由于前两项的取值仅有 $9$ 种，所以时间复杂度为 $O(9n)$，可以通过本题。
                        
### 核心代码：
```cpp
inline int judge(int d) {//检验该公差是否可行
	int res = 0;
	for(ri i = 3;i <= n;++i){
		if(b[i]-b[i-1] > d + 1 || b[i]-b[i-1] < d - 1) return -1;
 		else if(b[i]-b[i-1] == d + 1) ++res,b[i]--;
 		else if(b[i] - b[i-1] == d - 1) ++res,++b[i];
	} 
	return res;
}
```
      


---

## 作者：FanYongchen (赞：3)

因为要构成一个[等差数列](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97/1129192?fr=aladdin)，所以很容易想到

### 只要确定第 1、2 项，就可确定后面的每一项

于是我们可以先枚举第 1、2 项的操作方法，然后求出整一个序列。若数组中有一个数与求出的序列的数字相差 $\geq 1$,则判定这种方法不行。

代码如下：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int a[100005];
int tmp[100005];//临时数组 
int d[3]={0,1,-1};//操作的方法 
int cnt[3]={0,1,1};//操作所需变化次数 
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    int ans=0x7fffffff;//先赋成一个极大值 
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)//枚举第1、2项的操作方法 
        {
            memcpy(tmp,a,sizeof(tmp));//先复制数组 
            bool isCan=true;//这种枚举方法是否满足题目要求 
            int sub=tmp[0]+d[i]-(tmp[1]+d[j]);//求出公差 
            tmp[1]+=d[j];//更新第一个数(这里和下面更新数字时不能用原数组) 
            int c=cnt[i]+cnt[j];//共用的次数 
            for(int k=2;k<n;k++)//从第三项开始 
            {
                bool find=false;//对于这个数，判断它是否有一个操作方法，使得可以构成一个等差数列 
                for(int l=0;l<3;l++)//枚举 
                    if(tmp[k-1]-(tmp[k]+d[l])==sub)//构成等差数列 
                        {tmp[k]+=d[l]/*更新数字*/;c+=cnt[l]/*累加次数*/;find=true/*记录已经找到*/;break;}
                if(!find) {isCan=false;break;}//若没找到，判定这个第1、2项的方法不能满足题意 
            }
            if(isCan) ans=min(ans,c);//若满足，更新答案 
        }
    if(ans==0x7fffffff) ans=-1;//无解的情况 
    cout<<ans;
    return 0;
}
```


---

## 作者：Sophon (赞：3)

由于是等差数列，所以只要第一项和第二项确定，那么通项公式就随之确定，
于是先调整（枚举）a1，a2，确定通项公式，然后将a数列的后面所有项与通项公式对比，只要距离超过1，那么这种情况无效，如果距离小于等于1，就加上调整的距离，输出最小解即可
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[100005];//存输入
int moveA1[] = { 0,0,0,1,1,1,-1,-1,-1 };//调整a1
int moveA2[] = { 0,1,-1,0,1,-1,0,1,-1 };//调整a2


int ans = 0x7f7f7f7f;//先将答案初始化成很大
int n;

int calc(int a1, int a2, int n)//计算通项公式
{
	return a1 + (n - 1)*(a2 - a1);
}
void work(int a1, int a2, int change)//change 为a1和a2的调整值之和
{
	int temp = 0;
	for (int i = 3; i <= n; i++)//从第三项开始向后遍历原数列
	{
		int t = abs(calc(a1, a2, i) - a[i]);//计算该项需要调整的距离
		if (t > 1)//如果距离超过1，结束
		{
			return;
		}
		else//否则加上调整值
		{
			temp += t;
		}
	}
	temp += change;//加上第一项和第二项的调整值
	ans = min(ans, temp);//取较小值保存
}
int main()
{

	cin >> n;

	if (n <= 2)//由题项数小于等于2是等差
	{
		cout << 0 << endl;
		return 0;
	}

	for (int i = 1; i <= n; i++)//输入
	{
		cin >> a[i];
	}

	for (int i = 0; i < 9; i++)//分九种枚举a1, a2
	{
		work(a[1] + moveA1[i], a[2] + moveA2[i], abs(moveA1[i]) + abs(moveA2[i]));
	}

	if (ans != 0x7f7f7f7f)//如果发生调整
	{
		cout << ans << endl;
	}
	else//如果一次调整都没有
	{
		cout << -1 << endl;
	}
}
```
对于楼上暴力枚举剪枝的做法，蒟蒻在此献上膝盖

---

## 作者：nstk0513 (赞：2)

### 骗分过样例，暴力出奇迹！

我是一个蒟蒻，不会正解，但是还是过了，用的是暴搜。

搜索方法很简单，就是对于每一个数枚举它是不变，增加1还是减少1。时间复杂度$O(3^{n})$。但是很显然，这样是过不了的。所以，我加了若干个优化：

1，可行性剪枝：如果现有的数改变后的值与上一个数改变后的值之差不等于前面固定下来的等差数列中的相等的差，停止搜索（因为这标志着现在这种改变方式已经是不成立的）。

2，最优性剪枝：如果搜索到现在改变的次数已经超过或等于了最优答案，停止搜索（因为即使搜完了也无法更新最优答案，没有用）。

但是这样也未必能过。我想到一组数据卡掉了我的搜索：最后两个数差值特别大，导致前面搜完了好多遍总是在最后卡住。所以我又加了一个优化：在搜索前处理初始序列最大的差值和最小的差值，如果这两个值的差大于4则直接输出无解。因为以这道题的变换方式，每一个差与原来的差的变化值最多为2，所以两个差的差最多为4，否则不可能相等。

所以这样就可以$O(3^{n})$（其实是$O($能过$)$，~~因为我也不知道到底是多少~~）过200000的数据量了（或者是因为CodeForces机子效率太高？）。而且没有FST，没有被Hack，如果有能Hack的数据也欢迎指正。

代码：

```
#include <iostream>
#include <cstdio>
using namespace std;
#define MAXN 100005
int n,b[MAXN],maxgap,mingap,gap,tot,ans;
int move[3]={0,1,-1};
//手写STL优化常数
inline int max(int a,int b) { if(a>b) return a; else return b; }
inline int min(int a,int b) { if(a<b) return a; else return b; }
inline int abs(int x) { if(x>0) return x; else return -x; }
void dfs(int u,int k){
    if(tot>=ans) return;//最优性剪枝
    if(u==n){
        ans=min(tot,ans);
        return;
    }
    for(int i=0; i<=2; i++){
        if(u==1) gap=b[u+1]+move[i]-b[u]-move[k];
        else{
            if(b[u+1]+move[i]-b[u]-move[k]!=gap) continue;
            //可行性剪枝
        }
        if(move[i]!=0) tot++;
        dfs(u+1,i);
        if(move[i]!=0) tot--;//回溯
    }
}
char ch; int f;
inline void read(int &x){
     x=0,f=1;
     while(ch<'0' || ch>'9'){
         if(f=='-') f=-1;
         ch=getchar();
     }
     while(ch>='0' && ch<='9'){
         x=x*10+ch-'0';
         ch=getchar();
     }
     x*=f;
}
//读入优化卡常
int main(){
    read(n);
    maxgap=-1;
    mingap=2147483647;
    for(int i=1; i<=n; i++){
        read(b[i]);
        if(i!=1){
            maxgap=max(maxgap,abs(b[i]-b[i-1]));
            mingap=min(mingap,abs(b[i]-b[i-1]));
        }
    }
    if(n<=2){
        printf("0\n");
        return 0;
    }
    //只有一个或两个数的数列必然是等差数列
    if(maxgap-mingap>4){
        printf("-1\n");
        return 0;
    }
    //当最大差值和最小差值的差值大于4时直接返回无解
    ans=MAXN;
    tot=0; dfs(1,0);
    //一个比较玄学的优化：先搜改变次数少的，不知是否有效
    tot=1; dfs(1,1);
    tot=1; dfs(1,2);
    if(ans==MAXN) printf("-1\n");//记得判无解
    else printf("%d\n",ans);
    return 0;
}
```

---

## 作者：liwenxi114514 (赞：1)

### 题目大意
给定一个长度为 $n$ 的序列 $a_i$，求**最少**多少次操作，使得其变为**等差数列**。
操作为：加一、减一或不变。
### 思路
考虑**搜索**，容易有 $O(n^3)$ 的做法如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],minn=INT_MAX;//minn为最少操作次数
bool check(){//判断是否为等差数列
	int x=a[2]-a[1];//公差
	for(int i=2;i<n;i++){
		if(a[i+1]-a[i]!=x){
			return 0;
		}
	}
	return 1;
}
void dfs(int x,int sum){//x表示对a[x]进行操作，sum表示操作次数
	if(x==n+1){
		if(check()){//如果是等差数列，更新答案。
			minn=min(minn,sum);
		}
		return ;
	}
	dfs(x+1,sum);//不变
	a[x]+=1;
	dfs(x+1,sum+1);//加1
	a[x]-=1;//回溯
    a[x]-=1;
	dfs(x+1,sum+1);//减1
	a[x]+=1;//回溯
}
int main(){
	cin>>n;
	if(n<=2){//当n大于2是必定为等差数列
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	dfs(1,0);
	if(minn==INT_MAX){//当minn的值没有被改变时，无解
		cout<<-1;
		return 0;
	}
	cout<<minn;
	return 0;
}
```
显然，这份代码会超时。考虑优化。那如何优化呢？这里介绍两种`dfs`的优化方法：

1.**最优性剪枝**：当现在的答案**大于**了原本的**最小值**，就直接`return`。

2.**可行性剪枝**：**始终保持**答案为**可行**的。

知道这两种剪枝技巧后，就可以优化我们的代码了。若当前的操作次数大于了`minn`，就`return`。（最优性剪枝）始终保持**此次修改所得的公差与第一次修改的公差相等**，就一定可以变为等差数列。（可行性剪枝）

`AC`代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],minn=INT_MAX,pre;//pre为第一次修改的公差
int go[3]={0,-1,1};//表示三种操作方法
void dfs(int x,int sum,int m){//m表示当前所用的操作
	if(sum>=minn){//最优性剪枝，详见文字部分
		return ;
	}
	if(x==n){//由于我们每次考虑的操作是同时改变a[x]和a[x+1]，所以当x==n时就不用再进行操作了
		minn=min(minn,sum);
		return ;
	}
	for(int i=0;i<3;i++){//枚举x+1的修改方案
		if(x==1){//第一次修改
			pre=(a[1]+go[m])-(a[2]+go[i]);//将前两个数修改后求公差
		}else{
			if((a[x]+go[m])-(a[x+1]+go[i])!=pre){//可行性剪枝，详见文字部分
				continue;
			}
		}
		if(i==0){//当x+1不变时，操作次数不用加一。
			dfs(x+1,sum,i/*a[x+1]的修改方案*/);
		}else{
			dfs(x+1,sum+1,i);
		}
	} 
}
int main(){
	cin>>n;
	if(n<=2){
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	dfs(1,0,0);//a[1]不变
	dfs(1,1,1);//a[1]减一
	dfs(1,1,2);//a[1]加一
	if(minn==INT_MAX){
		cout<<-1;
		return 0;
	}
	cout<<minn;
	return 0;
}
```
管理员大大求通过！！！

---

## 作者：J_Kobe (赞：1)

### 题意
将一个数列通过三种操作变成一个等差数列。

三种操作分别为：自增 $ 1 $，自减 $ 1 $ 和不变。


### 思路
我们看到是将一个数列变成等差数列，所以我们可以想到只要确定了其中两个数，那么就可以确定整个序列了，因为等差序列的每相邻两项的差永远是一样的。

那么我们就可以暴力枚举所有情况，每种情况都是不同的两个数放在最前面，确定了这两个数以后，就根据这个公差求出后面的所有项，如果其中有不能通过以上三种操作变成数列中的数的话，那么这种情况就是不行的，如果某种情况是可行的话，那么就用这种情况的总次数与当前的最小值比较，如果小就刷新，否则就不刷新。

接下来就上代码了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int a[N], b[N];

int mx[] = {0, 0, 0, -1, -1, -1, 1, 1, 1};
int my[] = {1, -1, 0, 1, -1, 0, 1, -1, 0};

int n, ans = INT_MAX;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	if (n <= 2)
	{
		printf("0");
		return 0;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			b[j] = a[j];
		}
		b[1] = a[1] + mx[i];
		b[2] = a[2] + my[i];
		int sum = 0;
		int x = b[2] - b[1];
		int y = abs(mx[i]) + abs(my[i]);
		bool flag = true;
		for (int k = 3; k <= n; k++)
		{
			if (b[k] - b[k-1] < x - 1 || b[k] - b[k-1] > x + 1)
			{
				flag = false;
				break;
			}
			if (b[k] - b[k-1] == x - 1)
			{
				b[k]++;
				sum++;
			}
			else if (b[k] - b[k-1] == x + 1)
			{
				b[k]--;
				sum++;
			}
		}
		if (flag == true)
		{
			ans = min(ans, sum + y);
		}
	}
	if (ans == INT_MAX)
	{
		printf("-1");
	}
	else
	{
		printf("%d", ans);
	}
	return 0;
}
```


---

## 作者：OIerZhang (赞：0)

# [CF978D Almost Arithmetic Progression](https://www.luogu.com.cn/problem/CF978D)

简简单单数学题。

## 思路

在这之前，我们需要了解下等差数列的两大要素：首项 $a_1$ 和公差 $d$。

只要我们知道了 $a_1$ 和 $d$，那么就能确定整个等差数列。

那么问题就迎刃而解了！

因为只能自增 $1$、自增 $-1$ 和不变，所以可以枚举 $a_1 + 1, a_1 - 1, a_1$ 三种情况。对应的 $d$ 也可以枚举 $d + 1, d - 1, d$ 三种情况。

对于每一种情况，用 `check()` 函数检查每一种情况的等差数列是否符合操作要求。

## 代码

珍爱账号，远离抄袭。

```cpp
#include <bits/stdc++.h>
#define int long long
#define INF 2e9
using namespace std;

int n, a[100005];

int check(int s, int d)
{
	int res = 0, tmp;
	for (int i = 1; i <= n; i++)
	{
		tmp = abs(a[i] - s);
		if (tmp > 1)
			return INF;
		if (tmp != 0)
			res++;
		s += d;
	}
	return res;
}

signed main()
{
	int d, ans = INF;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	d = a[2] - a[1];
	for (int i = 0; i <= 2; i++)
		ans = min(ans, check(a[1] - 1, d + i));
	for (int i = -1; i <= 1; i++)
		ans = min(ans, check(a[1], d + i));
	for (int i = -2; i <= 0; i++)
		ans = min(ans, check(a[1] + 1, d + i));
	if (ans == INF)
		cout << -1;
	else
		cout << ans;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

先特判：若 $n\le 2$，必然可构成等差数列，所以我们直接输出 `0`。

否则的话我们想，等差数列这个东西只需要得知首项和公差就可以构造整个序列，所以，解法出来了！我们只需枚举第一项和第二项的数值，再一直往后推并记录答案就完事了。

代码（你交交试试）：
```
#include<bits/stdc++.h>
using namespace std;
long long n,s[1100000],ans=LONG_LONG_MAX;
int main(){
	cin>>n;
	if(n<=2){
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++)
		cin>>s[i];
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++){
			for(int z=3;z<=n;z++){
				//同学们自己写 
			}
		}
	cout<<ans;
	return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

输入一个序列，请通过最小操作数将它变为等差数列。

## 解法

当 $n\leq2$ 时直接输出 $0$，因为一定是满足等差数列的。

对于其它情况，我们可以枚举等差数列的差。

因为只可以通过将一个数加一、减一或不变来操作，并且确定前两个数即可确定差，我们就枚举全部前两个数的情况。前两个数中，每个数三种情况，总共 $A_3^3=6$ 种。

枚举到其中一种情况时，进入函数判断是否可以以这个为差，取最小修改次数。

函数具体流程：

1. 首先以一个备用数组 $a$ 来存 $b$，以免改变原数组的值，再以 $c=b_2-b_1$ 来计算差。
2. 从 $3$ 开始枚举 $a$ 数组，若枚举到 $i$ 时 $a_i-a_{i-1}=c$，就可以进入下一次循环，否则就说明需要改变 $a_i$ 的值来使得差一样。
   * 若当前这个差只和 $c$ 相差 $1$，就说明将 $a_i$ 加一或减一就可以满足条件，直接改变 $a_i$ 的值，修改次数加一；
   * 否则，这个 $c$ 就是不行的，返回极大值。
3. 返回修改次数。

**注意**：枚举前两个的修改情况时也要累加进修改次数里。

最后，因为枚举前两个数的情况时改变了 $b$ 的值，所以改回去就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,b[100001],ans = 1e9,a[100001],now;
int o[3] = {1,-1,0};//每种情况

int check()
{
	int c = b[2] - b[1],num = 0;//差值和修改次数
	for(int i = 1;i <= n;i++) a[i] = b[i];//备用数组
	for(int i = 3;i <= n;i++)
	{
		int nc = a[i] - a[i - 1];//新的差
		if(nc != c)//需要修改
		{
			if(nc + 1 == c) a[i]++;
			else if(nc - 1 == c) a[i]--;
			else return 1e9;//无法满足条件
			num++;//修改次数加一
		}
	}
	return num;
}

signed main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&b[i]);
	if(n <= 2){printf("0");return 0;}//长度小于二就一定可以
	for(int i = 0;i < 3;i++)//枚举情况
	{
		for(int j = 0;j < 3;j++)
		{
			b[1] += o[i];
			b[2] += o[j];//修改前两个
			now = 0;
			if(i < 2) now++;//记得要增加修改次数
			if(j < 2) now++;
			ans = min(ans,check() + now);//取最小值
			b[1] -= o[i];//改回去
			b[2] -= o[j];
		}
	}
	if(ans == 1e9) printf("-1");//不可以
	else printf("%d",ans);
	return 0;
}
```

---

## 作者：WegestGao (赞：0)

不管各位大佬是用什么神仙方法打的，反正我看到标签是搜索我就用的 DFS。经过斟酌，我们可以得到的思路是：从 $a_1$ 开始更改（三种情况），当 DFS 完一整个数组后判断是否可行，最后找出所有可行方案更改数量的最小值。

但是，对于这种复杂度异常高（这里不计算了）的情况，肯定是过不了的！

于是，我们可以考虑进行标签内的**剪枝**优化。

### 优化方案

#### 最优性剪枝（过程值中的优化）

我们首先就能想到在 DFS 的过程中，操作数是一直在变的。每一次当 DFS 完的时候，我们都能得到一个操作数的值，此时我们会进行待选答案的迭代（也就是打擂台，最小的数留下），但是，如果再 DFS 过程中，这个操作数大于这个已经选出的待选答案的值，那么我们就可以直接退出 DFS 了。就像这样：
```
if(summ>=ans)   // ans是待选答案，summ是 DFS 过程中操作数的值
    return;
```

#### 可行性剪枝（过程中可行性的判断）

我们知道，在 DFS 中我们原来的算法都是在将所有 $a_i$ 的数值算出来的情况下进行的，这就导致最终算出来的所有 $a$ 数组可能性的数量非常大，肯定是会超时的。我们都知道，由于只有三种情况，所以只要 $a_1$ 和 $a_2$ 的值确定，公差 $d$ 也随之确定，且只有 $3^2=9$ 种可能，我们挨个枚举一遍，然后根据枚举得到的内容再进行 DFS。因此，我们在进行 DFS 的时候可以在确定 $a_i$ 的时候判断是否满足公差 $d=a_i-a_{i-1}$ 就可以了。如果满足，就进行 DFS，如果不满足，就略过当前这种情况。

于是，这个问题就被我们解决了！！！

DFS 代码如下：

```
void dfs(int x,int summ,int d){
    if(summ>=ans) return;
    if(x>n){
        ans=min(ans,summ);
        return;
	}
	for(int i=0;i<3;i++){
		if(i==1) {
			if(a[x]-a[x-1]==d) dfs(x+1,summ,d);
		}
		else {
			a[x]+=dx[i];
			if(a[x]-a[x-1]==d) dfs(x+1,summ+1,d);
            a[x]-=dx[i];
		}
	}
}
```
剩下的主函数的代码大家肯定都会，这里就不放了。

### 注意点

- 当 $n=1,2$ 时，直接输出 `0` 即可，就不用计算了。

- DFS 一定不要忘记回溯！

### 后记

做完题目过了一个晚上，突然发现直接用三重循环就能做，都不用 DFS 了。方法都差不多，大家想写哪种就写哪种！

求管理员通过！

---

## 作者：ny_Dacong (赞：0)

# 思路

一个已知项数等差数列，可以通过首项与公差生成这个等差数列。因此，这道题只需要枚举修改后的等差数列的首项与公差即可。

对这道题而言，首项一共有三种情况。设原首项为 $a$，那么最终的首项分别是 $a+1,a,a-1$。一共 3 种情况。

公差也有三种情况。设原第二项为 $b$，那么最终的公差分别是 $b-a,(b+1)-a,(b-1)-a$。不过注意，这里的 $a$ 有三种情况，所以这里一共 9 种情况。

我们只需枚举这 9 种情况，然后生成对应的等差数列，接着一一检查每个元素并记录即可。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans = 0x3f3f3f3f;
int num[100005];
int check(int First,int d){
	int res = 0,now;
	if(First != num[1]){
		res++;
	}
	for(int i = 2; i <= n; i++){
		now = First+(i-1)*d;
		if(abs(now-num[i]) > 1){
			return 0x3f3f3f3f;
		}
		if(now != num[i]){
			res++;
		}
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d",&num[i]);
	}
	ans = min(ans,check(num[1]+1,num[2]-num[1]));
	ans = min(ans,check(num[1]+1,num[2]-num[1]-1));
	ans = min(ans,check(num[1]+1,num[2]-num[1]-2));
	ans = min(ans,check(num[1],num[2]-num[1]+1));
	ans = min(ans,check(num[1],num[2]-num[1]));
	ans = min(ans,check(num[1],num[2]-num[1]-1));
	ans = min(ans,check(num[1]-1,num[2]-num[1]+2));
	ans = min(ans,check(num[1]-1,num[2]-num[1]+1));
	ans = min(ans,check(num[1]-1,num[2]-num[1]));
	if(ans == 0x3f3f3f3f){
		printf("-1");
		return 0;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：ILLENIUM_DOOR (赞：0)

### 题意简述

对一个有 $n$ 个数的数列 $a$ 的每个数 $+1$，$-1$ 或不进行更改，使其成为一个等差数列。

若无法做到，输出 $-1$；若能做到输出调整的最小值。

数据范围：$n\leq 100000$。

### solution

首先由等差数列性质得，每两个数的差都为公差 $d$，且两个数即可确定公差。

则考虑枚举每种不同的 $d$，判断后面每两个数的差值 $d_1$ 是否可通过 $+1$ 或 $-1$ 变为 $d$。若可以则累加答案，不行则直接退出。

最终对于每种不同的情况得到的 $ans$ 取最小值即可。

枚举时，可考虑对于 $a_1$ 与 $a_2$ 定义偏移数组，记录它们 $+1$，$-1$ 或不变组合起来的情况。则共有 $3\times3=9$ 种情况。

### 坑点

+ 判断时不能使用原数组，因为会改变原数组的值。

+ 新数组 $b$ 的前两项需初始化成偏移后对应的 $a$ 数组前两项。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
int f[MAXN],b[MAXN];
int mx[]={0,0,0,-1,-1,-1,1,1,1};
int my[]={1,-1,0,1,-1,0,1,-1,0};
int n,ans=0x7f7f7f;
void work(int diff,int al){ //al 记录前两项改变的值 
	int temp=0;
	for(int i=3;i<=n;i++){
		if(b[i]-b[i-1]<diff-1||b[i]-b[i-1]>diff+1) //不符合条件 
			return;
		if(b[i]-b[i-1]==diff-1) b[i]++,temp++;
		else if(b[i]-b[i-1]==diff+1) b[i]--,temp++;
	}
	ans=min(ans,temp+al);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>f[i];
	if(n<=2){ //由题得项数小于等于二时直接输出，进行特判 
		cout<<"0";
		return 0;
	}
	for(int i=0;i<9;i++){
		for(int j=1;j<=n;j++) b[j]=f[j];
		b[1]=f[1]+mx[i];
		b[2]=f[2]+my[i];//b 数组前两项需进行对应更改 
		work(b[2]-b[1],abs(mx[i])+abs(my[i]));
	}
	if(ans==0x7f7f7f) cout<<"-1";
	else cout<<ans;
	return 0;
}

```

---

## 作者：Mistybranch (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF978D)

题目大概意思是：给你一组数，对每个数有三个操作：$+1$，$-1$，以及不变，判断能否通过操作将这组数变成等差数列，若能则输出最小改变次数，若不行则输出 $-1$。

首先我们要了解等差数列，我们要知道，一个等差数列的首项（$l_1$）和末项（$l_n$）一旦确定，那么这个等差数列的公差必然确定$\left(\dfrac{l_1 + l_n}{n - 1} \right)$，自然就可以确定所有的数。

那么思路就很好确定了：

- 当 $n$ 为 $1$ 或 $2$ 时，一定是等差数列，直接输出 $0$。

```cpp
if (n <= 2) {
	cout << 0 << endl;
	return 0;
}
```

- 剩下的情况时，对于给定的数列，枚举首项和末项的值（因为每个数最多有 $3$ 种操作情况，两个数枚举就是 $9$ 种，情况很少的），那么公差就能求出来了，进而能求出当前改变后的整个数列，记为 $b$。

```cpp
for (int i = -1; i <= 1; i++) {
	for (int j = -1; j <= 1; j++) {
		a1 = l[1] + i;
		an = l[n] + j;
		
		if ((an - a1) % (n - 1) != 0) {
			continue;
		}
		
		d = (an - a1) / (n - 1);
		ai = a1;
		cc = abs(i) + abs(j);
	}
}
```

- 在公差是整数的情况下，扫一遍 $a_2$ 到 $a_{n - 1}$，判断 $a_i$ 与 $b_i$ 的差是否在 $-1$ 到 $1$ 之间。

1. 如果 $a_i$ 与 $b_i$ 的差在 $-1$ 到 $1$ 之间，如果$a_i$ 不等于 $b_i$，那么当前操作数 $+1$，否则跳过。

2. 否则，说明这个原数列不能通过给定操作改变成当前枚举的等差数列，直接跳过。

```cpp
for (int k = 2; k < n; k++) {
	ai += d;
	
	if (abs(l[k] - ai) > 1) {
		cc = -1;
		break;
	}
	
	if (ai != l[k]) {
		cc++;
	}
}
```

- 最后刷新结果，让操作数尽可能少（别忘了 $a_1$ 和 $a_n$ 的操作）。

```cpp
if (cc >= 0) {
	res = min(res, cc);
}
```

完整代码：
```cpp


#include <bits/stdc++.h>

using namespace std;

int n, l[100009], res = 100009; 

int main () {
	int a1, an, ai, d, cc;
	
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", &l[i]);
	}
	
	if (n <= 2) {
		cout << 0 << endl;
		return 0;
	}
	
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			a1 = l[1] + i;
			an = l[n] + j;
			
			if ((an - a1) % (n - 1) != 0) {
				continue;
			}
			
			d = (an - a1) / (n - 1);
			ai = a1;
			cc = abs(i) + abs(j);
			
			for (int k = 2; k < n; k++) {
				ai += d;
				
				if (abs(l[k] - ai) > 1) {
					cc = -1;
					break;
				}
				
				if (ai != l[k]) {
					cc++;
				}
			}
			
			if (cc >= 0) {
				res = min(res, cc);
			}
		}
	}
	
	if (res == 100009) {
		printf("-1\n");
	}
	
	else {
		printf("%d\n", res);
	}
	
	return 0;
}
```


---

## 作者：追梦的黑旋风 (赞：0)

**很多dalao都发了比较难~~懂~~的题解**

来一篇蒟蒻适配题解叭，~~刚学完语言也能轻松听懂哦！~~

### 题目大意
给定一个数列，不能改变数列的顺序，可以给每一位加一或减一或不变；使这个数列成为一个**等差数列**；

### 大体思路
那么就很简单了，既然只能加一，减一，不变；

那么就可以知道第一项改变只有三种可能了，也就是
数组的第一项加一，减一或者不变

同理数组的第二项也有三种可能，一共九种可能，也就可以用第二项减去第一项计算出9种**公差**；

遍历每一位看它的下一位和这一位的差是否为**公差**加一减一或不变；是则对下一位做对应的操作；如果这三个都不是，那就不成立，把当前情况的答案改成**最大值**

最后遍历答案数组得到最小值就可以啦qwq

下面是蒟蒻的代码，码风清奇，不喜勿喷：
```cpp
#include<cstdio>
#include<stdlib.h>
#include<cmath>
using namespace std;
#define ll long long
ll min(ll a,ll b){
	if(a<b){
		return a;
	}else{
		return b;
	}
}
int n;
ll a[100010];//存原数组 
ll b[100010];//更改的数组 
ll ans[4][4];//答案数组 
int d;
ll real=1e9;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int k1=-1;k1<=1;k1++){
		for(int k2=-1;k2<=1;k2++){
			for(int i=1;i<=n;i++){
				b[i]=a[i];//因为直接对a更改下一次循环就凉了所以我们对b数组进行修改； 
			}
			ans[k1+2][k2+2]=abs(k1)+abs(k2);//更改了第一位，ans++，更改了第二位，ans++ 
			b[1]+=k1;
			b[2]+=k2;
			d=b[2]-b[1];
			for(int i=1;i<n;i++){
				if(b[i+1]-1==d+b[i]){
					b[i+1]--;
					ans[k1+2][k2+2]++;
				}else if(b[i+1]+1==d+b[i]){
					b[i+1]++;
					ans[k1+2][k2+2]++;
				}else if(b[i+1]==d+b[i]){
					//啥都不干
				}else{
					ans[k1+2][k2+2]=1e9;//赋成最大值 
				}
			}
		}
	}
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			real=min(real,ans[i][j]);//比大小qwq 
		}
	}
	if(real>=1e9){
		printf("-1");
		return 0;
	}else{
		printf("%lld",real);
	}
	return 0;
}








//made by 追梦的黑旋风 
```
管理大大手下留情qwq第五次交了

---

## 作者：世末OIer (赞：0)

题解:如果我们知道了改动后的头两个数的值，就知道了公差，那么整个数组就知道了。所以说我们只要枚举前两个数的改动值，一个一个往后推，推道差大于1的就是不可以，否则就是可以

```cpp
int n;
int b[100005],t[100005];
stack<int> st,nw;
int D;
int ans=1234567;
inline void solve(int x,int ch){                   //一个一个判断
//	for(int i=0;i<n;i++) cout<<b[i]<<' ';
//	cout<<endl;
	int i,j;
	D=b[1]-b[0];
	for(i=0;i<n;i++) t[i]=b[i];
	int res=0;
	bool ok=1;
	for(i=1;i<n;i++){
		if(t[i]-t[i-1]==D) continue;
		else if(t[i]-t[i-1]==D+1) t[i]--,res++;
		else if(t[i]-t[i-1]==D-1) t[i]++,res++;
		else{
			ok=0;
			break;
		}
	}
	if(ok) ans=min(ans,res+ch);
}
int main(){
	cin>>n;
	int i,j;
	for(i=0;i<n;i++) cin>>b[i];
	if(n<3){
		cout<<0<<endl;
		return 0;
	}
	solve(b[1]-b[0],0);                    //暴力枚举
	b[1]++;
	solve(b[1]-b[0],1);
	b[1]-=2;
	solve(b[1]-b[0],1);
	b[1]++;
	b[0]++;
	solve(b[1]-b[0],1);
	b[0]-=2;
	solve(b[1]-b[0],1);
	b[0]++;
	b[0]++;
	b[1]++;
	solve(b[1]-b[0],2);
	b[0]-=2;
	b[1]-=2;
	solve(b[1]-b[0],2);
	b[0]+=2;
	solve(b[1]-b[0],2);
	b[0]-=2;
	b[1]+=2;
	solve(b[1]-b[0],2);
	if(ans==1234567) cout<<-1<<endl;
	else cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Ak_hjc_using (赞：0)

### 思路：
- 特判
  
  首先可以知道，在 $n \le 2$ 时，一定能够构造出等差数列，所以判断 $n$ 是否小于等于 $2$，如果是就直接输出 $0$。
- 其他情况
  
  等差数列有一个特点，就是知道首项和公差就可以直接求出整个数列，故本题的方法就是枚举首项和第二项，算出公差，求出最小的次数，这也非常好枚举，首项的数量有三个，分别是 `a[1]`，`a[1] - 1`，`a[1] + 1`，而公差一共有九个，分别枚举即可。
### 代码:
本题思路较为简单，只是一道非常简单的模拟即可，故不放代码。

---

