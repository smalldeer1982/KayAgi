# [ARC179F] All the Same

## 题目描述

给你一个只包含字符 `A` 和 `B` 的长度为 $N$ 的字符串 $S$。

需要找到一个由字符 `1`、`2` 和 `3` 组成的长度为 $N$ 的字符串 $X$，并定义其**得分**如下：

- 初始化四个变量 $h_1, h_2, h_3, P$ 为 $0$。
- 然后依次处理 $i = 1, 2, \dots, N$：
  - 若 $S$ 的第 $i$ 个字符为 `A`，则执行操作 A；若为 `B`，则执行操作 B。此处，$d$ 代表 $X$ 的第 $i$ 个字符对应的数字。
    - **操作 A**：将 $h_d$ 增加 $2$。
    - **操作 B**：若 $d$ 等于 $2$ 或 $h_d$ 不等于 $h_2$，则将 $P$ 设为 $-10^{100}$；否则将 $h_d$ 和 $h_2$ 各自增加 $1$。
  - 如果此时 $h_1$ 等于 $h_2$ 且等于 $h_3$，则将 $P$ 增加 $1$。
- 最终，$P$ 的值即为字符串 $X$ 的得分。

请输出一个能使得分最大的字符串 $X$。

共有 $T$ 个测试用例，请分别求解每个测试用例。

## 说明/提示

- $1 \le T \le 10^5$
- $1 \le N \le 10^6$
- $S$ 由字符 `A` 和 `B` 组成
- 所有测试用例中的 $N$ 之和不超过 $10^6$

## 样例解释

以每个字符的处理步骤举例说明变量 $(h_1, h_2, h_3, P)$ 的变化：
- 第一个测试用例处理结果为 $(0, 0, 0, 0) \rightarrow (2, 0, 0, 0) \rightarrow (2, 1, 1, 0) \rightarrow (2, 2, 2, 1) \rightarrow (2, 2, 4, 1)$，所以最大得分为 $1$。
- 第二个测试用例处理结果为 $(0, 0, 0, 0) \rightarrow (2, 0, 0, 0) \rightarrow (2, 2, 0, 0) \rightarrow (2, 2, 2, 1) \rightarrow (2, 4, 2, 1) \rightarrow (4, 4, 2, 1)$，最大得分为 $1$。
- 第三个、第四个和第五个测试用例的得分最大值分别为 $0, 0, 2$。

