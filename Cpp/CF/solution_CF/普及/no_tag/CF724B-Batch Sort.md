# Batch Sort

## 题目描述

现在给你一个  **_n_**  行  **_m_**  列的数字矩阵，每一行的元素是一个1到m的全排列。

你可以在每一行中选取两个元素并交换它们，但是每一行这样的操作不能超过一次。

同样的，你可以选择两列并交换它们，这样的操作不能超过1次。

显而易见的，你一共可以进行  **_0_**  到  **_n+1_**  次这样的操作。而且操作顺序可以任意。

现在给你的任务是判断能否在进行一系列操作后使得每一行的数字从小到大排列，即  **_1_**  到  **_m_**  。换句话说，就是能否按照给出的规则进行操作使每一行单调递增。

## 样例 #1

### 输入

```
2 4
1 3 2 4
1 3 4 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 4
1 2 3 4
2 3 4 1
3 4 1 2
4 1 2 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3 6
2 1 3 4 5 6
1 2 4 3 5 6
1 2 3 4 6 5
```

### 输出

```
YES
```

# 题解

## 作者：GWBailang (赞：4)

#### [原题传送](https://www.luogu.com.cn/problem/CF724B)
非常经典的一句话：**暴力出奇迹**。

如果没有“可以交换任意两列”这个条件，那么方法便一目了然。每一行最多只能让两个数交换一次，所以对于第 $i$ 行，判断有几个 ```a[i][j]!=j``` 的数，这个数量必须为 $0$ 或 $2$ 才能交换一次或不用交换使得第 $i$ 行变成 $1$ 到 $m$ 的全排列。

所有的 $n$ 行都这样判断一遍，有一行不行就无法满足题意。

然后把“可以交换任意两列”这个条件加上，也就是用两层循环来枚举交换哪两列。

