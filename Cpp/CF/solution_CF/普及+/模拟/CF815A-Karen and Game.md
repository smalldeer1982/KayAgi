# Karen and Game

## 题目描述

On the way to school, Karen became fixated on the puzzle game on her phone!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/69d9eed46962e3cdadeae01ef67d1e4bd4bac050.png)The game is played as follows. In each level, you have a grid with $ n $ rows and $ m $ columns. Each cell originally contains the number $ 0 $ .

One move consists of choosing one row or column, and adding $ 1 $ to all of the cells in that row or column.

To win the level, after all the moves, the number in the cell at the $ i $ -th row and $ j $ -th column should be equal to $ g_{i,j} $ .

Karen is stuck on one level, and wants to know a way to beat this level using the minimum number of moves. Please, help her with this task!

## 说明/提示

In the first test case, Karen has a grid with $ 3 $ rows and $ 5 $ columns. She can perform the following $ 4 $ moves to beat the level:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/2c8fcc04f5be718b03f1b0d9aafd9c48834c67b9.png)In the second test case, Karen has a grid with $ 3 $ rows and $ 3 $ columns. It is clear that it is impossible to beat the level; performing any move will create three $ 1 $ s on the grid, but it is required to only have one $ 1 $ in the center.

In the third test case, Karen has a grid with $ 3 $ rows and $ 3 $ columns. She can perform the following $ 3 $ moves to beat the level:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/b5d0f3212dd0b57527e9775bb29c6dbecaf28d27.png)Note that this is not the only solution; another solution, among others, is col 1, col 2, col 3.

## 样例 #1

### 输入

```
3 5
2 2 2 3 2
0 0 0 1 0
1 1 1 2 1
```

### 输出

```
4
row 1
row 1
col 4
row 3
```

## 样例 #2

### 输入

```
3 3
0 0 0
0 1 0
0 0 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 3
1 1 1
1 1 1
1 1 1
```

### 输出

```
3
row 1
row 2
row 3
```

# 题解

## 作者：Lian_zy (赞：3)

非常简单的一道 模拟 + 贪心。

题目说给你一个初始全为零的 $n \times m$ 的方格，每次操作可以使一行或一列全部加一，问最少要操作几步能使方格和输入一样。

正着不好想，所以我们可以反着来。

给你一个的 $n \times m$ 的方格，每次操作可以使一行或一列全部减去一，问最少要操作几步能使方格里的数字全部变成 $0$。

然后就很好做啦：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 100005
using namespace std;

bool noans;
int n, m, ans, a[105][105];
struct Answer {
	int rc;//记录行/列数
	bool is_row;//记录行还是列
} t[maxn];
bool row(int i) { //可行返回true，不可行返回false
	for (int j = 1; j <= m; j++) {
		if (a[i][j]) continue;
		return false; //不能再减了，再减就成负数了
	}
	for (int j = 1; j <= m; j++) a[i][j]--;//减
	t[++ans].rc = i;
	t[ans].is_row = true;//添加答案
	return true;//可行
} 
bool col(int j) { //可行返回true，不可行返回false
	for (int i = 1; i <= n; i++) {
		if (a[i][j]) continue;
		return false;//不能再减了，再减就成负数了
	}
	for (int i = 1; i <= n; i++) a[i][j]--;//减
	t[++ans].rc = j;
	t[ans].is_row = false;//添加答案
	return true;//可行
} 
int mian() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			while (a[i][j]) {//能减就减
				if (n <= m) {//此时优先减去行是最优的
					if (row(i)) continue;
					if (col(j)) continue;
					noans = true;//都不行，无解力（悲
					break;
				} else {
					if (col(j)) continue;
					if (row(i)) continue;
					noans = true;//都不行，无解力（悲
					break;
				}
			}
			if (noans) break;//同下
		}
		if (noans) break; //不行了，再搜也没用了
	}	
	if (noans) puts("-1");//不可行输出-1
	else {
		printf("%d\n", ans);
		for (int i = 1; i <= ans; i++) { //输出答案
			if (t[i].is_row) printf("row %d\n", t[i].rc);
			else printf("col %d\n", t[i].rc);
		}
	}
	return 0;//结束啦
}