注意，一个测试用例可能会存在多个得分最大的 $X$，选择其中任意一个输出即可。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
4
ABBA
5
AAAAA
6
BBBBBB
7
ABABABA
20
AAABBBBBBBBAAABBBABA```

### 输出

```
1333
12321
333333
1313212
33311111133121111311```

# 题解

## 作者：fydj (赞：4)

### 思路

原题题解已经写得很清楚了。

把它当成俄罗斯方块，方块大小只有 $1\times 2$ 的，```A``` 代表要竖着放，```B``` 代表要横着放。

先考虑一下哪些操作之后可能会让答案加一。假设现在进行完第 $i$ 次操作之后可以让答案加一。设 $a_i$ 表示 $1$ 到 $i$ 操作中有多少个 ```A``` 操作，$b_i$ 表示有多少个 ```B``` 操作。一个方块会占用两个格子，一行有三个格子，容易得到 $a_i+b_i \equiv 0\pmod 3$。接着，也容易发现 $b_i \equiv 0 \pmod 2$。接着把竖着的方块放在第一列（左边），横着的方块放在二三列（右边），横着的方块不能太多，这意味着左边的高度不能低于右边的高度，也就是 $2a_i-b_i\ge 0$。

整理一下，设 $v_i=2a_i-b_i$，前两个式子可以整合为 $v_i \equiv 0 \pmod 6$，后面一个不等式就是 $v_i \ge 0$。

接下来就是要找一个最长的序列 $p$，使得 $p$ 中每一个位置都可以让答案加一，$p$ 的长度就是最大的分数。那么 $v_{pi} \equiv 0 \pmod 6$，为了限制 ```B``` 的个数不会太多，要求 $v_{pi-1}\le v_{pi}$。

这样，求 $p$ 就转换为求最长不下降子序列，$O(n\log n)$ 可以求出。

求出 $p$ 以后就可以把构造 $x$ 拆分为若干段，每一段要构造下标在 $p_{i-1}+1$ 到 $p_i$ 中的 $x$。

按以前的办法，```A``` 操作放左边（第一列），```B``` 操作放右边（二三列），假设一段长度为 $n$，定义 $c_i$ 为做完第 $i$ 次操作之后左边比右边高多少，虽然 $c_n \equiv 0 \pmod 6$，但可能 $c_n\ge 0$，因此要通过调整使得每次 $c_n$ 减少 $6$，最后让 $c_n=0$。

发现 ```A``` 操作会让 $c$ 增加 $2$，而 ```B``` 操作会让 $c$ 减少 $1$。

那么，要找到最前面的 $c_i\ge 4$ 的位置，这个位置 $i$ 的操作一定是 ```A```，$i-1$ 的操作也一定是 ```A```，分两类。

+ 当 $c_{i-1}=2$，$c_i=4$ 时，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tcsxhsgi.png)

此时，把 $x$ 放到中间，同时交换左边和右边，即如果原来左边是第一列、右边是二三列，交换过后左边就是第三列，右边是一二列，这时 ```A``` 操作就要放到第三列，```B``` 操作要放到前两列；反之亦然。交换过后左边比后边高 $-2$，这使得 $c_n$ 减少 $6$。

+ 当 $c_{i-1}=3$，$c_i=5$ 时，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ztwpkkfn.png)

此时把 $x_{i-1}$ 设为 $2$，同时把 $x_i$ 放到右边，这个时候左边比右边高 $-1$，也使得 $c_n$ 减少 $6$。

最后因为有 $v$ 的约束条件，可以保证一定可以通过调整使得方案合法。

因此总的时间复杂度为 $O(n \log n)$，瓶颈在于求最长不下降子序列。

### 代码

```cpp
const int N=1000099;
int T,n,v[N]={},p[N]={},vp[N]={},m,x[N]={},a[N]={},f[N]={},from[N]={},tr[N<<2]={};
char s[N]={};
void color(int l,int r) {
	int i,lp=1,rp=3,an=0;
	a[l-1]=0;
	for(i=l;i<=r;++i) an+=s[i]=='A'?2:-1;
	for(i=l;i<=r;++i) {
		if(s[i]=='A') x[i]=lp,a[i]=a[i-1]+2;
		else if(s[i]=='B') x[i]=rp,a[i]=a[i-1]-1;
		if(a[i-1]==2&&a[i]==4&&an) x[i]=2,swap(lp,rp),a[i]=-2,an-=6;
		else if(a[i-1]==3&&a[i]==5&&an) x[i-1]=2,x[i]=rp,a[i]=-1,an-=6;
	}
	return ;
}
#define lowbit(x) ((x)&-(x))
bool cmp(int x,int y) { return f[x]>f[y]; }
int cmpmax(int x,int y) { return f[x]>f[y]?x:y; }
void put(int x,int v) { while(x<=n) tr[x]=cmpmax(tr[x],v),x+=lowbit(x); return ; }
int get(int x) { int rey=0; while(x) rey=cmpmax(rey,tr[x]),x-=lowbit(x); return rey; }
int main()
{
//	usefile("same");
	int i,maxk;
	read(T);
	loop : --T;
	read(n),scanf("%s",s+1);
	for(i=1;i<=n;++i) v[i]=v[i-1]+(s[i]=='A'?2:-1),f[i]=from[i]=0;
	for(i=1;i<=m;++i) color(p[i-1]+1,p[i]);
	memset(tr,0,(n+5)<<2),f[0]=1;
	for(i=1;i<=n;++i) if(v[i]>=0&&v[i]%6==0) from[i]=get(v[i]/6+1),f[i]=f[from[i]]+1,put(v[i]/6+1,i);
	maxk=0; for(i=1;i<=n;++i) maxk=cmpmax(maxk,i);
	m=f[maxk]; for(i=maxk;i;i=from[i]) p[m--]=i; p[m]=0,m=f[maxk];
	for(i=0;i<m;++i) color(p[i]+1,p[i+1]);
	for(i=p[m]+1;i<=n;++i) x[i]=s[i]=='A'?1:3;
	for(i=1;i<=n;++i) printf("%d",x[i]); printf("\n");
	memset(p,0,(m+5)<<2),memset(vp,0,(m+5)<<2);
	if(T) goto loop;
	return 0;
}
```

---

