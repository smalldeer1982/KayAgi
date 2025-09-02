# Jeff and Periods

## 题目描述

One day Jeff got hold of an integer sequence $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ of length $ n $ . The boy immediately decided to analyze the sequence. For that, he needs to find all values of $ x $ , for which these conditions hold:

- $ x $ occurs in sequence $ a $ .
- Consider all positions of numbers $ x $ in the sequence $ a $ (such $ i $ , that $ a_{i}=x $ ). These numbers, sorted in the increasing order, must form an arithmetic progression.

Help Jeff, find all $ x $ that meet the problem conditions.

## 说明/提示

In the first test $ 2 $ occurs exactly once in the sequence, ergo $ p_{2}=0 $ .

## 样例 #1

### 输入

```
1
2
```

### 输出

```
1
2 0
```

## 样例 #2

### 输入

```
8
1 2 1 3 1 2 1 5
```

### 输出

```
4
1 2
2 4
3 0
5 0
```

# 题解

## 作者：PR_CYJ (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/CF352B)

# 思路
对于每个数组中的每个数 $ a_i $，用三个数组分别记录 $ a_i $ **上一次**出现的位置，$ a_i $ 出现位置的**下标**是否构成等差数列，以及以 $ a_i $ 出现位置的下标构成的等差数列的**公差**。

然后 $ O(n) $ 扫一遍数组，判断此次下标与上次下标的差与公差是否相等，注意**特判第一次与第二次**出现。 

最后再 $ O(n) $ 扫两遍数组，第一次求答案总数，第二次分别输出每个 $ a_i $ 和对应公差。

具体实现见代码，如有不懂请看注释。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,ans=0,m=0;
	cin>>n;
	int a[n+10]={};
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		m=max(m,a[i]);//求最大数 
	}
	m+=10;//避免数组越界 
	int lt[m]={},d[m]={};
	bool f[m]={};//三个数组的详细含义请看思路部分 
	for(int i=1;i<=n;i++)
	{
		if (lt[a[i]]!=0)//特判第一次出现的情况（即上一次出现位置为 0） 
		{
			if (d[a[i]]==0)//特判第二次出现的情况（即公差为 0） 
				d[a[i]]=i-lt[a[i]];
			else if (i-lt[a[i]]!=d[a[i]])
				f[a[i]]=true;
		}
		lt[a[i]]=i;//更新上一次出现的位置 
	}
	for(int i=1;i<m;i++)//注意是i<m，否则会数组越界 
		if (lt[i]!=0&&!f[i])//lt数组也可用于判断该数是否出现 
			ans++;
	cout<<ans<<endl;
	for(int i=1;i<m;i++)
		if (lt[i]!=0&&!f[i])
			cout<<i<<" "<<d[i]<<endl;//输出答案 
}
```


---

## 作者：The_jester_from_Lst (赞：2)

稍微动一点脑筋的模拟。

自然我们首先想到暴力模拟题意。顺序枚举数组 $a$，若当前的 $a_i$ 没有被搜过我们往后搜索，记 $t$ 为上一次 $a_i$ 出现的位置，$v$ 为公差，设当前搜到第 $j$ 位。每搜到一个  $a_j=a_i$，我们把 $j$ 标记。每次用 $a_j-a_t$ 计算 $v$。一遍搜下来 $v$ 始终不变则我们认为该 $a_i$ 是一个可行解，将 $a_i$ 与 $v$ 记录进结构体 $ans$ 即可。

但是这样的时间复杂度为 $O(n^2)$，虽然理论上跑不满（有标记），但实测仍然会超时。我们考虑优化搜索部分。易得算法瓶颈在于查找 $a_j=a_i$。

既然如此我们不是每一次进行搜索，而是另开数组 $vis$ 记录每一个 $a_i$ 上次出现的位置，在遍历中以 $vis_{a_i}=i$ 的形式维护，开数组 $cha$ 记录每一个 $a_i$ 的公差，在遍历中以 $cha_{a_i}=i-vis_{a_i}$ 的形式维护，这下只要每次计算当前算出来的差值是否与原有的 $cha_{a_i}$ 相等即可，一旦不相等就记 $cha_{a_i}=-1$，最后遍历 $a$ 数组把 $cha_{a_i} \ne -1$ 的 $a_i$ 与 $cha_{a_i}$ 记入结构体 $ans$，然后对 $ans$ 排序，最后输出 $ans$ 中的所有值即可。

容易发现时间复杂度降至排序的 $O(n\log{n})$，可以通过此题。

附上代码（代码中还有一些小细节）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
	int jya=0,ysc=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')ysc=-1;ch=getchar();}
	while(isdigit(ch)){jya=jya*10+(ch-'0');ch=getchar();}
	return jya*ysc;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)wr(x/10);
	putchar(x%10+'0');
}
struct node{
	int x,y;
}ans[100086];
int n,a[100086],b[100086],s,vis[100086],cha[100086];
inline bool cmp(node x,node y){
	return x.x<y.x;
}
signed main(){
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<=n;++i){
		if(cha[a[i]]==-1)continue;//已经排除了就不要搜了
		if(vis[a[i]]==0){
			vis[a[i]]=i;
			continue;
		}//特判第一次访问
		if(cha[a[i]]==0)cha[a[i]]=i-vis[a[i]];//特判
		else {
			if(cha[a[i]]!=i-vis[a[i]]){
				cha[a[i]]=-1;
				continue;
			}
		}
		vis[a[i]]=i;
	}
	for(int i=1;i<=n;++i){
		if(cha[a[i]]!=-1){
			ans[++s].x=a[i];
			ans[s].y=cha[a[i]];
			cha[a[i]]=-1;//去重
		}
	}
	sort(ans+1,ans+1+s,cmp);
	wr(s);putchar('\n');
	for(int i=1;i<=s;++i){
		wr(ans[i].x);
		putchar(' ');
		wr(ans[i].y);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：HUANGRUI11 (赞：1)

简单的模拟题。

### 解法

题意是找出序列 $a$ 中若干个每次出现都距离相同距离的数，并且输出要按照从小到大来排列，不难想到要用桶排来解决。

用 $v$ 数组记录每个数最新位置，用 $f$ 数组记录相同数之间间隔的距离，如果之前记录的值与 $i-v _ {a _ {i}}$ 不相等，则说明此数不符合等差，在 $f$ 数组中用 $-1$ 标记。
最后再循环查找 $f _ {a _ {i}}$ 是否为 $-1$。如果不是，则说明符合条件，用数组存储排序后进行输出。


### 部分代码
```cpp
	for(int i=1;i<=n;i++)
	cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(f[a[i]]==-1) continue;//剪枝
		if(v[a[i]]==0) v[a[i]]=i;
		if(f[a[i]]==0) f[a[i]]=i-v[a[i]];//记录距离
		else
		{
			if(f[a[i]]!=i-v[a[i]]) f[a[i]]=-1;//标记
		}
		v[a[i]]=i;//更新位置
	}
	for(int i=1;i<=n;++i)
	{
		if(f[a[i]]!=-1)
		{
			sum[++cnt].x=a[i],sum[cnt].y=f[a[i]];
			f[a[i]]=-1;//以免重复输出
		}
	}
	sort(sum+1,sum+cnt+1,cmp);//快排（函数我就不写了）