int main(){mian();return 0;}//皮一下QWQ
```

---

## 作者：Na2PtCl6 (赞：2)

### 分析
首先分析无解的情况：如果我们找遍了每行每列，然后每次都把那一行或那一列的每个数减掉其中的最小数，最后有不是 $0$ 的数，就无解了。

在有解的基础上，如果 $n<m$ 就要先处理行再处理列，否则先处理列再处理行。我们先看一个比较极端的例子：
```
5 3
6 6 6
6 6 6
6 6 6
6 6 6
6 6 6
```
显然是先处理列会快，因为每在列上操作一次减掉的总数值更大，其他情况也可类推。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char res[5000004];
int n,m,cnt,tot,a[104][104];

vector < int > r,c;

void solveR(){
	for(int i=1;i<=n;i++){
		int mini=0x7fffffff;
		for(int j=1;j<=m;j++)
			mini=min(mini,a[i][j]);
		for(int j=1;j<=m;j++)
			a[i][j]-=mini;
		while(mini--){
			++tot;
			r.push_back(i);
		}
	}
}

void solveC(){
	for(int i=1;i<=m;i++){
		int mini=0x7fffffff;
		for(int j=1;j<=n;j++)
			mini=min(mini,a[j][i]);
		for(int j=1;j<=n;j++)
			a[j][i]-=mini;
		while(mini--){
			++tot;
			c.push_back(i);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	if(n<m){
		solveR();
		solveC();
	}
	else{
		solveC();
		solveR();
	}
	bool f=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!=0)
				f=1;
	if(f){
		puts("-1");
		return 0;
	}
	printf("%d\n",tot);
	for(int i=0;i<r.size();i++)
		printf("row %d\n",r[i]);
	for(int i=0;i<c.size();i++)
		printf("col %d\n",c[i]);
	return 0;
}
```

---

## 作者：MrFish (赞：1)

**整体思路：这道题说给你一个全为零的方阵，每次操作可以使一行或一列全部加一，使它变成给出的方阵，我们可以把这道题转换成给你一个方阵，每次操作可以使一行或一列全部减一，使它全变成零。我们依次检查每一行，每一列，把得到的答案记起来，最后如果方阵中有不是0的数，输出“-1”。**
#### 但是，如果只是这样，你会在第十四个点WA掉，这个程序用了100个move，而正解只用了50个move。因为我们先检查行，再检查列，得到的答案可能不是最小的，我们还要先检查列，再检查行再来一遍，看哪个得到的步数少。

170多行的AC代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

struct node
{
    string dir;
    int num;
}ans[100005],ans2[100005];  //记录答案

int a[105][105];  //我们要检查两遍，所以这些数组都要定义两个！
int a2[105][105];
int n,m,anscnt,anscnt2;

bool chk1_1(int x)
{
    for(int i=1;i<=m;i++)
    {
        if(a[x][i]==0)
        {
            return false;
        }
    }    
    return true;
}  //判断a[x]这一行是否全是零

bool chk1_2(int x)
{
    for(int i=1;i<=m;i++)
    {
        if(a2[x][i]==0)
        {
            return false;
        }
    }    
    return true;
}	//判断a2[x]这一行是否全是零
 
bool chk2_1(int y)
{
    for(int i=1;i<=n;i++)
    {
        if(a[i][y]<=0)
        {
            return false;
        }
    }
    return true;
}	//判断a[y]这一列是否全是零

bool chk2_2(int y)
{
    for(int i=1;i<=n;i++)
    {
        if(a2[i][y]<=0)
        {
            return false;
        }
    }
    return true;
}  //判断a2[y]这一列是否全是零

void chkrow(int x)
{
    while(chk1_1(x))
    {
        ans[anscnt].dir="row";
        ans[anscnt].num=x;
        anscnt++;
        for(int i=1;i<=m;i++)
        {
            a[x][i]--;
        }
    }
}  //判断a的行并记录答案

void chkrow2(int x)
{
    while(chk1_2(x))
    {
        ans2[anscnt2].dir="row";
        ans2[anscnt2].num=x;
        anscnt2++;
        for(int i=1;i<=m;i++)
        {
            a2[x][i]--;
        }
    }
}	//判断a2的行并记录答案

void chkcol(int y)
{
    while(chk2_1(y))
    {
        ans[anscnt].dir="col";
        ans[anscnt].num=y;
        anscnt++;
        for(int i=1;i<=n;i++)
        {
            a[i][y]--;
        }
    }
}	//判断a的列并记录答案

