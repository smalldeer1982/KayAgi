# Party Organization

## 题目描述

在伟大的巴尔提亚岛上居住着 $N$ 个人，编号从 $1$ 到 $N$ ，其中正好有 $M$ 对人彼此为朋友。但他们对于一场成功的聚会有非常严格的规定。  

每一场巴尔提亚岛的聚会中有 5 个人，如果聚会上的所有人彼此是朋友（这样他们就可以互相交谈但不需要担心与自己不认识的人交谈），或者聚会中没有两个人彼此是朋友（这样他们就可以与自顾自玩手机而不会被别人打扰），则这是一个成功的聚会。
 
 请帮助巴尔提亚人举办一场成功的聚会，或者告诉他们这是不可能的。
 
 &nbsp;

## 说明/提示

$ 5 \leqslant N \leqslant 2 \times 10^5 $  

$ 1 \leqslant M \leqslant 2 \times 10^5 $

## 样例 #1

### 输入

```
6 3
1 4
4 2
5 4```

### 输出

```
1 2 3 5 6```

## 样例 #2

### 输入

```
5 4
1 2
2 3
3 4
4 5```

### 输出

```
-1```

# 题解

## 作者：Jerrlee✅ (赞：6)

## 题意
巴尔提亚岛上居住着 $n$ 个人，编号从 $1$ 到 $n$ ，其中正好有 $m$ 对人彼此为朋友。但他们对于一场成功的聚会有非常严格的规定。

每一场聚会都有 $5$ 个人，如果聚会上的所有人彼此是朋友，或聚会中没有两个人彼此是朋友，则这是一个成功的聚会。

不可能时输出 `-1`。
## 思路
[拉姆齐定理](https://baike.baidu.com/item/%E6%8B%89%E5%A7%86%E9%BD%90%E5%AE%9A%E7%90%86)

如果我们至少有 $48$ 人，我们将总能找到一个成功的分组（因为众所周知，拉姆齐定理的 $R(5,5)$ 数字介于 $43$ 和 $48$ 之间）。如果我们有超过 $48$ 人，我们可以在前 $48$ 人中寻找一个成功的分组，而忽略其他人。这意味着我们可以暴力解决这个任务。该算法的复杂度很高：$O(n^5)$。（有好的算法欢迎提出~）
## 代码
```cpp
#include<iostream>
using namespace std;
int n,m,g[55][55]; //g 可以理解为一个 bool 数组
int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		if(a<55&&b<55) g[a][b]=g[b][a]=1;
	}
	for(int a=1;a<=min(48,n);a++)
		for(int b=a+1;b<=min(48,n);b++)
			for(int c=b+1;c<=min(48,n);c++)
				for(int d=c+1;d<=min(48,n);d++)
					for(int e=d+1;e<=min(48,n);e++)
						if((g[a][b]&&g[a][c]&&g[a][d]&&g[a][e]&&g[b][c]&&g[b][d]&&g[b][e]&&g[c][d]&&g[c][e]&&g[d][e])||(!g[a][b]&&!g[a][c]&&!g[a][d]&&!g[a][e]&&!g[b][c]&&!g[b][d]&&!g[b][e]&&!g[c][d]&&!g[c][e]&&!g[d][e]))
							return cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e,0;
	cout<<-1;
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/60452072)

[AC记录（CF）](http://codeforces.com/contest/1600/submission/132535391)

---

## 作者：Argon_Cube (赞：3)

没听说过 Ramsey 定理。

在一张图里随机选一对点，它们之间有边或者没边的概率一定有一个大于等于二分之一。那么 $5$ 个点的完全图有 $10$ 条边，感性理解一下，这 $10$ 条边都有或者都没有的概率应该大于 $\frac{1}{1024}$。所以如果有解，那么随机 $4\times 10^6$ 组点找不到解的概率应该小到可以忽略。

如果随机完了 $4\times 10^6$ 组点还是没找到解就输出无解。

```cpp
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <bitset>
#include <string>
#include <array>
#include <ctime>

using namespace std;

unordered_set<long long> edges;
default_random_engine rdeg(time(nullptr));

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cnt,cnte;
    cin>>cnt>>cnte;
    uniform_int_distribution<int> randnd(1,cnt);
    while(cnte--)
    {
        int u,v;
        cin>>u>>v;
        if(u>v)
            swap(u,v);
        edges.insert(u*cnt+v);
    }
    auto finde=[cnt](int u,int v){return edges.find(min(u,v)*cnt+max(u,v))!=edges.end();};
    array<int,5> answer;
    bool flag=true;
    int cntq=0;
    while(flag&&cntq<4e6)
    {
        flag=false;
        for(int& i:answer)
            i=randnd(rdeg);
        bool state=finde(answer[0],answer[1]);
        for(int i=0;i<5;i++)
            for(int j=0;j<i;j++,++cntq)
                if(answer[i]==answer[j]||state!=finde(answer[i],answer[j]))
                {
                    flag=true;
                    break;
                }
    }
    if(flag)
        return cout<<-1,0;
    for(int i:answer)
        cout<<i<<' ';
    return 0;
}
```

---

## 作者：Gordon_Song (赞：1)

## 前置定理

拉姆齐定理：$R(5,5)\leq 48$。[度娘链接](https://baike.baidu.com/item/%E6%8B%89%E5%A7%86%E9%BD%90%E5%AE%9A%E7%90%86/7478185)。

说人话：当点数 $n$ 大于等于 $48$ 时，一定满足存在五个点互相之间都没有边，或五个点互相之间都有边。

## 思路

对于 $n \leq 48$ 的数据，我们直接暴力枚举 $5$ 个点在验证就可以了。

对于 $49 \le n$ 的数据，一定可以找到一组五个点都在 $48$ 以内的解，直接在 $48$ 以内找就可以了。

## 代码

```cpp
int n,m;
bool g[101][101];
int a[101];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		if(x<=60&&y<=60){
			g[x][y]=1;g[y][x]=1;
		}
	}
	for(a[1]=1;a[1]<=min(n,60);a[1]++){
		for(a[2]=a[1]+1;a[2]<=min(n,60);a[2]++){
			for(a[3]=a[2]+1;a[3]<=min(n,60);a[3]++){
				for(a[4]=a[3]+1;a[4]<=min(n,60);a[4]++){
					for(a[5]=a[4]+1;a[5]<=min(n,60);a[5]++){
						bool fl=false;
						for(int i=1;i<=5;i++){
							for(int j=i+1;j<=5;j++){
								if(g[a[i]][a[j]]){
									fl=true;
								}
							}
						}
						if(!fl){
							for(int i=1;i<=5;i++){
								printf("%d ",a[i]);
							}
							return 0;
						}
						fl=false;
						for(int i=1;i<=5;i++){
							for(int j=i+1;j<=5;j++){
								if(!g[a[i]][a[j]]){
									fl=true;
								}
							}
						}
						if(!fl){
							for(int i=1;i<=5;i++){
								printf("%d ",a[i]);
							}
							return 0;
						}
					}
				}
			}
		}
	}
	printf("-1");
}
```


---

## 作者：_zhy (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1600F)。

有 $n$ 个人，问这 $n$ 个人中是否有 $5$ 个人两两认识或两两不认识。

要是用暴力的话 $O(n^5)$，$n \leq 2 \times 10 ^ 5$，妥妥超时。

这个时候我们可以简化算法，我们需要用到[拉姆齐定理](https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&tn=baidu&wd=%E6%8B%89%E5%A7%86%E9%BD%90%E5%AE%9A%E7%90%86&fenlei=256&rsv_pq=0xa2402f6d00014773&rsv_t=c372GDHpzKxJnEit%2F%2FAp8k2afo2nnb%2F34OVOiimBnx5ZIzYQ06NijL7yA4su&rqlang=en&rsv_enter=1&rsv_dl=tb&rsv_sug3=10&rsv_sug1=15&rsv_sug7=100&rsv_sug2=0&rsv_btype=i&inputT=6896&rsv_sug4=6897)。

这个要用到鸽巢原理证明，有兴趣的可以去看看。

如果要确定 $5$ 个人是否两两认识或两两不认识，有 $48$ 人一定满足，不足 $48$ 人直接判断即可，由于要输出具体是哪些人，所以我们循环判断就行。
$n \leq 48$ 的就只存小于等于 $48$ 的人，因为 $48$ 人中一定有两两认识或两两不认识的 $5$ 人。

### code

```cpp
#include <cstdio>

