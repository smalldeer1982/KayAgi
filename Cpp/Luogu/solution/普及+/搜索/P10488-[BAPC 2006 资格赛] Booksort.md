# [BAPC 2006 资格赛] Booksort

## 题目描述

给定 $n$ 本书，编号为 $1 \sim n$。

在初始状态下，书是任意排列的。

在每一次操作中，可以抽取其中连续的一段，再把这段插入到其他某个位置。

我们的目标状态是把书按照 $1 \sim n$ 的顺序依次排列。

求最少需要多少次操作。

## 说明/提示

$1 \le n \le 15$。

## 样例 #1

### 输入

```
3
6
1 3 4 6 2 5
5
5 4 3 2 1
10
6 8 5 3 4 7 2 9 1 10```

### 输出

```
2
3
5 or more```

# 题解

## 作者：BK小鹿 (赞：9)

## 题意简述

给定一个序列，通过几次插入操作，使其变得有序，求最小的操作数。

## 思路分析

看到这么小的范围，明显爆搜。但是朴素的算法复杂度为四次方，显然会超时。此时考虑双向搜索或 IDA*。由于本人太菜了，不会双向搜索，所以决定使用 IDA*。

什么是 IDA* 呢？其实就是迭代加深的升级版，我们在搜索的时候提前预估这个节点会产生多少层，如果加上当前层数大于搜索最大层数就提前返回。正确性显而易见，我们只需要写一个估价函数，使他小与等于实际层数就行了。

如何写估价函数呢？显然，假设当前一共有 $tot$ 个错误后继，我们一次移动最理想的情况下能修正三个，直接除以三即可。

剩下的就是套路模版了，非常好写。

## AC Code


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 15;

int n;
int q[N], w[5][N];

int f()
{
    int tot = 0;
    for (int i = 0; i + 1 < n; i ++ )
      if (q[i] + 1 != q[i + 1])
        tot ++ ;
        
    return (tot + 2) / 3;
}

bool dfs(int u, int max_depth)
{
    if (u + f() > max_depth)  return 0;
    if (f() == 0)  return 1;
    
    for (int len = 1; len <= n; len ++ )
      for (int l = 0; l + len - 1 < n; l ++ )
      {
          int r = l + len - 1;
          for (int k = r + 1; k < n; k ++ )
          {
              memcpy(w[u], q, sizeof q);
              
              int y = l;
              for (int x = r + 1; x <= k; x ++ , y ++ )  q[y] = w[u][x];
              for (int x = l; x <= r; x ++ , y ++ )  q[y] = w[u][x];
              
              if (dfs(u + 1, max_depth))  return 1;
              
              memcpy(q, w[u], sizeof q);
          }
      }
      
    return 0;
}

