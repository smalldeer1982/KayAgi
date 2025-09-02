# 题目信息

# Enemy is weak

## 题目描述

The Romans have attacked again. This time they are much more than the Persians but Shapur is ready to defeat them. He says: "A lion is never afraid of a hundred sheep".

Nevertheless Shapur has to find weaknesses in the Roman army to defeat them. So he gives the army a weakness number.

In Shapur's opinion the weakness of an army is equal to the number of triplets $ i,j,k $ such that $ i&lt;j&lt;k $ and $ a_{i}&gt;a_{j}&gt;a_{k} $ where $ a_{x} $ is the power of man standing at position $ x $ . The Roman army has one special trait — powers of all the people in it are distinct.

Help Shapur find out how weak the Romans are.

## 样例 #1

### 输入

```
3
3 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 3 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
10 8 3 1
```

### 输出

```
4
```

## 样例 #4

### 输入

```
4
1 5 4 3
```

### 输出

```
1
```

# AI分析结果

### 题目重写
# 敌人很弱

## 题目描述
罗马人再次发动了进攻。这一次，他们的人数比波斯人多得多，但沙普尔已经准备好击败他们。他说：“一头狮子从不畏惧一百只绵羊。”

尽管如此，沙普尔还是必须找出罗马军队的弱点才能击败他们。于是，他给这支军队设定了一个弱点数值。

在沙普尔看来，一支军队的弱点等于满足 $i<j<k$ 且 $a_{i}>a_{j}>a_{k}$ 的三元组 $i,j,k$ 的数量，其中 $a_{x}$ 是站在位置 $x$ 的人的战斗力。罗马军队有一个特殊的特点——其中所有人的战斗力都是不同的。

帮助沙普尔弄清楚罗马人有多弱。

## 样例 #1
### 输入
```
3
3 2 1
```
### 输出
```
1
```
## 样例 #2
### 输入
```
3
2 3 1
```
### 输出
```
0
```
## 样例 #3
### 输入
```
4
10 8 3 1
```
### 输出
```
4
```
## 样例 #4
### 输入
```
4
1 5 4 3
```
### 输出
```
1
```

### 算法分类
树状数组

### 题解综合分析与结论
这些题解主要围绕求满足特定条件 $i<j<k$ 且 $a_{i}>a_{j}>a_{k}$ 的三元组数量展开。大部分题解思路基于树状数组，结合离散化处理大数据范围问题。核心在于通过树状数组维护信息，计算每个位置左边比它大的数的数量和右边比它小的数的数量，再利用乘法原理得到每个位置对答案的贡献，最后累加得到总答案。部分题解还涉及动态规划思想，通过状态转移方程求解。不同题解在实现细节和优化程度上有所差异。

### 所选的题解
- **作者：George1123 (5星)**
    - **关键亮点**：思路清晰，明确指出求三元逆序对与二元逆序对在树状数组维护上的联系，提出维护两个权值树状数组的方法，空间和时间复杂度分析准确。
    - **个人心得**：认为别人题解玄学难懂，自己尝试写简单易懂的题解。
    - **重点代码**：
```cpp
//Data
const int N=1e6;
int n,a[N+7],b[N+7];
lng ans;

//Bittree
typedef vector<lng> bit;
bit c1(N+7),c2(N+7);
void add(bit&c,int x,lng y){for(;x<=n;x+=x&-x) c[x]+=y;}
lng sum(bit&c,int x){lng res=0;for(;x;x-=x&-x) res+=c[x];return res;}
lng sum(bit&c,int x,int y){return sum(c,y)-sum(c,x-1);}

//Main
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	for(int i=1;i<=n;i++) ans+=sum(c2,a[i]+1,n),add(c2,a[i],sum(c1,a[i]+1,n)),add(c1,a[i],1);
	printf("%lld\n",ans);
	return 0;
}
```
    - **核心实现思想**：离散化数组元素后，利用两个树状数组 `c1` 和 `c2`，`c1` 维护已遍历元素个数，`c2` 维护满足条件的二元逆序对数量，通过遍历数组并结合树状数组操作累计三元逆序对数量。