void chkcol2(int y)
{
    while(chk2_2(y))
    {
        ans2[anscnt2].dir="col";
        ans2[anscnt2].num=y;
        anscnt2++;
        for(int i=1;i<=n;i++)
        {
            a2[i][y]--;
        }
    }
}	//判断a2的列并记录答案

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            a2[i][j]=a[i][j];
        }
    }	//读入
    for(int i=1;i<=n;i++)
    {
        chkrow(i);
    }
    for(int i=1;i<=m;i++)
    {
        chkcol(i);
    }	//判断a的每一行，每一列

    for(int i=1;i<=m;i++)
    {
        chkcol2(i);
    }
    for(int i=1;i<=n;i++)
    {
        chkrow2(i);
    }	//判断a2的每一行，每一列
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]!=0)
            {
                cout<<"-1"<<endl;
                exit(0);
            }
        }
    }	//如果方阵中有不是0的数，输出“-1”
    if(anscnt<=anscnt2)	//判断哪个步数用得少
    {
        cout<<anscnt<<endl;
        for(int i=0;i<anscnt;i++)
        {
            cout<<ans[i].dir<<' '<<ans[i].num<<endl;
        }
    }
    else
    {
        cout<<anscnt2<<endl;
        for(int i=0;i<anscnt2;i++)
        {
            cout<<ans2[i].dir<<' '<<ans2[i].num<<endl;
        }        
    }
    
    return 0;
}
```


---

## 作者：longlong_int (赞：0)

题目说的是给你一个全是 $0$ 的格子，把它整行整行的加，加到跟 $g$ 一样。

则每一行/每一列**最多**共同加 $\min\{\textrm{这一行/列}\}$。

那么一个一个加就行了。注意别草率，像第二个样例就是处理完了以后还剩一个，正常的是一个都不剩的。

$O(ng_i)$，不用担心。

AC Code（码风很差，所以不要抄袭）：

```cpp
/***----------Copyright SwethessPotion 2024.-----------***/

#include <bits/stdc++.h>
#define endl '\n'
typedef long long ll;
using namespace std;

const int N = 105;
int arr[N][N], temp[N][N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> arr[i][j];
            temp[i][j] = arr[i][j];
        }
    }

    int ans = 0;
    if (n < m)
    {
        for (int i = 1; i <= n; i++)
        {
            int minn = 0x3f3f3f3f;
            for (int j = 1; j <= m; j++) minn = min(minn, arr[i][j]);
            for (int j = 1; j <= m; j++) arr[i][j] -= minn;
            for (int j = 1; j <= minn; j++) ans++;
        }

        for (int i = 1; i <= m; i++)
        {
            int minn = 0x3f3f3f3f;
            for (int j = 1; j <= n; j++)  minn = min(minn, arr[j][i]);
            for (int j = 1; j <= n; j++) arr[j][i] -= minn;
            for (int j = 1; j <= minn; j++) ans++;
        }
    }
    else
    {
        for (int i = 1; i <= m; i++)
        {
            int minn = 0x3f3f3f3f;
            for (int j = 1; j <= n; j++)  minn = min(minn, arr[j][i]);
            for (int j = 1; j <= n; j++) arr[j][i] -= minn;
            for (int j = 1; j <= minn; j++) ans++;
        }

        for (int i = 1; i <= n; i++)
        {
            int minn = 0x3f3f3f3f;
            for (int j = 1; j <= m; j++) minn = min(minn, arr[i][j]);
            for (int j = 1; j <= m; j++) arr[i][j] -= minn;
            for (int j = 1; j <= minn; j++) ans++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (arr[i][j] != 0)
            {
                cout << "-1" << endl;
                return 0;
            }
        }
    }

    cout << ans << endl;

    if (n < m)
    {
        for (int i = 1; i <= n; i++)
        {
            int minn = 0x3f3f3f3f;
            for (int j = 1; j <= m; j++) minn = min(minn, temp[i][j]);
            for (int j = 1; j <= m; j++) temp[i][j] -= minn;
            for (int j = 1; j <= minn; j++) cout << "row " << i << endl;
        }

        for (int i = 1; i <= m; i++)
        {
            int minn = 0x3f3f3f3f;
            for (int j = 1; j <= n; j++)  minn = min(minn, temp[j][i]);
            for (int j = 1; j <= n; j++) temp[j][i] -= minn;
            for (int j = 1; j <= minn; j++) cout << "col " << i << endl;
        }
    }
    else
    {
        for (int i = 1; i <= m; i++)
        {
            int minn = 0x3f3f3f3f;
            for (int j = 1; j <= n; j++)  minn = min(minn, temp[j][i]);
            for (int j = 1; j <= n; j++) temp[j][i] -= minn;
            for (int j = 1; j <= minn; j++) cout << "col " << i << endl;
        }

        for (int i = 1; i <= n; i++)
        {
            int minn = 0x3f3f3f3f;
            for (int j = 1; j <= m; j++) minn = min(minn, temp[i][j]);
            for (int j = 1; j <= m; j++) temp[i][j] -= minn;
            for (int j = 1; j <= minn; j++) cout << "row " << i << endl;
        }
    }
    return 0;
}
```

管理员大大求过！

---

## 作者：youdu666 (赞：0)

### 思路：贪心

在有解的情况下，易证在当前填下的数字均小于答案时，总能在当前的基础上填出答案，换句话说，只要没填爆掉，怎么填都能形成正确答案。

接下来考虑步数的问题，当 $n>m$ 时，显然是先考虑竖着填，否则考虑横着填。

因此，贪心的思路就显而易见了。从一个非零数字开始扫，优先考虑可以填得较多的方案。如果对于某个数字，当前情况下无合法的填数方案，则报告无解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(void)
{
    int x=0,y=1;
    char c=getchar();
    while(c>'9'||c<'0')
    {
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}
const int N=105,M=505;
int n,m;
int a[N][N];
struct anss{
    bool p;
    int x;
}as[N*N*M];
int ann;
inline bool sn(int j)//看看能不能竖着填
{
    for(int i=1;i<=n;i++)
        if(!a[i][j])
            return false;//不能填
    for(int i=1;i<=n;i++)
        --a[i][j];
    as[++ann].p=false;
    as[ann].x=j;
    return true;//能填
}
inline bool sm(int i)//看看能不能横着填
{
    for(int j=1;j<=m;j++)
        if(!a[i][j])
            return false;
    for(int j=1;j<=m;j++)
        --a[i][j];
    as[++ann].p=true;
    as[ann].x=i;
    return true;
}
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            a[i][j]=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            while(a[i][j])//注意用while，因为每一个格子能填多次
            {
                if(n>m)//如果竖着填所用步数更少
                {
                    if(!sn(j))//先考虑竖着填，竖着填不了
                    if(!sm(i))//再考虑横着填
                    {
                        printf("-1\n");//都填不了，报告无解
                        return 0;
                    }
                }
                else//同上
                {
                    if(!sm(i))
                    if(!sn(j))
                    {
                        printf("-1\n");
                        return 0;
                    }
                }
            }
            
        }
    printf("%d\n",ann);//华丽的输出
    for(int i=1;i<=ann;i++)
    {
        if(as[i].p)
            printf("row %d\n",as[i].x);
        else
            printf("col %d\n",as[i].x);
    }
}
/*

*/
```