const int N = 50;

int n, m;
bool f[N][N];

int main() {
	scanf("%d %d", &n, &m);
	while (m--) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a <= 48 && b <= 48)	//只处理小于等于48的人。 
			f[a][b] = f[b][a] = true;
	}
	for (int i = 1; i <= 48 && i <= n; i++)	//判断是否两两认识。 
		for (int j = i + 1; j <= 48 && j <= n; j++)
			if (f[i][j])
				for (int k = j + 1; k <= 48 && k <= n; k++)
					if (f[i][k] && f[j][k])
						for (int l = k + 1; l <= 48 && l <= n; l++)
							if (f[i][l] && f[j][l] && f[k][l])
								for (int o = l + 1; o <= 48 && o <= n; o++)
									if (f[i][o] && f[j][o] && f[k][o] && f[l][o]) {
										printf("%d %d %d %d %d\n", i, j, k, l, o);
										return 0;
									}
	for (int i = 1; i <= 48 && i <= n; i++)	//判断是否两两不认识。 
		for (int j = i + 1; j <= 48 && j <= n; j++)
			if (!f[i][j])
				for (int k = j + 1; k <= 48 && k <= n; k++)
					if (!f[i][k] && !f[j][k])
						for (int l = k + 1; l <= 48 && l <= n; l++)
							if (!f[i][l] && !f[j][l] && !f[k][l])
								for (int o = l + 1; o <= 48 && o <= n; o++)
									if (!f[i][o] && !f[j][o] && !f[k][o] && !f[l][o]) {
										printf("%d %d %d %d %d\n", i, j, k, l, o);
										return 0;
									}
	puts("-1");	//都没有就输出-1。 
	return 0;
}
```

---

