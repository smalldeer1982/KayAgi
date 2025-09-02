# 题目信息

# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 2 1 16
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# Vasya和良好序列

## 题目描述
Vasya有一个由n个整数$a_1, a_2, \dots, a_n$组成的序列$a$。Vasya可以执行以下操作：从序列中选择一个数，并在其二进制表示中交换任意两位。例如，Vasya可以将数字6（$…00000000110_2$）转换为3（$…00000000011_2$）、12（$…000000001100_2$）、1026（$…10000000010_2$）等等。Vasya可以对序列中的任意数字使用此操作任意（可能为零）次。

Vasya将一个序列称为良好序列，如果通过上述操作，他可以得到所有元素的按位异或（https://en.wikipedia.org/wiki/Exclusive_or）等于0的序列。

对于给定的序列$a_1, a_2, \ldots, a_n$，Vasya想计算满足$1 \le l \le r \le n$且序列$a_l, a_{l + 1}, \dots, a_r$为良好序列的整数对$(l, r)$的数量。

## 说明/提示
在第一个示例中，对$(2, 3)$和$(1, 3)$是有效的。对$(2, 3)$有效，因为$a_2 = 7 \rightarrow 11$，$a_3 = 14 \rightarrow 11$，且$11 \oplus 11 = 0$，其中$\oplus$表示按位异或。对$(1, 3)$有效，因为$a_1 = 6 \rightarrow 3$，$a_2 = 7 \rightarrow 13$，$a_3 = 14 \rightarrow 14$，且$3 \oplus 13 \oplus 14 = 0$。

在第二个示例中，对$(1, 2)$、$(2, 3)$、$(3, 4)$和$(1, 4)$是有效的。

## 样例 #1
### 输入
```
3
6 7 14
```
### 输出
```
2
```

## 样例 #2
### 输入
```
4
1 2 1 16
```
### 输出
```
4
```

### 综合分析与结论
这些题解的核心思路都是围绕判断子序列能否通过操作使异或和为0展开。要点在于利用前缀和维护二进制下1的个数，难点是处理最大1的个数不超过总数一半这个限制条件。不同题解在处理该难点时采用了不同方法，有的暴力枚举短区间，有的利用分治、笛卡尔树等更复杂的数据结构和算法。

### 所选的题解
- **作者：开始新的记忆 (5星)**
    - **关键亮点**：思路清晰，代码简洁高效。利用前缀和维护1的个数，通过双重循环枚举区间，同时考虑1的总数为偶数和最大1的个数限制条件，在$O(n)$时间复杂度内解决问题。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,anss[300010],num[300010],cnt[2]={1};
long long ans=0;

int main() 
{	cin>>n;
	for(int i=1;i<=n;++i)
	{
		long long x;
		cin>>x;
		while(x>0)
		{
			num[i]+=(x%2);
			x/=2;
		}
		anss[i]=anss[i-1]+num[i];
		ans+=cnt[anss[i]%2];
		for(int j=i,k=i+1,maxn=0;j>=1 && j>=i-64;--j)
		{
            while(k>j) 
				maxn=max(maxn,num[--k]);
            if(maxn*2>anss[i]-anss[j-1] && anss[i]%2==anss[j-1]%2) 
				--ans;
        }
        ++cnt[anss[i]%2];
	}
	cout<<ans<<endl;
	return 0;
}
```
核心实现思想：外层循环遍历每个数，计算当前数二进制下1的个数并更新前缀和。每次更新前缀和后，通过内层循环枚举可能的左端点，找到该区间内最大1的个数，判断是否满足条件，若不满足则减去之前多算的答案。
- **作者：蒟酱 (4星)**
    - **关键亮点**：同样利用前缀和优化，代码简洁易懂。通过巧妙的枚举顺序和对区间长度的分析，将时间复杂度控制在较低水平。
    - **核心代码片段**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#define siz(x) int((x).size())
#define cauto const auto
#define all(x) (x).begin(),(x).end()
using std::cin;using std::cout;
using loli=long long;
using venti=__int128_t;
using pii=std::pair<int,int>;
constexpr int kN=3e5+1;
int n,a[kN],cnt[]={1,0},sum;
loli ans;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){loli x;cin>>x;a[i]=__builtin_popcountll(x);}
	for(int l=1;l<=n;l++){
		ans+=cnt[(sum+=a[l])&1]++;
		for(int r=l,max=0,num=0;r<=std::min(n,l+58);r++)
			max=std::max(max,a[r]),
			ans-=(num+=a[r])%2==0&&2*max>num;
	}
	cout<<ans;
	return 0;
}
```
核心实现思想：外层循环枚举左端点，更新当前区间1的总数并利用前缀和思想统计答案。内层循环枚举右端点，计算当前区间1的总数和最大值，判断是否满足条件，若不满足则减去答案。
- **作者：Itst (4星)**
    - **关键亮点**：提出两种解决问题的思路，一种是利用最大值分治，另一种是暴力枚举短区间。这里以暴力枚举短区间思路为例，其代码实现较为清晰，对边界条件处理细致。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;