---

## 作者：_HMZ_ (赞：0)

## 解题思路：

首先看到题面和样例，发现没什么规律，于是我们大胆猜个结论，如果一行的最小值不是 $0$，那我们就将这一行全部减去最小值，一列同理。

但是，这里要求次数尽可能的小，我们随便构造一组数据：

	3 1
    3
    3
    3
    
比如这样，如果我们优先减去行，次数不是最少的，于是我们再次贪心，如果一行的个数小于一列的，则优先列，否则优先减行。

而无解只需要看最后给出的数组中是否有元素不是 $0$。

## AC代码：

```cpp
#include<iostream>
using namespace std;
int n,m,val[1005][1005],ans,line[1000005];
string op[1000005];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>val[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(val[i][j]==0)
				continue;
			int num=1e9;
			if(n>m)//如果一列比一行多
			{
				for(int k=1;k<=n;k++)
					num=min(num,val[k][j]);
				for(int k=1;k<=n;k++)
					val[k][j]-=num;
				for(int k=1;k<=num;k++)
					op[++ans]="col",line[ans]=j;

				num=1e9;

				for(int k=1;k<=m;k++)
					num=min(num,val[i][k]);
				for(int k=1;k<=m;k++)
					val[i][k]-=num;
				for(int k=1;k<=num;k++)
					op[++ans]="row",line[ans]=i;
			}
			else
			{

				for(int k=1;k<=m;k++)
					num=min(num,val[i][k]);
				for(int k=1;k<=m;k++)
					val[i][k]-=num;
				for(int k=1;k<=num;k++)
					op[++ans]="row",line[ans]=i;

				num=1e9;

				for(int k=1;k<=n;k++)
					num=min(num,val[k][j]);
				for(int k=1;k<=n;k++)
					val[k][j]-=num;
				for(int k=1;k<=num;k++)
					op[++ans]="col",line[ans]=j;
			}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(val[i][j]!=0)//判断一下无解
			{
				cout<<-1;
				return 0;
			}
		}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)
		cout<<op[i]<<' '<<line[i]<<endl;
	return 0;
}
```



---

## 作者：pengzy (赞：0)

### 思路：

这是一道带有 **思维难度** 的 **模拟**。

拿样例一来举个例子。

我们发现样例的方法是：行 $1$ 加一、行 $1$ 加一、列 $4$ 加一、行 $3$ 加一。当然，我们也可以：行 $1$ 加一、行 $1$ 加一、行 $3$ 加一、列 $4$ 加一，结果也是正确的。由此，我们可以得出只改变操作的顺序，不改变方法，结果是相同的，因为每一个格子都互不影响。所以，在模拟的过程中，我们只需要 **先加完行，再加完列** 或 **先加完列，再加完行**，取操作次数小的即可。 

那怎么判断行（列）要增加多少次结束呢？

只要对每一行（列）进行判断，只要它的某一个值 **超过给定方阵的对应值** 时，就需要交换行（列）操作了。

最后，如果方阵操作结束后还是不等于给定方阵，就输出 $-1$。

---

