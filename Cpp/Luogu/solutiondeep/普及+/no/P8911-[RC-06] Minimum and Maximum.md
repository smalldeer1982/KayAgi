# 题目信息

# [RC-06] Minimum and Maximum

## 题目背景

受洛谷限制，本题数据有所删减。评测全套数据请到 [InfOJ](http://119.27.163.117/contest/7/)。

## 题目描述

给定长度为 $n$ 的序列 $[a_1,a_2,\dots ,a_n]$。

$m$ 次询问，每次给出四个正整数 $L_1,R_1,L_2,R_2\ (1\le L_1\le R_1\le 4000,1\le L_2\le R_2\le 4000)$，问有多少个区间 $[l,r]\ (1\le l\le r\le n)$ 满足 $a_l,a_{l+1},\dots,a_r$ 中的最大值属于 $[L_1,R_1]$、最小值属于 $[L_2,R_2]$。

询问次数很大，所以询问是在程序内生成的。请自行阅读提示说明一栏的代码。

## 说明/提示

**样例 1 解释**

五次询问的 $(L_1,R_1,L_2,R_2)$ 分别为 $(1,5,1,5),(1,2,2,4),(3,4,2,2),(2,4,2,2),(2,5,2,5)$，答案分别为 $15,1,1,2,6$。

输出 $(1\times 15)\ \mathrm{xor}\ (2\times 1)\ \mathrm{xor}\ (3\times 1)\ \mathrm{xor}\ (4\times 2)\ \mathrm{xor}\ (5\times 6)=24$。

**样例程序**

下面是我们提供的样例程序，你可以直接以其为基础编写你的程序。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace Generator{
typedef unsigned long long ull;
typedef __uint128_t L;
ull seed;
int p,q;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
}F(2);
void init(){
	cin>>p>>q>>seed;//读入 p,q,seed 
	assert(p!=q);
	F=FastMod(q-p+1);
}
unsigned long long rd () {
	seed ^= (seed << 13);
	seed ^= (seed >> 7);
	seed ^= (seed << 17);
	return seed;
}
void getlr(int &l1,int &r1,int &l2,int &r2){
	//将 l1,r1,l2,r2 作为参数传入，即可得到一组询问 
	l1=F.reduce(rd())+p;
	r1=F.reduce(rd())+p;
	l2=F.reduce(rd())+p;
	r2=F.reduce(rd())+p;
	if(l1>r1)swap(l1,r1);
	if(l2>r2)swap(l2,r2);
}

}
int n,m,a[100005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	Generator::init();
	long long xorsum=0;
	for(int i=1,l1,r1,l2,r2;i<=m;i++){
		Generator::getlr(l1,r1,l2,r2);
		long long ans=/*ans保存你的答案*/;
		xorsum^=ans*i;
	}
	cout<<xorsum;
}
```

**数据范围**

本题有四个子任务。子任务一时间限制 $0.5$ 秒，其它子任务时间限制 $5$ 秒。

所有数据均满足：$1\le n\le 10^5$，$1\le m\le 2\times 10^7$，$1\le a_i\le 4000$，$1\le p\lt q\le 4000$，$0\le seed\lt 2^{64}$。

- 子任务 $1$（$5$ 分）：$n,m,a_i,q\le 10$。
- 子任务 $2$（$20$ 分）：$n\le 10^4$。
- 子任务 $3$（$20$ 分）：$a_i,q\le 10$。
- 子任务 $4$（$55$ 分）：无特殊限制。

## 样例 #1

### 输入

```
5 5
2 4 1 3 5
1 5 1145141919810```

### 输出

```
24```

## 样例 #2

### 输入

```
10 20000000
1 3 4 10 5 5 2 7 10 7
1 10 23333333333333333```

### 输出

```
548722417```

# AI分析结果

### 算法分类
前缀和、枚举

### 综合分析与结论
本题的核心在于高效处理大量询问，要求快速计算满足特定条件的区间数量。两位作者分别采用了不同的预处理和查询策略：

1. **作者：_•́へ•́╬_**  
   - 通过预处理二维前缀和数组 `b[i][j]`，表示所有值在 `[i, j]` 之间的区间数量。  
   - 查询时通过容斥原理快速计算满足条件的区间数量，时间复杂度为 O(1)。  
   - 预处理时间复杂度为 O(nV)，其中 V 是数值范围。

2. **作者：Wf_yjqd**  
   - 使用 RMQ 和二维前缀和进行预处理，记录每个区间的最大值和最小值。  
   - 通过维护右侧第一个比最小值小和比最大值大的位置，优化了预处理过程。  
   - 查询时利用二维前缀和快速计算满足条件的区间数量。

### 所选题解
#### 作者：_•́へ•́╬_ (★★★★★)
**关键亮点**：  
- 通过预处理二维前缀和数组，实现了 O(1) 的查询效率。  
- 使用容斥原理简化了查询逻辑，代码清晰且高效。  
- 预处理过程虽然时间复杂度较高，但在数值范围较小的情况下表现良好。

**核心代码**：
```cpp
for(int i=p;i<=q;++i)
{
    for(int i=0;i<n;l[i]=r[i]=-1,++i);
    for(int j=i;j<=q;++j)
    {
        b[i][j]=b[i][j-1];
        for(int k=0,o;k<c[j].size();++k)
        {
            o=c[j][k];l[o]=r[o]=o;++b[i][j];
            if(o&&~l[o-1])b[i][j]+=o-l[o-1],r[l[o-1]]=o,l[o]=l[o-1];
            if(o<n-1&&~l[o+1])
                b[i][j]+=(o-l[o]+1ll)*(r[o+1]-o),
                l[r[o+1]]=l[o],r[l[o]]=r[o+1];
        }
    }
}
```

#### 作者：Wf_yjqd (★★★★)
**关键亮点**：  
- 通过 RMQ 和二维前缀和进行预处理，优化了查询效率。  
- 维护右侧第一个比最小值小和比最大值大的位置，减少了不必要的计算。  
- 预处理过程虽然复杂，但在大规模数据下表现稳定。

**核心代码**：
```cpp
for(ll i=n;i>=1;i--){
    for(ll j=1;j<=4000;j++){
        if(j==a[i])
            L[j]=R[j]=i;
        else if(j<a[i])
            R[j]=i;
        else
            L[j]=i;
    }
    l=r=a[i];
    for(ll j=i;j<=n;j=min(L[l-1],R[r+1])){
        l=min(l,a[j]);
        r=max(r,a[j]);
        ewqzh[l][r]+=min(L[l-1],R[r+1])-j;
    }
}
```

### 最优关键思路
- **预处理二维前缀和**：通过预处理二维前缀和数组，可以快速查询满足条件的区间数量，极大提高了查询效率。  
- **容斥原理**：在查询时使用容斥原理，简化了复杂条件的计算，使得查询逻辑更加清晰。

### 拓展思路
- **类似问题**：可以扩展到其他需要快速查询满足特定条件的区间数量的问题，如区间和、区间乘积等。  
- **优化预处理**：在数值范围较大的情况下，可以考虑使用更高效的预处理方法，如分块或线段树。

### 推荐题目
1. [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)  
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)  
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：23.92秒