inline ull read(){
    ull a = 0;
    char c = getchar();
    while(!isdigit(c))
        c = getchar();
    while(isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
        c = getchar();
    }
    return a;
}

const int MAXN = 3e5 + 10;
int num[MAXN], rig[MAXN][65], lef[MAXN][65], cnt[MAXN][2], sum[MAXN], ST[21][MAXN], logg2[MAXN], N;
long long ans;

inline int cmp(int a, int b){
    return num[a] > num[b]? a : b;
}

void init_st(){
    for(int i = 2 ; i <= N ; ++i)
        logg2[i] = logg2[i >> 1] + 1;
    for(int i = 1 ; 1 << i <= N ; ++i)
        for(int j = 1 ; j + (1 << i) - 1 <= N ; ++j)
            ST[i][j] = cmp(ST[i - 1][j], ST[i - 1][j + (1 << (i - 1))]);
}

inline int query(int x, int y){
    int t = logg2[y - x + 1];
    return cmp(ST[t][x], ST[t][y - (1 << t) + 1]);
}

void solve(int l, int r){
    if(l > r)
        return;
    if(l == r){
        ans += num[l] == 0;
        return;
    }
    int k = query(l, r);
    //cout << l << ' ' << r << ' ' << k << endl;
    solve(l, k - 1);
    solve(k + 1, r);
    if(k - l < r - k)
        for(int i = k ; i >= l ; --i)
            ans += cnt[r][sum[i - 1] & 1] - cnt[min(max(k - 1, rig[i][num[k]] - 1), r)][sum[i - 1] & 1];
    else
        for(int i = k ; i <= r ; ++i)
            if(lef[i][num[k]] >= l)
                ans += cnt[min(k - 1, lef[i][num[k]] - 1)][sum[i] & 1] - (l == 1? 0 : cnt[l - 2][sum[i] & 1]);
    //cout << l << ' ' << r << ' ' << ans << endl;
}

int main(){
    N = read();
    cnt[0][0] = 1;
    for(int i = 1 ; i <= N ; ++i){
        ull a = read();
        while(a){
            if(a & 1)
                ++num[i];
            a >>= 1;
        }
        sum[i] = sum[i - 1] + num[i];
        cnt[i][0] = cnt[i - 1][0] +!(sum[i] & 1);
        cnt[i][1] = cnt[i - 1][1] + (sum[i] & 1);
        ST[0][i] = i;
        //cout << num[i] << ' ';
    }
    for(int i = 0 ; i <= 64 ; ++i){
        int p = 0;
        for(int j = 1 ; j <= N ; ++j)
            while(p < j && sum[j] - sum[p] >= i << 1)
                rig[++p][i] = j;
        while(p < N)
            rig[++p][i] = N + 1;
        for(int j = N ; j ; --j)
            while(p >= j && sum[p] - sum[j - 1] >= i << 1)
                lef[p--][i] = j;
    }
    init_st();
    //cout << endl;
    solve(1, N);
    cout << ans;
    return 0;
}
```
核心实现思想：先预处理出每个数二进制下1的个数及前缀和，同时利用ST表预处理区间最大值。通过分治，每次找到区间最大值，根据左右子区间长度关系，分别枚举左端点或右端点，结合预处理数组判断是否满足条件并统计答案。

### 最优关键思路或技巧
利用前缀和优化对区间和的计算，通过分析数据范围（$a_i$的二进制位数最多64位），对长度较短的区间进行暴力枚举判断，从而在较低时间复杂度内解决问题。

### 可拓展之处
此类题目属于序列异或性质结合区间统计的问题。类似算法套路有利用前缀和优化区间统计、针对特殊条件（如最大值限制）采用分治或枚举等策略。同类型题可考虑其他关于序列操作并结合区间统计的题目，例如改变操作类型或限制条件等。

### 洛谷相似题目推荐
- P1908 逆序对：考察利用树状数组或归并排序统计序列中的逆序对数量，与本题利用数据结构优化统计操作类似。
- P3370 【模板】字符串哈希：通过哈希值快速判断字符串子串的相等关系，和本题通过前缀和快速判断区间性质有相似之处。
- P1387 最大正方形：在二维数组中寻找满足一定条件的最大正方形，同样需要分析条件并利用合适的数据结构或算法优化枚举过程。 

---
处理用时：55.31秒