# Almost Fault-Tolerant Database

## 题目描述

You are storing an integer array of length $ m $ in a database. To maintain internal integrity and protect data, the database stores $ n $ copies of this array.

Unfortunately, the recent incident may have altered the stored information in every copy in the database.

It's believed, that the incident altered at most two elements in every copy. You need to recover the original array based on the current state of the database.

In case there are multiple ways to restore the array, report any. If there is no array that differs from every copy in no more than two positions, report that as well.

## 说明/提示

In the first example, the array $ [1, 10, 1, 100] $ differs from first and second copies in just one position, and from the third copy in two positions.

In the second example, array $ [1, 1, 1, 1, 1, 1, 1] $ is the same as the first copy and differs from all other copies in at most two positions.

In the third example, there is no array differing in at most two positions from every database's copy.

## 样例 #1

### 输入

```
3 4
1 10 10 100
1 1 1 100
10 100 1 100```

### 输出

```
Yes
1 10 1 100```

## 样例 #2

### 输入

```
10 7
1 1 1 1 1 1 1
1 1 1 1 1 1 2
1 1 1 1 1 2 2
1 1 1 1 2 2 1
1 1 1 2 2 1 1
1 1 2 2 1 1 1
1 2 2 1 1 1 1
2 2 1 1 1 1 1
2 1 1 1 1 1 1
1 1 1 1 1 1 1```

### 输出

```
Yes
1 1 1 1 1 1 1```

## 样例 #3

### 输入

```
2 5
2 2 1 1 1
1 1 2 2 2```

### 输出

```
No```

# 题解

## 作者：syksykCCC (赞：8)

**UPD: 修复了一处笔误**

---

不妨先考虑令 $ans = s_1$，跑一遍，找出每一个串与 $ans$ 的最大差距 $\Delta$ 和这个串的编号 $id$。

如果 $\Delta \le 2$，直接输出 $ans$ 就好了。

如果 $\Delta > 4$，必然无解。

现在只剩下 $\Delta = 3, 4$ 的情况。

后者是容易解决的，因为 $s_1, s_{id}$ 与真正的答案必然各有 $2$ 个不同。那么对于 $s_1$ 和 $s_{id}$ 不同的 $4$ 个位置，枚举其中哪两个是和 $s_1$ 一样，哪两个是和 $s_{id}$ 一样，剩下的 $m - 4$ 个位置必然与它们都相同，只需要检查至多 $\binom{4}{2} = 6$ 遍就行了。

着重研究一下 $\Delta = 3$ 的情况。

设真正的答案与 $s_1$ 差距为 $a$，真正的答案与 $s_{id}$ 差距为 $b$。因为 $s_1$ 和 $s_{id}$ 已经有 $3$ 个位置不同，所以 $a+b \ge 3$。同时，因为 $a \le 2, b \le 2$，所以 $a+b \le 4$。由此可知，$a+b \in \{ 3, 4 \}$。

记 $s_1$ 与 $s_{id}$ 不同的三个位置为 $x, y, z$。可不可能存在另一个 $p \notin \{x, y, z\}$，使得 $s_1/s_{id}$ 不同于真正的答案呢？

这是 **不可能** 的，因为如果存在这样的 $p$，必然导致 $a+b \ge 2 + 3 = 5$，矛盾。

现在考虑 $S = \{ans_x, ans_y, ans_z\}$ 分别应该是什么。

因为 $s_1$ 和 $s_{id}$ 有 $3$ 个位置不同，**可知 $S$ 中必然有一个元素与 $s_1$ 对应位置相同，$S$ 中也必然有另一个元素与 $s_{id}$ 对应位置相同**。这是显然的，因为不这样会导致 $a/b \ge 3$。

不失一般性的，设 $ans_x = s_{1, x}$，$ans_y = s_{id, y}$，这时候可以先随便设 $ans_z = s_{1, z}$，跑一遍，如果发现了另一个串 $id'$ 与现在的 $ans$ 有 $3$ 个不同，就可以令 $ans_z = s_{id', z}$，再检查一遍就行了。

上述过程枚举 $x, y$ 有 $\binom{3}{2} \binom{2}{1} = 6$ 种情况，每种情况至多检查 $2$ 遍，运算量接近 $12nm$。