```

完结散花~~~~

---

## 作者：hcy1117 (赞：1)

# 题目
题意很清楚自己去看[题目传送门](https://www.luogu.com.cn/problem/CF352B)。
# 思路
看到数据范围 $n \le 100000$ 可以直接否掉暴力，于是就想怎么优化，多动动脑可以想到。

- $pre_{i}$ 维护数字 $i$ 在 $a$ 中上一次出现的位置，维护这个是为了计算公差。
- $num_{i}$ 维护数字 $i$ 在 $a$ 中出现位置所构成的等差序列 $b$ 的公差，如果不为等差序列 $num$ 就等于负一。

看到这应该有思路了吧，但还需要注意的是数字 $i$ 在 $a$ 中第一次出现时需要特殊处理。处理很简单易懂代码中会体现。

还有不懂的可以参考注释和代码。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005],pre[100005],num[100005];//前面提到过，不记得的话返回去看看 
bool f[100005];//用来去重 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		int x=i-pre[a[i]];//计算公差 
		if(pre[a[i]]==0)x=0; //特殊处理 
		if(num[a[i]]!=-1&&num[a[i]]!=x)//与之前算出的公差不相等 
		{
			if(num[a[i]]==0)num[a[i]]=x;//第一次 
			else num[a[i]]=-1;//不是等差序列 
		}
		pre[a[i]]=i;//更新位置 
	}
	//f数组的用处就是因为数字x可能在a中出现多次但只能记一次，所以要去重 
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(num[a[i]]!=-1&&!f[a[i]])
		{
			++cnt;
			f[a[i]]=1;
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=100000;i++)
	{
		if(f[i]==1)
		{
			cout<<i<<" "<<num[i]<<endl;
		}
	}
}
```
还有不懂得就再仔细看看，也欢迎来问。

---

