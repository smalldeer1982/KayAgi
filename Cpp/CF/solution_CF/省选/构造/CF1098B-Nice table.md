# Nice table

## 题目描述

给定一个 $n \times m$ 的字符表格，表格中的字符仅包含「A」、「G」、「C」、「T」。我们称一个表格是“优美的”，如果它的每一个 $2 \times 2$ 子方格都包含这四个不同的字符。你的任务是找到一个“优美的”表格（同样只包含「A」、「G」、「C」、「T」），并且与给定表格不同的字符数最少。

## 说明/提示

在第一个样例中，表格已经是优美的。在第二个样例中，你可以修改 9 个元素使表格变为优美的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2
AG
CT
```

### 输出

```
AG
CT
```

## 样例 #2

### 输入

```
3 5
AGCAG
AGCAG
AGCAG
```

### 输出

```
TGCAT
CATGC
TGCAT
```

# 题解

## 作者：_sys (赞：7)

比赛当天就想到思路了但是因为当时凌晨两点多所以根本没法思考，于是写了$40$分钟没过样例，最后$Δ=-22......$

首先我们可以发现，有两种情况：
- 隔列字符相同，隔行字符集合相同
如：

$AGAG$

$CTCT$

$GAGA$

$TCTC$

- 隔行字符相同，隔列字符集合相同
如：

$ACGT$

$GTAC$

$ACGT$

$GTAC$

然后分类讨论就好啦！
第一种情况隔行不影响，第二种隔列不影响
分类讨论字符分成哪两个集合，再看那个字符开头，就能退出来

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn=300005;
char choose[][2]={{0,0},{'A','G'},{'A','C'},{'A','T'},{'C','T'},{'G','T'},{'C','G'}};
int pos[3][Maxn][7],n,now[3],m,tot[3][Maxn];
string str[Maxn],T[Maxn];
void print(pair <int,int> way)
{
	if(!way.first)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				printf("%c",choose[(way.second+(i&1)*3-1)%6+1][(j&1)!=(pos[0][i][way.second]-1)]);
			printf("\n");
		}
	}
	else
	{
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				T[j]+=choose[(way.second+(i&1)*3-1)%6+1][(j&1)!=(pos[1][i][way.second]-1)];
		for(int i=1;i<=n;i++)
			cout<<T[i]<<endl;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		cin>>str[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=6;j++)
		{
			now[1]=now[2]=0;
			for(int k=1;k<=m;k++)
			{
				now[1]+=choose[(j+(i&1)*3-1)%6+1][k&1]!=str[i][k-1];
				now[2]+=choose[(j+(i&1)*3-1)%6+1][!(k&1)]!=str[i][k-1];
			}
			pos[0][i][j]=now[1]<now[2]?1:2;
			tot[0][j]+=min(now[1],now[2]);
		}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=6;j++)
		{
			now[1]=now[2]=0;
			for(int k=1;k<=n;k++)
			{
				now[1]+=choose[(j+(i&1)*3-1)%6+1][k&1]!=str[k][i-1];
				now[2]+=choose[(j+(i&1)*3-1)%6+1][!(k&1)]!=str[k][i-1];
			}
			pos[1][i][j]=now[1]<now[2]?1:2;
			tot[1][j]+=min(now[1],now[2]);
		}
	int ans=0x3f3f3f3f;
	pair <int,int> way;
	for(int i=0;i<=1;i++)
		for(int j=1;j<=6;j++)
			if(tot[i][j]<ans) ans=tot[i][j],way=make_pair(i,j);
	print(way);
	return 0;
}

```

---

## 作者：lottle1212__ (赞：4)

# [Nice table](https://www.luogu.com.cn/problem/CF1098B)

首先可以观察一下合法的矩阵的性质。只要随意地填，填足够多时，就会发现规律。即一个合法的矩阵，要么每一行是两个字母交错构成，要么每一列是两个字母交错构成。如下：

```
AGAGAGAG
CTCTCTCT
GAGAGAGA
CTCTCTCT
```