int main()
{
    int T;
    cin >> T;
    while (T -- )
    {
        cin >> n;
        for (int i = 0; i < n; i ++ )  cin >> q[i];
        
        int depth = 0;
        
        while (depth < 5 && !dfs(0, depth))  depth ++ ;
        
        if (depth >= 5)  puts("5 or more");
        else cout << depth << '\n';
    }
    
    return 0;
}
```

---

## 作者：MoonCake2011 (赞：7)

就是一个 DFS。

写一个 `move` 函数。

表示将 $x,y$ 段，与 $y+1,z$ 段交换。

也就是将 $y+1,z$ 段提出，插入到 $x$ 之前的位置。

每次注意用局部数组记录当前状态来递归。

枚举就行。

于是 TLE 了。

为什么？

~~只因你太美~~。

只因数据有点大。

现在需要跑 $(15^3)^5=15^{15}=4.3789389e+17$。

$4 \times 10^{17}$ 太大了。

你会发现，有些答案可能在浅层。

所以应用 BFS。

但是空间。

所以 IDDFS 启动。

IDDFS，顾名思义，就是一层一层搜的 DFS。

于是外层循环枚举层数。

里面执行有深度限制的 DFS。

只要搜到答案就 `break`。

But，这样治标不治本。

于是，搜索剪枝，启动。

现在有了层数限制。

于是直接从这方面考虑。

假设一个数有错误后继 $F$ 个。

$F=0$ 时答案成立。

一次 `move(x,y,z)` 最多能将 $F-3$。

因为最好情况下，能将 $z$ 的后继修正，$x-1$ 修正，$y$ 修正。

假设最深层为 $dep$，现在搜到了 $t$ 层。

于是，如果 $t+\dfrac{F}{3} > dep$。

这一个枝条一定没有答案。

剪了。

一个~~漂亮~~的 IDA* 写好了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[20],tmp[20];
void move(int x,int y,int z){
	memset(tmp,0,sizeof tmp);
	int tot=0;
	for(int i=y+1;i<=z;i++) tmp[++tot]=a[i];
	for(int i=x;i<=y;i++) tmp[++tot]=a[i];
	tot=0;
	for(int i=x;i<=z;i++) a[i]=tmp[++tot]; 
}
bool dfs(int maxd,int dep){
	if(dep>maxd) return 0;
	int q[20];
	for(int i=1;i<=n;i++) q[i]=a[i];
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			for(int k=j+1;k<=n;k++){
				move(i,j,k);
				int F=0;
				for(int p=1;p<n;p++) if(a[p+1]!=a[p]+1) F++;
				if(a[n]!=n) F++;
				if(F==0) return true;
				if(3*dep+F<=3*maxd && dfs(maxd,dep+1)) return true; 
				for(int p=1;p<=n;p++) a[p]=q[p];
			}
		}
	}
	return false;
}
void solve(){
	cin>>n;
	int t[20];
	for(int i=1;i<=n;i++) cin>>a[i],t[i]=a[i];
	bool flag=0;
	for(int i=1;i<n;i++) if(a[i+1]!=a[i]+1) flag=1;
	if(a[n]!=n) flag=1;
	if(!flag){
		cout<<"0\n";
		return;
	}
	for(int i=1;i<=4;i++){
		if(dfs(i,1)){
			cout<<i<<"\n";
			return;
		}
		for(int j=1;j<=n;j++) a[j]=t[j];
	}
	cout<<"5 or more\n";
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
} 
```

---

## 作者：cyx12 (赞：6)

# 题解：P10488 Booksort

