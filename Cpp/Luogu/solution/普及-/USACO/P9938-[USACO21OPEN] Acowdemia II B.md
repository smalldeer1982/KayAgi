# [USACO21OPEN] Acowdemia II B

## 题目描述

Bessie 正在申请计算机科学的研究生，并取得了一所久负盛名的计算机科学实验室的面试通知。然而，为了避免冒犯任何人，Bessie 有意先确定实验室的 $N$ 名现有成员的相对资历（$1\le N\le 100$）。没有两名实验室成员的资历相同，但确定他们的资历深浅可能并不好办。为此，Bessie 将会对实验室的出版物进行调查。

每份出版物均包含一个作者列表，为所有 $N$ 名实验室成员的一个排列。列表按每名实验室成员对这篇文章的贡献降序排列。如果多名研究员的贡献相等，则按字典序排列。由于更有资历的实验室成员负有更多的管理责任，更有资历的研究员从不会比资历较浅的研究员做出更多的贡献。

例如，在一个由资历较浅的学生 Elsie、资历较深的教授 Mildred、以及十分资深的教授 Dean 组成的实验室中，可能存在一篇论文 Elsie-Mildred-Dean，如果他们做出了不等的贡献（也就是说，Elsie 做出的贡献比 Mildred 更多，Mildred 比 Dean 更多）。然而，也有可能存在一篇论文 Elsie-Dean-Mildred，如果 Mildred 和 Dean 做出了相等的贡献，而 Elsie 做出了更多的贡献。

给定实验室的 $K$ 份出版物（$1\le K\le 100$），对于实验室中每对研究员，如果可能的话帮助 Bessie 判断其中谁的资历更深。

## 说明/提示

### 样例解释 1

在这个样例中，单独一份论文 elsie-mildred-dean 并不能提供足够的信息判断 Elsie 比 Mildred 资历更深或更浅。然而，我们可以推断出 Dean 一定比这两名研究员资历更深，从而资历排序为 Elsie<Mildred<Dean 和 Mildred<Elsie<Dean 均是可能的。 

### 样例解释 2

在这个样例中，唯一能与两篇论文相一致的资历排序为 Elsie<Mildred<Dean，这是因为基于第一个样例所提供的信息，第二篇论文可以帮助我们推断出 Mildred 比 Elsie 的资历更深。 

## 样例 #1

### 输入

```
1 3
dean elsie mildred
elsie mildred dean```

### 输出

```
B11
0B?
0?B```

## 样例 #2

### 输入

```
2 3
elsie mildred dean
elsie mildred dean
elsie dean mildred```

### 输出

```
B00
1B0
11B```

# 题解

## 作者：_Deer_Peach_ (赞：1)

题意：

有 $k$ 份出版物，每份出版物都由 $n$ 名成员编写，将他们按资历深浅降序排序，资历相同按名字字典序排序，求判断意两名成员之间资历谁更深。第 $i$ 名成员比第 $j$ 名成员资历更深时用 $1$ 表示，否则用 $0$ 表示。

思路：

按题目模拟即可，每给出一份出版物就判断两人之间资历关系，因为 $n$ 的数据很小，所以不会超时。

因为资历相同按名字字典序排序，所以如果一个人的名字字典序比前一个人大，就不能判断谁资历更深。所以我们要找第一个名字字典序比前一个人小的人，那么前面的人都比后面的人资历更深。

代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;bool vis[101][101];string name[101];//vis[i][j]=1说明第i个人比第j个人资历深
map<string,int>id;signed main(){
	cin>>k>>n;for(int i=1;i<=n;i++)cin>>name[i],id[name[i]]=i;//输入+标号
	for(int i=1;i<=k;i++){//k份出版物
		for(int j=1;j<=n;j++)cin>>name[j];
		for(int j=1;j<=n;j++){
			int x=j+1;while(x<=n&&name[x]>name[x-1])x++;//找第一个名字字典序比前一个人小的人
			for(int y=x;y<=n;y++)vis[id[name[y]]][id[name[j]]]=1;//当前这个人资历都比后面的人深
		}
	}for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)cout<<"B";
			else if(!vis[i][j]&&!vis[j][i])cout<<"?";//都是0说明没有确定过关系
			else cout<<vis[i][j];//否则正常输出
		}cout<<endl;
	}return 0;
}
```

---

## 作者：cly312 (赞：0)

首先根据每篇出版物构建一个资历比较矩阵 $g$，其中 $g_{a,b} = 1$ 表示研究员 $a$ 比 $b$ 资历更高。

遍历每篇出版物，识别出第一个降序的名字，然后假定该名字之后的所有研究员资历都比当前名字对应的研究员资历高即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 110;
int g[N][N];//g[a][b] = 1表示a的资历比b高
int n, m;
unordered_map<string, int> id;

int main() {
	cin >> m >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		id[s] = i;
	}
	string name[N];
	while (m--) {
		for (int i = 0; i < n; i++) cin >> name[i];
		for (int i = 0; i < n; i++) {
			int j = i + 1;
			while (j < n && name[j] > name[j - 1]) j++;//找到第一个降序的名字
			while (j < n) { //j之后的所有人资历都严格比i高
				int a = id[name[i]], b = id[name[j]];
				g[b][a] = 1;
				j++;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (i == j) cout << 'B';
			else if (!g[i][j] && !g[j][i]) cout << '?';
			else cout << g[i][j];
		cout << endl;
	}
	return 0;
}
```

---

## 作者：HUTEHE (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9938)

### 题目大意

根据经过贡献值和字典序排列后的字符串确定资历深浅，贡献值大的资历浅。

