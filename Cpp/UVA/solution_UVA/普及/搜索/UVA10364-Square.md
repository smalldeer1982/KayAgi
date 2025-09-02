# Square

## 题目描述

给定 $N$ 根木棍，每根木棍的长度为 $x$ 。

尝试用所有的木棍围成一个正方形。

## 样例 #1

### 输入

```
3
4 1 1 1 1
5 10 20 30 40 50
8 1 7 2 6 4 4 3 5```

### 输出

```
yes
no
yes```

# 题解

## 作者：ljw2005 (赞：11)

这题其实就是一个DFS

代码和注释见下
``` cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int m,l,a[25];
bool su[25];//标记有没有选
int dfs(int pos,int len,int b){
	if(b==3) return 1;//如果都构成3边了，那么最后一遍是肯定构成的
	for(int i=pos;i>=0;i--){
		if(!su[i]){//没走过
			su[i]=1;//置为走过
			if(len+a[i]<l){//长度小于边长
				if(dfs(i-1,len+a[i],b)) return 1;
			}
			else{
				if(len+a[i]==l)//正好等于边长
					if(dfs(m-1,0,b+1)) return 1;//边数加1
			}
			su[i]=0;//归为未走
		}
	}
	return 0;
}
int main()
{
	int i,t,sum,maxn;
	scanf("%d",&t);
	while(t--){
		sum=0; 
		scanf("%d",&m);
		for(i=0;i<m;i++){
			scanf("%d",&a[i]);//读入
			sum+=a[i];//算出木棍长度的总和
		}
		l=sum/4;//算出边长
		memset(su,0,sizeof(su));
		sort(a,a+m);
		if(l*4!=sum||m<4||l<a[m-1]) printf("no\n");//如果不能构成正方形或边长小于最大值
		else if(dfs(m-1,0,0)) printf("yes\n");//DFS
		else printf("no\n");//输出完毕
	}
	return 0;
}
```
希望对大家有所帮助(*^▽^*)

---

## 作者：SmallTownKid (赞：9)

dfs+剪枝，这道题和小木棍那道题差不多，有五个剪枝，但其实这道题不需要这么多，不过最好都学一学。

剪枝（1）：用fail记录最近一次尝试拼接的木棍长度，如果这个长度的木棍没法拼上，那么和它一样长的当前也一定没法拼上

剪枝（2）：限制加入的木棍长度是递减的，用last记录上一个选用的木棍，下一步选的时候就不需要考虑比它长的了，因为假如边长是8.先选3再选5和先选5再选3是一样的，会费时间

剪枝（3）：把木棍从长到短排序，从大往小搜

剪枝（4）：如果当前长度为0，且加入长度为a[i]的木棍不合法，那么直接return false，因为再往后也一定有空的木棍，你这个长度为a[i]就算在这一步不加进去。换了个短的加进去，但也迟早要加进去，边长都是一样的，再往后搜也是加不进去的