[题目传送门](https://www.luogu.com.cn/problem/P10488)

## Part 1 思路讲解

1. 考虑每个状态的转移（分支）数量，在每个状态下，可以抽取连续的一段数，移动到另一个位置。

- 对于任意的长度 $len$，当抽取长度为 $len$ 时，有 $n - len + 1$ 种选择，有 $n - len$ 个可插入的位置。

- 另外，把一段数移动到更靠前的位置，等价于把“跳过”的那段书移动到靠后的某个位置，所以上面的计算方法把每种移动情况算了两遍，每个状态的分支数量约为：

- $\sum_{k = 1}^{n-1} \ (n-k) \times (n-k+1) \div 2 \le \sum_{k = 1}^{14} \ (n-k) \times (n-k+1) \div 2 = 560$

2. 根据题目要求，只需要考虑在 $4$ 次操作内是否能实现目标，也就是我们只需要考虑搜索树的前 $4$ 层。

- 四层的搜索树的规模能够达到 $560^4$，超时！

3. 算法 1：采用双向 BFS，从初始状态，目标状态开始各搜 $2$ 步，看能否在相同的状态相遇，复杂度降为 $560^2$（请自行尝试）。

4. 算法 2：IDA Star

- 在目标状态下，第 $i$ 本书的后面应该是 $i+1$ 本书，称 $i+1$ 时 $i$ 的正确后继。

- 对于任意状态下，考虑整个排列中书的错误后继的总个数（记为 $cnt$），可以发现，每次操作最多更改 $3$ 本书的后继。即使在最理想的情况下，每次操作都能把某 $3$ 个错误后继全部改对，清除所有错误后继的操作次数也至少需要 $\lceil \frac{cnt}{3} \rceil$ 次。

- 因此，可以将状态 $stat$ 的估价函数设计为 $f(stat) = \lceil \frac{cnt}{3} \rceil$，其中 $cnt$ 表示状态 $stat$ 中有多少本书的后继是错误的。

- 采用迭代加深的方法，从 $1 \to 4$ 一次限制搜索深度，然后从起始状态出发 DFS。DFS 时，在每个状态下直接枚举抽取那一段，移动到更靠后的某个位置，沿着该分支深入即可。注意在进入任何状态 $stat$ 后，先进行判断，如果当前操作次数 + $f(s)$ 已经大于深度限制，直接从当前分支回溯。

## Part 2 代码

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int a[20],tmp[20];
void move(int x,int y,int z){
	memset(tmp,0,sizeof tmp);
	int t=0;
	for(int i=y+1;i<=z;i++) tmp[++t]=a[i];
	for(int i=x;i<=y;i++) tmp[++t]=a[i];
	t=0;
	for(int i=x;i<=z;i++) a[i]=tmp[++t]; 
}
bool dfs(int maxd,int dep){
	if(dep>maxd) return false;
	int q[20];
	memcpy(q,a,sizeof(q));
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			for(int k=j+1;k<=n;k++){
				move(i,j,k);
				int F=0;
				for(int p=1;p<n;p++) if(a[p+1]!=a[p]+1) F++;
				if(a[n]!=n) F++;
				if(F==0) return true;
				if(F==0||3*dep+F<=3*maxd&&dfs(maxd,dep+1)) return true; 
				memcpy(a,q,sizeof(a));
			}
		}
	}
	return false;
}
int main() {
	int t;
	cin>>t;
	while(t--){
        cin>>n;
    	int t[20];
    	for(int i=1;i<=n;i++) cin>>a[i];
        memcpy(t,a,sizeof(t));
    	bool flag=0;
    	for(int i=1;i<n;i++) 
            if(a[i+1]!=a[i]+1) flag=1;
    	if(a[n]!=n) flag=1;
    	if(!flag){
    		cout<<"0\n";
    		continue;
    	}
    	int f=1;
    	for(int i=1;i<=4;i++){
    		if(dfs(i,1)){
    			cout<<i<<"\n";
    			f=0;
    			break;
    		}
    		memcpy(a,t,sizeof(a));
    	}
    	if(f==1)cout<<"5 or more\n";
    }
	return 0;
} 
```

---

## 作者：喵仔牛奶 (赞：5)

来一篇实现简洁的题解！

# Solution

题目说了次数 $<5$，我们自然考虑 [IDA\*](https://oi-wiki.org/search/idastar/)，枚举深度再来 DFS。

先考虑模拟这个操作。设插入的位置是 $k$，如果 $k<l$，那么将 $[l,r]$ 插到 $k$ 前面可以看作交换 $[k,l-1],[l,r]$；如果 $k>r$，那么将 $[l,r]$ 插到 $k$ 后面可以看作交换 $[l,r],[r+1,k]$。交换相邻区间可以利用 `std::rotate` 函数：
> `rotate(l,k,r)` 即为交换 $[l,k-1],[k,r-1]$，其中 $l,k,r$ 都是指针或迭代器。

我们的代码就有啦：
```cpp
REP(L, 1, n) REP(R, L, n) {
	REP(k, 1, L - 1) {
		rotate(a + k, a + L, a + R + 1), dfs(d + 1, mxdep);
		rotate(a + k, a + k + R - L + 1, a + R + 1); // 回溯
	}
	REP(k, R + 1, n) {
		rotate(a + L, a + R + 1, a + k + 1), dfs(d + 1, mxdep);
		rotate(a + L, a + L + k - R, a + k + 1); // 回溯
	}
}
```

写个 dfs 测一下样例，嗯，T 飞了。不过不慌，这是因为我们还没有写 IDA* 的核心——**乐观估价函数**！

考虑乐观估价函数怎么写。我们令 $a_{0}=0,a_{n+1}=n+1$，计算 $ct=\sum_{i=1}^{n+1}[a_{i}-a_{i-1}\neq1]$，即相邻的数后面减前面的差不为一的个数。我们发现一次操作最多让 $ct$ 减少 $3$，因为只有 $(k-1,k),(l-1,l),(r,r+1)$ 这三个位置可能贡献被取消。我们算出这个 $ct$，一次最多减 $3$，那么把 $ct$ 减光至少也得 $\lceil\dfrac{ct}{3}\rceil$ 次才行，也就是说我们的乐观估价函数 $h(A)=\lceil\dfrac{ct}{3}\rceil$。

代码那就是这样咯：
```cpp
int ct = 0;
REP(i, 1, n + 1) ct += (a[i] - a[i - 1] != 1);
ct = (ct + 2) / 3;
if (d + ct > mxdep) return;
```

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	int n, chk, a[N];
	void dfs(int d, int mxdep) {
		if (chk) return;
		int ct = 0;
		REP(i, 1, n + 1) ct += (a[i] - a[i - 1] != 1);
		ct = (ct + 2) / 3; // 相当于 ceil(1.0 * ct / 3)
		if (d + ct > mxdep) return;
		if (!ct) { chk = 1; return; }
		REP(L, 1, n) REP(R, L, n) {
			REP(k, 1, L - 1) {
				rotate(a + k, a + L, a + R + 1), dfs(d + 1, mxdep);
				rotate(a + k, a + k + R - L + 1, a + R + 1);
			}
			REP(k, R + 1, n) {
				rotate(a + L, a + R + 1, a + k + 1), dfs(d + 1, mxdep);
				rotate(a + L, a + L + k - R, a + k + 1);
			}
		}
	}
	int main() {
		cin >> n, a[n + 1] = n + 1;
		REP(i, 1, n) cin >> a[i];
		REP(i, 0, 4) {
			chk = 0, dfs(0, i);
			if (chk) { cout << i << '\n'; return 0; }
		}
		cout << "5 or more\n";
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1; cin >> T;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：mxjz666 (赞：3)

**思路**：

本题可以用 IDA* 来解，现在考虑如何制造估价函数。

我们知道第 $i$ 本书后面是第 $i+1$ 本书，这是我们将 $i+1$ 称为 $i$ 的正确后继，我们一次操作至多可以改变 $3$ 个错误后继，所以至少也需要$\lceil tot/3 \rceil$ 次操作。其中 $tot$ 表示错误后继的数量。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[20],b[10][20];
int f(){
	int cnt=0;
	for(int i=0;i<(n-1);i++){
		if(a[i+1]!=a[i]+1){
			cnt++;
		}
	}
	return (cnt+2)/3;
}
bool dfs(int dep,int maxx){
	if(dep+f()>maxx){
		return false;
	}
	if(f()==0){
		return true;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j+i-1<=n;j++){
			int r=j+i-1;
			for(int k=r+1;k<n;k++){
				memcpy(b[dep],a,sizeof(a));
				int x=r+1,y=j;
				for(;x<=k;x++,y++){
					a[y]=b[dep][x];
				}
				x=j;
				for(;x<=r;x++,y++){
					a[y]=b[dep][x];
				}
				if(dfs(dep+1,maxx)==true){
					return true;
				}
				memcpy(a,b[dep],sizeof(a));
			}
		}
	}
	return false;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		if(f()==0){
		    cout<<0<<endl;
		    continue;
		}
		int dep=1;
		while(dep<5){
			if(dfs(0,dep)==true){
				break;
			}
			dep++;
		}
		if(dep>=5){
			cout<<"5 or more";
		}else{
			cout<<dep;
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Zhl2010 (赞：3)

# Booksort

## 题目概括

有 $n$ 本书，在每一次操作中，可以抽取其中连续的一段，再把这段插入到其他某个位置，求最少需要多少次操作把书按照 $1 \sim n$ 的顺序依次排列。

## 样例解释（自己觉得有点难理解的样例）
这个样例有点难懂。
### 样例输入

```
5
5 4 3 2 1
```

### 样例输出

```
3
```
先把 $43$ 移到1的后面，变成 $52143$。

再把 $14$ 移到 $5$ 的前面，变成 $14523$。

最后把 $45$ 移到 $3$ 的后面，变成 $12345$。
## 思路
[IDA*算法](https://blog.csdn.net/weixin_56154577/article/details/137006560)

### 核心：估价函数
我们可以观察到连续序列的移动可以在序列中改变多达三位数字。

因此，每次我们计算当前序列中非法继承人的总数时，除以 $3$ 并四舍五入，得到当前状态评估函数的值。

然后，我们使用迭代深化方法将搜索深度从 $0$ 限制为 $4$，然后从初始状态运行 `DFS`。
## 代码+注释
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q[110],w[6][110];
int f(){//估价函数 
	int an=0;
	for(int z=0;z<n-1;z++){
		if(q[z+1]!=q[z]+1)an++;//两数不符合Q_{i}+1=Q{i+1}，an++ 
	}
	return (an+2)/3;//上取整 
}
bool check(){
	for(int z=0;z<n;z++){
		if(q[z]!=z+1)return 0;//同上 
	}
	return 1;
}
bool dfs(int u,int dep){
	if(f()+u>dep)return 0;//估价函数说超了 
	if(check())return 1;//OK了，直接返回 
	for(int l=0;l<n;l++){//要移动的区域左边界 
		for(int r=l;r<n;r++){//右边界 
			for(int k=r+1;k<n;k++){//移动位置 
				memcpy(w[u],q,sizeof(q));//更新+保存
				int x,y;
				for(x=r+1,y=l;x<=k;x++,y++) q[y]=w[u][x];//更新
				for(x=l;x<=r;x++,y++) q[y]=w[u][x];//更新
				if(dfs(u+1,dep))return 1;
				memcpy(q,w[u],sizeof(q));//dfs后消除上一步 
			}
		}
	}
	return 0;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int z=0;z<n;z++)scanf("%d",&q[z]);
		int dep=0;
		while(dep<5&&!dfs(0,dep))dep++;//迭代加深，dep小于5 
		if(dep>=5)cout<<"5 or more"<<endl;
		else cout<<dep<<endl;
	}
	return 0;
}
```

