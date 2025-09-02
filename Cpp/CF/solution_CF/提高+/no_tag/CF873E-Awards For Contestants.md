# Awards For Contestants

## 题目描述

translated by @[RebelAlliance](https://www.luogu.org/space/show?uid=92461)


------------


Alexey最近为从Berland来的学生举办了一场编程测试，有 $n$ 个学生参加了测试，第 $i$ 个学生做出了 $a_{i}$ 道题。 现在他想授予一些学生文凭。Alexey可以授予学生三个不同学位的文凭。每个学生要么被授予一个学位的文凭，要么不被授予文凭。令 $cnt_{x}$ 表示被授予学位 $x$ 的文凭的学生数量。其满足一下条件：

* 对任意 $x$ $( 1 \leqslant x \leqslant 3 )$，满足 $cnt_{x} > 0$

* 对任意两个学位 $x$ 和 $y$，满足 $cnt_{x} \leqslant 2cnt_{y}$

当然，有很多种方法分发学位。令 $b_{i}$ 代表第 $i$ 个学生将获得文凭的学位（如果学生不会获得任何文凭则为 $-1$）。同时对任意的 $x$ $( 1 \leqslant x \leqslant 3 )$ 定义 $c_{x}$ 为所有获得学位 $x$ 的文凭的学生中做出最多题的学生做出的题目数量，$d_{x}$ 为所有获得学位 $x$ 的文凭的学生中做出最少题的学生做出的题目数量。Alexey想通过以下规则分发文凭：

1. 如果学生 $i$ 比学生 $j$ 做出了更多题目，那么他被授予的文凭不能比学生 $j$ 的差（不可能学生 $j$ 有文凭而学生 $i$ 没有，同时他们都有文凭但 $b_{j} < b_{i}$ 的情况也不会发生）

2. $d_{1} - c_{2}$ 取能取到的最大值

3. 在所有满足上一条的情况中，$d_{2} - c_{3}$ 取能取到的最大值

4. 在所有满足上一条的情况中，$d_{3} - c_{-1}$ 取能取到的最大值（ $c_{-1}$ 为所有没有获得文凭的学生中做出最多题的学生做出的题目数量，如果所有学生都有文凭则为 $0$ ）

帮助Alexey找到一种授予文凭的方法！

## 样例 #1

### 输入

```
4
1 2 3 4
```

### 输出

```
3 3 2 1 
```

## 样例 #2

### 输入

```
6
1 4 3 1 1 2
```

### 输出

```
-1 1 2 -1 -1 3 
```

# 题解

## 作者：Jorge_Filho (赞：1)

# CF873E Solution

## 题意（简化版）:
给定一个降序的序列，把其分成 $3\sim 4$ 段，要求前 $3$ 段每段长度都不大于前 $3$ 段中任意一段长度的 $2$ 倍，依次最大化段与段之间的间隔（即先最大化第一段的右端点与第二段的左端点的差，在这个基础上再最大化第二段的右端点与第三段的左端点的差，以此类推，若没有第四段，则第四段左端点视为的值视为 $0$）。

## 解析:

一个很显然的思路，枚举 $3$ 个断点，判断 $4$ 个区间长度是否合法即可。复杂度 $O(n^3)$，显然过不去。

考虑优化：先枚举前两个断点，对于第三个断点不再去枚举，而是直接找出间隔最小的。注意，这里第三个区间的长度是被限制了的，具体来讲：$\max\{ \left \lceil \frac{len_1}{2} \right \rceil,\left \lceil \frac{len_2}{2} \right \rceil \} \le len_3 \le \min\{2 \cdot len_1,2 \cdot len_2\}$。在这个范围内寻找最小的间隔，即静态差分数组的区间最小值，使用 ST 表即可。

时间复杂度：ST 表预处理 $O(n \cdot \log_2 n)$，查询 $O(1)$，枚举前两个断点 $O(n^2)$，总复杂度 $O(n^2)$。

具体实现细节较多，具体详见代码注释。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3,LN=12;
int n,l,r,x,y,flo,cei,ans1,ans2,ans3,loc1,loc2,loc3;
int f[LN+4][N+4],pos[LN+4][N+4],loga[N+4];

struct node
{
	int gra,wz,awa; 
}a[N+4];

inline bool Cmp1(const node &x,const node &y)//按照分数降序排序
{
	return x.gra>y.gra;
}

inline bool Cmp2(const node &x,const node &y)//按照输入顺序排序
{
	return x.wz<y.wz;
}

void Init()//St表初始化
{
	//预处理出1~n内每个数以2为底的对数
	for(int i=0;(1<<i)<=n;i++) loga[1<<i]=i;
	for(int i=1;i<=n;i++)
	{
		f[0][i]=a[i].gra-a[i+1].gra;
		pos[0][i]=i;
		if(loga[i]) continue;
		loga[i]=loga[i-1];
	}
	//St表需要做的是找出区间最小值所在的位置
	for(int j=1;j<=loga[n];j++)
	{
		int lim=n-(1<<j)+1;
		for(int i=1;i<=lim;i++)
			if(f[j-1][i]>f[j-1][i+(1<<(j-1))])
			{
				f[j][i]=f[j-1][i];
				pos[j][i]=pos[j-1][i];
			}
			else
			{
				f[j][i]=f[j-1][i+(1<<(j-1))];
				pos[j][i]=pos[j-1][i+(1<<(j-1))];
			}
	}
}

int Ask(const int &l,const int &r)//St表查询区间最小值所在的位置
{
	int ll=loga[r-l+1];
	if(f[ll][l]>f[ll][r-(1<<ll)+1]) return pos[ll][l];
	else return pos[ll][r-(1<<ll)+1];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].gra);
		a[i].wz=i;
	}
	sort(a+1,a+n+1,Cmp1)//按照分数排序
	Init();
	for(int i=1;i<=n;i++)//i枚举第一段的最后一个人
	{
		if(ans1>a[i].gra-a[i+1].gra) continue;//不优于目前的最好情况,无需讨论
		//对第二个区间长度的限制
		l=((i+1)>>1)+i;
		r=min((i<<1)+i,n);//注意不要超过n了
		for(int j=l;j<=r;j++)//j枚举第二段的最后一个人
		{
			if(ans1==a[i].gra-a[i+1].gra&&ans2>a[j].gra-a[j+1].gra) continue;//不优
			x=i;//第一段长度
			y=j-i;//第二段长度
			//对第三个区间长度的限制
			flo=max((x+1)>>1,(y+1)>>1)+j;
			cei=min(min(x<<1,y<<1)+j,n);//注意不要超过n了
			if(flo>cei) continue;
			int k=Ask(flo,cei);//k为第三段的最后一个人
			if(ans1==a[i].gra-a[i+1].gra&&ans2==a[j].gra-a[j+1].gra&&ans3>a[k].gra-a[k+1].gra) continue;//不优
			//更新答案 
			ans1=a[i].gra-a[i+1].gra;
			ans2=a[j].gra-a[j+1].gra;
			ans3=a[k].gra-a[k+1].gra;
			loc1=i;
			loc2=j;
			loc3=k;
		}
	}
	//确定好断点以后就可以开始颁奖了
	for(int i=1;i<=loc1;i++) a[i].awa=1;
	for(int i=loc1+1;i<=loc2;i++) a[i].awa=2;
	for(int i=loc2+1;i<=loc3;i++) a[i].awa=3;
	for(int i=loc3+1;i<=n;i++) a[i].awa=-1;
	//还原输入顺序准备输出
	sort(a+1,a+n+1,Cmp2);
	for(int i=1;i<=n;i++) printf("%d ",a[i].awa);
	return 0;
}
```
[AC记录](https://codeforces.com/contest/873/submission/191254525)（目前 Codeforces 全站最优解）

---

## 作者：bellmanford (赞：1)

首先将做题量从大到小排序，因为规则一，得到相同文凭的人在排好序以后一定是连续的一段区间，那么问题就转化为找出 $i,j,k\ (1\le i<j<k\le n)$ ， $[1,i],[i+1,j],[j+1,k]$ 这三个区间里的人分别获得 $1,2,3$ 类文凭，找出满足条件的最优方案。

假设 $s_x$ 是第 $x$ 个人的做题量，暴力枚举 $i,j,k$ 的效率是 $\mathcal{O(n^3)}$ ，~~事实证明处理的好是可以过的~~，注意最优是使得 $s_i-s_{i+1}$ 最大的同时分别让 $s_j-s_{j+1}$ 和 $s_k-s_{k+1}$ 最大，由于题目的限制，根据前面的 $i$ 不同，后面 $j,k$ 可选取的区间也不同，导致很难直接贪心，考虑到可接受的复杂度是 $\mathcal{O(n^2)}$ ，所以可以优化掉最后枚举 $k$ 的复杂度，可以发现选取的最大值只和 $k$ 有关，那就变为了一个区间求最大值的东西，可以枚举 $i,j$ ，最后 $k$ 的选取使用 ST 表维护。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=5005;

int read(){
    int x=0,y=1;char ch=getchar();
    while(ch<'0'||ch>'9') y=(ch=='-'?-1:1),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*y;
}

struct Stu{ int id,val; }s[M];int n,Ans[M];
bool cmp(Stu x,Stu y){ return x.val>y.val; }
int nowa=1,nowb=2,nowc=3,ST[M][M];
void solve(){
    n=read();
    for(int i=1;i<=n;i++) s[i].val=read(),s[i].id=i;
    sort(s+1,s+n+1,cmp);s[n+1].val=0;
    for(int i=1;i<=n;i++){
        ST[i][i]=i;int Max=s[i].val-s[i+1].val;
        for(int j=i+1;j<=n;j++){
            int v=s[j].val-s[j+1].val;
            if(v>Max) Max=v,ST[i][j]=j;
            else ST[i][j]=ST[i][j-1];
        }
    }
    for(int i=1;i<=n/2;i++){
        if(s[i].val-s[i+1].val<s[nowa].val-s[nowa+1].val) continue ;
        int lj=i+(i+1)/2,rj=min(i*3,n-(i+1)/2);
        for(int j=lj;j<=rj;j++){
            int lk=j+max((i+1)/2,(j-i+1)/2),rk=min(j+min(i*2,(j-i)*2),n);
            if(lk>rk) continue ;
            int k=ST[lk][rk];
            int va=s[i].val-s[i+1].val;
            int vb=s[j].val-s[j+1].val;
            int vc=s[k].val-s[k+1].val;
            int Ansa=s[nowa].val-s[nowa+1].val;
            int Ansb=s[nowb].val-s[nowb+1].val;
            int Ansc=s[nowc].val-s[nowc+1].val;
            if(va>Ansa||(va==Ansa&&(vb>Ansb||(vb==Ansb&&vc>Ansc)))) nowa=i,nowb=j,nowc=k;
        }
    }
    for(int i=1;i<=n;i++){
        if(i<=nowa) Ans[s[i].id]=1;
        else if(i<=nowb) Ans[s[i].id]=2;
        else if(i<=nowc) Ans[s[i].id]=3;
        else Ans[s[i].id]=-1;
    }
    for(int i=1;i<=n;i++) printf("%d ",Ans[i]);printf("\n");
}

signed main(){
    // freopen("shuju.in","r",stdin);
    solve();
}
```

---