最后复杂度为 $O(nm^3)$，题目时限为 2 秒，足够了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[25][25];
long long n,m;
void huan(long long x,long long y){//交换两列
	for(long long i=1;i<=n;i++){
		swap(a[i][x],a[i][y]);
	}
}
bool hanshu(){//判断
	long long cnt;
	for(long long i=1;i<=n;i++){
		cnt=0;
		for(long long j=1;j<=m;j++){
			if(a[i][j]!=j)cnt++;
		}
		if(cnt!=2&&cnt!=0)return false;
	}
	return true;
}
int main(){
	cin>>n>>m;
	for(long long i=1;i<=n;i++){
		for(long long j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	if(hanshu()){//不交换任意两列也可以，所以需要特判一下
		cout<<"YES\n";
		return 0;
	}
	for(long long i=1;i<m;i++){//枚举交换哪两列
		for(long long j=i+1;j<=m;j++){
			huan(i,j);
			if(hanshu()){//如果可以就直接输出即可
				cout<<"YES\n";
				return 0;
			}
			huan(i,j);
		}
	}
	cout<<"NO\n";
	return 0;
}
```


---

## 作者：Chtholly_Tree (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF724B)

## Part 1 题意

给定 $n$ 行 $m$ 列的矩阵，保证每行的数字为 $1 \to m$ 的全排列并且不重复，问是否能交换任意两列的每行的两个元素让每行变成 $1 \to m$。

## Part 2 分析

因为交换任意两列会影响较多的元素，所以可以先枚举交换的两列。交换后，在判断是否合法。

我们可以写一个子程序，交换两列；也可以再写一个子程序，判断是否合法。

对于交换过的列，我们可以判断 $a_{i, j}$ 是否等于 $j$，如果不等于，则 $cnt$ 加 $1$。

最后判断 $cnt$ 是否为 $0$ 或 $2$ 即可，如果 $cnt$ 为 $0$ 的情况下就是全部成立；$cnt$ 为 $2$ 就是有两个元素不同，交换即可。

## Part 3 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, m, a[30][30];

void swaplie (int (&b)[30][30], int x, int y) { // 交换第 x 列和第 y 列
                  // 一定要引用！！！
	for (int i = 1; i <= n; i++) {
		swap(b[i][x], b[i][y]);
	}
}

bool check (int b[30][30]) { // 验证函数
	for (int i = 1; i <= n; i++) {
		int cnt = 0; // cnt 的定义如题目分析
		for (int j = 1; j <= m; j++) { // 如题目分析
			if (b[i][j] != j) cnt++;
		}
		if (!(cnt == 0 || cnt == 2)) return 0; // 如果 cnt 既不等于 0 也不等于 2 退出
	}
	return 1;
}

signed main () {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	if (check(a)) { // 如果不换就成功，退出
		cout << "YES";
		return 0;
	}
	for (int i = 1; i < m; i++) { // 枚举交换的两列
		for (int j = i + 1; j <= m; j++) { // 枚举交换的两列
			swaplie(a, i, j); // 交换
			if (check(a)) { // check 成功
				cout << "YES";
				return 0;
			}
			swaplie(a, i, j); // 换回来
		}
	}
	cout << "NO";
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/123036892)

---

## 作者：ryl_ahu (赞：2)

这道题直接暴力即可。

先暴力枚举哪两列可以交换，交换以后再加一个判断就可以了。

问题在于如何怎么判断：因为题中描述“每一行只能交换两个数”，所以我们看第 $i$ 行 $j$ 列的数等不等于 $j$。只有 $0$（完好无损）个数或 $2$（交换一次）个数的时候才能保证全排列。所以我们先套双重循环，然后在判断 $i$ 行 $j$ 列是不是 $j$。如果不是的话 ```ans++```。判断 ans 是不是 $0$ 或 $2$。

---

 大纲：

- 输入。（没啥好说的）
- 先判断一开始的数组是不是全排列。
- 然后爆搜：

	$1$.先交换。
    
   $2$.交换后判断如果成立，直接输出。
   
   $3$.再交换回来。
- 华丽结束。

---

最后提醒一句：十年 OI 一场空，不开__________见祖宗。

---
### 你们最爱的总代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m;
long long a[30][30];
bool h() {
	long long ans = 0;
	for (long long i = 1; i <= n; i++) {
		ans = 0;
		for (long long j = 1; j <= m; j++) {
			if (a[i][j] != j) ans++;
		}
		if (ans == 1 or ans >= 3) return false;
	}
	return true;
}
int main() {
	cin >> n >> m;
	for (long long i = 1; i <= n; i++) {
		for (long long j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	if (h() == true) {
		cout << "YES" << endl;
		return 0;
	}
	for (long long i = 1; i <= m + 1; i++) {
		for (long long j = i + 1; j <= m; j++) {
			for (long long k = 1; k <= n; k++) {
				swap(a[k][i], a[k][j]);
			}
			if (h() == true) {
				cout << "YES" << endl;
				return 0;
			}
			for (long long k = 1; k <= n; k++) {
				swap(a[k][i], a[k][j]);
			}
		}
	}
	cout << "NO" << endl;
	return 0;
}
```
---
祝大家做出这道~~水~~题。

---

## 作者：伟大的王夫子 (赞：2)

此题做不出来一定是没有掌握暴力枚举的精髓

首先，我们不交换列，根据每一列判断是否可行。如果不进行判断，那么样例3会输出错误。

具体判断方法：$\forall i \in [1,n]$ 若存在$2$个以上$j\in[1,m]$使得$a_{i,j} \not = j$，那么不可行

（其实就是判断有几个数对不上全排列，因为只能交换一次，所以最多只有两个对不上才可行，可以把它们交换变成全排列）

若每行判断过来都可行，即为可行

若不行的话，我们枚举要交换的两列$i,j(1 \le i < j \le m)$然后再进行上述判断。

总的来说就是一个大暴力

注意细节即可

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, a[110][110];
int main() {
	cin >> n >> m;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			cin >> a[i][j];
	bool flag = 1;
	for (register int k = 1; k <= n; ++k) {
		int cnt = 0;
		for (register int l = 1; l <= m; ++l)
			cnt += a[k][l] != l;
		if (cnt > 2) {
			flag = 0;
			break;
		}
	}
	if (flag) {
		puts("YES");
		return 0;
	}
	for (register int i = 1; i <= m; ++i)
		for (register int j = i + 1; j <= m; ++j) {
			for (register int k = 1; k <= n; ++k)
				swap(a[k][i], a[k][j]);
			bool flag = 1;
			for (register int k = 1; k <= n; ++k) {
				int cnt = 0;
				for (register int l = 1; l <= m; ++l)
					cnt += a[k][l] != l;
				if (cnt > 2) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				puts("YES");
				return 0;
			}
			for (register int k = 1; k <= n; ++k)
				swap(a[k][i], a[k][j]);
		}
	puts("NO");
}
```

时间复杂度$O(nm^3)$可以通过

---

## 作者：朱屹帆 (赞：2)

### 题目：[CF724B Batch Sort](https://www.luogu.com.cn/problem/CF724B)
### 题意：我们可以简化一下题意：

- 给定 $n$ 个长为 $m$ 的全排列，允许每一个全排列中任意两个数值位置互换，同时允许一次将所有全排列中的两列互换，即所有全排列中的同样两个位置的数值进行交换。


### 思路：
相信这一题如果**删去"允许一次将所有全排列中的两列互换"条件**，那么这一题就很简单了，我们可以 $O(n*m)$ 将 $n$ 个全排列全部扫一遍，用 $dif (different) $ 把所有不再自己应该位置上的数值计数。

- 因为每一个全排列都只能互换一次，所以当有某个全排列的 $dif$ 计数不是 $2$ 或 $0$ 时，就意味着这个全排列**无法通过
小于 $1$ 次互换操作**满足题意。

- 我们可以先设 $ bool $ 类型的 $flag$ 为 $false$ ,即没有可解决的方案，直到每个全排列的 $dif$ 计数都是 $2$ 或 $0$ 时 $flag$ 变为 $true$ 可完成即可。

```cpp
	long long dif=0;
	for(long long i=1;i<=n;i++,dif=0){
		for(long long j=1;j<=m;j++){
			if(s[i][j]!=j)dif++;
			if(dif>=3)return ;
		}
		if(dif==1)return ;
	}
	flag=true;
```


- 但题目中多了一个条件：即也**允许一次将所有全排列中的两列互换**，既然我们可以以 $O(n*m)$ 的复杂度解决**每一个全排列都只能互换一次**的问题，那么我们不妨**提前将要换的两行枚举处理出来**，在进行原先每一个全排列最多互换一次的操作，便可解决此题。

- 代码片段中 $use()$ 为处理枚举的每行的列数， $need()$为恢复全排列。

```cpp
void need(long long x,long long y){
	for(long long i=1;i<=n;i++)
		swap(s[i][x],s[i][y]);
	return ;
}
void use(long long x,long long y){
	for(long long i=1;i<=n;i++)
		swap(s[i][x],s[i][y]);
	return ;
}
void pd(long long x,long long y){
	use(x,y);
	... //中间的return前面也要加need(x,y)
	need(x,y);flag=true;
	return ;
}
int main(){
	...
	for(i=1;i<=(m-1);i++){
		for(j=i+1;j<=m;j++){
			pd(i,j);
			if(flag==true){i=m;break;}
		}
	}
	...
}
```

### Code：
```cpp
//具体操作方向见上文
#include<bits/stdc++.h>
#define Yes "YES"
#define No "NO" 
using namespace std;
long long read(){
	long long q=0,w=1;
	char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')q=q*10+ch-'0',ch=getchar();
	return q*w;
}

const long long N = 1e2+5;
long long n,m,s[N][N];
long long i,j,k;

bool flag=false;
long long step;
void need(long long x,long long y){
	for(long long i=1;i<=n;i++)
		swap(s[i][x],s[i][y]);
	return ;
}
void use(long long x,long long y){
	for(long long i=1;i<=n;i++)
		swap(s[i][x],s[i][y]);
	return ;
}
void pd(long long x,long long y){
	long long dif=0;
	use(x,y);
	for(long long i=1;i<=n;i++,dif=0){
		
		for(long long j=1;j<=m;j++){
			if(s[i][j]!=j)dif++;
			if(dif>=3){need(x,y);return ;}
		}
		if(dif==1){need(x,y);return ;}
	}
	need(x,y);flag=true;
	return ;
}
int main(){
	n=read(),m=read();
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			s[i][j]=read();
	pd(0,0);
	if(flag==true){
		cout<<Yes<<endl;
		return 0;
	}
	for(i=1;i<=(m-1);i++){
		for(j=i+1;j<=m;j++){
			pd(i,j);
			if(flag==true){i=m;break;}
		}
	}
	if(flag==true)cout<<Yes<<endl;
	else cout<<No<<endl;
	return 0;
}
```
### 注：
- 这一题数据较小，适合**暴力**；

- 时间复杂度： $O((m*m)*n*m)$

---

## 作者：Inker (赞：2)

暴力枚举交换哪两列，再逐行check能否微调使其成立。
```cpp
#include<cstdio>
int g[30][30],n,m;

bool check()
{
    int cnt;
    for(int i=1;i<=n;i++)
    {
        cnt=0;
        for(int j=1;j<=m;j++)
        {
            if(g[i][j]==j)continue;
            if(j==g[i][g[i][j]])cnt++;
            else return 0;
        }
        if(cnt>2)return 0;
    }
    return 1;
}

void swap(int &a,int &b)
{
    int t=a;a=b;b=t;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&g[i][j]);
        }
    }
    bool ans=check();
    for(int i=1;i<m;i++)
    {
        if(ans)break;
        for(int j=i+1;j<=m;j++)
        {
            for(int k=1;k<=n;k++)swap(g[k][i],g[k][j]);
            if(check()){ans=1;break;}
            for(int k=1;k<=n;k++)swap(g[k][i],g[k][j]);
        }
    }
    if(ans)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}