---

## 作者：wcy0902 (赞：1)

一道 IDA* 的题。


## 思路
我们先进行估价，看他是否找到答案，然后枚举移动的左端点、右端点以及移动到的位置，这里放一张图以助理解。


![](https://cdn.luogu.com.cn/upload/image_hosting/w5gz0a7r.png)

然后说说估价函数。每次移动可以改变三个元素的相对位置，是哪三个呢？分别是左端点、右端点和右端点后面那个节点。

最后就是正常的 IDA* 了

## 坑点

注意是从 $0$ 到 $4$ 进行每一层的递归。


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,y,j,flag;
string a,cnt;
void dfs(int step){
	int cha=0;
	for(int i=1;i<a.size();i++){
		if(a[i]!=a[i-1]+1)  
		cha++;
	}    
	if(cha==0){    
		flag=1;//找到答案。        
		return;        
	}    
        if(cha/3+step>=j)//估价。    
	return;    
	string p=a,s1,s2,s3,s4;//本蒟蒻做法。   
	int p1,p2,p3;    
	for(int i=1;i<=n;i++){   
		for(int x=n+1;x>=i+1;x--){       
			for(int k=2;k<=n+1;k++){           
				if(flag==1)//不做多余动作。      
				return;                
				if(k<i||k>x){//选放在区间外的位置。              if(k<i){p1=k;p2=i;p3=x;}
                            else{p1=i;p2=x;p3=k;}//编个号方便统一处理。 
                            s1=a.substr(0,p1-1);//分为四部分。 
				s2=a.substr(p1-1,p2-p1);
				s3=a.substr(p2-1,p3-p2);
				s4=a.substr(p3-1,n-p3+1);
				a=s1+s3+s2+s4;//插入相当于交换s2,s3位置。 
				dfs(step+1);//继续往下搜。 
				a=p;//回溯。 
				}
			}
		}
	}
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		a=cnt;//归零（本蒟蒻做法）。 
		for(int i=1;i<=n;i++){
		cin>>y; 
		a+=char('A'+y);
	    }
	    flag=0;//归零。 
	    for(j=0;j<=4;j++){//记得从0开始，不然第一个点过不了。 
	    	dfs(0); 
	    	if(flag==1){
	    		cout<<j<<endl;
	    		break;
			}
		}
		if(flag!=1)
		cout<<"5 or more"<<endl;
	}
}
```

祝大家切了这道题。

---

## 作者：Robin_kool (赞：1)

发现 $n$ 很小，状态压缩又不好做，考虑大力枚举。

可是区间左右端点和交换的位置是无法优化的，也就是说对于每一步都需要进行 $O(n^3)$ 的枚举，会寄掉。

考虑先枚举最终的步数，判断是否可行。在枚举的时候，我们先给当前的状态得出一个理想状态下的最优解（实际不可能优于此最优解），再加上已经使用的步数，若得到的总步数无法实现，则可以大胆结束。

本题的难点在于对理想最优解的判断，发现一次交换当前一段和他相邻两端的情况，最少为 $3$，因此最优解即为当前不合法的情况数除以 $3$，记得向上取整。

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

核心算法：IDA*。

首先，$5$ 的最大深度限制就是对迭代加深搜索的提示。但是依然不够，因为每一次都有 $n^3$ 种情况。

这时候我们就需要估价函数辅助。这里，我们约定下文的“逆序对”专指相邻的逆序对。那么，每一次操作最多只能够“修正”三个逆序对。

那么，估价函数的值就可以视为逆序对数量 $\lceil x/3\rceil$。这就是估出来的最少步数。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[16],mdep,tmp[6][16],l,r; bool flg;
inline static int gj(){
	int tot=0;
	for(int i=1;i<n;++i) tot+=(a[i]+1!=a[i+1]);
	return (tot+2)/3;
}    
void dfs(int dep){
	if(flg) return;
	if(!gj()){
		cout<<dep<<endl;
		flg=1; return;
	}
	if(dep+gj()>mdep) return; 
	for(int len=1;len<n;++len)
		for(int i=1;i+len-1<=n;++i){
			int j=i+len-1;
			for(int k=j+1;k<=n;++k){
				memcpy(tmp[dep],a,sizeof a);
				for(l=j+1,r=i;l<=k;l++,r++) a[r]=tmp[dep][l];
				for(l=i;l<=j;++l,++r) a[r]=tmp[dep][l];
				dfs(dep+1); if(flg) return;
				memcpy(a,tmp[dep],sizeof a);
			}
		}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n; mdep=0; flg=0;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(mdep=gj();mdep<=5;++mdep){
			if(mdep>=5){
				cout<<"5 or more\n";
				break;
			}
			dfs(0); if(flg) break;
		}
	}
	return 0;
}
```

