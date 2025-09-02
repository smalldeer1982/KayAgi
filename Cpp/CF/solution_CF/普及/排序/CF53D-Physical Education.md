# Physical Education

## 题目描述

Vasya is a school PE teacher. Unlike other PE teachers, Vasya doesn't like it when the students stand in line according to their height. Instead, he demands that the children stand in the following order: $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the height of the $ i $ -th student in the line and $ n $ is the number of students in the line. The children find it hard to keep in mind this strange arrangement, and today they formed the line in the following order: $ b_{1},b_{2},...,b_{n} $ , which upset Vasya immensely. Now Vasya wants to rearrange the children so that the resulting order is like this: $ a_{1},a_{2},...,a_{n} $ . During each move Vasya can swap two people who stand next to each other in the line. Help Vasya, find the sequence of swaps leading to the arrangement Vasya needs. It is not required to minimize the number of moves.

## 样例 #1

### 输入

```
4
1 2 3 2
3 2 1 2
```

### 输出

```
4
2 3
1 2
3 4
2 3
```

## 样例 #2

### 输入

```
2
1 100500
1 100500
```

### 输出

```
0
```

# 题解

## 作者：Siyuan (赞：6)

> ## 其实这道题主要看思路，如果思路对了就迎刃而解了（逃。。。

## 本题思路：
1. 注意到$\ n$的范围很小，于是就想到了$\ O(n^2)$做法。
2. 从$\ a[1]$开始复原到$\ a[n]$；每次在$\ b$数组中查找$\ a[i]$的下标，并在$\ b$数组中进行交换。
3. 正是每次及时交换，因此每次查找时，$\ b$数组中的下标肯定不小于$\ a$数组中下标，这也就保证了每次交换不会影响之前排列好的数字。

### 代码如下：（虽然是D题但挺简单的）

```
#include<cstdio>
using namespace std;

int n,a[302],b[302];
int cnt,ans[1000005];

inline void write(const int &x)
{
	if(x>9)  write(x/10);
	putchar(x%10+'0');
}

int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)  scanf("%d",&a[i]);
	for(register int i=1;i<=n;i++)  scanf("%d",&b[i]);
	for(register int i=1;i<=n;i++)
	{
		register int k;
		for(register int j=i;j<=n;j++)
			if(b[j]==a[i]){k=j;break;}
		for(register int j=k;j>=i+1;j--)
		{
			b[j]^=b[j-1],b[j-1]^=b[j],b[j]^=b[j-1];
			ans[++cnt]=j;
		}
	}
	write(cnt);  puts("");
	for(register int i=1;i<=cnt;i++)
	{
		write(ans[i]-1);
		putchar(' ');
		write(ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：drop (赞：1)

## 提醒
此题为 **Special Judge**，只要输出合理即可。

## 思路

### 交换

拿样例 1 来说：

| i | a | b |
| -:|:-:|:-:|
| → **1** | 1 | 3 |
| 2 | 2 | 2 |
| 3 | 3 | 1 |
| 4 | 2 | 2 |

$a$ 数组的第一项为 $1$，经查找 $b$ 数组的第三项是 $1$，所以，为了让其相等，将 $b$ 数组的第三项和第二项交换，再将第二项（原来的第三项）和第一项交换，最终用两次完成交换。

| i | a | b |
| -:|:-:|:-:|
| 1 | 1 | 1 |
| → **2** | 2 | 3 |
| 3 | 3 | 2 |
| 4 | 2 | 2 |

再来看 $a$ 数组的第二项，为 $2$，经查找 $b$ 数组的第三项和第四项都是 $2$，取其中的任意一项（这里我用前一项），所以将 $b$ 数组的第三项和第二项交换（或者交换第四项和第三项，再交换第三项和第二项），用一次完成交换。

| i | a | b |
| -:|:-:|:-:|
| 1 | 1 | 1 |
| 2 | 2 | 2 |
| → **3** | 3 | 3 |
| → **4** | 2 | 2 |

然后，我们发现 $a$ 数组的后两项与 $b$ 数组的相同，所以输出就是：
```
3
2 3
1 2
2 3