## 作者：Eason_cyx (赞：1)

观察到 $1 \le a_i \le 10^5$，所以可以将每个 $a_i$ 在输入时用数组记录一些信息。

我们使用 $typ_{i}$ 维护**数** $i$ 的状态，分为以下几种：

- $-1$：该数未在 $a$ 数组中出现过。

- $0$：该数在 $a$ 数组中出现过，且满足题目中的要求。

- $1$：该数在 $a$ 数组中出现过，且不满足题目中的要求。

最后统计 $0$ 的个数输出即可。

如何判断是否满足题目中的要求？对于每一个**数** $i$，建立一个 `vector` 可变长数组记录数组中所有出现 $i$ 的位置。当新增一个位置后，判断最后一个元素和倒数第二个元素的差是否与倒数第二个元素和倒数第三个元素的差相等。如果不相等，则这个数 $i$ 不满足要求，将 $typ_i$ 标记为 $1$ 即可。整个数组输入完毕后，剩下的 $0$ 即为满足条件的数，输出即可。

坑：注意当一个数在数组中仅出现一次时，你的第二个数应当输出 `0`。

[Accepted,528 ms,2000 KB](https://codeforces.com/contest/352/submission/260252899)

---

## 作者：wangqinyan (赞：1)

这题思路与代码实现其实都很简单。

# **题目思路**

这道题其实就是一道比较简单的贪心。大致的题意就是在一个序列中，找出每个出现过的数，如果这个出现过的数的下标可以构成一个等差数列的话，就将其输出。首先，最暴力的方法莫过于分别暴力找出每个出现过的数，判断这些数的下标是否可以构成等差数列。但是很明显，这样会超时。再看这题的数据范围，可以用桶来做。因此，我们可以考虑这样一个思路。先用一个结构体数组来分别存储为 $x$ 的数的最大下标和公差。每输入一个数时，就判断能否与之前出现的同一个数构成等差数列。如果不行，做上标记，不作为答案输出。如果可以，则更新结构体数组中为 $x$ 的最大下标。最后，再对答案进行统计。这样，这道题就做好了。具体可见代码。

# **注意点**

取公差时不需要取绝对值，因为处理时，公差是由后来找到的数的下标减去先前存储的最大下标所求得的。因此，不存在后面的减去前面的为负数的情况。

# **代码**
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long w;
	long long v;
}a[101000];
long long n,x,maxn,s;
bool p[100100];
int main()
{
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		maxn=max(maxn,x);
		if(p[x])continue;
		if(a[x].w!=0)
		{
			if(a[x].v==0)a[x].v=i-a[x].w;
			if(i-a[x].w!=a[x].v)p[x]=1;
			else
			a[x].w=i;
		}
		else a[x].w=i;
	}
	for(int i=1;i<=maxn;i++)
	if(a[i].w!=0&&p[i]!=1)s++;
	cout<<s<<endl;
	for(int i=1;i<=maxn;i++)
	if(a[i].w!=0&&p[i]!=1)cout<<i<<" "<<a[i].v<<endl;
//    fclose(stdin);
//    fclose(stdout);
	return 0;
}