### 思路

* 利用 STL 中的 map 容器将姓名作为下标存储贡献值的优先级（STL 容器不熟的[点这](https://oi-wiki.org/lang/csl/associative-container/)）。
* 定义一个二维数组，存储 $n_i$ 与 $n_j$ 的大小关系，优先级高的为 $1$，低的为 $0$​。
* 具体实现详见代码注释。

### 代码实现

```cpp
//改自Yulicezzz的代码
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp> 
#define int long long
using namespace std;
using namespace __gnu_pbds;
const int MAXN=1e5+7;
map<string,int>name;
string s[MAXN];
int mp[1005][1005];
int n,m;
signed main()         
{     
	cin>>m>>n;//按题意输入
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		name[s[i]]=i;//map存储优先级
	}
	while(m--)
	{
		int l=1;//记录上一个级别的最后一个位置
		s[0]='z'+25;
		for(int i=1;i<=n;i++)
		{
			cin>>s[i];
			if(s[i]<s[i-1])
			{
				l=i;//更新
			}
			for(int j=1;j<l;j++)
			{
				mp[name[s[j]]][name[s[i]]]=-1;//根据优先级存入数组
				mp[name[s[i]]][name[s[j]]]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i!=j)
				mp[i][j]==1?cout<<"1":mp[i][j]==-1?cout<<"0":cout<<"?";//输出矩阵
			else
				cout<<"B";//如果 i=j 则输出 B
		}
		puts("");
	}
	return 0;
}
```

### 时间复杂度

约 $O(m ⋅ n^2)$。

---

## 作者：not_so_littlekayen (赞：0)

**[P9938 [USACO21OPEN] Acowdemia II B ](https://www.luogu.com.cn/problem/P9938)**

[推荐读懂官方题解后食用！](https://usaco.org/current/data/sol_prob2_bronze_open21.html)

我们来简单分析一下样例，以样例一为例，假如 elsie 和 mildred 要排到 dean 的前面去，需要比 dean 付出更大的努力——也就是说，elsie 和 mildred 比 dean 资历更浅。

为什么是这样呢？

若三人做出的贡献相等，则三人就按照字典序进行排列。可怜的 elsie 和 mildred 只好排在 dean 之后。

若 elsie 和 mildred 做出的贡献比 dean 少，就更应该排在后面了。不对，题目中不是说了吗，**更有资历的研究员从不会比资历较浅的研究员做出更多的贡献**。

所以，elsie 和 mildred 排到了前面，又根据题目中更有资历的研究员从不会比资历较浅的研究员做出更多的贡献这句话可知 elsie 和 mildred 比 dean 资历更浅。

在进行了以上分析之后，我们就可以得出一个通用的结论：令 $n_1,n_2,…,n_N$ 为一份出版物上出现的名字，如果存在 $i < j$，且 $n_i,…,n_j$ 不按字典序排列，我们就可以判断出 $n_i$ 比 $n_j$ 的资历要浅。



由此，可得程序。
```cpp
//illustrated by littlekayen_qwq!
#include<bits/stdc++.h>
using namespace std;
int mp[105][105];//记录答案
map<string, int> trans;//将名字转换为数字
string orgin[105], name[105];
int n, k, cnt;
bool alphabet(int st, int ed)//按照字典序排列
{
    for(int i = st;i < ed;i++)
        if(name[i] > name[i+1])return 0;
    return 1;
}
int main()
{
    cin >> k >> n;
    for(int i = 1;i <= n;i++)
        cin >> orgin[i], trans[orgin[i]] = i;
    while(k--)
    {
        for(int i = 1;i <= n;i++)
            cin >> name[i];
        for(int i = 1;i <= n;i++)
            for(int j = i+1;j <= n;j++)
                if(!alphabet(i, j))
                {
                    int a = trans[name[i]], b = trans[name[j]];
                    mp[a][b] = 1;//a比b资历浅
                    mp[b][a] = 2;//b比a资历深
                }
    }
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            if(i == j)cout << "B";
            else
            {
                switch(mp[i][j])
                {
                    case 0:cout << "?";break;
                    case 1:cout << "0";break;
                    default:cout << "1";
                }
            }
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：we_are_the_chuibing (赞：0)

### 题意
给一些经过双关键字排序（贡献为第一关键字，名字为第二关键字）的人名，贡献多的资历一定浅，贡献相同的无法确定大小关系。
### 思路
找字典序非递减的地方可以找到大小关系，建图。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 105
int k,n;
string s[MAXN];
map<string,int>name;
short vh[MAXN][MAXN];
int main(){
	cin>>k>>n;
	for(int i=1;i<=n;++i)
		cin>>s[i],name[s[i]]=i;
	s[0]=char('z'+1);//第0位设为无穷大
	memset(vh,false,sizeof(vh));
	while(k--){
		int pos=1;
		for(int i=1;i<=n;++i){
			cin>>s[i];
			if(s[i]<s[i-1])
				pos=i;//pos记录当前按字典序递增的第一位
			for(int j=1;j<pos;++j){//该人的资历一定比pos前的所有人资历深，使用邻接矩阵存图可以省去重边
				vh[name[s[i]]][name[s[j]]]=1;
				vh[name[s[j]]][name[s[i]]]=-1;
			}
		}
	}for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(j==i){
				cout<<"B";
				continue;
			}switch(vh[i][j]){
				case 1:cout<<1;break;
				case -1:cout<<0;break;
				default:cout<<"?";break;
			}
		}cout<<endl;
   }
	return 0;
}

```


---