```
虽然与样例 1 输出不同，但因此题是 **Special Judge**，这种情况是被允许的。

### 输出

在交换 $j$ 和 $j+1$ 前用数组 $out$ 记录 $j$，到时候输出 $out[j]$ 和 $out[j+1]$。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000],b[1000],ans;
vector <int> out; //不定长数组，相当于一个可以变长度的数组

void Sort(){
	for(int i=1;i<=n;i++){
		int flag=0;
		for(int j=i;j<=n;j++){
			if(b[j]==a[i]){ //发现b数组和a数组重复的地方 
				flag=j;
				break;
			}
		}
		for(int j=flag-1;j>=i;j--){
			swap(b[j],b[j+1]); //交换b数组 
			out.push_back(j);  //记录j 
			ans++; //交换次数增加1 
		}
	}
	cout<<ans<<endl;
	for(int i=0;i<out.size();i++) cout<<out[i]<<" "<<out[i]+1<<endl;
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	Sort();
	return 0;
}
```

---

## 作者：Supor__Shoep (赞：1)

我们简化一下题目，就是用最少的相邻移动次数把一个数组变成另一个数组。

和许多大佬的思路相似，首先我们定义一个栈数组记录答案，对于 $a$ 数组的每一个数，我们可以从下标开始往后循环查找 $b$ 数组的数，如果两者相同，就把这一段循环的所有数字进行交换。但是一定要记得及时终止循环。

记录答案的时候，可以记录 $k$ ，也可以记录 $k-1$ 。

有些人可能不明白，为什么这样的交替一定是答案呢？

说实话这个问题还是比较弱的，为了和冒泡排序扯上关系，也没有什么更简单的方法。对于这个数字，找到了它的归宿之后，途中所有的数都必须交换，以此把这个数字推到它的归宿上面。

也就是这样的：

	1 2 3 4 5
  	5 4 3 2 1

对于第一个序列中的 $1$ ，我们要把它移到第 $5$ 个数上。

	2 1 3 4 5
  	2 3 1 4 5
  	2 3 4 1 5
  	2 3 4 5 1
    
这不就是把途中的数字给交换了吗？所以我们根据冒泡一定可以找到正确的答案。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int a[305],b[305];
int stk[1000005];//栈数组
int T;
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)//从这里往后查找相同的数
        {
            if(b[j]==a[i])//找到了归宿
            {
                for(int k=j;k>i;k--)//途中的数要交换
                {
                    swap(b[k],b[k-1]);
                    stk[++T]=k-1;//记录答案
                }
                break;//一定要及时跳出循环
            }
        }
    }
    cout<<T<<endl;
    for(int i=1;i<=T;i++)
    {
        cout<<stk[i]<<" "<<stk[i]+1<<endl;
        //代表此答案下标和下一个数字交换
    }
    return 0;
}
```

---

## 作者：fls233666 (赞：1)

首先可以注意到序列 $a$ 不一定是有序的。这就使序列 $b$ 变换到序列 $a$ 的过程变得复杂了。显然，由于 $1 \le n \le 300$ ，直接搜索是不行的。考虑如何转化。

回顾各种经典的排序算法，可以发现这些算法都是 **将无序的序列变为有序的。** 那么，一个很巧妙的思路是 **给无序的序列 $a$ 打上有序的标记，再将这些标记映射到序列 $b$ 中，映射后的标记进行排序。** 进一步考虑发现映射需要的时间为 $O(n^2)$ ，排序需要的时间也是 $O(n^2)$ ,则总复杂度为 $O(n^2)$ ,可以通过此题。

如何打标记？一个简单的方法就是拿数组下表当作标记【因为数组下标本身就是有序的】。另外开一个数组标记哪些数字已经被映射到序列 $b$ 中。全部映射完成后，就可以得到映射后的下标序列了。

最后，基于题目中只能交换相邻两个学生的要求，考虑使用 **冒泡排序** 对映射得到的下标序列排序。 记录排序过程中交换数字的顺序输出即可。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define ll long long
#define rgt register int
using namespace std;

int n;
const int mxn = 303;
int a[mxn],b[mxn],tag[mxn];
bool use[mxn];
vector < pair<int,int> > ans;

int main(){

	scanf("%d",&n);
	for(rgt i=1;i<=n;i++)
		scanf("%d",&a[i]);  //读入序列 a
        
	for(rgt i=1;i<=n;i++){
		scanf("%d",&b[i]);  //读入序列 b
		for(rgt j=1;j<=n;j++){
			if(!use[j]&&a[j]==b[i]){  //找到还未映射过的数字进行映射
				tag[i]=j;  //存储映射得到的下标序列
				use[j]=true;
				break;
			}
		}
	}
    
	for(rgt i=1;i<n;i++){   //对映射得到的下标序列冒泡排序
		for(rgt j=1;j<n;j++){
			if(tag[j]>tag[j+1]){  //记录交换的顺序
				ans.push_back(make_pair(j,j+1));
				tag[j]^=tag[j+1];
				tag[j+1]^=tag[j];
				tag[j]^=tag[j+1];
			}
		}
	}
    
	printf("%d\n",ans.size());  //输出交换次数和方案
	for(rgt i=0;i<ans.size();i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}
```