- **作者：jdsb (4星)**
    - **关键亮点**：先将原问题转化为求三元上升子序列的数量，再利用动态规划思想，通过状态转移方程 $f[i][j]=\sum\limits_{k=1}^{i-1}f[i-1][k]\ (a_j>a_k)$ 求解，并用树状数组优化，同时考虑到数据离散化。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return x*f;
}
const int N=1e6+5;
int n;
ll a[N],b[N],f[4][N],tr[N],ans;
void add(int x,ll v)
{
	while(x<=n)
	{
		tr[x]+=v;
		x+=x&-x;
	}
}
ll query(int x)
{
	ll s=0;
	while(x)
	{
		s+=tr[x];
		x-=x&-x;
	}
	return s;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=-read(),b[i]=a[i];
	sort(b+1,b+n+1);
	int len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=n;i++) f[1][i]=1;
	for(int i=2;i<=3;i++)
	{
		memset(tr,0,sizeof(tr));
		for(int j=1;j<=n;j++)
		{
			f[i][j]=query(a[j]-1);
			add(a[j],f[i-1][j]);
		}
	}
	for(int i=1;i<=n;i++) ans+=f[3][i];
	printf("%lld\n",ans);
	return 0;
}
```
    - **核心实现思想**：将原序列取反转化为求三元上升子序列，利用动态规划数组 `f` 记录以第 `j` 个数结尾的长度为 `i` 的子序列数量，通过树状数组 `tr` 优化状态转移过程，最终累加 `f[3][i]` 得到答案。
- **作者：peterwuyihong (4星)**
    - **关键亮点**：思路简洁明了，直接对每个位置，通过树状数组分别求其前面大于它的数的数量与后面小于它的数的数量，相乘后累加得到总答案，代码实现较为直观。
    - **重点代码**：
```cpp
#define maxn 1000010
int n;
int a[maxn],b[maxn],cnt;
int c[maxn];
void add(int x,int y){
	for(;x<=cnt;x+=x&-x)c[x]+=y;
}
int ask(int x){
	int ans=0;
	for(;x;x-=x&-x)ans+=c[x];
	return ans;
}
int up[maxn],down[maxn];
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	cnt=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	for(int i=1;i<=n;i++){
		up[i]=ask(cnt)-ask(a[i]);
		add(a[i],1);
	}
	memset(c,0,sizeof c);
	for(int i=n;i;i--){
		down[i]=ask(a[i]-1);
		add(a[i],1);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)ans+=(long long)up[i]*down[i];
	cout<<ans;
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
    - **核心实现思想**：离散化数组后，通过树状数组 `c` 两次遍历数组，第一次正向遍历求每个位置前面大于它的数的数量存于 `up` 数组，第二次反向遍历求每个位置后面小于它的数的数量存于 `down` 数组，最后将 `up[i]` 与 `down[i]` 相乘累加得到答案。

### 最优关键思路或技巧
树状数组结合离散化是解决本题的关键。利用树状数组高效维护前缀和信息，能快速获取每个位置左右两侧满足条件的数的数量。离散化处理大数据范围，将较大值域映射到较小连续区间，降低空间复杂度。部分题解中动态规划与树状数组结合的优化思路，也为解决此类问题提供了新的视角。

### 可拓展思路
同类型题常围绕逆序对、上升子序列等问题，结合不同数据结构（如线段树）或算法（如归并排序求逆序对）进行拓展。类似算法套路为遇到求特定序列关系数量问题时，考虑通过数据结构维护信息，利用乘法原理或动态规划思想求解。

### 推荐洛谷题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：基础的逆序对问题，可帮助理解树状数组求逆序对原理。
- [P1637 三元上升子序列](https://www.luogu.com.cn/problem/P1637)：与本题类似，求三元上升子序列数量，可进一步巩固相关算法应用。
- [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)：树状数组模板题，加深对树状数组操作的理解与应用。

### 个人心得摘录与总结
- George1123 认为他人题解玄学难懂，自己尝试写简单易懂题解，强调清晰表达解题思路的重要性。 

---
处理用时：84.18秒