```
感谢观看！

---

## 作者：No0Chenquanlin (赞：1)

对于我这种蒟蒻都能一遍  AC  的水题嘛，我要不然~~放个代码就跑吧~~~~~

算了，还是老老实实分析题意。

对于 如此~~小的可怕~~的数据范围，显然我们可以开一个结构体，分别存储**每个元素**在数组里出现的上一个数**的位置**，等差数列的**差**，这个数出现的**次数**和当前成立与否。
 
然后 $O(n)$     扫一遍，特判一下某个数第一次和第二次出现一定成立就好。

最后   $O(n)$   扫两遍，分别统计成立数字的个数，然后再输出。


具体实现看代码，自以为注释挺详细的。

```cpp
#include<iostream>
using namespace std;
int n, maxn;
int a[100005];
struct Node{
	int last;//上一个数是几
	int cha;//等差数列的差是几
	int num;//这个数出现了几次 
	bool flag = true;//这个数成立与否 
}ans[100005];
int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		maxn = max(maxn, a[i]);//找到最大的a[i] 
	}
	for(int i = 1; i <= n; i++){
		if(ans[a[i]].flag == false)//在之前的判断中已经不成立了
			continue;//直接退出 
		else if(ans[a[i]].num == 0)//这个数是第一次出现
			ans[a[i]].last = i,//起始位置是i
			ans[a[i]].num++,
			ans[a[i]].cha = 0; 
		else if(ans[a[i]].num == 1){//有一个数了，是第二次出现
			ans[a[i]].cha = i - ans[a[i]].last,//标记差值 
			ans[a[i]].last = i,//标记元素 
			ans[a[i]].num++;//个数++ 
		}
		else{//出现过多次了 
			if(i - ans[a[i]].last != ans[a[i]].cha)//不成立 
				ans[a[i]].flag = false;//此时不用做别的处理，因为!flag后都没有意义了 
			else
				ans[a[i]].last = i,//继续更新 
				ans[a[i]].num++;
		}
	}
	int cnt = 0;
	for(int i = 1; i <= maxn; i++)
		if(ans[i].num && ans[i].flag)
			cnt++;
	printf("%d\n",cnt);
	for(int i = 1; i <= maxn; i++)
		if(ans[i].num && ans[i].flag)
			printf("%d %d\n", i, ans[i].cha);
	return 0;
}
```

~~不是，你分析思路跟没分析一样~~


---

## 作者：Zaku (赞：1)

### 题意：
这里对样例 2 作出解释：
```
8
1 2 1 3 1 2 1 5
```
- $1$ 的下标分别为 $1$，$3$，$5$，$7$，成等差数列。所以输出数列的公差 $2$；
- $2$ 的下标分别为 $2$，$6$，成等差数列，所以输出数列的公差 $4$；
- $3$ 和 $5$ 只出现了一次，所以输出 $0$。

再看一组数据：
```
6
1 1 4 5 1 4
```
- $1$ 的下标分别为 $1$，$2$，$5$，不成等差数列，所以不输出。
- $4$ 的下标分别为 $3$，$6$，成等差数列，所以输出数列的公差 $3$；
- $5$ 只出现了一次，所以输出 $0$。

懂了吗？
### 解法：
~~膜你~~模拟

假设 $i$ 是当前数字，用 $c_i$ 记录 $i$ 的上一位置，$b_i$ 记录 $c_i$ 与 $i$ 的距离，然后与之前的距离进行比较，如果有一次不等，那么这个数就不能构成等差数列，也就不输出该数。否则，输出该数与其等差数列的公差。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],b[N],c[N];//b数组记录公差 c[a[i]]记录上一个a[i]的位置 
bool vis[N];//遍历数组时用 
map<int,int> t;
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        t[a[i]]++;
        if(t[a[i]]==1)c[a[i]]=i;//第一次出现 记录当前位置 
        if(t[a[i]]==2){
            b[a[i]]=i-c[a[i]];//计算与上一次位置的差，录入b数组
            c[a[i]]=i;//刷新c数组 
        }else if(t[a[i]]>2){//已多次出现
            if((i-c[a[i]])!=b[a[i]])//判断公差是否一致 
                b[a[i]]=0;//不一致，那么a[i]不构成等差序列 
            else c[a[i]]=i;//否则继续刷新c数组 
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(vis[a[i]])continue;
    	vis[a[i]]=1;
        if(t[a[i]]==1)cnt++;
        else if(b[a[i]]!=0)cnt++;
    }//查找等差数列个数，相信大家看得懂，就不解释了 
    cout<<cnt<<endl;
    sort(a+1,a+1+n);//排序，因为样例要求从小到大输出 
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++){
        if(vis[a[i]]) continue;
    	vis[a[i]]=1;
        if(t[a[i]]==1)cout<<a[i]<<" "<<"0"<<endl;
        else if(b[a[i]]>0)cout<<a[i]<<" "<<b[a[i]]<<endl;
    }//输出，大家肯定也看得懂 
    return 0;
}
```


---

## 作者：Red_Ghost (赞：1)

## 题意翻译：

给你一个数列，对于里面的每一个数，如果重复的它们的下标是等差数列，则为所需要的答案。最后输出这些“所需要的数”的数量和这些“所需要的数”。

## 思路分析：
将所有出现过的数字都装到 `vector` 里储存下标，随后对于每一个出现过的数字进行判断：

1. 如果这个数只出现过一次，则直接将这个数存到答案数组中，它的差值为 $0$ ;

2. 如果这个数出现过多次，则先求出前两个位置间的差值，随后计算每两个位置间的差值，如与预算的差值不同，那么这个数就不是需求的数。如果所有位置间的差值和预算的差值都相同，则也将这个数存到答案数组中，它的差值即为预算的差值。