---

## 作者：_edge_ (赞：1)

### 标签：模拟

### 难度：普及T2 (在我看来)

这题目有 $1 \le n \le 300$ 这个条件，还有 $1 \le k \le 10^6$ 这个条件，两个条件下我们可以轻松地进行模拟。

我的思路是在第一个数组里面一个一个枚举过去，然后在第二个数组里面寻找相等的，前面已经好了的就不用查找，最坏情况下是 $O(n^2)$ ，且满足题意。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=305;
int n,a[INF],b[INF],fx[INF*INF*5],fy[INF*INF*5],tot;
bool vis[INF];
signed main()
{
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%d",&a[i]);
        for (int i=1; i<=n; i++) scanf("%d",&b[i]);
        for (int i=1; i<=n; i++) {
                int j=1;
                for (j=i; j<=n; j++) {
                        if (b[j]==a[i]) break;
                }
                if (i==j) continue;
                if (i<j) for (; j>i; j--) fx[++tot]=j-1,fy[tot]=j,swap(b[j],b[j-1]);
                if (i>j) for (; j<i; j++) fx[++tot]=j+1,fy[tot]=j,swap(b[j],b[j+1]);
                // cout<<"\n";
                // for (int ii=1; ii<=n; ii++) cout<<b[ii]<<"\n";
                // cout<<"\n";
                // cout<<i<<"\n";
        }
        cout<<tot<<"\n";
        for (int i=1; i<=tot; i++) cout<<fx[i]<<" "<<fy[i]<<"\n";
        return 0;
}

```

感谢那些评论区里面 hack 或者提出意见的神仙们！

---

## 作者：_Weslie_ (赞：1)

update 2022.8.6:发现有错误，改一下。

## [题目传送门(CF53D)](https://www.luogu.com.cn/problem/CF53D)

这一题，有两个数组，分别是 $\ a,b$。

然后我们看一下 $n$ 的数据范围，$1\leq n\leq300$。

于是考虑 $\ \operatorname{O}(n^3)$。

---

## 思路部分

首先，这一题是要求换数组 $\ b$ 直到换成数组 $\ a$。

题目是这么写的——
```
不需要最小化移动次数。
```

那么，我们可以利用冒泡排序的性质，去得到答案。

冒泡排序的思路是：

比较 $\ a_i\ $ 和 $\ a_{i-1}$，（升序排列）如果 $\ a_i>a_{i-1}$，交换 $\ a_i\ $ 和 $\ a_{i-1}$。

第一轮比较结束之后，最大的数就到最后面的 $\ a_n\ $ 了。

经过 $\ n-1\ $ 轮比较，数组就有序了。

我们对冒泡进行改动，即可 $\ \text{AC}\ $ 本题。

当我们把一个数移到另一个位置时，$ans$ 数组就记录下来了。

记录下来之后，因为本题不求最优解，所以一点问题没有。

而且冒泡只交换连续的两个数字，所以不会违反题意。

## 代码实现

读入部分就不说了。

如果，$\ a_i=b_j$，说明找到了人，开始交换。

交换的过程用第三层循环 $\ k\ $ 来表示。

$\forall k,i<k \leq j$。

记得 $\ k\ $ 是倒序循环。

然后定义 $\ ans\ $ 数组，记录答案(记录 $\ k\ $)。当然了，记录 $\ k-1\ $ 的话最后输出时就得输出 $\ ans_i\ $ 和 $\ ans_i+1$。

最后，对于每个 $\ ans_i$，输出 $\ ans_i-1\ $和 $\ ans_i\ $ 即可。

### AC Code:
```
#include<iostream>
using namespace std;
int a[301],b[301],ans[1000001],p,n;//定义数组和变量（不会MLE）
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(b[j]==a[i]){
				for(int k=j;k>i;k--){
					swap(b[k],b[k-1]);//冒泡排序思路交换
					ans[++p]=k;//记录ans
				}
				break;//一定记得break
			}
		}
	}
	cout<<p<<endl;//输出总数
	for(int i=1；i<=p;i++){
		cout<<ans[i]-1<<' '<<ans[i]<<endl;
	}
	return 0;
}
```

时间复杂度约为 $\ \operatorname{O}(n^3)$。

后记：萌新第一次写题解，如果有错，请大佬帮忙指出！谢谢啦！

---

## 作者：开始新的记忆 (赞：0)

题目大意：现在给你一个序列，让你经过若干次相邻之间的交换后使得序列等于要求的序列。

思路：注意到题目的n很小，所以可以直接上n^2qwq，每次从要求序列的头到尾找，不难发现，每次匹配完都会使得直到这意味之前的都一样，题目已经保证会有解，所以每次寻找都会在这位的后面，暴力查询即可。

```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
};
vector <node > qwq;
int n,a[310],b[310];