```

---

## 作者：Otue (赞：1)

## 思路
**难点在于分析题意（**

没看清题目的我重复一遍：
* 选择一行中的两个整数并交换它们。此操作，每行**最多只能执行一次**。
* 选择列表中的两列并交换它们。此操作，**最多只能执行一次**。

交换列只能执行一次，那么枚举交换的哪两条列即可。

又因为一行最多交换一次，那么不与 $1,2,3,...,m$ 相等的数最多有 $2$ 个。

复杂度 $O(n\times m^3)$，而 $n,m\leq 20$，完全可以过。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

int n, m, a[25][25];

bool check() {
    for (int i = 1; i <= n; i++) {
        int r = 0;
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != j) r++;  
        }
        if (r > 2) return 0;  // 每行最多有2个不符合要求的数
        // 但是不可能只有1个不符合要求的数，原因很简单
    }
    return 1;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    }
    for (int i = 1; i <= m; i++) {  
        for (int j = i; j <= m; j++) {  // 暴力枚举两条列
            // 若i=j，那么表示不交换
            for (int k = 1; k <= n; k++) swap(a[k][i], a[k][j]);
            if (check()) {
                puts("YES");
                exit(0);
            }
            for (int k = 1; k <= n; k++) swap(a[k][i], a[k][j]);
        }
    }
    puts("NO");
}
```