## Code：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
vector <int> pos[100010];//位置数组
int n,ans,maxx,minn=0x3f3f3f3f,a[100010];
struct node{
	int chaz,num;
} ansa[100010];//答案数组
int main() {
	cin>>n;
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		maxx=max(maxx,a[i]);
		minn=min(minn,a[i]);//优化扫的时间，防止超时
		pos[a[i]].push_back(i);
	}
	for (int i=minn;i<=maxx;i++) {
		bool flag=true;
		if (pos[i].size()==0) continue;//跳过没出现的数字
		if (pos[i].size()==1) {
			ansa[++ans].num=i,ansa[ans].chaz=0;
			continue;
		}//判断1
		int cha=pos[i][1]-pos[i][0];
		for (int j=2;j<pos[i].size();j++) if (pos[i][j]-pos[i][j-1]!=cha) {
			flag=false;
			break;
		}
		if (flag) ansa[++ans].num=i,ansa[ans].chaz=cha;//判断2
	}
	cout<<ans<<endl;
	for (int i=1;i<=ans;i++) printf("%d %d\n",ansa[i].num,ansa[i].chaz);
	return 0;
}
```


---

## 作者：jixiyue114514 (赞：0)

## 题目大意
给一个长度为 $n$ 的序列，找出所有的 $x$，满足：

- $x$ 在序列 $a$ 中出现。
- $x$ 在序列 $a$ 中所有出现的位置组成序列 $b$，使这个序列 $b$ 成为等差数列。

## 题解思路
先输入序列 $a$，然后找到这个序列中的最大值和最小值，$x$ 的取值范围就是最小值到最大值，之后判断是否组成了等差数列，但是要注意**当 $b$ 序列长度为 $1$ 的时候公差要输出为 $0$，当 $b$ 序列长度为 $0$ 的时候跳过这个 $x$。**

根据我的思路走，可以成功 AC。

![](https://cdn.luogu.com.cn/upload/image_hosting/gu8o0pvt.png)

---

## 作者：lostxxx (赞：0)

# 题目分析

我们观察发现，$ 1 \le a_i \le 10^5 $ ，于是我们可以先扫一遍 $a$ 数组，然后每次将 $i$ 放进编号为 $a_i$ 的数组中，这是为了获得同一个元素的下标。

随后，我们从 $1$ 到 $10^5$ 遍历每一个可能出现的元素，然后判断当前元素的所有下标是否构成一个等差数列，注意特判长度为 $1$ 和长度为 $2$ 的数列。

代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
ll a[200100];
vector<ll>g[200100];
unordered_map<ll,ll>ma;
ll ans1[200100],ans2[200100],k=1;
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        g[a[i]].push_back(i);
    }
    for (int i=1;i<=1e5;i++){
        if (g[i].size()==0)
            continue;
        bool flag=1;
        ll times;
        if (g[i].size()==1)
            times=0;
        else if (g[i].size()==2){
            times=g[i][1]-g[i][0];
        }else{
            times=g[i][1]-g[i][0];
            for (int j=2;j<g[i].size();j++){
                if (g[i][j]-g[i][j-1]!=times){
                    flag=0;
                    break;
                }
            }
        }
        if (flag){
            ans1[k]=i;
            ans2[k++]=times;
        }
    }
    cout<<k-1<<endl;
    for (int i=1;i<k;i++)
        cout<<ans1[i]<<" "<<ans2[i]<<endl;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

用一个桶记录 $a_i$ 最后一次出现的位置，再用数组 $d$ 记录数字 $a_i$ 出现位置的公差，最后特判一下数字第一次出现和第二次出现时的情况（数字 $i$ 第二次出现时才能求出公差）。

时间复杂度：$O(n)$。

**注意：** 数字只出现一次也要计入答案。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
int arr[100010] ;
int tong[100010];
int d[100010] ;
bool ok[100010] ;
int maxn , n ;
signed main (){
	cin >> n;
	maxn = -0x3f3f3f3f ;
	for (int i = 1 ; i <= n ;i++){
		cin >> arr[i] ;
		maxn = max ( maxn , arr[i] ) ;
	}
	for (int i = 1 ; i <= n ;i++){
		if ( tong[arr[i]] ){
			if ( !d[arr[i]] ){
				d[arr[i]] = ( i - tong[arr[i]] ) ;//更新公差
			}else if ( i - tong[arr[i]] - 1 + 1 - 1 + 1 != d[arr[i]] ){
				ok[arr[i]] = 1 ;//不符合题目要求
			}
		}
		tong[arr[i]] = i ; 
	}
	int cnt = 0 ;
	for ( int i = 1 ; i <= maxn  ; i++ ){
		if ( ok[i] == 0 && tong[i] != 0){
			++cnt ;
		}
	}
	cout << cnt << '\n' ;
	for ( int i = 1 ; i <= maxn  ; i++ ){
		if ( ok[i] == 0 && tong[i] != 0){
			cout << i << " " << d[i] << '\n' ;
		}
	}
	return 0 ;
}
```