int main()
{	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n;++i)
		cin>>b[i];
	for(int i=1;i<=n;++i)
	{
		int t=n;
		for(int j=i;j<=n;++j)
			if(a[j]==b[i])
			{
				t=j;
				break;
			}
		for(int j=t;j>i;--j)
		{
			node hh;
			hh.x=j-1;hh.y=j;
			swap(a[j],a[j-1]);
			qwq.push_back(hh);
		}
	}
	cout<<qwq.size()<<endl;
	for(int i=qwq.size()-1;i>=0;--i)
		cout<<qwq[i].x<<' '<<qwq[i].y<<endl;
	return 0;
}
```


---

## 作者：lixiao189 (赞：0)

### 思路:
这道题目其实就是一个冒泡排序的变种。加入有一个a[i]数组，该数组中的数据为：
```cpp
1 2 3 2 
```
那么我们就给每个a[i]数组中的数给予一个权值这个权值就是这个数的位置i这样在我们就可以得到这样的关系

```cpp
a[i]中的数：     1 2 3 2
a[i]数的权值：   1 2 3 4

```

然后我们在输入b[i]后就找出b[i]在原来在数组a[i]中的权值（比如说假如b[i]中有一个3那么这个3的权值就是3)，如果有重复（比如说这里有两个2）那么我们前面的b[i]就用前面的权值，后面的b[i]就用后面的权值。这样b[i]中的每个数又有了新的关系:

```cpp
b[i]中的数：     3 2 1 2
b[i]中的权值:    3 2 1 4
```

然后对b[i]中的权值进行冒泡排序即可。复杂度O(n^2)

### 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int N =1e3+5;

//定义变量
int n;
struct u{
	int num;
	int date;
	bool book;
}a[N],b[N];

int main(){

	//输入
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i].date;
		a[i].num=i;
		a[i].book=true;
	}
	for (int j=1;j<=n;j++){
		cin>>b[j].date;
		for (int i=1;i<=n;i++){
			if (a[i].date==b[j].date && a[i].book){
				b[j].num=a[i].num;	
				a[i].book=false;
				break;	
			}
		}
	}

	int sum=0;
	vector <int> u;
	vector <int> v;
	for (int i=1;i<=n;i++){
		for (int j=1;j<n;j++){
			if (b[j].num>b[j+1].num){
				sum++;
				u.push_back(j);
				v.push_back(j+1);
				swap(b[j],b[j+1]);
			}
		}
	}

	cout<<sum<<endl;
	for (int i=0;i<(int)u.size();i++){
		cout<<u[i]<<" "<<v[i]<<endl;;
	}	

	return 0;

}
```

---