---

## 作者：pomelo_nene (赞：1)

还是一道暴力好题 仍然就是暴力枚举区间进行交换列，然后判断每行是否可以通过一次交换变回严格递增

因为我们两个操作不会互相干扰，所以我们先交换列（时间更短）

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
int n,m,a[25][25];
void getChanged(int x,int y){for(int i=1;i<=n;++i)	swap(a[i][x],a[i][y]);}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)	for(int j=1;j<=m;++j)	scanf("%d",&a[i][j]);
	for(int i=1;i<=m;++i)
	{
		for(int j=i;j<=m;++j)
		{
			getChanged(i,j);
			bool flag=true;
			for(int k=1;k<=n;++k)
			{
				bool fail=false;
				int tot=0;
				for(int l=1;l<=m;++l)
				{
					if(l==a[k][l])	continue;
					if(l==a[k][a[k][l]])	++tot;
					else
					{
						flag=false;
						fail=true;
						break;
					}
				}
				if(fail)	break;
				if(tot>2)
				{
					flag=false;
					break;
				}
			}
			if(flag)	return puts("YES")&0;
			getChanged(i,j);
		}
	}
	puts("NO");
	return 0;
}
```

---

## 作者：_775spacing747_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF724B)
# 1 题意
给定一个 $n$ 行 $m$ 列的矩阵，每一次操作可以每一行中任意两个数值位置互换，也可以允许一次将所有行中的两列交换，即所有行中的同样两个位置的数值交换。请问否能通过操作让每行变成单调递增？
# 2 思路
**暴力出奇迹，打表过样例。** 

这道题目~~仁慈~~的给了 $2$ 秒的时间限制，所以我们可以直接暴力枚举交换哪两列，不过这样得不出正确答案，所以我们还需要挨个判断是否合理，不合理就进行调整。
# 3 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100][100];
//重头戏 
bool check()
{
	//返回1合理，返回0不合理 
    int s;
    for(int i=1;i<=n;i++)
    {
        s=0;//初始值！！！！ 
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]==j)continue;//相等退出 
            if(j==a[i][a[i][j]])s++;//计数器++ 
            else return 0;//如果不符合代表不合理，直接返回0 
        }
        if(s>2)return 0;//大于2了也不行 
    }
    return 1;//最后肯定合理 
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)cin>>a[i][j];
    bool f=check();//先看看原矩阵合不合理 
    for(int i=1;i<m;i++)
    {
        if(f)break;//合理退出 
        for(int j=i+1;j<=m;j++)//开始枚举 
        {
            for(int k=1;k<=n;k++)swap(a[k][i],a[k][j]);//交换 
            if(check())//若合理可以直接退出 
			{
				f=1;
				break;
			}
			//不合理，进行调整 
            for(int k=1;k<=n;k++)swap(a[k][i],a[k][j]);//进行交换 
        }
    }
    if(f)cout<<"YES";//能的话f=1 
    else cout<<"NO";//否则f=0 
    return 0;//华丽结束 
}
```
## [AC 记录](https://www.luogu.com.cn/record/132177779)