---

## 作者：Qiering (赞：0)

# CF352B Jeff and Periods
## 题目描述
[传送门](http://www.luogu.org/)
## 题目分析
用 $A$ 表示原序列。

对于每个 $x(x \in A)$ 记录：

* $vis_x$ 表示 $x$ 是否出现过。
* $id_{x,y}$ 表示 $x$ 在 $A$ 中出现的第 $y$ 个下标。

记录过程复杂度显然 $O(n)$。

对于每个 $x$ 检查 $id_x$ 是否构成等差数列。

每个下标都被记入 $id_x$ 一次，所以检查过程复杂度为 $O(n)$。

总体复杂度 $O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
#define re register
const int N=1e5+5;
int n,m;
vector<int> id[N];
bool vis[N];
int cnt;
int ansx[N],anscha[N];
signed main()
{
	IOS;
	cin>>n;
	for(re int i=1;i<=n;++i)//记录
	{
		int x;
		cin>>x;
		vis[x]=1;
		id[x].push_back(i);
		m=max(m,x);
	}
	for(re int i=1;i<=m;++i)//检查
	{
		if(!vis[i]) continue;
		bool flag=1;
		if(id[i].size()==1)//注意特判
		{
			ansx[++cnt]=i;
			anscha[cnt]=0;
			continue;
		}
		else if(id[i].size()==2)//注意特判
		{
			ansx[++cnt]=i;
			anscha[cnt]=id[i][1]-id[i][0];
			continue;
		}
		int k=id[i][1]-id[i][0];//公差 
		for(re int j=2;j<id[i].size();++j)
		{
			if(id[i][j]-id[i][j-1]!=k)//判断等差数列
			{
				flag=0;
				break;
			}
		}
		if(flag)
		{
			ansx[++cnt]=i;
			anscha[cnt]=k;
		}
	}
	cout<<cnt<<'\n';
	for(re int i=1;i<=cnt;++i)
	{
		cout<<ansx[i]<<' '<<anscha[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：very_easy (赞：0)

## 题意

这道题题目看上去花里胡哨，其实就是道水题。

题目大意就是说将每个相同数出现的下标（从 $1$ 开始）统计一下，如果这些下标所构成的数列是等差数列那就输出这个重复出现的数以及等差数列的公差。

是不是没懂？

举个例子，如样例二：

```
8
1 2 1 3 1 2 1 5
```

$1$ 出现了三次，分别在下标 $1,3,5,7$ 的位置上，而 $1,3,5,7$ 是一个等差数列，公差为 $2$，因此应该输出 $1$ $2$，其中 $1$ 是这个数， $2$ 是等差数列的公差。

然后是 $2$，它出现了两次，分别在下标 $2,6$ 的位置上，$2,6$ 也是一个等差数列，公差为 $4$，因此输出 $2,4$。

再看 $3$ 和 $5$，这两个数只出现了一次，所以直接输出 $3,0$ 和 $5,0$。

## 思路

本题由于要考虑重复出现的数字，所以大部分大佬直接开始用桶做，但是不要忘了我们学的可是一个面向对象的语言，可以使用 `STL` 来做啊。

首先是数字下标的存储方面，由于只需要考虑下标，没必要记录每一个数字，所以不需要再额外开数组，存储方式有点像邻接表的存储。

```
int n;
cin>>n;
for(int i=1;i<=n;i++){//下标从1开始！！！ 
	int x;
	cin>>x;
	v[x].push_back(i);//记录数值的下标 
}
```

然后就是对于等差数列的判断了。

我们可以先计算第一个数和第二个数之间的差，记作 $d$，然后扫描数组，如果相邻的两个数之间的差都等于 $d$ 的话那就说明是一个等差数组。

```
for(int i=0;i<N;i++){
	if(v[i].empty()) continue;
	if(v[i].size()==1){//特判只出现一次的情况 
		//记录答案 
		continue;
	}
	//下面可能有点绕，可以把v[i]看成一个整体来阅读 
	int d=v[i][1]-v[i][0];
	bool flag=false;
	for(int j=1;j<v[i].size()-1;j++){
		if(v[i][j+1]-v[i][j]!=d){//不符合情况 
			flag=true;
			break;
		}
	}
	if(flag==false){
		//记录答案 
	}
}
```

就差最后一步了，那就是记录答案了。

我们可以发现，答案包括两个部分，数值与公差，既然是两个部分捆绑在一起，很容易想到结构体数组，~~但是不要忘了我们学的可是一个面向对象的语言，可以使用 `STL` 来做啊。~~

可以考虑开一个结构体类型的队列来进行存储，由于队列是一种先进先出的容器，因此我们无需再次考虑数据有序的问题。

```
for(int i=0;i<N;i++){
	if(v[i].empty()) continue;
	if(v[i].size()==1){//特判只出现一次的情况 
		ans.push({i,0});//直接入队 
		continue;
	}
	//下面可能有点绕，可以把v[i]看成一个整体来阅读 
	int d=v[i][1]-v[i][0];
	bool flag=false;
	for(int j=1;j<v[i].size()-1;j++){
		if(v[i][j+1]-v[i][j]!=d){//不符合情况 
			flag=true;
			break;
		}
	}
	if(flag==false){
		ans.push({i,d});//如果满足情况，直接入队 
	}
}
```

最后我们会发现，答案的个数不就是队列的长度吗，所以我们可以直接输出队列长度和队中元素。

```
cout<<ans.size()<<endl;
while(!ans.empty()){
	cout<<ans.front().val<<" "<<ans.front().d<<endl;//val为数值，d是公差 
	ans.pop();
}
```

## 完整代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct node{//结构体 
	int val,d;//val为数值，d是公差 
}; 
vector<int> v[N];
queue<node> ans; 
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){//下标从1开始！！！ 
		int x;
		cin>>x;
		v[x].push_back(i);//记录数值的下标 
	}
	for(int i=0;i<N;i++){
		if(v[i].empty()) continue;
		if(v[i].size()==1){//特判只出现一次的情况 
			ans.push({i,0});//直接入队 
			continue;
		}
		//下面可能有点绕，可以把v[i]看成一个整体来阅读 
		int d=v[i][1]-v[i][0];
		bool flag=false;
		for(int j=1;j<v[i].size()-1;j++){
			if(v[i][j+1]-v[i][j]!=d){//不符合情况 
				flag=true;
				break;
			}
		}
		if(flag==false){
			ans.push({i,d});//如果满足情况，直接入队 
		}
	}
	cout<<ans.size()<<endl;
	while(!ans.empty()){
		cout<<ans.front().val<<" "<<ans.front().d<<endl;
		ans.pop();
	}
	return 0;
}

```


---

## 作者：DiDi123 (赞：0)

# 一、大意
本题要求找出一个数列 $a$ 中有多少个数是按照不变的间隔分布的（即分布位置成等差数列）。

# 二、分析

我们可以观察一下 $a_i$ 的范围，发现非常的小（$a_i\leq 10^5$），这是在提醒我们用**桶**的思想。

我们可以建立一个桶，储存每个 $a_i$ 最后一次的出现位置 $p$ 以及 $a_i$ 分布的间隔 $d$。如果发现又进来了一个数 $x$，就用这个数的位置减去上一个 $x$ 的位置为这个 $x$ 与上一个 $x$ 的间隔，然后对比这个间隔与前面储存的间隔是否一致，如果相同，就更新最后一个 $x$ 的位置，否则就标记，以后再也不用 $x$ 这个数了。

还有一些具体的问题，比如有零个 $x$ 和一个 $x$ 时记录的 $d$ 都为 $0$，这些问题可以看下面程序的注释。

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001
int n,cnt,x,maxx;
struct node1
{
	int p=0,d=-1;
}a[MAXN],ans[MAXN]; //这里注意ans的p和a的p意思不同，ans[i].p表示满足要求的数p，a[i].p表示数i在数列中上一个出现位置
// ans[i].d表示ans[i].p以间隔ans[i].d出现；a[i].d表示i以间隔a[i].d出现
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		maxx=max(maxx,x); //maxx表示所有输入的数的上限，加速第25行的扫描操作
		if(a[x].d==-1) //表示x这个数没有出现过，没有间隔
			a[x].p=i,a[x].d=0;
		else if(a[x].d==0) //表示x这个数只出现过一次，没有间隔
			a[x].d=i-a[x].p,a[x].p=i; //注意更新顺序
		else if(i-a[x].p==a[x].d)
			a[x].p=i;
		else a[x].d=-2; //表示x已经与前面的间隔不同，以后x的间隔不重要了
	}
	for(int i=1;i<=maxx;i++) //在a中扫一遍
		if(a[i].d>=0) //说明i出现过且满足要求
			ans[++cnt].p=i,ans[cnt].d=a[i].d;
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
		cout<<ans[i].p<<' '<<ans[i].d<<endl;
}
```


---

## 作者：Novelist_ (赞：0)

# 思路
看到这题的第一秒，我的脑海里就蹦出了暴力模拟。看了一眼数据范围也是直接放弃。再仔细想想，我们完全可以边输入边做。我们将每一个输入的数的上一次出现位置（未出现出现视为 $0$）和下标差值（第一次出现视为 $0$）记录下来，判断是否构成等差数列，如果无法构成就跳过，并且之后这个数再出现就直接跳过。循环结束后再分别开两个循环，一个求答案个数，一个求 $x$ 和公差。

下面是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int Max(const int x,const int y)
{
  return x>y?x:y;//不建议手打，因为我开始时打错了
}
struct k
{
  int last_position,D_value;//上一次出现位置和公差
}a[100002];
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n,i,j,s(0),maxn=INT_MIN,x;//j是习惯性打出，无用
  bool b[100002]={};
  cin>>n;
  for(i=1;i<=n;++i)
  {
    cin>>x;
    maxn=Max(maxn,x);
    if(!b[x])
    {
      if(a[x].last_position)
      {
        if(!a[x].D_value)
		a[x].D_value=i-a[x].last_position;
        if(i-a[x].last_position!=a[x].D_value)
		{
		  b[x]=1;
		  continue;
		}
        else a[x].last_position=i;
      }
      else a[x].last_position=i;
	}
  }
  for(i=1;i<=maxn;++i)
  if(a[i].last_position&&!b[i])++s;//求答案个数
  cout<<s<<'\n';
  for(i=1;i<=maxn;++i)//求x和公差
  if(a[i].last_position&&!b[i])
  cout<<i<<' '<<a[i].D_value<<'\n';//
  return 0;
}
```

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF352B)


这里我主要是采用队列来存储。你可以把这篇题解看作队列教程。

## 什么是队列
队列是一种线性表。画图的话大概长这样(丑陋勿喷)：
![](https://cdn.luogu.com.cn/upload/image_hosting/cd3brs8q.png)

欸，先进来的貌似先出去耶?

所以，队列又叫先进先出表。

正是因为它有这种特性，我才用它来解决问题。

## 队列的建立
有两种方法。STL 和手写数组。

STL 写法：
![](https://cdn.luogu.com.cn/upload/image_hosting/96cmvwpl.png)

手写数组：建立一个数组，在规定首指针、尾指针。不讲。

个人推荐使用 STL。方便。但比较慢。

## 队列操作

1. ```q.push(a);``` 将元素 ``a`` 加入到队列 ``q``;

2. ```q.pop();``` 删除队列 ``q`` 的队首元素；

3. ```q.front()；``` 查询队列 ``q`` 的队首元素；

4. ```q.back()；``` 查询队列 ``q`` 的队尾元素；

5. ```q.size()``` 查询队列 ``q`` 的元素的个数；

6. ```q.empty()；``` 查询队列 ``q ``是否为空；


## 代码

```
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct wqy{//用于最后的输出。
	int sum,cha;//（我不会告诉你wqy是我朋友）
};
queue<int>Q;//这个队列用于存储数字下标
queue<wqy>q;//这个队列用于存储最后输出的各个数
int n,ma=-1,t[100005],ans,a[100005];//初始化
void Enchanted(){//开始
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		++t[a[i]];//统计出现的数字（桶标记）
		ma=max(ma,a[i]);//记录最大的数据
	}
	for(int i=1;i<=ma;++i)
		if(t[i]!=0){//如果这个数在a中出现
			int s=0;
			for(int j=1;j<=n;++j)if(a[j]==i){Q.push(j);++s;}//查找出现次数，并统计下标
			if(s==1){++ans;q.push((wqy){i,0});Q.pop();}//只出现一次，直接加入。不要忘了队列清空
			else{//不然的话
				int first=Q.front(),cha;
				Q.pop();cha=Q.front()-first;
				first=Q.front();Q.pop();//求出公差
				bool flag=true;
				while(!Q.empty()){
				int tmp=Q.front();
				Q.pop();//清空队列的必要操作
				if(tmp-first!=cha)flag=false;//公差不一致就不加入
				first=tmp;//滚雪球
			}
			if(flag){++ans;q.push((wqy){i,cha});}//满足条件就加入输出。
			}
		}
	cout<<ans<<endl;//方案数
	for(int i=1;i<=ans;++i){
		wqy tmp=q.front();//取出队首
		q.pop();//不要忘了清空
		cout<<tmp.sum<<' '<<tmp.cha<<endl；
	}
	exit(0);
}
signed main(){Enchanted();}

```


---