剪枝（5）：如果当前长度加上长度为a[i]的木棍正好拼成边长的长度，但之后的递归分支返回false，那直接判断你加入a[i]的这个分支失败，因为可以用贪心来思考，你先把长的用了，给后面留了更多的灵活的短木棍都拼不出来，那先把灵活的短的用了，把不灵活的长木棍留在后面更拼不出来。
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,cnt,sum;
bool vis[101];//记录这个木棍有没有被用过
int a[101];
bool dfs(int stick,int cab,int last)//stick记录当前在拼第几条边,cab记录当前拼的这条边的长度已经是多少了,last记录上一个使用的木棍
{
	if(stick>4)//如果已经拼出了四条边，return就可以了
	return true;
	if(cab==cnt)//如果当前这条边拼好了
	return dfs(stick+1,0,1);//last置为1，从头重新开始搜
	int fail=0;//剪枝（1）
	for(int i=last;i<=m;i++)
	{
		if(vis[i]==0&&a[i]+cab<=cnt&&fail!=a[i])
		 {
            vis[i]=1;
            if(dfs(stick,cab+a[i],i))
            return true;
            vis[i]=0;//回溯
            fail=a[i];//记录最近一次尝试拼接的木棍长度
            if(cab==0||cab+a[i]==cnt)//剪枝（4）和（5）
            return false;
        }
	}
	return false;
}
int main()
{
	cin>>n;
	while(n--)
	{
		sum=0;
		cin>>m;
		for(int i=1;i<=m;i++)
		{
			cin>>a[i];
			sum+=a[i];
		}
		sort(a+1,a+1+m);//剪枝（3）
		reverse(a+1,a+1+m);//reverse作用是把数组倒置，1,2,3变成3,2,1,也可以写个cmp加到sort里，都一样。因为我们要从大到小搜，所以要倒置一下
		if(sum%4!=0)//如果不能被4整除，直接no就可以
		{
			cout<<"no"<<endl;
		    continue;
		}
        cnt=sum/4;//算出边长
		memset(vis,0,sizeof(vis));//每一次都要清空vis数组
		if(dfs(1,0,1))
		cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
	return 0;
}

---

## 作者：红尘万李 (赞：7)

# UVA10364 Square 题解
[题面传送门](https://www.luogu.com.cn/problem/UVA10364)

------------
## **关于提交 UVA 的题......**
**输出问题**一定要注意！要严格控制空格、换行等字符与题意和样例完全相同。我按照样例，没有输出最后一个换行，得到了 [WA](https://www.luogu.com.cn/record/156696168)；而当我**仅改变输出部分**，使之输出最后一个换行时便得到了 [AC](https://www.luogu.com.cn/record/156696403)。~~希望输出样例能加个换行......~~

------------
## 好了，现在切入正题
首先，我们在输入时就可以算出所有的边长和，并储存最长木棍的边长。如果总长度和不为 $4$ 的倍数，或者说，这里面最长的木棍的长度大于了要拼的边长，直接输出 ```no```；

其次，进行深度优先搜索，用 ```bool``` 型应该比 ```void``` 型快一点，但两种均可，无伤大雅；

接下来，在进行搜索的过程中，需要用到**可行性剪枝**和**搜索顺序剪枝**。在拼接的过程中，应该分成两种情况进行判断：

1. 当前长度和 $sum$ 小于要拼边长 $l$ 且小木棍没用过。

2. 这根木棍加上去就拼好了一边。

由于一根木棍可能在四条不同的边上得以利用，所以当我们选择了某根木棍后，应该使用标记数组 $b$ 改变当前木棍的状态，在本次搜索后再还原为初始状态，以便以后的搜索能够继续选择这根木棍。

------------

做法其实大同小异，有一些剪枝和特判，让你从 TLE 变成 AC 哦！
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[21],b[21],l,tot;
bool dfs(int k,int sum,int p)//分别是上一根小木棍的编号、当前边已拼长度、第几条边
{
	if(p==4)return true;//剪枝 2：前三边拼好了，到第四边就不用拼了
	for(int i=k+1;i<=n;i++)
	{
		if(sum+a[i]<l&&!b[i])//当前长度和小于要拼边长且小木棍没用过
		{
			b[i]=1;
			if(dfs(i,sum+a[i],p))
				return true;
			b[i]=0;
		}
		if(sum+a[i]==l&&!b[i])//这根木棍加上去就拼好了一边的情况
		{
			b[i]=1;
			if(dfs(0,0,p+1))//这里 k 为 0 是因为我的循环是从 k+1 开始搜的
				return true;
			b[i]=0;
		}
	}
	return false;//记得打这个不然 RE
}
int main()
{
	scanf("%d",&t);
	for(int phi=1;phi<=t;phi++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			b[i]=0;
		tot=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			tot+=a[i];
		}
		sort(a+1,a+n+1);
		reverse(a+1,a+n+1);//剪枝 1：由大到小排序
		l=tot/4;
		if(tot%4||a[1]>l)//特判：如果总长度和不为 4 的倍数，或者这里面最长的木棍的长度大于了要拼的边长，直接输出 no
		{
			printf("no\n");
			continue;
		}
		if(dfs(0,0,1))printf("yes\n");//写成 bool 类型的函数作为判断的条件
		else printf("no\n");
	}
	return 0;
}
```
记得，顶一下！

---

## 作者：Ezis (赞：3)

这道题我们可以用 $dfs$ 的方式来做。

可以先对 $a[1...n]$ 取 $\max$, $\min$ 和 $sum$。

1. 若 $sum \bmod 4$ 不等于 $0$，那么直接输出 $no$。
1. 若 $mx > sum/4$ ，也输出 $no$。
1. 最后判断 $dfs(1,0,a[1])$ 是否为 $true$ 即可。

注意，每次运行前都要初始化！

**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum,mx,mn,n,a[25];
bool vis[25];
bool dfs(int x,int p,int tot){
	if(tot==sum){		//基本情况 
		p++;
		tot=0;
		x=0;
	}
	if(mn+tot>sum)		//剪枝1 
		return false;
	if(p==3)		//有三条了，最后一条肯定符合 
		return true;
	int l=-1e9;
	for(int i=x+1;i<=n;i++)
		if(vis[i]==false&&a[i]!=l){
			vis[i]=true;
			if(dfs(i,p,tot+a[i])==true)		//下一层 
				return true;
			vis[i]=false;		//回溯 
			l=a[i];
		}
	return false;
}
bool cmp(int x,int y){
	return x>y;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		mn=1e9;
		mx=0;
		sum=0;
		memset(vis,false,sizeof(vis));
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			sum+=a[i];				//求和 
			mx=max(mx,a[i]);		//求max 
			mn=min(mn,a[i]);		//求min 
		}
		sort(a+1,a+n+1,cmp);		//把a从大到小排序 
		if(sum%4!=0){ 
			printf("no\n");
			continue;
		}
		sum/=4;
		if(mx>sum){
			printf("no\n");
			continue;
		}
		vis[1]=true;
		if(dfs(1,0,a[1])==true)
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;
}
```


---

## 作者：Fengxiang008 (赞：3)

### 题目分析：

首先，$N \le 5$，且边数是 $2N\times(N+1) \le 60$。在这样的小数据下可以位运算优化。

启发式搜索，设计估价函数 $G(X)$。要求低于真实代价。

下面是一种方法：

对于每一个正方形，删除它的所有边。重复这个操作知道没有正方形，操作的次数就是估价。

然而，仅仅这样不足以过掉这题，还需要优化。

### 判断正方形：
在纸上推导一下，或者直接找规律，可以得到：

如果一条横放的火柴编号为 $X_0$，

$X_0$ 左下方的 $L$ 根火柴分别是：$X_i=X+(2i−1)N+i-1,0 < i < L  $。

那么正方形的左边界确定了，右边界的编号就是左边界加上边长。

预处理出所有的正方形，并且按照从小到大的顺序。

这样在 ```DFS``` 函数里减少了判断正方形的开销。

### 位运算的技巧
用 ```unsigned long long``` 存储一个正方形的边的编号。

利用 ```&，|``` 运算符可以完成判断正方形是否存在，在一个状态上增加边等操作。
##### 具体实现方法:

```cpp
#define Mark(X,K) (X=X|((Ull)1<<((K)-1)))
#define Del(X,K) (X&(~((Ull)1<<((K)-1))))
#define Check(X,K) (X&(1<<((K)-1)))
```

三个宏定义的作用分别是：标记数 $X$ 的第 $K$ 位，删除标记和检查是否有标记。

### 减枝
从预处理的正方形里，挑选最小的完整的一个，枚举删除它的边。
因为前面的正方形已经残缺不全了，那么不必再纠缠,同时因为从小到大的顺序，搜索树的分支会更少。
使用迭代加深。

### 附上部分代码
预处理正方形：下面的代码返回了以X为初始，以K为边长的正方形，并且把正方形的起始边、长度保存下来:

```cpp
Ull Get (int X , int K) 
{
	Ull Ans = 0 ;
	int Dlt = K * ((N << 1) + 1) ;
	for (int i = X ; i < X + K ; ++ i) Mark (Ans , i) , Mark (Ans , Dlt + i) ;
	for (int i = 1 ; i <= K; ++ i) 
      Mark (Ans , X + (2*i-1) * N + i - 1) , Mark (Ans ,X + (2*i-1) * N + i - 1 + K) ;
	return Ans ;
}
```

估价函数：利用位运算从一个状态中拆除整个正方形：

```cpp
int G (Ull X) {
	int Ans = 0 ;
	for (int i = 1 ; i <= Cnt ; ++ i) {
		if( (S[i] & X) == S[i]) {
			++ Ans ;
			X = X & (~S[i]) ;
		}
	}
	return Ans ;
}
```
搜索：因为前期做好了工作，搜索函数内部很简洁：

```cpp
void DFS (Ull X , int Stp , int Des) {

	int Now = G(X) ;
	if (Now + Stp > Ans) return ;
	if (Now == 0 || Fl) {
		Fl = true ;
		return ;
	}

while ((S[Des] & X) != S[Des]) ++ Des ;
for (int i = F[Des] ; i < F[Des] + Len[Des] ; ++ i) {
		if (Check (X , F[Des]))DFS (Del (X , F[Des]) , Stp + 1 , Des + 1) ;
		if (Check (X , Len[Des] * ((N << 1) + 1) + i))
            DFS (Del ( X , Len[Des] * ((N << 1) + 1) + i) , Stp + 1 , Des + 1);
	}
for (int i = 1 ; i <= Len[Des]; ++ i) {
	if (Check (X , F[Des] + (2*i-1) * N + i - 1))
          DFS( Del (X , F[Des] + (2*i-1) * N + i - 1) , Stp + 1 , Des + 1) ;
	if (Check (X , F[Des] + (2*i-1) * N + i - 1 + Len[Des])) 
          DFS (Del (X , F[Des] + (2*i-1) * N + i - 1 + Len[Des] ), Stp + 1 , Des + 1) ;
	}
}
```

**注意清空数组**


```cpp
memset(a,0,sizeof(a));//清零 a 数组
```


---

## 作者：__Kyw666__ (赞：2)

## 题意解释
有 $n$ 根木棒，长度分别为 $x_i$，问是否能拼成一个正方形。

## 思路分析
就是一道 ``dfs``。  
**首先：** 把木棒的总长度算出来，看看是否能被 $4$ 整除。否则输出 ``no``，能则计算出每条边所需的长度，开始搜索。  
其中有个小细节，就是把 $x$ 数组按从小到大排个序。  
**其次：** 进行深搜，判断能否用其中的若干根小木棒组成每条边所需长度，并组成 $4$ 条。  
**最后：** 按要求输出 ``yes`` 或 ``no``。  

**坑点：**   
本题为多组数据，记得清空。  
时间复杂度较高，要剪枝，我还用了加速语句。  
输入格式要注意，否则 WA。

## 代码实现
以下展示深搜部分的代码。

```cpp
bool dfs(int num,int len,int stick)//分别表示第num根小棒，现在正在组合的长度len,已经拼好了stick条边 
{
	if(stick>=4) return 1;//完成任务 
	if(len==sum) return dfs(0,0,stick+1);//拼好了一条边 
	int t=0;//记录是否重复 
	for(int i=num;i<=n;i++)
	{
		if(vis[i]||len+x[i]>sum||t==x[i]) continue;//不符合要求 
		vis[i]=1;
		if(dfs(i+1,len+x[i],stick)) return 1;//再拼一根 
		t=x[i];//记录 
		vis[i]=0;//回溯 
	}
	return 0;
}
```

结束！

---

## 作者：___w (赞：2)

### [UVA10364 Square](https://www.luogu.com.cn/problem/UVA10364)

#### 题意简述
有 $n$ 个小木棍，判断所有的木棍能否拼成一个正方形。

#### 题目分析
搜索题，要考虑剪枝，其实这道题是[小木棍](https://www.luogu.com.cn/problem/P1120)的弱化版。

优化：

1. 优化搜索顺序

把木棍长度从大到小排序，优先尝试较长的木棍。

2. 排除等效冗余

（1）可以限制先后加入一根原始木棒的木棍长度是递减的。这是因为先拼上一根长度为 $x$ 的木棍，再拼上一根长为 $y$ 的木棍（$x<y$），与先拼上 $y$ 再拼上 $x$ 显然是等效的，只需要搜索其中一种。

（2）对于当前原始木棒，记录最近一次尝试拼接的木棍长度。如果分支搜索失败回溯，不再尝试向该木棒中拼接其他相同长度的木棍（必定也会失败）。

（3）如果在当前原始木棒中“尝试拼入的第一根木棍”的递归分支就返回失败，那么直接判定当前分支失败，立即回溯。这是因为在拼入这根木棍前，面对的原始木棒都是“空”的（还没有进行拼接），这些木棒是等效的。木棍拼在当前的木棒中失败，拼在其他木棒中一样会失败。

（4）如果在当前原始木棒中拼入一根木棍后，木棒恰好被拼接完整，并且“接下来拼接剩余原始木棒”的递归分支返回失败，那么直接判定当前分支失败，立即回溯。该剪枝可以用贪心来解释，“再用 $1$ 根木棍恰好拼完当前原始木棒”必然比“再用若干根木棍拼完当前原始木棒”更好。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 25;
int t, n, len, sum, a[N];
bool v[N];

bool cmp(int x, int y) { return x > y; }

bool dfs(int p, int l, int k) {//当前位置，当前的边的长度，当前要拼接第几条边 
	if (k == 4) return 1;//前3个边拼完一定满足 
	if (l == len) return dfs(1, 0, k+1);//当前的边拼完 
	int fail = 0;//剪枝(2) 
	for (int i = p; i <= n; ++i)//剪枝(1) 
		if (!v[i] && l+a[i] <= len && fail != a[i]) {
			v[i] = 1;
			if (dfs(i+1, l+a[i], k)) return 1;
			v[i] = 0;
			fail = a[i];
			if (!l || l+a[i] == len) return 0;//剪枝(3,4) 
		}
	return 0;
}

bool solve() {
	len = sum/4;
	sort(a+1, a+n+1, cmp);
	if (sum%4 || a[1] > len) return 0;
	memset(v, 0, sizeof(v));//多测 
	return dfs(1, 0, 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n;
		sum = 0;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			sum += a[i];
		}
		if (solve()) cout << "yes\n";
		else cout << "no\n";
	}
	return 0;
}
```

---

## 作者：caramel_qwq (赞：2)

这道题嘛，一看就是个 dfs 


------------
### 题意简述及注意事项
- 这道题有点像 $n$ 个数选出 $m$ 组和为 $k$ 的和的排列
- 注意时间限制
- 数组大小合理空间炸不了


### 题目分析
- 要带回溯，因为是选 $m$ 组，说明肯定会有多种组合方式对吧，当然是在有解的情况下。
- 那么就很像全排列了，不过 $m$ 固定为 $4$，因为正方形有 $4$ 条边~~这不是人都知道~~，所以只要带个变量（当前选了第几条边或选到了第几条边，随便你怎么理解吧）然后就是已经选边的和（埋个伏笔）。
- 每次递归看一下有没有到 $1/4$ 总和，是的话就清零下一条


### 接上文伏笔
```cpp
void dfs(int now){
	if(flag) return ;
	if(flag==false&&now==4){
		flag=true;
		cout<<"yes\n";
		return ;
	}
	if(sum==zlen/4){
		sum=0;
		dfs(now+1);
	}
	for(int i=1;i<=n;i++){
		if(v[i]==false){
			v[i]=true;
			sum+=a[i];
			dfs(now);
			sum-=a[i];
			v[i]=false;
		}
	}
	return ;
}
```

如果你用的是上文解法，恭喜你超时了，因为这道题要剪枝，不然会把所有排列都试一遍，貌似是 $n!$ 次递归？$20$ 的阶乘你自己算算，不用我多说剪枝的意义了吧。不懂剪枝是什么的，请走[传送门](https://www.cnblogs.com/jaszzz/p/12722445.html)


------------

这道题有几种剪枝方法，不需要全部用，但是我为了保险一点，写上所有方法。
1. 排序，你这么想，从大往小选，是因为累加起来要快一点，就看你怎么理解“快”。如果已经超过 $1/4$ 长度总和，也就是边长，还有继续选的必要嘛？肯定不是正解啊，所以这个排列跳过，这就是从大到小排序的必要性或好处；
1. 用一个 $last$，记录上一次选到哪了，这是什么操作呢？题目要求全部用上，对吧？但是如果你每次递归都从开头开始找没有选过的，不是有很多冗余吗？那么就记录上一次选到哪了，这次就从这里开始选；
1. 主函数里就可以剪枝，如果总长度不是 $4$ 的倍数，能围成正方形吗？不能，所以特判看一下要不要进递归；
1. 有没有选的必要性，比如我现在总和为 $0$，加上这条边的长度，这条边  $0cm$ ，我用加吗？或者说你现在加了个长木棍，就把 $0$ 留到后面，那不还是要加吗？这是个贪心的策略，你要么现在加，要么以后加，你说长的好算，也对，你说短的灵活，方便修改，那也对，所以就把不合法的干脆扔掉，也就是返回 $0$。
第四种剪枝方案其实包含了两步操作，别看岔了哦。


------------
当然这只蒟蒻刚开始没考虑那么多，写了个排序就交了，于是[看，这个是AC（doge](https://www.luogu.com.cn/record/75200037)


------------
鄙人认为最好还是把 $4$ 种剪枝都写上，毕竟保险点，现在附上通过了的代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int t,n,a[108],zlen;
bool v[108],flag;
bool dfs(int now,int tsum,int last){
	// 防伪认证
	if(now>4){
		flag=1;
		return true;
	}
	if(tsum==zlen){
		dfs(now+1,0,1);
	}
	int before=0;
	for(int i=last;i<=n;i++){
		if(tsum+a[i]<=zlen&&v[i]==false&&before!=a[i]){
			v[i]=true;
			if(dfs(now,tsum+a[i],i)==true){
				return true;
			}
			v[i]=false;
			before=a[i];
			if(tsum==0||tsum+a[i]==zlen){
				return false;	
			} 
		}
	}
	return false;
}
bool cmp(int x,int y){
	return x>y;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		memset(v,0,sizeof(v));
		zlen=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			zlen+=a[i];
		}
		if(zlen%4!=0){
			printf("no\n");
			continue;
		}
		zlen/=4;
		sort(a+1,a+n+1,cmp);
		flag=0;
		dfs(1,0,1);
		if(flag==true){
			printf("yes\n");
		}else{
			printf("no\n");
		}
	}
	return 0;
}
```


------------
### 结尾
请忽略我凌乱的码风，另外，你要抄就抄吧，反正洛谷黑科技能查出来的。

---

## 作者：LouYiYang1 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/UVA10364)
## 正解(搜索剪枝)
当总长度不是四的倍数时不可行。

接着将长度和除以 $4$ ，得到每条边的长度 $l$ 。用一个变量 $flag$ 代表当前是否有可行方案。之后暴力搜索，并定义四个变量 $a,b,c,d$ ，分别代表四条边已有的长度。若木棒加上此边的长度超过了 $l$ ,则跳过（剪枝操作）。本条边加上木棍长度，进行下一步搜索，并回溯。若```flag=1```，（已有可行方案）则可以直接跳过以上操作。当木棍遍历结束，可直接判断 $a=b$ 且 $b=c$ 且 $c=d$ ，若等于则```flag=1```。最后输出。
## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,s;
int a[25],b[5];
int fl=0;
void dfs(int i){
	if(i==n+1){
		if(b[1]==b[2]&&b[2]==b[3]&&b[3]==b[4]) fl=1;
		return;
	}
	for(int j=1;j<=4;j++){
		if(b[j]+a[i]>s) continue;
		if(fl==0){
			b[j]+=a[i];
			dfs(i+1);
			b[j]-=a[i];
		}
		else break;
	}
}
int main(){
	cin>>T;
	while(T--){
		memset(b,0,sizeof(b));
		fl=0;
		s=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s+=a[i];
		}
		if(s%4!=0){
			cout<<"no"<<"\n"; 
			continue;	
		}
		s/=4;
		dfs(1);
		if(fl==1) cout<<"yes"<<"\n";
		else cout<<"no"<<"\n";
	}
	return 0;
}
```

---

## 作者：headache (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA10364)
## 骗分代码
  将所有的长度加起来。
  
  当是 $4$ 的倍数，可行。
  
  其他情况，不可行。
  

---

这的确给了我们一些思路。
至少当总长度不是四的倍数时不可行。

## 正解(搜索剪枝)
当总长度不是四的倍数时不可行。

接着将长度和除以 $4$ ，得到每条边的长度 $l$ 。用一个变量 $flag$ 代表当前是否有可行方案。

之后暴力搜索，并定义四个变量 $a,b,c,d $，分别代表四条边已有的长度。若木棒加上此边的长度超过了 $l$ ,则跳过（剪枝操作）。

本条边加上木棍长度，进行下一步搜索，并回溯。

若 $flag=1$ ，（已有可行方案）则可以直接跳过以上操作。

当木棍遍历结束，可直接判断 $a=b=c=d$ ，若等于则   $flag=1$ 。

最后输出。

## 代码展示
```
#include<bits/stdc++.h>
using namespace std;
int T,n,s;
int a[25],b[5];
int fl=0;
void dfs(int i){
	if(i==n+1){
		if(b[1]==b[2]&&b[2]==b[3]&&b[3]==b[4]) fl=1;
		return;
	}
	for(int j=1;j<=4;j++){
		if(b[j]+a[i]>s) continue;
		if(fl==0){
			b[j]+=a[i];
			dfs(i+1);
			b[j]-=a[i];
		}
		else break;
	}
}
int main(){
	cin>>T;
	while(T--){
		memset(b,0,sizeof(b));
		fl=0;
		s=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s+=a[i];
		}
		if(s%4!=0){
			cout<<"no"<<"\n"; 
			continue;	
		}
		s/=4;
		dfs(1);
		if(fl==1) cout<<"yes"<<"\n";
		else cout<<"no"<<"\n";
	}
	return 0;
}
```

---

## 作者：ZnHF (赞：1)

# 题意简述

给定 $n$ 根木棍，第 $i$ 根的长度为 $a_{i}$，求能否使用**全部**木棍拼成一个正方形。

# 题目分析

这道题和 P1120 很像，都考察了对于 DFS 的剪枝优化。

具体地，我们有以下几个剪枝策略

1. 计算出每根木棍的长度之和，记为 $sum$，若 $sum \bmod 4 \neq 0$，则直接输出 `no`。

2. 将每一根木棍按长度从大到小排序，优先尝试将长度更长的木棍拼入正方形中。

3. 若下一层搜索返回失败，则不再尝试将长度和上一次拼入正方形的木棍的长度一样的木棍拼入正方形。

4. 若下一层搜索返回失败，且当前拼出的边的长度为 $0$ 则直接返回失败。原因是其他没有拼过的边和当前在考虑的空的边是等效的，将某跟木棍拼入当前的边若失败，则将该木棍拼入其他空的边同样会失败。

5. 若将当前考虑的某根木棍拼入当前考虑的边后，边长达到了要求，但后续的搜索返回失败，则直接返回失败。原因是较短的木棍比较长的木棍更优，当为后续的搜索留下更多更短的木棍都无法拼成时，若在当前使用更短的木棍，则后续的搜索一定无法成功。

讲得可能不太好，所以具体实现看代码。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[25],sum;
bool vis[25];
bool cmp(int x,int y){
	return x>y;
}
bool dfs(int finish,int now_len,int last){
	if(finish>=4) return 1;
	if(now_len==sum) return dfs(finish+1,0,1);
	int never=0;
	for(int i=last;i<=n;i++){
		if(!vis[i] && now_len+a[i]<=sum && never!=a[i]){
			vis[i]=1;
			if(dfs(finish,now_len+a[i],i+1)) return 1;
			never=a[i];
			vis[i]=0;
			if(!now_len || now_len+a[i]==sum) return 0;
		}
	}
	return 0;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		sum=0;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		if(sum%4!=0){
			puts("no");
			continue;
		}
		sort(a+1,a+1+n,cmp);
		sum/=4;
		if(dfs(0,0,1)==1) puts("yes");
		else puts("no");
	}
	return 0;
}
```

