# Young Table

## 题目描述

You've got table $ a $ , consisting of $ n $ rows, numbered from 1 to $ n $ . The $ i $ -th line of table $ a $ contains $ c_{i} $ cells, at that for all $ i $ $ (1&lt;i<=n) $ holds $ c_{i}<=c_{i-1} $ .

Let's denote $ s $ as the total number of cells of table $ a $ , that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF237B/41032ee9d28de3347d7865d06640fb12d664cefb.png). We know that each cell of the table contains a single integer from $ 1 $ to $ s $ , at that all written integers are distinct.

Let's assume that the cells of the $ i $ -th row of table $ a $ are numbered from 1 to $ c_{i} $ , then let's denote the number written in the $ j $ -th cell of the $ i $ -th row as $ a_{i,j} $ . Your task is to perform several swap operations to rearrange the numbers in the table so as to fulfill the following conditions:

1. for all $ i,j $ $ (1&lt;i<=n; 1<=j<=c_{i}) $ holds $ a_{i,j}&gt;a_{i-1,j} $ ;
2. for all $ i,j $ $ (1<=i<=n; 1&lt;j<=c_{i}) $ holds $ a_{i,j}&gt;a_{i,j-1} $ .

In one swap operation you are allowed to choose two different cells of the table and swap the recorded there numbers, that is the number that was recorded in the first of the selected cells before the swap, is written in the second cell after it. Similarly, the number that was recorded in the second of the selected cells, is written in the first cell after the swap.

Rearrange the numbers in the required manner. Note that you are allowed to perform any number of operations, but not more than $ s $ . You do not have to minimize the number of operations.

## 样例 #1

### 输入

```
3
3 2 1
4 3 5
6 1
2
```

### 输出

```
2
1 1 2 2
2 1 3 1
```

## 样例 #2

### 输入

```
1
4
4 3 2 1
```

### 输出

```
2
1 1 1 4
1 2 1 3
```

# 题解

## 作者：__DayLight__ (赞：2)