---

## 作者：ganyu1 (赞：1)

# P10488 Booksort 题解
## 思路分析
这道题很明显是一道 DFS ，一层一层搜索如何移动书本，但是虽然它的数据很小，我们不知道移动哪些以及移动到哪里，单纯 DFS 的话是包爆掉的。再仔细一看，只需要知道四步以内能否达到目标，而且数据 $1 \leq n \leq 15$ ，那必然就是迭代加深搜索了。然而，单是这样依旧不够，因为需要枚举的地方有点多，因此还要加一点点剪枝。
## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 21
using namespace std;
int T,n,a[N];

template<typename T>inline void read(T &a){
    char c=getchar();T x=0,f=1;
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    a=f*x;
}//快读，我本来没加然后被卡了~ 

int dif(){
	int res=0;
	for(int i=1;i<=n;i++){
		if(a[i]!=i) res++;
	}
	return res;
}//求出还有多少本书不符合目标 

void modify(int s,int l,int e){
	int x[N],cnt=0;
	for(int i=l+1;i<=e;i++) x[++cnt]=a[i];
	for(int i=s;i<=l;i++) x[++cnt]=a[i];
	for(int i=e;i>=s;i--) a[i]=x[cnt--];
	return ;
}//将几本书插入另一个地方可以看作将两部分互换，这样会好写很多 