---

## 作者：chenyanbing2023 (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF724B)

思路非常简单，分两步考虑。

先考虑不用交换列的情况，那么只需要关心每行的数字是否在自己的位置上。记下不在自己的位置上的数字个数，如果大于 2 则说明至少要交换 2 次。显然是不符合条件的。

现在再来考虑交换列的情况，暴力枚举所有列交换的可能 ~~正所谓“暴力出奇迹”~~ ，再看看交换过后是否符合每行只需要交换两个数就行了。如果每行交换的大于 2 个数，则输出 `YES`，否则输出 `NO`。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=22;
int G[25][25];
int n,m;
bool BatchSort(int G[25][25])
{
	for(int i=1;i<=n;i++)
	{
		int cnt=0;//计算次数
		for(int j=1;j<=m;j++)
		{
			if(G[i][j]!=j)
			{
				cnt++;
			}
		}
		if(cnt>2)
		{
			return 0;
		}
	}
	return 1;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&G[i][j]);
		}
	}
	if(BatchSort(G))
	{
		puts("YES\n");
		continue;
	}
	bool flag=0;//判断能否操作成功
	for(int i=1;i<=m;i++)
	{
		if(flag)
		{
			break;//如果已经可以就退出
		}
		for(int j=i+1;j<=m;j++)
		{
			if(flag)
			{
				break;
			}
			for(int k=1;k<=n;k++)
			{
				swap(G[k][i],G[k][j]);//交换
			}
			if(BatchSort(G))
			{
				flag=true;
			}
			for(int k=1;k<=n;k++)
			{
				swap(G[k][i], G[k][j]);//换回去
			}
		}
	}
	printf("%s\n", flag?"YES":"NO"); //三目运算符，如flag为真则返回"YES"，否则返回"NO"
	return 0;
}
```


---

## 作者：2021sunzishan (赞：0)

## 题目大意：
给定一个 $n\times m$ 的矩阵，每一行都是 $1\sim m$ 的全排列。可以交换两列一次，每行也可以交换两个数一次。问可不可以交换后，使每列的数都从小到大排序，及第 $i$ 个数为 $i$。

## 思路：
看看数据范围：$ 1\le n,m\le 20 $，看看时限，还不暴力？

直接枚举交换哪两列，交换完了以后判断可不可以。

当然，处理每一行的交换也很简单。每一行当中，如果有且仅有 $2$ 个数不符合，就可以交换他们。全部符合也可以，不用交换。

最后还要注意，需要特判一下，原始的矩阵满不满足要求。

那么以上就是本题的思路了，如果还是不懂，那就看代码吧！

**切勿抄袭！！！**

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[25][25];
inline int read() {//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
bool pd() {//判断符不符合
	for(int i=1; i<=n; i++){
		int k=0;//累加每一行不符合的次数
		for(int j=1; j<=m; j++)
			if(a[i][j]!=j)
				k++;
		if(k!=2&&k!=0)return 0;
	}
	return 1;
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	if(pd()){//特判哦~
		printf("YES\n");
		return 0;
	}
	for(int i=1;i<m;i++)
		for(int j=i+1;j<=m;j++){
			for(int k=1;k<=n;k++)//交换
				swap(a[k][i],a[k][j]);
			if(pd()){//判断一下
				printf("YES\n");
				return 0;
			}
			for(int k=1;k<=n;k++)//换回来
				swap(a[k][i],a[k][j]);
		}
	printf("NO\n");
	return 0;
}

```
完结~