综上，时间复杂度 $O(knm)$，$k \le 12$。为了偷懒，我下面代码写得比较丑（做了些不必要的检查），运算量可以达到 $18nm$，但这依然不影响通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2.5e5 + 5;
vector<int> s[N], ans;
int n, m;
void Print()
{
    cout << "Yes\n";
    for(int i = 1; i <= m; i++)
        cout << ans[i] << ' ';
}
int Comp(int idx)
{
    int res = 0;
    for(int i = 1; i <= m; i++)
    {
        if(s[idx][i] != ans[i]) res++;
    }
    return res;
}
int Comp(int idx, vector<int> &pos)
{
    int res = 0;
    pos.clear();
    for(int i = 1; i <= m; i++)
    {
        if(s[idx][i] != ans[i])
        {
            res++;
            pos.push_back(i);
        }
    }
    return res;
}
void Work(int &max_dif, int &pos)
{
    max_dif = -1;
    for(int i = 1; i <= n; i++)
    {
        int cur_dif = Comp(i);
        if(cur_dif > max_dif)
        {
            max_dif = cur_dif;
            pos = i;
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        s[i].resize(m + 5);
        for(int j = 1; j <= m; j++)
            cin >> s[i][j];
    }
    ans = s[1];
    int mx, line;
    Work(mx, line);
    if(mx <= 2)
    {
        Print();
        return 0;
    }
    else if(mx == 3)
    {
        vector<int> dif_pos;
        Comp(line, dif_pos);
        for(int chg = 1; chg < 7; chg++)
        {
            ans = s[1];
            for(int i = 0; i < 3; i++)
            {
                if(chg >> i & 1) ans[dif_pos[i]] = s[line][dif_pos[i]];
            }
            int new_mx, new_line;
            Work(new_mx, new_line);
            if(new_mx <= 2)
            {
                Print();
                return 0;
            }
            else if(new_mx == 3)
            {
                vector<int> new_dif_pos;
                Comp(new_line, new_dif_pos);
                for(int i = 0; i < 3; i++)
                {
                    int tmp = ans[new_dif_pos[i]];
                    ans[new_dif_pos[i]] = s[new_line][new_dif_pos[i]];
                    int final_mx, final_line;
                    Work(final_mx, final_line);
                    if(final_mx <= 2)
                    {
                        Print();
                        return 0;
                    }
                    ans[new_dif_pos[i]] = tmp;
                }
            }
        }
    }
    else if(mx == 4)
    {
        vector<int> dif_pos;
        Comp(line, dif_pos);
        for(int chg = 1; chg < 15; chg++)
        {
            ans = s[1];
            for(int i = 0; i < 4; i++)
            {
                if(chg >> i & 1) ans[dif_pos[i]] = s[line][dif_pos[i]];
            }
            int new_mx, new_line;
            Work(new_mx, new_line);
            if(new_mx <= 2)
            {
                Print();
                return 0;
            }
        }
    }
    cout << "No\n";
    return 0;
}
```

---

## 作者：7KByte (赞：6)

> 结论 $1$：如果两行的差异$>4$则无解。

因为我们可以构造出一个答案使得与两行的差异都是 $2$ 。

> 结论 $2$：答案一定是在任何一行的基础上改动不超过两个位置。

根据定义，答案与当前行差异不超过 $2 $，等价于改动两个位置使之完全相同。

我们可以假定答案是在第一行的基础上改动不超过两个。

那么我们需要先求出每一行与第一行的差异。如果差异为 $4$，则修改的两个位置一定是这四个不同的位置中的两个。同理，如果差异为 $3$，则最少要在这三个位置中修改$1$ 个。

那么可能修改的位置数量不超过 $\min\{M,4N\}$，是 $\rm O(\sqrt{NM})$ 级别的。

这样我们可以在这些可能的列上枚举两个列 $(i,j)$ 进行修改，注意这里的$(i,j)$是有序的。

> 结论 $3$：如果第 $k$ 行第 $i$ 列与第一行不同，且第 $k$ 行与第一行的差异 $>2$，则我们一定将第一行第 $i$ 列改为第 $k$ 行第 $i$ 列上的数。

证明：如果差异为 $4$ ，则第$i,j$列都必须修改。如果差异为 $3$，则$i,j$必须修改一个，枚举$(i,j)$则修改 $i$，枚举$(j,i)$ 则修改 $j$ 可以覆盖所有情况。

所以枚举$(i,j)$后我们可以算出这两位修改后的数，然后再检查一下是否为最终答案。

每次检查的时间复杂度为 $\rm O(N)$。

令 $T=N\times M$ 。如果$N\le M$，则$N\le \sqrt{T}$时间复杂度为$\rm O(N^3)$。否则$M\le \sqrt{T}$，时间复杂度为$\rm O(NM^2)$。事实上远不到这个上界。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 250005
using namespace std;
vector<int>a[N];int n,m,v[N],c[N],t,s[N],f[N];
bool check(int x,int y){
	int u=a[1][x],v=a[1][y];
	rep(i,2,n)f[i]=s[i];
	rep(i,2,n)if(f[i]>=3){u=a[i][x];break;}
	rep(i,2,n)if(a[i][x]==a[1][x]&&a[i][x]!=u)f[i]++;else if(a[i][x]!=a[1][x]&&a[i][x]==u)f[i]--;
	rep(i,2,n)if(f[i]>3){return false;}
	rep(i,2,n)if(f[i]==3){v=a[i][y];break;}
	rep(i,2,n)if(a[i][y]==a[1][y]&&a[i][y]!=v)f[i]++;else if(a[i][y]!=a[1][y]&&a[i][y]==v)f[i]--;
	rep(i,2,n)if(f[i]>2)return false;
	puts("Yes");
	rep(i,1,m)printf("%d ",i==x?u:(i==y?v:a[1][i]));
	putchar('\n');
	return true;
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)a[i].push_back(0);
	rep(i,1,n)rep(j,1,m){
		int x;scanf("%d",&x);
		a[i].push_back(x);
	}
	bool flag=true;
	rep(i,2,n){
		rep(j,1,m)s[i]+=a[i][j]!=a[1][j];
		if(s[i]>4){puts("No");return 0;}
		rep(j,1,m)v[j]|=a[i][j]!=a[1][j];
		flag&=s[i]<3;
	}
	rep(i,2,n)if(flag){
		puts("Yes");
		rep(j,1,m)printf("%d ",a[1][j]);putchar('\n');
		return 0;
	}
	rep(j,1,m)if(v[j])c[++t]=j;
	rep(i,1,t)rep(j,1,t)if(i!=j)if(check(c[i],c[j]))return 0;
	puts("No");
	return 0;
}
//By Inf_Voltage
```

---

## 作者：xuezhe (赞：5)

定义两个长度均为 $m$ 的序列 $A,B$ 的差异为 $\sum_{i=1}^m [A_i \neq B_i]$。

将第 $1$ 个序列作为基准序列。

首先可以发现 $n$ 与 $m$ 必有至少一个小于等于 $\sqrt{nm}$。

往这个方向考虑，结合每个序列被修改不超过 $2$ 次，可以发现基准序列中至多有 $2n$ 个数是与其中一个序列对应位置不同的，否则必然无解。于是只需要考虑 $\min\{2n,m\}$ 个数。

然后先看答案序列是否可以是基准序列，如果不行就假装基准序列中有两个数被修改了。

然后就到了喜闻乐见的大力分类环节。

枚举被修改的两个数的位置 $i,j$，如果扣掉这两个数的贡献是否存在一个序列依然存在一个序列与基准序列的差距超过 $2$，则不可能是这两个数被修改。

否则如果存在一个序列 $s_k$ 与基准序列的差距恰为 $2$，则将这基准序列中 $i$ 和 $j$ 两个位置的数分别修改为 $s_{k,i}$ 与 $s_{k,j}$，然后验证这个序列是否能作为答案序列。

否则必然存在若干序列与基准序列的差距为 $1$，将这些序列全部找出来，对于每个这样的序列，将基准序列的 $i$ 与 $j$ 修改后必然有一个和这个序列中对应位置上的数相同。

于是考虑枚举 $x$，将基准序列中的第 $i$ 个数修改成 $x$，然后如果存在序列 $s_k$ 满足 $s_k$ 与基准序列的差距为 $1$ 且 $s_{k,i} \neq x$，将基准序列中的第 $j$ 个数修改成 $s_{k,j}$ 后数一下是否每个都符合条件了。

如果找不到就判定无解。

最终实现的时间复杂度是 $O(nm\sqrt{nm} \log n)$，可能可以去掉一个 $\log$，比标算劣。

Code:
```cpp
typedef pair<int,int> pii;
int n,m,s[250005],v[250005],d[250005],o[250005],otot;
vector< vector<int> > a,b,c;
vector<int> f;
vector<pii> vl;
 
void fakemain(){
    Read(n),Read(m);
    a.resize(n+1);
    b.resize(n+1);
    c.resize(n+1);
    for(int i=1;i<=n;++i){
        a[i].resize(m+1);
        for(int j=1;j<=m;++j){
            Read(a[i][j]);
            o[++otot]=a[i][j];
        }
        b[i].resize(m+1);
        b[i][0]=0;
        for(int j=1;j<=m;++j){
            if(a[1][j]!=a[i][j])
                b[i][j]=1,++s[i],v[j]=1;
        }
        c[i].resize(m+1);
    }
    sort(o+1,o+1+otot);
    otot=unique(o+1,o+1+otot)-(o+1);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            c[i][j]=lower_bound(o+1,o+1+otot,a[i][j])-o;
    int s_=0;
    for(int i=1;i<=m;++i)
        s_+=v[i];
    if(s_>n*2){
        puts("No");
    }else{
        int owo=1;
        for(int i=2;i<=n;++i)
            if(s[i]>2){
                owo=0;
                break;
            }
        if(owo){
            puts("Yes");
            for(int i=1;i<=m;++i)
                printf("%d%c",a[1][i]," \n"[i==m]);
            return;
        }
        if(s_<=2){
            puts("Yes");
            for(int i=1;i<=m;++i)
                printf("%d%c",a[1][i]," \n"[i==m]);
            return;
        }else{
            for(int i=1;i<=m;++i)
                if(v[i])
                    f.push_back(i);
            for(int i=0;i<int(f.size());++i){
                for(int j=i+1;j<int(f.size());++j){
                    int flg=true,t2=0;
                    for(int k=2;k<=n;++k){
                        if(s[k]-b[k][f[i]]-b[k][f[j]]>2){
                            flg=false;
                            break;
                        }
                        if(s[k]-b[k][f[i]]-b[k][f[j]]==2)
                            t2=k;
                    }
                    if(flg){
                        if(t2){
                            for(int k=2;k<=n;++k)
                                if(s[k]-b[k][f[i]]-b[k][f[j]]+(a[k][f[i]]!=a[t2][f[i]])+(a[k][f[j]]!=a[t2][f[j]])>2){
                                    flg=false;
                                    break;
                                }
                            if(flg){
                                a[1][f[i]]=a[t2][f[i]],a[1][f[j]]=a[t2][f[j]];
                                puts("Yes");
                                for(int k=1;k<=m;++k)
                                    printf("%d%c",a[1][k]," \n"[k==m]);
                                return;
                            }
                        }else{
                            vl.clear();
                            for(int k=2;k<=n;++k)
                                if(s[k]-b[k][f[i]]-b[k][f[j]]==1)
                                    vl.push_back(pii(a[k][f[i]],k));
                            if(!vl.size()){
                                puts("Yes");
                                for(int k=1;k<=m;++k)
                                    printf("%d%c",a[1][k]," \n"[k==m]);
                                return;
                            }else{
                                sort(vl.begin(),vl.end());
                                for(int k=0;k<int(vl.size());++k)
                                    ++d[c[vl[k].second][f[j]]];
                                for(int l=0,r;l<int(vl.size());l=r){
                                    for(r=l+1;r<int(vl.size()) && vl[l].first==vl[r].first;++r);
                                    for(int k=l;k<r;++k)
                                        --d[c[vl[k].second][f[j]]];
                                    if(l==0 && r==int(vl.size())){
                                        a[1][f[i]]=vl[0].first;
                                        puts("Yes");
                                        for(int k=1;k<=m;++k)
                                            printf("%d%c",a[1][k]," \n"[k==m]);
                                        return;
                                    }else{
                                        if(l!=0){
                                            if(r-l+d[c[vl[0].second][f[j]]]==int(vl.size())){
                                                a[1][f[i]]=vl[l].first,a[1][f[j]]=a[vl[0].second][f[j]];
                                                puts("Yes");
                                                for(int k=1;k<=m;++k)
                                                    printf("%d%c",a[1][k]," \n"[k==m]);
                                                return;
                                            }
                                        }else{
                                            if(r-l+d[c[vl[r].second][f[j]]]==int(vl.size())){
                                                a[1][f[i]]=vl[l].first,a[1][f[j]]=a[vl[r].second][f[j]];
                                                puts("Yes");
                                                for(int k=1;k<=m;++k)
                                                    printf("%d%c",a[1][k]," \n"[k==m]);
                                                return;
                                            }
                                        }
                                    }
                                    for(int k=l;k<r;++k)
                                        ++d[c[vl[k].second][f[j]]];
                                }
                                for(int k=0;k<int(vl.size());++k)
                                    --d[c[vl[k].second][f[j]]];
                            }
                        }
                    }
                }
            }
        }
        puts("No");
    }
}
```

---

## 作者：Ephemeroptera (赞：2)


### 题意简述：  
给你 $n$ 个序列，请你构造出一个序列满足对给出的每一个序列不同处小于等于 $2$。
### Solution：
因为要构造一串序列要满足与任意序列的不同处不超过 $2$ ，不如就直接取第一个序列然后加之修改。 

考虑第一个序列和其余序列可能存在的情况：

1. 和一个串的不同处 $>4$ ，这时无论如何都是无解。
2. 和每一个串的不同处 $ \le 2$ ，这时这一个序列就可以是答案。
3. 存在一些序列不同处 $=3,4$ ，考虑如何处理使不同处减小到 $2$ 以下。  


首先不难发现，如果只有一对不同串不同处大于 $2$，我们可以去枚举造成不同的位置  ，对其进行更改，使现在不同处 $\le 2$，然后去检查修改后的串是否满足整个序列不同处 $\le 2$。  

如果此时只有三个串不同处大于 $2$，我们可以任意选择一个串进行修改，因为每次修改都是枚举完了所有不同处的情况的，如果此时修改后检查不合法，那么枚举另一个串修改了检查时也会不合法。    

所以一开始选取一个与第一个串不同处最多的串，然后枚举修改的位置即可。  

注意到有可能修改会修改成为其余序列的值，所以将其中一个设定为 $-1$ 处理，表示这个位置可以被修改。

最终实现的复杂度为 $O(nm)$ ,常数不大。


[CODE](https://www.luogu.com.cn/paste/tzudnj5p)

---

## 作者：Piwry (赞：1)

## 解析

首先答案序列显然可以看做第一个序列拷贝再修改其中至多两个元素

不妨以第一个序列为标准，逐步调整得到答案

首先直接扫一遍求出其它序列（即除首个序列外）与当前序列的不同数（同位置值不同的元素个数）

1. 如果存在序列与当前序列的不同数 $\geq5$，那么显然在两步修改内无法使这两个序列相等，即无解
2. 如果所有序列与当前序列的不同数都 $\leq 2$，那么显然已经找到了解

排除掉这两个情况后，所有序列与当前序列的不同数均 $\leq 4$。我们随便挑一个与其不同数 $>2$ 的序列 $\{x_i\}$；由于至多两次的修改后，我们必须使这两个序列的不同数 $\leq 2$，因此当前序列的所有值不同的位置中必定有几个（$1$ 或 $2$ 个）要修改为 $\{x_i\}$ 对应位置的值，这里先枚举修改其中的一个。接着还剩一次修改，可以直接递归一层用同样的方式做（可以参考代码理解qaq）

至于复杂度，不难发现函数最多递归三层，其中 一、二 层均至多枚举 $4$ 次，最后一层不会接着向下枚举递归；因此总复杂度是 $O(4^2nm)$ 的，且并不容易跑满

## CODE

代码里记录了父层修改过的位置，并在之后（子层）不再枚举这些位置；这其实只能在某些情况下稍微优化下时间，不加也无大碍

```cpp
#include <cstdio>
#include <vector>
#include <cstdlib>
using std::vector;
using std::pair;
typedef pair<int, int> pad;

/*------------------------------IO------------------------------*/

namespace IO_number{
	int read(){
		int x =0; char c =getchar(); bool f =0;
		while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
		while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
		return (f) ? -x : x;
	}
	
	void write(const int &x){
		if(x < 0){
			putchar('-');
			write(-x);
		}
		else{
			if(x/10)
				write(x/10);
			putchar('0'+x%10);
		}
	}
}
using namespace IO_number;

/*------------------------------Main------------------------------*/

int n, m;
vector<vector<int> > a;
vector<bool> fixed;

inline void Ans(const int &typ){
	if(typ == -1)
		puts("No");
	else{
		puts("Yes");
		for(int i =0; i < m; ++i)
			write(a[0][i]), putchar(' ');
	}
	exit(0);
}

void modify(const int &cnt_modify_left){
	int mx_dif =0, i_mx_dif =-1;
	for(int i =1; i < n; ++i){
		int cnt =0;
		for(int j =0; j < m; ++j)
			if(a[i][j] != a[0][j])
				++cnt;
		if(cnt > mx_dif)
			mx_dif =cnt, i_mx_dif =i;
	}
	
	if(mx_dif <= 2)
		Ans(1);
	else if(mx_dif >= 5)
		return;
	else if(cnt_modify_left <= 0)
		return;
	else{
		for(int j =0; j < m; ++j)
			if(a[i_mx_dif][j] != a[0][j] && !fixed[j]){
				const int tmp =a[0][j];
				a[0][j] =a[i_mx_dif][j];
				fixed[j] =1;
				modify(cnt_modify_left-1);
				a[0][j] =tmp;
				fixed[j] =0;
			}
	}
}

int main(){
	n =read(), m =read();
	a =vector<vector<int> >(n, vector<int>(m));
	fixed =vector<bool>(m, 0);
	for(int i =0; i < n; ++i)
		for(int j =0; j < m; ++j)
			a[i][j] =read();
	
	modify(2);
	Ans(-1);
}
```

---

## 作者：lfxxx (赞：0)

考虑增量构造。

先以序列 $1$ 为答案，依次加入后面的序列。

假若与当前的答案序列差别大于 $4$，根据抽屉原理，一定无解。

假若差别为 $4$，一定是两个序列均与答案序列差别为 $2$，于是有 $4 \choose 2$ 种情况，暴力枚举 check 即可。

假若差别为 $3$，你发现两个序列与答案序列的差异一定大于等于 $1$ 且小于等于 $2$，于是对于不同的三个位置，一定是一个与第一个序列相同，另一个与当前枚举的序列相同，还有一个不确定，于是我们需要 check 共 $3!$ 个有一个位置不确定的序列，考虑将其他位置差别已经为 $2$ 的序列在不确定的位置上的值拿出来看是不是同一个数即可。

假若差别小于等于 $2$，就一直跑直到遇到上面的情况或者全部跑完，假若全部跑完了，就直接以序列 $1$ 为答案即可。

时间复杂度 $O(n \times m)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+114;
vector<int> a[maxn];
int n,m;
vector<int> diff(vector<int> x,vector<int> y){
    vector<int> res;
    for(int i=1;i<=m;i++){
        if(x[i]!=y[i]) res.push_back(i);
    }
    return res;
}
vector<int> ans;
bool check(){
    vector<int> vec;
    for(int i=1;i<=n;i++){
        int res=0;
        for(int j=1;j<=m;j++){
            if(ans[j]!=-1){
                if(ans[j]!=a[i][j]) res++;
            }
        }
        if(res>2) return false; 
        if(res==2) vec.push_back(i);
    }
    if(vec.size()==0){
        for(int i=1;i<=m;i++)
            if(ans[i]==-1) ans[i]=114514;
        return true;
    }
    for(int i=1;i<=m;i++){
        if(ans[i]==-1){
            for(int j=1;j<vec.size();j++)
                if(a[vec[j]][i]!=a[vec[0]][i]) return false;
            ans[i]=a[vec[0]][i];
        }
    }
    return true;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        a[i].push_back(0);
        for(int j=1;j<=m;j++){
            int x;
            cin>>x;
            a[i].push_back(x);
        }
    }
    for(int i=2;i<=n;i++){
        vector<int> vec=diff(a[i],a[1]);
        if(vec.size()>4){
            cout<<"No\n";
            return 0;
        }else if(vec.size()==4){
            ans=a[1];
            for(int v=0;v<16;v++){
                if(__builtin_popcount(v)==2){
                    for(int p=0;p<4;p++)
                        if((1<<p)&v) ans[vec[p]]=a[i][vec[p]];
                        else ans[vec[p]]=a[1][vec[p]];
                    if(check()==true){
                        cout<<"Yes\n";
                        for(int x=1;x<=m;x++) cout<<ans[x]<<' ';
                        return 0;
                    }
                }
            }
            cout<<"No\n";
            return 0;
        }else if(vec.size()==3){
            ans=a[1];
            for(int v=0;v<8;v++){
                if(__builtin_popcount(v)==2){
                    for(int v1=v;v1;v1=(v1-1)&v){
                        if(__builtin_popcount(v1)==1){
                            for(int p=0;p<3;p++){
                                if(!((1<<p)&v)) ans[vec[p]]=-1;
                                else if((1<<p)&v1) ans[vec[p]]=a[1][vec[p]];
                                else ans[vec[p]]=a[i][vec[p]];
                            }
                            if(check()==true){
                                cout<<"Yes\n";
                                for(int x=1;x<=m;x++) cout<<ans[x]<<' ';
                                return 0;
                            }
                        }
                    }
                }
            }
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";
    for(int x=1;x<=m;x++) cout<<a[1][x]<<' ';
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

首先明确一下题目目标：

> 构造一个序列 $ans$，使得其分别与 $a_1, a_2, ..., a_n$ 的差异值都不超过 $2$。

发现差异值不超过 $2$，这个限制是很小的，所以引导我们进行 case 分讨。

首先我们不难注意到：

- 如果对于 $a_i, a_j$ 两个序列，其差异值 $> 4$，那么肯定无解。

感性不难理解，证明的话考虑到其差异值 $> 4$，我最优就是一个差 $2$ 个元素，一个差 $3$ 个元素，也就是说我无法找到一个合适的中间序列来连接 $a_i, a_j$ 的关系。

但是其实我的做法和这个判无解没有啥关系，因为判无解是 $O(n^2 m)$，并且似乎没有啥很好的优化方式。

其次我们又注意到：

- 最终的 $ans$ 与 $a_1$ 的差异值不会超过 $2$，也就是说 $ans$ 只会在 $a_1$ 的基础上更改 $2$ 个元素。

于是我们不妨钦定 $a_1$ 来进行分讨（注意以下情况只要对于一个 $i$ 挂掉了就是无解，如果你打开我的提交记录 WA 的那两发都是因为我情况 $3$ 写错了导致的，下面会提到）：

情况 $1$：$a_1$ 与 $a_i$ 的差异值 $\le 2$，此时啥都不用管，直接跳就好。

---

情况 $2$：$a_1$ 与 $a_i$ 的差异值 $= 4$，那么我们大胆猜结论，$4$ 个不同的数中，一定是 $ans$ 改 $2$ 个 $a_1$ 的元素，改 $2$ 个 $a_i$ 的元素，于是我们直接枚举改哪两个就好，感觉也不难证明。

---

情况 $3$：$a_1$ 与 $a_i$ 的差异值 $= 3$，依靠情况 $2$，我们可以猜测肯定有 $1$ 个或者 $2$ 改成 $a_1$，剩下的改成 $a_i$，恭喜你，[WA on test 32](https://codeforces.com/contest/1492/submission/286074202)。

考虑这个贪心为什么是不对的，其实是因为我本质上可以更改 $4$ 个位置，但是我只有 $3$ 个位置对不上，所以我只填了 $3$ 个位置，还可以填一个位置，我们浪费了这个机会。

于是我们更改我们的结论：我们先在 $3$ 个数中枚举 $1$ 个数将其更改为 $a_1$ 元素，然后剩下的 $2$ 个数更改为 $a_i$ 元素，然后我们枚举所有序列，发现有一个序列与当前 $ans$ 的差异值 $> 2$ 时我们尝试修改其中一个差异元素，再次检查，如果检查不过就是不行，否则就是可以。

然后我按照这三种 case 写了一发，$156 ms$ 轻松 A。

仔细分析一下发现复杂度貌似是 $O(nm)$？反正能过就行。

## Code

Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 3e5 + 5;

int n, m;
vector < int > a[N], tmp;

bool check ( vector < int > tmp ) {
  for ( int i = 1; i <= n; i ++ ) {
    int cnt = 0;
    for ( int j = 0; j < m; j ++ ) {
      cnt += ( a[i][j] != tmp[j] );
    }
    if ( cnt > 2 ) {
      return false;
    }
  }
  return true;
}

void Solve () {
  ios :: sync_with_stdio ( false );
  cin.tie ( 0 ), cout.tie ( 0 );
  cin >> n >> m;
  for ( int i = 1; i <= n; i ++ ) {
    for ( int j = 1; j <= m; j ++ ) {
      int x;
      cin >> x;
      a[i].push_back ( x );
    }
  }
  for ( int i = 1; i <= m; i ++ ) {
    tmp.push_back ( 0 );
  }
  for ( int i = 2; i <= n; i ++ ) {
    vector < int > pos;
    for ( int j = 0; j < m; j ++ ) {
      if ( a[1][j] != a[i][j] ) {
        pos.push_back ( j );
      }
    }
    if ( pos.size () > 4 ) {
      cout << "No";
      return ;
    }
    if ( pos.size () == 4 ) {
      for ( int x : pos ) {
        for ( int y : pos ) {
          for ( int j = 0; j < m; j ++ ) {
            tmp[j] = ( j == x || j == y ? a[1][j] : a[i][j] );
          }
          if ( check ( tmp ) ) {
            cout << "Yes\n";
            for ( int j = 0; j < m; j ++ ) {
              cout << tmp[j] << " ";
            }
            return ;
          }
        }
      }
      cout << "No";
      return ;
    }
    else if ( pos.size () == 3 ) {
      for ( int x : pos ) {
        for ( int j = 0; j < m; j ++ ) {
          tmp[j] = ( j != x ? a[1][j] : a[i][j] );
        }
        if ( check ( tmp ) ) {
          cout << "Yes\n";
          for ( int j = 0; j < m; j ++ ) {
            cout << tmp[j] << " ";
          }
          return ;
        }
        for ( int j = 1; j <= n; j ++ ) {
          int cnt = 0;
          for ( int k = 0; k < m; k ++ ) {
            cnt += ( a[j][k] != tmp[k] );
          }
          if ( cnt > 2 ) {
            for ( int k = 0; k < m; k ++ ) {
              if ( a[j][k] != tmp[k] ) {
                int chifan = tmp[k];
                tmp[k] = a[j][k];
                if ( check ( tmp ) ) {
                  cout << "Yes\n";
                  for ( int j = 0; j < m; j ++ ) {
                    cout << tmp[j] << " ";
                  }
                  return ;
                }
                tmp[k] = chifan;
              }
            }
            break;
          }
        }
      }
      cout << "No";
      return ;
    }
  }
  for ( int j = 0; j < m; j ++ ) {
    tmp[j] = a[1][j];
  }
  if ( check ( tmp ) ) {
    cout << "Yes\n";
    for ( int i = 0; i < m; i ++ ) {
      cout << a[1][i] << " ";
    }
  }
  else {
    cout << "No";
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

$\textbf{CF1492E}$

首先找到一个不是全相同的列 $i$，那么必定有至少一行会产生 $1$ 个不同的值。随便找两个值不一样的行即可，以下记这一行为 $c$。

注意到最终的序列 $s$ 除去第 $i$ 列外只有一个位置和 $a_c$ 不同，枚举这一列 $j$，容易计算出每一行和 $s$ 除去 $i,j$ 两列的不同数量 $d_i$。

- $d_i = 0$ 的行不会带来任何限制。（即使 $i,j$ 两列全都不同也合法）
- $d_i = 1$ 的行里 $i,j$ 两列至少有一个和这一行相等。
- $d_i = 2$ 的行里 $i,j$ 两列都和这一行相等。

那我们随意找到一个 $d_i > 0$ 的行，即可确定一列的值。然后只剩下一个待确定的列，重新计算 $d'_i$ 后只有 $d'_i = 2$ 会带来限制，填入 $d'_i = 2$ 的行值即可。

时间复杂度 $\mathcal O(nm)$，常数比较大。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 02.09.2024 20:42:48
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,m,ans[N],fg,fm; vector<int> a[N];
void ck(int c,int st){
    vector<vector<int>> pr(n + 1,vector<int>(m + 2)),
                        sf(n + 1,vector<int>(m + 2));
    for(int i = 1;i <= n;i ++){
        for(int j = fm;j <= m;j ++)
            pr[i][j] = pr[i][j - 1] + (a[i][j] != a[c][j]);
        for(int j = m;j >= fm;j --)
            sf[i][j] = sf[i][j + 1] + (a[i][j] != a[c][j]);
    }for(int i = fm;i <= m;i ++){
        vector<int> rw(n + 1); int t = 0;
        for(int j = 1;j <= n;j ++){
            rw[j] = pr[j][i-1] + sf[j][i+1];
            if(rw[j]) t = j;
        }if(!t){
            fg = 1;
            for(int j = 1;j <= m;j ++) ans[j] = a[c][j];
            return ;
        }auto test = [&](int cl,int ml){
            int mt = 0; auto r = rw;
            for(int i = 1;i <= n;i ++) if(a[i][ml] != a[t][ml]) r[i] ++;
            if(*max_element(r.begin(),r.end()) > 2) return 0;
            for(int i = 1;i <= n;i ++) if(r[i] == 2){
                if(mt && a[i][cl] != mt) return 0;
                mt = a[i][cl]; 
            }for(int i = 1;i <= m;i ++) ans[i] = a[c][i];
            ans[ml] = a[t][ml],ans[cl] = mt ? mt : a[t][cl];
            return 1;
        };if(test(i,fm - 1)) return fg = 1,void();
        if(test(fm - 1,i)) return fg = 1,void();
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m; int fuck;
    if(m == 1) return cin >> fuck,cout << "Yes\n" << fuck << "\n",0;
    for(int i = 1;i <= n;i ++){
        a[i].resize(m + 1);
        for(int j = 1;j <= m;j ++) cin >> a[i][j];
    }int c = 1;
    while(c <= m){
        int bt = a[1][c];
        for(int i = 1;i <= n;i ++) if(a[i][c] != bt) bt = -1;
        if(bt == -1) break; else c ++;
    }if(c > m){
        cout << "Yes\n";
        for(int i = 1;i <= m;i ++) cout << a[1][i] << " \n"[i == m];
        return 0;
    }int bt = 0; fm = c + 1;
    for(int i = 1;i <= n;i ++){
        if(a[i][c] != bt){
            ck(i,a[i][c]);
            if(fg){
                cout << "Yes\n";
                for(int j = 1;j <= m;j ++) cout << ans[j] << " \n"[j == m];
                return 0;
            }if(!bt) bt = a[i][c]; else break;
        }
    }cout << "No\n";
}
```

---

## 作者：xh39 (赞：0)

**注:本题解时间复杂度 $O(36n^2+nm)$ 不保证正确。**

正确数据在任意一行上改变不超过 $2$。所以设第一行为标准行，要求出改第一行的哪两个数。

如果直接枚举，需要 $O(m^{2})$，所以肯定不能直接枚举。需要观察一下可能改的数有什么规律。

改的数肯定是与第一行不同的数。若相同，改了反而会使差异更大。

设第一行与第 $i$ 行的差异为 $dif[i]$。差异定义为 一个位置上的元素不同 的个数。于是对 $dif$ 进行分类讨论。

$dif\geq5$:此种情况肯定无解。不管怎么改，总会是一行差异超过 $2$。

$dif=4$:一定是要改变差异中的 $2$ 个。于是枚举哪两个。然后判断是否可行。由于只有4个，所以全部枚举也只需要 $C^{2}_{4}=6(\text{次})$ 即可。

$dif=3$:此种情况比较复杂。如果单纯改其中的 $2$ 个，会被这一组数据卡掉:
```cpp
3 3
0 1 2
3 4 5
6 7 8
```
这时，需要把 $1$ 改为 $4$，把 $2$ 改为 $8$。所以有可能改过的答案来自不同的 $2$ 行。

这时，需要枚举到底来自哪两行。同样，只会来自差异部分。

时间复杂度:此时并**不**是要枚举 $O(n^{2})$ 种情况。$dif[i]\leq3$，意味着至少要改成这一行中的一个差异。否则这一行差异不会变小，这样就无解了。所以只需要 $O(n)$ 找到其中一个 $dif[i]==3$ 的行，然后枚举所有的 $dif[j]=3$ 且 $i!=j$ 的 $j$。所以只需要 $O(n)$ 即可。

$dif\leq2$:此时无法判断是否改了。所以此信息对我们没用。如果仅有 $dif<=2$ 的行，直接输出第一行即可。

现在需要解决如何 $O(n)$ 求修改 $2$ 个数后的差异。枚举每一行，看改对(指原来错，现在对)有多少个，改错(原来对，现在错)有多少个，然后直接 $\text{总差异}\gets dif[i]-\text{改对}+\text{改错}$。具体见代码。

细节:因本题未单独限定 $n$ 与 $m$ 的范围，所以直接开二维数组不可取。于是模拟系统建二维数组的思路，$a[i][j]$ 表示为 $a[i\times m+j]$。这可以理解为简单的 有序数对hash。

总时间复杂度:$O(n^{2}+nm)$，常数为 $9\times 4=36$。
 
虽然时间复杂度较高，在 $n$ 很大的时候过不了，但是 codeforces 貌似没卡。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int dif[1000005][7],tot[1000005],a[1000005],n,m; //第i行第j列:m*i+j。 
void check(int b,int c,int d,int e){ //将位置b修改为c,将位置d修改为e。
	if(b==d){ //如果b与d相同,说明只改了一个。此种情况已经枚举过了,故可直接返回。若不返回,则需将d,e设为-1。避免计算改对与改错时出错。
		return;
	} 
	int i,j,sum=0,dui,cuo;
	bool ykbb,ykbd; //ykbb表示b有没有改对一个数,ykbd表示d有没有改对一个数。
	for(i=1;i<n;i++){
		//对:之前没对&&现在对了。错:之前对了,现在错了。 
		dui=0;
		ykbb=(b>=0&&a[b]!=c); //一开始要是对的,才可能改错。
		ykbd=(d>=0&&a[d]!=e); //判b,d为正的原因:若其为负,则说明该元素不改,详见main函数调用部分。
		for(j=0;j<tot[i];j++){ //枚举差异。改对的元素只可能在这里面产生。
			dui+=(b==dif[i][j]&&a[i*m+b]==c)+(d==dif[i][j]&&a[i*m+d]==e); //b与其相等才可能改对该元素。而b相等的情况下,值与c(现在的数)相同即为改对。
			ykbb&=(b!=dif[i][j]); //若b与dif相等,则说明之前也是错的。最终答案取与即表示原先所有的差异位置都不与b相同。
			ykbd&=(d!=dif[i][j]);
		}
		cuo=ykbb+ykbd; //二者相加表示改错了多少。
		if(tot[i]-dui+cuo>2){
			return;
		}
	}
	cout<<"Yes"<<endl;
	for(i=0;i<m;i++){
		if(i==b){ //被改成b的部分输出c,改成d的部分输出e。否则未改,输出原值。
			cout<<c<<" ";
		}else if(i==d){
			cout<<e<<" ";
		}else{
			cout<<a[i]<<" ";
		}
	}
	exit(0); //找到解了,直接结束程序。未结束说明该方案不可取。相当于return false;
}
int main(){
	int i,j;
	bool ykb=0;
	cin>>n>>m;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d",a+m*i+j);
		}
	}
	for(i=1;i<n;i++){
		dif[i][0]=m+1;
		dif[i][1]=m+1;
		dif[i][2]=m+1;
		dif[i][3]=m+1;
		for(j=0;j<m;j++){
			if(a[j]!=a[m*i+j]){
				dif[i][tot[i]++]=j;
			}
		}
		if(tot[i]>=5)
			cout<<"No";
			return 0;
		}
	}
	for(i=0;i<n;i++){
		if(tot[i]==4){
			check(dif[i][0],a[m*i+dif[i][0]],dif[i][1],a[m*i+dif[i][1]]);
			check(dif[i][0],a[m*i+dif[i][0]],dif[i][2],a[m*i+dif[i][2]]);
			check(dif[i][0],a[m*i+dif[i][0]],dif[i][3],a[m*i+dif[i][3]]);
			check(dif[i][1],a[m*i+dif[i][1]],dif[i][2],a[m*i+dif[i][2]]);
			check(dif[i][1],a[m*i+dif[i][1]],dif[i][3],a[m*i+dif[i][3]]);
			check(dif[i][2],a[m*i+dif[i][2]],dif[i][3],a[m*i+dif[i][3]]);
			cout<<"No";
			return 0;
		}
	}
	for(i=1;i<n;i++){
		if(tot[i]==3){
			check(dif[i][0],a[m*i+dif[i][0]],-3,-3); //现在只要改一个元素,那么第二个修改值定为原数组中不存在的下标,就相当于没改。
			check(dif[i][1],a[m*i+dif[i][1]],-3,-3);
			check(dif[i][2],a[m*i+dif[i][2]],-3,-3);
			for(j=1;j<n;j++){
				if(i!=j){
					check(dif[i][0],a[m*i+dif[i][0]],dif[j][1],a[m*j+dif[j][1]]);
					check(dif[i][0],a[m*i+dif[i][0]],dif[j][2],a[m*j+dif[j][2]]);
					check(dif[i][1],a[m*i+dif[i][1]],dif[j][0],a[m*j+dif[j][0]]);
					check(dif[i][1],a[m*i+dif[i][1]],dif[j][2],a[m*j+dif[j][2]]);
					check(dif[i][2],a[m*i+dif[i][2]],dif[j][0],a[m*j+dif[j][0]]);
					check(dif[i][2],a[m*i+dif[i][2]],dif[j][1],a[m*j+dif[j][1]]);
				}
			}
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes"<<endl; //说明未出现>=3的情况,若出现,早就返回了。
	for(i=0;i<m;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```
附一组可以卡掉本算法的数据(生成在 ```1.in```)(*windows7* 下跑了  $81.76$s):
```cpp
#include<iostream>
using namespace std;
int main(){
    freopen("1.in","w",stdout);
    int i;
    cout<<"83333 3"<<endl;
    for(i=0;i<40000;i++){
        cout<<"0 0 0"<<endl;
    }
    for(i=0;i<43333;i++){
        cout<<i*3<<" "<<i*3+1<<" "<<i*3+2<<endl;
    }
    return 0;
}
```

---