---

## 作者：Scean_Tong (赞：1)

# 思路

这道题其实是一道搜索问题，要求从给定的 $N$ 根木棍中选择一些围成正方形。看到题目似乎最先想到的是 DFS，当然大家想到的其他算法也可以尝试实现。

DFS 可以想象成遍历一颗树，每一个节点都是一个状态，在搜索过程中不断地向下遍历，直到满足我们困惑的需要为止。具体地，遍历中选择每一条路径，其中 $x$ 代表还剩下需要放置的木棍的 $index$，$s$ 代表当前累计的边长长组成。


注意每一根木棍只能挑选一次，这需要在每一次 DFS 中剪枝。此外，满足如下条件亦可进行剪枝：

- 当 $s1$ 和 $s2$ 已经等长，但 $s3$ 或 $s4$ 目前所需长度大于 $s1$ 或 $s2$；
- 当 $s1$、$s2$、$s3$ 中有至少一个和 $s4$ 长度相同，但这个长度小于正方形的边长。

需要注意一下，为了提高效率，可以先对原数组进行排序，每次从数组最后面开始取。因为长度小的木棍可以先判断出来是否可以组成正方形，这样比先选长的木棍进行枚举回溯更能提高效率（可以尝试画出 DFS 的状态树，自行体会两种策略的时间复杂度）。