bool dfs(int step,int mstep){
	if(step==mstep){
		if(!dif()) return true;
		return false;
	}
	int aa[N];
	for(int i=1;i<=n;i++) aa[i]=a[i];
	for(int i=1;i<=n;i++){
		for(int l=i;l<=n;l++){
			for(int j=l;j<=n;j++){
				modify(i,l,j);
				if(3*step+dif()<=3*mstep&&dfs(step+1,mstep)) return true;
				//剪枝，每一步最多能增加三本位置正确的书，如果3*step+dif()<=3*mstep则一定无答案
				for(int k=1;k<=n;k++) a[k]=aa[k];
			}
		}
	}
	return false;
}

signed main(){
///	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	read(T);
	while(T--){
		read(n);
		bool f=true;
		for(int i=1;i<=n;i++){
			read(a[i]);
			if(a[i]!=a[i-1]+1) f=false;
		}
		if(f){
			cout<<"0\n";
			continue;
		}//有可能刚开始就排好了 
		for(int i=1;i<=4;i++){ 
			if(dfs(0,i)){
				cout<<i<<endl;
				f=true;
				break;
			}
		}
		if(f) continue;
		cout<<"5 or more\n";
	}
	return 0;
}

```

---

## 作者：_Warfarin_ (赞：0)

### 初见分析
注意到多于 $ 5 $ 次时，并不需要输出详细次数，直接考虑是能在 $ 5 $ 次内完成。             
估计搜索次数：      
$ \frac{\sum_{i=1}^{n}(n-i) \times(n-i+1)}{2}=\frac{15 \times 14+14 \times 13 \times \cdots \times 2 \times 1}{2}=560 $。    
直接暴力的话，为 $ 560^{4} $，显然会炸，综上考虑 IDAStar 。
#### 估价函数设计 
假设有 $ n $ 个位置使得相邻的位置并不是相差 $ 1 $，而每次移动会改变 $ 3 $ 个数后面的数，所以操作数量为 $ \left\lceil\frac{ n }{3}\right\rceil=\left\lfloor\frac{ n +2}{3}\right\rfloor $。

### AC代码
```
#include <bits/stdc++.h>