那么只要枚举一下交错的是行还是列，奇数行、偶数行分别是哪些字母，求最小值就好了。[代码](https://codeforces.com/problemset/submission/1098/305086423)看着有点长，其实都是复制粘贴。

---

## 作者：wmrqwq (赞：1)

注意到对于每一列或者每一行是有轮换的性质的。

也就是说，对于每行或者每列，字符集的大小为 $2$。

然后相同奇偶性的行或列字符集是**一致**的，且不同奇偶行的行或列的字符集大小为 $4$。

于是我们枚举行相同还是列相同，然后枚举行或列选取的字符集即可，代码不是很好写。

[参考代码](https://codeforces.com/problemset/submission/1098/313198402)

---

## 作者：RyexAwl (赞：1)

### CF1098B Nice table

[题目链接](https://www.luogu.com.cn/problem/CF1098B)

#### 简要题意

给定一个 $nm$ 的矩阵，求最小的操作，使的每个 $2\times2$ 的子矩阵中都含有 `AGCT` 四个字母。

每次操作可以改变矩阵中任意一个字符。

$2\le n,m,n\times m\le 3\times 10^5$。

#### 题解

考虑对于满足任意 $2\times 2$ 子矩阵都含有 `AGCT` 的矩阵的性质。

考虑两种有公共部分的 $2\times 2$ 的矩形：

![](https://cdn.luogu.com.cn/upload/image_hosting/0neyc2s1.png)

观察左侧两条红色部分，设其分别为 $S_1=\{a_{i,j},a_{i+1,j}\},S_2=\{a_{i,j+2},a_{i+1,j+2}\}$，一定有 $S_1=S_2$（注意集合是无序的）。因为两个矩形都有中间公共的白条部分。

同理对于右侧两条绿色的部分，设其分别为 $T_1=\{a_{i,j},a_{i,j+1}\},T_2=\{a_{i+2,j},a_{i+2,j+1}\}$，那么一定有 $T_1=T_2$。

那么考虑对所有列按奇偶性分类，考察奇偶性相同的列之间的关系。

考虑第 $i$ 列和第 $i+2$ 列上元素的关系，从小的情况开始考虑，设第一行和第二行对应的情况是这样的：

$$
\begin{aligned}
\text{1\ \ 1}\\
\text{2\ \ 2}
\end{aligned}
$$

根据 $S_1=\{a_{i,j},a_{i+1,j}\},S_2=\{a_{i,j+2},a_{i+1,j+2}\}$，一定有 $S_1=S_2$，第三行对应的元素一定是相同的。并且可以推出对于所有行 $j$ 一定有 $a_{i,j}=a_{i+2,j}$。

考虑第一行和第二行对应的另一种情况：

$$
\begin{aligned}
\text{1\ \ 2}\\
\text{2\ \ 1}
\end{aligned}
$$

根据 $S_1=\{a_{i,j},a_{i+1,j}\},S_2=\{a_{i,j+2},a_{i+1,j+2}\}$，一定有 $S_1=S_2$，第三行一定是 $\text{1\ \ 2}$。并且不断迭代可以得出其一定是 $\text{1\ \ 2}$，$\text{2\ \ 1}$ 交替出现。

考虑确定第一列上的元素尝试使用第 $i$ 列和第 $i+2$ 列元素关系的观察得出所有和第一列同余的列上的元素的性质。

注意到如果第 $1$ 列是两种元素交替，即形如：

$$
\begin{aligned}
1\\
2\\
1\\
2\\
1\\
....
\end{aligned}
$$

那么所有列一定是 $1,2$ 交替。（因为无论第 $i$ 列和第 $i+2$ 列元素的关系是两种关系中的哪一种第 $i+2$ 列一定是 $1,2$ 交替）

如果第 $1$ 列存在 $3$ 种或 $4$ 种元素，那么所有和第一列同余的列一定与第一列的元素对应位置相同。

并且我们可以直接根据奇数列的状态推出偶数列的状态：

* 如果奇数列是两种元素交替，那么偶数列也已一定是两种元素交替出现。并且其交替的元素恰好是奇数列未出现过的两种元素。

* 如果奇数列出现了 $3$ 种或 $4$ 种元素，那么偶数列也已一定出现了 $3$ 种或 $4$ 种元素。

接下来我们将依据上面两个结论得到题目的重要突破口：如果存在某一列出现了 $3$ 种或 $4$ 种元素，那么对于任意一行的元素一定是两种元素交替出现的。对于行反过来也可以得出关于列的类似的结论（即如果某一行出现了 $3$ 种或 $4$ 种元素，那么对于任意一列的元素一定是两种元素交替）。结合在一起：要么任意一行只有两种元素要么任意一列只有两种元素。

考虑钦定列只有两种元素交替出现（行也是类似的方式处理，在下面不做讨论），枚举奇数列出现的两种元素然后枚举每一列是两种交替情况的哪一种比较优即可。

复杂度 $O(nm)$。




---

## 作者：foreverlasting (赞：1)

[安利一波博客](https://foreverlasting1202.github.io/)

B Nice table

题面：给出一个$n\ast m$的碱基方阵。现要求多次修改，使得每个2*2的方格内都有ACGT。每次修改只能把任意一个格子改成任意一个字符，求最小修改数。

做法：因为一定是要么一行的时候两个字符轮换，或者一列的时候两个轮换（感觉一下），于是暴力打出方案数就好了。

code:
```cpp
//2019.1.26 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-10
inline int read() {
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')w=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y) {
    x^=y^=x^=y;
}
inline int _max(const res &x,const res &y) {
    return x>y?x:y;
}
inline int _min(const res &x,const res &y) {
    return x<y?x:y;
}
const int N=3e5+10;
namespace MAIN {
    int n,m;
    string str[N],Ans[N],ret,pos[N];
#define pb push_back
    int ans=inf;
    int qaq;
    bool flag;
    string ss[N];
    inline void MAIN(){
        n=read(),m=read();
        for(res i=1;i<=n;i++)cin>>str[i];
        qaq=0;
        for(res i=1;i<=n;i++){
            if(i&1){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(!(i&1)){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(i&1){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(!(i&1)){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(i&1){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(!(i&1)){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[i][j]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[i][j]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];}

        _swap(n,m);
        
//        for(res i=1;i<=n;i++){
//        	for(res j=0;j<m;j++)putchar(str[j+1][i-1]);
//        	puts("");
//        }
        qaq=0;
        for(res i=1;i<=n;i++){
            if(i&1){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];flag=1;}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(!(i&1)){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];flag=1;}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(i&1){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];flag=1;}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(!(i&1)){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];flag=1;}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(i&1){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];flag=1;}

        qaq=0;
        for(res i=1;i<=n;i++){
            if(!(i&1)){
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('A'),ret.pb('T');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('A');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('T'),ret.pb('A');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('T');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
            else {
                ret.clear();
                res QAQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('G'),ret.pb('C');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('G');
                for(res j=0;j<m;j++)QAQ+=(ret[j]!=str[j+1][i-1]);
                pos[i]=ret;
                ret.clear();
                res QWQ=0;
                for(res j=1;j<=m/2;j++)ret.pb('C'),ret.pb('G');
                for(res j=(int)m/2*2+1;j<=m;j++)ret.pb('C');
                for(res j=0;j<m;j++)QWQ+=(ret[j]!=str[j+1][i-1]);
                if(QWQ<QAQ)pos[i]=ret;
                qaq+=_min(QAQ,QWQ);
            }
        }
        if(qaq<ans){ans=qaq;for(res i=1;i<=n;i++)Ans[i]=pos[i];flag=1;}

//		printf("%d\n",ans);
        if(!flag){
            _swap(n,m);
            for(res i=1;i<=n;i++){
                for(res j=1;j<=m;j++)putchar(Ans[i][j-1]);
                puts("");
            }
        }
        else {
            for(res j=1;j<=m;j++){
                for(res i=1;i<=n;i++)putchar(Ans[i][j-1]);
                puts("");
            }
        }
    }
}
int main() {
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

更新 2024.2.25：修改了时间复杂度写法。

------------

[CF1098B Nice table](https://www.luogu.com.cn/problem/CF1098B)

### 思路

我们对于这种构造一个矩阵，使得每个类似/相同的子矩阵有类似/相同的限制条件，我们有一个很好的思路是构造一个符合条件的小矩阵，然后不断复制它，直到达到所求矩阵的大小。最后用符合条件的矩阵与原矩阵比较，计算答案。

这道题看到是 $2\times2$ 的子矩阵，我们考虑构造一个 $4\times4$ 的小矩阵，显然这包含了所有子矩阵的可能。

这个需要自己探索一下，比如你可以写出这样的小矩阵：

```
AGAT
CTCG
AGAT
CTCG
```

写完后你发现，无论怎么变化，要么隔一行是相同的，要么隔一列是相同的。因为某一行/列出现过的字母不可能在相邻行/列的左中右位置再次出现。我们于是缩小构造的范围，将原来的范围减半，变成 $4\times 2$ 的小矩阵。

如果隔一行是相同的，那么你可以发现隔一列要么相同，要么互相反转。因为显然这之中不能换成其它字母，而且反转对于一个子矩阵，字母种类显然不会发生变化。细心观察你会发现，由于相同行的限制，对于每一列，它含有的字母数恰好为 $2$。于是我们枚举奇数列的字母，枚举它们的上下顺序，同时统计一下最少需要修改几个字符，取这种状态下的最优决策。

隔一列相同的处理也是相似的，只不过行列互换而已。

时间复杂度为 $O(knm)$，$k$ 为枚举的方案数。这里全排列枚举，$k=2\times4!=48$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=300005;
int n,m,a[5],ans,col[N];
std::string s[N],t=" ACGT",fin[N];
inline void check2(std::string w){//相同行枚举列
	int tot=0;
	for(int j=1;j<=m;++j){
		int c1=0,c2=0;
		for(int i=1;i<=n;i+=2){
			c1+=(s[i][j]!=w[j&1])+(i+1<=n)*(s[i+1][j]!=w[2+(j&1)]);
			c2+=(s[i][j]!=w[2+(j&1)])+(i+1<=n)*(s[i+1][j]!=w[j&1]);
		}//统计反转前后的修改次数
		col[j]=c1>c2;tot+=std::min(c1,c2);//选取当前状态下的最优决策
	}
	if(tot<ans){//打擂台计算最优解
		for(int j=1;j<=m;++j)
			if(col[j]) for(int i=1;i<=n;i+=2){fin[i][j]=w[2+(j&1)];if(i+1<=n) fin[i+1][j]=w[j&1];}
			else for(int i=1;i<=n;i+=2){fin[i][j]=w[j&1];if(i+1<=n) fin[i+1][j]=w[2+(j&1)];}
		ans=tot;
	}
}
inline void check3(std::string w){//相同列枚举行
	int tot=0;
	for(int i=1;i<=n;++i){
		int c1=0,c2=0;
		for(int j=1;j<=m;j+=2){
			c1+=(s[i][j]!=w[i&1])+(j+1<=m)*(s[i][j+1]!=w[2+(i&1)]);
			c2+=(s[i][j]!=w[2+(i&1)])+(j+1<=m)*(s[i][j+1]!=w[i&1]);
		}//统计反转前后的修改次数
		col[i]=c1>c2;tot+=std::min(c1,c2);//选取当前状态下的最优决策
	}
	if(tot<ans){//打擂台计算最优解
		for(int i=1;i<=n;++i)
			if(col[i]) for(int j=1;j<=m;j+=2){fin[i][j]=w[2+(i&1)];if(j+1<=m) fin[i][j+1]=w[i&1];}
			else for(int j=1;j<=m;j+=2){fin[i][j]=w[i&1];if(j+1<=m) fin[i][j+1]=w[2+(i&1)];}
		ans=tot;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;ans=n*m+1;
	for(int i=1;i<=n;++i){cin>>s[i];s[i]=" "+s[i];fin[i].resize(m+2);}
	a[1]=1;a[2]=2;a[3]=3;a[4]=4;
	do{
		std::string w="";w+=t[a[1]];w+=t[a[2]];w+=t[a[3]];w+=t[a[4]];check2(w);check3(w);
	}while(std::next_permutation(a+1,a+5));//枚举填充顺序
	for(int i=1;i<=n;++i){for(int j=1;j<=m;++j) cout<<fin[i][j];cout<<'\n';}
	return 0;
}
```

---

## 作者：cmll02 (赞：0)

这题显然方案为如下格式：

```
ACACACAC...
GTGTGTGT...
CACACACA...
TGTGTGTG...
CACACACA...
...
```

或者

```
AGAC
TCTG
AGAG
TCTG
```

也就是间隔一行（或一列）用的是相同的两个字母。

那么我们枚举第一行和第一列所有可能的字母，然后算出修改数，这样就可以写出来了。

具体实现还是看代码吧。（由于我不想改，`min` 函数返回的是最大值）

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
inline int read()
{
    int num=0,f=1;char c=getchar();
    while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
    while(c>47&&c<58)num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num*f;
}
inline int min(int a,int b){return a<b?b:a;}
inline int max(int a,int b){return a<b?b:a;}
char** a;
int cow[303000][4][2],row[300006][4][2];//ATGC
int dist(char a,char b,char c,char d,int n,int m)
{
    int ans=0;
    for(int i=0;i<m;i+=2)ans+=max(cow[i][a][0]+cow[i][b][1],cow[i][b][0]+cow[i][a][1]);
    for(int i=1;i<m;i+=2)ans+=max(cow[i][c][0]+cow[i][d][1],cow[i][d][0]+cow[i][c][1]);
    return ans;
}
int dist_(char a,char b,char c,char d,int n,int m)
{
#define cow row
    int ans=0;
    for(int i=0;i<n;i+=2)ans+=max(cow[i][a][0]+cow[i][b][1],cow[i][b][0]+cow[i][a][1]);;
    //puts("");
    for(int i=1;i<n;i+=2)ans+=max(cow[i][c][0]+cow[i][d][1],cow[i][d][0]+cow[i][c][1]);;
    return ans;
#undef cow
}
void filcow(int aa,int b,int co,int n)
{
    for(int i=0;i<n;i++)
        a[i][co]=(i&1)?b:aa;
}
void filrow(int aa,int b,int ro,int m)
{
    //printf("filling %d %d %d %d\n",aa,b,ro,m);
    for(int i=0;i<m;i++)
        a[ro][i]=(i&1)?b:aa;
}
int printcow(int a,int b,int c,int d,int n,int m)
{
    //printf("%d\n",m);
    //printf("%d %d %d %d c \n",a,b,c,d);
    for(int i=0;i<m;i+=2)
    {
        if(cow[i][a][0]+cow[i][b][1]>cow[i][b][0]+cow[i][a][1])filcow(a,b,i,n);
        else filcow(b,a,i,n);
    }
    for(int i=1;i<m;i+=2)
    {
        if(cow[i][c][0]+cow[i][d][1]>cow[i][d][0]+cow[i][c][1])filcow(c,d,i,n);
        else filcow(d,c,i,n);
    }
    return 0;
}
int printrow(int a,int b,int c,int d,int n,int m)
{
    //printf("%d %d %d %d r \n",a,b,c,d);
#define cow row
    for(int i=0;i<n;i+=2)
    {
        if(cow[i][a][0]+cow[i][b][1]>cow[i][b][0]+cow[i][a][1])filrow(a,b,i,m);
        else filrow(b,a,i,m);
    }
    for(int i=1;i<n;i+=2)
    {
        if(cow[i][c][0]+cow[i][d][1]>cow[i][d][0]+cow[i][c][1])filrow(c,d,i,m);
        else filrow(d,c,i,m);
    }
#undef cow
    return 0;
}
char mmm[5]="ATGC";
inline int print(int n,int m)
{
    for(int i=0;i<n;i++,puts(""))for(int j=0;j<m;j++)putchar(mmm[a[i][j]]);
    return 0;
}
signed main()
{
    int n=read(),m=read();
    a=new char*[n];
    for(int i=0;i<n;i++)a[i]=new char[m+1],scanf("%s",a[i]);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(a[i][j]=='A')a[i][j]=0;
            else if(a[i][j]=='T')a[i][j]=1;
            else if(a[i][j]=='G')a[i][j]=2;
            else a[i][j]=3;
            cow[j][a[i][j]][(i)&1]++;
            row[i][a[i][j]][(j)&1]++;
        }
    }
    int ct,ca,cg,at,tg,ag,mina;
    int rct,rca,rcg,rat,rtg,rag,minb;
    ct=dist(3,1,0,2,n,m);
    ca=dist(3,0,1,2,n,m);
    cg=dist(3,2,0,1,n,m);
    at=dist(0,1,3,2,n,m);
    tg=dist(2,1,3,0,n,m);
    ag=dist(0,2,1,3,n,m);
    rct=dist_(3,1,0,2,n,m);
    rca=dist_(3,0,1,2,n,m);
    rcg=dist_(3,2,0,1,n,m);
    rat=dist_(0,1,3,2,n,m);
    rtg=dist_(2,1,3,0,n,m);
    rag=dist_(0,2,1,3,n,m);
    mina=min(ct,min(ca,min(cg,min(at,min(tg,ag)))));
    minb=min(rct,min(rca,min(rcg,min(rat,min(rtg,rag)))));
    int minn=min(mina,minb);

    //printf("%d %d %d %d %d %d\n",rct,rca,rcg,rat,rtg,rag);
    if(minn==ct){printcow(3,1,0,2,n,m);print(n,m);return 0;}
    if(minn==ca){printcow(3,0,1,2,n,m);print(n,m);return 0;}
    if(minn==cg){printcow(3,2,0,1,n,m);print(n,m);return 0;}
    if(minn==at){printcow(0,1,3,2,n,m);print(n,m);return 0;}
    if(minn==tg){printcow(2,1,3,0,n,m);print(n,m);return 0;}
    if(minn==ag){printcow(0,2,1,3,n,m);print(n,m);return 0;}
    if(minn==rct){printrow(3,1,0,2,n,m);print(n,m);return 0;}
    if(minn==rca){printrow(3,0,1,2,n,m);print(n,m);return 0;}
    if(minn==rcg){printrow(3,2,0,1,n,m);print(n,m);return 0;}
    if(minn==rat){printrow(0,1,3,2,n,m);print(n,m);return 0;}
    if(minn==rtg){printrow(2,1,3,0,n,m);print(n,m);return 0;}
    if(minn==rag){printrow(0,2,1,3,n,m);print(n,m);return 0;}
    //ATGC

    delete[ ] a;
}
```

---