---

## 作者：guaidaokenan (赞：0)

# 题目大意
要判断题目给定的 $N$ 根木棍是否能围成一个正方形。

# 大体思路
- 拼成的正方形的周长必须能被 $4$ 整除，因为每条边为整数。
- $N$ 根木棍中的任意一根都不能超过边长。
- 使用回溯算法将每根木棍分配到正方形的四条边里。由于可能存在多种拼凑方式，可以使用回溯算法来遍历所有可能的拼凑情况，如果发现当前的分配方式不合法，就退回到上一步，尝试其他的方式，直到找到一种可以围成正方形的拼凑方式或者尝试完所有可能的拼凑方案。

# 回溯

分配可以用 [回溯](http://oi-wiki.com/search/backtracking/) 解决，可是容易发现，单纯的回溯会超时，需要剪枝。

- 回溯过程中可能会尝试相同长度的木棍，如果有一根木棍无法拼接到某条边上，那和它长度相同的木棍也不能拼接。所以遇到长度相同的木棍，直接跳过即可。
- 将木棍按长度从长到短排序，这样可以优先选长的木棍拼，因为短的木棍利用的场景更多，所以优先采用长的木棍，将短的木棍留下来。
- 若边长为 $0$ 且加入长度为 $a_i$ 的木棍不符合，直接返回即可。

# 给出代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n;
int sum;
int a[25];
bool flag;
bool vis[25];
void dfs(int x, int y, int z) {
    if(flag==1){//找到了方案，即flag为1，返回
        return ;
    }
    if(x==5){
        flag=1;
        return;
    }
    if(y==sum){//已构建完，开始建下一条边
        dfs(x+1,0,0);
    }
    for(int i=z+1; i<=n; i++){        
        if (vis[i]==0&&y+a[i]<=sum){// 如果第i根木棍还未被使用并加入后不会超过目标长度
            vis[i]=1;
            dfs(x,y+a[i],i);
            vis[i]=0;
        }
    }
}
signed main(){
    scanf("%d",&t);//多组数据
    while(t--){
        scanf("%d",&n);
        sum=0;//初数值
        flag=0;
        for(int i=1; i<=n; i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        if(sum%4!=0){//总长不能能被 4 整除
            printf("no\n");
        }
        else{
            sum/=4;//算出边长
            bool f=false;
            for(int i=1; i<=n; i++){
                if(a[i]>sum){
                    f=true;
                    break;
                }
            }
            if(f==true){
                printf("no\n");
            }
            else{
                for(int i=1; i<=n; i++){
                    vis[i]=0;//初始值
                }
                dfs(1,0,1);
                if(flag==true){//找到了合适的解法
                    printf("yes\n");
                }
                else {
                    printf("no\n");
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：zhangmuning1016 (赞：0)

## 题目
我们要判断给定的 $N$ 根木棍是否能够围成一个正方形。
## 思路
- 拼成正方形要四条边长度相等，应为木棍的长度为整数，那么木棍的总长必须被 $4$ 整除。
- 木棍的长度不能超过边长，不然这个木棍就放不了。
- 运用回溯算法将每根木棍分配到正方形的四条边中。由于可能存在多种分配方式，我们使用回溯算法来遍历所有可能的分配情况，当发现当前的分配方式不合法，就回溯到上一步，尝试其他的分配方式，直到找到一种可以围成正方形的分配方式或者遍历完所有可能的组合。
## 回溯
分配可以用 [回溯](https://oiwiki.com/search/backtracking/) 解决，可是容易发现，单纯的回溯会超时，需要剪枝。
- 回溯过程中会重复尝试相同长度的木棍，如果有根木棍无法拼接到某条边上，那和它长度相同的木棍也不能拼接。所以遇到长度相同的木棍，直接跳过。
- 将木棍按长度从长到短排序，这样可以优先选长的木棍拼。
- 如果边长为 $0$，且加入长度为 $a_i$ 的木棍不符合，直接返回。
## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n;
int sum;
int a[21];

bool flag;// 初始值0。
bool v[21];
void dfs(int x, int y, int z) {
    if (flag == 1) {// 找到了方案，即 flag 为 1，返回。
        return;
    }
    if (x == 5) {
        flag = 1;
        return;
    }
    if (y == sum) {// 已构建完，开始建下一条边。
        dfs(x + 1, 0, 0);
    }
    for (int i = z + 1; i <= n; i++) {
        
        if (v[i] == 0 && y + a[i] <= sum) {// 如果第 i 根木棍还未被使用并加入后不会超过目标长度。
            v[i] = 1;
            dfs(x, y + a[i], i);
            v[i] = 0;
        }
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--) {
        cin >> n;
        sum = 0;
        flag = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum += a[i];
        }
        if (sum % 4 != 0) {//总长不能能被 4 整除。
            cout << "no";
        }
        else {
            sum /= 4;
            bool f = 0;
            for (int i = 1; i <= n; i++) {
                if (a[i] > sum) {
                    f = 1;
                    break;
                }
            }
            if (f) {
                cout << "no";
            }
            else {
                for (int i = 1; i <= n; i++) {
                    v[i] = 0;
                }
                dfs(1, 0, 1);
                if (flag) {//找到了。
                    cout << "yes";
                }
                else {
                    cout << "no";
                }
            }
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# UVA10364
## 题意
给定 $N$ 根木棍，第 $i$ 根木棍的长度为 $x _ {i}$，问是否能围成一个正方形。
## 思路
本题考虑使用深搜。一开始可以排除一些情况，我们记木棍的总长度为 $sum$，如果 $sum$ 不是 $4$ 的倍数或者 $N < 4$ 或者 $sum$ 小于木棍长度的最大值，直接输出 ``no``。然后去做深搜看能不能围成正方形即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,m,sum,l,a[25];
bool vis[25];
int dfs(int pos,int len,int x){//pos是现在的木棍编号，len是现在围成的一边的长度，x是已经围好的边数 
	if(x==3)return 1;//如果已经围好了三条边，肯定可以 
	for(int i=pos;i>=0;i--)
	if(!vis[i]){//如果没访问过 
		vis[i]=1;
		if(len+a[i]<l&&dfs(i-1,len+a[i],x))return 1;
		else if(len+a[i]==l&&dfs(m-1,0,x+1))return 1;
		vis[i]=0;
	}
	return 0;
}
int main()
{
	cin>>t;
	while(t--){
		sum=0; 
		cin>>m;
		for(int i=0;i<m;i++){
			cin>>a[i];
			sum+=a[i];
		}
		l=sum/4;//每条边的长度 
		memset(vis,0,sizeof(vis));
		sort(a,a+m);
		if(l*4!=sum||m<4||l<a[m-1])cout<<"no\n";
		else if(dfs(m-1,0,0))cout<<"yes\n";
		else cout<<"no\n";
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

本题是 P2383 的强化版。

考虑以下几种剪枝：

剪枝 1：如果已经拼好了 3 条边，剩下的木棍就无需考虑；

剪枝 2：给木棍长度从大到小排序，因为大的活动性弱，可以决定大致范围；

剪枝 3：在同一条边上，已经遍历过的长木棍不用再遍历；

剪枝 4：如果这条边已经拼好了，就不用再考虑这条边了；

剪枝 5：找到了合适的方法就退出。

```cpp
//P2383 & UVA10364
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=25;
int n,len;
bool f;
int a[N];
bool vis[N];
void dfs(int l,int e,int lst){
	if(f) return ;
	if(l>len) return ;
	if(l==len){
		l=0,++e,lst=0;
	}if(e==3){
		f=1;
		return ;
	}
	for(int i=lst+1;i<=n;++i){
		if(!vis[i]){
			vis[i]=1;
			dfs(l+a[i],e,i);
			vis[i]=0;
			if(l==0||l+a[i]==len) return ;
		}
	}return ;
}
void work(){
	cin>>n;
	f=0;
	len=0;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		len+=a[i];
	}if(len%4!=0){
		cout<<"no"<<endl;
		return ;
	}
	len/=4;
	sort(a+1,a+n+1,greater<int>());
	dfs(0,0,0);
	if(f){
		cout<<"yes"<<endl;
	}else{
		cout<<"no"<<endl;
	}
	return ;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		work();
	} 
	return 0;
} 
```

---

## 作者：zishengzhe (赞：0)

题面→ [Link](https://www.luogu.com.cn/problem/UVA10364)

此题为 DFS 题，因为数据有点大，所以要对 DFS 进行剪枝。
1. 判断所有木棍长度总和 $sum$ 是否为 $4$ 的倍数。
2. 如果木棍总数 $m<4$，则不可能构成正方形。
3. 如果最长木棍的长度大于所有木棍长度总和 $sum$，则不可能构成正方形。
4. 如果已构成正方形的三条边，则直接返回，不再判断。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int t,m,a[25],sum,mx;
bool used[25];//是否用过此木棍
int dfs(int pos,int s,int bian){//pos为木棍个数，s为当前边已拼好长度，bian为当前拼到的边
	if(bian==3) return 1;//剪枝4
	for(int i=pos;i>=0;i--){//
		if(!used[i]){//找到一个没用过的木棍
			used[i]=1;
			if(s+a[i]<sum/4){
				if(dfs(i-1,s+a[i],bian)) return 1;//减少一根木棍，长度加a[i]
			}
			else{
				if(s+a[i]==sum/4)//是否拼好一边
					if(dfs(m-1,0,bian+1)) return 1;//减少一根木棍,清空此边长度，拼成的边数加1
			}
			used[i]=0;
		}
	}
	return 0;
}
int main(){
	cin>>t;
	while(t--){
		sum=0,mx=0;
		for(int i=0;i<22;++i) used[i]=0;//每一轮循环后都要初始化
		cin>>m;
		for(int i=0;i<m;++i){
			cin>>a[i];
			sum+=a[i];//记录木棍总和
			mx=max(mx,a[i]);//记录最长木棍长度
		}
		if(mx*4>sum||m<4||sum%4!=0){//剪枝1,2,3
			cout<<"no\n";
			continue;
		}
		sort(a,a+m);//排序
		if(dfs(m-1,0,0)) cout<<"yes\n";//满足条件
		else cout<<"no\n";//不满足
	}
	return 0;//完结撒花，感谢观看
}

```

---