## 前言
这是一种非常暴力的方法，见 [124ms &124.00KB](https://www.luogu.com.cn/record/156244975)。
## 思路
由于操作步数只要求**不超过 $s$**，所以考虑将表格 $a$ 中的数进行**升序**处理。

例如：
```
4 3 5
6 1
2
```
升序得：
```
1 2 3
4 5
6
```
因为每个位置只会交换一次，所以最多会交换 $s$ 次。

各种细节见代码。

------------
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s;
int c[55],x[2505],y[2505],p[2505],q[2505];
int t[55][55];
//要注意的是，每次操作都会影响后面的操作。
//所以记录原表格的 t 数组在每次记录后也要发生变化； 
//也就是说 t 要模拟交换的过程 。 
int a[2505];//为了方便排序，表格 a 用一维数组存放。 
signed main(){
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>c[i];
	for(int i=1; i<=n; i++)
		for(int j=1; j<=c[i]; j++)
		{
			cin>>a[++s];
			t[i][j]=a[s];
		}
	sort(a+1,a+1+s);
	s=0; 
	for(int i=1; i<=n; i++)
		for(int j=1; j<=c[i]; j++)
		{
			//该做法是基于每个数都不同的情况下。 
			s++;
			if(a[s]!=t[i][j])//两个数不同意味着交换了一次。 
			{
				m++;
				for(int k=1; k<=n; k++)//在表格中寻找两个数分别处于的位置 。 
					for(int l=1; l<=c[k]; l++)
					{
						if(a[s]==t[k][l])x[m]=k,y[m]=l;
						if(t[i][j]==t[k][l])p[m]=k,q[m]=l;
					}
					
				swap(t[x[m]][y[m]],t[p[m]][q[m]]);
				//模拟交换。	
			}
		}
	cout<<m<<'\n';
	for(int i=1; i<=m; i++)
		cout<<x[i]<<' '<<y[i]<<' '<<p[i]<<' '<<q[i]<<'\n';
	return 0;
} 
```

---

## 作者：_edge_ (赞：1)

不得不说，这题目的暴力还是稍微有一点点技巧的。

首先我们需要明确，这是一个 $1$ 到 $s$ 的排列，这对于后面记录位置相当有帮助。

然后这题目的数据范围为 $1 \le n \le 50$ 和 $1 \le c_i \le 50$ 。

这样就可以进行暴力了。

我们将最小的从最左上开始排，次小的排到右边，以此类推。

然后遇到边界就换下一行的头一个。

|  1|  2|3  |
| -----------: | -----------: | -----------: |
|  4| 5 | 6 |
| 7 |8  |  9|

就相当于这样，因为我们知道前一行的最大值必定都是小于后一行的最小值，于是正确性也有了保证。

然后我们就可以进行一个暴力的交换位置了。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=55;
int n,c[INF],sum,a[INF*INF],b[INF*INF],Map[INF][INF],ans,ans1[INF*INF][11];
signed main()
{
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%d",&c[i]),sum+=c[i];
        for (int i=1; i<=n; i++) {
                for (int j=1; j<=c[i]; j++) {
                        int x=0; scanf("%d",&x);
                        a[x]=i; b[x]=j; Map[i][j]=x;
                }
        }
        int x=1,y=1;
        for (int i=1; i<sum; i++) {
                if (a[i]==x && b[i]==y) {
                        if (y==c[x]) {
                                x++; y=1;
                        }
                        else y++;
                        continue;
                }
                ans++; ans1[ans][0]=x; ans1[ans][1]=y;
                ans1[ans][2]=a[i]; ans1[ans][3]=b[i];
                swap(a[Map[x][y]],a[i]);
                swap(b[Map[x][y]],b[i]);
                swap(Map[x][y],Map[a[Map[x][y]]][b[Map[x][y]]]);
                if (y==c[x]) {
                        x++; y=1;
                }
                else y++;
                // cout<<x<<" "<<y<<"\n";
        }
        cout<<ans<<"\n";
        for (int i=1; i<=ans; i++) cout<<ans1[i][0]<<" "<<ans1[i][1]<<" "<<ans1[i][2]<<" "<<ans1[i][3]<<"\n";
        return 0;
}

```


---

## 作者：JimmyLee (赞：1)

# CF237B Young Table 题解

## 题目描述

[CF237B Young Table](https://www.luogu.com.cn/problem/CF237B)

## 题目解法

题目中要求满足以下条件：

对所有的 $i,j (1< i\leq n,1\leq j\leq c_i)$，满足 $a_{i,j}>a_{i-1,j}$

对所有的 $i,j (1\leq i\leq n,1 < j\leq c_i)$，满足 $a_{i,j}>a_{i,j-1}$

不难发现，对于样例：

```plaintext
4 3 5
6 1
2
```

将该表格进行排序后是满足条件的，如下：

```plaintext
1 2 3
4 5
6
```

又因为题目中给的是一个全排列，可以先记录好数字的位置然后再交换位置即可。

细节就看代码吧。

# Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define maxn 52

int len[maxn];
int mp[maxn][maxn];

void upd(int &x, int &y) // 表格中向后移动一步
{
    if(y==len[x]) y=1, x++;
    else y++;
}

pair<int, int> pos[maxn*maxn]; // 记录坐标
struct ans{int a, b, c, d;};
vector<ans> vc; // 记录答案

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>len[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=len[i];j++)
            cin>>mp[i][j], pos[mp[i][j]]={i, j};
    int sum=accumulate(len+1, len+1+n, 0); // 求出数字个数
    int x=0, y=0;
    for(int i=1;i<sum;i++)
    {
        upd(x, y); // 移动一步
        if(mp[x][y]==i) continue; // 特判
        vc.push_back({x,y,pos[i].first,pos[i].second});
        int l=mp[x][y];
        swap(mp[x][y], mp[pos[i].first][pos[i].second]);
        swap(pos[l], pos[i]);
    }
    cout<<vc.size()<<'\n';
    for(auto [a, b, c, d]:vc) cout<<a<<' '<<b<<' '<<c<<' '<<d<<'\n'; // 输出答案
}
```

---

## 作者：729hao (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF237B)
比较容易想的一道题目，但本蒟蒻用了将近半个小时才 A 掉这道题。

------------
因为

>不必寻求最优

显然，按照 $1,2,3,...,s-1,s$ 的顺序依次放入 $a_{1,1},a_{1,2},...,a_{1,c_1-1},a_{1,c_1},a_{2,1},...,a_{2,c_2},a_{c_3,1},...,a_{n,c_n}$ 一定满足题目要求。

再考虑交换次数，最坏情况下每次交换只能将一个数放到对应的位置中，但确定了 $s-1$ 后，$s$ 自然会被放在 $a_{n,c_n}$ 的位置。所以最多需要 $s-1$ 次交换，正好满足题目

>你应当使用少于 $s$ 次交换

的要求。

------------
所以，我们只需要用一个数组 $pos$ 来记录每个数原本的位置，从 $1$ 开始扫到 $s$，如果不在对应位置则交换两个数即可。

AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s,c[2505],sq[2505][2505],pt;
struct P{
	int x,y;
}pos[2505];
struct ans{
	int x,y,p,q;
}A[2505];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
		s+=c[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=c[i];j++){
			scanf("%d",&sq[i][j]);
			pos[sq[i][j]].x=i;
			pos[sq[i][j]].y=j;
		}
	}
	int nx=1,ny=1;
	for(int i=1;i<=s;i++){
		if(pos[i].x!=nx||pos[i].y!=ny){//如果不对应 
			++pt;
			A[pt].x=nx;
			A[pt].y=ny;
			A[pt].p=pos[i].x;
			A[pt].q=pos[i].y;
			//注意还要更新被交换数的位置。因为数i之后不会再用到，所以i的位置不更新也不影响之后的操作 
			pos[sq[nx][ny]]=pos[i];
			sq[pos[i].x][pos[i].y]=sq[nx][ny];
		}
		ny++;
		if(ny>c[nx]){
			nx++;
			ny=1;
		}
	}
	printf("%d\n",pt);
	for(int i=1;i<=pt;i++)printf("%d %d %d %d\n",A[i].x,A[i].y,A[i].p,A[i].q);
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[Young Table](https://www.luogu.com.cn/problem/CF237B)
## 分析
看到复杂度很小，并且不是求最优解，直接枚举每个点，如果这个点不是它应该是的点 $k$，那就将当前的点与 $k$ 点交换，细节上运用映射的思路就可以了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y;
}p[50000];
int n;
int c[500];
int a[100][100];
struct an
{
	int tx,ty,fx,fy;
}ans[50000];
int cnt;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=c[i];j++)
		{
			scanf("%d",&a[i][j]);
			p[a[i][j]].x=i,p[a[i][j]].y=j; 
		}
	int id=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=c[i];j++)
		{
			if(a[i][j]!=id)
			{
				int tx=p[id].x,ty=p[id].y;
				cnt++;
				ans[cnt]=(an){i,j,tx,ty};//记录ans 
				swap(a[i][j],a[tx][ty]); 
				swap(p[id].x,p[a[tx][ty]].x);
				swap(p[id].y,p[a[tx][ty]].y);//这3个swap就是交换位置	
			}
			id++;
		}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d %d %d %d\n",ans[i].tx,ans[i].ty,ans[i].fx,ans[i].fy);
	return 0;
}
```


---

## 作者：Lovely_Elaina (赞：0)

一眼丁真，鉴定为若至题。

### 分析题面

易得将交换结果两两首尾相接得到一个 $1\sim s$ 的递增数列。 

比如样例一：

```DATA
1 2 3 
4 5 
6 
```

可以得到 `1 2 3 4 5 6`。

同时最重要的是要求操作少于 $s$ 就行，就相当于允许 $s-1$ 次操作。

那不就一个个交换就行了？

### 做法

开个 map，记录每个数字当前在的位置（单元格中的位置及单元格首尾相接拼在一起得到的序列中的位置）。

然后从第一个开始，如果当前位置要求的数字不在，就和应有数组进行一次交换，并将操作存在一个结构体里。

最后输出操作次数和操作。

```cpp
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;
const int N = 55;

struct node{
    pair<int,int > x;
    pair<int,int > y;
}ans[N*N];

// 数字 对应在数列中的位置 对应在单元格中的位置
map<int,pair<int,pair<int,int> > > t;

int n,c[N];
int s,a[N*N];

int cnt;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> c[i];
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= c[i]; j++){
            pair<int,pair<int,int> > p;

            cin >> a[++s];

            p.first = s;
            p.second.first = i;
            p.second.second = j;
            t[a[s]] = p;
        }
    }
    
    // sort(a+1,a+1+s);

    int cnt = 0;
    for(int i = 1; i <= s; i++){
        if(a[i] == i) continue;
        cnt++;
        ans[cnt].x = t[a[i]].second;
        ans[cnt].y = t[i].second;

        /*cout << t[i].second.first << " " << t[i].second.second << endl;
        cout << ans[cnt].x.first << " ";
        cout << ans[cnt].x.second << " ";
        cout << ans[cnt].y.first << " ";
        cout << ans[cnt].y.second << endl;*/

        int now = t[i].first;
        swap(t[a[i]],t[i]);
        swap(a[i],a[now]);
    }

    cout << cnt << endl;
    for(int i = 1; i <= cnt; i++){
        cout << ans[i].x.first << " ";
        cout << ans[i].x.second << " ";
        cout << ans[i].y.first << " ";
        cout << ans[i].y.second << endl;
    }
    return 0;
}
```

---

## 作者：tmp_get_zip_diff (赞：0)

本题其实就是一个暴力，没什么好说的，~~个人认为只要看懂了题目意思就能做~~。

这里有一个函数：`swap(int x,int y)`，实际上就是交换 $x$ 和 $y$ 的值，手写也可以。

具体解释在代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=305; //这里其实可以省一下空间，但是开的下，就懒得算了 
int n,c[N],sum,a[N],b[N],now[N][N],num,ans[N][10],f,x,y;

void change(int &x,int &y) //参数前面加个 &，更新后的值会直接传到数里面去 
{
    if(y==c[x])
	{
        x++;
		y=1;
    }
    else
		y++;
	return ;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
		cin>>c[i];
		sum+=c[i];
	}
    for(int i=1;i<=n;i++)
        for(int j=1;j<=c[i];j++)
		{
			cin>>f;
            a[f]=i;
			b[f]=j;
			now[i][j]=f;
        }
    x=1;
	y=1; //一定要初始化！！！ 
    for(int i=1;i<=sum-1;i++)
	{
        if(a[i]==x&&b[i]==y)
		{
			change(x,y); //移动当前位置 (x,y) 
            continue;
       	}
		ans[++num][0]=x;
		ans[num][1]=y;
        ans[num][2]=a[i];
		ans[num][3]=b[i];
        swap(a[now[x][y]],a[i]); //交换 
        swap(b[now[x][y]],b[i]);
        swap(now[x][y],now[a[now[x][y]]][b[now[x][y]]]);
        change(x,y);
    }
	cout<<num<<"\n";
    for(int i=1;i<=num;i++)
		cout<<ans[i][0]<<" "<<ans[i][1]<<" "<<ans[i][2]<<" "<<ans[i][3]<<"\n";
    return 0;
}
```

----

欢迎大佬提问！

---

## 作者：expecto__patronum (赞：0)

## 题意：
给你 $n$ 行，每行有 $c[i]$ 个数，每次你可以交换任意两个不同的数。现在要求每行非降序排列、每列非降序排列。让你输出交换方案。

思路：全 sort 下，因为 $m$ 限制为 $m$ 小于等于 $s$，那么我们从左到右、从上到下扫一遍就可以了。
## AC代码:
```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <queue>
#define CLR(a, b) memset(a, (b), sizeof(a))
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 1e6 + 1;
const int MOD = 1073741824;
const int INF = 0x3f3f3f3f;
void add(LL &x, LL y) { x += y; x %= MOD; }
int Map[60][60];
int a[4000];
int next[4000][4];
int c[60];
map<int, pii> fp;
int main()
{
    int n;
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; i++) {
            scanf("%d", &c[i]);
        }
        int top = 0; fp.clear();
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= c[i]; j++) {
                scanf("%d", &Map[i][j]);
                fp[Map[i][j]] = pii(i, j);
                a[top++] = Map[i][j];
            }
        }
        sort(a, a+top);
        int ans = 0; int id = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= c[i]; j++) {
                int x = fp[a[id]].fi;
                int y = fp[a[id]].se;
                if(a[id] != Map[i][j]) {
                    next[ans][0] = i;
                    next[ans][1] = j;
                    next[ans][2] = x;
                    next[ans++][3] = y;
                    fp[Map[i][j]] = pii(x, y);
                    swap(Map[i][j], Map[x][y]);
                }
                id++;
            }
        }
        printf("%d\n", ans);
        if(ans) {
            for(int i = 0; i < ans; i++) {
                printf("%d %d %d %d\n", next[i][0], next[i][1], next[i][2], next[i][3]);
            }
        }
    }
    return 0;
}
```
[博客](https://blog.csdn.net/chenzhenyu123456/article/details/51276158)

---