---

## 作者：TerryGong (赞：0)

# CF742B 题解

这是一道有意思的异或题目。

---
### 题意

给定序列 $A$ 和一个整数 $x$ ，求 $A_i\oplus A_j=x$ 的组数。

### 知识

- `a^b=!(a==b)` （ ^是大多数语言中异或的符号）

- 异或也叫半加运算，其运算法则相当于不带进位的二进制加法。~~容易理解~~

---

本题目需要注意的是异或( $xor,eor,\oplus$ )的亿些好用的性质。

> 如果 $a\oplus b=c$ 那么 $a\oplus c=b$ ， $b\oplus c=a$ (读者可以自行证明，此处不再赘述)。

所以如果 $i\oplus j = x$ 那么 $i\oplus x =j$ ，所以只需要统计 $i\oplus x = j$ 的数量，全部累乘即可。于是我们可以读入 $t$ ，查询 $a_{x\oplus  t}$ 的数量，然后累加，就可以达到目的。

建立一个 $map$ （或者查找数组），注意使用 $long\ long$ ，此题可过。

```cpp
#include <map>
#include <cstdio>
using namespace std;
#define N 100010
int x,n;
long long ans;
map<int,long long> a;
int main(){
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++){
		int t;
		scanf("%d",&t);
		ans+=a[x^t];
		++a[t];
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF724B)

[CF's link](https://codeforces.com/problemset/problem/724/B)

#### 题意：

现在给你一个 $n$ 行 $m$ 列的数字矩阵，每一行的元素是一个1到m的全排列。可以在每一行中选取两个元素并交换它们，但是每一行这样的操作不能超过 $1$ 次。同样的，也可以选择两列并交换它们，这样的操作不能超过 $1$ 次，使得最后每行数字都单调递增。

#### Solution：

暴力枚举要交换的两个序列，然后逐行判断是否能通过 $1$ 次交换使得这行单调递增。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-15 21:06:22 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-15 21:22:29
 */
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=25;
int n,m,a[N][N],b[N][N],sum;
bool flag=0;
void work(int x,int y){
	flag=0;
	FOR(i,1,n) FOR(j,1,m) a[i][j]=b[i][j];
	FOR(i,1,n) swap(a[i][x],a[i][y]);
	FOR(i,1,n){
		sum=0;
		FOR(j,1,m) if(j!=a[i][j]) sum++;
		if(sum>2){
			flag=1;
			break;
		}
	}
	if(!flag){
		puts("YES");
		exit(0);
	}
}
int main(){
	n=read();m=read();
	FOR(i,1,n) FOR(j,1,m) b[i][j]=a[i][j]=read();
	FOR(i,1,n){
		sum=0;
		FOR(j,1,m) if(j!=a[i][j]) sum++;
		if(sum>2){
			flag=1;
			break;
		}
	}
	if(!flag){
		puts("YES");
		return 0;
	}
	FOR(i,1,m){
		FOR(j,i+1,m){
			work(i,j);
		}
	}
	puts("NO");
	return 0;
}
```



---