#define ll long long
#define io cin.tie(0),cout.tie(0),ios::sync_with_stdio(false)
#define ri register int

using namespace std;

const int N = 15;

int n;
int a[N], w[5][N];

inline int f()
{
	int res = 0;
	for (ri i = 0; i + 1 < n; i ++ )
		if (a[i + 1] != a[i] + 1)
			res ++ ;
	return (res + 2) / 3;
}

inline bool dfs(int tmp, int maxs)
{
	if (tmp + f() > maxs)
		return false;
	if (f() == 0)
		return true;
	for (int l = 0; l < n; l ++ )
		for (int r = l; r < n; r ++ )
			for (int k = r + 1; k < n; k ++ )
			{
				memcpy(w[tmp], a, sizeof a);
				int x, y;
				for (x = r + 1, y = l; x <= k; x ++, y ++ )
					a[y] = w[tmp][x];
				for (x = l; x <= r; x ++, y ++ )
					a[y] = w[tmp][x];
				if (dfs(tmp + 1, maxs))
					return true;
				memcpy(a, w[tmp], sizeof a);
			}
	return false;
}

int main()
{
	io;
	int t;
	cin >> t;
	while (t -- )
	{
		cin >> n;
		for (int i = 0; i < n; i ++ )
			cin >> a[i];
		int depth = 0;
		while (depth < 5 && !dfs(0, depth))
			depth ++ ;
		depth >= 5 ? cout << "5 or more" << endl : cout << depth << endl;
	}
	return 0;
}
```

---

